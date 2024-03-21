#ifndef ENCYCLOPEDIAINDEX_H_INCLUDED
#define ENCYCLOPEDIAINDEX_H_INCLUDED

#include <map>
#include <string>

#include "beingindex.h"
#include "sovereigntyindex.h"
#include "placeindex.h"
#include "inventoryindex.h"

const std::map<int, std::string>encyclopediaLeykinLore =
{
    {ANCESTRY_GENERAL, "Leykin are creatures capable of traversing the leylines that thread the Bottled World's domains together. Their ancestors emerged from veins of sacred earth to inherit the ruins of cities too grand even for all their number. Yet, the day will come that the Leykin outgrow this Bottled World, returning to clay to be sculpted anew once more."},

    {ANCESTRY_VERIT, "Individualists who prize their personal philosophies above law or tradition. Although the well-travelled among them quickly adapt to the customs of foreign lands, Verit are often seen as self-righteous and disruptive by other Leykin."},
    {ANCESTRY_YETI, "Stout-hearted adherents to a creed of fraternity built on self-sacrifice. Every year, Yeti congregate in the holy city of Verse to reaffirm its tenents."},
    {ANCESTRY_MAKHI, "Descendents and worshippers of the technological civilization Makhia. They enjoy sleeping in the sun while hirelings toil, and spare no expense or cunning to attract capable candidates to their service."},
    {ANCESTRY_BEYU, "Beyu society is regimented to a fault, but still makes ample time for leisure. Their streamlined bodies propel them gracefully through and against the currents of the Thousand Isles."},
    {ANCESTRY_MESERA, "A long-lived people who emerge from Hathsera in great numbers every twelve years to spread its seeds. All the world's forests are in fact Hathsera's descendents."},
    {ANCESTRY_ORDON, "The few Ordon who venture out of ashen V'ordozaal carry with them tools of surpassing quality, lending much to their reputation as artificers."},
    {ANCESTRY_HAPHAE, "Inquisitive but ever-forgetful, the adventurous Hapahae descend from their unchanging mountain villages in pursuit of experiences worth remembering."}
};

const std::map<int, std::string>encyclopediaFactionLore =
{
    {SOV_NULL, "This area is not recognized as soverign territory."},
    {SOV_VERUS,"The Republic of Verus is symbolically overseen by a parliament of academics responsible for updating the 'Annual Consensus of Philosophy'. This monolithic, self-contradictory text is a survey of national ideals as voted upon by citizens, and serves as a means for individuals to compare the strength of personal beliefs against the norm. The Consensus regularly conflates moral and physical principles as a matter of style, acknowledging that all understanding can be suborned to the preservation of the Republic's incredibly diverse society. Because the Consensus acts as a standard for discourse, citizens can involve themselves in civic life simply by airing their opinions, the most agreeable of which will invariably become reflected in national writ."},
    {SOV_SHARUMNIR, "Sharumnir Assembly represents the secular leadership of its territories. Its laws are few and succinct, concerned with minimums that every citizen is expected to surpass. Though rarely called for, Sharumnir's justice widely engages community support for the counsel and reconciliation of offenders to victims. /// Sharmunir's religious mission is led by the Apostles, chosen messengers who travel between Yeti communities at home and abroad to deliver sermons of encouragement. The Apostles have no formal powers, but are revered as exemplary practitioners of The Creed."},
    {SOV_XENIA, "Xenia is a desert kingdom occupying the domains of the lost technological civilization Makhia, from whom the present-day Makhii claim descent. Power is exercised through the Four Corners, magi-mechanical thrones that greatly extended their occupants' lifespan. Because the thrones select capable leaders and reject them "},
    {SOV_THOUSAND_ISLES,"The Convocation of The Thousand Isles was originally an economic alliance between the Beyu island states of Reach, Karune and Yulmer, before the advent of tethercraft made "}
};

struct EncyclopediaIndex
{
    enum enumEncyclopediaCategories
    {
        EN_CAT_LEYKIN = 0,
        EN_CAT_FACTIONS = 1,
        EN_CAT_PLACES = 2,
        EN_CAT_CARGO = 3
    };

    static std::map<int,std::map<int, std::string>>encyclopedia;

    static void LoadConfigurations()
    {
        encyclopedia =
        {
            {EncyclopediaIndex::EN_CAT_LEYKIN, encyclopediaLeykinLore},
            {EncyclopediaIndex::EN_CAT_FACTIONS, encyclopediaFactionLore}
        };

        for(unsigned i = InventoryIndex::IT_MARKER_FIRST; i <= InventoryIndex::IT_MARKER_LAST; i++)
        {
            std::string section = "cargo " + std::to_string(i);
            encyclopedia[EN_CAT_CARGO][i] = Configuration::ReturnString(Configuration::cargoCfg, section.c_str(), "lore");
        }

        for(unsigned i = PlaceIndex::PL_MARKER_FIRST; i <= PlaceIndex::PL_MARKER_LAST; i++)
        {
            std::string section = "place " + std::to_string(i);
            encyclopedia[EN_CAT_PLACES][i] = Configuration::ReturnString(Configuration::placeCfg, section.c_str(), "lore");
        }
    }
};

#endif // ENCYCLOPEDIAINDEX_H_INCLUDED
