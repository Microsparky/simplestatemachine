// SimpleStateMachine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu


#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

// define a structure similar to packet
struct packet {
	int len;
	int cmd;
	int data[16];
	int status;
};

// declare packet as global
packet usb_packet;

// define a state function type
typedef void state_fn(struct state*);

// define a state structure
struct state
{
	string name;
	state_fn *next;		// equivilant to void (*next)(struct state*);
};

// Declare states
state_fn idle, start, run, stop;		// equivilant to void idle(struct state*); void run(struct state*);

// State function: Idle
void idle(struct state * state)
{
	(*state).name = "Idle";

	cout << "State: " << (*state).name << endl;
	cin >> usb_packet.cmd;

	if (usb_packet.cmd == 1) {
		(*state).next = start;
	}
	else {
		(*state).next = idle;
	}
}

// State function: Start
void start(struct state * state)
{
(*state).name = "Start";

	cout << "State: " << (*state).name << endl;
	cin >> usb_packet.cmd;

	if (usb_packet.cmd == 0) {
		(*state).next = stop;
	}
	else {
		(*state).next = run;
	}
}

// State function: Run
void run(struct state * state)
{
	(*state).name = "Run";

	cout << "State: " << (*state).name << endl;
	cin >> usb_packet.cmd;

	if (usb_packet.cmd == 0) {
		(*state).next = stop;
	}
	else {
		(*state).next = run;
	}
}

// State function: Stop
void stop(struct state * state)
{
	(*state).name = "Stop";

	cout << "State: " << (*state).name << endl;
	cin >> usb_packet.cmd;

	if (usb_packet.cmd == 0) {
		(*state).next = idle;
	}
	else {
		(*state).next = start;
	}
}
int main(void)
{
	// Declare the current state and set state.next (a function pointer) to the address of foo and state.i to 0
	struct state state = { "Idle", idle };

	// while the next function is not null
	while (state.next) {
		// call the state.next function with argument &state (the current state)
		state.next(&state);
	}
}