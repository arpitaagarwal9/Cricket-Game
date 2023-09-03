#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define Total_wickets 5
#define Total_overs 5

typedef struct
{
    char Name[20], Out_by[20];
    int Runs_scored, Balls_faced, Fours, Sixes, Balls_deliverd, Wickets_taken, Runs_given;
    float Strike_rake, Economy;
    short Batting_flag, Bowling_flag;
} Players;

typedef struct
{
    int Runs, Balls, Wickets, Extras, Number;
    float Run_rate;
} Teams;

// Global variables:

Teams My_team, Opponent_team;
Players My_players[Total_wickets + 1], Opponent_players[Total_wickets + 1];
int Inning = 1, Toss, end = 0; // temp_toss will tell what we took/got in the first inning. if temp_toss=1 we got/took batting in first inning, if temp_toss=2 meand we got/took bowling in first inning.
char All_players_name[8][10][20] = {{"Rohit Sharma", "Virat Kohli", "MS Dhoni", "Suresh Raina", "Yuvraj Singh", "R Jadeja", "Hardik Pandya", "R Ashwin", "Jasprit Bumrah", "Mohd Shami"}, {"Misbah-ul-Haq", "Younis Khan", "Shahid Afridi", "Ahmed Shehzad", "Haris Sohail", "Sarfaraz Ahmed", "Umar Akmal", "Mohammad Irfan", "Wahab Riaz", "Mohammad Amir"}, {"Steve Smith", "David Warner", "Glenn Maxwell", "George Bailey", "Shane Watson", "Usman Khwaja", "Brad Haddin", "Pat Cummins", "Mitchell Starc", "James Faulkner"}, {"Joe Root", "Eoin Morgan", "Jos Butler", "Alex Hales", "Ian Bell", "Moeen Ali", "Chris Woakes", "Adil Rashid", "Stuart Broad", "James Anderson"}, {"B McCullum", "K Williamson", "Martin Guptill", "Grant Elliot", "Corey Anderson", "Tim Southee", "Adam Milne", "Daniel Vettori", "Trent Boult", "M McClenaghan"}, {"Chris Gayle", "Andre Russell", "Keiron Pollard", "Darren Bravo", "Marlon Samuels", "Dinesh Ramdin", "Darren Sammy", "Jason Holder", "Kemar Roach", "Sunil Narine"}, {"T. Dilshan", "K. Sangakkara", "Upul Theranga", "M. Jayawardene", "L. Thirimanne", "Angelo Mathews", "D. Chandimal", "Rangana Herath", "Thisara Perera", "Lasith Malinga"}, {"Q. de Kock", "Hashim Amla", "AB de Villiers", "David Miller", "JP Duminy", "Kyle Abbott", "Kagiso Rabada", "Imran Tahir", "Morne Morkel", "Dale Steyn"}};

// Prototype of all functions:

int Random_omit(int Upper_value, int Omit);                                 // Returns a random number from 1 to Upper_value excluding Omit.
float Overs(int Balls_bowled);                                              // Converts Balls_bowled into equivalent overs.
int Is_in_limit(int Upper_limit, int Lower_limit, int Number);              // Returns 1 if Number is in between Upper_limit and Lower_limit(including both) else 0.
void Strike_swap(int *Striker, int *Runner);                                // Swaps position of Striker and Runner.
const char *Team_name(int Team_number);                                     // Returns the team name corresponding to the team number.
void Select_my_team(int Team_number);                                       // Select our team of 6 players.
void Select_opponent_team(int Team_number);                                 // Select top and bottom 3 players.
int Toss_outcome();                                                         // Computes the event of toss and returns 1 if 1st batting is of user else 2.
void My_batting();                                                          // Batting of the user takes place in this function.
int New_batsman();                                                          // Allows the user to choose new batsman from the remaining players after one currently playing is out.
int Opponent_new_bowler(int n);                                             // Select new bowler for computer.
void My_bowling();                                                          // Batting of the computer takes place in this function.
int Opponent_new_batsman(int n);                                            // Select new batsman for computer.
int New_bowler(int Current_bowler);                                         // Allows the user to choose a new bowler after the end of an over.
void Display_scorecard(Teams B_t, Players *B_p, Teams Bo_t, Players *Bo_p); // Displays complete scorecard at the end of an over or if someone gets out.
int Result();                                                               // Displays the final scorecard and the result of the match.
void Print_big(int);                                                        // Dsiplays certain words & symbols in an enlarged fashion.

