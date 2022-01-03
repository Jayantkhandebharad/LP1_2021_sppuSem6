#include <iostream>
#include <algorithm>
#include <climits>

using namespace std;

// FCFS STARTS
// {

void find_waiting_time_fcfs(int *burst, int *arrival, int *waiting, int n)
{
    int *service = new int[n];
    waiting[0] = 0;
    service[0] = arrival[0];
    for (int i = 1; i < n; i++)
    {
        service[i] = service[i - 1] + burst[i - 1];
        waiting[i] = service[i] - arrival[i];
        if (waiting[i] < 0)
        {
            waiting[i] = 0;
        }
    }
    delete[] service;
}

void find_turnaround_time_fcfs(int *burst, int *waiting, int *turnaround, int n)
{
    for (int i = 0; i < n; i++)
    {
        turnaround[i] = burst[i] + waiting[i];
    }
}

void find_average_times_fcfs(int *burst, int *arrival, int *turnaround, int *waiting, int n, double &avg_tat, double &avg_wt)
{
    find_waiting_time_fcfs(burst, arrival, waiting, n);
    find_turnaround_time_fcfs(burst, waiting, turnaround, n);
    int total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++)
    {
        total_wt += waiting[i];
        total_tat += turnaround[i];
    }
    avg_tat = (1.0 * total_tat) / n;
    avg_wt = (1.0 * total_wt) / n;
}

void fcfs_algo()
{
    int n, i;
    double avg_tat, avg_wt;
    cout << "Enter number of processes ";
    cin >> n;
    int *processes = new int[n];
    int *burst = new int[n];
    int *arrival = new int[n];
    int *turnaround = new int[n];
    int *waiting = new int[n];
    cout << "\nEnter process ID:\n";
    for (i = 0; i < n; i++)
    {
        cin >> processes[i];
    }
    cout << "\nEnter Burst Times: \n";
    for (i = 0; i < n; i++)
    {
        cin >> burst[i];
    }
    cout << "\nEnter Arrival Times: \n";
    for (i = 0; i < n; i++)
    {
        cin >> arrival[i];
    }
    find_average_times_fcfs(burst, arrival, turnaround, waiting, n, avg_tat, avg_wt);
    cout << "\n\nP. ID"
         << "\t\t"
         << "A.T."
         << "\t\t"
         << "B.T."
         << "\t\t"
         << "T.A.T."
         << "\t\t"
         << "W.T." << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processes[i] << "\t\t" << arrival[i] << "\t\t" << burst[i] << "\t\t" << turnaround[i] << "\t\t" << waiting[i] << endl;
    }

    cout << "\n\nAverage turnaround time = " << avg_tat;
    cout << "\nAverage waiting time = " << avg_wt;

    delete[] processes;
    delete[] arrival;
    delete[] waiting;
    delete[] burst;
    delete[] turnaround;
}

// }
// FCFS ENDS

// SJF STARTS
// {

struct Process_sjf
{
    int id;
    int bt;
    int at;
};

void findWaitingTime_sjf(Process_sjf proc[], int n, int wt[])
{
    int rt[n];
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    while (complete != n)
    {

        for (int j = 0; j < n; j++)
        {
            if ((proc[j].at <= t) && (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false)
        {
            t++;
            continue;
        }

        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;
        if (rt[shortest] == 0)
        {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].at;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}

void findTurnAroundTime_sjf(Process_sjf proc[], int n, int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = proc[i].bt + wt[i];
    }
}

void findAverageTime_sjf(Process_sjf proc[], int n, int wt[], int tat[], double &avg_wt, double &avg_tat)
{
    findWaitingTime_sjf(proc, n, wt);
    findTurnAroundTime_sjf(proc, n, wt, tat);
    int total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    avg_tat = (1.0 * total_tat) / n;
    avg_wt = (1.0 * total_wt) / n;
}

void sjf_algo()
{
    int n, i;
    double avg_wt, avg_tat;
    cout << "\nEnter number of processes ";
    cin >> n;
    Process_sjf *proc = new Process_sjf[n];
    int *turnaround = new int[n];
    int *waiting = new int[n];
    cout << "\nEnter process ID: \n";
    for (i = 0; i < n; i++)
    {
        cin >> proc[i].id;
    }
    cout << "\nEnter Burst Times: \n";
    for (i = 0; i < n; i++)
    {
        cin >> proc[i].bt;
    }
    cout << "\nEnter Arrival Times: \n";
    for (i = 0; i < n; i++)
    {
        cin >> proc[i].at;
    }
    findAverageTime_sjf(proc, n, waiting, turnaround, avg_wt, avg_tat);
    cout << "\n\nP. ID"
         << "\t\t"
         << "A.T."
         << "\t\t"
         << "B.T."
         << "\t\t"
         << "T.A.T."
         << "\t\t"
         << "W.T." << endl;
    for (int i = 0; i < n; i++)
    {
        cout << proc[i].id << "\t\t" << proc[i].at << "\t\t" << proc[i].bt << "\t\t" << turnaround[i] << "\t\t" << waiting[i] << endl;
    }

    cout << "\n\nAverage turnaround time = " << avg_tat;
    cout << "\nAverage waiting time = " << avg_wt;
}

// }
// SJF ENDS

// PRIORITY STARTS
// {

struct Process_priority
{
    int pid;
    int bt;
    int priority;
};

bool comparison(Process_priority a, Process_priority b)
{
    return (a.priority > b.priority);
}

void findWaitingTime_priority(Process_priority proc[], int n, int wt[])
{
    wt[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wt[i] = proc[i - 1].bt + wt[i - 1];
    }
}

void findTurnAroundTime_priority(Process_priority proc[], int n, int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = proc[i].bt + wt[i];
    }
}

void findavgTime_priority(Process_priority proc[], int n)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    findWaitingTime_priority(proc, n, wt);
    findTurnAroundTime_priority(proc, n, wt, tat);
}

