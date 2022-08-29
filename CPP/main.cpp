#include <iostream>
#include <string.h>
#include <math.h>
#include <fstream>

using namespace std;

 int wickets=0,balls;
 int count=0;
 float overs;

 class kaad{
    public:
        char batname[20];
        char dismissal[20];
        int score,sixes,fours,bulls;
        int flag,batnum;

        kaad(char ch[20])
        {
            strcpy(batname,ch);
            score=0;sixes=0;fours=0;
            flag=1;bulls=0;
            this->batnum=count;
        }
        kaad *next;
        kaad *STRO(kaad *bat);
        kaad *STRIKEROTATE(kaad *bat);
 };

 class maad{
    public:
    char bowlname[20];
    int score,bnum,wickets;
    float ovars;
    maad(char ch[20]){
        strcpy(bowlname,ch);
        score=0;bnum=0;
        ovars=0;wickets=0;
        }
    maad *next;
};

 class team
 {
    public:
    int score;
    char teamname[20];
    team *next;
    team(char teamname[20]){
        strcpy(this->teamname,teamname);
        score=0;
    }
  team *TOSSTIME(team *taam);
};


  void SCORECARD(kaad *bat,maad *bowl,team *taam);
  void FINALSHEET(kaad *bat, maad *bowl,team *taam);
  kaad *COUNTER(kaad *bat,maad *bowl,team *taam,int runs);
  void INCREM(kaad *bat,maad *bowl,team *taam,int runs);
  void FILEPRINT(ofstream& fout,team *taam,kaad* bat, maad *bowl);
  kaad *INSBAT(kaad *bat,char ch[20]);
  maad *INSBOWL(maad *bowl,char ch[20]);
  team *INSTEAM(team *taam,char ch[20]);


int main()
{
    kaad *bat=NULL;     maad *bowl=NULL;
    kaad *temp1;        maad *temp2;
    team *taam=NULL;
    char venue[20],ch[20],runs;
    float temp;
    int bnum,flag=0;

    cout<<"\t\t\t\t\t| CRICKET SCORECARD |\n";
    cout<<"\n\tTeam 1:\t";
    cin>>ch;
    taam=INSTEAM(taam,ch);
    cout<<"\n\tTeam 2:\t";
    cin>>ch;
    taam=INSTEAM(taam,ch);
    cout<<"\n\tVenue of the Match:\t";
    cin>>venue;

    taam=taam->TOSSTIME(taam);

    cout<<"Enter the number of overs \n";
    cin>>overs;
    temp=overs;


    cout<<"-------------------------------------------------------------------------------\n\n";
    cout<<"                   "<<taam->teamname<<"    vs   "<< taam->next->teamname;
    cout<<"                   \n\tVENUE: "<< venue;
    cout<<"\n-------------------------------------------------------------------------------\n\n";

    while(flag<2)
{
        cout<<"\tBatter 1:\t";
        cin>>ch;
        bat=INSBAT(bat,ch);

        cout<<"\n\tBatter 2:\t";
        cin>>ch;
        bat=INSBAT(bat,ch);

        bat=bat->STRIKEROTATE(bat);

        overs=0;wickets=0;
        balls=1;


            while(overs<temp && wickets<10)
          {

                if(bowl==NULL)
                {
                    cout<<"\n\tEnter the number of Bowler:";
                    cin>>bnum;

                    cout<<"\n\t\tEnter the name of new Bowler 1:";
                    cin>>ch;
                    bowl=INSBOWL(bowl,ch);
                    bowl->bnum=bnum;
                    bowl->ovars=0;bowl->wickets=0;
                }
                else
                {
                    cout<<"\n\tEnter the number of Bowler:";
                    cin>>bnum;

                    temp2=bowl;
                    while(temp2->next->bnum!=bnum && temp2->next!=bowl)
                        temp2=temp2->next;
                    if(temp2->next->bnum==bnum)
                        bowl=temp2->next;
                    else
                    {
                        cout<<"\n\tEnter the name of new Bowler "<<bnum<<":";
                        cin>>ch;
                        bowl=INSBOWL(bowl,ch);
                        bowl->bnum=bnum;
                    }
                }

                        while(balls<=6 && wickets<10)
                        {
                            SCORECARD(bat,bowl,taam);

                            cout<<"\n \tRuns scored in this ball by batter =\t";
                            cin>>runs;

                            bat=COUNTER(bat,bowl,taam,runs);
                        }
                    if(balls>6 && wickets<10)
                {
                    cout<<"\n\n...........................Over Up......................\n\n";
                    overs=round(overs+0.1);
                    bowl->ovars=bowl->ovars+0.4;

                    SCORECARD(bat,bowl,taam);

                    balls=1;
                    bat=bat->STRIKEROTATE(bat);
                }
        }
    temp1=bat;
    while(temp1->next!=bat)
    {
        if(temp1->flag==1)
        {
            strcpy(temp1->dismissal,"NOT-OUT");
        }
            temp1=temp1->next;
    }
    if(temp1->flag==1)
        strcpy(temp1->dismissal,"NOT-OUT");

        cout<<"\n"<<count;
    FINALSHEET(bat,bowl,taam);

    {
        ofstream fout;
        fout.open("Scoresheet",ios::app);
        FILEPRINT(fout,taam,bat,bowl);
        fout.close();
    }


    flag++;

        if(flag<2)
        {
            cout<<"\n\n\t\t\t\t|"<<taam->next->teamname<<" Batting|\n\n";
            taam=taam->next;

        bat=NULL;bowl=NULL;
	    count=0;

        }

}
 return 0;
}


