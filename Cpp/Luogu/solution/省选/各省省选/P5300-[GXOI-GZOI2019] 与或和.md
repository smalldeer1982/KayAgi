# [GXOI/GZOI2019] 与或和

## 题目描述

Freda 学习了位运算和矩阵以后，决定对这种简洁而优美的运算，以及蕴含深邃空间的结构进行更加深入的研究。

对于一个由非负整数构成的矩阵，她定义矩阵的 $\texttt{AND}$ 值为矩阵中所有数二进制 $\texttt{AND(\&)}$ 的运算结果；定义矩阵的 $\texttt{OR}$ 值为矩阵中所有数二进制 $\texttt{OR(|)}$ 的运算结果。

给定一个 $N \times N$ 的矩阵，她希望求出：
1. 该矩阵的所有子矩阵的 $\texttt{AND}$ 值之和（所有子矩阵 $\texttt{AND}$ 值相加的结果）。
2. 该矩阵的所有子矩阵的 $\texttt{OR}$ 值之和（所有子矩阵 $\texttt{OR}$ 值相加的结果）。

接下来的剧情你应该已经猜到——Freda 并不想花费时间解决如此简单的问题，所以这个问题就交给你了。

由于答案可能非常的大，你只需要输出答案对 $1,000,000,007 (10^9 + 7)$ 取模后的结果。

## 说明/提示

### 样例1解释

该 $3 \times 3$ 矩阵共有 $9$ 个 $1 \times 1$ 子矩阵、$6$ 个 $1 \times 2$ 子矩阵、$6$ 个 $2 \times 1$ 子矩阵、$4$ 个 $2 \times 2$ 子矩阵、3 个 $1 \times 3$ 子矩阵、$3$ 个 $3 \times 1$ 子矩阵、$2$ 个 $2 \times 3$ 子矩阵、$2$ 个 $3 \times 2$ 子矩阵和 $1$ 个 $3 \times 3$ 子矩阵。  
只有一个子矩阵（仅由第一行第一列的那个元素构成的 $1 \times 1$ 矩阵）$\texttt{AND}$ 值为 $1$，其余子矩阵的 $\texttt{AND}$ 值均为 $0$，总和为 $1$。  
包含第一行第一列那个元素的子矩阵有 $9$ 个，它们的 $\texttt{OR}$ 值为 $1$，其余子矩阵的 $\texttt{OR}$ 值为 $0$，总和为 $9$。

### 数据范围

|测试点编号|$n$ 的规模|矩阵中的自然数|
|:-:|:-:|:-:|
|$1$|$1 \le n \le 10$|$\le 100$|
|$2$|$1 \le n \le 10$|$\le 100$|
|$3$|$1 \le n \le 100$|$\le 100$|
|$4$|$1 \le n \le 100$|$\le 100$|
|$5$|$1 \le n \le 100$|$\le 100$|
|$6$|$1 \le n \le 1,000$|$\le 2^{31} - 1$|
|$7$|$1 \le n \le 1,000$|$\le 2^{31} - 1$|
|$8$|$1 \le n \le 1,000$|$\le 2^{31} - 1$|
|$9$|$1 \le n \le 1,000$|$\le 2^{31} - 1$|
|$10$|$1 \le n \le 1,000$|$\le 2^{31} - 1$|

另外有一组不计分的 hack 数据，放在 subtask 1 中，数据范围与测试点 $6 \sim 10$ 一致。

## 样例 #1

### 输入

```
3
1 0 0
0 0 0
0 0 0```

### 输出

```
1 9```

## 样例 #2

### 输入

```
3
1 2 3
4 5 6
7 8 9```

### 输出

```
73 314```

# 题解

## 作者：冒泡ioa (赞：12)

>[更啰嗦的题解](http://bubbleioa.top/archives/828)


## 题解


由于与运算和或运算在每一位上都是独立的，我们可以考虑对每一位进行计算。

我们先考虑与运算（其实两个运算是一样的）  
于是就成了一个求一个矩阵中，有多少个0/1子矩阵，我们可以考虑用单调栈做。

有一个显然的结论

> 在一个 $N\times M$ 的矩阵中，以(n,m)为右下角的子矩阵共有 $N\times M$ 个

具体来讲，我们要求出一个s二维数组，s[i][j]表示(i,j)点上方有多少个连续的1，$O(N^2)$预处理

枚举每一个点，我们来计算**以它为右下角**的子矩阵个数
对于一般情况，在2处，A区域就没有意义，4处，B区域就没有意义
![](https://cdn.luogu.com.cn/upload/pic/56750.png)
所以我们要维护一个单调栈，栈中元素k要满足s[i][k]单调递增（栈顶s[i][k]最大）

每次有元素出栈时，说明有部分答案不能产生贡献，见代码注释

对于或运算，求所有0子矩阵，全集-0子矩阵数目即是贡献。

直接复制这个代码会T  
ch上这样是过得了的，但是luogu上你需要加一个快读

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=2003,mod=1e9+7;
int ma[MAXN][MAXN];
int s[MAXN][MAXN];
int stk[MAXN],top;
int n;
ll ans1,ans2;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&ma[i][j]);
		}
	}
	for(int k=0;k<31;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if((ma[i][j]>>k)&1)s[i][j]=s[i-1][j]+1;
				else s[i][j]=0;
			}
		}
		for(int i=1;i<=n;i++){
			ll ans=0;top=0;
			for(int j=1;j<=n;j++){
				ans+=s[i][j];
				while(top&&s[i][stk[top]]>=s[i][j]){
					ans-=(stk[top]-stk[top-1])*(s[i][stk[top]]-s[i][j]);
					//栈顶对于第二大的元素的距离×栈顶与j的落差，即为上图中j=3时灰色线的上半部分
					top--;
				}
				ans1+=ans<<k;
				ans1%=mod;
				stk[++top]=j;
			}
		}
	}
	cout<<ans1<<" ";
	for(int k=0;k<31;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if((ma[i][j]>>k)&1)s[i][j]=0;
				else s[i][j]=s[i-1][j]+1;
			}
		}
		for(int i=1;i<=n;i++){
			ll ans=0;top=0;
			for(int j=1;j<=n;j++){
				ans+=s[i][j];
				while(top&&s[i][stk[top]]>=s[i][j]){
					ans-=(stk[top]-stk[top-1])*(s[i][stk[top]]-s[i][j]);
					top--;
				}
				ans2+=(i*j-ans)<<k;
				ans2%=mod;
				stk[++top]=j;
			}
		}
	}
	cout<<ans2<<endl;
		
	return 0;
}
```


---

## 作者：szm_ (赞：9)

~~测试一开始看错题目敲了两小时，发现是个水题~~

---
目前是洛咕rk1 ~~（开了O2的那种）~~  

做法较为玄学，没有单调栈 ~~因为不会~~  

---
首先把 $ and $ 转化成 $ or $ ，这样我们只需要写半道题了  


显然对于某一二进制位,我们需要求出此位 $ or $ 和为 $ 1 $ 的子矩阵个数。  

枚举每一个位置作为右下角，记 $ s_i $ 为到当前行为止，当前位为 $ 1 $ 的数最后出现时的所在行。那么通过画图可知，这一位作为右下角的贡献就是以当前列作为右端点作后缀 $ Max $ ，再把后缀 $ Max $ 加起来的和。  

因为后缀 $ Max $ 是单调的，而且每次修改只有一种操作：把某个位置（此位为 $ 1 $）改成最大值（当前行号）。那么对于每个位置记 $ Pre_i $ ，表示在他之前最后一个比他大的，可以发现每个位置后缀最大值和可以用这个 $ Pre $ 求出。考虑一次修改的影响，我们只要扫一遍，记下最后一个改成最大值的位置，再和当前位的 $ Pre $ 取最大就可以了。  

时间效率 $ O(n^2log) $  

~~而且代码很短的就0.7k~~


```cpp
#include<cstdio>
#define L long long
const L p=1e9+7,N=1002,u=(1ll<<31)-1;
L n,a[N][N],s[N],v[N],r[N],A,O;
inline L S(L k) {
	L c=0;for(L j=1;j<=n;j++) s[j]=r[j]=0;
	for(L i=1;i<=n;i++)
		for(L j=1,w=0;j<=n;j++) {
			if(a[i][j]>>k&1) s[j]=i,r[w=j]=0;
			else if(w>r[j]) r[j]=w;
			v[j]=v[r[j]]+s[j]*(j-r[j]);
			c+=v[j];if(c>=p) c-=p;
		}return c*(1ll<<k)%p;
}
int main() {
	scanf("%lld",&n);
	for(L i=1;i<=n;i++) for(L j=1;j<=n;j++)
		scanf("%lld",&a[i][j]);
	for(L i=0;i<=30;i++) if((O+=S(i))>=p) O-=p;
	for(L i=1;i<=n;i++) for(L j=1;j<=n;j++) {
		a[i][j]^=u;if((A+=i*j*u%p)>=p) A-=p;
	}
	for(L i=0;i<=30;i++) if((A-=S(i))<0) A+=p;
return printf("%lld %lld\n",A,O),0;}
```


---

## 作者：xht (赞：7)

题目地址：[P5300 [GXOI/GZOI2019]与或和](https://www.luogu.org/problemnew/show/P5300)

考虑按位计算贡献

对于 **AND** 运算，只有全 $1$ 子矩阵才会有贡献

对于 **OR** 运算，所以非全 $0$ 子矩阵均有贡献

如果求一个 **01** 矩阵中全 $0/1$ 子矩阵的个数呢？

单调栈可以 $O(n^2)$ 实现

总时间复杂度 $O(n^2k)$ 其中 $k$ 是二进制位数

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e3 + 6, P = 1e9 + 7;
int n, a[N][N], h[N], s[N], w[N], p;
ll ans[2];

inline ll get(int x) {
	return (1ll * x * (x + 1)) >> 1;
}

inline ll calc(int o) {
	ll cnt = 0;
	for (int j = 1; j <= n; j++) h[j] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if ((a[i][j] & 1) == o) ++h[j];
			else h[j] = 0;
			if (h[j] > s[p]) s[++p] = h[j], w[p] = 1;
			else {
				int k = 0;
				while (s[p] > h[j]) {
					k += w[p];
					cnt += (s[p] - max(s[p-1], h[j])) * get(k);
					--p;
				}
				s[++p] = h[j], w[p] = k + 1;
			}
		}
		int k = 0;
		while (p) {
			k += w[p];
			cnt += (s[p] - s[p-1]) * (get(k));
			--p;
		}
	}
	return cnt % P;
}

void work(int o) {
	if (o == 32) return;
	ans[0] += calc(1) * (1 << o) % P, ans[0] %= P;
	ans[1] += (get(n) * get(n) % P - calc(0)) * (1 << o) % P, ans[1] %= P;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			a[i][j] >>= 1;
	work(o + 1);
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &a[i][j]);
	work(0);
	cout << (ans[0] + P) % P << " " << (ans[1] + P) % P << endl;
	return 0;
}
```

