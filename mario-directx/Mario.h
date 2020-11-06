#pragma once
#include "GameObject.h"
#include "Koopa.h"
#include "Utils.h"
#include "Fireball.h"

#define MARIO_WALKING_SPEED			0.1f
#define MARIO_RUNNING_SPEED			0.2f
#define MARIO_RUNNING_FAST_SPEED	0.3f
//0.1f
#define MARIO_JUMP_SPEED_X			0.1f
#define MARIO_JUMP_SPEED_Y			0.25f
#define MARIO_JUMP_UP_TIME			300

#define MARIO_FLY_JUMP_SPEED_Y		0.00199f
#define MARIO_FLY_JUMP_TIME			300

#define MARIO_FLY_SPEED_Y			1.0/400.0
#define MARIO_FLY_TIME				500

#define MARIO_THROW_TIME			200

#define MARIO_JUMP_DEFLECT_SPEED	0.3f
#define MARIO_GRAVITY				0.002f
#define MARIO_DIE_DEFLECT_SPEED		0.5f
#define MARIO_RUNNING_TIME			1000

#define MARIO_STATE_IDLE				0
#define MARIO_STATE_WALKING_RIGHT		100
#define MARIO_STATE_WALKING_LEFT		200
#define MARIO_STATE_RUNNING_RIGHT		300
#define MARIO_STATE_RUNNING_LEFT		400
#define MARIO_STATE_JUMPING				500
#define MARIO_STATE_TURNING_LEFT		600
#define MARIO_STATE_TURNING_RIGHT		700
#define MARIO_STATE_RUNNING_FAST_LEFT	800
#define MARIO_STATE_RUNNING_FAST_RIGHT	900
#define MARIO_STATE_DIE					1000

#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT		3
#define MARIO_ANI_TAIL_IDLE_RIGHT		4
#define MARIO_ANI_TAIL_IDLE_LEFT		5
#define MARIO_ANI_FIRE_IDLE_RIGHT		6
#define MARIO_ANI_FIRE_IDLE_LEFT		7

#define MARIO_ANI_BIG_WALKING_RIGHT			8
#define MARIO_ANI_BIG_WALKING_LEFT			9
#define MARIO_ANI_SMALL_WALKING_RIGHT		10
#define MARIO_ANI_SMALL_WALKING_LEFT		11
#define MARIO_ANI_TAIL_WALKING_RIGHT		12
#define MARIO_ANI_TAIL_WALKING_LEFT			13
#define MARIO_ANI_FIRE_WALKING_RIGHT		14
#define MARIO_ANI_FIRE_WALKING_LEFT			15

#define MARIO_ANI_BIG_RUNNING_RIGHT			16
#define MARIO_ANI_BIG_RUNNING_LEFT			17
#define MARIO_ANI_SMALL_RUNNING_RIGHT		18
#define MARIO_ANI_SMALL_RUNNING_LEFT		19
#define MARIO_ANI_TAIL_RUNNING_RIGHT		20
#define MARIO_ANI_TAIL_RUNNING_LEFT			21
#define MARIO_ANI_FIRE_RUNNING_RIGHT		22
#define MARIO_ANI_FIRE_RUNNING_LEFT			23

#define MARIO_ANI_BIG_RUNNING_FASTER_RIGHT			24
#define MARIO_ANI_BIG_RUNNING_FASTER_LEFT			25
#define MARIO_ANI_SMALL_RUNNING_FASTER_RIGHT		26
#define MARIO_ANI_SMALL_RUNNING_FASTER_LEFT			27
#define MARIO_ANI_TAIL_RUNNING_FASTER_RIGHT			28
#define MARIO_ANI_TAIL_RUNNING_FASTER_LEFT			29
#define MARIO_ANI_FIRE_RUNNING_FASTER_RIGHT			30
#define MARIO_ANI_FIRE_RUNNING_FASTER_LEFT			31

#define MARIO_ANI_BIG_JUMPING_RIGHT		32
#define MARIO_ANI_BIG_JUMPING_LEFT		33
#define MARIO_ANI_SMALL_JUMPING_RIGHT	34
#define MARIO_ANI_SMALL_JUMPING_LEFT	35
#define MARIO_ANI_TAIL_JUMPING_RIGHT	36
#define MARIO_ANI_TAIL_JUMPING_LEFT		37
#define MARIO_ANI_FIRE_JUMPING_RIGHT	38
#define MARIO_ANI_FIRE_JUMPING_LEFT		39

