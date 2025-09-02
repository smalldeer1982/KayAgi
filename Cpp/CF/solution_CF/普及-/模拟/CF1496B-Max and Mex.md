# Max and Mex

## 题目描述

[题目链接](https://codeforces.com/problemset/problem/1496/B)

给出一个长度大小为 $n$ 的可重集合 $S$（集合内允许有），保证这 $n$ 个数互不相同且非负。

接下来，你需要将下面操作进行 $k$ 次：  
将 $\lceil \frac{a+b}{2}\rceil$ 加入集合（注意这里是**可重集**），其中 $a=\operatorname{mex}(S)$， $b=\max(S)$。

这里 $\operatorname{mex}(S)$ 表示集合 $S$ 中没有出现过的最小的非负整数，$\max(S)$ 表示 $S$ 中的最大整数。

求 $k$ 次操作后，集合 $S$ 中有多少个不同的数。

## 说明/提示

$1\le T \le 100$  
$1\le n \le 10^5$  
$0 \le a_i,k \le 10^9$  
$\sum n\le 10^5$

## 样例 #1

### 输入

```
5
4 1
0 1 3 4
3 1
0 1 4
3 0
0 1 4
3 2
0 1 2
3 2
1 2 3```

### 输出

```
4
4
3
5
3```

# 题解

## 作者：洛璟 (赞：4)

### [博客食用更佳~](https://www.luogu.com.cn/blog/Soviet-Molotov/solution-cf1496b)

3.17 经巨佬Imakf的指正，修改了时间复杂度的错误

### 题目大意：

给定一个集合，每次选出这个集合的 $mex$ 和 $max$ 计算 $\lceil \frac{mex+max}{2}\rceil$，并插入此集合，计算操作 $k$ 次后集合中有多少个数字，重复数字算一个。 其中 $max$ 代表这个集合中的最大值，$mex$ 代表这个集合的补集的最小值。

## Solution 
解法一：暴力模拟，大家应该都会，但是 $k\leq 10^9$ 妥妥 $TLE$.

但是看到了 $k$ 的数据范围之后，有经验的人~~啪的一下就站起来了，很快啊~~就能看出来是找规律。

我们可以从两个数字去下手：$mex$、$max$ 我们考虑每一次得到的数是否会改变 $mex$ 和 $max$。我们考虑这个集合有没有包含 $0$~$n$ 的所有数字，若没有，我们可以易证 $max>mex$ 并且加入的数字不可能等于 $max$ 或者 $mex$。

证明：

$\because max>mex \space\space \lceil \frac{mex+max}{2}\rceil= \lfloor \frac{mex+max+1}{2}\rfloor $ 

$\therefore \lceil \frac{mex+max}{2}\rceil> mex \space\space\space \lceil \frac{mex+max}{2}\rceil< max$


~~好吧其实就是易证~~

---

那么就完事了，由于在上述情况中 $mex$ 和 $max$ 均不会改变，那么我们也就只需要找出第一个 $max$ 和 $mex$ ，经过计算后再加入集合，然后就可以直接忽略 $k$ 了。

接下来考虑另一种情况：若集合包含了 $0$~$n$ 所有数字。

那么我们可以轻易发现，$mex$ 始终等于 $max+1$ 那么也就是说，每次$\lceil \frac{mex+max}{2}\rceil$ 均等于 $max+1$ 也就是说每操作一次，集合里面的数字就加一，这个更加易证，手操一下就好了。

那么我们完美地跳过了 $k$ 这个天坑，复杂度降到了优秀的$O(n\space log n \space t)$ ~~这还是输入的复杂度。~~

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, t, k, me, ma;
int a[100010];
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c>'9')
    {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = (x << 3) + (x << 1) + (c ^ '0');
        c = getchar();
    }
    return x * f;
}
int main()
{
    t = read();
    while (t--)
    {
        map<int, bool> fg;
        priority_queue<int> q;
        n = read();
        k = read();
        for (int i = 1;i <= n;++i)
        {
            a[i] = read();
            fg[a[i]] = 1;
            q.push(a[i]);
        }
        if (k == 0)
        {
            printf("%d\n", n);
            continue;
        }
        for (int i = 0;i <= n;++i)
        {
            if (fg[i] == 0)
            {
                me = i;
                break;
            }

        }
        if (me > q.top())
        {
            printf("%d\n", n + k);
        }
        else
        {
            int tmp = (me + q.top() + 1) / 2;
            if (fg[tmp] == 0)
            {
                printf("%d\n", n + 1);
            }
            else
            {
                printf("%d\n", n);
            }
        }
    }

    return 0;
}
```


---

## 作者：Silence_water (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1496B)

---

$Analyse$

设 $a=\operatorname{mex}(S)$，$b=\max(S)$，$p=\left\lceil\dfrac{a+b}{2}\right\rceil$。

那么显然有 $a\ne b$。

考虑分类讨论：

1. 当 $k=0$ 时，无操作，$ans=n$。

2. 当 $a<b$ 时，此时必然有 $a<a+1<b$，即 $2\times a<a+b+1<2\times b$，因此 $a<p<b$。所以此时向 $S$ 中加入 $p$ 对 $a$ 和 $b$ 的值是没有影响的。故 $p$ 为定值，只需要考虑原集合中是否存在 $p$ 这个值。如果是，$ans=n$；否则 $ans=n+1$。

3. 当 $a>b$ 时，此时必然有 $a=b+1$，故 $p=\left\lceil\dfrac{2\times b+1}{2}\right\rceil=b+1$。因此，每操作一次，$S$ 中不同的数就会 $+1$。因此 $ans=n+k$。

---

$Solution$

比赛的时候脑抽了，用了个 `multiset`，不过还是能过的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int M=1e5+5;
int T,n,k,x;
multiset<int> m;
multiset<int>::iterator it,st;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
    	m.clear();
    	scanf("%d%d",&n,&k);
    	for(int i=1;i<=n;i++)
    	{
    		scanf("%d",&x);
    		m.insert(x);
		}
    	if(k==0)
    	{
    		printf("%d\n",n);
    		continue;
		}
		it=m.begin();
		int mex=-inf;
		if(*it>0)mex=0;// 无0就是0
		else
		{
			for(int i=1;i<n;i++)
			{
				st=it;it++;
				if(*st+1<*it){mex=i;break;}//找到mex
			}
			if(mex==-inf)mex=(*it)+1;//如果没找到，那么mex=max+1
		}
		it=m.end();
		it--;
		int mx=*it;
		if(mx+1==mex)
		{
			printf("%d\n",n+k);
			continue;
		}
		int ns=(int)ceil(0.5*(mex+mx));
		it=m.lower_bound(ns);
		if(*it!=ns)n++;//若不存在，ans=n+1
		printf("%d\n",n);
	}
    return 0;
}
```

