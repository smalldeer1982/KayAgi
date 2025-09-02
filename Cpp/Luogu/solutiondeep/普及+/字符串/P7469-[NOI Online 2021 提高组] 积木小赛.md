# 题目信息

# [NOI Online 2021 提高组] 积木小赛

## 题目描述

Alice 和 Bob 最近热衷于玩一个游戏——积木小赛。

Alice 和 Bob 初始时各有 $n$ 块积木从左至右排成一排，每块积木都被标上了一个英文小写字母。

Alice 可以从自己的积木中丢掉任意多块（也可以不丢）；Bob 可以从自己的积木中丢掉最左边的一段连续的积木和最右边的一段连续的积木（也可以有一边不丢或者两边都不丢）。两人都不能丢掉自己所有的积木。然后 Alice 和 Bob 会分别将自己剩下的积木按原来的顺序重新排成一排。

Alice 和 Bob 都忙着去玩游戏了，于是想请你帮他们算一下，有多少种不同的情况下他们最后剩下的两排积木是相同的。

两排积木相同，当且仅当这两排积木块数相同且每一个位置上的字母都对应相同。

两种情况不同，当且仅当 Alice（或者 Bob）剩下的积木在两种情况中不同。

## 说明/提示

对于所有测试点：$1\le n \le 3000$，$s$ 与 $t$ 中只包含英文小写字母。

测试点 $1$ 满足：$n\le3000$，$s$ 与 $t$ 中只包含同一种字母。

测试点 $2,3,4$ 满足：$n\le100$。

测试点 $5,6,7$ 满足：$n\le500$。

测试点 $8,9,10$ 满足：$n\le3000$。

