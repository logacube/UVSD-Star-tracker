#pragma once
#include <string>
#include "linear_algebra.h"
#include "trees.h"
#include "database.h";
struct star_quad {
	vec<6> distances;
	float longest_arc;
};
struct star {
	char name[32];
	float right_ascension;//between 0 and 2PI
	float declination;//between -pi and +pi
	float magnitude;//just the plain old astronomical magnitude -1.0 to ~7.0
	vec<3> dir;//the normal direction of the star from the perspective of the earth and the satellite 
	star_quad primary;
};
struct sky_map {
	vec<3> dir;
	//this isn't acuually an angle. It's the threshold dot product value. 
	float bounding_angle;
	unsigned int star_count;
	star* stars;
};
class sky_atlas {
private:

public:
	unsigned int tile_count;
	sky_map* maps;
	sky_atlas(database<star> data, unsigned int subdivisions);
	star* get_visible_stars(vec<3> dir, float angle, int* star_count);
	void get_orientation(vec<2>* centroids, int visible_stars, float fov, float safety_fov, float identification_theshold, vec<3> estimated_dir, vec<3>* forward, vec<3>* right, vec<3>* up, star** true_stars, int* matches, int *top_three_matches, int* search_size);
};
int compare_stars_simple(star a, star b);
vec<3> point_on_sphere(float theta, float phi);
unsigned long long int z_index_from_star(star s);
star* generate_random_stars(unsigned int star_count);
void synthesize_database(unsigned int star_count, const char* path);
void find_star_neighbors(binary_node<star, 3>** stars, unsigned int star_count, star* start);
star** find_matches(binary_node<star, 6>* root, star_quad reference, unsigned int quad_count, int match_count);
star_quad* generate_star_quads_from_star_centroids(vec<2>* centroids, unsigned int star_count);
vec<2>* generate_synthetic_image_data(vec<3> normal, float ccw_rotation, float fov, star* stars, unsigned int star_count, unsigned int* visible_star_count, star*** visible_stars_out, float noise, int random_seed);
void test_orientation_from_centroids(vec<2>* centroids, int visible_stars, float fov, float identification_theshold, binary_node<star, 6>* root, vec<3>* forward, vec<3>* right, vec<3>* up, star** test_stars, int* matches, int* top_three_matches);
void orientation_from_centroids(vec<2>* centroids, int visible_stars, float fov, binary_node<star, 6>* root, vec<3>* forward, vec<3>* right, vec<3>* up);
float random_float(int seed);
std::string RA_to_string(float RA);
std::string DEC_to_string(float DEC);
unsigned long long int z_index_from_star_quad(star s);
