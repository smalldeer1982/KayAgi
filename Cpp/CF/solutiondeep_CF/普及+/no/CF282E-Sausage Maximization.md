# 题目信息

# Sausage Maximization

## 题目描述

The Bitlandians are quite weird people. They have their own problems and their own solutions. They have their own thoughts and their own beliefs, they have their own values and their own merits. They have their own dishes and their own sausages!

In Bitland a sausage is an array of integers! A sausage's deliciousness is equal to the bitwise excluding OR (the $ xor $ operation) of all integers in that sausage.

One day, when Mr. Bitkoch (the local cook) was going to close his BitRestaurant, BitHaval and BitAryo, the most famous citizens of Bitland, entered the restaurant and each ordered a sausage.

But Mr. Bitkoch had only one sausage left. So he decided to cut a prefix (several, may be zero, first array elements) of the sausage and give it to BitHaval and a postfix (several, may be zero, last array elements) of the sausage and give it to BitAryo. Note that one or both pieces of the sausage can be empty. Of course, the cut pieces mustn't intersect (no array element can occur in both pieces).

The pleasure of BitHaval and BitAryo is equal to the bitwise XOR of their sausages' deliciousness. An empty sausage's deliciousness equals zero.

Find a way to cut a piece of sausage for BitHaval and BitAryo that maximizes the pleasure of these worthy citizens.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2
1000 1000
```

### 输出

```
1000
```

# AI分析结果

### 题目内容
# 香肠最大化

## 题目描述
比特兰人是相当奇怪的一群人。他们有自己的问题和解决方案，有自己的思想和信仰，有自己的价值观和优点。他们有自己的菜肴，也有自己的香肠！

在比特兰，香肠是一个整数数组！一根香肠的美味程度等于该数组中所有整数的按位异或（异或操作）。

一天，当比特科赫先生（当地的厨师）准备关闭他的比特餐厅时，比特兰最著名的居民比特哈瓦尔和比特阿约走进了餐厅，每人都点了一根香肠。

但比特科赫先生只剩下一根香肠了。所以他决定切下这根香肠的一个前缀（若干个，也可能是零个，数组的前几个元素）给比特哈瓦尔，再切下一个后缀（若干个，也可能是零个，数组的后几个元素）给比特阿约。注意，这两段香肠可以为空。当然，切下的两段不能相交（数组中的任何元素不能同时出现在两段中）。

比特哈瓦尔和比特阿约的愉悦度等于他们香肠美味程度的按位异或。空香肠的美味程度等于零。

请找到一种给比特哈瓦尔和比特阿约切香肠的方法，使这两位尊贵居民的愉悦度最大化。

## 样例 #1
### 输入
```
2
1 2
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3
1 2 3
```
### 输出
```
3
```

## 样例 #3
### 输入
```
2
1000 1000
```
### 输出
```
1000
```

### 算法分类
贪心

### 题解综合分析与结论
这些题解主要围绕如何优化计算前缀和后缀异或和的组合以获取最大异或值展开。
- **暴力解法**：$O(n^3)$ 暴力枚举前缀与后缀位置，循环求解前缀异或和、后缀异或和并取最大值，时间复杂度高导致 TLE。$O(n^2)$ 解法通过预处理前缀和后缀异或和，减少循环计算，但仍在大数据下 TLE。
- **01Trie 解法**：多个题解采用 01Trie 数据结构优化。先预处理前缀异或和与后缀异或和，将前缀异或和插入 01Trie 树，对后缀异或和在 01Trie 树上贪心查询最大异或值。利用异或在二进制下 “相同得 0，不同得 1” 的性质，在 Trie 树查询时尽可能让高位出现 $0\oplus1$ 或 $1\oplus0$ 的情况，以保证异或和最大。

### 所选的题解
#### 作者：Zvelig1205 (5星)
- **关键亮点**：详细阐述了从暴力到优化的思路过程，对异或运算的原理及 01Trie 树的构建、查询操作解释清晰，并给出了详细代码及注释。
- **个人心得**：无

```cpp
const int inf=1e5+7;
int n,ans,a[inf];
int pre[inf],nex[inf];
struct Trie_01{
    int lc,rc;
}T[inf*100];
int rot1,rot2,cnt;
void insert(int &now,int k,int dep)
{
    if(now==0)now=++cnt;
    if(dep==41)return;
    if(k&1)insert(T[now].rc,k>>1,dep+1);
    else insert(T[now].lc,k>>1,dep+1);
}
void chuli(int &i,int k)
{
    int s=0,cnt=-1;
    while(k)
    {
        if(k&1)s=(s<<1|1);
        else s=(s<<1);
        k>>=1,cnt++;
    }
    while(cnt<40)cnt++,s<<=1;
    insert(i,s,0);
}
void ask(int x,int y,int sum,int dep)
{
    if(dep==41)
    {
        ans=max(ans,sum);
        return;
    }
    bool pd=1;
    if(T[x].lc&&T[y].rc)
        pd=0,ask(T[x].lc,T[y].rc,sum<<1|1,dep+1);
    if(T[x].rc&&T[y].lc)
        pd=0,ask(T[x].rc,T[y].lc,sum<<1|1,dep+1);
    if(pd&&T[x].lc&&T[y].lc)
        ask(T[x].lc,T[y].lc,sum<<1,dep+1);
    if(pd&&T[x].rc&&T[y].rc)
        ask(T[x].rc,T[y].rc,sum<<1,dep+1);
}
signed main()
{
    n=re();
    for(int i=1;i<=n;i++)
        a[i]=re();
    insert(rot1,0,0);insert(rot2,0,0);
    for(int i=1;i<=n;i++)
    {
        pre[i]=pre[i-1]^a[i];
        chuli(rot1,pre[i]);
    }
    for(int i=n;i>0;i--)
    {
        nex[i]=nex[i+1]^a[i];
        chuli(rot2,nex[i]);
    }
    ask(rot1,rot2,0,0);
    wr(ans);
    return 0;
}
```
核心代码实现思想：`insert` 函数用于将数插入 01Trie 树，`chuli` 函数对插入数进行翻转处理方便查询，`ask` 函数在两棵 01Trie 树中查询最大异或值。主函数中先预处理前后缀异或和并插入对应 01Trie 树，最后调用 `ask` 函数获取结果。

#### 作者：☯☯枫☯☯ (4星)
- **关键亮点**：对题意理解清晰，详细说明了 Trie 树在二进制运算中的应用，代码实现简洁明了，包含插入、删除和查询操作。
- **个人心得**：无

```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define F(i,a,b) for(reg int i=(a);i<=(b);i++)
inline ll read();
using namespace std;
const int N=1e5+10;
int n,trie[N*64][2],cnt=1,rec[N*64];
ll bk[N],a[N],ans;
inline void insert(ll x) {
    int p=1;
    for(reg int i=62; i>=0; i--) {
        bool k=(x&(1ll<<i));
        if(!trie[p][k])trie[p][k]=++cnt;
        p=trie[p][k];
        rec[p]++;
    }
}
inline void del(ll x) {
    int p=1;
    for(reg int i=62; i>=0; i--){
        bool k=(x&(1ll<<i));
        if(!rec[p] or!trie[p][k])return;
        p=trie[p][k];
        rec[p]--;
    }
}
inline ll search(ll x){
    int p=1;
    ll s=0;
    for(reg int i=62;i>=0;i--){
        bool k=(x&(1ll<<i));
        s<<=1ll;
        int &to=trie[p][k^1];
        if(!to or!rec[to]){
            if(rec[trie[p][k]] and trie[p][k])p=trie[p][k];
            else break;
        }
        else p=to,s|=1ll;
    }
    return s;
}
int main() {
    n=read();
    F(i,1,n)a[i]=read();
    for(reg int i=n; i>=1; i--)bk[i]=bk[i+1]^a[i],insert(bk[i]);
    ll cur=0;
    ans=search(cur);
    F(i,1,n){
        cur^=a[i];
        del(bk[i]);
        ans=max(ans,search(cur));
    }
    printf("%lld",ans);
    return 0;
}
inline ll read() {
    reg ll x=0;
    reg char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=(x<<3ll)+(x<<1ll)+(c^48),c=getchar();
    return x;
}
```
核心代码实现思想：`insert` 函数将后缀异或和插入 Trie 树，`del` 函数用于删除后缀异或和，`search` 函数在 Trie 树中查找与当前前缀异或和对应的最大异或值。主函数先计算并插入后缀异或和，再遍历数组更新前缀异或和，删除对应后缀异或和并查询最大异或值。

#### 作者：Leap_Frog (4星)
- **关键亮点**：指出不重合条件无用，利用异或 $x\oplus x = 0$ 的性质简化问题，代码简洁清晰。
- **个人心得**：无

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
    x=0;char c=getchar(),f=0;
    for(;c<'0'||c>'9';c=getchar()) if(c=='-') f=1;
    for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
    if(f) x=-x;
}
int n,ch[4000005][2],tt,rt;ll a[100005],s[100005],t[100005];
inline void ins(int &x,ll vl,int d=40)
{
    x?x:x=++tt;if(d<0) return;
    ins(ch[x][(vl>>d)&1],vl,d-1);
}
inline ll qry(int x,ll vl,int d=40)
{
    int nw;if(d<0) return 0;else nw=(vl>>d)&1;
    if(ch[x][!nw]) return qry(ch[x][!nw],vl,d-1)+(1ll<<d);
    else return qry(ch[x][nw],vl,d-1);
}
int main()
{
    read(n);for(int i=1;i<=n;i++) read(a[i]);
    for(int i=1;i<=n;i++) s[i]=s[i-1]^a[i];
    for(int i=n;i>=1;i--) t[i]=t[i+1]^a[i];
    for(int i=0;i<=n;i++) ins(rt,s[i]);
    ll rs=0;for(int i=1;i<=n+1;i++) rs=max(rs,qry(rt,t[i]));
    return printf("%lld\n",rs),0;
}
```
核心代码实现思想：`ins` 函数将前缀异或和插入 Trie 树，`qry` 函数在 Trie 树中查询后缀异或和对应的最大异或值。主函数预处理前后缀异或和，插入前缀异或和到 Trie 树，遍历后缀异或和查询并更新最大异或值。

