# Circle of Numbers

## 题目描述

有一天，Vasya走到黑板前，把 $1$ 到 $n$ 之间的不同整数按一定的顺序画成一个圆圈。然后他画弧来连接整数对 $(a,b)\ (a≠b)$，它们要么在圆相邻，要么有数字 $c$，使得 $a$ 和 $c$ 相邻，并且 $b$ 和 $c$ 相邻。易得出，瓦西亚最后画了 $2n$ 条弧。

例如，如果将数字 $1,2,3,4,5$ 以顺时针方向写入圆中，则弧将连接整数对 $(1,2)$，$(2,3)$，$(3,4)$，$(4,5)$，$(5,1)$，$(1,3)$，$(2,4)$，$(3,5)$，$(4,1)$ 和 $(5,2)$。

后来，黑板上的数字被抹去了。但 Vasya 发现了一张纸，上面写着 $2n$ 个整数对，它们对应着原来黑板上的每个圆弧相联的数对。Vasya 要求您通过这些数对查找圆圈中原有的数字顺序。

## 样例 #1

### 输入

```
5
1 2
2 3
3 4
4 5
5 1
1 3
2 4
3 5
4 1
5 2
```

### 输出

```
1 2 3 4 5 ```

## 样例 #2

### 输入

```
6
5 6
4 3
5 3
2 4
6 1
3 1
6 2
2 5
1 4
3 6
1 2
4 5
```

### 输出

```
1 2 4 5 3 6 ```

# 题解

## 作者：_edge_ (赞：0)

首先，可以明确，如果一个数出现的次数超过了 $4$ 次，那么这个肯定构造不成了，直接输出 `-1`，这个结论很好证，因为没有重复的数对，所以一个数只有可能连出去连到左边右边，或者左边的左边，右边的右边，如果存在出现重复的数对，显然不会成立。

然后我们考虑当前这个 $1$，因为输出的顺序是任意的，不妨将 $1$ 变为第 $1$ 个数。

然后我们就会发现这个东西非常难做，因为他有好几种可能性，但是想到之前那个结论，所在的数对仅有 $4$ 对，不妨确定第 $1,2,3$ 个位置所有的数。

确定完了这个之后，我们就能推出下一个数了，假设其为 $a_i$，我们知道 $a_{i-2}$，他所在的数对有两个已经确定了，分别为 $(a_{i-2},a_{i-1})$ 和 $(a_{i-3},a_{i-2})$，那么还剩下 $2$ 个，分别是 $(a_{i-2},a_{i})$ 和 $(a_{i-2},a_{i-4})$，但是我们又知道 $a_{i-1}$，因为 $(a_{i-1},a_{i-4})$ 是不可能存在的，所以可以放心大胆的枚举了。

总时间复杂度是 $O(n)$ 的。

```cpp
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
const int INF=5e5+5;
int n,in[INF],fl,vis[INF];
map <int,map<int,int> > Map;
struct _node_edge{
    int to_,next_;
}edge[INF<<1];
int head[INF],tot,d[INF];
void add_edge(int x,int y) {
    edge[++tot]=(_node_edge){y,head[x]};
    head[x]=tot;return ;
}
void DFS(int xx) {
    if (xx>n) {
        // for (int i=1;i<=n;i++)
        //     cout<<d[i]<<" ";
        // cout<<Map[1][5]<<" "<<Map[d[1]][d[n-1]]<<" "<<Map[d[2]][d[n]]<<"\n";
        if (Map[d[n]][d[1]] && Map[d[n-1]][d[1]] && Map[d[n]][d[2]]) {
                for (int i=1;i<=n;i++)
                    cout<<d[i]<<" ";
                fl=1;
                return ;
            }
        return ;
    }
    for (int i=head[d[xx-1]];i;i=edge[i].next_) {
        int v=edge[i].to_;
        if (!Map[d[xx-1]][v] && !Map[v][d[xx-1]]) continue;
        if (!Map[d[xx-2]][v] && !Map[v][d[xx-2]]) continue;
        if (vis[v]) continue;
        d[xx]=v;
        vis[v]=1;
        DFS(xx+1);
        vis[v]=0;
        if (fl) return ;
    }
    return ;
}
signed main()
{
    scanf("%d",&n);
    for (int i=1;i<=n*2;i++) {
        int a=0,b=0;
        scanf("%d %d",&a,&b);
        in[a]++;in[b]++;
        if (in[a]>4 || in[b]>4) {
            cout<<"-1\n";
            return 0;
        }
        add_edge(a,b);add_edge(b,a);
        Map[a][b]=Map[b][a]=1;
    }
    d[1]=1;
    for (int i=head[1];i;i=edge[i].next_) {
        for (int j=head[1];j;j=edge[j].next_) {
            int v=edge[i].to_,v1=edge[j].to_;
            if (v==v1) continue;
            // cout<<v<<" "<<v1<<" over1\n";
            if (!Map[v][v1] && !Map[v1][v]) continue;
            // cout<<v<<" "<<v1<<" over\n";
            d[2]=v;d[3]=v1;Map[v][1]=0;
            Map[v1][1]=0;Map[v][v1]=0;
            Map[1][v]=0;
            Map[1][v1]=0;Map[v1][v]=0;
            vis[1]=vis[v]=vis[v1]=1;
            DFS(4);
            if (fl) return 0;
            Map[v][1]=1;
            Map[v1][1]=1;Map[v][v1]=1;
            Map[1][v]=1;
            Map[1][v1]=1;Map[v1][v]=1;
            vis[1]=vis[v]=vis[v1]=0;
        }
    }
    cout<<"-1\n";
    return 0;
}
```


---

