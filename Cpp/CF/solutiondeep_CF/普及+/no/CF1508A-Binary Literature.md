# 题目信息

# Binary Literature

## 题目描述

A bitstring is a string that contains only the characters 0 and 1.

Koyomi Kanou is working hard towards her dream of becoming a writer. To practice, she decided to participate in the Binary Novel Writing Contest. The writing prompt for the contest consists of three bitstrings of length $ 2n $ . A valid novel for the contest is a bitstring of length at most $ 3n $ that contains at least two of the three given strings as subsequences.

Koyomi has just received the three prompt strings from the contest organizers. Help her write a valid novel for the contest.

A string $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero) characters.

## 说明/提示

In the first test case, the bitstrings 00 and 01 are subsequences of the output string: 010 and 010. Note that 11 is not a subsequence of the output string, but this is not required.

In the second test case all three input strings are subsequences of the output string: 011001010, 011001010 and 011001010.

## 样例 #1

### 输入

```
2
1
00
11
01
3
011001
111010
010001```

### 输出

```
010
011001010```

# AI分析结果

### 题目内容（中文重写）
# 二进制文学

## 题目描述
一个二进制串是只包含字符 0 和 1 的字符串。

神尾小夜子正在为实现成为作家的梦想而努力。为了练习，她决定参加二进制小说写作比赛。比赛的写作提示由三个长度为 $2n$ 的二进制串组成。比赛的有效小说是一个长度至多为 $3n$ 的二进制串，且该串至少包含三个给定字符串中的两个作为子序列。

神尾小夜子刚刚从比赛组织者那里收到了三个提示字符串。请帮助她写出一篇比赛的有效小说。

如果字符串 $a$ 可以通过删除字符串 $b$ 中的若干（可能为零）字符得到，那么字符串 $a$ 是字符串 $b$ 的子序列。

## 说明/提示
在第一个测试用例中，二进制串 00 和 01 是输出字符串的子序列：010 和 010。请注意，11 不是输出字符串的子序列，但这不是必需的。

在第二个测试用例中，所有三个输入字符串都是输出字符串的子序列：011001010、011001010 和 011001010。

## 样例 #1

### 输入
```
2
1
00
11
01
3
011001
111010
010001
```

### 输出
```
010
011001010
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是基于构造的方法来解决问题。由于要构造一个长度不超过 $3n$ 的二进制串，且使其至少包含三个给定长度为 $2n$ 的二进制串中的两个作为子序列，关键在于利用长度为 $2n$ 的二进制串中 0 或 1 的数量至少为 $n$ 这一性质，结合鸽巢原理，找到两个具有相同特征（0 或 1 的数量不少于 $n$）的字符串进行构造。

不同题解的区别在于具体的构造方式和实现细节：
- **syksykCCC**：理论阐述了构造的思路，指出必然能构造出 $3n$ 的合法方案，但未给出具体代码实现。
- **Light_snow**：逐位确定构造的字符串，通过维护指针和匹配子序列长度，保证每次扩展至少有两个指针右移，从而证明构造的字符串长度不超过 $3n$，并给出了完整代码。
- **RedreamMer**：找到两个 0 或 1 数量不少于 $n$ 的字符串，将相同数码合并，其余暴力合并，给出了代码实现。
- **封禁用户**：定义 0 串和 1 串，根据鸽巢原理找到两个同类型的字符串，通过维护指针进行构造，并证明了构造的字符串长度在 $3n$ 之内，给出了代码。
- **Cutest_Junior**：从理论上分析了构造最短母串与最长公共子序列的关系，通过找到两个最大公共子序列长度大于等于 $n$ 的字符串进行构造，给出了代码。
- **氧少Kevin**：提出找到两个 0 或 1 数量较多的字符串，将其中一个的 0 或 1 穿插到另一个中进行构造，但未给出代码。
- **Little09**：指出可将两个 0 或 1 个数过半的字符串拼在一起，保留 0 或 1，将 1 或 0 插到空里，给出了拼接的代码片段。
- **PPL_**：通过检查两个字符串 0 或 1 的数量是否都不少于 $n$，若满足则进行构造，给出了代码。

### 所选题解
- **Light_snow（4星）**
  - **关键亮点**：思路清晰，逐位构造的方法易于理解，代码实现简洁明了，通过指针移动和子序列长度的维护，有效控制了构造字符串的长度。
  - **个人心得**：无

### 重点代码
```c++
#include<iostream>
#include<cstdio>
#define ll long long 
#define N 300005

char a[N],b[N],c[N];
int la,lb,lc;
int n;
int T;

int main(){
    scanf("%d",&T);
    while(T -- ){
        scanf("%d",&n);
        scanf("%s",a + 1);
        scanf("%s",b + 1);
        scanf("%s",c + 1);
        la = lb = lc = 1;
        while(la <= 2 * n && lb <= 2 * n && lc <= 2 * n){
            int to = (a[la] - '0' + b[lb] - '0' + c[lc] - '0');
            to = (to >= 2) ? 1 : 0;
            std::cout<<to;
            if(a[la] == '0' + to)
            la ++ ;
            if(b[lb] == '0' + to)
            lb ++ ;
            if(c[lc] == '0' + to)
            lc ++ ;
        } 
        if(la == 2 * n + 1){
            if(lb > lc)
            for(int i = lb;i <= 2 * n;++i)
            std::cout<<b[i];	
            else
            for(int i = lc;i <= 2 * n;++i)
            std::cout<<c[i];	
        }
        if(lb == 2 * n + 1){
            if(la > lc)
            for(int i = la;i <= 2 * n;++i)
            std::cout<<a[i];	
            else
            for(int i = lc;i <= 2 * n;++i)
            std::cout<<c[i];
        }
        if(lc == 2 * n + 1){
            if(lb > la)
            for(int i = lb;i <= 2 * n;++i)
            std::cout<<b[i];	
            else
            for(int i = la;i <= 2 * n;++i)
            std::cout<<a[i];
        }				
        puts("");
    }
}
```
**核心实现思想**：逐位确定构造的字符串 $S$，每次扩展时选择在 $a[la + 1],b[lb + 1],c[lc + 1]$ 中至少出现两次的字符作为 $S$ 的下一位，并将出现该字符的字符串指针右移。当有一个字符串完全成为 $S$ 的子序列后，在剩下的两个字符串中选取已经匹配位数最多的并输出其剩下的项。

### 最优关键思路或技巧
- 利用长度为 $2n$ 的二进制串中 0 或 1 的数量至少为 $n$ 这一性质，结合鸽巢原理，找到两个具有相同特征的字符串进行构造。
- 逐位构造字符串，通过维护指针和匹配子序列长度，保证构造的字符串长度不超过 $3n$。

### 可拓展之处
同类型题或类似算法套路：在构造类题目中，常常需要利用一些特殊性质和原理（如鸽巢原理）来找到构造的方向，然后通过合理的方法（如逐位构造、合并等）来实现构造。例如，在构造满足一定条件的序列、图形等问题中都可以运用类似的思路。

### 推荐洛谷题目
- P1090 [NOIP2004 提高组] 合并果子（贪心、构造）
- P1223 排队接水（贪心、构造）
- P1803 凌乱的yyy / 线段覆盖（贪心、构造）

---
处理用时：54.00秒