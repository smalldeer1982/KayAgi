# 「OICon-02」maxiMINImax

## 题目描述

给出一个长度为 $n$ 的排列 $a$。定义一个子区间 $[l,r]$ 中 $a_i$ 的最小值为 $\min_{[l,r]}$，$a_i$ 的最大值为 $\max_{[l,r]}$。对于所有子区间三元组 $([l_1,r_1],[l_2,r_2],[l_3,r_3])$ 使得 $1\leq l_1\leq r_1<l_2\leq r_2<l_3\leq r_3\leq n$，求 $\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})$ 之和，对 $9712176$ 取模。

## 说明/提示

### 样例解释

对于样例 $1$：

* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,1],[2,2],[3,3])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=0$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,1],[2,2],[3,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=0$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,1],[2,2],[4,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=2$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,1],[2,3],[4,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=2$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,1],[3,3],[4,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=6$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([1,2],[3,3],[4,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=2$；
* $([l_1,r_1],[l_2,r_2],[l_3,r_3])=([2,2],[3,3],[4,4])$：$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})=2$。

所有 $([l_1,r_1],[l_2,r_2],[l_3,r_3])$ 的 $\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})$ 总和为 $0+0+2+2+6+2+2=14$。

### 数据范围

**本题采用捆绑测试。**

| $\text{Subtask}$ | 特殊性质 | $\text{Score}$ |
|:--:|:--:|:--:|
| $1$ | $n\leq60$ | $5$ |
| $2$ | $n\leq100$ | $9$ |
| $3$ | $n\leq200$ | $9$ |
| $4$ | $n\leq500$ | $9$ |
| $5$ | $n\leq2000$ | $19$ |
| $6$ | $n\leq6000$ | $11$ |
| $7$ | $n\leq10^5$ | $19$ |
| $8$ | 无特殊限制 | $19$ |

对于 $100\%$ 的数据：$1\leq n\leq10^6$，$1\leq a_i\leq n$，保证 $a$ 为 $\{1,2,\dots,n\}$ 的一个排列。

## 样例 #1

### 输入

```
4
1 3 4 2```

### 输出

```
14```

## 样例 #2

### 输入

```
10
1 3 6 2 7 9 4 10 8 5```

### 输出

```
1992```

# 题解

## 作者：Argon_Cube (赞：7)

首先看到三个区间肯定是枚举中间那个，然后看到 $\min/\max$ 就考虑做单调栈然后枚举区间的 $\min/\max$。

其次我们发现三个区间不交的条件是没用的，也就是说只要有两个区间有交集那么这种方案一定贡献为 $0$。证明很简单，我们发现如果 $r_1\geq l_2$ 也就是前两个区间有交，交集包含 $x$ 那么 $\min_2\leq x\leq \max_1$ 从而 $\min_2-\max_1\leq 0$。

现在我们只需要保证 $\min_2>\max(\max_1,\max_3)$，我们从小到大加入数并让当前加入的数为 $\min_2$。即可满足这个条件。容易用单调栈跑出每一个数 $a_i$ 作为区间 $\min/\max$ 时合法的区间数 $c_i/d_i$。于是此时包含 $\min_2$ 的贡献为 $\sum c_{\min_2}d_{\max_1}d_{\max_3}(\min_2-\max_1)(\min_2-\max_3)$，拆一下发现只需要知道容易用树状数组维护的 $\sum d_{\max_1}$、$\sum d_{\max_3}$、$\sum d_{\max_1}\max_1$、$\sum d_{\max_3}\max_3$ 即可快速计算。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <stack>
#include <array>

using namespace std;

stack<int,vector<int>> mnstk;
array<int,1000002> vals,ivals,bidt1,bidt2,bidt3,bidt4,rgln,rgrn,rglx,rgrx;
const int moder=9712176;

inline void update(int idx,long long val,int cnt,decltype(bidt1)& bidt)
{
    while(idx<=cnt)
        bidt[idx]=(bidt[idx]+val)%moder,idx+=-idx&idx;
}
inline int query(int idx,decltype(bidt1)& bidt)
{
    int result=0;
    while(idx)
        result=(result+bidt[idx])%moder,idx-=idx&-idx;
    return result;
}

