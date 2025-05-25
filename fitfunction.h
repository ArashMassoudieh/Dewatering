#ifndef FITFUNCTION_H
#define FITFUNCTION_H

#include <vector>
#include "BTC.h"
#include "Matrix_arma.h"
#include "Vector_arma.h"

enum class FunctionForm {exponentialcummulative, expontialdeclining};

struct result {
	CVector_arma parameters;
	double MSE;
	CTimeSeries<double> predicted;
    CTimeSeries<double> derivative;
	double inversederivative;
};

class FitFunction
{
public:
    FitFunction();
    double Function(const double &x, const CVector_arma &parameters) const;
    CVector_arma SolveLevenBerg_Marquardt(const CVector_arma &parameters) const;
    void SetObservedData(const CTimeSeries<double> &obsdata) {

		for (int i = 0; i < obsdata.n; i++)
		{
			if (!std::isnan(obsdata.GetC(i)) && !std::isnan(obsdata.GetT(i)))
			{
				observed_data.append(obsdata.GetT(i), obsdata.GetC(i));
			}
		}
    
    }
    double InverseDerivatve(const double &x, const CVector_arma &parameters) const;
    double Derivatve(const double& x, const CVector_arma &parameters) const;
	void SetFunctionForm(FunctionForm form) { functionform = form; }
	FunctionForm GetFunctionForm() const { return functionform; }
	CTimeSeries<double> GetObservedData() const { return observed_data; }
	CTimeSeries<double> GetPredictedData(const CVector_arma& parameters) const;
    CTimeSeries<double> GetPredictedData(const CVector_arma& parameters, int n_intervals) const;
    CTimeSeries<double> GetPredictedDerivative(const CVector_arma& parameters, int n_intervals) const;
    result Solve() const; 
private:
    FunctionForm functionform; 
    CTimeSeries<double> observed_data;
    CVector_arma OneStepLevenbergMarquardt(const CVector_arma &parameters, const double &lambda) const;
    CVector_arma ResidualVector(const CVector_arma &parameters) const;
    CMatrix_arma ResidualJacobian(const CVector_arma &parameters) const;
};

#endif // FITFUNCTION_H
