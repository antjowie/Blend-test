#pragma once
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\System\Time.hpp>

std::string getBlendModeName(const sf::BlendMode &blendMode);

class Object : public sf::Drawable
{
private:
	sf::Text m_text;
	sf::RectangleShape m_rect;
	sf::BlendMode m_blendMode;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override final;

public:
	Object(const float x, const float y, const float width, const float heigth, const sf::BlendMode &blendMode);
	Object(const sf::FloatRect &rect, const sf::BlendMode &blendMode);

	void setBlendMode(const sf::BlendMode & blendMode);
	void setPosition(const sf::Vector2f &pos);
	void setColor(const sf::Color &color);
};

