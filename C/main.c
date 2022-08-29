#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

 int wickets=0,balls;
 int batnum=0,count=0;
 float overs;

 typedef struct kaad{
 char batname[20];
 int score,sixes,batnum;
 int fours,balls,flag;
 char dismissal[20];
 struct kaad *next;
 }batter;

 typedef struct maad{
 char bowlname[20];
 int score;
 int bnum;
 float ovars;
 int wickets;
 struct maad *next;
}bowler;

struct team{
 char teamname[20];
 int score;
}team1,team2;

 batter *INSBAT(batter *bat,char ch[20]);
 bowler *INSBOWL(bowler *bowl,char ch[20]);
 void TOSSTIME(char p[20],char q[20]);
 void SCORECARD(batter *bat,bowler *bowl);
 void FINALSHEET(batter *bat, bowler *bowl);
 void FILEPRINT(FILE *fp,batter* bat, bowler *bowl);
 batter *STRIKEROTATE(batter *bat);
 batter *STRO(batter *bat);
 void INCREM(batter *bat,bowler *bowl,int runs);
 batter *COUNTER(batter *bat,bowler *bowl,int runs);


int main()
{
    batter *bat=NULL;          bowler *bowl=NULL;
    batter *temp1;      	 bowler *temp2;
    char venue[20],ch[20],yell[20],runs;
    float temp;
    int bnum,flag=0;

    printf("\t\t\t\t\t| CRICKET SCORECARD |\n");
    printf("\n\tTeam 1:\t");
    scanf("%s", team1.teamname);
    printf("\n\tTeam 2:\t");
    scanf("%s", team2.teamname);
    printf("\n\tVenue of the Match:\t");
    scanf("%s", venue);
    FILE *fp;


    TOSSTIME(team1.teamname,team2.teamname);

    printf("Enter the number of overs \n");
    scanf("%f", &overs);
    temp=overs;


    printf("-------------------------------------------------------------------------------\n\n");
    printf("                   %s    vs   %s                 \n\n", team1.teamname,team2.teamname);
    printf("                    VENUE: %s                              \n",venue);
    printf("-------------------------------------------------------------------------------\n\n");

    while(flag<2)
{
        printf("\tBatter 1:\t");
        scanf("%s",ch);
        bat=INSBAT(bat,ch);

        printf("\n\tBatter 2:\t");
        scanf("%s",ch);
        bat=INSBAT(bat,ch);

        bat=STRIKEROTATE(bat);

        overs=0;wickets=0;
        balls=1;
        team1.score=0;



            while(overs<temp && wickets<10)
          {

                if(bowl==NULL)
                {
                    printf("\n\tEnter the number of Bowler:");
                    scanf("%d",&bnum);

                    printf("\n\t\tEnter the name of new Bowler 1:");
                    scanf("%s",ch);
                    bowl=INSBOWL(bowl,ch);
                    bowl->bnum=bnum;
                    bowl->ovars=0;bowl->wickets=0;
                }
                else
                {
                    printf("\n\tEnter the number of Bowler:");
                    scanf("%d",&bnum);

                    temp2=bowl;
                    while(temp2->next->bnum!=bnum && temp2->next!=bowl)
                        temp2=temp2->next;
                    if(temp2->next->bnum==bnum)
                        bowl=temp2->next;
                    else
                    {
                        printf("\n\tEnter the name of new Bowler %d:",bnum);
                        scanf("%s",ch);
                        bowl=INSBOWL(bowl,ch);
                        bowl->bnum=bnum;
                    }
                }

                        while(balls<=6 && wickets<10)
                        {
                            SCORECARD(bat,bowl);

                            printf("\n \tRuns scored in this ball by batter =\t");
                            scanf("%c", &runs);

                            bat=COUNTER(bat,bowl,runs);

                        }
                    if(balls>6 && wickets<10)
                {
                    printf("\n\n...........................Over Up....................\n\n");
                    overs=round(overs);
                    bowl->ovars=bowl->ovars+0.4;

                    SCORECARD(bat,bowl);

                    balls=1;
                    bat=STRIKEROTATE(bat);
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
    {
        strcpy(temp1->dismissal,"NOT-OUT");
    }

    FINALSHEET(bat,bowl);

    {
        fp=fopen("Scoresheet","a");

        FILEPRINT(fp,bat,bowl);

        fclose(fp);
    }


    flag++;

        if(flag<2)
        {
            printf("\n\n\t\t\t\t|%s Batting|\n\n",team2.teamname);
            strcpy(yell,team1.teamname);
            strcpy(team1.teamname,team2.teamname);
            strcpy(team2.teamname,yell);


        bat=NULL;bowl=NULL;
	  count=0;batnum=0;

        }

}
 return 0;
}


batter *INSBAT(batter *bat,char ch[20])
{
    batter *newnode;
    newnode=(batter*)malloc(sizeof(batter));
    strcpy(newnode->batname,ch);
    newnode->balls=0;newnode->fours=0;
    newnode->score=0;newnode->sixes=0;
    count++;
    newnode->batnum=batnum+1;
    if(bat==NULL)
    {
        bat=newnode;
    }
    else
    {
        newnode->next=bat->next;
    }
        bat->next=newnode;
        newnode->flag=1;
        batnum++;
        return newnode;
}

bowler *INSBOWL(bowler *bowl,char ch[20])
{
    bowler *newnode;
        newnode=(bowler*)malloc(sizeof(bowler));
        newnode->score=0;newnode->wickets=0;
        newnode->ovars=0;
        strcpy(newnode->bowlname,ch);
    if(bowl==NULL)
        bowl=newnode;
    else
    {
        newnode->next=bowl->next;
    }
   bowl->next=newnode;
        return newnode;
}

void TOSSTIME(char p[20],char q[20])
{
    char yell[20];
    int trick,toss;
        printf("\nWho won the Toss ?\n");
    printf("1:%s\t or\t 2:%s\n", p,q);
    scanf("%d", &trick);

    switch(trick)
    {
        case 1: printf("%s Won the toss !!\n",p);
                printf("1:BAT \t 2:BOWL\n");
                scanf("%d",&toss);
                    printf("-------------------------------------------------------------------------------\n\n");
                switch(toss)
                {
                    case 1: printf("\t\t%s opted to BAT first\n",p);
                    printf("-------------------------------------------------------------------------------\n\n");
                            break;
                    case 2: printf("\t\t%s opted to BOWL first\n",p);
                    printf("-------------------------------------------------------------------------------\n\n");
                            strcpy(yell,p);
                            strcpy(p,q);
                            strcpy(q,yell);
                            break;
                }
                break;
        case 2: printf("%s Won the toss !!\n",q);
                printf("1:BAT \t 2:BOWL\n");
                scanf("%d",&toss);
                    printf("-------------------------------------------------------------------------------\n\n");
                switch(toss)
                {
                    case 1: printf("\t\t%s opted to BAT first\n",q);
                            strcpy(yell,q);
                            strcpy(q,p);
                            strcpy(p,yell);
                            break;
                    case 2: printf("\t\t%s opted to BOWL first\n",q);
                            break;
                }
                break;
    }
}

void SCORECARD(batter *bat,bowler *bowl)
{
            batter *temp=bat->next;
            printf("\n-------------------------------------------------------------------------------\n\n");

            printf("%s-%d/%d\n\n",team1.teamname,team1.score,wickets);
            printf("Overs=%0.1f\n\n", overs);

            printf(" %s-%d(%d)\t\t ",bat->batname,bat->score,bat->balls);
            while(temp->flag!=1 && temp!=bat)
                temp=temp->next;
            printf(" %s-%d(%d)\t\t ",temp->batname,temp->score,temp->balls);
            printf("%s-%d/%d(%0.1f)\n",bowl->bowlname,bowl->score,bowl->wickets,bowl->ovars);

        printf("-------------------------------------------------------------------------------\n\n");
}

void FINALSHEET(batter *bat, bowler *bowl)
{
        int kid=1;
        batter *temp1;   temp1=bat->next;
        bowler *temp2;   temp2=bowl->next;
        printf("-----------------------------------------END OF BATTING-------------------------------------------------------\n\n");

    printf("......................................%s VS %s ..............................................................\n\n",team1.teamname,team2.teamname);
    printf("\t\t\t\t| BATTING TEAM - %s  |\n\n",team1.teamname);

        printf("\tBATTER\t\t\tSCORE\t\t HOW OUT \t\t\t\t 4's\t 6's \n");
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("-----------------------------------------------------------------------------------------------------\n");
    while(kid<=count)
        {
            if(temp1->batnum==kid)
            {
                printf("\n\t %-10.10s\t\t %d\t\t %-15.15s\t\t\t %d\t %d\n",temp1->batname,temp1->score,temp1->dismissal,temp1->fours,temp1->sixes);
                printf("-----------------------------------------------------------------------------------------------------\n");
                temp1=temp1->next;
                kid++;
            }
            else
                temp1=temp1->next;
        }

            printf("-----------------------------------------------------------------------------------------------------\n\n");
            printf("\t\t\t\t| BOWLING TEAM - %s  |\n\n",team2.teamname);

        printf("\tNo.\t BOWLER \t\t\tFIGURES\t\tOVERS  \n");
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("-----------------------------------------------------------------------------------------------------\n");
    while(temp2!=bowl)
 {
        printf("\n\t %d\t %-10.10s\t\t\t %d/%d\t\t %0.1f \n",temp2->bnum,temp2->bowlname,temp2->score,temp2->wickets,temp2->ovars);
        printf("-----------------------------------------------------------------------------------------------------\n");
        temp2=temp2->next;
 }
        printf("\n\t %d\t %-10.10s\t\t\t %d/%d\t\t %0.1f \n",temp2->bnum,temp2->bowlname,temp2->score,temp2->wickets,temp2->ovars);
        printf("-----------------------------------------------------------------------------------------------------\n");

printf("\n\t\t%s - %d/%d\n", team1.teamname,team1.score,wickets);
printf("\t\tOVERS=%0.1f\n", overs);
}

void FILEPRINT(FILE *fp,batter* bat, bowler *bowl)
{
     int kid=1;
    batter *temp1=bat->next; bowler *temp2=bowl->next;

    fprintf(fp,"......................................%s VS %s ......................................................\n\n",team1.teamname,team2.teamname);
    fprintf(fp,"\t\t\t\t| BATTING TEAM - %s  |\n\n",team1.teamname);

        fprintf(fp,"\tBATTER\t\tSCORE\t\t HOW OUT \t\t\t 4's\t 6's \n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------\n");

    while(kid<=count)
        {
            if(temp1->batnum==kid)
            {
                fprintf(fp,"\n\t %-10.10s\t\t %d\t\t %-15.15s\t\t\t %d\t %d\n",temp1->batname,temp1->score,temp1->dismissal,temp1->fours,temp1->sixes);
                fprintf(fp,"-----------------------------------------------------------------------------------------------------\n");
                temp1=temp1->next;
                kid++;
            }
            else
                temp1=temp1->next;
        }

             fprintf(fp,"-----------------------------------------------------------------------------------------------------\n\n");
            fprintf(fp,"\n\t\t\t\t| BOWLING TEAM - %s  |\n\n",team2.teamname);

        fprintf(fp,"\tNo.\t BOWLER \t\tFIGURES\t\tOVERS  \n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------\n");

    while(temp2!=bowl)
    {
        fprintf(fp,"\n\t %d\t %-10.10s\t\t\t %d/%d\t\t %0.1f \n",temp2->bnum,temp2->bowlname,temp2->score,temp2->wickets,temp2->ovars);
        fprintf(fp,"-----------------------------------------------------------------------------------------------------\n");
        temp2=temp2->next;
    }
        fprintf(fp,"\n\t %d\t %-10.10s\t\t\t %d/%d\t\t %0.1f \n",temp2->bnum,temp2->bowlname,temp2->score,temp2->wickets,temp2->ovars);
        fprintf(fp,"-----------------------------------------------------------------------------------------------------\n");

fprintf(fp,"\n\t\t%s - %d/%d\n", team1.teamname,team1.score,wickets);
fprintf(fp,"\t\tOVERS=%0.1f\n", overs);

}

 batter *STRIKEROTATE(batter *bat)
 {
     batter *temp=bat->next;
     while(temp->flag!=1)
        temp=temp->next;
     bat=temp;
     return bat;
 }

 batter *STRO(batter *bat)
    {
        char ch[20];
        if(bat->flag==0)
                {
                    printf("\n\tEnter the new Batter Name\n");
                    scanf("%s",ch);
                    bat=INSBAT(bat,ch);
                }
                return bat;
    }

     void INCREM(batter *bat,bowler *bowl,int runs)
    {
        bat->score=bat->score+runs;
        bowl->score=bowl->score+runs;
        team1.score=team1.score+runs;
        bowl->ovars=bowl->ovars+0.1;
        overs=overs+0.1;
        bat->balls++;
        balls++;
    }


    batter *COUNTER(batter *bat,bowler *bowl,int runs)
{
int add=0,add1=0,out;
char sr[5],fielder[20];

 switch(runs)
        {
          case '1': INCREM(bat,bowl,1);
                    bat=STRIKEROTATE(bat);
                    break;

          case '2': INCREM(bat,bowl,2);
                    break;

          case '3': INCREM(bat,bowl,3);
                    bat=STRIKEROTATE(bat);
                    break;

          case '4': INCREM(bat,bowl,4);
                    bat->fours++;
                    break;

          case '5': INCREM(bat,bowl,5);
                    bat=STRIKEROTATE(bat);
                    break;

          case '6': INCREM(bat,bowl,6);
                    bat->sixes++;
                    break;

          case 'o' :
          case 'O' : printf("\n\t\t.....%s OUT..!!!!\n\n",bat->batname);
                    bat->balls++;
                    bowl->ovars=bowl->ovars+0.1;
                    overs=overs+0.1;
                    printf("\n 1: Bowled\n 2: Catch\n 3: Run-out\n 4: Stumps\n");
                    printf("Select the dismissal\n");
                    scanf("%d",&out);
                    switch(out)
                    {
                        case 1: printf("-------------------------------------------------\n");
                                printf("\n\t\t%s-%d(%d)\n\t\tB.%s \n", bat->batname,bat->score,bat->balls,bowl->bowlname);
                                printf("-------------------------------------------------\n");
                                strcpy(bat->dismissal,"B.");
                                strcat(bat->dismissal,bowl->bowlname);
                                bowl->wickets++;
                                bat->flag=0;
                                bat=STRO(bat);
                                break;

                        case 2: printf("Enter the fielder name\n");
                                scanf("%s",fielder);
                                printf("-------------------------------------------------\n");
                                printf("\n\t\t%s-%d(%d)\n\t\tC.%s\tB.%s \n",bat->batname,bat->score,bat->balls,fielder,bowl->bowlname);
                                printf("-------------------------------------------------\n");
                                strcpy(bat->dismissal,"C.");
                                strcat(bat->dismissal,fielder);
                                strcat(bat->dismissal,"_B.");
                                strcat(bat->dismissal,bowl->bowlname);
                                bowl->wickets++;
                                bat->flag=0;
                                bat=STRO(bat);
                                printf("\nStrike Rotate ?\n Y\t(or)\t N \n");
                                scanf("%s",sr);
                                if(sr[0]=='Y'|| sr[0]=='y')
                                bat=STRIKEROTATE(bat);
                                break;

                        case 3: printf("Enter the fielder name\n");
                                scanf("%s",fielder);
                                printf("-------------------------------------------------\n");
                                printf("\n\t\t%s-%d(%d)\n\t\tR/O.%s\tB.%s \n",bat->batname,bat->score,bat->balls,fielder,bowl->bowlname);
                                printf("-------------------------------------------------\n");
                                strcpy(bat->dismissal,"R/O.");
                                strcat(bat->dismissal,fielder);
                                bat->flag=0;
                                bat=STRO(bat);
                                printf("\nStike Rotate ?\n Y\t(or)\t N \n");
                                scanf("%s",sr);
                                if(sr[0]=='Y'|| sr[0]=='y')
                                bat=STRIKEROTATE(bat);
                                break;

                        case 4: printf("-------------------------------------------------\n");
                                printf("\n\t\t%s-%d(%d)\n\t\tB.%s \n", bat->batname,bat->score,bat->balls,bowl->bowlname);
                                printf("-------------------------------------------------\n");
                                strcpy(bat->dismissal,"St.");
                                strcat(bat->dismissal,bowl->bowlname);
                                bowl->wickets++;
                                bat->flag=0;
                                bat=STRO(bat);
                                break;

                    }
                    wickets++;
                    balls++;
                    break;

          case 'w':
          case 'W': printf(".....WIDE BALL....\n\n");
                    printf("Additional runs scored\n");
                    scanf("%d", &add);
                    bat->score=bat->score+add;
                    if(add%2!=0)
                    bat=STRIKEROTATE(bat);
                    team1.score=team1.score+add+1;
                    bowl->score=bowl->score+add+1;
                    break;

         case 'n':
         case 'N' : printf(".....NO BALL.....\n\n");
                    printf("......FREE-HITTT.....!!!\n\n");
                    printf("Runs scored by bat\n");
                    scanf("%d",&add1);
                    bat->score=bat->score+add1;
                    if(add1==6)
                        bat->sixes++;
                    if(add1==4)
                        bat->fours++;
                    printf("Runs scored without bat\n");
                    scanf("%d", &add);
                   if((add+add1)%2!=0)
                      {
                        bat=STRIKEROTATE(bat);
                      }
                    team1.score=team1.score+add+add1+1;
                    bowl->score=bowl->score+add+add1+1;
                    bowl->ovars=bowl->ovars-0.1;
                    overs=overs-0.1;
                    balls--;
                    break;

           case 'B':
           case 'b': printf(".....BYCE.....\n\n");
                     printf("Runs gained\n\n");
                     scanf("%d", &add);
                     if(add%2!=0)
                      {
                        bat=STRIKEROTATE(bat);
                      }
                      bat->balls++;
                     team1.score=team1.score+add;
                     bowl->score=bowl->score+add;
                     bowl->ovars=bowl->ovars+0.1;
                     overs=overs+0.1;
                     balls++;
                     break;

            case '0': INCREM(bat,bowl,0);
                      break;
    }
    return bat;
}



