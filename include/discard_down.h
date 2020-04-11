/*
 * Determines down pile information.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DISCARD_DOWN_h
#define DISCARD_DOWN_h

#include <vector>
#include "card_util.h"

using std::vector;

struct DiscardDown
{
    vector<CardUtil> down_pile;
};

#endif