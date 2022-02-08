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
    public:
        std::coroutine_handle<promise_type> m_handle;
    };




    struct Action
    {
        void operator delete(void*)
        {

        }
        struct promise_type
        {
            ver::Action get_return_object() noexcept
            {
                printf("%s\n", __FUNCTION__);
                return ver::Action{ std::coroutine_handle<promise_type>::from_promise(*this), *this };
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
            std::suspend_always yield_value()noexcept
            {
                return{};
            }

            std::suspend_always unhandled_exception() const noexcept
            {
                printf("%s\n", __FUNCTION__);
                return {};
            }
        };
    public:
        explicit Action(std::coroutine_handle<promise_type> handle, promise_type& promise)
            : m_handle(handle), promise(promise)
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
        auto yield()
        {
            return promise.yield_value();
        }
    public:
        std::coroutine_handle<promise_type> m_handle;
        promise_type& promise;
    };

    struct ResumableAction
    {
        struct promise_type
        {
            ver::ResumableAction get_return_object() noexcept
            {
                printf("%s\n", __FUNCTION__);
                return ver::ResumableAction{ std::coroutine_handle<promise_type>::from_promise(*this) };
            }

            void return_void() const noexcept
            {
                printf("%s\n", __FUNCTION__);
            }

            std::suspend_never initial_suspend() const noexcept
            {
                printf("%s\n", __FUNCTION__);
                return{};
            }

            std::suspend_always final_suspend() const noexcept
            {
                printf("%s\n", __FUNCTION__);
                return{};
            }
            std::suspend_always yield_value()noexcept
            {
                return{};
            }

            std::suspend_always unhandled_exception() const noexcept
            {
                printf("%s\n", __FUNCTION__);
                return {};
            }
        };
    public:
        explicit ResumableAction(std::coroutine_handle<promise_type> handle)
            : m_handle(handle)
        {
            printf("%s\n", __FUNCTION__);
        }
        ~ResumableAction()
        {
            printf("%s\n", __FUNCTION__);
            if (m_handle)m_handle.destroy();
        }
        //ResumableAction(const ResumableAction&) = delete;
        //ResumableAction& operator=(const ResumableAction&) = delete;
    public:
        void resume()const
        {
            m_handle.resume();
        }
        void resume_parent()const
        {
            m_parenthandle.resume();
        }
    public:
        std::coroutine_handle<promise_type> m_handle;
        std::coroutine_handle<> m_parenthandle;
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

    template <>
    struct await_adapter<ResumableAction>
    {
        await_adapter(ResumableAction& async) : async(async){ printf("%s\n", __FUNCTION__); }

        ResumableAction& async;


        bool await_ready() const noexcept
        {
            printf("%s\n", __FUNCTION__);
            return true;
        }

        bool await_suspend(std::coroutine_handle<> handle)
        {
            printf("%s\n", __FUNCTION__);
            async.m_parenthandle = handle;
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
    inline await_adapter<ResumableAction> operator co_await(ResumableAction& async)
    {
        return{ async };
    }
}
