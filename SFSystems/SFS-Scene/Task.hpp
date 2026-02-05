#pragma once
#ifndef TASK_HPP_
#define TASK_HPP_
#include "framework.h"
#include <queue>
#include <memory>

namespace SFS {

	template <typename T>
	class BaseTask {
	public:
		virtual void doTask(T& object) = 0;
	};

	template<typename T>
	class TaskQueue {
	private:
		std::queue<std::shared_ptr<BaseTask<T>>> tasks;
	public:
		void addTask(BaseTask<T>* newTask);
		void executeTask(T& executor);
		void executeAll(T& executor);
		void clear();
	};
}

#include "Task.inl"

#endif