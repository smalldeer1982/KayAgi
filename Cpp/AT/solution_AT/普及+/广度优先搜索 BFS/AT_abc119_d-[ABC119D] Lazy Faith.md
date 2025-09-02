# [ABC119D] Lazy Faith

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc119/tasks/abc119_d

東西方向に伸びる道路に沿って $ A $ 社の神社と $ B $ 軒の寺が建っています。 西から $ i $ 社目の神社は道路の西端から $ s_i $ メートルの地点に、西から $ i $ 軒目の寺は道路の西端から $ t_i $ メートルの地点にあります。

以下の $ Q $ 個の問いに答えてください。

問 $ i $ ($ 1\ \leq\ i\ \leq\ Q $): 道路の西端から $ x_i $ メートルの地点から出発して道路上を自由に移動するとき、神社一社と寺一軒を訪れるのに必要な最小の移動距離は何メートルか？ (必要数を超えた数の寺社を通過してもよい。)

## 说明/提示

### 制約

- $ 1\ \leq\ A,\ B\ \leq\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 1\ \leq\ s_1\ <\ s_2\ <\ ...\ <\ s_A\ \leq\ 10^{10} $
- $ 1\ \leq\ t_1\ <\ t_2\ <\ ...\ <\ t_B\ \leq\ 10^{10} $
- $ 1\ \leq\ x_i\ \leq\ 10^{10} $
- $ s_1,\ ...,\ s_A,\ t_1,\ ...,\ t_B,\ x_1,\ ...,\ x_Q $ はすべて異なる。
- 入力される値はすべて整数である。

### Sample Explanation 1

$ 2 $ 社の神社と $ 3 $ 軒の寺があり、神社は道路の西端から $ 100,\ 600 $ メートルの地点に、寺は道路の西端から $ 400,\ 900,\ 1000 $ メートルの地点にあります。 - 問 $ 1 $: 道路の西端から $ 150 $ メートルの地点から出発する場合、まず西に $ 50 $ メートル進んで神社を訪れ、次に東に $ 300 $ メートル進んで寺を訪れるのが最適です。 - 問 $ 2 $: 道路の西端から $ 2000 $ メートルの地点から出発する場合、まず西に $ 1000 $ メートル進んで寺を訪れ、次に西に $ 400 $ メートル進んで神社を訪れるのが最適です。途中で寺をもう一軒通過しますが、構いません。 - 問 $ 3 $: 道路の西端から $ 899 $ メートルの地点から出発する場合、まず東に $ 1 $ メートル進んで寺を訪れ、次に西に $ 300 $ メートル進んで神社を訪れるのが最適です。 - 問 $ 4 $: 道路の西端から $ 799 $ メートルの地点から出発する場合、まず西に $ 199 $ メートル進んで神社を訪れ、次に西に $ 200 $ メートル進んで寺を訪れるのが最適です。

### Sample Explanation 2

道路は長く、$ 32 $ ビット整数に収まらない距離を移動する必要があるかもしれません。

## 样例 #1

### 输入

```
2 3 4
100
600
400
900
1000
150
2000
899
799```

### 输出

```
350
1400
301
399```

## 样例 #2

### 输入

```
1 1 3
1
10000000000
2
9999999999
5000000000```

### 输出

```
10000000000
10000000000
14999999998```

# 题解

## 作者：c60521c (赞：17)

蒟蒻第一次写题解

简单说一下运用的算法

这道题主要就是用二分，其中有lower_bound的算法简单介绍一下

lower_bound(a+1,a+n+1,key) 下界 找到第一个大于等于key的地址

再说一下这道题的主要思路：

first step：用lower_bound找出最近的shrine和temple

second：会发现可以找出四个，左shrine，右 shrine，左temple，右temple

third：同侧取max，不同侧考虑就要来回

final：四种情况去min，完美结束

下面正片开始：

