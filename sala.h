#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
class sala
{
private:
    int id;
    std::string nume;
    int randuri;
    int coloane;
    std::vector<std::vector<bool>> locuri; // false = liber, true = ocupat
public:
    sala(int id, const std::string& nume, int randuri, int coloane)
        : id(id), nume(nume), randuri(randuri), coloane(coloane),
        locuri(randuri, std::vector<bool>(coloane, false)) {}
    int getId() const { return id; }
    std::string getNume() const { return nume; }
    int getRanduri() const { return randuri; }
    int getColoane() const { return coloane; }

    bool esteIndexValid(int rand, int coloana) const {
        return rand >= 0 && rand < randuri && coloana >= 0 && coloana < coloane;
    }
    bool esteLiber(int rand, int coloana) const {
        if (!esteIndexValid(rand, coloana)) {
            throw std::out_of_range(
                "Index invalid! Randul " + std::to_string(rand + 1) +
                ", Coloana " + std::to_string(coloana + 1) +
                " nu exista in sala '" + nume + "' (" +
                std::to_string(randuri) + " randuri x " +
                std::to_string(coloane) + " coloane)."
            );
        }
        return !locuri[rand][coloana];
    }
    void rezervaLoc(int rand, int coloana) {
        if (!esteIndexValid(rand, coloana)) {
            throw std::out_of_range(
                "Index invalid! Randul " + std::to_string(rand + 1) +
                ", Coloana " + std::to_string(coloana + 1) +
                " nu exista in sala '" + nume + "'."
            );
        }
        if (locuri[rand][coloana]) {
            throw std::runtime_error(
                "Locul [Rand " + std::to_string(rand + 1) +
                ", Coloana " + std::to_string(coloana + 1) +
                "] este deja ocupat!"
            );
        }
        locuri[rand][coloana] = true;
    }
    // Eliberează un loc (pentru anulare rezervare)
    void elibereazaLoc(int rand, int coloana) {
        if (!esteIndexValid(rand, coloana)) {
            throw std::out_of_range("Index invalid la eliberare loc.");
        }
        locuri[rand][coloana] = false;
    }

    // Afișează harta sălii
    void afiseazaLocuri() const {
        std::cout << "\n  Sala: " << nume
            << " (" << randuri << " randuri x " << coloane << " coloane)\n";
        std::cout << "  [ L ] = Liber   [ X ] = Ocupat\n\n";

        // Header coloane
        std::cout << "        ";
        for (int c = 0; c < coloane; ++c) {
            std::cout << std::setw(4) << (c + 1);
        }
        std::cout << "\n";

        std::cout << "        ";
        for (int c = 0; c < coloane; ++c) {
            std::cout << "----";
        }
        std::cout << "\n";

        for (int r = 0; r < randuri; ++r) {
            std::cout << "  Rand " << std::setw(2) << (r + 1) << " |";
            for (int c = 0; c < coloane; ++c) {
                std::cout << std::setw(3) << (locuri[r][c] ? "[X]" : "[L]") << " ";
            }
            std::cout << "\n";
        }

        // Statistici
        int ocupate = 0;
        for (auto& rand : locuri)
            for (bool loc : rand)
                if (loc) ocupate++;

        std::cout << "\n  Total locuri: " << (randuri * coloane)
            << " | Ocupate: " << ocupate
            << " | Libere: " << (randuri * coloane - ocupate) << "\n";
    }

    // Afișează doar locurile libere
    void afiseazaLocuriLibere() const {
        std::cout << "\n  Locuri LIBERE in sala '" << nume << "':\n  ";
        bool gasit = false;
        for (int r = 0; r < randuri; ++r) {
            for (int c = 0; c < coloane; ++c) {
                if (!locuri[r][c]) {
                    std::cout << "[R" << (r + 1) << "C" << (c + 1) << "] ";
                    gasit = true;
                }
            }
        }
        if (!gasit) std::cout << "(niciun loc liber)";
        std::cout << "\n";
    }
};



