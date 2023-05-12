#include "Game.h"

Game::Game(int alto, int ancho, string titulo)
{
	pWnd = new RenderWindow(VideoMode(alto, ancho), titulo);
	fps = 60.f;
	tiempoFrame = 1.f / fps;
	pWnd->setFramerateLimit(fps);
	cargar_imagenes();
	set_zoom();
	iniciar_fisica();

	//inicializo objetos



	for (int i = 0; i < 6; i++)
	{
		Ragdolino[i] = new Avatar(bod_ragdol[i], fig_ragdol[i]);

	}

	for (int i = 0; i < 5; i++)
	{
		puente_blando[i] = new Avatar(bod_puente[i], fig_puente[i]);

	}

	pisolino = new Avatar(bod_piso, piso);

}

void Game::UpdateGame() //actualizo los objetos
{
	for (int i = 0; i < 6; i++)
	{
		Ragdolino[i]->actualizar_ragdol();
	}

	for (int i = 0; i < 5; i++)
	{
		puente_blando[i]->actualizar_ragdol();
	}

	pisolino->actualizar_ragdol();
}

void Game::DrawGame()
{
	for (int i = 0; i < 6; i++)
	{
		Ragdolino[i]->dibujar_ragdol(*pWnd);
	}

	for (int i = 0; i < 5; i++)
	{
		puente_blando[i]->dibujar_ragdol(*pWnd);

	}

	pisolino->dibujar_ragdol(*pWnd);
}

void Game::ProcessCollisions()
{
}

void Game::cargar_imagenes()
{
	piso = new RectangleShape(Vector2f(10, 2));
	piso->setFillColor(Color::Blue);
	for (int i = 0; i < 6; i++)
	{
		fig_ragdol[i] = new RectangleShape;
	}
	/*************/
	for (int i = 0; i < 5; i++)
	{
		fig_puente[i] = new RectangleShape;
		fig_puente[i]->setFillColor(Color::Red);

	}
	/************************/
	fig_ragdol[0]->setFillColor(Color::White);
	fig_ragdol[1]->setFillColor(Color::Color(15, 50, 59));
	fig_ragdol[2]->setFillColor(Color::Yellow);
	fig_ragdol[3]->setFillColor(Color::Green);
	fig_ragdol[4]->setFillColor(Color::Color(170, 50, 59));
	fig_ragdol[5]->setFillColor(Color::Red);
}

