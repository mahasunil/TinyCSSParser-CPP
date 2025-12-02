#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

class Declaration
{
private:
    string property;
    string value;

public:
    void addProperty(const string &prop)
    {
        property = prop;
    }

    void addValue(const string &val)
    {
        value = val;
    }
    string getProperty() const
    {
        return property;
    }
    string getValue() const
    {
        return value;
    }
};

class Rule
{
private:
    string selector;
    vector<Declaration> declarations;
    vector<Rule> nestedRules;

public:
    void addSelector(const string &sel)
    {
        selector = sel;
    }
    void addDeclaration(Declaration &&d)
    {
        declarations.push_back(move(d));
    }
    void addNestedRule(Rule &&r)
    {
        nestedRules.push_back(move(r));
    }
    string getSelector() const
    {
        return selector;
    }
    const vector<Declaration> &getDeclaration() const
    {
        return declarations;
    }
    const vector<Rule> &getNestedRule() const
    {
        return nestedRules;
    }
};

class StyleSheet
{
private:
    vector<Rule> rules;

public:
    string trim(const string &str)
    {
        size_t first = str.find_first_not_of(" \n\t");
        if (first == string::npos)
            return "";
        size_t last = str.find_last_not_of(" \n\t");
        return str.substr(first, (last - first + 1));
    };

    StyleSheet(const string &cssContents)
    {
        stringstream ss(cssContents);
        string line;

        stack<Rule> stackRules;

        while (getline(ss, line))
        {
            string buffer = trim(line);
            if (buffer.empty())
                continue;

            size_t openCurly = buffer.find('{');
            size_t closeCurly = buffer.find('}');

            if (openCurly != string::npos)
            {
                string selector = trim(buffer.substr(0, openCurly));
                Rule newRule;
                newRule.addSelector(selector);

                stackRules.push(move(newRule));

                buffer = trim(buffer.substr(openCurly + 1));
                continue;
            }
            else if (closeCurly != string::npos)
            {
                if (!stackRules.empty())
                {
                    Rule stackTopRule = move(stackRules.top());
                    stackRules.pop();

                    if (stackRules.empty())
                    {
                        rules.push_back(move(stackTopRule));
                    }
                    else
                    {
                        stackRules.top().addNestedRule(move(stackTopRule));
                    }
                }
                buffer = trim(buffer.substr(closeCurly + 1));
                continue;
            }
            else
            {
                size_t semi = buffer.find(';');
                if (semi == string::npos)
                    break;
                string stmnt = trim(buffer.substr(0, semi + 1));

                size_t colon = buffer.find(':');
                if (colon != string::npos)
                {
                    string prop = trim(stmnt.substr(0, colon));
                    string val = trim(stmnt.substr(colon + 1, stmnt.size() - colon - 2));

                    Declaration d;
                    d.addProperty(prop);
                    d.addValue(val);

                    if (!stackRules.empty())
                    {
                        stackRules.top().addDeclaration(move(d));
                    }
                    else
                    {
                    }
                }

                buffer = trim(buffer.substr(semi + 1));
                continue;
            }
        }

        while (!stackRules.empty())
        {
            Rule unfinished_StackRule = move(stackRules.top());
            stackRules.pop();
            rules.push_back(move(unfinished_StackRule));
        }
    }

    void printStyle(const Rule &rule, int indent = 0)
    {
        string space(indent * 2, ' ');
        cout << space << rule.getSelector() << endl;
        for (const auto &decl : rule.getDeclaration())
        {
            cout << space << ' ' << decl.getProperty() << ": " << decl.getValue() << endl;
        }
        for (const auto &nested : rule.getNestedRule())
        {
            printStyle(nested, indent + 1);
        }
    }

    void print()
    {
        for (const auto rule : rules)
        {
            printStyle(rule);
            cout << endl;
        }
    }
};

int main()
{
    string cssStyle = R"(
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
             .main{
                max-width:700px;
                margin:0 auto;
            }
        }
        @media(min-width:761px){
              p{
            color:gray;
            font-size:17px;
        }
        }

    )";

    StyleSheet sheet(cssStyle);
    sheet.print();
    return 0;
}