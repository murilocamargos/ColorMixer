#ifndef CONFIG_H_
#define CONFIG_H_

class Config
{
private:
    wxApp *app;

public:
    long     volumeUnit,
             valveMaxFlow,
             tank1MaxVol,
             tank2MaxVol,
             tank3MaxVol,
             id;

    wxColour tank1Color,
             tank2Color;

    Config(wxApp *app);
    void Save();
    bool SaveFile(wxString filePath);
    bool LoadFile(wxString filePath);
};

#endif // CONFIG_H_
