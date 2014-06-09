#include "test_ctrl.h"
cc::cc(Windows::ApplicationWindow*paw){
	aw = paw;
}
void cc::ccs(){
	new Windows::Window({ "edit", "x" }, { 50, 50, 0, 0 }, WS_CHILD | WS_VISIBLE, aw);

}