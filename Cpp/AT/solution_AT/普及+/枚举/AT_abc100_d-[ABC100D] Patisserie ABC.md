# [ABC100D] Patisserie ABC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc100/tasks/abc100_d

高橋君はプロのパティシエになり, AtCoder Beginner Contest 100 を記念して, 「ABC洋菓子店」というお店を開いた.

ABC洋菓子店では, $ N $ 種類のケーキを売っている.  
 各種類のケーキには「綺麗さ」「おいしさ」「人気度」の $ 3 $ つの値を持ち, $ i $ 種類目のケーキの綺麗さは $ x_i $, おいしさは $ y_i $, 人気度は $ z_i $ である.  
 これらの値は $ 0 $ 以下である可能性もある.

りんごさんは, ABC洋菓子店で $ M $ 個のケーキを食べることにした. 彼は次のように, 食べるケーキの組み合わせを選ぶことにした.

- 同じ種類のケーキを $ 2 $ 個以上食べない.
- 上の条件を満たしつつ, (綺麗さの合計の絶対値) + (おいしさの合計の絶対値) + (人気度の合計の絶対値) が最大になるように選ぶ.

このとき, りんごさんが選ぶケーキの (綺麗さの合計の絶対値) + (おいしさの合計の絶対値) + (人気度の合計の絶対値) の最大値を求めなさい.

## 说明/提示

### 制約

- $ N $ は $ 1 $ 以上 $ 1\ 000 $ 以下の整数
- $ M $ は $ 0 $ 以上 $ N $ 以下の整数
- $ x_i,\ y_i,\ z_i\ (1\ \leq\ i\ \leq\ N) $ は, それぞれ $ -10\ 000\ 000\ 000 $ 以上 $ 10\ 000\ 000\ 000 $ 以下の整数.

### Sample Explanation 1

$ 2,\ 4,\ 5 $ 種類目のケーキを食べることを考える. そのとき, 「綺麗さ」「おいしさ」「人気度」の合計はそれぞれ次のようになる. - 綺麗さ：$ 1\ +\ 3\ +\ 9\ =\ 13 $ - おいしさ：$ 5\ +\ 5\ +\ 7\ =\ 17 $ - 人気度：$ 9\ +\ 8\ +\ 9\ =\ 26 $ このときの (綺麗さの合計の絶対値) + (おいしさの合計の絶対値) + (人気度の合計の絶対値) は $ 13\ +\ 17\ +\ 26\ =\ 56 $ となり, これが最大になる.

### Sample Explanation 2

$ 1,\ 3,\ 5 $ 種類目のケーキを食べることを考える. そのとき, 「綺麗さ」「おいしさ」「人気度」の合計はそれぞれ次のようになる. - 綺麗さ：$ 1\ +\ 7\ +\ 13\ =\ 21 $ - おいしさ：$ (-2)\ +\ (-8)\ +\ (-14)\ =\ -24 $ - 人気度：$ 3\ +\ (-9)\ +\ 15\ =\ 9 $ このときの (綺麗さの合計の絶対値) + (おいしさの合計の絶対値) + (人気度の合計の絶対値) は $ 21\ +\ 24\ +\ 9\ =\ 54 $ となり, これが最大になる.

### Sample Explanation 3

$ 3,\ 4,\ 5,\ 7,\ 10 $ 種類目のケーキを食べると, 綺麗さの合計は $ -323 $, おいしさの合計は $ 66 $, 人気度の合計は $ 249 $ となる. このときの (綺麗さの合計の絶対値) + (おいしさの合計の絶対値) + (人気度の合計の絶対値) は $ 323\ +\ 66\ +\ 249\ =\ 638 $ となり, これが最大になる.

### Sample Explanation 4

ケーキの綺麗さ, おいしさ, 人気度や出力すべき値が, 32bit 整数に収まらない場合もある.

## 样例 #1

### 输入

```
5 3
3 1 4
1 5 9
2 6 5
3 5 8
9 7 9```

### 输出

```
56```

## 样例 #2

### 输入

```
5 3
1 -2 3
-4 5 -6
7 -8 -9
-10 11 -12
13 -14 15```

### 输出

```
54```

## 样例 #3

### 输入

```
10 5
10 -80 21
23 8 38
-94 28 11
-26 -2 18
-69 72 79
-26 -86 -54
-72 -50 59
21 65 -32
40 -94 87
-62 18 82```

