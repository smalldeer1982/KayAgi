# Minimal Segment Cover

## 题目描述

给定 $n$ 个区间，形式为 $[l, r]$，在数轴上。

同时给定 $m$ 个查询，每个查询为 $[x, y]$。你需要选择最少数量的区间，使得从 $x$ 到 $y$ 的每一个点（不一定是整数）都被至少一个区间覆盖。

如果无法选择区间使得 $[x, y]$ 的每个点都被覆盖，则对于该查询输出 $-1$。

## 说明/提示

在第一个样例中，有三个查询：

1. 查询 $[1, 3]$ 可以被区间 $[1, 3]$ 覆盖；
2. 查询 $[1, 4]$ 可以被区间 $[1, 3]$ 和 $[2, 4]$ 覆盖。无法用一个区间覆盖 $[1, 4]$；
3. 查询 $[3, 4]$ 可以被区间 $[2, 4]$ 覆盖。只需要覆盖查询区间内的点，其他点是否被覆盖无关紧要。

在第二个样例中，有四个查询：

1. 查询 $[1, 2]$ 可以被区间 $[1, 3]$ 覆盖。注意可以选择任意一个 $[1, 3]$ 区间；
2. 查询 $[1, 3]$ 可以被区间 $[1, 3]$ 覆盖；
3. 查询 $[1, 4]$ 无法被任何区间集合覆盖；
4. 查询 $[1, 5]$ 无法被任何区间集合覆盖。注意区间 $[1, 3]$ 和 $[4, 5]$ 组合无法覆盖 $[1, 5]$，因为所有点（包括非整数点）都必须被覆盖。例如 $3.5$ 没有被覆盖。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2 3
1 3
2 4
1 3
1 4
3 4
```

### 输出

```
1
2
1
```

## 样例 #2

### 输入

```
3 4
1 3
1 3
4 5
1 2
1 3
1 4
1 5
```

### 输出

```
1
1
-1
-1
```

# 题解

## 作者：米奇 (赞：35)

## 倍增

这题问你覆盖一段区间需要最少几条线段。

我们先如处理出从一个左端点用一条线段最远能覆盖到哪个右端点
注意线段起点可能在这个左端点左边

然后就可以倍增预处理出每个左端点用x条线段最远能覆盖到哪个右端点

然后对于每个询问就能log求出答案

## 代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=600005;
int n,m,l,r,ma,a[N],f[N][22];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&l,&r);
		a[l]=max(a[l],r);
		ma=max(ma,r);
	}
	for(int i=1;i<=ma;i++)a[i]=max(a[i],a[i-1]);
	for(int i=0;i<=ma;i++)f[i][0]=a[i];
	for(int i=1;i<=20;i++)
		for(int j=0;j<=ma;j++)f[j][i]=f[f[j][i-1]][i-1];
	while(m--)
	{
		scanf("%d%d",&l,&r);
		int ans=0;
		for(int i=20;i>=0;i--)
			if(f[l][i]<r)
			{
				ans+=1<<i;
				l=f[l][i];
			}
		if(a[l]>=r)printf("%d\n",ans+1);
		else puts("-1");
	}
	return 0;
}
```


---

## 作者：WaterSun (赞：23)

# 思路

这是一道简单的 DP 题，DP 题的核心就是状态转移。

先来说一说 $dp$ 数组的含义。

$dp_{i,j}$ 表示从 $i$ 这个点用 $2 ^ j$ 条线段能走到的最远的点。

我们再来考虑一下边界情况。

因为我们只用 $2 ^ 0$ 条线段，那么：$dp_{i,0} = \max(dp_{i,0},r)$

接着，我们递推一遍，从前往后更新一遍最大值。

即：$dp_{i,0} = \max(dp_{i,0},dp_{i - 1,0})$

然后我们对 $dp$ 数组进行递增。

即：$dp_{j,i} = dp_{dp_{j,i - 1},i - 1}$

注：以上递推和递增的操作都需要从 $1$ 到 $N$，原因是：我们操作都是预处理，最后直接求答案的。

最后，我们直接用一个循环来求出答案。

如果 $dp_{x,i} < y$，那么我们的结果直接加上 $2 ^ i$，将 $x$ 更新为 $dp_{x,i}$。

结果要加上 $2 ^ i$ 的原因是：我们从 $dp$ 数组的含义出发，我们需要的线段数量便是 $2 ^ i$

将 $x$ 更新成 $dp_{x,i}$ 的原因是：我们把点 $x$ 之前的所有点都走过了，所以我们直接更新即可

我们最后算出来的结果是终点的上一个点，所以我们需要判断一下最后一个是否有解就行了，如果有解输出结果 + 1，否则输出 -1

# code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10;
int n,m;
int dp[N + 100000/*要开大一点，不然越界*/][25];

