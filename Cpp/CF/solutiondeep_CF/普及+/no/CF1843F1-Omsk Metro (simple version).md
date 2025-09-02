# 题目信息

# Omsk Metro (simple version)

## 题目描述

This is the simple version of the problem. The only difference between the simple and hard versions is that in this version $ u = 1 $ .

As is known, Omsk is the capital of Berland. Like any capital, Omsk has a well-developed metro system. The Omsk metro consists of a certain number of stations connected by tunnels, and between any two stations there is exactly one path that passes through each of the tunnels no more than once. In other words, the metro is a tree.

To develop the metro and attract residents, the following system is used in Omsk. Each station has its own weight $ x \in \{-1, 1\} $ . If the station has a weight of $ -1 $ , then when the station is visited by an Omsk resident, a fee of $ 1 $ burle is charged. If the weight of the station is $ 1 $ , then the Omsk resident is rewarded with $ 1 $ burle.

Omsk Metro currently has only one station with number $ 1 $ and weight $ x = 1 $ . Every day, one of the following events occurs:

- A new station with weight $ x $ is added to the station with number $ v_i $ , and it is assigned a number that is one greater than the number of existing stations.
- Alex, who lives in Omsk, wonders: is there a subsegment $ \dagger $ (possibly empty) of the path between vertices $ u $ and $ v $ such that, by traveling along it, exactly $ k $ burles can be earned (if $ k < 0 $ , this means that $ k $ burles will have to be spent on travel). In other words, Alex is interested in whether there is such a subsegment of the path that the sum of the weights of the vertices in it is equal to $ k $ . Note that the subsegment can be empty, and then the sum is equal to $ 0 $ .

You are a friend of Alex, so your task is to answer Alex's questions.

 $ \dagger $ Subsegment — continuous sequence of elements.

## 说明/提示

Explanation of the first sample.

The answer to the second question is "Yes", because there is a path $ 1 $ .

In the fourth question, we can choose the $ 1 $ path again.

In the fifth query, the answer is "Yes", since there is a path $ 1-3 $ .

In the sixth query, we can choose an empty path because the sum of the weights on it is $ 0 $ .

It is not difficult to show that there are no paths satisfying the first and third queries.

## 样例 #1

### 输入

```
1
8
+ 1 -1
? 1 1 2
? 1 2 1
+ 1 1
? 1 3 -1
? 1 1 1
? 1 3 2
? 1 1 0```

### 输出

```
NO
YES
NO
YES
YES
YES```

## 样例 #2

### 输入

```
1
10
+ 1 -1
+ 1 -1
+ 3 1
+ 3 -1
+ 3 1
? 1 6 -1
? 1 6 2
? 1 2 0
? 1 5 -2
? 1 4 3```

### 输出

```
YES
NO
YES
YES
NO```

# AI分析结果

### 题目内容重写

#### 题目描述

这是问题的简单版本。简单版本和困难版本之间的唯一区别在于，在这个版本中 $u = 1$。

众所周知，Omsk 是 Berland 的首都。像任何首都一样，Omsk 拥有一个发达的地铁系统。Omsk 地铁由一定数量的站点组成，这些站点通过隧道连接，并且任意两个站点之间恰好有一条路径，该路径经过每个隧道不超过一次。换句话说，地铁是一棵树。

为了发展地铁并吸引居民，Omsk 使用了以下系统。每个站点都有自己的权重 $x \in \{-1, 1\}$。如果站点的权重为 $-1$，那么当 Omsk 居民访问该站点时，将收取 $1$ burle 的费用。如果站点的权重为 $1$，那么 Omsk 居民将获得 $1$ burle 的奖励。

Omsk 地铁目前只有一个编号为 $1$ 的站点，权重为 $x = 1$。每天，会发生以下事件之一：

- 一个新的站点，权重为 $x$，被添加到编号为 $v_i$ 的站点，并且它被分配一个比现有站点数量大一的编号。
- Alex，住在 Omsk，想知道：在顶点 $u$ 和 $v$ 之间的路径上是否存在一个子段 $ \dagger $（可能为空），通过沿着它旅行，可以恰好赚取 $k$ burles（如果 $k < 0$，这意味着旅行将花费 $k$ burles）。换句话说，Alex 感兴趣的是，是否存在这样一个路径的子段，使得其中顶点的权重之和等于 $k$。注意，子段可以为空，此时和为 $0$。

你是 Alex 的朋友，所以你的任务是回答 Alex 的问题。

$ \dagger $ 子段 —— 连续的元素序列。

#### 说明/提示

第一个样例的解释。

第二个问题的答案是“Yes”，因为存在路径 $1$。

在第四个问题中，我们可以再次选择路径 $1$。

在第五个问题中，答案是“Yes”，因为存在路径 $1-3$。

