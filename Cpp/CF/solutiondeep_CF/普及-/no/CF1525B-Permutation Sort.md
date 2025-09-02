# 题目信息

# Permutation Sort

## 题目描述

You are given a permutation $ a $ consisting of $ n $ numbers $ 1 $ , $ 2 $ , ..., $ n $ (a permutation is an array in which each element from $ 1 $ to $ n $ occurs exactly once).

You can perform the following operation: choose some subarray (contiguous subsegment) of $ a $ and rearrange the elements in it in any way you want. But this operation cannot be applied to the whole array.

For example, if $ a = [2, 1, 4, 5, 3] $ and we want to apply the operation to the subarray $ a[2, 4] $ (the subarray containing all elements from the $ 2 $ -nd to the $ 4 $ -th), then after the operation, the array can become $ a = [2, 5, 1, 4, 3] $ or, for example, $ a = [2, 1, 5, 4, 3] $ .

Your task is to calculate the minimum number of operations described above to sort the permutation $ a $ in ascending order.

## 说明/提示

In the explanations, $ a[i, j] $ defines the subarray of $ a $ that starts from the $ i $ -th element and ends with the $ j $ -th element.

In the first test case of the example, you can select the subarray $ a[2, 3] $ and swap the elements in it.

In the second test case of the example, the permutation is already sorted, so you don't need to apply any operations.

In the third test case of the example, you can select the subarray $ a[3, 5] $ and reorder the elements in it so $ a $ becomes $ [2, 1, 3, 4, 5] $ , and then select the subarray $ a[1, 2] $ and swap the elements in it, so $ a $ becomes $ [1, 2, 3, 4, 5] $ .

## 样例 #1

### 输入

```
3
4
1 3 2 4
3
1 2 3
5
2 1 4 5 3```

### 输出

```
1
0
2```

# AI分析结果

### 题目内容
# 排列排序

## 题目描述
给定一个由 $n$ 个数字 $1$，$2$，...，$n$ 组成的排列 $a$（排列是指一个数组，其中从 $1$ 到 $n$ 的每个元素恰好出现一次）。

你可以执行以下操作：选择 $a$ 的某个子数组（连续子段），并以任意方式重新排列其中的元素。但此操作不能应用于整个数组。

例如，如果 $a = [2, 1, 4, 5, 3]$，并且我们要对 $a[2, 4]$ 子数组（包含从第 $2$ 个到第 $4$ 个的所有元素）应用该操作，那么操作后，数组可能变为 $a = [2, 5, 1, 4, 3]$，或者例如 $a = [2, 1, 5, 4, 3]$。

你的任务是计算通过上述操作将排列 $a$ 按升序排序所需的最小操作次数。

## 说明/提示
在解释中，$a[i, j]$ 定义为从第 $i$ 个元素开始到第 $j$ 个元素结束的 $a$ 的子数组。

在示例的第一个测试用例中，你可以选择子数组 $a[2, 3]$ 并交换其中的元素。

在示例的第二个测试用例中，排列已经排序，因此无需应用任何操作。

在示例的第三个测试用例中，你可以选择子数组 $a[3, 5]$ 并重新排列其中的元素，使 $a$ 变为 $[2, 1, 3, 4, 5]$，然后选择子数组 $a[1, 2]$ 并交换其中的元素，使 $a$ 变为 $[1, 2, 3, 4, 5]$。

## 样例 #1
### 输入
```
3
4
1 3 2 4
3
1 2 3
5
2 1 4 5 3
```
### 输出
```
1
0
2
```

### 算法分类
数学

### 综合分析与结论
所有题解思路基本一致，均通过对序列首末元素情况进行分类讨论得出最小操作次数。关键在于根据首末元素是否为 $1$ 或 $n$ 来确定操作次数：若序列已升序，操作次数为 $0$；若第一个元素为 $1$ 或者最后一个元素为 $n$，操作次数为 $1$；若第一个元素为 $n$ 且最后一个元素为 $1$，操作次数为 $3$；其他情况操作次数为 $2$。各题解在代码实现上略有差异，如输入输出方式、变量命名等，但核心逻辑相同。

