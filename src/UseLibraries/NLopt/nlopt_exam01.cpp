/**
 *  This example shows how to use NLopt to optimize minimization problem with
 *  nonlinear inequality constraint.
 *
 *  History:
 *
 *      2014-01-28
 *
 *          Li Dong     First creation.
 */

#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>
#include <nlopt.hpp>
#include <armadillo>

using std::cout;
using std::endl;
using std::vector;

using arma::vec;
using arma::mat;
using arma::norm;
using arma::span;
using arma::sum;
using arma::endr;

// -----------------------------------------------------------------------------
// problem instance data
struct Data {
    vec q;
    mat x;
    mat y;
};

// -----------------------------------------------------------------------------
// define objective function
int evalCounter = 0;
double objective(unsigned int n,  const double *x, double *grad, void *data_) {
    assert(n == 9);
    Data *data = static_cast<Data*>(data_);
    assert(data->q.size() == 3);
    assert(data->x.n_rows == 3);
    assert(data->y.n_rows == 3);
    mat H(x, 3, 3);
    // calculate objective value
    double f = 0.0;
    for (int j = 0; j < data->x.n_cols; ++j) {
        f += pow(norm(data->x(span::all, j)-data->q-H*data->y(span::all, j), 2), 2);
    }
    cout << "[Notice]: Iteration " << ++evalCounter;
    cout << ": Objective function value is " << f << endl;
    // calculate gradient
    if (grad != NULL) {
        int k = 0;
        for (int j = 0; j < 3; ++j) {
            for (int i = 0; i < 3; ++i) {
                grad[k++] =
                2*(sum(data->y(j, span::all)%data->y(0, span::all))*H(i, 0)+
                   sum(data->y(j, span::all)%data->y(1, span::all))*H(i, 1)+
                   sum(data->y(j, span::all)%data->y(2, span::all))*H(i, 2)-
                   sum(data->y(j, span::all)%(data->x(i, span::all)-data->q(i))));
            }
        }
    }
    return f;
}

// -----------------------------------------------------------------------------
// define nonlinear inequality constraint
double nonlinear_ineq_constraint(unsigned int n,  const double *x,
                                 double *grad, void *data_) {
    assert(n == 9);
    Data *data = static_cast<Data*>(data_);
    assert(data->q.size() == 3);
    assert(data->x.n_rows == 3);
    assert(data->y.n_rows == 3);
    mat H(x, 3, 3);
    double c = -det(H);
    if (grad != NULL) {
        grad[0] = H(1, 2)*H(2, 1)-H(1, 1)*H(2, 2);
        grad[1] = H(0, 1)*H(2, 2)-H(0, 2)*H(2, 1);
        grad[2] = H(0, 2)*H(1, 1)-H(0, 1)*H(1, 2);
        grad[3] = H(1, 0)*H(2, 2)-H(1, 2)*H(2, 0);
        grad[4] = H(0, 2)*H(2, 0)-H(0, 0)*H(2, 2);
        grad[5] = H(0, 0)*H(1, 2)-H(0, 2)*H(1, 0);
        grad[6] = H(1, 1)*H(2, 0)-H(1, 0)*H(2, 1);
        grad[7] = H(0, 0)*H(2, 1)-H(0, 1)*H(2, 0);
        grad[8] = H(0, 1)*H(1, 0)-H(0, 0)*H(1, 1);
    }
    return c;
}

// -----------------------------------------------------------------------------
// case
void run_case(nlopt::opt &a, const Data &data) {
    vector<double> H0(9);
    double obj;
    nlopt::result res;
    H0[0] = 1.0; H0[1] = 0.0; H0[2] = 0.0;
    H0[3] = 0.0; H0[4] = 1.0; H0[5] = 0.0;
    H0[6] = 0.0; H0[7] = 0.0; H0[8] = 1.0;
    try {
        res = a.optimize(H0, obj);
    } catch (const std::exception &e) {
        cout << "[Error]: Encounter exception \"" << e.what() << "\" from NLopt!" << endl;
        exit(-1);
    }
    if (res == nlopt::SUCCESS || res == nlopt::FTOL_REACHED ||
        res == nlopt::STOPVAL_REACHED) {
        cout << "[Notice]: Objective function is evaluated ";
        cout << evalCounter << " times." << endl;
        mat H(&H0.front(), 3, 3);
        cout << "[Notice]: Fitted deformation matrix:" << endl;
        H.print();
        cout << "[Notice]: det(H) = " << det(H) << endl;
        mat x(data.x);
        for (int j = 0; j < x.n_cols; ++j) {
            x(span::all, j) = data.q+H*data.y(span::all, j);
        }
        cout << "[Notice]: Actual coordinates:" << endl;
        data.x.print();
        cout << "[Notice]: Fitted coordinates:" << endl;
        x.print();
    } else {
        cout << "[Error]: Optimization failed!" << endl;
    }
}

