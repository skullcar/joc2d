#ifndef _ANIMATION_KEYFRAMES
#define _ANIMATION_KEYFRAMES

#include "General.h"

// AnimKeyframes contains all information related to a single animation.
// These are the animation speed measured by millisecsPerKeyframe
// and texture coordinates for all keyframes.

struct KeyFrame {
	glm::vec2 keyframeDispl;
	//ATAQUES
	bool attack;
	int damage;
	glm::ivec2 hitbox;
	int distance;
};


struct AnimKeyframes
{
	float millisecsPerKeyframe;
	vector<KeyFrame> keyframes;
};


#endif // _ANIMATION_KEYFRAMES//


