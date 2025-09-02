# Triangles

## 题目描述

Alice and Bob don't play games anymore. Now they study properties of all sorts of graphs together. Alice invented the following task: she takes a complete undirected graph with $ n $ vertices, chooses some $ m $ edges and keeps them. Bob gets the ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF229C/4408e88d41b3075c330afb5b8cbb30c34ea57359.png) remaining edges.

Alice and Bob are fond of "triangles" in graphs, that is, cycles of length 3. That's why they wonder: what total number of triangles is there in the two graphs formed by Alice and Bob's edges, correspondingly?

## 说明/提示

In the first sample Alice has 2 triangles: (1, 2, 3) and (2, 3, 4). Bob's graph has only 1 triangle : (1, 4, 5). That's why the two graphs in total contain 3 triangles.

In the second sample Alice's graph has only one triangle: (1, 2, 3). Bob's graph has three triangles: (1, 4, 5), (2, 4, 5) and (3, 4, 5). In this case the answer to the problem is 4.

## 样例 #1

### 输入

```
5 5
1 2
1 3
2 3
2 4
3 4
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5 3
1 2
2 3
1 3
```

### 输出

```
4
```

# 题解

## 作者：Joker_M (赞：4)

对于一个完全图，三角形的个数显然是 $C(n,3)$

现在把一些边挪到了另一个平面，那么就会有一些原本存在的三角形被拆掉了

我们选择把在原平面上的边染成红色，另一个平面上的边染成蓝色

这样就可以把两个平面变成一个了

样例大概长这样

![](https://cdn.luogu.com.cn/upload/image_hosting/7y4ox3oo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那么我们要求的就是 **三边全红** 或者 **三边全蓝** 的三角形

直接数不好数，选择用 **所有三角形的数量 - 不合法的三角形数量** 

那么问题就变成了求 **不合法的三角形数量**

显然不合法的三角形满足 **两红一蓝** 或者 **一红两蓝** 

上面两个条件等价于 **三条边中至少有一条红边和一条蓝边**

考虑一个点 $i$ ，假设它会往外面连 $a_i$ 条红色边和 $b_i$ 条蓝色边

由于每一条从 $i$ 出发的红色边都可以和每一条从 $i$ 出发的蓝色边构成一个不合法三角形

（由于一红一蓝已经满足了条件，我们并不需要去考虑第三条边的颜色）

所以这个点贡献的不合法三角形个数为 $a_i \times b_i$

 但是这么算会有重复

拿样例来说，对于三角形 $(2,3,5)$ ，点 $2$ 做了一次贡献，点 $3$ 做了一次贡献

点 $5$ 由于两边都是蓝色所以没有贡献

因为 **两红一蓝** 或者 **一红两蓝** 的三角形中有且只有一个点的两条边都是同色的

所以只有两个点有贡献，一个三角形会被重复算两次

所以 $ans=C(n,3)- \dfrac{\sum \limits_{i=1}^n a_i \times b_i}{2}$

~~然后你就会发现 $n^2$ 的边数直接统计 $a_i$ 肯定就炸了~~

但因为是完全图，所以 $a_i+b_i= n-1$

所以 $ans=C(n,3)- \dfrac{\sum \limits_{i=1}^n b_i \times (n-1-b_i)}{2}$

只需要统计 $b_i$ 即可

复杂度 $\mathcal O(n+m)$

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

const int N=1005000;

int n,m;
int b[N];
long long ans;

inline long long read(){
	long long re=0,k=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')	k=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		re=re*10+ch-'0';
		ch=getchar();
	}
	return re*k;
}

int main(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		b[x]++,b[y]++;
	}
	for(int i=1;i<=n;i++)	ans-=(long long)b[i]*(n-1-b[i]);
	ans=ans/2+(long long)(n-2)*(n-1)*n/6;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1900}$
---
### 解题思路：

正难则反，将问题转化为在分层之后减少了多少个三角形。

对于每一个位置，减少方案数为第一层图中的边的数量与第二层的乘积，因为所有的点的总度数为 $n-1$，所以可以直接用 $cnt(n-1-cnt)$ 计算出贡献，但是这样每一条边都会被计算两次，需要除以二。

