/// \file KeyBuffer.hpp
/// \brief Implementation of KeyBuffer class and any associated global functions.
/// \author John Shenk
/// \version A04

#include "KeyBuffer.hpp"

/// \brief Constructs a new KeyBuffer.
/// \postcondition All keys are assumed to be "up".
KeyBuffer::KeyBuffer ()
{
    for(size_t x = 0; x <= (GLFW_KEY_LAST + 1); ++x)
    {
        keyIsPressed[x] = false;
    }
}

/// \brief Records that a key is "down".
/// \param[in] key The key that was pressed (a GLFW_KEY_? constant).
/// \postcondition That key is "down".
void
KeyBuffer::setKeyDown (int key)
{
    keyIsPressed[key] = true;
}

/// \brief Sets all keys to "up".
/// \postcondition All keys are assumed to be "up".
void
KeyBuffer::reset ()
{
    for(size_t x = 0; x <= (GLFW_KEY_LAST + 1); ++x)
    {
        keyIsPressed[x] = false;
    }
}

/// \brief Records that a key is "up".
/// \param[in] key The key that was released (a GLFW_KEY_?) constant).
/// \postcondition That key is "up".
void
KeyBuffer::setKeyUp (int key)
{
    
    keyIsPressed[key] = false;
}

/// \brief Checks whether or not a key "down".
/// \parm[in] key The key that you want to know about (a GLFW_KEY_? constant).
/// \return True if that key is "down", otherwise false.
bool
KeyBuffer::isKeyDown (int key) const
{
    return keyIsPressed[key];
}
