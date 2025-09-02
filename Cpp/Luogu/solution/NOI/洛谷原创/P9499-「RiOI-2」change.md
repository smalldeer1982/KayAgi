# 「RiOI-2」change

## 题目背景

小 E 终于在今天收回了被妈妈保管的压岁钱。

作为有远见的收藏家，小 E 知道，如果她从现在开始收集东西，以后就会变得值钱了。

小 E 的世界里有一些纸币。她知道这些纸币未来的价值，但遗憾的是，这些纸币只能从小换到大。如何是好？

## 题目描述

给定 $n$ 种物品，每种物品 $i$ 价值为 $v_i$，个数为 $c_i$。

定义总价值为 $\sum\limits_{i=1}^nc_iv_i$，你可以进行一些（可能为 $0$）次操作来最大化总价值。

一次操作为：选定一个 $i$ 满足 $c_i \geq x_i$，让 $c_i\gets c_i - x_i$，$c_{i+1}\gets c_{i+1}+ 1$。

输出最大的总价值对 $998,\!244,\!353$ 取模。

**注意，你需要最大化总价值，再对 $998,\!244,\!353$ 取模，而不是最大化「总价值对 $998,\!244,\!353$ 取模的值」。**

## 说明/提示

### 样例解释

对于样例的第一组数据，$v=[1,5]$，$c=[5,1]$，$x=[4]$。可以选定 $i=1$ 进行一次操作，此时 $c=[1,2]$，总价值为 $1\cdot 1+5\cdot 2=11$，可以证明它是最大的。

### 数据规模与约定

**本题采用捆绑测试。**

下面是各 Subtask 的特殊性质，斜杠表示该栏无特殊限制。

|$\text{sid}=$| $\sum n\le$ | $c_i,v_i\le$ | 特殊性质 |分值|
| :-: | :---------: | :----------: | :------: | :-: |
| $1$ | / | / | 特殊性质 A | $5$ |
| $2$ | / | / | 特殊性质 B | $15$ |
| $3$ | / | / | 特殊性质 C | $15$ |
| $4$ | $300$ | $300$ | / | $15$ |
| $5$ | $2000$ | $2000$ | / | $20$ |
| $6$ | $2000$ | / | / | $15$ |
| $7$ | / | / | / | $15$ |

+ 特殊性质 A：$x_i = 10^9$。
+ 特殊性质 B：$x_i = 1$。
+ 特殊性质 C：所有 $c_i, v_i$ 均在 $[0, 10^5]$ 间均匀随机生成；所有 $x_i$ 均在 $[1, 10^5]$ 间均匀随机生成。

对于所有数据，$1\le t \le 10^5$，$2\le n$，$\sum n\le 2\times 10^5$，$1\le x_i\le 10^9$，$0\le c_i,v_i\le 10^9$。

upd：新增一组 hack 数据，$\text{sid}$ 为 $7$。

## 样例 #1

### 输入

```
0
2
2
1 5
5 1
4
10
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
11
172998509```

# 题解

## 作者：Lynkcat (赞：15)

写一个 dp 做法。

首先有一个很暴力的 dp，设 $dp_{i,j}$ 表示算完前 $i$ 个，从 $i$ 移到 $i+1$ 的个数大于等于 $j$ 个然后转移即可。

尝试直接维护这个 dp，首先我们把 $x_i=1$ 的段合并在一起，也就是说如果能通过 $x_i=1$ 一直往后移到比当前位置大的位置，那么就移。发现这样子之后 $c_i$ 不为 $0$ 的位置一定在段内的 $v_i$ 的后缀最大值处。

接下来考虑 dp 的时候我们在干什么，设 $cost_{i,k}$ 为第 $i$ 段的这些 $c_i$ 选 $k$ 个要往后移的最大贡献，$val_i$ 为第 $i$ 段的 $v$ 的最大值。那么转移是先枚举从 $i-1$ 段移过来个数 $j$，然后枚举这一段要往后移的个数 $k$，有 $dp_{i,\lfloor\frac{j+k}{x_i}\rfloor}=\max(dp_{i,\lfloor\frac{j+k}{x_i}\rfloor},dp_{i-1,j}+cost_{i,k})$，然后 $dp_{i,j}=\max(dp_{i,j},dp_{i,j+1}+v_{i+1})$。

首先可以发现 $cost_{i}$ 是一个上凸壳，所以每次的转移的第一步是一个闵可夫斯基和，可以在两个凸壳大小的和时间内完成。

