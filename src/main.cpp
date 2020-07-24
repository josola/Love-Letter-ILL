#include "deck.h"
#include "player.h"
#include "input.h"
#include "reference.h"
#include "game_state.h"
#include "card_actions.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <limits>

using std::any_of;
using std::cin;
using std::cout;
using std::none_of;
using std::numeric_limits;
using std::sort;
using std::streamsize;
using std::to_string;
using std::vector;

int main()
{
	GameState gameState;

	cout << "-- WELCOME TO LOVE LETTER --\n";

	cout << "How many players will be playing: ";
	int player_count = -1;
	cin >> player_count;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (player_count < 2 || player_count > 6)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "Number must be between 2 and 6 players:\n";
		cin >> player_count;
	}

	gameState.SetPlayers(player_count);

	// game loop
	bool game_over = false;
	while (!game_over)
	{
        vector<Card> deck;
        Build(deck);
        Shuffle(deck);

		cout << "-- ROUND " << gameState.round_count_ << " --\n";

		if (gameState.round_count_ > 1)
		{
			for (Player &i : gameState.players_)
			{
				i.Reset();
			}
		}

        vector<Card> aside;
		aside.push_back(deck.at(0));
        deck.erase(deck.begin() + 0);

        vector<Card> discard;
		if (gameState.players_.size() == 2)
		{
			for (int i = 0; i < 2; i++)
			{
				discard.push_back(deck.at(0));
                deck.erase(deck.begin() + 0);
			}
		}

		for (Player &i : gameState.players_)
		{
			i.Draw(deck.at(0));
            deck.erase(deck.begin() + 0);
		}

		vector<Player *> remaining_players;
        for (Player &iPlayer : gameState.players_)
        {
            // player must be playing
            if (iPlayer.Status() && (remaining_players.size() != 1) && !deck.empty())
            {
                // remove handmaid protection
                iPlayer.SetProtection(0);

                // draw input
                cout << iPlayer.GetName() << " draw a card (d): ";
                char draw = ' ';
                cin >> draw;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (draw != 'd')
                {
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    cout << "Input MUST be 'd':\n";
                    cin >> draw;
                }

                // current player draw card
                // iPlayer.Draw(deck.at(0)); // standard logic

                //debugging logic begin
                
                iPlayer.Draw(Card("BARON", 3, "REF"));
                
                // debug logic end

                cout << "\nDeck size: \n";
                cout << deck.size() << '\n';

                cout << "\nDiscard pile:\n";
                if (discard.empty())
                {
                    cout << "EMPTY" << '\n';
                }
                else
                {
                    if (discard.size() == 1)
                    {
                        cout << discard.at(0).GetName() << '\n';
                    }
                    else
                    {
                        for (size_t i = 0; i < discard.size(); i++)
                        {
                            if (i < discard.size() - 1)
                            {
                                cout << discard.at(i).GetName() << ", ";
                            }
                            else
                            {
                                cout << discard.at(i).GetName() << '\n';
                            }
                        }
                    }
                }

                cout << "\nOpponents:\n";
                for (size_t i = 0; i < gameState.players_.size(); i++)
                {
                    if (gameState.players_.size() == 2 && gameState.players_.at(i).GetValue() != iPlayer.GetValue())
                    {
                        cout << gameState.players_.at(i).GetName() << '\n';
                    }
                    else
                    {
                        if (gameState.players_.at(i).GetValue() != iPlayer.GetValue())
                        {
                            if (i == gameState.players_.size() - 1)
                            {
                                cout << gameState.players_.at(i).GetName() << '\n';
                            }
                            else
                            {
                                cout << gameState.players_.at(i).GetName() << ", ";
                            }
                        }
                    }
                }

                // print opponents with Handmaid protection
                cout << "\nHandmaid protection:\n";
                for (size_t i = 0; i < gameState.players_.size(); i++)
                {
                    if (gameState.players_.size() == 2 && gameState.players_.at(i).GetValue() != iPlayer.GetValue() && gameState.players_.at(i).ProtectionStatus())
                    {
                        cout << gameState.players_.at(i).GetName() << '\n';
                    }
                    else
                    {
                        if (gameState.players_.at(i).GetValue() != iPlayer.GetValue() && gameState.players_.at(i).ProtectionStatus())
                        {
                            if (i == gameState.players_.size() - 1)
                            {
                                cout << gameState.players_.at(i).GetName() << '\n';
                            }
                            else if (gameState.players_.at(i).ProtectionStatus())
                            {
                                cout << gameState.players_.at(i).GetName() << ", ";
                            }
                        }
                    }
                }
                if (none_of(gameState.players_.begin(), gameState.players_.end(), [](Player &i) { return i.ProtectionStatus(); }))
                {
                    cout << "NONE\n";
                }

                iPlayer.PrintHand();
                cout << "--\n";

                // log cards already in hand
                vector<int> in_hand;
                vector<Card> hand = *iPlayer.GetHand();
                for (Card iCard : hand)
                {
                    in_hand.push_back(iCard.GetValue());
                }

                // countess restriction check
                bool countess = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 8; });
                bool king = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 7; });
                bool prince = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 5; });

                bool correct_input = false;
                int card = 0;
                while (!correct_input)
                {
                    cout << iPlayer.GetName() << " play a card: ";
                    cin >> card;
                    SanitizeCard(card, -1);

                    if ((countess && king) || (countess && prince))
                    {
                        while (card != 8)
                        {
                            if (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            cout << "You MUST play the Countess.\n";
                        }
                    }

                    // play card in hand: without restriction
                    else
                    {
                        for (Card &iCard : hand)
                        {
                            if (iCard.GetValue() == card)
                            {
                                correct_input = true;
                                break;
                            }
                        }
                        if (!correct_input)
                        {
                            cout << "Not in hand.\n";
                        }
                    }
                }

                // discard card
                iPlayer.Discard(card, discard);

                // play card action
                switch (card)
                {
                case 0:
                    Spy(iPlayer);
                    break;
                case 1:
                    Guard(gameState, iPlayer, discard);
                    break;
                case 2:
                    Priest(gameState, iPlayer);
                    break;
                case 3:
                    Baron(gameState, iPlayer, discard);
                    break;
                case 4:
                    Handmaid(iPlayer);
                    break;
                case 5:
                    Prince(gameState, iPlayer, discard);
                    break;
                case 6:
                    Chancellor(discard, iPlayer);
                    break;
                case 7:
                    King(gameState, iPlayer);
                    break;
                case 8:
                    Countess(iPlayer);
                    break;
                case 9:
                    Princess(iPlayer, discard);
                    break;
                }
                cout << '\n';
                cout << iPlayer.GetName() << " end turn.\n";
            }
            
            // reset remaining players after round start
            remaining_players.erase(remaining_players.begin(), remaining_players.end());
            
            // round ends when one player is standing or deck is empty
            for (Player &iPlayer : gameState.players_)
            {
                if (iPlayer.Status())
                {
                    remaining_players.push_back(&iPlayer);
                }
            }
        }

		// increase round count
		gameState.round_count_++;

		// round end

		// deck is empty, players compare hands, highest hand wins the round
		if (deck.size() == 0)
		{
			cout << "Deck is empty, players compare hands!\n";
			Player *winner = nullptr;
			for (Player &iPlayer : gameState.players_)
			{
				if (iPlayer.GetValue() > winner->GetValue())
				{
        					winner = &iPlayer;  
				}
			}
			cout << winner->GetName() << " has the highest hand! " << winner->GetHand()->at(0).GetName() << '\n';
			winner->Addtoken();
			winner->Winner(1);
		}

		// spy bonus
		int spy_count = 0;
		if (any_of(gameState.players_.begin(), gameState.players_.end(), [](Player &iPlayer) { return iPlayer.SpyStatus(); }))
		{
			Player *spy_bonus = nullptr;
			for (Player &iPlayer : gameState.players_)
			{
				if (iPlayer.Status() && iPlayer.SpyStatus() && spy_count < 2)
				{
					spy_bonus = &iPlayer;
					spy_count++;
				}
			}
			if (spy_count >= 2)
			{
				cout << "Multiple players had the Spy, no one gets a bonus\n";
			}
			else if (spy_count == 1)
			{
				cout << spy_bonus->GetName() << " had the Spy!\n";
				spy_bonus->Addtoken();
				cout << spy_bonus->GetName() << " token count: " << spy_bonus->GetTokenCount() << '\n';
			}
		}

		// check that player has winning token count
		for (Player &iPlayer : gameState.players_)
		{
			if (iPlayer.GetTokenCount() == gameState.winning_token_count_)
			{
				cout << iPlayer.GetName() << " has " << iPlayer.GetTokenCount() << " tokens!\n";
				cout << iPlayer.GetName() << " wins the game!\n";
				game_over = true;
				break;
			}
		}

		// celebrate the last player standing
		Player *winner = nullptr;
		for (Player &iPlayer : gameState.players_)
		{
			if (iPlayer.Status())
			{
				winner = &iPlayer;
			}
		}

		cout << winner->GetName() << " was the last player standing!\n";
		winner->Addtoken();
		cout << winner->GetName() << " token count: " << winner->GetTokenCount() << '\n';
	}

	return 0;
}
