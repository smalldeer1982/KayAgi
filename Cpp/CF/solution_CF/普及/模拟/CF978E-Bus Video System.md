# Bus Video System

## 题目描述

The busses in Berland are equipped with a video surveillance system. The system records information about changes in the number of passengers in a bus after stops.

If $ x $ is the number of passengers in a bus just before the current bus stop and $ y $ is the number of passengers in the bus just after current bus stop, the system records the number $ y-x $ . So the system records show how number of passengers changed.

The test run was made for single bus and $ n $ bus stops. Thus, the system recorded the sequence of integers $ a_1, a_2, \dots, a_n $ (exactly one number for each bus stop), where $ a_i $ is the record for the bus stop $ i $ . The bus stops are numbered from $ 1 $ to $ n $ in chronological order.

Determine the number of possible ways how many people could be in the bus before the first bus stop, if the bus has a capacity equals to $ w $ (that is, at any time in the bus there should be from $ 0 $ to $ w $ passengers inclusive).

## 说明/提示

In the first example initially in the bus could be $ 0 $ , $ 1 $ or $ 2 $ passengers.

In the second example initially in the bus could be $ 1 $ , $ 2 $ , $ 3 $ or $ 4 $ passengers.

In the third example initially in the bus could be $ 0 $ or $ 1 $ passenger.

## 样例 #1

### 输入

```
3 5
2 1 -3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 4
-1 1
```

### 输出

```
4
```

## 样例 #3

### 输入

```
4 10
2 4 1 2
```

### 输出

```
2
```

# 题解

## 作者：「已注销」 (赞：6)

设上车前人数$x$，中途最大人数为$x+max$，最小人数为$x+min$ $(max≥0,min\le0)$

可得不等式组$x+max\le w,x+min≥0$

整数解个数为$max(0,w-max+min+1)$

求出$max,min$即可，记得`long long`
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,w,a;
long long s,mx,mn;
int main(){
	cin>>n>>w;
	for(int i=1;i<=n;++i){
		cin>>a;
		s+=a;
		mx=max(mx,s);
		mn=min(mn,s);
	}
	cout<<max(0LL,w-mx+mn+1);
}
```

---

## 作者：wuyixiang (赞：4)

题目大意：一辆大巴车，到每个站点会下车 $-a_i$ 或上车 $a_i$ 人，但是任意一个时刻大巴车的总人数都应该在 $0$ 至 $w$ 人之间，问一开始大巴车上的人数有几种可能。

思路分析：一道简单的贪心题。

把 $a$ 数组遍历完之后，我们可以得知车上在任意一个时刻最多会增加 $maxx$ 人，减少 $minn$ 人。所以一开始车上的人数，必须 $+maxx \le w$，$-minn \ge 0$。所以车上的人数只有可能是 $minn$ 至 $w - maxx$ 人，那么就会有 $w - maxx - minn + 1$ 种方案。注意：如果 $minn > w - maxx$，就说明不存在可能性，应当输出 $0$。

### AC code:

```cpp
#include <iostream>
using namespace std;
long long n,w,a,maxx,minn,num ;//不开long long见祖宗
int main()
{
    cin >> n >> w;
    for(int i = 1;i <= n;i ++)
    {
        cin >> a;
        num += a;
        maxx = max(maxx,num),minn = min(minn,num);//更新最大与最小
    }
    cout << max(w - maxx + minn + 1,0LL);//注意这里的minn是负数，应改成+号
}
```


---

## 作者：Fkxxx (赞：2)

### 题意

一辆公交车，上面有整数个人，有 $n$ 个站，给出每个站的上车人数减下车人数。

问：最开始有多少种人数，在公交车运行任何时刻人数都不超过 $w$？

### 思路

我们可以感性一点思考，发现，结果一定是在某个区间内的。

例如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/ighbti14.png)

在这个例子中，红色的这种方案是可行的答案的**最大值**，反之绿色的方案则是**最小值**。

所以我们就可以假设最开始车上没人，接下来模拟一遍并计算最小值和最大值。

最后计算最小值和最大值的差值，就可以得到下面这个范围：

![](https://cdn.luogu.com.cn/upload/image_hosting/w3z47zm4.png)

接下来我们想计算出答案的范围。

以图中的黑色方案为例，我们要求的其实就是，这条方案最大的，**向上下活动的范围**，也就是下图中的灰色范围。

![](https://cdn.luogu.com.cn/upload/image_hosting/iqw6mnwb.png)

最后，因为我们求出的范围是一个闭区间，最终答案需要加一，所以可以得出下式：

$$w-(max-min)+1$$

### 重要提示

一定要开 `long long`。

### ACCODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n , w , num , minx , maxx ;
signed main(){
    cin >> n >> w ;
    for( int i = 1 ; i <= n ; i ++ ){
        int u ;
        cin >> u ;
        num += u ;
        maxx = max( maxx , num ) ;
        minx = min( minx , num ) ;
    }
    cout << max( (int)0 , w - maxx + minx + 1 ) ;
    return 0 ;
}
```

