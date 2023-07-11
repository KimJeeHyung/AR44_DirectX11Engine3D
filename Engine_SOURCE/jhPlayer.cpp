#include "jhPlayer.h"

namespace jh
{
	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	void Player::Initalize()
	{
		GameObject::Initialize();
	}

	void Player::Update()
	{
		GameObject::Update();
	}

	void Player::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}

	void Player::Render()
	{
		GameObject::Render();
	}
}