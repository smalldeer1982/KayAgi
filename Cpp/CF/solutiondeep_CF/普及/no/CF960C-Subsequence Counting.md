# 题目信息

# Subsequence Counting

## 题目描述

Pikachu had an array with him. He wrote down all the non-empty subsequences of the array on paper. Note that an array of size $ n $ has $ 2^{n}-1 $ non-empty subsequences in it.

Pikachu being mischievous as he always is, removed all the subsequences in which Maximum\_element\_of\_the\_subsequence $ - $ Minimum\_element\_of\_subsequence $ >=d $

Pikachu was finally left with $ X $ subsequences.

However, he lost the initial array he had, and now is in serious trouble. He still remembers the numbers $ X $ and $ d $ . He now wants you to construct any such array which will satisfy the above conditions. All the numbers in the final array should be positive integers less than $ 10^{18} $ .

Note the number of elements in the output array should not be more than $ 10^{4} $ . If no answer is possible, print $ -1 $ .

## 说明/提示

In the output of the first example case, the remaining subsequences after removing those with Maximum\_element\_of\_the\_subsequence $ - $ Minimum\_element\_of\_subsequence $ >=5 $ are $ [5],[5,7],[5,6],[5,7,6],[50],[7],[7,6],[15],[6],[100] $ . There are $ 10 $ of them. Hence, the array $ [5,50,7,15,6,100] $ is valid.

Similarly, in the output of the second example case, the remaining sub-sequences after removing those with Maximum\_element\_of\_the\_subsequence $ - $ Minimum\_element\_of\_subsequence $ >=2 $ are $ [10],[100],[1000],[10000] $ . There are $ 4 $ of them. Hence, the array $ [10,100,1000,10000] $ is valid.

## 样例 #1

### 输入

```
10 5
```

### 输出

```
6
5 50 7 15 6 100```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
4
10 100 1000 10000```

# AI分析结果

### 题目内容重写
# 子序列计数

## 题目描述

Pikachu有一个数组。他在纸上写下了该数组的所有非空子序列。注意，一个大小为 $n$ 的数组有 $2^{n}-1$ 个非空子序列。

Pikachu一如既往地调皮，他删除了所有满足子序列中最大元素与最小元素之差 $>=d$ 的子序列。

最后，Pikachu剩下了 $X$ 个子序列。

然而，他丢失了最初的数组，现在陷入了困境。他仍然记得数字 $X$ 和 $d$。现在，他希望你构造一个满足上述条件的数组。数组中的所有数字都应该是小于 $10^{18}$ 的正整数。

注意，输出数组中的元素数量不应超过 $10^{4}$。如果没有可能的答案，输出 $-1$。

## 说明/提示

在第一个样例的输出中，删除所有满足最大元素与最小元素之差 $>=5$ 的子序列后，剩下的子序列为 $[5],[5,7],[5,6],[5,7,6],[50],[7],[7,6],[15],[6],[100]$。共有 $10$ 个子序列。因此，数组 $[5,50,7,15,6,100]$ 是有效的。

类似地，在第二个样例的输出中，删除所有满足最大元素与最小元素之差 $>=2$ 的子序列后，剩下的子序列为 $[10],[100],[1000],[10000]$。共有 $4$ 个子序列。因此，数组 $[10,100,1000,10000]$ 是有效的。

## 样例 #1

### 输入

```
10 5
```

### 输出

```
6
5 50 7 15 6 100```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
4
10 100 1000 10000```

### 算法分类
构造

### 题解分析与结论
1. **核心思路**：通过将数组分成若干组，每组内的元素满足最大元素与最小元素之差小于 $d$，从而确保每组内的子序列都满足条件。每组对总子序列数的贡献为 $2^{n}-1$，其中 $n$ 是组内元素的数量。
2. **难点**：如何将 $X$ 分解为若干组，使得每组的贡献之和恰好为 $X$。通过二进制分解的方法，可以将 $X$ 表示为若干个 $2^{n}-1$ 的和。
3. **优化**：通过引入一个大小为1的组，将问题转化为 $2^{n}$ 的二进制分解，简化了问题的处理。

### 所选题解
1. **作者：XCH_0803 (赞：1)**
   - **星级**：4
   - **关键亮点**：通过二进制分解将 $X$ 转化为 $2^{n}$ 的形式，简化了问题处理。代码简洁明了，逻辑清晰。
   - **核心代码**：
     ```cpp
     for(int i=31;i>=0;i--){
         if(x&(1ll<<i)){
             a[m]=i;
             a[m+1]=1;
             n+=i+1;
             m+=2;
         }
     }
     ```
   - **实现思想**：通过遍历 $X$ 的二进制位，将每个为1的位对应的组大小存储在数组中，最后输出构造的数组。

2. **作者：DPair (赞：0)**
   - **星级**：4
   - **关键亮点**：详细解释了如何通过加 $d$ 来确保新组的元素不会影响前面的组，逻辑严谨，代码实现清晰。
   - **核心代码**：
     ```cpp
     while(x){
         if(x & 1){
             for (register int i = 1;i <= base - 1;i ++){
                 ans.push_back(cur);
             }
             cur += d;
             ans.push_back(cur);
             cur += d;
         }
         x >>= 1;
         base ++;
     }
     ```
   - **实现思想**：通过循环处理 $X$ 的二进制位，每次为1的位对应一个组，构造相应的元素并加入结果数组。

3. **作者：Composite_Function (赞：0)**
   - **星级**：4
   - **关键亮点**：通过贪心算法，从最大 $k$ 开始构造，确保每次构造的组对总子序列数的贡献最大，代码简洁高效。
   - **核心代码**：
     ```cpp
     while (x != 0) {
         if (x % 2 == 1) {
             for (int i = 1; i <= num - 1; ++i)
                 ans.push_back(cnt);
             cnt += d, ans.push_back(cnt), cnt += d;
         }
         x /= 2, ++num;
     }
     ```
   - **实现思想**：通过循环处理 $X$ 的二进制位，每次为1的位对应一个组，构造相应的元素并加入结果数组。

### 最优关键思路
通过将 $X$ 进行二进制分解，将问题转化为构造若干组，每组对总子序列数的贡献为 $2^{n}-1$。通过引入一个大小为1的组，将问题简化为 $2^{n}$ 的二进制分解，从而简化了问题的处理。

### 可拓展之处
类似的问题可以通过分组和二进制分解的方法来解决，特别是在需要精确控制某些条件（如子序列数）时，这种思路非常有效。

### 推荐题目
1. [CF960C - Subsequence Counting](https://www.luogu.com.cn/problem/CF960C)
2. [P1469 - 找筷子](https://www.luogu.com.cn/problem/P1469)
3. [P1496 - 火烧赤壁](https://www.luogu.com.cn/problem/P1496)

---
处理用时：38.18秒