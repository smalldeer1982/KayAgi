# DerrickLo's Brackets (UBC002E)

## 题目描述

DerrickLo 有一个长度为 $n$ 的正整数序列 $a$，以及一个长度为 $n$ 的仅含有 `(` 与 `)` 的字符序列 $t$。他现在要根据这两个序列生成 $q$ 组括号序列，具体地，他会选择两个在 $[1,n]$ 中的正整数 $l,r$ 且 $l\le r$ 并对一个初始为空的字符串 $S$ 进行如下操作：

- 从小到大枚举每个在 $[l,r]$ 之间的正整数 $i$，将 $a_i$ 个 $t_i$ 加到 $S$ 的末尾。

他希望你能在每次他生成了一个括号序列 $S$ 后告诉他 $S$ 的最长合法匹配子串的大小。

合法匹配串的定义如下：

- 空串是合法匹配串。
- 若 $A$ 是合法匹配串，则 $(A)$ 为合法匹配串。
- 若 $A,B$ 都是合法匹配串，则 $AB$ 为合法匹配串。
- 除此以外的所有字符串都不是合法匹配串。

## 说明/提示

**样例说明**

第一次生成的括号序列为 `(()))(`，它的最长合法匹配子串为 `(())`。

第二次生成的括号序列为 `)))(`，它的最长合法匹配子串为空串。

**数据范围**

$1\le n,q\le 10^6$，$1\le a_i\le 10^9$，每次生成中的 $l,r$ 满足 $1\le l\le r\le n$，$t$ 仅由 `(` 与 `)` 组成。除 $t$ 外所有输入数据为整数。

## 样例 #1

### 输入

```
3 2
2 3 1
()(
1 3
2 3```

### 输出

```
4
0```

# 题解

## 作者：Crazyouth (赞：1)

## 分析

赛后写一个出题人 & 验题人解。

读前注意：这篇题解非常不使用数学语言，但是比较形象。

我们先画出整个括号序列的图（假设一个 `(` 使线往上走一格，一个 `)` 往下走一格），假设它长这样：（红线间是一个 $a_i$）

