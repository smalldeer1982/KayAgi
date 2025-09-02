# Orchestra

## 题目描述

Paul is at the orchestra. The string section is arranged in an $ r×c $ rectangular grid and is filled with violinists with the exception of $ n $ violists. Paul really likes violas, so he would like to take a picture including at least $ k $ of them. Paul can take a picture of any axis-parallel rectangle in the orchestra. Count the number of possible pictures that Paul can take.

Two pictures are considered to be different if the coordinates of corresponding rectangles are different.

## 说明/提示

We will use '\*' to denote violinists and '\#' to denote violists.

In the first sample, the orchestra looks as follows

`<br></br>*#<br></br>**<br></br>` Paul can take a photograph of just the viola, the $ 1×2 $ column containing the viola, the $ 2×1 $ row containing the viola, or the entire string section, for $ 4 $ pictures total.In the second sample, the orchestra looks as follows

`<br></br>#*<br></br>*#<br></br>#*<br></br>` Paul must take a photograph of the entire section.In the third sample, the orchestra looks the same as in the second sample.

## 样例 #1

### 输入

```
2 2 1 1
1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
3 2 3 3
1 1
3 1
2 2
```

### 输出

```
1
```

## 样例 #3

### 输入

```
3 2 3 2
1 1
3 1
2 2
```

### 输出

```
4
```

# 题解

## 作者：prefer (赞：5)

## 题意：给定一个矩阵以及N个小提琴手的位置，求至少有多少个子矩阵，有K个小提琴手
-------
### 分析：我们第一眼就可以想出n^6暴力做法，可是看这道题目难度：目前是蓝题！提高+/省选- 

太令人震惊了！

为了配上这颜色，我们想一个稍微高端一点的做法，于是乎，两秒钟之后，我们就想到了二维前缀和！

我们首先设pre[i][j]为二维前缀和数组，我们先求和，然后四重循环枚举坐标，使用二维前缀和
数组计算一下当前是否符合要求就好了，时间复杂度n^4

~~码风贼丑~~



