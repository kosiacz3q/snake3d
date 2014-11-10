#ifndef SRC_HIGHSCOREHANDLER_H_
#define SRC_HIGHSCOREHANDLER_H_

#include<string>
#include<vector>

class Highscore
{
	public:
		Highscore(std::string name, int result)
				: name(name)
		{
			setResult(result);
		}

		Highscore(std::string name, std::string result)
						: name(name), result(result)
		{
		}

		std::string getName();
		std::string getResult();
		void setResult(int result);

	private:
		friend class HighscoreHandler;

		std::string name;
		std::string result;
};

class HighscoreHandler
{
	public:
		HighscoreHandler();
		virtual ~HighscoreHandler();
		void loadAll();
		void saveAll();
		void add(const Highscore newHighscore);
		std::vector<Highscore>& getHighscores();
		std::string getUsername();
		void setUsername(std::string newname);
	private:
		void sort();
		void cut();
		std::vector<Highscore> _highscores;
		std::string _username;
};

#endif /* SRC_HIGHSCOREHANDLER_H_ */
