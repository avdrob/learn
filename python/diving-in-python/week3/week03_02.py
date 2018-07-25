import os
import csv
import traceback

class BaseCar:
    """This is a base vehicle class"""    

    def __init__(self, car_type=None,
            photo_file_name=None,
            brand=None, carrying=0.0):
        self._car_type = car_type
        self._photo_file_name = photo_file_name
        self._brand = brand
        self._carrying = carrying
    
    def __repr__(self):
        return f"{str.capitalize(self.car_type)}({self.brand}, {self.photo_file_name}, {self.carrying})"

    @property
    def car_type(self):
        return self._car_type

    @property
    def photo_file_name(self):
        return self._photo_file_name
    
    @property
    def brand(self):
        return self._brand
    
    @property
    def carrying(self):
        return self._carrying

    def get_photo_file_ext(self):
        os.path.splitext(self.photo_file_name)[1]

class Car(BaseCar):
    """Class describing an ordinary car"""

    def __init__(self, photo_file_name=None,
            brand=None, carrying=0,
            passenger_seats_count=5):
        super().__init__(car_type="car",
                photo_file_name=photo_file_name,
                brand=brand, carrying=carrying)
        self._passenger_seats_count = passenger_seats_count

    @property
    def passenger_seats_count(self):
        return self._passenger_seats_count

class Truck(BaseCar):
    """Class describing a truck"""

    def __init__(self, photo_file_name=None,
            brand=None, carrying=0.0,
            body_width=0.0, body_height=0.0,
            body_length=0.0):
        super().__init__(car_type="truck",
                photo_file_name=photo_file_name,
                brand=brand, carrying=carrying)
        self._body_width = body_width
        self._body_height = body_height
        self._body_length = body_length
    
    @property
    def body_width(self):
        return self._body_width

    @property
    def body_height(self):
        return self._body_height

    @property
    def body_length(self):
        return self._body_length

    def get_body_volume(self):
        return self.body_width * self.body_height * self.body_length

class SpecMachine(BaseCar):
    """Special machine class"""

    def __init__(self, photo_file_name=None,
            brand=None, carrying=0,
            extra=None):
        super().__init__(car_type="spec_machine",
                photo_file_name=photo_file_name,
                brand=brand, carrying=carrying)
        self._extra = extra
    
    @property
    def extra(self):
        return self._extra

def parse_car(csv_row):
    cartype_to_attrnum = {
        'car': (5,),
        'truck': (4, 5),
        'spec_machine': (5,)
    }

    min_col = min(min(cartype_to_attrnum.values()))
    reduced_row = [el for el in csv_row if el]
    if len(reduced_row) < min_col:
        raise RuntimeError("insufficient collumns number")

    car_type = reduced_row[0]
    it = iter(reduced_row)
    next(it)

    if car_type == "car":
        if len(reduced_row) not in cartype_to_attrnum[car_type]:
            raise RuntimeError("car: wrong collumns number")
        brand, passenger_seats_count, photo_file_name, carrying = it
        try:
            passenger_seats_count = int(passenger_seats_count)
            carrying = float(carrying)
        except (ValueError, TypeError):
            raise
        return Car(photo_file_name=photo_file_name,
                brand=brand, carrying=carrying,
                passenger_seats_count=passenger_seats_count)
    elif car_type == "truck":
        if len(reduced_row) not in cartype_to_attrnum[car_type]:
            raise RuntimeError("truck: wrong collumns number")
        brand = photo_file_name = body_whl = carrying = ""
        if len(reduced_row) == 5:
            brand, photo_file_name, body_whl, carrying = it
        else:
            brand, photo_file_name, carrying = it
        try:
            body_whl = body_whl.split('x')
            if len(body_whl) not in (1, 3):
                raise RuntimeError("body_whl: wrong parameters number")
            if len(body_whl) == 1:
                body_width = body_height = body_length = 0.0
            else:
                body_whl = map(lambda el: float(el) if el else 0.0, body_whl)
                body_width, body_height, body_length = body_whl
            carrying = float(carrying)
        except (ValueError, TypeError):
            raise
        return Truck(photo_file_name=photo_file_name,
                brand=brand, body_width=body_width,
                body_height=body_height,
                body_length=body_length,
                carrying=carrying)
    elif car_type == "spec_machine":
        if len(reduced_row) not in cartype_to_attrnum[car_type]:
            raise RuntimeError("spec_machine: wrong collumns number")
        brand, photo_file_name, carrying, extra = it
        try:
            carrying = float(carrying)
        except (ValueError, TypeError):
            raise
        return SpecMachine(photo_file_name=photo_file_name,
                brand=brand, carrying=carrying,
                extra=extra)
        