int main()
{
    Print_big(5);
    printf("\033[1;33m"); // Set the text color to yellow
    printf("\n\n\t\t--------!! HERE THE GAME OF CRICKET BEGINS !!--------\n\n");
    printf("\t\t--------!! HERE ARE THE RULES OF THE GAME !!--------\n\nBefore every ball, you will select a number and the computer will randomly generate a number (from 1-6 both included).\n1. If the numbers match, the batting team will lose a wicket and no runs will be awarded to them.\n2. Otherwise, the batting team's chosen number will be awarded as runs to them.\n\n#Note: No balls are completely random and you don't have any control over them.\n\n");
p:

    printf("\033[1;34m");
    printf("Select you team number from the following teams :");

    printf("\n\n1. India\n");
    printf("\n2. Pakistan\n");
    printf("\n3. Australia\n");
    printf("\n4. England\n");
    printf("\n5. New Zealand\n");
    printf("\n6. West Indies\n");
    printf("\n7. Sri Lanka\n");
    printf("\n8. South Africa\n\n\n");

    scanf("%d", &My_team.Number);
    system("cls");
    if (!Is_in_limit(8, 1, My_team.Number)) // this will ensure that selected team is correct.
    {
        printf("\033[1;31m");
        printf("\n\t\t\t !! Enter a valid input !!\n");
        goto p;
    }
    printf("\033[1;32m");
    printf("\n\t\t\tYour selected team is : %s\n", Team_name(My_team.Number));
    Select_my_team(My_team.Number);
    Opponent_team.Number = Random_omit(8, My_team.Number);
    printf("\n\t\tBest of luck, your opponent team is : %s\n", Team_name(Opponent_team.Number));
    Select_opponent_team(Opponent_team.Number);
    Toss = Toss_outcome();
    Print_big(3);
    printf("\n\t\t\t----------|| THE FIRST INNING OF THE MATCH BEGINS ||----------\n"); // first inning of the match begins here
    if (Toss == 1)                                                                      // 1st batting of User
    {
        My_batting();
        printf("\n\n%s needs %d runs, in 5.0 overs, to WIN this match.\n\n", Team_name(Opponent_team.Number), My_team.Runs + 1);
        Print_big(4);
        printf("\n\n\t\t\t----------|| THE SECOND INNING OF THE MATCH BEGINS ||----------\n"); // second inning of the match begins here
        printf("\n\t\t\t  ----------|||| YOUR BOWLING STARTS HERE ||||----------\n");
        Inning++;
        My_bowling();
    }
    else if (Toss == 2) // 1st batting of Computer
    {
        My_bowling();
        printf("\n\n%s needs %d runs, in 5.0 overs, to WIN this match.\n\n", Team_name(My_team.Number), Opponent_team.Runs + 1);
        Print_big(4);
        printf("\n\t\t\t----------|| SECOND INNING OF THE MATCH BEGINS ||----------\n"); // second inning of the match begins here
        printf("\n\t\t\t  ----------|||| YOUR BATTING STARTS HERE ||||----------\n");
        Inning++;
        My_batting();
    }

    return 0;
}

int Random_omit(int Upper_value, int Omit)
{
    int ran;
    do
    {
        srand(time(NULL));
        ran = (rand() % Upper_value) + 1;
    } while (ran == Omit);
    return ran;
}

float Overs(int Balls_bowled)
{
    float Overs;
    Overs = Balls_bowled / 6 + Balls_bowled % 6 / 10.0;
    return Overs;
}

int Is_in_limit(int Upper_limit, int Lower_limit, int Number)
{
    if (Number >= Lower_limit && Number <= Upper_limit)
        return 1;
    return 0;
}

void Strike_swap(int *Striker, int *Runner)
{
    int temp = *Striker;
    *Striker = *Runner;
    *Runner = temp;
}

const char *Team_name(int Team_number)
{
    switch (Team_number)
    {
    case 1:
        return "India";
    case 2:
        return "Pakistan";
    case 3:
        return "Australia";
    case 4:
        return "England";
    case 5:
        return "New Zealand";
    case 6:
        return "West Indies";
    case 7:
        return "Sri Lanka";
    case 8:
        return "South Africa";
    default:
        return "None";
    }
}

