# 题目信息

# The Best Vacation

## 题目描述

由于本场题面违反互联网相关法律，不予展示原题面。

## 说明/提示

In the first test case, the numbers of the days in a year are (indices of days in a corresponding month) $ \{1,1,2,3,1\} $ . Coronavirus-chan will hug you the most if you come on the third day of the year: $ 2+3=5 $ hugs.

In the second test case, the numbers of the days are $ \{1,2,3,1,2,3,1,2,3\} $ . You will get the most hugs if you arrive on the third day of the year: $ 3+1+2+3+1+2=12 $ hugs.

In the third test case, the numbers of the days are $ \{1,2,3,4,1,2, 1,2,3, 1, 1,2,3\} $ . You will get the most hugs if you come on the twelfth day of the year: your friend will hug you $ 2+3+1+2+3+4=15 $ times.

## 样例 #1

### 输入

```
3 2
1 3 1```

### 输出

```
5```

## 样例 #2

### 输入

```
3 6
3 3 3```

### 输出

```
12```

## 样例 #3

### 输入

```
5 6
4 2 3 1 3```

### 输出

```
15```

# AI分析结果

### 题目翻译
由于本场题面违反互联网相关法律，不予展示原题面。

### 说明/提示
在第一个测试用例中，一年中各天的编号（对应月份中各天的索引）为 $\{1,1,2,3,1\}$。如果你在一年中的第三天到来，Coronavirus - chan 会给你最多的拥抱：$2 + 3 = 5$ 个拥抱。

在第二个测试用例中，各天的编号为 $\{1,2,3,1,2,3,1,2,3\}$。如果你在一年中的第三天到达，你将得到最多的拥抱：$3 + 1 + 2 + 3 + 1 + 2 = 12$ 个拥抱。

在第三个测试用例中，各天的编号为 $\{1,2,3,4,1,2, 1,2,3, 1, 1,2,3\}$。如果你在一年中的第十二天到来，你将得到最多的拥抱：你的朋友会拥抱你 $2 + 3 + 1 + 2 + 3 + 4 = 15$ 次。

### 样例 #1
#### 输入
```
3 2
1 3 1
```
#### 输出
```
5
```

### 样例 #2
#### 输入
```
3 6
3 3 3
```
#### 输出
```
12
```

### 样例 #3
#### 输入
```
5 6
4 2 3 1 3
```
#### 输出
```
15
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是基于贪心策略，即答案肯定是连续几个月加上某个月的月末的拥抱数。为了优化时间复杂度，大多题解采用了前缀和来快速计算区间内的拥抱数，同时使用二分或双指针来确定区间范围。

### 所选题解
- **作者：_xbn (赞：4)，4星**
    - **关键亮点**：思路清晰，通过贪心确定答案形式，使用前缀和优化累加操作，并用二分查找确定区间位置，代码实现规范。
    - **个人心得**：无
- **作者：Fairicle (赞：3)，4星**
    - **关键亮点**：采用双指针的写法，相比二分更简洁易写，且当前是提交记录的 rank1，时间复杂度更优。
    - **个人心得**：认为此题双指针比二分好写，还更优。
- **作者：KellyFrog (赞：3)，4星**
    - **关键亮点**：详细阐述了贪心的思路，通过枚举起点并结合二分查找确定区间，注意到了破环成链、特殊情况判断等细节。
    - **个人心得**：因为特判了但没写 `else` 所以 `WA on test #23`。

### 重点代码
#### _xbn 的代码核心实现
```cpp
for (int i = 1; i <= 2 * n; i++)
{
    if(s1[i] < x) continue;
    int pos = lower_bound(s1 + 1, s1 + 1 + 2 * n, s1[i] - x) - s1;
    int tmp = s2[i] - s2[pos];
    tot = x - s1[i] + s1[pos];
    tmp += (a[pos] - tot + 1 + a[pos]) * tot / 2;
    ans = max(tmp, ans);
}
```
**核心思想**：枚举最后一个月，用二分查找找到之前最多能取到的位置，利用前缀和计算区间内的拥抱数，更新最大拥抱数。

#### Fairicle 的代码核心实现
```cpp
for(ri i=1,j=0;i<=2*n;++i){
    while(sd[i]-sd[j]>k) ++j;
    if(sd[i]>=k){
        ll tmp=sh[i]-sh[j];
        ll res=k-sd[i]+sd[j];
        tmp+=(2*d[j]+1-res)*res/2;
        ans=max(ans,tmp);
    }
}
```
**核心思想**：使用双指针，$i$ 指针枚举最后一个月，$j$ 指针保证 $i$ 和 $j$ 之间的天数不超过给定天数，利用前缀和计算拥抱数并更新答案。

#### KellyFrog 的代码核心实现
```cpp
for(int i = 1; i <= n; i++) {
    int b = bs(i); 
    if(b == 0) {
        int l = a[i] - d;
        ans = max(ans, a[i] * (a[i] + 1) / 2 - l * (l + 1) / 2);
    } else if(sum[b] - sum[i - 1] == d) {
        ans = max(ans, suma[b] - suma[i - 1]);
    } else {
        int l = d - (sum[b] - sum[i - 1]);
        int l2 = a[b + 1] - l;
        ans = max(ans, suma[b + 1] - suma[i - 1] - l2 * (l2 + 1) / 2);
    }
}
```
**核心思想**：枚举起点，用二分查找确定区间，根据不同情况计算拥抱数并更新答案。

### 最优关键思路或技巧
- **贪心策略**：根据题目性质，确定答案是连续几个月加上某个月的月末的拥抱数，减少不必要的枚举。
- **前缀和优化**：使用前缀和数组记录到每个月为止的天数和拥抱数，快速计算区间内的天数和拥抱数，避免暴力累加导致的 TLE。
- **二分或双指针**：使用二分查找或双指针确定区间范围，进一步优化时间复杂度。

### 可拓展之处
同类型题可能会改变月份天数的分布规律，或者增加其他限制条件，如不同月份的拥抱数计算方式不同等。类似算法套路可以应用在区间选择问题中，通过贪心策略确定最优区间形式，再用前缀和、二分或双指针等方法优化计算过程。

### 推荐洛谷题目
- [P1007 独木桥](https://www.luogu.com.cn/problem/P1007)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)

---
处理用时：45.87秒