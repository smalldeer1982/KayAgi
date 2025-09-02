# Halve or Subtract

## 题目描述

# Halve or Subtract


给定一个长度为 $n$ 的数列 $ a_1, a_2, \ldots, a_n $ ，一个正整数 $b$ 和两种操作：

1. 选一个 $i$ 满足 $ 1 \le i \le n $ ，把 $ a_i $ 变为 $ \lceil \frac{a_i}{2} \rceil $ 。
2. 选一个 $i$ 满足 $ 1 \le i \le n $ ，把 $ a_i $ 变为 $ \max(a_i - b, 0) $ 。

同时给定两个非负整数 $0 \le k_1, k_2 \le n$， 要求至多进行 $k_1$ 次操作1， $k_2$ 次操作2，同时对于每个元素，每种操作至多进行一次。 

求出进行若干次满足条件的操作后 $a_1 + a_2 + \ldots + a_n$ 的最小值。

## 样例 #1

### 输入

```
7
3 2 1 1
9 3 5
2 1 2 0
1000000000 1
5 3 1 1
2 8 3 19 3
6 9 4 2
1 2 3 4 5 6
3 10 3 3
1 2 3
5 1 0 0
999999999 999999999 999999999 999999999 999999999
5 5 4 3
5 9 10 7 4```

### 输出

```
11
500000001
23
6
0
4999999995
6```

# 题解

## 作者：听取MLE声一片 (赞：8)

提供一个 $O(n\log n)$ 的做法。

模拟赛出了这道题范围给了 $10^5$，但是我不会模拟费用流，就写了这个神秘做法。

首先考虑转化，定义贡献为原数减修改后的数，答案即为总和减去最大贡献。

然后考虑如何最大化贡献。贡献分别是 $\lfloor \frac{a_i}{2} \rfloor$ 和 $\min(a_i,b)$，我们要让这两个贡献最大。

如果对一个数操作两次，那么一定是先一后二，证明显然。

让贡献最大，容易想到，对于操作一尽量找原数最大，对于操作二尽量找大于 $b$ 的数。

对于 $a_i$ 大于 $2\times b$，这些数进行一操作对于二操作的没有影响的。根据上面的结论，这些数应该尽可能都进行一遍一二操作。将这些数降序排序然后依次操作即可。

这个操作之后更新 $k_1$ 和 $k_2$，令 $k=k_1+k_2$。

考虑如何处理 $1\leq a_i \leq 2\times b$ 的情况。

先做不对一个数同时做一二操作的情况。

对于操作集合内的数，大的数肯定优于小的数（优即为能提供更多的贡献）。然后就取剩下数的前 $k$ 大，如果数量不足 $k$ 就补 $0$。

我们可以处理出每个位置进行一操作和二操作分别的贡献 $A_i$ 和 $B_i$。

先假定全部进行操作一，统计出贡献和，答案是把 $k_2$ 个一操作换为二操作。

考虑记录 $C_i=B_i-A_i$，然后求这些数的前 $k_2$ 大和即可。实现时用堆维护。

最后就是在一些位置同时进行一操作和二操作。

设三操作为对一个位置先进行一操作再进行二操作。

对一个不大于 $2\times b$ 的数进行三操作是把这个数变成 $0$，所以每次操作要取能操作的最大的。

简单证明一下，有两个数分别是 $x$，$y$，其中 $x>y$。

如果进行一次三操作和一次一操作，三操作给 $x$ 的贡献为 $x+\lfloor \frac{y}{2} \rfloor$，给 $y$ 的贡献为 $y+\lfloor \frac{x}{2} \rfloor$。因为 $x-y \ge \lfloor \frac{x}{2} \rfloor-\lfloor \frac{y}{2} \rfloor$，所以三操作给 $x$ 是更优的。

如果进行一次三操作和一次二操作，三操作给 $x$ 的贡献为 $x+\min(y,b)$，给 $y$ 的贡献为 $y+\min(x,b)$。因为 $x-y \ge \min(x,b)-\min(y,b)$，所以三操作给 $x$ 是更优的。

这样就证明了每次进行三操作都是要取最大的。

考虑从小到大枚举三操作个数。三操作个数每增加 $1$，$k_1$ 和 $k_2$ 都会减小 $1$，$k$ 就会减小 $2$。因为大数肯定优于小数，所以对于三操作的对于序列的修改就是删除开头和结尾。

我们要维护这样几个东西，第一个是序列内所有 $A_i$ 的总和，这个直接维护即可。第二个是进行三操作的数的总和，也容易维护。

最后也是最重要的是维护 $C_i$ 的前 $K$ 大和，要支持删除。

询问的 $K$ 是单调递减的，所以使用 set 维护然后记录位置，然后查询的时候移动指针即可。

设记录的第 $K$ 大为 $u$，删除的数为 $x$。修改一共分三种情况，分别是 $u<x$，$u=x$，$u>x$，分别维护操作指针即可。

总时间复杂度 $O(n \log n)$。

