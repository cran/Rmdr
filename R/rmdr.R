.packageName <- "Rmdr"
rmdr<-function(data,cvk,nbr,ratio=NULL, randomize=FALSE){
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

# Start Cross-validation
for(l in 1:k){
cat(" Cross Validation", l, date(),"\n") 
xx<-data[-((1+(l-1)*m):(l*m)),1:n]
xx1<-xx[,2:n]
yy<-data[((1+(l-1)*m):(l*m)),1:n]
yy1<-yy[,2:n]

for(i in 1:ncol(tmp)){

y[,1]<-matrix.matches(tmp3,xx[,c(1,tmp[,i]+1)])
y[,2]<-matrix.matches(tmp4,xx[,c(1,tmp[,i]+1)])
y1[,1]<-matrix.matches(tmp3,yy[,c(1,tmp[,i]+1)])
y1[,2]<-matrix.matches(tmp4,yy[,c(1,tmp[,i]+1)])
y[,3]<-y[,1]/y[,2]
y1[,3]<-y[,1]/y[,2]

z[i,l+nbr]<-100*(sum(y[which(y[,3]<1),1])+sum(y[which(y[,3]>1),2]))/(N-m)
zz[i,l+nbr]<-100*(sum(y1[which(y1[,3]<1),1])+sum(y1[which(y1[,3]>1),2]))/(sum(y1[which(y1[,3]<1),1:2])+sum(y1[which(y1[,3]>1),1:2]))
}

z1[l]<-which.min(z[,l+nbr])
cat("The best set of loci is",z[z1[l],1:nbr],"\n")
}
z2<-diag(z[z1,(nbr+1):(k+nbr)])
z3<-diag(zz[z1,(nbr+1):(k+nbr)])
z4<-z[z1,1:nbr]
res<-cbind(z4,z2,z3)
colnames(res)<-c(rep(c("locus"),nbr), "misclassification error", "prediction error")
return(res)
}

