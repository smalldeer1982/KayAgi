# Checkpoints

## 题目描述

数轴上有 $n$ 个点，分别编号为 $1, 2, ..., n $。你初始位置在 $a$ ，要经过其中的 $n-1$ 个点，求最小总行走距离。

## 样例 #1

### 输入

```
3 10
1 7 12
```

### 输出

```
7
```

## 样例 #2

### 输入

```
2 0
11 -10
```

### 输出

```
10
```

## 样例 #3

### 输入

```
5 0
0 0 1000 0 0
```

### 输出

```
0
```

# 题解

## 作者：taotiehai_AFO (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF709B)

## 题目简述
给定 $N$ 个数字 $n_1,n_2 \cdots n_N$ 和初始位置 $a$，必须经过 $N-1$ 个点。求**最短**的路径。
## 分析
~~我第一眼居然认为要用最短路~~

这道题暴力的时间复杂度是 $O(n^2)$，所以不能打暴力，而是要分析。

首先我们注意到必须经过 $N-1$ 个点。


那么，只有两种情况：不经过 $n_1$ 或是 $n_N$。

当进行第①种情况，则又分了几种情况:
1. $a \ge n_N$
1. $n_2 \le a \le n_N$
1. $a \le n_2$

对于第一种情况，我们直接计算 $a-n_2$ 的值，对于第二种情况，我们计算 $\min(a-n_2,n_N-a)+n_N-n_2$，对于第三种情况，我们计算 $n_N-a$ 的值。对这几个值进行综合取得
$$ans_1=\min(|n_N-a|+n_N-n_2,|n_2-a|+n_N-n_2)$$
同理我们可以推出第②种情况的公式
$$ans_2=\min(|n_{N-1}-a|+n_{N-1}-n_1,|n_1-a|+n_{N-1}-n_1)$$
最后
$$ans=\min(\min(|n_N-a|+n_N-n_2,|n_2-a|+n_N-n_2),\min(|n_{N-1}-a|+n_{N-1}-n_1,|n_1-a|+n_{N-1}-n_1))$$
最后注意 $N=1$ 时的特判就行了。空间和时间复杂度均为 $O(n)$，不会爆。
## AC Code
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
int n[100005];
signed main()
{
	int N,a;
	cin>>N>>a;
   if(N==1)
   {
      cout<<0;
      return 0;
   }
	for(int i=0;i<N;i++) scanf("%d",&n[i]);
	sort(n,n+N);
	cout<<min(min(abs(n[N-1]-a)+n[N-1]-n[1],abs(n[1]-a)+n[N-1]-n[1]),
	min(abs(n[N-2]-a)+n[N-2]-n[0],abs(n[0]-a)+n[N-2]-n[0]));
    //如前描述，但下标从0开始，故全部都需要改
	return 0;
}
```


---

## 作者：wangqinyan (赞：1)

这题思路与代码实现其实都很简单。

# **题目思路**

这道题就是一道非常简单的贪心。因为要在 $n$ 个点中，只有一个点不选，而要求最小总行走距离。因此，不选的点只有两种情况可能可以做到最优。第一种就是不选第 $1$ 个点。第二种就是不选第 $n$ 个点。那我们只要分别考虑这两种情况后，再取 ``min`` 即可。同时，这两种情况中，又分别要考虑两种取法，再从中取最优解。第一种，先走到要取的最靠左的点。第二种，先走到要取的最靠右的点。这样这题就做好了。可能我说的比较抽象，可以结合代码理解。

# **注意点**

当 $n$ 为 $1$ 时，不需要选点 ~~不然选零个点咋做啊~~ 直接输出 $0$ 即可。

# **代码**
```
#include<bits/stdc++.h>
using namespace std;
long long n,x,a[100100],mina,minb;
int main()
{
//    freopen(".in","r",stdin);
//    freopen(".out","w",stdout);
	cin>>n>>x;
	if(n==1)
	{
		cout<<0;
		return 0;
	}
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);
	mina=min((abs(x-a[2])+abs(a[n]-a[2])),(abs(x-a[n])+abs(a[n]-a[2])));
	minb=min((abs(x-a[1])+abs(a[n-1]-a[1])),(abs(x-a[n-1])+abs(a[n-1]-a[1])));
	cout<<min(mina,minb);
//    fclose(stdin);
//    fclose(stdout);
	return 0;
}

