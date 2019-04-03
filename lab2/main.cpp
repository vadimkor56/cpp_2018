#include <iostream>
#include <stack>
#include <cmath>

#include <libxml++/libxml++.h>
#include <iomanip>
#include <fstream>

using namespace std;

struct weather
{
    Glib::ustring lat, lon, temp;

};

class CParser : public xmlpp::SaxParser
{
private:
    weather w_cur, current_info;
    std::stack<Glib::ustring> tags;

public:
    int i = 0;
    double temp = 0;

    CParser(Glib::ustring& lat, Glib::ustring& lon)
    {
        w_cur.lat = lat;
        w_cur.lon = lon;
        w_cur.temp = "0";
    }

    virtual ~CParser() {}

    void print_result()
    {
        double ans = 0;

        ans = temp / i;

        cout << "Weather in current location: " << ans << "°C" << '\n';
    }

protected:
    virtual void on_start_document() override
    {

    }

    virtual void on_end_document() override
    {

    }

    virtual void on_start_element(const Glib::ustring& name,
                                  const AttributeList& properties) override
    {
        tags.push(name);

        if (name == "current")
        {
            current_info.lat.clear();
            current_info.lon.clear();
            current_info.temp.clear();
        }
    }

    virtual void on_end_element(const Glib::ustring& name) override
    {
        tags.pop();

        if (name == "current")
        {
            if (fabs(stod(current_info.lat) - stod(w_cur.lat)) < 10
                && fabs(stod(current_info.lon) - stod(w_cur.lon)) < 10)
            {
                i++;
                temp += stod(current_info.temp);
            }
        }
    }

    virtual void on_characters(const Glib::ustring& chars) override
    {
        if (tags.top() == "lat")
        {
            current_info.lat = chars;
        }
        else if (tags.top() == "lon")
        {
            current_info.lon = chars;
        }
        else if (tags.top() == "temperature")
        {
            current_info.temp = chars;
        }
    }

    virtual void on_comment(const Glib::ustring& text) override
    {

    }

    virtual void on_warning(const Glib::ustring& text) override
    {

    }

    virtual void on_error(const Glib::ustring& text) override
    {

    }

    virtual void on_fatal_error(const Glib::ustring& text) override
    {

    }
};

int main(int argc, char** argv) {
    Glib::ustring filename("weather.xml");
    Glib::ustring lat("50"), lon("40");

    std::locale::global(std::locale(""));

    for (int i = 1; i < argc - 1; ++i)
    {
        Glib::ustring arg = argv[i];
        if (arg == "--data")
            filename = argv[++i];
        else if (arg == "--lat")
            lat = argv[++i];
        else if (arg == "--lon")
            lon = argv[++i];
    }

    cout << lat << " " << lon;
    CParser parser(lat, lon);
    parser.parse_file(filename);

    parser.print_result();
    return 0;
}
