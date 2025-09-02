# 「Wdcfr-1」CONsecutive and CONcat (easy version)

## 题目描述

**In easy version, It is guaranteed that any string in array $\mathbf a$ contains at least two different letters.**

Lily White is playing with strings. Being a yousei, she is not capable of complex speech. Thus, she likes strings that only contain one kind of letter, she calls such strings of length $x$ a "$x$-CON string". For example, `qqqq` is a "$4$-CON string", while `aaab` is not any type of "CON string".

Lily White composed an array $a$. It contains $n$ strings of length $m$ that she will use to herald spring. For each permutation of $1,2,\ldots, n$, let us denote current permutation as $p=\{p_1,p_2,\cdots,p_n\}$. Lily White concatenates all the string in array $a$ in the order of $a_{p_1},a_{p_2},\cdots,a_{p_n}$ into a string $s$ of length $nm$ . 

As she likes $k$-CON strings, she wants to know the sum of the number of "$k$-CON string" in all non-empty substrings of $s$ composed by all $n!$ permutations. Since the answer may be enormous, just print the answer taken modulo $998,244,353$ (a large prime).


## 说明/提示

### Explanation

#### Sample \#1

- For permutation $1,2,3$, the formed $s$ is `aabbaabaa`, none on the non-empty substring in this string are "$4$-CON string".
- For permutation $1,3,2$, the formed $s$ is `aabbaabaa`, none on the non-empty substring in this string are "$4$-CON string".
- For permutation $2,1,3$, the formed $s$ is `baaaabbaa`, this string has one substring `aaaa` which is a "$4$-CON string".
- For permutation $2,3,1$, the formed $s$ is `baabaaaab`, this string has one substring `aaaa` which is a "$4$-CON string".
- For permutation $3,1,2$, the formed $s$ is `baaaabbaa`, this string has one substring `aaaa` which is a "$4$-CON string".
- For permutation $3,2,1$, the formed $s$ is `baabaaaab`, this string has one substring `aaaa` which is a "$4$-CON string".

In summary, the answer is $0+0+1+1+1+1=4$.

#### Sample \#2

In all of the full permutation of length $3$, there will be six different $s$: `xyzqaqaba`, `xyzabaqaq`, `qaqxyzaba`, `qaqabaxyz`, `abaqaqxyz`, and `abaxyzqaq`. None of these has a non-empty substrings which is a "$2$-CON string". So the answer is $0$.

### Constraints

$2\le k \le n\cdot m\le 10^6;\ 1\le m \le 100$. $a_i$ contains only lowercase English letters.

**In easy version, we ensure that any string in array $\mathbf a$ contains at least two different letters.**

## 样例 #1

### 输入

```
3 3 4
aab
baa
baa```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3 2
xyz
qaq
aba
```

### 输出

```
0```

# 题解

## 作者：FFTotoro (赞：2)

原来的官方题解比较有误导性，包括但不限于公式中代表变量的字母写错，计算方式很容易让人理解错意思导致边界条件处理不清楚。这里提供一份较为完整且附带参考代码的题解。

考虑把贡献分成两部分：

一部分为**单个字符串内部贡献**，即对于单个字符串内所有长度为 $k$ 的、由同一个字符组成的子串，每个都会在所有 $n!$ 种方案中出现。每个字符串循环模拟一遍即可，具体地，对于一个极长的、由同一个字符组成、长度为 $t(t\ge k)$ 的子串，其贡献为 $n!(t-k+1)$。

比较复杂的另一部分是对于两个字符串，**前者后缀拼接后者前缀**产生的贡献（这里的后缀内的所有字符、缀前内的所有字符都相同）。具体地，因为 $m\le 100$，所以可以直接枚举后（前）缀的字符、后缀长度与前缀长度然后计算。但是这里如果你直接按官方题解的公式计算，会**算重**。具体地，设拼接的后缀长度为 $s$，前缀长度为 $p$，一种情况就是当 $k\le s$ 或者 $k\le p$ 时，其中有若干长度为 $k$ 的子串在**同一个**字符串中！

所以我们只能考虑子串跨越两个字符串的情况，及它的**真**前缀在前者的后缀内，它的**真**后缀在后者的前缀内。于是我们可以的出后缀长度为 $s$，前缀长度为 $p$ 时单次产生的贡献，即为 $\min\{s,s+p-k+1\}-\max\{s-k+2,1\}+1$（证明可自行推导，分别考虑子串左右端点的最小值和最大值并取上交集即可）。又由于在 $n!$ 种情况中特定的两个字符串相邻的情况共有 $(n-1)!$ 种，所以贡献要乘以 $(n-1)!$。

当然要注意误把同一个字符串“自己和自己拼接”加入贡献的情况，把这部分去掉即可。

把两部分合起来就是最终答案。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=998244353;
main(){
  ios::sync_with_stdio(false);
  int n,m,k,r=0,F=1,F2=1; cin>>n>>m>>k;
  for(int i=2;i<=n;i++)(F*=i)%=p;
  for(int i=2;i<n;i++)(F2*=i)%=p;
  // 预处理阶乘，F = n!，F2 = (n - 1)!
  vector<string> a(n);
  vector<array<int,26> > b(m),s(m);
  // b[i][j] 统计具有长度为 i、字符全部为 c 的极长前缀的字符串个数
  // s[i][j] 类似，只是把前缀换成后缀
  vector e(m,vector<array<int,26> >(m));
  for(auto &i:a){
    cin>>i; int t=0,l=0;
    for(int j=0;j<m;j++)
      if(!j||i[j]==i[j-1])t++; // 与上一个字符相同
      else{
        if(t>=k)(r+=F*(t-k+1)%p)%=p; // 第一部分贡献
        t=1; // 将答案清空，计算下一段
      }
    if(t>=k)(r+=F*(t-k+1)%p)%=p; // 最后还有一段
    for(int j=0;j<m&&i[j]==i[0];j++)l++;
    b[l][i[0]-97]++,s[t][i[m-1]-97]++;
    // l 为极长的、字符相同的前缀长度
    // 利用剩余的 t 得到极长的、字符相同的后缀长度
    // 统计特定字符的前缀、后缀长度确定时的字符串个数
    if(i[0]==i[m-1])e[l][t][i[0]-97]++;
    // 自己和自己拼接的情况
  }
  auto f=[&](int i,int j,int k){
    return min(i,i+j-k+1)-max(1ll,i-k+2)+1;
  }; // 计算拼接时“跨越”字符串的子串数
  // i 为后缀长度，j 为前缀长度
  for(int c=0;c<26;c++)
    for(int i=1;i<m;i++)
      for(int j=max(k-i,1ll);j<m;j++)
        (r+=(b[j][c]*s[i][c]%p-e[j][i][c]+p)%p*f(i,j,k)%p*F2%p)%=p;
         // 统计所有方案数
  cout<<r<<endl;
  return 0;
}
```

