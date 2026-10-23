#include "request.h"
#include "webserver.cpp"
#include "loadbalancer.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

const int NUM_SERVERS = 5;
static int ps = 0;			// the process ID incrementer, static so one copy persists

request createRandomRequest()
{
   stringstream ips, ipd;
   request r;
   // For example, 12.243.87.112
   ips << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
   ipd << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256) << "." << (rand() % 256);
   r.source = ips.str();
   r.destination = ipd.str();
   r.processTime = (rand() % 500);
   r.pid = ++ps;
   return r;
}

int main()
{
   // random number generator
   srand(7);

   // create a loadbalancer
   loadbalancer lb;
   
   // start off with a "full" queue
   for (int i = 0; i < 10; ++i)
   {
      request r = (createRandomRequest());
      lb.addRequest(r);

   }
   
   // an array of webservers, each given an initial request to process
   webserver webarray[NUM_SERVERS];
   for (int i = 0; i < NUM_SERVERS; ++i)
   {
      webserver w((char) (i+65));
      webarray[i] = w;
      int startTime = lb.getTime();
      request initialReq = lb.getRequest();
      webarray[i].addRequest(initialReq, startTime);
   }
   // loop
   while (lb.getTime() < 10000)
{
    int currTime = lb.getTime();
    int size = lb.getSize();

    if (webarray[currTime % NUM_SERVERS].isRequestDone(currTime))
    {
        request r =
            webarray[currTime % NUM_SERVERS].getRequest();

        cout << "Finished at " << currTime << " "
             << webarray[currTime % NUM_SERVERS].getName()
             << " pid " << r.pid << "/" << size
             << " process time was " << r.processTime << endl;

        webarray[currTime % NUM_SERVERS].addRequest(
            lb.getRequest(), currTime);
    }

    if (rand() % 10 == 0)
    {
        request r = createRandomRequest();
        lb.addRequest(r);
    }

    lb.incTime();
   }
}
