#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;

/*
enum class Gender {
	FEMALE,
	MALE
};

struct Person {
	int age;  // возраст
	Gender gender;  // пол
	bool is_employed;  // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
  if (range_begin == range_end) {
    return 0;
  }
  vector<typename InputIt::value_type> range_copy(range_begin, range_end);
  auto middle = begin(range_copy) + range_copy.size() / 2;
  nth_element(
      begin(range_copy), middle, end(range_copy),
      [](const Person& lhs, const Person& rhs) {
        return lhs.age < rhs.age;
      }
  );
  return middle->age;
}
*/

void PrintStats(vector<Person> persons)
{
	int age;
	vector<Person>::iterator it;

	age = ComputeMedianAge(persons.begin(), persons.end());
	cout << "Median age = " << age << endl;

	it = partition(persons.begin(), persons.end(),
			[] (const Person &p) {
				return p.gender == Gender::FEMALE;
			});
	age = ComputeMedianAge(persons.begin(), it);
	cout << "Median age for females = " << age << endl;

	it = partition(persons.begin(), persons.end(),
			[] (const Person &p) {
				return p.gender == Gender::MALE;
			});
	age = ComputeMedianAge(persons.begin(), it);
	cout << "Median age for males = " << age << endl;

	it = partition(persons.begin(), persons.end(),
			[] (const Person &p) {
				return p.gender == Gender::FEMALE &&
					p.is_employed == true;
			});
	age = ComputeMedianAge(persons.begin(), it);
	cout << "Median age for employed females = " << age << endl;

	it = partition(persons.begin(), persons.end(),
			[] (const Person &p) {
				return p.gender == Gender::FEMALE &&
					p.is_employed == false;
			});
	age = ComputeMedianAge(persons.begin(), it);
	cout << "Median age for unemployed females = " << age << endl;

	it = partition(persons.begin(), persons.end(),
			[] (const Person &p) {
				return p.gender == Gender::MALE &&
					p.is_employed == true;
			});
	age = ComputeMedianAge(persons.begin(), it);
	cout << "Median age for employed males = " << age << endl;

	it = partition(persons.begin(), persons.end(),
			[] (const Person &p) {
				return p.gender == Gender::MALE &&
					p.is_employed == false;
			});
	age = ComputeMedianAge(persons.begin(), it);
	cout << "Median age for unemployed males = " << age << endl;
}

/*
int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}
*/
