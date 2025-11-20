#include "gtest/gtest.h"
#include "../inc/DateTime.h"

#include <stdexcept>

//setup oggetti validi
Date d1(15,6,2025);
TimeOfDay t1(10,30,0);
Date d2(16,6,2025);
TimeOfDay t2(11,30,0);

TEST(DateTimeTest,ObjectConstructionAndGetters) { //test costruttore con oggetti e getters
    DateTime dt(d1,t1);
    ASSERT_EQ(dt.getDate(),d1);
    ASSERT_EQ(dt.getTime(),t1);
    ASSERT_EQ(dt.toString(),"15-06-2025 10:30:00");
}

TEST(DateTimeTest,StringConstruction) { //test costruttore con stringhe
    DateTime dt("20-12-2024","23:59:59");
    ASSERT_EQ(dt.getDate().toString(),"20-12-2024");
    ASSERT_EQ(dt.getTime().toString(),"23:59:59");
}

TEST(DateTimeTest,Setters) { //test setter
    DateTime dt(1,1,2000,0,0,0);
    dt.setDate(d2);
    dt.setTime(t2);
    ASSERT_EQ(dt.toString(),"16-06-2025 11:30:00");
    dt.setDate(5,5,2005);
    dt.setTime(5,5,5);
    ASSERT_EQ(dt.toString(),"05-05-2005 05:05:05");
}

TEST(DateTimeTest,EqualityOperator) { //test operatore ==
    DateTime dt1(d1,t1);
    DateTime dt2(d1,t1);
    DateTime dt3(d2,t1);
    ASSERT_TRUE(dt1==dt2);
    ASSERT_FALSE(dt1==dt3);
}

TEST(DateTimeTest,GreaterThanOperator_TimeDifference) { //test operatore > con ora diversa
    DateTime dt1(d1,t1);
    DateTime dt2(d1,t2);
    ASSERT_TRUE(dt2>dt1);
    ASSERT_FALSE(dt1>dt2);
}

TEST(DateTimeTest,GreaterThanOperator_DateDifference) { //test operatore > con data diversa
    DateTime dt1(d1,t1);
    DateTime dt2(d2,t1);
    ASSERT_TRUE(dt2>dt1);
    ASSERT_FALSE(dt1>dt2);
}

TEST(DateTimeTest,GreaterThanOperator_DateDominates) { //test operatore >
    DateTime earlier_date_later_time(d1,t2);
    DateTime later_date_earlier_time(d2,t1);
    ASSERT_TRUE(later_date_earlier_time>earlier_date_later_time);
}

TEST(DateTimeTest, LessThanOperator) { //test operatore <
    DateTime dt1(d2,t2);
    DateTime dt2(d1,t1);
    ASSERT_TRUE(dt2<dt1);
    ASSERT_FALSE(dt1<dt2);
}