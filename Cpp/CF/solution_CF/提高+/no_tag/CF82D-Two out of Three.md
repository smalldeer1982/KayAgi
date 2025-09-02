# Two out of Three

## 题目描述

Vasya has recently developed a new algorithm to optimize the reception of customer flow and he considered the following problem.

Let the queue to the cashier contain $ n $ people, at that each of them is characterized by a positive integer $ a_{i} $ — that is the time needed to work with this customer. What is special about this very cashier is that it can serve two customers simultaneously. However, if two customers need $ a_{i} $ and $ a_{j} $ of time to be served, the time needed to work with both of them customers is equal to $ max(a_{i},a_{j}) $ . Please note that working with customers is an uninterruptable process, and therefore, if two people simultaneously come to the cashier, it means that they begin to be served simultaneously, and will both finish simultaneously (it is possible that one of them will have to wait).

Vasya used in his algorithm an ingenious heuristic — as long as the queue has more than one person waiting, then some two people of the first three standing in front of the queue are sent simultaneously. If the queue has only one customer number $ i $ , then he goes to the cashier, and is served within $ a_{i} $ of time. Note that the total number of phases of serving a customer will always be equal to $ ⌈n/2⌉ $ .

Vasya thinks that this method will help to cope with the queues we all hate. That's why he asked you to work out a program that will determine the minimum time during which the whole queue will be served using this algorithm.

## 样例 #1

### 输入

```
4
1 2 3 4
```

### 输出

```
6
1 2
3 4
```

## 样例 #2

### 输入

```
5
2 4 3 1 4
```

### 输出

```
8
1 3
2 5
4
```

# 题解

## 作者：lenlen (赞：15)

比较好的一道 DP 题。

### Problem

题目大意：给定一个序列，每次从前三个中选两个值并取他们的最大值累加，不足 3 个就取剩下的 1 个或 2 个的最大值累加，求累计的和的最小值以及取法。

数据范围：$ n \leq 1000,a_i \leq 10^6$。

### Solution

考虑 DP 设状态，可以发现每一次会取两个数，也就是会剩下一个数，所以我们可以把剩下的那个数来设状态。而且可以发现，当我们执行到第 $i$ 轮的时候，我们考虑的必然是 $2i,2i+1,j$ （ $j$ 代表之前一轮中剩下的那个数）三个数，所以转移就明显了： $dp_{i,j}$ 表示第 $i$ 轮选择后剩下的是第 $j$ 个数的最小累计和。

初始状态：$dp_{1,1}=\max(a_1,a_2),dp_{1,2}=\max(a_1,a_3),dp_{1,3}=\max(a_1,a_2)$。

转移方程：

$$dp_{i,j}=dp_{i-1,j}+\max(a_{2i},a_{2i+1})$$

当第 $i$ 轮选择的是 $[1,2i-1]$ 中的数时，显然第 $i-1$ 轮剩下的也必须是第 $j$ 个数，而第 $i$ 轮选择的是 $\max(a_{2i},a_{2i+1})$。

$$dp_{i,2i}=dp_{i-1,j}+\max(a_{j},a_{2i+1})$$

$$dp_{i,2i+1}=dp_{i-1,j}+\max(a_{j},a_{2i})$$

可以发现，当个数为奇数的时候，最后会有一个落单的，即我们统计出 $dp_{\lfloor n/2 \rfloor,i}+a_i$ 的最大值就可以了。

若为偶数，我的处理方法是加一个数 $inf$ 变成奇数，最后不输出最后一项即可。

同时记录一下前驱状态就可以了。

另外还要判断一下，当只有一个或者两个的时候要直接输出。

