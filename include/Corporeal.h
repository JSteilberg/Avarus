#ifndef CORPOREAL_H
#define CORPOREAL_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

#include "Atlas.h"
#include "Constants.h"

using std::string;

// A Corporeal is a Drawable with the ability to collide and return opposite forces
// As well as move. It has a mass, position, velocity, acceleration, and rotation
class Corporeal : public sf::Drawable {
 public:

  // Set the main bounding rectangle for this Corporeal's sf::Texture
  void SetMainTextureRect(const sf::IntRect& rectangle);

  // Set this Corporeal's position
  void SetPos(b2Vec2 pos);

  // Get this Corporeal's position
  b2Vec2 GetPos();

  // Set this Corporeal's velocity
  void SetVel(b2Vec2 vel);

  // Get this Corporeal's velocity
  b2Vec2 GetVel();

  // Set this Corporeal's rotation
  void SetRot(float rot);

  // Get this Corporeal's rotation
  float GetRot();

  // Apply a force to this Corporeal
  void ApplyForce(b2Vec2 forceVec);

  // Update this Corporeal with a given deltaTime
  void Update(const sf::Time& deltaTime);

  // Get the type ID for this Corporeal
  virtual int GetTypeId() const = 0;

  // Sets the shape of this Corporeal's body
  void SetShape(const b2Vec2* vertices, int vertex_count);

  // Gets the sprite used to draw this Corporeal
  const sf::Sprite& GetSprite() const;

  virtual ~Corporeal();

 protected:

  // Basic constructor that includes the atlas texture and corresponding
  // texture rects
  Corporeal(const sf::Texture& texture,
            const std::map<string, sf::IntRect>& texture_rects,
            b2World& world);

  // Map of texture subsets to be used by this Corporeal. The first texture will be mapped to "main".
  const std::map<string, sf::IntRect>& texture_rects_;

  // Array of sf::Vector2f that define the shape of this Corporeal
  //VertexArray vertices_;

  // Reference to the texture to be used
  const sf::Texture& texture_;

  // Sprite used to draw this Corporeal
  sf::Sprite sprite_;

  b2BodyDef body_def_;

  b2Body* body_;

  b2PolygonShape shape_;

  b2FixtureDef fixture_def_;

  float width_ = 1;

  float height_ = 2;


 private:
};

#endif // CORPOREAL_H