```
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<vector>
#include<bitset>
#include<ctime>
#define int long long
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+10;
int n,m,k,k1,k2,a[N],b[N],A[N],B[N];
int Ans,ans;
vector<int>e,E;
priority_queue<pii >q;
set<pii > st;
set<pii >::iterator it;
int cmp(int x,int y){
	return x>y;
}
int f1(int x){
	int y=(x+1)/2;
	return x-y;
}
int f2(int x){
	int y=max(x-m,0ll);
	return x-y;
}
int solve(){
	int p1=k1,p2=k2,p=k,q=min(k1,k2),res=0;
	p1-=q;
	p2-=q;
	for(int i=1;i<=q;i++)
		res+=a[i];
	for(int i=q+1;i<=p;i++){
		if(!p1&&!p2)
			break;
		if(p1){
			p1--;
			res+=f1(a[i]);
			continue;
		}
		if(p2){
			p2--;
			res+=f2(a[i]);
			continue;
		}
	}
	return res;
}
signed main()
{
	int T=read();
	while(T--){
		n=read(),m=read(),k1=read(),k2=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			Ans+=a[i];
			if(a[i]<=2*m){
				E.push_back(a[i]);
				continue;
			}
			e.push_back(a[i]);
		}
		sort(e.begin(),e.end(),cmp);
		sort(E.begin(),E.end(),cmp);
		for(int i=0;i<e.size();i++){
			int x=e[i];
			if(k1&&k2){
				k1--,k2--;
				int y=max(((x+1)/2)-m,0ll);
				ans+=x-y;
				continue;
			}
			if(k1&&!k2){
				k1--;
				int y=(x+1)/2;
				ans+=x-y;
				continue;
			}
			if(!k1&&k2){
				k2--;
				int y=max(x-m,0ll);
				ans+=x-y;
				continue;
			}
		}
		for(int u:E){
			if(k>=k1+k2)
				break;
			a[++k]=u;
		}
		while(k<k1+k2)
			a[++k]=0;
		int sum=0,res=0,tot=0;
		tot=solve();
		for(int i=1;i<=k;i++){
			int x=a[i],y=(x+1)/2,z=max(x-m,0ll);
			A[i]=x-y;
			B[i]=x-z;
			b[i]=B[i]-A[i];
			q.push(mkp(b[i],i));
			sum+=A[i];
			st.insert(mkp(b[i],i));
		}
		pii u;
		int P=0;
		while(!q.empty()){
			if(P==k2)
				break;
			P++;
			pii x=q.top();
			u=x;
			q.pop();
			res+=x.fi;
		}
		tot=max(tot,sum+res);
		int s=0,p=min(k1,k2);
		for(int i=1;i<p;i++){
			s+=a[i];
			pii ret=mkp(b[i],i);
			it=st.lower_bound(ret);
			if(ret>u){
				sum-=A[i];
				res-=b[i];
				u=*--st.lower_bound(u);
				res+=u.fi;
				st.erase(it);
			}
			else if(ret==u){
				sum-=A[i];
				res-=b[i];
				st.erase(it);
				u=*st.lower_bound(ret);
				u=*--st.lower_bound(u);
				res+=u.fi;
			}
			else{
				sum-=A[i];
				st.erase(it);
			}
			ret=mkp(b[k],k);
			it=st.lower_bound(ret);
			if(ret>u){
				sum-=A[k];
				res-=b[k];
				u=*--st.lower_bound(u);
				res+=u.fi;
				st.erase(it);
			}
			else if(ret==u){
				sum-=A[k];
				res-=b[k];
				st.erase(it);
				u=*st.lower_bound(ret);
				u=*--st.lower_bound(u);
				res+=u.fi;
			}
			else{
				sum-=A[k];
				st.erase(it);
			}
			k--;
			res-=u.fi;
			it=st.lower_bound(u);
			++it;
			if(it==st.end())
				continue;
			u=*it;	
			tot=max(tot,s+sum+res);
		}
		ans+=tot;
		printf("%lld",Ans-ans);
		putchar('\n');
		e.clear();
		E.clear();
		Ans=ans=0;
		k=0;
		st.clear();
		while(!q.empty())
			q.pop(); 
	}
	return 0;
}
```


---

## 作者：蒟蒻君HJT (赞：8)

好题但是简单题，放 $1+2$ 的 $\text{F}$ 过分了。

考虑对于每个数有四种状态：除 $+$ 减，除，减，什么都不干。

- 引理 $1$：操作全用完一定不劣。

- 引理 $2$：对于除 $+$ 减的数，一定先除后减。

接下来将所有数从大到小排序，得到 $a_1,a_2,\cdots a_n$。

显然除 $+$ 减的一定是一段前缀 $k$。直接枚举前缀 $k$。

为了方便，令 $\max(0,k1+k2-n)\leq k\leq \min(k1,k2)$。鉴于引理 $1$，这样做没问题。

剩下了 $k1-k$ 个除和 $k2-k$ 个减。

- 引理 $3$：除了 $a_1,a_2,\cdots a_k$ 之外，进行操作的数字必然是 $a_{k+1},a_{k+2}\cdots a_{k1+k2-k}$。

对于 $a_{k+1},a_{k+2},\cdots a_{k1+k2-k}$，按照与 $b$ 的大小关系，分成两段：$a_{k+1},a_{k+2},\cdots a_p$ 与 $a_{p+1},a_{p+2},\cdots a_{k1+k2-k}$。