![](https://cdn.luogu.com.cn/upload/image_hosting/pwf653am.png)

那么转化完题意后结果就是要找那个区间内最长的线使得两边“海拔”相等。我们想一下什么样的线才最长，不妨设我们有一个 $[l',r']$ 是海拔相等的，若它的两端都不是某个 $a_i$ 的两端，$[l'-1,r'+1]$ 必定也是海拔相等的。

我们既然已经知道最长的海拔相等的线需要端点，不妨就从端点向左或者向右找最远的海拔相等的位置，且中间不被别的括号挡住（这里以向右为例）：

![](https://cdn.luogu.com.cn/upload/image_hosting/l0ud5vw6.png)

我们假设一个箭头从 $s$ 点出发，箭头指向了区间 $[t-1,t]$（如果刚好指向了一个端点，我们认为那个端点就是 $t$），那么只要询问区间 $[l,r]$ 包含 $[s,t]$，这段箭头就可能作为一个最长的海拔相等的线段，也就是可以为本次询问做贡献，这是一个二位数点问题。

但是我们漏了一些东西，请看这里：

![](https://cdn.luogu.com.cn/upload/image_hosting/tuo5txr4.png)

如果很多的端点同一个高度，我们就需要知道询问区间 $[l,r]$ 最多容纳多少个这样的端点，但这样的端点数量一定不少，于是我们研究一下就会发现只有满足**该端点海拔为区间最小值**的才会被漏算。如果不是最小值，往两边个扩展到下一个端点必然会比当前的长度长；如果不能扩展则说明有一个端点是询问区间的端点，会在第一部分（即二维数点）的时候被计算。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ed79f5d4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
![](https://cdn.luogu.com.cn/upload/image_hosting/iajtbyf3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样一来，我们只需要支持区间最小值和区间某个数最前和最后的出现位置即可。我们分别使用线段树与 vector 上二分可以求得。

然后对两部分的最长线段长度取 $\max$ 即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
stack<int> st;
const int N=1e6+10;
int a[N],sum[N],h[N],n,q;
vector<int> pos[N];
string t;
set<int> lsh;
unordered_map<int,int> mp;
//hi->height of i
struct node
{
	int l,r,len;
}p[N<<1];
int cmp(node x,node y)
{
	return x.r<y.r;
}
struct query
{
	int l,r,id;
}qry[N];
int cmp2(query x,query y)
{
	return x.r<y.r;
}
int ans[N];
int tr[N<<2];
void add(int k,int c,int x=0,int y=n,int o=1)
{
	if(x==y)
	{
		tr[o]=max(tr[o],c);
		return;
	}
	int m=x+y>>1;
	if(k<=m) add(k,c,x,m,o<<1);
	else add(k,c,m+1,y,o<<1|1);
	tr[o]=max(tr[o<<1],tr[o<<1|1]);
}
void upd(int k,int c,int x=0,int y=n+1,int o=1)
{
	if(x==y)
	{
		tr[o]=c;
		return;
	}
	int m=x+y>>1;
	if(k<=m) upd(k,c,x,m,o<<1);
	else upd(k,c,m+1,y,o<<1|1);
	tr[o]=min(tr[o<<1],tr[o<<1|1]);
}
int qmax(int l,int r,int x=0,int y=n,int o=1)
{
	if(l<=x&&y<=r) return tr[o];
	int m=x+y>>1;
	int res=0;
	if(l<=m) res=qmax(l,r,x,m,o<<1);
	if(r>m) res=max(res,qmax(l,r,m+1,y,o<<1|1));
	return res;
}
int qmin(int l,int r,int x=0,int y=n+1,int o=1)
{
	if(l<=x&&y<=r) return tr[o];
	int m=x+y>>1;
	int res=1e9;
	if(l<=m) res=qmin(l,r,x,m,o<<1);
	if(r>m) res=min(res,qmin(l,r,m+1,y,o<<1|1));
	return res;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i],sum[i]=sum[i-1]+a[i];
	cin>>t;
	t=' '+t;
	for(int i=1;i<=n;i++) h[i]=h[i-1]+(t[i]=='('?1:-1)*a[i],lsh.insert(h[i]);
	lsh.insert(0);
	int lcnt=0;
	for(auto i:lsh) mp[i]=++lcnt;
	for(int i=0;i<=n;i++)
	{
		int nh=mp[h[i]];
		upd(i,nh);
		pos[nh].push_back(i);
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(t[i]=='(') st.push(i);
		else
		{
			while(st.size()&&h[i]<h[st.top()-1]&&h[st.top()-1]<=h[i-1])
			{
				p[++cnt]={st.top(),i,sum[i-1]-sum[st.top()-1]+h[i-1]-h[st.top()-1]};
				st.pop();
			}
		}
	}
	while(st.size()) st.pop();
	for(int i=n;i;i--)
	{
		if(t[i]==')') st.push(i);
		else
		{
			while(st.size()&&h[i]>=h[st.top()]&&h[st.top()]>h[i-1])
			{
				p[++cnt]={i,st.top(),sum[st.top()]-sum[i]+h[i]-h[st.top()]};
				st.pop();
			}
		}
	}
	for(int i=1;i<=q;i++)
	{
		cin>>qry[i].l>>qry[i].r;
		qry[i].id=i;
		int minn=qmin(qry[i].l-1,qry[i].r);
		ans[i]=sum[*(upper_bound(pos[minn].begin(),pos[minn].end(),qry[i].r)-1)]-sum[(*lower_bound(pos[minn].begin(),pos[minn].end(),qry[i].l-1))];
	}
	memset(tr,0,sizeof tr);
	sort(p+1,p+cnt+1,cmp);
	sort(qry+1,qry+q+1,cmp2);
	int pt=1;
	for(int i=1;i<=q;i++)
	{
		while(pt<=cnt&&p[pt].r<=qry[i].r)
		{
			add(p[pt].l,p[pt].len);
			pt++;
		}
		ans[qry[i].id]=max(ans[qry[i].id],qmax(qry[i].l,n));
	}
	for(int i=1;i<=q;i++) cout<<ans[i]<<'\n';
}

---

## 作者：cosf (赞：1)

我们先转换题意。令 $S$ 表示原始字符串，即 $a_i$ 个 $t_i$ 连起来的结果。令 $s_0 = 0$，且 $\forall i \in [1, n], s_i = s_{i - 1} + a_i$。再令高度函数 $h$：
$$
h_i = \begin{cases}
0 & i = 0\\
h_{i - 1} + 1 & \exists j, i \in (s_{j - 1}, s_j], t_j = \text{'('}\\
h_{i - 1} - 1 & \exists j, i \in (s_{j - 1}, s_j], t_j = \text{')'}\\
\end{cases}
$$
令 $n_0 = s_n$，则 $|S| = n_0$。原题相当于：

> 给定 $l, r$，求一组 $(l', r')$ 使得 $[l', r'] \sub [l, r]$ 且 $h_{l'} = h_{r'} = \min_{i \in [l', r']}h_i$，并且最大化 $r' - l'$。

性质一：最优解必然有一个端点 $\in s$。

证明：考虑反证，令最优解为 $(l', r')$。由合法括号序列性质得字符串 $S_{l'} = \text{'('}, S_{r'} = \text{')'}$。再由 $l'$ 非端点得出 $S_{l' - 1} = S_{l'} = \text{'('}$ 以及 $l' - 1 \ge l$。同理 $S_{r' + 1} = \text{')'}, r' + 1 \le r$，则 $(l' - 1, r' + 1)$ 为更优的解，矛盾。

于是我们可以分类讨论。

如果只有一个端点 $\in s$，不妨设为右端点 $r'$（左端点同理）。跟前面类似，$S_{l' - 1} = S_{l'} = \text{'('}$，即，该合法子串 $(l', r')$ 不可能通过在其左边添加一个合法子串使其变长，这也说明了此时 $l'$ 的唯一性。设 $r' = s_j$，则我们只需要求 $h_{s_{1 \dots j - 1}}$ 中最后的小于 $h_{r'}$ 的一项，设为 $h_{s_i}$，则子串 $(l', r')$ 的长度为 $r' - s_i - h_{r'} + h_{s_i}$，可以贡献给所有 $l \le i\land j \le r$ 的询问。这是一个二维数点问题，可以在 $
O(n\log n)$ 复杂度内解决。

考虑两个端点都 $\in s$ 的情况。我们先钦定右端点为 $s_j$，我们找到最小的 $i$，使得 $(s_i, s_j)$ 合法。这可以对 $l \le i \land j \le r$ 的询问做贡献。我们再钦定左端点 $s_i$，找到最大的 $j$ 使得 $(s_i, s_j)$ 合法。这同样可以给 $l \le i \land j \le r$ 的询问做贡献。这仍然是一个二维数点问题，复杂度 $O(n\log n)$。

这两类并不能涵盖所有两个端点 $\in s$ 的情况。可以证明，唯一可能漏掉的情况是 $h_i, h_j$ 均为 $h_{l\dots r}$ 最小值。这个也好处理，先对每个区间求其最小值，然后离线下求区间当中最小值出现的最左和最右的位置，相减就是其贡献了，复杂度 $O(n\log n)$。线性 RMQ 的话那就是 $O(n)$ 的。

令 $p_j$ 表示上述过程中最大的 $i$，$q_i$ 表示最小的 $j$。则会漏掉的情况，必定是对于某个 $i \in [l, r]$，有 $p_i \lt l, r \lt q_i$。显然有 $h_{s_i}$ 为区间最小值。

当然，如果要求在线的话，用主席树一样可以做到 $O(n\log n)$。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define MAXN 1000006
#define ls (p << 1)
#define rs (p << 1 | 1)

using ll = long long;

int a[MAXN];

ll h[MAXN], s[MAXN], b[MAXN];
int idx;

int n, m;

struct Query
{
    int l, r, i;
} q[MAXN];
ll res[MAXN];

struct Node
{
    int p;
    ll v;
};

vector<Query> qs[MAXN];
vector<Node> qr[MAXN];
vector<int> ps[MAXN];

template <typename Cmp = less<ll>, ll st = 0>
struct SGT
{
    static Cmp cmp;
    struct Tree
    {
        ll m, t;
    } t[MAXN << 2];

    void pushup(int p)
    {
        t[p].m = max(t[ls].m, t[rs].m, cmp);
    }

    void pushdown(int p)
    {
        if (t[p].t != st)
        {
            t[ls].m = max(t[ls].m, t[p].t, cmp);
            t[ls].t = max(t[ls].t, t[p].t, cmp);
            t[rs].m = max(t[rs].m, t[p].t, cmp);
            t[rs].t = max(t[rs].t, t[p].t, cmp);
            t[p].t = st;
        }
    }

    void build(int p, int l, int r)
    {
        t[p] = {st, st};
        if (l == r)
        {
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
    }

    void modi(int p, int l, int r, int q, ll v)
    {
        if (l == r)
        {
            t[p].m = max(t[p].m, v, cmp);
            t[p].t = max(t[p].t, v, cmp);
            return;
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        if (mid >= q)
        {
            modi(ls, l, mid, q, v);
        }
        else
        {
            modi(rs, mid + 1, r, q, v);
        }
        pushup(p);
    }

    ll query(int p, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            return t[p].m;
        }
        pushdown(p);
        int mid = (l + r) >> 1;
        ll res = st;
        if (mid >= ql)
        {
            res = max(res, query(ls, l, mid, ql, qr), cmp);
        }
        if (mid < qr)
        {
            res = max(res, query(rs, mid + 1, r, ql, qr), cmp);
        }
        return res;
    }
};

SGT t1;
SGT<greater<ll>, MAXN> t2;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        char ch;
        cin >> ch;
        if (ch == '(')
        {
            h[i] = h[i - 1] + a[i];
        }
        else
        {
            h[i] = h[i - 1] - a[i];
        }
        b[i + 1] = h[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> q[i].l >> q[i].r;
        q[i].l--;
        q[i].i = i;
    }
    sort(q + 1, q + m + 1, [](Query a, Query b)
         { return a.r < b.r; });
    // part 1 & 2: 2d counting
    vector<int> st;
    st.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        // h[has] >= h[cur] => pop
        while (!st.empty() && h[st.end()[-1]] >= h[i])
        {
            st.pop_back();
        }
        if (!st.empty())
        {
            int cur = st.end()[-1];
            qr[i].push_back({cur, s[i] - s[cur] - h[i] + h[cur]});
        }
        st.push_back(i);
    }
    st.clear();
    st.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        // h[las] > h[cur] => pop
        while (!st.empty() && h[st.end()[-1]] > h[i])
        {
            st.pop_back();
        }
        if (!st.empty() && h[st.end()[-1]] == h[i])
        {
            int cur = st.end()[-1];
            qr[i].push_back({cur, s[i] - s[cur]});
        }
        else
        {
            st.push_back(i);
        }
    }
    st.clear();
    st.push_back(n);
    for (int i = n - 1; ~i; i--)
    {
        // h[las] > h[cur] => pop
        while (!st.empty() && h[st.end()[-1]] >= h[i])
        {
            st.pop_back();
        }
        if (!st.empty())
        {
            int cur = st.end()[-1];
            qr[cur].push_back({i, s[cur] - s[i] - h[i] + h[cur]});
        }
        st.push_back(i);
    }
    st.clear();
    st.push_back(n);
    for (int i = n - 1; ~i; i--)
    {
        // h[las] > h[cur] => pop
        while (!st.empty() && h[st.end()[-1]] > h[i])
        {
            st.pop_back();
        }
        if (!st.empty() && h[st.end()[-1]] == h[i])
        {
            int cur = st.end()[-1];
            qr[cur].push_back({i, s[cur] - s[i] - h[i] + h[cur]});
        }
        else
        {
            st.push_back(i);
        }
    }
    t1.build(1, 0, n);
    int p = 1;
    for (int i = 0; i <= n; i++)
    {
        for (auto [l, v] : qr[i])
        {
            t1.modi(1, 0, n, l, v);
        }
        while (p <= m && q[p].r == i)
        {
            res[q[p].i] = max(res[q[p].i], t1.query(1, 0, n, q[p].l, i));
            p++;
        }
    }
    // part 3: bs on vector & sgt
    sort(b + 1, b + n + 2);
    idx = unique(b + 1, b + n + 2) - b - 1;
    t2.build(1, 0, n);
    for (int i = 0; i <= n; i++)
    {
        h[i] = lower_bound(b + 1, b + idx + 1, h[i]) - b;
        ps[h[i]].push_back(i);
        t2.modi(1, 0, n, i, h[i]);
    }
    for (int i = 1; i <= m; i++)
    {
        auto [l, r, j] = q[i];
        int m = t2.query(1, 0, n, l, r);
        int fi = *lower_bound(ps[m].begin(), ps[m].end(), l);
        int la = *lower_bound(ps[m].rbegin(), ps[m].rend(), r, greater<int>());
        res[j] = max(res[j], s[la] - s[fi]);
    }
    // output
    for (int i = 1; i <= m; i++)
    {
        cout << res[i] << endl;
    }
    return 0;
}
```

---

