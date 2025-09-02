# 题目信息

# Greg and Friends

## 题目描述

One day Greg and his friends were walking in the forest. Overall there were $ n $ people walking, including Greg. Soon he found himself in front of a river. The guys immediately decided to get across the river. Luckily, there was a boat by the river bank, just where the guys were standing. We know that the boat can hold people with the total weight of at most $ k $ kilograms.

Greg immediately took a piece of paper and listed there the weights of all people in his group (including himself). It turned out that each person weights either 50 or 100 kilograms. Now Greg wants to know what minimum number of times the boat needs to cross the river to transport the whole group to the other bank. The boat needs at least one person to navigate it from one bank to the other. As the boat crosses the river, it can have any non-zero number of passengers as long as their total weight doesn't exceed $ k $ .

Also Greg is wondering, how many ways there are to transport everybody to the other side in the minimum number of boat rides. Two ways are considered distinct if during some ride they have distinct sets of people on the boat.

Help Greg with this problem.

## 说明/提示

In the first test Greg walks alone and consequently, he needs only one ride across the river.

In the second test you should follow the plan:

1. transport two $ 50 $ kg. people;
2. transport one $ 50 $ kg. person back;
3. transport one $ 100 $ kg. person;
4. transport one $ 50 $ kg. person back;
5. transport two $ 50 $ kg. people.

That totals to $ 5 $ rides. Depending on which person to choose at step 2, we can get two distinct ways.

## 样例 #1

### 输入

```
1 50
50
```

### 输出

```
1
1
```

## 样例 #2

### 输入

```
3 100
50 50 100
```

### 输出

```
5
2
```

## 样例 #3

### 输入

```
2 50
50 50
```

### 输出

```
-1
0
```

# AI分析结果



### 题目翻译
# Greg和他的朋友们

## 题目描述

某天Greg和他的朋友在森林里散步，共有$n$个人（包括Greg）。他们遇到一条河流，发现一艘最大载重为$k$公斤的小船。已知每个人体重是50或100公斤，求将所有人运到对岸的最少渡河次数，及对应方案数（模$10^9+7$）。若无法完成输出`-1 0`。

## 说明/提示

样例2中需要5次渡河，具体步骤涉及来回运送50kg的人来支持100kg的人过河。当无法满足载重要求时（如样例3中两人各50kg但船载重仅50kg），判定无解。

---

### 题解分析与结论

#### 核心思路
所有题解均采用**状态转移+组合数计算**的核心方法：
1. **状态定义**：以两岸的50kg/100kg人数为状态维度
2. **转移方向**：通过奇偶性/船的位置区分去程与返程
3. **组合计算**：预处理组合数用于计算不同选择方式的方案数
4. **剪枝优化**：设定4n次操作上限判断无解

#### 最优题解推荐

##### 1. 作者：gesong（★★★★☆）
**关键亮点**：
- 通过奇偶性统一处理往返过程
- 状态定义简洁（过程次数+剩余人数）
- 代码结构清晰，组合数预处理优雅

**核心代码**：
```cpp
f[0][x][y] = 1;
for(int i=1; i<=4*n; i++)
    for(int j=0; j<=x; j++)
        for(int k=0; k<=y; k++){
            if(i&1){ // 去程
                for(int a=0; a<=x-j; a++)
                    for(int b=0; b<=y-k; b++)
                        if(50*a + 100*b <= k)
                            f[i][j][k] += f[i-1][j+a][k+b] * C[...];
                if(f[i][0][0]) return答案;
            }else{ // 返程
                for(int a=0; a<=j; a++)
                    for(int b=0; b<=k; b++)
                        if(50*a + 100*b <= k)
                            f[i][j][k] += f[i-1][j-a][k-b] * C[...];
            }
        }
```

##### 2. 作者：SevenDawns（★★★★☆）
**关键亮点**：
- BFS保证最短路径优先搜索
- 三维状态（出发岸人数+船的位置）设计巧妙
- 动态维护步数与方案数的同步更新

**核心思路**：
```cpp
struct State { int i,j,k; }; // i:50kg人数, j:100kg人数, k:船的位置
queue<State> q;
while(!q.empty()){
    auto [i,j,pos] = q.front();
    if(pos == 1){ // 出发岸
        for选a个50kg和b个100kg过河:
            新状态 = (i-a, j-b, 0)
            更新dp[新状态] += 原方案数 * C组合数
    }else{ // 对岸
        for送a个50kg和b个100kg返回:
            新状态 = (i+a, j+b, 1)
            更新dp[新状态]
    }
}
```

##### 3. 作者：zztqwq（★★★☆☆）
**亮点**：
- 船的位置显式建模
- 组合数通过阶乘逆元优化计算
- 状态转移方程数学表达清晰

---

### 关键技巧总结
1. **状态压缩**：将两岸人数与船的位置合并为状态，避免重复计算
2. **组合数预处理**：通过杨辉三角或阶乘逆元预先计算$C(n,m)$
3. **方向切换机制**：利用操作次数的奇偶性或船的位置切换转移方向
4. **动态规划剪枝**：设置最大操作次数4n（每人最多往返两次）

---

### 相似题目推荐
1. [P1514 引水入城](https://www.luogu.com.cn/problem/P1514)（状态转移+方案计数）
2. [P4011 孤岛营救问题](https://www.luogu.com.cn/problem/P4011)（多维状态BFS）
3. [P2761 软件补丁问题](https://www.luogu.com.cn/problem/P2761)（状态压缩+最短路）

---

### 调试心得摘录
1. **组合数处理**：多位作者提到忘记取模或错误计算组合数导致WA
2. **船必须载人**：有题解因漏判空船转移导致错误状态扩展
3. **数据类型**：封禁用户题解强调`long long`避免溢出
4. **方向判断**：gesong通过奇偶性简化代码，减少状态维度

---
处理用时：68.49秒