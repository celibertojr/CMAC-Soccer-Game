// IMPORTANTISSIMO
// PARA COMPILAR USE
// g++ -lm -lcurses Littman.cpp -o Littman.exe



#include "Simulator.h"
#include "tiles.h"


Simulator::Simulator()
{
	int i, j;


	// Initialize random seed;
	srandom(time(NULL)); // seed random number generator from internal clock
}

void Simulator::printGrid(void)
{
	int i, j;

	// printf("50\E[H\E[J");
	printf("\nTeams:\n");
	for (j = 0; j < FIELD_HEIGHT; j++)
	{
		for (i = 0; i < FIELD_WIDTH; i++)
		{
			if (grid[i][j] == -1) printf("X");
			 else if (grid[i][j] == 0) printf("0");
			  else printf("1");
		}
		printf("\n");
	}

	printf("\nPlayers:\n");
	for (j = 0; j < FIELD_HEIGHT; j++)
	{
		for (i = 0; i < FIELD_WIDTH; i++)
		{
		  printf("%d",gridP[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	getchar();
}

void Simulator::executeAction(int team, int player, Action action, State * currentState, State * nextState)
{
	// computing the next state for one defined action.
	// IMPORTANT: as the next state is alredy the same as thecurrent state, we only have to compute actions that change states.
	// ALL actions that does not result in a state change are ignored here, for example,
	// stand, or move when there is a wall in front of the player.

	// if action is stand, next state = this state. As they are already the same, this action stand does nothing


	switch (action)
	{
		case N:
		// printf("Action N\n");
		if(currentState->Pos[team][player].line < FIELD_HEIGHT - 1)
		  	if(grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line+1] == -1)  // free space
		  	{
			  	nextState->Pos[team][player].line = currentState->Pos[team][player].line + 1;

				grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line+1] =
				grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line];
				gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line+1] =
				gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line];

				grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line] = -1;
				gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line] = -1;
		  	}
		  	else
		  	{
		  	// lost the ball possession, or ball passed to other team member.
		  		if (
		  			grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line+1] !=
					grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line]
					)
					// lost the ball to other team
					{
						nextState->TeamwithBall = grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line+1];
						nextState->PlayerwithBall = gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line+1];
					}
				else
					{
						// pass among players of the same team
						nextState->PlayerwithBall = gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line+1];
					}
		  	}
		break;

		case S:
		// printf("Action S\n");
		if(currentState->Pos[team][player].line > 0 )
		  if(grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line-1] == -1)
		  	{
			  	nextState->Pos[team][player].line = currentState->Pos[team][player].line - 1;

				grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line-1] =
				grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line];
				gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line-1] =
				gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line];

				grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line] = -1;
				gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line] = -1;
		  	}
		  	else
		  	{
		  	// lost the ball possession, or ball passed to other team member.
		  		if (
		  			grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line-1] !=
					grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line]
					)
					// lost the ball to other team
					{
						nextState->TeamwithBall = grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line-1];
						nextState->PlayerwithBall = gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line-1];
					}
				else
					{
						// pass among players of the same team
						nextState->PlayerwithBall = gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line-1];
					}
		  	}

		break;

		case E:
		 //printf("Action E\n");
		if(currentState->Pos[team][player].col < FIELD_WIDTH -1)
		//{
			if(grid[currentState->Pos[team][player].col+1][currentState->Pos[team][player].line] == -1)
		 	{
				nextState->Pos[team][player].col = currentState->Pos[team][player].col + 1;

				grid[currentState->Pos[team][player].col+1][currentState->Pos[team][player].line] =
				grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line];
				gridP[currentState->Pos[team][player].col+1][currentState->Pos[team][player].line] =
				gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line];

				grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line] = -1;
				gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line] = -1;
		  	}
			else
		  	{
		  	// lost the ball possession, or ball passed to other team member.
		  		if (
		  			grid[currentState->Pos[team][player].col+1][currentState->Pos[team][player].line] !=
					grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line]
					)
					// lost the ball to other team
					{
						nextState->TeamwithBall = grid[currentState->Pos[team][player].col+1][currentState->Pos[team][player].line];
						nextState->PlayerwithBall = gridP[currentState->Pos[team][player].col+1][currentState->Pos[team][player].line];
					}
				else
					{
						// pass among players of the same team
						nextState->PlayerwithBall = gridP[currentState->Pos[team][player].col+1][currentState->Pos[team][player].line];
					}
		  	}
		//}
		else
		// in case of a goal by team zero (only team zero can make goal in the east side :-) ):
		if(
		    team == 0 && currentState->Pos[team][player].col == FIELD_WIDTH -1  			// team zero attacking
		    &&
		    team == currentState->TeamwithBall && player == currentState->PlayerwithBall // this player have the ball
		    &&
		    (currentState->Pos[team][player].line == (FIELD_HEIGHT /2) 		||
		     currentState->Pos[team][player].line == ((FIELD_HEIGHT /2) -1)	//||
		     //currentState->Pos[team][player].line == ((FIELD_HEIGHT /2) +1)	||
		     //currentState->Pos[team][player].line == ((FIELD_HEIGHT /2) -2)
			 //*** AQUI *** - AQUI QUE DEFINE O TAMANHO DO GOAL. AGORA ESTA SO COM 2 LINHAS

		    )				// it is in front of the goal
		  )
			isGoal = 1;

		break;

		case W:
		// printf("Action W\n");
		if(currentState->Pos[team][player].col > 0 )
		//{
			if(grid[currentState->Pos[team][player].col-1][currentState->Pos[team][player].line] == -1)
		 	{
				nextState->Pos[team][player].col = currentState->Pos[team][player].col - 1;

				grid[currentState->Pos[team][player].col-1][currentState->Pos[team][player].line] =
				grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line];
				gridP[currentState->Pos[team][player].col-1][currentState->Pos[team][player].line] =
				gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line];

				grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line] = -1;
				gridP[currentState->Pos[team][player].col][currentState->Pos[team][player].line] = -1;
		  	}
			else
		  	{
		  	// lost the ball possession, or ball passed to other team member.
		  		if (
		  			grid[currentState->Pos[team][player].col-1][currentState->Pos[team][player].line] !=
					grid[currentState->Pos[team][player].col][currentState->Pos[team][player].line]
					)
					// lost the ball to other team
					{
						nextState->TeamwithBall = grid[currentState->Pos[team][player].col-1][currentState->Pos[team][player].line];
						nextState->PlayerwithBall = gridP[currentState->Pos[team][player].col-1][currentState->Pos[team][player].line];
					}
				else
					{
						// pass among players of the same team
						nextState->PlayerwithBall = gridP[currentState->Pos[team][player].col-1][currentState->Pos[team][player].line];
					}
		  	}
		//}
		else
		// in case of a goal by team one (only team one can make goal in the west side :-) ):
		if(
		    team == 1 && currentState->Pos[team][player].col == 0			// team one attacking
		    &&
		    team == currentState->TeamwithBall && player == currentState->PlayerwithBall // this player have the ball
		    &&
		    (currentState->Pos[team][player].line == (FIELD_HEIGHT /2) 		||
		     currentState->Pos[team][player].line == ((FIELD_HEIGHT /2) -1)	// ||
		     //currentState->Pos[team][player].line == ((FIELD_HEIGHT /2) +1)	||
		     //currentState->Pos[team][player].line == ((FIELD_HEIGHT /2) -2)

			 //*** AQUI *** - AQUI QUE DEFINE O TAMANHO DO GOAL. AGORA ESTA SO COM 2 LINHAS
		    )				// it is in front of the goal
		  )
			isGoal = 1;

			//nextState->Pos[team][player].col = currentState->Pos[team][player].col - 1;


		break;

		//case P:
		// printf("Action P\n");
		//break;
	}





}


