#include "header.h"
class delta_function{
private:
    mpscs transitions;
public:
    delta_function();
    void add_delta_function(string s1, string s2, char k);
    mpscs get_transitions();
};
