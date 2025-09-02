# Hits Different

## 题目描述

In a carnival game, there is a huge pyramid of cans with $ 2023 $ rows, numbered in a regular pattern as shown.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829G/e0a8819b39df73d7be64e1bb568b787d59d3e814.png)If can $ 9^2 $ is hit initially, then all cans colored red in the picture above would fall.

You throw a ball at the pyramid, and it hits a single can with number $ n^2 $ . This causes all cans that are stacked on top of this can to fall (that is, can $ n^2 $ falls, then the cans directly above $ n^2 $ fall, then the cans directly above those cans, and so on). For example, the picture above shows the cans that would fall if can $ 9^2 $ is hit.

What is the sum of the numbers on all cans that fall? Recall that $ n^2 = n \times n $ .

## 说明/提示

The first test case is pictured in the statement. The sum of the numbers that fall is $ $$$1^2 + 2^2 + 3^2 + 5^2 + 6^2 + 9^2 = 1 + 4 + 9 + 25 + 36 + 81 = 156. $ $ </p><p>In the second test case, only the can labeled  $ 1^2 $  falls, so the answer is  $ 1^2=1 $ .</p><p>In the third test case, the cans labeled  $ 1^2 $  and  $ 2^2 $  fall, so the answer is  $ 1^2+2^2=1+4=5 $ .</p><p>In the fourth test case, the cans labeled  $ 1^2 $  and  $ 3^2 $  fall, so the answer is  $ 1^2+3^2=1+9=10 $ .</p><p>In the fifth test case, the cans labeled  $ 1^2 $ ,  $ 2^2 $ , and  $ 4^2 $  fall, so the answer is  $ 1^2+2^2+4^2=1+4+16=21$$$.

## 样例 #1

### 输入

```
10
9
1
2
3
4
5
6
10
1434
1000000```

### 输出

```
156
1
5
10
21
39
46
146
63145186
58116199242129511```

# 题解

## 作者：ivyjiao (赞：13)

推倒 $9$ 号纸杯后，$5,6$ 号也会跟着倒下，按理来说推倒 $5,6$ 号的总分数应该和 $9$ 号有关系，但是他们俩加起来却不等于 $9$ 的值，因为 $5,6$ 号的共同父亲 $3$ 被推倒的总分数被加了两遍，所以将其减去即可。

但是要想让上面的思路变成 $O(n)$，就需要我们在每个位置存储在推倒这个位置后得到的总分数，这里我用的是二维数组模拟了这个纸杯的摆放并存储。

那么这个时候对于一个 $f_{i,j}$ 因为要模拟这些纸杯的摆放位置，所以 $j\leq i$ ，它的两个父亲就是 $f_{i-1,j-1},f_{i-1,j}$。重复加的值，即两个父亲的共同父亲就是 $f_{i-2,j-1}$。

注意 $1$ 的位置要特判，因为不特判的话这个点会访问到 $f_{-1,0}$，就会爆炸。 

DP 式：

