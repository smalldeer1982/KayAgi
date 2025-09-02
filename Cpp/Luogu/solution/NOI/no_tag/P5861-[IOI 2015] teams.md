# [IOI 2015] teams

## 题目描述

班里有 $N$ 个学生,他们的编号为从 $0$ 到 $N-1$。每天，老师都有一些项目需要学生去完成。每个项目都需要由一组学生在一天内完成。项目的难度可能不同。对于每个项目，老师知道应该选择由多少学生组成的小组去完成。

不同的学生对小组的规模有不同的喜好。更准确地说, 对学生 $i$ 而言, 他只愿意在小组规模介于 $A[i]$ 和 $B[i]$ 之间（含 $A[i]$ 和 $B[i]$）的小组工作。每一天，一个学生最多只能被分配到一个小组工作。有些学生可能未被分配到任何小组中。每个小组只负责一个项目。

老师已选择好接下来 $Q$ 天中每一天的项目。对于每一天, 现需要判断是否有一种分配学生的方案，使得每个项目都有一个小组负责。

## 说明/提示

对于 $100\%$ 的数据，$1\le N\le 5 \times 10^5$，$1\le Q\le 2 \times 10^5$， $\sum M \leq 2\times 10^5$。

## 样例 #1

### 输入

```
4
2 4
1 2
2 3
2 3
2
2 1 3
2 1 1
```

### 输出

```
1
0
```

# 题解

## 作者：max67 (赞：5)

## 前言

题解写到一半时突然 wmh 跑过来把我题解删了。
阿巴阿巴阿巴......

## 题解

### 思路

（pass：用 [i] 表示引理 $i$，找不到的用 ```ctrl+f```。）

我们把题目中的 $A_i$ 记为 $L_i$，$B_i$ 记为 $R_i$，并把 $k_i$ 从小到大排序。

首先考虑一个基础的贪心：对于一次询问中的 $k_i$，我们在所有剩余的满足条件的数（$L_i \le k_i \le R_i$）中贪心按 $R_i$ 从小到大取，证明如下：

> 对于两个数 $i$ 和 $j$（$L_i,L_j\le k_i$，$R_i\le R_j$）来说，对于 $\forall l \in (i,n]$ 来说，都有 $L_i,L_j \le k_i \le k_l$，即这两个数在考虑 $k_l$ 的贡献时只需要考虑 $R$ 的限制。那么显然是把 $R$ 大的留在后面更优。

但暴力模拟贪心会炸（$O(n\times q)$）。因为 $q$ 的原因，因此下面的算法中不能用 $i$ 去更新 $k_j$，而要以 $k_j$ 去找满足条件的剩余的 $i$。

观察贪心过程，我们会发现他有一个优美的性质：只有一次操作时，对于所有满足的 $L_i\le k_1$ 的数按 $R_i$ 排序时，没被取过的数（也满足 $L_i\le k_1$）的集合一定满足他是一个从（排序的集合的）右端点开始的区间。这个容易在贪心的过程中证明。

由于这个优美的性质，若有第二次操作时，我们只需要考虑两个部分 

* 1. 左端点满足 $k_1<L_i\le k_2$ 的数，他们都没有被取过。我们可以贪心取。

* 2. （[1]）左端点满足 $L_i\le k_1$ 的部分，设 $h$ 为没被取过的数中最小的右端点。若满足 $h\le k_2$，说明我们可以按第一个部分的方案取，而不会取到合法的方案，因为 $\forall R_i\ge h,L_i\le k_1$ 都没被取过，且 $h\le k_2$，即 $\forall R_i\ge k_2,L_i\le k_1$ 也没有被取过 ；若 $h>k_2$，则我们可以统计所有没被取过的数，他们都能对 $k_2$ 造成贡献。

知道了能取的数的集合，那么我们就要讨论剩下的数（考虑 $h_1> k_i$ 的情况，显然个数固定）。直接的话这样算的：

