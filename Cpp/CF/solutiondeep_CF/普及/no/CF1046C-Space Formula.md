# 题目信息

# Space Formula

## 题目描述

Formula 1 officials decided to introduce new competition. Cars are replaced by space ships and number of points awarded can differ per race.

Given the current ranking in the competition and points distribution for the next race, your task is to calculate the best possible ranking for a given astronaut after the next race. It's guaranteed that given astronaut will have unique number of points before the race.

## 说明/提示

If the third ranked astronaut wins the race, he will have 35 points. He cannot take the leading position, but he can overtake the second position if the second ranked astronaut finishes the race at the last position.

## 样例 #1

### 输入

```
4 3
50 30 20 10
15 10 7 3
```

### 输出

```
2
```

# AI分析结果

### 题目翻译

# 太空公式

## 题目描述

F1官方决定引入新的比赛。赛车被替换为宇宙飞船，并且每场比赛的得分分配可能不同。

给定当前比赛的排名和下一场比赛的得分分配，你的任务是计算给定宇航员在下一场比赛后可能获得的最佳排名。保证给定的宇航员在比赛前的得分是唯一的。

## 说明/提示

如果排名第三的宇航员赢得了比赛，他将获得35分。他无法取得领先位置，但如果排名第二的宇航员在比赛中获得最后一名，他可以超越第二名的位置。

## 样例 #1

### 输入

```
4 3
50 30 20 10
15 10 7 3
```

### 输出

```
2
```

### 算法分类
贪心

### 题解分析与结论

题目要求计算给定宇航员在下一场比赛后可能获得的最佳排名。核心思路是通过贪心算法，假设该宇航员在比赛中获得最高分，然后计算他能够超越多少名比他当前排名高的宇航员。

#### 题解对比
1. **DennyQi** 的题解通过贪心算法，假设宇航员获得最高分，然后从后向前遍历，计算能够超越的宇航员数量。时间复杂度为O(n)，代码简洁高效。
2. **Michael1234** 的题解也采用了贪心算法，但思路较为简单，直接假设宇航员获得最高分，然后遍历前面的宇航员，计算能够超越的数量。时间复杂度为O(n)，但代码实现稍显冗长。
3. **ThySecret** 的题解提出了两种方法：二分查找和双指针优化。双指针优化方法时间复杂度为O(n)，与贪心算法类似，但实现更为复杂。

#### 最优关键思路
贪心算法是解决该问题的最优方法。通过假设宇航员获得最高分，然后从后向前遍历，计算能够超越的宇航员数量，可以在O(n)时间复杂度内解决问题。

#### 可拓展之处
类似的问题可以通过贪心算法解决，例如在比赛中计算选手的最佳排名、在资源分配中计算最优分配方案等。

### 推荐题目
1. [P1046 太空公式](https://www.luogu.com.cn/problem/P1046)
2. [P1047 太空公式2](https://www.luogu.com.cn/problem/P1047)
3. [P1048 太空公式3](https://www.luogu.com.cn/problem/P1048)

### 所选高分题解

#### 题解1：DennyQi (5星)
**关键亮点**：
- 贪心算法，时间复杂度O(n)
- 代码简洁高效，逻辑清晰

**核心代码**：
```cpp
int N,D,Ans,st(2);
int s[MAXN],p[MAXN];
int main(){
    N = r, Ans = D = r;
    for(int i = 1; i <= N; ++i) s[i] = r;
    for(int i = 1; i <= N; ++i) p[i] = r;
    for(int i = D-1; i > 0; --i){
        while(s[i] + p[st] > s[D] + p[1] && st <= N) ++st;
        if(st > N) break;
        --Ans, ++st;
    }
    printf("%d", Ans);
    return 0;
}
```

#### 题解2：ThySecret (4星)
**关键亮点**：
- 提出了双指针优化方法，时间复杂度O(n)
- 思路清晰，代码实现较为复杂

**核心代码**：
```cpp
int n, pos; cin >> n >> pos;
for (int i = 1; i <= n; i++) cin >> s[i];
for (int i = 1; i <= n; i++) cin >> p[i];
int maxn = s[pos] + p[1], ans = pos;
for (int i = pos - 1, cur = 2; i >= 1; i--){
    while (s[i] + p[cur] > maxn && cur <= n) cur ++;
    if (cur > n) break;
    ans --, cur ++;
}
cout << ans << '\n';
```

### 个人心得
DennyQi 的题解通过贪心算法，简洁高效地解决了问题，代码逻辑清晰，值得学习。ThySecret 的题解虽然提出了双指针优化方法，但实现较为复杂，适合对算法有深入理解的同学参考。

---
处理用时：33.66秒