#include <tclap/CmdLine.h>

class Network;

/*!
  This is the top-level class, building all the objects and running the simulation, based on user-defined parameters.
  The dynamics is a discrete stochastic heat equation on the graph: each node in the network is initialized 
  with a random value and these values then diffuse across the links.
  At each time-step random diffusion coefficients are drawn for each node.  
 */

class Simulation {

public:
/*!
  The constructor takes a pointer to the network which the simulation will be run over.
 */
    Simulation(Network*);
/*!
  The initialization takes the user arguments and configures the network and the simulation parameters.
 */
    void initialize(int, char**);
/*!
  Runs the entire simulation by calling \ref step() \ref maxtime times.
 */
    void run();
/*! 	
  Check the arguments passed by the initializer in the TCLAP.
   -The seed must be a positive integer
   -the number of steps to simulate must be a non-negative integer 
   -The degree must be smaller than the standard deviation of a poisson distribution, which is 
    the square root of the nodes
    
    Remark : the program may crash even with the current test. If you try degree 1 with four nodes and the poisson distribution gives 3 at the second nodes
			 you will not have enough nodes to link them
 */
	void CheckArgv(long, int, int, double);
    
    

private:
    void step() const; /*!<  One time step. */
    void print(const int&) const; /*!<  Prints out the network values every \ref stepnum steps. */
    Network *_network;
    int maxtime;  /*!<  number of steps until the end of the simulation */
    int stepnum;  /*!<  number of steps between printouts */


};
