# Feed Cats

## 题目描述

你在玩一个游戏，这个游戏有 $n$ 步。你有 $m$ 只猫，每只猫有特定的饲养时间 $[l_i,r_i]$。如果你在第 $x$ 步决定饲养，那么所有满足 $l_i\le x\le r_i$ 的猫都会被饲养；或者你不决定饲养，那么无事发生。但是如果一只猫被饲养了两次及以上，它就会死亡。请问在没有猫死亡的情况下，最多有多少只猫被饲养了至少一次？

## 样例 #1

### 输入

```
3
15 6
2 10
3 5
2 4
7 7
8 12
11 11
1000 1
1 1000
5 10
1 2
3 4
3 4
3 4
3 4
1 1
1 2
3 3
3 4
3 4```

### 输出

```
5
1
10```

# 题解

## 作者：GGapa (赞：5)

搞不懂你们为啥要搞数据结构，我就很讨厌数据结构，$O(n)$ 就可以解决这道题，代码也非常短。

定义 $F(i)$ 代表 $1\sim i$ 的时间段内最多能够喂的猫的数量，显然需要求的即为 $F(n)$，考虑到可以预处理数组 $S(i)$ 代表如果在第 $i$ 步投喂，会喂多少只猫，为了避免把一只猫喂死了，我们还需要记录一个数组 $mx(i)$ 代表如果在第 $i$ 步喂猫，最远在多少步不能够再喂，此时已经可以完成这道题，转移方程请详见代码。

```cpp
using VI = vector<int>;
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)

void solve() {
    int n, m; cin >> n >> m;
    vector<VI> A(n + 1) ;
    vector<int> mx(n + 1), S(n + 2);
    for(int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        mx[x] = max(mx[x], y);
        S[x]++; S[y + 1]--;
    }
    rep(i, 1, n) S[i] += S[i - 1], mx[i] = max(mx[i], mx[i - 1]); 
    vector<int> F(n + 1);
    rep(i, 1, n) {
        F[i] = max(F[i], F[i - 1]);
        F[mx[i]] = max(F[mx[i]], F[i - 1] + S[i]);
    }
    cout << F[n] << '\n';
}
```

---

## 作者：信息向阳花木 (赞：5)

$f_i$ 表示在第 $i$ 点喂猫的最大数量。

显然 $f_i$ 由前一个喂猫点转移过来。记录所有线段中可以覆盖点 $i$ 的最小左端点值，记为 $l$。前一个喂猫点的范围就是 $[1,l-1]$。预处理按线段右端点排序，记一个后缀最小值，求的时候直接二分就可以了。

然后算一下第 $i$ 点能喂多少只猫。计算一下有多少条线段覆盖了点 $i$，直接差分，记为 $cnt_i$。

转移方程：$f_i \gets \max\{f_{i-1}, f_{l-1} + cnt_i\}$。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef pair<int, int> PII;

const int N = 1000010;

#define x first
#define y second

int t, n, m;
int b[N], minn[N], f[N], premax[N], ed[N];
PII a[N];

bool cmp(PII p, PII q)
{
	return p.y < q.y;
}

int main()
{
	scanf("%d", &t);
	while (t -- )
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i ++ ) b[i] = f[i] = 0;
		for (int i = 1; i <= m; i ++ )
			scanf("%d%d", &a[i].x, &a[i].y);
		sort(a + 1, a + m + 1, cmp); // 按右端点从小到大排序
		minn[m + 1] = 0x3f3f3f3f;
		for (int i = m; i >= 1; i -- )
		{
			minn[i] = min(minn[i + 1], a[i].x); // 后缀最小值
			ed[i] = a[i].y; // 从小到大的右端点值
		}
		for (int i = 1; i <= m; i ++ )
		{
			int l = a[i].x, r = a[i].y;
			b[l] ++; b[r + 1] --;
		}
		for (int i = 1; i <= n; i ++ ) b[i] += b[i - 1]; // 差分求点 i 被几条线段覆盖
		for (int i = 1; i <= n; i ++ )
		{
			int p = lower_bound(ed + 1, ed + m + 1, i) - ed, l = i;
			// p 是第一个右端点大于等于 i 的线段编号，可能覆盖 i 的线段最小左端点是 minn[p]
			if(ed[p] >= i && minn[p] <= i) l = minn[p];
			f[i] = max(f[i - 1], b[i] + f[l - 1]);
		}
		printf("%d\n", f[n]);
	}
	return 0;
}
```

---

## 作者：H2ptimize (赞：2)

![](https://cdn.luogu.com.cn/upload/image_hosting/2gjwtjqr.png)

现在能写了。

---
考虑 dp 做法。

在读入数据之后，我们下意识地对每条线段 $(l_i,r_i)$ 进行排序。随后经过尝试，我们可以排除以猫的编号为阶段进行 dp 的方案。因此我们选择以位置为阶段进行 dp。

设 $dp(i,0/1)$ 表示位置 $i$ 是否投喂能获得的最大价值。有转移方程（注意 $dp(i,1)$ 进行了一步推导）：

$$
\begin{cases}
dp(i,0)=\max(dp(i-1,0),dp(i-1,1))\\
dp(i,1)=\max(dp(lp_i-1,0),dp(lp_i-1,1))+cnt=dp(lp_i,0)+cnt
\end{cases}
$$

其中，$lp_i$ 表示所有覆盖位置 $i$ 的线段中，左端点编号 $l$ 的最小值；如果没有线段覆盖，$lp_i=i$。$cnt$ 表示覆盖位置 $i$ 的线段条数。

$lp$ 可用双指针进行处理，$cnt$ 可用差分进行处理。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int MAXN=1e6+10;

int t,n,m,dp[MAXN][2],diff[MAXN],lp[MAXN];
pair<int,int>cat[MAXN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(int i=0;i<=n+5;i++)dp[i][0]=dp[i][1]=diff[i]=0;
		for(int i=1;i<=m;i++)cin>>cat[i].first>>cat[i].second;
		sort(cat+1,cat+m+1);
		for(int i=1;i<=m;i++)
		{
			diff[cat[i].first]++;
			diff[cat[i].second+1]--;
		}
		int j=1;
		for(int i=1;i<=n;i++)
		{
			if(i<cat[j].first)lp[i]=i;
			if(cat[j].first<=i&&i<=cat[j].second)lp[i]=cat[j].first;
			while(cat[j].second<i&&j<=m)j++;
			if(j>m)lp[i]=i;
			else lp[i]=cat[j].first;
		}
		int cnt=0;
		for(int i=1;i<=n;i++)
		{
			cnt+=diff[i];
			dp[i][0]=max(dp[i-1][0],dp[i-1][1]);
			dp[i][1]=dp[lp[i]][0]+cnt;
		}
		cout<<max(dp[n][0],dp[n][1])<<'\n';
	}
	return 0;
}
```

