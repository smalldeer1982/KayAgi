# Basketball Exercise

## 题目描述

Finally, a basketball court has been opened in SIS, so Demid has decided to hold a basketball exercise session. $ 2 \cdot n $ students have come to Demid's exercise session, and he lined up them into two rows of the same size (there are exactly $ n $ people in each row). Students are numbered from $ 1 $ to $ n $ in each row in order from left to right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195C/05855164ffa55108436f13cfefdb8a460d04c2d7.png)Now Demid wants to choose a team to play basketball. He will choose players from left to right, and the index of each chosen player (excluding the first one) will be strictly greater than the index of the previously chosen player. To avoid giving preference to one of the rows, Demid chooses students in such a way that no consecutive chosen students belong to the same row. The first student can be chosen among all $ 2n $ students (there are no additional constraints), and a team can consist of any number of students.

Demid thinks, that in order to compose a perfect team, he should choose students in such a way, that the total height of all chosen students is maximum possible. Help Demid to find the maximum possible total height of players in a team he can choose.

## 说明/提示

In the first example Demid can choose the following team as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195C/9a3e2230ef98dd0879303ff329fc9cb7b1cf5209.png)In the second example Demid can choose the following team as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1195C/c3c20000e8e493da34f3e2b1ef145d407e671b29.png)

## 样例 #1

### 输入

```
5
9 3 5 7 3
5 8 1 4 5
```

### 输出

```
29
```

## 样例 #2

### 输入

```
3
1 2 9
10 1 1
```

### 输出

```
19
```

## 样例 #3

### 输入

```
1
7
4
```

### 输出

```
7
```

# 题解

## 作者：tth37 (赞：13)

很水的一道C题……目测难度在黄~绿左右。请各位切题者合理评分。

注意到可以选择的球员编号是严格递增的，因此可以把状态的第一维定义为球员编号，第二维描述编号同为 $i$ 的两名球员的选取情况。

定义状态：$f[i][0/1/2]$ 表示选取了编号在 $i$ 及以前的球员，所能得到的身高总和最大值。其中，第二维的 $0$ 表示编号为 $i$ 的球员一个都不选；$1$ 表示只选上面一个；$i$ 表示只选下面一个。（显然没有上下都选的情况）

状态转移方程：
$$
f[i][0]=max\lbrace f[i-1][0],f[i-1][1],f[i-1][2]\rbrace
$$
$$
f[i][1]=max\lbrace f[i-1][0],f[i-1][2]\rbrace+height[i][1]
$$
$$
f[i][2]=max\lbrace f[i-1][0],f[i-1][1]\rbrace+height[i][2]
$$

