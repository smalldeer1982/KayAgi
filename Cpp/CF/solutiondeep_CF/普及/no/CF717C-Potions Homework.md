# 题目信息

# Potions Homework

## 题目描述

Harry Water, Ronaldo, Her-my-oh-knee and their friends have started a new school year at their MDCS School of Speechcraft and Misery. At the time, they are very happy to have seen each other after a long time. The sun is shining, birds are singing, flowers are blooming, and their Potions class teacher, professor Snipe is sulky as usual. Due to his angst fueled by disappointment in his own life, he has given them a lot of homework in Potions class.

Each of the $ n $ students has been assigned a single task. Some students do certain tasks faster than others. Thus, they want to redistribute the tasks so that each student still does exactly one task, and that all tasks are finished. Each student has their own laziness level, and each task has its own difficulty level. Professor Snipe is trying hard to improve their work ethics, so each student’s laziness level is equal to their task’s difficulty level. Both sets of values are given by the sequence $ a $ , where $ a_{i} $ represents both the laziness level of the $ i $ -th student and the difficulty of his task.

The time a student needs to finish a task is equal to the product of their laziness level and the task’s difficulty. They are wondering, what is the minimum possible total time they must spend to finish all tasks if they distribute them in the optimal way. Each person should receive one task and each task should be given to one person. Print the answer modulo $ 10007 $ .

## 说明/提示

In the first sample, if the students switch their tasks, they will be able to finish them in $ 3+3=6 $ time units.

## 样例 #1

### 输入

```
2
1
3
```

### 输出

```
6
```

# AI分析结果



# Potions Homework

## 题目描述

Harry Water、Ronaldo、Her-my-oh-knee 和他们的朋友们在 MDCS 演讲与苦难学校开始了新学年。此时，他们非常开心能在长时间分别后重逢。阳光明媚，鸟儿歌唱，花儿绽放，而他们的魔药课老师斯内普教授依旧闷闷不乐。由于对自身生活的失望带来的焦虑，他给学生们布置了大量魔药课作业。

每个学生被分配一个任务。有些学生完成某些任务更快。他们希望重新分配任务，使得每个学生仍完成恰好一个任务，且所有任务都被完成。每个学生有懒惰值，每个任务有难度值。斯内普教授希望提升他们的职业道德，因此每个学生的懒惰值等于其任务的难度值。这两个值序列由数组 $a$ 给出，其中 $a_i$ 表示第 $i$ 个学生的懒惰值和其任务的难度值。

学生完成任务的时间等于其懒惰值与任务难度的乘积。求在最优分配下完成任务的最小总时间，结果对 $10007$ 取模。

## 标签
贪心

---

## 题解综合分析

所有题解均采用贪心策略，核心思路为排序后最大元素与最小元素配对。通过数学证明，这种配对方式能最小化总和。关键实现要点包括正确排序、头尾配对、及时取模。部分题解未使用 long long 但依赖模运算防止溢出，而显式使用 long long 更为稳健。

### 最优题解推荐

1. **Steve_xh（⭐⭐⭐⭐⭐）**  
   亮点：详细数学证明，显式使用 long long 避免溢出，循环变量双向移动  
   心得：强调"十年OI一场空，不开long long见祖宗"的调试经验  
   ```cpp
   sort(a+1,a+n+1);
   for(int i=1,j=n;i<=n;i++,j--)
       ans=(ans+(a[i]*a[j])%MOD)%MOD;
   ```

2. **Zq_water（⭐⭐⭐⭐）**  
   亮点：代码简洁，双向枚举思路清晰  
   ```cpp
   sort(a+1,a+n+1);
   for(long long i=1,j=n;i<=n;i++,j--)
       ans=(ans+(a[i]*a[j])%MOD)%MOD;
   ```

3. **Bpds1110（⭐⭐⭐⭐）**  
   亮点：通过代数比较证明贪心正确性，代码规范  
   ```cpp
   sort(a+1,a+1+n);
   for(i=1;i<=n;++i)
       ans=(ans+a[i]*a[n-i+1])%mod;
   ```

---

## 关键技巧总结
1. **贪心配对策略**：将排序后的数组头尾配对（最大×最小）以最小化乘积和  
2. **溢出处理**：每次乘法后立即取模，显式使用 long long 更安全  
3. **循环实现**：使用双向指针（i从首递增，j从尾递减）简化配对逻辑  

---

## 拓展思考
类似贪心问题常见于任务调度（如P1094 纪念品分组）、最优匹配（如P1223 排队接水）等场景。核心在于通过排序将极值合理配对。

---

## 推荐习题
1. P1223 排队接水（贪心+排序）  
2. P1094 纪念品分组（双指针贪心）  
3. P1012 拼数（字符串贪心排序）

---
处理用时：49.23秒