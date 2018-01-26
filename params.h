#ifndef __PARAMS_H__
#define __PARAMS_H__

struct Params
{
    USVec2D targetPosition;
    float max_velocity;
    float max_acceleration;
    float dest_radius;
	float arrive_radius;

	float max_angular_velocity;
	float max_angular_acceleration;
	float angular_arrive_radius;
	float angular_dest_radius;
	float targetRotation;

	float look_ahead;
	float time_ahead;

	float char_radius;
};

bool ReadParams(const char* filename, Params& params);

#endif