假设已经给两段分配好了各自除和减的数量，怎么确定具体的对每个数字的操作呢？

- 1. 对于不小于 $b$ 的 $a_{k+1},a_{k+2},\cdots a_p$：

减操作的贡献一定是 $-b$，而除操作对于 $a_x$ 的贡献是 $-\lfloor \frac{a_x}{2}\rfloor$。

既然减给谁都无所谓，那么显然是给大的数除，给小的数减。

即对于 $a_{k+1},a_{k+2},\cdots a_p$ 的操作是： $///---$。

- 2. 对于小于 $b$ 的 $a_{p+1},a_{p+2},\cdots a_{k1+k2-k}$：

对于 $a_x$，减操作的贡献是 $-a_x$，除操作的贡献是 $-\lfloor \frac{a_x}{2}\rfloor$。显然，我们应给大的数减，给小的数除。

即对于 $a_{p+1},a_{p+2},\cdots a_{k1+k2-k}$ 的操作是：$---///$。

发现了什么？从 $a_{k+1}$ 到 $a_{k1+k2-k}$ 的操作是先除，再减，最后除。

所以我们不用真的对 $a_x$ 根据 $b$ 分段，只需要在枚举 $k$ 之后，再枚举减的一段的开头 $a_p$ 即可。可以通过简单 $\mathcal{O}(n)$ 预处理达到单次 $\mathcal{O}(1)$ 算出一个方案的答案。

时间复杂度 $\mathcal{O}(n^2)$。

### [code](https://codeforces.com/contest/1799/submission/195356368)

---

## 作者：SlyCharlotte (赞：6)

[更好的阅读体验？](https://zhuanlan.zhihu.com/p/610191879)

## 题意描述

你被给了一个长度为 $n$ 的序列，有两种操作：

1. 找到一个数，把它除以 $2$，随后向上取整。
2. 找到一个数，把它减去 $b$，随后与 $0$ 取 max。

每种操作有使用次数上限，对于每个数每种操作只能使用一次，求经过若干次操作后，序列的最小总和。

## 简要分析

一眼 dp，然后假了，于是思维。

### Character 1

一个简单的性质，**对于每个数优先进行操作一随后进行操作二比先进行操作二再进行操作一更优**。

这个是显然的。

### Character 2

**数越大操作一对答案的贡献也就越大**。

这个更显然了。

所以我们排个序，这里默认从大到小。

### Character 3

随后开始观察样例，发现最后一个样例十分有趣，$4,5,7$ 我们需要对 $5$ 进行操作二，随后对 $4,7$ 进行操作一才能得到最优答案。

针对这一特殊性质，我们展开举例。

不难发现，**对于进行操作二的区间总是被进行操作一的区间所包围**。

通过观察，进行操作二的区间有且仅有一个。



通过上述三个性质，可以看出我们的操作大致是如下这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/g4n2azth.png)

接下来我们只需要枚举双操作区间的右端点即初次砍半区间的左端点，与初次砍半区间的长度即可。

## 代码实现

```C++
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;
const ll maxn = 1e5 + 7;
const ll INF = 1e9 + 7, MOD = 998244353;

inline ll read() {
    char cCc;
    ll xXx = 0, wWw = 1;
    while (cCc < '0' || cCc > '9')
        (cCc == '-') && (wWw = -wWw), cCc = getchar();
    while (cCc >= '0' && cCc <= '9')
        xXx = (xXx << 1) + (xXx << 3) + (cCc ^ '0'), cCc = getchar();
    xXx *= wWw;
    return xXx;
}

inline void write(ll xXx) {
    if (xXx < 0)
        putchar('-'), xXx = -xXx;
    if (xXx > 9)
        write(xXx / 10);
    putchar(xXx % 10 + '0');
}

ll n, b, p, q, a[maxn], ans;
ll f[maxn], g[maxn], h[maxn], s[maxn];

void solve() {
    n = read(), b = read(), p = read(), q = read();
    for (ll i = 1; i <= n; i++)a[i] = read();
    sort(a + 1, a + n + 1, greater<ll>()), ans = 1e18;
    for (ll i = 1; i <= n; i++)
        f[i] = f[i - 1] + max(0ll, (a[i] + 1) / 2 - b), g[i] = g[i - 1] + (a[i] + 1) / 2, h[i] =
                h[i - 1] + max(0ll, a[i] - b), s[i] = s[i - 1] + a[i];
    for (ll i = 0; i <= n; i++)
        for (ll j = 0; j <= n; j++)
            if (p >= i + j && q >= i && p + q - i <= n)
                ans = min(ans, f[i] + g[i + j] - g[i] + h[q + j] - h[i + j] + g[p + q - i] - g[q + j] + s[n] -
                               s[p + q - i]);
    cout << ans << '\n';
}

signed main() {
//    freopen("code.in","r",stdin);
//    freopen("code.out","w",stdout);
    ll T = read();
    while (T--)solve();
    return 0;
}
```


---

## 作者：王熙文 (赞：5)

提供一种新思路，复杂度为 $\mathcal O(n \log^2 n)$ 且好想好写。

## 思路

首先如果一个点上有两个操作，那么一定先进行操作 1 后进行操作 2。