### 最优关键思路或技巧
利用 01Trie 树解决异或相关问题，通过预处理前缀和后缀异或和，将前缀异或和插入 01Trie 树，在查询后缀异或和与前缀异或和的最大异或值时，利用异或在二进制下的性质，从高位到低位贪心选择，使异或和尽可能大。

### 可拓展之处
此类题目属于异或相关的数组处理问题，常见套路是利用异或的性质结合数据结构优化计算。类似题目通常围绕数组元素的异或操作，求最大异或值、满足特定条件的异或组合等。例如给定一个数组，求子数组异或和满足某种条件的问题，可尝试用 01Trie 树结合前缀异或和求解。

### 推荐洛谷题目
- [P3834 【模板】可持久化线段树 2（主席树）](https://www.luogu.com.cn/problem/P3834)：涉及到前缀和与数据结构优化查询，与本题利用前缀异或和结合 01Trie 树优化有相似思路。
- [P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)：同样是异或相关问题，通过树结构与异或性质求解，有助于巩固异或问题的处理能力。
- [P2048 [NOI2010] 超级钢琴](https://www.luogu.com.cn/problem/P2048)：虽然不是直接的异或问题，但在利用数据结构优化查询最大元素方面与本题有相似的优化思维。 

---
处理用时：114.78秒