# 题目信息

# Getting Points

## 题目描述

Monocarp is a student at Berland State University. Due to recent changes in the Berland education system, Monocarp has to study only one subject — programming.

The academic term consists of $ n $ days, and in order not to get expelled, Monocarp has to earn at least $ P $ points during those $ n $ days. There are two ways to earn points — completing practical tasks and attending lessons. For each practical task Monocarp fulfills, he earns $ t $ points, and for each lesson he attends, he earns $ l $ points.

Practical tasks are unlocked "each week" as the term goes on: the first task is unlocked on day $ 1 $ (and can be completed on any day from $ 1 $ to $ n $ ), the second task is unlocked on day $ 8 $ (and can be completed on any day from $ 8 $ to $ n $ ), the third task is unlocked on day $ 15 $ , and so on.

Every day from $ 1 $ to $ n $ , there is a lesson which can be attended by Monocarp. And every day, Monocarp chooses whether to study or to rest the whole day. When Monocarp decides to study, he attends a lesson and can complete no more than $ 2 $  tasks, which are already unlocked and not completed yet. If Monocarp rests the whole day, he skips a lesson and ignores tasks.

Monocarp wants to have as many days off as possible, i. e. he wants to maximize the number of days he rests. Help him calculate the maximum number of days he can rest!

## 说明/提示

In the first test case, the term lasts for $ 1 $ day, so Monocarp should attend at day $ 1 $ . Since attending one lesson already gives $ 5 $ points ( $ 5 \ge P $ ), so it doesn't matter, will Monocarp complete the task or not.

In the second test case, Monocarp can, for example, study at days $ 8 $ and $ 9 $ : at day $ 8 $ he will attend a lesson for $ 10^9 $ points and complete two tasks for another $ 5 \cdot 10^8 + 5 \cdot 10^8 $ points. And at day $ 9 $ he only attends a lesson for another $ 10^9 $ points.

In the third test case, Monocarp can, for example, study at day $ 42 $ : attending a lesson gives him $ 1 $ point and solving $ 2 $ out of $ 6 $ available tasks gives him another $ 2 \cdot 10 $ points.

In the fourth test case, Monocarp has to attend all lessons and complete all tasks to get $ 8 \cdot 10 + 2 \cdot 20 = 120 $ points.

In the fifth test case, Monocarp can, for example, study at days: $ 8 $ — one lesson and first and second tasks; $ 15 $ — one lesson and the third task; $ 22 $ — one lesson and the fourth task; $ 29 $ — one lesson and the fifth task; $ 36 $ — one lesson and the sixth task.

## 样例 #1

### 输入

```
5
1 5 5 2
14 3000000000 1000000000 500000000
100 20 1 10
8 120 10 20
42 280 13 37```

### 输出

```
0
12
99
0
37```

# AI分析结果

### 题目翻译
# 获取积分

## 题目描述
Monocarp 是伯兰国立大学的一名学生。由于伯兰教育系统最近的改革，Monocarp 只需学习一门科目——编程。

学期共有 $n$ 天，为了不被开除，Monocarp 必须在这 $n$ 天内至少获得 $P$ 积分。获取积分有两种途径：完成实践任务和参加课程。Monocarp 每完成一项实践任务可获得 $t$ 积分，每参加一次课程可获得 $l$ 积分。

随着学期的推进，实践任务“每周”解锁一次：第一项任务在第 $1$ 天解锁（可在第 $1$ 天至第 $n$ 天的任意一天完成），第二项任务在第 $8$ 天解锁（可在第 $8$ 天至第 $n$ 天的任意一天完成），第三项任务在第 $15$ 天解锁，依此类推。

从第 $1$ 天到第 $n$ 天，每天都有一堂课可供 Monocarp 参加。每天，Monocarp 都要选择是学习一整天还是休息一整天。当 Monocarp 决定学习时，他会参加一堂课，并且最多可以完成 $2$ 项已经解锁但尚未完成的任务。如果 Monocarp 休息一整天，他就会逃课并忽略任务。

Monocarp 希望尽可能多地休息，即他希望最大化休息的天数。请帮助他计算他最多可以休息多少天！

## 说明/提示
在第一个测试用例中，学期持续 $1$ 天，因此 Monocarp 应该在第 $1$ 天参加课程。由于参加一次课程已经可以获得 $5$ 积分（$5 \ge P$），所以 Monocarp 是否完成任务并不重要。

在第二个测试用例中，Monocarp 可以在第 $8$ 天和第 $9$ 天学习：在第 $8$ 天，他将参加课程获得 $10^9$ 积分，并完成两项任务，每项任务获得 $5 \cdot 10^8$ 积分。在第 $9$ 天，他只参加课程，又获得 $10^9$ 积分。

