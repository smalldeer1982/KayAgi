# Omkar and Time Travel

## 题目描述

El Psy Kongroo.

Omkar is watching Steins;Gate.

In Steins;Gate, Okabe Rintarou needs to complete $ n $ tasks ( $ 1 \leq n \leq 2 \cdot 10^5 $ ). Unfortunately, he doesn't know when he needs to complete the tasks.

Initially, the time is $ 0 $ . Time travel will now happen according to the following rules:

- For each $ k = 1, 2, \ldots, n $ , Okabe will realize at time $ b_k $ that he was supposed to complete the $ k $ -th task at time $ a_k $ ( $ a_k < b_k $ ).
- When he realizes this, if $ k $ -th task was already completed at time $ a_k $ , Okabe keeps the usual flow of time. Otherwise, he time travels to time $ a_k $ then immediately completes the task.
- If Okabe time travels to time $ a_k $ , all tasks completed after this time will become incomplete again. That is, for every $ j $ , if $ a_j>a_k $ , the $ j $ -th task will become incomplete, if it was complete (if it was incomplete, nothing will change).
- Okabe has bad memory, so he can time travel to time $ a_k $ only immediately after getting to time $ b_k $ and learning that he was supposed to complete the $ k $ -th task at time $ a_k $ . That is, even if Okabe already had to perform $ k $ -th task before, he wouldn't remember it before stumbling on the info about this task at time $ b_k $ again.

Please refer to the notes for an example of time travelling.

There is a certain set $ s $ of tasks such that the first moment that all of the tasks in $ s $ are simultaneously completed (regardless of whether any other tasks are currently completed), a funny scene will take place. Omkar loves this scene and wants to know how many times Okabe will time travel before this scene takes place. Find this number modulo $ 10^9 + 7 $ . It can be proven that eventually all $ n $ tasks will be completed and so the answer always exists.

## 说明/提示

For the first sample, all tasks need to be completed in order for the funny scene to occur.

Initially, the time is $ 0 $ . Nothing happens until time $ 3 $ , when Okabe realizes that he should have done the $ 2 $ -nd task at time $ 2 $ . He then time travels to time $ 2 $ and completes the task.

As the task is done now, he does not time travel again when the time is again $ 3 $ . However, at time $ 4 $ , he travels to time $ 1 $ to complete the $ 1 $ -st task.

This undoes the $ 2 $ -nd task. This means that the $ 2 $ -nd task is not currently completed, meaning that the funny scene will not occur at this point even though the $ 1 $ -st task is currently completed and Okabe had previously completed the $ 2 $ -nd task.

Once it is again time $ 3 $ he travels back to time $ 2 $ once more and does the $ 2 $ -nd task again.

Now all tasks are complete, with Okabe having time travelled $ 3 $ times.

The second sample has the same tasks for Okabe to complete. However, this time the funny scene only needs the first task to be completed in order to occur. From reading the above sample you can see that this occurs once Okabe has time travelled $ 2 $ times.

## 样例 #1

### 输入

```
2
1 4
2 3
2
1 2```

### 输出

```
3```

## 样例 #2

### 输入

```
2
1 4
2 3
1
1```

### 输出

```
2```

## 样例 #3

### 输入

```
1
1 2
1
1```

### 输出

```
1```

## 样例 #4

### 输入

```
6
10 12
3 7
4 6
2 9
5 8
1 11
3
2 4 6```

### 输出

```
17```

## 样例 #5

### 输入

```
16
31 32
3 26
17 19
4 24
1 28
15 21
12 16
18 29
20 23
7 8
11 14
9 22
6 30
5 10
25 27
2 13
6
3 8 2 5 12 11```

### 输出

```
138```

# 题解

## 作者：MoonPie (赞：9)


**形式化题意**

