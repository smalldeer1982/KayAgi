# Cozy Glow之拯救小马国

## 题目背景

本题难度普及-，请noip两个组别的选手都把它AC（~~不然你noip省三都保不住了~~）

ps：三年OI一场空，day1T1见祖宗。。。

## 题目描述

Cozy Glow偷偷摸摸的造了一个魔法阵，这个魔法阵在吸取小马国的魔力，所以你得赶紧把它毁掉。

这个魔法阵由若干个神器组成，每个神器都有一个法力值，每两个神器之间也都有一个关联值。你要依次把这些神器拿走，但是，每拿走一个神器，你就会受到一定量的反噬，反噬的量为这个神器与其他还在神器的关联值乘以这个神器的法力值，为了减少反噬，tb148需要拿走每个神器，但由于他贪生怕死，他想让他受到的反噬值之和最小，现在tb148想知道，怎样拿走神器，才能让反噬值的和最小。

## 说明/提示

神器个数<=1000

所有其他的值<=2000000

正对角线上的数保证都是零。。。

## 样例 #1

### 输入

```
4
2 5 1 7
0 343 154 12
343 0 214 132
154 214 0 441
12 132 441 0```

### 输出

```
2179```

# 题解

## 作者：beargeng是女孩子 (赞：14)

这道题么……水的要死。
先上代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n,a[1005],ans,tmp;
int main()
{
    cin>>n;
    for(long long i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(long long i=1;i<=n;i++)
    {
        for(long long j=1;j<=n;j++)
        {
            cin>>tmp;
            if(i>j)
            	ans+=tmp*min(a[i],a[j]);
        }
    }
    cout<<ans;
    return 0;
}
```
先排序一下i>j的时候就直接乘一下就行了啊。
不用快读可以AC。
直接读入TMP之后乘……
不说太多了。

---

## 作者：Last_hope (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P5132)

### 题意
给你几个法器，告诉你它们的法力值，再告诉你他们的关联值，让你把法器全拆了，拆一个的反噬值等于所有和它相连关联值的和乘它的法力值，要反噬值最小。
### 思路
本想用搜索的来着，结果提交后全超时了，只好换了个做法。

你可以从关联值入手，这个关联值连的两个法器是肯定要乘一个的，为了让反噬值最小，当然要乘小的那一个，所以，答案不就出来了么。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, a[1005], v, ans;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//可以加速cin、cout的黑科技
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
		{
			cin >> v;
			if(i > j)//不重复计算，所以判断一下
				ans += v * min(a[i], a[j]);//挑小的乘
		}
	cout << ans;
	return 0;
}
```



---

## 作者：盖矣斌峥 (赞：5)


[本人博客](https://prime.design.blog/)

   题目说拿走每个神器受到反噬值为关联值乘上法器的法力值

   换一种思路，其实就是对于每一个关联值，要乘上它所连接的两个法器中的一个的法力值
   
   又因为想要值最小，所以对于每一个关联值乘上它所连接的法器中法力值小的一个，全部加起来就是答案
   

------------

   注意不要把每个关联值累加两次
   
```
 if(i>j)
 	ans+=(LL)x*min(a[i],a[j]);
```


------------
见代码：

```
#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
int n,a[1005];
long long ans=0;
int main()
{
	scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
        	int x;
           	scanf("%d",&x);
            	if(i>j)
              	  ans+=(LL)x*min(a[i],a[j]);
        }
    printf("%lld",ans);
    return 0;
}
```


---

## 作者：AmadeusSG (赞：3)


1.因为每个法器是必须拿的，**所以说同一种拿法按不同顺序最终反噬值相等** 

2.既然这道题要取到最小值，所以让**关联值乘关联法器中法力最小**的就可以了

3.***解释一下if（i>j），因为邻接矩阵输入，所以相同两件法器会关联两次，
i>j就是一种限定，只关联一次，否则结果就会*2**

标程：


```
#include<bits/stdc++.h>
#define ll long long//不开long long见祖宗 
using namespace std;
ll n,about,ans;
ll magic[2000005];
int main()
{
	scanf("%lld",&n);
	for(ll i=1;i<=n;++i)scanf("%lld",&magic[i]);
	for(ll i=1;i<=n;++i)
		for(ll j=1;j<=n;++j)
		{
			scanf("%lld",&about);
			if(i>j)ans+=about*min(magic[i],magic[j]);
		}
	printf("%lld",ans);
	return 0;
}
```




---

## 作者：No_Rest (赞：1)

## 题目分析

如果你仔细分析，这道题还是很水的。我们可以用逆向思维，尝试取消关联线来拿走神器。每取消一条关联线就需要把他相邻的两个神器中的一个给拿走。明显，我们要取法力值小的那个。剩下细节详见代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, x, ans, a[1005];
int main(){
	scanf("%lld", &n);//输入
	for(int i = 1; i <= n; i++){
		scanf("%lld", &a[i]);
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin >> x;//这里不用数组，用变量省空间
			if(i > j){//防止重复
				ans += x * min(a[i], a[j]);//加上较小的那个法力值
			}
		}
	}
	printf("%lld", ans);//输出
	return 0;//好习惯
}
```

---

## 作者：Lonely_NewYear (赞：1)

# P5132 题解

## 题目分析

对于一个关联值，和它对应的两个神器（设为 $i$ 和 $j$），如果神器 $i$ 比神器 $j$ 先拿出来，那么最终答案就会加上这个关联值乘上 $i$ 的法力，反之同理。所以为了使答案最小就要让这个关联值乘上 $i$ 和 $j$ 的法力值中较小的一个，这就保证了正确性。可行性呢？只要以神器的法力值排序来取就可以得到上述的效果。

最后注意每个关联值会出现两次，最后只需要统计一次。

### tips

1. 数据原因导致快读用了一定会 TLE

1. 还是数据原因，导致如下写法只有第一种正确

- 对于矩阵只统计左下部分的答案

- 对于矩阵只统计右上部分的答案

- 整个矩阵都统计，最后答案除以 $2$

## 代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long a[1001];
int main()
{
	int n,x;
	scanf("%d",&n);
	long long ans=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&x);
			if(i>j)ans+=x*min(a[i],a[j]);
		}
	printf("%lld",ans);
	return 0;
}
```

谢谢观看！

---

## 作者：Kiloio (赞：1)

# 目标：反噬值最小  
方法：  法器**必须要拿**，反噬值又要最小，让法力**相对最小的**乘上**关联值**即可。  

注意事项：  因为鄙人用的**邻接矩阵**，关联值会重复，所以加了$i>j$的限定。  

比如样例简化版：  
$0$ $3$ $1$ $1$   
$3$ $0$ $2$ $1$   
$1$ $2$ $0$ $4$   
$1$ $1$ $4$ $0$  
  
**加了**$i>j$的限定条件后，所代表的**意义相同**~~（长得还是不一样）~~：     
$3$   
$1$ $2$  
$1$ $1$ $4$  

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
long long n,x,ans,a[2000005];//a数组存的法器的法力 
int main(){
	cin>>n;
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){		
			scanf("%lld",&x);//没用2维数组存，但实际是跟邻接矩阵的存法一样 
			if(i>j){
				ans+=x*min(a[i],a[j]);//min取得相对最小 
			}
		}
	}		
	cout<<ans;
	return 0;
}
```


---

## 作者：yf最qhhh (赞：1)

~~这道题不该是蓝题吧~~

思路很简单，反正每个都要拿，那么输入关联的值的时候就直接用那个值 $\times$ 两个神器中反噬小的那个就行了。

代码：
```cpp
#include<cstdio>
#include<algorithm>
#define ll long long
#define rll register long long
ll arr[1000005];
int main(){
	rll n,i,j,tmp,ans=0;
	scanf("%lld",&n);
	for(i=1;i<=n;i++)scanf("%lld",&arr[i]);输入
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
			scanf("%lld",&tmp);
			ans+=i>j?tmp*std::min(arr[i],arr[j]):0;//之所以要判断一次i>j是因为不然就会被算两次。
		}
	printf("%lld",ans); 
	return 0;
}

