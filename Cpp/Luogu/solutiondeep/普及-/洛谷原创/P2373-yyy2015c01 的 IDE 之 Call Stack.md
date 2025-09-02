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
这些题解均围绕判断函数是否相同这一核心任务展开，思路大致为将函数名和参数类型进行存储并判重。算法要点在于准确识别参数类型、处理函数名大小写以及合理选择数据结构存储函数信息。解决难点主要集中在参数类型的判断、main函数的排除以及高效的去重操作。

从质量上看，各题解在思路清晰度、代码可读性和优化程度上有所差异。多数题解能清晰阐述思路，但部分代码在可读性和优化方面有提升空间。

### 所选的题解
#### 作者：Alex_Wei (5星)
- **关键亮点**：思路清晰，通过定义结构体存储函数名和参数类型，使用vector动态存储参数类型，代码结构合理，可读性高。单独编写函数处理参数，提高程序模块化程度。
- **重点代码核心思想**：定义`fact`结构体存储函数名和参数类型向量。`strcmp`函数用于判断字符串是否相同。`getpara`函数获取参数类型向量。主函数中读入函数调用信息，处理函数名大小写，判断是否为`main`函数，然后与已有答案去重并存储。
```cpp
struct fact{
    string na;
    vector <int> para;
};
int strcmp(string a,string b) 
{
    if(a.size()!=b.size())return 0;
    for(int x=0;x<a.size();x++)if(a[x]!=b[x])return 0;
    return 1;
}
vector <int> getpara()
{
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
int main()
{
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
#### 作者：OoXiao_QioO (4星)
- **关键亮点**：思路巧妙，将函数名和参数类型简化为一个字符串，利用`map`进行去重，代码简洁明了。对题目要求的把握准确，注释详细。
- **重点代码核心思想**：定义`map<string, int> M`作为桶存储简化后的字符串。读入函数信息，将函数名转小写，根据参数中是否有单引号判断参数类型，拼接成简化字符串`x`，利用`map`判重并统计不同函数个数。
```cpp
map<string,int> M;
string x;
char s[100001],s1[100001];
int main()
{
    int n,i,l,cnt=0,f;
    cin>>n;
    while(n--)
    {
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
        for(i=0;i<l;i++)
        {
            f = 1;
            if(s1[i]=='=')
            {
                while(s1[i]!=','&&i<l)
                {
                    i++;
                    if(s1[i]=='\'')
                    {
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
#### 作者：UnyieldingTrilobite (4星)
- **关键亮点**：使用`set<pair<string, vector<bool> > >`存储函数信息，利用`set`自动去重特性，代码简洁高效。通过重载`<`运算符实现自定义比较，便于`set`去重。
- **重点代码核心思想**：重载`vector<bool>`的`<`运算符用于`set`比较。主函数中读入函数信息，将函数名转小写，特判`main`函数，通过`readnxt`函数读取参数类型向量，插入`set`中，最后输出`set`的大小。
```cpp
bool operator < (const vector<bool>&a,const vector<bool>&b){
    if(a.size()!=b.size())return a.size()<b.size();
    for(register int i=0;i<a.size();++i){
        if(a[i]^b[i])return b[i];
    }
    return 0;
}
set<pair<string,vector<bool> > >st;
string input;
int n;
vector<bool>p;
bool readnxt();
int main(){
    cin>>n;
    while(n--){
        cin>>input;
        for(int i=0;i<input.size();++i)if(isupper(input[i]))input[i]=input[i]-'A'+'a';
        if(input=="main"){
            getline(cin,input);
            continue;
        }
        for(p.clear();readnxt(););
        st.insert(make_pair(input,p));
    }
    cout<<st.size()<<endl;
    return 0;
}
bool readnxt(){
    bool f=0,tag=0;
    char c=getchar();
    while(c!=','&&c!=')'){
        if(c!='(')tag=1;
        if(c==39)f=1;
        c=getchar();
    }
    if(tag)p.push_back(f);
    return c!=')';
}
```

### 最优关键思路或技巧
1. **数据结构选择**：使用`map`或`set`等关联容器进行去重操作，利用其自动去重特性简化代码逻辑。如`map`可通过键值对存储简化后的函数字符串来判重，`set`可存储函数名和参数类型的组合实现去重。
2. **参数类型判断**：通过判断参数中是否存在单引号来确定参数是`char`类型还是`int`类型，简洁高效。
3. **函数名处理**：将函数名统一转换为大写或小写，便于后续比较，减少判断复杂度。

### 可拓展之处
同类型题通常围绕字符串处理、数据结构应用和模拟实际场景展开。类似算法套路包括对输入信息进行合理抽象和编码，选择合适的数据结构存储和处理数据，以及针对特定规则进行模拟操作。例如，处理函数重载判断、文件路径解析等问题，都可采用类似的字符串处理和数据结构判重思路。

### 推荐题目
1. **P1055 ISBN号码**：涉及字符串处理和校验规则模拟，与本题处理字符串信息并依据规则判断的思路相似。
2. **P1255 数楼梯**：通过模拟不同的楼梯走法，锻炼对实际场景的抽象和代码实现能力，与本题模拟函数调用场景类似。
3. **P1909 买铅笔**：需要根据不同的购买方案进行模拟和比较，与本题判断不同函数的思路有相通之处，都涉及对多种情况的处理和判断。

### 个人心得摘录
暂无明显的个人心得（调试/顿悟）表述。 

---
处理用时：38.41秒