**Update: 用贪心可以证明，在最优解中，不会出现连续两列一个不取的情况。因此， $f[i][0]$ 其实没有必要考虑来自 $f[i-1][0]$ 的状态转移。**

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int N;
ll h[100005][3];
ll f[100005][3];
int main() {
	cin >> N;
    for (register int i = 1; i <= N; ++i) cin >> h[i][1];
    for (register int i = 1; i <= N; ++i) cin >> h[i][2];
    f[1][0] = 0;
    f[1][1] = h[1][1];
    f[1][2] = h[1][2];
    for (register int i = 2; i <= N; ++i) {
        f[i][0] = max(f[i - 1][0], max(f[i - 1][1], f[i - 1][2]));
        f[i][1] = max(f[i - 1][0], f[i - 1][2]) + h[i][1];
        f[i][2] = max(f[i - 1][0], f[i - 1][1]) + h[i][2];
    }
    cout << max(f[N][0], max(f[N][1], f[N][2]));
    return 0;
}
```

---

## 作者：AC_Dolphin (赞：8)

另一种设计dp的方法

令$dp[i][j]$表示到第$i$行、第$j$列最大的高度和，则不难得到转移方程$ dp[i][1]=max_{j<i}(dp[j][2])+a[i]$,$dp[i][2]=max_{j<i}(dp[j][1])+b[i]$
但是这样的的dp是$O(n^2)$的，肯定会超时。

我们优化的突破口就是$max_{j<i}(dp[j][1/2])$这个地方，因为每次我们都需要$O(n)$的时间查找这个最大值，所以我们考虑在每一次计算$dp[i][1/2]$的时候就记下最大值。

令$cnt1$、$cnt2$表示当前$dp[i][1]$、$dp[i][2]$的最大值，则$dp[i][1]=cnt2+a[i]$，$dp[i][2]=cnt1+b[i]$，计算完后更新$cnt1$和$cnt2$，最后$ans=max(dp[n][1],dp[n][2])$。

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(register int (i)(1);(i)<=(n);++(i))
#define int long long
int n,a[100005],b[100005];
int dp[100005][5],cnt1,cnt2;
typedef long long ll;
inline int read(){
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int lowbit(int x){
	return x&(-x);
}
signed main(){
	n=read();
	rep(i,n) a[i]=read();
	rep(i,n) b[i]=read();
	dp[1][1]=a[1],dp[1][2]=b[1];
	cnt1=a[1],cnt2=b[1];
	for(int i=2;i<=n;i++) {dp[i][1]=cnt2+a[i];dp[i][2]=cnt1+b[i];cnt1=max(cnt1,dp[i][1]);cnt2=max(cnt2,dp[i][2]);}
	//for(int i=2;i<=n;i++) {dp[i][2]=cnt1+b[i];cout<<dp[i][2]<<" ";}
	//cout<<"t"<<endl;
	cout<<max(dp[n][1],dp[n][2]);
	return 0;
}

```

---

## 作者：两年打铁 (赞：3)

最难的是看懂题面，英文不好一直看错直接自闭。
# 题意
有两行n个人，从左往右选，每一列只能选一个或者全不选，并且选出来的序列左右两个不在同一行，求可以选的最大的和。

我们用$f[i][0/1/2]$ 来表示第i列，选第一行，选第二行和两行都不选，转移就直接按照题意转移就可以了



```cpp
#include<bits/stdc++.h>
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define int long long  
using namespace std;
 
inline void read(int &x)
{
    x=0;char ch=getchar();int pd=1;
    while(ch<'0'||ch>'9'){if(ch=='-')pd=-pd;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    x*=pd;
}
inline void write(const int &x)
{
    char ggg[10001];int s=0;int tmp=x;
    if(tmp==0){putchar('0');return;}
    if(tmp<0){tmp=-tmp;putchar('-');}
    while(tmp>0){ggg[s++]=tmp%10+'0';tmp/=10;}
    while(s>0){putchar(ggg[--s]);}
}
 
int n,a[100010][3],f[300010][4];
int cnt,b[300010];
int len;
signed main()
{
    read(n);
    for(register int i=1;i<=n;++i)
    {
        read(a[i][0]);
    }
    for(register int i=1;i<=n;++i)
    {
        read(a[i][1]);
    }
    for(register int i=1;i<=n;++i)
    {
        f[i][0]=max(f[i-1][1],f[i-1][2])+a[i][0];
        f[i][1]=max(f[i-1][0],f[i-1][2])+a[i][1];
        f[i][2]=max(f[i-1][0],max(f[i-1][1],f[i-1][2]));
    }
    write(max(f[n][0],max(f[n][1],f[n][2])));
    return 0;
} 

---

## 作者：woshishei (赞：2)

## DP

用$dp[k][i]$表示考虑到第$k$行，第$i$列的身高之和的最大值。

不难发现当前位置身高之和的最大值为**另一行的所有 _下标小于当前位置下标的_ 位置的身高之和的最大值**和**当前位置的身高**之和。

于是可以列出转移方程：

$dp[1][i]=max\{dp[2][1],dp[2][2],...,dp[2][i-1]\}+h_{1,i}$

$dp[2][i]=max\{dp[1][1],dp[1][2],...,dp[1][i-1]\}+h_{2,i}$

但是这样的时间复杂度为$O(n^2)$，会T。

用两个$max$变量储存第一、二行$dp[k][1]$到$dp[k][i-1]$的最大值即可优化至$O(n)$。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
int n,h1[100010],h2[100010];
ll dp[3][100010],mx1=0,mx2=0;//储存最大值的两个max变量，强迫症使我浪费了100000个变量的空间= =
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&h1[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&h2[i]);
	for(int i=1;i<=n;i++)
	{
		dp[1][i]=mx2+h1[i];//第二行的最大值加上这个人的身高
		dp[2][i]=mx1+h2[i];//第一行的最大值加上这个人的身高
		mx1=max(mx1,dp[1][i]);
		mx2=max(mx2,dp[2][i]);//更新max变量
	}
	printf("%I64d",max(dp[1][n],dp[2][n]));//最后结果即dp[1][n]和dp[2][n]的最大值
	return 0;
}
```

