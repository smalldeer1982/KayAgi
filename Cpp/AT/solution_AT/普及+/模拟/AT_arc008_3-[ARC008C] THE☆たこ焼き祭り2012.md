# [ARC008C] THE☆たこ焼き祭り2012

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc008/tasks/arc008_3

 たこ焼き屋の開店にあたって、たこ焼きの味を皆に分かってもらうために試食イベントを行うことにしました。  
 しかし、高橋社長はたこ焼きをより多くの人に食べてもらいたいので、試食イベントを兼ねたお祭り『THE☆たこ焼き祭り2012』をすることを提案してきました。高橋社長が提案してきた『THE☆たこ焼き祭り2012』の試食イベント内容は以下のようになっています。

 会場にはあなたと参加者を足して $ N $ 人の人がいます。あなたはたこ焼きを $ N $ 個持っており、それを全員に $ 1 $ 人 $ 1 $ 個ずつ行き渡るようにします。  
 会場は広いのであなたはたこ焼きを投げて配らないといけません。 あなただけで全員に配ることは大変なので、参加者にも協力してもらうことにし、参加者は受け取ったたこ焼きを別の参加者へと投げることもできます。  
 あなたと参加者はつまようじを$ 1 $ 人につき $ 1 $ 本しか持っていないので同じタイミングで複数のたこ焼きを投げることはできず、たこ焼きを投げてから $ 1 $ 秒間は次のたこ焼きを投げることができません。受け取る側はいつでも何個でも受け取ることができます。  
 さらに、あなたと参加者は立っている位置から動いてはいけません。  
 参加者は大人から子供までいるのでそれぞれにはたこ焼きをキャッチできる速度の上限があり、たこ焼きを投げる側にも投げられる速度の上限があります。投げられたたこ焼きの速度は減衰することなく受け取り手に届きます。

 たこ焼きはなるべく出来立てを食べて欲しいので、たこ焼きを全員に配り切るために必要な時間の最小値を答えなさい。

 入力は以下の形式で標準入力から与えられる。 > $ N $ $ x_{0} $ $ y_{0} $ $ t_{0} $ $ r_{0} $ $ x_{1} $ $ y_{1} $ $ t_{1} $ $ r_{1} $ : : $ x_{N-1} $ $ y_{N-1} $ $ t_{N-1} $ $ r_{N-1} $

- 入力は $ N+1 $ 行ある。
- $ 1 $ 行目には、たこ焼き祭りの参加者数とあなたを足した数を表す整数 $ N\ (1≦N≦1,000) $ が与えられる。
- $ 2 $ 行目には、あなたが立っている位置の $ x $ 座標を表す整数 $ x_0\ (-10,000≦x_0≦10,000) $、$ y $ 座標を表す整数 $ y_0\ (-10,000≦y_0≦10,000) $、たこ焼きを投げる速度の上限を表す整数 $ t_0\ (3≦t_0≦340) $ とたこ焼きを受け取る速度の上限を表す整数 $ r_0\ (3≦r_0≦340) $ が空白で区切られて与えられる。
- $ 3 $ 行目から $ N-1 $ 行のうち $ i+2\ (1≦i≦N-1) $ 行目には $ i $ 番目の参加者が立っている位置の $ x $ 座標を表す整数 $ x_i\ (-10,000≦x_i≦10,000) $、$ y $ 座標を表す整数 $ y_i\ (-10,000≦y_i≦10,000) $、たこ焼きを投げる速度の上限を表す整数 $ t_i\ (3≦t_i≦340) $ とたこ焼きを受け取る速度の上限を表す整数 $ r_i\ (3≦r_i≦340) $ が空白で区切られて与えられる。
- 与えられる速度は $ 1 $ 秒辺りの速度である。
- 複数の人が同じ位置に立つことはない。
 
 たこ焼きを全ての参加者が $ 1 $ つずつ受け取るためまでに必要な秒数の最小値を $ 1 $ 行で出力せよ。  
 出力は整数および小数のみとし、誤差は絶対誤差あるいは相対誤差の少なくとも片方が $ 10^{−6} $ 以下であれば許容する。  
 なお、最後には改行を出力せよ。 ```

4
0 0 300 10
0 100 10 100
0 200 10 200
0 300 10 300
```

 ```

3
```

