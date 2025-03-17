#include "ladder.h"

using namespace std;

void error(string word1, string word2, string msg){
    cout << word1 << ' ' << word2 << ' ' << msg << endl;
}

char to_lowercase(char c) {
	return (c >= 'A' && c <= 'Z') ? (c + 32) : c;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
    int len1 = str1.size();
    int len2 = str2.size();
    int len_diff = len1 - len2;
    int char_diff = 0;

    if (abs(len_diff) > d) return false;

    if (len_diff == 0) {
        for (int i = 0; i < len1; ++i) {
            if (to_lowercase(str1[i]) != to_lowercase(str2[i])) ++char_diff;
            if (char_diff > d) return false;
        }
        return char_diff <= d;
    }

    else {
        int len_max = max(len1, len2);
        int len_min = len_max - 1;
        const string& max_word = len1 > len2 ? str1 : str2;
        const string& min_word = len1 < len2 ? str1 : str2;

        int i = 0;
        for (int j = 0; i < len_max && j < len_min; ++i, ++j) {
            if (to_lowercase(max_word[i]) != to_lowercase(min_word[j])) {
                ++char_diff;
                --j;
            }
            if (char_diff > d) return false;
        }
        return true;
	}
}

bool is_adjacent(const string& word1, const string& word2){
    int len_word1 = word1.size();
    int len_word2 = word2.size();
    int len_diff = len_word1 - len_word2;
    int char_diff = 0;

    if (abs(len_diff) > 1) return false;

    if (len_diff == 0) {
        for (int i = 0; i < len_word1; ++i) {
            if (to_lowercase(word1[i]) != to_lowercase(word2[i])) ++char_diff;
            if (char_diff > 1) return false;
        }
        return char_diff <= 1;
    }

	else {
		int len_max = max(len_word1, len_word2);
		int len_min = len_max - 1;
		const string& max_word = len_word1 > len_word2 ? word1 : word2;
		const string& min_word = len_word1 < len_word2 ? word1 : word2;

		int i = 0;
		for (int j = 0; i < len_max && j < len_min; ++i, ++j) {
			if (to_lowercase(max_word[i]) != to_lowercase(min_word[j])) {
				++char_diff;
				--j;
			}
			if (char_diff > 1) return false;
		}
		return true;
	}
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
	vector<string> partial_ladder;
	queue<vector<string>> ladders;
	set<string> visited;
	
	partial_ladder.push_back(begin_word);
	ladders.push(partial_ladder);
	visited.insert(begin_word);
	
	while (!ladders.empty()) {
		partial_ladder = ladders.front();
		ladders.pop();
		string last_word = partial_ladder[partial_ladder.size() - 1];
		for (const auto &word : word_list) {
			if (is_adjacent(last_word, word)) {
				set<string>::iterator visited_word = visited.find(word);
				if (visited_word == visited.end()) {
					visited.insert(word);
					vector<string> new_partial_ladder = partial_ladder;
					new_partial_ladder.push_back(word);
					if (word == end_word) {
						return new_partial_ladder;
					}
					ladders.push(new_partial_ladder);
				}
			}
		}
	}
	vector<string> result;
	return result;
}

void load_words(set<string> & word_list, const string& file_name){
	ifstream in{file_name};
	string word;

	while (in >> word) {
		word_list.insert(word);
	}
}

void print_word_ladder(const vector<string>& ladder){
	if (ladder.size() == 0) {
		cout << "No word ladder found.";
	} else {
		cout << "Word ladder found: ";
		for (const auto& word : ladder) {
			cout << word << ' ';
		}
	}
	cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
