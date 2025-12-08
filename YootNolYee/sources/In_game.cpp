#include "In_game.hpp"
#include <chrono>
#include <thread>

In_game::In_game(int num_of_teams, int num_of_pieces) {
	yoots = new Yoots;
	map = new Map();
	this->num_of_teams = num_of_teams;
	this->num_of_pieces = num_of_pieces;

	std::vector<const char*> team1_img_vector;
	std::vector<const char*> team2_img_vector;
	std::vector<const char*> team3_img_vector;

	team1_img_vector.push_back(team1_1);
	team1_img_vector.push_back(team1_2);
	team1_img_vector.push_back(team1_3);
	team1_img_vector.push_back(team1_4);

	team2_img_vector.push_back(team2_1);
	team2_img_vector.push_back(team2_2);
	team2_img_vector.push_back(team2_3);
	team2_img_vector.push_back(team2_4);

	team3_img_vector.push_back(team3_1);
	team3_img_vector.push_back(team3_2);
	team3_img_vector.push_back(team3_3);
	team3_img_vector.push_back(team3_4);

	all_images.push_back(team1_img_vector);
	all_images.push_back(team2_img_vector);
	all_images.push_back(team3_img_vector);	

	for (int i = 0; i < num_of_teams; i++) {
		teams.push_back(new Team(i+1, num_of_pieces, all_images[i]));
	}
	current_team_number = 1;
	in_game_status = IN_GAME_STATUS::BEFORE_ROLL;
}

void In_game::initialize() {
	for(int i = 0; i < teams.size(); i++) {
		teams[i]->initialize();
	}
}

In_game::~In_game() {
	piece_to_move = nullptr;
	delete yoots;
	delete map;
	for (int i = 0; i < teams.size(); i++) {
		delete teams[i];
	}
}

bool In_game::is_team_region(float x, float y) {
	// if(x >= -boundaryX + WINDOW_HEIGHT / 12 - 20.f / 2.0f && 
	// 	x <= -boundaryX + WINDOW_HEIGHT / 12 * (teams[current_team_number - 1]->get_current_pieces().size() + 1) + 20.f / 2.0f &&
	// 	y >= boundaryY - WINDOW_HEIGHT / (num_of_teams + 1) * current_team_number - 20.f / 2.0f &&
	// 	y <= boundaryY - WINDOW_HEIGHT / (num_of_teams + 1) * current_team_number + 20.f / 2.0f) {
	// 		if(teams[current_team_number - 1]->get_current_pieces().size()) { // 그 team에 piece가 아직 있는 상태이면...
	// 			return true;
	// 		}
	// }

	// 대충 떼운 것... 대체 왜 위의 코드가 제대로 작동하지 않는 것인가?
	if(x >= -boundaryX && 
		x <= -MAP_boundaryX &&
		y >= boundaryY - WINDOW_HEIGHT / (num_of_teams + 1) * current_team_number - 20.f / 2.0f &&
		y <= boundaryY - WINDOW_HEIGHT / (num_of_teams + 1) * current_team_number + 20.f / 2.0f) {
			if(teams[current_team_number - 1]->get_current_pieces().size()) { // 그 team에 piece가 아직 있는 상태이면...
				return true;
			}
	}

	return false;
}

bool In_game::is_position_region(float x, float y) {
	std::vector<Position*> pos_vec = map->get_positions();
	for(int i = 0; i < pos_vec.size(); i++) {
		float center_x = (*pos_vec[i])[0];
		float center_y = (*pos_vec[i])[1];
		if(x >= center_x - pos_vec[i]->get_size() / 2 &&
			x <= center_x + pos_vec[i]->get_size() / 2 &&
			y >= center_y - pos_vec[i]->get_size() / 2 &&
			y <= center_y + pos_vec[i]->get_size()) {
				return true;
			}
	}

	return false;
}

bool In_game::is_possible_target_region(std::vector<Position*> targets, float x, float y) {
	for(int i = 0; i < targets.size(); i++) {
		if(x >= (*targets[i])[0] - targets[i]->get_size() / 2 && x <= (*targets[i])[0] + targets[i]->get_size() / 2 &&
			y >= (*targets[i])[1] - targets[i]->get_size() / 2 && y <= (*targets[i])[1] + targets[i]->get_size() / 2) {
				return true;
			}
	}
	return false;
}

Position* In_game::decide_the_real_target(std::vector<Position*> targets, float x, float y) {
	return search_selected_position(x, y);
}