kaad *INSBAT(kaad *bat,char ch[20])
{
    kaad *newnode= new kaad(ch);
    count++;
    if(bat==NULL)
        bat=newnode;
    else
    {
        newnode->next=bat->next;
    }
        bat->next=newnode;
        return newnode;
}

 team *INSTEAM(team *taam,char ch[20])
 {
     team *newnode=new team(ch);
     if(taam==NULL)
        taam=newnode;
     else
     {
        newnode->next=taam->next;
     }
    taam->next=newnode;
    return taam;
 }

maad *INSBOWL(maad *bowl,char ch[20])
{
    maad *newnode= new maad(ch);
    if(bowl==NULL)
        bowl=newnode;
    else
    {
        newnode->next=bowl->next;
    }
   bowl->next=newnode;
        return newnode;
}

 team* team::TOSSTIME(team *taam)
{
    int trick,toss;
        cout<<"\nWho won the Toss ?\n";
    cout<<"1:"<<taam->teamname<<"\t or\t 2:"<<taam->next->teamname<<"\n";
    cin>>trick;

    switch(trick)
    {
        case 1: cout<<taam->teamname<<" Won the toss !!\n";
                cout<<"1:BAT \t 2:BOWL\n";
                cin>>toss;
                    cout<<"-------------------------------------------------------------------------------\n\n";
                switch(toss)
                {
                    case 1: cout<<"\t\t"<<taam->teamname<<" opted to BAT first\n";
                            cout<<"-------------------------------------------------------------------------------\n\n";
                            break;
                    case 2: cout<<"\t\t"<<taam->teamname<<" opted to BOWL first\n";
                            cout<<"-------------------------------------------------------------------------------\n\n";
                            taam=taam->next;
                            break;
                }
                break;
        case 2: cout<<taam->next->teamname<<" Won the toss !!\n";
                cout<<"1:BAT \t 2:BOWL\n";
                cin>>toss;
                    cout<<"-------------------------------------------------------------------------------\n\n";
                switch(toss)
                {
                    case 1: cout<<"\t\t"<<taam->next->teamname<<" opted to BAT first\n";
                            taam=taam->next;
                            break;
                    case 2: cout<<"\t\t"<<taam->next->teamname<<" opted to BOWL first\n";
                            break;
                }
                break;
    }
    return taam;
}

