# 题目信息

# yyy2015c01 的 IDE 之 Call Stack

## 题目背景

在 2020 年的某一天，我们的 yyy2015c01 同学想要开发一套 IDE。


## 题目描述

作为他开发团队中的一员，你不幸地 yyy2015c01 被选入了 Debugger 的开发组。

yyy2015c01 设想的 Debugger 由几部分组成，其中的一个小组件就是 Call Stack——中文称之为 “调用栈”。

由于 IDE 目前还是内测版，开发组需要先编一个能识别参数表的 Call Stack 来看看效果如何。这个任务交由你来完成。

开发组假想的 Call Stack 能实现识别 `int` 和 `char` 参数表，以辨别出不同的函数，规则是：

```
int fac1(int n);
```

和

```
int fac1(char n);
```

是两个不同的函数；但

```
int Fac1(int n,int m);
```

和

```
int FAC1(int x,int y);
```

被认为是相同的函数。也就是说，这个 Call Stack 认的不是参数名，而是其类型和忽略大小写的函数名。

注意：`int main()` 可能会出现，也可能不出现；无论它有没有出现，都不能将其算入函数中。

请你编写一个 Call Stack，并在所有函数调用完后输出这个程序一共有多少个不完全相同的函数（保证程序中的每个函数至少调用一次）。


## 说明/提示

每个函数的参数最多有 $10$ 个，每行的输入数据长度均不超过 $255$。

向本题主人公 yyy2015c01 同学致敬！


## 样例 #1

### 输入

```
2
FAC1 (N=233, M=65 'A', A=0)
main ()
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
fac1 (N=250)
FAC1 (a=987)
```

### 输出

```
1
```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是通过特定数据结构存储函数信息并判重，以统计不同函数的数量。主要区别在于数据结构的选择和具体实现方式。
1. **思路方面**：多数题解通过将函数名转为小写统一处理，再根据单引号判断参数类型。对于每个函数调用，提取函数名和参数类型信息，与已记录的函数进行比较。
2. **算法要点**：关键在于准确提取函数名和参数类型，并合理选择数据结构进行存储和判重。如使用结构体、`vector`、`map`、`set`等。
3. **解决难点**：主要难点是处理输入格式，包括函数名后的空格、参数间的逗号以及单引号的判断。同时要注意忽略`main`函数。

综合质量来看，以下题解相对较好：
 - **Alex_Wei**：思路清晰，代码结构合理，通过结构体和`vector`存储函数信息，单独写函数处理参数，提高可读性。
 - **OoXiao_QioO**：利用`map`作为桶，将函数名和参数类型组合成字符串进行判重，实现简洁。但使用了`gets()`存在版本兼容性问题。
 - **zimingsun23**：使用`map<pair<vector<bool>,string>,bool>`判重，代码简洁，利用`tolower`函数转换大小写。

### 所选题解
- **Alex_Wei（5星）**
    - **关键亮点**：代码结构清晰，模块化设计，将参数处理封装成函数，便于理解和维护。
    - **核心代码**：
```cpp
struct fact{
    string na;
    vector <int> para;
};
vector <fact> ans;
int strcmp(string a,string b) {
    if(a.size()!=b.size())return 0;
    for(int x=0;x<a.size();x++)if(a[x]!=b[x])return 0;
    return 1;
}
vector <int> getpara() {
    string p;
    int pc=0;
    vector <int> para;
    getline(cin,p);
    for(int x=0;x<p.size();x++){
        if(p[x]==','||p[x]==')')para.pb(pc),pc=0;
        if(p[x]==39)pc=1;
    }
    return para;
}
int main() {
    cin>>n;
    for(int x=1;x<=n;x++){
        string na;
        cin>>na;
        for(int y=0;y<na.size();y++)if(na[y]<'a')na[y]+=32;
        if(strcmp(na,"main"))continue;
        int same=1;
        vector <int> para=getpara();
        for(int y=0;y<ans.size();y++){
            fact cmp=ans[y];
            if(cmp.para.size()!=para.size()||!strcmp(cmp.na,na))same=0;
            else for(int z=0;z<cmp.para.size();z++)
                    if(cmp.para[z]!=para[z])same=0;
        }
        if(!same||x==1)ans.pb((fact){na,para});
    }
    cout<<ans.size();
    return 0;
}
```
    - **核心实现思想**：定义`fact`结构体存储函数名和参数类型`vector`。`getpara`函数处理输入参数，判断参数类型。主函数中读入函数名并转换为小写，跳过`main`函数，与已有函数比较判重。
 - **OoXiao_QioO（4星）**
    - **关键亮点**：思路巧妙，将函数名和参数类型组合成字符串，利用`map`判重，代码简洁。
    - **核心代码**：
