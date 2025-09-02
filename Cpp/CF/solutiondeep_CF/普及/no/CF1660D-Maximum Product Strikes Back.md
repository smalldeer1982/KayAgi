# 题目信息

# Maximum Product Strikes Back

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. For each $ i $ ( $ 1 \le i \le n $ ) the following inequality is true: $ -2 \le a_i \le 2 $ .

You can remove any number (possibly $ 0 $ ) of elements from the beginning of the array and any number (possibly $ 0 $ ) of elements from the end of the array. You are allowed to delete the whole array.

You need to answer the question: how many elements should be removed from the beginning of the array, and how many elements should be removed from the end of the array, so that the result will be an array whose product (multiplication) of elements is maximal. If there is more than one way to get an array with the maximum product of elements on it, you are allowed to output any of them.

The product of elements of an empty array (array of length $ 0 $ ) should be assumed to be $ 1 $ .

## 说明/提示

In the first case, the maximal value of the product is $ 2 $ . Thus, we can either delete the first three elements (obtain array $ [2] $ ), or the last two and one first element (also obtain array $ [2] $ ), or the last two elements (obtain array $ [1, 2] $ ). Thus, in the first case, the answers fit: "3 0", or "1 2", or "0 2".

In the second case, the maximum value of the product is $ 1 $ . Then we can remove all elements from the array because the value of the product on the empty array will be $ 1 $ . So the answer is "3 0", but there are other possible answers.

In the third case, we can remove the first two elements of the array. Then we get the array: $ [-2, 2, -1] $ . The product of the elements of the resulting array is $ (-2) \cdot 2 \cdot (-1) = 4 $ . This value is the maximum possible value that can be obtained. Thus, for this case the answer is: "2 0".

## 样例 #1

### 输入

```
5
4
1 2 -1 2
3
1 1 -2
5
2 0 -2 2 -1
3
-2 -1 -1
3
-1 -2 -2```

### 输出

```
0 2
3 0
2 0
0 1
1 0```

# AI分析结果

### 题目内容重写
#### 题目描述
给定一个由 $n$ 个整数组成的数组 $a$，对于每个 $i$（$1 \le i \le n$），满足 $-2 \le a_i \le 2$。你可以从数组的开头删除任意数量的元素（可能为 $0$），并从数组的末尾删除任意数量的元素（可能为 $0$）。你可以删除整个数组。

你需要回答：应该从数组的开头删除多少个元素，以及从数组的末尾删除多少个元素，使得剩下的数组的乘积最大。如果有多种方式可以得到乘积最大的数组，你可以输出其中任意一种。

空数组的乘积应被视为 $1$。

#### 说明/提示
在第一个样例中，乘积的最大值为 $2$。因此，我们可以删除前三个元素（得到数组 $[2]$），或者删除最后两个元素和一个第一个元素（也得到数组 $[2]$），或者删除最后两个元素（得到数组 $[1, 2]$）。因此，在第一个样例中，答案可以是 "3 0"、"1 2" 或 "0 2"。

在第二个样例中，乘积的最大值为 $1$。因此，我们可以删除所有元素，因为空数组的乘积为 $1$。所以答案是 "3 0"，但还有其他可能的答案。

在第三个样例中，我们可以删除数组的前两个元素。然后得到数组 $[-2, 2, -1]$。结果数组的乘积为 $(-2) \cdot 2 \cdot (-1) = 4$。这个值是可能得到的最大值。因此，对于这个样例，答案是 "2 0"。

### 算法分类
贪心、前缀和

### 题解分析与结论
题目要求从数组中删除前缀和后缀，使得剩余子数组的乘积最大。由于空数组的乘积为 $1$，因此我们需要确保剩余子数组的乘积不为负数或零。题解中常见的思路是通过前缀和统计负数和绝对值大于等于 $2$ 的元素数量，然后根据负数的奇偶性决定删除策略。

### 评分较高的题解
#### 1. 作者：Miraik (5星)
**关键亮点**：
- 使用前缀和统计负数和绝对值大于等于 $2$ 的元素数量。
- 通过奇偶性判断是否需要删除负数，确保乘积为正。
- 时间复杂度为 $O(n)$，代码简洁高效。

**核心代码**：
```cpp
void solve(int l,int r){
    if(l == r && a[l] < 0) return;
    int minus=0;
    for(int i=l;i<=r;i++){
        if(a[i] < 0) minus++;
    }
    if(minus%2){
        int tmp1=0,tmp2=0;
        for(int i=l;i<=r;i++) //找最左边的负数
            if(a[i] < 0){
                tmp1 = i;
                break;
            }
        for(int i=r;i>=l;i--) //找最右边的负数
            if(a[i] < 0){
                tmp2 = i;
                break;
            }
        if(f[r] - f[tmp1] > f[tmp2-1] - f[l-1]) l=tmp1+1;
        else r=tmp2-1;
    }
    if(f[r]-f[l-1] > f[ansr]-f[ansl-1])
        ansr=r,ansl=l;
}
```

#### 2. 作者：stripe_python (4星)
**关键亮点**：
- 将数组按 $0$ 分割成子段，分别处理每个子段。
- 使用前缀和统计负数和绝对值大于等于 $2$ 的元素数量。
- 通过比较删除左边或右边负数的损失，选择最优策略。

**核心代码**：
```cpp
void solve(int l, int r) {
    if (l > r || r > n) return;
    int neg = 0;
    for (int i = l; i <= r; i++) {
        if (a[i] < 0) neg++;
    }
    if (neg & 1) {
        int x = 0, y = 0;
        for (int i = l; i <= r; i++) {
            if (a[i] < 0) {x = i; break;}
        }
        for (int i = r; i >= l; i--) {
            if (a[i] < 0) {y = i; break;}
        }
        if (pre[r] - pre[x] > pre[y - 1] - pre[l - 1]) l = x + 1;
        else r = y - 1;
    } 
    if (pre[r] - pre[l - 1] > pre[resr] - pre[resl - 1]) resl = l, resr = r;
}
```

#### 3. 作者：GWBailang (4星)
**关键亮点**：
- 使用前缀和统计负数和绝对值大于等于 $2$ 的元素数量。
- 通过奇偶性判断是否需要删除负数，确保乘积为正。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
void hanshu(long long zuo,long long you){
    if(zuo>=you&&a[zuo]<=0)return;
    if((qzhf[you]-qzhf[zuo-1])%2==1){
        f1=zuo;f2=you;
        while(a[f1]>0)f1++;
        while(a[f2]>0)f2--;
        if(qzh2[you]-qzh2[f2-1]>qzh2[f1]-qzh2[zuo-1])zuo=f1+1;
        else you=f2-1;
    }
    if(qzh2[you]-qzh2[zuo-1]>da){
        da=qzh2[you]-qzh2[zuo-1];
        l=zuo;r=you;
    }
}
```

### 最优关键思路
1. **前缀和统计**：通过前缀和统计负数和绝对值大于等于 $2$ 的元素数量，便于快速计算区间内的负数和绝对值大于等于 $2$ 的元素数量。
2. **奇偶性判断**：根据区间内负数的奇偶性决定是否需要删除一个负数，确保乘积为正。
3. **删除策略**：通过比较删除左边或右边负数的损失，选择最优策略。

### 拓展思路
类似的问题可以扩展到其他需要统计区间内特定元素数量的场景，如统计区间内特定值的出现次数、区间内最大值等。

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3865 ST 表](https://www.luogu.com.cn/problem/P3865)

---
处理用时：45.15秒