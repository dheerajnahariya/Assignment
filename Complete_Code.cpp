#include <bits/stdc++.h>
using namespace std;

struct match   //Structure for Match (Both Side Team)
{
    string name1,name2;
    double avg1,avg2;
    double dif;
};

struct players   //Structure for Players
{
    string name;
    double score;
};

struct team      //Structure for Team (One Side Team)
{
    string name;
    double avg;
};


// This Function Will Create Unique Teams. Example : Input {M=2 and A B C D} => Output {A B vs C D} , {A C vs B D} , {A D vs B C} 
void create_unique_teams(int ind,vector<int> &helper_vector,int n,vector<vector<int>> &uniqueid_list,int m)
{
    // we only Want 2m Players in One Match => M vs M
    if(helper_vector.size()==2*m) // Selecting Pair of 2M Players from List of Players cause we Want M vs M (Match)
    {
        uniqueid_list.push_back(helper_vector);
        return;
    }

    //Base Case to Terminate The Recursion
    if(ind ==n)
        return;

    //Recursive Case with Back Tracking
    //Following Code for Generating Possible Subsets (Matches) Using BackTracking
    create_unique_teams(ind+1,helper_vector,n,uniqueid_list,m);
    helper_vector.push_back(ind);
    create_unique_teams(ind+1,helper_vector,n,uniqueid_list,m);
    helper_vector.pop_back();  //Backtracking Concept
}

vector<match> unique_matches_list; // Defining Unique Matches List Vector (Globally)


//Important part of the Question.
// Design All the Possible Unique Matches from the Players List of Size M vs M.
void Design_Unique_Matches(int ind,int n,vector<int>&help,vector<int>&all,int m, vector<players>&players_list)
{
    if(help.size()==m)  // When One side Team Size Reached M
    {
        if(help[0]==all[0])
        {
            // We will use this Array to Diffrentiate Between Team 1 vs Team 2
            int mark[n]={0};  //Empty Array of Size n 

            for(auto x:all)
            mark[x]=1;
            match tt;
            double av=0;
            string temp="";

            //Selecting M Students for First Team ( team 1) from help Vector and Calculating The Average of Team 1
            for(auto x:help)
            {
                mark[x]=0;
                temp+=players_list[x].name;
                temp.push_back(',');
                av+=players_list[x].score;
            }

            temp.pop_back();  //This is for removing Last Comma to Avoid => { A,B, (78) vs C,D,(98)} type of Thing.
            av=av/m*1.0;  // Calculating Average by dividing M 
            tt.name1=temp;
            tt.avg1=av;

            // Set String temp to NULL and Integer av to Zero for Calculation of Second Team (Team 2).
            temp="";
            av=0;


            // Traverse in the Rest of the List and Select M Players for Second Team ( Team 2 ).
            // Same Calculation for the Team 2 Also.
            for(auto x:all)
            {
                if(mark[x]==0)
                continue;

                temp+=players_list[x].name;
                temp.push_back(',');
                av+=players_list[x].score;
            }

            temp.pop_back();   //To remove the Last Comma from Team 2 Name.

            av=av/m*1.0;    //Calculating Average for Team Second.
            tt.name2=temp;
            tt.avg2=av;

            tt.dif=abs(tt.avg1-tt.avg2);  // Calculating Diffrences of Average / Closeness of Averages

            unique_matches_list.push_back(tt); // Finally Push it in the Unique Matches List.

            // So the Thing is in Each Recursive Call we will Store Every Unique Match Combination in Unique_macth_List.
        }
        return;
    }

    //Base Case to Terminate the Recursion
    if(ind ==all.size())
        return;

    //Recursive Case with Backtracking
    // Following Code is to Fill all the Possible Unique Matches with Averages and Diffrences
    Design_Unique_Matches(ind+1,n,help,all,m,players_list);
    help.push_back(all[ind]);
    Design_Unique_Matches(ind+1,n,help,all,m,players_list);
    help.pop_back();  // => BackTracking Concept
}


// Compare Function for Compare the Match List According to the Diffrences of the Averages.
// Input => Match1 A(100) vs B(78) , Match2 A(100) vs C(87)
//Output => Match2 , Match1 (Sorted order according to diffrences of Averages)
bool compare(match players_list , match b) 
{
    return players_list.dif < b.dif;  //Ascending Order Sort...
}

int main()
{
    int m;
    cin>>m;  // Taking Input of Players of Each Side M
    vector<players> players_list;
    string player_name;
    double player_score;

    // While loop will Take Input till the end of Line.
    while(cin>>player_name && cin>>player_score)   //taking input and storing all details.
    {
        players temp;
        temp.name=player_name;
        temp.score=player_score;
        players_list.push_back(temp);
    }

    int n = players_list.size();   //n is the Total Number of Players => In our Input till end of Line. 
    vector<int>helper_vector;      //an helper vector
    vector<vector<int>> uniqueid_list;

    // Create Teams by Calling Following Function
    create_unique_teams(0,helper_vector,n,uniqueid_list,m);  // Calling Create Unique Teams of Size M to play M vs M Match
    // We Will Store the Unique Teams in Unique ID List.

    //Unique_Id_List => { {A,B vs C,D} , {A,C vs B,D} , {A,D vs B,C} }

    for(auto x:uniqueid_list)
    {
        vector<int>help;
        vector<int>all=x;
        Design_Unique_Matches(0,n,help,all,m,players_list);     //This Function Will Generate All the Possible Unique Matches 

        // We will Store the Matches in Unique_matches_list.
    }

    // Sort the Matches in Ascending Order According to thier Closeness by Passing Compare Function.    
    sort(unique_matches_list.begin(),unique_matches_list.end(),compare);//sorting matches on the basis of closeness


    // Traverse in Unique Matches List and Print the Output in Following Format.
    //Format => Team1 Name (Average) vs Team2 Name (Average)
    for(auto x:unique_matches_list)//printing the desired output
    {
        cout<<x.name1<<" ("<<setprecision(2)<<fixed<<x.avg1<<") vs "<<x.name2<<" ("<<x.avg2<<")\n";
    }
        
}







//after this  check my new file in that i will attach the unit testing document in new file