### 输出

```
638```

## 样例 #4

### 输入

```
3 2
2000000000 -9000000000 4000000000
7000000000 -5000000000 3000000000
6000000000 -1000000000 8000000000```

### 输出

```
30000000000```

# 题解

## 作者：μηδσ (赞：7)

## Solution

其实这道题模拟就行了，数据范围也不是很大

事先决定$x,y,z$的和分别是正的还是负的分别记录为$i,j,k$，然后直接暴力求出每个蛋糕相应的特点（价值）然后求出前$m$个蛋糕的价值总和

ps：表面上虽然有四重循环，但是钱三重都是判断符号的循环，所以时间复杂度并不是很高。

## Code

~~~cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

const int MAXN = 1005;
const int INF = 0x3f3f3f3f;
const long long LNF = 0x3f3f3f3f3f3f3f3f;

ll n, m;
ll i, j, k;

struct CAKE{
	ll a;
	ll b;
	ll c;
} cake[MAXN];

bool cmp(CAKE a, CAKE b){
	return a.a * i + a.b * j + a.c * k > b.a * i + b.b * j + b.c * k;
}

int main(){
	cin >> n >> m;
	for(i = 1;i <= n;i++)
		cin >> cake[i].a >> cake[i].b >> cake[i].c;
	ll ans = -LNF;
	for(i = -1;i <= 1;i += 2)
		for(j = -1;j <= 1;j += 2)
			for(k = -1;k <= 1;k += 2){	
				sort(cake + 1, cake + n + 1, cmp); 
				ll tot[5] = {};		
				for(int l = 1;l <= m;l++){
					tot[1] += cake[l].a;
					tot[2] += cake[l].b;
					tot[3] += cake[l].c;
				} 
				ans = max(ans, tot[1] * i + tot[2] * j + tot[3] * k);
			}
	cout << ans << endl;
	return 0;
}

~~~

---

## 作者：Nightingale_OI (赞：4)

### 大意

有 $ n $ 个物品，每个物品有三个权值 $ a_i $，$ b_i $，$ c_i $。

要从这选出 $ m $ 个物品，将它们这三个权值分别求和记为 $ A $，$ B $，$ C $。

求最大的 $ |A| + |B| + |C| $。

### 思路

考虑如何去掉绝对值：我们枚举三个绝对值里分别是正数还是负数，直接去掉绝对值。

一共有 $ 8 $ 种情况，一一动态规划求解即可。

即使枚举时可能无法使最后结果是非负数，但由于这样不优，不影响计算。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
#define pos(i,j) (((i>>(j-1)&1ll)==1?1ll:-1ll))
void Max(long long& x,long long y){if(x<y)x=y;}
long long a[1010],b[1010],c[1010];
long long dp[1010][1010][8],ans;
int main(){
    cin>>n>>m;
    f(i,1,n)scanf("%lld %lld %lld",&a[i],&b[i],&c[i]);
    f(j,1,m)f(k,0,7)dp[0][j][k]=-101010101010101010;
    f(i,1,n)f(j,1,m)f(k,0,7){
        dp[i][j][k]=-101010101010101010;
        Max(dp[i][j][k],dp[i-1][j][k]);
        Max(dp[i][j][k],dp[i-1][j-1][k]+pos(k,1)*a[i]+pos(k,2)*b[i]+pos(k,3)*c[i]);
    }
    f(k,0,7)Max(ans,dp[n][m][k]);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：suzhikz (赞：3)

发现 $n$ 的范围很特殊，然后发现这玩意很不好 dp，原因主要是值太大以及正负号。

于是考虑用什么操作让正负号变得确定，发现只有三种值，所以可以直接枚举正负号，然后再乘上去，直接排序贪心取最大的即可。

为什么正确呢？首先最大值肯定能被取到，当我们枚举的正负号与最终答案的正负相同时，一定能取到，否则一定有一个值比答案中的大发生了交换，与答案是最大的相冲，显然不行。

若枚举的正负号不同，则有可能我们枚举的符号与最终结果的符号不同，但是此时答案一定小于最终答案，因为减去正数显然比加上正数更不优，所以答案一定更小。

代码非常好写。


```cpp
for(int i=-1;i<=1;i+=2){
	for(int j=-1;j<=1;j+=2){
		for(int k=-1;k<=1;k+=2){
			for(int l=1;l<=n;l++){
				z[l]=a[l]*i+b[l]*j+c[l]*k;
			}
			sort(z+1,z+1+n);
			ll book=0;
			for(int i=n;i>=n-m+1;i--)book+=z[i];
			ans=max(ans,book);
		}
	}
}
```

---

## 作者：linjinxi666 (赞：2)

# 思路

一共有 $a,b,c$ 三个序列，去掉绝对值符号后 $a_i,b_i,c_i$ 三个数的符号情况只能有 $2\times2\times2=8$ 种。

所以我们只需要枚举每一种情况，然后取最大值就好了。  

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//宏定义
bool cmp(int a,int b){//排序判断函数
	return a>b;
}
int n,m,a[1005],b[1005],c[1005],ans=0,h[1005];
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i]>>c[i];
	}
	for(int i=-1;i<=1;i+=2){//枚举
		for(int j=-1;j<=1;j+=2){//枚举
			for(int k=-1;k<=1;k+=2){//枚举
				for(int l=1;l<=n;l++){
					h[l]=i*a[l]+j*b[l]+k*c[l];//计算每一行在当前符号下的值
				}
				sort(h+1,h+n+1,cmp);//排序
				int res=0;
				for(int l=1;l<=m;l++){
					res+=h[l];//选m个值
				}
				ans=max(res,ans);//求最大值
			}
		}
	}
	cout<<ans;//输出
	return 0;//圆满结尾
}

