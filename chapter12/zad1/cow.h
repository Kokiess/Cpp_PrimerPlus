#ifndef  COW_H
class Cow
{
private:
    char name [20];
    char * hobby;
    double weight;
public:
    Cow();
    Cow (const char * nm, const char * ho, double wt);
    Cow (const Cow & c);
    Cow & operator = (const Cow & c);
    void ShowCow () const;
};
#endif // COW_H

