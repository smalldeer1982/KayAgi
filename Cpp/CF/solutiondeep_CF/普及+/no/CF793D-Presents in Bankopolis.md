# 题目信息

# Presents in Bankopolis

## 题目描述

Bankopolis is an incredible city in which all the $ n $ crossroads are located on a straight line and numbered from $ 1 $ to $ n $ along it. On each crossroad there is a bank office.

The crossroads are connected with $ m $ oriented bicycle lanes (the $ i $ -th lane goes from crossroad $ u_{i} $ to crossroad $ v_{i} $ ), the difficulty of each of the lanes is known.

Oleg the bank client wants to gift happiness and joy to the bank employees. He wants to visit exactly $ k $ offices, in each of them he wants to gift presents to the employees.

The problem is that Oleg don't want to see the reaction on his gifts, so he can't use a bicycle lane which passes near the office in which he has already presented his gifts (formally, the $ i $ -th lane passes near the office on the $ x $ -th crossroad if and only if $ min(u_{i},v_{i})&lt;x&lt;max(u_{i},v_{i}))) $ . Of course, in each of the offices Oleg can present gifts exactly once. Oleg is going to use exactly $ k-1 $ bicycle lane to move between offices. Oleg can start his path from any office and finish it in any office.

Oleg wants to choose such a path among possible ones that the total difficulty of the lanes he will use is minimum possible. Find this minimum possible total difficulty.

## 说明/提示

In the first example Oleg visiting banks by path $ 1→6→2→4 $ .

Path $ 1→6→2→7 $ with smaller difficulity is incorrect because crossroad $ 2→7 $ passes near already visited office on the crossroad $ 6 $ .

In the second example Oleg can visit banks by path $ 4→1→3 $ .

## 样例 #1

### 输入

