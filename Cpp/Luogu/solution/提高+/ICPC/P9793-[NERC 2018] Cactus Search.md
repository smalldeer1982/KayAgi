# [NERC 2018] Cactus Search

## 题目背景

翻译自 [NERC 2018](https://neerc.ifmo.ru/archive/2018/neerc-2018-statement.pdf) C 题。

如果你想让数组问题更难解决，可以在树上解决；如果你想让树的问题更难解决，可以在仙人掌上解决。

## 题目描述

在前几年，就有过人提出了许多关于仙人掌——连通无向图的问题，其中每条边最多属于一个简单的循环。更加直观地说，仙人掌是一棵树的概括，在这棵树上允许有一些环。下面的图片给出了仙人掌的一个例子。

![](https://cdn.luogu.com.cn/upload/image_hosting/a44vr6aa.png)

你和 Chloe 在一个仙人掌上玩游戏，你有一株仙人掌，但是淘气的 Chloe 偷偷拿走了一个顶点 $v$，你需要在 $10$ 次以内猜出 $v$，如果你猜到了 $v$，那你就赢了，如果你猜测的是另一个点 $u$，Chloe 会告诉你一个点 $w$，其中 $w$ 到 $v$ 经过的边数严格小于 $u$ 到 $v$。

## 说明/提示

数据保证 $1 \leq n \leq 500$，$0 \leq m \leq 500$，$1 \leq k_i \leq 500$。

注：为了方便比对，在样例输入输出上加入了一些空行进行对齐，实际输入输出中没有这些空行。

## 样例 #1

### 输入

```
5 2
5 1 2 3 4 5
2 1 3

FOUND
GO 4
FOUND
GO 2
FOUND
GO 1
FOUND
GO 4
GO 5
FOUND```

### 输出

```




3
3
4
3
2
3
1
3
4
5```

# 题解

## 作者：FFTotoro (赞：2)

考虑每次选择一个点，使得不管回答哪一个结点，最终可能成为答案的点集最小化。

有结论：每次选出符合上面条件的一个点，必然可以使得最终点集的大小除以 $2$（证明可以考虑，假设询问 $u$，$v$ 为返回的结点，且有大于一半的点可以成为答案，即有一半的可以成为答案的点到 $u$ 的路径上经过了 $v$，那么询问 $v$ 更优）。于是询问次数不超过 $\lceil\log_2n\rceil$，可以通过。

找单个结点的时间复杂度为 $O(n^2)$，由于要找 $n$ 次所以时间复杂度为 $O(n^3)$。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int I=1e9;
int main(){
  ios::sync_with_stdio(false);
  int n,m; cin>>n>>m;
  vector f(n,vector<int>(n,I));
  for(int i=0;i<n;i++)
    f[i][i]=0;
  for(int i=0;i<m;i++){
    int s; cin>>s;
    vector<int> v(s);
    for(auto &i:v)cin>>i,i--;
    for(int i=1;i<s;i++)
      f[v[i-1]][v[i]]=f[v[i]][v[i-1]]=1;
  }
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      for(int k=0;k<n;k++)
        f[j][k]=min(f[j][k],f[j][i]+f[i][k]);
  for(int r=0;r<n;r++){
    vector<bool> b(n,true);
    while(1){
      int v=n+1,u=-1;
      for(int i=0;i<n;i++)
        if(b[i]){
          int s=0;
          for(int j=0;j<n;j++)
            if(b[j]&&f[i][j]==1){
              int c=0;
              for(int k=0;k<n;k++)
                c+=b[k]&&f[j][k]<f[i][k];
              s=max(s,c);
            }
          if(s<v)v=s,u=i;
        }
      cout<<u+1<<endl;
      string s; cin>>s;
      if(s=="FOUND")break;
      int x; cin>>x,x--;
      for(int i=0;i<n;i++)
        if(f[x][i]>=f[u][i])b[i]=false;
    }
  }
  return 0;
}
```

---

