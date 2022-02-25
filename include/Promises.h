#pragma once
#include <coroutine>
#include <optional>

#include <queue>

std::queue<std::coroutine_handle<>> scheduler;

namespace ver
{
	//struct fire_and_forget
	//{
	//	struct promise_type
	//	{
	//		auto get_return_object() noexcept {
	//			return ver::fire_and_forget{ std::coroutine_handle<promise_type>::from_promise(*this) };
	//		}
	//		void return_void() const noexcept {}
	//		std::suspend_never initial_suspend() const noexcept { return{}; }
	//		std::suspend_never final_suspend() const noexcept { return{}; }
	//		void unhandled_exception() const noexcept {}
	//	};
	//public:
	//	explicit fire_and_forget(std::coroutine_handle<promise_type> handle)
	//		: m_handle(handle) {}
	//public:
	//	std::coroutine_handle<promise_type> m_handle;
	//};


	template <typename T, typename _Enable = void>
	struct promise_return_base;

	template <typename T>
	struct promise_return_base<T, std::enable_if_t<std::is_void_v<T>>>
	{
	public:
		void return_void() {}
	};

	template <typename T>
	struct promise_return_base<T, std::enable_if_t<!std::is_void_v<T>>>
	{
		std::optional<T> value;
	public:
		void return_value(T&& xvalue) { value = xvalue; }
	};

	template<std::floating_point U>
	struct time_awaiter
	{
		U value;
	public:
		bool await_ready() { return false; }
		auto await_suspend(std::coroutine_handle<> handle) {
			if (!handle.done())
				scheduler.push(handle);
			scheduler.pop();
			return scheduler.front();
		}
		U await_resume() { return value; }
	};

	template<typename T, class _Initial>
	struct basic_action
	{
		struct promise_type : public promise_return_base<T>
		{
			auto get_return_object() noexcept {
				return ver::basic_action<T, _Initial>{ std::coroutine_handle<basic_action<T, _Initial>::promise_type>::from_promise(*this) };
			}
			_Initial initial_suspend() const noexcept { return{}; }
			std::suspend_always final_suspend() const noexcept { return{}; }
			void unhandled_exception() const noexcept { std::terminate(); }

			template<typename U>
			auto await_transform(U&& val) { return val; }

			template<std::floating_point U>
			auto await_transform(U&& val) { return time_awaiter<U>{val}; }
		};
	public:
		using value_type = std::conditional_t<std::is_void_v<T>, void, std::optional<T>&>;
		explicit basic_action(std::coroutine_handle<promise_type> handle)
			: m_handle(handle) {}
		~basic_action() {
			if (m_handle)m_handle.destroy();
		}

		bool await_ready() { return false; }
		auto await_suspend(std::coroutine_handle<> handle) {
			if (!handle.done())
				scheduler.push(handle);
			scheduler.pop();
			return scheduler.front();
		}
		value_type await_resume()
		{
			if constexpr (!std::is_void_v<T>)
				return m_handle.promise().value;
		}
		value_type get() { return await_resume(); }
	public:
		std::coroutine_handle<promise_type> m_handle;
	};

	using action = basic_action<void, std::suspend_never>;
	using delayed_action = basic_action<void, std::suspend_always>;
	template<typename T>using operation = basic_action<T, std::suspend_never>;
	template<typename T>using delayed_operation = basic_action<T, std::suspend_always>;
}
