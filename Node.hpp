/*
 * Node.hpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#ifndef NODE_HPP_
#define NODE_HPP_

class Node
{
public:

    Node();
    explicit
    Node(int id, double* coord);
    ~Node();

    void
    setCoord(double*);

    int
    getId() const;

    double*
    getCoord() const;

private:

    int     _id;
    double* _coord;
};

#endif /* NODE_HPP_ */
