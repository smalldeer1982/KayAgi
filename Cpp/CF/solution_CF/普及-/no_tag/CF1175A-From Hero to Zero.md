# From Hero to Zero

## 题目描述

You are given an integer $ n $ and an integer $ k $ .

In one step you can do one of the following moves:

- decrease $ n $ by $ 1 $ ;
- divide $ n $ by $ k $ if $ n $ is divisible by $ k $ .

For example, if $ n = 27 $ and $ k = 3 $ you can do the following steps: $ 27 \rightarrow 26 \rightarrow 25 \rightarrow 24 \rightarrow 8 \rightarrow 7 \rightarrow 6 \rightarrow 2 \rightarrow 1 \rightarrow 0 $ .

You are asked to calculate the minimum number of steps to reach $ 0 $ from $ n $ .

## 说明/提示

Steps for the first test case are: $ 59 \rightarrow 58 \rightarrow 57 \rightarrow 19 \rightarrow 18 \rightarrow 6 \rightarrow 2 \rightarrow 1 \rightarrow 0 $ .

In the second test case you have to divide $ n $ by $ k $ $ 18 $ times and then decrease $ n $ by $ 1 $ .

## 样例 #1

### 输入

```
2
59 3
1000000000000000000 10
```

### 输出

```
8
19
```

# 题解

## 作者：hensier (赞：2)

主要思路：对于每组测试数据，只要能除得尽，就不停地除，否则每次减$1$。因为除的速度绝对比减$1$的速度要快。代码如下：~~（十年OI一场空，不开long long见祖宗）~~

```cpp
#include<cstdio>
int t;
long long n,k,s;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        s=0;
        scanf("%lld%lld",&n,&k);
        while(n)
        {
            while(n%k==0)
            {
                n/=k;
                s++;
            }
            s++;
            n--;
        }
        printf("%lld\n",s);
    }
}
```

提交了之后发现，第一个点$AC$，第二个点就$TLE$。

考虑了一下之后，发现优化的方法很简单——每一次不是减$1$，而是减去$n\%k$，这样更加直接。即：


```cpp
#include<cstdio>
int t;
long long n,k,s;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        s=0;
        scanf("%lld%lld",&n,&k);
        while(n)
        {
            while(n%k==0)
            {
                n/=k;
                s++;
            }
            s+=n%k;
            s-=n%k;
        }
        printf("%lld\n",s);
    }
}
```

这样的速度就更快了，~~而且看起来更清晰一些~~。最终，居然$AC$了。所以有的时候优化可能只是改动了一下，但是变化是十分巨大的。

---

## 作者：Kubic (赞：1)

考虑到只允许向下减$1$，那么思路就很简单了：

每一次将$n$减去$n$ $mod$ $k$，使$n$成为$k$的倍数，再将$n$除以$k$，顺便统计答案（加上$(n$ $mod$ $k)+1$）

由于最后一次，$n$被减为$0$了，但我们仍然让答案加上了$n$除以$k$所产生的$1$次操作，所以最后输出时答案要减$1$

上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int T;ll n,m,ans;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		ans=0;scanf("%lld %lld",&n,&m);
		while(n) ans+=n%m+1,n/=m;//这里不写n-=n%m是因为n/=m会自动吃掉余数
		printf("%lld\n",ans-1);//答案减1
	}
}
```

---

## 作者：Zekrom (赞：1)

## 二分 
 
找离n最近的k的倍数    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define inf 0x3f3f3f3f
using namespace std;
inline long long read(){
	long long x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
int main()
{
	long long t=read();
	for(int i=1;i<=t;i++){
		long long x=read();long long d=read();
		long long cnt=0,mul=1;
		if(d>x){
			printf("%lld\n",x);
			continue;
		}
		while(x){
			long long l=1,r=x/d+1;
			if(x<d){
				cnt+=x;
				break;
			}
			while(l<r){
				long long mid=(l+r+1)>>1;
				if(mid*d>x)r=mid-1;else l=mid;
			} 
			cnt+=x-(r*d);x=r*d;
			while(x%d==0){
				x/=d;cnt++;
			}			
		}
		printf("%lld\n",cnt);
	} 
	return 0;
}

```


---

