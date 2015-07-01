#include "../../App/Includes.h"

#include "LogScreen.h"
#include <wx/file.h>

#include "../../Controls/DirSelect.h"

BEGIN_EVENT_TABLE(LogScreen, wxDialog)
    EVT_CHOICE(CHOICE_DATE_OPR, LogScreen::OnChoiceOprDate)
    EVT_CHOICE(ALL_CHOICES, LogScreen::OnChoice)
    EVT_COMBOBOX(ALL_COMBO, LogScreen::OnCombo)
    EVT_DATE_CHANGED(ALL_DATE, LogScreen::OnDate)
    EVT_BUTTON(EXPORT, LogScreen::OnExport)
    EVT_CLOSE(LogScreen::OnExit)
END_EVENT_TABLE()

LogScreen::LogScreen( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
    this->db  = new SQLiteHandler();
    this->sql = new SQLHandler();

    #define POP(cmb, tbl, key, val) this->db->Select(this->sql->Table(std::string(tbl))->Column(std::string(key) + " as key")->Column(std::string(val) + " as val"));\
	for (unsigned int i = 0; i < this->db->rows.size(); i++)\
        cmb->Append(this->db->rows[i]["key"] + ". " + wxString::FromUTF8Unchecked(wxString(this->db->rows[i]["val"])));

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* parentBS = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* searchFieldsBS = new wxBoxSizer( wxHORIZONTAL );

    // ===================== FIELD 1 (USERS) ===================== //
	SFULabel = new wxStaticText( this, wxID_ANY, _("User") + ":", wxDefaultPosition, wxDefaultSize, 0 );

    int oprs1[] = {1, 2};
    wxArrayString choices1 = this->sql->GetOpr( oprs1, 2 );
	SFUOperator = new wxChoice( this, ALL_CHOICES, wxDefaultPosition, wxSize( 120,-1 ), choices1, 0 );
	SFUOperator->SetSelection( 0 );

	SFUsers = new wxComboBox( this, ALL_COMBO, wxEmptyString, wxDefaultPosition, wxSize( 120,-1 ), 0, NULL, 0 );
	SFUsers->Append(_("All"));
    POP(SFUsers, "usuarios", "user_id", "nome");
	SFUsers->SetSelection(0);

    wxBoxSizer* SFUsersBS = new wxBoxSizer( wxVERTICAL );
    SFUsersBS->Add( SFULabel, 0, wxALL, 5 );
	SFUsersBS->Add( SFUOperator, 0, wxALL, 5 );
	SFUsersBS->Add( SFUsers, 0, wxALL, 5 );

	searchFieldsBS->Add( SFUsersBS, 1, wxEXPAND, 5 );

    // ===================== CONNECTOR 1 ===================== //
	wxString SFConnector1Choices[] = { _("And"), _("Or") };
	int SFConnector1NChoices = sizeof( SFConnector1Choices ) / sizeof( wxString );
	SFConnector1 = new wxChoice( this, ALL_CHOICES, wxDefaultPosition, wxSize( 50,30 ), SFConnector1NChoices, SFConnector1Choices, 0 );
	SFConnector1->SetSelection( 0 );

	wxBoxSizer* SFConnectorBS1 = new wxBoxSizer( wxVERTICAL );

	SFConnectorBS1->Add( 0, 0, 1, wxEXPAND, 5 );
	SFConnectorBS1->Add( SFConnector1, 0, wxALL, 5 );
	SFConnectorBS1->Add( 0, 0, 1, wxEXPAND, 5 );
	searchFieldsBS->Add( SFConnectorBS1, 1, wxEXPAND, 5 );

    // ===================== FIELD 2 (TYPES) ===================== //
	SFTLabel = new wxStaticText( this, wxID_ANY, _("Type") + ":", wxDefaultPosition, wxDefaultSize, 0 );

	int oprs2[] = {1, 2};
    wxArrayString choices2 = this->sql->GetOpr( oprs2, 2 );
	SFTOperator = new wxChoice( this, ALL_CHOICES, wxDefaultPosition, wxSize( 120,-1 ), choices2, 0 );
	SFTOperator->SetSelection( 0 );

	SFTypes = new wxComboBox( this, ALL_COMBO, wxEmptyString, wxDefaultPosition, wxSize( 120,-1 ), 0, NULL, 0 );
	SFTypes->Append(_("All"));
	POP(SFTypes, "log_desc", "log_id", "descricao");
	SFTypes->SetSelection(0);

    wxBoxSizer* SFTypeBS = new wxBoxSizer( wxVERTICAL );
	SFTypeBS->Add( SFTLabel, 0, wxALL, 5 );
	SFTypeBS->Add( SFTOperator, 0, wxALL, 5 );
	SFTypeBS->Add( SFTypes, 0, wxALL, 5 );

	searchFieldsBS->Add( SFTypeBS, 1, wxEXPAND, 5 );

    // ===================== CONNECTOR 2 ===================== //
	wxBoxSizer* SFConnectorBS2;
	SFConnectorBS2 = new wxBoxSizer( wxVERTICAL );


	SFConnectorBS2->Add( 0, 0, 1, wxEXPAND, 5 );

    //wxArrayString choices = wxArrayString({_("And"), _("Or")});

	wxString SFConnector2Choices[] = { _("And"), _("Or") };
	int SFConnector2NChoices = sizeof( SFConnector2Choices ) / sizeof( wxString );
	SFConnector2 = new wxChoice( this, ALL_CHOICES, wxDefaultPosition, wxSize( 50,30 ), SFConnector2NChoices, SFConnector2Choices, 0 );
	SFConnector2->SetSelection( 0 );
	SFConnectorBS2->Add( SFConnector2, 0, wxALL, 5 );


	SFConnectorBS2->Add( 0, 0, 1, wxEXPAND, 5 );


	searchFieldsBS->Add( SFConnectorBS2, 1, wxEXPAND, 5 );

	// ===================== FIELD 3 (DATE) ===================== //
	wxBoxSizer* SFDateBS;
	SFDateBS = new wxBoxSizer( wxVERTICAL );

	SFDLabel = new wxStaticText( this, wxID_ANY, _("Date") + ":", wxDefaultPosition, wxDefaultSize, 0 );
	SFDLabel->Wrap( -1 );
	SFDateBS->Add( SFDLabel, 0, wxALL, 5 );

	wxString SFDOperatorChoices[] = { _("Any"), "=", "!=", ">", "<", ">=", "<=", _("Between"), _("Not between") };
	int SFDOperatorNChoices = sizeof( SFDOperatorChoices ) / sizeof( wxString );
	SFDOperator = new wxChoice( this, CHOICE_DATE_OPR, wxDefaultPosition, wxSize( 180,-1 ), SFDOperatorNChoices, SFDOperatorChoices, 0 );
	SFDOperator->SetSelection( 0 );
	SFDateBS->Add( SFDOperator, 0, wxALL, 5 );

	wxBoxSizer* SFDateFieldsBS;
	SFDateFieldsBS = new wxBoxSizer( wxHORIZONTAL );

	SFDatePicker1 = new wxDatePickerCtrl( this, ALL_DATE, wxDefaultDateTime, wxDefaultPosition, wxSize( 85,-1 ), wxDP_DEFAULT|wxDP_DROPDOWN );
	SFDatePicker1->Enable( false );
	SFDateFieldsBS->Add( SFDatePicker1, 0, wxALL, 5 );

	SFDatePicker2 = new wxDatePickerCtrl( this, ALL_DATE, wxDefaultDateTime, wxDefaultPosition, wxSize( 85,-1 ), wxDP_DEFAULT|wxDP_DROPDOWN );
	SFDatePicker2->Enable( false );

	SFDateFieldsBS->Add( SFDatePicker2, 0, wxALL, 5 );


	SFDateBS->Add( SFDateFieldsBS, 1, wxEXPAND, 5 );


	searchFieldsBS->Add( SFDateBS, 1, wxEXPAND, 5 );


	parentBS->Add( searchFieldsBS, 1, wxEXPAND, 5 );

	// ===================== FIELD 4 (TABLE) ===================== //
	logsTable = new wxDataViewListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 570,300 ), 0 );

	logsTable->AppendTextColumn(_("User"));
    logsTable->AppendTextColumn(_("Log Type"), wxDATAVIEW_CELL_INERT, 210);
    logsTable->AppendTextColumn(_("Info."), wxDATAVIEW_CELL_INERT, 120);
    logsTable->AppendTextColumn(_("Date"), wxDATAVIEW_CELL_INERT, 110);

    this->Populate(sql->Table("logs as l")
                      ->Join("log_desc as ls", "l.log_id = ls.log_id")
                      ->NaturalJoin("usuarios as u")
                      ->Column("u.nome")
                      ->Column("l.ocorrencia")
                      ->Column("l.descricao as info")
                      ->Column("ls.descricao"));

	parentBS->Add( logsTable, 0, wxALL, 5 );

    wxBoxSizer* btnBS;
	btnBS = new wxBoxSizer( wxHORIZONTAL );
	btnBS->Add( 0, 0, 1, wxEXPAND, 5 );

	btnExport = new wxButton( this, EXPORT, _("Export Log"), wxDefaultPosition, wxSize( -1,30 ), 0 );
	btnBS->Add( btnExport, 0, wxALL, 5 );


	parentBS->Add( btnBS, 1, wxEXPAND, 5 );

	this->SetSizer( parentBS );
	this->Layout();

	this->Centre( wxBOTH );
}

