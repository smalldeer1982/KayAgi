# TV Shows

## 题目描述

There are $ n $ TV shows you want to watch. Suppose the whole time is split into equal parts called "minutes". The $ i $ -th of the shows is going from $ l_i $ -th to $ r_i $ -th minute, both ends inclusive.

You need a TV to watch a TV show and you can't watch two TV shows which air at the same time on the same TV, so it is possible you will need multiple TVs in some minutes. For example, if segments $ [l_i, r_i] $ and $ [l_j, r_j] $ intersect, then shows $ i $ and $ j $ can't be watched simultaneously on one TV.

Once you start watching a show on some TV it is not possible to "move" it to another TV (since it would be too distracting), or to watch another show on the same TV until this show ends.

There is a TV Rental shop near you. It rents a TV for $ x $ rupees, and charges $ y $ ( $ y < x $ ) rupees for every extra minute you keep the TV. So in order to rent a TV for minutes $ [a; b] $ you will need to pay $ x + y \cdot (b - a) $ .

You can assume, that taking and returning of the TV doesn't take any time and doesn't distract from watching other TV shows. Find the minimum possible cost to view all shows. Since this value could be too large, print it modulo $ 10^9 + 7 $ .

## 说明/提示

In the first example, the optimal strategy would be to rent $ 3 $ TVs to watch:

- Show $ [1, 2] $ on the first TV,
- Show $ [4, 10] $ on the second TV,
- Shows $ [2, 4], [5, 9], [10, 11] $ on the third TV.

This way the cost for the first TV is $ 4 + 3 \cdot (2 - 1) = 7 $ , for the second is $ 4 + 3 \cdot (10 - 4) = 22 $ and for the third is $ 4 + 3 \cdot (11 - 2) = 31 $ , which gives $ 60 $ int total.

In the second example, it is optimal watch each show on a new TV.

In third example, it is optimal to watch both shows on a new TV. Note that the answer is to be printed modulo $ 10^9 + 7 $ .

## 样例 #1

### 输入

```
5 4 3
1 2
4 10
2 4
10 11
5 9
```

### 输出

```
60```

## 样例 #2

### 输入

```
6 3 2
8 20
6 22
4 15
20 28
17 25
20 27
```

### 输出

```
142```

## 样例 #3

### 输入

```
2 1000000000 2
1 2
2 3
```

### 输出

```
999999997```

# 题解

## 作者：p_b_p_b (赞：6)

恶意评分害死人……

这题略一思考，就可以得出结论：只需要贪心地在选用原有电视和借新电视之间选择较小的即可

读入节目的开始结束时间时存入另一个数组里，记录这是开始/结束，然后按时间为第一关键字，开始/结束为第二关键字sort，扫一遍即可

用完的电视不要扔，~~裹上面包糠~~堆进栈里，下次可能还要用。用旧电视当然优先选用最近用完的，减小空着的时间

代码实现难度并不大，思维难度也不大，不知道怎么被评成紫题了

```cpp
#include<bits/stdc++.h>
#define sz 200020
#define mod (int)(1e9+7)
using namespace std;
typedef long long ll;
struct hh{ll t,id;bool d;}s[sz];
inline bool cmp(const hh &x,const hh &y){return x.t==y.t?x.d<y.d:x.t<y.t;}
struct hhh{ll l,r;}a[sz];
int n;
ll X,Y;
int main()
{
	ll i,x,y;
	cin>>n>>X>>Y;
	for (i=1;i<=n;i++) cin>>x>>y,a[i]=(hhh){x,y},s[i*2-1]=(hh){x,i,0},s[i*2]=(hh){y,i,1};
	stack<int>st;
	ll ans=0;
	sort(s+1,s+n+n+1,cmp);
	for (i=1;i<=n+n;i++)
	{
		if (s[i].d) st.push(s[i].t);
		else
		{
			y=a[s[i].id].r;
			if (st.empty()) (ans+=(X+Y*(y-s[i].t)%mod)%mod)%=mod;
			else
			{
				x=st.top();
				if (Y*(y-x)<X+Y*(y-s[i].t)) (ans+=Y*(y-x)%mod)%=mod,st.pop();
				else (ans+=(X+Y*(y-s[i].t)%mod)%mod)%=mod;
			}
		}
	}
	cout<<ans;
}
```

