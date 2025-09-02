# 题目信息

# Candy Box (easy version)

## 题目描述

This problem is actually a subproblem of problem G from the same contest.

There are $ n $ candies in a candy box. The type of the $ i $ -th candy is $ a_i $ ( $ 1 \le a_i \le n $ ).

You have to prepare a gift using some of these candies with the following restriction: the numbers of candies of each type presented in a gift should be all distinct (i. e. for example, a gift having two candies of type $ 1 $ and two candies of type $ 2 $ is bad).

It is possible that multiple types of candies are completely absent from the gift. It is also possible that not all candies of some types will be taken to a gift.

Your task is to find out the maximum possible size of the single gift you can prepare using the candies you have.

You have to answer $ q $ independent queries.

If you are Python programmer, consider using PyPy instead of Python when you submit your code.

## 说明/提示

In the first query, you can prepare a gift with two candies of type $ 8 $ and one candy of type $ 5 $ , totalling to $ 3 $ candies.

Note that this is not the only possible solution — taking two candies of type $ 4 $ and one candy of type $ 6 $ is also valid.

## 样例 #1

### 输入

```
3
8
1 4 8 4 5 6 3 8
16
2 1 3 3 4 3 4 4 1 3 2 2 2 4 1 1
9
2 2 4 4 4 7 7 7 7
```

### 输出

```
3
10
9
```

# AI分析结果

### 题目内容
# 糖果盒（简单版）

## 题目描述
本题实际上是同一竞赛中问题G的子问题。

糖果盒中有 $n$ 颗糖果。第 $i$ 颗糖果的类型为 $a_i$（$1 \le a_i \le n$）。

你必须用其中一些糖果准备一份礼物，需满足以下限制：礼物中每种类型糖果的数量都应各不相同（例如，一份礼物中有两颗类型1的糖果和两颗类型2的糖果是不可以的）。

可能有多种类型的糖果完全不出现在礼物中。也有可能某些类型的糖果并非全部被选入礼物。

你的任务是找出使用现有糖果能准备出的单份礼物的最大可能大小。

你必须回答 $q$ 个独立的询问。

如果你是Python程序员，提交代码时考虑使用PyPy而非Python。

## 说明/提示
在第一个询问中，你可以准备一份礼物，包含两颗类型8的糖果和一颗类型5的糖果，总计3颗糖果。

注意，这并非唯一可能的解决方案 —— 选取两颗类型4的糖果和一颗类型6的糖果也是有效的。

## 样例 #1
### 输入
```
3
8
1 4 8 4 5 6 3 8
16
2 1 3 3 4 3 4 4 1 3 2 2 2 4 1 1
9
2 2 4 4 4 7 7 7 7
```
### 输出
```
3
10
9
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，先统计每种糖果的数量，再通过不同方式选取满足条件（每种类型糖果数量各不相同）的糖果以达到最大数量。主要区别在于统计和选取糖果数量的具体实现方式。部分题解使用排序后从大到小贪心选择，部分题解则通过两个桶分别统计糖果出现次数和每种出现次数对应的糖果种类数，从大到小枚举选取。部分题解提到使用 `memset` 函数在多组数据情况下会超时，需手动清零数组。

### 所选的题解
- **作者：luo_shen（5星）**
    - **关键亮点**：思路清晰，代码简洁。先使用桶排统计每种糖果出现次数，再将次数从大到小排序，通过贪心策略，在每次循环中取当前可选取的最小数量糖果，同时注意处理已选数量和及时结束循环避免结果变小。
    - **重点代码**：
```cpp
sort(b + 1, b + n + 1, cmp);   //按数量从大到小排序 
int ans = 0, k = 2147483647; //初始化，k取极大值 
for (int i = 1; i <= n; i++) {
    k--;		//已经选过的数量要去掉 
    k = min(k, b[i]);  /*在要选的数量和现在的这种糖果的数量中取最少的数量，并记录。
                      因为是从大到小排序，所以如果这种糖果都满足不了k，那么下一种
                      糖果依然满足不了k,所以直接用min取到最小值 
                              */ 
    ans = ans + k;
    if (!k) {	        //如果能取的数量已经取完了，那么直接结束循环。如果不结束，那么k会变成负数导致结果变小 
        break;
    }
}
```
- **作者：__HHX__（5星）**
    - **关键亮点**：时间复杂度优化到 $O(n)$，通过两个桶分别记录每种糖果出现次数和每种出现次数对应的糖果种类数，从大到小枚举，巧妙更新桶和答案，效率更高。
    - **重点代码**：
```cpp
for (int i = 1; i <= n; i++) {
    cnt2[cnt[i]]++;
}
for (int i = n; i >= 1; i--) {
    if (cnt2[i]) {
        ans += i;
        cnt2[i - 1] += cnt2[i] - 1;
    }
}
```
- **作者：___Yang__（4星）**
    - **关键亮点**：与luo_shen思路类似，代码简洁易懂，通过贪心策略从大到小排序后选取糖果，清晰展示了贪心的过程。
    - **重点代码**：
```cpp
sort(a + 1, a + n + 1, cmp);
int ans = 0, p = 2147483647;
for (int i = 1; i <= n; i++) {
    p--; 
    p = min(p, a[i]);
    ans += p;
    if (p == 0) break;
}
```

### 最优关键思路或技巧
1. **使用桶排序**：通过桶排统计每种糖果的出现次数，方便后续处理。
2. **贪心策略**：从大到小考虑糖果数量，优先选取数量多的糖果，同时保证每种糖果数量不同，以达到最大礼物大小。
3. **优化时间复杂度**：如__HHX__的题解，通过额外桶记录每种出现次数对应的糖果种类数，避免排序的 $O(n \log n)$ 复杂度，将时间复杂度优化到 $O(n)$。

### 同类型题或类似算法套路拓展
此类题目通常围绕贪心策略，给定一定限制条件，求满足条件的最大或最小值。类似套路包括先统计数据分布，再根据限制条件从大到小或从小到大贪心选择。

### 洛谷相似题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：通过贪心策略合并果子，使总代价最小，与本题贪心选择糖果思路类似。
2. [P1199 [NOIP2010 普及组] 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要运用贪心策略选择武将，以获得最大得分，同样考验对贪心策略的运用。
3. [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过合理排序后贪心选择，使总时间最小，与本题通过排序后贪心选取糖果数量的思路类似。 

---
处理用时：69.84秒