```cpp
#include<cstdio>
  
#include<cmath>
  
#include<algorithm>
  
using namespace std;

long long a[100005],b[100005];//不多说 一定要longlong

int main() {

	int n,m,x,y,t;
	long long k;

	scanf("%d%d%d",&n,&m,&t);

	for(int i=0;i<n;i++)//i一定要从0开始 不然只过1个点 ~~惨痛的教训~~
    	scanf("%lld",&a[i]);//输入建议用scanf cin会慢一些
	for(int i=0;i<m;i++)
    	scanf("%lld",&b[i]);

	long long  ans;

	while(t--)//t次查找
	{
    	scanf("%d",&k);

    	x=lower_bound(a,a+n,k)-a;//二分搜 注意减
    	y=lower_bound(b,b+m,k)-b;
    	ans=1e16;

    //以下分四种情况讨论 ~~自认为比较简单？~~
    	if(x<n&&y<m)//神社和寺庙都在左
    	{
        	ans=min(ans,max(a[x],b[y])-k);
    	}
    	if(x>0&&y>0)//神社寺庙都在右
    	{
        	ans=min(ans,k-min(a[x-1],b[y-1]));
    	}
    	if(x>0&&y<m)//神社左寺庙右
    	{
        	ans=min(ans,b[y]-a[x-1]+min(k-a[x-1],b[y]-k));
    	}
    	if(y>0&&x<n)//寺庙左神社右
    	{
        	ans=min(ans,a[x]-b[y-1]+min(k-b[y-1],a[x]-k));
    	}
    	printf("%d\n",ans);
	}
	return 0;
} //完美结束
```


先别走！

为您们再奉上几个有关二分查找的函数
```cpp
//upper_bound(a+1,a+n+1,key) 上界 找到第一个大于key的地址
```

```cpp
upper_bound(a+1,a+n+1,key)-lower_bound(a+1,a+n+1,key) 求key在数组中的个数
```

另外还有个自己写的二分查找的小函数

```cpp
int bs(long long a[],long long key)

{

int low=1,high=n;                  
while(low<=high)
    {
        int mid=(low+high)/2;
        if(a[mid]==key)
            return mid;
        else if(a[mid]<key)
            low=mid+1;
        else
            high=mid-1;
    }
return -1;
}
```
就这样了 不妨点个赞再走（卑微

第4次提交，排版应该没问题了，求过.jpg

---

## 作者：AgrumeStly (赞：5)

AT4303 [ABC119D] Lazy Faith[题解][二分]
=

