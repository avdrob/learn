from abc import ABC, abstractmethod


class Engine:
    pass


class ObservableEngine(Engine):
    def __init__(self):
        super().__init__()
        self._subscribers = set()

    def subscribe(self, observer):
        self._subscribers.add(observer)

    def unsubscribe(self, observer):
        self._subscribers.discard(observer)

    def notify(self, achievement):
        for observer in self._subscribers:
            observer.update(achievement)


class AbstractObserver(ABC):
    @abstractmethod
    def update(self):
        pass


class ShortNotificationPrinter(AbstractObserver):
    def __init__(self):
        self.achievements = set()

    def update(self, achievement):
        self.achievements.add(achievement['title'])


class FullNotificationPrinter(AbstractObserver):
    def __init__(self):
        self.achievements = list()

    def update(self, achievement):
        if achievement not in self.achievements:
            self.achievements.append(achievement)
