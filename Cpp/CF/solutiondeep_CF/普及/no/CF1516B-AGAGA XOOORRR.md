# 题目信息

# AGAGA XOOORRR

## 题目描述

Baby Ehab is known for his love for a certain operation. He has an array $ a $ of length $ n $ , and he decided to keep doing the following operation on it:

- he picks $ 2 $ adjacent elements; he then removes them and places a single integer in their place: their [bitwise XOR](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). Note that the length of the array decreases by one.

Now he asks you if he can make all elements of the array equal. Since babies like to make your life harder, he requires that you leave at least $ 2 $ elements remaining.

## 说明/提示

In the first sample, he can remove the first $ 2 $ elements, $ 0 $ and $ 2 $ , and replace them by $ 0 \oplus 2=2 $ . The array will be $ [2,2] $ , so all the elements are equal.

In the second sample, there's no way to make all the elements equal.

## 样例 #1

### 输入

```
2
3
0 2 2
4
2 3 1 10```

### 输出

```
YES
NO```

# AI分析结果

### 题目重写
Baby Ehab 以对某种操作的喜爱而闻名。他有一个长度为 $n$ 的数组 $a$，他决定对其进行以下操作：

- 他选择 2 个相邻的元素，然后将它们删除，并在它们的位置插入一个整数：它们的 [按位异或](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。注意，数组的长度会减少 1。

现在他问你，是否可以使数组中的所有元素相等。由于婴儿喜欢让你的生活变得更难，他要求你至少留下 2 个元素。

### 说明/提示
在第一个样例中，他可以删除前 2 个元素 $0$ 和 $2$，并用 $0 \oplus 2=2$ 替换它们。数组将变为 $[2,2]$，因此所有元素都相等。

在第二个样例中，无法使所有元素相等。

### 样例 #1
#### 输入
```
2
3
0 2 2
4
2 3 1 10
```
#### 输出
```
YES
NO
```

### 算法分类
位运算、前缀和

### 题解分析与结论
本题的核心在于通过相邻元素的异或操作，最终使数组中的所有元素相等，且至少保留两个元素。多个题解都围绕以下两个关键点展开：
1. **全局异或和的性质**：如果最终所有元素相等，那么整个数组的异或和要么为 0（偶数段），要么为最终的元素值（奇数段）。
2. **分段异或和**：通过前缀和的方式，判断是否可以将数组划分为若干段，每段的异或和相等。

### 精选题解
#### 1. 江户川·萝卜 (5星)
**关键亮点**：
- 利用全局异或和的性质，直接判断是否可以划分为偶数段或奇数段。
- 代码简洁，时间复杂度为 $O(tn)$，适合大规模数据。

**核心代码**：
```cpp
int x=0;
for(int i=1;i<=n;i++) scanf("%d",&a[i]),x^=a[i];
if(x==0) puts("YES");
else{
    int cnt=0,cur=0;
    for(int i=1;i<=n;i++){
        cur^=a[i];
        if(cur==x) cnt++,cur=0;
    }
    if(cnt>=2) puts("YES");
    else puts("NO");
}
```
**实现思想**：通过计算全局异或和，判断是否可以划分为多个异或和相等的段。

#### 2. Cry_For_theMoon (4星)
**关键亮点**：
- 详细分析了全局异或和与分段异或和的关系，给出了清晰的证明。
- 代码实现较为直观，适合理解异或操作的性质。

**核心代码**：
```cpp
if(!sum[n]){
    printf("YES");continue;
}
rep(i,2,n){
    rep(j,i,n){
        if((sum[j]^sum[i-1])==sum[i-1] && (sum[n]^sum[j])==sum[i-1]){
            goto OK;
        }    
    }
}
printf("NO");continue;
OK:printf("YES");
```
**实现思想**：通过枚举分段点，判断是否可以划分为三段异或和相等的段。

#### 3. Engulf (4星)
**关键亮点**：
- 直接利用异或和的性质，判断是否可以划分为偶数段或奇数段。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
if (x == 0) {puts("YES"); continue;}
int cnt = 0, cur = 0;
for (int i = 0; i < n; i ++ ){
    cur ^= a[i];
    if (cur == x) {cur = 0; cnt ++ ;}
}
puts(cnt >= 2 ? "YES" : "NO");
```
**实现思想**：通过计算异或和，判断是否可以划分为多个异或和相等的段。

### 最优关键思路
1. **全局异或和的性质**：如果最终所有元素相等，全局异或和要么为 0，要么为最终的元素值。
2. **分段异或和**：通过前缀和的方式，判断是否可以将数组划分为若干段，每段的异或和相等。

### 可拓展之处
- 类似的问题可以扩展到其他位操作，如按位与、按位或等。
- 可以进一步优化时间复杂度，考虑更高效的分段判断方法。

### 推荐题目
1. [CF1516B - AGAGA XOOORRR](https://www.luogu.com.cn/problem/CF1516B)
2. [CF1516C - Baby Ehab Plays with Permutations](https://www.luogu.com.cn/problem/CF1516C)
3. [CF1516D - Cut](https://www.luogu.com.cn/problem/CF1516D)

### 个人心得摘录
- **江户川·萝卜**：通过全局异或和的性质，直接判断是否可以划分为偶数段或奇数段，代码简洁高效。
- **Cry_For_theMoon**：详细分析了全局异或和与分段异或和的关系，给出了清晰的证明，代码实现较为直观。
- **Engulf**：直接利用异或和的性质，判断是否可以划分为偶数段或奇数段，代码简洁，逻辑清晰。

---
处理用时：32.24秒