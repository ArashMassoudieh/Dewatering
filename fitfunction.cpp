#include "fitfunction.h"
#include <QDebug>

FitFunction::FitFunction() {}

CVector_arma FitFunction::OneStepLevenbergMarquardt(const CVector_arma &parameters, const double &lambda) const
{

    CVector_arma V = ResidualVector(parameters);
	qDebug()<< "V = " << V.toString();
    CMatrix_arma M = ResidualJacobian(parameters);
    qDebug() << "M=" << M.toString();
    CMatrix_arma JTJ = Transpose(M)*M;
	qDebug() << "JTJ = " << JTJ.toString();
    JTJ.ScaleDiagonal(1+lambda);
    CVector_arma J_epsilon = Transpose(M)*V;

    if (JTJ.det()<=1e-6)
    {
        JTJ += lambda*CMatrix::Diag(JTJ.getnumcols());
    }

    CVector_arma dx = J_epsilon/JTJ;
    qDebug() << "dx = " << dx.toString(); 
    return dx;
}

CVector_arma FitFunction::ResidualVector(const CVector_arma &parameters) const
{
    CVector_arma Residual(observed_data.n);
    for (int i=0; i<observed_data.n; i++)
    {
        Residual[i] = observed_data.GetC(i)-Function(observed_data.GetT(i),parameters);
    }

    return Residual;
}

CMatrix_arma FitFunction::ResidualJacobian(const CVector_arma &parameters) const
{
    CMatrix_arma Jacobian(observed_data.n,parameters.size());

    CVector_arma base_residual = ResidualVector(parameters);
    for (unsigned int i = 0; i < parameters.size(); i++)
    {
        CVector_arma parameters_purturbed = parameters;
        double epsilon = 1e-6;
        parameters_purturbed[i] += epsilon;
        CVector_arma purturbed_residual = ResidualVector(parameters_purturbed);
        Jacobian.setcol(i,(purturbed_residual - base_residual) / epsilon);
    }
    return Jacobian;

}

CVector_arma FitFunction::SolveLevenBerg_Marquardt(const CVector_arma &parameters) const
{

    double err = 1000;
    double err_p = 0;
    double tol = 1e-10;
    double lambda = 1;
    int counter = 0;
    double err_0 = ResidualVector(parameters).norm2();
    double err_x = 10000;
    double err_x0 = 10000;
    CVector_arma X = parameters;
    while (err>tol && err_x>tol/1000 && counter<1000)
    {
        CVector_arma X0 = X;
        err_p = err;
        CVector_arma dx = OneStepLevenbergMarquardt(X,lambda);

        if (dx.size() == 0)
            lambda *= 5;
        else
        {
            err_x = dx.norm2();
            if (counter == 0) err_x0 = err_x;
            X = X0 - dx;

            CVector_arma V = ResidualVector(X);
            err = V.norm2();
            if (err < err_p*0.9)
            {
                lambda /= 3;
            }
            else if (err > err_p)
            {
                lambda *= 2;
                X = X0;
                err = err_p;
            }
        }
        counter++;
        cout<<"counter:"<<counter<<"err:"<<err<<"err_x:"<<err_x<<std::endl;
    }

    return X;
}

double FitFunction::Function(const double &x, const CVector_arma &parameters) const
{
    if (functionform == FunctionForm::exponentialcummulative)
        return parameters[0]*(1-exp(-parameters[1]*(x-parameters[2])));
	else if (functionform == FunctionForm::expontialdeclining)
        return parameters[0] - (1 - exp(-parameters[1] * (x - parameters[2]))) * (parameters[0] - parameters[3]);
	else
	{
		qDebug() << "Function form not defined";
		return 0;
	}
}

