#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>
using namespace std;

class Card
{
	std::string image_path;

public:

	int num;
	int suit;

	Card()
	{
		num = 0;
		suit = 0;
		image_path = "";
	}

	Card(int num, int suit)
		: num(num), suit(suit)
	{
		image_path = ":/images/" + to_string(num) + "" + to_string(suit);
	}

	std::string get_image_path() const { return image_path; }
};

vector<Card> table;
vector<Card> hand;

vector<Card> removeDuplicates(vector<Card> vec) {
	vector<Card> result;
	for (int i = 0; i < vec.size(); i++) {
		if (result.empty() || vec[i].num != result.back().num) {
			result.push_back(vec[i]);
		}
	}
	return result;
}

// GET ALL CARDS FROM TABLE AND HAND
vector <Card> get_all_cards(vector<Card> table, vector<Card> hand)
{
	vector <Card> all;
	for (size_t i = 0; i < table.size(); i++)
	{
		all.push_back(table[i]);
	}
	for (size_t i = 0; i < hand.size(); i++)
	{
		all.push_back(hand[i]);
	}
	return all;
}

vector <Card> all = get_all_cards(table, hand);
// SORT CARDS
vector <Card> sort_by_num(vector <Card> all)
{
	Card buff;
	for (size_t i = 0; i < all.size(); i++)
	{
		for (size_t j = 0; j < all.size() - i - 1; j++)
		{
			if (all[j].num > all[j + 1].num)
			{
				buff = all[j];
				all[j] = all[j + 1];
				all[j + 1] = buff;
			}
		}
	}

	return all;
}

vector <Card> sort_by_suit(vector <Card> all)
{
	Card buff;
	for (size_t i = 0; i < all.size(); i++)
	{
		for (size_t j = 0; j < all.size() - i - 1; j++)
		{
			if (all[j].suit > all[j + 1].suit)
			{
				buff = all[j];
				all[j] = all[j + 1];
				all[j + 1] = buff;
			}
		}
	}

	return all;
}

// PAIR
bool check_bool_pair(vector <Card> all)
{
	for (size_t i = 0; i < all.size(); i++)
	{
		for (size_t j = 0; j < all.size(); j++)
		{
			if (i != j) {
				if (all[i].num == all[j].num) return true;
			}
		}
	}
	return false;
}

// SET
bool check_bool_set(vector <Card> all)
{
	unordered_map<int, int> card_count;

	for (const Card& card : all)
	{
		card_count[card.num]++;
	}

	for (const auto& pair : card_count)
	{
		if (pair.second == 3)
		{
			return true;
		}
	}

	return false;
}

// ROYAL FLUSH
bool check_royal_flush(vector <Card> all)
{
	int count = 0;
	int suit = 0;
	for (size_t i = 0; i < all.size(); i++)
	{
		if (all[i].num == 13)
		{
			count++;
			suit = all[i].suit;
			break;
		}
	}
	if (count == 0) return 0;

	for (size_t i = 0; i < all.size(); i++)
	{
		if (all[i].num == 12 && all[i].suit == suit)
		{
			count++;
			break;
		}
	}

	if (count == 1) return 0;

	for (size_t i = 0; i < all.size(); i++)
	{
		if (all[i].num == 11 && all[i].suit == suit)
		{
			count++;
			break;
		}
	}

	if (count == 2) return 0;

	for (size_t i = 0; i < all.size(); i++)
	{
		if (all[i].num == 10 && all[i].suit == suit)
		{
			count++;
			break;
		}
	}
	if (count == 3) return 0;

	for (size_t i = 0; i < all.size(); i++)
	{
		if (all[i].num == 9 && all[i].suit == suit)
		{
			count++;
			break;
		}
	}

	if (count == 4) return 0;
	else return 1;
}

// STRAIGHT
bool check_straight(vector <Card> all)
{
	all = removeDuplicates(all);
	all = sort_by_num(all);
	int count = 1;
	while (all.size() >= 5)
	{
		for (size_t i = 0; i < all.size(); i++)
		{
			if (i + 1 != all.size()) {
				if (all[i].num + 1 == all[i + 1].num) count++;
				else
				{
					all.erase(all.begin() + i);
					break;
				}
			}
		}

		if (count == 5) return true;
	}

	return false;
}

// STRAIGHT FLUSH
bool check_straight_flush(vector <Card> all)
{
	if (check_straight(all))
	{
		all = sort_by_num(all);
		int count = 0;
		while (all.size() >= 5)
		{
			for (size_t i = 0; i < all.size(); i++)
			{
				if (all[i].num + 1 == all[i + 1].num) count++;
				else
				{
					count = 0;
					all.erase(all.begin() + i);
					break;
				}
			}
			if (count == 5) break;
		}

		for (size_t i = 0; i < all.size(); i++)
		{
			if (i + 1 != all.size()) {
				if (all[i].suit != all[i + 1].suit) return false;
			}
		}

		return true;
	}
	return false;
}