Position* In_game::search_selected_position(float x, float y) {
	// 예외처리가 필요함...
	std::vector<Position*> pos_vec = map->get_positions();
	for(int i = 0; i < pos_vec.size(); i++) {
		float center_x = (*pos_vec[i])[0];
		float center_y = (*pos_vec[i])[1];
		if(x >= center_x - pos_vec[i]->get_size() / 2 &&
			x <= center_x + pos_vec[i]->get_size() / 2 &&
			y >= center_y - pos_vec[i]->get_size() / 2 &&
			y <= center_y + pos_vec[i]->get_size()) {
				return pos_vec[i];
			}
	}

	return 0; // 그냥 해둔 것.. 어차피 위에서 다 됨.
}

std::unordered_map<Position*, int> In_game::possible_targets(Position* from, std::vector<int> steps) {
	std::unordered_map<Position*, int> targets;

	//
	for(int i = 0; i < steps.size(); i++) {
	int step = steps[i];

	if(step >= 0) {
		if(from->get_nexts().size() > 1) {
			// SENTINEL 때문에 이렇게 해줌...
			if(from->get_current_pieces().back()->piece_type == Piece::PIECE_TYPE::INITIAL){
				Position* target = from;
				target = from;
				target = target->get_nexts()[1];
				for(int i = 0; i < step - 1; i++) {
					target = target->get_nexts()[0];
				}

				targets[target] = step;
			}

			else if(from == map->position_0) {
				targets[map->tail] = step;
			}
			
            else {
				Position* target1 = from; Position* target2 = from;

				for(int i = 0; i < step; i++) {
					target1 = target1->get_nexts()[0];
				}

				target2 = target2->get_nexts()[1];

				if(from == map->get_positions()[10] && step >= 4) {
					for(int i = 0; i< step - 1; i++) {
						if(target2 == map->get_positions()[22]) {
							target2 = target2->get_nexts()[1];
						}

						else {
							target2 = target2->get_nexts()[0];
						}
					}					
				}

				else {
					for(int i = 0; i< step - 1; i++) {
						target2 = target2->get_nexts()[0];
					}
				}

				targets[target1] = step; targets[target2] = step;
			}
		}

		// 단 position 22에 한해서 중요한 예외처리가 되어야함!
		// position 10, 24, 23에서 27, 28로 가야할 경우에 대한 예외임...
		else {
			if(from == map->get_positions()[24] && step >= 3) {
				Position* target = from;
				for(int i = 0; i < step; i++) {
					if(target == map->get_positions()[22]) {
						target = target->get_nexts()[1];
					}
					
					else {
						target = target->get_nexts()[0];
					}
				}
				targets[target] = step;
			}

			else if(from == map->get_positions()[23] && step >= 2) {
				Position* target = from;
				for(int i = 0; i < step; i++) {
					if(target == map->get_positions()[22]) {
						target = target->get_nexts()[1];
					}
					
					else {
						target = target->get_nexts()[0];
					}
				}
				targets[target] = step;
			}

			else {
				Position* target = from;
				for(int i = 0; i < step; i++) {
					target = target->get_nexts()[0];
				}
				targets[target] = step;
			}
		}
	}

	else {
		if(from->get_prevs().size() > 1) {
			Position* target1 = from; Position* target2 = from;
			
			target1 = target1->get_prevs()[0]; // 어차피 기껏해야 하나 가니까...
			target2 = target2->get_prevs()[1];

			targets[target1] = step; targets[target2] = step;
		}

		else {
			Position* target = from;
			target = target->get_prevs()[0];
			targets[target] = step;
		}
	}

	}
	return targets;
}

int In_game::how_many_in_tail(int team_number) {
	int num_of_objects = 0;

	for(const auto& o : map->tail->get_current_pieces()) {
		if(o->get_team_number() == team_number) {
			num_of_objects++;
		}
	}

	return num_of_objects;
}

void In_game::display() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-boundaryX, boundaryX, -boundaryY, boundaryY, -100.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//////////////////////////////////////////
    map->draw();

	for (int i = 0; i < teams.size(); i++) {
		teams[i]->draw(teams.size());
	}
	//////////////////////////////////////////

	glutSwapBuffers();
}

