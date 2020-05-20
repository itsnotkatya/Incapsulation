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

//1. Смоделировано некорректно. Вы используете Наследование Гостя от Пиццерии. Между гостем и пиццерией явно другое отношение.
//2. Не нашёл демонстрации инкапсуляции с помощью абстракции. Для этого создаётся функция/метод, которая на вход ожидает абстракцию, а по факту получает какую-то реализацию
//Показать часть

#include <iostream>
enum Pizza { Pepperoni, Hawaiian, FourCheese};
enum NewPizza {Bulgarian, Russian, Vegeterian};
class Pizzeria {
protected:
    std::string Order;
    int Price;
    Pizza pizza;
public:
    std::string Adress;                         //отсутсвие инкапсуляции
    std::string StuffName;

    Pizzeria(const char *Adress) {
        this -> Adress = Adress;
    }

    Pizzeria (std::string Order, int Price, Pizza pizza) {
        this -> Order = Order;
        this -> Price = Price;
        this -> pizza = pizza;
    }

    void setOrder(std::string order) {
        this -> Order = order;
    };
    std::string getOrder() {
        return Order;
    };

    virtual void sayAdress(std::string Adress)  {
        std::cout << "Our Adress is ";

    };

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
    virtual std::string getStuffName() {
        return (const std::basic_string<char> &) "Nick";
    }

};

class Guest  {
protected:
    std::string VisitorsName;
public:
    Guest(std::string VisitorsName)  {
        this -> VisitorsName = VisitorsName;
    };

    std::string getVisitorsName() { return VisitorsName; };                                    //инкапсуляция с помощью геттера
    void setVisitorsName(std::string VisitorsName) { this -> VisitorsName = VisitorsName; };   //инкапсуляция с помощью сеттера


};

class Superiors : public Pizzeria {
private:
    std::string OwnerName;
    std::string ChiefName;
public:
    Superiors (Pizzeria Adress, const char *OwnerName, const char *ChiefName) : Pizzeria (Adress) {
        this -> OwnerName = OwnerName;
        this -> ChiefName = ChiefName;
    }
    void InitOwner (std::string owner_name, int owner_age) {
        Superiors :: OwnerName = owner_name;
    };
    void InitAge (std::string chief_name, int chief_age) {
        Superiors :: ChiefName = chief_name;
    };

    virtual std::string getStuffName() override {
       StuffName = "John" ;
    };                                                               //замена поведения

    void OpenNewPizzeria (Pizzeria &p) {                             //инкапсуляция с помощью абстракции
        p.Adress = "Green ave, 256";
        NewPizza pizza;
        p.sayAdress(p.Adress);
        StuffName = "Margarita";
    }
};

int main() {
    Pizzeria PizzaHut("Green ave, 113");
    int ord;
    std::cout << "Hello, Pizza!" << std::endl;
    std::cout << "Choose pizza " << std::endl;
    std::cin >> ord;

    PizzaHut.setPrice(Pepperoni,100);  //позднее связывание

    switch(ord) {
        case 0: PizzaHut.MakeOrder(Pepperoni);
            break;
        case 1: PizzaHut.MakeOrder(Hawaiian);
            break;
        case 2: PizzaHut.MakeOrder(FourCheese);
            break;
        case 3: PizzaHut.callStuff((const std::basic_string<char> &) "Nick");
            break;
    }
    std::cout << "Your order is " << ord << std::endl;

    Superiors NewPizzeria ("Green ave, 113","John","Peter");
    NewPizzeria.OpenNewPizzeria(PizzaHut);              //инкапсуляция с помощью абстракции - создан объект дочернего класса,
                                                           //вызвана функция этого класса, которая ожидает на вход ссылку на род. класс
                                                           //и внутри вызывает виртуальный метод род. класса
    return 0;
}