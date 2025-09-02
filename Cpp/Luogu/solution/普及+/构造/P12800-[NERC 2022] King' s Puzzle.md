# [NERC 2022] King' s Puzzle

## 题目描述

国王 Kendrick 是 Kotlin 王国的君主。他正在为下一次政$ $府会议做准备。Kotlin 王国由 $n$ 个城市组成。这些城市需要通过若干条双向道路连接起来。由于各个部门负责王国居民的安全和舒适等方面，其中一些部门提出了以下要求：

- “所有城市都应通过新修的道路连接起来，即任意一个城市都应能通过道路到达其他任何城市”——交通与数字基础设施部。
- “不能有自环路——即连接一个城市到其自身的道路”——环境部。
- “任意一对城市之间最多只能有一条道路”——财政部。
- “如果 $a_i$ 是连接到第 $i$ 个城市的道路数量，那么集合 $\{a_1, \ldots, a_n\}$ 应恰好由 $k$ 个不同的数字组成”——ICPC 部。

国王 Kendrick 对 ICPC 部的要求感到头疼。他请求你帮助他。请找出一组满足上述所有要求的道路方案，或者说明这是不可能的。

## 说明/提示

### 样例 1 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/cuv06x7v.png)

城市 1 有四条道路与之相连，而其他城市都只有一条。

### 样例 2 解释

![](https://cdn.luogu.com.cn/upload/image_hosting/xbm5xgu8.png)

每个城市都恰好有两条道路与之相连。

翻译由 gemini2.5pro 完成

## 样例 #1

### 输入

```
5 2```

### 输出

```
YES
4
1 2
1 3
1 4
1 5```

## 样例 #2

### 输入

```
4 1```

### 输出

```
YES
4
1 2
2 3
3 4
4 1```

# 题解

## 作者：fish_love_cat (赞：2)

建议升蓝啊，想了一整天，感觉比[隔壁的 Ad-hoc 构造](https://www.luogu.com.cn/article/v9w8rpaz)难多了 /fad

说不上来怎么想到的，类似于灵光乍现写写画画突然得到的构造。~~Ad-hoc 让我怎么告诉你思维过程。~~

---

显然度数最大不超过 $n-1$，所以若有解必有 $k<n$。

想不到其他无解情况了，于是着手对于 $n=k+1$ 的极限情况进行构造。

假设能构造出来吧，那么 $n-(k+1)$ 的这么多点可以用链的形式挂在后面保证连通。

这样题目转变为了 $n=k+1$ 时的情况。

此时合法度数集内的数显然就是 $[1,k]$。

不知道怎么回事想到连一个菊花，然后把这个点扔掉。

此时我们少了度为 $k$ 的点的需求，并且剩余点的度数需求均有减一。

此时剩下的构造等价于用 $k$ 个点连出一个度数集为 $[0,k-2]$ 的图。

$0$ 的显然直接扔掉，于是变成 $k$ 个点连出一张图使得度数集合大小为 $k-2$。

这是一个和原问题一模一样的子问题，用类似递归的思想做就行了。

还是很巧妙的呀！

另外注意本题小数据时的特判，详细见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int>ve[300005];
int top;
int main(){
    int n,k;
    cin>>n>>k;
    if(n==1&&k==1){
        puts("YES\n0");
        return 0;
    }
    if(n==2&&k==1){
        puts("YES\n1\n1 2");
        return 0;
    }
    if(n<=k){
        puts("NO");
        return 0;
    }
    if(k<=2){
        puts("YES");
        cout<<n-(k==2)<<'\n';
        for(int i=1;i<n;i++)cout<<i<<' '<<i+1<<'\n';
        if(k==1)cout<<1<<' '<<n<<'\n';
        return 0;
    }
    for(int i=k+1,j=1;i>=j;i--,j++)
        for(int k=j;k<i;k++)ve[++top]=make_pair(i,k);
    for(int i=k+2;i<=n;i++)
        ve[++top]=make_pair(i-1,i);
    puts("YES");
    cout<<top<<'\n';
    for(int i=1;i<=top;i++)
    cout<<(ve[i].first)<<' '<<(ve[i].second)<<'\n';
    return 0;
}
```

---

## 作者：lovelish (赞：0)

好玩题，一点都不难。

$k=1$ 就是个环，特判一下即可。（需要额外特判 $n=1$ 和 $n=2$）

$k=n$ 显然无解，因为不能有重边或自环，所以每个点最多只能连 $n-1$ 条边。

考虑 $2\le k\le n-1$，由简入难，我们一点一点深入：

- 若 $k=2$，则将节点 $1$ 与其他节点全部相连即可。

- 若 $k=4$，则在 $k=2$ 的基础上，额外将节点 $2$ 与节点 $3\sim n-1$ 全部相连即可。

- 若 $k=6$，则在 $k=4$ 的基础上，额外将节点 $3$ 与节点 $4\sim n-2$ 全部相连即可。

- $\dots$

图画出来是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/hf9ccni8.png)

于是我们就解决了所有 $k$ 为偶数的情况，奇数情况略变一点就可以：如果在对一个节点的连边全部连完后发现只差 $1$ 答案就足够，那么下一个节点的连边只连一条即可。例如 $n=8,k=5$ 时，借助上图，在红色边连完后所有节点边数为 $[7,6,2,2,2,2,2,1]$，此时有 $4$ 种不同的数，那么对于黄色边就只需要连第一条即可。这样我们就解决了 $k$ 为奇数的情况。以下为代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int cnt,ans1[200010],ans2[200010];
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int n,k,ans=0;
	cin>>n>>k;
	if(k==1&&n==1)
	{
		cout<<"Yes"<<endl<<0<<endl;
		return 0;
	}
	if(k==1&&n==2)
	{
		cout<<"Yes"<<endl<<1<<endl<<1<<" "<<2<<endl;
		return 0;
	}
	if(k==n)
	{
		cout<<"NO"<<endl;
		return 0;
	}	
	cout<<"YES"<<endl;
	if(k==1)
	{
		cout<<n<<endl;
		for(int i=1;i<n;i++)cout<<i<<" "<<i+1<<endl;
		cout<<n<<" "<<1<<endl; 
		return 0;
	}
	for(int i=1;i<=n/2;i++)
	{
		ans++;
		cnt++;ans1[cnt]=i;ans2[cnt]=i+1;
		if(ans==k)break;
		for(int j=i+2;j<=n-i+1;j++)
		{
			cnt++;
			ans1[cnt]=i,ans2[cnt]=j;
		}
		ans++;
		if(ans==k)break;
	}
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)cout<<ans1[i]<<" "<<ans2[i]<<endl;
	return 0;
}


```

---