---

## 作者：liugh_ (赞：6)

[P5300 [GXOI/GZOI2019] 与或和](https://www.luogu.com.cn/problem/P5300)

考虑按位拆分。先讨论 $\text{AND}$ 值，一个子矩阵有贡献当且仅当该子矩阵内所有数全为 $1$。问题转化为全1子矩阵计数。我们可以分别计算以每一行为底向上增长的子矩阵的贡献，这样既不会多算，也不会漏算。如
$$
\begin{aligned}
&a &b \\
&c &d \\
\end{aligned}
$$
- 计算以第 $1$ 行为底的子矩阵。
  - 算当前行，分别是 $\{a\},\{b\},\{a,b\}$。
  - 共 $3$ 个。
- 计算以第 $2$ 行为底的子矩阵。
  - 先算当前行，共 $3$ 个，分别是 $\{c\},\{d\},\{c,d\}$。
  - 然后以当前行为底向上增长，共 $3$ 个，分别是 $\{a,c\},\{b,d\},\{a,b,c,d\}$。
  - 共 $6$ 个。

如何求以某一行为底其内部全为 $1$ 的子矩阵个数？考虑记录以当前行为底向上连续的 $1$ 的个数，并转化为直方图以便考虑贡献。

记列 $i$ 的高度为 $h_i$，记当前列位置为 $u$，记左边第一个高度不超过其的列的位置为 $l$，记右边第一个高度不超过其的列的位置为 $r$，则我们仅需计算高度大于 $\max\{h_l,h_r\}$ 的子矩阵。单调栈维护，单次时间复杂度 $\Theta(n)$。

举例部分，如 $[3,4,1,1]$：
$$
\begin{aligned}
&\ \ \ O \\
&O O \\
&O O \\
&O O O  O  \\
&1 \ 2 \ 3 \ 4 \\
\end{aligned}
$$
到 $3$，此时栈是空的，可以直接入栈。
$$
\begin{aligned}
&\\
&O \\
&O \\
&O \\
&1 \\
\end{aligned}
$$
到 $4$，此时栈顶是 $3$，比 $4$ 小，可以直接入栈。
$$
\begin{aligned}
&\ \ \ O \\
&O O \\
&O O \\
&O O \\
&1 \ 2
\end{aligned}
$$
到 $1$，此时栈顶是 $4$，比 $1$ 大，需要出栈，此时计算 $4$ 的贡献：

- 仅需计算 $4$ 高出来的部分，此时 $l=1,r=3$，它高出左右两边的那一部分 $h=4-\max\{1,3\}=1$，记 $w=r-l-1=1$，则共有 $hw(w+1)/ 2=1$ 个子矩阵。

$$
\begin{aligned}
&\ \ \ \textcolor{red}O \\
&O \textcolor{green}O \\
&O \textcolor{green}O \ \\
&O \textcolor{green}O O \\
&1 \ 2 \ 3 \\
\end{aligned}
$$

还是 $1$，此时栈顶是 $3$，比 $1$ 大，需要出栈，此时计算 $3$ 的贡献：

- $3$ 高出来的那部分与 $4$ 刚才没有计算的部分**重合**了。此时 $l=0,r=3$，它高出左右两边的那部分 $h=3-\max\{0,1\}=2$，记 $w=r-l-1=2$，则共有 $hw(w+1)/2=6$ 个子矩阵。

$$
\begin{aligned}
&\ 	  & &\ \ \ \textcolor{grey}O \\
&\textcolor{red}O    & &\textcolor{red}O \textcolor{orange}O \\
&\textcolor{red}O  & &\textcolor{red}O \textcolor{orange}O \ \\
&\textcolor{green}O  O & &\textcolor{green}O \textcolor{grey}O O \\
&1 \ 3 \             & &1 \ 2 \ 3
\end{aligned}
$$

到下一个 $1$，此时栈顶是 $1$，等于 $1$，需要出栈，此时计算 $1$ 的贡献：

- 此时 $1$ **没有**高出来的部分，但由于我们计算 $h=1-\max\{0,1\}=0$，故 $hw(w+1)/2=0$，不影响答案。

$$
\begin{aligned}
& \\
& \\
& \\
&\textcolor{green}O O\\
&3 \ 4\\
\end{aligned}
$$

已经扫完一遍直方图，但还需将栈弹空：

- 此时栈中除栈顶外无剩余的元素，说明这一行内所有数都不小于栈顶 $1$，即 $l=0,r=n+1=5$，$h=1-\max\{0,0\}=1$，记 $w=r-l-1=n=4$，则共有 $hw(w+1)/2=10$ 个子矩阵。

$$
\begin{aligned}
& \\
& \\
& \\
&\textcolor{red}O\\
&4\\
\end{aligned}
$$

把所有 $h$ 相加，就能得到**以当前行为底**全1子矩阵的数量 $17$。外层枚举每一行，总时间复杂度 $\Theta(n^2)$。由于是按位操作，记得每一位的总贡献应当乘上该位的位权。

再考虑 $\text{OR}$ 值，一个子矩阵有贡献当且仅当该子矩阵内有**至少** $1$ 个 $1$。不好维护，正难则反，考虑子矩阵没有贡献当且仅当该子矩阵内全为 $0$，同上即可。

```cpp
int calc() {
	top = 0;
	int ret = 0;
	for(int i = 1; i <= n; ++i) {
		while(top and hei[sta[top]] >= hei[i]) {
			int u = sta[top--];
			int l = top ? sta[top] : 0;
			int r = i;
			int w = (r - 1) - (l + 1) + 1;
			int h = hei[u] - max(hei[l], hei[r]);
			ret = (ret + (w * (w + 1) / 2) * h % MOD) % MOD;
		}
		sta[++top] = i;
	}
	while(top) {
		int u = sta[top--];
		int l = top ? sta[top] : 0;
		int r = n + 1;
		int w = (r - 1) - (l + 1) + 1;
		int h = hei[u] - hei[l];
		ret = (ret + (w * (w + 1) / 2) * h % MOD) % MOD;
	}
	return ret % MOD;
}
void work(int bit) {
	if(bit >= 32) return;

	int ans = 0;
	for(int i = 1; i <= n; ++i) hei[i] = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if((a[i][j] & 1) == 1) hei[j]++;
			else hei[j] = 0;
		}
		ans += calc();
	}
	AND = (AND + ans % MOD * (1 << bit) % MOD) % MOD;

	ans = 0;
	for(int i = 1; i <= n; ++i) hei[i] = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			if((a[i][j] & 1) == 0) hei[j]++;
			else hei[j] = 0;
		}
		ans += calc();
	}
	OR = (OR + (sqr(n * (n + 1) / 2) - ans) % MOD * (1 << bit) % MOD) % MOD;

	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= n; ++j) 
			a[i][j] >>= 1;
	work(bit + 1);
}
// work(0);
```

---

## 作者：mygr (赞：3)

原题链接：[P5300 [GXOI/GZOI2019] 与或和](https://www.luogu.com.cn/problem/P5300)

仔细观察题目，我们发现，对于每矩阵而言，矩阵与运算和或运算的贡献其实可以拆分为矩阵中每一位数的与和或的答案乘上当前位数的和。

证明：对于一个矩阵而言，对矩阵中的每一位数进行二进制拆分，若对于同一位数而言，矩阵中的每个数的那一位都为 1，则这个矩阵的与运算的结果中这一位的值一定为 1，若矩阵中的每个数中至少一个数的那一位为 1，则这个矩阵的或运算的结果中这一位的值一定为 1。

于是乎，题目就转化为了 “给定  $\log$  组数据，每次给出一个矩阵，矩阵中的数只有 0 和 1，求每个子矩阵的与运算和或运算的和”。

因为矩阵中只有 0 和 1，容易得出一个等式

$$tot=cnt_0+cnt_{or}$$

其中，$tot$ 表示所有子矩阵的数量，$cnt_0$ 表示子矩阵中全为 0 的矩阵数量，$cnt_{or}$ 表示矩阵或的答案为 1 的子矩阵数量。

所以得

$$cnt_{or}=tot-cnt_0$$

所有子矩阵的数量显然可以预处理得到，因此，我们只需要知道子矩阵中全为 0 的矩阵数量和全为 1 的矩阵数量即可统计答案，这两种矩阵显然可以使用同一种方式统计

为了方便，我们接下来只讨论统计全为 1 的情况。

统计每个点自往下总共有多少个 1。

考虑枚举矩阵的左上角，若一个点往下的 1 的数量比一个点左侧往下的 1 的数量多，那么这个点在左侧高度以下的部分一定取不到，换言之，右下角能取到的位置一定是自下往上全为 1 的单调不增子序列的和，可以用单调栈维护。

细节看代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int Max=1005,Mod=1e9+7;
int num[Max][Max],tot1[Max][Max],tot0[Max][Max];
int n,maxnum=0;
ll ans0,ans1,tot;
int read()
{
	int w=0;
	char c;
	c=getchar();
	while(c<'0' or '9'<c)c=getchar();
	while('0'<=c and c<='9')
	{
		w=w*10+c-'0';
		c=getchar();
	
	}
	return w;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			tot=(tot+((n-j+1)*(n-i+1))%Mod)%Mod;
			num[j][i]=read();
			maxnum=max(maxnum,num[j][i]);
		}
	int now=1;
	for(;maxnum;maxnum>>=1,now<<=1)
	{
		ll totans1=0,totans0=0;
		for(int i=n;i>=1;i--)
		{
			stack<pair<int,int> > t0,t1;//num,len
			ll fin1=0,fin0=0;
			for(int j=n;j>=1;j--)
			{
				if(num[j][i]&1)
				{
					tot1[j][i]=tot1[j][i+1]+1;
					tot0[j][i]=0;
				}
				else
				{
					tot0[j][i]=tot0[j][i+1]+1;
					tot1[j][i]=0;
				}
				
				
				int len=1;
				while(!t1.empty() and t1.top().first>tot1[j][i])
				{
					len+=t1.top().second;
					fin1-=t1.top().first*t1.top().second;
					t1.pop();
				}
				fin1+=len*tot1[j][i];
				totans1=(totans1+fin1)%Mod;
				t1.push(make_pair(tot1[j][i],len));
				
				
				len=1;
				while(!t0.empty() and t0.top().first>tot0[j][i])
				{
					len+=t0.top().second;
					fin0-=t0.top().first*t0.top().second;
					t0.pop();
				}
				fin0+=len*tot0[j][i];
				totans0=(totans0+fin0)%Mod;
				t0.push(make_pair(tot0[j][i],len));
				
				
				num[j][i]>>=1;
			}
		}
		ans1=(ans1+(totans1*now)%Mod)%Mod;
		ans0=(ans0+((tot-totans0+Mod)%Mod)*now)%Mod;
	}
	printf("%lld %lld",ans1%Mod,ans0%Mod);
}
```


---

## 作者：I_am_Accepted (赞：2)

### Analysis

首先二进制每一位分开考虑贡献，若以 $\mathtt{AND}$ 值之和为例，则问题转化成：

**给定一个 $n\times n$ 的 $01$ 矩阵，求全 $1$ 子矩阵的个数。**

这个问题可以线性，用单调栈解决。

即转化成过于简单的直方图求子矩阵个数问题。

这里再说明一下具体过程。

枚举该子矩阵的下边高度，在这条上记录向上连续的 $1$ 的个数。然后从左往右维护单调栈即可。再具体可看 Code 中 `work()` 的部分。

总体时间 $O(31n^2)$

### Code

注意代码中求的是全 $0$ 子矩阵。

```cpp
//Said no more counting dollars. We'll be counting stars.
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")//DONT use rashly,I have suffered
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")//DONT use rashly,I have suffered
#include<bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define fir first
#define sec second
#define mkp make_pair
#define pb emplace_back
#define mem(x,y) memset(x,y,sizeof(x))
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define Fe(x,y) for(int x=head[y];x;x=e[x].nxt)
#define ckmx(a,b) a=max(a,b)
#define ckmn(a,b) a=min(a,b)
#define fin(s) freopen(s,"r",stdin)
#define fout(s) freopen(s,"w",stdout)
#define file(s) fin(s".in");fout(s".out")
#define cerr cerr<<'_'
#define debug cerr<<"Passed line #"<<__LINE__<<endl
template<typename T>T ov(T x){cerr<<"Value: "<<x<<endl;return x;}
#define ll long long
const ll mod=1000000007;
inline ll pw(ll x,ll y){ll r=1;while(y){if(y&1)r=r*x%mod;x=x*x%mod;y>>=1;}return r;}
inline void mad(ll &a,ll b){a=(a+b)%mod;while(a<0)a+=mod;}
inline void mmu(ll &a,ll b){a=a*b%mod;while(a<0)a+=mod;}
#define inv(a) pw(a,mod-2)
#define int long long
#define N 1024

int n,b[N][N],a1=0,a2=0,h[N][N];
bool a[N][N];
int st[N],tot;
int work(){//all 0 count
	For(i,1,n) h[1][i]=a[1][i]^1;
	For(i,2,n){
		For(j,1,n){
			h[i][j]=(a[i][j]?0:h[i-1][j]+1);
		}
	}
	int res=0,now;
	For(i,1,n){
		tot=now=0;
		For(j,1,n){
			while(tot && h[i][st[tot]]>=h[i][j]){
				mad(now,-h[i][st[tot]]*(st[tot]-st[tot-1]));
				tot--;
			}
			mad(now,h[i][j]*(j-st[tot]));
			st[++tot]=j;
			mad(res,now);
		}
	}
	return res;
}
signed main(){IOS;
	cin>>n;
	int all=pw(n*(n+1)/2%mod,2);
	For(i,1,n)For(j,1,n)cin>>b[i][j];
	For(i,0,30){
		For(j,1,n)For(k,1,n)a[j][k]=((b[j][k]>>i)&1)^1;
		mad(a1,pw(2,i)*work());
		For(j,1,n)For(k,1,n)a[j][k]=(b[j][k]>>i)&1;
		mad(a2,pw(2,i)*(all-work()));
	}
	cout<<a1<<" "<<a2<<endl;
return 0;}
```

---

## 作者：行吟啸九州 (赞：2)

这个题的评紫主要还是因为数据，如果给几个$ai <= 1$的测试点，相信这个题肯定会是一个蓝题的。

我们不难发现，&与|这两个位运算，都有一个性质，就是每一位之间互不影响。

由题意得，ai <= $2^{31}$ − 1，所以我们可以把每个数分成31位，每一位分别考虑。

所以转化成这么一个问题，有一个矩阵，每个位置的值要么为0，要么为1。求有多少个子矩阵满足矩阵各个位置全部是1（即&运算）,有多少个子矩阵满足该子矩阵各个位置至少有一个1(即|运算)。

至少有什么什么，通常很难求，所以可以做一个容斥转换，就像是高中数学题，正难则反嘛，我们可以求有多少个子矩阵满足矩阵各个位置全部是0，然后用总子矩阵数-这个答案，一个$n * n$的方阵，子矩阵数目 = $C_{n + 1}^2 * C_{n + 1}^2$的，因为有$n + 1$条横线与竖线，每个子矩阵都是两条竖线与两条横线圈起来的，根据组合数知识可求出以上结果。

所以我们现在就是求有多少个子矩阵满足矩阵各个位置全部是1，0的话同理可做。我们枚举子矩阵的右下端点，考虑画图与木桶原理可知，它对应的所有合法子矩阵的左上端点的可取值范围一定是一个形如这个样子的。

![](https://cdn.luogu.com.cn/upload/image_hosting/dp7m8z44.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

显然对于这种满足单调性性质的，我们可以用单调栈维护，具体细节详见代码与注释。

复杂度O（$n^2logV$)，V = $2^{31}$ − 1。

```
#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
#define int long long
#define mod 1000000007
#define For(i, j, n) for(register int i = j ; i <= n ; ++i) 
int n, num, ansa, anso;
int stk[maxn], a[maxn][maxn], b[maxn][maxn], up[maxn][maxn], cnt[maxn][maxn];
//up[i][j]代表矩阵第i行第j列的点的合法高度, cnt[i][j]代表从矩阵第i行第j列的点左边合法高度大于等于这个点的合法高度的宽度

inline int solve(int x){
	int ans = 0;
	memset(up, 0, sizeof(up));
	For(i, 1, n) For(j, 1, n) if(b[i][j] == x) up[i][j] = up[i - 1][j] + 1;
	For(i, 1, n){
		int top = 0, sum = 0;
		For(j, 1, n){
			cnt[i][j] = 1;
			for( ; top && up[i][stk[top]] >= up[i][j] ; --top) sum -= cnt[i][stk[top]] * up[i][stk[top]], cnt[i][j] += cnt[i][stk[top]];
			sum += cnt[i][j] * up[i][j], ans += sum, stk[++top] = j;
		}
	}
	return ans % mod;
}

signed main(){
	scanf("%lld", &n), num = n * n * (n + 1) * (n + 1) / 4;
	For(i, 1, n) For(j, 1, n) scanf("%lld", &a[i][j]);
	For(i, 0, 30){
		For(j, 1, n) For(k, 1, n) b[j][k] = a[j][k] & 1, a[j][k] >>= 1;
		ansa = (ansa + (solve(1) << i)) % mod , anso = (anso + ((num - solve(0)) % mod << i)) % mod;
	}
	printf("%lld %lld", ansa, anso);
	return 0;
}
```

---

## 作者：da32s1da (赞：1)

这不与[[WC2015]未来程序](https://www.luogu.org/problemnew/show/P4920)的第$5$个测试点是一个题么。。。

二进制每一位$1$单独考虑。

AND：求有多少个全$1$子矩阵

OR：求有多少个全$0$子矩阵，再用总矩阵减去

单调栈维护以$a[i][j]$为右下角的答案，即维护一个梯形面积。

```cpp
#include<cstdio>
#include<stack>
using namespace std;
const int N=1005;
const int mod=1e9+7;
int n,A[N][N],AND,OR,qwq;
int a[N][N],data[N][N],Ans,ans;
typedef pair<int,int>pr;
stack<pr>s;
void clear(){while(s.size())s.pop();ans=0;}
int count(){
    Ans=0;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    a[i][j]=data[i][j]*(a[i-1][j]+1);
    //处理每个1向上的最大延伸长度
    for(int i=1;i<=n;i++){
        clear();//初始化
        for(int j=1;j<=n;j++){
            if(!a[i][j]){clear();continue;}//该点为0，清空栈
            int siz=1;
            while(s.size()&&s.top().first>=a[i][j]){
                siz+=s.top().second;
                ans=(ans-1ll*s.top().first*s.top().second%mod+mod)%mod;
                s.pop();//不能作为左上端点的减去
            }
            s.push(pr(a[i][j],siz));//插入
            ans=(ans+1ll*a[i][j]*siz%mod)%mod;
            Ans=(Ans+ans)%mod;//计算答案
        }
    }
    return Ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	for(int j=1;j<=n;j++)scanf("%d",&A[i][j]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)qwq=(qwq+i*j)%mod;//求总矩阵数
	for(int i=1073741824;i>=1;i>>=1){
		for(int j=1;j<=n;j++)
		for(int k=1;k<=n;k++)data[j][k]=(A[j][k]&i)>0;//每一位分开考虑
		AND=(AND+1ll*count()*i%mod)%mod;//AND
		for(int j=1;j<=n;j++)
		for(int k=1;k<=n;k++)data[j][k]=!data[j][k];
		OR=(OR+1ll*(qwq-count()+mod)%mod*i%mod)%mod;//总矩阵减去
	}
	printf("%d %d\n",AND,OR);
} 
```

---

## 作者：Fzrcy (赞：0)

Tags：二进制拆分，单调栈。

由于 $\operatorname{AND}$ 值之和与 $\operatorname{OR}$ 值之和在 $01$ 矩阵中可以互相转换，所以下文只计算 $\operatorname{OR}$ 值之和。

因为二进制下每个数位互不影响，所以我们对每个数位分别计算贡献，最后合并即可。

拆分数位后原矩阵变为 $01$ 矩阵，然后对于点对 $(i,j)$ 分别统计因其为右下角的 $\operatorname{OR}$ 值为 $1$ 的矩阵的个数。

有一个明显的性质：若以 $(x,y)$ 为左上角、$(i,j)$ 为右下角的 $\operatorname{OR}$ 值为 $1$，则以 $(a,b)$（$a\le x,b\le y$）为左上角、$(i,j)$ 为右下角的 $\operatorname{OR}$ 值均为 $1$。

假设当前枚举到 $(i,j)$。

设 $b_x$（$1\le x\le i$）表示最大的 $y$，满足以 $(x,y)$ 为左上角的 $\operatorname{OR}$ 值为 $1$ 且 $1\le y \le j$，若不存在这样的 $y$，则 $b_x=0$。

根据上文的性质，我们得到 $b_x \ge b_{x+1}$，因此我们可以用单调栈维护 $b_x$ 和 $\sum_{1\le x\le i}b_x$。

那么对于以 $(i,j)$ 为右下角的 $\operatorname{OR}$ 值为 $1$ 的矩阵个数为 $\sum_{1\le x\le i}b_x$。

最后合并答案即可。

```cpp
// qwq
#include <bits/stdc++.h>
#define RG register
#define R RG int
#define RL RG ll
#define inl inline
#define gc getchar()
using ll = long long;
using namespace std;
inl int in(){
    char c;R x=0,bo=0;
    while(!isdigit(c=gc))if(c=='-')bo=1;
    while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=gc;
    return bo?-x:x;
}
constexpr int N=1002;
constexpr ll P=1e9+7;
int st[N],top,cur;
int n,a[N][N],b[N];
void ins(R x){
    while(top&&b[st[top]]<=b[x]){
        cur-=(st[top]-st[top-1])*b[st[top]];
        top--;
    }
    st[++top]=x;
    cur+=(st[top]-st[top-1])*b[st[top]];
}
ll sol(){
    RL ans=0;cur=0,top=0;
    for(R i=1;i<=n;i++)b[i]=0;
    for(R i=1;i<=n;i++,cur=0,top=0){
        for(R j=1;j<=n;j++){
            if(a[i][j])b[j]=i;
            ins(j),(ans+=cur)%=P;
        }
    }
    return ans;
}
int t[N][N];
ll all,a0,a1;
void get(R b){
    for(R i=1;i<=n;i++)
        for(R j=1;j<=n;j++)
            a[i][j]=t[i][j]>>b&1;
    (a1+=(sol()<<b)%P)%=P;
    for(R i=1;i<=n;i++)
        for(R j=1;j<=n;j++)
            a[i][j]^=1;
    (a0+=(((all-sol()+P)%P)<<b)%P)%=P;
}
int main(){
    n=in();
    for(R i=1;i<=n;i++)
        for(R j=1;j<=n;j++)
            t[i][j]=in(),(all+=i*j%P)%P;
    for(R i=0;i<31;i++)get(i);
    cout<<a0<<' '<<a1;
    return 0;
}
```



---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.com.cn/problem/P5300)看题目。  
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到位运算，由于进行位运算的时候各个二进制位是独立的，我们于是不难想到将每一位分离出来处理。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;将$a$中的数的二进制第$k$位分离出来之后，我们就得到了一个$0/1$矩阵$b_k$。考虑枚举点$(i,j)$，并且计算出所有以$(i,j)$为右下角的子矩阵的贡献。对于$and$和$or$运算分别分析性质：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$1.and:$由于$b_k$是一个$0/1$矩阵，所以会对答案产生贡献的子矩阵只会是以$(i,j)$为右下角，且全是$1$的子矩阵。并且不难发现对于那些以$(i,j)$为右下角且有贡献的子矩阵，它们的左上角$(x,y)$，$y$的可用值范围会随着$i-x$的增大而减小。这启示我们用一个单调栈维护一块全是$1$的、内部除$(i,j)$外所有位置都在$(i,j)$的左上方的区域的面积。在这个区域内的位置都可以成为$(i,j)$的左上角，并且对答案有贡献。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$2.or:$类似上面。对答案造成贡献的子矩阵只需要里面有$1$即可。于是考虑用总面积减去不可行面积。我们现在考虑维护一块全是$0$的且内部除$(i,j)$外所有位置都在$(i,j)$的左上方的区域的面积。在这块区域内的位置如果作为$(i,j)$的左上角，就不会产生贡献。减去它们即可。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;总时间是$O(n^2\log_2 \max \{a\})$  
# 代码
```cpp
#include <cstdio>

typedef long long LL;

const int mod = 1e9 + 7;
const int MAXN = 1005;

template<typename _T>
void read( _T &x )
{
	x = 0; char s = getchar();int f = 1;
	while( s < '0' || '9' < s ) { f = 1; if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ) { x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ) { putchar( '-' ), x = -x; }
	if( 9 < x ) { write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

int sta[MAXN], top;
int up[2][MAXN][MAXN];
int a[MAXN][MAXN];
int N;
bool b[MAXN][MAXN];

int main()
{
	freopen( "andorsum.in", "r", stdin );
	freopen( "andorsum.out", "w", stdout );
	LL andAns = 0, orAns = 0;
	int mx = 0, siz;
	read( N );
	for( int i = 1 ; i <= N ; i ++ )
		for( int j = 1 ; j <= N ; j ++ )
			read( a[i][j] ), mx = MAX( mx, a[i][j] );
	for( int k = 0 ; ( 1ll << k ) <= mx ; k ++ )
	{
		for( int i = 1 ; i <= N ; i ++ )
			for( int j = 1 ; j <= N ; j ++ )
				b[i][j] = ( a[i][j] >> k ) & 1, up[0][i][j] = up[1][i][j] = 0; 
		for( int t = 0 ; t < 2 ; t ++ )
			for( int i = 1 ; i <= N ; i ++ )
				for( int j = 1 ; j <= N ; j ++ )	
					up[t][i][j] = ( b[i][j] == t ? up[t][i - 1][j] + 1 : 0 );
		for( int i = 1 ; i <= N ; i ++ )
		{
			siz = top = 0, sta[0] = 0;
			for( int j = 1 ; j <= N ; j ++ )
			{
				while( top && up[1][i][sta[top]] >= up[1][i][j] )
					siz -= up[1][i][sta[top]] * ( sta[top] - sta[top - 1] ), top --;
				siz += up[1][i][j] * ( j - sta[top] ), sta[++ top] = j;
				andAns = ( andAns + 1ll * siz * ( 1ll << k ) % mod ) % mod;
			}
			siz = top = 0, sta[0] = 0;
			for( int j = 1 ; j <= N ; j ++ )
			{
				while( top && up[0][i][sta[top]] >= up[0][i][j] )
					siz -= up[0][i][sta[top]] * ( sta[top] - sta[top - 1] ), top --;
				siz += up[0][i][j] * ( j - sta[top] ), sta[++ top] = j;
				orAns = ( orAns + 1ll * ( i * j - siz ) * ( 1ll << k ) % mod ) % mod;
			}
		}
	}
	write( andAns ), putchar( ' ' ), write( orAns ), putchar( '\n' );
	return 0;
}
```


---

## 作者：Rainybunny (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.com.cn/problem/P5300).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~数组开大光荣MLE爆零.~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;按照一般的套路, 我们思考矩阵内的每一个元素对最后答案的贡献. 由于$and$和$or$的计算对于不同的二进制位是独立的, 我们考虑把原矩阵拆成很多个$01$矩阵, 代表元素某一二进制位的值, 分别计算.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;接下来, 先思考$and$运算. 把一个矩阵的贡献记在该矩阵右下角的元素上, 可以发现问题转化为: **求以某个点为右下角的全$1$矩阵的个数**. 不难想到使用单调栈求解. 枚举每一行, 并处理处该行每一个元素上方 ( 包括自身 ) 有多少个$1$, 抽象成一个柱状图, 就很好办了.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~接下来的剧情你应该已经猜到~~, 由于某个矩阵在$or$计算中产生贡献$iff$其中至少有一个元素为$1$, 我们只需要把$and$所求的东西反过来, 求到**以某个点为右下角的全$0$矩阵的个数**, 再用以该点为右下角的所有矩阵个数减掉它即可.
# 代码
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;注意代码中$Upp$数组的空间消耗非常大, 尽量不要这样做, 在枚举行的时候顺便推出该行的$Upp$即可. ( 懒得改$qwq$. )
```cpp
#include <cstdio>
#include <utility>

#define Int register int
#define mkpr( x, y ) make_pair ( x, y )
#define Bit( x, b ) ( bool ( x & ( 1LL << b ) ) )

using namespace std;

const int MAXN = 1000, MOD = 1e9 + 7;
int n, a[MAXN + 5][MAXN + 5], UpperBit;
int Upp[2][35][MAXN + 5][MAXN + 5], Top;
pair<int, int> S[MAXN + 5];

inline int rint () {
	int x = 0; char s = getchar ();
	for ( ; s < '0' || '9' < s; s = getchar () );
	for ( ; '0' <= s && s <= '9'; s = getchar () ) x = ( x << 3 ) + ( x << 1 ) + ( s ^ '0' );
	return x;
}

inline void Work () {
	n = rint ();
	for ( Int i = 1; i <= n; ++ i ) {
		for ( Int j = 1; j <= n; ++ j ) {
			a[i][j] = rint ();
			if ( 1LL << UpperBit < a[i][j] ) {
				for ( ; 1LL << UpperBit <= a[i][j]; ++ UpperBit );
				-- UpperBit;
			}
		}
	}
	for ( Int bt = 0; bt <= UpperBit; ++ bt ) {
		for ( Int i = 1; i <= n; ++ i ) {
			for ( Int j = 1; j <= n; ++ j ) {
				Upp[1][bt][i][j] = Bit ( a[i][j], bt ) ? Upp[1][bt][i - 1][j] + 1 : 0;
				Upp[0][bt][i][j] = ! Bit ( a[i][j], bt ) ? Upp[0][bt][i - 1][j] + 1 : 0;
			}
		}
	}
	int Ansor = 0, Ansand = 0;
	for ( Int bt = 0; bt <= UpperBit; ++ bt ) {
		for ( Int i = 1; i <= n; ++ i ) {
			int BitCnt = 0;
			S[Top = 0] = mkpr ( -1, 0 );
			for ( Int j = 1; j <= n; ++ j ) {
				int l = 1;
				for ( ; S[Top].first >= Upp[1][bt][i][j]; ) {
					BitCnt = BitCnt - ( S[Top].first - Upp[1][bt][i][j] ) * S[Top].second;
					l += S[Top].second;
					-- Top;
				}
				S[++ Top] = mkpr ( Upp[1][bt][i][j], l ), BitCnt += Upp[1][bt][i][j];
				Ansand = ( Ansand + BitCnt * ( 1LL << bt ) % MOD ) % MOD;
			}
			BitCnt = 0;
			S[Top = 0] = mkpr ( -1, 0 );
			for ( Int j = 1; j <= n; ++ j ) {
				int l = 1;
				for ( ; S[Top].first >= Upp[0][bt][i][j]; ) {
					BitCnt = BitCnt - ( S[Top].first - Upp[0][bt][i][j] ) * S[Top].second;
					l += S[Top].second;
					-- Top;
				}
				S[++ Top] = mkpr ( Upp[0][bt][i][j], l ), BitCnt += Upp[0][bt][i][j];
				Ansor = ( Ansor + ( 1LL * i * j - BitCnt ) * ( 1LL << bt ) % MOD ) % MOD;
			}
		}
	}
	printf ( "%lld %lld\n", Ansand, Ansor );
}

int main () {
//	freopen ( "andorsum.in", "r", stdin );
//	freopen ( "andorsum.out", "w", stdout );
	Work ();
	return 0;
}
```

---

## 作者：hl666 (赞：0)

又是GXOI2019里水水的送分题，然而我看错题+细节写挂愣是搞了一个多小时（深深的明白自己的弱小）

首先看到二进制我们就考虑到**枚举每一位**，算子矩阵中这一位为$1$的方案数再乘起来吧

然后这时候矩阵就变成了$0/1$矩阵（其实样例1就在提示你这种做法），我们考虑$AND$时的答案，即求出**全$1$矩阵**个数

这个很套路吧，我们预处理出$h_{i,j}$表示$(i,j)$以上（包括$(i,j)$最多有多少个连续的$1$）

接下来考虑求出以每一个点为**矩阵的右下角**时的方案数，每一列的情况可以**单调栈**处理：

考虑连续递增的一段的答案（如$(3,5,6)$我们是可以计算的，就是一个求和的过程），那么我们就维护**单调递增**的单调栈

然后考虑每次加入一个数，那么前面大于它的都会被他删掉，此时的贡献其实就是删掉数的个数$\times$当前的$h_{i,j}$

因此单调栈里再维护一下前缀和以及数的个数（因为被删除的要累积到删除它的数上），就完成了$AND$的做法

那么$OR$呢，其实直接**补集转化**一下就好了，用总方案数减去全$0$矩阵方案数即为所求

因此综上，复杂度$O(n^2\log a_i)$，足以通过此题

CODE

```cpp
#include<cstdio>
#include<cctype>
#define RI register int
#define CI const int&
#define Tp template <typename T>
using namespace std;
const int N=1005,mod=1e9+7;
int n,a[N][N],and_ans,or_ans,mx,h[N][N],st[N],sum[N],val[N],top,cur;
class FileInputOutput
{
	private:
		static const int S=1<<21;
		#define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
		char Fin[S],*A,*B;
	public:
		Tp inline void read(T& x)
		{
			x=0; char ch; while (!isdigit(ch=tc()));
			while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));
			
		}
		#undef tc
}F;
inline void inc(int& x,CI y)
{
	if ((x+=y)>=mod) x-=mod;
}
inline int add(CI x,CI y)
{
	int t=x+y; return t>=mod?t-mod:t;
}
inline int solve_and(CI bs,int ret=0)
{
	RI i,j; for (i=1;i<=n;++i) for (j=1;j<=n;++j)
	if (a[i][j]&bs) h[i][j]=h[i-1][j]+1; else h[i][j]=0;
	for (i=1;i<=n;++i) for (top=0,j=1;j<=n;++j) if (!h[i][j]) top=0; else
	{
		int high=1; while (top&&st[top]>h[i][j]) high+=val[top--];
		inc(ret,1LL*h[i][j]*high%mod); inc(ret,sum[top]); st[++top]=h[i][j];
		val[top]=high; sum[top]=add(sum[top-1],1LL*h[i][j]*val[top]%mod);
	}
	return 1LL*ret*bs%mod;
}
inline int solve_or(CI bs,int ret=0)
{
	RI i,j; for (i=1;i<=n;++i) for (j=1;j<=n;++j)
	if (!(a[i][j]&bs)) h[i][j]=h[i-1][j]+1; else h[i][j]=0;
	for (i=1;i<=n;++i) for (top=0,j=1;j<=n;++j) if (!h[i][j]) top=0; else
	{
		int high=1; while (top&&st[top]>h[i][j]) high+=val[top--];
		inc(ret,1LL*h[i][j]*high%mod); inc(ret,sum[top]); st[++top]=h[i][j];
		val[top]=high; sum[top]=add(sum[top-1],1LL*h[i][j]*val[top]%mod);
	}
	ret=cur-ret; if (ret<0) ret+=mod; return 1LL*ret*bs%mod;
}
int main()
{
	//freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
	RI i,j; for (F.read(n),i=1;i<=n;++i) for (j=1;j<=n;++j)
	F.read(a[i][j]),mx=a[i][j]>mx?a[i][j]:mx,inc(cur,1LL*i*j%mod);
	for (i=1;i<=mx&&i>0;i<<=1) inc(and_ans,solve_and(i)),inc(or_ans,solve_or(i));
	return printf("%d %d",and_ans,or_ans),0;
}
```



---

## 作者：hehelego (赞：0)

**2019.8.15 upd:** afo后更新.插入内容在题解的开头.

枚举列$j$,从上向下考虑每一行$i$,对于$(i,j)$,考虑如何计算右下角为$(i,j)$的所有全1矩形数量.  
**先考虑矩形平行于行方向上的长度** 枚举长度$k$,贡献为$\sum_{1\leq k\leq n}len(k)$其中$len(k)$为 从$(i,j)$向上走满足$left_{i',j}\geq k$的$(i',j)$能走的最大长度,或者说用长度为$k$的线段向上滑动,走多远会被卡住.这个想法的正确性是显然的,但是会导致总复杂度到达$O(n^3)$.  
**先考虑矩形平行于列方向上的长度** 即考虑右上角为$(i',j)$时构成的子矩阵计数.这样固定了矩形的一条边后,贡献是$min(left_{x,j}\, x\in[i',i])$,相当于考虑固定了一条纵向的线段,向左移动多远会遇到0,显然取决于$left$的最小值.  

和前一种想法进行对比一下它们是等价的.但是这种想法给了我们一个可以均摊$O(n^2)$维护的式子,即
$$A(i,j)=\sum_{0\lt x\leq i}min(left_{y,j}\quad y\in[x,i])$$  
显然sigma里面那个东西关于$x$是单调不增的,我们考虑把$min(left_{y,j}\quad y\in[x,i])$相同的$x$缩起来,记录当前的$A(i,j)$,然后考虑新加入一个$(i+1,j)\quad left_{i+1,j}$的影响:我们需要把**最近的一些**  $A(i,j)$,其中$min(left_{y,j}\quad y\in[x,i])\gt left_{i+1,j}$修改掉(有了更短的东西卡住了之前较长的东西qwq),改成$left_{i+1,j}$,这个特点很像stack,于是我们大概知道怎么玩了!  

维护一个stack记录那个min(这会是从bottom到top单调增的),同时记录stack里面东西的sum.新插入一个left,把min过大的部分改掉. 然后发现这东西单次$O(n)$, ~~没救了~~ emm,把相同的min值缩起来,再考虑复杂度.每个连续段最多被替换一次,而连续段显然是$O(n^2)$的,于是这个求出所有$A(i,j)$的过程复杂度为$O(n^2)$...写的有点乱,不过这些应该能够帮助您成功理解下面的东西了(指code).....

---

这是个二合一题...首先看一下这东西是位运算结果之和所以每一位的贡献是独立的,值域$2^{31}-1$拆32位分别算乘上$2^i$求和即可.然后每一位的贡献咋算啊,and要求全都是1,or的话要求至少一个1,反转一下就是所有子矩阵减掉全是0的.01互换一下就和and一样了.

----

前面都是瞎扯...看这里.  
1. 我们发现可以拆位统计,因为(a&b+c&d)=$\sum_{i=0}^{32}(a[i]\,and\,b[i])+(c[i]\,and\,d[i])$
2. 每一位只能是0/1,那么一个子矩阵的and为1就是全1才会有$2^i$的贡献,考虑一下or,是至少一个1统计全0即可,再01反转,就和and一致了,两问没有本质区别.

我们下面考虑如何解决这个计数问题,给定一个01矩阵,求全1矩阵数量.  
~~这是[原题](https://www.luogu.org/problemnew/show/P3400)~~

考虑枚举$(i,j)$,有多少右下角是$(i,j)$,考虑一下长为$x$的矩阵能够有多少个,就是一直向上找$j$列的元素$(k,j)$,使得$(k,j)$左侧不足$x$个连续1.

首先这个向左极大连续1我们可以$n^2$乱搞出来...
然后考虑这个计算.  
似乎不太可做?维护一下$(1,j),(2,j),(3,j)...(i,j)$这样一些位置向左延申长度的**后缀最小值**这东西向上走显然单调不增..暴力跳上去或者倍增跳上去就可以了,那枚举矩形的长为$x$咋去掉啊?  


这里懒得划式子...我们举个例子来说明计算方式.  
$1,1,1$  
$0,1,1$  
$0,0,1$  
考虑右下那个位置,贡献是$1+1+1$,因为上面的扩展长度**被最小值卡死了**,所以这个位置的贡献是,这一列上的后缀最小值之和.  

后缀最小值在向下扫描时显然是不增的,我们考虑用一个单调栈来维护,加入了一个元素$x$我们不断把栈顶元素扔掉,减掉它的贡献,如果扔掉了k个元素,那么后缀最小值等于$x$的数量是$k+1$,贡献是$x(k+1)$.扔掉的元素只是被$x$卡死了,我们还需要知道有多少个元素被踢掉了...于是单调栈维护二元组$(value,count)$表示count个后缀最小值是value.  

然后就做完了...


```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
int read(){
    int x=0;char c;
    do{c=getchar();}while(!isdigit(c));
    do{x=x*10+c-'0';c=getchar();}while(isdigit(c));
    return x;
}
const int N=1000+10;
const int LG=32;
int n,b[N][N];
bool a[32][N][N];
typedef long long Int;
const Int mod=Int(1e9)+7LL;

int left[N][N];
Int solve(int k){// a[k][n*n] ,count full sub matrix

// 扫出向左延申的极大长度.
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
        if(a[k][i][j]) left[i][j]=left[i][j-1]+1;
        else left[i][j]=0;

    Int ans=0;
// 枚举每一列...从第一行开始扫描下去.
    for(int j=1;j<=n;j++){
        std::stack<std::pair<int,int> > stk; //(value,count)
        Int s=0; //这个是后缀最小值之和.
        for(int i=1;i<=n;i++){ int c=1;
            while(!stk.empty()&&stk.top().first>=left[i][j]){
                std::pair<int,int> p=stk.top(); stk.pop();
// 扣掉贡献,累加计数.
                s-=p.first*p.second%mod; s=(s%mod+mod)%mod;
                c+=p.second;
            }
// 这里,最后$c$行的后缀最小值都是$left_{i,j}$把贡献累计.
            s=(s+1LL*left[i][j]*c%mod)%mod;
            stk.push(std::make_pair(left[i][j],c));
// (i,j)为右下角的矩形计数,根据上面分析是向左扩展长度的后缀最小值之和.
            ans=(ans+s)%mod;
        }
    }
    return ans;
}

int main(){
    n=read();
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
        b[i][j]=read();
// 拆32位统计.
        for(int k=0;k<LG;k++) a[k][i][j]=(b[i][j]>>k)&1;
    }

    Int ans=0,qwq=n*(n+1)/2; qwq=qwq*qwq%mod;
    for(int i=0;i<LG;i++) ans=(ans+(1LL<<i)%mod*solve(i))%mod;
    std::cout<<ans<<" "; ans=0;

    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
        for(int k=0;k<LG;k++) a[k][i][j]^=1;
    for(int i=0;i<LG;i++){
        ans=(ans+(1<<i)%mod*(qwq-solve(i)+mod)%mod)%mod;
        ans=(ans%mod+mod)%mod;
    }
    std::cout<<ans<<std::endl;

    return 0;
}
``

