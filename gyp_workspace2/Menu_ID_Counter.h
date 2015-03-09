#ifndef INC_MENU_ID_COUNTER_H
#define INC_MENU_ID_COUNTER_H
//#include <boost/preprocessor/slot/counter.hpp> 
//#define BOOST_PP_VALUE 0 //ensure 0 to start
//#include BOOST_PP_ASSIGN_SLOT(1) 
//#define BOOST_PP_VALUE 1 + BOOST_PP_SLOT(1)
//#include BOOST_PP_ASSIGN_SLOT(1) 
//return BOOST_PP_SLOT(1);
namespace Windows{//http://stackoverflow.com/questions/2557009/can-you-make-an-incrementing-compiler-constant

	namespace Menu_ID_Counter{

		extern inline unsigned int Get_ID();

	}
}
#endif