[![q28NPf.png](https://s1.ax1x.com/2022/03/30/q28NPf.png)](https://imgtu.com/i/q28NPf)

（红线标的部分为 $h_1=R_i$）

那么就是先从下到上取到第二个集合直到红线部分，再按 $R_i$ 依次从小到大取。BUT，我们发现了一个事情——当我们没有取到红线部分时，对于 $L_i\le k_2$ 的数按 $R_i$ 从小到大排序时，剩下的数的集合不一定在上面连续。但是取过红线以后又满足了上面说的性质。

转化一下判断方法，即当我们剩余的数的名额从前往后贪心的取，（就相当于贪心地从后往前取对 $k_2$ 能造成贡献的数）。设此时 $h_2$ 为此时满足 $k_1< L_i\le k_2$ 的剩余的数中 $R_i$ 的最小值。那么若 $h_2\ge h_1$ ，则能取到红线部分，否则取不到。

基此，我们发现了一个妙妙的方法：（[2]）若按上面的判断方法能越过红线的话，$L_i\le k_1$ 和 $k_1\le L_i \le k_2$ 的剩余部分与 $L_i \le k_2$ 的部分贪心按 $R_i$ 从大到小取所得的剩余部分等同。否则不相等。（[3]）当不相等的时候，总体贪心取的方案恰好等同于对 $k_1<L_i\le k_2$ 中贪心取剩余的数的方案——总结，都可以贪心取。

因此，若我们按照上面的方法合并的话，我们发现每个区间剩余的数的右端点的最小高度单调递减。

### 实现

我们睿智地看了一眼，发现这和单调栈非常像。因此我们用单调栈进行操作：

（若单调栈中没有数，默认为 $0$。）

* 记 $hater_i$（夹带私货.jpg） 表示元素 $i$ 与单调栈上一个元素（记为 $j$）中满足 $k_j<L_i\le k_i$ 中剩余的数的 $R_i$ 的最小值。记 $s_i$ 表示满足 $k_1......k_i$ 后的剩余的数的数量。单调栈从大到小维护 $i$

* 对于一个新的元素 $i$ 来说，我们找到单调栈中满足 $hater_i$ 大于 $i$的第一个数（[1]）记为 $j$（由于栈中元素的最小高度大于等于 $j$ 的，所以都可以这样计算），然后用数据结构求解在满足 $k_j\le L_l\le k_i,R_l\ge k_i$ 的数量。判断是否有 $k$ 个数（$s_i+$ 个数 $\ge$ $k_i$，记为 $sum$）。


* 然后对于栈中的每个元素（设为 $j$），我们记录 $h$ 表示在从前往后贪心的取中，在满足 $k_j<L_l\le k_i$ 数中剩余的数的 $R_l$ 的最小值。若 $h>hater[i]$，则弹出栈中的元素（[2]）。


* $s_i=sum$，$hater[i]=h$（[3]），并把 $i$ 加入到栈中。

容易发现，上面所说的数据结构就是主席树，可以满足：

* 求 $k_j<L_l\le k_i$，$R_l\ge k_i$ 的数量。

* 求出  $k_j<L_l\le k_i$ 中，$R_i$ 从大到小排序的第 $k$ 位。

注意，由于可能没有数可取，这时定义 $hater_i=n+1$。

由于数据范围很小，所以不用离散化。


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define pb push_back
using namespace std;
const int N=1e7+1e3;
struct Segment_Tree
{
    int tot;
    int rt[N],ls[N],rs[N];
    int val[N];
    #define midd ((l+r)>>1)
    int New(){return ++tot;}
    void insert(int &x,int y,int l,int r,int p)
    {
        x=New();val[x]=val[y]+1; 
        ls[x]=ls[y];rs[x]=rs[y];
        if(l==r)return;
        int mid=midd;
        if(p<=mid)insert(ls[x],ls[y],l,mid,p);
        else insert(rs[x],rs[y],mid+1,r,p);
    }
    int qpos(int x,int y,int l,int r,int k)
    // 求出从大到小的第 i 位的 值
    {
        if(l==r)return l;
        int t=val[rs[x]]-val[rs[y]],mid=midd;
        if(t>=k)return qpos(rs[x],rs[y],mid+1,r,k);
        return qpos(ls[x],ls[y],l,mid,k-t);
    }
    int query(int x,int y,int l,int r,int p)
    //求出大于等于 p 的数量
    {
        if(!x)return 0;
        if(l==r)return val[x]-val[y];
        int mid=midd;
        if(p<=mid)return query(ls[x],ls[y],l,mid,p)+val[rs[x]]-val[rs[y]];
        return query(rs[x],rs[y],mid+1,r,p);
    }
    #undef midd
}T;
int n,m;
int k[N];
pii a[N];
stack<int>st;
int hater[N],s[N];
void work()
{
    stack<int>st;while(!st.empty())st.pop();
    for(int i=1;i<=m;i++)
    {
        while(!st.empty()&&hater[st.top()]<k[i])st.pop();
        int pre=(st.empty()?0:st.top());
        int sum=s[pre]+T.query(T.rt[k[i]],T.rt[k[pre]],1,n+1,k[i])-k[i];
        if(sum<0)return puts("0"),void();
        int h=T.qpos(T.rt[k[i]],T.rt[k[pre]],1,n+1,sum-s[pre]);
        while(!st.empty()&&h>=hater[st.top()])
        {
            st.pop();pre=(st.empty()?0:st.top());
            h=T.qpos(T.rt[k[i]],T.rt[k[pre]],1,n+1,sum-s[pre]);
        }
        st.push(i);hater[i]=h;s[i]=sum;
    }
    puts("1");
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+n+1);
    for(int i=1,j=1;i<=n+1;i++)
    //注意 n+1
    {
        T.rt[i]=T.rt[i-1];
        while(j<=n&&a[j].fi==i)T.insert(T.rt[i],T.rt[i],1,n+1,a[j].se),j++;
    }
    int _;scanf("%d",&_);
    while(_--)
    {
        scanf("%d",&m);
        for(int i=1;i<=m;i++)scanf("%d",&k[i]);
        sort(k+1,k+m+1);
        work();
    }
    return 0;
}
```

## 后记

这题希望评个黑（这样我就有黑题题解了）。

感谢人 win [legendgod 大佬](https://www.luogu.com.cn/user/151723) 的[指导](https://legendgod.ml/) 。

[![q2DKRs.png](https://s1.ax1x.com/2022/03/30/q2DKRs.png)](https://imgtu.com/i/q2DKRs)[![q2riY4.png](https://s1.ax1x.com/2022/03/30/q2riY4.png)](https://imgtu.com/i/q2riY4)
[![q2rAp9.png](https://s1.ax1x.com/2022/03/30/q2rAp9.png)](https://imgtu.com/i/q2rAp9)




---

## 作者：yaoxi (赞：5)

[不知道会不会更好的阅读体验](https://yaoxi-std.github.io/2022/03/28/sol-p5861/)

**这是一个 $O(N \log N + S \log^2 N)$ 的方法**，可能需要卡卡常才能过。**不需要主席树**~~只需要线段树套 vector 再进行一堆奇怪的操作~~

容易想到贪心思路：先将 $K[i]$ 从小到大排序，每次取 $B[j]$ 最小的 $K[i]$ 个，这样显然是最优的。

所以可以对于每个学生，在线段树的 $B[i]$ 处插入一个数 $A[i]$。在处理 $K[i]$ 时，在线段树上二分出最小的 $r$ 使得有 $\ge K$ 个 $A[i] \le K \le B[i] \le r$，然后将对应的 $K$ 个学生删除。

思路很简单，下面是实现。因为在询问过程中不需要对学生进行修改，所以就可以在预处理阶段就构建出这个线段树套 vector 并排好序。

考虑如何在线段树上二分，这个很套路，首先由于 $K[i]$ 递增，所以 $B[i] < K$ 的已经没有用了，全部删去。然后就考虑的是一个最小的前缀 $r$ 使有 $\ge K$ 个 $A[i] \le K$ 并且 $B[i] \le R$，直接普通的线段树二分即可。由于还需要在 vector 上再次二分，所以一次操作为 $O(\log^2 N)$。

然后考虑删除，显然对于线段树上每个节点，删除掉的都是 vector 中的一段前缀，于是想到对每个节点维护一个 $pos$ 表示已经删掉了前 $pos$ 个，这样就可以对每个节点快速删除了，只需要在线段树上找到对应的区间并更新 $pos$ 就行。

最后在做完一次询问需要清空。显然清空就是将所有的 $pos$ 赋成 $0$，维护一个是否清空的标记 $cls$ 并 pushdown 即可。

upd: 我知道之前为什么要 pushdown 两次了，因为有可能修改一次以后 $cls$ 标记还存在。代码已经修改过了，可以放心食用。

### 代码

```cpp
bool m_be;
using ll = long long;
const int MAXN = 5e5 + 10;
const int INF = 0x3f3f3f3f;
struct SegmentTree {
    #define li (i << 1)
    #define ri (i << 1 | 1)
    #define lson li, l, mid
    #define rson ri, mid + 1, r
    int pos[MAXN * 4];           // 已经删掉几个数了
    bool cls[MAXN * 4];          // 是否要清空的标记
    vector<int> vec[MAXN * 4];   // 对应 vector
    // 为了排序
    void build(int i, int l, int r) {
        pos[i] = 0;
        sort(vec[i].begin(), vec[i].end());
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(lson), build(rson);
    }
    // 插入，全部的插入操作结束后需要 build 来排序
    void insert(int i, int l, int r, int q, int v) {
        vec[i].emplace_back(v);
        if (l == r) return;
        int mid = (l + r) >> 1;
        q <= mid ? insert(lson, q, v) : insert(rson, q, v);
    }
    // 节点 i 中未被删除的 <=p 的数字数量
    int count(int i, int p) {
        return upper_bound(vec[i].begin(), vec[i].end(), p) - vec[i].begin() - pos[i];
    }
    // 下传标记
    void pushdown(int i) {
        // 如果需要清空就直接清空
        if (cls[i]) cls[i] = 0, cls[li] = cls[ri] = 1, pos[li] = pos[ri] = 0;
        // 不需要下传
        if (pos[i] == pos[li] + pos[ri]) return;
        // 由于删掉的一定是前 pos[i] 个，所以儿子节点中小于 vec[i][pos[i]-1] 
        // 的一定已经要被删掉，剩下的等于 vec[i][pos[i]-1] 的就优先删除 B[i] 
        // 更小的也就是左儿子中的。
        int x = vec[i][pos[i] - 1];
        pos[li] += count(li, x - 1), pos[ri] += count(ri, x - 1);
        int p = pos[i] - pos[li] - pos[ri], t = count(li, x);
        (p <= t) ? (pos[li] += p) : (pos[li] += t, pos[ri] += p - t);
    }
    // 查询 B[i] 在区间 [ql,qr] 的学生中还有多少个 A[i]<=p 的
    int query(int i, int l, int r, int ql, int qr, int p) {
        if (ql > qr) return 0;
        if (ql <= l && r <= qr) return count(i, p);
        int mid = (l + r) >> 1, ret = 0; pushdown(i);
        if (ql <= mid) ret += query(lson, ql, qr, p);
        if (qr > mid) ret += query(rson, ql, qr, p);
        return ret;
    }
    // 二分出最小的 R 使得有 >=k 个 A[i]<=p 且 B[i]<=R
    // 这里是把 二分 和 删除 放到一个函数里了，应该看得懂吧
    int bound(int i, int l, int r, int p, int k) {
        if (l == r) return pos[i] += k, l;
        int mid = (l + r) >> 1; pushdown(i);
        int tmp = count(li, p), ret;
        if (k <= tmp) ret = bound(lson, p, k);
        else pos[li] += tmp, ret = bound(rson, p, k - tmp);
        return pos[i] = pos[li] + pos[ri], ret;
    }
} sgt;
int n, q, m, a[MAXN], b[MAXN], k[MAXN];
bool m_ed;
signed main() {
    resetIO(teams);
    // debug("Mem %.5lfMB.", fabs(&m_ed - &m_be) / 1048576);
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]), read(b[i]);
    for (int i = 1; i <= n; ++i)
        sgt.insert(1, 1, n, b[i], a[i]);
    sgt.build(1, 1, n);
    read(q);
    while (q--) {
        bool ans = 1; ll sum = 0; read(m);
        for (int i = 1; i <= m; ++i) read(k[i]), sum += k[i];
        if (sum > n) { putc('0'), putc('\n'); continue; }
        sort(k + 1, k + m + 1);
        sgt.cls[1] = 1, sgt.pos[1] = 0; // 记得打上清空的标记
        for (int i = 1; i <= m; ++i) {
            // B[i] < K[i] 的不再有用，可以直接删掉
            int rem = k[i] + sgt.query(1, 1, n, 1, k[i] - 1, k[i]);
            if (sgt.count(1, k[i]) < rem) { ans = 0; break; }
            sgt.bound(1, 1, n, k[i], rem);
        }
        putc(ans ? '1' : '0'), putc('\n');
    }
    return print_final(), 0;
}
```

---

## 作者：myee (赞：4)

### 前言

不会正解，所以写了个根号做法。

### 思路

先考虑 $q=1$ 怎么做。

我们考虑贪心，从小到大扫描线，遇上左边界就插入有边界的小根堆，遇上需求就弹出对应个数的堆顶元素，遇上右边界就弹出堆顶元素（如果存在的话）。

当某个需求无法解决时直接无解，否则必然有解。

考虑 $q>1$ 的情况。

我们考虑求出覆盖一段区间的需求的人的数目是多少。这样每次本质不同的人只有 $O(\min(m^2,n))$ 种。

直接主席树是 $O(m\sqrt n\log n)$ 的，不优。

考虑根号平衡，我们把人按左端点排序，每 $\sqrt n$ 个分一块，每个块内的人再按右端点逆序排序。记录每个位置对应多少个前 $k$ 个块内的人，查询时再额外统计散块的贡献。

这样我们就知道每段需求区间被多少个人完全覆盖，进一步通过容斥得到恰好覆盖。

这样就把人划分成了 $O(\min(m^2,n))$ 种。

然后暴力模拟前面的贪心，容易做到 $O(m\sqrt n)$。

总复杂度 $O((n+m)\sqrt n)$，空间 $O(n\sqrt n)$。

平衡复杂度时块长取 $3000$ 实际跑得很快。

由于洛谷上的版本来自 bzoj，允许离线，所以空间其实可以做到 $O(n)$。不过我懒，所以直接写了空间根号的做法。

### Code

代码很好写。

```cpp
const uint Block=3000,Lim=500000;
std::pair<uint,uint>P[Lim+5];
uint C[Lim/Block+5][Lim+5],F[Lim/Block+5];
uint W[1005][1005],n,c;
bol solve(std::vector<uint>S)
{
    std::vector<uint>A,B;
    std::sort(S.begin(),S.end());uint v=0;
    for(auto s:S)
    {
        if((v+=s)>n)return false;
        if(A.size()&&A.back()==s)B.back()+=A.back();else A.push_back(s),B.push_back(s);
    }
    for(uint i=0,p,r;i<A.size();i++)
    {
        p=0;while(p+1<c&&F[p+1]<=A[i])p++;
        r=std::min((p+1)*Block,n);
        for(uint j=A.size()-1,k=p*Block,c=0;j>=i&&~j;j--)
        {
            while(k<r&&P[k].second>=A[j])c+=P[k++].first<=A[i];
            W[i][j]=c+C[p][A[j]];
        }
    }
    for(uint i=0;i<A.size();i++)for(uint j=0;i+j<A.size();j++)
    {
        if(j)W[j][i+j]-=W[j-1][i+j];
        if(i+j+1<A.size())W[j][i+j]-=W[j][i+j+1];
        if(j&&i+j+1<A.size())W[j][i+j]+=W[j-1][i+j+1];
    }
    for(uint i=0;i<A.size();i++)
    {
        for(uint j=i;j<A.size();j++)if(B[i]>=W[i][j])B[i]-=W[i][j],W[i][j]=0;else W[i][j]-=B[i],B[i]=0;
        if(B[i])return false;
        for(uint j=i+1;j<A.size();j++)W[i+1][j]+=W[i][j];
    }
    return true;
}
int main()
{
    uint q;scanf("%u",&n);for(uint i=0;i<n;i++)scanf("%u%u",&P[i].first,&P[i].second);
    std::sort(P,P+n);
    for(uint j=0,r;j<n;j+=Block)
    {
        F[j/Block]=P[j].first;
        std::sort(P+j,P+(r=std::min(j+Block,n)),
            [&](std::pair<uint,uint>a,std::pair<uint,uint>b){return a.second>b.second;}),c++;
        for(uint k=0;k<r;k++)C[c][P[k].second]++;
        for(uint k=n;k;k--)C[c][k-1]+=C[c][k];
    }
    scanf("%u",&q);
    while(q--)
    {
        uint m;scanf("%u",&m);
        std::vector<uint>S(m);
        for(auto&v:S)scanf("%u",&v);
        puts(solve(S)?"1":"0");
    }
}
```





---

## 作者：MusicBox (赞：3)

原来题解写的过于抽象了，现在重构一下，其实重构后也很抽象，大家可以看一下这位大佬写的 [题解](https://www.luogu.com.cn/article/om4r85bg)。如果你想看我原来的抽象题解的话，也可以[点这里](https://www.luogu.com/paste/yqlojr7g)。

首先我们发现，我们可以将第 $i$ 个人需要在 $[l_i, r_i]$ 的小组中转化成，小组要取出恰好 $k$ 个人，满足 $l_j \leq k \leq r_j$，我们可以将 $(l_i, r_i)$ 放置于二维平面上，每次要从一个长方形内取出 $k$ 个点。



![](https://cdn.luogu.com.cn/upload/image_hosting/a1yw2oeh.png)

对于静态的二维数点问题，我们可以使用主席树完成。

显然，若 $m = 1$，我们可以直接做，由于每天询问之间独立，我们每天二维数点即可。

考虑 $m > 1$，我们将询问 $k_i$ 从小到达排序。

我们发现询问之间可能冲突，即，我在 $k_1$ 时选的点可能在 $k_2$ 查询时也能用上。

那么，我们肯定是每次贪心选择 $y$ 坐标较低的点。

我们假设对于每次询问后，保留如下内容：

$high, q$，分别表示我们此时对于 $x \leq k$ 剩下能选的的最低点，以及我们剩下能选的点的个数。

如果我们存在一段使得 $high_{i - 1} > high_i$，我们就将 $high_{i - 1}$ 设置为失效状态，这是显然的，因为我这次选择必然将 $high_{i - 1}$ 那个高度点用掉了。那么有效状态的 $high$ 显然是单调的。（如果这段看不大懂可以先看下面几个段，然后回来看）

我们不难发现 $high$ 一定是单调递减的，用单调栈维护。

我们发现如果我们此次查询的 $k > high_{last}$，那么上一次维护的 $q$ 就没必要存在了，设置为失效，我们一直倒退到 $k \leq high$，然后来查询剩下合法数量 $tot$，若 $tot < k$，显然无解，否则，我们尝试找到若干高度尽量低的点。

我们如何找到高度尽量低的点呢？我们发现栈是单调递减的，若我们用栈最后一部分的那个区间能获取出 $k$ 个点，且剩余点的最低位置 $H > high_{lst}$，那么显然，我们就用这些了，否则我们可以继续均摊，使得最低高度不用那么高，即我们将最后一段 $< high_{lst}$ 且合法的点拿出来，然后合并两段。

code:

```cpp
int n, T;
int a[L], b[L];
vector<int> e[L];
int k[L];