- $ 0 $ 秒目 : 
  - あなた : $ 1 $ 番目の参加者に速度 $ 100 $ でたこ焼きを投げる。
- $ 1 $ 秒目 : 
  - あなた : $ 2 $ 番目の参加者に速度 $ 200 $ でたこ焼きを投げる。
  - $ 1 $ 番目の参加者 : あなたが $ 0 $ 秒目に投げたたこ焼きをキャッチする。
- $ 2 $ 秒目 : 
  - あなた : $ 3 $ 番目の参加者に速度 $ 300 $ でたこ焼きを投げる。
  - $ 2 $ 番目の参加者 : あなたが $ 1 $ 秒目に投げたたこ焼きをキャッチする。
- $ 3 $ 秒目 : 
  - $ 3 $ 番目の参加者 : あなたが $ 2 $ 秒目に投げたたこ焼きをキャッチする。
 
```

4
0 0 100 10
0 90 10 10
0 100 30 100
-20 100 10 10
```

 ```

3
```

- $ 0 $ 秒目 : 
  - あなた : $ 2 $ 番目の参加者に速度 $ 100 $ でたこ焼きを投げる。
- $ 1 $ 秒目 : 
  - あなた : $ 2 $ 番目の参加者に速度 $ 100 $ でたこ焼きを投げる。
  - $ 2 $ 番目の参加者 : あなたが $ 0 $ 秒目に投げたたこ焼きをキャッチし、$ 3 $ 番目の参加者に速度 $ 10 $ で投げる。
- $ 2 $ 秒目 : 
  - あなた : $ 2 $ 番目の参加者に速度 $ 100 $ でたこ焼きを投げる。
  - $ 2 $ 番目の参加者 : あなたが $ 1 $ 秒目に投げたたこ焼きをキャッチし、$ 2 $ 番目の参加者に速度 $ 10 $ で投げる。
- $ 3 $ 秒目 : 
  - $ 1 $ 番目の参加者 : $ 2 $ 番目の参加者が $ 2 $ 秒目に投げたたこ焼きをキャッチする。
  - $ 2 $ 番目の参加者 : あなたが $ 2 $ 秒目に投げたたこ焼きをキャッチする。
  - $ 3 $ 番目の参加者 : $ 2 $ 番目の参加者が $ 1 $ 秒目に投げたたこ焼きをキャッチする。
 
```

1
0 0 3 3
```

 ```

0
```

- 参加者があなただけなので配る必要がありません。
 
```

4
58 -49 38 109
45 -29 200 56
-32 123 103 98
49 -234 289 43
```

 ```

4.874179
```


```

8
100 100 30 50
100 50 93 123
100 0 89 111
50 100 13 18
50 0 155 86
0 100 30 58
0 50 58 49
0 0 98 153
```

 ```

7.666667
```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc008_3)

### 思路

不难想到可以用**最短路**解决此题。

本题中可以将每个人当作一个点，将两个人传递小丸子所需时间建成边权，做最短路即可。

由于 $N\le10^3$，考虑 Floyd，时间复杂度 $\mathcal{O}(N^3)$，可以通过此题。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e3+10;
int x[N],y[N],t[N],r[N];
double f[N][N];
int main(){
	int n=read();
	for(int i=1;i<=n;++i)
		x[i]=read(),y[i]=read(),t[i]=read(),r[i]=read();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			f[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))/min(t[i],r[j]);
	for(int k=1;k<=n;++k)
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	sort(f[1]+1,f[1]+n+1);
	double ans=0;
	for(int i=2;i<=n;++i)
		ans=max(ans,f[1][i]+n-i);
	printf("%.12lf\n",ans);
	return 0;
}
```

---

## 作者：_xbn (赞：3)

[题目](https://www.luogu.com.cn/problem/AT279)

由于数据范围很小，我们可以考虑建边直接跑 floyd ，对于每一对丸子建一条双向边。

边权为两个点的距离，然后直接跑最短路即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1002,INF = 1<<30;
double d[N][N];
double x[N], y[N], t[N], r[N];
int n;
int main()
{
	cin >> n;
	for(int i=0; i<n; i++) 
	{
	   cin >> x[i] >> y[i] >> t[i] >> r[i];
	}
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
				double dx = x[i] - x[j];
				double dy = y[i] - y[j];
				d[i][j] = sqrt(dx*dx + dy*dy) / min(t[i], r[j]);
		}
	}
	for(int k=0; k<n; k++)
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

	double ret = 0;
	sort(d[0], d[0]+n);
	for(int i=1; i<n; i++)
	{
		ret = max(ret, d[0][i]+(n-1-i));
	}
	printf("%.6f\n", ret);
}
```




