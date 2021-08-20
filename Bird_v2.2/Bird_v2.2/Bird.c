#include<stdio.h>
#include<stdlib.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include<time.h>


// Reset Function ##############################
void rest_game_array_0(int a[]);
void rest_game_array_575(int a[]);
void rest_game_array_600(int a[]);
void drop_box(int a[]);

int main() {

	// RANDOM NUMBER ###################
	srand(time(NULL));

	// ALLEGRO THINGS #####################
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* queue = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	// PİCTURE ####################
	ALLEGRO_BITMAP* background1 = NULL;
	ALLEGRO_BITMAP* background2 = NULL;
	ALLEGRO_BITMAP* background3 = NULL;
	ALLEGRO_BITMAP* background4 = NULL;
	ALLEGRO_BITMAP* box = NULL;
	ALLEGRO_BITMAP* menu = NULL;
	ALLEGRO_BITMAP* alt = NULL;
	ALLEGRO_BITMAP* alt2 = NULL;
	ALLEGRO_BITMAP* finish = NULL;
	ALLEGRO_BITMAP* player1 = NULL;
	ALLEGRO_BITMAP* player2 = NULL;

	// MUSİC #########################
	ALLEGRO_SAMPLE* music1 = NULL;
	ALLEGRO_SAMPLE* music2 = NULL;
	ALLEGRO_SAMPLE_INSTANCE* songinstance1 = NULL;
	ALLEGRO_SAMPLE_INSTANCE* songinstance2 = NULL;

	// GLOBAL VARIABLE ###################
	int xpos = 200, ypos = 575;// player x and y
	int bl = 0;// random number
	int bls[8] = { 0 };//this location is filled 
	int ks[8] = { 0 };// boxes Column
	int kc[8] = { 0 };// Getting On The Boxes (between boxes)
	int kct[8] = { 575 ,  575 , 575 , 575 , 575 , 575 , 575 , 575 };//player y location
	int kb[8] = { 0 };// shows if there is a box
	int FPS = 30;// FPS
	int tr[8] = { 0 };// Boxes fall from above
	int a = 0;// location is where boxes drop
	int kut[8] = { 600,600,600,600,600,600,600,600 };// Boxes y location
	int yd[8] = { 0 };// Boxes in graound (for player)
	int yy[8] = { 0 };// upper the ground
	int point = 0;// point
	int mpoint = 0;// max point
	int start = 1;// Start
	int tk = 0;// Answer Y
	int tk_N = 0;// Answer N
	int dn = 1;// Loop
	int bd[8] = { 0 };//Boxes droped
	int bdg[8] = { 0 };//Boxes in graound (for draw boxes)
	int music_stop = 0;//Stop all music
	int music1_play = 0;//start music 1
	int music2_play = 0;//start music 2
	int yst = 0;//Background draw
	int pw = 1;//player direction
	int bc = 0;//boxes down


	al_init();

	// ADDONs ##########################
	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();

	// LOAD PİCTURE ################
	background1 = al_load_bitmap("background1.jpg");
	background2 = al_load_bitmap("background2.jpg");
	background3 = al_load_bitmap("background3.jpg");
	background4 = al_load_bitmap("background4.jpg");
	box = al_load_bitmap("Kutu.jpg");
	menu = al_load_bitmap("Start-menu.jpg");
	alt = al_load_bitmap("alt.jpg");
	alt2 = al_load_bitmap("Alt-kutu.jpg");
	finish = al_load_bitmap("son.jpg");
	player1 = al_load_bitmap("Player-L.png");
	player2 = al_load_bitmap("Player-R.png");

	// SAOUND #####################

	al_reserve_samples(10);
	music1 = al_load_sample("music1.ogg");
	music2 = al_load_sample("music2.ogg");
	songinstance1 = al_create_sample_instance(music1);
	songinstance2 = al_create_sample_instance(music2);
	al_set_sample_instance_playmode(songinstance1, ALLEGRO_PLAYMODE_LOOP);
	al_set_sample_instance_playmode(songinstance2, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songinstance1, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(songinstance2, al_get_default_mixer());

	// SCREEN ################
	display = al_create_display(400, 700);

	// MOVING EVENTS ##############
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_keyboard_event_source());

	// TIMING EVENT #################
	timer = al_create_timer(1.0 / FPS);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	// SCREEN WİDTH-HEİGHT ###################
	int screen_w = al_get_display_width(display);
	int screen_h = al_get_display_height(display);

	// FONTs ##################
	ALLEGRO_FONT* font24 = al_load_font("arial.ttf", 24, 0);
	ALLEGRO_FONT* font36 = al_load_font("arial.ttf", 36, 0);
	ALLEGRO_FONT* font18 = al_load_font("arial.ttf", 18, 0);


	while (dn) {


		// EVENTs ##############
		ALLEGRO_EVENT ev; // moving
		ALLEGRO_EVENT evt;// timing




		// Start - Menu ##############
		if (start) {


			//Music - Star (in Start Menu)#################
			if (music1_play == 1) {
				al_stop_sample_instance(songinstance2);
				al_play_sample_instance(songinstance1);
				music1_play = 0;
				music2_play = 0;
				music_stop = 0;
			}
			if (music2_play == 1) {
				al_stop_sample_instance(songinstance1);
				al_play_sample_instance(songinstance2);
				music1_play = 0;
				music2_play = 0;
				music_stop = 0;
			}
			if (music_stop == 1) {
				al_stop_sample_instance(songinstance1);
				al_stop_sample_instance(songinstance2);
				music1_play = 0;
				music2_play = 0;
				music_stop = 0;
			}

			//Main menu informations #################
			al_draw_bitmap(menu, 0, 0, 0);
			al_draw_text(font18, al_map_rgb(255, 0, 0), (screen_w / 2) + 85, (screen_h / 2) - 300, ALLEGRO_ALIGN_CENTRE, "Press 1 or 2 to listen music");
			al_draw_text(font18, al_map_rgb(255, 0, 0), (screen_w / 2) + 85, (screen_h / 2) - 285, ALLEGRO_ALIGN_CENTRE, "and press 3 stop the music");
			al_draw_text(font18, al_map_rgb(255, 0, 0), (screen_w / 2), (screen_h / 2) - 270, ALLEGRO_ALIGN_CENTRE, "(you can change the music when you want)");
			al_draw_text(font18, al_map_rgb(255, 127, 0), (screen_w / 2), screen_h / 2, ALLEGRO_ALIGN_CENTRE, "Please start to play the game press a button");
			al_draw_rectangle(100, 400, 300, 450, al_map_rgb(255, 255, 255), 5);
			al_draw_text(font36, al_map_rgb(0, 0, 0), screen_w / 2, 405, ALLEGRO_ALIGN_CENTRE, "SPACE");

			al_flip_display();

			al_wait_for_event(queue, &ev);

			//Play - Stop main manu music #############
			if (ev.keyboard.keycode == ALLEGRO_KEY_1)
				music1_play = 1;
			if (ev.keyboard.keycode == ALLEGRO_KEY_2)
				music2_play = 1;
			if (ev.keyboard.keycode == ALLEGRO_KEY_3)
				music_stop = 1;

			if (ev.keyboard.keycode != ALLEGRO_KEY_SPACE)
				continue;

			start = 0;
			al_start_timer(timer);

		}


		// Music (in The Game)#############
		if (ev.keyboard.keycode == ALLEGRO_KEY_1)
			music1_play = 1;
		if (ev.keyboard.keycode == ALLEGRO_KEY_2)
			music2_play = 1;
		if (ev.keyboard.keycode == ALLEGRO_KEY_3)
			music_stop = 1;


		//Play - Stop music (in the game) #############
		if (music1_play == 1) {
			al_stop_sample_instance(songinstance2);
			al_play_sample_instance(songinstance1);
			music1_play = 0;
			music2_play = 0;
			music_stop = 0;
		}
		if (music2_play == 1) {
			al_stop_sample_instance(songinstance1);
			al_play_sample_instance(songinstance2);
			music1_play = 0;
			music2_play = 0;
			music_stop = 0;
		}
		if (music_stop == 1) {
			al_stop_sample_instance(songinstance1);
			al_stop_sample_instance(songinstance2);
			music1_play = 0;
			music2_play = 0;
			music_stop = 0;
		}

		al_clear_to_color(al_map_rgb(0, 0, 0));

		//Timer ##############
		al_wait_for_event(event_queue, &evt);
		al_get_next_event(queue, &ev);

		// Background ############
		if (yst == 0) {
			al_draw_bitmap(background1, 0, 0, 0);
		}
		if (yst == 1) {
			al_draw_bitmap(background2, 0, 0, 0);
		}
		if (yst == 2) {
			al_draw_bitmap(background3, 0, 0, 0);
		}
		if (yst == 3) {
			al_draw_bitmap(background4, 0, 0, 0);
		}

		// Information how to play this game
		if (point < 100) {

			// Left #####
			al_draw_rectangle(100, 500, 150, 550, al_map_rgb(255, 255, 255), 5);
			al_draw_line(120, 525, 145, 525, al_map_rgb(255, 255, 255), 3);
			al_draw_filled_triangle(120, 519, 120, 531, 110, 525, al_map_rgb(255, 255, 255));

			// Right #####
			al_draw_rectangle(250, 500, 300, 550, al_map_rgb(255, 255, 255), 5);
			al_draw_line(255, 525, 280, 525, al_map_rgb(255, 255, 255), 3);
			al_draw_filled_triangle(280, 519, 280, 531, 290, 525, al_map_rgb(255, 255, 255));

		}


		// Moving #############
		if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT && xpos < 400) {
			xpos += 10;
			pw = 0;
			ev.keyboard.keycode = ALLEGRO_KEY_SPACE;
		}
		if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT && xpos > 0) {
			xpos -= 10;
			pw = 1;
			ev.keyboard.keycode = ALLEGRO_KEY_SPACE;
		}



		// Determines To Which Area The Boxes Will Be Randomly Thrown ###################
		if (tr[bl] == 0) {

			bl = rand() % 8;

			if (bl == 0) {
				a = 0;
				kb[0] = 1;
				ks[0] = 1;
				kc[0] ++;
				yy[0] ++;
				bd[0]++;
			}
			if (bl == 1) {
				a = 50;
				kb[1] = 1;
				ks[1] = 1;
				kc[1] ++;
				yy[1] ++;
				bd[1]++;
			}
			if (bl == 2) {
				a = 100;
				kb[2] = 1;
				ks[2] = 1;
				kc[2] ++;
				yy[2] ++;
				bd[2]++;
			}
			if (bl == 3) {
				a = 150;
				kb[3] = 1;
				ks[3] = 1;
				kc[3] ++;
				yy[3] ++;
				bd[3]++;
			}
			if (bl == 4) {
				a = 200;
				kb[4] = 1;
				ks[4] = 1;
				kc[4] ++;
				yy[4] ++;
				bd[4]++;
			}
			if (bl == 5) {
				a = 250;
				kb[5] = 1;
				ks[5] = 1;
				kc[5] ++;
				yy[5] ++;
				bd[5]++;
			}
			if (bl == 6) {
				a = 300;
				kb[6] = 1;
				ks[6] = 1;
				kc[6] ++;
				yy[6] ++;
				bd[6]++;
			}
			if (bl == 7) {
				a = 350;
				kb[7] = 1;
				ks[7] = 1;
				kc[7] ++;
				yy[7] ++;
				bd[7]++;
			}
		}

		// The Following Code Lets The Boxes Drop Down The Screen ##################
		if (tr[bl] <= kut[bl] + 10) {
			al_draw_bitmap(box, a, tr[bl], 0);

			tr[bl] += 10;
		}

		// Calculate The Point
		if (tr[bl] == kut[bl]) {
			point = point + (ks[bl] * 100);
		}

		// It Causes The Boxes To Stay On Ground  ###################

		// 0. Area #####
		if (kb[0] == 1 && tr[0] == kut[0] || bls[0]) {

			if (tr[0] == kut[0]) {
				if (kut[0] > 0) {
					if (ks[0]) {
						kut[0] -= 50;
						ks[0] = 0;
					}
				}
				yd[0] = 1;
				bdg[0] = bd[0];
			}
			if (bdg[0] > 0) {
				for (int j = bdg[0]; j > 0; j--) {
					al_draw_bitmap(box, 0, 600 - (j * 50), 0, 0);
				}
			}

			bls[0] = 1;

		}

		// 1. Area #####
		if (kb[1] == 1 && tr[1] == kut[1] || bls[1]) {

			if (tr[1] == kut[1]) {
				if (kut[1] > 0) {
					if (ks[1]) {
						kut[1] -= 50;
						ks[1] = 0;
					}
				}
				yd[1] = 1;
				bdg[1] = bd[1];
			}
			if (bdg[1] > 0) {
				for (int j = bdg[1]; j > 0; j--) {
					al_draw_bitmap(box, 50, 600 - (j * 50), 0, 0);
				}
			}

			bls[1] = 1;

		}

		// 2. Area #####
		if (kb[2] == 1 && tr[2] == kut[2] || bls[2]) {

			if (tr[2] == kut[2]) {
				if (kut[2] > 0) {
					if (ks[2]) {
						kut[2] -= 50;
						ks[2] = 0;
					}
				}
				yd[2] = 1;
				bdg[2] = bd[2];
			}
			if (bdg[2] > 0) {
				for (int j = bdg[2]; j > 0; j--) {
					al_draw_bitmap(box, 100, 600 - (j * 50), 0, 0);
				}
			}

			bls[2] = 1;
		}

		// 3. Area #####
		if (kb[3] == 1 && tr[3] == kut[3] || bls[3]) {

			if (tr[3] == kut[3]) {
				if (kut[3] > 0 && tr[3] == kut[3]) {
					if (ks[3]) {
						kut[3] -= 50;
						ks[3] = 0;
					}
				}
				yd[3] = 1;
				bdg[3] = bd[3];
			}

			if (bdg[3] > 0) {
				for (int j = bdg[3]; j > 0; j--) {
					al_draw_bitmap(box, 150, 600 - (j * 50), 0, 0);
				}
			}


			bls[3] = 1;
		}

		// 4. Area #####
		if (kb[4] == 1 && tr[4] == kut[4] || bls[4]) {

			if (tr[4] == kut[4]) {
				if (kut[4] > 0) {
					if (ks[4]) {
						kut[4] -= 50;
						ks[4] = 0;
					}
				}
				yd[4] = 1;
				bdg[4] = bd[4];
			}
			if (bdg[4] > 0) {
				for (int j = bdg[4]; j > 0; j--) {
					al_draw_bitmap(box, 200, 600 - (j * 50), 0, 0);
				}
			}

			bls[4] = 1;
		}

		// 5. Area #####
		if (kb[5] == 1 && tr[5] == kut[5] || bls[5]) {

			if (tr[5] == kut[5]) {
				if (kut[5] > 0) {
					if (ks[5]) {
						kut[5] -= 50;
						ks[5] = 0;
					}
				}
				yd[5] = 1;
				bdg[5] = bd[5];
			}
			if (bdg[5] > 0) {
				for (int j = bdg[5]; j > 0; j--) {
					al_draw_bitmap(box, 250, 600 - (j * 50), 0, 0);
				}
			}


			bls[5] = 1;
		}

		// 6. Area #####
		if (kb[6] == 1 && tr[6] == kut[6] || bls[6]) {

			if (tr[6] == kut[6]) {
				if (kut[6] > 0) {
					if (ks[6]) {
						kut[6] -= 50;
						ks[6] = 0;
					}
				}
				yd[6] = 1;
				bdg[6] = bd[6];
			}
			if (bdg[6] > 0) {
				for (int j = bdg[6]; j > 0; j--) {
					al_draw_bitmap(box, 300, 600 - (j * 50), 0, 0);
				}
			}


			bls[6] = 1;
		}

		// 7. Area #####
		if (kb[7] == 1 && tr[7] == kut[7] || bls[7]) {

			if (tr[7] == kut[7]) {
				if (kut[7] > 0) {
					if (ks[7]) {
						kut[7] -= 50;
						ks[7] = 0;
					}
				}
				yd[7] = 1;
				bdg[7] = bd[7];
			}
			if (bdg[7] > 0) {
				for (int j = bdg[7]; j > 0; j--) {
					al_draw_bitmap(box, 350, 600 - (j * 50), 0, 0);
				}
			}

			bls[7] = 1;
		}

		// Lower #################
		al_draw_bitmap(alt, 0, 600, 0);
		al_draw_textf(font18, al_map_rgb(255, 0, 127), screen_w / 2, 625, ALLEGRO_ALIGN_CENTRE, "Max : %d", mpoint / 100);
		al_draw_textf(font36, al_map_rgb(255, 0, 127), screen_w / 2, 650, ALLEGRO_ALIGN_CENTRE, "%d", point / 100);
		if (bc)
			al_draw_bitmap(alt2, 0, 600, 0);


		// Getting On The Boxes #############################################

		// Area 0 #####
		if (0 <= xpos && xpos <= 50 && bls[0]) {

			if (yd[0] == 1) {
				for (int j = kc[0]; j > 0; j--) {
					kct[0] -= 50;
				}
				kc[0] = 0;
				yd[0] = 0;
			}
			ypos = kct[0];

		}

		// Area 1 #####
		if (xpos > 50 && xpos < 100 && bls[1]) {

			if (yd[1] == 1) {
				for (int j = kc[1]; j > 0; j--) {
					kct[1] -= 50;
				}
				kc[1] = 0;
				yd[1] = 0;
			}

			ypos = kct[1];

		}

		// Area 2 #####
		if (xpos > 100 && xpos < 150 && bls[2]) {

			if (yd[2] == 1) {
				for (int j = kc[2]; j > 0; j--) {
					kct[2] -= 50;
				}
				kc[2] = 0;
				yd[2] = 0;
			}

			ypos = kct[2];

		}

		// Area 3 #####
		if (xpos > 150 && xpos < 200 && bls[3]) {

			if (yd[3] == 1) {
				for (int j = kc[3]; j > 0; j--) {
					kct[3] -= 50;
				}
				kc[3] = 0;
				yd[3] = 0;
			}

			ypos = kct[3];

		}

		// Area 4 #####
		if (xpos > 200 && xpos < 250 && bls[4]) {

			if (yd[4] == 1) {
				for (int j = kc[4]; j > 0; j--) {
					kct[4] -= 50;
				}
				kc[4] = 0;
				yd[4] = 0;
			}

			ypos = kct[4];

		}

		// Area 5 #####
		if (xpos > 250 && xpos < 300 && bls[5]) {

			if (yd[5] == 1) {
				for (int j = kc[5]; j > 0; j--) {
					kct[5] -= 50;
				}
				kc[5] = 0;
				yd[5] = 0;
			}

			ypos = kct[5];

		}

		// Area 6 #####
		if (xpos > 300 && xpos < 350 && bls[6]) {

			if (yd[6] == 1) {
				for (int j = kc[6]; j > 0; j--) {
					kct[6] -= 50;
				}
				kc[6] = 0;
				yd[6] = 0;
			}

			ypos = kct[6];

		}

		// Area 7 #####
		if (xpos > 350 && xpos < 400 && bls[7]) {

			if (yd[7] == 1) {
				for (int j = kc[7]; j > 0; j--) {
					kct[7] -= 50;
				}
				kc[7] = 0;
				yd[7] = 0;
			}

			ypos = kct[7];

		}

		// Drop On The Ground (For Player) ###########
		if (xpos < 50 && bls[0] == 0 || xpos > 50 && xpos < 100 && bls[1] == 0 || xpos > 100 && xpos < 150 && bls[2] == 0 || xpos > 150 && xpos < 200 && bls[3] == 0 || xpos > 200 && xpos < 250 && bls[4] == 0 || xpos > 250 && xpos < 300 && bls[5] == 0 || xpos > 300 && xpos < 350 && bls[6] == 0 || xpos > 350 && xpos < 400 && bls[7] == 0) {
			ypos = 575;
		}

		// This Code Lets To Up The Screen ##############
		if (tr[bl] > kut[bl]) {
			if (yy[0] > 0 && yy[1] > 0 && yy[2] > 0 && yy[3] > 0 && yy[4] > 0 && yy[5] > 0 && yy[6] > 0 && yy[7] > 0) {
				if (yst < 3)
					yst++;
				drop_box(kut);
				drop_box(kct);
				for (int t = 0; t < 8; t++) {
					yy[t] --;
				}
				for (int t = 0; t < 8; t++) {
					bdg[t] --;
				}
				for (int t = 0; t < 8; t++) {
					bd[t] --;
				}
				bc = 1;
			}
		}

		// Draw The Player #############
		if (pw == 1)
			al_draw_bitmap(player1, xpos - 20, ypos - 10, 0);
		if (pw == 0)
			al_draw_bitmap(player2, xpos - 20, ypos - 10, 0);


		al_flip_display();

		// If Player dead ###############
		while ((ypos - 50) - tr[bl] <= 0 && a <= xpos && xpos <= a + 50) {

			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_stop_timer(timer);

			al_draw_bitmap(finish, 0, 0, 0);
			al_draw_text(font36, al_map_rgb(255, 127, 127), screen_w / 2, screen_h / 2, ALLEGRO_ALIGN_CENTRE, "THE GAME OVER");
			al_draw_text(font18, al_map_rgb(255, 255, 255), (screen_w / 2), (screen_h / 2) + 50, ALLEGRO_ALIGN_CENTRE, "Do you want to play again ? (y/n)");
			al_draw_textf(font24, al_map_rgb(255, 0, 127), screen_w / 2, (screen_h / 2) - 50, ALLEGRO_ALIGN_CENTRE, "Your Score : %d", point / 100);

			al_flip_display();

			al_wait_for_event(queue, &ev);

			// Replay The Game ############
			if (ev.keyboard.keycode == ALLEGRO_KEY_Y) {
				rest_game_array_0(bls);
				rest_game_array_0(ks);
				rest_game_array_0(kc);
				rest_game_array_0(kb);
				rest_game_array_0(tr);
				rest_game_array_0(yd);
				rest_game_array_0(bd);
				rest_game_array_0(bdg);
				rest_game_array_575(kct);
				rest_game_array_600(kut);

				if (point > mpoint) {
					mpoint = point;
				}

				yst = 0;
				bl = 0;
				a = 0;
				xpos = 200;
				ypos = 575;
				point = 0;
				start = 1;
				tk = 1;



			}
			// Finish The Game ############
			else if (ev.keyboard.keycode == ALLEGRO_KEY_N) {
				dn = 0;
				tk_N = 1;
				break;
			}
			// If Player Press The Unwanted Key ###########
			else if (ev.keyboard.keycode != ALLEGRO_KEY_N && ev.keyboard.keycode != ALLEGRO_KEY_Y) {
				continue;
			}
		}

		// Stop The Loop ###########
		if (tk_N == 1) {

			al_stop_sample_instance(songinstance1);
			al_stop_sample_instance(songinstance2);
			al_destroy_sample(music1);
			al_destroy_sample(music2);
			al_destroy_sample_instance(songinstance1);
			al_destroy_sample_instance(songinstance2);
			al_destroy_bitmap(player1);
			al_destroy_bitmap(alt);
			al_destroy_bitmap(box);
			al_destroy_bitmap(menu);
			al_destroy_bitmap(finish);
			al_destroy_bitmap(background1);
			al_destroy_bitmap(background2);
			al_destroy_bitmap(background3);
			al_destroy_bitmap(background4);
			al_destroy_timer(timer);
			al_destroy_event_queue(queue);
			al_destroy_event_queue(event_queue);
			al_destroy_display(display);

			break;
		}

		// Start Loop Again ###########
		if (tk == 1) {
			tk = 0;
			continue;
		}


		// Stop Drop The Boxes ######################
		if (tr[0] > kut[0]) {
			tr[0] = 0;
		}
		if (tr[1] > kut[1]) {
			tr[1] = 0;
		}
		if (tr[2] > kut[2]) {
			tr[2] = 0;
		}
		if (tr[3] > kut[3]) {
			tr[3] = 0;
		}
		if (tr[4] > kut[4]) {
			tr[4] = 0;
		}
		if (tr[5] > kut[5]) {
			tr[5] = 0;
		}
		if (tr[6] > kut[6]) {
			tr[6] = 0;
		}
		if (tr[7] > kut[7]) {
			tr[7] = 0;
		}

		point++;
	}


	return 0;
}


//Reset Function
void rest_game_array_0(int a[]) {
	for (int t = 0; t < 8; t++) {
		a[t] = 0;
	}
}
void rest_game_array_575(int a[]) {
	for (int t = 0; t < 8; t++) {
		a[t] = 575;
	}
}
void rest_game_array_600(int a[]) {
	for (int t = 0; t < 8; t++) {
		a[t] = 600;
	}
}
void drop_box(int a[]) {
	for (int t = 0; t < 8; t++) {
		a[t] += 50;
	}
}