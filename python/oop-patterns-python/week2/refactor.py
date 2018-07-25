import pygame
import random
import math


# Методы для работы с векторами
class Vec2D:
    def __init__(self, x, y):
        if (isinstance(x, Vec2D) and
                isinstance(y, Vec2D)):
            # Construct a new vector with begin and end points
            self._x = y.x - x.x
            self._y = y.y - x.y
        else:
            self._x = x
            self._y = y

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    def __str__(self):
        return f'({self.x}, {self.y})'

    def __repr__(self):
        return f'Vec2D({self.x}, {self.y})'

    def __sub__(self, other):
        return Vec2D(self.x - other.x, self.y - other.y)

    def __add__(self, other):
        return Vec2D(self.x + other.x, self.y + other.y)

    def __len__(self):
        return math.sqrt(self.x * self.x + self.y * self.y)

    def __mul__(self, other):
        if isinstance(other, Vec2D):     # scalar multiplication
            return sum((self.x * other.x, self.y * other.y))
        else:                               # multiplying by number
            return Vec2D(self.x * other, self.y * other)

    # for expressions like N * Vec2D(x, y)
    def __rmul__(self, other):
        if isinstance(self, Vec2D):
            return sum((self.x * other.x, self.y * other.y))
        else:
            return Vec2D(other.x * self, other.y * self)

    def int_pair(self):
        return (int(self.x), int(self.y))


class Polyline:
    def __init__(self, display, screen_dim):
        self.display = display
        self.screen_dim = screen_dim
        self.points = []
        self.speeds = []

    # "Отрисовка" точек
    def draw_points(
            self, points=None,
            style="points", width=3,
            color=(255, 255, 255)
    ):
        if points is None:
            points = self.points

        if style == "line":
            for p_n in range(-1, len(points) - 1):
                pygame.draw.line(
                        self.display, color,
                        points[p_n].int_pair(),
                        points[p_n + 1].int_pair(),
                        width
                )
        elif style == "points":
            for p in points:
                pygame.draw.circle(
                        self.display, color,
                        p.int_pair(), width
                )

    # Пересчитывание координат опорных точек
    def set_points(self):
        for p in range(len(self.points)):
            self.points[p] = self.points[p] + self.speeds[p]
            if not (0 <= self.points[p].x <= self.screen_dim[0]):
                self.speeds[p] = Vec2D(-self.speeds[p].x, self.speeds[p].y)
            if not (0 <= self.points[p].y <= self.screen_dim[1]):
                self.speeds[p] = Vec2D(self.speeds[p].x, -self.speeds[p].y)

    def add_point(self, point, speed):
        self.points.append(point)
        self.speeds.append(speed)

    def remove_point(self, index=None):
        if index is None:
            self.points.pop()
            self.speeds.pop()
        else:
            self.points.pop(index)
            self.speeds.pop(index)

    def clear(self):
        self.points = []
        self.speeds = []

    # Если multiplier < 1, кривая замедлится; иначе -- ускорится
    def speedup(self, multiplier):
        self.speeds = self.speeds * multiplier


class Knot(Polyline):
    def __init__(self, display, screen_dim, steps):
        super().__init__(display, screen_dim)
        self.steps = steps

        self.hue = 0
        self.color = pygame.Color(0)

    def inc_steps(self):
        self.steps += 1

    def dec_steps(self):
        self.steps -= 1 if self.steps > 1 else 0

    # Сглаживание ломаной
    def get_point(self, base_points, alpha, deg=None):
        if deg is None:
            deg = len(base_points) - 1
        if deg == 0:
            return base_points[0]
        return base_points[deg] * alpha + \
            self.get_point(base_points, alpha, deg - 1) * (1 - alpha)

    def get_points(self, base_points, count):
        alpha = 1 / count
        res = []
        for i in range(count):
            res.append(self.get_point(base_points, i * alpha))
        return res

    def get_knot(self, count):
        if len(self.points) < 3:
            return []
        res = []
        for i in range(-2, len(self.points) - 2):
            ptn = []
            ptn.append((self.points[i] + self.points[i + 1]) * 0.5)
            ptn.append(self.points[i + 1])
            ptn.append((self.points[i + 1] + self.points[i + 2]) * 0.5)

            res.extend(self.get_points(ptn, count))
        return res

    def redraw_knot(self):
        self.hue = (self.hue + 1) % 360
        self.color.hsla = (self.hue, 100, 50, 100)
        self.draw_points(
                self.get_knot(self.steps),
                "line", 3, self.color
        )

    def add_point(self, point, speed):
        super().add_point(point, speed)
        self.redraw_knot()

    def set_points(self):
        super().set_points()
        self.redraw_knot()


class Screensaver:
    def __init__(self, caption, screen_dim, knot=True, steps=35):
        pygame.init()
        self.game_display = pygame.display.set_mode(screen_dim)
        self.screen_dim = screen_dim
        self.steps = steps
        self.knot = knot
        pygame.display.set_caption(caption)

    def inc_steps(self):
        self.steps += 1

    def dec_steps(self):
        self.steps -= 1 if self.steps > 1 else 0

    def process_events(self):
        if self.knot:
            curve = Knot(self.game_display, self.screen_dim, self.steps)
        else:
            curve = Polyline(self.game_display)

        working = True
        show_help = False
        pause = True

        while working:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    working = False
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_ESCAPE:
                        working = False
                    if event.key == pygame.K_r:
                        curve.clear()
                    if event.key == pygame.K_p:
                        pause = not pause
                    if event.key == pygame.K_KP_PLUS:
                        self.inc_steps()
                        if self.knot:
                            curve.inc_steps()
                    if event.key == pygame.K_F1:
                        show_help = not show_help
                    if event.key == pygame.K_KP_MINUS:
                        self.dec_steps()
                        if self.knot:
                            curve.dec_steps()

                if event.type == pygame.MOUSEBUTTONDOWN:
                    curve.add_point(
                            Vec2D(event.pos[0], event.pos[1]),
                            Vec2D(random.random() * 2, random.random() * 2)
                    )

            self.game_display.fill((0, 0, 0))
            curve.draw_points()
            curve.redraw_knot()
            if not pause:
                curve.set_points()
            if show_help:
                self.draw_help()

            pygame.display.flip()

    def quit(self):
        pygame.display.quit()
        pygame.quit()

    # Отрисовка справки
    def draw_help(self):
        self.game_display.fill((50, 50, 50))
        font1 = pygame.font.SysFont("courier", 24)
        font2 = pygame.font.SysFont("serif", 24)
        data = []
        data.append(["F1", "Show Help"])
        data.append(["R", "Restart"])
        data.append(["P", "Pause/Play"])
        data.append(["Num+", "More points"])
        data.append(["Num-", "Less points"])
        data.append(["", ""])
        data.append([str(self.steps), "Current points"])

        pygame.draw.lines(self.game_display, (255, 50, 50, 255), True,
                          [(0, 0), (800, 0), (800, 600), (0, 600)], 5)
        for i, text in enumerate(data):
            self.game_display.blit(
                    font1.render(text[0], True, (128, 128, 255)),
                    (100, 100 + 30 * i)
            )
            self.game_display.blit(
                    font2.render(text[1], True, (128, 128, 255)),
                    (200, 100 + 30 * i)
            )


# Основная программа
if __name__ == "__main__":
    SCREEN_DIM = (800, 600)

    scr_saver = Screensaver("MyScreenSaver", SCREEN_DIM)
    scr_saver.process_events()
    scr_saver.quit()

    exit(0)