---

## 作者：一扶苏一 (赞：5)

## Description

给定 $n$ 个电视节目和两个参数 $x,y$。你想要看全部的电视节目，但是同一个电视机同一个时刻只能播放一个电视节目，所以你只能多租赁电视机。在时间 $[l,r]$ 租赁一台电视机的花费是 $x~+~y~(r - l)$。一台电视机不可以在节目没有播放完时中断播放。求最小花费。答案对 $1e9+7$ 取模

## Input

第一行是三个整数 $n, x, y$

下面 $n$ 行每行两个整数 $l,r$，代表节目时间

## Output

一行一个整数代表答案对 $1e9+7$ 取模的结果

## Hint

$1~\leq~n~\leq~10^5~,~1~\leq~y~<~x~\leq~10^9~,~1~\leq~l~\leq~r~\leq~10^9$

## Solution

考虑贪心，有如下结论：

#### 一、如果必须租赁新的电视机，在结束租赁的时间一定的情况下，租赁时间越晚越好。

这个结论显然，因为租赁时间越晚，租赁时长的代价越低。

#### 二、如果前面有好几台空闲的电视机可以用，在不考虑租赁新的电视机时，一定选择上次结束时间最靠后的一台。

例如：

![qwq](https://cdn.luogu.com.cn/upload/pic/47909.png)

我们一定选择三号机器而不是一号二号，因为这样“浪费”的时间更少，即从上个节目结束到这个节目开始的时间花费更少。考虑如果后面紧跟着还有一个节目（开始时当前节目未结束），则它会选择一号，与这次选择一号下次选择三号相比，答案不会更劣。

以上是感性的理解结论二，下面给出结论二的证明（参考自官方题解）：

先将节目顺序按照左端点排序。因为每个节目时长再乘 $y$ 是的花费是不变的，因此我们只比较额外的花费。即租赁新电视机的花费和**续**时的花费。下面的花费均值额外花费

考虑我们有两个用过的电视机 $o1,o2$，其中 $r_{o1}~<~r_{o2}$， $r$ 为该电视上个节目的结束时间。当前我们要分配 $i$ 这个节目。

下面分三种情况：

###### 第一种：

如果后面不存在一个 $j$ 使得从两个中继承过来比新租一个更划算的话，显然把 $o2$ 分配给 $i$ 更优

###### 第二种：

如果后面存在一个 $j$，使得 $(l_j ~-~r_{o2})~y~\leq~x~~(1)$，但是 $(l_j ~-~r_{o1})~y~>~x~~(2)$，我们如果将 $o1$ 分配给 $i$，那么花费是 $(l_j~-~r_{o2})~y~+~(l_i~-~r_{o1})~y~~(3)$。考虑将 $o2$ 分配给 $i$，那么花费是 $(r_l~-~r_{o1})~y~+~x~~(4)$。给 $(2)$ 式左右同加 $(l_i~-~r_{o2})~y$ 即得 $(l_j ~-~r_{o1})~y~+~(l_i~-~r_{o2})~y>~x~+~(l_i~-~r_{o2})~y$，即 $(3)~>~(4)$，所以讲 $o2$ 分配给 $i$ 更优

###### 第三种：

如果后面存在一个 $j$，使得 $(l_j ~-~r_{o2})~y~\leq~x~~(1)$，并且 $(l_j ~-~r_{o1})~y~\leq~x~~(2)$，那么这两种分配方式分别花费是 $(l_j~-~r_{o2})y~+~(l_i~-~r_{o1})y~=~y(l_j~+~l_i~-~r_{o2}~-~r_{o1})$ 和 $(l_i~-~r_{o2})y~+~(l_j~-~r_{o1})y~=~y(l_j~+~l_i~-~r_{o2}~-~r_{o1})$。所以上两式是相等的，选择 $o2$ 给 $i$ 不会更劣。证毕。

那么我们就有如上两个贪心策略，每次比较贪心策略那个更优即可。即：新选择一个电视机租赁或者选择上次结束时间最靠后的一个电视机。根据结论一，如果选上次租赁过的而不是新租赁一个更好的话，因为新租赁电视机的时间被推迟了，答案一定不会更劣。于是这个贪心是正确的。

## Code

```cpp
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 100010;
const int maxm = 200010;
const int MOD = 1000000007;

struct M {
	int l, r;
	inline bool operator<(const M &_others) const {
		return this->r < _others.r;
	}
};
M MU[maxn];

struct Zay {
	int id, pos;
	bool Is_Begin;
	inline bool operator<(const Zay &_others) const {
		if (this->pos != _others.pos) return this->pos < _others.pos;
		else if (this->Is_Begin ^ _others.Is_Begin) return this->Is_Begin;
		else return this->id < _others.id;
	}
};
Zay CU[maxm];

int n, x, y, cnt, scnt, ans;
int stack[maxm];

int main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(x); qr(y);
	for (rg int i = 1; i <= n; ++i) {
		qr(MU[i].l); qr(MU[i].r);
		Zay &_temp = CU[++cnt];
		_temp.id = i; _temp.pos = MU[i].l; _temp.Is_Begin = true;
		Zay &_tp = CU[++cnt];
		_tp.id = i; _tp.pos = MU[i].r;
	}
	std::sort(CU + 1, CU + 1 + cnt);
	for (rg int i = 1; i <= cnt; ++i) {
		if (CU[i].Is_Begin) {
			ll payd = x + 1ll * (MU[CU[i].id].r - MU[CU[i].id].l) * y;
			if (scnt) {
				if ((1ll * (MU[CU[i].id].r - stack[scnt]) * y) < payd) {
					payd = 1ll * (MU[CU[i].id].r - stack[scnt]) * y;
					--scnt;
				}
			}
			ans = (ans + payd) % MOD;
		} else {
			stack[++scnt] = CU[i].pos;
		}
	}
	qw(ans, '\n', true);
	return 0;
}
```

---

## 作者：Drind (赞：0)

### 题目解析
我们第一个拿到这道题应该都能想到要把这些区间合并吧。最朴素的思路就是按照左端点排序之后找左端点最小的比这个点右端点还大的，也就是当前枚举到第 $i$ 个点，找到一个 $j$ 点满足 $l_j \gt r_i$ 且 $l_j$ 最小。这样答案更新为 $ans-x+y\times \left(l_j-r_i\right)$，对于这个 $j$ 点怎么寻找，应该可以用权值线段树之类的做法搞一搞。

但是这个做法实在是太复杂了，不够优美。我们回想旧的做法遇见什么问题。枚举每个区间，找到第一个左端点大于这个区间右端点的，但是我们要按照左端点排序，所以我们查询就是一个区间而不是整段。（注意到我们可以倒序做，这样每次只需要查询 $r_i$ 以后的所有数据，但是存在 $k$ 满足 $l_k \gt l_i$ 但 $l_k \le r_i$，也就是两个区间重叠。）

如果我们按照右端点排序呢？显然并没有解决刚才的问题。我们回想一下，在更新答案的时候，我们只使用了枚举到的区间的右端点和找到新区间的左端点，也就是 $r_i$ 和 $l_j$，但是我们并不在意这两个区间的长度。所以我们可以把一个区间的两个端点拆开考虑。按照所在位置从大到小排序，对于左端点，进栈，对于右端点，直接拿出栈内最小的（栈头）和他自己匹配。

实现方法见代码注释。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e6+10;
const int p=1e9+7;
int n,x,y,ans; 

struct node{
	int l,r;
}s[N];

struct dat{//拆点，val代表位置，id代表是第几个区间，lr代表左端点/右端点
	int val,id,lr;
}d[N]; int cnt;

inline void fake_main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>s[i].l>>s[i].r;
		ans=(ans+x+(s[i].r-s[i].l)*y)%p;//先假设没有一个区间被合并统计答案
		d[++cnt]={s[i].l,i,1};//加点
		d[++cnt]={s[i].r,i,0};
	}
	sort(d+1,d+cnt+1,[](dat x,dat y){
		if(x.val!=y.val//先按位置从大到小排序
			return x.val>y.val;
		return x.lr<y.lr;//左端点排在右端点后面，因为右端点不能匹配和自己位置相同的左端点，换句话说区间端点不相交才能合并
	});
	stack<int>st;
	for(int i=1;i<=cnt;i++){
		if(d[i].lr){//左端点直接进栈
			st.push(d[i].id);
		}else{//如果是右端点，栈中所有左端点都比这个右端点大，而且栈内还是有序的，栈顶就是最小值，直接取栈顶即可。
			if(st.empty()) continue;
			int R=st.top();
			if((s[R].l-s[d[i].id].r)*y<x){//如果合并区间有收益，那就合并，不然就不管了
				st.pop();
				ans=((ans+(s[R].l-s[d[i].id].r)*y-x)%p+p)%p;//模加模防止出现负数
			} 
		}
	}
	cout<<ans<<"\n";
}