```

---

## 作者：LiamZou (赞：2)

题目传送门:[题目传送门](https://www.luogu.com.cn/problem/AT_abc100_d?contestId=220370)

题目题解：看到题目的第一眼，可以轻松的想到我们可以打一个暴力搜索。枚举每一种选长度为 $m$ 的 $t$ 数组的状态，最后取最大值就可以了。
虽然他会 WA ，但还是放代码吧，想到这一步是一个进步。代码很容易理解对吧。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
//记住，一定要开 long long （警钟敲爆 ） 
int n, m, a[1005], b[1005], c[1005], maxn = -1;
void dfs(int one, int two, int three, int now, int need)
/*
one、two、three 分别表示当前状态下 a[i]、b[i] 和 c[i] 的和。
now表示当前搜索到了第几个。
need表示还需几个才能得到 m 个数的 t 数组。 
*/ 
{
	if (need == 0)//如果满足了条件就计算当前状态的答案并取 max 
	{
		int temp = abs(one) + abs(two) + abs(three);
		maxn = max(maxn, temp);
		return;
	}
	if (now >= n + 1)//如果越界了还没满足条件就直接 return 
	{
		return;
	}
	dfs(one, two, three, now + 1, need);//不选择
	dfs(one + a[now], two + b[now], three + c[now], now + 1, need - 1);//选择
}
signed main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i] >> b[i] >> c[i];
	}
	dfs(0, 0, 0, 1, m);//开始 dfs 
	cout << maxn << endl;//输出 
	return 0;//结束 awa 
}
```
现在我们不放在这个代码的基础上再想想。
题目是想要下标为 $t_i(1\leq i\leq n)$ 的 $a_i$ 和 $b_i$ 和 $c_i$ 的和分别的绝对值的和最大。

也就是 $\lvert \sum_{i=1}^m a_{t_i} \rvert+\lvert \sum_{i=1}^m b_{t_i} \rvert+\lvert \sum_{i=1}^m c_{t_i} \rvert$ 的最大值
（这里有点难理解）
注意是绝对值的话，我们就不妨可以想一下：**如果我们枚举 $a,b,c$ 数组的和的目标状态是正数还是负数的话，时间复杂度就可以降一个指数了。**

继续跟着这个思路：
我们只需要计算出当前目标状态下，对与每一个下标的 $a,b,c$ 数组对当前的状态的贡献，最后把这一些贡献排一个序，去最大的前 $m$ 个的和就是当前状态的最大答案了。
对于最终答案，我们轻轻松松取个 $\max$ 就可以输出了。
计算了一下时间复杂度是: $\mathcal{O}(n\log{n})$ 

