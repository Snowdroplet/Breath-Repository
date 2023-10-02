#ifndef SOVEREIGNTYINDEX_H_INCLUDED
#define SOVEREIGNTYINDEX_H_INCLUDED

#include <string>
#include <map>

enum enumSoverignties
{
    SOV_NULL = 0,

    SOV_VERUS = 1,
    SOV_SHARUMNIR = 2,
    SOV_XENIA = 3,
    SOV_THOUSAND_ISLES = 4,

    SOV_VERUS_SHARUMNIR_BORDER = 5,
    SOV_VERUS_XENIA_BORDER = 6,
    SOV_VERUS_THOUSAND_ISLES_BORDER = 7,
    SOV_SHARUMNIR_THOUSAND_ISLES_BORDER = 8,
    SOV_XENIA_THOUSAND_ISLES_BORDER = 9
};

const std::map<int, std::string>sovereigntyNames =
{
    {SOV_NULL, "No sovereignty"},
    {SOV_VERUS,"Republic of Verus"}, {SOV_SHARUMNIR,"Sharumnir Assembly"}, {SOV_XENIA, "Kingdom of Xenia"}, {SOV_THOUSAND_ISLES,"Convocation of The Thousand Isles"},
    {SOV_VERUS_SHARUMNIR_BORDER, "Verus-Sharumnir Border"},
    {SOV_VERUS_XENIA_BORDER, "Verus-Xenia Border"},
    {SOV_VERUS_THOUSAND_ISLES_BORDER, "Verus-Thousand Isles Border"},
    {SOV_SHARUMNIR_THOUSAND_ISLES_BORDER, "Sharumnir-Thousand Isles Border"},
    {SOV_XENIA_THOUSAND_ISLES_BORDER, "Xenia-Thousand Isles Border"}
};


#endif // SOVEREIGNTYINDEX_H_INCLUDED