将问题转化为每次减的总和最大。那么每种操作减少量为：

* 操作 1：$\lfloor \dfrac{a_i}{2}\rfloor$；

* 操作 2：$\min(a_i,b_i)$；

* 操作 1+2：$\min(\lfloor \dfrac{a_i}{2}\rfloor+b,a_i)$。

发现如果将 $k_1$ 从小到大枚举，答案的增大量一定是先大后小的，也就是说答案有凸性。因为如果相邻两次增大量先小后大，则交换一定更优。

这样就可以 wqs 二分了。设斜率为 $mid$，则操作 1 和 1+2 的贡献都需要减去 $mid$。

这样就没有 $k_1$ 的限制了。接下来的问题是在没有 $k_1$ 的限制下，求答案以及答案达到最大值时操作 1 与操作 1+2 的操作次数最小值。

为什么要求后者？因为 wqs 本质上是二分斜率，如果有答案的线上有若干点共线，若不取最小值有可能认为次数大于 $k_1$。

考虑最初每个点都用不操作或操作 1 的贡献最大值。接下来只需要选从原状态到加入操作 2 和操作 1+2 的修改量前 $k_2$ 大，将这些数使用操作 2 或操作 1+2。这样就可以求出答案了。

还有一个问题是如何让次数最小。考虑在修改量相同的时候优先使用操作 2 的贡献大于等于操作 1+2 的贡献且不操作的贡献小于操作 1 的贡献。因为这样会使操作 1 和操作 1+2 的次数之和减小 $1$。因此在排序的时候加入这一维即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,b,k1,k2;
int a[5010];
struct Sort { int lst,a,b,c; } p[5010];
bool cmp(Sort x,Sort y)
{
	int xx=max(x.b,x.c)-max(x.lst,x.a),yy=max(y.b,y.c)-max(y.lst,y.a);
	return xx==yy?(x.b>=x.c && x.lst<x.a)>(y.b>=y.c && y.lst<y.a):xx>yy;
}
int check(int mid,bool op)
{
	for(int i=1; i<=n; ++i) p[i]={0,a[i]/2-mid,min(a[i],b),min(a[i]/2+b,a[i])-mid};
	sort(p+1,p+n+1,cmp);
	if(op==1)
	{
		int sum=0;
		for(int i=1; i<=n; ++i) sum+=max(p[i].lst,p[i].a);
		for(int i=1; i<=k2; ++i) sum+=max(max(p[i].b,p[i].c)-max(p[i].lst,p[i].a),0ll);
		return sum+k1*mid;
	}
	int cnt=n;
	for(int i=1; i<=n; ++i) cnt-=(p[i].lst>=p[i].a);
	for(int i=1; i<=k2; ++i)
	{
		if(max(p[i].b,p[i].c)>=max(p[i].lst,p[i].a)) cnt-=(p[i].b>=p[i].c && p[i].lst<p[i].a);
	}
	return cnt<=k1;
}
signed main()
{
	int t; cin>>t; while(t--)
	{
		cin>>n>>b>>k1>>k2;
		int sum=0;
		for(int i=1; i<=n; ++i) cin>>a[i],sum+=a[i];
		sort(a+1,a+n+1,greater<int>());
		int el=0,er=1e9,mid,ans;
		while(el<=er)
		{
			mid=el+er>>1;
			if(check(mid,0)) ans=mid,er=mid-1;
			else el=mid+1;
		}
		cout<<sum-check(ans,1)<<'\n';
	}
	return 0;
}
```

---

## 作者：cyffff (赞：2)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1799F)

介绍一下一种高维 wqs 的方法。

此方法来自 @[YeahPotato](https://www.luogu.com.cn/user/94976) 的专栏 [严谨的 WQS 二分方法](https://www.luogu.com/article/vsffwrc3)。

## 题意

给定一个长为 $n$ 的序列 $v_{1\dots n}$，三个常数 $d,a,b$。你可以执行若干次以下两种操作：

1. 选择 $1\le i\le n$，令 $v_i\gets\lceil\frac{v_i}{2}\rceil$。
1. 选择 $1\le i\le n$，令 $v_i\gets\max(v_i-d,0)$。

你至多进行 $a$ 次操作 1，$b$ 次操作 2，同时对于每个元素，每种操作至多进行一次。

你需要最小化操作后 $\sum v$ 的值并输出。

$1\le n\le 10^5$。
## 题解

两个显然的性质是，我们会把操作用完、我们会先用操作 1 再用操作 2。而根据费用流建图，答案关于操作次数 $a,b$ 均为下凸的。

我们设操作次数限制为 $a,b$ 时的答案为 $f(a,b)$，那么我们需要使用两层 wqs 二分分别去除两维限制，而外层二分我们需要求出「使得 $f(x,b)-kx$ 取到最小值的 $x$」，而它并不好求。问题的关键为我们无法直接通过调整斜率使得求出切到的点恰为给定值，无法同时使两维取到 $a,b$。

此时，我们就需要寻找求解凸函数单点值的更优方法。

有如下结论：

- 当 $f(x)$ 关于 $x$ 上凸时，令 $g_a(k)=ka+\displaystyle\max_{x}(f(x)-kx)$，那么有：$g_a(k)$ 关于 $k$ 下凸且 $f(a)=\displaystyle\min_kg_a(k)$。
- 当 $f(x)$ 关于 $x$ 下凸时，令 $g_a(k)=ka+\displaystyle\min_{x}(f(x)-kx)$，那么有：$g_a(k)$ 关于 $k$ 上凸且 $f(a)=\displaystyle\max_kg_a(k)$。

> 证明：不妨考虑证明其中第二条。
>
> 以下将 $g_a(k)$ 简写为 $g(k)$。令 $h(k)$ 为 $f(x)-kx$ 取到最小值的某个 $x$。
>
> 证明 $g(k)$ 上凸即证 $\forall k_1,k_2,\forall \lambda\in[0,1]$，令 $k=\lambda k_1+(1-\lambda )k_2$，有 $\lambda g(k_1)+(1-\lambda)g(k_2)\le g(k)$：
>
> $$\begin{aligned}&\lambda g(k_1)+(1-\lambda)g(k_2)\\=&\lambda [k_1a+\min_x(f(x)-k_1x)]+(1-\lambda)[k_2a+\min_x(f(x)-k_2x)]\\\le&\lambda [k_1a+(f(h(k))-k_1h(k))]+(1-\lambda)[k_2a+(f(h(k))-k_2h(k))]\\=&g(k)\end{aligned}$$
>
> 还需证明 $g(k)$ 的最大值为 $f(a)$，那么由于 $f(x)$ 关于 $x$ 下凸，必定有 $g(f'(a))=f(a)$。而 $g(k)\le ka+f(a)-ka=f(a)$，所以 $f(a)=\max_k g(k)$。

有了这个结论，我们就把较对复杂的凸函数求值转化为了对较简单的凸函数求最值。

接下来，我们就可二分或三分求 $g(k_1)=k_1a+\min_x(f(x,b)-k_1x)$ 的最值；而其中 $\min_x(f(x,y)-k_1x)$ 又是关于 $y$ 的下凸函数，再用二分或三分求 $h(k_2)=k_2b+\min_{x,y}(f(x,y)-k_1x-k_2y)$ 的最值即可。

时间复杂度 $O(n\log^2 v)$。

核心代码：
```cpp
const int N=5e3+10;
int n,d,a,b,v[N];
inline ll calc(int k1,int k2){
	ll s=0;
	for(int i=1;i<=n;i++)
		s+=min({v[i],(v[i]+1)/2-k1,max(v[i]-d,0)-k2,max((v[i]+1)/2-d,0)-k1-k2});
	return s;
}
inline ll solve2(int k1){
	int L=-1e9,R=0;
	while(L<R){
		int mL=L+R>>1,mR=mL+1;
		ll v1=calc(k1,mL)+1ll*mL*b,v2=calc(k1,mR)+1ll*mR*b;
		if(v1==v2) return v1;
		if(v1<v2) L=mL+1;
		else R=mR-1;
	}
	return calc(k1,L)+1ll*L*b;
}
inline ll solve1(){
	int L=-1e9,R=0;
	while(L<R){
		int mL=L+R>>1,mR=mL+1;
		ll v1=solve2(mL)+1ll*mL*a,v2=solve2(mR)+1ll*mR*a;
		if(v1==v2) return v1;
		if(v1<v2) L=mL+1;
		else R=mR-1;
	}
	return solve2(L)+1ll*L*a;
}
```

---

## 作者：Petit_Souris (赞：1)

什么题小常数 $\mathcal O(n\log n)$ 开 $n=5000$？

首先对于同一个数如果除法和减法都操作了，一定是先做除法再做减法。

其次对于任意时刻，不可能不操作最大的数而去操作后面的数。

因此最终从大到小排序后的操作情况形如：

- 第一段是做了两种操作的；

- 第二段是做了其中一种操作的；

- 剩下是没有操作的。

我们可以枚举第一段前缀的长度，设为 $i$，此时需要从接下来的 $k_1+k_2-2i$ 个数中选择 $k_1-i$ 个做除法，$k_2-i$ 个做减法。可以考虑贪心，即初始的时候全都选除法，再从所有可能的数中选出增量最大的 $k_2-i$ 个替换。这样有 $\mathcal O(n^2\log n)$ 的做法。

发现从大到小枚举 $i$ 有很好的性质：每次 $k_1,k_2$ 分别增加 $1$，选择的第二段的区间会向左向右分别扩展一个。于是直接用对顶堆维护这个过程就行了，时间复杂度 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
bool Mbe;
ll read(){
    ll x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return x*f;
}
void write(ll x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
const ll N=2e5+9;
ll T,n,b,k1,k2,a[N],pre[N],suf[N],d1[N],d2[N],dt[N];
void solve(){
    n=read(),b=read(),k1=read(),k2=read();
    rep(i,1,n)a[i]=read();
    sort(a+1,a+n+1,greater<ll>());
    rep(i,0,n+1)pre[i]=suf[i]=d1[i]=d2[i]=0;
    rep(i,1,n)pre[i]=pre[i-1]+max((a[i]+1)/2-b,0ll);
    per(i,n,1)suf[i]=suf[i+1]+a[i];
    rep(i,1,n){
        d1[i]=a[i]-(a[i]+1)/2;
        d2[i]=a[i]-max(a[i]-b,0ll);
        dt[i]=d2[i]-d1[i];
    }
    priority_queue<ll,vector<ll>,greater<ll> >q1;
    priority_queue<ll>q2;
    ll s1=0,s2=0,l=-1,r=-1,fir=0,ans=1e18;
    per(i,n,0){
        if(k1>=i&&k2>=i){
            if(!fir){
                fir=1;
                l=i+1,r=max(k1,k2);
                rep(j,l,r)s1+=d1[j],q2.push(dt[j]);
            }
            else {
                l--,r++;
                s1+=d1[l],q2.push(dt[l]);
                if(r<=n)s1+=d1[r],q2.push(dt[r]);
            }
            while((ll)q1.size()<k2-i){
                ll t=q2.top();q2.pop();
                q1.push(t),s2+=t;
            }
            while(!q1.empty()&&!q2.empty()&&q1.top()<q2.top()){
                ll x=q1.top();q1.pop();
                s2-=x;
                ll y=q2.top();q2.pop();
                s2+=y,q1.push(y);
            }
            ans=min(ans,pre[i]+suf[i+1]-(s1+s2));
        }
    }
    write(ans),putchar('\n');
}
bool Med;
int main(){
    // freopen("a.in","r",stdin);
    // freopen("a.out","w",stdout);
    cerr<<fabs(&Med-&Mbe)/1048576.0<<"MB\n";
    T=read();
    while(T--)solve();
    cerr<<"\n"<<clock()*1.0/CLOCKS_PER_SEC*1000<<"ms\n";
    return 0;
}
```

