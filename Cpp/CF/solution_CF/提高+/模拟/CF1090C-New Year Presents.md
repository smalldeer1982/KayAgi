# New Year Presents

## 题目描述

圣诞老人已经为 $n$ 个孩子准备好了装有礼物的盒子，每个孩子一个盒子。有 $m$ 种不同的礼物：气球、糖果、巧克力棒、玩具车……每个孩子如果收到两个相同种类的礼物会感到失望，因此每个盒子里的礼物种类都必须各不相同。

在打包完所有礼物后，圣诞老人发现不同的盒子里礼物的数量可能不同。这样对孩子们来说不公平，于是他决定在盒子之间移动一些礼物，使得每个盒子里的礼物数量尽量接近。所有移动完成后，任意盒子中礼物数量的最大值与最小值之差应尽可能小。每个盒子中的礼物种类仍需各不相同。圣诞老人希望尽快完成这项工作，因此他想让所需移动的次数尽量少。

给定每个盒子中礼物的种类，请找出一种最短的移动方案，使得所有盒子中礼物数量的最大值与最小值之差不超过 $1$，并且每个盒子中的礼物种类各不相同。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 5
5 1 2 3 4 5
2 1 2
2 3 4
```

### 输出

```
2
1 3 5
1 2 3
```

# 题解

## 作者：Luzhuoyuan (赞：1)

Links: [[Codeforces]](http://codeforces.com/problemset/problem/1090/C) [[Luogu]](https://www.luogu.com.cn/problem/CF1090C)

另外一篇题解复杂度假了，现在已经过不了原题了。补一个时间正确的题解。

### 题意

有 $n$ 个盒子和 $m$ 种礼物，第 $i$ 个盒子里有 $s_i$ 个不同种类的礼物。现在要使所有盒子中的礼物数量尽可能相近（即礼物最多的盒子与最少的盒子的礼物数量差不大于 $1$），且最终每个盒子中的礼物种类依旧两两不同。你可以进行若干次操作，每次操作可以从一个盒子中取出一个礼物放到另一个盒子中，求满足条件的最小操作次数和一种操作方案。

- $1\le n,m\le 10^5$；
- $\sum s_i\le 5\cdot 10^5$。

### 思路

参考了 jqdai0815 的[代码](https://codeforces.com/contest/1090/submission/46796964)。

首先，贪心思路是没有问题的。把盒子看成集合，每次我们从最大的集合中取出一个元素插到最小的集合中，由于最大集合大小大于最小集合，最大集合中一定存在一个元素不出现在最小集合中。暴力做法就是维护大根堆和小根堆，每次暴力遍历最大集合，找到一个合法的元素插进最小集合。

为了优化上面的做法，我们首先对集合按大小升序排序。我们可以计算出每个集合最终应当有多少个元素，为了最小化操作次数，如果 $n\nmid(\sum s_i)$，我们让原大小较小的集合拥有较小的最终大小。

然后，我们用两个指针维护当前还没有到达最终大小的集合中的最大和最小集合，设它们分别为 $S_r,S_l$。我们再维护一个集合 $df$ 表示当前最大集合能移向最小集合的元素组成的集合，即 $df=\{x|x\in S_r\wedge x\notin S_l\}$。如果 $|S_l|,|S_r|$ 都没有达到最终大小，则从 $df$ 中选任意一个元素并移动它即可。

如果 $|S_l|,|S_r|$ 中的某一个达到了最终预期的大小，我们就要切换到下一个集合。为了保证复杂度，我们要尽量保证移动一端时只遍历本侧的集合，这样每个元素遍历次数为 $O(1)$。当移动右端点时，我们直接把 $df$ 赋值为新的 $S_r$，然后遍历 $S_r$ 的元素并从 $df$ 中删除在 $S_l$ 中出现过的元素；当移动左端点时，我们先遍历原来的 $S_l$，把其中在 $S_r$ 中出现过的元素加入 $df$，也就是把 $df$ 还原为 $S_r$（注意 `unordered_set` 的赋值复杂度关于元素个数线性），然后移动左端点，遍历新的 $S_l$ 并从 $df$ 中删除在新的 $S_l$ 中出现的值。这样我们就能方便地维护 $df$ 了。

复杂度为 $O(n\log n+\sum s_i)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N=1e5+5;
int n,m,x,y,num[N],d[N],l,r;
unordered_set<int> s[N],df;
struct node{int x,y,z;};
vector<node> ve;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>x;
	for(int i=1;i<=n;i++){cin>>x,m+=x,d[i]=i;while(x--)cin>>y,s[i].insert(y);}
	sort(d+1,d+1+n,[&](int xx,int yy){return s[xx].size()<s[yy].size();});
	for(int i=0;i<m;i++)num[n-i%n]++;
	l=1,r=n;df=s[d[n]];
	for(int i:s[d[n]])if(s[d[1]].count(i))df.erase(i);
	while(l<r){
		if((int)s[d[r]].size()==num[r]){
			if(l>=--r)break;
			df=s[d[r]];
			for(int i:s[d[r]])if(s[d[l]].count(i))df.erase(i);
			continue;
		}
		if((int)s[d[l]].size()==num[l]){
			for(int i:s[d[l]])if(s[d[r]].count(i))df.insert(i);
			if(++l>=r)break;
			for(int i:s[d[l]])if(df.count(i))df.erase(i);
			continue;
		}
		int x=*df.begin();ve.pb({d[r],d[l],x});
		s[d[r]].erase(x),s[d[l]].insert(x),df.erase(x);
	}
	cout<<ve.size()<<'\n';
	for(node v:ve)cout<<v.x<<' '<<v.y<<' '<<v.z<<'\n';
	return 0;
}
```

（逃

---