void In_game::mouse(int button, int state, int x, int y) { // 클릭해야만 하는 곳이 아닌 다른 곳을 클릭했을 때 예외 처리가 필요함...
	/* Implement */
	float in_game_x = -boundaryX + 2 * boundaryX / (WINDOW_WIDTH - 1) * x; // 좌표계 변환, 계산하면 나옴
	float in_game_y = boundaryY - 2 * boundaryY / (WINDOW_HEIGHT - 1) * y;

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if(in_game_status == IN_GAME_STATUS::SELECTING_PIECE) {
			if(is_team_region(in_game_x, in_game_y)) {
					std::cout << "팀 No. " << current_team_number << "의 맵 밖의 말을 골랐습니다.\n\n";
					std::cout << "이제 어디로 갈 것인지 클릭하십시오. \n\n";
					piece_to_move = teams[current_team_number - 1]->get_current_pieces().back();
					teams[current_team_number - 1]->give_a_piece_to_position(map->position_0);
					in_game_status = IN_GAME_STATUS::SELECTING_POSITION;
			}

			// "ON_GOING" piece들을 다음 idle에서 toss하는 방식으로!
		    else if(is_position_region(in_game_x, in_game_y)){ // 어떠한 piece도 없거나 다른 팀이 점령한 position을 클릭한 경우의 처리도 해주어야 함.
				Position* clicked_position = search_selected_position(in_game_x, in_game_y);

				if(clicked_position->get_current_pieces().size() &&
					clicked_position->get_current_pieces().front()->get_team_number() == current_team_number) {
					std::cout << "팀 No. " << current_team_number << "의 맵 안의 말을 골랐습니다.\n\n";
					std::cout << "이제 어디로 갈 것인지 클릭하십시오. \n\n";
					piece_to_move = clicked_position->get_current_pieces().front(); // problem?
					in_game_status = IN_GAME_STATUS::SELECTING_POSITION;
				}
			}
		}

		else if(in_game_status == IN_GAME_STATUS::SELECTING_POSITION) {
			Position* from;
			Position* target_position;
			std::unordered_map<Position*, int> map_of_positions_and_steps;
			std::vector<Position*> target_positions;

			from = piece_to_move->get_current_position();
			map_of_positions_and_steps = possible_targets(from, steps_to_go);

			for(const auto& pair : map_of_positions_and_steps) {
				target_positions.push_back(pair.first);
			}
			// target_positions = possible_targets(from, steps_to_go);

			// possible_target vector를 만든 후 거기 안에 있는 Position 중 아무거나 클릭하면 이동할 수 있게 하면 되겠다.

			if(is_possible_target_region(target_positions, in_game_x, in_game_y)) {
				target_position = decide_the_real_target(target_positions, in_game_x, in_game_y); // 사실 얘는 필요 없는 함수이다.

				float x_destination = (*target_position)[0];
				float y_destination = (*target_position)[1];
				float size = target_position->get_size();
			
				if(in_game_x >= x_destination - size / 2 && in_game_x <= x_destination + size / 2 &&
					in_game_y >= y_destination - size / 2 && in_game_y <= y_destination + size / 2) {

					int step_to_find = map_of_positions_and_steps[target_position];
					
					// 아래 주석 코드에서 step을 어떻게 골라낼 것인지만 생각하면 된다.
					auto it = std::find(steps_to_go.begin(), steps_to_go.end(), step_to_find);
					if(it != steps_to_go.end()) {
						steps_to_go.erase(it);
					}
					//

					// 다른 팀의 말을 먹는 경우의 if문
					if(target_position->get_current_pieces().size() && 
						target_position->get_current_pieces().front()->get_team_number() != current_team_number &&
						target_position->pos_type != Position::POS_TYPE::TAIL) {

						int team_number_of_target_position = target_position->get_current_pieces().front()->get_team_number();
						target_position->give_pieces_to_team(teams[team_number_of_target_position - 1]);

						in_game_status = IN_GAME_STATUS::PREPARED_TO_ROLL;
						std::cout << "팀 No. " << current_team_number << "이(가) 다른 팀의 말을 먹었습니다.\n\n";
						std::cout << "윷을 또 던질 수 있습니다. 스페이스바를 누르십시오.\n\n";
						// from->toss_a_piece(target_position);
					}

					// 모든 steps를 소진한 경우
					else if(steps_to_go.size() == 0) {
						in_game_status = IN_GAME_STATUS::PIECE_MOVING;
						std::cout << "스페이스바를 눌러 턴을 넘기도록 합니다. \n\n";
					}

					// 아직 쓸 수 있는 steps가 남아있는 경우
					else {
						in_game_status = IN_GAME_STATUS::SELECTING_PIECE;
						std::cout << "팀 No. " << current_team_number << "는 아직 더 갈 수 있습니다.\n\n";

						std::cout << "현재 갈 수 있는 step은 아래와 같습니다\n";
						std::cout <<"| ";
						for(int i = 0; i < steps_to_go.size(); i++) {
							std::cout << steps_to_go[i] << " | ";
						}
						std::cout << "\n\n";						
					}

					from->toss_a_piece(target_position);

					// ARRIVED 처리를 위해 매우 중요한 구문
					if(piece_to_move->piece_type == Piece::PIECE_TYPE::INITIAL) {
						piece_to_move->piece_type = Piece::PIECE_TYPE::ON_GOING;
					}

					if(piece_to_move->get_current_position()->pos_type == Position::POS_TYPE::TAIL) {
						piece_to_move->piece_type = Piece::PIECE_TYPE::ARRIVED;
					}
				}
			}
		}
	
	}
	glutPostRedisplay();
}

