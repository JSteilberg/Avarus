#include "Corporeal.h"

Corporeal::Corporeal(const sf::Texture& texture,
                     const std::map<string, sf::IntRect>& texture_rects,
                     const VertexArray& vertices,
                     b2World& world) :
  texture_rects_(texture_rects),
  vertices_(vertices),
  texture_(texture),
  world_(world) {

  rot_ = 0.0;
  SetMainTextureRect(texture_rects_.at("norm"));
  body_def_.type = b2_dynamicBody;
  body_def_.position.Set(0, 5);
  body_ = world_.CreateBody(&body_def_);
}

void Corporeal::SetMainTextureRect(const sf::IntRect& rectangle) {
  vertices_[0].texCoords = sf::Vector2f(rectangle.left, rectangle.top);
  vertices_[1].texCoords = sf::Vector2f(rectangle.left, rectangle.top + rectangle.height);
  vertices_[2].texCoords = sf::Vector2f(rectangle.left + rectangle.width, rectangle.top + rectangle.height);
  vertices_[3].texCoords = sf::Vector2f(rectangle.left + rectangle.width, rectangle.top);
}

void Corporeal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // getTransform() is defined by sf::Transformable
  states.transform *= getTransform();
  states.transform.scale(16.0, 16.0);

  // Apply the current texture
  states.texture = &texture_;

  // Draw the vertex array
  target.draw(vertices_, states);
}

void Corporeal::Update(const sf::Time& deltaTime) {
  vel_ = vel_ + acc_;
  AddPos(vel_ * deltaTime.asSeconds());
  acc_ = Vector2f(0, 0);
  setPosition(body_->GetPosition().x / 16.f, -body_->GetPosition().y / 16.f);
  std::cout << body_->GetPosition().y << std::endl;
//  vertices_[0].position = Vector2f(body_->.GetVertex(0));//  vertices_[1].position = Vector2f(shape_.GetVertex(1));//  vertices_[2].position = Vector2f(shape_.GetVertex(2));//  vertices_[3].position = Vector2f(shape_.GetVertex(3));
}

void Corporeal::SetShape(const b2Vec2* vertices, int vertex_count) {
  shape_.Set(vertices, vertex_count);
  fixture_def_.shape = &shape_;
  fixture_def_.density = 1.0f;
fixture_def_.friction = 0.3f;
body_->CreateFixture(&fixture_def_);
}

void Corporeal::SetPos(Vector2f pos) {
  for(size_t i = 0; i < vertices_.getVertexCount(); ++i) {
    vertices_[i].position = pos / 16.f;
  }
  pos_ = pos;
}

void Corporeal::SetVel(Vector2f vel) {
  vel_ = vel;
}

void Corporeal::SetAcc(Vector2f acc) {
  acc_ = acc;
}

void Corporeal::SetRot(float rot) {
  const float diff = rot - rot_;
  //transform_.rotate(diff,
  rot_ = rot;
}

void Corporeal::AddPos(Vector2f posOffset) {
  for(size_t i = 0; i < vertices_.getVertexCount(); ++i) {
    vertices_[i].position += posOffset;
  }
  pos_ = pos_ + posOffset;
}

void Corporeal::AddVel(Vector2f velOffset) {
  vel_ = vel_ + velOffset;
}

void Corporeal::AddAcc(Vector2f accOffset) {
  acc_ = acc_ + accOffset;
}

void Corporeal::AddRot(float rotOffset) {
  SetRot(rot_ + rotOffset);
}

Corporeal::~Corporeal() {
  //dtor
}