#define MARIO_ANI_SMALL_TURNING_LEFT	40
#define MARIO_ANI_SMALL_TURNING_RIGHT	41
#define MARIO_ANI_BIG_TURNING_LEFT		42
#define MARIO_ANI_BIG_TURNING_RIGHT		43
#define MARIO_ANI_TAIL_TURNING_LEFT		44
#define MARIO_ANI_TAIL_TURNING_RIGHT	45
#define MARIO_ANI_FIRE_TURNING_LEFT		46
#define MARIO_ANI_FIRE_TURNING_RIGHT	47

#define MARIO_ANI_SMALL_KICKING_LEFT	48
#define MARIO_ANI_SMALL_KICKING_RIGHT	49
#define MARIO_ANI_BIG_KICKING_LEFT		50
#define MARIO_ANI_BIG_KICKING_RIGHT		51
#define MARIO_ANI_TAIL_KICKING_LEFT		52
#define MARIO_ANI_TAIL_KICKING_RIGHT	53
#define MARIO_ANI_FIRE_KICKING_LEFT		54
#define MARIO_ANI_FIRE_KICKING_RIGHT	55

#define MARIO_ANI_SMALL_HOLD_KOOPA_IDLE_RIGHT			56
#define MARIO_ANI_SMALL_HOLD_KOOPA_IDLE_LEFT			57
#define MARIO_ANI_BIG_HOLD_KOOPA_IDLE_RIGHT				58
#define MARIO_ANI_BIG_HOLD_KOOPA_IDLE_LEFT				59
#define MARIO_ANI_TAIL_HOLD_KOOPA_IDLE_RIGHT			60
#define MARIO_ANI_TAIL_HOLD_KOOPA_IDLE_LEFT				61
#define MARIO_ANI_FIRE_HOLD_KOOPA_IDLE_RIGHT			62
#define MARIO_ANI_FIRE_HOLD_KOOPA_IDLE_LEFT				63

#define MARIO_ANI_SMALL_HOLD_KOOPA_WALKING_RIGHT		64
#define MARIO_ANI_SMALL_HOLD_KOOPA_WALKING_LEFT			65
#define MARIO_ANI_BIG_HOLD_KOOPA_WALKING_RIGHT			66
#define MARIO_ANI_BIG_HOLD_KOOPA_WALKING_LEFT			67
#define MARIO_ANI_TAIL_HOLD_KOOPA_WALKING_RIGHT			68
#define MARIO_ANI_TAIL_HOLD_KOOPA_WALKING_LEFT			69
#define MARIO_ANI_FIRE_HOLD_KOOPA_WALKING_RIGHT			70
#define MARIO_ANI_FIRE_HOLD_KOOPA_WALKING_LEFT			71

#define MARIO_ANI_SMALL_HOLD_KOOPA_RUNNING_RIGHT		72
#define MARIO_ANI_SMALL_HOLD_KOOPA_RUNNING_LEFT			73
#define MARIO_ANI_BIG_HOLD_KOOPA_RUNNING_RIGHT			74
#define MARIO_ANI_BIG_HOLD_KOOPA_RUNNING_LEFT			75
#define MARIO_ANI_TAIL_HOLD_KOOPA_RUNNING_RIGHT			76
#define MARIO_ANI_TAIL_HOLD_KOOPA_RUNNING_LEFT			77
#define MARIO_ANI_FIRE_HOLD_KOOPA_RUNNING_RIGHT			78
#define MARIO_ANI_FIRE_HOLD_KOOPA_RUNNING_LEFT			79

#define MARIO_ANI_BIG_SITTING_RIGHT						80
#define MARIO_ANI_BIG_SITTING_LEFT						81
#define MARIO_ANI_TAIL_SITTING_RIGHT					82
#define MARIO_ANI_TAIL_SITTING_LEFT						83
#define MARIO_ANI_FIRE_SITTING_RIGHT					84
#define MARIO_ANI_FIRE_SITTING_LEFT						85

#define MARIO_ANI_SMALL_HOLD_KOOPA_JUMPING_RIGHT		86
#define MARIO_ANI_SMALL_HOLD_KOOPA_JUMPING_LEFT			87
#define MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_RIGHT			88
#define MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_LEFT			89
#define MARIO_ANI_TAIL_HOLD_KOOPA_JUMPING_RIGHT			90
#define MARIO_ANI_TAIL_HOLD_KOOPA_JUMPING_LEFT			91
#define MARIO_ANI_FIRE_HOLD_KOOPA_JUMPING_RIGHT			92
#define MARIO_ANI_FIRE_HOLD_KOOPA_JUMPING_LEFT			93

#define MARIO_ANI_TAIL_FLY_JUMP_RIGHT			94
#define MARIO_ANI_TAIL_FLY_JUMP_DROP_RIGHT		95
#define MARIO_ANI_TAIL_FLY_JUMP_LEFT			96
#define MARIO_ANI_TAIL_FLY_JUMP_DROP_LEFT		97

