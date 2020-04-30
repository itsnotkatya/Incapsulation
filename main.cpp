//1. Продемонстрировать различные уровни инкапсуляции данных (указать комментарием):
//a. Отсутствие инкапсуляции (public свойства) +
//b. Инкапсуляция с помощью set/get +
//c. Инкапсуляция с помощью специализированных протоколов/методов
//d. Инкапсуляция за счёт абстракций
//
//
//2. Продемонстрировать различные варианты инкапсуляции поведения
//a. За счёт позднего связывания +
//b. Замена поведения (тут тоже используется позднее связывание) ++
//c. Расширения поведения (тут тоже используется позднее связывание) +

#include <iostream>
enum Pizza { Pepperoni, Hawaiian, FourCheese};
class Pizzeria {
protected:
    std::string Order;
    int Price;
    Pizza pizza;
protected:
    const std::string StuffName;
public:
    std::string Adress;                         //отсутсвие инкапсуляции

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

    virtual void setPrice(Pizza pizza, int price) {                                           //инкапсуляция через позднее связывание
        this -> Price = price;
        std::cout << price << std::endl;
    };
    int getPrice() { return Price; };

    virtual void MakeOrder(Pizza  pizza) {
        switch (pizza) {
            case 0: setPrice(Pepperoni,200);
                break;
            case 1: setPrice(Hawaiian,250);
                break;
            case 2: setPrice(FourCheese,300);
                break;
        }
    }

    void callStuff (std::string StuffName) const {                                                //расширение поведения
        std::cout << "My name is " << StuffName << ". How can I help you?" << std::endl;
    }
    virtual const char* getStuffName(int x) { return "Nick"; }
};

class Guest : public Pizzeria {
protected:
    std::string VisitorsName;

public:
    Guest(std::string Order, int Price, std::string VisitorsName) : Pizzeria (Order, Price, pizza) {
        this -> VisitorsName = VisitorsName;
    };

    std::string getVisitorsName() { return VisitorsName; };                                    //инкапсуляция с помощью геттера
    void setVisitorsName(std::string VisitorsName) { this -> VisitorsName = VisitorsName; };   //инкапсуляция с помощью сеттера


    virtual const char* getStuffName(int x) override { return "Bill"; }                        //замена поведения

};

class Superiors : public Pizzeria {                                                            //инкапсуляция с помощью абстракции
private:
    std::string OwnerName;
    std::string ChiefName;
public:
    Superiors (std::string Adress, std::string OwnerName, std::string ChiefName) : Pizzeria(Adress) {
        this -> OwnerName = OwnerName;
        this -> ChiefName = ChiefName;
    }
    void InitOwner (std::string owner_name, int owner_age) {
        Superiors :: OwnerName = owner_name;
    };
    void InitAge (std::string chief_name, int chief_age) {
        Superiors :: ChiefName = chief_name;

    };
};

int main() {
    Pizzeria PizzaHut("Green ave, 113");
    int ord;
    std::cout << "Hello, Pizza!" << std::endl;
    //std::cout << "Choose pizza " << std::endl;
    //std::cin >> ord;

    PizzaHut.setPrice(Pepperoni,100);  //позднее связывание

   /* switch(ord) {
        case 0: PizzaHut.MakeOrder(Pepperoni);
            break;
        case 1: PizzaHut.MakeOrder(Hawaiian);
            break;
        case 2: PizzaHut.MakeOrder(FourCheese);
            break;
        case 3: PizzaHut.callStuff("Nick");
            break;
    }
    std::cout << "Your order is " << ord << std::endl; */

    return 0;
}