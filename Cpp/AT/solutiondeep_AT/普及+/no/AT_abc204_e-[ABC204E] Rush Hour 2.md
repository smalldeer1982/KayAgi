# 题目信息

# [ABC204E] Rush Hour 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc204/tasks/abc204_e

AtCoder国には $ N $ 個の都市と $ M $ 本の道路があります。

都市には $ 1 $ から $ N $ の番号が、道路には $ 1 $ から $ M $ の番号が振られています。道路 $ i $ は都市 $ A_i $ と都市 $ B_i $ を双方向に結びます。

AtCoder国には時刻 $ 0 $ をピークとするラッシュアワーがあり、時刻 $ t $ に道路 $ i $ の通行を始めると、移動するのに $ C_i+\ \left\lfloor\ \frac{D_i}{t+1}\ \right\rfloor $ の時間がかかります。 ( $ \lfloor\ x\rfloor $ は $ x $ を超えない最大の整数を表す)

高橋君は時刻 $ 0 $ またはそれ以降の **整数時刻に** 都市 $ 1 $ を出発して、道路を通行することで都市 $ N $ へ向かおうとしています。

高橋君が各都市で **整数時間** 待機することができるとき、高橋君が都市 $ N $ に到達することができる最も早い時刻を出力してください。なお、制約の下で答えは整数になることが証明できます。

ただし、都市 $ N $ に到達できないときはかわりに `-1` を出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- $ 0\ \leq\ C_i,D_i\ \leq\ 10^9 $
- 入力は全て整数

### Sample Explanation 1

最初に都市 $ 1 $ で時刻 $ 1 $ まで待機します。そして時刻 $ 1 $ に道路 $ 1 $ を使って移動をすると、移動に $ 2+\left\lfloor\ \frac{3}{1+1}\ \right\rfloor\ =\ 3 $ の時間がかかり、都市 $ 2 $ には時刻 $ 4 $ に到着することができます。 時刻 $ 4 $ より早く都市 $ 2 $ に到着することはできません。

### Sample Explanation 2

同じ都市の組を結ぶ道路が複数ある場合や、同じ都市に戻ってくる道路がある場合もあります。

### Sample Explanation 3

都市 $ 1 $ から都市 $ N $ に至る経路がないこともあります。

## 样例 #1

### 输入

```
2 1

1 2 2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
2 3

1 2 2 3

1 2 2 1

1 1 1 1```

### 输出

```
3```

## 样例 #3

### 输入

```
4 2

1 2 3 4

3 4 5 6```

### 输出

```
-1```

## 样例 #4

### 输入

```
6 9

1 1 0 0

1 3 1 2

1 5 2 3

5 2 16 5

2 6 1 10

3 4 3 4

3 5 3 10

5 6 1 100

4 2 0 110```

### 输出

```
20```

# AI分析结果

【题目内容】
# [ABC204E] Rush Hour 2

## 题目描述

AtCoder国有 $ N $ 个城市和 $ M $ 条道路。城市编号为 $ 1 $ 到 $ N $，道路编号为 $ 1 $ 到 $ M $。道路 $ i $ 双向连接城市 $ A_i $ 和城市 $ B_i $。

AtCoder国有一个以时刻 $ 0 $ 为高峰的交通高峰期，如果在时刻 $ t $ 开始通过道路 $ i $，则通过该道路所需的时间为 $ C_i+\ \left\lfloor\ \frac{D_i}{t+1}\ \right\rfloor $。（$ \lfloor\ x\rfloor $ 表示不超过 $ x $ 的最大整数）

高桥君在时刻 $ 0 $ 或之后的**整数时刻**从城市 $ 1 $ 出发，通过道路前往城市 $ N $。高桥君可以在每个城市**整数时间**等待，求高桥君到达城市 $ N $ 的最早时间。如果无法到达城市 $ N $，则输出 `-1`。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i,B_i\ \leq\ N $
- $ 0\ \leq\ C_i,D_i\ \leq\ 10^9 $
- 输入均为整数

### 样例解释

样例1：在时刻 $ 1 $ 开始通过道路 $ 1 $，所需时间为 $ 2+\left\lfloor\ \frac{3}{1+1}\ \right\rfloor\ =\ 3 $，到达城市 $ 2 $ 的时间为 $ 4 $。

样例2：存在多条连接相同城市的道路或返回原城市的道路。

