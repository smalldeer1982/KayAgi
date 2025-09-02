# The Hard Work of Paparazzi

## 题目描述

You are a paparazzi working in Manhattan.

Manhattan has $ r $ south-to-north streets, denoted by numbers $ 1, 2,\ldots, r $ in order from west to east, and $ r $ west-to-east streets, denoted by numbers $ 1,2,\ldots,r $ in order from south to north. Each of the $ r $ south-to-north streets intersects each of the $ r $ west-to-east streets; the intersection between the $ x $ -th south-to-north street and the $ y $ -th west-to-east street is denoted by $ (x, y) $ . In order to move from the intersection $ (x,y) $ to the intersection $ (x', y') $ you need $ |x-x'|+|y-y'| $ minutes.

You know about the presence of $ n $ celebrities in the city and you want to take photos of as many of them as possible. More precisely, for each $ i=1,\dots, n $ , you know that the $ i $ -th celebrity will be at the intersection $ (x_i, y_i) $ in exactly $ t_i $ minutes from now (and he will stay there for a very short time, so you may take a photo of him only if at the $ t_i $ -th minute from now you are at the intersection $ (x_i, y_i) $ ). You are very good at your job, so you are able to take photos instantaneously. You know that $ t_i < t_{i+1} $ for any $ i=1,2,\ldots, n-1 $ .

Currently you are at your office, which is located at the intersection $ (1, 1) $ . If you plan your working day optimally, what is the maximum number of celebrities you can take a photo of?

## 说明/提示

Explanation of the first testcase: There is only one celebrity in the city, and he will be at intersection $ (6,8) $ exactly $ 11 $ minutes after the beginning of the working day. Since you are initially at $ (1,1) $ and you need $ |1-6|+|1-8|=5+7=12 $ minutes to reach $ (6,8) $ you cannot take a photo of the celebrity. Thus you cannot get any photo and the answer is $ 0 $ .

Explanation of the second testcase: One way to take $ 4 $ photos (which is the maximum possible) is to take photos of celebrities with indexes $ 3, 5, 7, 9 $ (see the image for a visualization of the strategy):

- To move from the office at $ (1,1) $ to the intersection $ (5,5) $ you need $ |1-5|+|1-5|=4+4=8 $ minutes, so you arrive at minute $ 8 $ and you are just in time to take a photo of celebrity $ 3 $ .
- Then, just after you have taken a photo of celebrity $ 3 $ , you move toward the intersection $ (4,4) $ . You need $ |5-4|+|5-4|=1+1=2 $ minutes to go there, so you arrive at minute $ 8+2=10 $ and you wait until minute $ 12 $ , when celebrity $ 5 $ appears.
- Then, just after you have taken a photo of celebrity $ 5 $ , you go to the intersection $ (6,6) $ . You need $ |4-6|+|4-6|=2+2=4 $ minutes to go there, so you arrive at minute $ 12+4=16 $ and you wait until minute $ 17 $ , when celebrity $ 7 $ appears.
- Then, just after you have taken a photo of celebrity $ 7 $ , you go to the intersection $ (5,4) $ . You need $ |6-5|+|6-4|=1+2=3 $ minutes to go there, so you arrive at minute $ 17+3=20 $ and you wait until minute $ 21 $ to take a photo of celebrity $ 9 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1427C/cf9dde842b4a7da217c75d840d0291c96e32acfa.png)Explanation of the third testcase: The only way to take $ 1 $ photo (which is the maximum possible) is to take a photo of the celebrity with index $ 1 $ (since $ |2-1|+|1-1|=1 $ , you can be at intersection $ (2,1) $ after exactly one minute, hence you are just in time to take a photo of celebrity $ 1 $ ).

Explanation of the fourth testcase: One way to take $ 3 $ photos (which is the maximum possible) is to take photos of celebrities with indexes $ 3, 8, 10 $ :

