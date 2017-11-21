#include "Game.h"

#include "img/bullet_img.h"

static bool alt = false;
static BYTE num_bullts = 0;

static void wait(Process *me) {
  Object *o = me->o;
  if (o->z - Camera::z > 256) {
    me->suicide();
    return;
  }
  o->theta -= 15;
  //  if (o->lines == bullet1_img) {
  //    o->lines = bullet2_img;
  //  }
  //  else {
  //    o->lines = bullet1_img;
  //  }
  me->sleep(1);
}

void bullet_process(Process *me) {
  Object *o = ObjectManager::alloc();
  if (!o) {
    me->suicide();
    return;
  }
  o->z = Camera::z;
  if (alt) {
    o->x = Camera::x + 20;
    o->y = Camera::y - 20;
  }
  else {
    o->x = Camera::x - 20;
    o->y = Camera::y - 20;
  }
  alt = !alt;
  o->vz = BULLET_VZ;
  o->lines = bullet1_img;
  me->o = o;
  me->sleep(1, wait);
}