接下来要做的是将坐标除以这一段最右点的 $x_i$，这个也可以在凸壳大小内完成。然后还有一步是 $dp_{i,j}=\max(dp_{i,j},dp_{i,j+1}+v_{i+1})$，这一步相当于 pop 掉凸壳前面一部分斜率大于 $v_{i+1}$ 的点，直接 pop 就行。

考虑这个做法的复杂度，除以 $x_i$ 的时候凸包上每个点的横坐标至少除以二。所以凸包大小总和大概是 $n\log v$ 级别，时间复杂度即为 $O(n\log v)$。

```c++
// Problem: T351677 「RiOI-2」change
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T351677?contestId=122187
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll __int128
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define sz(x) (int)((x).size())
#define int ll
#define N 200005
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,a[N],b[N],x[N],suf[N];
bitset<10000005>vis;
struct node
{
	vector<int>x,y;
	node()
	{
		poly().swap(x),poly().swap(y);
	}
	void ins(int a,int b)
	{
		while (x.size()>0&&a==x.back()&&b>=y.back()) x.pop_back(),y.pop_back();
		if (x.size()>0&&a==x.back()&&b<y.back()) return;
		x.push_back(a);
		y.push_back(b);
	}
	void add(int k)
	{
		int l=0;
		int mx=0;
		for (int i=1;i<x.size();i++)
		{
			mx=max(mx,y[i]+x[i]*k);
			if ((y[i]-y[i-1])/(x[i]-x[i-1])>=-k) 
			{
				l=i;
			}
		}
		if (l==0) return;
		poly xx,yy;
		xx.push_back(0);yy.push_back(mx);
		for (int i=l;i<x.size();i++)
			xx.push_back(x[i]),yy.push_back(y[i]);
		x.swap(xx);
		y.swap(yy);
	}
	void selfclr()
	{
		for (int i=0;i<x.size();i++) vis[i]=0;
		int t=0;
		for (int i=1;i+1<x.size();i++)
		{
			if ((y[i]-y[i-1])*(x[i+1]-x[i])==(y[i+1]-y[i])*(x[i]-x[i-1]))
				vis[i]=1,t=1;
		}
		if (!t) return;
		poly xx,yy;
		for (int i=0;i<x.size();i++)
			if (!vis[i])
				xx.push_back(x[i]),yy.push_back(y[i]);
		x.swap(xx);
		y.swap(yy);
	}
};
pa all[10000005];
int cnt;
node merge(node x,node y)
{
	cnt=0;
	for (int i=1;i<x.x.size();i++)
	{
		all[++cnt]=mp(x.x[i]-x.x[i-1],x.y[i]-x.y[i-1]);
	}
	for (int i=1;i<y.x.size();i++)
	{
		all[++cnt]=mp(y.x[i]-y.x[i-1],y.y[i]-y.y[i-1]);
	}
	node res;
	res.ins(0,x.y[0]+y.y[0]);
	sort(all+1,all+cnt+1,[&](pa x,pa y)
	{
		return x.se*y.fi>y.se*x.fi;
	});
	for (int i=1;i<=cnt;i++)
		res.ins(res.x.back()+all[i].fi,res.y.back()+all[i].se);
	return res;
}
void outp(node x)
{
	for (int i=0;i<x.x.size();i++)
		writesp(x.x[i]),writeln(x.y[i]);
	puts("");
}
void BellaKira()
{
	n=read();
	for (int i=1;i<=n;i++) a[i]=read();
	for (int i=1;i<=n;i++) b[i]=read();
	node dp;
	dp.x.push_back(0);
	dp.y.push_back(0);
	node st=dp;
	for (int i=1;i<n;i++) x[i]=read();
	x[n]=1;
	suf[n+1]=-1;
	for (int i=n;i>=1;i--)
	{
		suf[i]=a[i];
		if (x[i]==1) suf[i]=max(suf[i],suf[i+1]);
	}
	for (int i=1;i<n;i++)
	{
		if (x[i]==1&&suf[i+1]>=suf[i]) b[i+1]+=b[i],b[i]=0;
	}
	for (int l=1;l<=n;l++)
	{
		int r=l;
		while (r<n&&x[r]==1) r++;
		node nw=st;
		int sum=0;
		for (int i=r;i>=l;i--) sum+=a[i]*b[i];
		nw.y[0]=sum;
		for (int i=r;i>=l;i--)
			if (b[i])
			{
				nw.ins(nw.x.back()+b[i],sum-a[i]*b[i]);
				sum-=a[i]*b[i];
			}
		dp.add(suf[l]);
		nw=merge(dp,nw);
		if (r==n) 
		{
			dp=nw;
			break;
		}
		dp=node();
		dp.ins(0,nw.y[0]);
		for (int i=1;i<nw.x.size();i++)
		{
			{
				if (nw.x[i]/x[r]!=nw.x[i-1]/x[r])
				{
					dp.ins(nw.x[i]/x[r],nw.y[i]-(nw.y[i]-nw.y[i-1])*(nw.x[i]%x[r])/(nw.x[i]-nw.x[i-1]));
				}
			}
			dp.ins(nw.x[i]/x[r],nw.y[i]);
			if (i+1<nw.x.size())
			{
				if (nw.x[i+1]/x[r]!=nw.x[i]/x[r])
				{
					dp.ins(nw.x[i]/x[r]+1,nw.y[i]+(x[r]-nw.x[i]%x[r])*(nw.y[i+1]-nw.y[i])/(nw.x[i+1]-nw.x[i]));
				}
			}
		}
		dp.selfclr();
		l=r;
	}
	writeln(dp.y[0]%mod);
		
}
signed main()
{
	int id=read();
	int T=read();
	while (T--)
	{
		BellaKira();
	}
}
```