// FOUR OF A KIND

bool check_four_of_a_kind(vector <Card> all)
{
	unordered_map<int, int> card_count;

	for (const Card& card : all)
	{
		card_count[card.num]++;
	}

	for (const auto& pair : card_count)
	{
		if (pair.second == 4)
		{
			return true;
		}
	}
	return false;
}

// FULL HOUSE
bool check_full_house(vector <Card> all)
{
	if (check_bool_set(all))
	{
		//9 11 11 11 13 13 13
		unordered_map<int, int> card_count;
		int count = 0;

		for (const Card& card : all)
		{
			card_count[card.num]++;
		}

		for (const auto& pair : card_count)
		{
			if (pair.second == 3)
			{
				card_count.erase(pair.first);
				count++;
				break;
			}
		}

		for (const auto& pair : card_count)
		{
			if (pair.second == 3 || pair.second == 2)
			{
				count++;
			}
		}

		if (count == 2)  return true;
		else return false;
	}
	return false;
}

// FLUSH
bool check_flush(vector <Card> all)
{
	all = sort_by_suit(all);
	int count = 0;
	for (size_t i = 0; i < all.size(); i++)
	{
		for (size_t j = 0; j < all.size(); j++)
		{
			if (all[i].suit == all[j].suit) count++;
			if (count == 5) return true;
		}
		count = 0;
	}
	return false;
}


// TWO PAIR
bool check_two_pair(vector <Card> all)
{
	if (check_bool_pair(all))
	{
		vector <int> index;
		int count = 0;
		all = sort_by_num(all);
		for (size_t i = 0; i < all.size(); i++)
		{
			if (i + 1 != all.size()) {
				if (all[i].num == all[i + 1].num)
				{
					count++;
					index.push_back(i);
					index.push_back(i);
					break;
				}
			}
		}

		for (size_t i = 0; i < index.size(); i++)
		{
			all.erase(all.begin() + index[i]);
		}

		for (size_t i = 0; i < all.size(); i++)
		{
			if (i + 1 != all.size()) {
				if (all[i].num == all[i + 1].num)
				{
					count++;
					index.push_back(i);
					index.push_back(i + 1);
				}
			}
		}

		if (count == 2) return true;
	}
	return false;
}

class User
{
	bool is_first_account_entry;

	std::string    name;
	std::string    image_path;

	unsigned int   global_game_money;

	unsigned int   win_count;

public:

	User(const std::string& name, bool is_first_account_entry = true, unsigned int global_game_money = 10000, const std::string& image_path = ":/images/default_user_image",
		unsigned int win_count = 0)
		: name(name), is_first_account_entry(is_first_account_entry), global_game_money(global_game_money), image_path(image_path),
		win_count(win_count)
	{}

	bool is_first_entry() const { return is_first_account_entry; }
	void set_first_entry(bool is_first_account_entry) { this->is_first_account_entry = is_first_account_entry; }

	std::string get_name() const { return name; }
	void set_name(const std::string& name) { this->name = name; }

	std::string get_image_path() const { return image_path; }
	void set_image_path(const std::string& image_path) { this->image_path = image_path; }

	unsigned int get_global_money() const { return global_game_money; }
	void set_global_money(unsigned int global_game_money) { this->global_game_money = global_game_money; }
};
class Player
{

	User* user;

protected:

	bool fold = false;

	std::map<int, int> combination_score;
	std::string        combination_name;

	unsigned int   current_game_money;

	std::vector<Card> cards;

public:

	Player()
	{
		combination_name = "none";
		this->current_game_money = current_game_money;
		cards = std::vector<Card>(2);
	}

	Player(User* user, unsigned int current_game_money)
		: user(user)
	{
		combination_name = "none";
		this->current_game_money = current_game_money;
		cards = std::vector<Card>(2);
	}

	User* get_user() const { return user; }
	bool is_fold() const { return fold; }
	std::string get_combination_name() const { return combination_name; }
	unsigned int get_current_game_money() const { return current_game_money; }
	std::vector<Card> get_cards() const { return cards; }

	void set_current_game_money(unsigned int amount)
	{
		if (amount > user->get_global_money())
		{
			throw(std::string("player doesn't have enough money"));
			return;
		}

		user->set_global_money(user->get_global_money() - amount);
		current_game_money = amount;
	}