---

## 作者：Composite_Function (赞：1)

# 思路

设一开始巴士上的人数为 $ans$，第 $i$ 次上/下车人数位 $a_i$。

中途人数最多的为 $ans + \max \left\{ \sum^n_{i = 1} a_i \right\}$，最少为 $ans + \min \left\{ \sum^n_{i = 1} a_i \right\}$。

记 $max$ 表示  $\max \left\{ \sum^n_{i = 1} a_i \right\}$，$min$ 表示 $\min \left\{ \sum^n_{i = 1} a_i \right\}$。

则
$
\left\{
\begin{array}{rcl}
ans + max \leq w\\
ans + min \geq 0\\
\end{array} \right.
$

又 $ans$ 为整数，所以 $ans$ 有 $\max(0, w - max + min + 1)$ 个解。

------------

# 代码

```
# include <bits/stdc++.h>
using namespace std;
# define int long long
int n, w, sum, a;
int maxx, minn;
signed main()
{
    cin >> w >> n;
    while (n--) {
        cin >> a, sum += a;
        maxx = max(maxx, sum);
        minn = min(minn, sum);
    }
    int ans = w - maxx + minn + 1;
    cout << max(0ll, ans) << endl;
    return 0;
    //作者做了一些啥用没有的防抄处理，hh
}
```


---

## 作者：SqrtSecond (赞：1)

我们先**假设**车上最开始一个人都没有。

模拟一遍过程，并记录下过程中人数的最大值 $maxn$ 与最小值 $minn$ 。（**过程中考虑人数为负数的情况**）

显然最开始的乘客数的范围是一个区间。

我们来讨论一下这个区间的最大值 $r$ 与最小值 $l$ 。

### 最大值

最大值就是最多还能上多少乘客。

我们只需要考虑上述过程中人数最大值即可。

此时由于人数总是 $\le w$ ，当能上车的人数最多时，这个值应该恰好为 $w$ 。

则 $maxn+r=w$ ，解得 $r=maxn-w$ 。

### 最小值

这个相对好理解一点。

因为过程中乘客非负，那么只需要保证最小的时候至少为0即可。

即 $l+minn=0$ ， $l=-minn$ 。

### 方案数

即区间长度，答案为 $r-l+1$ ，注意若 $l>r$ 则无解。

### code:

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	char ch=getchar();int x=0,r=1;
	while(ch<'0'||ch>'9'){if(ch=='-')r=0;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return r?x:-x;
}//快读 
int n,w,x;//如题所示
int now,minn,maxn,l,r;
signed main()
{
	n=read();w=read();
	now=0;//初始化人数
	minn=maxn=0;//与初始人数一致 
	for(int i=1;i<=n;++i)
	{
		x=read();now+=x;//更新人数
		maxn=max(maxn,now);//更新最大值
		minn=min(minn,now);//更新最小值 
	}
	l=-minn;//最少需要加上的人数就是之前过程中人数最少的一次 
	r=w-maxn;//最多可以加上的人数就是最多的人数基础上还可以加多少人
	if(l>r)puts("0");//不合法的情况 
	else printf("%d\n",r-l+1);//区间长度 
	return 0;//养成好习惯 
}
```


---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF978E)

# 思路

上下车的人数都有人数限制，上限是$\ w$，下限是$\ 0$。

每一次的人数都有可能，计算出区域的 $\max$ 与 $\min$ 即可。

AC 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int n,w,a;
long long sum,maxN,minN;
int main()
{
    cin>>n>>w;
    for(int i=1;i<=n;i++)
    {
        cin>>a;sum+=a;
        maxN=max(sum,maxN);minN=min(sum,minN);
    }
    cout<<max(0LL,w-maxN+minN+1);
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/111159064)

---

## 作者：_Kouki_ (赞：0)

### 题目思路：

这是一道思维题。   
假设车上原有 $ x $ 人，车上最少是有 $ minn $ 人，车上最多是有 $ maxn $ 人。

因为 $ maxn\le w \ \ \&\&\ \ 0 \le minn $，求这个范围内的整数解，即 $ w-maxn+minn+1 $ 。  

但如果值 $ < 0$ 则无解，输出 $ 0 $。

### 题目代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll w,maxn,minn,s;
int main()
{
    scanf("%d%lld",&n,&w);
    s=0;
    for(int i=1;i<=n;++i){
        ll x;
        scanf("%lld",&x);
        s+=x;
        minn=min(minn,s);
        maxn=max(maxn,s);
    }
    printf("%lld",max((ll)0,w-maxn+minn+1));
    // cin>>n;
    return 0;
}
```

---

## 作者：MC小萌新 (赞：0)

### 题目分析
既然公交车上的人数在 $ (0,w) $ 之间，设一开始的值为 $ ans $，那么 $ 0≤ans+x_i+sum_{i-1}≤w $，所以 $ ans $ 的最小值就为 $ 0-x_i-sum_{i-1} $，最大值为 $ w-x_i-sum_{i-1} $。求出这之间有多少数即为答案数量。

当任一时刻最小值大于最大值时，说明无解，输出 $ 0 $ 即可。

### 代码实现
注意一开始 $ ans $ 取值也在 $ 0 $ ~ $ w $ 之间。
```cpp
#include <iostream>
using namespace std;
int x,n,w,sum,ansl,ansr;
int main(){
    cin>>n>>w;
    ansr=w;
    for(int i=1;i<=n;++i){
        cin>>x;
        sum+=x;//0<=ans+sum<=w
        ansl=max(ansl,0-sum);
        ansr=min(ansr,w-sum);
        if(ansl>ansr){
            cout<<0<<endl;
            return 0;
        }
    }
    cout<<ansr-ansl+1<<endl;
    return 0;
}
```


---

## 作者：WsW_ (赞：0)

特别水，直接模拟即可。  
不算一开始的初始人数，只统计每次上下车之后的人数，并记录其中的最大值 $max$ 和最小值 $min$ 。  
如果最大值与最小值的差大于巴士最多能容纳的人数，即 $max-min>w$ 说明无论怎样，总会有两个时刻的人数差超过巴士最大容量，所以一定不可行，输出 $0$ 。  
否则，则是一定有解，解的数量相当于把连续的 $(max-min)$ 个物品放进 $n$ 个格子里，数量为 $w-(max-min)+1$ 。 
## 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开long long 见祖宗
int n,w;
int a;
int miin,maax;
int sum;
signed main(){
	scanf("%lld%lld",&n,&w);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a);
		sum+=a;
		miin=min(miin,sum);//统计最大与最小
		maax=max(maax,sum);
	}
	if(maax-miin>w){//无解
		printf("0");
		return 0;
	}
	printf("%lld",w-(maax-miin)+1);//输出解的数量
	return 0;
} 
```

---

## 作者：tonyre (赞：0)

## CF978E 题解

时间限制 $ 1s $​​   |   空间限制 $ 256M $​​



#### 题目描述：

有一辆巴士，开始车上的人数未知，巴士会经过 $n$ 个站点，巴士最多能容纳的人数为 $w$，给出在每个站点的上下车人数，任何时刻车上的人数都应该在 $0$ 到 $w$ 之间，求出车上一开始人数的可能方案数。如果方案不存在，输出 $0$。



#### 输入格式：

第一行，包含两个整数 $n(1\le n\le 1000), w(1\le w\le 10^9)$​​，分别表示经过的站点数和最大载人数。

接下来一行包含 $n$ 个整数，$a_1, a_2, a_3,...,a_n(-10^6\le a_i\le 10^6)$，$a_i$​​ 表示在第 $i$​ 站的净上车人数。



#### 输出格式：

输出一个整数，表示车上一开始人数的可能方案数，若方案不存在，输出 $0$​。

#### 解题思路：

假设开始没有乘客，统计每一站巴士内的乘客数 $p_i$，在保证开始时的乘客数 $k$ 大于等于 $0$ 的前提下，使得 $0\le k + p_i\le w, 1\le i\le n$。统计满足条件的乘客数 $k$ 的数量，即 $k$ 满足 $0\le \min(p_1, p_2,..., p_n) + k$ 且 $\max(p_1, p_2,..., p_n) + k\le w$。由此可求出 $k$ 的最小值和最大值，即可求出总情况数 $cnt = \max(0, w - \max(p_1, p_2,..., p_n) + \min(p_1, p_2,..., p_n) + 1)$。

#### 参考代码：

不开 `long long` 见祖宗。

```c++
#include<iostream>
using namespace std;
long long p,maxp,minp;
int main()
{
    int n,w;
    cin>>n>>w;
    for(int i=1;i<=n;i++)
    {
        int a;
        cin>>a;
        p+=a;
        maxp=max(maxp,p);
        minp=min(minp,p);
    }
    cout<<max((long long)0,w-maxp+minp+1);
    return 0;
}
```



---

