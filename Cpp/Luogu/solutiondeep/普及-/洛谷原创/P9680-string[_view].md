# 题目信息

# string[_view]

## 题目背景

C++ 的 string 类是一个功能强大的字符串类，然而由于其字符串算法和内存管理绑定的机制，所以在处理 C 风格字符串时效率低下。

为了解决这个问题，C++17 标准引入了 string\_view 类型，将内存管理和字符串算法分离，从而更好地适配了 C 风格字符串的处理。

## 题目描述

你需要模拟一个简单的 C++ 程序，该程序的每一行必然为如下两种形式之一：

- `string <variable-name>(<initializer>);`
- `string_view <variable-name>(<initializer>);`

其中 `variable-name` 为声明的变量名（保证之前未出现过，且长度不超过 $10$），`initializer` 为初始化该变量的内容，可以是：

- 字符串字面量，即用双引号引起的字符串（形如 `"abc"`）；
- 之前出现过的变量名 `source`，此时应将 `source` 对应的字符串赋给 `variable-name`。

具体而言，将任意一个字符串 $s$ 赋给 string 类型会进行 $|s|$ 次字符拷贝，而赋给 string\_view 类型不会拷贝字符。其中 $|s|$ 为字符串 $s$ 的长度。

你需要计算出该程序中字符拷贝的总次数。

## 说明/提示

  对于每组数据，保证代码长度均不超过 $10^4$（不包括换行符）。

保证字符串字面量（除去两侧引号）和变量名中只有拉丁字母，且给定的代码严格满足题目要求。

### 子任务

|  #   |            特殊性质            | 分值 |
| :--: | :----------------------------: | :--: |
|  0   |              样例              | 0  |
|  1   | 所有变量均为 string\_view 类型 | 10 |
|  2   |    只使用字符串字面量初始化    | 20 |
|  3   |               -                | 70 |

---

好消息：GCC 9.3.0 支持 string_view。

坏消息：NOI 不开 C++17。

## 样例 #1

### 输入

```
6
string a("cxyakioi");
string_view b("cxyakapio");
string c(b);
string_view d(a);
string_view cxyakioi(c);
string cxyakapio(d);```

### 输出

```
25```

# AI分析结果

### 综合分析与结论
这些题解的核心思路均为模拟程序中字符串的赋值操作，统计 `string` 类型变量赋值时的字符拷贝次数。主要差异在于输入字符串的解析方式及数据存储结构的选择。各题解均能正确解决问题，但在思路清晰度、代码可读性及优化程度上有所不同。

### 所选的题解
1. **作者：zhang_Jimmy（4星）**
    - **关键亮点**：思路清晰，先明确用 `map` 存储 `string` 变量对应的字符串长度，再详细说明对输入字符串的拆解及不同情况的处理方式，逻辑连贯，代码简洁明了。
    - **重点代码及核心思想**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, ans;
string s, s2;
map<string, int> mp; 

int main(){
    cin >> t;
    while(t --){
        cin >> s >> s2; 
        string st;
        while(s2[0]!= '('){//提取变量名 
            st += s2[0];
            s2.erase(0, 1);
        }
        s2.erase(0, 1);//删除( 
        s2.pop_back();//删除; 
        s2.pop_back();//删除) 
        int len;
        if(s2[0] == '\"')
            len = s2.size() - 2; 
        else
            len = mp[s2]; 
        mp[st] = len; 
        if(s == "string")
            ans += len;
    } 
    cout << ans;
    return 0;
}
```
核心思想是先从输入字符串中提取变量名和初始化内容，判断初始化内容是字符串常量还是变量，更新 `map` 中变量名对应的长度，并在变量类型为 `string` 时累加长度到答案。
2. **作者：HFanGDoDM（4星）**
    - **关键亮点**：对每个子任务进行详细分析，解法循序渐进，从简单子任务逐步过渡到完整解法，有助于理解问题本质。时间复杂度分析详细，能让读者清楚了解算法效率。
    - **重点代码及核心思想**：
```cpp
map<string,int>len;
...
    string type;
    cin>>type>>str[i];
    string name=str[i].substr(0,str[i].find("("));//提取变量名
    int lef=str[i].find("(")+1,rig=str[i].find(")")-1;
    if(str[i][lef]<'A'||str[i][lef]>'z'){//字符串字面量
        len[name]=rig-lef-1;//记录新变量名与字符串长度的对应关系
        if(type=="string")
            ans+=len[name];
    }
    else{//使用变量名赋值
        string name1=str[i].substr(lef,rig-lef+1);//提取用于赋值的变量名
        if(type=="string")
            ans+=len[name1];
        len[name]=len[name1];//两个变量字符串长度相等
    }
...
printf("%d",ans);
```
核心思想是通过 `find` 函数定位关键字符，用 `substr` 函数提取变量名和初始化内容，判断初始化方式并记录变量名与长度的对应关系，在变量为 `string` 类型时累加长度到答案。
3. **作者：流光萤影（4星）**
    - **关键亮点**：代码简洁高效，利用 `string` 的 `substr` 和 `find` 函数快速解析输入字符串，逻辑清晰，对关键代码有详细注释说明，便于理解。
    - **重点代码及核心思想**：
```cpp
#include<bits/stdc++.h>
using namespace std;int n,ans;string s,name,val;
map<string,string> mp;
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin >> n;
    for(;n;--n)
    {
        cin >> s;
        if(s == "string")
        {
            cin >> s;
            name = s.substr(0,s.find('('));
            if(s[s.find('(')+1] == '"') val = s.substr(s.find('(')+2,s.find(')')-1-name.size()-2);
            else val = mp[s.substr(s.find('(')+1,s.find(')')-name.size()-1)];
            mp[name] = val,ans += val.size();
        }
        else
        {
            cin >> s;
            name = s.substr(0,s.find('('));
            if(s[s.find('(')+1] == '"') val = s.substr(s.find('(')+2,s.find(')')-1-name.size()-2);
            else val = mp[s.substr(s.find('(')+1,s.find(')')-name.size()-1)];
            mp[name] = val;
        }
    }
    cout << ans;
}
```
核心思想是通过 `substr` 和 `find` 函数解析输入字符串，获取变量名和初始化值，在变量为 `string` 类型时累加值的长度到答案，并使用 `map` 存储变量名与值的对应关系。

### 最优关键思路或技巧
- **数据结构选择**：使用 `map` 存储变量名与对应字符串长度或内容的关系，方便根据变量名快速获取所需信息。
- **字符串解析**：利用 `string` 类的 `find`、`substr` 等函数，结合循环遍历，准确提取变量名、初始化内容等关键信息。

### 可拓展之处
此类题目属于模拟与字符串处理结合的题型，类似套路为根据给定规则模拟程序行为，同时处理好输入字符串的解析。拓展方向可包括增加变量类型、改变赋值规则、处理更复杂的输入格式等。

### 相似知识点洛谷题目
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)：涉及字符串处理与校验规则模拟。
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：考察字符串查找与统计。
- [P1593 因子和阶乘](https://www.luogu.com.cn/problem/P1593)：结合数论知识，通过模拟计算阶乘中各因子的个数，包含字符串处理。

### 个人心得摘录与总结
暂未发现题解中有个人心得相关内容。 

---
处理用时：33.71秒