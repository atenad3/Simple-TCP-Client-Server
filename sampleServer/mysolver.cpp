#include "mysolver.h"

MySolver::MySolver(){
    // env("/home/atefe/Downloads/ampl.linux-intel64/");
    qDebug() << "hello";
    // ampl::Environment env("/home/atefe/Downloads/ampl.linux-intel64/");
    // // ampl(env);
    // ampl::AMPL ampl(env);
    env.setBinDir("/home/atefe/Downloads/ampl.linux-intel64/");
    ampl = new ampl::AMPL(env); //new returns the pointer
    qDebug() << "bye";
}

void MySolver::setSolver(QString solver){
    // ampl.setOption("solver", solver);
    ampl->setOption("solver", solver.toStdString().c_str());
}

void MySolver::readModel(QString model_file) {
    // ampl.read(model_file.toStdString().c_str());
    ampl ->read(model_file.toStdString().c_str());
    // ampl ->read();
}

void MySolver::solve() {
    // ampl.solve();
    ampl ->solve();
}

double MySolver::getVariableValue(QString var_name) {
    // double variable =ampl.getVariable(var_name.toStdString().c_str()).value();
    // return variable;
    double variable = ampl ->getVariable(var_name.toStdString().c_str()).value();
    return variable;
}

void MySolver::setRequirement(){
    // env.setBinDir("/home/atefe/Downloads/ampl.linux-intel64/");
    // // ampl(env);
    // ampl -> AMPL(env);
    // // ampl::AMPL ampl;
}