感谢 [w33z8kqrqk8zzzx33](https://www.luogu.com.cn/user/220037) 提供测试数据。

## 样例 #1

### 输入

```
5
bcabc
bbcca```

### 输出

```
9```

## 样例 #2

### 输入

```
20
egebejbhcfabgegjgiig
edfbhhighajibcgfecef```

### 输出

```
34```

# AI分析结果

• 综合分析与结论：
    - 思路方面，所有题解都围绕找出字符串t的子串且该子串是字符串s的子序列，并统计本质不同的子串数量。主流思路是枚举t的子串，再判断其是否为s的子序列，最后去重。
    - 算法要点上，常利用子序列自动机、后缀自动机（SAM）、哈希、Trie树等数据结构和算法。如通过建立子序列自动机快速判断子序列，用SAM处理子串去重，哈希和Trie树用于判重等。
    - 解决难点在于高效的子序列判断和去重。子序列判断通过预处理相关数组（如记录字符下一个位置的数组）实现；去重方法多样，哈希有直接哈希、双哈希，还有用桶排思想优化哈希，Trie树则通过特定存储方式避免空间爆炸。

    - 综合质量来看，syksykCCC、一叶知秋。、Karry5307的题解相对较好。

  - syksykCCC题解（5星）：
    - 关键亮点：思路简洁清晰，利用哈希和贪心思想。枚举t的子串，用指针贪心扫描s判断子序列，将子串哈希值存入数组，最后排序去重。代码简洁高效。
    - 重点代码核心思想：外层循环枚举t子串左端点i，内层循环枚举右端点j，每次移动j时，用指针p从前往后扫描s找匹配字符，若找到则更新子串哈希值并存入数组t，最后对t数组排序去重输出。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3005, BASE = 51971;
const long long M = 2005091020050911;
int n;
char a[N], b[N];
long long t[N * N];
int main()
{
    scanf("%d %s %s", &n, a + 1, b + 1);
    for(int i = 1; i <= n; i++)
    {
        long long v = 0; int p = 1;
        for(int j = i; j <= n; j++)
        {
            while(p <= n && a[p]!= b[j]) p++;
            if(p > n) break;
            p++;
            v = (1LL * v * BASE + b[j] - 'a' + 1) % M;
            t[++t[0]] = v;
        }
    }
    sort(t + 1, t + t[0] + 1);
    printf("%d\n", unique(t + 1, t + t[0] + 1) - t - 1);
    return 0;
}
```
  - 一叶知秋。题解（4星）：
    - 关键亮点：提出用暴力转移计算LCP数组来判重的独特思路，算法主要流程清晰，通过枚举t的子串并利用指针扫描s判断子序列。
    - 重点代码核心思想：倒序枚举t子串左端点i，每次先找出以i + 1开头后缀与其他后缀的最大LCP，然后从i + Max开始枚举右端点j，用指针k扫描s判断子序列，同时更新LCP数组。
```cpp
#include<cstdio>
#include<cctype>

#define maxn 3333

template<class T>

inline T read(){
    T r=0,f=0;
    char c;
    while(!isdigit(c=getchar()))f|=(c=='-');
    while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
    return f?-r:r;
}

template<class T>

inline T max(T a,T b){
    return a>b?a:b;
}

int n,ans,len[maxn][maxn];

char s[maxn],t[maxn];

int main(){
    freopen("block.in","r",stdin);
    freopen("block.out","w",stdout);
    n=read<int>();
    scanf("%s\n%s",s+1,t+1);
    for(int i=n;i>=1;i--){
        int Max=0;
        for(int j=i+1;j<=n;j++)
            Max=max(Max,len[j][i]);
        int k=1;
        for(int j=i;j<i+Max;j++){
            while(k<=n&&(s[k]^t[j]))k++;
            if(k>n)break;
            k++;
        }
        for(int j=i+Max;j<=n;j++){//枚举右端点
            while(k<=n&&(s[k]^t[j]))k++;//指针直接扫
            if(k>n)break;
            k++;
            ans++;
        }
        for(int j=1;j<=n;j++)//转移
            if(t[i]==t[j])len[i][j]=len[i+1][j+1]+1;
    }
    printf("%d\n",ans);
    return 0;
}
```
  - Karry5307题解（4星）：
    - 关键亮点：使用子序列自动机和哈希表，先对s建立子序列自动机快速判断子序列，再枚举t子串并用哈希表判重，考虑到数据规模对哈希模数选择和哈希表实现进行优化。
    - 重点代码核心思想：先预处理出子序列自动机nxt数组，然后枚举t子串左端点i，右端点j从i到n，通过子序列自动机判断子串是否为s的子序列，同时计算子串哈希值并用手写哈希表判重。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=9e6+51;
const li MOD1=8530716171517,MOD2=8530716771587;
struct HashTable{
    const ll MOD=8530771;
    ll tot;
    ll last[MAXN],prev[MAXN/2];
    li hsh1[MAXN/2],hsh2[MAXN/2];
    inline void insert(li hv1,li hv2);
    inline ll query(li hv1,li hv2);
};
HashTable hsh;
ll n,res,cur;
li hsh1,hsh2;
ll nxt[3051][27];
char s[3051],t[3051];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline void HashTable::insert(li hv1,li hv2)
{
    ll x=hv1%MOD;
    prev[++tot]=last[x],hsh1[tot]=hv1,hsh2[tot]=hv2,last[x]=tot;
}
inline ll HashTable::query(li hv1,li hv2)
{
    ll x=hv1%MOD;
    for(register int i=last[x];i;i=prev[i])
    {
        if(hsh1[i]==hv1&&hsh2[i]==hv2)
        {
            return 1;
        }
    }
    return 0;
}
int main()
{
    n=read(),scanf("%s%s",s+1,t+1);
    for(register int i=n;i;i--)
    {
        memcpy(nxt[i-1],nxt[i],sizeof(nxt[i])),nxt[i-1][s[i]-'a']=i;
    }
    for(register int i=1;i<=n;i++)
    {
        cur=hsh1=hsh2=0;
        for(register int j=i;j<=n;j++)
        {
            if(!(cur=nxt[cur][t[j]-'a']))
            {
                break;
            }
            hsh1=(hsh1*131+t[j]-'a'+1)%MOD1,hsh2=(hsh2*131+t[j]-'a'+1)%MOD2;
           !hsh.query(hsh1,hsh2)?hsh.insert(hsh1,hsh2),res++:1;
        }
    }
    printf("%d\n",res);
}
```
• 最优关键思路或技巧：
    - 数据结构方面，子序列自动机可高效判断子序列，通过预处理记录每个字符下一个位置，在判断子序列时能快速移动指针。
    - 去重技巧上，哈希方法结合合适的模数选择以及优化的哈希表实现（如手写哈希表），能有效且高效地判断本质不同的子串。

• 可拓展之处：
同类型题常考察字符串子序列、子串相关问题，类似算法套路有利用自动机（子序列自动机、后缀自动机等）处理字符串匹配和去重，以及使用哈希进行快速判重。

• 相似知识点洛谷题目：
    - P4112 [HEOI2015]最短不公共子串，涉及子序列自动机和后缀自动机的应用。
    - P3804 【模板】后缀自动机，专注后缀自动机的基本应用。
    - P5410 【模板】子序列自动机，着重子序列自动机的实现与运用。

• 个人心得摘录与总结：
    - wsyhb提到要认真分析时间复杂度，比赛时有条件要生成大数据测试，否则可能因复杂度分析不清导致TLE，且未意识到桶排中字符集大小带来的复杂度问题，从100分降到70分。总结为算法竞赛中时间复杂度分析和大数据测试的重要性。
    - KAMIYA_KINA考场上想出Trie树做法，但因数组大小设置问题，在luogu上从50分提升到80分后因内存爆掉未得满分，强调代码实现中数组大小等细节的重要性。 

---
处理用时：71.58秒