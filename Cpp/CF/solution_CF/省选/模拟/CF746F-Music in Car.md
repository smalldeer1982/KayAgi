# Music in Car

## 题目描述

Sasha reaches the work by car. It takes exactly $ k $ minutes. On his way he listens to music. All songs in his playlist go one by one, after listening to the $ i $ -th song Sasha gets a pleasure which equals $ a_{i} $ . The $ i $ -th song lasts for $ t_{i} $ minutes.

Before the beginning of his way Sasha turns on some song $ x $ and then he listens to the songs one by one: at first, the song $ x $ , then the song $ (x+1) $ , then the song number $ (x+2) $ , and so on. He listens to songs until he reaches the work or until he listens to the last song in his playlist.

Sasha can listen to each song to the end or partly.

In the second case he listens to the song for integer number of minutes, at least half of the song's length. Formally, if the length of the song equals $ d $ minutes, Sasha listens to it for no less than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF746F/a0138c33f01c951ba371aceb046ff51db6674fec.png) minutes, then he immediately switches it to the next song (if there is such). For example, if the length of the song which Sasha wants to partly listen to, equals $ 5 $ minutes, then he should listen to it for at least $ 3 $ minutes, if the length of the song equals $ 8 $ minutes, then he should listen to it for at least $ 4 $ minutes.

It takes no time to switch a song.

Sasha wants to listen partly no more than $ w $ songs. If the last listened song plays for less than half of its length, then Sasha doesn't get pleasure from it and that song is not included to the list of partly listened songs. It is not allowed to skip songs. A pleasure from a song does not depend on the listening mode, for the $ i $ -th song this value equals $ a_{i} $ .

Help Sasha to choose such $ x $ and no more than $ w $ songs for partial listening to get the maximum pleasure. Write a program to find the maximum pleasure Sasha can get from the listening to the songs on his way to the work.

## 说明/提示

In the first example Sasha needs to start listening from the song number $ 2 $ . He should listen to it partly (for $ 4 $ minutes), then listen to the song number $ 3 $ to the end (for $ 3 $ minutes) and then partly listen to the song number $ 4 $ (for $ 3 $ minutes). After listening to these songs Sasha will get pleasure which equals $ 4+3+5=12 $ . Sasha will not have time to listen to the song number $ 5 $ because he will spend $ 4+3+3=10 $ minutes listening to songs number $ 2 $ , $ 3 $ and $ 4 $ and only $ 1 $ minute is left after that.

## 样例 #1

### 输入

```
7 2 11
3 4 3 5 1 4 6
7 7 3 6 5 3 9
```

### 输出

```
12
```

## 样例 #2

### 输入

```
8 4 20
5 6 4 3 7 5 4 1
10 12 5 12 14 8 5 8
```

### 输出

```
19
```

## 样例 #3

### 输入

```
1 1 5
6
9
```

### 输出

```
6
```

## 样例 #4

### 输入

```
1 1 3
4
7
```

### 输出

```
0
```

# 题解

## 作者：Mine_King (赞：7)

