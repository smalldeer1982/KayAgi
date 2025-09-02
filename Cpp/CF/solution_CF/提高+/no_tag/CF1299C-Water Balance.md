# Water Balance

## 题目描述

There are $ n $ water tanks in a row, $ i $ -th of them contains $ a_i $ liters of water. The tanks are numbered from $ 1 $ to $ n $ from left to right.

You can perform the following operation: choose some subsegment $ [l, r] $ ( $ 1\le l \le r \le n $ ), and redistribute water in tanks $ l, l+1, \dots, r $ evenly. In other words, replace each of $ a_l, a_{l+1}, \dots, a_r $ by $ \frac{a_l + a_{l+1} + \dots + a_r}{r-l+1} $ . For example, if for volumes $ [1, 3, 6, 7] $ you choose $ l = 2, r = 3 $ , new volumes of water will be $ [1, 4.5, 4.5, 7] $ . You can perform this operation any number of times.

What is the lexicographically smallest sequence of volumes of water that you can achieve?

As a reminder:

A sequence $ a $ is lexicographically smaller than a sequence $ b $ of the same length if and only if the following holds: in the first (leftmost) position where $ a $ and $ b $ differ, the sequence $ a $ has a smaller element than the corresponding element in $ b $ .

## 说明/提示

In the first sample, you can get the sequence by applying the operation for subsegment $ [1, 3] $ .

In the second sample, you can't get any lexicographically smaller sequence.

## 样例 #1

### 输入

```
4
7 5 5 7```

### 输出

```
5.666666667
5.666666667
5.666666667
7.000000000```

## 样例 #2

### 输入

```
5
7 8 8 10 12```

### 输出

```
7.000000000
8.000000000
8.000000000
10.000000000
12.000000000```

## 样例 #3

### 输入

```
10
3 9 5 5 1 7 5 3 8 7```

### 输出

```
3.000000000
5.000000000
5.000000000
5.000000000
5.000000000
5.000000000
5.000000000
5.000000000
7.500000000
7.500000000```

# 题解

## 作者：Alex_Wei (赞：20)

> [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1299C) & [CF题面传送门](http://codeforces.com/problemset/problem/1299/C)

> 题意简述：你可以对给定的序列进行无限次操作：选一个区间，使得该区间的所有数变成该区间的平均数，求操作后字典序最小的序列。

---

显然有一个 $\mathcal O(n^2)$ 的贪心思路：从左往右枚举每个 $i\in[1,n]$，再枚举一个 $j\in[i,n]$ 使得区间 $[i,j]$ 的平均值最小，将 $[i,j]$ 进行一遍上述操作。

当然，$10^6$ 的数据是不太可能让 $n^2$ 过去的。~~（暴力碾标算，$n$ 方过百万！）~~

观察一下样例 $3$（这个样例给的真不错），发现答案是一个不下降序列，这就启发我们用单调栈解决该问题。

首先，我们把序列中的每个数都看成一个长度为 $1$ 的区间，然后从左往右弹入栈中。**任意时刻**如果将要弹入栈中区间的平均值不大于栈顶区间的平均值，就将栈顶区间弹出，与将要弹入的区间合并。**这就保证了最后每个大区间的平均值是单调不降的**。

这道题目出的真心不错，赞一个 :)