样例3：从城市 $ 1 $ 到城市 $ N $ 可能没有路径。

【算法分类】最短路

【题解分析与结论】
该题的核心在于通过分析函数 $f(t) = t + c + \lfloor \frac{d}{t+1} \rfloor$ 的最小值，确定在何时通过道路是最优的。大多数题解都通过均值不等式得出 $t = \sqrt{d} - 1$ 时函数取得最小值，并在此基础上使用 Dijkstra 算法求解最短路。部分题解还考虑了浮点数精度问题，并使用了并查集来判断图的连通性。

【评分较高的题解】

1. **作者：_Ponder_ (赞：2)**
   - **星级：4**
   - **关键亮点：**
     - 通过均值不等式得出 $t = \sqrt{d} - 1$ 时函数取得最小值。
     - 使用 Dijkstra 算法求解最短路，并在转移时判断是否需要等待。
     - 使用并查集判断图的连通性，避免不必要的计算。
   - **核心代码：**
     ```cpp
     void Dijkstra(){
         memset(dis,0x3f,sizeof dis);
         dis[1]=0;q.push(Node{1,0});
         while(!q.empty()){
             now=q.top();q.pop();
             if(vis[now.x]) continue;
             vis[now.x]=1;
             for(int i=head[now.x];i;i=nxt[i]){
                 int v=to[i],t;
                 if(now.time<=round(sqrt(d[i]))-1) t=round(sqrt(d[i]))-1;
                 else t=now.time;
                 if(dis[v]>t+c[i]+d[i]/(t+1)){
                     dis[v]=t+c[i]+d[i]/(t+1);
                     q.push(Node{v,dis[v]});
                 }
             }
         }
     }
     ```

2. **作者：zhujiangyuan (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 通过基本不等式得出 $t = \sqrt{d} - 1$ 时函数取得最小值。
     - 使用 Dijkstra 算法求解最短路，并在转移时判断是否需要等待。
     - 代码简洁，逻辑清晰。
   - **核心代码：**
     ```cpp
     void Dijkstra(){
         memset(dis,0x3f,sizeof dis);
         dis[1]=0;q.push(Node{1,0});
         while(!q.empty()){
             now=q.top();q.pop();
             if(vis[now.x]) continue;
             vis[now.x]=1;
             for(int i=head[now.x];i;i=nxt[i]){
                 int v=to[i],t;
                 if(now.time<=round(sqrt(d[i]))-1) t=round(sqrt(d[i]))-1;
                 else t=now.time;
                 if(dis[v]>t+c[i]+d[i]/(t+1)){
                     dis[v]=t+c[i]+d[i]/(t+1);
                     q.push(Node{v,dis[v]});
                 }
             }
         }
     }
     ```

3. **作者：This_Rrhar (赞：1)**
   - **星级：4**
   - **关键亮点：**
     - 通过求导得出 $t = \sqrt{d} - 1$ 时函数取得最小值。
     - 使用 Dijkstra 算法求解最短路，并在转移时判断是否需要等待。
     - 代码实现简洁，逻辑清晰。
   - **核心代码：**
     ```cpp
     void dijkstra(){
         memset(dis,0x3f,sizeof(dis)),dis[1]=0,q.push({1,0});
         while(!q.empty()){
             node u=q.top();
             q.pop();
             if(!vis[u.i]){
                 vis[u.i]=true;
                 for(auto i:e[u.i]){
                     ll t=nd(u.t,i.x,i.y,i.sq);
                     if(t<dis[i.v])q.push({i.v,dis[i.v]=t});
                 }
             }
         }
     }
     ```

【最优关键思路或技巧】
1. **函数分析**：通过均值不等式或求导得出 $t = \sqrt{d} - 1$ 时函数 $f(t) = t + c + \lfloor \frac{d}{t+1} \rfloor$ 取得最小值。
2. **Dijkstra 算法**：在转移时判断当前时间是否小于 $\sqrt{d} - 1$，如果是则等待，否则立即出发。
3. **并查集**：用于判断图的连通性，避免不必要的计算。

【可拓展之处】
该题的思路可以拓展到其他涉及时间依赖的最短路问题，例如在某些时间段内通过某条路径的代价不同，或者通过某条路径的代价随时间变化。

【推荐题目】
1. [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)
2. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
3. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)

---
处理用时：44.68秒