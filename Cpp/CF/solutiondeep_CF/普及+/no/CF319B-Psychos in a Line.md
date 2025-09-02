# 题目信息

# Psychos in a Line

## 题目描述

There are $ n $ psychos standing in a line. Each psycho is assigned a unique integer from $ 1 $ to $ n $ . At each step every psycho who has an id greater than the psycho to his right (if exists) kills his right neighbor in the line. Note that a psycho might kill and get killed at the same step.

You're given the initial arrangement of the psychos in the line. Calculate how many steps are needed to the moment of time such, that nobody kills his neighbor after that moment. Look notes to understand the statement more precise.

## 说明/提示

In the first sample line of the psychos transforms as follows: \[10 9 7 8 6 5 3 4 2 1\] $ → $ \[10 8 4\] $ → $ \[10\]. So, there are two steps.

## 样例 #1

### 输入

```
10
10 9 7 8 6 5 3 4 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 排成一排的疯子

## 题目描述
有 $n$ 个疯子站成一排。每个疯子被分配一个从 $1$ 到 $n$ 的唯一整数。在每一步中，每个编号大于其右边疯子（如果存在）的疯子会杀死他右边的邻居。注意，一个疯子可能在同一时刻既杀人又被杀。

给定疯子在一排中的初始排列。计算到这样一个时刻需要多少步：在该时刻之后，没有人再杀死他的邻居。查看注释以更准确地理解该陈述。

## 说明/提示
在第一个示例中，疯子的排列如下变换： \[10 9 7 8 6 5 3 4 2 1\] $ → $ \[10 8 4\] $ → $ \[10\]。所以，需要两步。

## 样例 #1
### 输入
```
10
10 9 7 8 6 5 3 4 2 1
```
### 输出
```
2
```

## 样例 #2
### 输入
```
6
1 2 3 4 5 6
```
### 输出
```
0
```

### 算法分类
单调栈（属于数据结构相关，在此题用于优化动态规划）

### 题解综合分析与结论
这些题解都围绕使用单调栈解决该问题，核心思路是利用单调栈维护序列的单调性，从而优化计算每个疯子杀人轮数的过程。不同题解在具体实现细节和解释方式上有所差异。

### 所选的题解
- **作者：xxbzzyw (5星)**
    - **关键亮点**：思路清晰，通过将数列切成单调递减区间，分析不同区间长度关系得出共性，进而利用单调栈倒着跑，准确计算每个疯子杀人轮数。代码实现简洁明了，有详细的读入优化。
    - **个人心得**：最开始尝试用dp思路，想将局部量转移至整体，后采用单调栈解决问题。
    ```cpp
    int main(void){
        int n=read();
        int l=0; 
        int ans=0;
        for(int i=1;i<=n;i++)a[i]=read();
        for(int i=n;i;i--){
            int t=0;
            while(l&&a[s[l]]<a[i]){
                t++;
                f[i]=t=max(t,f[s[l]]);
                l--;
            }
            s[++l]=i;
            ans=max(ans,t);
        }
        cout<<ans;
        return 0;
    }
    ```
    - **核心实现思想**：从后往前遍历数组，利用单调栈维护递减序列，每次弹出栈顶元素时更新当前元素杀人轮数，取所有元素杀人轮数的最大值作为答案。
- **作者：ZHR100102 (4星)**
    - **关键亮点**：先通过观察得出一个疯子会杀到右边第一个比他大的疯子处，基于此定义状态转移方程，再利用单调栈优化动态规划，时间复杂度达到 $O(n)$，代码简洁高效。
    - **个人心得**：理解“一个人先钦定被左边第一个比他大的人杀，之后再动态调整，不影响最终答案的类似反悔贪心的思想”是解题关键。
    ```cpp
    int main()
    {
        ios::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=n;i>=1;i--)
        {
            int res=0;
            while(tp&&a[s[tp]]<a[i])res=max(res+1,dp[s[tp--]]);
            s[++tp]=i;
            dp[i]=res;
            ans=max(dp[i],ans);
        }
        cout<<ans;
        return 0;
    }
    ```
    - **核心实现思想**：从右往左遍历，用单调栈维护右边最大值，在元素入栈时，从弹出元素转移状态，计算每个疯子杀人轮数，最终答案为所有轮数的最大值。
- **作者：xing_yue (4星)**
    - **关键亮点**：解题思路表述清晰，通过设立单调栈存储未死亡值，利用数组 $f$ 存储到每个值“死完”所需步数，每次新元素比栈顶大时继承之前杀的结果并更新答案。
    ```cpp
    int main() {
        ios::sync_with_stdio(false);
        cin.tie(0);
        cout.tie(0);
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            int maxn = 0; 
            while (!st.empty() && st.top() < a[i]) { 
                maxn = max(maxn, f[st.top()]); 
                st.pop();
            }
            if (!st.empty()) { 
                f[a[i]] = maxn + 1; 
            }
            st.push(a[i]); 
            ans = max(ans, f[a[i]]); 
        }
        cout << ans;
        return	 0;
    }
    ```
    - **核心实现思想**：遍历数组，新元素比栈顶大时更新当前元素“死完”步数，最终答案为数组 $f$ 中的最大值。

### 最优关键思路或技巧
利用单调栈维护序列单调性，优化动态规划过程。从右往左遍历序列，在单调栈弹出元素时，根据弹出元素的杀人轮数更新当前元素的杀人轮数，从而高效计算出最终答案。

### 同类型题或类似算法套路
此类题目通常涉及元素间的比较和动态变化，可通过分析元素间关系，利用单调栈优化动态规划或模拟过程。例如，对于一些具有前后依赖关系且需要维护某种单调性的序列问题，可考虑使用单调栈解决。

### 推荐洛谷题目
- [P5788 【模板】单调栈](https://www.luogu.com.cn/problem/P5788)：基础单调栈模板题，用于熟悉单调栈的基本应用。
- [P2866 [USACO06NOV]Bad Hair Day S](https://www.luogu.com.cn/problem/P2866)：与本题类似，通过单调栈解决元素间比较和计数问题。
- [P4185 [USACO18JAN]MooTube G](https://www.luogu.com.cn/problem/P4185)：需要利用单调栈优化查询操作，进一步加深对单调栈应用的理解。

---
处理用时：64.97秒