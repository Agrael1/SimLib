#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <array>
#include <ranges>

#define LIST_WARN_LVL\
	X(Info)\
	X(Warning)\
	X(Error)

class Message
{
public:
	enum class Level
	{
#define X(a) a,
		LIST_WARN_LVL
#undef X
		size
	};
	static constexpr std::array<std::string_view, size_t(Level::size)> levels =
	{
#define X(a) #a,
		LIST_WARN_LVL
#undef X
	};
public:
	Message(Level lvl) :lvl(lvl) {}
public:
	Message& operator<<(std::string_view message) {
		msg += message;
		return *this;
	}
	auto level()const noexcept {
		return lvl;
	}
	std::string_view Text()const noexcept{
		return msg;
	}
private:
	std::string msg;
	Level lvl;
};

class Log
{
public:
	~Log() = default;
public:
	static Message& Info() {
		return instance().MakeMessage(Message::Level::Info);
	}
	static Message& Warning() {
		return instance().MakeMessage(Message::Level::Warning);
	}
	static Message& Error() {
		return instance().MakeMessage(Message::Level::Error);
	}
	static auto Infos()
	{
		return instance().MakeView < Message::Level::Info>();
	}
	static auto Warnings()
	{
		return instance().MakeView < Message::Level::Warning>();
	}
	static auto Errors()
	{
		return instance().MakeView< Message::Level::Info >();
	}
private:
	Message& MakeMessage(Message::Level lvl)
	{
		return msgvec.emplace_back(lvl);
	}
	template<Message::Level lvl>
	auto MakeView()const
	{
		return msgvec | std::views::filter([this](const Message& x) {return x.level() == lvl; });
	}
public:
	void Print();
	static Log& instance()
	{
		static Log log;
		return log;
	}
private:
	std::vector<Message> msgvec;
};