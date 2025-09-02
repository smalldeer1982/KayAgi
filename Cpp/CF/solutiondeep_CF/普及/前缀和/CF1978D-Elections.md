# 题目信息

# Elections

## 题目描述

Elections are taking place in Berland. There are $ n $ candidates participating in the elections, numbered from $ 1 $ to $ n $ . The $ i $ -th candidate has $ a_i $ fans who will vote for him. Additionally, there are $ c $ people who are undecided about their favorite candidate, let's call them undecided. Undecided people will vote for the candidate with the lowest number.

The candidate who receives the maximum number of votes wins the elections, and if multiple candidates receive the same maximum number of votes, the candidate with the lowest number among them wins.

You found these elections too boring and predictable, so you decided to exclude some candidates from them. If you do not allow candidate number $ i $ to participate in the elections, all $ a_i $ of his fans will become undecided, and will vote for the candidate with the lowest number.

You are curious to find, for each $ i $ from $ 1 $ to $ n $ , the minimum number of candidates that need to be excluded from the elections for candidate number $ i $ to win the elections.

## 说明/提示

In the first test case:

- If all candidates are allowed, candidate number $ 1 $ will receive $ 3 $ votes ( $ 1 $ undecided person will vote for him), candidate number $ 2 $ will receive $ 0 $ votes, and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 1 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 0 $ .
- If candidate number $ 1 $ is not allowed, his $ 2 $ fans will become undecided. Then candidate number $ 2 $ will receive $ 3 $ votes ( $ 3 $ undecided people will vote for him) and candidate number $ 3 $ will receive $ 3 $ votes. Therefore, candidate number $ 2 $ wins (he received the same number of votes as candidate $ 3 $ , but his number is lower), so the answer for him is $ 1 $ .
- If candidates with numbers $ 1 $ and $ 2 $ are not allowed, candidate number $ 3 $ wins, so the answer for him is $ 2 $ .

In the second test case, candidate number $ 1 $ will win if candidate number $ 2 $ is not allowed to participate.

## 样例 #1

### 输入

```
5
3 1
2 0 3
2 3
0 10
5 3
5 4 3 2 1
4 5
3 10 7 1
6 0
2 2 2 3 3 3```

### 输出

```
0 1 2
1 0
0 1 2 3 4
1 0 2 3
1 1 2 0 4 5```

# AI分析结果

### 题目内容重写
# 选举

## 题目描述

在Berland地区正在进行选举。共有$n$位候选人参与选举，编号从$1$到$n$。第$i$位候选人有$a_i$位粉丝会为他投票。此外，还有$c$位尚未决定投票对象的选民，我们称他们为“未决定选民”。未决定选民会将票投给编号最小的候选人。

获得最多票数的候选人将赢得选举，如果有多位候选人获得相同的最高票数，则编号最小的候选人获胜。

你觉得这场选举过于无聊且可预测，因此决定排除一些候选人。如果你不允许编号为$i$的候选人参与选举，那么他的$a_i$位粉丝将变成未决定选民，并将票投给编号最小的候选人。

你好奇地想知道，对于每个$i$从$1$到$n$，为了让编号为$i$的候选人赢得选举，最少需要排除多少位候选人。

## 说明/提示

在第一个测试用例中：

- 如果所有候选人都被允许参与选举，编号为$1$的候选人将获得$3$票（$1$位未决定选民会投票给他），编号为$2$的候选人将获得$0$票，编号为$3$的候选人将获得$3$票。因此，编号为$1$的候选人获胜（他与编号为$3$的候选人获得相同的票数，但他的编号更小），所以他的答案是$0$。
- 如果编号为$1$的候选人被排除，他的$2$位粉丝将变成未决定选民。然后，编号为$2$的候选人将获得$3$票（$3$位未决定选民会投票给他），编号为$3$的候选人将获得$3$票。因此，编号为$2$的候选人获胜（他与编号为$3$的候选人获得相同的票数，但他的编号更小），所以他的答案是$1$。
- 如果编号为$1$和$2$的候选人都被排除，编号为$3$的候选人将获胜，所以他的答案是$2$。

