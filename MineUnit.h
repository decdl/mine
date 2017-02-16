
#ifndef MINEUNIT_H_
#define MINEUNIT_H_

#include <wx/wx.h>

class MineUnit : public wxControl
{
	private:
		wxButton *button;
		wxStaticText *text;
		int number;
		wxPoint position;
		bool disabled;
		DECLARE_EVENT_TABLE();
	public:
		class PositionType : public wxClientData
		{
			public:
				wxPoint position;
				PositionType(const wxPoint &pos) : position(pos){}
		};
		MineUnit(wxWindow *parent, const wxPoint &pt, const wxSize &sz, const wxPoint &pos);
		inline bool is_mine() {return number == -1;}
		inline void clear() {stop(); number = 0;}
		inline void start() {disabled = false;}
		inline void stop() {disabled = true;}
		void init(int num);
		void OnClick(wxCommandEvent &event);
		void OnSize(wxSizeEvent &event);
};

wxDECLARE_EVENT(EVENT_MINE, wxCommandEvent);

#endif

