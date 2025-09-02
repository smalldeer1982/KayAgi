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
Petya在大学学习。当前学年以 $n$ 个特殊的日子结束。Petya需要在这些特殊的日子里通过 $m$ 门考试。本题中的特殊日子从 $1$ 到 $n$ 编号。

关于每门考试有三个值：
- $s_i$ —— 第 $i$ 门考试的题目公布的日子。
- $d_i$ —— 第 $i$ 门考试的日子（$s_i < d_i$）。
- $c_i$ —— Petya准备第 $i$ 门考试需要的天数。对于第 $i$ 门考试，Petya应该在 $s_i$ 到 $d_i - 1$（包含两端）的日子里进行准备。

Petya在每一天有三种活动类型：花一天时间什么都不做（休息）、花一天时间恰好通过一门考试或者花一天时间恰好准备一门考试。所以他不能在一天内通过/准备多门考试。他不能在一天内混合进行这些活动。如果他在第 $j$ 天准备第 $i$ 门考试，那么 $s_i \leq j < d_i$。

允许在准备一门考试时进行休息，并且允许在连续的日子里交替准备不同的考试。所以准备一门考试不需要在连续的日子里完成。

找出Petya准备并通过所有考试的日程安排，或者报告这是不可能的。

## 说明/提示
在第一个样例中，Petya可以，例如，在第一天准备考试1，在第二天准备考试2，在第三天通过考试1，在第四天休息，在第五天通过考试2。所以，他可以准备并通过所有考试。

在第二个样例中，有三天和两门考试。所以，Petya只能在一天内进行准备（因为在另外两天他应该参加考试）。那么Petya就不能准备并通过所有考试。

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
这些题解均采用贪心算法解决问题，核心思路是优先安排考试时间更早的考试，并尽早安排复习时间。不同题解在具体实现上存在差异，如排序方式、数据结构的使用等。

### 所选题解
- 作者：风中の菜鸡 (赞：6)，4星。
  - 关键亮点：思路清晰，代码注释详细，易于理解。通过结构体存储考试信息，按考试时间排序，然后枚举时间安排复习。
  - 个人心得：做完本题后，推荐练习 [P1230](https://www.luogu.com.cn/problem/P1230) 智力大冲浪，认为和本题思路、难度都差不多。
- 作者：fls233666 (赞：4)，4星。
  - 关键亮点：代码简洁，使用 `inline` 函数提高效率。同样按考试时间排序，从公布时间到考试前一天安排复习。
- 作者：kimidonatsu (赞：1)，4星。
  - 关键亮点：对贪心算法的解释详细，使用模块化编程，代码结构清晰。通过 `stable_sort` 按考试时间排序，枚举时间安排复习。

### 重点代码
#### 风中の菜鸡的代码
```cpp
struct Exam{
    int promulgate,start,review,place; 
}exam[110];
int cmp(Exam x,Exam y){ 
    return x.start<y.start;
}
// ...
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
核心思想：定义结构体存储考试信息，按考试时间排序，从公布时间到考试时间枚举，若当天无计划则安排复习，若复习天数不足则无解。

#### fls233666的代码
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
// ...
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
核心思想：定义结构体存储考试信息，按考试时间排序，从公布时间到考试前一天枚举，若当天空闲则安排复习，若复习天数不足则无解。

#### kimidonatsu的代码
```cpp
struct node {
    int s, d, c, id;
} exams[N];
inline bool cmp(const node x, const node y) {
    return x.d < y.d;
}
// ...
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
核心思想：定义结构体存储考试信息，按考试时间排序，从公布时间到考试前一天枚举，若当天无安排则安排复习，若复习天数不足则无解。

### 最优关键思路或技巧
- **贪心策略**：优先安排考试时间更早的考试，并尽早安排复习时间。
- **排序**：按考试时间对考试进行排序，确保先处理先考的考试。
- **结构体存储**：使用结构体存储考试的公布时间、考试时间、复习时间等信息，方便处理。

### 可拓展之处
同类型题或类似算法套路：此类贪心问题通常需要根据题目条件确定贪心策略，然后通过排序等操作实现。例如，活动选择问题、区间覆盖问题等，都可以通过贪心算法解决。

### 洛谷相似题目推荐
1. [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)
2. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

---
处理用时：54.46秒