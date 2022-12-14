#include <nada/fs.hpp>
#include <nada/str.hpp>

#include <fstream>
#include <filesystem>

void nada::fs::read_lines(const std::string& pfad, std::vector<std::string>& liste, unsigned min_laenge) {
    std::ifstream in(pfad, std::ios::binary);
    if (in.good()) {
        for (std::string zeile; std::getline(in, zeile);) {
            if (zeile.size() >= min_laenge) {
                nada::str::remove(zeile, '\r'); // Windows workaround
                liste.push_back(zeile);
            }
        }
        //if (liste.empty()) nada::Log::err() << "Keine Elemente in " << pfad << '\n'; //TODO
    }
    //else nada::Log::err() << pfad << " konnte nicht gelesen werden.\n"; //TODO
}

std::vector<std::string> nada::fs::all_files(const std::string& ordner, std::string endung) {
    std::vector<std::string> dateien;
    endung = "." + endung;
    for (const auto& entry : std::filesystem::directory_iterator(ordner)) {
        if (entry.is_regular_file()) {
            const auto& dateiname = entry.path().generic_string();
            if (endung == "." || nada::str::ends_with(dateiname, endung)) dateien.push_back(dateiname);
        }
    }
    return dateien;
}

std::vector<std::string> nada::fs::all_files_recursive(const std::string& folder, std::string extension) {
    std::vector<std::string> dateien;
    extension = "." + extension;
    for (const auto& entry : std::filesystem::recursive_directory_iterator(folder)) {
        if (entry.is_regular_file()) {
            const auto& dateiname = entry.path().generic_string();
            if (extension == "." || nada::str::ends_with(dateiname, extension)) dateien.push_back(dateiname);
        }
    }
    return dateien;
}
