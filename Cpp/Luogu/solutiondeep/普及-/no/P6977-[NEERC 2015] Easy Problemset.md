# 题目信息

# [NEERC 2015] Easy Problemset

## 题目描述



Perhaps one of the hardest problems of any ACM ICPC contest is to create a problemset with a reasonable number of easy problems. On Not Easy European Regional Contest this problem is solved as follows.

There are $n$ jury members (judges). They are numbered from $1$ to $n$ . Judge number $i$ had prepared $p_{i}$ easy problems before the jury meeting. Each of these problems has a hardness between $0$ and $49$ (the higher the harder). Each judge also knows a very large (say infinite) number of hard problems (their hardness is $50$) . Judges need to select $k$ problems to be used on the contest during this meeting.

They start to propose problems in the ascending order of judges numbers. The first judge takes the first problem from his list of remaining easy problems (or a hard problem, if he has already proposed all his easy problems) and proposes it. The proposed problem is selected for the contest if its hardness is greater than or equal to the total hardness of the problems selected so far, otherwise it is considered too easy. Then the second judge does the same etc. ; after the n-th judge, the first one proposes his next problem, and so on. This procedure is stopped immediately when $k$ problems are selected.

If all judges have proposed all their easy problems, but they still have selected less than $k$ problems, then they take some hard problems to complete the problemset regardless of the total hardness.

Your task is to calculate the total hardness of the problemset created by the judges.



## 说明/提示

Time limit: 1 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
3 8
5 0 3 12 1 10
4 1 1 23 20
4 1 5 17 49
```

### 输出

```
94
```

## 样例 #2

### 输入

```
3 10
2 1 3
1 1
2 2 5
```

### 输出

```
354
```

# AI分析结果

### 算法分类
模拟

### 综合分析与结论
本题的核心逻辑是模拟评委们轮流选择问题的过程，直到选出k个问题为止。所有题解都采用了模拟的方法，主要区别在于数据结构的选取和代码的实现细节。大部分题解使用了队列或数组来存储每个评委的问题列表，并通过循环模拟选择过程。题解的难点在于如何高效地模拟选择过程，并正确处理评委的问题列表为空的情况。

### 所选题解
1. **作者：MoonCake2011 (赞：7)**
   - **星级：4星**
   - **关键亮点：**
     - 使用`queue`数据结构存储每个评委的问题列表，简化了问题的出队操作。
     - 代码简洁明了，逻辑清晰，易于理解。
     - 通过`while(k)`循环和`for`循环实现了评委轮流选择问题的过程。
   - **核心代码：**
     ```cpp
     while(k){//选k道题 
         for(int i=1;i<=n;i++){
             if(k==0) break;
             if(q[i].empty()) sum+=50,k--;
             else if(q[i].front()<sum) q[i].pop();
             else sum+=q[i].front(),q[i].pop(),k--;
         }
     }
     ```

2. **作者：Daben1 (赞：1)**
   - **星级：4星**
   - **关键亮点：**
     - 使用`vector`存储每个评委的问题列表，并通过`pos`数组记录每个评委当前处理到的问题位置。
     - 代码结构清晰，逻辑严谨，易于扩展。
     - 通过`while(k > 0)`循环和`for`循环实现了评委轮流选择问题的过程。
   - **核心代码：**
     ```cpp
     while(k > 0){
         for(int i=1; i<=n; i++){
             if(pos[i] < cnt[i]){
                 if(vec[i][pos[i]] >= ans){
                     ans += vec[i][pos[i]];
                     pos[i]++;
                     k--;
                 }
                 else{
                     pos[i]++;
                 }
             }
             else{
                 ans += 50;
                 k--;
             }
             if(k == 0)break;
         }
     }
     ```

3. **作者：yeshubo_qwq (赞：0)**
   - **星级：4星**
   - **关键亮点：**
     - 使用`queue`数据结构存储每个评委的问题列表，简化了问题的出队操作。
     - 代码简洁明了，逻辑清晰，易于理解。
     - 通过`while(1)`循环和`for`循环实现了评委轮流选择问题的过程，并在必要时直接输出结果。
   - **核心代码：**
     ```cpp
     while (1)
         for (i=1;i<=n;i++){
             if (problem[i].empty())
                 return write(ans+m*50),0;
             x=problem[i].front();
             problem[i].pop();
             if (x>=ans){
                 ans+=x;
                 if (--m==0) return write(ans),0;
             }
         }
     ```

### 最优关键思路或技巧
- **数据结构选择：** 使用`queue`或`vector`存储每个评委的问题列表，简化了问题的出队操作。
- **循环控制：** 通过`while`循环和`for`循环实现了评委轮流选择问题的过程，确保在选出k个问题后立即停止。
- **边界处理：** 在处理评委的问题列表为空时，直接选择难度为50的难题，并确保最终选出k个问题。

### 可拓展之处
- **类似算法套路：** 类似的模拟问题可以通过选择合适的数据结构和循环控制来实现，如使用栈、优先队列等。
- **同类型题：** 可以尝试解决其他需要模拟过程的问题，如任务调度、资源分配等。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

---
处理用时：29.92秒