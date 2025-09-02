# [USACO18DEC] Teamwork G

## 题目描述

在 Farmer John 最喜欢的节日里，他想要给他的朋友们赠送一些礼物。由于他并不擅长包装礼物，他想要获得他的奶牛们的帮助。你可能能够想到，奶牛们本身也不是很擅长包装礼物，而 Farmer John 即将得到这一教训。

Farmer John 的 $N$ 头奶牛（$1\le N\le 10^4$）排成一行，方便起见依次编号为 $1\dots N$。奶牛 $i$ 的包装礼物的技能水平为 $s_i$。她们的技能水平可能参差不齐，所以 FJ 决定把她的奶牛们分成小组。每一组可以包含任意不超过 $K$ 头的连续的奶牛（$1\le K\le 10^3$），并且一头奶牛不能属于多于一个小组。由于奶牛们会互相学习，这一组中每一头奶牛的技能水平会变成这一组中水平最高的奶牛的技能水平。

请帮助 FJ 求出，在他合理地安排分组的情况下，可以达到的技能水平之和的最大值。

## 说明/提示

在这个例子中，最优的方案是将前三头奶牛和后三头奶牛分别分为一组，中间的奶牛单独成为一组（注意一组的奶牛数量可以小于 $K$）。这样能够有效地将 $7$ 头奶牛的技能水平提高至 $15$、$15$、$15$、$9$、$10$、$10$、$10$，和为 $84$。

## 样例 #1

### 输入

```
7 3
1
15
7
9
2
5
10```

### 输出

```
84```

# 题解

## 作者：linyinuo2008 (赞：14)

