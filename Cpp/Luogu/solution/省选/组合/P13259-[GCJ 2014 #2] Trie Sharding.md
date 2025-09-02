# [GCJ 2014 #2] Trie Sharding

## 题目描述

一组字符串 $\mathbf{S}$ 可以被高效地存储在一个字典树（trie）中。字典树是一棵有根树，其中每个节点代表 $\mathbf{S}$ 中某个字符串的一个前缀，且不重复。

例如，如果 $\mathbf{S}$ 为 "AAA"、"AAB"、"AB" 和 "B"，那么对应的字典树将包含 $7$ 个节点，分别对应前缀：""、"A"、"AA"、"AAA"、"AAB"、"AB" 和 "B"。

我现在有一台服务器，用一个大的字典树来存储 $\mathbf{S}$。不幸的是，随着 $\mathbf{S}$ 的不断增大，我发现很难再将它完整地装进单台服务器的内存中。为了解决这个问题，我打算将 $\mathbf{S}$ 拆分并存储在 $\mathbf{N}$ 台不同的服务器上。具体来说，$\mathbf{S}$ 将被划分成若干个不相交的非空子集 $\mathbf{T}_1, \mathbf{T}_2, \ldots, \mathbf{T}_\mathbf{N}$，然后在每台服务器 $i$ 上构建仅包含 $\mathbf{T}_i$ 中字符串的字典树。

这种方式的缺点是：所有 $\mathbf{N}$ 个字典树中的节点总数可能会变多。更糟的是，我无法控制字符串是如何被划分到各个服务器上的！

例如，如果 "AAA"、"AAB"、"AB" 和 "B" 被分配到两台服务器，其中一台存储 "AAA" 和 "B"，另一台存储 "AAB" 和 "AB"，那么第一台服务器的字典树需要 $5$ 个节点（""、"A"、"AA"、"AAA"、"B"），第二台服务器也需要 $5$ 个节点（""、"A"、"AA"、"AAB"、"AB"），总共就是 $10$ 个节点。而如果将所有字符串放到一台服务器上，只需要 $7$ 个节点。

现在，给定字符串集 $\mathbf{S}$ 和服务器数 $\mathbf{N}$，我希望你帮我计算以下两个问题：

1. 在最坏的划分方案下，所有服务器上字典树节点数的总和最多是多少？
2. 有多少种划分方式能导致上述最大节点数？由于这个数可能非常大，请输出其对 $1,\!000,\!000,\!007$ 取模的结果。

注意：$\mathbf{N}$ 台服务器是有区别的——如果某种方案中一个字符串出现在 $\mathbf{T}_i$ 中，而另一种方案中它出现在 $\mathbf{T}_j$ 中（$i \neq j$），则这两种划分方式被认为是不同的。


## 说明/提示

**限制条件**

- $1 \leq T \leq 100$
- 字符串集 $\mathbf{S}$ 中的字符串只包含大写英文字符
- $\mathbf{S}$ 中所有字符串互不相同
- $\mathbf{N} \leq \mathbf{M}$

### Small 数据集（9 分）

- 时间限制：~~60~~ 3 秒
- $1 \leq M \leq 8$
- $1 \leq N \leq 4$
- 每个字符串长度在 $1$ 到 $10$ 之间

### Large 数据集（30 分）

- 时间限制：~~120~~ 5 秒
- $1 \leq M \leq 1000$
- $1 \leq N \leq 100$
- 每个字符串长度在 $1$ 到 $100$ 之间

翻译由 ChatGPT-4o 完成

## 样例 #1

### 输入

```
2
4 2
AAA
AAB
AB
B
5 2
A
B
C
D
E```

### 输出

```
Case #1: 10 8
Case #2: 7 30```

# 题解

## 作者：zzwdsj (赞：3)

~~[测试点下载：测试点.zip](https://vdse.bdstatic.com//192d9a98d782d9c74c96f09db9378d93.mp4)~~

### 思路

#### 第一问

考虑贪心。设 $p$ 为某个输入字符串的某个前缀，当一个包含前缀 $p$ 的字符串被分配到了服务器 $i$，就说前缀 $p$ 被分配给了服务器 $i$。

当前缀 $p$ 被重复分到一个服务器 $i$ 时，根据 Trie 的特性，这个前缀产生节点的贡献和只分配给 $i$ 一次是一样的。因此，最优分配应该能让每个前缀尽量分配给所有服务器。

考虑将输入字符串 $s_i$ 按字典序排序，这样相同前缀的字符串都被排在一起。然后把 $s_1$ 分配到服务器 $1$，$s_2$ 分配到服务器 $2\dots$，$s_1+N$ 分配到服务器 $1\dots$ 这样任意 $N$ 个相邻字符串都会被分到 $N$ 个服务器里，也就能保证 $N$ 个相邻的前缀被分到 $N$ 个服务器里了。

#### 第二问

考虑树形 dp。根据第一问的分析，最优分配会将每个前缀 $p$ 平均分配给每个服务器，前缀 $p$ 应该会被分配到 $K_p=\min\left(T_p,N\right)$，其中 $T_p$ 表示有多少个字符串包含前缀 $p$。将所有字符串插入进 Trie 中。设 $f_x$ 为 Trie 上点 $x$ 的子树里的字符串分配给 $K_p$ 个服务器的方案数，答案即为 $f_{root}$。

接着看看怎么转移。对于节点 $x$：

1. 它的每个子节点都可以取任意中方案，所以 $f_x$ 要乘上 $\Pi_{i\in son_x}f_i$。
2. 还需要考虑把它子树内的字符串（在 $s$ 中）分配到 $K_p$ 个服务器里的方案数。如果 $x$ 代表的字符串在 $s$ 中，则需要考虑把它子树内的字符串和它本身分配到 $K_p$ 个服务器里的方案数。
   对于每个 $i\in son_x$，它字子树内 $K_i$ 个服务器的分配已经处理好了。现在只需要把这 $K_i$ 个服务器对应到 $K_p$ 个服务器就好了。这 $K_i$ 个服务器可以看成是相同的，但是不同子节点的 $K_i$ 个服务器则是不同的。可以看成将一个可重集 $L$ 里的元素分成 $K_p$ 类，每类不为空，方案数记作 $g\left(L,K_p\right)$（$g\left(L,K_p\right)$ 的求法后面再讲）。
3. 对于 $x$ 代表的字符串在 $s$ 中的情况，就多了 $x$ 这个元素分成 $K_p$ 类，在 $L$ 中多加一个元素即可。

现在计算 $g\left(L,K_p\right)$。在此之前，先规定一下可重集 $L$ 的表示方法：$L$ 被表示为一个数组 $l$，$l_i$ 表示元素 $i$ 在 $L$ 中出现的次数。先不考虑每类不为空的限制，每种元素可以单独计算。答案为 $\Pi \binom{K_p}{L_i}$。然后考虑上不为空的限制，可以减去为空的方案数。枚举不空的类数 $a$，它可以是 $K_p$ 中任意 $a$ 个，分成 $a$ 类有 $g\left(L,a\right)$ 中方案。只有 $a$ 类不空总方案数为 $g\left(L,a\right)\times \binom{K_p}{a}$。这有一个递归，可以改成递推实现。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
int C[105][105],f[105];
int g(vector<int> l,int k)
{
    f[1]=1;
    for(int j:l)f[1]=1LL*f[1]*C[1][j]%mod;
    for(int i=2;i<=k;i++)
    {
        f[i]=1;
        for(int j:l)f[i]=1LL*f[i]*C[i][j]%mod;
        for(int j=1;j<i;j++)f[i]=(f[i]-1LL*f[j]*C[i][i-j]%mod+mod)%mod;
    }
    return f[k];
}
int n,k,ans1,ans2;
string s[1005];
struct hs{int operator()(char x){return x-'A';}};
template<int N,int M,class toInt>
class trie
{
    toInt f;
    int ch[N+5][M],cnt[N+5],dp[N+5],tot;
    bool end[N+5];
    public:void insert(string s)
    {
        int x=1;
        cnt[x]++;
        for(char i:s)
        {
            if(!ch[x][f(i)])ch[x][f(i)]=++tot;
            x=ch[x][f(i)];
            cnt[x]++;
        }
        end[x]=1;
    }
    int getans()
    {
        vector<int>L;
        for(int i=tot;i>=1;i--)
        {
            L.clear();
            dp[i]=1;
            for(int j=0;j<M;j++)
                if(ch[i][j])
                    dp[i]=1LL*dp[i]*dp[ch[i][j]]%mod,L.push_back(min(cnt[ch[i][j]],k));
            if(end[i])L.push_back(1);
            dp[i]=1LL*dp[i]*g(L,min(cnt[i],k))%mod;
        }
        return dp[1];
    }
    int size(){return tot;}
    void clear()
    {
        memset(ch,0,sizeof ch);
        memset(cnt,0,sizeof cnt);
        memset(end,0,sizeof end);
        tot=1;
    }
    trie():tot(1){}
};
trie<100000,26,hs>t,v;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    C[0][0]=1;
    for(int i=0;i<=100;i++,C[i][0]=1)
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    int T;
    cin>>T;
    for(int Case=1;Case<=T;Case++)
    {
        cin>>n>>k;
        ans1=ans2=0;
        t.clear();
        for(int i=1;i<=n;i++)cin>>s[i],t.insert(s[i]);
        sort(s+1,s+n+1);
        for(int i=1;i<=k;i++)
        {
            v.clear();
            for(int j=i;j<=n;j+=k)v.insert(s[j]);
            ans1+=v.size();
        }
        ans2=t.getans();
        cout<<"Case #"<<Case<<": "<<ans1<<" "<<ans2<<endl;
    }
    return 0;
}
```

---

