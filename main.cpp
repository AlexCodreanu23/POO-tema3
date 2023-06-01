#include <iostream>
#include <string>
#include <exception>
using namespace std;

class aExceptie : public std::exception{
private:
    std::string mesaj1;
public:
    aExceptie(){mesaj1 = "Aceasta marime nu este valida";}
    const char* what() const throw(){
        return mesaj1.c_str();
    }
};

class bExceptie : public std::exception{
private:
    std::string mesaj2;
public:
    bExceptie(){mesaj2 = "Acest gender nu exista";}
    const char* what() const throw(){
        return mesaj2.c_str();
    }
};


template <typename T>
class Id {
private:
    static int lastid;
    int id;
public:
    Id() : id(lastid++) {}

    int getId() const {
        return id;
    }
};
template<typename T>
int Id<T>::lastid = 0;


class Clothing{
private:
    std::string gender;
    std::string season;
    std::string brand;
public:

    Clothing(){}

    const string &getGender() const {
        return gender;
    }

    void setGender(const string &gender) {
        Clothing::gender = gender;
    }

    const string &getSeason() const {
        return season;
    }

    void setSeason(const string &season) {
        Clothing::season = season;
    }

    const string &getBrand() const {
        return brand;
    }

    void setBrand(const string &brand) {
        Clothing::brand = brand;
    }

    bool operator==(const Clothing &rhs) const {
        return gender == rhs.gender &&
               season == rhs.season &&
               brand == rhs.brand;
    }

    bool operator!=(const Clothing &rhs) const {
        return !(rhs == *this);
    }

    virtual std::ostream& print(std::ostream& os) const {
        os << "gender: " << gender << " season: " << season << " brand: " << brand;
        return os;
    }

    friend std::ostream& operator<<(std::ostream& os, const Clothing& clothing) {
        return clothing.print(os);
    }

    friend std::istream &operator>>(std::istream &is, Clothing &clothing){
        std::string gender;
        std::string season;
        std::string brand;

        is >> gender;
        if(gender != "male" && gender != "female")
            throw bExceptie();
        is >> season >> brand;
        clothing.setGender(gender);
        clothing.setSeason(season);
        clothing.setBrand(brand);

    }

    virtual void display() const {
        std::cout << "Gender: " << getGender() << std::endl
                  << "Season: " << getSeason() << std::endl
                  << "Brand: " << getBrand() << std::endl;
    }

    virtual void processFunction() const {
        std::cout << "This is a common function for all clothing items." << std::endl;
    }


    virtual Clothing* clone() const {
        return new Clothing(*this);
    }

    virtual ~Clothing() {

    }

};


class Tshirt : public Clothing, public Id<Tshirt>{
private:
    std::string design;
    int marime;
public:

    const string &getDesign() const {
        return design;
    }

    void setDesign(const string &design) {
        Tshirt::design = design;
    }

    int getMarime() const {
        return marime;
    }

    void setMarime(int marime) {
        Tshirt::marime = marime;
    }

    friend std::istream &operator>>(std::istream &is, Tshirt &tshirt) {
        is >> static_cast<Clothing&>(tshirt);
        is >> tshirt.design;
        is >> tshirt.marime;
        if(tshirt.marime < 92)
        {
            throw aExceptie();
        }
        return is;
    }

    void display() const override {
        Clothing::display();
        std::cout<< "Design: " <<getDesign() << " Marime: "<<getMarime() <<std::endl;
    }

    void specificFunction() const {
        std::cout << "This is a function specific to T-shirts." << std::endl;
    }

    Tshirt* clone() const override {
        return new Tshirt(*this);
    }

    ~Tshirt() override {

    }
};

class Pants : public Clothing, public Id<Pants>{
private:
    std::string type;
public:

    const string &getType() const {
        return type;
    }

    void setType(const string &type) {
        Pants::type = type;
    }

    friend std::istream &operator>>(std::istream &is, Pants &pants) {
        is >> static_cast<Clothing&>(pants);
        is >> pants.type;
        return is;
    }

    void display() const override {
        Clothing::display();
        std::cout<< "Type: " <<getType() <<std::endl;
    }

    Pants* clone() const override {
        return new Pants(*this);
    }

    ~Pants() override {

    }
};

int main(){

        Tshirt tshirt;
        std::cout << "Introduceti detalii despre tricou:" << std::endl;
        std::cin >> tshirt;

        std::cout << "Detalii despre tricou:" << std::endl;
        tshirt.display();

        std::cout << "ID tricou: " << tshirt.getId() << std::endl;

        Clothing* clothing = &tshirt;
        clothing->processFunction();
        Tshirt* downcastedTshirt = dynamic_cast<Tshirt*>(clothing);
        downcastedTshirt->specificFunction();


    return 0;
};