void Game::iniciar_fisica()
{
	//creo el mundo
	mundo = new b2World(b2Vec2(0.f, 9.8f));

	/***************************/
	def_puente[0].position = (b2Vec2(49.8f, 97.f)); //1
	def_puente[1].position = (b2Vec2(51.f, 97.f)); //2
	def_puente[2].position = (b2Vec2(52.2f, 97.f)); //3
	def_puente[3].position = (b2Vec2(49.8f - 0.9f, 97.7f)); //poste izquierd
	def_puente[4].position = (b2Vec2(52.2f + 0.9f, 97.7f)); //poste derecho

	for (int i = 0; i < 5; i++)
	{
		if (i < 3)
		{
			def_puente[i].type = b2_dynamicBody;
		}
		else
		{
			// los parantes son estaticos
			def_puente[i].type = b2_staticBody;
		}
		bod_puente[i] = mundo->CreateBody(&def_puente[i]);
	}

	b2PolygonShape shape_puente[5];

	shape_puente[0].SetAsBox(0.6f, 0.2f);
	shape_puente[1].SetAsBox(0.6f, 0.2f);
	shape_puente[2].SetAsBox(0.6f, 0.2f);
	shape_puente[3].SetAsBox(0.2f, 1.3f);
	shape_puente[4].SetAsBox(0.2f, 1.3f);

	for (int i = 0; i < 5; i++)
	{
		fix_def_puente[i].shape = &shape_puente[i];
		fix_def_puente[i].density = 0.4f;
		fix_def_puente[i].restitution = 0.1f;
		fix_def_puente[i].friction = 0.1f;
		fix_puente[i] = bod_puente[i]->CreateFixture(&fix_def_puente[i]);
	}

	//resortes del puente

	def_joint_puente[0].Initialize(bod_puente[3], bod_puente[0], b2Vec2(bod_puente[3]->GetPosition().x, bod_puente[3]->GetPosition().y - 1.0f), b2Vec2(bod_puente[0]->GetPosition().x - 0.25f, bod_puente[0]->GetPosition().y));
	def_joint_puente[1].Initialize(bod_puente[0], bod_puente[1], b2Vec2(bod_puente[0]->GetPosition().x + 0.25, bod_puente[0]->GetPosition().y), b2Vec2(bod_puente[1]->GetPosition().x - 0.25, bod_puente[1]->GetPosition().y));
	def_joint_puente[2].Initialize(bod_puente[1], bod_puente[2], b2Vec2(bod_puente[1]->GetPosition().x + 0.25, bod_puente[1]->GetPosition().y), b2Vec2(bod_puente[2]->GetPosition().x - 0.25, bod_puente[2]->GetPosition().y));
	def_joint_puente[3].Initialize(bod_puente[2], bod_puente[4], b2Vec2(bod_puente[2]->GetPosition().x + 0.25, bod_puente[2]->GetPosition().y), b2Vec2(bod_puente[4]->GetPosition().x, bod_puente[4]->GetPosition().y - 1.0f));

	for (int i = 0; i < 4; i++)
	{
		def_joint_puente[i].collideConnected = true;
		def_joint_puente[i].dampingRatio = 0.3f;
		def_joint_puente[i].frequencyHz = 6.0f;
		def_joint_puente[i].length = 0.50f;

		joint_puente[i] = (b2DistanceJoint*)mundo->CreateJoint(&def_joint_puente[i]); //hay que castear
	}

	/*****************************/

	//creacion del suelo
	// 
	//definicion_body (piso)
	boddef_piso.type = b2_staticBody; //def
	boddef_piso.position = b2Vec2(50.f, 100.f); //def

	//body del piso en el mundo
	bod_piso = mundo->CreateBody(&boddef_piso); // linkeo el body a su definicion creada por el mundo

	//creo una shape para asignar al fixture
	b2PolygonShape shape_piso;
	shape_piso.SetAsBox(50.f, 1.f); // tiene que ser la mitad de la caja (en x, y)

	//definicion fixture piso
	fixdef_piso.shape = &shape_piso;
	fixdef_piso.density = 0.1f; // densidad = masa / volumen
	fixdef_piso.friction = 0.3f;
	fixdef_piso.restitution = 0.1f; //rebote (1.0 = infinito el rebote)

	//fix
	fix_piso = bod_piso->CreateFixture(&fixdef_piso); //uno las propiedades fisicas al body.

	//ragdoll

	//posicion de los cuerpos del ragdol en el mundo
	boddef_ragdol[0].position = b2Vec2(50.f, 90.1f); //cabeza
	boddef_ragdol[1].position = b2Vec2(50.f, 90.65f); //torzo
	boddef_ragdol[2].position = b2Vec2(50.32f, 90.5f); //brazod
	boddef_ragdol[3].position = b2Vec2(49.68f, 90.5f); //brazoi
	boddef_ragdol[4].position = b2Vec2(50.09f, 91.5f); //piernad
	boddef_ragdol[5].position = b2Vec2(49.91f, 91.5f); //piernai

	for (int i = 0; i < 6; i++)
	{
		boddef_ragdol[i].type = b2_dynamicBody;
		bod_ragdol[i] = mundo->CreateBody(&boddef_ragdol[i]);
	}

	b2PolygonShape shape_ragdol[6];

	shape_ragdol[0].SetAsBox(0.1, 0.1); //cabeza
	shape_ragdol[1].SetAsBox(0.2, 0.4); //torzo
	shape_ragdol[2].SetAsBox(0.07, 0.3); //brazod
	shape_ragdol[3].SetAsBox(0.07, 0.3); //brazoi
	shape_ragdol[4].SetAsBox(0.07, 0.4); //piernad
	shape_ragdol[5].SetAsBox(0.07, 0.4); //piernai

	for (int i = 0; i < 6; i++)
	{
		fixdef_ragdol[i].shape = &shape_ragdol[i];
		fixdef_ragdol[i].density = 0.5f;
		fixdef_ragdol[i].friction = 0.1f;
		fixdef_ragdol[i].restitution = 0.7f;
		fix_ragdol[i] = bod_ragdol[i]->CreateFixture(&fixdef_ragdol[i]);

	}

	//inicializacion de resortes
		//union de resortes

		//cabeza[0] a pecho [1]
	joint_def_ragdolino[0].Initialize(bod_ragdol[0], bod_ragdol[1], b2Vec2(bod_ragdol[0]->GetPosition().x, bod_ragdol[0]->GetPosition().y + 0.08), b2Vec2(bod_ragdol[1]->GetPosition().x, bod_ragdol[1]->GetPosition().y - 0.4));
	//pecho[1] a brazo derecho[2]
	joint_def_ragdolino[1].Initialize(bod_ragdol[1], bod_ragdol[2], b2Vec2(bod_ragdol[1]->GetPosition().x + 0.18, bod_ragdol[1]->GetPosition().y - 0.38), b2Vec2(bod_ragdol[2]->GetPosition().x - 0.05, bod_ragdol[2]->GetPosition().y - 0.28));
	//pecho[1] a brazo izquierdo[3]
	joint_def_ragdolino[2].Initialize(bod_ragdol[1], bod_ragdol[3], b2Vec2(bod_ragdol[1]->GetPosition().x - 0.18, bod_ragdol[1]->GetPosition().y - 0.38), b2Vec2(bod_ragdol[3]->GetPosition().x + 0.05, bod_ragdol[3]->GetPosition().y - 0.28));
	//pecho[1] a pierna  derecha[4]
	joint_def_ragdolino[3].Initialize(bod_ragdol[1], bod_ragdol[4], b2Vec2(bod_ragdol[1]->GetPosition().x + 0.09, bod_ragdol[1]->GetPosition().y + 0.38), b2Vec2(bod_ragdol[4]->GetPosition().x, bod_ragdol[4]->GetPosition().y - 0.38));
	//pecho[1] a pierna izquierda[5]
	joint_def_ragdolino[4].Initialize(bod_ragdol[1], bod_ragdol[5], b2Vec2(bod_ragdol[1]->GetPosition().x + 0.09, bod_ragdol[1]->GetPosition().y + 0.38), b2Vec2(bod_ragdol[5]->GetPosition().x, bod_ragdol[5]->GetPosition().y - 0.38));

	for (int i = 0; i < 5; i++)
	{
		joint_def_ragdolino[i].dampingRatio = 0.3f; //rebote
		joint_def_ragdolino[i].frequencyHz = 4.0f;
		joint_def_ragdolino->collideConnected = true;
		//joint_def_ragdolino[i].length = 0.025f;
		joint_ragdolino[i] = (b2DistanceJoint*)mundo->CreateJoint(&joint_def_ragdolino[i]); //hay que castear
	}
}

