# 题目信息

# Gardener and the Array

## 题目描述

The gardener Kazimir Kazimirovich has an array of $ n $ integers $ c_1, c_2, \dots, c_n $ .

He wants to check if there are two different subsequences $ a $ and $ b $ of the original array, for which $ f(a) = f(b) $ , where $ f(x) $ is the [bitwise OR](https://en.wikipedia.org/wiki/Bitwise_operation#OR) of all of the numbers in the sequence $ x $ .

A sequence $ q $ is a subsequence of $ p $ if $ q $ can be obtained from $ p $ by deleting several (possibly none or all) elements.

Two subsequences are considered different if the sets of indexes of their elements in the original sequence are different, that is, the values of the elements are not considered when comparing the subsequences.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1775B/01e7b88f6704ebb4d7f093f81e886f156c238509.png)

## 说明/提示

It can be proven that in the first test case there are no two different subsequences $ a $ and $ b $ for which $ f(a) = f(b) $ .

In the second test case, one of the possible answers are following subsequences: the subsequence $ a $ formed by the element at position $ 1 $ , and the subsequence $ b $ formed by the elements at positions $ 1 $ and $ 2 $ .

In the third test case, one of the possible answers are following subsequences: the subsequence $ a $ formed by elements at positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , and the subsequence $ b $ formed by elements at positions $ 2 $ , $ 3 $ and $ 4 $ .

## 样例 #1

### 输入

```
5
3
2 1 5
2 2 4
2 2 3
2
2 1 2
1 2
4
3 1 2 4
2 2 4
4 1 2 5 6
2 2 5
5
3 3 1 2
3 2 5 3
5 7 2 3 1 4
5 1 2 6 3 5
3 2 6 3
2
1 1
1 2```

### 输出

```
No
Yes
Yes
Yes
No```

# AI分析结果

### 题目翻译
## 园丁与数组

### 题目描述
园丁卡齐米尔·卡齐米罗维奇有一个包含 $n$ 个整数的数组 $c_1, c_2, \dots, c_n$。

他想检查原始数组中是否存在两个不同的子序列 $a$ 和 $b$，使得 $f(a) = f(b)$，其中 $f(x)$ 是序列 $x$ 中所有数字的按位或运算结果。

如果序列 $q$ 可以通过从序列 $p$ 中删除若干（可能为零个或全部）元素得到，那么序列 $q$ 就是序列 $p$ 的子序列。

如果两个子序列在原始序列中的元素索引集合不同，则认为这两个子序列是不同的，也就是说，在比较子序列时不考虑元素的值。

### 说明/提示
可以证明，在第一个测试用例中，不存在两个不同的子序列 $a$ 和 $b$ 使得 $f(a) = f(b)$。

在第二个测试用例中，一个可能的答案是以下子序列：由位置 $1$ 处的元素构成的子序列 $a$，以及由位置 $1$ 和 $2$ 处的元素构成的子序列 $b$。

在第三个测试用例中，一个可能的答案是以下子序列：由位置 $1$、$2$、$3$ 和 $4$ 处的元素构成的子序列 $a$，以及由位置 $2$、$3$ 和 $4$ 处的元素构成的子序列 $b$。

### 样例 #1
#### 输入
```
5
3
2 1 5
2 2 4
2 2 3
2
2 1 2
1 2
4
3 1 2 4
2 2 4
4 1 2 5 6
2 2 5
5
3 3 1 2
3 2 5 3
5 7 2 3 1 4
5 1 2 6 3 5
3 2 6 3
2
1 1
1 2
```
#### 输出
```
No
Yes
Yes
Yes
No
```

### 题解综合分析与结论
#### 思路对比
各题解核心思路一致，都是判断是否能找到一个数，去掉它后数组的按位或值不变。通过固定一个子序列为原数组，另一个子序列为原数组去掉一个数，利用按位或运算性质简化问题。
#### 算法要点
- 用桶（数组或 `map`）统计每个二进制位出现的次数。
- 枚举每个数，检查其所有二进制位在桶中的计数是否都大于 1。
#### 解决难点
- 输入数据以二进制位形式给出，需正确处理并统计。
- 避免暴力枚举所有子序列导致超时，通过上述思路优化到 $O(\sum k)$ 复杂度。

