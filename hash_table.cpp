#include "hash_table.h"

HashTable::HashTable() {
    // Constructor: Inicializa el tamaño del mazo en 12 posiciones y la cantidad actual en 0.
    deckSize = 12;
    currentAmountOfCards = 0;

    // Reserva memoria dinámica para el arreglo de la tabla hash.
    deck = new PlanetCard[deckSize];
}

size_t HashTable::hash(const PlanetCard &userCard) {
    size_t index = 0;
    size_t cardNameLength = userCard.planetName.length();

    // Función Hash: Usa un algoritmo de hash polinomial (multiplicador 31).
    // Itera por cada carácter del nombre del planeta y calcula un valor numérico.
    for (size_t i = 0; i < cardNameLength; i++) {
        index = (index * 31 + static_cast<unsigned char>(userCard.planetName[i]));
    }

    // Se aplica el operador módulo (%) para asegurar que el índice resultante 
    // esté dentro de los límites del arreglo actual (0 a deckSize - 1).
    index = index % deckSize;

    return index;
}

void HashTable::insertCard(const PlanetCard &userCard) {
    size_t currentIndex = hash(userCard);
    size_t startPoint = currentIndex;
    
    // Almacena el índice de la primera celda con estado "DELETED" que encontremos.
    // Esto sirve para reutilizar celdas borradas y optimizar espacio (Lazy Deletion).
    std::optional<size_t> indexWithDeletedState;

    // Linear Probing (Exploración lineal) para resolver colisiones.
    // Seguimos buscando mientras no encontremos una celda completamente vacía (DOESNT_EXISTS).
    while (deck[currentIndex].state != cardState::DOESNT_EXISTS) {
        
        // Si encontramos una celda ocupada con el mismo nombre, rechazamos el duplicado.
        if (deck[currentIndex].state == cardState::EXISTS && deck[currentIndex].planetName == userCard.planetName) {
            throw std::runtime_error("That card already exists.");
        }

        // Si pasamos por una celda borrada y no hemos guardado ninguna aún, guardamos su índice.
        if (deck[currentIndex].state == cardState::DELETED) {
            if (!indexWithDeletedState.has_value()) {
                indexWithDeletedState = currentIndex;
            } 
        }

        // Avanzamos al siguiente índice de manera circular.
        currentIndex = (currentIndex + 1) % deckSize;

        // Si dimos la vuelta completa a la tabla...
        if (currentIndex == startPoint) {
            // Si encontramos un hueco borrado en el camino, salimos del ciclo para usarlo.
            if (indexWithDeletedState.has_value()) break;
            // Si no hay huecos de ningún tipo, la tabla está llena.
            throw std::runtime_error("The deck is already full.");
        }
    }

    // Si encontramos una celda "DELETED" durante el recorrido, la sobrescribimos.
    if (indexWithDeletedState.has_value()) {
        deck[*indexWithDeletedState].planetName = userCard.planetName;
        deck[*indexWithDeletedState].id = userCard.id;
        deck[*indexWithDeletedState].state = cardState::EXISTS;
        ++currentAmountOfCards;
        std::cout << userCard.planetName << " card was inserted correctly." << std::endl;
    }
    // Si no, usamos la celda vacía ("DOESNT_EXISTS") en la que se detuvo el ciclo while.
    else {
        deck[currentIndex].planetName = userCard.planetName;
        deck[currentIndex].id = userCard.id;
        deck[currentIndex].state = cardState::EXISTS;
        ++currentAmountOfCards;
        std::cout << userCard.planetName << " card was inserted correctly." << std::endl;
    }

    // Comprobamos el "Factor de Carga" (Load Factor). 
    // Si más del 70% de la tabla está llena, disparamos una redimensión (rehash).
    float loadFactor = static_cast<float>(currentAmountOfCards) / deckSize;
    if (loadFactor > 0.7) {
        rehash();
    }
}