int main(){
	cin >> n >> m;
	for (int i = 1;i <= n;i++){
		int a,b;
		cin >> a >> b;
		dp[a][0] = max(dp[a][0],b);
	}
	for (int i = 1;i <= N;i++) dp[i][0] = max(dp[i][0],dp[i - 1][0]);
	for (int i = 1;i <= 19;i++){
		for (int j = 0;j <= N;j++){
			dp[j][i] = dp[dp[j][i - 1]][i - 1];
		}
	}
	while (m--){
		int x,y;
		int res = 0;
		cin >> x >> y;
		for (int i = 19;i >= 0;i--){
			if (dp[x][i] < y){
				res += (1 << i);
				x = dp[x][i];
			}
		}
		if (dp[x][0] >= y) cout << res + 1 << endl;
		else puts("-1");
	}
	return 0;
}
```

---

## 作者：吴思诚 (赞：6)

## CF1175E Minimal Segment Cover 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1175E)

### 思路
首先设 $f_{i,k}$ 表示从第 $i$ 个单位使用 $2^k$ 条线段覆盖到的最远点。当然 $f_{i,0}=r$。然后是一遍递推，即 $f_{i,0}=\max(f_{i-1,0},f_{i,0})$。然后开始递增。即$f_{i,j}=f_{f_{i,j-1},j-1}$。对于每次询问，如果 $f_{i,j}>0$ 且 $f_{i,j}<r$，则选取了 $2^j$ 条，然后更新当前的位置，如果最后 $f_{l,0}<r$，则无解。

___
### 代码
```cpp
#include<bits/stdc++.h>
const int maxn=1e6+10;
using namespace std;
int f[maxn][23],i,j,n,m,ans;
int main(){
	int i,x,y;
	scanf("%d%d",&n,&m);
	for(j=0;(1<<j)<maxn;j++)
		for(i=0;i<maxn;i++)
			f[i][j]=0;
	for(i=1;i<=n;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		f[l][0]=max(f[l][0],r);
	}
	for(i=1;i<maxn;i++)
		f[i][0]=max(f[i-1][0],f[i][0]);
	for(j=1;(1<<j)<maxn;j++){
		for(i=0;i<maxn;i++){
			f[i][j]=f[f[i][j-1]][j-1];
		}
	}
	for(i=1;i<=m;i++){
		int l,r;
		ans=0;
		scanf("%d%d",&l,&r);
		for(j=20;j>=0;j--){
			if(f[l][j]&&f[l][j]<r){
				ans+=(1<<j);
				l=f[l][j];
			}
		}
		if(f[l][0]<r)
			printf("-1\n");
		else
			printf("%d\n",ans+1); 
	}
	return 0;
}
```

---

## 作者：MILLOPE (赞：4)

## 题目
[题目传送门](https://www.luogu.org/problemnew/show/CF1175E) 

给出$n$个形如$[l,r]$的线段。$m$次询问，每次询问区间$[x,y]$，问至少选出几条线段，使得区间$[x,y]$的任何一个部位都被至少一条线段覆盖。

## 题解
- 首先非常暴力的想法，我们可以把每个点$x$尽量的往后跳，跳的时候是可以后退的（如下图：
	
	![在这里插入图片描述](https://img-blog.csdnimg.cn/2019070819064352.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzM0NDkzODQw,size_16,color_FFFFFF,t_70)

- 这样我们就可以预处理出每个点所能到的最远点
- 然后我们可以把跳的过程用倍增实现，这样就会降低我们的复杂度qwq

## $code$
```cpp
#include <bits/stdc++.h> 
using namespace std; 
#define maxn 600100

template <typename T> 
inline void read(T &s) {
    s = 0; 
    T w = 1, ch = getchar(); 
    while (!isdigit(ch)) { if (ch == '-') w = -1; ch = getchar(); }
    while (isdigit(ch)) { s = (s << 1) + (s << 3) + (ch ^ 48); ch = getchar(); }
    s *= w; 
}

int a[maxn]; 
int f[maxn][25]; 

int main() {
    int n, m, R = 0; 
    read(n), read(m); 
    for (int i = 1; i <= n; ++i) {
        int l, r; read(l), read(r); 
        a[l] = max(a[l], r); 
        R = max(R, r); 
    }

    for (int i = 1; i <= R; ++i) 
        a[i] = max(a[i], a[i-1]); 
    for (int i = 0; i <= R; ++i) f[i][0] = a[i]; 
    for (int j = 1; j <= 20; ++j) 
    	for (int i = 0; i <= R; ++i) 
    		f[i][j] = f[ f[i][j-1] ][j-1]; 

    while (m--) {
    	int l, r; read(l), read(r); 
    	int ans = 0; 
    	for (int i = 20; i >= 0; --i) {
    		if (f[l][i] < r) 
    			l = f[l][i], ans += 1<<i; 
    	}
    	if (a[l] >= r) printf("%d\n", ans+1); 
    	else puts("-1"); 
    }
    return 0; 
} 



