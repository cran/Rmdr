\name{rmdr}
\alias{rmdr}
\title{ R-Multifactor Dimensionality Reduction Function}
\description{
rmdr (R function of the MDR approach): Detection and Characterization of Gene-Gene Interactions and Gene-Environment Interactions in 
Genetic and Epidemiological Studies. MDR is a nonparametric and genetic model-free alternative to 
logistic regression for detecting and characterizing nonlinear interactions among discrete genetic
 and environmental attributes. 


}
\usage{
rmdr(data, cvk, nbr, ratio = NULL, randomize = FALSE)
}

\arguments{
  \item{data}{ the data to be used. The fisrt column describes the class variable (0 for unaffected and 1 for affected). The other columns describe the attributes with values 0,1,2.}
  \item{cvk}{ The number of cross-validation > 1 }
  \item{nbr}{ the number of attribute combinations to be considered}
  \item{ratio}{ the threshold that is used to pool attribute levels into two groups }
  \item{randomize}{ randomly order the data }
}

\value{
  A matrix giving the best combination of loci, the misclassification error and the prediction error.
  

}
\references{Hahn LW, Ritchie MD, Moore JH.: Multifactor dimensionality reduction software for detecting gene-gene and gene-environment interactions.Bioinformatics. 2003 Feb 12;19(3):376-82 }
\author{ Mounir Aout}

\examples{
data(mdrdata)
cvk<-10
nbr=2
res<-rmdr(mdrdata,10,2, randomize=TRUE)
}
\keyword{math}