```
7 4
4
1 6 2
6 2 2
2 4 2
2 7 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 3
4
2 1 2
1 3 2
3 4 2
4 1 1
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# Bankopolis的礼物

## 题目描述
Bankopolis是一座令人惊叹的城市，其中所有的 $n$ 个十字路口都位于一条直线上，并从1到 $n$ 依次编号。在每个十字路口都有一家银行办公室。

这些十字路口由 $m$ 条有向自行车道连接（第 $i$ 条车道从十字路口 $u_i$ 通向十字路口 $v_i$ ），每条车道的难度已知。

银行客户Oleg想要给银行员工送去幸福和欢乐。他想拜访恰好 $k$ 个办公室，在每个办公室他都想给员工送礼物。

问题是Oleg不想看到人们对他礼物的反应，所以他不能使用经过他已经送过礼物的办公室附近的自行车道（正式地说，第 $i$ 条车道经过 $x$ 号十字路口的办公室附近，当且仅当 $min(u_i, v_i) < x < max(u_i, v_i)$ ）。当然，在每个办公室Oleg只能送一次礼物。Oleg打算恰好使用 $k - 1$ 条自行车道在办公室之间移动。Oleg可以从任何办公室开始他的行程，并在任何办公室结束。

Oleg想从所有可能的路径中选择一条，使得他将使用的车道的总难度尽可能小。找出这个最小的可能总难度。

## 说明/提示
在第一个例子中，Oleg按路径 $1→6→2→4$ 拜访银行。

路径 $1→6→2→7$ 难度更小但不正确，因为从 $2→7$ 的十字路口经过了已经拜访过的6号十字路口的办公室附近。

在第二个例子中，Oleg可以按路径 $4→1→3$ 拜访银行。

## 样例 #1
### 输入
```
7 4
4
1 6 2
6 2 2
2 4 2
2 7 1
```
### 输出
```
6
```

## 样例 #2
### 输入
```
4 3
4
2 1 2
1 3 2
3 4 2
4 1 1
```
### 输出
```
3
```

### 算法分类
动态规划

### 综合分析与结论
这两道题解均采用动态规划的方法解决问题，核心思路都是通过记录可到达的区间以及当前所在端点来进行状态转移。xzggzh1的题解使用递推方式，船酱魔王的题解使用记忆化搜索方式。二者都利用了问题中每经过一条边可到达边范围缩小的特性，通过合理设计状态和转移方程来求解。

### 所选的题解
- **xzggzh1的题解**：
  - **星级**：4星
  - **关键亮点**：使用滚动数组优化空间复杂度，代码简洁紧凑，递推方式逻辑清晰。
  - **重点代码**：
```cpp
const int N=85;
int n,K,m,u,v,c,cc[N][N],f[2][N][N][2],i,j,k,nw,ans=1<<30;
int main(){
    memset(cc,1,sizeof cc);
    scanf("%d%d%d",&n,&K,&m);
    while(m--)scanf("%d%d%d",&u,&v,&c),cc[u][v]=min(cc[u][v],c);
    memset(f[0],1,sizeof f[0]);
    for(i=1;i<=n;++i)f[0][0][i][1]=f[0][i][n+1][0]=0;
    while(--K){
        nw^=1;memset(f[nw],1,sizeof f[nw]);
        for(i=0;i<=n-1;++i)for(j=i+2;j<=n+1;++j)for(k=i+1;k<j;++k){
            f[nw][i][k][1]=min(f[nw][i][k][1],min(f[!nw][i][j][1]+cc[j][k],f[!nw][i][j][0]+cc[i][k]));
            f[nw][k][j][0]=min(f[nw][k][j][0],min(f[!nw][i][j][0]+cc[i][k],f[!nw][i][j][1]+cc[j][k]));
        }
    }
    for(i=0;i<=n+1;++i)for(j=0;j<=n+1;++j)ans=min(ans,min(f[nw][i][j][0],f[nw][i][j][1]));
    if(ans>1<<20)ans=-1;
    printf("%d\n",ans);
}
```
  - **核心实现思想**：定义状态 $f[i][j][k][0/1]$ 表示经过 $i$ 个点，可去区间是 $[j,k]$ ，当前在左端点或右端点。通过三重循环遍历不同状态，根据前一状态和边权进行状态转移，最后遍历所有状态取最小值得到答案。

- **船酱魔王的题解**：
  - **星级**：4星
  - **关键亮点**：使用记忆化搜索实现DP，代码结构清晰，状态转移方程直观。
  - **重点代码**：
```cpp
int solve(int l, int r, int st, int ps) {
    if(dp[l][r][st][ps]!= -1) {
        return dp[l][r][st][ps];
    }
    if(st == 1) {
        return dp[l][r][st][ps] = 0;
    }
    if(l >= r - 1) {
        return inf;
    }
    dp[l][r][st][ps] = inf;
    if(ps == 0) {
        for(int i = 0; i < g[l].size(); i++) {
            int v = g[l][i].to;
            int w = g[l][i].w;
            if(l < v && v < r) {
                dp[l][r][st][ps] = min(dp[l][r][st][ps], min(solve(l, v, st - 1, 1), solve(v, r, st - 1, 0)) + w);
            }
        }
    } else {
        for(int i = 0; i < g[r].size(); i++) {
            int v = g[r][i].to;
            int w = g[r][i].w;
            if(l < v && v < r) {
                dp[l][r][st][ps] = min(dp[l][r][st][ps], min(solve(l, v, st - 1, 1), solve(v, r, st - 1, 0)) + w);
            }
        }
    }
    return dp[l][r][st][ps];
}
```
  - **核心实现思想**：定义状态 $dp[l][r][st][ps]$ 表示可选点范围 $(l,r)$ ，还需走 $st$ 步，当前在 $ps$ 端点。通过记忆化搜索，根据当前状态和边权递归计算下一状态，从而得到答案。

### 最优关键思路或技巧
二者都巧妙地利用动态规划，将问题状态与可到达区间及当前端点相关联，通过合理设计状态转移方程来解决问题。在实现上，xzggzh1使用滚动数组优化空间，船酱魔王使用记忆化搜索使代码结构更清晰。

### 同类型题或类似算法套路拓展
此类题目通常涉及路径选择并带有一定限制条件，一般可以考虑通过状态压缩或记录关键信息来设计动态规划状态，根据题目限制设计状态转移方程。

### 洛谷相似题目推荐
- [P1896 [SCOI2005] 互不侵犯](https://www.luogu.com.cn/problem/P1896)
- [P3211 [HNOI2011] 防线修建](https://www.luogu.com.cn/problem/P3211)
- [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

---
处理用时：62.29秒