---

$The$ $end$

感谢您的观看！如有不足，请麻烦指正哦。

---

## 作者：cmll02 (赞：1)

分类讨论一下。

如果 $\operatorname{mex}(a)>\max(a)$，那么每一次都会添加一个 $\operatorname{mex}(a)$，之后 $\operatorname{mex}(a),\max(a)$ 都会变大 $1$，所以答案是 $n+k$。

否则 $\operatorname{mex}(a),\max(a)$ 不会变，只要执行一次就可以了，最后统计答案。

```cpp
#include <stdio.h>
#include <string.h> 
#include <algorithm>
#define int long long
inline int read()
{
	int num=0,f=1;char c=getchar();
	while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
	while(c>47&&c<58)num=num*10+(c^48),c=getchar();
	return num*f;
}
int a[100005];
signed main()
{
	int T=read();
	while(T--)
	{
		int n=read(),k=read();
		for(int i=1;i<=n;i++)a[i]=read();
		std::sort(a+1,a+n+1);
		int mex=-1,max=a[n];a[0]=-1;
		for(int i=1;i<=n;i++)
		{
			if(a[i]-1>a[i-1])
			{
				mex=a[i-1]+1;
				break;
			}
		}
		if(mex==-1)
		{
			printf("%lld\n",k+max+1);
			continue;
		}
		if(max-1==mex)
		{
			printf("%lld\n",n);
		}
		else
		{
			if(k==0)printf("%lld\n",n);
			else
			{
				int aa=(max+mex-1)/2+1;
				for(int i=1;i<=n;i++)
				{
					if(a[i]==aa)
					{
						printf("%lld\n",n);
						goto ng;
					}
				}
				printf("%lld\n",n+1);
			}
		}
		ng:;
	}
}
```