---

## 作者：Zheng_iii (赞：2)

## 思路
看到 $ N \leq 1000$，我们立马想到 Floyd，把每个人都当作点，把传递小丸子所需的时间当作边权去建边。

最后直接跑一遍 Floyd 就好了。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e3+10;
int x[N],y[N],t[N],r[N],n;
double dis[N][N],res;

inline void floyd(){
	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
}
int main(){
	// freopen("text.in","r",stdin);
	// freopen("text.out","w",stdout);
	ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
	cin>>n;
	for(int i = 1;i <= n;i++){
		cin>>x[i]>>y[i]>>t[i]>>r[i];
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			dis[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) / min(t[i], r[j]);
		}
	}
	floyd();
	sort(dis[1]+1,dis[1]+1+n);
	for(int i = 2;i <= n;i++){
		res = max(res,dis[1][i]+n-i);
	}
	cout<<fixed<<setprecision(6)<<res;
	return 0;
}
```

---

## 作者：miraculously (赞：2)

分析：

这道题要求所有人拿到章鱼丸的最小时间，那就把每个人的传递时间当成权值，跑一遍最短路，然后求最后一个收到章鱼丸的时间就好了，因为数据范围不大，所以可以用 Floyd 过这道题。

代码如下（有注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;
double d[1001][1001];//d数组存第i个人直接到第j个人的时间
double x[1001],y[1001],t[1001],r[1001];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%lf%lf%lf%lf",&x[i],&y[i],&t[i],&r[i]);
	for(int i=1;i<=n;i++)//预处理时间
	for(int j=1;j<=n;j++)
	{
		double tx=x[i]-x[j];
		double ty=y[i]-y[j];
		d[i][j]=sqrt(tx*tx+ty*ty)/min(t[i],r[j]);//速度为第i个人扔出速度和第j个人接收速度的最小值
	}
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	d[i][j]=min(d[i][j],d[i][k]+d[k][j]);//Floyd
	sort(d[1]+1,d[1]+n+1);//将第1个人到第j个人的最短时间排序
	double ans=0.00;
	for(int i=2;i<=n;i++)//必须从第2个开始不然会错
	ans=max(ans,d[1][i]+(n-i));//加上(n-i)是因为每投一次都要隔一秒再投
	printf("%.6lf",ans);
}
```


---

## 作者：Tjaweiof (赞：1)

# AT_arc008_3 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_arc008_3)

