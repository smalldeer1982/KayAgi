# 题目信息

# Number Circle

## 题目描述

You are given $ n $ numbers $ a_1, a_2, \ldots, a_n $ . Is it possible to arrange them in a circle in such a way that every number is strictly less than the sum of its neighbors?

For example, for the array $ [1, 4, 5, 6, 7, 8] $ , the arrangement on the left is valid, while arrangement on the right is not, as $ 5\ge 4 + 1 $ and $ 8> 1 + 6 $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1189B/68eb6130a6cefad8260448b1347c6d6d41d81495.png)

## 说明/提示

One of the possible arrangements is shown in the first example:

 $ 4< 2 + 3 $ ;

 $ 2 < 4 + 3 $ ;

 $ 3< 4 + 2 $ .

One of the possible arrangements is shown in the second example.

No matter how we arrange $ 13, 8, 5 $ in a circle in the third example, $ 13 $ will have $ 8 $ and $ 5 $ as neighbors, but $ 13\ge 8 + 5 $ .

There is no solution in the fourth example.

## 样例 #1

### 输入

```
3
2 4 3
```

### 输出

```
YES
4 2 3 ```

## 样例 #2

### 输入

```
5
1 2 3 4 4
```

### 输出

```
YES
4 4 2 1 3```

## 样例 #3

### 输入

```
3
13 8 5
```

### 输出

```
NO```

## 样例 #4

### 输入

```
4
1 10 100 1000
```

### 输出

```
NO```

# AI分析结果

### 题目内容
# 数字圆圈

## 题目描述
给定 $n$ 个数 $a_1, a_2, \ldots, a_n$ 。是否有可能将它们排成一个圆圈，使得每个数都严格小于其相邻数之和？

例如，对于数组 $[1, 4, 5, 6, 7, 8]$ ，左边的排列是有效的，而右边的排列则无效，因为 $5\geq 4 + 1$ 且 $8> 1 + 6$ 。

![数字圆圈示例](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1189B/68eb6130a6cefad8260448b1347c6d6d41d81495.png)

## 说明/提示
第一个示例中展示了一种可能的排列：
$4< 2 + 3$ ；
$2 < 4 + 3$ ；
$3< 4 + 2$ 。

第二个示例中展示了一种可能的排列。

在第三个示例中，无论我们如何将 $13, 8, 5$ 排成一个圆圈，$13$ 的相邻数都将是 $8$ 和 $5$ ，但 $13\geq 8 + 5$ 。

第四个示例中没有解决方案。

## 样例 #1
### 输入
```
3
2 4 3
```
### 输出
```
YES
4 2 3 
```

## 样例 #2
### 输入
```
5
1 2 3 4 4
```
### 输出
```
YES
4 4 2 1 3
```

## 样例 #3
### 输入
```
3
13 8 5
```
### 输出
```
NO
```

