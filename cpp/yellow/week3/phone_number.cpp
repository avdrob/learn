#include <string>
#include <iostream>
#include <sstream>
#include <exception>

#include "phone_number.h"

using namespace std;

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}

string PhoneNumber::GetCityCode() const {
	return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
	return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
	return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}

PhoneNumber::PhoneNumber(const string &international_number) {
	istringstream iss(international_number);
	char c;

	iss >> c;
	if (c != '+')
		throw invalid_argument("Not beginning with +");

	getline(iss, country_code_, '-');
	if (country_code_.size() == 0)
		throw invalid_argument("Wrong country code");

	getline(iss, city_code_, '-');
	if (city_code_.size() == 0)
		throw invalid_argument("Wrong city code");

	getline(iss, local_number_);
	if (local_number_.size() == 0)
		throw invalid_argument("Wrong local number");
}
