# 题目信息

# Superhero Battle

## 题目描述

A superhero fights with a monster. The battle consists of rounds, each of which lasts exactly $ n $ minutes. After a round ends, the next round starts immediately. This is repeated over and over again.

Each round has the same scenario. It is described by a sequence of $ n $ numbers: $ d_1, d_2, \dots, d_n $ ( $ -10^6 \le d_i \le 10^6 $ ). The $ i $ -th element means that monster's hp (hit points) changes by the value $ d_i $ during the $ i $ -th minute of each round. Formally, if before the $ i $ -th minute of a round the monster's hp is $ h $ , then after the $ i $ -th minute it changes to $ h := h + d_i $ .

The monster's initial hp is $ H $ . It means that before the battle the monster has $ H $ hit points. Print the first minute after which the monster dies. The monster dies if its hp is less than or equal to $ 0 $ . Print -1 if the battle continues infinitely.

## 样例 #1

### 输入

```
1000 6
-100 -200 -300 125 77 -4
```

### 输出

```
9
```

## 样例 #2

### 输入

```
1000000000000 5
-1 0 0 0 0
```

### 输出

```
4999999999996
```

## 样例 #3

### 输入

```
10 4
-3 -6 5 4
```

### 输出

```
-1
```

# AI分析结果

### 题目内容重写
**超级英雄战斗**

#### 题目描述
超级英雄与怪物进行战斗。战斗由若干轮组成，每轮持续恰好 $n$ 分钟。每轮结束后，下一轮立即开始。这个过程不断重复。

每轮的场景相同，由一个长度为 $n$ 的序列描述：$d_1, d_2, \dots, d_n$（$-10^6 \le d_i \le 10^6$）。第 $i$ 个元素表示每轮的第 $i$ 分钟，怪物的血量（HP）会变化 $d_i$。具体来说，如果在一轮的第 $i$ 分钟之前，怪物的血量为 $h$，那么在第 $i$ 分钟之后，血量变为 $h := h + d_i$。

怪物的初始血量为 $H$。输出怪物死亡的第一分钟。怪物死亡的条件是其血量小于或等于 $0$。如果战斗无限进行，输出 $-1$。

#### 样例 #1
##### 输入
```
1000 6
-100 -200 -300 125 77 -4
```
##### 输出
```
9
```

#### 样例 #2
##### 输入
```
1000000000000 5
-1 0 0 0 0
```
##### 输出
```
4999999999996
```

#### 样例 #3
##### 输入
```
10 4
-3 -6 5 4
```
##### 输出
```
-1
```

### 算法分类
**模拟**

### 题解分析与结论
题目要求计算怪物死亡的第一分钟，且每轮的伤害序列是固定的。由于每轮的伤害序列相同，我们可以通过模拟每一轮的伤害变化来判断怪物何时死亡。难点在于如何处理多轮的情况，特别是当每轮的总伤害为负数时，怪物最终会死亡，但需要计算具体的时间。

### 高星题解推荐
1. **作者：sea_bird (赞：3)**
   - **星级：4**
   - **关键亮点**：通过计算每轮的总伤害和最大伤害，判断怪物是否会在某一轮中死亡。代码逻辑清晰，处理了多种边界情况。
   - **核心代码**：
     ```cpp
     if(sum>=0){//当伤害不是负数时
         cout<<-1<<endl;
         return 0;
     }
     sum=abs(sum);//求绝对值
     l=(t+maxn)%sum;//排除最后一轮的情况 
     if(l>0){//就像样例#1
         ans=n*((t+maxn)/sum+1);//计算最后一轮之前的分钟数 
         t=t-((t+maxn)/sum+1)*sum;//更新t的值为不算最后一轮的情况 
     }
     else{//就像样例#2 
         ans=n*((t+maxn)/sum);
         t=t-((t+maxn)/sum)*sum;
     }
     for(int i=1;i<=n;i++){//再循环最后一轮的情况 
         t+=x[i];
         if(t<=0){
             ans+=i;
             break;//跳出循环
         }
     }
     ```
   - **个人心得**：作者提到在调试过程中发现了一些边界情况，如第一轮就死亡的情况，最终通过增加判断条件解决了问题。

2. **作者：Y_QWQ_Y (赞：2)**
   - **星级：4**
   - **关键亮点**：通过前缀和和最小值的计算，判断怪物是否会在某一轮中死亡。代码简洁，逻辑清晰。
   - **核心代码**：
     ```cpp
     if(sum[n]>=0){
         cout<<-1;
         return 0;
     }
     long long ans=1e18;
     for(int i=1;i<=n;i++){
         ans=min(ans,(m+sum[i]-sum[n]-1)/(-sum[n])*n+i);
     }
     cout<<ans;
     ```
   - **个人心得**：作者提到在调试过程中发现了一些特殊情况，如第一轮就死亡的情况，最终通过增加判断条件解决了问题。

3. **作者：da32s1da (赞：2)**
   - **星级：4**
   - **关键亮点**：通过计算每轮的总伤害和最大伤害，判断怪物是否会在某一轮中死亡。代码逻辑清晰，处理了多种边界情况。
   - **核心代码**：
     ```cpp
     if(x>=0){puts("-1");return 0;}//判掉
     x=-x;
     Ans=1ll*n*((H+y)/x+((H+y)%x>0));//把整的几轮加上
     H=H-1ll*((H+y)/x+((H+y)%x>0))*x;//剩下的血
     for(int i=1;i<=n;i++){
         H+=a[i];
         if(H<=0){printf("%I64d\n",Ans+i);return 0;}
     }
     ```
   - **个人心得**：作者提到在调试过程中发现了一些边界情况，如第一轮就死亡的情况，最终通过增加判断条件解决了问题。

### 最优关键思路或技巧
1. **前缀和与最小值计算**：通过计算每轮的前缀和和最小值，可以快速判断怪物是否会在某一轮中死亡。
2. **边界情况处理**：特别关注第一轮就死亡的情况，以及每轮总伤害为负数的情况。
3. **模拟与循环**：通过模拟每一轮的伤害变化，可以精确计算怪物死亡的时间。

### 可拓展之处
类似的问题可以扩展到其他周期性变化的场景，如资源消耗、时间管理等。可以通过前缀和和模拟的方法来解决这类问题。

### 推荐题目
1. [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)
2. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
3. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)

---
处理用时：40.89秒