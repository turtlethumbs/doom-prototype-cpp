#include "MyEventReceiver.hpp"

MyEventReceiver::MyEventReceiver()
{
    for (u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;

    for (int i = 0; i < 3; ++i)
    {
        mouseButtonStates[i] = false;
        mouseButtonJustPressed[i] = false; // Initialize the just pressed states
    }
}

bool MyEventReceiver::OnEvent(const SEvent& event)
{
    // Handle key events
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    // Handle mouse events
    else if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        switch (event.MouseInput.Event)
        {
            case irr::EMIE_LMOUSE_PRESSED_DOWN:
                mouseButtonStates[0] = true;
                mouseButtonJustPressed[0] = true; // Mark as just pressed
                break;
            case irr::EMIE_LMOUSE_LEFT_UP:
                mouseButtonStates[0] = false;
                mouseButtonJustPressed[0] = false; // Mark as released
                break;
            case irr::EMIE_RMOUSE_PRESSED_DOWN:
                mouseButtonStates[1] = true;
                mouseButtonJustPressed[1] = true; // Mark as just pressed
                break;
            case irr::EMIE_RMOUSE_LEFT_UP:
                mouseButtonStates[1] = false;
                mouseButtonJustPressed[1] = false; // Mark as released
                break;
            case irr::EMIE_MMOUSE_PRESSED_DOWN:
                mouseButtonStates[2] = true;
                mouseButtonJustPressed[2] = true; // Mark as just pressed
                break;
            case irr::EMIE_MMOUSE_LEFT_UP:
                mouseButtonStates[2] = false;
                mouseButtonJustPressed[2] = false; // Mark as released
                break;
            default:
                break;
        }
    }

    return false;
}

bool MyEventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

bool MyEventReceiver::IsMouseButtonDown(int buttonIndex) const
{
    if (buttonIndex >= 0 && buttonIndex < 3)
        return mouseButtonStates[buttonIndex];
    return false;
}

bool MyEventReceiver::IsMouseButtonJustPressed(int buttonIndex) const
{
    if (buttonIndex >= 0 && buttonIndex < 3)
        return mouseButtonJustPressed[buttonIndex];
    return false;
}

void MyEventReceiver::ResetMouseButtonPressState()
{
    for (int i = 0; i < 3; ++i)
    {
        mouseButtonJustPressed[i] = false; // Reset all button press states
    }
}
