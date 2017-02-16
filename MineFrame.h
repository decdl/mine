
#ifndef MINEFRAME_H_
#define MINEFRAME_H_

#include <wx/wx.h>
#include "MineUnit.h"
#include <vector>

class MineFrame : public wxFrame
{
	private:
		int x, y;
		int mines, mines_remaining;
		std::vector<std::vector<MineUnit *>> unit;
		bool unit_created;
		std::vector<wxPoint> pos;
		void Start();
		void Dead();
		void OnResizeMap();
		DECLARE_EVENT_TABLE();
	public:
		MineFrame(int width, int height, int num_mines);
		void OnCreate(wxWindowCreateEvent &event);
		void OnNew(wxCommandEvent &event);
		void OnMine(wxCommandEvent &event);
		void OnSize(wxSizeEvent &event);
};

#endif