void SCORECARD(kaad *bat,maad *bowl,team *taam)
{
            kaad *temp=bat->next;
            cout<<"\n-------------------------------------------------------------------------------\n\n";

            cout<<taam->teamname<<"-"<<taam->score<<"/"<<wickets<<"\n\n";
            cout<<"Overs="<<overs<<"\n\n";

            cout<<bat->batname<<"-"<<bat->score<<"("<<bat->bulls<<")\t\t ";
            while(temp->flag!=1 && temp!=bat)
                temp=temp->next;
            cout<<temp->batname<<"-"<<temp->score<<"("<<temp->bulls<<")\t\t ";
            cout<<bowl->bowlname<<"-"<<bowl->score<<"/"<<bowl->wickets<<"("<<bowl->ovars<<")\n";

        cout<<"-------------------------------------------------------------------------------\n\n";
}

 void  FINALSHEET(kaad *bat, maad *bowl,team *taam)
{
        int kid=0;
        kaad *temp1;   temp1=bat->next;
        maad *temp2;   temp2=bowl->next;

        cout<<"-----------------------------------------END OF BATTING-------------------------------------------------------\n\n";

    cout<<"......................................"<<taam->teamname<<" VS "<<taam->next->teamname<<" ..............................................................\n\n";
    cout<<"\t\t\t\t| BATTING TEAM - "<<taam->teamname<<"  |\n\n";

        cout<<"\tBATTER\t\tSCORE\t\t HOW OUT \t\t\t 4's\t 6's \n";
        cout<<"-----------------------------------------------------------------------------------------------------\n";
        cout<<"-----------------------------------------------------------------------------------------------------\n";
    while(kid<count)
        {
            if(temp1->batnum==kid)
            {
                cout<<"\n\t "<<temp1->batname<<"\t\t "<<temp1->score<<"\t\t "<<temp1->dismissal<<"\t\t\t "<<temp1->fours<<"\t "<<temp1->sixes<<"\n";
                cout<<"-----------------------------------------------------------------------------------------------------\n";
                temp1=temp1->next;
                kid++;
            }
            else
                temp1=temp1->next;
        }

            cout<<"------------------------------------------------------------------------------------------------------\n\n";
            cout<<"\t\t\t\t| BOWLING TEAM - "<<taam->next->teamname<<"  |\n\n";

        cout<<"\tNo.\t BOWLER \t\t\tFIGURES\t\tOVERS  \n";
        cout<<"-----------------------------------------------------------------------------------------------------\n";
        cout<<"-----------------------------------------------------------------------------------------------------\n";
    while(temp2!=bowl)
 {
        cout<<"\n\t "<<temp2->bnum<<"\t "<<temp2->bowlname<<"\t\t\t "<<temp2->score<<"/"<<temp2->wickets<<"\t\t "<<temp2->ovars<<" \n";
        cout<<"-----------------------------------------------------------------------------------------------------\n";
        temp2=temp2->next;
 }
        cout<<"\n\t "<<temp2->bnum<<"\t "<<temp2->bowlname<<"\t\t\t "<<temp2->score<<"/"<<temp2->wickets<<"\t\t "<<temp2->ovars<<" \n";
        cout<<"-----------------------------------------------------------------------------------------------------\n";

cout<<"\n\t\t"<<taam->teamname<<" - "<<taam->score<<"/"<<wickets<<"\n";
cout<<"\t\tOVERS="<<overs<<"\n";
 }

