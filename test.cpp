#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <set>
#include <cctype>
#include <unordered_map>

std::vector<std::string_view> CountAndFindLines(const std::string_view& text) {

    int lines_count = std::count(text.begin(), text.end(), '\n') + 1;

    std::vector<std::string_view> lines(lines_count);

    auto it_begin = text.begin();

    auto it_end = text.begin();

    while (it_end != text.end()) {

        it_end = std::find(it_begin, text.end(), '\n');

        std::string_view slice(&(*it_begin), std::distance(it_begin, it_end));

        lines.push_back(slice);

        if (it_end != text.end()) {

            ++it_end;
        }

        it_begin = it_end;
    }

    return lines;
};

std::vector<std::string_view> FindWordsInQuery(std::string_view str) {

    std::vector<std::string_view> words;
    auto it_begin = str.begin();
    auto it_end = str.begin();
    bool inWord = false;

    while (it_end != str.end()) {
        if (std::isalpha(*it_end)) {
            if (!inWord) {
                it_begin = it_end;
                inWord = true;
            }
        } else {
            if (inWord) {
                words.push_back(std::string_view(&(*it_begin), std::distance(it_begin, it_end)));
                inWord = false;
            }
        }
        ++it_end;
    }

    if (inWord) {  // space check
        words.push_back(std::string_view(&(*it_begin), std::distance(it_begin, it_end)));
    }

    return words;
};

std::unordered_map<std::string_view, float> FindIDF(const std::vector<std::string_view>& lines, const std::vector<std::string_view>& words) {

    std::unordered_map<std::string_view, float> string_idf;

    for (const auto& word : words) {

        size_t count_words = 0;

        for (const auto& line : lines) {

            if (std::find(line.begin(), line.end(), word) != line.end()) {

                ++count_words;
            }
        }
    
        string_idf[word] = count_words / lines.size();
    }
    return string_idf;
};

std::unordered_map<std::string_view, float> FindIF(const std::vector<std::string_view>& lines, const std::vector<std::string_view>& words) {

    std::unordered_map<std::string_view, float> string_if;

    for (const auto& line : lines) {

        size_t count_words = 0;

        for (const auto& word : words) {

            count_words += std::count(line.begin(), line.end(), word);
        }
        
        if (!count_words) {
    
            string_if[line] = count_words / line.size();
        }
    }

    return string_if;
}

// std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    
//     std::vector<std::string_view> relevant_lines = CountAndFindLines(text);

//     size_t lines_count = relevant_lines.size();

//     size_t findings_count_in_lines = 0;

//     std::vector<std::string_view> query_words = FindWordsInQuery(query);

//     std::unordered_map<int, std::vector<std::string>> lines_by_id;

//     for (const auto& line : relevant_lines) {

        
//     }    
    
// }

int main() {

    std::string_view text =
        "Lorem Ipsum is simply dummy text\n"
        "of the printing and typesetting industry.\n"
        "Lorem Ipsum has been the industry's standard\n"
        "dummy text ever since the 1500s, when an unknown\n"
        "printer took a galley of type and scrambled it\n"
        "to make a type specimen book. It has survived\n"
        "not only five centuries, but also the leap into\n"
        "electronic typesetting, remaining essentially\n"
        "unchanged. It was popularised in the 1960s with\n"
        "the release of Letraset sheets containing Lorem\n"
        "psum passages, and more recently with desktop\n"
        "publishing software like Aldus PageMaker\n"
        "including versions of Lorem Ipsum.";

    std::string_view query = "typesetting release";

    std::vector<std::string_view> res = CountAndFindLines(text);

    for (const auto& slice : res) {
        std::cout << slice << std::endl;
    }

    return 0;
}
