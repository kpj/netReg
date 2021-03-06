% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/netReg-package.R
\docType{package}
\name{netReg-package}
\alias{netReg-package}
\title{Network-Regularized Regression Models}
\description{
\emph{netReg} fits linear regression models using network-regularization.
Network-regularization used graph prior as penality for the coefficients of linear models.
The graph can represent any relationship between the covariables/responses of the
model, for instance, some quantifiable biological relationship such as coexpression.
}
\details{
\emph{netReg} uses \emph{Armadillo} and \emph{TensorFlow} for
fast matrix computations and optimization.
}
\references{
Dirmeier, Simon and Fuchs, Christiane and Mueller, Nikola S and Theis,
 Fabian J (2018),
 netReg: Network-regularized linear models for biological association
 studies. \cr
 \emph{Bioinformatics}\cr \cr
 Abadi, Martín et al. (2016),
 Tensorflow: A system for large-scale machine learning. \cr
 \emph{12th USENIX Symposium on Operating Systems Design and Implementation (OSDI 16)}\cr \cr
 Powell M.J.D. (2009),
 The BOBYQA algorithm for bound constrained optimization
  without derivatives.\cr
 \url{http://www.damtp.cam.ac.uk/user/na/NA_papers/NA2009_06.pdf}
 Eddelbuettel, Dirk and Sanderson, Conrad (2014),
 RcppArmadillo: Accelerating R with high-performance C++ linear algebra.
 \emph{Computational Statistics & Data Analysis}
}
\author{
Simon Dirmeier | \email{simon.dirmeier@web.de}
}
\keyword{package}
