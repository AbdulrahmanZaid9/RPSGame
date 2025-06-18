#include<iostream>
using namespace std;

enum enGameChoices { Rock = 1, Paper = 2, Scissors = 3 };
enum enwinner { Player1 = 1, Computer = 2, Draw = 3 };
struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoices Playe1Choice;
	enGameChoices ComputerChoice;
	enwinner Winner;
	string WinnerName = "";
};
struct stGameResult
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enwinner GameWinner;
	string WinnerName = "";
};
string Tabs(short NumberOfTaps)
{
	string t = "";
	for (int i = 1; i < NumberOfTaps; i++)
	{
		t += "\t";
		cout << t;
	}
	return t;
}
void ShowGameOverScreen()
{
	cout << Tabs(2) << "_____________________________________________________________________\n\n" << endl;
	cout << Tabs(2) << "                            +++Game Over+++                          \n\n" << endl;
	cout << Tabs(2) << "_____________________________________________________________________\n\n" << endl;
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}
short HowManyRounds()
{
	short Rounds;
	do
	{
		cout << "How Many Round 1 To 10?\n";
		cin >> Rounds;
	} while (Rounds < 1 || Rounds > 10);

	return Rounds;
}
enGameChoices ReadPlayer1Choice()
{
	short Choice;
	do
	{
		cout << "\nYour Choice: [1]:Rock, [2]:Paper, [3]:Scissors? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enGameChoices)Choice;
}
enGameChoices GetComputerChoice()
{
	return (enGameChoices)RandomNumber(1, 3);
}
enwinner WhoWinTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.ComputerChoice == RoundInfo.Playe1Choice)
	{
		return enwinner::Draw;
	}

	switch (RoundInfo.Playe1Choice)
	{
	case enGameChoices::Rock:
		if (RoundInfo.ComputerChoice == enGameChoices::Paper)
		{
			return enwinner::Computer;
		}
		break;
	case enGameChoices::Paper:
		if (RoundInfo.ComputerChoice == enGameChoices::Scissors)
		{
			return enwinner::Computer;
		}
		break;
	case enGameChoices::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoices::Rock)
		{
			return enwinner::Computer;
		}
		break;
	}
	return enwinner::Player1;
}
string WinnerName(enwinner Winner)
{
	string WinnerNames[3] = { "Player1","Computer","Draw" };
	return WinnerNames[Winner - 1];
}
string ChoiceName(enGameChoices Choice)
{
	string Names[3] = { "Rock","Paper","Scissors" };
	return Names[Choice - 1];
}
void SetWinnerScreenColor(enwinner Winner)
{
	switch (Winner)
	{
	case enwinner::Player1:
		system("color 2F");
		break;
	case enwinner::Computer:
		system("color 4F");
		cout << "\a" << endl;
		break;
	default:
		system("color 6F");
	}
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.Playe1Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "_________________________________________\n" << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
}
enwinner WhoWinTheGame(short PlayerWinTimes, short ComputerWinTimes)
{
	if (PlayerWinTimes > ComputerWinTimes)
	{
		return enwinner::Player1;
	}
	else if (ComputerWinTimes > PlayerWinTimes)
	{
		return enwinner::Computer;
	}
	else
	{
		return enwinner::Draw;
	}

}
stGameResult FillGameResult(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResult GameReuslt;
	GameReuslt.GameRounds = GameRounds;
	GameReuslt.ComputerWinTimes = ComputerWinTimes;
	GameReuslt.Player1WinTimes = Player1WinTimes;
	GameReuslt.DrawTimes = DrawTimes;
	GameReuslt.GameWinner = WhoWinTheGame(Player1WinTimes, ComputerWinTimes);
	GameReuslt.WinnerName = WinnerName(GameReuslt.GameWinner);

	return GameReuslt;
}
stGameResult PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (int GameRounds = 1; GameRounds <= HowManyRounds; GameRounds++)
	{
		cout << "\n Rounds [" << GameRounds << "] Begin: \n";
		RoundInfo.RoundNumber = GameRounds;
		RoundInfo.Playe1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWinTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);


		switch (RoundInfo.Winner)
		{
		case enwinner::Player1:
			player1WinTimes++;
			break;

		case enwinner::Computer:
			ComputerWinTimes++;
			break;
		default:
			DrawTimes++;
		}
		PrintRoundResults(RoundInfo);
	}
	return FillGameResult(HowManyRounds, player1WinTimes, ComputerWinTimes, DrawTimes);
}
void ShowFinalGameResult(stGameResult GameReuslt)
{
	cout << Tabs(2) << "_____________________________[Game Results]__________________________\n\n" << endl;
	cout << Tabs(2) << "Game Rounds       : " << GameReuslt.GameRounds << endl;
	cout << Tabs(2) << "Player Won Time   : " << GameReuslt.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer Won Time : " << GameReuslt.ComputerWinTimes << endl;
	cout << Tabs(2) << "Draw Times        : " << GameReuslt.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner      : [" << GameReuslt.WinnerName << "]" << endl;

	SetWinnerScreenColor(GameReuslt.GameWinner);
}
void StartGame()
{
	char PlayAgain;
	do
	{
		ResetScreen();
		stGameResult GameResult = PlayGame(HowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResult(GameResult);
		cout << "\n";
		cout << "Do You Want To Play Again ? \n";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}