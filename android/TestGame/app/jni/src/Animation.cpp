#include "./Animation.h"

Animation::Animation() {

}

Animation::Animation(int index, int numFrames, int animationSpeed) {
    this->index = index;
    this->numFrames = numFrames;
    this->animationSpeed = animationSpeed;
}
