#include"KeyMap.h"
#include"Player.h"
#include"controller.h"
#include"complex"

bool mInputs[Count];
bool mPrevInputs[Count];
bool isInputPossible;
void InitInput() {

}
void InputExchange() {

	if (GetControllerPress(NpadButton::Plus::Index))
	{
		mInputs[K_Map] = true;
	}
	else
	{
		mInputs[K_Map] = false;
	}

	if (GetControllerPress(NpadButton::A::Index)) {
		mInputs[K_Attack] = true;
	}
	else {
		mInputs[K_Attack] = false;
	}

	if (GetControllerPress(NpadButton::B::Index)) {
		mInputs[K_Jump] = true;
	}
	else {
		mInputs[K_Jump] = false;
	}

	Float2 stick = GetControllerLeftStick();



	abs(stick.x) > abs(stick.y) ? stick.y = 0.0f : stick.x = 0.0f;


	if (GetControllerPress(NpadButton::Left::Index) || stick.x < 0.0f)
	{
		mInputs[K_Left] = true;
	}
	else
	{
		mInputs[K_Left] = false;
	}
	if (GetControllerPress(NpadButton::Right::Index) || stick.x > 0.0f) {
		mInputs[K_Right] = true;
	}
	else {
		mInputs[K_Right] = false;
	}
	if (GetControllerPress(NpadButton::Up::Index) || stick.y > 0.0f) {
		mInputs[K_Up] = true;
	}
	else {
		mInputs[K_Up] = false;
	}
	if (GetControllerPress(NpadButton::Down::Index) || stick.y < 0.0f) {
		mInputs[K_Down] = true;
	}
	else {
		mInputs[K_Down] = false;
	}

	if (GetControllerPress(NpadButton::R::Index)) {
		mInputs[K_Reset] = true;
	}
	else {
		mInputs[K_Reset] = false;
	}

}

void UpdatePrevInputs()
{
	int count = Count;
	for (int i = 0; i < count; ++i) {
		mPrevInputs[i] = mInputs[i];
	}
}

bool Released(KeyLayout key)
{
	return (!mInputs[(int)key] && mPrevInputs[(int)key]);
};

bool KeyState(KeyLayout key)
{
	return (mInputs[(int)key]);
};

bool Pressed(KeyLayout key)
{
	return (mInputs[(int)key] && !mPrevInputs[(int)key]);
};

void SetInputPossible(bool set) {
	isInputPossible = set;
}
bool GetInputPossible() {
	return isInputPossible;
}

void StartVibration() {
	SetControllerLeftVibration(5);
	SetControllerRightVibration(5);
}
