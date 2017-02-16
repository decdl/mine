
#include "precompile.h"

BEGIN_EVENT_TABLE(MineFrame, wxFrame)
	EVT_MENU(wxID_NEW, MineFrame::OnNew)
	EVT_WINDOW_CREATE(MineFrame::OnCreate)
	EVT_SIZE(MineFrame::OnSize)
	EVT_COMMAND(wxID_ANY, EVENT_MINE, MineFrame::OnMine)
END_EVENT_TABLE();

static const wxPoint offsets[] = {
	wxPoint(-1,-1), wxPoint( 0,-1), wxPoint(+1,-1),
	wxPoint(-1, 0),                 wxPoint(+1, 0),
	wxPoint(-1,+1), wxPoint( 0,+1), wxPoint(+1,+1)};

MineFrame::MineFrame(int width, int height, int num_mines)
		: wxFrame(nullptr, wxID_ANY, L"Mine Sweeper with wxWidgets",
				wxDefaultPosition, wxDefaultSize,
				wxDEFAULT_FRAME_STYLE),// & ~wxRESIZE_BORDER),
		  x(width), y(height), mines(num_mines), unit_created(false)
{
	wxMenu *menu = new wxMenu;
	menu->Append(wxID_NEW, L"&New Game");
	wxMenuBar *menu_bar = new wxMenuBar;
	menu_bar->Append(menu, L"&File");
	SetMenuBar(menu_bar);
}

inline void swap(wxPoint &x, wxPoint &y)
{
	wxPoint t = y;
	y = x;
	x = t;
}

void MineFrame::OnNew(wxCommandEvent &event)
{
	Start();
}

void MineFrame::Start()
{
	// create random sequence
	static ::std::default_random_engine g(std::chrono::system_clock::now().time_since_epoch().count());
	for (uint16_t i = 0; i < mines; i++)
		swap(pos[i], pos[std::uniform_int_distribution<size_t>(i, x*y-1)(g)]);

	// signal MineUnits
	for (auto &v : unit)
		for (MineUnit *u : v)
			u->clear();

	for (uint16_t i = 0; i < mines; i++)
		unit[pos[i].x][pos[i].y]->init(-1);
	for (uint16_t i = mines; i < x*y; i++)
	{
		int count = 0;
		for (const wxPoint &offset : offsets)
		{
			wxPoint target = pos[i] + offset;
			if (target.x >= 0 && target.x < x && target.y >= 0 && target.y < y)
				if (unit[target.x][target.y]->is_mine())
					count++;
		}
		unit[pos[i].x][pos[i].y]->init(count);
	}

	mines_remaining = x * y;
	for (auto &v : unit)
		for (MineUnit *u : v)
			u->start();
}

void MineFrame::Dead()
{
	for (auto &v : unit)
		for (MineUnit *u : v)
			u->stop();
}

void MineFrame::OnCreate(wxWindowCreateEvent &event)
{
	if (event.GetWindow() == this)
	{
		int unit_length = GetFont().GetPixelSize().y * 1.5;
		SetClientSize(x * unit_length, y * unit_length);
		OnResizeMap();
		unit_created = true;
		Start();
	}
}

void MineFrame::OnSize(wxSizeEvent &event)
{
	if (unit_created)
	{
		int unit_width, unit_height;
		GetClientSize(&unit_width, &unit_height);
		unit_width /= x;
		unit_height /= y;
		for (int i = 0; i < x; i++)
			for (int j = 0; j < x; j++)
				unit[i][j]->SetSize(
						i * unit_width, j * unit_height,
						unit_width, unit_height, 0);
	}
}

void MineFrame::OnResizeMap()
{
	// cleanup previous MineUnits
	for (auto &v : unit)
		for (MineUnit *u : v)
			u->Destroy();
	// create new MineUnits
	int unit_width, unit_height;
	GetClientSize(&unit_width, &unit_height);
	unit_width /= x;
	unit_height /= y;
	unit.resize(x);
	for (int i = 0; i < x; i++)
	{
		unit[i].clear();
		unit[i].reserve(y);
		for (int j = 0; j < y; j++)
			unit[i].push_back(new MineUnit(
					this,
					wxPoint(i * unit_width, j * unit_height),
					wxSize(unit_width, unit_height),
					wxPoint(i, j)));
	}
	pos.resize(x * y);
	decltype(pos)::iterator it = pos.begin();
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
		{
			*it = wxPoint(i, j);
			it++;
		}
}

void MineFrame::OnMine(wxCommandEvent &event)
{
	wxPoint pos = static_cast<MineUnit::PositionType *>(event.GetClientObject())->position;
	if (unit[pos.x][pos.y]->is_mine())
		Dead();
	if (event.GetInt() == 1)
	{
		wxCommandEvent evt_button(wxEVT_BUTTON, wxID_ANY);
		for (const wxPoint &offset : offsets)
		{
			wxPoint target = pos + offset;
			if (target.x >= 0 && target.x < x && target.y >= 0 && target.y < y)
				unit[target.x][target.y]->GetEventHandler()->AddPendingEvent(evt_button);
		}
	}
	if (--mines_remaining == mines)
		Dead();
}
