#include "Includes.h"
#include "Config.h"

#include <wx/file.h>

Config::Config(wxApp *app)
{
    this->app = app;
    this->id = 90214391;

    this->sql = new SQLHandler();
    this->db  = new SQLiteHandler();

    // Verifica as tags de configuração salvas no banco de dados.
    std::string needed_cnfs[] = {"color_t1", "vol_unit", "max_flow", "max_vol_t1",
                                 "max_vol_t2", "max_vol_t3", "color_t2", "vin1",
                                 "vout1", "vin2", "vout2", "vout3"};
    std::string std_cnfs[] = {"16777216", "0", "0", "0", "0", "0",
                              "16777216", "0", "0", "0", "0", "0"};

    std::map<std::string, int> saved_cnfs;
    this->db->Select(this->sql->Table("configs")->Column("key"));
    for (unsigned int i = 0; i < this->db->rows.size(); i++)
        saved_cnfs[this->db->rows[i]["key"]] = 0;

    for (int i = 0; i < 12; i++)
        if (saved_cnfs.find(needed_cnfs[i]) == saved_cnfs.end())
            this->db->Exec(this->sql->Set("key", needed_cnfs[i])->Set("value", std_cnfs[i])->Insert());

    this->Load();
}

void Config::Load()
{
    this->db->Select(sql->Table("configs"));

    for (unsigned int i = 0; i < this->db->rows.size(); i++)
    {
        this->cnfs[this->db->rows[i]["key"]] = this->db->rows[i]["value"];
    }

    #define GFM(idx, def) ((this->cnfs.find(idx) != this->cnfs.end()) ? atoi(this->cnfs[idx].c_str()) : def)
    #define GFM_UL(idx, val) ((this->cnfs.find(idx) != this->cnfs.end()) ? wxString(this->cnfs[idx]).ToULong(val) : FALSE)

    unsigned long c1 = 16777216, c2 = 16777216;

    GFM_UL("color_t1", &c1);
    GFM_UL("color_t2", &c2);

    this->volumeUnit   = GFM("vol_unit",   0);
    this->valveMaxFlow = GFM("max_flow",   0);
    this->tank1MaxVol  = GFM("max_vol_t1", 0);
    this->tank2MaxVol  = GFM("max_vol_t2", 0);
    this->tank3MaxVol  = GFM("max_vol_t3", 0);
    this->vin1         = GFM("vin1",       0);
    this->vout1        = GFM("vout1",      0);
    this->vin2         = GFM("vin2",       0);
    this->vout2        = GFM("vout2",      0);
    this->vout3        = GFM("vout3",      0);

    if (c1 == 16777216) this->tank1Color = wxNullColour;
    else this->tank1Color.SetRGB(c1);

    if (c2 == 16777216) this->tank2Color = wxNullColour;
    else this->tank2Color.SetRGB(c2);
}

void Config::SaveValves(int vin1, int vout1, int vin2, int vout2, int vout3)
{
    this->vin1  = vin1;
    this->vout1 = vout1;
    this->vin2  = vin2;
    this->vout2 = vout2;
    this->vout3 = vout3;

    this->Save(true);
}

void Config::Save(bool valves)
{
    std::string val = "";

    #define UPD(k, v)\
    this->sql->Table("configs");\
    val = std::string(wxString::Format(wxT("%lu"), v).mb_str());\
    this->sql->Set("key", k)->Set("value", val)->Where("key", k);\
    this->db->Exec(this->sql->Update());

    if (!valves)
    {
        UPD("vol_unit", this->volumeUnit);
        UPD("max_flow", this->valveMaxFlow);
        UPD("max_vol_t1", this->tank1MaxVol);
        UPD("max_vol_t2", this->tank2MaxVol);
        UPD("max_vol_t3", this->tank3MaxVol);
        UPD("color_t1", this->tank1Color.GetRGB());
        UPD("color_t2", this->tank2Color.GetRGB());
    }

    if (valves)
    {
        UPD("vin1", this->vin1);
        UPD("vout1", this->vout1);
        UPD("vin2", this->vin2);
        UPD("vout2", this->vout2);
        UPD("vout3", this->vout3);
    }
}

bool Config::SaveFile(wxString filePath)
{
    wxFile file(filePath, wxFile::write);

    if (!file.IsOpened())
    {
        return false;
    }

    file.Write(&this->id,           sizeof(this->id));
    file.Write(&this->volumeUnit,   sizeof(this->volumeUnit));
    file.Write(&this->valveMaxFlow, sizeof(this->valveMaxFlow));
    file.Write(&this->tank1MaxVol,  sizeof(this->tank1MaxVol));
    file.Write(&this->tank2MaxVol,  sizeof(this->tank2MaxVol));
    file.Write(&this->tank3MaxVol,  sizeof(this->tank3MaxVol));
    file.Write(&this->tank1Color,   sizeof(this->tank1Color));
    file.Write(&this->tank2Color,   sizeof(this->tank2Color));

    file.Close();

    return true;
}

bool Config::LoadFile(wxString filePath)
{
    long fid = 0;

    wxFile file(filePath, wxFile::read);

    file.Read(&fid, sizeof(fid));

    if (!file.IsOpened() || fid != this->id)
    {
        return false;
    }

    file.Read(&this->volumeUnit,   sizeof(this->volumeUnit));
    file.Read(&this->valveMaxFlow, sizeof(this->valveMaxFlow));
    file.Read(&this->tank1MaxVol,  sizeof(this->tank1MaxVol));
    file.Read(&this->tank2MaxVol,  sizeof(this->tank2MaxVol));
    file.Read(&this->tank3MaxVol,  sizeof(this->tank3MaxVol));
    file.Read(&this->tank1Color,   sizeof(this->tank1Color));
    file.Read(&this->tank2Color,   sizeof(this->tank2Color));

    file.Close();

    return true;
}
