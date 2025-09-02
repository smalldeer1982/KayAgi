# 题目信息

# Petya's Exams

## 题目描述

Petya studies at university. The current academic year finishes with $ n $ special days. Petya needs to pass $ m $ exams in those special days. The special days in this problem are numbered from $ 1 $ to $ n $ .

There are three values about each exam:

- $ s_i $ — the day, when questions for the $ i $ -th exam will be published,
- $ d_i $ — the day of the $ i $ -th exam ( $ s_i < d_i $ ),
- $ c_i $ — number of days Petya needs to prepare for the $ i $ -th exam. For the $ i $ -th exam Petya should prepare in days between $ s_i $ and $ d_i-1 $ , inclusive.

There are three types of activities for Petya in each day: to spend a day doing nothing (taking a rest), to spend a day passing exactly one exam or to spend a day preparing for exactly one exam. So he can't pass/prepare for multiple exams in a day. He can't mix his activities in a day. If he is preparing for the $ i $ -th exam in day $ j $ , then $ s_i \le j < d_i $ .

It is allowed to have breaks in a preparation to an exam and to alternate preparations for different exams in consecutive days. So preparation for an exam is not required to be done in consecutive days.

Find the schedule for Petya to prepare for all exams and pass them, or report that it is impossible.

## 说明/提示

In the first example Petya can, for example, prepare for exam $ 1 $ in the first day, prepare for exam $ 2 $ in the second day, pass exam $ 1 $ in the third day, relax in the fourth day, and pass exam $ 2 $ in the fifth day. So, he can prepare and pass all exams.

In the second example, there are three days and two exams. So, Petya can prepare in only one day (because in two other days he should pass exams). Then Petya can not prepare and pass all exams.

## 样例 #1

### 输入

```
5 2
1 3 1
1 5 1
```

### 输出

```
1 2 3 0 3 
```

## 样例 #2

### 输入

```
3 2
1 3 1
1 2 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
10 3
4 7 2
1 10 3
8 9 1
```

### 输出

```
2 2 2 1 1 0 4 3 4 4 
```

# AI分析结果

### 题目中文重写
# Petya的考试

## 题目描述
Petya在大学学习。当前学年以 $ n $ 个特殊的日子结束。Petya需要在这些特殊的日子里通过 $ m $ 门考试。本题中特殊的日子从 $ 1 $ 到 $ n $ 编号。

关于每门考试有三个值：
- $ s_i $ —— 第 $ i $ 门考试的题目公布的日子。
- $ d_i $ —— 第 $ i $ 门考试的日期（$ s_i < d_i $）。
- $ c_i $ —— Petya准备第 $ i $ 门考试需要的天数。对于第 $ i $ 门考试，Petya应该在 $ s_i $ 到 $ d_i - 1 $ （包含两端）的日子里进行准备。

Petya在每一天有三种活动类型：花一天时间什么都不做（休息）、花一天时间通过恰好一门考试或者花一天时间准备恰好一门考试。所以他不能在一天内通过/准备多门考试。他不能在一天内混合他的活动。如果他在第 $ j $ 天准备第 $ i $ 门考试，那么 $ s_i \leq j < d_i $。

允许在准备一门考试时有休息时间，并且允许在连续的日子里交替准备不同的考试。所以准备一门考试不需要在连续的日子里完成。

为Petya找到一个准备所有考试并通过它们的日程安排，或者报告这是不可能的。

## 说明/提示
在第一个样例中，例如，Petya可以在第一天准备考试1，在第二天准备考试2，在第三天通过考试1，在第四天休息，在第五天通过考试2。所以，他可以准备并通过所有考试。

在第二个样例中，有三天和两门考试。所以，Petya只能在一天内准备（因为在另外两天他应该通过考试）。那么Petya不能准备并通过所有考试。

## 样例 #1
### 输入
```
5 2
1 3 1
1 5 1
```
### 输出
```
1 2 3 0 3 
```

## 样例 #2
### 输入
```
3 2
1 3 1
1 2 1
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
10 3
4 7 2
1 10 3
8 9 1
```
### 输出
```
2 2 2 1 1 0 4 3 4 4 
```