	void add_cards(std::vector<Card>& all_cards, int amount = 2)
	{
		Card temp;

		for (int i = 0; i < amount; i++)
		{
			temp = all_cards.at(all_cards.size() - 1);

			all_cards.erase(all_cards.end() - 1);

			cards.push_back(temp);
		}
	}

	virtual void check_and_set_combination()
	{
		///
	}

	/*void fold()
	{
		///
	}

	void check()
	{
		///
	}

	void call(unsigned int amount)
	{
		///
	}

	int raise(unsigned int amount)
	{
		///
	}

	void all_in()
	{
		///
	}*/
}; 

void id_replace(vector <int>& id) 
{
	int buff = id[0];
	id.erase(id.begin());
	id.push_back(buff);
}

int probably_royal(vector <Card> all)
{
	vector <int> rez;
	vector <int> id{ 9,10,11,12,13 };
	int count = 0;
	int suit = 0;
	if (all.size() == 7) return 0;
	for (size_t i = 0; i < 5; i++)
	{
		for (size_t i = 0; i < all.size(); i++)
		{
			if (all[i].num == id[0])
			{
				count++;
				suit = all[i].suit;
				break;
			}
		}

		for (size_t i = 0; i < all.size(); i++)
		{
			if (all[i].num == id[1] && all[i].suit == suit)
			{
				count++;
				break;
			}
		}


		for (size_t i = 0; i < all.size(); i++)
		{
			if (all[i].num == id[2] && all[i].suit == suit)
			{
				count++;
				break;
			}
		}

		for (size_t i = 0; i < all.size(); i++)
		{
			if (all[i].num == id[3] && all[i].suit == suit)
			{
				count++;
				break;
			}
		}

		for (size_t i = 0; i < all.size(); i++)
		{
			if (all[i].num == id[4] && all[i].suit == suit)
			{
				count++;
				break;
			}
		}
		id_replace(id);
		rez.push_back(count);
		count = 0;
	}


	return *max_element(rez.begin(), rez.end());
	
}

vector <Card> sort_by_suit_num(vector <Card> all) 
{
	all = sort_by_suit(all);
	Card buff;
	for (size_t i = 0; i < all.size(); i++)
	{
		for (size_t j = 0; j < all.size() - i - 1; j++)
		{
			if (all[j].num > all[j + 1].num && all[j].suit == all[j + 1].suit)
			{
				buff = all[j];
				all[j] = all[j + 1];
				all[j + 1] = buff;
			}
		}
	}

	return all;
}

int probably_straight_flush(vector <Card> all)
{
	all = sort_by_suit_num(all);
	vector <int> rez;
	int count = 1;
	while (all.size() > 0) {
		for (size_t i = 0; i < all.size(); i++)
		{
			if (i + 1 != all.size()) {
				if (all[i].num + 1 == all[i + 1].num && all[i].suit == all[i + 1].suit) count++;
				else
				{
					rez.push_back(count);
					count = 1;
					all.erase(all.begin() + i);
					break;
				}
			}
			else
			{
				rez.push_back(count);
				count = 1;
				all.erase(all.begin() + i);
				break;
			}
		}
	}

	return *max_element(rez.begin(), rez.end());
}

int probably_flush(vector <Card> all)
{
	all = sort_by_suit(all);
	vector <int> rez;
	int count = 1;
	while (all.size() > 0) {
		for (size_t i = 0; i < all.size(); i++)
		{
			if (i + 1 != all.size()) {
				if (all[i].suit == all[i + 1].suit) count++;
				else
				{
					rez.push_back(count);
					count = 1;
					all.erase(all.begin() + i);
					break;
				}
			}
			else
			{
				rez.push_back(count);
				count = 1;
				all.erase(all.begin() + i);
				break;
			}
		}
	}

	return *max_element(rez.begin(), rez.end());
}

int probably_straight(vector <Card> all)
{
	all = removeDuplicates(all);
	all = sort_by_num(all);
	vector <int> rez;
	int count = 1;
	while (all.size() > 0) {
		for (size_t i = 0; i < all.size(); i++)
		{
			if (i + 1 != all.size()) {
				if (all[i].num + 1 == all[i + 1].num) count++;
				else
				{
					rez.push_back(count);
					count = 1;
					all.erase(all.begin() + i);
					break;
				}
			}
			else
			{
				rez.push_back(count);
				count = 1;
				all.erase(all.begin() + i);
				break;
			}
		}
	}

	return *max_element(rez.begin(), rez.end());
}

int hand_check(vector <Card> hand) 
{
	vector <int> all_num;
	for (size_t i = 0; i < all.size(); i++)
	{
		all_num.push_back(all[i].num);
	}

	if (*max_element(all_num.begin(), all_num.end()) >= 10 && all[0].suit == all[1].suit) return 5;
	else if (all[0].suit == all[1].suit) return 3;
	else if (*max_element(all_num.begin(), all_num.end()) >= 10) return 3;
	else if (probably_straight(all) == 2) return 3;
	else return 0;
}

