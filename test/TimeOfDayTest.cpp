#include "gtest/gtest.h"
#include "../inc/TimeOfDay.h"

#include <stdexcept>

TEST(TimeTest, ValidConstructionAndGetters) { //test costruttore e getter con input validi
    TimeOfDay t(14,30,45);
    ASSERT_EQ(t.getHour(),14);
    ASSERT_EQ(t.getMinute(),30);
    ASSERT_EQ(t.getSecond(),45);
    ASSERT_EQ(t.toString(),"14:30:45");
}

TEST(TimeTest,StringConstructionValid) { //test costruttore da stringa con input validi
    TimeOfDay t("09:05:01");
    ASSERT_EQ(t.getHour(),9);
    ASSERT_EQ(t.getMinute(),5);
    ASSERT_EQ(t.getSecond(),1);
    ASSERT_EQ(t.toString(),"09:05:01");
}

TEST(TimeTest,InvalidConstructionThrowsException) { //test costruttore con input non validi
    ASSERT_THROW(TimeOfDay(24,0,0),std::invalid_argument);
    ASSERT_THROW(TimeOfDay(10,60,0),std::invalid_argument);
    ASSERT_THROW(TimeOfDay(10,0,60),std::invalid_argument);
    ASSERT_THROW(TimeOfDay("10-30-00"),std::invalid_argument);
}

TEST(TimeTest,EqualityOperator) { //test operatore ==
    TimeOfDay t1(12,30,0);
    TimeOfDay t2(12,30,0);
    TimeOfDay t3(12,30,1);
    ASSERT_TRUE(t1==t2);
    ASSERT_FALSE(t1==t3);
}

TEST(TimeTest,GreaterThanOperator) { //test operatore >
    TimeOfDay t1(10,0,0);
    TimeOfDay t2(11,0,0);
    TimeOfDay t3(10,30,0);
    TimeOfDay t4(10,0,15);
    ASSERT_TRUE(t2>t1);
    ASSERT_TRUE(t3>t1);
    ASSERT_TRUE(t4>t1);
    ASSERT_FALSE(t1>t1);
}

TEST(TimeTest,LessThanOperator) { //test operatore <
    TimeOfDay t1(10,0,0);
    TimeOfDay t2(9,59,59);
    TimeOfDay t3(9,30,0);
    TimeOfDay t4(9,0,0);
    ASSERT_TRUE(t2<t1);
    ASSERT_TRUE(t3<t1);
    ASSERT_TRUE(t4<t1);
    ASSERT_FALSE(t1<t1);
}