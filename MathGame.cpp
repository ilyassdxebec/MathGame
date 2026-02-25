#include <iostream> 
#include<cmath>
#include <cstdlib>    
#include <ctime>    
using namespace std;

enum enOpType { Add = 1, Sub = 2, Mul = 3 , Div = 4 , Mix = 5 };
enum enDifficulty { Easy = 1, Med = 2, Hard = 3 , DiffMix = 4 };

struct stQuestion{

 int Number1;
 int Number2;
 int RightAnswer;
 int PlayerAnswer;
 bool PassQuestion;
  char Operator;
};

struct stQuizz{   

 stQuestion QuestionsList[100];
 enOpType OperationsType;
 enDifficulty Difficulty;
 int NumOfQuestions;
 int NumOfRightQuestions;
 int NumOfWrongQuestions;
 bool Pass;
};

short DecideHowManyQuestions(){

   short questions;
   do{
    cout<<"How many questions you want to answer from 1 to 10 ? : \n";
   cin>>questions;
   cout<<endl;
   }while(questions>10||questions<1);
   return questions;
}

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

void ResetScreen(){
    system("cls");
        system("color 0");
}

enOpType GetOpType(){

 short Operator;
 do{
 cout<<"Please enter OperationType: [1] Add, [2] Sub , [3] Mul , [4] Div , [5] Mix ? \n";
 cin>>Operator;
 }while(Operator>5||Operator<1);
 cout<<endl;
 return (enOpType) Operator;
}

enDifficulty GetDifficulty(){

  short Level;
 do{
 cout<<"Please enter QuestionLevel: [1] Easy, [2] Med , [3] Hard , [4] Mix ? ";
 cin>>Level;
 }while(Level>4||Level<1);
 cout<<endl;
 return (enDifficulty) Level;
}

int DecideQuestionNumbers(enDifficulty Difficulty){

 switch (Difficulty)
 {
 case Easy:
    return RandomNumber(1,30);
    break;
case Med:
    return RandomNumber(30,60);
    break;
case Hard:
    return RandomNumber(60,100);
    break;
case DiffMix:
    return RandomNumber(1,100);
    break;    
 default:
    break;
 }
}

char DecideOperator(enOpType Operator){

   switch (Operator)
   {
   case Add:
    return '+';
    break;
    case Mul:
    return '*';
    break;
    case Sub:
    return '-';
    break;
    case Div:
    return '/';
    break;
    case Mix:
     return DecideOperator((enOpType)RandomNumber(1,4));
   default:
    break;
   }
}

int RightQuestionAnswer(int Number1,int Number2,char Operator){

 switch (Operator)
 {
 case '+':
    return Number1 + Number2;
    break;
 case '-':
    return Number1 - Number2;
    break;
 case '*':
    return Number1*Number2;
    break;
 case '/':
 if(Number2 == 0) Number2 = 1;
     return Number1/Number2;
     break;

 default:
    break;
 }
}

bool CheckPlayerAnswer(int PlayerAnswer,int RightAnswer){
 return PlayerAnswer==RightAnswer;
}

void PrintQuestion(int NumOfQuestions,int QuestionNum,int Number1,int Number2,char Operator){

  cout<<endl<<"Question ["<<QuestionNum<<"/"<<NumOfQuestions<<"]"<<endl;
  cout<<Number1<<endl;
  cout<<Number2<<"\t"<<Operator<<endl;
  cout<<"___________"<<endl;    
}

string PrintPassOrFail(bool Pass){
 if(Pass) return "Pass :-)";
 else return "Fail :(";
}

void DisplayColor( bool Pass){
    if(Pass) system("color AF");
 else system("color 4F"); 
}

void PrintFinalResults(stQuizz Quizz){

 DisplayColor(Quizz.Pass);
 cout<<"\n______________________________"<<endl;
 cout<<"\tFinal Result Is "<<PrintPassOrFail(Quizz.Pass)<<endl;
 cout<<"______________________________";

 cout<<"NumberOfQuestions : "<<Quizz.NumOfQuestions<<endl;
 cout<<"QuestionsLevel : "<<Quizz.Difficulty<<endl;
 cout<<"OpType : "<<DecideOperator(Quizz.OperationsType)<<endl;
 cout<<"Number Of Right Questions : "<<Quizz.NumOfRightQuestions<<endl;
 cout<<"Number Of Wrong Questions : "<<Quizz.NumOfWrongQuestions<<endl;

  cout<<"______________________________"<<endl;

}

void StartGame(){

  int NumOfQuestions,NumOfRightQustions=0,NumOfWrongQuestions=0;
  stQuizz Quizz;

  NumOfQuestions = DecideHowManyQuestions();
  Quizz.NumOfQuestions = NumOfQuestions;
  Quizz.Difficulty = GetDifficulty();
  Quizz.OperationsType = GetOpType();

  for(int i=1;i<=NumOfQuestions;i++){
    Quizz.QuestionsList[i-1].Number1 = DecideQuestionNumbers(Quizz.Difficulty);
    Quizz.QuestionsList[i-1].Number2 = DecideQuestionNumbers(Quizz.Difficulty);
     Quizz.QuestionsList[i-1].Operator =  DecideOperator(Quizz.OperationsType);
    Quizz.QuestionsList[i-1].RightAnswer = RightQuestionAnswer(Quizz.QuestionsList[i-1].Number1,Quizz.QuestionsList[i-1].Number2,Quizz.QuestionsList[i-1].Operator);

    PrintQuestion(NumOfQuestions,i,Quizz.QuestionsList[i-1].Number1,Quizz.QuestionsList[i-1].Number2,Quizz.QuestionsList[i-1].Operator);
    cin>>Quizz.QuestionsList[i-1].PlayerAnswer;

    if(CheckPlayerAnswer(Quizz.QuestionsList[i-1].PlayerAnswer,Quizz.QuestionsList[i-1].RightAnswer))
    {
         cout<<"Right Answer :)";
          system("color AF");
         NumOfRightQustions++;
        }
    else 
    {
        cout<<"Wrong Answer :-("<<endl;
    cout<<"The right answer is : "<<Quizz.QuestionsList[i-1].RightAnswer;
      system("color 4F");
    NumOfWrongQuestions++;
    }
}

  Quizz.NumOfRightQuestions=NumOfRightQustions;
  Quizz.NumOfWrongQuestions=NumOfWrongQuestions;

  if(NumOfRightQustions>=NumOfWrongQuestions){
      Quizz.Pass = true;
  }
  else {
    Quizz.Pass = false;
  }

  PrintFinalResults(Quizz);
} 
 
void PlayMathGame(){

  char Choice;
  do{
    ResetScreen();
    StartGame();
    cout<<"\n do you want to play again (y)/(n)?";
    cin>>Choice;
  }while(Choice=='Y'||Choice=='y');

  system("color 07");
}

int main()
{
    srand((unsigned)time(NULL)); 
    PlayMathGame();
}