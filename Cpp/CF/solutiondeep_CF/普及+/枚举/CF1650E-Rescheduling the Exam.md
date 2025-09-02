# 题目信息

# Rescheduling the Exam

## 题目描述

Now Dmitry has a session, and he has to pass $ n $ exams. The session starts on day $ 1 $ and lasts $ d $ days. The $ i $ th exam will take place on the day of $ a_i $ ( $ 1 \le a_i \le d $ ), all $ a_i $ — are different.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/80b5043cb96246fb12fe0316b7ae224994f04da5.png)Sample, where $ n=3 $ , $ d=12 $ , $ a=[3,5,9] $ . Orange — exam days. Before the first exam Dmitry will rest $ 2 $ days, before the second he will rest $ 1 $ day and before the third he will rest $ 3 $ days.For the session schedule, Dmitry considers a special value $ \mu $ — the smallest of the rest times before the exam for all exams. For example, for the image above, $ \mu=1 $ . In other words, for the schedule, he counts exactly $ n $ numbers — how many days he rests between the exam $ i-1 $ and $ i $ (for $ i=0 $ between the start of the session and the exam $ i $ ). Then it finds $ \mu $ — the minimum among these $ n $ numbers.

Dmitry believes that he can improve the schedule of the session. He may ask to change the date of one exam (change one arbitrary value of $ a_i $ ). Help him change the date so that all $ a_i $ remain different, and the value of $ \mu $ is as large as possible.

For example, for the schedule above, it is most advantageous for Dmitry to move the second exam to the very end of the session. The new schedule will take the form:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/ea72ffbaa1a469cfa577e07f4a541e64f273ed21.png)Now the rest periods before exams are equal to $ [2,2,5] $ . So, $ \mu=2 $ .Dmitry can leave the proposed schedule unchanged (if there is no way to move one exam so that it will lead to an improvement in the situation).

## 说明/提示

The first sample is parsed in statement.

One of the optimal schedule changes for the second sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/a8127e465b7998df08b0c9dd6be925e73333852b.png)Initial schedule.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c109ce56a74359821f30b8b4de03ca418349d132.png)New schedule.

In the third sample, we need to move the exam from day $ 1 $ to any day from $ 4 $ to $ 100 $ .

In the fourth sample, any change in the schedule will only reduce $ \mu $ , so the schedule should be left as it is.

In the fifth sample, we need to move the exam from day $ 1 $ to any day from $ 100000000 $ to $ 300000000 $ .

One of the optimal schedule changes for the sixth sample:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c42982828b6b783bfe2b7287e37a4f2be5dfff0a.png)Initial schedule.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/40bee0dd841380562f7e8f2d4a71c924f5f6fe41.png)New schedule.

In the seventh sample, every day is exam day, and it is impossible to rearrange the schedule.

## 样例 #1

### 输入

```
9

3 12
3 5 9

2 5
1 5

2 100
1 2

5 15
3 6 9 12 15

3 1000000000
1 400000000 500000000

2 10
3 4

2 2
1 2

4 15
6 11 12 13

2 20
17 20```

### 输出

```
2
1
1
2
99999999
3
0
1
9```

# AI分析结果

### 题目内容
# 重新安排考试

## 题目描述
现在德米特里有一个考试季，他必须通过 \(n\) 场考试。考试季从第 \(1\) 天开始，持续 \(d\) 天。第 \(i\) 场考试将在第 \(a_i\) 天进行（\(1 \leq a_i \leq d\)），所有的 \(a_i\) 都不同。

![示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/80b5043cb96246fb12fe0316b7ae224994f04da5.png)
示例中，\(n = 3\)，\(d = 12\)，\(a = [3, 5, 9]\)。橙色表示考试日。在第一场考试前德米特里将休息 \(2\) 天，在第二场考试前他将休息 \(1\) 天，在第三场考试前他将休息 \(3\) 天。
对于考试季的日程安排，德米特里考虑一个特殊的值 \(\mu\) —— 所有考试前休息时间中的最小值。例如，对于上面的图片，\(\mu = 1\)。换句话说，对于这个日程安排，他确切地计算 \(n\) 个数字 —— 他在第 \(i - 1\) 场考试和第 \(i\) 场考试之间休息多少天（对于 \(i = 0\)，是在考试季开始和第 \(i\) 场考试之间）。然后找到 \(\mu\) —— 这些 \(n\) 个数字中的最小值。

