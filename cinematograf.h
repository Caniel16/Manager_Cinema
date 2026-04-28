#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "sala.h"
#include "film.h"
#include "Rezervare.h"

class cinematograf

{
private:
    std::string nume;
    std::vector<film*> filme;       // agregare filme
    std::vector<sala*> sali;        // agregare sali
    std::vector<Rezervare*> rezervari;

    film* gasesteFilm(int id) const {
        for (auto f : filme)
            if (f->getId() == id) return f;
        return nullptr;
    }

    sala* gasesteSala(int id) const {
        for (auto s : sali)
            if (s->getId() == id) return s;
        return nullptr;
    }

public:
    cinematograf(const std::string& nume) : nume(nume) {}

    ~cinematograf() {
        for (auto f : filme) delete f;
        for (auto s : sali) delete s;
        for (auto r : rezervari) delete r;
    }

    // --- Gestionare filme ---
    void adaugaFilm(int id, const std::string& titlu, const std::string& gen,
        int durata, double rating) {
        filme.push_back(new film(id, titlu, gen, durata, rating));
    }

    // --- Gestionare sali ---
    void adaugaSala(int id, const std::string& numeSala, int randuri, int coloane) {
        sali.push_back(new sala(id, numeSala, randuri, coloane));
    }

    // --- Afișare filme ---
    void afiseazaFilme() const {
        std::cout << "\n========================================\n";
        std::cout << "   FILMELE DE LA: " << nume << "\n";
        std::cout << "========================================\n";
        if (filme.empty()) {
            std::cout << "  (niciun film disponibil)\n";
            return;
        }
        for (auto f : filme) {
            std::cout << "  ";
            f->afiseaza();
        }
    }

    // --- Afișare sali ---
    void afiseazaSali() const {
        std::cout << "\n  Salile disponibile:\n";
        for (auto s : sali) {
            std::cout << "  [ID " << s->getId() << "] " << s->getNume()
                << " (" << s->getRanduri() << "x" << s->getColoane() << ")\n";
        }
    }

    // --- Afișare locuri dintr-o sală ---
    void afiseazaLocuriSala(int idSala) const {
        sala* Sala = gasesteSala(idSala);
        if (!Sala) {
            std::cout << "  Sala cu ID " << idSala << " nu exista!\n";
            return;
        }
        Sala->afiseazaLocuri();
    }

    // --- Realizare rezervare ---
    Rezervare* realizeazaRezervare(const std::string& numeClient,
        int idFilm, int idSala,
        int rand, int coloana) {
        // rand și coloana sunt 1-based din input, convertim la 0-based intern
        int r = rand - 1;
        int c = coloana - 1;

        film* Film = gasesteFilm(idFilm);
        if (!Film) {
            throw std::invalid_argument(
                "Filmul cu ID " + std::to_string(idFilm) + " nu exista!"
            );
        }

        sala* Sala = gasesteSala(idSala);
        if (!Sala) {
            throw std::invalid_argument(
                "Sala cu ID " + std::to_string(idSala) + " nu exista!"
            );
        }

        // Excepțiile pentru index invalid și loc ocupat sunt aruncate de sala->rezervaLoc
        Sala->rezervaLoc(r, c);

        Rezervare* rez = new Rezervare(numeClient, Film, Sala, r, c);
        rezervari.push_back(rez);
        return rez;
    }

    // --- Anulare rezervare ---
    void anuleazaRezervare(int idRezervare) {
        for (auto it = rezervari.begin(); it != rezervari.end(); ++it) {
            if ((*it)->getId() == idRezervare) {
                (*it)->getSala()->elibereazaLoc((*it)->getRand(), (*it)->getColoana());
                std::cout << "  Rezervarea #" << idRezervare << " a fost anulata.\n";
                delete* it;
                rezervari.erase(it);
                return;
            }
        }
        throw std::invalid_argument(
            "Rezervarea cu ID " + std::to_string(idRezervare) + " nu exista!"
        );
    }

    // --- Afișare toate rezervările ---
    void afiseazaRezervari() const {
        std::cout << "\n  === REZERVARI ACTIVE (" << rezervari.size() << ") ===\n";
        if (rezervari.empty()) {
            std::cout << "  (nicio rezervare)\n";
            return;
        }
        for (auto r : rezervari) r->afiseaza();
    }


};

