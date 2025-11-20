#include "gtest/gtest.h"
#include "../inc/Date.h"

#include <stdexcept>

TEST(DateTest,ValidConstructionAndGetters) { //test costruttore e getter con input validi
    Date d(15,6,2025);
    ASSERT_EQ(d.getDay(),15);
    ASSERT_EQ(d.getMonth(),6);
    ASSERT_EQ(d.getYear(),2025);
    ASSERT_EQ(d.toString(),"15-06-2025");
}

TEST(DateTest,InvalidConstructionThrowsException) { //test costruttore con input non validi
    ASSERT_THROW(Date(32,1,2024), std::invalid_argument);
    ASSERT_THROW(Date(1,13,2024), std::invalid_argument);
    ASSERT_THROW(Date(1,1,1581), std::invalid_argument);
    ASSERT_THROW(Date(30,2,2023), std::invalid_argument);
}

TEST(DateTest,IsLeapYear) { //test anni bisestili
    Date d1(1,1,2000);
    ASSERT_TRUE(d1.isLeapYear(2000));
    Date d2(1,1,2024);
    ASSERT_TRUE(d2.isLeapYear(2024));
    Date d3(1,1,1900);
    ASSERT_FALSE(d3.isLeapYear(1900));
    Date d4(1,1,2023);
    ASSERT_FALSE(d4.isLeapYear(2023));
}

TEST(DateTest,LeapDayValidation) { //test 29 febbraio
    ASSERT_NO_THROW(Date(29,2,2024));
    ASSERT_THROW(Date(29,2,2023), std::invalid_argument);
}

TEST(DateTest,EqualityOperator) { //test operatore ==
    Date d1(10,5,2025);
    Date d2(10,5,2025);
    Date d3(11,5,2025);
    ASSERT_TRUE(d1==d2);
    ASSERT_FALSE(d1==d3);
}

TEST(DateTest,GreaterThanOperator) { //test operatore >
    Date d1(10,5,2025);
    Date d2(11,5,2025);
    Date d3(10,6,2025);
    Date d4(10,5,2026);
    ASSERT_TRUE(d2>d1);
    ASSERT_TRUE(d3>d1);
    ASSERT_TRUE(d4>d1);
    ASSERT_FALSE(d1>d1);
    ASSERT_FALSE(d1>d2);
}

TEST(DateTest,LessThanOperator) { //test operatore <
    Date d1(10,5,2025);
    Date d2(9,5,2025);
    Date d3(10,4,2025);
    Date d4(10,5,2024);
    ASSERT_TRUE(d2<d1);
    ASSERT_TRUE(d3<d1);
    ASSERT_TRUE(d4<d1);
    ASSERT_FALSE(d1<d1);
    ASSERT_FALSE(d1<d2);
}