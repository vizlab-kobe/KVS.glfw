/*****************************************************************************/
/**
 *  @file   KVSKey.h
 *  @author Naohisa Sakamoto
 */
/*****************************************************************************/
#pragma once
#include <kvs/Key>


namespace kvs
{

namespace glfw
{

class KVSKey
{
public:
    static int Code( const int key );
    static int Modifier( const int modifier );
};

inline int KVSKey::Code( const int key )
{
    switch ( key )
    {
    case GLFW_KEY_ESCAPE:     return kvs::Key::Escape;
    case GLFW_KEY_BACKSPACE:  return kvs::Key::BackSpace;
    case GLFW_KEY_TAB:        return kvs::Key::Tab;
    case GLFW_KEY_SPACE:      return kvs::Key::Space;
    case GLFW_KEY_APOSTROPHE: return kvs::Key::Apostrophe;
    case GLFW_KEY_COMMA:      return kvs::Key::Comma;
    case GLFW_KEY_MINUS:      return kvs::Key::Minus;
    case GLFW_KEY_PERIOD:     return kvs::Key::Period;
    case GLFW_KEY_SLASH:      return kvs::Key::Slash;
    case GLFW_KEY_SEMICOLON:  return kvs::Key::Semicolon;
    case GLFW_KEY_EQUAL:      return kvs::Key::Equal;
    case GLFW_KEY_LEFT_BRACKET: return kvs::Key::BracketLeft;
    case GLFW_KEY_BACKSLASH:  return kvs::Key::Backslash;
    case GLFW_KEY_RIGHT_BRACKET: return kvs::Key::BracketRight;
    case GLFW_KEY_GRAVE_ACCENT: return kvs::Key::QuoteLeft;
    case GLFW_KEY_0:          return kvs::Key::Zero;
    case GLFW_KEY_1:          return kvs::Key::One;
    case GLFW_KEY_2:          return kvs::Key::Two;
    case GLFW_KEY_3:          return kvs::Key::Three;
    case GLFW_KEY_4:          return kvs::Key::Four;
    case GLFW_KEY_5:          return kvs::Key::Five;
    case GLFW_KEY_6:          return kvs::Key::Six;
    case GLFW_KEY_7:          return kvs::Key::Seven;
    case GLFW_KEY_8:          return kvs::Key::Eight;
    case GLFW_KEY_9:          return kvs::Key::Nine;
    case GLFW_KEY_A:          return kvs::Key::a;
    case GLFW_KEY_B:          return kvs::Key::b;
    case GLFW_KEY_C:          return kvs::Key::c;
    case GLFW_KEY_D:          return kvs::Key::d;
    case GLFW_KEY_E:          return kvs::Key::e;
    case GLFW_KEY_F:          return kvs::Key::f;
    case GLFW_KEY_G:          return kvs::Key::g;
    case GLFW_KEY_H:          return kvs::Key::h;
    case GLFW_KEY_I:          return kvs::Key::i;
    case GLFW_KEY_J:          return kvs::Key::j;
    case GLFW_KEY_K:          return kvs::Key::k;
    case GLFW_KEY_L:          return kvs::Key::l;
    case GLFW_KEY_M:          return kvs::Key::m;
    case GLFW_KEY_N:          return kvs::Key::n;
    case GLFW_KEY_O:          return kvs::Key::o;
    case GLFW_KEY_P:          return kvs::Key::p;
    case GLFW_KEY_Q:          return kvs::Key::q;
    case GLFW_KEY_R:          return kvs::Key::r;
    case GLFW_KEY_S:          return kvs::Key::s;
    case GLFW_KEY_T:          return kvs::Key::t;
    case GLFW_KEY_U:          return kvs::Key::u;
    case GLFW_KEY_V:          return kvs::Key::v;
    case GLFW_KEY_W:          return kvs::Key::w;
    case GLFW_KEY_X:          return kvs::Key::x;
    case GLFW_KEY_Y:          return kvs::Key::y;
    case GLFW_KEY_Z:          return kvs::Key::z;
    case GLFW_KEY_F1:         return kvs::Key::F1;
    case GLFW_KEY_F2:         return kvs::Key::F2;
    case GLFW_KEY_F3:         return kvs::Key::F3;
    case GLFW_KEY_F4:         return kvs::Key::F4;
    case GLFW_KEY_F5:         return kvs::Key::F5;
    case GLFW_KEY_F6:         return kvs::Key::F6;
    case GLFW_KEY_F7:         return kvs::Key::F7;
    case GLFW_KEY_F8:         return kvs::Key::F8;
    case GLFW_KEY_F9:         return kvs::Key::F9;
    case GLFW_KEY_F10:        return kvs::Key::F10;
    case GLFW_KEY_F11:        return kvs::Key::F11;
    case GLFW_KEY_F12:        return kvs::Key::F12;
    case GLFW_KEY_LEFT:       return kvs::Key::Left;
    case GLFW_KEY_RIGHT:      return kvs::Key::Right;
    case GLFW_KEY_UP:         return kvs::Key::Up;
    case GLFW_KEY_DOWN:       return kvs::Key::Down;
    case GLFW_KEY_PAGE_UP:    return kvs::Key::PageUp;
    case GLFW_KEY_PAGE_DOWN:  return kvs::Key::PageDown;
    case GLFW_KEY_HOME:       return kvs::Key::Home;
    case GLFW_KEY_END:        return kvs::Key::End;
    case GLFW_KEY_INSERT:     return kvs::Key::Insert;
    default:                  break;
    }

    return key;
}

inline int KVSKey::Modifier( const int modifier )
{
    switch ( modifier )
    {
    case GLFW_MOD_SHIFT: return kvs::Key::ShiftModifier;
    case GLFW_MOD_CONTROL: return kvs::Key::ControlModifier;
    case GLFW_MOD_ALT: return kvs::Key::AltModifier;
    default: break;
    }

    return modifier;
}

} // end of namespace glfw

} // end of namespace kvs
