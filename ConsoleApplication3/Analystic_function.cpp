//#pragma once
//#include <iostream>
//#include <algorithm>
//#include <map>
//#include <vector>
//#include <unordered_map>
//class Card
//{
//public:
//	int num, suit;
//
//	Card(int _num, int _suit)
//	{
//		num = _num;
//		suit = _suit;
//	}
//
//	Card() {}
//};
//using namespace std;
//vector<Card> removeDuplicates(vector<Card> vec) {
//	vector<Card> result;
//	for (int i = 0; i < vec.size(); i++) {
//		if (result.empty() || vec[i].num != result.back().num) {
//			result.push_back(vec[i]);
//		}
//	}
//	return result;
//}
//
//// GET ALL CARDS FROM TABLE AND HAND
//vector <Card> get_all_cards(vector<Card> table, vector<Card> hand)
//{
//	vector <Card> all;
//	for (size_t i = 0; i < table.size(); i++)
//	{
//		all.push_back(table[i]);
//	}
//	for (size_t i = 0; i < hand.size(); i++)
//	{
//		all.push_back(hand[i]);
//	}
//	return all;
//}
//
//// SORT CARDS
//vector <Card> sort_by_num(vector <Card> all)
//{
//	Card buff;
//	for (size_t i = 0; i < all.size(); i++)
//	{
//		for (size_t j = 0; j < all.size() - i - 1; j++)
//		{
//			if (all[j].num > all[j + 1].num)
//			{
//				buff = all[j];
//				all[j] = all[j + 1];
//				all[j + 1] = buff;
//			}
//		}
//	}
//
//	return all;
//}
//
//vector <Card> sort_by_suit(vector <Card> all)
//{
//	Card buff;
//	for (size_t i = 0; i < all.size(); i++)
//	{
//		for (size_t j = 0; j < all.size() - i - 1; j++)
//		{
//			if (all[j].suit > all[j + 1].suit)
//			{
//				buff = all[j];
//				all[j] = all[j + 1];
//				all[j + 1] = buff;
//			}
//		}
//	}
//
//	return all;
//}
//
//// PAIR
//bool check_bool_pair(vector <Card> all)
//{
//	for (size_t i = 0; i < all.size(); i++)
//	{
//		for (size_t j = 0; j < all.size(); j++)
//		{
//			if (i != j) {
//				if (all[i].num == all[j].num) return true;
//			}
//		}
//	}
//	return false;
//}
//
//// SET
//bool check_bool_set(vector <Card> all)
//{
//	unordered_map<int, int> card_count;
//
//	for (const Card& card : all)
//	{
//		card_count[card.num]++;
//	}
//
//	for (const auto& pair : card_count)
//	{
//		if (pair.second == 3)
//		{
//			return true;
//		}
//	}
//
//
//}
//
//// ROYAL FLUSH
//bool check_royal_flush(vector <Card> all)
//{
//	int count = 0;
//	int suit = 0;
//	for (size_t i = 0; i < all.size(); i++)
//	{
//		if (all[i].num == 13)
//		{
//			count++;
//			suit = all[i].suit;
//			break;
//		}
//	}
//	if (count == 0) return 0;
//
//	for (size_t i = 0; i < all.size(); i++)
//	{
//		if (all[i].num == 12 && all[i].suit == suit)
//		{
//			count++;
//			break;
//		}
//	}
//
//	if (count == 1) return 0;
//
//	for (size_t i = 0; i < all.size(); i++)
//	{
//		if (all[i].num == 11 && all[i].suit == suit)
//		{
//			count++;
//			break;
//		}
//	}
//
//	if (count == 2) return 0;
//
//	for (size_t i = 0; i < all.size(); i++)
//	{
//		if (all[i].num == 10 && all[i].suit == suit)
//		{
//			count++;
//			break;
//		}
//	}
//	if (count == 3) return 0;
//
//	for (size_t i = 0; i < all.size(); i++)
//	{
//		if (all[i].num == 9 && all[i].suit == suit)
//		{
//			count++;
//			break;
//		}
//	}
//
//	if (count == 4) return 0;
//	else return 1;
//}
//
//// STRAIGHT
//bool check_straight(vector <Card> all)
//{
//	all = removeDuplicates(all);
//	all = sort_by_num(all);
//	int count = 1;
//	while (all.size() >= 5)
//	{
//		for (size_t i = 0; i < all.size(); i++)
//		{
//			if (i + 1 != all.size()) {
//				if (all[i].num + 1 == all[i + 1].num) count++;
//				else
//				{
//					all.erase(all.begin() + i);
//					break;
//				}
//			}
//		}
//
//		if (count == 5) return true;
//	}
//
//	return false;
//}
//
//// STRAIGHT FLUSH
//bool check_straight_flush(vector <Card> all)
//{
//	if (check_straight(all))
//	{
//		all = sort_by_num(all);
//		int count = 0;
//		while (all.size() >= 5)
//		{
//			for (size_t i = 0; i < all.size(); i++)
//			{
//				if (all[i].num + 1 == all[i + 1].num) count++;
//				else
//				{
//					count = 0;
//					all.erase(all.begin() + i);
//					break;
//				}
//			}
//			if (count == 5) break;
//		}
//
//		for (size_t i = 0; i < all.size(); i++)
//		{
//			if (i + 1 != all.size()) {
//				if (all[i].suit != all[i + 1].suit) return false;
//			}
//		}
//
//		return true;
//	}
//	return false;
//}
//
//// FOUR OF A KIND
//
//bool check_four_of_a_kind(vector <Card> all)
//{
//	unordered_map<int, int> card_count;
//
//	for (const Card& card : all)
//	{
//		card_count[card.num]++;
//	}
//
//	for (const auto& pair : card_count)
//	{
//		if (pair.second == 4)
//		{
//			return true;
//		}
//	}
//	return false;
//}
//
//// FULL HOUSE
//bool check_full_house(vector <Card> all)
//{
//	if (check_bool_set(all))
//	{
//		//9 11 11 11 13 13 13
//		unordered_map<int, int> card_count;
//		int count = 0;
//
//		for (const Card& card : all)
//		{
//			card_count[card.num]++;
//		}
//
//		for (const auto& pair : card_count)
//		{
//			if (pair.second == 3)
//			{
//				card_count.erase(pair.first);
//				count++;
//				break;
//			}
//		}
//
//		for (const auto& pair : card_count)
//		{
//			if (pair.second == 3 || pair.second == 2)
//			{
//				count++;
//			}
//		}
//
//		if (count == 2)  return true;
//		else return false;
//	}
//	return false;
//}
//
//// FLUSH
//bool check_flush(vector <Card> all)
//{
//	all = sort_by_suit(all);
//	int count = 0;
//	for (size_t i = 0; i < all.size(); i++)
//	{
//		for (size_t j = 0; j < all.size(); j++)
//		{
//			if (all[i].suit == all[j].suit) count++;
//			if (count == 5) return true;
//		}
//		count = 0;
//	}
//	return false;
//}
//
//
//// TWO PAIR
//bool check_two_pair(vector <Card> all)
//{
//	if (check_bool_pair(all))
//	{
//		vector <int> index;
//		int count = 0;
//		all = sort_by_num(all);
//		for (size_t i = 0; i < all.size(); i++)
//		{
//			if (i + 1 != all.size()) {
//				if (all[i].num == all[i + 1].num)
//				{
//					count++;
//					index.push_back(i);
//					index.push_back(i);
//					break;
//				}
//			}
//		}
//
//		for (size_t i = 0; i < index.size(); i++)
//		{
//			all.erase(all.begin() + index[i]);
//		}
//
//		for (size_t i = 0; i < all.size(); i++)
//		{
//			if (i + 1 != all.size()) {
//				if (all[i].num == all[i + 1].num)
//				{
//					count++;
//					index.push_back(i);
//					index.push_back(i + 1);
//				}
//			}
//		}
//
//		if (count == 2) return true;
//	}
//	return false;
//}