int main(int argc,char* argv[],char* envp[])
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int cnt;
    cin>>cnt;
    for(int i=1;i<=cnt;i++)
        cin>>vals[i],ivals[vals[i]]=i;
    vals[0]=vals[cnt+1]=0;
    mnstk.push(0);
    for(int i=1;i<=cnt+1;i++)
    {
        while(vals[mnstk.top()]>vals[i])
            rgrn[mnstk.top()]=i,mnstk.pop();
        rgln[i]=mnstk.top();
        mnstk.push(i);
    }
    mnstk.pop();
    vals[0]=vals[cnt+1]=cnt+1;
    for(int i=1;i<=cnt+1;i++)
    {
        while(vals[mnstk.top()]<vals[i])
            rgrx[mnstk.top()]=i,mnstk.pop();
        rglx[i]=mnstk.top();
        mnstk.push(i);
    }
    int answer=0;
    for(int idx=1;idx<=cnt;idx++)
    {
        long long i=ivals[idx];
        long long cntn=(rgrn[i]-i+0ll)*(i-rgln[i])%moder,cntx=(rgrx[i]-i+0ll)*(i-rglx[i])%moder;
        long long a=query(i,bidt1),b=query(cnt-i+1,bidt2),c=query(i,bidt3),d=query(cnt-i+1,bidt4);
        answer=(answer+cntn*((c*d-idx*((a*d+b*c)%moder)%moder+moder+a*b%moder*idx%moder*idx)%moder))%moder;
        // cerr<<idx<<' '<<i<<' '<<cntn<<' '<<cntx<<' '<<answer<<'\n';
        update(i,cntx,cnt,bidt1),update(cnt-i+1,cntx,cnt,bidt2),update(i,cntx*idx,cnt,bidt3),update(cnt-i+1,cntx*idx,cnt,bidt4);
    }
    cout<<answer;
    return 0;
}
```

---

## 作者：XFlypig (赞：7)

### 说明：本题解中有部分借鉴此[博客](https://www.luogu.com.cn/blog/Unnamed-Cube/solution-p10173)

首先看到三个区间，第一反应枚举中间的区间。

至少 $O(n^2)$，再想到枚举每一个值，用做贡献的方法来统计答案。

现在条件稍显复杂，先推推结论简化条件。

## 1.这是个排列，所以不存在用区间内两个等值极值算了重复的该区间

这个能在一定程度上让我们的具体代码方便一点。

## 2.相交的区间是没有贡献的

证明很简单，如果有相交区间，如：$l_2 \le l_3 \le r_2 \le r_3$ 则：

$$\forall \ l_3 \le i \le r_2, 
\min_{[l_2, r_2]} \le a_i \le \max_{[l_3, r_3]}$$

所以此时对答案无贡献，这个结论的用处就是我们不用担心答案里多算了相交区间。

接下来，我们还需要满足的条件就是：

$$\min_{[l_2, r2]} \ge \max(\max_{[l1,r1]}, \max_{[l3,r3]})$$

这里有个常规技巧，就是把数从小到大放进去，并把当前的 $a_i$ 当作 $\min_{[l2,r2]}$，则满足当前数小于在这之前加入的所有数。

然后就是左边乘右边来计算答案了，这样我们枚举每个数作为第二个区间最小值即 $\min_{[l2,r2]}$，自然是不重不漏啦，具体做法是这样的：

预处理 $c_i, d_i$ 分别表示第 $i$ 个数作为区间最小值，最大值的区间数。

这里可以用单调栈做，预处理 $lmn,lmx,rmn,rmx$ 等数组表示 $i$ 左侧第一个比他小的数的位置，$i$ 左侧第一个比他大的数的位置等等，则：

```cpp
c[i] = (i - lmn[i]) * (rmn[i] - i);
d[i] = (i - lmx[i]) * (rmx[i] - i);
```

那么答案就很直接了：

$$\sum c_{min2}d_{max1}d_{max3}(min2-max1)(min2-max3)$$

此处 $max1,max3$ 看似要枚举，但我们拆开这个式子后，发现可以通过树状数组维护以下几个求和来快速计算答案：

$$\sum d_{max1},\sum d_{max3},\sum d_{max1}a_{max1},\sum d_{max3}a_{max3}$$

最后放一下代码啦，**别忘了及时取模**。

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

#define int long long

using namespace std;

const int N = 1000010, P = 9712176;

int n;
int w[N], p[N];
int stk[N];
int c[N], d[N];
int lmn[N], lmx[N], rmn[N], rmx[N];
class BIT {

private : 
    int tr[N];
    
    int lowbit(int x)
    {
        return x & -x;
    }
    
    int sum(int x)
    {
        int res = 0;
        for (int i = x; i; i -= lowbit(i)) res = (res + tr[i]) % P;
        return res;
    }

public : 
    void update(int x, int c)
    {
        for (int i = x; i <= n; i += lowbit(i)) tr[i] = (tr[i] + c) % P;
    }
    
    int query(int l, int r)
    {
        return (sum(r) - sum(l - 1) + P) % P;
    }
} b1, b2, b3, b4;

signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i ++ )
    {
        scanf("%lld", &w[i]);
        p[w[i]] = i;
    }
    
    int tt = 0;
    stk[ ++ tt] = 0;
    for (int i = 1; i <= n + 1; i ++ )
    {
        while (tt && w[stk[tt]] >= w[i]) rmn[stk[tt -- ]] = i;
        lmn[i] = stk[tt];
        stk[ ++ tt] = i;
    }
    
    w[0] = w[n + 1] = n + 1;
    stk[tt = 1] = 0;
    for (int i = 1; i <= n + 1; i ++ )
    {
        while (tt && w[stk[tt]] <= w[i]) rmx[stk[tt -- ]] = i;
        lmx[i] = stk[tt];
        stk[ ++ tt] = i;
    }
    
    for (int i = 1; i <= n; i ++ )
    {
        c[i] = (int)(i - lmn[i]) * (rmn[i] - i) % P;
        d[i] = (int)(i - lmx[i]) * (rmx[i] - i) % P;
    }
    
    int res = 0;
    for (int i = 1; i <= n; i ++ )
    {
        int id = p[i], w2 = w[id];
        int B1 = b1.query(1, id - 1);
        int B2 = b2.query(id + 1, n);
        int B3 = b3.query(1, id - 1);
        int B4 = b4.query(id + 1, n);
        res = (res + (
            w2 * w2 % P * B1 % P * B2 % P + B3 * B4 % P - 
            (B1 * B4 % P + B2 * B3 % P) % P * w2 % P + P
            ) % P * c[id] % P + P) % P;
        b1.update(id, d[id]);
        b2.update(id, d[id]);
        b3.update(id, d[id] * w2 % P);
        b4.update(id, d[id] * w2 % P);
    }
    
    cout << (res % P + P) % P << endl;
    
    return 0;
}
```

