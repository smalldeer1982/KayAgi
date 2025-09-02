# Sasha and His Trip

## 题目描述

Sasha is a very happy guy, that's why he is always on the move. There are $ n $ cities in the country where Sasha lives. They are all located on one straight line, and for convenience, they are numbered from $ 1 $ to $ n $ in increasing order. The distance between any two adjacent cities is equal to $ 1 $ kilometer. Since all roads in the country are directed, it's possible to reach the city $ y $ from the city $ x $ only if $ x < y $ .

Once Sasha decided to go on a trip around the country and to visit all $ n $ cities. He will move with the help of his car, Cheetah-2677. The tank capacity of this model is $ v $ liters, and it spends exactly $ 1 $ liter of fuel for $ 1 $ kilometer of the way. At the beginning of the journey, the tank is empty. Sasha is located in the city with the number $ 1 $ and wants to get to the city with the number $ n $ . There is a gas station in each city. In the $ i $ -th city, the price of $ 1 $ liter of fuel is $ i $ dollars. It is obvious that at any moment of time, the tank can contain at most $ v $ liters of fuel.

Sasha doesn't like to waste money, that's why he wants to know what is the minimum amount of money is needed to finish the trip if he can buy fuel in any city he wants. Help him to figure it out!

## 说明/提示

In the first example, Sasha can buy $ 2 $ liters for $ 2 $ dollars ( $ 1 $ dollar per liter) in the first city, drive to the second city, spend $ 1 $ liter of fuel on it, then buy $ 1 $ liter for $ 2 $ dollars in the second city and then drive to the $ 4 $ -th city. Therefore, the answer is $ 1+1+2=4 $ .

In the second example, the capacity of the tank allows to fill the tank completely in the first city, and drive to the last city without stops in other cities.

## 样例 #1

### 输入

```
4 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7 6
```

### 输出

```
6
```

# 题解

## 作者：Velix (赞：3)

一道简单的题目，思维性也不强，顶多算橙吧，根本到不了黄……

---

首先如果 $n<v$，那直接输出 $n-1$ 即可（在最开始直接加可以到终点的油的数量）

否则，我们需要在别的时候加油。

根据加油的价格，我们可以推断出在越早的时候加油越好。

在一开始就直接加满，之后从第二个站点开始每到一个站点就再加 $1$ 升油，直到到达第 $n-v$ 个站点。

容易发现在最开始的油价为 $v$，之后加油的油价是一个等差数列，可以直接计算。

于是我们就得到了一个 $O(1)$ 的算法

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,v;
	cin>>n>>v;
	if(n<=v) cout<<n-1;
	else cout<<v+(n-v+2)*(n-v-1)/2;
}
```


---

## 作者：WsW_ (赞：1)

### 更新
这是一篇**已通过**的题解。
- $2024.12.12$ 对老题解进行更新。

---

### 思路
因为油越到后面越贵，求最少用多少钱，所以尽量在考前的位置加。  
如果在第 $1$ 个城市加的油就足够了，那么就直接在第一个城市加油 $n-1$；否则在第一个城市加满油箱 $v$。  
我们发现每次走完 $1$ 公里就立刻加是最好的，保证了尽量在前面加。所以每走 $1$ 公里就加 $1$ 升油，直到油箱里的油足够走到终点。  

发现除了第 $1$ 个城市外，在其他城市都是加 $1$ 升油，花费构成等差数列。  
在第 $1$ 个城市加 $v$ 升油花费 $v$，还差 $n-1-v$ 升，所以还要在另外 $n-1-v$ 个城市加油。在这些城市加油的花费为 $2+3+\cdots+(n-v)=\dfrac{(2+n-v)\times (n-1-v)}{2}$。  

时间复杂度 $O(1)$。

---

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,v;
int main(){
	scanf("%d%d",&n,&v);
	if(v>=n-1)printf("%d",n-1);//如果第一次加油就够了就输出n-1
	else printf("%d",(n+n*n+v*v+v)/2-n*v-1);//否则按上述输出
	return 0;
}
```

---

## 作者：kaceqwq (赞：0)

# 题意:
一个人要开车参观 $n$ 个城市，他从第一个城市出发，油箱初始为 0 ，油箱大小为 $v$ ，每个城市都有一个加油站，第 $i$ 个城市的加油站加一升油的价格为 $i$ 。每 1 公里消耗 1 升汽油，求最少用多少钱到达终点。


# 分析:
首先,我们知道油箱初始是为 0 的,所以我们在第一个城市先把油加满,接着油费会越来越贵,所以我们每经过一个加油站就要把油加满,这是最划算的 $($ 但是我们需要特判:如果城市数量还没有油箱大,在起始地加的油可以走完全程,就不用再加油了 $)$ 。由于第 $i$ 个城市中一升油的价格为 $i$ ，我们便得出了一个等差数列，随后我们使用等差数列求和公式,最后求出最终答案即可。

**等差数列求和公式：** $($ 首项 $+$ 末项 $)$ $\times$ 项数 $\div$ 2

# Code:
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	int n,v;
	cin>>n>>v;
	if(n<=v)   //特判,如果城市数量还没有油箱大,就不用在沿途加油了
	cout<<n-1<<'\n';
	else 
	cout<<v+(n-v+2)*(n-v-1)/2<<'\n'; //等差数列公式
	return 0;
}

```


---

## 作者：JoseTony (赞：0)

这道题是一道巧妙的结论题。我们先需要明确一下，城市数为 $n$ 因此里程数为 $n-1$。首先我们考虑的情况是，如果油箱的容量大于等于走的里程数，即 $v \geq n-1$ 时，我们只需要加 $n-1$ 升油，即可从起点走到终点并保证花费最小。另外的一种情况，油箱的容量小于走的里程数，即 $v < n-1$ 时，首先我们需要在第一个城市将油加满，花费为 $v$。接下来，从第二个城市开始一直到第 $n-v$ 个城市，每走一个城市就将油加满，即在每个城市只需加一升油。由于第 $i$ 个城市中一声油的价格为 $i$，因此这时就构成了一个首项为 $2$，末项为 $n-v$ 的等差数列，随后我们使用等差数列求和公式即可求出最终答案。时间复杂度为 $O(1)$，是解决本题的最优复杂度。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
    int n,v;
    cin >> n >> v;
    if(v>=n-1) cout << n-1;
    else{
        cout << v+(2+n-v)*(n-v-1)/2;//等差数列求和公式
    }
    return 0;
}

```


---

## 作者：Cult_style (赞：0)

本人萌新，不像各位大佬一样写$O(1)$算法，不过数据不大，$O(n)$也能过，先说思路吧



------------
首先，我们不难想到，我们要在**不超过油箱容量的情况下**，尽量在前面买油，那么，每当你使用一升油，你就要再买一升油，得出以下代码：

```
#include<bits/stdc++.h>
#define min(a,b) (a>b)?b:a
using namespace std;
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	int tot=0,ans=0;
	for(int i=1;i<=n;i++){
		int t=min(n-i,m);
        	//n-i表示还要走的路程，m表示油箱容量，如果还要走的路程小于容量的话，那么再买就没有意义
		ans+=(t-tot)*i;
        	//买油
		tot=t;
        	//赋值
		tot--;
        	//走一公里
	}
	printf("%d",ans);
	
	return 0;
}
```


---