---

## 作者：wdsj0yqqs (赞：0)

题面比较简短，就不用过多描述了。

思路

首先遍历所有可能的排序 $p$。对于每一个排序 $p$，把对应的字符串 $a_{p_{1}},a_{p_{2}},\cdots,a_{p_{n}}$ 拼接起来得到的字符串 $s$。然后遍历字符串 $s$，对于每个位置 $x$，检查从 $x$ 开始长度为 $k$ 的子串是否为同一种字符。从 $x$ 到 $x+k-1$，检查字符是否都是相同的。如果是，则把满足条件的位置都加 $1$。

最后把所有满足条件的位置数对 $ 998244353$ 取模后输出就可以了。

---

## 作者：yzy1 (赞：0)

考虑将贡献分为两种——字符串内部的贡献和拼接处产生的贡献。第一种贡献直接暴力求即可，重点是第二种。考虑一个有长度为 $i$ 的连续极大后缀的字符串和一个长度为 $j$ 的极大连续前缀的字符串相拼接。会对答案造成 $i+j-k+1$ 的贡献。我们可以预处理出有极大前缀为字符 $c$，长度为 $i$ 的字符串数量 $\operatorname{pre}(c,i)$，极大后缀为字符 $c$，长度为 $j$ 的字符串数量 $\operatorname{suf}(c,j)$。枚举 $c,i,j$，从两个集合各选出一个字符串拼接在一起的方案数为 $\operatorname{suf}(c,j)\operatorname{pre}(c,i)$。考虑将「所有的全排列中 $k$ 连串数量的总和」转化为「随机洗牌后 $k$ 连串数量的期望」。从 $n$ 个位置中选择两个位置共有 $\operatorname{C}_n^2 = n(n-1)$ 种方案。而这 $n(n-1)$ 种方案中只有 $(n-1)$ 种使得两个字符串正好相邻。也就是说，随机洗牌后这两个字符串正好相邻形成 $k$ 连串的概率为 $\dfrac{n-1}{n(n-1)}=\dfrac 1 n$。所以对答案的贡献为：
$$
\dfrac{\operatorname{suf}(c,j)\operatorname{pre}(c,i)(i+j-k+1)} n.
$$
但是这会忽略一种特殊情况，试想有这样一组数据：

```
-1
2 3 2
aba
cde
```

正确答案显然为 $0$，但是根据上面那种方式得到的答案为 $1$，原因是因为字符串 `aba` 的前后缀有相同的字符，计算答案时会「自己和自己拼接」而造成贡献，我们可以记录多少个字符串有着极大前后缀字符均为 $c$ 的，前缀长度为 $i$，后缀长度为 $j$ 的字符串数量 $\operatorname{same}(c,i,j)$，计算答案时减去即可。故最终答案为：
$$
\sum_{c=\verb!a!}^{\verb!z!}\sum_{i=1}^{m-1}\sum_{j=1}^{m-1}\dfrac{(\operatorname{suf}(c,i)\operatorname{pre}(c,i)-\operatorname{same}(c,i,j))(i+j-k+1)} n.
$$

---

