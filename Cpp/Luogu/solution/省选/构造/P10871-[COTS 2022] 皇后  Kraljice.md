# [COTS 2022] 皇后  Kraljice

## 题目背景


译自 [Izborne Pripreme 2022 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2022/) D1T1。$\texttt{1s,0.5G}$。



## 题目描述

有一块 $N\times N$ 的国际象棋棋盘，**依次**在空格子上放置皇后，最大化放置皇后的数量。你需要构造一组方案。

能在一个格子上放置皇后，当且仅当这个格子被偶数个皇后攻击。

一个皇后攻击一个格子，当且仅当皇后所在的格子与被攻击格子处于同一行/列/对角线上。

## 说明/提示


### 样例解释

样例 $3$ 解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/qr1b2kcs.png)

#### 数据范围

对于 $100\%$ 的数据，保证 $1\le N\le 2^{10}$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $6$  | $1\le N\le 2^4$  |
| $2$  | $11$  | $1\le N\le 2^6$  |
| $3$  | $28$  | $1\le N\le 2^8$ |
| $4$  | $55$  | 无额外约束 |


## 样例 #1

### 输入

```
1```

### 输出

```
1
1 1

```

## 样例 #2

### 输入

```
2```

### 输出

```
1
1 1
```

## 样例 #3

### 输入

```
3```

### 输出

```
9
2 3
3 1
2 2
1 1
3 3
3 2
1 2
1 3
2 1
```

# 题解

## 作者：zyh_helen (赞：7)

非常有意思的一道题，这里提供一下我的构造方法。

---
---

点进来一看到样例吓一跳，这不直接猜棋子数是 $n^2$ 吗？又看 $n=2$ 的样例，就直接猜 $n$ 是奇数的时候棋子数是 $n^2$ 了。

先不细想正确性，考虑 $n$ 是偶数的最小棋子数，看到样例很难不让人想到 $(n-1)^2$，但想构造越想越不对劲，感觉还可以再放，但放满 $(n-1)^2$ 之后就再也放不了了呀。

小小手玩了一下，发现 $n=4$ 的时候可以在外面先围个圈，再在其中放就可以做到更优秀。

---

我们改变之前从上往下放的思路，但是整体归纳分析的思路不能变，于是我们使用经典的从外到内放，发现外面的一圈对中间是没有影响的：每个棋子八个方向各有 $x$（外围圈数）个皇后，刚好抵消了。

所以我们只用考虑一圈怎么构造。接着我们开始手玩，这里我直接给出方法：

- 首先对于上边和下边，我们交替错开分别连着放两个棋子，容易证明这时符合要求。

- 接着对于左边和右边，我们也是交替错开分别连着放两个棋子，这时候由于上边和下边的皇后对于一个点刚好抵消，所以也是符合要求的。

这里一定要注意边界细节，可以参考代码的实现。

---

观察到我们此时昨晚上面两步后的形状大概是这样的：

```
111110
100001
100001
100001
100001
011110
```

但最后三个棋子无论怎样都放不进去，这时候我们做一步巧妙的步骤：往内层右上角先放一个。

我们发现它是能放进去的，并且放进去后，外层右上角也能放了，接着右下角，左下角都能放了。

这也带来一个问题，那就是我们往内层放了一个，打乱了节奏。这也很好解决，我们下一轮左右翻转一下就行了，毕竟我们本来第一个就是放角落的。

---

分析一下，除了最后到了 $2\times2$ 的矩阵无法继续操作，其他都可以，所以我们偶数的最小步数是 $n^2 - 3$。（别急，还不是正解，但我显然当时以为是最小了）

回过头看奇数，不也是这么做吗？

但同样的，到了 $3\times3$ 的矩阵无法继续操作，这时候，就要注意样例了！

样例给出了 $3\times3$ 的构造方案，我们只要将其前两步调转（显然不影响）正确性，就是我们所需要的解了。

---

到这里，我们已经有了清晰的构造方案，奇数 $n^2$，偶数 $n^2-3$。

但是当你信心满满的交上去，竟是 WA！

---

偷偷看一下错误信息，原来是偶数我们的答案大了 1。

接着又是手玩，可以在 $4\times4$ 的最后时候人类智慧的优化一步。

```
1110    1110    1111    1111    1111    1111
1001 -> 1011 -> 1011 -> 1011 -> 1011 -> 1011
1001    1001    1001    1101    1101    1111
0110    0110    0110    0110    0111    0111
```

左右翻转的时候同理。

至此这道题就结束了。

---
---

