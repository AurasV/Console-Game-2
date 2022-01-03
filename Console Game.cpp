#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <fstream>
#include <string.h>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>
/*
if (f.is_open())
        {
            while (getline(f, b)) //read entire line
                cout << b << "\n";
        }
int r = (rand() % max_number) + 1; //randomness
*/
/*
TO DO:
finish fight_action function
implement the use for player stats
make a check for levels (more exactly for when the game is done)
think of player progression when it comes to leveling up and stats increase from that
think of how enemies scale
save system
think of what's missing
*/
std::ifstream questionshungarian("questionshungarian.txt"); //file containing questions hungarian
std::ifstream questionsromanian("questionsromanian.txt"); //file containing questions romanian
std::ifstream questionsenglish("questionsenglish.txt"); //file containing questions english
std::ifstream fighthungarian("fighthungarian.txt"); //hungarian version for fights
std::ifstream fightromanian("fightromanian.txt"); //romanian version for fights
std::ifstream fightenglish("fightenglish.txt"); //english version for fights
std::ifstream hungarianstory("hungarian.txt"); //hungarian version of the story
std::ifstream romanianstory("romanian.txt"); //romanian version of the story
std::ifstream englishstory("english.txt"); //english version of the story
std::ifstream shophungarian("shophungarian.txt"); //hungarian version of the shop
std::ifstream shopromanian("shopromanian.txt"); //romanian version of the shop
std::ifstream shopenglish("shopenglish.txt"); //english version of the shop
std::ifstream menuenglish("menuenglish.txt"); //english version of the menu
std::ifstream menuromanian("menuromanian.txt"); //romanian version of the menu
std::ifstream menuhungarian("menuhungarian.txt"); //hungarian version of the menu
std::string b, first_name, last_name, c, story[100], questions[100], d, ar, fight[100],shop[100],menu[100];
int i, language, j, k, r, enemy_number, e, item_number, p, weapon_number, armor_number, death_number;
int day = 1;
char a; //player input variable
bool ok_name = false, ok_fight_first = true, ok_access_shop = false, test;
struct player //player
{
    std::string player_name = { " " }; //player name
    float ATK = { 5 }, DEF = { 5 }, THP = { 20 }, CHP = { 20 }; //player number stats
    int current_xp = { 0 }; //current xp
    int level = { 1 }; //current level
    int xp_to_next_level = { 100 };
    int current_gold = { 0 };
};
struct weapon
{
    std::string name = { " " }; //name
    float ATK = { 0 }; //atk bonus
    std::string hand = { " " }; //main / off hand
    int price = { 0 }; //price
};
struct enemy //enemies
{
    std::string enemy_name = { " " }; //enemy name
    float ATK = { 0 }, DEF = { 0 }, THP = { 0 }, CHP = { 0 }; //enemy number stats
    std::string drops = { " " }; //enemy dropped item
};
struct armor //armors
{
    std::string name = { " " }; //name
    float DEF = { 0 }; //def bonus
    std::string place = { " " }; //equip place
    int price = { 0 }; //price
};
struct item //items
{
    std::string name = { " " }; //item name  //type of bonus from the item
    int price = { 0 }; //price of the item at a store
    int number = { 0 }; //number of items inventory currently
}; 
struct equipment
{
    std::string head = { "-" }; //head name
    std::string chest = { "-" }; //chest name
    std::string pants = { "-" }; //pants name
    std::string boots = { "-" }; //boots name
    std::string mainweapon = { "-" }; //main hand weapon name
    std::string offweapon = { "-" }; //off hand weapon name
    int h_def = { 0 }; //head def
    int c_def = { 0 }; //chest def
    int p_def = { 0 }; //pants def
    int b_def = { 0 }; //boots def
    int mw_atk = { 0 }; //main hand weapon atk
    int ow_atk = { 0 }; //off hand weapon atk
    int npot_nr = { 0 }; //normal potion number
    int spot_nr = { 0 }; //superior potion number
    int upot_nr = { 0 }; //ultimate potion number
};
armor leatherh, leatherc, leatherp, leatherb, goldh, goldc, goldp, goldb, ironh, ironc, ironp, ironb, diamondh, diamondc, diamondp, diamondb, netheriteh, netheritec, netheritep, netheriteb; //armors
weapon wooden_sword, stone_sword, iron_sword, diamond_sword, netherite_sword, bow, crossbow, trident; //weapons
enemy iron_golem, zombie, skeleton, creeper, husk, current_enemy; //enemies
item iron_ingot, rotten_flesh, bone, gunpowder, normal_hp, greater_hp, supreme_hp;; //items
player pc; //player
equipment equip; //currently equipped stuff
void languagechoice(); //language choice
void read_language(char a, int& language); //read the story and the questions
void readfight(); //read all fight needed text
void readweapons(); //read all weapons
void readenemies(); //read all enemies
void readarmors(); //read all armors
void readitems(); //read all items
void playercurrentstate(player& x); //output current player state
void fight_action(enemy& current_enemy); //fight function
void fight_enemy_generate(enemy& enemy); //generate enemy function
void ico(); //input one character then clear console
void enemy_stats(enemy& x); //output enemy_stats
void weapons(weapon& x); //read weapons from file
void enemies(enemy& x); //read enemy from file
void armors(armor& x); //read armor from file
void items(item& x); //read item from file
void name(); //get the name of the character
void tests(); //tests funciton
void access_shop(); //access shop
void shop_buy(); //buying section of shop
void shop_sell(); //selling section of shop
void buy_armor(); //armor buying section of shop
void buy_weapon(); //weapon buying section of shop
void buy_health_potion(); //health potion buying section of shop
void buy_leather(); //leather armor buying section of shop
void buy_gold(); //gold armor buying section of shop
void buy_iron(); //iron armor buying section of shop
void buy_diamond(); //diamond armor buying section of shop
void buy_netherite(); //netherite armor buying section of shop
void buy_main_hand(); //main hand weapon buying section of shop
void buy_off_hand(); //off hand weapon buying section of shop
void main_menu(); //main menu
void readshop(); //shop reading function
void readfight(); //fight reading function
void readmenu(); //menu reading function
void nice_try(); //nice try function
void save_game(); //save game function
void load_game(); //load game function
void buy_armor_h(armor x);
void buy_armor_c(armor x);
void buy_armor_p(armor x);
void buy_armor_b(armor x);
void buy_main(weapon x);
void buy_off(weapon x);
void buy_hp(item& x);
void languagechoice() //language choice
{
    std::cout << "Choose a language.\nAlege limba.\nValassz nyelvet.\n\n\n1)English/Engleza/Angol\n2)Romana/Romanian/Roman\n3)Magyar/Maghiara/Hungarian\n";
    ico(); //read language option
    if (a != '1' && a != '2' && a != '3')
    {
        std::cout << "Incorrect input, please try again:/Intrare incorecta, te rog incearca din nou:/Hiba, kerlek probald ujra:" << "\n"; //incorrect input for the language choice
        languagechoice();
    }
}
void read_language(char a, int& language) //read the story and the questions
{
    switch (a)
    {
    case '1': //if language is english
        if (englishstory.is_open()) //check if the file is open
        {
            while (getline(englishstory, b)) //read line and store in b
            {
                i++; //increase the number for the line of the story string
                story[i] = b; //add the line to the story string
            }
        }
        if (questionsenglish.is_open()) //check if the file is open
            while (getline(questionsenglish, b)) //read line and store in b
            {
                j++; //increase the number for the line of the questions string
                questions[j] = b; //add the line to the questions string
            }
        language = 1;
        break;
    case '2': //if language is romanian
        if (romanianstory.is_open()) //check if the file is open
        {
            while (getline(romanianstory, b)) //read line and store in b
            {
                i++; //increase the number for the line of the story string
                story[i] = b; //add the line to the story string
            }
        }
        if (questionsromanian.is_open()) //check if the file is open
            while (getline(questionsromanian, b)) //read line and store in b
            {
                j++; //increase the number for the line of the questions string
                questions[j] = b; //add the line to the questions string
            }
        language = 2;
        break;
    case '3': //if language is hungarian
        if (hungarianstory.is_open()) //check if the file is open
        {
            while (getline(hungarianstory, b)) //read line and store in b
            {
                i++; //increase the number for the line of the story string
                story[i] = b; //add the line to the story string
            }
        }
        if (questionshungarian.is_open()) //check if the file is open
            while (getline(questionshungarian, b)) //read line and store in b
            {
                j++; //increase the number for the line of the questions string
                questions[j] = b; //add the line to the questions string
            }
        language = 3;
        break;
    }
    englishstory.close(); //close english version of file
    romanianstory.close(); //close romanian version of file
    hungarianstory.close(); //close hungarian version of file
    questionsenglish.close(); //close english version of file
    questionsromanian.close(); //close romanian version of file
    questionshungarian.close(); //close hungarian version of file
}
void readweapons()
{
    weapons(wooden_sword); //read wooden sword
    weapons(stone_sword); //read stone sword
    weapons(iron_sword); //read iron sword
    weapons(diamond_sword); //read diamond sword
    weapons(netherite_sword); //read netherite sword
    weapons(bow); //read bow
    weapons(crossbow); //read crossbow
    weapons(trident); //read trident
}
void readenemies() //read all enemies
{
    enemies(iron_golem); //read iron golem
    enemies(zombie); //read zombie
    enemies(skeleton); //read skeleton
    enemies(creeper); //read creeper
    enemies(husk); //read husk
}
void readarmors() //read all armors
{
    armors(leatherh); //read leather helmet
    armors(leatherc); //read leather chestplate
    armors(leatherp); //read leather pants
    armors(leatherb); //read leather boots
    armors(goldh); //read gold helmet
    armors(goldc); //read gold chestplate
    armors(goldp); //read gold pants
    armors(goldb); //read gold boots
    armors(ironh); //read iron helmet
    armors(ironc); //read iron chestplate
    armors(ironp); //read iron pants
    armors(ironb); //read iron boots
    armors(diamondh); //read diamond helmet
    armors(diamondc); //read diamond chestplate
    armors(diamondp); //read diamond pants
    armors(diamondb); //read diamond boots
    armors(netheriteh); //read netherite helmet
    armors(netheritec); //read netherite chestplate
    armors(netheritep); //read netherite pants
    armors(netheriteb); //read netherite boots
}
void readitems() //read all items
{
    items(iron_ingot); // read iron ingot
    items(rotten_flesh); //read rotten flesh
    items(bone); //read bone
    items(gunpowder); //read gunpowder
    items(normal_hp); //read normal health potion
    items(greater_hp); //read greater health potion
    items(supreme_hp); //read supreme health potion
}
void readfight()
{
    i = 1;
    switch (language) 
    {
    case 1: //if language is english
        if (fightenglish.is_open()) //check if file is open
            while (getline(fightenglish, b)) //read line and store in b
            {
                fight[i] = b; //add the line to the fight string
                i++; //increase the number for the line of the fight string
            }
        break;
    case 2: //if language is romanian
        while (getline(fightromanian, b)) //read line and store in b
        {
            fight[i] = b; //add the line to the fight string
            i++; //increase the number for the line of the fight string
        }
        break;
    case 3: //if language is hungarian
        while (getline(fighthungarian, b)) //read line and store in b
        {
            fight[i] = b; //add the line to the fight string
            i++; //increase the number for the line of the fight string
        }
        break;
    }
    fightenglish.close(); //close english version of file
    fightromanian.close(); //close romanian version of file
    fighthungarian.close(); //close hungarian version of file
}
void readshop()
{
    i = 1;
    if (language == 1) //if language is english
        if (shopenglish.is_open()) //check if file is open
        {
            while (getline(shopenglish, b)) //read line and store in b
            {
                shop[i] = b; //add the line to the shop string
                i++; //increase the number for the line of the shop string
            }
        }
    if (language == 2) //if language is romanian
        if (shopromanian.is_open()) //check if file is open
        {
            while (getline(shopromanian, b)) //read line and store in b
            {
                shop[i] = b; //add the line to the shop string
                i++; //increase the number for the line of the shop string
            }
        }
    if (language == 3) //if language is hungarian
        if (shophungarian.is_open()) //check if file is open
        {
            while (getline(shophungarian, b)) //read line and store in b
            {
                shop[i] = b; //add the line to the shop string
                i++; //increase the number for the line of the shop string
            }
        }
    shopenglish.close(); //close english version of file
    shopromanian.close(); //close romanian version of file
    shophungarian.close(); //close hungarian version of file
}
void readmenu()
{
    i = 1;
    switch (language)
    {
    case 1:
        if (menuenglish.is_open()) //check if file is open
        {
            while (getline(menuenglish, b)) //read line and store in b
            {
                menu[i] = b; //add the line to the menu string
                i++; //increase the number for the line of the menu string
            }
        }
    case 2:
        if (menuromanian.is_open()) //check if file is open
        {
            while (getline(menuromanian, b)) //read line and store in b
            {
                menu[i] = b; //add the line to the menu string
                i++; //increase the number for the line of the menu string
            }
        }
    case 3:
        if (menuhungarian.is_open()) //check if file is open
        {
            while (getline(menuhungarian, b)) //read line and store in b
            {
                menu[i] = b; //add the line to the menu string
                i++; //increase the number for the line of the menu string
            }
        }
    }
    menuenglish.close(); //close english file
    menuromanian.close(); //close romanian file
    menuhungarian.close(); //close hungarian file
}
void access_shop()
{
    for (int shop_counter = 1; shop_counter <= 6; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico(); //read shop action
    switch (a)
    {
    case '1': //if answer is buy
        shop_buy(); 
        break;
    case '2': //if answer is sell
        shop_sell(); 
        break;
    case '0': //exit
        main_menu();
        std::cout << "\n";
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        access_shop();
        break;
    }
}
void shop_buy()
{
    for (int shop_counter = 7; shop_counter <= 11; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico(); //read action
    switch (a)
    {
    case '1': //if answer is buy armors
        buy_armor();
        break;
    case '2': //if answer is buy weapons
        buy_weapon();
        break;
    case '3': //if answer is buy health potions
        buy_health_potion();
        break;
    case '0': //go back
        access_shop();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        shop_buy();
    }

}
void shop_sell()
{
    for (int shop_counter = 70; shop_counter <= 75; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1': //if answer is bone
        if (bone.number > 0)
        {
            pc.current_gold = pc.current_gold + bone.price * bone.number;
            system("CLS");
            if (language == 3)
                std::cout << bone.name << shop[80] << bone.number << "\n" << shop[81];
            else
                std::cout << shop[80] << bone.number << " " << bone.name << "\n" << shop[81];
            bone.number = 0;
            ico();
            shop_sell();
        }
        else
        {
            system("CLS");
            std::cout << shop[76] << bone.name << "\n" << shop[81];
            ico();
            shop_sell();
        }
        break;
    case '2': //if answer is rotten flesh
        if (rotten_flesh.number > 0)
        {
            pc.current_gold = pc.current_gold + rotten_flesh.price * rotten_flesh.number;
            system("CLS");
            if (language == 3)
                std::cout << rotten_flesh.name << shop[80] << rotten_flesh.number << "\n" << shop[81];
            else
                std::cout << shop[80] << rotten_flesh.number << " " << rotten_flesh.name << "\n" << shop[81];
            rotten_flesh.number = 0;
            ico();
            shop_sell();
        }
        else
        {
            system("CLS");
            std::cout << shop[76] << rotten_flesh.name << "\n" << shop[81];
            ico();
            shop_sell();
        }
        break;
    case '3': //if answer is iron ingot
        if (iron_ingot.number > 0)
        {
            pc.current_gold = pc.current_gold + iron_ingot.price * iron_ingot.number;
            system("CLS");
            if (language == 3)
                std::cout << iron_ingot.name << shop[80] << iron_ingot.number << "\n" << shop[81];
            else 
                std::cout << shop[80] << iron_ingot.number << " " << iron_ingot.name << "\n" << shop[81];
            iron_ingot.number = 0;
            ico();
            shop_sell();
        }
        else
        {
            system("CLS");
            std::cout << shop[76] << iron_ingot.name << "\n" << shop[81];
            ico();
            shop_sell();
        }
        break;
    case '4': //if answer is gunpowder
        if (gunpowder.number > 0)
        {
            pc.current_gold = pc.current_gold + gunpowder.price * gunpowder.number;
            system("CLS");
            if (language == 3)
                std::cout << gunpowder.name << shop[80] << gunpowder.number << "\n" << shop[81];
            else
                std::cout << shop[80] << gunpowder.number << " " << gunpowder.name << "\n" << shop[81];
            gunpowder.number = 0;
            ico();
            shop_sell();
        }
        else
        {
            system("CLS");
            std::cout << shop[76] << gunpowder.name << "\n" << shop[81];
            ico();
            shop_sell();
        }
        break;
    case '0': //go back
        access_shop();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        shop_sell();
        break;
    }
}
void buy_armor()
{
    for (int shop_counter = 12; shop_counter <= 18; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':  //if answer is leather armor
        buy_leather();
        break;
    case '2': //if answer is gold armor
        buy_gold();
        break;
    case '3': //if answer is iron armor
        buy_iron();
        break;
    case '4': //if answer is diamond armor
        buy_diamond();
        break;
    case '5': //if answer is netherite armor
        buy_netherite();
        break;
    case '0': //go back
        shop_buy();
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_armor();
    }
}
void buy_leather()
{
    for (int shop_counter = 19; shop_counter <= 24; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1': //if answer is helmet
        buy_armor_h(leatherh);
        break;
    case '2': //if answer is chestplate
        buy_armor_c(leatherc);
        break;
    case '3': //if answer is pants
        buy_armor_p(leatherp);
        break;
    case '4': //if answer is boots
        buy_armor_b(leatherb);
        break;
    case '0': //go back
        buy_armor();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_leather();
        break;
    }
}
void buy_gold()
{
    for (int shop_counter = 25; shop_counter <= 30; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1': //if answer is helmet
        buy_armor_h(goldh);
        break;
    case '2': //if answer is chestplate
        buy_armor_c(goldc);
        break;
    case '3': //if answer is pants
        buy_armor_p(goldp);
        break;
    case '4': //if answer is boots
        buy_armor_b(goldb);
        break;
    case '0': //go back
        buy_armor();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_gold();
        break;
    }
}
void buy_iron()
{
    for (int shop_counter = 31; shop_counter <= 36; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1': //if answer is helmet
        buy_armor_h(ironh);
        break;
    case '2': //if answer is chestplate
        buy_armor_c(ironc);
        break;
    case '3': //if answer is pants
        buy_armor_p(ironp);
        break;
    case '4': //if answer is boots
        buy_armor_b(ironb);
        break;
    case '0': //go back
        buy_armor();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_iron();
        break;
    }
}
void buy_diamond()
{
    for (int shop_counter = 37; shop_counter <= 42; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':  //if answer is helmet
        buy_armor_h(diamondh);
        break;
    case '2':  //if answer is chestplate
        buy_armor_c(diamondc);
        break;
    case '3': //if answer is pants
        buy_armor_p(diamondp);
        break;
    case '4': //if answer is boots
        buy_armor_b(diamondb);
        break;
    case '0': //go back
        buy_armor();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_diamond();
        break;
    }
}
void buy_netherite()
{
    for (int shop_counter = 43; shop_counter <= 48; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1': //if answer is helmet
        buy_armor_h(netheriteh);
        break;
    case '2': //if answer is chestplate
        buy_armor_c(netheritec);
        break;
    case '3': //if answer is pants
        buy_armor_p(netheritep);
        break;
    case '4': //if answer is boots
        buy_armor_b(netheriteb);
        break;
    case '0': //go back
        buy_armor();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_netherite();
        break;
    }
}
void buy_weapon()
{
    for (int shop_counter = 49; shop_counter <= 52; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1': //if answer is main hand
        buy_main_hand();
        break;
    case '2': //if answer is off hand
        buy_off_hand();
        break;
    case '0': //go back
        shop_buy();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_weapon();
        break;
    }

}
void buy_main_hand()
{
    for (int shop_counter = 53; shop_counter <= 59; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1': //if answer is wooden sword
        buy_main(wooden_sword);
        break;
    case '2': //if answer is stone sword
        buy_main(stone_sword);
        break;
    case '3': //if answer is iron sword
        buy_main(iron_sword);
        break;
    case '4': //if answer is diamond sword
        buy_main(diamond_sword);
        break;
    case '5': //if answer is netherite sword
        buy_main(netherite_sword);
        break;
    case '0': //go back
        buy_weapon();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_main_hand();
        break;
    }
}
void buy_off_hand()
{
    for (int shop_counter = 60; shop_counter <= 64; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico(); //read player's choice
    switch (a)
    {
    case '1': //if the answer is bow
        buy_off(bow);
        break;
    case '2': //if the answer is crossbow
        buy_off(crossbow);
        break;
    case '3': //if the answer is trident
        buy_off(trident);
        break;
    case '0': //go back
        buy_weapon();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_off_hand();
        break;
    }

}
void buy_health_potion() //buy health potion
{
    for (int shop_counter = 65; shop_counter <= 69; shop_counter++)
        std::cout << shop[shop_counter] << "\n"; //output shop text
    ico();
    switch (a)
    {
    case '1':
        buy_hp(normal_hp);
        break;
    case '2':
        buy_hp(greater_hp);
        break;
    case '3':
        buy_hp(supreme_hp);
    case '0':
        shop_buy(); //go back
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        buy_health_potion();
        break;
    }
}
void fight_action(enemy& current_enemy)
{
    if (ok_fight_first == true)
        std::cout << fight[1] << " " << current_enemy.enemy_name; //you've been attacked by on the first run
    else std::cout << fight[2] << " " << current_enemy.enemy_name; //you're currently fighting on the subsequent ones
}
//have to finish this ^
void fight_enemy_generate(enemy& current_enemy) //generate enemy
{
    int r = (rand() % 100) + 1; //get random number
    if (r <= 32)
        current_enemy = zombie; //32% chance of zombie
    if (r > 32 && r <= 64)
        current_enemy = skeleton; //32% chance of zombie
    if (r > 64 && r <= 96)
        current_enemy = husk; //32% chance of husk
    if (r > 96 && r <= 98)
        current_enemy = creeper; //2% chance of creeper
    if (r > 98 && r <= 100)
        current_enemy = iron_golem; //2% chance of iron_golem
}
void playercurrentstate(player& x) //output current player state
{
    int equip_def = equip.h_def + equip.c_def + equip.p_def + equip.b_def;
    int equip_atk = equip.mw_atk + equip.ow_atk;
    system("CLS");
    p = pc.player_name.length() - 1; //i dont really remember why this is here
    switch (language)
    {
    case 1: //if the language is english
        if (pc.player_name[p] == 's') //special case because english is a special language
            std::cout << pc.player_name << char(39) << " current stats are:\nAttack: " << pc.ATK + equip_atk << "\nDefense: " << pc.DEF + equip_def << "\nTotal Health Point: " << pc.THP << "\nCurrent Health Points: " << pc.CHP << "\nLevel: " << pc.level << "\nGold: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP Until Level Up: " << pc.xp_to_next_level - pc.current_xp << "\n" << "Helmet: " << equip.head << "\n" << "Chestplate: " << equip.chest << "\n" << "Pants: " << equip.pants << "\n" << "Boots: " << equip.boots << "\n"; //if the last letter is s
        else
            std::cout << pc.player_name << char(39) << "s current stats are:\nAttack: " << pc.ATK + equip_atk << "\nDefense: " << pc.DEF + equip_def << "\nTotal Health Point: " << pc.THP << "\nCurrent Health Points: " << pc.CHP << "\nLevel: " << pc.level << "\nGold: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP Until Level Up: " << pc.xp_to_next_level - pc.current_xp << "\n" << "Helmet: " << equip.head << "\n" << "Chestplate: " << equip.chest << "\n" << "Pants: " << equip.pants << "\n" << "Boots: " << equip.boots << "\n"; //if the last letter isn't s
        std::cout << shop[81];
        break;
    case 2: //if the language is romanian
        std::cout << "Statisticile Curente pentru " << pc.player_name << " sunt:\n" << "Atac: " << pc.ATK + equip_atk << "\nAparare: " << pc.DEF + equip_def << "\nPuncte de Viata Totale: " << pc.THP << "\nPuncte de Viata Curente: " << pc.CHP << "\nNivel: " << pc.level << "\nAur: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP Pana la Cresterea Nivelului: " << pc.xp_to_next_level - pc.current_xp << "\n" << "Casca: " << equip.head << "\n" << "Platosa: " << equip.chest << "\n" << "Jambiere: " << equip.pants << "\n" << "Cizme: " << equip.boots << "\n"; //if the language is romanian
        std::cout << shop[81];
        break;
    case 3: //if the language is hungarian
        std::cout << "Jelenlegi statisztikak " << pc.player_name << ":\n" << "Tamadas : " << pc.ATK + equip_atk << "\nVedekezes: " << pc.DEF + equip_def << "\nAz osszes eletero: " << pc.THP << "\nJelenlegi eletero: " << pc.CHP << "\nSzint: " << pc.level << "\nArany: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP szukseges a szint lepeshez: " << pc.xp_to_next_level - pc.current_xp << "\n" << "Sisak: " << equip.head << "\n" << "Pancel: " << equip.chest << "\n" << "Nadrag: " << equip.pants << "\n" << "Csizma: " << equip.boots << "\n"; //if the language is hungarian
        std::cout << shop[81];
        break;
    }
    ico();
    main_menu();
}
void enemy_stats(enemy& x) //output enemy stats
{
    //system("CLS");
    switch (language)
    {
    case 1: //if the language is english
        std::cout << "Name: " << x.enemy_name << "\n" << "Attack: " << x.ATK << "\n" << "Defense: " << x.DEF << "\n" << "Total Health Points: " << x.THP << "\n" << "Current Health Points: " << x.CHP << "\n" << "Drops: " << x.drops; // output enemy stats and drops
        break;
    case 2: //if the language is romanian
        std::cout << "Nume: " << x.enemy_name << "\n" << "Atac: " << x.ATK << "\n" << "Aparare: " << x.DEF << "\n" << "Puncte Viata Totale: " << x.THP << "\n" << "Puncte Viata Curente: " << x.CHP << "\n" << "Drop-uri: " << x.drops; // output enemy stats and drops
        break;
    case 3: //if the language is hungarian
        std::cout << "Nev: " << x.enemy_name << "\n" << "Tamadas: " << x.ATK << "\n" << "Vedekezes: " << x.DEF << "\n" << "Az osszes eletero: " << x.THP << "\n" << "Jelenlegi eletero: " << x.CHP << "\n" << "Eszkozoket: " << x.drops; // output enemy stats and drops
        break;
    }
        std::cout << "\n" << "\n";
}
//have to add the clear console here and finish it after fight functions are done ^
void weapons(weapon& x) //read weapon from file
{
    std::ifstream weaponstxt("weapons.txt");
    for (e = 1; e <= weapon_number; e++)
        std::getline(weaponstxt, b); //skip unnecessary lines
    std::getline(weaponstxt, b); //getting line
    switch (language)
    {
    case 1: //if the language is english
        x.name = b; //weapon name
        std::getline(weaponstxt, b);
        std::getline(weaponstxt, b);
        break;
    case 2: //if the language is romanian
        std::getline(weaponstxt, b);
        x.name = b; //weapon name
        std::getline(weaponstxt, b);
        break;
    case 3: //if the language is hungarian
        getline(weaponstxt, b);
        getline(weaponstxt, b);
        x.name = b; //weapon name
        break;
    }
    getline(weaponstxt, b); //get the hand for the weapon
    x.hand = b; //save weapon hand
    weaponstxt >> x.ATK; //read weapon atk stat
    weaponstxt >> x.price;
    weapon_number += 6; //increase to get to next weapon
    weaponstxt.close(); //close weapon file
}
void enemies(enemy& x) //read enemy from file
{
    std::ifstream enemies("enemies.txt"); //file containing enemy stats and names
    for (e = 1; e <= enemy_number; e++)
        std::getline(enemies, b); //skip unncessary lines
    std::getline(enemies, d); //getting line
    x.enemy_name = d; //enemy name 
    std::getline(enemies, d); //getting line
    switch (language)
    {
    case 1: //if the language is english
        x.drops = d; //enemy drops
        std::getline(enemies, d);
        std::getline(enemies, d);
        break;
    case 2: //if the language is romanian
        std::getline(enemies, d);
        x.drops = d; //enemy drops
        std::getline(enemies, d);
        break;
    case 3: //if the language is hungarian
        std::getline(enemies, d);
        std::getline(enemies, d);
        x.drops = d; //enemy drops
        break;
    }
    enemies >> x.ATK >> x.DEF >> x.THP >> x.CHP; //reading the number stats from file
    enemy_number = enemy_number + 8; //increase to get to next enemy
    enemies.close(); //close enemy file
}
void armors(armor& x) //read armor from file
{
    std::ifstream armortxt("armor.txt"); //file containg armor stats names and placement
    for (e = 1; e <= armor_number; e++)
        std::getline(armortxt, ar); //skip unnecessary lines
    std::getline(armortxt, ar);
    switch (language)
    {
    case 1: //if the language is english
        x.name = ar; //armor name
        std::getline(armortxt, ar);
        std::getline(armortxt, ar);
        break;
    case 2: //if the language is romanian
        std::getline(armortxt, ar);
        x.name = ar; //armor name
        std::getline(armortxt, ar);
        break;
    case 3: //if the language is hungarian
        std::getline(armortxt, ar);
        std::getline(armortxt, ar);
        x.name = ar; //armor name
        break;
    }
    std::getline(armortxt, ar); //ger armor place
    x.place = ar; //save armor place
    armortxt >> x.DEF; //save armor def
    armortxt >> x.price;
    armor_number += 6; //increase to get to next armor piece
    armortxt.close(); //close armor file
}
void items(item& x) //read item from file
{
    std::ifstream items("items.txt"); //items file
    for (e = 1; e <= item_number; e++)
        std::getline(items, b); //skip unneccessary lines
    std::getline(items, b); //get first important line
    switch (language)
    {
    case 1: //if language is english
        x.name = b; //item name
        std::getline(items, b);
        std::getline(items, b);
        break;
    case 2: //if language is romanian
        std::getline(items, b);
        x.name = b; //item name
        std::getline(items, b);
        break;
    case 3: //if language is hungarian
        std::getline(items, b);
        std::getline(items, b);
        x.name = b; //item name
        break;
    }
    items >> x.price; //get the price of item
    item_number += 4; //increase to get the next item
    items.close(); //close items file
}
void name() //get the name of the character
{
    if (ok_name != true) //first time run test
        std::cout << story[1] << "\n"; //ask for name
    else //if the input was incorrect last time
    {
        std::cout << "Incorrect Input. Please try again" << "\n";
        std::cout << story[1] << "\n";
    }
    std::getline(std::cin, pc.player_name); //read name
    system("CLS");
    std::cout << questions[1] << " " << char(39) << pc.player_name << char(39) << " " << questions[2] << "\n\n" << questions[3] << "\n" << questions[4] << "\n"; //ask if the name is correct
    ico(); //read the answer
    if (a == '2') //check if the name is correct
    {
        ok_name = false; //reset ok for acknowledged incorrecst name
        name(); //redo name input if the name is incorrect
    }
    if (a != '2' && a != '1') //check if the input is correct
    {
        ok_name = true;
        name();
    }
}
void ico() //input one character then clear console
{
    a = _getch(); //read one character user input
    system("CLS"); //clear console
}
void tests()
{
    std::cout << "Items: " << "\n";
    std::cout << iron_ingot.name << "\n" << iron_ingot.price << "\n";
    std::cout << bone.name << "\n" << bone.price << "\n";
    std::cout << rotten_flesh.name << "\n" << rotten_flesh.price << "\n";
    std::cout << gunpowder.name << "\n" << gunpowder.price << "\n";
    std::cout << normal_hp.name << "\n" << normal_hp.price << "\n";
    std::cout << greater_hp.name << "\n" << greater_hp.price << "\n";
    std::cout << supreme_hp.name << "\n" << supreme_hp.price << "\n";
    std::cout << "\n" << "Weapons: " << "\n";
    std::cout << wooden_sword.name << "\n" << wooden_sword.ATK << "\n" << wooden_sword.hand << "\n" << wooden_sword.price << "\n";
    std::cout << stone_sword.name << "\n" << stone_sword.ATK << "\n" << stone_sword.hand << "\n" << stone_sword.price << "\n";
    std::cout << iron_sword.name << "\n" << iron_sword.ATK << "\n" << iron_sword.hand << "\n" << iron_sword.price << "\n";
    std::cout << diamond_sword.name << "\n" << diamond_sword.ATK << "\n" << diamond_sword.hand << "\n" << diamond_sword.price << "\n";
    std::cout << netherite_sword.name << "\n" << netherite_sword.ATK << "\n" << netherite_sword.hand << "\n" << netherite_sword.price << "\n";
    std::cout << bow.name << "\n" << bow.ATK << "\n" << bow.hand << "\n" << bow.price << "\n";
    std::cout << crossbow.name << "\n" << crossbow.ATK << "\n" << crossbow.hand << "\n" << crossbow.price << "\n";
    std::cout << trident.name << "\n" << trident.ATK << "\n" << trident.hand << "\n" <<trident.price << "\n";
    std::cout << "\n" << "Armors: " << "\n";
    std::cout << leatherh.name << "\n" << leatherh.DEF << "\n" << leatherh.place << "\n" << leatherh.price << "\n";
    std::cout << leatherc.name << "\n" << leatherc.DEF << "\n" << leatherc.place << "\n" << leatherc.price << "\n";
    std::cout << leatherp.name << "\n" << leatherp.DEF << "\n" << leatherp.place << "\n" << leatherp.price << "\n";
    std::cout << leatherb.name << "\n" << leatherb.DEF << "\n" << leatherb.place << "\n" << leatherb.price << "\n";
    std::cout << goldh.name << "\n" << goldh.DEF << "\n" << goldh.place << "\n" << goldh.price << "\n";
    std::cout << goldc.name << "\n" << goldc.DEF << "\n" << goldc.place << "\n" << goldc.price << "\n";
    std::cout << goldp.name << "\n" << goldp.DEF << "\n" << goldp.place << "\n" << goldp.price << "\n";
    std::cout << goldb.name << "\n" << goldb.DEF << "\n" << goldb.place << "\n" << goldb.price << "\n";
    std::cout << ironh.name << "\n" << ironh.DEF << "\n" << ironh.place << "\n" << ironh.price << "\n";
    std::cout << ironc.name << "\n" << ironc.DEF << "\n" << ironc.place << "\n" << ironc.price << "\n";
    std::cout << ironp.name << "\n" << ironp.DEF << "\n" << ironp.place << "\n" << ironp.price << "\n";
    std::cout << ironb.name << "\n" << ironb.DEF << "\n" << ironb.place << "\n" << ironb.price << "\n";
    std::cout << diamondh.name << "\n" << diamondh.DEF << "\n" << diamondh.place << "\n" << diamondh.price << "\n";
    std::cout << diamondc.name << "\n" << diamondc.DEF << "\n" << diamondc.place << "\n" << diamondc.price << "\n";
    std::cout << diamondp.name << "\n" << diamondp.DEF << "\n" << diamondp.place << "\n" << diamondp.price << "\n";
    std::cout << diamondb.name << "\n" << diamondb.DEF << "\n" << diamondb.place << "\n" << diamondb.price << "\n";
    std::cout << netheriteh.name << "\n" << netheriteh.DEF << "\n" << netheriteh.place << "\n" << netheriteh.price << "\n";
    std::cout << netheritec.name << "\n" << netheritec.DEF << "\n" << netheritec.place << "\n" << netheritec.price << "\n";
    std::cout << netheritep.name << "\n" << netheritep.DEF << "\n" << netheritep.place << "\n" << netheritep.price << "\n";
    std::cout << netheriteb.name << "\n" << netheriteb.DEF << "\n" << netheriteb.place << "\n" << netheriteb.price << "\n";
    std::cout << "\n" << "Enemies:" << "\n";
    enemy_stats(skeleton);
    enemy_stats(husk);
    enemy_stats(zombie);
    enemy_stats(iron_golem);
    enemy_stats(creeper);
    playercurrentstate(pc);
}
//only a test function have to delete before final iteration ^
void main_menu() 
{
    if (language == 3)
        std::cout << day << menu[1] << "\n";
    else
        std::cout << menu[1] << day << "\n";
    for (int menu_counter = 2; menu_counter <= 9; menu_counter++)
        std::cout << menu[menu_counter] << "\n"; //output menu text
    ico();
    switch (a)
    {
    case '1': //find enemy
        fight_enemy_generate(current_enemy);
        fight_action(current_enemy);
        break;
    case '2': //shop
        access_shop();
        break;
    case '3': //go to sleep
        if (day == 2147483646)
            nice_try();
        pc.CHP = pc.THP; //restore hp
        day++; //increase day
        main_menu();
        break;
    case '4': //check status
        playercurrentstate(pc); //check status
        break;
    case '5': //save game
        save_game();
        break;
    case '6':
        load_game();
        break;
    case '0':
        std::cout << menu[10] << "\n" << questions[3] << "\n" << questions[4] << "\n";
        ico();
        if (a == '1')
        {
            system("CLS");
            std::cout << "Quitting...";
            exit(0);
        }
        else main_menu();
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        main_menu();
        break;
    }
}
void save_game()
{
    system("CLS");
    for (int i = 5; i <= 9; i++)
        std::cout << questions[i] << "\n";
    ico();
    switch (a)
    {
    case '1':
    {
        std::ifstream save;
        save.open("save1.txt");
        if (save.fail())
        {
            save.close();
            std::ofstream save("save1.txt");
            system("CLS");
            std::cout << "Saving...";
            save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number;
            system("CLS");
            std::cout << "Saved" << "\n" << shop[81];
            save.close();
        }
        else
        {
            for (int skip = 15; skip <= 17; skip++)
                std::cout << questions[skip] << "\n";
            ico();
            if (a == '1')
            {
                save.close();
                std::ofstream save("save1.txt");
                system("CLS");
                std::cout << "Saving...";
                save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number;
                system("CLS");
                std::cout << "Saved" << "\n" << shop[81];
                save.close();
            }
            else
                main_menu();
        }
        ico();
        main_menu();
        break;
    }
    case '2':
    {
        std::ifstream save;
        save.open("save2.txt");
        if (save.fail())
        {
            save.close();
            std::ofstream save("save2.txt");
            system("CLS");
            std::cout << "Saving...";
            save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number;
            system("CLS");
            std::cout << "Saved" << "\n" << shop[81];
            save.close();
        }
        else
        {
            for (int skip = 15; skip <= 17; skip++)
                std::cout << questions[skip] << "\n";
            ico();
            if (a == '1')
            {
                save.close();
                std::ofstream save("save2.txt");
                system("CLS");
                std::cout << "Saving...";
                save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number;
                system("CLS");
                std::cout << "Saved" << "\n" << shop[81];
                save.close();
            }
            else
                main_menu();
        }
        ico();
        main_menu();
        break;
    }
    case '3':
    {
        std::ifstream save;
        save.open("save3.txt");
        if (save.fail())
        {
            save.close();
            std::ofstream save("save3.txt");
            system("CLS");
            std::cout << "Saving...";
            save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number;
            system("CLS");
            std::cout << "Saved" << "\n" << shop[81];
            save.close();
        }
        else
        {
            for (int skip = 15; skip <= 17; skip++)
                std::cout << questions[skip] << "\n";
            ico();
            if (a == '1')
            {
                save.close();
                std::ofstream save("save3.txt");
                system("CLS");
                std::cout << "Saving...";
                save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number;
                system("CLS");
                std::cout << "Saved" << "\n" << shop[81];
                save.close();
            }
            else
                main_menu();
        }
        ico();
        main_menu();
        break;
    }
    case '0':
    {
        main_menu();
        break;
    }
    }
    system("CLS");
    std::cout << "Saving...";
    
}
void load_game()
{
    system("CLS");
    for (int i = 10; i <= 14; i++)
        std::cout << questions[i] << "\n";
    ico();
    system("CLS");
    switch (a)
    {
    case '1':
    {
        std::ifstream save;
        save.open("save1.txt");
        if (save.fail())
        {
            std::cout << menu[11] << "\n" << menu[12] << "\n" << shop[81];
        }
        else
        {
            std::cout << "Loading...";
            std::getline(save, b);
            pc.player_name = b;
            save >> pc.ATK >> pc.DEF >> pc.THP >> pc.CHP;
            save >> pc.level >> pc.current_gold >> pc.current_xp;
            for (int saveskip = 1; saveskip <= 9; saveskip++)
                std::getline(save, b);
            std::getline(save, b);
            b = equip.head;
            std::getline(save, b);
            b = equip.chest;
            std::getline(save, b);
            b = equip.pants;
            std::getline(save, b);
            b = equip.boots;
            save >> equip.h_def >> equip.c_def >> equip.p_def >> equip.b_def;
            save >> equip.mw_atk >> equip.ow_atk;
            save >> bone.number >> gunpowder.number >> rotten_flesh.number >> iron_ingot.number;
            save >> normal_hp.number >> greater_hp.number >> supreme_hp.number;
            system("CLS");
            std::cout << "Loaded!\n" << shop[81];
        }
        ico();
        main_menu();
        break;
    }
    case '2':
    {
        std::ifstream save;
        save.open("save2.txt");
        if (save.fail())
        {
            std::cout << menu[11] << "\n" << menu[12] << "\n" << shop[81];
        }
        else
        {
            std::cout << "Loading...";
            std::getline(save, b);
            pc.player_name = b;
            save >> pc.ATK >> pc.DEF >> pc.THP >> pc.CHP;
            save >> pc.level >> pc.current_gold >> pc.current_xp;
            for (int saveskip = 1; saveskip <= 9; saveskip++)
                std::getline(save, b);
            std::getline(save, b);
            b = equip.head;
            std::getline(save, b);
            b = equip.chest;
            std::getline(save, b);
            b = equip.pants;
            std::getline(save, b);
            b = equip.boots;
            save >> equip.h_def >> equip.c_def >> equip.p_def >> equip.b_def;
            save >> equip.mw_atk >> equip.ow_atk;
            save >> bone.number >> gunpowder.number >> rotten_flesh.number >> iron_ingot.number;
            save >> normal_hp.number >> greater_hp.number >> supreme_hp.number;
            system("CLS");
            std::cout << "Loaded!\n" << shop[81];
        }
        ico();
        main_menu();
        break;
    }
    case '3':
    {
        std::ifstream save;
        save.open("save3.txt");
        if (save.fail())
        {
            std::cout << menu[11] << "\n" << menu[12] << "\n" << shop[81];
        }
        else
        {
            std::cout << "Loading...";
            std::getline(save, b);
            pc.player_name = b;
            save >> pc.ATK >> pc.DEF >> pc.THP >> pc.CHP;
            save >> pc.level >> pc.current_gold >> pc.current_xp;
            for (int saveskip = 1; saveskip <= 9; saveskip++)
                std::getline(save, b);
            std::getline(save, b);
            b = equip.head;
            std::getline(save, b);
            b = equip.chest;
            std::getline(save, b);
            b = equip.pants;
            std::getline(save, b);
            b = equip.boots;
            save >> equip.h_def >> equip.c_def >> equip.p_def >> equip.b_def;
            save >> equip.mw_atk >> equip.ow_atk;
            save >> bone.number >> gunpowder.number >> rotten_flesh.number >> iron_ingot.number;
            save >> normal_hp.number >> greater_hp.number >> supreme_hp.number;
            system("CLS");
            std::cout << "Loaded!\n" << shop[81];
        }
        ico();
        main_menu();
        break;
    }
    case '0':
    {
        main_menu();
        break;
    }
    }
}
void nice_try()
{
    std::cout << "Nice try! The game will now close";
    ico();
    exit(0);
}
void buy_armor_h(armor x) //buy helmet function
{
    if (pc.current_gold >= x.price && x.DEF > equip.h_def)
    {
        pc.current_gold = pc.current_gold - x.price;
        equip.h_def = x.DEF;
        equip.head = x.name;
        system("CLS");
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_armor();
    }
    else
    {
        if (pc.current_gold < x.price)
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_armor();
        }
        else
        {
            system("CLS");
            std::cout << shop[83] << "\n" << shop[81];
            ico();
            buy_armor();
        }
    }
}
void buy_armor_c(armor x) //buy chestplate function
{
    if (pc.current_gold >= x.price && x.DEF > equip.c_def)
    {
        pc.current_gold = pc.current_gold - x.price;
        equip.c_def = x.DEF;
        equip.chest = x.name;
        system("CLS");
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_armor();
    }
    else
    {
        if (pc.current_gold < x.price)
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_armor();
        }
        else
        {
            system("CLS");
            std::cout << shop[83] << "\n" << shop[81];
            ico();
            buy_armor();
        }
    }
}
void buy_armor_p(armor x) //buy pants function
{
    if (pc.current_gold >= x.price && x.DEF > equip.p_def)
    {
        pc.current_gold = pc.current_gold - x.price;
        equip.p_def = x.DEF;
        equip.pants = x.name;
        system("CLS");
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_armor();
    }
    else
    {
        if (pc.current_gold < x.price)
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_armor();
        }
        else
        {
            system("CLS");
            std::cout << shop[83] << "\n" << shop[81];
            ico();
            buy_armor();
        }
    }
}
void buy_armor_b(armor x) //buy boots function
{
    if (pc.current_gold >= x.price && x.DEF > equip.b_def)
    {
        pc.current_gold = pc.current_gold - x.price;
        equip.b_def = x.DEF;
        equip.boots = x.name;
        system("CLS");
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_armor();
    }
    else
    {
        if (pc.current_gold < x.price)
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_armor();
        }
        else
        {
            system("CLS");
            std::cout << shop[83] << "\n" << shop[81];
            ico();
            buy_armor();
        }
    }
}
void buy_main(weapon x)
{
    if (pc.current_gold >= x.price && x.ATK > equip.mw_atk)
    {
        pc.current_gold = pc.current_gold - x.price;
        equip.mw_atk = x.ATK;
        equip.mainweapon = x.name;
        system("CLS");
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_main_hand();
    }
    else
    {
        if (pc.current_gold < x.price)
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_main_hand();
        }
        else
        {
            system("CLS");
            std::cout << shop[84] << "\n" << shop[81];
            ico();
            buy_main_hand();
        }
    }
}
void buy_off(weapon x)
{
    if (pc.current_gold >= x.price && x.ATK > equip.ow_atk)
    {
        pc.current_gold = pc.current_gold - x.price;
        equip.ow_atk = x.ATK;
        equip.offweapon = x.name;
        system("CLS");
        std::cout << shop[82] << x.name << shop[81];
        ico();
        buy_off_hand();
    }
    else
    {
        if (pc.current_gold < x.price)
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_off_hand();
        }
        else
        {
            system("CLS");
            std::cout << shop[84] << "\n" << shop[81];
            ico();
            buy_off_hand();
        }
    }
}
void buy_hp(item& x)
{
    if (pc.current_gold >= x.price)
    {
        pc.current_gold = pc.current_gold - x.price;
        x.number++;
        system("CLS");
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_health_potion();
    }
    else
    {
        system("CLS");
        std::cout << shop[78] << x.name << "\n" << shop[81];
        ico();
        buy_health_potion();
    }
}
int main()
{
    std::cout << "Loading...";
    SetConsoleTitleA("Recover your strength"); //set the title of the game
    srand((int)time(0)); //for randomness
    system("CLS");
    languagechoice(); //language choice 
    read_language(a, language); //read the story and the questions
    name(); //get the name of the character
    std::cout << "Loading..."; //loading screen 
    readenemies(); //read all enemies
    readweapons(); //read all weapons
    readarmors(); //read all armors
    readitems(); //read all items
    readshop(); //read all shop test
    readfight(); //read all fight text
    readmenu(); //read all menu text
    system("CLS"); //clear console
    //tests(); //tests function
    //playercurrentstate(pc);
    std::cin >> test;
    system("CLS");
    if (test == true)
    {
        bone.number = 200;
        gunpowder.number = 200;
        iron_ingot.number = 200;
        rotten_flesh.number = 200;
    }
    main_menu();
    return 0;
}
