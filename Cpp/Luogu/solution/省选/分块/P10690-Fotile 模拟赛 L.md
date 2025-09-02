# Fotile 模拟赛 L

## 题目描述

FOTILE 得到了一个长为 $N$ 的序列 $A$，为了拯救地球，他希望知道某些区间内的最大的连续 $\rm XOR$ 和。

即对于一个询问，你需要求出

$$
\max_{l\le i\le j\le r}\bigoplus_{k=i}^{j} a_k
$$

为了体现在线操作，对于一个询问 $(x,y)$：

- $l = \min ( ((x+{\rm lastans}) \bmod N)+1 , ((y+{\rm lastans}) \bmod N)+1)$.
- $r = \max ( ((x+{\rm lastans}) \bmod N)+1 , ((y+{\rm lastans}) \bmod N)+1)$.

**其中 $\rm lastans$ 是上次询问的答案，一开始为0。**

## 说明/提示

对于所有的测试数据满足 $N=12000$，$M=6000$，$x$，$y$，$a_i$ 均在 signed int 范围内。

## 样例 #1

### 输入

```
3 3
1 4 3 
0 1
0 1
4 3```

### 输出

```
5
7
7```

# 题解

## 作者：ivyjiao (赞：7)

wukaichen888 /hs /bx

区间 DP 神仙题。

---

$N=12000$，$O(n^2)$ 可过。

考虑区间 DP，第一维枚举长度，第二维枚举区间起点，然后就是 DP 转移，设 $dp_{l,r}$ 为 $\max_{l\le i\le j\le r}\bigoplus_{k=i}^{j} a_k$，则这里有一个比较显然的 DP 转移式：

$$dp_{l,r}=\max\{a_l\oplus a_{l+1}\oplus\cdots\oplus a_r,dp_{l,r-1},dp_{l+1,r}\}$$

DP 数组的初始值就是 $dp_{i,0}=a_i$。

然后考虑优化这个 $O(n^3)$ 的 DP 转移过程，不难发现异或满足 $x\oplus x=0$，所以 $a_l\oplus a_{l+1}\oplus\cdots\oplus a_r=qzh_r\oplus qzh_{l-1}$，其中 $qzh$ 是前缀异或和数组。所以我们只需要预处理出前缀异或和数组即可把该转移过程优化为 $O(n^2)$。

$$dp_{l,r}=\max\{qzh_r\oplus qzh_{l-1},dp_{l,r-1},dp_{l+1,r}\}$$

然而，这题的空间不允许你开这么大的数组，所以我们考虑继续优化该 DP。

经过计算，大概空间再减少一半就能开的下了，那么怎么优化掉一半的空间？

不难发现我们的 DP 数组其实有一半都被浪费掉了（$r<l$ 的部分），这就是本题的突破口。

C++ 中，有这么一个美妙的东西，它叫 vector 动态数组。

这个 vector 的好处就是它的大小是可以动态调整的，不像普通数组一样定下了就改不了。

但是我们发现浪费的空间并非在数组的末尾，所以我们要更改 DP 式，让浪费的空间出现在数组的末尾。

设 $dp_{l,len}$ 为 $\max_{l\le i\le j\le l+len-1}\bigoplus_{k=i}^{j} a_k$，则这里有一个比较显然的 DP 转移式：

$$dp_{l,len}=\max\{qzh_{l+len-1}\oplus qzh_{l-1},dp_{l,len-1},dp_{l+1,len-1}\}$$

DP 数组的初始值就是 $dp_{i,1}=a_i$。

然后我们发现此时被浪费的空间都出现在数组的末尾了，那么如何让这些空间不被浪费？

C++ 的 vector 中，有一个函数叫做 resize，它可以控制 vector 的大小，现在这些空间就被节约下来了。

