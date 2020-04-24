#ifndef LAB_2_1__PROTOTYPES_H
#define LAB_2_1__PROTOTYPES_H
void delete_elem(Planet **pPlanet, int &num);

int menu();

void read_db(const char* filename, Planet** pPlanet, int &num);

int StrToInt(char *s);

void add(Planet **pPlanet, int& num);

void sort_db(Planet **pPlanet, int num);

void write_db(const char *filename, Planet **pPlanet, int num);

void read_pl(const char* filename,Planet **pPlanet, int &num);

void write_pl(const char *filename, Planet **pPlanet, int num);

void operator >>(ifstream& file, Planet** pPlanet);

ostream& operator << (ostream& out, Planet** pPlanet);

#endif