---

## 作者：My__L (赞：3)

这种区间最值问题按区间考虑肯定不优，所以起手先用单调栈求出每个值 $a_i$ 作为区间最大值/最小值的次数，之后按值考虑。记 $cnt1_i$ 表示 $a_i$ 作为区间最大值的次数，$cnt2_i$ 表示 $a_i$ 作为区间最小值的次数。

考虑枚举区间三元组中第二个区间的最小值 $a_i$，那么其对答案的贡献应是
$$cnt2_i\times \sum_{j<i,a_j<a_j}{(a_i-a_j)\times cnt1_j}\times \sum_{j>i,a_j<a_i}{(a_i-a_j)\times cnt1_j}$$

这显然二维数点问题，所以可以按值域扫描线后线段树维护两部分的 $\sum{cnt1_j}$ 以及 $\sum{a_j\times cnt1_j}$ 并计算答案。

```
#include <bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define fst first
#define scd second
using namespace std;
const int N=1e6+5;
const int MOD=9712176;
int n,a[N],pos[N],ans;
int q[N],tl,mx[N],mn[N];
struct Segment_Tree
{
    struct node { int l,r; pii res; }tr[N<<2];
    pii mge(pii a,pii b) { return {(a.fst+b.fst)%MOD,(a.scd+b.scd)%MOD}; }
    void push_up(int id) { tr[id].res=mge(tr[id<<1].res,tr[id<<1|1].res); }
    void build(int id,int l,int r)
    {
        tr[id].l=l,tr[id].r=r;
        if (l==r) return ;
        int mid=(l+r)>>1;
        build(id<<1,l,mid),build(id<<1|1,mid+1,r);
    }
    void update(int id,int pos,int k1,int k2)
    {
        if (tr[id].l==tr[id].r) { tr[id].res={k1*k2%MOD,k2}; return ; }
        int mid=(tr[id].l+tr[id].r)>>1;
        if (pos<=mid) update(id<<1,pos,k1,k2);
        else update(id<<1|1,pos,k1,k2); push_up(id);
    }
    pii query(int id,int l,int r)
    {
        if (l>r) return {0,0};
        if (tr[id].l>=l&&tr[id].r<=r) return tr[id].res;
        int mid=(tr[id].l+tr[id].r)>>1; pii res={0,0};
        if (mid>=l) res=query(id<<1,l,r);
        if (mid+1<=r) res=mge(res,query(id<<1|1,l,r)); return res;
    }
}Tr;

void init()
{
    for (int i=1;i<=n;i++)
    {
        while (tl&&a[q[tl]]<a[i]) { mx[q[tl]]=i-q[tl]; tl--; }
        q[++tl]=i;
    }
    while (tl) { mx[q[tl]]=n-q[tl]+1; tl--; }
    for (int i=n;i>=1;i--)
    {
        while (tl&&a[q[tl]]<a[i]) { mx[q[tl]]=mx[q[tl]]*(q[tl]-i)%MOD; tl--; }
        q[++tl]=i;
    }
    while (tl) { mx[q[tl]]=mx[q[tl]]*q[tl]%MOD; tl--; }

    for (int i=1;i<=n;i++)
    {
        while (tl&&a[q[tl]]>a[i]) { mn[q[tl]]=i-q[tl]; tl--; }
        q[++tl]=i;
    }
    while (tl) { mn[q[tl]]=n-q[tl]+1; tl--; }
    for (int i=n;i>=1;i--)
    {
        while (tl&&a[q[tl]]>a[i]) { mn[q[tl]]=mn[q[tl]]*(q[tl]-i)%MOD; tl--; }
        q[++tl]=i;
    }
    while (tl) { mn[q[tl]]=mn[q[tl]]*q[tl]%MOD; tl--; }
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);

    cin>>n;
    for (int i=1;i<=n;i++) { cin>>a[i]; pos[a[i]]=i; }

    Tr.build(1,1,n),init();
    for (int i=1;i<=n;i++)
    {
        pii tmp1=Tr.query(1,1,pos[i]-1),tmp2=Tr.query(1,pos[i]+1,n);
        ans=(ans+mn[pos[i]]*(i*tmp1.scd%MOD-tmp1.fst+MOD)%MOD*(i*tmp2.scd%MOD-tmp2.fst+MOD)%MOD)%MOD;
        Tr.update(1,pos[i],i,mx[pos[i]]);
    }
    cout<<ans; return 0;
}
```