题目中是 $1\leq n\leq1000$ 且 $0\leq m\leq n$
**时间复杂度完全够用！！！**
好了最终代码就现在贴上去了：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//要开 long long qwq 
int n, m, one, two, three, maxn = -1, ans, f[1005], a[1005], b[1005], c[1005];
signed main()
{
	cin >> n >> m;//输入不用多说了吧
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i] >> b[i] >> c[i];
	}
	for (one = -1; one <= 1; one += 2)
	{
		for (two = -1; two <= 1; two += 2)
		{
			for (three = -1; three <= 1; three += 2)//这里的 one,two,three 分别表示的是当前 a,b,c 数组的目标值是正数还是负数。 
			{
				ans = 0;
				for (int i = 1; i <= n; i++)
				{
					f[i] = a[i] * one + b[i] * two + c[i] * three;//f[i] 表示的是对于下标（1<=i<=n）的 a,b,c 数组的值在当前状态下的贡献 
				}
				sort(f + 1, f + n + 1, greater<int>());//从大到小排序贡献 
				for (int i = 1; i <= m; i++)
				{
					ans += f[i];//取前 m 大的贡献值 
				}
				//加起来之后，ans 就是当前状态下能达到的最大答案了 
				maxn = max(maxn, abs(ans));//与最终答案取 max（打擂台，不用多说了吧） 
			}
		}
	}
	cout << maxn << endl;//输出 
	return 0;//华丽结束 awa
}
```

---

## 作者：andycode (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc100_d)
## 题目大意
有 $n$ 个物品，每个物品有三个价值，分别为 $a_i$，$b_i$ 和 $c_i$，且每一个物品都有**只有一个**。

现在要从这 $n$ 个物品中取走 $m$ 个，设取出的物品为 $t_1\sim t_m$，求这些取出的物品的三个价值各自相加后的绝对值之和最大是多少，即 $|\sum\limits_{i=1}^{m}a_{t_i}|+|\sum\limits_{i=1}^{m}b_{t_i}|+|\sum\limits_{i=1}^{m}c_{t_i}|$ 的最大值。
## 思路
枚举每个数列之和是否为负数的 $8$ 种情况，来统计每个 $t_i$ 对答案的贡献。用 $01$ 背包再加个维度即可实现。

最终答案为每种可能的最大值，由于最优答案肯定属于这 $8$ 种情况之一，所以最大值肯定为最优答案。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1003;
int n,m;
long long a[N],b[N],c[N],dp[N][N][8];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);
	memset(dp,-127,sizeof(dp));//因为可能为负数，所以初始化为负无穷
	for(int j=0;j<8;j++)
		dp[0][0][j]=0;//初始化
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;k<8;k++)//01背包再枚举8种情况
				if(j)
					dp[i][j][k]=max(dp[i-1][j][k],dp[i-1][j-1][k]+(k&1?-1:1)*a[i]+(k&2?-1:1)*b[i]+(k&4?-1:1)*c[i]);
				else
					dp[i][j][k]=dp[i-1][j][k];
	long long ans=0;
	for(int i=0;i<8;i++)
		ans=max(ans,dp[n][m][i]);//统计最大值
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：chinazhanghaoxun (赞：1)

## 思路

这道题直接枚举 $A$，$B$，$C$ 的正负性即可，因为只有正负两种情况，所以只需要枚举 $2^3=8$ 次即可。对于每一次，我们计算出每个蛋糕的总价值，再从大到小排序后选前 $m$ 个相加就得到了当前情况的 $sum$。因为每种情况都是合法的，所以我们可以取到最大值。因此，可以得到 $ans=\max (sum)$。

该算法的时间复杂度为 $\cal O(n)$，可以通过。
## 代码

根据正负性枚举即可。

```cpp
#include<bits/stdc++.h>
#define int long long //开long long 
using namespace std;
int n,m,a[1005],b[1005],c[1005],t[1005],ans;
bool cmp(int x,int y){
	return x>y;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i]>>b[i]>>c[i];
	//枚举符号 
	for(int i=-1;i<=1;i+=2)
		for(int j=-1;j<=1;j+=2)
			for(int k=-1;k<=1;k+=2){
				for(int q=1;q<=n;q++)
					t[q]=a[q]*i+b[q]*j+c[q]*k; //求出每种情况对应的答案 
				sort(t+1,t+n+1,cmp);//从大到小排序方便求大的
				int sum=0;
				for(int q=1;q<=m;q++) //取最大的m个 
					sum+=t[q];
				ans=max(ans,sum);
			}
	cout<<ans;
	return 0;
}
```

---

## 作者：CASCwty (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc100_d)

## 思路

赛时考了，想了一个很奇怪的贪心，不负众望啊！[死了](https://www.luogu.com.cn/record/194989651)。

后来仔细地想了一下，本题最重要的一点是如何消除绝对值。$|A|= \begin{cases}-A(A<0)\\0(A=0)\\A(A>0) \end{cases}$

因此：对于每一个 $|\sum\limits_{i=1}^m a_{t_i}|+|\sum\limits_{i=1}^m b_{t_i}|+|\sum\limits_{i=1}^m c_{t_i}|$，完全可以通过乘以 $1$ 或 $-1$，消除绝对值的问题，得到所有答案。总共有 $2×2×2=8$ 种方法。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1010;
int n,m;
struct Node{
	int a,b,c;
}inf[N],t[N];
int h[N];
int ans;
int absl[2]={1,-1};
int ret;
void change(int aa,int bb,int cc)
{
	for(int i=1;i<=n;i++)
	{
		t[i].a=inf[i].a*aa;
		t[i].b=inf[i].b*bb;
		t[i].c=inf[i].c*cc;
	}
}
int cal()
{
	ret=0;
	for(int i=1;i<=n;i++)
		h[i]=t[i].a+t[i].b+t[i].c;
	sort(h+1,h+n+1);
	for(int i=n-m+1;i<=n;i++)ret+=h[i];
	return ret; 
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld%lld",&inf[i].a,&inf[i].b,&inf[i].c);
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			for(int k=0;k<2;k++)
			{
				change(absl[i],absl[j],absl[k]);
				ans=max(ans,cal());
			}
		}
	}
	printf("%lld",ans);
	return 0;
 } 
```