void Select_my_team(int Team_number)
{
    int i;
    printf("\n\t\t\t!!! Its Time To Select Your Team !!! \n");
    for (i = 0; i < 10; i++)
        printf("%d. %s\n", i + 1, All_players_name[Team_number - 1][i]);
    printf("\nEnter the indexes of six players you want to keep in your team.\n");
    for (i = 0; i < Total_wickets + 1; i++)
    {
        int p;
    s:
        scanf("%d", &p);
        if (!Is_in_limit(10, 1, p))
        {
            printf("!! Enter a valid number !!");
            goto s;
        }
        strcpy(My_players[i].Name, All_players_name[Team_number - 1][p - 1]);
    }
    printf("\nYour Playing 6: \n");
    for (i = 0; i < Total_wickets + 1; i++)
        printf("\t%d. %s\n", i + 1, My_players[i].Name);
}

void Select_opponent_team(int Team_number)
{
    printf("\nYour Opponent's Playing 6: \n");
    for (int i = 0, j = 0; i < 10; i++)
    {
        if (i >= 3 && i <= 6)
            continue;
        strcpy(Opponent_players[j].Name, All_players_name[Team_number - 1][i]);
        printf("\t%d. %s\n", j + 1, Opponent_players[j].Name);
        j++;
    }
}

int Toss_outcome()
{
    int toss_choice, toss, BatBallChoice;
    printf("\n\t--- Its time for the toss, coin is in the air, select index of H/T you want to choose ---\n1. Heads\n2. Tails\n");
q:
    scanf("%d", &toss_choice);
    if (!Is_in_limit(2, 1, toss_choice)) // this will ensure that selected toss is correct.
    {
        printf("\n\t\t\t!! Enter a valid input !!\n");
        goto q;
    }
    toss = Random_omit(2, 0);
    printf("\t\t%s is the call \n\t\t.............\n\t\t.............\n\t\tand %s it is.\n\n", toss_choice == 1 ? "heads" : "tails", toss == 1 ? "heads" : "tails");
    if (toss_choice == toss)
    {
        printf("\t\tCONGRATULATIONS !! You WON the toss.\nWhat would you choose ?\n1)Bat\n2)Ball\n");
        scanf("%d", &BatBallChoice);
        printf("\n\t\tSo you choose to %s first.", BatBallChoice == 1 ? "Bat" : "Ball");
    }
    else
    {
        BatBallChoice = Random_omit(2, 0);
        printf("\tOHH NO !! You(%s) lose the toss, and %s choose to %s first.\n\n", Team_name(My_team.Number), Team_name(Opponent_team.Number), BatBallChoice == 1 ? "BALL" : "BAT");
    }
    return BatBallChoice;
}

