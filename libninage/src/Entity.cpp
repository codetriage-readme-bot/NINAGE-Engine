#include "includes/Entity.h"
#include "includes/Viewmode.h"


Entity::Entity(float x, float y, float z): Instance(x, y, z) {
    this->dx = 0.0f;
    this->dy = 0.0f;
    this->dz = 0.0f;
    this->dxrot = 0.0f;
    this->dyrot = 0.0f;
    this->dzrot = 0.0f;
    this->friction = 0.03f;
    this->xfriction = this->friction;
    this->yfriction = this->friction;
    this->yfriction = this->friction;
    this->rotationFriction = 0.06f;
}


/**
 * Updates physics, the goal is that
 * delta-x, delta-y, delta-z becomes `0`
 *
 * @param float delta
 */
void Entity::updatePhysics(float delta) {
    dx = EngineMath::toZero(dx, xfriction);
    dy = EngineMath::toZero(dy, yfriction);
    dz = EngineMath::toZero(dz, zfriction);
    
    dxrot = EngineMath::toZero(dxrot, rotationFriction);
    dyrot = EngineMath::toZero(dyrot, rotationFriction);
    dzrot = EngineMath::toZero(dzrot, rotationFriction);

    this->xrotation += this->dxrot * delta;
    this->yrotation += this->dyrot * delta;
    this->zrotation += this->dzrot * delta;
    
    this->position->x += this->dx * delta;
    this->position->y += this->dy * delta;
    this->position->z += this->dz * delta;
}


/**
 * "Pushes" the object into a certain direction with specified force.
 *
 * @param float degrees
 * @param float force
 */
void Entity::addForce(float degrees, float force, int mode) {
    this->dx += cos(EngineMath::toRadians(degrees)) * force;
    this->dy += sin(EngineMath::toRadians(degrees)) * force;

    if (mode == Viewmode::D3)
        this->dz += tan(EngineMath::toRadians(degrees)) * force;
}


/**
 * "Pushes" or adds rotation to the object.
 *
 * @param float rotation
 * @param int axis (0 = x, 1 = y, 2 = z)
 */
void Entity::addRotation(float rotation, int axis) {
    switch (axis) {
        case 0:
            this->dxrot += rotation;
        break;
        case 1:
            this->dyrot += rotation;
        break;
        case 2:
           this->dzrot += rotation;
        break;
    }
}

void mouseMoveEvent(
    int &mouseX,
    int &mouseY,
    int &deltaMouseX,
    int &deltaMouseY
) {

}

/**
 * Get the direction the object is moving in.
 *
 * @param float delta
 *
 * @return float
 */
float Entity::getMovingDirection(float delta) {
    float deltaY = this->getY() - (this->getY() + (this->dy * delta));
    float deltaX = this->getX() - (this->getX() + (this->dx * delta));
    return (float) (atan2(deltaY, deltaX) * 180 / M_PI);
}

/**
 * Check if entity's collisionbox intersects with
 * another entity's collisionbox.
 *
 * @return bool
 */
bool Entity::intersectsWith(float delta, Entity * entity) {

    if (this->centeredOrigo) {
        return
            (this->getX() - this->collisionBox->width / 2) + (this->dx * delta) <=
            entity->getX() + entity->collisionBox->width + (entity->dx * delta) &&
            
            this->getX() + this->collisionBox->width / 2 + (this->dx * delta) >=
            entity->getX() + (entity->dx * delta) &&
            
            (this->getY() - this->collisionBox->height) + (this->dy * delta) <=
            entity->getY() + entity->collisionBox->height + (entity->dy * delta) &&
            
            this->getY() + this->collisionBox->height + (this->dy * delta) >=
            entity->getY() + (entity->dy * delta) &&

            (this->getZ() - this->collisionBox->depth / 2) + (this->dz * delta) <=
            entity->getZ() + entity->collisionBox->depth + (entity->dz * delta) &&
            
            this->getZ() + this->collisionBox->depth / 2 + (this->dz * delta) >=
            entity->getZ() + (entity->dz * delta);
    } else {
        return
            (this->getX()) + (this->dx * delta) <=
            entity->getX() + entity->collisionBox->width + (entity->dx * delta) &&
            
            this->getX() + this->collisionBox->width + (this->dx * delta) >=
            entity->getX() + (entity->dx * delta) &&
            
            (this->getY() - this->collisionBox->height) + (this->dy * delta) <=
            entity->getY() + entity->collisionBox->height + (entity->dy * delta) &&
            
            this->getY() + this->collisionBox->height + (this->dy * delta) >=
            entity->getY() + (entity->dy * delta) &&

            (this->getZ()) + (this->dz * delta) <=
            entity->getZ() + entity->collisionBox->depth + (entity->dz * delta) &&
            
            this->getZ() + this->collisionBox->depth + (this->dz * delta) >=
            entity->getZ() + (entity->dz * delta);
    }
}
