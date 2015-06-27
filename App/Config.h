#ifndef CONFIG_H_
#define CONFIG_H_

class Config
{
private:
    wxApp *app;
    SQLHandler *sql;
    SQLiteHandler *db;
    std::map<std::string, std::string> cnfs;

public:
    int      volumeUnit,
             valveMaxFlow,
             tank1MaxVol,
             tank2MaxVol,
             tank3MaxVol,
             vin1,
             vout1,
             vin2,
             vout2,
             vout3,
             id;

    wxColour tank1Color,
             tank2Color;

    Config(wxApp *app);
    void Save(bool valves = false);
    void Load();

    void SaveValves(int vin1, int vout1, int vin2, int vout2, int vout3);

    bool SaveFile(wxString filePath);
    bool LoadFile(wxString filePath);
};

#endif // CONFIG_H_