在x轴上有 $n$ 个传送门，第 $i$ 个传送门用左右端点 $l_i,r_i$ 表示。每个传送门的右端点有一个开关，一开始都处于**开**的状态。你从原点出发，每次可以往右走一格。当你走到了 $r_i$ 且开关处于开的状态，你就会被送到 $l_i$，并关闭开关。同时，所有 $l_j > l_i$ 的传送门的开关都被打开。

当你打开了给定集合 $S$ 的传送门的所有开关时，游戏结束。请输出此时你被传送了多少次。答案对 $10^9+7$ 取模。
$$
1\le n \le2\cdot 10^5,1\le l_i< r_i\le 2n
$$
$l_i,r_i$ 互不相同。

---

可以发现，开关被打开的顺序为按照右端点从小到大的来的。所以被一个传送门 $i$ 作用的传送门，就是被其包含的线段，设为集合 $T_i$。

设 $f_i$ 表示在第 $i$ 个传送门的开关处于开的状态来到 $r_i$ 被传送回去，再走回 $r_i$ 的传送次数。
$$
f_i = 1+\sum_{j\in T_i}f_j
$$
可以用树状数组维护计算。然后就是这道题的难点：如何利用计算出来的 $f_i$ 计算出答案。

通过手模第二个样例，我们可以发现 $f_i$ 的第二层含义：从 $l_i$ 费尽千辛万苦来到 $r_i$，再被传送回去的被传送次数。

考虑 $S$ 集合中右端点在最右边的传送门 $mr$，是一定会从 $l_{mr}$ 走到 $r_{mr}$ 然后传送回去的，因为只有这样才能打开 $mr$ 的开关。然后考虑走了这个 $mr$ 还有哪些新的传送门是必须走的：因为是要从 $l_{mr}$  出发的，所以左端点在 $l_{mr}$ 左边的传送门就变成了必须走的，即 $l_k < l_{mr} \wedge r_k < r_{mr}$ 变成了必须走的。然后转化成了一个子问题。还是用树状数组维护。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5, mod = 1e9+7;
template<class T> void Plus(T &x, T y) {x = x + y >= mod ? x + y - mod : x + y; }

int n,m;
struct door {
	int l,r;
	bool operator<(const door &o) const {
		return r < o.r;
	}
}d[N],s[N];

struct fenwick {
	int tr[N<<1];
	void Add(int x,int w) {
		for (; x; x -= x&-x) Plus(tr[x], w);
	}
	int Query(int x) {
		int res = 0;
		for (; x <= n*2; x += x&-x) Plus(res, tr[x]);
		return res;
	}
}T1,T2;
int dp[N];

int main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> d[i].l >> d[i].r;
	cin >> m;
	for (int i = 1, x; i <= m; ++i) cin >> x, s[i] = d[x];

	sort(d+1,d+n+1);
	for (int i = 1; i <= n; ++i) 
	{
		dp[i] = T1.Query(d[i].l) + 1;
		T1.Add(d[i].l, dp[i]);
	}

	sort(s+1,s+m+1);
	int ans = 0;
	for (int i = n, j = m; i >= 1; --i)
	{
		for (; j >= 1 && s[j].r >= d[i].r; --j) T2.Add(s[j].l, 1);
		if (T2.Query(d[i].l)) Plus(ans, dp[i]), T2.Add(s[i].l, 1);
	}
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：Alex_Wei (赞：6)

