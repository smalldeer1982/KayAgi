# 题目信息

# [BalticOI 1996] A FAST JOURNEY (Day 2)

## 题目描述

一侧的交通道路连接了许多城市。城市从 $1$ 到 $n$ 编号，其中 $n$ 是城市的数量。在奇数天，车辆按照交通指示的方向行驶，在偶数天，则沿相反的方向行驶。两个城市之间的道路长度用一个整数值来衡量——从一个城市到另一个城市的旅程的持续时间（以小时为单位），它与方向无关。  

编写一个程序来查找从城市 A 到城市 B 的路线，以便尽可能快地到达城市 B。  

旅程的第一天是奇数天。一天之内的旅程不能超过十二个小时。晚上必须在一个城市度过。行程可能会在第二天继续。

## 说明/提示

#### 数据规模与约定  
对于 $100 \%$ 的数据，$1 < n \le 100$，$1 \le k \le 1000$。
#### 样例说明  
![TuLi](https://cdn.luogu.com.cn/upload/image_hosting/onmlfj8f.png)
#### 分值说明  
本题分值按 BOI 原题设置，**满分** $35$ 。
#### 题目说明  
来源于 Baltic Olympiad in Informatics 1996 的 [Day 2:A FAST JOURNEY](https://boi.cses.fi/files/boi1996_day2.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
1 3
6 7
1 2 9
1 6 2
1 5 10
5 4 1
4 6 2
4 3 4
2 3 5```

### 输出

```
1 5 1 10
5 4 1 1
4 3 3 4```

# AI分析结果

### 综合分析与结论
这些题解主要围绕从城市 A 到城市 B 的最短路径问题展开，考虑了每天行驶时间限制、道路方向随日期奇偶变化以及可停留的情况。解题思路主要分为两类：一是使用最短路算法（如 Dijkstra、SPFA），以天数为第一关键字、当天剩余时间为第二关键字进行优化；二是采用深度优先搜索（DFS）或动态规划（DP）来遍历所有可能路径。

### 所选题解
- **作者：logfk（5星）**
    - **关键亮点**：思路清晰，详细解释了如何使用 Dijkstra 算法解决问题，考虑了停留情况，代码注释丰富，可读性高。
    - **核心代码**：
```cpp
struct node{
    int da,ti,np;
    friend bool operator < (node x,node y)
    {
        if(x.da==y.da) return x.ti>y.ti;
        return x.da>y.da;
    }
};
priority_queue<node> q;
//...
while(!q.empty())
{
    node nq=q.top();
    q.pop();
    if(nq.np==ed)
    {
        int cc=0;
        out(nq.np,cc);
        for(int i=cc-1;i>=0;i--)
        {
            cout<<ansp[i]<<" "<<ansx[i]<<" "<<anst[i]<<" "<<ansti[i]<<endl;
        }
        return 0;
    }
    x=nq.np;
    int d=nq.da,tt=nq.ti;
    for(int i=head[x];i;i=nxt[i])
    {
        int ft=to[i],ro=val[i];
        if(tt+ro<=12)
        {
            if(!vis[ft][d%2][tt+ro]&&d%2==fl[i])
            {
                if(d<hpt[ft]||(d==hpt[ft]&&tt+ro<hpla[ft]))
                {
                    pre[ft]=x;
                    hpt[ft]=d;
                    hpti[ft]=ro;
                    hpla[ft]=ro+tt;
                }
                vis[ft][d%2][tt+ro]=1;
                q.push((node){d,tt+ro,ft});
            }
        }
    }
    if(!vis[x][(d+1)%2][0])
    {
        q.push((node){d+1,0,x});
    }
}
```
    - **核心思想**：使用优先队列实现 Dijkstra 算法，以天数和当天剩余时间为关键字进行排序。在遍历邻接边时，判断当天剩余时间是否足够通过该边，若可以则更新距离和路径信息。同时，考虑在当前城市停留一天的情况。

- **作者：Y_ATM_K（4星）**
    - **关键亮点**：采用动态规划的方法，思路独特，详细解释了状态定义和转移方程，考虑了输出字典序最小方案的问题。
    - **核心代码**：
```cpp
bool f[N<<1][13][N];
int g[N<<1][13][N][3];
//...
for(int i=1;i<=n<<1&&!ansd;++i) {
    for(int j=0;j<=12;++j) {
        if(f[i][j][T]) {
            ansd=i,anst=j;
            break;
        }
        for(int k=1;k<=n;++k) {
            if(!f[i][j][k]) continue;
            if(i&1) {
                int sz=head1[k].size();
                for(int l=0;l<sz;++l) {
                    int v=head1[k][l].v,w=head1[k][l].w;
                    if(j+w<=12&&!f[i][j+w][v]) {
                        f[i][j+w][v]=1;
                        g[i][j+w][v][0]=i,g[i][j+w][v][1]=j,g[i][j+w][v][2]=k;
                    }
                }
            } else {
                int sz=head2[k].size();
                for(int l=0;l<sz;++l) {
                    int v=head2[k][l].v,w=head2[k][l].w;
                    if(j+w<=12&&!f[i][j+w][v]) {
                        f[i][j+w][v]=1;
                        g[i][j+w][v][0]=i,g[i][j+w][v][1]=j,g[i][j+w][v][2]=k;
                    }
                }
            }
            if(!f[i+1][0][k]) {
                f[i+1][0][k]=1;
                g[i+1][0][k][0]=i,g[i+1][0][k][1]=j,g[i+1][0][k][2]=k;
            }
        }
    }
}
out(ansd,anst,T);
```
    - **核心思想**：定义状态 $f_{i,j,k}$ 表示能否在第 $i$ 天走 $j$ 小时到达编号为 $k$ 的结点，通过状态转移方程更新状态。使用数组 $g$ 记录状态转移的前驱信息，最后通过递归输出路径。

### 最优关键思路或技巧
- **使用优先队列优化最短路算法**：以天数为第一关键字、当天剩余时间为第二关键字进行排序，确保优先处理天数少且当天剩余时间多的状态。
- **考虑停留情况**：在状态转移时，增加在当前城市停留一天的转移分支，避免遗漏可能的最优解。
- **记录路径信息**：使用额外的数组或结构体记录每个状态的前驱信息，方便最后输出最短路径。

### 可拓展之处
同类型题可能会有更多的限制条件，如不同时间段的道路通行规则不同、不同城市的停留成本不同等。可以采用类似的思路，通过增加状态维度来处理这些复杂情况。

### 推荐题目
- [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)：考察最短路算法和路径计数。
- [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)：基础的单源最短路径问题，可用于练习 Dijkstra 或 SPFA 算法。
- [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)：加强版的单源最短路径问题，需要使用堆优化的 Dijkstra 算法。

### 个人心得摘录与总结
- **作者：Y_ATM_K**：提到由于本题没有 spj，需要输出字典序最小的方案，解决方案是让记录状态转移前驱的数组 $g$ 存当前状态被推到的第一个状态，避免了因输出方案不符合要求而导致的错误。这提醒我们在解题时要仔细考虑题目要求和输出格式。

---
处理用时：45.05秒