void My_batting()
{
    int Bat, Ball, Striker, Runner, Free_hit = 0, temp, temp_i, Bowler = 5, Check;
    printf("Press the numbers\n1 for 1 run\n2 for 2 run\n3 for 3 run\n4 for 4 run\n5 for defence\n6 for 6 run\nNow you you have to select the index of the striker and the runner from the team of 6 members you have made:\n");
    for (int i = 0; i < Total_wickets + 1; i++)
        printf("\t%d) %s\n", i + 1, My_players[i].Name);
line192:
    scanf("%d", &Striker);
    if (!Is_in_limit(6, 1, Striker))
    {
        printf("\t\t\t!! Enter a valid input !!\n");
        goto line192;
    }
line194:
    scanf("%d", &Runner);
    if (!Is_in_limit(6, 1, Runner) || Runner == Striker)
    {
        printf("\t\t\t!! Enter a valid input !!\n");
        goto line194;
    }
    Striker--;
    Runner--;
    My_players[Striker].Batting_flag = 1;
    My_players[Runner].Batting_flag = 1;
    printf("Striker is %s\nRunner is %s\n\n", My_players[Striker].Name, My_players[Runner].Name);
    Opponent_players[Bowler].Bowling_flag = 1;
    printf("Bowler is %s\n\n", Opponent_players[Bowler].Name);
    while (My_team.Balls < Total_overs * 6 && My_team.Wickets < Total_wickets)
    {

        printf("Enter your Batting choice: ");
    Line198:
        scanf("%d", &Bat);
        if (!Is_in_limit(6, 1, Bat))
        {
            printf("\\n\t\t\t!! Enter a valid input !!\n");
            goto Line198;
        }
        printf("\n");
        Ball = Random_omit(8, 5);
        if (Ball == 7)
            Ball = 6;
        if (Ball == 8)
            Ball = 4;
        temp = -1;
        if (Random_omit(12, 0) == 1) // No ball checker
        {
            My_team.Runs++;
            My_team.Extras++;
            Opponent_players[Bowler].Runs_given++;
            Free_hit = 1;
            printf("No ball\n\t\tFREE HIT!!!!\n\n");
        }
        else
        {
            My_team.Balls++;
            Opponent_players[Bowler].Balls_deliverd++;
            if (Free_hit == 1)
                Ball = 0;
            if (Bat == Ball)
            {
                My_team.Wickets++;
                Opponent_players[Bowler].Wickets_taken++;
                strcpy(My_players[Striker].Out_by, Opponent_players[Bowler].Name);
                temp = Bat;
                Bat = 0;
            }
            Free_hit = 0;
        }
        if (Bat == 5)
            Bat = 0;
        if (Bat == 6)
            My_players[Striker].Sixes++;
        if (Bat == 4)
            My_players[Striker].Fours++;
        My_players[Striker].Runs_scored += Bat;
        My_players[Striker].Balls_faced++;
        My_team.Runs += Bat;
        Opponent_players[Bowler].Runs_given += Bat;
        if (Bat % 2 == 1) // if run is odd no., change strike
            Strike_swap(&Striker, &Runner);
        if (temp == Ball)
        {
            printf("\n\t\t\tIT'S A WICKET !!!");
            My_players[Striker].Batting_flag = 2;
            Display_scorecard(My_team, My_players, Opponent_team, Opponent_players);
            Striker = New_batsman();
        }
        if (Inning == 2)
        {
            if (Result() == 1)
            {
                Display_scorecard(My_team, My_players, Opponent_team, Opponent_players);
                break;
            }
        }
        if (My_team.Balls % 6 == 0 && My_team.Balls != 0 && Free_hit == 0)
        {
            printf("\t\t\tOVER COMPLETED\n");
            Display_scorecard(My_team, My_players, Opponent_team, Opponent_players);
            if (Overs(My_team.Balls) != Total_overs && My_team.Wickets != Total_wickets)
            {
                Strike_swap(&Striker, &Runner);
                Bowler = Opponent_new_bowler(Bowler);
                printf("\nThe new bowler is %s\n", Opponent_players[Bowler].Name);
            }
        }
        if (My_team.Wickets != Total_wickets)
            printf("\n%s \t %d-%d(%.1f)\t\t%s*\t%d  %d\t\t\t%s\t\t%d-%d\t%0.1f\n\t\t\t\t%s\t%d  %d\n\n", Team_name(My_team.Number), My_team.Runs, My_team.Wickets, Overs(My_team.Balls), My_players[Striker].Name, My_players[Striker].Runs_scored, My_players[Striker].Balls_faced, Opponent_players[Bowler].Name, Opponent_players[Bowler].Wickets_taken, Opponent_players[Bowler].Runs_given, Overs(Opponent_players[Bowler].Balls_deliverd), My_players[Runner].Name, My_players[Runner].Runs_scored, My_players[Runner].Balls_faced);
    }
}

int New_batsman()
{
    int i = 0, n;
    if (My_team.Wickets == Total_wickets)
    {
        printf("\t\tALL OUT\n");
        Display_scorecard(My_team, My_players, Opponent_team, Opponent_players);
        return -1;
    }
r:
    printf("Choose New Batsman from the following: \n");
    for (i = 0; i < Total_wickets + 1; i++)
    {
        if (My_players[i].Batting_flag == 0)
            printf("%d. %s\n", i + 1, My_players[i].Name);
    }
    scanf("%d", &n);
    if (n > 6 || My_players[n - 1].Batting_flag != 0)
    {
        printf("Enter a valid choice\n");
        goto r;
    }
    My_players[n - 1].Batting_flag = 1;
    printf("\nThe new batsman is : %s\n", My_players[n - 1].Name);
    return n - 1;
}

int Opponent_new_bowler(int Current_Bowler)
{
    int New_bowler = Random_omit(3, Current_Bowler - 2) + 2;
    Opponent_players[Current_Bowler].Bowling_flag = 2;
    Opponent_players[New_bowler].Bowling_flag = 1;
    return New_bowler;
}

