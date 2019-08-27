#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdint>

using namespace std;

class ReadingManager {
public:
    ReadingManager()
        : users_num(0), user2page(max_users_num + 1, 0),
          page2users_read(max_pages_num + 1, 0)
    {}

    void read(uint32_t user, uint16_t page)
    {
        uint16_t old_page = user2page[user];
        if (old_page == 0) {
            users_num++;
        }
        for (int i = old_page + 1; i <= page; i++) {
            page2users_read[i]++;
        }
        user2page[user] = page;
    }

    double cheer(uint32_t user) const
    {
        uint16_t page = user2page[user];
        if (page == 0) {
            return 0.0;
        }
        else if (users_num == 1) {
            return 1.0;
        }

        return (users_num - page2users_read[page]) * 1.0 / (users_num - 1);
    }


private:
    static const uint32_t max_users_num = 100'000;
    static const uint16_t max_pages_num = 1'000;

    uint32_t users_num;
    vector<uint16_t> user2page;
    vector<uint32_t> page2users_read;
};


int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; ++i) {
        string cmd;
        cin >> cmd;
        int user;
        cin >> user;

        if (cmd == "READ") {
            int page;
            cin >> page;
            manager.read(user, page);
        }
        else if (cmd == "CHEER") {
            cout << setprecision(6) << manager.cheer(user) << "\n";
        }
    }

    return 0;
}