---

## 作者：UniGravity (赞：2)

## Solution P10173 maxiMINImax
提示：这篇题解讲述了从暴力到正解的一步步优化过程，适合循序渐进的阅读。

### 做法
首先讲暴力做法：

发现答案：
$$\max(0,\min_{[l_2,r_2]}-\max_{[l_1,r_1]})\times\max(0,\min_{[l_2,r_2]}-\max_{[l_3,r_3]})$$
实际上要求 $\min_{[l_2,r_2]}>\max_{[l_1,r_1]}$ 且 $\min_{[l_2,r_2]}>\max_{[l_3,r_3]}$，否则答案为 $0$ **不计入**。

![](https://cdn.luogu.com.cn/upload/image_hosting/tzani5fg.png)
如图，我们设 $\min_{[l_2,r_2]}$ 为蓝色点 $j$，$\max_{[l_1,r_1]}$ 和 $\max_{[l_3,r_3]}$ 为红色点 $i$ 和 $k$。

根据上述式子，$j$ 点的值**最大**。

如果给定满足条件的 $i,j,k$，那么**一定**满足 $r_1<l_2,r_2<l_3$，以 $r_1<l_2$ 为例，可以从 $r_1<a_i,l_2>a_j,a_i<a_j$ 得出。

即如果确定了 $i,j,k$，就确定了 $l_1,r_1,l_2,r_2,l_3,r_3$ 的**取值范围**。

每种情况对答案的贡献是 $(a_j-a_i)(a_j-a_k)$，同时共有 $(i-minl_i+1)(minr_j-j+1)(j-maxl_j+1)(maxr_j-j+1)(k-minl_k+1)(minr_k-k+1)$ 种情况。

$minl_i$ 代表**红色**区间**左端最远**能延伸的范围，也是 $i$ **左侧第一个**比 $i$ **大**的数的编号加 $1$，同理 $minr_i$ 是**右端**最远能延伸的范围。

$maxl_i$ 代表**蓝色**区间左端最远能延伸的范围，也是 $i$ 左侧第一个比 $i$ **小**的数的编号加 $1$，同理 $minr_i$ 是右端最远能延伸的范围，这几个值都可以用**单调栈** $O(1)$ 求出。

做法很明显，枚举 $i,j,k$，然后按上述方法求贡献，时间复杂度 $O(n^3)$。

这里给出核心代码：
```cpp
val = (a[j] - a[i]) * (a[j] - a[k]) % MOD;
cnt = (j - minl[j] + 1) * (minr[j] - j + 1) % MOD * (i - maxl[i] + 1) * (maxr[i] - i + 1) % MOD * (k - maxl[k] + 1) * (maxr[k] - k + 1) % MOD;
ans = (ans + val * cnt % MOD) % MOD;
```

------------

考虑优化。  

根据乘法交换律，$i$ 和 $k$ 的贡献可以分开计算。

枚举 $j$，接下来**分开**枚举 $i$ 和 $j$，时间复杂度 $O(n^2)$。

核心代码，$val_i=(i-maxl_i+1)(maxr_i-i+1)$。   
```cpp
a1 = (j - minl[j] + 1) * (minr[j] - j + 1) % MOD;
a2 = a3 = 0;
for (int i = 1; i < j; i++) {
    if (a[j] > a[i]) a2 = (a2 + (a[j] - a[i]) * val[i] % MOD) % MOD;
}
for (int i = j + 1; i <= n; i++) {
    if (a[j] > a[i]) a3 = (a3 + (a[j] - a[i]) * val[i] % MOD) % MOD;
}
ans = (ans + a1 * a2 % MOD * a3 % MOD) % MOD;
```

------------

再次优化，发现 $i,j,k$ 的大小关系不好处理。

根据以下式子：
$$val_i\cdot(a_j-a_i)=a_j\cdot val_i-a_i\cdot val_i$$

发现需要求的是所有 $i<j,a_i<a_j$ 的 $val_i$ 值**和**。

对于 $a_i<a_j$ 我们可以**按顺序加点**累计和，对于前面这个限制则难以优化。

这个时候我们又想到了**树状数组**，按顺序将第 $i$ 位变为 $val_i$，查询 $[1,j)$ 的和即可。

同理，$a_i\cdot val_i$ 也是**固定值**，可以按上述方式处理。

这样我们只需开两个**单点修改**，**区间求和**的树状数组即可。

时间复杂度 $O(n\log n)$。

### 完整代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
		ch = getchar();
    }
    return x * f;
}

