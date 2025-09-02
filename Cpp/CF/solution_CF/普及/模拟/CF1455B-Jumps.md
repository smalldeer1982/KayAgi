# Jumps

## 题目描述

You are standing on the $ \mathit{OX} $ -axis at point $ 0 $ and you want to move to an integer point $ x > 0 $ .

You can make several jumps. Suppose you're currently at point $ y $ ( $ y $ may be negative) and jump for the $ k $ -th time. You can:

- either jump to the point $ y + k $
- or jump to the point $ y - 1 $ .

What is the minimum number of jumps you need to reach the point $ x $ ?

## 说明/提示

In the first test case $ x = 1 $ , so you need only one jump: the $ 1 $ -st jump from $ 0 $ to $ 0 + 1 = 1 $ .

In the second test case $ x = 2 $ . You need at least three jumps:

- the $ 1 $ -st jump from $ 0 $ to $ 0 + 1 = 1 $ ;
- the $ 2 $ -nd jump from $ 1 $ to $ 1 + 2 = 3 $ ;
- the $ 3 $ -rd jump from $ 3 $ to $ 3 - 1 = 2 $ ;

Two jumps are not enough because these are the only possible variants:

- the $ 1 $ -st jump as $ -1 $ and the $ 2 $ -nd one as $ -1 $ — you'll reach $ 0 -1 -1 =-2 $ ;
- the $ 1 $ -st jump as $ -1 $ and the $ 2 $ -nd one as $ +2 $ — you'll reach $ 0 -1 +2 = 1 $ ;
- the $ 1 $ -st jump as $ +1 $ and the $ 2 $ -nd one as $ -1 $ — you'll reach $ 0 +1 -1 = 0 $ ;
- the $ 1 $ -st jump as $ +1 $ and the $ 2 $ -nd one as $ +2 $ — you'll reach $ 0 +1 +2 = 3 $ ;

In the third test case, you need two jumps: the $ 1 $ -st one as $ +1 $ and the $ 2 $ -nd one as $ +2 $ , so $ 0 + 1 + 2 = 3 $ .

In the fourth test case, you need three jumps: the $ 1 $ -st one as $ -1 $ , the $ 2 $ -nd one as $ +2 $ and the $ 3 $ -rd one as $ +3 $ , so $ 0 - 1 + 2 + 3 = 4 $ .

## 样例 #1

### 输入

```
5
1
2
3
4
5```

### 输出

```
1
3
2
3
4```

# 题解

## 作者：Allanljx (赞：15)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1455B)

