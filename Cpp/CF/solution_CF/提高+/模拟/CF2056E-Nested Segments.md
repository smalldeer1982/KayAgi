# Nested Segments

## 题目描述

如果 $1\le l\le r\le n$ 且 $A$ 中任何一对不同的线段 $[l_i, r_i], [l_j, r_j]$ 都恰好满足以下条件之一，那么由具有整数端点的成对不同线段 $[l, r]$ 组成的集合 $A$ 就称为良好集合：

- $r_i < l_j$ 或 $r_j < l_i$ （线段不相交）
- $l_i \le l_j \le r_j \le r_i$ 或 $l_j \le l_i \le r_i \le r_j$ （一条线段完全包含在另一条线段中）

给你一个很好的集合 $S$ 由 $m$ 对不同的线段 $[l_i, r_i]$ 组成，其端点为整数。您希望在确保集合 $S$ 不变的前提下，尽可能多地向集合 $S$ 添加线段。

由于这项任务过于简单，因此您需要确定有多少种不同的方法可以在确保集合 $S$ 不变的情况下，向 $S$ 添加最大数量的额外线段。如果在其中一种方法中增加了一个线段，而在另一种方法中没有增加，那么这两种方法就被认为是不同的。

从形式上看，我们需要找出由不同的线段组成的良好集合 $T$ 的个数，使得 $S$ 是 $T$ 的子集，而 $T$ 具有最大可能的大小。由于结果可能很大，请计算答案的模数 $998\,244\,353$ 。

## 说明/提示

在第一个例子中，唯一可能的线段是 $[1, 1]$ ，因此 $T = \{[1, 1]\}$ 的大小最大，也是唯一的解。

在第二个示例中，无法向集合 $S$ 添加任何额外的线段。因此，向 $S$ 添加线段的唯一方法就是不添加任何线段。

在第三个例子中，在确保集合 $S$ 仍然良好的情况下，可以向 $S$ 添加 $7$ 个额外的线段。我们可以证明，在 $S$ 中添加超过 $7$ 的线段是不可能的。恰好有 $2$ 种不同的方法可以将这些 $7$ 个线段添加到 $S$ 中，它们各自的集合 $T$ 如下所示：

- $\{[1, 1], [1, 3], [1, 4], [1, 5], [2, 2], [2, 3], [3, 3], [4, 4], [5, 5]\}$
- $\{[1, 1], [1, 3], [1, 5], [2, 2], [2, 3], [3, 3], [4, 4], [4, 5], [5, 5]\}$ .

在第四个例子中，正好有 $5$ 种不同的方法可以将最多 $6$ 个额外的线段添加到 $S$ 中，它们各自的集合 $T$ 如下所示：

- $\{[1, 1], [1, 2], [1, 3], [1, 4], [2, 2], [3, 3], [4, 4]\}$
- $\{[1, 1], [1, 2], [1, 4], [2, 2], [3, 3], [3, 4], [4, 4]\}$
- $\{[1, 1], [1, 3], [1, 4], [2, 2], [2, 3], [3, 3], [4, 4]\}$
- $\{[1, 1], [1, 4], [2, 2], [2, 3], [2, 4], [3, 3], [4, 4]\}$
- $\{[1, 1], [1, 4], [2, 2], [2, 4], [3, 3], [3, 4], [4, 4]\}$ 