赛时代码（没有用栈，用的 $\rm{vector}$，写的较丑，见谅）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+5;
struct seg{
	ll sum;
	int l,r;
};
ll n,a[N],cnt,l[N],r[N];
vector <seg> ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	ans.push_back({a[1],1,1});
	for(int i=2;i<=n;i++){
		ans.push_back({a[i],i,i});
		while(ans.size()>1){
			int len=ans.size();
			seg x=ans[len-2],y=ans[len-1];
			double avx=1.l*x.sum/(x.r-x.l+1),avy=1.l*y.sum/(y.r-y.l+1);
			if(avx>=avy)ans.pop_back(),ans.pop_back(),ans.push_back({x.sum+y.sum,x.l,y.r});
			else break;
		}
	}
	for(int i=0;i<ans.size();i++){
		seg x=ans[i];
		double ave=1.l*x.sum/(x.r-x.l+1);
		for(int j=x.l;j<=x.r;j++)printf("%.9lf\n",ave);
	}
	return 0;
}
```


---

## 作者：灵茶山艾府 (赞：7)

本质上是一道求凸包的题。

考察 $a$ 的前缀和 $sum$，画出前缀和的折线图（横坐标为 $i$，纵坐标为 $sum_i$，坐标原点也算上）。

然后把折线图的首尾相连，这样我们得到了一个多边形。

把某段区间的值修改成区间平均值的操作，就相当于把多边形上的两个点直接连起来，中间的线段去掉。

这样就很容易能看出，字典序最小的序列等价于多边形的凸包。遍历前缀和即可，复杂度 $O(n)$。

AC 代码（Golang）：

（没有高亮的话请点击 [在Ta的博客查看](https://www.luogu.com.cn/blog/endlesscheng/solution-cf1299c)）

```go
package main

import (
	"bufio"
	. "fmt"
	"os"
)

type vec struct{ x, y int64 }

func (a vec) sub(b vec) vec   { return vec{a.x - b.x, a.y - b.y} }
func (a vec) det(b vec) int64 { return a.x*b.y - a.y*b.x }