见谅啊
### CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int ret=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') {
			f=-f;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		ret=ret*10+ch-'0';
		ch=getchar();
	}
	return ret*f;
}
struct data {
	int x,y;
} a[505];
int mp[505][105],pre[505][505];
int r,c,n,k;
int calc(int x,int y) {
	int pp=0;
	for(int i=1; i<=x; i++) {
		for(int j=1; j<=y; j++) {
			pp+=mp[i][j];
		}
	}
	return pp;
}
int main() {
	freopen("orchestra.in","r",stdin);
	freopen("orchestra.out","w",stdout);
	int ans=0;
	r=read();
	c=read();
	n=read();
	k=read();
	for(int i=1; i<=n; i++) {
		a[i].x=read();
		a[i].y=read();
		mp[a[i].x][a[i].y]=1;
	}
	int sum=0;
	for(int i=1; i<=r; i++) {
		for(int j=1; j<=c; j++) {
			pre[i][j]=calc(i,j);
		}
	}
	for(int i=1; i<=r; i++) {
		for(int j=1; j<=c; j++) {
			for(int kk=i; kk<=r; kk++) {
				for(int o=j; o<=c; o++) {
					if(pre[kk][o]-pre[kk][j-1]-pre[i-1][o]+pre[i-1][j-1]>=k) {
						ans++;
					}
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：xht (赞：4)

> [CF627E Orchestra](https://codeforces.com/contest/627/problem/E)

## 题意

- 在一个 $r \times c$ 的矩阵中有 $n$ 个点，问有多少个连续子矩阵至少包含 $k$ 个点。
- $r,c,n \le 3 \times 10^3$，$k \le 10$。

## 题解

这题不同复杂度的做法非常多。

### $\mathcal O(r^3c^3 + n)$

最朴素的做法，枚举连续子矩阵的上下左右边界，暴力计算其中的点数。

也就是 [https://www.luogu.com.cn/problem/CF635A](https://www.luogu.com.cn/problem/CF635A) 这题。

### $\mathcal O(r^2c^2 + n)$

对于 $\mathcal O(r^3c^3)$ 做法的优化，计算连续子矩阵中的点数时，前缀和优化一下。

### $\mathcal O(r^2c + n)$

只枚举上下边界，中间 two pointers 扫一遍。

### $\mathcal O(r^2 + rc + rnk)$

注意到 $n,k$ 都非常小，其中 $n,r,c$ 同阶，而 $k$ 只有 $10$。

考虑枚举上边界 $i$，下边界从 $i$ 往下推，用链表按**列为第一关键字，行为第二关键字**的顺序维护所有点以及点之后第 $k-1$ 个点的列。

往下推的过程，相当于往链表里动态加点的过程，注意到每次加点只会改变其前面 $k-1$ 个点的信息，那么暴力更新即可。

但是链表无法随机访问，无法实现动态加点。那么换个方向，从 $r$ 往上推到 $i$，动态加点改为动态删点，就可以用链表维护了。

## 代码

```cpp
const int N = 3e3 + 7;
int r, c, n, k, p[N], q[N], t[N], v[N];
pi a[N];
vector<pi> R[N], C[N];
ll ans;

inline ll calc(int i, int j, int o) {
	ll ret = 1ll * (t[o] - j + 1) * (a[o].se - a[p[o]].se) * (c - a[v[o]].se + 1);
	return t[o] = j - 1, ret;
}

int main() {
	rd(r), rd(c), rd(n), rd(k);
	for (int i = 1, x, y; i <= n; i++)
		rd(x), rd(y), a[i] = mp(x, y), R[x].pb(mp(y, i)), C[y].pb(mp(x, i));
	for (int i = 1; i <= r; i++) sort(R[i].begin(), R[i].end());
	for (int i = 1; i <= c; i++) sort(C[i].begin(), C[i].end());
	a[n+1] = mp(r + 1, c + 1);
	for (int i = 1; i <= r; i++) {
		int o = 0;
		for (int j = 1; j <= c; j++)
			for (pi x : C[j])
				if (x.fi >= i)
					q[o] = x.se, p[x.se] = o, o = x.se, t[o] = r, v[o] = 0;
		q[o] = q[n+1] = v[n+1] = n + 1, t[n+1] = r, o = 0;
		for (int j = 1; j <= k; j++) o = q[o];
		for (int j = q[0]; j != n + 1; j = q[j], o = q[o]) v[j] = o;
		for (int j = r; j >= i; j--)
			for (pi x : R[j]) {
				ans += calc(i, j, q[x.se]), o = x.se;
				for (int l = 1; o && l <= k; l++, o = p[o]) ans += calc(i, j, o);
				q[p[x.se]] = q[x.se], p[q[x.se]] = p[x.se];
				int w = o = q[o];
				for (int l = 1; l < k; l++) w = q[w];
				while (o != q[x.se]) v[o] = w, o = q[o], w = q[w];
			}
	}
	print(ans);
	return 0;
}
```

---

## 作者：_ouhsnaijgnat_ (赞：3)

## 思路

这道题暴力出奇迹都是可以过的，时间复杂度为 $O(n^6)$。

然而，我要与众不同。

我们可以使用二维前缀和优化，时间复杂度为 $O(n^4)$。这道题枚举矩阵的左上角和右下角，再用前缀和算出有多少个点，符不符合。二位前缀和不懂的上百度，我就不过多讲解了。

两个四层循环解决了这个 $1\leq r,c\leq10$ 的水题。

代码奉上。

```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,l,n,a[15][15],dp[15][15],ans;
int main(){
	cin>>r>>c>>n>>l;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		a[x][y]=1;//将点记录下来。 
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){//二维前缀和赋值 。 
			int sum=0;
			for(int s=1;s<=i;s++){
				for(int k=1;k<=j;k++){//不会太高端的方法，只能用二层循环。 
					if(a[s][k])sum++;
				}
			}
			dp[i][j]=sum;
		}
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){//左上角。 
			for(int s=i;s<=r;s++){
				for(int k=j;k<=c;k++){//右下角。 
					if(dp[s][k]-dp[s][j-1]-dp[i-1][k]+dp[i-1][j-1]>=l)ans++;
				}
			}
		}
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：2311241987j (赞：3)

# 模拟？

这道题还不算太难,主要是数据小啊。

有暴力的做法，复杂度10^6，这是最**暴力**的，代码如下，具体**解析**见代码。

这道题很的、容易想到**暴力**，**模拟**！！！
```
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int ret=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-f;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
int n,r,c,k;
bool flag[15][15];
int main() {
	r=read(),c=read(),n=read(),k=read();
	for(int i=1; i<=n; i++) {
		int x=read(),y=read();
		flag[x][y]=1;
	}
	int sum=0;
	for(int i1=1; i1<=r; i1++)//枚举左上角的x
		for(int j1=1; j1<=c; j1++)//左上角y
			for(int i2=i1; i2<=r; i2++)//右下角x
				for(int j2=j1; j2<=c; j2++) //右下角y
                {
					int ans=0;
					for(int x=i1; x<=i2; x++)
						for(int y=j1; y<=j2; y++)//矩阵
							if(flag[x][y])ans++;
					if(ans>=k)sum++;//多了一个解
				}
	cout<<sum;
	return 0;
}```

这不是最优的做法，不过较为简单，主要数据问题。

但是可以运用前缀和来优化**10^4**

~~作者偷懒~，不打**10^4**~~



---

## 作者：rzh123 (赞：2)

# CF635A 题解  

题目链接：[CF635A Orchestra](https://www.luogu.com.cn/problem/CF635A)  

本题目前最优解：“优化”二维前缀和  

我也不知道这算不算“优化”，但是现有题解里没有这种，而且这个比他们的快。  

## 思路  

用 **两个** 二维数组 $s$ 和 $ss$。  

$s_{i,j}$ 表示 $(1,1)$ 到 $(i,j)$ 之间的矩阵中有几个点，也就是“二维前缀和”数组。  

$ss_{i,j}$ 表示第 $i$ 行前 $j$ 个点中有几个点，也就是每一行的“一维前缀和”数组。  

这样，在计算 $s_{i,j}$ 时不需要把第 $i$ 行重新遍历一遍，而是可以用 $s_{i,j}=s_{i-1,j}+ss_{i,j}$ 计算出来，加快了速度。这个式子可以用下图表示：  

[![HkQumn.png](https://s4.ax1x.com/2022/02/01/HkQumn.png)](https://imgtu.com/i/HkQumn)  

然后，直接暴力枚举子矩阵四个顶点，记录满足条件的子矩阵数量。  

时间复杂度：$O(n^4)$，常数小于其他同类题解。

## 代码  

```cpp
#include <cstdio>
#define gc getchar()
#define pc(c) putchar(c)
int r,c,n,k;
int a[17][17],s[17][17],ss[17][17];
int read(){
	int t=0;
	char c=gc;
	while(c<'0'||c>'9') c=gc;
	while(c>='0'&&c<='9') t=10*t+(c^48),c=gc;
	return t;
}
void write(int x){
	if(x<10){
		pc(x|48);
		return;
	}
	write(x/10);
	pc((x%10)|48);
}
int main(){
	int ans=0; 
	r=read(),
	c=read(),
	n=read(),
	k=read();
	for(int i=1;i<=n;++i){
		int x=read();
		int y=read();
		a[x][y]=1;
	}
	for(int i=1;i<=r;++i){
		for(int j=1;j<=c;++j){
			ss[i][j]=ss[i][j-1]+a[i][j];
			s[i][j]=s[i-1][j]+ss[i][j];
		}
	}
	for(int i=1;i<=r;++i){
		for(int j=1;j<=c;++j){
			for(int u=i;u<=r;++u){
				for(int v=j;v<=c;++v){
 					if(s[u][v]-s[i-1][v]-s[u][j-1]+s[i-1][j-1]>=k){
						++ans;
					}
				}
			}
		}
	}
	write(ans);
	puts("");
	return 0;
}
```  

[AC 记录](https://www.luogu.com.cn/record/68422122)  


---

## 作者：Marshall001 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF635A)

## 题目大意

- 在一个 $r \times c$ 的矩阵中有 $n$ 个点，问有多少个连续子矩阵至少包含 $k$ 个点。
- $r,c,n,k \le 10$。

## 思路一

这一题的 $r,c,n,k$ 都很小，可以直接用 $O(n^6)$ 的方法来做。

先枚举矩阵的左上角，再枚举矩阵的右下角，最后枚举整个矩阵就可以了。

## 思路二

用二维前缀和记录，时间复杂度为 $O(n^6)$。

只要你知道从 $(i,j)$ 到 $(k,l)$ 的点数量之和为这个：

```cpp
sum[k][l]-sum[k][j-1]-sum[i-1][l]+sum[i-1][j-1];
//其中sum[i][j]表示从（1，1）到（i，j）的点数之和。
```

## 代码：
思路一代码：
```cpp
#include <iostream>
using namespace std;
const int MAXN=15;
bool vis[MAXN][MAXN];
int r,c,n,k,ans;
int main(){
	cin>>r>>c>>n>>k;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		vis[x][y]=1;
	}
	for(int x1=1;x1<=r;x1++){
		for(int y1=1;y1<=c;y1++){//左上角
			for(int x2=x1;x2<=r;x2++){
				for(int y2=y1;y2<=c;y2++){//右下角
					int sum=0;
					for(int i=x1;i<=x2;i++){
						for(int j=y1;j<=y2;j++){//整个矩阵
							sum+=vis[i][j];
						}
					}
					if(sum>=k){
						ans++;
					}
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```

思路二代码：
```cpp
#include <iostream>
using namespace std;
const int MAXN=15;
int r,c,n,p,ans,sum[MAXN][MAXN],vis[MAXN][MAXN];
int main(){
	cin>>r>>c>>n>>p;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		vis[x][y]=1;
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			for(int k=1;k<=i;k++){
				for(int l=1;l<=j;l++){
					sum[i][j]+=vis[k][l];
				}
			}
		}
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			for(int k=i;k<=r;k++){
				for(int l=j;l<=c;l++){
					int o=sum[k][l]-sum[k][j-1]-sum[i-1][l]+sum[i-1][j-1];//计算
					if(o>=p){
						ans++;
					}
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：羽儇 (赞：1)

$\text{挺简单一水题}$

---
$Solution$ 

简单的思路：XYlen数组[x][nx][y][ny]存入从(x,y)到(nx,ny)小提琴手的数量

![](https://cdn.luogu.com.cn/upload/image_hosting/ciax9bdm.png)

如图，我们所读入的（x,y）会对，任何经过（x,y）的矩形(左上角为（i,j）的点,右下角为（nx,ny）的点)造成影响，所以我们可以枚举出所有经过（x,y）的矩形，即枚举左上角的点，右下角的点，使之+1；

最后枚举一下所有矩形看其是否符合条件 > K 即可

---
```cpp
#include <iostream>
#include <cstdio>
const int maxn = 11;
using namespace std;
int XYlen[maxn][maxn][maxn][maxn],ans;
int main()
{
	int x,y,r,c,n,k;
	scanf("%d%d%d%d",&r,&c,&n,&k);
	for(int i = 1 ; i <= n; i ++ )
	{
		scanf("%d%d",&x,&y);
		for(int i = 1 ; i <= x ; i ++ )
		for(int o = 1 ; o <= y ; o ++ )
        for(int j = x ; j <= r ; j ++ )
        for(int z = y ; z <= c ; z ++ )
        XYlen[i][j][o][z]++;
	}
	for(x = 1 ; x <= r ; x ++ )
	for(y = 1 ; y <= c ; y ++ )
		for(int nx = x ; nx <= r; nx ++ )
		for(int ny = y ; ny <= c; ny ++ )
		if(XYlen[x][nx][y][ny] >= k)  ans ++;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：xukuan (赞：1)

这题的难度有明显的问题，红题啊！

暴力可以过，当然前缀和优化是可行的

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll r,c,n,k,a[100][100],ans;
//a[x][y]代表从[1][1]到[x][y]的矩阵中有多少个小提琴演奏者

int main(){
//	freopen("orchestra.in","r",stdin);
//	freopen("orchestra.out","w",stdout);
	scanf("%lld %lld %lld %lld",&r,&c,&n,&k);
	for(ll i=1; i<=n; i++){
		ll x,y;
		scanf("%lld %lld",&x,&y);
		a[x][y]++;
	}
	for(ll i=1; i<=r; i++){
		for(ll j=1; j<=c; j++){
			a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
		}
	}
	for(ll x1=1; x1<=r; x1++){
		for(ll Y1=1; Y1<=c; Y1++){
			for(ll x2=x1; x2<=r; x2++){
				for(ll y2=Y1; y2<=c; y2++){
					if(a[x2][y2]-a[x1-1][y2]-a[x2][Y1-1]+a[x1-1][Y1-1]>=k) ans++;
				}
			}
		}
	}
	printf("%lld",ans);
//	fclose(stdin); fclose(stdout);
	return 0;
}
```

---

## 作者：___cjy__ (赞：0)

# CF1214A Optimal Currency Exchange 题解

[题目传送门](https://www.luogu.com.cn/problem/CF635A)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-cf635a)

### 题目大意：

一个 $r \times c$ 的矩阵中有 $n$ 个点，问有多少个连续子矩阵至少包含 $k$ 个点。

### 正文：

**解法一：暴力枚举**

时间复杂度：$O(n^6)$

没什么好说的，分别枚举子矩阵的两个对角端点，再遍历子矩阵记录点的个数。如果点数比 $k$ 大，就记录答案。

**AC Code：**


```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
#define int long long
#define N 20
#define INF 0xffffffff
#define bug printf("..........bug!..........\n");
using namespace std;
int a[N][N]; 
int r,c,n,k,ans,cnt; 
signed main(){
	cin>>r>>c>>n>>k;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		a[x][y]++;
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){//枚举子矩阵左上角坐标 
			for(int q=i;q<=r;q++){
				for(int p=j;p<=c;p++){//枚举子矩阵左右下角坐标 
					cnt=0;
					for(int x=i;x<=q;x++){
						for(int y=j;y<=p;y++){//遍历点的个数 
							cnt+=a[x][y];
						}
					}
					if(cnt>=k) ans++;
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```
---
**解法二：前缀和优化的暴力枚举**

时间复杂度：$O(n^4)$

需要用到一种不是很常见的二维前缀和，这里直接呈现公式，推导过程不理解请自行百度。

二维前缀和的初始化递推公式为：

$$f_{i,j}=f_{i-1,j}+f_{i,j-1}-f_{i-1,j-1}+a_{i,j}$$

求坐标 $(x_1,y_1)$ 和坐标 $(x_2,y_2)$ 之间的连续子矩阵的点的个数公式为：

$$f_{x_2,y_2}-f_{x_1-1,y_2}-f_{x_2,y_1-1}+f_{x_1-1,y_1-1}$$

我们枚举每一个 $(x_1,y_1)$ 和 $(x_2,y_2)$ 就可以求出至少包含 $k$ 个点的连续子矩阵的个数了。

**AC Code：**

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
#define int long long
#define N 20
#define INF 0xffffffff
#define bug printf("..........bug!..........\n");
using namespace std;
int a[N][N]; 
int d[N][N];
int r,c,n,k,ans,cnt; 
signed main(){
	cin>>r>>c>>n>>k;
	for(int i=1;i<=n;i++){
		int x,y;
		cin>>x>>y;
		a[x][y]++;
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){//初始化 
			d[i][j]=d[i-1][j]+d[i][j-1]-d[i-1][j-1]+a[i][j];
		}
	}
	for(int i=1;i<=r;i++){
		for(int j=1;j<=c;j++){
			for(int q=i;q<=r;q++){
				for(int p=j;p<=c;p++){//枚举坐标 
					if(d[q][p]-d[q][j-1]-d[i-1][p]+d[i-1][j-1]>=k)
						ans++;//求当前枚举矩阵点的个数是否大于等于k 
				}
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_lmz_ (赞：0)

这里我将介绍 2 种方法，有普及组水平的就可以直接看第二部分。
## Part 1 枚举
$6$ 层循环，前 $4$ 层枚举位置，后两层枚举矩阵内的点的个数。

代码很好实现。
```cpp
for(int i=1;i<=r;i++)
	for(int j=1;j<=c;j++)
		for(int k=i+1;k<=r;k++)
			for(int l=j+1;l<=c;l++){
				int sum=0;
				for(int A=i;A<=k;A++)
					for(int B=j;B<=l;B++)
						if(mp[A][B]) sum++;
				if(sum>=k) ans++;
			}
```
时间复杂度 $O(R^3 \times C^3)$。
## Part 2 前缀和优化
我们用 $\mathit{cnt}_{i,j}$ 表示从 $(1,1)$ 加到 $(i,j)$ 的总和，这个值可以通过 $3$ 个已知值加起来，再减去重合，加上本身的值。公式很好推导。
$$\mathit{cnt}_{i,j}=\mathit{cnt}_{i-1,j}+\mathit{cnt}_{i,j-1}-\mathit{cnt}_{i-1,j-1}+\mathit{a}_{i,j}$$
然后我们在程序开始之前求出这个值，然后再套上公式
$$\mathit{cnt}_{i,j}-\mathit{cnt}_{i,j-c}-\mathit{cnt}_{i-r,j}+\mathit{cnt}_{i-r,j-c}$$
这个值就是从 $(r,c)$ 加到 $(i,j)$ 的值，然后将这个公式套上代码，我们就可以 AC 了。

---

