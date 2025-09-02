# 题目信息

# Programming Language

## 题目描述

Recently, Valery have come across an entirely new programming language. Most of all the language attracted him with template functions and procedures. Let us remind you that templates are tools of a language, designed to encode generic algorithms, without reference to some parameters (e.g., data types, buffer sizes, default values).

Valery decided to examine template procedures in this language in more detail. The description of a template procedure consists of the procedure name and the list of its parameter types. The generic type T parameters can be used as parameters of template procedures.

A procedure call consists of a procedure name and a list of variable parameters. Let's call a procedure suitable for this call if the following conditions are fulfilled:

- its name equals to the name of the called procedure;
- the number of its parameters equals to the number of parameters of the procedure call;
- the types of variables in the procedure call match the corresponding types of its parameters. The variable type matches the type of a parameter if the parameter has a generic type T or the type of the variable and the parameter are the same.

You are given a description of some set of template procedures. You are also given a list of variables used in the program, as well as direct procedure calls that use the described variables. For each call you need to count the number of procedures that are suitable for this call.

## 样例 #1

### 输入

```
4
void f(int,T)
void  f(T, T)
 void foo123   ( int,  double,  string,string  ) 
  void  p(T,double)
3
int a
 string    s
double x123 
5
f(a,  a)
  f(s,a   )
foo   (a,s,s)
 f  (  s  ,x123)
proc(a)
```

### 输出

```
2
1
0
1
0
```

## 样例 #2

### 输入

```
6
void f(string,double,int)
void f(int)
   void f  ( T  )
void procedure(int,double)
void f  (T, double,int)   
void f(string, T,T)
4
 int a
 int x
string  t
double  val  
5
f(t, a, a)
f(t,val,a)
f(val,a, val)
 solve300(val, val)
f  (x)
```

### 输出

```
1
3
0
0
2
```

# AI分析结果

### 题目内容
#### 编程语言
1. **题目描述**：最近，瓦莱里接触到了一种全新的编程语言。该语言最吸引他的是模板函数和过程。提醒一下，模板是一种语言工具，旨在编码通用算法，而不涉及某些参数（例如，数据类型、缓冲区大小、默认值）。

瓦莱里决定更详细地研究这种语言中的模板过程。模板过程的描述由过程名称及其参数类型列表组成。通用类型 `T` 参数可用作模板过程的参数。

过程调用由过程名称和变量参数列表组成。如果满足以下条件，我们称一个过程适用于此调用：
    - 它的名称与被调用过程的名称相同；
    - 它的参数数量与过程调用的参数数量相同；
    - 过程调用中变量的类型与相应参数的类型匹配。如果参数具有通用类型 `T`，或者变量和参数的类型相同，则变量类型与参数类型匹配。

给定一组模板过程的描述。还给出程序中使用的变量列表，以及使用所述变量的直接过程调用。对于每个调用，需要计算适用于此调用的过程数量。
2. **样例 #1**
    - **输入**
```
4
void f(int,T)
void  f(T, T)
 void foo123   ( int,  double,  string,string  ) 
  void  p(T,double)
3
int a
 string    s
double x123 
5
f(a,  a)
  f(s,a   )
foo   (a,s,s)
 f  (  s ,x123)
proc(a)
```
    - **输出**
```
2
1
0
1
0
```
3. **样例 #2**
    - **输入**
```
6
void f(string,double,int)
void f(int)
   void f  ( T  )
void procedure(int,double)
void f  (T, double,int)   
void f(string, T,T)
4
 int a
 int x
string  t
double  val  
5
f(t, a, a)
f(t,val,a)
f(val,a, val)
 solve300(val, val)
f  (x)
```
    - **输出**
```
1
3
0
0
2
```

### 算法分类
模拟

### 题解综合分析与结论
这道题的核心是模拟函数匹配过程，各题解思路总体一致，均先处理输入数据，存储函数信息和变量类型，再针对每个函数调用，检查其与已有函数的匹配情况。主要难点在于输入格式处理，包括去除空格、提取函数名与参数类型等。不同题解在具体实现方式上有所差异，如数据结构选择、类型匹配判断方法等。

