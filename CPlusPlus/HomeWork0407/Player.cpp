#include "Player.h"
#include <conio.h>
#include <Windows.h>
#include <GameEngineConsole/ConsoleGameScreen.h>
#include "ConsoleObjectManager.h"
#include "Bomb.h"
#include "GameEnum.h"

bool Player::IsGameUpdate = true;

Player::Player()
{
	RenderChar = '*';
	SetPos(ConsoleGameScreen::GetMainScreen().GetScreenSize().Half());

}

// 다음이동위치가 폭탄이면 트루.
bool Player::IsBomb(int2 _NextPos)
{
	std::list<ConsoleGameObject*>& BombGroup
		= ConsoleObjectManager::GetGroup(ObjectOrder::Bomb);

	// Ranged for 라는 문법이에요

	// 절대절대절대. 내부에서 구조나 개수가 바뀌는 행동을 하면 안되요.
	// push_back
	// push_front
	// erase
	for (ConsoleGameObject* Ptr : BombGroup)
	{
		// 터질때가 있습니다.
		if (nullptr == Ptr)
		{
			continue;
		}

		int2 BombPos = Ptr->GetPos();
		if (_NextPos == BombPos)
		{
			return true;
		}
	}

	return false;
}

// 화면바깥으로 못나가게 하세요. 
void Player::Update()
{
	if (0 == _kbhit())
	{
		return;
	}

	char Ch = _getch();

	int2 NextPos = Pos;

	switch (Ch)
	{
	case 'a':
	case 'A':
		NextPos.X -= 1;
		if (true == IsBomb(NextPos)) // 다음위치가 폭탄이면 리턴.
		{
			return;
		}
		else if (false == ConsoleGameScreen::GetMainScreen().IsScreenOver(NextPos))
		{
			Pos.X -= 1;
		}
		break;
	case 'd':
	case 'D':
		NextPos.X += 1;

		if (true == IsBomb(NextPos)) // 다음위치가 폭탄이면 리턴.
		{
			return;
		}

		if (false == ConsoleGameScreen::GetMainScreen().IsScreenOver(NextPos))
		{
			Pos.X += 1;
		}
		break;
	case 'w':
	case 'W':
		NextPos.Y -= 1;

		if (true == IsBomb(NextPos)) // 다음위치가 폭탄이면 리턴.
		{
			return;
		}

		if (false == ConsoleGameScreen::GetMainScreen().IsScreenOver(NextPos))
		{
			Pos.Y -= 1;
		}
		break;
	case 's':
	case 'S':
		NextPos.Y += 1;

		if (true == IsBomb(NextPos)) // 다음위치가 폭탄이면 리턴.
		{
			return;
		}

		if (false == ConsoleGameScreen::GetMainScreen().IsScreenOver(NextPos))
		{
			Pos.Y += 1;
		}
		break;
	case 'f':
	case 'F':
	{
		Bomb* NewBomb = ConsoleObjectManager::CreateConsoleObject<Bomb>(ObjectOrder::Bomb);
		NewBomb->Init(Player::BombPower);
		NewBomb->SetPos(GetPos());
		break;
	}
	case 'q':
	case 'Q':
	{
		IsGameUpdate = false;
		break;
	}
	default:
		break;
	}
}
