vector<match> unique_matches_list; // Defining Unique Matches List Vector (Globally declared)


//Important part of the Question.
//we have to Design All the Possible Unique Matches from the Players List of Size M vs M.


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
