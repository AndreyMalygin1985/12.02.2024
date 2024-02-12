#include <iostream>
#include <Windows.h>

using namespace std;

class Claim {
private:
	string typeOfClaim;
	string from;
	double amountOfMoney;
public:
	Claim(string type = "", string from_ = "", double amountM = 0.0) : typeOfClaim(type), from(from_), amountOfMoney(amountM) {}
	~Claim() {}

	string GetTypeOfClaim() const { return typeOfClaim; }
	string GetFrom() const { return from; }
	double GetAmountOfMoney() const { return amountOfMoney; }

	void SetTypeOfClaim(string type) { typeOfClaim = type; }
	void SetFrom(string from_) { typeOfClaim = from_; }
	void SetAmountOfMoney(double amountM) { typeOfClaim = amountM; }
};

class Manager {
protected:
	Manager* pSuccesor;
public:
	void SetSuccesor(Manager* pTemp) {
		pSuccesor = pTemp;
	}

	virtual void Process(const Claim& request) = 0;
	virtual ~Manager() {}
};

class LocalManager :public Manager {
	LocalManager() {}
	~LocalManager() {}

	void Process(const Claim& request) {
		if (request.GetAmountOfMoney() < 10000.0) {
			cout << "Ваш запрос был одобрен менеджером местного филиалаю Вот информация " << endl;
			cout << request.GetTypeOfClaim() << " " << request.GetFrom() << " " << request.GetAmountOfMoney();
		}
		else {
			pSuccesor->Process(request);
		}
	}
};

class RegionalManager : public Manager {
public:
	RegionalManager() {}
	~RegionalManager() {}
	void Process(const Claim& request) {
		if (request.GetAmountOfMoney() < 10000.0) {
			cout << "Ваш запрос был одобрен менеджером местного филиалаю Вот информация " << endl;
			cout << request.GetTypeOfClaim() << " " << request.GetFrom() << " " << request.GetAmountOfMoney();
		}
		else {
			pSuccesor->Process(request);
		}
	}
};

class CEO :public Manager {
public:
	CEO() {}
	~CEO() {}

	void Process(const Claim& request) {
		if (request.GetAmountOfMoney() < 100000.0) {
			cout << "Ваш запрос был одобрен менеджером местного филиалаю Вот информация " << endl;
			cout << request.GetTypeOfClaim() << " " << request.GetFrom() << " " << request.GetAmountOfMoney();
		}
		else {
			cout << "Простите мы ни чем не можем вам помочь " << endl;
		}
	}
};

int main()
{
	SetConsoleOutputCP(1251);

	Manager* vasya = new LocalManager();
	Manager* sveta = new RegionalManager();
	Manager* petya = new CEO();

	vasya->SetSuccesor(sveta);
	sveta->SetSuccesor(petya);

	Claim first("Об обслуживании", "Даша", 500.0);
	vasya->Process(first);
	Claim second("О службе поддержки клиентов", "Игнат", 5000.0);
	vasya->Process(second);
	Claim third("Об интернете", "Славон", 50000.0);
	vasya->Process(third);
	Claim fourth("Об авариях", "Михуил", 150000.0);
	vasya->Process(fourth);

	delete vasya;
	delete sveta;
	delete petya;



	return 777;
}