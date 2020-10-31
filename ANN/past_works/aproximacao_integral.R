f<-function(x){return(x^(1/2)*exp(-x))}  // Equacao original
g<-function(x){return(1/(x^(5/2) * exp(1/x)))} // Modificada

simpson <- function(f, a, b, n) {
  n <- max(c(2*(n %/% 2), 4))
  h <- (b-a)/n
  x.vec1 <- seq(a+h, b-h, by = 2*h)
  x.vec2 <- seq(a+2*h, b-2*h, by = 2*h)
  f.vec1 <- sapply(x.vec1, f)
  f.vec2 <- sapply(x.vec2, f)
  S <- h/3*(f(a) + f(b) + 4*sum(f.vec1) + 2*sum(f.vec2))
  return(S)
}

simpson(g,0.000000001,1/2,100)
integrate(f,2,Inf)


metodo_euler <- function(f, t0, y0, n, a, b){
     respostas = c()
     h = (b - a) / n
     respostas[1] = y0
     for (i in 1:n){
         yn = y0 + h * f(t0 + (i - 1) * h, y0)
         y0 = yn
         respostas[i + 1] = yn
     }
     return(respostas)
}

metodo_rungeKutta2 <- function(f, t0, y0, n, a, b){
     respostas = c()
     h = (b - a) / n
     respostas[1] = y0
     for (i in 1:n){
         yn_aux = y0 + h * f(t0 + (i - 1) * h, y0)
         yn = y0 + h/2 * (f(t0 + (i - 1) * h, y0) + f(t0 + i * h, yn_aux))
         y0 = yn
         respostas[i + 1] = yn
     }     
     return(respostas)
}

metodo_rungeKutta4 <- function(f, t0, y0, n, a, b){
     respostas = c()
     h = (b - a) / n
     respostas[1] = y0
     for (i in 1:n){
         y1 = y0
         y2 = y0 + h/2 * f(t0 + (i - 1) * h, y1)
         y3 = y0 + h/2 * f(t0 + (i - 1/2) * h, y2)
         y4 = y0 + h * f(t0 + (i - 1/2) * h, y3)
         yn = y0 + h/6 * (f(t0 + (i - 1) * h, y1) + 2 * f(t0 + (i - 1/2) * h, y2)+ 2 * f(t0 + (i - 1/2) * h, y3) + f(t0 + i * h, y4))
         y0 = yn
         respostas[i + 1] = yn
     }     
     return(respostas)
}


h <-function(x,y){return((x+1)/(y+1))}
t0h = 1
y0h = 0.25
n = 20
ah = 0
bh = 1

metodo_euler(h,t0h,y0h,n,ah,bh)
metodo_rungeKutta2(h,t0h,y0h,n,ah,bh)
metodo_rungeKutta4(h,t0h,y0h,n,ah,bh)

plot(metodo_euler(h,t0h,y0h,n,ah,bh),type="o",col="blue")
plot(metodo_rungeKutta2(h,t0h,y0h,n,ah,bh),type="o",col="red")
plot(metodo_rungeKutta4(h,t0h,y0h,n,ah,bh),type="o",col="orange")