void My_bowling()
{
    int Bat, Ball, Striker, Runner, Free_hit = 0, temp, temp_i = 0, Bowler;
    Striker = temp_i++;
    Runner = temp_i++;
    Opponent_players[Striker].Batting_flag = 1;
    Opponent_players[Runner].Batting_flag = 1;
    printf("Striker is %s \nRunner is %s\n\n", Opponent_players[Striker].Name, Opponent_players[Runner].Name);
s:
    printf("Choose a bowler: \n\n");
    for (int i = 0; i < Total_wickets + 1; i++)
        printf("%d. %s\n", i + 1, My_players[i].Name);
    scanf("%d", &Bowler);
    if (!Is_in_limit(6, 1, Bowler))
    {
        printf("\t\t\t!! Enter a valid input !!\n");
        goto s;
    }
    Bowler--;
    My_players[Bowler].Bowling_flag = 1;
    printf("Bowler is %s\n\n", My_players[Bowler].Name);
    while (Opponent_team.Balls < Total_overs * 6 && Opponent_team.Wickets < Total_wickets)
    {

        printf("Enter your Bowling choice: ");
    Line323:
        scanf("%d", &Ball);
        if (!Is_in_limit(6, 1, Ball))
        {
            printf("\n\t\t\t!! Enter a valid input !!\n");
            goto Line323;
        }
        printf("\n");
        if (Free_hit == 0)
            Bat = Random_omit(6, 5);
        else
            Bat = 6;
        temp = -1;
        if (Random_omit(12, 0) == 1) // No ball maker
        {
            Opponent_team.Runs++;
            Opponent_team.Extras++;
            My_players[Bowler].Runs_given++;
            Free_hit = 1;
            printf("\t\t\tYou did a NO BALL\n\n\t\t\t\tOpponent gets a FREE HIT!!!!\n\n");
        }
        else
        {
            Opponent_team.Balls++;
            My_players[Bowler].Balls_deliverd++;
            if (Free_hit == 1)
                Ball = 0;
            if (Bat == Ball)
            {
                Opponent_team.Wickets++;
                My_players[Bowler].Wickets_taken++;
                strcpy(Opponent_players[Striker].Out_by, My_players[Bowler].Name);
                temp = Bat;
                Bat = 0;
            }
            Free_hit = 0;
        }
        if (Bat == 5)
            Bat = 0;
        if (Bat == 6)
            Opponent_players[Striker].Sixes++;
        if (Bat == 4)
            Opponent_players[Striker].Fours++;
        Opponent_players[Striker].Runs_scored += Bat;
        Opponent_players[Striker].Balls_faced++;
        Opponent_team.Runs += Bat;
        My_players[Bowler].Runs_given += Bat;
        printf("Opponent hit: %d\n", Bat);
        if (Bat % 2 == 1) // if run is odd no., change strike
            Strike_swap(&Striker, &Runner);
        if (temp == Ball)
        {
            printf("\n\t\tOh Yes !! IT'S A WICKET!!");
            Opponent_players[Striker].Batting_flag = 2;
            Display_scorecard(Opponent_team, Opponent_players, My_team, My_players);
            Striker = Opponent_new_batsman(temp_i++);
        }
        if (Inning == 2)
        {
            if (Result() == 1)
            {
                Display_scorecard(Opponent_team, Opponent_players, My_team, My_players);
                break;
            }
        }
        if (Opponent_team.Balls % 6 == 0 && Opponent_team.Balls != 0 && Free_hit == 0)
        {
            printf("\t\t\tOVER COMPLETED\n");
            Display_scorecard(Opponent_team, Opponent_players, My_team, My_players);
            if (Overs(Opponent_team.Balls) != Total_overs && Opponent_team.Wickets != Total_wickets)
            {
                Strike_swap(&Striker, &Runner);
                Bowler = New_bowler(Bowler);
                printf("\nThe new bowler is %s\n", My_players[Bowler].Name);
            }
        }
        if (Opponent_team.Wickets != Total_wickets)
            printf("\n%s \t %d-%d(%.1f)\t\t%s*\t%d  %d\t\t\t%s\t%d-%d\t%0.1f\n\t\t\t\t\t%s\t%d  %d\n\n", Team_name(Opponent_team.Number), Opponent_team.Runs, Opponent_team.Wickets, Overs(Opponent_team.Balls), Opponent_players[Striker].Name, Opponent_players[Striker].Runs_scored, Opponent_players[Striker].Balls_faced, My_players[Bowler].Name, My_players[Bowler].Wickets_taken, My_players[Bowler].Runs_given, Overs(My_players[Bowler].Balls_deliverd), Opponent_players[Runner].Name, Opponent_players[Runner].Runs_scored, Opponent_players[Runner].Balls_faced);
    }
}

