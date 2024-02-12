#include <iostream>
#include <Windows.h>
#include <map>
#include <unordered_map>

using namespace std;

struct SharedState {
	string brand_;
	string model_;
	string color_;

	SharedState(const string& brand, const string& model, const string& color) :brand_(brand), model_(model), color_(color) {}

	friend ostream& operator<<(ostream& os, const SharedState& ss) {
		return os << "[ " << ss.brand_ << " , " << ss.model_ << " , " << ss.color_ << " ]";
	}
};

struct UniqueState {
	string owner_;
	string PTS_;

	UniqueState(const string& owner, const string& PTS) :owner_(owner), PTS_(PTS) {}

	friend ostream& operator<<(ostream& os, const UniqueState& ss) {
		return os << "[ " << ss.owner_ << " , " << ss.PTS_ << " ]";
	}
};

class Flyweight {
private:
	SharedState* shared_state_;
public:
	Flyweight(const SharedState* shared_state) : shared_state_(new SharedState(*shared_state)) {}
	Flyweight(const Flyweight& other) : shared_state_(new SharedState(*other.shared_state_)) {}
	~Flyweight() {
		delete shared_state_;
	}

	SharedState* shared_state_() const {
		return shared_state_;
	}

	void Operation(const UniqueState& unique_state) const {
		cout << "Flyweight: Отображение общего (" << *shared_state_ << ") и уникального(" << unique_state << ") состояния.\n";
	}
};

class FlyweightFactory {
private:
	unordered_map<string, Flyweight> flyweights_;
	string GetKey(const SharedState& ss) const {
		return ss.brand_ + "_" + ss.model_ + "_" + ss.color_ + "_";
	}	
public:
	FlyweightFactory(initializer_list<SharedState> shared_states) {
		for (const SharedState& ss:shared_states)
		{
			this->flyweights_.insert(make_pair<string, Flyweight>(this->GetKey(ss), Flyweight(&ss)));
		}
	}

	Flyweight GetFlyweight(const SharedState& shared_state) {
		string key = this->GetKey(shared_state);
		if (this ->flyweights_.find(key) == this->flyweights_.end())
		{
			cout << "FlyweightFactory: не удалось найти flyweights, создаю новый." << endl;
			this->flyweights_.insert(make_pair(key, Flyweight(&shared_state)));
		}
		else
		{
			cout << "FlyweightFactory: Повторное использование существующего FlyweightFactory" << endl;
		}
		return this->flyweights_.at(key);
	}

	void ListFlyweights() const {
		size_t count = this->flyweights_.size();

		cout << "FlyweightFactory: у меня есть " << count << "flyweights: " << endl;
		for (pair<string, Flyweight> pair: this->flyweights_)
		{
			cout << pair.first << endl;
		}
	}
};

void AddCatToPoliceDB(FlyweightFactory& ff, const string& PTS, const string& owner, const string& brand, const string& model, const string& color) {
	cout << "Клиент: Добавили автомобиль в базу данных" << endl;
	const Flyweight& flyweight = ff.GetFlyweight({ brand, model, color });
	flyweight.Operation({ owner,PTS });
}

int main()
{
	SetConsoleOutputCP(1251);

	FlyweightFactory& factory = new FlyweightFactory({
		{"Chevrolete","Camaro2018","pink"},
		{"Nersedes Benz","C300","black"},
		{"Nersedes Benz","C500","red"},
		{"BMW","M5","red"},
		{"BMW","X6","white"}
		});

	factory->ListFlyweights();
	AddCatToPoliceDB(*factory, "Chevrolete", "Camaro2018", "pink", "Вася", "FJGIPU9334");
	AddCatToPoliceDB(*factory, "BMW", "M5", "red", "Вася", "SGDDD1234");

	delete factory;

	return 777;
}