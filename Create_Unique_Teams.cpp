// This Function Will Create Unique Teams.
//Example : Input {M=2 and A B C D} => Output {A B vs C D} , {A C vs B D} , {A D vs B C} 


void create_unique_teams(int ind,vector<int> &helper_vector,int n,vector<vector<int>> &uniqueid_list,int m)
{
    // we only Want 2*M Players in One Match => M vs M
    if(helper_vector.size()==2*m) // Selecting Pair of 2*M Players from List of Players cause we Want M vs M (Match)
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
