# OpenStreetMap

## 题目描述

Seryozha conducts a course dedicated to building a map of heights of Stepanovo recreation center. He laid a rectangle grid of size $ n \times m $ cells on a map (rows of grid are numbered from $ 1 $ to $ n $ from north to south, and columns are numbered from $ 1 $ to $ m $ from west to east). After that he measured the average height of each cell above Rybinsk sea level and obtained a matrix of heights of size $ n \times m $ . The cell $ (i, j) $ lies on the intersection of the $ i $ -th row and the $ j $ -to column and has height $ h_{i, j} $ .

Seryozha is going to look at the result of his work in the browser. The screen of Seryozha's laptop can fit a subrectangle of size $ a \times b $ of matrix of heights ( $ 1 \le a \le n $ , $ 1 \le b \le m $ ). Seryozha tries to decide how the weather can affect the recreation center — for example, if it rains, where all the rainwater will gather. To do so, he is going to find the cell having minimum height among all cells that are shown on the screen of his laptop.

Help Seryozha to calculate the sum of heights of such cells for all possible subrectangles he can see on his screen. In other words, you have to calculate the sum of minimum heights in submatrices of size $ a \times b $ with top left corners in $ (i, j) $ over all $ 1 \le i \le n - a + 1 $ and $ 1 \le j \le m - b + 1 $ .

Consider the sequence $ g_i = (g_{i - 1} \cdot x + y) \bmod z $ . You are given integers $ g_0 $ , $ x $ , $ y $ and $ z $ . By miraculous coincidence, $ h_{i, j} = g_{(i - 1) \cdot m + j - 1} $ .

## 说明/提示

The matrix from the first example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195E/f7a7b9ecd6a8532f015eda872ed84e65d4581837.png)

## 样例 #1

### 输入

```
3 4 2 1
1 2 3 59
```

### 输出

```
111
```

# 题解

## 作者：柳易辰 (赞：7)

# Codeforces 1195E OpenStreetMap 题解
思路 1：暴力枚举每一个子矩形，并暴力查询最小值，时间复杂度 $O(nmab)$，显然超时。

思路 2：二维 RMQ。

考虑到查询是区间最小值，且没有修改操作（静态），容易想到 $\text{RMQ}$，但是空间（$nm\log\max(n,m)$） 开不下。

---
## 正解：单调队列

