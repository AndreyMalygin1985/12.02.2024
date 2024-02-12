#include <iostream>
#include <Windows.h>

using namespace std;

//Reciver

class TV {
private:
	bool on;
public:
	void TurnOn() {
		cout << "Я включился";
		on = true;
	}
	void TurnOff() {
		cout << "Я выключился";
		on = false;
	}
};

//Command

class TVCommand {
protected:
	TV* tvPlayer = nullptr;
public:
	TVCommand(TV* pTv) {
		tvPlayer = pTv;
	}
	virtual void Execute() = 0;
};

class TVOnCommand : public TVCommand {
public:
	TVOnCommand(TV* ptr) :TVCommand(ptr) {}

	void Execute() {
		if (tvPlayer) {
			tvPlayer->TurnOn();
		}
	}
};

class RemoteControl {
private:
	TVCommand* command;
public:
	void SetCommand(TVCommand* pCommand) {
		command = pCommand;
	}
	void PressButtom() {
		command->Execute();
	}
};

int main()
{
	SetConsoleOutputCP(1251);

	RemoteControl control;
	TV* concerteTV = new TV();

	TVCommand* tvOn = new TVOnCommand(concerteTV);
	TVCommand* tvOff = new TVOffCommand(concerteTV);




	return 777;
}