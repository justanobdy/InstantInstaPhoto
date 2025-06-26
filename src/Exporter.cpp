#include "Exporter.hpp"

#include <App.hpp>

namespace Export {
	void ExportImage(const std::filesystem::path& path, const std::string& name, const std::string& filetype, const ProjectSettings& settings, const std::vector<std::shared_ptr<Object>>& objects)
	{
		bool found = false;

		for (const auto& type : GetPossibleOutputTypes()) {
			if (type == filetype) {
				found = true;
			}
		}

		if (!found) {
			return;
		}

		const auto outputResolution = sf::Vector2u(settings.imageResolution.x * settings.totalSlides, settings.imageResolution.y);

		sf::RenderTexture texture(outputResolution);

		texture.clear(settings.backgroundColor);

		for (const auto& object : objects) {
			texture.draw(*object);
		}

		texture.display();

		sf::Image image = texture.getTexture().copyToImage();

		std::vector<sf::Image> outputImages;

		for (int i = 0; i < settings.totalSlides; i++) {
			sf::Image newImage = sf::Image(sf::Vector2u(settings.imageResolution), settings.backgroundColor);

			newImage.copy(image, sf::Vector2u(0, 0), sf::IntRect(sf::Vector2i(settings.imageResolution.x * i, 0), sf::Vector2i(settings.imageResolution)));

			std::string outputFile;

			outputFile = path.generic_string() + "/" + name + "_" + std::to_string(i) + filetype;

			if (!newImage.saveToFile(outputFile)) {
				std::cout << "Could not save file: " << outputFile << "!\n";
			}
		}
	}

	std::vector<std::string> GetPossibleOutputTypes()
	{
		// The types of images that SFML can save, as per https://www.sfml-dev.org/documentation/3.0.1/classsf_1_1Image.html#a3e5834cd9862f4dc77ed495b78f67f2d
		return {
			".bmp",
			".png",
			".tga",
			".jpg"
		};
	}
}