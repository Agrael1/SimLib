#pragma once

class Entity
{
public:
    virtual void Activate(double period);       //!< activate after certain period (schedule)
    virtual void Passivate();                   //!< deactivation
    virtual void Terminate() = 0;               //!< end Behavior() and remove entity
    virtual void Behavior() = 0;               //!< end Behavior() and remove entity
private:

};

