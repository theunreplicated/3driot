#include "Menu_ID_Counter.h"

//int a = BOOST_PP_SLOT(1); //0
namespace Windows{

	namespace Menu_ID_Counter{

		unsigned int start_with_number = 201;
		inline unsigned int Get_ID(){

			return start_with_number++;//warum 200?
		}

	}
};