---

## 作者：_lbw_ (赞：1)

时间复杂度 $\mathcal{O}(n\log ^2n)$。

打表+感性理解 发现答案关于同时做 1,2 操作是上凸的。

三分，并且可以发现 1,2 操作只会在尽可能大的数上操作，容易反证。

接下来是一个经典问题，每个数有权值 $w_1,w_2$，两个数只能选一个，每个数有选择个数限制，求最大权值。

这个问题可以反悔贪心，有如下操作：

- 选第一个数。 

- 选第二个数。

- 将一个数从一反悔到二，然后再选一个二。

- 将一个数从二反悔到一，然后再选一个一。

用堆维护之。

```cpp
const int maxn = 1e6+5;
#define pii pair<ll,ll>
priority_queue<pii>q1,q2,q3,q4;
bool cmax(ll&x,ll val){return x<val?x=val,1:0;}
ll n,b,k1,k2,a[maxn],w1[maxn],w2[maxn],na[maxn],S;bool vis[maxn];
ll check(ll M){

    while(!q1.empty())q1.pop();while(!q2.empty())q2.pop();
    while(!q3.empty())q3.pop();while(!q4.empty())q4.pop();

    ll nl=n-M,n1=k1-M,n2=k2-M,ans=0;
    F(i,1,M)ans+=min(a[i]/2+b,a[i]);F(i,1,nl)na[i]=a[i+M],vis[i]=0;
    F(i,1,nl)w1[i]=na[i]/2,w2[i]=min(b,na[i]),q1.push({w1[i],i}),q2.push({w2[i],i});
    // F(i,1,nl)cout<<w1[i]<<' '<<w2[i]<<endl;
    while(n1||n2){
        ll type=0,cg=-1e18,x,y;
        while(!q1.empty()&&vis[q1.top().second])q1.pop();
        while(!q2.empty()&&vis[q2.top().second])q2.pop();
        if(n1){
            if(!q1.empty()&&cmax(cg,q1.top().first))type=1;
            if(!q4.empty()&&!q2.empty()&&cmax(cg,q2.top().first+q4.top().first))
                type=2;
        }
        if(n2){
            if(!q2.empty()&&cmax(cg,q2.top().first))type=3;
            if(!q3.empty()&&!q1.empty()&&cmax(cg,q1.top().first+q3.top().first))
                type=4;
        }
        // cout<<type<<' '<<n1<<' '<<n2<<' '<<cg<<endl;
        if(!type)break;ans+=cg;assert(type);
        if(type==1)n1--,x=q1.top().second,q1.pop(),vis[x]=1,q3.push({w2[x]-w1[x],x});
        if(type==2){
            n1--;//w1-w2 + w2
            x=q2.top().second,q2.pop(),vis[x]=1,q4.push({w1[x]-w2[x],x});
            y=q4.top().second,q4.pop(),q3.push({w2[y]-w1[y],y});
        }
        if(type==3)n2--,x=q2.top().second,q2.pop(),vis[x]=1,q4.push({w1[x]-w2[x],x});
        if(type==4){
            n2--;
            x=q1.top().second,q1.pop(),vis[x]=1,q3.push({w2[x]-w1[x],x});
            y=q3.top().second,q3.pop(),q4.push({w1[y]-w2[y],y});
        }
    }
    return ans;
}
ll cdq(ll l,ll r){
    // cout<<l<<' '<<r<<endl;
    if(l==r)return check(l);ll mid=l+r>>1,x=check(mid),y=check(mid+1);
    return x<y?cdq(mid+1,r):cdq(l,mid);
}
IV solve(){
    n=read();b=read();k1=read();k2=read();S=0;
    F(i,1,n)a[i]=read(),S+=a[i];ll l=0,r=min(k1,k2);
    ll ans=0;sort(a+1,a+1+n);reverse(a+1,a+1+n);
    printf("%lld\n",S-cdq(l,r));
}
int main(){
    // freopen("1.in","r",stdin);
    // freopen("1.out","w",stdout);
    ll T=read();while(T--)solve();return 0;
}
```


