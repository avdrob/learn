#include <vector>
// #include "test_runner.h"

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
{
    // Напишите реализацию функции, не копируя объекты типа Token
    vector<Sentence<Token>> res;
    res.push_back(Sentence<Token>());

    // State codes:
    //   0: prev token was non-end, cur token is non-end (sentence continues)
    //   1: prev token was non-end, cur token is end (sentence terminates)
    //   2: prev token was end, cur token is non-end (new sentence)
    //   3: prev token was end, cur token is end (termination continues)
    int state = 0;
    for (Token &token : tokens) {
        // Determine new state
        switch (state) {
        case 0:
            if (token.IsEndSentencePunctuation()) {
                state = 1;
            }
            break;
        case 1:
            if (token.IsEndSentencePunctuation()) {
                state = 3;
            }
            else {
                state = 2;
            }
            break;
        case 2:
            if (token.IsEndSentencePunctuation()) {
                state = 1;
            }
            else {
                state = 0;
            }
            break;
        case 3:
            if (!token.IsEndSentencePunctuation()) {
                state = 2;
            }
            break;
        }

        // Perform actions depending on new state
        switch (state) {
        case 2:
            res.push_back(Sentence<Token>());
        case 0:
        case 1:
        case 3:
            res.back().push_back(move(token));
            break;
        }
    }

    return res;
}

// struct TestToken {
//   string data;
//   bool is_end_sentence_punctuation = false;
// 
//   bool IsEndSentencePunctuation() const {
//     return is_end_sentence_punctuation;
//   }
//   bool operator==(const TestToken& other) const {
//     return (data == other.data) && (is_end_sentence_punctuation ==
//                                     other.is_end_sentence_punctuation);
//   }
// };
// 
// ostream& operator<<(ostream& stream, const TestToken& token) {
//   return stream << token.data;
// }
// 
// // Тест содержит копирования объектов класса TestToken.
// // Для проверки отсутствия копирований в функции SplitIntoSentences
// // необходимо написать отдельный тест.
// void TestSplitting() {
//   ASSERT_EQUAL(
//     SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
//     vector<Sentence<TestToken>>({
//         {{"Split"}, {"into"}, {"sentences"}, {"!"}}
//     })
//   );
// 
//   ASSERT_EQUAL(
//     SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
//     vector<Sentence<TestToken>>({
//         {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
//     })
//   );
// 
//   ASSERT_EQUAL(
//     SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
//     vector<Sentence<TestToken>>({
//         {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
//         {{"Without"}, {"copies"}, {".", true}},
//     })
//   );
// }
// 
// int main() {
//   TestRunner tr;
//   RUN_TEST(tr, TestSplitting);
//   return 0;
// }