---

## 作者：easy42 (赞：0)

### 思路
本题难点在于想到分类讨论。

首先，绝对值是一个非常麻烦的东西，所以我们想办法把它拆掉。

所以对绝对值的正负讨论。

然后发现绝对值只有两种情况：正的和负的。

所以一共只有 $2^3=8$ 种情况，完全可以枚举！

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
struct edge{
	int x,y,z;
}a[200005],b[200005];
int h[8][3]={{1,1,1},{1,1,-1},{1,-1,1},{-1,1,1},{-1,-1,1},{-1,1,-1},{1,-1,-1},{-1,-1,-1}};
int maxx=-1;
bool cmp(edge h1,edge h2){
	return h1.x+h1.y+h1.z>h2.x+h2.y+h2.z;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].x>>a[i].y>>a[i].z;
	}
	for(int i=0;i<8;i++){
		for(int j=1;j<=n;j++){
			b[j].x=a[j].x*h[i][0];
			b[j].y=a[j].y*h[i][1];
			b[j].z=a[j].z*h[i][2];
		}
		sort(b+1,b+n+1,cmp);
		int ans=0;
		for(int j=1;j<=m;j++){
			ans+=(b[j].x+b[j].y+b[j].z);
		}
		maxx=max(maxx,ans);
	}
	cout<<maxx;
	return 0;
}
```

---

## 作者：xixihaha2021 (赞：0)

# [[ABC100D] Patisserie ABC](https://www.luogu.com.cn/problem/AT_abc100_d)
## 题意简述
选择一个不重数列 $\{t_m\}$，求 $|\sum_{i=1}^n a_i|+|\sum_{i=1}^n b_i|+|\sum_{i=1}^n c_i|$ 的最大值。
## 思路简述
分讨每个绝对值内的正负性共计 $2^3=8$ 种情况。对于每种情况，令 $d_i=p_1 \cdot a_i+p_2 \cdot b_i+p_3 \cdot c_i$，式中 $p_i \in \{-1,1\}(1 \le i \le 3)$，其具体的值根据对应数列绝对值内的正负而定，则只需对 $\{d_n\}$ 进行排序，取其前 $m$ 大的项求和即可。对每种情况的答案取最大值。

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,a[1005],b[1005],c[1005],w[1005],f[1005],ans,sum,d[8][3] = {{1,1,1},{1,1,-1},{1,-1,1},{1,-1,-1},{-1,1,1},{-1,1,-1},{-1,-1,1},{-1,-1,-1}};
ll read(){
	ll x = 0;
	bool f = true;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-')f = !f;
		ch = getchar();
	}
	while(isdigit(ch))x = x * 10 + ch - '0',ch = getchar();
	return x * f * 2 - x;
}
ll write(ll x,string ch){
	ll f = 1,L = ch.size(),tmp = x;
	if(tmp < 0){
		putchar('-');
		tmp *= -1;
	}
	while(f <= tmp)f *= 10;
	if(tmp)f /= 10;
	while(f){
		putchar(tmp / f + '0');
		tmp -= (tmp / f * f),f /= 10;
	}
	for(ll i = 0;i <= L - 1;i++)putchar(ch[i]);
	return x;
}
int main(){
	n = read(),m = read();
	for(ll i = 1;i <= n;i++)a[i] = read(),b[i] = read(),c[i] = read();
	for(ll i = 0;i <= 7;i++){
		memset(w,0,sizeof(w));
		sum = 0;
		for(ll j = 1;j <= n;j++)w[j] = a[j] * d[i][0] + b[j] * d[i][1] + c[j] * d[i][2];
		sort(w + 1,w + n + 1);
		for(ll j = n;j >= n - m + 1;j--)sum += w[j];
		ans = max(ans,sum);
	}
	write(ans,"");
	return 0;
}
```