namespace segment_tree {
    #define mid (l + r >> 1)
    #define lson L, R, l, mid, tree[w].l
    #define rson L, R, mid + 1, r, tree[w].r
    int cnt = 0;
    const int L = 4e7 + 5;
    int root[L];
    struct node {
        int l, r, num;
    } tree[L];
    int clone(int w) {
        int nw = ++ cnt;
        tree[nw] = tree[w];
        return nw;
    }
    void pushup(int w) {
        tree[w].num = tree[tree[w].l].num + tree[tree[w].r].num;
    }
    int modify(int L, int R, int l, int r, int w, int num) {
        w = clone(w);
        if(L <= l && r <= R) { tree[w].num ++; return w; }
        if(R <= mid) tree[w].l = modify(lson, num);
        else if(mid < L) tree[w].r = modify(rson, num);
        else tree[w].l = modify(lson, num), tree[w].r = modify(rson, num);
        pushup(w);
        return w;
    }
    int query(int L, int R, int l, int r, int w) {
        if(L <= l && r <= R) return tree[w].num;
        if(R <= mid) return query(lson);
        else if(mid < L) return query(rson);
        else return query(lson) + query(rson);    
    }
    int build(int l, int r, int w) {
        if(l != r)
            tree[w].l = build(l, mid, ++ cnt), tree[w].r = build(mid + 1, r, ++ cnt), pushup(w);
        else
            tree[w].num = 0;
        return w;
    }
}

