#pragma once

#include "rapidjson/document.h"
#include "ConfigurationFileModel.h"

class JSONConfigurationFileParser
{
public:
	explicit JSONConfigurationFileParser(const char* configurationFile);
	const ConfigurationFileModel getConfigurationFileModel() const;

private:
	void validateJSONConfigurationFile() const;
	void convertJSONDocumentToConfigurationFileModel() noexcept;

	rapidjson::Document JSONDocument;
	ConfigurationFileModel configurationFileModel;
};