```
感谢观看！

---

## 作者：So_noSlack (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/CF709B)&[CF 链接](http://codeforces.com/problemset/problem/709/B)

本篇题解为此题**较简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给定 $N$ 个点，在一条数轴上，位置为 $x_1,…,x_n$，你的位置为 $p$，你要经过 $N-1$ 个点，求**至少**要走的距离。

## 思路

首先因为输入是**乱序**的，所以需要**由小到大排序**。

又因为需要经过 $N-1$ 个点，所以要么不走**左端点**，要么不走**右端点**，这样分两种情况讨论，分别求出答案取 $\min$ 即可。

首先分析情况 $1$，要么 $p \le a_2 \le a_n$，要么 $a_2 \le p \le a_n$，要么 $a_2 \le a_n \le p$，**第二种不论先去 $a_2$ 还是 $a_n$ 结果都一样。所以不讨论**，第一三种需要讨论一下，对于第一种**一定是先去** $a_2$ 结果最小， 对于第三种**一定是先去** $a_n$ 结果最小，只需对这两种分别处理最后取 $\min$ 即可，由此分析可得这种情况的**方程式**为：

$$\min( | a_n - p | + | a_n - a_2 |, | a_2 - p | + | a_n - a_2 | )$$

同样分析可得情况 $2$ 的**方程式**：

$$\min( | a_{n - 1} - p | + | a_{n - 1} - a_1 |, | a_1 - p | + | a_{n - 1} - a_1 | )$$

最后对两种情况取 $\min$ 即可。

经过以上分析，很容易即可得出**代码**了：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

int n, a[100005], p;
long long ans = 0x3f3f3f3f; // 要取 min 所以需初始化一个较大数

int min(int x, int y) { return (x < y) ? x : y; }

int abs(int x) { return (x > 0) ? x : -x; }

int main(){
	cin >> n >> p;
	if(n == 1) { cout << "0\n"; return 0; } // 特判
	for(int i = 1; i <= n; i ++) cin >> a[i];
	sort(a + 1, a + n + 1); // 因为是乱序，所以需要排序
	long long num1 = 0, num2 = 0; // 可不开 long long
	// 情况 1
  	num1 = min(abs(a[n] - p) + abs(a[n] - a[2]), abs(a[2] - p) + abs(a[n] - a[2]));
  	// 情况 2
	num2 = min(abs(a[n - 1] - p) + abs(a[n - 1] - a[1]), abs(a[1] - p) + abs(a[n - 1] - a[1]));
	ans = min(num1, num2); // 答案取 min
	cout << ans << endl; // 输出，换行好习惯
	return 0;
}

```

提交记录：

