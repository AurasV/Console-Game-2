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
PlaySound(L"Sounds\\mob\\file_name.wav", NULL, SND_FILENAME | SND_ASYNC);
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
std::ifstream ascii("ascii images.txt"); //text file containing ascii art for everything
std::string b, first_name, last_name, c, story[100], questions[100], d, ar, fight[100],shop[100],menu[100];
int i, language, j, k, r, enemy_number = 0, e, item_number, p, weapon_number, armor_number, death_number, mute_sound;
int day = 1, min_enemy_ascii, max_enemy_ascii;
char a; //player input variable
bool ok_name = false, ok_fight_first = true, ok_access_shop = false, test, enemy_dead = false, action_done = false;
int lost_fights = 0;
std::string string_ascii[820];
struct player //player
{
    std::string player_name = { " " }; //player name
    float ATK = { 8 }, DEF = { 8 }, THP = { 25 }, CHP = { 25 }; //player number stats
    int current_xp = { 0 }; //current xp
    int level = { 1 }; //current level
    int xp_for_next_level = { 50 };
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
void languagechoice(); //language choice function
void read_language(char a, int& language); //read the story and the questions function
void readfight(); //read all fight needed text function
void readweapons(); //read all weapons function
void readenemies(); //read all enemies function
void readarmors(); //read all armors function
void readitems(); //read all items function
void playercurrentstate(player& x); //output current player state function
void fight_action(enemy& current_enemy); //fight function
void fight_enemy_generate(enemy& enemy); //generate enemy function
void ico(); //input one character then clear console function
void enemy_stats(enemy& x); //output enemy stats function
void weapons(weapon& x); //read weapons from file function
void enemies(enemy& x); //read enemy from file function
void armors(armor& x); //read armor from file function
void items(item& x); //read item from file function
void name(); //get the name of the character function
void access_shop(); //access shop function
void shop_buy(); //buying section of shop function
void shop_sell(); //selling section of shop function
void buy_armor(); //armor buying section of shop function
void buy_weapon(); //weapon buying section of shop function
void buy_health_potion(); //health potion buying section of shop function
void buy_leather(); //leather armor buying section of shop function
void buy_gold(); //gold armor buying section of shop function
void buy_iron(); //iron armor buying section of shop function
void buy_diamond(); //diamond armor buying section of shop function
void buy_netherite(); //netherite armor buying section of shop function
void buy_main_hand(); //main hand weapon buying section of shop function
void buy_off_hand(); //off hand weapon buying section of shop function
void main_menu(); //main menu function
void readshop(); //shop reading function
void readfight(); //fight reading function
void readmenu(); //menu reading function
void nice_try(); //nice try function
void save_game(); //save game function
void load_game(); //load game function
void buy_armor_h(armor x); //buy helmet function
void buy_armor_c(armor x); //buy chestplate function
void buy_armor_p(armor x); //buy pants function
void buy_armor_b(armor x); //buy boots function
void buy_main(weapon x); //buy main weapon function
void buy_off(weapon x); //buy off weapon function
void buy_hp(item& x); //buy health potion function
void try_to_run(enemy& x); //try to run function
void attack_enemy(enemy& x); //attack enemy function
void use_health(enemy& x); //use health function
void dead_enemy(enemy& x); //dead enemy function
void level_up(player& pc); //level up function
void ask_out_story(); //ask if you want story function
void enemy_action(enemy& x); //enemy action function
void lose_battle(); //lose battle function
void ask_out_story(); //ask story function
void finish_game(); //finish game function
void readascii(); //read ascii stuff function
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
    system("CLS");
    if (enemy_dead == true)
        dead_enemy(current_enemy); //what to do if the enemy died
    std::string sound_path;
    int say_random = (rand() % 2) + 1; //randomness    
    if (action_done == true)
    {
        action_done = false;
        enemy_action(current_enemy);
    }
    if (mute_sound == 0) //mute the sound when the player tries to run so it doesn't become annoying
        switch (current_enemy.enemy_name[0]) //check the first letter of the name so there's no need for nested if elses
        {
        case 'Z':
            if (say_random == 1) //two versions of say sound
                PlaySound(L"Sounds\\zombie\\say1.wav", NULL, SND_FILENAME | SND_ASYNC);
            else
                PlaySound(L"Sounds\\zombie\\say2.wav", NULL, SND_FILENAME | SND_ASYNC);
            break;
        case 'S':
            if (say_random == 1) //two versions of say sound
                PlaySound(L"Sounds\\skeleton\\say1.wav", NULL, SND_FILENAME | SND_ASYNC);
            else
                PlaySound(L"Sounds\\skeleton\\say2.wav", NULL, SND_FILENAME | SND_ASYNC);
            break;
        case 'C':
            if (say_random == 1) //two versions of say sound
                PlaySound(L"Sounds\\creeper\\say1.wav", NULL, SND_FILENAME | SND_ASYNC);
            else
                PlaySound(L"Sounds\\creeper\\say2.wav", NULL, SND_FILENAME | SND_ASYNC);
            break;
        case 'H':
            if (say_random == 1) //two versions of say sound
                PlaySound(L"Sounds\\husk\\say1.wav", NULL, SND_FILENAME | SND_ASYNC);
            else
                PlaySound(L"Sounds\\husk\\say2.wav", NULL, SND_FILENAME | SND_ASYNC);
            break;
        case 'I':
            if (say_random == 1) //two versions of say sound
                PlaySound(L"Sounds\\irongolem\\say1.wav", NULL, SND_FILENAME | SND_ASYNC);
            else
                PlaySound(L"Sounds\\irongolem\\say2.wav", NULL, SND_FILENAME | SND_ASYNC);
            break;
        default:
            break;
        };
    if (ok_fight_first == true) 
    {
        std::cout << fight[1] << " " << current_enemy.enemy_name << "\n"; //you've been attacked by on the first run
        ok_fight_first = false;
    }
    else std::cout << fight[2] << " " << current_enemy.enemy_name << "\n"; //you're currently fighting on the subsequent ones
    std::cout << current_enemy.enemy_name << fight[3] << current_enemy.CHP << fight[4] << "\n";
    for (int text = 5; text <= 9; text++)
        std::cout << fight[text] << "\n"; //text
    std::cout << fight[26] << pc.CHP << "\n";
    for (int e = min_enemy_ascii; e <= max_enemy_ascii; e++)
        std::cout << string_ascii[e] << "\n";
    ico();
    switch (a)
    {
    case '1':
        attack_enemy(current_enemy);
        break;
    case '2':
        use_health(current_enemy);
        break;
    case '3':
        enemy_stats(current_enemy);
        break;
    case '0':
        mute_sound = 1;
        try_to_run(current_enemy);
        break;
    default:
        fight_action(current_enemy);
        break;
    }
}
void enemy_action(enemy& x) 
{

    int random_buff = (rand() % 4) + 1; //random buff
    int random_debuff = (rand() % 3) + 1; //random debuff
    int damage = (rand() % (3 * pc.level)) + 1; //base dmg
    damage = damage + random_buff - random_debuff - int(sqrt(pc.DEF)); //final damage
    if (damage <= 0)
        damage = 1;
    pc.CHP -= damage;
    std::cout << x.enemy_name << fight[27] << "\n" << fight[28] << damage << fight[29] << "\n" << shop[81];
    ico();
    if (pc.CHP <= 0)
        lose_battle();
    else
    {
        action_done = false;
        fight_action(x);
    }
}
void lose_battle()
{
    std::cout << fight[30] << "\n" << fight[31] << "\n" << shop[81] << "\n"; //text
    pc.CHP = 1; //set hp to 1 if you lose
    lost_fights++; //for ending
    ico();
    main_menu();
}
void fight_enemy_generate(enemy& current_enemy) //generate enemy
{
    int r = (rand() % 100) + 1; //get random number
    if (r <= 32)
    {
        min_enemy_ascii = 401;
        max_enemy_ascii = 467;
        current_enemy = zombie; //32% chance of zombie
    }
    if (r > 32 && r <= 64)
    {
        min_enemy_ascii = 535;
        max_enemy_ascii = 608;
        current_enemy = skeleton; //32% chance of skeleton
    }
    if (r > 64 && r <= 96)
    {
        min_enemy_ascii = 468;
        max_enemy_ascii = 534;
        current_enemy = husk; //32% chance of husk
    }
    if (r > 96 && r <= 98)
    {
        min_enemy_ascii = 609;
        max_enemy_ascii = 690;
        current_enemy = creeper; //2% chance of creeper
    }
    if (r > 98 && r <= 100)
    {
        min_enemy_ascii = 691;
        max_enemy_ascii = 765;
        current_enemy = iron_golem; //2% chance of iron_golem
    }
    current_enemy.DEF += int(sqrt(pc.level) * 2); //scale according to level
    current_enemy.ATK += int(sqrt(pc.level) * 2); //scale according to level
    current_enemy.CHP += int(sqrt(pc.level) * 4); //scale according to level
    current_enemy.THP += int(sqrt(pc.level) * 4); //scale according to level
} //the scalings probably dont work at later levels...
void playercurrentstate(player& x) //output current player state
{
    int equip_def = equip.h_def + equip.c_def + equip.p_def + equip.b_def; //add alll armor stats
    int equip_atk = equip.mw_atk + equip.ow_atk; //add all weapons attack 
    system("CLS");
    p = pc.player_name.length() - 1; //i dont really remember why this is here
    switch (language)
    {
    case 1: //if the language is english
        if (pc.player_name[p] == 's') //special case because english is a special language
            std::cout << pc.player_name << char(39) << " current stats are:\nAttack: " << pc.ATK + equip_atk << "\nDefense: " << pc.DEF + equip_def << "\nTotal Health Point: " << pc.THP << "\nCurrent Health Points: " << pc.CHP << "\nLevel: " << pc.level << "\nGold: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP Until Level Up: " << pc.xp_for_next_level - pc.current_xp << "\n" << "Helmet: " << equip.head << "\n" << "Chestplate: " << equip.chest << "\n" << "Pants: " << equip.pants << "\n" << "Boots: " << equip.boots << "\n" << "Main Weapon: " << equip.mainweapon << "\n" << "Off-hand Weapon: " << equip.offweapon << "\n"; //if the last letter is s
        else
            std::cout << pc.player_name << char(39) << "s current stats are:\nAttack: " << pc.ATK + equip_atk << "\nDefense: " << pc.DEF + equip_def << "\nTotal Health Point: " << pc.THP << "\nCurrent Health Points: " << pc.CHP << "\nLevel: " << pc.level << "\nGold: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP Until Level Up: " << pc.xp_for_next_level - pc.current_xp << "\n" << "Helmet: " << equip.head << "\n" << "Chestplate: " << equip.chest << "\n" << "Pants: " << equip.pants << "\n" << "Boots: " << equip.boots << "\n" << "Main Weapon: " << equip.mainweapon << "\n" << "Off-hand Weapon: " << equip.offweapon << "\n"; //if the last letter isn't s
        std::cout << shop[81];
        break;
    case 2: //if the language is romanian
        std::cout << "Statisticile Curente pentru " << pc.player_name << " sunt:\n" << "Atac: " << pc.ATK + equip_atk << "\nAparare: " << pc.DEF + equip_def << "\nPuncte de Viata Totale: " << pc.THP << "\nPuncte de Viata Curente: " << pc.CHP << "\nNivel: " << pc.level << "\nAur: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP Pana la Cresterea Nivelului: " << pc.xp_for_next_level - pc.current_xp << "\n" << "Casca: " << equip.head << "\n" << "Platosa: " << equip.chest << "\n" << "Jambiere: " << equip.pants << "\n" << "Cizme: " << equip.boots << "\n" << "Arma Principala: " << equip.mainweapon << "\n" << "Arma Secundara: " << equip.offweapon << "\n"; //if the language is romanian
        std::cout << shop[81];
        break;
    case 3: //if the language is hungarian
        std::cout << "Jelenlegi statisztikak " << pc.player_name << ":\n" << "Tamadas : " << pc.ATK + equip_atk << "\nVedekezes: " << pc.DEF + equip_def << "\nAz osszes eletero: " << pc.THP << "\nJelenlegi eletero: " << pc.CHP << "\nSzint: " << pc.level << "\nArany: " << pc.current_gold << "\nXP: " << pc.current_xp << "\nXP szukseges a szint lepeshez: " << pc.xp_for_next_level - pc.current_xp << "\n" << "Sisak: " << equip.head << "\n" << "Pancel: " << equip.chest << "\n" << "Nadrag: " << equip.pants << "\n" << "Csizma: " << equip.boots << "\n" << "Fo: " << equip.mainweapon << "\n" << equip.offweapon << "Masodlagos: " <<  "\n"; //if the language is hungarian
        std::cout << shop[81];
        break;
    }
    ico();
    main_menu();
}
void dead_enemy(enemy& x)
{
    switch (current_enemy.enemy_name[0]) //check first letter so there's no need for nested if elses
    {
    case 'Z': //death sound
        PlaySound(L"Sounds\\zombie\\death.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'S': //death sound
        PlaySound(L"Sounds\\skeleton\\death.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'C': //death sound
        PlaySound(L"Sounds\\creeper\\death.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'H': //death sound
        PlaySound(L"Sounds\\husk\\death.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'I': //death sound
        PlaySound(L"Sounds\\irongolem\\death.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    default:
        break;
    };
    system("CLS");
    std::cout << fight[13] << "\n";
    int xp = (rand() % 10 * pc.level) + 1; //xp
    int drop = (rand() % 3) + 1; //drop
    std::cout << fight[14] << xp << " " << fight[15] << drop << " " << x.drops; //text
    pc.current_xp = pc.current_xp + xp; //add xp
    if (x.drops == bone.name)
        bone.number += drop; //if enemy drops bones
    if (x.drops == rotten_flesh.name)
        rotten_flesh.number += drop; //if enemy dops rotten flesh
    if (x.drops == gunpowder.name)
        gunpowder.number += drop; //if enemy drops gunpowder
    if (x.drops == iron_ingot.name)
        iron_ingot.number += drop; //if enemy drops iron ingot
    std::cout << "\n" << shop[81] << "\n";
    ico();
    if (pc.current_xp >= pc.xp_for_next_level)
        level_up(pc); //level up if you have enough xp
    else
        main_menu();
}
void level_up(player& pc)
{
    pc.level++; //increase level
    if (pc.level == 25)
        finish_game(); //check for end of game
    if (pc.current_xp > pc.xp_for_next_level)
        pc.current_xp = pc.current_xp - pc.xp_for_next_level; //if you have more xp than necessary
    else
        pc.current_xp = 0; //if not
    pc.xp_for_next_level = pc.xp_for_next_level + 10 * pc.level; //increase needed xp for next level
    pc.ATK++; //increase atk
    pc.DEF++; //increase def
    pc.THP += 10; //increase thp
    pc.CHP = pc.THP; //heal
    if (language != 3)
        std::cout << fight[32] << pc.level << "\n" << shop[81]; //if not hungarian
    else
        std::cout << fight[32] << pc.level << fight[33] << "\n" << shop[81]; //if hungarian
    ico();
    main_menu();
}
void finish_game()
{
    system("CLS");
    std::cout << story[16] << "\n" << story[17] << day << story[18] << "\n" << story[19] << lost_fights << story[20] << "\n" << story[21]; //end of game stuff
    ico();
    exit(0);
}
void enemy_stats(enemy& x) //output enemy stats
{
    system("CLS");
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
    std::cout << "\n" << shop[81];
    ico();
    fight_action(x);
}
void try_to_run(enemy& x)//atempt to run from a fight
{
    int escape = (rand() % 100) + 1; //randomness
    if (escape >= 90) //10% chance to escape
    {
        std::cout << fight[16] << "\n" << shop[81]; //if you escaped
        ico();
        main_menu();
    }
    else
    {
        std::cout << fight[17] << "\n" << shop[81]; //if you didn't
        ico();
        fight_action(x);
    }

}
void attack_enemy(enemy& x)
{ //attack the enemy
    int damage = pc.ATK + equip.mw_atk + equip.ow_atk - x.DEF; //default damage
    int crit = (rand() % 100) + 1; //randomness
    int random_bonus(rand() % 5 + 1); //random damage bonus
    int random_debuff(rand() % 5 + 1); //random damage debuff
    damage += random_bonus; //add damage bonus
    damage -= random_debuff; //substract damage debuff
    if (crit > 95) //crit
        damage *= 2;
    if (damage <= 0)
        damage = 1;
    int hurt_random = (rand() % 2) + 1; //randomness 
    switch (current_enemy.enemy_name[0]) //check the first letter of the name so there's no need for nested if elses
    {
    case 'Z':
        if (hurt_random == 1) //there's two versions of the hurting sound
            PlaySound(L"Sounds\\zombie\\hurt1.wav", NULL, SND_FILENAME | SND_ASYNC);
        else
            PlaySound(L"Sounds\\zombie\\hurt2.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'S':
        if (hurt_random == 1) //there's two versions of the hurting sound
            PlaySound(L"Sounds\\skeleton\\hurt1.wav", NULL, SND_FILENAME | SND_ASYNC);
        else
            PlaySound(L"Sounds\\skeleton\\hurt2.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'C':
        if (hurt_random == 1) //there's two versions of the hurting sound
            PlaySound(L"Sounds\\creeper\\hurt1.wav", NULL, SND_FILENAME | SND_ASYNC);
        else
            PlaySound(L"Sounds\\creeper\\hurt2.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'H':
        if (hurt_random == 1) //there's two versions of the hurting sound
            PlaySound(L"Sounds\\husk\\hurt1.wav", NULL, SND_FILENAME | SND_ASYNC);
        else
            PlaySound(L"Sounds\\husk\\hurt2.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    case 'I':
        if (hurt_random == 1) //there's two versions of the hurting sound
            PlaySound(L"Sounds\\irongolem\\hurt1.wav", NULL, SND_FILENAME | SND_ASYNC);
        else
            PlaySound(L"Sounds\\irongolem\\hurt2.wav", NULL, SND_FILENAME | SND_ASYNC);
        break;
    default:
        break;
    };
    x.CHP = x.CHP - damage; //change enemy hp
    if (x.CHP <= 0)
        enemy_dead = true;
    std::cout << fight[10] << damage << fight[11] << "\n" << shop[81];
    action_done = true; //counts as an action so the enemy can attack
    mute_sound = 0;
    ico();
    fight_action(x);
}
void use_health(enemy& x)
{
    system("CLS");
    std::cout << fight[18] << "\n"; //text
    std::cout << fight[19] << normal_hp.number << "\n"; //text
    std::cout << fight[20] << greater_hp.number << "\n"; //text
    std::cout << fight[21] << supreme_hp.number << "\n"; //text
    std::cout << fight[22] << "\n" << fight[23] << "\n"; //text
    ico();
    switch (a)
    {
    case '1':
        if (pc.CHP == pc.THP) //full hp already
        {
            std::cout << fight[24] << "\n" << shop[81]; //text
            ico();
            use_health(x);
        }
        if (normal_hp.number > 0) //if you have potion
        {
            normal_hp.number--;
            pc.CHP += 10;
            if (pc.THP < pc.CHP)
                pc.CHP = pc.THP;
            use_health(x);
        }
        else //if you dont
        {
            std::cout << fight[25] << normal_hp.name << "\n" << shop[81]; //text
            ico();
            use_health(x);
        }
        break;
    case '2':
        if (pc.CHP == pc.THP) //full hp already
        {
            std::cout << fight[24] << "\n" << shop[81]; //text
            ico();
            use_health(x);
        }
        if (greater_hp.number > 0) //if you have potion
        {
            greater_hp.number--;
            pc.CHP += 20;
            if (pc.THP < pc.CHP)
                pc.CHP = pc.THP;
            use_health(x);
        }
        else //if you dont
        {
            std::cout << fight[25] << greater_hp.name << "\n" << shop[81]; //text
            ico();
            use_health(x);
        }
        break;
    case '3':
        if (pc.CHP == pc.THP) //full hp already
        {
            std::cout << fight[24] << "\n" << shop[81];
            ico();
            use_health(x);
        }
        if (supreme_hp.number > 0) //if you have potion
        {
            supreme_hp.number--;
            pc.CHP += 30;
            if (pc.THP < pc.CHP)
                pc.CHP = pc.THP;
            use_health(x);
        }
        else //if you dont
        {
            std::cout << fight[25] << supreme_hp.name << "\n" << shop[81]; //text
            ico();
            use_health(x);
        }
        break;
    case '0':
        fight_action(x);
        break;
    default:
        std::cout << shop[79] << "\n";
        use_health(x);
        break;
    }
}
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
void main_menu() 
{
    if (language == 3)
        std::cout << day << menu[1] << "\n"; //day 
    else
        std::cout << menu[1] << day << "\n"; //day
    for (int menu_counter = 2; menu_counter <= 9; menu_counter++)
        std::cout << menu[menu_counter] << "\n"; //text
    ico(); //answer
    switch (a)
    {
    case '1': //find enemy
        ok_fight_first = true;
        enemy_dead = false;
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
    case '6': //load game
        load_game();
        break;
    case '0': //exit
        std::cout << menu[10] << "\n" << questions[3] << "\n" << questions[4] << "\n"; //are you sure?
        ico(); //answer
        if (a == '1')
        { //quit
            system("CLS");
            std::cout << "Quitting...";
            exit(0);
        }
        else main_menu(); //return
        break;
    default: //wrong input
        std::cout << shop[79] << "\n"; //if wrong input
        main_menu();
        break;
    }
}
void save_game()
{
    system("CLS"); //clear console
    for (int i = 5; i <= 9; i++)
        std::cout << questions[i] << "\n"; //text
    ico(); //read answer
    switch (a)
    {
    case '1':
    {
        std::ifstream save;
        save.open("save1.txt");
        if (save.fail()) //check if the file already exists
        { //if it doesn't
            save.close();
            std::ofstream save("save1.txt");
            system("CLS");
            for (int e = 767; e <= 778; e++)
                std::cout << string_ascii[e] << "\n"; //text
            save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << pc.xp_for_next_level << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n";
            system("CLS");
            for (int e = 779; e <= 794; e++)
                std::cout << string_ascii[e] << "\n"; //text
            std::cout << shop[81];
            save.close();
        }
        else
        { //if it does
            for (int skip = 15; skip <= 17; skip++)
                std::cout << questions[skip] << "\n"; //text
            ico(); //answer
            if (a == '1') //overwrite
            {
                save.close();
                std::ofstream save("save1.txt");
                system("CLS");
                for (int e = 767; e <= 778; e++)
                    std::cout << string_ascii[e] << "\n"; //text
                save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << pc.xp_for_next_level << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n";
                system("CLS");
                for (int e = 779; e <= 794; e++)
                    std::cout << string_ascii[e] << "\n"; //text
                std::cout << shop[81];
                save.close();
            }
            else //return 
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
        if (save.fail()) //check if the file already exists
        { //if it doesn't
            save.close();
            std::ofstream save("save2.txt");
            system("CLS");
            for (int e = 767; e <= 778; e++)
                std::cout << string_ascii[e] << "\n"; //text
            save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << pc.xp_for_next_level << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n";
            system("CLS");
            for (int e = 779; e <= 794; e++)
                std::cout << string_ascii[e] << "\n"; //text
            std::cout << shop[81];
            save.close();
        }
        else
        { //if it does
            for (int skip = 15; skip <= 17; skip++)
                std::cout << questions[skip] << "\n"; //text
            ico(); //answer
            if (a == '1')
            { //overwrite
                save.close();
                std::ofstream save("save2.txt");
                system("CLS");
                for (int e = 767; e <= 778; e++)
                    std::cout << string_ascii[e] << "\n"; //text
                save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << pc.xp_for_next_level << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n";
                system("CLS");
                for (int e = 779; e <= 794; e++)
                    std::cout << string_ascii[e] << "\n"; //text
                std::cout << shop[81];
                save.close();
            }
            else
                main_menu(); //return 
        }
        ico();
        main_menu();
        break;
    }
    case '3':
    {
        std::ifstream save;
        save.open("save3.txt");
        if (save.fail()) //check if file already exists
        { //if it doesn't
            save.close();
            std::ofstream save("save3.txt");
            system("CLS");
            for (int e = 767; e <= 778; e++)
                std::cout << string_ascii[e] << "\n"; //text
            save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << pc.xp_for_next_level << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n";
            system("CLS");
            for (int e = 779; e <= 794; e++) 
                std::cout << string_ascii[e] << "\n"; //text
            std::cout << shop[81];
            save.close();
        }
        else
        { //if it does
            for (int skip = 15; skip <= 17; skip++)
                std::cout << questions[skip] << "\n"; //text
            ico(); //answer
            if (a == '1')
            { //overwrite
                save.close();
                std::ofstream save("save3.txt");
                system("CLS");
                for (int e = 767; e <= 778; e++)
                    std::cout << string_ascii[e] << "\n"; //text
                save << pc.player_name << "\n" << pc.ATK << "\n" << pc.DEF << "\n" << pc.THP << "\n" << pc.CHP << "\n" << pc.level << "\n" << pc.current_gold << "\n" << pc.current_xp << "\n" << pc.xp_for_next_level << "\n" << bone.number << "\n" << gunpowder.number << "\n" << rotten_flesh.number << "\n" << iron_ingot.number << "\n" << normal_hp.number << "\n" << greater_hp.number << "\n" << supreme_hp.number << "\n" << equip.h_def << "\n" << equip.c_def << "\n" << equip.p_def << "\n" << equip.b_def << "\n" << equip.mw_atk << "\n" << equip.ow_atk << "\n" << equip.head << "\n" << equip.chest << "\n" << equip.pants << "\n" << equip.boots << "\n";
                system("CLS");
                for (int e = 779; e <= 794; e++)
                    std::cout << string_ascii[e] << "\n"; //text
                std::cout << shop[81];
                save.close();
            }
            else
                main_menu(); //return
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
    for (int e = 767; e <= 778; e++)
        std::cout << string_ascii[e] << "\n";
    
}
void load_game()
{
    system("CLS"); //clear console
    for (int i = 10; i <= 14; i++)
        std::cout << questions[i] << "\n"; //text
    ico(); //answer
    system("CLS"); //clear console
    switch (a)
    {
    case '1':
    {
        std::ifstream save;
        save.open("save1.txt");
        if (save.fail()) //check if file exists
        { //if it doesn't
            std::cout << menu[11] << "\n" << menu[12] << "\n" << shop[81];
        }
        else
        { //if it does
            for (int e = 767; e <= 778; e++)
                std::cout << string_ascii[e] << "\n"; //loading screen
            std::getline(save, b);
            pc.player_name = b;
            save >> pc.ATK >> pc.DEF >> pc.THP >> pc.CHP;
            save >> pc.level >> pc.current_gold >> pc.current_xp >> pc.xp_for_next_level;
            save >> bone.number >> gunpowder.number >> rotten_flesh.number >> iron_ingot.number;
            save >> normal_hp.number >> greater_hp.number >> supreme_hp.number;
            save >> equip.h_def >> equip.c_def >> equip.p_def >> equip.b_def;
            save >> equip.mw_atk >> equip.ow_atk;
            std::getline(save, b);
            b = equip.head;
            std::getline(save, b);
            b = equip.chest;
            std::getline(save, b);
            b = equip.pants;
            std::getline(save, b);
            b = equip.boots;
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
        if (save.fail()) //check if file exists
        { //if it doesn't
            std::cout << menu[11] << "\n" << menu[12] << "\n" << shop[81];
        }
        else
        { //if it does
            for (int e = 767; e <= 778; e++)
                std::cout << string_ascii[e] << "\n"; //loading screen
            std::getline(save, b);
            pc.player_name = b;
            save >> pc.ATK >> pc.DEF >> pc.THP >> pc.CHP;
            save >> pc.level >> pc.current_gold >> pc.current_xp >> pc.xp_for_next_level;
            save >> bone.number >> gunpowder.number >> rotten_flesh.number >> iron_ingot.number;
            save >> normal_hp.number >> greater_hp.number >> supreme_hp.number;
            save >> equip.h_def >> equip.c_def >> equip.p_def >> equip.b_def;
            save >> equip.mw_atk >> equip.ow_atk;
            std::getline(save, b);
            b = equip.head;
            std::getline(save, b);
            b = equip.chest;
            std::getline(save, b);
            b = equip.pants;
            std::getline(save, b);
            b = equip.boots;
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
        if (save.fail()) //check if file exists
        { //if it doesn't
            std::cout << menu[11] << "\n" << menu[12] << "\n" << shop[81];
        }
        else
        { //if it does
            for (int e = 767; e <= 778; e++)
                std::cout << string_ascii[e] << "\n"; //loading screen
            std::getline(save, b);
            pc.player_name = b;
            save >> pc.ATK >> pc.DEF >> pc.THP >> pc.CHP;
            save >> pc.level >> pc.current_gold >> pc.current_xp >> pc.xp_for_next_level;
            save >> bone.number >> gunpowder.number >> rotten_flesh.number >> iron_ingot.number;
            save >> normal_hp.number >> greater_hp.number >> supreme_hp.number;
            save >> equip.h_def >> equip.c_def >> equip.p_def >> equip.b_def;
            save >> equip.mw_atk >> equip.ow_atk;
            std::getline(save, b);
            b = equip.head;
            std::getline(save, b);
            b = equip.chest;
            std::getline(save, b);
            b = equip.pants;
            std::getline(save, b);
            b = equip.boots;
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
{ //day overflow function
    std::cout << "Nice try! The game will now close"; //text
    ico();
    exit(0);
}
void buy_armor_h(armor x) //buy helmet function
{
    if (pc.current_gold >= x.price && x.DEF > equip.h_def) //if you have gold and worse armor
    {
        pc.current_gold = pc.current_gold - x.price; //change gold
        equip.h_def = x.DEF;
        equip.head = x.name;
        system("CLS");
        for (int e = 242; e <= 268; e++)
            std::cout << string_ascii[e] << "\n";
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_armor();
    }
    else
    {
        if (pc.current_gold < x.price) //if you dont have money
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_armor();
        }
        else //if you have better helmet
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
    if (pc.current_gold >= x.price && x.DEF > equip.c_def) //if you have gold and worse armor
    {
        pc.current_gold = pc.current_gold - x.price; //change gold
        equip.c_def = x.DEF;
        equip.chest = x.name;
        system("CLS");
        for (int e = 282; e <= 320; e++)
            std::cout << string_ascii[e] << "\n";
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_armor();
    }
    else
    {
        if (pc.current_gold < x.price) //if you dont have gold
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_armor();
        }
        else
        { //if you have better chestplate
            system("CLS");
            std::cout << shop[83] << "\n" << shop[81];
            ico();
            buy_armor();
        }
    }
}
void buy_armor_p(armor x) //buy pants function
{
    if (pc.current_gold >= x.price && x.DEF > equip.p_def) //if you have gold and worse armor
    {
        pc.current_gold = pc.current_gold - x.price; //change gold
        equip.p_def = x.DEF;
        equip.pants = x.name;
        system("CLS");
        for (int e = 323; e <= 359; e++)
            std::cout << string_ascii[e] << "\n";
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_armor();
    }
    else
    {
        if (pc.current_gold < x.price) //if you dont have money
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_armor();
        }
        else
        { //if you have better armor
            system("CLS");
            std::cout << shop[83] << "\n" << shop[81];
            ico();
            buy_armor();
        }
    }
}
void buy_armor_b(armor x) //buy boots function
{
    if (pc.current_gold >= x.price && x.DEF > equip.b_def) //if you have gold and worse armor
    {
        pc.current_gold = pc.current_gold - x.price; //change gold
        equip.b_def = x.DEF;
        equip.boots = x.name;
        system("CLS");
        for (int e = 362; e <= 399; e++)
            std::cout << string_ascii[e] << "\n";
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_armor();
    }
    else
    {
        if (pc.current_gold < x.price) //if you dont have gold
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_armor();
        }
        else
        { //if you have better armor
            system("CLS");
            std::cout << shop[83] << "\n" << shop[81];
            ico();
            buy_armor();
        }
    }
}
void buy_main(weapon x)
{
    if (pc.current_gold >= x.price && x.ATK > equip.mw_atk) //if you have gold and worse weapon
    {
        pc.current_gold = pc.current_gold - x.price; //change gold
        equip.mw_atk = x.ATK;
        equip.mainweapon = x.name;
        system("CLS");
        if (x.price == 100 || x.price == 200) //different ascii art depending on price
            for (int e = 1; e <= 40; e++)
                std::cout << string_ascii[e] << "\n";
        if (x.price == 300 || x.price == 400)
            for (int e = 41; e <= 80; e++)
                std::cout << string_ascii[e] << "\n";
        if (x.price == 500)
            for (int e = 81; e <= 120; e++)
                std::cout << string_ascii[e] << "\n";
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_main_hand();
    }
    else
    {
        if (pc.current_gold < x.price) //if you dont have gold
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_main_hand();
        }
        else
        { //if you have better weapon
            system("CLS");
            std::cout << shop[84] << "\n" << shop[81];
            ico();
            buy_main_hand();
        }
    }
}
void buy_off(weapon x)
{
    if (pc.current_gold >= x.price && x.ATK > equip.ow_atk) //if you have gold and worse weapon
    {
        pc.current_gold = pc.current_gold - x.price; //change gold
        equip.ow_atk = x.ATK;
        equip.offweapon = x.name;
        system("CLS");
        if (x.price == 300)
            for (int e = 124; e <= 160; e++)
                std::cout << string_ascii[e] << "\n";
        if (x.price == 400)
            for (int e = 161; e <= 198; e++)
                std::cout << string_ascii[e] << "\n";
        if (x.price == 500)
            for (int e = 206; e <= 238; e++)
                std::cout << string_ascii[e] << "\n";
        std::cout << shop[82] << x.name << shop[81];
        ico();
        buy_off_hand();
    }
    else
    {
        if (pc.current_gold < x.price) //if you dont have gold
        {
            system("CLS");
            std::cout << shop[78] << x.name << "\n" << shop[81];
            ico();
            buy_off_hand();
        }
        else
        { //if you have better weapon
            system("CLS");
            std::cout << shop[84] << "\n" << shop[81];
            ico();
            buy_off_hand();
        }
    }
}
void buy_hp(item& x)
{
    if (pc.current_gold >= x.price) //if you have gold
    {
        pc.current_gold = pc.current_gold - x.price;
        x.number++;
        system("CLS");
        std::cout << shop[82] << x.name << "\n" << shop[81];
        ico();
        buy_health_potion();
    }
    else
    { //if you dont have gold
        system("CLS");
        std::cout << shop[78] << x.name << "\n" << shop[81];
        ico();
        buy_health_potion();
    }
}
void ask_out_story()
{
    system("CLS");
    std::cout << story[13] << "\n" << story[14] << "\n" << story[15] << "\n"; //text
    ico();
    switch (a)
    {
    case '1':
        for (int story_int = 2; story_int <= 12; story_int++)
            std::cout << story[story_int] << "\n"; //text
        std::cout << shop[81];
        ico();
        main_menu();
    case '2':
        main_menu();
    default:
        ask_out_story();
    }
}
void readascii()
{
    int e;
    for (e = 1; e < 800; e++)
    {
        std::getline(ascii, b);
        string_ascii[e] = b;
    }
    ascii.close();
}
void main()
{  
    /*
    a lot of these functions could be done in the main program but I'd rather
    make them functions so its easier to digest because they have a self explanatory name
    and it helps keep track of them (of course I wouldn't do this with a bigger project)
    */
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); //fullscreen W10
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0); //fulscreen W7
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = 15;                  // Height of each character in the font
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    std::wcscpy(cfi.FaceName, L"Consolas"); // font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi); 
    readascii(); //reads all ascii stuff
    for (int e = 767; e <= 778; e++)
        std::cout << string_ascii[e] << "\n"; //loading screen 
    SetConsoleTitleA("Recover your strength"); //set the title of the game 
    srand((int)time(0)); //for randomness 
    system("CLS"); // clear console
    languagechoice(); //language choice 
    read_language(a, language); //read the story and the questions
    name(); //get the name of the character
    for (int e = 767; e <= 778; e++)
        std::cout << string_ascii[e] << "\n"; //loading screen 
    readenemies(); //read all enemies
    readweapons(); //read all weapons
    readarmors(); //read all armors
    readitems(); //read all items
    readshop(); //read all shop test
    readfight(); //read all fight text
    readmenu(); //read all menu text
    system("CLS"); //clear console
    ask_out_story(); //ask if the player wants the story or not
}