def get_car_list(csv_filename):
    car_list = []
    with open(csv_filename) as csv_fd:
        reader = csv.reader(csv_fd, delimiter=';')
        next(reader)
        for row in reader:
            try:
                car = parse_car(row)
                car_list.append(car)
            except (RuntimeError, ValueError, TypeError):
                # traceback.print_exc()
                continue
    return car_list

def _main():
    print(get_car_list("coursera_week3_cars.csv"))

if __name__ == "__main__":
    _main()

"""Reference solution:

import csv
import sys
import os.path


class CarBase:
    \"""Базовый класс с общими методами и атрибутами\"""

    # индексы полей, которые соответствуют колонкам в исходном csv-файле 
    ix_car_type = 0
    ix_brand = 1
    ix_passenger_seats_count = 2
    ix_photo_file_name = 3
    ix_body_whl = 4
    ix_carrying = 5
    ix_extra = 6

    def __init__(self, brand, photo_file_name, carrying):
        self.brand = brand
        self.photo_file_name = photo_file_name
        self.carrying = float(carrying)

    def get_photo_file_ext(self):
        _, ext = os.path.splitext(self.photo_file_name)
        return ext


class Car(CarBase):
    \"""Класс легковой автомобиль\"""
    
    car_type = "car"

    def __init__(self, brand, photo_file_name, carrying, passenger_seats_count):
        super().__init__(brand, photo_file_name, carrying)
        self.passenger_seats_count = int(passenger_seats_count)

    @classmethod
    def from_tuple(cls, row):
        \""" Метод для создания экземпляра легкового автомобиля
            из строки csv-файла\"""

        return cls(
            row[cls.ix_brand],
            row[cls.ix_photo_file_name],
            row[cls.ix_carrying],
            row[cls.ix_passenger_seats_count],
        )


class Truck(CarBase):
    \"""Класс грузовой автомобиль\"""

    car_type = "truck"

    def __init__(self, brand, photo_file_name, carrying, body_whl):
        super().__init__(brand, photo_file_name, carrying)
        # обрабатываем поле body_whl
        try:
            length, width, height = (float(c) for c in body_whl.split("x", 2))
        except ValueError:
            length, width, height = .0, .0, .0

        self.body_length = length
        self.body_width = width
        self.body_height = height

    def get_body_volume(self):
        return self.body_width * self.body_height * self.body_length

    @classmethod
    def from_tuple(cls, row):
        return cls(
            row[cls.ix_brand],
            row[cls.ix_photo_file_name],
            row[cls.ix_carrying],
            row[cls.ix_body_whl],
        )


class SpecMachine(CarBase):
    \"""Класс спецтехника\"""

    car_type = "spec_machine"

    def __init__(self, brand, photo_file_name, carrying, extra):
        super().__init__(brand, photo_file_name, carrying)
        self.extra = extra

    @classmethod
    def from_tuple(cls, row):
        return cls(
            row[cls.ix_brand],
            row[cls.ix_photo_file_name],
            row[cls.ix_carrying],
            row[cls.ix_extra],
        )


def get_car_list(csv_filename):
    with open(csv_filename) as csv_fd:
        # создаем объект csv.reader для чтения csv-файла
        reader = csv.reader(csv_fd, delimiter=';')
        
        # пропускаем заголовок csv
        next(reader)
        
        # это наш список, который будем возвращать
        car_list = []
        
        # объявим словарь, ключи которого - тип автомобиля (car_type),
        # а значения - класс, объект которого будем создавать
        create_strategy = {car_class.car_type: car_class
                           for car_class in (Car, Truck, SpecMachine)}

        # обрабатываем csv-файл построчно
        for row in reader:
            try:
                # определяем тип автомобиля
                car_type = row[CarBase.ix_car_type]
            except IndexError:
                # если не хватает колонок в csv - игнорируем строку
                continue

            try:
                # получаем класс, объект которого нужно создать
                # и добавить в итоговый список car_list
                car_class = create_strategy[car_type]
            except KeyError:
                # если car_type не извесен, просто игнорируем csv-строку
                continue

            try:
                # создаем и добавляем объект в car_list
                car_list.append(car_class.from_tuple(row))
            except (ValueError, IndexError):
                # если данные некорректны, то игнорируем их
                pass

    return car_list


if __name__ == "__main__":
    print(get_car_list(sys.argv[1]))
"""