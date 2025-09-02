# 题目信息

# Test of Love

## 题目描述

ErnKor is ready to do anything for Julen, even to swim through crocodile-infested swamps. We decided to test this love. ErnKor will have to swim across a river with a width of $ 1 $ meter and a length of $ n $ meters.

The river is very cold. Therefore, in total (that is, throughout the entire swim from $ 0 $ to $ n+1 $ ) ErnKor can swim in the water for no more than $ k $ meters. For the sake of humanity, we have added not only crocodiles to the river, but also logs on which he can jump. Our test is as follows:

Initially, ErnKor is on the left bank and needs to reach the right bank. They are located at the $ 0 $ and $ n+1 $ meters respectively. The river can be represented as $ n $ segments, each with a length of $ 1 $ meter. Each segment contains either a log 'L', a crocodile 'C', or just water 'W'. ErnKor can move as follows:

- If he is on the surface (i.e., on the bank or on a log), he can jump forward for no more than $ m $ ( $ 1 \le m \le 10 $ ) meters (he can jump on the bank, on a log, or in the water).
- If he is in the water, he can only swim to the next river segment (or to the bank if he is at the $ n $ -th meter).
- ErnKor cannot land in a segment with a crocodile in any way.

Determine if ErnKor can reach the right bank.

## 说明/提示

Let's consider examples:

- First example: We jump from the shore to the first log ( $ 0 \rightarrow 1 $ ), from the first log to the second ( $ 1 \rightarrow 3 $ ), from the second to the fourth ( $ 3 \rightarrow 5 $ ), and from the last log to the shore ( $ 5 \rightarrow 7 $ ). So, we have $ 0 \rightarrow 1 \rightarrow 3 \rightarrow 5 \rightarrow 7 $ . Since we did not encounter a crocodile and swam no more than k meters, the answer is «YES».
- Second example: $ 0 \rightarrow 1 $ , we jump into the water from the first log ( $ 1 \rightarrow 2 $ ), swim a cell to the log ( $ 2 \leadsto 3 $ ), $ 3 \rightarrow 4 \rightarrow 5 \rightarrow 6 \rightarrow 7 $ . Since we did not encounter a crocodile and swam no more than k meters, the answer is «YES».
- In the third example, ErnKor needs to swim two cells 'W', but can only swim one. Therefore, the answer is «NO».
- Sixth example: We jump from the shore into the water ( $ 0 \rightarrow 6 $ ) and swim one cell in the water ( $ 6 \leadsto 7 $ ). Since we did not encounter a crocodile and swam no more than k meters, the answer is «YES».

## 样例 #1

### 输入

```
6
6 2 0
LWLLLW
6 1 1
LWLLLL
6 1 1
LWLLWL
6 2 15
LWLLCC
6 10 0
CCCCCC
6 6 1
WCCCCW```

### 输出

```
YES
YES
NO
NO
YES
YES```

# AI分析结果

### 题目内容重写

#### 题目描述

ErnKor 愿意为 Julen 做任何事情，甚至愿意游过满是鳄鱼的沼泽。我们决定测试这份爱。ErnKor 需要游过一条宽度为 $1$ 米、长度为 $n$ 米的河流。

河水非常冷。因此，在整个游泳过程中（即从 $0$ 到 $n+1$ 米），ErnKor 在水中游泳的总距离不能超过 $k$ 米。出于人道考虑，我们不仅在河中放置了鳄鱼，还放置了一些木头，供他跳跃。我们的测试如下：

最初，ErnKor 在左岸，需要到达右岸。它们分别位于 $0$ 和 $n+1$ 米处。河流可以表示为 $n$ 个长度为 $1$ 米的段。每个段包含木头 'L'、鳄鱼 'C' 或水 'W'。ErnKor 可以按以下方式移动：

- 如果他在表面上（即在岸上或木头上），他可以向前跳跃最多 $m$ 米（$1 \le m \le 10$）（他可以跳到岸上、木头上或水中）。
- 如果他在水中，他只能游到下一个河段（或者如果他位于第 $n$ 米处，则游到岸上）。
- ErnKor 不能以任何方式降落在鳄鱼所在的段。

判断 ErnKor 是否能到达右岸。

#### 说明/提示

考虑以下示例：

- 第一个示例：我们从岸上跳到第一个木头（$0 \rightarrow 1$），从第一个木头跳到第二个（$1 \rightarrow 3$），从第二个跳到第四个（$3 \rightarrow 5$），从最后一个木头跳到岸上（$5 \rightarrow 7$）。因此，路径为 $0 \rightarrow 1 \rightarrow 3 \rightarrow 5 \rightarrow 7$。由于没有遇到鳄鱼且游泳距离不超过 $k$ 米，答案为 «YES»。
- 第二个示例：$0 \rightarrow 1$，我们从第一个木头跳入水中（$1 \rightarrow 2$），游到木头（$2 \leadsto 3$），$3 \rightarrow 4 \rightarrow 5 \rightarrow 6 \rightarrow 7$。由于没有遇到鳄鱼且游泳距离不超过 $k$ 米，答案为 «YES»。
- 第三个示例：ErnKor 需要游过两个 'W' 段，但只能游一个。因此，答案为 «NO»。
- 第六个示例：我们从岸上跳入水中（$0 \rightarrow 6$），在水中游一个段（$6 \leadsto 7$）。由于没有遇到鳄鱼且游泳距离不超过 $k$ 米，答案为 «YES»。

