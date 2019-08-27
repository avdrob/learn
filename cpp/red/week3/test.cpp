#include <cstdlib>
#include <string>

using namespace std;

int main()
{
    string *s = new string[3];
    delete s;
    return 0;
}