- Update on 2023.1.31 重写题解，原题解见 [剪贴板](https://www.luogu.com.cn/paste/zhn830ym)。

> [CF1583G Omkar and Time Travel](https://www.luogu.com.cn/problem/CF1583G)

好题，很抽象。

首先，让我们明确一点：从 $a_i$ 到 $b_i$ 再被传送回来的传送次数仅与右端点落在 $(a_i, b_i)$ 上的所有区间当前的状态相关，而与其它区间的状态无关。

我们称一个区间被彻底点亮当且仅当它此后不会再熄灭，因为点亮 $i$ 时会将所有 $a_j > a_i$ 的 $j$ 熄灭，所以区间按左端点递增的顺序被彻底点亮。将所有区间按 $a_i$ 递增排序。

进一步地，$i$ 被彻底点亮时，$i + 1$ 后均熄灭，且 $i$ 前均被彻底点亮。这启发我们设 $f_i$ 表示当前在位置 $a_i$，$i$ 熄灭，不会被传送到 $a_i$ 左侧，且左端点在 $a_i$ 右边的区间全部熄灭（相当于原问题的子结构）时，点亮 $i$ 的传送次数。

因为所有右端点在 $(a_i, b_i)$ 上的区间必须点亮，而在这些区间（而不是所有区间）中左端点在 $a_i$ 左边的区间已经点亮（否则就会被传送到 $a_i$ 左侧），所以相当于将所有完全包含于 $i$ 的区间从熄灭变成点亮。

我们发现，对于一个完全包含于 $i$ 的区间，它在这个子问题中被彻底点亮的传送次数，等于它在原问题中被彻底点亮的传送次数。因为在这两个问题中，所有可能影响到传送次数的区间（即一开始所明确的右端点落在该区间上）的状态完全相同。换言之，**$i$ 是否点亮不影响包含于 $i$ 的区间的传送次数**。

又因 $a_i$ 递增，故有
$$
f_i = 1 + \sum_{i < j \land b_j < b_i} f_j
$$
按 $i$ 从大到小的顺序 DP，用树状数组维护。

接下来考虑统计答案。如果 $i$ 被点亮，则 $j < i$ 且 $b_j < b_i$ 的 $j$ 也一定被点亮，但其它区间可以不被点亮，所以答案即被集合内任意区间二维偏序的所有区间（存在 $i\in S$ 使得 $j < i\land b_j < b_i$ 的 $j$）的 $f$ 之和。同样使用树状数组维护。

时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/1583/submission/191336378)。

---

## 作者：FZzzz (赞：3)

暑假的时候就有个初中同学把石头门给补了然后一直在吹，我寻思我要不要抽个空也把这玩意补了。

一个显然的事实是：每个不同的“已完成任务集合”只会出现一次。因为，你完成一个集合里的任务之后处于的时间点是确定的，那么如果你完成了同一个集合超过一次，你就永远走不出去了。

这个事实的一个直接推论是：所有可能出现的集合（下简称“合法集合”）之间存在一个偏序关系。每次集合发生变化会发生一次跃迁，那么只需要找到第一个包含目标集合（不一定是一个合法集合）的合法集合前面有多少个合法集合即可。

考虑什么样的集合是合法的。如果两个任务 $i$ 和 $j$ 满足 $a_i<a_j$ 且 $b_i<b_j$，并且一个合法集合包含 $j$，那么它一定也包含 $i$。因为，我完成 $i$ 的时候会把 $j$ 给撤销掉，并且如果我在哪一次跃迁把 $i$ 给撤销了，那 $j$ 一定也被撤销了。

称满足这个条件的集合为“准合法集合”。我们将要证明，准合法集合与合法集合是同一个东西。

首先我们定义一个准合法集合的“标准表示”：只保留这样的任务 $i$，使得集合中不存在 $a$ 和 $b$ 都比 $i$ 大的任务。由于这是一个偏序关系，我们显然可以得到，每个集合的标准表示都不相同。又，如果我们用区间 $[a_i,b_i]$ 表示任务 $i$，一个标准表示是若干个嵌套包含的区间，并且每个这样的集合都是某个准合法集合的标准表示。

我们考虑如何用两个标准表示确定对应的两个准合法集合之间的偏序关系。我们找出两个标准表示中最大的两个区间，若他们不相同，则其中 $b$ 大的一个在后面。因为，如果我要撤销掉这个 $b$ 大一点的任务，我必须要完成一个 $a$ 比它小的任务，那么这个任务必然在另一个准合法集合中。

同样，若这两个区间相同，我们可以取出两个标准表示中次大的区间再进行比较，这样一直继续下去。特别地，如果一个标准表示是另一个的子集，那么这个子集在它前面。如果我们把标准表示中所有区间的 $b$ 从大到小写下来，那么即是比较这两个串的字典序。

回到“准合法集合等价于合法集合”的证明。我们已经知道了前者包含后者，那么我们也可以写出任意合法集合的标准表示。考虑一个合法集合被完成后，我们所在的时间点是其最大的一个 $a$——也即是标准表示中最大的 $a$。

这个合法集合的下一个集合即是从这个时间一直走，走到第一个不在当前合法集合中的 $b$，然后完成这个任务。容易发现，这个集合的标准表示也是当前集合的标准表示的下一个标准表示，具体证明留给读者。这也就是说，对于一个合法集合，其下一个合法集合也是下一个准合法集合。这样，我们就证明了准合法集合等价于合法集合。

仿照将一个合法集合写成标准表示的方法，去掉目标集合中的可以被其他任务导出的任务，得到一个标准表示，容易证明这个标准表示对应的合法集合即是第一个包含目标集合的合法集合。那么现在问题容易地多：我们只需要计算这个标准表示前面有多少个标准表示即可。

考虑从左往右扫，扫到一个 $b$ 时若这个区间在目标标准表示中，我们考虑若它是某个比目标标准表示小的标准表示与目标标准表示的 lcp 的下一个区间，那么前者的这个位置的区间必然 $b$ 比当前区间小，并且 $a$ 比 lcp 的最后一个区间即当前区间在目标标准表示中的上一个区间要大。

那么我们扫到一个 $b$ 时在 $a$ 处将有多少个以这个区间开头的标准表示——这可以通过类似的方法用数据结构优化 dp 求出——加入到数据结构内。在扫到目标标准表示的某个区间的 $b$ 时，我们只需要在这个数据结构内查询后缀和即可。容易发现，这样我们不会统计目标标准表示本身，但统计了本不应该被统计的空集，因此得出的答案是正确的。

至此，问题在 $O(n\log n)$ 时间内得到完整解决。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll readint(){
	ll x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-'){
		f=1;
		c=getchar();
	}
	while(isdigit(c)){
		x=x*10+c-'0';
		c=getchar();
	}
	return f?-x:x;
}
const int maxn=2e5+5;
int n,a[maxn*2],b[maxn],t;
bool v[maxn*2];
int lst[maxn*2];
const ll mod=1e9+7;
inline int lowbit(int x){
	return x&-x;
}
ll c[maxn*2];
void modify(int x,ll k){
	while(x){
		c[x]=(c[x]+k)%mod;
		x-=lowbit(x);
	}
}
ll query(int x){
	ll s=0;
	while(x<=n*2){
		s=(s+c[x])%mod;
		x+=lowbit(x);
	}
	return s;
}
ll f[maxn*2];
int main(){
	#ifdef LOCAL
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	#endif
	n=readint();
	for(int i=1;i<=n;i++){
		int x=readint();
		b[i]=readint();
		a[b[i]]=x;
	}
	t=readint();
	for(int i=1;i<=t;i++) v[b[readint()]]=1;
	int l=0;
	for(int i=n*2;i>0;i--) if(v[i]){
		if(a[i]<l) v[i]=0;
		else{
			lst[i]=l;
			l=a[i];
		}
	}
	for(int i=1;i<=n*2;i++) if(a[i]){
		f[i]=(query(a[i])+1)%mod;
		modify(a[i],f[i]);
	}
	ll ans=0;
	memset(c,0,sizeof(c));
	for(int i=1;i<=n*2;i++) if(a[i]){
		if(v[i]) ans=(ans+query(lst[i]+1)+1)%mod;
		modify(a[i],f[i]);
	}
	printf("%lld\n",ans);
	#ifdef LOCAL
	fprintf(stderr,"%d\n",(int)clock());
	#endif
	return 0;
}
```

---

## 作者：lytqwq (赞：2)

考虑现在在 $b_i$ 时刻意识到任务 $i$，准备回 $a_i$ 时刻，这时所有在 $b_i$ 时刻之前意识到的任务都已经完成，所有在 $b_i$ 时刻之后意识到的任务都未完成。

回到 $a_i$ 时刻后，所有满足 $a_j>a_i\land b_j<b_i$ 的 $j$ 都被重置，而且所有这些 $j$ 本来都应该是被完成过的。所以，在 _最后意识到的集合中的任务_  后面意识到的任务不会被完成，我们直接去掉就完了。

设 $f_i$ 表示完成任务 $i$ 的次数，那么，每次这样的重置都会使 $a_j>a_i \land b_j<b_i$ 的 $f_j$ 增加。

考虑按 $a_i$ 从小到大排序，$a_1$ 一定不会作为被增加完成次数的任务，所以 $f_1=1$，而它还可能增加其他的 $f$，这时只需要满足 $b_j<b_i$ 就行了，因为我们已经按 $a_i$ 从小到大排序了，用树状数组就完了，时间复杂度 $O(n \log n)$。

注意完成最后一个集合任务之后，不需要再把重置的任务补上了。

代码可能更清晰一点。

```cpp

