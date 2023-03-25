/**

    @file      Axys.h
    @brief     
    @details   ~
    @author    Dmitrii
    @date      19.03.2023
    @copyright © Dmitrii, 2023. All right reserved.

**/

#ifndef AXYS_H__

#define  AXYS_H__

#include "Canvas_console.h"  
#include "Point.h"
#include "Ray.h"
#include "Matrix.h"
#include "Canvas_xy.h"

/**

    @class   Axys
    @brief   
    @details ~

**/
class Axys : public Canvas_xy
{

public:

 /**
     @brief 
 **/
	void remove();


 /**
     @brief 
 **/
	void render_matrix() override;


 /**
     @brief 
 **/
	void print() const override;



private:
	void calculate_matrix() override;
	Coordinate ORIGIN_;

	std::string outfile_adress = "Axys_out.txt";

	void moving_points_from_ray_to_matrix();
};

#endif //!  AXYS_H__


