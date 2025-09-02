# Moving Pieces

## 题目描述

[problemUrl]: https://atcoder.jp/contests/acl1/tasks/acl1_c

$ N $ 行 $ M $ 列からなる盤面があります． この盤面の情報は $ N $ 個の文字列 $ S_1,S_2,\ldots,S_N $ によって表されます． 具体的には，上から $ i $ 行目，左から $ j $ 列目のマスの状態は，以下のように表されます．

- $ S_{i,j}= $`.` : このマスは空である．
- $ S_{i,j}= $`#` : このマスには障害物が置かれている．
- $ S_{i,j}= $`o` : このマスには $ 1 $ つの駒が置かれている．

yosupo くんが，これから以下の操作を繰り返します．

- 駒を $ 1 $ つ選び，$ 1 $ 個下，もしくは $ 1 $ 個右のマスに移動させる． ただし，他の駒もしくは障害物のあるマスに駒を移動させる操作は禁止されている． もちろん，駒が盤面を飛び出すような操作も行えない．

yosupo くんは，できるだけ多くの回数操作をしたいです． 操作回数の最大値を求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 50 $
- $ 1\ \leq\ M\ \leq\ 50 $
- $ S_i $ は，`.`,`#`,`o` からなる長さ $ M $ の文字列．
- $ 1\ \leq\ ( $ 駒の個数 $ )\leq\ 100 $． つまり，$ S_{i,j}= $`o` を満たす $ (i,j) $ の個数は $ 1 $ 個以上 $ 100 $ 個以下．

### Sample Explanation 1

以下のように $ 4 $ 回の操作を行えます． ``` o.. .o. ..o ... ... ... -&gt; ... -&gt; ... -&gt; ..o -&gt; ..o o.# o.# o.# o.# .o# ```

## 样例 #1

### 输入

```
3 3
o..
...
o.#```

### 输出

```
4```

## 样例 #2

### 输入

```
9 10
.#....o#..
.#..#..##o
.....#o.##
.###.#o..o
#.#...##.#
..#..#.###
#o.....#..
....###..o
o.......o#```

### 输出

```
24```

# 题解

## 作者：良心WA题人 (赞：1)

## 前言

太久没做网络流降智了，这种简单建图都不会了。难绷。

## 题意

给定一张网格图，每次操作可以选择一颗棋子向右或者向下，每个点同时只能出现一颗棋子，问最多操作多少次。

## 思路

数据范围挺小，考虑网络流。因为我们要计算最多操作多少次，所以应该是建费用流模型。下面思考如何去建图。

最显然的边，每操作一次费用加一。因为是最小费用最大流，所以连边权为 $-1$，流量正无穷的边。

下面思考如何满足每个点同时只会有一个点的要求。第一眼看上去考虑拆点，但是显然并非是每个点只能经过一次，所以不可行。注意到，因为每个点同时只会有一个棋子，所以每个棋子最终落在的位置上只会有一个棋子，那么可以考虑一个棋子最终会落在哪里，即源点向有棋子的点连流量为 $1$，费用为 $0$ 的边，每个格子向汇点连一条流量为 $1$，费用为 $0$ 的边。

不难发现这样是对的。因为若一个点的终点堵在了另一个点到终点的唯一道路上，可以交换他们的目的地，就不会有影响了。时间复杂度 $O(n^3m^3)$。但是众所周知费用流远远跑不满，所以可以通过此题。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2504,MM=20004;
int head[NN],ne[MM],e[MM],w[MM],c[MM],f[NN],d[NN],pre[NN],idx=-1,flow,cost,s,t;
bool st[NN];
char str[54][54];
void add(int u,int v,int l,int money)
{
    e[++idx]=v;
    ne[idx]=head[u];
    c[idx]=l;
    w[idx]=money;
    head[u]=idx;
    e[++idx]=u;
    ne[idx]=head[v];
    w[idx]=-money;
    head[v]=idx;
}
bool spfa()
{
    memset(f,0,sizeof(f));
    memset(d,0x3f,sizeof(d));
    queue<int>q;
    q.push(s);
    f[s]=1e9;
    d[s]=0;
    st[s]=true;
    while(q.size())
    {
        int u=q.front();
        q.pop();
        st[u]=false;
        for(int i=head[u];~i;i=ne[i])
        {
            int v=e[i];
            if(c[i]&&d[v]>d[u]+w[i])
            {
                f[v]=min(f[u],c[i]);
                d[v]=d[u]+w[i];
                pre[v]=i;
                if(st[v])
                    continue;
                q.push(v);
                st[v]=true;
            }
        }
    }
    return f[t]>0;
}
void EK()
{
    while(spfa())
    {
        flow+=f[t];
        cost+=d[t]*f[t];
        for(int i=t;i!=s;i=e[pre[i]^1])
        {
            c[pre[i]]-=f[t];
            c[pre[i]^1]+=f[t];
        }
    }
}
int n,m;
int get(int x,int y)
{
	return (x-1)*m+y;
}
int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    t=n*m+1;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str[i]+1);
		for(int j=1;j<=m;j++)
		{
			if(str[i][j]=='#')
				continue;
			if(str[i][j]=='o')
				add(s,get(i,j),1,0);
			if(i+1<=n)
				add(get(i,j),get(i+1,j),1e9,-1);
			if(j+1<=m)
				add(get(i,j),get(i,j+1),1e9,-1);
			add(get(i,j),t,1,0);
		}
	}
    EK();
    printf("%d",-cost);
    return 0;
}
```

---

