#include <iostream> 
#include<cmath>
#include <cstdlib>    
#include <ctime>    
using namespace std;

enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 };
enum enDifficulty { Easy = 1, Med = 2, Hard = 3, DiffMix = 4 };

struct stQuestion
{
    enOpType QuestionOpType;
    enDifficulty QuestionDiff;
    int Number1 = 0;
    int Number2 = 0;
    int RightAnswer;
    int PlayerAnswer;
    bool PassQuestion;
};

struct stQuizz
{
    stQuestion QuestionsList[10];
    enOpType OperationsType;
    enDifficulty Difficulty;
    int NumOfQuestions;
    int NumOfRightQuestions = 0;
    int NumOfWrongQuestions = 0;
    bool Pass;
};

short DecideHowManyQuestions()
{
    short questions;
    do {
        cout << "How many questions you want to answer from 1 to 10 ? : \n";
        cin >> questions;
        cout << endl;
    } while (questions > 10 || questions < 1);
    return questions;
}

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

void ResetScreen()
{
    system("cls");
    system("color 0");
}

enOpType GetOpType()
{
    short Operator;
    do {
        cout << "Please enter OperationType: [1] Add, [2] Sub , [3] Mul , [4] Div , [5] Mix ? \n";
        cin >> Operator;
    } while (Operator > 5 || Operator < 1);
    cout << endl;
    return (enOpType)Operator;
}

enDifficulty GetDifficulty()
{
    short Level;
    do {
        cout << "Please enter QuestionLevel: [1] Easy, [2] Med , [3] Hard , [4] Mix ? ";
        cin >> Level;
    } while (Level > 4 || Level < 1);
    cout << endl;
    return (enDifficulty)Level;
}


string PrintPassOrFail(bool Pass)
{
    if (Pass) return "Pass :-)";
    else return "Fail :(";
}

void DisplayColor(bool Pass)
{
    if (Pass) system("color AF");
    else system("color 4F");
}

int SimpleCalculator(int Number1, int Number2, enOpType Operator)
{
    switch (Operator)
    {
    case Add:
        return Number1 + Number2;
    case Div:
        if (Number2 == 0) Number2 = 1;
        return Number1 / Number2;
    case Sub:
        return Number1 - Number2;
    case Mul:
        return Number1 * Number2;
    }
}

stQuestion GenerateQuestion(enDifficulty Difficulty, enOpType OpType)
{
    stQuestion Question;

    if (Difficulty == DiffMix) {
        Difficulty = (enDifficulty)RandomNumber(1, 3);
    }

    if (OpType == Mix) {
        OpType = (enOpType)RandomNumber(1, 4);
    }

    Question.QuestionOpType = OpType;

    switch (Difficulty)
    {
    case Easy:

        Question.Number1 = RandomNumber(0, 20);
        Question.Number2 = RandomNumber(0, 20);
        Question.QuestionDiff = Difficulty;
        Question.RightAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.QuestionOpType);
        return Question;

    case Med:

        Question.Number1 = RandomNumber(30, 60);
        Question.Number2 = RandomNumber(30, 60);
        Question.QuestionDiff = Difficulty;
        Question.RightAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.QuestionOpType);
        return Question;

    case Hard:

        Question.Number1 = RandomNumber(60, 100);
        Question.Number2 = RandomNumber(60, 100);
        Question.QuestionDiff = Difficulty;
        Question.RightAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.QuestionOpType);
        return Question;
    }
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumOfQuestions; QuestionNumber++)
    {
        Quizz.QuestionsList[QuestionNumber] = GenerateQuestion(Quizz.Difficulty, Quizz.OperationsType);
    }
}

string OpTypeSymbol(enOpType OpType)
{
    switch (OpType)
    {
    case Add:
        return "+";
    case Sub:
        return "-";
    case Mul:
        return "*";
    case Div:
        return "/";
    default:
        return "Mix";
    }
}

void PrintQuestion(int QuestionNum, stQuizz Quizz)
{
    cout << endl << "Question [" << QuestionNum + 1 << "/" << Quizz.NumOfQuestions << "]" << endl;
    cout << Quizz.QuestionsList[QuestionNum].Number1 << endl;
    cout << Quizz.QuestionsList[QuestionNum].Number2 << "\t" << OpTypeSymbol(Quizz.QuestionsList[QuestionNum].QuestionOpType) << endl;
    cout << "___________" << endl;
}

void CheckPlayerAnswer(int QuestionNumber, stQuizz& Quizz)
{
    if (Quizz.QuestionsList[QuestionNumber].PlayerAnswer == Quizz.QuestionsList[QuestionNumber].RightAnswer)
    {
        Quizz.QuestionsList[QuestionNumber].PassQuestion = true;
        Quizz.NumOfRightQuestions++;

        cout << endl << "Right Answer :)";
    }
    else
    {
        Quizz.QuestionsList[QuestionNumber].PassQuestion = false;
        Quizz.NumOfWrongQuestions++;

        cout << endl << "Wrong Answer :(" << endl;
        cout << "The right answer is : " << Quizz.QuestionsList[QuestionNumber].RightAnswer;
        cout << endl;
    }

    DisplayColor(Quizz.QuestionsList[QuestionNumber].PassQuestion);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumOfQuestions; QuestionNumber++)
    {
        PrintQuestion(QuestionNumber, Quizz);
        cin >> Quizz.QuestionsList[QuestionNumber].PlayerAnswer;
        CheckPlayerAnswer(QuestionNumber, Quizz);
    }

    Quizz.Pass = (Quizz.NumOfRightQuestions >= Quizz.NumOfWrongQuestions);
}

string PrintDifficulty(enDifficulty Difficulty)
{
    switch (Difficulty)
    {
    case Easy:
        return "Easy";
    case Med:
        return "Medium";
    case Hard:
        return "Hard";
    case DiffMix:
        return "Mix";
    }
}

void PrintFinalResults(stQuizz Quizz)
{
    DisplayColor(Quizz.Pass);
    cout << endl;
    cout << "\n____________________________________________" << endl;
    cout << "\t  Final Result Is " << PrintPassOrFail(Quizz.Pass) << endl;
    cout << "____________________________________________";

    cout << "\n\n\tNumberOfQuestions : " << Quizz.NumOfQuestions << endl;
    cout << "\tQuestionsLevel : " << PrintDifficulty(Quizz.Difficulty) << endl;
    cout << "\tOpType : " << OpTypeSymbol(Quizz.OperationsType) << endl;
    cout << "\tNumber Of Right Questions : " << Quizz.NumOfRightQuestions << endl;
    cout << "\tNumber Of Wrong Questions : " << Quizz.NumOfWrongQuestions << endl;

    cout << "____________________________________________" << endl;
}

void StartGame()
{
    stQuizz Quizz;

    Quizz.NumOfQuestions = DecideHowManyQuestions();
    Quizz.Difficulty = GetDifficulty();
    Quizz.OperationsType = GetOpType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintFinalResults(Quizz);
}

void PlayMathGame()
{
    char Choice;
    do {

        system("color 07");
        ResetScreen();
        StartGame();

        cout << "\n do you want to play again (y)/(n)?";
        cin >> Choice;

    } while (Choice == 'Y' || Choice == 'y');

    system("color 07");
}

int main()
{
    srand((unsigned)time(NULL));
    PlayMathGame();
}