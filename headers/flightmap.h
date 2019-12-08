#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>

#include "heap.h"

struct Flight;
struct Port {//struct for airport info (vertexes)
public:
    std::string code;
    std::vector<std::shared_ptr<Port>> adjlist; //list of destination airports that are one flight from the current port
    std::vector<std::shared_ptr<Flight>> depflights; //list of flights departing from this airport
    int dval;
    // int parentid; what this for?
    //CONSTRUCTOR//
    Port(std::string code, int d_in);
    void prt();
};

struct Flight{//struct for flight data (edges)
    static int fltcount;
    int fltnum;
    std::shared_ptr<Port> origin;
    std::shared_ptr<Port> dest;
    float deptime; //departure time
    float arrtime; //arrival time

    //CONSTRUCTOR//
    Flight(std::shared_ptr<Port> orig_in, std::shared_ptr<Port> dest_in, int time_in, float length_in);
    void prt();
};

class FlightMap
{//class for creating and holding all the travel data related to a graph of airports and flights
    std::vector<std::shared_ptr<Port>> ports;
    std::vector<std::shared_ptr<Flight>> flights;
    // std::unique_ptr<Heap> heap;
public:
    //CONSTRUCTOR//
    FlightMap(int port_count, int flight_count);
    //FUNCTIONS//
    static float genTime(int MAX_HOURS);
    static std::string genCode(int code_length);
    //PRINT FUNCTION//
            // for(std::shared_ptr<flight> f : p->depflights){
    friend std::ostream& operator <<(std::ostream& os, std::shared_ptr<FlightMap> const fltmp)
    {
        for(std::shared_ptr<Port> p : fltmp->ports){
            p->prt();
        }
        return os << "\n";
    };
};