const int MOD = 9712176;

int n, a[1000005], sum[1000005];

struct Tree {
	int bit[1000005];
	
	int lowbit(int x) {
		return x & (-x);
	}
	void update(int x, int num) {
		for (int i = x; i <= n; i += lowbit(i)) {
			bit[i] = (bit[i] + num) % MOD;
		}
	}
	int query(int x) {
		int sum = 0;
		for (int i = x; i >= 1; i -= lowbit(i)) {
			sum = (sum + bit[i]) % MOD;
		}
		return sum;
	}
	int query(int x, int y) {
		return (query(y) - query(x - 1) + MOD) % MOD;
	}
};

inline int getv(int l, int r) {
	return sum[r] - sum[l - 1];
}

int maxl[1000005], maxr[1000005], minl[1000005], minr[1000005];
int val[1000005], val2[1000005];
int pos[1000005];

Tree v1, v2;

signed main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		a[i] = read();
		pos[a[i]] = i;
		sum[i] = sum[i - 1] + a[i];
	}
	stack< int > s1, s2, s3, s4;
	a[0] = 0x3f3f3f3f;
	s1.push(0);
	for (int i = 1; i <= n; i++) {
		while (!s1.empty() && a[s1.top()] < a[i]) {
			s1.pop();
		}
		maxl[i] = s1.top() + 1;
		s1.push(i);
//		printf("%lld: %lld\n", i, maxl[i]);
	}
	a[0] = 0;
	s2.push(0);
	for (int i = 1; i <= n; i++) {
		while (!s2.empty() && a[s2.top()] > a[i]) {
			s2.pop();
		}
		minl[i] = s2.top() + 1;
		s2.push(i);
//		printf("%lld: %lld\n", i, minl[i]);
	}
	a[n + 1] = 0x3f3f3f3f;
	s3.push(n + 1);
	for (int i = n; i >= 1; i--) {
		while (!s3.empty() && a[s3.top()] < a[i]) {
			s3.pop();
		}
		maxr[i] = s3.top() - 1;
		s3.push(i);
//		printf("%lld: %lld\n", i, maxr[i]);
	}
	a[n + 1] = 0;
	s4.push(n + 1);
	for (int i = n; i >= 1; i--) {
		while (!s4.empty() && a[s4.top()] > a[i]) {
			s4.pop();
		}
		minr[i] = s4.top() - 1;
		s4.push(i);
//		printf("%lld: %lld\n", i, minr[i]);
	}
	for (int i = 1; i <= n; i++) {
		val[i] = (i - maxl[i] + 1) * (maxr[i] - i + 1);
		val2[i] = val[i] * a[i] % MOD;
	}
	
	int ans = 0, a1, a2, a3;
	for (int jval = 2; jval <= n; jval++) {
		int lst = pos[jval - 1];
		v1.update(lst, val[lst]); // 值域树状数组 
		v2.update(lst, val2[lst]);
		int j = pos[jval], la, ra, lt, rt;
		// a[j] * val[i] - val2[i]  (a[i] < a[j])
		la = v1.query(1, j - 1);
		ra = v1.query(j + 1, n);
		lt = v2.query(1, j - 1);
		rt = v2.query(j + 1, n);
		a1 = (j - minl[j] + 1) * (minr[j] - j + 1) % MOD;
		a2 = (a[j] * la % MOD - lt + MOD) % MOD;
		a3 = (a[j] * ra % MOD - rt + MOD) % MOD;
		ans = (ans + a1 * a2 % MOD * a3 % MOD) % MOD;
	}
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：2)

