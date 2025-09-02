# New Building for SIS

## 题目描述

你正在研究夏季信息学院新建筑的楼层设计。因为你担任着英国秘密情报局的后勤物流任务，所以你十分在乎去往不同位置的路程耗时：了解从演讲室到食堂，或者从健身房到服务器机房的耗时是很重要的。

这个建筑由 $n$ 个塔楼组成，标号为 $1 - n$ ；每个塔楼有 $h$ 层，标号为 $1 - h$ 。任意两个相邻的塔楼间有一条通道（当 $1 \le i \le n - 1$ 时，塔楼 $i$ 与 $i - 1$ 相连）。在第 $x ( a \le x \le b)$ 层上，你可以在与第 $x$ 层相邻的2层移动，或如果第 $x$ 层与相邻的塔楼有通道连通也可移动至其上。离开建筑是不被允许的。

![img](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1020A/f837e8e8bdf323146303fdec0eaae175f05c2066.png)

这个图片解释了 **输入 #1**

你将被给予 $k$ 对位置 $(t_a, f_a), (t_b, f_b)$ ：代表塔楼 $t_a$ 上的第 $f_a$ 层，塔楼  $t_b$ 上的第 $f_b$ 层。

对于每一对位置，你需要确定它们之间的最短耗时。

## 样例 #1

### 输入

```
3 6 2 3 3
1 2 1 3
1 4 3 4
1 2 2 3
```

### 输出

```
1
4
2
```

# 题解

## 作者：Andy_Li (赞：4)

# CF1020A New Building for SIS 题解

## 题意

给定 $n$ 栋高为 $h$ 的楼，相邻的楼之间有 $b-a+1$ 个通道，这 $b-a+1$ 个通道是连续的，从 $a$ 楼一直到 $b$ 楼都有通道，问给定两个点，这两个点的最短路有几步？

## 思路

分类讨论简单题。

想办法将当前的位置移到含有通道的这一层，移到含有通道的这一层后就可以通过通道到达另一个目标点所在的楼。

假设出发点在 $t_a$ 楼的 $f_a$ 层，目标点在 $t_b$ 楼的 $f_b$ 层。

如果 $a \le f_a \le b$，直接从 $t_a$ 移动到 $t_b$ 这栋楼，最短路长度累加 $ \left| t_a-t_b \right|$。

如果 $f_a < a $，将 $f_a$ 移动到 $a$ 层，最短路长度累加 $ \left| a-f_a \right|$。

如果 $f_a > b $，将 $f_a$ 移动到 $b$ 层，最短路长度累加 $ \left| f_a-b \right|$。

当 $t_a = t_b$ 时，最短路长度累加 $ \left| f_a-f_b \right|$。

