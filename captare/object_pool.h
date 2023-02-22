#pragma once

#include "chess.h"

namespace chess
{
	template <class T>
	class object_pool
	{
	private:
		std::vector<T*> _inuse{};
		std::vector<T*> _ready{};

	public:
		object_pool(int capacity, int preallocate = 0);
		~object_pool();

		T& get();
		void put(T& obj);
	};

	template<class T>
	object_pool<T>::object_pool(int capacity, int preallocate)
	{
		_inuse.reserve(capacity);
		_ready.reserve(capacity);
		for (int n = 0; n < preallocate; ++n)
		{
			_ready.push_back(new T{});
		}
	}

	template<class T>
	object_pool<T>::~object_pool()
	{
		for (auto obj : _inuse)
		{
			delete obj;
		}

		for (auto obj : _ready)
		{
			delete obj;
		}
	}

	template<class T>
	T& object_pool<T>::get()
	{
		if (!_ready.empty())
		{
			T* obj = *_ready.rbegin();
			_ready.pop_back();
			_inuse.push_back(obj);
			return *obj;
		}
		T* obj = new T{};
		_inuse.push_back(obj);
		return *obj;
	}

	template<class T>
	void object_pool<T>::put(T& obj)
	{
		auto iter = std::find(_inuse.begin(), _inuse.end(), &obj);
		if (iter != _inuse.end())
		{
			obj.clear();
			_ready.push_back(&obj);
			_inuse.erase(iter);
		}
	}
}