int Opponent_new_batsman(int n)
{
    if (Opponent_team.Wickets == Total_wickets)
    {
        printf("\t\tALL OUT\n");
        Display_scorecard(Opponent_team, Opponent_players, My_team, My_players);
        return -1;
    }
    Opponent_players[n].Batting_flag = 1;
    printf("\nThe new batsman is : %s\n", Opponent_players[n].Name);
    return n;
}

int New_bowler(int Current_bowler)
{
    int i, New_bowler;
r:
    printf("Choose New Bowler from the following: \n");
    for (i = 0; i < Total_wickets + 1; i++)
    {
        if (My_players[i].Bowling_flag != 1)
            printf("%d. %s\n", i + 1, My_players[i].Name);
    }
    scanf("%d", &New_bowler);
    if (New_bowler > 6 || My_players[New_bowler - 1].Bowling_flag == 1)
    {
        printf("Enter a valid choice\n");
        goto r;
    }
    My_players[New_bowler - 1].Bowling_flag = 1;
    My_players[Current_bowler].Bowling_flag = 2;
    return (New_bowler - 1);
}

void Display_scorecard(Teams Batting_team, Players *Batting_players, Teams Bowling_team, Players *Bowling_players)
{
    Batting_team.Run_rate = (float)Batting_team.Runs * 6 / Batting_team.Balls;
    for (int i = 0; i < Total_wickets + 1; i++)
    {
        if (Batting_players[i].Batting_flag != 0)
            Batting_players[i].Strike_rake = (float)Batting_players[i].Runs_scored / Batting_players[i].Balls_faced * 100;
        if (Bowling_players[i].Bowling_flag != 0)
            Bowling_players[i].Economy = (float)Bowling_players[i].Runs_given / Bowling_players[i].Balls_deliverd * 6;
    }
    printf("\n----------------------------------------------------------------------------------------------------\n");
    printf("Batting\t\t\tRuns\tBalls\tFours\tSixes\tStrike Rate\n\n");
    for (int i = 0; i < Total_wickets + 1; i++)
    {
        if (Batting_players[i].Batting_flag == 0)
            continue;
        printf("%s ", Batting_players[i].Name);
        printf("\t\t%d\t%d\t%d\t%d\t%0.2f\n", Batting_players[i].Runs_scored, Batting_players[i].Balls_faced, Batting_players[i].Fours, Batting_players[i].Sixes, Batting_players[i].Strike_rake);
        if (Batting_players[i].Batting_flag == 1)
            printf("NOT OUT\n\n");
        else
            printf("OUT by %s\n\n", Batting_players[i].Out_by);
    }
    printf("Extras:\t\t %d\nRun Rate:\t %.2f\n", Batting_team.Extras, Batting_team.Run_rate);
    printf("Total runs \t %d(%d Wickets, %.1f Overs)\n", Batting_team.Runs, Batting_team.Wickets, Overs(Batting_team.Balls));
    printf("Yet to bat\t ");
    for (int i = 0; i < Total_wickets + 1; i++)
    {
        if (Batting_players[i].Batting_flag == 0)
            printf("%s || ", Batting_players[i].Name);
    }
    printf("\n\n\t\t*************\n");
    printf("\nBowling\t\t\tOvers\tRuns\tWickets\t   Economy\n\n");
    for (int i = 0; i < Total_wickets + 1; i++)
    {
        if (Bowling_players[i].Bowling_flag == 0)
            continue;
        printf("%s\t\t%0.1f\t%d\t%d\t   %0.2f\n", Bowling_players[i].Name, Overs(Bowling_players[i].Balls_deliverd), Bowling_players[i].Runs_given, Bowling_players[i].Wickets_taken, Bowling_players[i].Economy);
    }
    printf("\n----------------------------------------------------------------------------------------------------\n");
}