---

## 作者：2huk (赞：2)

### Desciption

数轴上有 $n$ 个点和 $m$ 条线段 $[l_i, r_i]$。

你会删掉若干条线段。接下来你需要在 $1 \sim n$ 中选择几个整数点，使得剩下的线段中没有一条线段覆盖两个及以上选中点。

求最多的剩下的线段数量。

$1 \le n \le 10^6$，$1 \le m \le 2 \times 10^5$。

### Solution

设 $f_i$ 表示如果只在 $1 \sim i$ 中选点，最多能剩下几条线段。转移枚举点 $i$ 选与不选，有：
$$
f_i = \max(f_{i - 1}, f_{L_i - 1} + V_i)
$$
其中 $L_i$ 表示所有包含点 $i$ 的线段中左端点的最小值，$V_i$ 表示有多少条线段覆盖了点 $i$。

这样做的原因是，如果我们选择了点 $i$，那么所有覆盖 $i$ 的线段所覆盖的其它点我们就都不能选了。所以记录最靠左的这个点 $L_i$，从 $f_{L_i - 1}$ 转移过来即可。

所以我们只需要预处理 $L_i, V_i$。

每添加一条线段 $[l_i, r_i]$，相当于所有的 $V_i(l \le i \le r)$ 都加一。先维护差分数组最后再求一遍前缀和即可。

$L_i$ 可以用递推的方式来求。初始化所有 $L_i \gets \infty$。接下来对于一条线段 $[l_i, r_i]$，很显然有 $L_{r_i} = l_i$。然后递推 $L_i \gets \min(L_i, L_{i + 1})$。

最后答案为 $f_n$。

### Code

```cpp
int lft[N], f[N], s[N];

int solve() {
	int n = read(), m = read();
	
	fup (i, 0, n + 1) {
		lft[i] = N;
		f[i] = s[i] = 0;
	}
	
	fup (i, 1, m) {
		int l = read(), r = read();
		++ s[l], -- s[r + 1];
		lft[r] = min(lft[r], l);
	}
	
	fdw (i, n - 1, 0) lft[i] = min(lft[i], lft[i + 1]);
	
	 db(lft + 1, lft + n + 1);
	
	fup (i, 1, n) s[i] += s[i - 1];
	
	fup (i, 1, n) {
		if (lft[i] == N) f[i] = f[i - 1] + s[i];
		else f[i] = max(f[i - 1], f[lft[i] - 1] + s[i]);
	}
	
	return f[n];
}
```


---

## 作者：zhuweiqi (赞：1)

数据结构优化 dp 好题。