---

## 作者：AuCloud (赞：1)

摸鱼的一场比赛

这个B还是很水的说。

# 题意

给出序列，进行$k$次操作，每次取**最小的没出现过的数字**$mex$和**最大的数字**$max$

在序列中插入$\lceil\frac{mex+max}{2}\rceil$，最后询问序列中有多少不同的数字

# 题解

可以比较简单的发现$\lceil\frac{mex+max}{2}\rceil$(不妨设为$x$)一定有：
$$
mex \leq x \leq max+1
$$

于是分情况讨论

#### $mex=x=max+1$

这种情况就是序列为$1-n$中的所有数，此时每做一次增加操作，不同数字个数会增加$1$

所以这种情况下答案即为$n+k$

#### 上一种不成立

先看一下边界情况：$mex = max - 1$

这种情况下，$x=max$，原序列无变化

因为之前的结论，$mex$与$max$都不会变化，则$k$次中的$x$都不会变化，所以数字个数最多增加$1$。

至于是否增加，判断$x$是否在原序列中出现过，未出现则答案为$n+1$，否则答案为$n$

# 代码

```cpp
#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
long long a[100001];
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		unordered_map<long long, bool> mp;
		long long n, k;
		cin >> n >> k;
		for(int i = 1; i <= n; i++)
		{
			scanf("%lld", a + i);
			mp[a[i]] = 1;
		}
		if(k == 0)
		{
			cout << n << endl;
			continue;
		}
		sort(a + 1, a + n + 1);
		long long mex = a[n] + 1;
		if(a[1] != 0) mex = 0;
		else for(int i = 2; i <= n; i++)
		{
			if(a[i] != a[i - 1] + 1)
			{
				mex = a[i - 1] + 1;
				break;
			}
		}
		if(mex == a[n] + 1) printf("%lld", n + k);
		else if(!mp[(mex + a[n] + 1) / 2]) printf("%lld", n + 1);
		else printf("%lld", n);
		puts("");
	}
	return 0;
}
```

---

## 作者：BrotherCall (赞：0)

## 思维题
对于我这个小蒟蒻来说，这题应该是 $Div.2$ 前三题里面思维难度最高的一题。

~~虽然巨佬们都说这题难度小于第一题。~~

### 言归正传
这题的重点是一个小结论：

如果 $⌈ {\frac{mex(S) + max(S)}{2}} ⌉$ 等于 $mex(S)$ ，那么这个数列将无节制地添加新数下去，直到添加 $k$ 次为止。此时答案为$n + k$ 。

如果 $⌈ {\frac{mex(S) + max(S)}{2}} ⌉$ 不等于 $mex(S)$ ， 那么只能加一次。然而我们还要考虑加进去的数原先是否已存在。若不存在，那么出现的数字总数为 $n+1$；若存在，那么出现数字的总数为 $n$ 。

## Code
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
 
int T;
int n,k;
int a[100010];
 