LogScreen::~LogScreen()
{
}

void LogScreen::OnExit(wxCloseEvent& event)
{
    Destroy();
}

void LogScreen::Populate(SQLHandler* sql)
{
    unsigned long date;

    this->logsTable->DeleteAllItems();

    this->db->Select(sql);
    wxVector<wxVariant> data;

    for (unsigned int i = 0; i < this->db->rows.size(); i++)
    {
        wxString(this->db->rows[i]["ocorrencia"]).ToULong(&date);

        data.clear();
        data.push_back(wxVariant(wxString::FromUTF8Unchecked(wxString(this->db->rows[i]["nome"]))));
        data.push_back(wxVariant(wxString::FromUTF8Unchecked(wxString(this->db->rows[i]["descricao"]))));
        data.push_back(wxVariant(wxString::FromUTF8Unchecked(wxString(this->db->rows[i]["info"]))));
        data.push_back(wxVariant(wxDateTime(static_cast<time_t>(date)).FormatISOCombined(' ')));
        this->logsTable->AppendItem(data);
    }
}

void LogScreen::Find()
{
    where USER, TYPE, DATE;

    /////////////////////////////////////////////////////////////
    wxString uid("");
    wxString uopr = this->SFUOperator->GetString(this->SFUOperator->GetSelection());
    if (this->SFUsers->GetSelection() != 0)
    {
        uid = this->SFUsers->GetString(this->SFUsers->GetSelection());
        uid = uid.SubString(0, uid.Find(".") - 1);
    }

    USER.col  = "u.user_id";
    USER.opr  = this->sql->GetOpr(uopr);
    USER.val1 = uid;
    USER.val2 = "";
    USER.con  = "AND";
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    wxString lid("");
    wxString lopr = this->SFTOperator->GetString(this->SFTOperator->GetSelection());
    wxString lcon = (this->SFConnector1->GetSelection() == 0) ? "AND" : "OR";
    if (this->SFTypes->GetSelection() != 0)
    {
        lid = this->SFTypes->GetString(this->SFTypes->GetSelection());
        lid = lid.SubString(0, lid.Find(".") - 1);
    }

    TYPE.col  = "l.log_id";
    TYPE.opr  = this->sql->GetOpr(lopr);
    TYPE.val1 = lid;
    TYPE.val2 = "";
    TYPE.con  = lcon;
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    wxString dopr = this->SFDOperator->GetString(this->SFDOperator->GetSelection());
    wxDateTime d1 = this->SFDatePicker1->GetValue(), d2 = this->SFDatePicker2->GetValue();

    DATE = this->sql->GetDateWhere(this->sql->GetOpr(dopr), d1, d2);

    wxString dcon = (this->SFConnector2->GetSelection() == 0) ? "AND" : "OR";

    DATE.col = "ocorrencia";
    DATE.con = dcon;
    /////////////////////////////////////////////////////////////

    sql->Table("logs as l")
       ->Join("log_desc as ls", "l.log_id = ls.log_id")
       ->NaturalJoin("usuarios as u")
       ->Column("u.nome")
       ->Column("l.ocorrencia")
       ->Column("l.descricao as info")
       ->Column("ls.descricao")
       ->Where(USER)
       ->Where(TYPE)
       ->Where(DATE);

    this->Populate(sql);
}

