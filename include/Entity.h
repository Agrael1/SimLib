#pragma once
#include <memory>

class B;


class Entity
{
public:
    //~Entity();
private:
    std::unique_ptr<B> cp;
};