int Result()
{
    if (Inning == 2)
    {
        if (Toss == 1)
        {
            if (My_team.Runs < Opponent_team.Runs)
            {
                printf("\n\t\t\t----------|||| YOUR BOWLING ENDS HERE ||||----------\n");
                printf(" \n\n\t\tYour team (%s) lost by %d wickets.\n", Team_name(My_team.Number), Total_wickets - Opponent_team.Wickets);

                Print_big(2);
                end = 1;
                return end;
            }
            else if ((My_team.Runs > Opponent_team.Runs) && (Opponent_team.Balls == Total_overs * 6))
            {
                printf("\n\t\t\t----------|||| YOUR BOWLING ENDS HERE ||||----------\n");
                printf(" \n\n\t\tYour team (%s) won by %d runs.\n", Team_name(My_team.Number), -Opponent_team.Runs + My_team.Runs);
                Print_big(1);
                end = 1;
                return end;
            }
            else if ((My_team.Runs > Opponent_team.Runs) && (Opponent_team.Wickets == Total_wickets))
            {
                printf("\n\t\t\t----------|||| YOUR BOWLING ENDS HERE ||||----------\n");
                printf(" \n\n\t\tYour team (%s) won by %d runs.\n", Team_name(My_team.Number), -Opponent_team.Runs + My_team.Runs);
                Print_big(1);
                end = 1;
                return end;
            }
            else if ((Opponent_team.Balls == Total_overs * 6 || Opponent_team.Wickets == Total_wickets) && My_team.Runs == Opponent_team.Runs)
            {
                printf("\n\t\t\t----------|||| YOUR BOWLING ENDS HERE ||||----------\n");
                Print_big(6);
                end = 1;
                return end;
            }
            else
                return -1;
        }
        else if (Toss == 2)
        {

            if ((My_team.Runs < Opponent_team.Runs) && (My_team.Balls == Total_overs * 6))
            {
                printf("\n\t\t\t----------|||| YOUR BATTING ENDS HERE ||||----------\n");
                printf("\n\n\t\tYour team (%s) lost by %d runs.\n", Team_name(My_team.Number), Opponent_team.Runs - My_team.Runs);
                Print_big(2);
                end = 1;
                return end;
            }
            else if ((My_team.Runs < Opponent_team.Runs) && (My_team.Wickets == Total_wickets))
            {
                printf("\n\t\t\t----------|||| YOUR BATTING ENDS HERE ||||----------\n");
                printf(" \n\n\t\tYour team (%s) lost by %d runs.\n", Team_name(My_team.Number), Opponent_team.Runs - My_team.Runs);
                Print_big(2);
                end = 1;
                return end;
            }
            else if (My_team.Runs > Opponent_team.Runs)
            {
                printf("\n\t\t\t----------|||| YOUR BATTING ENDS HERE ||||----------\n");
                printf("\n \n\t\tYour team (%s) won by %d wickets.\n", Team_name(My_team.Number), Total_wickets - My_team.Wickets);
                Print_big(1);
                end = 1;
                return end;
            }
            else if ((My_team.Balls == Total_overs * 6 || My_team.Wickets == Total_wickets) && My_team.Runs == Opponent_team.Runs)
            {
                printf("\n\t\t\t----------|||| YOUR BATTING ENDS HERE ||||----------\n");
                Print_big(6);
                end = 1;
                return end;
            }
            else
                return -1;
        }
        else
            return -1;
    }
    else
        return -1;
}