[CF传送门](http://codeforces.com/problemset/problem/1455/B)
## 题意
你在坐标为$0$的的地方，你可以往前走 $k$ 个单位，也可以往回退一个单位，问最少操作几次可使你所在的坐标等于 $n$ 。 $k$ 是操作次数。
## 思路
一直执行操作一，直到坐标大于等于 $n$ ，因为这样，可以通过将一次操作改为坐标减一来得到 $n$ ，但是要注意坐标不能等于 $n+1$ ，因为这样只能在后面进行一次减一操作，不能通过更改已有的操作一得到 $n$ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t;
int main()
{
	cin>>t;
	while(t--) //多组数据
	{
		cin>>n;
		int s=0,i;
		for(i=0;s<n||s==n+1;s+=++i){}//枚举和大于n
		cout<<i<<endl;
	}
	return 0;
}
```


---

## 作者：mcqueen (赞：10)

观察到数据范围只有 $10^6$ ，而且输入输出的形式为“给定一个数，输出一个数”，所以自然想到打表找规律。

那么我们可以用 BFS 来模拟题目“跳”的过程。代码如下：

```cpp
#include<bits/stdc++.h>
#define N 1000005
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
queue<pii> q;
int dis[N];
int main()
{
	memset(dis,-1,sizeof(dis));
	dis[N]=0;
	q.push(mp(0,1));
	while(!q.empty())
	{
		int from=q.front().fi,k=q.front().se;
		if(from>0&&dis[from]==-1)dis[from]=k-1;
		q.pop();
		if(k==20)break;//不能让 BFS 一直搜下去，搜到一定程度就把表打出来看看。
		q.push(mp(from+k,k+1));
		q.push(mp(from-1,k+1));
	}
	for(int i=1;i<=30;++i)cout<<dis[i]<<endl;
	return 0;
}
```
打出的表：

![](https://cdn.luogu.com.cn/upload/image_hosting/optgmief.png)

观察一下就能找到规律。具体如下：

`1 3 2`（前三个直接特判掉）  
`3 4 3`  
`4 4 5 4`  
`5 5 5 6 5`  
`6 6 6 6 7 6`  
`7 7 7 7 7 8 7`  
……

这个规律想必大家都能看出来把。

由于数据范围只有 $10^6$ ，所以我们可以通过这个规律 $O(n)$ 预处理出一个表。那么对于每个询问，直接查表输出就行了。

AC代码：
```cpp
#include<bits/stdc++.h>
#define N 1000005
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
using namespace std;
template<typename T>
inline void in(T &x)
{
	x=0;
	char c=getchar();
	bool fu=0;
	while(c<'0'||c>'9'){if(c=='-')fu=1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	x=fu?-x:x;
}
int dis[N];
void init()
{
	dis[1]=1;
	dis[2]=3;
	dis[3]=2;
	int i=4,step=1,j=3;
	while(i<=1000000)
	{
		for(int k=0;k<step;++k)
		{
			dis[i]=j;
			if(i==1000000)return;
			++i;
		}
		dis[i]=j+1;
		++i;if(i==1000000)return;
		dis[i]=j;if(i==1000000)return;
		++i;
		++step;
		++j;
	}
}
int main()
{
	init();
	int T;
	in(T);
	while(T--)
	{
		int x;
		in(x);
		printf("%d\n",dis[x]);
	}
	return 0;
}
```
如果您想知道这样这题的正常解法，您还是去 CF 上看官方题解或者看洛谷上的其他题解吧。不过我们始终要记得，在遇到不会做的题时，不要放弃，要尝试打个暴力打个表来找找规律，万一规律找到了把题目 AC 了呢？

---

## 作者：TEoS (赞：9)

本文同步发表在[我的blog](https://www.cnblogs.com/TEoS/p/14074708.html)


------------


先假设全部执行第一种操作，然后把其中几个操作改为第二次操作。那么在第 $k$ 次执行的第二种操作就是走 $-k-1$ 。

显然我们应该先用第一次操作走过 $x$ 后再改其中的几个操作往回走。设最开始先走 $p$ 次第一种操作，则 $p$ 应该为最小的满足 $\frac{p(p+1)}{2}\geq x$ 的 $p$ 。通过枚举可以找到这个 $p$ 。然后我们需要往回走 $\frac{p(p+1)}{2}-x$ 步。

通过把第一种操作改成第二种操作可以往回走的步数范围显然为 $[2,p+1]$ ，而显然有 $\frac{p(p+1)}{2}-x\in[0,p-1]$ 。可以发现，步数为 $[2,p-1]$ 的情况都可以通过把一个第一种操作改成第二种操作来实现，步数即为 $p$ ；而相差 $0$ 步显然不用走；只有相差 $1$ 步的情况需要多执行一次第二种操作，此时答案为 $p+1$ 。

综上，先枚举到最小满足 $\frac{p(p+1)}{2}\geq x$ 的 $p$ ，然后判断 $\frac{p(p+1)}{2}-x$ 是否为 $1$ ，若为 $1$ 则答案为 $p+1$ ，否则为 $p$ 。

```c++
#include<iostream>
#include<cstdio>
using namespace std;
int T,n,p;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(p=1;p*(p+1)<n*2;p++);//暴力枚举
		printf("%d\n",p+(p*(p+1)/2-n==1));//特判输出
	}
	return 0;
}
```



---

## 作者：小蒟蒻皮皮鱼 (赞：1)

设 $s[i]$ 表示 $1+2+...+i$ 。

这道题如果没有操作二，就是找到最小的 $s[i]> x$ ，然后输出 $i + s[i] - x$ 。

考虑操作二的本质，发现如果在位置 $j$ 进行了一次操作二实质上是把 $s[i]$ 减去了$j +1$ 。因为原本在位置 $j$ 应当进行 $+j$ 的操作，但是现在却进行了 $-1$ 的操作。

那么假设对于当前的 $i$ 来说，有这样的 $j$ 使得$s[i] - (j +1)=x$ ，则可以通过 $i$ 次操作到达点 $x$ 。

否则，就一定会在 $i+1$ 步走到 $x$ 。

答案再对没有操作二的取 $\min$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
int T;
int x, k, ans;
int s[10005];
int main()
{
	scanf("%d", &T);
	for(int i = 1; i < 10005 && (1 + k) * k / 2 < N; i ++)
		s[i] = s[i - 1] + i;
	while(T --)
	{
		ans = 999999999;
		scanf("%d", &x);
		int a = lower_bound(s + 1, s + 1 + 10005, x) - s;
		int b = s[a] - x;
		if(b == 0) ans = a;
		if(b != 0) 
		{
			int k = b - 1;
			if(k != 0) ans = min(ans, a);
			else if(k == 0) ans = min(ans, a + 1);
		}
		printf("%d\n", ans);
	}
}

```



