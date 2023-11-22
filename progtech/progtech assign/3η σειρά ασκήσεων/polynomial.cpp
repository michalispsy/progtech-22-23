#include <iostream>

using namespace std;

class Polynomial {
protected:
    class Term {
    protected:
        int exponent;
        int coefficient;   
        Term *next = nullptr;
        Term(int exp, int coeff, Term *n) : exponent(exp), coefficient(coeff), next(n) {};
        Term(){};
        friend class Polynomial;
    };

    public:
        Term *head = nullptr;
        
        //getters
        Term * get_next(Term *p) const
        {
            return p->next;
        }

        int get_coeff(Term *p) const 
        {
            return p->coefficient;
        }

        int get_exp(Term *p) const
        {
            return p->exponent;
        }

public:
    Polynomial() {};
    Polynomial(const Polynomial &p);
    ~Polynomial() {delete head;};

    Polynomial & operator = (const Polynomial &p);

    void addTerm(int expon, int coeff);
    double evaluate(double x);

    friend Polynomial operator+ (const Polynomial &p, const Polynomial &q);
    friend Polynomial operator* (const Polynomial &p, const Polynomial &q);

    friend ostream & operator << (ostream &out, const Polynomial &p);
};

// constructors
Polynomial::Polynomial(const Polynomial &p) 
{
    Term *n = head;
    Term *q = p.head;

    while( q != nullptr)
    {
        this->addTerm(q->exponent, q->coefficient);
        q = q->next;

        /*
            mporei na min einai toso apodotiko
            isos na prepei na kano 
            n->exponent = q->exponent
            n->coefficient = q->coefficient
        */
    }
}

Polynomial & Polynomial::operator = (const Polynomial &p) 
{
    delete head;
    Term *n = head;
    Term *q = p.head;

    while( q != nullptr)
    {
        this->addTerm(q->exponent, q->coefficient);
        q = q->next;
    }

    return *this;
}

// add and evaluate
void Polynomial::addTerm(int expon, int coeff) 
{
    Term *n = head, *prev = head;
    
    if(n == nullptr || expon > n->exponent) 
    {
        n = new Term(expon, coeff, head);
        head = n;
        return;
    }

    while(expon < n->exponent)
    {
        prev = n;
        n = n->next;
        if(n == nullptr) break;
    }
    
    if(n != nullptr && expon == n->exponent)
    {   
        n->coefficient += coeff;
        return;
    }

    n = new Term(expon, coeff, prev->next);
    prev->next = n;
}

double Polynomial::evaluate(double x)
{
    double result = 0;
    Term *n = head;
    while(n != nullptr)
    {   
        if(n->exponent == 0) return result + n->coefficient;

        double result_pol = x * n->coefficient;
        for(int i = 1; i < n->exponent; i++)
        {
           result_pol = result_pol*x;
        }
        
        result += result_pol;
        n = n->next;
    }

    return result;
}

//operators
ostream & operator << (ostream &out, const Polynomial &p) 
{
    Polynomial::Term *n = p.head; 
    bool first_sign = true;

    while(n != nullptr)
    {   
        if(p.get_coeff(n) == 0)
        {
            n = p.get_next(n);
            continue;
        }

        // prosima
        if(p.get_coeff(n) >= 0 && !first_sign) cout << " + ";
        else if (!first_sign) cout << " - ";

        if(first_sign && p.get_coeff(n) < 0) 
        {
            cout << "- "; 
            first_sign = false;
        }
        else first_sign = false;

        //o oros einai stathera
        if(p.get_exp(n) == 0) 
        {
            cout << abs(p.get_coeff(n)); 
            n = p.get_next(n);
            continue;
        }

        if(abs(p.get_coeff(n)) != 1) cout << abs(p.get_coeff(n));
        cout << 'x';

        //o oros einai protou bathmoy
        if(p.get_exp(n) == 1)
        { 
            n = p.get_next(n);
            continue; 
        }

        //dinami
        cout << '^' << p.get_exp(n);
        
        //epomenos oros
        n = p.get_next(n);
    }
    
    if(first_sign && n == nullptr) cout << '0';
    return out;
}

Polynomial operator+ (const Polynomial &p, const Polynomial &q)
{
    Polynomial::Term *n = p.head;
    Polynomial::Term *t = q.head; 
    Polynomial sum;

    while(n != nullptr && t != nullptr)
    {
        if(p.get_exp(n) == q.get_exp(t))
        {
            sum.addTerm(p.get_exp(n), p.get_coeff(n) + q.get_coeff(t));
            n = p.get_next(n);
            t = q.get_next(t);
            continue;
        }

        if(p.get_exp(n) > q.get_exp(t))
        {
            sum.addTerm(p.get_exp(n), p.get_coeff(n));
            n = p.get_next(n);
            continue;
        }

        sum.addTerm(q.get_exp(t), q.get_coeff(t));
        t = q.get_next(t);
    }

    if(t == nullptr)
    {
        while (n != nullptr)
        {
            sum.addTerm(p.get_exp(n), p.get_coeff(n));
            n = p.get_next(n);
        }
    }

    if(n == nullptr)
    {
        while (t != nullptr)
        {
            sum.addTerm(q.get_exp(t), q.get_coeff(t));
            t = q.get_next(t);
        }
    }

    return sum;
}


Polynomial operator* (const Polynomial &p, const Polynomial &q)
{
    Polynomial::Term *n = p.head;
    Polynomial::Term *t = q.head; 
    Polynomial prod;

    while(n != nullptr)
    {
        while(t != nullptr)
        {
            prod.addTerm(p.get_exp(n) + q.get_exp(t), p.get_coeff(n) * q.get_coeff(t));
            t = q.get_next(t);
        }
        t = q.head;
        n = p.get_next(n);
    }

    return prod;
}

int main() {
    Polynomial p; //
    p.addTerm(1, 1); // x
    p.addTerm(2, -1); // -(x^2) + x
    p.addTerm(4, 7);
    p.addTerm(10, 9);
    p.addTerm(17, -9);
    //p.addTerm(0, -1); // -1
    Polynomial q(p); // -x^2 + x
    q.addTerm( 1, -3); // -3x {} -x^2 - 2x

    cout << "P(x) = " << p << endl;
    cout << "P(0) = " << p.evaluate(0) << endl; //0
    cout << "P(1) = " << p.evaluate(1) << endl; //0
    cout << "P(-95) = " << p.evaluate(-95) << endl; //-210
    cout << "Q(x) = " << q << endl;
    cout << "Q(1) = " << q.evaluate(1) << endl; // -3
    cout << "(P+Q)(x) = " << p+q << endl; //-2x^2 -x
    cout << "(P*Q)(x) = " << p*q << endl; // x^4 +x^3 -2x^2
}