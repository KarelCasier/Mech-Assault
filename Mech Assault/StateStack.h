#pragma once

#include <SFML/Graphics/NonCopyable.hpp>

class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };
    
public:
    explicit            StateStack(State::Context context);
    
    template <typename T>
    void                registerState(States::ID stateID);
    
    void                update(sf::Time dt);
    void                draw();
    void                handleEvent(const sf::Event& event);
    
    void                pushState(States::ID stateID);
    void                popState();
    void                clearState();
    
    bool                isEmpty() const;
    
private:
    State::Ptr          createState(States::ID stateID);
    void                applyPendingChanges();
    
private:
    struct PendingChange
    {
        Action          action;
        States::ID      stateID;
    };
    
private:
    std::vector<State::Ptr>                             mStack;
    std::vector<PendingChange>                          mPendingList;
    State::Context                                      mContext;
    std::map<States::ID, std::function<State::Ptr()>>   mFactories;
};