import unittest


def factorize(x):
    """ Factorize positive integer and return its factors.
        :type x: int,>=0
        :rtype: tuple[N],N>0
    """
    pass


class FactorizeTest(unittest.TestCase):
    def test_wrong_types_raise_exception(self):
        args = ('string', 1.5)
        for arg in args:
            with self.subTest(x=arg):
                self.assertRaises(TypeError, factorize, arg)

    def test_negative(self):
        args = (-1, -10, -100)
        for arg in args:
            with self.subTest(x=arg):
                self.assertRaises(ValueError, factorize, arg)

    def check_equality_cases(self, cases):
        for arg, factors in cases.items():
            with self.subTest(x=arg):
                self.assertEqual(factorize(arg), factors)

    def test_zero_and_one_cases(self):
        cases = {
            0: (0,),
            1: (1,)
        }
        self.check_equality_cases(cases)

    def test_simple_numbers(self):
        cases = {
            3: (3,),
            13: (13,),
            29: (29,)
        }
        self.check_equality_cases(cases)

    def test_two_simple_multipliers(self):
        cases = {
            6: (2, 3),
            26: (2, 13),
            121: (11, 11)
        }
        self.check_equality_cases(cases)

    def test_many_multipliers(self):
        cases = {
            1001: (7, 11, 13),
            9699690: (2, 3, 5, 7, 11, 13, 17, 19)

        }
        self.check_equality_cases(cases)
