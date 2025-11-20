#include "gtest/gtest.h"
#include "../inc/Location.h"

TEST(LocationTest,ConstructionAndGetter) { //test costruttore e getter
    Location loc("Via Roma 10, Milano");
    ASSERT_EQ(loc.getAddress(),"Via Roma 10, Milano");
}

TEST(LocationTest,Setter) { //test setter
    Location loc("Old Address");
    loc.setAddress("New Address, Firenze");
    ASSERT_EQ(loc.getAddress(),"New Address, Firenze");
}

TEST(LocationTest,EqualityOperator) { //test operatore ==
    Location loc1("Piazza Duomo");
    Location loc2("Piazza Duomo");
    Location loc3("Piazza della Scala");
    ASSERT_TRUE(loc1==loc2);
    ASSERT_FALSE(loc1==loc3);
}