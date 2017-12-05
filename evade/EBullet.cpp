#define DEBUGME
//#undef DEBUGME

#include "Game.h"

#include "img/ebullet_img.h"

void EBullet::genocide() {
  for (Object *o = ObjectManager::first(); o;) {
    Object *next = o->next;
    if ((o->flags & OFLAG_ENEMY_BULLET)) {
      ObjectManager::free(o);
    }
    o = next;
  }
}

void EBullet::run() {
  for (Object *o = ObjectManager::first(); o;) {
    Object *next = o->next;
    if (o->flags & OFLAG_ENEMY_BULLET) {
      if (game_mode != MODE_GAME) {
        ObjectManager::free(o);
      }
      else {
        float dz = o->z - Camera::z;

        // If enemy bullet collides with player
        if (abs(dz) < abs(o->vz) && abs(o->x - Camera::x) < 32 && abs(o->y - Camera::y) < 32) {
          Player::hit(10);
          //        Player::flags |= PLAYER_FLAG_HIT;
          //        Sound::play_sound(SFX_PLAYER_HIT_BY_ENEMY);
          ObjectManager::free(o);
        }
        else if (dz < 0 || --o->state <= 0) {
          ObjectManager::free(o);
        }
        else {
          o->theta += 40;
        }
      }
    }
    o = next;
  }
}

BOOL EBullet::fire(Object *oo) {
  const FLOAT frames = 64; // time to hit player (how many ticks)

  Object *o = ObjectManager::alloc();
  if (!o) {
    return FALSE;
  }

  o->flags |= OFLAG_ENEMY_BULLET;
  o->lines = ebullet_img;
  o->state = 128; // timeout

  Sound::play_sound(SFX_ENEMY_SHOOT);

  // position the bullet
  o->x = oo->x - 8;
  o->y = oo->y - 8; //  - 32;
  o->z = oo->z;
  // fly at the player (where he will be in Z)
  o->vx = (Camera::x - o->x) / frames;
  o->vy = (Camera::y - o->y) / frames;
  o->vz = Camera::vz - (o->z - Camera::z) / frames;
  return TRUE;
}
