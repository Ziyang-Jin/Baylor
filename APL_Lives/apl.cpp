#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Array {
    vector<int> dimension = {1, 1, 0};
    vector<int> array;
};

struct Variable {
    string name;
    Array value;
};

vector<Variable> vars;

void parse(string line, vector<string>& ss);
void printArray(Array rsf);
void evaluate(vector<string>& ss, Array& rsf);
vector<int> get_lo_drop(vector<string>& ss);
vector<int> get_lo_rho(vector<string>& ss);
Array parenthesis(vector<string>& ss);


int main() {
    string line;
    ifstream myfile;
    myfile.open("input.txt");
    int count = 1;
    if (myfile.is_open()) {
        while(getline(myfile, line) && (line != "#")) {
            Array rsf;
            rsf.dimension = {1, 1, 0};
            vector<string> ss; 
            cout << "Case " << count++ << ": " << line << endl;
            parse(line, ss);
            evaluate(ss, rsf);
            printArray(rsf);
        }
        myfile.close();
    } else
    cout << "Unable to open file" << endl;
return 0;
}

void parse(string line, vector<string>& ss) {
    string s = "";
    for(int i = 0; i < line.length(); i++) {
        if(line[i] != ' ') {
            s += line[i];
        } else {
            ss.push_back(s);
            s = "";
        }
    }
    ss.push_back(s);
}

void printArray(Array a) {
    int index = 0;
    for(int i = 0; i < a.dimension[0]; i++) {
        for(int j = 0; j < a.dimension[1]; j++) {
            for(int k = 0; k < a.dimension[2]; k++) {
                cout << a.array[index] << " ";
                index++;
                index = index % a.array.size();
            }
            cout << endl;
        }
        if(i < a.dimension[0] - 1)
            cout << endl;
    }
}