原来的总方案数是 $C(n,3)$，也就是 $\dfrac{n(n-1)(n-2)}{6}$。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
long long n,m,x,y,d[1000006],ans;
int main(){
	scanf("%I64d%I64d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%I64d%I64d",&x,&y);
		d[x]++;d[y]++;
	}
	for(int i=1;i<=n;i++){
		ans+=d[i]*(n-1-d[i]);
	}
	ans=(n-1)*(n-2)*n/6-(ans/2);
	printf("%I64d\n",ans);
	return 0;
}
```


---

## 作者：liuyifan (赞：1)

## 本题主要考察思维深度

直接求原题所求较为麻烦

如果求**拿走一些边后，破坏的三角形的个数**就简单得多了。

我们先设拿走的变为黑边，还在的为白边。对于任意一个点，他的一条黑边和一条白边加上第三边即是一个破环的三角形。这样每个三角形**会计算两次**然后用C（3，n）减掉破环的三角形就是答案了。

注意上面的加粗内容，最后三角形个数要除以2(本人用的位运算，同理)

本蒟蒻渣code:
```cpp
#include<bits/stdc++.h>
#define reg register//register有助于卡常
#define ll long long//long long保平安(本题卡int)
#define inf 0x3f3f3f3f
using namespace std;
ll d[1000005],ans,n,m,x,y,sum;//数组注意多开一点，防爆
int main()
{
    scanf("%lld%lld",&n,&m);
    sum=n*(n-1)/2*(n-2)/3;//体面所示公式预处理
    while(m--)
    {
		scanf("%lld%lld",&x,&y);
		d[x]++;
		d[y]++;//统计黑白边
    }
    for(reg int i=1;i<=n;i++)ans+=d[i]*(n-1-d[i]);//统计破环的三角形的个数
    printf("%lld\n",sum-(ans>>1));//输出，注意ans要除以2
    return 0;
}
```


---

## 作者：hongshixiaobai (赞：0)

# CF229C Triangles 题解
[传送门](https://www.luogu.com.cn/problem/CF229C)
## 思路
考虑整体减去不合法数量，显然不合法的环都有一条红边，两条蓝边或一条蓝边，两条红边。对于每个点，统计所有出边中红、蓝两种颜色的边的数量，用红边数量乘以蓝边数量即可得到所有包含这个点的不合法三元环数量，因为会在两个点处都统计一次所以最后不合法换数量要除 $2$。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,ans,cnt,d[1000006],u,v,i;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	ans = n*(n-1)*(n-2)/6;
	for(i = 1;i<=m;i++)
	{
		cin>>u>>v;
		d[u]++,d[v]++;
	}
	for(i = 1;i<=n;i++)
	{
		cnt+=(n-1-d[i])*d[i];
	}
	cnt>>=1;
	cout<<ans-cnt;
}
```

---

## 作者：Vitamin_B (赞：0)

# 思路
对于每个 $u,v(1\le u,v\le n)$，它们之间一定有一条边，可能在原图上，也可能在另一个平面。然后如果要构成三角形，这三点 $a,b,c$ 必须互相连通，也相当于不能有 $mp_{a,b}+mp_{b,c}+mp_{a,c}\ne3,0$（$mp_{i,j}$ 表示 $i$ 和 $j$ 在原图上是否有边相连）。这也就说明对于 $a,b,c$ 三个点，有两个点是有且仅有一条边与其余两个点相连，设 $s_i$ 表示有 $s_i$ 条边与 $i$ 点不相连，则 $n-1-s_i$ 条边与 $i$ 相连（因为原先是完全图，每个点有 $n-1$ 条边），根据乘法原理，有 $s_i\times(n-1-s_i)$ 种方案，但因为会重复算两次，所以在加和后要把得数除以 $2$。然后完全图原先有 $C_n^3$ 种选法，去除不合法的就是 $C_n^3-\sum\limits_{i=1}^n s_i\times(n-1-s_i)$ 个三角形。
# 代码
```cpp
# include <bits/stdc++.h>
typedef long long ll;
using namespace std;
int n, m, x, y, a[1000005];
ll sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	while (m --)
		cin >> x >> y, ++ a[x], ++ a[y];
	for (int i = 1; i <= n; ++ i)
		sum += a[i] * (n - 1 - a[i]);
	sum = n * (n - 1ll) * (n - 2) / 6 - sum / 2;
	cout << sum;
	return 0;
}
```

---

