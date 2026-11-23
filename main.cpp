#include <iostream>
#include "bowling_frame.h"
#include <random>

using namespace std;

std::random_device dev_main;
std::mt19937 rng_main(dev_main());

int current_game_total(Bowling_Frame * first_frame)
{
	Bowling_Frame * temp = first_frame;
	int game_total = 0;
	while(temp)
	{
		game_total += temp->frame_score();
		temp = temp->next_frame();
	}
	return game_total;	
}

void printGame(Bowling_Frame * firstFrame, int playerNum){
	Bowling_Frame * traverse = firstFrame;
	while(traverse){
		cout << "Frame " << traverse->frame_num() << ": " << endl
		     << " Score 1: " << traverse->score1() << endl
		     << " Score 2: " << traverse->score2() << endl;
		if(traverse->frame_num() == 10 && (traverse->strike() || traverse->spare())){
			cout << " Score 3: " << traverse->score3() << endl;
		}
		traverse = traverse->next_frame();
	}
	cout << endl << "Total Game Score for player " << playerNum << ": " << current_game_total(firstFrame) << endl << endl;
}

int main(int argc, char * argv[])
{
	//make frames
	const int framesPerGame = 10;

	if(argc != 2){
		cout << "Usage: " << argv[0] << " <num_players>" << endl;
		return 0;
	}
	int num_players = stoi(argv[1]);
	if(num_players <= 0){
		cout << "Usage: " << argv[0] << " <num_players>" << endl;
		cout << "<num_players> must be a positive int" << endl;
		return 1;
	}
	cout << "Player count is: " << num_players << endl;
// the bowling_frame pointers with 1 element for each playa
	Bowling_Frame ** players = new Bowling_Frame*[num_players];

	for(int p = 0; p < num_players; p++){
		Bowling_Frame * prev = nullptr;
		for(int f = 1; f <= framesPerGame; f++){
			Bowling_Frame * current = new Bowling_Frame(f);
			if(f == 1){
				players[p] = current; // first frame  
			}
			else{
				prev->next_frame(current);
				current->prev_frame(prev);   
			}
			prev = current;
		}
	}

	for(int p = 0; p < num_players; p++){
		for(int roll = 0; roll < framesPerGame * 2 + 1; roll++){
			players[p]->update_scores();
		}
	}

	for(int p = 0; p < num_players; p++){
		printGame(players[p], p + 1);
	}

	for(int p = 0; p < num_players; p++){
		Bowling_Frame * current = players[p];
		while(current){
			Bowling_Frame * next = current->next_frame();
			delete current;
			current = next;
		}
	}
	delete [] players;

	return 0;

}