void FILEPRINT(ofstream& fout,team *taam,kaad* bat, maad *bowl)
{
        int kid=0;
        kaad *temp1;   temp1=bat->next;
        maad *temp2;   temp2=bowl->next;
        fout<<"-----------------------------------------END OF BATTING-------------------------------------------------------\n\n";

    fout<<"......................................"<<taam->teamname<<" VS "<<taam->next->teamname<<" ..............................................................\n\n";
    fout<<"\t\t\t\t| BATTING TEAM - "<<taam->teamname<<"  |\n\n";

        fout<<"\tBATTER\t\tSCORE\t\t HOW OUT \t\t\t 4's\t 6's \n";
        fout<<"-----------------------------------------------------------------------------------------------------\n";
        fout<<"-----------------------------------------------------------------------------------------------------\n";
    while(kid<count)
        {
            if(temp1->batnum==kid)
            {
                fout<<"\n\t "<<temp1->batname<<"\t\t "<<temp1->score<<"\t\t "<<temp1->dismissal<<"\t\t\t "<<temp1->fours<<"\t "<<temp1->sixes<<"\n";
                fout<<"-----------------------------------------------------------------------------------------------------\n";
                temp1=temp1->next;
                kid++;
            }
            else
                temp1=temp1->next;
        }

            fout<<"-----------------------------------------------------------------------------------------------------\n\n";
            fout<<"\t\t\t\t| BOWLING TEAM - "<<taam->next->teamname<<"  |\n\n";

        fout<<"\tNo.\t BOWLER \t\t\tFIGURES\t\tOVERS  \n";
        fout<<"-----------------------------------------------------------------------------------------------------\n";
        fout<<"-----------------------------------------------------------------------------------------------------\n";
    while(temp2!=bowl)
 {
        fout<<"\n\t "<<temp2->bnum<<"\t "<<temp2->bowlname<<"\t\t\t "<<temp2->score<<"/"<<temp2->wickets<<"\t\t "<<temp2->ovars<<" \n";
        fout<<"-----------------------------------------------------------------------------------------------------\n";
        temp2=temp2->next;
 }
        fout<<"\n\t "<<temp2->bnum<<"\t "<<temp2->bowlname<<"\t\t\t "<<temp2->score<<"/"<<temp2->wickets<<"\t\t "<<temp2->ovars<<" \n";
        fout<<"-----------------------------------------------------------------------------------------------------\n";

fout<<"\n\t\t"<<taam->teamname<<" - "<<taam->score<<"/"<<wickets<<"\n";
fout<<"\t\tOVERS="<<overs<<"\n";

}

 kaad* kaad :: STRIKEROTATE(kaad *bat)
 {
     kaad *temp=bat->next;
     while(temp->flag!=1)
        temp=temp->next;
     bat=temp;
     return bat;
 }

 kaad* kaad :: STRO(kaad *bat)
    {
        char ch[20];
        if(bat->flag==0)
                {
                    cout<<"\n\tEnter the new Batter Name\n";
                    cin>>ch;
                    bat=INSBAT(bat,ch);
                }
                return bat;
    }

     void INCREM(kaad *bat,maad *bowl,team *taam,int runs)
    {
        bat->score=bat->score+runs;
        bowl->score=bowl->score+runs;
        taam->score=taam->score+runs;
        bowl->ovars=bowl->ovars+0.1;
        overs=overs+0.1;
        bat->bulls++;
        balls++;
    }


 kaad* COUNTER(kaad *bat,maad *bowl,team *taam,int runs)
{
int add=0,add1=0,out;
char sr[5],fielder[20];

 switch(runs)
        {
          case '1': INCREM(bat,bowl,taam,1);
                    bat=bat->STRIKEROTATE(bat);
                    break;

          case '2': INCREM(bat,bowl,taam,2);
                    break;

          case '3': INCREM(bat,bowl,taam,3);
                    bat=bat->STRIKEROTATE(bat);
                    break;

          case '4': INCREM(bat,bowl,taam,4);
                    bat->fours++;
                    break;

          case '5': INCREM(bat,bowl,taam,5);
                    bat=bat->STRIKEROTATE(bat);
                    break;

          case '6': INCREM(bat,bowl,taam,6);
                    bat->sixes++;
                    break;

          case 'o' :
          case 'O' : cout<<"\n\t\t....."<<bat->batname<<" OUT..!!!!\n\n";
                    bat->bulls++;
                    bowl->ovars=bowl->ovars+0.1;
                    overs=overs+0.1;
                    cout<<"\n 1: Bowled\n 2: Catch\n 3: Run-out\n 4: Stumps\n";
                    cout<<"Select the dismissal\n";
                    cin>>out;
                    switch(out)
                    {
                        case 1: cout<<"-------------------------------------------------\n";
                                cout<<"\n\t\t"<<bat->batname<<"-"<<bat->score<<"("<<bat->bulls<<")\n\t\tB."<<bowl->bowlname<<"\n";
                                cout<<"-------------------------------------------------\n";
                                strcpy(bat->dismissal,"B.");
                                strcat(bat->dismissal,bowl->bowlname);
                                bowl->wickets++;
                                bat->flag=0;
                                bat=bat->STRO(bat);
                                break;

                        case 2: cout<<"Enter the fielder name\n";
                                cin>>fielder;
                                cout<<"-------------------------------------------------\n";
                                cout<<"\n\t\t"<<bat->batname<<"-"<<bat->score<<"("<<bat->bulls<<")\n\t\tC."<<fielder<<"\tB."<<bowl->bowlname<<"\n";
                                cout<<"-------------------------------------------------\n";
                                strcpy(bat->dismissal,"C.");
                                strcat(bat->dismissal,fielder);
                                strcat(bat->dismissal,"_B.");
                                strcat(bat->dismissal,bowl->bowlname);
                                bowl->wickets++;
                                bat->flag=0;
                                bat=bat->STRO(bat);
                                cout<<"\nStrike Rotate ?\n Y\t(or)\t N \n";
                                cin>>sr;
                                if(sr[0]=='Y'|| sr[0]=='y')
                                bat=bat->STRIKEROTATE(bat);
                                break;

                        case 3: cout<<"Enter the fielder name\n";
                                cin>>fielder;
                                cout<<"-------------------------------------------------\n";
                                cout<<"\n\t\t"<<bat->batname<<"-"<<bat->score<<"("<<bat->bulls<<")\n\t\tR/O."<<fielder<<"\tB."<<bowl->bowlname<<"\n";
                                cout<<"-------------------------------------------------\n";
                                strcpy(bat->dismissal,"R/O.");
                                strcat(bat->dismissal,fielder);
                                bat->flag=0;
                                bat=bat->STRO(bat);
                                cout<<"\nStike Rotate ?\n Y\t(or)\t N \n";
                                cin>>sr;
                                if(sr[0]=='Y'|| sr[0]=='y')
                                bat=bat->STRIKEROTATE(bat);
                                break;

                        case 4: cout<<"-------------------------------------------------\n";
                                cout<<"\n\t\t"<< bat->batname<<"-"<<bat->score<<"("<<bat->bulls<<")\n\t\tB."<<bowl->bowlname<<"\n";
                                cout<<"-------------------------------------------------\n";
                                strcpy(bat->dismissal,"St.");
                                strcat(bat->dismissal,bowl->bowlname);
                                bowl->wickets++;
                                bat->flag=0;
                                bat=bat->STRO(bat);
                                break;

                    }
                    wickets++;
                    balls++;
                    break;

          case 'w':
          case 'W': cout<<".....WIDE BALL....\n\n";
                    cout<<"Additional runs scored\n";
                    cin>>add;
                    bat->score=bat->score+add;
                    if(add%2!=0)
                    bat=bat->STRIKEROTATE(bat);
                    taam->score=taam->score+add+1;
                    bowl->score=bowl->score+add+1;
                    break;

         case 'n':
         case 'N' : cout<<".....NO BALL.....\n\n";
                    cout<<"......FREE-HITTT.....!!!\n\n";
                    cout<<"Runs scored by bat\n";
                    cin>>add1;
                    bat->score=bat->score+add1;
                    if(add1==6)
                        bat->sixes++;
                    if(add1==4)
                        bat->fours++;
                    cout<<"Runs scored without bat\n";
                    cin>>add;
                   if((add+add1)%2!=0)
                      {
                        bat=bat->STRIKEROTATE(bat);
                      }
                    taam->score=taam->score+add+add1+1;
                    bowl->score=bowl->score+add+add1+1;
                    bowl->ovars=bowl->ovars-0.1;
                    overs=overs-0.1;
                    balls--;
                    break;

           case 'B':
           case 'b': cout<<".....BYCE.....\n\n";
                     cout<<"Runs gained\n\n";
                     cin>>add;
                     if(add%2!=0)
                      {
                        bat=bat->STRIKEROTATE(bat);
                      }
                      bat->bulls++;
                     taam->score=taam->score+add;
                     bowl->score=bowl->score+add;
                     bowl->ovars=bowl->ovars+0.1;
                     overs=overs+0.1;
                     balls++;
                     break;

            case '0': INCREM(bat,bowl,taam,0);
                      break;

            default: cout<<"\n\t\tInvalid Input";
                        break;
    }
    return bat;
}



