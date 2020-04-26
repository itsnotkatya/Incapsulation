#include <iostream>
enum Pizza { Pepperoni, Hawaiian, FourCheese};
class Pizzeria {
protected:
    std::string Order;
    int Price;
    Pizza pizza;
public:
    std::string Adress;
    std::string StuffName;               //отсутсвие инкапсуляции

    Pizzeria(std::string Adress) {
        this -> Adress = Adress;
    }

    Pizzeria (std::string Order, int Price, Pizza pizza) {
        this -> Order = Order;
        this -> Price = Price;
        this -> pizza = pizza;
    }

    void setOrder(std::string order) { this -> Order = order; };
    std::string getOrder() { return Order; };

    virtual void setPrice(int price) {
        this -> Price = price;
        std::cout << price << std::endl;
    };
    int getPrice() { return Price; };


    void TellAdress (std::string Adress) {                  //ранее связывание
        std::cout << "Pizzeria's addres is " << Adress;
    }

    virtual void MakeOrder(Pizza  pizza) {                 //позднее связывание
        switch (pizza) {
            case 0: setPrice(200);
                break;
            case 1: setPrice(250);
                break;
            case 2: setPrice(300);
                break;
        }

    }

    void callStuff (std::string StuffName) {
        std::cout << "My name is " << StuffName << ". How can I help you?" << std::endl;
    }
};

class Guest : public Pizzeria {
protected:
    std::string VisitorsName;
    int CardNumber;
public:
    Guest(std::string Order, int Price, std::string VisitorsName, int CardNumber) : Pizzeria (Order, Price, pizza) {
        this -> CardNumber = CardNumber;
        this -> VisitorsName = VisitorsName;
    };

    int getCardNumber() { return CardNumber; };                                //инкапсуляция с помощью геттера
    void setCardNumber(int CardNumber) { this -> CardNumber = CardNumber; };   //инкапсуляция с помощью сеттера

    std::string getVisitorsName() { return VisitorsName; };
    void setVisitorsName(std::string VisitorsName) { this -> VisitorsName = VisitorsName; };

    void setPrice(int Price) override {                                        //расширение поведения
        Price = 0;
    }
};

class Superiors {
private:
    std::string OwnerName;
    int OwnerAge;
    std::string ChiefName;
    int ChiefAge;
public:
    void InitOwner (std::string owner_name, int owner_age) {            //инкапсуляция с помощью абстракции
        Superiors :: OwnerName = owner_name;
        Superiors :: OwnerAge = owner_age;
    };
    void InitAge (std::string chief_name, int chief_age) {
        Superiors :: ChiefName = chief_name;
        Superiors :: ChiefAge = chief_age;
    };
};

int main() {
    Pizzeria PizzaHut("Green ave, 113");
    int ord;
    std::cout << "Hello, Pizza!" << std::endl;
    std::cout << "Choose pizza " << std::endl;
    std::cin >> ord;
                                                                      //позднее связывание
    switch(ord) {
        case 0: PizzaHut.MakeOrder(Pepperoni);
            break;
        case 1: PizzaHut.MakeOrder(Hawaiian);
            break;
        case 2: PizzaHut.MakeOrder(FourCheese);
            break;
        case 3: PizzaHut.callStuff("Nick");
            break;
    }
    std::cout << "Your order is " << ord << std::endl;

    return 0;
}