---

## 作者：Owen_codeisking (赞：0)

突然发现哪里的省选都比 $ZJOI$ 可做……

实质上这题就是求有多少个子矩阵全部是 $0/1$

我们每次处理出每个点的最长 $0$ 区间，把问题转化为所有区间最小值之和。

建议管理员把这题改为【模板】区间最小值之和。

$Code\ Below:$

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=1000+10;
const int mod=1e9+7;
int n,a[maxn][maxn],len[maxn];ll val,ans1,ans2;
pair<int,int> sta[maxn];

inline int read()
{
	register int x=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return (f==1)?x:-x;
}

inline ll solve(int T,int f)
{
	ll res=0,sum;int top,tmp;
	for(int i=1;i<=n;i++) len[i]=0;
	for(int i=1;i<=n;i++)
	{
		sum=top=0;
		for(int j=1;j<=n;j++)
		{
			len[j]=((a[i][j]>>T)&1)==f?len[j]+1:0;tmp=1;
			while(top&&sta[top].first>=len[j]) sum-=1ll*sta[top].first*sta[top].second,tmp+=sta[top].second,top--;
			sum+=1ll*len[j]*tmp;(res+=sum)%=mod;sta[++top]=make_pair(len[j],tmp);
		}
	}
	return res;
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) a[i][j]=read(),(val+=1ll*i*j)%=mod;
	for(int i=0,j=1;i<=30;i++,j<<=1)
	{
		(ans1+=solve(i,1)*j)%=mod;
		(ans2+=(val-solve(i,0))*j)%=mod;
	}
	(ans1+=mod)%=mod;(ans2+=mod)%=mod;
	printf("%lld %lld\n",ans1,ans2);
	return 0;
}
```

---

## 作者：Great_Influence (赞：0)

首先，问题是二进制操作。我们考虑拆位分别计算。

那么，矩阵就只剩下 $0$ 和 $1$ 两种元素了。

区间与为 $1$ 当且仅当整个矩阵都是 $1$ ，区间或为 $0$ 当且仅当整个矩阵都是 $0$ 。那么，就变成了两个类似的问题。以区间与为例。

我们对每个位置记录数值 $h_i$ 表示从这个位置向下延伸最长有多少个 $1$ 。我们再枚举矩阵左上角位置，然后再枚举右上角。可以发现，右上角向右移动时矩阵的可能高度只会单调不断缩小。

因此我们从右向左枚举左上角，然后用一个单调栈维护可能高度的上限即可。

复杂度 $O(n^2\log w)$ 。 $w$ 为权域。

代码:
```cpp
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cassert>
#include<queue>
#include<iostream>
#define Rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Repe(i,a,b) for(register int i=(a);i>=(b);--i)
#define rep(i,a,b) for(register int i=(a);i<(b);++i)
#define pb push_back
#define mx(a,b) (a>b?a:b)
#define mn(a,b) (a<b?a:b)
typedef unsigned long long uint64;
typedef unsigned int uint32;
typedef long long ll;
using namespace std;

