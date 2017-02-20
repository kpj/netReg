/**
 * netReg: graph-regularized linear regression models.
 * <p>
 * Copyright (C) 2015 - 2016 Simon Dirmeier
 * <p>
 * This file is part of netReg.
 * <p>
 * netReg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * <p>
 * netReg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * <p>
 * You should have received a copy of the GNU General Public License
 * along with netReg. If not, see <http://www.gnu.org/licenses/>.
 *
 * @author: Simon Dirmeier
 * @email: simon.dirmeier@gmx.de
 */


#ifndef NETREG_EDGENET_GAUSSIAN_HPP
#define NETREG_EDGENET_GAUSSIAN_HPP

#include <vector>

#include "graph_penalized_linear_model_data.hpp"
#include "graph_penalized_linear_model_cv_data.hpp"
#include "cv_fold.hpp"


#ifdef USE_RCPPARMADILLO
// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#else
#include "armadillo"
#endif

namespace netreg
{
    /**
     * Class for estimating the coeffiecients of a edge-regularized linear regression model.
     */
    class edgenet_gaussian
    {
    public:
        /**
         * Calulates the coefficients of a graph-regularized regression model.
         *
         * @param data an object that holds all required data for the model
         */
        arma::Mat<double> run(graph_penalized_linear_model_data &data) const;

        /**
         * Calulates the optimal set of shrinkage parameters of a
         * graph-regularized regression model.
         *
         * @param data an object that holds all required data for the model
         * @param lambda the shrinkage parameter you want to use for the LASSO
         * @param alpha the parameter for the elastic net
         * @param psigx penalization of laplacian for X
         * @param psigy penalization of laplacian for Y
         *
         * @return returns the estimated coefficients
         */
        arma::Mat<double> run_cv
            (graph_penalized_linear_model_cv_data &data,
             const double lambda,
             const double alpha,
             const double psigx,
             const double psigy,
             cv_fold &fold) const;

    private:

        /**
         * Calculate an univariate cyclic coordinate descent on the index of
         * a column of a multivariate response matrix.
         *
         * @param data an object containing all relevant data
         * @param B the current coefficient matrix
         * @param B_old the old coefficient matrix
         * @param qi the index of a column of the multivariate response amtrox
         */
        void uccd_
            (int P, int Q,
             double thresh, int niter,
             double lambda, double alpha,
             double psigx, const double psigy,
             arma::Mat<double> &TXX, arma::Mat<double> &TXY,
             arma::Mat<double> &LX, arma::Mat<double> &LY,
             arma::Mat<double> &coef,
             arma::Mat<double> &old_coef,
             int qi,
             std::vector< arma::rowvec >& txx_rows,
             std::vector< arma::rowvec >& lx_rows) const;

        /**
         * Updates the softthresholding parameter and the normalization
         * constant using the graph Laplacians.
         *
         * @param s the softthresholding parameter to be set
         * @param norm the normalization constant to be set
         * @param cfs the current estimate of the coefficients
         * @param LX the normalized laplacian of X
         * @param LY the normalized laplacian of Y
         * @param P the number of covariables
         * @param Q the number of responses
         * @param pi the current index of the column of X
         * @param qi the current index of the column of Y
         * @param psigx the penalty for the Laplacian of X
         * @param psigy the penalty for the Laplacien of Y
         */
        void graph_penalize
            (double &s, double &norm,
             const double psigx, const double psigy,
             arma::Mat<double> &LX, arma::Mat<double> &LY, arma::Mat<double> &cfs,
             const int P, const int Q,
             const int pi, const int qi, arma::rowvec& lx_rows) const;

        /**
         * Adds the penalty from the Laplacian of X to the softthresholding
         * parameter s and the normalization constant norm.
         *
         * @param s the softthresholding parameter to be set
         * @param norm the normalization constant to be set
         * @param cfs the current estimate of the coefficients
         * @param LX the normalized laplacian of X
         * @param P the number of covariables
         * @param pi the current index of the column of X
         * @param qi the current index of the column of Y
         * @param psigx the penalty for the Laplacian of X
         */
        void lx_penalize
            (double &s, double &norm, const double psigx, arma::Mat<double> &LX,
             arma::Mat<double> &cfs, const int P, const int pi,
             const int qi, arma::rowvec& lx_rows) const;

        /**
         * Adds the penalty from the Laplacian of X to the softthresholding
         * parameter s and the normalization constant norm.
         *
         * @param s the softthresholding parameter to be set
         * @param norm the normalization constant to be set
         * @param psigy the penalty for the Laplacien of Y
         * @param LY the normalized laplacian of Y
         * @param B the current estimate of the coefficients
         * @param Q the number of responses
         * @param pi the current index of the column of X
         * @param qi the current index of the column of Y
         */
        void ly_penalize
            (double &s, double &norm, const double psigy,
             arma::Mat<double> &LY, arma::Mat<double> &B, const int Q,
             const int pi, const int qi) const;

        /**
         * Calculates the softhresholding parameter as well as the normalisation constant.
         *
         * @param s the softthresholding parameter to be set
         * @param norm the normalization constant to be set
         * @param TXX the square of the design matrix
         * @param TXY the design times the response matrix
         * @param B the current estimate of the coefficients
         * @param LX the normalized laplacian of X
         * @param LY the normalized laplacian of Y
         * @param P the number of covariables
         * @param Q the number of responses
         * @param pi the current index of the column of X
         * @param qi the current index of the column of Y
         * @param psigx the penalty for the Laplacian of X
         * @param psigy the penalty for the Laplacien of Y
         * @param lower boolean flag whether only the lower triangular matrix of TXX is initialized
         */
        void set_params
            (double &s, double &norm,
             arma::Mat<double> &TXX, arma::Mat<double> &TXY,
             arma::Mat<double> &B,
             arma::Mat<double> &LX, arma::Mat<double> &LY,
             const int P, const int Q, const int pi, const int qi,
             const double psigx, const double psigy,
             arma::rowvec& txx_rows, arma::rowvec& lx_rows) const;
    };
}

#endif //NETREG_EDGENET_H