![SonoSlack](https://cdn.luogu.com.cn/upload/image_hosting/g5vfxfzv.png)

$$\text{The End!}$$

---

## 作者：Colead (赞：1)

简单的思维逻辑题。

只有一个点不选，那就要么左端点，要么右端点。

那么走路的范围也就确定了，再想一想向左走还是向右走就好了。

只有一个坑点就是 $n=1$ 的时候是无解的，输出 $0$ 就行了。

部分code：

```
        cin>>n>>a;
	if(n==1)
	{
		cout<<"0"<<endl;
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>p[i];
	}
	sort(p+1,p+n+1);
	long long ans1=min(abs(p[n]-a)+abs(p[n]-p[2]),abs(p[2]-a)+abs(p[n]-p[2]));
	long long ans2=min(abs(p[1]-a)+abs(p[n-1]-p[1]),abs(p[n-1]-a)+abs(p[1]-p[n-1]));
	cout<<min(ans1,ans2)<<endl;
	return 0;
```


---

## 作者：The_jester_from_Lst (赞：0)

简易思维题 ~~（CF 是对思维题有什么执念吗）~~ 。

既然经过 $n-1$ 个点，容易想到要么最左端不走，要么最右端不走。设 $ans$ 为答案。

则对于最左端不走的情况，有两种方案：

1. 先走到第 $n$ 个点，再走到第 $2$ 个点，有计算方法：
$$ans=a_n-a_2+a_n-m$$

2. 先走到第 $2$ 个点，再走到第 $n$ 个点，有计算方法：
$$ans=a_n-a_2+a_2-m$$

对于最右端不走，也有两种方案：

1. 先走到第 $1$ 个点，再走到第 $n-1$ 个点，有计算方法：
$$ans=a_{n-1}-a_1+a_1-m$$

2. 先走到第 $n-1$ 个点，再走到第 $1$ 个点，有计算方法：
$$ans=a_{n-1}-a_1+a_{n-1}-m$$ 

将以上四种情况，取最小值即可。

**注意：**

1. 对于以上四个公式，绝对值不能省！（$m$ 有可能大于 $a_n$ 或小于 $a_1$）

2. 一开始时需要特判 $n$ 为 $1$，不判的话你会 $WA$ 在第四十二个点

附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define mod 1000000007
using namespace std;
il int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
il void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
il int min(int x,int y){return (x<=y)?x:y;}
il int max(int x,int y){return (x>y)?x:y;}
int n,m,a[100086];
namespace man{
	il void what_can_i_say(){
		n=rd();m=rd();
		if(n==1){
			putchar('0');
			return;
		}
		for(int i=1;i<=n;++i)a[i]=rd();
		sort(a+1,a+1+n);
		int ans;
		ans=min(a[n-1]-a[1]+abs(a[n-1]-m),a[n-1]-a[1]+abs(m-a[1]));
		ans=min(ans,min(a[n]-a[2]+abs(m-a[2]),a[n]-a[2]+abs(a[n]-m)));
		wr(ans);
	}
}
signed main(){
	man::what_can_i_say();
    return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

考虑贪心，具体过程如下。

- 把 $a$ 加入 $x$。
- 将 $x$ 排序。
- 分两种情况：不走最左边的点、不走最右边的点。对它们分别计算，方法像[宝箱](https://www.luogu.com.cn/problem/P9581)这一题。
- 特殊情况：最左边的点是 $a$，不考虑；最右边的点是 $a$，也不考虑。当 $n=1$，答案为 $0$。
- 原因：如果不走中间的点，如样例一，不走 $7$，最佳答案也为 $13$（$10$ 到 $12$ 再到 $1$），很明显大于正确答案。不走边上的点，才有可能找到最优解。


### $\color{#74abab}\text{AC Code}$
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO {
	inline int r() {
		int z=1,y=0;
		char t=getchar();
		while(t<'0'||t>'9') {
			if(t=='-')z=-1;
			t=getchar();
		}
		while(t<='9'&&t>='0') {
			y=(y<<1)+(y<<3)+(t^48);
			t=getchar();
		}
		return z*y;
	}
	inline void w_(int x) {
		if(x<0) {
			x=-x;
			putchar('-');
		}
		if(x==0)return;
		w_(x/10);
		putchar(x%10+48);
	}
	inline void w(int x) {
		if(x==0)putchar('0');
		else w_(x);
	}
}
using namespace IO;
namespace D1n0 {
	int n,a,t[105000],Ans=1145141919810;
	inline int sl(int l,int r) {
		int a1=a-t[l],a2=t[r]-a;
		return min(a1,a2)*2+max(a1,a2);
	}
	inline void _() {
		n=r(),a=r();
		for(int i=1; i<=n; ++i)t[i]=r();
		t[++n]=a;
		sort(t+1,t+1+n);
		if(t[1]!=a)Ans=min(Ans,sl(2,n));
		if(t[n]!=a)Ans=min(Ans,sl(1,n-1));
		if(Ans<INT_MAX)w(Ans);
		else w(0);
	}
}
signed main() {
	D1n0::_();
}
```

---

## 作者：Bpds1110 (赞：0)

当 $n = 1$，直接输出 $0$。

要在 $n$ 个点中经过 $n - 1$ 个，发现只能不经过下标为 $1$ 或 $n$ 的。假设经过 $[1, n]$，则必须经过 $[1, n]$ 中的所有点，不满足经过 $n - 1$ 个点。

所以，只要考虑经过 $[2, n]$ 或 $[1, n - 1]$ 这两个区间即可。注意每种区间有两种可能性，分别是先走到左端点，和先走到右端点。

---

## 作者：fmdd_szx (赞：0)

[原题](https://www.luogu.com.cn/problem/CF709B)
# 题意

数轴上有 $n$ 个点。初始位置在 $x$，要经过其中的 $n-1$ 个点，求最小总行走距离。

# 思路

既然经过 $n-1$ 个点，因此要么只走左端点，要么只走右端点，就会有四种情况：

- $1∼n-1$
- $n-1∼1$
- $2∼n$
- $n∼2$

答案求最小即可。

有个坑点是当 $n=1$ 时，无解，输出 $0$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,i,s1,s2,a[100001];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>x;
	if(n==1) return cout<<0,0;//特判
	for(i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	s1=min(abs(x-a[n])+abs(a[n]-a[2]),abs(x-a[2])+abs(a[2]-a[n]));//只走右端点
	s2=min(abs(x-a[1])+abs(a[1]-a[n-1]),abs(x-a[n-1])+abs(a[n-1]-a[1]));//只走左端点
	cout<<min(s1,s2);
	return 0;
}
```


---

## 作者：xxxr_2024 (赞：0)

# CF709B Checkpoints 题解
构造题，题意翻译说的挺清楚的了。
## 分析
会发现题目一共给了你 $n$ 个点，却让你经过 $n-1$ 个点，你就不好奇那少的一个点是啥吗？

用脑子好好想想，如果没有少的这一个点，明显是先走到最左端在走到最右端是最优的。那减少的一个点就可以是左端点或右端点，你走路会有四种情况：$1\sim n-1,n-1\sim 1,2\sim n,n\sim 2$，输出四种情况取 $\min$ 即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Raiden
{
    const int N=1e5+5;
    int x[N];
    signed work()
    {
        int n,a;
        while(cin>>n>>a)
        {
            for(int i=1;i<=n;i++)
            {
                cin>>x[i];
            }
            sort(x+1,x+n+1);
            if(n==1)
            {
                cout<<0<<endl;
                continue;
            }
            cout<<min({abs(x[1]-a)+x[n-1]-x[1],abs(x[2]-a)+x[n]-x[2],abs(x[n-1]-a)+x[n-1]-x[1],abs(x[n]-a)+x[n]-x[2]});
        }
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    return Raiden::work();
}
```

---

## 作者：2012zxt (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF709B)

## 1.思路

本题是一道思维题。

我们先来分析，发现先走到最左边或者最右边再折返是最好的方法，其他方法重复的地方都比这样多。

再发现可以删除一个点，最优方法只有可能是在删左端点和右端点之间选择一种。

于是这样代码就出来了。

写代码的时候可以把所有情况分为两类，一类是一开始向左走的，另一种是向右走的，接着再把它分为删除左端点和删除右端点两种选择。

## 2.坑点
如果你 wa on #45 ——
要注意考虑只有一个点的情况，那就不需要走，输出 0。

## 3.代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,x[100005],mini=1e9;
int main(){
	cin>>n>>a;
	for(int i=1;i<=n;i++)
		cin>>x[i];
	if(n==1){//如上特判
		cout<<0;
		return 0;
	}
	sort(x+1,x+1+n);
   mini=min(mini,min(abs(x[n]-a)+abs(x[n]-x[2]),abs(x[n-1]-a)+abs(x[n-1]-x[1])));//先向右走
	mini=min(mini,min(abs(a-x[2])+abs(x[n]-x[2]),abs(a-x[1])+abs(x[n-1]-x[1])));//向左走
	cout<<mini;
	return 0;
}

```

---

## 作者：cosf (赞：0)

[**CF709B Checkpoints**](https://www.luogu.com.cn/problem/CF709B)

---

## 题目描述

给你 $N$ 个点，在一条数轴上，位置为 $x_1,\dots,x_n$，你的位置为 $a$，你要经过 $N-1$ 个点，求你最少要走多远？

---

## 思路

我们先给 $x_i$ 排个序（即后文中 $x_1<x_2<\dots<x_n$）。

**如果**你需要经过 $N$ 个点，那么你至少要走 $x_n-x_1$ 长度。**如果**你不经过的那个点*不是* $x_1$ 或 $x_n$，则你还是必须要走 $x_n-x_1$ 长度。**则如果**你不经过的点是 $x_1$ 或 $x_n$，你必须要走的路程就是 $x_n-x_2$ 或 $x_{n-1}-x_1<x_n-x_1$。

接下来就是代码了：

### AC Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    int n, a;
    cin >> n >> a;
    if (n == 1) // 需要特判，否则会报错（为什么自己想）
    {
        cout << 0 << endl;
        return 0;
    }
    int x[100005];
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    sort(x + 1, x + n + 1);
    int res = min(
      x[n] - x[2] + min(abs(a - x[2]), abs(x[n] - a)),
      x[n - 1] - x[1] + min(abs(a - x[1]), abs(x[n - 1] - a))
    );// 重点
    cout << res << endl;
    return 0;
}

```



---

## 作者：Jerrycyx (赞：0)

## 解析

在该题目中，经过其中 $n-1$ 个点说明要**去掉一个点不走**。

要求经过 $n-1$ 个点的最小距离，**只需计算到最左边和最右边的最短距离即可**，因为只要到达这两个点，就意味着其间所有的点全部都经过了一遍，符合题意。

那么“去掉一个点不走”，需要去掉哪一个点呢？这个问题可分为两种情况：
1. 去掉最左右两点
2. 去掉它们之间的点

根据上面的推论，**只有最左右两点影响最终结果**，所以**只有去掉最左右两点才可能得到最小行走距离**，故只需要对比去掉左右那个点得到的行走距离，就能得到答案。

## 具体实现

我们可以使用变量 `right1`、`right2` 和变量 `left1`、`left2` 来分别计算点 $a$ 往右走的最大、次大距离和往左走的最大、次大距离。

这样，最后只需要计算去掉 `right1` 或去掉 `left1` 得到的答案即可。

注意，先往左走和先往右走得到的答案是不同的，故需要再次判断。

## $\texttt{\textcolor{Green}{Accepted} 代码}$

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

int n,a;
int left1,left2;	//分别是a往左第一大的距离和第二大的距离
int right1,right2;	//分别是a往右第一大的距离和第二大的距离
int ans;

int MIN(int x1,int x2,int x3,int x4)	//四个数的最小值函数 
{
	return min(min(x1,x2),min(x3,x4));
}
int main()
{
	scanf("%d%d",&n,&a);
	for(int i=1;i<=n;i++)
	{
		int tmp;
		scanf("%d",&tmp);
		if(tmp>a)	//tmp在a右边 
		{
			if(tmp-a>right1)
			{
				right2=right1;
				right1=tmp-a;
			}
			else if(tmp-a>right2)
				right2=tmp-a;
			//更新right1和right2 
		}
		if(tmp<a)	//tmp在a左边 
		{
			if(a-tmp>left1)
			{
				left2=left1;
				left1=a-tmp;
			}
			else if(a-tmp>left2)
				left2=a-tmp;
			//更新left1和left2 
		}
	}
	ans=MIN(left2*2+right1,right1*2+left2,left1*2+right2,right2*2+left1);
	//计算最最小总行走距离
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：wangml (赞：0)

## Description
 在一条数轴上有$n$个点，告诉你点的坐标，出发的位置。
 求至少走多远才能经过$n-1$个点。
## Solution
### 有如下情况
1. 起点在最左(右)端，则一路走，一共走n-1个点，则完成目标。
2. 起点在中间，则既可以向左走再回头，也可以向右走再回头。
   **机智的蒟蒻当然果断走短的一条路qwq**
而这条路可以被拆分为两部分：转向前与转向后，然后把两部分加起来。

> 用**绝对值函数**&&**最小值函数**配合起来即可用代码实现。

代码如下：


```  
#include <bits/stdc++.h>
using namespace std;  
const int inf=1e9;
const int maxn=1e5+10;
int n,m,a[maxn],ans;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);     		//输入 
    sort(a+1,a+n+1);     		// 先从小到大排序，方便确定出发点与检查点（目标点）的位置 
    if(n==1) printf("0\n");  	//只有一个点，无法完成目标 
    else 
	{
    	if(m>=a[n]) ans=m-a[2];  				//  起点在最右端 
    	else if(m<=a[1]) ans=a[n-1]-m;    		//  起点在最左端 
    	else
    	{
    		int dis1=min(abs(a[n-1]-m),abs(m-a[1]))+a[n-1]-a[1];     //向左走到 第1个点，再转向走到第n-1个点 
    		int dis2=min(abs(a[n]-m),abs(m-a[2]))+a[n]-a[2];		//向右走到 第n个点， 再转向走到第2个点 
    	    ans=min(dis1,dis2);  //取两条路的最短距离 
    	}
    	printf("%d\n",ans); //输出答案 
    }
    return 0;
}
```

---

## 作者：_Sky_Dream_ (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF709B)

题目要求经过 $n-1$ 个点，那么，有以下四种可能：

- $a_1 \to a_{n-1}$

- $a_{n-1} \to a_1$

- $a_2 \to a_n$

- $a_n \to a_2$

求最小值即可。

AC Code:
```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define itn int
#define tni int
#define tin int
#define nit int
#define nti int
#define int long long
using namespace std;
int n,a,A,B,q[100001];
void Enchanted() {
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>n>>a;
	if(n==1) {//不用经过点那还走啥呀
		cout<<0;
		exit(0);
	}
	for(int i=1; i<=n; ++i)cin>>q[i];
	sort(q+1,q+n+1);//排序
	A=min(abs(a-q[n])+abs(q[n]-q[2]),abs(a-q[2])+abs(q[2]-q[n]));
	B=min(abs(a-q[1])+abs(q[1]-q[n-1]),abs(a-q[n-1])+abs(q[n-1]-q[1]));
	cout<<min(A,B);//最小值
}
signed main() {
	Enchanted();
}


```

---