float Simulator::computeReward(int team, int player, Action action, State * currentState, State * nextState)
{

	// If a goal is made
	if (isGoal)
	{
			return (REWARD_GOAL_MADE);

	}

	// if a player lost the ball to the other team
	else
	if (nextState->TeamwithBall != currentState->TeamwithBall)
		return (REWARD_LOST_BALL);

	// if a pass was well done
	else
	if (nextState->TeamwithBall == currentState->TeamwithBall
		&&
		nextState->PlayerwithBall != currentState->PlayerwithBall
		)
		return(REWARD_PASS_OK);

	// if anything else happens, return zero.
	else
		return(0);






}

void Simulator::execute_simulation(Team * A, Team * B)
{
	int i, j, player;

	FILE * evoltA;
	char fname[20];

	// define current and next state.
	State * currentState, * nextState;

	currentState = new State();
	nextState = new State();

	// define the reward vector, a floar teward for each player of the team.
	float reward;

	// define the action vector, containing the actions to be taken by each player of the team.
	Action action;

	// define which side each team is.
	// A is always on the left side, B is always on the right side, doesn matter what A and B are.
	A->side = 0;
	B->side = 1;

	int goalsA, goalsB;
	// greatest loop: for all training sessions
	for (session = 0; session < TRAINING_SESSIONS; session++)
	{
		printf("Starting training session %d \n", session);
		system("date");

		// abre arquivo para salvar esta secao
		sprintf(fname, "database/evolution-tA-%d.txt", session);
		evoltA = fopen(fname, "w");

		if (evoltA == NULL)
		{
			printf("Impossivel abrir arquivo de evolucao do time A.\nBailing out!\n\n");
			exit(1);
		}

		//Here starts a training session
		evolgoalsA[session] = evolgoalsB[session] =
		evolgameswonA[session] = evolgameswonA[session] = 0;
		ALPHA = ALPHA_INIT;

		for (player = 0; player < NUM_PLAYERS; player++)
		{
			// to initializa q table before starting a session
			A->Players[player]->resetPlayer();
			B->Players[player]->resetPlayer();
		}

		// LOOP for one training session, composed of several games
		for (game = 0; game < NUM_GAMES; game++)
		{
			// Here a game starts.
			goalsA = goalsB = 0;

			if (VERBOSE) printf("Starting game session %d, game %d.\n ", session, game);

			// loop for the number of trials in the game
			for (trial = 0; trial < NUM_TRIALS_IN_GAME; trial++)
			{
				//if (VERBOSE) printf("Starting training session %d, game %d, trial %d - \n", session, game, trial);
				step = 0;

				// clear grid - used to know if there is an obstacle (other robot).
				for (i = 0; i < FIELD_WIDTH; i++)
					for (j = 0; j < FIELD_HEIGHT; j++)
					{
						grid[i][j] = -1;
						gridP[i][j] = -1;
					}
				// reposiciona todos os jogadores e a bola...
				// reposition players and ball, each on its side of the field.
				// this is an static positioning of agents in the same place...
				for (player = 0; player < NUM_PLAYERS; player++)
				{
					currentState->Pos[0][player].line = FIELD_HEIGHT/2;
					currentState->Pos[0][player].col = player;
					currentState->Pos[1][player].line = FIELD_HEIGHT/2;
					currentState->Pos[1][player].col = FIELD_WIDTH - 1 - player;

					grid[player][FIELD_HEIGHT/2] = 0;
					gridP[player][FIELD_HEIGHT/2] = player;

					grid[FIELD_WIDTH - 1 - player][FIELD_HEIGHT/2] = 1;
					gridP[FIELD_WIDTH - 1 - player][FIELD_HEIGHT/2] = player;

				}
				currentState->TeamwithBall = random() % 2;
				currentState->PlayerwithBall = (random() % NUM_PLAYERS);
				// printf("Initial ball possession: %d %d\n", currentState->TeamwithBall,currentState->PlayerwithBall);

				// reset the isGoal flag
				isGoal = 0;


				// copy current state to next state, or else update state will not work
				memcpy(nextState,currentState, sizeof (State));


				// reposiciona a bola e da ela para um dos times, aleatoreamente.
				// Sorteia time e qual agente do time para dar a bola.

				// Starts the RL LOOP!
				do
				{
					// For the N players, do the RL loop (select, execute, reward).
					// alternate plays: each team play one move, then the other.
					// alwais in the same player order. This can be changed to a random order, but is not worth now.

					for (player = 0; player < NUM_PLAYERS; player++)
					{

						// Select A teams actions.
						action = A->Players[player]->selectAction(currentState);

						// Execute A team actions, execute action, changing the agents states.
						executeAction(0, player, action, currentState, nextState);
						///printf("OK", session, game);
						// compute the reward.
						reward = computeReward(0, player, action, currentState, nextState);

						// Reward A team
						A->Players[player]->receiveReward(action, reward, currentState, nextState);

						// copy new state to current state
						memcpy(currentState,nextState, sizeof (State));

						// if is goal finishes the loop.
						if (isGoal)
						{
							goalsA++;

							break;
						}



						// prints the grid
						//if (VERBOSE)
						//   printGrid();

						// Select B teams actions.
						action = B->Players[player]->selectAction(currentState);

						// Execute action.
						executeAction(1, player, action, currentState, nextState);

						// compute the reward.
						reward = computeReward(1, player, action, currentState, nextState);

						// Reward  player of the team
						B->Players[player]->receiveReward(action, reward, currentState, nextState);

						// copy new state to current state
						memcpy(currentState,nextState, sizeof (State));

						// if is goal finishes the loop.
						if (isGoal)
						{
							goalsB++;

							//  *** aqui - dar reforco negativo pro goleiro que deixou fazer goal

							break;
						}



						// prints the grid
						//if (VERBOSE)
						//   printGrid();


						// adds one to number of steps each team had done.
						step++;

						// DECAIMENTO DE ALPHA AQUI.
						ALPHA = ALPHA * ALPHA_DECAY;

					}  // end players loop.
				} while (step < MAX_STEPS_IN_TRIAL && !isGoal); // end of one trial in a game, if max steps is reached or a goal is made.



				// if a goal was scored
				if (isGoal)
				{
					if (VERBOSE) printf("Goal in %d steps. \n", step);

				}
				else
				   if (VERBOSE) printf("No Goal in %d steps. \n", step);



			} // end of trials loop - each iteraction ends one game

		// HERE a game has ended.

		// record the number of goals made by each team
		evolgoalsA[session] += goalsA;
		evolgoalsB[session] += goalsB;

		// Record de goals diference to be able to compute the goal evolution.
		record_evolution(session, game, goalsA-goalsB);

		// Print the evolution to have all data in files
		fprintf(evoltA, "%d %d %d %d\n", game, goalsA-goalsB, goalsA, goalsB);
		fflush(evoltA);

		// compute who whon the game
		// record the numer of games won by each team
		if( goalsA>goalsB)
			evolgameswonA[session]++;
		else if( goalsA<goalsB)
			evolgameswonB[session]++;
			else
			evolDraws[session]++;




		} // end of games loop


		// ***aqui
		// aqui escreve o arquivo deste jogo.
		fclose (evoltA);


	} // end Training sessions loop



}