func main() {
	in := bufio.NewScanner(os.Stdin)
	in.Split(bufio.ScanWords)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()
	read := func() (x int) {
		in.Scan()
		for _, b := range in.Bytes() {
			x = x*10 + int(b-'0')
		}
		return
	}

	n := read()

	// 求前缀和
	sum := make([]int64, n+1)
	for i := 0; i < n; i++ {
		sum[i+1] = sum[i] + int64(read()) 
	}

	// 求凸包
	ps := make([]vec, 0, n+1)
	for i, sumi := range sum {
		p := vec{int64(i), sumi}
		for {
			sz := len(ps)
			if sz <= 1 || ps[sz-1].sub(ps[sz-2]).det(p.sub(ps[sz-1])) > 0 {
				break
			}
			ps = ps[:sz-1]
		}
		ps = append(ps, p)
	}

	// 计算凸包相邻两点对应区间的均值，区间为左闭右开
	for i := 1; i < len(ps); i++ {
		a, b := ps[i-1], ps[i]
		segLen := b.x - a.x
		avg := float64(b.y-a.y) / float64(segLen)
		for ; segLen > 0; segLen-- {
			Fprintf(out, "%.9f\n", avg)
		}
	}
}
```


---

## 作者：__gcd (赞：7)

注意到答案中的数列是不下降的，因为如果出现下降子段的话，将它们取平均数就可以使字典序更小。反过来说，要想得到答案，就必须通过操作使整个数列不下降。并且由于不下降，这个数列不可能通过操作使字典序更小。

于是可以得到结论：只要通过操作使整个数列不下降，那么它就是答案。

由于不下降，所以我们可以使用单调栈维护每个取过平均数的区间。每次新加进来一个数的时候，如果它能使栈顶的区间平均数更小，那么就贪心地将它与这个区间合并。合并之后，再看栈顶对应的区间能不能使栈中在它下面的区间平均数更小，再进行合并。如此反复，直到单调栈中的元素单调递增（不相等是因为平均数相等的区间可以直接合并）。由于上面的结论可知，这种方法能得到正确答案。

判断区间是否能合并的方法也很简单，只需要比较平均数即可，后面的区间如果比前面的区间平均数小，那么就可以合并。对于计算新区间的平均数，只需要维护两个区间的左端点，右端点和平均数，将其求和后再求平均数即可。

最后的分段结果保存在栈中。由于栈顶保存的是最后一个区间，所以需要递归倒序输出。

参考代码如下：


```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
using namespace std;
inline int read()
{
    int x = 0; bool op = 0;
	char c = getchar();
	while(!isdigit(c))op |= (c == '-'), c = getchar() ;
	while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
	return op ? -x : x;
}
const int N = 1000010;
int n;
db a[N];
struct Node
{
	int l, r;
	db val;
	Node(){l = r = val = 0;}
	Node(int l = 0, int r = 0, db val = 0):l(l), r(r), val(val){}
};
stack<Node> s;
db sum(Node a)
{
	return a.val * (a.r - a.l + 1);
}
void update(int x)
{
	Node p = Node(s.top().l, x, (sum(s.top()) + a[x]) / (x - s.top().l + 1));
	s.pop();
	while(s.empty() == false && p.val < s.top().val)
	{
		Node cur = s.top();
		s.pop();
		p.val = (sum(p) + sum(cur)) / (p.r - cur.l + 1);
		p.l = cur.l;
	}
	s.push(p);
	return ;
}
void print()
{
	if(s.empty() == true)
		return ;
	Node tmp = s.top();
	s.pop();
	print();
	for(int i = tmp.l; i <= tmp.r; i++)
		printf("%.9lf\n", tmp.val);
	return ;
}
int main()
{
	n = read();
	for(int i = 1; i <= n; i++)
		a[i] = read();
	for(int i = 1; i <= n; i++)
	{
		if(s.empty() == true || a[i] > s.top().val)
			s.push(Node(i, i, a[i]));
		else update(i);
	}
	print();
	return 0;
}
```
膜拜一下在课上想出正解的 @[hjl666](https://www.luogu.com.cn/user/89667) 大佬。

---

## 作者：wwlw (赞：2)

[Link](https://www.luogu.com.cn/problem/CF1299C)
------------

### Solution
要求字典序最小，那么前面的值要尽量小，那就不妨先考虑前面的值。两段有交部分的操作是很难处理的，肯定需要某种转换。所以想到观察两段有交的操作会产生什么样的效果。简单的分类讨论之后，会发现无论怎么操作都对前面的数没有正的贡献，反而有可能把前面的一段数变大。由于有交的操作一定不会更优，所以最后的操作一定是不相交的。那么问题就转换成了将一个序列分成若干段，满足越前面的段平均值越小越好，求最优的序列。

用增量法，假设前面已经有一个段了，考虑要不要把当前新的数加入这个段。如果合并后平均值变小了，那么合并进去更优；反之，则新开一段。但如果合并了后平均值变小了，就可能出现比更前面一段的平均值还小的情况，显然再把这两段合并更优。如此迭代。容易想到用单调栈来维护这个过程。

```cpp
#include<stdio.h>
#define N 1000007
#define db double

inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}

struct Node{
    db sum; int num;
    db calc(){return sum/num;}
    Node operator +(const Node &X) {
        Node A;
        A.sum=sum+X.sum,A.num=num+X.num;
        return A;
    }
}sta[N];

int n,top=0;
int main(){
    n=read();
    for(int i=1;i<=n;i++){
        Node now; now.sum=read(),now.num=1;
        while(top&&sta[top].calc()>now.calc()) 
            now=now+sta[top--];
        sta[++top]=now;
    }
    for(int i=1;i<=top;i++)
        for(int j=1;j<=sta[i].num;j++) printf("%.9lf\n",sta[i].sum/sta[i].num);
}
```

---

## 作者：little_sun (赞：2)

### 简要题意

你有一个序列$\{a\}$,你的每次操作可以把一段区间里的数全部变成这个区间的平均数，求能得到的字典序最小的序列

### 分析

我们发现字典序最小时显然$\{a_i\}$单调不降

那么我们可以维护一个单调栈，栈里维护的值$\{l,r,avr\}$，表示该段区间的左端点、右端点、平均值

每次插入$\{i,i,a_i\}$,然后暴力循环取出栈顶的两个节点$x, y$（$y$在$x$后插入）,如果满足$y.avr<x.avr$则合并$x,y$，直到不能合并为止（具体细节可以看代码）

最后把栈中记录的值输出即可

### 代码

```cpp
#include <bits/stdc++.h>
 