在[我的博客](https://www.cnblogs.com/mk-oi/p/14990076.html)阅读效果更佳。

## Problem

[CF746F](https://www.luogu.com.cn/problem/CF746F)  

**题目大意：**

有 $k$ 的时间，$n$ 首歌，听每首歌的时间不一定相同，要求按顺序听一段连续的歌，其中有 $w$ 首可以只听一半（向上取整）。每首歌有一个快乐值，听第 $i$ 首歌即可获得 $a_i$ 的快乐值（不论听整首还是半首），问能获得的最大的快乐值是多少。

## Solution

首先有一个很明显的事，就是对于每一个确定的区间左边界 $l$，一定要使 $r$ 尽可能的大，也就是确定做断电后，只要能扩展区间就扩展区间。然后看数据范围，$1\le n \le 2 \times 10^5$，可以想到要用 $O(n\log n)$ 或者 $O(n)$ 的算法。  
于是我们考虑用 two-pointers 解决这题。  
这时还需要用到一个贪心，就是对于目前 two-pointers 找到的一个区间 $[l,r]$，我们必然让时间最大的 $w$ 首歌只听一半。

具体实现时，我们可以用 STL 中的 `multiset<>` 来存储歌曲，这里不能用 `set<>` 是因为两首歌的时间可能一样。  
我们用两个 `multiset<>` $s_1,s_2$ 分别存储听一半的歌的**原本的时间**和听整首歌的时间。  
对于每次将要进入区间的一个数，我们进行分类讨论：

- 若只有不到 $w$ 首歌在 $s1$ 中且剩余时间足够听半首歌，弹入 $s_1$。
- 否则，若 $s_1$ 中原时间最小的数比当前数要小，则把当前数放入 $s_1$，将那个数放入 $s_2$。$s_1$ 存原时间的好处就在这里，如果存半首的时间，将无法确定原时间，把元素放入 $s_2$ 时就会出问题。另外，这里还要判一下放进去调整后的时间够不够用。
- 否则，若剩余时间够听整首歌，则把当前数放入 $s_2$。
- 否则，说明这个区间已经最大了，放不进去了，就需要弹出左端点。这里也需要分类讨论：
  - 若 $s_2$ 为空，左端点一定在 $s_1$ 中，删除即可。
  - 否则，若 $s_1$ 最小的数比左端点的时间大，那么左端点在 $_2$ 中，删除即可。
  - 否则，左端点在 $s_1$ 中，把左端点删除后， $s_1$ 不满而 $s_2$ 有数，把 $s_2$ 中最大的数放入 $s_1$。

于是就可以完成此题了！

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,w,k,a[200005],t[200005];
int T,res,ans;
multiset<int>s1,s2;
int main()
{
	scanf("%d%d%d",&n,&w,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&t[i]);
	int l=1,r=0;
	while(r<n)
	{
		r++;
		int tmp=*s1.begin();
		if((int)s1.size()<w&&T+(t[r]+1)/2<=k)
			s1.insert(t[r]),T+=(t[r]+1)/2,res+=a[r];
		else if(t[r]>tmp&&T-(tmp+1)/2+(t[r]+1)/2+tmp<=k)
		{
			s1.erase(s1.find(tmp));
			s1.insert(t[r]);
			s2.insert(tmp);
			T+=(t[r]+1)/2-(tmp+1)/2+tmp;
			res+=a[r];
		}
		else if(T+t[r]<=k) s2.insert(t[r]),T+=t[r],res+=a[r];
		else
		{
			r--;
			if(s1.empty()){r++;continue;}
			else if(s2.empty()) s1.erase(s1.find(t[l])),T-=(t[l]+1)/2;
			else if(t[l]<tmp) s2.erase(s2.find(t[l])),T-=t[l];
			else
			{
				int ttmp=*--s2.end();
				s1.erase(s1.find(t[l]));
				s1.insert(ttmp);
				s2.erase(s2.find(ttmp));
				T=T-(t[l]+1)/2-ttmp+(ttmp+1)/2;
			}
			res-=a[l];
			l++;
		}
		ans=max(ans,res);
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：zjh111111 (赞：5)

[link](https://www.luogu.com.cn/problem/CF746F)

中文的翻译不是那么清楚。

题意是有 n 首歌，每首歌有一个价值。现选一段**连续区间**的歌听，其中最多可选 w 首歌听 $\lceil \dfrac{t_i}{2} \rceil$ 分钟，其余听 $t_i$ 分钟，在满足听歌总时间 $\le k$ 的情况下求最大的价值和。

- 首先在明确区间 $[l,r]$ 的情况下，肯定选择听歌时间**前 w 大**的听一半，因为这样减少的听歌时间最多。

- 于是我们就有了一个 $O(n^2\log_{2}^n)$ 的做法：枚举左端点，右端点从左端点开始向右扫，每次用 set 维护前 w 大的听歌时间，更新答案即可。

	- 具体地，先将加入的时间 insert 进 set 中，如果 set 的 size 比 w 大的话，把 set 中最小的元素弹出，这样可以保证前 w 大的元素都在 set 里。

- 因为歌的价值都是非负的，所以可以用 **two-pointers** 优化这道题。

	- 具体地，L 初始等于1，向右枚举 R 并加点，若 $[L,R]$ 不满足听歌时间 $\le k$，则容易得到：当 $R'>R,L'<=L$ 时，$[L',R']$ 也不满足条件。所以此时删去点 L，$L \gets L+1$。

	- 加点同上，只是要多维护一个 set 保存弹出的较小的元素，在删点时判断当前删的 $t_L$ 在哪个 set 里，减去对应的时间，如果减去的时间原来是减半的，那么要把 维护弹出元素的 set 的最大值（如果有的话）放入 维护减半值的 set。

	- 可能不是那么直观，看代码会比较好懂。

```cpp

#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x) {
	char c = getchar(); int w = 1; x = 0;
	while (!isdigit(c))
		(c == '-') && (w = -w), c = getchar();
	while (isdigit(c))
		x = (x << 1) + (x << 3) + (c ^ '0'), c = getchar();
	x *= w;
}

const int N = 200010;
int n, w, k, a[N], b[N];
multiset<int> small, big;
multiset<int> :: iterator j;
signed main() {
	read(n); read(w); read(k);
	for (register int i=1; i<=n; ++i) {
		read(a[i]);
	}
	for (register int i=1; i<=n; ++i) {
		read(b[i]);
	}
	int l = 1, t = 0, v = 0, ans = 0;
	for (register int r=1; r<=n; ++r) {
		t += (b[r] + 1) / 2; v += a[r];
		big.insert(b[r]);
		if (big.size() > w) {
			small.insert(*(big.begin()));
			t += *(big.begin()) / 2; //ceil(x/2)+floor(x/2)=x
			big.erase(big.begin());
		}
		while (l <= r && t > k) {
			if (b[l] >= *big.begin()) {
				t -= (b[l] + 1) / 2;
				big.erase(big.find(b[l]));
				if (small.size()) {
					j = small.end(); -- j;
					big.insert(*j);
					t -= *j / 2;
					small.erase(j);
				}
			}
			else {
				small.erase(small.find(b[l])); t -= b[l];
			}
			v -= a[l ++];
		}
		ans = max(ans, v);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：water_tomato (赞：3)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf746f-music-in-car-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF746F)。

给定一个序列，包含 $n$ 个有重量和价值的物品。需要找出一个连续区间，可以选择其中的至多 $w$ 个物品令其重量减半（向上取整）而价值不变，然后该区间重量和须不大于 $k$。求满足这样条件的总价值最大的区间。

## 解析

求区间最大价值容易想到双指针。考虑如何维护重量减半（以下简称打折）的 $w$ 个物品。

由于元素会有重复，考虑用两个 multiset，一个用来维护打折的物品，另一个用来维护不打折的物品。

当加入一个新物品时，我们先将其加入打折物品中，然后如果打折物品超出了 $w$ 个，取出其中重量最小的令其不打折即可。这样就完成了右指针的右移操作。

当删除一个物品时，我们先将其与打折物品中重量最低的那个进行比较，如果其重量大于等于打折物品最小重量，说明其为打折物品，在打折物品中删除，然后如果有未打折物品的话，将其中重量最大的进行打折即可。如果其重量小于打折物品最小重量，直接在未打折物品中删除即可。

容易发现，在这些过程中我们很容易维护区间重量和以及区间价值和，本题至此解决。一些细节问题见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,w,k;
int a[N],t[N];
int l,now,happy,ans;
multiset<int> s1,s2;
int main(){
	scanf("%d%d%d",&n,&w,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&t[i]);
	l=1;
	for(int r=1;r<=n;r++){//双指针
		s1.insert(t[r]);
		now+=(t[r]+1)>>1;happy+=a[r];//加入物品
		if(s1.size()>w){//如果打折物品太多了，转移一个重量最小的
			s2.insert(*s1.begin());
			now+=*s1.begin();
			now-=(*s1.begin()+1)>>1;
			s1.erase(s1.begin());
		}
		while(now>k){//删除操作
			if(t[l]>=*s1.begin()){
				now-=(t[l]+1)>>1;
				s1.erase(s1.find(t[l]));//不能直接 erase(t[l])，因为该操作会把所有等重量的物品都删除，而我们只需要删除一个，因此需要 find() 一下
				if(!s2.empty()){
					s1.insert(*s2.rbegin());//rbegin() 取反向开头，比 end() 方便
					now-=*s2.rbegin();
					now+=(*s2.rbegin()+1)>>1;
					s2.erase(s2.find(*s2.rbegin()));
				}
			}
			else{
				now-=t[l];
				s2.erase(s2.find(t[l]));
			}
			happy-=a[l];//过程中重量和和价值和小心处理好
			l++;
		}
		ans=max(ans,happy);//更新答案
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：oisdoaiu (赞：2)

*tag:二分，主席树*

---
这是一个思维难度很低的做法。

## 题意

给定一个长度为 $n$ 的序列，每个位置有 $a_i,t_i$ 两个值，可以使至多 $w$ 个位置的 $t_i$ 变为 $\lceil\frac {t_i}2\rceil$ 。

求选择一个区间，使得区间内 $\sum t_i\le k$ 的前提下，$\sum a_i$ 最大。

## 题解

首先假设我们选定了一个区间，那么一定是让 $t_i$ 最大的 $w$ 个位置折半。

而且当 $l$ 固定时，$r$ 越大，$\sum a_i$ 和 $\sum t_i$ 就一定越大。

所以可以想到枚举 $l$，然后二分 $r$。

---
对于二分出的一个 $[l,r]$，我们想要快速求出 $\sum t_i$。

那么问题变为，区间 $[l,r]$ 内，对前 $w$ 大的 $t_i$，求出 $\sum \lceil\frac {t_i}2\rceil-t_i$。

然后把这个加到区间 $t_i$ 和上，就可以得到区间 $[l,r]$ 在折半 $w$ 个 $t_i$ 后的 $\sum t_i$。

而这个问题可以使用主席树+线段树上二分轻松解决。

```cpp
inline int Query(int l, int r){
	int res = S1[r]-S1[l-1];
	l = root[l-1]; r = root[r];
	int head=1, tail=lshcnt, rem=w;
	while(head<tail){
		int mid = head+tail >> 1;
		if(sz(rc(r))-sz(rc(l)) <= rem)
			rem -= sz(rc(r))-sz(rc(l)),
			res += sum(rc(r))-sum(rc(l)),
			l = lc(l), r = lc(r), tail = mid;
		else
			l = rc(l), r = rc(r), head = mid+1;
	}
	res += min(rem,sz(r)-sz(l))*((lsh[head]+1)/2-lsh[head]);
	return res;
}
```

---
复杂度 $O(n\log^2n)$。

[代码](https://www.luogu.com.cn/paste/rqht1o0j)

---

## 作者：Acfboy (赞：2)

对顶堆写过，对顶 `set` 还真没写过……

看到题目有个很简单的想法，就是枚举一个左端点看它最右能拓展到哪里，然后更新答案。

这中间的答案肯定得用某种数据结构维护啦！我们要维护的是尽可能多的节省时间，所以是 $t_i$ 和 $\lceil\frac{t_i}{2}\rceil$ 差距大的优先进行打折。  
可以用两个 `set`，先插进打折的里面，如果打折的满了再插到不打折的里面，同时更新记录的答案。注意从打折的里删除的是差距最小的，而从不打折里删除的是差距最大的。

具体实现的时候可以自己封装一个结构体，然后写主程序研究十分愉快了！

一些细节看代码。

```cpp
#include <cstdio>
#include <utility>
#include <algorithm>
#include <set>
#define int long long
typedef std::pair<int, int> P;
const int N = 200005;
int n, w, k, a[N], t[N], ans;
struct twt {
	std::multiset<P> sin, sout;
	int V, W;
	void fix() {
		if (sin.size() < w && sout.empty() || sin.size() == w) return;
		if (sin.size() > w) {
			P e = *sin.begin();
			sin.erase(sin.begin());
			W += e.first;
			sout.insert(e);
		}
		else {
			P e = *(--sout.end());
			sout.erase(--sout.end());
			W -= e.first;
			sin.insert(e);
		}
	}
	void insert(int i) {
		sin.insert(std::make_pair(t[i] - (t[i]+1)/2, i));
		W += (t[i]+1) / 2, V += a[i];
		fix();
	}
	void erase(int i) {
		P now = std::make_pair(t[i] - (t[i]+1)/2, i);
		V -= a[i];
		std::multiset<P>::iterator it = sin.lower_bound(now), 
							       it2 = sout.lower_bound(now);
		if (*it == now) sin.erase(it), W -= (t[i]+1)/2;
		else sout.erase(it2), W -= t[i]; 
		fix();
	}
	int getw() { return W; }
	int getv() { return V; }
	bool find(int i) {
		P now = std::make_pair(t[i] - (t[i]+1)/2, i);
		return (sin.find(now) != sin.end() || sout.find(now) != sout.end());
	}
} s;
signed main() {
	scanf("%lld%lld%lld", &n, &w, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%lld", &t[i]);
	for (int i = 1, j = 1; i <= n; i++) {
		for ( ; j <= n; j++) {
			s.insert(j);
			if (s.getw() > k) { 
				s.erase(j); break; 
			}
		}
		ans = std::max(ans, s.getv());
		if (s.find(i)) s.erase(i);
	}
	printf("%lld", ans);
	return 0;
}

```

---

## 作者：ChengJY_ (赞：1)

无内鬼，来点主席树做法。

~~其实是因为不会 stl。~~

### Solution

看这个连续区间加上，区间长度不限制，还有 $t$ 的单调性，考虑双指针。 

那么复杂度瓶颈就在如何快速计算区间中前 $w$ 大的数的时间的一半。

区间前 $k$ 大，考虑主席树。

其实就是经典区间第 $k$ 大的变种，实现起来并不是特别困难。

时间复杂度 $O(n\log n)$ 。

### Code

```cpp
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define N 500005
using namespace std;

int read(){
    int x=0,w=1;
    char ch=getchar();
    while(ch>'9'||ch<'0') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*w;
}

int n,w,k,tot,ans;
int root[N],t[N],sum[N],sum1[N],a[N];
struct node{int l,r,sum,val;}tree[N<<5];

void update(int &p,int l,int r,int x){
	tot++;
	tree[tot]=tree[p];tree[tot].sum++;tree[tot].val+=x/2;
	p=tot;
	int mid=(l+r)>>1;
	if(l<r){
		if(x<=mid) update(tree[p].l,l,mid,x);
		else update(tree[p].r,mid+1,r,x);
	}
}
int query(int t1,int t2,int l,int r,int k){
	if(l>=r) return l/2*(tree[t1].sum-tree[t2].sum-k+1);
	int x=tree[tree[t1].l].sum-tree[tree[t2].l].sum;
	int y=tree[t1].val-tree[t2].val-(tree[tree[t1].l].val-tree[tree[t2].l].val);
	int mid=(l+r)>>1;
	if(x>=k) return query(tree[t1].l,tree[t2].l,l,mid,k)+y;
	else return query(tree[t1].r,tree[t2].r,mid+1,r,k-x);
}

signed main(){
	n=read();w=read();k=read();
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
	for(int i=1;i<=n;++i){
		t[i]=read();
		root[i]=root[i-1];
		update(root[i],1,10000,t[i]);
	}
	for(int i=1;i<=n;++i) sum1[i]=sum1[i-1]+t[i];
	int r=0;
	for(int l=1;l<=n;++l){
		while(r<n&&sum1[r+1]-sum1[l-1]-query(root[r+1],root[l-1],1,10000,r+3-l-min(w,r+2-l))<=k) r++;
		ans=max(ans,sum[r]-sum[l-1]);
	}
	printf("%d\n",ans);
	return 0;
}
```

因为一一些细节调了很久，可读性并不是很好，感性理解一下。

---

## 作者：Loser_King (赞：1)

好的思维题。

难度：$\color{purple}\texttt{省选/NOI-}$

## 题意

有一个长度为 $n$ 的序列，序列中每个结点都有两个信息：$a_i$ 和 $t_i$。

在其中选择一段连续的序列，满足：

1. 其中最多有 $w$ 个结点的 $t_i$ 可以变为原来的一半（上取整）。
2. 经过1.的操作以后，这段结点的 $t_i$ 的和小于等于 $k$。

然后对于每个满足条件的段，求其 $a_i$ 之和的最大值。

## 做法

一看数据范围：$1\le n\le 2\times 10^5$，还要枚举序列，而且子序列越长答案越大，于是使用类似双指针的方法枚举序列，时间复杂度是 $O(n)$ 的。

对于每一段序列，如果结点可以使用减半的话一定使用，而且一定对序列中 $t_i$ 最大的结点使用减半。

所以需要维护当前段的最大 $t_i$ 的 $w$ 个节点。

使用 `stl multiset` 维护的话，每次插入，删除，查找最大最小值的时间复杂度是 $O(\log\;n)$ 的。

这样就可以在	$O(n\;\log\;n)$ 的时间复杂度内解决本题。

具体实现见代码。

## 代码实现
```c++
//CF746F AC Code
//written by Loser_King(159686)
//1.80s / 7.93MB / 998B C++ O2
#include<bits/stdc++.h>
using namespace std;
int const N=233333;
int n,w,k,sum,cur,ans,a[N],t[N];
//sum为当前序列ti和，cur为当前序列ai和
multiset<int>s1,s2;
//s1存储减半的ti，s2存储
int main(){
	ios::sync_with_stdio(0);
	cin>>n>>w>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>t[i];
	int l=1,r=0;
	//双指针枚举序列：l表示序列左端点，r表示序列右端点
	while(r<n){
		while(r<n){
			r++;
			int s1b=*s1.begin();
			if(s1.size()<w&&sum+(t[r]+1)/2<=k)s1.insert(t[r]),sum+=(t[r]+1)/2;
			//减半的数不足ti个，t[r]直接减半
			//注意除以2上取整
			else if(t[r]>s1b&&sum+s1b-(s1b+1)/2+(t[r]+1)/2<=k){
			//减半的数已满ti个，且t[r]比s1中最小的ti大
			//将t[r]减半，将s1中最小的不减半
				s2.insert(s1b),s1.erase(s1.find(s1b)),s1.insert(t[r]);
				//注意multiset去除一个数要用s.erase(s.find(x))
				//直接s.erase(x)会去除所有的x
				sum+=s1b-(s1b+1)/2+(t[r]+1)/2;
			}else if(sum+t[r]<=k)s2.insert(t[r]),sum+=t[r];
			//否则不减半t[r]
			else{r--;break;} 
			//如果t[r]不满足上述三种情况，右移左端点以减小sum
			ans=max(ans,cur+=a[r]);
			//更新答案
		}
		//右端点移动如上
		if(!s1.size()){r++;continue;}
		//当前序列为空，前移右端点以增加cur
		else if(!s2.size())s1.erase(s1.find(t[l])),sum-=(t[l]+1)/2;
		//s2为空，t[l]在s1内，直接在s1内删除
		else if(t[l]<*s1.begin())s2.erase(s2.find(t[l])),sum-=t[l];
		//t[l]在s2内，直接在s2里删除
		else{
			//t[l]在s1内，且s2非空
			//在s1中删除t[l]且把s2中最大的补到s1中
			int tmp=*s2.rbegin();
			s1.erase(s1.find(t[l])),s1.insert(tmp),s2.erase(s2.find(tmp));
			sum-=(t[l]+1)/2-(tmp+1)/2+tmp;
		}
		cur-=a[l++];
		//左端点移动如上
	}
	cout<<ans<<endl;
}
```

---

## 作者：_Anchor (赞：0)

# 前言

提供一个线段树+双指针的 $O(n\log n)$ 做法。 

# 题目大意

给定一个长度为 $n$ 的序列，每个位置有 $a_i,t_i$
  两个值，可以使至多 $w$ 个位置的 $t_i$
  变为 $ \lceil\frac {t_i}2\rceil$

选择一个区间，使得区间内 $\sum t_i\le k$ 的前提下，求 $\sum a_i$ 的最大值。

# 分析

首先不难观察到这个区间肯定是选的数越多越好，那么我们可以考虑对于每一个点作为左端点，求出其最长可以延伸到的右端点，之后直接前缀和询问即可。

显然选的数越多（右端点越往后）就越不容易满足条件的限制，那么这里的每一个左端点能取到的最右端点就具有单调性。

于是可以考虑双指针来维护这个不断更新右端点的过程。

现在考虑如何判断当前是否合法，大多数人都是用的 multiset 或者 priority_queue 来判断，这里采用不用动脑子的线段树。

对于当前的序列（即当前的左右端点构成的序列）维护一个值域线段树，记录区间 $sum$ 和区间 $siz$ 。（$sum$ 指的是如果我们把这个至于范围内的所有值折半，可以节省下来的代价之和。） 

那么插入和一般线段树一样，注意更新即可。

查询就是尽可能地往大的值域区间取（贪心的想，折半越大的数一定是不劣的），那么采用线段树上二分来判断，具体可以见代码。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
const int N=2e5+5,INF=1e9+7,M=1e5;
int n,w,k,sum[N<<2],siz[N<<2],a[N],t[N],Sum;
void Modify(int x,int l,int r,int pos,int v){
	if(l>r||!pos) return ;
	if(l==r) return sum[x]+=(l-(int)ceil(1.0*l/2))*v,siz[x]+=v,void();//注意sum的含义 
	int mid=l+r>>1;
	if(pos<=mid) Modify(x<<1,l,mid,pos,v);
	else Modify(x<<1|1,mid+1,r,pos,v);
	sum[x]=sum[x<<1]+sum[x<<1|1];
	siz[x]=siz[x<<1]+siz[x<<1|1];
	return ;
}
int Query(int x,int l,int r,int k){//线段树上二分 
	if(k<=0) return 0;
	if(k>=siz[x]) return sum[x];
	if(l==r) return sum[x]/siz[x]*min(k,siz[x]);
	int mid=l+r>>1,ls=siz[x<<1],rs=siz[x<<1|1];
	if(k<=rs) return Query(x<<1|1,mid+1,r,k);//如果右边的数可以取完w个就尽可能往大的取 
	return Query(x<<1,l,mid,k-rs)+sum[x<<1|1];
}
int pre[N],Ans;
signed main(){
	read(n),read(w),read(k);
	for(int i=1;i<=n;i++) read(a[i]),pre[i]=pre[i-1]+a[i];
	for(int i=1;i<=n;i++) read(t[i]);
	int j=1;Modify(1,1,M,t[1],1);Sum=t[1];
	for(int i=1;i<=n;i++){
		while(j<=n&&Sum-Query(1,1,M,w)<=k){j++;Modify(1,1,M,t[j],1);Sum+=t[j];}//右端点更新 
		Modify(1,1,M,t[j],-1),Modify(1,1,M,t[i],-1);//因为此时j会多增加1，所以需要减掉，而i则是因为左端点要右移 
		Sum-=t[i]+t[j];j--;//同上 
		Ans=max(Ans,pre[j]-pre[i-1]);
	}
	write(Ans);
	return 0;
}
```

---

## 作者：洛璟 (赞：0)

## Solotion：

注意到答案必须是一整个区间，所以可以考虑双指针来确定区间的两端点。

那么对于一个区间，我们应该如何选择？显然我们要让那些时间最长的音乐来作为只听一半的那些，这样可以在尽量短的时间内听最多的歌。

与此同时，我们会想到用堆来维护一个区间内半时间以及全时间的歌曲，为了随时保证这个区间的时间是最少的，因此，对于半时间的堆，我们必须时刻让这个区间内用时最大的 $w$ 首歌曲放入半时间的堆中，而剩下的歌曲放入全时间的堆，因此当右指针扫到一个新的歌曲时，我们就应该判断它是否比半价堆中最短的歌曲长，若是，则顶替那首歌曲，若不是，则顶入全时间的堆。

而一旦现在的区间时间总和超过了规定，那么左端点~~机枪~~向右移动~~五厘米~~，删除当前这个点后再将全时间堆中找出一个最长时间的扔到半时间堆中，不断重复即可。

tips：每一次加入完都应该判断是否超过规定时间，并处理完毕后再更新答案。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, w, k, sum, ans, laans;
struct cccp
{
    int s, t;
}a[200010];
multiset<pair<int, int> > s, m;//使用mutiset来维护
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int main()
{
    n = read();
    w = read();
    k = read();
    for (int i = 1;i <= n;++i)
    {
        a[i].s = read();
    }
    for (int i = 1;i <= n;++i)
    {
        a[i].t = read();
    }
    int l = 1, r = 1;
    while (r <= n)
    {
        if (s.size() < w)//判断半时间堆未满
        {
            s.insert(make_pair((a[r].t + 1) / 2, r));
            sum += (a[r].t + 1) / 2;
            ans += a[r].s;
        }
        else
        {
            pair<int, int> qwq = *s.begin();
            if (a[qwq.second].t < a[r].t)//把新的长时间歌曲仍入半时间堆
            {
                s.erase(s.begin());
                sum -= qwq.first;
                m.insert(make_pair(a[qwq.second].t, qwq.second));
                sum += a[qwq.second].t;
                s.insert(make_pair((a[r].t + 1) / 2, r));
                sum += (a[r].t + 1) / 2;
                ans += a[r].s;
            }
            else//否则扔入全时间堆
            {
                m.insert(make_pair(a[r].t, r));
                sum += a[r].t;
                ans += a[r].s;
            }
        }
        ++r;
        while (sum > k)//超限了
        {
            pair<int, int> qaq = *s.begin();
            if (s.find(make_pair((a[l].t + 1) / 2, l)) != s.end())//在左端点所指的数半时间堆中
            {
                s.erase(s.find(make_pair((a[l].t + 1) / 2, l)));
                sum -= (a[l].t + 1) / 2;
                ans -= a[l].s;
                if (!m.empty())
                {
                    pair<int, int> nmsl = *--m.end();
                    m.erase(--m.end());
                    sum -= nmsl.first;
                    nmsl.first = (nmsl.first + 1) / 2;
                    s.insert(nmsl);
                    sum += nmsl.first;
                }

            }
            else
            {
                m.erase(m.find(make_pair(a[l].t, l)));
                sum -= a[l].t;
                ans -= a[l].s;
            }
            ++l;
        }
        laans = max(laans, ans);
    }
    if (sum <= k)
    {
        laans = max(laans, ans);
    }
    printf("%d", laans);
    return 0;
}
```

---