在第二个测试用例中，如果编号为$2$的候选人被排除，编号为$1$的候选人将获胜。

## 样例 #1

### 输入

```
5
3 1
2 0 3
2 3
0 10
5 3
5 4 3 2 1
4 5
3 10 7 1
6 0
2 2 2 3 3 3```

### 输出

```
0 1 2
1 0
0 1 2 3 4
1 0 2 3
1 1 2 0 4 5```

### 题解分析与结论

该题的核心在于如何通过排除候选人来使得特定候选人获得最多的票数。大多数题解都采用了类似的前缀和与后缀最大值的方法来计算每个候选人需要排除的最少人数。以下是对各题解的要点提炼和难点对比：

1. **前缀和与后缀最大值**：几乎所有题解都使用了前缀和和后缀最大值的技巧来计算每个候选人的票数。这种方法的时间复杂度为$O(n)$，效率较高。
2. **分类讨论**：部分题解对候选人的情况进行分类讨论，特别是当候选人本身已经是最大值时，直接输出0；否则，需要排除前面的所有候选人，并进一步判断是否需要排除后面的最大值。
3. **贪心策略**：一些题解采用了贪心策略，优先排除后面的最大值，以确保特定候选人获得最多的票数。

### 精选题解

#### 题解1：作者：hh弟中弟 (赞：5)
**星级：5**
**关键亮点**：思路清晰，代码简洁，使用了前缀和和后缀最大值的技巧，时间复杂度为$O(n)$。
**代码核心**：
```cpp
for(int i=1;i<=n;++i){
    if(a[i]==max[1]&&st<max[1]){std::cout<<0<<' ';}
    else{
        int ans=i-1;
        if(sum[i]<max[i+1]){ans++;}
        std::cout<<ans<<' ';
    }
    st=std::max(st,a[i]);
}
```
**核心思想**：通过前缀和和后缀最大值判断每个候选人是否需要排除后面的最大值。

#### 题解2：作者：szh_AK_all (赞：4)
**星级：4**
**关键亮点**：详细分析了候选人的情况，分类讨论清晰，代码可读性强。
**代码核心**：
```cpp
for(int i=1;i<=n;i++) {
    if(i == maxn) cout << 0;
    else if(a[i] + qian >= hou[i + 1]) cout << i - 1;
    else cout << i;
    qian += a[i];
    cout << " ";
}
```
**核心思想**：通过前缀和和后缀最大值判断每个候选人是否需要排除后面的最大值。

#### 题解3：作者：NATO (赞：3)
**星级：4**
**关键亮点**：强调了贪心策略，优先排除后面的最大值，确保特定候选人获得最多的票数。
**代码核心**：
```cpp
for(int i=1;i<=n;++i) {
    if(a[i] == hou[1]) {
        maxn = i;
        break;
    }
}
```
**核心思想**：通过后缀最大值判断每个候选人是否需要排除后面的最大值。

### 最优关键思路
1. **前缀和与后缀最大值**：通过计算前缀和和后缀最大值，可以快速判断每个候选人是否需要排除后面的最大值。
2. **贪心策略**：优先排除后面的最大值，确保特定候选人获得最多的票数。

### 拓展思路
类似的问题可以通过前缀和、后缀最大值以及贪心策略来解决，特别是在需要快速计算区间和或区间最大值的情况下。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3374 树状数组 1](https://www.luogu.com.cn/problem/P3374)
3. [P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368)

### 个人心得
部分题解中提到，比赛时由于理解题意不清导致浪费时间，强调了仔细阅读题目的重要性。此外，部分题解提到在实现过程中由于细节处理不当导致错误，提醒我们在编写代码时要注意细节。

---
处理用时：57.81秒