#ifndef FITFUNCTION_H
#define FITFUNCTION_H

#include <vector>
#include "BTC.h"
#include "Matrix_arma.h"
#include "Vector_arma.h"

class FitFunction
{
public:
    FitFunction();
    double ObjectiveFunction(const std::vector<double> &parameters) const;
    double Function(const double &x, const CVector_arma &parameters) const;
    CVector_arma SolveLevenBerg_Marquardt(const CVector_arma &parameters) const;
    void SetObservedData(const CTimeSeries<double> &obsdata) {observed_data = obsdata;}
    double InverseDerivatve(const double &x, const std::vector<double> &parameters);
private:
    CTimeSeries<double> observed_data;
    CVector_arma OneStepLevenbergMarquardt(const CVector_arma &parameters, const double &lambda) const;
    CVector_arma ResidualVector(const CVector_arma &parameters) const;
    CMatrix_arma ResidualJacobian(const CVector_arma &parameters) const;
};

#endif // FITFUNCTION_H