namespace IO
{
	const uint32 Buffsize=1<<15,Output=1<<24;
	static char Ch[Buffsize],*S=Ch,*T=Ch;
	inline char getc()
	{
		return((S==T)&&(T=(S=Ch)+fread(Ch,1,Buffsize,stdin),S==T)?0:*S++);
	}
	static char Out[Output],*nowps=Out;
	
	inline void flush(){fwrite(Out,1,nowps-Out,stdout);nowps=Out;}

	template<typename T>inline void read(T&x)
	{
		x=0;static char ch;T f=1;
		for(ch=getc();!isdigit(ch);ch=getc())if(ch=='-')f=-1;
		for(;isdigit(ch);ch=getc())x=x*10+(ch^48);
		x*=f;
	}

	template<typename T>inline void write(T x,char ch='\n')
	{
		if(!x)*nowps++='0';
		if(x<0)*nowps++='-',x=-x;
		static uint32 sta[111],tp;
		for(tp=0;x;x/=10)sta[++tp]=x%10;
		for(;tp;*nowps++=sta[tp--]^48);
		*nowps++=ch;
	}
}
using namespace IO;

void file()
{
#ifndef ONLINE_JUDGE
	FILE*DSD=freopen("water.in","r",stdin);
	FILE*CSC=freopen("water.out","w",stdout);
#endif
}