因为数据范围较小，考虑 Floyd。把每个人看成一个节点，传递章鱼小丸子需要的时间看成边权。然后遍历每个人，找到最晚拿到章鱼小丸子的人，输出他拿到的时间即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
double dist[1001][1001], x[1001], y[1001], t[1001], r[1001], ans;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> x[i] >> y[i] >> t[i] >> r[i];
    }
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= n; j++){
			dist[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) / min(t[i], r[j]);
		}
	}
	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	sort(dist[1] + 1, dist[1] + 1 + n);
	for (int i = 2; i <= n; i++){
		ans = max(ans, dist[1][i] + (n - i));
	}
	cout << fixed << setprecision(10) << ans;
	return 0;
}
```

---

## 作者：Acerkaio (赞：1)

### 题目：
~~提一嘴，这个样例（题目看不懂所以我去看样例）看了我是蒙的，所以我稍微修改了一下题目，毕竟“每个人1人一个一个地把它普及”不是人人都可以看懂的~~  
原题：[这](https://www.luogu.com.cn/problem/AT279)  
修改后：[这](https://www.luogu.com.cn/paste/xetemnsh) 
### 思路：
其实也很简单，从题目中不难看出要跑最短路。数据中 $N\le 1000$ 样的数据。$\mathcal{O}(n^3)$ 该可能也许大概是过得了（~~反正这题是过了~~），所以咱使用 Floyd 算法。

讲一下 Floyd：

Floyd 算法是一个基于「贪心」、「动态规划」求一个图中所有点到所有点 最短路径的算法，时间复杂度 $\mathcal{O}(n^3)$。

其重点思想：以每个点为「中转站」，刷新所有「入度」和「出度」的距离。

大家也可以先看看[【Clear And Present Danger S】](https://www.luogu.com.cn/problem/P2910)这道板子题。

再看本题，要求求把章鱼小丸子分发给所有人所需时间的最小值，就把两个人传递的时间当作「入度」和「出度」的距离，跑一遍 Floyd 即可。
### CODE：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
double x[514850],y[514850],t[514850],r[514850],f[1001][1001],a;
inline void floyd()
{
	for(int k=1; k<=n; k++) {
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++) {
				f[i][j]=min(f[i][k]+f[k][j],f[i][j]);
			}
		}
	}	
}
signed main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>x[i]>>y[i]>>t[i]>>r[i];

	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			double fx=x[i]-x[j];
			double fy=y[i]-y[j];
			f[i][j]=sqrt(fx*fx+fy*fy)/min(t[i],r[j]);
		}
	}
	floyd();
	sort(f[1]+1,f[1]+n+1);
	for(int i=2;i<=n;i++)
	a=max(a,f[1][i]+n-i);
	printf("%.6lf",a);
	return 0;
}
```


---

## 作者：Nahia (赞：0)

### 思路

我们首先注意到 $N \leqq 1000$，于是。

> 一眼 Floyd。

将每个人当作一个点，将两个人传递小丸子所需的时间当作边权来建边，最后跑一遍 Floyd 就好了。

~~数据过水，$\mathcal{O}(N^3)$ 都能过~~