本题解的核心做法为 dp。具体地，$f_i$ 表示第 $i$ 步一定喂一次猫时的答案，我们首先需要在所有 $i\leq r_j$（$1\leq j\leq m$）的条件中找到 $l_j$ 的最小值（设为 $R$），此部分可以用优先队列维护（按 $l_j$ 排序，如果队顶的 $r_j<i$ 则弹出），接着就是方程式的转移：$f_i=\max\{f_1,f_2,\dots,f_{R-1}\}+c_i$，后者 $c_i$ 表示饲养时间包含 $i$ 这个时间点的猫的总数，用差分预处理出并不难，前者则可以单独开一个数组来存 $maxs_i=\max\{f_1,f_2,\dots,f_i\}$，最后输出 $maxs_n$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int N=1e6+5;
int c[N],f[N],maxs[N];
priority_queue<pii,vector<pii>,greater<pii>> q;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n,m,sum=0;
		cin>>n>>m;
		for(int i=0;i<=n;i++) c[i]=0;
		while(!q.empty()) q.pop();
		while(m--){
			int x,y;
			cin>>x>>y;
			c[x]++,c[y+1]--;
			q.push({x,y});
		}
		for(int i=1;i<=n;i++){
			c[i]+=c[i-1];
			while(!q.empty() && q.top().second<i) q.pop();
			if(q.empty()) f[i]=maxs[i-1];
			else f[i]=maxs[min(q.top().first,i)-1]+c[i];
			maxs[i]=max(maxs[i-1],f[i]);
		}
		cout<<maxs[n]<<"\n";
	}
	return 0;
}
```

---

## 作者：xishanmeigao (赞：1)

（[题目传送门](https://www.luogu.com.cn/problem/CF1932F)）

把每只猫活动的范围看成线段。设 $f_i$ 表示在 $i$ 点投喂能投喂的最多数量。考虑转移，对于点 $i$，记在包含点 $i$ 的所有线段中左端点的最小值为 $L$，则 $f_i=\max\limits_{j<L}\{f_j+cnt_i\}$。其中 $cnt_i$ 表示有多少条线段包含点 $i$。

$L$ 可以预处理出来，具体地，写个支持区间修改、区间取 $\min$ 的线段树即可。

$cnt_i$ 可以用差分数组实现。

对于状态转移方程，不难看出可以简单地用树状数组维护。

时间复杂度 $\mathcal{O}(Tn\log n)$。

（代码里 $n,m$ 是反过来的）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10,M=1e6+10;

int n,m,cnt[M],f[M];

#define lc(p) p<<1
#define rc(p) p<<1|1
struct SegmentTree
{
	int dat[M<<2],ad[M<<2];

	void cmin(int p,int v)
	{
		ad[p]=min(ad[p],v);
		dat[p]=min(dat[p],v);
	}

	void pushup(int p)
	{
		dat[p]=min(dat[lc(p)],dat[rc(p)]);
	}

	void spread(int p)
	{
		if(ad[p]<1e9)
		{
			cmin(lc(p),ad[p]);
			cmin(rc(p),ad[p]);
			ad[p]=1e9;
		}
	}

	void build(int p,int l,int r)
	{
		ad[p]=dat[p]=1e9;
		if(l==r)
			return dat[p]=1e9,void();
		int mid=(l+r)>>1;
		build(lc(p),l,mid);
		build(rc(p),mid+1,r);
		pushup(p);
	}

	void change(int p,int l,int r,int ql,int qr,int v)
	{
		if(ql<=l && qr>=r)
			return cmin(p,v),void();
		spread(p);
		int mid=(l+r)>>1;
		if(ql<=mid)
			change(lc(p),l,mid,ql,qr,v);
		if(qr>mid)
			change(rc(p),mid+1,r,ql,qr,v);
		pushup(p);
	}

	int ask(int p,int l,int r,int pos)
	{
		if(l==r)
			return dat[p];
		spread(p);
		int mid=(l+r)>>1;
		if(pos<=mid)
			return ask(lc(p),l,mid,pos);
		return ask(rc(p),mid+1,r,pos);
	}
}T;

struct BIT
{
	int c[M];

	void clear()
	{
		for(int i=1; i<=m; i++)
			c[i]=0;
	}

	void add(int x,int y)
	{
		for(x; x<=m; x+=(x&-x))
			c[x]=max(c[x],y);
	}

	int query(int x)
	{
		if(x<=0)
			return 0;
		int res=0;
		for(x; x; x-=(x&-x))
			res=max(res,c[x]);
		return res;
	}
}t;

void mian()
{
	scanf("%d%d",&m,&n);

	memset(cnt,0,sizeof(cnt));
	t.clear();
	T.build(1,1,m);
	for(int i=1; i<=n; i++)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		T.change(1,1,m,l,r,l);
		cnt[l]++;  cnt[r+1]--;
	}

	for(int i=1; i<=m; i++)
		cnt[i]+=cnt[i-1];

	f[0]=0;  int ans=0;
	for(int i=1; i<=m; i++)
	{
		f[i]=cnt[i];
		int L=T.ask(1,1,m,i);
		if(L>i)
			continue;
		f[i]=max(f[i],t.query(L-1)+cnt[i]);
		ans=max(ans,f[i]);
		t.add(i,f[i]);
	}

	printf("%d\n",ans);
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
		mian();

	return 0;
}
```



---

## 作者：rainygame (赞：1)

> 没切 E 切了 F……

设含 $i$ 的线段的左端点最小为 $L_i$，右端点最大为 $R_i$，那么如果有一个 $j$ 和 $i$ 同线段，当且仅当 $j \in [L_i, R_i]$。

然后就可以考虑 DP 了，设 $f_i$ 表示 $[1,i]$ 的答案，设 $v_i$ 为 $i$ 所在的线段数，那么有转移方程：

$$
f_i=\begin{cases}
f_{i-1}, & v_i=0,\\
\max\{f_{i-1},f_{L_i-1}+v_i\}, & v_i \ne 0
\end{cases}
$$

剩下的问题就是如何求 $L_i$ 和 $v_i$ 了，考虑使用 `multiset` 储存当前所有线段的左端点，到一个点就加入以它为左端点的线段，删除以它为右端点的线段即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000001
#define MAXM 200001

int t, n, m, l, r;
int f[MAXN];
vector<int> mpl[MAXN], mpr[MAXN];

int uread(){
    int x(0);
    char ch;
    while ((ch = getchar()) < 48);
    do{
        x = (x << 1) + (x << 3) + (ch ^ 48);
    }while ((ch = getchar()) > 47);
    return x;
}

signed main(){
    t = uread();
    while (t--){
        n = uread();
        m = uread();
        for (int i(1); i<=n; ++i){
            mpl[i].clear();
            mpr[i].clear();
            f[i] = 0;
        }
        for (int i(1); i<=m; ++i){
            l = uread();
            r = uread();
            mpl[l].push_back(r);
            mpr[r].push_back(l);
        }
        multiset<int> mstl;
        for (int i(1); i<=n; ++i){
            for (auto j: mpl[i]) mstl.insert(i);
            f[i] = f[i-1];
            if (mstl.size()) f[i] = max(f[i], (int)(f[*mstl.begin()-1]+mstl.size()));
            for (auto j: mpr[i]) mstl.erase(mstl.find(j));
        }
        printf("%d\n", f[n]);
    }

    return 0;
}

