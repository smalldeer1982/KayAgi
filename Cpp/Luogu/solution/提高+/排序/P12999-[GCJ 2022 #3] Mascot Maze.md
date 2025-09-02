# [GCJ 2022 #3] Mascot Maze

## 题目描述

Google 编程竞赛团队正在筹建一个新的主题公园。和所有优秀的主题公园一样，我们希望让演员装扮成吉祥物与游客互动。由于开业在即，我们决定使用 CODE JAM、KICK START 和 HASH CODE 中的字母作为吉祥物，共计 13 种不同的吉祥物（字母 `ACDEHIJKMORST`）。

公园唯一的景点是一个由 $\mathbf{N}$ 个房间组成的迷宫，房间编号从 1 到 $\mathbf{N}$。每个房间都有一个左出口和一个右出口。每个出口会将游客带到另一个房间。出口不能反向使用；例如，如果房间 2 有一个出口通向房间 3，你不能从房间 3 返回到房间 2，除非房间 3 恰好也有一个出口通向房间 2。

![](https://cdn.luogu.com.cn/upload/image_hosting/8fuhdtgj.png)

我们希望在每个房间放置恰好一个这 13 种吉祥物。每个字母可以在迷宫的零个、一个或多个房间中出现。为了增加多样性，我们希望这样放置吉祥物：游客连续访问的任意三个（不一定不同）房间中的吉祥物必须互不相同。

你能帮助我们为每个房间选择一个吉祥物来满足这一目标吗？或者告诉我们这是不可能实现的？


## 说明/提示

**样例解释**

样例 #1 对应题目描述中的图片。游客可以连续访问房间 1、2、1（其中房间 1 被访问两次），因此这种情况不可能满足要求。

样例 #2 的布局如下（蓝色箭头表示左出口，红色箭头表示右出口）：

![](https://cdn.luogu.com.cn/upload/image_hosting/ykiviiry.png)

众多有效解之一如输出所示。注意虽然我们不需要分配两个 $\tau$ 吉祥物，但当前的分配方式不会违反规则。

样例 #3 和 #4 是可行的，但需要重复使用某些吉祥物。

**限制**

- $1 \leq \mathbf{T} \leq 100$。
- 对于所有 $i$，$\mathbf{L}_i \neq i$ 且 $\mathbf{R}_i \neq i$。
- 对于所有 $i$，$1 \leq \mathbf{L}_i < \mathbf{R}_i \leq \mathbf{N}$。

**测试集 1（12 分，可见判题结果）**

- 时间限制：20 秒。
- $3 \leq \mathbf{N} \leq 100$。

**测试集 2（13 分，隐藏判题结果）**

- 时间限制：45 秒。
- $3 \leq \mathbf{N} \leq 10^5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3
2 1 1
3 3 2
6
3 1 4 1 2 3
5 3 5 2 4 5
20
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 1 1
3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 20 2
19
2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 1 1
3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 19 3```

### 输出

```
Case #1: IMPOSSIBLE
Case #2: TSHIRT
Case #3: HCJKSHCJKSHCJKSHCJKS
Case #4: CODEJAMROCKSTHEMOST```

# 题解

## 作者：FFTotoro (赞：2)

感觉是挺好的 trick。

这题是图的点染色问题的特殊情况，注意到原图上每个点的出度都最多为 $6$，所以建出“矛盾图”（即对于不能颜色相同的点连边）之后，最小度数的点度数不超过 $12$。

证明：其中 $6$ 个为原来的“出度”，由于有向图出度和不超过 $6n$ 故入度也不超过 $6n$，所以度数最小的点入度和必然不超过 $6$，即平均值，所以度数最多为 $12$。

每次删掉一个度数 $\le 12$ 的点和与它相连的边之后，图仍然满足这个性质。最后倒着推回来，由于颜色有 $13$ 种所以填完 $12$ 条出边以后至少剩下一种，故方案一定合法。

使用队列进行 BFS 模拟删掉度数 $\le 12$ 的点，前面的去重环节需要带个 $\log$，总时间复杂度 $O(TN\log N)$。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const string S="ACDEHIJKMORST";
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int tt; cin>>tt;
  for(int t=1;t<=tt;t++){
    int n; cin>>n;
    vector<int> l(n),r(n);
    for(auto &i:l)cin>>i,i--;
    for(auto &i:r)cin>>i,i--;
    vector<vector<int> > g(n);
    bool f=true;
    for(int u=0;u<n&&f;u++)
      for(int i:{l[u],r[u]}){
        g[u].emplace_back(i);
        g[i].emplace_back(u);
        for(int j:{l[i],r[i]}){
          if(u==j){f=false; break;}
          g[u].emplace_back(j);
          g[j].emplace_back(u);
        }
      } // 建出“矛盾图”
    cout<<"Case #"<<t<<": ";
    if(!f){cout<<"IMPOSSIBLE\n"; continue;}
    vector<int> d(n),v,c(n,-1);
    vector<bool> b(n);
    queue<int> q;
    for(int u=0;u<n;u++){
      sort(g[u].begin(),g[u].end());
      g[u].erase(unique(g[u].begin(),g[u].end()),g[u].end());
      if((d[u]=g[u].size())<=12)b[u]=true,q.emplace(u);
    } // 对边去重，并加入初始时度数不大于 12 的点
    while(!q.empty()){
      int u=q.front(); q.pop();
      v.emplace_back(u);
      for(int i:g[u])
        if(--d[i]<=12&&!b[i])b[i]=true,q.emplace(i);
    } // 执行一个类似拓扑排序的过程
    reverse(v.begin(),v.end());
    for(int u:v){
      vector<bool> b(13);
      for(int i:g[u])
        if(~c[i])b[c[i]]=true;
      for(int i=0;i<13;i++)
        if(!b[i]){c[u]=i; break;}
    } // 倒推回来染色
    for(int i:c)cout<<S[i];
    cout<<'\n';
  }
  return 0;
}
```

---

## 作者：水星湖 (赞：2)

不是哥们这 $13$ 真有用啊？

考虑原图 $(u,v),(v,w)$ 的有向边，这样的 $(u,v,w)$ 只有 $4n$ 个，限制是 $(u,v,w)$ 颜色不同，把 $(w,u)$ 也连上，形成一个新图，限制就是相邻点颜色不同，由于新图只有 $6n$ 个边，这样至少有一个点度数 $\le12$，从这个点开始删，任意时刻就都会有度数 $\le 12$ 的点，因为有 $13$ 种字母就做完了。

---

