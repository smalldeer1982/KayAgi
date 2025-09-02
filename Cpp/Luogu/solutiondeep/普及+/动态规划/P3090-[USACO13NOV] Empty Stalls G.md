# 题目信息

# [USACO13NOV] Empty Stalls G

## 题目描述

Farmer John's new barn consists of a huge circle of N stalls (2 <= N <= 3,000,000), numbered 0..N-1, with stall N-1 being adjacent to stall 0.

At the end of each day, FJ's cows arrive back at the barn one by one, each with a preferred stall they would like to occupy.  However, if a cow's preferred stall is already occupied by another cow, she scans forward sequentially from this stall until she finds the first unoccupied stall, which she then claims.  If she scans past stall N-1, she continues scanning from stall 0.

Given the preferred stall of each cow, please determine the smallest index of a stall that remains unoccupied after all the cows have returned to the barn.  Notice that the answer to this question does not depend on the order in which the cows return to the barn.

In order to avoid issues with reading huge amounts of input, the input to this problem is specified in a concise format using K lines (1 <= K <= 10,000) each of the form:

X Y A B

One of these lines specifies the preferred stall for XY total cows: X cows prefer each of the stalls f(1) .. f(Y), where f(i) = (Ai + B) mod N.  The values of A and B lie in the range 0...1,000,000,000.

Do not forget the standard memory limit of 64MB for all problems.

约翰的谷仓中有N(2 <= N <=3,000,000)个房间，编号0到N-1，这些房间排布成环状,编号0的和编号N-1的相邻。

每天傍晚，奶牛们一只一只排队回到谷仓，每头奶牛都有一个喜欢的房间，但是，如果它喜欢的房间已被其他奶牛占了，它会向前挨个探索其他房间（如果它探索过了N-1号房间，它会继续探索0号房间，以此继续下去）直到探到第一个没有被占用的房间，这时它会宣布占用这个房间。

告诉你每头奶牛喜欢的房间，当所有奶牛都找到房间后，剩下的没被占用的房间中，编号最小的是哪个。很明显，问题的答案与奶牛进入谷仓的顺序无关。


为避免输入内容过多。本题的输入数据采用一种简洁的方式：一共K(1 <= K <=10,000)行，每行格式如下：

X Y A B

表示有Y批奶牛，每批X头，也就是总共X\*Y只奶牛喜欢的房间号。Y批奶牛编号1到Y，第i批X头奶牛喜欢的房间号为(A\*i+B) Mod N.

A和B的取值范围为0...1,000,000,000

注意，只有64M的空间。


## 说明/提示

There are 10 stalls in the barn, numbered 0..9.  The second line of input states that 3 cows prefer stall (2\*1+4) mod 10 = 6, and 3 cows prefer stall (2\*2+4) mod 10 = 8.  The third line states that 2 cows prefer stall (0\*1+1) mod 10 = 1.  Line four specifies that 1 cow prefers stall (1\*1+7) mod 10 = 8 (so a total of 4 cows prefer this stall).


All stalls will end up occupied except stall 5. 



## 样例 #1

### 输入

```
10 3 
3 2 2 4 
2 1 0 1 
1 1 1 7 
```

### 输出

```
5 
```

# AI分析结果



### 综合分析与结论
本题核心在于高效模拟环形房间分配过程，关键挑战是处理大规模输入（N≤3e6）与空间限制（64MB）。各题解主要采用两种思路：  
1. **溢出传递法**：预处理所有牛的偏好，将超量牛传递到后续位置，处理两次循环解决环状溢出  
2. **并查集优化**：动态维护每个位置的可用后继，实现O(α(N))的跳跃查询  

### 高星题解推荐

#### 1. 作者：小手冰凉（⭐⭐⭐⭐⭐）
**核心亮点**：  
- 两阶段处理：首次遍历处理常规溢出，二次处理尾部到首部的溢出  
- 代码简洁高效，仅用O(N)空间，完美符合空间限制  
- 巧妙利用模运算处理环形结构  

**关键代码**：
```cpp
for(int i=0;i<n;i++){
    if(ans[i]>0)ans[(i+1)%n]+=ans[i]-1,ans[i]=1;
}
while(ans[0]>1) // 二次处理首尾相连的溢出
```

#### 2. 作者：不便透露（⭐⭐⭐⭐）
**核心亮点**：  
- 并查集实现动态路径压缩，find(k+1)直接跳转到可用位置  
- 处理批量插入时的优化：x头牛只需连接x次  
- 时间复杂度稳定在O(KYxα(N))，适合极端数据  

**代码片段**：
```cpp
int find(int a){
    return fa[a]==a ? a : fa[a]=find(fa[a]);
}
// 批量处理x头牛
k = find((a*j+b)%n);
for(int t=1;t<=x;t++){
    z[k]=1;
    fa[k] = find(k+1);
    k = fa[k];
}
```

#### 3. 作者：yydfj（⭐⭐⭐⭐）
**亮点**：  
- 双次处理策略清晰，通过两次work()解决环状溢出  
- 输入处理时直接取模优化  
- 代码极简，仅20余行实现核心逻辑  

**实现思想**：
```cpp
void work() {
    for(int i=0;i<n;i++)
        if(room[i]>1) {
            room[(i+1)%n] += room[i]-1;
            room[i] = 1;
        }
}
// 主函数中调用两次
work(); work();
```

### 最优思路总结
**溢出传递法**为最优实践：  
1. 预处理所有偏好位置的初始牛数  
2. 线性扫描处理溢出，将超量牛传递至i+1位置  
3. 二次处理解决尾部→头部的溢出  
4. 最后遍历寻找首个空位  

**关键优化点**：  
- 利用模运算处理环形结构  
- 最多两次遍历即可稳定分配，时间复杂度O(N)  
- 仅需单个数组存储，空间复杂度O(N)  

### 相似题目推荐
1. [P3405 白雪皑皑](https://www.luogu.com.cn/problem/P3405) - 并查集维护区间染色  
2. [P2894 酒店](https://www.luogu.com.cn/problem/P2894) - 线段树维护最长连续空房  
3. [P1197 星球大战](https://www.luogu.com.cn/problem/P1197) - 逆向并查集维护连通性  

### 调试经验摘录
"在并查集实现中，必须注意`fa[k] = find(k+1)`的顺序，若先更新fa[k]会导致后续查找错误" —— 不便透露  
"两次work()调用是关键，第一次处理常规溢出，第二次处理尾部到首部的特殊情况" —— yydfj

---
处理用时：43.07秒