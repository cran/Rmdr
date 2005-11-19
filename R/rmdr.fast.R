.packageName <- "Rmdr"

.First.lib <- function(lib, pkg){
 library.dynam("Rmdr", pkg, lib)
}

rmdr.fast<-function(data,cvk,nbr,ratio=NULL, randomize=FALSE){
N<-dim(data)[1]
n<-dim(data)[2]
if(is.null(ratio)) ratio<-length(which(data[,1]==1))/length(which(data[,1]==0)) 
print(ratio)
if (randomize==TRUE){
oo<-sample(1:N)
data<-data[oo,]
}
k<-cvk
m<-N%/%k
nbr<-nbr
tmp<-combn(n-1,nbr)
z<-matrix(0,choose(n-1,nbr),k+nbr)
zz<-matrix(0,choose(n-1,nbr),k+nbr)
z[,1:nbr]<-t(tmp)
zz[,1:nbr]<-t(tmp)
z1<-rep(0,k)
tmp0<-list(c(0,1,2))
tmp3<-cbind(rep(1,3^nbr),expand.grid(rep(tmp0,nbr)))
tmp4<-cbind(rep(0,3^nbr),expand.grid(rep(tmp0,nbr)))

tt3<-dim(tmp3)[1]
y<-matrix(0,tt3,3)
y1<-matrix(0,tt3,3)

for(l in 1:k){
xx<-data[-((1+(l-1)*m):(l*m)),1:n]
yy<-data[((1+(l-1)*m):(l*m)),1:n]
 nltmp34<-tt3
 nc<-nbr+1
 nlxx<-N-m
 ncxx<-n
 nlyy<-m
 nltmp<-nbr
 nctmp<-choose(n-1,nbr) 
 cat(" Cross Validation", l,"\n") 
resultat<-.C("mdr",as.integer(nltmp34),as.integer(nc), as.integer(nlxx), as.integer(nlyy),as.integer(ncxx), as.integer(nltmp), as.integer(nctmp),  as.double(as.matrix(tmp)), as.double(as.matrix(tmp3)), as.double(as.matrix(tmp4)), as.double(as.matrix(xx)), as.double(as.matrix(yy)) ,matrix(0,nctmp,1) ,matrix(0,nctmp,1),ratio, PACKAGE="Rmdr")
 z[,l+nbr]<-resultat[[13]]
 zz[,l+nbr]<-resultat[[14]]
 z1[l]<-which.min(z[,l+nbr])
 cat("The best set of loci is ",z[z1[l],1:nbr],"\n")
rm(xx,yy,resultat)
}
z2<-diag(z[z1,(nbr+1):(k+nbr)])
z3<-diag(zz[z1,(nbr+1):(k+nbr)])
z4<-z[z1,1:nbr]
res<-cbind(z4,z2,z3)
colnames(res)<-c(rep(c("locus"),nbr), "misclassification error", "prediction error")
return(res)
}