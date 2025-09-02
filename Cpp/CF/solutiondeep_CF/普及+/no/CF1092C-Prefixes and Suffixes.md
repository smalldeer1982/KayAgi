# 题目信息

# Prefixes and Suffixes

## 题目描述

Ivan挑了几个长度为$n$的小写英文字符串。

但是你不知道Ivan挑的是什么字符串。Ivan会给你这些字符串的前缀和后缀，但是你不知道哪个是前缀，哪个是后缀。

你的任务是猜出他给你的$2n-2$个字符串中哪个是前缀，哪个是后缀。猜出他挑的任意一个字符串，并且回答与之一致即可通过。

PS：在Ivan给你的某个字符串中，如果前面有一个与之相同并且你判了它为$P$，那么你只能判它为$S$。

## 样例 #1

### 输入

```
5
ba
a
abab
a
aba
baba
ab
aba
```

### 输出

```
SPPSPSPS
```

## 样例 #2

### 输入

```
3
a
aa
aa
a
```

### 输出

```
PPSS
```

## 样例 #3

### 输入

```
2
a
c
```

### 输出

```
PS
```

# AI分析结果

### 题目内容
# 前缀和后缀

## 题目描述
伊万挑选了几个长度为 $n$ 的小写英文字符串。
但你不知道伊万选的具体是什么字符串。伊万会给你这些字符串的前缀和后缀，但你不清楚哪个是前缀，哪个是后缀。
你的任务是从他给出的 $2n - 2$ 个字符串中分辨出哪些是前缀，哪些是后缀。猜出他挑选的任意一个字符串，并给出与之相符的判断结果即可通过。
注意：在伊万给你的某个字符串中，如果前面有一个与之相同并且你判定它为前缀（$P$），那么你只能判定它为后缀（$S$）。

## 样例 #1
### 输入
```
5
ba
a
abab
a
aba
baba
ab
aba
```
### 输出
```
SPPSPSPS
```

## 样例 #2
### 输入
```
3
a
aa
aa
a
```
### 输出
```
PPSS
```

## 样例 #3
### 输入
```
2
a
c
```
### 输出
```
PS
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心思路主要围绕如何利用给定的 $2n - 2$ 个字符串来还原出原字符串，进而判断每个字符串是前缀还是后缀。不同题解在确定原字符串的方式上有所差异，有的通过最长字符串，有的利用长度为 $n - 1$ 的字符串等。部分题解思路清晰、代码简洁，而有些题解代码复杂且可读性较差。

### 所选的题解
- **作者：zhoukaixiang（4星）**
  - **关键亮点**：思路清晰，利用长度为 $n - 1$ 的两个字符串必定一个是前缀一个是后缀这一特性，通过比较子串确定最长前缀子串，进而判断其他字符串。
  - **核心代码实现思想**：先找出两个长度为 $n - 1$ 的字符串，通过比较子串确定最长前缀子串 `p`，遍历所有字符串，判断其是否为 `p` 的子串且未出现过，若是则为前缀输出 `P`，否则为后缀输出 `S`。
```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[500];
int n,num;
string maxstring="",maxstring2="",p,a[500];
int main()
{
    cin>>n;
    memset(vis, false, sizeof(vis));
    for(int i=1;i<=2*n-2;i++){
        cin>>a[i];
        if(a[i].size()==n-1){//保存最长前缀子串或后缀子串 
            if(maxstring=="") maxstring=a[i];
            else maxstring2=a[i];
        }
    }
    for(int i=1;i<=2*n-2;i++)
    {
        if(maxstring.substr(0,a[i].size())==a[i]) 
            num++;//在最长前缀子串的子串个数 
    }
    if(num>=(2*n-2)/2 && maxstring.substr(1,n-2)==maxstring2.substr(0,n-2)) 
        p=maxstring;//p保存的是正确的最长前缀子串 
    else 
        p=maxstring2;//否则mx2才是最长前缀子串 
    for(int i=1;i<=n*2-2;i++)
    {
        if(a[i]==p.substr(0,a[i].size()) && vis[a[i].size()]!=true) 
        {
            vis[a[i].size()]=true,;
            printf("P");//判断是否处于最长前缀子串中，且只能出现一次，即为前缀 
        }
        else 
            printf("S");//否则为后缀 
    }
}
```
- **作者：jr_inf（4星）**
  - **关键亮点**：通过合理推测原串由两个长度为 $n - 1$ 的串组合而成，仅需枚举两种组合方案，思路巧妙且代码简洁。
  - **核心代码实现思想**：对输入字符串按长度从大到小排序，取前两个最长串 `s1` 和 `s2`，枚举 `s1 + s2[n - 2]` 和 `s2 + s1[n - 2]` 两种组合作为原串，检查每个输入串是否符合前缀或后缀条件，符合则输出对应 `P` 或 `S`。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100+10;
int n;
char ans[N*2];
struct node{int id;string s;}a[N*2];
bool cmp(node x,node y)
{
    if(x.s.size()!=y.s.size())return x.s.size()>y.s.size();
    return x.id<y.id;
}
void run(string s)
{
    for(int i=1;i<=n*2-2;i++)
    {
        if(a[i].s==s.substr(0,a[i].s.size()))ans[a[i].id]='P';
        else if(a[i].s==s.substr(n-a[i].s.size(),a[i].s.size()))ans[a[i].id]='S';
        else return;//不合法
        if(i>1&&a[i].s==a[i-1].s)ans[a[i].id]='S';//按题意去重
    }
    for(int i=1;i<=n*2-2;i++)cout<<ans[i];
    exit(0);
}
signed main()
{
    cin>>n;
    for(int i=1;i<=n*2-2;i++)
    {
        a[i].id=i;
        cin>>a[i].s;
    }
    sort(a+1,a+1+n*2-2,cmp);//找最长串
    string s1=a[1].s,s2=a[2].s;
    run(s1+s2[n-2]);
    run(s2+s1[n-2]);
}
```
- **作者：xvl_ （4星）**
  - **关键亮点**：明确指出原字符串由一个长度为 $n - 1$ 的前缀和后缀组成，通过枚举这两个长度为 $n - 1$ 字符串的前后缀组合情况来判断。
  - **核心代码实现思想**：找到两个长度为 $n - 1$ 的字符串 `s1` 和 `s2`，分别假设 `s1` 为前缀和后缀两种情况构造原串 `t`，通过 `check1` 和 `check2` 函数判断每个输入字符串是否为 `t` 的前缀或后缀，根据判断结果记录答案，最后输出合法的答案。
