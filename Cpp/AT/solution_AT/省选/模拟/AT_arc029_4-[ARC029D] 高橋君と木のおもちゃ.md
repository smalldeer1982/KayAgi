# [ARC029D] 高橋君と木のおもちゃ

## 题目描述

给定一棵大小为 $N$，根为 $1$ 的树，并指定树上边的方向为编号大的指向编号小的。给定树上点 $i$ 的权值为 $s_i$。

现在给定 $M$ 个操作。每个操作依次进行。对于每个操作 $i$，有参数 $t_i$，可以选择：

- 不进行操作
- 在树上任意选定一个节点 $u$ 。并对原树进行参数为 $t_i$ 的**上移操作**。

参数为 $t_i$ 的上移操作就是将原图中 $u$ 以及它的所有祖先（除了根）的权值向父亲节点上移一位（根节点权值被删除），然后再将 $s_u$ 设为 $t_i$。

求在经历 $M$ 次操作之后，最终整棵树的权值和最大是多少。

## 样例 #1

### 输入

```
7
4
7
5
1
5
2
4
1 2
1 3
1 4
2 5
2 6
6 7
8
2
8
1
3
6
3
7
5```

### 输出

```
40```

## 样例 #2

### 输入

```
6
21
5
5
5
5
5
1 2
1 3
1 4
1 5
1 6
5
8
8
8
8
8```

### 输出

```
46```

# 题解

## 作者：Doveqise (赞：1)

题目大意：  
高桥收到了妹妹作为生日礼物的木制玩具。
木制玩具由N个球和N-1个节构成。每个球的编号为1到N ，各节的编号为1到N-1。  
N-1个节连接着不同的2个球，这些全部从号码大的球朝向号码小的球。另外，球1以外的任何球都有从球向号码小的其他球方向移动的节点，每个球都正好可以存储1个整数。最初，球i (1≤i≤N)中存储整数si。  
高桥和妹妹一起使用手边的M个整数玩具做游戏，游戏的目的在于，木制玩具的各个球所存储的整数总和尽可能变大。  
高桥君进行M回以下的步骤。  
取出1个整数i(1≤i≤M)，取出的整数是ti。  
进行以下任一操作。  
- 对木制玩具什么都不做，扔掉整数ti。
- 从木制玩具的球中选择1，放置整数ti。  

当整数j被放置时，进行以下动作。
- j = 1时，球1舍弃原来保存的整数，保存球1所放置的整数。
- j≥2的时候，球j把原来存储的整数放到成为从球j出去的节目的地的球上，存储在球j中的整数。

在木制玩具的变化停止之前，高桥君和妹妹不能移动到下一步。
求出最终木质玩具的各球存储的整数的总和的最大值。  

分析：  
这道题一道典型DFS&&DP，vector存题中树，排一遍序然后DFS接着DP即可。  
有问题看代码↓

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll INF = 1LL << 58;
ll N, S[5000], M, T[5000];
vector<int>tree[5000];
ll dp[5001][5001],sz[5001];
void dfs(int idx){
  dp[idx][0]=0,dp[idx][1]=S[idx];sz[idx]=1;
  for(auto &to:tree[idx]){dfs(to);
    for(int i=sz[idx];i>0;i--) for(int j=sz[to];j>=0;j--) 
        dp[idx][i+j]=min(dp[idx][i+j],dp[idx][i]+dp[to][j]);
    sz[idx] += sz[to];}
  return;
}
int main(){
      ll all=0;scanf("%lld",&N);
      for(int i=0;i<N;i++){scanf("%lld",&S[i]);all+=S[i];}
      for(int i=1;i<N;i++){
            int a,b;scanf("%d%d",&a,&b);
            tree[a-1].push_back(b-1);}
      scanf("%lld",&M);for(int i=0;i<M;i++)scanf("%lld",&T[i]);
      sort(T,T+M,greater<>());
      fill_n(*dp,5001*5001,INF);
      dfs(0);ll ans=0,latte=0;int lim=min(N,M);
      for(int i = 0;i<=lim;i++) {
            ans=max(ans,all+latte-dp[0][i]);latte+=T[i];}
      printf("%lld\n",ans);
      return 0;
}

```


---

