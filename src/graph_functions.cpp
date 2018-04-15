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

#include "graph_functions.hpp"

#ifdef _OPENMP
#include <omp.h>
#endif
#include <vector>
#include <cmath>

namespace netreg
{
    std::vector<double> degree_distribution(const arma::Mat<double>& x)
    {
        std::vector<double> degrees(x.n_rows);

        #pragma omp parallel for
        for (unsigned int i = 0; i < x.n_rows; ++i)
        {
            double rowSum = 0.0;
            for (unsigned j = 0; j < x.n_cols; ++j) rowSum += x(i, j);
            degrees[i] = rowSum;
        }

        return degrees;
    }

    arma::Mat<double> laplacian(const arma::Mat<double>& x)
    {
        std::vector<double> degrees = degree_distribution(x);
        arma::Mat<double> lap(x.n_rows, x.n_cols);

        // compute the normalized Laplacian
        #pragma omp parallel for
        for (unsigned int i = 0; i < x.n_rows; ++i)
        {
            for (unsigned int j = 0; j < x.n_cols; ++j)
            {
                if (i == j && degrees[i] != 0)
                    lap(i, j) = 1 - (x(i, j) / degrees[i]);
                else if (i != j && x(i, j) != 0)
                    lap(i, j) = -x(i, j) / std::sqrt(degrees[i] * degrees[j]);
                else
                    lap(i, j) = 0.0;
            }
        }

        return lap;
    }
}
