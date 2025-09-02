# 题目信息

# Shifting String

## 题目描述

Polycarp found the string $ s $ and the permutation $ p $ . Their lengths turned out to be the same and equal to $ n $ .

A permutation of $ n $ elements — is an array of length $ n $ , in which every integer from $ 1 $ to $ n $ occurs exactly once. For example, $ [1, 2, 3] $ and $ [4, 3, 5, 1, 2] $ are permutations, but $ [1, 2, 4] $ , $ [4, 3, 2, 1, 2] $ and $ [0, 1, 2] $ are not.

In one operation he can multiply $ s $ by $ p $ , so he replaces $ s $ with string $ new $ , in which for any $ i $ from $ 1 $ to $ n $ it is true that $ new_i = s_{p_i} $ . For example, with $ s=wmbe $ and $ p = [3, 1, 4, 2] $ , after operation the string will turn to $ s=s_3 s_1 s_4 s_2=bwem $ .

Polycarp wondered after how many operations the string would become equal to its initial value for the first time. Since it may take too long, he asks for your help in this matter.

It can be proved that the required number of operations always exists. It can be very large, so use a 64-bit integer type.

## 说明/提示

In the first sample operation doesn't change the string, so it will become the same as it was after $ 1 $ operations.

In the second sample the string will change as follows:

- $ s $ = babaa
- $ s $ = abaab
- $ s $ = baaba
- $ s $ = abbaa
- $ s $ = baaab
- $ s $ = ababa

## 样例 #1

### 输入

```
3
5
ababa
3 4 5 2 1
5
ababa
2 1 4 5 3
10
codeforces
8 6 1 7 5 2 9 3 10 4```

### 输出

```
1
6
12```

# AI分析结果

### 题目翻译
# 移位字符串

## 题目描述
Polycarp 找到了字符串 $ s $ 和排列 $ p $。它们的长度相同，都等于 $ n $。

一个包含 $ n $ 个元素的排列是一个长度为 $ n $ 的数组，其中从 $ 1 $ 到 $ n $ 的每个整数恰好出现一次。例如，$ [1, 2, 3] $ 和 $ [4, 3, 5, 1, 2] $ 是排列，但 $ [1, 2, 4] $、$ [4, 3, 2, 1, 2] $ 和 $ [0, 1, 2] $ 不是。

在一次操作中，他可以将 $ s $ 与 $ p $ 相乘，即他将 $ s $ 替换为新字符串 $ new $，其中对于从 $ 1 $ 到 $ n $ 的任何 $ i $，都有 $ new_i = s_{p_i} $。例如，当 $ s = wmbe $ 且 $ p = [3, 1, 4, 2] $ 时，经过一次操作后，字符串将变为 $ s = s_3 s_1 s_4 s_2 = bwem $。

Polycarp 想知道，经过多少次操作后，字符串第一次变回其初始值。由于这个次数可能非常大，他向你寻求帮助。

可以证明，所需的操作次数总是存在的。这个次数可能非常大，因此请使用 64 位整数类型。

## 说明/提示
在第一个样例中，操作不会改变字符串，因此经过 $ 1 $ 次操作后，字符串将与初始状态相同。

在第二个样例中，字符串将按如下方式变化：
- $ s $ = babaa
- $ s $ = abaab
- $ s $ = baaba
- $ s $ = abbaa
- $ s $ = baaab
- $ s $ = ababa

## 样例 #1
### 输入
```
3
5
ababa
3 4 5 2 1
5
ababa
2 1 4 5 3
10
codeforces
8 6 1 7 5 2 9 3 10 4
```

### 输出
```
1
6
12
```

### 算法分类
图论

### 综合分析与结论
这些题解的核心思路都是将排列 $p$ 转化为图中的环，然后找出每个环的最短循环节，最后计算所有最短循环节长度的最小公倍数得到答案。

思路方面，大家都能想到将问题转化为环的问题，但对于如何计算每个环的最短循环节，不同题解有不同的方法，包括暴力模拟、KMP 算法和子串哈希等。

算法要点上，主要涉及图的遍历找环、最短循环节的计算以及最小公倍数的计算。

难点在于如何正确计算每个环的最短循环节，因为环内可能存在循环，不能简单地将环长作为循环节长度。

### 所选题解
- **liujy_（5星）**
    - **关键亮点**：思路清晰，先给出暴力做法，再给出严格线性做法，对问题的分析和解决过程详细，代码注释完善。
    - **个人心得**：初写题解时比较菜，过了题就兴奋地交题解，后来准备给学弟学妹做杂题选讲时又重新思考，想出了不暴力判断的做法。
- **zhouyuhang（4星）**
    - **关键亮点**：提出严格线性做法，对做法的推导和证明详细，给出了使用 KMP 算法的具体思路和复杂度分析。
