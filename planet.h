#ifndef LAB_2_1__PLANET_H
#define LAB_2_1__PLANET_H

class Planet{
public:

    Planet();

    void print();

    char* get_name();

    unsigned int get_dim();

    bool get_life();

    unsigned int get_sp_count();

    void set_name(const char* name = nullptr);

    void set_dim(unsigned long dim = 0);

    void set_life(bool life = 0);

    void set_sp_count(unsigned int sp_count = 0);

    friend bool operator ==(Planet& a,Planet& b);

    friend bool operator <(Planet& a,Planet& b);

    ~Planet();

private:
    char* name;
    unsigned long dim;
    bool life;
    unsigned int sp_count;
};

#endif