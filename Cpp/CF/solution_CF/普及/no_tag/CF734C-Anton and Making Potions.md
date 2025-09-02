# Anton and Making Potions

## 题目描述

Anton is playing a very interesting computer game, but now he is stuck at one of the levels. To pass to the next level he has to prepare $ n $ potions.

Anton has a special kettle, that can prepare one potions in $ x $ seconds. Also, he knows spells of two types that can faster the process of preparing potions.

1. Spells of this type speed up the preparation time of one potion. There are $ m $ spells of this type, the $ i $ -th of them costs $ b_{i} $ manapoints and changes the preparation time of each potion to $ a_{i} $ instead of $ x $ .
2. Spells of this type immediately prepare some number of potions. There are $ k $ such spells, the $ i $ -th of them costs $ d_{i} $ manapoints and instantly create $ c_{i} $ potions.

Anton can use no more than one spell of the first type and no more than one spell of the second type, and the total number of manapoints spent should not exceed $ s $ . Consider that all spells are used instantly and right before Anton starts to prepare potions.

Anton wants to get to the next level as fast as possible, so he is interested in the minimum number of time he needs to spent in order to prepare at least $ n $ potions.

## 说明/提示

In the first sample, the optimum answer is to use the second spell of the first type that costs $ 10 $ manapoints. Thus, the preparation time of each potion changes to $ 4 $ seconds. Also, Anton should use the second spell of the second type to instantly prepare $ 15 $ potions spending $ 80 $ manapoints. The total number of manapoints used is $ 10+80=90 $ , and the preparation time is $ 4·5=20 $ seconds ( $ 15 $ potions were prepared instantly, and the remaining $ 5 $ will take $ 4 $ seconds each).

In the second sample, Anton can't use any of the spells, so he just prepares $ 20 $ potions, spending $ 10 $ seconds on each of them and the answer is $ 20·10=200 $ .

## 样例 #1

### 输入

```
20 3 2
10 99
2 4 3
20 10 40
4 15
10 80
```

### 输出

```
20
```

## 样例 #2

### 输入

```
20 3 2
10 99
2 4 3
200 100 400
4 15
100 800
```

### 输出

```
200
```

# 题解

## 作者：BorisDimitri (赞：1)

# 题意

要求得到至少 $n$ 个药剂，可以使用两种魔法，一种能够缩短制药时间，一种能瞬间制药，

给你 $x$ 表示标准制药一个要 $x$ 秒，给你 $s$ 表示你的法力值为$s$。

$m$ 种第一类魔法，消耗 $b$ 点法力值，缩短时间为 $a$ 秒。

$k$ 种第二类魔法，消耗 $d$ 点法力值，瞬间做出 $c$ 个药。

两种魔法最多各选一个用，问你**最少花多少时间能制得至少 $n$ 个药剂**。


# 分析：
1. 首先按第一种药剂以能缩短的时间为第一关键字，以消耗的法力值为第二关键字排序。

2. 枚举第一种药剂，二分第二种药剂即可。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;

const int INF= 0x3f3f3f3f;
const int N=2e5+5;
typedef long long LL;

LL n,m,k,w,s;
LL b[N],c[N];

struct Node
{
	LL cost;
	LL changeto;
} a[N];

int main()
{
	scanf("%d%d%d%d%d",&n,&m,&k,&w,&s);
	for(int i=1; i<=m; i++) scanf("%d",&a[i].cost);
	for(int i=1; i<=m; i++) scanf("%d",&a[i].changeto);
	for(int i=1; i<=k; i++) scanf("%d",&b[i]);
	for(int i=1; i<=k; i++) scanf("%d",&c[i]);

	LL time=n*w;
	for(int i=1; i<=k; i++)
	{
		if(c[i] <= s)
		{
			time=min(time, (n-b[i])*w );
		}
	}
	for(int i=1; i<=m; i++)
	{
		if(a[i].changeto <= s)
		{
			time=min(time, n*a[i].cost );
		}
	}
	for(int i=1; i<=m; i++)
	{
		if(a[i].changeto > s) continue;

		LL temp=upper_bound(c+1,c+1+k, s-a[i].changeto )-(c+1);
		if(c[temp] <= s-a[i].changeto)
			time=min(time, (n-b[temp])*a[i].cost) ;
	}
	
	cout<<time;

	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
本题的主要思路是二分。
## 分析。
注意到每一种咒语只能选择一次，所以我们尽量要最小化每一个操作的时间，但是我们注意到有可能只用第二种咒语，不用第一种咒语，而前者比后者更优，所以没有办法贪心。那么我们现在需要判断两个关键词：时间和效果。因为第二种咒语的效果和消耗时间都是已经排好序的，所以我们只要枚举第一种咒语然后二分第二种咒语就能得到答案。具体来说，第二种能力可以在限度时间内进行查询，然后枚举第一种咒语，然后二分求出使用第二种咒语可以制造多少的药水，找到最多的，剩下地直接最大化缩短时间即可。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
long long n,m,k,x,s;
long long ans,time;
long long a[200005],b[200005],c[200005],d[200005];
int main(){
    cin>>n>>m>>k>>x>>s;
    ans=n*x;
    for (int i=1;i<=m;i++){
    	cin>>a[i];
	}
    for (int i=1;i<=m;i++){
    	cin>>b[i];
	}
    for (int i=1;i<=k;i++){
    	cin>>c[i];
	}
    for (int i=1;i<=k;i++){
    	cin>>d[i];
	}
    for (int i=1;i<=k;i++){
        if (d[i]<=s){
		    ans=min(ans,x*max(0ll,n-c[i]));
		}
	}
    for (int i=1;i<=m;i++){
        if(a[i]<x&&b[i]<=s){
            time=s-b[i];
            if(time<d[1]){
			    ans=min(ans,n*a[i]);
			}
            else{
                long long l=1,r=k+1;
				long long mid=(l+r)>>1;
                while(l+1<r){
                    if(d[mid]<=time){
					    l=mid;
					}
                    else{
					    r=mid;
					}
					mid=(l+r)>>1;
				}
                ans=min(ans,max(0ll,n-c[l])*a[i]);
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