int main(){
	cin>>T;
	while(T--){
		scanf("%d%d",&n,&k);
		int mex = 0 ,maxi = 0;
		for(int i = 1;i <= n;i++){
			scanf("%d",&a[i]);
			maxi = max(maxi , a[i]);
		}
		if(k == 0){//单独考虑 k = 0的情况
			printf("%d\n",n);
			continue;
		}
		sort(a + 1,a + 1 + n);//从小到大排序，以求mex
		bool f = false;
		a[0] = -1;//将第0位赋值为-1，这样就可以判断0是否在集合中
		for(int i = 1 ; i <= n;i++){
			if(a[i] - a[i - 1] > 1){//求 mex 的值
				f = true;
				mex = a[i - 1] + 1;
				break; 
			}
		}
		if(f == false)mex = a[n] + 1;
		bool flag = false;
		int cr = (maxi + mex + 1) / 2;//以下为套用结论部分
		for(int i = 1;i <= n;i++){
			if(cr == a[i]){
				flag = true;
				break;
			}
		}
		if((maxi + mex + 1) / 2 == mex){
			printf("%d\n",n + k);
			continue;
		}
		if(flag == true)printf("%d\n",n);
			else printf("%d\n",n + 1);
	}
	return 0;
}
```


---

## 作者：Zzzzzzzm (赞：0)

### 难度：橙色-黄色，偏思维的构造题

我们可以先对测试点数据范围进行分析，可以看到一共$t$组数据每组数据$n$个点，$1≤t≤100$，$1≤n≤100000$，大概输入就是$n×t$的时间复杂度大概就是需要每一个测试点$O(n)$才能通过。

#### 因此，我们就需要推性质而不是尝试一个一个的去模拟。

首先$max∈z$，可能为正也可能为负，$mex∈N$，我们可以很两种情况讨论。

- 1.$max>mex$，我们就可以发现有$mex≤(\max+mex)/2≤max$，因为$mex>0$，$\max>mex>0$，所以一定存在有$\max+mex>0$，$2×mex<max+mex<2×max$。因此不会影响$mex$与$\max$的值。

- 2.$mex>max$，我们就可以发现有$\max<(\max+mex)/2≤mex$，因此每次会产生一个新的值。举个例子，如当前$\max=-2$，$mex=0$。$k=1$时$\max=-1$，$mex=0$，$k=2$时，$\max=0$，$mex=1$，以此类推每次都会使$n+1$。

所以我们只需在输入的时候先存储每一个元素到容器$map$中，记录下有无出现过，并且输入一个就比较更新最大值$\max$。然后通过找到循环从$0$开始的最小值，最差情况是数列为$0$~$n$，此时时间复杂度为$O(tn)$。

如果得到了$\max$与$mex$，我们就判断是$1$情况还是$2$情况，$1$情况判断当前数列中有无$(\max+mex)/2$，有则输出$n$，无则输出$n+1$。如果为第二种情况则输出$n+k$。

另外需要注意如果一轮即$k=0$都没有就直接输出$n$

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n, t, k, a, maxn, minn;
map<int, bool> Map;

template<typename T>										//快读快写 
inline void read(T&x){
	x=0; char q; bool f=1;
	while(!isdigit(q = getchar()))	if(q == '-')	f = 0;
	while(isdigit(q)){
		x = (x<<1)+(x<<3)+(q^48);
		q = getchar();
	}
	x = f?x:-x;
}

template<typename T>
inline void write(T x){
	if(x<0){
		putchar('-');
		x = -x;
	}
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}

int main(){
	read(t);
	while(t--){												//t组数据 
		maxn = -0x3f3f3f3f;
		minn = 0;
		Map.clear();
		read(n), read(k);
		for(register int i = 1; i <= n; ++i){
			read(a);
			Map[a] = true;									//加入a 
			if(a > maxn)	maxn = a;						//如果大于最大值就更新最大值 
		}
		if(k == 0){											//如果一轮都没有，就一定是k 
			write(n);
			putchar((char)10);
			continue;
		}
		for(register int i = 0; i <= maxn+1; ++i){			//寻找mex 
			if(Map[i])	continue;
			minn = i;
			break;
		}								
		if(minn > maxn){									//如果mex大于max 
			write(n+k);
			putchar((char)10);
			continue;
		}
		if(Map[(minn+maxn+1)/2]){							//否则看(max+mex)/2是否存在 
			write(n);
			putchar((char)10);
			continue;
		}
		write(n+1);
		putchar((char)10);
		continue;
	}
	return 0;
}
```


---

## 作者：清烛 (赞：0)

