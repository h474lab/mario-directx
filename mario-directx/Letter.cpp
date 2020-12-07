#include "Letter.h"

CLetter::CLetter()
{
	background = 1;
	letter = -1;

	SetAnimationSet(CAnimationSets::GetInstance()->Get(ID_ANI_SET_LETTERS));
}

void CLetter::Render()
{
	if (state == LETTER_STATE_DISAPPEAR) return;
	if (letter >= 0 && letter < LETTER_NUMBER)
		animation_set->at(letter)->Render(x, y);
}

CLetters::CLetters(string str)
{
	numberOfLetters = str.length();
	letters = new LPLETTER[numberOfLetters];

	for (int i = 0; i < numberOfLetters; i++)
	{
		if (str[i] != ' ')
		{
			int pos = toascii(str[i]) - 65;
			letters[i]->SetState(LETTER_STATE_APPEAR);
			letters[i]->SetLetter(pos);
		}
		else letters[i]->SetState(LETTER_STATE_DISAPPEAR);
	}
}
