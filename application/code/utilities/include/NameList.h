#pragma once

#include <string>
#include <set>

struct NameList
{
    static std::set<std::string> names;
};

std::set<std::string> NameList::names = { "James", "Robert", "John", "Michael", "David", "Wiliam", "Richard", "Joseph", "Thomas",
                                        "Charles", "Christopher", "Daniel", "Matthew", "Anthony", "Mark", "Donald", "Steven",
                                        "Paul", "Andrew", "Joshua", "Kenneth", "Kevin", "Brian", "George", "Timothy", "Ronald",
                                        "Edward", "Jason", "Jeffrey", "Ryan", "Jacob", "Gary", "Nicholas", "Jan Pawel Drugi Papiesh",
                                        "Pierun", "Tofik", "Eric", "Jonathan", "Stephen", "Larry", "Justin", "Scott", "Brandon",
                                        "Benjamin", "Samuel", "Gregory", "Aleksander", "Frank", "Raymond", "Mary", "Jennifer",
                                        "Linda", "Elizabeth", "Barbara", "Susan", "Jessica", "Sarah", "Karen", "Lisa", "Nancy",
                                        "Betty", "Margaret", "Sandra", "Ashley", "Kimberly", "Emily", "Donna", "Michelle", "Carol",
                                        "Amanda", "Dorothy", "Melissa", "Deborah", "Stephanie", "Rebecca", "Sharon", "Laura", "Cynthia",
                                        "Kathleen", "Amy", "Angela", "Shirley", "Anna", "Brenda", "Pamela", "Emma", "Nicole", "Helen",
                                        "Samantha", "Katherine", "Christine", "Debra", "Rachel", "Carolyn", "Janet", "Catherine",
                                        "Heather"};