不保证是最简单的做法。仅供参考。

考虑怎样才能对答案产生贡献。不难发现，只要满足 $\min_{[l_2, r_2]} \le \max{[l_1, r_1]}$ 和 $\min_{[l_2, r_2]} \le \max{[l_3, r_3]}$ 两个条件中的一个，就对答案没有贡献。

由于 $[l_1, f_1]$ 在 $[l_2, r_2]$ 左面，$[l_3, r_3]$ 在 $[l_2, r_2]$ 右面，不妨设 $\max_l = \max{[l_1, r_1]}, \max_r = \max_{[l_3, r_3]}, \min = \min_{[l_2, r_2]}$。

因此问题转化为：对满足 $\min > \max_l \wedge \min > \max_r$ 的区间，求出 $(\min - \max_l)(\min - \max_r)$ 的和。

考虑枚举 $\min$。接下来，枚举左边的 $\max_l < \min$，枚举右面的 $\max_r > \min$，对答案进行贡献即可。下面讨论如何计算贡献。

----------------

设当前枚举的 $\min$ 值为 $x$。找到 $x$ 左右两边小于 $x$ 的距离 $x$ 最近的两个位置 $L, R$，则对于 $(L, R)$ 内包含 $x$ 的子区间，其最小值都是 $x$。

设 $x$ 左面小于 $x$ 的位置集合为 $S_l$，右面小于 $x$ 的位置集合为 $S_r$。显然，我们只需要在 $S_l$ 中选一个作为 $\max_l$，$S_r$ 中选一个作为 $\max_r$ 即可。

假设我们选定了一个 $\max_l \in S_l$，求出 $\max_l$ 左右两边距离它最近的且大于 $\max_l$ 的位置 $L, R$，则对于所有包含 $\max_l$ 的子区间，其最大值都是 $\max_l$。对于 $\max_r$ 同理。

-----------------

接下来回到答案计算。对于一对 $(\max_l, \min, \max_r)$ 来说，其贡献为：

$(\min - \max_l)(\min - \max_r) = \min ^ 2 - \min \max_l - \min \max_r + \max_l \max_r$

逐项考虑。对于第一项 $\min ^ 2$，只要左右配对一个就能贡献一次。设左面 $\max_l < \min$ 的区间个数为 $s_l$，右面为 $s_r$，贡献次数就是 $s_l \times s_r$。

对于第二项 $\min \max_l$，设 $\max_l$ 之和为 $\sum \max_l$，则这部分贡献就是 $\min s_r\sum \max_l$。右面同理。

对于第三项，贡献显然是 $\sum \max_l \times \sum \max_r$。

考虑如何维护 $\sum \max$ 和 $s$。可以使用树状数组 / 线段树动态维护。复杂度 $O(n \log n)$。而对于每个数左面 / 右面离他最近的最大 / 最小值，可以做四遍单调栈。

是目前的最优解。代码略微压行。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define gc getchar
#define pc putchar
#define int long long
#define all(x) x.begin(), x.end()
#define D(x) (cerr << #x << " = " << x << '\n')
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )
#define rop(i, a, b) for (int i = (a); i < (b); i ++ )
#define dep(i, a, b) for (int i = (a); i >= (b); i -- )

using namespace std;

const int N = 1000010;
const int mod = 9712176;

int tr1[N], tr2[N], a[N], l[N], r[N], L[N], R[N], stk[N], bin[N], ans, top, n;
void add(int *tr, int x, int v) { for (int i = x; i <= n; i += (i & -i)) tr[i] += v; }
int ask(int *tr, int x, int s = 0) { for (int i = x; i; i -= (i & -i)) s += tr[i]; return s; }
int res[N];
signed main() {
	read(n); rep(i, 1, n) read(a[i]);
	top = 0; rep(i, 1, n) {
		while (top and a[stk[top]] < a[i]) top -- ;
		l[i] = stk[top]; stk[ ++ top] = i;
	} top = 0; stk[ ++ top] = a[n + 1] = n + 1;
	dep(i, n, 1) {
		while (top and a[stk[top]] < a[i]) top -- ;
		r[i] = stk[top]; stk[ ++ top] = i;
	} rep(i, 1, n) l[i] ++ , r[i] -- ;
	top = 0; rep(i, 1, n) {
		while (top and a[stk[top]] > a[i]) top -- ;
		L[i] = stk[top]; stk[ ++ top] = i;
	} top = 0; stk[ ++ top] = n + 1; a[n + 1] = 0;
	dep(i, n, 1) {
		while (top and a[stk[top]] > a[i]) top -- ;
		R[i] = stk[top]; stk[ ++ top] = i;
	} rep(i, 1, n) L[i] ++ , R[i] -- ;
	rep(i, 1, n) bin[a[i]] = i;
	rep(i, 1, n) {
		int p = bin[i], maxl = ask(tr1, p) % mod, maxr =( (ask(tr1, n) - ask(tr1, p)) % mod + mod) % mod;
		int sl = ask(tr2, p) % mod, sr = ((ask(tr2, n) - ask(tr2, p)) % mod + mod) % mod, s = 0;
		(s += maxl * maxr % mod) %= mod; (s -= maxl * sr % mod * i % mod) %= mod;
		(s -= maxr * sl % mod * i % mod) %= mod; (s += sl * sr % mod * i % mod * i % mod) %= mod;
		((s %= mod) += mod) %= mod; (ans += s * ((R[p] - p) * (p - L[p]) % mod + R[p] - L[p] + 1) % mod) %= mod;
		add(tr1, p, i * ((r[p] - p) * (p - l[p]) % mod + (r[p] - l[p] + 1)) % mod); 
		add(tr2, p, ((p - l[p]) * (r[p] - p) + r[p] - l[p] + 1) % mod);
	} write('\n', ans); return 0;
}

