#include "headers/flightmap.h"

using str = std::string;
using s_Port = std::shared_ptr<Port>;
using s_Flight = std::shared_ptr<Flight>;
using s_Heap = std::shared_ptr<Heap>;

Port::Port(str code_in, int d_in)
    : code(code_in), dval(d_in) {/*CONSTRUCTOR*/}
//PRINT FUNCTION//
void Port::prt()
{
    std::cout << "\nAirport Code: " << this->code << '\t'
                << "dval: " << this->dval << '\n';
    if (this->depflights.size() == 0){
        std::cout << "There are no flights leaving " << this->code << std:: endl;
    }
    for(std::shared_ptr<Flight> flt : this->depflights){
        flt->prt();
    }
}

Flight::Flight(s_Port orig_in, s_Port dest_in, int time_in, float length_in)
    : fltnum(fltcount++), origin(orig_in), dest(dest_in), deptime(time_in)
    {/*CONSTRUCTOR*/
        float endtime = this->deptime + length_in;
        if (endtime > 24){
            this->arrtime = endtime - 24;
        }
        else
            this->arrtime = endtime;
    }
//PRINT FUNCTION//
void Flight::prt()
{
    std::cout << "Num: " << this->fltnum << "\n\t"
                << "Origin: " << this->origin->code << "\n\t"
                << "Destination: " << this->dest->code << "\n\t";
    printf("Departure Time: %02.f:%02.f\n\t",floor(this->deptime), (this->deptime - floor(this->deptime))*100);
    printf("Arrival Time: %02.f:%02.f\n",floor(this->arrtime), (this->arrtime - floor(this->arrtime))*100);
};


int Flight::fltcount = 0; 
FlightMap::FlightMap(int port_count, int flight_count)
{//generates a set of airports, flights between them and stores the portids in a heap for djikstra's algo
    // this->ports.resize(port_count);
    // this->flights.resize(flight_count);
    //fill ports
    s_Port newport;
    s_Flight newflight;
    for (int i = 0 ; i < flight_count ; i++){
        str portcode = FlightMap::genCode(3);
        newport = std::make_shared<Port>(portcode, 0);
        this->ports.push_back(newport);
    }
    //fill flights
    for (int i = 0 ; i < flight_count; i++){
        float deptime = FlightMap::genTime(24); //gen random flight deptime less than 24hrs
        float length = FlightMap::genTime(12) + 1; //generate random flight length less than 12hrs
        //randomize ports
        s_Port port1;
        s_Port port2;
        do
        { 
            port1 = ports[rand() % port_count];
            port2 = ports[rand() % port_count];
        } while(port1 == port2);

        newflight = std::make_shared<Flight>(port1, port2, deptime, length);
        this->flights.push_back(newflight);
        port1->adjlist.push_back(port2);
        port1->depflights.push_back(newflight);
    }
}

str FlightMap::genCode(int length_in)
{//generates a random capitalized string of length length_in
    str code = "";
    for(int i=0; i < length_in; i++){
        int num = rand() % 26;
        char letter = 'a' + num;
        code += toupper(letter);
    }
    return code;
}

float FlightMap::genTime(int MAX_HOUR)
{//generates random float representing a time of day
    float min = float(rand() % 61)/100.0;
    // float newmin = min/100.0;
    float time = (rand() % MAX_HOUR) + min;
    return time;
}