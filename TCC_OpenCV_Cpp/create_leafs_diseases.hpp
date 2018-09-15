#ifndef CREATE_LEAFS_DISEASES_HPP
#define CREATE_LEAFS_DISEASES_HPP

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include <iostream>

namespace cld {

	bool check_color(const cv::Mat& src, int y, int x)
	{
		// Posição alvo é o limbo foliar branco
		cv::Vec3b color = src.at<cv::Vec3b>(cv::Point(y,x));

		if (color[0] == 255 && color[1] == 255 && color[2] == 255)
			return true;

		return false;
	}

	bool check_pos(const cv::Mat& src, const cv::Point& pt,
		int spotY, int spotX)
	{
		int y = spotY / 2;
		int x = spotX / 2;
		if (!check_color(src, pt.y, pt.x)) return false;
		if (!check_color(src, pt.y, pt.x + x)) return false;
		if (!check_color(src, pt.y, pt.x + spotX)) return false;

		if (!check_color(src, pt.y + y, pt.x)) return false;
		if (!check_color(src, pt.y + y, pt.x + x)) return false;
		if (!check_color(src, pt.y + y, pt.x + spotX)) return false;		


		if (!check_color(src, pt.y + spotY, pt.x)) return false; 
		if (!check_color(src, pt.y + spotY, pt.x + x)) return false; 
		if (!check_color(src, pt.y + spotY, pt.x + spotX)) return false;

		return true;
	}

	void infect(cv::Mat& image_original, int y, int x, const cv::Mat& image_spot)
	{
		double alpha(0.8);
		double beta(1.0);

		cv::Mat roi = image_original(cv::Rect(x, y, image_spot.rows,
			image_spot.cols));
		// cv::imshow("roi", roi);

		cv::Mat blend;
		addWeighted(image_spot, alpha, roi, beta, 0.0, blend);
		// cv::imshow("blend", blend);
		
		blend.copyTo(image_original(cv::Rect(x, y, blend.rows, blend.cols)));
	}

	int build_leaf_disease(const std::string& leaf_original, 
		const std::string& leaf_binary, const std::string& spot,
		const std::string& leaf_disease, const int& infection)
	{
		cv::Mat image_spot = cv::imread(spot);
        if(image_spot.empty()) { 
			std::cout << "could not open Spot image!\n";
        	return (EXIT_FAILURE);
        }  		
		
		cv::Mat image_bin = cv::imread(leaf_binary);
		if(image_bin.empty()) { 
			std::cout << "could not open Binary image!\n";
        	return (EXIT_FAILURE);
        }

		cv::Mat image_original = cv::imread(leaf_original);
		if(image_original.empty()) { 
			std::cout << "could not open Original image!\n";
        	return (EXIT_FAILURE);
        }

        cv::Point pt_leaf;
 		cv::RNG rng(0xFFFFFFFF);
        int windowHeight = image_bin.rows;
        int windowWidth  = image_bin.cols;
        int spotY = image_spot.rows;
        int spotX = image_spot.cols;

        if (windowHeight <= spotY || windowWidth <= spotX)
         return (EXIT_FAILURE);

        for (int i = 0; i < infection; ++i)
        {
        	int count(100);
        	while(count--) {

        		// Escolher um ponto na imagem binária
        		pt_leaf.y = rng.uniform(spotY, windowHeight - spotY);        		
        		pt_leaf.x = rng.uniform(spotX, windowWidth  - spotX);
        		std::cout << ".";

        		if (check_pos(image_bin, pt_leaf, spotY, spotX)) {

        			// Misturar imagem de mancha foliar e folha sadia
        			std::cout << " point ... ok!" << '\n';
        			infect(image_original, pt_leaf.y, pt_leaf.x, image_spot);

        			// Marcar na imagem binária o espaço alterado
					cv::Point pt;
					pt.y = pt_leaf.y + image_spot.rows;
					pt.x = pt_leaf.x + image_spot.cols;
					cv::rectangle(image_bin, pt_leaf, pt,cv::Scalar(0, 0, 255)
						, 1, 1);

					// Visualizar
					// cv::imshow("spot", image_spot);
					cv::imshow("Binary", image_bin);
					cv::imshow("Leaf Disease", image_original);
					cv::waitKey(10);

        			break;
        		}
        	}
        }
        // cv::waitKey();

        // Salvando resultado no local selecionado
        cv::imwrite(leaf_disease, image_original);

		return (EXIT_SUCCESS);
	}

} // namespace cld

#endif // CREATE_LEAFS_DISEASES_HPP