德米特里认为他可以改进考试季的日程安排。他可以请求更改一场考试的日期（更改任意一个 \(a_i\) 的值）。帮助他更改日期，使得所有的 \(a_i\) 仍然不同，并且 \(\mu\) 的值尽可能大。

例如，对于上面的日程安排，对德米特里来说最有利的是将第二场考试移到考试季的最后。新的日程安排将如下所示：

![新示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/ea72ffbaa1a469cfa577e07f4a541e64f273ed21.png)
现在考试前的休息时间分别为 \([2, 2, 5]\)。所以，\(\mu = 2\)。
德米特里可以保持提议的日程安排不变（如果没有办法移动一场考试以改善情况）。

## 说明/提示
第一个样例在题目描述中已解析。

第二个样例的一个最优日程更改：

![初始日程](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/a8127e465b7998df08b0c9dd6be925e73333852b.png)
初始日程。

![新日程](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c109ce56a74359821f30b8b4de03ca418349d132.png)
新日程。

在第三个样例中，我们需要将考试从第 \(1\) 天移到第 \(4\) 天到第 \(100\) 天中的任意一天。

在第四个样例中，任何日程更改只会降低 \(\mu\)，所以日程应该保持不变。

在第五个样例中，我们需要将考试从第 \(1\) 天移到第 \(100000000\) 天到第 \(300000000\) 天中的任意一天。

第六个样例的一个最优日程更改：

![初始日程](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/c42982828b6b783bfe2b7287e37a4f2be5dfff0a.png)
初始日程。

![新日程](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1650E/40bee0dd841380562f7e8f2d4a71c924f5f6fe41.png)
新日程。

在第七个样例中，每天都是考试日，无法重新安排日程。

## 样例 #1
### 输入
```
9

3 12
3 5 9

2 5
1 5

2 100
1 2

5 15
3 6 9 12 15

3 1000000000
1 400000000 500000000

2 10
3 4

2 2
1 2

4 15
6 11 12 13

2 20
17 20
```
### 输出
```
2
1
1
2
99999999
3
0
1
9
```

### 题解综合分析与结论
- **思路**：多数题解都基于贪心思想，认为要使 \(\mu\) 值最大，应修改产生最小距离的相邻考试日期。对于修改方式，都考虑了将考试插入到距离最大的两个相邻考试之间或插入到最后（第 \(d\) 天）这两种情况。
- **算法要点**：找到最小间隔的考试位置，计算修改该位置或其前一个位置考试日期后的最优间隔。部分题解使用二分查找答案，通过检查给定间隔是否可行来确定最终结果。
- **解决难点**：核心在于如何确定修改哪一场考试以及如何计算修改后能得到的最优间隔。不同题解通过不同方式实现，如直接贪心计算、二分查找结合检查函数等。

### 所选的题解
- **作者：DaiRuiChen007（5星）**
  - **关键亮点**：思路清晰，直接基于贪心策略，代码简洁高效。通过一次遍历找到最小间隔位置，然后分别计算修改该位置及前一个位置考试日期后的最优解。
  - **核心代码**：
```cpp
inline int calc(int x) {
    int lst = 0, min_gap = d, max_gap = 0;
    for(int i = 1; i <= n; ++i) {
        if(i == x) continue;
        int gap = a[i] - a[lst] - 1;
        min_gap = min(min_gap, gap);
        max_gap = max(max_gap, gap);
        lst = i;
    }
    return min(min_gap, max(((max_gap - 1)/2), d - a[lst] - 1));
}
inline void solve() {
    int pos = 1, res = 0;
    scanf("%d%d", &n, &d);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        if(a[i] - a[i - 1] - 1 < a[pos] - a[pos - 1] - 1) pos = i;
    }
    res = calc(pos); 
    if(pos > 1) res = max(res, calc(pos - 1));
    printf("%d\n", res);
    return ;
}
```
  - **核心思想**：`calc` 函数计算修改第 `x` 个考试日期后的最优间隔。先遍历得到最小和最大间隔，再根据两种插入情况计算并返回最优间隔。`solve` 函数找到最小间隔位置，调用 `calc` 函数计算修改该位置及前一个位置后的结果并输出。
- **作者：OIer_ACMer（4星）**
  - **关键亮点**：采用二分答案的方法，思路独特。通过二分查找最大的可行间隔，`check` 函数详细判断给定间隔是否能通过修改一场考试日期实现。
  - **个人心得**：无
  - **核心代码**：
