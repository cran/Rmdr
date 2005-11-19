\name{matrix.matches}
\alias{matrix.matches}
\title{ matrix matches function}
\description{
matrix.matches returns a matrix of total matches of
     its first argument in its second. Each row of mat1 is matched against mat2 rows.


}
\usage{
matrix.matches(mat1,mat2)
}

\arguments{
  \item{mat1}{matrix: the values to be matched.}
  \item{mat2}{matrix: the values to be matched against.}
  }

\value{
  An integer matrix giving the number of matches. Each row gives the sum of matches.


}
\references{ }
\author{ Mounir Aout}

\examples{
x1<-matrix(sample(0:2,10,replace=TRUE),5,2)
x2<-matrix(sample(0:2,24,replace=TRUE),12,2)
res<-matrix.matches(x1,x2)
}
\keyword{math}