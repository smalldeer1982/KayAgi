# Koa and the Beach (Hard Version)

## 题目描述

The only difference between easy and hard versions is on constraints. In this version constraints are higher. You can make hacks only if all versions of the problem are solved.

Koa the Koala is at the beach!

The beach consists (from left to right) of a shore, $ n+1 $ meters of sea and an island at $ n+1 $ meters from the shore.

She measured the depth of the sea at $ 1, 2, \dots, n $ meters from the shore and saved them in array $ d $ . $ d_i $ denotes the depth of the sea at $ i $ meters from the shore for $ 1 \le       i \le n $ .

Like any beach this one has tide, the intensity of the tide is measured by parameter $ k $ and affects all depths from the beginning at time $ t=0 $  in the following way:

- For a total of $ k $ seconds, each second, tide increases all depths by $ 1 $ .
- Then, for a total of $ k $ seconds, each second, tide decreases all depths by $ 1 $ .
- This process repeats again and again (ie. depths increase for $ k $ seconds then decrease for $ k $ seconds and so on ...). Formally, let's define $ 0 $ -indexed array $ p = [0, 1, 2,           \ldots, k - 2, k - 1, k, k - 1, k - 2, \ldots, 2, 1] $ of length $ 2k $ . At time $ t $ ( $ 0 \le t $ ) depth at $ i $ meters from the shore equals $ d_i + p[t \bmod 2k] $ ( $ t \bmod 2k $ denotes the remainder of the division of $ t $ by $ 2k $ ). Note that the changes occur instantaneously after each second, see the notes for better understanding.

At time $ t=0 $ Koa is standing at the shore and wants to get to the island. Suppose that at some time $ t $ ( $ 0 \le t $ ) she is at $ x $ ( $ 0 \le x \le n $ ) meters from the shore:

- In one second Koa can swim $ 1 $ meter further from the shore ( $ x $ changes to $ x+1 $ ) or not swim at all ( $ x $ stays the same), in both cases $ t $ changes to $ t+1 $ .
- As Koa is a bad swimmer, the depth of the sea at the point where she is can't exceed $ l $ at integer points of time (or she will drown). More formally, if Koa is at $ x $ ( $ 1 \le x         \le n $ ) meters from the shore at the moment $ t $ (for some integer $ t\ge 0 $ ), the depth of the sea at this point — $ d_x + p[t \bmod 2k] $ — can't exceed $ l $ . In other words, $ d_x + p[t \bmod 2k] \le l $ must hold always.
- Once Koa reaches the island at $ n+1 $ meters from the shore, she stops and can rest. Note that while Koa swims tide doesn't have effect on her (ie. she can't drown while swimming). Note that Koa can choose to stay on the shore for as long as she needs and neither the shore or the island are affected by the tide (they are solid ground and she won't drown there).

Koa wants to know whether she can go from the shore to the island. Help her!

## 说明/提示

In the following $ s $ denotes the shore, $ i $ denotes the island, $ x $ denotes distance from Koa to the shore, the underline denotes the position of Koa, and values in the array below denote current depths, affected by tide, at $ 1, 2,       \dots, n $ meters from the shore.

In test case $ 1 $ we have $ n = 2, k = 1, l = 1, p = [ 0, 1 ] $ .

Koa wants to go from shore (at $ x = 0 $ ) to the island (at $ x = 3 $ ). Let's describe a possible solution:

- Initially at $ t = 0 $ the beach looks like this: $ [\underline{s}, 1, 0, i] $ .
- At $ t = 0 $ if Koa would decide to swim to $ x = 1 $ , beach would look like: $ [s, \underline{2}, 1, i] $ at $ t =         1 $ , since $ 2 > 1 $ she would drown. So Koa waits $ 1 $ second instead and beach looks like $ [\underline{s}, 2, 1,         i] $ at $ t = 1 $ .
- At $ t = 1 $ Koa swims to $ x = 1 $ , beach looks like $ [s, \underline{1}, 0, i] $ at $ t = 2 $ . Koa doesn't drown because $ 1 \le 1 $ .
- At $ t = 2 $ Koa swims to $ x = 2 $ , beach looks like $ [s, 2, \underline{1}, i] $ at $ t = 3 $ . Koa doesn't drown because $ 1 \le 1 $ .
- At $ t = 3 $ Koa swims to $ x = 3 $ , beach looks like $ [s, 1, 0, \underline{i}] $ at $ t = 4 $ .
- At $ t = 4 $ Koa is at $ x = 3 $ and she made it!

We can show that in test case $ 2 $ Koa can't get to the island.

## 样例 #1

### 输入

```
7
2 1 1
1 0
5 2 3
1 2 3 2 2
4 3 4
0 2 4 3
2 3 5
3 0
7 2 3
3 0 2 1 3 0 1
7 1 4
4 4 3 0 2 4 2
5 2 3
1 2 3 2 2```

### 输出

```
Yes
No
Yes
Yes
Yes
No
No```

# 题解

## 作者：_xinyu1113 (赞：10)

### 放在前面
- ~~2200难度的题我能在比赛时做出来真是个奇迹~~
- ~~再说一句，B1我还真不会~~
### 理论
- 我们列一个表（例子五）
- 7 2 3
- 3 0 2 1 3 0 1
```cpp
除以6
余3-6 3 5 4 6 3 4
余4-5 2 4 3 5 2 3
余5-4 1 3 2 4 1 2
余0-3 0 2 1 3 0 1
余1-4 1 3 2 4 1 2
余2-5 2 4 3 5 2 3
余3-6 3 5 4 6 3 4
```
注意：表是经过变形的，从余3开始
- 显而易见，应该从**开始退潮后**离海岸最近的一列**第一次**进入安全水位后入海。
- 接下来，将表的安全水位用1标出，其余用0。
```cpp
0 1 0 0 0 1 0
0 1 0 1 0 1 1
0 1 1 1 0 1 1
1 1 1 1 1 1 1
0 1 1 1 0 1 1
0 1 0 1 0 1 1
0 1 0 0 0 1 0
```
解法显而易见了
- 接下来**能往右下角走**的就**往右下角走**（普通列），不行就等到能往前走，遇到**无论什么时候都在安全水位**的列（特殊列）就等到**重新退潮**再继续走。
- 显然要重新回到第一行就要通过**无论什么时候都在安全水位**的列。（等到最后一行后循环到第一行）
- 以上过程对于每列都可以用max（普通列）和直接移动到第一行+max（特殊列）来用1至2次运算实现
### 无法到达的判定
无法向右下角走，也无法向下走
### 程序
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a,n,k,l,m,las,p;
int main()
{
	cin>>a;
	for(int i=0;i<a;i++)
	{
		p=1;
		las=0;
		cin>>n>>k>>l;
		for(int j=0;j<n;j++)
		{
			cin>>m;
			if(m>l)//走不通
			{
				p=0;
			}
			else if(m+k<=l)//特殊列
			{
				las=0;
			}
			else if(las<k)//普通列
			{
				las=max(las+1,k-(l-m));
			}
			else
			{
				if(k+(l-m)<las+1)//走不通
				{
					p=0;
				}
				else
				las++;//往下一行，往前一列
			}
		}
			if(p==1)
			cout<<"Yes"<<endl;
			else
			cout<<"No"<<endl;
	}
    return 0;
}
```
## 写在后面
~~不知道cf上dp的tag是从哪来的~~

---

## 作者：Meatherm (赞：6)

如果存在 $d_i>l$，那么 Koa 一定会溺水，所以她无法到达岛上。这种情况可以通过简单的代码进行判断，在接下来，我们假设 $d_i \leq l$。

我们定义一个位置是安全的，当且仅当任何时间停留在该位置都不会溺水，否则该位置是不安全的。根据定义，$0$，$d_i+k \leq l$ 的 $i$ 以及 $n+1$ 是安全的。

Koa 可以采用以下策略前进：

- 如果她在时间 $t$ 处在一个不安全的位置 $x$，那么她需要在不溺水的前提下尽快到达 $x+1$。如果不可能存在这样的时间，那么她无法到达岛上。
- 如果她在时间 $t$ 处在一个安全的位置 $x$，那么她需要等待一个时间 $t_0 \geq t$，使得该时间潮汐高度在下降，且能安全地到达 $x+1$。在此前提下，使潮汐尽可能地高。

该策略可以证明。

首先，让我们证明，如果可以从一个安全位置 $i$ 到达下一个安全位置 $j$，那么在她从 $i$ 到 $j$ 的过程中，潮汐高度**至多下降一次**。如果潮汐从 Koa 到达一个不安全的位置 $m(i+1<m<j)$ 时开始**再次**开始下降，那么潮汐在上一秒高度为 $k$。如果 Koa 在上一秒所处的位置 $b$ 时没有溺水，那么有 $p_{b}+k \leq l$，$b$ 将是一个安全的位置，于是这和定义矛盾。

根据上面的结论，显然在潮汐尽可能地高且在下降时从 $i$ 出发最优。如果因为出发过早，当前潮汐过高而导致无法到达 $m (i<m<j)$，那么我们可以在原地等待潮汐高度下降。但如果出发太晚，潮汐高度会提前开始上升，这会使到达后面的位置变得困难。

例如，$n=2,k=2,l=3,d=[2,3]$。最优策略是在潮汐高度为 $2$ 时离开位置 $0$，这样到达位置 $1$ 时潮汐高度为 $1$。然而并不可以在潮汐高度为 $1$ 时离开位置 $0$ —— 这样会使到达位置 $1$ 时潮汐高度提前开始上升，无法到达位置 $2$。

**Code**

```cpp
# include <bits/stdc++.h>
# define rr
# define int long long
const int N=300010,INF=0x3f3f3f3f;
int n,k,l;
int d[N];
std::vector <int> safe;
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
signed main(void){
	int T=read();
	while(T--){
		n=read(),k=read(),l=read();
		safe.resize(0);
		safe.push_back(0);
		bool flag=false;
		for(rr int i=1;i<=n;++i){
			d[i]=read();
			if(d[i]>l){
				flag=true;
			}else if(d[i]+k<=l){
				safe.push_back(i);
			}
		}
		if(flag){
			puts("No");
			goto End;
		}
		safe.push_back(n+1);
		d[0]=d[n+1]=0;
		for(rr int i=0;i<(int)safe.size()-1;++i){
			int now=k,down; // 离开 i 时的高度尽可能地高
			down=(now>0);
			for(rr int j=safe[i];j<safe[i+1];++j){
				if(j+1==n+1){ // 安全位置不受影响
					puts("Yes");
					goto End;
				}else if(j+1==safe[i+1]){
					break;
				}else if(!down){ // 如果已经在上升 便不可能等待下降
					if(now+1+d[j+1]>l){
						puts("No");						
						goto End;
					}
					else
						++now;	
				}else{
					now=std::min(now-1,l-d[j+1]); // 等待最早能通过的时间
					if(!now){//到达 0 便开始上升
						down=0;
					}
				}
			}
		}
		End:;
	}

	return 0;
}
```

---

## 作者：JWRuixi (赞：3)

~~这题 $2200$ 评绿……~~

- 题意

给定长度为 $n$ 的序列 $d$，参数 $k$ 和 $l$，数组 $p = [0,1,2,...,k-1,k,k-1,...,1]$，时刻 $t$ 能到达 $i$ 当且仅当 $p_{t\bmod 2k} + d_i \le l$。

- 分析

首先有两种特殊点：

1. $k+d_i\le l$，这种跟起点差不多，可以随时进入下一个位置。
2. $d_i > l$，直接祭，根本过不去。

那考虑其他普通点，站在那里不动肯定是等死，只能越往前跑越好，知道遇到的一种特殊点可以喘一口气，当然跑着跑着可能就祭了。

那怎么跑呢？你观察到对于每一个点，它可以通行的时间区间是一个以 $k$ 为中心的对称的区间，那每次跑到左端点，看看有没有撞上右端点即可，注意不能时间倒流，起码要加 $1$。

- code

```cpp
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(3e5 + 500);
int T, n, k, l, d[maxn];

int main () {
	T = read();
	while (T--) {
		n = read(), k = read(), l = read();
		for (int i = 1; i <= n; i++) d[i] = read();
		int pos = 0;
		for (int i = 1; i <= n; i++) {
			if (d[i] > l) {
				puts("No");
				goto end;
			}
			if (d[i] + k <= l) {
				pos = 0;
				continue;
			}
			pos = max(pos + 1, k + d[i] - l);
			if (pos > k + l - d[i]) {
				puts("No");
				goto end;
			}
		}
		puts("Yes");
		end:;
	}
}
```

---

## 作者：_edge_ (赞：1)

双倍经验，有 easy 和 hard 两个版本。

这里介绍 hard 如何做。

我们看到这种题目，首先把那个限制稍微搞搞掉。

$p_{t \bmod 2k} \le l- d_i$ 变成了这样子的形式。

我们发现，这个 $p$ 是个上升之后又下降，因此对于每一个人，合法的时刻一定是一段前缀和后缀。

考虑计算出这段前缀和后缀。

先不考虑全部时刻合法的情况，对于单独一个岛来说，设它后缀到达的是 $r$，则 $r$ 一定是比较优秀的点，因为 $r$ 这个点，它后面是下降的，并且是接上一段前缀的。

不妨把一开始的设成 $r_1$，然后考虑如何判断它是否合法。

那么一种简单的想法就是对当前的时刻进行讨论。

如果在 $k$ 的后面：

设 $t$ 表示前一个时刻。

一种情况是 $t<r_i$ 那么下一个时刻一定得等到 $r_i$，否则就不合法。

还有一种情况是 $r_i \le t$ 那么当前时刻 $+1$ 即可。

如果在 $k$ 前面：

设 $l_i$ 表示他这个地方能到达的前缀。

一种情况是 $t<l_i$，这种情况 $t+1$ 即可。

另外一种情况就不合法了。

考虑加进来所有时刻合法的，我们记一个变量表示他前面是否是全部合法的，这样碰到一个不是的话，就把 $t$ 设为他的 $r_i$ 即可。

当然，如果 $d_i>l$ 则一定不合法。

贪心题细节稍微有点多，读者可以尝试自己实现。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=3e5+5;
struct _node_data{
	int l,r;
}aa[INF];
int n,k,l,d[INF],t;
signed main()
{
	ios::sync_with_stdio(false);
	cin>>t;
	while (t--) {
		cin>>n>>k>>l;
		int fl=0;
		for (int i=1;i<=n;i++) {
			cin>>d[i];
			int xx=l-d[i];
			if (xx<0) fl=1;
			aa[i].l=xx;aa[i].r=2*k-xx;
		}
		int la=aa[1].r,S=0;
		if (aa[1].l>=aa[1].r) S=1;
		if (la>=2*k) la=0;
		for (int i=2;i<=n;i++) {
//			cout<<aa[i].l<<" "<<aa[i].r<<" "<<la<<" "<<S<<" ?\n";
			if (aa[i].l>=aa[i].r) S=1;
			else if (S) {la=aa[i].r;S=0;continue;} 
			if (la>=2*k) la=0;
			if (la>=k) {
				if (aa[i].r>2*k) la=0;
				else if (aa[i].r<=la) la++;
				else la=aa[i].r;
			}
			else {
				if (aa[i].l>la) la++;
				else fl=1;
			}
			if (la>=2*k) la=0;
		}
		if (fl) cout<<"No\n";
		else cout<<"Yes\n";
	}
	return 0;
}
```


---

## 作者：_wkjzyc (赞：1)

考虑维护在一个位置上可以停留的时刻。

如果前一个位置可以一直停留，那这个位置的合法时刻会形如 $[0,d_{max}]\cup [2k-d_{max}+1,2k]$，其中 $d_{max}=l-d$。为了便于处理，我们把 $[0,k]$ 的区间向右平移 $2k$ 个单位，它就是一个关于 $2k$ 对称的区间 $[2k-d_{max},2k+d_{max}]$。

前一个位置不能一直停留，考虑用前一个位置的区间 $[l,r]$ 推出下一个位置的区间。如果 $[l,r]\cap[2k-d_{max},2k+d_{max}]\neq \emptyset$，这个位置是合法的，并且可以停在 $[\max(l,2k-d_{max}),2k+d_{max}]$ 中，把它向右平移 $1$ 就是下一个位置的区间；否则无解。注意特判。

（感觉其他题解做法都好奇怪。）

```cpp
scanf("%lld%lld%lld",&n,&k,&l);
a=k,b=3*k,flag=1; //区间 [a, b], 答案
for(int i=1;i<=n;i++) {
	scanf("%lld",&d);
	if(a>2*k+(l-d)||b<2*k-(l-d)||l<d) flag=0;
	a=max(a,2*k-(l-d))+1,b=2*k+(l-d)+1;
	if(b>3*k) a=k,b=3*k;
}
puts(flag?"Yes":"No");
```

---

## 作者：Provicy (赞：1)

$\text{Solution}$：

不错的贪心题。

考虑把 $n$ 个点分成两种位置。对于任何时间在 $i$ 位置都是安全的点，我们的策略显然是找到最优的时间去 $i+1$（如果 $i+1$ 不在任何时间都安全），称其为一类点；否则，称其为二类点，到达这个点之后，也是要找到最优的时间去 $i+1$。如果 $i$ 这个点变成不安全前都去不了 $i+1$，那就是 ``NO`` 的答案。问题转化为找到对于每个点来说，最优的转移时间。

对于一类点的转移，只需要考虑当 $i$ 是一类点且 $i+1$ 是二类点即可。有一个贪心就是，我们想转移到 $i+1$ 点后，**可以停留**的时间越长越好，原因是：如果不这么转移，那么在 $2K$ 的一轮时间内，在 $i+1$ 点停留的可行时刻的右端点还是相同的。故在 $p$ 递减且第一次满足 $p_{t\%2K}+d_{i+1}<=L$ 时即可转移。

对于二类点的转移，分成 $p$ 在递增和 $p$ 在递减分类讨论。

当 $p$ 在递增时，如果无法转移，那么 $p$ 必然会递增到 $K$，此时 $i$ 这个位置就不安全，故答案为 ``NO``；否则为了避免进入上面的情况，就直接转移。

当 $p$ 在递减时，情况与一类点转移类似，故只需要考虑第一次满足 $p_{t\%2K}+d_{i+1}<=L$ 时直接转移即可。

贪心的模拟即可。

$\text{Code}$：

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register
#define mk make_pair
#define E (N+1)
using namespace std; const int N=300010;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
int n,K,L,a[N],c[N];
signed main()
{
	for(ri int T=read();T;T--)
	{
		n=read(), K=read(), L=read();
		c[0]=c[n+1]=1;
		int spec=0;
		for(ri int i=1;i<=n;i++)
		{
			a[i]=read();
			if(a[i]>L)
			{
				spec=1;
			}
			if(a[i]+K<=L) c[i]=1;
			else c[i]=0;
		}
		if(spec) { puts("No"); continue; }
		for(ri int i=1;i<=n;)
		{
			int ud=0;
			while(i<=n && c[i]) i++;
			int now=-1;
			while(i<=n && !c[i])
			{
				if(!(~now))
				{
					ud=-1;
					now=L-a[i];
					i++;
					continue;
				}
				while(i<=n && !c[i])
				{
					if(!now) ud=1;
					if(now==K) ud=-1;
					if(now+ud+a[i]<=L) now+=ud;
					else
					{
						if(ud==1)
						{
							spec=1;
							break;
						}
						else now=L-a[i];
					}
					i++;
				}
				now=-1;
				if(spec) break;
			}
		}
		(spec)?puts("No"):puts("Yes");
	}
	return 0;
}
```


---