void Game::ProcessEvent(Event& evt)
{

	switch (evt.type)
	{
	case Event::Closed:
		pWnd->close();
		break;

		//evento de teclado
	case Event::KeyPressed:

		if (evt.key.code == Keyboard::Escape)
		{
			pWnd->close();
		}

		if (evt.key.code == Keyboard::A)
		{
			//para mover uso set transform
			//bod_piso->SetTransform(bod_piso->GetPosition(), bod_piso->GetAngle() - grados_a_radiannes(2.f));
		}
		else if (evt.key.code == Keyboard::D)
		{
			//bod_piso->SetTransform(bod_piso->GetPosition(), bod_piso->GetAngle() + grados_a_radiannes(2.f));
		}
		else if (evt.key.code == Keyboard::S)
		{
			bod_puente[0]->SetTransform(b2Vec2(bod_puente[0]->GetPosition().x, bod_puente[0]->GetPosition().y + 1.9f), bod_puente[0]->GetAngle());
			bod_puente[1]->SetTransform(b2Vec2(bod_puente[1]->GetPosition().x, bod_puente[1]->GetPosition().y + 1.9f), bod_puente[1]->GetAngle());
			bod_puente[2]->SetTransform(b2Vec2(bod_puente[2]->GetPosition().x, bod_puente[2]->GetPosition().y + 1.9f), bod_puente[2]->GetAngle());

		}
		break;
	}

}

void Game::set_zoom()
{
	camara1 = new View({ 10.f,5.f }, { 30.f, 30.f });
	camara1->move(40.f, 85.f);
	pWnd->setView(*camara1);
}

void Game::actualizar_fisica()
{

	mundo->Step(tiempoFrame, 8, 8);
	mundo->ClearForces();

}

float Game::grados_a_radiannes(float grados)
{
	float pi = 3.14;



	return grados * pi / 180;
}

float Game::radianes_a_grados(float radianes)
{
	float pi = 3.14;

	return radianes / pi * 180;
}

void Game::Go() {
	//objeto para recibir eventos
	Event evt;
	while (pWnd->isOpen()) {
		//procesar eventos
		while (pWnd->pollEvent(evt))
			ProcessEvent(evt);
		//procesar colisiones
		ProcessCollisions();
		//actualizar estados de objetos
		UpdateGame();
		pWnd->clear();
		actualizar_fisica();
		DrawGame();
		pWnd->display();
	}
}

Game::~Game()
{
}