```


---

## 作者：Louis_lxy (赞：0)

视时间段为若干区间，记 $f(i,0/1)$ 表示第 $i$ 个时间不饲养/饲养的最大价值，记 $mx(i)=\max_{j=1}^i\max(f(i,0),f(i,1))$，$s(i)$ 表示第 $i$ 个点的覆盖区间数量，$lst$ 表示这个点能覆盖的所有区间的左端点的最小值。

则有 $f(i,0)=mx(i-1)$，$f(i,1)=mx(lst-1)+s(i)$。

然后考虑计算 $lst$，容易发现这是经典贪心，跟 CSP-S2024 T2 差不多（有点区别），直接对左端点排序然后暴力扫就可以了。

最后就是计算 $s$，直接差分就好了。

---

## 作者：Harrylzh (赞：0)

一道较水的 DP。

## 思路

考虑对于每个点 $i$，设 $f_i$ 为从 $1$ 走到 $i$ 喂的最大数量。因为需要求这个位置多喂了多少，所以需要求出每个点喂的数量，记为 $c_i$。因为转移时不能重复计算同一个区间，需要求出在这个点前面最晚的，不会喂在 $i$ 点喂过的猫的点。换句话说，覆盖 $i$ 点的区间中左端点的最小值是要喂 $i$ 点喂过的猫中最早的一个，那么这个点前面一个点肯定不会与 $i$ 点重复，记为 $a_i$。

$c_i$ 很好求，维护一个差分数组再求前缀和即可。把区间按照 $l_i$ 排序，遍历每个区间，$r_i$ 比 $r_{i-1}$ 多延伸出去的部分的 $a$ 值都为 $l_i$。

求出这两个数组之后，我们可以写出状态转移方程：

$$f_i=\max(f_{i-1},f_{a_i-1}+c_i)$$

其中两种情况分别为选和不选这个点。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
struct node{long long l,r;}v[1000000+5];
bool cmp(node x,node y){return x.l<y.l;}
long long a[1000000+5],b[1000000+5],c[1000000+5];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long t;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		for(long long i=1;i<=n;i++) c[i]=0;
		for(long long i=1;i<=m;i++) cin>>v[i].l>>v[i].r,c[v[i].r+1]--,c[v[i].l]++;
		for(long long i=1;i<=n;i++) c[i]+=c[i-1];
		sort(v+1,v+m+1,cmp);
		long long cur=0;
		for(long long i=1;i<=m;i++)
		{
			for(long long j=max(cur+1,v[i].l);j<=v[i].r;j++)
			{
				a[j]=v[i].l;
			}
			cur=max(cur,v[i].r);
		}
		long long ans=0;
		for(long long i=1;i<=n;i++)
		{
			b[i]=max(b[i-1],b[a[i]-1]+c[i]);
			ans=max(ans,b[i]);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：lyt_cg (赞：0)

区间问题，一眼线段树，但一眼不出来做法。

转而考虑二分，符合二分的条件，但感觉 check 很难写甚至写不出。

考虑 dp，设 $f[i]$ 表示在前 $i$ 个点喂猫，能喂猫的数量的最大值。

考虑划分，$f[i]$ 可以分成两部分，在第 $i$ 个点喂/不喂。

在第 $i$ 个点不喂时：$f[i] = f[i-1]$；

在第 $i$ 个点喂时：$f[i] = f[t-1] + \text{cnt}[i]$；

其中 $t$ 表示点 $i$ 所涉及的所有线段最左边的那个点的位置。

线段树维护区间信息，所以：

$t = \text{query2}(1, i)$ （点 $i$ 涉及到的点的最左边的位置）；

$\text{cnt} = \text{query1}(1, i)$ （点 $i$ 这个点猫的数量）；

$f[i] = \max(f[i-1], f[t-1] + \text{cnt})$。

线段树维护每个点猫的数量，同时维护每个点涉及的所有线段最左边的那个点的位置。

区间修改，单点查询。

每个节点维护 $\text{sum}$，和 $\text{mn}$ 值（最左边的位置）。

只有子节点的信息有效。

（可以不用 pushup，不过无所谓）。

```
#include<bits/stdc++.h>
#define lc u<<1
#define rc u<<1|1
using namespace std;

const int N=1e6+10,M=2e5+10;

struct Node{
    int l,r,sum,mn,add,lazy;
}tr[4*N];

void pushup(int u){
    tr[u].sum=tr[lc].sum+tr[rc].sum;
    tr[u].mn=min(tr[lc].mn,tr[rc].mn);
}

void pushdown(int u){
    auto &rt=tr[u],&L=tr[lc],&R=tr[rc];
    if(rt.add){
        L.add+=rt.add;
        R.add+=rt.add;
        L.sum+=(L.r-L.l+1)*rt.add;
        R.sum+=(R.r-R.l+1)*rt.add;
        rt.add=0;
    }
    L.lazy=min(L.lazy,rt.lazy);
    R.lazy=min(R.lazy,rt.lazy);
    L.mn=min(L.mn,rt.lazy);
    R.mn=min(R.mn,rt.lazy);
    rt.lazy=0x3f3f3f3f;
}

void build(int u,int l,int r){
    if(l==r) tr[u]={l,r,0,l,0,0x3f3f3f3f};
    else{
        tr[u]={l,r,0,l,0,0x3f3f3f3f};
        int mid=l+r>>1;

        build(lc,l,mid);
        build(rc,mid+1,r);
        pushup(u);
    }
}

void modify1(int u,int l,int r,int k){
    if(l<=tr[u].l && tr[u].r<=r){
        tr[u].add+=k;
        tr[u].sum+=(tr[u].r-tr[u].l+1)*k;
    }
    else{
        pushdown(u);
        int mid=tr[u].l+tr[u].r>>1;
        if(l<=mid) modify1(lc,l,r,k);
        if(r>mid) modify1(rc,l,r,k);
        pushup(u);
    }
}