void In_game::keyboardDown(unsigned char key, int x, int y) {
	switch (key)
	{
	case ' ':
		if(in_game_status == IN_GAME_STATUS::PREPARED_TO_ROLL) {
			std::cout << "팀 No. " << current_team_number << "이(가) 윷을 던집니다.\n\n";
			int step = yoots->roll();
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "과연? \n\n"; 
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "뭐가?\n\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "나올까요?\n\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			yoots->print();


			if(step == 0) {
				std::cout << "NAK!!!\n\n";

				if(steps_to_go.size() == 0) {
					in_game_status = IN_GAME_STATUS::BEFORE_ROLL;
					current_team_number = (current_team_number) % (num_of_teams) + 1;
				}

				else {
					in_game_status = IN_GAME_STATUS::SELECTING_PIECE;
					std::cout << "현재 갈 수 있는 step은 아래와 같습니다\n";
					std::cout <<"| ";
					for(int i = 0; i < steps_to_go.size(); i++) {
						std::cout << steps_to_go[i] << " | ";
					}
					std::cout << "\n\n";
				}
			}

            // num_of_piece - current_piece의 size = tail의 team_number 개수와 일치할 경우 넘어가야함.
			else if(step == -1 && (num_of_pieces - teams[current_team_number - 1]->get_current_pieces().size() 
									== how_many_in_tail(current_team_number))){
				if(steps_to_go.size() == 0) {
					std::cout << "아무 말도 없을 때 빽도가 나왔습니다. ㅋㅋㅋㅋ 턴이 넘어갑니다.\n\n";
					in_game_status = IN_GAME_STATUS::BEFORE_ROLL;
					current_team_number = (current_team_number) % (num_of_teams) + 1;
				}

				else {
					steps_to_go.push_back(step);
					std::cout << step << " is push_backed \n\n";
					in_game_status = IN_GAME_STATUS::SELECTING_PIECE;
					std::cout << "현재 갈 수 있는 step은 아래와 같습니다\n";
					std::cout <<"| ";
					for(int i = 0; i < steps_to_go.size(); i++) {
						std::cout << steps_to_go[i] << " | ";
					}
					std::cout << "\n\n";
				}
			}

			else if(step >= 4) {
				steps_to_go.push_back(step);
				std::cout << step << " is push_backed \n\n";

				std::cout << "현재 갈 수 있는 step은 아래와 같습니다\n";
				std::cout <<"| ";
				for(int i = 0; i < steps_to_go.size(); i++) {
					std::cout << steps_to_go[i] << " | ";
				}
				std::cout << "\n\n";

				std::cout << "윷을 다시 던질 수 있습니다. SPACEBAR를 누르십시오. \n\n";
				in_game_status = IN_GAME_STATUS::PREPARED_TO_ROLL;
			}

			else {
				steps_to_go.push_back(step);
				std::cout << step << " is push_backed \n\n";
				in_game_status = IN_GAME_STATUS::SELECTING_PIECE;

				std::cout << "현재 갈 수 있는 step은 아래와 같습니다.\n";
				std::cout <<"| ";
				for(int i = 0; i < steps_to_go.size(); i++) {
					std::cout << steps_to_go[i] << " | ";
				}
				std::cout << "\n\n";
			}	

			break;
		}

		if(in_game_status == IN_GAME_STATUS::PIECE_MOVING) {

			current_team_number = (current_team_number) % (num_of_teams) + 1;

			// steps_to_go.clear();

			in_game_status = IN_GAME_STATUS::BEFORE_ROLL;

			std::cout << "다음 팀으로 넘어갑니다.\n\n";
		}

		glutPostRedisplay();

	default:
		break;
	}

	glutPostRedisplay();
}

void In_game::idle() {
	if(how_many_in_tail(current_team_number) == num_of_pieces) {
		std::cout << "팀 No. " << current_team_number << "은(는) 이미 게임이 끝났습니다.\n 다음 팀으로 넘어갑니다.\n\n";
		steps_to_go.clear();
		current_team_number = (current_team_number) % (num_of_teams) + 1;
		in_game_status = IN_GAME_STATUS::PREPARED_TO_ROLL;
	}

	if(in_game_status == IN_GAME_STATUS::BEFORE_ROLL) {
		std::cout << "팀 No. " << current_team_number << "은(는) SPACEBAR를 눌러서 윷을 던지거라~~~~~~~~~\n\n";
		in_game_status = IN_GAME_STATUS::PREPARED_TO_ROLL;
	}
}