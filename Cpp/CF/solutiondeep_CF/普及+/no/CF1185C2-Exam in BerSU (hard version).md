# 题目信息

# Exam in BerSU (hard version)

## 题目描述

The only difference between easy and hard versions is constraints.

If you write a solution in Python, then prefer to send it in PyPy to speed up execution time.

A session has begun at Beland State University. Many students are taking exams.

Polygraph Poligrafovich is going to examine a group of $ n $ students. Students will take the exam one-by-one in order from $ 1 $ -th to $ n $ -th. Rules of the exam are following:

- The $ i $ -th student randomly chooses a ticket.
- if this ticket is too hard to the student, he doesn't answer and goes home immediately (this process is so fast that it's considered no time elapses). This student fails the exam.
- if the student finds the ticket easy, he spends exactly $ t_i $ minutes to pass the exam. After it, he immediately gets a mark and goes home.

Students take the exam in the fixed order, one-by-one, without any interruption. At any moment of time, Polygraph Poligrafovich takes the answer from one student.

The duration of the whole exam for all students is $ M $ minutes ( $ \max t_i \le M $ ), so students at the end of the list have a greater possibility to run out of time to pass the exam.

For each student $ i $ , you should count the minimum possible number of students who need to fail the exam so the $ i $ -th student has enough time to pass the exam.

For each student $ i $ , find the answer independently. That is, if when finding the answer for the student $ i_1 $ some student $ j $ should leave, then while finding the answer for $ i_2 $ ( $ i_2>i_1 $ ) the student $ j $ student does not have to go home.

## 说明/提示

The explanation for the example 1.

Please note that the sum of the first five exam times does not exceed $ M=15 $ (the sum is $ 1+2+3+4+5=15 $ ). Thus, the first five students can pass the exam even if all the students before them also pass the exam. In other words, the first five numbers in the answer are $ 0 $ .

In order for the $ 6 $ -th student to pass the exam, it is necessary that at least $ 2 $ students must fail it before (for example, the $ 3 $ -rd and $ 4 $ -th, then the $ 6 $ -th will finish its exam in $ 1+2+5+6=14 $ minutes, which does not exceed $ M $ ).

In order for the $ 7 $ -th student to pass the exam, it is necessary that at least $ 3 $ students must fail it before (for example, the $ 2 $ -nd, $ 5 $ -th and $ 6 $ -th, then the $ 7 $ -th will finish its exam in $ 1+3+4+7=15 $ minutes, which does not exceed $ M $ ).

## 样例 #1

### 输入

```
7 15
1 2 3 4 5 6 7
```

### 输出

```
0 0 0 0 0 2 3 ```

## 样例 #2

### 输入

```
5 100
80 40 40 40 60
```

### 输出

```
0 1 1 2 3 ```

# AI分析结果

### 题目中文重写
# BerSU 考试（困难版本）

## 题目描述
简单版本和困难版本的唯一区别在于约束条件。

如果你用 Python 编写解决方案，建议使用 PyPy 提交以加快执行时间。

伯兰国立大学的一个学期开始了，许多学生正在参加考试。

波利格拉夫·波利格拉福维奇（Polygraph Poligrafovich）将考查一组 $n$ 名学生。学生们将按照从第 $1$ 名到第 $n$ 名的顺序依次参加考试。考试规则如下：
- 第 $i$ 名学生随机抽取一张试卷。
- 如果这张试卷对该学生来说太难，他将不回答并立即回家（这个过程非常快，可认为不消耗时间）。该学生考试不及格。
- 如果学生觉得试卷容易，他将恰好花费 $t_i$ 分钟通过考试。之后，他将立即获得成绩并回家。

学生们按固定顺序依次参加考试，中间没有任何中断。在任何时刻，波利格拉夫·波利格拉福维奇只接收一名学生的答案。

所有学生的考试总时长为 $M$ 分钟（$\max t_i \le M$），因此排在后面的学生更有可能没有足够的时间通过考试。

对于每个学生 $i$，你应该计算出最少需要有多少名学生考试不及格，才能让第 $i$ 名学生有足够的时间通过考试。

对于每个学生 $i$，应独立计算答案。也就是说，如果在为学生 $i_1$ 计算答案时，某些学生 $j$ 需要离开，那么在为 $i_2$（$i_2 > i_1$）计算答案时，学生 $j$ 不一定需要回家。

## 说明/提示
示例 1 的解释：

请注意，前 5 名学生的考试时间总和不超过 $M = 15$（总和为 $1 + 2 + 3 + 4 + 5 = 15$）。因此，即使前面的所有学生都通过了考试，前 5 名学生也可以通过考试。换句话说，答案中的前 5 个数字是 $0$。

为了让第 6 名学生通过考试，至少需要有 2 名学生在他之前考试不及格（例如，第 3 名和第 4 名学生，那么第 6 名学生将在 $1 + 2 + 5 + 6 = 14$ 分钟内完成考试，不超过 $M$）。

为了让第 7 名学生通过考试，至少需要有 3 名学生在他之前考试不及格（例如，第 2 名、第 5 名和第 6 名学生，那么第 7 名学生将在 $1 + 3 + 4 + 7 = 15$ 分钟内完成考试，不超过 $M$）。

