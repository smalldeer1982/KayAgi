# 题目信息

# Boats Competition

## 题目描述

There are $ n $ people who want to participate in a boat competition. The weight of the $ i $ -th participant is $ w_i $ . Only teams consisting of two people can participate in this competition. As an organizer, you think that it's fair to allow only teams with the same total weight.

So, if there are $ k $ teams $ (a_1, b_1) $ , $ (a_2,       b_2) $ , $ \dots $ , $ (a_k, b_k) $ , where $ a_i $ is the weight of the first participant of the $ i $ -th team and $ b_i $ is the weight of the second participant of the $ i $ -th team, then the condition $ a_1 + b_1 = a_2 + b_2 =       \dots = a_k + b_k = s $ , where $ s $ is the total weight of each team, should be satisfied.

Your task is to choose such $ s $ that the number of teams people can create is the maximum possible. Note that each participant can be in no more than one team.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, we can reach the optimal answer for $ s=6 $ . Then the first boat is used by participants $ 1 $ and $ 5 $ and the second boat is used by participants $ 2 $ and $ 4 $ (indices are the same as weights).

In the second test case of the example, we can reach the optimal answer for $ s=12 $ . Then first $ 6 $ participants can form $ 3 $ pairs.

In the third test case of the example, we can reach the optimal answer for $ s=3 $ . The answer is $ 4 $ because we have $ 4 $ participants with weight $ 1 $ and $ 4 $ participants with weight $ 2 $ .

In the fourth test case of the example, we can reach the optimal answer for $ s=4 $ or $ s=6 $ .

In the fifth test case of the example, we can reach the optimal answer for $ s=3 $ . Note that participant with weight $ 3 $ can't use the boat because there is no suitable pair for him in the list.

## 样例 #1

### 输入

```
5
5
1 2 3 4 5
8
6 6 6 6 6 6 8 8
8
1 2 2 1 2 1 1 2
3
1 3 3
6
1 1 3 4 2 2```

### 输出

```
2
3
4
1
2```

# AI分析结果

### 题目内容重写
**题目描述**

有 $n$ 个人想参加划船比赛。第 $i$ 个人的体重为 $w_i$。只有由两人组成的队伍才能参加比赛。作为组织者，你认为只有总重量相同的队伍才是公平的。

因此，如果有 $k$ 个队伍 $(a_1, b_1)$, $(a_2, b_2)$, $\dots$, $(a_k, b_k)$，其中 $a_i$ 是第 $i$ 个队伍的第一个人的体重，$b_i$ 是第二个人的体重，那么必须满足 $a_1 + b_1 = a_2 + b_2 = \dots = a_k + b_k = s$，其中 $s$ 是每个队伍的总重量。

你的任务是选择一个 $s$，使得可以组成的队伍数量尽可能多。注意，每个人最多只能在一个队伍中。

你需要回答 $t$ 个独立的测试用例。

**说明/提示**

在第一个测试用例中，我们可以选择 $s=6$，这样第一艘船由第 1 和第 5 个人使用，第二艘船由第 2 和第 4 个人使用（索引与体重相同）。

在第二个测试用例中，我们可以选择 $s=12$，这样前 6 个人可以组成 3 对。

在第三个测试用例中，我们可以选择 $s=3$，答案是 4，因为我们有 4 个体重为 1 的人和 4 个体重为 2 的人。

在第四个测试用例中，我们可以选择 $s=4$ 或 $s=6$。

在第五个测试用例中，我们可以选择 $s=3$。注意，体重为 3 的人不能使用船，因为列表中没有合适的配对。

**样例 #1**

### 输入

```
5
5
1 2 3 4 5
8
6 6 6 6 6 6 8 8
8
1 2 2 1 2 1 1 2
3
1 3 3
6
1 1 3 4 2 2
```

### 输出

```
2
3
4
1
2
```

### 算法分类
枚举

### 题解分析与结论
本题的核心是通过枚举所有可能的队伍总重量 $s$，然后统计在每个 $s$ 下可以组成的队伍数量，最终取最大值。由于 $n$ 和 $w_i$ 的范围都很小，暴力枚举是可行的。

### 所选题解
#### 1. 作者：Tenshi (赞：7)
**星级：5星**
**关键亮点：**
- 使用尺取法优化了枚举过程，减少了时间复杂度。
- 代码清晰，逻辑严谨，特别是对尺取法的应用非常巧妙。
- 提供了详细的思路分析和代码注释，便于理解。

**核心代码：**
```cpp
while(val[s]+val[t]==k && s<t){
    s++,t--;
    rec++;
}
while(val[s]+val[t]<k && s<t){
    s++;
}
while(val[s]+val[t]>k && s<t){
    t--;
}
if(s>=t){
    ans=max(ans,rec);
    break;
}
```
**核心思想：**
通过尺取法在排序后的数组中快速找到满足条件的配对，减少了不必要的枚举。

#### 2. 作者：xiaoPanda (赞：3)
**星级：4星**
**关键亮点：**
- 使用贪心策略，每次找到满足条件的配对后立即减少计数，避免了重复计算。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码：**
```cpp
if (i > a[j] && f[i - a[j]] > 0 && f[a[j]] > 0) {
    if (i - a[j] == a[j]) {
        if (f[a[j]] > 1) sum++, f[i - a[j]]--, f[a[j]]--;
    } else {
        sum++, f[i - a[j]]--, f[a[j]]--;
    }
}
```
**核心思想：**
通过贪心策略，每次找到满足条件的配对后立即减少计数，避免了重复计算。

#### 3. 作者：wmy_goes_to_thu (赞：3)
**星级：4星**
**关键亮点：**
- 使用双指针法，排序后从左到右枚举，确保每次找到的配对是最优的。
- 代码简洁，逻辑清晰，适合初学者理解。

**核心代码：**
```cpp
while(l<r) {
    if(w[l]+w[r]>s) r--;
    else if(w[l]+w[r]<s) l++;
    else anss++, l++, r--;
}
```
**核心思想：**
通过双指针法在排序后的数组中快速找到满足条件的配对，减少了不必要的枚举。

### 最优关键思路或技巧
- **尺取法**：在排序后的数组中，通过双指针快速找到满足条件的配对，减少时间复杂度。
- **贪心策略**：每次找到满足条件的配对后立即减少计数，避免重复计算。
- **双指针法**：在排序后的数组中，通过双指针快速找到满足条件的配对，减少不必要的枚举。

### 可拓展之处
- 类似的问题可以扩展到更多元素的组合，如三人队伍、四人队伍等。
- 可以结合其他算法如动态规划，进一步优化时间复杂度。

### 推荐题目
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

---
处理用时：38.69秒