#### 样例 #1

##### 输入

```
6
6 2 0
LWLLLW
6 1 1
LWLLLL
6 1 1
LWLLWL
6 2 15
LWLLCC
6 10 0
CCCCCC
6 6 1
WCCCCW
```

##### 输出

```
YES
YES
NO
NO
YES
YES
```

### 题解分析与结论

本题的核心是通过动态规划或贪心算法模拟 ErnKor 的移动过程，判断其是否能到达右岸且游泳距离不超过 $k$ 米。题解中主要采用了以下几种思路：

1. **动态规划**：通过状态转移方程记录每个位置的最小游泳距离或最大剩余游泳距离，判断是否能够到达终点。
2. **贪心算法**：每次选择最优的跳跃或游泳策略，尽可能减少游泳距离。
3. **最短路算法**：将问题转化为图的最短路问题，通过 Dijkstra 算法求解。

### 精选题解

#### 题解1：Garry_HJR (★★★★★)

**关键亮点**：
- 使用动态规划，状态转移清晰，边界处理得当。
- 通过 `rem[i]` 记录每个位置的最大剩余游泳距离，避免了复杂的边界判断。
- 代码简洁，逻辑清晰，易于理解。

**核心代码**：
```cpp
for(int i=1;i<=n+1;i++){
    rem[i]=-114514;
    if(ch[i]=='C'){
        rem[i]=-114514;
        continue;
    }
    int fr=max(0,i-m);
    for(int j=fr;j<i;j++){
        if(ch[j]=='L'){
            if(min(k,rem[j])>rem[i]){
                rem[i]=min(k,rem[j]);
            }
        }
    }
    if(ch[i-1]=='W'||i-1==0){
        if(rem[i-1]-1>rem[i]){
            rem[i]=rem[i-1]-1;
        }
    }
}
```

#### 题解2：Kindershiuo (★★★★☆)

**关键亮点**：
- 将问题转化为图的最短路问题，使用 Dijkstra 算法求解。
- 建图思路清晰，边权设置合理。
- 代码结构清晰，易于扩展。

**核心代码**：
```cpp
for(int i=0;i<=n+1;i++){
    if(s[i]=='L'){
        for(int j=1;j<=m;j++){
            if(s[i+j]=='W'){
                e[i].push_back({i+j,1});
            }
            else if(s[i+j]=='L'){
                e[i].push_back({i+j,0});
            }
        }
    }
}
```

#### 题解3：Pursuewind (★★★★☆)

**关键亮点**：
- 使用动态规划，状态转移方程简洁明了。
- 通过 `dp[i][0/1]` 记录每个位置的最小游泳距离，状态转移清晰。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
for(int i=1;i<=n+1;i++){
    if(s[i]=='C'){
        continue;
    }
    if(s[i]=='L'){
        dp[i][0]=min(dp[i-1][0],dp[i-1][1]);
    }
    else{
        dp[i][1]=min(dp[i-1][0],dp[i-1][1])+1;
    }
    for(int j=i-1;j>=max(0ll,i-m);j--){
        if(s[j]=='C'){
            continue;
        }
        if(s[i]=='W'){
            if(s[j]=='L'){
                dp[i][1]=min(dp[i][1],dp[j][0])+1;
            }
        }
        else{
            if(s[j]=='L'){
                dp[i][0]=min(dp[i][0],dp[j][0]);
            }
        }
    }
}
```

### 最优关键思路与技巧

- **动态规划**：通过记录每个位置的最大剩余游泳距离或最小游泳距离，判断是否能够到达终点。这种方法适用于状态转移清晰、边界条件明确的问题。
- **贪心算法**：每次选择最优的跳跃或游泳策略，尽可能减少游泳距离。这种方法适用于问题可以分解为局部最优解的情况。
- **最短路算法**：将问题转化为图的最短路问题，通过 Dijkstra 算法求解。这种方法适用于问题可以抽象为图的情况。

### 拓展思路

- **类似问题**：可以扩展到更复杂的移动规则，如跳跃距离可变、游泳距离可变等。
- **优化技巧**：可以通过单调队列优化动态规划的状态转移，减少时间复杂度。

### 推荐题目

1. [P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)
2. [P1359 租用游艇](https://www.luogu.com.cn/problem/P1359)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：53.53秒