### Code

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1732;
int a[N],n,dp[N][N],ans=0x3f3f3f3f;
int pre[N][N],ans1,pr[N][N][2];
int mx(int x,int y){return x>y?x:y;}
int mi(int x,int y){return x<y?x:y;}
void dfs(int x,int y)
{
	if(x==0) return ;
	int xx=x-1,yy=pre[x][y];
	dfs(xx,yy);
	printf("%d %d\n",pr[x][y][0],pr[x][y][1]);
}
int main()
{
	bool flag=false;
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	if(n==1) 
	{
		printf("%d\n1\n",a[1]);
		return 0;
	}
	if(n==2)
	{
		printf("%d\n1 2\n",mx(a[1],a[2]));
		return 0;
	}
	if(n%2==0) ++n,a[n]=0x3f3f3f3f,flag=true;
	memset(dp,0x3f,sizeof(dp));
	dp[1][1]=mx(a[2],a[3]);pr[1][1][0]=2;pr[1][1][1]=3;
	dp[1][2]=mx(a[1],a[3]);pr[1][2][0]=1;pr[1][2][1]=3;
	dp[1][3]=mx(a[1],a[2]);pr[1][3][0]=1;pr[1][3][1]=2;
	for(int i=2;i<=(n>>1);++i)
	{
		for(int j=1;j<(i<<1);++j)
		{
			if(dp[i-1][j]+mx(a[j],a[i<<1])<dp[i][i<<1|1]) dp[i][i<<1|1]=dp[i-1][j]+mx(a[j],a[i<<1]),pre[i][i<<1|1]=j,pr[i][i<<1|1][0]=j,pr[i][i<<1|1][1]=(i<<1);
			if(dp[i-1][j]+mx(a[j],a[i<<1|1])<dp[i][i<<1]) dp[i][i<<1]=dp[i-1][j]+mx(a[j],a[i<<1|1]),pre[i][i<<1]=j,pr[i][i<<1][0]=j,pr[i][i<<1][1]=(i<<1|1);
			if(dp[i-1][j]+mx(a[i<<1|1],a[i<<1])<dp[i][j]) dp[i][j]=dp[i-1][j]+mx(a[i<<1|1],a[i<<1]),pre[i][j]=j,pr[i][j][0]=(i<<1),pr[i][j][1]=(i<<1|1);
		}
	}
	for(int i=1;i<=n;i++) 
	{
		if(flag&&i==n) ans=dp[n>>1][i],ans1=i;
		else if(ans>dp[n>>1][i]+a[i]) ans=dp[n>>1][i]+a[i],ans1=i;
	}
	printf("%d\n",ans);
	dfs(n>>1,ans1);
	if(!flag) printf("%d\n",ans1);
}
```


---

## 作者：Tony102 (赞：7)

[Link](https://www.luogu.com.cn/problem/CF82D)

[更好的阅读体验](https://tony102.xyz/index.php/2020/11/21/cf82d-two-out-of-three/)


### Sol

状态不好设, [yzhx](https://www.cnblogs.com/yzhx)讲了才会

每一轮收银都会剩下一个人没有买单,也就是说,第$x$轮结束时在 $[1, 2 * x - 1]$ 中将会有 $x$ 人剩下

每次都转移被选中的两个人似乎不好搞,就看看能不能转移那个没被选中的人.

设 $f[i][j]$ 表示第 $i$ 次买单结束以后剩下了第 $j$ 个人没有买单

那么枚举没有买单的那个人 $j$ , 这一轮买单的第 $2 \times i - 1$ 和 $2 \times i $ 个人

注意到每次转移的时候 $2 \times i - 1$ 和 $2 \times i$ 个人也有可能是被选中的,也要转移

那么转移方程式是:

$$f[i][j] = min\{ f[i-1][j] + max(t[a], t[b]) \}$$

$a$, $b$ 就是 $2 \times i - 1$ 和 $2 \times i$

除此之外还要记一下方案

没了



### Code

代码环节还是我最喜欢的环节

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int SIZE = 1e3 + 5;
const int inf = 0x7f7f7f7f;

int n;
int t[SIZE], f[SIZE][SIZE];

struct opt {
	int i, j, k;
} path[SIZE][SIZE];

namespace ae86 {
	const int bufl = 1 << 15;
	char buf[bufl], *s = buf, *t = buf;
	inline int fetch() {
		if (s == t) { t = (s = buf) + fread(buf, 1, bufl, stdin); if (s == t) return EOF; }
		return *s++;
	}
	inline int read() {
		int a = 0, b = 1, c = fetch();
		while (!isdigit(c))b ^= c == '-', c = fetch();
		while (isdigit(c)) a = a * 10 + c - 48, c = fetch();
		return b ? a : -a;
	}
}
using ae86::read;

inline void output(int i, int j)
{
	if (i != 1) output(i - 1, path[i][j].k);
	if (path[i][j].i > n) { printf("%lld\n", path[i][j].j); return; }
	if (path[i][j].j > n) { printf("%lld\n", path[i][j].i); return; }
	printf("%lld %lld\n", path[i][j].i, path[i][j].j);
}

signed main()
{
	// freopen("code.in", "r", stdin);
	// freopen("code.out", "w", stdout);
	n = read();
	for (int i = 1; i <= n; ++ i) t[i] = read();
	t[++ n] = 0;
	memset(f, inf, sizeof(f));
	f[0][1] = 0;
	for (int i = 1, a, b; i <= n / 2; ++ i) {
		a = (i << 1), b = a + 1;
		for (int j = 1; j < a; ++ j) {
			if (f[i - 1][j] + std::max(t[a], t[b]) < f[i][j]) {
				f[i][j] = f[i - 1][j] + std::max(t[a], t[b]);
				path[i][j] = (opt) {a, b, j};
			}
			if (f[i - 1][j] + std::max(t[a], t[j]) < f[i][b]) {
				f[i][b] = f[i - 1][j] + std::max(t[a], t[j]);
				path[i][b] = (opt) {a, j, j};
			}
			if (f[i - 1][j] + std::max(t[b], t[j]) < f[i][a]) {
				f[i][a] = f[i - 1][j] + std::max(t[b], t[j]);
				path[i][a] = (opt) {b, j, j};
			}
		}
	}
	printf("%lld\n", f[n / 2][n]);
	output(n / 2, n);
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：4)

补上周的作业题，直接用的老师讲的法子。。不知道有没有雷同。

------------

首先考虑肯定是个 dp，要求最少的总时间，且前后有一定关联。

然后，受题目名字的启发，每次从三个人中挑两个继续跑。

其中一定有两个是紧连的，其余一个可能一起，也可能是从前面一路淘汰下来的。

考虑用其中两个的最大值加上剩下一个与后面的继续匹配的答案进行转移。

老师说可以正着写但麻烦，于是写记搜。

特判只剩一个或两个的边界条件。

至于记录路径直接重新跑一遍，根据答案反推就行。

时间复杂度 $\operatorname{O}(n^2)$，实际比这少很多。

------------

第一遍写的时候我把下标和数值整混了，结果还能过样例。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+84;
int n,a[maxn],dp[maxn][maxn];
inline int minsr(int x,int y,int z){
    return min(min(x,y),z);
}
inline int dfs(int now,int last){
    if(now==n+1)
        dp[now][last]=a[last];
    else if(now==n)
        dp[now][last]=max(a[now],a[last]);
    else if(!dp[now][last])
        dp[now][last]=minsr(max(a[now],a[last])+dfs(now+2,now+1),max(a[now],a[now+1])+dfs(now+2,last),max(a[now+1],a[last])+dfs(now+2,now));
    return dp[now][last];
}
inline void get_path(int now,int last){
    if(now==n+1)
        printf("%d",last);
    else if(now==n)
        printf("%d %d",last,now);
    else if(dp[now][last]==max(a[now],a[last])+dp[now+2][now+1]){
        printf("%d %d\n",last,now);
        get_path(now+2,now+1);
    }
    else if(dp[now][last]==max(a[now],a[now+1])+dp[now+2][last]){
        printf("%d %d\n",now,now+1);
        get_path(now+2,last);
    }
    else{
        printf("%d %d\n",last,now+1);
        get_path(now+2,now);
    }
    return ;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    dfs(2,1);
    printf("%d\n",dp[2][1]);
    get_path(2,1);
    return 0;
}
//Sherry
```