---

## 作者：_maze (赞：1)

> 给你一个序列 $a$ 和一个常数 $b$，你可以对 $a$ 做两种操作：
> 1. 将 $a_i\leftarrow\lceil\frac{a_i}{2}\rceil$。
> 2. 将 $a_i\leftarrow\max(a_i-b,0)$。
> 限制你最多做 $k_1$ 次一操作，$k_2$ 次二操作，且每个数两种操作最多各做一次。求操作后最小的 $\sum a$。

tag：贪心

考虑每个数被操作的四种形式，首先是先除后减（先减后除必定没有先除后减优）。容易想到这是对于最大的几个数做的。不妨枚举数的数量 $p$，将 $k_1\leftarrow k_1-p$，同时将 $k_2\leftarrow k_2-p$。

对于剩下的数，我们将数分为大于等于 $b$ 和小于 $b$ 两部分，分类的依据是二操作能不能贡献满。接着分类讨论：

1. 对于大于 $b$ 的部分，二操作对答案的影响全部相同，重点讨论一操作。显然我们选较大的数比选择较小的数更优。于是我们倒序后先除后减。
2. 对于小于 $b$ 的部分，一操作的贡献必定大于二操作，而且一操作较大的数贡献更大。于是我们倒序后先减后除。

发现区分点在于除转减和减转除两段。于是我们用前缀和预处理出每个除转减与减转除的贡献，对于每个除转减的点，我们尽量用完一操作再转回除法（根据上文分析可得，除转减后所有点均用减法最优），然后暴力枚举 $p$ 和除转减的分界点即可。时间复杂度 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define forp(i, a, b) for (int i = a; i <= b; ++i)
#define ll long long
const int N = 5e3 + 5;
ll n, b, k1, k2, a[N], r[N], d[N], p[N], rd[N], ans;
void solve() {
  cin >> n >> b >> k1 >> k2;ans = 3e15;
  forp (i, 1, n) cin >> a[i];
  sort(a + 1, a + n + 1, [](ll a, ll b) { return a > b; });
  forp (i, 1, n) r[i] = r[i - 1] + max(a[i] - b, 0ll), d[i] = d[i - 1] + ((a[i] + 1) / 2);
  forp (i, 1, min(k1, k2)) rd[i] = rd[i - 1] + max(((a[i] + 1) / 2) - b, 0ll);
  forp (i, 1, n) p[i] = p[i - 1] + a[i];
  forp (q, 0, min(k1, k2)) forp (tr, q, min(n, k1)) {
    int bk = min(n, tr + (k2 - q)), ed = min(n, bk + k1 - tr);
    ans = min(ans, rd[q] + (d[tr] - d[q]) + (r[bk] - r[tr]) + (d[ed] - d[bk]) + (p[n] - p[ed]));
  }
  cout << ans << endl;
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);
  int t;cin >> t;while (t--) solve();
  return 0;
}
```


---

## 作者：Retired_lvmao (赞：1)

### 题目描述

给定 $n$ 个自然数 ，第 $i$ 个自然数 $A_i$ 。给定常数 $k_1,k_2,b$ ，你可以按照以下规则对这个序列进行操作 $1$ 和操作 $2$：

- 操作 $1$，选定一个 $i$，使得 $A_i$ 变为 $\lceil\frac{A_i}{2}\rceil$。
- 操作 $2$，选定一个 $i$，使得 $A_i$ 变为 $\max{(A_i-b,0)}$。

- 每个数至多只能被执行一次操作 $1$，一次操作 $2$，且操作 $1$ 的次数不超过 $k_1$ 次，操作 $2$ 的次数不超过 $k_2$ 次。

$n\leq 5000$

### 题解

首先考虑将这些数字从大到小排序。

可以注意到，同时被执行操作 $1$ 和操作 $2$ 的数字总是一段前缀（也就是最大的一些数）。因此，我们不妨考虑枚举有多少个数同时被进行了操作。

继续考虑剩下的数。由于进行操作总是不劣的，我们总是会把所有的操作用完。当所有的操作不足以将所有的数字操作一遍时，肯定有一段后缀的数不被进行操作，这一段数字可以被直接确定。

最后考虑剩下的数字。这些数字一定会恰好被两种操作中的一种执行，且两种操作都有一个次数上限。对于这个问题，我们可以使用反悔贪心来解决。

单次反悔贪心的时间复杂度是 $O(n\log n)$，再乘上枚举的复杂度，时间复杂度 $O(n^2 \log n)$。由于该做法常数优秀，可以通过。

当然这个贪心也可以不用反悔直接做，只需要按照两种操作的结果的差，排序后，从两头贪即可。

### 代码
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,bbd,k1,k2,t;
int a[500010],b[500010],c[500010],d[500010];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld%lld%lld",&n,&bbd,&k2,&k1);
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		sort(a+1,a+n+1,greater<int>());
		for(int i=1;i<=n;i++)
		{
			d[i]=max((a[i]+1)/2-bbd,0ll);
			c[i]=(a[i]+1)/2;
			b[i]=max(a[i]-bbd,0ll);
		}
		int ans=1e18;
		for(int i=0;i<=n&&i<=k1&&i<=k2;i++)
		{
			int cur=0;
			for(int j=1;j<=i;j++)
				cur+=d[j];
			int lst1=k1-i,lst2=k2-i;
			for(int j=i+lst1+lst2+1;j<=n;j++)
				cur+=a[j];
			priority_queue<pair<int,int>> q1;
			priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q2;
			for(int j=i+1;j<=i+lst1+lst2;j++)
			{
				if(b[j]>=c[j])
				{
					if(q2.size()<lst2)
						q2.push(make_pair(b[j]-c[j],j)),cur+=c[j];
					else if(lst2)
					{
						q2.push(make_pair(b[j]-c[j],j)),cur+=c[j];
						auto x=q2.top();q2.pop(); 
						cur-=c[x.second];cur+=b[x.second];
						q1.push(make_pair(b[x.second]-c[x.second],x.second));
					}
					else
						q1.push(make_pair(b[j]-c[j],j)),cur+=b[j];
				}
				else 
				{
					if(q1.size()<lst1)
						q1.push(make_pair(b[j]-c[j],j)),cur+=b[j];
					else if(lst1)
					{
						q1.push(make_pair(b[j]-c[j],j)),cur+=b[j];
						auto x=q1.top();q1.pop(); 
						cur-=b[x.second];cur+=c[x.second];
						q2.push(make_pair(b[x.second]-c[x.second],x.second));
					}
					else
						q2.push(make_pair(b[j]-c[j],j)),cur+=c[j];
				}
			}
			ans=min(ans,cur);
		}
		printf("%lld\n",ans);
	}
}
```

