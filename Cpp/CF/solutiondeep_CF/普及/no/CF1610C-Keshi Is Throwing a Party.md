# 题目信息

# Keshi Is Throwing a Party

## 题目描述

Keshi is throwing a party and he wants everybody in the party to be happy.

He has $ n $ friends. His $ i $ -th friend has $ i $ dollars.

If you invite the $ i $ -th friend to the party, he will be happy only if at most $ a_i $ people in the party are strictly richer than him and at most $ b_i $ people are strictly poorer than him.

Keshi wants to invite as many people as possible. Find the maximum number of people he can invite to the party so that every invited person would be happy.

## 说明/提示

In the first test case, he invites the first and the second person. If he invites all of them, the third person won't be happy because there will be more than $ 1 $ person poorer than him.

## 样例 #1

### 输入

```
3
3
1 2
2 1
1 1
2
0 0
0 1
2
1 0
0 1```

### 输出

```
2
1
2```

# AI分析结果

### 题目内容重写

Keshi 正在举办一个派对，他希望派对上的每个人都能开心。

他有 $n$ 个朋友。他的第 $i$ 个朋友有 $i$ 美元。

如果你邀请第 $i$ 个朋友参加派对，他只有在派对中严格比他富有的人不超过 $a_i$ 个，且严格比他贫穷的人不超过 $b_i$ 个时才会开心。

Keshi 希望邀请尽可能多的人。找出他可以邀请到派对的最大人数，使得每个被邀请的人都开心。

### 说明/提示

在第一个测试用例中，他邀请了第一个人和第二个人。如果他邀请所有人，第三个人不会开心，因为比他贫穷的人会超过 $1$ 个。

### 样例 #1

#### 输入

```
3
3
1 2
2 1
1 1
2
0 0
0 1
2
1 0
0 1
```

#### 输出

```
2
1
2
```

### 算法分类
二分

### 题解分析与结论

所有题解都采用了二分法来解决这个问题，核心思路是通过二分搜索确定最大可以邀请的人数，并通过贪心策略来判断某个特定人数是否可行。题解的主要区别在于判断函数的具体实现和代码风格。

### 精选题解

#### 题解1：作者：huyangmu (赞：4)
- **星级**：5星
- **关键亮点**：代码简洁明了，判断函数逻辑清晰，二分搜索的实现标准且高效。
- **核心代码**：
```cpp
bool check (int x){
    int cnt=0;
    for (int i=1;i<=n;++i){
        if (a[i]<x-cnt-1||b[i]<cnt) continue;
        ++cnt;
    }
    return cnt>=x;
}
```
- **实现思想**：通过遍历所有朋友，统计满足条件的人数，判断是否达到目标人数。

#### 题解2：作者：Terraria (赞：3)
- **星级**：4星
- **关键亮点**：详细解释了二分法的应用和贪心策略的合理性，代码结构清晰。
- **核心代码**：
```cpp
bool check(int sum){
    int cnt=0;
    for(int i=1;i<=n;i++){
        if(b[i]>=cnt&&a[i]>=sum-cnt-1) cnt++;
    }
    return (cnt>=sum);
}
```
- **实现思想**：通过遍历所有朋友，统计满足条件的人数，判断是否达到目标人数。

#### 题解3：作者：kevin1616 (赞：2)
- **星级**：4星
- **关键亮点**：代码简洁，判断函数逻辑清晰，二分搜索的实现标准且高效。
- **核心代码**：
```cpp
bool check(int x){
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        if(a[i] >= x - cnt - 1 && b[i] >= cnt) cnt++;
    }
    return (cnt >= x);
}
```
- **实现思想**：通过遍历所有朋友，统计满足条件的人数，判断是否达到目标人数。

### 最优关键思路或技巧
1. **二分法**：通过二分搜索确定最大可以邀请的人数，利用单调性减少搜索范围。
2. **贪心策略**：在判断函数中，通过贪心策略选择满足条件的朋友，确保每次选择都是最优的。

### 可拓展之处
类似的问题可以通过二分法和贪心策略结合来解决，特别是在需要确定最大或最小值的场景中。例如，确定最大满足某种条件的子集大小。

### 推荐题目
1. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
3. [P1316 丢瓶盖](https://www.luogu.com.cn/problem/P1316)

### 个人心得摘录
- **huyangmu**：通过二分法可以快速确定最大人数，贪心策略确保每次选择都是最优的。
- **Terraria**：详细解释了二分法的应用和贪心策略的合理性，代码结构清晰。
- **kevin1616**：代码简洁，判断函数逻辑清晰，二分搜索的实现标准且高效。

---
处理用时：29.52秒