/*******************************************************************************
* File Name: composite_tree_app.cpp	                       		                 *
* Description: Definition test functions of composite_tree                     *
* Developer: Guy Chen	                                                         *
* Reviert: Iman Nasreldeen						                                         *
* Date: 16.11.2020										                                         *
*******************************************************************************/

#include <iostream>

#include "composite_tree.hpp"

using namespace hrd14;


/*************************** functions declarations ***************************/

static void FileCtorAndFileCout();

/****************************** Main function *********************************/

int main(int argc, char** argv)
{
    FileCtorAndFileCout();
    std::shared_ptr<const Directory> dir = Directory::Create(argv[1]);


    dir->Print(std::cout);

    return (0);
}


/******************************************************************************/

static void FileCtorAndFileCout()
{
    File f("hello");

    f.Print(std::cout);
}


