# 题目信息

# News About Credit

## 题目描述

Polycarp studies at the university in the group which consists of $ n $ students (including himself). All they are registrated in the social net "TheContacnt!".

Not all students are equally sociable. About each student you know the value $ a_{i} $ — the maximum number of messages which the $ i $ -th student is agree to send per day. The student can't send messages to himself.

In early morning Polycarp knew important news that the programming credit will be tomorrow. For this reason it is necessary to urgently inform all groupmates about this news using private messages.

Your task is to make a plan of using private messages, so that:

- the student $ i $ sends no more than $ a_{i} $ messages (for all $ i $ from $ 1 $ to $ n $ );
- all students knew the news about the credit (initially only Polycarp knew it);
- the student can inform the other student only if he knows it himself.

Let's consider that all students are numerated by distinct numbers from $ 1 $ to $ n $ , and Polycarp always has the number $ 1 $ .

In that task you shouldn't minimize the number of messages, the moment of time, when all knew about credit or some other parameters. Find any way how to use private messages which satisfies requirements above.

## 说明/提示

In the first test Polycarp (the student number $ 1 $ ) can send the message to the student number $ 2 $ , who after that can send the message to students number $ 3 $ and $ 4 $ . Thus, all students knew about the credit.

## 样例 #1

### 输入

```
4
1 2 1 0
```

### 输出

```
3
1 2
2 4
2 3
```

## 样例 #2

### 输入

```
6
2 0 1 3 2 0
```

### 输出

```
6
1 3
3 4
1 2
4 5
5 6
4 6
```

## 样例 #3

### 输入

```
3
0 2 2
```

### 输出

```
-1
```

# AI分析结果



【中文题目重写】

# 关于考试的通知

## 题目描述

Polycarp所在大学小组共有$n$名学生（包含他自己）。所有成员都在社交网络"TheContact!"注册。

每个学生的活跃度不同。已知第$i$个学生的$a_i$值，表示该学生每天最多能发送的消息数（不能给自己发消息）。

今晨Polycarp得知明天有编程考试，需通过私信通知所有组员。请制定消息传递方案，要求：

1. 第$i$个学生发送消息数不超过$a_i$
2. 所有学生最终获知消息（初始仅Polycarp知道）
3. 学生只有自己知情时才能发送消息

Polycarp编号始终为1。输出任意可行方案即可，无需优化消息总数或传递时间。

## 样例 #3

### 输入
```
3
0 2 2
```

### 输出
```
-1
```

---

**算法分类**：贪心

**题解分析与结论**  
各题解均采用贪心策略，核心思路是优先让消息容量大的节点传播消息。关键差异在于实现方式：
1. **动态排序法**：每次选择可用节点中$a_i$最大者（Yamchip方案），时间复杂度较高但正确
2. **双指针覆盖法**：预处理节点排序后线性扩展覆盖范围（Zhuluoan方案），时间复杂度最优
3. **轮换主力法**：消耗当前节点消息容量后切换新节点（glass_goldfish方案），实现简单但效率中等

**优质题解推荐**

1. **Zhuluoan（5星）**  
   关键亮点：预处理降序排列+双指针覆盖，O(n logn)时间复杂度  
   ```cpp
   sort(a+2,a+1+n,cmp);  // 除1号外按a_i降序排列
   int r=1;  // 当前覆盖右边界
   for(int i=1; i<=n && r<n; i++){
       if(r < i) return -1;  // 无法覆盖后续节点
       int extend = min(r + a[i].fi, n);
       for(int j=r+1; j<=extend; j++)
           ans.emplace_back(a[i].se, a[j].se);
       r = extend;
   }
   ```

2. **Yamchip（4星）**  
   关键亮点：实时排序确保最优选择，代码可读性佳  
   ```cpp
   while(未全部覆盖){
       for 所有已覆盖节点i 
           收集未覆盖节点信息
       sort(未覆盖节点按a_i降序)  // 关键排序
       while(当前节点还有消息额度)
           发送给排序后的前几个节点
   }
   ```

3. **glass_goldfish（4星）**  
   关键亮点：轮换发送主力的直观实现  
   ```cpp
   while(存在未通知者){
       k = 第一个有剩余消息的已通知节点
       while(k还有额度)
           按顺序通知未通知者
   }
   ```

**核心技巧总结**  
1. **贪心排序预处理**：将除消息源外的节点按消息容量降序排列，确保优先使用传播能力强的节点
2. **覆盖区间扩展法**：维护当前覆盖右边界，每个节点负责其能力范围内的连续区间
3. **无解条件判定**：总消息数不足n-1或源节点无发送能力时直接返回-1

**同类题目推荐**  
1. P1094 [NOIP2007 普及组] 纪念品分组（贪心+双指针）  
2. P4995 跳跳！（贪心+交替选择极值）  
3. P1230 智力大冲浪（贪心+截止时间排序）

**题解心得摘录**  
- Zhuluoan："预处理排序后，每个节点只需处理一次，类似哈夫曼编码的构造思想"  
- glass_goldfish："调试时发现必须优先耗尽当前节点的额度，否则会形成死循环"  
- Yamchip："虽然题目不要求最优解，但贪心排序能自然满足题目约束"

---
处理用时：63.51秒