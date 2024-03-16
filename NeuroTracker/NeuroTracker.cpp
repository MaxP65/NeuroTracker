#include <iostream>
#include "NeuralNetwork.h"

int main() {
    srand(time(NULL));
    LayerData layers[] = {
        InputLayer(1),
        ConnectedLayer(3),
        ConnectedLayer(1)
    };
    NeuralNetwork net(3, layers);
    net.randomize();
    std::cout << "randomized\n";

    std::vector<Scalar> vect{ 0, 0, 0.5, 1, 1, 0 };
    Dataset data = fromVector(3, 1, 1, vect);
    net.optimize(data, 0.1, 40);
    std::cout << "optimized \n";
    
    //Matrix in(2, 1);
    //in(0, 0) = 1;
    //in(1, 0) = 2;
    //Matrix out = net.output(in);
    //std::cout << "out" << out(0,0);
    //Vector out = net.process(in);
}