// FUNCOES PARA CALCULAR MEDIA DAS EXECUCOES ETC.

void Simulator::record_evolution(int t, int g, int goals)
{
     evol_data[t][g] = goals;
}


void Simulator::write_evol_data(void)
{

  FILE *run;
  int j, trial;

  int t;
  double sum, media, desvio_quad;

  // Prints the average
  {
    run = fopen("evolution.txt", "w");

    for (j=0;j< NUM_GAMES;j++)
      {
	// Calcula a soma para imprimir a media
	sum = 0;
	for (trial=0; trial<TRAINING_SESSIONS; trial++)
	  sum += evol_data[trial][j];
	media = sum/(double)TRAINING_SESSIONS;
	// Calcula o desvio PG 16 DO OTAVIANO HELENE,eh o sigma ^ 2)

	desvio_quad = 0;
	for (t = 0; t < TRAINING_SESSIONS; t++)
	  desvio_quad += pow((evol_data[t][j] - media), 2);

	desvio_quad = desvio_quad / (double) (TRAINING_SESSIONS );

	// Imprime media e desvio

	fprintf(run,"%d %f %f \n", j, media , sqrt(desvio_quad)) ;

      }
    fclose(run);
  }
}




void Simulator::print_final_results(void)
{
	int t;

	int somagolsA=0, somagolsB=0, somaganhasA=0, somaganhasB = 0,somaEmpates  = 0;
	float mediagolsA, mediagolsB, mediaganhasA, mediaganhasB, mediaEmpates ;

	float desviogolsA=0, desviogolsB=0, desvioganhasA=0, desvioganhasB = 0, desvioEmpates=0;


	printf("\n\nResultado Final de %d trials.\n", TRAINING_SESSIONS);


	// Calcula a soma e a media para imprimir a media

	for (t=0; t<TRAINING_SESSIONS; t++)
		somagolsA += evolgoalsA[t];
	mediagolsA = somagolsA/(double)TRAINING_SESSIONS;

	for (t=0; t<TRAINING_SESSIONS; t++)
		somagolsB += evolgoalsB[t];
	mediagolsB = somagolsB/(double)TRAINING_SESSIONS;

	for (t=0; t<TRAINING_SESSIONS; t++)
		somaganhasA += evolgameswonA[t];
	mediaganhasA = somaganhasA/(double)TRAINING_SESSIONS;

	for (t=0; t<TRAINING_SESSIONS; t++)
		somaganhasB += evolgameswonB[t];
	mediaganhasB = somaganhasB/(double)TRAINING_SESSIONS;

	for (t=0; t<TRAINING_SESSIONS; t++)
		somaEmpates += evolDraws[t];
	mediaEmpates = somaEmpates/(double)TRAINING_SESSIONS;

	// Calcula o desvio PG 16 DO OTAVIANO HELENE,eh o sigma ^ 2)


	for (t = 0; t < TRAINING_SESSIONS; t++)
		desviogolsA += pow((evolgoalsA[t] - mediagolsA), 2);
	desviogolsA = sqrt(desviogolsA / (double) (TRAINING_SESSIONS));

	for (t = 0; t < TRAINING_SESSIONS; t++)
		desviogolsB += pow((evolgoalsB[t] - mediagolsB), 2);
	desviogolsB = sqrt(desviogolsB / (double) (TRAINING_SESSIONS));

	for (t = 0; t < TRAINING_SESSIONS; t++)
		desvioganhasA += pow((evolgameswonA[t] - mediaganhasA), 2);
	desvioganhasA = sqrt(desvioganhasA / (double) (TRAINING_SESSIONS));

	for (t = 0; t < TRAINING_SESSIONS; t++)
		desvioganhasB += pow((evolgameswonB[t] - mediaganhasB), 2);
	desvioganhasB = sqrt(desvioganhasB / (double) (TRAINING_SESSIONS));

	for (t = 0; t < TRAINING_SESSIONS; t++)
		desvioEmpates += pow((evolDraws[t] - mediaEmpates), 2);
	desvioEmpates = sqrt(desvioEmpates / (double) (TRAINING_SESSIONS));

	printf("Total de gols Time A: %d\n", somagolsA);
	printf("Total de gols Time B: %d\n", somagolsB);
	printf("Total de vitorias Time A: %d\n", somaganhasA);
	printf("Total de vitorias Time B: %d\n", somaganhasB);

	printf("Media de gols Time A: %f desvio %f\n", mediagolsA, desviogolsA);
	printf("Media de gols Time B: %f desvio %f\n", mediagolsB, desviogolsB);
	printf("Media de vitorias Time A: %f desvio %f\n", mediaganhasA, desvioganhasA);
	printf("Media de vitorias Time B: %f desvio %f\n", mediaganhasB, desvioganhasB);
	printf("Media de empates: %f desvio %f\n", mediaEmpates, desvioEmpates);
	printf("GOLS: (%d $\\pm$ %d) $\\times$ (%d $\\pm$ %d)\n", (int)mediagolsA, (int)desviogolsA, (int)mediagolsB, (int)desviogolsB);
	printf("Partidas: (%d $\\pm$ %d) $\\times$ (%d $\\pm$ %d)\n", (int)mediaganhasA, (int)desvioganhasA, (int)mediaganhasB, (int)desvioganhasB);



}



