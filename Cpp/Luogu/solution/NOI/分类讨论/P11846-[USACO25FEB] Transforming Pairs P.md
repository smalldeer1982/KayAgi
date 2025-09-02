# [USACO25FEB] Transforming Pairs P

## 题目描述

回答 $Q$（$1\le Q\le 10^5$）个独立查询，每个查询的形式如下：

给定四个整数 $a$，$b$，$c$，$d$（$-10^{18}\le a,b,c,d\le 10^{18}$）。在一次操作中，你可以执行 $a\mathrel{+}=b$，或 $b\mathrel{+}=a$。求将 $(a,b)$ 转变为 $(c,d)$ 所需要的最小操作次数，或者如果不可能完成，输出 $-1$。

## 说明/提示

样例 1 解释：

第一个查询：$(5,-3)\to (2,-3)\to (-1,-3)$。

第二个查询：不可能。

第三个查询：$(5,3) \to (8, 3) \to (8, 11) \to (8, 19)$。

第四个查询：不需要任何操作。


- 测试点 $2$：$|a|, |b|, |c|,|d|\le 10$。
- 测试点 $3$：$a,b\ge 0$。
- 测试点 $4$：$a \geq 0 \geq b$。
- 测试点 $5$：$a \leq 0 \leq b$。
- 测试点 $6$：$a,b\le 0$。
- 测试点 $7$：$c,d\ge 0$。
- 测试点 $8$：$c \geq 0 \geq d$。
- 测试点 $9$：$c \leq 0 \leq d$。
- 测试点 $10$：$c,d\le 0$。
- 测试点 $11\sim 14$：$Q \leq 10^3$。
- 测试点 $15\sim 19$：没有额外限制。

## 样例 #1

### 输入

```
4
5 -3 -1 -3
5 3 5 2
5 3 8 19
5 3 5 3```

### 输出

```
2
-1
3
0```

# 题解

## 作者：Twilight_star (赞：11)