const int MAXN=1011;

static int n,w[MAXN][MAXN];

inline void init()
{
	read(n);
	Rep(i,1,n)Rep(j,1,n)read(w[i][j]);
}

static int a[MAXN][MAXN],h[MAXN][MAXN];

static int ans0,ans1;

const int mod=1e9+7;

static int sta[MAXN],tp;

inline void solve()
{
	Rep(_,0,30)
	{
		ll sm=0ll;
		Rep(i,1,n)Rep(j,1,n)a[i][j]=w[i][j]>>_&1;
		Repe(i,n,1)Rep(j,1,n)h[i][j]=a[i][j]?h[i+1][j]+1:0;
		Rep(i,1,n)h[i][n+1]=-1;
		Rep(i,1,n)
		{
			int *cr=h[i],as=0;
			sta[tp=1]=n+1;
			Repe(j,n,1)
			{
				while(cr[sta[tp]]>=cr[j])
				{
					int u=sta[tp--];
					as-=(sta[tp]-u)*cr[u];
				}
				as+=(sta[tp]-j)*cr[j],sta[++tp]=j;
				sm+=as;
			}
		}
		ans1=(ans1+sm%mod*(1ll<<_))%mod;
		sm=0;
		Rep(i,1,n)Rep(j,1,n)a[i][j]=~w[i][j]>>_&1;
		Repe(i,n,1)Rep(j,1,n)h[i][j]=a[i][j]?h[i+1][j]+1:0;
		Rep(i,1,n)
		{
			int *cr=h[i],as=0;
			sta[tp=1]=n+1;
			Repe(j,n,1)
			{
				while(cr[sta[tp]]>=cr[j])
				{
					int u=sta[tp--];
					as-=(sta[tp]-u)*cr[u];
				}
				as+=(sta[tp]-j)*cr[j],sta[++tp]=j;
				sm+=(n-i+1)*(n-j+1)-as;
			}
		}
		ans0=(ans0+sm%mod*(1ll<<_))%mod;
	}
	printf("%d %d\n",ans1,ans0);
}

