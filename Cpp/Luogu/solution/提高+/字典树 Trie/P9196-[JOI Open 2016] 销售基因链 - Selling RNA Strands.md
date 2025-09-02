# [JOI Open 2016] 销售基因链 / Selling RNA Strands

## 题目背景

**译自 [JOI Open 2016](https://contests.ioi-jp.org/open-2016/index.html) T2 「RNA 鎖の販売 / Selling RNA Strands」**

本题由于测试数据过多，仅在此提供部分测试数据，剩余数据请[于此测试](https://www.luogu.com.cn/problem/U288877)。

## 题目描述

基因库中有 $N$ 个字符串，这些字符串仅由 `A`，`G`，`U`，`C` 组成（保证每个字符串都包含四种字母）。

有 $M$ 组查询，每组查询包含两个字符串 $P,Q$，试求：基因库中有多少个字符串同时存在前缀 $P$ 和后缀 $Q$。

举个例子，`GAC` 存在前缀 `G`、`GA`、`GAC`，存在后缀 `C`、`AC`、`GAC`，那么我们可以说：`GAC` 同时存在前缀 `GA` 和后缀 `AC`。

## 说明/提示

### 样例 1 解释

第一组查询：无法找到；  
第二组查询：`AUGC` 满足条件；  
第三组查询：`AUGC` 和 `AGC` 满足条件。

### 样例 2 解释

注意基因库中的字符串可以重复。

### 数据规模与约定

**本题采用捆绑测试**。

对于所有数据，$1\le N, M \leq 10 ^ 5$，$1 \leq |S_i|, |P_j|, |Q_j| \le 10^5$，$1\le\sum |S_i|, \sum |P_j|, \sum |Q_j| \le 2\times 10^6$。

- Subtask 1（10 points）：$N, M, |S_i|, |P_j|, |Q_j| \le 100$。
- Subtask 2（25 points）：$N, M\le 5000$。
- Subtask 3（25 points）：$\sum |S_i|, \sum|P_j|, \sum |Q_j| \le 10^5$。
- Subtask 4（40 points）：没有额外限制。

## 样例 #1

### 输入

```
2 3
AUGC
AGC
G C
AU C
A C```

### 输出

```
0
1
2```

## 样例 #2

### 输入

```
3 3
AA
AA
AGA
AA AA
AG GA
AG GA```

### 输出

```
2
1
1```

## 样例 #3

### 输入

```
8 7
GCGCUACCCCAACACAAGGCAAGAUAUA
G
GGAC
GCGG
U
GCGCUACCCCAACACAAGGCAAGAUGGUC
GCCG
GCGCUGA
GCGCUACCC A
GCGCUACCCC AC
GCG C
GCGC A
G G
G C
G GGA```

### 输出

```
1
0
1
2
3
2
0```

# 题解

## 作者：AFewSuns (赞：34)

感觉这题出的很好阿，但是评黑有点过了。

### 题目大意

给定 $n$ 个文本串 $S_i$，有 $m$ 次询问，每次给定两个字符串 $P,Q$，求有多少个文本串同时包含前缀 $P$ 和后缀 $Q$。

$1 \leq n,m \leq 10^5,1 \leq |S_i|,|P_i|,|Q_i| \leq 10^5,1 \leq \sum|S_i|,\sum|P_i|,\sum|Q_i| \leq 2 \times 10^6,|\Sigma|=4$。

### 题目分析

首先看到题目的第一反应肯定是 $\text{trie}$，如果只有前缀要求的话就是 $\text{trie}$ 树板子了。

不过没关系。考虑到这个板子的前缀查询实际上是求 $\text{trie}$ 树上某个子树内有多少个串，于是对反串也建一个 $\text{trie}$ 树，这样相当于数有多少个串，既在第一棵树的某个子树内，也在第二棵树的某个子树内。

子树问题可以通过 $\text{dfs}$ 序转化成区间问题，于是这就变成了一个经典的二维数点问题：

> 给定平面上 $n$ 个点，$m$ 次询问一个矩形内有多少个点。

差分后二维数点即可，复杂度 $\mathcal O(\sum|S|+(n+m)\log n)$，这好像也是官方题解的做法。

---

但是强化成二维数点好像很蠢。有没有更好的做法呢？

有！

把反串的那棵 $\text{trie}$ 扔掉，现在只有一开始的 $\text{trie}$。还是将子树转化成区间，那么问题相当于求一段区间 $[l_i,r_i]$ 内有多少个串包含后缀 $Q_i$。

这又是一个经典问题，可以构建可持久化 $\text{trie}$ 来做到 $\mathcal O(\sum|S|)$ 的复杂度。

---

还有没有其他做法？

有！

这次我们不把子树问题转化成区间问题，而是直接在 $\text{trie}$ 树上讨论。一个比较容易想到的做法是对 $\text{trie}$ 树上每个节点都建一棵 $\text{trie}$，用来维护子树内串的后缀信息。

如果直接使用类似线段树套线段树的做法，那么时间空间复杂度双双爆炸。可以将询问离线下来之后 $\text{dsu on tree}$。具体来说，将一个节点的子树大小定义为子树内 $\text{trie}$ 的长度和，那么除去第一次的插入，每次暴力插入一个串时，它所在的节点的子树大小就会至少翻一倍，时间复杂度 $\mathcal O(\sum|S|\log\sum|S|)$。

---

能不能再快一点？

能！

注意到 $\text{dsu on tree}$ 的题一般都可以用线段树合并做，于是类似地，我们使用 $\text{trie}$ 树合并。

类比线段树合并的过程，合并两个 $\text{trie}$ 时，如果当前节点只有一个 $\text{trie}$ 有，那么直接返回；否则一直搜索下去，将两树这个节点的信息合并。

至于时间复杂度，不妨设合并的两棵树大小为 $T_x,T_y$，合并之后的树大小为 $T'$，那么这次合并的时间复杂度就是 $\mathcal O(T_x+T_y-T')$，即 $T_x$ 和 $T_y$ 的重合部分。将所有的 $\text{trie}$ 树合并复杂度加起来，那么 $-T'$ 会在它合并的时候与 $+T'$ 抵消掉，最后的复杂度就是所有叶子的 $\text{trie}$ 树大小和减去根的 $\text{trie}$ 树大小。而所有叶子的 $\text{trie}$ 树大小和就是 $\sum|S|$，所以时间复杂度就是 $\mathcal O(\sum|S|)$ 的了！

---

能不能不用 $\text{trie}$？

能！

回到最初的问题，我们需要同时匹配前缀和后缀。这很麻烦，因为前缀和后缀中间可能会有空隙，甚至可能重合，导致一般解决匹配问题的方法都不可行。

既然如此，我们就把它强行“拼接”起来，把一个串 $S_i$ 变成 $S_i\#S_i$，其中 $\#$ 是一个特殊字符。再把需要匹配的前缀 $P_i$ 和后缀 $Q_i$ 变成 $Q_i\#P_i$，那么 $S_i$ 能匹配这个前缀和后缀，就相当于 $S_i\#S_i$ 能匹配 $Q_i\#P_i$ 这个子串。

将所有的 $S_i\#S_i$ 拼接起来，为了避免跨串匹配，在 $S_i$ 与 $S_{i+1}$ 中间插入另一个特殊字符 $\&$，那么原问题就相当于给定 $m$ 个模式串，问它在一个大文本串里出现多少次，使用 AC 自动机即可做到 $\mathcal O(\sum|S|)$。

做法比较多，就不贴代码了。

最后感谢 @[KHIN](https://www.luogu.com.cn/user/236807) 大佬，没有他就没有这篇博客。

---

## 作者：rui_er (赞：12)

套路题，来讲个套路解法。

如果没有后缀的要求，答案就是 trie 树的子树内字符串数量。现在加上了后缀，尝试继续使用 trie 树解决问题。

我们建立两棵 trie 树 $T_1,T_2$，其中 $T_1$ 是正常的 trie 树，$T_2$ 是每个字符串翻转后的 trie 树。这样的话，包含给定后缀的字符串在 $T_2$ 上构成一棵子树。例如，样例一中的两棵 trie 树如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/fnpys80c.png)

考虑一个询问意味着什么，其实就是查询同时在 $T_1$ 一棵子树和 $T_2$ 一棵子树内的字符串数。例如 $(\texttt{AU},\texttt{C})$ 就是查询同时在 $T_1$ 的节点 $2$ 的子树和 $T_2$ 的节点 $1$ 的子树内的字符串数，只有 $\texttt{AUGC}$ 符合要求，因此答案为 $1$。

把每个字符串抽象为坐标 $(x,y)$ 的点，其中 $x,y$ 分别是 $T_1,T_2$ 上字符串终止节点的 dfs 序，那么一次询问就是查询一个矩形内部点的数量，是二维数点问题，扫描线维护即可。

```cpp
//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
    uniform_int_distribution<int> dist(L, R);
    return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 2e6+5;

int n, m, ans[N];
string s, t;
vector<tuple<int, int>> dots;
vector<tuple<int, int, int, int>> queries;

int f(char c) {
    if(c == 'A') return 0;
    if(c == 'G') return 1;
    if(c == 'U') return 2;
    if(c == 'C') return 3;
    return -1;
}

struct Trie {
    int son[N][4], tot, sz[N], dfn[N], tms;
    int insert(string s) {
        int u = 0;
        for(char c : s) {
            int k = f(c);
            if(!son[u][k]) son[u][k] = ++tot;
            u = son[u][k];
        }
        return u;
    }
    int find(string s) {
        int u = 0;
        for(char c : s) {
            int k = f(c);
            if(!son[u][k]) return -1;
            u = son[u][k];
        }
        return u;
    }
    void dfs(int u) {
        dfn[u] = tms++;
        sz[u] = 1;
        rep(i, 0, 3) {
            if(son[u][i]) {
                dfs(son[u][i]);
                sz[u] += sz[son[u][i]];
            }
        }
    }
}pre, suf;

struct BIT {
    int c[N];
    int lowbit(int x) {return x & (-x);}
    void add(int x, int k) {++x; for(; x < N; x += lowbit(x)) c[x] += k;}
    int ask(int x) {++x; int k = 0; for(; x; x -= lowbit(x)) k += c[x]; return k;}
}bit;

int main() {
    // freopen("debug.log", "w", stderr);
    scanf("%d%d", &n, &m);
    rep(i, 1, n) {
        cin >> s;
        int x = pre.insert(s);
        reverse(s.begin(), s.end());
        int y = suf.insert(s);
        dots.emplace_back(x, y);
    }
    pre.tms = suf.tms = 0;
    pre.dfs(0);
    suf.dfs(0);
    for(auto& [x, y] : dots) {
        x = pre.dfn[x];
        y = suf.dfn[y];
    }
    rep(i, 1, m) {
        cin >> s >> t;
        reverse(t.begin(), t.end());
        int u = pre.find(s), v = suf.find(t);
        if(u == -1 || v == -1) ans[i] = 0;
        else {
            // debug("# %d : %d %d %d %d\n", i, pre.dfn[u], suf.dfn[v], pre.dfn[u]+pre.sz[u]-1, suf.dfn[v]+suf.sz[v]-1);
            queries.emplace_back(pre.dfn[u]-1, suf.dfn[v]-1, i, +1);
            queries.emplace_back(pre.dfn[u]-1, suf.dfn[v]+suf.sz[v]-1, i, -1);
            queries.emplace_back(pre.dfn[u]+pre.sz[u]-1, suf.dfn[v]-1, i, -1);
            queries.emplace_back(pre.dfn[u]+pre.sz[u]-1, suf.dfn[v]+suf.sz[v]-1, i, +1);
        }
    }
    sort(dots.begin(), dots.end());
    sort(queries.begin(), queries.end());
    // for(auto [x, y, id, mul] : queries) debug("* %d %d %d %d\n", x, y, id, mul);
    int ds = (int)dots.size(), qs = (int)queries.size(), did = 0, qid = 0;
    // debug("= %d %d\n", pre.tot, suf.tot);
    rep(i, 0, pre.tot) {
        // debug("? %d\n", i);
        while(did < ds) {
            auto [x, y] = dots[did];
            if(x != i) break;
            // debug("+ %d/%d : %d %d\n", did, ds, x, y);
            bit.add(y, 1);
            ++did;
        }
        while(qid < qs) {
            auto [x, y, id, mul] = queries[qid];
            if(x != i) break;
            // debug("! %d/%d : %d %d %d %d -> %d\n", qid, qs, x, y, id, mul, bit.ask(y));
            ans[id] += mul * bit.ask(y);
            ++qid;
        }
    }
    rep(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}
```

---

## 作者：TKXZ133 (赞：7)

[销售基因链](https://www.luogu.com.cn/problem/P9196)

### 题目大意

给定 $n$ 个字符串，长度总和为 $m$，进行 $q$ 次询问，每次询问给定两个字符串 $p,s$，问所有的字符串中以 $p$ 为前缀且以 $s$ 为后缀的有多少个。

### 思路分析

分享一个船新的~~答辩~~做法。（目前是最劣解）

考虑哈希，对每个给定的字符串前后各做一遍哈希，将所有的哈希值离散化，对每个字符串往其对应的所有哈希值的 `vector` 中存入自己的编号。

那么我们的问题就变成了：

- 给定 $m$ 个集合，集合中数的总和在 $O(m)$ 数量级，进行 $q$ 次询问，每次询问两个集合的交集的元素个数。

这个问题可以通过 `bitset` 解决。

简单的说，我们可以对每个哈希值建一个 `bitset`，每次求交集的时候只需要与一下对应的 `bitset` 再求一下元素个数就可以了，单次时间复杂度为 $O(\frac{nm}{w})$，可以接受。

但空间复杂度无法接受，因此我们考虑根号分治平衡时空复杂度。

具体的说，我们设定一个阈值 $B$，只对所有元素个数大于 $B$ 的哈希值建立 `bitset`。查询时，对元素个数小于 $B$ 的集合直接暴力扫描加入一个公用的 `bitset`，再与另一个 `bitset` 与一下，最后将公用的 `bitset` 清空。

这样我们的时间复杂度就为：$O(qB+\frac{nq}{w}+m\log m)$，空间复杂度为 $O(\frac{nm}{vB})$，其中 $w=64,v=8$，时空都还可以接受。

于是你满怀希望的交了一发，取得了 $35\text{pts}$ 的好成绩，最大点跑了 $6s$。

开始大力卡常：

- 将哈希值离散化的 `map` 换成排序加去重加 `lower_bound`，时间降为 $4.5s$。

- 将 `unsigned long long` 自然溢出哈希改为 `unsigned int` 自然溢出哈希，时间降为 $4s$。

- 加字符串快读快写，时间降为 $3.5s$。

- 将固定阈值 $B=1000$ 改为 $B=\sqrt {q}$，时间降为 $3s$。

- 在查询时先判断哈希值存不存在，时间降为 $2s$。

- 将前哈希和后哈希分开，各自独立离散化，时间降为 $1.5s$。

这样，我们就以

![](https://user-images.githubusercontent.com/110758650/263566678-2b6bbb66-c94b-4cd2-b0d3-3ce2fdcf4208.png)

的好成绩~~喜提最劣解~~通过本题。

### 代码

（最劣解的代码也要看？）

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>

using namespace std;
const int M=5010,L=100010,N=2000100,P=133,Q=133;
typedef unsigned int ull;

int n,m,tt,tt2,cnt,tot1,tot2,BL,sum;
int vis1[N<<1],vis2[N<<1];
ull v3[N],v4[N],vHash1[N],vHash2[N];
int vid1[N],vid2[N];

vector<int> v1[N<<1],v2[N<<1];
bitset<L> bset[M];
char s[N],s1[N],s2[N];

#define getchar() (S==T&&(T=(S=B)+fread(B,1,1<<16,stdin),S==T)?EOF:*S++)
char B[1<<16],*S=B,*T=B;

inline void readint(int &x){
    x=0;char ch=getchar();
    while(ch<'0'||'9'<ch) ch=getchar();
    while('0'<=ch&&ch<='9') x=x*10+ch-'0',ch=getchar();
}

inline int readchar(char a[]){
    int len=0;
    char ch=getchar();
    while(ch<'A'&&'Z'<ch) ch=getchar();
    while('A'<=ch&&ch<='Z') a[++len]=ch,ch=getchar();
    return len;
}

void write(int x){
    int k=x/10;
    if(k) write(k);
    putchar(x%10+'0');
}

int main(){
    readint(n);readint(m);
    for(int i=1;i<=n;i++){
        int len=readchar(s);
        sum+=len;
        ull Hash=1;
        for(int j=1;j<=len;j++){
            Hash=Hash*P+s[j]+Q;
            v3[++tt]=Hash;tot1++;
            vHash1[tot1]=Hash;vid1[tot1]=i;
        }
        Hash=1;
        for(int j=len;j>=1;j--){
            Hash=Hash*P+s[j]+Q;
            v4[++tt2]=Hash;tot2++;
            vHash2[tot2]=Hash;vid2[tot2]=i;
        }
    }   
    BL=pow(m,0.5);
    sort(v3+1,v3+tt+1);sort(v4+1,v4+tt2+1);
    tt=unique(v3+1,v3+tt+1)-v3-1;
    tt2=unique(v4+1,v4+tt2+1)-v4-1;
    for(int i=1;i<=tot1;i++)
        v1[lower_bound(v3+1,v3+tt+1,vHash1[i])-v3].push_back(vid1[i]);
    for(int i=1;i<=tot2;i++)
        v2[lower_bound(v4+1,v4+tt2+1,vHash2[i])-v4].push_back(vid2[i]);
    for(int i=1;i<=tt;i++)
        if(v1[i].size()>BL){
            vis1[i]=++cnt;
            for(int j=0;j<v1[i].size();j++) bset[cnt][v1[i][j]]=1;
        }
    for(int i=1;i<=tt2;i++)
        if(v2[i].size()>BL){
            vis2[i]=++cnt;
            for(int j=0;j<v2[i].size();j++) bset[cnt][v2[i][j]]=1;
        }
    while(m--){
        int len1=readchar(s1);
        int len2=readchar(s2);
        ull Hash1=1,Hash2=1;
        for(int i=1;i<=len1;i++)
            Hash1=Hash1*P+s1[i]+Q;
        for(int i=len2;i>=1;i--)
            Hash2=Hash2*P+s2[i]+Q;
        int x=lower_bound(v3+1,v3+tt+1,Hash1)-v3;
        int y=lower_bound(v4+1,v4+tt2+1,Hash2)-v4;
        if(v3[x]!=Hash1||v4[y]!=Hash2){cout<<"0\n";continue;}
        if(v1[x].size()>BL&&v2[y].size()>BL){
            write((bset[vis1[x]]&bset[vis2[y]]).count());putchar('\n');
        }
        else if(v1[x].size()>BL||v2[y].size()>BL){
            if(v1[x].size()>BL){
                bitset<L> st;
                for(auto it:v2[y]) st[it]=1;
                write((st&bset[vis1[x]]).count());putchar('\n');
            }
            else{
                bitset<L> st;
                for(auto it:v1[x]) st[it]=1;
                write((st&bset[vis2[y]]).count());putchar('\n');
            }
        }
        else{
            bitset<L> st,st2;
            for(auto it:v1[x]) st[it]=1;
            for(auto it:v2[y]) st2[it]=1;
            write((st&st2).count());putchar('\n');
        }
    }
    return 0;
}
```

---

## 作者：Transfixion_ (赞：7)

题目链接：[$\texttt{Link}$](https://www.luogu.com.cn/problem/P9196)

给出一种只需要字符串哈希和 STL 的方法。

## $\textbf{Description}$

给定 $n$ 个字符串，这些字符串构成的集合记为 $\{S\}$。

现有 $m$ 个询问，每次询问给出两个字符串 $P,Q$，表示查询 $\{S\}$ 中满足 $P$ 为前缀且 $Q$ 为后缀的字符串的个数。

$1\le n,m\le 10^5,\,1\le |S_i|,|P_i|,|Q_i|\le 10^5,1\le \sum|S_i|,\sum|P_i|,\sum|Q_i|\le2\times10^6$。

## $\textbf{Solution}$

下文中哈希表的时间复杂度看成均摊 $\mathcal O(1)$。

### $\textbf{10 pts}$

判断一个字符串是否为另一个字符串的前 / 后缀，考虑 Hash。

那么有一个很显然的暴力可以写：

对于 $\{S\}$ 中的每个字符串，维护两个集合（`std::map` 或者 `std::set`），分别存前缀和后缀的 Hash 值。查询的时候先对 $P$ 和 $Q$ 进行 Hash，然后 $\mathcal O(n)$ 扫描每个字符串，判断 $P$ 和 $Q$ 的 Hash 值是否属于字符串的前 / 后缀集即可。

时间复杂度：读入与预处理 $\mathcal O(\sum|P_i|+\sum|Q_i|+\sum|S_i|)$，查询 $\mathcal O(nm)$。

### $\textbf{35 pts}$

上述做法以原字符串为对象，我们不妨换个角度，以前后缀 Hash 值为对象。

依然使用哈希表，给每个 Hash 值映射一个 `bool` 数组，查询等价于在前 / 后缀 Hash 值对应的 `bool` 数组中寻找同时为 $1$ 的下标个数。

容易优化为 `std::bitset`，查询的时候两个 `std::bitset` 与一下就行。

时间复杂度：读入与预处理 $\mathcal O(\sum|P_i|+\sum|Q_i|+\sum|S_i|)$，查询 $\mathcal O\left(\dfrac{nm}\omega\right)$。

### $\textbf{100 pts}$

$35\text{ pts}$ 做法的瓶颈在于空间。

MLE 肯定是 `std::map` 炸了。上述做法对每个字符串都保存它所有的前后缀，但是查询不一定用得到，十分浪费。

考虑离线。把 $\{S\}$ 全部存下来，预处理留到后面，先读询问。把所有 $P$ 和 $Q$ 对应的 Hash 值用 `std::map` 记录下来。

然后才是预处理。基本框架依然不变，不同的是仅在当前 Hash 值在询问中有出现时才在对应的 `std::bitset` 上修改。

空间复杂度：$\mathcal O(\sum|S_i|)$ 个 `std::bitset` $\to$ $\mathcal O(m)$ 个 `std::bitset`。

时间复杂度：读入与预处理 $\mathcal O(\sum|P_i|+\sum|Q_i|+\sum|S_i|)$，查询 $\mathcal O\left(\dfrac{nm}\omega\right)$。

---

upd：

本来这里是卡常教程，因为我本来用的是 `std::unordered_map`。

但是如果你用 `__gnu_pbds::gp_hash_table` 的话更本不用卡常。。。

## $\textbf{AC Code}$

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define rep(i, st, ed) for(int i = (st); i <= (ed); i++)
#define per(i, st, ed) for(int i = (st); i >= (ed); i--)
#define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 20], *p1 = buf, *p2 = buf;
template <typename _Tp> inline void read(_Tp& x) {
	char c = gc(); x = 0; bool f = 0;
	for(; !std::isdigit(c); c = gc()) f |= c == '-';
	for(; std::isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c ^ 48);
	f ? x = ~x + 1 : 1;
}
inline void read(std::string& x) {
	x.clear(); char c = gc(); while(!std::isalpha(c)) c = gc();
	while(std::isalpha(c)) x.push_back(c), c = gc();
}
template <typename _Tp, typename ...Args>
inline void read(_Tp& x, Args& ...args) {
	read(x), read(args...);
}

typedef long long i64;
typedef unsigned long long ui64;
constexpr int N = 1e5 + 5;
constexpr ui64 base = 233;
__gnu_pbds::gp_hash_table<ui64, std::bitset<N>> pre, suf;
__gnu_pbds::gp_hash_table<ui64, bool> p, q;
std::pair<ui64, ui64> qry[N];
std::string S[N], P, Q;
int n, m;

inline ui64 zip(char c) { return c - 'A' + 1; }
signed main() {
	read(n, m); rep(i, 1, n) read(S[i]);
	for(int i = 1, l1, l2; i <= m; i++) {
		read(P, Q);
		ui64 Hash1 = 0, Hash2 = 0;
		l1 = P.size(), l2 = Q.size();
		P = '#' + P, Q = '#' + Q;
		for(int j = 1; j <= l1; j++) Hash1 = Hash1 * base + zip(P[j]);
		for(int j = l2; j >= 1; j--) Hash2 = Hash2 * base + zip(Q[j]);
		p[Hash1] = 1, q[Hash2] = 1;
		qry[i] = std::make_pair(Hash1, Hash2);
	}
	for(int i = 1, len; i <= n; i++) {
		len = S[i].size(), S[i] = '#' + S[i];
		ui64 Hash1 = 0, Hash2 = 0;
		for(int j = 1; j <= len; j++) {
			Hash1 = Hash1 * base + zip(S[i][j]);
			Hash2 = Hash2 * base + zip(S[i][len - j + 1]);
			if(p[Hash1]) pre[Hash1].set(i);
			if(q[Hash2]) suf[Hash2].set(i);
		}
	}
	rep(i, 1, m) printf("%d\n", (int)(pre[qry[i].first] & suf[qry[i].second]).count());
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：6)

## 题目大意
给定 $N$ 个字符串 $S_i$，有 $M$ 组询问，第 $j$ 组询问有多少个字符串 $S_i$ 满足 $P_j$ 是其前缀，$Q_j$ 是其后缀。

$1\le N,M\le 10^5$，$1\le \sum |S_i|,\sum |P_j|,\sum |Q_j|\le 2\times 10^6$。

## 题目分析
标签：trie，莫队。但，我不会，但，

#### 我会 AC 自动机 ！！

又要前缀又要后缀，怎么办？

反向建 trie？没必要！

只需要把 $S_i$ 复制一遍，中间加个间隔符 `#`，得到 $R_i$，然后对于询问，构造一个字符串 $T=Q+$ `#` $+P$。问题就转换成了 AC 自动机的板子题了！为什么？

显而易见，我们新构造的 $R$ 长成这样：$S$`#`$S$，$T$ 长成这样：$Q$`#`$P$。那么 $T$ 是 $R$ 的子串，当且仅当 $Q$ 是 $S$ 的后缀，$P$ 是 $S$ 的前缀。正确性显然，问题就变成了多模匹配。

但这题普通的 AC 自动机匹配由于多次跳 fail，复杂度并非线性，容易 TLE，怎么办？

#### 我会拓扑排序优化！
用 vector 记录在每个节点结束的字符串的编号，建立 fail 树，然后将父节点记录的编号下传到子节点，查询时就减少反复跳 fail 的过程。复杂度 $O(\sum |S|)$。常数很大，需要吸氧。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK l>=Ll&&r<=Rr
#define ui unsigned int
#define ull unsigned ll
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define e(x) for(int i=h[x];i;i=nxt[i])
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e5+5,M=4e7+5,mod=10007;
using namespace std;
int n=read(),m=read(),ans[N],cnt,h[N*20],to[N*40],nxt[N*40],ct;
inline void add(int a,int b){
	to[++ct]=b,nxt[ct]=h[a],h[a]=ct;	
} 
string s[N],t[N];
inline int id(char c){
	if(c=='#')return 5;
	if(c=='A')return 1;
	if(c=='U')return 2;
	if(c=='G')return 3;
	return 4;
}
struct node{
	int son[6],fail;
	vector<int>p;
}trie[N*20];
inline void insert(int x){
	int len=t[x].length(),now=0;
	rep(i,0,len-1){
		int k=id(t[x][i]);
		if(!trie[now].son[k])trie[now].son[k]=++cnt;
		now=trie[now].son[k];
	}
	trie[now].p.push_back(x);
}
inline void dfs(int x){
	int si=trie[x].p.size()-1;
	e(x){
		int y=to[i];
		rep(j,0,si)trie[y].p.push_back(trie[x].p[j]);
		dfs(y);
	}
}
inline void build(){
	queue<int>q;
	rep(i,1,5)if(trie[0].son[i])q.push(trie[0].son[i]),trie[trie[0].son[i]].fail=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		rep(i,1,5)if(trie[x].son[i])q.push(trie[x].son[i]),trie[trie[x].son[i]].fail=trie[trie[x].fail].son[i];
		else trie[x].son[i]=trie[trie[x].fail].son[i];
	}
	rep(i,1,cnt)add(trie[i].fail,i);
	dfs(0);
} 
inline void query(int x){
	int len=s[x].length(),now=0;
	rep(i,0,len-1){
		int k=id(s[x][i]);
		now=trie[now].son[k];
		int si=trie[now].p.size()-1;
		rep(j,0,si){
			int y=trie[now].p[j];
			ans[y]++;
		}
	}
}
int main(){
	string a,b;
	rep(i,1,n)cin >>a,s[i]=a+'#'+a;
	rep(i,1,m)cin >>a>>b,t[i]=b+'#'+a,insert(i);
	build();
	rep(i,1,n)query(i);
	rep(i,1,m)pf(ans[i]),putchar('\n');
	return 0;
}
```


---

## 作者：LimpidSlirm (赞：5)

## 题意 

给定 $n$ 个由 `A`，`G`，`U`，`C` 组成的字符串 $s_1,s_2,\dots,s_n$。$q$ 次查询以 $pre_i$ 为前缀，以 $suc_i$ 为后缀的字符串个数。

## Solution

显然地，用 trie 树来处理前后缀，发现关键问题在于如何判断同时满足前后缀要求。发现将 $s_1,s_2,\dots,s_n$ 排序后，满足前缀为 $pre_i$ 的字符串编号连续，设其为 $[a_l,a_r]$。将 $s_1,s_2,\dots,s_n$ 翻转后排序，满足后缀为 $suc_i$ 的字符串编号同样连续，设其为 $[b_l,b_r]$。设字符串 $s_i$ 原来排序后的编号为 $u_i$，翻转排序后的编号为 $v_i$。则问题转化为同时满足 $u_i \in [a_l,a_r]$，$v_i\in [b_l,b_r]$ 的字符串个数。

考虑离线后二维数点解决，$[a_l,a_r]$ 和 $[b_l,b_r]$ 可用 trie 树快速维护。设 $\sum{\mid s_i\mid}=m$，字符串平均长度为 $len$，显然地，对于两个字符串，比较的最坏复杂度为 $\mathcal{O}(len)$，则排序复杂度为 $\mathcal{O}((\frac{m}{len}\log\frac{m}{len})\times len)$ 即 $\mathcal{O}(m \log \frac{m}{len})$，最坏情况下 $len=1$，即最坏复杂度为 $\mathcal{O}(m \log m)$。故总时间复杂度为 $\mathcal{O}(m\log m+\sum{\mid pre_i\mid}+\sum{\mid suc_i\mid})$，可以在时限内通过。

~~其实跑起来还是很快的，直接冲到最优解 rk2（rk1 坐在我边上）。~~

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
struct node 
{
	int data;
	int son[5];
};
int tot;
struct node nd[2000010];
int l[2000010],r[2000010];
int cnt[2000010],ans[2000010];
string s[100010];
vector<tuple<string,int,int> > info[2000010];
int helper(char ch)
{
	switch(ch)
	{
		case 'A': return 1;
		case 'U': return 2;
		case 'G': return 3;
		case 'C': return 4;
	}
	return -1;
}
void insert(string s,int id)
{
	int fr=0;
	for(int i=0;i<s.length();i++)
	{
		int tmp=helper(s[i]);
		int to=nd[fr].son[tmp];
		if(to==0)
		{
			nd[fr].son[tmp]=++tot;
			to=tot;
			l[to]=id,r[to]=id;
		}
		l[to]=min(l[to],id),r[to]=max(r[to],id);
		fr=to;
	}
	return ;
}
void modify(string s)
{
	int fr=0;
	for(int i=s.length()-1;i>=0;i--)
	{
		int tmp=helper(s[i]);
		int to=nd[fr].son[tmp];
		if(to==0)
			nd[fr].son[tmp]=++tot,to=tot;
		cnt[to]++;
		fr=to;
	}
	return ;
}
int query(string s)
{
	int fr=0;
	for(int i=0;i<s.length();i++)
	{
		int tmp=helper(s[i]);
		int to=nd[fr].son[tmp];
		if(to==0)
			return -1;
		fr=to;
	}
	return fr;
}
int main(int argc,const char *argv[])
{
	int n=read(),q=read();
	for(int i=1;i<=n;i++)
		cin>>s[i];
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++)
		insert(s[i],i);
	for(int i=1;i<=q;i++)
	{
		string pre,suc;
		cin>>pre>>suc;
		int pos=query(pre);
		if(pos==-1)
			continue;
		reverse(suc.begin(),suc.end());
		info[r[pos]].push_back(make_tuple(suc,i,1));
		info[l[pos]-1].push_back(make_tuple(suc,i,-1));
	}
	memset(nd,0,sizeof nd);
	tot=0;
	for(int i=1;i<=n;i++)
	{
		modify(s[i]);
		for(auto j:info[i])
		{
			int pos=query(get<0>(j));
			ans[get<1>(j)]+=cnt[pos]*get<2>(j);
		}
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：3)

模拟赛题，总算补上一道了。

考场 Trie 树写挂。。

复杂度多一个根号竟成了最优解。

------------

考虑按字典序排序后，相同前缀一定连续。

将所有串翻转后再存一遍，同样用排序处理后缀。

注意要标记正反两种串的对应关系（例如，记录字典序第 $i$ 小的字符串翻转后第 $id_i$ 小），方便下面处理。

其实直接二分（没必要用 Trie 树）就可以快速得到两段区间，分别表示前缀为 $P$ 的串，和后缀为 $Q$ 的串。

想象其在二维空间中，每个串映射成一个二维的位置。

经典的二维数点问题，与其他做法不同，我使用莫队和树状数组维护矩形内点的个数。

对于一维用莫队维护区间状态，另一维用树状数组维护单点修改并求区间和。

主要难在问题转换上，复杂度 $\operatorname{O}(n\times\log n\times\sqrt n)$。

------------

复杂度很高，但不卡常最优解。

欢迎大佬 hack。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+84;
int n,m,sqn,l=1,r,T[maxn];
pair<string,int> f[maxn];
string z[maxn],pp,qq;
struct Query{
    int xl,xr,yl,yr,id,ans;
    friend bool operator<(Query xy,Query zb){
        if((xy.yl-1)/sqn==(zb.yl-1)/sqn){
            if(((xy.yl-1)/sqn)&1)
                return xy.yr>zb.yr;
            return xy.yr<zb.yr;
        }
        return xy.yl<zb.yl;
    }
}q[maxn];
inline int lowbit(int x){
    return x&(-x);
}
inline void modify(int x,int delta){
    while(x<=n){
        T[x]+=delta;
        x+=lowbit(x);
    }
    return ;
}
inline int query(int x){
    int res=0;
    while(x){
        res+=T[x];
        x-=lowbit(x);
    }
    return res;
}
inline bool cmp(Query xy,Query zb){
    return xy.id<zb.id;
}
int main(){
    scanf("%d%d",&n,&m);
    sqn=(n-1)/sqrt(m)+1;
    for(int i=1;i<=n;i++)
        cin>>z[i];
    sort(z+1,z+n+1);
    for(int i=1;i<=n;i++){
        f[i]={z[i],i};
        reverse(f[i].first.begin(),f[i].first.end());
    }
    sort(f+1,f+n+1);
    for(int i=1;i<=m;i++){
        cin>>pp>>qq;
        reverse(qq.begin(),qq.end());
        q[i].xl=lower_bound(z+1,z+n+1,pp)-z;
        q[i].yl=lower_bound(f+1,f+n+1,make_pair(qq,-168))-f;
        pp[pp.size()-1]++;
        qq[qq.size()-1]++;
        q[i].xr=lower_bound(z+1,z+n+1,pp)-z-1;
        q[i].yr=lower_bound(f+1,f+n+1,make_pair(qq,-168))-f-1;
        q[i].id=i;
    }
    sort(q+1,q+m+1);
    for(int i=1;i<=m;i++){
        while(l>q[i].yl){
            l--;
            modify(f[l].second,1);
        }
        while(l<q[i].yl){
            modify(f[l].second,-1);
            l++;
        }
        while(r<q[i].yr){
            r++;
            modify(f[r].second,1);
        }
        while(r>q[i].yr){
            modify(f[r].second,-1);
            r--;
        }
        q[i].ans=query(q[i].xr)-query(q[i].xl-1);
    }
    sort(q+1,q+m+1,cmp);
    for(int i=1;i<=m;i++)
        printf("%d\n",q[i].ans);
    return 0;
}
```


---

## 作者：zzxLLL (赞：3)

[AFewSuns](https://www.luogu.com.cn/user/224336)大佬太强了，先膜拜一波。

---

无脑的线性的后缀自动机做法。

又要查前缀又要查后缀，所以套路地将每个文本串倍长，中间用特殊字符连接。再将所有的倍长过的文本串连成一大串，中间用另一个字符连接。

然后就变成了``S1#S1$S2#S2$...$Sn#Sn$``的样子，构建其后缀自动机。

对于查询串，将其拼接成``Q#P``的样子，然后直接放在后缀自动机上跑就行了。

~~喜提最劣解。~~

```cpp
#include<cstdio>
#include<cstring>
const int M=5e6+10,N=4e5+10;

int turn(char ch){
	if(ch=='A') return 0;
	if(ch=='G') return 1;
	if(ch=='U') return 2;
	if(ch=='C') return 3;
	return -1;
}

struct node{int ch[6],fa,len,size;}v[M<<1];
int last=1,cnt=1;
void insert(int x){
	int cur=++cnt,p=last;
	v[cur].len=v[last].len+1;
	while(p && !v[p].ch[x]) v[p].ch[x]=cur,p=v[p].fa;
	int q=v[p].ch[x];
	if(!q) v[cur].fa=1;
	else
		if(v[q].len==v[p].len+1) v[cur].fa=q;
		else{
			int nq=++cnt;
			v[nq]=v[q],v[nq].len=v[p].len+1;
			while(p && v[p].ch[x]==q) v[p].ch[x]=nq,p=v[p].fa;
			v[q].fa=v[cur].fa=nq;
		}
	last=cur;
}

int head[M<<1],cnte;
struct Edge{int to,next;}edge[M<<1];
void add(int u,int v){
	edge[++cnte].to=v;
	edge[cnte].next=head[u];
	head[u]=cnte;
}
void getsize(int u){
	for(int i=head[u];~i;i=edge[i].next)
		getsize(edge[i].to),v[u].size+=v[edge[i].to].size;
}

int qwq,Q[N];
int n,m,len,S[M];
char T[N],pre[N],suf[N];

int main(){
	memset(head,-1,sizeof head);
	scanf("%d%d",&n,&m);
	for(int i=1,ln;i<=n;i++){
		scanf(" %s",T+1),ln=strlen(T+1);
		for(int j=1;j<=ln;j++) S[++len]=turn(T[j]); S[++len]=4;
		for(int j=1;j<=ln;j++) S[++len]=turn(T[j]); S[++len]=5;
	}
	
	for(int i=1;i<=len;i++) insert(S[i]);
	int cur=1;
	for(int i=1;i<=len;i++) v[cur=v[cur].ch[S[i]]].size=1;
	for(int i=2;i<=cnt;i++) add(v[i].fa,i);
	getsize(1);
	
	for(int i=1,ln;i<=m;i++){
		scanf(" %s",pre+1),scanf(" %s",suf+1);
		ln=strlen(suf+1),qwq=0;
		for(int j=1;j<=ln;j++) Q[++qwq]=turn(suf[j]);
		Q[++qwq]=4,ln=strlen(pre+1);
		for(int j=1;j<=ln;j++) Q[++qwq]=turn(pre[j]);
		
		bool flag=true; cur=1;
		for(int j=1;j<=qwq;j++)
			if(!v[cur].ch[Q[j]]){flag=false;break;}
			else cur=v[cur].ch[Q[j]];
		if(!flag) printf("0\n");
		else printf("%d\n",v[cur].size);
	}
	return 0;
}
```

---

## 作者：luckydrawbox (赞：3)

[$\text{Link}$](https://www.luogu.com.cn/problem/P9196)

## 分析

假设题目只询问一个前缀，我们知道，将一堆字符串排序后，前缀相同的串是排在一起的，所以可以直接排序，二分出第一个和最后一个前缀相同的位置即可。

进一步的，如果有多组询问，我们可以把询问的前缀 $S$ 直接放进那堆字符串里一起排序，这样前缀所在的位置往后一段区间的字符串的前缀都是该前缀，但我们还需要知道末尾，注意到题目中的字符串都是大写字母，所以字符串 $S+\texttt{a}$ 一定比其他前缀为 $S$ 的前缀大，所以也把 $S+\texttt{a}$ 加入其中一起排序，这样我们就可以求出前缀为 $S$ 的字符串所在的区间 $[lpre_S,rpre_S]$ 了。

更进一步的，加上后缀的限制，我们把字符串反过来，也可以求出每个后缀对应的区间 $[lsuf_S,rsuf_S]$，假设一个非询问串在前缀排序时的位置为 $x$，后缀排序时的位置为 $y$，询问就变成了求 $lpre_S<x<rpre_S\land lsuf_S<y<rsuf_S$ 的点对 $(x,y)$ 的个数，是个经典的二维数点问题，直接离线 $+$ 树状数组即可解决。

对于排序，可以直接用 $\text{sort}$，设字符串总长为 $|S|$，使用 $\text{sort}$ 的时间复杂度其实是 $O((n+m+|S|\log|S|)\log(n+m))$ ，开 $\text{O2}$ 也能过，不必用 $\text{Trie}$。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch))
	{if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=1e5+10;
int n,m,c[N*3],ans[N];
string s[N],p[2][N];
struct Node{
	int rank[2];
}a[N];
struct Que{
	int l[2],r[2];
}b[N];
struct Str{
	string s;
	int id;
}d[N*3];
bool cmp(Str a,Str b){
	return a.s==b.s?a.id>b.id:a.s<b.s;
}
vector<int>ad[N*3];
vector<pair<int,int> >q1[N*3];
void add(int x,int v){
	for(;x<=n+2*m;x+=x&-x)
		c[x]+=v;
}
int ask(int x){
	int ans=0;
	for(;x;x-=x&-x)
		ans+=c[x];
	return ans;
}
void reverse(string &s){
	int len=s.size();
	for(int i=0;i*2<len;i++)
		swap(s[i],s[len-i-1]);
}
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		cin>>s[i];
		d[i].s=s[i];d[i].id=i;
	}
	for(int i=1;i<=m;i++){
		cin>>d[n+2*i-1].s>>p[1][i];
		d[n+2*i-1].id=n+i;
		d[n+2*i].s=d[n+2*i-1].s+"a";d[n+2*i].id=n+i;
	}
	sort(d+1,d+n+2*m+1,cmp);
	for(int i=1,j;i<=n+2*m;i++){
		if(d[i].id<=n)
			a[d[i].id].rank[0]=i;
		else{
			j=d[i].id-n;
			if(b[j].l[0])b[j].r[0]=i;
			else b[j].l[0]=i;
		}
	}
	for(int i=1;i<=n;i++){
		reverse(s[i]);
		d[i].s=s[i];d[i].id=i;
	}
	for(int i=1;i<=m;i++){
		reverse(p[1][i]);
		d[n+2*i-1].s=p[1][i];d[n+2*i-1].id=n+i;
		d[n+2*i].s=p[1][i]+"a";d[n+2*i].id=n+i;
	}
	sort(d+1,d+n+2*m+1,cmp);
	for(int i=1,j;i<=n+2*m;i++){
		if(d[i].id<=n)
			a[d[i].id].rank[1]=i;
		else{
			j=d[i].id-n;
			if(b[j].l[1])b[j].r[1]=i;
			else b[j].l[1]=i;
		}
	}
	for(int i=1;i<=n;i++)
		ad[a[i].rank[0]].push_back(i);
	for(int i=1;i<=m;i++){
		if(b[i].l[0]>b[i].r[0]||b[i].l[1]>b[i].r[1])continue;
		q1[b[i].l[0]-1].push_back(make_pair(i,0));
		q1[b[i].r[0]].push_back(make_pair(i,1));
	}
	for(int i=1;i<=n+2*m;i++){
		for(auto j:ad[i]){
			add(a[j].rank[1],1);
		}
		for(auto j:q1[i]){
			if(j.second==0)
				ans[j.first]+=ask(b[j.first].l[1]-1)-ask(b[j.first].r[1]);
			else
				ans[j.first]+=ask(b[j.first].r[1])-ask(b[j.first].l[1]-1);
		}
	}
	for(int i=1;i<=m;i++){
		write(ans[i]);puts("");
	}
	return 0;
}
```

---

## 作者：Luzhuoyuan (赞：2)

抽象做法。模拟赛题，但是哈希爆炸了……

Link: [[Luogu]](https://www.luogu.com.cn/problem/P9196)

### 题意

给定 $N$ 个仅包含字符 `A`、`G`、`U`、`C` 的字符串 $S_i$，有 $M$ 次询问，第 $j$ 次给出两个字符串 $P_j,Q_j$，问有多少字符串满足 $P_j$ 是其前缀且 $Q_j$ 是其后缀。

- $1\le N,M,|S_i|,|P_j|,|Q_j|\le 10^5$；
- $\sum|S_i|,\sum|P_j|,\sum|Q_j|\le 2\times 10^6$。

### 思路

没有想到两个 Trie 的做法，但是由于最近启发式合并做多了，搞出来一个抽象做法。

首先，对前缀和后缀分开考虑。要求的值即为 Trie 树上指定的前缀对应的点的子树内有多少串的后缀等于指定的后缀。

于是我们建一个 Trie，插入每个串 $S_i$ 并在其对应位置上开一个哈希表，当作桶存储 $S_i$ 的每个后缀的哈希值。之后，我们离线操作，把每个操作挂在这个操作的前缀在 Trie 上对应的点上（如果没有这样的点答案就是 $0$，直接忽略）。

接着，我们对 Trie 进行 DFS。对于每个点，先遍历其儿子，并在过程中维护当前点及其已经遍历的子孙的后缀组成的桶。对于每个新遍历的儿子，将当前的桶与该儿子的桶进行启发式合并，即遍历其中较小的桶，并将其中的元素加入另一个桶。遍历完所有儿子后，我们就可以处理当前点上的询问，每个询问的答案即为询问的后缀在桶中的出现次数。

容易证明，时间复杂度为 $O((\sum|S_i|)\log(\sum|S_i|))$，略微精细处理即可轻松通过本题，跑得飞快（没在最优解最后一页）。

### 代码

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#define ull unsigned
//卡空间用的 unsigned（本题可以用 unsigned long long 获得更大的正确率和常数）
#define pb push_back
#define SZ(x) (int)((x).size())
using namespace std;
const int N=2e6+5,M=1e5+5;
const ull B=1e9+7;
int n,m,o[M],cnt,to[200];
ull q[M],d[4];
char s[M];
mt19937 rnd(time(0));
__gnu_pbds::gp_hash_table<ull,int> mp[M];
//卡常用的 pbds 的 gp_hash_table
struct Trie{
	int t[N][4],tot,fl[N];
	vector<int> ve[N];
	inline void ins(){
		int l=strlen(s),u=0;ull v=0;
		for(int i=0;i<l;i++){
			if(!t[u][to[(int)s[i]]])t[u][to[(int)s[i]]]=++tot;
			u=t[u][to[(int)s[i]]];
		}if(!fl[u])fl[u]=++cnt;
		for(int i=l-1;~i;i--)v=v*B+d[to[(int)s[i]]],mp[fl[u]][v]++;
	}//插入一个字符串
	inline void qry(int id){
		int l=strlen(s),u=0;
		for(int i=0;i<l;i++){if(!t[u][to[(int)s[i]]])return;u=t[u][to[(int)s[i]]];}
		ve[u].pb(id);
	}//挂一个询问
	int dfs(int u=0){
		for(int i=0;i<4;i++)if(t[u][i]){
			int v=dfs(t[u][i]);if(!fl[u]){fl[u]=v;continue;}
			if(SZ(mp[fl[u]])<SZ(mp[v]))swap(fl[u],v);
			for(auto i:mp[v])mp[fl[u]][i.first]+=i.second;
			mp[v].clear();
		}
		for(int v:ve[u])if(mp[fl[u]].find(q[v])!=mp[fl[u]].end())o[v]=mp[fl[u]][q[v]];
		return fl[u];
	}
}T;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>m;to['U']=1,to['G']=2,to['C']=3;
	for(int i=0;i<4;i++)d[i]=rnd();
	for(int i=1;i<=n;i++)cin>>s,T.ins();
	for(int i=1;i<=m;i++){
		cin>>s,T.qry(i),cin>>s;
		for(int j=strlen(s)-1;~j;j--)q[i]=q[i]*B+d[to[(int)s[j]]];
	}T.dfs();
	for(int i=1;i<=m;i++)cout<<o[i]<<'\n';
	return 0;
}
```

（逃

---

## 作者：Nuyoah_awa (赞：2)

### 题目大意

$N$ 个串，多次询问，求前缀和后缀为 $P,Q$ 的字符串数量。

### 题目分析

多个串前后缀匹配，于是想到可以用字典树维护，想到对于前缀满足条件的串在字典树中一定是一颗子树，即一定是 dfs 序中连续的一段，所以可以考虑把询问离线下来，对于每个后缀，将其在前缀 dfs 序上做区间修改，然后按照深度优先搜索的顺序遍历，则对于一个询问，遍历子树后前缀子树中标记个数和遍历前的差即为这个询问的答案。

然后实现就是字典树和树状数组（也可以用线段树）即可，时间复杂度是 $\mathcal O(M \log N)$。

### code

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define lowbit(x) (x&-x)

using namespace std;

const int N = 4e6 + 5;
int n, q, ch[3][N][30], len[3], beg[N], lst[N], dfsid, a[N], out[N], t[N];
struct node{
	int id, ls, rs;
};
string s;
vector <int> ed[3][N];
vector <node> ans[N];

void update(int x){while(x <= n){t[x]++, x += lowbit(x);}}
int query(int x)
{
	int res = 0;
	while(x > 0)
	{
		res += t[x];
		x -= lowbit(x);
	}
	return res;
}

void dfs(int x)
{
	beg[x] = dfsid;
	for(int i = 0;i < ed[1][x].size();i++)	a[ed[1][x][i]] = ++dfsid;
	for(int i = 0;i < 26;i++)
		if(ch[1][x][i])	dfs(ch[1][x][i]);
	lst[x] = dfsid;
}

void add(string s, int id, int xth)
{
	int now = 0;
	for(int i = 1;i < s.size();i++)
	{
		if(!ch[xth][now][s[i]-'A'])	ch[xth][now][s[i]-'A'] = ++len[xth];
		now = ch[xth][now][s[i]-'A'];
	}
	ed[xth][now].push_back(id);
}
int get(string s, int xth)
{
	int now = 0;
	for(int i = 1;i < s.size();i++)
	{
		if(!ch[xth][now][s[i]-'A'])	return -1;
		now = ch[xth][now][s[i]-'A'];
	}
	return now;
}

void solve(int x)
{
	for(int i = 0;i < ans[x].size();i++)
		out[ans[x][i].id] -= query(ans[x][i].rs) - query(ans[x][i].ls);
	for(int i = 0;i < ed[2][x].size();i++)	update(a[ed[2][x][i]]);
	for(int i = 0;i < 26;i++)
		if(ch[2][x][i])	solve(ch[2][x][i]); 
	for(int i = 0;i < ans[x].size();i++)	//算delta 
		out[ans[x][i].id] += query(ans[x][i].rs) - query(ans[x][i].ls);
}

int main()
{
	scanf("%d %d", &n, &q);
	for(int i = 1;i <= n;i++)
	{
		cin >> s;s = "#" + s;
		add(s, i, 1);
		for(int j = 1;j + j < s.size();j++)	swap(s[j], s[s.size()-j]);
		add(s, i, 2);
	}
	dfs(0);
	for(int i = 1;i <= q;i++)
	{
		cin >> s;s = "#" + s;
		int val = get(s, 1);
        cin >> s;s = "#" + s;
		for(int j = 1;j + j < s.size();j++)	swap(s[j], s[s.size()-j]);
		if(val != -1 && get(s, 2) != -1)
			ans[get(s, 2)].push_back((node){i, beg[val], lst[val]});
	}
	solve(0);
	for(int i = 1;i <= q;i++)
		printf("%d\n", out[i]);
	return 0;
}
```

---

## 作者：lfxxx (赞：2)

来一份线性时间的题解。

考虑先解决前缀限制，显然可以直接把字符串和询问全部搬到 Trie 树上，问题就变成了查询一个子树内满足后缀限制的字符串数量。

接着考虑 Trie 树合并，具体地，把后缀限制以及字符串挂在单词节点上，接着遍历整个 Trie 每到一个节点就把这个节点的儿子的所有 Trie 树合并并将这个节点挂着的字符串插入，随后回答询问，当然这个 Trie 树要从末位插入解决后缀限制。

由于每进行一次合并操作就会减少一个 Trie 上的节点又因为节点数量是 $O(\sum |S_i| + |P_i| + |Q_i|)$ 的所以复杂度就是线性的。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e6 + 114;
struct Big_Trie {
    char c;
    int ch[4];//A G U C
} tr1[maxn];
int answer[maxn];
int tot1, rt1;
struct Small_Trie {
    char c;
    int ch[4];//A G U C
    int cnt;//单词节点数量
    int sz;
} tr2[maxn];
int tot2;
int rt2[maxn];
int merge(int a, int b) {
    if (a == 0 || b == 0)
        return a + b;

    tr2[a].ch[0] = merge(tr2[a].ch[0], tr2[b].ch[0]);
    tr2[a].ch[1] = merge(tr2[a].ch[1], tr2[b].ch[1]);
    tr2[a].ch[2] = merge(tr2[a].ch[2], tr2[b].ch[2]);
    tr2[a].ch[3] = merge(tr2[a].ch[3], tr2[b].ch[3]);
    tr2[a].cnt += tr2[b].cnt;
    tr2[a].sz = tr2[tr2[a].ch[0]].sz + tr2[tr2[a].ch[1]].sz + tr2[tr2[a].ch[2]].sz + tr2[tr2[a].ch[3]].sz +
                tr2[a].cnt;
    return a;
}
void insert(int &cur, string &s) {
    if (cur == 0)
        cur = ++tot2;

    if (s.size() == 0) {
        tr2[cur].cnt++;
        tr2[cur].sz = tr2[tr2[cur].ch[0]].sz + tr2[tr2[cur].ch[1]].sz + tr2[tr2[cur].ch[2]].sz +
                      tr2[tr2[cur].ch[3]].sz + tr2[cur].cnt;
        return ;
    } else if (s[s.size() - 1] == 'A')
        s.pop_back(), insert(tr2[cur].ch[0], s);
    else if (s[s.size() - 1] == 'G')
        s.pop_back(), insert(tr2[cur].ch[1], s);
    else if (s[s.size() - 1] == 'U')
        s.pop_back(), insert(tr2[cur].ch[2], s);
    else if (s[s.size() - 1] == 'C')
        s.pop_back(), insert(tr2[cur].ch[3], s);

    tr2[cur].sz = tr2[tr2[cur].ch[0]].sz + tr2[tr2[cur].ch[1]].sz + tr2[tr2[cur].ch[2]].sz +
                  tr2[tr2[cur].ch[3]].sz + tr2[cur].cnt;
}
int query(int cur, string &s) {
    if (cur == 0)
        return 0;
    else if (s.size() == 0) {
        return tr2[cur].sz;
    } else if (s[s.size() - 1] == 'A') {
        s.pop_back();
        return query(tr2[cur].ch[0], s);
    } else if (s[s.size() - 1] == 'G') {
        s.pop_back();
        return query(tr2[cur].ch[1], s);
    } else if (s[s.size() - 1] == 'U') {
        s.pop_back();
        return query(tr2[cur].ch[2], s);
    } else if (s[s.size() - 1] == 'C') {
        s.pop_back();
        return query(tr2[cur].ch[3], s);
    }

    return 0;
}
vector<string> str[maxn];
void Ins_str(int &cur, string &s, string &Suf) {
    if (cur == 0)
        cur = ++tot1;

    if (s.size() == 0) {
        str[cur].push_back(Suf);
        return ;
    } else if (s[s.size() - 1] == 'A')
        s.pop_back(), Ins_str(tr1[cur].ch[0], s, Suf);
    else if (s[s.size() - 1] == 'G')
        s.pop_back(), Ins_str(tr1[cur].ch[1], s, Suf);
    else if (s[s.size() - 1] == 'U')
        s.pop_back(), Ins_str(tr1[cur].ch[2], s, Suf);
    else if (s[s.size() - 1] == 'C')
        s.pop_back(), Ins_str(tr1[cur].ch[3], s, Suf);
}
vector< pair<string, int>> Q[maxn];
void Ins_ask(int &cur, string &s, string &Suf, int id) {
    if (cur == 0)
        cur = ++tot1;

    if (s.size() == 0) {
        Q[cur].push_back(make_pair(Suf, id));
        return ;
    } else if (s[s.size() - 1] == 'A')
        s.pop_back(), Ins_ask(tr1[cur].ch[0], s, Suf, id);
    else if (s[s.size() - 1] == 'G')
        s.pop_back(), Ins_ask(tr1[cur].ch[1], s, Suf, id);
    else if (s[s.size() - 1] == 'U')
        s.pop_back(), Ins_ask(tr1[cur].ch[2], s, Suf, id);
    else if (s[s.size() - 1] == 'C')
        s.pop_back(), Ins_ask(tr1[cur].ch[3], s, Suf, id);
}
void dfs(int cur) {
    if (cur == 0)
        return ;

    dfs(tr1[cur].ch[0]), rt2[cur] = merge(rt2[cur], rt2[tr1[cur].ch[0]]);
    dfs(tr1[cur].ch[1]), rt2[cur] = merge(rt2[cur], rt2[tr1[cur].ch[1]]);
    dfs(tr1[cur].ch[2]), rt2[cur] = merge(rt2[cur], rt2[tr1[cur].ch[2]]);
    dfs(tr1[cur].ch[3]), rt2[cur] = merge(rt2[cur], rt2[tr1[cur].ch[3]]);

    for (string now : str[cur]) {
        insert(rt2[cur], now);
    }

    for (pair<string, int> now : Q[cur]) {
        answer[now.second] = query(rt2[cur], now.first);
    }
}
int n, m;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        string s, rs;
        cin >> s;

        for (int i = s.size() - 1; i >= 0; i--)
            rs.push_back(s[i]);

        Ins_str(rt1, rs, s);
    }

    for (int i = 1; i <= m; i++) {
        string p, q, rp;
        cin >> p >> q;

        for (int i = p.size() - 1; i >= 0; i--)
            rp.push_back(p[i]);

        Ins_ask(rt1, rp, q, i);
    }

    dfs(rt1);

    for (int i = 1; i <= m; i++)
        cout << answer[i] << '\n';
}
```



---

## 作者：tanghg (赞：1)

考虑离线。

之后把基因库的字符串按字典序排序，然后显然一段相同前缀的字符串会连续出现。那我们就可以求出第 $i$ 个询问所在排序后的基因库所对应的前缀区间 $[l_i,r_i]$，那我们只需要考虑在这个区间内有多少个后缀是询问的就行了。通常这种套路考虑可持久化数据结构。

按顺序将每个元素翻转之后加进可持久化字典树中，之后只要查询版本在 $[l_i,r_i]$ 范围内的后缀元素数量即可。
```cpp
#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
const ll MAXN=1e6+5;
string s[MAXN];
map<string,ll>l,r;
set<string>sl,sr;
ll n,m;
struct query{
    string f,b;
}q[MAXN];
ll ans[MAXN];
ll trie[MAXN*4][26],tot;
ll sum[MAXN*4],rt[MAXN*4];
void insert(ll &u,string s){
    ++tot;
    for(int i='A';i<='Z';++i){
        trie[tot][i-'A']=trie[u][i-'A'];
    }
    sum[tot]=sum[u]+1;
    u=tot;
    ll v=u;
    for(int i=0;i<s.size();++i){
        ll x=s[i]-'A';
        ++tot;
        ll on=trie[v][x];
        for(int j=0;j<26;++j){
            trie[tot][j]=trie[on][j];
        }
        sum[tot]=sum[on]+1;//可持久化字典树，求每个后缀的经过次数。
        trie[v][x]=tot;
        v=trie[v][x];
    }
}
ll query(ll lu,ll ru,string s){
    for(int i=0;i<s.size();++i){
        ll c=s[i]-'A';
        lu=trie[lu][c];
        ru=trie[ru][c];
    }
    return sum[ru]-sum[lu];
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>s[i];
    }
    sort(s+1,s+n+1);
    for(int i=1;i<=m;++i){
        cin>>q[i].f>>q[i].b;
        reverse(q[i].b.begin(),q[i].b.end());
        sl.insert(q[i].f);
    }
    for(ll i=1;i<=n;++i){
        string val;
        if(sl.count(val)){
            if(!l.count(val)){
                l[val]=i;
            }
            r[val]=i;
        }
        for(int j=0;j<s[i].size();++j){
            val+=s[i][j];   
            if(sl.count(val)){
                if(!l.count(val)){
                    l[val]=i;
                }
                r[val]=i;
            }
        }
        reverse(s[i].begin(),s[i].end());
        rt[i]=rt[i-1];
        insert(rt[i],s[i]);
    }
    for(int i=1;i<=m;++i){
        if(r[q[i].f]==0){
            cout<<0<<endl;
            continue;
        }
        cout<<query(rt[l[q[i].f]-1],rt[r[q[i].f]],q[i].b)<<endl;//版本区间内的后缀数量
    }
    return 0;
}
```

---

## 作者：galfth (赞：1)

~~在找莫队题写，结果居然没纯正莫队题解，特来写一发。~~

这道题可以将询问字符串前后缀转化成区间查询问题，想到此思路有很大部分是受此题启发： [P5268 [SNOI2017] 一个简单的询问](https://www.luogu.com.cn/problem/P5268)。

有兴趣的可以试着去尝试一下这道前置题。

## 处理方式
题面要求寻找每一次询问，前后缀能匹配上的那些字符串。

可以想到字符串可以按字典序排序的性质。对一个字符串序列 $S$ 按字典序排序后，符合前缀要求的那些字符串会形成一段连续的区间。

此时序列满足单调性，此时我们就可以二分找到符合要求的字符串的左右端点，举个例子：
找前缀为 'AB' 的字符串（此时已排好序）。

| pre | AB |
| :-----------: | :----------- |
| 1 | AA |
| 2 | AB |
| 3 | ABC |
| 4 | ACB |

满足前缀的字符串区间是 $[1,2]$。

- 如何寻找左端点？

按照上面序列，$S_1=$'AA'$<$'AB' 但从 $S_2=$ 'AB' 开始往右都大于等于前缀 'AB' 满足单调性。

(若前缀为字符串 $pre$)

所以遇到大于等于 $pre$ 的字符串就向左二分，否则向右。

- 如何寻找右端点？

同理，遇到小于 $pre$ 和前缀正好为 $pre$ 的字符串就向右二分，大于 $pre$ 向左二分就行。


 **至于后缀完全可以将字符串和后缀反转,然后后缀按照前缀的方法求就行。** 


------------

然后我们对于每一组询问会获得两个区间：$[l_1,r_1],[l_2,r_2]$。

**要注意，可能不会有能匹配上前缀或后缀的字符串，对这组询问要特殊处理，输出为0**

同时我们还要记录字符串原本输入时的编号，并且跟着字符串一起排序获得数组 $p_1,p_2$。$p_1[i]$ 表示排序过后的字符串 $s_i$ 原本的编号。$p_2[i]$ 表示排序过后的反转字符串 $s_i'$ 原本的编号。

然后这道题就变成了：求 $p_1$ 的 $[l_1,r_1]$ 和 $p_2$ 的 $[l_2,r_2]$ 中，有多少个值相同。

然后我们就可以请出莫队了。

## 莫队做法

莫队不适合同时维护两个区间，所以我们可以再转化一下问题。

我们定义 $v[n,m]$ 为 $p_1$ 的 $[1,n]$ 和 $p_2$ 的 $[1,m]$ 中，有多少个值相同。

那么答案就是
$$
	v[r_1,r_2]-v[l_1-1,r_2]-v[r_1,l_2-1]+v[l_1-1,l_2-1]
$$

将这四个值分开求，就可以进行正常的莫队维护了。

# Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
string a[N],b[N];
int p1[N],p2[N];
struct Que
{
	int l1,r1,l2,r2;
}Q[N];int cnt=0;
bool cmp(int x,int y){return a[x]<a[y];}
bool cmp1(int x,int y){return b[x]<b[y];}
int l1,r1,l2,r2;
int n,m;
void find(string pre,string suf)
{
	int l=1,r=n;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(a[mid]>=pre)
			l1=mid,r=mid-1;
		else
			l=mid+1;
	}
	l=1,r=n;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(a[mid]<pre||a[mid].substr(0,pre.size())==pre)
			r1=mid,l=mid+1;
		else
			r=mid-1;
	}
	l=1,r=n;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(b[mid]>=suf)
			l2=mid,r=mid-1;
		else
			l=mid+1;
	}
	l=1,r=n;
	while(l<=r)
	{
		int mid=l+r>>1;
		if(b[mid]<suf||b[mid].substr(0,suf.size())==suf)
			r2=mid,l=mid+1;
		else
			r=mid-1;
	}
}
namespace galfth
{
	const int maxn = 1e6+ 5;
	int n, blo, m, a[maxn], cnt1[maxn],cnt2[maxn], ans[maxn], res;
	int b[maxn]; 
	int p1[maxn],p2[maxn];
	struct Query {
		int id,flag, l, r;
		