#### 题解评分
| 作者 | 评分 | 理由 |
| ---- | ---- | ---- |
| Endt | 4星 | 思路清晰，代码简洁，有详细注释 |
| wwwwza | 3星 | 思路明确，但代码中使用 `-1` 分隔较难理解 |
| xu222ux | 3星 | 思路合理，代码结构清晰，但输出处理稍显复杂 |
| BFSDFS123 | 3星 | 证明过程详细，但代码中使用 `map` 效率稍低 |
| ran_qwq | 3星 | 思路简单直接，但代码中使用快读未给出实现 |
| OJ_killer | 3星 | 思路正确，但代码中多次修改 `map` 值，效率不高 |
| daiarineko | 4星 | 思路和证明详细，代码规范，有优化提示 |
| Mine_King | 4星 | 思路推导严谨，代码模块化，有函数封装 |

#### 所选题解
- **Endt（4星）**
    - 关键亮点：思路清晰，代码简洁，有详细注释。
    - 核心代码：
```cpp
for(int i=1;i<=n;++i){
    f=1;
    for(int j:p[i])if(d[j]==1)f=0;
    if(f)break;
}
```
核心思想：枚举每个数，检查其所有二进制位出现次数是否都大于 1。
- **daiarineko（4星）**
    - 关键亮点：思路和证明详细，代码规范，有优化提示。
    - 核心代码：
```cpp
for (int i = 1; i <= n; ++i)
    for (auto j : c[i])
        ++vis[j]; // 预处理所有位的出现次数
for (int i = 1; i <= n; ++i)
{
    bool flag2 = true;
    for (auto j : c[i])
        if (vis[j] < 2)
        {
            flag2 = false;
            break;
        }
    if (flag2)
    {
        flag = true;
        break;
    }
}
```
核心思想：先统计所有二进制位出现次数，再枚举每个数判断是否满足条件。
- **Mine_King（4星）**
    - 关键亮点：思路推导严谨，代码模块化，有函数封装。
    - 核心代码：
```cpp
int check(int x) {
    int flag=1;
    for (int i:c[x])
        if (!--b[i]) flag=0;
    for (int i:c[x]) b[i]++;
    return flag;
}
for (int i=1;i<=n;i++)
    if (check(i)) {
        puts("Yes");
        goto NXT;
    }
```
核心思想：封装 `check` 函数判断去掉某个数是否满足条件，枚举每个数调用该函数。

### 最优关键思路或技巧
- **简化问题**：通过证明得出若有解，一定存在一个子序列是原数组，另一个是原数组去掉一个数，将问题从枚举所有子序列简化为枚举去掉的数。
- **桶统计**：用数组或 `map` 统计每个二进制位出现的次数，快速判断去掉一个数后按位或值是否改变。

### 可拓展之处
同类型题可拓展到其他位运算，如按位与、按位异或等，判断是否存在子序列满足特定位运算结果相等。类似算法套路可用于处理集合包含关系、元素贡献等问题。

### 推荐题目
- [P1832 A+B Problem（再升级）](https://www.luogu.com.cn/problem/P1832)：考察位运算和组合数学。
- [P2114 [NOI2014] 起床困难综合症](https://www.luogu.com.cn/problem/P2114)：涉及位运算和贪心思想。
- [P3812 【模板】线性基](https://www.luogu.com.cn/problem/P3812)：与二进制位相关，可加深对二进制位处理的理解。

### 个人心得摘录与总结
- **daiarineko**：遇到询问是否有解的题，可先在不改变解的存在性的情况下简化问题，如本题从“选择两个子序列”简化为“删除一个数”，提升求解速度并更容易得到答案。此心得强调了简化问题的重要性，在面对复杂问题时，可尝试通过合理转化降低问题难度。 

---
处理用时：39.10秒