---

## 作者：gesong (赞：1)

题目传送门：[CF1195C](https://www.luogu.com.cn/problem/CF1195C)。
# 思路
这道一看就是 **dp**。

**状态表示**：

$f_{i,0}$ 表示第 $i$ 列不选的最大价值，$f_{i,1}$ 表示第 $i$ 列选择第一行的最大数，$f_{i,2}$ 表示第 $i$ 列选择第二行的最大数，$a_i$ 表示第一行第 $i$ 列的数，$b_i$ 表示第二行第 $i$ 列的数。

**方程初始化**：

$f_{1,0}=0$ 不选就是 $0$。

$f_{1,1}=a_1$ 选择第一行就是第一行的值 $a_1$。

$f_{1,2}=b_1$ 选择第二行就是第二行的值 $b_1$。

**状态转移**：

$f_{i,0}$

由于这一列都没有选择，所以它的方程就是前一列选择第一行，选择第二行，不选的最大值。

所以方程为：$f_{i,0}=\max(f_{i-1,0},f_{i-1,1},f_{i-1,2})$。

$f_{i,1}$

由于这一列的第一行被选择，根据题意得知只能选择前一列选择第二行，不选的最大值即 $\max(f_{i-1,0},f_{i-1,2})$，然后再加上当前数的值即 $a_i$。

所以方程为：$f_{i,1}=\max(f_{i-1,0},f_{i-1,2})+a_i$。

$f_{i,2}$

由于这一列的第二行被选择，根据题意得知只能选择前一列选择第一行，不选的最大值即 $\max(f_{i-1,0},f_{i-1,1})$，然后再加上当前数的值即 $b_i$。

所以方程为：$f_{i,2}=\max(f_{i-1,0},f_{i-1,1})+b_i$。

最后的答案就是三者的最大值即：$\max(f_{n,0},f_{n,1},f_{n,2})$。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100001],b[100001],f[1000001][3]; 
main(){
	int n;
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++) cin>>b[i];
	f[1][1]=a[1];//方程初始化
	f[1][2]=b[1];
	for (int i=2;i<=n;i++){//方程转移
		f[i][0]=max(max(f[i-1][0],f[i-1][1]),f[i-1][2]);
		f[i][1]=max(f[i-1][0],f[i-1][2])+a[i];
		f[i][2]=max(f[i-1][0],f[i-1][1])+b[i];
	} 
	cout <<max(max(f[n][0],f[n][1]),f[n][2]);//输出结果
    return 0;
}

