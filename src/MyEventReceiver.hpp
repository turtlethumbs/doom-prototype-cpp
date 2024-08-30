#ifndef MY_EVENT_RECEIVER_HPP
#define MY_EVENT_RECEIVER_HPP

#include <irrlicht.h>

using namespace irr;

class MyEventReceiver : public IEventReceiver
{
public:
    MyEventReceiver();

    bool OnEvent(const SEvent& event) override;

    bool IsKeyDown(EKEY_CODE keyCode) const;
    bool IsMouseButtonDown(int buttonIndex) const; // Change to accept button index
    bool IsMouseButtonJustPressed(int buttonIndex) const; // Method to check single press

    void ResetMouseButtonPressState(); // Method to reset the state

private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    bool mouseButtonStates[3]; // 0: Left, 1: Right, 2: Middle
    bool mouseButtonJustPressed[3]; // Track if button was just pressed
};

#endif // MY_EVENT_RECEIVER_HPP