/*

TEAMS

*/

// Construtor da Classe Team
Team::Team()
{
	printf("Abstract Team constructed.\n");

}

Team::Team(int s)
{
	side = s;
	printf("Abstract Team with side %d constructed.\n", side);


}

// Desostrutor da Classe Team
Team::~Team()
{
	int player;

		printf("Team destructed.\n");

	for (player = 0; player < NUM_PLAYERS; player++)
	{
		delete Players[player];
	}

}


// Construtor da Classe Team
RandomTeam::RandomTeam(int side):Team(side)
{
	int player;

	printf("Random Team constructed.\n");

	for (player = 0; player < NUM_PLAYERS; player++)
	{
		Players[player] = new RandomPlayer();
	}

}

// Desostrutor da Classe Team
RandomTeam::~RandomTeam()
{
	int player;

		printf("Random Team destructed.\n");

	for (player = 0; player < NUM_PLAYERS; player++)
	{
		delete Players[player];
	}
}

// Construtor da Classe CMAC_ Team
CMAC_QTeam::CMAC_QTeam(int side):Team(side)
{
	int player;

	printf("CMAC Q-learning Team constructed.\n");

	// *** AQUI ***
	// Change here the type of player in the team!

	for (player = 0; player < NUM_PLAYERS; player++)
	{
		Players[player] = new CMAC_QPlayer(side, player);
	}

}

CMAC_QTeam::~CMAC_QTeam()
{
	int player;

	printf("Random Team destructed.\n");

	for (player = 0; player < NUM_PLAYERS; player++)
	{
		delete Players[player];
	}
}


/*

PLAYERS

*/




Player::Player()
{

}

Player::Player(int s, int p)
{
	side = s;
	playerID = p;
}

Action Player::selectAction(State * S)
{
	if (VERBOSE) printf("PLayer Action Selection\n");
	return((Action)0);
};

void Player::receiveReward(Action action, float Reward, State * currentState, State * nextState)
{
	if (VERBOSE) printf("Player Reward Received\n");

};

Action RandomPlayer::selectAction(State * S)
{
	int fave;

	fave = (random() % NUM_ACTION); // use random  to generate number

	//if (VERBOSE) printf("RandomPlayer Action Selection: %d\n", fave);

	return ((Action)fave);
};

void RandomPlayer::receiveReward(Action action, float reward, State * currentState, State * nextState)
{

};


//CMAC





CMAC_QPlayer::CMAC_QPlayer(int s, int p):Player(s,p)
{
	// Initializing the Q matrix

	printf("CMAC Q-Learning player %d %d Built\n", side, playerID);

}



void CMAC_QPlayer::resetPlayer(void)
{
	//int action, possession, pl, w1, w2, w3, w4, w5, w6, h1, h2, h3, h4, h5, h6;

    printf("resetting Q-table player %d %d.\n", side, playerID);

    for (int i=0; i<MEMORY_SIZE; i++) {
        weights[i]= 0.0;                     // clear weights
                             // clear all traces
    }
    epsilon = 0.5;
    alpha = 0.2;                      // step size parameter

    RLgamma = 0.9;                    // gamma parameter


	printf("DONE !!!\n", side, playerID);


}

Action CMAC_QPlayer::selectAction(State * S)
{
	Action action;


    //if (S->TeamwithBall == side && S->PlayerwithBall == playerID)

	if ( (random() % 100)/(float)100 > EXPLORATION_RATE)
    {
		action = amaxQ(S);
    }

	else action = (Action)(random() % NUM_ACTION);

	//if (VERBOSE) printf("QPlayer Action Selection: %d \n", (int) action);

	return (action);
};

Action CMAC_QPlayer::amaxQ(State * S)
{
	int action, maxAction = 0;




	int tocomabola;

	if (S->TeamwithBall == side && S->PlayerwithBall == playerID) tocomabola = 1;
	else tocomabola = 0;


    tmp_obs[0] = tocomabola;
    tmp_obs[1] = S->Pos[0][0].col;			// Position of the first player;
    tmp_obs[2] = S->Pos[0][0].line;           // Position of the first player
    tmp_obs[3] = S->Pos[0][1].col;            // Position of the second player
    tmp_obs[4] = S->Pos[0][1].line;           // Position of the second player
    tmp_obs[5] = S->Pos[0][2].col;             // Position of the third player
    tmp_obs[6] = S->Pos[0][2].line;            // Position of the third player
    tmp_obs[7] = S->Pos[0][3].col;             // Position of the third player
    tmp_obs[8] = S->Pos[0][3].line;            // Position of the third player
    tmp_obs[9] = S->Pos[1][0].col;             // Position of the first opponent playe
    tmp_obs[10] = S->Pos[1][0].line;           // Position of the first opponent playe
    tmp_obs[11] = S->Pos[1][1].col;            // Position of the second player
    tmp_obs[12] =S->Pos[1][1].line;           // Position of the second player
    tmp_obs[13] =S->Pos[1][2].col;           // Position of the third player
    tmp_obs[14] =S->Pos[1][2].line;          // Position of the third player
    tmp_obs[15] =S->Pos[1][3].col;           // Position of the third player
    tmp_obs[16] =S->Pos[1][3].line;          // Position of the third player


    computeActiveFeatures(tmp_obs);
    computeActionValues();

    action = selectEpsilonGreedyAction();

    maxAction = action;


    return ((Action) maxAction);

}



void CMAC_QPlayer::receiveReward(Action action, float reward, State * currentState, State * nextState)
{

    int tocomabola;

	if (currentState->TeamwithBall == side && currentState->PlayerwithBall == playerID) tocomabola = 1;
	else tocomabola = 0;


    float maximQ;

    maximQ = amaxQ(currentState);

    double delta = reward - maximQ;

    maximQ = amaxQ(nextState);


    delta += RLgamma * maximQ;


    updateWeights(delta, currentState,tocomabola,action);









};

