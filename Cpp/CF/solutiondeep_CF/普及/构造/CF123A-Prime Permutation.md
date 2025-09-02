# 题目信息

# Prime Permutation

## 题目描述

You are given a string $ s $ , consisting of small Latin letters. Let's denote the length of the string as $ |s| $ . The characters in the string are numbered starting from $ 1 $ .

Your task is to find out if it is possible to rearrange characters in string $ s $ so that for any prime number $ p<=|s| $ and for any integer $ i $ ranging from $ 1 $ to $ |s|/p $ (inclusive) the following condition was fulfilled $ s_{p}=s_{p×i} $ . If the answer is positive, find one way to rearrange the characters.

## 说明/提示

In the first sample any of the six possible strings will do: "abc", "acb", "bac", "bca", "cab" or "cba".

In the second sample no letter permutation will satisfy the condition at $ p=2 $ ( $ s_{2}=s_{4} $ ).

In the third test any string where character "y" doesn't occupy positions 2, 3, 4, 6 will be valid.

## 样例 #1

### 输入

```
abc
```

### 输出

```
YES
abc
```

## 样例 #2

### 输入

```
abcd
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
xxxyxxx
```

### 输出

```
YES
xxxxxxy
```

# AI分析结果

### 题目中文重写
## 质数排列

### 题目描述
给定一个由小写拉丁字母组成的字符串 $s$，记字符串的长度为 $|s|$，字符串中的字符从 $1$ 开始编号。

你的任务是判断是否可以重新排列字符串 $s$ 中的字符，使得对于任何小于等于 $|s|$ 的质数 $p$ 以及任何范围在 $1$ 到 $|s|/p$（包含两端）的整数 $i$，都满足 $s_{p}=s_{p×i}$。如果答案是肯定的，找出一种重新排列字符的方式。

### 说明/提示
- 在第一个样例中，六个可能的字符串 “abc”、“acb”、“bac”、“bca”、“cab” 或 “cba” 都符合要求。
- 在第二个样例中，没有字母排列能满足 $p = 2$ 时的条件（$s_{2}=s_{4}$）。
- 在第三个测试中，任何字符 “y” 不占据位置 2、3、4、6 的字符串都是有效的。

### 样例 #1
#### 输入
```
abc
```
#### 输出
```
YES
abc
```

### 样例 #2
#### 输入
```
abcd
```
#### 输出
```
NO
```

### 样例 #3
#### 输入
```
xxxyxxx
```
#### 输出
```
YES
xxxxxxy
```

### 综合分析与结论
这些题解的核心思路都是先分析出满足条件的字符串特征，即存在一个大集合（由合数和部分质数组成），大集合中的字符需相同，然后判断字符串中是否有足够数量的某个字符来填充这个大集合。

- **思路对比**：
    - Oscar12345 通过标记质数和倍数，计算大集合规模，找到满足条件的字符来构造解。
    - qwertim 和 __hjwucj__ 计算合数和小于 $\frac{|s|}{2}$ 的质数个数，判断出现次数最多的字符是否足够。
    - Lily_White 从字符集合的角度，将字符串分成大集合和小集合，用出现次数最多的字符填充大集合。
    - Rei_Sen 从图论和并查集的角度分析，最后简化为计算染色次数判断是否有解。
- **算法要点**：
    - 都需要统计字符出现次数。
    - 计算满足条件的大集合规模。
    - 判断是否有足够数量的字符填充大集合，若有则构造解。
- **解决难点**：
    - 准确找出大集合的元素，不同题解采用了不同方法，如标记倍数、判断质数等。
    - 合理构造满足条件的字符串。

### 所选题解
- **Oscar12345（5星）**
    - **关键亮点**：思路清晰，代码实现规范，通过预处理质数倍数标记，逐步计算大集合规模并构造解。
    - **核心代码**：
```cpp
void init ()
{
    memset ( maxPrime, -1, sizeof ( maxPrime ) );
    for ( int i = 2 ; i < MAX ; i++ )
    {
        if (~maxPrime[i]) continue;
        for ( int j = i*2 ; j < MAX ; j += i )
            maxPrime[j] = i;
    }
}
//...
int cnt = 2;
for ( int i = n ; i >= 2; i-- )
{
    if ( mark[i] && maxPrime[i] == -1 ) continue;
    if ( ~maxPrime[i] )
    {
        mark[i] = true;
        for ( int j = 2 ; j*j <= i ; j++ )
        {
            if ( i%j ) continue;
            mark[j] = mark[i/j] = true;
        }
    }
    else cnt++;
}
```
核心实现思想：先预处理每个数的最大质因数，然后遍历字符串长度，标记合数及其质因数，计算大集合规模。
- **qwertim（4星）**
    - **关键亮点**：思路简洁明了，代码使用了 `map` 统计字符出现次数，逻辑清晰。
    - **核心代码**：
```cpp
bool isprime(int x){
    int tmp=sqrt(x);
    fo(i,2,tmp)
        if(x%i==0)return 0;
    return 1;
}
//...
fo(i,2,s.size()){
    if(!isprime(i))b[i]=1,a++;//是合数
    else if(i<=s.size()/2)b[i]=1,a++;//是|s|/2及以下的质数
}
```
核心实现思想：通过判断质数和合数，标记满足条件的位置，统计大集合元素个数。
- **Lily_White（4星）**
    - **关键亮点**：从集合的角度分析问题，使用 `vector` 存储大集合元素，代码结构清晰。
    - **核心代码**：
```cpp
for (int i = 2; i <= n; i++){
    if (i == 1) continue;
    if (!mark[i]) {
        mark[i] = true;
        if (n / i <= 1) continue;			
        pos.pb(i);
        for (int j = i; j <= n; j += i) {
            if (!mark[j]) {
                mark[j] = true;
                pos.pb(j);
            }
        }
    }
}
```
核心实现思想：遍历字符串长度，标记未处理的数及其倍数，将其加入大集合。

### 最优关键思路或技巧
- 分析出字符串可分为大集合和小集合，大集合元素需相同，简化问题。
- 利用质数和合数的性质计算大集合规模。
- 使用 `map` 统计字符出现次数，方便查找出现次数最多的字符。

### 可拓展之处
同类型题可能会改变条件，如对不同集合的字符有更多限制，或要求输出所有可能的排列。类似算法套路可用于解决染色问题、集合划分问题等。

### 洛谷题目推荐
- P1217 [USACO1.5]回文质数 Prime Palindromes
- P1075 [NOIP2012 普及组] 质因数分解
- P1579 哥德巴赫猜想（升级版）

---
处理用时：35.97秒