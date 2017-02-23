// IMPORTANTISSIMO
// PARA COMPILAR USE
// g++

#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
#include <cmath>
//#include <string.h>
#include <ctime>

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
//#include <stdio.h>
#include <string.h>
double lastQValue = 0;
// Standard RL parameters:
double epsilon;                    // probability of random action
double alpha;                      // step size parameter
double RLgamma;                // discount-rate parameter
int tmp_action;
//double* tmp_obs;
double tmp_obs[13];
double* obs_AGENTE;
double tmp_obs_TEMP[13];

#define MEMORY_SIZE 102400                      //number of possible features
#define NUM_ACTIONS 5                          //number of available actions
#define  NUM_TILINGS 10                   //number of tiling grids
#define NUM_OBSERVATIONS 17                     //dimension of observation



#define VERBOSE 1   // define if will print all  debug information: 1 print, 0 dont print

#define MAX_STEPS_IN_TRIAL 100000		// Max steps in a trial

// Number of games and how many trials there are in each game.
#define NUM_GAMES 100
#define NUM_TRIALS_IN_GAME 20

// Numeber of training sessions
#define TRAINING_SESSIONS 30

#define ALPHA_INIT 0.95 // 1.0			// ALPHA initial
#define ALPHA_DECAY 1.0 // 0.99999954
float ALPHA = ALPHA_INIT;				// learning rate uso ou 0.95 ou 0.05 ou menos...

#define GAMMA 0.9				// discount factor
#define EXPLORATION_RATE 0.2	// exploration exploitation rate

#define H_USADO 10

#define MAXFLOAT 200000000

// Dimensions of the field. HIGHT must be an even number.
// minimum dimentions is WIDTH = 5, HEIGHT = 4


#define FIELD_WIDTH 10
#define FIELD_HEIGHT 10


#define CMAC_FIELD_WIDTH FIELD_WIDTH/8
#define CMAC_FIELD_HEIGHT FIELD_HEIGHT/8


#define NUM_PLAYERS 4			// number of players in each team

// Rewards:

#define REWARD_GOAL_MADE 1000
//#define REWARD_GOAL_SUFFERED 1000
#define REWARD_LOST_BALL 0
#define REWARD_PASS_OK 0

// Global RL variables:
double QSA[NUM_ACTIONS];                                                                // action values
double weights[MEMORY_SIZE];                                                  // feature weights
int activeFeatures[NUM_ACTIONS][NUM_TILINGS];           // sets of features, one set per action

//using namespace std;

#ifndef RAND_MAX
#  define RAND_MAX ((int) ((unsigned) ~0 >> 1))
#endif

// retirei acao P daqui, era a ultima
enum Action {stand, N, S, E, W, NUM_ACTION};



int grid[FIELD_WIDTH][FIELD_HEIGHT];				// pointer to the state grid

class Position {
public:
	int line;
	int col;
};



class State {
public:
	Position Pos[2][NUM_PLAYERS]; // position of the players.
	// first fiels is Team = 0 (left) or 1 (right), second field is players 0 .. NUM_PLAYERS

	int TeamwithBall, PlayerwithBall;		// possession of the ball.
	// Team = 0 (left) or 1 (right), Players 0 ... NUM_PLAYERS.
};



/*

PLAYERS

*/

class Player {
public:
	int playerID;
	int side;

	Player();
	Player(int s, int p);		// construtor

	// methods for RL
	virtual Action selectAction(State * S);
	virtual void receiveReward(Action action, float reward, State * currentState, State * nextState);
	virtual void resetPlayer(void){};
};

class RandomPlayer : public Player {
public:
	Action selectAction(State * S);
	void receiveReward(Action action, float reward, State * currentState, State * nextState);
	void resetPlayer(void){};
};


class CMAC_QPlayer : public Player {
public:



	// Q matrix. the one that keeps the learning of this player.
	CMAC_QPlayer(int s, int p);

	Action selectAction(State * S);

	void receiveReward(Action action, float reward, State * currentState, State * nextState);

	Action amaxQ(State * S);

	float maxQ(State * S);

	void resetPlayer(void);

    void computeActiveFeatures(double* o);
    void computeActionValues(int a);
    void computeActionValues();
    void updateWeights(double delta, State * S,int bola,Action action);
    int selectEpsilonGreedyAction();
    int argmax(double QSA[],int size,double &bestvalue);
};



/*

TEAMS

*/



class Team {
public:
	int side;			// the side of the team: 0 = left and 1 = right

	Player * Players[NUM_PLAYERS];  // players of the team

	Team();
	Team(int s);				// Constructor
 	~Team();					// destructor
};

class RandomTeam : public Team {
public:
	RandomTeam(int s);			// Constructor
	~RandomTeam();				// destructor
};


class CMAC_QTeam : public Team {
public:
	CMAC_QTeam(int s);				// Constructor
	~CMAC_QTeam();					// destructor
};




/*

SIMULATOR

*/




class Simulator {
public:
	// variables for statistics
	int evol_data[TRAINING_SESSIONS][NUM_GAMES];
	int evolgoalsA[TRAINING_SESSIONS];
	int evolgoalsB[TRAINING_SESSIONS];
	int evolgameswonA[TRAINING_SESSIONS];
	int evolgameswonB[TRAINING_SESSIONS];
	int evolDraws[TRAINING_SESSIONS];

	// variables of the game
	int session, game, trial, step; 		// number of the current training session
	int isGoal;								// 0 if not goal, 1 if goal made.

	// Variable for keeping the grid of the game in the memory, for checking movements, etc.
	// grid contains the team and greadp contains the player number
	int gridP[FIELD_WIDTH][FIELD_HEIGHT];
	void printGrid(void);


	// Methods
	Simulator();					// constructor

	void execute_simulation(Team * A, Team * B);	// execute all the simulation

	void executeAction(int team, int player, Action action, State * currentState, State * nextState);
	// execute one action, computes next state

	// computes the reward.
	float computeReward(int team, int player, Action action, State * currentState, State * nextState);


	// Methods for statistics
	void record_evolution(int t, int g, int goals);
	void write_evol_data(void);
	void print_final_results(void);
};
