#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class Item {
	public : 
		Item() : name_(""), price_(0) {};
		Item(const string& name, int price) : name_(name), price_(price) {};
		const string& GetName() const {
			return name_;
		};
		int getPrice() const {
			return price_;
		};
		void printInfo() const {
			cout << "[이름: " << name_ << ", 가격: " << price_ << "G}" << endl;
		};
	private:
		string name_;
		int price_;
};

bool compareItems(const Item& item1, const Item& item2) {
	return item1.getPrice() < item2.getPrice();
}

template <typename T>
class Inventory {
public : 
	Inventory(int capacity = 10) : capacity_(capacity), size_(0) {
		if (capacity_ <= 0) {
			capacity_ = 1;
		}
		items_ = new T[capacity_];
	};

	Inventory(const Inventory& other){
		capacity_ = other.capacity_;
		size_ = other.size_;
		items_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			items_[i] = other.items_[i];
		}
	}
	~Inventory() {
		delete[] items_;
		items_ = nullptr;
	}

	void addItem(const T& item) {
		if (size_ >= capacity_) {
			Resize(capacity_ * 2);
		}
		items_[size_] = item;
		size_++;
	};

	void RemoveItem() {
		if (size_ > 0) {
			size_--;
		}
	};
	int getSize() const {
		return size_;
	}
	int getCapacity() const {
		return capacity_;
	}
	void PrintAllItems() const {
		cout << "인벤토리 아이템: " << endl;
		for (int i = 0; i < size_; ++i) {
			items_[i].printInfo();
		}
		if (size_ == 0) {
			cout << "인벤토리가 비어 있습니다." << endl;
		}
	};

	void Resize(int newCapacity) {
		if (newCapacity <= capacity_) {
			cout << "새로운 용량은 현재 용량보다 커야 합니다. 현재 용량: " << capacity_ << endl;
			return;
		}
		T* newItems = new T[newCapacity];
		for (int i = 0; i < size_; ++i) {
			newItems[i] = items_[i];
		}
		delete[] items_;
		items_ = newItems;
		capacity_ = newCapacity;
	}
	
	void SortItems() {
		if (size_ == 0) {
			cout << "인벤토리가 비어 있어 정렬할 아이템이 없습니다." << endl;
			return;
		}
		sort(items_, items_ + size_, compareItems);
	};

private:
	T* items_;
	int capacity_;
	int size_;
};

void InventoryMenu(Inventory<Item>* inventory) {
	while (true) {
		cout << "인벤토리 관리 시스템" << endl;
		cout << "1. 아이템 추가" << endl;
		cout << "2. 아이템 제거" << endl;
		cout << "3. 모든 아이템 출력" << endl;
		cout << "4. 인벤토리 확장" << endl;
		cout << "5. 아이템 정렬" << endl;
		cout << "6. 인벤토리 복제" << endl;
		cout << "7. 종료" << endl;

		int choice;
		if (!(cin >> choice)) {
			cout << "오류: 숫자를 입력해주세요." << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		if (choice == 1) {
			while (true) {
				string name;
				int price;
				cout << "아이템 이름을 입력하세요(입력을 중지하시려면 0) : ";
				if (!getline(cin, name) || name == "0") {
					break;
				}
				cout << "아이템 가격을 입력하세요 : ";
				cin >> price;
				if (cin.fail()) {
					cout << "오류: 숫자만 입력 가능합니다!" << std::endl;
					cin.clear();
					cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

				Item item(name, price);
				inventory->addItem(item);
				cout << "아이템이 추가되었습니다." << endl;
				item.printInfo();
			}
		}
		else if (choice == 2) {
			inventory->RemoveItem();
			cout << "아이템이 제거되었습니다." << endl;
		}
		else if (choice == 3) {
			inventory->PrintAllItems();
			cout << "현재 용량 : " << inventory->getCapacity() << endl;
		}
		else if (choice == 4) {
			int newCapacity;
			cout << "새로운 인벤토리 용량을 입력하세요 : ";
			cin >> newCapacity;
			if (cin.fail()) {
				cout << "오류: 숫자만 입력 가능합니다!" << std::endl;
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
				break;
			}
			inventory->Resize(newCapacity);
			cout << "인벤토리가 확장되었습니다. 현재 용량 : " << inventory->getCapacity() << endl;
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (choice == 5) {
			inventory->SortItems();
			cout << "아이템이 가격순으로 정렬되었습니다." << endl;
		}
		else if (choice == 6) {
			Inventory<Item>* copiedInventory = new Inventory<Item>(*inventory);
			cout << "인벤토리가 복제되었습니다. 복제된 인벤토리의 아이템: " << endl;
			copiedInventory->PrintAllItems();
			delete copiedInventory;
		}
		else if (choice == 7) {
			cout << "프로그램을 종료합니다." << endl;
			break;
		}
		else {
			cout << "잘못된 선택입니다. 다시 시도해주세요." << endl;
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

	}
}

int startInventorySystem() {
	cout << "인벤토리 관리 시스템에 오신 것을 환영합니다!" << endl;
	cout << "인벤토리 용량을 입력해주세요" << endl;
	int capacity;
	cin >> capacity;
	if (cin.fail()) {
		cout << "오류: 숫자만 입력 가능합니다!" << std::endl;
		cout << "기본 용량 10으로 설정됩니다." << endl;
	}
	cin.clear();
	cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

	return capacity > 0 ? capacity : 10;
}

int main() {

	Inventory<Item>* inventory = new Inventory<Item>(startInventorySystem());

	InventoryMenu(inventory);

	delete inventory;

	return 0;
}
