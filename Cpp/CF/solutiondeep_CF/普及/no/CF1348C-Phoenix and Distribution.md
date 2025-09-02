# 题目信息

# Phoenix and Distribution

## 题目描述

Phoenix has a string $ s $ consisting of lowercase Latin letters. He wants to distribute all the letters of his string into $ k $ non-empty strings $ a_1, a_2, \dots, a_k $ such that every letter of $ s $ goes to exactly one of the strings $ a_i $ . The strings $ a_i $ do not need to be substrings of $ s $ . Phoenix can distribute letters of $ s $ and rearrange the letters within each string $ a_i $ however he wants.

For example, if $ s =  $ baba and $ k=2 $ , Phoenix may distribute the letters of his string in many ways, such as:

- ba and ba
- a and abb
- ab and ab
- aa and bb

But these ways are invalid:

- baa and ba
- b and ba
- baba and empty string ( $ a_i $ should be non-empty)

Phoenix wants to distribute the letters of his string $ s $ into $ k $ strings $ a_1, a_2, \dots, a_k $ to minimize the lexicographically maximum string among them, i. e. minimize $ max(a_1, a_2, \dots,       a_k) $ . Help him find the optimal distribution and print the minimal possible value of $ max(a_1, a_2, \dots, a_k) $ .

String $ x $ is lexicographically less than string $ y $ if either $ x $ is a prefix of $ y $ and $ x \ne y $ , or there exists an index $ i $ ( $ 1 \le i \le min(|x|, |y|)) $ such that $ x_i $ &lt; $ y_i $ and for every $ j $ $ (1 \le j       < i) $ $ x_j = y_j $ . Here $ |x| $ denotes the length of the string $ x $ .

## 说明/提示

In the first test case, one optimal solution is to distribute baba into ab and ab.

In the second test case, one optimal solution is to distribute baacb into abbc and a.

In the third test case, one optimal solution is to distribute baacb into ac, ab, and b.

In the fourth test case, one optimal solution is to distribute aaaaa into aa, aa, and a.

In the fifth test case, one optimal solution is to distribute aaxxzz into az, az, x, and x.

In the sixth test case, one optimal solution is to distribute phoenix into ehinopx.

## 样例 #1

### 输入

```
6
4 2
baba
5 2
baacb
5 3
baacb
5 3
aaaaa
6 4
aaxxzz
7 1
phoenix```

### 输出

```
ab
abbc
b
aa
x
ehinopx```

# AI分析结果

### 题目内容重写
Phoenix有一个由小写拉丁字母组成的字符串$s$。他想要将字符串中的所有字母分配到$k$个非空字符串$a_1, a_2, \dots, a_k$中，使得$s$中的每个字母恰好被分配到一个字符串$a_i$中。字符串$a_i$不需要是$s$的子串。Phoenix可以随意分配$s$中的字母，并可以在每个字符串$a_i$中重新排列字母。

例如，如果$s = \text{baba}$且$k=2$，Phoenix可以以多种方式分配字母，例如：
- ba和ba
- a和abb
- ab和ab
- aa和bb

但以下分配方式无效：
- baa和ba
- b和ba
- baba和空字符串（$a_i$必须非空）

Phoenix希望将字符串$s$中的字母分配到$k$个字符串$a_1, a_2, \dots, a_k$中，使得这些字符串中字典序最大的字符串尽可能小，即最小化$max(a_1, a_2, \dots, a_k)$。请帮助他找到最优的分配方式，并输出最小的$max(a_1, a_2, \dots, a_k)$。

字符串$x$字典序小于字符串$y$，如果$x$是$y$的前缀且$x \ne y$，或者存在一个索引$i$（$1 \le i \le min(|x|, |y|)$）使得$x_i < y_i$，且对于所有$j$（$1 \le j < i$）有$x_j = y_j$。这里$|x|$表示字符串$x$的长度。

### 算法分类
贪心、字符串、排序

### 题解分析与结论
题目要求将字符串$s$中的字母分配到$k$个非空字符串中，使得这些字符串中字典序最大的字符串尽可能小。核心思路是通过贪心策略，尽可能将字典序较小的字母放在前面，从而最小化最大字符串的字典序。

#### 关键思路：
1. **排序**：首先对字符串$s$进行排序，使得字母按字典序排列。
2. **分配策略**：
   - 如果前$k$个字符不完全相同，则直接将第$k$个字符作为最大字符串。
   - 如果前$k$个字符相同，则根据剩余字符的情况决定是否将所有剩余字符接到第一个字符串后面，或者平均分配。

#### 难点对比：
- **WYXkk**的题解简洁明了，直接通过排序和简单的条件判断得出结果，代码简洁高效。
- **wsyhb**的题解详细分析了不同情况，并提供了两种策略的实现，代码较为复杂但逻辑清晰。
- **huayucaiji**的题解通过具体样例分析，提出了“一条龙”和“斗地主发牌”两种策略，并给出了详细的实现代码。

### 所选高分题解
#### 1. WYXkk (5星)
**关键亮点**：代码简洁，逻辑清晰，直接通过排序和条件判断得出结果。
**代码核心**：
```cpp
rd(n);rd(k);
scanf("%s",s+1);
sort(s+1,s+n+1);
if(s[k]!=s[1]) printf("%c\n",s[k]);
else if(s[n]!=s[k+1]) printf("%c%s\n",s[1],s+k+1);
else {putchar(s[1]);F(i,1,(n-1)/k) putchar(s[k+1]);puts("");}
```

#### 2. wsyhb (4星)
**关键亮点**：详细分析了不同情况，并提供了两种策略的实现，逻辑清晰。
**代码核心**：
```cpp
if(s[1]==s[k])
{
    ans+=s[1];
    for(int i=k+1;i<=n;++i)
        ans+=s[i];
}
else
    ans+=s[k];
string Max="";
for(int i=1;i<=k;++i)
{
    string now="";
    for(int j=i;j<=n;j+=k)
        now+=s[j];
    Max=max(Max,now);
}
ans=min(ans,Max);
```

#### 3. huayucaiji (4星)
**关键亮点**：通过具体样例分析，提出了“一条龙”和“斗地主发牌”两种策略，并给出了详细的实现代码。
**代码核心**：
```cpp
if(s[1]!=s[k]) {
    cout<<s[k]<<endl;
}
else {
    if(q==1) {
        int t=1;
        for(;now<=n;now++) {
            a[t]+=s[now];
            t++;
            if(t==k+1) {
                t=1;
            }
        }
    }
    else {
        for(;now<=n;now++) {
            a[1]+=s[now];
        }
    }
    string ans=a[1];
    for(int i=2;i<=k;i++) {
        if(a[i]>ans) {
            ans=a[i];
        }
    }
    cout<<ans<<endl;
}
```

### 最优关键思路
1. **排序**：首先对字符串进行排序，确保字母按字典序排列。
2. **贪心分配**：根据前$k$个字符是否相同，决定是否将所有剩余字符接到第一个字符串后面，或者平均分配。

### 拓展思路
类似的问题可以扩展到其他分配问题，如将数字分配到多个集合中，使得集合中的最大值最小化。这类问题通常可以通过排序和贪心策略来解决。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：34.33秒