### 所选的题解
1. **作者：HyyypRtf06 (5星)**
    - **关键亮点**：思路清晰，代码结构分明，通过多个函数分别处理输入、存储和匹配逻辑，可读性强。使用 `map` 和 `set` 等 STL 容器，简洁高效。
    - **个人心得**：提到思路虽明显，但调试易因粗心出错。
    - **重点代码**
```cpp
set<string> name_func;
const vector<string> Vector;
map<string,vector<string> > func[1010];
map<string,string> inter;
string Turn(string s,bool flag=true){
    for(int i=0;i<s.size();i++){
        if(s[i]==' '){
            s=s.substr(0,i)+s.substr(i+1);
            i--;
        }
    }
    if(flag){
        s=s.substr(4);
    }
    return s;
}
void Read_func(string s){
    string Name=s.substr(0,s.find('('));
    name_func.insert(Name);
    vector<string> v;
    string type;
    int start=s.find('(')+1;
    for(int i=start;i<s.size();i++){
        if(s[i]==','||s[i]==')'){
            type=s.substr(start,i-start);
            start=i+1;
            v.push_back(type);
        }
    }
    for(int i=0;;i++){
        if(func[i][Name]==Vector){
            func[i][Name]=v;
            break;
        }
    }
    return;
}
void Read_inter(){
    string s;
    string t;
    cin>>s>>t;
    inter[t]=s;
    return;
}
void Solve(string s){
    string Name=s.substr(0,s.find('('));
    vector<string> v;
    string type;
    int start=s.find('(')+1;
    for(int i=start;i<s.size();i++){
        if(s[i]==','||s[i]==')'){
            type=inter[s.substr(start,i-start)];
            start=i+1;
            v.push_back(type);
        }
    }
    int ans=0;
    for(set<string>::iterator it=name_func.begin();it!=name_func.end();it++){
        if(*it==Name){
            for(int i=0;;i++){
                if(func[i][*it]==Vector){
                    break;
                }
                if(func[i][*it].size()!=v.size()){
                    continue;
                }
                for(int j=0;j<v.size();j++){
                    if(v[j]!=func[i][*it][j]&&func[i][*it][j]!="T"){
                        goto Break;
                    }
                }
                ans++;
                Break:;
            }
        }   
    }
    cout<<ans<<endl;
    return;
}
```
    - **核心思想**：`Turn` 函数去除字符串空格并可选择去掉 `void` 前缀；`Read_func` 提取函数名和参数类型并存储；`Read_inter` 读取变量类型并记录；`Solve` 处理函数调用，判断匹配函数数量。
2. **作者：Empty_Dream (4星)**
    - **关键亮点**：代码简洁，利用 `istringstream` 自动分离字符串，处理输入较为巧妙。使用 `vector` 和 `map` 存储数据，逻辑清晰。
    - **重点代码**
```cpp
map<string, string> variable_type;
vector<vector<string>> function_type;
bool check(vector<string> a, vector<string> b){
    if (a.size() - 1!= b.size()) return false;
    if (a[1]!= b[0]) return false;
    for (int i = 1; i < b.size(); i++){
        if (a[i + 1]!= "T" && a[i + 1]!= variable_type[b[i]]) return false;
    }
    return true;
}
signed main(){
    scanf("%lld\n", &n);
    for (int i = 1; i <= n; i++){
        getline(cin, s);
        vector<string> name;
        for (char &c : s) if (c == '(' || c == ')' || c == ',') c = ' ';
        istringstream ss(s);
        while (ss >> s) name.push_back(s);
        function_type.push_back(name);
    } 
    scanf("%lld\n", &m);
    for (int i = 1; i <= m; i++){
        cin >> a >> b;
        variable_type[b] = a;
    }
    scanf("%lld\n", &k);
    for (int i = 1; i <= k; i++){
        int cnt = 0;
        getline(cin, s);
        vector <string> name;
        for (char &c : s) if (c == '(' || c == ')' || c == ',') c = ' ';
        istringstream ss(s);
        while (ss >> s) name.push_back(s);
        for (int j = 0; j < n; j++){
            if (check(function_type[j], name)) cnt++;
        }
        printf("%lld\n", cnt);
    }
    return 0;
}
```
    - **核心思想**：`check` 函数判断函数与调用是否匹配。主函数中，先处理函数输入，将函数各部分存入 `function_type`；再处理变量输入，记录变量类型；最后处理函数调用，通过 `check` 函数统计匹配函数数量。