```


---

## 作者：EAlivn (赞：1)

~~拯救马保国~~ 

我承认第一眼我看成了这个，但是后来看到题发现是一道水题直接 $A$ 掉


**注意**

题目说拿走每个神器受到反噬值为关联值乘上法器的法力值。

对于每一个关联值，要乘上它所连接的两个法器中的一个的法力值。

又因为想要值最小，所以对于每一个关联值乘上它所连接的法器中法力值小的一个，全部加起来就是答案。

**代码**


```C++
#include<bits/stdc++.h>
using namespace std;
long long faqi[2000005]; //faqi 指法器的法力
inline long long read(){
	long long a;
	scanf("%lld",&a);
	return a;
}
int main() {
	long long n=read();
	for(long long i=1; i<=n; i++) faqi[i]=read();
	long long ans=0;
	for(long long i=1; i<=n; i++){
		for(long long j=1; j<=n; j++) {
			long long tmp=read();
			if(i>j) ans+=tmp*((faqi[i]<=faqi[j])?faqi[i]:faqi[j]);
		}
	}
	printf("%lld\n",ans);
}
```




---

## 作者：_FJX_ (赞：0)

题目要求求出拿走每个神器受到反噬值为关联值乘上法器的法力值。

其实就是对于每一个关联值，要乘上它所连接的两个法器 $i(1 \leq i \leq n) , j(1 \leq j \leq n)$ 中的一个的法力值。

又因为想要值最小，所以我们对于每一个关联值乘上法器 $i$ 与 $j$ 中最小的一个即可。

注意！

1. 为了防止重复算, 我们在 $i > j$ 的时候就直接如上所述算一下就行了。

2. 不开 long long 见祖宗！

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[1005], ans;
int main(){
    ios_base::sync_with_stdio(false);
	cin.tie (0);
	cout.tie (0);
	ll n; 
	cin >> n;
	for (ll i = 1; i <= n; i ++)
	{
		cin >> a[i];
	}
	for (ll i = 1; i <= n; i ++)
	{
		for (ll j = 1; j <= n; j ++)
		{
			ll x;
			cin >> x;
			if (i > j)
			{
				ans += x * min(a[i], a[j]);
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：Lysea (赞：0)

## 思路

因为最终所有神器都要被拿走，所以可以直接累加结果（好水啊）。

具体累加方法: 因为要求最后的值最小，所以我们要用关联值乘上最小的法力值，在代码中体现为:

```
if(i>j) ans+=q*min(cn[i],cn[j]);
```

因为每两个神器之间的关联值会出现两次，只有 $i>j$ 的时候才能够累加结果，不然得到的结果会是两倍。

## 标程
```
#include<bits/stdc++.h>
#define int long long
#define N 10000005
using namespace std;
int n,q,ans,cn[N];
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&cn[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%lld",&q);
			if(i>j) ans+=q*min(cn[i],cn[j]);
		}
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：XL4453 (赞：0)

