#include "mountain.h"

mountain_t::mountain_t (const hitbox_t& hitbox)
{
	this->set_position(point_t(0, SCREEN_HEIGHT - hitbox.h));
	this->set_color(color_t("#c7a87e"));
	this->set_hitbox(hitbox);
	this->set_mass(24.310f);
}

void mountain_t::handle_object_collision(const object_t& object)
{
	if (typeid(object) == typeid(orbiter_t))
		this->set_color(color_t("#f00"));
}

void mountains (objects_allocator_type& objects)
{
	object_t *scenary_obj = new object_t(
		hitbox_t(SCREEN_WIDTH, 300.0f),
		point_t(0.0f, SCREEN_HEIGHT - 300.0f),
		color_t("#ccc"),
		0.0f,
		"./textures/mountains.bmp"
	);

	objects.push(scenary_obj);

	mountain_t *mountain = new mountain_t(hitbox_t(55, 105)); 
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 90)); 
	mountain->get_position().x = 55;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(15, 50)); 
	mountain->get_position().x = 60;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(65, 27)); 
	mountain->get_position().x = 75;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(27, 21)); 
	mountain->get_position().x = 140;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 25)); 
	mountain->get_position().x = 167;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 32)); 
	mountain->get_position().x = 177;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 38)); 
	mountain->get_position().x = 187;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 55)); 
	mountain->get_position().x = 192;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 65)); 
	mountain->get_position().x = 202;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 75)); 
	mountain->get_position().x = 212;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 105)); 
	mountain->get_position().x = 222;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 115)); 
	mountain->get_position().x = 232;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 125)); 
	mountain->get_position().x = 242;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 147)); 
	mountain->get_position().x = 252;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 158)); 
	mountain->get_position().x = 262;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 175)); 
	mountain->get_position().x = 272;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 185)); 
	mountain->get_position().x = 282;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 195)); 
	mountain->get_position().x = 292;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(30, 198)); 
	mountain->get_position().x = 302;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(60, 205)); 
	mountain->get_position().x = 332;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 195)); 
	mountain->get_position().x = 392;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 175)); 
	mountain->get_position().x = 397;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 80)); 
	mountain->get_position().x = 402;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 10)); 
	mountain->get_position().x = 482;
	objects.push(mountain);
	
	mountain = new mountain_t(hitbox_t(30, 20)); 
	mountain->get_position().x = 492;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 10)); 
	mountain->get_position().x = 522;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(25, 25)); 
	mountain->get_position().x = 560;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 35)); 
	mountain->get_position().x = 585;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 40)); 
	mountain->get_position().x = 595;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(20, 47)); 
	mountain->get_position().x = 605;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 45)); 
	mountain->get_position().x = 625;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 55)); 
	mountain->get_position().x = 635;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(12, 60)); 
	mountain->get_position().x = 645;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 95)); 
	mountain->get_position().x = 657;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 100)); 
	mountain->get_position().x = 667;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 107)); 
	mountain->get_position().x = 677;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(25, 113)); 
	mountain->get_position().x = 687;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 105)); 
	mountain->get_position().x = 712;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(30, 102)); 
	mountain->get_position().x = 717;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 95)); 
	mountain->get_position().x = 747;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(36, 80)); 
	mountain->get_position().x = 752;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(7, 55)); 
	mountain->get_position().x = 788;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(7, 45)); 
	mountain->get_position().x = 795;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(20, 15)); 
	mountain->get_position().x = 802;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 15)); 
	mountain->get_position().x = 1100;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 25)); 
	mountain->get_position().x = 1105;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 35)); 
	mountain->get_position().x = 1110;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 45)); 
	mountain->get_position().x = 1115;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 55)); 
	mountain->get_position().x = 1120;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 60)); 
	mountain->get_position().x = 1125;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 63)); 
	mountain->get_position().x = 1130;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 67)); 
	mountain->get_position().x = 1140;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(10, 70)); 
	mountain->get_position().x = 1150;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(20, 75)); 
	mountain->get_position().x = 1160;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 82)); 
	mountain->get_position().x = 1180;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 87)); 
	mountain->get_position().x = 1185;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 95)); 
	mountain->get_position().x = 1190;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 102)); 
	mountain->get_position().x = 1195;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 110)); 
	mountain->get_position().x = 1200;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 120)); 
	mountain->get_position().x = 1205;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 130)); 
	mountain->get_position().x = 1210;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 140)); 
	mountain->get_position().x = 1215;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 150)); 
	mountain->get_position().x = 1220;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 158)); 
	mountain->get_position().x = 1225;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 162)); 
	mountain->get_position().x = 1230;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 165)); 
	mountain->get_position().x = 1235;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 168)); 
	mountain->get_position().x = 1240;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 171)); 
	mountain->get_position().x = 1245;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 173)); 
	mountain->get_position().x = 1250;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 175)); 
	mountain->get_position().x = 1255;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 177)); 
	mountain->get_position().x = 1260;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 179)); 
	mountain->get_position().x = 1265;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 185)); 
	mountain->get_position().x = 1270;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 200)); 
	mountain->get_position().x = 1275;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 215)); 
	mountain->get_position().x = 1280;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 250)); 
	mountain->get_position().x = 1285;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 253)); 
	mountain->get_position().x = 1290;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 258)); 
	mountain->get_position().x = 1295;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 262)); 
	mountain->get_position().x = 1300;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 268)); 
	mountain->get_position().x = 1305;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 274)); 
	mountain->get_position().x = 1310;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 285)); 
	mountain->get_position().x = 1315;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 288)); 
	mountain->get_position().x = 1320;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 290)); 
	mountain->get_position().x = 1325;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 292)); 
	mountain->get_position().x = 1330;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 294)); 
	mountain->get_position().x = 1335;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 296)); 
	mountain->get_position().x = 1340;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 298)); 
	mountain->get_position().x = 1345;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(5, 299)); 
	mountain->get_position().x = 1350;
	objects.push(mountain);

	mountain = new mountain_t(hitbox_t(15, 300)); 
	mountain->get_position().x = 1355;
	objects.push(mountain);
}