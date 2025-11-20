#include "gtest/gtest.h"
#include "../inc/Task.h"

#include <sstream>

//setup
Date test_date(25,12,2025);
TimeOfDay test_time(18,0,0);
DateTime test_dt(test_date,test_time);
Location test_loc("Ufficio");
const std::string desc="Preparare la relazione annuale";

TEST(TaskTest,ConstructionAndInitialState) { //test costruttore
    Task t(desc,test_dt,test_loc);
    ASSERT_EQ(t.getDescription(),desc);
    ASSERT_EQ(t.getDateTime(),test_dt);
    ASSERT_EQ(t.getLocation(),test_loc);
    ASSERT_FALSE(t.isCompleted());
}

TEST(TaskTest,CompletionSetters) { //test mark completed-pending
    Task t(desc,test_dt,test_loc);
    t.markCompleted();
    ASSERT_TRUE(t.isCompleted());
    t.markPending();
    ASSERT_FALSE(t.isCompleted());
}

TEST(TaskTest, ToStringFormat) { //test toString
    Task t(desc,test_dt,test_loc);
    t.markCompleted();
    std::string expected_completed="Date & Time: 25-12-2025 18:00:00; Location: Ufficio; Completed: yes; Description: Preparare la relazione annuale";
    ASSERT_EQ(t.toString(),expected_completed);
    t.markPending();
    std::string expected_pending = "Date & Time: 25-12-2025 18:00:00; Location: Ufficio; Completed: no; Description: Preparare la relazione annuale";
    ASSERT_EQ(t.toString(),expected_pending);
}

TEST(TaskTest, SaveLoadPersistence) { //test save-load
    Task original_task("Comprare il latte",DateTime("01-01-2026","10:00:00"),Location("Supermercato"));
    original_task.markCompleted();
    std::stringstream ss;
    original_task.save(ss);
    Task loaded_task("Placeholder",DateTime("01-01-1582","00:00:00"),Location("Placeholder"));
    loaded_task.load(ss);
    ASSERT_EQ(loaded_task.getDescription(),"Comprare il latte");
    ASSERT_TRUE(loaded_task.isCompleted());
    ASSERT_EQ(loaded_task.getDateTime().toString(),"01-01-2026 10:00:00");
    ASSERT_EQ(loaded_task.getLocation().getAddress(),"Supermercato");
}