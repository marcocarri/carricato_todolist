#include "gtest/gtest.h"
#include "../inc/ToDoList.h"

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <fstream>

//uso una fixture per testare la classe senza alterare il file
class ToDoListTest : public ::testing::Test {
protected:
    ToDoList list;
    //oggetti per testare
    Task t1;
    Task t2;
    Task t3;

    ToDoListTest() :
        t1("Task 1: Passata",DateTime(10,5,2025,10,0,0),Location("Casa")),
        t2("Task 2: Prossima",DateTime(15,5,2025,15,0,0),Location("Ufficio")),
        t3("Task 3: Passata-Tardi",DateTime(10,5,2025,11,0,0),Location("Parco"))
    {}

    void SetUp() override {
        std::ofstream file(list.getFileName(), std::ios::trunc);
        file.close();
        list.setTasks({});
        list.addTask(t1.getDescription(),t1.getDateTime(),t1.getLocation());
        list.getTask(0).markCompleted();
        list.addTask(t2.getDescription(),t2.getDateTime(),t2.getLocation());
        list.addTask(t3.getDescription(),t3.getDateTime(),t3.getLocation());
    }
    void TearDown() override {
        std::ofstream file(list.getFileName(), std::ios::trunc);
        file.close();
    }
};


TEST_F(ToDoListTest,AddAndRemoveTask) { //test addTask e removeTask
    ASSERT_EQ(list.getTasks().size(),3);
    list.removeTask(1);
    ASSERT_EQ(list.getTasks().size(),2);
    ASSERT_EQ(list.getTasks()[0].getDescription(),t1.getDescription());
    ASSERT_EQ(list.getTasks()[1].getDescription(),t3.getDescription());
    ASSERT_THROW(list.removeTask(5),std::out_of_range);
}

TEST_F(ToDoListTest,SortDescending) { //test ordinamento decrescente
    auto sorted=list.getSortedTasksByDateTimeDescending();
    ASSERT_EQ(sorted.size(),3);
    ASSERT_EQ(sorted[0].getDescription(),t2.getDescription());
    ASSERT_EQ(sorted[1].getDescription(),t3.getDescription());
    ASSERT_EQ(sorted[2].getDescription(),t1.getDescription());
}

TEST_F(ToDoListTest,SortAscending) { //test ordinamento crescente
    auto sorted=list.getSortedTasksByDateTimeAscending();
    ASSERT_EQ(sorted.size(),3);
    ASSERT_EQ(sorted[0].getDescription(),t1.getDescription());
    ASSERT_EQ(sorted[1].getDescription(),t3.getDescription());
    ASSERT_EQ(sorted[2].getDescription(),t2.getDescription());
}

TEST_F(ToDoListTest,FilterByCompleted) { //test filtro per stato di completamento (true)
    auto completed=list.getFilteredTasksByCompleted(true);
    ASSERT_EQ(completed.size(),1);
    ASSERT_EQ(completed[0].getDescription(),t1.getDescription());
}

TEST_F(ToDoListTest,FilterByPending) { //test filtro per stato di completamento (false)
    auto pending=list.getFilteredTasksByCompleted(false);
    ASSERT_EQ(pending.size(),2);
    std::vector<std::string> pending_desc;
    for (const auto& task : pending) { pending_desc.push_back(task.getDescription()); }
    ASSERT_TRUE(std::find(pending_desc.begin(),pending_desc.end(),t2.getDescription())!=pending_desc.end());
    ASSERT_TRUE(std::find(pending_desc.begin(),pending_desc.end(),t3.getDescription())!=pending_desc.end());
}

TEST_F(ToDoListTest,FilterByDate) { //test filtro per data
    Date specific_date(10,5,2025);
    Date no_match_date(1,1,2026);
    auto tasks_10_05=list.getFilteredTasksByDate(specific_date);
    ASSERT_EQ(tasks_10_05.size(),2);
    auto tasks_2026=list.getFilteredTasksByDate(no_match_date);
    ASSERT_TRUE(tasks_2026.empty());
}