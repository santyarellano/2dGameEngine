#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
    public:
        unsigned int index;
        unsigned int numFrames;
        unsigned int animationSpeed;
        Animation();
        Animation(int index, int numFrames, int animationSpeed);
};

#endif
