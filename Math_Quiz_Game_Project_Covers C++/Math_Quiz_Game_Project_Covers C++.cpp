#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, MixLevel = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
    int Number1, Number2;
    enOperationType OperationType;
    enQuestionsLevel QuestionsLevel;
    int CorrectAswer;
    int PlayerAswer;
    bool AnswerResult;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionsLevel QuestionsLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRigthtAnswers = 0;
    bool isPass = false;
};

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions = 1;
    do
    {
        cout << "How many Questions do you want to answer (1 to 100)? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1 || NumberOfQuestions > 100);
    return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short QuestionsLevel = 0;
    do
    {
        cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix: ";
        cin >> QuestionsLevel;
    } while (QuestionsLevel < 1 || QuestionsLevel > 4);
    return (enQuestionsLevel)QuestionsLevel;
}

enOperationType ReadOpType()
{
    short OpType = 0;
    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mult, [4] Div, [5] Mix: ";
        cin >> OpType;
    } while (OpType < 1 || OpType > 5);
    return (enOperationType)OpType;
}

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case Add:return "+";
    case Sub:return "-";
    case Mult:return "*";
    case Div:return "/";
    default:return "Mix";
    }
}

enOperationType GetRandomOperationType()
{
    return (enOperationType)RandomNumber(1, 4);
}

string GetQuestionLevelText(enQuestionsLevel QuestionsLevel)
{
    string arrQuestionLevelText[4] = { "Easy","Medium","Hard","Mixed" };
    return arrQuestionLevelText[QuestionsLevel - 1];
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

int SimpleCalculator(int Number1, int Number2, enOperationType Optype)
{
    switch (Optype)
    {
    case Add:return Number1 + Number2;
    case Sub:return Number1 - Number2;
    case Mult:return Number1 * Number2;
    case Div:return (Number2 != 0) ? (Number1 / Number2) : 0;
    default:return Number1 + Number2;
    }
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;
    if (QuestionLevel == MixLevel)
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    if (OpType == MixOp)
        OpType = GetRandomOperationType();
    Question.OperationType = OpType;
    switch (QuestionLevel)
    {
    case EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case MedLevel:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        break;
    case HardLevel:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        break;
    }
    Question.CorrectAswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
    Question.QuestionsLevel = QuestionLevel;
    return Question;
}

void PrintQuestion(stQuestion Question, short QuestionNumber, short TotalQuestions)
{
    cout << "\nQuestion [" << QuestionNumber + 1 << "/" << TotalQuestions << "]\n\n";
    cout << Question.Number1 << endl;
    cout << GetOpTypeSymbol(Question.OperationType) << " " << Question.Number2 << endl;
    cout << "_______\n";
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintQuestion(Quizz.QuestionList[QuestionNumber], QuestionNumber, Quizz.NumberOfQuestions);
        cout << "Your Answer: ";
        cin >> Quizz.QuestionList[QuestionNumber].PlayerAswer;
        if (Quizz.QuestionList[QuestionNumber].PlayerAswer == Quizz.QuestionList[QuestionNumber].CorrectAswer)
        {
            cout << "? Correct!\n";
            Quizz.NumberOfRigthtAnswers++;
            SetScreenColor(true);
        }
        else
        {
            cout << "? Wrong! Correct Answer: " << Quizz.QuestionList[QuestionNumber].CorrectAswer << endl;
            Quizz.NumberOfWrongAnswers++;
            SetScreenColor(false);
        }
    }
    Quizz.isPass = (Quizz.NumberOfRigthtAnswers >= Quizz.NumberOfWrongAnswers);
}

void PrintFinalResult(stQuizz Quizz)
{
    cout << "\n_________________________________________\n";
    cout << "Final Result: " << (Quizz.isPass ? "Pass ??" : "Fail ?") << endl;
    cout << "_________________________________________\n";
    cout << "Questions Level: " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "Operation Type  : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Total Questions : " << Quizz.NumberOfQuestions << endl;
    cout << "Right Answers   : " << Quizz.NumberOfRigthtAnswers << endl;
    cout << "Wrong Answers   : " << Quizz.NumberOfWrongAnswers << endl;
    cout << "_________________________________________\n";
}

void PlayMatchGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOpType();
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
        Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintFinalResult(Quizz);
}

int main()
{
    srand((unsigned)time(NULL));
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayMatchGame();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
    return 0;
}