Translate by [@TigerXiaoxi](https://www.luogu.com.cn/user/943404)

## 样例 #1

### 输入

```
6
1 0
2 3
1 1
2 2
1 2
5 2
1 3
2 3
4 1
1 1
6 2
1 3
4 6
2300 0```

### 输出

```
1
1
2
5
4
187997613```

# 题解

## 作者：Iniaugoty (赞：6)

### [CF2056E	Nested Segments](/problem/CF2056E)

注意到最优构造会是一个二叉树（线段树？）状物，答案为 $2n - 1$。

证明可以考虑归纳。设 $f _ n$ 为 $[1, n]$ 的答案，然后大致就是，首先选择 $[1, n]$，然后随便选一个 $x$ 分为两段 $[1, x]$ 和 $[x + 1, n]$，变成两个子问题，$f _ n = 1 + f _ {x} + f _ {n - x} = 1 + 2x - 1 + 2(n - x) - 1 = 2n - 1$；而分成更多段的时候，算一下这个值会 $< 2n - 1$。

考虑当 $m = 0$ 时求最优构造的方案数。

设为 $g _ n$。发现 $x$ 可以任意选取，于是 $g _ n = \sum _ {i = 1} ^ {n - 1} g _ i g _ {n - i}$。这不是卡特兰数吗，所以得到了 $g _ {n + 1} = H _ n = \frac {\binom {2n} {n}} {n + 1}$。

那当 $m \neq 0$ 时呢。

发现 $[1, n]$ 和 $[i, i]$ 都是一定选取的，把他们加进来，发现区间之间可以按照包含关系建出一个树状结构。

考虑结点 $u$ 表示区间 $[l _ u, r _ u]$，设它有 $deg _ u$ 个子结点。不难发现这一步选取的区间，不能跨越两个子结点的区间内部，就是可以把一个子结点 $[l _ v, r _ v]$ 当作一个点 $[x, x]$，于是实际上变成了一个 $deg _ u$ 规模的 $m = 0$ 的问题，方案数是 $H _ {deg _ u - 1}$。

预处理 $H _ n$，排序后用一个单调栈建树，答案为 $\prod H _ {deg _ u - 1}$。

时间复杂度为 $O(\log n)$。

[代码](https://codeforces.com/contest/2056/submission/301513111)。

---

## 作者：Hell0_W0rld (赞：3)

先考虑 $m=0$ 的情况。注意到一种最优构造是 $[1,i],[i,i]$ 共 $2n-1$ 个区间。不妨设 $f(x)$ 表示线段都包含于 $[1,x]$ 的最优解方案数，则考虑在中间寻找分界线，有 $f(k)=\sum_{i=1}^{k-1}f(i)f(k-1-i)$。

于是 $f(x)$ 即为卡特兰数，递推求解即可。
***
考虑 $m\neq 0$。

![n=9](https://cdn.luogu.com.cn/upload/image_hosting/d5uozlkm.png)
考虑上面这张图（$n=9$，左闭右开），等价于新加入的区间不能与 $[2,6][8,9]$ 相交却不包含，也就是在区间 $[1,1][2,6][7,7][8,9]$ 中插入子区间，并以这四个区间为基础，放更大的区间。

而在区间 $[2,6]$ 中有子区间 $[2,2][4,5]$，等价于在 $[2,2][3,3][4,5][6,6]$ 中插入子区间并以这四个区间为基础进行合并。
***
考虑建树：
![](https://cdn.luogu.com.cn/upload/image_hosting/g4zr3wwd.png)

发现每一个节点 $u$ 对总答案的贡献即为 $f(len_u-\sum\limits_{\text{v is a son of u}}(len_v-1))$，其中 $len_u$ 表示区间 $u$ 的长度。

将区间按照左端点排序，并用一个栈模拟 dfs 的过程，不断 pop 并乘上贡献，直到找到第一个完全包含当前区间的区间。减掉 $len$ 之后入栈即可。

注意 $f(x)=\operatorname{cat}(x-1)$！！
***
```cpp
#include<bits/stdc++.h>
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define ll long long
#define ld long double
#define ull unsigned long long
#define rep(i,l,r) for(ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(ll i=(r);i>=(l);--i)
#define all(x) x.begin(),x.end()
#define Set(x,y) memset(x,y,sizeof(x))
#define Cpy(x,y) memcpy(x,y,sizeof(x))
#define cll const long long
using namespace std;
mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
template<class T>void death(T s){cout<<s<<endl;exit(0);}
template<cll MOD> class modint{
	private:
	public:
		ll x;
		modint()=default;
		modint(ll _x){x=(_x%MOD+MOD)%MOD;}
		friend istream& operator>>(istream& in, modint& a){in>>a.x; a.x%=MOD; return in;}
		friend ostream& operator<<(ostream& out, modint a){return out<<a.x;}
		friend modint operator+(modint a,modint b){return a.x+b.x>=MOD?a.x+b.x-MOD:a.x+b.x;}
		friend modint operator-(modint a,modint b){return a.x-b.x>=0?a.x-b.x:a.x-b.x+MOD;}
		friend modint operator*(modint a,modint b){ll x=a.x,y=b.x;return x*y%MOD;}
		friend modint operator/(modint a,modint b){return a*(~b);}
		friend modint operator^(modint a,ll p){modint ans=1;for(;p;p>>=1){if(p&1)ans*=a;a=a*a;}return ans;}
		friend modint operator~(modint a){return a^(MOD-2);}
		friend modint operator-(modint a){return a.x==0?0:MOD-a.x;}
		friend modint& operator+=(modint&a,modint b){return a=a+b;}
		friend modint& operator-=(modint&a,modint b){return a=a-b;}
		friend modint& operator*=(modint&a,modint b){return a=a*b;}
		friend modint& operator/=(modint&a,modint b){return a=a/b;}
		friend modint& operator++(modint&a) {return a+=1;}
		friend modint operator++(modint&a,int){modint x=a;a+=1;return x;}
		friend modint& operator--(modint&a) {return a-=1;}
		friend modint operator--(modint&a,int){modint x=a;a-=1;return x;}
		friend bool operator==(modint a, modint b){return a.x==b.x;}
		friend bool operator!=(modint a, modint b){return a.x!=b.x;}
};
using mint=modint<998244353>;
cll N=200009;
mint cat[N]; ll n,m,len[N];
struct Segment{
	ll l,r;
	bool operator<(const Segment&x)const{return l<x.l||l==x.l&&r>x.r;}
}s[N];
void solve(){
	{ cin>>n>>m; bool a=0; 
	rep(i,1,m)cin>>s[i].l>>s[i].r,a|=(s[i].l==1&&s[i].r==n);
	if(!a) s[++m]=(Segment){1,n}; sort(s+1,s+1+m); rep(i,1,m)len[i]=s[i].r-s[i].l+1;} // init
	stack<ll> stk; stk.push(1); mint ans=1;
	rep(i,2,m){
		ll fa;
		while(!stk.empty()){
			ll x=stk.top();
			if(s[x].l<=s[i].l&&s[i].r<=s[x].r){fa=x; break;}
			else{ ans*=cat[len[x]]; stk.pop(); }
		}
		len[fa]-=len[i]-1; stk.push(i);
	}
	while(!stk.empty())ans*=cat[len[stk.top()]],stk.pop();
	cout<<ans<<endl;
}
int main(){
	cat[1]=cat[2]=1; rep(k,2,N-5)cat[k]=cat[k-1]*2*(2*k-3)/k;
	ll T;cin>>T;while(T--)solve();
	return 0;
}
```

---

## 作者：yvbf (赞：1)

![](bilibili:BV13QwtefEjN?t=3221)

---

## 作者：RAYMOND_7 (赞：1)

难度可能是 $*1500$。

读题后发现集合大小最后是 $2n-1$ 。

首先考虑 $m=0$ ，发现就是卡特兰数。

然后考虑 $m>0$ ，发现 $[i,i] / [1,n]$ 之类是必选的，其余的部分一定构成了一个树结构，对于一个节点 $[l,r]$ 其贡献应该是将子树看成一个整体后套 $m=0$ 的做法，也就是将若干卡特兰数乘起来，用 $\text{set}$ 维护不交区间可以做到 $O(n\log n)$。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include <ctime>
#include <set>

using namespace std;

#pragma GCC optimize("Ofast")
#define int long long
#define PII pair<int,int>
#define x first
#define y second
#define For(i, l, r) for(int i = l; i <= r; i ++)
#define Rep(i, l, r) for(int i = l; i >= r; i --)

bool START;

void in(int &x)
{
	char c = getchar(); int op = 1;
	while(c > '9' || c < '0') op *= (c == '-' ? -1 : 1), c = getchar();
	for(x = 0; c >= '0' && c <= '9'; c = getchar()) x = x * 10 + c - '0'; x *= op;
}

const int N = 4e5+ 50,P=998244353;

int n, m, a[N],xr[N],L[N],R[N],f[N],fc[N],ifc[N];
int ksm(int x,int y)
{
	int s=1;
	while(y)
	{
		if(y&1)s=s*x%P;
		x=x*x%P;y>>=1;
	}
	return s;
}
PII p[N];
multiset<PII> se;
int T;

void init(int n)
{
	fc[0]=ifc[0]=1;
	For(i,1,n*2)fc[i]=fc[i-1]*i%P,ifc[i]=ksm(fc[i],P-2);
	For(i,1,n)f[i]=fc[i*2-2]*ifc[i-1]%P*ifc[i]%P;
	f[1]=1;f[2]=1;
}

bool ENDPOS = 0;
signed main()
{
	double chu = clock();
	in(T);
	init(200010);
	while(T--)
	{
		in(n);in(m);
		se.clear();int mm=0;
		For(i,1,m)
		{
			int l,r;in(l);in(r);
			if(l==r)continue;
			if(l==1&&r==n)continue;
			p[++mm]={l,r};
		}
		m=mm;
		if(!m){printf("%lld\n", f[n]);continue;}
		sort(p+1,p+m+1,[](PII a,PII b){return a.x!=b.x?a.x<b.x:a.y>b.y;});
		reverse(p+1,p+m+1);
		int ans=1;
		p[++m]={1,n};
		For(i,1,m)
		{
			int l=p[i].x,r=p[i].y;
			auto it=se.lower_bound({l,l});
			int sz=r-l+1;
			while(it!=se.end())
			{
				if((it->y)>r)break;
				sz=sz-(it->y) + (it->x);
				it=se.erase(it);
			}
			se.insert({l,r});
			ans=ans*f[sz]%P;
		}
		printf("%lld\n",ans);
	}
	cerr << "Time = " << (clock() - chu) / CLOCKS_PER_SEC << endl;
	cerr << (&ENDPOS - &START) * 1.0 / 1024 / 1024 << endl; return 0;
}

```

---

## 作者：rainygame (赞：0)

这有 \*2500？见证 CF 评分随机性。

首先注意到 $[1,n]$ 和 $[i,i]$ 都是必须在答案里的。因为任何时候都一定可以加上这些区间。

这个区间的性质可以建树，因为显然不能有两个不交的区间拥有共同的一个子区间。把树建出来，现在的问题是每次可以选择多个“连续”的兄弟节点，并建立一个新点 $x$ 作为它们的父亲，再将 $x$ 设为它们原来父亲的儿子，要求最后的点数最多并求出方案数。

可以发现最后树一定是一个除叶子外每个节点都有两个儿子的树，因为如果有多个儿子则还可以新加点。因为这相当于每次将两个集合合并，所以除叶子外每个节点都有两个儿子的树总点数一定为 $2n-1$。

考虑设 $f_x$ 表示区间为 $[1,x],[1,1],[2,2],\dots,[x,x]$，那么有 $f_x=\sum\limits_{i=1}^{x-2}f_if_{x-i-1}$，发现这就是[卡特兰数递推式](https://oi-wiki.org/math/combinatorics/catalan/#%E9%80%92%E6%8E%A8%E5%BC%8F)，有 $f_x=H_{x-1}$。

设 $u$ 共有 $a_u$ 个儿子，那么显然答案就是 $\prod\limits_{u=1}^nH_{a_u-1}$。

建树可以用 `set` $O(n\log n)$ 实现，总复杂度可以做到 $O(n\log n)$。

[submission](https://codeforces.com/contest/2056/submission/319870899)

---

