# 题目信息

# [NWRRC 2017] Auxiliary Project

## 题目描述



Anna has just finished her course project. She has a lot of seven-segment LED displays as leftovers and a small power source. Each display consumes power proportionally to the number of lit segments, e.g . $‘9'$ consumes twice more power than $‘7'.$

![](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/15131/1.png)

Anna wonders what is the maximum possible sum of digits she is able to achieve, if her power source is able to light $n$ segments, and she wants to light exactly $n$ segments.



## 说明/提示

Time limit: 3 s, Memory limit: 512 MB. 



## 样例 #1

### 输入

```
4
```

### 输出

```
4
```

## 样例 #2

### 输入

```
7
```

### 输出

```
11
```

## 样例 #3

### 输入

```
6
```

### 输出

```
14
```

# AI分析结果

### 算法分类
贪心

### 综合分析与结论
本题的核心是通过贪心策略最大化数字和，主要思路是尽可能多地使用性价比最高的数字“7”（每段灯管贡献的值为7/3），然后根据剩余灯管数进行调整。大多数题解都采用了这一思路，通过讨论n对3的余数来决定如何调整结果。动态规划的题解虽然也能解决问题，但复杂度较高，不如贪心简洁高效。

### 所选题解
1. **作者：Karry5307 (5星)**
   - **关键亮点**：思路清晰，代码简洁，直接通过n对3的余数进行分类讨论，逻辑严谨。
   - **代码核心**：
     ```cpp
     printf("%d\n",n/3*7+(n%3==2?1:n%3==1?-3:0));
     ```
   - **个人心得**：无

2. **作者：fkcufk (4星)**
   - **关键亮点**：代码简洁，逻辑清晰，直接根据n对3的余数输出结果。
   - **代码核心**：
     ```cpp
     if(n%3==0) cout<<n/3*7;
     else if(n%3==1) cout<<n/3*7-3;
     else cout<<n/3*7+1;
     ```
   - **个人心得**：无

3. **作者：Eason_AC (4星)**
   - **关键亮点**：详细解释了贪心策略的合理性，并通过表格展示了各数字的性价比，增强了理解。
   - **代码核心**：
     ```cpp
     if(n == 1) printf("%d", ans - 3);
     else if(n == 2) printf("%d", ans + 1);
     else printf("%d", ans);
     ```
   - **个人心得**：无

### 最优关键思路或技巧
- **贪心策略**：优先使用性价比最高的数字“7”，然后根据剩余灯管数进行调整。
- **数学优化**：通过n对3的余数直接计算结果，避免了复杂的动态规划。

### 可拓展之处
- **类似问题**：在其他需要最大化某种资源的场景中，贪心策略常常是首选，尤其是当资源可以分割且存在明显的性价比差异时。
- **算法套路**：贪心算法在资源分配、调度问题中广泛应用，如背包问题、任务调度等。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048) - 经典的背包问题，考察贪心与动态规划。
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略在合并问题中的应用。
3. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223) - 贪心算法在调度问题中的应用。

---
处理用时：19.60秒