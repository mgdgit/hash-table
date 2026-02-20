#include "dictionary.h"
#include <iostream>

using namespace std;

int main() {
    Dictionary deck;
    PlanetCard userCard;
    int userOption = 0;
    int deckCurrentAmount;

    cout << endl << "Options: " << endl << endl;
    cout << "1. Current amount of cards in the deck." << endl;
    cout << "2. Show all the cards that are currently in the deck." << endl;
    cout << "3. Search a card." << endl;
    cout << "4. Insert a card." << endl;
    cout << "5. Delete a card." << endl;
    cout << "6. Exit." << endl << endl;

    while (userOption < 6) {

        cout << "----------------------------------------------------------" << endl;
        cout << "Select an option: ";
        cin >> userOption;
        cout << endl;

        try {

            switch (userOption)
            {
            case 1:
                deckCurrentAmount = deck.currentAmount();
                cout << "Currently there are " << deckCurrentAmount << " cards in the deck." << endl;
                break;
            case 2:
                deck.showCurrentCards();
                break;
            case 3:
                cout << "Write the name of the card: ";
                cin >> userCard.planetName;
                cout << endl;
                deck.searchCard(userCard);
                break;
            case 4:
                cout << "Write the name and id of the new card that you want to add: ";
                cin >> userCard.planetName >> userCard.id;
                cout << endl;
                deck.insertCard(userCard);
                break;
            case 5:
                cout << "Write the name of the card: ";
                cin >> userCard.planetName;
                cout << endl;
                deck.deleteCard(userCard);
                break;
            case 6:
                break;
            default:
                cout << "Write a valid option." << endl;
                break;
            }

        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    }

    return 0;
}