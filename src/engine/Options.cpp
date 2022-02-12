#include "Options.h"
#include "Paths.h"

#include <cereal/archives/json.hpp>
#include <fstream>
#include <iostream>
#include <jngl/all.hpp>

Options::Options() : filename(getPaths().getConfig() + "options.json") {
	const int BORDER = 50;
	const int dpiFactor = std::max(std::min(
		(jngl::getDesktopWidth() - BORDER) / windowWidth,
		(jngl::getDesktopHeight() - BORDER) / windowHeight
	), 1);
	windowWidth *= dpiFactor;
	windowHeight *= dpiFactor;
	try {
		std::ifstream ifs(filename);
		cereal::JSONInputArchive archive(ifs);
		archive >> cereal::make_nvp("options", *this);
	} catch(std::exception& e) {
		std::cout << "Error loading " << filename << ": " << e.what() << std::endl;
	}
}

void Options::Save() const {
	std::ofstream ofs(filename);
	cereal::JSONOutputArchive archive(ofs);
	archive << cereal::make_nvp("options", *this);
}

Options& getOptions() {
	return *Options::handle();
}
