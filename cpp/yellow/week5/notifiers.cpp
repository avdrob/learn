#include <string>
#include <iostream>

using namespace std;

class INotifier {
public:
	virtual void Notify(const string &message) const = 0;
};

class SmsNotifier : public INotifier {
public:
	SmsNotifier(const string &phone_num) : phone_num_(phone_num) {}
	virtual void Notify(const string &message) const override
	{
		SendSms(phone_num_, message);
	}

private:
	string phone_num_;
};

class EmailNotifier : public INotifier {
public:
	EmailNotifier(const string &email) : email_(email) {}
	virtual void Notify(const string &message) const override
	{
		SendEmail(email_, message);
	}

private:
	string email_;
};

/*
void SendSms(const string& number, const string& message) {
  cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
  cout << "Send '" << message << "' to e-mail "  << email << endl;
}

void Notify(INotifier& notifier, const string& message) {
  notifier.Notify(message);
}


int main() {
  SmsNotifier sms{"+7-495-777-77-77"};
  EmailNotifier email{"na-derevnyu@dedushke.ru"};

  Notify(sms, "I have White belt in C++");
  Notify(email, "And want a Yellow one");
  return 0;
}
*/
