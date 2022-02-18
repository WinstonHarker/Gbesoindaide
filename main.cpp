#include <iostream>
#include <vector>
#include <stdlib.h> 

class game{ // core du jeu 
    public:
        game(int x);
        ~game();
        void turn_player_one();
        void turn_player_two();
        void print_the_board();
        int is_this_a_victory(std::vector<std::vector<int>> map);
        int minimax(std::vector<std::vector<int>> map, int depth, int isMaxi);
        std::vector<std::vector<int>> the_tab;
    private:
        int len_of_map;

};


game::game(int x){  // création de la map
    for(int i = 0; i < x; i++){
        std::vector<int> to_add;
        for(int y = 0; y < x; y++)
            to_add.push_back(0);
        the_tab.push_back(to_add);
    }
    this -> len_of_map = x;
    return;
}

game::~game(){
}


int game::is_this_a_victory(std::vector<std::vector<int>> map){ //prends en entré une map vector de vector de int et un int en sorti, 2 si c'est l'ia qui gagne, 1 si c'est 'lhumain, 0 si personne, -1 une égalité
    int victory_1 = 0;
    int victory_2 = 0;
    for(int i = 0; i < map.size(); i++){
        for(int y = 0; y < map[i].size(); y++){
            if(map[i][y] == 1 || map[i][y] == 2){
                victory_1 = 0;
                victory_2 = 0;
                for(int parc = y; parc < map[i].size(); parc++){
                    if(map[i][parc] == 1){
                        victory_1 += 1;
        
                    }
                    if(map[i][parc] == 2){
                        victory_2 += 1;
                       
                    }
                    if (victory_1 == 5){
                        return 1;
                    }
                    if (victory_2 == 5){
                        return 2;
                    }
                }
                victory_1 = 0;
                victory_2 = 0;
                
                for(int parc = len_of_map - 1, count = 0; parc >= 0 ; parc--, count++){
                    if(map[parc][count] == 1){
                        victory_1 = victory_1  + 1;
                    }
                    if(map[parc][count] == 2){
                        victory_2 = victory_2  + 1;
                    }
                    if (victory_1 == 5){
                        return 1;
                    }
                    if (victory_2 == 5){
                        return 2;
                    }
                }
                victory_1 = 0;
                victory_2 = 0;
                for(int parc = i; parc < map.size(); parc++){
                    if(map[parc][y] == 1){
                        victory_1 += 1;
                       
                    }
                    if(map[parc][y] == 2){
                        victory_2 += 1;
                      
                    }
                    if (victory_1 == 5)
                        return 1;
                    
                    if (victory_2 == 5)
                        return 2;
                }
                victory_1 = 0;
                victory_2 = 0;   
            }
        }
    }
    for(int i = 0; i < map.size(); i++)
        for(int y = 0; y < map[i].size(); y++)
                if(map[i][y] == 0)
                    return 0;
    return -1;
}

int game::minimax(std::vector<std::vector<int>> map, int depth, int isMaxi){ // algorithme minmax, la ou est tout le problème
//il est en recursif, prend une map vector de vector de int, une depth qui correspond a la depth, et un bool 0 si il simule le joueur, 1 si c'est l'ia
//return un score 2 si l'ia win -1 si l'humain 1 si égalité
    int bestscore;
    int victory_or_die = this->is_this_a_victory(map);
    int score;
    std::vector<std::vector<int>> tab2; 
    
    if(victory_or_die == 2){
        return 2;
    }
    if(victory_or_die == 1)
        return -1;
    if(victory_or_die == -1)
        return 1;
    if(isMaxi == 1){
        bestscore = -999999;
        for (int i = 0; i < this -> len_of_map; i++){
            for (int j = 0; j < this -> len_of_map; j++){
                if(map[i][j] == 0){
                    for (size_t parcour = 0; parcour != map.size(); parcour++)
                        tab2.push_back(map[parcour]);
                    tab2[i][j] = 2;
                    if(depth > 1){
                        return 1;
                    }
                    score = this->minimax(tab2, depth + 1, 0);
                    tab2[i][j] = 0;
                        
                    if (score == 2){ // on fais une optimisation pour avoir le meilleurs resultat
                        tab2.clear();
                        return 2;
                    }
                    if (score > bestscore)
                        bestscore = score;
                    tab2.clear();
                }
            }
        }
        return bestscore;
    } else {
        bestscore = 999999;
        for (int i = 0; i < this -> len_of_map; i++){
            for (int j = 0; j < this -> len_of_map; j++){
                if(map[i][j] == 0){
                    for (size_t pouet = 0; pouet != map.size(); pouet ++)
                        tab2.push_back(map[pouet]);
                    tab2[i][j] = 1;
                    if(depth > 1){
                        return 1;
                    }
                    score = this->minimax(tab2, depth + 1, 1);


                    if (score == -1){//optimisation
                        tab2.clear();
                        return -1;
                    }
                    if (score < bestscore)
                        bestscore = score;
                    tab2.clear();
                }
            }
        }
        return bestscore;
    }
}

void game::turn_player_one(){ // std cout normal
    std::string get_x;
    std::string get_y;

    std::cout << "player 1 press x" << std::endl;
    std::getline (std::cin,get_x);
    std::cout << "player 1 press y" << std::endl;
    std::getline (std::cin,get_y);

    int x = atoi(get_x.c_str());
    int y = atoi(get_y.c_str());
    this->the_tab[y][x] = 1;
    return;
}
void game::turn_player_two(){
    int x = 0;
    int y = 0;
    int bestscore = -999999;
    int score;
    for (int i = 0; i < this -> len_of_map; i++) //debut du min max
        for (int j = 0; j < this -> len_of_map; j++){
            if(this->the_tab[i][j] == 0){
                this->the_tab[i][j] = 2;
                score = this->minimax(this->the_tab, 0, 1);
                this->the_tab[i][j] = 0;
                if(score > bestscore){
                    bestscore = score;
                    y = i;
                    x = j;
                    
                }
            }
        }
        
    std::cout << x << " and " << y << std::endl;
    this->the_tab[y][x] = 2;
    return;
}

void game::print_the_board(){
    for(int i = 0; i < this->the_tab.size(); i++){
        for(int y = 0; y < this->the_tab[i].size(); y++)
            std::cout << this->the_tab[i][y];
        std::cout << std::endl;
    }
    return;
}


int main(){
    game thegame = game(5);
    while(1){ //boucle de jeu
        thegame.turn_player_two();
        thegame.print_the_board();
        if(thegame.is_this_a_victory(thegame.the_tab) == 1 || thegame.is_this_a_victory(thegame.the_tab) == 2)
            return 0;
        thegame.turn_player_one();
        thegame.print_the_board();
        if(thegame.is_this_a_victory(thegame.the_tab) == 1 || thegame.is_this_a_victory(thegame.the_tab) == 2)
            return 0;
    }
    return 0;
}