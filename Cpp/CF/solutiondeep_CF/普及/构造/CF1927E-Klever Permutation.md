# 题目信息

# Klever Permutation

## 题目描述

You are given two integers $ n $ and $ k $ ( $ k \le n $ ), where $ k $ is even.

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in any order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation (as $ 2 $ appears twice in the array) and $ [0,1,2] $ is also not a permutation (as $ n=3 $ , but $ 3 $ is not present in the array).

Your task is to construct a  $ k $ -level permutation of length $ n $ .

A permutation is called  $ k $ -level if, among all the sums of continuous segments of length $ k $ (of which there are exactly $ n - k + 1 $ ), any two sums differ by no more than $ 1 $ .

More formally, to determine if the permutation $ p $ is  $ k $ -level, first construct an array $ s $ of length $ n - k + 1 $ , where $ s_i=\sum_{j=i}^{i+k-1} p_j $ , i.e., the $ i $ -th element is equal to the sum of $ p_i, p_{i+1}, \dots, p_{i+k-1} $ .

A permutation is called  $ k $ -level if $ \max(s) - \min(s) \le 1 $ .

Find any  $ k $ -level permutation of length $ n $ .

## 说明/提示

In the second test case of the example:

- $ p_1 + p_2 = 3 + 1 = 4 $ ;
- $ p_2 + p_3 = 1 + 2 = 3 $ .

 The maximum among the sums is $ 4 $ , and the minimum is $ 3 $ .

## 样例 #1

### 输入

```
5
2 2
3 2
10 4
13 4
7 4```

### 输出

```
2 1
1 3 2
1 8 4 10 2 7 5 9 3 6
4 10 1 13 5 9 2 12 6 8 3 11 7
1 6 3 7 2 5 4```

# AI分析结果

### 题目内容中文重写
# 巧妙排列

## 题目描述
给定两个整数 $n$ 和 $k$（$k \leq n$），其中 $k$ 为偶数。

长度为 $n$ 的排列是一个由 $1$ 到 $n$ 的 $n$ 个不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是排列（因为 $2$ 在数组中出现了两次），$[0,1,2]$ 也不是排列（因为 $n = 3$，但数组中没有 $3$）。

你的任务是构造一个长度为 $n$ 的 $k$ 级排列。

如果在所有长度为 $k$ 的连续段的和（恰好有 $n - k + 1$ 个）中，任意两个和的差值不超过 $1$，则称该排列为 $k$ 级排列。

更正式地，为了确定排列 $p$ 是否为 $k$ 级排列，首先构造一个长度为 $n - k + 1$ 的数组 $s$，其中 $s_i=\sum_{j=i}^{i+k - 1} p_j$，即第 $i$ 个元素等于 $p_i, p_{i + 1}, \dots, p_{i + k - 1}$ 的和。

如果 $\max(s) - \min(s) \leq 1$，则称该排列为 $k$ 级排列。

找出任意一个长度为 $n$ 的 $k$ 级排列。

## 说明/提示
在示例的第二个测试用例中：
- $p_1 + p_2 = 3 + 1 = 4$；
- $p_2 + p_3 = 1 + 2 = 3$。

这些和中的最大值是 $4$，最小值是 $3$。

## 样例 #1
### 输入
```
5
2 2
3 2
10 4
13 4
7 4
```
### 输出
```
2 1
1 3 2
1 8 4 10 2 7 5 9 3 6
4 10 1 13 5 9 2 12 6 8 3 11 7
1 6 3 7 2 5 4
```

### 综合分析与结论
这些题解的核心思路都是通过分析相邻长度为 $k$ 的连续段和的关系，得出要使任意两个和的差值不超过 $1$，需满足 $|p_i - p_{i + k}| = 1$，且 $p_i - p_{i + k}$ 要交替为 $1$ 和 $-1$。具体构造方法上，大部分题解是按模 $k$ 的余数分类，奇数余数位置正着填数，偶数余数位置反着填数。

### 所选题解
- **作者：2huk（5星）**
    - **关键亮点**：思路清晰，通过详细的公式推导得出构造方法，代码实现简洁，有注释辅助理解。
    - **核心代码**：
