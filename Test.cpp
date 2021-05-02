#include "doctest.h"
#include "NumberWithUnits.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("addition operators"){
    NumberWithUnits number1(530,"g");
    NumberWithUnits number2(15.7,"kg");
    NumberWithUnits number3(1.2,"ton");
    
    CHECK(number1 + number2 == NumberWithUnits(16230,"g"));
    CHECK(number2 + number3 == NumberWithUnits(1215.7,"kg"));
    CHECK(++number2 == NumberWithUnits(16.7,"kg"));
    CHECK((number3 += number2) == NumberWithUnits(1.2157,"ton"));
    CHECK(number2++ == NumberWithUnits(16.7,"kg"));
    CHECK((+number2) == NumberWithUnits(15.7,"kg"));   
}

TEST_CASE("subtraction operators"){
    NumberWithUnits number1(120,"cm");
    NumberWithUnits number2(230,"m");
    NumberWithUnits number3(4,"km");
    
    CHECK(number3 - number1 == NumberWithUnits(3.88,"km"));
    CHECK(--number1 == NumberWithUnits(119,"cm"));
    CHECK((number2 -= number1) == NumberWithUnits(228.8,"ton"));
    CHECK(number2-- == NumberWithUnits(229,"kg"));
    CHECK((-number3) == NumberWithUnits(-4,"kg"));   
}

TEST_CASE("multiplication operators"){
    NumberWithUnits number1(46,"sec");
    NumberWithUnits number2(130," min");
    NumberWithUnits number3(4.5,"hour");
    double d = rand() % 100;

    CHECK_EQ(number1 * d, NumberWithUnits(46*d, "sec"));
    CHECK_EQ(d * number2  , NumberWithUnits(d*130, "min"));
    CHECK_EQ((number3 *= d) , NumberWithUnits(4.5*d, "ton"));
}

TEST_CASE("comparison operators"){
    NumberWithUnits number1(120,"cm");
    NumberWithUnits number2(230,"m");
    NumberWithUnits number3(4,"km");
    NumberWithUnits number4(15,"cm");
    NumberWithUnits number5(75,"m");
    NumberWithUnits number6(1.4,"km");
    
    CHECK_NE(number1 , number2);
    CHECK(number1 != number2);
    CHECK(number4 < number1);
    CHECK(number3 > number6);
    CHECK(number2 >= number5);
    CHECK(number6 >= number1);
    CHECK_NE(number3 ,number6);
    CHECK(number1 == number4);
}

TEST_CASE("exeptions"){
    NumberWithUnits number1(120,"cm");
    NumberWithUnits number2(230,"g");
    NumberWithUnits number3(4,"sec");
    
    CHECK_THROWS(number3 + number1);
    CHECK_THROWS(number2 -= number1);
    CHECK_THROWS(number2 + number3);
    CHECK_THROWS(number1 - number3);
    CHECK_THROWS(number3 += number1);

}

TEST_CASE("random tests"){
    NumberWithUnits number1(120,"cm");
    NumberWithUnits number2(230,"m");
    NumberWithUnits number3(4,"km");
    
    /*************
     * operators:
     * < > <= >= == !=
     * *********/
    for(int i = 0; i < 20; i++)
    {
        //generate random numbers up to 3 km
        double cm = rand() % 3000;
        double m = rand() % 300;
        double km = rand() % 3;

        NumberWithUnits number1(cm,"cm");
        NumberWithUnits number2(m,"m");
        NumberWithUnits number3(km,"km");

        CHECK(number1 < number2);
        CHECK(number3 > number2);
        CHECK(number1 == number2);
        CHECK(number3 >= number2);
        
        //generate random values for coin values
        double shekel = rand() % 3500;
        double dolar = rand() % 1000;

        NumberWithUnits number4(shekel,"ILS");
        NumberWithUnits number5(dolar,"USD");
        
        CHECK(number4 != number5);
        CHECK(number5 >= number4);
    }

    /*************
     * operators:
     * + ++ += - -- -=
     * *********/
    for (int i = 0; i < 20; i++)
    {
        //generate random numbers up to 1 day
        double sec = rand() % 8640;
        double min = rand() % 1440;
        double hour = rand() % 24;

        NumberWithUnits number1(sec,"sec");
        NumberWithUnits number2(min,"min");
        NumberWithUnits number3(hour,"hour");

        CHECK((number1+number2) == NumberWithUnits(sec+min*60,"sec"));
        CHECK((number3++) == NumberWithUnits(hour,"hour"));
        CHECK((++number2) == NumberWithUnits(min+1,"min"));
        CHECK((number3 += number2) == NumberWithUnits(hour+(min/24),"hour"));
        
        //generate random values for wight values
        double g = rand() % 50000;
        double kg = rand() % 50;

        NumberWithUnits number4(g,"g");
        NumberWithUnits number5(kg,"kg");
        
        CHECK(-number4 == NumberWithUnits(-g,"g"));
        CHECK((number5 -= number4) == NumberWithUnits(kg-(g/1000),"kg"));
    }

    /*************
     * operators:
     * * *=
     * *********/
    for (int i = 0; i < 20; i++)
    {
        //generate random numbers up to 1 day
        double shekel = rand() % 3500;
        double dollar = rand() % 1000;
        
        NumberWithUnits number1(shekel,"ILS");
        NumberWithUnits number2(dollar,"USD");
        
        double rand_val = rand() % 50;

        CHECK(number1 * rand_val == NumberWithUnits(shekel * rand_val,"ILS"));
        CHECK(rand_val * number1 == NumberWithUnits(shekel * rand_val,"ILS"));
        CHECK((number2 *= rand_val) == NumberWithUnits(dollar * rand_val,"dollar"));
    }




}