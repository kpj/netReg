#' Package: netReg
#'
#' \emph{netReg} is a package for generalized linear regression that includes prior graphs in the models objective function.
#' The models are a generalization of the \emph{LASSO} by Tibshirani.
#' \emph{netReg} uses \emph{Armadillo}, \emph{Intel MKL}, \emph{OpenBLAS}, \emph{BLAS} and \emph{LAPACK} for fast matrix computations and
#' \emph{Dlib} for constrained derivate-free optimization.
#' 
#'
#' @name netReg-package
#' @author Simon Dirmeier | \email{simon.dirmeier@@gmx.de}
#' @docType package
#' @keywords package
#' @references 
#'  Friedman J., Hastie T., Hoefling H. and Tibshirani R. (2007), 
#'  Pathwise coordinate optimization.\cr
#'  \emph{The Annals of Applied Statistics}\cr \cr
#'  Friedman J., Hastie T. and Tibshirani R. (2010),
#'  Regularization Paths for Generalized Linear Models via Coordinate Descent. \cr
#'  \emph{Journal of Statistical Software}\cr \cr
#'  Fu W. J. (1998),  Penalized Regression: The Bridge Versus the Lasso.\cr
#'  \emph{Journal of Computational and Graphical Statistics}\cr \cr
#'  Cheng W. and Wang W. (2014), Graph-regularized dual Lasso for robust eQTL mapping.\cr
#'  \emph{Bioinformatics}\cr \cr
#'  Powell M.J.D. (2009), 
#'  The BOBYQA algorithm for bound constrained optimization without derivatives.\cr
#'  \url{http://www.damtp.cam.ac.uk/user/na/NA_papers/NA2009_06.pdf}
NULL