3. **作者：Sexy_Foxy (4星)**
    - **关键亮点**：代码详细，对每个步骤都有清晰的实现，通过自定义函数去除字符串空格，便于后续处理。使用 `map` 存储函数和变量信息，查找效率较高。
    - **重点代码**
```cpp
map<string,vector<vector<string> > >fun;
map<string,string>type;
string get_space(string s){
    for(int i=0;i<s.size();i++){
        if(s[i]==' ')
        {
            s=s.substr(0,i)+s.substr(i+1);
            i--;
        }
    }
    return s;
}
int main()
{
    scanf("%d",&n);
    while(n--)
    {
        string qwq,s;
        cin>>qwq;
        getline(cin,s);
        s=get_space(s);
        int start=0;
        string name;
        while(s[start]!='(')
        {
            name+=s[start++];
        }
        string x;
        vector<string>a;
        for(int i=start+1;i<s.size();i++)
        {
            if(s[i]==','||s[i]==')')
            {
                a.push_back(x);
                x.clear();
            }
            else
            {
                x+=s[i];
            }
        }
        fun[name].push_back(a);
    }
    scanf("%d",&m);
    while(m--)
    {
        string ty,name;
        cin>>ty>>name;
        type[name]=ty;
    }
    scanf("%d",&k);
    getchar();
    while(k--)
    {
        string s;
        getline(cin,s);
        s=get_space(s);
        int start=0;
        string name;
        while(s[start]!='(')
        {
            name+=s[start++];
        }
        vector<string>a;
        string x;
        for(int i=start+1;i<s.size();i++)
        {
            if(s[i]==','||s[i]==')')
            {
                a.push_back(x);
                x.clear();
            }
            else
            {
                x+=s[i];
            }
        }
        int ans=0;
        for(int i=0;i<fun[name].size();i++)
        {
            vector<string>sum=fun[name][i];
            if(sum.size()!=a.size())
            {
                continue;
            }
            bool flag=true;
            for(int j=0;j<sum.size();j++)
            {
                if(type[a[j]]!=sum[j]&&type[a[j]]!="T"&&sum[j]!="T")
                {
                    flag=false;
                    break;
                }
            }
            if(flag)
            {
                ans++;
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```
    - **核心思想**：`get_space` 函数去除字符串空格。主函数中，先处理函数输入，提取函数名和参数类型存入 `fun`；再处理变量输入，记录变量类型到 `type`；最后处理函数调用，判断匹配函数数量并输出。

### 最优关键思路或技巧
1. **数据结构选择**：使用 `map` 存储函数信息（如函数名与参数类型的映射）和变量类型，利用其快速查找特性，提高匹配效率；`vector` 用于存储参数列表，方便处理参数数量和顺序。
2. **输入处理技巧**：通过多种方式处理输入字符串，如去除空格、利用 `istringstream` 分离字符串等，使输入数据更易于处理和分析。

### 拓展
此类题目属于字符串模拟类型，常见套路为根据给定规则处理字符串，提取关键信息并进行匹配或计算。类似题目通常围绕字符串解析、规则匹配展开，可通过练习此类题目提升字符串处理和逻辑实现能力。

### 洛谷相似题目
1. **P1055 [NOIP2008 普及组] ISBN 号码**：通过对输入字符串按特定规则处理，计算校验码并判断 ISBN 号码是否正确，考察字符串处理和规则应用。
2. **P1251 餐巾计划问题**：涉及字符串处理和费用计算，根据每天所需餐巾数量及不同处理方式的费用，规划最优方案，锻炼逻辑思维和问题解决能力。
3. **P1308 [NOIP2011 普及组] 统计单词数**：要求在给定字符串中按规则统计特定单词出现次数，重点在于字符串查找和匹配。 

---
处理用时：106.59秒