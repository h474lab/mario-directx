#pragma once
#include "GameObject.h"
#include "Koopa.h"
#include "Utils.h"
#include "Fireball.h"

#define MARIO_WALKING_SPEED			0.1f
#define MARIO_RUNNING_SPEED			0.2f
#define MARIO_RUNNING_FAST_SPEED	0.3f
#define MARIO_SLIDING_SPEED_DOWN	0.02f
//0.1f
#define MARIO_JUMP_SPEED_X			0.1f
#define MARIO_JUMP_SPEED_Y			0.25f
#define MARIO_JUMP_UP_TIME			300

#define MARIO_FLY_JUMP_SPEED_Y		0.00199f
#define MARIO_FLY_JUMP_TIME			300

#define MARIO_FLY_SPEED_Y			1.0/400.0f
#define MARIO_FLY_SPEED_X			0.35f
#define MARIO_FLY_TIME				500

#define MARIO_THROW_TIME			200

#define MARIO_JUMP_DEFLECT_SPEED	0.3f
#define MARIO_GRAVITY				0.002f
#define MARIO_DIE_DEFLECT_SPEED		0.5f
#define MARIO_RUNNING_TIME			1000

#define MARIO_SWITCHING_SCENE_SPEED	0.02f

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
#define MARIO_ANI_FIRE_JUMPING_LEFT		38
#define MARIO_ANI_FIRE_JUMPING_RIGHT	39

#define MARIO_ANI_TAIL_FLY_JUMP_RIGHT			40
#define MARIO_ANI_TAIL_FLY_JUMP_DROP_RIGHT		41
#define MARIO_ANI_TAIL_FLY_JUMP_LEFT			42
#define MARIO_ANI_TAIL_FLY_JUMP_DROP_LEFT		43

#define MARIO_ANI_TAIL_FLY_RIGHT				44
#define MARIO_ANI_TAIL_FLY_DROP_RIGHT			45
#define MARIO_ANI_TAIL_FLY_LEFT					46
#define MARIO_ANI_TAIL_FLY_DROP_LEFT			47

#define MARIO_ANI_SMALL_TURNING_LEFT	48
#define MARIO_ANI_SMALL_TURNING_RIGHT	49
#define MARIO_ANI_BIG_TURNING_LEFT		50
#define MARIO_ANI_BIG_TURNING_RIGHT		51
#define MARIO_ANI_TAIL_TURNING_LEFT		52
#define MARIO_ANI_TAIL_TURNING_RIGHT	53
#define MARIO_ANI_FIRE_TURNING_LEFT		54
#define MARIO_ANI_FIRE_TURNING_RIGHT	55

#define MARIO_ANI_SMALL_KICKING_LEFT	56
#define MARIO_ANI_SMALL_KICKING_RIGHT	57
#define MARIO_ANI_BIG_KICKING_LEFT		58
#define MARIO_ANI_BIG_KICKING_RIGHT		59
#define MARIO_ANI_TAIL_KICKING_LEFT		60
#define MARIO_ANI_TAIL_KICKING_RIGHT	61
#define MARIO_ANI_FIRE_KICKING_LEFT		62
#define MARIO_ANI_FIRE_KICKING_RIGHT	63

#define MARIO_ANI_SMALL_HOLD_KOOPA_IDLE_RIGHT			64
#define MARIO_ANI_SMALL_HOLD_KOOPA_IDLE_LEFT			65
#define MARIO_ANI_BIG_HOLD_KOOPA_IDLE_RIGHT				66
#define MARIO_ANI_BIG_HOLD_KOOPA_IDLE_LEFT				67
#define MARIO_ANI_TAIL_HOLD_KOOPA_IDLE_RIGHT			68
#define MARIO_ANI_TAIL_HOLD_KOOPA_IDLE_LEFT				69
#define MARIO_ANI_FIRE_HOLD_KOOPA_IDLE_RIGHT			70
#define MARIO_ANI_FIRE_HOLD_KOOPA_IDLE_LEFT				71

#define MARIO_ANI_SMALL_HOLD_KOOPA_WALKING_RIGHT		72
#define MARIO_ANI_SMALL_HOLD_KOOPA_WALKING_LEFT			73
#define MARIO_ANI_BIG_HOLD_KOOPA_WALKING_RIGHT			74
#define MARIO_ANI_BIG_HOLD_KOOPA_WALKING_LEFT			75
#define MARIO_ANI_TAIL_HOLD_KOOPA_WALKING_RIGHT			76
#define MARIO_ANI_TAIL_HOLD_KOOPA_WALKING_LEFT			77
#define MARIO_ANI_FIRE_HOLD_KOOPA_WALKING_RIGHT			78
#define MARIO_ANI_FIRE_HOLD_KOOPA_WALKING_LEFT			79

#define MARIO_ANI_SMALL_HOLD_KOOPA_RUNNING_RIGHT		80
#define MARIO_ANI_SMALL_HOLD_KOOPA_RUNNING_LEFT			81
#define MARIO_ANI_BIG_HOLD_KOOPA_RUNNING_RIGHT			82
#define MARIO_ANI_BIG_HOLD_KOOPA_RUNNING_LEFT			83
#define MARIO_ANI_TAIL_HOLD_KOOPA_RUNNING_RIGHT			84
#define MARIO_ANI_TAIL_HOLD_KOOPA_RUNNING_LEFT			85
#define MARIO_ANI_FIRE_HOLD_KOOPA_RUNNING_RIGHT			86
#define MARIO_ANI_FIRE_HOLD_KOOPA_RUNNING_LEFT			87

