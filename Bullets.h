#ifndef BULLET_h
#define BULLET_h

#include "BaseFunctions.h"
#include "BaseObject.h"


struct Bullet : public BaseObjects
{
    int x_;
    int y_;
    int type;
    bool is_move;

    Bullet();
    ~Bullet();

    void loadBullet(string path, SDL_Renderer* renderer);
    void render_bullet(SDL_Renderer* renderer);

};


#endif // BULLET_h

