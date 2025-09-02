# 题目信息

# Quiz Master

## 题目描述

A school has to decide on its team for an international quiz. There are $ n $ students in the school. We can describe the students using an array $ a $ where $ a_i $ is the smartness of the $ i $ -th ( $ 1 \le i \le n $ ) student.

There are $ m $ topics $ 1, 2, 3, \ldots, m $ from which the quiz questions will be formed. The $ i $ -th student is considered proficient in a topic $ T $ if $ (a_i \bmod T) = 0 $ . Otherwise, he is a rookie in that topic.

We say that a team of students is collectively proficient in all the topics if for every topic there is a member of the team proficient in this topic.

Find a team that is collectively proficient in all the topics such that the maximum difference between the smartness of any two students in that team is minimized. Output this difference.

## 说明/提示

In the first test case, we have participants with smartnesses $ 3 $ and $ 7 $ , and $ m = 4 $ . Thus, there is no student with smartness divisible by $ 2 $ . Since $ 2 \leq m $ , there is no way to choose a team.

In the second test case, we can select the participant with smartness $ 2 $ to be the only one on the team. This way the team will be collectively proficient in both topics $ 1 $ and $ 2 $ .

In the third test case, consider the team with participants of smartnesses $ 4, 5, 6, 7 $ . This way the team will be collectively proficient in all topics $ 1, 2, \ldots, 7 $ .

## 样例 #1

### 输入

```
3
2 4
3 7
4 2
3 7 2 9
5 7
6 4 3 5 7```

### 输出

```
-1
0
3```

# AI分析结果

### 题目内容重写
#### 题目描述
一所学校需要决定其国际竞赛的团队。学校中有 $n$ 名学生，可以用一个数组 $a$ 来描述这些学生，其中 $a_i$ 表示第 $i$ 名学生的聪明度。

竞赛有 $m$ 个主题，编号为 $1, 2, 3, \ldots, m$。如果 $(a_i \bmod T) = 0$，则第 $i$ 名学生被认为精通主题 $T$，否则他在这方面是新手。

我们说一个学生团队在所有主题上都是集体精通的，如果对于每个主题，团队中至少有一名成员精通该主题。

找到一个在所有主题上集体精通的团队，使得团队中任意两名学生聪明度的最大差异最小化。输出这个差异。

#### 说明/提示
在第一个测试用例中，我们有聪明度为 $3$ 和 $7$ 的参与者，$m = 4$。因此，没有学生的聪明度能被 $2$ 整除。由于 $2 \leq m$，无法选择团队。

在第二个测试用例中，我们可以选择聪明度为 $2$ 的参与者作为团队的唯一成员。这样，团队将在主题 $1$ 和 $2$ 上集体精通。

在第三个测试用例中，考虑聪明度为 $4, 5, 6, 7$ 的参与者组成的团队。这样，团队将在所有主题 $1, 2, \ldots, 7$ 上集体精通。

#### 样例 #1
##### 输入
```
3
2 4
3 7
4 2
3 7 2 9
5 7
6 4 3 5 7
```
##### 输出
```
-1
0
3
```

### 算法分类
排序、双指针、数学

### 题解分析与结论
该题的核心在于找到一个学生团队，使得团队中所有成员的聪明度的因子覆盖了 $1$ 到 $m$ 的所有主题，并且团队中聪明度的最大差异最小化。题解中普遍采用了排序和双指针的策略，通过预处理每个数的因子，然后使用双指针来维护一个区间，使得该区间内的数的因子覆盖了所有主题。

### 评分较高的题解
#### 1. 作者：yemuzhe (赞：7)
**星级：5星**
**关键亮点：**
- 使用了双指针算法，通过预处理每个数的因子，优化了时间复杂度。
- 代码清晰，逻辑严谨，详细解释了每一步的操作。

**核心代码：**
```cpp
for (int l = 1, r = 0; l <= n; l ++) {
    while (r < n && cnt < m) {
        r ++;
        for (int i = 0; i < v[a[r]].size (); i ++) {
            t = v[a[r]][i];
            cnt += t <= m && !(vis[t] ++);
        }
    }
    if (cnt == m) {
        ans = min (ans, a[r] - a[l]);
    }
    for (int i = 0; i < v[a[l]].size (); i ++) {
        t = v[a[l]][i];
        cnt -= t <= m && !(-- vis[t]);
    }
}
```
**核心思想：**
通过双指针维护一个区间，使得区间内的数的因子覆盖了所有主题，同时更新最小差异。

#### 2. 作者：ExplodingKonjac (赞：3)
**星级：4星**
**关键亮点：**
- 使用了双指针和桶计数的方法，动态维护区间内因子的出现次数。
- 代码简洁，逻辑清晰。

**核心代码：**
```cpp
for (int i = 1, j = 1; i <= n; i++) {
    for (auto &k: d[a[i]])
        if (k <= m) add(k, 1);
    while (j <= i && tot == m) {
        ans = min(ans, a[i] - a[j]);
        for (auto &k: d[a[j]])
            if (k <= m) add(k, -1);
        j++;
    }
}
```
**核心思想：**
通过双指针和桶计数的方法，动态维护区间内因子的出现次数，确保覆盖所有主题。

#### 3. 作者：DaiRuiChen007 (赞：0)
**星级：4星**
**关键亮点：**
- 使用了双指针和因子的预处理，优化了时间复杂度。
- 代码结构清晰，逻辑严谨。

**核心代码：**
```cpp
for (int l = 1, r = 0; l <= n; ++l) {
    while (r < n && tot != 0) add(a[++r]);
    if (tot > 0) break;
    ans = min(ans, a[r] - a[l]);
    del(a[l]);
}
```
**核心思想：**
通过双指针和因子的预处理，动态维护区间内因子的出现次数，确保覆盖所有主题。

### 最优关键思路或技巧
1. **预处理因子**：通过预处理每个数的因子，优化了后续的查询和更新操作。
2. **双指针维护区间**：通过双指针维护一个区间，使得区间内的数的因子覆盖了所有主题，同时更新最小差异。
3. **桶计数**：使用桶计数的方法，动态维护区间内因子的出现次数，确保覆盖所有主题。

### 可拓展之处
该题的思路可以拓展到其他需要覆盖特定条件的区间问题，例如覆盖特定字符、覆盖特定数字等。类似的问题可以通过预处理和双指针的方法来解决。

### 推荐题目
1. [P1712 [NOI2016] 区间](https://www.luogu.com.cn/problem/P1712)
2. [P7514 [省选联考 2021 A/B 卷] 卡牌游戏](https://www.luogu.com.cn/problem/P7514)
3. [P1496 火烧赤壁](https://www.luogu.com.cn/problem/P1496)

### 个人心得
在调试过程中，发现预处理因子的时间复杂度较高，因此采用了 $O(n \log n)$ 的预处理方法，优化了整体时间复杂度。此外，双指针的移动顺序和条件判断需要仔细处理，确保区间内的因子覆盖所有主题。

---
处理用时：44.34秒