#define MARIO_ANI_BIG_SITTING_RIGHT						88
#define MARIO_ANI_BIG_SITTING_LEFT						89
#define MARIO_ANI_TAIL_SITTING_RIGHT					90
#define MARIO_ANI_TAIL_SITTING_LEFT						91
#define MARIO_ANI_FIRE_SITTING_RIGHT					92
#define MARIO_ANI_FIRE_SITTING_LEFT						93

#define MARIO_ANI_SMALL_HOLD_KOOPA_JUMPING_RIGHT		94
#define MARIO_ANI_SMALL_HOLD_KOOPA_JUMPING_LEFT			95
#define MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_RIGHT			96
#define MARIO_ANI_BIG_HOLD_KOOPA_JUMPING_LEFT			97
#define MARIO_ANI_TAIL_HOLD_KOOPA_JUMPING_RIGHT			98
#define MARIO_ANI_TAIL_HOLD_KOOPA_JUMPING_LEFT			99
#define MARIO_ANI_FIRE_HOLD_KOOPA_JUMPING_RIGHT			100
#define MARIO_ANI_FIRE_HOLD_KOOPA_JUMPING_LEFT			101

#define MARIO_ANI_FIRE_RIGHT			102
#define MARIO_ANI_FIRE_LEFT				103

#define MARIO_ANI_SPINNING_LEFT			104
#define MARIO_ANI_SPINNING_RIGHT		105

#define MARIO_ANI_SMALL_SWICHING_SCENE	106
#define MARIO_ANI_BIG_SWITCHING_SCENE	107
#define MARIO_ANI_TAIL_SWITCHING_SCENE	108
#define MARIO_ANI_FIRE_SWITCHING_SCENE	109

#define MARIO_ANI_DIE					110

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
#define MARIO_TAIL_BBOX_MARGIN_LEFT		9
#define MARIO_TAIL_BBOX_MARGIN_RIGHT	0

#define MARIO_TAIL_NORMAL_LENGTH		5
#define MARIO_TAIL_HEAD_TO_TAIL		18
#define MARIO_TAIL_TAIL_WIDTH		2

#define MARIO_TAIL_SPINNING_WIDTH	23
#define MARIO_TAIL_SPINNING_LENGTH	7
#define MARIO_SPINNING_PHASE_ERROR	16

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
#define MARIO_KICKING_TIME		1000
#define MARIO_SPINNING_TIME		500

#define MARIO_SWITCHING_ZONE_DIRECTION_UP	0
#define MARIO_SWITCHING_ZONE_DIRECTION_DOWN	1

#define MARIO_SCORE_100		100
#define MARIO_SCORE_200		200
#define MARIO_SCORE_400		400
#define MARIO_SCORE_800		800
#define MARIO_SCORE_1000	1000
#define MARIO_SCORE_2000	2000
#define MARIO_SCORE_4000	4000
#define MARIO_SCORE_8000	8000
#define MARIO_SCORE_1UP		-1

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	// Koopa that Mario is holding
	CKoopa* holdenKoopa;

	// State in the last frame
	int lastState;

	// When Mario changes his direction, he may be turned into turning state
	int turning;	// turn left - 1, turn right - 2
	DWORD turning_start;

	// Indicate whether Mario is on the ground or not
	int jumping;

	// "Jumping Up" is the state that Mario can jump higher (or further) than normal jumping state
	int jumpingUp;
	DWORD jumpingUp_start;

	int flyJump;
	DWORD flyJump_start;
	int fly;

	int sitting;

	// Point out whether Mario is ready to go up/down the tube
	int readyToUp, readyToDown;

	int throwing;
	DWORD throwing_start;
	
	int lastRunning;
	int running;
	DWORD running_start;
	int powerLevel;

	int kicking;
	DWORD kicking_start;

	int spinning;
	DWORD spinning_start, spinningTime;
	float startSpinningPosition;
	int spinningPhase;

	int hittableTail;
	float tail_start_x, tail_end_x;
	float tail_start_y, tail_end_y;

	vector<CFireball*> fireballs;
	int currentFireball;

	int lastFlyingDirection;
	int allowSwichingZone;

	float start_x;			// initial position of Mario at scene
	float start_y;

	int scoreStreak;

	DWORD now;
public:
	CMario(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	int RenderSmallMario();
	int RenderBigMario();
	int RenderTailMario();
	int RenderFireMario();

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
	void StartUntouchable() { untouchable = 1; untouchable_start = (DWORD)GetTickCount64(); }

	void StartTurning(int dir) { turning = dir; turning_start = (DWORD)GetTickCount64(); running = 0; }

	void StartKicking() { kicking = 1; kicking_start = (DWORD)GetTickCount64(); };

	void StartSpinning();
	int GetHittableTail() { return hittableTail; }

	void SetTail(float start_x, float end_x);
	void GetTail(float &start_x, float &end_x, float &start_y, float &end_y) { start_x = tail_start_x; end_x = tail_end_x; start_y = tail_start_y; end_y = tail_end_y; }
	
	void StartRunning() { running_start = (DWORD)GetTickCount64(); }

	int GetPowerLevel() { return powerLevel; }

	void AddFireball(CFireball* fireball) { this->fireballs.push_back(fireball); }

	void SetReadyUp(int state) { readyToUp = state; }
	void SetReadyDown(int state) { readyToDown = state; }

	void StartSwitchingZone(int direction);
	int GetAllowSwitchingZone() { return allowSwichingZone; }
	void SetAllowSwitchingZone(int value) { allowSwichingZone = value; }

	void AddStreakScore(CGameObject* coObject);
	void AddScore(int score, CGameObject* coObject);

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};