---

## 作者：Godzilla (赞：4)

看了一眼题解。

### 描述：

给定一个序列，每次可以删除前 $3$ 个中的两个，代价为它们的 $a$ 取 $\max$ ，剩余一个时取一个代价就为它的 $a$ ，求最少代价和。

### 思路：

考虑模拟数据，发现操作有很好的性质：剩余序列只会由单独一个位置+后缀序列，其中后缀序列的左端点在单独一个位置之后。

第一次操作符合要求，模拟以下，一个单独位置+后缀序列在三种类型的操作后仍符合要求。

设 $f(i,j)$ 表示单独一个位置为 $i$ ，后缀序列左端点为 $j$ ，其中 $i\le j$ ，当 $i=j$ 时，表示无单独后缀序列。

转移分类讨论取第一个和第二个，取第一个和第三个，取第二个和第三个即可。

发现可能出现删除 $1$ 个位置的操作，考虑加入 $n+1$ 和 $n+2$ ， $a$ 皆为 $0$ ，那么当 $n$ 为奇数时答案为 $f(n+2,n+2)$ ，当 $n$ 为偶数时答案为 $f(n+1,n+1)$ 。

输出路径就用 $pre(i,j,0/1)$ 表示 $f(i,j)$ 的前继状态，从最终状态到推即可。

### 代码：

```c++
#include <bits/stdc++.h>

#define LL long long
#define PR pair <int, int>
#define MK make_pair
#define fi first
#define se second
#define pb push_back
#define Low(x) (x & (-x))

using namespace std;

const int kN = 1e3 + 5, kInf = 2e9;

int n, f[kN][kN], a[kN], pre[kN][kN][2], tot;
PR ans[kN];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  for (int i = 1; i <= n + 2; ++i)
    for (int j = 1; j <= n + 2; ++j)
      f[i][j] = kInf;
  f[1][1] = 0;
  for (int i = 1; i <= n + 2; ++i) {
    if (f[i + 2][i + 2] > f[i][i] + max(a[i], a[i + 1])) {
      f[i + 2][i + 2] = f[i][i] + max(a[i], a[i + 1]);
      pre[i + 2][i + 2][0] = pre[i + 2][i + 2][1] = i;
    }
    if (f[i + 1][i + 3] > f[i][i] + max(a[i], a[i + 2])) {
      f[i + 1][i + 3] = f[i][i] + max(a[i], a[i + 2]);
      pre[i + 1][i + 3][0] = pre[i + 1][i + 3][1] = i;
    }
    if (f[i][i + 3] > f[i][i] + max(a[i + 1], a[i + 2])) {
      f[i][i + 3] = f[i][i] + max(a[i + 1], a[i + 2]);
      pre[i][i + 3][0] = pre[i][i + 3][1] = i;
    }
    //f(i,i)
    for (int j = i + 1; j <= n + 2; ++j) {
      if (f[j + 1][j + 1] > f[i][j] + max(a[i], a[j])) {
	f[j + 1][j + 1] = f[i][j] + max(a[i], a[j]);
	pre[j + 1][j + 1][0] = i, pre[j + 1][j + 1][1] = j;
      }
      if (f[j][j + 2] > f[i][j] + max(a[i], a[j + 1])) {
	f[j][j + 2] = f[i][j] + max(a[i], a[j + 1]);
	pre[j][j + 2][0] = i, pre[j][j + 2][1] = j;
      }
      if (f[i][j + 2] > f[i][j] + max(a[j], a[j + 1])) {
	f[i][j + 2] = f[i][j] + max(a[j], a[j + 1]);
	pre[i][j + 2][0] = i, pre[i][j + 2][1] = j;
      }
      //f(i,j) j>i
    }
  }
  int x, y;
  if (n & 1) printf("%d\n", f[n + 2][n + 2]), x = y = n + 2;
  else printf("%d\n", f[n + 1][n + 1]), x = y = n + 1;
  while (x > 1 || y > 1) {
    int gx = pre[x][y][0], gy = pre[x][y][1];
    if (gx == gy) {
      if (x == gx + 2 && y == gy + 2) ans[++tot] = MK(gx, gx + 1);
      if (x == gx + 1 && y == gy + 3) ans[++tot] = MK(gx, gx + 2);
      if (x == gx && y == gy + 3) ans[++tot] = MK(gx + 1, gx + 2);
    }
    else {
      if (x == gy + 1 && y == gy + 1) ans[++tot] = MK(gx, gy);
      if (x == gy && y == gy + 2) ans[++tot] = MK(gx, gy + 1);
      if (x == gx && y == gy + 2) ans[++tot] = MK(gy, gy + 1);
    }
    x = gx, y = gy;
  }
  while (tot) {
    if (ans[tot].fi <= n) printf("%d ", ans[tot].fi);
    if (ans[tot].se <= n) printf("%d ", ans[tot].se);
    printf("\n"); tot--;
  }
  return 0;
}

```