void modify2(int u,int l,int r,int k){
    if(l<=tr[u].l && tr[u].r<=r){
        tr[u].lazy=min(tr[u].lazy,k);
        tr[u].mn=min(tr[u].mn,k);
    }
    else{
        pushdown(u);
        int mid=tr[u].r+tr[u].l>>1;
        if(l<=mid) modify2(lc,l,r,k);
        if(r>mid) modify2(rc,l,r,k);
        pushup(u);
    }
}
//查询当前点猫的数量
int query1(int u,int x){
    if(tr[u].l==tr[u].r && tr[u].r==x) return tr[u].sum;
    else{
        pushdown(u);
        int mid=tr[u].l+tr[u].r>>1;
        if(x<=mid) return query1(lc,x);
        else return query1(rc,x);
    }
}

int query2(int u,int x){
    if(tr[u].l==tr[u].r && tr[u].r==x) return tr[u].mn;
    else{
        pushdown(u);
        int mid=tr[u].l+tr[u].r>>1;
        if(x<=mid) return query2(lc,x);
        else return query2(rc,x);
    }
}

void solve(){
    int n,m;
    cin>>n>>m;
    build(1,1,n);

    for(int i=1;i<=m;i++){
        int l,r;
        cin>>l>>r;
        modify1(1,l,r,1);
        modify2(1,l,r,l);
    }

    vector<int>f(n+10);
    for(int i=1;i<=n;i++){
        f[i]=f[i-1];
        int t=query2(1,i)-1;
        f[i]=max(f[i],f[t]+query1(1,i));
    }
    cout<<f[n]<<endl;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int ct=1;
    cin>>ct;
    while(ct--){
        solve();
    }
    return 0;
}
```

---

## 作者：IGA_Indigo (赞：0)

## 题目大意
喂猫，在每只猫的区间内任意一个点喂猫就可以喂到这只猫，一共有 $n$ 次喂猫机会和 $m$ 只猫，猫被喂两次就会撑死，问最多能喂多少只猫且不让猫死亡。
## 大体思路
明显是动态规划。
### 状态设置
$f_{i,j}$ 表示在第 $i$ 个点喂或不喂猫得到的最大值。
### 状态转移
$f_{i,0}=\max(f_{i-1,0},f_{i-1,1})$；

设所有覆盖此点的线段中最小的 $l$ 为 $minl$，覆盖此点的线段数为 $nu$。

$f_{i,1}=f_{minl,0}+nu$。

解释：当第 $i$ 天选的时候，第 $minl$ 天必不能选，我们还能同时喂 $minl$ 只猫，即可得到此转移方程。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int> c[1000005];
int nu[1000005];
int minl[1000005];
int f[1000005][2];
int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=m;i++){
			cin>>c[i].first>>c[i].second;
		}
		for(int i=0;i<=n+1;i++){
			nu[i]=0;
			minl[i]=0;
			f[i][0]=0;
			f[i][1]=0;
		}
		sort(c+1,c+1+m);//按右端点从小到大排的话后面好处理左端点先后 
		for(int i=1;i<=m;i++){
			nu[c[i].first]++;
			nu[c[i].second+1]--;//差分一下他 
		}
		for(int i=1;i<=n+1;i++){
			nu[i]+=nu[i-1];//前缀和回来 
		}
		int lj=1;
		for(int i=1;i<=n;i++){
			if(i<c[lj].first){//没赶上区间的话 
				minl[i]=i; //直接赋值成自己 
			}
			if(c[lj].first<=i&&i<=c[lj].second){//这个点被区间所包含 
				minl[i]=c[lj].first;//最早的赋值成他 
			}
			while(c[lj].second<i&&lj<=m){//区间被落在后面了 
				lj++;//往后推一个区间 
			}//这时候我们就发现按右端点从小到大排的好处了 
			if(c[lj].second<i&&lj==m){//满足条件但是lj动不了了 
				minl[i]=i;//又赋值成自己 
			}
			if(i<c[lj].first){//再跑一遍刚刚的，免得有的minl没赋值 
				minl[i]=i;
			}
			if(c[lj].first<=i&&i<=c[lj].second){ 
				minl[i]=c[lj].first;
			}
		}
		for(int i=1;i<=n;i++){
			f[i][0]=max(f[i-1][0],f[i-1][1]);
			f[i][1]=f[minl[i]][0]+nu[i]; 
		}//上文的状态转移方程
		cout<<max(f[n][0],f[n][1])<<endl;
	}
	return 0;
}
```

---

## 作者：2020kanade (赞：0)