```

---

## 作者：GIFBMP (赞：3)

一开始我们可以想到贪心，即：

把所有线段按照右端点排序，然后每次找与其有重合且右端点最右的线段。

然而这样是 $\Theta (nq)$ 的，无法通过本题。

于是我们考虑倍增优化询问。

设 $f_{i,j}$ 表示点 $i$ 向右扩展 $2^j$ 根线段，能到达的最远距离，则有：

$$f_{i,0}=\text{max}(\text{max}_{a_l=i}a_r,f_{i-1,0})$$

$$f_{i,j}=f_{f_{i,j-1},j-1}$$

于是便可以 $\Theta(\operatorname{log}\operatorname{max}a_r)$ 回答询问，可以通过本题。

Code:

```cpp
#include <cstdio>
using namespace std ;
const int MAXN = 5e5 + 10 ;
int n , q , f[MAXN][25] , k ;
int max (int a , int b) {
	return a > b ? a : b ;
}
int main () {
	scanf ("%d %d" , &n , &q) ;
	for (int i = 1 ; i <= n ; i++) {
		int l , r ;
		scanf ("%d %d" , &l , &r) ;
		f[l][0] = max (f[l][0] , r) ;
		k = max (k , r) ;
	}
	for (int i = 1 ; i <= k ; i++) f[i][0] = max (f[i][0] , f[i - 1][0]) ;
	for (int i = 1 ; i <= 20 ; i++)
		for (int j = 0 ; j <= k ; j++)
			f[j][i] = f[f[j][i - 1]][i - 1] ;
	while (q--) {
		int l , r , ans = 0 ;
		scanf ("%d %d" , &l , &r) ;
		for (int i = 20 ; i >= 0 ; i--)
			if (f[l][i] < r) {
				ans += 1 << i ;
				l = f[l][i] ;
			}
		printf ("%d\n" , f[l][0] >= r ? ans + 1 : -1) ;
	}
	return 0 ;
}
```

---

## 作者：FZzzz (赞：3)

最近想刷点 cf 题，但是那种计数神题和各种杂题是肯定做不动的，所以准备来水点小清新 ds 水题。尽量每做一题都写篇题解记录一下好了。

好了下面是题解：

------------
首先考虑这个题如果一次询问怎么做：

这就是道 pj 贪心题。先把有包含关系的线段处理一下，剩下的线段排序。

然后我们就可以发现选择的第一个线段肯定是左端点在区间左端点左边并且最靠右的线段。每个线段的下一个线段就是与这个线段有重合的最右的线段。

好了现在如果是一次询问我们就可以直接去做了。但是现在多次询问怎么办呢？

朴素的算法我们需要对于每条线段找到它的下一条线段。我们尝试优化这个过程。这可以用倍增做到。

然而这个算法的细节还是挺多的……虽然码量并不大但是我还是懒得写。

其实当值域小的时候我们有另一种差不多的贪心方法。我们计算每一个点用一条线段往右最多能盖到哪里。

这样就好写很多了，不过细节还是有点多，具体看代码吧。
```cpp
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
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
const int maxa=5e5+5;
int n,m;
int f[maxa][20];
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    m=readint();
    memset(f,-1,sizeof(f));
    while(n--){
    	int l,r;
    	l=readint();
    	r=readint();
    	f[l][0]=max(f[l][0],r);
	}
	for(int i=1;i<maxa;i++) f[i][0]=max(f[i][0],f[i-1][0]);
	for(int i=1;i<20;i++) for(int j=0;j<maxa;j++)
		if(f[j][i-1]<0) f[j][i]=-1;
		else f[j][i]=f[f[j][i-1]][i-1];
	while(m--){
		int x,y;
		x=readint();
		y=readint();
		int ans=0;
		for(int i=19;i>=0;i--) if(f[x][i]>=0&&f[x][i]<y){
			ans+=1<<i;
			x=f[x][i];
		}
		if(f[x][0]<y) printf("-1\n");
		else printf("%d\n",ans+1);
	}
    return 0;
}
```


---

## 作者：极寒神冰 (赞：2)

原题是一道数据范围较小的且没有贪心。做法为贪心地将所有线段左端点排序，然后枚举每一条线段。

代码大概长这个样子：
```cpp
inline int cmp(node x,node y)
{
	if(x.l==y.l) return x.r>y.r;
	return x.l<y.l;
}
int main()
{
	n=read(),T=read();
	for(int i=1;i<=n;i++)
	{
		a[i].l=read();
		a[i].r=read();
	}	
	sort(a+1,a+n+1,cmp);
	int i=0;
	while(i<=n)
	{
		int maxx=-1;
		while(i<=n&&a[i].l<=R+1)
		{
			maxx=max(maxx,a[i].r);
			i++;
		}
		if(maxx<=R)
		{
			puts("-1");
			return 0;
		}
		ans++;
		R=maxx;
		if(R>=T)
		{
			cout<<ans;
			return 0;
		}
	}
	puts("-1");
} 
```

对于这道题，先预处理出一个R[i]表示表示l<=i时，R最大的值。（如果有一条线段左端点比你小，右端点还比你大，这条线段就没用了）

令$dp[i][j]$ 表示第i个位置往右走$2^j$条线段所能到达的最右的位置，有

$$dp[i][j]=dp[dp[i][j-1]][j-1]$$

表示从第i个位置往右走$2^j$步从这个点走$2^{j-1}$再走$2^{j-1}$步所到达的位置

具体见代码:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
const int MAX_L = 500010;//最大距离为500000；
int dp[MAX_L][20];
int R[MAX_L];//每个点最远能到哪里 
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,m,l,r;

int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		l=read(),r=read();
		R[l]=max(R[l],r);
	}
	dp[0][0]=R[0];
	for(int i=1;i<MAX_L;i++)
	{
		R[i]=max(R[i],R[i-1]);//预处理出每个点所能到右最远的位置 
		dp[i][0]=R[i];//这个位置往右一条线段就是R[i] 
	}
	for(int j=1;j<20;j++)
	{
		for(int i=0;i<MAX_L;i++)
		{
			dp[i][j]=dp[dp[i][j-1]][j-1];
		}
	}
	while(m--)
	{
		int x=read(),y=read(),ret=0;
		for(int i=19;i>=0;i--)
		{
			if(dp[x][i]<y)
			{
				ret+=(1<<i);
				x=dp[x][i];
			}
		}
		if(dp[x][0]<y)
		{
			puts("-1");
		}
		else 
		{
			printf("%d\n",ret+1)；
		}
	}
} 
```