---

## 作者：喵仔牛奶 (赞：9)

来写一篇详细一点的贪心题解。

# Solution

先别管复杂度，考虑如何写一个正确的贪心。

先将所有物品的价值加到答案。按物品编号从小到大贪心，在每个位置考虑把一些物品的贡献取消，合成到这个物品后后再加上贡献。

定义一个物品的代价 $s_u$ 是合成该物品的价值之和，我们贪心里面把一些物品换成 $i$ 并不是真正把它们换过去，而是通过它们合成后的代价判断是否应该换过去。

假设现在贪完了前 $i-1$ 个物品。设一集合 $q$，存若干二元组 $(s,ct)$，一个二元组 $(s_j,ct_j)$ 表示全部换到物品 $i-1$ 后，有 $ct_j$ 个物品需要 $s_j$ 的代价。

我们在 $i$ 上贪心，第一步就是把 $q$ 中物品合成物品 $i$。我们将物品从小到大排序，每 $x_i$ 个合成一个，多余的扔掉。这样可以保证物品的代价尽可能小。

处理完后，将所有 $s_j<v_i$ 的二元组 $(s_j,ct_j)$ 的代价改为 $i$。即将他们合成为 $i$。

这样就得到了一个 $\mathcal{O}(n^2)$ 做法。

考虑优化：
- 对于 $s_j>10^{10}$ 的物品，直接丢掉。因为肯定不会有用。
- 将 $q$ 设成底大顶小的单调栈，在 $x_i=1$ 时无需合成物品，直接在单调栈上操作即可。

这样优化后，对于 $x_i>1$，二元组的代价至少翻倍，所以每个物品合成后只有 $\mathcal{O}(\log v)$ 个 $x_i>1$ 的物品会决策它。

对于 $x_i=1$，不需要合成，总弹栈次数为 $\mathcal{O}(n)$。

时间复杂度 $\mathcal{O}(n\log v)$，常数较小。

# Code
```cpp
// writer: Milkcat
// time: 2024.2.24 11:29
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef __int128 i128;
	typedef pair<i128, i128> pii;
	const int N = 1e6 + 5, mod = 998244353;
	LL n, t; i128 ans, c[N], v[N], x[N];
	vector<pii> q;
	int main() {
		cin >> n, q.clear();
		REP(i, 1, n) cin >> t, v[i] = t;
		REP(i, 1, n) cin >> t, c[i] = t;
		REP(i, 2, n) cin >> t, x[i] = t;
		q.pb(v[1], c[1]), ans = v[1] * c[1];
		REP(i, 2, n) {
			if (x[i] > 1) {
				i128 sv = 0, sc = 0; vector<pii> p;
				while (q.size()) {
					auto [s, ct] = q.back(); q.pop_back();
					if (sc > 0) {
						i128 w = min(ct, x[i] - sc);
						sc += w, sv += w * s, ct -= w;
						if (sv > 1e10) break;
						if (sc == x[i]) p.pb(sv, 1), sv = sc = 0;
						else continue;
					}
					if (s * x[i] > 1e10) break;
					p.pb(s * x[i], ct / x[i]), ct %= x[i];
					sc = ct, sv = s * ct;
				}
				reverse(p.begin(), p.end()), p.swap(q);
			}
			while (q.size() && q.back().fi < v[i]) {
				auto [s, ct] = q.back();
				ans -= s * ct, c[i] += ct, q.pop_back();
			}
			ans += c[i] * v[i], q.pb(v[i], c[i]);
		}
		cout << (LL)(ans % mod) << '\n';
		return 0;
	}
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int sid, t = 1; cin >> sid >> t;
	while (t --) Milkcat::main();
	return 0;
}
```