题目： 
[CF1932F](https://www.luogu.com.cn/problem/CF1932F)

赛时在不熟悉 ```std::vector``` 的情况下没调出来。

非常好 XCPC 区域赛签到 or 普及组 T4，个人的实现还算写复杂了。

原题目附赠的形式化题意已经说得非常清楚了：在一条数轴上有若干线段，要求选择若干个位置放点使每条线段中至多有一个点，最大化包含点的线段数量。

显然放点的顺序不影响结果，我们强行从左到右来，考虑什么时候能在某个位置放点：要求任何线段最多只包含一个点，因此如果包含当前位置的线段在之前已经被放了点，这里就不能放点；反之，这里可以放点的充要条件是，上一次放点的位置在本次放点所波及到的所有线段的左端点之前。

这一步的话，我们把所有线段按左端点为第一关键字排序，放在数轴上扫，动态维护覆盖当前点的线段中最小左端点，对于第 $i$ 个点的这个值记为 $lim_i$，显然如果要在第 $i$ 个位置合法地放点，上次放点的位置应当 $\lt lim_i$；此外，$lim_i$ 随 $i$ 单调不降，因为整个过程中维护的最小左端点显然是单调不降的。

之后，如果在某个合法位置放点，贡献显然是有多少条线段覆盖了这个点，设第 $i$ 个位置的这个值为 $val_i$，求它的话差分一下即可。

到这里，考虑动态规划：$f_i$ 为从左到右放点的过程中进行到位置 $i$ 并且强制在此处放点时的答案，有转移方程 $f_i=\max_{j\lt\min\{lim_i,i\}}\{f_j\}+val_i$。

直接暴力转移显然平方复杂度，注意前继是一个前缀最大值，且 $lim_i$ 随 $i$ 单调不降，也就是说前缀是单向扩展的，直接再拿一个单向右移的指针根据 $lim_i$ 扩展合法前缀，一边扫一边取最大值即可，完全不需要线段树之类。

这边的实现时间复杂度是 $\Theta(\sum n+\sum m \log n)$，实现精细点可以完全线性。

顺便说句闲话，代码里模板的 F-word 源自一个悲伤的故事，以后不要问了，会伤心的。

```cpp
//written by Amekawa_kanade
#pragma G++ optimize(2)
#include<bits/stdc++.h>
using namespace std;
void syncoff()//fuck you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
#define endl '\n'
const int N=1e6+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll JT=998244353;
const ll GEH=1e9+7;
const ll ZLH=1e9+9;
int t,n,k,m,q;
set<int> lll[N],rrr[N];
void solve()
{
	cin>>n>>m;
	vector<pair<int,int> > a(m+3),area(n+3);
	vector<ll> val(n+3,0),dp(n+3,0);
	vector<int> plim(n+3,0);
	for(int i=1;i<=m;++i) cin>>a[i].first>>a[i].second;
	sort(a.begin()+1,a.begin()+1+m);
	multiset<int> lp,rp;
	for(int i=1;i<=m;++i) lll[a[i].first].insert(i),rrr[a[i].second+1].insert(i);
	for(int i=1;i<=n;++i)
	{
		for(auto x:lll[i]) lp.insert(a[x].first),rp.insert(a[x].second);
		for(auto x:rrr[i]) lp.erase(lp.find(a[x].first)),rp.erase(rp.find(a[x].second));
		val[i]=lp.size();int llim=0,rlim=0;
		if(lp.size()) llim=*lp.begin();
		if(rp.size()) rlim=*rp.rbegin();
		area[i]={llim,rlim};
	}
	int npre=0;
	for(int i=1;i<=n;++i)
	{
		if(area[i].first==0&&area[i].second==0) continue;
		while(npre<i-1&&area[npre+1].second<i) ++npre;
		plim[i]=npre;
	}
	//for(int i=1;i<=n;++i) cout<<area[i].first<<' '<<area[i].second<<endl;
	//for(int i=1;i<=n;++i) cout<<plim[i]<<' ';cout<<endl;
	//return;
	//f[i]=\max{f[j]}+val[i],1<=j<=plim
	ll nmp=0;int npr=0;
	for(int i=1;i<=n;++i)
	{
		if(val[i]==0) continue;
		while(npr+1<=plim[i]) ++npr,nmp=max(nmp,dp[npr]);
		dp[i]=val[i]+nmp;
	}
	ll ans=0;
	for(int i=1;i<=n;++i) ans=max(ans,dp[i]);cout<<ans<<endl;
	for(int i=1;i<=n+1;++i) lll[i].clear(),rrr[i].clear();
}
int main()
{
    syncoff();
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：SamHJD (赞：0)

## [Feed Cats](https://www.luogu.com.cn/problem/CF1932F)

### Description

二维数轴上有一些线段，对于 $i\in[1,n]$，你可以选择给所有经过 $i$ 的线段打上标记。一条线段不能被打上超过一个标记。

求最多能给几条线段打上标记。

### Solution

设 $f_i$ 为前 $i$ 个位置的答案，$l_i$ 为经过 $i$ 的线段左端点的最小值，$d_i$ 为经过 $i$ 的线段的个数，则有转移：

$$f_i=\begin{cases}f_{i-1}\\f_{l_i-1}+d_i\end{cases}$$

$l$ 可以用线段树处理。

### Code

```cpp
#include "bits/stdc++.h"
#define ls p*2
#define rs p*2+1
using namespace std;
template<typename T>
inline void read(T &x){
	x=0;int f=1;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	x*=f;
}
const int N=1e6+10,INF=0x3f3f3f3f;
struct SegmentTree{
	struct node{
		int l,r,mn,tag;
	}t[N*4];
	void build(int p,int l,int r){
		t[p].l=l;t[p].r=r;t[p].mn=INF;t[p].tag=INF;
		int mid=(l+r)>>1;
		if(l==r) return;
		build(ls,l,mid);
		build(rs,mid+1,r);
	}
	void pushup(int p){t[p].mn=min(t[ls].mn,t[rs].mn);}
	void lazy(int p,int k){t[p].mn=min(t[p].mn,k);t[p].tag=min(t[p].tag,k);}
	void pushdown(int p){lazy(ls,t[p].tag);lazy(rs,t[p].tag);t[p].tag=INF;}
	void upd(int p,int nl,int nr,int k){
		if(nl<=t[p].l&&t[p].r<=nr){lazy(p,k);return;}
		if(t[p].tag!=INF) pushdown(p);
		if(t[ls].r>=nl) upd(ls,nl,nr,k);
		if(t[rs].l<=nr) upd(rs,nl,nr,k);
		pushup(p);
	}
	int query(int p,int x){
		if(t[p].l==t[p].r) return t[p].mn;
		if(t[p].tag!=INF) pushdown(p);
		if(x<=t[ls].r) return query(ls,x);
		else return query(rs,x);
	}
};
int T,n,m,d[N],f[N];
struct CAT{
	int l,r;
}cat[N];
void solve(){
	read(n);read(m);
	SegmentTree t;
	t.build(1,1,n);
	for(int i=1;i<=n;++i) d[i]=0,f[i]=0;
	for(int i=1;i<=m;++i){
		read(cat[i].l),read(cat[i].r);
		d[cat[i].l]++;d[cat[i].r+1]--;
		t.upd(1,cat[i].l,cat[i].r,cat[i].l);
	}
	for(int i=1;i<=n;++i) d[i]+=d[i-1];
	for(int i=1;i<=n;++i){
	    f[i]=f[i-1];
	    if(d[i]==0 || t.query(1,i)>n) continue;
		f[i]=max(f[i],f[t.query(1,i)-1]+d[i]);
	}
	printf("%d\n",f[n]);
}
int main(){
	read(T);while(T--) solve();
	return 0;
}
```

---

## 作者：Cure_Wing (赞：0)

[CF1932F Feed Cats](https://www.luogu.com.cn/problem/CF1932F)

### 思路

我们记录下在第 $i$ 个时间能喂养的猫的只数，记作 $cnt_i$，这个可以差分解决。同时记 $[L_i,R_i]$ 表示在这个时间喂猫后不能喂猫的时间区间。

同时我们看到时间的流动是单向的，于是设 $f_i$ 表示到第 $i$ 个时间为止，强制在第 $i$ 个时间喂猫，可以喂的最多的猫数。

转移方程很好写：$f_i=(\max\limits_{j=1}^{L_i-1}f_j)+cnt_i$。

暴力转移是 $O(n^2)$ 的。但是考虑到我们是按时间枚举的，所以可以选择的区间肯定是不断向右增大的。于是我们暴力维护 `dp` 前缀最大值 $pre$。具体的，我们对于每一个时间点 $i$，当它等于一个区间 $L_j$ 时，把它标记在 $R_j$ 上，让它在这个时候解封。同时解封所有 $R_j=i$ 的 $L_j$，并且检验如果所有的 $L_j$ 的标记都已取消，那么就让 $\max\{f_{R_j},pre\}\to pre$，因为此时 $L_j$ 一定可取，且不会被再次封闭。


时间复杂度 $O(\sum(n+m))$。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using std::cin;using std::cout;
constexpr int N=1000006,M=200005;
int t,n,m,f[N],cnt[N],tot[N],ans,pre,last;
struct A{int l,r;}a[M];
std::queue<int>q;
std::vector<int>in[N],out[N];
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;cout<<ans<<'\n'){
		cin>>n>>m;ans=pre=last=0;
		for(int i=1;i<=n;++i){tot[i]=0;out[i].clear();in[i].clear();}//多测不清空，爆零两行泪
		for(int i=1;i<=m;++i){cin>>a[i].l>>a[i].r;++tot[a[i].l];--tot[a[i].r+1];in[a[i].l].push_back(a[i].r);}//差分
		for(int i=1;i<=n;++i) tot[i]+=tot[i-1];//计算和
		for(int i=1;i<=n;++i){
			for(;!q.empty()&&cnt[q.front()];q.pop()) --cnt[q.front()];//弹出已解封的
			for(int j=last+1;j<=(q.empty()?i:q.front())-1;++j) pre=std::max(pre,f[j]);//可取范围一定小于未解封
			last=(q.empty()?i:q.front())-1;
			for(int j:in[i]){q.push(i);out[j].push_back(i);}//标记
			ans=std::max(ans,f[i]=pre+tot[i]);//转移
			for(int j:out[i]) ++cnt[j];//解封标记
		}
	}
	return 0;
}
```

---

## 作者：_Z_F_R_ (赞：0)

### 题意

有 $N$ 个区间 $[l_i, r_i]$。可以在一些时刻 $x$ 选定所有满足 $l_i \le x \le r_i$ 的区间。不可以选一个区间两次。问最多能选定多少个区间。

### 题解

考虑对于每个时刻 DP。设 $f_i$ 表示选 $i$ 时刻且满足要求的最多能选的区间总数，则：
$$f_i = \max_{r_j' < i}\{f_j\} + cur_i$$
其中 $r_j'$ 表示所有包含时刻 $j$ 的区间的 $r_i$ 的最大值，$cur_i$ 表示有多少个包含时刻 $i$ 的区间。

对于本题，$O(M^2)$ 显然不行，考虑用线段树优化 DP，每次 DP 后在 $r_i'$ 修改为原答案与 $f_i$ 的最大值，就可以做到 $O(M \log_2 M)$ 了。

赛时 Code：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll Read() {
	int sig = 1;
	ll num = 0;
	char c = getchar();
	while(!isdigit(c)) {
		if(c == '-') {
			sig = -1;
		}
		c = getchar();
	}
	while(isdigit(c)) {
		num = (num << 3) + (num << 1) + (c ^ 48);
		c = getchar();
	}
	return num * sig;
}
void Write(ll x) {
	if(x < 0) {
		putchar('-');
		x = -x;
	}
	if(x >= 10) {
		Write(x / 10);
	}
	putchar((x % 10) ^ 48);
}
const int N = 200005;
struct Cat {
	int l, r;
	friend bool operator <(Cat x, Cat y) { // 先按左端点，再按右端点排序
		return (x.l ^ y.l) ? x.l < y.l : x.r < y.r;
	}
}a[N];
int n, m, cur[N * 5], maxr[N * 5], f[N * 5]; // maxr 即为 r'
struct SegTree { // 简单的单点修改 + 区间最大线段树
	struct tNode {
		int l, r;
		ll maxn;
	}tree[N << 5];
	void PushUp(int x) {
		tree[x].maxn = max(tree[x << 1].maxn, tree[x << 1 | 1].maxn);
	}
	void Build(int x, int l, int r) {
		tree[x].l = l, tree[x].r = r;
		if(l == r) {
			tree[x].maxn = 0;
			return ; 
		}
		int mid = (l + r) >> 1;
		Build(x << 1, l, mid);
		Build(x << 1 | 1, mid + 1, r);
		PushUp(x);
	}
	void Modify(int x, int mp, ll num) {
		int l = tree[x].l, r = tree[x].r;
		if(l == r) {
			tree[x].maxn = max(num, tree[x].maxn); // 注意取 max
			return ;
		}
		int mid = (l + r) >> 1;
		if(mp <= mid) {
			Modify(x << 1, mp, num);
		}
		else {
			Modify(x << 1 | 1, mp, num);
		}
		PushUp(x);
	}
	ll Query(int x, int ql, int qr) {
		if(ql > qr) {
			return 0;
		}
		int l = tree[x].l, r = tree[x].r;
		if(ql <= l && r <= qr) {
			return tree[x].maxn;
		}
		int mid = (l + r) >> 1;
		ll res = 0;
		if(ql <= mid) {
			res = max(res, Query(x << 1, ql, qr));
		}
		if(qr > mid) {
			res = max(res, Query(x << 1 | 1, ql, qr));
		}
		return res;
	}
}segtree;
int main() {
	int testcase;
	scanf("%d", &testcase);
	while(testcase--) {
		int i;
		n = Read(), m = Read();
		for(i = 1; i <= m; i++) {
			a[i].l = Read(), a[i].r = Read();
		}
		sort(a + 1, a + m + 1);
		int j = 1, ans = 0;
		/* 一个大根堆（q），一个小根堆（q2） */
		priority_queue<int> q;
		priority_queue<int, vector<int>, greater<int> > q2;
		for(i = 1; i <= n; i++) {
			while(j <= m && a[j].l <= i) {
				q.push(a[j].r);
				q2.push(a[j].r);
				j++;
			}
			while(!q2.empty() && q2.top() < i) { // r_j < i 说明区间 j 一定不包括 i
				q2.pop();
			}
			cur[i] = q2.size();
			if(!q.empty() && q.top() >= i) { // 若当前所有左端点小于 i 的区间的最大值大于等于 i，有解
				maxr[i] = q.top();
			}
			else { // 否则无解，r_i' = n 时可以证明不会从 i DP 到任何一个数
				maxr[i] = n;
			}
		}
		segtree.Build(1, 1, n);
		for(i = 1; i <= n; i++) {
			f[i] = segtree.Query(1, 1, i - 1) + cur[i];
			ans = max(ans, f[i]);
			segtree.Modify(1, maxr[i], f[i]);
		}
		Write(ans), putchar('\n');
	}
	return 0;
}
```

---

## 作者：Linge_Zzzz (赞：0)

# 形式化题意

在长为 $n$ 的空间里有 $m$ 条线段 $l_i,r_i$，你需要在这个空间中选定一些点，使得没有一条线段包含两个或以上个被选定的点，在此基础上让包含选定的点的线段个数最多。

数据范围：$n \leq 10^6,m\leq 2\times 10^5$。

# 题解

考虑线性 dp。

设 $f_i$ 为 $i$ 被选定时的最多线段数，考虑转移。

注意到 $i$ 被选定，则 $i$ 到 $\min_{i\in [l_j,r_j]}\{l_j\}$ 都是不可选定的，同时所有包含点 $i$ 的线段都会被覆盖到。

记 $g_i$ 为 $\min_{i\in [l_j,r_j]}\{l_j\}$，$cnt_i$ 为点 $i$ 可以覆盖到的线段数，则有：

$$ f_i = \max_{j=1}^{g_i-1}\{f_j+cnt_i\} $$

把常量提出来，得到：

$$ f_i = \max_{j=1}^{g_i-1}\{f_j\}+cnt_i $$

容易发现前半部分可以单纯地用一个前缀最大和来解决，后半部分可以提前预处理。

$cnt_i$ 就是一个区间加和计数，可以使用差分解决。

$g_i$ 可以使用一个维护最小值的区间修改，单点查询的线段树来解决。具体地，对于每个线段 $[l,r]$ ，对 $[l,r]$ 区间修改为 $l$。

另外要注意细节：这种线段树可以不用 $lazy$ 值，**多测清空的时候要多清空几个**。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10,M=2e5+100,INF=0x3f3f3f3f3f3f3f3f;

int n,m;
struct node{
	int val;
}t[N*4];
void pushdown(int p){
	t[p*2].val=min(t[p*2].val,t[p].val);
	t[p*2+1].val=min(t[p*2+1].val,t[p].val);
}
void build(int p,int l,int r){
	t[p].val=INF;
	if(l==r)return;
	int m=(l+r)>>1;
	build(p*2,l,m);
	build(p*2+1,m+1,r);
}
void update(int p,int l,int r,int L,int R,int val){
	if(L<=l&&r<=R){
		t[p].val=min(t[p].val,val);
		return;
	}
	int m=(l+r)>>1;
	pushdown(p);
	if(L<=m)update(p*2,l,m,L,R,val);
	if(R>m)update(p*2+1,m+1,r,L,R,val);
}
int query(int p,int l,int r,int pos){
	if(l==r)return t[p].val;
	int m=(l+r)>>1;
	pushdown(p);
	if(pos<=m)return query(p*2,l,m,pos);
	else return query(p*2+1,m+1,r,pos);
}
int f[N],mx[N],cnt[N];
void solve(){
	int ans=0;
	cin>>n>>m;
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int l,r;
		cin>>l>>r;
		update(1,1,n,l,r,l);
		cnt[l]++;
		cnt[r+1]--;
	}
	for(int i=1;i<=n;i++){
		cnt[i]+=cnt[i-1];
	}
	for(int i=1;i<=n;i++){
		int l=query(1,1,n,i);
		if(l==INF)l=1;
		f[i]=mx[l-1]+cnt[i];
		ans=max(ans,f[i]);
		mx[i]=max(f[i],mx[i-1]);
	}
	memset(f,0,sizeof(int)*n+50);
	memset(mx,0,sizeof(int)*n+50);
	memset(cnt,0,sizeof(int)*n+50);
	cout<<ans<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t;cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