---

## 作者：樱花飞舞 (赞：2)

这道题与某些贪心很相似，都是给你一些线段去覆盖一个区间。但是，由于数据很大，直接用普通的贪心很容易超时，所以就想到优化。使用倍增的方法能够快速解决。

```cpp
#include<iostream>
int n,m,x,y;
int dp[500001][26];
int a[500001];
using namespace std;
int main()
{
	ios::sync_with_stdio(false);//快速
	cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		cin>>x>>y;
		a[x]=max(a[x],y);
	}
	dp[0][0]=a[0];
	for(int i=1;i<500001;i++)
	{
		a[i]=max(a[i],a[i-1]);
		dp[i][0]=a[i];
	}
	for(int j=1;j<20;j++)
		for(int i=0;i<500001;i++)
			dp[i][j]=dp[dp[i][j-1]][j-1];//初始化
	while(m--)
	{
		cin>>x>>y;
		int ret=0;
		for(int i=19;i>=0;i--)
		{
			if(dp[x][i]<y)
			{
				ret+=(1<<i);
				x=dp[x][i];
			}
		}
		if(dp[x][0]<y) cout<<-1<<endl;//判断
		else cout<<ret+1<<endl;
	}
	return 0;	
} 
```


---

## 作者：wasa855 (赞：2)

首先有一个显然的贪心，设询问区间为$[l,r]$，则所取的区间最靠左的一个的左端点必定小于等于$l$，并且要使这个区间尽可能地向右延伸。   
取完第一个之后，重复以上的贪心，直至满足条件，那么这样的答案必定是最小的。   
   
但是这样的时间复杂度是$O(nm)$的，所以要考虑优化，优化方法是用倍增，每次向右跳$2^i$条线段，那么复杂度就变成$O(n\log m)$了。于是本题就解决了。   
   
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 200005
#define M 500005
inline int read()
{
	char ch=getchar();
	while(!isdigit(ch)) ch=getchar();
	int ans=0;
	while(isdigit(ch))
	{
		ans=ans*10+ch-48;
		ch=getchar();
	}
	return ans;
}
int suf[M][25];

