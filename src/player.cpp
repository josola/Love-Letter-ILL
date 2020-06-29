/*
 * player.cpp
 * Written by Jordan Sola
 * (C) Jordan Sola 2020 - MIT License
 */

#include <iostream>
#include "player.h"

using std::exception;
using std::cout;
using std::endl;

Player::Player(const string name, const int value, const Reference &reference)
	: name_(name), value_(value), reference_(reference){};

void Player::Draw(const Card obj)
{
	hand_.push_back(obj);
}
template <typename T>
void Player::Discard(T &obj)
{
	if (typeid(obj) == typeid(Card) && typeid(obj) != typeid(int))
	{
		typename vector<T>::iterator it =
			find(hand_.begin(), hand_.end(), [obj](Card &i) { return i == obj; });
		if (it != hand_.end())
		{
			int index = distance(hand_.begin(), it);
			hand_.erase(hand_.begin() + index);
		}
	}
	else if (typeid(obj) == typeid(int) && typeid(obj) != typeid(Card))
	{
		if (obj >= 0 && obj <= 9)
		{
			typename vector<T>::iterator it =
				find(hand_.begin(), hand_.end(),
					 [obj](const Card &i) { return obj == i.GetValue(); });
			if (it != hand_.end())
			{
				int index = distance(hand_.begin(), it);
				hand_.erase(hand_.begin() + index);
			}
			else
			{
				throw exception("Object not in hand");
				return;
			}
		}
		else
		{
			throw exception("Object not in hand");
			return;
		}
	}
	else
	{
		throw exception("Player does not know what to do with that type");
		return;
	}
}

void Player::Print(short unsigned int choice)
{
	switch (choice)
	{
	case 0:
		cout << name_;
		break;
	
	case 1:
		cout << value_;
		break;

	case 2:
		reference_.Print();
		break;

	case 3:
		if (hand_.empty())
		{
			cout << "EMPTY" << endl;
		}
		else
		{
			for (size_t i = 0; i < hand_.size(); i++)
			{
				if (i < hand_.size() - 1)
				{
					cout << hand_.at(i).GetName() << ", ";
				}
				else
				{
					cout << hand_.at(i).GetName() << endl;
				}
			}
		}
		break;

	default:
		break;
	}
}

void Player::Reset()
{
	hand_.clear();
	handmaid_ = false;
	spy_ = false;
}