void priority_algo()
{
    int n, i;
    double avg_wt, avg_tat;
    cout << "\nEnter number of processes: ";
    cin >> n;
    Process_priority *proc = new Process_priority[n];

    cout << "\nEnter Process ID: \n";
    for (i = 0; i < n; i++)
    {
        cin >> proc[i].pid;
    }
    cout << "\nEnter Burst Time: \n";
    for (i = 0; i < n; i++)
    {
        cin >> proc[i].bt;
    }
    cout << "\nEnter priority of each process: \n";
    for (i = 0; i < n; i++)
    {
        cin >> proc[i].priority;
    }
    sort(proc, proc + n, comparison);
    int wt[n], tat[n];
    findWaitingTime_priority(proc, n, wt);
    findTurnAroundTime_priority(proc, n, wt, tat);
    findavgTime_priority(proc, n);
    cout << "\n\nP. ID"
         << "\t\t"
         << "PRIORITY"
         << "\t\t"
         << "B.T."
         << "\t\t"
         << "T.A.T."
         << "\t\t"
         << "W.T." << endl;
    for (int i = 0; i < n; i++)
    {
        cout << proc[i].pid << "\t\t" << proc[i].priority << "\t\t\t" << proc[i].bt << "\t\t" << tat[i] << "\t\t" << wt[i] << endl;
    }
    // for(i=0;i<n;i++){
    //     cout<<"\n\nFor the process "<<proc[i].pid<<"\n";
    //     cout<<"\n\nPriority \t\t= "<<proc[i].priority;
    //     cout<<"\nBurst time \t\t= "<<proc[i].bt;
    //     cout<<"\nTurnaround time \t= "<<turnaround[i];
    //     cout<<"\nWaiting time \t\t= "<<waiting[i];
    // }
    cout << "\n\nAverage turnaround time = " << avg_tat;
    cout << "\nAverage waiting time = " << avg_wt;
}

// }
// PRIORITY ENDS

// ROUND ROBIN STARTS
// {

void findWaitingTime_roundrobin(int processes[], int n, int bt[], int wt[], int quantum)
{
    int rem_bt[n];
    for (int i = 0; i < n; i++)
    {
        rem_bt[i] = bt[i];
    }

    int t = 0;
    while (1)
    {
        bool done = true;
        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = false;
                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t = t + rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == true)
            break;
    }
}

void findTurnAroundTime_roundrobin(int processes[], int n, int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
    }
}

void findavgTime_roundrobin(int processes[], int n, int bt[], int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;
    double avg_tat, avg_wt;
    findWaitingTime_roundrobin(processes, n, bt, wt, quantum);
    findTurnAroundTime_roundrobin(processes, n, bt, wt, tat);
    for (int i = 0; i < n; i++)
    {
        cout << "\n\nFor the process " << processes[i] << "\n";
        cout << "\nBurst time \t\t= " << bt[i];
        cout << "\nTurnaround time \t= " << tat[i];
        cout << "\nWaiting time \t\t= " << wt[i];
    }
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    avg_tat = (1.0 * total_tat) / n;
    avg_wt = (1.0 * total_wt) / n;
    cout << "\n\nAverage turnaround time = " << avg_tat;
    cout << "\nAverage waiting time = " << avg_wt;
}

void roundrobin_algo()
{
    int n, i;
    cout << "Enter number of processes ";
    cin >> n;
    int *processes = new int[n];
    int *burst = new int[n];
    cout << "\nEnter process numbers\n";
    for (i = 0; i < n; i++)
    {
        cin >> processes[i];
    }
    cout << "\nEnter burst times\n";
    for (i = 0; i < n; i++)
    {
        cin >> burst[i];
    }
    int quantum = 2;
    findavgTime_roundrobin(processes, n, burst, quantum);
}

// }
// ROUND ROBIN ENDS

int main()
{
    int ch, n, i;
    cout << "\n\n\t\t\t\tCPU SCHEDULING ALGORITHMS\n\n";
    while (1)
    {
        cout << "\n\n1. FCFS SCHEDULING ALGORITHM";
        cout << "\n2. SJF SCHEDULING ALGORITHM";
        //cout<<"\n3. PRIORITY SCHEDULING ALGORITHM";
        cout << "\n4. ROUND ROBIN SCHEDULING ALGORITHM";
        cout << "\n5. STOP";
        cout << "\n\nEnter choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            fcfs_algo();
            break;
        case 2:
            sjf_algo();
            break;
        case 3:
            priority_algo();
            break;
        case 4:
            roundrobin_algo();
            break;
        case 5:
            cout << "\n\n\t\t\t\tTHANK YOU!!!";
            return 0;
        default:
            cout << "\n\nEnter valid choice";
            return 0;
        }
    }

    return 0;
}