double FitFunction::InverseDerivatve(const double &x, const CVector_arma &parameters) const
{
    if (functionform == FunctionForm::exponentialcummulative)
        return parameters[2] - 1.0/parameters[1]*log(x/(parameters[0]*parameters[1]));
    else if (functionform == FunctionForm::expontialdeclining)
    {
		return parameters[2] - 1.0 / parameters[1] * log(x / (parameters[1] * (parameters[0] - parameters[3])));
	}
    else
    {
        qDebug() << "Function form not defined";
        return 0;
    }
}

double FitFunction::Derivatve(const double& x, const CVector_arma &parameters) const
{
    if (functionform == FunctionForm::exponentialcummulative)
        return parameters[0]*parameters[1]*exp(-parameters[1]*(x-parameters[2]));
    else if (functionform == FunctionForm::expontialdeclining)
    {
        return parameters[1]*(parameters[0]-parameters[3])* exp(-parameters[1] * (x - parameters[2]));
    }
    else
    {
        qDebug() << "Function form not defined";
        return 0;
    }
}

CTimeSeries<double> FitFunction::GetPredictedData(const CVector_arma& parameters) const
{
	CTimeSeries<double> predicted_data;
	for (int i = 0; i < observed_data.n; i++)
	{
		double t = observed_data.GetT(i);
		double value = Function(t, parameters);
		predicted_data.append(t, value);
	}
	return predicted_data;
}

CTimeSeries<double> FitFunction::GetPredictedData(const CVector_arma& parameters, int n_intervals) const
{
    CTimeSeries<double> predicted_data;
    for (double x = observed_data.mint(); x <= observed_data.maxt(); x+=(observed_data.maxt()-observed_data.mint())/double(n_intervals))
    {
        double value = Function(x, parameters);
        predicted_data.append(x, value);
    }
    return predicted_data;
}

CTimeSeries<double> FitFunction::GetPredictedDerivative(const CVector_arma& parameters, int n_intervals) const
{
    CTimeSeries<double> predicted_data;
    for (double x = observed_data.mint(); x <= observed_data.maxt(); x += (observed_data.maxt() - observed_data.mint()) / double(n_intervals))
    {
        double value = Derivatve(x, parameters);
        predicted_data.append(x, value);
    }
    return predicted_data;
}

result FitFunction::Solve() const
{
    const int num_trials = 20; // Number of initial guesses
    const double lower_bounds[] = { 0.01, 0.0001, 0.0, 0.0 }; // Assume 4 parameters
    const double upper_bounds[] = { 100.0, 1.0, 100.0, 100.0 };
    const int num_params = functionform == FunctionForm::expontialdeclining ? 4 : 3;

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dist[4] = {
        std::uniform_real_distribution<>(lower_bounds[0], upper_bounds[0]),
        std::uniform_real_distribution<>(lower_bounds[1], upper_bounds[1]),
        std::uniform_real_distribution<>(lower_bounds[2], upper_bounds[2]),
        std::uniform_real_distribution<>(lower_bounds[3], upper_bounds[3])
    };

    double best_error = std::numeric_limits<double>::max();
    CVector_arma best_params;
    CTimeSeries<double> best_prediction;

    for (int trial = 0; trial < num_trials; ++trial) {
        CVector_arma initial_guess(num_params);
        for (int i = 0; i < num_params; ++i)
            initial_guess[i] = dist[i](gen);

        CVector_arma fitted = SolveLevenBerg_Marquardt(initial_guess);
        double mse = ResidualVector(fitted).norm2() / observed_data.n;

        if (mse < best_error) {
            best_error = mse;
            best_params = fitted;
            best_prediction = GetPredictedData(fitted,50);
        }
    }

    result res;
    res.parameters = best_params;
    res.MSE = best_error;
    res.predicted = best_prediction;
	res.derivative = GetPredictedDerivative(best_params, 50);
    
    if (functionform == FunctionForm::exponentialcummulative)
        res.inversederivative = best_params[2] - 1.0 / best_params[1];
    else if (functionform == FunctionForm::expontialdeclining)
        res.inversederivative = best_params[2] - 1.0 / best_params[1];
    else
        res.inversederivative = 0;

    return res;
}