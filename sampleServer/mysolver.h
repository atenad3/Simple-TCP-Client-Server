#ifndef MYSOLVER_H
#define MYSOLVER_H

#include <QObject>
#include <iostream>
#include "ampl/ampl.h"
#include"QDebug"

class MySolver
{
public:
    MySolver();
    void setRequirement();
    void setSolver(QString solver);
    void readModel(QString model_file);
    void solve();
    double getVariableValue(QString var_name);
private:
    // ampl::AMPL ampl;
    ampl::Environment env;
    ampl::AMPL *ampl;

};

#endif // MYSOLVER_H
