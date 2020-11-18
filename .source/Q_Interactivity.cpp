#include "Q_Interactivity.h"


extern "C" int getCursorPosition(lua_State * L)
{
	lua_pushnumber(L, event.motion.x);
	lua_pushnumber(L, event.motion.y);
	return 2;
}


extern "C" int getScrollValue(lua_State * L)
{
	lua_pushnumber(L, abs(event.wheel.y) > 0 ? abs(event.wheel.y) : abs(event.wheel.x));
	return 1;
}


extern "C" int updateEvent(lua_State * L)
{
	if (SDL_PollEvent(&event))
	{
		lua_pushnumber(L, 0);
	}
	else
	{
		lua_pushnumber(L, -1);
	}
	return 1;
}


extern "C" int getEventType(lua_State * L)
{
	string prefix = "";
	string suffix = "";
	string keyResult = "";
	switch (event.type)
	{
	case SDL_QUIT:
		lua_pushstring(L, "QUIT");
		break;
	case SDL_MOUSEMOTION:
		lua_pushstring(L, "MOUSEMOTION");
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			lua_pushstring(L, "MOUSEBUTTON_D_L");
			break;
		case SDL_BUTTON_RIGHT:
			lua_pushstring(L, "MOUSEBUTTON_D_R");
			break;
		case SDL_BUTTON_MIDDLE:
			lua_pushstring(L, "MOUSEBUTTON_D_M");
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		switch (event.button.button)
		{
		case SDL_BUTTON_LEFT:
			lua_pushstring(L, "MOUSEBUTTON_U_L");
			break;
		case SDL_BUTTON_RIGHT:
			lua_pushstring(L, "MOUSEBUTTON_U_R");
			break;
		case SDL_BUTTON_MIDDLE:
			lua_pushstring(L, "MOUSEBUTTON_U_M");
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEWHEEL:
		if (event.wheel.y > 0)
		{
			lua_pushstring(L, "MOUSESCROLL_U");
		}
		else if (event.wheel.y < 0)
		{
			lua_pushstring(L, "MOUSESCROLL_D");
		}
		else if (event.wheel.x > 0)
		{
			lua_pushstring(L, "MOUSESCROLL_R");
		}
		else if (event.wheel.x < 0)
		{
			lua_pushstring(L, "MOUSESCROLL_L");
		}
		break;
	case SDL_WINDOWEVENT:
		switch (event.window.event)
		{
		case SDL_WINDOWEVENT_SHOWN:
			lua_pushstring(L, "WINDOWSHOW");
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			lua_pushstring(L, "WINDOWHIDE");
			break;
		case SDL_WINDOWEVENT_MOVED:
			lua_pushstring(L, "WINDOWMOVE");
			break;
		case SDL_WINDOWEVENT_RESIZED:
			lua_pushstring(L, "WINDOWRESIZE");
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			lua_pushstring(L, "WINDOWMINSIZE");
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			lua_pushstring(L, "WINDOWMAXSIZE");
			break;
		case SDL_WINDOWEVENT_ENTER:
			lua_pushstring(L, "WINDOWENTER");
			break;
		case SDL_WINDOWEVENT_LEAVE:
			lua_pushstring(L, "WINDOWLEAVE");
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			lua_pushstring(L, "WINDOWFOCUS");
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			lua_pushstring(L, "WINDOWLOST");
			break;
		case SDL_WINDOWEVENT_CLOSE:
			lua_pushstring(L, "WINDOWCLOSE");
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		prefix = event.type == SDL_KEYUP ? "KEYUP_" : "KEYDOWN_";
		switch (event.key.keysym.sym)
		{
		case SDLK_0:
		case SDLK_KP_0:
			keyResult = prefix + "0";
			break;
		case SDLK_KP_00:
			keyResult = prefix + "00";
			break;
		case SDLK_KP_000:
			keyResult = prefix + "000";
			break;
		case SDLK_1:
		case SDLK_KP_1:
			keyResult = prefix + "1";
			break;
		case SDLK_2:
		case SDLK_KP_2:
			keyResult = prefix + "2";
			break;
		case SDLK_3:
		case SDLK_KP_3:
			keyResult = prefix + "3";
			break;
		case SDLK_4:
		case SDLK_KP_4:
			keyResult = prefix + "4";
			break;
		case SDLK_5:
		case SDLK_KP_5:
			keyResult = prefix + "5";
			break;
		case SDLK_6:
		case SDLK_KP_6:
			keyResult = prefix + "6";
			break;
		case SDLK_7:
		case SDLK_KP_7:
			keyResult = prefix + "7";
			break;
		case SDLK_8:
		case SDLK_KP_8:
			keyResult = prefix + "8";
			break;
		case SDLK_9:
		case SDLK_KP_9:
			keyResult = prefix + "9";
			break;
		case SDLK_F1:
			keyResult = prefix + "F1";
			break;
		case SDLK_F2:
			keyResult = prefix + "F2";
			break;
		case SDLK_F3:
			keyResult = prefix + "F3";
			break;
		case SDLK_F4:
			keyResult = prefix + "F4";
			break;
		case SDLK_F5:
			keyResult = prefix + "F5";
			break;
		case SDLK_F6:
			keyResult = prefix + "F6";
			break;
		case SDLK_F7:
			keyResult = prefix + "F7";
			break;
		case SDLK_F8:
			keyResult = prefix + "F8";
			break;
		case SDLK_F9:
			keyResult = prefix + "F9";
			break;
		case SDLK_F10:
			keyResult = prefix + "F10";
			break;
		case SDLK_F11:
			keyResult = prefix + "F11";
			break;
		case SDLK_F12:
			keyResult = prefix + "F12";
			break;
		case SDLK_F13:
			keyResult = prefix + "F13";
			break;
		case SDLK_F14:
			keyResult = prefix + "F14";
			break;
		case SDLK_F15:
			keyResult = prefix + "F15";
			break;
		case SDLK_F16:
			keyResult = prefix + "F16";
			break;
		case SDLK_F17:
			keyResult = prefix + "F17";
			break;
		case SDLK_F18:
			keyResult = prefix + "F18";
			break;
		case SDLK_F19:
			keyResult = prefix + "F19";
			break;
		case SDLK_F20:
			keyResult = prefix + "F20";
			break;
		case SDLK_F21:
			keyResult = prefix + "F21";
			break;
		case SDLK_F22:
			keyResult = prefix + "F22";
			break;
		case SDLK_F23:
			keyResult = prefix + "F23";
			break;
		case SDLK_F24:
			keyResult = prefix + "F24";
			break;
		case SDLK_a:
		case SDLK_KP_A:
			keyResult = prefix + "A";
			break;
		case SDLK_b:
		case SDLK_KP_B:
			keyResult = prefix + "B";
			break;
		case SDLK_c:
		case SDLK_KP_C:
			keyResult = prefix + "C";
			break;
		case SDLK_d:
		case SDLK_KP_D:
			keyResult = prefix + "D";
			break;
		case SDLK_e:
		case SDLK_KP_E:
			keyResult = prefix + "E";
			break;
		case SDLK_f:
		case SDLK_KP_F:
			keyResult = prefix + "F";
			break;
		case SDLK_g:
			keyResult = prefix + "G";
			break;
		case SDLK_h:
			keyResult = prefix + "H";
			break;
		case SDLK_i:
			keyResult = prefix + "I";
			break;
		case SDLK_j:
			keyResult = prefix + "J";
			break;
		case SDLK_k:
			keyResult = prefix + "K";
			break;
		case SDLK_l:
			keyResult = prefix + "L";
			break;
		case SDLK_m:
			keyResult = prefix + "M";
			break;
		case SDLK_n:
			keyResult = prefix + "N";
			break;
		case SDLK_o:
			keyResult = prefix + "O";
			break;
		case SDLK_p:
			keyResult = prefix + "P";
			break;
		case SDLK_q:
			keyResult = prefix + "Q";
			break;
		case SDLK_r:
			keyResult = prefix + "R";
			break;
		case SDLK_s:
			keyResult = prefix + "S";
			break;
		case SDLK_t:
			keyResult = prefix + "T";
			break;
		case SDLK_u:
			keyResult = prefix + "U";
			break;
		case SDLK_v:
			keyResult = prefix + "V";
			break;
		case SDLK_w:
			keyResult = prefix + "W";
			break;
		case SDLK_x:
			keyResult = prefix + "X";
			break;
		case SDLK_y:
			keyResult = prefix + "Y";
			break;
		case SDLK_z:
			keyResult = prefix + "Z";
			break;
		case SDLK_ESCAPE:
			keyResult = prefix + "ESC";
			break;
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			keyResult = prefix + "ENTER";
			break;
		case SDLK_BACKSPACE:
		case SDLK_KP_BACKSPACE:
			keyResult = prefix + "BACKSPACE";
			break;
		case SDLK_UP:
			keyResult = prefix + "UP";
			break;
		case SDLK_DOWN:
			keyResult = prefix + "DOWN";
			break;
		case SDLK_LEFT:
			keyResult = prefix + "LEFT";
			break;
		case SDLK_RIGHT:
			keyResult = prefix + "RIGHT";
			break;
		case SDLK_INSERT:
			keyResult = prefix + "INSERT";
			break;
		case SDLK_DELETE:
			keyResult = prefix + "DELETE";
			break;
		case SDLK_HOME:
			keyResult = prefix + "HOME";
			break;
		case SDLK_END:
			keyResult = prefix + "END";
			break;
		case SDLK_PAGEUP:
			keyResult = prefix + "PAGEUP";
			break;
		case SDLK_PAGEDOWN:
			keyResult = prefix + "PAGEDOWN";
			break;
		case SDLK_LCTRL:
			keyResult = prefix + "LCTRL";
			break;
		case SDLK_LGUI:
			keyResult = prefix + "LGUI";
			break;
		case SDLK_LALT:
			keyResult = prefix + "LALT";
			break;
		case SDLK_LSHIFT:
			keyResult = prefix + "LSHIFT";
			break;
		case SDLK_RCTRL:
			keyResult = prefix + "RCTRL";
			break;
		case SDLK_RGUI:
			keyResult = prefix + "RGUI";
			break;
		case SDLK_RALT:
			keyResult = prefix + "RALT";
			break;
		case SDLK_RSHIFT:
			keyResult = prefix + "RSHIFT";
			break;
		case SDLK_SPACE:
			keyResult = prefix + "SPACE";
			break;
		case SDLK_TAB:
		case SDLK_KP_TAB:
			keyResult = prefix + "TAB";
			break;
		case SDLK_CAPSLOCK:
			keyResult = prefix + "CAPSLOCK";
			break;
		case SDLK_NUMLOCKCLEAR:
			keyResult = prefix + "NUMLOCK";
			break;
		case SDLK_PRINTSCREEN:
			keyResult = prefix + "PRINTSCREEN";
			break;
		case SDLK_SCROLLLOCK:
			keyResult = prefix + "SCROLLLOCK";
			break;
		case SDLK_PAUSE:
			keyResult = prefix + "PAUSE";
			break;
		case SDLK_AUDIOMUTE:
			keyResult = prefix + "AUDIOMUTE";
			break;
		case SDLK_AUDIOPREV:
			keyResult = prefix + "AUDIOPREV";
			break;
		case SDLK_AUDIONEXT:
			keyResult = prefix + "AUDIONEXT";
			break;
		case SDLK_AUDIOPLAY:
			keyResult = prefix + "AUDIOPLAY";
			break;
		case SDLK_AUDIOSTOP:
			keyResult = prefix + "AUDIOSTOP";
			break;
		case SDLK_VOLUMEUP:
			keyResult = prefix + "VOLUMEUP";
			break;
		case SDLK_VOLUMEDOWN:
			keyResult = prefix + "VOLUMEDOWN";
			break;
		case SDLK_BRIGHTNESSUP:
			keyResult = prefix + "BRIGHTNESSUP";
			break;
		case SDLK_BRIGHTNESSDOWN:
			keyResult = prefix + "BRIGHTNESSDOWN";
			break;
		case SDLK_BACKQUOTE:
			keyResult = prefix + "BACKQUOTE";
			break;
		case SDLK_EXCLAIM:
		case SDLK_KP_EXCLAM:
			keyResult = prefix + "EXCLAM";
			break;
		case SDLK_AT:
		case SDLK_KP_AT:
			keyResult = prefix + "AT";
			break;
		case SDLK_HASH:
		case SDLK_KP_HASH:
			keyResult = prefix + "HASH";
			break;
		case SDLK_DOLLAR:
			keyResult = prefix + "DOOLAR";
			break;
		case SDLK_CARET:
		case SDLK_KP_POWER:
			keyResult = prefix + "CARET";
			break;
		case SDLK_AMPERSAND:
		case SDLK_KP_AMPERSAND:
			keyResult = prefix + "AMPERSAND";
			break;
		case SDLK_KP_DBLAMPERSAND:
			keyResult = prefix + "DBLAMPERSAND";
			break;
		case SDLK_ASTERISK:
		case SDLK_KP_MULTIPLY:
			keyResult = prefix + "ASTERISK";
			break;
		case SDLK_LEFTPAREN:
		case SDLK_KP_LEFTPAREN:
			keyResult = prefix + "LEFTPAREN";
			break;
		case SDLK_RIGHTPAREN:
		case SDLK_KP_RIGHTPAREN:
			keyResult = prefix + "RIGHTPAREN";
			break;
		case SDLK_MINUS:
		case SDLK_KP_MINUS:
			keyResult = prefix + "MINUS";
			break;
		case SDLK_UNDERSCORE:
			keyResult = prefix + "UNDERSCORE";
			break;
		case SDLK_PLUS:
		case SDLK_KP_PLUS:
			keyResult = prefix + "PLUS";
			break;
		case SDLK_EQUALS:
		case SDLK_KP_EQUALS:
			keyResult = prefix + "EQUALS";
			break;
		case SDLK_LEFTBRACKET:
			keyResult = prefix + "LEFTBRACKET";
			break;
		case SDLK_RIGHTBRACKET:
			keyResult = prefix + "RIGHTBRACKET";
			break;
		case SDLK_KP_LEFTBRACE:
			keyResult = prefix + "LEFTBRACE";
			break;
		case SDLK_KP_RIGHTBRACE:
			keyResult = prefix + "RIGHTBRACE";
			break;
		case SDLK_COLON:
			keyResult = prefix + "COLON";
			break;
		case SDLK_SEMICOLON:
			keyResult = prefix + "SEMICOLON";
			break;
		case SDLK_BACKSLASH:
			keyResult = prefix + "BACKSLASH";
			break;
		case SDLK_QUOTE:
			keyResult = prefix + "QUOTE";
			break;
		case SDLK_QUOTEDBL:
			keyResult = prefix + "QUOTEDBL";
			break;
		case SDLK_LESS:
			keyResult = prefix + "LESS";
			break;
		case SDLK_GREATER:
			keyResult = prefix + "GREATER";
			break;
		case SDLK_COMMA:
			keyResult = prefix + "COMMA";
			break;
		case SDLK_PERIOD:
			keyResult = prefix + "PERIOD";
			break;
		case SDLK_QUESTION:
			keyResult = prefix + "QUESTION";
			break;
		case SDLK_SLASH:
			keyResult = prefix + "SLASH";
			break;
		case SDLK_KP_VERTICALBAR:
			keyResult = prefix + "VERTICALBAR";
			break;
		case SDLK_KP_DBLVERTICALBAR:
			keyResult = prefix + "DBLVERTICALBAR";
			break;
		case SDLK_WWW:
			keyResult = prefix + "WWW";
			break;
		case SDLK_MAIL:
			keyResult = prefix + "EMAIL";
			break;
		default:
			break;
		}
		lua_pushstring(L, keyResult.c_str());
		break;
	default:
		break;
	}
	return 1;
}