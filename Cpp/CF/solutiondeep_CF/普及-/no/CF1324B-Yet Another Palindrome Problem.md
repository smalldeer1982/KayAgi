# 题目信息

# Yet Another Palindrome Problem

## 题目描述

You are given an array $ a $ consisting of $ n $ integers.

Your task is to determine if $ a $ has some subsequence of length at least $ 3 $ that is a palindrome.

Recall that an array $ b $ is called a subsequence of the array $ a $ if $ b $ can be obtained by removing some (possibly, zero) elements from $ a $ (not necessarily consecutive) without changing the order of remaining elements. For example, $ [2] $ , $ [1, 2, 1, 3] $ and $ [2, 3] $ are subsequences of $ [1, 2, 1, 3] $ , but $ [1, 1, 2] $ and $ [4] $ are not.

Also, recall that a palindrome is an array that reads the same backward as forward. In other words, the array $ a $ of length $ n $ is the palindrome if $ a_i = a_{n - i - 1} $ for all $ i $ from $ 1 $ to $ n $ . For example, arrays $ [1234] $ , $ [1, 2, 1] $ , $ [1, 3, 2, 2, 3, 1] $ and $ [10, 100, 10] $ are palindromes, but arrays $ [1, 2] $ and $ [1, 2, 3, 1] $ are not.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, the array $ a $ has a subsequence $ [1, 2, 1] $ which is a palindrome.

In the second test case of the example, the array $ a $ has two subsequences of length $ 3 $ which are palindromes: $ [2, 3, 2] $ and $ [2, 2, 2] $ .

In the third test case of the example, the array $ a $ has no subsequences of length at least $ 3 $ which are palindromes.

In the fourth test case of the example, the array $ a $ has one subsequence of length $ 4 $ which is a palindrome: $ [1, 2, 2, 1] $ (and has two subsequences of length $ 3 $ which are palindromes: both are $ [1, 2, 1] $ ).

In the fifth test case of the example, the array $ a $ has no subsequences of length at least $ 3 $ which are palindromes.

## 样例 #1

### 输入

```
5
3
1 2 1
5
1 2 2 3 2
3
1 1 2
4
1 2 2 1
10
1 1 2 2 3 3 4 4 5 5```

### 输出

```
YES
YES
NO
YES
NO```

# AI分析结果

### 题目内容
# 又一个回文问题

## 题目描述
给定一个由 $n$ 个整数组成的数组 $a$ 。

你的任务是判断 $a$ 是否存在长度至少为 $3$ 的回文子序列。

回想一下，如果数组 $b$ 可以通过从数组 $a$ 中删除一些（可能为零）元素（不一定连续）而不改变剩余元素的顺序得到，那么数组 $b$ 就被称为数组 $a$ 的子序列。例如，$[2]$ ，$[1, 2, 1, 3]$ 和 $[2, 3]$ 是 $[1, 2, 1, 3]$ 的子序列，但 $[1, 1, 2]$ 和 $[4]$ 不是。

同样，回想一下，回文是一个从后向前读和从前向后读都相同的数组。换句话说，长度为 $n$ 的数组 $a$ 是回文数组，当且仅当对于从 $1$ 到 $n$ 的所有 $i$ ，都有 $a_i = a_{n - i - 1}$ 。例如，数组 $[1234]$ ，$[1, 2, 1]$ ，$[1, 3, 2, 2, 3, 1]$ 和 $[10, 100, 10]$ 是回文数组，但数组 $[1, 2]$ 和 $[1, 2, 3, 1]$ 不是。

你必须回答 $t$ 个独立的测试用例。

## 说明/提示
在示例的第一个测试用例中，数组 $a$ 有一个子序列 $[1, 2, 1]$ ，它是回文的。

在示例的第二个测试用例中，数组 $a$ 有两个长度为 $3$ 的回文子序列：$[2, 3, 2]$ 和 $[2, 2, 2]$ 。

在示例的第三个测试用例中，数组 $a$ 没有长度至少为 $3$ 的回文子序列。

在示例的第四个测试用例中，数组 $a$ 有一个长度为 $4$ 的回文子序列：$[1, 2, 2, 1]$ （并且有两个长度为 $3$ 的回文子序列：都是 $[1, 2, 1]$ ）。

在示例的第五个测试用例中，数组 $a$ 没有长度至少为 $3$ 的回文子序列。

