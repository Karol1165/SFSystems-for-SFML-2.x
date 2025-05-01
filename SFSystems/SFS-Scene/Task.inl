#include "pch.h"
#include "Task.hpp"


namespace SFS {

	template<typename T>
	void TaskQueue<T>::addTask(BaseTask<T>* newTask) {
		this->tasks.push(std::unique_ptr<BaseTask<T>>(newTask));
	}
	template<typename T>
	void TaskQueue<T>::executeTask(T& executor) {
		this->tasks.front()->doTask(executor);
		this->tasks.pop();
	}
	template<typename T>
	void TaskQueue<T>::executeAll(T& executor) {
		while (!this->tasks.empty()) {
			this->executeTask(executor);
		}
	}
	template<typename T>
	void TaskQueue<T>::clear() {
		while (!this->tasks.empty()) {
			this->tasks.pop();
		}
	}

}