---

## 作者：hwx12233 (赞：4)

[CF82D Two out of Three](https://www.luogu.com.cn/problem/CF82D)

楼上的大佬已经说了很多了

在此补充一点

做到这道题时首先我是没有任何想法的

因为前面的人剩下会对后面产生影响

有一定的后效性

在dalao的指导下我们可以发现

因为每次只能从前三个人中选2个

不断选两个人那就意味着**前三人中必定有一个人剩下**

**那我们就可以记录那个剩下的人**

再想转移方法

因为我们每次取的是两个人

故可以每次枚举一对人

然后再枚举前面剩下了哪个人来进行转移

组数为n/2上取整这样可以包括$a[n+1]$


答案便是$dp[m][n+1]$

因为$a[n+1]$为$0$可以选上最后剩下的

$dp[i][j]$表示第$i$个$2$人组时第$j$个人不取所花费的最短时间

初始化:

```cpp
dp[1][1]=max(a[2],a[3])
dp[1][2]=max(a[1],a[3])
dp[1][3]=max(a[1],a[2])
```

转移：i为组数 x为 i * 2 y为 i * 2+1
```cpp
dp[i][x]=min(dp[i][x],dp[i-1][j]+max(a[j],a[y]));
dp[i][y]=min(dp[i][y],dp[i-1][j]+max(a[x],a[j]));
dp[i][j]=min(dp[i][j],dp[i-1][j]+max(a[x],a[y]));
```
下面是代码
```cpp
int n,a[N],dp[N][N],out[N][N][3];
inline void ass(int i,int j,int x,int y,int z){
	out[i][j][0]=x;out[i][j][1]=y;out[i][j][2]=z;
}
inline void print(int x,int y){
	if(y==0)return;
	print(x-1,out[x][y][2]);
	if(out[x][y][0]<=n)
		cout<<out[x][y][0]<<" ";
	if(out[x][y][1]<=n)
		cout<<out[x][y][1]<<" ";
	cout<<endl;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	memset(dp,63,sizeof(dp));
	dp[1][1]=max(a[2],a[3]);
	dp[1][2]=max(a[1],a[3]);
	dp[1][3]=max(a[2],a[1]);
	ass(1,1,2,3,0);
	ass(1,2,1,3,0);
	ass(1,3,1,2,0);
	int m=(n&1)?n/2+1:n/2;	
	for(int i=2;i<=m;i++){
		int x=i<<1,y=i<<1|1;
		for(int j=1;j<x;j++){
			if(dp[i][x]>dp[i-1][j]+max(a[j],a[y])){
				dp[i][x]=dp[i-1][j]+max(a[j],a[y]);
				ass(i,x,j,y,j);
			}
			if(dp[i][y]>dp[i-1][j]+max(a[j],a[x])){
				dp[i][y]=dp[i-1][j]+max(a[j],a[x]);
				ass(i,y,j,x,j);
			}
			if(dp[i][j]>dp[i-1][j]+max(a[y],a[x])){
				dp[i][j]=dp[i-1][j]+max(a[y],a[x]);
				ass(i,j,x,y,j);
			}
		}
	}
	cout<<dp[m][n+1]<<endl;
	print(m,n+1);
}
```











---

## 作者：基地A_I (赞：4)

## 前言

全网唯一不同题解，~~把我的青春热血奉献给了洛谷~~

设 $f[i][j]$ 表示第 $i$ 次选取留下来的数是 $k$ 的最小花费

枚举前面的留下来的点 $k$ 当前能留下的点只有 $(2*i),(2*i+1),k$ 中的一个，时间复杂度 $O(n^2)$ ~~其实时间复杂度是 $O(\frac{n^2}{4})$ 据说这个复杂度CF可以跑过百万~~

选取次数是 $n/2$ 向上取整。因最后什么点也不留下，$a[n+1]=0$，所以答案可以为 $f[m][n+1]$ ($m=n/2$向上取整)

路径记录就是挺基础的东西了，如果不会看看代码想想就明白了.

Code

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#define INF 0x3f3f3f3f
using namespace std;
inline int read() {
	int x=0,f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<3)+(x<<1)+(ch^48); ch=getchar(); }
	return x * f;
}
const int N = 1007;
int n;
int a[N];
int f[N][N];
struct operation {
	int x,y,pre;
}p[N][N];
inline int Const(int x,int y) {
	return max(a[x], a[y]);
}
void output(int now,int pos) {
	if(now == 0) return ;
	output(now-1,p[now][pos].pre);
	if(a[p[now][pos].x])	
		printf("%d ",p[now][pos].x);
	if(a[p[now][pos].y])
		printf("%d",p[now][pos].y);
	puts("");
}
int main()
{
	n = read();
	for(int i=1;i<=n;++i)
		a[i] = read();
	memset(f, 0x3f, sizeof(f));
	f[1][1] = max(a[2],a[3]); f[1][2] = max(a[1],a[3]); f[1][3] = max(a[1],a[2]);
	p[1][1] = (operation)<%2,3,0%>;
	p[1][2] = (operation)<%1,3,0%>;
	p[1][3] = (operation)<%1,2,0%>;
	int m = n&1 ? n/2+1 : n/2;
	for(int i=2;i<=m;++i) {
		int x = 2*i, y = 2*i+1;	// i次选取的最后两个数 
		for(int k=1;k<x;++k) {	//枚举上一次留下的数 
			if(f[i-1][k]+Const(y,k) < f[i][x]) {
				f[i][x] = f[i-1][k]+Const(y,k);
				p[i][x] = (operation)<%k,y,k%>;
			}
			if(f[i-1][k]+Const(x,k) < f[i][y]) {
				f[i][y] = f[i-1][k]+Const(x,k);
				p[i][y] = (operation)<%k,x,k%>;
			}
			if(f[i-1][k]+Const(x,y) < f[i][k]) {
				f[i][k] = f[i-1][k]+Const(x,y);
				p[i][k] = (operation)<%x,y,k%>;
			}
			// f[i][x] = min(f[i][x], f[i-1][k]+Const(y,k));
			// f[i][y] = min(f[i][y], f[i-1][k]+Const(x,k));
			// f[i][k] = min(f[i][k], f[i-1][k]+Const(x,y));
		}
	}
	int ans = f[m][n+1];
	printf("%d\n",ans);
	output(m,n+1);
	return 0;
}
```

其实代码还是不很完善与简洁明了的，因为我主要是刷题。希望后来刷到这题的OIer能写出更好的题解！QwQ

---

## 作者：m256i (赞：3)

手玩一下可以发现无论怎么删剩下的序列在原序列中一定是一个点加上一段连续的区间。所以设 $f(x, l)$ 是 $x$ 与 $[l, n]$ 这段区间的答案，那么有：

* 删 1、2：$f(l+1, l+2)+\max(a_x,a_l)$
* 删 1、3：$f(l, l+2)+\max(a_x,a_{l+1})$
* 删 2、3：$f(x, l+2)+\max(a_l,a_{l+1})$

取最小值记忆化搜索就行。注意边界要特判区间长度为 0 和 1 的两种情况。

输出的时候重新搜一遍就好。

参考代码：

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#include <bitset>
#include <algorithm>
typedef long long ll;
typedef unsigned long long ull;

template <typename T>
inline T max(T a, T b){return (a>b) ? a : b;}
template <typename T>
inline T min(T a, T b){return (a<b) ? a : b;}

template <typename T>
void read(T &x){
	static char ch;
	x = 0;
	while (!isdigit(ch=getchar()));
	do x = (x<<3)+(x<<1)+(ch^'0');
	while (isdigit(ch=getchar()));
}

template <typename T>
void write(T x, char c = ' '){
	static char st[100], *p;
	if (x < 0) putchar('-'), x = -x;
	if (x == 0) putchar('0');
	for (p = st; x; x /= 10) *++p = x%10;
	for (; p != st; --p) putchar(*p|'0');
	putchar(c);
}

template <typename T>
inline void writeln(T x){write(x, '\n');}

int a[1005], n, dp[1005][1005];

int dfs(int x, int l){
	if (l > n) return a[x];
	if (l == n) return max(a[x], a[l]);
	if (dp[x][l]) return dp[x][l];
	int l1 = dfs(l+1, l+2)+max(a[x], a[l]), // 1 2
	l2 = dfs(l, l+2)+max(a[x], a[l+1]), // 1 3
	l3 = dfs(x, l+2)+max(a[l], a[l+1]); // 2 3
	return dp[x][l]=min(l1, min(l2, l3));
}

void output(int x, int l){
	if (l > n){
		writeln(x); return;
	}
	if (l == n){
		write(x), writeln(l); return;
	}
	int l1 = dfs(l+1, l+2)+max(a[x], a[l]), // 1 2
		l2 = dfs(l, l+2)+max(a[x], a[l+1]), // 1 3
		l3 = dfs(x, l+2)+max(a[l], a[l+1]); // 2 3
	if (l1 < l2){
		if (l1 < l3) write(x), writeln(l), output(l+1, l+2); // l1
		else write(l), writeln(l+1), output(x, l+2); // l3
	}
	else{
		if (l2 < l3) write(x), writeln(l+1), output(l, l+2); // l2
		else write(l), writeln(l+1), output(x, l+2); // l3
	}
}

int main(){
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	read(n); for (int i = 1; i <= n; ++i) read(a[i]);
	writeln(dfs(1, 2));
	output(1, 2);
	
	
	return 0;
}
```