int main()
{
	file();
	init();
	solve();
	return 0;
}
```

---

## 作者：NeosKnight (赞：0)

显然对于每一位考虑贡献。

与我们就求所有全 1 矩阵个数。

或我们就求所有全 0 矩阵个数然后用总数减去就行了。

然后考虑求以某个点为右下角的全 0/1 矩阵个数。采用类似悬线法的方法，我们求出一个点向上最长能扩张的长度$H[i][j]$，令 $S[i][j]$ 为第i行j列的贡献,那么 $S[i][j]=\sum_{k=1}^{j} min_{l=k}^jH[i][l]$

就是个后缀 min 求和。这个就可以直接用一个单调栈维护了,求出每一个点前面第一个比自己小的后,一部分答案是间隔长度乘以自己的 $H$ , 另一部分就直接是那个点的 $S$。

code:

```cpp
#include<bits/stdc++.h>
#define Set(a,b) memset(a,b,sizeof(a))
using namespace std;
const int N=1005;
const int mod=1e9+7;
template <typename T> inline void init(T&x){
	x=0;char ch=getchar();bool t=0;
	for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') t=1;
	for(;ch>='0'&&ch<='9';ch=getchar()) x=(x<<1)+(x<<3)+(ch-48);
	if(t) x=-x;return;
}
typedef long long ll;
template<typename T>inline void Inc(T&x,int y){x+=y;if(x>=mod) x-=mod;return;}
template<typename T>inline void Dec(T&x,int y){x-=y;if(x <  0) x+=mod;return;}
template<typename T>inline int fpow(int x,T k){int ret=1;for(;k;k>>=1,x=(ll)x*x%mod) if(k&1) ret=(ll)ret*x%mod;return ret;}
inline int Sum(int x,int y){x+=y;if(x>=mod) return x-mod;return x;}
inline int Dif(int x,int y){x-=y;if(x < 0 ) return x+mod;return x;}
int mat[N][N];
int n,ans0=0,ans1=0,tot;
int H0[N][N],H1[N][N],S0[N][N],S1[N][N];
int stk0[N],stk1[N],top0,top1;
inline void Solve(int k){
	int all0=0,all1=0;
	for(int i=1;i<=n;++i){
		top0=top1=0;
		for(int j=1;j<=n;++j) {
			S0[i][j]=S1[i][j]=0;
			int v=(mat[i][j]>>k)&1,fir;
			if(v) H1[i][j]=H1[i-1][j]+1,H0[i][j]=0;
			else  H1[i][j]=0,H0[i][j]=H0[i-1][j]+1;
			while(top0&&H0[i][j]<H0[i][stk0[top0]]) --top0;
			fir=stk0[top0];
			S0[i][j]=(ll)(j-fir)*H0[i][j]%mod;
			
			if(top0) Inc(S0[i][j],S0[i][stk0[top0]]);stk0[++top0]=j;
			Inc(all0,S0[i][j]);
			while(top1&&H1[i][j]<H1[i][stk1[top1]]) --top1;
			fir=stk1[top1];
			S1[i][j]=(ll)(j-fir)*H1[i][j]%mod;
			
			if(top1) Inc(S1[i][j],S1[i][stk1[top1]]);stk1[++top1]=j;
			Inc(all1,S1[i][j]);
		}
	}int bit=(1<<k)%mod;
	Inc(ans0,(ll)all1*bit%mod);
	Inc(ans1,(ll)Dif(tot,all0)*bit%mod);
	return;
}
int main()
{
	init(n);
	for(int i=1;i<=n;++i) for(int j=1;j<=n;++j) Inc(tot,i*j),init(mat[i][j]);
	for(int k=0;k<31;++k) Solve(k);
	printf("%d %d\n",ans0,ans1);
	return 0;
}