void LogScreen::OnChoiceOprDate(wxCommandEvent& event)
{
    this->Find();
    int opr = this->sql->GetOpr(this->SFDOperator->GetString(this->SFDOperator->GetSelection()));
    this->SFDatePicker1->Enable(opr > 0);
    this->SFDatePicker2->Enable((opr == 7 || opr == 8));
}

void LogScreen::OnChoice(wxCommandEvent& event)
{
    this->Find();
}

void LogScreen::OnCombo(wxCommandEvent& event)
{
    this->Find();
}

void LogScreen::OnDate(wxDateEvent& event)
{
    this->Find();
}

void LogScreen::OnExport(wxCommandEvent& event)
{
    wxString path = DirSelect::PathDlg();

    if (path == "")
    {
        wxMessageDialog dlg(this, _("You must select a path to save the file!"), _("Error"), wxICON_WARNING);
        dlg.ShowModal();
    }
    else
    {
        wxFile file(path + "/ColorMixer.log", wxFile::write);

        if (!file.IsOpened())
        {
            wxMessageDialog dlg(this, _("We couldn't create the file in this directory!"), _("Error"), wxICON_WARNING);
            dlg.ShowModal();
        }
        else
        {
            for (unsigned int i = 0; i < this->logsTable->GetItemCount(); i++)
            {
                wxString row("");
                row += "[" + this->logsTable->GetTextValue(i, 3) + "] ";
                row += "[" + this->logsTable->GetTextValue(i, 0) + "] ";
                row += "[" + this->logsTable->GetTextValue(i, 1) + "] ";
                row += this->logsTable->GetTextValue(i, 2) + "\r\n";
                file.Write(row);
            }

            wxMessageDialog dlg(this, _("The log file was saved!"), _("Success"), wxICON_INFORMATION);
            dlg.ShowModal();
        }

        file.Close();
    }
}
