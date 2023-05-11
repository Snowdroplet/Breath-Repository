#ifndef PLACEINDEX_H_INCLUDED
#define PLACEINDEX_H_INCLUDED

#include <map>

enum enumPlaces
{
    PL_NONE = -1,

    PL_ERICENNES = 0,
    PL_CHORAS = 1,
    PL_KETH_KETHER = 2,
    PL_KETH_ENTWEIR = 3, PL_VIELLEICHT = 4, PL_QUELLUDE = 5, PL_AMBLEFORTH = 6,
    PL_ROSKANEL = 7, PL_ROSELLA = 8,
    PL_OBSERVIA = 9, PL_COLDLAKE = 10, PL_UMBERDELL = 11,
    PL_RAMSHORN = 12, PL_HOLLYHEAD = 13, PL_JASPER = 14,
    PL_RUMNIR = 15, PL_HEWNHEIM = 16, PL_ARTAS_ROCK = 17, PL_VERSE = 18,
    PL_YHANE = 19, PL_VEINS = 20, PL_XENIA = 21,
    PL_TOBANDJAN = 22, PL_QUMANTHA = 23,
    PL_MAKHIA = 24,
    PL_HAPHADEE = 25,
    PL_ASTEROS = 26,
    PL_REACH = 27,
    PL_KARUNE = 28,
    PL_HATHSERA = 29,
    PL_DOZAAL = 30,
    PL_YULMER = 31,
    PL_ETRURI = 32
};
const unsigned PL_MARKER_FIRST = PL_ERICENNES;
const unsigned PL_MARKER_LAST = PL_JASPER;

const std::map<int, std::string>placeNames =
{
  {PL_ERICENNES,"Ericennes"},
  {PL_CHORAS,"Choras"},
  {PL_KETH_KETHER,"Keth Kether"},
  {PL_KETH_ENTWEIR,"Keth Entweir"},
  {PL_VIELLEICHT,"Vielleicht"},
  {PL_QUELLUDE,"Quellude"},
  {PL_AMBLEFORTH,"Ambleforth"},
  {PL_ROSKANEL,"Roskanel"},
  {PL_ROSELLA,"Rosella"},
  {PL_OBSERVIA,"Observia"},
  {PL_COLDLAKE,"Coldlake"},
  {PL_UMBERDELL,"Umberdell"},
  {PL_RAMSHORN,"Ramshorn"},
  {PL_HOLLYHEAD,"Hollyhead"},
  {PL_JASPER,"Jasper"}

};

#endif // PLACEINDEX_H_INCLUDED