- To move from the office at $ (1,1) $ to the intersection $ (101,145) $ you need $ |1-101|+|1-145|=100+144=244 $ minutes, so you can manage to be there when the celebrity $ 3 $ appears (at minute $ 341 $ ).
- Then, just after you have taken a photo of celebrity $ 3 $ , you move toward the intersection $ (149,379) $ . You need $ |101-149|+|145-379|=282 $ minutes to go there, so you arrive at minute $ 341+282=623 $ and you wait until minute $ 682 $ , when celebrity $ 8 $ appears.
- Then, just after you have taken a photo of celebrity $ 8 $ , you go to the intersection $ (157,386) $ . You need $ |149-157|+|379-386|=8+7=15 $ minutes to go there, so you arrive at minute $ 682+15=697 $ and you wait until minute $ 855 $ to take a photo of celebrity $ 10 $ .

## 样例 #1

### 输入

```
10 1
11 6 8```

### 输出

```
0```

## 样例 #2

### 输入

```
6 9
1 2 6
7 5 1
8 5 5
10 3 1
12 4 4
13 6 2
17 6 6
20 1 4
21 5 4```

### 输出

```
4```

## 样例 #3

### 输入

```
10 4
1 2 1
5 10 9
13 8 8
15 9 9```

### 输出

```
1```

## 样例 #4

### 输入

```
500 10
69 477 122
73 186 235
341 101 145
372 77 497
390 117 440
494 471 37
522 300 498
682 149 379
821 486 359
855 157 386```

### 输出

```
3```

# 题解

## 作者：7KByte (赞：5)

不难想到一个朴素的DP。

$f[i]$表示以第$i$个点为终点，最多经过的点的个数。

得到方程$f[i]=\max\{f[j]+1\}$。转移条件是$i$到$j$所花时间小于时间差。

但这是$N^2$的。

