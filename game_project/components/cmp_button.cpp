// Button component C++ file
#include"cmp_button.h"
#include<SFML/Window.hpp>
#include <system_renderer.h>
#include <system_resources.h>
#include "engine.h"
#include "../game.h"

using namespace sf;
using namespace std;

unique_ptr<Button> button;
button_states Button::_key_pressed;

void Button::update(double dt) {
  // Hover statement
  if (selected)
  {
    //Pressed statement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
      buttonState = BUTTON_ACTIVED;
      if (_key_pressed == BUTTON_IDLE)
        _key_pressed = BUTTON_ACTIVED;
      else if (_key_pressed == BUTTON_ACTIVED)
        _key_pressed = BUTTON_DOWN;
    }
    else
    {
      buttonState = BUTTON_HOVER;
    }
  }
  else
    buttonState = BUTTON_IDLE;

  switch (buttonState)
  {
    case BUTTON_IDLE:
      shape.setFillColor(idleColor);
      break;
    case BUTTON_HOVER:
      shape.setFillColor(hoverColor);
      break;
    case BUTTON_ACTIVED:
      shape.setFillColor(activeColor);
      break;
    default:
      shape.setFillColor(sf::Color::Cyan);
      break;
  }
}
//Draws the button
void Button::render() {
  Renderer::queue(&shape);
  Renderer::queue(&_text);
}
//Constructor
Button::Button(Entity* p, sf::Vector2f position, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
        : Component(p), selected(false) {
  buttonState = BUTTON_IDLE;
  shape.setSize(sf::Vector2f(200, 70));
  shape.setPosition(position - (shape.getSize() / 2.f));
  shape.setOrigin(0, 0);

  _text.setString(text);
  _text.setFillColor(sf::Color::Black);
  _text.setCharacterSize(20);
  font = Resources::get<sf::Font>("RobotoMono-Regular.ttf");
  _text.setFont(*font);

  _text.setPosition(Vector2f(
          (shape.getPosition().x + shape.getLocalBounds().width / 2.f) - (_text.getLocalBounds().width / 2),
          (shape.getPosition().y + shape.getLocalBounds().height / 2.f) - (_text.getLocalBounds().height / 2)));

  this->activeColor = activeColor;
  this->hoverColor = hoverColor;
  this->idleColor = idleColor;

  shape.setFillColor(idleColor);
}

// Returns true if button is pressed and false otherwise
const bool Button::isPressed() const
{
  if (buttonState == BUTTON_ACTIVED)
  {
    if (_key_pressed == BUTTON_ACTIVED)
      return true;
  }

  return false;
}

const Vector2f Button::getSize() { return shape.getSize(); }