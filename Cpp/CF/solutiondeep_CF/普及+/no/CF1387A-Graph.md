# 题目信息

# Graph

## 题目描述

You are given an undirected graph where each edge has one of two colors: black or red.

Your task is to assign a real number to each node so that:

- for each black edge the sum of values at its endpoints is $ 1 $ ;
- for each red edge the sum of values at its endpoints is $ 2 $ ;
- the sum of the absolute values of all assigned numbers is the smallest possible.

Otherwise, if it is not possible, report that there is no feasible assignment of the numbers.

## 说明/提示

Note that in the second example the solution is not unique.

## 样例 #1

### 输入

```
4 4
1 2 1
2 3 2
1 3 2
3 4 1```

### 输出

```
YES
0.5 0.5 1.5 -0.5```

## 样例 #2

### 输入

```
2 1
1 2 1```

### 输出

```
YES
0.3 0.7```

## 样例 #3

### 输入

```
3 2
1 2 2
2 3 2```

### 输出

```
YES
0 2 0```

## 样例 #4

### 输入

```
3 4
1 2 2
2 2 1
2 1 1
1 2 2```

### 输出

```
NO```

# AI分析结果

【题目内容（中文重写）】
# 图

## 题目描述
给定一个无向图，其中每条边有两种颜色之一：黑色或红色。

你的任务是为每个节点分配一个实数，使得：
- 对于每条黑色边，其两个端点的值之和为 $1$；
- 对于每条红色边，其两个端点的值之和为 $2$；
- 所有分配数字的绝对值之和尽可能小。

否则，如果无法满足上述条件，则报告不存在可行的数字分配方案。

## 说明/提示
注意，在第二个样例中，解不是唯一的。

## 样例 #1
### 输入
```
4 4
1 2 1
2 3 2
1 3 2
3 4 1
```
### 输出
```
YES
0.5 0.5 1.5 -0.5
```

## 样例 #2
### 输入
```
2 1
1 2 1
```
### 输出
```
YES
0.3 0.7
```

## 样例 #3
### 输入
```
3 2
1 2 2
2 3 2
```
### 输出
```
YES
0 2 0
```

## 样例 #4
### 输入
```
3 4
1 2 2
2 2 1
2 1 1
1 2 2
```
### 输出
```
NO
```

【算法分类】
图论

【综合分析与结论】
这三道题解的核心思路都是将图中的边转化为方程，将问题转化为求解方程组是否有解以及求出绝对值最小解的问题。由于图不一定连通，所以都采用了对每个连通块分别处理的方法。
- **思路对比**：
    - chen_hx 的题解使用 `pair<int, int>` 来表示每个节点的值，通过 BFS 遍历连通块。
    - zjw806903 的题解使用 `num` 数组存储每个节点的系数和常数项，通过 DFS 遍历连通块。
    - Zikl 的题解使用 `a` 和 `b` 数组存储每个节点的系数和常数项，同样通过 DFS 遍历连通块。
- **算法要点**：
    - 对于每个连通块，先设一个节点的值为 $x$，然后用 $±x + b$ 的形式表示其他节点的值。
    - 若某个节点被多个方程组表示，通过解方程确定 $x$ 的值。
    - 若 $x$ 未被确定，利用绝对值之和的几何意义，将 $x$ 设为中位数以使得绝对值之和最小。
- **解决难点**：
    - 判断方程组是否有解，若出现矛盾则输出 `NO`。
    - 处理多解情况，找到使绝对值之和最小的解。

【所选的题解】
- chen_hx 的题解（4星）
    - 关键亮点：思路清晰，代码实现简洁，使用 `pair<int, int>` 来表示节点的值，方便处理方程。
- Zikl 的题解（4星）
    - 关键亮点：对不合法情况的判断和处理比较详细，对代码中的关键部分有注释说明。

【重点代码】
### chen_hx 的题解核心代码
```cpp
void solve(int s){
    coe[s]={1,0};
    queue<int> que;
    vis[s]=1;
    que.push(s);
    stop=0;
    while(que.size()){
        int u=que.front();
        sta[++stop]=u;
        que.pop();
        for(int e=last[u];e;e=d[e].p){
            int v=d[e].to,w=d[e].w;
            pii ev={-coe[u].first,w-coe[u].second};
            if(vis[v]){
                if(ev==coe[v])continue;
                if(ev.first==coe[v].first)exit(puts("NO")&0);
                double uu;
                uu=1.00*(coe[v].second-ev.second)/(1.00*(ev.first-coe[v].first));
                if(!calc[s])ans[s]=uu,calc[s]=1;
                else if(fabs(ans[s]-uu)>eps)exit(puts("NO")&0);
            }
            else{
                vis[v]=1;
                coe[v]=ev;
                que.push(v);
            }
        }
    }
    if(!calc[s]){
        for(int i=1;i<=stop;i++)
            mvp[i]=-coe[sta[i]].second/coe[sta[i]].first;
        sort(mvp+1,mvp+stop+1);
        ans[s]=mvp[(stop+1)/2];calc[s]=1;
    }
    for(int i=2;i<=stop;i++){
        ans[sta[i]]=coe[sta[i]].first*ans[s]+coe[sta[i]].second;
    }
}
```
**核心实现思想**：使用 BFS 遍历连通块，用 `coe` 数组存储每个节点的系数和常数项。若遇到矛盾则输出 `NO`，若 $x$ 未被确定，则将 $x$ 设为中位数。最后根据 $x$ 的值计算其他节点的值。

### Zikl 的题解核心代码
```cpp
void dfs(int x){
    vis[x]=1;
    stack_[++top]=x;int dd=e[x].size()-1;
    F(i,0,dd){
        int y=e[x][i].fi,w=e[x][i].sd;
        if(vis[y]){
            if(a[x]+a[y]==0&&b[x]+b[y]!=w){
                printf("NO");
                exit(0);
            }
            if(a[x]+a[y]!=0){
                int delta=(w-b[x]-b[y])/(a[x]+a[y]); 
                if(flag==1&&delta!=X){
                    printf("NO");
                    exit(0);
                }
                flag=1,X=delta; 
            }
        }
        else a[y]=-a[x],b[y]=w-b[x],dfs(y);
    }
}
```
**核心实现思想**：使用 DFS 遍历连通块，用 `a` 和 `b` 数组存储每个节点的系数和常数项。若遇到矛盾则输出 `NO`，若 $x$ 未被确定，则将 $x$ 设为中位数。

【关键思路或技巧】
- 将图中的边转化为方程，通过解方程来判断方程组是否有解。
- 对于多解情况，利用绝对值之和的几何意义，将 $x$ 设为中位数以使得绝对值之和最小。
- 对每个连通块分别处理，避免不同连通块之间的干扰。

【拓展思路】
同类型题或类似算法套路：
- 可以考虑在有向图中进行类似的赋值问题，边的约束条件可能会更加复杂。
- 增加边的颜色种类或约束条件，进一步拓展问题的难度。

【推荐题目】
- P1113 杂务
- P1341 无序字母对
- P1127 词链

【个人心得】
- chen_hx：提到“事实证明，码力很重要的”，强调了代码实现能力的重要性。
- Zikl：提到“本题唯一题解的马蜂太炸裂了”，可能是觉得之前的题解有些难以理解。 

---
处理用时：49.15秒