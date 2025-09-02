# 题目信息

# Running Track

## 题目描述

A boy named Ayrat lives on planet AMI-1511. Each inhabitant of this planet has a talent. Specifically, Ayrat loves running, moreover, just running is not enough for him. He is dreaming of making running a real art.

First, he wants to construct the running track with coating $ t $ . On planet AMI-1511 the coating of the track is the sequence of colored blocks, where each block is denoted as the small English letter. Therefore, every coating can be treated as a string.

Unfortunately, blocks aren't freely sold to non-business customers, but Ayrat found an infinite number of coatings $ s $ . Also, he has scissors and glue. Ayrat is going to buy some coatings $ s $ , then cut out from each of them exactly one continuous piece (substring) and glue it to the end of his track coating. Moreover, he may choose to flip this block before glueing it. Ayrat want's to know the minimum number of coating $ s $ he needs to buy in order to get the coating $ t $ for his running track. Of course, he also want's to know some way to achieve the answer.

## 说明/提示

In the first sample string "cbaabc" = "cba" + "abc".

In the second sample: "ayrat" = "a" + "yr" + "at".

## 样例 #1

### 输入

```
abc
cbaabc
```

### 输出

```
2
3 1
1 3
```

## 样例 #2

### 输入

```
aaabrytaaa
ayrat
```

### 输出

```
3
1 1
6 5
8 7
```

## 样例 #3

### 输入

```
ami
no
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# 跑道

## 题目描述
一个名叫艾拉特（Ayrat）的男孩生活在AMI - 1511星球上。这个星球上的每个居民都有一种天赋。具体来说，艾拉特热爱跑步，而且，仅仅跑步对他来说还不够。他梦想着将跑步变成一门真正的艺术。

首先，他想建造一条带有涂层$t$的跑道。在AMI - 1511星球上，跑道的涂层是由彩色方块组成的序列，每个方块用一个小写英文字母表示。因此，每一种涂层都可以看作是一个字符串。

不幸的是，方块不向非商业客户自由出售，但艾拉特找到了无限数量的涂层$s$。此外，他还有剪刀和胶水。艾拉特打算购买一些涂层$s$，然后从每一个涂层中准确地剪下一段连续的部分（子串），并将其粘贴到他的跑道涂层的末尾。而且，在粘贴之前，他可以选择将这个方块翻转。艾拉特想知道，为了得到他的跑道涂层$t$，他最少需要购买多少个涂层$s$。当然，他也想知道实现这个答案的一些方法。

## 说明/提示
在第一个样例中，字符串“cbaabc” = “cba” + “abc”。

在第二个样例中：“ayrat” = “a” + “yr” + “at”。

## 样例 #1
### 输入
```
abc
cbaabc
```
### 输出
```
2
3 1
1 3
```
## 样例 #2
### 输入
```
aaabrytaaa
ayrat
```
### 输出
```
3
1 1
6 5
8 7
```
## 样例 #3
### 输入
```
ami
no
```
### 输出
```
-1
```

### 算法分类
字符串

### 综合分析与结论
三道题解均围绕如何用字符串$s$的子串（可翻转）拼接出字符串$t$展开。Tx_Lcy采用纯暴力匹配，虽未用KMP优化但时间复杂度理论正确且实际常数小；_edge_提出两种思路，$O(nm \log nm)$的哈希+DP因常数大未通过，$O(nm)$的贪心思路通过维护最长相同子串实现；RedLycoris通过贪心+二分优化暴力枚举，将复杂度优化到$O(n^2log_2n)$。

### 所选的题解
- **Tx_Lcy**（5星）
  - **关键亮点**：纯暴力匹配思路简单直接，时间复杂度理论正确且实际运行常数小，速度快。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e3+10;
vector< pair<int,int> >ans;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    string s1,s2;cin>>s1>>s2;
    int l1=s1.length(),l2=s2.length(),l=1;
    s1=" "+s1,s2=" "+s2;
    string s11=s1.substr(1,l1);
    reverse(s11.begin(),s11.end()),s11=" "+s11;
    while (l<=l2){
        int maxn=0,maxni;
        for (int i=1;i<=l1;++i){
            int j=i,j1=l;
            while (s1[j]==s2[j1] && j<=l1 && j1<=l2) ++j,++j1;
            if (j-i>maxn) maxn=j-i,maxni=i;
        }
        int maxn1=0,maxni1;
        for (int i=1;i<=l1;++i){
            int j=i,j1=l;
            while (s11[j]==s2[j1] && j<=l1 && j1<=l2) ++j,++j1;
            if (j-i>maxn1) maxn1=j-i,maxni1=i;
        }
        if (!maxn &&!maxn1) return cout<<"-1\n",0;
        if (maxn1>maxn) l+=maxn1,ans.push_back({l1-maxni1+1,l1-maxni1-maxn1+2});
        else l+=maxn,ans.push_back({maxni,maxni+maxn-1});
    }
    cout<<ans.size()<<'\n';
    for (auto i:ans) cout<<i.first<<' '<<i.second<<'\n';
    return 0;
}
```
  - **核心实现思想**：记录初始串$s1$、目标串$s2$及$s1$翻转后的串$s11$。通过双重循环在$s1$和$s11$中暴力匹配$s2$，每次找出能匹配的最长子串，记录位置并更新匹配位置，直到匹配完$s2$或无法匹配。
- **_edge_**（4星）
  - **关键亮点**：提出两种思路，其中$O(nm)$的贪心思路有效解决问题，通过维护最长相同子串的转移方程实现。
  - **重点代码**：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=2105;
