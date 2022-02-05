#pragma once
#include <coroutine>

namespace ver
{
    struct fire_and_forget
    {
        struct promise
        {
            ver::fire_and_forget get_return_object() noexcept
            {
                return ver::fire_and_forget{ std::coroutine_handle<promise>::from_promise(*this) };
            }

            constexpr void return_void() const noexcept
            {
            }

            constexpr std::suspend_never initial_suspend() const noexcept
            {
                return{};
            }

            constexpr std::suspend_never final_suspend() const noexcept
            {
                return{};
            }

            constexpr void unhandled_exception() const noexcept
            {

            }
        };
    public:
        using promise_type = promise;
        explicit fire_and_forget(std::coroutine_handle<promise_type> handle)
            : m_handle(handle)
        {
            printf("%s\n", __FUNCTION__);
        }
        ~fire_and_forget()
        {
            printf("%s\n", __FUNCTION__);
        }
    private:
        std::coroutine_handle<promise_type> m_handle;
    };




    struct Action
    {
        struct promise_type
        {
            ver::Action get_return_object() noexcept
            {
                printf("%s\n", __FUNCTION__);
                return ver::Action{ std::coroutine_handle<promise_type>::from_promise(*this) };
            }

            void return_void() const noexcept
            {
                printf("%s\n", __FUNCTION__);
            }

            std::suspend_always initial_suspend() const noexcept
            {
                printf("%s\n", __FUNCTION__);
                return{};
            }

            std::suspend_always final_suspend() const noexcept
            {
                printf("%s\n", __FUNCTION__);
                return{};
            }

            void unhandled_exception() const noexcept
            {
                printf("%s\n", __FUNCTION__);
            }
        };
    public:
        explicit Action(std::coroutine_handle<promise_type> handle)
            : m_handle(handle)
        {
            printf("%s\n", __FUNCTION__);
        }
        ~Action()
        {
            printf("%s\n", __FUNCTION__);
            if(m_handle)m_handle.destroy();
        }
        Action(const Action&) = delete;
        Action& operator=(const Action&) = delete;
    public:
        void resume()const
        {
            m_handle.resume();
        }
    private:
        std::coroutine_handle<promise_type> m_handle;
    };


    template <typename Async>
    struct await_adapter
    {
        await_adapter(Async const& async) : async(async) { printf("%s\n", __FUNCTION__); }

        Async const& async;


        bool await_ready() const noexcept
        {
            printf("%s\n", __FUNCTION__);
            return true;
        }

        bool await_suspend(std::coroutine_handle<> handle)
        {
            printf("%s\n", __FUNCTION__);
            return true;
        }

        auto await_resume() const
        {
            printf("%s\n", __FUNCTION__);
            async.resume();
        }
    private:
    };

    inline await_adapter<Action> operator co_await(Action const& async)
    {
        return{ async };
    }
}