void CMAC_QPlayer::updateWeights(double delta, State * S, int bola, Action action)
{


	double temp = (alpha/NUM_TILINGS)*delta;



    tmp_obs_TEMP[0] = bola;
    tmp_obs_TEMP[1] = S->Pos[0][0].col;			// Position of the first player;
    tmp_obs_TEMP[2] = S->Pos[0][0].line;           // Position of the first player
    tmp_obs_TEMP[3] = S->Pos[0][1].col;            // Position of the second player
    tmp_obs_TEMP[4] = S->Pos[0][1].line;           // Position of the second player
    tmp_obs_TEMP[5] = S->Pos[0][2].col;             // Position of the third player
    tmp_obs_TEMP[6] = S->Pos[0][2].line;            // Position of the third player
    tmp_obs_TEMP[7] = S->Pos[0][3].col;             // Position of the third player
    tmp_obs_TEMP[8] = S->Pos[0][3].line;
    tmp_obs_TEMP[9] = S->Pos[1][0].col;             // Position of the first opponent playe
    tmp_obs_TEMP[10] =S->Pos[1][0].line;           // Position of the first opponent playe
    tmp_obs_TEMP[11] =S->Pos[1][1].col;            // Position of the second player
    tmp_obs_TEMP[12] =S->Pos[1][1].line;           // Position of the second player
    tmp_obs_TEMP[13] =S->Pos[1][2].col;           // Position of the third player
    tmp_obs_TEMP[14] =S->Pos[1][2].line;          // Position of the third player
    tmp_obs_TEMP[15] =S->Pos[1][3].col;           // Position of the third player
    tmp_obs_TEMP[16] =S->Pos[1][3].line;          // Position of the third player


	computeActiveFeatures(tmp_obs_TEMP);



	for (int j=0; j<NUM_TILINGS; j++)
    {
		weights[activeFeatures[action][j]]+=temp;
    }
}




void CMAC_QPlayer::computeActiveFeatures(double o[])
{
	// get set of active features for current observation. One for each action

    float inputObservations[NUM_OBSERVATIONS];
    inputObservations[0] = o[0]/ 8;
    inputObservations[1] = o[1]/ CMAC_FIELD_HEIGHT;
    inputObservations[2] = o[2]/ CMAC_FIELD_WIDTH;
    inputObservations[3] = o[3]/ CMAC_FIELD_HEIGHT;
    inputObservations[4] = o[4]/ CMAC_FIELD_WIDTH;
    inputObservations[5] = o[5]/ CMAC_FIELD_HEIGHT;
    inputObservations[6] = o[6]/ CMAC_FIELD_WIDTH;
    inputObservations[7] = o[7]/ CMAC_FIELD_HEIGHT;
    inputObservations[8] = o[8]/ CMAC_FIELD_WIDTH;
    inputObservations[9] = o[9]/ CMAC_FIELD_HEIGHT;
    inputObservations[10] = o[10]/ CMAC_FIELD_WIDTH;
    inputObservations[11] = o[11]/ CMAC_FIELD_HEIGHT;
    inputObservations[12] = o[12]/ CMAC_FIELD_WIDTH;
    inputObservations[13] = o[13]/ CMAC_FIELD_HEIGHT;
    inputObservations[14] = o[14]/ CMAC_FIELD_WIDTH;
    inputObservations[15] = o[15]/ CMAC_FIELD_HEIGHT;
    inputObservations[16] = o[16]/ CMAC_FIELD_WIDTH;



    for (int a=0; a<NUM_ACTIONS; a++)
    {
      tiles(&activeFeatures[a][0],NUM_TILINGS,MEMORY_SIZE, inputObservations,NUM_OBSERVATIONS,a);
    }
}



void CMAC_QPlayer::computeActionValues()
{
	// Compute all the action values from current activeFeatures and weights

	for (int a=0; a<NUM_ACTIONS; a++)
	{
		QSA[a] = 0;
		for (int j=0; j<NUM_TILINGS; j++)
			QSA[a] += weights[activeFeatures[a][j]];
	}
}

void CMAC_QPlayer::computeActionValues(int a)
{
	// Compute a particular action value from current activeFeatures and weights

	QSA[a] = 0;
    for (int j=0; j<NUM_TILINGS; j++)
		QSA[a] += weights[activeFeatures[a][j]];
}

int CMAC_QPlayer::selectEpsilonGreedyAction()
{
    double v;

    int ac = argmax(QSA,NUM_ACTIONS,v);
    lastQValue = QSA[ac];

    return ac;
}

int CMAC_QPlayer::argmax(double QSA[],int size,double &bestvalue)
{
	// Returns index (action) of largest entry in QSA array, breaking ties randomly

    int best_action = 0;

    double best_value = QSA[0];



    int num_ties = 1;                    // actually the number of ties plus 1
    double value;

	for (int a=1; a<size; a++)
	{
		value = QSA[a];
		if (value >= best_value)
			if (value > best_value)
			{
				best_value = value;
				best_action = a;
			}
			else
			{
				num_ties++;
				if (0 == (int)(rand()*num_ties))
				{
					best_value = value;
					best_action = a;
				}
			}
	}
    return best_action;
}








//fim do cmaC

//*******************************************************************************************************





int main(void) {


	// Creating the simulator object
	Simulator * S = new Simulator();

	// Creating the teams. To change teams, change here.

	// team A is always team zero, and team b is always "1".

	//Team * A = new RandomTeam(0);
	Team * A = new CMAC_QTeam(0);


	Team * B = new RandomTeam(1);
	//Team * B = new QTeam(1);

	S->execute_simulation(A,B);

	//Escreve a evolucao.
	S->write_evol_data();
	S->print_final_results();


	// deleting teams and simulator objects
	delete A;
	delete B;
	delete S;


	printf("\nTerminado\n");
}


