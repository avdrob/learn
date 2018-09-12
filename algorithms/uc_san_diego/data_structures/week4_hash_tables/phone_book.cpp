#include <iostream>
#include <vector>
#include <string>

using namespace std;

class PhoneBook {
public:
    PhoneBook()
        : number2name(1e7)
    {}

    void add(unsigned number, const string &name)
    {
        number2name[number] = name;
    }

    void del(unsigned number)
    {
        number2name[number] = "";
    }

    string find(unsigned number) const
    {
        return number2name[number] != "" ? number2name[number] : "not found";
    }

private:
    vector<string> number2name;
};

int main(int argc, char *argv[])
{
    int N;
    cin >> N;

    PhoneBook pb;
    for (int i = 0; i < N; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "add") {
            unsigned number;
            string name;
            cin >> number >> name;
            pb.add(number, name);
        }
        else if (cmd == "del") {
            unsigned number;
            cin >> number;
            pb.del(number);
        }
        else if (cmd == "find") {
            unsigned number;
            cin >> number;
            cout << pb.find(number) << endl;
        }
        else {
            continue;
        }
    }

    return 0;
}