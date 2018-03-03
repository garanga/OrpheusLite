//---------------------------------------------------------------------------
// Created on: 04.03.2017.
// Author: Mikhail A. Volkov
// E-mail: Volkovmikhl@gmail.com
//---------------------------------------------------------------------------

#include "includes.hpp"

ODBFrame::ODBFrame()
{

}


ODBFrame::~ODBFrame()
{

}

ODBFrame::ODBFrame(std::ifstream& fin, int dim    , int nodes_per_element,
                                       int n_nodes, int n_elemens        )
{
    int current_symbol;

    while(1)
    {
        fin >> current_symbol;

        if (current_symbol == (int)Symbol::Output::OUTPUTEND)
            break;

        switch(current_symbol)
        {
            case (int)Symbol::Output::U :
            {
                std::vector<double> data_vector;
                int cntr = 0;
                double data;
                for (int i = 0; i < n_nodes; ++i)
                {
                    while (cntr < dim)
                    {
                        fin >> data;
                        data_vector.push_back(data);
                        cntr++;
                    }
                    cntr = 0;
                }
                mFields.data[Symbol::Output::U] = data_vector;
                break;
        }
        case (int)Symbol::Output::S :
        {
            std::vector<double> data_vector;
            int limit = 1;

            if (dim == 2)
                limit = 3;
            else if (dim == 3)
                limit = 6;


            double data;
            for (int i = 0; i < n_nodes; ++i)
            {
                for (int j =0; j < limit; j++)
                {
                    fin >> data;
                    data_vector.push_back(data);
                }
            }
            mFields.data[Symbol::Output::S] = data_vector;
            break;
        }
        }
    }
}

void ODBFrame::setFieldOutput(FieldOutput& fields)
{
    mFields = fields;
}

ScalarOutput& ODBFrame::getScalarOutput()
{
    return mScalars;
}

FieldOutput& ODBFrame::getFieldOutput()
{
    return mFields;
}

void ODBFrame::fileStreamWrite(std::ofstream& fout, int dim)
{
    for (auto it  = mScalars.data.begin();
              it != mScalars.data.end()  ; ++it)
    {
        int scalar_type = static_cast<int>(it->first);
        fout << scalar_type << "\n";
        switch (scalar_type)
        {
        case (int)Symbol::Output::T :
        {
            for (unsigned int i = 0; i < it->second.size(); ++i)
                fout << it->second.at(i) << std::endl;
            break;
        }
        }
    }

    for (auto it  = mFields.data.begin();
              it != mFields.data.end()  ; ++it)
    {
        int field_type = static_cast<int>(it->first);
        fout << field_type << "\n";
        switch (field_type)
        {
        case (int)Symbol::Output::U :
        {
            for (unsigned int i = 0; i < it->second.size(); i += dim)
            {
                for (int j = 0; j < dim; ++j)
                {
                    fout << it->second.at(i + j);
                    if (j != dim - 1)
                        fout << " ";
                }
                fout << std::endl;

            }
            break;
        }
        case (int)Symbol::Output::S :
        case (int)Symbol::Output::E :
        {

            int limit = 1;
            if (dim == 2)
                limit = 3;
            else if (dim == 3)
                limit = 6;

            for (unsigned int i = 0; i < it->second.size(); i += limit)
            {
                for (int j = 0; j < limit; ++j)
                {
                    fout << it->second.at(i + j);
                    if (j != limit - 1)
                        fout << " ";
                }
                fout << std::endl;
            }
            break;
        }
        }
    }

    fout << (int)Symbol::Output::OUTPUTEND << std::endl;

}

void ODBFrame::printData(int dim)
{
    std::cout << "data size: " << mFields.data.size() << std::endl;
    std::cout << "end first: " << (int)mFields.data.end()->first << std::endl;
    for(auto it = mFields.data.begin(); it != mFields.data.end(); ++it)
    {
        std::cout << "Data type: " << (int)it->first << std::endl;
        switch ((int)it->first)
        {
        case (int)Symbol::Output::U :
        {
            auto iter  = it->second.begin();

            while (iter != it->second.end())
            {
                for (int i = 0; i < dim; ++i, ++iter)
                    std::cout<< (*iter) << " ";
                std::cout << std::endl;
            }
            break;
        }
        case (int)Symbol::Output::S :
        {
            int limit = 1;
            if (dim == 2)
                limit = 3;
            else if(dim == 3)
                limit = 6;

            auto iter  = it->second.begin();

            while (iter != it->second.end())
            {
                for (int i = 0; i < limit; ++i, ++iter)
                    std::cout<< (*iter) << " ";
                std::cout << std::endl;
            }
            break;
        }
        default:
        {
            std::cout << "Wrong Code: " << (int)it->first << std::endl;
            if (it == mFields.data.end())
                std::cout << "Real end\n";
            break;
        }
        }
    }

}