---

## 作者：LCGUO (赞：1)

#### 【题目大意】

一队顾客排在一位收银员前面。

他采取这样一个策略：每次，假如队伍有至少两人，就会从前面的前三人（如果有）中选取两位一起收银，所花费的时间为这两人单独收银所需时间的最大值；如果只有两人，那么一起收银；如果只有一人，那么单独收银。

请问所需的总时间最少是多少，以及总时间最少的方案。（$1\leq n\leq1000,1\leq a_i\leq 10^6$）


---

设 $f_{i,j}$ 代表当前三个人中选择的两个人为第 $i$ 个和第 $j$ 个人的时候，最少花费的时间（$i<j$）。

状态转移方程为：
$$
\large f(i,j)=\min\begin{cases}\max(a_i,a_j)+f(j+1,j+2) \\\max(a_i,a_{j+1})+f(j,j+2)\\ \max(a_j,a_{j+1})+f(i,j+2)\end{cases}
$$
我们可以用记忆化搜索实现。

至于输出方案，我们可以再进行一遍深搜，判断当前状态是由哪一状态转移过来的。

代码如下：

```cpp
#include<bits/stdc++.h>
#define rint register int
using namespace std;
inline int read(){
    int s=0,f=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=0;c=getchar();}
    while(c>='0'&&c<='9') s=(s<<1)+(s<<3)+(c^48),c=getchar();
    return f?s:-s;
}
int n,f[1010][1010],a[1010];
int dfs(int x,int y){
    if(f[x][y]) return f[x][y];
    if(y==n+1) return f[x][y]=a[x];
    if(y==n) return f[x][y]=max(a[x],a[y]);
    f[x][y]=max(a[x],a[y])+dfs(y+1,y+2);
    f[x][y]=min(f[x][y],max(a[x],a[y+1])+dfs(y,y+2));
    f[x][y]=min(f[x][y],max(a[y],a[y+1])+dfs(x,y+2));
    return f[x][y];
}
void Print(int x,int y){
    if(y==n+1) return printf("%d\n",x),void();
    if(y==n) return printf("%d %d\n",x,y),void();
    if(f[x][y]==max(a[x],a[y])+f[y+1][y+2])
        printf("%d %d\n",x,y),Print(y+1,y+2);
    else if(f[x][y]==max(a[x],a[y+1])+f[y][y+2])
        printf("%d %d\n",x,y+1),Print(y,y+2);
    else if(f[x][y]==max(a[y],a[y+1])+f[x][y+2])
        printf("%d %d\n",y,y+1),Print(x,y+2);
}
int main(){
    n=read();
    for(rint i=1;i<=n;i++) a[i]=read();
    dfs(1,2);
    printf("%d\n",f[1][2]);
    Print(1,2);
    return 0;
}
```



