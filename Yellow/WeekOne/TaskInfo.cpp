#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <map>

using namespace std;
// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE         // завершена
};

int rang(TaskStatus value) {
    switch (value) {
        case TaskStatus::NEW:
            return 1;

        case TaskStatus::IN_PROGRESS:
            return 2;

        case TaskStatus::TESTING:
            return 3;

        case TaskStatus::DONE:
            return 4;
    }
}

bool operator<(TaskStatus lhs, TaskStatus rhs) {
    return rang(lhs) < rang(rhs);
}

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return personTasks.at(person);
    }

    // Добавить новую задачу (в статусе TaskStatus::NEW) для конкретного разработчитка
    void AddNewTask(const string &person) {
        ++personTasks[person][TaskStatus::NEW];
    }

    static TasksInfo trim(TasksInfo &tasksInfo) {
        bool hasNew = false;
        bool hasProgress = false;
        bool hasTesting = false;
        bool hasDone = false;

        for (const auto&[p, p1]: tasksInfo) {
            if (p == TaskStatus::NEW && p1 == 0) {
                hasNew = true;
            }
            if (p == TaskStatus::IN_PROGRESS && p1 == 0) {
                hasProgress = true;
            }
            if (p == TaskStatus::TESTING && p1 == 0) {
                hasTesting = true;
            }
            if (p == TaskStatus::DONE && p1 == 0) {
                hasDone = true;
            }
        }
        if (hasNew) {
            tasksInfo.erase(TaskStatus::NEW);
        }
        if (hasProgress) {
            tasksInfo.erase(TaskStatus::IN_PROGRESS);
        }
        if (hasTesting) {
            tasksInfo.erase(TaskStatus::TESTING);
        }
        if (hasDone) {
            tasksInfo.erase(TaskStatus::DONE);
        }
        return tasksInfo;
    }

    static void
    ifBigger(TasksInfo &origTaskInfo, TasksInfo &updatedTask, int &task_count, TaskStatus from, TaskStatus to,
             TasksInfo &origTaskInfoMutable) {
        task_count -= origTaskInfo[from];
        if (task_count < 0) {
            task_count = 0;
        }
        origTaskInfoMutable[to] += origTaskInfo[from];

        updatedTask[to] = origTaskInfo[from];

        origTaskInfoMutable[from] -=origTaskInfo[from];
        origTaskInfo[from] = 0;
    }

    static tuple<TasksInfo, TasksInfo>
    ifLess(TasksInfo &origTaskInfo, TasksInfo &updatedTask, TasksInfo &oldTask, int &task_count,
           TaskStatus from, TaskStatus to, TasksInfo &origTaskInfoMutable) {
        origTaskInfo[from] -= task_count;
        origTaskInfoMutable[from] -= task_count;
        origTaskInfoMutable[to] += task_count;
        updatedTask[to] = task_count;

        if (origTaskInfo[TaskStatus::NEW] != 0) {
            oldTask[TaskStatus::NEW] = origTaskInfo[TaskStatus::NEW];
        }

        if (origTaskInfo[TaskStatus::IN_PROGRESS] != 0) {
            oldTask[TaskStatus::IN_PROGRESS] =
                    origTaskInfo[TaskStatus::IN_PROGRESS];
        }

        if (origTaskInfo[TaskStatus::TESTING] != 0) {
            oldTask[TaskStatus::TESTING] = origTaskInfo[TaskStatus::TESTING];
        }

        trim(updatedTask);
        trim(oldTask);
        trim(origTaskInfoMutable);

        return tie(updatedTask, oldTask);
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count) {
        TasksInfo updatedTask;
        TasksInfo oldTask;
        if (personTasks.count(person) <= 0) {
            return tie(updatedTask, oldTask);
        }
        TasksInfo origTaskInfo = personTasks.at(person);
        TasksInfo &origTaskInfoMutable = personTasks.at(person);

        if (origTaskInfo.count(TaskStatus::NEW) > 0 && task_count <= origTaskInfo.at(TaskStatus::NEW)) {
            return ifLess(origTaskInfo, updatedTask, oldTask, task_count, TaskStatus::NEW, TaskStatus::IN_PROGRESS, origTaskInfoMutable);
        } else {
            ifBigger(origTaskInfo, updatedTask, task_count, TaskStatus::NEW, TaskStatus::IN_PROGRESS, origTaskInfoMutable);
        }

        if (origTaskInfo.count(TaskStatus::IN_PROGRESS) > 0 && task_count <= origTaskInfo.at(TaskStatus::IN_PROGRESS)) {
            return ifLess(origTaskInfo, updatedTask, oldTask, task_count, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, origTaskInfoMutable);
        } else {
            ifBigger(origTaskInfo, updatedTask, task_count, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, origTaskInfoMutable);
        }

        if (origTaskInfo.count(TaskStatus::TESTING) > 0 && task_count <= origTaskInfo.at(TaskStatus::TESTING)) {
            return ifLess(origTaskInfo, updatedTask, oldTask, task_count, TaskStatus::TESTING, TaskStatus::DONE, origTaskInfoMutable);
        } else {
            ifBigger(origTaskInfo, updatedTask, task_count, TaskStatus::TESTING, TaskStatus::DONE, origTaskInfoMutable);
        }

        trim(updatedTask);
        trim(oldTask);
        trim(origTaskInfoMutable);

        return tie(updatedTask, oldTask);
    }

