# 题目信息

# Equalize

## 题目描述

Vasya has two hobbies — adding permutations $ ^{\dagger} $ to arrays and finding the most frequently occurring element. Recently, he found an array $ a $ and decided to find out the maximum number of elements equal to the same number in the array $ a $ that he can obtain after adding some permutation to the array $ a $ .

More formally, Vasya must choose exactly one permutation $ p_1, p_2, p_3, \ldots, p_n $ of length $ n $ , and then change the elements of the array $ a $ according to the rule $ a_i := a_i + p_i $ . After that, Vasya counts how many times each number occurs in the array $ a $ and takes the maximum of these values. You need to determine the maximum value he can obtain.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, it is optimal to choose $ p = [2, 1] $ . Then after applying the operation, the array $ a $ will be $ [3, 3] $ , in which the number $ 3 $ occurs twice, so the answer is $ 2 $ .

In the second test case, one of the optimal options is $ p = [2, 3, 1, 4] $ . After applying the operation, the array $ a $ will be $ [9, 4, 5, 5] $ . Since the number $ 5 $ occurs twice, the answer is $ 2 $ .

## 样例 #1

### 输入

```
7
2
1 2
4
7 1 4 1
3
103 102 104
5
1 101 1 100 1
5
1 10 100 1000 1
2
3 1
3
1000000000 999999997 999999999```

### 输出

```
2
2
3
2
1
1
2```

# AI分析结果

### 题目内容翻译
# 使数组元素相等

## 题目描述
瓦西亚（Vasya）有两个爱好——将排列 $ ^{\dagger} $ 加到数组中，以及找出出现频率最高的元素。最近，他找到了一个数组 $ a $，并决定找出在将某个排列加到数组 $ a $ 后，数组 $ a $ 中等于同一个数的元素的最大数量。

更正式地说，瓦西亚必须恰好选择一个长度为 $ n $ 的排列 $ p_1, p_2, p_3, \ldots, p_n $，然后根据规则 $ a_i := a_i + p_i $ 更改数组 $ a $ 的元素。之后，瓦西亚统计数组 $ a $ 中每个数出现的次数，并取这些值中的最大值。你需要确定他能得到的最大值。

$ ^{\dagger} $ 长度为 $ n $ 的排列是一个由 $ 1 $ 到 $ n $ 的 $ n $ 个不同整数按任意顺序组成的数组。例如，$ [2,3,1,5,4] $ 是一个排列，但 $ [1,2,2] $ 不是一个排列（数字 $ 2 $ 在数组中出现了两次），$ [1,3,4] $ 也不是一个排列（$ n = 3 $，但数组中出现了 $ 4 $）。

## 说明/提示
在第一个测试用例中，最优的选择是 $ p = [2, 1] $。然后在执行操作后，数组 $ a $ 将变为 $ [3, 3] $，其中数字 $ 3 $ 出现了两次，因此答案是 $ 2 $。

在第二个测试用例中，其中一个最优的选择是 $ p = [2, 3, 1, 4] $。在执行操作后，数组 $ a $ 将变为 $ [9, 4, 5, 5] $。由于数字 $ 5 $ 出现了两次，所以答案是 $ 2 $。

## 样例 #1
### 输入
```
7
2
1 2
4
7 1 4 1
3
103 102 104
5
1 101 1 100 1
5
1 10 100 1000 1
2
3 1
3
1000000000 999999997 999999999
```

### 输出
```
2
2
3
2
1
1
2
```

### 综合分析与结论
- **思路**：大部分题解都基于相同的核心思路。由于排列中的数各不相同，原数组中相同的数在加上排列后必然不同，所以先对数组排序并去重。对于去重后的数组，若一个区间内的最大数与最小数之差小于等于 $n - 1$，则该区间内的数可以通过加上一个排列变得相等，问题转化为在去重排序后的数组中找满足条件的最长区间。
- **算法要点**：
    - **排序去重**：使用 `sort` 函数对数组排序，再用 `unique` 函数去重。
    - **查找最长区间**：有双指针和二分查找两种方法。双指针通过维护左右指针，动态调整区间；二分查找则是对于每个元素，查找以其为最小值的满足条件的最大区间。
