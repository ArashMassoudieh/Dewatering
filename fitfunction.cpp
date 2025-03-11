#include "fitfunction.h"

FitFunction::FitFunction() {}

CVector_arma FitFunction::OneStepLevenbergMarquardt(const CVector_arma &parameters, const double &lambda) const
{

    CVector_arma V = ResidualVector(parameters);
    CMatrix_arma M = ResidualJacobian(parameters);
    CMatrix_arma JTJ = M*Transpose(M);
    JTJ.ScaleDiagonal(1+lambda);
    CVector_arma J_epsilon = M*V;

    if (JTJ.det()<=1e-6)
    {
        JTJ += lambda*CMatrix::Diag(JTJ.getnumcols());
    }

    CVector_arma dx = J_epsilon/JTJ;
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
    CMatrix_arma Jacobian(parameters.size(),observed_data.n);

    CVector_arma base_residual = ResidualVector(parameters);
    for (unsigned int i = 0; i < parameters.size()-1; i++)
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
    double err_p;
    double tol = 1e-10;
    double lambda = 1;
    int counter = 0;
    double err_0 = ResidualVector(parameters).norm2();
    double err_x = 10000;
    double err_x0 = 10000;
    CVector_arma X = parameters;
    while (err>tol && err_x>tol && counter<1000)
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
            CVector_arma X = X0 - dx;
            CVector_arma V = ResidualVector(X);
            err = V.norm2();
            if (err < err_p * 0.8)
            {
                lambda /= 1.2;
                X = X0;
            }
            else if (err > err_p)
            {
                lambda *= 1.2;
                err = err_p;
            }
        }
        counter++;
    }

    return X;
}

double FitFunction::Function(const double &x, const CVector_arma &parameters) const
{
    return parameters[0]*(1-exp(-parameters[1]*(x-parameters[2])));
}
