# 题目信息

# [PA 2020] Skierowany graf acykliczny

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda 5 [Skierowany graf acykliczny](https://sio2.mimuw.edu.pl/c/pa-2020-1/dag/)**

正如名字所示，有向无环图（*Directed Acyclic Graph*，简称 DAG）是一个无环的有向图。

如果我们在这样一个图中选择两个节点，我们可以计算出这些节点之间存在多少条不同的有向路径。如果其中一条路径包含一条边而另一条不包含这条边，我们就认为这两条路径是不同的。

你的任务是构造一个 $n$ 个节点（编号从 $1$ 到 $n$）的有向无环图，其中从节点 $1$ 到节点 $n$ 正好有 $k$ 条路径。你的图最多可以有 $100$ 个节点，每个节点最多可以有两条出边，而且不能包含重边（即如果一个节点有两条出边，它们必须通向不同的节点）。可以证明，对于每一个满足输入中约束条件的 $k$，都可以构造一个满足条件的图。

## 说明/提示

#### 样例 1 解释

下图展示了输出中 $6$ 个节点的有向无环图，从 $1$ 到 $6$ 有三条路径：$1\to 3\to 2\to 6,1\to 3\to 6$ 和 $1\to 5\to 6$。

![](https://cdn.luogu.com.cn/upload/image_hosting/hinzei5g.png)

------------

#### 数据范围

**本题采用捆绑测试**

对于 $100\%$ 的数据，保证 $1\le k\le 10^9$，$2\le n\le 100$。

## 样例 #1

### 输入

```
3```

### 输出

```
6
3 5
6 -1
2 6
2 6
6 -1
-1 -1```

# AI分析结果

### 综合分析与结论

本题的核心在于如何利用有限数量的节点（最多100个）和每个节点最多两条出边的限制，构造一个从节点1到节点n的有向无环图，使得从1到n的路径数恰好为给定的k。由于k的范围很大（1到10^9），直接暴力构造不可行，因此需要利用二进制分解或类似的数学技巧来高效构造图。

从题解中可以看出，大多数解法都采用了二进制分解的思路，即将k表示为若干个2的幂次之和，然后通过构造图来对应这些幂次。这种思路的核心在于利用每个节点的两条出边来生成不同的路径数，从而通过组合这些路径数来达到目标k。

### 所选题解

#### 1. 作者：mayike (5星)
- **关键亮点**：利用二进制分解的思路，通过每个节点的两条出边来生成不同的路径数，最终组合成目标k。思路清晰，代码简洁，且时间复杂度为O(log k)，非常高效。
- **个人心得**：作者提到“一个点有且至少一条，至多两条入边，即为路径数的累加”，这种思路非常直观且易于理解。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll k,sum[101],cnt,num,n,ab,a[101]; 
int main(){
    scanf("%lld",&k);
    if(k==1){
    	cout<<2<<'\n'<<2<<' '<<-1<<'\n'<<-1<<' '<<-1;
    	exit(0);
	}sum[1]=1;
	num=cnt=1;
	while(num*2-1<k){
		num*=2;
		sum[++cnt]=num;
	}ab=k,n=cnt*2+1;
	for(int i=cnt;i;i--)
		if(ab>=sum[i])ab-=sum[i],a[i*2]=1;
	cout<<n<<'\n';
	for(int i=1;i<=n;i++)
		if(i==n)
			cout<<-1<<' '<<-1;
		else if(i==n-2||i==n-1)
		    cout<<i+1<<' '<<-1<<'\n';
		else
			if(i%2==0)
				if(!a[i])cout<<i+1<<' '<<-1<<'\n';
				else cout<<i+1<<' '<<n<<'\n';
			else cout<<i+1<<' '<<i+2<<'\n';
	return 0;
}
```

#### 2. 作者：_3Zinc_ (4星)
- **关键亮点**：通过将图分为两部分，一部分用于生成2的幂次路径数，另一部分用于组合这些路径数来达到目标k。思路清晰，代码实现较为详细。
- **个人心得**：作者提到“任何一个题目给出的k都可以分解成2^{x1}+2^{x2}+2^{x3}+\cdots”，这种思路与二进制分解一致，但通过图的分层结构使得实现更加直观。

```cpp
#include <bits/stdc++.h>
using namespace std;
int k,n,bit[32],cnt,res;
int path[105][2],d1,d2,pos;
int main() {
	scanf("%d",&k);
	if(k==1) {
		printf("2\n2 -1\n-1 -1\n");
		return 0;
	}
	memset(path,-1,sizeof(path));
	for(;k;k>>=1) bit[++cnt]=k&1;
	path[2][0]=d1=3,path[2][1]=d2=4;	
	for(int i=1;i<cnt-1;i++) {
		path[d1][0]=path[d2][0]=d1+2;
		path[d1][1]=path[d2][1]=d2+2;
		d1+=2,d2+=2;
	}
	path[1][0]=pos=d2+1,res=2;
	for(int i=cnt;i>0;i--) {
		if(i>1) path[pos][0]=pos+1;
		if(bit[i]) path[pos][1]=res;
		res+=2,pos++;
	}
	path[d1][0]=pos,path[d2][0]=pos;
	printf("%d\n",pos);
	for(int i=1;i<=pos;i++) printf("%d %d\n",path[i][0],path[i][1]);
	return 0;
} 
```

#### 3. 作者：FBW2010 (4星)
- **关键亮点**：通过构造类似于二叉树的图结构，利用每个节点的两条出边来生成不同的路径数，最终组合成目标k。思路清晰，代码实现较为简洁。
- **个人心得**：作者提到“我们可以把k写成若干个2的幂相加，其实就是把k转化为二进制”，这种思路与二进制分解一致，且通过图的结构使得实现更加直观。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int k,cnt,a[105],l[105],r[105];
int main(){
	scanf("%d",&k);
	int p=0;
	while(k){
		a[++p]=k%2;
		k/=2;
	}
	cnt=1;
	int x=1,y;
	for(int i=1;i<p;i++){
		y=++cnt;
		l[x]=++cnt;
		l[cnt]=y;
		r[x]=++cnt;
		l[cnt]=y;
		x=y;
	}
	l[x]=++cnt;
	x=cnt;
	y=1;
	for(int i=1;i<p;i++){
		y=l[y];
		if(a[i])r[y]=x;
		y=l[y];
	}
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++){
		if(l[i])printf("%d ",l[i]);
		else printf("-1 ");
		if(r[i])printf("%d\n",r[i]);
		else printf("-1\n");
	}
	return 0;
}
```

### 最优关键思路或技巧

- **二进制分解**：将k表示为若干个2的幂次之和，然后通过构造图来对应这些幂次，最终组合成目标k。
- **图的构造**：利用每个节点的两条出边来生成不同的路径数，通过组合这些路径数来达到目标k。

### 可拓展之处

- **类似问题**：类似的问题可以考察如何利用有限的节点和边数构造满足特定路径数的图，或者考察如何利用二进制分解来解决其他组合问题。
- **算法套路**：二进制分解、图的构造、组合数学。

### 推荐题目

1. [P3388 【模板】割点（割顶）](https://www.luogu.com.cn/problem/P3388)
2. [P3379 【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
3. [P3381 【模板】最小费用最大流](https://www.luogu.com.cn/problem/P3381)

---
处理用时：55.87秒