# 题目信息

# Vus the Cossack and Strings

## 题目描述

Vus the Cossack has two binary strings, that is, strings that consist only of "0" and "1". We call these strings $ a $ and $ b $ . It is known that $ |b| \leq |a| $ , that is, the length of $ b $ is at most the length of $ a $ .

The Cossack considers every substring of length $ |b| $ in string $ a $ . Let's call this substring $ c $ . He matches the corresponding characters in $ b $ and $ c $ , after which he counts the number of positions where the two strings are different. We call this function $ f(b, c) $ .

For example, let $ b = 00110 $ , and $ c = 11000 $ . In these strings, the first, second, third and fourth positions are different.

Vus the Cossack counts the number of such substrings $ c $ such that $ f(b, c) $ is even.

For example, let $ a = 01100010 $ and $ b = 00110 $ . $ a $ has four substrings of the length $ |b| $ : $ 01100 $ , $ 11000 $ , $ 10001 $ , $ 00010 $ .

- $ f(00110, 01100) = 2 $ ;
- $ f(00110, 11000) = 4 $ ;
- $ f(00110, 10001) = 4 $ ;
- $ f(00110, 00010) = 1 $ .

Since in three substrings, $ f(b, c) $ is even, the answer is $ 3 $ .

Vus can not find the answer for big strings. That is why he is asking you to help him.

## 说明/提示

The first example is explained in the legend.

In the second example, there are five substrings that satisfy us: $ 1010 $ , $ 0101 $ , $ 1111 $ , $ 1111 $ .

## 样例 #1

### 输入

```
01100010
00110
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1010111110
0110
```

### 输出

```
4
```

# AI分析结果

### 题目翻译
# Vus 哥萨克人与字符串

## 题目描述
Vus 哥萨克人有两个二进制字符串，即仅由 "0" 和 "1" 组成的字符串。我们将这两个字符串称为 $a$ 和 $b$。已知 $|b| \leq |a|$，即 $b$ 的长度至多为 $a$ 的长度。

哥萨克人会考虑字符串 $a$ 中每个长度为 $|b|$ 的子串。我们将这个子串称为 $c$。他会对比 $b$ 和 $c$ 中对应的字符，然后统计两个字符串不同的位置数量。我们将这个函数称为 $f(b, c)$。

例如，设 $b = 00110$，$c = 11000$。在这两个字符串中，第一、二、三、四个位置不同。

Vus 哥萨克人会统计满足 $f(b, c)$ 为偶数的子串 $c$ 的数量。

例如，设 $a = 01100010$，$b = 00110$。$a$ 有四个长度为 $|b|$ 的子串：$01100$、$11000$、$10001$、$00010$。
- $f(00110, 01100) = 2$；
- $f(00110, 11000) = 4$；
- $f(00110, 10001) = 4$；
- $f(00110, 00010) = 1$。

由于在三个子串中，$f(b, c)$ 为偶数，所以答案是 $3$。

Vus 无法为长字符串找到答案。这就是他请求你帮助的原因。

## 说明/提示
第一个样例在题目描述中已解释。

在第二个样例中，有五个满足条件的子串：$1010$、$0101$、$1111$、$1111$。

## 样例 #1
### 输入
```
01100010
00110
```
### 输出
```
3
```

## 样例 #2
### 输入
```
1010111110
0110
```
### 输出
```
4
```

### 算法分类
字符串

### 综合分析与结论
这些题解的核心都是解决在字符串 $a$ 中找出长度为 $|b|$ 且与 $b$ 的差异度为偶数的子串数量的问题。各题解思路有所不同：
- **hsfzLZH1**：通过固定 $a$ 滑动 $b$，分析相邻子串差异度奇偶性的变化规律，利用规律维护差异度奇偶性并统计答案。
- **世末OIer**：观察到字符串 $a$ 中相邻位不同会影响答案，使用后缀和优化枚举过程。
- **wanghaoran00**：利用前缀和维护 $a$ 中 $1$ 的个数，根据 $1$ 的个数判断差异度奇偶性。
- **RemiliaScar1et**：发现两个等长串差异度奇偶性与两串中 $1$ 的个数奇偶性有关，通过前缀和统计并枚举判断。
- **cbyybccbyybc**：与 wanghaoran00 思路类似，用前缀和维护区间 $1$ 的个数，枚举区间判断奇偶性。
- **brealid**：证明了 $f(a,b)$ 的奇偶性与两串中 $1$ 的个数奇偶性的关系，使用滚动思想辅助计算。

### 所选题解
- **hsfzLZH1（5星）**
  - 关键亮点：思路清晰，详细分析了相邻子串差异度奇偶性的变化规律，代码实现简洁高效。
  - 重点代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1000010;
int l1,l2,nww,cnt,ans;
char a[maxn],b[maxn];
int main()
{
    scanf("%s%s",a+1,b+1);
    l1=strlen(a+1);l2=strlen(b+1);
    for(int i=1;i<=l2;i++)if(a[i]!=b[i])nww++;
    for(int i=1;i<l2;i++)if(b[i]!=b[i+1])cnt++;
    cnt=cnt%2;
    if(nww%2==0)ans++;
    for(int l=1,r=l2;r<l1;l++,r++)
    {
        if(a[l]!=b[1])nww++;
        if(a[r+1]!=b[l2])nww++;
        nww+=cnt;
        if(nww%2==0)ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```
核心实现思想：先计算初始子串与 $b$ 的差异度，再统计 $b$ 中相邻位不同的数量，然后通过滑动子串，根据首尾字符和中间部分的变化维护差异度奇偶性，统计满足条件的子串数量。

### 最优关键思路或技巧
- 利用前缀和或后缀和优化枚举过程，将时间复杂度从 $O(n^2)$ 降低到 $O(n)$。
- 分析相邻子串之间的关系，找出差异度奇偶性的变化规律，避免重复计算。

### 可拓展之处
同类型题目可能会有不同的字符串操作或条件限制，如字符串中字符种类增多、差异度计算方式改变等。类似算法套路可用于处理字符串匹配、子串统计等问题，关键在于找出规律并利用合适的数据结构优化计算。

### 推荐题目
- [P1125 笨小猴](https://www.luogu.com.cn/problem/P1125)
- [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)
- [P5733 【深基6.例1】自动修正](https://www.luogu.com.cn/problem/P5733)

### 个人心得摘录与总结
- **cbyybccbyybc**：在考场上没推出公式，回来后发现题目其实很简单。总结是遇到难题不要慌张，考完后要深入思考。 

---
处理用时：42.97秒