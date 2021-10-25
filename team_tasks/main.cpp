#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <vector>
#include <utility>

enum class TaskStatus {
    NEW, 
    IN_PROGRESS,
    TESTING,
    DONE
};

using TasksInfo = std::map<TaskStatus, int>;

class TeamTasks {
public:
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const
    {
        return tasks.at(person);
    }

    void AddNewTask(const std::string& person)
    {
        tasks[person][TaskStatus::NEW]++;
    }

    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(const std::string& person, int task_count)
    {
        std::map<std::string, TasksInfo> copy_tasks(tasks);
        TasksInfo updatedTasks;
        TasksInfo legacyTasks;

        for (int i = 0; i < task_count; i++)
        {
        	if (copy_tasks[person][TaskStatus::NEW] != 0)
        	{
            	copy_tasks[person][TaskStatus::NEW]--;
                copy_tasks[person][TaskStatus::IN_PROGRESS]++;
                updatedTasks[TaskStatus::IN_PROGRESS]++;

        	}
        	else if (copy_tasks[person][TaskStatus::IN_PROGRESS] != 0)
        	{
            	copy_tasks[person][TaskStatus::IN_PROGRESS]--;
                copy_tasks[person][TaskStatus::TESTING]++;
                updatedTasks[TaskStatus::TESTING]++;

        	}
        	else if (copy_tasks[person][TaskStatus::TESTING] != 0)
        	{
            	copy_tasks[person][TaskStatus::TESTING]--;
                copy_tasks[person][TaskStatus::DONE]++;
                updatedTasks[TaskStatus::DONE]++;

        	}
        }

        if (copy_tasks[person][TaskStatus::NEW] != 0)
        {
    		legacyTasks[TaskStatus::NEW] = copy_tasks[person][TaskStatus::NEW];
        }

        if (copy_tasks[person][TaskStatus::IN_PROGRESS] != 0)
        {
        	if (updatedTasks.find(TaskStatus::IN_PROGRESS) != updatedTasks.end())
        		legacyTasks[TaskStatus::IN_PROGRESS] = copy_tasks[person][TaskStatus::IN_PROGRESS] - updatedTasks[TaskStatus::IN_PROGRESS];
        	else
        		legacyTasks[TaskStatus::IN_PROGRESS] = copy_tasks[person][TaskStatus::IN_PROGRESS];
        }

        if (copy_tasks[person][TaskStatus::TESTING] != 0)
        {
        	if (updatedTasks.find(TaskStatus::TESTING) != updatedTasks.end())
        		legacyTasks[TaskStatus::TESTING] = copy_tasks[person][TaskStatus::TESTING] - updatedTasks[TaskStatus::TESTING];
        	else
        		legacyTasks[TaskStatus::TESTING] = copy_tasks[person][TaskStatus::TESTING];
        }

        tasks = copy_tasks;

        return std::tie(updatedTasks, legacyTasks);        
    }

private:
    std::map<std::string, TasksInfo> tasks;

};

void PrintTasksInfo(TasksInfo tasks_info) {
    std::cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
    ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
    ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
    ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << std::endl;
}

int main()
{
    TeamTasks tasks;

    tasks.AddNewTask("Ilia");
    
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }

    std::cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));

    std::cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);

    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);

    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);

    std::cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);

    std::cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}