---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 2000}$
---
### 解题思路：

动态规划。

设 $f_{i,j}$ 表示考虑到第 $i$ 次结账，其中第 $j$ 个人被留了下来的最短时间。

然后考虑转移，对于每一种状态，留下来的那一个人有可能是之前的某一个人，也有可能是让之前的某一个人结账留下当前新加入的那两个人中的一个。

具体讨论每一种情况：

1. 留下来的人是之前的某一个人。直接枚举这个人，结账的是当前的那两个人，也就是 $f_{i,j}=f_{i-1,j}+\max(a_{2i},a_{2i+1})$。

2. 留下来的人是当前的某一个人。枚举之前没有结账的是哪一个人，结账的就是剩下的两个人。由于新加入的有两个，对称地有：$f_{i,2i+t}=\min(f_{i-1,j}+\max(a_j,a_{2i+1-t}))$。其中 $t\in[0,1]$，且 $t\in Z$。

可以将 $a_{n+1}$ 设定为正无穷，这样如果 $n$ 是偶数，最后的答案一定在 $f_{\left\lfloor\frac{n}{2}\right\rfloor,n+1}$ 中，也就是一定会将一个不存在的 $n+1$ 保留下来，让所以其它的进行结账。如果 $n$ 是奇数，则需要枚举最后保留下来的那个顾客，单独结账。

注意本题还要求输出路径。

