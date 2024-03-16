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

/*
const std::map<int, std::string>encyclopediaPlaceLore =
{
    {PL_ERICENNES, "The City of Gates, capital of The Republic of Verus.\n\nEricennes has been the seat of several once-great civilizations, owing to its uniquely well-connected position on the leyways. Many of its ancient monuments still endure, warning against the follies that brought their builders to ruin."},
    {PL_CHORAS, "Countless generations of stoneshapers have carved their legacies into the grand terraces of the Canyon City, poetically dubbed the Stairway to Heaven. Its walls are steeped in age-old mysteries that the ever foward-looking Republic tend to overlook."},
    {PL_KETH_KETHER, "The Domed city, known for the colossal hemispheres that house its many automated workshops. While the domes are believed to be indestructable, Kether lacks the means to make repairs should real damage ever occur."},
    {PL_KETH_ENTWEIR, "Built atop the ruins of the Last Entweir, a bulwark against the forest's wrath once upon a time. The spirits bound to this place have since learned benevolence, but its occupants have slowly forgotten humility."},
    {PL_VIELLEICHT, "The Harbour of Many Colours, renowned for festivals that attract tourists from every corner of the world. Its title refers to a tradition of having its walls entirely repainted every three years. In some districts, "},
    {PL_QUELLUDE, "A picturesque monastary town famed for its excellent books and wine - pleasures they proclaim to be the two halves of a most cultivated life."},
    {PL_AMBLEFORTH, "A laid-back village on the seaside that lives for good food and good company. An unknown power makes it possible to breathe the clear waters at its shore, but those who follow the power out to sea are known to vanish into its depths."},
    {PL_ROSKANEL, "A fortress town founded by misguided predecessors to repel the Xenians. There is no evidence that its pristine walls have ever known war."},
    {PL_ROSELLA, "A Verit tribe of little renown makes their home on this isolated plateau overlooking the desert. Though quiet and unmaterialistic, they warmly welcome any visitors bearing news and gifts from the world below."},
    {PL_OBSERVIA, "The University and its township was purposefully founded at a distance from the capital and its concerns. Ironically, the so-called 'secret police' have a headquarters here for the same reason, but the two groups have a policy of non-interference in each other's affairs."},
    {PL_COLDLAKE, "This mining town is blanketed by chill mist from the nearby lake. Its citizens have amassed substantial wealth through honest toil, but most understandably prefer to seek their entertainments elsewhere."},
    {PL_UMBERDELL, "Inviolate accords struck with the Republic in its formative years prevents any visitor who stays three nights in the other's territory from returning home. Through this compromise, the self-sufficient Umberdell became part of the if only in name, preserving the autonomy of the former and allowing the latter to finally proclaim the unification of all Verit domains."},
    {PL_RAMSHORN, "Ramshorn borders both Lethemere and the Grazeland, stomping grounds of truly imposing beasts and the mighty hunters who dare to challenge them."},
    {PL_HOLLYHEAD, "Many visit Hollyhead for its geothermal baths reputed to confer all manner of benefit to body and mind. Not least among them are caravaneers coming to and from the icy territories of Sharumnir Assembly."},
    {PL_JASPER, "Influential despite their isolation, Jasper is a commune of artisian-mechanics who profess the highest aesthetic realization in building machines that do nothing, but elegantly. Their works are revered in distant Xenia, where travellers have made fortunes as toy peddlers."},

    {PL_RUMNIR, "Visitors to Sharumnir are freely welcomed at this snowy outpost bearing the Assembly's name. The local Yeti are quick to offer their services as guides, seeking merit and honour that outweighs any material compensation. Such is their value however, that itinerant merchants readily foist gifts upon them anyway."},
    {PL_HEWNHEIM, "Hewnheim is a subterannean city comfortably sheltered from the icy weather at its surface, save for the exposed harbour district whose workers are reputed to hold the world's toughest jobs. Recently, the Convocation of the Thousand Isles have issued decrees prohibiting its sailors from entering Hewnheim beyond the harbour for reasons yet unexplained to the baffled Assembly."},
    {PL_ARTAS_ROCK, "A mountain stronghold that has managed to harness the storms raging around it for effectively unlimited energy. Arta's Rock hosts the monthly councils of the Assembly, despite Verse making a more temperate and accessible table. The Yeti are adamant that the offices of their faith and politics remain separate."},
    {PL_VERSE, "The holy city of Sharumnir Assembly rests in the eye of a perpetual storm that rests easy for two weeks in every thirteen months. It is during these intervals that Yeti make pilgrimage to Verse to renew their faith, reconnect with family, and celebrate life."},

    {PL_YHANE, "Destroyed in a fuel storage accident fifty years ago, Yhane was rebuilt from the ground up as an opulent casino resort. Ceaseless investment of treasure and workforce by the Xenian monarchs has since repaid itself in unheard of gambling revenues and attracted hordes of skilled foreign servants to what has become the fastest-growing city in history."},
    {PL_VEINS, "A beach town under a natural cavern illuminated by countless leystone veins. Its sand has a mysterious power over plants, causing them to grow deep and strong in what ought to be an inhospitable medium. Xenia's botanists have tried avidly to replicate this effect in the open desert for ages."},
    {PL_QALAIZ, "Qaliz is a citiadel constructed to protect, study and revere the Sceptre, a towering Makhian artefact in the heart of the desert. Tresspass is autonomously prohibited by the Sceptre itself, which causes any who dare approach to vanish without a trace."},
    {PL_TOBANDJAN, "The plantations of Tobandjan are ideal for growing the hottest, sweetest spices. In a break from Xenia's usual preference for thinking labour, every step of the physically intensive cultivation is carried out by effigies."},
    {PL_QUMANTH, "Qumanth, Light-Under-Sun, is a magocractic city that prides itself on amply rewarding talent and application. Its ever-shifting servant classes outnumber the populations of most cities."},
    {PL_XENIA, "Xenia houses the Four Corners and the "},

    {PL_REACH, "Reach is an island state credited for the invention of tethercraft: self-steering ships that allow non-beyu to follow imperceptible ocean leys. This opened the gates to widespread trade and cultural exchange with the mainland, which necessitated expanding the Convocation's scope to better protect islander interests."},
    {PL_KARUNE, "<Karune>"},
    {PL_HATHSERA, "<Hathsera>"},
    {PL_VORDOZAAL, "<V'ordozaal>"},
    {PL_YULMER, "<Yulmer>"},

    {PL_MAKHIA, "<Makhia>"},
    {PL_HAPHADEE, "<Haphadee>"},
    {PL_ASTEROS, "<Asteros>"},
    {PL_ETRURI, "<Etruri>"}
};
*/

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
            //{EncyclopediaIndex::EN_CAT_PLACES, encyclopediaPlaceLore},
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
