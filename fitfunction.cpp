#include "fitfunction.h"

FitFunction::FitFunction() {}

CVector_arma FitFunction::OneStepLevenbergMarquardt(const CVector_arma &parameters, const double &lambda) const
{

    CVector_arma V = ResidualVector(parameters);
    CMatrix_arma M = ResidualJacobian(parameters);
    M.writetofile("M.txt");
    V.writetofile("V.txt");
    CMatrix_arma JTJ = Transpose(M)*M;
    JTJ.writetofile("JTJ_before.txt");
    JTJ.ScaleDiagonal(1+lambda);
    JTJ.writetofile("JTJ_after.txt");
    CVector_arma J_epsilon = Transpose(M)*V;
    J_epsilon.writetofile("J_epsilon");
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
        dx.writetofile("dx.txt");
        if (dx.size() == 0)
            lambda *= 5;
        else
        {
            err_x = dx.norm2();
            if (counter == 0) err_x0 = err_x;
            X = X0 - dx;
            X.writetofile("X.txt");
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
    //std::cout<<parameters[0]<<":"<<parameters[1]<<":"<<parameters[2]<<std::endl;
    //std::cout<<parameters[0]*(1-exp(-parameters[1]*(x-parameters[2])))<<std::endl;
    return parameters[0]*(1-exp(-parameters[1]*(x-parameters[2])));


}