private:
    map<string, TasksInfo> personTasks;
};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
//void PrintTasksInfo(TasksInfo tasks_info) {
//    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
//         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
//         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
//         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
//}

void PrintTasksInfo(const TasksInfo& tasks_info) {
    if (tasks_info.count(TaskStatus::NEW)) {
        std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
    }
    if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
        std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
    }
    if (tasks_info.count(TaskStatus::TESTING)) {
        std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
    }
    if (tasks_info.count(TaskStatus::DONE)) {
        std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
    }
}

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
    std::cout << "Updated: [";
    PrintTasksInfo(updated_tasks);
    std::cout << "] ";

    std::cout << "Untouched: [";
    PrintTasksInfo(untouched_tasks);
    std::cout << "] ";

    std::cout << std::endl;
}

int main() {
    TeamTasks tasks;
    TasksInfo updated_tasks;
    TasksInfo untouched_tasks;

    /* TEST 1 */
    std::cout << "Alice" << std::endl;

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
                                                                   2);  // [{"IN_PROGRESS": Yellow}, {"NEW": 3, "TESTING": 4}]
    PrintTasksInfo(updated_tasks, untouched_tasks);

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": Yellow, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;

    /* TEST Yellow */
    std::cout << "\nJack" << std::endl;

    tasks.AddNewTask("Jack");

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

    tasks.AddNewTask("Jack");

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

    tasks.AddNewTask("Jack");

    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
    std::cout << std::endl;

    /* TEST 3 */
    std::cout << "\nLisa" << std::endl;

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Lisa");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 1);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

    for (auto i = 0; i < 5; ++i) {
        tasks.AddNewTask("Lisa");
    }

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": Yellow}, {"NEW": 3, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 3, "IN_PROGRESS": Yellow, "TESTING": 4, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 4);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 5);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 4, "DONE": 1}, {"TESTING": 4}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"TESTING": 8, "DONE": Yellow}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 8}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 10);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"DONE": 10}
    std::cout << std::endl;

    tasks.AddNewTask("Lisa");

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"NEW": 1, "DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Lisa", 2);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

    PrintTasksInfo(tasks.GetPersonTasksInfo("Lisa"));  // {"IN_PROGRESS": 1, "DONE": 10}
    std::cout << std::endl;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Bob", 3);
    PrintTasksInfo(updated_tasks, untouched_tasks);  // [{}, {}]

    return 0;
}



//int main() {
//    TeamTasks tasks;
//    for (int i = 0; i < 5; ++i) {
//        tasks.AddNewTask("Alice");
//    }
//    cout << endl;
//    TasksInfo updated_tasks, untouched_tasks;
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
//    cout << "Updated Alice's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    cout << "Untouched Alice's tasks: ";
//    PrintTasksInfo(untouched_tasks);
//    cout << endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
//    cout << "Updated Alice's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    cout << "Untouched Alice's tasks: ";
//    PrintTasksInfo(untouched_tasks);
//    cout << endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
//    cout << "Updated Alice's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    cout << "Untouched Alice's tasks: ";
//    PrintTasksInfo(untouched_tasks);
//    cout << endl;
//
//    for (int i = 0; i < 5; ++i) {
//        tasks.AddNewTask("Alice");
//    }
//    cout << "add" << endl; //??
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", Yellow);
//    cout << "Updated Alice's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    cout << "Untouched Alice's tasks: ";
//    PrintTasksInfo(untouched_tasks);
//    cout << endl;//??
//
//    auto r = tasks.GetPersonTasksInfo("Alice");
//    cout << "GetPersonTasksInfo" << endl;
//    PrintTasksInfo(r);
//    cout << endl;
//
//    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
//    cout << "Updated Alice's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    cout << "Untouched Alice's tasks: ";
//    PrintTasksInfo(untouched_tasks);
//    cout << endl;
//
//    r = tasks.GetPersonTasksInfo("Alice");
//    cout << "GetPersonTasksInfo" << endl;
//    PrintTasksInfo(r);

//    AddNewTasks Alice 5
//    PerformPersonTasks Alice 5
//    PerformPersonTasks Alice 5
//    PerformPersonTasks Alice 1
//    AddNewTasks Alice 5
//    PerformPersonTasks Alice Yellow

//    GetPersonTasksInfo Alice
//    PerformPersonTasks Alice 4
//    GetPersonTasksInfo Alice



//    cout << "Ilia's tasks: ";
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
//    cout << "Ivan's tasks: ";
//    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
//
//    TasksInfo updated_tasks, untouched_tasks;
//
//    tie(updated_tasks, untouched_tasks) =
//            tasks.PerformPersonTasks("Ivan", Yellow);
//    cout << "Updated Ivan's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    cout << "Untouched Ivan's tasks: ";
//    PrintTasksInfo(untouched_tasks);
//
//    tie(updated_tasks, untouched_tasks) =
//            tasks.PerformPersonTasks("Ivan", Yellow);
//    cout << "Updated Ivan's tasks: ";
//    PrintTasksInfo(updated_tasks);
//    cout << "Untouched Ivan's tasks: ";
//    PrintTasksInfo(untouched_tasks);

//    return 0;
//}