### 所选的题解
- **EuphoricStar**：
  - **星级**：4星
  - **关键亮点**：思路清晰简洁，直接阐述不同条件下的结论，代码简洁明了，逻辑判断直接对应各种情况。
  - **重点代码**：
```cpp
bool flag = 1;
for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    if (a[i]!= i) {
        flag = 0;
    }
}
if (flag) {
    cout << 0 << endl;
    continue;
}
if (a[1] == 1 || a[n] == n) {
    cout << 1 << endl;
} else if (a[n] == 1) {
    if (a[1]!= n) {
        cout << 2 << endl;
    } else {
        cout << 3 << endl;
    }
} else {
    cout << 2 << endl;
}
```
  - **核心实现思想**：先遍历数组判断是否已排序，然后根据首末元素的不同情况直接输出对应的操作次数。
- **miraculously**：
  - **星级**：4星
  - **关键亮点**：题目大意和分析清晰，代码结构完整，通过 `if - else` 语句准确实现不同情况的判断输出。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>

using namespace std;

int a[51];

int main()
{
    int t,n,f;
    scanf("%d",&t);
    while(t--)
    {
        f=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]!=i)
                f=1;
        }
        if(f==0)
            printf("0\n");
        else if(a[1]==n&&a[n]==1)
            printf("3\n");
        else if(a[1]!=1&&a[n]!=n)
            printf("2\n");
        else
            printf("1\n");
    }
}
```
  - **核心实现思想**：通过循环输入数组元素并判断是否已排序，再依据首末元素的特定组合输出操作次数。
- **翼德天尊**：
  - **星级**：4星
  - **关键亮点**：对每种情况的贪心策略解释详细，如每次选择 $n - 1$ 个元素排序的原因及具体操作步骤，代码逻辑与分析紧密结合。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 205
int t,a[N]; 
int read(){
    int w=0,f=1;
    char c=getchar();
    while (c>'9'||c<'0'){
        if (c=='-') f=-1;
        c=getchar();
    }
    while (c>='0'&&c<='9'){
        w=(w<<3)+(w<<1)+(c^48);
        c=getchar();
    }
    return w*f;
}
int gcd(int x,int y){
    if (y==0) return x;
    return gcd(y,x%y); 	
}
int main(){
    t=read();
    while (t--){
        int n=read(),ans=0;
        bool pd=0;
        for (int i=1;i<=n;i++){
            a[i]=read();
            if (a[i]!=i) pd=1;
        }
        if (pd==0) puts("0");
        else if (a[1]==1||a[n]==n) puts("1");
        else if (a[1]==n&&a[n]==1) puts("3");
        else puts("2");
    }
    return 0;
}
```
  - **核心实现思想**：自定义输入函数读取数据，通过循环判断数组是否有序，再按首末元素情况输出操作次数。

### 最优关键思路或技巧
通过对序列首末元素的特征进行分类讨论，快速得出最小操作次数，避免复杂的排序模拟过程，简化问题求解。

### 拓展
同类型题通常围绕特定规则下的序列变换及最小操作次数展开，类似算法套路为对序列的特殊位置元素（如首尾）或特定元素分布情况进行分析，归纳出不同情况对应的操作次数。

### 推荐题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合判断质数，考察对数字特征的分析和组合运用。
- [P1141 01迷宫](https://www.luogu.com.cn/problem/P1141)：利用广度优先搜索遍历迷宫，可类比本题对不同情况分类处理的思路。
- [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)：结合质数判断和回文数特性，通过合理剪枝优化枚举过程，与本题分析特殊情况的思维类似。

### 个人心得摘录与总结
- **FutaRimeWoawaSete**：一开始没发现性质，想用暴力方法处理，后经提醒考虑到答案为 $3$ 的情况，增加特判后通过。总结为做题时要全面考虑各种可能情况，不能局限于常规思路，注意特殊情况的分析。 

---
处理用时：52.97秒