void HashTable::searchCard(const PlanetCard &userCard) {
    if (currentAmountOfCards == 0) {
        throw std::length_error("You can't use this option with the deck empty.");
    }

    size_t currentIndex = hash(userCard);
    size_t startPoint = currentIndex;

    // Recorremos la tabla (Linear Probing) buscando la carta.
    while (deck[currentIndex].state != cardState::DOESNT_EXISTS) {
        
        // Si encontramos la carta y está activa (EXISTS), mostramos su ID y terminamos.
        if (deck[currentIndex].state == cardState::EXISTS && deck[currentIndex].planetName == userCard.planetName) {
            std::cout << "That card exists and has an ID of " + std::to_string(deck[currentIndex].id) + "." << std::endl;
            return;
        }

        // Avanzamos al siguiente índice.
        currentIndex = (currentIndex + 1) % deckSize;

        // Si dimos la vuelta completa, la carta no está en la tabla.
        if (currentIndex == startPoint) {
            throw std::runtime_error("That card doesn't exists.");
        }
    }
    
    // Si el while termina por encontrar DOESNT_EXISTS, tampoco existe y no se hace nada.
}

void HashTable::deleteCard(const PlanetCard &userCard) {
    if (currentAmountOfCards == 0) {
        throw std::length_error("You can't use this option with the deck empty.");
    }

    size_t currentIndex = hash(userCard);
    size_t startPoint = currentIndex;

    // Exploración lineal idéntica a searchCard().
    while (deck[currentIndex].state != cardState::DOESNT_EXISTS) {
        
        // Si encontramos la carta solicitada, aplicamos "Borrado Lógico" (Lazy Deletion).
        // Cambiamos su estado a DELETED en lugar de vaciarla.
        // Esto evita que las búsquedas de otras cartas que colisionaron en esta zona se corten prematuramente.
        if (deck[currentIndex].state == cardState::EXISTS && deck[currentIndex].planetName == userCard.planetName) {
            deck[currentIndex].state = cardState::DELETED;
            std::cout << "That card has been successfully deleted." << std::endl;
            --currentAmountOfCards;
            return;
        }

        currentIndex = (currentIndex + 1) % deckSize;

        // Si dimos la vuelta completa, la carta a borrar no existe.
        if (currentIndex == startPoint) {
            throw std::runtime_error("That card doesn't exists.");
        }
    }
}

void HashTable::showCurrentDeck() {
    // Itera sobre el arreglo completo físico, pero solo imprime
    // las posiciones que albergan una carta válida (estado EXISTS).
    for (size_t i = 0; i < deckSize; i++) {
        if (deck[i].state == cardState::EXISTS) {
            std::cout << "Card Name: " << deck[i].planetName << ", ID: " << deck[i].id << "." << std::endl;
        }
    }
}

size_t HashTable::currentAmount() {
    // Retorna un getter simple con el número actual de cartas guardadas.
    return currentAmountOfCards;
}

void HashTable::rehash() {
    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << "To maintain insert and search performance, we will double the deck size." << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;

    // Guardamos las referencias al arreglo viejo para no perder los datos.
    PlanetCard *oldDeck = deck;
    size_t oldDeckSize = deckSize;

    // Duplicamos el tamaño de la tabla y creamos un nuevo arreglo.
    deckSize *= 2;
    deck = new PlanetCard[deckSize];
    
    // Reiniciamos el contador, ya que insertCard lo volverá a incrementar.
    currentAmountOfCards = 0;
    
    // Recorremos el arreglo viejo. Si la carta existe, la insertamos en el nuevo.
    // Al usar insertCard, los elementos son hasheados nuevamente con el nuevo tamaño del mazo (deckSize),
    // por lo que ocuparán nuevas (y mejores) posiciones, y las celdas "DELETED" serán purgadas.
    for (size_t i = 0; i < oldDeckSize; i++) {
        if (oldDeck[i].state == cardState::EXISTS) {
            insertCard(oldDeck[i]);
        }
    }

    // Liberamos la memoria del arreglo viejo para prevenir fugas de memoria (Memory Leaks).
    delete[] oldDeck;
}

bool HashTable::isEmpty() {
    // Si el contador es 0, la tabla no tiene elementos activos.
    if (currentAmountOfCards == 0) {
        return true;
    }
    else {
        return false;
    }
}

HashTable::~HashTable() {
    // Destructor: Libera la memoria del arreglo principal de la tabla al destruir el objeto.
    delete[] deck;
}