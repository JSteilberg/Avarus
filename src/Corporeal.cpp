#include "Corporeal.h"

Corporeal::Corporeal(const sf::Texture& texture,
                     const std::map<string, sf::IntRect>& texture_rects,
                     b2World& world) :
  texture_rects_(texture_rects),
  texture_(texture),
  sprite_(texture, texture_rects.at("norm")) {

  body_def_.type = b2_dynamicBody;
  body_def_.position.Set(0, 0);

  body_ = world.CreateBody(&body_def_);
}

void Corporeal::SetMainTextureRect(const sf::IntRect& rectangle) {
  //vertices_[0].texCoords = sf::Vector2f(rectangle.left, rectangle.top);
  //vertices_[1].texCoords = sf::Vector2f(rectangle.left, rectangle.top + rectangle.height);
  //vertices_[2].texCoords = sf::Vector2f(rectangle.left + rectangle.width, rectangle.top + rectangle.height);
  //vertices_[3].texCoords = sf::Vector2f(rectangle.left + rectangle.width, rectangle.top);
}

const sf::Sprite& Corporeal::GetSprite() const {
  return sprite_;
}

void Corporeal::Update(const sf::Time& deltaTime) {
  sprite_.setPosition(body_->GetPosition().x * consts::kPixelScale,
                      body_->GetPosition().y * consts::kPixelScale);
  sprite_.setRotation(body_->GetAngle());

  //std::cout << body_->GetPosition().x << "/" << body_->GetPosition().y << std::endl;
}

void Corporeal::SetShape(const b2Vec2* vertices, int vertex_count) {
  shape_.Set(vertices, vertex_count);
  fixture_def_.shape = &shape_;
  fixture_def_.density = 1.0f;
  fixture_def_.friction = 0.3f;
  body_->CreateFixture(&fixture_def_);
}

void Corporeal::SetPos(b2Vec2 pos) {
  body_->SetTransform(body_->GetPosition(), body_->GetAngle());
}

b2Vec2 Corporeal::GetPos() {
  return body_->GetPosition();
}

void Corporeal::SetVel(b2Vec2 vel) {
  body_->SetLinearVelocity(vel);
}

b2Vec2 Corporeal::GetVel() {
  return body_->GetLinearVelocity();
}

void Corporeal::SetRot(float rot) {
  sprite_.setRotation(rot);
  body_->SetTransform(body_->GetPosition(), rot);
}

float Corporeal::GetRot() {
  return body_->GetAngle();
}

void Corporeal::ApplyForce(b2Vec2 forceVec) {
  body_->ApplyForce(forceVec, body_->GetWorldCenter(), true);
}

Corporeal::~Corporeal() {
  //dtor
}
