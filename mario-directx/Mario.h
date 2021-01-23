#pragma once
#include "GameObject.h"
#include "Koopa.h"
#include "Utils.h"
#include "Fireball.h"

#define MARIO_ACCELERATION_X		0.0005f
#define MARIO_ACCELERATION_POSITIVE	1
#define MARIO_ACCELERATION_NEGATIVE	-1

#define MARIO_WALKING_SPEED			0.1f
#define MARIO_RUNNING_SPEED			0.16f
#define MARIO_RUNNING_AFTERSCENE_SPEED	0.13f
#define MARIO_RUNNING_FAST_SPEED	0.2f
#define MARIO_SLIDING_SPEED_DOWN	0.001f
#define MARIO_JUMPING_SPEED_DOWN	0.002f

#define MARIO_JUMP_SPEED_X			0.1f
#define MARIO_JUMP_SPEED_Y			0.15f
#define MARIO_JUMP_HEIGHT			64.0f
#define MARIO_MAX_FIREBALL_NUMBER	2

#define MARIO_LEVEL_TRANSFORMING_TIME	50
#define MARIO_LEVEL_TRANSFORMING_STEPS	10

#define MARIO_POWER_LEVEL_REDUCING_TIME	300
#define MARIO_MAXIMUM_POWER_LEVEL		6.0f

#define MARIO_FLY_JUMP_SPEED_Y		0.01f
#define MARIO_FLYING_JUMP_SPEED_X	0.07f
#define MARIO_FLY_JUMP_TIME			300

#define MARIO_FLY_SPEED_Y			0.12f
#define MARIO_FLYING_SPEED_X		0.1f
#define MARIO_FLY_TIME				500

#define MARIO_JUMP_MAX_POWER_SPEED_Y	0.03f
#define MARIO_JUMP_MAX_POWER_SPEED_X	0.14f
#define MARIO_JUMP_MAX_POWER_TIME		300

#define MARIO_JUMP_MAX_POWER_NONE	0
#define MARIO_JUMP_MAX_POWER_UP		1
#define MARIO_JUMP_MAX_POWER_DOWN	2

#define MARIO_SPINNING_SPEED_X		0.1f

#define MARIO_THROW_TIME			200

#define MARIO_JUMP_DEFLECT_SPEED	0.15f
#define MARIO_GRAVITY				0.012f
#define MARIO_DIE_DEFLECT_SPEED		0.3f
#define MARIO_DIE_DELAY				500
#define MARIO_RUNNING_TIME			1000

#define MARIO_SWITCHING_SCENE_SPEED	0.02f

#define MARIO_STATE_IDLE				0
#define MARIO_STATE_IDLE_LEFT			50
#define MARIO_STATE_IDLE_LEFT_HOLD_KOOPA	55
#define MARIO_STATE_SIT_RIGHT			60
#define MARIO_STATE_SIT_LEFT			70
#define MARIO_STATE_JUMPING_OUT			80
#define MARIO_STATE_LOOKING_UP			90
#define MARIO_STATE_WALKING_RIGHT		100
#define MARIO_STATE_WALKING_LEFT		200
#define MARIO_STATE_RUNNING_RIGHT		300
#define MARIO_STATE_RUNNING_LEFT		400
#define MARIO_STATE_JUMPING				500
#define MARIO_STATE_FLY_JUMP_LEFT		510
#define MARIO_STATE_JUMPING_LEFT		520
#define MARIO_STATE_TURNING_LEFT		600
#define MARIO_STATE_TURNING_RIGHT		700
#define MARIO_STATE_RUNNING_FAST_LEFT	800
#define MARIO_STATE_RUNNING_FAST_RIGHT	900
#define MARIO_STATE_UNAVAILABLE			990
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

#define MARIO_ANI_TAIL_ATTACK_LEFT			104
#define MARIO_ANI_TAIL_ATTACK_RIGHT			105
#define MARIO_ANI_FACING_THE_SCREEN			106
#define MARIO_ANI_FACING_DOWN_THE_SCREEN	107

#define MARIO_ANI_SMALL_SWICHING_SCENE	108
#define MARIO_ANI_BIG_SWITCHING_SCENE	109
#define MARIO_ANI_TAIL_SWITCHING_SCENE	110
#define MARIO_ANI_FIRE_SWITCHING_SCENE	111

#define MARIO_ANI_INTRO_JUMPING_OUT		112
#define MARIO_ANI_INTRO_LOOKING_UP		113

#define MARIO_ANI_DIE					114
#define MARIO_TAIL_TURNING_OFFSET_Y		2

