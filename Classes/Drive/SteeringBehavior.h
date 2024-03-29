/********************************************************************
	created:	2016/01/17
	created:	17:1:2016   10:11
	filename: 	E:\Armada\Classes\Drive\SteeringBehavior.h
	file path:	E:\Armada\Classes\Drive
	file base:	SteeringBehavior
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef SteeringBehavior_h__
#define SteeringBehavior_h__

#include "cocos2d.h"

class Vehicle;

//--------------------------- Constants ----------------------------------


//
class SteeringBehavior
{
public:
	enum Deceleration{ slow = 3, normal = 2, fast = 1 };
	enum behavior_type
	{
		none = 0x00000,
		arrive = 0x00002,

		//
		boost			= 0x01000,
		breakdown		= 0x02000,
		turn_left		= 0x04000,
		turn_right		= 0x08000,
		wall_avoidance	= 0x10000,
		block_avoidance = 0x20000,


	};

	enum rot_dir
	{
		clockwise = -1,
		counter_clockwise = 1
	};
public:
	SteeringBehavior(Vehicle* agent);
	virtual ~SteeringBehavior();
	//
	cocos2d::Vec2 Calculate();
	float		  Torque(){ return mTorque; }
	//
	void SetTarget(const cocos2d::Vec2& t);
	void SetDeceleration(Deceleration d){ mDeceleration = d; }
	bool On(behavior_type bt){ return (mFlags & bt) == bt; }

	//计算平行于头部的驱动力
	float    ForwardComponent();

	//计算垂直于头部的驱动力
	float    SideComponent();
	//
	bool	 BlockAvoidance();
	//
	void SetMaxTorque(float t){ mMaxTorque = t; }
	void SetMaxBoost(float t){ mMaxBoost = t; }


protected:
	//
	Vehicle*		mVehicle;
	//驱动力
	cocos2d::Vec2   mSteeringForce;
	float			mTorque;
	//
	cocos2d::Vec2   mTarget;
	//
	Deceleration	mDeceleration;
	//
	int				mFlags;
	float			mMaxTorque;
	float			mMaxBoost;

	//
	bool		AccumulateForce(cocos2d::Vec2 &sf, const cocos2d::Vec2& ForceToAdd);
	cocos2d::Vec2 Arrive(const cocos2d::Vec2& TargetPos, Deceleration deceleration);
	cocos2d::Vec2 Boost();
	float TurnLeft();
	float TurnRight();
	cocos2d::Vec2 BreakDown();

public:
	void ArriveOn(){ mFlags |= arrive; }
	void ArriveOff(){ if(On(arrive))mFlags ^= arrive; }
	//
	void BoostOn(){ mFlags |= boost; }
	void BoostOff(){ if (On(boost))mFlags ^= boost; }
	void TurnLeftOn(){ mFlags |= turn_left; }
	void TurnLeftOff(){ if (On(turn_left))mFlags ^= turn_left; }
	void TurnRightOn(){ mFlags |= turn_right; }
	void TurnRightOff(){ if (On(turn_right))mFlags ^= turn_right; }
	void BreakDownOn(){ mFlags |= breakdown; }
	void BreakDownOff(){ if (On(breakdown))mFlags ^= breakdown; }

	//
	void BlockAvoidanceOn(){ mFlags |= block_avoidance; }
	void BlockAvoidanceOff(){ if (On(block_avoidance))mFlags ^= block_avoidance; }

};

#endif // SteeringBehavior_h__