### 综合分析与结论
- **思路对比**：大部分题解都采用贪心策略，核心思路是优先安排考试时间更早的考试进行复习。如“风中の菜鸡”“fls233666”“kimidonatsu”等题解直接按考试时间 $d_i$ 排序；“玉环小姐姐”采用多关键字排序，先按结束时间，再按题目发布时间，最后按复习时间；“atarashiTLE”则按 $d_i$、$d_i - s_i$、$c_i$ 依次排序；“codeLJH114514”不用排序，考虑每天复习距离开考最近的考试，用 `set` 维护。
- **算法要点**：
    - 定义结构体存储每场考试的公布时间、考试时间、复习时间等信息。
    - 对考试按一定规则排序。
    - 遍历排序后的考试，从公布时间到考试前一天安排复习，若无法安排足够天数则无解。
- **解决难点**：核心难点在于确定合理的贪心策略和排序规则，确保能安排出满足所有考试复习要求的日程。部分题解还需处理好数据结构的使用，如 `set` 的插入、删除和查找操作。

### 所选题解
- **作者：风中の菜鸡（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对每个步骤解释明确，适合初学者理解。
    - **个人心得**：做完本题后推荐练习 [P1230](https://www.luogu.com.cn/problem/P1230) 智力大冲浪，认为思路和难度都差不多。
    - **核心代码**：
```cpp
struct Exam{
    int promulgate,start,review,place; 
};
int cmp(Exam x,Exam y){
    return x.start<y.start;
}
//...
sort(exam+1,exam+m+1,cmp);
for(int i=1;i<=m;i++){
    num=0;
    for(int j=exam[i].promulgate;j<exam[i].start;j++){
        if(num==exam[i].review){
            break;
        } 
        if(jh[j]==-1){
            jh[j]=exam[i].place;
            num++;
        }
    }
    if(num<exam[i].review){
        cout<<"-1";
        return 0; 
    }
}
```
核心实现思想：先按考试时间对考试结构体数组排序，然后遍历每场考试，从公布时间到考试前一天，若当天无安排则安排复习，若无法安排足够天数则输出 `-1`。

- **作者：fls233666（4星）**
    - **关键亮点**：代码简洁，逻辑清晰，对贪心策略的阐述较为明确。
    - **核心代码**：
```cpp
struct exams{
    int si;
    int di;
    int ci;
    int id;
};
inline bool cmp(struct exams e1,struct exams e2){
    return e1.di<e2.di;
}
//...
sort(e+1,e+1+m,cmp);
for(rgt i=1;i<=m;i++){
    for(rgt j=e[i].si;j<e[i].di;j++){
        if(!plan[j]){
            plan[j]=e[i].id;
            e[i].ci--;
            if(!e[i].ci)
                break;
        }
    }
    if(e[i].ci){
        printf("-1");
        return 0;
    }
}
```
核心实现思想：按考试时间对考试结构体数组排序，遍历每场考试，从公布时间到考试前一天，若当天空闲则安排复习，若无法安排足够天数则输出 `-1`。

- **作者：kimidonatsu（4星）**
    - **关键亮点**：对贪心算法的原理有一定解释，代码模块化，结构清晰。
    - **核心代码**：
```cpp
struct node {
    int s, d, c, id;
};
inline bool cmp(const node x, const node y) {
    return x.d < y.d;
}
//...
stable_sort(exams + 1, exams + m + 1, cmp);
for (re int i = 1; i <= m; i++) {
    for (re int j = exams[i].s; j < exams[i].d; j++) {
        if (!ans[j]) {
            ans[j] = exams[i].id;
            exams[i].c--;
            if (!exams[i].c) break;
        }
    }
    if (exams[i].c) {
        printf("-1\n");
        exit(0);
    }
}
```
核心实现思想：按考试时间对考试结构体数组排序，遍历每场考试，从公布时间到考试前一天，若当天无安排则安排复习，若无法安排足够天数则输出 `-1`。

### 最优关键思路或技巧
- **贪心策略**：优先安排考试时间更早的考试进行复习，确保先处理紧急的任务。
- **结构体排序**：通过定义结构体存储考试信息，并自定义排序规则，方便对考试进行排序和处理。

### 同类型题或类似算法套路
此类题目属于贪心算法的应用，常见套路是根据题目条件确定贪心策略，对数据进行排序后按策略进行处理。同类型题可能涉及任务调度、区间覆盖等问题。

### 洛谷相似题目推荐
- [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)
- [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
- [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得总结
- “风中の菜鸡”做完本题后推荐练习 [P1230](https://www.luogu.com.cn/problem/P1230) 智力大冲浪，认为思路和难度都差不多，可通过练习巩固贪心算法的应用。
- “玉环小姐姐”提醒输出时两个数之间要加空格，避免因格式问题出错。 

---
处理用时：44.96秒