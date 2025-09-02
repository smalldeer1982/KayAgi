# 题目信息

# Coffee and Coursework (Easy version)

## 题目描述

The only difference between easy and hard versions is the constraints.

Polycarp has to write a coursework. The coursework consists of $ m $ pages.

Polycarp also has $ n $ cups of coffee. The coffee in the $ i $ -th cup has $ a_i $ caffeine in it. Polycarp can drink some cups of coffee (each one no more than once). He can drink cups in any order. Polycarp drinks each cup instantly and completely (i.e. he cannot split any cup into several days).

Surely, courseworks are not usually being written in a single day (in a perfect world of Berland, at least). Some of them require multiple days of hard work.

Let's consider some day of Polycarp's work. Consider Polycarp drinks $ k $ cups of coffee during this day and caffeine dosages of cups Polycarp drink during this day are $ a_{i_1}, a_{i_2}, \dots, a_{i_k} $ . Then the first cup he drinks gives him energy to write $ a_{i_1} $ pages of coursework, the second cup gives him energy to write $ max(0, a_{i_2} - 1) $ pages, the third cup gives him energy to write $ max(0, a_{i_3} - 2) $ pages, ..., the $ k $ -th cup gives him energy to write $ max(0, a_{i_k} - k + 1) $ pages.

If Polycarp doesn't drink coffee during some day, he cannot write coursework at all that day.

Polycarp has to finish his coursework as soon as possible (spend the minimum number of days to do it). Your task is to find out this number of days or say that it is impossible.

## 说明/提示

In the first example Polycarp can drink fourth cup during first day (and write $ 1 $ page), first and second cups during second day (and write $ 2 + (3 - 1) = 4 $ pages), fifth cup during the third day (and write $ 2 $ pages) and third cup during the fourth day (and write $ 1 $ page) so the answer is $ 4 $ . It is obvious that there is no way to write the coursework in three or less days in this test.

In the second example Polycarp can drink third, fourth and second cups during first day (and write $ 4 + (2 - 1) + (3 - 2) = 6 $ pages) and sixth cup during second day (and write $ 4 $ pages) so the answer is $ 2 $ . It is obvious that Polycarp cannot write the whole coursework in one day in this test.

In the third example Polycarp can drink all cups of coffee during first day and write $ 5 + (5 - 1) + (5 - 2) + (5 - 3) + (5 - 4) = 15 $ pages of coursework.

In the fourth example Polycarp cannot drink all cups during first day and should drink one of them during the second day. So during first day he will write $ 5 + (5 - 1) + (5 - 2) + (5 - 3) = 14 $ pages of coursework and during second day he will write $ 5 $ pages of coursework. This is enough to complete it.

In the fifth example Polycarp cannot write the whole coursework at all, even if he will drink one cup of coffee during each day, so the answer is -1.

## 样例 #1

### 输入

```
5 8
2 3 1 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7 10
1 3 4 2 1 4 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 15
5 5 5 5 5
```

### 输出

```
1
```

## 样例 #4

### 输入

```
5 16
5 5 5 5 5
```

### 输出

```
2
```

## 样例 #5

### 输入

```
5 26
5 5 5 5 5
```

### 输出

```
-1
```

# AI分析结果

### 题目内容重写

# 咖啡与作业（简单版）

## 题目描述

简单版与困难版的唯一区别在于约束条件。

Polycarp 需要写一份作业，这份作业共有 $m$ 页。

Polycarp 还有 $n$ 杯咖啡。第 $i$ 杯咖啡含有 $a_i$ 的咖啡因。Polycarp 可以喝一些咖啡（每杯最多喝一次）。他可以以任意顺序喝这些咖啡。Polycarp 会立即且完全地喝完每一杯咖啡（即他不能将一杯咖啡分成几天喝）。

当然，作业通常不会在一天内完成（至少在 Berland 的完美世界中是这样）。有些作业需要多天的努力。

考虑 Polycarp 工作的某一天。假设 Polycarp 在这一天喝了 $k$ 杯咖啡，且他喝的咖啡的咖啡因含量分别为 $a_{i_1}, a_{i_2}, \dots, a_{i_k}$。那么第一杯咖啡会给他写 $a_{i_1}$ 页作业的能量，第二杯咖啡会给他写 $max(0, a_{i_2} - 1)$ 页的能量，第三杯咖啡会给他写 $max(0, a_{i_3} - 2)$ 页的能量，……，第 $k$ 杯咖啡会给他写 $max(0, a_{i_k} - k + 1)$ 页的能量。

如果 Polycarp 在某一天不喝咖啡，那么他这一天无法写作业。

Polycarp 需要尽快完成他的作业（花费最少的天数）。你的任务是找出这个天数，或者说明这是不可能的。

## 说明/提示

在第一个例子中，Polycarp 可以在第一天喝第四杯咖啡（并写 $1$ 页），第二天喝第一杯和第二杯咖啡（并写 $2 + (3 - 1) = 4$ 页），第三天喝第五杯咖啡（并写 $2$ 页），第四天喝第三杯咖啡（并写 $1$ 页），所以答案是 $4$。显然，在这个测试中，无法在三天或更少的时间内完成作业。

