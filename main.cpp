#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;

class Declaration{
    private:
    string property;
    string value;

    public:
    void addProperty(const string &prop){
        property = prop;
    }

    void addValue(const string &val){
        value = val;
    }
    string getProperty()const{
        return property;
    }
    string getValue()const{
        return value;
    }
};

class Rule{
    private:
    string selector;
    vector<Declaration>declarations;

    public:
    void addSelector(const string &sel){
        selector=sel;
    }
    void addDeclaration(Declaration &&d){
        declarations.push_back(move(d));
    }
    string getSelector()const{
        return selector;
    }
    const vector<Declaration>&getDeclaration()const{
        return declarations;
    }
};

class StyleSheet{
    private:
    vector<Rule>rules;

    public: 
    string trim(const string &str){
        size_t first = str.find_first_not_of(" \n\t");
        if(first==string::npos)return "";
        size_t last = str.find_last_not_of(" \n\t");
        return str.substr(first, (last-first+1));
    };
    void print(){
        for(auto &rule:rules){
            cout<<"Selector: "<<rule.getSelector()<<endl;
            for(auto &decl:rule.getDeclaration()){
                cout<<" "<<" ";
                cout<<decl.getProperty()<<": "<<decl.getValue()<<endl;
            }
            cout<<endl;
        }
    };
    StyleSheet(const string &cssContents){
        Rule currentRule;
        stringstream ss(cssContents);
        string line;
        bool inRule=false;

        while(getline(ss, line, '\n')){
            line=trim(line);
            if(!inRule){
                size_t pos = line.find('{');
                if(pos!=string::npos){
                    currentRule.addSelector(trim(line.substr(0, pos)));
                    inRule=true;
                }
            }else{
                size_t pos=line.find('}');
                if(pos!=string::npos){
                    rules.push_back(currentRule);
                    currentRule=Rule();
                    inRule=false;
                }else{
                    size_t colon=line.find(':');
                    size_t semi=line.find(';');
                    if(colon!=string::npos && semi!=string::npos){
                        Declaration d;
                        d.addProperty(trim(line.substr(0, colon)));
                        d.addValue(trim(line.substr(colon+1, (semi-colon-1))));
                        currentRule.addDeclaration(move(d));
                    }
                }
            }
        }
    }
};

int main(){
    string cssStyle=R"(
        body{
            background:gray;
            padding:10px;
        }
        h1{
            font-size:30px;
            color:gray;
        }
        p{
            color:black;
            font-size:20px;
        }
        h2.highlight{
            background:yellow;
            padding:10px;
            border-radius:10px;
        }
        div.note{
            height:150px;
            padding:10px;
            background:blue;
        }
    )";

    StyleSheet sheet(cssStyle);
    sheet.print();
    return 0;
}