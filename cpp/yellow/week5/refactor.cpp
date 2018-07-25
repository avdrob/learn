#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
	Person(const string &name = "Nobody", const string &occupation = "Person")
		: Name(name), Occupation(occupation) {}
	string GetName() const { return Name; }
	string GetOccupation() const { return Occupation; }

	void Action(const string &what) const
	{
		cout << Occupation << ": " << Name << " ";
		cout << what << endl;
	}

	virtual void Walk(const string &destination) const
	{
		const string what = "walks to: " + destination;
		Action(what);
	}

protected:
	const string Name;
	const string Occupation;
};

class Student : public Person {
public:
	Student(const string &name, const string &favouriteSong)
		: Person(name, "Student"), FavouriteSong(favouriteSong) {}

	void Learn() const
	{
		const string what = "learns";
		Action(what);
	}

	void SingSong() const
	{
		const string what = "sings a song: " + FavouriteSong;
		Action(what);
	}

	virtual void Walk(const string &destination) const override
	{
		Person::Walk(destination);
		SingSong();
	}

private:
	const string FavouriteSong;
};

class Teacher : public Person {
public:
	Teacher(const string &name, const string &subject)
		: Person(name, "Teacher"), Subject(subject) {}

	void Teach() const
	{
		const string what = "teaches: " + Subject;
		Action(what);
	}

private:
	const string Subject;
};

class Policeman : public Person {
public:
	Policeman(const string &name) : Person(name, "Policeman") {}

	void Check(const Person &p) const
	{
		const string what = "checks " + p.GetOccupation() + ". " +
				p.GetOccupation() + "'s name is: " +
				p.GetName();
		Action(what);
	}
};

void VisitPlaces(const Person &person, const vector<string> &places)
{
	for (auto place : places)
		person.Walk(place);
}

int main()
{
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, {"Moscow", "London"});
	p.Check(s);
	VisitPlaces(s, {"Moscow", "London"});

	return 0;
}