```cpp
map<string,int> M;
string x;
char s[100001],s1[100001];
int main() {
    int n,i,l,cnt=0,f;
    cin>>n;
    while(n--) {
        scanf("%s",s);
        l = strlen(s);
        if(strcmp(s,"main")==0)
            continue;
        for(i=0;i<l;i++)
            if(isupper(s[i])) 
                s[i] += 32;
        x = s;
        getchar();
        gets(s1);
        l = strlen(s1);
        for(i=0;i<l;i++) {
            f = 1;
            if(s1[i]=='=') {
                while(s1[i]!=','&&i<l) {
                    i++;
                    if(s1[i]=='\'') {
                        f = 0;
                        break;
                    }
                }
            }
            if(f)
                x += '1';
            else
                x += '0';
        }
        if(M[x]==0)
            cnt++;
        M[x] = 1;
    }
    cout<<cnt<<endl;
    return 0;
}
```
    - **核心实现思想**：读入函数名转换为小写，与参数类型组成字符串`x`，利用`map`判断`x`是否已存在，统计不同函数数量。
 - **zimingsun23（4星）**
    - **关键亮点**：使用`map<pair<vector<bool>,string>,bool>`判重，代码简洁高效，利用`tolower`转换大小写。
    - **核心代码**：
```cpp
map<pair<vector<bool>,string>,bool> pd;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,ans=0;
    bool pds=0;
    string a,b,c;
    cin>>n;
    for(int i=1;i<=n;++i) {
        cin>>a>>b;
        c="";
        vector<bool> dq;
        for(char &cs:a) cs=tolower(cs);
        if(a=="main") continue;
        while(b[b.length()-1]!=')') {
            cin>>b;
            for(int j=b.length()-1;j>=0;--j) {
                if(b[j]=='=') break;
                else if(b[j]=='\'') {
                    pds=1;
                    dq.push_back(0);
                    break;
                }   
            }
            if(!pds) dq.push_back(1);
            pds=0;
        }
        if(pd[make_pair(dq,a)]==0) {
            pd[make_pair(dq,a)]=1;
            ++ans;
        }
    }
    cout<<ans;
    exit(0);
}
```
    - **核心实现思想**：读入函数名转换为小写，跳过`main`函数，通过判断单引号确定参数类型存入`vector<bool>`，与函数名组成`pair`，利用`map`判重统计不同函数数量。

### 最优关键思路或技巧
1. **数据结构选择**：选择合适的数据结构对函数信息进行存储和判重，如`map`、`set`、结构体结合`vector`等，能简化代码逻辑。
2. **输入处理**：利用字符串处理函数和循环，准确提取函数名和参数类型，注意处理空格、逗号和单引号等特殊字符。
3. **模块化设计**：将复杂的输入处理和判断逻辑封装成函数，提高代码可读性和可维护性。

### 可拓展之处
此类题目属于字符串处理和数据结构应用的结合，类似套路可应用于其他需要处理特定格式输入并进行判重、统计的题目。例如，处理日志文件中的特定记录，根据某些特征进行分类统计等。

### 相似知识点洛谷题目
1. **P1055 ISBN号码**：考察字符串处理和校验计算。
2. **P1308 统计单词数**：涉及字符串查找和统计。
3. **P1593 因子和倍数问题**：结合数论知识和简单的输入处理。

### 个人心得摘录与总结
无明显个人心得相关内容。 

---
处理用时：103.55秒