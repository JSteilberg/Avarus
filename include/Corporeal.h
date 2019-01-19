#ifndef CORPOREAL_H
#define CORPOREAL_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

#include "Atlas.h"
#include "Vector2f.h"
#include "VertexArray.h"

using std::string;

// A Corporeal is a Drawable with the ability to collide and return opposite forces
// As well as move. It has a mass, position, velocity, acceleration, and rotation
class Corporeal : public sf::Drawable, public sf::Transformable {
 public:

  // Set the main bounding rectangle for this Corporeal's sf::Texture
  void SetMainTextureRect(const sf::IntRect& rectangle);

  // Draw member function inherited from sf::Drawable, called when this Corporeal is drawn
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  // Set this Corporeal's position to a given Vector2f
  void SetPos(Vector2f pos);

    // Set this Corporeal's velocity
  void SetVel(Vector2f vel);

  // Set this Corporeal's acceleration
  void SetAcc(Vector2f acc);

  // Set this Corporeal's rotation
  void SetRot(float rot);

  // Offset this Corporeal's position by a given Vector2f
  void AddPos(Vector2f posOffset);

  // Add to this Corporeal's velocity
  void AddVel(Vector2f velOffset);

  // Add to this Corporeal's acceleration
  void AddAcc(Vector2f accOffset);

  // Add to this Corporeal's rotation
  void AddRot(float rotOffset);

  // Apply a force to this Corporeal, as a vector with units N*m/s^2
  void Force(Vector2f forceVect);

  // Update this Corporeal with a given deltaTime
  void Update(const sf::Time& deltaTime);

  // Return this Corporeal's VertexArray, but transformed
  sf::VertexArray ApplyTransform();

  // Project this Corporeal onto a given Vector2f and return it
  Vector2f Project(Vector2f proj);

  // Get the type ID for this Corporeal
  virtual int GetTypeId() const = 0;

  void SetShape(const b2Vec2* vertices, int vertex_count);

  virtual ~Corporeal();

 protected:

  // Constructs this Corporeal without any texture, only vertices
  Corporeal(const sf::Texture& texture,
            const std::map<string, sf::IntRect>& texture_rects,
            const VertexArray& vertices,
            b2World& world);

  // Map of texture subsets to be used by this Corporeal. The first texture will be mapped to "main".
  const std::map<string, sf::IntRect>& texture_rects_;

  // Array of sf::Vector2f that define the shape of this Corporeal
  VertexArray vertices_;

  // Used for transforming vertices in the VertexArray
  sf::Transform transform_;

  // Reference to the texture to be used
  const sf::Texture& texture_;

  // x and y position of this Corporeal
  Vector2f pos_;

  // x and y velocity of this Corporeal
  Vector2f vel_;

  // x and y acceleration of this Corporeal
  Vector2f acc_;

  // Mass of this Corporeal, in Kilograms
  float mass_;

  // Angle of this Corporeal, in Radians
  float rot_;

  b2World& world_;

  // From Box2d, used
  b2BodyDef body_def_;

  b2Body* body_;

  b2PolygonShape shape_;

  b2FixtureDef fixture_def_;

 private:
};

#endif // CORPOREAL_H