void Print_big(int num)
{
    if (num == 1)
    {
        printf("\033[1;32m");
        printf("\n");
        printf("##   ##   #######   ##      ##             ##        ##  ########  ##      ##\n");
        printf("##   ##  ##     ##  ##      ##             ##        ##     ##     ###     ##\n");
        printf("##   ##  ##     ##  ##      ##             ##   ##   ##     ##     ####    ##\n");
        printf(" #####   ##     ##  ##      ##             ##   ##   ##     ##     ## ##   ##\n");
        printf("  ##     ##     ##  ##      ##             ##   ##   ##     ##     ##  ##  ##\n");
        printf("  ##     ##     ##   ##    ##              ##   ##   ##     ##     ##   ## ##\n");
        printf("  ##      #######     ######                ##########   ########  ##    ####\n");
    }
    if (num == 2)
    {
        printf("\033[1;31m");
        printf("\n");
        printf("##   ##   #######   ##      ##              ##        ######     ######    ####### \n");
        printf("##   ##  ##     ##  ##      ##              ##       ##    ##   ##         ##      \n");
        printf("##   ##  ##     ##  ##      ##              ##       ##    ##   ##         ##      \n");
        printf(" #####   ##     ##  ##      ##              ##       ##    ##    ######    ######  \n");
        printf("  ##     ##     ##  ##      ##              ##       ##    ##         ##   ##      \n");
        printf("  ##     ##     ##   ##    ##               ##       ##    ##         ##   ##      \n");
        printf("  ##      #######     ######                #######   ######    #######    #######  \n");
    }
    if (num == 3)
    {
        printf("\033[1;35m");
        printf("\n");
        printf("#######  ########  #######     ######  ########          ########  ##      ##  ##      ##  #######  ##     ##    ##### \n");
        printf("##          ##     ##    ##   ##          ##                ##     ###     ##  ###     ##     ##    ###    ##   ##     \n");
        printf("##          ##     ##    ##   ##          ##                ##     ####    ##  ####    ##     ##    ####   ##  ##      \n");
        printf("######      ##     ######     ######      ##                ##     ## ##   ##  ## ##   ##     ##    ## ##  ##  ##   ###\n");
        printf("##          ##     ##   ##         ##     ##                ##     ##  ##  ##  ##  ##  ##     ##    ##  ## ##  ##    ##\n");
        printf("##          ##     ##    ##        ##     ##                ##     ##   ## ##  ##   ## ##     ##    ##   ####   ##   ##\n");
        printf("##       ########  ##     ##  ######      ##             ########  ##    ####  ##    ####  #######  ##    ###    ##### \n");
    }
    if (num == 4)
    {
        printf("\033[1;36m");
        printf("\n");
        printf(" ######  #######    #####     #####    ##     ##  ######            ########  ##      ##  ##      ##  #######  ##     ##    ##### \n");
        printf("##       ##        ##   ##   ##   ##   ###    ##  ##    ##             ##     ###     ##  ###     ##     ##    ###    ##   ##     \n");
        printf("##       ##       ##        ##     ##  ####   ##  ##     ##            ##     ####    ##  ####    ##     ##    ####   ##  ##      \n");
        printf("######   ######   ##        ##     ##  ## ##  ##  ##     ##            ##     ## ##   ##  ## ##   ##     ##    ## ##  ##  ##   ###\n");
        printf("     ##  ##       ##        ##     ##  ##  ## ##  ##     ##            ##     ##  ##  ##  ##  ##  ##     ##    ##  ## ##  ##    ##\n");
        printf("     ##  ##        ##   ##   ##   ##   ##   ####  ##    ##             ##     ##   ## ##  ##   ## ##     ##    ##   ####   ##   ##\n");
        printf("######   #######    #####     #####    ##    ###  ######            ########  ##    ####  ##    ####  #######  ##    ###    ##### \n");
    }
    if (num == 5)
    {

        printf("\033[1;32m");
        printf("\n");
        printf("  #####   #######    ########    #####   ##    ##  #######  ########            __\n");
        printf(" ##   ##  ##    ##      ##      ##   ##  ##   ##   ##          ##               \\ \\  \n");
        printf("##        ##    ##      ##     ##        ##  ##    ##          ##                \\ \\ \n");
        printf("##        ######        ##     ##        #####     ######      ##               __\\ \\__\n");
        printf("##        ##   ##       ##     ##        ##  ##    ##          ##               \\      \\\n");
        printf(" ##   ##  ##    ##      ##      ##   ##  ##   ##   ##          ##                \\      \\\n");
        printf("  #####   ##     ##  ########    #####   ##    ##  #######     ##                 \\       ##\n");
        printf("  \t\t\t\t\t\t\t\t\t\t   \\     ####\n");
        printf("  \t\t\t\t\t\t\t\t\t\t    \\     ##\n");
        printf("  \t\t\t\t\t\t\t\t\t\t     \\      \\\n");
        printf("  \t\t\t\t\t\t\t\t\t\t      \\______\\\n");
    }
    if (num == 6)
    {
        printf("\n");
        printf("########  ########  ####### \n");
        printf("   ##        ##     ##      \n");
        printf("   ##        ##     ##      \n");
        printf("   ##        ##     ######  \n");
        printf("   ##        ##     ##      \n");
        printf("   ##        ##     ##      \n");
        printf("   ##     ########  ####### \n");
    }
}