string s1,s2;
int n,m,f[INF][INF],lcp[INF][INF],ans[INF*INF][5],tot;
int lcpe[INF][INF],f1[INF][INF];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>s1>>s2; n=s1.size(); m=s2.size();
    s1=" "+s1; s2=" "+s2;
    for (int i=n; i>=1; i--)
        for (int j=m; j>=1; j--)
            if (s1[i]==s2[j]) {
                lcp[i][j]=lcp[i+1][j+1]+1;
                if (lcp[i][j]>1) f[i][j]=f[i+1][j+1];
                else f[i][j]=i;
            }
    for (int i=1; i<=n; i++)
        for (int j=m; j>=1; j--)
            if (s1[i]==s2[j]) {
                lcpe[i][j]=lcpe[i-1][j+1]+1;
                if (lcpe[i][j]>1) f1[i][j]=f1[i-1][j+1];
                else f1[i][j]=i;
            }
    for (int i=1; i<=m; ) {
        int j=0,j1=0; int fl=i;
        for (int k=1; k<=n; k++)
            if (lcp[k][i]>lcp[j][i]) j=k;
        for (int k=1; k<=n; k++)
            if (lcpe[k][i]>lcpe[j1][i]) j1=k;
        if (lcp[j][i]>lcpe[j1][i]) {
            ans[++tot][0]=j;
            ans[tot][1]=f[j][i];
            i+=lcp[j][i];
        }
        else {
            ans[++tot][0]=j1;
            ans[tot][1]=f1[j1][i];
            i+=lcpe[j1][i];
        }
        if (fl==i) {cout<<"-1\n"; return 0;}
    }
    cout<<tot<<"\n";
    for (int i=1; i<=tot; i++)
        cout<<ans[i][0]<<" "<<ans[i][1]<<"\n";
    return 0;
}
```
  - **核心实现思想**：先正向和反向预处理出以$s1$和$s2$中各位置为起点的最长相同子串长度及起始位置。然后遍历$s2$，每次找出从当前位置开始在$s1$（正反）中能匹配的最长子串，记录位置并更新匹配位置，若无法更新则输出 -1。
- **RedLycoris**（4星）
  - **关键亮点**：利用贪心思想，通过二分优化暴力枚举，降低时间复杂度。
  - **重点代码**：
```cpp
using namespace std;
const int mxn=2e5+5;
string a,b,ta;
int n,m;
vector<pair<int,int> >ans;
inline bool check(int bg,int ed){
    if(ed-bg+1>a.size())return 0;
    string t=b.substr(bg,ed-bg+1);
    for(int i=0;i<a.size()-t.size()+1;++i){
        bool ok=1;
        for(int j=0;j<t.size();++j){
            if(a[i+j]!=t[j]){
                ok=0;
                break;
            }
        }
        if(ok)return 1;
    }
    for(int i=0;i<ta.size()-t.size()+1;++i){
        bool ok=1;
        for(int j=0;j<t.size();++j){
            if(ta[i+j]!=t[j]){
                ok=0;
                break;
            }
        }
        if(ok)return 2;
    }
    return 0;
}
inline pair<int,int> getp(int bg,int ed){
    string t=b.substr(bg,ed-bg+1);
    for(int i=0;i<a.size()-t.size()+1;++i){
        bool ok=1;
        for(int j=0;j<t.size();++j){
            if(a[i+j]!=t[j]){
                ok=0;
                break;
            }
        }
        if(ok)return mp(i,i+t.size()-1);
    }
    for(int i=0;i<ta.size()-t.size()+1;++i){
        bool ok=1;
        for(int j=0;j<t.size();++j){
            if(ta[i+j]!=t[j]){
                ok=0;
                break;
            }
        }
        if(ok)return mp(a.size()-i-1,a.size()-i-t.size());
    }
}
inline string E(int bg,int ed){
    return b.substr(bg,ed-bg+1);
}
inline void solve(){
    cin>>a>>b;ta=a;reverse(ta.begin(),ta.end());
    n=a.size(),m=b.size();
    int b=0;
    for(;b<m;++b){
        int l=b,r=m,md;
        for(;l<r-1;){
            md=l+r>>1;
            if(check(b,md))l=md;
            else r=md;
        }
        if(l==b and!check(b,l)){
            cout<<"-1\n";
            return;
        }
        if(check(b,l)==1)ans.push_back(getp(b,l));
        b=l;
    }
    cout<<ans.size()<<'\n';
    for(int i=0;i<ans.size();++i)cout<<ans[i].first+1<<' '<<ans[i].second+1<<'\n';
    return;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;//cin>>T;
    for(;T--;)solve();
}
```
  - **核心实现思想**：先反转字符串$a$得到$ta$。遍历字符串$b$，对每个位置二分最远能匹配的位置，通过`check`函数判断子串是否在$a$或$ta$中，若能匹配则记录位置，若无法匹配则输出 -1。

### 最优关键思路或技巧
贪心思想在解决此类字符串拼接问题上较为有效，每次选择能匹配的最长子串进行拼接。同时，暴力匹配虽简单但在某些情况下时间复杂度可接受且常数小，如Tx_Lcy的题解。

### 拓展
同类型题常围绕字符串的匹配、拼接、构造等展开，类似算法套路包括利用字符串的前缀、后缀信息，KMP等字符串匹配算法，以及贪心、动态规划等优化策略。

### 洛谷题目推荐
- P3375 【模板】KMP字符串匹配
- P1308 统计单词数
- P2580 [ZJOI2006] 书架

---
处理用时：101.00秒