```cpp
int a[N];

void solve() {
    int n = read(), k = read();
    int cnt = 0;
    bool flg = false;		// 是否要翻转
    int st = 1;
    while (cnt!= n) {
        while (a[st]) ++ st;
        int now = st;
        vector<int> pos;
        while (now <= n) {
            pos.push_back(now);
            now += k;
        }
        if (flg) reverse(pos.begin(), pos.end());
        for (int &t : pos) a[t] = ++ cnt;
        flg ^= 1;
    }
    wel(a + 1, a + n + 1);
    fup (i, 1, n) a[i] = 0;
    return;
}
```
核心实现思想：通过 `while` 循环不断找到未填数的位置，将间隔为 $k$ 的位置存到 `pos` 数组中，根据 `flg` 决定是否翻转 `pos` 数组，然后依次填入递增的数，最后将 `flg` 取反，保证交替填入。

- **作者：Mr_Vatican（4星）**
    - **关键亮点**：先给出错误尝试，再调整构造方法，思路有对比，容易理解，代码简洁。
    - **核心代码**：
```cpp
void solve()
{
    scanf("%d%d",&n,&k);
    int now=0;
    for(int i=1;i<=k;i++)
    {
        int tmp=n/k*k+i;if(tmp>n) tmp-=k;//这个是从后往前第一个模 k 余 i 的位置
        if(i&1) for(int j=i;j<=n;j+=k) a[j]=++now;
        else for(int j=tmp;j>0;j-=k) a[j]=++now;
    }
    for(int i=1;i<=n;i++) cout << a[i] << " \n"[i==n];
}
```
核心实现思想：遍历 $1$ 到 $k$，对于模 $k$ 余奇数的位置，正着填数；对于模 $k$ 余偶数的位置，从后往前填数。

- **作者：__Dist__（4星）**
    - **关键亮点**：通过样例直观分析相邻区间和的变化规律，得出构造方法，代码逻辑清晰。
    - **核心代码**：
```cpp
void solve() {
    int cnt = 0;
    cin >> n >> k;
    for (int i = 1; i <= k; i++) {
        if(i & 1) {
            int j = i;
            while(j <= n) {
                ans[j] = ++cnt;
                j += k;
            }
        }
        else {
            int j = i;
            int x = cnt;
            while(j <= n) {
                x++;
                j += k;
            }
            int xx = x;
            j = i;
            while(j <= n) {
                ans[j] = x--;
                j += k;
            }
            cnt += xx;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}
```
核心实现思想：遍历 $1$ 到 $k$，对于奇数 $i$，从 $i$ 开始每隔 $k$ 个位置依次填入递增的数；对于偶数 $i$，先计算出最后一个位置应填的数，再从 $i$ 开始每隔 $k$ 个位置依次填入递减的数。

### 最优关键思路或技巧
- **思维方式**：通过分析相邻长度为 $k$ 的连续段和的关系，得出关键条件 $|p_i - p_{i + k}| = 1$，并进一步发现 $p_i - p_{i + k}$ 要交替为 $1$ 和 $-1$，从而找到构造方法。
- **代码实现技巧**：按模 $k$ 的余数分类，奇数余数位置正着填数，偶数余数位置反着填数，实现简单且有效。

### 可拓展之处
同类型题可能会改变条件，如 $k$ 为奇数时的构造，或者对排列有其他额外限制。类似算法套路是通过分析相邻元素或区间的关系，找出规律进行构造。

### 推荐洛谷题目
- P1002 过河卒
- P1216 [USACO1.5] 数字三角形 Number Triangles
- P1048 采药

### 个人心得
部分题解提到先尝试简单的构造方法，发现不满足条件后再调整，如 Mr_Vatican 先写了每次跳着填数的代码，发现样例都过不去，然后调整为对于模 $k$ 余奇数的位置正着填，余偶数的位置反着填。这提示我们在解决构造题时，可以先从简单情况入手，根据反馈调整思路。 

---
处理用时：36.76秒