```

可能写的有点语无伦次了。

---

## 作者：operator_ (赞：1)

# P10173 maxiMINImax

[题目传送门](https://www.luogu.com.cn/problem/P10173)

## 题解

感觉还是比较套路的，而且不需要笛卡尔树，~~连我都能做出来~~。

这种区间 $\min,\max$ 的题不难想到单调栈，我们可以 $O(n)$ 处理出有几个区间的最小/大值为 $a_i$，记为 $ln_i,lx_i$。然后推一下式子，写成标准形式，即 $\sum\limits_{i<j<k}ln_j\times lx_i\times lx_k\times (a_j-a_i)(a_j-a_k)$ 。

最后那个东西显然可以拆开，变成 $a_i^2-a_ia_j-a_ia_k+a_ja_k$。

可以用权值树状数组求出 $\sum\limits_{i=1}^{x-1}lx_i,\sum\limits_{i=1}^{x-1}lx_ia_i,\sum\limits_{i=x+1}^nlx_i,\sum\limits_{i=x+1}^nlx_ia_i$，简记为 $l1_x,l2_x,r1_x,r2_x$，则答案为 $\sum\limits_{i=1}^nln_i\times(a_i^2\times l1_i\times r1_i-a_i\times l2_i\times r1_i-a_i\times l1_i\times r2_i+l2_i\times r2_i)$，即可 $O(n)$ 统计。

代码：

```cpp
/*
 * @Author: operator_ 
 * @Date: 2024-02-18 15:43:22 
 * @Last Modified by: operator_
 * @Last Modified time: 2024-02-18 17:16:35
 */
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int rd() {
    int s=0,m=0;char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')m=1;ch=getchar();}
    while( isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
    return m?-s:s;
}
const int M=9712176;
int n,a[1000005],ans,st1[1000005],top1,st2[100005],top2;
int lmin[1000005],rmin[1000005],lmax[1000005],rmax[1000005];
int lenmin[1000005],lenmax[1000005],l1[1000005],l2[1000005],r1[1000005],r2[1000005];
struct Binary_Indexed_Tree {
	int t[1000005];
	int lb(int x) {return x&-x;}
	int sum(int x) {int s=0;for(int i=x;i;i-=lb(i)) s=(s+t[i])%M;return s;}
	void add(int x,int k) {for(int i=x;i<=n;i+=lb(i)) t[i]=(t[i]+k)%M;}
}t1,t2;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) a[i]=rd();
    for(int i=1;i<=n;i++) {
        while(top1&&a[st1[top1]]>a[i]) top1--;
        lmin[i]=st1[top1];st1[++top1]=i;
        while(top2&&a[st2[top2]]<a[i]) top2--;
        lmax[i]=st2[top2];st2[++top2]=i;
    }
    st1[top1=0]=st2[top2=0]=n+1;
    for(int i=n;i>=1;i--) {
        while(top1&&a[st1[top1]]>a[i]) top1--;
        rmin[i]=st1[top1];st1[++top1]=i;
        while(top2&&a[st2[top2]]<a[i]) top2--;
        rmax[i]=st2[top2];st2[++top2]=i;
    }
    for(int i=1;i<=n;i++)
        lenmin[i]=(i-lmin[i])*(rmin[i]-i)%M,lenmax[i]=(i-lmax[i])*(rmax[i]-i)%M;
    for(int i=1;i<=n;i++) {
        l1[i]=t1.sum(a[i]),l2[i]=t2.sum(a[i]);
        t1.add(a[i],lenmax[i]);t2.add(a[i],lenmax[i]*a[i]%M);
    }
    for(int i=1;i<=n;i++) t1.t[i]=t2.t[i]=0;
    for(int i=n;i>=1;i--) {
        r1[i]=t1.sum(a[i]),r2[i]=t2.sum(a[i]);
        t1.add(a[i],lenmax[i]);t2.add(a[i],lenmax[i]*a[i]%M);
    }
    for(int i=1;i<=n;i++) {
        ans=(ans+a[i]*a[i]%M*l1[i]%M*r1[i]%M*lenmin[i]%M)%M;
        ans=(ans-a[i]*l2[i]%M*r1[i]%M*lenmin[i]%M+M)%M;
        ans=(ans-a[i]*l1[i]%M*r2[i]%M*lenmin[i]%M+M)%M;
        ans=(ans+l2[i]*r2[i]%M*lenmin[i]%M)%M;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：zhangxy__hp (赞：0)

容易发现相交的区间是不会产生贡献的。于是不用考虑这个限制。

用单调栈可以求出以 $a_i$ 为最小值和最大值的区间个数 $qmn_i$ 和 $qmx_i$。

从小到大枚举第二个区间的最小值，记 $p_i$ 表示 $i$ 的位置，则对于 $i$ 的答案即为：

$$
\sum_{j=1}^{p_i-1}\sum_{k=p_i+1}^{n}{qmn_{p_i}qmx_jqmx_k(i-a_j)(i-a_k)}
$$

~~简单~~推式子后得到：

$$
qmn_{p_i}(\sum{qmx_j}\sum{qmx_k}i^2-\sum{qmx_ja_j}\sum{qmx_k}i-\sum{qmx_j}\sum{qmx_ka_k}i+\sum{qmx_ja_j}\sum{qmx_ka_k})
$$

于是开两棵树状数组维护 $qmx_j$ 和 $qmx_ja_j$ 就好了。时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline

using namespace std;
namespace asbt{
namespace cplx{bool begin;}
const int maxn=1e6+5,mod=9712176;
int n,a[maxn],p[maxn],zhan[maxn];
int lmn[maxn],rmn[maxn];
int lmx[maxn],rmx[maxn];
int qmn[maxn],qmx[maxn];
struct{
	int tr[maxn];
	il int lowbit(int x){
		return x&-x;
	}
	il void upd(int p,int v){
		for(;p<=n;p+=lowbit(p)){
			(tr[p]+=v)%=mod;
		}
	}
	il int query(int p){
		int res=0;
		for(;p;p-=lowbit(p)){
			(res+=tr[p])%=mod;
		}
		return res;
	}
	il int query(int l,int r){
		return (query(r)-query(l-1)+mod)%mod;
	}
}F1,F2;
namespace cplx{
	bool end;
	il double usdmem(){return (&begin-&end)/1048576.0;}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		p[a[i]]=i;
	}
	for(int i=1,top=0;i<=n;i++){
		while(top&&a[zhan[top]]>a[i]){
			top--;
		}
		lmn[i]=zhan[top];
		zhan[++top]=i;
	}
	for(int i=1,top=0;i<=n;i++){
		while(top&&a[zhan[top]]<a[i]){
			top--;
		}
		lmx[i]=zhan[top];
		zhan[++top]=i;
	}
	zhan[0]=n+1;
	for(int i=n,top=0;i;i--){
		while(top&&a[zhan[top]]>a[i]){
			top--;
		}
		rmn[i]=zhan[top];
		zhan[++top]=i;
	}
	for(int i=n,top=0;i;i--){
		while(top&&a[zhan[top]]<a[i]){
			top--;
		}
		rmx[i]=zhan[top];
		zhan[++top]=i;
	}
	for(int i=1;i<=n;i++){
		qmn[i]=(i-lmn[i])*1ll*(rmn[i]-i)%mod;
		qmx[i]=(i-lmx[i])*1ll*(rmx[i]-i)%mod;
	}
	int ans=0;
	for(int i=1,xj,xaj,xk,xak;i<=n;i++){
		xj=F1.query(1,p[i]-1);
		xaj=F2.query(1,p[i]-1);
		xk=F1.query(p[i]+1,n);
		xak=F2.query(p[i]+1,n);
		(ans+=qmn[p[i]]*1ll*(xj*1ll*xk%mod*i%mod*i%mod-xaj*1ll*xk%mod*i%mod-xj*1ll*xak%mod*i%mod+xaj*1ll*xak%mod)%mod)%=mod;
		(ans+=mod)%=mod;
		F1.upd(p[i],qmx[p[i]]);
		F2.upd(p[i],qmx[p[i]]*1ll*i%mod);
	}
	cout<<ans;
	return 0;
}
}
int main(){return asbt::main();}
```

---