---

## 作者：ღꦿ࿐ (赞：4)

很典但也很妙的题。

首先有一个显然暴力的 dp：从前往后一个一个换，记录目前剩的货币的数量，$f_{i,j}$ 目前换完第换完第 $i$ 种货币，保留了 $j$ 张，可以赚到多少钱，转移如下： 

兑换货币：

$$
f_{i,\lfloor\frac{j}{x_{i-1}}\rfloor+c_i}={f_{i-1,j}}
$$

在这一步将 $k$ 张货币用于获取价值，剩下的保留换取更靠后的货币（完全背包）：

$$
f_{i,j}=\max_{0\leq k\leq j}\{f_{i,j+k}+kv\}
$$

和值域相关，需要优化，往往要把这种直接放在值域上的东西转化成分段离散的东西来维护，我们把 dp 拍平（滚动数组）观察转移是对 dp 数组进行怎样的操作：

- 在开头放 $c$ 个 $0$，整体右移。
- 从后往前，每个位置加上 $v$ 去更新前一个位置（完全背包）。
- 将数组“放缩 $x$ 倍”，即只保留 $x,2x,\dots,kx$ 这些项。

这种形态的 dp 往往都不太好维护或是直接优化转移，分析可以发现 dp 值构成了一个上凸包：

- 显然 dp 值是单调递减的，所以在开头插入一段 $0$ 不影响凸性。
- 从后往前，每个位置加上 $v$ 去更新前一个位置，等价于与数组 $\{0,v,2v,....,kv\}$ 做一个闵可夫斯基和（只不过是差卷积的形态）。
- 放缩 $x$ 倍后显然不改变凸性：其单减的差分数组上两段等长的区间，靠前那段一定和不会更小。

考虑维护这个上凸包，经典地，维护差分数组的分段函数。

前两种操作是很经典的，第一种操作直接在数组的前面插入一段 $0$，第二种操作相当于将前面一段斜率小于 $v$ 的值给弹出，换成斜率为 $v$ 的段。

第三种操作我们直接暴力完成（当 $x>1$ 时）：

对于每个原来凸包上的拐点，找到其前后第一个横坐标为 $x$ 的倍数的点称作特殊点，然后将相邻两个特殊点连起来。

两个中间有拐点的特殊点在缩放后的横坐标差为 $1$，直接计算斜率，而中间没有拐点的特殊点直接将斜率扩大 $x$ 倍即可。

下面我们来证明直接暴力完成的复杂度是正确的：

- 首先每次暴力操作会让所有点的坐标至少减半，然后两个凸包拐点的距离也会至少变成除二上取整。

- 虽然每次放缩有可能会使凸包的点数翻倍（每个点前后各取一个），但是这些距离为 $1$ 的点对在下一次放缩时一定会每组消失至少一个。

所以复杂度为 $O(n\log \sum c_i)$，常数不大。










 


---

## 作者：zhuzhu2891 (赞：4)

## 链接