我们观察一下可以发现$2\times r$的时间可以从一个点走到任意另外一个点。所以对于每个状态只用枚举前面$2\times r$个进行转移。前面的开一个变量记录即可。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 505
#define M 100005
using namespace std;
int n,m;
int X[M],Y[M],t[M];
int f[M];
int main(){
	scanf("%d%d",&n,&m);X[0]=Y[0]=1;
	rep(i,1,m)scanf("%d%d%d",&t[i],&X[i],&Y[i]);
	memset(f,0xcf,sizeof(f));
	f[0]=0;int mx=0xcfcfcfcf,ans=0;
	rep(i,1,m){
		f[i]=max(f[i],mx+1);
		rep(j,max(0,i-2*n),i-1)if(t[i]-t[j]>=abs(X[i]-X[j])+abs(Y[i]-Y[j]))f[i]=max(f[i],f[j]+1);
		if(i>=2*n)mx=max(mx,f[i-2*n]);
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	return 0;
}
/*
g++ C.cpp -o C -Wall -std=c++11
*/
```

---

## 作者：zztqwq (赞：2)

## Solution

考虑一个 $\mathcal O(n^2)$ 的朴素 dp：令 $f(i)$ 表示从起点到点 $i$ 且刚好在点 $i$ 看到明星的最优答案，则 $f(i)=\max\limits_{1\le j<i\text{且}\operatorname{dis}(i,j)\le t_i-t_j} \{f_j+1\}$，其中 $\operatorname{dis}(i,j)=\vert x_i-x_j\vert+\vert y_i-y_j\vert$。

观察题目以及不等式 $\operatorname{dis}(i,j)\le t_i-t_j$，可以看出当 $i-j>2r$ 时，$j$ 一定能够到达 $i$（$\operatorname{dis}(i,j)$ 最多是 $2r$，$\{t_i\}$ 单调递增）。也就是说，$\max\limits_{1\le j< i-2r}\{f_j\}$ 一定能够转移到 $f_i$，dp 过程中顺便存一下即可，而我们需要枚举的只有 $[i-2r+1,i-1]$ 这个区间，这样复杂度就变成了 $\mathcal O(nr)$。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5;
int dp[N+10],t[N+10],x[N+10],y[N+10];
int main()
{
	int n,r;
	scanf("%d %d",&r,&n);
	x[0]=y[0]=1;
	for(int i=1;i<=n;i++) scanf("%d %d %d",&t[i],&x[i],&y[i]);
	int mx=0xcfcfcfcf; //极小值
	memset(dp,0xcf,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=max(0,i-2*r+1);j<i;j++)
		{
			if(t[i]-t[j]>=abs(x[i]-x[j])+abs(y[i]-y[j]))
				dp[i]=max(dp[i],dp[j]+1);
		}
		dp[i]=max(dp[i],mx+1);
		if(i>=r*2) mx=max(mx,dp[i-r*2]);
	}
	int ans=0;
	for(int j=1;j<=n;j++) ans=max(ans,dp[j]);
	printf("%d",ans); 
	return 0;
}
```

---

## 作者：pikabi (赞：2)

## 暴力 dp

题意就是给定 $n$ 个时间点，该些时间点的位置上可以获得 $photo$ ，请问自己能得到的最多 $photos$。

距离是曼哈顿距离。所以观察到 $r \le 500$ ,所以有一个特殊性质：

- 所有点对之间的距离不超过 $2 \times r$

所以我们只需要在时间差为 1000 左右内的任务里 dp 就好了，对于大于等于 1000 的，我们直接用差分对其后每一个点进行 update 即可。

时间复杂度为 $n \times r$。

code $-->$

```
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cctype>
#define ll long long
#define inf 1023456789

using namespace std;

inline int read(){
	int x=0,w=0;char ch=getchar();
	while (!isdigit(ch))w|=ch=='-',ch=getchar();
	while (isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return w?-x:x;
}

struct node{
	int t, x, y;
}a[1000005];

int r, n, f[1000005], maxn, dif[1000005];

int main(){
	r = read(), n = read();
	for(int i = 1; i <= n; i++){
		a[i].t = read();
		a[i].x = read();
		a[i].y = read();
		f[i] = -inf;
		dif[i] = -inf;
	}
	dif[0] = -inf;
	a[0].t = 0;
	a[0].x = 1;
	a[0].y = 1;
	for(int i = 0; i < n; i++){
		if(i) dif[i] = max(dif[i - 1], dif[i]);
		f[i] = max(dif[i], f[i]);
		maxn = max(maxn, f[i]);
		for(int j = i + 1; j <= n; j++){
			if(a[j].t - a[i].t > 1000) {
				dif[j] = max(dif[j], f[i] + 1);
				break;
			}
			int dis = abs(a[i].x - a[j].x ) + abs(a[i].y - a[j].y );
			if(dis <= a[j].t - a[i].t ){
				f[j] = max(f[j], f[i] + 1);
//				printf("%d %d %d %d\n",i, j, dis, a[j].t - a[i].t );
			}
		}
	}
	dif[n] = max(dif[n - 1], dif[n]);
	f[n] = max(dif[n], f[n]);
	maxn = max(maxn, f[n]);
	printf("%d\n",maxn);
}

```

完结撒花

---

## 作者：SSerxhs (赞：2)

设 $f_{n}$ 表示参加第 $n$ 个最多可以参加的活动次数，显然有 $f_n=\max_{dis(i,n)\le t_n-t_i}\{f_i+1\}$

考虑 $t$ 两两不同，只需要考虑对前 1000 个转移，然后 1000 个以前的一定能到达，记个 max 即可

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e2+2,M=1e5+2,inf=1e9;
int f[M],x[M],t[M],y[M],g[M];
int n,m,c,fh,i;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
inline int ab(const int x)
{
	if (x>0) return x;return -x;
}
int main()
{
	read(m);read(n);
	register int i,j,k;
	for (i=1;i<=n;i++) {read(t[i]);read(x[i]);read(y[i]);f[i]=g[i]=-inf;}
	x[0]=y[0]=1;
	for (i=1;i<=n;i++)
	{
		for (j=i-1;(~j)&&(t[i]-t[j]<=1000);j--) if (t[i]-t[j]>=ab(x[i]-x[j])+ab(y[i]-y[j])) f[i]=max(f[i],f[j]+1);
		if (j>=0) f[i]=max(f[i],g[j]+1);g[i]=max(g[i-1],f[i]);
		//printf("%d %d\n",f[i],g[i]);
	}printf("%d",g[n]);
}
```

---

## 作者：ykzzldz (赞：2)

这题有几个坑点，首先是翻译没有说出，初始时位置在 $(1,1)$，然后在最开始的时候要将初值赋成负无穷，不然有可能由不合法的状态转移而来。接下来，$dp$ 就比较简单了。设 $f_i$ 表示拍第 $i$ 个人的最大答案。那么，当同时能拍 $i$ 和 $j$（$j<i$）时，就可以由 $f_j+1$ 转移到 $f_i$。最后，再统计最大的答案就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,n,t[110000],x[110000],y[110000],f[110000],ans;
signed main(){
	cin>>r>>n;
	for(int i=1;i<=n;i++){
		cin>>t[i]>>x[i]>>y[i];
		f[i]=-1e9;
	}
	t[0]=0,x[0]=1,y[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=i-1;j>=max(0,i-2000);j--){
			if(abs(x[i]-x[j])+abs(y[i]-y[j])<=t[i]-t[j]){
				f[i]=max(f[i],f[j]+1);
			}
		}
		ans=max(ans,f[i]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：wizardMarshall (赞：1)

## 题意

第 $i$ 个关键点在坐标 $(x_i, y_i)$，时间 $t_i$ 出现，你每个单位时间可以移动 $1$ 距离。求最多能得到多少个关键点（只能沿着整点走，也就是要求曼哈顿距离）

## 思路

首先不难想到简单动态规划。$dp_i$ 表示到第 $i$ 个可以获得的最大点数，然后枚举符合条件的 $j$ 来转移。判断坐标差是不是小于等于时间差。

双层循环，时间复杂度 $O(n^2)$。

----

明显超时，考虑优化。我们的坐标满足 $1\le x_i,y_i \le r$，也就是说一个点到另一个点的距离 $|x_i-x_j|+|y_i-y_j| \le 2r$。$r$ 的数据范围很小，每个点的时间又互不相同。于是考虑只需要判断这个点前面的 $2r$ 个点是不是满足距离的条件，再往前的不需要考虑距离。（注意这里只是**不需要考虑距离**，转移还是要的！可以开个变量维护）

稍微注意一个点就是开始时位于 $(1,1)$。而不是可以随便取。

时间复杂度 $O(nr)$。

## 代码

```c++


#include <bits/stdc++.h>
using namespace std;

struct Node{
	int x, y, t;
	bool operator < (const Node & y) const{
		return t < y.t;
	}
}node[200005];
int dp[200005];
signed main() {
	int r, n;
	cin >> r >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &node[i].t, &node[i].x, &node[i].y);
		dp[i] = -1e9;
	}
	
	dp[0] = 0;//把0当做开始的位置，便于转移
	node[0].x = 1;
	node[0].y = 1;
	node[0].t = 0;
	int ans = 0;
	int e = -1e9;
	for (int i = 1; i <= n; i++) {
		if (i > 2 * r) {//维护前面一部分的dp最大值
			e = max(e, dp[i - 2 * r - 1]);
		}dp[i] = e + 1;
		for (int j = i - 1; j >= max(0, i - 2 * r); j--) {//这部分的还要判断距离
			if (abs(node[i].x - node[j].x) + abs(node[i].y - node[j].y) <= node[i].t - node[j].t) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}ans = max(ans, dp[i]);
	}cout << ans;
    return 0;
}


```

---