---

## 作者：3_14 (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/AT_abc100_d)**

# 思路

先考虑一个简单的子问题，即如果目标是最大化（总和的美观度 + 总和的美味度 + 总和的受欢迎度），那么从 $x_i + y_i + z_i$ 较大的蛋糕中选择 $M$ 个就是最优选择。

原问题是要最大化（美观度总和的绝对值）+（美味度总和的绝对值）+（受欢迎度总和的绝对值）。这意味着我们需要考虑让某些数的总和为负来达到更大的绝对值。

对于每个参数（美观度、美味度、受欢迎度），我们可以枚举，使其总和朝着正方向或负方向最大。由于有三个参数，所以总共有 $2^3 = 8$ 种组合方式。举个栗子，如果我们希望美观度和美味度的总和朝着正方向最大，而受欢迎度的总和朝着负方向最大，那么从 $x_i + y_i - z_i$ 较大的蛋糕中选择 $M$ 个，这就是最优选择。

# 代码

```cpp
#include<bits/stdc++.h>
#define lcm(x,y) x/__gcd(x,y)*y;
#define str to_string
using namespace std;
using ll=long long;
const int MAX=1e5+1;
const double EPS=1e-6;
struct Cake{
    ll beauty,tastiness,popularity;
};// 蛋糕结构体
// 根据不同的权重计算排序依据
ll calculateScore(Cake &cake, int signBeauty, int signTastiness, int signPopularity){
    return signBeauty * cake.beauty + signTastiness * cake.tastiness + signPopularity * cake.popularity;
}
// 计算一种组合方式下的最大绝对值和
ll calculateMaxAbsSum(vector<Cake> &cakes, int M, int signBeauty, int signTastiness, int signPopularity) {
    vector<ll> scores;
    for(auto cake : cakes)
        scores.push_back(calculateScore(cake, signBeauty, signTastiness, signPopularity));
    sort(scores.rbegin(), scores.rend());
    ll sumBeauty = 0, sumTastiness = 0, sumPopularity = 0;
    for (int i = 0; i < M; ++i) {
        for (size_t j = 0; j < cakes.size(); ++j) {
            if (calculateScore(cakes[j], signBeauty, signTastiness, signPopularity) == scores[i]) {
                sumBeauty += cakes[j].beauty;
                sumTastiness += cakes[j].tastiness;
                sumPopularity += cakes[j].popularity;
                break;
            }
        }
    }
    return abs(sumBeauty)+abs(sumTastiness)+abs(sumPopularity);
}
int N,M;
int main(){
    cin >> N >> M;
    vector<Cake> cakes(N);
    for (int i = 0; i < N; ++i)
        cin >> cakes[i].beauty >> cakes[i].tastiness >> cakes[i].popularity;
    ll maxValue = 0;
    // 枚举8种组合方式
    for (int signBeauty = -1; signBeauty <= 1; signBeauty += 2) {
        for (int signTastiness = -1; signTastiness <= 1; signTastiness += 2) {
            for (int signPopularity = -1; signPopularity <= 1; signPopularity += 2) {
                maxValue = max(maxValue, calculateMaxAbsSum(cakes, M, signBeauty, signTastiness, signPopularity));
            }
        }
    }
    cout << maxValue <<'\n';
    return 0;// 结束 
}
```

