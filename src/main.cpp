#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int startTime;
    int finishTime;
    int waitingTime;
    int turnaroundTime;
};
bool compareById(const Process& a, const Process& b) {
    return a.id < b.id;
}
void executeRoundRobin(queue<Process>& processes, int timeQuantum, vector<Process>& results) {
    int currentTime = 0;
    while (!processes.empty()) {
        Process currentProcess = processes.front();
        processes.pop();
        if (currentProcess.startTime == -1) {
            currentProcess.startTime = max(currentTime, currentProcess.arrivalTime);
        }
        int executionTime = min(timeQuantum, currentProcess.remainingTime);
        cout << "Executing Process " << currentProcess.id << " for " << executionTime << " ms." << endl;
        currentProcess.remainingTime -= executionTime;
        currentTime += executionTime;
        queue<Process> tempQueue = processes;
        while (!tempQueue.empty()) {
            Process& p = tempQueue.front();
            if (p.arrivalTime <= currentTime) {
                p.waitingTime += executionTime;
            }
            tempQueue.pop();
        }
        if (currentProcess.remainingTime > 0) {
            processes.push(currentProcess);
        } else {
            currentProcess.finishTime = currentTime;
            currentProcess.turnaroundTime = currentProcess.finishTime - currentProcess.arrivalTime;
            results.push_back(currentProcess);
        }
    }
    for (Process& finalProcess : results) {
        finalProcess.waitingTime = finalProcess.turnaroundTime - finalProcess.burstTime;
    }
}
int main() {
    int numProcesses, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the time quantum for Round Robin (in ms): ";
    cin >> timeQuantum;
    queue<Process> processesQueue;
    vector<Process> results;
    for (int i = 1; i <= numProcesses; i++) {
        Process process;
        process.id = i;
        cout << "Enter arrival time for Process " << i << " (in ms): ";
        cin >> process.arrivalTime;
        cout << "Enter burst time for Process " << i << " (in ms): ";
        cin >> process.burstTime;
        process.remainingTime = process.burstTime;
        process.startTime = -1;
        process.finishTime = -1;
        process.waitingTime = 0;
        process.turnaroundTime = 0;
        processesQueue.push(process);
    }
    cout << "\nSimulation Start:\n\n";
    executeRoundRobin(processesQueue, timeQuantum, results);
    cout << "\nSimulation End."<<endl;
    cout<<"Results:"<<endl;
    cout<<endl;
    sort(results.begin(), results.end(), compareById);
    for (const Process& finalProcess : results) {
        cout << "Process " << finalProcess.id 
             << " Arrival Time: " << finalProcess.arrivalTime << " ms"
             << " Burst Time: " << finalProcess.burstTime << " ms"<< " - Start Time: " << finalProcess.startTime << " ms"
             << " Waiting Time: " << finalProcess.waitingTime << " ms Finish Time: " << finalProcess.finishTime << " ms"
             << " Turnaround Time: " << finalProcess.turnaroundTime << " ms" << endl;
    }
    return 0;
}