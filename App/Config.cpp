#include "Includes.h"
#include "Config.h"

#include <wx/file.h>

Config::Config(wxApp *app)
{
    this->app = app;
    this->id = 90214391;

    wxConfig config(this->app->GetAppName());

    config.Read("config_unit",  &this->volumeUnit,   0);
    config.Read("config_flow",  &this->valveMaxFlow, 0);
    config.Read("config_maxt1", &this->tank1MaxVol,  0);
    config.Read("config_maxt2", &this->tank2MaxVol,  0);
    config.Read("config_maxt3", &this->tank3MaxVol,  0);
    config.Read("config_c1",    &this->tank1Color,   wxNullColour);
    config.Read("config_c2",    &this->tank2Color,   wxNullColour);
}

void Config::Save()
{
    wxConfig config(this->app->GetAppName());

    config.Write("config_unit",  this->volumeUnit);
    config.Write("config_flow",  this->valveMaxFlow);
    config.Write("config_maxt1", this->tank1MaxVol);
    config.Write("config_maxt2", this->tank2MaxVol);
    config.Write("config_maxt3", this->tank3MaxVol);
    config.Write("config_c1",    this->tank1Color);
    config.Write("config_c2",    this->tank2Color);

    config.Flush();
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