void evaluate(vector<string>& ss, Array& rsf) {
    string s;
    if(ss.size() > 0) {
        s = ss.back();
        ss.pop_back();
        if(isdigit(s[0])) {
            rsf.array.insert(rsf.array.begin(), stoi(s, NULL));
            rsf.dimension[2] = rsf.array.size();
        } else if (s == ")") {
            rsf = parenthesis(ss);
        } else if (s == "iota") {
            int n = rsf.array.back();
            rsf.array.pop_back();
            for(int i = 0; i < n; i++)
                rsf.array.push_back(i+1);
            rsf.dimension[2] = rsf.array.size();
        } else if (s == "drop") {
            vector<int> lo = get_lo_drop(ss);
            rsf.array.erase(rsf.array.begin(), rsf.array.begin()+lo[0]);
            rsf.dimension[2] = rsf.array.size();
        } else if (s == "rho") {
            vector<int> lo = get_lo_rho(ss);
            rsf.dimension = lo;
        } else if (s == "=") {
            s = ss.back();
            ss.pop_back();
            bool find = false;
            for(int i = 0; i < vars.size(); i++) {
                if (vars[i].name == s) {
                    vars[i].value = rsf;
                    find = true;
                    break;
                }
            }
            if(!find) {
                Variable x;
                x.name = s;
                x.value = rsf;
                vars.push_back(x);
            }
        } else if (s == "+" || s == "-" || s == "*") {
            char op;
            if(s == "+") op = '+';
            else if (s == "-") op = '-';
            else if (s == "*") op = '*';
            s = ss.back();
            ss.pop_back();
            if(isdigit(s[0])) {
                int n = rsf.array.size();
                vector<int> lo;
                lo.insert(lo.begin(), stoi(s, NULL));
		for(int i = 0; i < (n-1); i++) {
                    s = ss.back();
                    ss.pop_back();
                    lo.insert(lo.begin(), stoi(s, NULL));
                }
                for(int i = 0; i < n; i++) {
                    if (op == '+')
                        rsf.array[i] = lo[i] + rsf.array[i];
                    else if (op == '-')
                        rsf.array[i] = lo[i] - rsf.array[i];
                    else // op == '*'
                        rsf.array[i] = lo[i] * rsf.array[i];
                }
            } else if (s == ")"){
                Array lo = parenthesis(ss);
                int n = rsf.array.size();
                if (n == 1) {
                    for(int i = 0; i < lo.array.size(); i++) {
                        if (op == '+')
                            lo.array[i] = lo.array[i] + rsf.array[0];
                        else if (op == '-')
                            lo.array[i] = lo.array[i] - rsf.array[0];
                        else // op == '*'
                            lo.array[i] = lo.array[i] * rsf.array[0];
                    }
                    rsf = lo;
                } else {
                    for(int i = 0; i < n; i++) {
                        if (op == '+')
                            rsf.array[i] = lo.array[i] + rsf.array[i];
                        else if (op == '-')
                            rsf.array[i] = lo.array[i] - rsf.array[i];
                        else // op == '*'
                            rsf.array[i] = lo.array[i] * rsf.array[i];
                    }
                }
            } else { // s is a variable
                for(int i = 0; i < vars.size(); i++) {
                    if(vars[i].name == s) {
                        Array x = vars[i].value;
                        for(int j = 0; j < x.array.size(); j++)
                            x.array[j] = x.array[j] + rsf.array.back();
                        rsf.array = x.array;
                    }
                }
            }
        } else if (s == "/") {
            s = ss.back();
            ss.pop_back();
            char op;
            if (s == "+") op = '+';
            else if (s == "-") op = '-';
            else op = '*'; // s == "*"
            Array x;
            x.dimension[0] = 1;
            x.dimension[1] = rsf.dimension[0];
            x.dimension[2] = rsf.dimension[1];
            int n = rsf.dimension[2];
            for(int i = 0; i < x.dimension[1]; i++) {
                for(int j = 0; j < x.dimension[2]; j++) {
                    int temp = n;
                    int a, b;
                    while(temp > 1) {
                        b = rsf.array.back();
                        rsf.array.pop_back();
                        a = rsf.array.back();
                        rsf.array.pop_back();
                        if(op == '+') a = a + b;
                        else if(op == '-') a = a - b;
                        else a = a * b;
                        rsf.array.push_back(a);
                        temp--;
                    }
                    a = rsf.array.back();
                    rsf.array.pop_back();
                    x.array.insert(x.array.begin(), a);
                }
            }
            rsf = x;
        } else { // s is a variable
            bool find = false;
            for(int i = 0; i < vars.size(); i++) {
                if (vars[i].name == s) {
                    find = true;
                    rsf = vars[i].value;
                    break;
                }
            }
            if(!find) {
                Variable x;
                x.name = s;
                vars.push_back(x);
            }
        }
        evaluate(ss, rsf);
    }
}

vector<int> get_lo_drop(vector<string>& ss) {
    vector<int> rv;
    string s = ss.back();
    ss.pop_back();
    if (isdigit(s[0])) {
        rv.push_back(stoi(s, NULL));
    } else if (s == ")") { // s = ")"
        rv = parenthesis(ss).array;
    }
    return rv;
}

vector<int> get_lo_rho(vector<string>& ss) {
    vector<int> rv;
    string s = ss.back();
    ss.pop_back();
    if(isdigit(s[0])) {
        int count = 2;
        rv.insert(rv.begin(), stoi(s, NULL));
        while(ss.size() > 0 && count > 0) {
            s = ss.back();
            if(isdigit(s[0])) {
                rv.insert(rv.begin(), stoi(s, NULL));
                count--;
            } else
                break;
            ss.pop_back();
        }
        for(int i = 0; i < count; i++)
            rv.insert(rv.begin(), 1);
    } else { // s = ")"
        rv = parenthesis(ss).array;
    }
    return rv;
}

Array parenthesis(vector<string>& ss) {
    vector<string> sub;
    Array rv;
    rv.dimension = {1, 1, 0};
    string s = ss.back();
    ss.pop_back();
    int count = 1;
    while (ss.size() > 0) {
        if (s != "(") {
            sub.insert(sub.begin(), s);
            if (s == ")")
                count++;
            s = ss.back();
            ss.pop_back();
        } else {
            if (count == 1) break;
            else {
                sub.insert(sub.begin(), s);
                count--;
            }
        }
    }
    evaluate(sub, rv);
    return rv;
}