## 样例 #1
### 输入
```
7 15
1 2 3 4 5 6 7
```
### 输出
```
0 0 0 0 0 2 3
```

## 样例 #2
### 输入
```
5 100
80 40 40 40 60
```
### 输出
```
0 1 1 2 3
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，要让第 $i$ 个学生能通过考试，就需要尽量删除前面用时较长的学生。不同题解在实现方式上有所不同，主要区别在于数据结构的选择和优化方法。

|作者|思路|算法要点|解决难点|评分|
|---|---|---|---|---|
|songhn|利用贪心思想，结合桶排优化删除最大值的过程|桶排统计每个用时的学生数量，从大到小枚举删除|数据范围大，直接扫描序列复杂度高|4星|
|lzyqwq|使用权值线段树二分，动态开点处理值域大的问题|权值线段树二分查找满足条件的最小数|值域大，需要高效的数据结构支持查找和插入|4星|
|_edge_|用两个 set 模拟删除和交换的过程|通过两个 set 交换元素，保证留下的时间较多|分析交换次数的复杂度|3星|
|Cesare|可撤销的贪心，记录当前加入元素对后续答案的影响|比较当前元素与堆中弹出元素的关系，决定是否回退操作|普通贪心可能忽略当前元素对后续答案的影响|3星|
|Special_Tony|使用大根堆和小根堆，回滚操作弥补漏洞|小根堆存储已弹出的数，根据情况回滚操作|普通大根堆做法可能导致后续答案错误|3星|
|linakrbcs|权值树状数组 + 倍增，先离散化处理较大值域|权值树状数组维护元素个数和元素和，倍增查找前缀和不超过某个值的最大位置|值域大，需要离散化，且要保证离散化后的值不同|3星|

### 所选题解
- songhn（4星）
  - 关键亮点：利用桶排的思想，结合数据范围中 $t$ 较小的特点，将时间复杂度优化到 $O(t\cdot n)$，代码实现简洁明了。
- lzyqwq（4星）
  - 关键亮点：使用权值线段树二分，动态开点处理值域大的问题，时间和空间复杂度均为 $\mathcal{O}(n\log m)$，是一种高效的数据结构应用。

### 重点代码
#### songhn
```cpp
for(int i=1;i<=n;i++)
{
    if(sum[i]<=m) printf("0 ");
    else
    {
        int temp=sum[i-1]-m+a[i];
        int res=0;
        for(int j=100;j>=1;j--)
        {
            int t=min(mp[j],(temp+j-1)/j);
            temp-=t*j;
            res+=t;
            if(temp<=0) break;
        }
        printf("%d ",res);
    }
    mp[a[i]]++;
}
```
核心实现思想：先计算前缀和，对于每个学生 $i$，如果前缀和不超过 $m$ 则答案为 $0$，否则计算需要删除的时间总和 $temp$，从大到小枚举桶中的元素，贪心删除最大的元素，直到 $temp$ 小于等于 $0$。

#### lzyqwq
```cpp
struct SegmentTree {
    int rt, sum[N * 30], tot[N * 30], cnt, ls[N * 30], rs[N * 30];
    void init() {
        memset(sum, 0, sizeof sum), memset(tot, 0, sizeof tot);
        memset(ls, cnt = rt = 0, sizeof ls), memset(rs, 0, sizeof rs);
    }
    SegmentTree() { init(); }
    void modify(int &x, int l, int r, int val) {
        if (!x) x = ++cnt;
        ++tot[x], sum[x] += val; if (l == r) return;
        int mid = (l + r) >> 1;
        if (val <= mid) modify(ls[x], l, mid, val);
        else modify(rs[x], mid + 1, r, val);
    }
    int query(int x, int l, int r, int k) {
        if (l == r) return (k + l - 1) / l;
        int mid = (l + r) >> 1, val = sum[rs[x]];
        if (k <= val) return query(rs[x], mid + 1, r, k);
        return query(ls[x], l, mid, k - val) + tot[rs[x]];
    }
} sgt;
```
核心实现思想：定义权值线段树结构体，`modify` 函数用于插入元素，`query` 函数用于二分查找满足条件的最小数，根据右儿子的和是否够来决定在右儿子还是左儿子中继续查找。

### 最优关键思路或技巧
- 利用数据范围的特点，如 $t$ 较小使用桶排，值域大使用动态开点的权值线段树。
- 贪心策略，优先删除用时较长的学生。

### 拓展思路
同类型题可能会改变数据范围、增加其他约束条件或改变问题形式，但核心贪心思想不变。类似算法套路包括使用不同的数据结构优化贪心过程，如堆、线段树、树状数组等。

### 推荐题目
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考查贪心和堆的应用。
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：简单的贪心问题。
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：经典的贪心问题，涉及物品的选择。

### 个人心得
- Special_Tony：使用大根堆的原始做法会 WA，原因是题目规定 $a_i$ 自身不能弹掉，导致先前弹掉的数在后面不一定也要弹，可能出现之前弹掉的数比 $a_i$ 还小的情况。解决方法是使用小根堆存储已弹出的数，根据情况回滚操作。 

---
处理用时：61.73秒