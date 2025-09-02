# Context Advertising

## 题目描述

你有一个有 $n$ 个**单词**的文本，请按要求重新编辑此文本后输出。

以下为规定:

1. 一个单词中的每个字母都在一行上。
2. 单词之间以**若干**个空格分隔。
3. 最终的文本应当是原文本中的一个子段。也就是说，选择一个区间 $[i, j]$，然后让第 $i$ 个单词到第 $j$ 个单词都出现在最终文本上。
4. 最多有 $r$ 行，每行最多 $c$ 个**字符**。
5. 包含的单词数尽可能多。

## 样例 #1

### 输入

```
9 4 12
this is a sample text for croc final round
```

### 输出

```
this is a
sample text
for croc
final round
```

## 样例 #2

### 输入

```
9 1 9
this is a sample text for croc final round
```

### 输出

```
this is a
```

## 样例 #3

### 输入

```
6 2 3
croc a a a croc a
```

### 输出

```
a a
a
```

## 样例 #4

### 输入

```
2 2 5
first second
```

### 输出

```
first
```

# 题解

## 作者：chenxia25 (赞：0)

>### [洛谷题目页面传送门](https://www.luogu.org/problem/CF309B) & [CodeForces题目页面传送门](https://codeforces.com/contest/309/problem/B)

>给定一个$n$个单词的文本，第$i$个单词的长度为$len_i$，要求截取文本的一段（单词必须取整的），分若干行放，同行单词用空格分隔，使得每行的长度不超过$m$，最多放$s$行。求截取的单词数最多的截法。

>$n\in\left[1,10^6\right],\sum\limits_{i=1}^nlen_i\in\left[1,5\times10^6\right],ms\in\left[1,10^6\right]$。

这道题想要AC还是很容易的。考虑枚举截取的第$1$个单词，然后计算往后最多能延申多少个单词，最后取个$\max$。重点在于如何计算往后最多能延申多少个单词，这个可以傻傻地贪心。先求出$spl$数组，表示从第$i$个单词开始最多能往后延申到第$spl_i-1$个单词放在一行。很显然，“是否能延申到第$x$个单词放在一行”具有单调性，于是$spl$数组可以$\mathrm O(n\log_2n)$配合前缀和二分求出。那么从第$i$个单词往后最多能延申的单词数就是$\underbrace{spl_{spl_{spl_{\cdots_{i}}}}}_{s\text{次}spl\text{映射}}-i$。这个又显然可以总共$\mathrm O(n\log_2n)$倍增求出。于是$\mathrm O(n\log_2n)$的复杂度是extremely easy的。

而我~~们~~是追求完美的OIer，这个复杂度能否达到$\mathrm O(n)$呢？带$\log$复杂度的地方有$2$个——求$spl$数组和$s$次$spl$映射，我们一个一个来看。

首先是求$spl$数组。不难发现，$spl$数组本身具有单调性，即$spl_i\le spl_{i+1}$，那么我们可以从后往前two-pointers，求$spl_i$时，只需从$spl_{i+1}$到$i$从后往前试是否能延申到即可。其中边界是$spl_{n+1}=n+1$。这样所有单词均摊被试$\mathrm O(n)$次，时间复杂度就没有$\log$了。

接下来是映射。仍然利用$spl$数组的单调性，若在所有$i$和$spl_i$之间连一条边，若$i=spl_i$则不连边，那么一定会形成一个森林，而对$i$进行$s$次映射显然就等于节点$i$的$\min(s,dep_i)$辈祖先。我们对森林里的每一棵树进行DFS，同时维护一个递归栈$stk$，那么$\mathrm O(1)$便可找到节点$i$的$\min(s,dep_i)$辈祖先，复杂度也变成整体$\mathrm O(n)$了。

下面贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=1000000;
int n/*单词数*/,m/*每行最多能放的长度*/,s/*最多能放的行数*/;
string a[N+1];//单词们 
int Sum[N+1];//前缀长度和（每个单词后面加上空格） 
vector<int> son[N+2];int fa[N+2];//树，fa即spl数组 
int stk[N+1],top;//递归栈 
int ans[N+2];//从第i个单词开始最多能延伸的单词数 
void dfs(int x){//对树DFS 
	stk[top++]=x;//将此节点入栈 
	ans[x]=stk[max(0,top-1-s)]-x;//O(1)找min(s,dep[i])辈祖先 
	for(int i=0;i<son[x].size();i++){
		int y=son[x][i];
		dfs(y);
	}
	top--;//出栈 
}
int main(){
	cin>>n>>s>>m;
	for(int i=1;i<=n;i++)cin>>a[i],Sum[i]=Sum[i-1]+a[i].size()+1/*预处理前缀和*/;
	fa[n+1]=n+1;//递推边界 
	for(int i=n;i;i--){//从后往前递推 
		fa[i]=fa[i+1]; 
		while(Sum[fa[i]-1]-Sum[i-1]-1>m)fa[i]--;//从后往前试 
		if(fa[i]!=i)son[fa[i]].pb(i);//连边 
	}
//	for(int i=1;i<=n+1;i++)cout<<fa[i]<<" ";puts("");
	for(int i=1;i<=n+1;i++)if(fa[i]==i)top=0,dfs(i);//DFS每棵树 
	int mx=*max_element(ans+1,ans+n+2);//最大答案 
	for(int i=1;i<=n+1;i++)if(ans[i]==mx){
		while(s--){//输出 
			for(int j=i;j<fa[i];j++)cout<<a[j]<<(j<fa[i]-1?" ":"\n");
			i=fa[i];
		}
		return 0;
	}
}
```

---

