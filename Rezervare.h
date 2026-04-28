#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "sala.h"
#include "film.h"
class Rezervare
{
private:
    static int contor;
    int idRezervare;
    std::string numeClient;
    film* Film;       // asociere cu Film
    sala* Sala;       // asociere cu Sala
    int rand;
    int coloana;

public:
    Rezervare(const std::string& numeClient, film* Film, sala* Sala, int rand, int coloana)
        : numeClient(numeClient), Film(Film), Sala(Sala), rand(rand), coloana(coloana) {
        idRezervare = ++contor;
    }

    int getId() const { return idRezervare; }
    std::string getNumeClient() const { return numeClient; }
    film* getFilm() const { return Film; }
    sala* getSala() const { return Sala; }
    int getRand() const { return rand; }
    int getColoana() const { return coloana; }

    void afiseaza() const {
        std::cout << "  ╔══════════════════════════════════════╗\n";
        std::cout << "  ║         BILET DE CINEMA              ║\n";
        std::cout << "  ╠══════════════════════════════════════╣\n";
        std::cout << "  ║ Rezervare #" << std::setw(27) << std::left << idRezervare << "║\n";
        std::cout << "  ║ Client:  " << std::setw(29) << numeClient << "║\n";
        std::cout << "  ║ Film:    " << std::setw(29) << Film->getTitlu() << "║\n";
        std::cout << "  ║ Sala:    " << std::setw(29) << Sala->getNume() << "║\n";
        std::cout << "  ║ Loc:     Rand " << std::setw(3) << (rand + 1)
            << ", Coloana " << std::setw(18) << std::left << (coloana + 1) << "║\n";
        std::cout << "  ╚══════════════════════════════════════╝\n";
    }
 
};