```cpp
#include<bits/stdc++.h>
//#include<Windows.h>
#define int long long
//#define ll long long
//#define double long double
#define fi first
#define se second
//#define ls t[p].l
//#define rs t[p].r
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 4e3 + 10, inf = 1e9, M = 2e5;
//const double eps = 1e-16;
const int mod = 1e9 + 7;
//const int mod;
//const int AQX = 9;
mt19937 rnd(time(0) ^ clock());
int random(int l, int r){
	return rnd() % (r - l + 1) + l;
}
const int offset = 101, offset2 = 103;
/*
		    	           _      _        _          
			       ____  _| |_   | |_  ___| |___ _ _  
			      |_ / || | ' \  | ' \/ -_) / -_) ' \ 
			      /__|\_, |_||_|_|_||_\___|_\___|_||_|
			          |__/    |___|                              
				       
*/
//struct Graph{
//	int head[N], tot;
//	struct edge{
//		int t, f;
//		int d, fa;
//		int next;
//	}e[N << 1];
//	void edge_add(int u, int v, int w = 0){
//		e[++tot].next = head[u];
//		e[tot].t = v;
//		e[tot].d = w;
//		e[tot].f = u;
//		head[u] = tot;
//	}
//	void clear(int n){
//		for(int i = 1;i <= tot;i++)e[i].t = e[i].f = e[i].d = e[i].next = 0;
//		for(int i = 1;i <= n;i++)head[i] = 0;
//		tot = 0;
//	}
//}g1, g2;
//int qmr(int x, int a){
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}

int n, vis[N][N];
vector<pair<int, int> >v;
void work(int nw, int f, int p){
	if(nw == 2)return;
	if(nw == 3){
		if(f == 1){
			v.push_back({p + 1, p + 2});
			v.push_back({p + 1, p + 1});
			v.push_back({p + 2, p});
			v.push_back({p + 2, p + 2});
			v.push_back({p + 2, p + 1});
			v.push_back({p, p + 1});
			v.push_back({p, p + 2});
			v.push_back({p + 1, p});
		}
		else {
			v.push_back({p + 1, p});
			v.push_back({p + 1, p + 1});
			v.push_back({p + 2, p + 2});
			v.push_back({p + 2, p});
			v.push_back({p + 2, p + 1});
			v.push_back({p, p + 1});
			v.push_back({p, p});
			v.push_back({p + 1, p + 2});
		}
		return;
	}
	if(f == 1){
		for(int i = p + 1, f = 0;i < nw + p - 1;i++, f ^= 1){
			if(f)v.push_back({p, i}), v.push_back({p + nw - 1, i});
			else v.push_back({p + nw - 1, i}), v.push_back({p, i});
		}
		for(int i = nw + p - 2, f = 0;i > p;i--, f ^= 1){
			if(f)v.push_back({i, p}), v.push_back({i, p + nw - 1});
			else v.push_back({i, p + nw - 1}), v.push_back({i, p});
		}
		if(nw == 4){
			v.push_back({p + 1, n - p});
			v.push_back({p, n - p + 1});
			v.push_back({p + 2, n - p - 1});
			v.push_back({p + 3, p + 3});
			v.push_back({p + 2, p + 2});
		}
		else {
			v.push_back({p + 1, n - p});
			v.push_back({p, n - p + 1});
			v.push_back({n - p + 1, n - p + 1});
			v.push_back({n - p + 1, p});
			work(nw - 2, 2, p + 1);
		}
	}
	else {
		for(int i = nw + p - 2, f = 0;i > p;i--, f ^= 1){
			if(f)v.push_back({p, i}), v.push_back({p + nw - 1, i});
			else v.push_back({p + nw - 1, i}), v.push_back({p, i});
		}
		for(int i = nw + p - 2, f = 1;i > p;i--, f ^= 1){
			if(f)v.push_back({i, p}), v.push_back({i, p + nw - 1});
			else v.push_back({i, p + nw - 1}), v.push_back({i, p});
		}
		if(nw == 4){
			v.push_back({p + 1, p + 1});
			v.push_back({p, p});
			v.push_back({p + 2, p + 2});
			v.push_back({p + 3, p});
			v.push_back({p + 2, p + 1});
		}
		else {
			v.push_back({p + 1, p + 1});
			v.push_back({p, p});
			v.push_back({n - p + 1, p});
			v.push_back({n - p + 1, n - p + 1});
		}
		work(nw - 2, 1, p + 1);
	}
}
signed main(){
	cin >> n;
	if(n <= 2){
		cout << "1\n1 1\n" << endl;
		return 0;
	}
	cout << n * n - 2 * (n % 2 == 0) << endl;
	v.push_back({1, 1});
	work(n, 1, 1);
	for(auto x : v)printf("%lld %lld\n", x.fi, x.se);
	return 0;
}
/*


2 3
3 1
2 2
1 1
3 3
3 2
1 2
1 3
2 1
*/

---

## 作者：masterhuang (赞：3)

更好的阅读体验：[我的博客](https://www.cnblogs.com/HaHeHyt/p/18486444)！

这题我想到了一个绝妙的构造方法，空间足够，我写下了。

---

首先，当 $n\le 2$ 时答案均为 $1$。下面 $n\ge 3$。

此时若 $n$ 为奇数，则答案为 $n^2$。否则答案为 $n^2-2$。

接下来构造。请注意观察 $n=3$ 的情况，尤其是倒二步剩下的那个缺口，在后面十分关键。

![](https://cdn.luogu.com.cn/upload/image_hosting/qr1b2kcs.png)

---

首先考虑偶数，先是 $n=4$ 的情况。

我们先构造一个缺口：

```
0111
0x11
0111
x000
```

而后再依次填上位置 $(1,1),(4,2),(4,4),(3,1),(2,1),(4,3)$ 即可，其中两个 `x` 是最后空的格子。

然后考虑构造一个如下的外壳递归到 $n-2$ 的情况：

```
111111
100001
100001
100001
100001
111111
```

首先这样：

```
1357...00
0000...00
0000...00
0000...00
0000...00
4286...00
```

继续下去构造成这样 $(*)$：

```
1111...1100
0000...0000
0000...0000
0000...0000
0000...0000
1111...1100
```

但此时最后四个不能类似构造（对角线有影响），稍微动点脑子：

```
1111...11AB
0000...0000
0000...0000
0000...0000
0000...0000
1111...11DC
```

然后是左右两侧：

```
1111...1111
A000...000D
1000...0004
.  .      .
.    .    .
.      .  .
3000...0002
C000...000B
1111...1111
```

此时没有对角线的影响能直接构造完整个边框。

然后递归：$n\to n-2\to n-4\to \cdots \to 4$，最后上 $n=4$ 的构造即可。

偶数：

```cpp
inline void out(int x,int y){cout<<x<<" "<<y<<"\n";}//输出
inline void ex3(int m,int M)
{
	out(m,M+1);out(m+1,M-1);out(m,M);out(m-1,M-1);
	out(m+1,M+1);out(m+1,M);out(m-1,M);out(m-1,M+1);
}//3 的带有缺口的构造
namespace even
{
	inline void sol(int l,int r)
	{
		if(l+3==r) return;
		for(int i=l;i<r-2;i+=2)
		{
			out(l,i);out(r,i+1);
			out(l,i+1);out(r,i);
		}
		out(l,r-1);out(l,r);
		out(r,r);out(r,r-1);

		for(int i=l+1;i<=(l+r-1)/2;i++)
		{
			out(i,l);out(l+r-i,r);
			out(l+r-i,l);out(i,r);
		}
		sol(l+1,r-1);
	}//构造边框，递归到 n-2
	inline void get()
	{
		cout<<n*n-2<<"\n";
		sol(1,n);
		int l=(n/2)-2;ex3(l+2,l+3);

		out(l+1,l+1);
		out(l+4,l+2);
		out(l+4,l+4);
		out(l+3,l+1);
		out(l+2,l+1);
		out(l+4,l+3);//n=4 的构造
	}
}
```

---

然后考虑奇数，此时构造边框就比较难了（反正我不会）。

此时考虑一点其他的优美构型，参考 $n$ 为偶数时**左右边框**的方法：

先这样：

```
0000000
1000001
1000001
0000000
1000001
1000001
0000000
```

再这样：

```
0110110
1000001
1000001
0000000
1000001
1000001
0110110
```

递归下去，构造成只剩余中间米字型：

```
0110110
1010101
1100011
0000000
1100011
1010101
0110110
```

---

此时如果直接填满中间 $3\times 3$，则剩下就没有位置可以给我们填了。

还是考虑 $3\times 3$ 构造中的**缺口！**

我们先这样构造，其中 `x` 位置是缺口：

```
0110110
1010101
1111111
00x1100
1111111
1010101
0110110
```

然后继续剥外壳（按字母顺序）：

```
E11B11G
1010101
1111111
A0x110C
1111111
1010101
D11H11F
```

然后把剥外壳的过程递归下去构造，最后填上位置 `x` 即可！

奇数：

```cpp
inline void out(int x,int y){cout<<x<<" "<<y<<"\n";}//输出
inline void ex3(int m,int M)
{
	out(m,M+1);out(m+1,M-1);out(m,M);out(m-1,M-1);
	out(m+1,M+1);out(m+1,M);out(m-1,M);out(m-1,M+1);
}//3 的带有缺口的构造
namespace odd
{
	inline void sol(int l,int r)
	{
		if(l==r) return;int m=(l+r)/2;
		for(int i=l+1;i<m;i++)
		{
			out(i,l);out(l+r-i,r);
			out(n+1-i,l);out(i,r);
		}
		for(int i=l+1;i<m;i++)
		{
			out(l,i);out(r,l+r-i);
			out(l,l+r-i);out(r,i);
		}
		sol(l+1,r-1);
	}//递归构造到只剩米字型
	inline void sol1(int l,int r)
	{
		if(l+2==r) return;int m=(l+r)>>1;
		out(m,l);out(l,m);out(m,r);
		out(r,l);out(l,l);out(r,r);out(l,r);
		out(r,m);
		sol1(l+1,r-1);
	}//继续剥米字型的外壳
	inline void get()
	{
		cout<<n*n<<"\n";
		sol(1,n);
		int m=(n+1)/2;ex3(m,m);
		sol1(1,n);
		out(m,m-1);
	}
}
```

---

于是本题就做完啦！这篇题解给出了一种极其精妙且极富有对称性的构造方法。欢迎大家学习借鉴。

完整代码：

```cpp
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=1<<10|5;
int n;
inline void out(int x,int y){cout<<x<<" "<<y<<"\n";}
inline void ex3(int m,int M)
{
	out(m,M+1);out(m+1,M-1);out(m,M);out(m-1,M-1);
	out(m+1,M+1);out(m+1,M);out(m-1,M);out(m-1,M+1);
}
namespace odd
{
	inline void sol(int l,int r)
	{
		if(l==r) return;int m=(l+r)/2;
		for(int i=l+1;i<m;i++)
		{
			out(i,l);out(l+r-i,r);
			out(n+1-i,l);out(i,r);
		}
		for(int i=l+1;i<m;i++)
		{
			out(l,i);out(r,l+r-i);
			out(l,l+r-i);out(r,i);
		}
		sol(l+1,r-1);
	}
	inline void sol1(int l,int r)
	{
		if(l+2==r) return;int m=(l+r)>>1;
		out(m,l);out(l,m);out(m,r);
		out(r,l);out(l,l);out(r,r);out(l,r);
		out(r,m);
		sol1(l+1,r-1);
	}
	inline void get()
	{
		cout<<n*n<<"\n";
		sol(1,n);
		int m=(n+1)/2;ex3(m,m);
		sol1(1,n);
		out(m,m-1);
	}
}
namespace even
{
	inline void sol(int l,int r)
	{
		if(l+3==r) return;
		for(int i=l;i<r-2;i+=2)
		{
			out(l,i);out(r,i+1);
			out(l,i+1);out(r,i);
		}
		out(l,r-1);out(l,r);
		out(r,r);out(r,r-1);

		for(int i=l+1;i<=(l+r-1)/2;i++)
		{
			out(i,l);out(l+r-i,r);
			out(l+r-i,l);out(i,r);
		}
		sol(l+1,r-1);
	}
	inline void get()
	{
		cout<<n*n-2<<"\n";
		sol(1,n);
		int l=(n/2)-2;ex3(l+2,l+3);

		out(l+1,l+1);
		out(l+4,l+2);
		out(l+4,l+4);
		out(l+3,l+1);
		out(l+2,l+1);
		out(l+4,l+3);
	}
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n;
	if(n<=2) return cout<<"1\n1 1\n",0;
	return (n&1)?odd::get():even::get(),0;
}
```

</details>

---

## 作者：qnqfff (赞：2)

### 思路

考虑递归构造，每次删掉两行两列，注意 $n\le4$ 要特判，按照以下方式放。

![](https://cdn.luogu.com.cn/upload/image_hosting/qfyjcoes.png?x-oss-process=image)

即前 $5$ 个先放，然后蛇形填满前两行，然后蛇形填满前两列，注意最后一行第二个放之前要放 $(2,2)$ ，然后做完了。 

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<23],*p1=buf,*p2=buf;
int read(){int p=0,flg=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-') flg=-1;c=getchar();}while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}return p*flg;}
int n;
signed main(){
	n=read();
	vector<array<int,2>>ans;
	for(;;n-=2){
		auto F=[&](int x,int y){ans.push_back({x,y});}; 
		if(n<=2){F(1,1);break;}
		if(n==3){F(2,3);F(3,1);F(2,2);F(1,1);F(3,3);F(3,2);F(1,2);F(1,3);F(2,1);break;}
		if(n==4){F(1,1);F(2,3);F(2,2);F(3,1);F(3,3);F(2,1);F(4,1);F(3,2);F(1,4);F(1,2);F(3,4);F(2,4);F(4,3);F(4,4);break;}
		F(n,n);F(n-1,n-2);F(n-1,n);F(n,n-2);F(n,n-1);
		for(int i=n-3,j=0;i;i--,j^=1){if(!j) F(n,i),F(n-1,i);else F(n-1,i),F(n,i);}
		for(int i=n-2,j=0;i^1;i--,j^=1){if(!j) F(i,n-1),F(i,n);else F(i,n),F(i,n-1);}
		if(n&1) F(n-1,n-1),F(1,n-1),F(1,n);else F(1,n),F(n-1,n-1),F(1,n-1);
	}cout<<ans.size()<<'\n';for(auto i:ans) cout<<i[0]<<' '<<i[1]<<'\n';
	return 0;
}
```

