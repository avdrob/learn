#include <string>
#include <string_view>
#include <set>
#include <map>
#include <utility>

using namespace std;

class Translator {
public:
    Translator() = default;

    void Add(string_view source, string_view target)
    {
        bool inserted;
        set<string>::const_iterator src_it, targ_it;

        tie(src_it, inserted) = words.insert(string(source));
        tie(targ_it, inserted) = words.insert(string(target));
        forward[*src_it] = *targ_it;
        backward[*targ_it] = *src_it;
    }

    string_view TranslateForward(string_view source) const
    {
        return Translate(forward, source);
    }

    string_view TranslateBackward(string_view target) const
    {
        return Translate(backward, target);
    }

private:
    static string_view Translate(
                            const map<string_view, string_view> &dict,
                            string_view word
                        )
    {
        if (dict.find(word) != dict.end()) {
            return dict.at(word);
        }
        else {
            return "";
        }
    }

    set<string> words;
    map<string_view, string_view> forward;
    map<string_view, string_view> backward;
};