**[AC记录](https://www.luogu.com.cn/record/195875819)**

---

## 作者：AnOIer (赞：0)

七年级数学题，~~绿是不是评高了。~~

## 思路

先考虑把绝对值符号去掉。可以发现，绝对值符号内的代数式的加减符号“相对”不改变（即将代数式中所有加减变成逆运算），代数式的结果不会改变，本题中我们可以将原数乘上 $1$ 或 $-1$ 来改变符号。这样变换一下就可以把绝对值符号去掉了，并且这样求出的结果和原来式子的结果是一样的。

最后排序求前 $m$ 大的值相加，如果计算出的和大于答案就刷新一下答案。

时间复杂度基本为 $O(n\log n)$。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1010
#define int long long
int a[maxn],b[maxn],c[maxn],sum[maxn];
int ans=-1e18;
bool cmp(int a,int b) {return a>b;}
int f(int opt) {if(opt==1) return 1;else return -1;}
signed main(){
	int n,m;	
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>a[i]>>b[i]>>c[i];
	}
	for(int i=1;i<=2;i++) {//枚举一下系数
		for(int j=1;j<=2;j++) {
			for(int k=1;k<=2;k++) {
				for(int l=1;l<=n;l++) {
					sum[l]=(a[l]*f(i))+(b[l]*f(j))+(c[l]*f(k));//计算和
				} 
				sort(sum+1,sum+1+n,cmp);//排序
				int tmp=0;
				for(int l=1;l<=m;l++) {
					tmp+=sum[l]; 
				}
				ans=max(ans,tmp); //刷新答案
			}
		}
	} 
	cout<<ans<<"\n";//记得换行
	return 0;
}

```

---

## 作者：LiSA_OLiVE (赞：0)

形式化题意题目中已经给出，这里就不再说了。
## 思路
首先，带着绝对值肯定不好算，我们最好去掉绝对值。于是我们枚举三个序列的和在绝对值时究竟是原本就大于 $0$ 没有变化，还是小于 $0$ 乘了 $-1$。这样对于三个序列每个序列有 $2$ 种情况，总共 $2^3=8$ 种情况。

然后绝对值已经去掉，我们知道了每个序列每一位的系数为 $1$ 还是 $-1$。我们就可以直接计算每一位三个序列的和，然后排序，取出和最大的 $m$ 位相加即可。最后取每一种情况的和的最大值就是答案。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[2000],b[2000],c[2000];
int h[2000];
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i]>>c[i];
	}
	int ans=0;
	for(int x=-1;x<=1;x+=2){
		for(int y=-1;y<=1;y+=2){
			for(int z=-1;z<=1;z+=2){
				for(int i=1;i<=n;i++){
					h[i]=x*a[i]+y*b[i]+z*c[i];
				}
				sort(h+1,h+1+n);
				int res=0;
				for(int i=n;i>=n-m+1;i--){
					res+=h[i];
				}
				ans=max(ans,res);
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：cly312 (赞：0)

考虑怎么去掉绝对值。分别讨论每项的正负，一共有 $2^3=8$ 种情况。

比如：我们要使 $\sum\limits_{i=1}^m a_{t_i}+\sum\limits_{i=1}^m b_{t_i}-\sum\limits_{i=1}^m c_{t_i}$ 最大，那么就对每个蛋糕，求出所有蛋糕的 $a_i+b_i-c_i$ ，降序排序，取前 $m$ 个即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
signed main(){
	cin>>n>>m;
	vector<int> x(n),y(n),z(n);
	for(int i=0;i<n;++i){
		cin>>x[i]>>y[i]>>z[i];
	}
	int ans=0;
	vector<int>sums(n);
	for(int a=-1;a<=1;a+=2){
		for(int b=-1;b<=1;b+=2){
			for(int c=-1;c<=1;c+=2){
				for(int i=0;i<n;++i){
					sums[i]=a*x[i]+b*y[i]+c*z[i];
				}
				sort(sums.begin(),sums.end(),greater());
				int sum=0;
				for(int i=0;i<m;++i){
					sum+=sums[i];
				}
				ans=max(ans,sum);
			}
		}
	}
	cout<<ans;
}
```

---

