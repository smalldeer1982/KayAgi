# 题目信息

# Equidistant String

## 题目描述

Susie 喜欢字符串。她的字符串只包含数字 $0$ 和 $1$。今天，她使用了[汉明距离法](https://baike.baidu.com/item/%E6%B1%89%E6%98%8E%E8%B7%9D%E7%A6%BB/475174?fr=aladdin)计算了它们之间的距离。

汉明距离的定义表示两个相同长度字符串对应位置的不同字符的数量。

有2个长度为 $n$ 的字符串 $s$ 和 $t$ 她还想要一个长度为 $n$ 的字符串 $p$ 使得 $p$ 到 $s$ 的距离等于 $p$ 到 $t$ 的距离

请你帮她找到这样的字符串 $p$。可能有很多种答案，找到一种即可。

## 说明/提示

第一组样例：汉明距离为3

答案也可以为 $1001$

第二组样例：无法找到满足要求的字符串

translated by [Yang080108](https://www.luogu.com.cn/user/422348)

## 样例 #1

### 输入

```
0001
1011
```

### 输出

```
0011
```

## 样例 #2

### 输入

```
000
111
```

### 输出

```
impossible
```

# AI分析结果

### 题目分类
构造

### 综合分析与结论
这些题解的核心思路都是基于汉明距离的定义来构造满足条件的字符串。当两个输入字符串对应位置字符相同时，新字符串该位置字符任意取；当对应位置字符不同时，需要对这些不同位置进行处理。若不同位置的数量为奇数，则无法构造出满足条件的字符串，输出 `impossible`；若为偶数，则可以通过平分这些不同位置来构造出满足条件的字符串。

各题解的区别主要在于处理不同位置的具体方式和代码实现细节，但整体思路是一致的。

### 所选题解
- **Yang818（4星）**
    - **关键亮点**：思路清晰，通过详细的样例分析引出解题思路，代码简洁易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int main(){
    int cnt=0;
    cin>>s>>t;
    for(int i=0;i<s.size();i++){
        if(s[i]==t[i])
            continue;
        cnt++;
        if(cnt%2!=0)
            s[i]=t[i];
    }
    if(cnt%2==0)
        cout<<s;
    else
        cout<<"impossible";
    return 0;
} 
```
    - **核心实现思想**：遍历两个字符串，统计不同位置的数量 `cnt`。当 `cnt` 为奇数时，将当前位置的字符改为另一个字符串对应位置的字符。最后判断 `cnt` 是否为偶数，若是则输出修改后的字符串，否则输出 `impossible`。

- **Laisira（4星）**
    - **关键亮点**：对汉明距离的定义解释清晰，思路简洁明了，代码逻辑清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,ans=0;
    string s[2];
    cin>>s[0]>>s[1];
    n=s[0].size();
    for(int i=0;i<n;i++)
        ans+=(s[0][i]!=s[1][i]);
    if(ans&1)cout<<"impossible";
    else {
        int flag=0;
        for(int i=0;i<n;i++)
            if(s[0][i]==s[1][i])cout<<s[0][i];
            else cout<<s[flag][i],flag^=1;
    }
    return 0;
}
```
    - **核心实现思想**：先统计两个字符串不同位置的数量 `ans`，若 `ans` 为奇数则输出 `impossible`。若为偶数，则遍历字符串，相同位置直接输出，不同位置交替输出两个字符串对应位置的字符。

- **__DayLight__（4星）**
    - **关键亮点**：思路推导详细，对每个步骤的解释清晰，代码逻辑严谨。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,t;
int p;//记录 p 到 s 的汉明距离，用于输出。 
signed main(){
    cin>>s>>t;
    int hm=0,n=s.size();//hm 记录 s 与 t 的汉明距离。 
    s=" "+s,t=" "+t;
    for(int i=1; i<=n; i++)
        if(s[i]!=t[i])hm++;
    if(hm%2)cout<<"impossible";//如果不同的数量是奇数。 
    else
        for(int i=1; i<=n; i++)
            if(s[i]!=t[i])//对应位置的字符不同。 
            {
                if(p<hm/2)cout<<s[i],p++; 
                else cout<<t[i];
            }
            else cout<<s[i];//相同，不用操作，随便输出一个。 
    return 0;
}
```
    - **核心实现思想**：先计算两个字符串的汉明距离 `hm`，若 `hm` 为奇数则输出 `impossible`。若为偶数，则遍历字符串，相同位置直接输出，不同位置在前 `hm/2` 次输出第一个字符串对应位置的字符，之后输出第二个字符串对应位置的字符。

### 最优关键思路或技巧
- 利用汉明距离的定义，分析出相同位置对结果无影响，只需要关注不同位置。
- 通过判断不同位置的数量奇偶性来确定是否有解，若为偶数则可以通过平分不同位置来构造满足条件的字符串。

### 可拓展之处
同类型题目可能会改变字符串的字符集，或者增加更多的约束条件，但核心思路仍然是基于汉明距离的定义进行构造。类似的算法套路可以应用于其他需要构造满足特定条件的字符串或序列的问题。

### 推荐题目
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
2. [P1598 垂直柱状图](https://www.luogu.com.cn/problem/P1598)
3. [P1914 小书童——凯撒密码](https://www.luogu.com.cn/problem/P1914)

### 个人心得
无

---
处理用时：30.47秒