/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//  CMAC ////
// ESTAS FUNCOES VIERAM DO TILES.C E FORAM COLOCAR AQUI DEVIDO A UM PROBLEMA COM O MAC //////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 External documentation and recommendations on the use of this code is
 available at http://www.cs.umass.edu/~rich/tiles.html.

 This is an implementation of grid-style tile codings, based originally on
 the UNH CMAC code (see http://www.ece.unh.edu/robots/cmac.htm).
 Here we provide a procedure, "GetTiles", that maps floating-point and integer
 variables to a list of tiles. This function is memoryless and requires no
 setup. We assume that hashing colisions are to be ignored. There may be
 duplicates in the list of tiles, but this is unlikely if memory-size is
 large.

 The floating-point input variables will be gridded at unit intervals, so generalization
 will be by 1 in each direction, and any scaling will have
 to be done externally before calling tiles.  There is no generalization
 across integer values.

 It is recommended by the UNH folks that num-tilings be a power of 2, e.g., 16.

 We assume the existence of a function "rand()" that produces successive
 random integers, of which we use only the low-order bytes.
 */



void tiles(
		   int the_tiles[],               // provided array contains returned tiles (tile indices)
		   int num_tilings,           // number of tile indices to be returned in tiles
		   int memory_size,           // total number of possible tiles
		   float floats[],            // array of floating point variables
		   int num_floats,            // number of floating point variables
		   int ints[],				   // array of integer variables
		   int num_ints)              // number of integer variables
{
	int i,j;
	int qstate[MAX_NUM_VARS];
	int base[MAX_NUM_VARS];
	int coordinates[MAX_NUM_VARS * 2 + 1];   /* one interval number per relevant dimension */
	int num_coordinates = num_floats + num_ints + 1;

	for (int i=0; i<num_ints; i++) coordinates[num_floats+1+i] = ints[i];

	/* quantize state to integers (henceforth, tile widths == num_tilings) */
    for (i = 0; i < num_floats; i++) {
    	qstate[i] = (int) floor(floats[i] * num_tilings);
    	base[i] = 0;
    }

    /*compute the tile numbers */
    for (j = 0; j < num_tilings; j++) {

		/* loop over each relevant dimension */
		for (i = 0; i < num_floats; i++) {

    		/* find coordinates of activated tile in tiling space */
			if (qstate[i] >= base[i])
				coordinates[i] = qstate[i] - ((qstate[i] - base[i]) % num_tilings);
			else
				coordinates[i] = qstate[i]+1 + ((base[i] - qstate[i] - 1) % num_tilings) - num_tilings;

			/* compute displacement of next tiling in quantized space */
			base[i] += 1 + (2 * i);
		}
		/* add additional indices for tiling and hashing_set so they hash differently */
		coordinates[i] = j;

		the_tiles[j] = hash_UNH(coordinates, num_coordinates, memory_size, 449);
	}
	return;
}


void tiles(
		   int the_tiles[],               // provided array contains returned tiles (tile indices)
		   int num_tilings,           // number of tile indices to be returned in tiles
		   collision_table *ctable,    // total number of possible tiles
		   float floats[],            // array of floating point variables
		   int num_floats,            // number of floating point variables
		   int ints[],				   // array of integer variables
		   int num_ints)              // number of integer variables
{
	int i,j;
	int qstate[MAX_NUM_VARS];
	int base[MAX_NUM_VARS];
	int coordinates[MAX_NUM_VARS * 2 + 1];   /* one interval number per relevant dimension */
	int num_coordinates = num_floats + num_ints + 1;

	for (int i=0; i<num_ints; i++) coordinates[num_floats+1+i] = ints[i];

	/* quantize state to integers (henceforth, tile widths == num_tilings) */
    for (i = 0; i < num_floats; i++) {
    	qstate[i] = (int) floor(floats[i] * num_tilings);
    	base[i] = 0;
    }

    /*compute the tile numbers */
    for (j = 0; j < num_tilings; j++) {

		/* loop over each relevant dimension */
		for (i = 0; i < num_floats; i++) {

    		/* find coordinates of activated tile in tiling space */
			if (qstate[i] >= base[i])
				coordinates[i] = qstate[i] - ((qstate[i] - base[i]) % num_tilings);
			else
				coordinates[i] = qstate[i]+1 + ((base[i] - qstate[i] - 1) % num_tilings) - num_tilings;

			/* compute displacement of next tiling in quantized space */
			base[i] += 1 + (2 * i);
		}
		/* add additional indices for tiling and hashing_set so they hash differently */
		coordinates[i] = j;

		the_tiles[j] = hash(coordinates, num_coordinates, ctable);
	}
	return;
}


/* hash_UNH
 Takes an array of integers and returns the corresponding tile after hashing
 */


int hash_UNH(int *ints, int num_ints, long m, int increment)
{
	static unsigned int rndseq[2048];
	static int first_call =  1;
	int i,k;
	long index;
	long sum = 0;

	/* if first call to hashing, initialize table of random numbers */
    if (first_call) {
		for (k = 0; k < 2048; k++) {
			rndseq[k] = 0;
			for (i=0; i < int(sizeof(int)); ++i)
	    		rndseq[k] = (rndseq[k] << 8) | (rand() & 0xff);
		}
		first_call = 0;
    }

	for (i = 0; i < num_ints; i++) {
		/* add random table offset for this dimension and wrap around */
		index = ints[i];
		index += (increment * i);
		/* index %= 2048; */
		index = index & 2047;
		while (index < 0) index += 2048;

		/* add selected random number to sum */
		sum += (long)rndseq[(int)index];
	}
	index = (int)(sum % m);
	while (index < 0) index += m;

	/* printf("index is %d \n", index); */

	return(index);
}


//int hash(int *ints, int num_ints, collision_table *ct);

/* hash
 Takes an array of integers and returns the corresponding tile after hashing
 */
int hash(int *ints, int num_ints, collision_table *ct)
{
	int j;
	long ccheck;

	ct->calls++;
	j = hash_UNH(ints, num_ints, ct->m, 449);
	ccheck = hash_UNH(ints, num_ints, MaxLONGINT, 457);
	if (ccheck == ct->data[j])
	    ct->clearhits++;
	else if (ct->data[j] == -1) {
		ct->clearhits++;
	    ct->data[j] = ccheck; }
	else if (ct->safe == 0)
		ct->collisions++;
	else {
		long h2 = 1 + 2 * hash_UNH(ints,num_ints,(MaxLONGINT)/4,449);
		int i = 0;
		while (++i) {
			ct->collisions++;
			j = (j+h2) % (ct->m);
			/*printf("collision (%d) \n",j);*/
			if (i > ct->m) {printf("\nTiles: Collision table out of Memory"); exit(0);}
			if (ccheck == ct->data[j]) break;
			if (ct->data[j] == -1) {ct->data[j] = ccheck; break;}
		}
	}
	return j;
}

void collision_table::reset() {
    for (int i=0; i<m; i++) data[i] = -1;
    calls = 0;
    clearhits = 0;
    collisions = 0;
}

collision_table::collision_table(int size, int safety) {
	int tmp = size;
	while (tmp > 2){
		if (tmp % 2 != 0) {
			printf("\nSize of collision table must be power of 2 %d",size);
			exit(0);
		}
		tmp /= 2;
	}
	data = new long[size];
	m = size;
	safe = safety;
	reset();
}

collision_table::~collision_table() {
	delete[] data;
}

int collision_table::usage() {
	int count = 0;
	for (int i=0; i<m; i++) if (data[i] != -1)
	{

		count++;
    }

	return count;
}

void collision_table::print() {
    printf("Collision table: Safety : %d Usage : %d Size : %ld Calls : %ld Collisions : %ld\n",this->safe,this->usage(),this->m,this->calls,this->collisions);
}

void collision_table::save(int file) {
	write(file, (char *) &m, sizeof(long));
	write(file, (char *) &safe, sizeof(int));
	write(file, (char *) &calls, sizeof(long));
	write(file, (char *) &clearhits, sizeof(long));
	write(file, (char *) &collisions, sizeof(long));
	write(file, (char *) data, m*sizeof(long));
}

void collision_table::restore(int file) {
	read(file, (char *) &m, sizeof(long));
	read(file, (char *) &safe, sizeof(int));
	read(file, (char *) &calls, sizeof(long));
	read(file, (char *) &clearhits, sizeof(long));
	read(file, (char *) &collisions, sizeof(long));
	read(file, (char *) data, m*sizeof(long));
}

/*
 void collision_table::save(char *filename) {
 write(open(filename, O_BINARY | O_CREAT | O_WRONLY);
 };

 void collision_table::restore(char *filename) {
 read(open(filename, O_BINARY | O_CREAT | O_WRONLY);
 }
 */


int i_tmp_arr[MAX_NUM_VARS];
float f_tmp_arr[MAX_NUM_VARS];

// No ints
void tiles(int the_tiles[],int nt,int memory,float floats[],int nf) {
    tiles(the_tiles,nt,memory,floats,nf,i_tmp_arr,0);
}
void tiles(int the_tiles[],int nt,collision_table *ct,float floats[],int nf) {
    tiles(the_tiles,nt,ct,floats,nf,i_tmp_arr,0);
}

//one int
void tiles(int the_tiles[],int nt,int memory,float floats[],int nf,int h1) {
    i_tmp_arr[0]=h1;
    tiles(the_tiles,nt,memory,floats,nf,i_tmp_arr,1);
}
void tiles(int the_tiles[],int nt,collision_table *ct,float floats[],int nf,int h1) {
    i_tmp_arr[0]=h1;
    tiles(the_tiles,nt,ct,floats,nf,i_tmp_arr,1);
}

// two ints
void tiles(int the_tiles[],int nt,int memory,float floats[],int nf,int h1,int h2) {
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    tiles(the_tiles,nt,memory,floats,nf,i_tmp_arr,2);
}
void tiles(int the_tiles[],int nt,collision_table *ct,float floats[],int nf,int h1,int h2) {
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    tiles(the_tiles,nt,ct,floats,nf,i_tmp_arr,2);
}

// three ints
void tiles(int the_tiles[],int nt,int memory,float floats[],int nf,int h1,int h2,int h3) {
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    i_tmp_arr[2]=h3;
    tiles(the_tiles,nt,memory,floats,nf,i_tmp_arr,3);
}
void tiles(int the_tiles[],int nt,collision_table *ct,float floats[],int nf,int h1,int h2,int h3) {
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    i_tmp_arr[2]=h3;
    tiles(the_tiles,nt,ct,floats,nf,i_tmp_arr,3);
}

// one float, No ints
void tiles1(int the_tiles[],int nt,int memory,float f1) {
    f_tmp_arr[0]=f1;
    tiles(the_tiles,nt,memory,f_tmp_arr,1,i_tmp_arr,0);
}
void tiles1(int the_tiles[],int nt,collision_table *ct,float f1) {
    f_tmp_arr[0]=f1;
    tiles(the_tiles,nt,ct,f_tmp_arr,1,i_tmp_arr,0);
}

// one float, one int
void tiles1(int the_tiles[],int nt,int memory,float f1,int h1) {
    f_tmp_arr[0]=f1;
    i_tmp_arr[0]=h1;
    tiles(the_tiles,nt,memory,f_tmp_arr,1,i_tmp_arr,1);
}
void tiles1(int the_tiles[],int nt,collision_table *ct,float f1,int h1) {
    f_tmp_arr[0]=f1;
    i_tmp_arr[0]=h1;
    tiles(the_tiles,nt,ct,f_tmp_arr,1,i_tmp_arr,1);
}

// one float, two ints
void tiles1(int the_tiles[],int nt,int memory,float f1,int h1,int h2) {
    f_tmp_arr[0]=f1;
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    tiles(the_tiles,nt,memory,f_tmp_arr,1,i_tmp_arr,2);
}
void tiles1(int the_tiles[],int nt,collision_table *ct,float f1,int h1,int h2) {
    f_tmp_arr[0]=f1;
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    tiles(the_tiles,nt,ct,f_tmp_arr,1,i_tmp_arr,2);
}

// one float, three ints
void tiles1(int the_tiles[],int nt,int memory,float f1,int h1,int h2,int h3) {
    f_tmp_arr[0]=f1;
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    i_tmp_arr[2]=h3;
    tiles(the_tiles,nt,memory,f_tmp_arr,1,i_tmp_arr,3);
}
void tiles1(int the_tiles[],int nt,collision_table *ct,float f1,int h1,int h2,int h3) {
    f_tmp_arr[0]=f1;
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    i_tmp_arr[2]=h3;
    tiles(the_tiles,nt,ct,f_tmp_arr,1,i_tmp_arr,3);
}

// two floats, No ints
void tiles2(int the_tiles[],int nt,int memory,float f1,float f2) {
    f_tmp_arr[0]=f1;
    f_tmp_arr[1]=f2;
    tiles(the_tiles,nt,memory,f_tmp_arr,2,i_tmp_arr,0);
}
void tiles2(int the_tiles[],int nt,collision_table *ct,float f1,float f2) {
    f_tmp_arr[0]=f1;
    f_tmp_arr[1]=f2;
    tiles(the_tiles,nt,ct,f_tmp_arr,2,i_tmp_arr,0);
}

// two floats, one int
void tiles2(int the_tiles[],int nt,int memory,float f1,float f2,int h1) {
    f_tmp_arr[0]=f1;
    f_tmp_arr[1]=f2;
    i_tmp_arr[0]=h1;
    tiles(the_tiles,nt,memory,f_tmp_arr,2,i_tmp_arr,1);
}
void tiles2(int the_tiles[],int nt,collision_table *ct,float f1,float f2,int h1) {
    f_tmp_arr[0]=f1;
    f_tmp_arr[1]=f2;
    i_tmp_arr[0]=h1;
    tiles(the_tiles,nt,ct,f_tmp_arr,2,i_tmp_arr,1);
}

// two floats, two ints
void tiles2(int the_tiles[],int nt,int memory,float f1,float f2,int h1,int h2) {
    f_tmp_arr[0]=f1;
    f_tmp_arr[1]=f2;
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    tiles(the_tiles,nt,memory,f_tmp_arr,2,i_tmp_arr,2);
}
void tiles2(int the_tiles[],int nt,collision_table *ct,float f1,float f2,int h1,int h2) {
    f_tmp_arr[0]=f1;
    f_tmp_arr[1]=f2;
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    tiles(the_tiles,nt,ct,f_tmp_arr,2,i_tmp_arr,2);
}

// two floats, three ints
void tiles2(int the_tiles[],int nt,int memory,float f1,float f2,int h1,int h2,int h3) {
    f_tmp_arr[0]=f1;
    f_tmp_arr[1]=f2;
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    i_tmp_arr[2]=h3;
    tiles(the_tiles,nt,memory,f_tmp_arr,2,i_tmp_arr,3);
}
void tiles2(int the_tiles[],int nt,collision_table *ct,float f1,float f2,int h1,int h2,int h3) {
    f_tmp_arr[0]=f1;
    f_tmp_arr[1]=f2;
    i_tmp_arr[0]=h1;
    i_tmp_arr[1]=h2;
    i_tmp_arr[2]=h3;
    tiles(the_tiles,nt,ct,f_tmp_arr,2,i_tmp_arr,3);
}

void tileswrap(
			   int the_tiles[],               // provided array contains returned tiles (tile indices)
			   int num_tilings,           // number of tile indices to be returned in tiles
			   int memory_size,           // total number of possible tiles
			   float floats[],            // array of floating point variables
			   int num_floats,            // number of floating point variables
			   int wrap_widths[],         // array of widths (length and units as in floats)
			   int ints[],				  // array of integer variables
			   int num_ints)             // number of integer variables
{
	int i,j;
	int qstate[MAX_NUM_VARS];
	int base[MAX_NUM_VARS];
    int wrap_widths_times_num_tilings[MAX_NUM_VARS];
	int coordinates[MAX_NUM_VARS * 2 + 1];   /* one interval number per relevant dimension */
	int num_coordinates = num_floats + num_ints + 1;

	for (int i=0; i<num_ints; i++) coordinates[num_floats+1+i] = ints[i];

	/* quantize state to integers (henceforth, tile widths == num_tilings) */
    for (i = 0; i < num_floats; i++) {
    	qstate[i] = (int) floor(floats[i] * num_tilings);
    	base[i] = 0;
    	wrap_widths_times_num_tilings[i] = wrap_widths[i] * num_tilings;
    }

    /*compute the tile numbers */
    for (j = 0; j < num_tilings; j++) {

		/* loop over each relevant dimension */
		for (i = 0; i < num_floats; i++) {

    		/* find coordinates of activated tile in tiling space */
			if (qstate[i] >= base[i])
				coordinates[i] = qstate[i] - ((qstate[i] - base[i]) % num_tilings);
			else
				coordinates[i] = qstate[i]+1 + ((base[i] - qstate[i] - 1) % num_tilings) - num_tilings;
			if (wrap_widths[i] != 0) coordinates[i] = coordinates[i] % wrap_widths_times_num_tilings[i];
			if (coordinates[i] < 0) {
				while (coordinates[i] < 0)
                    coordinates[i] += wrap_widths_times_num_tilings[i];
			}
			/* compute displacement of next tiling in quantized space */
			base[i] += 1 + (2 * i);
		}
		/* add additional indices for tiling and hashing_set so they hash differently */
		coordinates[i] = j;

		the_tiles[j] = hash_UNH(coordinates, num_coordinates, memory_size, 449);
	}
	return;
}

void tileswrap(
			   int the_tiles[],               // provided array contains returned tiles (tile indices)
			   int num_tilings,           // number of tile indices to be returned in tiles
			   collision_table *ctable,   // total number of possible tiles
			   float floats[],            // array of floating point variables
			   int num_floats,            // number of floating point variables
			   int wrap_widths[],         // array of widths (length and units as in floats)
			   int ints[],				  // array of integer variables
			   int num_ints)             // number of integer variables
{
	int i,j;
	int qstate[MAX_NUM_VARS];
	int base[MAX_NUM_VARS];
    int wrap_widths_times_num_tilings[MAX_NUM_VARS];
	int coordinates[MAX_NUM_VARS * 2 + 1];   /* one interval number per relevant dimension */
	int num_coordinates = num_floats + num_ints + 1;

	for (int i=0; i<num_ints; i++) coordinates[num_floats+1+i] = ints[i];

	/* quantize state to integers (henceforth, tile widths == num_tilings) */
    for (i = 0; i < num_floats; i++) {
    	qstate[i] = (int) floor(floats[i] * num_tilings);
    	base[i] = 0;
    	wrap_widths_times_num_tilings[i] = wrap_widths[i] * num_tilings;
    }

    /*compute the tile numbers */
    for (j = 0; j < num_tilings; j++) {

		/* loop over each relevant dimension */
		for (i = 0; i < num_floats; i++) {

    		/* find coordinates of activated tile in tiling space */
			if (qstate[i] >= base[i])
				coordinates[i] = qstate[i] - ((qstate[i] - base[i]) % num_tilings);
			else
				coordinates[i] = qstate[i]+1 + ((base[i] - qstate[i] - 1) % num_tilings) - num_tilings;

			if (wrap_widths[i] != 0) coordinates[i] = coordinates[i] % wrap_widths_times_num_tilings[i];
			if (coordinates[i] < 0) {
				while (coordinates[i] < 0)
                    coordinates[i] += wrap_widths_times_num_tilings[i];
			}
			/* compute displacement of next tiling in quantized space */
			base[i] += 1 + (2 * i);
		}
		/* add additional indices for tiling and hashing_set so they hash differently */
		coordinates[i] = j;

		the_tiles[j] = hash(coordinates, num_coordinates,ctable);
	}
	return;
}






///////////////////////////////////////////////////////////////////////////////////////////////

//FIM CMAC
//////////////////////////////////////////////
