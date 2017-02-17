
#include "prec.h"

BEGIN_EVENT_TABLE(MineUnit, wxControl)
	EVT_BUTTON(wxID_ANY, MineUnit::OnClick)
	EVT_SIZE(MineUnit::OnSize)
END_EVENT_TABLE();

wxDEFINE_EVENT(EVENT_MINE, wxCommandEvent);

MineUnit::MineUnit(wxWindow *parent, const wxPoint &pt, const wxSize &sz, const wxPoint &pos) :
	wxControl(parent, wxID_ANY, pt, sz), number(0), position(pos), disabled(true)
{
	button = new wxButton(this, wxID_ANY, L"", wxPoint(0, 0), sz);
	text = new wxStaticText(this, wxID_STATIC, L"", wxPoint(0, 0), sz, wxALIGN_CENTRE_HORIZONTAL | wxST_NO_AUTORESIZE);
	button->Show(true);
	text->Show(false);
}

void MineUnit::OnClick(wxCommandEvent &event)
{
	if (!disabled)
	{
		disabled = true;
		button->Show(false);
		text->Show(true);
		wxCommandEvent event(EVENT_MINE, GetId());
		PositionType pos(position);
		event.SetClientObject(&pos);
		if (number == 0)
			event.SetInt(1);
		else
			event.SetInt(0);
		GetParent()->ProcessWindowEvent(event);
	}
}

void MineUnit::OnSize(wxSizeEvent &event)
{
	auto size = GetSize();
	button->SetSize(size);
	text->SetSize(size);
}

void MineUnit::init(int num)
{
	number = num;
	button->Show(true);
	text->Show(false);
	if (num == -1)
		text->SetLabelText(L"*");
	else if (num == 0)
		text->SetLabelText(L"");
	else
	{
		std::wostringstream oss;
		oss << num;
		text->SetLabelText(oss.str());
	}
}
