#include <iostream>
#include "string"
#include <fstream>
#include <map>

using namespace std;

void output(map <int, string> a, int k, string var[]){
	int c, s = a.size();
	for (int i = 0; i < k; i++){
		cout << a[0] << i+1 << ": ";
		for (int j = 1; j < s; j++){
			cout << " " << j << " - " << a[j] << ",";
		}
		cout << endl << "Choice: ";
		cin >> c;
		var[i] = a[c];
	}
}

int main(){
	double var[3];
	string type[3], oper[2], mod[3];
	map <int, string> types = {
		{0, "Type"},{1, "int"},{2, "float"},{3, "double"},{4, "long"}
	};
	map <int, string> mods = {
		{0, "Mod"},{1, "long"},{2, "short"},{3, "unsigned"}, {4, "signed"}, {5, ""}
	};
	map <int, string> opers = {
		{0, "Operation"},{1, "+"},{2, "-"},{3, "*"}, {4, "/"}
	};
	output(types, 3, type);
	output(mods, 3, mod);
	output(opers, 2, oper);
	for (int i = 0; i < 3; i++){
		cout << "Variable " << i+1 << " " << mod[i] << " " << type[i] << " - ";
		cin >> var[i];
	}
	ofstream fout("func_1.cpp");
	fout << "#include <iostream>" << endl;
	fout << "int f(void) {"<< endl;
	for (int i = 0; i < 3; i++){
		fout << mod[i] << " " << type[i] << " var" << i+1 << " = " << var[i] << ";"<< endl;
	}
	fout << "std::cout";
	for (int j = 0; j < 3; j++){
		fout << " << var" << j+1;
		if (j!=2) fout << " << '" << oper[j] << "'";
		else fout << " << '=' ;" << endl;
	}
	fout << "std::cout <<";
	for (int m = 0; m < 3; m++){
		fout << " var" << m+1;
		if (m!=2) fout << " " << oper[m];
		else fout << " << std::endl;" << endl;
	}
	fout << "return 0;" << endl;
	fout << "}" << endl;
	fout.close();
	return 0;
}