> [AT4303](https://www.luogu.com.cn/problem/AT4303)

translation
-

有 $a$ 个点 $s$，有 $b$ 个点 $t$，问从点 $x$ 出发到达至少一个 $a$ 和一个 $b$ 的最短距离是多少。

solution
-

我们先举一个简单的例子，假如我们有 $2$ 个点 $s$ 分别在 $3,6$ 和 $2$ 个点 $t$ 分别在 $2,5$，$x$ 从 $4$ 出发。

先画一个图更好的理解

![1](https://i.loli.net/2020/11/15/7spJN9YZVDUqKP6.png)

那么我们现在有 $4$ 种选择：

- 选择 $s_1$ 和 $t_1$
- 选择 $s_2$ 和 $t_2$
- 选择 $s_1$ 和 $t_2$
- 选择 $s_2$ 和 $t_1$

那么可以想想，还有其他的选择吗？并没有！

因为要选择最短的路线，如果在 $t_1$ 左边或 $s_2$ 右边还有点的话，若选择它肯定距离长，肯定要舍。

所以总结，只有这四种选法：

- 左 $s$ 左 $t$
- 右 $s$ 右 $t$
- 左 $s$ 右 $t$
- 右 $s$ 左 $t$

所以只要将这 $4$ 种选法都算出来，取 $\min$ 即可。

那如何算？

第一个问题：

如何找到在 左/右 边离 $x$ 最近的 $s/t$？

这里我们就要用到 **二分**

~~众所周知~~ 用二分可以用 `lower_bound` 和 `upper_bound` 函数。

我们在这里简单介绍一下这两种函数。

- `lower_bound`  
	此函数通过二分的原理，在 $a$ 数组中找到第一个 $\leq x$ 的数。  
    使用：`lower_bound(a + 1, a + n + 1, x)`
- `upper_bound`  
	使用方法与 `lower_bound` 类似，但是找到第一个 $\le x$ 的数。
    
那么我们找到在 左/右 边离 $x$ 最近的 $s/t$ 就很容易了。

code
-

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#define int long long
using namespace std;

const int NR = 1e5 + 5;
int a, b, q;
int s[NR], t[NR];

void solve() {
	int x;
	cin >> x;
	int ss = lower_bound(s + 1, s + a + 1, x) - s;
	int sm = lower_bound(t + 1, t + b + 1, x) - t;
	int ans = 9e18;
	//左社左寺
	if (ss > 1 && sm > 1) {
		ans = min(ans, max(x - s[ss - 1], x - t[sm - 1]));
	}
	//右社右寺
	if (ss <= a && sm <= b) {
		ans = min(ans, max(s[ss] - x, t[sm] - x));
	}
	//左社右寺
	if (ss > 1 && sm <= b) {
		if (x - s[ss - 1] <= t[sm] - x) //如果左比右近或两边距离出发点相等，就先走左边
			ans = min(ans, (x - s[ss - 1]) * 2 + (t[sm] - x));
		else
			ans = min(ans, (t[sm] - x) * 2 + (x - s[ss - 1]));
	}
	//右社左寺
	if (ss <= a && sm > 1) {
		if (s[ss] - x <= x - t[sm - 1]) //如果右比左近，就先走右边
			ans = min(ans, (s[ss] - x) * 2 + (x - t[sm - 1]));
		else
			ans = min(ans, (x - t[sm - 1]) * 2 + (s[ss] - x));
	}
	cout << ans << endl;
	return;
}

signed main() {
	cin >> a >> b >> q;
	for (int i = 1; i <= a; i++) cin >> s[i];
	for (int i = 1; i <= b; i++) cin >> t[i];
	sort(s + 1, s + a + 1);
	sort(t + 1, t + b + 1);
	while (q--) solve();
	return 0;
}
```

---

## 作者：qss_ (赞：4)

一道二分练习题，思维难度较大。

### 思路
先把所有的建筑物排序一遍，一共只有四种情况：

1.去最靠近自己的**左**边的神社和寺庙（神社，寺庙可互换）

![](https://cdn.luogu.com.cn/upload/image_hosting/em39w23u.png)

可以发现，最短路程是**离你远的那一个**到你的距离

2.去最靠近自己的**右**边的神社和寺庙（神社，寺庙可互换）

![](https://cdn.luogu.com.cn/upload/image_hosting/tc94t0h8.png)

可以发现，最短路程还是**离你远的那一个**到你的距离


3.去最靠近自己的**左**边的神社和最靠近自己的**右**边的寺庙（神社，寺庙**不**可互换）

![](https://cdn.luogu.com.cn/upload/image_hosting/1r8jvl9d.png)

这时候就有意思了，你会发现你总会走寺庙和神社之间的路程，但是先去离你近的会让总路程更少

最短路程是**离你近的那一个**到你的距离**加上两者之间**的距离

4.去最靠近自己的**右**边的神社和最靠近自己的**左**边的寺庙（神社，寺庙**不**可互换）

![](https://cdn.luogu.com.cn/upload/image_hosting/yp847aog.png)

这时候就又有意思了，你会发现你又总会走寺庙和神社之间的路程，但是先去离你近的又会让总路程更少

最短路程还是**离你近的那一个**到你的距离**加上两者之间**的距离

### 总结

最近的神庙：$s$ (shenmiao)

最近的神庙：$t$ (temple)

你的位置：$q$

左神社左寺庙：$max(q-s,q-t)$

右神社右寺庙：$max(s-q,t-q)$

左神社右寺庙：$max(q-s,t-q)$

右神社左寺庙：$max(s-q,q-t)$

### 实现

STL人，STL魂，STL都是大懒人！

我们当然是用$lower\_bound$来实现（偷懒）啦！

$lower\_bound(1, r, key)$会返回该数组中下标$l$与$r$之间第一个**大于等于**$key$的数的**下标**，如果没有，**返回的下标不在$l$和$r$之间**

具体$l$和$r$的用法有点像$sort$，详见下方代码

我们可以利用这个来找出最靠近右边的建筑

左边只需要下标$-1$（第一个小于等于$key$的前一个数就是最后一个大于$key$的）

**注意：该函数不会默认将数组排序**，所以需要手动加上$sort$，还要**特判**哦

这里就不展开啦~如想了解更多去翻别人的$blog$吧~

-----

### 代码：

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
#define LL long long
// lower_bound <= 注意，是小于等于

LL A, B, Q;
LL a[100005], b[100005], q;

int main()
{
	scanf("%lld%lld%lld", &A, &B, &Q);
	for (int i = 1; i <= A; i++)
		scanf("%lld", &a[i]);
	for (int i = 1; i <= B; i++)
		scanf("%lld", &b[i]);
		
	sort(a+1, a+A+1);// 别忘sort
	sort(b+1, b+B+1);
		
	while (Q--)// 查询次数
	{
		scanf("%lld", &q);// 每次的位置
		LL sa = lower_bound(a+1, a+A+1, q) - a;// 最靠近的神社
		LL sb = lower_bound(b+1, b+B+1, q) - b;// 最靠近的寺庙
		LL ans = 9223372036854775807;// 防被卡（笑
		if (sa <= A && sb <= B)// 左神社左寺庙
			ans = min(ans, max(a[sa] - q, b[sb] - q));
		if (sa > 1 && sb > 1)// 右神社右寺庙
			ans = min(ans, max(q - a[sa-1], q - b[sb-1]));
		if (sa <= A && sb > 1)// 左神社右寺庙
			ans = min(ans, a[sa] - b[sb-1] + min(a[sa] - q, q - b[sb-1]));
		if (sa > 1 && sb <= B)// 右神社左寺庙
			ans = min(ans, b[sb] - a[sa-1] + min(q - a[sa-1], b[sb] - q));
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：CCX_CoolMint (赞：1)

关于这道题，题解区全都是二分的做法，在这里我提供一个不需要二分的方法且非常好理解！

首先我们考虑一个坐标如何达到目标，即前往一家神社和一家寺庙。发现最优情况只有可能是如下四种情况之一：

- 前往该坐标左侧的神社和左侧的寺庙
- 前往该坐标右侧的神社和左侧的寺庙
- 前往该坐标左侧的神社以后，立马折回，向右前往该坐标右侧的寺庙**或**前往该坐标右侧的寺庙以后，立马折回，向左前往该坐标左侧的神社
- 前往该坐标左侧的寺庙以后，立马折回，向右前往该坐标右侧的神社**或**前往该坐标右侧的神社以后，立马折回，向左前往该坐标左侧的寺庙

这是显然的。那么对于这四种情况，它们所花费的移动距离是多少？令左侧神社为 $Ls$，左侧寺庙为 $Lt$，右侧神社为 $Rs$，右侧寺庙为 $Rt$。$X$ 表示一座神社或一座寺庙与该坐标的距离，那么对应的四种情况的移动距离如下：

- $max(X_{Ls},X_{Lt})$
- $max(X_{Rs},X_{Rt})$
- $min(2X_{Ls}+X_{Rt},2X_{Rt}+X_{Ls})$
- $min(2X_{Lt}+X_{Rs},2X_{Rs}+X_{Lt})$

这样就做完了。时间复杂度瓶颈在排序，为 $O(n log n)$，其中 $n=A+B+Q$.

关于具体实现，可以先将所有的坐标（包括神社、寺庙以及询问三种类型的坐标）做上标记（标记他们属于什么类型的坐标），再进行排序。之后对于每一个询问类型的坐标，从前往后、从后往前遍历两遍，找到它们左侧、右侧的神社、寺庙。然后像上面一样计算他们所需要的移动距离，四种情况取最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a,b,q,la,lb,ra,rb,ans;
struct node
{
	ll id,x;
	char op;
}c[1001000];
struct node2
{
	ll la,lb,ra,rb;
}tj[1001000];
bool cmp(node u,node v)
{
	return u.x<v.x;
}
int main()
{
	cin>>a>>b>>q;
	for(int i=1;i<=a;i++) cin>>c[i].x,c[i].op='A';
	for(int i=a+1;i<=a+b;i++) cin>>c[i].x,c[i].op='B';
	for(int i=a+b+1;i<=a+b+q;i++)
	{
		cin>>c[i].x;
		c[i].id=i-a-b;
	}
	sort(c+1,c+1+a+b+q,cmp);
	for(int i=1;i<=a+b+q;i++)
	{
		if(!c[i].id)
		{
			if(c[i].op=='A') la=c[i].x;
			else lb=c[i].x;
		}
		else
		{
			if(la) tj[c[i].id].la=c[i].x-la;
			else tj[c[i].id].la=-1;
			if(lb) tj[c[i].id].lb=c[i].x-lb;
			else tj[c[i].id].lb=-1;
		}
	}
	for(int i=a+b+q;i>=1;i--)
	{
		if(!c[i].id)
		{
			if(c[i].op=='A') ra=c[i].x;
			else rb=c[i].x;
		}
		else
		{
			if(ra) tj[c[i].id].ra=ra-c[i].x;
			else tj[c[i].id].ra=-1;
			if(rb) tj[c[i].id].rb=rb-c[i].x;
			else tj[c[i].id].rb=-1;
		}
	}
	for(int i=1;i<=q;i++)
	{
		ans=LLONG_MAX;
		if(tj[i].la!=-1&&tj[i].lb!=-1) ans=min(ans,max(tj[i].la,tj[i].lb));
		if(tj[i].ra!=-1&&tj[i].rb!=-1) ans=min(ans,max(tj[i].ra,tj[i].rb));
		if(tj[i].la!=-1&&tj[i].rb!=-1) ans=min(ans,min(tj[i].la*2+tj[i].rb,tj[i].rb*2+tj[i].la));
		if(tj[i].ra!=-1&&tj[i].lb!=-1) ans=min(ans,min(tj[i].ra*2+tj[i].lb,tj[i].lb*2+tj[i].ra));
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Black_Porridge (赞：1)

~~在whk的追杀下仓促写下此题解~~

## 解题思路：

我认为本题的关键步骤有两个：

- 分别查找起点左边和右边最靠近起点的神社和寺庙；
- 分类讨论行走的情况。

第一个问题很好解决。由于此题的数据可能到达 $10^5$ 数量级，所以显然我们不能使用 $O(n^2)$ 的爆力查找，而应该运用二分查找，使程序的时间复杂度降至 $O(n$ $logn)$ 。这里我们可以使用 $lower$_ $bound$ 函数查找到起点右侧最靠近它的寺庙 $x_i$ 和神社 $y_j$，而左侧最靠近它的寺庙和神社自然就是 $x_{i-1}$ 和$y_{j-1}$了。

第二个问题可以分四种情况讨论：社左庙左；社左庙右；社右庙左；社右庙右。我们只需保证在起点左侧的寺庙或者神社的下标大于 $0$ ，右侧的小于等于 $a$ 或者 $b$ 即可。具体实现可参照代码。

## 代码：

```
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
const int N = 1e5 + 10;

int a, b, q, maxx, maxy;

long long x[N], y[N];

int main()
{
	cin >> a >> b >> q;
	for(int i = 1; i <= a; i++)
		cin >> x[i];
	for(int i = 1; i <= b; i++)
		cin >> y[i];
	sort(x + 1, x + a + 1);
	sort(y + 1, y + b + 1); 
	for(int i = 1; i <= q; i++)
	{
		long long k, ans = 9e18;
		cin >> k;
		int x1 = lower_bound(x + 1, x + a + 1, k) - x, y1 = lower_bound(y + 1, y + b + 1, k) - y;
		//l x l y
		if(x1 > 1 and y1 > 1)
		ans = min(ans, k - min(x[x1 - 1], y[y1 - 1]));
		//l x r y
		if(y1 <= b and x1 > 1)
		ans = min(ans, min(k - x[x1 - 1], y[y1] - k) + abs(x[x1 - 1] - y[y1]));
		//l y r x
		if(x1 <= a and y1 > 1)
		ans = min(ans, min(x[x1] - k, k - y[y1 - 1]) + abs(x[x1] - y[y1 - 1]));
		//r x r y
		if(x1 <= a and y1 <= b)
		ans = min(ans, max(x[x1] - k, y[y1] - k));
		cout << ans << endl;
		 
	} 
	return 0;
 } 

---

