#include "Player.h"

Player::Player(GraphicsBuffer * pBuffer, float srcX, float srcY, float width, float height)
:Sprite(pBuffer, srcX, srcY, width, height)
,mPos(100, 100)
{
}