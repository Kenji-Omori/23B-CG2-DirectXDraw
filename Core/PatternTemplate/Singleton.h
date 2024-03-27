#pragma once


namespace Core
{
	template<class T>
	class Singleton {
	public:

	static T* GetInstance() {
		if (isntance_ == nullptr) { CreateInstance(); }
		return isntance_;
	}



	protected:
		Singleton() = default;
		const Singleton& operator=(const Singleton& other) {}
		Singleton(const Singleton& other) = delete;

	private:
		static T* isntance_;
//		T& operator=(const T&) = delete;

		static void CreateInstance() {
			isntance_ = new T();
		}
	};
}

