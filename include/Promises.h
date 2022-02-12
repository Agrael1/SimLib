#pragma once
#include <coroutine>
#include <optional>

namespace ver
{
    struct fire_and_forget
    {
        struct promise_type
        {
            ver::fire_and_forget get_return_object() noexcept{
                return { std::coroutine_handle<promise_type>::from_promise(*this) };
            }

            constexpr void return_void() const noexcept{}

            constexpr std::suspend_never initial_suspend() const noexcept{
                return{};
            }

            constexpr std::suspend_never final_suspend() const noexcept{
                return{};
            }

            constexpr void unhandled_exception() const noexcept{}
        };
    public:
        fire_and_forget(std::coroutine_handle<promise_type> handle)
            : m_handle(handle)
        {
            printf("%s\n", __FUNCTION__);
        }
        ~fire_and_forget()
        {
            printf("%s\n", __FUNCTION__);
        }
    public:
        std::coroutine_handle<promise_type> m_handle;
    };

    template <typename T>
    struct task
    {
        struct promise_type
        {
            std::optional<T>    m_value{};
            std::coroutine_handle<promise_type> m_inner_handler{};
            std::coroutine_handle<promise_type> m_outer_handler{};

            auto value()
            {
                return m_value;
            }

            auto initial_suspend()
            {
                return std::suspend_always{};
            }

            auto final_suspend() noexcept
            {
                return std::suspend_always{};
            }

            void return_value(T t)
            {
                m_value = t;
            }

            task<T> get_return_object()
            {
                return { handle_type::from_promise(*this) };
            }

            void unhandled_exception()
            {
                std::terminate();
            }

            void rethrow_if_unhandled_exception()
            {

            }
        };
    public:
        using handle_type = std::coroutine_handle<promise_type>;
        mutable handle_type m_handle;

        task(handle_type handle)
            : m_handle(handle)
        {}
        task(task&& other) noexcept
            : m_handle(other.m_handle)
        {
            other.m_handle = nullptr;
        }
        ~task()
        {
            if (m_handle)
                m_handle.destroy();
        }
    public:
        bool await_ready(){
            return !m_handle || m_handle.done();
        }

        bool await_suspend(std::coroutine_handle<> handle){
            return true;
        }
        auto await_suspend(std::coroutine_handle<promise_type> handle)
        {
            m_handle.resume();
            handle.promise().m_inner_handler = m_handle;
            m_handle.promise().m_outer_handler = handle;
            return handle;
        }
        auto await_resume(){
            return *m_handle.promise().m_value;
        }

        //manualy wait for finish
        bool one_step()
        {
            auto curr = m_handle;
            while (curr)
            {
                if (!curr.promise().m_inner_handler)
                {
                    while (!curr.done())
                    {
                        curr.resume();
                        if (!curr.done())
                            return true;
                        if (curr.promise().m_outer_handler)
                        {
                            curr = curr.promise().m_outer_handler;
                            curr.promise().m_inner_handler = nullptr;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    break;
                }
                curr = curr.promise().m_inner_handler;
            }
            return !curr.done();
        }
    };
}