[原题](https://www.luogu.com.cn/problem/T336272)
## 解法

我们从前往后遍历，遍历到每一级时考虑维护一个二元组单调队列（以花费排序），表示可合成的当前级别的物品数量以及它们的单个花费。

每次加入时，从小到大判断，若该元素小于当前级别的价值就将它“执行”。（往 $ans$ 里加入收益，并将该元素合并入本级别即将加入的元素中）

**然后在加入下一个元素之前相邻的每 $x_i$ 个合并。**（多余扔掉）（若单个花费大于 $10^9$ 也扔掉）这一步模拟即可。

然后只需要期间统计答案就可以了。

## 代码

```cpp
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
#define pr pair
#define f first
#define s second
#define ll long long
#define mp make_pair
#define pll pr<ll,ll>
#define pii pr<int,int>
#define piii pr<int,pii>
using namespace std;
const ll m=998244353;
ll ans=0,ls;
struct stk
{
	int s;
	ll v[600005],c[600005];
	void add(ll x,ll y)
	{
		ans+=x*y;
		while(s>0)
		{
			if(v[s-1]>x) break;
			s--;
			y+=c[s];
			ans+=c[s]%m*(x-v[s])%m;
		}
		if(y==0) return;
		v[s]=x;
		c[s++]=y;
		ans%=m;
	}
	void mto(ll x,stk&a)
	{
		a.s=0;
		ll res=0,curc=0,g;
		for(int i=s-1;i>=0;i--)
		{
			if(res!=0)
			{
				g=min(x-res,c[i]);
				curc+=v[i]*g;
				res+=g;
				c[i]-=g;
				if(res<x) continue;
				else
				{
					if(curc>1.5e9) break;
					a.v[a.s]=curc;
					a.c[a.s++]=1;
				}
			}
			if(c[i]>=x)
			{
				if(v[i]*x>1.5e9) break;
				a.v[a.s]=v[i]*x;
				a.c[a.s++]=c[i]/x;
				c[i]%=x;
			}
			res=c[i];
			curc=c[i]*v[i];
		}
		reverse(a.c,a.c+a.s);
		reverse(a.v,a.v+a.s);
	}
};
ll v[200005],c[200005],x[200005];
stk _,__;
stk*a=&_,*b=&__;
stk*l;
void sl()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++) cin>>v[i];
	for(int i=0;i<n;i++) cin>>c[i];
	for(int i=1;i<n;i++) cin>>x[i];
	ans=0;
	a->s=0;
	a->add(v[0],c[0]);
	for(int i=1;i<n;i++)
	{
		if(x[i]>1)
		{
			a->mto(x[i],*b);
			l=a;
			a=b;
			b=l;
		}
		a->add(v[i],c[i]);
	}
	cout<<ans<<endl;
}
void ssl()
{
	int sid,t;
	cin>>sid>>t;
	while(t--) sl();
}
int main()
{
	ssl();
	return 0;
}
```

---

## 作者：N_z_ (赞：1)

## 思路

我们从前往后加入 $(v_i,c_i)$，维护一个 $(v,c)$ 组。  
对于一组新的 $(v_i,c_i,x_{i-1})$。  
我们首先将组里从后往前每 $x_{i-1}$ 个并成一个元素，$v$ 为他们的和，$c$ 为 $1$，即需要减少新的 $v$ 的代价来造出一个当前的 $i$。  
然后加入 $(v_i,c_i)$，当当前 $v_i$ 大于组里的 $v$ 时，我们使得组里的 $v$ 直接变成当前的 $v_i$，即 $c_i$ 增加组里的 $c$，然后将组里的 ${v,c}$ 丢掉。

我们证明这个做法的正确性。  
我们首先证明组内关于 $v$ 是单调不增的。这是容易的，贪心合并 $x$ 个保证了这一点。  
其次我们证明这一构造是最优的。具体的，我们可以证明 $v$ 从后往前是使用最小代价造出 $k$ 个 $i$ 的方案，同时用 $i$ 造 $k$ 不劣于先用 $i$ 造 $j$ 再造 $k(i<j<k)$。以及我们并不会将劣的方案选到答案中，从而这一做法是最优的。

具体实现中，我们将 $v$ 组中 $>v_{\max}$ 的直接丢弃，在 $x=1$ 的时候不干活，因为这些并不能带来贡献，这保证了复杂度在 $O(n\log n)$。

## 代码

```cpp
#define int __int128
constexpr int p=998244353;
main()
{
	signed t;
	cin>>t>>t;
	while(t--)
	{
		int n;
		cin>>n;
		vector<int>c(n),v(n),X(n-1);
		cin>>v>>c>>X;
		int ans=v[0]*c[0];
		vector<pair<int,int>>p;
		p.push_back({v[0],c[0]});
		for(int x=1;x<n;x++)
		{
			if(X[x-1]>1)
			{
				vector<pair<int,int>>p_;
				int lst=0,llst=0;
				while(!p.empty())
				{
					auto [u,v]=p.back();
					p.pop_back();
					if(lst!=0)
					{
						int fk=min(v,X[x-1]-llst);
						lst+=fk*u;
						llst+=fk;
						v-=fk;
						if(lst>1e10)break; 
						if(llst==X[x-1])p_.push_back({lst,1}),lst=llst=0;
						else continue; 
					}
					if(u*X[x-1]<=1e10)p_.push_back({u*X[x-1],v/X[x-1]}),v%=X[x-1];
					else break;
					lst=u*v;llst=v;
				}
				swap(p,p_);
				reverse(p.begin(),p.end());
			}
			ans+=v[x]*c[x]%(::p);
			while(!p.empty()&&p.back().first<=v[x])
			ans+=p.back().second*(v[x]-p.back().first)%(::p),c[x]+=p.back().second,p.pop_back();
			p.push_back({v[x],c[x]});
		}
		cout<<ans%(::p)<<endl;
	}
}
```
注：[这](https://www.luogu.com.cn/paste/a5e7tybl)是这份代码的头。

---