#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)
 
const int MaxN = 1e6 + 10;
 
struct node
{
    int l, r;
    double sum, len;
};
 
int n;
double a[MaxN];
std::vector<node> vec;
 
int main()
{
    int tmp;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &tmp), a[i] = tmp;
    for (int i = 1; i <= n; i++)
    {
        vec.push_back((node){i, i, a[i], 1});
        while (vec.size() >= 2 && (vec[vec.size() - 2].sum / vec[vec.size() - 2].len) >= (vec[vec.size() - 1].sum / vec[vec.size() - 1].len))
        {
            node x = (node){vec[vec.size() - 2].l, vec[vec.size() - 1].r, vec[vec.size() - 2].sum + vec[vec.size() - 1].sum, vec[vec.size() - 1].r - vec[vec.size() - 2].l + 1.0};
            vec.pop_back(), vec.pop_back(), vec.push_back(x);
        }
    }
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = vec[i].l; j <= vec[i].r; j++)
            a[j] = (vec[i].sum / vec[i].len);
    }
    for (int i = 1; i <= n; i++)
        printf("%.10lf\n", a[i]);
    return 0;
}
```







---

## 作者：syksykCCC (赞：1)

首先，$\mathcal O(n^2)$ 的思路十分好想。

大概就是说，我们发现答案序列是单调不降的，所以倒着来，对于每个位置 $i$，我们找一个它后面的位置 $j$，使得 $\frac{\sum_{k=i}^{j} a_k}{j-i+1}$ 是最小的，然后把这一段全部赋值为这个值。这样，我们就在优先确保前面的值更优时，得到了一个可靠的贪心策略。

因为 $10^6$ 肯定要更好的方法，所以考虑优化。当处理位置 $i$ 的时候，$(i, n]$ 已经处理好了，成为了一个不降的，若干个连续段组成的数列。而对于连续的一段，我们 **要不一起选，要不一起不选**，所以就可以用一个栈来维护后面的这个东西。栈里存一个三元组，表示这一段的左端点 $l$，右端点 $r$，以及总和 $w$。

比如这时，已选的数字的总和为 $sum$，已选的数字总个数为 $tot$，显然，如果处于栈顶的那一段（不妨叫做 $top$）能够 **拖低平均值**，即 $\frac{w_{top}}{r_{top}-l_{top} +1} \le \frac{sum}{tot}$（注意等于也可以不加，反正不会改变什么），那么我们就要选这一段。细节问题是避免浮点计算，交叉相乘，看看 $w_{top} \times tot \le sum \times (r_{top}-l_{top}+1)$ 就行了。

时间复杂度 $\mathcal O(n)$，下面是代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, l[N], r[N], top, a[N];
long long w[N];
double ans[N];
int main()
{
	scanf("%d", &n);
	for(register int i = 1; i <= n; i++) scanf("%d", &a[i]);
	top = 1;
	l[1] = r[1] = n;
	w[1] = a[n];
	l[0] = n + 1;
	for(register int i = n - 1; i; i--)
	{
		int tot = 1;
		long long sum = a[i];
		while(top && w[top] * tot <= sum * (r[top] - l[top] + 1))
		{
			sum += w[top];
			tot += r[top] - l[top] + 1;
			top--;
		}
		top++;
		r[top] = l[top - 1] - 1;
		l[top] = i;
		w[top] = sum;
	}
	for(register int i = 1; i <= top; i++)
		for(register int j = l[i]; j <= r[i]; j++) ans[j] = 1.0 * w[i] / (r[i] - l[i] + 1);
	for(register int i = 1; i <= n; i++) printf("%.10lf\n", ans[i]);
	return 0;
}
```

