
#include "precompile.h"

DECLARE_APP(Mine);
IMPLEMENT_APP(Mine);

bool Mine::OnInit()
{
	MineFrame *frame = new MineFrame(10, 10, 10);
	if (frame == nullptr)
		return false;
	frame->Show();
	return true;
}