[原题链接](https://www.luogu.com.cn/problem/P5124)

这是一道非常棒的线性动归题，其中还有一些操作小技巧。

# 1、题意理解

简化版题意：给你 $n$ 个数，让你把这 $n$ 个数分成任意组，每组中包含任意连续不超过 $k$ 个数。当一个数被分到一组中后，它会变成这组数中最大的那个，求分完后这些数和的可能最大值。

例:  

```
5 3
1
2
4
6
1
```

我们把 $ 1 $, $2$, $4$ 放一组，把 $6$ 和 $2$放一组，得到最大值为 $4 \times 3 + 6 \times 2 = 24$。

通过这个例子，应该已经理解了题意，下面就是一些要点。

- 我们要分的是这 $n$ 头奶牛，并且每组必须是连续的不超过 $k$ 头奶牛。

- 一只奶牛只能属于一组，可以理解为在奶牛序列中放上几块隔板。


# 2、动态规划求解答案

这题一看就是动态规划，并且符合无后效性的性质（~~标签上不是写着呢吗~~）。这里我摘录一段来自[这篇博客](https://blog.csdn.net/qq_25800311/article/details/90635979)的解释：

> 无后效性，有两层含义，第一层含义是，在推导后面阶段状态的时候，我们只关心前面阶段的状态值，不关心这个状态是怎么一步步推导出来的。第二层含义是，某阶段状态一旦确定，就不受之后阶段的决策影响。无后效性是一个非常“宽松”的要求。

所以动归状态很自然的就出来了。我们设 $f_i$ 表示前 $i$ 头奶牛最大的技能水平和，那么我们来研究一下 $f_i$ 可以从哪里转移过来。我们对每一只奶牛进来后最重要的是什么？是把它放在哪一组！我们要确定它的组别。

---

来个栗子。

如图，当 $k=3$ 时：

[![ggZtNq.png](https://z3.ax1x.com/2021/05/16/ggZtNq.png)](https://imgtu.com/i/ggZtNq)

新进来了一头红牛，编号为 $i$，我们把它放哪？

由于一组最多只能放三头，所以我们有三种方法：

[![ggeSbj.png](https://z3.ax1x.com/2021/05/16/ggeSbj.png)](https://imgtu.com/i/ggeSbj)

把它单独放一组，这种方案是从 $f_{i-1}$ 转移过来的。

![gbvzpn.png](https://z3.ax1x.com/2021/05/22/gbvzpn.png)

把它和前一只奶牛放一组，这种状态是从 $f_{i-2}$ 转移过来的。

[![gbx5EF.png](https://z3.ax1x.com/2021/05/22/gbx5EF.png)](https://imgtu.com/i/gbx5EF)

把它和前两只奶牛放一组，这种状态是从 $f_{i-3}$ 转移过来的。

至此，我们就完成了这只奶牛的全部状态转移，并且无法再找到新的状态，因为再往前分组就会超出 $k$ 的约束范围。

---

所以我们的最终 $f_i$ 是什么呢? 显然是从之前的 $f_{j-1}$ 转移过来的，把 $[j,i]$ 这个区间中的奶牛分为一组。但是我们别忘了还要加上这一组的效率和。这里的效率和为为 $mx \times (i-j+1)$ ，其中 $mx$ 为区间 $[j,i]$ 的最大值，意思就是这一组的效率值为这一组中的最大值乘上这一组的组员个数。

但是 $j$ 又要满足什么要求呢？显然，我们选的那一组奶牛数不能超过 $k$ ，也就是说 $[j,i]$ 这个区间长度不能超过 $k$ ，所以 $ i-k+1 \leq j \leq i$ ，但这还不够，因为最初 $i-k+1$ 可能为负数，所以左端点还要跟一取最大值，也就是说 $ \max(i-k+1,1) \leq j \leq i$。

于是我们就有了这样的代码：

```cpp 
#include <iostream>
using namespace std;
const int N=10005;
int n,k,s[N];
int f[N];
inline int max(int a,int b)
{
	return a>b?a:b;
}
int mx(int k,int l)//在[k,l]区间内取最大值
{
	int maxx=-1;
	for(int i=k;i<=l;i++) maxx=max(maxx,s[i]);		
	return maxx;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>s[i];
	f[1]=s[1];
	for(int i=2;i<=n;i++)
	{
		for(int j=max(i-k+1,1);j<=i;j++)
		{
			f[i]=max(f[i],f[j-1]+mx(j,i)*(i-j+1));//转移
		}
	}
	cout<<f[n];
    return 0;
}
```
交上去一看，**TLE $\times$ 3**。

这是为什么呢？是在这里出了问题：

```cpp
int mx(int k,int l)//在[k,l]区间内取最大值
{
	int maxx=-1;
	for(int i=k;i<=l;i++) maxx=max(maxx,s[i]);
	return maxx;
}
```
这里求区间最大值的时间是 $O(n)$ 的，这样一来总复杂度是 $O(n^3)$ ，就炸掉了。所以我们不能在求最大值上花复杂度，所以我们可以每次从 $i$ 倒着枚举到 $\max(i-k+1,1)$ 每次在转移 $f_i$ 时顺便就实现了求 $[j,i]$ 的最大值。

# 3、AC代码

代码中有注释。

```cpp
#include <iostream>
using namespace std;
const int N=10005;
int n,k,s[N];
int f[N];
/*
f[i]表示前i头奶牛最大水平和
f[i]=max(f[i],f[j-1]+mx(j,i)*(i-j+1))  (i-k+1<=j<=i) 
*/
int max(int a,int b)
{
	return a>b?a:b;
}
int main()
{
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>s[i];
	f[1]=s[1];//初始化f[1]=s[1]
	for(int i=2;i<=n;i++)
	{
		int mx=-1;//先设为-1，因为都是正数
		for(int j=i;j>=max(i-k+1,1);j--)//边界条件
		{
			mx=max(mx,s[j]);//先得把mx更新了
			f[i]=max(f[i],f[j-1]+mx*(i-j+1));//才能转移
		}
	}
	cout<<f[n];
    return 0;
}
```

**若有错误，欢迎指出！**


---

## 作者：欢黎明陌 (赞：8)

一道中等难度的 $DP$。

这道题我一开始做的时候没有看到“连续的奶牛”，导致做成了贪心，因为是错误答案，所以就不粘过来了，直接放个链接在这开始说说正确做法。

[错误做法（二分法贪心）](https://www.luogu.com.cn/paste/r7qbe3zs)

好了，以下是这道题的 $DP$ 正确思路：

既然是给他们分组，而且是找最大值，我们只需要枚举可能出现最大值的所有可能（注意是可能出现最大值的所有可能，而不是所有可能，否则会严重超时），并且随时存储更新最大值，如果嫌慢可以加个快读（一个值快写就算了吧，当然如果喜欢的话也没人拦着）。

值得注意的是，我们在每一次找完本次的最大值之后，都要初始化一下自己定义的查找最大值的变量（否则本人输出值感觉开 $long$ $long$ 都不够用）。

这道题的精髓在于，实时更新最大值，并且用此最大值去递推题目要的最大值，有一点找加权路径的路径最大值题的感觉。

下面放上标程（已 $AC$ 请放心食用）：

```cpp

#include <iostream>
#include <cstdio>
using namespace std;

int a[1001000] , ans[1001000];//数组一定要开得足够大 

inline int read(){//快读不解释 
	int x = 0 , f = 1;
	char ch = getchar();
	while( ch < '0' || ch > '9' ){
		if( ch == '-' ) f = -1;
		ch = getchar();
	}
	while( ch >= '0' && ch <= '9' ){
		 x = ( x << 1 ) + ( x << 3 ) + ( ch ^ 48 );
		 ch = getchar();
	}
	return x * f;
}

int main(int argc , char *argv[])
{
	int n , k;
	cin >> n >> k;
	for(int i = 1;i <= n;i ++) a[i] = read();//按题目要求输入 
	for(int i = 1;i <= n;i ++){
		int maxn = 0;//定义一个记录最大值的变量，本次循环的最大值，千万不要忘记初始化， 
		for(int j = i;j < min(i+k,n+1);j ++){//动态规划寻找最优解 
			maxn = max( maxn , a[j] );
			ans[j] = max( ans[j] , ans[i-1] + maxn * (j-i+1) );
		}
	}
	cout << ans[n] << endl;//因为是直接递推的，所以ans数组的最后一个元素即为答案 
	return 0;
}

```

管理大大辛苦了。

---

## 作者：Rhodoks (赞：8)

简单的动归。dp[i]代表对前i只奶牛分组得到的最大的技能水平，对每个i，枚举j，将接下来j组奶牛编为一组，更新数据。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define _ 0
using namespace std;

int dp[10010];
int a[10010];
int n,k;

int main()
{
	cin>>n>>k;
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	{
		int maxa=0;
		for (int j=i;j<min(i+k,n+1);j++)
		{
			if (a[j]>maxa)
				maxa=a[j];
			if (dp[i-1]+(j-i+1)*maxa>dp[j])
				dp[j]=dp[i-1]+(j-i+1)*maxa;
		}
	}
	cout<<dp[n];
	return ~~(0^_^0);
}


```

---

## 作者：shuiyuhan (赞：7)

 这题居然没有p的题解，那我来水一发
 
 ~~感觉这题不到蓝吧~~
 
 题目描述：长度为n的序列，可以把一段长为k的连续序列改成最大值
 
 不难想到dp
 
 用b[i]表示前i个数能达到的最大价值。
 b[i]:=max(b[j]+(i-j)*max(a[j]),b[i]) 
 而b[i]所能达到的最小值为b[i-1]+a[i],所以可以提前处理b[i]，
 但i-j可能会<=0,怎么办呢？特判一下呗
 
 代码
```pascal
uses math;//math库是个好东西
var
  n,m,i,j,k,maxx:longint;
  a,b:array[0..100005] of longint;//不管怎么说，开大点总不会错
begin
  readln(n,m);
  for i:=1 to n do read(a[i]);
  for i:=1 to n do
  begin
    maxx:=a[i];
    b[i]:=b[i-1]+a[i];
    for j:=1 to m-1 do
    begin
      if i<=j then break;//如果i<=j,那就跳过循环
        maxx:=max(maxx,a[i-j]);
        b[i]:=max(b[i-j-1]+maxx*(j+1),b[i]);//dp转移方程
    end;
  end;
  writeln(b[n]); //输出最大价值b[n]
end.
```

---

## 作者：微香玉烛暗 (赞：4)

这道题是一个动规模板，还是线性的。    
（吸引我的其实是这道题的题目）  
设$f[i]$为以第$i$头牛结尾能获得的最大值。     
设$sum$为$a[i]$~$a[j]$间的最大值          
转移是这样的：$f[i]=max(f[i],f[j-1]+sum*(i-j+1))$

上代码：
```cpp
# include <cstdio>
# include <iostream>
# include <algorithm>
using namespace std;
const int N=10005;
int n,k,a[N],f[N];

int main () {
	scanf ("%d%d",&n,&k);
	for (int i=1;i<=n;i++) scanf ("%d",&a[i]);
	for (int i=1;i<=n;i++) {
		int sum=-1e9;
		for (int j=i;i-j+1<=k&&j>=1;j--) {//这里注意一下，j不仅要保证在k个以内，还要大于等于1
			sum=max(sum,a[j]);
			f[i]=max(f[i],f[j-1]+sum*(i-j+1));
		}
	}
	printf ("%d\n",f[n]);
	return 0;
    //和上面讲的一毛一样，不放什么注释了
}
//By苍空的蓝耀

```


---

## 作者：hater (赞：2)

线段树水题

先看题目 我们只需要一维定义即可

因为题目并没有要求这要分多少组

f[ i ] 为分到第i个时最大水平和

之后我们要在 i-k 到 i 寻找断点

特殊的 如果 i-k 小于1 我们可以将它分在一组

这样子水平和最大 

之后上线段树板子维护区间极值即可

```cpp
#include<bits/stdc++.h>
#define MAXN 10005 
#define IL inline 
#define R register
#define INF 0x7f7f7f7f
using namespace std ;
int f[MAXN] , n , k , a[MAXN];
int Max[MAXN*4] ;
IL int read() {
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')  s=s*10+ch-'0',ch=getchar();
   return s*w;
}
IL int max (int A,int B) { return A>B?A:B ; }
IL int Ask(int k ,int l ,int r ,int x,int y)
{
   if(r<x || l>y) return -INF ;
   if( x<=l && r<=y ) return Max[k] ;
   int mid = l+r>>1 , res = -INF ;
   if(x <= mid) res = max( res , Ask(k<<1 , l , mid , x , y) ) ;
   if(mid < y) res = max( res , Ask(k<<1|1, mid+1 , r , x , y) ) ;
   return res ;
}
IL void build (int k ,int l ,int r)
{
   if(l == r) 
   {
	Max[k] = a[l] ;
	return ;
   }
   int mid= l+r>>1 ;
   build( k<<1 , l , mid ) ;
   build( k<<1 | 1 , mid+1 , r) ;
   Max[k] = max( Max[k<<1] , Max[k<<1 | 1] ) ;
}
int main() 
{
   n = read() ; k = read() ;
   for(R int i=1; i<=n; ++i)
      a[i] = read() ;
   build( 1 , 1 , n ) ;
   for(R int i=1 ; i<=n ; ++i)
   {
      if( i-k < 1 ) 
      {
    	  f[i] = Ask( 1 , 1, n , 1 , i) * i;
    	  continue ;
      }
      for(R int j=i-k; j<i; ++j)
         f[i] = max( f[i] , f[j]+Ask(1, 1, n ,j+1 , i)*(i-j) );
    }
    printf ( "%d\n" , f[n] ) ;
    return 0; 
}
```
之后你会发现被卡了一个点 

此时我们需要那句神奇的咒语

~~古娜拉黑暗之神---呜呼啦呼---黑魔变身~~


[你渴望力量吗](https://www.luogu.org/paste/r5wh627k)

---

## 作者：Unordered_OIer (赞：1)

# P5124 题解
## 题意
将已知序列分为连续若干段，每段长度不超过 $k$ 。求分段后段内**最大值 $\times$ 段长度**之和最大。

## 解答
显然 $dp$ 。

设 $f[i]$ 表示前 $i$ 头牛的分段后最大值。则有如下转移方程：
$$f[i]=f[i-k]+k \times \max\{a[j]\}\ |\ i-k+1 \leq j \leq i$$

然后写代码吧。

## Code
```cpp

//
//  by HpyX
//  Luogu5124,有坑版
//

#include <bits/stdc++.h>
using namespace std;

const int N=10009;

inline int read() { // 快读
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)) { if (ch=='-') f=-f; ch=getchar(); }
	while (isdigit(ch)) { x=(x<<1)+(x<<3)+(ch^48); ch=getchar(); }
	return x*f;
}

int n,k,a[N],f[N];

void solve_dp() {
	for (int i=1;i<=n;i++) {
		int mx=a[i]; // mx赋值为a[i]
		for (int j=i;i-j+1<k && j>1;j--) {
			mx=max(mx,a[j]); // 最大值
			f[i]=max(f[i], f[j-1]+mx*(i-j+1)); // 所有前k个分一组的情况取最大值
		}
	}
}

int main() {
	scanf("%d%d", &n, &k);
	for (int i=1;i<=n;i++) scanf("%d", a+i);
	solve_dp();
	printf("%d\n", f[n]);
	return 0;
}
```

---

## 作者：djh123 (赞：1)

看到数据范围，考虑dp求解

设 $f[i]$ 表示到了第$i$头牛，能得到的最大收益

那么答案就是$f[n]$

转移

设 $t[i]$ 表示第 $i$ 头牛的权值。

$f[i] = max\{f[i - j] + max\{t[i - j + 1] \cdots t[i]\}\}$

寻找 $t$ 的最大值可以用 ST 表实现。

复杂度 $O(nk)$

```cpp
#include <cstdio>
#include <iostream>
int f[10005];
int t[10005][20];
int log_2[10005];
int que(int l, int r) {
    int tmp = log_2[r - l + 1];
    return std::max(t[l][tmp], t[r - (1 << tmp) + 1][tmp]);
}
int main() {
    int n, k; scanf("%d %d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) scanf("%d", &t[i][0]);
    
    for(int i = 1 ; i <= 19 ; ++ i)
    for(int j = 1 ; j + (1 << i) - 1 <= n ; ++ j)
	t[j][i] = std::max(t[j][i - 1], t[j + (1 << (i - 1))][i - 1]);
	for(int i = 2 ; i <= n ; ++ i) log_2[i] = log_2[i >> 1] + 1;
	for(int i = 1 ; i <= n ; ++ i) {
		for(int j = 1 ; j <= k ; ++ j) {
			if(j > i) break;
			f[i] = std::max(f[i], f[i - j] + que(i - j + 1, i) * j);
        }
    }
    printf("%d\n", f[n]);
}
```

---

## 作者：SymphonyOfEuler (赞：1)

一道动态规划题。

先求所有牛能力的最大值。

$dp[i]$ 表示 $1...i$ 得到最大值。

再枚举$j$，则 $dp[i]=max(dp[i],dp[j-1]+max(s_1...s_n)*(i-j+1))$。

```
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 100005;

int dp[MAXN], s[MAXN];

int n, k;

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }
    for (int i = 1; i <= n; ++i) {
        int maxn = -0x3f3f3f3f;
        for (int j = i; j >= max(1, i - k + 1); --j) {
            maxn = max(maxn, s[j]);//求出最好的
            dp[i] = max(dp[i], dp[j - 1] + maxn * (i - j + 1));//动态转移
        }
    }
    cout << dp[n] << '\n';//输出在第n位
    return 0;
}
```


---

## 作者：cqbz_luoyiran (赞：0)

**[题目描述](https://www.luogu.com.cn/problem/P5124)**

一次模拟赛的T2,自认为是一道很简单的DP题目，考场上花了3min看题，5min想DP状态转移方程式，5min打出，0s过样例，5min构数据查错，一共二十分钟就过了这道题。

## 分析

一道很水的线性动态规划，设$dp[i]$表示前i个人最多能得到的技能水平之和，他对$dp[min(i + k,n)]$这个之前的有影响，而后面的又由后面$k(j<=n)$个的最大值得到，于是他就可以得到一个十分简单的状态转移方程
$$f[j]=max(f[j],f[i]+sum*(j-i))$$
当动态规划题目写出来了状态转移方程式，接下来还不简单吗？直接狂撸代码，反正代码量都只有这么小了。。。
先外层循环枚举结尾，循环0-n(1-n)也行，就多在外面加个初始状态就可以了)。内层循环枚举后面会影响的从$i$到$min(n,i + k)$，一边存当前访问的最大值，一边更新当前的dp值，最后输出dp[n]，也就是1-n全部的技术值，时间复杂度$O(nk)$，也是~~快的飞起~~，代码十分短。

## **code**

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1e4 + 5;
int n,k,a[MAXN],dp[MAXN];
int main() {
	freopen("worker.in","r",stdin);
	freopen("worker.out","w",stdout);
	scanf("%d %d",&n,&k);
	for(int i = 1;i <= n;i ++)
	scanf("%d",&a[i]);
	for(int i = 0;i <= n;i ++) {
		int maxx = 0;
		for(int j = i + 1;j <= min(i + k,n + 1);j ++) {
			maxx = max(maxx,a[j]);
			dp[j] = max(dp[j],dp[i] + maxx * (j - i));
		}
	}
	printf("%d",dp[n]);
	return 0;
}
```

---

## 作者：nomonick (赞：0)

这居然是到蓝题

# 题解 P5124 【[USACO18DEC]Teamwork G】

[P5124 [USACO18DEC]Teamwork G](https://www.luogu.com.cn/problem/P5124)

很简单的 $dp$ 题目，读清楚题目就可以很快地推出这道题目的方程。

其实根本不用维护区间最大值，反正在转移的时候也会逐位考虑转移，于是直接暴力取 $\max$ 即可，方程如下：

$$
dp[j] = \max(dp[j],dp[i-1]+(j-i+1)\times maxn);
$$

直接 $n \times k$ 次暴力的转移就可以
# code

```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1e4 + 50;
const int inf = 1e9 + 50;

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9')
	{
		f = (ch == '-' ? -1 : 1);
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9')
	{
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return f * x;
}

int n,k;
int num[SIZE],dp[SIZE];

int main()
{
	n = read();k = read();
	for (int i = 1; i <= n; ++i)
	{
		num[i] = read();
	}
	for (int i = 1; i <= n; ++i)
	{
		int limit = min(i+k,n+1),maxn = 0;
		for (int j = i; j < limit; ++j)
		{
			maxn = max(maxn,num[j]);
			dp[j] = max(dp[j],dp[i-1]+(j-i+1)*maxn);
		}
	}
	printf("%d\n",dp[n]);
	return 0;
}
```

---

## 作者：KSToki (赞：0)

~~中考过后做的第一道题，当然要发个题解庆祝一下~~
# 题目大意
给出$n$个技能水平，将其分成若干组，每组不超过$k$个，使得每组中最大值与~~人~~牛数之积的和最大。
# 题目分析
这是一个dp题，我们设$dp_i$表示前$i$头奶牛的技能水平之和的最大值，那么对于每个$dp_i$，枚举前$min(i,k)$个数作为新的分组点，计算该情况的结果。

如果初始技能水平为$a_i$，那么我们的动态转移方程式就为：$dp[i]=max(dp[i-(j=1...min(i,k))]+max(a[(i-j)...i])\times j)$

如果对于每个$max$都去枚举的话，时间复杂度会达到$O(nk^2)$，显然会超时。这里很容易就想到用一个数据结构来预处理一下每个区间里的$max$。如果使用线段树，时间复杂度为$O(nklogn)$，提交后还是会TLE。由于是静态的，我们用一个ST表维护即可，预处理$O(nlogn)$，每次查询$O(1)$，所以时间复杂度为$O(nk)$，可以通过。
# 代码
重头戏啦。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[10001],Log[10001],Max[10001][15],dp[10001];
inline int query(int l,int r)//查询，其实可以不用写个函数。。。
{
	int s=Log[r-l+1];
	return max(Max[l][s],Max[r-(1<<s)+1][s]);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;++i)
	    scanf("%d",&a[i]);
	Log[0]=-1;
	for(register int i=1;i<=n;++i)
	{
		Max[i][0]=a[i];
		Log[i]=Log[i>>1]+1;
	}
	for(register int j=1;j<=14;++j)
	    for(register int i=1;i+(1<<j)-1<=n;++i)
	        Max[i][j]=max(Max[i][j-1],Max[i+(1<<j-1)][j-1]);//ST表预处理
	for(register int i=1;i<=n;++i)
	    for(register int j=1;j<=min(i,k);++j)
	        dp[i]=max(dp[i],dp[i-j]+query(i-j+1,i)*j);
	printf("%d\n",dp[n]);
	return 0;
}
```


---

## 作者：zmxqs (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P5124)

分析一下题目的要求：

+ 把$n$个数分成$k$组，使得每组的最大值的和最大

+ 求这个和

拿到这道题，我的第一印象就是 数据结构 $or$ 动态规划

这道题用线段树来写的话代码会十分复杂，而且复杂度很差

所以就可以用动态规划来解决了

不难推出状态转移方程，感觉难度不是很高

$dp_{i}$表示以第$i$头奶牛结尾的最大价值

则$dp_{i}=Max(dp_{i},MaxV(a_{i}~a_{j})*(i-j+1)+dp_{i})$

其中的$MaxV$表示区间$[a_i,a_j]$的最大值

用一个变量$sum$来保存区间$[a_i,a_j]$的最大和
~~（当然你用线段树也没事，纯属装$X$）~~

## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
/*
template<typename T> void read(T &x) {
	T s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') w=-1; c=getchar();}
	while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
	x=s*w;
}
*/
unsigned long long read() {
	unsigned long long s=0,w=1;
	char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') w=-1; c=getchar();}
	while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
	return s*w;
}
int n,k;
int a[10100],dp[10100];

int main() {
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;++i) {
		int sum = INT_MIN ; 
		for(int j=i;i-j+1 <= k && j >= 1; --j) {
			sum = Max(sum,a[j]);
			dp[i] = Max(dp[i],dp[j-1]+sum*(i-j+1));
		}
	}
	printf("%d",dp[n]);
	return 0;
}
```

---

## 作者：fsq0726 (赞：0)

有一个长度为$n$的序列 $a$ $,$ 每次可以将附近连续几个比自己小的数变为自己 $,$ 求最大技能水平和。

**不难想到是动态规划!**

令 $dp[i]$ 为前 $i$ 头奶牛可以达到的技能水平之和的最大值 $,$ 可列出转移方程：

$dp[i]=max(dp[j]+(i-j)*max(a[j]))$
   
其中$(max(0,i-k)≤j<i)$

上代码：

```cpp
#include <bits/stdc++.h> 
using namespace std;
const int MAXN=1e4+7;
int n,k,Max;
int dp[MAXN],s[MAXN];
int main() {
	scanf("%d%d",&n,&k);
	for (int i=1; i<=n; i++)
		scanf("%d",&s[i]);
	for (int i=1; i<=n; i++) {
		Max=s[i];
		dp[i]=dp[i-1]+s[i];
		for (int j=1; j<k; j++)
			if (i-j>0) {
				Max=max(Max,s[i-j]);
				dp[i]=max(dp[i-j-1]+Max*(j+1),dp[i]);
			} else break;
	}
	printf("%d\n",dp[n]); 
	return 0;
}

```





---

## 作者：jun君 (赞：0)

**题目大概：** 一个数组：a[1]、a[2]……a[n-1]、a[n],一个数可以把附近连续几个比自己小的数更为自己，所以第一想到:
## 贪心! ! ! 
求区间最大值，接着不难想到用**动态规划**

数组f[i]：表示前i个数能得的最大值，f[i]=f[i-j]+max{a[i-j+1]、a[i-j+2]……}*(i-j)
$\color{red}{(1<=j<=k)}$

代码如下：
```cpp
#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;
const int N=10000+10;
int n,k,ans[N],mx,a[N];
int main()
{
	cin>>n>>k;
	for (int i=1;i<=n;i++)scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	{
		ans[i]=a[i];
		mx=a[i];//最大值初始化
		for (int j=i-1;(j>=0&&j>=i-k);j--)
		{
		    ans[i]=max(ans[j]+mx*(i-j),ans[i]);//即上面的动态方程
			mx=max(mx,a[j]);//更新最大值
		}
	}
	cout<<ans[n]<<endl;
	return 0;
}

```

---

## 作者：ustze (赞：0)

这应该是gold中最简单的一题吧。。  
定义$f[i]$为前i头奶牛可以达到的技能水平之和的最大值  
那么我们可以列出状态转移方程$$f[i]=max(f[j]+(i-j)*max(a[j]))$$ 
其中$(max(0,i-k)\leq j<i) $  
具体还是见代码吧  
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=10005;
int n,k;
ll a[N],f[N];
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++){
        ll mx=a[i];
        for(int j=i-1;j>=0&&j>=i-k;j--){
            mx=max(mx,a[j+1]);
            f[i]=max(f[i],f[j]+mx*(i-j));
        }
    }
    cout<<f[n];
    return 0;
}
```

---

## 作者：da32s1da (赞：0)

考虑DP求解。

我们令$g[i]$为划分好前$i$个的最大技能水平和。

有$g[i]=\max(g[j]+max(a_{j+1}...a_{i}))$。

时间复杂度$O(knlog_2n)$

~~可能需要开O2~~
```
#include<cstdio>
const int N=1e4+50;
int g[N];
int n,k,x,ans;
inline int max(int u,int v){return u>v?u:v;}
int tre[N<<3];
void mktree(int now,int ls,int rs){
	if(ls==rs){
		scanf("%d",&tre[now]);
		return;
	}
	int noww=now<<1,nrs=ls+rs>>1;
	mktree(noww,ls,nrs);
	mktree(noww|1,nrs+1,rs);
	tre[now]=max(tre[noww],tre[noww|1]);
}
int gmax(int now,int ls,int rs,int zuo,int you){
	if(ls>you||rs<zuo)return 0;
	if(ls>=zuo&&rs<=you)return tre[now];
	int noww=now<<1,nrs=ls+rs>>1;
	return max(gmax(noww,ls,nrs,zuo,you),gmax(noww|1,nrs+1,rs,zuo,you));
}
int main(){
	scanf("%d%d",&n,&k);
	mktree(1,1,n);
	for(int i=1;i<=n;i++){
		for(int j=max(0,i-k);j<i;j++)
		g[i]=max(g[i],g[j]+(i-j)*gmax(1,1,n,j+1,i));
	}
	printf("%d\n",g[n]);
} 
```

---