```

---

## 作者：米奇奇米 (赞：1)

## 题解- CF1195C Basketball Exercise

### $1.1$题目意思
有两行$n$个人，从左往右选，每一列只能选一个或者全不选，并且选出来的序列左右两个不在同一行，求可以选的最大的和是多少。

### $2.1$算法思路
简单$dp$运用啊。

我们设立**状态：** $f[i][0/1]$表示第$i$个选上面还是下面

对于$dp$**转移：**
$f[i][0]=max(f[i-1][0],f[i-1][1]+a[i][0])$

$f[i][0]$显然如果$i-1$选了下面,那么这次只能选上面

$f[i-1][0]$就是上次选的就是上面，这次就不能选上面。

$f[i][1]$与$f[i][0]$同理的


---

## 作者：小黑AWM (赞：1)

简单的线性的DP，一眼看出状态后很容易可以写掉，但是题意可能会有导向性错误导致想到 $O(n^2)$ 的算法。

约定：记 $h(x,y)$ 为第 $x$ 列，第 $y$ 行的人的身高。

第 $i$ 列我们考虑有三种状态：选第一个，选第二个，不选。由于题意限制，我们需要考虑是否连续两个选的在同一行。

不难发现除了当前这列和之前这列我们需要考虑，更前面的状态都已经没有用了，那么这满足了无后效性的要求。

我们给出最大的子方案一定能使的总方案最大，所以也满足最优子结构的性质。

根据之前的考虑设计状态 $f(i,\space k)$ 表示选到第 $i$ 列，每列选了第 $k$ 行的人时的最大身高和，当 $k=0$ 时表示这列不选。

由状态直接得到状态转移方程，不需要优化可以直接线性DP。

$$f(i ,k) = max\{f(i-1,j)+h(i,k)\},j\in \{0,1,2\}$$

且 $j$ 和 $k$ 应满足 $j \not = k$ 或 $j=k=0$

那么最终答案就是 $max\{f(n,0),f(n,1),f(n,2)\}$ 实现并没有难度。

```cpp
/*
 * Author: xiaohei_AWM
 * Date: 7.17
 * Mutto: Face to the weakness, expect for the strength.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
#define reg register
#define endfile fclose(stdin);fclose(stdout);
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
namespace IO{
    char buf[1<<15],*S,*T;
    inline char gc(){
        if (S==T){
            T=(S=buf)+fread(buf,1,1<<15,stdin);
            if (S==T)return EOF;
        }
        return *S++;
    }
    inline int read(){
        reg int x;reg bool f;reg char c;
        for(f=0;(c=gc())<'0'||c>'9';f=c=='-');
        for(x=c^'0';(c=gc())>='0'&&c<='9';x=(x<<3)+(x<<1)+(c^'0'));
        return f?-x:x;
    }
    inline ll readll(){
        reg ll x;reg bool f;reg char c;
        for(f=0;(c=gc())<'0'||c>'9';f=c=='-');
        for(x=c^'0';(c=gc())>='0'&&c<='9';x=(x<<3)+(x<<1)+(c^'0'));
        return f?-x:x;
    }
}
using namespace IO;
const int maxn = 1e5 + 10;
int n;//f[i][j]表示选到第i个人，那人是j状态的最大答案
ll  h[3][maxn], f[maxn][3];
int main(){
    n = read();
    for(int i = 1; i <= n; i++) h[1][i] = read();
    for(int i = 1; i <= n; i++) h[2][i] = read();
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= 2; j++){
            for(int k = 0; k <= 2; k++){
                if(j == k && j != 0) continue;
                f[i][j] = max(f[i][j], f[i-1][k] + h[j][i]);
            }
        }
    }
    cout << max(f[n][0], max(f[n][1], f[n][2])) << endl;
    return 0;
}

```


---

## 作者：Lily_White (赞：1)

一道很不错的DP题。

决策是每一步选择在这一列选还是不选（如果不选可能在后面遇到更好的解）。

例如：
```
100 1  1
1   1  100
```
最优解应当跳过第二列，为$200$。

因此：

我们用数组$a[MAXN][2]$来存储输入。

定义$f[i][j]$为**决策到第$i$列，当前位置在第$j$行$(j = 0,1)$的最优解。**

$f[i+1,j]=\max(f[i,j], f[i,!j]+a[i,j])$

初始状态：$f[1][j]=a[1][j]$。

Code：
```cpp
    #include <bits/stdc++.h>
    using namespace std;
    const int MAXN = 100010;
    int a[MAXN][2];
    long long f[MAXN][2];
    int main()
    {
    	int n;
    	cin >> n;
    	for (int i = 1; i <= n; i++)cin >> a[i][0];
    	for (int j = 1; j <= n; j++)cin >> a[j][1];
    	long long ans = 0;
    	f[1][0] = a[1][0], f[1][1] = a[1][1];
    	for (int i = 1; i <= n - 1; i++)
    	{
    		f[i + 1][0] = max(f[i][0], f[i][1] + a[i + 1][0]);
    		f[i + 1][1] = max(f[i][1], f[i][0] + a[i + 1][1]);
    	}
    	cout << max(f[n][0], f[n][1]) << endl;
    	return 0;
    }
     
```

---

## 作者：FstAutoMaton (赞：0)

一道DP题

首先考虑DFS，每一列可以分为3种状态。（ 0表示不选，1表示选第一行，2表示选第二行 ）那么DFS的转移方程为:
```
for( int i = 0; i < 3; i ++ )
{
   if( i == pre && i && pre && step != 1 ) continue;
   dfs( step + 1, i, sum + a[step][i] );                   
}                  
```
其中```step```为当前行数，```pre```为前一次的选择，```
sum```为当前的和，```a[step][i]```为本次选择的位置。由此可得如下DFS函数：
```
void dfs( int step, int pre, int sum )
{
	if( step > n )
	{
		ans = max( ans, sum );
		return ;
	}
	for( int i = 0; i < 3; i ++ )
	{
    	if( i == pre && i && pre && step != 1 ) continue;
		dfs( step + 1, i, sum + a[step][i] );
	}
}
```
可以用前缀和减枝，整体如下：
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, a[100005][3], ans, back[100005];
void dfs( int step, int pre, int sum )
{
	if( sum + back[n] - back[step - 1] <= ans ) return ;
	if( step > n )
	{
		ans = max( ans, sum );
		return ;
	}
	for( int i = 0; i < 3; i ++ )
	{
		if( i == pre && i && pre && step != 1 ) continue;
		dfs( step + 1, i, sum + a[step][i] );
	}
}
signed main()
{
	cin >> n;
	for( int i = 1; i <= n; i ++ )
		cin >> a[i][1];
	for( int i = 1; i <= n; i ++ )
		cin >> a[i][2];
	for( int i = 1; i <= n; i ++ )
		back[i] = back[i - 1] + max( a[i][1], a[i][2] );
	dfs( 1, 0, 0 );
	cout << ans;
}
```
然后就TLE了~~其实是UKE了~~。

但我们可以将DFS进行变形，得到如下DP代码：
```
dp[1][1] = a[1][1];
dp[1][2] = a[1][2];
for( int i = 2; i <= n; i ++ )
{
	dp[i + 1][0] = max( dp[i][0], max( dp[i][1], dp[i][2] ) );
	dp[i + 1][1] = max( dp[i][0], dp[i][2] ) + a[i][1];
	dp[i + 1][2] = max( dp[i][0], dp[i][1] ) + a[i][2];
}
```
但这样最终答案会被存在```dp[n + 1]```里，所以可以把DP的 **扩散性** 变为 **收集性**。AC代码如下：
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, dp[100005][3], a[100005][3], ans;
signed main()
{
    cin >> n;
    for( int i = 1; i <= n; i ++ ) cin >> a[i][1];
    for( int i = 1; i <= n; i ++ ) cin >> a[i][2];
	dp[1][1] = a[1][1];
	dp[1][2] = a[1][2];
	for( int i = 2; i <= n; i ++ )
	{
		dp[i][0] = max( dp[i - 1][0], max( dp[i - 1][1], dp[i - 1][2] ) );
		dp[i][1] = max( dp[i - 1][0], dp[i - 1][2] ) + a[i][1];
		dp[i][2] = max( dp[i - 1][0], dp[i - 1][1] ) + a[i][2];
	}
    cout << max( dp[n][0], max( dp[n][1], dp[n][2] ) );
}
```
~~求通过。~~

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1195C)    
一道超水黄题，并且还是一道 dp 水题。   
我们观察图片，不难发现，对于 $h$ 的每一列，都有三种状态：选上面的、选下面的和不选。   
我们可以用 $dp_{i,j}$ 来表示第 $i$ 列的第 $j$ 种情况的**最优解**（$j$ 为 $0$ 表示不选，$j$ 为 $1$ 表示选上面的，$j$ 为 $2$ 表示选下面的）：    
如果 $j=0$，这时候的转移方程是 $dp_{i,j}=\operatorname{max}(dp_{i-1,0},dp_{i-1,1},dp_{i-1,2})$。    
如果 $j=1$，这时候的转移方程是 $dp_{i,j}=\operatorname{max}(dp_{i-1,0},dp_{i-1,2})+h_{i,1}$，**注意这种情况不能选下面的，要加上本身**。    
如果 $j=2$，这时候的转移方程是 $dp_{i,j}=\operatorname{max}(dp_{i-1,0},dp_{i-1,1})+h_{i,2}$，**注意这种情况不能选上面的，要加上本身**。    
CODE：
```cpp
#include <iostream>
using namespace std;
#define int long long
inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
	{
		write(x/10);
	}
	putchar(x%10+'0');
}
inline int read()
{
	int x=0;
	bool f=false;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			f=true;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	if(f)
		return -x;
    return x;
}
inline int max(int a,int b){
	return a>b?a:b;
}
int n,a[2][114514],dp[114514][3];
signed main(void){
	n=read();
	for(int i=0;i<2;++i){
		for(int j=1;j<=n;++j){
			a[i][j]=read();
		}
	}
	for(int i=1;i<=n;++i){
		dp[i][0]=max(max(dp[i-1][0],dp[i-1][1]),dp[i-1][2]);//不选 
		dp[i][1]=max(dp[i-1][2],dp[i-1][0])+a[0][i];//选下面的
		dp[i][2]=max(dp[i-1][1],dp[i-1][0])+a[1][i];//选上面的 
	}
	write(max(max(dp[n][0],dp[n][1]),dp[n][2]));//最后输出最大值
}
```


---

## 作者：寒鸽儿 (赞：0)

本题解同步发表于:  
[作者的个人博客](https://froldh.github.io/2019/07/22/codeforcesPlan/CF1195/)  [luogu博客](https://www.luogu.org/blog/oldherd/solution-CF1195C)  
我们必须知道当前的列和当前搜索的情况。可以用(x, 0|1, 0|1)来表示。  
考虑进一步优化:由于状态很简单，不妨记录，用记忆化搜索或者动态规划来求解。  
注意边界情况即可。  
```cpp
#include <cstdio>

using namespace std;

const int maxn = 100010;
int h[2][maxn];
long long f[maxn][2][2];

inline long long max(long long x, long long y) {
	return x > y ? x : y;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &h[0][i]);
	for(int i = 1; i <= n; i++) scanf("%d", &h[1][i]);
	f[1][0][0] = 0; f[1][1][0] = h[0][0]; f[1][0][1] = h[1][1];
	for(int i = 1; i <= n; i++) {
		f[i][1][0] = max(f[i-1][0][1], f[i-1][0][0]) + h[0][i];
		f[i][0][1] = max(f[i-1][1][0], f[i-1][0][0]) + h[1][i];
		f[i][0][0] = max(max(f[i-1][0][1], f[i-1][1][0]), f[i-1][0][0]);
	}
	printf("%lld\n", max(max(f[n][0][0], f[n][0][1]), f[n][1][0]));
	return 0;
}
```

---

## 作者：Konnyaku_ljc (赞：0)

虽然一眼看出了DP为正解，但是先傻乎乎的打了个 O(n^2)……  
at first，我想每次都更新一遍，绝对无后效性！更新顺序从左到右  
核心代码如下
``` cpp
dp[1][1]=a[1][1];
dp[2][1]=a[2][1];
for(int i=1;i<=n-1;i++)
{
    for(int j=i+1;j<=n;j++)
    {
        dp[1][j]=max(dp[1][j],dp[2][i]+a[1][j]);
        dp[2][j]=max(dp[2][j],dp[1][i]+a[2][j]);
    }
}
cout<<max(dp[1][n],dp[2][n]);
```
第五个点就虚了，O(n^2)就是不行！  

但可以想象一下dp[1(2)][x]>dp[2(1)][x-1]，dp[i][x]>dp[i][x-2];所以，可变为O(n)的动态转移方程——  
### dp[1][i]=max(dp[2][i-1]+a[1][i],dp[2][i-2]+a[1][i])  
### dp[2][i]=max(dp[1][i-1]+a[2][i],dp[1][i-2]+a[2][i])  
附AC代码——
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n;
long long a[3][100005],dp[3][100005];
//开到3，不然就越位了（不要问我怎么知道的……）
//不开long long 应该会见祖宗吧，没敢试
int main()
{
    cin>>n;//输入
    for(int i=1;i<=n;i++) cin>>a[1][i];
    for(int i=1;i<=n;i++) cin>>a[2][i];
    dp[1][1]=a[1][1];
    dp[2][1]=a[2][1];
    dp[1][2]=a[2][1]+a[1][2];
    dp[2][2]=a[1][1]+a[2][2];
    //先将第一列、第二列更新，不然无法进行后面
    //动态转移方程——
    for(int i=3;i<=n;i++)
    {
        dp[1][i]=max(dp[2][i-1]+a[1][i],dp[2][i-2]+a[1][i]);
        dp[2][i]=max(dp[1][i-1]+a[2][i],dp[1][i-2]+a[2][i]);
    }
    cout<<max(dp[1][n],dp[2][n]);//取最大的输出
    return 0;
}
```                                      
#### AC!
~~这是第三次尝试，虽然还不知道到底哪里排版不齐……~~

---

## 作者：momo5440 (赞：0)

很明显这是一道dp题，而当扫到i这列时，第i列的决定受上一列的决定影响所以要记录上一列的选择（这里是选与不选），我是设两个dp数组，一个是dp1[2][n]另一个是dp2[2][n]，dp1,dp2分别对应上面一排和下面一排。dp1[0][i]表示的是到i1（上面那排的i）这个人不选这个人的最大高度，dp1[1][i]表示的是选i1这个人所能达到的最大值，dp2的设定同理。

下面便该考虑转移方程了，我们以dp1举例，当遍历到i时dp1[0][i]有很多选择，上一列不管选不选，不管是上是下都可以过继过来所以

**dp1[0][i]=max(dp1[0][i-1],dp1[1][i-1],dp2[1][i-1],dp2[0][i-1])**

而相对来说dp1[1][i]能选的相对就少了，同一排上一个被选了这个就不能选了，但除此之外全能选所以

**dp1[1][i]=max(dp2[1][i-1],dp1[0][i-1],dp2[0][i-1])+a1[i]**

dp2大概也差不多

上代码，保证安全无毒

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int maxn=100005;
ll n,tp,sum,su1,a1[maxn],a2[maxn];
ll dp1[2][maxn],dp2[2][maxn];
int maxm(int a,int b){
	if (a>b) return a;
	else return b;
}
int main(){
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>a1[i];
	}
	for (int i=1;i<=n;i++){
		cin>>a2[i];
	}
	ll ans=0;
	for (int i=1;i<=n;i++){
		dp1[0][i]=dp2[0][i]=max(dp1[0][i-1],max(dp1[1][i-1],max(dp2[1][i-1],dp2[0][i-1])));
		dp1[1][i]=max(dp2[1][i-1],max(dp1[0][i-1],dp2[0][i-1]))+a1[i];
		dp2[1][i]=max(dp1[1][i-1],max(dp1[0][i-1],dp2[0][i-1]))+a2[i];
		ans=max(dp1[0][i],max(dp1[1][i],max(dp2[1][i],dp2[0][i])));
	}
	cout<<ans<<endl;
	return 0;
}

```

还有个小小优化，由于每个dp都只由上一个dp得出所以你并不需要两个数组来记录，用八个变量就行了（四个记录上一个，四个记录这次的）。

---

## 作者：灵光一闪 (赞：0)

A的第一道DP题呢！感觉棒棒哒（希望管理也棒棒哒

首先，我不知道啥叫动态转移方程，也不知道啥是DP，只是按照一个贪心（感觉是的）的思路去写的

没翻题解区，即使有雷同也希望给过qaq（毕竟第一道DP题

打``*``号的地方是怎么来的呢？

是由``#``号来的，这两个是**最直接的**

而打``@``号的是经过若干点来的，不算在内

Tip：以上有一个条件：不相邻&&最优解

|  | @ | @ |  | * |
| -----------: | -----------: | -----------: | -----------: | -----------: |
|  | @ | # | # |  |



代码：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

using namespace std;
long long a[2][233333];
long long dp[2][233333];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[0][i];
    }
    for(int i=0;i<n;i++){
        cin>>a[1][i];
    }//一下重点（敲黑板
    dp[0][0]=a[0][0];
    dp[1][0]=a[1][0];
cout<<dp[0][0]<<" "<<dp[1][0]<<endl;//这个是方便你们理解用的
    for(int i=1;i<n;i++){
        if(i==1){
            dp[0][i]=a[0][i]+dp[1][i-1];
            dp[1][i]=a[1][i]+dp[0][i-1];
        }
        else{
            dp[0][i]=max(dp[1][i-2]+a[0][i],dp[1][i-1]+a[0][i]);
            dp[1][i]=max(dp[0][i-2]+a[1][i],dp[0][i-1]+a[1][i]);//这个不讲了，上面讲过
        }
cout<<dp[0][i]<<" "<<dp[1][i]<<endl;//同上面的cout
    }
    cout<<max(dp[0][n-1],dp[1][n-1])<<endl;//最后一列就是两种答案，去最大值即可
    return 0;
}
```

The End.

---

## 作者：世末OIer (赞：0)

dp.

令

dp[i][0]表示考虑到第i个位置，当前位置不选人的最大值

dp[i][1]表示考虑到第i个位置，当前位置选队列1的人的最大值

dp[i][2]表示考虑到第i个位置，当前位置选队列2的人的最大值

则这题就结束了。

```cpp
	cout.tie(0);
	cin>>n;
	for(i=1;i<=n;++i) cin>>h1[i];
	for(i=1;i<=n;++i) cin>>h2[i];
	for(i=1;i<=n;++i){   //循环枚举
		for(j=0;j<3;++j){
			if(j==0) dp[i][j]=max(dp[i][j],max(dp[i-1][0],max(dp[i-1][1],dp[i-1][2])));
			else if(j==1) dp[i][j]=max(dp[i][j],max(dp[i-1][0],dp[i-1][2])+h1[i]);
			else dp[i][j]=max(dp[i][j],max(dp[i-1][0],dp[i-1][1])+h2[i]);
		}
	}
   cout<<max(dp[n][0],max(dp[n][1],dp[n][2]))<<endl;
```

---

