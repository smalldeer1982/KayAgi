# 题目信息

# Interesting Subarray

## 题目描述

For an array $ a $ of integers let's denote its maximal element as $ \max(a) $ , and minimal as $ \min(a) $ . We will call an array $ a $ of $ k $ integers interesting if $ \max(a) - \min(a) \ge k $ . For example, array $ [1, 3, 4, 3] $ isn't interesting as $ \max(a) - \min(a) = 4 - 1 = 3 < 4 $ while array $ [7, 3, 0, 4, 3] $ is as $ \max(a) - \min(a) = 7 - 0 = 7 \ge 5 $ .

You are given an array $ a $ of $ n $ integers. Find some interesting nonempty subarray of $ a $ , or tell that it doesn't exist.

An array $ b $ is a subarray of an array $ a $ if $ b $ can be obtained from $ a $ by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end. In particular, an array is a subarray of itself.

## 说明/提示

In the second test case of the example, one of the interesting subarrays is $ a = [2, 0, 1, 9] $ : $ \max(a) - \min(a) = 9 - 0 = 9 \ge 4 $ .

## 样例 #1

### 输入

```
3
5
1 2 3 4 5
4
2 0 1 9
2
2019 2020
```

### 输出

```
NO
YES
1 4
NO
```

# AI分析结果

### 题目内容重写
# 有趣的子数组

## 题目描述

对于一个整数数组 $a$，我们将其最大元素记为 $\max(a)$，最小元素记为 $\min(a)$。我们称一个包含 $k$ 个整数的数组 $a$ 为“有趣的”，如果 $\max(a) - \min(a) \ge k$。例如，数组 $[1, 3, 4, 3]$ 不是有趣的，因为 $\max(a) - \min(a) = 4 - 1 = 3 < 4$，而数组 $[7, 3, 0, 4, 3]$ 是有趣的，因为 $\max(a) - \min(a) = 7 - 0 = 7 \ge 5$。

给定一个包含 $n$ 个整数的数组 $a$，找出一个有趣的非空子数组，或者判断它是否存在。

数组 $b$ 是数组 $a$ 的子数组，如果 $b$ 可以通过从 $a$ 的开头删除若干个（可能为零或全部）元素，并从 $a$ 的结尾删除若干个（可能为零或全部）元素得到。特别地，数组本身也是其子数组。

## 说明/提示

在样例 2 中，一个有趣的子数组是 $a = [2, 0, 1, 9]$：$\max(a) - \min(a) = 9 - 0 = 9 \ge 4$。

## 样例 #1

### 输入

```
3
5
1 2 3 4 5
4
2 0 1 9
2
2019 2020
```

### 输出

```
NO
YES
1 4
NO
```

### 算法分类
贪心

### 题解分析与结论
这些题解的核心思路是通过观察发现，只要存在两个相邻元素的差值大于等于2，那么这两个元素构成的子数组就是“有趣的”。如果整个数组中没有这样的相邻元素对，那么整个数组也不存在“有趣的”子数组。这种思路通过反证法得到了证明，即如果所有相邻元素的差值都小于2，那么整个数组的最大值与最小值之差必然小于数组长度，因此不存在“有趣的”子数组。

### 精选题解
1. **作者：tangber (赞：8)**
   - **星级：5星**
   - **关键亮点：** 通过观察样例得出关键结论，并进行了简单的反证法证明，代码简洁高效。
   - **代码核心思想：** 遍历数组，检查相邻元素的差值是否大于等于2，如果找到则输出YES和对应的下标，否则输出NO。
   ```cpp
   for(int i=1;i<n;i++) {
       if(abs(a[i]-a[i+1])>=2) {
           flag=1;
           cout<<"Yes"<<endl<<i<<" "<<i+1<<endl;
           break;
       }
   }
   ```

2. **作者：naroto2022 (赞：2)**
   - **星级：4星**
   - **关键亮点：** 通过反证法详细证明了结论，代码实现清晰。
   - **代码核心思想：** 同样遍历数组，检查相邻元素的差值是否大于等于2，如果找到则输出YES和对应的下标，否则输出NO。
   ```cpp
   for(int i=2; i<=n; i++){
       if(abs(a[i]-a[i-1])>=2){
           ok=0;
           printf("YES\n%d %d\n",i-1,i);
           break;
       }
   }
   ```

3. **作者：寒鸽儿 (赞：2)**
   - **星级：4星**
   - **关键亮点：** 通过数学归纳法进一步验证了结论，代码简洁明了。
   - **代码核心思想：** 遍历数组，检查相邻元素的差值是否大于等于2，如果找到则输出YES和对应的下标，否则输出NO。
   ```cpp
   for(int i = 2; i <= n; ++i) {
       if(abs(tmp - lst) >= 2) {
           pls = i;
           flg = true;
       }
       lst = tmp;
   }
   ```

### 关键思路与技巧
- **关键思路：** 通过观察相邻元素的差值来判断是否存在“有趣的”子数组，利用反证法证明结论的正确性。
- **技巧：** 遍历数组时，只需检查相邻元素的差值，无需考虑更长的子数组，大大简化了问题。

### 拓展思路
- 类似的问题可以通过观察数组的局部性质来简化问题，例如通过检查相邻元素的性质来判断整个数组的性质。
- 反证法在证明某些结论时非常有效，尤其是在需要证明“不存在”的情况下。

### 推荐题目
1. [CF1270B - Interesting Subarray](https://www.luogu.com.cn/problem/CF1270B)
2. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
3. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)

---
处理用时：36.57秒