#include "Object.h"
#include "SFML\Graphics\RenderTarget.hpp"
#include <iostream>

void Object::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_text);
	
	states.blendMode = m_blendMode;
	target.draw(m_rect, states);
}

Object::Object(const float x, const float y, const float width, const float heigth, const sf::BlendMode &blendMode):
	Object(sf::FloatRect(x,y,width,heigth),blendMode)
{
}

Object::Object(const sf::FloatRect & rect, const sf::BlendMode & blendMode):
	m_blendMode(blendMode)
{
	m_rect.setPosition(rect.left, rect.top);
	m_rect.setSize(sf::Vector2f(rect.width, rect.height));
	m_rect.setFillColor(sf::Color::Black);

	// Ugliest code ever
	static sf::Font font;
	static bool initiated{ false };
	if (!initiated)
	{
		font.loadFromFile("font.ttf");
		initiated = true;
	}

	m_text.setFont(font);
	m_text.setFillColor(sf::Color::Black);
	m_text.setString(getBlendModeName(blendMode));
	m_text.setOrigin(m_text.getLocalBounds().width / 2,m_text.getLocalBounds().height / 2);
	m_text.setPosition(rect.left + rect.width / 2, rect.top  - 50);
}

void Object::setBlendMode(const sf::BlendMode & blendMode)
{
	m_blendMode = blendMode;
	m_text.setString(getBlendModeName(m_blendMode));
	std::cout << getBlendModeName(m_blendMode) << '\n';
}

void Object::setPosition(const sf::Vector2f & pos)
{
	m_rect.setPosition(pos);
}

void Object::setColor(const sf::Color & color)
{
	m_rect.setFillColor(color);
}

std::string getBlendModeName(const sf::BlendMode & blendMode)
{
	if (blendMode == sf::BlendAdd)
		return "Add";
	else if (blendMode == sf::BlendAlpha)
		return "Alpha";
	else if (blendMode == sf::BlendMultiply)
		return "Mult";
	else if (blendMode == sf::BlendNone)
		return "None";
	else
		return "Null";
}