---

## 作者：MiniLong (赞：0)

除排序外 $\Theta(n)$ 的做法。

将 $a$ 从小到大排序。

首先可以发现，若 $\lceil \dfrac{a_i}{2} \rceil - b \ge 0$，那么这个数一定会被两种操作同时操作。那么可以从最大的开始把满足这个要求的数全操作了。在操作这些数的过程中，若 $k1,k2$ 中其中一个不够用了，那么从大到小把 $a_i$ 用另一种操作肯定是优的。此时直接返回答案即可。

去除上述满足条件的数后，剩下的数一定满足 $a_i < 2\times b$。这些数中，有些数可以同时用两种操作，有些数只用一种操作，可以考虑观察一下哪些数是用两种操作、哪些数用第一种比第二种优。

结论：一定是一段后缀同时使用两种操作，然后跟着一段只用一操作，然后跟着一段只用二操作，再后面跟着一段只用一操作。

![](https://cdn.luogu.com.cn/upload/image_hosting/drdp975m.png)

如上图，只有这两种情况。

证明如下：

- 若只看 $<b$ 的部分，使用第二种操作可以使 $a_i$ 直接变成 $0$，使用第一种操作只能减半，此时一定是最大的若干个使用第二种操作。假设存在 $x>y$ 使得 $x$ 使用了第一种操作，$y$ 使用了第二种操作，此时能使答案减少 $\lfloor \dfrac{x}{2} \rfloor+y$，若交换，可以使得答案减少 $\lfloor \dfrac{y}{2} \rfloor + x$，显然后面更优。
- 再看 $\ge b$ 的部分。
  - 首先两种全用的肯定是最大若干个，证明可以用调整法，与上面类似。
  - 然后是第一种和第二种操作的顺序，此时因为保证 $a_i \ge b$，第二种操作的贡献是确定的，那么肯定是选择比较小的若干个，让除以 $2$ 的用到比较大的部分即可。

然后再考虑中间那段绿色的部分到底是在哪里，设绿色部分最大的数是 $x$，绿色部分后面那个是 $y$。若此时把绿色的往后平移一格更优，那么有 $\lfloor \dfrac{x}{2} \rfloor + y > b + \lfloor \dfrac{y}{2} \rfloor$，即 $x+y >2\times b$。

显然满足这个要求的起始点一定是一段图中的后缀，我们肯定是想让起始点越大越好，于是在绿色长度固定的时候只需要找到第一个 $a_i + a_{i-len} \le 2 \times b$ 的最大的 $i$ 即可，这个可以用简单双指针做到。

考虑具体算法：直接枚举有多少个数同时使用两种操作，此时就确定了绿色部分，讨论红色部分的大小。若剩下的红色部分长度小于绿色到蓝色部分之间的空隙，那么让红色占满蓝色后面的一段，并让绿色往左移动到没有空隙位为止；否则就让一部分红色填满这个空隙，剩下的塞绿色后面即可。预处理前缀和即可 $\Theta(n)$ 实现这个过程。

所以在不考虑排序的情况下，此算法复杂度为 $\Theta(n)$。

---

