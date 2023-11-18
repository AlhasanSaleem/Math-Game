#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

enum enQuestionLevel { EasyLevel = 1, MediumLevel = 2, HardLevel = 3, MixLevel = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
    float Number1 = 0;
    float Number2 = 0;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionsList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionsLevel;
    enOperationType OpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass = false;
};

int GetRandomNumber(int From, int To)
{
    int RandomNumber = rand() % (To - From + 1) + From;
    return RandomNumber;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions = 0;

    cout << "How Many Questions do you want to answer ? ";
    cin >> NumberOfQuestions;

    while (NumberOfQuestions < 1 || NumberOfQuestions > 10 || cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Number, Enter a valid one : ";
        cin >> NumberOfQuestions;
    }

    return NumberOfQuestions;
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
        system("color 4F");
}

enQuestionLevel ReadQuestionsLevel()
{
    short QuestionsLevel = 0;

    cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
    cin  >>  QuestionsLevel;

    while (QuestionsLevel < 1 || QuestionsLevel > 4 || cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Number, Enter a valid one : ";
        cin >> QuestionsLevel;
    }

    return (enQuestionLevel) QuestionsLevel;
}

enOperationType ReadOperationType()
{
    short OpType = 0;

    cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
    cin >> OpType;

    while (OpType < 1 || OpType > 5 || cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Number, Enter a valid one : ";
        cin >> OpType;
    }

    return (enOperationType) OpType;
}

enOperationType GetRandomOperationType()
{
    return (enOperationType) GetRandomNumber(1, 4);
}

string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "*";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

float SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        if (Number2 == 0)
            cout << "Cannot divide by zero";
        else
            Number1 / Number2;  
    default:
        return Number1 + Number2;
    }
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n"; 
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n"; 
    cout << Quizz.QuestionsList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionsList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionsList[QuestionNumber].OperationType);
    cout << "\n_________" << endl; 
}

float ReadQuestionAnswer()
{
    float Answer = 0.0;
    cin >> Answer;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Number, Enter a valid one : ";
        cin >> Answer;
    }
    
    return Answer;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionsList[QuestionNumber].PlayerAnswer != Quizz.QuestionsList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionsList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "Worng Answer :-( \n";
        cout << "The right answer is: ";
        cout << Quizz.QuestionsList[QuestionNumber].CorrectAnswer;
        cout << "\n";
    }
    else
    {
        Quizz.QuestionsList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;
        cout << "Right Answer :-) \n";
    }
    cout << endl;
    SetScreenColor(Quizz.QuestionsList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionAnswer(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionsList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
        Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
    }
}

stQuestion GenrateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;
    if (QuestionLevel == enQuestionLevel::MixLevel)
    {
        QuestionLevel = (enQuestionLevel) GetRandomNumber(1, 4);
    }

    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionLevel::EasyLevel:
        Question.Number1 = GetRandomNumber(1, 10);
        Question.Number2 = GetRandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case enQuestionLevel::MediumLevel:
        Question.Number1 = GetRandomNumber(10, 50);
        Question.Number2 = GetRandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case enQuestionLevel::HardLevel:
        Question.Number1 = GetRandomNumber(50, 100);
        Question.Number2 = GetRandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
    return Question;
}

void GenrateQuizzQuestions(stQuizz& Quizz)
{
    for (int i = 0; i < Quizz.NumberOfQuestions; i++)
        Quizz.QuestionsList[i] = GenrateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevel[4] = {"Easy", "Medium", "Hard", "Mix"};
    return arrQuestionLevel[QuestionLevel - 1];
}

string GetFinalResultsText(bool Pass)
{
    if (Pass)
        return "PASS :-)";
    else
        return "FAIL :-(";  
}

void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "______________________________\n\n";
    cout << " Final Resutls is       : " << GetFinalResultsText(Quizz.isPass);
    cout << "\n______________________________\n\n";
    cout << "Number of Questions     : " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level         : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "OpType                  : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right Answers : " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl;
    cout << "______________________________\n";
}

void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OpType = ReadOperationType();
    GenrateQuizzQuestions(Quizz);
    AskAndCorrectQuestionAnswer(Quizz);
    PrintQuizzResults(Quizz);
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayMathGame();
        cout << endl << "Do you want to play again? Y/N? "; 
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
    
}

int main()
{
    //Seeds the random number generator in C++, called only once
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}