剩下的就是一些细节了，注意 $x+lastans$ 可能会爆 int，要写成 $(x\bmod n+lastans\bmod n)\bmod n$，剩余的同理。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,l,r,a[12001],qzh[12001],lastans;
vector<int>dp[12001];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        dp[i].resize(n-i+2);
        dp[i][1]=a[i];
        qzh[i]=qzh[i-1]^a[i];
    }
    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            dp[i][len]=max({qzh[i+len-1]^qzh[i-1],dp[i+1][len-1],dp[i][len-1]});
        }
    }
    while(m--){
        cin>>x>>y;
        l=min(((x%n+lastans%n)%n)+1,((y%n+lastans%n)%n)+1);
        r=max(((x%n+lastans%n)%n)+1,((y%n+lastans%n)%n)+1);
        cout<<dp[l][r-l+1]<<'\n';
        lastans=dp[l][r-l+1];
    }
}
```

---

## 作者：L01001101 (赞：5)

[$\color{000000}\text{P10690 Fotile 模拟赛 L}$](https://www.luogu.com.cn/problem/P10690)

对于区间询问最大异或值，可以用前缀和维护，然后用可持久化 Trie 来求。

直接暴力查询时间复杂度 $O(nm \log n)$。

但是这样不太优，思考怎样优化。

由于值不会改变，尝试预处理一些信息，用分块是不错的选择。

记 $f_{i,j}$ 表示从第 $i$ 个块开始，到端点 $j$ 的最大异或值。

则 $f_{i,j}$ 可以由 $f_{i,j-1}$ 和一个端点为 $j$ 的区间最大异或值转移而来。

所以我们可以得到从 $l$ 的下一个块一直到右端点的答案，同时对于散块暴力查询即可。

设块长为 $B$，时间复杂度 $O(n \times \frac{n}{B} \times \log n+mB)$，取 $B=\sqrt n$ 较优，为 $O(n\sqrt n\log n)$。

需要注意的是，由于我们记得是前缀和，所以查询区间不是 $[l,r]$ 而是 $[l-1,r]$。

```cpp
#include<cstdio>
#include<cmath>
const int N=12010,_B=120;
int n,m,B;
int a[N],s[N];
int pos[N],ls[_B],rs[_B];
int f[_B][N];
int R=-1,tot;
int r[N];
int t[N<<5][2],size[N<<5];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9')ch=='-'?f=0:0,ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?x:-x;
}
template<typename T>inline T max(T a,T b){return a>b?a:b;}
template<typename T>inline T min(T a,T b){return a<b?a:b;}
inline void Tadd(int x){
	r[++R]=++tot;
	for(int k=30,i,p1=r[R],p2=r[R-1];~k;--k)
		i=x>>k&1,t[p1][i^1]=t[p2][i^1],t[p1][i]=++tot,p1=t[p1][i],p2=t[p2][i],size[p1]=size[p2]+1;
}
inline int Task(int p1,int p2,int x){
	int res=0;
	p1=r[p1],p2=r[p2];
	for(int k=30,i;~k;--k)
		i=x>>k&1,size[t[p2][i^1]]>size[t[p1][i^1]]?res+=(1<<k),i^=1:0,p1=t[p1][i],p2=t[p2][i];
	return res;
}
int main(){
	n=read(),m=read(),B=sqrt(n+1),Tadd(0);
	for(int i=1;i<=n;++i)
		a[i]=read(),s[i]=s[i-1]^a[i],Tadd(s[i]);
	for(int i=1;i<=n;++i)pos[i]=(i-1)/B+1;
	for(int i=1,l=0,r;l<=n;++i,l=r+1)
		r=min(l+B-1,n),ls[i]=l,rs[i]=r;
	for(int i=1;i<=pos[n];++i)for(int j=ls[i]+1;j<=n;++j)
		f[i][j]=max(f[i][j-1],Task(ls[i]-1,j,s[j]));//查询区间为 [ls[i],j]
	for(int i=1,l,r,ans=0;i<=m;++i){
		l=((1LL*read()+ans)%n+n)%n+1,r=((1LL*read()+ans)%n+n)%n+1,l>r?l^=r^=l^=r:0,--l,ans=0;//查询区间为 [l-1,r]
		if(pos[l]==pos[r])for(int i=l;i<=r;++i)
			ans=max(ans,Task(l?l-1:0,r,s[i]));
		else{
			ans=f[pos[l]+1][r];
			for(int i=l;i<=rs[pos[l]];++i)
				ans=max(ans,Task(l?l-1:0,r,s[i]));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：spire001 (赞：5)

## P10690 题解

### 前言
我真傻，真的，看到这道题，这不很显然是通过前缀异或和转化成 01trie 问题吗？
诶？竟然是整个区间询问，那这复杂度不就是 $O(NM\log _2N)$ 了吗？
然后一算，大概要做 $7\times 10^8$ 次运算，应该能过。。。

交了十几次，怎么过不了？卡卡常数试试？？？

沉思良久，我发现这道题只给一秒就说明有更好的办法。。。

### 解题思路

首先一段连续区间的最大值，可以转化为异或前缀和后取两个点的最大值。
这个可以用 01trie 维护，然而询问很耗时，因为需要枚举某一边的端点。

这种询问很费时的题目，大抵都和预处理有点关系。

但是全部预处理显然不太行，所以考虑分块。。。
~~建议管理员添加“分块”标签。。。~~

$ma_{i,j}$ 表示从第 $j$ 个数到第 $i$ 个块中间的最大答案。

为了不必要的麻烦，到第 $i$ 个块的距离表示为到第 $i$ 个块的开头的距离。

~~把表示右端点的 $i$ 放在数组的第一维，是因为一些玄学原因，不喜勿喷。。。~~

那么 $ma_{i, j}$ 就可以由 $ma_{i,j+1}$ 以及一边拿 $a_{j-1}$ 时整个区间（注意不是 $a_j$）的最大值推出。

在询问的时候找到 $r$ 的左端点（这里就可以看出取块的起点而不是终点的好处了），$O(1)$ 得到已处理的最大值，然后再在这个块里暴力枚举其他未处理的右端点。  
当然，$l, r$ 在一个块内就直接暴力。

现在推一下复杂度，设块长为 $B$，则有 $\frac{N}{B}$ 个块。

预处理是 $O(\frac{N^2\log _2N}{B})$ 的。询问是 $O(M\times B)$ 的。

由于预处理的复杂度带了一个小于 $1$ 的常数，所以取 $B$ 等于 $\sqrt N$ 是比较优的。

最后复杂度 $O(N^{1.5}\log _2N)$。

所以就可以写出代码了，还有一些小细节在注释里呈现。。。

### AC 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

typedef long long LL;

constexpr int N = 12010;
constexpr int K = 30; // K = 30 最大可以表示 2147483647
constexpr int M = 120; // 块长

int n, T, lstans, rt[N], tot(1), cnt(0), a[N];

int st[M], ed[M], pos[N], ma[M][N];
int block, t;
void pre()
{
  block = __builtin_sqrt(n); // 预处理块长
  t = n / block + bool(n % block);
  for (int i = 1; i <= t; i++)
    st[i] = ed[i - 1] + 1,
    ed[i] = st[i] + block - 1;
  ed[t] = n;
  
  for (int i = 1; i <= t; i++)
    for (int j = st[i]; j <= ed[i]; j++)
      pos[j] = i;

  return;
}

struct trie{
  int nums[N * 31 * 2];
  int child[2][N * 31 * 2];
  
  void insert(const int x) // 01trie 可持久化
  {
    int lp = rt[cnt];
    rt[++cnt] = ++tot;
    int p = rt[cnt];

    for (int i = K; ~i; i--)
    {
      const int bit = x >> i & 1;
      
      if (!child[bit][p]) 
        child[bit][p] = ++tot;
      child[!bit][p] = child[!bit][lp];
      
      p = child[bit][p]; lp = child[bit][lp];
      nums[p] = nums[lp] + 1; // 值放在儿子上，就是说根节点不存值
    }

    return;
  }

  int ask(const int l, const int r, const int val) // 询问
  {
    int p = rt[r + 1], lp = rt[l]; // 最开始插入了一个 0
    // 所以是 p = rt[r + 1], lp = rt[l]
    // lp 指的是左端点代表的子树
    int res = 0;

    for (int i = K; ~i; i--)
    {
      const int bit = val >> i & 1;

      if (nums[child[!bit][p]] - nums[child[!bit][lp]] > 0)
      {
        res |= 1 << i; // 异或，贪心
        p = child[!bit][p];
        lp = child[!bit][lp];
      }
      else 
      {
        p = child[bit][p];
        lp = child[bit][lp];
      }
    }

    return res;
  }

} bt;

void bl()
{
  for (int i = 1; i <= t; i++)
  {
    ma[i][st[i]] = a[st[i]] ^ a[st[i] - 1]; // 预处理
    for (int j = st[i] - 1; j >= 1; j--)
      ma[i][j] = max(ma[i][j + 1], bt.ask(j - 1, st[i], a[j - 1])); // a[j - 1] 而不是 a[j]
//    assert(!lstans);
  }
  
  return;
}

int main()
{
  
  ios::sync_with_stdio(false);
  cin.tie(nullptr); cout.tie(nullptr);

  cin >> n >> T; pre();

  bt.insert(0); // a[0]

  for (int i = 1; i <= n; i++)  
    cin >> a[i];

  for (int i = 1; i <= n; i++)
  {
    a[i] ^= a[i - 1]; // 异或前缀和
    bt.insert(a[i]); // 插入
  }

  bl(); // 预处理
  
  while (T--)
  {
    int l, r;

    LL x, y; // 开了 long long 避免麻烦
    
    cin >> x >> y;

    l = min(((x + lstans) % n + n) % n + 1, ((y + lstans) % n + n) % n + 1); // 我觉得 x, y 可能是 2147483647 或 -2147483648, 不知道出题人有没有这么干
    r = max(((x + lstans) % n + n) % n + 1, ((y + lstans) % n + n) % n + 1);

    int res = 0;
    
    if (pos[r] > pos[l]) // 在不同的块
    { 
      res = ma[pos[r]][l];
      for (int i = r; i >= st[pos[r]]; i--)
        res = max(res, bt.ask(l - 1, i, a[i]));
    }
    else // 暴力
    {
      for (int i = r; i >= l; i--)
        res = max(res, bt.ask(l - 1, i, a[i]));
    }

    cout << (lstans = res) << '\n';
  }

  return 0;
}
```

---

## 作者：Tachibana27 (赞：4)

~~啊因为 SB 错误调了一天~~。这题是 [P4735](https://www.luogu.com.cn/problem/P4735) 的**可持久化 01trie** 用**分块**优化。本题要求有一定 **01trie** 基础。如果已完成 P4735 可以直接跳至**此题思路**部分。


------------
## 可持久化 01trie

看到**异或**，可以想到转换成 01trie 解决问题。在查询区间最大异或值的时候，不一定是从全局直接查询，故需要使用 **可持久化 01trie** 结合**前缀异或和**。

~~可持久化 01trie 就是可持久的 01trie~~，对于每一次的插入操作，只需要对于有影响的节点复制一遍，记录修改后的节点，每一次复制只会增加 $\log n$ 个点。相比于暴力的将整棵树复制一遍，节省了大量时间与空间。具体过程与**主席树**类似。

查询操作从二进制下最高位开始，设需要查询一个 $y$，使得其与 $x$ 异或和尽可能的大，则每一次在 01trie 中尽可能的选择当前位与二进制下 $x$ 不同的节点。这是一个显然的贪心，例如：$(1000)_2 >(0111)_2$。

从 $1$ 至 $i$ 的前缀异或和为 $xum_i$，则最终的答案是：

$$\max \limits _{l\le i\le j\le r}xum_i \oplus xum_j$$

显然对于每一次询问可以暴力的枚举一个 $i$ 并用 $O(\log n)$ 的复杂度查找到对应的 $xum_j$。

运用上面两个操作，再搭配上前缀异或和可以实现 $O(n\log n)$ 的插入所有元素，但查询区间最大异或和还是 $O(nm\log n)$，需要继续优化。

## 此题思路


注意到查询是算法的瓶颈，要考虑用某种算法或数据结构维护区间内的答案。~~因为我非常喜欢暴力数据结构~~，所以我用**分块**预处理出部分答案。

设 $s_{i,j}$ 表示以第 $i$ 块的左端点为左端点，以 $j$ 为右端点的区间内的最大异或和。记 $M$ 为在 $s_{i,j}$ 区间内与 $xum_j$ 异或的最大值。不难发现有：
$$s_{i,j}=\max(s_{i,j-1},M)$$

接下来在每一次的询问中，就只需要计算考虑散块中的答案即可。

此时的时间复杂度是 $O(n\sqrt n\times \log n+m\log n)$，当然常数有那么亿点点大，但既然是正确的复杂度就不必深究啦。

## 代码实现

在实现过程中，因为懒得特判各种 $0$ 的情况，01trie 的 $root$ 统一向右移动一格。

**ans 一定要清 $0$！**

```cpp
int n,m;
int point;
int rt[1000086];
int tr[1000086][2];
int cnt[1000086];
int xum[120086];
int id[120086];
int ltp[586];
int rtp[586];
int ask(int l,int r,int v){
    int ans=0;
    for(int i=63;i>=0;i--){//事实上远到不了2^63
        int qwq=(v>>i)&1;
        if(cnt[tr[r][not qwq]]>cnt[tr[l][not qwq]]){//若可以走与当前为相反的
            ans+=(1<<i);//当前位可以是1
            qwq=not qwq;//当前位取反
        }
        l=tr[l][qwq];
        r=tr[r][qwq];//继续考虑后一位
    }
    return ans;
}
void insert(int l,int r,int v){
    for(int i=63;i>=0;i--){//同上
        int qwq=(v>>i)&1;
        tr[l][not qwq]=tr[r][not qwq];//复制
        tr[l][qwq]=++point;//新增节点
        cnt[tr[l][qwq]]=cnt[tr[r][qwq]]+1;//记为可以走相反的
        l=tr[l][qwq];
        r=tr[r][qwq];//考虑后一位
    }
    return;
}
int ans;
int s[586][100086];
signed main(){
    std::cin>>n>>m;
    rt[1]=++point;
    insert(rt[1],0,0);//01trie 一定要先插入一个0，以后的插入都是在此基础上做修改
    int c=sqrt(n);
    int len=(n+1)/c;
    if(c*c<n+1)//由于向右移了一格，故处理 01trie 时都是 n+1
        len++;
    id[1]=1;
    for(int i=1;i<=n;i++){
        id[i+1]=i/c+1;//预处理id
        int x;
        std::cin>>x;
        xum[i+1]=xum[i] xor x;//前缀异或和
        rt[i+1]=++point;
        insert(rt[i+1],rt[i],xum[i+1]);//插入当前的xum
    }
    for(int i=1;i<=len;i++){
        ltp[i]=rtp[i-1]+1;
        rtp[i]=std::min(n+1,ltp[i]+c-1);//预处理每个块的左右端点
     }
    for(int i=1;i<=len;i++)
        for(int j=ltp[i]+1;j<=n+1;j++)
            s[i][j]=std::max(s[i][j-1],ask(rt[ltp[i]-1],rt[j],xum[j]));//其中ask是查询sij范围内的最大异或和，也就是上面的M
    while(m--){
        int x,y;
        int l,r;
        std::cin>>x>>y;
		l=std::min((ans+x)%n+1,(ans+y)%n+1);
		r=std::max((ans+x)%n+1,(ans+y)%n+1);
        r++;
        ans=0;
        int st=id[l];
        int ed=id[r];
        if(st==ed)//同块内暴力
            for(int i=l;i<=r;i++)
                ans=std::max(ans,ask(rt[l-1],rt[r],xum[i]));
        else{
            ans=s[st+1][r];//前面处理好了答案
            for(int i=l;i<=rtp[st];i++)
                ans=std::max(ans,ask(rt[l-1],rt[r],xum[i]));
        }
        std::cout<<ans<<"\n";

  }
  return 0;//撒花！
}
```

如有不足，欢迎指正。

---

## 作者：KinNa_Sky (赞：2)

更劣的复杂度！大常数 $O(N^2 + NM)$。

现在我们已经求得 $a$ 的前缀异或和，题意转化成选择 $[l - 1, r]$ 中两个数使其异或最大。

首先这个 $N, M$ 很小啊，但是直接暴力 $O(MN^2)$ 肯定过不去。  
但是这是分块的练习题啊，如果用分块（块长取 $O(\sqrt{N})$）优化暴力就可以 $O(M (\sqrt N)^2)$ 卡过去了。

具体的，我们求一个 $mx_{i, j}$ 表示左端点位于第 $i$ 个块，右端点位于第 $j$ 个块的最大异或值，求一个 $val_{i, j}$ 表示 $i$ 与第 $j$ 个块中的数异或得到的最大异或值。  
这里直接这么求：
```cpp
// #define rep(i, a, b) for (int i = (a); i <= (b); ++i)
rep(i, 1, n) rep(j, i, n)
	chkmax(mx[bel[i]][bel[j]], a[i] ^ a[j]),
	chkmax(val[i][bel[j]], a[i] ^ a[j]),
	chkmax(val[j][bel[i]], a[i] ^ a[j]);
```

然后询问的时候我们分别查区间内的整块与整块、散块与整块、散块与散块的最大值，每部分都是 $O((\sqrt{N})^2)$。

代码：
```cpp
LL qry(int l, int r) {
	LL res = 0;
	if (bel[l] == bel[r]) {
		rep(i, l, r) rep(j, i, r)
			chkmax(res, a[i] ^ a[j]);
	} else {
		rep(i, bel[l] + 1, bel[r] - 1) rep(j, i, bel[r] - 1)
			chkmax(res, mx[i][j]);

		rep(i, l, bR[bel[l]]) rep(j, bel[l] + 1, bel[r] - 1)
			chkmax(res, val[i][j]);
		rep(i, bL[bel[r]], r) rep(j, bel[l] + 1, bel[r] - 1)
			chkmax(res, val[i][j]);

		rep(i, l, bR[bel[l]]) rep(j, i, bR[bel[l]])
			chkmax(res, a[i] ^ a[j]);
		rep(i, bL[bel[r]], r) rep(j, i, r)
			chkmax(res, a[i] ^ a[j]);
		rep(i, l, bR[bel[l]]) rep(j, bL[bel[r]], r)
			chkmax(res, a[i] ^ a[j]);
	}
	return res;
}
```

复杂度不是很优，但是优点是真的暴力，好想。

[Code](https://www.luogu.com.cn/paste/3mr3d2fu) 或者 [Code](https://www.luogu.me/paste/3mr3d2fu#)

---

## 作者：hzoi_Shadow (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10690)

# 前置知识

[可持久化字典树](https://oi-wiki.org//ds/persistent-trie/) | [分块思想](https://oi-wiki.org//ds/decompose/)

# 解法

考虑分块预处理整块的答案，散块直接暴力。

设 $f_{i,j}$ 表示以 $i$ 所在的块的左端点为左端点，$j$ 为右端点的最大异或和，可持久化 01-Trie 维护即可。
  - 本题中这种写法比处理整块到整块的答案更容易处理些。

整块的答案直接继承，枚举散块内的点判断即可。

理论块长取 $\frac{n\sqrt{m \log_{2}{V}}}{m}$，但实测取 $176$ 最快。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
struct PDS_Trie
{
	int root[12010],rt_sum=0;
	struct Trie
	{
		int cnt,ch[2];
	}tree[12010*40];
	int build()
	{
		rt_sum++;
		return rt_sum;
	}
	void insert(int pre,int &rt,int s)
	{
		rt=build();
		int p=rt,q=pre;
		tree[p].cnt=tree[q].cnt+1;
		for(int i=31;i>=0;i--)
		{
			for(int j=0;j<=1;j++)
			{
				tree[p].ch[j]=tree[q].ch[j];
			}
			tree[p].ch[(s>>i)&1]=build();
			p=tree[p].ch[(s>>i)&1];
			q=tree[q].ch[(s>>i)&1];
			tree[p].cnt=tree[q].cnt+1;
		}
	}
	int query(int rt1,int rt2,int s)
	{
		int ans=0;
		for(int i=31;i>=0;i--)
		{
			if(tree[rt2].ch[((s>>i)&1)^1]-tree[rt1].ch[((s>>i)&1)^1]>=1)
			{
				ans|=(1<<i);
				rt1=tree[rt1].ch[((s>>i)&1)^1];
				rt2=tree[rt2].ch[((s>>i)&1)^1];
			}
			else
			{
				rt1=tree[rt1].ch[(s>>i)&1];
				rt2=tree[rt2].ch[(s>>i)&1];
			}
		}
		return ans;
	}
	int ask(int l,int r,int s)
	{
		l++;
		r++;
		return query(root[l-1],root[r],s);
	}
}T;
int L[12010],R[12010],pos[12010],a[12010],sum[12010],f[900][12010],klen,ksum;
void init(int n,int m)
{
	klen=n*sqrt(m*32)/m+1;
	ksum=n/klen;
	for(int i=1;i<=ksum;i++)
	{
		L[i]=R[i-1]+1;
		R[i]=R[i-1]+klen;
	}
	if(R[ksum]<n)
	{
		ksum++;
		L[ksum]=R[ksum-1]+1;
		R[ksum]=n;
	}
	for(int i=1;i<=ksum;i++)
	{
		for(int j=L[i];j<=R[i];j++)
		{
			pos[j]=i;
		}
		for(int j=L[i];j<=n;j++)
		{
			f[i][j]=max(f[i][j-1],T.ask(L[i],j,sum[j]));
		}
	}
}
int query(int l,int r)
{
	int ans=0;
	if(pos[l]==pos[r])
	{
		for(int i=l;i<=r;i++)
		{
			ans=max(ans,T.ask(l,r,sum[i]));
		}
	}
	else
	{
		ans=f[pos[l]+1][r];
		for(int i=l;i<=R[pos[l]];i++)
		{
			ans=max(ans,T.ask(l,r,sum[i]));
		}
	}
	return ans;
}
int main()
{
	int n,m,ans=0,pos=1,l,r,i;
	cin>>n>>m;
	T.insert(T.root[0],T.root[1],0);
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		sum[i]=sum[i-1]^a[i];
		pos++;
		T.insert(T.root[pos-1],T.root[pos],sum[i]);
	}
	init(n,m);
	for(i=1;i<=m;i++)
	{
		cin>>l>>r;
		l=(l%n+ans%n)%n+1;
		r=(r%n+ans%n)%n+1;
		if(l>r)
		{
			swap(l,r);
		}
		ans=query(l-1,r);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：_zuoqingyuan (赞：0)

数据结构题被区间 dp 艹 过去了，这是怎么一回事呢？

下文中 $V$ 表示值域。

我们考虑枚举右端点 $j\in [l,r]$，找到对应的 $i\in [l,j]$ 使 $[i,j]$ 的异或和最大。利用可持久化 trie 可以 $O(\log n)$ 处理单次询问，暴力时间复杂度 $O(n^2\log V)$。

注意到没有修改操作，显然可以预处理；考虑分块（数据范围不大所以直接取块长为 $\sqrt{n}\approx 200$），设 $g_{i,j}$ 表示块 $i\sim j$ 内最大子区间异或和，建出一颗正的可持久化 trie 可以做到 $O(n\sqrt n\log V)$ 预处理。

对于询问，假设左右两个散块为 $p,q$，对答案 $[l,r]$ 分类讨论：

1. $[l,r]$ 在 $p+1\sim q-1$ 块中：直接调用 $g_{p+1,q-1}$。

2. $r$ 在块 $q$ 中：枚举 $q$ 中的每个元素作为右端点，用可持久化 trie 求出对应右端点的最大左端点。时间复杂度 $O(\sqrt n\log V)$。

3. $l$ 在块 $p$ 中：枚举 $p$ 中的每个元素作为左端点，倒着建一个可持久化 trie 求答案。时间复杂度 $O(\sqrt n\log V)$。

因为 $\max$ 具有区间可重复贡献的性质，所以 $l$ 在块 $p$，$r$ 在块 $q$ 的情况重复计算对答案没有影响。

总时间复杂度为 $O((n+q)\sqrt n\log V)$。

~~（代码写的太丑请尽量不要参考）~~。


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int N=12005,V=35,B=200,M=200;
typedef long long ll;
struct DS{
	int tr[N*40][2],mx[N*40],tot,o,rt[N],n;
	ll s[N];
	void init(ll a[],int op,int nn){
		o=op,n=nn;
		if(!o){
			for(int i=1;i<=n;i++)s[i]=s[i-1]^a[i];
		}else{
			for(int i=1;i<=n;i++)s[i]=s[i-1]^a[n-i+1];
		}
		rt[0]=++tot,insert(rt[0],0,0,0ll,V);
		for(int i=1;i<=n;i++){
			rt[i]=++tot;
			insert(rt[i],rt[i-1],i,s[i],V);
		}
	}
	ll ask(int x,int l,int r){
		if(o)x=n-x+1,l=n-l+1,r=n-r+1,swap(l,r);
		return Ask(rt[r-1],l-1,V,s[x],0);
	}
	void insert(int p,int q,int id,ll val,int k){
		if(k<0){
			mx[p]=id;return;
		}else{
			int c=((val>>k)&1);
			tr[p][c^1]=tr[q][c^1];
			tr[p][c]=++tot;
			insert(tr[p][c],tr[q][c],id,val,k-1);
			mx[p]=max(mx[tr[p][c]],mx[tr[q][c]]);
		}
	}
	ll Ask(int p,int lim,int k,ll val,ll ans){
		if(k<0)return ans;
		int c=((val>>k)&1);
		if(!tr[p][c^1]||mx[tr[p][c^1]]<lim)return Ask(tr[p][c],lim,k-1,val,ans);
		else return Ask(tr[p][c^1],lim,k-1,val,ans^(1<<k));
	}
}tr1,tr2;
int n,m,L[M],R[M],pos[N],t;
ll a[N],g[M][M];
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	tr1.init(a,0,n);
	tr2.init(a,1,n);
	t=n/B;
	for(int i=1;i<=t;i++)L[i]=R[i-1]+1,R[i]=i*B;
	if(R[t]<n){t++;L[t]=R[t-1]+1;R[t]=n;}
	for(int i=1;i<=t;i++)for(int j=L[i];j<=R[i];j++)pos[j]=i;
	for(int i=1;i<=t;i++){
		for(int j=i;j<=t;j++){
			if(j>i)g[i][j]=g[i][j-1];
			for(int k=L[j];k<=R[j];k++)g[i][j]=max(g[i][j],tr1.ask(k,L[i],k));
		}
	}
	ll lst=0,l,r;
	while(m--){
		scanf("%d %d",&l,&r);
		l=(l+lst)%n+1,r=(r+lst)%n+1;
		if(l>r)swap(l,r);
		lst=0;
		if(pos[l]==pos[r]){
			for(int i=l;i<=r;i++)lst=max(lst,tr1.ask(i,l,i));
		}else{
			int p=pos[l],q=pos[r];
			lst=g[p+1][q-1];
			for(int i=L[q];i<=r;i++)lst=max(lst,tr1.ask(i,l,i));
			for(int i=l;i<=R[p];i++)lst=max(lst,tr2.ask(i,i,r));
		}
		printf("%lld\n",lst);
	}
	return 0;
}
```

其实 $n,q$ 开到 $5\times 10^4$ 就可以把 dp 冲掉了。

如有错误，请指出。

---

## 作者：CNS_5t0_0r2 (赞：0)

前置知识：[分块](https://www.luogu.com.cn/article/wdfutjma)，[可持久化 0-1 Trie](https://www.luogu.com.cn/article/vgrucytc)。

看到区间异或肯定想到的是求前缀异或，这样就把原问题转化为求区间最大异或对问题。

最大异或对问题的标准做法是 0-1 Trie，但这里是区间问题，所以我们要快速地得到每个区间对应的 0-1 Trie，这里显然就要用到可持久化。

但此时查询的复杂度依然高达 $O(n \log n)$，考虑分块，仿照 [P4168](https://www.luogu.com.cn/problem/P4168) 的思路，预处理第 $i \sim j$ 块之间的最大异或对，查询的时候再额外考虑散块对整个区间的贡献即可。

取块长 $O(\sqrt{n})$，复杂度 $O(n \sqrt{n} \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 12009,SqrtN = 119,LOGV = 32,S = 2,K = N * LOGV * S;
int n,logn,q,ans;
int a[N],s[N];
struct Trie{
	struct node{
		int ch[S];
		int cnt;
	} t[K];
	int Root[N],node_cnt;
	int new_node(){
		return ++node_cnt;
	}
	void insert(int last_u,int u,int x){
    	for(int i = logn;i >= 0;i--){
    		t[u].cnt = t[last_u].cnt + 1;
    	    int c = (x >> i) & 1;
    	    if(!t[u].ch[c])
    	        t[u].ch[c] = new_node();
    	    t[u].ch[c ^ 1] = t[last_u].ch[c ^ 1];
    	    u = t[u].ch[c];
    	    last_u = t[last_u].ch[c];
 	   }
 	   t[u].cnt = t[last_u].cnt + 1;
	}
	int query(int last_u,int u,int x){
    	int ret = 0;
    	for(int i = logn;i >= 0;i--){
    	    int c = (x >> i) & 1;
    	    if(t[t[u].ch[c ^ 1]].cnt - t[t[last_u].ch[c ^ 1]].cnt){
    	        u = t[u].ch[c ^ 1];
    	        last_u = t[last_u].ch[c ^ 1];
    	        ret = (ret << 1) | 1;
    	    }
    	    else{
    	        u = t[u].ch[c];
    	        last_u = t[last_u].ch[c];
    	        ret <<= 1;
    	    }
    	}
   		return ret;
	}
} trie;
struct block{
	int l,r;
} b[SqrtN];
int block_len,block_cnt;
int belong[N];
void build_block(){
	block_len = block_cnt = (int)sqrt(n + 1);
	for(int i = 1;i <= block_cnt;i++){
		b[i].l = b[i - 1].r + 1;
		b[i].r = b[i].l + block_len - 1;
	}
	b[block_cnt].r = n + 1;
	for(int i = 1;i <= block_cnt;i++)
		for(int j = b[i].l;j <= b[i].r;j++)
			belong[j] = i;
}
int p[SqrtN][SqrtN];//第i~j个块中的最大异或对
int Query(int l,int r,int x){//在区间[l,r]中查询与x构成的最大异或对 
 	if(l == 0)
 		return max(x,trie.query(trie.Root[l],trie.Root[r],x));
	return trie.query(trie.Root[l - 1],trie.Root[r],x);
}
void init(){
	for(int i = 1;i <= block_cnt;i++){
		int Max = 0;
		for(int j = i;j <= block_cnt;j++){
			for(int k = b[j].l;k <= b[j].r;k++)
				Max = max(Max,Query(b[i].l,b[j].r,a[k]));
			p[i][j] = Max;
		}
	}
}
int query(int l,int r){
	int pos_l = belong[l],pos_r = belong[r];
	int ret = 0;
	if(pos_l == pos_r){
		for(int i = l;i <= r;i++)
			ret = max(ret,Query(l,r,a[i - 1]));
		return ret;
	}
	ret = p[pos_l + 1][pos_r - 1];
	for(int i = l;i <= b[pos_l].r;i++)
		ret = max(ret,Query(l,r,a[i - 1]));
	for(int i = b[pos_r].l;i <= r;i++)
		ret = max(ret,Query(l,r,a[i - 1]));
	return ret;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> q;
	logn = 30;
	build_block();
	trie.Root[0] = trie.new_node();
	for(int i = 1;i <= n;i++){
		cin >> a[i];
		a[i] ^= a[i - 1];
		trie.Root[i] = trie.new_node();
		trie.insert(trie.Root[i - 1],trie.Root[i],a[i - 1]);
	}
	trie.Root[n + 1] = trie.new_node();
	trie.insert(trie.Root[n],trie.Root[n + 1],a[n]);
	init();
	while(q--){
		int l,r;
		cin >> l >> r;
		l = (l + ans) % n + 1;
		r = (r + ans) % n + 1;
		if(l > r)
			swap(l,r);
		l++;r++;
		ans = query(l - 1,r);
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Filberte (赞：0)

对原数列求前缀亦或和，记为 $s$ 序列。问题转化为每次给定 $l,r$，选出 $x,y\in[l-1,r]$，最大化 $s_x \oplus s_y$ 的值。读者需要掌握的是，使用可持久化字典树，先进行 $O(n\log V)$ 的预处理，之后若给定常数 $v$，可以在 $O(\log V)$ 的时间复杂度内求出 $\max\limits_{x = l}^r s_x \oplus v$。若不了解此算法详细流程，可以参照 [P4735](https://www.luogu.com.cn/problem/P4735)。

考虑按 $\sqrt n$ 为大小分块。记 $L_i$ 表示第 $i$ 个块的左端点。用 $f_{i,j}$ 表示选择 $x,y\in[L_i,j]$， $s_x \oplus s_y$ 的值最大是多少。先把 $f$ 数组预处理出来。若已知 $f_{i,j}$，想要计算 $f_{i,j+1}$，无非就是选择 $x\in[L_i,j]$，最大化 $s_x \oplus s_{j+1}$ ，则有以下转移：$f_{i,j+1} = \max(f_{i,j},s_x\oplus s_{j+1})$，可以在 $O(n\log V)$ 的复杂度内计算出某一个 $i$ 对应的 $f$ 值。一共有 $\sqrt n$ 个不同的块，所以预处理的总复杂度是 $O(n\sqrt n\log V)$。

对于每组询问 $(l,r)$，找到第一个整块的编号记为 $i$，则 $f_{i,r}$ 可以就可以表示出所有左端点落在 $L_i$ 右边的区间的最大值。而对于落在 $L_i$ 左侧的左端点 $p$ 最后只有 $\sqrt n$ 个，暴力求出 $x\in [l,r]$ 使得 $s_x \oplus s_p$ 的值最大，这可以在 $O(\sqrt n \log V)$ 的复杂度内求出这 $\sqrt n$ 个散点答案的最大值。共有 $m$ 组询问，复杂度是 $O(m \sqrt n\log v)$。

总复杂度 $O((n+m)\sqrt n\log v)$，调一下块长实际上跑的很快。实现的时候可以先往字典树里插入一个 $0$，这样就不用考虑各种边界问题了。

代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 12500, M = 120;
struct Trie{
    static const int maxn = 1e6;
    int rt[N], vers = 0;
    int ch[maxn][2], val[maxn], cnt = 0;
    void Insert(int v){
        rt[++vers] = ++cnt;
        ins(rt[vers], rt[vers - 1], v);
    }
    void Clear(){
        for(int i = 1;i <= vers;i++) rt[i] = 0;
        vers = 0;
        for(int i = 1;i <= cnt;i++) val[i] = ch[i][0] = ch[i][1] = 0;
        cnt = 0;
        Insert(0);
    }
    void ins(int u, int od, int v){
        for(int i = 31;i >= 0;i--){
            int c = ((v >> i) & 1);
            ch[u][c ^ 1] = ch[od][c ^ 1];
            if(!ch[u][c]) ch[u][c] = ++cnt;
            u = ch[u][c], od = ch[od][c];
            val[u] = val[od] + 1;
        }
    }  
    int Query(int l, int r, int v){ // l ~ r xor v 的最大值
        int x = rt[l], y = rt[r + 1];
        int res = 0;
        for(int i = 31;i >= 0;i--){
            int c = (((v >> i) & 1) ^ 1);
            if(val[ch[y][c]] - val[ch[x][c]] > 0){
                res |= (1 << i);
                x = ch[x][c], y = ch[y][c];
            }
            else x = ch[x][c ^ 1], y = ch[y][c ^ 1];
        }
        return res;
    }
}T;

int n, m, a[N];
struct Block{
    int loc[N], L[M], R[M];
    int len, cnt;
    int Mx[M][N];
    void init(){
        len = sqrt(n) + 1, cnt = (n - 1) / len + 1;
        for(int i = 1;i <= cnt;i++){
            L[i] = (i - 1) * len + 1;
            R[i] = (i == cnt) ? n : i * len;
            for(int j = L[i];j <= R[i];j++) loc[j] = i;
            for(int j = L[i];j <= n;j++){
                Mx[i][j] = max(Mx[i][j - 1], T.Query(L[i], j, a[j]));
            }
        }
    }
    int Query(int l, int r){
        int res = 0;
        if(loc[l] == loc[r]){
            for(int i = l;i <= r;i++) res = max(res, T.Query(l, r, a[i]));
            return res;
        }
        res = Mx[loc[l] + 1][r];
        for(int i = l;i <= R[loc[l]];i++) res = max(res, T.Query(l, r, a[i]));
        return res;
    }
}b;
int main(){
    cin >> n >> m;
    T.Clear();
    for(int i = 1;i <= n;i++){
        cin >> a[i];
        a[i] ^= a[i - 1];
        T.Insert(a[i]);
    }
    b.init();
    for(int _t = 1, lst = 0;_t <= m;_t++){
        long long x, y;
        cin >> x >> y;
        x = (x % n + lst % n) % n + 1;
        y = (y % n + lst % n) % n + 1;
        if(x > y) swap(x, y);
        cout << (lst = b.Query(x - 1, y)) << endl;
    }
    return 0;
}
```

---

