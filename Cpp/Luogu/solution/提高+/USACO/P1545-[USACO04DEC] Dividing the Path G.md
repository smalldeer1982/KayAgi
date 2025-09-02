# [USACO04DEC] Dividing the Path G

## 题目描述

约翰的奶牛们发现山脊上的草特别美味。为了维持草的生长，约翰打算安装若干喷灌器。

为简化问题，山脊可以看成一维的数轴，长为 $L\ (1\le L\le 10^6)$，而且 $L$ 一定是一个偶数。每个喷灌器可以双向喷灌，并有确定的射程，该射程不短于 $A$，不长于 $B$，$A$，$B(1\le A\le B\le 10^3)$ 都是给出的正整数。它所在位置的两边射程内，都属它的灌溉区域。

现要求山脊的每一个区域都被灌溉到，而且喷灌器的灌溉区域不允许重叠。约翰有 $N(1\le N\le 10^3)$ 只奶牛，每一只都有特别喜爱的草区，第 $i$ 奶牛的草区是 $[S_i,E_i]$，不同奶牛的草区可以重叠。现要求，每只奶牛的草区仅被一个喷灌器灌溉。

注意：

1. 数轴 $L$ 从 $0$ 开始标记（即坐标范围 $0\sim L$）  
2. 喷灌器坐标和射程必须为整数，对于坐标为 $i$ 射程为 $x$ 的喷灌器，它的灌溉范围为 $[i-x,i+x]$。
3. 浇灌区间必须在山脊范围内。例如，不能在 $0$ 位置放一个半径为 $1$ 的浇灌器。

寻找最少需要的喷灌器数目。

## 说明/提示

对于 $100\%$ 的数据，$1\le L\le 10^6$，$1\le A,B\le 10^3$，$1\le N\le 10^3$，$1\le S_i<E_i\le L$。

样例解释：