// -----------------------------------------------------------------------------
// output:
//
//      [Notice]: Case 1:
//      [Notice]: Iteration 1: Objective function value is 4
//      [Notice]: Iteration 2: Objective function value is 1.77779
//      [Notice]: Iteration 3: Objective function value is 0.433226
//      [Notice]: Iteration 4: Objective function value is 0.184161
//      [Notice]: Iteration 5: Objective function value is 0.000435879
//      [Notice]: Iteration 6: Objective function value is 8.13121e-05
//      [Notice]: Iteration 7: Objective function value is 0.000268815
//      [Notice]: Iteration 8: Objective function value is 2.89248e-05
//      [Notice]: Iteration 9: Objective function value is 2.89248e-05
//      [Notice]: Iteration 10: Objective function value is 6.34976e-06
//      [Notice]: Iteration 11: Objective function value is 2.13883e-06
//      [Notice]: Iteration 12: Objective function value is 1.10063e-06
//      [Notice]: Iteration 13: Objective function value is 8.81941e-07
//      [Notice]: Objective function is evaluated 13 times.
//      [Notice]: Fitted deformation matrix:
//      6.5851e-04        0e+00   3.4400e-05
//      0e+00   8.3297e-06        0e+00
//      5.0273e-05        0e+00   3.2973e+00
//      [Notice]: det(H) = 1.80864e-08
//      [Notice]: Actual coordinates:
//      0.0255   0.0262   0.0268   0.0262
//      0.0003   0.0010   0.0003  -0.0003
//      -0.9997  -0.9997  -0.9996  -0.9997
//      [Notice]: Fitted coordinates:
//      0.0255   0.0262   0.0269   0.0262
//      0.0003   0.0003   0.0003   0.0003
//      -0.9998  -0.9997  -0.9996  -0.9997
//      [Notice]: Case 2:
//      [Notice]: Iteration 14: Objective function value is 4.10061
//      [Notice]: Iteration 15: Objective function value is 1.8159
//      [Notice]: Iteration 16: Objective function value is 0.863326
//      [Notice]: Iteration 17: Objective function value is 0.126213
//      [Notice]: Iteration 18: Objective function value is 0.876192
//      [Notice]: Iteration 19: Objective function value is 0.0216174
//      [Notice]: Iteration 20: Objective function value is 0.0216174
//      [Notice]: Iteration 21: Objective function value is 0.00309204
//      [Notice]: Iteration 22: Objective function value is 0.00215742
//      [Notice]: Iteration 23: Objective function value is 2.34291
//      [Notice]: Iteration 24: Objective function value is 0.0222922
//      [Notice]: Iteration 25: Objective function value is 0.0020315
//      [Notice]: Iteration 26: Objective function value is 0.0020315
//      [Notice]: Iteration 27: Objective function value is 0.00247789
//      [Notice]: Iteration 28: Objective function value is 0.0009098
//      [Notice]: Iteration 29: Objective function value is 0.0009098
//      [Notice]: Iteration 30: Objective function value is 1.64017
//      [Notice]: Iteration 31: Objective function value is 0.0159819
//      [Notice]: Iteration 32: Objective function value is 0.000928478
//      [Notice]: Iteration 33: Objective function value is 0.000877263
//      [Notice]: Iteration 34: Objective function value is 0.000877263
//      [Notice]: Iteration 35: Objective function value is 0.00030082
//      [Notice]: Iteration 36: Objective function value is 0.000207817
//      [Notice]: Iteration 37: Objective function value is 7.46385e-05
//      [Notice]: Iteration 38: Objective function value is 5.43053e-05
//      [Notice]: Iteration 39: Objective function value is 3.07545e-05
//      [Notice]: Iteration 40: Objective function value is 1.0732e-05
//      [Notice]: Iteration 41: Objective function value is 7.05675e-06
//      [Notice]: Iteration 42: Objective function value is 1.35483e-06
//      [Notice]: Iteration 43: Objective function value is 4.12899e-07
//      [Notice]: Objective function is evaluated 43 times.
//      [Notice]: Fitted deformation matrix:
//      -7.3354e-05   3.3419e-04   1.2768e-01
//      -4.8447e-06  -2.4614e-02   2.3482e-03
//      2.4500e-02   1.1525e-04   3.2775e+00
//      [Notice]: det(H) = 8.29377e-05
//      [Notice]: Actual coordinates:
//      9.9960e-01   9.9930e-01   9.9960e-01   9.9990e-01
//      1.2300e-02   3.6800e-02   1.2300e-02  -1.2300e-02
//      -2.4500e-02  -1.5030e-18   2.4500e-02   4.5080e-18
//      [Notice]: Fitted coordinates:
//      1.0000   0.9996   0.9998   1.0002
//      0.0123   0.0369   0.0123  -0.0123
//      -0.0245  -0.0001   0.0245   0.0001
//      [Notice]: Case 3:
//      [Notice]: Iteration 44: Objective function value is 4.01
//      [Notice]: Iteration 45: Objective function value is 1.86778
//      [Notice]: Iteration 46: Objective function value is 1.29314
//      [Notice]: Iteration 47: Objective function value is 0.971275
//      [Notice]: Iteration 48: Objective function value is 0.971275
//      [Notice]: Iteration 49: Objective function value is 0.375479
//      [Notice]: Iteration 50: Objective function value is 0.498023
//      [Notice]: Iteration 51: Objective function value is 0.195969
//      [Notice]: Iteration 52: Objective function value is 0.195969
//      [Notice]: Iteration 53: Objective function value is 0.0923087
//      [Notice]: Iteration 54: Objective function value is 0.0590023
//      [Notice]: Iteration 55: Objective function value is 0.245301
//      [Notice]: Iteration 56: Objective function value is 0.0417097
//      [Notice]: Iteration 57: Objective function value is 0.0417097
//      [Notice]: Iteration 58: Objective function value is 1.0485
//      [Notice]: Iteration 59: Objective function value is 0.0270964
//      [Notice]: Iteration 60: Objective function value is 0.0270964
//      [Notice]: Iteration 61: Objective function value is 0.00680416
//      [Notice]: Iteration 62: Objective function value is 0.0185493
//      [Notice]: Iteration 63: Objective function value is 0.00238037
//      [Notice]: Iteration 64: Objective function value is 0.00238037
//      [Notice]: Iteration 65: Objective function value is 0.00102714
//      [Notice]: Iteration 66: Objective function value is 0.00258825
//      [Notice]: Iteration 67: Objective function value is 0.000199708
//      [Notice]: Iteration 68: Objective function value is 0.000199708
//      [Notice]: Iteration 69: Objective function value is 6.8813e-06
//      [Notice]: Iteration 70: Objective function value is 6.40882e-07
//      [Notice]: Objective function is evaluated 70 times.
//      [Notice]: Fitted deformation matrix:
//      -3.3790e-04  -3.9496e-04   5.9688e-02
//      4.9809e-02  -3.4408e-05   1.4183e-01
//      -1.1196e-04   4.9989e-02   3.3013e+00
//      [Notice]: det(H) = 0.000216003
//      [Notice]: Actual coordinates:
//      1.0000   1.0000   1.0000   1.0000
//      0.9500   1.0000   1.0500   1.0000
//      0  -0.0500        0   0.0500
//      [Notice]: Fitted coordinates:
//      1.0003   1.0004   0.9997   0.9996
//      0.9502   1.0000   1.0498   1.0000
//      0.0001  -0.0500  -0.0001   0.0500
//
int main(int argc, char const *argv[])
{
    Data data;
    data.y << -1.0 <<  0.0 <<  1.0 <<  0.0 << endr
           <<  0.0 << -1.0 <<  0.0 <<  1.0 << endr
           <<  0.0 <<  0.0 <<  0.0 <<  0.0 << endr;
    
    nlopt::opt a(nlopt::LD_SLSQP, 9);
    a.set_min_objective(objective, &data);
    a.add_inequality_constraint(nonlinear_ineq_constraint, &data);
    a.set_ftol_rel(1.0e-3);
    a.set_stopval(1.0e-6);
    
    // -------------------------------------------------------------------------
    // case 1
    cout << "[Notice]: Case 1:" << endl;
    data.q <<  0.0262 <<  0.0003 << -0.9997 << endr;
    data.x <<  0.0255 <<  0.0262 <<  0.0268 <<  0.0262 << endr
           <<  0.0003 <<  0.0010 <<  0.0003 << -0.0003 << endr
           << -0.9997 << -0.9997 << -0.9996 << -0.9997 << endr;
    run_case(a, data);
    // -------------------------------------------------------------------------
    // case 2
    cout << "[Notice]: Case 2:" << endl;
    data.q << 0.9999 << 0.0123 << 0 << endr;
    data.x << 0.9996 << 0.9993 << 0.9996 << 0.9999 << endr
           << 0.0123 << 0.0368 << 0.0123 << -0.0123 << endr
           << -0.0245 << -1.503e-18 << 0.0245 << 4.508e-18 << endr;
    run_case(a, data);
    // -------------------------------------------------------------------------
    // case 3
    cout << "[Notice]: Case 3:" << endl;
    data.q <<  1.0 <<   1.0 << 0.0 << endr;
    data.x <<  1.0 <<   1.0 <<  1.0 <<  1.0 << endr
           << 0.95 <<   1.0 << 1.05 <<  1.0 << endr
           <<  0.0 << -0.05 <<  0.0 << 0.05 << endr;
    run_case(a, data);
    return 0;
}