signed main(){
	ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}
```

---

## 作者：_edge_ (赞：0)

观察一下样例，可以发现无非就两种决策，区间合并，或者是再开一台新电视。

显然，对于任意 $l,r$ $(r-l) \times y$ 的贡献都会被计算进去，不妨在一开始就计算掉。

不妨先假设每一个区间都要一台电视。

然后，发现这个东西本质就是寻找一个最小的 $l-r$，然后把 $(l-r) \times y$ 和 $x$ 进行比较，若前者大，证明这两个区间可以合并掉，并且合并了之后会使答案变得更优，我们就把它合并掉，并且将其视为另一个加进来的区间。

对于更一般的情况，就是寻找一个区间的 $r$ 最接近的另外一个区间的 $l$，这个东西可以使用 multiset 比较迅速地维护。

去思考这类题目时，可以尝试将左端点/右端点排序看看是否有最优的策略。

在这类题目里面，可以发现显然区间要左端点排序，即最开始的区间要最先处理。

当然，不要忘记开 long long。

如果有问题还请指出。

总时间复杂度 $O(n \log n)$。

```cpp
#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#define int long long 
using namespace std;
const int Mod=1e9+7;
const int INF=1e5+5;
struct _node_data{
	int l,r;
}aa[INF];
int n,x,y,l[INF],r[INF],ans; 
multiset <int> s;
bool cmp(_node_data xx,_node_data yy) {
	return xx.l<yy.l;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>x>>y;
	for (int i=1;i<=n;i++)
		cin>>l[i]>>r[i],ans+=x,ans+=y*(r[i]-l[i])%Mod,ans%=Mod,aa[i].l=l[i],aa[i].r=r[i];
	sort(aa+1,aa+1+n,cmp);
	for (int i=1;i<=n;i++)
		l[i]=aa[i].l,r[i]=aa[i].r;
	for (int i=1;i<=n;i++) {
		multiset<int>::iterator it=s.lower_bound(l[i]);
		if (s.begin()==it) { 
			s.insert(r[i]);
			continue;
		}
		it--;
		if ((l[i]-(*it))*y<x) {
			ans+=(l[i]-(*it))*y%Mod-x%Mod;ans%=Mod;
			ans+=Mod;ans%=Mod;
			s.erase(s.find(*it));
		}	
		s.insert(r[i]);
	}
	ans%=Mod;
	ans+=Mod;ans%=Mod;
	cout<<ans<<"\n";
	return 0;
}
```


---

