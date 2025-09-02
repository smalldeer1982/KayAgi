# 题目信息

# Polycarp Restores Permutation

## 题目描述

An array of integers $ p_1, p_2, \dots, p_n $ is called a permutation if it contains each number from $ 1 $ to $ n $ exactly once. For example, the following arrays are permutations: $ [3, 1, 2] $ , $ [1] $ , $ [1, 2, 3, 4, 5] $ and $ [4, 3, 1, 2] $ . The following arrays are not permutations: $ [2] $ , $ [1, 1] $ , $ [2, 3, 4] $ .

Polycarp invented a really cool permutation $ p_1, p_2, \dots, p_n $ of length $ n $ . It is very disappointing, but he forgot this permutation. He only remembers the array $ q_1, q_2, \dots, q_{n-1} $ of length $ n-1 $ , where $ q_i=p_{i+1}-p_i $ .

Given $ n $ and $ q=q_1, q_2, \dots, q_{n-1} $ , help Polycarp restore the invented permutation.

## 样例 #1

### 输入

```
3
-2 1
```

### 输出

```
3 1 2 ```

## 样例 #2

### 输入

```
5
1 1 1 1
```

### 输出

```
1 2 3 4 5 ```

## 样例 #3

### 输入

```
4
-1 2 2
```

### 输出

```
-1
```

# AI分析结果

### 题目中文重写
## Polycarp 恢复排列

### 题目描述
一个整数数组 $ p_1, p_2, \dots, p_n $ 被称为一个排列，如果它恰好包含从 $ 1 $ 到 $ n $ 的每个数字一次。例如，以下数组是排列：$ [3, 1, 2] $ 、$ [1] $ 、$ [1, 2, 3, 4, 5] $ 和 $ [4, 3, 1, 2] $ 。以下数组不是排列：$ [2] $ 、$ [1, 1] $ 、$ [2, 3, 4] $ 。

Polycarp 想出了一个非常酷的长度为 $ n $ 的排列 $ p_1, p_2, \dots, p_n $ 。非常令人失望的是，他忘记了这个排列。他只记得长度为 $ n - 1 $ 的数组 $ q_1, q_2, \dots, q_{n - 1} $ ，其中 $ q_i = p_{i + 1} - p_i $ 。

给定 $ n $ 和 $ q = q_1, q_2, \dots, q_{n - 1} $ ，帮助 Polycarp 恢复他想出的排列。

### 样例 #1
#### 输入
```
3
-2 1
```
#### 输出
```
3 1 2
```

### 样例 #2
#### 输入
```
5
1 1 1 1
```
#### 输出
```
1 2 3 4 5
```

