#include "Exporter.hpp"

#include <App.hpp>

Exporter::Exporter(std::weak_ptr<App> app)
	:	app(app)
{

}

void Exporter::ExportImage(const std::filesystem::path& path, sf::Vector2u resolution)
{
	const auto outputResolution = sf::Vector2u(resolution.x * app.lock()->state.projectSettings.totalSlides, resolution.y);

	sf::RenderTexture texture(outputResolution);

	texture.clear(app.lock()->state.projectSettings.backgroundColor);

	for (const auto& object : app.lock()->GetObjects()) {
		texture.draw(*object);
	}

	texture.display();

	sf::Image image = texture.getTexture().copyToImage();

	std::vector<sf::Image> outputImages;

	std::string extension = path.extension().generic_string();

	if (extension.empty())
		extension = ".png";

	for (int i = 0; i < app.lock()->state.projectSettings.totalSlides; i++) {
		sf::Image newImage = sf::Image(resolution, app.lock()->state.projectSettings.backgroundColor);

		newImage.copy(image, sf::Vector2u(0, 0), sf::IntRect(sf::Vector2i(resolution.x * i, 0), sf::Vector2i(resolution)));

		std::string outputFile;

		outputFile = path.parent_path().generic_string() + "/" + path.stem().generic_string() + "_" + std::to_string(i) + extension;

		if (!newImage.saveToFile(outputFile)) {
			std::cout << "Could not save file: " << outputFile << "!\n";
		}
	}

	//image.resize(resolution);

	/*if (!image.saveToFile(path)) {
		std::cout << "could not save file!" << std::endl;
	}*/
}