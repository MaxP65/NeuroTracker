#include <iostream>
#include "NeuralNetwork.h"

int main() {
    srand(time(NULL));
    LayerData layers[] = {
        InputLayer(2),
        ConnectedLayer(4),
        SoftmaxLayer(2)
    };
    NeuralNetwork net(layers, 3);
    net.randomize();
    parseData();
    std::cout << "randomized\n";

    std::vector<Scalar> vect{ 0, 0, 0, 1, 
                              1, 1, 1, 0 };
    Dataset data = fromVector(2, 2, 2, vect);
    net.optimize(data, 0.1, 100);
    std::cout << "optimized \n";
    Matrix in(2, 1, 1);
    Matrix out = net.output(in);
    std::cout << "out" << out(0, 0) << ' ' << out(1, 0) << " \n";
    //net.printGraph(0, 2, 50, 50);
}