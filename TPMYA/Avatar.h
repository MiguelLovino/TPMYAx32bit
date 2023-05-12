#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

	using namespace std;
	using namespace sf;

	class Avatar
	{
	private:

		RectangleShape* rec_shape;
		b2Body* bod_avatar;
		b2Vec2 posicion;

	public:

		Avatar(b2Body* cuerpo, RectangleShape* figura);
		float radianes_a_grados(float radianes);

		void dibujar_ragdol(RenderWindow& ventana);

		void actualizar_ragdol();
	};