前置知识：[滑动窗口](https://www.luogu.com.cn/problem/P1886)。

单调队列可以用于查询连续区间的最值，时间/空间复杂度均为 $O(n)$，此题中比 $\text{RMQ}$ 优秀不少。

对于一个 $a\times b$ 的子矩形，如果要用单调队列求最值，不难想到将其划分为 $a$ 行，每行的最值求完后，再求行与行之间的最值。

这样做对单个子矩形来说也是 $O(ab)$ 的，看似并没有得到优化。但是别忘了我们要求好多个子矩形的最值，单调序列快就快在求多个连续区间的最值。

于是我们可以每行先进行长度为 $b$ 的滑动窗口，求出 $c_{i,j}=\min\limits_{j-b<k\leqslant j}g_{i,k}$ ，所需时间 $O(nm)$。

随后，我们再每列进行长度为 $a$ 的滑动窗口，求出 $\min\limits_{i-a<k\leqslant i}c_{k,j}$，累加到答案上即可，所需时间 $O(nm)$。

用图片解释更加清楚，矩形与样例一样，取 $b=3$ 更加方便解释：

![](https://cdn.luogu.com.cn/upload/image_hosting/70rtyfif.png)

红色、黄色、绿色分别代表每行每次滑动窗口求最值的区间。

![](https://cdn.luogu.com.cn/upload/image_hosting/twwhaapu.png)

我们就得到了蓝色的子矩形（ $c$ 数组 ）。接下来再在这个蓝色子矩形里每列进行滑动窗口取最值。

![](https://cdn.luogu.com.cn/upload/image_hosting/qnc52bds.png)

橙色、紫色分别代表每列每次滑动窗口求最值得区间。

求完后的最小值（图中的四个 $\min$ 值）相加即为答案。

---

## 代码： C++

```c++
#include <stdio.h>
int n, m, a, b, x, y, z;
int g[3001][3001], c[3001][3001], q[3001]; // q 为手写队列
long long w; // w 记录答案
int main()
{
    
    scanf("%d%d%d%d%d%d%d%d", &n, &m, &a, &b, &g[1][1], &x, &y, &z);
    for (int i(1); i < n * m; ++i) // 直接求出原矩形
        g[i / m + 1][i % m + 1] = (1ll * x * g[(i - 1) / m + 1][(i - 1) % m + 1] + y) % z;
    for (int i(1); i <= n; ++i)
    {
        int head(0), tail(-1);
        for (int j(1); j <= m; ++j) // 每行进行滑动窗口
        {
            if (q[head] == j - b && j > b) ++head; // 窗口大小为 b
            while (head <= tail && g[i][q[tail]] >= g[i][j]) --tail;
            q[++tail] = j;
            c[i][j] = g[i][q[head]];
        }
    }
    for (int j(b); j <= m; ++j) // 每列进行滑动窗口
    {
        int head(0), tail(-1);
        for (int i(1); i <= n; ++i)
        {
            if (q[head] == i - a && i > a) ++head; // 窗口大小为 a
            while (head <= tail && c[q[tail]][j] >= c[i][j]) --tail;
            q[++tail] = i;
            if (i >= a && j >= b) w += c[q[head]][j];
        }
    }
    printf("%lld\n", w);
    return 0;
}
```

---

## 作者：redegg (赞：4)

这...难道不是单调队列板子题吗？？？

为什么是省选难度？？？

我们先维护出宽度为$1$长度为$b$的点的最小值，也就是每一行处理出长度为$b$的区间里的最小值，怎么求？

对于第$i$行：

我们使用双端队列，队列里面存储的是列数，队列中前一个元素$j_1$对应的值$h[i][j_1]$一定小于后一个元素$j_2$对应的$h[i][j_2]$的，假设枚举到$j$列，对头元素$j_{front}$一定满足$j-b<j_{front}$，不满足则将对头丢掉，同时，队尾元素$j_{back}$满足$h[i][j_{back}]<h[i][j]$，否则丢掉队尾元素，在上面条件满足后，将$j$丢入队列末尾，而对于以$j$为结尾的宽$1$长$b$的矩阵里的最小值就是处理后的$h[i][j_{front}]$。

同理，我们把这些答案整理存入一个新的矩阵，然后在做一遍找长度为$1$宽度为$a$的矩阵的最小值就行了。

证明复杂度：对于任何一个元素，只会被操作两次，入队一次，出队一次，所以复杂度是O(元素)。

则此题复杂度是$O(n\times m)$，证明会需要个$log$呢。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int n,m,a,b;
long long x,y,z;
long long g[9000010];
int h[3005][3005];
int minn[3005][3005];
long long ans;
deque<int> p;
 
int main()
{
    scanf("%d%d%d%d",&n,&m,&a,&b);
    scanf("%lld%lld%lld%lld",&g[0],&x,&y,&z);
    for(int i=1;i<=9000005;i++)g[i]=(g[i-1]*x+y)%z;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            h[i][j]=g[(i-1)*m+j-1];
    }
    for(int i=1;i<=n;i++)
    {
        while(!p.empty())p.pop_back();
        for(int j=1;j<=m;j++)
        {
            while(!p.empty()&&p.front()<=j-b)if(!p.empty())p.pop_front();
            while(!p.empty()&&h[i][p.back()]>=h[i][j])if(!p.empty())p.pop_back();
            p.push_back(j);
            minn[i][j]=h[i][p.front()];
        }
    }
    while(!p.empty())p.pop_back();
    for(int j=1;j<=m;j++)
    {
        while(!p.empty())p.pop_back();
        for(int i=1;i<=n;i++)
        {
            while(!p.empty()&&p.front()<=i-a)if(!p.empty())p.pop_front();
            while(!p.empty()&&minn[p.back()][j]>=minn[i][j])if(!p.empty())p.pop_back();
            p.push_back(i);
            if(i>=a&&j>=b)
                ans+=minn[p.front()][j];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```


---

## 作者：Cappuccino_mjj (赞：1)

很好的单调队列题。

---

## [题目传送门](https://www.luogu.com.cn/problem/CF1195E)
题目意思：

给定一个 $n\times m$ 的矩阵，求出所有大小为 $a\times b$ 的子矩形中的最小值的和。

---

思路：
1. 通过题目给的要求建立二维数组 $h$。
2. 通过单调队列一行一行地扫，将扫出来地一个新的数组另存。
3. 再通过单调队列一列一列扫，这一次一边扫一遍求出 $ans$ 的值。最后输出即可。

---

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=9e6+10;
int n,m,a,b;
int x,y,z;
int g[N];
int h[3005][3005];
int hh[3005][3005];
int ans;
signed main()
{
	cin>>n>>m>>a>>b>>g[0]>>x>>y>>z;
	for(int i=1;i<=N;i++)
		g[i]=(g[i-1]*x+y)%z;
	for(int i=1;i<=n;i++)//建造高度数组
		for(int j=1;j<=m;j++)
			h[i][j]=g[(i-1)*m+j-1];
	for(int i=1;i<=n;i++)//扫行
	{
		deque<int>q;//双端队列
		for(int j=1;j<=m;j++)
		{
        //如果超出窗口的范围了，就出队
			while(!q.empty()&&q.front()<=j-b)
				q.pop_front();
        //如果高度搞过枚举的高度，出队
			while(!q.empty()&&h[i][q.back()]>=h[i][j])
				q.pop_back();
			q.push_back(j);
			hh[i][j]=h[i][q.front()];
        //用新建的数组保存新的值
		}
	}
	for(int j=1;j<=m;j++)//扫列
	{
		deque<int>q;
		for(int i=1;i<=n;i++)
		{
        //超出范围就出队
			while(!q.empty()&&q.front()<=i-a)
				q.pop_front();
        //不符合要求就出队
			while(!q.empty()&&hh[q.back()][j]>=hh[i][j])
				q.pop_back();
			q.push_back(i);
			if(i>=a&&j>=b)//保存答案
				ans+=hh[q.front()][j];
		}
	}
	cout<<ans;
	return 0;
}
```

---

完美撒花~

---

## 作者：lqz_wppr (赞：1)

## CF1195E 【OpenStreetMap】
**[去博客阅读](https://imlqz.wind-flower.cn/archives/cf574-div2-1195/)**

**题意**

给定一个 $ n\times m $ 的矩阵 $ h $ ,求出所有大小为 $ a\times b $ 的子矩形中的最小值的和.

矩阵的给定方式: 给定 $ g_0,x,y,z $ ,它们表示一个序列 $ g_i=(g_{i-1}\cdot x+y)\bmod z $ ,而 $ h_{i,j}=g_{(i-1)\cdot m+j-1} $. 

**思路** 

**单调队列模板题**  

首先生成这个矩阵（这应该不用我说了吧。。。）

由于矩阵是二维的，不能直接用单调队列，因此可以先预处理出每行的情况$f_{i,j}$表示$h_{i,j}$,$h_{i,j+a-1}$中的最小值（很明显用单调队列）

这样就把原来的$a * b$的矩阵转换成了$1 * b$的矩阵，然后再求出每个1 * b矩阵中的最小值，求和即可（还是用单调队列）

单调队列具体实现方法：

以第一次操作为例，对于每一行

1. 首先建立一个双端队列(STL deque)，双端队列中存一个int类型，表示该元素对应是第i行的第几个。然后扫描该行，设扫到该行第j个元素
2. 首先检查对头的元素与j的距离是否大于a（如果大于说明这个最小值已经“过期”，弹出队头，并再次检查）
3. 最后剩下的队头就是$j-a+1$,$j-1$之间的最小值，与当前的$h_{i,j}$取个min即得到了一个最小值，累加到答案中
4. 检查队尾元素值是否大于$h_{i,j}$，如果大于，弹出队尾并重复这一步（因为这些元素在j之前就被加入，且值比j大，未来肯定没用，为了维护队列的单调性，直接弹出即可）
5. 把j插入到队尾

为什么这样可行？原因在于维护了一个队列，其中队列中每个下标对应的元素值递增，这样每次取出队头就得到了该次的最小值。每个元素平均出队/入队1次，因此复杂度为$O(nm)$

**Code请见博客**  

---

## 作者：xukuan (赞：1)

二维RMQ模板题

这题实际就是让我们求$\sum^{i=1,j=1}_{i<=n-a+1,j<=m-b+1} min H_{i,j}$

如果是一维的话，这题就是[滑动窗口](http://poj.org/problem?id=2823)，一个单调队列即可

那么二维的怎么办？

再加一个单调队列即可

PS：RMQ也可以用ST表或线段树做，在此不再多讲，使用线段树的同学注意常数优化

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll n,m,a,b,x,y,z,ans,g[3010*3010],h[3010][3010],f[3010][3010];
deque<ll> q;

int main(){
	cin>>n>>m>>a>>b;
	cin>>g[0]>>x>>y>>z;
	for(ll i=1; i<=n*m; i++) g[i]=(g[i-1]*x+y)%z;
	for(ll i=1; i<=n; i++){
		for(ll j=1; j<=m; j++) h[i][j]=g[(i-1)*m+j-1];
	}
  	//对H进行单调队列
	for(ll i=1; i<=n; i++){
		while(!q.empty()) q.pop_front();
		for(ll j=1; j<=m; j++){
			while(!q.empty()&&h[i][q.back()]>=h[i][j]) q.pop_back();
			if(!q.empty()&&q.front()+b-1<j) q.pop_front();
			q.push_back(j);
			f[i][j]=h[i][q.front()];
		}
	}
	//对f，也就是对h进行单调队列之后的最小值，进行单调队列
	for(ll j=1; j<=m; j++){
		while(!q.empty()) q.pop_front();
		for(ll i=1; i<=n; i++){
			while(!q.empty()&&f[q.back()][j]>=f[i][j]) q.pop_back();
			if(!q.empty()&&q.front()+a-1<i) q.pop_front();
			q.push_back(i);
			if(i>=a&&j>=b) ans+=f[q.front()][j];
			//如果左上角的大小达到了，就计入答案
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16791321.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1195E)
## 思路
单调队列板子。

设 $b_{i,j}$ 表示第 $i$ 行，区间为 $j$ 到 $j+y-1$ 的最小值，不难发现这个可以用单调队列 $O(nm)$ 预处理出来。

接下来我们的问题就转化成了有一个矩阵，求所有宽为 $1$，长为 $x$ 的子矩阵的最小值之和。

这个问题也十分好做，直接枚举列，然后在每一行单调队列即可。
## 代码
```cpp
/*
A tree without skin will surely die. 
A man without face is invincible.
*/
#include<bits/stdc++.h>
using namespace std;
int const N=3e3+10;
int ans,n,m,a[N][N],b[N][N],g[N*N];
struct node{int w,id;}q[N];
inline void go(int x,int y){
	for (int i=1;i<=n;++i){
		int l=1,r=0;
		for (int j=1;j<=y;++j){
			while (l<=r && q[r].w>=a[i][j]) --r;
			q[++r].w=a[i][j];q[r].id=j;
		}
		b[i][1]=q[l].w;
		for (int j=y+1;j<=m;++j){
			while (q[l].id<=j-y && l<=r) ++l;
 			while (l<=r && q[r].w>=a[i][j]) --r;
 			q[++r].w=a[i][j];q[r].id=j;
 			b[i][j-y+1]=q[l].w;
		}
	}
	for (int j=1;j<=m-y+1;++j){
		int l=1,r=0;
		for (int i=1;i<=x;++i){
			while (l<=r && q[r].w>=b[i][j]) --r;
			q[++r].w=b[i][j];q[r].id=i;
		}
		ans+=q[l].w;
		for (int i=x+1;i<=n;++i){
			while (q[l].id<=i-x && l<=r) ++l;
			while (l<=r && q[r].w>=b[i][j]) --r;
			q[++r].w=b[i][j];q[r].id=i;ans+=q[l].w;
		}
	}
}
signed main(){
	//读入
	for (int i=1;i<=n*m;++i) g[i]=(g[i-1]*xx%zz+yy)%zz;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j) a[i][j]=g[(i-1)*m+j-1];
	go(x,y);//输出
	return 0;
}
```


---

## 作者：gary2005 (赞：0)

st表

先用st表维护一个dp数组

dp[i][j]表示从第i,j号顶点向下a个单位之中的最小值

然后算已i,j为左上角时，答案就加上min(dp[i][j]~dp[i][j+b-1])再用一个st表就ok了。
```cpp
//* AuThOr GaRyMr *//
//solution by GWJ
//FIR. use st algor. to calc. the dp[i][j](i<=n-a+1)->from the cell i,j to the cell i+a-1,j 's mini val
//remember to reuse it
#include<bits/stdc++.h>
#define rb(a,b,c) for(int a=b;a<=c;++a)
#define rl(a,b,c) for(int a=b;a>=c;--a)
#define niv vector<int>
#define LL long long
#define IT iterator
#define PB(a) push_back(a)
#define II(a,b) make_pair(a,b)
#define FIR first
#define SEC second
using namespace std;
const int INF=0x3f3f3f3f;
typedef pair<int,int> mp;
typedef pair<mp,mp> superpair;
LL g[8999999+10];int x,y,z;int n,m,a,b;
LL mat[3001][3001];
LL st_algor[3001][13];//<- reuse guy
LL dp[3001][3001];
LL res=0;
void calc(){
	int ci2=int(log2(double(b)));
	rb(i,1,n-a+1){
		rb(j,1,m) st_algor[j][0]=dp[i][j];
		rb(k,1,12){
			rb(j,1,m){
				if(j+(1<<k)-1>m) break;
				st_algor[j][k]=min(st_algor[j][k-1],st_algor[j+(1<<(k-1))][k-1]);
			}
		}
		rb(j,1,m-b+1){
			res+=min(st_algor[j][ci2],st_algor[j+b-(1<<(ci2))][ci2]);
		}
	}
}
int main(){
	scanf("%d %d %d %d",&n,&m,&a,&b);
	scanf("%I64d %d %d %d",&g[0],&x,&y,&z);
	rb(i,1,8999999){
		g[i]=g[i-1]*x;
		g[i]+=y;
		g[i]%=z;
	}
	rb(i,1,n){
		rb(j,1,m){
			mat[i][j]=g[(i-1)*m+j-1];
		}
	}
	int ci=int(log2(double(a)));
	rb(j,1,m){
		rb(i,1,n) st_algor[i][0]=mat[i][j];
		rb(k,1,12){
			rb(i,1,n){
				if((i+(1<<k))-1>n) break;
				st_algor[i][k]=min(st_algor[i][k-1],st_algor[i+(1<<(k-1))][k-1]);
			}
		}
		rb(i,1,n-a+1){
			dp[i][j]=min(st_algor[i][ci],st_algor[i+a-(1<<ci)][ci]);
		}
	}
	calc();
	printf("%I64d\n",res);
	return 0;
}
```


---