### 样例 #3
#### 输入
```
4
-1 2 2
```
#### 输出
```
-1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心都是围绕已知的差分数组 $q$ 来恢复排列数组 $p$，并判断其是否为 $1$ 到 $n$ 的排列。不同题解采用了不同的数学思路和技巧。
- **前缀和推导法**：通过对 $q$ 数组求前缀和，结合排列数组的和公式，推导出 $p_1$ 的值，进而得到整个 $p$ 数组，最后检查其是否为合法排列。
- **排序法**：对前缀和数组排序，根据排序后的顺序确定 $p$ 数组的值，再进行合法性检查。
- **二分法**：通过二分查找合适的 $p_1$ 值，判断是否能得到合法排列。
- **构造法**：先假设一个初始值，根据 $q$ 数组递推得到 $p$ 数组，调整使其满足排列条件。

### 所选题解
- **作者：luojien (赞：4)，4星**
    - **亮点**：思路清晰，通过数学公式推导得出 $p_1$ 的值，代码实现简洁明了，注释详细，易于理解。
    - **个人心得**：作者提到这题看似简单，但调试了一下午，说明在实现过程中可能会遇到一些细节问题，需要仔细处理。
- **作者：wlzhouzhuan (赞：4)，4星**
    - **亮点**：通过预处理前缀和并排序的方法，巧妙地确定了排列数组的值，代码结构清晰，逻辑严谨。
- **作者：zhy12138 (赞：2)，4星**
    - **亮点**：同样利用前缀和推导 $p_1$ 的值，代码规范，注释合理，实现了正确的算法逻辑。

### 重点代码
#### 作者：luojien
```cpp
ll n;
cin >> n;
int q[n] = {};
ll r[n] = {};
ll sum = 0;
ll rSum = 0;
for (int i = 1; i <= n - 1; i++) {
    scanf("%d", &q[i]);
    sum += q[i];
    r[i] = sum;
    rSum += r[i];
}
ll S = (n * (n + 1)) >> 1;
ll k = S - rSum;
if(k % n != 0){
    printf("-1");
    return 0;
}
int p[n + 1] = {};
int pp[n + 1] = {};
p[1] = k / n;
pp[1] = p[1];
for(int i = 2; i <= n; i++){
    p[i] = r[i - 1] + p[1];
    pp[i] = p[i];
}
sort(p + 1, p + n + 1);
for(int i = 1; i <= n; i++){
    if(p[i] != i){
        printf("-1");
        return 0;
    }
}
for(int i = 1; i <= n; i++){
    printf("%d ", pp[i]);
}
```
**核心思想**：先对 $q$ 数组求前缀和得到 $r$ 数组，再根据排列数组的和公式计算 $p_1$ 的值，然后根据 $p_1$ 和前缀和数组得到 $p$ 数组，最后排序检查其是否为合法排列。

#### 作者：wlzhouzhuan
```cpp
read(n);
qwq[1].s = 0, qwq[1].id = 1;
rep(i, 2, n) {
    read(a[i]);
    qwq[i].s = qwq[i - 1].s + a[i];
    qwq[i].id = i;
}
sort(qwq + 1, qwq + n + 1);
for (int i = 1; i <= n; i++)
    ans[qwq[i].id] = i;

if (check()) {
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
    putchar('\n');
}
else puts("-1");
```
**核心思想**：预处理前缀和并记录原始位置，对前缀和数组排序，根据排序后的顺序确定排列数组的值，最后检查其合法性。

#### 作者：zhy12138
```cpp
n=read();
for(register int i=1;i<n;++i)
    q[i]=q[i-1]+read(),sum+=q[i];
long long t=n*(n+1)/2;
long long rest=t-sum;
if(rest%n!=0)
{
    puts("-1");
    return 0;
}
long long p1=rest/n;
a[1]=b[1]=p1;
for(register int i=2;i<=n;++i)
    a[i]=b[i]=(q[i-1]+p1);
sort(a+1,a+n+1);
if(a[1]!=1)
{
    puts("-1");
    return 0;
}
for(register int i=2;i<=n;++i)
    if(a[i]-a[i-1]!=1)
    {
        puts("-1");
        return 0;
    }
for(register int i=1;i<=n;++i)
    printf("%lld ",b[i]);
```
**核心思想**：对 $q$ 数组求前缀和，根据排列数组的和公式计算 $p_1$ 的值，得到 $p$ 数组后排序检查其是否为合法排列。

### 关键思路与技巧
- **前缀和的运用**：通过对差分数组 $q$ 求前缀和，可以得到相邻元素与 $p_1$ 的关系，从而推导出整个排列数组。
- **数学公式推导**：利用排列数组的和公式，结合前缀和数组，计算出 $p_1$ 的值。
- **排序与合法性检查**：对得到的排列数组进行排序，检查其是否为 $1$ 到 $n$ 的连续整数，以判断其是否为合法排列。

### 拓展思路
同类型题目可能会改变条件，如给定部分排列元素或改变差分数组的形式，但核心思路仍然是利用数学关系和逻辑推理来恢复排列。类似的算法套路包括利用前缀和、差分等数学工具，结合排序、检查等操作来解决问题。

### 推荐题目
1. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：涉及排列组合和动态规划的思想。
2. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)：需要运用递推和组合数学的知识。
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)：考察动态规划和贪心的算法应用。

---
处理用时：59.42秒