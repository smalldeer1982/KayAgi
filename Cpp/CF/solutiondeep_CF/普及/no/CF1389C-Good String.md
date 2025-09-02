# 题目信息

# Good String

## 题目描述

Let's call left cyclic shift of some string $ t_1 t_2 t_3 \dots t_{n - 1} t_n $ as string $ t_2 t_3 \dots t_{n - 1} t_n t_1 $ .

Analogically, let's call right cyclic shift of string $ t $ as string $ t_n t_1 t_2       t_3 \dots t_{n - 1} $ .

Let's say string $ t $ is good if its left cyclic shift is equal to its right cyclic shift.

You are given string $ s $ which consists of digits 0–9.

What is the minimum number of characters you need to erase from $ s $ to make it good?

## 说明/提示

In the first test case, you can erase any $ 3 $ characters, for example, the $ 1 $ -st, the $ 3 $ -rd, and the $ 4 $ -th. You'll get string 51 and it is good.

In the second test case, we can erase all characters except 0: the remaining string is 0000 and it's good.

In the third test case, the given string $ s $ is already good.

## 样例 #1

### 输入

```
3
95831
100120013
252525252525```

### 输出

```
3
5
0```

# AI分析结果

### 题目翻译
#### Good String

**题目描述**

我们称字符串 $t_1 t_2 t_3 \dots t_{n - 1} t_n$ 的左循环移位为字符串 $t_2 t_3 \dots t_{n - 1} t_n t_1$。

类似地，我们称字符串 $t$ 的右循环移位为字符串 $t_n t_1 t_2 t_3 \dots t_{n - 1}$。

我们称字符串 $t$ 是好的，如果它的左循环移位等于它的右循环移位。

给定一个由数字 0–9 组成的字符串 $s$，你需要删除最少的字符使得 $s$ 成为好的字符串。

**说明/提示**

在第一个测试用例中，你可以删除任意 3 个字符，例如第 1 个、第 3 个和第 4 个字符。你将得到字符串 51，它是好的。

在第二个测试用例中，我们可以删除所有字符，除了 0：剩下的字符串是 0000，它是好的。

在第三个测试用例中，给定的字符串 $s$ 已经是好的。

**样例 #1**

**输入**
```
3
95831
100120013
252525252525
```

**输出**
```
3
5
0
```

### 算法分类
字符串、枚举

### 题解分析与结论
题目要求通过删除最少的字符使得字符串的左循环移位等于右循环移位。经过分析，满足条件的字符串只能是以下两种形式：
1. 由单一字符组成的字符串（如 "AAAAA"）。
2. 由两种字符交替组成的字符串，且长度为偶数（如 "ABABAB"）。

各题解的思路基本一致，都是通过枚举所有可能的字符组合（0-9），然后计算需要删除的字符数，最终取最小值。不同题解在实现细节上有所差异，如剪枝优化、贪心策略等。

### 精选题解
#### 1. 作者：Skies (4星)
**关键亮点**：
- 通过记录每个数字出现的位置，使用二分查找优化搜索过程。
- 对两种情况进行分别处理，代码结构清晰。

**核心代码**：
```cpp
int _find(int num,int x) {
    int l=0,r=s[num].size();
    while(l<r) {
        int mid=(l+r)>>1;
        if(s[num][mid]<=x) l=mid+1;
        else r=mid;
    }
    if(r==s[num].size()) return -1;
    else return s[num][r];
}
```
**实现思想**：通过二分查找快速定位字符的位置，减少搜索时间。

#### 2. 作者：Fairicle (4星)
**关键亮点**：
- 使用二维数组记录字符交替出现的次数，避免重复计算。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
for(ri i=1;i<=len;++i){
    int k=ch[i]-'0';
    for(ri j=0;j<=9;++j){
        if(j==k) continue;
        if(p[j][k]%2!=0) p[j][k]++;
        if(p[k][j]%2==0) p[k][j]++;
    }
}
```
**实现思想**：通过二维数组记录字符交替出现的次数，避免重复计算，提高效率。

#### 3. 作者：Ericby666 (4星)
**关键亮点**：
- 直接枚举所有可能的字符组合，使用贪心策略计算最大匹配长度。
- 代码简洁，易于理解。

**核心代码**：
```cpp
for(int k=0;k<len;k++)
    if((now%2==0 && s[k]==i) || (now%2==1 && s[k]==j))
        now++;
if(now%2==1 && i!=j) now--;
ans=max(ans,now);
```
**实现思想**：通过贪心策略计算最大匹配长度，确保删除的字符数最少。

### 最优关键思路与技巧
- **枚举与剪枝**：通过枚举所有可能的字符组合，结合剪枝策略减少不必要的计算。
- **贪心策略**：在计算最大匹配长度时，使用贪心策略确保删除的字符数最少。
- **二分查找优化**：通过二分查找快速定位字符的位置，减少搜索时间。

### 可拓展之处
- **类似题目**：可以扩展到更复杂的字符串操作问题，如字符串的循环移位、字符串的匹配等。
- **算法套路**：枚举与剪枝、贪心策略、二分查找等技巧在其他字符串问题中也有广泛应用。

### 推荐题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)
3. [P3371 【模板】字符串的最小表示法](https://www.luogu.com.cn/problem/P3371)

---
处理用时：34.34秒