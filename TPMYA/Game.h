#pragma once
#include <SFML/Window.hpp> 
#include <SFML/Graphics.hpp> 
#include <Box2D/Box2D.h>
#include "Avatar.h"
#include <string> 
#include <iostream>

	using namespace sf;
	using namespace std;
	class Game {
	private:
		RenderWindow* pWnd;
		void ProcessEvent(Event& evt);
		void DrawGame();
		void UpdateGame();
		void ProcessCollisions();

		View* camara1;
		b2World* mundo;

		//piso

		//*****************///
		RectangleShape* fig_puente[5];
		b2Body* bod_puente[5];
		b2BodyDef def_puente[5];
		b2Fixture* fix_puente[5]; //todos iguales, uso el mismo fixture
		b2FixtureDef fix_def_puente[5];

		//resortes del puente

		b2DistanceJoint* joint_puente[4];
		b2DistanceJointDef def_joint_puente[4];


		//********************//



		RectangleShape* piso;
		b2Vec2 piso_posicion;

		b2Body* bod_piso;
		b2BodyDef boddef_piso; //no puede ser puntero
		b2Fixture* fix_piso;
		b2FixtureDef fixdef_piso; //no puede ser puntero

		//ragdoll

		b2Body* bod_ragdol[6];
		b2BodyDef boddef_ragdol[6];
		b2Fixture* fix_ragdol[6];
		b2FixtureDef fixdef_ragdol[6];

		RectangleShape* fig_ragdol[6];

		float fps, tiempoFrame;

		//avatares
		Avatar* Ragdolino[6];
		Avatar* pisolino;
		//**************//
		Avatar* puente_blando[5];
		//**************//

		// Resortes del ragdoll
		b2DistanceJoint* joint_ragdolino[5];
		b2DistanceJointDef joint_def_ragdolino[5];
	public: Game(int alto, int ancho, string titulo);
		  ~Game(void);
		  void Go();
		  void cargar_imagenes();
		  void set_zoom();
		  void iniciar_fisica();
		  void actualizar_fisica();
		  float grados_a_radiannes(float grados);
		  float radianes_a_grados(float radianes);

		  //TODO 
		  //a este proyecto queda empeza a realizar las clases.
	};