---
### 代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,a[1005],f[1005][1005],fr[1005][1005],p[1005][1005][2],minx,mini,now;
int rec[1005][2];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	memset(f,63,sizeof(f));
	a[n+1]=1e9;f[0][1]=0;
	for(int i=1;i<=n/2;i++){
		for(int j=1;j<2*i;j++){
			if(f[i-1][j]+max(a[i*2],a[i*2+1])<f[i][j]){
				f[i][j]=f[i-1][j]+max(a[i*2],a[i*2+1]);
				fr[i][j]=j;
				p[i][j][0]=i*2;
				p[i][j][1]=i*2+1;
			}
			if(f[i][i*2]>f[i-1][j]+max(a[i*2+1],a[j])){
				f[i][i*2]=f[i-1][j]+max(a[i*2+1],a[j]);
				fr[i][i*2]=j;
				p[i][i*2][0]=j;
				p[i][i*2][1]=i*2+1;
			}
			if(f[i][i*2+1]>f[i-1][j]+max(a[i*2],a[j])){
				f[i][i*2+1]=f[i-1][j]+max(a[i*2],a[j]);
				fr[i][i*2+1]=j;
				p[i][i*2+1][0]=i*2;
				p[i][i*2+1][1]=j;
			}
		}
	}
	if(n%2==0){
		printf("%d\n",f[n/2][n+1]);
		int now=n+1;
		for(int i=n/2;i>=1;i--){
			rec[i][0]=min(p[i][now][0],p[i][now][1]);
			rec[i][1]=max(p[i][now][0],p[i][now][1]);
			now=fr[i][now];
		}
		for(int i=1;i<=n/2;i++)
		printf("%d %d\n",rec[i][0],rec[i][1]);
	}
	else{
		minx=2147483647;
		for(int i=1;i<=n;i++){
			if(f[n/2][i]+a[i]<minx){
				minx=a[i]+f[n/2][i];
				mini=i;
			}
		}
		printf("%d\n",minx);
		int now=mini;
		for(int i=n/2;i>=1;i--){
			rec[i][0]=min(p[i][now][0],p[i][now][1]);
			rec[i][1]=max(p[i][now][0],p[i][now][1]);
			now=fr[i][now];
		}
		for(int i=1;i<=n/2;i++)
		printf("%d %d\n",rec[i][0],rec[i][1]);
		printf("%d\n",mini);
	}
	return 0;
}
```



---

## 作者：Hisaishi_Kanade (赞：0)

模拟赛二十分钟场切的题，感觉不是很难。

第 $i$ 轮操作可供选择有三人，而只选择两人，所以或许记录第三人就可以解决。考虑设 $f(i,j)$ 表示第 $i$ 轮**操作时**不选的人是 $j$，最小的价值。

这个东西没有后效性。考虑你第 $i$ 轮操作时实际上是对那些人选择？前 $(i-1)$ 轮已经删去了 $2(i-1)$ 个人，而上一轮剩下了一个人，总共 $t=(2(i-1)+1)$ 个人。那么 $f(i,j)$ 从 $f(i,j^\prime)$ 转移即在 $j^\prime,t+1,t+2$ 三人中选，和 $f(i,j^\prime)$ 的转移无关。

对于不选的这个人 $\in\{t+1,t+2\}$ 转移是非常显然的，$p(x,y)=\max(a_x,a_y)$。

+ $f(i,t+1)=\min\{f(i-1,j)+p(j,t+2)\}\mid j\le t$；
+ $f(i,t+2)=\min\{f(i-1,j)+p(j,t+1)\}\mid j\le t$；

否则就是去掉了 $t+1,t+2$。

+ $f(i,j)=\min\{f(i-1,j)+p(t+1,t+2)\}\mid j\le t$。

求方案，则直接记录从哪里转移的即可。

对于 $n$ 为偶数，在结尾加一个 $a=0$ 即可，显然这个点最后一轮不会被选中。

输出时特判一下。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
#define ll long long
int qt, i, j, n, tot, res;
const int N=5005;
int a[N], f[N][N]; short frm[N][N][2];
#define p(x, y) max(a[x], a[y])
inline void print(int id, int dep)
{
	if(dep==0) return ;
	if(frm[dep][id][0]>frm[dep][id][1])
	{
		print(id, dep-1);
		printf("%d %d\n", frm[dep][id][1], frm[dep][id][0]);
	}else
	{
//		printf("%d %d %d\n", id, dep, frm[dep][id][0]);
		print(frm[dep][id][0], dep-1);
		printf("%d %d\n", frm[dep][id][0], frm[dep][id][1]);
	}
}
int main()
{
//	freopen("bank.in", "r", stdin);
//	freopen("bank.out", "w", stdout);
	qt=1; while(qt--)
	{	tot=0; res=2e9;
		scanf("%d", &n); rep(i, 1, n) scanf("%d", a+i); if(n%2!=1) a[++n]=0;
		f[1][1]=p(2, 3); f[1][2]=p(1, 3); f[1][3]=p(1, 2);
//		frm[1][1]={2, 3}; frm[1][2]={1, 3}; frm[1][3]={1, 2};
		frm[1][1][0]=2; frm[1][1][1]=3; frm[1][2][0]=1; frm[1][2][1]=3; frm[1][3][0]=1; frm[1][3][1]=2;
		rep(i, 2, n/2) rep(j, 1, n) f[i][j]=2e9;
		rep(i, 2, n/2)
		{	tot=(i-1)*2+1;
			rep(j, 1, tot)
			{
				if(f[i-1][j]+p(j, tot+2)<f[i][tot+1])
				{
					f[i][tot+1]=f[i-1][j]+p(j, tot+2);
					frm[i][tot+1][0]=j, frm[i][tot+1][1]=tot+2;
				}
				if(f[i-1][j]+p(j, tot+1)<f[i][tot+2])
				{
					f[i][tot+2]=f[i-1][j]+p(j, tot+1);
					frm[i][tot+2][0]=j, frm[i][tot+2][1]=tot+1;
				}
			}
			rep(j, 1, tot) if(f[i][j]>f[i-1][j]+p(tot+1, tot+2)) f[i][j]=f[i-1][j]+p(tot+1, tot+2), frm[i][j][0]=tot+2, frm[i][j][1]=tot+1;
//			rep(j, 1, tot+2) printf("(%d %d %d) ",i, j, f[i][j]); puts("");
		}
		int pos; rep(i, 1, n) {res=min(res, f[n/2][i]+a[i]); if(res==f[n/2][i]+a[i]) pos=i;}
		printf("%d\n", res, pos);
		print(pos, n/2); if(a[pos]) printf("%d\n", pos);
	}
	return 0;
}

```

---

## 作者：lgswdn_SA (赞：0)

观察到第 $i$ 次买单过后，队列中的人的组成一定是 $x$ 和 $[2i+2,n]$，考虑列出 DP 状态 $f(i,j)$ 表示第 $i$ 次买单过后，$x=j$ 的情况。决策即枚举第 $i+1$ 次买单是买了哪两个人的单。第 $i+1$ 次处理的三个人分别为 $j$，$2i$，$2i+1$ （我们有初始时，$x=1$）。

所以可以推得转移

$$
f(i+1,j)\leftarrow f(i,j)+\max(a_{2i+2},a_{2i+3})
$$
$$
f(i+1,2i+2)\leftarrow f(i,j)+\max(a_{2i+3},a_{j})
$$
$$
f(i+1,2i+3)\leftarrow f(i,j)+\max(a_{2i+2},a_{j})
$$

计算答案时，考虑如果 $n$ 是奇数，那么我们在加入一个耗时 $0$ 的人 $a_{n+1}=0$，则有答案为

$$
ans=\min f([\frac{n}{2}],j)+a_j
$$

输出方案就比较烦。我们对于每一个状态都记录一下其决策，然后从 $ans$ 沿记录的决策往回回溯，记录下决策序列，然后反过来输出即可。

$n=1$  要特判。

