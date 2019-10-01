#pragma once


enum KeyLayout
{
	K_Left = 0,
	K_Right,
	K_Up,
	K_Down,
	K_Attack,
	K_Jump,
	K_Map,
	K_Reset,
	Count
};

void InitInput();
void InputExchange();
void UpdatePrevInputs();
bool Released(KeyLayout key);
bool KeyState(KeyLayout key);
bool Pressed(KeyLayout key);
void SetInputPossible(bool set);
bool GetInputPossible();
void StartVibration();