### solution

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int x[N],y[N],t[N],r[N];
double f[N][N];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i]>>t[i]>>r[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;++j)
			f[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))/min(t[i],r[j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				f[j][k]=min(f[j][k],f[j][i]+f[i][k]);
	sort(f[1]+1,f[1]+n+1);
	double ans=0;
	for(int i=2;i<=n;++i)
		ans=max(ans,f[1][i]+n-i);
	cout<<fixed<<setprecision(12)<<ans;
	return 0;
}
```

---

## 作者：InversionShadow (赞：0)

什么远古题，$n\le 10^3$ 为什么题解区全是弗洛伊德跑的？

显然可以把两个人看做两个点，两个点直接的边权容易算出。考虑 $n\le 10^3$，所以就可以 SPFA 跑了。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e6 + 100;

int n, head[N], tot;
double x[N], y[N], t[N], r[N], ans, dis[N];
bool vis[N];

struct Node {
	int to, nxt;
	double w;
} e[N];

void add(int x, int y, double w) {
	e[++tot].to = y;
	e[tot].nxt = head[x];
	e[tot].w = w;
	head[x] = tot;
}

void spfa() {
	for (int i = 1; i <= n; i++) {
		dis[i] = 10000000000.0;
	}
	queue<int> q;
	q.push(1);
	dis[1] = 0;
	vis[1] = 1;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (dis[v] > dis[u] + e[i].w) {
				dis[v] = dis[u] + e[i].w;
				if (!vis[v]) {
					vis[v] = 1;
					q.push(v);
				}
			}
		}
	}
}

signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> x[i] >> y[i] >> t[i] >> r[i];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			add(i, j, 1.0 * sqrt(1.0 * (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) / min(t[i], r[j]));
		}
	}
	spfa();
	sort(dis + 1, dis + n + 1);
	for (int i = 2; i <= n; i++) {
		ans = max(ans, dis[i] + (n - i));
	}
	cout << fixed << setprecision(10) << ans;
	return 0;
}
```

然后就是最优解力！

---

## 作者：maple_trees_112 (赞：0)

这道题是一道 Floyd。

我第一次看以为用 dijkstra，然后发现题解区里边全是 Floyd。我当时十分纳闷，就这数据范围居然能过？当我打出来后，发现样例中似乎有负环，吓得我赶紧重构代码。

所以我总结出一个道理，要学会看清样例，不要盲目迷恋 dijkstra。

Floyd yyds。

## 思路

可以把一个人看成一个点，然后跑一遍这个图即可。

送上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1010;
double f[maxn][maxn];
double x[maxn],y[maxn],t[maxn],r[maxn];
int n;
int main()
{
	cin>>n;
	for(int i = 0;i < n;i++) 
	{
	   cin>>x[i]>>y[i]>>t[i]>>r[i];
	}
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			double fx = x[i] - x[j];
			double fy = y[i] - y[j];
			f[i][j] = sqrt(fx * fx + fy * fy) / min(t[i], r[j]);
		}
	}
	for(int i = 0;i < n;i++)
	{
		for(int j = 0;j < n;j++)
		{
			for(int k = 0;k < n;k++)
			{
				f[j][k] = min(f[j][k], f[j][i] + f[i][k]);
			}
		}
	}
	double ans = 0;
	sort(f[0],f[0] + n);
	for(int i = 1;i <= n - 1;i++)
	{
		ans = max(ans, f[0][i] + (n - 1 - i));
	}
	cout<<fixed<<setprecision(6)<<ans;
}
```


---

## 作者：_zexal_ (赞：0)

## 前言
如果你是因为题面的问题而看向题解，那么请点击这个链接，这里有已经修改好的[题面](https://www.luogu.com.cn/paste/xetemnsh)。
## 思路
我们不妨把每个人看成一个个点，传递时间就是点到点之间的权值，然后我们跑一遍最短路即可。由于数据比较水（~~我随便随便打一发Floyd就过了~~），所以，我们可以使用 Floyd 算法。如果你不懂 Floyd 算法，可以看看我写的这篇[文章](https://www.cnblogs.com/zhong114514/p/16558911.html)。
## ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1005
double answer,x[N],y[N],t[N],r[N],fl[N][N],tx,ty,mixn;
int n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i]>>t[i]>>r[i];
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	{
		tx=(x[i]-x[j])*(x[i]-x[j]);
		ty=(y[i]-y[j])*(y[i]-y[j]);
		mixn=min(t[i],r[j]);
		fl[i][j]=sqrt(tx+ty)/mixn;//将时间转换为权值
	}
	for(int k=1;k<=n;k++)//枚举中转点
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				fl[i][j]=min(fl[i][j],fl[i][k]+fl[k][j]);
	sort(fl[1],fl[1]+n+1);
	for(int i=2;i<=n;i++)
	answer=max(answer,fl[1][i]+(n-i));//递出后一分钟后才能递出下一个章鱼丸子
	printf("%.6lf",answer);
	return 0;
}
```


---

## 作者：duchengjun (赞：0)

$1\le N\le 1000$。

N 并不大，考虑用 Floyd.

但是在数据强的情况下 Floyd 的时间可能会超，但是我只能说这题的数据太水了，$O(N^3)$ 竟然不超时！！！

于是此题就是一个模板题了。

附上[真模板题](https://www.luogu.com.cn/problem/P2910)。

此题只是求把章鱼小丸子分发给所有人所需时间的最小值。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000+10;
int n;
double f[N][N];
double x[N],y[N],t[N],r[N];
double ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i]>>t[i]>>r[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))/min(t[i],r[j]);
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	sort(f[1]+1,f[1]+1+n);
	for(int i=2;i<=n;i++)
		ans=max(ans,f[1][i]+(n-i));
	printf("%0.6f",ans);
	return 0;
}

```


---