首先你好几次都不过的原因可能是数据问题。

这题只能用
```cpp
if(i>j)ans+=min(a[j],a[i])*x;
```
这一写法，其他的非等价写法如
```
printf("%d",ans/2);
//全取最后除以二
```
等其他写法都是不行的（数据问题，别问我怎么知道的）。


------------
解题思路：

先说结论：对于每一个关联值，只需要将其与两关联法器中法力值较小的相乘的和即为答案。

然后给出一个不大严谨的证明：

原题中是要求求出一个排列顺序，使得其法力值与顺序在这个法器之后的所有法器的关联值乘积和最小。

那么，对于一个已经排好序的当前最优方案，考虑在其中塞进一个法器使得其还是下一个状态的最优排列。

这里很容易想到将所有的法力值比他大的法器放到这个的后面，这样一定能使对应的法器和关联值乘积最小。

因此，之前的所有状态也都一定是按照法力值排序的，故不会出现冲突的情况。


------------
代码：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
long long n,a[1005],x;
long long ans;
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%lld",&x);
			if(i>j)
			ans+=min(a[j],a[i])*x;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：lu_run_ting (赞：0)

### 十年OI一场空，不开long long见祖宗

这是一道奇怪的贪心题，不知道为什么，反正不开long long过不了，而且深受大家喜爱的快读开了反而也过不了……（不知道这是什么情况，黑科技？）

-----------------------------废话分割线----------------------------------------------------------------------------

分析：
	
首先观察一下，当每个其实题目所给的每个关联值都会被用到一次且只有一次，因为对于点a来说，任意删掉一个点b之后，与它相连的关联之就会被用掉一次，由于这个点已经被删了，所以就算我们再把点a删掉的时候也用不上这个关联值了。

所以，每个关联值既然都会被用到，那么对于每个关联之来说，只可能乘上这个关联值连接的两头，所以就用其中的一个小的乘上去就好了。

思路：

我们只需要枚举每一个关联值，然后再他两头中挑一个小的乘上去并且加到最终的答案ans里就ok了。

优化：

为了代码更短，我们其实不用把每个关联值存起来，只用边读边算就好了。

易错点：

因为输入的方式为邻接矩阵，所以会有一部分重复，需要去重；

还有就是要开long long。
    
    
    
上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1005;
long long n,score,x[N],ans; 
int main(){
	cin>>n;
	for(long long i=1;i<=n;i++) cin>>x[i];
	for(long long i=1;i<=n;i++)
		for(long long j=1;j<=n;j++){
			cin>>score;
			if(i>j) ans+=score*min(x[i],x[j]);
		}
	cout<<ans<<endl; 
	return 0;
} 
```

---

