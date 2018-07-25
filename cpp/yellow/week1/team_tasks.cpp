#include <iostream>
#include <string>
#include <map>
#include <string>
#include <tuple>

using namespace std;

/*
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

using TasksInfo = map<TaskStatus, int>;
*/

class TeamTasks {
public:
	const TasksInfo& GetPersonTasksInfo(const string& person) const;
	void AddNewTask(const string& person);
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person,
							int task_count);

private:
	map<string, TasksInfo> team;
};

void TeamTasks::AddNewTask(const string &person)
{
	team[person][TaskStatus::NEW]++;
}

const TasksInfo &TeamTasks::GetPersonTasksInfo(const string &person) const
{
	return team.at(person);
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string& person,
						int task_count) {
	TasksInfo &all_tasks = team[person];
	TasksInfo new_tasks, old_tasks;

	int undone_cnt = all_tasks[TaskStatus::NEW] +
			all_tasks[TaskStatus::IN_PROGRESS] +
			all_tasks[TaskStatus::TESTING];
	task_count = min(task_count, undone_cnt);

	/* Touch all_tasks[TaskStatus::DONE] */
	all_tasks[TaskStatus::DONE];

	int perform = 0;
	for (const auto &ti : all_tasks) {
		TaskStatus status = ti.first;
		int cnt = ti.second;

		if (perform > 0)
			new_tasks[status] = perform;

		if (task_count < cnt) {
			perform = task_count;
			old_tasks[status] = cnt - task_count;
			task_count = 0;
		}
		else {
			perform = cnt;
			task_count -= cnt;
		}
	}

	for (const auto &ti : all_tasks) {
		TaskStatus status = ti.first;
		int cnt_all = 0;
		if (new_tasks.count(status))
			cnt_all += new_tasks.at(status);
		if (old_tasks.count(status))
			cnt_all += old_tasks.at(status);

		if (cnt_all > 0)
			all_tasks[status] = cnt_all;
		else
			all_tasks.erase(status);
	}

	/* No need to report about old done tasks */
	if (old_tasks.count(TaskStatus::DONE))
		old_tasks.erase(TaskStatus::DONE);

	return make_tuple(new_tasks, old_tasks);
}

/*
int main()
{
	TeamTasks tasks;

	for (int i = 0; i < 5; i++)
		tasks.AddNewTask("Alice");
	tasks.PerformPersonTasks("Alice", 5);
	tasks.PerformPersonTasks("Alice", 5);
	tasks.PerformPersonTasks("Alice", 1);

	return 0;
}
*/