int main()
{
	int n,m;
	cin>>n>>m;
	int x,y;
	for(int i=1;i<=n;i++)
	{
		x=read(),y=read();
		x++;
		if(suf[x][0]<y)
		{
			suf[x][0]=y;
		}
	}
	for(int i=1;i<=M;i++)
	{
		suf[i][0]=max(suf[i][0],suf[i-1][0]);
	}
	for(int i=1;i<=19;i++)
	{
		for(int j=1;j<=M;j++)
		{
			suf[j][i]=suf[suf[j][i-1]+1][i-1];
		}
	}
	for(int i=1;i<=m;i++)
	{
		x=read(),y=read();
		int ans=0;
		for(int j=19;j>=0;j--)
		{
			if(suf[x+1][j]<y&&suf[x+1][j]>x)
			{
				x=suf[x+1][j];
				ans+=(1<<j);
			}
		}
		ans++;x=suf[x+1][0];
		if(x<y) printf("-1\n");
		else printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：_l_l_ (赞：1)

[题目页面](https://www.luogu.com.cn/problem/CF1175E)

[更好的阅读体验](https://www.luogu.com.cn/blog/yinjun2024/solution-cf1175e)

这道题我们使用倍增的思想，设计 $dp_{i,j}$ 为从第 $i$ 个单位覆盖了 $2^j$

则 $dp_{i,j}=dp_{dp_{_{i,j-1}},j-1}$

统计时在使用倍增即可

代码：

```cpp
#include <cstdio>
using namespace std;
const int MAXN = 6e5 + 10;
int n, q, f[MAXN][25], k;
int max (int a, int b) {
	return a > b ? a : b;
}
int main () {
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= n; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		f[l][0] = max(f[l][0], r);
		k = max(k, r);
	}
	for (int i = 1; i <= k; i++) f[i][0] = max(f[i][0], f[i - 1][0]);
	for (int i = 1; i <= 24; i++)
		for (int j = 0; j <= k; j++)
			f[j][i] = f[f[j][i - 1]][i - 1];
	while (q--) {
		int l, r, ans = 0;
		scanf("%d %d", &l, &r);
		for (int i = 24; i >= 0; i--)
			if (f[l][i] < r) {
				ans += 1 << i;
				l = f[l][i];
			}
		printf("%d\n", f[l][0] >= r ? ans + 1 : -1);
	}
	return 0;
}
```

---

## 作者：derta (赞：1)

[CF1175E Minimal Segment Cover](https://www.luogu.com.cn/problem/CF1175E)

这道题与线段编号无关，故考虑从 $l,r$ 的实值入手

令 $f_{i,j}$ 表示从 $i$（或之前）开始用 $2^j$ 条线段最多覆盖到哪里，若无法覆盖到任何地方或用 $2^k(k<j)$ 条线段即可达到用 $2^j$ 条线段的效果，$f_{i,j}=-1$

边界条件：$f_{l,0}=r$，若 $f_{i-1,j} >i$，$f_{i,j}=\max(f_{i,j},f_{i-1,j}$)

转移方程：若 $f_{i,j-1} \neq -1$ 且 $f_{f(i,j-1),j-1} \neq -1$，$f_{i,j}=f_{f(i,j-1),j-1}$

对于每一次询问，可以类比倍增 LCA 理解，详见代码

```cpp
#include <cstring>
#include <cstdio>
#include <cctype>
const int MAXW = 500000, lgMAXN = 20;
int n, m, l, r, x, y, res, maxright;
int f[MAXW + 5][lgMAXN + 5];

int read() { //快读 
	char c = getchar();
	int x = 0;
	while(!isdigit(c))
		c = getchar();
	while(isdigit(c)) {
		x = x*10 + c - '0';
		c = getchar(); 
	}
	return x;
}

inline int Max(int x, int y)
{ return x > y ? x : y; }

int main() {
	memset(f, -1, sizeof(f));
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) {
		l = read(), r = read();
		f[l][0] = Max(f[l][0], r); //别忘了取max 
		if(maxright < r) //更新右边界 
			maxright = r;
	}
	for(int i = 1; i <= maxright; ++i) //边界条件 
		if(f[i - 1][0] > i)
			f[i][0] = Max(f[i][0], f[i - 1][0]);
	for(int i = 1; (1 << i) <= n; ++i) //转移 
		for(int j = 0; j <= maxright; ++j)
			if(f[j][i - 1] != -1 && f[f[j][i - 1]][i - 1] != -1)
				f[j][i] = f[f[j][i - 1]][i - 1];
	while(m--) {
		res = 0;
		l = read(), r = read();
		for(int i = lgMAXN; i >= 0; --i) {
			if(f[l][i] != -1 && f[l][i] < r) { //覆盖不到 
				l = f[l][i]; //覆盖上这些线段 
				res += 1 << i; //更新答案 
			}
		}
		if(f[l][0] >= r) //覆盖上一条就能到r了 
			printf("%d\n", res + 1); //有解，输出答案（+1是因为又跳了一步） 
		else //无解 
			printf("-1\n"); //输出-1 
	}
	return 0;
}
```

---

## 作者：81179332_ (赞：1)

求覆盖一段区间最少需要几条线段

我们设 $f_{i,j}$ 表示从第 $i$ 个点使用 $2^j$ 个线段最远能覆盖到哪个右端点，起始状态 $f_{l,0}=r$

但是有很多点没被左端点覆盖，所以我们处理 $f_{i,0}=\max(f_{i,0},i,f_{i-1,0})$

倍增处理，对于每个询问跳即可

```cpp
timeuse:20min
const int N = 500010;
int n,q,l[N],r[N],maxx;
int f[N][25];
int main()
{
	n = read(),q = read();
	for(int i = 1;i <= n;i++)
	{
		l[i] = read() + 1,maxx = max(r[i] = read() + 1,maxx);
		f[l[i]][0] = max(f[l[i]][0],r[i]);
	}
	for(int i = 1;i <= maxx;i++) f[i][0] = max(f[i][0],max(i,f[i - 1][0]));
	for(int j = 1;j < 25;j++)
		for(int i = 1;i <= maxx;i++)
			f[i][j] = f[f[i][j - 1]][j - 1];
	while(q--)
	{
		int x = read() + 1,y = read() + 1;
		int ans = 0;
		for(int j = 24;~j;j--)
			if(f[x][j] < y) x = f[x][j],ans += (1 << j);
		x = f[x][0],ans++;
		if(ans > n || x < y) puts("-1");
		else fprint(ans);
	}
}
```

---

## 作者：lmgoat (赞：0)

倍增优化 DP。

设 $f[i][j]$ 表示第 $j$ 开始用 $2^i$ 条线段最大能覆盖到的右端点（这些线段中最小的左端点不一定是 $j$ ）。

初值：$f[0][i]=\max\{r[j]\}\,(l[j]<=i)$。$O(n)$ 扫一遍就可以预处理出 $f[0][i]$。

转移：$f[i][j]=f[i-1][f[i-1][j]]$，非常常规的倍增转移，就是从 $j$ 出发，选 $2^{i-1}$ 条线段，然后从这个位置再选 $2^{i-1}$ 条线段。

预处理出所有 $f[i][j]$。

查询：类似于倍增求 LCA 的跳法，从大到小枚举 $2$ 的指数 $i$，每次如果跳过去还不会超过 $y$ 就跳过去，答案加上 $2^i$。记录下当前位置就可以实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
int read() {
	int x(0),f(0);
	char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
const int N=500005,L=18;
int n,m,f[L+1][N],ma;
signed main() {
	n=read(),m=read();
	for(int i=1;i<=n;++i) {
		int l=read(),r=read();
		ma=max(ma,r);
		f[0][l]=max(f[0][l],r);
	}
	for(int i=1;i<=ma;++i) f[0][i]=max(f[0][i],f[0][i-1]);
	for(int i=1;i<=L;++i)
	for(int j=0;j<=ma;++j)
		f[i][j]=f[i-1][f[j][i-1]];
	while(m--) {
		int x=read(),y=read(),ans=0;
		for(int i=L;i>=0;--i)
			if(f[i][x]<y) x=f[i][x],ans+=1<<i;
		if(f[0][x]>=y) printf("%d\n",ans+1);
		else puts("-1");
	} 
	return 0;
}
```

---

## 作者：Utilokasteinn (赞：0)

## [Link](https://www.luogu.com.cn/problem/CF1175E)

一道比较水的倍增题，但是还是做了好久。

首先可以发现，对于两条线段 $x$ 和 $y$，若 $y$ 完全属于 $x$，则说明 $y$ 没有用，$y$ 能做的 $x$ 一定能做，所以就可以把 $y$ 去掉。所以我们先去重。

~~不知道问什么我会想到用权值线段树来去重。~~

可以先对线段进行排序，使得左端点从小到大排序。若两个线段左端点相同，则按右端点从大到小排序。

排完序后，从 $1$ 到 $n$，若第 $i$ 条线段的右端点大于 $\max_{j=1}^{i-1}r_j$ 则说明该线段没被任何线段树所包含。否则就是被包含，至于为什么显然。因为之前的线段的 $l$ 肯定小于等于 $l_i$，而又有至少一条线段的 $r$ 大于等于 $r_i$，则说明该线段肯定被包含。

之后，我们可以构造一个倍增数组 $f_{i,j}$。其中 $f_{i,0}$ 表示第 $i$ 条线段后的最后一条与其相交的线段。因为这样才能使得用最少的线段构成一个区间。

举个例子，区间 $[1,5]$，$[2,7]$，$[4,8]$。若查询区间 $[1,8]$ 实际上并不会用到第 $2$ 条线段。

至于如何处理 $f_{i,0}$，可以用二分到找到最后一条线段与第 $i$ 条线段相交的线段。

$f_{i,j}$ 表示第 $i$ 条线段后接下去的第 $2^j$ 条线段的编号。显然可以通过 $f_{i,0}$ 构造出。

接着就是查询，找到最后一个编号为 $pos$ 的线段，使得不与查询的 $qr$ 相交。然后将之间需要通过的线段数全部加起来加一就是答案了，这个答案可以在倍增的过程中实现。

细节需要注意一下。代码还是比较好想的（代码有亿点长）：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int s=0,f=1;char c=getchar();
	for(;!isdigit(c);c=getchar())
		if(c=='-')f=-1;
	for(;isdigit(c);c=getchar())
		s=s*10+c-'0';
	return s*f;
}
int n,m,maxn,tot;
struct segment{
	int l,r;
}temp[200005],se[200005];
bool cmp(segment a,segment b)
{
	if(a.l==b.l)return a.r>b.r;
	return a.l<b.l;
}
int f[200005][20];
void init()
{
	for(int i=1;i<tot;i++)//找到最后一条线段与第i条线段相交 
	{
		int l=i+1,r=tot,pos=0;
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(se[mid].l<=se[i].r)
				l=mid+1,pos=mid;
			else r=mid-1;
		}
		f[i][0]=pos;
	}
	for(int i=1;i<=19;i++)
		for(int j=1;j+(1<<i)-1<=tot;j++)
			f[j][i]=f[f[j][i-1]][i-1];
}
int solve(int ql,int qr)
{
	int l=1,r=tot,pos=-1;
	while(l<=r)//找到最后一个l小于等于ql的
	{
		int mid=(l+r)/2;
		if(se[mid].l<=ql)
			l=mid+1,pos=mid;
		else r=mid-1;
	}
	if(pos==-1)return -1;
	if(se[pos].r>=qr)return 1;
	int res=1;
	for(int i=19;i>=0;i--)
		if(f[pos][i]&&se[f[pos][i]].r<qr)
			pos=f[pos][i],res+=(1<<i);
	if(f[pos][0]==-1)return -1;
	if(se[f[pos][0]].r<qr)return -1;
	return res+1;
}
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		temp[i].l=read(),temp[i].r=read();
	sort(temp+1,temp+n+1,cmp);
	int maxn=-1;
	for(int i=1;i<=n;i++)
		if(temp[i].r>maxn)
		{
			se[++tot]=temp[i];
			maxn=temp[i].r;
		}
	init();
	for(int i=1;i<=m;i++)
	{
		int ql=read(),qr=read();
		printf("%d\n",solve(ql,qr));
	}
	return 0;
}
```

谢谢观赏。

---

## 作者：ttq012 (赞：0)

题目大意：给你一些线段，然后 $Q$ 次询问，每一次询问询问一段区间 $[l, r]$，问最少需要多少条线段可以覆盖这一段区间。

我们定义 `Seg[i]` 代表一条线段，其中 `seg[i].l` 代表线段的左端点，`seg[i].r` 代表一条线段的右端点。

我们可以暴力地贪心，每一次贪心区间 $[l, r]$，在 $O(N)$ 的时间复杂度内求出区间需要几条线段覆盖，但是这道题有多组询问，时间复杂度为 $O(NQ)$，所以会超时。

我们现在要将时间复杂度控制在 $O(N\log N)$ 及以下。

可以发现，对于某一个位置 $x$，有多条线段都可以覆盖这一个位置，我们实际上只用记录所有线段中，右端点最靠右的那一条就可以了。

现在我们要预处理出来一个 $R_i$，代表哪一条线段，它的左端点小于 $i$ 点，而且右端点最大。

但是 $R_i$ 如何预处理呢？对于任意的一条线段，$R_i = \max(R_i, seg_i.r)$

$R_i$ 也可以由 $R_{i - 1}$ 来更新过来，这样我们就可以预处理出来每一个位置往右，左端点小于 $i$ 点，且右端点最大了。

**核心要领：ST表**

我们定义 $dp_{i, j}$ 表示 $i$ 位置往右，$2^j$ 条线段所能到达的最靠右的位置。

$dp_{i, 0}$ 表示从 $i$ 位置开始，往右一条线段所能到达的最右位置，它就等于 $R_i$。

$dp_{i, j}$ 递推公式：$dp_{i, j} = dp_{dp_{i, j - 1}, j - 1}$。

**下面上代码**

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const int MAX_L = (N << 1) + N;

int dp[MAX_L][20], R[MAX_L];

int main()
{
    int n, m, l, r;
    cin >> n >> m;
    for (int i = 0; i < n; i ++)
    {
        scanf ("%d%d", &l, &r);
        R[l] = max(R[l], r); // 通过线段更新 R[l] 的值
    }
    dp[0][0] = R[0];
    for (int i = 1; i < MAX_L; i ++)
        R[i] = max(R[i], R[i - 1]); // 通过 R[i - 1] 来更新 R[i] 的值
    for (int i = 1; i < MAX_L; i ++) // 从这里开始预处理ST表(RMQ)
        dp[i][0] = R[i]; // 初始条件
    for (int j = 1; j < 20; j ++)
        for (int i = 0; i < MAX_L; i ++)
            dp[i][j] = dp[dp[i][j - 1]][j - 1]; // 状态转移方程
    // 询问，重点
    while (m --)
    {
        int x, y;
        scanf ("%d%d", &x, &y);
        int ret = 0;
        for (int i = 19; i >= 0; i --)
            if (dp[x][i] < y) // LCA思想，能跳就跳
                x = dp[x][i], ret += (1 << i);
        if (dp[x][0] < y)
            puts("-1");
        else
            printf ("%d\n", ret + 1); // LCA思想，到最后了，还不是最近的公共祖先，我们还需要往前跳一步才算是公共祖先
    }
    return 0;
}

```



---

## 作者：henrytb (赞：0)

[更好的阅读体验](https://blog.henrytb.ml/2020/11/%E9%A2%98%E8%A7%A3-CF1175E-Minimal-Segment-Cover/)

我们先考虑一下一道“缩水版”的题目。

> 已知数轴上有一个区间，左端点记为 $L$，右端点记为 $R$，以及 $n$ 条线段 $s_i$，请问在 $n$ 条线段中最少选择多少条，可以把区间完全覆盖（包括 $L$ 点和 $R$ 点）。

我们可以定义 $f_i$ 表示从 $i$ 这个点，通过一条线段能到达的最右的点。

实现方式：

```cpp
rep(i,1,MAXR) f[i]=i; //MAXR是值域
rep(i,1,n) {
    f[s[i].l]=max(f[s[i].l],s[i].r);
}
rep(i,0,MAXR) f[i]=max(f[i],f[i-1]);
```

然后暴力从 $L$ 开始跳 $f$ 即可。

如果遇到了 $f_i=i$ 且 $i<R$ 的情况，那么无解。

跳到 $R$ 以后 `break` 掉循环。

那么可以来看这道题目了。如果说要优化一次询问的过程呢？

可以倍增！设 $f_{i,j}$ 表示从 $i$ 这个点通过 $2^j$ 个线段能到达的最右的点。

这样一次询问我们就优化成了 $O(\log n)$，可以通过本题。

代码：

```cpp
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define per(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int N=2e5+5,MAXL=5e5+5;
int n,m,fare[MAXL][22];
int mxr=0;
int main() {
    scanf("%d%d",&n,&m);
    rep(i,1,n) {
        int l,r;
        scanf("%d%d",&l,&r);
        fare[l][0]=max(fare[l][0],r);
        mxr=max(mxr,r);
    }
    rep(i,0,mxr) fare[i][0]=max(fare[i][0],fare[i-1][0]);
    rep(j,1,21) rep(i,0,mxr) {
        fare[i][j]=fare[fare[i][j-1]][j-1];
    }
    rep(i,1,m) {
        int x,y;
        scanf("%d%d",&x,&y);
        int ans=0;bool flg=0;
        per(j,21,0) {
            if(fare[x][j]<y) {
                ans+=(1<<j);
                x=fare[x][j];
            }
        }
        if(fare[x][0]>=y) printf("%d\n",ans+1);
        else puts("-1");
    }
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：0)

&emsp;&emsp;[传送门](https://www.luogu.com.cn/problem/CF1175E)

&emsp;&emsp;就让我再来一发友好的倍增题解吧。

&emsp;&emsp;如果一个多次询问的题太难，我们就考虑一次询问的情况。

&emsp;&emsp;贪心易得，第一次选的一定是起始点小于等于 $x$ 的，同时要右端点尽可能大，这样后面的备选就多了。这个贪心不用证，想想都知道。

&emsp;&emsp;问题在于多次询问，不能每次模拟这个过程了。那么怎么倍增跳？倍增的题都要**满足结合律**，也就是可合并性（可能这方面有点像线段树）。那么怎么才能让 $x$ 和 $2x$ 代表的一些东西可合并又能得到答案呢。设 $f(x,idx)$ 是点 $x$ 选 $2^idx$ 条线段的最靠右的选法。得到 $f(x,idx) = f(f(x,idx-1),idx-1)$。分析一下为什么可以这样维护，这个柿子有结合律是因为**我们的贪心做法有结合律**。这个倍增本质上还是贪心的过程，只不过跳着维护了而已，如果选了 $k$ 条线段，必定是先选 $\frac{k}{2}$ 条线段的。根据上述的贪心，这 $\frac{k}{2}$ 条线段覆盖的应该尽可能广，然后按相同策略贪心。因此我们发现了这个东西是可以 $O(n \log n)$ 计算的。

&emsp;&emsp;本题的第二个（可能有点难）的点：如何计算 $f(i,0)$ ？即倍增的初始状态。不妨设 $g(i)$ 就代表 $f(i,0)$。考虑递推，一条覆盖 $i$ 的线段不是也覆盖了 $i-1$，就是以 $i$ 为起点，维护以 $i$ 为起点的线段的最靠右的点输入的时候直接维护，考虑跨越了 $i-1$ 的那些线段，因为这个推导是无后效性的，那么计算 $g(i)$ 之前$g(i-1)$ 就成功计算出来了，此时那些跨越 $i-1$ 和 $i$ 的线段一定被算在内了，于是可以 $O(n)$ 递推（dp）出来。

&emsp;&emsp;第三个点：到底如何计算最后的答案，毕竟只是预处理了 $2^k$ 条线段的最右点。这里其实和 lca 的求法类似（我们老师就放到了 lca 的作业里面），来分析一下为何两者有共同点（或者说为什么我们老师会说这是 lca的题导致我错误方向想了很久）。第一个点是，**如果 $n$ 条可以，$n+1$ 条必定可以**，在 LCA 中体现在**两个点的LCA的祖先依旧是这两个点的祖先**；第二个点是，**它们都可以用倍增跳出来**，这个的意思是，因为最短数量确定，它必定可以拆成一个二进制数，代表选择线段树，这个二进制数和 LCA 里面 $x,y$ 同层向上跳所需要的级数转成二进制数是一样的。总结一下：**这里选择 $2^k$ 条线段和 LCA 里向上跳 $2^k $ 层本质上是一样的。**

&emsp;&emsp;那么就好做了。与 LCA 相同地，因为我并不知道跳到 LCA 的那个步数的二进制到底是多少，导致如果我从小往大的次方跳，会出现最后很可能跳到的不是最近祖先（最少步数）。那么从大往小的次方跳，~~你会发现此时这个问题依旧没有解决~~，但是我们可以跳到 **最少步数的前一个步数**。这里和 LCA 就没有什么区别了，我们刚才已经分析过两者的相同点了，这个地方也一样。最后注意一下，树一定有 LCA，但这题不一定有最少步数，所以最后向上跳一格后要判断一下是不是真的 $>= y$ 了。

&emsp;&emsp;~~只要不是像我这种一开始就往 lca 想结果什么都出不来的，应该都能随便切掉这道题吧~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std; 
const int MAXN=5e5+10;
struct Line{
	int l,r;
}line[MAXN];
int n,m,l,r,tmp[MAXN],limit,x,y;
int power[30],f[MAXN][30]; //f(i,j) 2^j条线段，跨越点i可以向右延伸的最大点 
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&line[i].l,&line[i].r);
		tmp[line[i].l] = max(tmp[line[i].l],line[i].r);
		limit = max(limit,line[i].r); 
	}
	for(int i=1;i<=limit;i++){
		if(tmp[i-1] >= i)tmp[i] = max(tmp[i],tmp[i-1]);
	}
	for(int i=0;i<=limit;i++){
		f[i][0] = tmp[i];
	}
	power[0] = 1;
	for(int i=1;i<=20;i++)power[i] = power[i-1]<<1;
	for(int idx = 1;power[idx]<=n;idx++){
		for(int i = 0;i<=limit;i++){
			f[i][idx] = f[f[i][idx-1]][idx-1];
		}
	}
	for(int i =1;i<=m;i++){
		scanf("%d%d",&x,&y);
		int len = log(n)/log(2);
		int ans = 0;
		for(int idx = len;idx>=0;idx--){
			if(f[x][idx] < y){
				ans += power[idx];
				x = f[x][idx];
			}
		}
		ans++; 
		if(f[x][0] >= y)printf("%d\n",ans);
		else printf("-1\n");
	}
	return 0;
}
```


---