- **fast_photon（4星）**
    - **关键亮点**：对问题的分析全面，详细解释了为什么要找最短循环节以及如何找最短循环节，代码实现中使用了一些优化技巧，如用 $i*i$ 避免 TLE。

### 重点代码
#### liujy_ 的严格线性做法
```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#define int long long
using namespace std;
int t,n,m,now,mn,cnt,a[205],l[205],nxt[205];
char ch[205],c[205];bool vis[205],use1[205],use2[205];
signed main(){
    scanf("%lld",&t);
    for(int T=1;T<=t;T++){
        memset(vis,0,sizeof(vis));memset(l,0,sizeof(l));
        scanf("%lld",&n);scanf("%s",ch+1);cnt=0;
        for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
        for(int i=1;i<=n;i++){
            if(vis[i])continue ;
            ++cnt;int len=0;nxt[1]=0;
            for(int j=i;!vis[j];j=a[j])vis[j]=1,c[++len]=ch[j];
            for(int i=2,j=0;i<=len;i++){use1[i]=use2[i]=0;
                while(j&&c[i]!=c[j+1])j=nxt[j];
                if(c[i]==c[j+1])j++;nxt[i]=j;
            }
            l[cnt]=len;int p=nxt[len];
            while(p)use1[p]=1,use2[len-p+1]=1,p=nxt[p];
            for(int i=2;i<=len;i++)
                if(use2[i]&&use1[i-1]){l[cnt]=i-1;break;}
        }
        int ans=l[1];
        for(int i=2;i<=cnt;i++){
            int d=__gcd(ans,l[i]);
            ans=ans*l[i]/d;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```
**核心实现思想**：先通过图的遍历找出所有环，将环中的字符存储在数组中，然后使用 KMP 算法计算该数组的前缀函数，根据前缀函数找出所有公共前后缀，进而找出最短循环节，最后计算所有最短循环节长度的最小公倍数。

#### zhouyuhang 的做法
```cpp
// 部分关键思路代码
// 处理出 s 的前缀函数
for(int i = 2, j = 0; i <= n; i++) {
    while(j && s[i] != s[j + 1]) j = pi[j];
    if(s[i] == s[j + 1]) j++;
    pi[i] = j;
}
// 从字符串末尾不断沿着 pi 回跳，标记满足条件的位置
int p = pi[n];
while(p) {
    mark[p] = 1;
    p = pi[p];
}
// 枚举 k，判断是否满足条件
for(int k = 1; k < n; k++) {
    if(mark[k] && mark[n - k]) {
        // k 满足条件
    }
}
```
**核心实现思想**：先使用 KMP 算法计算字符串的前缀函数，然后从字符串末尾沿着前缀函数回跳，标记所有满足 $s[1…k]=s[n-k+1…n]$ 的 $k$，最后枚举 $k$，判断 $k$ 和 $n - k$ 是否都被标记，若都被标记，则 $k$ 满足条件。

#### fast_photon 的做法
```cpp
int minr(string s) { //这个是计算最短重复字串长度用的
    int len = s.size();
    int ans = 0x3f3f3f3f;
    for(int i = 1; i * i <= len; i++) {
        if(s.size() % i != 0) continue; 
        if(repeat(s.substr(0, i), len / i) == s) {
            ans = min(ans, i);
        }
        if(repeat(s.substr(0, len / i), i) == s) {
            ans = min(ans, len / i);
        }
    }
    return ans;
}
```
**核心实现思想**：枚举所有可能的子串长度 $i$，将子串重复 $len / i$ 次后与原串比较，若相同则更新最短重复子串长度，使用 $i * i <= len$ 避免 TLE。

### 扩展思路
同类型题或类似算法套路：
- 涉及置换群的问题，通常可以将置换拆成不相交的轮换，然后对每个轮换进行单独处理。
- 对于字符串的循环节问题，可以使用 KMP 算法、子串哈希等方法进行优化。

### 推荐题目
- [P1368 工艺](https://www.luogu.com.cn/problem/P1368)：求字符串的最小表示法，与本题找最短循环节有相似之处。
- [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)：KMP 算法的模板题，可用于练习 KMP 算法。
- [P5410 【模板】扩展 KMP](https://www.luogu.com.cn/problem/P5410)：扩展 KMP 算法的模板题，可进一步加深对字符串匹配算法的理解。

### 个人心得总结
- liujy_ 提到初写题解时比较浮躁，后来重新思考问题，得出了更好的解法，说明做题后要多总结和反思，才能不断进步。
- fast_photon 详细分析了问题，避免了一些常见的错误思路，提醒我们在做题时要仔细分析题目条件，不能想当然。

---
处理用时：66.29秒