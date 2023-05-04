#include<iostream>
using namespace std;

struct Product {
	char* name;
	double discount;
	double price;
	int quantity;
};

struct Store {
	char* Address;
	Product** products;
	int count = 0;
};

void ShowMenu() {
	cout << "=====================" << endl;
	cout << "Show All Products [1]" << endl;
	cout << "Add New Products  [2]" << endl;
	cout << "Delete products   [3]" << endl;
	cout << "Buy products      [4]" << endl;
}


void ShowProducts(const Product& product) {
	cout << "NAME : " << product.name << endl;
	cout << "PRICE : " << product.price << endl;
	cout << "DISCOUNT : " << product.discount * 100 << " % " << endl;
	cout << "QUANTITY : " << product.quantity << endl;
	cout << endl;
}

void ShowAllProducts(const Store& store) {
	cout << "- - - - Products - - - -" << endl;
	for (size_t i = 0; i < store.count; i++)
	{
		cout << "NO : " << i + 1 << endl;
		ShowProducts(*store.products[i]);
	}
}

Product* GetNewProduct() {
	cin.ignore();
	cin.clear();
	cout << "Enter product name : " << endl;
	char* name = new char[30] {};
	cin.getline(name, 30);
	cout << "Enter discount : " << endl;
	double discount = 0;
	cin >> discount;
	cout << "Enter price " << endl;
	double price = 0;
	cin >> price;
	Product* product = new Product{ name,discount,price };
	return product;
}

void AddNewProduct(Store& store, Product* product) {
	auto temp = new Product * [store.count + 1] {};
	for (size_t i = 0; i < store.count; i++)
	{
		temp[i] = store.products[i];
	}
	temp[store.count] = product;
	store.products = temp;
	temp = nullptr;
	store.count++;
}

void DeleteProductByID(Store& store, int index) {
	auto newproduct = new Product * [store.count - 1] {};
	for (size_t i = 0; i < index; i++)
	{
		newproduct[i] = store.products[i];
	}
	for (size_t i = index + 1; i < store.count; i++)
	{
		newproduct[i - 1] = store.products[i];
	}
	store.products = newproduct;
	newproduct = nullptr;
	store.count--;
}

void IncreasePrice(Product& product, int quantity) {
	if (quantity >= product.quantity / 2) {
		product.price += 0.3;
	}
	else if (quantity >= product.quantity / 3) {
		product.price += 0.1;
	}
}

void BuyProduct(Product& product, int quantity) {
	if (quantity < product.quantity) {
		product.quantity -= quantity;
		cout << "Product bought successfully " << endl;
	}
	else {
		cout << "There are not enough product counts" << endl;
	}
}

void main() {

	Product* p1 = new Product{ new char[30] {"Coca Cola"},0.3,1.5,300 };
	Product* p2 = new Product{ new char[30] {"Fuse Tea"},0.1,1.2,230 };
	Product* p3 = new Product{ new char[30] {"Red Bull"},0.4,3.6,100 };

	Product** products = new Product * [3] {p1, p2, p3};

	Store* store = new Store{ new char[30] {"Yasamal"},products,NULL };
	store->count = 3;

	while (true)
	{
		ShowMenu();
		int select = 0;
		cin >> select;
		system("cls");
		if (select == 1) {
			ShowAllProducts(*store);
		}
		else if (select == 2) {
			auto newproduct = GetNewProduct();
			AddNewProduct(*store, newproduct);
			cout << newproduct->name << " added successfully" << endl;
		}
		else if (select == 3) {
			ShowAllProducts(*store);
			cout << "Enter Product ID : " << endl;
			int no = 0;
			cin >> no;
			int index = no - 1;
			DeleteProductByID(*store, index);
			cout << "Product deleted successfully" << endl;
		}
		else if (select == 4) {
			ShowAllProducts(*store);
			cout << "Enter Product ID : ";
			int no = 0;
			cin >> no;
			int index = no - 1;
			cout << "Enter quantity : ";
			int quantity = 0;
			cin >> quantity;
			auto product = store->products[index];
			BuyProduct(*product, quantity);
			IncreasePrice(*product, quantity);
		}
	}
}
