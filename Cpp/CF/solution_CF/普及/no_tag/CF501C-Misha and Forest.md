# Misha and Forest

## 题目描述

Let's define a forest as a non-directed acyclic graph (also without loops and parallel edges). One day Misha played with the forest consisting of $ n $ vertices. For each vertex $ v $ from $ 0 $ to $ n-1 $ he wrote down two integers, $ degree_{v} $ and $ s_{v} $ , were the first integer is the number of vertices adjacent to vertex $ v $ , and the second integer is the XOR sum of the numbers of vertices adjacent to $ v $ (if there were no adjacent vertices, he wrote down $ 0 $ ).

Next day Misha couldn't remember what graph he initially had. Misha has values $ degree_{v} $ and $ s_{v} $ left, though. Help him find the number of edges and the edges of the initial graph. It is guaranteed that there exists a forest that corresponds to the numbers written by Misha.

## 说明/提示

The XOR sum of numbers is the result of bitwise adding numbers modulo $ 2 $ . This operation exists in many modern programming languages. For example, in languages C++, Java and Python it is represented as "^", and in Pascal — as "xor".

## 样例 #1

### 输入

```
3
2 3
1 0
1 0
```

### 输出

```
2
1 0
2 0
```

## 样例 #2

### 输入

```
2
1 1
1 0
```

### 输出

```
1
0 1
```

# 题解

## 作者：_H17_ (赞：4)

## 题目分析

边数显然是度的和除以二，原因是每个边造成两个度（起点、终点）。

类似于拓扑排序，每次度为 $1$ 的点的答案都是唯一确定的，然后在通过他们衍生出其他的点（去掉这个点的异或），可以使用堆来维护当前度最小的点，显然一开始是 $1$。

度是 $1$ 的点的值异或后还是那个数本身，直接扔进堆里即可，有点类似 Dijkstra 的堆。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int N=1e5+1;
int n,d[N],val[N],sum;
template<class T>struct cmp{
	bool operator()(T a,T b){
		return b.second<a.second;
	}
};
priority_queue<pair<int,int>,vector<pair<int,int> >,cmp<pair<int,int> > >q;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>d[i]>>val[i];
        q.push({i,d[i]});
        sum+=d[i];
    }
    cout<<sum/2<<'\n';//边
    while(!q.empty()){
        auto[cur,deg]=q.top();
        q.pop();
        if(!deg||deg!=d[cur])
            continue;//特殊处理根，重复的不走
        int tar=val[cur];//堆顶肯定是度数为1，直接就是下一个点
        cout<<cur<<' '<<tar<<'\n';
        val[tar]^=cur;//解异或
        if(--d[tar])
            q.push({tar,d[tar]});//继续
    }
    return 0;
}
```

---

## 作者：lichenxi111 (赞：4)

~~很像交互题~~

## 题意

告诉你树上每个节点与他相邻节点的异或和，让你还原出整个树。

## 思路

重点是拓扑排序，下文为实现。

每个节点都有一个度 $du[i]$ 和 异或值 $a[i]$。

因为是一棵树，所以我们发现对于每个叶子节点（$du[i] = 1$），他相邻的点有且仅有他的父亲，因此，我们可以从叶子节点往父亲节点推，每删一个叶子节点，就让他的父亲的 $du[i]$ 减 $1$，同时更新父亲的 $a[i]$，把一个节点的所有孩子都删完，我们也就知道了这个节点的父亲是谁。

把所有叶子节点都删完后，他们的父亲就变成了叶子节点，以此类推。直到遇到一个点的 $du[i] = 0$，这个点就是根。

---

## 作者：World_Creater (赞：3)

简单题。

考虑到度为 $1$ 的节点与他相邻的点可以确定，于是可以像拓扑排序那样不断加叶子，删边。

没了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d[100005],a[100005];
vector<pair<int,int> > ans;
queue<int> q;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>d[i]>>a[i];
	}
	for(int i=0;i<n;i++)
	{
		if(d[i]==1) 
		{
			q.emplace(i);//加叶子
		}
	}
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		if(d[x]==0) continue ;
		d[x]--;
		d[a[x]]--;
		a[a[x]]^=x;
		ans.emplace_back(x,a[x]);//删掉叶子，加入边
		if(d[a[x]]==1)
		{
			q.emplace(a[x]);
		}
	}
	cout<<ans.size()<<"\n";
	for(auto i:ans)
	{
		cout<<i.first<<" "<<i.second<<"\n";
	}
}
```

---

## 作者：浮光掠影 (赞：0)

### 题目大意

给一个森林，有 $n$ 个点编号为 $0 \sim n-1$，告诉每个点的度数，和所有与他连边的结点编号的异或和，问这个森林是什么样子，输出边。

### 解题思路

从叶子结点考虑，叶子结点的异或和的值就是与它连边的点的编号，然后那个点的度数减 $1$，重复这样操作。

也就是：


```cpp
while(!q.empty())
{
    int nn=q.front();
    q.pop();
    if(in[nn]==0)continue;
    u[tot]=nn;
    v[tot++]=val[nn];
    val[val[nn]]^=nn;
    in[val[nn]]--;
    if(in[val[nn]]==1) q.push(val[nn]);
}
```


### Code

代码我就不放了。大家可以用这种题来练练数据结构。

---

