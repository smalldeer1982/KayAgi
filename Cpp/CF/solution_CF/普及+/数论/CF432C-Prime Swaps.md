# Prime Swaps

## 题目描述

You have an array $ a[1],a[2],...,a[n] $ , containing distinct integers from $ 1 $ to $ n $ . Your task is to sort this array in increasing order with the following operation (you may need to apply it multiple times):

- choose two indexes, $ i $ and $ j $ ( $ 1<=i&lt;j<=n $ ; $ (j-i+1) $ is a prime number);
- swap the elements on positions $ i $ and $ j $ ; in other words, you are allowed to apply the following sequence of assignments: $ tmp=a[i],a[i]=a[j],a[j]=tmp $ ( $ tmp $ is a temporary variable).

You do not need to minimize the number of used operations. However, you need to make sure that there are at most $ 5n $ operations.

## 样例 #1

### 输入

```
3
3 2 1
```

### 输出

```
1
1 3
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
4 2 3 1
```

### 输出

```
3
2 4
1 2
2 4
```

# 题解

## 作者：hgckythgcfhk (赞：3)

假设你不会或者没想到哥德巴赫猜想，怎么做这个题？

其实我感觉用哥德巴赫猜想解释除了能显得自己会以外没有任何意义，大部分人想不到这种在 OI 中比较冷门的东西，~~这个东西甚至不在大纲上~~，所以我介绍一个不用哥德巴赫猜想的不超纲想法。

首先对于一个排列每个元素的目标位置是确定的，不考虑长度是质数的限制的话对于每个元素都可以一次操作把这个元素都放到正确位置，最后最多只会操作 $n-1$ 次，然后考虑加上这个限制，发现一次性把一个元素放好一定不会比最优解劣太多，那就考虑把要移动的距离拆成若干个质数多次移动，每次移动最大的小于等于当前位置与目标位置距离的质数。

其实哥德巴赫猜想仅仅只是用于证明时间复杂度，但是，哥德巴赫猜想并不在 NOI 大纲上，而且在 OI 中比较冷门，用这个东西仅仅只能做这个题，换个题还是想不到，于是，我们需要一个容易理解和想到的想法，使得能在别的题里很自然的想到。

线性筛总不超纲且不冷门吧，直觉告诉我们，相邻两个质数的距离不是很大，这个直觉主要来自于一般的个位数是 $3$ 或 $7$ 的大概率是质数，用线性筛验证一下，发现:

1. $10^5$ 范围内相邻两个质数的最大距离是 $72$

1. $10^6$ 范围内相邻两个质数的最大距离是 $114$

1. $10^7$ 范围内相邻两个质数的最大距离是 $154$

1. $10^8$ 范围内相邻两个质数的最大距离是 $168$

1. $10^9$ 范围内相邻两个质数的最大距离是 $232$

1. $72$ 范围内相邻两个质数的最大距离是 $6$

1. $6$ 范围内相邻两个质数的最大距离是 $2$

说明了两件事情，这个东西增长并不快，远低于根号和 $\log^2$，具体的，大概在 $\log\times\log\log$。然后，$10^5$ 范围内最多交换 $3$ 次。

有人可能会抬杠说，这个解释仅保证在数据范围内正确，没有理论价值，非常不严谨。

确实，我不敢保证这个解释在那种早期的一些省选题的 $10^{10^5}$ 的范围内正确，但是，在那种范围内，哥德巴赫猜想也未必正确。

根据 bdfs “哥德巴赫猜想被证明了吗”的结果：

> __至今尚未有人能够证明或反驳它__

