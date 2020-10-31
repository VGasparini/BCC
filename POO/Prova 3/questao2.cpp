// Vinicius Gasparini | Prova 3 - Questão 2

#include <bits/stdc++.h>
using namespace std;

class Complex {
  private:
    float a;
    float b;

  public:
    Complex(float n, float img){
      this->a = n;
      this->b = img;
    }

    Complex(float n){
      this->a = n;
      this->b = 0;
    }

    float getReal(){
      return this->a;
    }
    float getImag(){
      return this->b;
    }
    void setReal(float t){
      this->a = t;
    }
    void setImag(float t){
      this->b = t;
    }

    void show(){
      cout << this->getReal() << " ± " << this->getImag() << "i" << endl;
    }

    Complex operator* (Complex n2){
      Complex *r = new Complex(this->getReal() * n2.getReal() - this->getImag() * n2.getImag(),
                               this->getReal() * n2.getImag() + this->getImag() * n2.getReal());
      return *r;
    }

    float operator% (float c){
      Complex *r = this;
      return (*r).getReal() / c;
    }

    Complex operator- (){
      Complex *r = new Complex(-this->getReal(), - this->getImag());
      return *r;
    }

    Complex operator! (){
      float u,w;
      u = this->getImag();
      w = this->getReal();
      this->setReal(u);
      this->setImag(w);
    }


  };

int main(){
  Complex *n1 = new Complex(1);                                                 // Questão b
  Complex *n2 = new Complex(10,5);                                              // Questão c

  cout << (*n1).getReal() << endl;                                              // Questão d
  cout << (*n2).getReal() << " " << (*n2).getImag() << endl;

  (*n1).show();                                                                 // Questão e
  (*n2).show();

  ((*n1) * (*n2)).show();                                                       // Questão f

  cout << (*n2) % 2 << endl;                                                    // Questão g

  (-(*n2)).show();                                                              // Questão h

  !(*n2);                                                                       // Questão i
  ((*n2)).show();

}
