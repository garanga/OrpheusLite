/*
 * Element.hpp
 *
 *  Created on: Jan 18, 2017
 *      Author: pavel
 */

#ifndef ELEMENT_HPP_
#define ELEMENT_HPP_

class ElementType;

class Element
{
public:

    Element();
    explicit Element(int, int*, ElementType*);
    ~Element();

    void
    setConnect(int*);

    int
    getId() const;

    int*
    getConnect() const;

    ElementType*
    getType() const;

private:

    int          _id;
    int*         _connectivity;
    ElementType* _type;
};

#endif /* ELEMENT_HPP_ */
