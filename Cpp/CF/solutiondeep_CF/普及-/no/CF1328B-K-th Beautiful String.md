# 题目信息

# K-th Beautiful String

## 题目描述

For the given integer $ n $ ( $ n > 2 $ ) let's write down all the strings of length $ n $ which contain $ n-2 $ letters 'a' and two letters 'b' in lexicographical (alphabetical) order.

Recall that the string $ s $ of length $ n $ is lexicographically less than string $ t $ of length $ n $ , if there exists such $ i $ ( $ 1 \le i \le n $ ), that $ s_i < t_i $ , and for any $ j $ ( $ 1 \le j < i $ ) $ s_j = t_j $ . The lexicographic comparison of strings is implemented by the operator &lt; in modern programming languages.

For example, if $ n=5 $ the strings are (the order does matter):

1. aaabb
2. aabab
3. aabba
4. abaab
5. ababa
6. abbaa
7. baaab
8. baaba
9. babaa
10. bbaaa

It is easy to show that such a list of strings will contain exactly $ \frac{n \cdot (n-1)}{2} $ strings.

You are given $ n $ ( $ n > 2 $ ) and $ k $ ( $ 1 \le k \le \frac{n \cdot (n-1)}{2} $ ). Print the $ k $ -th string from the list.

## 样例 #1

### 输入

```
7
5 1
5 2
5 8
5 10
3 1
3 2
20 100```

### 输出

```
aaabb
aabab
baaba
bbaaa
abb
bab
aaaaabaaaaabaaaaaaaa```

# AI分析结果

### 题目内容
# K-th Beautiful String

## 题目描述
对于给定的整数 $n$（$n > 2$），我们按字典序（字母顺序）写下所有长度为 $n$ 的字符串，这些字符串包含 $n - 2$ 个字母 'a' 和两个字母 'b'。

回顾一下，长度为 $n$ 的字符串 $s$ 在字典序上小于长度为 $n$ 的字符串 $t$，如果存在这样的 $i$（$1 \leq i \leq n$），使得 $s_i < t_i$，并且对于任何 $j$（$1 \leq j < i$），$s_j = t_j$。现代编程语言中通过运算符 `<` 实现字符串的字典序比较。

例如，如果 $n = 5$，这些字符串（顺序很重要）为：
1. aaabb
2. aabab
3. aabba
4. abaab
5. ababa
6. abbaa
7. baaab
8. baaba
9. babaa
10. bbaaa

很容易证明这样的字符串列表将恰好包含 $\frac{n \cdot (n - 1)}{2}$ 个字符串。

给定 $n$（$n > 2$）和 $k$（$1 \leq k \leq \frac{n \cdot (n - 1)}{2}$）。打印列表中的第 $k$ 个字符串。

## 样例 #1
### 输入
```
7
5 1
5 2
5 8
5 10
3 1
3 2
20 100
```
### 输出
```
aaabb
aabab
baaba
bbaaa
abb
bab
aaaaabaaaaabaaaaaaaa
```

### 算法分类
数学

### 综合分析与结论
这几道题解均围绕寻找长度为 $n$ 且含 $n - 2$ 个 'a' 和 2 个 'b' 的字符串按字典序排列后的第 $k$ 个字符串这一问题。各题解思路差异在于寻找两个 'b' 位置的方式不同。有的通过找规律直接计算位置，有的借助数学推导确定行和列来定位，有的通过枚举和计数确定，还有的利用组合数相关公式以及二分查找结合前缀和来求解。

### 所选的题解
- **作者：suxxsfe (5星)**
    - **关键亮点**：通过观察例子找出两个 'b' 位置的移动规律，直接根据规律计算出第 $k$ 个字符串中两个 'b' 的位置，思路清晰，代码简洁高效。
    - **重点代码核心思想**：从后向前枚举第一个 'b' 的位置 $i$，根据 $k$ 与 $n - i$ 的大小关系判断是否继续向前枚举，若 $k \leq n - i$，则第二个 'b' 在第 $n - k + 1$ 位，从而确定两个 'b' 的位置并输出字符串。
    - **核心代码片段**：
```cpp
int main(){int T=read();while(T--){
    n=read();k=read();
    for(reg int i=n-1;i;i--){
        if(k>n-i) k-=n-i;
        else{
            for(reg int j=1;j<i;j++) std::putchar('a');
            std::putchar('b');
            for(reg int j=i+1;j<n-k+1;j++) std::putchar('a');
            std::putchar('b');
            for(reg int j=n-k+2;j<=n;j++) std::putchar('a');
            break;
        }
    }
    EN;
}
return 0;
}
```
- **作者：registerGen (4星)**
    - **关键亮点**：构造数表，利用数学推导通过求解不等式确定 $k$ 在数表中的行 $r$ 和列 $c$，进而得出两个 'b' 的位置，方法巧妙，时间复杂度为 $O(1)$ 计算关键参数。
    - **重点代码核心思想**：先通过求解不等式 $x^2 + x - 2k \leq 0$ 得到 $x \leq \frac{-1 + \sqrt{1 + 8k}}{2}$，从而确定 $r = \lceil x\rceil$，再计算 $c = k - \frac{r(r - 1)}{2}$，最后根据 $r$ 和 $c$ 确定两个 'b' 的位置为 $n - r$ 和 $n - c + 1$。
    - **核心代码片段**：无（题解中未给出完整代码）
- **作者：JACK_POT (4星)**
    - **关键亮点**：通过从后往前枚举第一个 'b' 的位置 $l$，累计每个 $l$ 对应的第二个 'b' 的位置数量 $n - i$ 到计数器 $sum$ 中，当 $sum \geq k$ 时确定 $l$ 和 $r$，思路直观，易于理解。
    - **重点代码核心思想**：从后往前枚举 $l$，累加 $n - i$ 到 $sum$，当 $sum \geq k$ 时，退回 $sum$ 并确定 $l = i$，通过 $r = n - (k - sum) + 1$ 确定 $r$，最后按位置输出 'a' 和 'b'。
    - **核心代码片段**：
```cpp
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&k);
        int sum=0,l,r;
        fo(i,n-1,1){
            sum+=n-i;
            if(sum>=k) {
                sum-=n-i;
                l=i;
                r=n-(k-sum)+1;
                break;
            }
        }
        fr(i,1,n){
            if(i==l||i==r) printf("b");
            else printf("a");
        }
        cout<<endl;
    }
    return 0;
}
```

### 最优关键思路或技巧
通过观察字符串中 'b' 的位置移动规律，利用数学方法直接计算出两个 'b' 的位置，避免了复杂的枚举过程，提高了效率。例如 suxxsfe 的题解通过找规律直接确定两个 'b' 的位置，registerGen 通过构造数表和数学推导确定位置。

### 拓展
此类题目属于字符串组合与位置确定的类型，类似套路为通过观察组合元素（本题为 'b'）的排列规律，结合数学运算（如不等式求解、数列计算等）来确定特定位置的组合形式。

### 洛谷相似题目
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)
- [P2704 [NOI2001] 炮兵阵地](https://www.luogu.com.cn/problem/P2704) 

---
处理用时：62.73秒