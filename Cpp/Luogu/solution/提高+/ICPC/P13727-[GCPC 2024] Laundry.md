# [GCPC 2024] Laundry

## 题目描述

每个星期天都是洗衣日，总有一大堆衣服等着你去洗，这肯定会花掉你很长时间。
你尤其讨厌那些需要特别小心清洗的衣物，并且必须为每件衣物选择合适的洗涤程序。

:::align{center}
![](https://cdn.pixabay.com/photo/2018/04/02/01/14/hanging-3282769_1280.jpg)

晾晒的衣服 [图片来自 gregroose，Pixabay](https://pixabay.com/photos/hanging-architecture-clothesline-3282769/)
:::

幸运的是，你的洗衣机很老旧，只支持三种不同的洗涤程序：A、B 和 C。
你每次最多可以在一桶中放入 $k$ 件衣物，
每一桶只能选择其中一种洗涤程序。

有些衣物很容易打理，可以随意放进任何一桶。
更精致的衣物则不能用某一种特定的程序洗，但可以用另外两种。
当然，最麻烦的衣物只能用一种特定的程序洗。

你已经将衣物分成了七堆，每堆中的衣物都可以用相同的程序组合来清洗，因此你知道每一堆的数量。

你需要计算，最少需要多少桶才能把所有衣物洗完？

:::align{center}
![](https://cdn.luogu.com.cn/upload/image_hosting/sd620u2k.png)

图 L.1：样例输入 2 的最优解示意图。左侧为七堆衣物，每堆对应一种程序组合。右侧为一种（可能的）最优解，每堆衣物都用一桶洗。每堆上的数字表示该桶中洗了多少件对应组合的衣物。特别地，最左侧的衣物用程序 A 洗，中间两堆用程序 B 洗，右侧两堆用程序 C 洗。因此总共需要五桶洗完所有衣物，这是最优的，因为总共有 15 件衣物。
:::

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
10
15 11 9 5 2 7 1
120
0 0 0 0 0 0 0
6
5 6 8 9 1 0 0
1213
295053681 137950336 87466375 956271897 344992260 31402049 988259763```

### 输出

```
6
0
6
2342454```

## 样例 #2

### 输入

```
1
3
1 2 1 3 3 2 3```

### 输出

```
5```

# 题解

## 作者：Crazyouth (赞：0)

## 分析

我们感性理解一下如何分配 `AB`，`BC`，`AC`。首先先随意把它们划进 `A`，`B`，`C` 中，然后比如说把一部分进 `A` 的 `AB` 划进 `B`，然后让在 `C` 的一部分 `AC` 划进 `A`，以此类推。这样反复操作，总有一个双划分方式的种类会完全进入一个洗涤程序中。以样例 $1$ 的第一组数据为例，我们可以把 `AB` 完全划分进 `B` 并实现一个最优方案，读者可以自行验证。

这样我们可以枚举每一个双划分方式的种类以及它会划进哪一类，每次使用贪心（尽可能让一次洗衣服洗满）就可以完成剩余的划分。复杂度是单次 $O(1)$ 的。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int c[8],d[8],k,ans=1e10,now=0;
void check()
{
	now++;
	int res=0,alft=0,blft=0,clft=0;
	for(int i=1;i<=7;i++) d[i]=c[i];
	c[4]=0;
	int b=c[1]%k;
	res+=c[1]/k;
	if(b)
	if(b+c[6]<k)
	{
		if(b+c[6]+c[7]>=k)
		{
			b+=c[6];
			c[6]=0;
			c[7]-=k-b;
			c[1]=0;
			res++;
		}
		else
		{
			alft+=k-b;
			res++;
			c[1]=0;
		}
	}
	else
	{
		res++;
		c[6]-=k-b;
		c[1]=0;
	}
	c[3]+=c[6];
	c[6]=0;
	b=c[3]%k;
	res+=c[3]/k;
	if(b)
	if(b+c[5]<k)
	{
		if(b+c[5]+c[7]>=k)
		{
			b+=c[5];
			c[5]=0;
			c[7]-=k-b;
			c[3]=0;
			res++;
		}
		else
		{
			clft+=k-b;
			c[3]=0;
			res++;
		}
	}
	else
	{
		res++;
		c[5]-=k-b;
		c[3]=0;
	}
	if(c[5]>clft) c[5]-=clft,clft=0;
	else c[5]=0,clft-=c[5];
	c[2]+=c[5];
	b=c[2]%k;
	if(b+c[7]<k)
	{
		c[7]-=alft+clft;
		c[7]=max(c[7],0ll);
		res+=(c[2]+c[7]+k-1)/k;
	}
	else
	{
		c[2]+=k-b;
		c[7]-=k-b;
		c[7]-=alft+clft;
		c[7]=max(c[7],0ll);
		res+=(c[2]+c[7]+k-1)/k;
	}
	ans=min(ans,res);
	for(int i=1;i<=7;i++) c[i]=d[i];
}
void solve()
{
	now=0;
	ans=1e10;
	cin>>k;
	for(int i=1;i<=7;i++) cin>>c[i];
	for(int t=1;t<=3;t++)
	{
		c[1]+=c[4];
		check();
		c[1]-=c[4];
		c[2]+=c[4];
		check();
		c[2]-=c[4];
		d[1]=c[3];d[2]=c[1];d[3]=c[2];d[4]=c[6];d[5]=c[4];d[6]=c[5];
		for(int i=1;i<=6;i++) c[i]=d[i];
	}
	cout<<ans<<'\n';
}
signed main()
{
	int t;
	cin>>t;
	while(t--) solve();
}

---