吐槽：

* 为啥 $\mathcal O(n^2)$ 能水过去？QwQ
* 为啥全部开 $\texttt{long double}$ 会 TLE? QwQ
* 为啥用 $\texttt{iostream}$ 会卡常？QwQ

~~所以这是一道毒瘤题……~~

---

## 作者：KJGKMTZB (赞：1)

$\text{前言：比赛时这题因为没看到n是1e6所以成功自闭了}$

$\text{本来是上分好场，打完发现遍地都是AK}$

$\text{我们考虑你现在在一个l，你要去选择一个r}$

$\text{不难发现你选择的r，首先要使得r上的值，必须小于l上的值}$

$\text{用set维护后面能选的比l小的r的所有val}$

$\text{用vector来存每个值的位置，并且每个vector里的位置是降序}$

$\text{其次再去选择最小的平均值}$

$\text{直接暴力遍历后面所有满足上面条件取min就好了}$

$\text{理论来说这玩意儿会被卡到}O(n^2log_2n) \text{（大雾）但数据水，能卡过去}$

$\Large{Code:}$

```
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <queue>
#include <vector>
#include <set>
#define intinf 0x7f7f7f7f
#define llinf 0x7f7f7f7f7f7f7f7f
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define ALL(a,x) for(int a=head[x];a;a=e[i].u)
#define pii pair<int,int> 
#define mp make_pair
#define fi first
#define se second
#define db long double
#define ll long long
#define ls rt<<1
#define rs rt<<1|1
using std::vector;
using std::pair;
using std::set;
template<class T>inline void read(T &x) {
	T f=1;x=0;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=(x<<1)+(x<<3)+(s&15);s=getchar();}
	x*=f;
}
template<class T>inline T fabs(T a) { return a>0?a:-a; }
template<class T>inline T max(T a,T b) { return a>b?a:b; }
template<class T>inline T min(T a,T b) { return a<b?a:b; } 
template<class T>inline T po(T a) { return a*a; }
const int maxn=1e6+6;
int n,m,now,b[maxn],tmp[maxn],top,s[maxn],lans,rans,siz[maxn];
db a[maxn],qz[maxn],nans,Ans;
vector<int> p[maxn];
vector<pii> ans;
set<int> pos;
inline db query(int l,int r) { return (qz[r]-qz[l-1])/((db)(r-l+1)); }
int main() {
	read(n);
	rep(i,1,n) scanf("%d",&b[i]),a[i]=(db)(b[i]),qz[i]=qz[i-1]+a[i];
	std::sort(b+1,b+n+1);
	m=std::unique(b+1,b+n+1)-b-1;
	rep(i,1,n) s[i]=std::lower_bound(b+1,b+m+1,(int)(a[i]))-b;
	rep(i,1,m) pos.insert(i);
	for(int i=n;i>=1;i--) p[s[i]].push_back(i);
	rep(i,1,m) siz[i]=(p[i].size()-1);
	now=1;
	while(now<=n) {
		if(now==n) {
			ans.push_back(std::make_pair(n,n)); break;
		}
		lans=now; rans=now; nans=a[now];
		top=0;
		for(int i:pos) {
			if(i>=s[now]) break;
			for(int k=0;k<=siz[i];k++) {
				if(p[i][k]<lans) {
					siz[i]=(k-1); break;
				}
				Ans=query(now,p[i][k]);
				if(Ans<nans) nans=Ans,rans=p[i][k];
			}
			if(siz[i]==-1) tmp[++top]=i;
		}
		rep(i,1,top) pos.erase(tmp[i]);
		ans.push_back(std::make_pair(lans,rans));
		now=rans+1;
	}
	now=0;
	rep(i,1,n) {
		printf("%.12Lf\n",query(ans[now].fi,ans[now].se));
		if(i==ans[now].se) now++;
	}
}
```

---

