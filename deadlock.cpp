#include <iostream>
#include <vector>
using namespace std;


bool isDeadlocked(vector<vector<int>> &allocation, vector<vector<int>> &request, vector<int> &available)
{
    int P = allocation.size();    // Number of processes
    int R = available.size();     // Number of resources
    vector<bool> finish(P, false); // Finish flag for each process
    vector<int> work = available; // Work vector initialized to available resources

    
    bool progress = true;
    while (progress)
    {
        progress = false;
        for (int i = 0; i < P; i++)
        {
            if (!finish[i]) 
            {
                bool canFinish = true;
                for (int j = 0; j < R; j++)
                {
                    if (request[i][j] > work[j])
                    {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish)
                {
                   
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    }
    
    
    for (int i = 0; i < P; i++)
    {
        if (!finish[i])
            return true; 
    }
    return false; 
}

int main()
{
    int P, R;
    cout << "Enter number of processes: ";
    cin >> P;
    cout << "Enter number of resources: ";
    cin >> R;

    vector<vector<int>> allocation(P, vector<int>(R));
    vector<vector<int>> request(P, vector<int>(R));
    vector<int> available(R);

    cout << "Enter allocation matrix:" << endl;
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            cin >> allocation[i][j];

    cout << "Enter request matrix:" << endl;
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            cin >> request[i][j];

    cout << "Enter available resources:" << endl;
    for (int i = 0; i < R; i++)
        cin >> available[i];

    if (isDeadlocked(allocation, request, available))
        cout << "Deadlock detected!" << endl;
    else
        cout << "No deadlock detected." << endl;

    return 0;
}
