matrix.matches <- function(mat1, mat2) { 
        result<-matrix(0,nrow(mat1),1)         
       I1<-1
        while (I1 <nrow(mat1)+1){ 
 I2<-seq(nrow(mat2))       
 JJ <- 1;
        while(length(I2) &&  JJ  < ncol(mat2)+1){
        I2 <- I2[mat2[I2, JJ] == mat1[I1,JJ]]; 
        JJ<-JJ+1
         } 
          result[I1,1]<-length(I2)
I1<-I1+1       
 }
         result
}