[题目链接](https://www.luogu.com.cn/problem/P11846)

首先先讨论弱化版 [P11841	[USACO25FEB] Transforming Pairs S](https://www.luogu.com.cn/problem/P11841)。

弱化版保证 $a,b,c,d>0$。从 $(a,b)$ 开始推有点难，因为很难判断到底要进行多少次各个操作。于是考虑从 $(c,d)$ 开始倒推。

我们发现，$(c,d)$ 的前置状态是确定的：

- 当 $c>d$ 时，只能从 $(c-d,d)$ 转移过来。
- 当 $c<d$ 时，只能从 $(c,d-c)$ 转移过来。
- 当 $c=d$ 时，能从 $(c,0)$ 或 $(0,d)$ 转移过来，但是弱化版讨论范围在正整数，所以暂时不考虑。

这个前置状态很像用更相减损法求 $\gcd$ 的过程。但是更相减损法是 $O(V)$ 的，$V$ 为值域大小。考虑换成更快的欧几里得法求 $\gcd$ 的过程。将多次 $c\gets c-d$ 和多次 $d\gets d-c$ 操作作为一组放在一起讨论。

每一次操作钦定 $c>d$，若不符则 $\operatorname{swap(a,b)},\operatorname{swap(c,d)}$。然后判断是否有 $b=d$ 且 $c$ 减去若干个 $d$ 后能等于 $a$ 即可。时间复杂度为 $O(\log V)$。

--- 

现在考虑本题。我们按 $a,b,c,d$ 的正负进行分类讨论：

### 1. $a,b$ 同号 (包含 $a=0$ 或 $b=0$)

此时如果 $a<0$ 或 $b<0$，就把 $a,b,c,d$ 全部变为它自己的相反数。

于是一定有 $a,b\ge 0$。考虑用类似弱化版的做法。但是需要进行更改，因为弱化版不用考虑 $0$ 的情况，本题这里需要考虑。

回顾弱化版，当 $c=d$ 时，会将 $c$ 或 $d$ 减为 $0$。换成欧几里得法，就是 $c \bmod d=0$ 时，会将 $c,d$ 其中一个减为 $0$。则进行分类讨论：

- 如果将 $c$ 减为 $0$

  则最终 $(c,d)$ 会成为 $(0,d)$。于是 $a=0$ 且 $b=d$ 则可以成功。

- 如果将 $d$ 减为 $0$

  则一定是将 $(c,d)$ 减为 $(d,d)$ 然后再一步减为 $(d,0)$。所以 $a=d$ 且 $b=0$ 时也是可以的。

代码如下：
```cpp
int calc(int a,int b,int c,int d)
{//计算 a,b>=0 时的答案
	if(c<0||d<0) return -1;
	if(a==c&&b==d) return 0;
	int res=0;
	while(c!=0&&d!=0)
	{
		if(a==c&&b==d) return res;
		if(c<d) swap(c,d),swap(a,b);
		if(b==d&&c>=a&&c%d==a%d) return res+(c-a)/d;//能否把c删成a 
		if(c%d==0&&((a==0&&b==d)||(a==d&&b==0))) return res+c/d;//删成0是否满足要求 
		res+=c/d;
		c%=d;
	}
	if(a==c&&b==d) return res;
	return -1;
}
void solve()
{
	a=read(),b=read(),c=read(),d=read();
	if(a==c&&b==d) return printf("0\n"),void();
	if(a<=0&&b<=0) a=-a,b=-b,c=-c,d=-d;
	if(a<0) swap(a,b),swap(c,d); 
	if(a>=0&&b>=0)//a,b同号 
	{
		if(c<0||d<0) return printf("-1\n"),void();
		return printf("%lld\n",calc(a,b,c,d)),void();	
	}
}
```

### 2. $a,b$ 异号，$c,d$ 异号

我们会发现，在操作途中，当 $a,b$ 从异号变成了同号，则不可能再变成异号。

于是当 $a,c$ 不同号，$b,d$ 不同号时则无解。

剩下的情况仅剩 $a,c$ 同号，$b,d$ 同号。我们模拟从 $(a,b)$ 出发的操作，因为不能让数改变符号，所以每一次只能是让绝对值大的数加上绝对值小的数。并且操作途中 $a,b$ 的绝对值会不断减小。

举个例子，现在 $(a,b)$ 满足 $|a|>|b|,a>0,b<0$，此时则一定变成 $(a+b,b)$，则只看绝对值的话会从 $(|a|,|b|)\to (|a|-|b|,|b|)$。这样只看绝对值是不是有点像上种情况的从 $c,d$ 倒推的情形。

于是这种情况的答案为上种情况 $(c,-d)\to (a,-b)$ 的答案。（钦定 $c>0$）

```cpp
//a,b异号，c,d异号，已保证a>0
if(c<0&&d>0) return printf("-1\n"),void();
if(c>=0&&d<=0) return printf("%lld\n",calc(c,-d,a,-b)),void();
```

### 3. $a,b$ 异号，$c,d$ 同号

现在需要考虑 $a,b$ 从异号变为同号的过程。先钦定 $a,c,d>0,b<0$。如果不符可以通过交换和取相反数满足。

我们把它搬到平面直角坐标系上讨论。存在两个坐标 $(a,b),(c,d)$。那么无论是从 $(a,b)$ 开始推还是从 $(c,d)$ 开始倒推都是不断在向 $x$ 轴靠近。直到某一次操作**我们让** $(a,b)$ 变为同号。

![](https://cdn.luogu.com.cn/upload/image_hosting/msla845v.png)

其实什么时候让 $a,b$ 变为同号是我们自己选择的。当 $a>-b$ 时，如果不想跨过 $x$ 轴则走到 $(a+b,b)$，但是如果我们向跨过 $x$ 轴，则可以直接走到 $(a,a+b)$。

如下图，蓝色边为跨过 $x$ 轴的转移边。

![](https://cdn.luogu.com.cn/upload/image_hosting/9ax2y889.png)

我们会发现，对于一段连续的向左的一组转移，我们可以从中选择一个点向上转移，并且向上转移后的落点在一条斜率为 $1$ 的直线上。

但是，有些落点是无法到达 $(c,d)$ 的。所以我们还要求出可以到达 $(c,d)$ 的所有点，再与所有落点取交集，才是真正合法的落点。

设 $(x,y)$ 为真正合法的落点之一，根据落点的定义，则一定有 $x<y$。所以从 $(c,d)$ 开始倒推的话， 到达 $(x,y)$ 下一步应该向左走。于是将所有向左走的点与所有落点取交即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/ja2utjj9.png)

于是枚举 $(c,d)$ 倒推向左走的每一组，并预处理出 $(c,d)$ 到这一组第一个点的操作次数。再枚举 $(a,b)$ 正推向左走的每一组，并预处理出 $(a,b)$ 到这一组第一个点的操作次数。

然后对交点计算总的操作次数即可。

注意不要漏掉落点在 $x$ 轴上的情况。

总时间复杂度 $O(q\log^2V)$。

具体判断条件见代码：

```cpp
//a,b异号，c,d同号
if(c<=0&&d<=0) a=-a,b=-b,c=-c,d=-d; 
if(a<0) swap(a,b),swap(c,d);

vector< array<int,3> > q;
for(int x=c,y=d,num=0;x>0&&y>0;)
{
  if(y>=x) num+=y/x,y%=x;
  else q.push_back({y,x,num}),num+=x/y,x%=y;
}//预处理 (c,d) 倒推时到达每一个向左组的操作次数 

int ans=inf,num=0;//num为(a,b)到当前组的 
while(a>0&&b<0)
{
  if(a+b==0)//向上走到坐标轴上 
  {
    ans=min(ans,num+1+calc2(a,0,c,d)); //calc2(a,b,c,d): 当calc(a,b,c,d)==-1时为inf，否则为calc(a,b,c,d) 
    break;
  }
  if(a+b<0)//向上走，不用考虑穿过坐标轴 
  {
    num+=(-b)/a;
    b=-((-b)%a);
    continue;
  }
  //向左走 
  for(auto i:q)//枚举 (c,d) 倒推途中向左转移的组 
  { 
    int y=i[0],mx=i[1];
    if(y<=a+b&&(a-y)%(-b)==0)//(a,a+b)为本组最右的落点 
    {
      int k=(a+b-y)/(-b);//本组第几个点 
      int x=a+k*b;//落点横坐标 
      if(x<=mx&&(mx-x)%y==0) ans=min(ans,num+i[2]+1+k+(mx-x)/y);//落点能在(c,d)路径上 
    }
   } 
  if(a%(-b)==0) ans=min(ans,num+a/(-b)+calc2(-b,0,c,d));//向上拐，走到x轴上 
  num+=a/(-b);
  a%=(-b);
}
if(a>=0&&b>=0) ans=min(ans,num+calc2(a,b,c,d));
if(ans>=inf) printf("-1\n");
else write(ans),putchar('\n');
```

---

## 作者：Purslane (赞：5)

# Solution

简单模拟题。

先考虑 $a,b \ge 0$ 的情况（显然 $a,b \le 0$ 可以转化过来）。发现过程中一定有 $a' \ge 0$、$b' \ge 0$ 恒成立。如果出现 $c<0$ 或 $d<0$ 无解。

所以如果我们知道了 $(c,d)$，往前推一步，要么是 $(c-d,d)$，要么是 $(c,d-c)$。显然如果 $c \neq d$，肯定是大的减去小的。而如果 $c=d$，则 $(c,0)$ 和 $(0,c)$ 都可以作为上一步。

所以我们直接模拟辗转相除即可。最小步数存在且唯一。

------

接下来考虑 $a>0$、$b<0$ 的情况。（因为 $a$ 和 $b$ 高度对称，所以可以大量化归。）

如果 $c<0$ 且 $d>0$，显然不可能成功了。

否则，如果 $c \ge 0$ 且 $d \le 0$，不妨设 $a' = a$、$b' = -b$，则 $(a,b) \to (a+b,b)$ 可以改写为 $(a,-b') \to (a-b',-b')$。所以我们可以把他倒过来写，也就是等价于求解 $(c,-d) \to (a,-b)$。

否则，不妨设 $c,d > 0$。

显然一定会出现某一个时刻满足 $a',b' \ge 0$。如果我们能找到这样一个位置，那么也就转化为最开始的情形了。

如果当前 $a+b=0$，那么下一步一定就会出现 $(0,b)$ 或者 $(a,0)$，可以直接暴力检验。

否则，如果 $a > -b$，下一步可以是 $(a+b,b)$，也可以是 $(a,a+b)$。发现后者就满足我们所需的“出现 $a',b' \ge 0$”，检验他。

我们会不断执行 $a \leftarrow a+b$ 直到 $a \le -b$。所以我们会对若干个 $k$ 计算 $(a+kb,a+(k+1)b)$ 如何转移到 $(c,d)$，最后令 $a \leftarrow a+tb$。

此时不妨设 $a < -b$。那么转移到 $(a+b,b)$ 或者 $(a,a+b)$。前者没有任何前途，因为会直接出现 $a',b' < 0$。所以我们直接辗转相除跳到下一个端点即可。

但是我们会计算非常多次 $(a,b) \to (c,d)$，这及其不友好。

发现我们可以将这样的 $(a,b)$ 划分为 $O(\log V)$ 段，每一段的 $a-b$ 为定值，且这个东西随着段的增加是递增的。

而将 $(c,d)$ 反方向往前推的时候，$c-d$ 在 $c > d$ 的时候是严格递减的，所以可以直接维护几个等差数列，使用双指针优化即可做到 $O(\log V)$ 单组询问。（不过你直接写 $O(\log^2 V)$ 的能过，而且还挺快）

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
int T,a,b,c,d;
int solve(int a,int b,int c,int d) {
	if(c<0||d<0) return -1;
	int ans=0;
	if(a==c&&b==d) return 0;
	while(c!=0&&d!=0) {
		if(c==d) {
			if(a==0&&b==c||a==c&&b==0) return ans+1;
			if(a==c&&b==d) return ans;
			return -1;
		}
		if(c<d) swap(c,d),swap(a,b);
		if(c%d==0&&(a==0&&b==d||a==d&&b==0)) return ans+c/d;
		if(b==d&&a<=c&&(c-a)%d==0) return ans+(c-a)/d;
		ans+=c/d,c%=d;
	}
	if(a==c&&b==d) return ans;
	return -1;
}
void check(int &ans,int mzx,int nv) {
	if(mzx==-1) return ;
	ans=min(ans,mzx+nv);	
}
struct INFO {int l1,l2,r,d;};
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>a>>b>>c>>d;
		if(a==c&&b==d) {cout<<0<<'\n';continue ;}
		if(a<=0&&b<=0) a=-a,b=-b,c=-c,d=-d;
		if(a>=0&&b>=0) {cout<<solve(a,b,c,d)<<'\n';continue ;}
		if(a<0) a=-a,b=-b,c=-c,d=-d;
		if(c>=0&&d<=0) {cout<<solve(c,-d,a,-b)<<'\n';continue ;}
		if(c<0) swap(a,b),swap(c,d),a=-a,b=-b,c=-c,d=-d;
		if(c<0&&d>0) {cout<<-1<<'\n';continue ;}
		vector<INFO> vc;
		int cc=c,dd=d;
		while(cc!=0&&dd!=0) {
			if(cc<=dd) {dd%=cc;continue ;}
			vc.push_back({cc%dd+dd,cc,dd,dd}),cc%=dd;
		}
		int v=__gcd(c,d);
		int ans=LONG_LONG_MAX,al=0;
		while(a>0&&b<0) {
			if(a+b==0) {check(ans,solve(a,0,c,d),al+1);break ;}
			if(a+b<0) {al+=(-b)/a,b=-((-b)%a);continue ;}
			if(-b==v) {
				int dl1=v,dl2=v,rr=0,ll=v;
				if(ll<=a&&(a-ll)%(-b)==0) check(ans,solve(ll,rr,c,d),al+(rr-a)/b);
			}
			for(auto id:vc) {
				int dl1=id.l1-id.r,dl2=id.l2-id.r;
				if(dl1<=-b&&-b<=dl2&&(-b-dl1)%id.r==0) {
					int rr=id.r,ll=rr-b; 
					if(ll<=a&&(a-ll)%(-b)==0) check(ans,solve(ll,rr,c,d),al+(rr-a)/b);
				}
			}
			al+=a/(-b),a=a%(-b);
		}
		if(a>=0&&b>=0) check(ans,solve(a,b,c,d),al);
		if(ans!=LONG_LONG_MAX) cout<<ans<<'\n';
		else cout<<-1<<'\n';
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P11846)

**题目大意**

> 给定数对 $(a,b)$，每次操作可以变成 $(a+b,b)$ 或 $(a,a+b)$，求变成 $(c,d)$ 的最少步数，$q$ 次询问。
>
> 数据范围：$q\le 10^5$。

**思路分析**

先从 $a,b\ge 0$ 的情况开始，那么整个过程中 $a,b$ 均非负。

那么从 $(c,d)$ 倒推，前一步一定是 $(c,d-c)$ 或 $(c-d,d)$，容易发现 $c\ne d$ 时只有一个状态满足两个数均非负。

那么我们模拟对 $(c,d)$ 的辗转相除法即可算出答案。

然后只需要考虑 $a>0>b$ 的情况，如果 $c<0<d$ 显然无解，如果 $c>0>d$，那么我们可以把这个过程看成 $(c,-d)\to (a,-b)$ 的问题，也能解决。

现在只需要考虑 $c,d>0$ 的情况。

我们的想法就是从 $(a,b)$ 出发，如果得到某个 $a,b\ge 0$ 的状态，那么直接算出到 $(c,d)$ 的最短路。

因此我们只要在 $a,b$ 均异号的前提下拓展状态，$a+b<0$ 时，一定变成 $(a,b+a)$。

$a+b>0$ 时，$(a,a+b)$ 直接算最短路，然后变成 $(a+b,b)$。

那么我们要计算所有 $(a+(k-1)b,a+kb)\to (c,d)$ 的最短路，其中 $a+kb\ge 0$。

但是很显然这个过程中很多的 $(a+(k-1)b,a+kb)$ 并不能走到 $(c,d)$，我们要求这个数对 $(x,y)$ 在刚才 $(c,d)$ 的辗转相除过程中出现过。

注意到 $x\ge y$，而辗转相除的过程中这样的 $y$ 只有 $\mathcal O(\log V)$ 个，枚举每个 $y$ 算出对应的 $k$，然后计算最短路。

预处理 $(c,d)$ 走到 $(x_0,y)$ 的距离，可以直接 $\mathcal O(1)$ 计算出最短路，因此复杂度 $\mathcal O(\log^2V)$。

时间复杂度 $\mathcal O(q\log^2V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf=4e18;
ll f(ll a,ll b,ll c,ll d) {
	if(c<0||d<0) return -1;
	if(a==c&&b==d) return 0;
	ll s=0;
	while(c&&d) {
		if(c<d) swap(a,b),swap(c,d);
		if(b==d&&a<=c&&(c-a)%d==0) return s+(c-a)/d;
		if(c%d==0&&a==d&&!b) return s+c/d;
		s+=c/d,c%=d;
	}
	return a==c&&b==d?s:-1;
}
ll F(ll a,ll b,ll c,ll d) {
	ll z=f(a,b,c,d);
	return ~z?z:inf;
}
void solve() {
	ll a,b,c,d;
	cin>>a>>b>>c>>d;
	if(a<=0&&b<=0) a=-a,b=-b,c=-c,d=-d;
	if(a>=0&&b>=0) return cout<<f(a,b,c,d)<<"\n",void();
	if(a<0) a=-a,b=-b,c=-c,d=-d;
	if(c<0&&d>0) return cout<<"-1\n",void();
	if(c>=0&&d<=0) return cout<<f(c,-d,a,-b)<<"\n",void();
	if(c<0) a=-a,b=-b,c=-c,d=-d,swap(a,b),swap(c,d);
	vector <array<ll,3>> S;
	for(ll x=c,y=d,z=0;x&&y;) {
		if(y>=x) z+=y/x,y%=x;
		else S.push_back({y,x,z}),z+=x/y,x%=y;
	}
	ll ans=inf,s=0;
	while(a>0&&b<0) {
		if(a+b==0) {
			ans=min(ans,s+1+F(a,0,c,d));
			break;
		}
		if(a+b<0) {
			s+=(-b)/a,b=-((-b)%a);
			continue;
		}
		for(auto it:S) {
			ll y=it[0],mx=it[1];
			if(y<a&&(a-y)%(-b)==0) {
				ll k=(y-a)/b,x=a+(k-1)*b;
				if(x<=mx&&(mx-x)%y==0) ans=min(ans,s+k+it[2]+(mx-x)/y);
			}
		}
		if(a%(-b)==0) ans=min(ans,s+a/(-b)+F(-b,0,c,d));
		s+=a/(-b),a%=-b;
	}
	if(a>=0&&b>=0) ans=min(ans,s+F(a,b,c,d));
	cout<<(ans==inf?-1:ans)<<"\n";
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int _; cin>>_;
	while(_--) solve();
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：1)

首先考虑 $a\ge 0,b\ge 0$ 的情形。判掉 $c<0$ 或 $d<0$ 的情况。那么倒着考虑的话，相当于可以让 $c,d$ 之间较大的数减去较小的数，直到变成 $(a,b)$。那么从 $(c,d)$ 变成 $(c,d\bmod c)$ 的过程只会进行 $O(\log n)$ 轮，暴力做复杂度是对的。

$a\le 0,b\le 0$ 则只需要将 $a,b,c,d$ 都取反。那么我们只用考虑 $a,b$ 异号的情况。不妨设 $a<0<b$，且 $|a|\le |b|$。考虑转化为 $a,b$ 同号。

先进行若干次 $b+=a$ 得到 $(a,b),(a,b+a),\ldots,(a,b+2a),\ldots$，再进行一次 $a+=b$，得到 $(a+b,b),(2a+b,a+b),\ldots$。设 $k$ 是最大的满足 $ka+b\ge 0$ 的非负整数。对于 $(a+b,b),(2a+b,a+b),\ldots,(ka+b,(k-1)a+b)$ 这些数对，可以转化为 $a,b\ge 0$ 的情形，只需要改动一下上面的做法，把这些数对包装起来再执行上面的算法。而对于 $((k+2)a+b,(k+1)a+b),((k+3)a+b,(k+2)a+b),\ldots$ 这些数对，同理可以转化到 $a,b\le 0$ 的情形。唯一的问题在于 $((k+1)a+b,ka+b)$，我们递归求解。递归的层数是 log 级别的，每一层只用调用 $O(1)$ 次上面的算法，于是总复杂度就是两只 log。

还有若干 corner cases，在此略过不提。

我考场的石山代码，惨被卡常两个测试点，于是成为了离 ak 最近的一次：

```cpp
```

UPD：实在卡不过去了，放一份原始代码：

```cpp
#include<bits/stdc++.h>
bool Mbg;
/*--------------------------------------------------------------------------------------*/
#define cin cio
#define cout cio
#define Fs 100000
#define inline __inline__ __attribute__((always_inline))
#define iopt inline IO& operator
#define Tc()(_A==_B&&(_B=(_A=Fi)+fread(Fi,1,100000,stdin),_A==_B)?EOF:*_A++)
#define Pc(Ch)(FS<Fs?Fo[FS++]=Ch:(fwrite(Fo,1,Fs,stdout),Fo[(FS=0)++]=Ch))
int Tp,FS;char Ch,*_A,*_B,Fi[Fs],Fo[Fs],Sk[Fs];
struct IO{
	template<typename T>
	iopt>>(T&x){bool Fl=0;x=0;while(!isdigit(Ch=Tc()))Fl|=Ch=='-';while(x=10*x +(Ch&15),isdigit(Ch=Tc()));if(Fl)x=-x;return*this;}
	iopt>>(char*x){int I=0;for(;((x[I]=Tc())!=' ')&&(x[I]!='\n');++I);x[I]='\0';return*this;}
	iopt>>(char&x){x=Tc();return*this;}
	template<typename T>
	iopt<<(T x){if(!x){return Pc('0'),*this;}if(x<0)Pc('-'),x=-x;while(x)Sk[++Tp]=x%10+48,x/=10;while(Tp)Pc(Sk[Tp--]);return*this;}
	iopt<<(const char*x){for(;*x!='\0';Pc(*(x++)));return*this;}
	iopt<<(char x){Pc(x);return*this;};~IO(){fwrite(Fo,1,FS,stdout),FS=0;}void tie(int){}
}cio;/*----------------------------------------------------------------------------------*/
using namespace std;
#define vec vector
#define pb push_back
#define eb emplace_back
#define siz(vec) ((int)(vec).size())
#define all(vec) (vec).begin(),(vec).end()
template<class T>
void operator +=(vec<T> &a,T b){a.push_back(b);}
template<class T>
void operator --(vec<T> &a){a.pop_back();}
#define pii pair<int,int>
#define x first
#define y second
#define mp make_pair
#define exc(exp) if(exp)continue;
#define stop(exp) if(exp)break;
#define ret(exp) if(exp)return;
#define deb(var) cerr<<#var<<'='<<(var)<<"; "
#define debl(var) cerr<<#var<<'='<<(var)<<";\n"
#define ins insert
#define era erase
#define lb lower_bound
#define ub upper_bound
#define int long long
#define inf (long long)((2e18)+1024)
template<class T>
bool Min(T &x,T y){return x>y?x=y,1:0;}
template<class T>
bool Max(T &x,T y){return x<y?x=y,1:0;}
const int mod=998244353;
void Add(int &x,int y){x=x+y<mod?x+y:x+y-mod;}
void Dec(int &x,int y){x=x>=y?x-y:x-y+mod;}
int fpm(int x,int y){
    int ans=1;for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)ans=1ll*x*ans%mod;return ans;
}

int a,b,c,d;

double sT;
int sol2(int c,int d,int a,int b,int D){
    // (a,b)
    // (a-D,b-D)
    // (a-2D,b-2D)
    // ...
    // 变成 (c,d)

    if(c<0||d<0){
        return inf;
    }
    auto STEP=[&](int c,int d){
        // a-kD=c,b-kD=d
        if(a<c)return inf;
        if((a-c)%D)return inf;
        int k=(a-c)/D;
        if(b-k*D!=d)return inf;
        return k;
    };
    int ans=STEP(c,d);
    if(c==0||d==0)return ans;
    if(c==d){
        return min({ans,1+STEP(0,c),1+STEP(c,0)});
    }
    if(c>d){
        return min(ans,sol2(d,c,b,a,D));
    }
    assert(c<=d);
    if(c<=a&&(a-c)%D==0){
        int A=c,B=b-a+c;
        // (A,B)
        // (c,d-c),(c,d-2c),...
        if(B<=d&&(d-B)%c==0){
            Min(ans,(d-B)/c+(a-c)/D);
        }
    }
    if(d%c==0){
        if(d/c-1<ans){
            Min(ans,d/c-1+sol2(c,c,a,b,D));
        }
        return ans;
    }else{
        if(d/c<ans){
            Min(ans,d/c+sol2(c,d%c,a,b,D));
        }
        return ans;
    }
}
int sol3(int c,int d,int a,int b,int D){
    // (a,b)
    // (a+D,b+D)
    // (a+2D,b+2D)
    // ...
    // 变成 (c,d)

    if(c<0||d<0){
        return inf;
    }
    auto STEP=[&](int c,int d){
        // a+kD=c,b+kD=d
        if(a>c)return inf;
        if((c-a)%D)return inf;
        int k=(c-a)/D;
        if(b+k*D!=d)return inf;
        return k;
    };
    int ans=STEP(c,d);
    if(c==0||d==0)return ans;
    if(c==d){
        return min({ans,1+STEP(0,c),1+STEP(c,0)});
    }
    if(c>d){
        return min(ans,sol3(d,c,b,a,D));
    }
    assert(c<=d);
    if(c>=a&&(c-a)%D==0){
        int A=c,B=b-a+c;
        // (A,B)
        // (c,d-c),(c,d-2c),...
        if(B<=d&&(d-B)%c==0){
            Min(ans,(d-B)/c+(c-a)/D);
        }
    }
    if(d%c==0){
        if(d/c-1<ans){
            Min(ans,d/c-1+sol3(c,c,a,b,D));
        }
        return ans;
    }else{
        if(d/c<ans){
            Min(ans,d/c+sol3(c,d%c,a,b,D));
        }
        return ans;
    }
}
int sol(int a,int b,int c,int d){
    if(c==a&&d==b){
        return 0;
    }
    // if(clock()-sT>=0.001*CLOCKS_PER_SEC){
    //     return inf;
    // }
    if(a>=0&&b>=0){
        if(c<0||d<0)return inf;
        if(c==0||d==0)return inf;
        if(c==d){
            return a==0&b==c||a==c&&b==0?1:inf;
        }
        if(c>d){
            return sol(b,a,d,c);
        }
        assert(c<=d);
        if(a==c){
            return d%c==b%c&&b<=d?(d-b)/c:inf;
        }
        if(d%c==0){
            return d/c-1+sol(a,b,c,c);
        }
        return d/c+sol(a,b,c,d%c);
    }else if(a<=0&&b<=0){
        return sol(-a,-b,-c,-d);
    }else if(a>b){
        return sol(b,a,d,c);
    }else{
        if(abs(a)==abs(b)){
            return min(sol(0,b,c,d)+1,sol(a,0,c,d)+1);
        }else if(abs(a)>abs(b)){
            return sol(-a,-b,-c,-d);
        }else{
            int ans=inf;
            if(c==a){
                if(d>b);
                else if((b-d)%(-a)){
                }else{
                    Min(ans,(b-d)/(-a));
                }
            }
            int D=(a+b-a-1)/(-a);
            Min(ans,1+sol2(c,d,a+b,b,-a));
            if(D+2<ans){
                Min(ans,D+2+sol3(-c,-d,-(a+b+a*(D+1)),-(b+a*(D+1)),-a));
            }
            if(D+1<ans){
                Min(ans,D+1+sol(a+b+a*D,b+a*D,c,d));
            }
            return ans;
        }
    }
}
void work(){
    cin>>a>>b>>c>>d;
    if(c==a&&d==b){
        cout<<"0\n";return;
    }
    if(ans>=inf)cout<<"-1\n";
    else cout<<ans<<'\n';
}
bool Med;
signed main(){
    ios::sync_with_stdio(0),
    cin.tie(0),cout.tie(0);
    int T=1;cin>>T;while(T--)work();
    // cerr<<"Time: "<<clock()<<" ms;\n";
    // cerr<<"Memory: "<<abs(&Med-&Mbg)/1024.0/1024.0<<" MiB.\n";
}
```

---

