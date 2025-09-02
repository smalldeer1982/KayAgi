# 题目信息

# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1
```

### 输出

```
9
```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

龙象征着智慧、力量和财富。在农历新年，人们用竹条和布料制作龙模型，用杆子举起，并高低挥舞，模仿飞龙的动作。

表演者将杆子举低时用 $1$ 表示，举高时用 $2$ 表示。因此，表演者的队列可以用一个序列 $a_{1},a_{2},...,a_{n}$ 来表示。

小 Tommy 也在其中。他想选择一个区间 $[l,r]$（$1<=l<=r<=n$），然后将 $a_{l},a_{l+1},...,a_{r}$ 反转，使得新序列的最长非递减子序列的长度最大。

非递减子序列是指一组索引 $p_{1},p_{2},...,p_{k}$，满足 $p_{1}<p_{2}<...<p_{k}$ 且 $a_{p1}<=a_{p2}<=...<=a_{pk}$。子序列的长度为 $k$。

#### 说明/提示

在第一个例子中，反转 $[2,3]$ 后，数组变为 $[1,1,2,2]$，此时最长非递减子序列的长度为 $4$。

在第二个例子中，反转 $[3,7]$ 后，数组变为 $[1,1,1,1,2,2,2,2,2,1]$，此时最长非递减子序列的长度为 $9$。

#### 样例 #1

##### 输入

```
4
1 2 1 2
```

##### 输出

```
4
```

#### 样例 #2

##### 输入

```
10
1 1 2 2 2 1 1 2 2 1
```

##### 输出

```
9
```

---

### 题解分析与结论

#### 综合分析

本题的核心是通过反转一个区间，使得序列的最长非递减子序列的长度最大化。由于序列中只有 $1$ 和 $2$ 两种元素，因此最终的最长非递减子序列可以分解为四段：$[1,1,...][2,2,...][1,1,...][2,2,...]$，其中每一段都可以为空。通过反转第二段和第三段，可以得到一个非递减序列。

大多数题解采用了动态规划（DP）的思路，通过维护四个状态来表示每一段的最大长度，最终通过状态转移方程求解。部分题解还使用了线段树等数据结构来优化查询，但核心思路仍然是基于四段式的分解。

#### 最优关键思路

1. **四段式分解**：将最终的非递减序列分解为四段，分别表示 $1$ 和 $2$ 的连续序列，通过反转第二段和第三段来得到最长非递减子序列。
2. **动态规划**：通过定义状态 $f[i][j]$ 表示前 $i$ 个数中前 $j$ 段的最大长度，利用状态转移方程逐步求解。
3. **状态压缩**：由于状态转移只依赖于前一个状态，因此可以压缩空间复杂度，仅使用一维数组来维护当前状态。

#### 可拓展之处

- **类似问题**：对于其他类型的序列问题，如最长上升子序列、最长公共子序列等，可以通过类似的分解和动态规划思路来解决。
- **数据结构优化**：对于更大规模的数据，可以使用线段树、树状数组等数据结构来优化查询和更新操作。

#### 推荐题目

1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020) - 考察最长不上升子序列和贪心算法。
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091) - 考察双向最长上升子序列。
3. [P1439 最长公共子序列](https://www.luogu.com.cn/problem/P1439) - 考察最长公共子序列的优化解法。

---

### 精选题解

#### 题解1：浅色调（解法二）

**评分：5星**

**关键亮点**：
- 使用了动态规划，状态定义清晰，转移方程简洁。
- 通过状态压缩，优化了空间复杂度。
- 代码简洁，易于理解。

**核心代码**：
```cpp
int n,x,f[5];

int main(){
    scanf("%d",&n);
    For(i,1,n) 
        scanf("%d",&x),
        f[1]+=(x==1),
        f[2]=max(f[1],f[2]+(x==2)),
        f[3]=max(f[2],f[3]+(x==1)),
        f[4]=max(f[3],f[4]+(x==2));
    cout<<f[4];
    return 0;
}
```

**核心思想**：通过四个状态 $f[1]$ 到 $f[4]$ 分别表示前 $i$ 个数中前四段的最大长度，逐步更新状态，最终输出 $f[4]$。

#### 题解2：_sh1kong_

**评分：4星**

**关键亮点**：
- 状态转移方程清晰，代码简洁。
- 通过状态压缩，优化了空间复杂度。

**核心代码**：
```cpp
int n;
int d[N], f[5];

signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> d[i];
	for (int i = 1; i <= n; i ++ )
	{
		f[1] += (d[i] == 1);
		f[2] = max(f[1], f[2] + (d[i] == 2));
		f[3] = max(f[2], f[3] + (d[i] == 1));
		f[4] = max(f[3], f[4] + (d[i] == 2));
	}
	cout << f[4];
}
```

**核心思想**：通过四个状态 $f[1]$ 到 $f[4]$ 分别表示前 $i$ 个数中前四段的最大长度，逐步更新状态，最终输出 $f[4]$。

#### 题解3：Ba_creeper

**评分：4星**

**关键亮点**：
- 状态转移方程清晰，代码简洁。
- 通过状态压缩，优化了空间复杂度。

**核心代码**：
```cpp
ll n,ans,f[12];
int main()
{
    n=read();
    for (ll i = 1; i <= n; i++)
    {
        ll tmp;
        scanf("%lld", &tmp);
        f[1] += (tmp == 1);
        f[2] = max(f[1], f[2] + (tmp == 2));
        f[3] = max(f[2], f[3] + (tmp == 1));
        f[4] = max(f[3], f[4] + (tmp == 2));
    }
    printf("%lld\n",f[4]);
    return 0;
}
```

**核心思想**：通过四个状态 $f[1]$ 到 $f[4]$ 分别表示前 $i$ 个数中前四段的最大长度，逐步更新状态，最终输出 $f[4]$。

---

### 个人心得总结

- **调试经历**：在实现动态规划时，状态转移方程的推导是关键，尤其是在处理多段式问题时，确保每一段的状态转移正确非常重要。
- **踩坑教训**：在状态压缩时，注意状态的更新顺序，避免覆盖前一个状态的值。
- **顿悟感想**：通过将问题分解为多个子问题，可以简化复杂问题的求解过程，动态规划是解决这类问题的有力工具。

---
处理用时：54.80秒