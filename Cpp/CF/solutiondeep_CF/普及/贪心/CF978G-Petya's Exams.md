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

### 题目翻译

Petya在大学学习。当前学年有$n$个特殊的日子，Petya需要在这些日子里通过$m$场考试。这些特殊的日子从$1$到$n$编号。

每场考试有三个属性：
- $s_i$ —— 第$i$场考试的题目公布的日子，
- $d_i$ —— 第$i$场考试的考试日子（$s_i < d_i$），
- $c_i$ —— Petya需要为第$i$场考试准备的天数。Petya必须在$s_i$到$d_i-1$之间的日子里准备第$i$场考试。

Petya每天只能做以下三件事之一：休息、参加一场考试、为一场考试做准备。他不能在同一天参加或准备多场考试。如果他在第$j$天为第$i$场考试做准备，那么必须满足$s_i \le j < d_i$。

允许在准备考试的过程中有间断，并且可以在连续的日子里交替准备不同的考试。因此，准备考试的天数不需要是连续的。

请为Petya安排一个时间表，使他能够为所有考试做好准备并通过它们，或者报告这是不可能的。

### 样例 #1

#### 输入
```
5 2
1 3 1
1 5 1
```

#### 输出
```
1 2 3 0 3 
```

### 样例 #2

#### 输入
```
3 2
1 3 1
1 2 1
```

#### 输出
```
-1
```

### 样例 #3

#### 输入
```
10 3
4 7 2
1 10 3
8 9 1
```

#### 输出
```
2 2 2 1 1 0 4 3 4 4 
```

---

### 题解分析与结论

本题的核心是贪心算法，通过优先安排考试时间较早的考试，并尽可能早地安排复习时间，以确保所有考试都能得到充分的准备。以下是各题解的要点总结：

1. **贪心策略**：所有题解都采用了贪心策略，优先安排考试时间较早的考试，并尽可能早地安排复习时间。
2. **排序**：大多数题解都按照考试时间$d_i$进行排序，以确保先安排考试时间较早的考试。
3. **复习安排**：在安排复习时，从$s_i$到$d_i-1$的天数中，优先安排空闲的天数进行复习。
4. **无解判断**：如果在安排复习时无法满足$c_i$天的复习需求，则输出`-1`。

### 精选题解

#### 题解作者：fls233666 (★★★★☆)

**关键亮点**：
- 代码简洁明了，逻辑清晰。
- 使用结构体存储考试信息，便于排序和后续处理。
- 通过提前标记考试日，简化了后续的复习安排。

**核心代码**：
```cpp
struct exams{
    int si;
    int di;
    int ci;
    int id;
}e[111];

inline bool cmp(struct exams e1,struct exams e2){
    return e1.di<e2.di;
}

int main(){
    scanf("%d%d",&n,&m);
    for(rgt i=1;i<=m;i++){
        scanf("%d%d%d",&e[i].si,&e[i].di,&e[i].ci);
        e[i].id=i;
        plan[e[i].di]=m+1;
    }
    sort(e+1,e+1+m,cmp);
    for(rgt i=1;i<=m;i++){
        for(rgt j=e[i].si;j<e[i].di;j++){
            if(!plan[j]){
                plan[j]=e[i].id;
                e[i].ci--;
                if(!e[i].ci) break;
            }
        }
        if(e[i].ci){
            printf("-1");
            return 0;
        }
    }
    for(rgt i=1;i<=n;i++)
        printf("%d ",plan[i]);
    return 0;
}
```

#### 题解作者：kimidonatsu (★★★★☆)

**关键亮点**：
- 详细解释了贪心策略的合理性，并通过反证法证明了其正确性。
- 代码结构清晰，注释详细，便于理解。

**核心代码**：
```cpp
struct node {
    int s, d, c, id;
} exams[N];

inline bool cmp(const node x, const node y) {
    return x.d < y.d;
}

void work() {
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
}
```

#### 题解作者：atarashiTLE (★★★★☆)

**关键亮点**：
- 采用了多关键字排序，优先安排考试时间较早、复习时间较短、需要复习时间较长的考试。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码**：
```cpp
struct exam {
    int s, d, c, bh, cha;
} exams[110];

bool cmp(exam a, exam b) {
    if (a.d == b.d)
        if (a.cha == b.cha)
            return a.c > b.c;
        else
            return a.cha < b.cha;
    return a.d < b.d;
}

int main() {
    sort(exams + 1, exams + n + 1, cmp);
    for (int i = 1; i <= n; i++) {
        int tot = 0;
        for (int j = exams[i].s; j <= exams[i].d && tot < exams[i].c; j++)
            if (!ans[j]) {
                ans[j] = exams[i].bh;
                tot++;
            }
        if (tot < exams[i].c) {
            cout << -1 << endl;
            return 0;
        }
    }
    for (int i = 1; i <= m; i++)
        cout << ans[i] << ' ';
    return 0;
}
```

### 最优关键思路与技巧

1. **贪心策略**：优先安排考试时间较早的考试，并尽可能早地安排复习时间。
2. **排序**：按照考试时间$d_i$进行排序，确保先安排考试时间较早的考试。
3. **复习安排**：从$s_i$到$d_i-1$的天数中，优先安排空闲的天数进行复习。
4. **无解判断**：如果在安排复习时无法满足$c_i$天的复习需求，则输出`-1`。

### 拓展与推荐题目

1. **P1230 智力大冲浪**：与本题类似，考察贪心算法的应用。
2. **P1803 凌乱的yyy / 线段覆盖**：贪心算法的经典题目，考察区间调度问题。
3. **P1090 合并果子**：贪心算法的应用，考察最小代价的合并策略。

### 个人心得总结

- **调试经历**：在安排复习时，需要特别注意复习天数的计算，确保不会超出考试日。
- **踩坑教训**：在排序时，确保考试时间的顺序正确，避免因排序错误导致复习安排不合理。
- **顿悟感想**：贪心算法的关键在于每一步都选择当前最优的策略，通过局部最优达到全局最优。

---
处理用时：57.59秒