在第二个例子中，Polycarp 可以在第一天喝第三杯、第四杯和第二杯咖啡（并写 $4 + (2 - 1) + (3 - 2) = 6$ 页），第二天喝第六杯咖啡（并写 $4$ 页），所以答案是 $2$。显然，Polycarp 无法在一天内完成整个作业。

在第三个例子中，Polycarp 可以在第一天喝掉所有咖啡，并写 $5 + (5 - 1) + (5 - 2) + (5 - 3) + (5 - 4) = 15$ 页作业。

在第四个例子中，Polycarp 无法在第一天喝掉所有咖啡，因此他需要在第二天喝掉其中一杯。所以第一天他会写 $5 + (5 - 1) + (5 - 2) + (5 - 3) = 14$ 页作业，第二天他会写 $5$ 页作业。这足以完成作业。

在第五个例子中，Polycarp 无法完成整个作业，即使他每天喝一杯咖啡，所以答案是 -1。

## 样例 #1

### 输入

```
5 8
2 3 1 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7 10
1 3 4 2 1 4 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
5 15
5 5 5 5 5
```

### 输出

```
1
```

## 样例 #4

### 输入

```
5 16
5 5 5 5 5
```

### 输出

```
2
```

## 样例 #5

### 输入

```
5 26
5 5 5 5 5
```

### 输出

```
-1
```

### 算法分类
二分、贪心

### 题解分析与结论

本题的核心在于如何合理地安排咖啡的饮用顺序，以最小化完成作业所需的天数。由于答案具有单调性，大多数题解采用了二分搜索的策略，结合贪心算法来验证某个天数是否可行。

#### 关键思路：
1. **二分搜索**：通过二分搜索来枚举可能的天数，判断在该天数内是否能够完成作业。
2. **贪心策略**：在验证某个天数是否可行时，优先使用咖啡因含量较高的咖啡，以最大化每天的作业量。
3. **排序**：将咖啡因含量从大到小排序，确保优先使用高咖啡因的咖啡。

#### 难点对比：
- **二分搜索的实现**：不同题解在二分搜索的实现上略有差异，有的使用 `while(l <= r)`，有的使用 `while(l < r)`，但核心思想一致。
- **贪心策略的验证**：在验证某个天数是否可行时，如何计算每天的作业量是关键。大多数题解通过遍历咖啡数组，并根据天数计算每杯咖啡的贡献。

### 精选题解

#### 题解1：作者：yaaaaaan (4星)
**关键亮点**：
- 使用二分搜索和贪心策略，思路清晰。
- 代码结构简洁，易于理解。

**核心代码**：
```cpp
bool check(int x)
{
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        cnt+=max(a[i]-1LL*ceil(1.0*i/x)+1,1.0*0);
    }
    return cnt>=m;
}
```
**核心思想**：通过遍历咖啡数组，计算在 `x` 天内每杯咖啡的贡献，判断是否满足作业量要求。

#### 题解2：作者：Merge_all (4星)
**关键亮点**：
- 二分搜索结合贪心策略，代码实现较为简洁。
- 使用了 `greater<int>()` 进行降序排序，优化了贪心策略。

**核心代码**：
```cpp
bool check(){
    sum=0;
    for(int i=1;i<=n;i++){
        sum+=max(0ll*1.0,a[i]-ceil(1.0*i/mid)+1);
        if(sum>=m){
            return true;
        }
    }
    return false;
}
```
**核心思想**：在验证 `mid` 天数是否可行时，优先使用高咖啡因的咖啡，计算总作业量。

#### 题解3：作者：Helium_Ship (4星)
**关键亮点**：
- 二分搜索结合贪心策略，代码实现清晰。
- 在二分搜索中使用了 `l < r`，并在最后检查长度为1的区间。

**核心代码**：
```cpp
inline bool check(int x){
    int ans=0,cnt=0,tmp=1;
    bool flag=1;
    while (ans<m&&flag){
        for (int i=1;i<=x;i++){
            ans+=a[tmp]-cnt,tmp++;
            if (a[tmp]-cnt<=0||tmp>n){
                flag=0;
                break;
            }
        }
        cnt++;
    }
    return ans>=m;
}
```
**核心思想**：在 `x` 天内，优先使用高咖啡因的咖啡，计算总作业量。

### 最优关键思路
1. **二分搜索**：通过二分搜索枚举可能的天数，结合贪心策略验证是否可行。
2. **贪心策略**：优先使用高咖啡因的咖啡，以最大化每天的作业量。
3. **排序优化**：将咖啡因含量从大到小排序，确保优先使用高咖啡因的咖啡。

### 可拓展之处
- **类似算法套路**：二分搜索结合贪心策略的题目，如“最小化最大值”或“最大化最小值”问题。
- **举一反三**：可以尝试解决其他需要二分搜索和贪心策略结合的题目，如“分配资源最小化最大负载”等问题。

### 推荐题目
1. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)
2. [P1316 丢瓶盖](https://www.luogu.com.cn/problem/P1316)
3. [P1824 进击的奶牛](https://www.luogu.com.cn/problem/P1824)

### 个人心得
- **调试经历**：在二分搜索中，边界条件的处理是关键，特别是在 `while(l < r)` 和 `while(l <= r)` 的选择上，需要根据具体问题进行调整。
- **踩坑教训**：在贪心策略中，排序的顺序和计算每杯咖啡的贡献时，需要注意细节，避免漏算或多算。

---
处理用时：60.23秒