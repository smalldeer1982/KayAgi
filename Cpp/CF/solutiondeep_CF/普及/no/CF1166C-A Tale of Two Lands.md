# 题目信息

# A Tale of Two Lands

## 题目描述

The legend of the foundation of Vectorland talks of two integers $ x $ and $ y $ . Centuries ago, the array king placed two markers at points $ |x| $ and $ |y| $ on the number line and conquered all the land in between (including the endpoints), which he declared to be Arrayland. Many years later, the vector king placed markers at points $ |x - y| $ and $ |x + y| $ and conquered all the land in between (including the endpoints), which he declared to be Vectorland. He did so in such a way that the land of Arrayland was completely inside (including the endpoints) the land of Vectorland.

Here $ |z| $ denotes the absolute value of $ z $ .

Now, Jose is stuck on a question of his history exam: "What are the values of $ x $ and $ y $ ?" Jose doesn't know the answer, but he believes he has narrowed the possible answers down to $ n $ integers $ a_1, a_2, \dots, a_n $ . Now, he wants to know the number of unordered pairs formed by two different elements from these $ n $ integers such that the legend could be true if $ x $ and $ y $ were equal to these two values. Note that it is possible that Jose is wrong, and that no pairs could possibly make the legend true.

## 说明/提示

Consider the first sample. For the pair $ \{2, 5\} $ , the situation looks as follows, with the Arrayland markers at $ |2| = 2 $ and $ |5| = 5 $ , while the Vectorland markers are located at $ |2 - 5| = 3 $ and $ |2 + 5| = 7 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/49a110f22f2f955554c4787453bc1d910bd25e72.png)The legend is not true in this case, because the interval $ [2, 3] $ is not conquered by Vectorland. For the pair $ \{5, -3\} $ the situation looks as follows, with Arrayland consisting of the interval $ [3, 5] $ and Vectorland consisting of the interval $ [2, 8] $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/764d6883589527503a65e13f965f521d456c3d05.png)As Vectorland completely contains Arrayland, the legend is true. It can also be shown that the legend is true for the pair $ \{2, -3\} $ , for a total of two pairs.

In the second sample, the only pair is $ \{3, 6\} $ , and the situation looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/18e49be72c9003e62671bf9e2781a2db66c67ab9.png)Note that even though Arrayland and Vectorland share $ 3 $ as endpoint, we still consider Arrayland to be completely inside of Vectorland.

## 样例 #1

### 输入

```
3
2 5 -3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
3 6
```

### 输出

```
1
```

# AI分析结果

### 题目内容重写

#### 题目描述

关于Vectorland建立的传说中提到了两个整数$x$和$y$。几个世纪前，数组国王在数轴上的$|x|$和$|y|$位置放置了两个标记，并征服了它们之间的所有土地（包括端点），宣布这片土地为Arrayland。多年后，向量国王在$|x - y|$和$|x + y|$位置放置了标记，并征服了它们之间的所有土地（包括端点），宣布这片土地为Vectorland。他这样做的方式使得Arrayland的土地完全包含在Vectorland的土地内（包括端点）。

这里$|z|$表示$z$的绝对值。

现在，Jose在历史考试中遇到了一个问题：“$x$和$y$的值是什么？”Jose不知道答案，但他相信自己已经将可能的答案缩小到了$n$个整数$a_1, a_2, \dots, a_n$。现在，他想知道从这$n$个整数中选取两个不同元素形成的无序对的数量，使得如果$x$和$y$等于这两个值，传说可以成立。注意，Jose可能是错的，可能没有任何对可以使传说成立。

#### 说明/提示

考虑第一个样例。对于对$\{2, 5\}$，Arrayland的标记位于$|2| = 2$和$|5| = 5$，而Vectorland的标记位于$|2 - 5| = 3$和$|2 + 5| = 7$：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/49a110f22f2f955554c4787453bc1d910bd25e72.png)

在这种情况下，传说并不成立，因为区间$[2, 3]$没有被Vectorland征服。对于对$\{5, -3\}$，Arrayland由区间$[3, 5]$组成，而Vectorland由区间$[2, 8]$组成：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/764d6883589527503a65e13f965f521d456c3d05.png)

由于Vectorland完全包含Arrayland，传说成立。还可以证明，对于对$\{2, -3\}$，传说也成立，总共有两对。

在第二个样例中，唯一的对是$\{3, 6\}$，情况如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/18e49be72c9003e62671bf9e2781a2db66c67ab9.png)

注意，即使Arrayland和Vectorland共享$3$作为端点，我们仍然认为Arrayland完全包含在Vectorland内。

#### 样例 #1

##### 输入

```
3
2 5 -3
```

##### 输出

```
2
```

#### 样例 #2

##### 输入

```
2
3 6
```

##### 输出

```
1
```

### 算法分类
排序、二分

### 题解分析与结论

#### 题解1：maomao (4星)
**关键亮点**：
- 通过绝对值处理简化问题，避免正负号的影响。
- 使用排序和二分查找优化时间复杂度，最终通过双指针进一步优化到$O(n)$。

**核心代码**：
```cpp
sort(a+1,a+n+1,cmp);
int l=1,r=1;
while(l<=n){
    while(a[r]-a[l]>=a[l] && r<=n)r++;
    ans+=(r-l-1);l++;
}
```

#### 题解2：lukelin (4星)
**关键亮点**：
- 通过绝对值处理和排序简化问题。
- 使用二分查找确定满足条件的最大元素位置，计算贡献。

**核心代码**：
```cpp
sort(a + 1, a + n + 1);
ll ans = 0;
for (int i = 1; i <= n; ++i){
    int l = i + 1, r = n, k = -1, val = a[i] << 1;
    while (l <= r){
        int mid = (l + r) >> 1;
        if (a[mid] <= val){
            l = mid + 1;
            k = mid;
        }
        else
            r = mid - 1;
    }
    if (k != -1)
        ans += k - i;
}
```

#### 题解3：XY_cpp (4星)
**关键亮点**：
- 通过绝对值处理和排序简化问题。
- 使用双指针优化时间复杂度到$O(n)$。

**核心代码**：
```cpp
sort(a + 1, a + 1 + n);
int l = 1, r = 2;
while (l <= n && r <= n) {
    while (a[l] < a[r] - a[l]) l++;
    if (l > n) break;
    ans += (long long)r - l; r++;
}
```

### 最优关键思路或技巧
1. **绝对值处理**：通过取绝对值简化问题，避免正负号的影响。
2. **排序与二分查找**：通过排序和二分查找优化时间复杂度。
3. **双指针优化**：进一步优化时间复杂度到$O(n)$。

### 可拓展之处
类似的问题可以通过绝对值处理和排序来简化，然后使用二分查找或双指针优化时间复杂度。例如，寻找满足某些条件的数对或区间。

### 推荐题目
1. [P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)
2. [P1631 序列合并](https://www.luogu.com.cn/problem/P1631)
3. [P1496 火烧赤壁](https://www.luogu.com.cn/problem/P1496)

### 个人心得
- **绝对值处理**：在处理涉及绝对值的题目时，取绝对值可以简化问题，避免正负号的影响。
- **双指针优化**：在有序数组中，双指针可以有效地优化时间复杂度，减少不必要的计算。

---
处理用时：42.45秒