- **解决难点**：主要难点在于分析出原数组中相同数的处理方式以及满足条件的区间的性质。通过逻辑推理得出相同数只能保留一个，以及区间最大最小值差的限制条件，从而将问题简化。

### 所选题解
- **Kdlyh（4星）**
    - **关键亮点**：思路清晰，详细阐述了两个重要性质，并分别给出双指针和二分查找两种实现方式，代码规范，可读性高。
    - **个人心得**：无
- **2huk（4星）**
    - **关键亮点**：对思路的分析详细，从问题的理解到性质的推导，再到算法的优化（从 $O(n^2)$ 优化到双指针的 $O(n)$），逻辑连贯，代码简洁明了。
    - **个人心得**：无
- **无名之雾（4星）**
    - **关键亮点**：提供了双指针和二分查找两种方法，且每种方法都有详细的思路和代码实现，对代码的解释较为清晰。
    - **个人心得**：提到因 `sort(a+1,a+n+1)` 打成 `sort(a+n,a+n+1)` 挂了5发，提醒注意排序范围。

### 重点代码
#### Kdlyh 双指针实现
```cpp
void solve() {
    int n;
    std::cin >> n;
    std::vector<i64> a(n);
    for (auto& i : a) std::cin >> i;
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
    i64 ans = 0;
    for (int i = 0, j = 0; i < a.size(); i++) {
        while(j < a.size() && a[i] + n - 1 >= a[j]) j++;
        ans = std::max<int>(ans, j - i);
    }
    std::cout << ans << '\n';
}
```
**核心思想**：先对数组排序去重，然后用双指针 $i$ 和 $j$ 维护一个区间，当区间满足最大最小值差小于等于 $n - 1$ 时，右指针 $j$ 右移，更新最大区间长度。

#### 2huk 双指针优化实现
```cpp
int solve() {
    int n = read();
    vector<int> a(n);
    for (int &t : a) t = read();
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = a.size(), res = 0;
    for (int r = 0, l = 0; r < m; ++ r ) {
        while (l <= r && a[r] + 1 - a[l] > n) {
            ++ l;
        }
        if (l <= r && a[r] + 1 - a[l] <= n) res = max(res, r - l + 1);
    }
    return res;
}
```
**核心思想**：同样先排序去重，然后用双指针 $l$ 和 $r$ 维护区间，当区间不满足条件时，左指针 $l$ 右移，更新最大区间长度。

#### 无名之雾 双指针实现
```cpp
signed main(){
    int t=read();
    while(t--){
        int n=read(),ans=0;
        for(int i=1;i<=n;i++)a[i]=read();
        sort(a+1,a+n+1);
        int q=unique(a+1,a+n+1)-a-1;
        for(int l=1,r=1;r<=q;r++){
            while(a[l]+n-1<a[r])l++;
            ans=max(ans,r-l+1);
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```
**核心思想**：排序去重后，用双指针 $l$ 和 $r$ 维护区间，当区间不满足条件时，左指针 $l$ 右移，更新最大区间长度。

### 最优关键思路或技巧
- **逻辑推理**：通过分析排列和数组的性质，得出原数组中相同数的处理方式以及满足条件的区间的性质，将复杂问题简化。
- **双指针和二分查找**：双指针可以在 $O(n)$ 时间复杂度内解决问题，二分查找可以在 $O(n\log n)$ 时间复杂度内解决问题，根据具体情况选择合适的方法。

### 可拓展之处
同类型题可能会改变排列的规则或数组的操作方式，但核心思路仍然是分析元素之间的关系，找出满足条件的区间。类似算法套路如滑动窗口、二分查找等可以应用到其他区间查找问题中。

### 推荐洛谷题目
- [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
- [P1440 求m区间内的最小值](https://www.luogu.com.cn/problem/P1440)
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)

### 个人心得总结
- 无名之雾提到因 `sort(a+1,a+n+1)` 打成 `sort(a+n,a+n+1)` 挂了5发，提醒在编写代码时要注意排序范围，避免低级错误。

---
处理用时：52.45秒