## 样例 #4
### 输入
```
4
1 10 100 1000
```
### 输出
```
NO
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是先对给定的数组进行排序，然后根据最大数与次大、第三大数的关系来判断是否能构造出满足条件的数字圆圈。如果最大数大于等于次大值与第三大值之和，那么一定无法满足条件，输出“NO”；否则可以通过特定的排列方式构造出满足条件的序列，输出“YES”并给出排列方案。不同题解的主要差异在于构造满足条件序列的具体方式。

### 所选的题解
- **作者：1saunoya (赞：3)  星级：4星**
    - **关键亮点**：思路清晰，先排序，将最小的数放在中心，然后两边拓展构造序列，最后再检查构造的序列是否满足条件。代码实现详细，对不同的 $n$（奇数和偶数）情况分别处理。
    - **重点代码**：
```cpp
sort(a + 1, a + n + 1);
int mid = n + 1 >> 1;
if (n & 1) {
    ans[mid] = a[1];
    int cnt = 1;
    int l = 0;
    int r = 0;
    while (cnt <= n - 1) {
        ans[mid - (++l)] = a[++cnt];
        ans[mid + (++r)] = a[++cnt];
    }
} else {
    ans[mid] = a[1];
    ans[mid + 1] = a[2];
    int cnt = 2;
    int l = 0;
    int r = 0;
    while (cnt <= n - 1) {
        ans[mid - (++l)] = a[++cnt];
        ans[mid + 1 + (++r)] = a[++cnt];
    }
}
ans[0] = ans[n];
ans[n + 1] = ans[1];
int f = 1;
for (register int i = 1; i <= n; i++) {
    if (ans[i] >= ans[i - 1] + ans[i + 1]) f = 0;
}
if (f) {
    puts("YES");
    for (register int i = 1; i <= n; i++) cout << ans[i] << ' ';
} else {
    puts("NO");
}
```
    - **核心实现思想**：先对数组 `a` 排序，根据 `n` 的奇偶性将最小数置于中间位置构造数组 `ans`，再检查 `ans` 中每个数是否满足小于相邻数之和的条件，根据检查结果输出。
- **作者：zct_sky (赞：2)  星级：4星**
    - **关键亮点**：逻辑简洁明了，直接根据最大数与次大、第三大数的关系判断能否构造，然后按照特定顺序直接构造出满足条件的序列，代码简洁高效。
    - **重点代码**：
```cpp
sort(a, a + n);
if (a[n - 1] >= a[n - 2] + a[n - 3]) {
    cout << "NO";
    return 0;
}
cout << "YES\n";
b[0] = a[n - 1], b[1] = a[n - 2], b[n - 1] = a[n - 3];
for (int i = n - 4; i >= 0; i--)
    b[n - 2 - i] = a[i];
for (int i = 0; i < n; i++)
    cout << b[i] << " ";
```
    - **核心实现思想**：对数组 `a` 排序后判断最大数与次大、第三大数关系，若满足条件则将最大、次大、第三大数按特定位置放置，再将剩余数从大到小填充构造数组 `b` 并输出。
- **作者：AC_Dolphin (赞：2)  星级：4星**
    - **关键亮点**：同样基于最大数与次大、第三大数的关系判断，通过简单交换操作构造出满足条件的序列，代码简洁，思路直接。
    - **重点代码**：
```cpp
sort(a + 1, a + n + 1);
if (a[n - 2] + a[n - 1] <= a[n]) { cout << "NO"; return 0; }
swap(a[n - 1], a[n]);
cout << "YES" << endl;
for (register int i(1); i <= n; ++i) cout << a[i] << " ";
```
    - **核心实现思想**：排序后判断最大数与次大、第三大数关系，若满足条件则交换最大数和次大数位置，直接输出数组 `a` 作为满足条件的序列。

### 最优关键思路或技巧
先对数组排序，通过判断最大数与次大、第三大数的关系来确定是否能构造出满足条件的序列，这是解决问题的关键。在构造满足条件的序列时，不同方法各有巧妙之处，如将最小数放中间向两边拓展，或者将最大数与次大、第三大数按特定位置放置后填充剩余数等。

### 拓展思路
此类题目属于构造类型，通常需要根据给定条件去寻找一种合理的排列或构建方式。类似题目可能会改变数字间的比较关系，或者对排列的形状、规则进行变化。例如，可能要求排成矩阵，或者相邻数的关系变为倍数关系等。

### 洛谷题目推荐
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及对数字的选取和组合，通过枚举和判断来解决问题，与本题对数字进行特定排列并判断条件满足情况类似。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：通过动态规划的方式解决组合问题，在思考如何满足一定条件下的组合方式上与本题有相似之处。
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：需要考虑点与点之间的关系，通过搜索等方法找到满足条件的路径，和本题构造满足特定关系的序列思路类似。

### 个人心得摘录与总结
- **作者：Zekrom**：吐槽CF不能写 `return printf(...)` 导致RE，做题时怀疑卡快排加了 `random_shuffle` 但仍RE。总结为应注意平台对代码写法的限制，遇到RE问题时排查原因不能仅局限于排序部分。 

---
处理用时：85.98秒