## 作者：霍士弘 (赞：0)

显然，对于 $n$ 来说，两种情况：  
① $k | n$，直接除 $k$ 是最优选择，代价为 $1$；  
② $k\not |  n$，不能直接除，我们可以转化为第一个比 $n$ 小的 $k$ 的倍数，即 $\left \lfloor \dfrac{n}{k}\right \rfloor \cdot k$，明显是最优选择，代价为 $n \bmod k$；  
***
所以，可以得到一个递归的式子：  
设 $f(n,k)$ 为 $n,k$ 时的最小操作数。  
则，  
$$f(n,k) = 
\begin{cases}
	0  & n = 0 \\
	f(\dfrac{n}{k},k) + 1  & k | n \\
   f(n - n \bmod k,k) + n \bmod k \quad & k \not | n \\
\end{cases}$$
复杂度在 $\Theta(\log n)$ 级别。  
***
代码：  
```cpp
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;
ll f(ll n,ll k)
{
	if(n == 0) return 0;
	if(n % k == 0)
	{
		return f(n / k,k) + 1;
	}else
	{
		return f(n - n % k,k) + (n % k);
	}
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{	
		ll n,k;
		cin>>n>>k;
		cout<<f(n,k)<<endl;
	}
	return 0;
}
```  
需要注意的是，答案也是要开 long long 的。

---

## 作者：zoobidubi (赞：0)

题意很简单，就是让你求一个最小操作数的问题

每次有两种操作

将 n 减 1

将 n 除以 k （前提：n 是 k 的倍数）

我的第一反应是，既然求最小操作数，那么当然是用广搜喽！

然后就敲出了以下的代码

wrong code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, k;
queue <long long> q;
long long bfs (long long x)
{
    q.push(x);
    int step = 0;
    while (!q.empty())//队列不为空
    {
        step ++;//步数加一
        long long len = q.size();//要操作的次数
        for (int i = 1; i <= len; i ++)
        {
            long long xx = q.front();//取出队头
            q.pop();//弹出
            if (xx == 1) return step; //因为除完这个数不可能等于0，所以只有减得情况，就是等于1减一后就返回步数
            q.push(xx - 1);//放入减一的情况
            if (xx % k == 0) q.push(xx / k); //可以整除就放入整除的情况
        }
    }
}
int main()
{
    int t;
    cin >> t;
    while (t --)
    {
        cin >> n >> k;
        while (!q.empty()) q.pop();//清空队列
        cout << bfs (n) << endl;//搜
    }
    return 0;
}

```
打完后一提交，居然惨烈的TLE了！

于是无奈的把每个操作得出的数输出，想剪枝一波

居然神奇的发现，每次搜的时间都消耗在减一的操作上了，10^18，不超才怪呢

于是全删了，魔改了一番，终于出现了可爱的AC（逃

具体思路看注释

AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, k;
long long xiagao (long long x)
{
    long long step = 0;//步数清0
    while (n)//一直做到n=0
    {
        if (n % k == 0) step ++, n /= k;//如果能整除的话，就先整除
        else step += (n % k), n -= (n % k);
        //否则的话就要一直减一，但是每次减都是减到能整除，所以我们可以
        //直接就减掉所有要减去的数，就是modk多出来的东西。。
        //步数就是减一的次数
    }
    return step;
}
int main()
{
    int t;
    cin >> t;
    while (t --)
    {
        cin >> n >> k;
        cout << xiagao (n) << endl;
    }
    return 0;
}


```



---

## 作者：AC_Dolphin (赞：0)

贪心策略：只要$k|n$就$k/=n$，否则把$n--$直到$k|n$，也就是$n-=(n\%k)$

因为$2^{64}>10^{18}$所以肯定不会爆栈

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define MAXN 100010
int a[MAXN],cnt,t;
ll n,k;
inline ll read(){
    ll f(1),x(0);
    char ch(getchar());
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return f*x;
}
inline ll query(ll n,ll k){
    if(!n) return 0;
    return (n%k)+query(n/k,k)+1;
}
int main(){
    t=read();
    while(t--){
        n=read();k=read();
        printf("%lld\n",query(n,k)-1);
    }
    return 0;
}
```

---

