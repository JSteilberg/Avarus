#include "Entity.h"

Entity::Entity(const sf::Texture& texture,
                     const std::map<string, sf::IntRect>& texture_rects,
                     b2World& world) :
  texture_rects_(texture_rects),
  texture_(texture),
  sprite_(texture, texture_rects.at("norm")) {
  //sprite_.setScale(1,2);
  sprite_.setScale(width_ * consts::kPixelScale/texture_rects.at("norm").width,
                   height_ * consts::kPixelScale/texture_rects.at("norm").height);

  body_def_.type = b2_dynamicBody;
  body_def_.position.Set(0, 0);

  body_ = world.CreateBody(&body_def_);
}

void Entity::SetMainTextureRect(const sf::IntRect& rectangle) {
  //vertices_[0].texCoords = sf::Vector2f(rectangle.left, rectangle.top);
  //vertices_[1].texCoords = sf::Vector2f(rectangle.left, rectangle.top + rectangle.height);
  //vertices_[2].texCoords = sf::Vector2f(rectangle.left + rectangle.width, rectangle.top + rectangle.height);
  //vertices_[3].texCoords = sf::Vector2f(rectangle.left + rectangle.width, rectangle.top);
}

const sf::Sprite& Entity::GetSprite() const {
  return sprite_;
}

void Entity::Update(const sf::Time& deltaTime) {
  sprite_.setPosition(body_->GetPosition().x * consts::kPixelScale,
                      body_->GetPosition().y * consts::kPixelScale);
  sprite_.setRotation(body_->GetAngle());

  //std::cout << body_->GetPosition().x << "/" << body_->GetPosition().y << std::endl;
}

void Entity::SetShape(const b2Vec2* vertices, int vertex_count) {
  shape_.Set(vertices, vertex_count);
  fixture_def_.shape = &shape_;
  fixture_def_.density = 1.0f;
  fixture_def_.friction = 0.3f;
  body_->CreateFixture(&fixture_def_);
}

void Entity::SetPos(b2Vec2 pos) {
  body_->SetTransform(body_->GetPosition(), body_->GetAngle());
}

b2Vec2 Entity::GetPos() {
  return body_->GetPosition();
}

void Entity::SetVel(b2Vec2 vel) {
  body_->SetLinearVelocity(vel);
}

b2Vec2 Entity::GetVel() {
  return body_->GetLinearVelocity();
}

void Entity::SetRot(float rot) {
  sprite_.setRotation(rot);
  body_->SetTransform(body_->GetPosition(), rot);
}

float Entity::GetRot() {
  return body_->GetAngle();
}

void Entity::ApplyForce(b2Vec2 forceVec) {
  body_->ApplyForce(forceVec, body_->GetWorldCenter(), true);
}

Entity::~Entity() {
  //dtor
}

/*Entity::Entity(const sf::Texture& texture,
               const std::map<string, sf::IntRect>& texture_rects,
               b2World& world) :
  Entity(texture, texture_rects, world) {}
*/

