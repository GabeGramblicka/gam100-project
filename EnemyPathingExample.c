//------------------------------------------------------------------------------
// file:	EnemyPathingExample.c
// author:	Gabe Gramblicka
// 
//
// brief:	file that shows off some quick-and-dirty code for
//        moving enemies in the game.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2023 DigiPen, All rights reserved.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// function: MovementInit
// author:	Gabe Gramblicka
//
// description:	this function handles detection and takes in 4 vectors to pass
//              to the MoveEnemies function
//
//------------------------------------------------------------------------------
void MovementInit(object* enemy, float SPEED, EnemyPoints v1, EnemyPoints v2, 
                                              EnemyPoints v3, EnemyPoints v4)
{
	detection = CP_Image_Load("./Assets/detection.png");

	if (EnemyCircleVision(enemy, thePlayer))
	{
    // Checks for a full police officer suit (hat and coat)
		if (!(thePlayer->which_key[4] == 1 && thePlayer->which_key[3] == 1))
		{
      // Within vision
      CP_Vector vec = CP_Vector_Set(enemy->dirX, enemy->dirY));

			if (EnemyVision(enemy, thePlayer, CP_Vector_Normalize(vec))
			{
        // Making sure it's not in a box (box hides detection)
				if (thePlayer->in_box == 0)
				{
					float temp_timer = enemy->timer5;

          // Draws the red outline to show detection
					stopwatch(&enemy->timer5, 255);
					CP_Image_Draw(detection, (1920 / 2), (1280 / 2), 1920, 1280, 
                       (int)(temp_timer * 100));

					enemy->detectiontimer--;

					if (enemy->detectiontimer <= 0)
					{
            // Moves the player to the defeat scene
						GotCaught(thePlayer, thePlayer->current_room);
					}
				}
			}
		}
	}
	else
	{
    // Timers for detection lengths
		if (enemy->drawtype == ENEMY_ART)
		{
			enemy->detectiontimer = 27;
		}
		if (enemy->drawtype == POLICEMAN)
		{
			enemy->detectiontimer = 10;
		}
		
		enemy->timer5 = 0;
	}

  // Creates an array for the points that the enemy moves toward
	EnemyPoints Varray[ENEMY_VECT_LEN] = { v1, v2, v3, v4 };

  // Moves the enemies 
	MoveEnemies(enemy, ENEMY_VECT_LEN, Varray, SPEED);
}

//------------------------------------------------------------------------------
// function: MoveEnemies
// author:	Gabe Gramblicka
// 
// description:	this function moves enemies by looping the the array of vectors
//              (points) once it reaches the next point
//              
//------------------------------------------------------------------------------
void MoveEnemies(object* enemy, int count, EnemyPoints points[], float SPEED)
{
	CP_Vector myposition;
	CP_Vector destination;
	CP_Vector direction;

	destination = CP_Vector_Set(points[enemy->arrayStart].x, points[enemy->arrayStart].y);
	myposition  = CP_Vector_Set(enemy->x, enemy->y);

	direction = CP_Vector_Subtract(destination, myposition);
	direction = CP_Vector_Normalize(direction);

	direction = CP_Vector_Scale(direction, (float)fabs(enemy->speed) * fast_forward());

	//move enemy towards point
	MoveObject(direction.x, direction.y, enemy);

	CP_Vector_Normalize(direction);

	enemy->dirX = direction.x;
	enemy->dirY = direction.y;

	float Pointdistance = CP_Vector_Distance(myposition, destination);

  // loop into the next point
	if (Pointdistance <= (8))
	{
		enemy->arrayStart++;
	}
	if (enemy->arrayStart == count)
	{
		enemy->arrayStart = 0;
	}
}