#include <map>
#include <queue>
#include <string>
#include <cstdint>

#include <iostream>

using namespace std;

class BookingManager {
private:
    struct Booking {
        int64_t time;
        uint32_t cliend_id;
        uint16_t room_count;
    };

    struct BookingJournal {
    public:
        BookingJournal(BookingManager &bm) : booking_manager(bm) {} 

        void add_booking(const Booking &booking)
        {
            book_queue.push(booking);
            client2book_cnt[booking.cliend_id] += 1;
            rooms_reserved += booking.room_count;
            adjust_queue();
        }

        uint32_t rooms()
        {
            adjust_queue();
            return rooms_reserved;
        }

        uint32_t uniq_clients()
        {
            adjust_queue();
            return client2book_cnt.size();
        }

    private:
        void adjust_queue()
        {
            while (!book_queue.empty() &&
                   ((book_queue.front().time + secs_per_day) <=
                   booking_manager.current_time)) {
                Booking booking = book_queue.front();
                book_queue.pop();
                client2book_cnt[booking.cliend_id] -= 1;
                rooms_reserved -= booking.room_count;

                if (client2book_cnt[booking.cliend_id] == 0) {
                    client2book_cnt.erase(booking.cliend_id);
                }
            }
        }

        queue<Booking> book_queue;
        map<uint32_t, uint32_t> client2book_cnt;
        uint32_t rooms_reserved = 0;
        BookingManager &booking_manager;
    };

    int64_t current_time = 0;
    static const uint32_t secs_per_day = 86400;

    map<string, BookingJournal> hotel_bookings;


public:
    struct BookingPublic : public Booking {
        string hotel_name;

        friend istream &operator>>(istream &is, BookingPublic &bp)
        {
            is >> bp.time >> bp.hotel_name >> bp.cliend_id >> bp.room_count;
            return is;
        }    
    };

    void book(const BookingPublic &bp)
    {
        current_time = bp.time;

        if (hotel_bookings.find(bp.hotel_name) == hotel_bookings.end()) {
            hotel_bookings.insert(
                    make_pair(bp.hotel_name, BookingJournal(*this))
            );
        }
        hotel_bookings.at(bp.hotel_name).add_booking(
                                Booking{bp.time, bp.cliend_id, bp.room_count}
                            );
    }

    uint32_t rooms(const string &hotel_name)
    {
        if (hotel_bookings.find(hotel_name) == hotel_bookings.end()) {
            return 0;
        }

        return hotel_bookings.at(hotel_name).rooms();
    }

    uint32_t clients(const string &hotel_name)
    {
        if (hotel_bookings.find(hotel_name) == hotel_bookings.end()) {
            return 0;
        }

        return hotel_bookings.at(hotel_name).uniq_clients();
    }
};


int main(int argc, char *argv[])
{
    int Q;
    cin >> Q;

    BookingManager bm;
    for (int i = 0; i < Q; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "BOOK") {
            BookingManager::BookingPublic bp;
            cin >> bp;
            bm.book(bp);
        }
        else if (cmd == "CLIENTS") {
            string hotel_name;
            cin >> hotel_name;
            cout << bm.clients(hotel_name) << '\n';
        }
        else if (cmd == "ROOMS") {
            string hotel_name;
            cin >> hotel_name;
            cout << bm.rooms(hotel_name) << '\n';
        }
    }

    return 0;
}