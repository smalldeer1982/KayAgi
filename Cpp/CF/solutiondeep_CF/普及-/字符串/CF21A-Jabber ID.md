# 题目信息

# Jabber ID

## 题目描述

一个地址由 `<username>@<hostname>[/resource]` 组成，其中 `[/resource]` 可以被省略。

- `<username>` 字段允许大写、小写字母，数字、下划线，其长度应在 $1$ 到 $16$ 之间。
- `<hostname>` 字段允许用 `.` 来分隔。每一段的要求同  `<username>` 字段，分隔出的每一部分长度在 $1$ 到 $16$，`<hostname>` 字段的总长度在 $1$ 到 $32$ 之间。
- `<resource>` 字段要求同 `<username>` 字段。


给出一个地址，询问是否合法。

## 样例 #1

### 输入

```
mike@codeforces.com
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
john.smith@codeforces.ru/contest.icpc/12
```

### 输出

```
NO
```

# AI分析结果

### 题目重写
一个地址由 `<username>@<hostname>[/resource]` 组成，其中 `[/resource]` 可以被省略。

- `<username>` 字段允许大写、小写字母，数字、下划线，其长度应在 $1$ 到 $16$ 之间。
- `<hostname>` 字段允许用 `.` 来分隔。每一段的要求同  `<username>` 字段，分隔出的每一部分长度在 $1$ 到 $16$，`<hostname>` 字段的总长度在 $1$ 到 $32$ 之间。
- `<resource>` 字段要求同 `<username>` 字段。

给出一个地址，询问是否合法。

### 题解分析与结论

#### 题解对比与评分
1. **andyli (4星)**  
   - **关键亮点**：使用正则表达式进行匹配，简洁高效。
   - **代码实现**：通过正则表达式直接匹配地址格式，代码简洁明了。
   - **个人心得**：正则表达式在处理字符串匹配问题时非常高效，适合处理复杂的字符串规则。

2. **SIXIANG32 (4星)**  
   - **关键亮点**：详细分析了题目中的坑点，并逐一处理，代码逻辑清晰。
   - **代码实现**：通过分割字符串并逐一检查每个字段的合法性，确保所有条件都满足。
   - **个人心得**：模拟题需要仔细处理每一个细节，尤其是边界条件和特殊情况。

3. **LYqwq (4星)**  
   - **关键亮点**：通过字符串分割和逐个字段检查，逻辑清晰，代码可读性强。
   - **代码实现**：使用 `substr` 和 `find` 函数分割字符串，并定义函数检查每个字段的合法性。
   - **个人心得**：字符串处理时，使用 `substr` 和 `find` 可以简化代码，提高可读性。

#### 最优关键思路与技巧
- **正则表达式**：在处理复杂的字符串匹配问题时，正则表达式是一种非常高效的工具，尤其适合处理格式固定的字符串。
- **字符串分割与检查**：通过分割字符串并逐一检查每个字段的合法性，确保所有条件都满足，适合处理复杂的字符串规则。
- **边界条件处理**：在处理模拟题时，特别需要注意边界条件和特殊情况，确保代码的鲁棒性。

#### 可拓展之处
- **类似题目**：可以拓展到其他需要字符串格式匹配的题目，如邮箱地址验证、URL验证等。
- **正则表达式应用**：正则表达式在处理字符串匹配问题时非常高效，适合处理复杂的字符串规则。

#### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)

#### 个人心得摘录
- **andyli**：正则表达式在处理字符串匹配问题时非常高效，适合处理复杂的字符串规则。
- **SIXIANG32**：模拟题需要仔细处理每一个细节，尤其是边界条件和特殊情况。
- **LYqwq**：字符串处理时，使用 `substr` 和 `find` 可以简化代码，提高可读性。

### 所选高分题解代码

#### andyli (4星)
```python
import re

print(re.match(r'^\w{1,16}@\w{1,16}(\.\w{1,16})*(\/\w{1,16})?$', input()) and 'YES' or 'NO')
```

