#include <map>
#include <string>
#include <algorithm>

using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string& first_name)
	{
		first_names[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name)
	{
		second_names[year] = last_name;
	}
	string GetFullName(int year)
	{
		// получить имя и фамилию по состоянию на конец года year
		// с помощью двоичного поиска
		string name = "";
		string surname = "";

		if (!first_names.empty() && first_names.begin()->first <= year) {
			auto it = first_names.lower_bound(year);
			if (it->first == year)
				name = it->second;
			else
				name = prev(it)->second;
		}
		if (!second_names.empty() && second_names.begin()->first <= year) {
			auto it = second_names.lower_bound(year);
			if (it->first == year)
				surname = it->second;
			else
				surname = prev(it)->second;
		}

		if (name.size() == 0 && surname.size() == 0)
			return "Incognito";
		if (name.size() == 0)
			return surname + " with unknown first name";
		if (surname.size() == 0)
			return name + " with unknown last name";
		return name + " " + surname;
	}
private:
	map<int, string> first_names;
	map<int, string> second_names;
};
