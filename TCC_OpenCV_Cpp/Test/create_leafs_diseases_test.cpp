#include "../create_leafs_diseases.hpp"

int main()
{
	// build_leaf_disease(const std::string& leaf_original, 
	// 					  const std::string& leaf_binary,
	// 					  const std::string& spot,
	// 					  const std::string& leaf_disease,	// output filename
	// 					  const int& infection)

	cld::build_leaf_disease(
		"../Images/images_test/Anthurium/Anthurium_alpha.jpg", 
		"../Images/images_test/Anthurium/Anthurium_bin_70-255.jpg",
		"../Images/images_test/spots/d1.png",
		"../Images/images_test/Anthurium/Anthurium_disease.jpg", 500);

	return 0;
}