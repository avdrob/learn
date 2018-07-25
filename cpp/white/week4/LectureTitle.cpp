#include <string>
using namespace std;

struct Specialization {
	string val;
	explicit Specialization(string s) {val = s;};
};

struct Course {
	string val;
	explicit Course(string s) {val = s;};
};

struct Week {
	string val;
	explicit Week(string s) {val = s;};
};

struct LectureTitle {
	string specialization;
	string course;
	string week;

	LectureTitle(Specialization spec, Course crs, Week w)
	{
		specialization = spec.val;
		course = crs.val;
		week = w.val;
	}
};