		bool operator < (const Query &b) const {
			if (l / blo != b.l / blo)
				return l < b.l; 
			return l / blo % 2 ? r < b.r : r > b.r;
		}
		
	} query[maxn];
	void add(int op,int x)
	{
		if(!op)
		{
			cnt1[x]++;
			if(cnt2[x])res++;
		}
		else
		{
			cnt2[x]++;
			if(cnt1[x])res++;
		}
	}
	void del(int op,int x)
	{
		if(!op)
		{
			cnt1[x]--;
			if(cnt2[x])res--;
		}
		else
		{
			cnt2[x]--;
			if(cnt1[x])res--;
		}
	}
	void main(int _n,int _m,Que Q[],int _p1[],int _p2[])
	{
		n=_n,m=_m;
		blo=sqrt(n);
		for(int i=1;i<=n;i++)
			p1[i]=_p1[i],p2[i]=_p2[i];
		for(int i=0;i<4*m;i+=4)
		{
			
			int l1=Q[i/4].l1,r1=Q[i/4].r1,l2=Q[i/4].l2,r2=Q[i/4].r2;
			query[i]={i/4,0,r1,r2};
			query[i+1]={i/4,1,l1-1,r2};
			query[i+2]={i/4,2,l1-1,l2-1};
			query[i+3]={i/4,3,r1,l2-1};
		}
		sort(query,query+4*m);
		for (int i=0,l=0,r=0;i<m*4;i++)
		{
			while(l<query[i].l)l++,add(0,p1[l]);
			while(l>query[i].l)del(0,p1[l]),l--;
			while(r<query[i].r)r++,add(1,p2[r]);
			while(r>query[i].r)del(1,p2[r]),r--;
			if(query[i].flag%2)
				ans[query[i].id]-=res;
			else
				ans[query[i].id]+=res;
		}
		for(int i=0;i<m;i++)
			if(ans[i]==-1)//找不到有时候答案会是-1，应该和主函数Q设的初始值有关
				cout<<0<<endl;
			else
				cout<<ans[i]<<endl;
	}
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		b[i]=a[i];
		reverse(begin(b[i]),end(b[i]));
		p1[i]=i,p2[i]=i;
	}
	//转化部分
	sort(p1+1,p1+n+1,cmp);
	sort(p2+1,p2+n+1,cmp1);
	sort(a+1,a+n+1);
	sort(b+1,b+n+1);

	for(int i=0;i<m;i++)
	{
		string pre,suf;
		cin>>pre>>suf;
		reverse(begin(suf),end(suf));
		find(pre,suf);
		if(a[l1].substr(0,pre.size())!=pre||a[r1].substr(0,pre.size())!=pre||b[l2].substr(0,suf.size())!=suf||b[r2].substr(0,suf.size())!=suf)//特判找不到的情况
			Q[i]={0,0,0,0};
		else
			Q[i]={l1,r1,l2,r2};//形成符合莫队问题的区间
	}
	galfth::main(n,m,Q,p1,p2);//调用莫队
	return 0;
}
```

---