```cpp
#define rep(i,a,b) for(register int i=(a);i<=(b);i++)
#define per(i,a,b) for(register int i=(a);i>=(b);i--)
using namespace std;
const int N=1009;

inline int read() {
    register int x=0, f=1; register char c=getchar();
    while(c<'0'||c>'9') {if(c=='-') f=-1; c=getchar();}
    while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+c-48,c=getchar();}
    return x*f;
}

int n,a[N],f[N][N],qwq[N][N];

void upd(int x,int y,int i,int j,int val) {
	if(val<f[x][y]) {
		f[x][y]=val;
		qwq[x][y]=j;
	}
}
void print(int i,int j) {
	if(i==0) return;
	print(i-1,qwq[i][j]);
	if(j==2*i) printf("%d %d\n",qwq[i][j],2*i+1);
	else if(j==2*i+1) printf("%d %d\n",qwq[i][j],2*i);
	else printf("%d %d\n",2*i,2*i+1);
}

int main() {
	n=read();
	rep(i,1,n) a[i]=read();
	if(n==1) {
		printf("%d\n%d\n",a[1],1);
		return 0;
	}
	memset(f,0x3f,sizeof(f));
	f[1][1]=max(a[2],a[3]), f[1][2]=max(a[1],a[3]), f[1][3]=max(a[1],a[2]);
	qwq[1][1]=qwq[1][2]=qwq[1][3]=1;
	rep(i,1,n/2) rep(j,1,2*i+1) {
		upd(i+1,j,i,j,f[i][j]+max(a[2*i+2],a[2*i+3]));
		upd(i+1,2*i+2,i,j,f[i][j]+max(a[2*i+3],a[j]));
		upd(i+1,2*i+3,i,j,f[i][j]+max(a[2*i+2],a[j]));
	}
	int ans=0x3f3f3f3f,qwqj=0;
	rep(j,1,n/2*2+1) {
		if(f[n/2][j]+a[j]<=ans) {
			ans=f[n/2][j]+a[j];
			qwqj=j;
		}
	}
	printf("%d\n",ans);
	print(n/2,qwqj);
	if(qwqj<=n) printf("%d\n",qwqj);
	return 0;
}
```

---

## 作者：xxbbkk (赞：0)

# $ CF82D $

### 2020.11.14

## 题意

有一列数，每次从前三个中选两个（不足两个则选一个）其中较大者为代价，接着这两个数出列，求让所有数出列的最小代价。

## 题解

状态不好设

~~讲的人都这么说~~

第$i$轮选数后，总共会选$2×i$个数，所以在第$i$轮选数时，是在（前$i-1$轮选数后剩下的那一个数（第$j$个数）和第$i*2$个数，第$i*2+1$个数）这三个数中选两个，剩一个。

所以设$f_i,_j$为第$i$轮，剩下第$j$个数时的最小代价

有三种状态转移（剩第$j$个数(要枚举的)、剩第$2*i$个数、剩第$（2*i+1）$个数）

式子：

$$f_{i,j}=min(f_{i,j}, \    f_{i-1,j}+max(a_{2*i},a_{2*i+1}))$$

$$f_{i,2*i}=min(f_{i,2*i},   \  f_{i-1,j}+max(a_{j},a_{2*i+1}))$$

$$f_{i,2*i+1}=min(f_{i,2*i+1}, \     f_{i-1,j}+max(a_{j},a_{2*i}))$$


但是还要方案，再来一个结构体$path$记录


$p[i][j].i$和$p[i][j].j$记录第$i$层剩第$j$个时选的那两个数，$p[i][j].k$记录上一层剩的是哪个数，以便递归输出。

## 注意事项

一、初始化$f$为INF，$f_{0,1}=0$


二、$n$++

这里是为了保证最后一轮时不剩下不该剩下的$1$~$n$

保证最后一轮剩下的是原来的$n$+$1$。


## Code
```
#include<bits/stdc++.h>
using namespace std;
struct path{int k,i,j;}p[1010][1010];
int n,ans=1e9,final,a[1010],f[1010][1010];
inline int read(){
	int w=0;
	char ch=getchar();
	while(ch>'9'||ch<'0') ch=getchar();
	while(ch>='0'&&ch<='9'){
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w;
}
inline void output(int px, int py){
	if(px>1) output(px-1,p[px][py].k);
	if(p[px][py].i>n){printf("%d\n", p[px][py].j);return;}
	if(p[px][py].j>n){printf("%d\n", p[px][py].i);return;}
	printf("%d %d\n",p[px][py].i,p[px][py].j);
	return;
}
int main(){
	n=read();
	memset(f,0x3f,sizeof(f)); 
	for(int i=1;i<=n;i++) a[i]=read();
	n++;
	f[0][1]=0;
	for(int i=1;i<=n/2;i++){
		for(int j=1;j<(i<<1);j++){
			if(f[i-1][j]+max(a[i<<1],a[i<<1|1])<f[i][j]){
				f[i][j]=f[i-1][j]+max(a[i<<1],a[i<<1|1]);
				p[i][j]=(path){j,i<<1,i<<1|1};
 			}
			if(f[i-1][j]+max(a[j],a[i<<1])<f[i][i<<1|1]){
				f[i][i<<1|1]=f[i-1][j]+max(a[j],a[i<<1]);
				p[i][i<<1|1]=(path){j,i<<1,j};				
			}
			if(f[i-1][j]+max(a[j],a[i<<1|1])<f[i][i<<1]){
				f[i][i<<1]=f[i-1][j]+max(a[j],a[i<<1|1]);
				p[i][i<<1]=(path){j,i<<1|1,j};
			}
		}
	}
	printf("%d\n",f[n/2][n]);
	output(n/2,n);
	return 0;
}

```



---