class Bot : public Player
{
	std::string name;
	std::string image_path;
	bool is_risky;
	int raiting = 0;
	int card_analystic_rez = 0;
	int bot_call = 0;

public:

	Bot(const std::string& name, const std::string& image_path, unsigned int current_game_money, bool is_risky)
		: name(name), image_path(image_path)
	{
		this->current_game_money = current_game_money;
	}

	User* get_user() = delete;

	std::string get_name() const { return name; }
	std::string get_image_path() const { return image_path; }
	int analystic_prob_combinations_and_hand(vector <Card> all, bool first)
	{
		if (first) 
		{
			return hand_check(cards);
		}
		else{
			int result = 0;
			int pr = probably_royal(all);
			int psf = probably_straight_flush(all);
			int pf = probably_flush(all);
			int ps = probably_straight(all);
			if (pr == 3 && all.size() == 5 || pr == 4 && all.size() == 6) return 12;
			else if (pr > 3 && all.size() == 5) return 20;

			else if (psf == 3 && all.size() == 5 || psf == 4 && all.size() == 6) return 10;
			else if (psf > 3 && all.size() == 5) return 17;

			else if (psf == 3 && all.size() == 5 || psf == 4 && all.size() == 6) return 5;
			else if (psf > 3 && all.size() == 5) return 10;

			else if (ps == 3 && all.size() == 5 || ps == 4 && all.size() == 6) return 4;
			else if (ps > 3 && all.size() == 5) return 7;
			else return hand_check(cards);
		}
	}

	void card_analysis(vector <Card> all, int &rez, bool first_circle)
	{
		if (check_royal_flush(all)) rez += 40;
		else if (check_straight_flush(all)) rez += 35;
		else if (check_four_of_a_kind(all)) rez += 30;
		else if (check_full_house(all)) rez += 25;
		else if (check_flush(all)) rez += 20;
		else if (check_straight(all)) rez += 15;
		else if (check_bool_set(all)) rez += 10;
		else if (check_two_pair(all)) rez += 7;
		else if (check_bool_pair(all)) rez += 5;
		else rez += analystic_prob_combinations_and_hand(all, first_circle);

	}
	int analuysis_cash(int rez,int pot, bool first_circle, int first_bet, int last_bet, int last_type_of_bet)
	{
		if (first_circle) 
		{
			if (last_type_of_bet >= 3 && first_bet * 3 <= last_bet) return 0;
			else return 2;
		}
		else 
		{
			if (last_type_of_bet >= 3 && first_bet * 3 <= last_bet && rez < 3) return 0;
			else if (last_type_of_bet >= 3 && first_bet * 3 <= last_bet && rez >= 3) return 3;
			else if (last_type_of_bet >= 3 && rez < 10 && rez > 5) return 5;
			else if (last_type_of_bet >= 3 && rez > 10) return 7;
			else return 2;
		}
	}
	int analysis(vector <Card> table, int pot, bool first_circle, int first_bet, int last_bet, int last_type_of_bet)
	{
		int rezult = 0;
		vector <Card> all = get_all_cards(table, cards);
		card_analysis(all, rezult, first_circle);
		rezult += analuysis_cash(rezult, pot, first_circle, first_bet, last_bet, last_type_of_bet);
		return rezult;
	}
	int doo(vector <Card> table, int pot, bool first_circle,int first_bet, int last_bet, int last_type_of_bet, int rand)
	{
		raiting -= card_analystic_rez;
		card_analystic_rez = analysis(table, pot, first_circle, first_bet, last_bet, last_type_of_bet);
		if (is_risky) card_analystic_rez += 5;
		raiting += card_analystic_rez;

		if (rand >= 70) return 4;

		if (raiting < 5 && !first_bet) return 0;
		else if (raiting >= 5 && raiting <= 10 && last_type_of_bet == 2 || last_type_of_bet == 1) return last_type_of_bet;
		else if (raiting >= 7 && raiting <= 15 && last_type_of_bet == 3) return 2;
		else if (last_type_of_bet >= 3 && raiting >= 10 && raiting <= 25) return 3;
		else if (last_type_of_bet >= 3 && raiting > 25) return 4;
	}
};


int main()	
{
	Card c1(2, 3);
	Card c2(5, 2);
	Card c3(5, 3);
	Card c4(11, 2);
	Card c5(2, 3);
	Card c6(11, 1);
	Card c7(11, 1);
	vector <Card> all{ c1,c2,c3,c4,c5,c6,c7 };
	cout << probably_straight(all);
}