[My blog](https://imyangty.com/oi/1324)

### 题意
给定一个多重集合 $S$，初始 $S$ 中有 $n$ 个互异的非负整数，定义 $\max (S)$ 为该集合中的最大元素，定义 $\mathrm{mex}(S)$ 为该集合中**第一个未出现过的非负整数**。

进行 $k$ 次操作，每次操作取出 $a = \max(S)$ 和 $b = \mathrm{mex}(S)$，然后计算出 $\left\lceil\frac{a + b}2\right\rceil$ 并插入回这个集合中。求 $k$ 次操作之后集合中互异元素的数量。

### 题解
比较有趣的思维题

注意到 $n\le 10^5, k\le 10^9$，所以暴力模拟肯定是行不通的，同时这道题是 CF 的 div2 B，所以考虑寻找这题的结论。

首先，如果 $\mathrm {mex}(S)$ 小于集合中最大的元素，则我们进行这个操作之后**$\mathrm{mex}(S)$ 的值是不会发生改变的**，举个例子：

$S = \lbrace 1, 2, 3, 5, 6\rbrace$，则 $\mathrm{mex}(S) = 0$，并且进行一次操作之后 $S = \lbrace1, 2, 3, 5, 6\rbrace$ 不发生改变，所以**如果 $\mathrm{mex}(S)$ 在集合中不存在并且小于集合中的最大元素**，进行一次操作之后就会陷入死循环，所以对于这种情况只需要查找 $\left\lceil\frac{a + b}2\right\rceil$ 在原来的集合中是否存在。

但对于 $S = \lbrace0, 1, 2, 3, 4\rbrace$ 这种情况，不难发现每进行一次操作之后 $S$ 中互异元素的数量都会增加 $1$，所以直接输出 $n + k$ 即可。

仍然需要注意 $k = 0$ 的情况，需要进行特判。

代码如下，注意一开始所有的元素不一定是升序排列的，所以一开始需要进行排序。一开始寻找 $\mathrm{mex}(S)$ 的方法也很简单：直接扫一遍即可。

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

const int maxn = 1e5 + 5;
int a[maxn], n, k;

int rndup(int a, int b)
{
    int ret = a + b;
    if (ret & 1)
        ret = (ret >> 1) + 1;
    else ret >>= 1;
    return ret;
}

int main()
{
    int T = read();
    while (T--)
    {
        n = read(), k = read();
        FOR(i, 1, n) a[i] = read();
        if (k == 0)
        {
            printf("%d\n", n);
            continue;
        }
        std::sort(a + 1, a + n + 1);
        if (a[n] == n - 1)
        {
            printf("%d\n", k + n);
            continue;
        }
        int mex = 0;
        FOR(i, 1, n)
        {
            if (a[i] == mex)
                ++mex;
            else break;
        }
        //printf("mex%d\n", mex);
        if ((*std::lower_bound(a + 1, a + n + 1, rndup(a[n], mex))) == rndup(a[n], mex))
            printf("%d\n", n);
        else printf("%d\n", n + 1);
    }
    return 0;
}
```


---

## 作者：血色黄昏 (赞：0)

感觉是一道很水的思维题，比 A 做的还快

题意是对一个几个进行 k 次操作，每次操作插入 $(max+mex)/2$ 向上取整，问操作结束集合中有几个数

我们分两种情况讨论

当 $mex=max+1$ 时，每次操作都会加入 $max+1$ 这个数，那么 k 次操作就会将集合中元素个数增加 k 

其他情况时，如果插入的数有了那么不管几次操作都不会改变个数；如果没有，因为插入的数不会等于 mex 所以以后插入的数一直会是这个数，那么最后元素个数就是原来个数加一

注释很详细，看代码吧 qwq

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, t, k, ans = 0, u, a[100010];
bool tong[100010];
string s;
set<int>www;
int cli()
{
	return www.size();//cli返回集合中元素个数
}
int main()
{
	cin>>t;
	while(t --)//多测
	{
		www.clear();
		memset(tong, false, sizeof(tong));
		int maxn = -0x3f3f3f3f, mex = -1;//多测记得清空
		cin>>n>>k;//输入
		for(int i = 1;i <= n;i ++)
		{
			cin>>u;//读入u，存进a[i]
			a[i] = u;
			www.insert(u);
			if(u <= 1e5)tong[u] = true;//因为最多1e5个，所以前1e5+1个中一定有一个是集合没有的
			maxn = max(maxn, u);//找max
		}
		for(int i = 0;i <= 1e5;i ++)
		{
			if(!tong[i])//找到mex然后break
			{
				mex = i;
				break;
			}
		}
		int qwq = (maxn + mex) % 2 == 1 ? (maxn + mex + 1) / 2 : (maxn + mex) / 2;//qwq为应插入的数，见题意
		if(mex > maxn)//如果mex比较大
		{
			cout<<cli() + k<<endl;//每次操作都会多一个数
			continue;
		}
		bool flag = true;
		for(int i = 1;i <= n;i ++)
		{
			if(a[i] == qwq)//如果有了falg变成false并输出
			{
				flag = false;
				cout<<cli()<<endl;
				break;
			}
		}
		if(flag)cout<<cli() + min(1, k)<<endl;//这里要注意，如果k为0就相当于没有操作，取1和k中最小的                             
	}
    return 0;
}
```


---

## 作者：vectorwyx (赞：0)

令 $a=mex(S),b=max(S)$

如果 $a<b$，则 $a<\lceil\frac{a+b}{2}\rceil\le b$，因此这 $k$ 次操作既不会改变 mex 也不会改变 max，加入 $S$ 的数恒为一开始的 $\lceil\frac{a+b}{2}\rceil$。

如果 $a>b$，则由 mex 和 max 的定义可知 $a=b+1$，故加进来的数为 $\lceil\frac{a+b}{2}\rceil=a$，恰好是此次操作前 S 的 mex。所以每次操作后 $mex(S)$ 和 $max(S)$ 都会加 $1$，集合里会多出一个不同的数。$k$ 次操作后就会多出 $k$ 个不同的数。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e5+5;
int a[N],n,k;

void work(){
	n=read(),k=read();
	fo(i,1,n) a[i]=read();
	sort(a+1,a+1+n);
	n=unique(a+1,a+1+n)-a-1;
	if(k==0){
		printf("%d\n",n);
		return;
	}
	fo(i,1,n) if(i-1!=a[i]){
		printf("%d\n",n+1-binary_search(a+1,a+1+n,(a[n]+i-1+1)/2));
		return;
	}
	printf("%d\n",n+k);
	//puts("");
}

int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：LinkZelda (赞：0)

- **题意**：

给定 $n$ 个非负数（可能重复），每次操作加入一个数 $\left\lceil\dfrac{mex+max}{2}\right\rceil$ , 其中 $mex$ 为这些数中最小的没出现过的非负数，$max$ 为这些数中的最大数。

求操作 $k$ 次后的不同数的个数。

- $Solution$：

我们发现可以分类讨论：

1. $mex<max$ ：显然此时加入的数是小于 $max$ ，并且是不等于 $mex$ 的。那么这个数加进去之后，对 $max$ 和 $mex$ 是没有影响的，直接判断新加进去的数是否存在于原集合中即可。

2. $max<mex$ ：显然此时 $mex=max+1$，那么新加入的数为 $max+1$，然后再加入一次的话就是新加入 $max+2$ 。于是相当于每次在后面放多一个未出现过的数。答案为 $n+k$。

- **代码**：
```cpp 
#include<cstdio>
#include<algorithm>
#include<ctype.h> 
using namespace std;
inline int read()
{
		int x=0,f=1;char ch=getchar();
		while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
		while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
		return x*f; 
}
int t,n,k,a[100005];
int main()
{
	t=read();
	while(t--)
	{
		n=read(),k=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		sort(a+1,a+n+1);
		int max=a[n],mex=0;
		for(int i=1;i<=n;i++)//找一次最小的未出现过的非负数
			if(a[i]==mex)
				mex++;
		if(mex<max)//分类讨论
		{
			bool ok=0;
			int ret=(mex+max)/2;
			if((max+mex)&1)
				ret++;
			for(int i=1;i<=n;i++)
				if(ret==a[i])
				{
					ok=1;
					break;
				}
			if(ok||k==0)//特判操作次数为 0 和加入的数已出现的情况
				printf("%d\n",n);
			else
				printf("%d\n",n+1); 
		}
		else
		{
			printf("%d\n",n+k);
		}
		
	}
	return 0;
}

```

---

