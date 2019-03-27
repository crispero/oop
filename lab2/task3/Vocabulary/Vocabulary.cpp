#include "Vocabulary.h"
#include "Consts.h"
#include "pch.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>

std::string ReadWordFromStream()
{
	std::string word;
	std::cout << ">";
	getline(std::cin, word);
	return word;
}

void InitVocabulary()
{
	std::ifstream vocabularyFile("Vocabulary.txt");
	while (!vocabularyFile.eof())
	{
		std::string word, translate;
		vocabularyFile >> word;
		vocabularyFile >> translate;
		vocabulary.insert(std::pair<std::string, std::string>(word, translate));
	}
}

bool FindWordInVocabulary(std::string& word)
{
	bool found = false;
	for (auto it = vocabulary.begin(); it != vocabulary.end(); ++it)
	{
		if (it->first == word)
		{
			std::cout << it->second << std::endl;
			found = true;
		}
	}
	return found;
}

bool AddWordToVocabulary(std::string& word)
{
	std::string translate = ReadWordFromStream();
	if (translate.size() == 0)
	{
		std::cout << "Неизвестное слово '" << word << "' проигнорировано." << std::endl;
		return false;
	}
	else
	{
		vocabulary.insert(std::pair<std::string, std::string>(word, translate));
		std::cout << "Слово '" << word << "' сохранено в словаре как '" << translate << "'." << std::endl;
		return true;
	}
}

void SaveChanges(bool& isChanged, Consts& consts)
{
	if (!isChanged)
	{
		std::cout << consts.PRINT_VOCABULARY_WAS_CHANGED;
		std::string userChoice = ReadWordFromStream();
		if (userChoice == "Y" || userChoice == "y")
			std::cout << consts.PRINT_FAREWELL_WORDS;
	}
}

bool HaveUserInteraction()
{
	Consts consts;
	bool isChanged = false;
	std::string word = ReadWordFromStream();
	std::transform(word.begin(), word.end(), word.begin(), (int (*)(int))std::tolower);
	if (word != consts.TYPE_TO_EXIT)
	{
		if (!FindWordInVocabulary(word))
		{
			std::cout << "Неизвестное слово '" << word << "'. Введите перевод или пустую строку для отказа." << std::endl;
			isChanged = AddWordToVocabulary(word);
		}
	}
	else
	{
		SaveChanges(isChanged, consts);
		return false;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	InitVocabulary();
	while (true)
	{
		if (!HaveUserInteraction())
			break;
	}
	return 0;
}