#include<bits/stdc++.h>
#define ll long long
#define PI pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define ui unsigned int
#define pb push_back
using namespace std;
const int N=400010,mod=1e9+7;
int T,n,q;
int a[N],b[N],c[N],res[N];
int isa[N];
bool cmp(int x,int y){
	return b[x]<b[y];
}
int d[N];
int lowbit(int x){
	return x&(-x);
}
void update(int x,int y){
	for(int i=x;i>=1;i-=lowbit(i)){
		d[i]=(d[i]+y)%mod;
	}
}
int query(int x){
	int sum=0;
	for(int i=x;i<=2*n;i+=lowbit(i)){
		sum=(sum+d[i])%mod;
	}
	return sum;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		isa[a[i]]=i;
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d",&c[i]);
	}
	b[0]=1e9;
	sort(c+1,c+q+1,cmp);
	int ok=q;
	ll sum=0;
	for(int i=1;i<=2*n;i++){
		if(isa[i]&&b[isa[i]]<=b[c[ok]]){
			res[isa[i]]=query(b[isa[i]])+(ok!=0);
			sum+=res[isa[i]];
			while(ok!=0&&a[c[ok]]<=i){
				ok--;
			}
			update(b[isa[i]],res[isa[i]]);
		}
		else if(isa[i]){
			res[isa[i]]=query(b[isa[i]]);
			sum+=res[isa[i]];
			update(b[isa[i]],res[isa[i]]);
		}
	}
	printf("%lld\n",sum%mod);
	return 0;
}
```



---

## 作者：Illusory_dimes (赞：1)

[不知道更好还更坏的阅读体验](https://www.cnblogs.com/Illusory-dimes/p/15888591.html)

## Description

有 $n$ 个传送点，每个传送点有一个入口 $a_i$ 和一个出口 $b_i$ （ $a_i > b_i$ ），初始时全部没做标记，并且只有没有标记的传送点会传送，每次传送之后标记该传送点，同时取消所有 $b_j > b_i$ 的 $j$ 的传送点的标记。

现在给定 $m$ 个编号，问这下编号的传送点全部被标记时，最小的传送次数。

## Solution

能明显感觉到有些区间是能够反复影响一些另外的区间的，来分类讨论一下：

1. 两个区间没有交集

- 那显然走到前面一个传送点的时候和后者完全没有关系，所以互不影响

2. 两个区间有交集但是不互相包含

- 同上的情况，因为我们只有走过 $a$ 才能跑到 $b$ ，所以即便是有交也不影响。

3. 包含

- 这样的话我们会先走到小区间，然后传送完之后走到大区间，这样会取消小区间的标记，然后再走一次小区间才能走出去。

------------

同时这也证明我们必能在有限时间内走出这个鬼地方。

现在发现我们只是讨论了两个区间的请款，多个的话肯定会复杂的要死，所以干脆我们设一个 $f_i$ 表示从 $i$ 从 $b_i$ 到能完全走出 $a_i$ 需要的传送次数。

那么也就是说所有 $i$ 包含的区间全部要这样来一遍，因为考虑到如果设 $b_i$ 到走出 $a_i$ 的话包含了第一次到达 $a_i$ 前的那些小区间走的次数，会计重，所以改一下定义：

$f_i$ 表示从 $a_i$ 传送回去到能完全走出 $a_i$ 需要的传送次数。

这样我们可以理解为走完一个大区间分为两步：

1. 把所有包含的小区间标记完要的次数。

2. 在 $i$ 传送之后再把包含的小区间重新再走一遍。

所以明显能推出这样的一个小式子（其中 $S_i$ 表示 $i$ 包含的区间集合）：

$$f_i = 1 + \sum_{j \in S_i} f_j$$

可以树状数组维护，把所有区间按照 $b_i$ 从小到大排序，从前往后扫，每次就把 $f_i$ 挂在 $a_i$ 上，然后查找所有 $a_j$ 比它大的区间。

因为前面已经挂了贡献的区间 $b_j$ 必定必 $b_i$ 小，树状数组查找只找 $a_j$ 比 $a_i$ 大的区间，那就是所有包含 $i$ 的区间，所以这样就类似二维偏序的完成了对 $f_i$ 的统计。

------------

然后是统计答案：

1. 我们发现一个要标记的区间 $i$ 前面所有区间（有交也算）必然要全部标记。

2. 自己包含的区间虽然有贡献但是如果算上自己被标记的传送次数 $1$ 的话，其实就是 $f_i$ 。

3. 但是注意到包含自己的区间没有贡献，完全不需要参与进来。

所以总结一下，就是一个区间要贡献的话，就相当于他要是在一个规定的区间前面（有交也算），或者自己要被标记。

所以这样的话同样树状数组挂标记能搞定。

时间复杂度 $O(n\log n)$ 。

（注：我的程序 $a$ 和 $b$ 是反过来的，并且我好像写的是按照 $b$ 排序，不过问题不大，都能做）

## Code

```cpp
/*

*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5 + 10, mod = 1e9 + 7;
int n, m, sig[N], f[N], ans;
struct mdzz {
	int a, b, id;
	bool operator < (const mdzz &it) const {
		return a < it.a;
	}
} l[N];
inline int read() {
	char ch = getchar();
	int s = 0, w = 1;
	while (!isdigit(ch)) {if (ch == '-') w = -1; ch = getchar();}
	while (isdigit(ch)) {s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar();}
	return s * w;
}
struct SGT {
	int c[N];
	inline int lowbit(int x) {return x & (-x);}
	inline void add(int x, int k) {
		for (; x <= (n << 1); x += lowbit(x)) (c[x] += k) %= mod;
	}
	inline int query(int x) {
		int tmp = 0;
		for (; x; x -= lowbit(x)) (tmp += c[x]) %= mod;
		return tmp;
	}
	inline int query(int x, int y) {
		return (query(y) - query(x) + mod) % mod;
	}
} feq, it;
int main() {
	n = read();
	for (int i = 1; i <= n; ++i) {
		l[i] = (mdzz) {read(), read(), i};
	}
	sort(l + 1, l + 1 + n);
	m = read();
	for (int i = 1; i <= m; ++i) sig[read()] = 1;
	for (int i = n; i; --i) {
		f[i] = (1 + feq.query(l[i].b)) % mod;
		feq.add(l[i].b, f[i]);
		it.add(l[i].b, sig[l[i].id]);
		if (it.query(l[i].b - 1, n << 1)) (ans += f[i]) %= mod;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