#define MARIO_ANI_TAIL_FLY_RIGHT				98
#define MARIO_ANI_TAIL_FLY_DROP_RIGHT			99
#define MARIO_ANI_TAIL_FLY_LEFT					100
#define MARIO_ANI_TAIL_FLY_DROP_LEFT			101

#define MARIO_ANI_FIRE_RIGHT			102
#define MARIO_ANI_FIRE_LEFT				103

#define MARIO_ANI_SPINNING_LEFT			104
#define MARIO_ANI_SPINNING_RIGHT		105
#define MARIO_ANI_DIE					106

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TAIL	3
#define MARIO_LEVEL_FIRE	4

#define MARIO_FIRE_BBOX_WIDTH	15
#define MARIO_FIRE_BBOX_HEIGHT	27
#define MARIO_FIRE_BBOX_MARGIN_LEFT		2
#define MARIO_FIRE_BBOX_MARGIN_RIGHT	0

#define MARIO_TAIL_FACING_SCREEN_WIDTH	16
#define MARIO_TAIL_BBOX_WIDTH	21
#define MARIO_TAIL_BBOX_HEIGHT	27
#define MARIO_TAIL_BBOX_MARGIN_LEFT		7
#define MARIO_TAIL_BBOX_MARGIN_RIGHT	0
#define MARIO_TAIL_HEAD_TO_TAIL		18
#define MARIO_TAIL_TAIL_WIDTH		2

#define MARIO_TAIL_SPINNING_WIDTH		23
#define MARIO_TAIL_SPINNING_MARGIN_LEFT	9

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27
#define MARIO_BIG_BBOX_MARGIN_LEFT		2
#define MARIO_BIG_BBOX_MARGIN_RIGHT		0

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15
#define MARIO_SMALL_BBOX_MARGIN_LEFT	2
#define MARIO_SMALL_BBOX_MARGIN_RIGHT	0

#define MARIO_FIRE_SITTING_BBOX_WIDTH	14
#define MARIO_FIRE_SITTING_BBOX_HEIGHT	18

#define MARIO_TAIL_SITTING_BBOX_WIDTH	22
#define MARIO_TAIL_SITTING_BBOX_HEIGHT	18

#define MARIO_BIG_SITTING_BBOX_WIDTH	14
#define MARIO_BIG_SITTING_BBOX_HEIGHT	18

#define MARIO_UNTOUCHABLE_TIME	2000
#define MARIO_TURNING_DELAY		150
#define MARIO_KICKING_TIME		1000
#define MARIO_SPINNING_TIME		300


class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	CKoopa* holdenKoopa;

	int lastState;

	int turning;	// turn left - 1, turn right - 2
	DWORD turning_start;

	int jumping;

	int jumpingUp;
	DWORD jumpingUp_start;

	int sitting;

	int flyJump;
	DWORD flyJump_start;

	int fly;

	int throwing;
	DWORD throwing_start;
	
	int lastRunning;
	int running;
	DWORD running_start;
	int powerLevel;

	int kicking;
	DWORD kicking_start;

	int spinning;
	DWORD spinning_start;
	float startSpinningPosition;
	int spinningPhase;

	int hittableTail;
	float tail_start_x, tail_end_x;
	float tail_start_y, tail_end_y;

	vector<CFireball*> fireballs;
	int currentFireball;

	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	CMario(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	int IsJumping() { return jumping; }
	void SetSittingState(int state);

	void SetJumpingUp(int jumpingUp);
	int GetJumpingUp() { return jumpingUp; }

	void FlyJump();

	void SetThrowing();
	void ThrowFireball();

	void setHoldenKoopa(CKoopa* koopa) { holdenKoopa = koopa; koopa->SetHolden(1); }
	void releaseKoopa();

	void LevelUp();
	void LevelDown();

	void SetState(int state);
	void SetLevel(int l);

	void GetMargins(int& leftMargin, int& rightMargin);

	int GetUntouchable() { return untouchable; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void StartTurning(int dir) { turning = dir; turning_start = GetTickCount64(); running = 0; }

	void StartKicking() { kicking = 1; kicking_start = GetTickCount64(); };

	void StartSpinning();
	int GetHittableTail() { return hittableTail; }
	void GetTail(float &start_x, float &end_x, float &start_y, float &end_y) { start_x = tail_start_x; end_x = tail_end_x; start_y = tail_start_y; end_y = tail_end_y; }
	void StartRunning() { running_start = GetTickCount64(); }

	int GetPowerLevel() { return powerLevel; }

	void AddFireball(CFireball* fireball) { this->fireballs.push_back(fireball); }

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};