既然都不保证正确，那就不要抬杠了，起码我能保证这个做法[能过](https://codeforces.com/contest/432/submission/256985935)。

---

## 作者：LHN200861 (赞：1)

### 声明：

这篇题解是本蒟蒻写的第三篇题解，如果代码部分有问题，敬请谅解。另外，如果有描述不恰当的地方，或者错误的地方，希望大家多多指出，欢迎大家多多留言评论，共同进步。

### 题目链接：

[题目（洛谷）](https://www.luogu.com.cn/problem/CF432C)

[题目（CodeForces）](https://codeforces.ml/problemset/problem/432/C)

### 解题思路

**1.哥德巴赫猜想：**

第一条：每个大于2的偶数都是两个素数之和。

第二条：每个大于5的奇数都是三个素数之和。

**2.解答：**

只要知道哥德巴赫猜想的第一条就不难了。

①将每个元素的值作为下标，记录该元素所在的位置。

②排序的时候判断该点是否为本身。如果不是的话，就去判断两点之间的距离是否为素数，不是则变为两个素数相加即可。

**3.代码：**

```cpp
#include<bits/stdc++.h>//个人建议用万能头
using namespace std;//个人建议加上名字空间
bool p[100005],q[100005];//数组别开小了
int v[100005],a[100005];//数组别开小了
map<int,int>m;//定义map
vector<pair<int,int> >ve;//定义vector
int main()
{
    int n,i,k,t;//定义，不多解释
    //以下部分都是初始化：
    memset(p,0,sizeof(p));
    memset(q,0,sizeof(q));
    memset(v,0,sizeof(v));
    for(i=2;i<100005;i++)
    {
        if(!q[i])
        {
            p[i]=1;
            for(k=i;k<100005;k+=i)
                q[k]=1;
        }
    }
    for(i=2;i<100005;i++)//小于等于该值最近的素数
    {
    	if(p[i])v[i]=i;
        else v[i]=v[i-1];
	}
    //进入正题：
    cin>>n;//输入n。
    for(i=1;i<=n;i++)//输入a数组，并初始化map。
    {
        cin>>a[i];
        m[a[i]]=i;
    }
    for(i=1;i<=n;i++)//核心代码
    {
        while(m[i]!=i)
        {
            t=m[i]-i+1,k=m[i]-v[t]+1;
            ve.push_back(make_pair(k,m[i]));
            m[a[k]]=m[i];
            swap(a[m[i]],a[k]);
            m[i]=k;
        }
    }
    //以下部分都是输出：
    cout<<ve.size()<<endl;
    for(i=0;i<ve.size();i++)
        cout<<ve[i].first<<" "<<ve[i].second<<endl;
    return 0;//完美地结束
}千万不要抄袭呀！
```


---

## 作者：程门立雪 (赞：1)

**题意：**

给出长度为 $N$ 的排列，每次你可以选择两个位置 $i$，$j$ 并交换上边的数，前提是 $j - i + 1$ 是质数。

要求在 $5N$ 次操作内，把这个序列排号，输出具体排列的操作。

**题解：**

**哥德巴赫猜想**: 任意大于二的偶数,都可表示成两个素数之和。

那么我们每次放心的移动就好了！

那我们贪心的按照 $1, 2, 3, 4……$ 的顺序来排，（就是让 $1$ 到第一位置，$2$ 到第二位置），哥德巴赫猜想保证了我们每次都可以移得动。

每次我们把一个数往前移动 $x$ 距离时，每步先移动一个尽量大的质数距离即可。

然后由于 $n$ 以内的质数的个数为 $\pi(n) \sim \frac{n}{\ln(n)}$ 个，质数间的平均间距为 $\ln(n)$，所以可以保证在 $5N$ 次一定可以完成。

代码中预处理哪些数是质数，以及每个数比它小的最大质数是多少。

```c
/*
Date:2021.8.21
Source:CF432C
konwledge:哥德巴赫猜想:任意大于二的偶数,都可表示成两个素数之和。
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#define orz cout << "AK IOI"

using namespace std;
const int maxn = 1e5 + 10;

inline int read()
{
	int f = 0, x = 0; char ch = getchar();
	while(!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
	return f ? -x : x;
}
inline void print(int X)
{
	if(X < 0) {X = ~(X - 1); putchar('-');}
	if(X > 9) print(X / 10);
	putchar(X % 10 + '0');
}
int n, a[maxn];
map<int, int> m;
int cnt, flag[maxn];
bool vis[maxn], prime[maxn];
vector<pair<int, int> > ans;
void init()
{
	prime[1] = 1;
	for(int i = 2; i <= maxn; i++) 
	{
		if(!vis[i]) 
		{
			prime[i] = 1;
			for(int j = i; j <= maxn; j += i) vis[j] = 1;
		}
	}
	for(int i = 2; i <= maxn; i++)
		if(prime[i]) flag[i] = i;
		else flag[i] = flag[i - 1];
}
int main()
{
	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    n = read();
    init();
    for(int i = 1; i <= n; i++) 
    	a[i] = read(), m[a[i]] = i;
	for(int i = 1; i <= n; i++)
	{
		while(m[i] != i)
		{
			int t = m[i] - i + 1;                  //需要移动的距离 
			int step = m[i] - flag[t] + 1;         //flag[t] 小于需要移动的距离的最大的质数 
			ans.push_back(make_pair(step, m[i]));
			m[a[step]] = m[i];                     //交换 
			swap(a[m[i]], a[step]);
			m[i] = step;
		}
	} 
    printf("%d\n", ans.size());
    for(int i = 0; i < ans.size(); i++)
    printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}
```


感谢 https://lhn.blog.luogu.org/solution-cf432c 




---

## 作者：_edge_ (赞：0)

来一篇不同的题解。

首先看到这个题，就应该联想到质数的有关性质。

很容易想到，交换操作相当于交换到 $j-i+1$ 的地方 $+1$，相当于向左移动 $j-i+1$ 步然后再 $+1$。

具体的我们可以理解为向左移动质数减一步。

相当于质数加起来，这东西可以利用哥猜来解决。

哥猜是奇数一定能被分解成 $3$ 个质数的和，偶数一定能被分解成 $2$ 个质数的和。

对于奇数的情况 $-3$ 就可以转化为偶数的情况。

然后我们需要做的操作就是把 $j-i+1$ 变成几个质数的和。

但是！我们会发现这东西居然还有减一操作。

但是非常非常有趣的是，我们分解出来的 $3$ 个质数的个数 $3$ 是个质数，同时对于偶数 $2$ 也是一个质数！

因此，我们可以再奇数后面加个 $3$，偶数后面加个 $2$。

我们操作次数理论下界是 $4 \times n$，但实际上完全跑不到。

还有一个子问题是哥猜的分解，这东西事实上 $n$ 以内的质数只有不到 $10^4$，可以筛出来然后暴力搞。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define pb push_back
using namespace std;
const int INF=2e5+5;
int n,a[INF],f[INF],p[INF];
bool prime[INF];
int Prime[INF],P[INF][5];
vector <int> ans[5];
void calc(int x,int y) {
	if (x>y) swap(x,y);
	if (y-x+1==1) return ;
//	cout<<y-x+1<<""
	if (!prime[y-x+1]) {
		int xx=y-x+1;
		ans[0].pb(y);ans[1].pb(y-xx+1);
		swap(p[a[y]],p[a[y-xx+1]]);
		swap(a[y],a[y-xx+1]);
		return ;
	}
	if ((y-x+1)%2==0) {
//		y=y-x+1;
		int xx=y-x+1;
		ans[0].pb(y);ans[1].pb(y-P[xx][0]+1);
		swap(p[a[y]],p[a[y-P[xx][0]+1]]);
		swap(a[y],a[y-P[xx][0]+1]);
		y=y-P[xx][0]+1;
		
//		if (xx==26) 
//			cout<<ans[0][ans[0].size()-1]<<" "<<ans[1][ans[0].size()-1]<<" ?\n";
		
		ans[0].pb(y);ans[1].pb(y-P[xx][1]+1);
		swap(p[a[y]],p[a[y-P[xx][1]+1]]);
		swap(a[y],a[y-P[xx][1]+1]);
		y=y-P[xx][1]+1;
		
//		if (xx==26) 
//			cout<<ans[0][ans[0].size()-1]<<" "<<ans[1][ans[0].size()-1]<<" ?1\n";
		
		ans[0].pb(y);ans[1].pb(y-2+1);
		swap(p[a[y]],p[a[y-2+1]]);
		swap(a[y],a[y-2+1]);
		
//		if (xx==26) 
//			cout<<ans[0][ans[0].size()-1]<<" "<<ans[1][ans[0].size()-1]<<" ?1\n";
	}
	
	else {
//		y=y-x+1;
		int xx=y-x+1;
		ans[0].pb(y);ans[1].pb(y-3+1);
		swap(p[a[y]],p[a[y-3+1]]);
		swap(a[y],a[y-3+1]);
		y=y-3+1;
		
		ans[0].pb(y);ans[1].pb(y-3+1);
		swap(p[a[y]],p[a[y-3+1]]);
		swap(a[y],a[y-3+1]);
		y=y-3+1;
		
		ans[0].pb(y);ans[1].pb(y-P[xx-3][0]+1);
		swap(p[a[y]],p[a[y-P[xx-3][0]+1]]);
		swap(a[y],a[y-P[xx-3][0]+1]);
		y=y-P[xx-3][0]+1;
		
		ans[0].pb(y);ans[1].pb(y-P[xx-3][1]+1);
		swap(p[a[y]],p[a[y-P[xx-3][1]+1]]);
		swap(a[y],a[y-P[xx-3][1]+1]);
	}
}
signed main()
{
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=2;i<=2e5;i++) {
		if (!prime[i]) Prime[++Prime[0]]=i;
		for (int j=1;j<=Prime[0] && Prime[j]*i<=2e5;j++) {
			prime[Prime[j]*i]=1;
			if (!(i%Prime[j])) break;
		}
	}
	for (int i=1;i<=Prime[0];i++) {
		for (int j=1;j<=Prime[0];j++) {
			int x=Prime[i]+Prime[j];
			if (x>2e5) break;
			if (!P[x][0]) 
				P[x][0]=Prime[i],P[x][1]=Prime[j];
		}
	}
	for (int i=1;i<=n;i++) cin>>a[i],p[a[i]]=i;
	for (int i=1;i<=n;i++) {
		int x=p[i];
		calc(i,x);
	} 
//	for (int i=1;i<=n;i++) cout<<a[i]<<" ";
//	cout<<"\n";
	cout<<ans[0].size()<<"\n";
	int len=ans[0].size();
	for (int i=0;i<len;i++)
		cout<<ans[1][i]<<" "<<ans[0][i]<<"\n";
	return 0;
}
```


---