![](https://vj.csgrandeur.cn/d4313c41a71f91cdadfcba2601cf5034?v=1699442455)

## 样例 #1

### 输入

```
2 8
1 2
6 7
3 6```

### 输出

```
3```

# 题解

## 作者：Svemit (赞：12)

[更好的阅读体验](https://www.cnblogs.com/Svemit/p/17453426.html)

丢一发好理解又好写的线段树优化 dp。

[题目传送门](https://www.luogu.com.cn/problem/P1545 "题目传送门")

### 简要题意
给定一个长为 $l$ 的线段，求出尽量少的不相交区间覆盖整段线段，要求题目给的所有子区间只被 $1$ 个区间覆盖。

### 分析
显然题目给的子区间 $[s, e]$ 中只有 $s$ 和 $e$ 端点能作为线段端点，所以我们应该给 $[s + 1, e - 1]$ 打上标记，这些不能作为线段端点。

令 $dp_i$ 为覆盖 $[0, i]$ 的最小的线段数量。

要求的就是 $\min (dp_j) + 1, j \in [i - a \times 2, i - b \times 2]$。

可以很轻易的写出一段暴力程序。
```cpp
dp[0] = 0;
for(int i = 2; i <= l; i += 2) {
	if(flag[i]) continue;
	for(int k = a; k <= b; k ++) {
		int j = i - k * 2; // 在i, j 中间放一个线段
		if(j < 0) break;
		dp[i] = min(dp[i], dp[j] + 1);
	}
}
```
发现该算法的瓶颈会在枚举 $k$ 的复杂度太高了，考虑优化掉。

区间最小值？线段树？

每次取出区间中的最小值算出 $dp_i$ 递推下去就行。

代码就变成了这样：

```cpp
	for(int i = a * 2; i <= l; i += 2) {
		if(flag[i]) continue;
		int ql = max(0, i - 2 * b), qr = i - 2 * a;
		dp[i] = query(ql, qr, 1) + 1;
		update(i, dp[i], 1);
	}
```
写一棵可爱的线段树就可以拉。

code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1e6 + 5, INF = 0x3f3f3f3f;
const LL mod = 1e9 + 7;
int n, l, a, b;
bool flag[N];
int c[N];
int dp[N];
struct segtree {
	int l, r, val;
	#define l(x) tr[x].l
	#define r(x) tr[x].r
	#define val(x) tr[x].val
} tr[N << 2];
void pushup(int x) {
	val(x) = min(val(x << 1), val(x << 1 | 1));
}
void build(int l, int r, int x) {
	l(x) = l, r(x) = r, val(x) = INF;
	if(l == r) return;
	int mid = l + r >> 1;
	build(l, mid, x << 1), build(mid + 1, r, x << 1 | 1);
}
void update(int pos, int v, int x) {
	if(l(x) == r(x)) {
		val(x) = v;
		return;
	}
	int mid = l(x) + r(x) >> 1;
	if(mid >= pos) update(pos, v, x << 1);
	else update(pos, v, x << 1 | 1);
	pushup(x);
}
int query(int l, int r, int x) {
	if(l <= l(x) && r(x) <= r) return val(x);
	int mid = l(x) + r(x) >> 1, res = INF;
	if(l <= mid) res = query(l, r, x << 1);
	if(r > mid) res = min(res ,query(l, r, x << 1 | 1));
	return res;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	cin >> n >> l >> a >> b;
	for(int i = 1; i <= n; i ++) {
		int x, y;
		cin >> x >> y;
		c[x + 1] ++, c[y] --;
	}
	for(int i = 1; i <= l; i ++) {
		c[i] += c[i - 1];
		if(c[i] > 0) flag[i] = true;
	}
	build(0, l, 1);
	update(0, 0, 1);
	for(int i = a * 2; i <= l; i += 2) {
		if(flag[i]) continue;
		int ql = max(0, i - 2 * b), qr = i - 2 * a;
		dp[i] = query(ql, qr, 1) + 1;
		update(i, dp[i], 1);
	}
	if(dp[l] >= INF) dp[l] = -1;
	cout << dp[l] << '\n';
    return 0;
}
```

upd: 将写错的 $[s + 1, e + 1]$ 改为 $[s + 1, e - 1]$，感谢 [Aslf_Ek](https://www.luogu.com.cn/user/175719) 指出错误。

upd: 在 [Alisya](https://www.luogu.com.cn/user/482007) 大佬的建议下将 $flag$ 数组的处理改为差分处理，复杂度更稳定。

---

## 作者：X____ (赞：8)

upd: 2024/08/18 修改题解中不通顺的地方以及滑动窗口代码中错误的部分。

## 题目描述

给定一个线段，要求用最少的子线段不重不漏覆盖该线段，并且要求题目中所给的区间仅被一条子线段覆盖，求符合要求的最少子线段数目。

## 解题

题目要求一个区间仅可以被一条子线段覆盖，说明该区间内除左右端点的任何地方不能作为子线段的端点。

所以一个位置能作为子线段的端点当且仅当该位置不被任何区间（该区间的左右端点除外）所包含。

定义 $f_i$ 为覆盖了从 $0$ 到 $i$ 的最小子线段数目。

易得 $f_i = \min(f_j + 1) (j \in [i-b \times 2, i - a \times 2])$。

得到如下暴力代码 :

```cpp
for(i = a*2; i <= l; i += 2) {
		if(flag[i]) continue; //该位置若不能作为子线段的端点就跳过 
		for(j = a; j <= b; j ++) {
			k = i - j*2;
			if(k < 0) continue;
			dp[i] = min(dp[i], dp[k]+1);
		}
	}
```

~~然后这题就水过了。~~

那么考虑如何优化，发现每次转移实质上是一个单点修改和一个区间查询最小值，可以使用线段树来维护。

代码如下。

```cpp
#include <bits/stdc++.h>
#define F(i, l, r) for(int (i) = (l); (i) <= (r); (i) ++)

using namespace std;
const int N = 1e6 + 5;
struct Tree{
	int l, r, sum;
}tr[N << 2];
int d[N], inf = 1e9;
void pushup(int c) {
	tr[c].sum = min(tr[c<<1].sum, tr[c<<1|1].sum);
}
void build(int c, int l, int r) {
	tr[c].l = l;
	tr[c].r = r;
	tr[c].sum = inf;
	if(l == r) return;
	int mid = l + r >> 1;
	build(c<<1, l, mid);
	build(c<<1|1, mid+1, r);
}
int query(int c, int l, int r) {
	if(tr[c].l >= l and tr[c].r <= r) return tr[c].sum;
	int mid = tr[c].l + tr[c].r >> 1;
	int res = inf;
	if(l <= mid) res = min(res, query(c<<1, l, r));
	if(r > mid) res = min(res, query(c<<1|1, l, r));
	return res;	
}
void update(int c, int p, int k) {
	if(tr[c].l == tr[c].r) return (void)(tr[c].sum = k);
	int mid = tr[c].l + tr[c].r >> 1;
	if(p <= mid) update(c<<1, p, k);
	else update(c<<1|1, p, k);
	pushup(c);
}
int f[N];
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, L, a, b;
	cin >> n >> L >> a >> b;
	F(i, 1, n) {
		int s, e;
		cin >> s >> e;
		//差分，将 s+1 到 e-1 的位置打上标记 
		d[s+1] ++;
		d[e] --;
	}
	F(i, 1, L) d[i] += d[i-1];
	build(1, 0, L);
	update(1, 0, 0);
	for(int i = a*2; i <= L; i += 2) {
		if(d[i]) continue;
		int ql = max(0, i-b*2), qr = i - a*2;
		f[i] = query(1, ql, qr) + 1;
		update(1, i, f[i]);
	}
	cout << (f[L] >= inf ? -1 : f[L])<< "\n";
	return 0;
}
```



当然也可以码量更少跑得更快滑动窗口来维护，代码如下。



```cpp
f[0] = 0;
for(int i = a*2; i <= L; i += 2) {
	while(!q.empty() and q.front() < i-b*2) q.pop_front();
	while(!q.empty() and f[i-a*2]<=f[q.back()]) q.pop_back();
	q.push_back(i-a*2);
	if(!d[i]) f[i] = f[q.front()] + 1;
}
```

---

## 作者：___nyLittleT___ (赞：7)

## 题意概括
给出奶牛数量，草坪长度，喷水的范围（分别对应 $n,l,a,b$），求出最少的不相交区间覆盖整段线段。

## 题目分析
本人蒟蒻一枚，看到此题就想到暴力。  
用我们教练的话来说：“暴力要有方法的暴力！”  
于是我就想到了 dp。

### 具体该怎样实现呢？
首先定义一个标记数组，  
暴力标记每只奶牛喜欢的草区。  
我们想一想，如果一个喷洒器位于 $x$，  
那么其能喷洒到的范围为 $[x-y,x+y]$（$y ∈ [a,b]$），  
而题目要求求到最小的喷洒器数量。  
即我们考虑 dp，  
用 $dp_x$ 表示位于 $x$ 位置之前总共需要的最少的喷洒器数量。

### 那么 $x$ 位置之前的范围又该怎么求呢？
我们固定 $j$ 为右端点，易求出此喷洒器可以喷洒到的范围为 $(x-j \times 2)$。

### 接下来就是 dp 的实现了
对于每个 $dp_x$ 而言，都可以由 $dp_j$ 转化而来，易得出本题状态转移方程：  
$$ dp_x = \min(dp_x,dp_j+1) $$  
这样整个题目我们就处理完了。  
最后……

###  $-1$ 的情况怎样判断
如果 $dp_l$ 的值大于一个极大值（我的代码里使用 $10^9$），  
那么就可以判断为无解，输出 $-1$。

## 最后附上AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,a,b,s,e,i,j,k;
int dp[1000005];// dp 数组 
bool flag[1000005];//标记数组 
int main(){
	memset(dp,0x3f,sizeof dp);
	scanf("%d %d %d %d",&n,&l,&a,&b);
	dp[0]=0;
	for(i=1;i<=n;i++){
		scanf("%d %d",&s,&e);
		for(j=s+1;j<=e-1;j++) flag[j]=1;//暴力标记 
	}
	for(i=2;i<=l;i+=2){//遍历偶数 
		if(flag[i]) continue;
		for(j=a;j<=b;j++){
			k=i-(j<<1);//以i为右端点，这个状态喷洒的范围 
			if(k<0) continue;//超出范围 
			dp[i]=min(dp[i],dp[k]+1); //取最小值 
		}
	}
	printf("%d",((dp[l]>1e9)?(-1):(dp[l])));
	return 0;
}
//完结撒花
```
**万望管理员大大通过**

---

## 作者：xiaoshumiao (赞：3)

设 $dp_i$ 为灌溉 $0 \sim i$ 所需要的最小喷灌器数量，则：

$$dp_i=\min\limits_{i-2b \le j \le i-2a}\{dp_j+1\}$$

答案为 $dp_L$。

但题面中说“每只奶牛的草区仅被一个喷灌器灌溉”，这怎么处理？

其实只要满足 $[s+1,e-1]$ 区间内所有点都是不是喷灌器灌溉范围的右端点（也就是把这个位置的 $dp$ 值设为 $\infty$）即可。

为什么？

假设满足 $s+1 \le i \le e-1$ 的 $i$ 处是喷灌器灌溉范围的右端点，那么 $[i+1,e]$ 区间肯定还需要一个喷灌器去灌溉，不满足题意。

由于喷灌器灌溉范围都是偶数（若射程为 $i$，则灌溉范围为 $2i$），所以只需要计算偶数下标的 $dp$ 值。

直接暴力做时间复杂度会超时，因此我们用单调队列优化 DP 的过程，用差分来标记哪些位置不能是喷灌器灌溉范围的右端点。

代码：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int L=1e6+10,INF=0x3f3f3f3f; int dp[L],d[L],q[L];//q 为单调队列，d 为差分数组
int main() {
  int n,l,a,b,h=1,t=1; scanf("%d %d %d %d",&n,&l,&a,&b);
  for(int i=1,s,e;i<=n;i++) scanf("%d %d",&s,&e),d[s+1]++,d[e]--;//标记哪些位置不能是喷灌器灌溉范围的右端点
  for(int i=1;i<=l;i++) d[i]+=d[i-1];
  memset(dp,0x3f,sizeof(dp)),dp[0]=0;
  for(int i=2*a;i<=l;i+=2) {
    while(h<t&&i-q[h]>2*b) h++;
    while(h<t&&dp[i-2*a]<=dp[q[t-1]]) t--;
	q[t++]=i-2*a;
    if(!d[i]) dp[i]=dp[q[h]]+1;
  }
  if(dp[l]>=INF) printf("-1");
  else printf("%d",dp[l]);
  return 0;
}
```

---

## 作者：Naoxiaoyu (赞：2)

# 思路
__单调队列优化动态规划。__

将题目中的喷灌器转化为一条长度在 $2\times A$ 和 $2\times B$ 之间的线段，枚举线段的右端点，设 $dp_i$ 表示 $0$ 到 $i$ 之间最少的喷灌器数目，则状态转移方程为 $dp_i=\max_{i-2\times B\leq j\leq i-2\times A} dp_j+1$，单调队列维护 $dp_j$ 的最大值即可。

题目中还有要求，奶牛的草区内只能被一个喷灌器覆盖，也就是说一只奶牛的草区内只有左端点和右端点可以作为线段的右端点进行枚举，可以用差分的方法预处理，进行动态规划时特判即可。

# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int M=1e3+10;
const int N=1e6+10;
int s[M],e[M];
int dp[N],f[N];
deque<int> q;
int main()
{
	int n,l,a,b;
	memset(dp,127,sizeof(dp));
	scanf("%d%d%d%d",&n,&l,&a,&b);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&s[i],&e[i]);
		f[s[i]+1]++;
		f[e[i]]--;
	}
	for(int i=1;i<=l;i++)
	{
		f[i]+=f[i-1];
	}
	//差分保证复杂度 
	dp[0]=0;
	for(int i=a*2;i<=l;i++)
	{
		while(!q.empty() && dp[i-a*2]<dp[q.back()]) q.pop_back();
		q.push_back(i-a*2);
		while(!q.empty() && q.front()<i-b*2) q.pop_front();
		//维护单调队列 
		if(f[i] || i%2==1) continue;
		//因题目得总长度不能为奇数 
		if(dp[q.front()]!=dp[l+1]) dp[i]=dp[q.front()]+1;
	}
	if(dp[l]==dp[l+1]) printf("-1\n");
	else printf("%d",dp[l]);
    return 0;
}
```

---

## 作者：_exist (赞：2)

# P1545 [USACO04DEC] Dividing the Path G 题解

本来想练练 dp 优化的，但是发现暴力过了，~~就简单水个题解~~。

先读题，若灌溉器位于位置 $i$，那么灌溉的范围就是 $[i-k,i+k]\ (k\in[a,b])$。

那么就可以定义 $dp[i]$，表示将 $i$ 之前的草坪都灌溉完毕需要的最少灌溉器，那么对于每一个 $dp[i]$ 就可以由 $dp[j]$ 转移过来，其中 $j $ 表示上一次灌溉的右边界，于是容易想到状态转移方程：
$$
dp[i]=\min(dp[i],dp[j]+1)
$$
因为我就想着打一个暴力试试，每一个灌溉器的灌溉长度 $[a,b]$ 直接暴力枚举 $j$ 就可以了，当然题目当中还有一些小小的限制条件，有一部分是奶牛的草场，而每个草场又只能由一个灌溉器灌溉，即相当于必须有一个灌溉器将该区间覆盖完，也就相当于在枚举 $j$ 这个右端点时，$j$ 只能由区间 $[s,e]$ 中的端点或区间外的点转移而来，即枚举的 $j$ 不能属于区间 $[s+1,e-1]$ ，那么直接暴力标记，然后就过了，数据太水了。

附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+9;
const int INF=1e9;
int n,l,a,b; 
int dp[N],f[N];
inline int get_min(const int &tx,const int &ty){return tx<ty?tx:ty;}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	memset(dp,0x3f,sizeof(dp));
	cin>>n>>l>>a>>b;
	for(int i=1;i<=n;i=-~i){
		int x,y;cin>>x>>y;
		for(int j=x+1;j<=y-1;j=-~j)f[j]=1;
	}
	dp[0]=0;
	for(int i=2;i<=l;i+=2){
		if(f[i])continue;
		for(int j=a;j<=b;j=-~j){
			int las=i-(j<<1);
//			cout<<'?'<<las<<' ';
			if(las<0)continue;
			dp[i]=get_min(dp[i],dp[las]+1); 
//			cout<<dp[i]<<' '<<dp[las]<<' ';
		}
//		cout<<'\n';
	}
	if(dp[l]>INF)cout<<"-1";
	else cout<<dp[l];
	return 0;
}

```



---

## 作者：渡墨残殇 (赞：1)

## 判断的应是这个位置是否合法而非判断该点是否安装喷灌装置
------------
# 题意

在一个确定的区间 $M$，用最小数量的可改变的确定区间 $x(A<x<B)$，完全覆盖掉这个区间 $M$，且各区间互不相交。

限制条件：子区间 $[s,e]$ 只能被一个区间完全覆盖。

# 分析

考虑子区间 $[s,e]$ 的限制条件，那么意味着覆盖区间时的间断点必然不能在 $[s+1,e-1]$ 这个区间内，而处理的时候只需要跳过即可。

首先，考虑定义状态 $f_i$ 表示覆盖到 $i$ 点时最少的灌溉器，可以得到 $dp$ 转移方程：

### $dp_i=\min(dp_i,dp_j+1)j\in (i-2 \times B,i-2 \times A)$。

由于在区间 $[s+1,e-1]$ 中不可有间断点，我们可以考虑把所有区间赋极大值，初始化 $f_0=0$ 即可。


```cpp
	memset(f, 127, sizeof(f));
	f[0] = 0;
	for (int i = 2; i <= l; i++)
	{
		if (a[i])
			continue;
		for (int j = 2*A; j <= 2*B; j += 2)
		{
			if (i - j < 0)
				break;
			f[i] = min(f[i - j ] + 1, f[i]);
		}
	}
```

不知道为啥，这个 $O(n^2)$ 的代码也能过，不过既然选择来练习单调队列，必然要用单调队列优化 $dp$ 。

观察发现 $j\in (i-2\times B,i-2\times A)$ 这是个可计算出来的确定的区间，而要求的就是求出 $\min(dp_j)$。

那必然可以使用单调队列来优化，照着模板改一下即可。

单调队列板子

```cpp
const int N = 11111111;
int q[N], d[N];      // 数组原值，队列数组
int h = 0, t = 0, k; // 头指针，尾指针，区间大小

for (int i = 1; i <= n; i++)
{
    while (h < t && q[d[t - 1]] <= q[i])
        t--;
    d[t++] = i;
    while (d[t - 1] - d[h] > k)
        h++;
}
```

优化后 $dp$ 


```cpp
	while (h < t && i - pos[h] > 2 * B)
		h++;
	while (h < t && f[i - 2 * A] <= f[pos[t - 1]])
		t--;
	pos[t++] = i - 2 * A;
```

优化后时间复杂度 $O(n)$ 满足题设。

## 代码

```cpp
#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
int a[1001000], f[1212121];
int q[1212122], pos[21312312];
int n, l, h, t;
int A, B;
int main()
{
	// 判断这个位置是否合法，而非判断这个位置是否安装喷洒装置
	cin >> n >> l;
	cin >> A >> B;
	for (int i = 1; i <= n; i++)
	{
		int x, y;
		cin >> x >> y;
		for (int j = x + 1; j < y; j++)
			a[j] = 1;
	}
	memset(f, 127, sizeof(f));
	f[0] = 0;
	for (int i = 2 * A; i <= l; i += 2)
	{
		while (h < t && i - pos[h] > 2 * B)
			h++;
		while (h < t && f[i - 2 * A] <= f[pos[t - 1]])
			t--;
		pos[t++] = i - 2 * A;
		if (a[i])
			continue;
		f[i] = f[pos[h]] + 1;
		// cout << f[i] << "\n";
	}
	if (f[l] >= 2139062143)
		cout << -1;
	else
		cout << f[l];
	return 0;
}
```







---

## 作者：XBaiC (赞：1)

### 题意：

这道题要求给定一个数轴上的若干个非重叠的子区间，用尽可能少的不相交区间覆盖所有的子区间。每个选择出来的区间需要从左到右是严格递增的。

### 思路：

看到题解区有用贪心的方法，这里分析一下单调队列的方法。

单调队列注意区间是左闭右开。

至于那些坏区间，如果某个状态在覆盖了该点的区间的最远的右端点，那是合法的，否则一旦它被覆盖就是不合法状态。

首先区间内除了两端点都不能切开，输入时候维护一下即可，然后单调队列优化 dp $f_{i} = \min {f_{k}} +1$；

注意 $A$ 和 $B$ 都要 $\times 2$。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1100000;
const int inf = 0x3f3f3f3f;
int A, B, t, n;
int c[N], a[N];
int q[N], l, r;
int f[N];
int main() {
	scanf("%d%d%d%d", &t, &n, &A, &B);
	A*=2, B*=2;
	for(int i=1;i<=t;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		for(int i=x+1;i<=y-1;i++) a[i]=1;
		
	}
	for(int i=1;i<A;i++) f[i] = inf;
	for(int i=A;i<=n;i+=2) {
		while(l<r&&q[l]<i-B)l++;
		while(l<r&&f[i-A]<=f[q[r-1]])r--;
		q[r++] = i-A;
		if(a[i]||f[q[l]]==inf)f[i]=inf;
		else f[i]=f[q[l]]+1;
	}
	printf("%d\n",f[n]>1000000?-1:f[n]);
}
```


---

## 作者：2huk (赞：1)

> - 给定一个长为偶数 $l$ 的线段。要求用若干**两两不交**的，长度在 $[2a,2b]$ 之间的偶数长度线段来覆盖整条线段。给定 $n$ 个区间 $[s_i,e_i]$，**每个区间必须只被一个线段覆盖**。求最少需要的线段数量。
> - $l \le 10^6$，$a, b, n \le 10^3$。

如果一个区间 $[s_i, e_i]$ 只被一个线段覆盖，等价于不存在两条线段的交点在 $[s_i + 1, e_i - 1]$ 内。又因为线段两两不交，所以等价于不存在线段的端点在 $[s_i + 1, e_i - 1]$ 内。

考虑剩余的允许放线段端点的位置 $i$。设 $f(i)$ 表示 $i = l$ 时原问题的答案。显然转移：
$$
\begin{aligned}
f(i) &= \min_{j=a}^b \{f(i - 2j) + 1\}\\
&= 1 + \min_{j=\max(0, i - 2b)}^{i-2a} f(j)
\end{aligned}
$$
单调队列/线段树维护即可。

```cpp
#include <bits/stdc++.h>

constexpr int N = 1000010;

int n, l, a, b;

struct Seg {
	int l, r;
}t[N];

int dp[N], sum[N];

struct Tree {
	int l, r, ls, rs, v;
}tr[N << 2];

void pushup(int u) {
	tr[u].v = std::min(tr[tr[u].ls].v, tr[tr[u].rs].v);
}

int idx;

int build(int l, int r) {
	int u = ++ idx;
	tr[u].l = l, tr[u].r = r;
	if (l != r) {
		int mid = l + r >> 1;
		tr[u].ls = build(l, mid), tr[u].rs = build(mid + 1, r);
	} else tr[u].v = 1e9;
	pushup(u);
	return u;
}

int query(int u, int l, int r) {
	if (tr[u].l >= l && tr[u].r <= r) return tr[u].v;
	int mid = tr[u].l + tr[u].r >> 1, res = 1e9;
	if (l <= mid) res = query(tr[u].ls, l, r);
	if (r > mid) res = std::min(res, query(tr[u].rs, l, r));
	return res;
}

void modify(int u, int x, int d) {
	if (tr[u].l == tr[u].r) tr[u].v = d;
	else {
		int mid = tr[u].l + tr[u].r >> 1;
		if (x <= mid) modify(tr[u].ls, x, d);
		else modify(tr[u].rs, x, d);
		pushup(u);
	}
}

int main() {
	std::cin >> n >> l >> a >> b;
	
	for (int i = 1; i <= n; ++ i ) {
		std::cin >> t[i].l >> t[i].r;
		++ sum[t[i].l + 1], -- sum[t[i].r];
	}
	
	for (int i = 1; i <= l; ++ i ) sum[i] += sum[i - 1];
	
	build(1, l + 1);
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	modify(1, 1, 0);
	for (int i = 2; i <= l; i += 2 )
		if (!sum[i]) {
			int L = std::max(0, i - 2 * b), R = i - 2 * a;
			
			for (int j = L; j <= R; ++ j ) dp[i] = std::min(dp[i], dp[j] + 1);
			modify(1, i + 1, dp[i]);
		}
	
	if (dp[l] >= 1e9) dp[l] = -1;
	std::cout << dp[l];
	
	return 0;
}
```

---

## 作者：wizard（偷开O2 (赞：0)

一道数据结构维护动态规划的好题。

### 题意

有一个长为 $L$ 的序列上有 $N$ 个可重叠区间，可以用长度在 $(2 \times A,2 \times B)$ 间的线段覆盖区间，前提是一个区间只能由一条线段覆盖，线段不相交，且线段不能越界。最后保证序列被全部覆盖，求最少的线段个数。

### 分析

用差分维护被覆盖的区间，分析得到一个线段不一定全被区间包住，也就是说，一个线段的两边不一定都在草上，所以我们应该在序列上用偶数节点进行动态规划。

则可以直接列出状态转移方程：$dp_{i}=\min(dp_{j})+1$。因为后一个状态明显比前一个状态更优，所以直接利用单调栈来维护 $dp$ 序列。

对于无解，有几种情况：如果区间比最大射程还大，那也就是说一个线段不能包括在一个区间中，无解；如果结果不满足单调性，无解；如果最后动态规划答案不存在，无解。

扫一遍偶数节点，因为差分数组内，只有区间的边界才有数值，所以如果遇到边界，就直接返回跳出去。

在单调队列维护的过程中，维护两个位置：区间开头与结尾，在区间中有值的情况下，如果说当前区间长度大于了最大射程，就把左端点往右推以缩小区间长度。

```cpp
while(l<=r&&i-q[l]>2*b){l++;}
```

在 $dp$ 区间有值的情况下，如果 $dp$ 区间的右端点大于当前节点，就把右端点往左推来维护单调性。

```cpp
while(l<=r&&dp[i]<dp[q[r]]){r--;}
```

最后 $dp$ 的末状态就是 $dp_{L}$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
const int maxn=1e6+10;
int n,L,a,b;
int dp[maxn],sum[maxn],q[maxn],l,r;
signed main(){
    cin >> n >> L >> a >> b;
    for(int i=1;i<=n;i++){
        int x,y;
		cin >> x >> y;
        sum[x+1]++;sum[y]--;
        if(y-x>2*b){//区间比射程还大 
			cout << -1 << endl;
			return 0;
		}
    }
    for(int i=1;i<=L;i++){
    	sum[i]+=sum[i-1];	
	}
    l=r=1;q[1]=0;
    for(int i=2*a;i<=L;i+=2){
        if(sum[i])continue;
        while(l<=r&&i-q[l]>2*b){
        	l++;
		}
        if(i-q[l]<2*a)continue;//射程之内
        if(l>r){cout << -1 << endl;return 0;}
        dp[i]=dp[q[l]]+1;
        while(l<=r&&dp[i]<dp[q[r]]){
        	r--;
		}
		q[++r]=i;
    }
    if(dp[L]){
		cout << dp[L] << endl;
	}else{
		cout << -1 << endl;
	}
    return 0;
}
```

---

## 作者：spire001 (赞：0)

## 题目大意
题面说的比较清楚，就不加赘述。
其主要的三点约束是：
1. 区间长度有上界和下届。
2. 草区只允许被一次覆盖。
3. 不能超出界限。

## 题目分析

首先第三条约束和第一条约束很容易完成。
只需要设置转移区间即可。

而第二条约束我们可以对其做一个等效，即做一个标记，让区间内（不含端点）的数不能作为端点。

这里打标记可以利用差分的思想完成。

这样就可以完美的解决第二条约束。  
然后就是标准的优化 dp 解题过程了。

首先列出状态转移方程：
$$
dp_i = \min^{i-B}_{i-A}\{dp_j+1\}
$$

其中 $dp_i$ 指的是刷了 $i$ 个点以前的最小喷头数。
由于题目是刷点而非刷边，我们的状态可以理解为从起点 $0$ 到 $i$ 的左闭右开区间。

然后就可以给出代码：
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <climits>
#define lc(i) (i << 1)
#define rc(i) (i << 1 | 1)
using namespace std;

constexpr int N = 1000010;
typedef long long LL;

int L, n;

struct node{
  int l, r;
} a[N];

int flag[N];
int dp[N], down, up;

struct tree { // 线段树
  int l, r, mi = 1e9;
} t[N << 2];

void build(int l, int r, int root = 1) // 建树
{
  t[root].l = l; t[root].r = r;

  if (l == r)
    return;
  
  int mid = (l + r) >> 1;

  build(l, mid, lc(root));
  build(mid + 1, r, rc(root));
}
void change(const int pos, const int val, int root = 1) // 单点修改
{
  if (t[root].l == t[root].r)
    return t[root].mi = val, void();

  int mid = (t[root].l + t[root].r) >> 1;
  
  if (pos <= mid)
    change(pos, val, lc(root));
  else 
    change(pos, val, rc(root));
  
  t[root].mi = min(t[lc(root)].mi, t[rc(root)].mi);

  return;
}

int ask(const int l, const int r, int root = 1) // 询问区间最小值
{
  if (l <= t[root].l && t[root].r <= r)
    return t[root].mi;

  int mid = (t[root].l + t[root].r) >> 1;

  int ans = INT_MAX;

  if (l <= mid)
    ans = min(ans, ask(l, r, lc(root)));
  if (r >  mid)
    ans = min(ans, ask(l, r, rc(root)));

  return ans;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  cin >> n >> L >> down >> up;

  for (int i = 1; i <= n; i++)
    cin >> a[i].l >> a[i].r, flag[a[i].l + 1]++, flag[a[i].r]--;
  
  for (int i = 1; i <= L; i++) // 查分打标记
    flag[i] += flag[i - 1];
  
  for (int i = 0; i <= L; i++) // 取反，让逻辑更加清晰
    flag[i] = !flag[i];
  
  for (int i = 0; i <= L; i++)
    dp[i] = 1e9 + 7;

  build(0, L); // 注意不是 build(1, n)

  for (int i = down * 2; i <= up * 2; i += 2) // 初始化
    if (flag[i])
      dp[i] = 1, change(i, 1);

  for (int i = up * 2 + 2; i <= L; i += 2) // 题面要求只有偶数状态合理
  {
    if (!flag[i]) continue;
    dp[i] = ask(i - up * 2, i - down * 2) + 1;
    change(i, dp[i]);
  }

  if (dp[L] >= 1e9) // 无法完成
    cout << -1 << endl;
  else 
    cout << dp[L] << endl;
  
  return 0;
}

```

其实这个题目暴力就可以通过了，数据亟待加强。

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$
很显然我们可以用 DP 来解决这个问题，设 $f_{i}$ 表示在第 $i$ 个位置前的所有草地均被覆盖的最小代价。由于一片草地必须被一个喷头完全覆盖，所以我们只需要不转移 $[s_i+1,e_i+1]$ 的区间就可以了。这个可以用差分标记。

转移式子就是 $f_i=\min\limits_{i-2b\leq j\leq i-2a\wedge vis_j=0}f_j+1$。（$vis_i$ 表示是否可以转移 $i$）。

考虑优化，一段连续区间的最小值，考虑单调队列优化，先将队首的超出转移范围的元素出队，再将队尾的 $f$ 的值大于等于当前的 $f$ 值的元素出队，接着入队当前元素，最后判断是否能够转移，和板子没什么区别就不多说了。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=1e6+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,l,f[N],a,b,q[N],hh,tt,vis[N];
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	l=read();
	a=read()<<1;
	b=read()<<1;
	rep1(i,1,n)
	{
		++vis[read()+1];
		--vis[read()];
	}
	rep1(i,1,l) vis[i]+=vis[i-1];
	memset(f,inf,sizeof f);
	f[0]=0;
	hh=1;
	tt=1;
	for(int i=a;i<=l;i+=2)
	{
		while(hh<=tt&&q[hh]<i-b) ++hh;
		while(hh<=tt&&f[q[tt]]>=f[i-a]) --tt;
		q[++tt]=i-a;
		if(!vis[i]) f[i]=f[q[hh]]+1;
	}
	if(f[l]>=inf) puts("-1");
	else cout<<f[l]<<endl;
	return 0;
}
```

---

## 作者：Elysian_Realme (赞：0)

# P1545 [USACO04DEC] Dividing the Path G

~~闻着线段树的味过来了，结果发现单调队列就可以。~~

看到这题就猜到要用 DP，定义 $dp_i$ 表示从 $0$ 到 $i$ 最少需要几个。

转移方程就是 $dp[i]=\min_{i-b\le j \le i-a}(dp[j]+1)$（$a,b$ 已乘二）。

不难发现，这个取 $\min$ 可以用线段树或单调队列优化掉（单调队列跑得快而且代码还简单，~~应该不会有硬写线段树的吧~~）。

这是[代码](https://www.luogu.com.cn/paste/6evxi7ir)。

关于我做题时的一些疑问：

- 为什么要将 $a,b$ 分别乘 $2$？因为我们 $dp$ 数组的定义是从 $0$ 到当前点，显然，如此更改之后我们就可以通过找 $i-b\sim i-a$ 的最小值来转移。

- 计算 $dp$ 的循环中 $i$ 的初值？为什么每次要 `i+=2`？在最靠左的位置放一个射程最小的喷灌器，刚好可以覆盖 $0\sim 2a$，在往左就溢出了（输入时已经乘二所以附为 $a$）。每次 `i+=2` 是因为射程每增大 $1$，管辖范围就会 $+2$，如果 $+1$ 就可能会导致重叠。

---

## 作者：Addicted_Game (赞：0)

# [传送门](https://www.luogu.com.cn/problem/P1545)

### 题目大意
给定几个区间，与覆盖区间的最长距离与最短距离，求最少需要几个区间才能包含所有区间（覆盖区间不重合）。

### 思路
很明显是一道 **dp** 题目，要在可包含区间找最小值。

动态转移方程：
$ dp[i]= \min ( dp [ k ] + 1) (k \in [ i - 2 \times b , i - 2 \times a ]) $。
#### 优化
这里只需要求最小值，且区间长度已知，可以想到**滑动窗口**，用单调队列维护区间最小值。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,l,a,b;
int s,e;
int vis[1100005];
int dp[1100005];
deque<int> q;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	memset(dp,0x3f,sizeof dp);
	cin>>n>>l>>a>>b;
	a*=2;
	b*=2;
   //因为是以i为最左侧所以最大灌溉区域要翻倍
	for(int i=1;i<=n;i++){
		cin>>s>>e;
		vis[s+1]++;
		vis[e]--;//差分优化时间
	}
	for(int i=1;i<=l;i++){
		vis[i]+=vis[i-1];
	}
	dp[0]=0;
	for(int i=a;i<=l;i+=2){
		while(!q.empty()&&q.front()<i-b){
			q.pop_front();//掐头
		}
		while(!q.empty()&&dp[i-a]<=dp[q.back()]){
			q.pop_back();//去尾
		}
       //找到最大值
		q.push_back(i-a);
		if(!vis[i]) dp[i]=dp[q.front()]+1;
	}
	if(dp[l]>=0x3f3f3f3f) cout<<"-1";
	else cout<<dp[l];
	return 0;
}
```
时间复杂度 $O(n)$。


