/*
 * Determines down pile information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef UP_PILE_h
#define UP_PILE_h

#include <vector>
#include "card_util.h"

using std::vector;

struct DownPile
{
    vector<CardUtil> down_pile;
};

#endif