#### SIXIANG32 (4星)
```cpp
#include<iostream>
#include<string>
using namespace std;
bool checkone(string str) {
    if(str.size()>=17||str.size()==1)return 0;
    for(int p=0;p<str.size();p++)
        if(str[p]!='@')
            if(!((str[p]>='A'&&str[p]<='Z')||(str[p]>='a'&&str[p]<='z')||(str[p]>='0'&str[p]<='9')||(str[p]=='_')))return 0;
    return 1;
}
bool checktwo(string str) {
    int sum=0;
    if(str[0]=='.')return 0;
    if(str.size()==0)return 0;
    if(str.size()>=33|| (str.size()==1&&str[0]=='/'))return 0;
    for(int p=0;p<str.size();p++) {
        if(str[p]=='.'&&str[p+1]=='.') return 0;
        if(str[p]!='.')
            if(!((str[p]>='A'&&str[p]<='Z')||(str[p]>='a'&&str[p]<='z')||(str[p]>='0'&str[p]<='9')||(str[p]=='_')))return 0;
    }
    return 1;
}
bool checkthree(string str) {
    if(str[0]=='/'&&str.size()==1)return 0;
    for(int p=0;p<str.size();p++)
        if(str[p]!='/')
            if(!((str[p]>='A'&&str[p]<='Z')||(str[p]>='a'&&str[p]<='z')||(str[p]>='0'&str[p]<='9')||(str[p]=='_')))return 0;
    return 1;
}
int main() {
    string str;
    getline(cin,str);
    if(str.find('@')==string::npos) {
        cout<<"NO"<<endl;
        return 0;
    }
    string so1=str.substr(0,str.find('@')+1);
    string so2=str.substr(str.find('@')+1,str.find('/')-str.find('@')-1);
    string so3=((str.find('/')!=string::npos)?(str.substr(str.find('/'),str.size()-str.find('/'))):(""));
    if(checkone(so1)&&checktwo(so2)&&checkthree(so3)&&str[str.size()-1]!='.'&&so1.size()+so2.size()+so3.size()==str.size())
        cout<<"YES"<<endl;
    else
        cout<<"NO"<<endl;
}
```

#### LYqwq (4星)
```cpp
#include <iostream>
#define N puts("NO"),exit(0)
using namespace std;
int sz,fd1,fd2;
string s,u,h,r;

void username() {
    int l=u.size();
    if(l==0 || l>=16) N;
    for(int i=0; i<l; i++) {
        if(!(u[i]>='A' && u[i]<='Z' || u[i]>='a' && u[i]<='z' || u[i]>='0' && u[i]<='9' || u[i]=='_')) N;
    }
}

void hostname() {
    int l=h.size();
    if(h[0]=='.' || l==0 || l>=33) N;
    for(int i=0; i<l; i++) {
        if(h[i]=='.' && h[i+1]=='.' || h[i]!='.' && !(h[i]>='A' && h[i]<='Z' || h[i]>='a' && h[i]<='z' || h[i]>='0' && h[i]<='9' || h[i]=='_')) N;
    }
}

void resource() {
    int l=r.size();
    if(!l) return;
    if(r[l-1]=='/') N;
    if(l>=17) N;
    for(int i=0; i<l; i++) {
        if(!(r[i]>='A' && r[i]<='Z' || r[i]>='a' && r[i]<='z' || r[i]>='0' && r[i]<='9' || r[i]=='_')) N;
    }
}

int main() {
    cin >> s;
    sz=s.size(),fd1=s.find('@'),fd2=s.find('/');
    if(fd1==string::npos || s[sz-1]=='.') N;
    u=s.substr(0,fd1);
    h=s.substr(fd1+1,fd2-(fd1+1));
    if(fd2!=string::npos) {
        if(s.substr(fd2,sz-fd2)=="/") N;
        r=s.substr(fd2+1,sz-fd2);
    }
    username(),hostname(),resource();
    puts("YES");
    return 0;
}
```

---
处理用时：59.01秒