---

## 作者：_HwH_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1455B)

## 分析

首先，根据题意，每次在第 $k$ 轮的时候可以选择向正方向走 $k$ 步，或者往负方向走 $1$ 步

那么当选择在第 $k$ 轮的时候选择向负方向走 $1$ 步时，就相当于这一轮向前走了 $k$ 步以后再回退 $k+1$ 步

那么显然，我们可以先走一直走，直到最后走过了目的地，再进行后退的判断

## Solution

首先，我们可以先将每次截止到第 $k$ 轮，每次都选择向前走，累计走过的步数序列预处理出来，然后对这个序列查找第一个累计走到的位置不小于目的地 $x$ 的所需的轮数 $pos$

如果累计走过 $pos$ 轮后，刚好能够走到 $x$ 位置，那么答案即为 $pos$

反之，如果在 $k=1$ 时候向后走，此时减去的数最小，即为 $2$ ，所以，如果当前 $pos$ 轮后的位置所到达的位置刚好比 $x$ 大 $1$ ，那么最优情况下就是先走到 $pos$ 轮后的位置，然后回退一步才能到达，此时的答案即为 $pos+1$ 

如果以上两个情况都不满足，则 $pos$ 轮后走到位置相对 $x$ 多出的部分的长度必然大于 $2$ ， 小于 $pos-1$ ，那么必然可以在先前的某一轮里进行向后走，将多出的部分调整好，此时答案即为 $pos$

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<math.h>
#include<cstring>
#include<algorithm>
#define ll long long

const ll maxn=1e6+10;
const ll inf=1e6;
ll k,n,cnt,ans;
ll s[maxn];

inline void pre()
{
	for(int i=1;;i++)
	{
		s[i]=s[i-1]+i;
		cnt++;
		if(s[i]>inf) break;
	}
}

int main(void)
{
	pre();
	
	scanf("%lld",&k);
	
	while(k--)
	{
		ans=0;
		scanf("%lld",&n);
		
		ll pos=std::lower_bound(s+1,s+cnt+1,n)-s;
		
		if(s[pos]==n)
		{
			ans=pos;
		}
		else
		{
			ll k=s[pos]-n-1;
			if(k==0)
			{
				ans=pos+1;
			}
			else
			{
				ans=pos;
			}
		}
		
		printf("%lld\n",ans);
	}
	
	return 0;
}
```

---