// Luigi animations
#define LUIGI_ANI_IDLE_RIGHT		115
#define LUIGI_ANI_IDLE_LEFT			116
#define LUIGI_ANI_WALK_RIGHT		117
#define LUIGI_ANI_WALK_LEFT			118
#define LUIGI_ANI_RUN_RIGHT			119
#define LUIGI_ANI_RUN_LEFT			120
#define LUIGI_ANI_RUN_FAST_RIGHT	121
#define LUIGI_ANI_RUN_FAST_LEFT		122
#define LUIGI_ANI_JUMP_RIGHT		123
#define LUIGI_ANI_JUMP_LEFT			124
#define LUIGI_ANI_TURN_LEFT			125
#define LUIGI_ANI_TURN_RIGHT		126
#define LUIGI_ANI_KICK_LEFT			127
#define LUIGI_ANI_KICK_RIGHT		128

#define LUIGI_ANI_HOLD_KOOPA_IDLE_RIGHT		129
#define LUIGI_ANI_HOLD_KOOPA_IDLE_LEFT		130
#define LUIGI_ANI_HOLD_KOOPA_WALK_RIGHT		131
#define LUIGI_ANI_HOLD_KOOPA_WALK_LEFT		132
#define LUIGI_ANI_HOLD_KOOPA_RUN_RIGHT		133
#define LUIGI_ANI_HOLD_KOOPA_RUN_LEFT		134
#define LUIGI_ANI_SIT_RIGHT					135
#define LUIGI_ANI_SIT_LEFT					136
#define LUIGI_ANI_HOLD_KOOPA_JUMP_RIGHT		137
#define LUIGI_ANI_HOLD_KOOPA_JUMP_LEFT		138
#define LUIGI_ANI_SWITCH_SCENE				139

#define MARIO_ANI_TAIL_TRANSFORM			140

// Mario jumps max power animations
#define MARIO_SMALL_JUMP_MAX_POWER_LEFT		141
#define MARIO_SMALL_JUMP_MAX_POWER_RIGHT	142
#define MARIO_BIG_JUMP_MAX_POWER_LEFT		143
#define MARIO_BIG_JUMP_MAX_POWER_RIGHT		144
#define MARIO_FIRE_JUMP_MAX_POWER_LEFT		145
#define MARIO_FIRE_JUMP_MAX_POWER_RIGHT		146

#define MARIO_ANI_SPARKLE					147

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TAIL	3
#define MARIO_LEVEL_FIRE	4
#define MARIO_LEVEL_LUIGI	10

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
#define MARIO_SPINNING_PHASE_ERROR	7

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

#define MARIO_UNTOUCHABLE_TIME	3000
#define MARIO_KICKING_TIME		300
#define MARIO_SPINNING_TIME		100

#define MARIO_UNTOUCHABLE_CHANGING_ALPHA_TIME	50
#define MARIO_UNTOUCHABLE_ALPHA_LOW				0
#define MARIO_UNTOUCHABLE_ALPHA_HIGH			255

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
#define MARIO_SCORE_1UP		-10

#define MARIO_FLYING_STATE_UP	1
#define MARIO_FLYING_STATE_DOWN	-1
#define MARIO_FLYING_STATE_NONE	0

#define MARIO_FACING_LEFT	0
#define MARIO_FACING_RIGHT	1

#define HOLDEN_KOOPA_OFFSET_RIGHT_X	-5
#define HOLDEN_KOOPA_OFFSET_RIGHT_Y	-KOOPA_LYING_HEIGHT - 1
#define HOLDEN_KOOPA_OFFSET_LEFT_X	5 - KOOPA_LYING_WIDTH
#define HOLDEN_KOOPA_OFFSET_LEFT_Y	-KOOPA_LYING_HEIGHT - 1

#define MARIO_TAIL_SPARKLE_OFFSET_LEFT_X	0
#define MARIO_TAIL_SPARKLE_OFFSET_LEFT_Y	5
#define MARIO_TAIL_SPARKLE_OFFSET_RIGHT_X	16
#define MARIO_TAIL_SPARKLE_OFFSET_RIGHT_Y	5
#define MARIO_TAIL_SPARKLE_TIME				100

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float v0;
	DWORD speed_up_start;

	// Koopa that Mario is holding
	CKoopa* holdenKoopa;
	int allowHodingKoopa;

	// State in the last frame
	int lastState;

	// When Mario changes his direction, he may be turned into turning state
	int turning;
	int slowingDown;

	// Indicate whether Mario is on the ground or not
	int jumping;
	float jumpingSpeed;

	// "Jumping Up" is the state that Mario can jump higher (or further) than normal jumping state
	int jumpingUp;
	float lastStandingHeight;

	int jumpMaxPower;
	DWORD jump_max_power_start;

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
	DWORD powerLevel_reduce_start;

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

	int levelTransform;
	int transform_lastLevel, transform_newLevel;
	int transformSteps;
	DWORD stepStart;

	int gainedMagicWings;

	float start_x;			// initial position of Mario at scene
	float start_y;

	unsigned int scoreStreak;
	int passedTheLevel;

	int renderAlpha; // Mario's alpha when rendering
	DWORD alpha_switch_start;

	int isInIntro; // Mario is currently in Intro Scene

	CGameObject* floor;

	int keyFacing;	// Mario facing direction based on pressed key

	int dying_delay;
	DWORD dying_delay_start;

	int sparkle;
	DWORD sparkle_start;
	float sparkle_x, sparkle_y;

	bool UpdateDyingDelay();
	void CheckReleasingKoopa();
	void UpdateSparkling();

	void UpdateMarioPassingLevel();
	bool UpdateMarioLevelTransformation();
	bool UpdateMarioSwitchingZone(DWORD dt);
	void UpdateMarioJumpingState();

	void CheckMarioRunningCondition();
	void UpdateRunningState();
	void CheckAndSetMagicWings();
	void CheckMarioTurning();
	void UpdateMarioSpeed(DWORD dt);

	void CheckMarioThrowingFireballs();
	void CheckMarioKickingState();
	void CheckMarioSpinningState();
	void CheckMarioUntouchableState();

	void UpdateMarioCollision(vector<LPCOLLISIONEVENT> coEvents, vector<LPGAMEOBJECT> *coObjects,
		float lastX, float lastY, float lastVx, float lastVy);

	void FixFloor();
	void SetKoopaPosition();

	void CleanUpCollisionEvents(vector<LPCOLLISIONEVENT> coEvents);

	void GetSparklePosition(float &x, float &y);
