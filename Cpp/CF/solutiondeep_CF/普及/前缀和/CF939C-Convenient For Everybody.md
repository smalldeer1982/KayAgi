# 题目信息

# Convenient For Everybody

## 题目描述

In distant future on Earth day lasts for $ n $ hours and that's why there are $ n $ timezones. Local times in adjacent timezones differ by one hour. For describing local time, hours numbers from $ 1 $ to $ n $ are used, i.e. there is no time "0 hours", instead of it " $ n $ hours" is used. When local time in the $ 1 $ -st timezone is $ 1 $ hour, local time in the $ i $ -th timezone is $ i $ hours.

Some online programming contests platform wants to conduct a contest that lasts for an hour in such a way that its beginning coincides with beginning of some hour (in all time zones). The platform knows, that there are $ a_{i} $ people from $ i $ -th timezone who want to participate in the contest. Each person will participate if and only if the contest starts no earlier than $ s $ hours 00 minutes local time and ends not later than $ f $ hours 00 minutes local time. Values $ s $ and $ f $ are equal for all time zones. If the contest starts at $ f $ hours 00 minutes local time, the person won't participate in it.

Help platform select such an hour, that the number of people who will participate in the contest is maximum.

## 说明/提示

In the first example, it's optimal to start competition at $ 3 $ hours (in first timezone). In this case, it will be $ 1 $ hour in the second timezone and $ 2 $ hours in the third timezone. Only one person from the first timezone won't participate.

In second example only people from the third and the fourth timezones will participate.

## 样例 #1

### 输入

```
3
1 2 3
1 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 2 3 4 1
1 3
```

### 输出

```
4
```

# AI分析结果

### 题目内容重写

#### 题目描述

在遥远的未来，地球的一天被划分为 $n$ 个小时，因此地球被划分为 $n$ 个时区。相邻时区的本地时间相差 1 小时。本地时间用 $1$ 到 $n$ 表示，即没有“0 小时”，而是用“$n$ 小时”表示。当第 1 时区的本地时间为 1 小时时，第 $i$ 时区的本地时间为 $i$ 小时。

某个在线编程竞赛平台希望举办一场持续 1 小时的比赛，比赛的开始时间与某个小时的开始时间一致（在所有时区中）。平台知道，第 $i$ 时区有 $a_{i}$ 人希望参加比赛。每个人只有在比赛开始时间不早于本地时间 $s$ 小时 00 分钟，且结束时间不晚于本地时间 $f$ 小时 00 分钟时才会参加比赛。如果比赛在本地时间 $f$ 小时 00 分钟开始，该时区的人将不会参加比赛。

帮助平台选择一个开始时间，使得参加比赛的人数最多。

#### 说明/提示

在第一个例子中，最优选择是在第 1 时区的 3 小时开始比赛。此时，第 2 时区的时间为 1 小时，第 3 时区的时间为 2 小时。只有第 1 时区的一个人不会参加比赛。

在第二个例子中，只有第 3 和第 4 时区的人会参加比赛。

#### 样例 #1

##### 输入

```
3
1 2 3
1 3
```

##### 输出

```
3
```

#### 样例 #2

##### 输入

```
5
1 2 3 4 1
1 3
```

##### 输出

```
4
```

### 题解分析与结论

#### 综合分析与结论

1. **思路对比**：
   - **信守天下**：通过枚举比赛开始时间，利用滑动窗口计算每个时区的参赛人数，最终找到最大值。代码简洁，思路清晰。
   - **helongyun**：使用前缀和优化，分三种情况计算参赛人数，代码较为复杂，但思路清晰。
   - **封禁用户**：与helongyun的思路类似，使用前缀和优化，代码结构清晰，但与前两者相比没有明显优势。
   - **Caro23333**：与helongyun和封禁用户的思路一致，使用前缀和优化，代码结构清晰，但与前两者相比没有明显优势。

2. **评分**：
   - **信守天下**：5星。代码简洁，思路清晰，滑动窗口优化得当。
   - **helongyun**：4星。思路清晰，但代码复杂度较高。
   - **封禁用户**：4星。思路清晰，代码结构清晰，但与前两者相比没有明显优势。
   - **Caro23333**：4星。思路清晰，代码结构清晰，但与前两者相比没有明显优势。

3. **最优关键思路**：
   - **滑动窗口**：通过滑动窗口计算每个时区的参赛人数，时间复杂度为 $O(n)$，效率高。
   - **前缀和优化**：通过前缀和快速计算区间和，适用于需要频繁计算区间和的场景。

4. **可拓展之处**：
   - 类似的时间区间问题，如会议安排、活动安排等，都可以使用滑动窗口或前缀和优化。
   - 可以扩展到二维或更高维度的区间和计算，如矩阵中的子矩阵和。

5. **推荐题目**：
   - [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
   - [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
   - [P3368 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3368)

### 所选高分题解

#### 信守天下 (5星)

**关键亮点**：
- 使用滑动窗口优化，时间复杂度为 $O(n)$，效率高。
- 代码简洁，思路清晰。

**核心代码**：
```cpp
for (int i = 0; i < n; i++) {
    l = (s - i + n) % n;
    r = (f - i + n) % n;
    sum -= a[r];
    sum += a[l];
    if (sum > mx) {
        mx = sum;
        ans = i;
    }
}
```
**核心实现思想**：
通过滑动窗口计算每个时区的参赛人数，最终找到最大值。

#### helongyun (4星)

**关键亮点**：
- 使用前缀和优化，分三种情况计算参赛人数，思路清晰。

**核心代码**：
```cpp
if(i<=s) ans=z[f-i]-z[s-i];
if(s<i&&i<f) ans=z[f-i]+z[n]-z[s-i+n];
if(i>=f) ans=z[f-i+n]-z[s-i+n];
```
**核心实现思想**：
通过前缀和快速计算区间和，适用于需要频繁计算区间和的场景。

#### 封禁用户 (4星)

**关键亮点**：
- 使用前缀和优化，代码结构清晰。

**核心代码**：
```cpp
if(i<=s) sum=a[f-i]-a[s-i];
if(s<i&&i<f) sum=a[f-i]+a[n]-a[s-i+n];
if(i>=f) sum=a[f-i+n]-a[s-i+n];
```
**核心实现思想**：
通过前缀和快速计算区间和，适用于需要频繁计算区间和的场景。

---
处理用时：44.39秒