最后，输出答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+7;
int main()
{
	cin.tie(0);
	std::ios::sync_with_stdio(false);
	//srand((unsigned)time(NULL));
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n,h,x,y,t;
	cin>>n>>h>>x>>y>>t;
	while(t--)
	{
		int sx,sy,fx,fy,ans=0;
		cin>>sx>>sy>>fx>>fy;
		while(sx!=fx)
		{
			if(x<=sy && sy<=y)
			{
				ans+=abs(sx-fx);
				sx=fx;
			}
			else if(sy<x)
			{
				ans+=abs(sy-x);
				sy=x;
			}
			else if(sy>y)
			{
				ans+=abs(y-sy);
				sy=y;
			}
		}
		cout<<ans+abs(sy-fy)<<endl;
	}
	return 0;
}
```

---

## 作者：virtualman (赞：4)

这道题纯模拟的水题，需要分类讨论：  
1. 当在同一栋楼时  
2. 当不在同一栋楼时  
  1. 当fa处于[a，b]之外
  2. 当fa处于[a,b]之间  
  
代码很好理解，顺着代码来即可！
```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string.h>
using namespace std;
int n,h,a,b,k;
int main()
{
    scanf("%d%d%d%d%d",&n,&h,&a,&b,&k);
    while(k--)
    {
        int ta,fa,tb,fb;long long ans=0;
        scanf("%d%d%d%d",&ta,&fa,&tb,&fb);
        if(ta==tb)
            ans+=abs(fb-fa);
        if(ta!=tb)
        {
            ans+=abs(tb-ta);
            if(fa>=a and fa<=b)
            {
                ans+=abs(fb-fa);
            }
            else
            {
                if(abs(fa-a)<abs(fa-b))
                {
                    ans+=abs(fa-a);
                    ans+=abs(a-fb);
                }
                else
                {
                    ans+=abs(fa-b);
                    ans+=abs(b-fb);
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Speech_less (赞：2)

# CF1020A New Building for SIS 题解
  [题目传送门](https://www.luogu.com.cn/problem/UVA10662)

### PART 1：主要思路
题目很简单，唯一的难点就只有中间的分类讨论。

------------
### PART 2：分类讨论
题目中共有四种情况：
1. 当起点与目的地在同一层楼时，即 $f_a=f_b$ 时：

	$$sum = |t_a - t_b| $$
    
2. 当起点与目的地不在同一层楼时，即 $ f_a \neq f_b $ 时，有3种情况：

	+ 当起点在楼层通道之下，即 $ f_a < a $ 时：
    
    $$sum = |t_a - t_b| + |f_b - a| + (a - f_a)$$
    
	解释：价值 $sum = $ 距离：$|t_a - t_b|+$ 终点与通道的距离 $|f_b - a| +$ 通道与起点的距离 $(a - f_a)$。
    
   + 当起点在楼层通道之上，即 $f_a > b$ 时：
   
    $$sum = |t_a - t_b| + |f_b - b| + (f_a - b)$$
    
  	解释：价值 $sum = $ 距离：$|t_a-t_b| + $ 终点与通道的距离 $|f_b - b| + $ 通道与起点的距离 $(f_a - b)$。
    
   + 当起点在楼层通道之间，即 $a \leqslant f_a \leqslant b$ 时：
   
    $$sum = |t_a - t_b| + |f_a - f_b|$$
    
    解释：价值 $sum = $ 距离：$|t_a - t_b| + $ 终点与起点的距离 $|f_a - f_b|$。
    
------------

### AC 代码上交：
```cpp
#include<bits/stdc++.h>
int n,h,a,b,k,ta,fa,tb,fb;
int main(){
	scanf("%d%d%d%d%d",&n,&h,&a,&b,&k);
	for(int i=1;i<=k;i++){
		int sum=0;
		scanf("%d%d%d%d",&ta,&fa,&tb,&fb);
		if(ta==tb) sum=abs(fa-fb);
		else{
			if(fa<a) sum=abs(ta-tb)+abs(fb-a)+(a-fa);
			else if(fa>b) sum=abs(ta-tb)+abs(fb-b)+(fa-b);
			else sum=abs(ta-tb)+abs(fa-fb);
		}
		printf("%d\n",sum);
	}
	return 0;
} 
```

------------

\*注：切记勿抄袭，抄袭马上变棕名。

题外：求管理员大大给过 QwQ。

---

## 作者：saixingzhe (赞：2)

# 分析
简单分讨题。

* 如果在同一栋楼，输出 $|f_a-f_b|$。
* 如果不在同一栋楼：

	1.如果 $f_a<a$，输出 $a-f_a+|t_a-t_b|+|f_b-a|$。

	2.如果 $f_a>b$，输出 $f_a-b+|t_a-t_b|+|f_b-b|$。

	3.如果 $a \leq f_a \leq b$，输出 $|t_a-t_b|+|f_a-f_b|$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,h,a,b,k,ta,fa,tb,fb;
int main(){
	scanf("%d%d%d%d%d",&n,&h,&a,&b,&k);
	for(int i=1;i<=k;i++){
		scanf("%d%d%d%d",&ta,&fa,&tb,&fb);
		if(ta==tb) cout<<abs(fa-fb)<<'\n';
		else{
			if(fa<a) cout<<a-fa+abs(ta-tb)+abs(a-fb)<<'\n';
			else if(fa>b) cout<<fa-b+abs(ta-tb)+abs(b-fb)<<'\n';
			else cout<<abs(fa-fb)+abs(ta-tb)<<'\n'; 
		}
	}
	return 0;
}
```

---

## 作者：_SkyLine_ (赞：1)

模拟即可。
## 思路分析
首先依据 $t_a$ 与 $t_b$ 的关系进行分类讨论。有 $t_a$ 与 $t_b$ 相等、$t_a$ 与 $t_b$ 不等两种关系。

$t_a$ 与 $t_b$ 相等时，即两个位置在同一座塔楼内，只需移动 $|f_a-f_b|$ 即可。输出 $|f_a-f_b|$ 作为答案。

$t_a$ 与 $t_b$ 不等时，按 $f_a$ 与 $a,b$ 的关系分三种情况讨论：

- $f_a > b$ 时，说明位置 $f_a$ 距离 $b$ 层较近，只需在塔楼 $t_a$ 上移动 $f_a-b$ 到达 $b$ 层，再通过 $t_a$ 与 $t_b$ 的通道移动 $|t_a-t_b|$ 到达塔楼 $t_b$，再于塔楼 $t_b$ 的第 $b$ 层上移动 $|b-f_b|$ 即可。输出 $f_a-b+|t_a-t_b|+|b-f_b|$ 作为答案。

- $f_a < a$ 时，说明位置 $f_a$ 距离 $a$ 层较近，只需在塔楼 $t_a$ 上移动 $a-f_a$ 到达 $a$ 层，再通过 $t_a$ 与 $t_b$ 的通道移动 $|t_a-t_b|$ 到达塔楼 $t_b$，再于塔楼 $t_b$ 的第 $a$ 层上移动 $|a-f_b|$ 即可。输出 $a-f_a+|t_a-t_b|+|a-f_b|$ 作为答案。

- $f_a \in [a,b]$ 时，不难发现在两座塔楼上共移动了 $|f_a-f_b|$ 层，通过通道移动了 $|t_a-t_b|$，输出 $|f_a-f_b|+|t_a-t_b|$ 作为答案。

## $\texttt{Code:}$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,h,a,b,k;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> h >> a >> b >> k;
	for(int i=1;i<=k;i++)
	{
		int ta,fa,tb,fb;
		cin >> ta >> fa >> tb >> fb;
		if(ta==tb)
			cout<<abs(fa-fb)<<endl;
		else
		{
			if(fa>b)
				cout<<fa-b+abs(ta-tb)+abs(b-fb)<<endl;
			else if(fa<a)
				cout<<a-fa+abs(ta-tb)+abs(a-fb)<<endl;
			else
				cout<<abs(fa-fb)+abs(ta-tb)<<endl; 
		}
	}
	return 0;
}
```

---

## 作者：expecto__patronum (赞：0)

## 思路
不就是给出长度为 $n$ 的字符串 $1$ 与长度为 $m$ 的字符串 $2$，再给出 $q$ 组 $l$，$r$，求在串 $1$ 区间 $[ l , r ]$ 中有多少个串 $2$ 吗？
### 两种可能
#### 1.当在同一栋楼时。
#### 2.当不在同一栋楼时。
## 现在开始模拟（解释都在注释里）
```
#include <stdio.h>
#include <iostream>
using namespace std;
inline int abs(int a)
{
	if(a<0)
	{
		return -a;
	}
	else
	{
		return a;
	}
}
int main()
{
	ios::sync_with_stdio(false);
    int n,h,a,b,k,ta,fa,tb,fb,ans;
    cin>>n>>h>>a>>b>>k;
    for(int i=1;i<=k;i++)
    {
        cin>>ta>>fa>>tb>>fb;
        ans=0;
        if(ta==tb)//在同一个塔 
		{
			ans=abs(fa-fb);//楼数差
		}
        else if(fa>a&&fa>b&&fb>a&&fb>b)//如果楼层都在天台上面 
        {
        	ans=abs(ta-tb)+abs(fa-fb)+min(fa-b,fb-b)*2;
		}
        else if(fa<a&&fa<b&&fb<a&&fb<b)//如果楼层都在天台下面 
        {
        	ans=abs(ta-tb)+abs(fa-fb)+min(a-fa,a-fb)*2;
		}
        else//位置在最高通道上方
        {
        	ans=abs(ta-tb)+abs(fa-fb);
		}
        cout<<ans<<endl;
    }
    return 0;
}
```
管理员大大求过！！

[博客](https://blog.csdn.net/apro1066/article/details/81697870)

---

## 作者：深度产业观察 (赞：0)

**一道很水的模拟，总共四种情况。**

1、同一栋楼，答案是 $|f_a-f_b|$。

2、不一栋楼，分三种情况：

①、$f_a>b$，答案是 $f_a-b+|t_a -t_b|+|f_b-b|$。

②、$f_a<a$，答案是 $a-f_a+|t_a -t_b|+|f_b-a|$。

③、$a≤f_a≤b$，答案是 $|t_a-t_b|+|f_a-f_b|$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,h,a,b,k;
int ta,tb,fa,fb;
int main(){
	cin>>n>>h>>a>>b>>k;
	while(k--){
		cin>>ta>>fa>>tb>>fb;
		if(ta==tb){
			cout<<abs(fa-fb)<<endl;
		} else{
			if(fa>b){
				cout<<fa-b+abs(ta-tb)+abs(fb-b)<<endl;
			}
			if(fa<a){
				cout<<a-fa+abs(ta-tb)+abs(fb-a)<<endl;
			}
			if(fa>=a&&fa<=b){
				cout<<abs(ta-tb)+abs(fa-fb)<<endl;
			}
		}
	}
	return 0;
}
```




---

## 作者：Fengyiwei1234 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1020A)

# 思路

考虑模拟，分四种情况讨论：
1. 两个地方在同一个楼。答案显而易见是$\ |{t}_{a}-{t}_{b}|$。

1. 当$\ {f}_{a}>b\ $时，此时最优路径应该是从$\ {f}_{a}\ $走到 b，然后从 $\ {t}_{a}\ $的 b 走到$\ {t}_{b}\ $的 b，最后走到$\ {f}_{b}$。

1. 同理，当$\ {f}_{a}<a\ $时，此时最优路径应该是从$\ {f}_{a}\ $走到 a，然后从$\ {t}_{a}\ $的 a 走到$\ {t}_{b}\ $的 a，最后走到$\ {f}_{b}$。

1. 最后一种：${f}_{b}\ $位于 a 和 b 之间，这样的最优路径就是从当前位置走到$\ {t}_{b}\ $的相同位置，然后再走到$\ {f}_{b}\ $处。

AC 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,a,b,k,h,ta,fa,tb,fb;
    cin>>n>>h>>a>>b>>k;//输入
    while(k--)
    {
        cin>>ta>>fa>>tb>>fb;//输入
        if(ta==tb)cout<<abs(fa-fb)<<endl;//分类讨论
        else if(fa>b)cout<<abs(ta-tb)+fa-b+abs(b-fb)<<endl;//分类讨论
        else if(fa<a)cout<<abs(ta-tb)+a-fa+abs(a-fb)<<endl;//分类讨论
        else cout<<abs(ta-tb)+abs(fa-fb)<<endl;//分类讨论
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/109511050)

---

## 作者：sjr3065335594 (赞：0)

## 思路

update 2023-8-22：修改了之前的错误。

我们分四种情况讨论：

1. $t_a=t_b$ 时，答案显而易见，就是 $\left\vert f_a-f_b \right\vert$。
2. $t_a \ne t_b$ 且 $a \le f_a \le b$ 时，先从 $t_a$ 楼走到 $t_b$ 楼，再从 $f_a$ 层走到 $f_b$ 层，总花费 $\left\vert t_a-t_b \right\vert + \left\vert f_a-f_b \right\vert$。
3. $t_a \ne t_b$ 且 $f_a < a$ 时，先从 $f_a$ 层走到 $a$ 层（可以证明走到 $a$ 层之后 $f_b$ 取任何值都能保证花费最小，不明白的话看结尾），再从 $t_a$ 楼走到 $t_b$ 楼，再从 $a$ 层走到 $f_b$ 层，总花费 $a-f_a + \left\vert f_b-a \right\vert+\left\vert t_a-t_b\right\vert$。
4. $t_a \ne t_b$ 且 $f_a > b$ 时，先从 $f_a$ 层走到 $b$ 层（可以证明走到 $b$ 层之后 $f_b$ 取任何值都能保证花费最小，不明白的话看结尾），再从 $t_a$ 楼走到 $t_b$ 楼，再从 $b$ 层走到 $f_b$ 层，总花费 $b-f_a + \left\vert f_b-b \right\vert+\left\vert t_a-t_b\right\vert$。

### 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, h, a, b, k;
int main() {
    cin >> n >> h >> a >> b >> k;
    while(k--) {
        int ta, fa, tb, fb;
        cin >> ta >> fa >> tb >> fb;
        if(ta == tb)//情况1
            cout << abs(fa - fb) << endl;
        else if(fa >= a && fa <= b)//情况2
            cout << abs(ta - tb) + abs(fa - fb) << endl;
        else if(fa < a)//情况3
            cout << a - fa + abs(ta - tb) + abs(fb - a)<< endl;
        else if(fa > b)//情况4
            cout << fa - b + abs(ta -tb) + abs(fb - b) << endl; 
    }
    return 0;//完美结束
}
```

### 证明

当 $t_a \ne t_b$ 且 $f_a < a$ 时，可以分三种情况讨论

1. $f_b<a$ 时，可以想象一下，$f_a$ 和 $f_b$ 都在 $a$ 层的下面，要让花费最小，就从 $f_a$ 层走到 $a$ 层，再从 $a$ 层走到 $f_b$ 层，如果要走到再上一层，就会使花费加上二，不是最优的。
2. $a \le f_b \le b$ 时，走到 $[a,f_b]$ 这个区间中的层数都能保证花费最小。
3. $f_b>b$ 时，走到 $[a,b]$ 这个区间的任何一层花费都相同。

所以走到 $a$ 层总能保证花费最小。

当 $t_a \ne t_b$ 且 $f_a > b$ 时，同理。

---

## 作者：清清老大 (赞：0)

## 思路

当在同一栋楼时，总时间为 $|f_a-f_b|$ 。

当在不同的楼时，分类讨论：

1. 当 $f_a>b$ 时，从 $f_a$ 走到 $b$ ，再去第 $t_b$ 层楼，最后走到 $f_b$ ，总时间为 $(f_a-b)+|t_a-t_b|+|f_b-b|$ 。

2. 当 $f_a<a$ 时，从 $f_a$ 走到 $a$ ，再去第 $t_b$ 层楼，最后走到 $f_b$ ，总时间为 $(a-f_a)+|t_a-t_b|+|a-f_b|$ 。

3. 当 $a \le f_a \le b$ 时，直接前往第 $t_b$ 层楼，最后走到 $f_b$ ，总时间为 $|t_a-t_b|+|f_a-f_b|$ 。

依照上面的步骤模拟即可。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,h,a,b,k;
    cin >> n >> h >> a >> b >> k;
    for(int i = 0;i < k;i ++)
    {
        int ta,fa,tb,fb;
        cin >> ta >> fa >> tb >> fb;
        if(ta == tb)
        {
            cout << abs(fa - fb);
        }
        else
        {
            if(fa > b)
            {
                cout << abs(ta - tb) + (fa - b) + abs(fb - b);
            }
            else if(fa < a)
            {
                cout << abs(ta - tb) + (a - fa) + abs(a - fb);
            }
            else
            {
                cout << abs(ta - tb) + abs(fa - fb);
            }
        }
        cout << endl;
    }
    return 0;
}
```


---

## 作者：Trilliverse (赞：0)

## 本题根据题意模拟即可！
---
### 题目分析：
- 分两大类：

一. 当起始位置都在一栋楼，答案直接为 $abs(fa-fb)$

二. 否则，分三小种情况：

1. 目前所在楼层 fa 在上限 b 的上面（`fa > b`），那么我们就先走到b层，然后再走到终点所在的楼 tb，最后再走到目标楼层 fb 。
2. 目前所在楼层 fa 在下限 a 的上面（`fa < a`），那么我们就先走到a层，然后再走到终点所在的楼 tb，最后再走到目标楼层 fb 。~~和上述思路差不多~~
3. 目前所在位置在 a--b 之间 那么我们可以直接走到目标楼，然后走到目标楼层。

---
 _顺着代码过一遍，更好理解_
 
 ### Code:
```cpp
#include<bits/stdc++.h>
  
using namespace std;

int n,h,a,b,k;

int Gao(int t1,int f1,int t2,int f2) {
  if(t1 == t2) return abs(f1-f2);//判断是否在同一个楼

  //以下内容和分析差不多
  int ans = 0;
  if(f1 > b) {
    ans += (f1-b);
    ans += abs(t1-t2);
    ans += abs(f2-b);
    return ans;
  }
  else if(f1 < a) {
    ans += (a-f1);
    ans += abs(t1-t2);
    ans += abs(f2-a);
    return ans;
  }
  else {
    ans += abs(t1-t2);
    ans += abs(f1-f2);
    return ans;
  }
}

int main() {
  cin >> n >> h >> a >> b >> k;
  while(k--) {
    int ta,fa,tb,fb;
    cin >> ta >> fa >> tb >> fb;
    cout << Gao(ta,fa,tb,fb) << endl;
  }
  return 0;
}
```
~~蒟蒻函数写的比较丑，请见谅~~

---

## 作者：Silencer_jin (赞：0)

## [题面](https://www.luogu.com.cn/problem/CF1020A)
这题不要被题面给吓到，就是一个循环 and 分支结构罢了！纯纯一道~~水~~模拟题。


------------

### 思路：
- 判断是否在同一个楼 （$ta = tb$）。
  - 如果是，输出之间的楼层差 。
  - 否则对临时变量，也就是最终答案 $t$ 进行赋值为楼之间的距离 $abs(ta-tb)$ 。然后，再进行 判断出发楼层是否在 $a ≤ fa ≤ b$ 之间。                           
    - 如果是， $t$ 加上楼层之间的差，并输出 $t$。
    - 否则， 进行判断， 出发楼层距离 $a$ 更近。
      - 如果是， $t$ 加上出发楼层到 $a$ 的距离，再加上终点楼层到 $a$ 的距离。
      - 否则， $t$ 加上出发楼层到 $b$ 的距离，再加上终点楼层到 $b$ 的距离。


------------
代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int n,h,a,b,k;
int main(){
    cin >> n >> h >> a >> b >> k;
    for(int i=1;i<=k;i++){
		int ta,fa,tb,fb;
		cin >> ta >> fa >> tb >> fb;
		if(ta==tb)cout << abs(fa-fb) << endl;
		else{
			int t;
			t=abs(ta-tb);
			if(fa>=a&&fa<=b)t+=abs(fb-fa);
			else{
				if(abs(fa-a)<abs(fa-b))t+=abs(fa-a)+abs(fb-a);
				else t+=abs(fa-b)+abs(fb-b); 
			}
			cout << t << endl;
		}
	}
	return 0;
}
```


------------

敲了半小时的题解，给个赞吧！

---

## 作者：User757711 (赞：0)

# [CF1020A New Building for SIS](https://www.luogu.com.cn/problem/CF1020A)题解
### 思路分析
分类讨论：

1：如果在一栋楼，输出 $|f_a-f_b|$。

2：如果在一栋楼：

如果 $f_a<a$，则答案为 $a-f_a+|t_a-t_b|+|f_a-a|$。

如果 $f_a>b$，则答案为 $f_a-b+|t_a-t_b|+|f_b-b|$。

如果 $a \leq f_a \leq b$，则答案为 $|t_a-t_b|+|f_a-f_b|$。
### 最后，附上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,h,a,b,k;
	cin>>n>>h>>a>>b>>k;
	for(int i=1;i<=k;i++)
	{
	    int ta,fa,tb,fb;
		cin>>ta>>fa>>tb>>fb;
		if(ta==tb) 
		{
		    cout<<abs(fa-fb)<<endl;
		}
		else if(fa<a) 
		{
		    cout<<a-fa+abs(ta-tb)+abs(a-fb)<<endl;
		}
		else if(fa>b) 
		{
		    cout<<fa-b+abs(ta-tb)+abs(b-fb)<<endl;
		}
		else 
		{
		    cout<<abs(fa-fb)+abs(ta-tb)<<endl;
		}
		
	}
	return 0;
}
```
### The End！

---