## 样例 #1
### 输入
```
5
3
1 2 1
5
1 2 2 3 2
3
1 1 2
4
1 2 2 1
10
1 1 2 2 3 3 4 4 5 5
```
### 输出
```
YES
YES
NO
YES
NO
```

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路大多围绕判断数组中是否存在满足条件的回文子序列展开。由于长度至少为3的回文子序列关键在于找到两个相同且间隔至少为1的元素（中间可任取一个元素构成回文），或者某个元素出现3次及以上。各题解主要差异在于实现方式和细节处理。部分题解考虑不全面被hack，后修正为同时考虑元素不连续出现两次及出现三次以上的情况。

### 所选的题解
- **作者：tuzhewen (5星)**
    - **关键亮点**：思路清晰，通过两个数组`vis1`和`vis2`分别统计每个数字出现的总次数以及不连续出现的次数，以此判断是否存在满足条件的回文子序列，代码简洁明了。
    - **重点代码**：
```cpp
int vis1[5005],vis2[5005];
//...
for(int i=1;i<=n;i++) {
    scanf("%d",&a[i]);
    vis1[a[i]]++;//计算每一个数字出现了多少次
    if(a[i]!=a[i-1]) vis2[a[i]]++;//计算不连续的数字出现了多少次
}
bool flag=false;
for(int i=1;i<=n;i++) {
    if(vis2[a[i]]>=2||vis1[a[i]]>=3) {
        flag=true;
        break;
    }
}
if(!flag) puts("NO");
else puts("YES");
```
核心实现思想：遍历数组统计各数字出现次数及不连续出现次数，再遍历判断是否满足回文子序列条件。

- **作者：Ignotus (4星)**
    - **关键亮点**：利用`pos`数组记录每个数第一次出现的位置，通过判断当前位置与第一次出现位置的距离是否大于1，来确定是否存在满足条件的回文子序列，逻辑清晰。
    - **重点代码**：
```cpp
int a[5010],pos[5010],T,n,flag;
//...
while(T--){
    flag=0;
    memset(pos, 0, sizeof pos);
    scanf("%d",&n);
    for(int i=1; i<=n; i++) scanf("%d",&a[i]);
    for(int i=1; i<=n; i++){
        if(!pos[a[i]]) pos[a[i]]=i;
        else{
            if(i-pos[a[i]]>1){
                flag=1;
                break;
            }
        }
    }
    if(flag) puts("YES");
    else puts("NO");
}
```
核心实现思想：遍历数组，若数字首次出现则记录位置，再次出现时判断距离是否大于1以确定是否有回文子序列。

- **作者：registerGen (4星)**
    - **关键亮点**：先指出只需考虑长度为3的回文子序列情况，通过`h`数组统计每个数出现次数，同时记录前一个数，判断当前数出现次数达到2且与前一个数不同或者出现次数达到3次及以上时存在回文子序列，思路直接，代码简洁。
    - **重点代码**：
```cpp
int n,a[N+10],h[N+10];
//...
while(T--){
    memset(h,0,sizeof(h));
    scanf("%d",&n);
    int tmp=0;
    bool ok=false;
    for(int i=1;i<=n;i++){
        int x;
        scanf("%d",&x);
        h[x]++;
        if(h[x]==2&&x!=tmp)ok=true;
        if(h[x]>=3)ok=true;
        tmp=x;
    }
    if(ok)puts("YES");
    else puts("NO");
}
```
核心实现思想：遍历数组统计各数出现次数，根据出现次数和与前一个数的关系判断是否存在回文子序列。

### 最优关键思路或技巧
利用数组统计元素出现次数及位置关系，快速判断是否存在满足条件的回文子序列。如通过记录元素首次出现位置判断是否不连续出现，或直接统计元素出现总次数判断是否达到3次及以上。

### 可拓展之处
此类题目可拓展到更复杂的子序列判断问题，如判断特定长度或特定模式的回文子序列。类似算法套路为通过数组或其他数据结构记录元素相关信息（出现次数、位置等），利用这些信息快速判断是否满足目标条件。

### 推荐洛谷题目
- [P1309 瑞士轮](https://www.luogu.com.cn/problem/P1309)：涉及到数据的排序与处理，与本题对数组元素的分析处理有相似之处。
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：通过特定方法统计数组中的逆序对数量，和本题一样需要对数组元素间的关系进行分析。
- [P1130 红牌](https://www.luogu.com.cn/problem/P1130)：判断字符串中是否存在满足特定条件的子串，类似本题判断数组中是否存在满足条件的子序列。 

---
处理用时：71.61秒