```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n;
bool flag;
string s1, s2, t, ans1, ans2; // t 是还原串
string s[205];
map <string, bool> mp;
bool check1(string str) { // 判断这个字符串是否是还原串的前缀
    for (int i = 0; i < str.size(); i++) {
        if (t[i]!= str[i]) return 0;
    }
    return 1;
}
bool check2(string str) { // 判断这个字符串是否是还原串的后缀
    int cnt = t.size() - 1;
    for (int i = str.size() - 1; i >= 0; i--) {
        if (t[cnt--]!= str[i]) return 0;
    }
    return 1;
}
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= 2 * n - 2; i++) cin >> s[i];
    for (int i = 1; i <= 2 * n - 2; i++) {
        if (s[i].size() == n - 1 and flag) s2 = s[i];
        if (s[i].size() == n - 1 and!flag) {
            s1 = s[i];
            flag = 1;
        }
    } 
    flag = 0;
    t = s1;
    t += s2[s2.size() - 1];
    // 如果 s1 是前缀
    for (int i = 1; i <= 2 * n - 2; i++) {
        if (!check1(s[i]) and!check2(s[i])) flag = 1; // 当 s1 是前缀时不合法
        else {
            if (check1(s[i]) and mp.find(s[i]) == mp.end()) {
                ans1 += 'P';
                mp[s[i]] = 1;
            }
            else ans1 += 'S';
        }
    }
    t = s2;
    t += s1[s1.size() - 1];
    // 如果 s1 是后缀
    mp.clear();
    for (int i = 1; i <= 2 * n - 2; i++) {
        if (check1(s[i]) and mp.find(s[i]) == mp.end()) {
            ans2 += 'P';
            mp[s[i]] = 1;
        }
        else ans2 += 'S';
    }
    if (!flag) cout << ans1; 
    else cout << ans2;
    return 0;
}
```

### 最优关键思路或技巧
利用长度为 $n - 1$ 的字符串的特性来确定原字符串的可能形式。如 `zhoukaixiang` 通过比较长度为 $n - 1$ 的两个字符串的子串确定最长前缀子串；`jr_inf` 和 `xvl_` 则通过枚举两个长度为 $n - 1$ 的字符串的组合方式来构造可能的原字符串，从而简化判断过程。

### 拓展
此类题目属于字符串匹配和判断类型，类似套路是先找出关键特征字符串（如本题长度为 $n - 1$ 的字符串），通过它们之间的关系推测原字符串，进而解决问题。同类型题目通常围绕字符串的前缀、后缀、子串匹配等展开。

### 洛谷相似题目
- [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [P2580 于是他错误的点名开始了](https://www.luogu.com.cn/problem/P2580)

### 个人心得摘录与总结
 - **作者：灵光一闪**：调了连续将近10个小时，强调题目虽思路有方向，但实现细节较多，容易出错，需耐心调试。 

---
处理用时：71.36秒