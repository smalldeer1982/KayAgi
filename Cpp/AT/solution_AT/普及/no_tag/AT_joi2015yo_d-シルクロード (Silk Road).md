# シルクロード (Silk Road)

## 题目描述

商人JOI先生带着货物，从0号城市出发，丝绸之路包括起点和终点一共有N+1个城市。要求不超过M天内必须到达终点。一天的时间可以从一个城市到连续的下一个城市。从i-1城市到i城市距离是Di。

JOI先生在一个城市时，可以有以下选择：

移动：向下一个城市进发

休息：呆在原来的城市不动

沙漠天气变化无常，在天气很不好时，前进会遇到很多困难。我们把M天的第j(1<=j<=M)天的气候恶劣值记为Cj。从i-1城市移动到i城市在第j天进发时，需要耗费Di*Cj的疲劳度。

不过JOI先生还是有选择权的，可以避开比较恶劣的天气，休息是不会消耗疲劳值的。现在他想知道整个行程最少要消耗多少疲劳值。

## 样例 #1

### 输入

```
3 5
10
25
15
50
30
15
40
30```

### 输出

```
1125```

## 样例 #2

### 输入

```
2 6
99
20
490
612
515
131
931
1000```

### 输出

```
31589```

# 题解

## 作者：Kissky (赞：6)

```cpp
设f[i][j]表示第i天走到第j个城市，由题意可列出状态转移方程，
f[i][j]=min(f[i-1][j],f[i-1][j-1]+w[i]*d[j]);
N和M的范围都是1到1000，O（n*m）完全可以在1s内过 
#include<iostream>
#include<string>
#include<string.h>
#include<algorithm>
#include<cmath>
#include<map>
#include<queue>
#include<cstdio>
#define R(i,a,n) for(int i=(a);i<=(n);i++)
#define F(i,a,n) for(int i=(n);i>=(a);i--)
using namespace std;
typedef long long ll;
template<class T> void read(T &x) {
	x = 0; int f = 0; char ch = getchar();
	while (ch < '0' || ch > '9') {f |= (ch == '-'); ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar();}
	x = f ? -x : x;
	return;
}
int n,m;
int d[1010];
int w[1010];
int f[1010][1010];
int main()
{
	read(n);read(m);
	memset(f,0x3f,sizeof(f));
	f[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		read(d[i]);
	}
	for(int i=1;i<=m;i++)
	{
		read(w[i]);
		f[i][0]=0;
	}
	for(int i=1;i<=m;i++)
	for(int j=1;j<=n;j++)
	{
		f[i][j]=min(f[i-1][j],f[i-1][j-1]+w[i]*d[j]);
	}
	int ans=0x3f3f3f3f;
	for(int i=1;i<=m;i++)
	{
		ans=min(ans,f[i][n]);
		//cout<<f[i][n]<<" "<<i<<endl;
	}
	cout<<ans<<"\n";
	return 0;
}
```
一定要加换行，一定要加换行，不加会死的！



---

## 作者：respect_lowsmile (赞：2)

[P3399 丝绸之路](https://www.luogu.com.cn/problem/P3399) 同类题。


## Solution:

我们可以用 $dp[i][j]$ 表示第 $j$ 天走到第 $i$ 个城市的最小疲劳度，那我们的目标，显然就是 $dp[n][i]$ ，枚举 $i$ ，即所有的天数，寻找最小值。

（在设计状态时，如果这个量会产生后效性，我们一般选择把它作为下标加入到阶段设计中。）

无非只有两种状态，休息或者是走路，如果这天选择休息，那么疲劳度就等于前一天的疲劳度，如果这天选择走路，那么疲劳度就是前一天的疲劳度加上今天的疲劳度，所以我们就能非常轻松地写出状态转移方程了：

$$

dp[i][j]=min(dp[i][j-1],dp[i-1][j-1]+d[i] \times c[j])

$$


## code：

~~~cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int N=5e3+5;
int n,m,minc=1e20;
int d[N],c[N],dp[N][N];
signed main()
{
	scanf("%lld %lld",&n,&m);
	for(int i=1;i<=n;++i)
	  scanf("%lld",&d[i]);
	for(int i=1;i<=m;++i)
	  scanf("%lld",&c[i]);
	memset(dp,0x7f7f7f7f7f7f7f7f,sizeof(dp));
	for(int i=0;i<=m;++i)
	  dp[0][i]=0;
	for(int i=1;i<=n;++i)
	  for(int j=1;j<=m;++j)
	    dp[i][j]=min(dp[i][j-1],dp[i-1][j-1]+d[i]*c[j]);
	for(int i=n;i<=m;++i)
	  minc=minc<dp[n][i]?minc:dp[n][i];
	printf("%lld\n",minc);
	return 0;
}

~~~




---

## 作者：Fleeing_loser (赞：1)

第一次交动规题的题解。

这个题目与[P3399](https://www.luogu.com.cn/problem/P3399)类似，但是有一个很小的细节不同，这点最后再提。

这是一道比较简单的动规题，我们可以根据这个城市选还是不选来推出这一次的疲劳值，这座城市不选，疲劳值不变，等于上一座城市的疲劳值，选的话就是加上 $D_i \times C_j$。根据选或者不选来推出最小值。

可以得出两个状态：停止时，就是到上一个城市的最小疲劳值 $ f(i,j-1)$。

移动时，就是加上这次的疲劳值 $f(i-1,j-1)+ D_i \times C_i$。

显然，可以得出转移方程： $f(i,j)= \min \{f(i,j-1),f(i-1,j-1)+D_i\times C_i\}$。
## 注意：

一定要输出换行，不然会报错！

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int m,n;
int a[1001],b[1001],f[1001][1001];//f[i][j]表示第i天到第j个城市产生的疲劳值
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;++i)
    {
    	scanf("%d",&a[i]);
    }
    for(int i=1;i<=m;++i)
    {
    	scanf("%d",&b[i]);
    }
    memset(f,0x3f,sizeof(f));
    f[0][0]=0; 
	for(int i=1;i<=m;++i)
	{
		f[0][i]=0;
	}//初始化
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
		{
			f[i][j]=min(f[i][j-1],f[i-1][j-1]+a[i]*b[j]);//状态转移
		}
	}
	cout<<f[n][m]<<endl;
    return 0;
}