```cpp
bool check(int x) {
    int index = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] - a[i - 1] - 1 < x) {
            index = i;
            break;
        }
    }
    if (!index) {
        return 1;
    }
    int cnt = 0, f = 0;
    for (int i = 1; i <= n; i++) {
        if (i!= index) {
            b[++cnt] = a[i];
        }
    }
    if (d - b[cnt] - 1 >= x) {
        f = 1;
    }
    for (int i = 1; i < n; i++) {
        if (b[i] - b[i - 1] - 1 < x) {
            f = 0;
            break;
        }
        if (b[i] - b[i - 1] >= 2 * x + 2) {
            f = 1;
        }
    }
    if (f) {
        return 1;
    }
    index--;
    cnt = f = 0;
    if (index == 0) {
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        if (i!= index) {
            b[++cnt] = a[i];
        }
    }
    if (d - b[cnt] - 1 >= x) {
        f = 1;
    }
    for (int i = 1; i < n; i++) {
        if (b[i] - b[i - 1] - 1 < x) {
            f = 0;
            break;
        }
        if (b[i] - b[i - 1] >= 2 * x + 2) {
            f = 1;
        }
    }
    if (f) {
        return 1;
    }
    return 0;
}
void littlefat() {
    n = read(), d = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
    }
    int l = 0, r = d;
    while (l < r - 10) {
        int mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    for (int i = r; i >= l; i--) {
        if (check(i)) {
            cout << i << endl;
            return;
        }
    }
}
```
  - **核心思想**：`check` 函数检查间隔 `x` 是否可行。先找到小于 `x` 的间隔位置，将该位置考试排除后检查剩余考试间隔情况，包括最后一场考试后的间隔以及相邻考试间隔，若满足条件则返回 `true`。`littlefat` 函数通过二分查找最大的可行间隔。
- **作者：Fislett（4星）**
  - **关键亮点**：贪心思路明确，代码简洁易懂。与 DaiRuiChen007 的解法类似，也是基于贪心确定修改位置并计算最优间隔。
  - **个人心得**：无
  - **核心代码**：
```cpp
int dis(int x, int y) {return a[x] - a[y] - 1;}
int f(int x)
{
    int Min = 2e9, Max = 0, last = 0; 
    for (int i = 1; i <= n; i ++)
    {
        if (i == x) continue; 
        Min = min(dis(i, last), Min);
        Max = max(dis(i, last), Max);
        last = i;
    }
    return min(Min, max((Max - 1) >> 1, d - a[last] - 1));
}
int main()
{
    scanf("%d", &t);
    while (t --)
    {
        int minn = 2e9, minx, ans = 0;
        scanf("%d%d", &n, &d);
        for (int i = 1; i <= n; i ++)
        {
            scanf("%d", &a[i]);
            if (dis(i, i - 1) < minn) 
            {
                minn = dis(i, i - 1);
                minx = i;
            }
        }
        ans = f(minx);
        if (minx!= 1) ans = max(ans, f(minx - 1)); 
        printf("%d\n", ans);
    }
}
```
  - **核心思想**：`dis` 函数计算相邻考试间隔。`f` 函数计算修改第 `x` 个考试日期后的最优间隔，与 DaiRuiChen007 的 `calc` 函数思路一致。`main` 函数找到最小间隔位置，调用 `f` 函数计算修改该位置及前一个位置后的结果并输出。

### 最优关键思路或技巧
贪心策略是解决本题的关键，即选择修改产生最小间隔的相邻考试日期。在计算修改后的最优间隔时，考虑插入到距离最大的两个相邻考试之间或插入到最后（第 \(d\) 天）这两种情况，通过简单的数学计算得出结果。二分查找答案的方法提供了另一种解题思路，适用于求最值且可通过检查函数判断可行性的场景。

### 可拓展之处
同类型题可能会改变考试数量、考试时间范围、修改考试日期的次数等条件。类似算法套路可应用于涉及间隔优化、最值求解且可通过局部调整达到全局最优的问题。例如，在一些资源分配问题中，通过贪心选择局部最优解来实现全局最优。

### 推荐洛谷题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过贪心策略解决问题，与本题贪心选择修改位置思路类似。
- [P1248 加工生产调度](https://www.luogu.com.cn/problem/P1248)：同样运用贪心算法，在不同任务调度场景下寻找最优解。
- [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：涉及到排序和贪心策略，与本题通过分析条件确定最优解的思路有相似之处。

### 个人心得摘录与总结
无个人心得。 

---
处理用时：55.71秒