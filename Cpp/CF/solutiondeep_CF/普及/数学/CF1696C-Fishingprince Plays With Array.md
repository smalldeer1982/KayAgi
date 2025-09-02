# 题目信息

# Fishingprince Plays With Array

## 题目描述

Fishingprince is playing with an array $ [a_1,a_2,\dots,a_n] $ . He also has a magic number $ m $ .

He can do the following two operations on it:

- Select $ 1\le i\le n $ such that $ a_i $ is divisible by $ m $ (that is, there exists an integer $ t $ such that $ m \cdot t = a_i $ ). Replace $ a_i $ with  $ m $ copies of $ \frac{a_i}{m} $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[2,3] $ and $ i=1 $ , $ a $ changes into $ [1,1,3] $ .
- Select $ 1\le i\le n-m+1 $ such that $ a_i=a_{i+1}=\dots=a_{i+m-1} $ . Replace these $ m $ elements with a single $ m \cdot a_i $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[3,2,2,3] $ and $ i=2 $ , $ a $ changes into $ [3,4,3] $ .

Note that the array length might change during the process. The value of $ n $ above is defined as the current length of the array (might differ from the $ n $ in the input).

Fishingprince has another array $ [b_1,b_2,\dots,b_k] $ . Please determine if he can turn $ a $ into $ b $ using any number (possibly zero) of operations.

## 说明/提示

In the first test case of the sample, we can do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ .

In the second testcase of the sample, we can:

- do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ .
- do the second operation with $ i=4 $ : $ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ .
- do the first operation with $ i=3 $ : $ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ .
- do the second operation with $ i=3 $ : $ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ .

## 样例 #1

### 输入

```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56```

### 输出

```
Yes
Yes
No
Yes
No```

# AI分析结果

### 题目内容重写

Fishingprince 正在玩一个数组 $ [a_1,a_2,\dots,a_n] $。他还有一个魔法数字 $ m $。

他可以对数组进行以下两种操作：

1. 选择一个 $ 1\le i\le n $，使得 $ a_i $ 能被 $ m $ 整除（即存在整数 $ t $ 使得 $ m \cdot t = a_i $）。将 $ a_i $ 替换为 $ m $ 个 $ \frac{a_i}{m} $。其他元素的顺序不变。例如，当 $ m=2 $ 且 $ a=[2,3] $ 且 $ i=1 $ 时，$ a $ 变为 $ [1,1,3] $。
2. 选择一个 $ 1\le i\le n-m+1 $，使得 $ a_i=a_{i+1}=\dots=a_{i+m-1} $。将这 $ m $ 个元素替换为一个 $ m \cdot a_i $。其他元素的顺序不变。例如，当 $ m=2 $ 且 $ a=[3,2,2,3] $ 且 $ i=2 $ 时，$ a $ 变为 $ [3,4,3] $。

注意，数组的长度可能在操作过程中发生变化。$ n $ 的值定义为数组的当前长度（可能与输入的 $ n $ 不同）。

Fishingprince 有另一个数组 $ [b_1,b_2,\dots,b_k] $。请判断他是否可以通过任意次数（可能为零次）的操作将 $ a $ 变成 $ b $。

### 题解分析与结论

#### 综合分析与结论

本题的核心在于判断两个数组 $ a $ 和 $ b $ 是否可以通过一系列拆分和合并操作相互转换。所有题解都抓住了两个操作是互逆的这一关键点，并提出了将两个数组尽可能拆分成最简形式后进行比较的思路。这种思路不仅简化了问题，还避免了直接处理大规模数据带来的时间和空间复杂度问题。

#### 精选题解

1. **作者：lenlen (★★★★★)**
   - **关键亮点**：通过双端队列逐步拆分和比较数组，避免了直接存储大规模数据的问题。代码清晰且高效。
   - **代码核心思想**：将数组 $ a $ 拆分成最简形式并存入双端队列，然后逐步拆分数组 $ b $ 并与队列中的元素进行比较。
   - **核心代码**：
     ```cpp
     deque <hl> q;
     for(int i=1;i<=n;i++) {
         int k=1;
         while(a[i]%m==0) a[i]/=m,k*=m;
         q.push_back((hl){a[i],k});
     }
     for(int i=1;i<=nn&&!flag;i++) {
         int k=1;
         while(b[i]%m==0) b[i]/=m,k*=m;
         while(k) {
             if(q.empty()) { flag=1; break; }
             tmp=q.front(); q.pop_front();
             if(tmp.d!=b[i]) { flag=1; break; }
             if(tmp.sum<=k) k-=tmp.sum;
             else { q.push_front((hl){tmp.d,tmp.sum-k}); k=0; }
         }
     }
     ```

2. **作者：Avocadooo (★★★★☆)**
   - **关键亮点**：通过结构体存储拆分后的数组，简化了比较过程。思路清晰，代码可读性强。
   - **代码核心思想**：将数组 $ a $ 和 $ b $ 拆分成最简形式，并用结构体存储每个数字及其重复次数，最后比较两个结构体数组是否相同。
   - **核心代码**：
     ```cpp
     struct NUM { int rt; ll cnt; }a[N],b[N];
     for(int i=1,x,y;i<=n;i++) {
         y=1;
         while(x%m==0) x/=m,y*=m;
         if(!cnt || x!=a[cnt].rt) a[++cnt].rt=x,a[cnt].cnt=y;
         else if(x==a[cnt].rt) a[cnt].cnt+=y;
     }
     ```

3. **作者：JS_TZ_ZHR (★★★★☆)**
   - **关键亮点**：使用栈来存储拆分后的数组，代码简洁且高效。
   - **代码核心思想**：将数组 $ a $ 拆分成最简形式并存入栈中，然后逐步拆分数组 $ b $ 并与栈中的元素进行比较。
   - **核心代码**：
     ```cpp
     stack<node>s;
     for(int i=1;i<=n;i++) {
         int tmp=1;
         while(a[i]%m==0) a[i]/=m,tmp*=m;
         s.push((node){a[i],tmp});
     }
     for(int i=k;i>=1;i--) {
         int tmp=1;
         while(b[i]%m==0) b[i]/=m,tmp*=m;
         while(tmp) {
             if(s.empty()||b[i]!=s.top().num) { flag=0; break; }
             if(tmp>=s.top().sum) tmp-=s.top().sum,s.pop();
             else { s.top().sum-=tmp; tmp=0; }
         }
     }
     ```

### 最优关键思路与技巧

- **互逆操作**：拆分和合并操作是互逆的，因此可以将问题转化为将两个数组拆分成最简形式后进行比较。
- **数据结构选择**：使用双端队列、栈或结构体来存储拆分后的数组，避免直接处理大规模数据。
- **逐步比较**：逐步拆分数组 $ b $ 并与存储的拆分结果进行比较，确保每一步都符合要求。

### 拓展思路

- **类似问题**：可以扩展到其他需要判断两个数组是否可以通过某种操作相互转换的问题，如字符串的编辑距离问题。
- **优化技巧**：在处理大规模数据时，可以通过压缩存储或分块处理来降低时间和空间复杂度。

### 推荐题目

1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
3. [P3384 【模板】树链剖分](https://www.luogu.com.cn/problem/P3384)

---
处理用时：45.80秒