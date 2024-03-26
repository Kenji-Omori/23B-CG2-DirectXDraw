#pragma once


namespace Core
{
	template<class T = int>
	class Singleton {
	public:

	static T* GetInstance() {
		if (isntance == nullptr) { CreateInstance(); }
		return isntance;
	}



	protected:
		Singleton() {}

	private:
		static T* isntance;
		Singleton() = default;
		Singleton(const Singleton& other) = delete;
		T& operator=(const T&) = delete;

		const Singleton& operator=(const Singleton& other) {}
		static void CreateInstance() {
			isntance = new T();
		}

	};

}