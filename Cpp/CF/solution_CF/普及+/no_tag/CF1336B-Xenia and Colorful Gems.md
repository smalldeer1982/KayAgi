# Xenia and Colorful Gems

## 题目描述

Xenia is a girl being born a noble. Due to the inflexibility and harshness of her family, Xenia has to find some ways to amuse herself.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336B/f1c62b7a1a43a6f38201f883bcf9e45e175e9eca.png)Recently Xenia has bought $ n_r $ red gems, $ n_g $ green gems and $ n_b $ blue gems. Each of the gems has a weight.

Now, she is going to pick three gems.

Xenia loves colorful things, so she will pick exactly one gem of each color.

Xenia loves balance, so she will try to pick gems with little difference in weight.

Specifically, supposing the weights of the picked gems are $ x $ , $ y $ and $ z $ , Xenia wants to find the minimum value of $ (x-y)^2+(y-z)^2+(z-x)^2 $ . As her dear friend, can you help her?

## 说明/提示

In the first test case, Xenia has the following gems:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1336B/2487fca86bd28d2bebb967f33db75171edb995c7.png)

If she picks the red gem with weight $ 7 $ , the green gem with weight $ 6 $ , and the blue gem with weight $ 4 $ , she will achieve the most balanced selection with $ (x-y)^2+(y-z)^2+(z-x)^2=(7-6)^2+(6-4)^2+(4-7)^2=14 $ .

## 样例 #1

### 输入

```
5
2 2 3
7 8
6 3
3 1 4
1 1 1
1
1
1000000000
2 2 2
1 2
5 4
6 7
2 2 2
1 2
3 4
6 7
3 4 1
3 2 1
7 3 3 4
6```

### 输出

```
14
1999999996000000002
24
24
14```

# 题解

## 作者：huayucaiji (赞：8)

这是一道有趣的题。

看到这个题，我们作为一种贪婪的生物，肯定会想到贪心，也就是找到尽量相近的 $x,y,z$。  
~~Q：这不是废话吗。这是题意啊~~    
~~A：这就是废话。~~

但是，这让我们知道我们直接去求这三个数，是不现实的。那么我们会想到一个算法：**二分答案**

通过缩小答案的范围来求出答案，是对于这种无法直接求解的题的一种好方法。但是，很可惜，我们无法想到一个 $O(n)$ 的check。所以，报废。但是可以有 $O(n \log n)$ 的，大家可以来写一写。

那么真的不能直接做吗？其实可以，如果现在有一个数是确定下来的，另外两个数用贪心可以求出。我们设 $x\leq y\leq z$，那么我们枚举 $y$，用 STL 里的 lower_bound 和 upper_bound 就可以轻松找到最优的 $x,z$。但是，$x,y,z$ 的关系不知这一种，有 $P_3^3=6$ 种，所以我们还需要枚举一下 $x,y,z$ 的顺序。时间复杂度为 $O(6\cdot n \log n)\approx 6\times100000\times 17 =10200000$。给了 $3s$ 的时限，妥妥够了。~~POJ的老爷评测姬都够了（滑稽）。~~

Q1：为什么这样能找到最优解呢？  
A1：我们想象一下这个过程，相当于我们对于每一个数，找了最优解，那么相当于一个枚举，只不过，有章法，有顺序，有道理。

Q2：为什么要枚举 $y$，然后找一个不严格小于 $y$ 的数和不严格大于 $y$ 的数，而不是都找不严格小于的数呢？  
A2：我们再找 $x,z$ 的过程，和枚举 $x$，找到 $y,z$ 的过程是一样的。但是不能保证 $y,z$ 之间的大小关系，所以枚举不完整，会错。

Q3：给个代码好吗？  
A3：好的。

Q4：加个注释好吗？  
A4：不了，原因：1.锻炼自我的代码能力，一下代码仅供参考。~~2.我懒~~

### 如果需要注释，可以私信我哟~~

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

const int maxn=1e5+10,inf=0x7fffffffffffffff;

int n[3],c[3][maxn];

int calc(int x,int y,int z) {
	return (x-y)*(x-y)+(y-z)*(y-z)+(x-z)*(x-z);
}