```

---

## 作者：览遍千秋 (赞：0)

## 问题描述

Freda 学习了位运算和矩阵以后，决定对这种简洁而优美的运算，以及蕴含深邃空间的结构进行更加深入的研究。

对于一个由非负整数构成的矩阵，她定义矩阵的 $\texttt{AND}$ 值为矩阵中所有数二进制 $\texttt{AND(&)}$ 的运算结果；定义矩阵的 $\texttt{OR}$ 值为矩阵中所有数二进制 $\texttt{OR(|)}$ 的运算结果。

给定一个 $N \times N$ 的矩阵，她希望求出：
1. 该矩阵的所有子矩阵的 $\texttt{AND}$ 值之和（所有子矩阵 $\texttt{AND}$ 值相加的结果）。
2. 该矩阵的所有子矩阵的 $\texttt{OR}$ 值之和（所有子矩阵 $\texttt{OR}$ 值相加的结果）。

接下来的剧情你应该已经猜到——Freda 并不想花费时间解决如此简单的问题，所以这个问题就交给你了。

由于答案可能非常的大，你只需要输出答案对 $1,000,000,007 (10^9 + 7)$ 取模后的结果。

[LG5300](https://www.luogu.com.cn/problem/P5300)

---

## 题解

发现 and 和 or 大毒瘤出现~~开幕雷击~~，于是考虑按位计算贡献。

问题就简化为了01矩阵。

于是一个子矩阵全是0的话对or有负贡献，全是1的话对and有正贡献。

单调栈维护即可

---

## $\mathrm{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

template <typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh=1;
	while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
	if(ch=='-') ch=getchar(),fh=-1;
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=fh;
}

const int mod=1000000007;
const int maxn=1007;

int a[maxn][maxn],n;
long long ansor,ansand;
int s[maxn],h[maxn],val[maxn],pos;
int mx;

void Init(void){
	read(n);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
		read(a[i][j]),mx=max(mx,a[i][j]);
}

long long sqr(long long x){
	return (long long)x*(x+1)/2;
}

int calc(int need){
	long long res=0;
	memset(h,0,sizeof(h));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if((a[i][j]&1)==need) h[j]++;
			else h[j]=0;
			if(h[j]>s[pos]) s[++pos]=h[j],val[pos]=1;
			else{
				int k=0;
				while(h[j]<s[pos]){
					k+=val[pos];
					res=(res+(s[pos]-max(s[pos-1],h[j]))*sqr(k)%mod)%mod;
					--pos;
				}
				s[++pos]=h[j],val[pos]=k+1;
			}
		}
		int k=0;
		while(pos){
			k+=val[pos];
			res=(res+(s[pos]-s[pos-1])*sqr(k)%mod)%mod;
			--pos;
		}
	}
	return res;
}

void Work(void){
	int tp=0;
	while(mx){
		ansand=(ansand+calc(1)*(1<<tp)%mod)%mod;
		ansor=(ansor+(sqr(n)*sqr(n)%mod-calc(0))*(1<<tp)%mod)%mod;
		mx>>=1;tp++;
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]>>=1;
	}
	ansand=(ansand%mod+mod)%mod;
	ansor=(ansor%mod+mod)%mod;
	printf("%lld %lld\n",ansand,ansor);
}

signed main(){
//	freopen("andorsum.in","r",stdin);freopen("andorsum.out","w",stdout);
	Init();
	Work();
}
```

---

