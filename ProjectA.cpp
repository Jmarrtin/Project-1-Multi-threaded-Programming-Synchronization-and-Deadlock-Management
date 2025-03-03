// projectA.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

// Phase 1
void carBasicOperation(int carId) {
    cout << "Car " << carId << " is starting its journey." << endl;
    // Simulate driving work
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "Car " << carId << " is driving." << endl;
}

void runPhase1() {
    cout << "=== Phase 1: Basic Thread Operations ===" << endl;
    vector<thread> carThreads;
    for (int i = 0; i < 10; i++) {
        carThreads.push_back(thread(carBasicOperation, i + 1));
    }
    for (auto &t : carThreads) {
        t.join();
    }
    cout << "Phase 1 completed.\n" << endl;
}

// Phase 2: Resource Protection (Gas Station)
mutex gasStationMutex;

void refuelAtGasStation(int carId) {
    cout << "Car " << carId << " is waiting for gas station access." << endl;
    {
        lock_guard<mutex> lock(gasStationMutex);
        cout << "Car " << carId << " is refueling at the gas station." << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
        cout << "Car " << carId << " has finished refueling." << endl;
    }
}

void runPhase2() {
    cout << "=== Phase 2: Resource Protection (Gas Station) ===" << endl;
    vector<thread> carThreads;
    for (int i = 0; i < 10; i++) {
        carThreads.push_back(thread(refuelAtGasStation, i + 1));
    }
    for (auto &t : carThreads) {
        t.join();
    }
    cout << "Phase 2 completed.\n" << endl;
}

// Phase 3: Deadlock Creation (Bridges Scenario) 
mutex bridgeAMutex;
mutex bridgeBMutex;

// This function simulates a car that must lock two bridges.
// The parameter 'reverseOrder' determines the order in which the locks are acquired.
void carDeadlockScenario(int carId, bool reverseOrder) {
    if (reverseOrder) {
        cout << "Car " << carId << " attempting to lock Bridge B." << endl;
        bridgeBMutex.lock();
        // Simulate delay
        this_thread::sleep_for(chrono::milliseconds(50));
        cout << "Car " << carId << " attempting to lock Bridge A." << endl;
        bridgeAMutex.lock();
    } else {
        cout << "Car " << carId << " attempting to lock Bridge A." << endl;
        bridgeAMutex.lock();
        // Simulate delay
        this_thread::sleep_for(chrono::milliseconds(50));
        cout << "Car " << carId << " attempting to lock Bridge B." << endl;
        bridgeBMutex.lock();
    }
    
    cout << "Car " << carId << " is passing through both bridges." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
    
    // Release both locks
    bridgeAMutex.unlock();
    bridgeBMutex.unlock();
}

void runPhase3() {
    cout << "=== Phase 3: Deadlock Creation (Bridges Scenario) ===" << endl;
    vector<thread> carThreads;
    // Launch threads with different lock orders (this may deadlock)
    for (int i = 0; i < 5; i++) {
        carThreads.push_back(thread(carDeadlockScenario, i + 1, false));
        carThreads.push_back(thread(carDeadlockScenario, i + 6, true));
    }
    // Warning: This phase might hang if a deadlock occurs.
    for (auto &t : carThreads) {
        t.join();
    }
    cout << "Phase 3 completed.\n" << endl;
}

// Phase 4: Deadlock Resolution 
void carDeadlockResolved(int carId) {
    cout << "Car " << carId << " attempting to lock both bridges safely." << endl;
    // Use std::lock to lock both mutexes without risk of deadlock
    std::lock(bridgeAMutex, bridgeBMutex);
    // Create lock guards adopting the already-locked mutexes
    lock_guard<mutex> lockA(bridgeAMutex, adopt_lock);
    lock_guard<mutex> lockB(bridgeBMutex, adopt_lock);
    
    cout << "Car " << carId << " is passing through both bridges safely." << endl;
    this_thread::sleep_for(chrono::milliseconds(100));
}

void runPhase4() {
    cout << "=== Phase 4: Deadlock Resolution ===" << endl;
    vector<thread> carThreads;
    for (int i = 0; i < 10; i++) {
        carThreads.push_back(thread(carDeadlockResolved, i + 1));
    }
    for (auto &t : carThreads) {
        t.join();
    }
    cout << "Phase 4 completed.\n" << endl;
}

// Menu 
int main() {
    // Choose phases to run (for demonstration, all phases are executed sequentially)
    runPhase1();
    runPhase2();

    // WARNING: runPhase3 may lead to a deadlock; you can comment it out after testing.
    cout << "Starting Phase 3 (Deadlock Creation). This phase may hang if a deadlock occurs." << endl;
    // Uncomment the next line to test deadlock behavior.
    // runPhase3();

    // For a safe demonstration, we run Phase 4 (Deadlock Resolution) instead.
    runPhase4();
    
    cout << "Multi-threaded Car Simulation completed." << endl;
    return 0;
}