signed main() {
	
	int t=read();
	while(t--) {
		for(int i=0;i<3;i++) {
			n[i]=read();
		}
		for(int i=0;i<3;i++) {
			for(int j=1;j<=n[i];j++) {
				c[i][j]=read();
			}
			sort(c[i],c[i]+n[i]+1);
		}
		int ans=inf;
		for(int i=0;i<3;i++) {
			for(int j=0;j<3;j++) {
				for(int k=0;k<3;k++) {
					if(i!=j&&j!=k&&i!=k) {
						for(int q=1;q<=n[i];q++) {
							int p1=lower_bound(c[j],c[j]+n[j]+1,c[i][q])-c[j];
							int p2=upper_bound(c[k],c[k]+n[k]+1,c[i][q])-c[k];
							if(p1!=n[j]+1&&p2!=1) {
								p2--;
								ans=min(ans,calc(c[i][q],c[j][p1],c[k][p2]));
							}
						}
					}
				}
			}
		}
		
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：Andrewzdm (赞：6)

**UPD**：分析了时间复杂度。修正了笔误（我太弱了把大于写成了小于……）

- - - -

# [CF1336B Xenia and Colorful Gems](https://www.luogu.com.cn/problem/CF1336B)

首先，很显然，要让 $(x-y)^2+(y-z)^2+(x-z)^2$ 的值尽可能小，$x,y,z$ 三个值就要尽可能接近。

于是我们考虑，枚举其中一种宝石的所有重量，然后在另外两种宝石的重量中找到最接近它的值，最后找到最小的答案。

为了便于枚举所有情况，我们可以确定下 $x,y,z$ 的大小关系然后进行枚举。  
举个栗子：当我们令 $x \le y \le z$ 时，我们可以先在第一个数组中枚举重量 $x$ ，在第二个数组中找到最接近 $x$ 且大于等于 $x$ 的值 $y$，在第三个数组中找到最接近 $y$ 且大于等于 $y$ 的值 $z$。然后计算答案，并在所有的答案中取最小值。

但是由于 $x,y,z$ 的大小关系不确定，我们需要枚举它们的 $6$ 种大小关系，分别是
$$x \le y \le z$$
$$x \le z \le y$$
$$y \le x \le z$$
$$y \le z \le x$$
$$z \le x \le y$$
$$z \le y \le x$$

当然，不管是用双指针还是二分都要先排序。

由于要多次用到相同的计算，不妨把枚举和计算的过程放到函数里。然后记得开 `long long`。

我的做法是双指针，所以没有用 `upper_bound` 和 `lower_bound`。

每次找较小值和较大值的部分时间复杂度是 $O(n)$ 的，排序的时间复杂度是 $O(n \log n)$，所以最终的时间复杂度是 $O(n \log n)$。

代码如下：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn = 1e5 + 5;
long long r[maxn], g[maxn], b[maxn];
long long ans;

long long calc(long long x, long long y, long long z)
{
	return (x-y)*(x-y)+(y-z)*(y-z)+(x-z)*(x-z);
}

void solve(long long *x, long long *y, long long *z, int nx, int ny, int nz)
{
	int p1 = 0, p2 = 0;
	for(int i = 1; i <= nx; i++)
	{
		while(p1 <= ny && y[p1] <= x[i]) p1++;  //找最接近的较小值
		while(p2 <= nz && z[p2] < x[i]) p2++;  //找最接近的较大值
		if(p1 - 1 != 0 && p2 != nz + 1)  //较小值和较大值都能找到
			ans = min(ans, calc(x[i], y[p1 - 1], z[p2]));
	}
	return;
}

void work()
{
	ans = 0x7fffffffffffffff;  //CF的C++11的编译器不支持<limits.h>中的LONG_LONG_MAX
	int nr, ng, nb;
	scanf("%d%d%d", &nr, &ng, &nb);
	for(int i = 1; i <= nr; i++) scanf("%lld", r + i);
	for(int i = 1; i <= ng; i++) scanf("%lld", g + i);
	for(int i = 1; i <= nb; i++) scanf("%lld", b + i);
	sort(r + 1, r + nr + 1);
	sort(g + 1, g + ng + 1);
	sort(b + 1, b + nb + 1);
   //枚举所有可能的大小关系
	solve(r, g, b, nr, ng, nb);
	solve(r, b, g, nr, nb, ng);
	solve(g, r, b, ng, nr, nb);
	solve(g, b, r, ng, nb, nr);
	solve(b, r, g, nb, nr, ng);
	solve(b, g, r, nb, ng, nr);
	printf("%lld\n", ans);
	return;
}

signed main()
{
	int T;
	scanf("%d", &T);
	while(T--)
		work();
	return 0;
}
```

---

## 作者：wsyhb (赞：6)

## 分析 + 题解

设取出来的三个数从小到大排序依次为 $x,y,z \; (x \le y \le z)$，由于 $\sum n_r,\sum n_g,\sum n_b \le 10^5$，显然需要枚举其中一个。

若枚举 $x$，最优的 $y,z$ 无法唯一确定。

**说明**：取最小的 $\ge x$ 的 $y$ 和最小的 $\ge y$ 的 $z$ 并不一定最优，因为有可能这样的 $y$ 和 $z$ 相差太大，还不如较大但相差较小的 $y,z$ 优。

若枚举 $z$，同理可以发现最优的 $x,y$ 无法唯一确定。

于是考虑枚举 $y$，此时最优的 $x$ 必为 $\le y$ 的最大的数，最优的 $z$ 必为 $\ge y$ 的最小的数。

**证明**：设 $a=y-x$，$b=z-y$，则 $a,b \ge 0$ 且 $z-x=a+b$，进一步有 $(x-y)^2+(y-z)^2+(z-x)^2=a^2+b^2+(a+b)^2$，显然 $a$ 和 $b$ 越小越优。

## 代码实现

先将三个数列排序，然后枚举上述 $x,y,z$ 分别属于哪个数列（共 $3!=6$ 种），并枚举 $y$，使用**二分查找**或**双指针**求得最优的 $x$ 和 $z$，更新答案即可。

尽管**二分查找**可以使用 STL 中的 `lower_bound` 和 `upper_bound`，但**双指针**并不会难写，且常数更小，因此下文代码使用**双指针**实现。~~轻轻松松最优解^_^~~

**时间复杂度**：$O(nlog_2n)$。（尽管可以使用**双指针**，但一开始也需要排序）

具体实现可以结合代码中的注释来理解。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+5;
int r[max_n],g[max_n],b[max_n];
inline long long get_ans(int a[],int na,int b[],int nb,int c[],int nc)//上述的 x 属于 a，y 属于 b，z 属于 c 
{
	long long res=4e18;//初始化为 inf，注意答案最大可能为 2e18，要开 long long 
	int i=1,j=1;//i 指向 a，j 指向 c 
	for(int k=1;k<=nb;++k)
	{
		int y=b[k];
		while(i<=na&&a[i]<=y)
			++i;
		if(i==1)//说明 a 中没有 <=y 的数 
			continue;
		int x=a[i-1];
		while(j<=nc&&c[j]<y)
			++j;
		if(j>nc)//说明 c 中没有 >=y 的数 
			break;
		int z=c[j];
		res=min(res,1ll*(x-y)*(x-y)+1ll*(y-z)*(y-z)+1ll*(z-x)*(z-x));//更新答案，记得加上 1ll 
	}
	return res;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int nr,ng,nb;
		scanf("%d%d%d",&nr,&ng,&nb);
		for(int i=1;i<=nr;++i)
			scanf("%d",r+i);
		sort(r+1,r+nr+1);//记得先排序 
		for(int i=1;i<=ng;++i)
			scanf("%d",g+i);
		sort(g+1,g+ng+1);
		for(int i=1;i<=nb;++i)
			scanf("%d",b+i);
		sort(b+1,b+nb+1);
		long long ans=get_ans(r,nr,g,ng,b,nb);
		ans=min(ans,get_ans(r,nr,b,nb,g,ng));
		ans=min(ans,get_ans(g,ng,r,nr,b,nb));
		ans=min(ans,get_ans(g,ng,b,nb,r,nr));
		ans=min(ans,get_ans(b,nb,r,nr,g,ng));
		ans=min(ans,get_ans(b,nb,g,ng,r,nr));//枚举六种情况 
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：奇米 (赞：4)

## $\mathrm{D.Xenia\ and \ Colorful\ Gems}$

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

####  **题目意思**
* [D](https://www.luogu.com.cn/problem/CF1336B)

####  $\mathrm{Sol}$
* 一道比较简单的题目，但是比赛时$fst$啦，赛后仔细想想开始想错了。
*  我们考虑一个简单的性质：就是如果选了$A$中的一个球$x$，那么$B,C$中想让答案小是不是只要试图去接近他就可以了。然后$B,C$同理。
* 这样我们就对$A,B,C$各自做一遍。然后找到对应另外两个中与他接近的（具体地看代码吧
* 时间复杂度：$O(k*n\log n)$,$k$为常数

####  $\mathrm{Code}$
```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=1e5+5;

int Q,na,nb,nc,ans;
int a[N],b[N],c[N];

inline int Calc(int x,int y,int z)
{
	return (x-y)*(x-y)+(z-x)*(z-x)+(y-z)*(y-z);
}

signed main()
{
	Q=read();
	for (;Q--;)
	{
		na=read(),nb=read(),nc=read();
		for ( int i=1;i<=na;i++ ) a[i]=read();
		for ( int i=1;i<=nb;i++ ) b[i]=read();
		for ( int i=1;i<=nc;i++ ) c[i]=read();
		sort(a+1,a+na+1);
		sort(b+1,b+nb+1);
		sort(c+1,c+nc+1);
		ans=1e19;
		for ( int i=1;i<=na;i++ )
		{
			int pb=upper_bound(b+1,b+nb+1,a[i])-b;//找到第一个比它大的
			int pc=upper_bound(c+1,c+nc+1,a[i])-c;
			int pbb=pb-1,pcc=pc-1;//找到最大的小于等于这个球的，下面同理
			if(pb<=nb)
			{
				if(pc<=nc) ans=min(ans,Calc(a[i],b[pb],c[pc]));
				if(pcc>=1) ans=min(ans,Calc(a[i],b[pb],c[pcc]));
			}
			if(pbb>=1)
			{
				if(pc<=nc) ans=min(ans,Calc(a[i],b[pbb],c[pc]));
				if(pcc>=1) ans=min(ans,Calc(a[i],b[pbb],c[pcc]));
			}
		}
		for ( int i=1;i<=nb;i++ )
		{
			int pa=upper_bound(a+1,a+na+1,b[i])-a;
			int pc=upper_bound(c+1,c+nc+1,b[i])-c;
			int paa=pa-1,pcc=pc-1;
			if(pa<=na)
			{
				if(pc<=nc) ans=min(ans,Calc(b[i],a[pa],c[pc]));
				if(pcc>=1) ans=min(ans,Calc(b[i],a[pa],c[pcc]));
			}
			if(paa>=1)
			{
				if(pc<=nc) ans=min(ans,Calc(b[i],a[paa],c[pc]));
				if(pcc>=1) ans=min(ans,Calc(b[i],a[paa],c[pcc]));
			}
		}
		for ( int i=1;i<=nc;i++ )
		{
			int pb=upper_bound(b+1,b+nb+1,c[i])-b;
			int pa=upper_bound(a+1,a+na+1,c[i])-a;
			int pbb=pb-1,paa=pa-1;
			if(pb<=nb)
			{
				if(pa<=na) ans=min(ans,Calc(c[i],b[pb],a[pa]));
				if(paa>=1) ans=min(ans,Calc(c[i],b[pb],a[paa]));
			}
			if(pbb>=1)
			{
				if(pa<=na) ans=min(ans,Calc(c[i],b[pbb],a[pa]));
				if(paa>=1) ans=min(ans,Calc(c[i],b[pbb],a[paa]));
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：gyh20 (赞：2)

我们假设最后选出的红绿蓝分别为 $x,y,z$。

先对三个数组排序。

假设 $x\leq y\leq z$

我们指针扫一遍，每次对于一个 $x$ 找到所有大于等于 $x$ 的但小于 $x$ 的下一个数的 $y$，再对于每一个找到下一个大于等于他的 $z$。

这样的复杂度是 $O(r+g+b)$ 的，但是并没有考虑完全，因为最后的答案不一定是  $x\leq y\leq z$。

但是，$x,y,z$ 的大小关系只有六种，我们显然可以枚举。

可以把一次计算放在函数里，减小代码量。

记得把答案上界开的足够大，开 long long 不用说了（要不然样例都过不了）。

```cpp
#include<cstdio>
#include<queue>
#include<algorithm>
#include<iostream>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
inline int sqr(re int x){
	return x*x;
}
inline int calc(re int *a,re int* b,re int* c,re int ra,re int rb,re int rc){
	re int l=1,r=1,ans=6e18;a[ra+1]=1e18;
	for(re int i=1;i<=ra;++i){
		while(b[l]<a[i+1]&&l<=rb){
		if(l>rb)return ans;
		while(c[r]<b[l]&&r<=rc)++r;if(r>rc)return ans;
		ans=min(ans,sqr(a[i]-b[l])+sqr(a[i]-c[r])+sqr(b[l]-c[r]));++l;}
	}
	
	return ans;
}
int t,n,m,a[100002],b[100002],c[100002],ra,rb,rc;
signed main(){
	t=read();
	while(t--){
		ra=read();rb=read();rc=read();
		for(re int i=1;i<=ra;++i)a[i]=read();
		for(re int i=1;i<=rb;++i)b[i]=read();
		for(re int i=1;i<=rc;++i)c[i]=read();
		sort(a+1,a+ra+1);sort(b+1,b+rb+1);sort(c+1,c+rc+1);
		re int ans=6e18;
		ans=min(ans,calc(a,b,c,ra,rb,rc));
		ans=min(ans,calc(a,c,b,ra,rc,rb));
		ans=min(ans,calc(b,a,c,rb,ra,rc));
		ans=min(ans,calc(b,c,a,rb,rc,ra));
		ans=min(ans,calc(c,a,b,rc,ra,rb));
		ans=min(ans,calc(c,b,a,rc,rb,ra));
		printf("%lld\n",ans);
	}
}
```



---

## 作者：_xbn (赞：1)

我们会发现一个很显然的性质：选出的 $3$ 个数数值越接近，答案就会越小。

于是我们可以先枚举其中一个数，再从另外两个数组中二分找到与它最接近的两个数，计算答案取最小值即可。

由于二分需要具有单调性，所以要记得给三个数组排序。

为了保证不漏算，最好三个数组都做一遍。

复杂度 $O(n\log_n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;
const int N = 200002;
int n, m, l, r, p, t, k, ans, sum, tot, cnt, a[N], b[N], c[N], d[N], f[N], lst[N], pos, R, G, B;
inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9')
	{
		x = x * 10 + ch - '0';
		ch = getchar();
	}
	return x * f;
}
int calc(int x, int y, int z)
{
	return (x - y) * (x - y) + (y - z) * (y - z) + (z - x) * (z - x);
}
signed main()
{
	int T = read();
	while (T--)
	{
		R = read(); G = read(); B = read(); ans = 6e18;
		for (int i = 1; i <= R; i++) a[i] = read();
		sort(a + 1, a + R + 1);
		for (int i = 1; i <= G; i++) b[i] = read();
		sort(b + 1, b + G + 1);
		for (int i = 1; i <= B; i++) c[i] = read();
		sort(c + 1, c + B + 1);
		for (int i = 1; i <= R; i++)
		{
			t = lower_bound(b + 1, b + G + 1, a[i]) - b;
			p = lower_bound(c + 1, c + B + 1, a[i]) - c;
			if(t > G && p > B) { ans = min(ans, calc(a[i], b[t - 1], c[p - 1])); continue; }
			if(t > G) t--;
			if(p > B) p--;
			if(t == 1 && p == 1)  { ans = min(ans, calc(a[i], b[1], c[1])); continue; }
			if(t == 1) { ans = min(ans, min(calc(a[i], b[1], c[p - 1]), calc(a[i], b[1], c[p]))); continue; }
			if(p == 1) { ans = min(ans, min(calc(a[i], b[t - 1], c[p]), calc(a[i], b[t], c[p]))); continue; }
			ans = min(ans, calc(a[i], b[t - 1], c[p - 1]));
			ans = min(ans, calc(a[i], b[t - 1], c[p]));
			ans = min(ans, calc(a[i], b[t], c[p - 1]));
			ans = min(ans, calc(a[i], b[t], c[p]));
		}
		for (int i = 1; i <= G; i++)
		{
			t = lower_bound(a + 1, a + R + 1, b[i]) - a;
			p = lower_bound(c + 1, c + B + 1, b[i]) - c;
			if(t > R && p > B) { ans = min(ans, calc(a[t - 1], b[i], c[p - 1])); continue; }
			if(t > R) t--;
			if(p > B) p--;
			if(t == 1 && p == 1)  { ans = min(ans, calc(a[1], b[i], c[1])); continue; }
			if(t == 1) { ans = min(ans, min(calc(a[1], b[i], c[p - 1]), calc(a[1], b[i], c[p]))); continue; }
			if(p == 1) { ans = min(ans, min(calc(a[t - 1], b[i], c[p]), calc(a[t], b[i], c[p]))); continue; }
			ans = min(ans, calc(a[t - 1], b[i], c[p - 1]));
			ans = min(ans, calc(a[t - 1], b[i], c[p]));
			ans = min(ans, calc(a[t], b[i], c[p - 1]));
			ans = min(ans, calc(a[t], b[i], c[p]));
		}
		for (int i = 1; i <= B; i++)
		{
			t = lower_bound(b + 1, b + G + 1, c[i]) - b;
			p = lower_bound(a + 1, a + R + 1, c[i]) - a;
			if(t > G && p > R) { ans = min(ans, calc(a[p - 1], b[t - 1], c[i])); continue; }
			if(t > G) t--;
			if(p > R) p--;
			if(t == 1 && p == 1)  { ans = min(ans, calc(a[1], b[1], c[i])); continue; }
			if(t == 1) { ans = min(ans, min(calc(a[p - 1], b[1], c[i]), calc(a[p], b[1], c[i]))); continue; }
			if(p == 1) { ans = min(ans, min(calc(a[p], b[t - 1], c[i]), calc(a[p], b[t], c[i]))); continue; }
			ans = min(ans, calc(a[p - 1], b[t - 1], c[i]));
			ans = min(ans, calc(a[p], b[t - 1], c[i]));
			ans = min(ans, calc(a[p - 1], b[t], c[i]));
			ans = min(ans, calc(a[p], b[t], c[i]));
		}
		cout << ans << endl;
	}
	return 0;
}
```




---

## 作者：little_sun (赞：1)

### 题目大意

你有$3$个数组，分别是$\texttt{r, g, b}$，长度分别是$n_r, n_b, n_g$

你需要在这三个数组中选择一个数，设你选择的三个数为$x, y, z$，则你要使$(x-y)^2+(y-z)^2+(z-x)^2$最小

多组数据，$1 \leq n_r, n_b, n_g \leq 10^5$，值域$1 \leq r_i, b_i, g_i \leq 10^9$

### 分析

首先我们考虑枚举其中一个数，假设我们枚举的是$r$数组。

对于一个数$x$，在某一个数组（假设是$z$）满足$(x-y)^2$最小的$y$一定是$x$在$z$内的前驱或后继。

于是对于每一个$r_i$，我们找到$r_i$在$g$中的前驱和后继，记为$gr_0, gr_1$，再找到$gr_0, gr_1$在$b$里的前驱后继，记为$bl_0, bl_1, bl_2, bl_3$，那么答案就在$f(r_i, gr_0, bl_0), f(r_i, gr_0, bl_1), \cdots, f(r_i, gr_1, bl_3)$中。（其中$f(x, y, z)$表示$1 \leq n_r, n_b, n_g \leq 10^5$）

但是这种可能会有缺漏， 我们可能漏掉了某些情况，例如下面这个例子

``` plain
1
2 2 2
1 2
3 4
6 7
```

。我们会选择$2, 3, 6$而正确答案应该是$2, 4, 6$。

于是，我们考虑对$r, g, b$都做一遍上面这个过程，就能得到正确的答案了。

时间复杂度$\mathcal{O}(n \log n)$

### 代码

``` cpp
#include <bits/stdc++.h>

#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)

const int Max = 2e9;
const int Min = -1e9;
const int MaxN = 2e5 + 10;

ll n, m, k, ans;
std::set<ll> R, G, B;
ll r[MaxN], g[MaxN], b[MaxN];

ll sqr(ll x) { return x * x; }

ll sub(ll x, std::set<ll> &y)
{
    if (x == 2000000000) return x;
    return *y.upper_bound(x);
}

ll pre(ll x, std::set<ll> &y)
{
    ll res = *y.lower_bound(x);
    if (x == -1000000000) return x;
    if (res > x) res = *(--y.lower_bound(x));
    return res;
}

void init()
{
    ans = 0x7f7f7f7f7f7f7f7fll;
    R.clear(), R.insert(-1e9), R.insert(2e9);
    G.clear(), G.insert(-1e9), G.insert(2e9);
    B.clear(), B.insert(-1e9), B.insert(2e9);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        init();
        scanf("%lld%lld%lld", &n, &m, &k);
        for (int i = 1; i <= n; i++)
            scanf("%lld", &r[i]), R.insert(r[i]);
        for (int i = 1; i <= m; i++)
            scanf("%lld", &g[i]), G.insert(g[i]);
        for (int i = 1; i <= k; i++)
            scanf("%lld", &b[i]), B.insert(b[i]);
        for (int i = 1; i <= n; i++)
        {
            ll gr[2] = {}, bl[4] = {};
            gr[0] = pre(r[i], G), gr[1] = sub(r[i], G);
            bl[0] = pre(gr[0], B), bl[1] = sub(gr[0], B);
            bl[2] = pre(gr[1], B), bl[3] = sub(gr[1], B);
            for (int j = 0; j < 2; j++)
            {
                for (int l = 0; l < 4; l++)
                    if (gr[j] != Max && gr[j] != Min && bl[l] != Max && bl[l] != Min)
                        ans = std::min(ans, sqr(r[i] - gr[j]) + sqr(gr[j] - bl[l]) + sqr(bl[l] - r[i]));
            }
        }
        for (int i = 1; i <= m; i++)
        {
            ll gr[2] = {}, bl[4] = {};
            gr[0] = pre(g[i], R), gr[1] = sub(g[i], R);
            bl[0] = pre(gr[0], B), bl[1] = sub(gr[0], B);
            bl[2] = pre(gr[1], B), bl[3] = sub(gr[1], B);
            for (int j = 0; j < 2; j++)
            {
                for (int l = 0; l < 4; l++)
                    if (gr[j] != Max && gr[j] != Min && bl[l] != Max && bl[l] != Min)
                        ans = std::min(ans, sqr(g[i] - gr[j]) + sqr(gr[j] - bl[l]) + sqr(bl[l] - g[i]));
            }
        }
        for (int i = 1; i <= k; i++)
        {
            ll gr[2] = {}, bl[4] = {};
            gr[0] = pre(b[i], R), gr[1] = sub(b[i], R);
            bl[0] = pre(gr[0], G), bl[1] = sub(gr[0], G);
            bl[2] = pre(gr[1], G), bl[3] = sub(gr[1], G);
            for (int j = 0; j < 2; j++)
            {
                for (int l = 0; l < 4; l++)
                    if (gr[j] != Max && gr[j] != Min && bl[l] != Max && bl[l] != Min)
                        ans = std::min(ans, sqr(b[i] - gr[j]) + sqr(gr[j] - bl[l]) + sqr(bl[l] - b[i]));
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```





---

## 作者：1saunoya (赞：1)

大概是赛时秒了这题，但是结论没怎么好好证明。

你考虑你选了一个 $a$，那么你最大的一定会是 $b,c$ 一定是在比 $a$ 小的最大的那个和比 $a$ 大的最小的那个，然后更新四次。

然后我们发现这样的贪心是比较正确的，但是你有的 $b$ 和有的 $c$ 没有枚举到，为了避免没有选到的 $b/c$ 是正确点
~~（其实是我写完之后发现有个样例没对）~~

然后就可以对 $b$ 和 $c$ 重复 $a$ 的这个操作，就可以过了.jpg

细节写的比较多…自闭了。

```cpp
// powered by c++11
// by Isaunoya
#include <bits/stdc++.h>

#define rep(i, x, y) for (register int i = (x); i <= (y); ++i)
#define Rep(i, x, y) for (register int i = (x); i >= (y); --i)

using namespace std;
using db = double;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

#define pii pair<int, int>
#define fir first
#define sec second

template <class T>

void cmax(T& x, const T& y) {
  if (x < y) x = y;
}

template <class T>

void cmin(T& x, const T& y) {
  if (x > y) x = y;
}

#define all(v) v.begin(), v.end()
#define sz(v) ((int)v.size())
#define pb emplace_back

template <class T>

void sort(vector<T>& v) {
  sort(all(v));
}

template <class T>

void reverse(vector<T>& v) {
  reverse(all(v));
}

template <class T>

void unique(vector<T>& v) {
  sort(all(v)), v.erase(unique(all(v)), v.end());
}

void reverse(string& s) { reverse(s.begin(), s.end()); }

const int io_size = 1 << 23 | 233;
const int io_limit = 1 << 22;
struct io_in {
  char ch;
#ifndef __WIN64
  char getchar() {
    static char buf[io_size], *p1 = buf, *p2 = buf;

    return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, io_size, stdin), p1 == p2) ? EOF : *p1++;
  }
#endif
  io_in& operator>>(char& c) {
    for (c = getchar(); isspace(c); c = getchar());

    return *this;
  }
  io_in& operator>>(string& s) {
    for (s.clear(); isspace(ch = getchar());)
      ;

    if (!~ch) return *this;

    for (s = ch; !isspace(ch = getchar()) && ~ch; s += ch)
      ;

    return *this;
  }

  io_in& operator>>(char* str) {
    char* cur = str;
    while (*cur) *cur++ = 0;

    for (cur = str; isspace(ch = getchar());)
      ;
    if (!~ch) return *this;

    for (*cur = ch; !isspace(ch = getchar()) && ~ch; *++cur = ch)
      ;

    return *++cur = 0, *this;
  }

  template <class T>

  void read(T& x) {
    bool f = 0;
    while ((ch = getchar()) < 48 && ~ch) f ^= (ch == 45);

    x = ~ch ? (ch ^ 48) : 0;
    while ((ch = getchar()) > 47) x = x * 10 + (ch ^ 48);
    x = f ? -x : x;
  }

  io_in& operator>>(int& x) { return read(x), *this; }

  io_in& operator>>(ll& x) { return read(x), *this; }

  io_in& operator>>(uint& x) { return read(x), *this; }

  io_in& operator>>(ull& x) { return read(x), *this; }

  io_in& operator>>(db& x) {
    read(x);
    bool f = x < 0;
    x = f ? -x : x;
    if (ch ^ '.') return *this;

    double d = 0.1;
    while ((ch = getchar()) > 47) x += d * (ch ^ 48), d *= .1;
    return x = f ? -x : x, *this;
  }
} in;

struct io_out {
  char buf[io_size], *s = buf;
  int pw[233], st[233];

  io_out() {
    set(7);
    rep(i, pw[0] = 1, 9) pw[i] = pw[i - 1] * 10;
  }

  ~io_out() { flush(); }

  void io_chk() {
    if (s - buf > io_limit) flush();
  }

  void flush() { fwrite(buf, 1, s - buf, stdout), fflush(stdout), s = buf; }

  io_out& operator<<(char c) { return *s++ = c, *this; }

  io_out& operator<<(string str) {
    for (char c : str) *s++ = c;
    return io_chk(), *this;
  }

  io_out& operator<<(char* str) {
    char* cur = str;
    while (*cur) *s++ = *cur++;
    return io_chk(), *this;
  }

  template <class T>

  void write(T x) {
    if (x < 0) *s++ = '-', x = -x;

    do {
      st[++st[0]] = x % 10, x /= 10;
    } while (x);

    while (st[0]) *s++ = st[st[0]--] ^ 48;
  }

  io_out& operator<<(int x) { return write(x), io_chk(), *this; }

  io_out& operator<<(ll x) { return write(x), io_chk(), *this; }

  io_out& operator<<(uint x) { return write(x), io_chk(), *this; }

  io_out& operator<<(ull x) { return write(x), io_chk(), *this; }

  int len, lft, rig;

  void set(int _length) { len = _length; }

  io_out& operator<<(db x) {
    bool f = x < 0;
    x = f ? -x : x, lft = x, rig = 1. * (x - lft) * pw[len];
    return write(f ? -lft : lft), *s++ = '.', write(rig), io_chk(), *this;
  }
} out;
#define int long long

template <int sz, int mod>

struct math_t {
	math_t() {
    fac.resize(sz + 1), ifac.resize(sz + 1);
    rep(i, fac[0] = 1, sz) fac[i] = fac[i - 1] * i % mod;

    ifac[sz] = inv(fac[sz]);
    Rep(i, sz - 1, 0) ifac[i] = ifac[i + 1] * (i + 1) % mod;
  }

  vector<int> fac, ifac;

  int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = x * x % mod)
      if (y & 1) ans = ans * x % mod;
    return ans;
  }

  int inv(int x) { return qpow(x, mod - 2); }

  int C(int n, int m) {
    if (n < 0 || m < 0 || n < m) return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
  }
};

int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
int lcm(int x, int y) { return x * y / gcd(x, y); }

const int inf = 2e9;
signed main() {
  // code begin.
	int _;
	in >> _;
	while(_ --) {
		set < int > a , b , c;
		int n1, n2, n3;
		in >> n1 >> n2 >> n3;
		a.insert(-inf), b.insert(-inf), c.insert(-inf);
		for(int i = 0 ; i < n1 ; i ++) {
			int x;
			in >> x;
			a.insert(x);
		}
		for(int i = 0 ; i < n2 ; i ++) {
			int x;
			in >> x;
			b.insert(x);
		}
		for(int i = 0 ; i < n3 ; i ++) {
			int x;
			in >> x;
			c.insert(x);
		}
		a.insert(inf), b.insert(inf), c.insert(inf);
		int mn = 9e18;
		for(int x : a){
			if(x == inf || x == -inf) continue;
			auto it = b.upper_bound(x);
			auto it2 = it; -- it;
			auto it3 = c.upper_bound(x);
			auto it4 = it3; -- it3;
			if(*it != inf && *it3 != inf) 
			if(*it != -inf && *it3 != -inf)
				cmin(mn, (x - *it) * (x - *it) + (x - *it3) * (x - *it3) + (*it - *it3) * (*it - *it3));
			if(*it2 != inf && *it3 != inf) 
			if(*it2 != -inf && *it3 != -inf) 
				cmin(mn, (x - *it2) * (x - *it2) + (x - *it3) * (x - *it3) + (*it2 - *it3) * (*it2 - *it3));
			if(*it != inf && *it4 != inf) 
			if(*it != -inf && *it4 != -inf) 
				cmin(mn, (x - *it) * (x - *it) + (x - *it4) * (x - *it4) + (*it - *it4) * (*it - *it4));
			if(*it2 != inf && *it4 != inf) 
			if(*it2 != -inf && *it4 != -inf) 
				cmin(mn, (x - *it2) * (x - *it2) + (x - *it4) * (x - *it4) + (*it2 - *it4) * (*it2 - *it4));
		}
		for(int x : b){
			if(x == inf || x == -inf) continue;
			auto it = a.upper_bound(x);
			auto it2 = it; -- it;
			auto it3 = c.upper_bound(x);
			auto it4 = it3; -- it3;
			if(*it != inf && *it3 != inf) 
			if(*it != -inf && *it3 != -inf)
				cmin(mn, (x - *it) * (x - *it) + (x - *it3) * (x - *it3) + (*it - *it3) * (*it - *it3));
			if(*it2 != inf && *it3 != inf) 
			if(*it2 != -inf && *it3 != -inf) 
				cmin(mn, (x - *it2) * (x - *it2) + (x - *it3) * (x - *it3) + (*it2 - *it3) * (*it2 - *it3));
			if(*it != inf && *it4 != inf) 
			if(*it != -inf && *it4 != -inf) 
				cmin(mn, (x - *it) * (x - *it) + (x - *it4) * (x - *it4) + (*it - *it4) * (*it - *it4));
			if(*it2 != inf && *it4 != inf) 
			if(*it2 != -inf && *it4 != -inf) 
				cmin(mn, (x - *it2) * (x - *it2) + (x - *it4) * (x - *it4) + (*it2 - *it4) * (*it2 - *it4));
		}
		for(int x : c) {
			if(x == inf || x == -inf) continue;
			auto it = a.upper_bound(x);
			auto it2 = it; -- it;
			auto it3 = b.upper_bound(x);
			auto it4 = it3; -- it3;
			if(*it != inf && *it3 != inf) 
			if(*it != -inf && *it3 != -inf)
				cmin(mn, (x - *it) * (x - *it) + (x - *it3) * (x - *it3) + (*it - *it3) * (*it - *it3));
			if(*it2 != inf && *it3 != inf)
			if(*it2 != -inf && *it3 != -inf) 
				cmin(mn, (x - *it2) * (x - *it2) + (x - *it3) * (x - *it3) + (*it2 - *it3) * (*it2 - *it3));
			if(*it != inf && *it4 != inf) 
			if(*it != -inf && *it4 != -inf) 
				cmin(mn, (x - *it) * (x - *it) + (x - *it4) * (x - *it4) + (*it - *it4) * (*it - *it4));
			if(*it2 != inf && *it4 != inf) 
			if(*it2 != -inf && *it4 != -inf) 
				cmin(mn, (x - *it2) * (x - *it2) + (x - *it4) * (x - *it4) + (*it2 - *it4) * (*it2 - *it4));
		}
		out << mn << '\n';
	}
  return 0;
  // code end.
}
```

---

## 作者：Tx_Lcy (赞：0)

思路非常简单，但是实现略复杂。

## 思路
在三个数：$x,y,z$ 中，我们不妨设 $x \le y \le z$ 或 $z \le y \le x$。我们把三个序列**从左往右扫一遍**，枚举每个数作为 $y$ 时的答案，我们发现这时有**两种情况**，**一种是 $x<z$，一种是 $x>z$，我们分别计算**，最后所有答案取**最小值**即可。

当我们确定 $y$ 时，可以在另外两个数列中分别二分查找第一个小于等于 $y$ 的数和第一个大于等于 $y$ 的数，就可以计算答案。
## 冗长的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
int const N=1e5+10;
int r[N],g[N],b[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    int t;cin>>t;
    while (t--){
    	int nr,ng,nb,ans=9e18;
    	memset(r,0,sizeof(r));
    	memset(g,0,sizeof(g));
    	memset(b,0,sizeof(b));//一定要清空，不然会答案错误
		cin>>nr>>ng>>nb;
    	for (rint i=1;i<=nr;++i) cin>>r[i];
    	sort(r+1,r+nr+1);//排序后才可以使用 lower_bound 函数
    	for (rint i=1;i<=ng;++i) cin>>g[i];
    	sort(g+1,g+ng+1);
    	for (rint i=1;i<=nb;++i) cin>>b[i];
    	sort(b+1,b+nb+1);
        for (rint i=1;i<=nr;++i){
        	int f=lower_bound(g+1,g+ng+1,r[i])-g,l=lower_bound(b+1,b+nb+1,r[i])-b;
		    int xf=f,xl=l;
		    if (g[f]!=r[i] && f!=1) --f;
		    ans=min(ans,(r[i]-g[f])*(r[i]-g[f])+(b[l]-r[i])*(b[l]-r[i])+(b[l]-g[f])*(b[l]-g[f]));//第一种情况
		    if (b[xl]!=r[i] && xl!=1) --xl;
		    f=xf,l=xl;
		    ans=min(ans,(r[i]-g[f])*(r[i]-g[f])+(b[l]-r[i])*(b[l]-r[i])+(b[l]-g[f])*(b[l]-g[f]));//第二种情况
		}
		for (rint i=1;i<=ng;++i){
			int f=lower_bound(r+1,r+nr+1,g[i])-r,l=lower_bound(b+1,b+nb+1,g[i])-b;
		    int xf=f,xl=l;
		    if (r[f]!=g[i] && f!=1) --f;
		    ans=min(ans,(r[f]-g[i])*(r[f]-g[i])+(b[l]-r[f])*(b[l]-r[f])+(b[l]-g[i])*(b[l]-g[i]));
		    if (b[xl]!=g[i] && xl!=1) --xl;
		    f=xf,l=xl;
		    ans=min(ans,(r[f]-g[i])*(r[f]-g[i])+(b[l]-r[f])*(b[l]-r[f])+(b[l]-g[i])*(b[l]-g[i]));
		}
		for (rint i=1;i<=nb;++i){
			int f=lower_bound(r+1,r+nr+1,b[i])-r,l=lower_bound(g+1,g+ng+1,b[i])-g;
		    int xf=f,xl=l;
		    if (r[f]!=b[i] && f!=1) --f;
		    ans=min(ans,(r[f]-g[l])*(r[f]-g[l])+(b[i]-r[f])*(b[i]-r[f])+(b[i]-g[l])*(b[i]-g[l]));
		    if (b[i]!=g[xl] && xl!=1) --xl;
		    f=xf,l=xl;
		    ans=min(ans,(r[f]-g[l])*(r[f]-g[l])+(b[i]-r[f])*(b[i]-r[f])+(b[i]-g[l])*(b[i]-g[l]));
		}
		cout<<ans<<'\n';
	}
    return 0;
}
```


---

## 作者：konnyaku_cstdio (赞：0)

# CF1336B 【Xenia and Colorful Gems】

首先题意很简单请见[翻译里面](https://www.luogu.com.cn/problem/CF1336B)。

然后从数据范围中可以看出

$ n_{r} \leq 10^5,n_{g} \leq 10^5,n_{b} \leq 10^5  $

所以复杂度得控制在 $ O( n \log n)$且最多乘以常数

于是我们考虑二分

### 过程
对于每个数组里的每个数 base，可以在另外两个数组里面分别寻找最接近它的两个数。为了方便查找，既保证查找过程单调，需要提前给三个数组 r,g,b 排序，复杂度 $ O(n \log n)$。设第一个数组里找到的最接近 base 的两个数是 t1,t2 第二个数组里最接近 base 的是 s1,s2 。如果 ti 和 si 都真实存在且合法，并且

$ (base-si)^2 +(base-ti)^2+(ti-si)^2 \leq ans$

那么我们我们更新 ans 。

### 细节

**此部分非常重要！！！**

- 注意二分结束后的上界 rt 和下界 lf，比如以下的样例中你就会发现对于 base=5 的时候，二分第一个数组可能会出现 lf 或者 rt 越界，具体取决于你的代码：
	```cpp
	1
	3 3 3
	1 2 3
	4 5 6
	7 8 9
	```
- 注意每次进行完一个测试数据，既下面代码里面 t-- 的时候务必要初始化所有的数组避免干扰
- 一定要把ans初始化成 $2^{63}-1$，因为~~你哪里知道出题人有多坑呢~~
## code

```
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;
ll rn,gn,bn,t,t1,t2,s1,s2,lstmid=-1;
long long ans;
ll lf,rt,mid;
ll r[100001],b[100001],g[100001];
void part(ll sz[],ll base,ll size){
	lf=1,rt=size,lstmid=-1;
	while(lf<=rt){
		mid=(lf+rt)>>1;
		if(sz[mid]==base){
			t1=sz[mid];
			t2=sz[mid+1];
			goto tagg;
		}
		if(sz[mid]>base)
			rt=mid-1;
		else
			lf=mid+1;
	}
	if(lf>size)
		lf-=1;
	if(lf<=0)
		lf+=1;
		if(sz[lf]>base){
			t2=sz[lf];
			t1=sz[lf-1];
		}
		else{
			t2=sz[lf+1];
			t1=sz[lf];
		}
	tagg:;
	return;
}
void part1(ll sz[],ll base,ll size){
	lf=1,rt=size;
	while(lf<=rt){
		mid=(lf+rt)>>1;
		if(sz[mid]==base){
			s1=sz[mid];
			s2=sz[mid+1];
			goto tag;
		}
		if(sz[mid]>base)
			rt=mid-1;
		else
			lf=mid+1;
	}
	if(lf<=0)
		lf+=1;
	if(lf>size)
		lf-=1;
		if(sz[lf]>base){
			s2=sz[lf];
			s1=sz[lf-1];
		}
		else{
			s2=sz[lf+1];
			s1=sz[lf];
		}
	tag:;
	return;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		ans=(1<<30);
		ans=ans*ans;
		ans=ans*4;
		ans+=(ans-1);
		scanf("%lld%lld%lld",&rn,&gn,&bn);
		for(int i=1;i<=rn;i++){
			scanf("%lld",&r[i]);
		}
		for(int i=1;i<=gn;i++){
			scanf("%lld",&g[i]);
		}
		for(int i=1;i<=bn;i++){
			scanf("%lld",&b[i]);
		}
		sort(r+1,r+1+rn);
		sort(g+1,g+1+gn);
		sort(b+1,b+1+bn);
		for(int i=1;i<=rn;i++){
			t1=t2=s1=s2=0;
			part(g,r[i],gn);
			part1(b,r[i],bn);
			if(t1){
				if(s1)
				ans=min(ans,(t1-r[i])*(t1-r[i])+(s1-r[i])*(s1-r[i])+(t1-s1)*(t1-s1));
				if(s2)
				ans=min(ans,(t1-r[i])*(t1-r[i])+(s2-r[i])*(s2-r[i])+(t1-s2)*(t1-s2));
			}
			if(t2){
				if(s1)
				ans=min(ans,(t2-r[i])*(t2-r[i])+(s1-r[i])*(s1-r[i])+(t2-s1)*(t2-s1));
				if(s2)
				ans=min(ans,(t2-r[i])*(t2-r[i])+(s2-r[i])*(s2-r[i])+(t2-s2)*(t2-s2));
			}
		}
		for(int i=1;i<=gn;i++){
			t1=t2=s1=s2=0;
			part(r,g[i],rn);
			part1(b,g[i],bn);
			if(t1){
				if(s1)
				ans=min(ans,(t1-g[i])*(t1-g[i])+(s1-g[i])*(s1-g[i])+(t1-s1)*(t1-s1));
				if(s2)
				ans=min(ans,(t1-g[i])*(t1-g[i])+(s2-g[i])*(s2-g[i])+(t1-s2)*(t1-s2));
			}
			if(t2){
				if(s1)
				ans=min(ans,(t2-g[i])*(t2-g[i])+(s1-g[i])*(s1-g[i])+(t2-s1)*(t2-s1));
				if(s2)
				ans=min(ans,(t2-g[i])*(t2-g[i])+(s2-g[i])*(s2-g[i])+(t2-s2)*(t2-s2));
			}
		}
		for(int i=1;i<=bn;i++){
			t1=t2=s1=s2=0;
			part(r,b[i],rn);
			part1(g,b[i],gn);
			if(t1){
				if(s1)
				ans=min(ans,(t1-b[i])*(t1-b[i])+(s1-b[i])*(s1-b[i])+(t1-s1)*(t1-s1));
				if(s2)
				ans=min(ans,(t1-b[i])*(t1-b[i])+(s2-b[i])*(s2-b[i])+(t1-s2)*(t1-s2));
			}
			if(t2){
				if(s1)
				ans=min(ans,(t2-b[i])*(t2-b[i])+(s1-b[i])*(s1-b[i])+(t2-s1)*(t2-s1));
				if(s2)
				ans=min(ans,(t2-b[i])*(t2-b[i])+(s2-b[i])*(s2-b[i])+(t2-s2)*(t2-s2));
			}
			
		}
		printf("%lld\n",ans);
		for(int i=1;i<=rn;i++)
			r[i]=0;
		for(int i=1;i<=gn;i++)
			g[i]=0;
		for(int i=1;i<=bn;i++)
			b[i]=0;
	}
	
	return 0;
}
```


---

## 作者：Meatherm (赞：0)

花了一个多小时才做出来这题...读错题了一个半小时，太自闭了。

容易发现，当确定了取的三个数 $x,y,z$ 中的任意两个时，第三个数就随之确定：例如，当 $x,y$ 确定时，$z$ 一定是 $b$ 数组中 $\dfrac {x+y}{2}$ 的一个不严格前驱 / 后继。

显然，当 $x$ 确定时，$y$ 取 $x$ 在 $g$ 数组中的不严格前驱 / 后继最优。

所以我们得到了一个算法：在 $r$ 数组中枚举 $x$，求出 $x$ 在 $g$ 数组中的不严格前驱 / 后继作为 $y$，并求出 $\dfrac {x+y}{2}$ 在 $b$ 数组中的不严格前驱 / 后继作为 $z$。

但容易发现，不一定是由 $x,y$ 确定推算出 $z$，还有可能是 $x,z$ 确定推算出 $y$。和上面的情况几乎完全一致，不再赘述。

```cpp
# include <bits/stdc++.h>
# define rr register
# define int long long
const int N=500010,INF=6e18;
int a[N],b[N],c[N];
int asize,bsize,csize;
int T;
int minx;
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
inline int nxt(int *ar,int size,int x){ // 不严格后继是第一个 >= 它的数
	int ans=std::lower_bound(ar+1,ar+1+size,x)-ar;
	if(ans>size) // 小心越界...找不到一定要返回 0
		return 0;
	return ar[ans];
}
inline int pre(int *ar,int size,int x){ // 不严格前驱是最后一个 <= 它的数
	int ans=std::upper_bound(ar+1,ar+1+size,x)-ar-1;
	if(ans>size||ans<1) // 同上
		return 0;
	return ar[ans];	
}
inline int p(int x){
	return x*x;
}
inline void cmin(int x,int y,int z){
	if(x&&y&&z)
		minx=std::min(minx,p(x-y)+p(y-z)+p(z-x));
	return;
}
signed main(void){
	T=read();
	while(T--){
		asize=read(),bsize=read(),csize=read();
		for(rr int i=1;i<=asize;++i){
			a[i]=read();
		}
		for(rr int i=1;i<=bsize;++i){
			b[i]=read();
		}
		for(rr int i=1;i<=csize;++i){
			c[i]=read();
		}
		std::sort(a+1,a+1+asize);
		std::sort(b+1,b+1+bsize);
		std::sort(c+1,c+1+csize);
		minx=INF; // INF 一定要开得极大 样例中已经提示了
		for(rr int i=1;i<=asize;++i){
			int va=nxt(b,bsize,a[i]),vb=pre(b,bsize,a[i]);
			cmin(a[i],va,nxt(c,csize,(a[i]+va)/2));
			cmin(a[i],va,pre(c,csize,(a[i]+va)/2));
			cmin(a[i],vb,nxt(c,csize,(a[i]+vb)/2));
			cmin(a[i],vb,pre(c,csize,(a[i]+vb)/2));
			va=nxt(c,csize,a[i]),vb=pre(c,csize,a[i]);
			cmin(a[i],nxt(b,bsize,(a[i]+va)/2),va);
			cmin(a[i],pre(b,bsize,(a[i]+va)/2),va);
			cmin(a[i],nxt(b,bsize,(a[i]+vb)/2),vb);
			cmin(a[i],pre(b,bsize,(a[i]+vb)/2),vb);
		}
		std::cout<<minx<<std::endl;
	}

	return 0;
}

```

---