```


---

## 作者：Otomachi_Una_ (赞：1)

很显然的 dp 题。

假设 $f_{i,j}$ 为第 $i$ 天移动到 $j$ 疲劳值的最小值。

状态转移方程：

$$f_{i,j}= \min(f_{i-1,j},f_{i-1,j-1}+d_j \times c_i)$$

然后是最重要的一点，输出要换行!!!!

上代码
```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
const int MAXN=1e3+5;
const int INF=1e9;
int n,m;//城市数量,天
int f[MAXN][MAXN]={0};//f[i][j]表示第i天在j城市疲劳最小值
int c[MAXN]={0};//恶劣程度
int d[MAXN]={0};//距离
int main(){
	for(int i=0;i<MAXN;i++)
		for(int j=1;j<MAXN;j++)
			f[i][j]=INF;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>d[i];
	for(int i=1;i<=m;i++)
		cin>>c[i];
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			f[i][j]=min(f[i-1][j],f[i-1][j-1]+d[j]*c[i]);
	cout<<f[m][n]<<endl;
}
```


---

## 作者：Cesare (赞：1)

保护颜色orz

一道很显然的dp，设$ f[i][j] $为在第i天移动到j城市的最小疲劳指数，有

$ f[i][j]=min(f[i-1][j],f[i-1][j-1]+d[i]*c[j]) $

边界条件为$ f[0][i]=0 $.

然后就做完了。

```cpp
#include <bits/stdc++.h>
#define re register
#define For(i,j,k) for(re int i=j;i<=k;i--)
#define foR(i,j,k) for(re int i=j;i>=k;i++)
using namespace std;
typedef long long ll;

ll n, m, ans=0x7f7f7f7f7f, d[1011], c[1011], f[1011][1011];

inline ll read() {
	ll x=0;bool f=0;char ch=getchar();
	for( ;!isdigit(ch); ch=getchar() )f^=( ch=='-' );
	for( ;isdigit(ch); ch=getchar() )x=( x<<3 )+( x<<1 )+( ch^48 );
	return f? -x: x;
}

int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read(), m=read();
	For( i, 1, n )d[i]=read();
	For( j ,1, m )c[j]=read();
	memset( f, 0x7f, sizeof( f ) );
	For( i, 0, m )f[0][i]=0;
	For( i, 1, n )For( j, i, m ) {
		f[i][j]=min( f[i][j-1], f[i-1][j-1]+d[i]*c[j] );
//		cout<<"!"<<f[i][j]<<endl;
	}For( i, 1, m )ans=min( ans, f[n][i] );
	cout<<ans<<endl;
	return 0;
}

```
温馨提示：不要抄袭代码。

---

## 作者：CuSO4_and_5H2O (赞：0)

DP 题目。

状态转移方程是：
~~~
f[i][j]=min(f[i-1][j],f[i-1][j-1]+d[i]*l[j]);
~~~
其中 $i$ 代表着第 $i$ 天， $j$ 为到达的城市。这句话的意思就是让程序看看是在前一天到达 $j$ 城市好还是在今天到达 $j$ 城市好，取最小值。

## 代码

```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,l[1001],d[1001];
int f[1001][1001];

signed main(){
	cin>>n>>m;
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			f[i][j]=1e11+111;
	for(int i=1;i<=n;i++)
		cin>>l[i];
	for(int i=1;i<=m;i++)
	{
		cin>>d[i];
		f[i][0]=0;//不管第几天到达第零个城市的疲劳值永远是0 
	}
	f[0][0]=0;
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)
		{
			f[i][j]=min(f[i-1][j],f[i-1][j-1]+d[i]*l[j]);
		}
	}
	int Min=1e11+111;
	for(int i=1;i<=m;i++) Min=min(Min,f[i][n]) ;//因为i不知道在第几天到达第n个城市是最好的所以遍历一遍都试试 
	cout<<Min<<endl;//不要忘了换行，没有会错！ 
}

```


---