在第六个问题中，我们可以选择一个空路径，因为其上的权重和为 $0$。

不难证明，第一个和第三个问题没有满足条件的路径。

#### 样例 #1

##### 输入

```
1
8
+ 1 -1
? 1 1 2
? 1 2 1
+ 1 1
? 1 3 -1
? 1 1 1
? 1 3 2
? 1 1 0
```

##### 输出

```
NO
YES
NO
YES
YES
YES
```

#### 样例 #2

##### 输入

```
1
10
+ 1 -1
+ 1 -1
+ 3 1
+ 3 -1
+ 3 1
? 1 6 -1
? 1 6 2
? 1 2 0
? 1 5 -2
? 1 4 3
```

##### 输出

```
YES
NO
YES
YES
NO
```

### 算法分类
动态规划、树

### 题解分析与结论

#### 题解对比
1. **zhicheng 的题解**：通过树上 DP 计算每个节点的最大和最小子段和，利用离线处理询问。思路清晰，代码模块化，适合初学者理解。
2. **Prms_Prmt 的题解**：直接维护每个节点的最大和最小子段和，无需建树，代码简洁高效，适合有一定基础的读者。
3. **Auto_Accepted 的题解**：通过 DFS 维护节点的最大和最小值，思路与 zhicheng 类似，但代码实现稍显复杂。
4. **yangshengyu0719 的题解**：使用树剖分和线段树维护最大和最小子段和，适合高级读者，但代码复杂度较高。
5. **_masppy_ 的题解**：通过维护每个节点的最大和最小子段和，直接判断询问，代码简洁，思路清晰。

#### 最优题解
1. **Prms_Prmt 的题解**（5星）
   - 关键亮点：直接维护每个节点的最大和最小子段和，无需建树，代码简洁高效。
   - 代码实现：
     ```cpp
     int main(){
         scanf("%d",&t);
         while(t--) {
             tot=1;
             scanf("%d",&n);
             for(int i=1;i<=n;++i)
                 mxt[i]=mxs[i]=mns[i]=mnt[i]=0;
             mxt[tot]=1;
             mxs[tot]=1;
             for(int i=1;i<=n;++i) {
                 char s;
                 cin>>s;
                 if(s=='+') {
                     int f,x;
                     scanf("%d%d",&f,&x);
                     mxt[++tot]=max(mxt[f]+x,x);
                     mnt[tot]=min(mnt[f]+x,x);
                     mxs[tot]=max(mxt[tot],mxs[f]);
                     mns[tot]=min(mnt[tot],mns[f]);
                 }
                 else {
                     int u,v,k;
                     scanf("%d%d%d",&u,&v,&k);
                     if(mns[v]<=k&&k<=mxs[v])
                         printf("YES\n");
                     else  puts("NO");
                 }
             }
         }
     }
     ```

2. **_masppy_ 的题解**（4星）
   - 关键亮点：通过维护每个节点的最大和最小子段和，直接判断询问，代码简洁，思路清晰。
   - 代码实现：
     ```cpp
     int main(){
         scanf("%d",&t);
         while(t--) {
             scanf("%d",&n);
             int tot=1;
             mx[1]=mxsum[1]=1;
             mn[1]=mnsum[1]=0;
             for(int i=1;i<=n;i++) {
                 char c[10];
                 scanf("%s",c+1);
                 if(c[1]=='+') {
                     int x,y;
                     scanf("%d%d",&x,&y);
                     mx[++tot]=max(y,mx[x]+y);
                     mn[tot]=min(y,mn[x]+y);
                     mxsum[tot]=max(mx[tot],mxsum[x]);
                     mnsum[tot]=min(mn[tot],mnsum[x]);
                 }
                 else {
                     int u,v,x;
                     scanf("%d%d%d",&u,&v,&x);
                     if(mnsum[v]<=x&&mxsum[v]>=x) printf("YES\n");
                     else printf("NO\n");
                 }
             }
         }
     }
     ```

#### 关键思路总结
- **最大和最小子段和**：通过维护每个节点的最大和最小子段和，判断询问的值是否在两者之间。
- **无需建树**：直接通过父节点的信息更新子节点的信息，减少代码复杂度。
- **离线处理**：先建树再处理询问，简化问题。

#### 可拓展之处
- **树剖分**：对于更复杂的树结构，可以使用树剖分和线段树来维护最大和最小子段和。
- **动态树**：对于动态添加节点的树，可以使用动态树数据结构来维护信息。

#### 推荐题目
1. [P4513 小白逛公园](https://www.luogu.com.cn/problem/P4513)
2. [P3384 【模板】重链剖分/树链剖分](https://www.luogu.com.cn/problem/P3384)
3. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)

---
处理用时：57.18秒