#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <string>
#include <iterator>
#include <iostream>
#include <stdexcept>

const int TOTAL_AMOUNT_OF_CARDS = 12;

struct PlanetCard {
    std::string planetName;
    int id;
};

class Dictionary {
    private:
        PlanetCard cards[TOTAL_AMOUNT_OF_CARDS];
        int currentAmountOfCards;
    
    public:
        Dictionary() {
            currentAmountOfCards = 0;
        }

        void insertCard(PlanetCard userCard) {
            if (currentAmountOfCards == 0) {
                cards[0].planetName = userCard.planetName;
                cards[0].id = userCard.id;
                ++currentAmountOfCards;
                std::cout << userCard.planetName << " card was inserted correctly." << std::endl;
                return;
            }

            for (int i = 0; i < currentAmountOfCards; i++) {

                if (userCard.planetName == cards[i].planetName) {
                    throw std::invalid_argument("That card already exists.");
                }
                else {
                    if (i == (currentAmountOfCards - 1)) {

                        if (currentAmountOfCards == TOTAL_AMOUNT_OF_CARDS) {
                            throw std::runtime_error("The array of cards is already full.");
                        }

                        cards[currentAmountOfCards].planetName = userCard.planetName;
                        cards[currentAmountOfCards].id = userCard.id;
                        ++currentAmountOfCards;
                        std::cout << userCard.planetName << " card was inserted correctly." << std::endl;
                        return;
                    }
                }
            }
        }

        void searchCard(PlanetCard userCard) {
            if (currentAmountOfCards == 0) {
                throw std::length_error("You can't use this option with the deck empty.");
            }

            for (int i = 0; i < currentAmountOfCards; i++) {
                if (userCard.planetName == cards[i].planetName) {
                    std::cout << "The ID of that card is " << cards[i].id << "." << std::endl;
                    return;
                }
                else {
                    if (i == (currentAmountOfCards - 1)) {
                        throw std::invalid_argument("That card doesn't exists.");
                    }
                }

            }
        }

        void deleteCard(PlanetCard userCard) {
            if (currentAmountOfCards == 0) {
                throw std::length_error("You can't use this option with the deck empty.");
            }

            for (int i = 0; i < currentAmountOfCards; i++) {
                if (userCard.planetName == cards[i].planetName) {
                    cards[i].planetName = cards[currentAmountOfCards - 1].planetName;
                    cards[i].id = cards[currentAmountOfCards - 1].id;
                    --currentAmountOfCards;
                    std::cout << std::endl << userCard.planetName << " card deleted successfully." << std::endl;
                    return;
                }
                else {
                    if (i == (currentAmountOfCards - 1)) {
                        throw std::invalid_argument("That card doesn't exists.");
                    }
                }
            }
        }

        int currentAmount() {
            return currentAmountOfCards;
        }

        void showCurrentCards() {
            if (currentAmountOfCards == 0) {
                throw std::length_error("You can't use this option with the deck empty.");
            }

            for (int i = 0; i < currentAmountOfCards; i++) {
                std::cout << i + 1 << ". Planet Card Name: " << cards[i].planetName << " - ID: " << cards[i].id << std::endl;
            }
        }

        bool isEmpty() {
            if (currentAmountOfCards == 0) {
                return true;
            }
            else {
                return false;
            }
        }
};

#endif