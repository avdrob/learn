#include <map>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct Name {
	string first;
	string last;
};

class Person {
	public:
		Person(const string& fst, const string& lst, int byear) {
			changes[byear].first = fst;
			changes[byear].last = lst;
			birth_year = byear;
		}

		void ChangeFirstName(int year, const string& first_name) {
			if (year < birth_year)
				return;
			if (changes.count(year) == 0)
				changes[year].last = "";
			changes[year].first = first_name;
		}

		void ChangeLastName(int year, const string& last_name) {
			if (year < birth_year)
				return;
			if (changes.count(year) == 0)
				changes[year].first = "";
			changes[year].last = last_name;
		}

		string GetFullName(int year) const
		{
			if (year < birth_year)
				return "No person";

			string fst = "", lst = "";
			for (const auto& item : changes)
				if (item.first <= year) {
					if (item.second.first.size() > 0)
						fst = item.second.first;
					if (item.second.last.size() > 0)
						lst = item.second.last;
				}

			if (fst.size() == 0 &&
					lst.size() == 0)
				return "Incognito";
			if (fst.size() == 0) {
				string res = lst;
				return res + " with unknown first name";
			}
			if (lst.size() == 0) {
				string res = fst;
				return res + " with unknown last name";
			}

			return fst + " " + lst;
		}

		string GetFullNameWithHistory (int year) const
		{
			if (year < birth_year)
				return "No person";

			string fst = "", lst = "";
			vector<string> vfst = {}, vlst = {};

			for (const auto& item : changes)
				if (item.first <= year) {
					if (item.second.first.size() > 0) {
						fst = item.second.first;
						if (vfst.size() == 0 ||
							item.second.first != vfst.back())
							vfst.push_back(item.second.first);
					}
					if (item.second.last.size() > 0) {
						lst = item.second.last;
						if (vlst.size() == 0 || 
							item.second.last != vlst.back())
							vlst.push_back(item.second.last);
					}
				}
			if (vfst.size() > 0)
				vfst.pop_back();
			if (vlst.size() > 0)
				vlst.pop_back();

			if (fst.size() == 0 &&
					lst.size() == 0)
				return "Incognito";

			string resfst = fst, reslst = lst;
			if (vlst.size() > 0) {
				reslst += " (";
				if (vlst.back() != lst)
					reslst += vlst.back();
				for (int i = vlst.size()-2; i > 0; i--)
					if (vlst[i] != vlst[i+1])
						reslst += ", " + vlst[i];
				if (vlst.size() > 1 && vlst[0] != vlst[1])
					reslst += ", " + vlst[0] + ")";
				if (vlst.size() == 1)
					reslst += ")";
			}
			if (vfst.size() > 0) {
				resfst += " (";
				if (vfst.back() != fst)
					resfst += vfst.back();
				for (int i = vfst.size()-2; i > 0; i--)
					if (vfst[i] != vfst[i+1])
						resfst += ", " + vfst[i]; 
				if (vfst.size() > 1 && vfst[0] != vfst[1])
					resfst += ", " + vfst[0] + ")";
				if (vfst.size() == 1)
					resfst += ")";
			}

			if (resfst.size() == 0) {
				resfst = "with unknown first name";
				return reslst + " " + resfst;
			}
			if (reslst.size() == 0)
				reslst = "with unknown last name";
			return resfst + " " + reslst;
		}

	private:
		map<int, Name> changes;
		int birth_year;
};
