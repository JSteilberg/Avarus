#include "Entity.h"

Entity::Entity(const sf::Texture &atlas,
               const std::map<string, sf::IntRect> &texture_map, b2World &world)
    : texture_map_(texture_map), atlas_(atlas),
      sprite_(atlas, texture_map.at("norm")) {
  // sprite_.setScale(1,2);
  sprite_.setScale(width_ * consts::kPixelScale / texture_map.at("norm").width,
                   height_ * consts::kPixelScale /
                       texture_map.at("norm").height);

  body_def_.type = b2_dynamicBody;
  body_def_.position.Set(0, 0);

  body_ = world.CreateBody(&body_def_);

  SetCurrentTexture("norm");
}

void Entity::SetMainTextureRect(const sf::IntRect &rectangle) {}

const sf::Sprite &Entity::GetSprite() {
  sprite_.setPosition(body_->GetPosition().x * consts::kPixelScale,
                      body_->GetPosition().y * consts::kPixelScale);
  sprite_.setRotation(body_->GetAngle());
  return sprite_;
}

void Entity::Update(const sf::Time &deltaTime) {
  // Do nothing
}

void Entity::SetShape(const b2Vec2 *vertices, int vertex_count) {
  shape_.Set(vertices, vertex_count);
  fixture_def_.shape = &shape_;
  fixture_def_.density = 1.0f;
  fixture_def_.friction = 0.3f;
  body_->CreateFixture(&fixture_def_);
}

void Entity::SetCurrentTexture(std::string key) {
  current_texture_ = key;
  sprite_.setTextureRect(texture_map_.at(key));
}

string Entity::GetCurrentTexture() { return current_texture_; }
void Entity::SetPos(b2Vec2 pos) {
  body_->SetTransform(body_->GetPosition(), body_->GetAngle());
}

b2Vec2 Entity::GetPos() { return body_->GetPosition(); }

void Entity::SetVel(b2Vec2 vel) { body_->SetLinearVelocity(vel); }

b2Vec2 Entity::GetVel() { return body_->GetLinearVelocity(); }

void Entity::SetRot(float rot) {
  sprite_.setRotation(rot);
  body_->SetTransform(body_->GetPosition(), rot);
}

float Entity::GetRot() { return body_->GetAngle(); }

void Entity::ApplyForce(b2Vec2 forceVec) {
  body_->ApplyForce(forceVec, body_->GetWorldCenter(), true);
}

Entity::~Entity() {

  // dtor
}