在第三个测试用例中，Monocarp 可以在第 $42$ 天学习：参加课程给他 $1$ 积分，完成 $6$ 项可用任务中的 $2$ 项，又给他 $2 \cdot 10$ 积分。

在第四个测试用例中，Monocarp 必须参加所有课程并完成所有任务，才能获得 $8 \cdot 10 + 2 \cdot 20 = 120$ 积分。

在第五个测试用例中，Monocarp 可以在以下日期学习：第 $8$ 天——参加一堂课并完成第一项和第二项任务；第 $15$ 天——参加一堂课并完成第三项任务；第 $22$ 天——参加一堂课并完成第四项任务；第 $29$ 天——参加一堂课并完成第五项任务；第 $36$ 天——参加一堂课并完成第六项任务。

## 样例 #1
### 输入
```
5
1 5 5 2
14 3000000000 1000000000 500000000
100 20 1 10
8 120 10 20
42 280 13 37
```
### 输出
```
0
12
99
0
37
```

### 算法分类
二分

### 综合分析与结论
这些题解大多采用二分算法来解决问题，因为数据范围较大，$O(n)$ 的复杂度无法通过，而二分算法复杂度为 $O(\log n)$ 可以满足要求。思路上主要是二分休息天数或上课天数，然后通过 `check` 函数判断该天数是否能满足获得至少 $P$ 分的条件。

不同题解在实现细节上有所差异，如计算作业总数、判断得分是否满足条件等，但核心都是二分查找。部分题解还提到了贪心思想，即尽量让每天的收益最大化（上一节课做两份作业）。

### 高星题解
- **作者：ATION001 (4星)**
  - 关键亮点：思路清晰，明确指出使用二分算法的原因，代码简洁，有详细注释，提醒了 `long long` 的使用。
  - 个人心得：“十年 OI 一场空，不开 long long 见祖宗”，强调了数据范围大时使用 `long long` 的重要性。
- **作者：Francium_ (4星)**
  - 关键亮点：思路清晰，对二分过程和 `check` 函数的解释详细，代码结构清晰，有加速输入输出的处理。
  - 个人心得：“不开 long long 见祖宗，别问我怎么知道的”，同样强调了 `long long` 的重要性。
- **作者：WAis_WonderfulAnswer (4星)**
  - 关键亮点：思路详细，对二分和 `check` 函数的实现解释清楚，代码规范，有详细注释。
  - 个人心得：无

### 重点代码
#### 作者：ATION001
```cpp
bool code(int x){
    int ans;
    int k=n/7+(n%7!=0);
    if(x*2<=k){
        ans=(l_1+2*t)*x;
    }else{
        ans=(l_1*x+t*k);
    }
    return ans>=m;
}
```
核心思想：根据学习天数 $x$ 计算总得分，判断是否满足要求。先计算作业总数 $k$，若 $x$ 天内可完成的作业数不超过 $k$，则总得分是 $(l_1 + 2*t) * x$；否则，总得分是 $l_1 * x + t * k$。

#### 作者：Francium_
```cpp
bool check(int mid) {
    int cl = (n - mid), x = ceil(n * 1.0 / 7);
    int p1 = cl * l, p2 = min(cl * 2, x) * t;
    return p1 + p2 >= p;
}
```
核心思想：根据休息天数 $mid$ 计算学习天数 $cl$ 和作业总数 $x$，分别计算上课得分 $p1$ 和作业得分 $p2$，判断总得分是否满足要求。作业得分取 $cl * 2$ 和 $x$ 的最小值乘以 $t$，防止作业数不足。

#### 作者：WAis_WonderfulAnswer
```cpp
bool check(int x)
{
    int rk=(n%7==0?n/7:n/7+1);
    return t*min(rk,2*x)+x*l>=p;
}
```
核心思想：根据上课天数 $x$ 计算作业总数 $rk$，分别计算作业得分和上课得分，判断总得分是否满足要求。作业得分取 $rk$ 和 $2 * x$ 的最小值乘以 $t$。

### 关键思路或技巧
- **二分算法**：由于数据范围大，使用二分算法将时间复杂度从 $O(n)$ 降低到 $O(\log n)$。
- **贪心思想**：尽量让每天的收益最大化，即上一节课做两份作业。
- **`long long` 的使用**：由于数据范围达到 $10^{18}$，使用 `long long` 避免溢出。

### 拓展思路
同类型题或类似算法套路：
- 二分查找在其他最值问题中的应用，如在一定条件下求最大或最小的某个值。
- 结合贪心思想的二分问题，通过贪心策略优化二分的判断条件。

### 推荐洛谷题目
- P2678 [NOIP2015 提高组] 跳石头
- P1873 [COCI 2011/2012 #5] EKO / 砍树
- P3853 [TJOI2007] 路标设置

---
处理用时：46.09秒