$$
f_{i,j}=
\left\{\begin{matrix}
1 & i=1\\ 
f_{i-1,j-1}+f_{i-1,j}-f_{i-2,j-1}&i>1\\
\end{matrix}\right.
$$

代码：

```cpp
#include<iostream>
using namespace std;
long long t,n,cnt=1,a[2001][2001],b[4000001];
int main(){
    cin>>t;
    for(int i=1;i<=2000;i++){
        for(int j=1;j<=i;j++){
            a[i][j]=(i==1? 1:cnt*cnt+a[i-1][j-1]+a[i-1][j]-a[i-2][j-1]);
            b[cnt]=a[i][j];
            cnt++;
        }
    }
    while(t--){
        cin>>n;
        cout<<b[n]<<endl;
    }
}
```


---

## 作者：Pengzt (赞：8)

[CF1829G](https://www.luogu.com.cn/problem/CF1829G)

先将整个塔变为一个直角三角形的模样。这时就可以很好的用数组表示了，这时发现答案就是一个倒着的等腰直角三角形的和（不考虑边界）。

考虑预处理。

令 $a_i$ 为点 $i$ 所在的行数，$f_i$ 表示 $i$ 号点的答案，$g_i$ 表示 $i$ 和 它正上方的元素的价值。

当 $i$ 为当前行的第一个数时，显然 $f_i = f_{i - a_i + 1} + i ^ 2$，$g_i = g_{i - a_i + 1} + i ^ 2$

当 $i$ 为当前行的最后一个数时，显然 $f_i = f_{i - a_i} + i ^ 2$，$g_i = i ^ 2$

否则 $f_i = f_{i - a_i} + g_{i - a_i + 1} + i ^ 2$，$g_i = g_{i - a_i + 1} + i^2$

边界：$f_1 = g_1 = 1$。$g_1$ 其实可以不赋值，因为第一列是特判了的，转移时就用不到第一列的 $g$ 了。

时间复杂度：$\mathcal{O}(n + m)$

[评测记录](https://codeforces.com/contest/1829/submission/205233898)

---

## 作者：cjh20090318 (赞：3)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

**本题有多组数据。**

有一个高 $2023$ 层的数字金字塔。

你击中了一个编号为 $n$ 的罐子，请你求出该罐子上方编号的平方的和。

## 分析

设 $l_i$ 为 $i$ 左上方罐子的编号，$r_i$ 为 $i$ 右上方罐子的编号，$f_i$ 为击中罐子 $i$ 时的答案。

所以可以很容易地发现几点：

1. 该罐子编号为 $1$，不存在左上方和右上方。
2. 第 $x$ 层最左侧罐子的 $r_{\frac{x(x+1)}{2}-x+1}=\dfrac{x(x-1)}{2}-x+2$，不存在左上方。
3. 第 $x$ 层最右侧罐子的 $l_{\frac{x(x+1)}{2}}=\dfrac{x(x-1)}{2}$，不存在右上方。
4. 其余罐子 $i$ 的 $l_i=r_{i-1}$，$r_i=l_i+1$。

经过观察 $f_i=f_{l_i}+f_{r_i}-f_{l_{r_i}}+i^2$，因为如果只加左上方和右上方的答案，就会有一部分重合，所以需要减去 $i$ 上方的上方的罐子的答案。

然后预处理 $1 \sim n$ 的相应答案即可。

总体时间复杂度 $O(n+t)$，~~竟然成为最优解~~！

## 注意事项

注意 $10^6 \times 10^6 = 10^{12} > 2^{31}-1$，所以计算出的答案需要 `long long` 存储。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#define MAXN 1000001
typedef long long LL;
int l[MAXN],r[MAXN];//左上方和右上方。
LL f[MAXN];//答案数组。
void solve(){
	int n;scanf("%d",&n);
	printf("%lld\n",f[n]);
}
int main(){
	for(int i=2;(((LL)i*(i+1))>>1ll)<MAXN+i-1;i++)r[((i*(i+1))>>1)-i+1]=((i*(i-1))>>1)-i+2;//预处理第二点。
	for(int i=2;(((LL)i*(i+1))>>1ll)<MAXN;i++)l[(i*(i+1))>>1]=(i*(i-1))>>1;//预处理第三点。
	for(int i=2;i<MAXN;i++){
		if(l[i]||r[i]) continue;//如果左上方或右上方编号已经处理过，说明是边界节点，直接跳出即可。
		l[i]=r[i-1],r[i]=l[i]+1;//预处理第四点。
	}
	f[1]=1;//记得赋初值！
	for(int i=2;i<MAXN;i++) f[i]=f[l[i]]+f[r[i]]-f[l[r[i]]]+(LL)i*i;//预处理 f 数组。
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：hellolin (赞：2)


## Codeforces Round 871 (Div. 4) - G. Hits Different

[洛谷题面](https://www.luogu.com.cn/problem/CF1829G) | [CodeForces 题面](https://codeforces.com/problemset/problem/1829/G) | [AC 记录](https://www.luogu.com.cn/record/109860700)

蒟蒻在赛时把这题想得有点复杂了 QAQ（虽然也能 AC

先上个保险以免溢出。

``` cpp
#define int long long
```

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829G/e0a8819b39df73d7be64e1bb568b787d59d3e814.png)

观察这张图，我们发现每层最左端的数可组成序列：

$$1^2,\ 2^2,\ 4^2,\ 7^2,\ 11^2,\ 16^2,\cdots$$

注意到，这些数的底数不就是二阶等差数串么：

$$1^2,\ (1+1)^2,\ (1+1+2)^2,\ (1+1+2+3)^2,\ (1+1+2+3+4)^2,\ (1+1+2+3+4+5)^2,\cdots$$

所以可以预处理出每层最左边的数。

``` cpp
constexpr static int Max=1e6+1;
vector<int>a;
void init()
{
    a.push_back(-1); // 占位
    int now=1,d=1;
    a.push_back(now);
    while(now<Max)
    {
        now+=d;
        ++d;
        if(now<Max)a.push_back(now);
    }
}
```

那么另一个需要解决的点就是如何推出上一层会掉落的纸杯，其实这个很简单，只要再观察一下就可得到如下的规律（下用 $l(l>1)$ 表示当前层数）：

$$\mathrm{left}_{l-1} = \mathrm{left}_{l} - l\\
\mathrm{right}_{l-1} = \mathrm{right}_{l} - l + 1$$

注意左右端点可能会超出边界，所以还要分别取 $\mathrm{max}$ 和 $\mathrm{min}$。

核心代码如下：

``` cpp
int n,l,ans;
int le,ri;
vector<int>::iterator w;
void solve()
{
    cin>>n;
    w=upper_bound(a.begin(),a.end(),n);
    l=w-a.begin()-1; // 注意 -1 才是当前层
    ans=n*n;
    le=ri=n;
    while(l)
    {
        le-=l, ri-=l-1;
        --l; // 到达上一层
        le=max(le,a[l]);
        ri=min(ri,a[l+1]-1);
        for(int i=le;i<=ri;i++)
            ans+=i*i;
    }
    cout<<ans<<endl;
}
```

完整代码如下：

``` cpp
// 珍爱账号，请勿贺题
#include <bits/stdc++.h>
using namespace std;
#define int long long

constexpr static int Max=1e6+1;
vector<int>a;
void init()
{
    a.push_back(-1);
    int now=1,d=1;
    a.push_back(now);
    while(now<Max)
    {
        now+=d;
        ++d;
        if(now<Max)a.push_back(now);
    }
}

int n,l,ans;
int le,ri;
vector<int>::iterator w;
void solve()
{
    cin>>n;
    w=upper_bound(a.begin(),a.end(),n);
    l=w-a.begin()-1;
    ans=n*n;
    le=ri=n;
    while(l)
    {
        le-=l, ri-=l-1;
        --l;
        le=max(le,a[l]);
        ri=min(ri,a[l+1]-1);
        for(int i=le;i<=ri;i++)
            ans+=i*i;
    }
    cout<<ans<<endl;
}

int T;
int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin>>T;
    init();
    while(T--)solve();

    return 0;
}

```


---

## 作者：Iniaugoty (赞：2)

怎么原有题解那么多，和我的做法都不一样。

首先简述一下题意，有一个三角形，一个数字掉落，它上面的两个数字都会掉落。每次查询给出掉落的数字 $n$，求最后所有掉落数字的平方的和。

原图是这样：

![](https://espresso.codeforces.com/3f72320a7f225babc9b2b244a719e59e9e8f028d.png)

挪一下，修改成这样：

```
 1
 2  3
 4  5  6
 7  8  9 10
11 12 13 14 15
......
```
这样变成了一个二维数组，剩下的没数字的地方默认为 $0$。

然后考虑递推，设 $k$ 为 $(i,j)$ 上的数字，$s_{i,j}$ 为 $k$ 上的数字掉落的答案。

注意到 $(i,j)$ 掉落之后，上面的两个数字即 $(i-1,j-1)$ 和 $(i-1,j)$ 都会掉落，那么貌似有 $s_{i,j}=k^2+s_{i-1,j-1}+s_{i-1,j}$。

然而这是错的。

分析原因：

$(i-1,j-1)$ 上面的两个数字为 $(i-2,j-2)$ 和 $(i-2,j-1)$。

$(i-1,j)$ 上面的两个数字为 $(i-2,j-1)$ 和 $(i-2,j)$。

容易发现，如果直接相加，$s_{i-2,j-1}$ 就多计算一遍，那么减去即可。

正确的递推式为：$s_{i,j}=k^2+s_{i-1,j-1}+s_{i-1,j}-s_{i-2,j-1}$。

注意点：

- 递推式中出现了 $i-2$，所以要初始化至少第 $1$ 行（第 $0$ 行全为 $0$）。

- 还有个技巧，为了方便处理，对数字到坐标建立一个映射， $(x_i,y_i)$ 为数字 $i$ 的坐标。

核心代码见下，由于是一次跑完全部数据，运行一遍即可应付所有查询：

```cpp
//注意这几个数组的大小
//maxn=1e6，n 的最大可能取值
s[1][1]=1,x[1]=y[1]=1;
	for(i=2,k=2;k<=maxn;i++)
		for(j=1;j<=i&&k<=maxn;j++,k++)
			x[k]=i,y[k]=j,s[i][j]=k*k+s[i-1][j-1]+s[i-1][j]-s[i-2][j-1];
```

全文完。

---

## 作者：ZVitality (赞：2)

*1600，高出我认知。

做法很简单：设 $dp_i$ 是第 $i$ 块的值，然后我们可以发现它由 $i\times i$ 和这一块顶着的部分的和组成。

如 $5$ 可以分为 $2$ 和 $3$。

需要注意的是，当它顶着两块时（就是不在两边），那还要减去它顶着的两块的共同部分。

例如，$dp_{13}$ 是 $13^2+dp_8+dp_9-dp_5$。（$5$ 重叠要减掉）。

至于如何求得层数，我用了一种很简单的方法：预处理出每一层的最后一个，二分查找小于等于 $x$ 的就好。

代码：

```
#include <bits/stdc++.h>
using namespace std;
void Solve();
int main() {
  int tt = 1;
  // cin >> tt;
  while( tt-- ) {
    Solve();
  }
  return 0;
}
 
#define int long long
 
const int _ = 1e6 + 5;
 
int a[_] , dp[_];
 
void Init( int n ) {
  for( int i = 1 , sum = 0 ; i <= n ; i++ ) {
  	sum += i;
    a[ i ] = sum;
  }
  for( int i = 1 ; i <= n ; i++ ) {
    dp[ i ] = i * i;
    int step = lower_bound( a , a + n , i ) - a;
    int b1 = 0 , b2 = 0;
    if( i != ( step - 1 ) * step / 2 + 1 ) {
      dp[ i ] += dp[ i - step ];
      b1 = 1;
    }
    if( i != ( step ) * ( step + 1 ) / 2 ) {
      dp[ i ] += dp[ i - step + 1 ];
      b2 = 1;
    }
    if( b1 + b2 == 2 ) { //不在便捷就要减去重叠部分
      dp[ i ] -= dp[ i - step + 1 - ( step - 1 ) ];
    }
  }
}
 
void Solve() {
  Init( 1000000 );
  int t;
  cin >> t;
  while( t-- ) {
    int n;
    cin >> n;
    cout << dp[ n ] << '\n';
  }
}

```

---

## 作者：Scrolling_Ball (赞：1)

题意很简单，就是求 $n$ 号罐子及其上方的罐子的平方和嘛。

很容易想到可以用一个类似前缀和的做法做到 $O(n)$ 预处理，$O(1)$ 查询。

然后就是愉快的推式子啦：

[![p9BldMj.png](https://s1.ax1x.com/2023/05/09/p9BldMj.png)](https://imgse.com/i/p9BldMj)

图丑勿喷。

那么对于 $9$ 这个点来说，能直接转移到它的只有红色的两个点。

但是如果直接加上红色的两个点的话会多算黄色这个点的值，需要减掉。

我们就只需要求红色点和黄色点编号的公式就行了。

发现转移方程跟当前这个数所在的层数有关，于是可以在循环的最外层枚举层数。

设 $i$ 所在的层数为 $j$，则左边红色的点编号为 $i-j$，右边红色点编号为 $i-j+1$，黄色的标号为 $i-j-(j-1)+1=i-j\ast 2+2$。

然后这道题就做完啦。

**注意**：首尾的两个点需要特判一下，因为能转移的只有一个点。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int t;
int n;
ll sum[2000005];
int main()
{
    cin >> t;
    for(ll i = 1; i <= 1e6; i ++ )
        sum[i] = i * i;
    ll x = 1, la = 1;
    for(ll i = 1; x <= 1e6; i ++ )
    {
        sum[ ++ x] += sum[la];//每行第一个点和最后一个点的特判
        for(ll j = 1; j < i; j ++ )
        {
            sum[ ++ x] += sum[la] + sum[la + 1] - sum[la + 1 - i];
            la ++ ;
        }
        sum[ ++ x] += sum[la];
        la = x - i;
    }
    while(t -- )
    {
        cin >> n;
        cout << sum[n] << endl;
    }
	return 0;
}

```

---

## 作者：rmzls (赞：1)

### 思路
考虑预处理。每个点 $i$ 的值就是自己上方的点的二维前缀和加上 $i^2$。在最开始预处理即可。  
二维前缀和相关知识点可以参考[oi-wiki](https://oi-wiki.org/basic/prefix-sum/)，主要运用了容斥原理。

------------
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e6+20;
int sum[N],t,n,l[N],r[N],cnt,tu[2530][2530],lf[N],rf[N];
signed main(){
	scanf("%lld",&t);
	for(int i=1;i<=1000005;i++){
		sum[i]+=i*i;
	}
	for(int i=1;i<=2023;i++){
		for(int j=1;j<=i;j++){
			tu[i][j]=++cnt;
		}
	}
	for(int i=1;i<=2023;i++){
		for(int j=1;j<=i;j++){
			if(tu[i-1][j]){
				rf[tu[i][j]]=tu[i-1][j];
			}
			if(tu[i-1][j-1]){
				lf[tu[i][j]]=tu[i-1][j-1];
			}
			l[tu[i][j]]=tu[i+1][j];
			r[tu[i][j]]=tu[i+1][j+1];
		}
	}
	for(int i=1;i<=1000005;i++){
		sum[l[i]]+=sum[i];
		sum[r[i]]+=sum[i];
		sum[l[i]]-=sum[lf[i]];
	}
	while(t--){
		scanf("%lld",&n);
		printf("%lld\n",sum[n]);
	}
	return 0;
} 
```


---

## 作者：luqyou (赞：1)

# 题意

有一个金字塔形状排列的罐头，共 $2023$ 层，如下图。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829G/e0a8819b39df73d7be64e1bb568b787d59d3e814.png)

现在问，我如果击倒有一个编号为 $n$ 的罐头，那么所有被击倒的罐头的编号的平方之和是多少？一个罐头被击倒，它上面的一个或两个罐头也都会被击倒。

如图，击倒编号为 $9$ 的罐头以后，红色的罐头都会被击倒。

# 思路

考虑把这个金字塔对齐，再补全：

![](https://cdn.luogu.com.cn/upload/image_hosting/t9kq0yd7.png)

那么现在击倒 $9$ 后，红色部分将会倒塌。那么我们可以发现一个规律：从被击倒的罐子开始，每往上一层，被击倒的区间右端点不变，左端点 $-1$。

可以发现不在金字塔之外的，也就是不用计算的，要么是列号 $< 1$ 的，要么是列号 $>$ 当前层数的。我们可以在求一层的击倒区间的左右端点时处理。

对于一层的区间查询平方和，前缀和预处理一下就好。同时还要处理出每个数在哪一行那一列，方便计算。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2023;
long long row[2100][2100];//编号
int lev[5000001],arr[5000001];//lev[i]代表i在第几行，arr[i]代表i在第几列
long long sum[2100][2100];//前缀和
void init(){//构造金字塔，预处理行列和前缀和
	int cnt=0;
	for(int i=1;i<=maxn;i++){
		for(int j=1;j<=i;j++){
			//cout<<i<<" "<<j<<endl;
			row[i][j]=++cnt;
			sum[i][j]=sum[i][j-1]+row[i][j]*row[i][j];
			lev[cnt]=i;
			arr[cnt]=j;
		}
	}
}
long long query(int le,int l,int r){//查询le层，区间[l,r]的平方和
	return sum[le][r]-sum[le][l-1];
}
void solve(){
	int n;
	cin>>n;
	long long sums=0;
	int x=lev[n],y=arr[n];
	for(int i=x;i>=1;i--){
		int l=y-(x-i),r=y;//处理当前层被击倒的区间
		l=max(1,l),r=min(i,r);
		sums+=query(i,l,r);
	}
	cout<<sums<<endl;
}
int main(){
 	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	init();
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：snail2956 (赞：0)

提供一种不一样的做法。

整个塔分成多层，考虑按层统计答案。

我们发现每层都是一些连续自然数的平方和，考虑套自然数平方和公式：
$$\sum^{n}_{i=1}i^2=\dfrac{n(n+1)(2n+1)}{6}$$

然后就可以快乐的统计答案了。

$\tt{Code}$:

```cpp
#include<cstdio>
 
int t,n;
long long ans;
 
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		ans=0;
		int h,l,r;
		for(h=1;;h++) if(1ll*h*(h+1)/2>=n) break;
		l=r=n-1ll*h*(h-1)/2;
		while(1){
		    if(h==1){
		        ans++;
		        break;
		    }
        	if(l<1) l=1;
        	if(r>h) r=h; 
        	int ln=(1ll*h*(h-1)/2+l),rn=(1ll*h*(h-1)/2+r);
        	ans+=(1ll*rn*(rn+1)*(2*rn+1)/6)-(1ll*(ln-1)*ln/2*(2*ln-1)/3);
        	h--,l--;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 分析

我们枚举出 $1^2$ 到 $n^2$ 的前缀和，然后根据：答案等于总情况减去不满足情况，进行删减即可。

其中，总的情况一定是 $1^2$ 到 $n^2$ 的前缀和。不满足情况分为两部分，第一部分是左边，即在每一行会倒的最左边的左边的所有数，第二部分是右边，即在每一行会倒的最右边的右边的所有数。

计算第 $i$ 行会倒的最左边的数，我们根据样例的图不难发现就是第 $i+1$ 行会倒的最左边的数减去 $i+1+1$。计算第 $i$ 行会倒的最右边的数，同理，根据图可知是第 $i+1$ 行会倒的最左边的数减去 $i$。而最开始的数，即最下面的会倒的坐左边和最右边的数，都是 $n$，所以我们还需要算出 $n$ 在第几行。

计算不满足情况时，我们还要判断一下这一行的最左边和最右边是不是会倒的最左边和最右边，如果是，那么这一行以上就不会有不满足情况了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n;
const int N=1e6+10;
int ss[N],kk[N];//第i行的最右边的数值，1^2~i^2的和
signed main() 
{
	for(int i=1;i<=1000001;i++) ss[i]=ss[i-1]+i;//预处理
	for(int i=1;i<=1000001;i++) kk[i]=kk[i-1]+i*i;
	cin>>t;
	while(t--) 
	{
		cin>>n;
		int k=1;//枚举第几行
		int ceng=0;//n的层数
		while(1)
		{
			if(ss[k]==n)
			{
				ceng=k;break;
			}
			if(ss[k]>n&&ss[k-1]<n) 
			{
				ceng=k;break;
			}
			k++;
		}
		int now=n,ans=0;//不满足情况值
		int ceng2=ceng;//暂存
		while(ss[ceng-1]+1<now)//这里两种不满足的情况是分开计算的
		{
			ans+=kk[now-1]-kk[ss[ceng-1]];//前缀和思想计算每一行不满足的值
			now-=ceng;//第i-1行最左边的值
			ceng--;	
		}
		ceng=ceng2;
		now=n-(--ceng);//因为n所在的那一行的右边是不在总情况里的，所以直接跳到上一行
		while(ss[ceng]>now)//找右边
		{
			ans+=kk[ss[ceng]]-kk[now];
			now-=(ceng-1);//第i-1行最右边的值
			ceng--;
		}
		cout<<kk[n]-ans<<endl;//总的-不满足的=答案
	}	
	return 0;
}
```


---

## 作者：frelow_poem (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1829G)


官方题解给的做法是转化为二维前缀和，这里放个[链接](https://codeforces.com/blog/entry/116108)。在下不才，赛时没想到这个做法，介绍一个复杂但更直观的解法。

---
### 思路点拨

首先，我们把这座塔左对齐，将其抽象为一个二维数组。下图是选择击打 $9$ 号纸杯的结果。

![](https://cdn.luogu.com.cn/upload/image_hosting/c7juc6wn.png)

此时每个纸杯的正上方两个纸杯变为其正上方和左上方的两个纸杯。因此可画出如下的路径图：

![](https://cdn.luogu.com.cn/upload/image_hosting/uonhxuo6.png)

看起来我们只需要算出所有黄色格子值的平方和就行了。但是注意到，有些格子被红色箭头标记了两次（$1$ 和 $3$），需要去重。

![](https://cdn.luogu.com.cn/upload/image_hosting/euqdc7mh.png)

与其对于每一个格子都计算其正上和左上的值，不如先计算正上方的一整列（青色箭头标记），然后在每一列的最下方向左上移动一格（红色箭头标记），再计算这一格上方的一整列，直到边界停止。

下面是击打 $12$ 号纸杯的一个例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/48327vvu.png)

那么我们如何计算纸杯对应的数字呢？对于位于 $r$ 行 $c$ 列的纸杯，假设其对应的数字为 $v_{(r,c)}$，有：

$$v_{(r,c)}=\dfrac{r(r-1)}{2}+c$$

反之，给出 $v_{(r,c)}$，我们也可以求出 $r$ 和 $c$。具体实现见代码。

---
### 完整代码

```cpp
#include <cstdio>
using namespace std;
typedef long long ll;

inline ll Val(ll _r, ll _c) //求值
{
    return ((_r * (_r-1)) >> 1) + _c;
}

ll sdfs(int _r, int _c) //竖向枚举
{
    if (_r < _c) return 0;
    ll v = Val(_r, _c), tot = v*v;
    if (_r > 1) tot += sdfs(_r-1, _c);
    return tot;
}

void Solve()
{
    int n; scanf("%d", &n);
    ll cur = 0; int r = -1, c = -1;
    //这里使用枚举的方法求r, c, 也可以用更快的sqrt()
    for (int i = 1; i <= n; i++)
    {
        cur += i;
        if (cur >= n)
        {
            r = i;
            break;
        }
    }
    c = n - ((r * (r-1)) >> 1);

    ll ans = 0;
    while (c >= 1 && r >= 1) //斜向枚举
    {
        ans += sdfs(r, c);
        r--, c--;
    }
    printf("%lld\n", ans);
}

//电脑看不见
int main()
{
    int T; scanf("%d", &T);
    while (T--) Solve();
    return 0;
}
```

---
### 后记

注意到每一列上需要求出的格子数目都是相同的，因此将整个数组上对齐得到一个倒三角形后，所有要求值的格子就变为了一个矩形。此时就得到了官方题解的二维前缀和做法，在此不再赘述。

感谢您的观看。

---

## 作者：shinzanmono (赞：0)

# Codeforces Round 871 (Div. 4) G 题解

首先理解一下题意，当一个方块掉落时，它的上方与它有杰出的方块掉落，我们找一下规律：

* 方块 $9^2$ 位于第 $4$ 行，他的上方分别是 $5^2$ 和 $6^2$。

* 方块 $14^2$ 位于第 $5$ 行，他的上方分别是 $9^2$ 和 $10^2$。

* 方块 $12^2$ 位于第 $5$ 行，他的上方分别是 $7^2$ 和 $8^2$。

我们总结出，如果一个在第 $p$ 行的方块 $x^2$ 不是最右边的那个，那么他的右上方的方块便是 $(x-p+1)^2$；如果一个在第 $p$ 行的方块不是最左边的那个，那么他左上方的方块便是 $(x-p)^2$。

我们可以发现，推倒一个方块时，这个方块的左上方的全部方块有贡献，而右上方的方块的贡献可以视为推倒右上方方块的贡献，把二者相加，便为总贡献。

我们维护一个方块 $i^2$ 及其左上方方块的权值和 $f_i$，最后的答案便是：
$$
ans_i=
\left\{
\begin{aligned}
&f_i+ans_{x-p}&x-p\text{不是一行的最右侧方块}\\
&f_i&otherwise
\end{aligned}
\right.
$$
其中 $p$ 是方块 $i^2$ 所在的行。

代码实现如下：
```cpp
#include<iostream>
#include<algorithm>
#include<bitset>
const int sz = 2e6 + 1100;
using ll = long long;
ll f[sz], dep[sz]; // dep 数组是每个方块所在的行数
std::bitset<sz> rside; // 判断该方块是否在最右侧
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    for (ll i = 1; i <= 2000; i++) {
        rside[(i + 1) * i / 2] = 1;
        for (ll j = (i - 1) * i / 2 + 1; j <= (i + 1) * i / 2; j++) {
            f[j] = j * j, dep[j] = i;
            if (j != (i - 1) * i / 2 + 1) f[j] += f[j - i];
        }
    }
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        ll res = f[n];
        while (!rside[n]) 
            n -= dep[n] - 1, res += f[n];
        std::cout << res << "\n";
    }
    return 0;
}
// 三年 OI 一场空，不开 long long 见祖宗
```

---

## 作者：沉石鱼惊旋 (赞：0)

[更好的阅读体验](http://blog.cyx2009.top/archives/169/)

# G.[Hits Different](https://codeforces.com/contest/1829/problem/G)

## 题目翻译

> 你有一个罐子搭成的金字塔，如图![](https://espresso.codeforces.com/3f72320a7f225babc9b2b244a719e59e9e8f028d.png)。第 $i$ 个罐子代表数 $i^2$，现在打掉第 $i$ 个罐子，问掉落罐子的数之和为多少。
> 
> $1\leq n\leq 10^6$。
> 
> $t$ 组数据，$1\leq t\leq 1000$。

## 题目思路

观察可得，打掉第 $x$ 行第 $y$ 列的罐子，那么第 $x$ 行第 $y-1$ 和第 $x$ 行第 $y$ 列的罐子都会倒塌，然后逐个往上。

我们做一个预处理，只需找出 $n$ 罐子的位置，一个个往上递推，用前缀和优化记录某一行某一段的和即可。

## 完整代码


```
#include<bits/stdc++.h>
using namespace std;
int x,l,r;
long long a[2020][2020],cnt;
long long s[2020][2020];
pair<int,int>fa[3000020];
long long Sum(int i,int l,int r)
{
    if(l<1)l=1;
    if(r>i)r=i;
    return s[i][r]-s[i][l-1];
}
void Get(int n)
{
    x=fa[n].first;
    l=r=fa[n].second;
}
void solve()
{
    int n;
    long long ans=0;
    cin>>n;
    Get(n);
    while(x>0)
    {
        ans+=Sum(x,l,r);
        l--;
        x--;
    }
    cout<<ans<<endl;
}
int main()
{
    for(int i=1;i<=2000;i++)
    {
        for(int j=1;j<=i;j++)
        {
            a[i][j]=++cnt;
            s[i][j]=s[i][j-1]+a[i][j]*a[i][j];
            fa[cnt]=make_pair(i,j);
        }
    }
    int t;cin>>t;while(t--)
    solve();
    return 0;
}
```


---

## 作者：ForgotDream_CHN (赞：0)

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17378919.html)

话说这场比赛的题名字好像都是 Taylor Swift 的歌名。

## 题意

有一个由罐子排列成的金字塔，罐子自上而下依次编号：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1829G/e0a8819b39df73d7be64e1bb568b787d59d3e814.png)

现在你要打下一个罐子，则与其有关的所有罐子也会被击落，计算所有被击落的罐子编号的平方和。

比如说，你击中了 $9$ 号罐子，则上图中所有标红的罐子都会被击落。

$n \le 10^6$。多测，$t \le 10^3$。

## 思路

乍一看好像很不好找出与一个罐子有关的所有罐子的编号？但是，我们可以把原图旋转一下，得到一个矩阵：

$$
\begin{pmatrix}
\color{red}{1} & \color{red}{3} & \color{red}{6} & 10 & 15 & \cdots \\
\color{red}{2} & \color{red}{5} & \color{red}{9} & 14 & 20 & \cdots \\
4 & 8 & 13 & 19 & 26 & \cdots \\
7 & 12 & 18 & 25 & 33 & \cdots \\
11 & 17 & 24 & 32 & 41 & \cdots \\
\vdots & \vdots & \vdots & \vdots & \vdots & \ddots
\end{pmatrix}
$$

这看上去是个无穷矩阵，但事实上由于题目中给出的 $n \le 10^6$，因此矩阵中的元素个数是有限的。

观察这个矩阵，我们得到：与某个数字相关的所有数字共同构成这个数字所在位置的左上方的矩形。比如说，与 $9$ 有关的数字（上图中标红的数字）刚好都在 $9$ 左上方的矩形中。

于是现在的问题就转化为了一个二维前缀和，即：求出 $n$ 左上角这个矩形中所有数字的平方和。如果我们能构造出这个矩阵的话，这当然是很容易的。

如何构造这个矩阵呢？观察得到矩阵中每一行与每一列的数字间都存在很强的递变规律，记上述的矩阵为 $A$，则有 $A_{i, j} = A_{i, j - 1} + i + j - 1 = A_{i - 1, j} + i + j - 2$。于是我们就可以通过这个关系求出具体的矩阵 $A$，记录下每个数字的坐标，在其上做二维前缀和就可以求出答案。

还有一种思路，即我的实现方法，就是找出每一行每一列增量的变化关系，这个其实与上边的做法本质相同，就不多说了。

我的具体实现稍有不同，我是先计算出每一行的前缀平方和，再将其与前边的行的前缀平方和累加来计算出每个数字对应的答案的。

由于这个矩阵不会随 $n$ 变化，因此我们可以把它预处理出来，这样就可以做到单次询问 $O(1)$，于是总的时间复杂度为 $O(\max(n) + t)$。

## 代码

代码中的 `pre[i]` 即为数字 $i$ 所在行的前缀和，`f[i]` 即为 $i$ 对应的答案。

```cpp
#include <bits/stdc++.h>

using i64 = long long;

static std::vector<i64> f(1e6 + 1);

void init() {
  f[1] = 1;

  std::vector a(1.5e3, std::vector<i64>(1.5e3));
  std::vector<i64> pre(1e6 + 1);
  int d1 = 1, row = 0;
  for (int i = 1; i <= 1e6; i += d1, d1++, row++) {
    int d2 = 1 + d1, col = 0;
    for (int j = i; j <= 1e6; j += d2, d2++, col++) {
      a[row][col] = j;
      pre[j] = (i64) j * j + (col ? pre[a[row][col - 1]] : 0);
      f[j] = pre[j] + (row ? f[a[row - 1][col]] : 0);
    }
  }

  return;
}

void solve() {
  int n;
  std::cin >> n;
  std::cout << f[n] << "\n";
  return;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  init();

  int t;
  std::cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
```

---