using segment_tree::build;
using segment_tree::root;
using segment_tree::modify;
using segment_tree::query;
using segment_tree::tree;

int QueryH(int L, int R, int l, int r, int num) {
    if(l == r) return l;
    if(num > tree[tree[R].r].num - tree[tree[L].r].num) return QueryH(tree[L].l, tree[R].l, l, (l + r >> 1), num - (tree[tree[R].r].num - tree[tree[L].r].num));
    else return QueryH(tree[L].r, tree[R].r, (l + r >> 1) + 1, r, num);
}

int s[L], q[L], high[L];

signed main() {
    n = read();
    rep(i, 1, n) {
        a[i] = read(), b[i] = read();
        e[a[i]].push_back(b[i]);
    }
    root[0] = build(1, n, 0);
    rep(i, 1, n) {
        root[i] = root[i - 1];
        for(auto d : e[i]) root[i] = modify(d, d, 1, n, root[i], 1);
    }
    T = read();
    while(T --) {
        int m = read();
        rep(i, 1, m) k[i] = read();
        sort(k + 1, k + 1 + m);
        int Top = 0;
        rep(i, 1, m) {
            while(high[Top] < k[i] && Top) Top --;
            int tot = query(k[i], n, 1, n, root[k[i]]) - query(k[i], n, 1, n, root[s[Top]]) + q[Top] - k[i];
            if(tot < 0) { 
                puts("0"); 
                goto leave; 
            }
            int H = QueryH(root[s[Top]], root[k[i]], 1, n, tot - q[Top]);
            while(high[Top] < H && Top) Top --, H = QueryH(root[s[Top]], root[k[i]], 1, n, tot - q[Top]);
            Top ++;
            s[Top] = k[i], q[Top] = tot, high[Top] = H;
        }
        puts("1");
        leave:;
    }
    return 0;
}
```

---