---

## 作者：zwye (赞：0)

## 思路
一道单调队列优化 `DP` 的练手题，下面讲讲思路：
首先提到对于每一个 $Si \sim Ei$，不能被不同的喷灌器喷灌，那么也就是说 $Si+1 \sim Ei-1$ 都不能成为任何一个喷灌器的右边界，所以我们开一个数组 $l_{i}$ 判断 $i$ 能否成为某一个喷灌器的右边界，若可以，$l_{i}=$`false`，反之，$l_{i}=$`true`。

接着，我们考虑状态，定义 $f_{i}$ 表示当覆盖长度为 $i$ 时用的最少的喷灌器的数量，也就是说，$i$ 是一个喷灌器的右边界，我们要枚举它的左边界，所以对于每一个合法的 $i$（即 $l_{i}=$`false`）。

很明显，这样做的时间复杂度是 $O(n^2)$ 的，不可取。

我们发现 $f_{i}$ 一定是由满足 $A\leq(i-j)/2\leq B$ 且 $f_{j}$ 最小的j转移过来的，所以选用单调队列维护这个最小值。当（$i-$ 队首元素下标）$/2>B$ 时，队首元素出队。另外还要再开一个队列存储元素编号，只有当这个队列队首元素的下标满足（$i-$ 队首元素下标）$/2\geq A$ 时，才可以将这个元素压进单调队列。

这样就可以优化到 $O(n)$ 的复杂度了，问题解决。
## 代码
```c
#include<bits/stdc++.h>
using namespace std;
int N,L,A,B,s,e;
int q[1000001],head=1,tail;
int p[1000001],h=1,t;
int f[1000001];
bool l[1000001];
int main()
{
    scanf("%d%d",&N,&L);
    scanf("%d%d",&A,&B);
    for(register int i=1;i<=N;i+=1)
    {
        scanf("%d%d",&s,&e);
        for(register int j=s+1;j<=e-1;j+=1)l[j]=true;
    }
    memset(f,127,sizeof(f));
    f[0]=0;
    p[++t]=0;
    for(register int i=2;i<=L;i+=2)
    {
        if(l[i]==true)continue;
        while(h<=t&&(i-p[h])/2>=A)
        {
            while(head<=tail&&f[q[tail]]>=f[p[h]])tail--;
            q[++tail]=p[h];
            h++;
        }
        while(head<=tail&&(i-q[head])/2>B)head++;
        if(head<=tail)
        {
            f[i]=f[q[head]]+1;
            p[++t]=i;
        }
    }
    if(f[L]!=2139062143)printf("%d\n",f[L]);
    else printf("-1\n");
    return 0;
}

```

---

