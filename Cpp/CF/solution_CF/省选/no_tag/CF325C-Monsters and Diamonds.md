# Monsters and Diamonds

## 题目描述

Piegirl has found a monster and a book about monsters and pies. When she is reading the book, she found out that there are $ n $ types of monsters, each with an ID between $ 1 $ and $ n $ . If you feed a pie to a monster, the monster will split into some number of monsters (possibly zero), and at least one colorful diamond. Monsters may be able to split in multiple ways.

At the begining Piegirl has exactly one monster. She begins by feeding the monster a pie. She continues feeding pies to monsters until no more monsters are left. Then she collects all the diamonds that were created.

You will be given a list of split rules describing the way in which the various monsters can split. Every monster can split in at least one way, and if a monster can split in multiple ways then each time when it splits Piegirl can choose the way it splits.

For each monster, determine the smallest and the largest number of diamonds Piegirl can possibly collect, if initially she has a single instance of that monster. Piegirl has an unlimited supply of pies.

## 样例 #1

### 输入

```
6 4
1 3 -1 1 -1
1 2 -1 -1
2 3 -1 3 -1
2 3 -1 -1 -1
3 2 -1 -1
4 2 4 -1
```

### 输出

```
2 -2
3 4
2 2
-1 -1
```

## 样例 #2

### 输入

```
3 2
1 2 1 -1
2 2 -1 -1
2 3 2 1 -1
```

### 输出

```
-1 -1
2 2
```

# 题解

## 作者：zifanwang (赞：1)

- [洛谷传送门](https://www.luogu.com.cn/problem/CF325C)
- [CF 传送门](https://codeforces.com/contest/325/problem/c)

一道二合一题。

首先 `-1` 的情况很好判断，可以和最小值一起搞。记 $f_i$ 表示点 $i$ 的答案，暴力更新的方法就是枚举每个该点的变换计算 $\sum f_{p_i}[p_i\neq -1]+[p_i=-1]$ 的值最后再取个最小值。

做一遍 $\tt dijistra$，一开始先将点 `-1` 入堆。每次取出一个点 $i$ 时，将每个包含该点的变换的代价加上 $f_i$，然后如果这个变换已经被每个 $p_i$ 更新过了就更新一下这个变换对应的点的 $f$ 值。

如果一个点的 $f$ 值在这个过程中没被更新，那这个点就是 `-1` 的情况。

接下来求最大值，直接 $\tt dfs$，如果一个点在这过程中可以访问到其 $\tt dfs$ 树上的父亲或者一个答案为 `-2` 的点，那这个点的答案就是 `-2`。剩下的情况直接暴力 $\tt dp$ 就好了。

参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mxn 100003
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define pq priority_queue
using namespace std;
struct node{
	ll c;
	vector<int>d;
};
int n,m,ed[mxn];
ll ds[mxn],dp[mxn],c[mxn],d1[mxn];
vector<node>e[mxn];
vector<int>f[mxn];
pq<pair<ll,int>>q;
bool v[mxn],ins[mxn];
void dfs(int x){
	v[x]=1,ins[x]=1;
	ll sm;
	for(node s:e[x]){
		for(int i:s.d)if(ds[i]>1e18)goto next; 
		sm=0;
		for(int i:s.d){
			if(!v[i]){
				dfs(i);
				if(dp[i]==-2)dp[x]=-2;
			}else if(ins[i]||dp[i]==-2)dp[x]=-2;
			sm+=dp[i];
		}
		if(dp[x]==-2)break;
		dp[x]=min(max(dp[x],sm+s.c),314000000ll);
		next:;
	}
	ins[x]=0;
}
signed main(){
	scanf("%d%d",&m,&n);
	for(int i=1,x,k,a;i<=m;++i){
		scanf("%d%d",&x,&k);
		c[i]=k,ed[i]=x;
		node s;
		rept(j,0,k){
			scanf("%d",&a);
			if(a!=-1)s.d.pb(a),f[a].pb(i);
			else d1[i]++,f[0].pb(i);
		}
		s.c=d1[i];
		e[x].pb(s);
	}
	memset(ds,0x3f,sizeof(ds));
	q.push({0,0}),ds[0]=0;
	while(q.size()){
		int x=q.top().second;q.pop();
		if(v[x])continue;
		v[x]=1;
		for(int i:f[x]){
			d1[i]+=ds[x];
			if(!--c[i]){
				if(d1[i]<ds[ed[i]]){
					ds[ed[i]]=d1[i];
					q.push({-d1[i],ed[i]});
				}
			}
		}
	}
	memset(v,0,sizeof(v));
	rep(i,1,n)if(ds[i]<1e18&&!v[i])dfs(i);
	rep(i,1,n){
		if(ds[i]>1e18)puts("-1 -1");
		else printf("%lld %lld\n",min(ds[i],314000000ll),dp[i]);
	}
	return 0;
}
```

---

