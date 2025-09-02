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
这些题解思路总体一致，都是通过模拟程序执行过程，记录并统计 `string` 类型变量赋值时的字符拷贝次数。
1. **思路**：读取每一行输入，判断是 `string` 还是 `string_view` 类型。对于 `string` 类型，若用字符串字面量初始化，计算字面量长度并累加到总拷贝次数；若用已定义变量初始化，则找到该变量对应长度并累加。`string_view` 类型不做拷贝次数累加。
2. **算法要点**：利用数据结构记录变量及其对应字符串长度，如 `map` 或自定义结构体数组。通过字符串操作函数（如 `find`、`substr` 等）提取变量名和初始化内容。
3. **解决难点**：主要难点在于解析输入字符串，准确提取变量名、判断初始化方式（字面量或变量），并正确处理不同类型的赋值操作。

各题解质量有差异，部分题解代码注释详细、思路清晰，部分题解代码稍显混乱或注释不足。

### 所选的题解
- **作者：zhang_Jimmy（4星）**
    - **关键亮点**：思路清晰，对输入字符串拆解和情况判断明确，代码简洁明了，利用 `map` 存储变量长度，逻辑清晰。
    - **核心代码**：
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
    - **核心实现思想**：先读取输入，通过循环提取变量名，再根据括号内内容判断是字面量还是变量，更新 `map` 并累加拷贝次数。

- **作者：HFanGDoDM（4星）**
    - **关键亮点**：对各子任务分别分析，思路详细，从简单情况逐步过渡到完整解法，对时间复杂度分析清晰。
    - **核心代码（子任务3）**：
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
    - **核心实现思想**：读入变量类型和初始化语句，利用 `find` 和 `substr` 函数提取变量名和初始化内容，根据内容类型更新 `map` 并累加拷贝次数。

- **作者：流光萤影（4星）**
    - **关键亮点**：代码简洁，利用 `string` 的 `substr` 和 `find` 函数高效实现模拟过程，对关键函数使用有示例说明。
    - **核心代码**：
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
    - **核心实现思想**：根据输入判断类型，提取变量名和初始化值，更新 `map` 并在 `string` 类型时累加拷贝次数。

### 最优的关键思路或技巧
1. **数据结构选择**：使用 `map` 存储变量名与对应字符串长度的映射关系，方便快速查找和更新。
2. **字符串处理技巧**：利用 `string` 类的 `find` 和 `substr` 函数，准确提取变量名和初始化内容，简化代码实现。

### 可拓展思路
此类题目属于模拟与字符串处理结合类型。拓展方向包括更复杂的变量定义和操作，如涉及指针、数组等；或增加条件判断、循环结构等控制语句。类似算法套路是通过数据结构记录关键信息，结合字符串处理函数解析输入，模拟程序执行逻辑。

### 相似知识点洛谷题目
1. [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：简单模拟，涉及条件判断和基本数学运算。
2. [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：模拟购物场景，通过比较不同方案得出最优解。
3. [P5717 点和线](https://www.luogu.com.cn/problem/P5717)：判断点与线段位置关系，结合模拟和简单几何知识。

### 个人心得摘录与总结
暂无典型个人心得。部分题解提到代码一次通过，强调了对题意理解和模拟逻辑正确性的重要性。 

---
处理用时：89.50秒