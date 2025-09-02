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

### 题目内容翻译

# 选举

## 题目描述

在Berland地区正在进行选举。共有 $n$ 名候选人参与选举，编号从 $1$ 到 $n$。第 $i$ 名候选人有 $a_i$ 名粉丝会为他投票。此外，还有 $c$ 名未决定投票对象的选民，我们称他们为“未决定者”。未决定者会将票投给编号最小的候选人。

获得最多票数的候选人将赢得选举，如果有多名候选人获得相同的最高票数，则编号最小的候选人获胜。

你觉得这次选举过于无聊且可预测，因此决定排除一些候选人。如果你不允许编号为 $i$ 的候选人参与选举，那么他的 $a_i$ 名粉丝将变成未决定者，并将票投给编号最小的候选人。

你好奇地想知道，对于每个 $i$ 从 $1$ 到 $n$，最少需要排除多少名候选人才能使编号为 $i$ 的候选人赢得选举。

## 说明/提示

在第一个测试用例中：

- 如果所有候选人都被允许参与，编号为 $1$ 的候选人将获得 $3$ 票（$1$ 名未决定者会投票给他），编号为 $2$ 的候选人将获得 $0$ 票，编号为 $3$ 的候选人将获得 $3$ 票。因此，编号为 $1$ 的候选人获胜（他与编号为 $3$ 的候选人获得相同的票数，但他的编号更小），所以他的答案是 $0$。
- 如果编号为 $1$ 的候选人不被允许，他的 $2$ 名粉丝将变成未决定者。然后编号为 $2$ 的候选人将获得 $3$ 票（$3$ 名未决定者会投票给他），编号为 $3$ 的候选人将获得 $3$ 票。因此，编号为 $2$ 的候选人获胜（他与编号为 $3$ 的候选人获得相同的票数，但他的编号更小），所以他的答案是 $1$。
- 如果编号为 $1$ 和 $2$ 的候选人都不被允许，编号为 $3$ 的候选人将获胜，所以他的答案是 $2$。

在第二个测试用例中，如果编号为 $2$ 的候选人不被允许参与，编号为 $1$ 的候选人将获胜。

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

本题的核心在于如何通过排除某些候选人，使得目标候选人能够获得最多的票数。所有题解都基于以下关键思路：

1. **前缀和与后缀最大值**：大多数题解都使用了前缀和和后缀最大值的技巧来快速计算每个候选人在排除某些候选人后的票数。
2. **贪心策略**：通过优先排除前面的候选人，使得目标候选人能够获得更多的票数。
3. **分类讨论**：根据目标候选人是否已经是最大票数获得者，分别讨论需要排除的候选人数量。

### 评分较高的题解

#### 1. 作者：hh弟中弟 (赞：5)  
**星级：5星**  
**关键亮点**：  
- 使用前缀和和后缀最大值，时间复杂度为 $\mathcal{O}(n)$，代码简洁高效。
- 清晰地将问题分为两种情况：目标候选人是否已经是最大票数获得者。
- 代码可读性强，逻辑清晰。

**核心代码**：
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

#### 2. 作者：szh_AK_all (赞：4)  
**星级：4星**  
**关键亮点**：  
- 通过前缀和和后缀最大值快速计算每个候选人的票数。
- 逻辑清晰，代码简洁，易于理解。
- 详细解释了为什么需要排除前面的候选人。

**核心代码**：
```cpp
for(int i=1;i<=n;i++) {
    if(i == maxn)
        cout << 0;
    else if(a[i] + qian >= hou[i + 1])
        cout << i - 1;
    else
        cout << i;
    qian += a[i];
    cout << " ";
}
```

#### 3. 作者：NATO (赞：3)  
**星级：4星**  
**关键亮点**：  
- 强调了未决定者投票给编号最小的候选人的重要性。
- 通过贪心策略，优先排除前面的候选人，使得目标候选人能够获得更多的票数。
- 代码逻辑清晰，易于理解。

**核心代码**：
```cpp
for(int i=1;i<=n;++i) {
    if(i == maxn)
        cout << 0;
    else if(a[i] + qian >= hou[i + 1])
        cout << i - 1;
    else
        cout << i;
    qian += a[i];
    cout << " ";
}
```

### 最优关键思路与技巧

1. **前缀和与后缀最大值**：通过预处理前缀和和后缀最大值，可以快速计算每个候选人在排除某些候选人后的票数，时间复杂度为 $\mathcal{O}(n)$。
2. **贪心策略**：优先排除前面的候选人，使得目标候选人能够获得更多的票数。
3. **分类讨论**：根据目标候选人是否已经是最大票数获得者，分别讨论需要排除的候选人数量。

### 可拓展之处

本题的贪心策略和前缀和技巧可以应用于类似的选举问题或资源分配问题。例如，在资源分配中，如何通过调整资源分配使得某个目标获得最大收益。

### 推荐题目

1. [P1880 [NOI1995]石子合并](https://www.luogu.com.cn/problem/P1880)  
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)  
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：44.13秒