---

## 作者：xxgirlxx (赞：1)

好玩。

同一场的 [P10872](https://www.luogu.com.cn/problem/P10872) 和 [P10873](https://www.luogu.com.cn/problem/P10873) 也好玩，可以去看看。

经过大量的手玩可以发现一些性质。

首先，$n$ 为奇数可以放下 $n\times n$ 个棋子，$n$ 为除了 $2$ 以外的偶数可以放下 $n\times n-2$ 个棋子。

其次，实际构造的时候会从外到内一层层构造。

再次：如果外层的构造是上下和左右还有对角线都对称，那么在空的格子放棋子一定是合法的（因为完全对称）。

最后，最大的放的棋子数取决于你最中间的操作数有多优（这就是为什么 $n=2$ 需要单独判，因为偶数的最优操作需要 $n\ge4$，具体的情况后面会讲）。

接下来我们先搞清楚怎么一层层构造：

有一个方法是每一层分四条边（去掉角上的），四条边上依次放一个，但是注意放的时候放的位置也要注意：具体地，如果现在这一层是在构造 $(l,l+1)$ 到 $(l,r-1)$，$(l+1,l)$ 到 $(r-1,l)$，$(r,l+1)$ 到 $(r,r-1)$ 和 $(l+1,r)$ 到 $(r-1,r)$ 这四条边，那么四条边上放的棋子的位置就得是第一轮四个：$(l,l+x)$，$(l+x,r)$，$(r-x,l)$ 和 $(r,r-x)$，第二轮四个：$(l,l+y)$，$(l+y,r)$，$(r-y,l)$ 和 $(r,r-y)$（其中 $y=r-l-x$）。
具体地：

![](https://cdn.luogu.com.cn/upload/image_hosting/c5dajm3x.png)

但是为什么要这么构造呢？

我们先把第二轮的撤下看看第一轮的棋子对棋盘有什么影响：

![](https://cdn.luogu.com.cn/upload/image_hosting/2f70re27.png)

可以发现，每一轮的四个棋子之间互不影响，而且他们都能攻击到第二轮的四个棋子，所以可以保证第二轮的四个棋子是合法的，而第二轮的四个棋子放进来就使得外层的构造是上下和左右还有对角线都对称，因此接下来的操作就可以忽略这两轮棋子的影响。

这个结论对吗？对！但不完全对！我第一次做这个题之所以假了就是因为少考虑了一点：当两轮的棋子会在同一个位置的时候这个结论就不对了。

因此偶数我们的外层能构造成这样：
```cpp
011110
100001
100001
100001
100001
011110
```
但是奇数我们的外层只能构造成这样：
```cpp
01010
10001
00000
10001
01010
```
那四个角怎么办呢？好办！

注意到我们四个角最多就放一个。

那么偶数就是：
```cpp
011110
100001
100001
100001
100001
011110
```
奇数就是：
```cpp
11010
10001
00000
10001
01010
```
这又有什么用呢？欸，等一下，你仔细看看奇数的情况：我们可以把四条边中间的格子填上啦！具体的顺序是：右左下上。当然也有别的顺序。

这样奇数就可以变成：
```cpp
11110
10001
10001
10001
01110
```
然后我们再考虑怎么将剩下三个角填上。

由于里面那一层也会先填上一个角，我们看看这会不会对我们有帮助：
```cpp
11110
11001
10001
10001
01110
```
额······这好像非法啊。

别急，换个角再放：
```cpp
11110
10011
10001
10001
01110
```
欸！这样我们就能把剩下三个角填上了，具体地顺序是先右上再右下最后左下。当然也有别的顺序。

这样我们就把一层填完了。

最后我们来考虑最优解。

奇数的情况是：
```cpp
11111
10011
10001
10001
11111
```
偶数的情况是：
```cpp
111111
111111
111011
110011
111111
111111
```
注意到奇数只剩下了 $8$ 个格子，直接暴力搜索，搜出来最优解是全部都能放，这肯定最优了。但是偶数会有三个格子不能放，这不一定最优，于是考虑将最内层从边长为 $2$ 改到边长为 $4$，搜出来结果是有两个格子不能放，更优。

具体的放置过程（$0$ 的位置为为构造外层而提前放置的格子）：

$n=4$：

|0|0|0||
|:-:|:-:|:-:|:-:|
|**0**|**2**|**1**|**0**|
|**0**|**3**||**0**|
|**5**|**0**|**0**|**4**|

$n=3$：
|0|8|3|
|:-:|:-:|:-:|
|**5**|**2**|**6**|
|**4**|**1**|**7**|

（~~相信聪明的你一定发现了这是样例旋转并交换操作一二后得到的~~）

注意一下因为两层之间先放的角是不一样的，所以注意判断一下然后对以上操作左右翻转一下。

关于偶数的最优解是 $n^2-2$ 的证明，主播太菜了，只能给出一个较为模糊的证明：

假设填满，即答案为 $n^2$，因为判合法只需要放上去的时候攻击数是偶数即可，也就是需要保证最后放置的一个格子的攻击数是偶数。因为行和列的攻击数会抵消，所以只能看斜线，然而因为是偶数，所以无论你放在哪里斜线上的攻击数一定会是奇数，所以一定不合法，最后一个格子一定放不了。

假设只有一个不能填，即答案为 $n^2-1$，我们可以发现，如果想要放下第 $n^2-1$ 个棋子，那么就需要摆在最后一个空格的攻击路线上，说白了就是剩的两个格子要互相影响，但是 $n$ 是偶数，构造又是对称的，我们过程中互相影响的格子都是角上的啊！那直接有四个格子了也用不了，所以无法搞出这种情况，所以放不了。

然后就是 $n^2-2$ 了，都搜出来了，能不是真的吗？
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m; 
int main(){
	cin>>n;
	if(n<=2)cout<<"1\n1 1\n";
	else if(n%2==1){
		cout<<n*n<<"\n";
		m=n/2+1;
		for(int l=1,r=n;r-l+1>3;l++,r--){
			for(int i=1;l+i!=r-i;i++){
				cout<<l<<" "<<l+i<<"\n";
				cout<<l+i<<" "<<r<<"\n";
				cout<<r-i<<" "<<l<<"\n";
				cout<<r<<" "<<r-i<<"\n";
				int j=r-l-i;
				cout<<l<<" "<<l+j<<"\n";
				cout<<l+j<<" "<<r<<"\n";
				cout<<r-j<<" "<<l<<"\n";
				cout<<r<<" "<<r-j<<"\n";
			}
		}
		cout<<"1 1\n";
		for(int l=1,r=n;r-l+1>3;l++,r--){
			if(l%2==1){
				cout<<r<<" "<<m<<"\n";
				cout<<l<<" "<<m<<"\n";
				cout<<m<<" "<<r<<"\n";
				cout<<m<<" "<<l<<"\n";
				cout<<l+1<<" "<<r-1<<"\n";
				cout<<l<<" "<<r<<"\n";
				cout<<r<<" "<<r<<"\n";
				cout<<r<<" "<<l<<"\n";
			}
			else{
				cout<<r<<" "<<m<<"\n";
				cout<<l<<" "<<m<<"\n";
				cout<<m<<" "<<l<<"\n";
				cout<<m<<" "<<r<<"\n";
				cout<<l+1<<" "<<l+1<<"\n";
				cout<<l<<" "<<l<<"\n";
				cout<<r<<" "<<l<<"\n";
				cout<<r<<" "<<r<<"\n";
			}
		}
		if(n/2%2==0){
			cout<<m+1<<" "<<m<<"\n";
			cout<<m<<" "<<m<<"\n";
			cout<<m-1<<" "<<m-1<<"\n";
			cout<<m+1<<" "<<m+1<<"\n";
			cout<<m<<" "<<m+1<<"\n";
			cout<<m<<" "<<m-1<<"\n";
			cout<<m+1<<" "<<m-1<<"\n";
			cout<<m-1<<" "<<m<<"\n";
		}
		else{
			cout<<m+1<<" "<<m<<"\n";
			cout<<m<<" "<<m<<"\n";
			cout<<m-1<<" "<<m+1<<"\n";
			cout<<m+1<<" "<<m-1<<"\n";
			cout<<m<<" "<<m-1<<"\n";
			cout<<m<<" "<<m+1<<"\n";
			cout<<m+1<<" "<<m+1<<"\n";
			cout<<m-1<<" "<<m<<"\n";
		}
	}
	else{
		cout<<n*n-2<<"\n";
		m=n/2;
		for(int l=1,r=n;r-l+1>3;l++,r--){
			for(int i=1;l+i<r-i;i++){
				cout<<l<<" "<<l+i<<"\n";
				cout<<l+i<<" "<<r<<"\n";
				cout<<r-i<<" "<<l<<"\n";
				cout<<r<<" "<<r-i<<"\n";
				int j=r-l-i;
				cout<<l<<" "<<l+j<<"\n";
				cout<<l+j<<" "<<r<<"\n";
				cout<<r-j<<" "<<l<<"\n";
				cout<<r<<" "<<r-j<<"\n";
			}
		}
		cout<<"1 1\n";
		for(int l=1,r=n;r-l+1>4;l++,r--){
			if(l%2==1){
				cout<<l+1<<" "<<r-1<<"\n";
				cout<<l<<" "<<r<<"\n";
				cout<<r<<" "<<r<<"\n";
				cout<<r<<" "<<l<<"\n";
			}
			else{
				cout<<l+1<<" "<<l+1<<"\n";
				cout<<l<<" "<<l<<"\n";
				cout<<r<<" "<<l<<"\n";
				cout<<r<<" "<<r<<"\n";
			}
		}
		if(n/2%2==0){
			cout<<m<<" "<<m+1<<"\n";
			cout<<m<<" "<<m<<"\n";
			cout<<m+1<<" "<<m<<"\n";
			cout<<m+2<<" "<<m+2<<"\n";
			cout<<m+2<<" "<<m-1<<"\n";
		}
		else{
			cout<<m<<" "<<m<<"\n";
			cout<<m<<" "<<m+1<<"\n";
			cout<<m+1<<" "<<m+1<<"\n";
			cout<<m+2<<" "<<m-1<<"\n";
			cout<<m+2<<" "<<m+2<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：不知名用户 (赞：1)

### 题意

$n\times n$ 的棋盘，依次放置若干个王后，要求每个王后放上去后（不是最终）被偶数个王后攻击到。$n\le1024$。

### 做法

@thomaswmy 教我的。

打表发现 $n$ 为奇数时可以填满，偶数差 $2$ 个（$n=2$ 特殊，只能填 $1$ 个）。

考虑归纳构造，将 $n$ 归约到 $n-2$，发现不好构造外圈，所以考虑构造最后两行两列。发现除了那些位置的其余位置被偶数个王后攻击到（感觉一下，主对角线两个，副对角线没有/两个/四个，右下各两个）。所以不会影响更小的问题。

考虑构造，可以先构造出一个 $3\times3$ 的扣掉一个角，然后在两边填数。下面是一个可行的构造（方格内的数表示是第几个放的）：

| | $4$ | $7$ |
| :-----------: | :-----------: | :-----------: |
| $2$ | $5$ | $8$ |
| $6$ | $3$ | $1$ |

经观察，可以轮流操作左/上，每次填两个，且每次填的第一个位置是否靠边取决于次数的奇偶性，这样是可行的。说的有点不清楚，可以配合下面的 $5\times5$ 的构造理解：

| | | | $15$ | $16$ |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| | | | $12$ | $11$ |
| | | | $4$ | $7$ |
| $14$ | $9$ | $2$ | $5$ | $8$ |
| $13$ | $10$ | $6$ | $3$ | $1$ |

奇数可以直接归约到 $n=1$ 再填满，但是偶数有些特殊。如果直接归约到 $n=2$，会缺 $3$ 个，所以考虑在 $n=4$ 时特殊构造。下面是一种可行的构造：

| $1$ | $3$ | $6$ |  |
| :-----------: | :-----------: | :-----------: | :-----------: |
| $8$ | $5$ | $2$ | $14$ |
| $7$ | $4$ | $11$ | $10$ |
| $12$ | $9$ |  | $13$ |

时间复杂度 $\Theta(n^2)$。代码十分好写。关键是要弄出那两个表。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<pair<int,int> >ans;

void put(int a, int b){ans.emplace_back(a,b);}

void cons(int n)
{
	put(n,n), put(n-1,n-2), put(n,n-1), put(n-2,n-1), put(n-1,n-1), put(n,n-2), put(n-2,n), put(n-1,n);
	int i, a = 0;
	for(i=n-3;i>=1;i--)
	{
		if(!a) put(n-1,i), put(n,i), put(i,n), put(i,n-1);
		else put(n,i), put(n-1,i), put(i,n-1), put(i,n);
		a ^= 1;
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	if(n<=2) return printf("1\n1 1\n"), 0;
	if(n&1)
	{
		while(n>=3) cons(n), n -= 2;
		put(1,1);
	}
	else
	{
		while(n>=6) cons(n), n -= 2;
		put(1,1), put(2,3), put(1,2), put(3,2);
		put(2,2), put(1,3), put(3,1), put(2,1);
		put(4,2), put(3,4), put(3,3), put(4,1);
		put(4,4), put(2,4);
	}
	printf("%d\n", (int)ans.size());
	for(auto i:ans) printf("%d %d\n", i.first, i.second);
	return 0;
}
```

---

## 作者：drmr (赞：1)

赛时写挂了，写一发题解。

在 $N \times N$ 的网格上，第 $i$ 行 $j$ 列为 $(i, j)$。考虑如何将 $N$ 缩小到 $N - 2$ 是原问题的等价问题。

当 $N$ 为偶数，先考虑构造一个 $2 \times N$ 的条形。在最右侧按照顺序进行：

```chess
... 6 4 5 1
... 7 2 8 3
```

接下来填充省略号的部分：

```chess
A D ...
C B ...
```

接下来向下构造：

```chess
? ? ? ? ...
? ? ? ? ...
1 2
A C
D B
A C
D B
. .
. .
. .
A B
```

这样就构造完成了。给出 $N = 10$ 的构造顺序：

```chess
17 20 13 16 09 12 06 04 05 01
19 18 15 14 11 10 07 02 08 03
21 22
23 25
26 24
27 29
30 28
31 33
34 32
35 36
```

对于 $N$ 是奇数的情况基本相同，给出 $N = 11$ 时的构造：

```chess
22 17 20 13 16 09 12 06 04 05 01
24 19 18 15 14 11 10 07 02 08 03
21 26
23 25
30 28
27 29
34 32
31 33
38 36
35 37
40 39
```

对于 $N \le 4$ 直接特判即可。

代码写得很难看。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e6;
int n, tot, B;
pair<int, int> ans[N];

void f(int x, int y){
	ans[++tot] = make_pair(x + B, y + B);
	return ;
}

void solve(int n){
	if(n == 4){
		f(1, 2);
		f(3, 1);
		f(1, 3);
		f(2, 1);
		f(2, 4);
		f(4, 3);
		f(4, 2);
		f(3, 4);
		f(1, 1);
		f(2, 3);
		f(1, 4);
		f(4, 4);
		f(3, 2);
		f(2, 2);
		return ;
	}
	f(1, n);
	f(2, n - 2);
	f(2, n);
	f(1, n - 2);
	f(1, n - 1);
	f(1, n - 3);
	f(2, n - 3);
	f(2, n - 1);
	for(int i = n - 5; i >= 1; i -= 2){
		f(1, i);
		f(2, i + 1);
		f(2, i);
		f(1, i + 1);
	}
	f(3, 1);
	f(3, 2);
	for(int i = 4; i < n; i += 2){
		f(i, 1);
		f(i + 1, 2);
		f(i, 2);
		f(i + 1, 1);
	}
	f(n, 1);
	f(n, 2);
	B += 2;
	solve(n - 2);
	return ;
}

void solve2(int n){
	if(n == 3){
		f(2, 3);
		f(3, 1);
		f(2, 2);
		f(1, 1);
		f(3, 3);
		f(3, 2);
		f(1, 2);
		f(1, 3);
		f(2, 1);
		return ;
	}
	f(1, n);
	f(2, n - 2);
	f(2, n);
	f(1, n - 2);
	f(1, n - 1);
	f(1, n - 3);
	f(2, n - 3);
	f(2, n - 1);
	for(int i = n - 5; i >= 1; i -= 2){
		f(1, i);
		f(2, i + 1);
		f(2, i);
		f(1, i + 1);
	}
	f(3, 1);
	f(1, 1);
	f(4, 1);
	f(2, 1);
	f(4, 2);
	f(3, 2);
	for(int i = 5; i < n; i += 2){
		f(i + 1, 1);
		f(i, 2);
		f(i + 1, 2);
		f(i, 1);
	}
	f(n, 2);
	f(n, 1);
	B += 2;
	solve2(n - 2);
	return ;
}

signed main(){
	cin >> n;
	if(n == 2 || n == 1){
		cout << "1\n";
		cout << "1 1\n";
		return 0;
	}
	if(n % 2 == 0){
		solve(n);
		cout << tot << "\n";
		for(int i = 1; i <= tot; i++)
			cout << ans[i].first << " " << ans[i].second << "\n";
		return 0;
	}
	else{
		solve2(n);
		cout << tot << "\n";
		for(int i = 1; i <= tot; i++)
			cout << ans[i].first << " " << ans[i].second << "\n";
		return 0;
	}
	return 0;
}
```

---

## 作者：RainySoul (赞：0)

非常有趣，一般有趣的构造题我就认为它是个好题。推荐不要观看题解自己玩一会。

首先看到这个题容易想到如果最外层已经是一个圈了那么最外层会给里面的任何一个点在八个方向上各提供一个贡献，所以外部的点直接不需要考虑了，相当于你从 $n\times n$ 的递归到了一个 $(n-2) \times (n-2)$ 的小问题。

然后考虑能否填出外围一圈。发现填到还剩三个角的时候有点填不动了。

```
0110
1001
1001
1110
```

此时尝试动一个里面的点。这个时候你只需要考虑里面小矩阵的四个角就可以了，不然对于现在空出来的大矩阵的三个角没有任何贡献。然后手模一下这四种情况，发现有成立的：

```
0110 --> 0110 --> 0110 --> 0111 --> 1111
1001 --> 1001 --> 1001 --> 1001 --> 1001
1001 --> 1011 --> 1011 --> 1011 --> 1011
1110 --> 1110 --> 1111 --> 1111 --> 1111
```

而动小矩阵的一角这完全没有问题，相当于你每次构造外面一个圈的时候从这个圈的一角开始构造，这是能够做到的。我们有从左下角开始，先将右边下边填完，再填左边上边的神秘构造。

拿 $4\times 4$ 的举例，开始两步你将矩阵填成这个样子：

```
0000-->0000
0000-->0000
0000-->0001
1000-->1000
```

然后你最后一行从右到左，最后一列从下往上两个两个交替着填就可以了。like this：

```
0000-->0000-->0000-->0000
0000-->0000-->0000-->0001
0001-->0001-->0001-->0001
1000-->1010-->1110-->1110
```

这样做为什么是对的？当一个格子对角线上有点的时候当前行或列中只有奇数个点，而当对角线上没有点的时候当前行或列中恰有偶数个点。第一列与第一行也是相同的办法，由于你已经将最后一行与最后一列填好了，而这两个部分一定会给第一行任意点提供恰好 $2$ 的贡献，给第一列任意点提供恰好 $3$ 的贡献。然后简单了。

```
0000-->0100-->0100-->0100-->0110
0001-->0001-->1001-->1001-->1001
0001-->0001-->0001-->1001-->1001
1110-->1110-->1110-->1110-->1110
```

然后就是 $n$ 往 $n-2$ 递归了。奇数时显然递归到 $n\le 3$ 之后可以直接填满不可能有更优的了。

```
000-->000-->000-->000-->000-->000-->100-->110-->111-->111
000-->000-->001-->101-->101-->111-->111-->111-->111-->111
000-->100-->100-->100-->101-->101-->101-->101-->101-->111
```

但是你发现一个诡异的事情：按照这个做法从 $4\times 4$ 递归到 $2\times 2$ 之后，$2\times 2$ 中明显会空出来 $3$ 个格子，手玩时却发现 $4\times 4$ 可以填到只空 $2$ 个格子，难道我们打假算了？但是它看起来真的很对啊。其实这个好办，反正你外围都是填满的，直接递归到 $n\le 4$ 的时候判掉即可。

随便玩一下填出来剩两个：

```
0110-->0110-->0110-->0110-->0111-->0111
1001-->1001-->1001-->1101-->1101-->1101
1001-->1011-->1111-->1111-->1111-->1111
1110-->1110-->1110-->1110-->1110-->1111
```

然后我们来证明一下为什么答案上界是 $n^2-2$：考虑记 $sum$ 为“当前能够相互攻击的皇后有多少对”，容易想到加入一个点这个 $sum$ 必定增加一个偶数，所以任意时刻合法的 $sum$ 一定为偶数。考虑一个满的棋盘，因为每个点贡献均为奇数，所以 $sum$ 为偶数，而最后一步增加的贡献一定是奇数，这就说明在 $n^2-1$ 的时候 $sum$ 为奇数，与前面推出的 $sum$ 为偶数冲突，说明 $n^2-1$ 并不是可达状态。

注意大矩阵递归到小矩阵是左右翻转的。

代码挺好写，还没调就一遍过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
struct zyx{
    int x,y;
};
vector<zyx> ans3,ans4;

void solve(int x,int n,int flag){
    if(n<=4){
        if(n==4){
            if(flag==0){
                for(int i=1;i<(int)ans4.size();i++)
                    cout<<x+ans4[i].x<<" "<<x+ans4[i].y<<'\n';
            }
            else{
                for(int i=1;i<(int)ans4.size();i++)
                    cout<<x+ans4[i].x<<" "<<x+n-ans4[i].y+1<<'\n';
            }
        }
        else if(n==3){
            if(flag==0){
                for(int i=1;i<(int)ans3.size();i++)
                    cout<<x+ans3[i].x<<" "<<x+ans3[i].y<<'\n';
            }
            else{
                for(int i=1;i<(int)ans3.size();i++)
                    cout<<x+ans3[i].x<<" "<<x+n-ans3[i].y+1<<'\n';
            }
        }
        return;
    }
    else{
        vector<zyx> temp;
        temp.clear();
        temp.push_back((zyx){n-1,n});
        int hang=n-1,lie=n-2,f=0;
        while(hang>1||lie>1){
            if(f==0){
                if(hang>2){
                    temp.push_back((zyx){n,hang});
                    temp.push_back((zyx){n,hang-1});
                    hang-=2;
                }
                else if(hang==2){
                    temp.push_back((zyx){n,hang});
                    hang--;
                }
            }
            else{
                if(lie>2){
                    temp.push_back((zyx){lie,n});
                    temp.push_back((zyx){lie-1,n});
                    lie-=2;
                }
                else if(lie==2){
                    temp.push_back((zyx){lie,n});
                    lie--;
                }
            }
            f=1-f;
        }
        temp.push_back((zyx){1,2});
        hang=3,lie=2,f=0;
        while(hang<n||lie<n){
            if(f==0){
                if(lie<n-1){
                    temp.push_back((zyx){lie,1});
                    temp.push_back((zyx){lie+1,1});
                    lie+=2;
                }
                else if(lie==n-1){
                    temp.push_back((zyx){lie,1});
                    lie++;
                }
            }
            else{
                if(hang<n-1){
                    temp.push_back((zyx){1,hang});
                    temp.push_back((zyx){1,hang+1});
                    hang+=2;
                }
                else if(hang==n-1){
                    temp.push_back((zyx){1,hang});
                    hang++;
                }
            }
            f=1-f;
        }
        temp.push_back((zyx){n-1,n-1});
        temp.push_back((zyx){n,n});
        temp.push_back((zyx){1,n});
        temp.push_back((zyx){1,1});
        if(flag==0){
            for(int i=0;i<(int)temp.size();i++)
                cout<<x+temp[i].x<<" "<<x+temp[i].y<<'\n';
        }
        else{
            for(int i=0;i<(int)temp.size();i++)
                cout<<x+temp[i].x<<" "<<x+n-temp[i].y+1<<'\n';
        }
        solve(x+1,n-2,1-flag);
    }
}
void init(){
    ans4.push_back((zyx){4,1});
    ans4.push_back((zyx){3,4});
    ans4.push_back((zyx){4,3});
    ans4.push_back((zyx){4,2});
    ans4.push_back((zyx){2,4});
    ans4.push_back((zyx){1,2});
    ans4.push_back((zyx){2,1});
    ans4.push_back((zyx){3,1});
    ans4.push_back((zyx){1,3});
    ans4.push_back((zyx){3,3});
    ans4.push_back((zyx){3,2});
    ans4.push_back((zyx){2,2});
    ans4.push_back((zyx){1,4});
    ans4.push_back((zyx){4,4});

    ans3.push_back((zyx){3,1});
    ans3.push_back((zyx){2,3});
    ans3.push_back((zyx){2,1});
    ans3.push_back((zyx){3,3});
    ans3.push_back((zyx){2,2});
    ans3.push_back((zyx){1,1});
    ans3.push_back((zyx){1,2});
    ans3.push_back((zyx){1,3});
    ans3.push_back((zyx){3,2});
}
int main(){
    int n=read();
    init();
    if(n<=4){
        if(n==4){
            cout<<14<<'\n';
            for(int i=0;i<(int)ans4.size();i++)
                cout<<ans4[i].x<<" "<<ans4[i].y<<'\n';
        }
        else if(n==3){
            cout<<9<<'\n';
            for(int i=0;i<(int)ans3.size();i++)
                cout<<ans3[i].x<<" "<<ans3[i].y<<'\n';
        }
        else if(n==2){
            cout<<1<<'\n';
            cout<<1<<" "<<1;
        }
        else if(n==1){
            cout<<1<<'\n';
            cout<<1<<" "<<1;
        }
        return 0;
    }
    if(n%2)cout<<n*n<<'\n';
    else cout<<n*n-2<<'\n';
    cout<<n<<" "<<1<<'\n';
    solve(0,n,0);
    return 0;
}
```

闲话：哦现在主题库口糊题解居然不能交了，痛苦面具。

---

## 作者：Union_of_Britain (赞：0)

野蛮题目，下次别出了，，，

经过手玩，奇数猜测是 $n^2$，偶数是 $n^2-2$（显然这是一个上界）。还可以发现在 $n$ 小的时候（大的没试过）相当程度地乱放就可以达到这个上界，所以题目留给我们构造的空间非常宽松。

奇数一个想法是 $n\to n+2$，可以如下构造（图为 $n=3$）：

![](https://cdn.luogu.com.cn/upload/image_hosting/4lcrgz8j.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

从两边没填的两行每次移动两格走到中心，每次调换先左/先右（先上/先下），最终剩下的 $3\times 3$ 涂了左上角图形，此时除了这个左上角的已涂色格子加起来没有影响；随便构造（例如代码中 `COL`）一个方案。

偶数的一种较有规律的填法是在中间四个格子选一个填（如果 $n=6$ 特殊处理，$n\equiv 0\pmod 4$ 则取 $(n/2+1,n/2+1)$ 否则 $(n/2,n/2)$）再从右下角填到选择格子的行列，每次把最右列最下行填了，然后递归到子问题。

每次填涂最右列最下行的方法是每次尽量选更靠近右下角的，懒得证明，反正这样确实是可以填完并且 AC 的。

应该是 $O(n^3)$ 但是出题人素质高开 $2^{10}$ 所以就通过了，，，

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1050;
int n,a[1050][1050];
int b[maxn],c[maxn],d[maxn*10],e[maxn*10],B=maxn*5;
inline void Pt(int x,int y){
	cout<<x<<" "<<y<<endl;
	if(n%2==0){
		a[x][y]=2;
		b[x]^=1,c[y]^=1,d[x+y+B]^=1,e[x-y+B]^=1;
	}
}
inline void COL(int x,int y){
	Pt(x+1,y+2);
	Pt(x+2,y+2);
	Pt(x+2,y+1);
	Pt(x+1,y+1);
	Pt(x+2,y);
	Pt(x,y+1);
	Pt(x,y+2);
	Pt(x+1,y);
}
inline void F(int n){
	if(n==4){
		if(a[4][4]!=2)Pt(4,4);
		Pt(2,3);Pt(3,4);Pt(4,1);Pt(4,3);
		Pt(1,4);Pt(2,4);Pt(4,2);Pt(3,3);
		Pt(3,1);Pt(1,2);Pt(2,1);Pt(2,2);
		Pt(1,1);
		return ;
	}
	if(n%4==0){
		Pt(n/2+1,n/2+1);
		for(int i=n;i>n/2;i--){
			for(int j=1;j<=2*i-1-(i==n/2+1);j++){
				int x=-1,y;
				for(int k=i;k>=1;k--){
					if(a[k][i]==0&&(b[k]^c[i]^d[k+i+B]^e[k-i+B])==0){x=k,y=i;break;}
					if(a[i][k]==0&&(b[i]^c[k]^d[k+i+B]^e[i-k+B])==0){x=i,y=k;break;}
				}	
				if(x==-1)exit(2);
				Pt(x,y);
			}
		}
		F(n/2);
	}else if(n!=6){
		Pt(n/2,n/2);
		for(int i=n;i>=n/2;i--){
			for(int j=1;j<=2*i-1-(i==n/2);j++){
				int x=-1,y;
				for(int k=i;k>=1;k--){
					if(a[k][i]==0&&(b[k]^c[i]^d[k+i+B]^e[k-i+B])==0){x=k,y=i;break;}
					if(a[i][k]==0&&(b[i]^c[k]^d[k+i+B]^e[i-k+B])==0){x=i,y=k;break;}
				}	
				Pt(x,y);
			}
		}
		F(n/2-1);
	}else{
		Pt(n/2+1,n/2+1);
		for(int i=n;i>n/2+1;i--){
			for(int j=1;j<=2*i-1;j++){
				int x=-1,y;
				for(int k=i;k>=1;k--){
					if(a[k][i]==0&&(b[k]^c[i]^d[k+i+B]^e[k-i+B])==0){x=k,y=i;break;}
					if(a[i][k]==0&&(b[i]^c[k]^d[k+i+B]^e[i-k+B])==0){x=i,y=k;break;}
				}	
				Pt(x,y);
			}
		}
		F(4);
	}
}
signed main(){
	cin>>n;
	if(n&1){
		cout<<n*n<<endl;
		Pt(1,1);
		for(int i=1;i<n;i+=2){
			int cur=0;
			for(int j=1;j<=i-1;j++){
				if(cur){
					Pt(j,i+1);Pt(j,i+2);Pt(i+2,j);Pt(i+1,j);
				}else{
					Pt(j,i+2);Pt(j,i+1);Pt(i+1,j);Pt(i+2,j);
				}
				cur^=1;
			}
			COL(i,i);
		}
	}else{
		if(n==2){
			cout<<1<<endl<<1<<" "<<1<<endl;
			return 0;
		}
		cout<<n*n-2<<endl;		
		F(n);
	}
	return 0;
}
```

---