public:
	CMario(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	void SetMovingLeft(int skillButtonPressed);
	void SetMovingRight(int skillButtonPressed);

	virtual void Render();
	int RenderSmallMario();
	int RenderBigMario();
	int RenderTailMario();
	int RenderFireMario();
	int RenderLuigi();
	
	void SetJumping(int jumpingState) { jumping = jumpingState; }
	int IsJumping() { return jumping; }
	void SetSittingState(int state);
	void SetJumpingUp(int jumpingUp);
	int GetJumpingUp() { return jumpingUp; }
	void FlyJump();
	void JumpMaxPower();

	void AddFireball(CFireball* fireball) { this->fireballs.push_back(fireball); }
	void SetThrowing();
	void ThrowFireball();

	void SetAllowHoldingKoopa(int value) { allowHodingKoopa = value; }
	void setHoldenKoopa(CKoopa* koopa) { holdenKoopa = koopa; koopa->SetHolden(1); }
	CKoopa* GetHoldenKoopa() { return holdenKoopa; }
	void releaseKoopa();

	void StartLevelTransform(int lastLevel, int newLevel);
	int GetLevelTransform() { return levelTransform; }
	void LevelUp();
	void LevelDown();
	void TurnIntoFire();
	void SetState(int state);
	void SetLevel(int l);
	int GetLevel() { return level; }

	void GetMargins(int& leftMargin, int& rightMargin);

	int GetUntouchable() { return untouchable; }
	void StartUntouchable() { untouchable = 1; untouchable_start = (DWORD)GetTickCount64(); }
	void StopUntouchable() { untouchable = 0; }
	void StartKicking() { kicking = 1; kicking_start = (DWORD)GetTickCount64(); };
	void StartRunning() { running_start = (DWORD)GetTickCount64(); }

	void SetSparkling();

	void StartSpinning();
	int GetHittableTail();
	void SetTail(float start_x, float end_x);
	void GetTail(float &start_x, float &end_x, float &start_y, float &end_y) { start_x = tail_start_x; end_x = tail_end_x; start_y = tail_start_y; end_y = tail_end_y; }
	
	int GetPowerLevel() { return powerLevel; }
	void ReducePowerLevel();

	// ready to switch scene (up/down the tube)
	void SetReadyUp(int state) { readyToUp = state; }
	void SetReadyDown(int state) { readyToDown = state; }

	int OutOfCamera();
	int PassedTheLevel() { return passedTheLevel; }
	void SetPassedTheLevel(int state) { passedTheLevel = state; }

	void StartSwitchingZone(int direction);
	int GetAllowSwitchingZone() { return allowSwichingZone; }
	void SetAllowSwitchingZone(int value) { allowSwichingZone = value; }

	void StartSpeedUp() { speed_up_start = (DWORD)GetTickCount64(); v0 = vx; }
	float GetMarioExpectedSpeedX(float limit_speed_x);

	void SetMagicWings(int state) { gainedMagicWings = state; }

	void AddStreakScore(CGameObject* coObject);
	void AddScore(int score, CGameObject* coObject);

	void SetInIntro(int value) { isInIntro = value; }
	int GetInIntro(int value) { return isInIntro; }

	int GetMarioFlyingState() { return fly; }
	int GetMarioFacingDirection() { return (nx > 0.0f) ? MARIO_FACING_RIGHT : MARIO_FACING_LEFT; }

	void StartDyingDelay() { dying_delay = 1; dying_delay_start = (DWORD)GetTickCount64(); }
	int GetDyingDelay() { return dying_delay; }

	CGameObject* GetFloor() { return floor; }
	void SetFloor(CGameObject* floor) { this->floor = floor; }
	void ClearFloor() { floor = NULL; }

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};