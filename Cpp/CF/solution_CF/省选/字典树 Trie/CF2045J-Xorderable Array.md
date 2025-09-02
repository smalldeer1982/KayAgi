# Xorderable Array

## 题目描述

给定一个整数数组 $A$，包含 $N$ 个元素，记作 $[A_1, A_2, \dots, A_N]$。

如果可以重新排列数组 $A$，使得对任意 $1 \leq i < j \leq N$ 的索引对 $(i, j)$，阵列满足：$A_i \oplus p \leq A_j \oplus q$ 且 $A_i \oplus q \leq A_j \oplus p$，那么称数组 $A$ 为 $(p, q)$-可排序的，其中 $\oplus$ 表示按位异或。

另有一个长度为 $M$ 的整数数组 $X$：$[X_1, X_2, \dots, X_M]$。求出所有满足 $1 \leq u < v \leq M$ 且数组 $A$ 可以是 $(X_u, X_v)$-可排序的索引对 $(u, v)$ 的数量。

## 说明/提示

关于样例的说明：
- 在样例 1 中，通过将数组 $A$ 重新排列为 $[0, 0, 3]$，可以达到 $(1, 1)$-可排序的要求。
- 在样例 2 中，通过将数组 $A$ 重新排列为 $[13, 0, 7, 24, 22]$，数组 $A$ 可以满足 $(12, 10)$-可排序条件。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3 4
0 3 0
1 2 1 1```

### 输出

```
3```

## 样例 #2

### 输入

```
5 2
0 7 13 22 24
12 10```

### 输出

```
1```

## 样例 #3

### 输入

```
3 3
0 0 0
1 2 3```

### 输出

```
0```

# 题解

## 作者：_jimmywang_ (赞：5)

阴间结论题。

观察那个奇奇怪怪的条件，$A_i \oplus p \le A_j \oplus q$ 且 $A_i \oplus q \le A_j \oplus p$。

为了简单起见，我们考虑 $(A_i,A_j,p,q)=(A,B,P,Q)$ 的时候这个条件的等价条件。

你发现你需要在有二进制操作的时候比较大小，那么我们选择按位比较。假设当前 $A,B,P,Q$ 的二进制位分别是 $a,b,p,q$（为了方便，使用了和最开始条件一样的小写 $p,q$，注意区分）。

官方题解使用了一定的逻辑推理，但是我不想看。所我列出一个类似真值表的东西。

$\begin{array}{|c c c c||c|}a&b&p&q&\text{判定结果}\\0&0&0&0\\0&0&0&1&\times\\0&0&1&0&\times\\0&0&1&1\\0&1&0&0&\checkmark\\0&1&0&1\\0&1&1&0\\0&1&1&1&\times\\1&0&0&0&\times\\1&0&0&1\\1&0&1&0\\1&0&1&1&\checkmark\\1&1&0&0\\1&1&0&1&\times\\1&1&1&0&\times\\1&1&1&1\\\end{array}$

其中 $\times$ 这一位出现了不符合条件（出现了大于），已经确定不符合，后面不用比了；$\checkmark$ 表示这一位两个条件都是小于（不是小于等于），已经确定符合，后面不用比了。留空则表示不违反当前条件，还得往下一位比。

使用一些注意力，你会发现：
- 1. $a \oplus b < p \oplus q$ 时，不符合条件。
- 2. $a \oplus b = p \oplus q$ 时，需要继续比。
- 3. $a \oplus b > p \oplus q$ 时，比较复杂，详细讨论：

这种情况中有两个 $\checkmark:(a,b,p,q)=(0,1,0,0)(1,0,1,1)$ 和两个 $\times:(a,b,p,q)=(0,1,1,1)(1,0,0,0)$。这意味着当且仅当遇到这种情况时，整个条件能被这一位的 $\times \checkmark$ 决定（因为表上没有留空的情况），即 不用往下一位比较了。

那么如果 $(A,B,P,Q)$ 在这某一位因为这种情况不符合条件了（获得一个 $\times$），我们惊奇的发现，$(B,A,P,Q)$ 将会在这一位获得一个 $\checkmark$（可以通过在这一位交换 $a,b$ 的值，去表上看一眼来发现）。所以结论是：

- 3. $a \oplus b > p \oplus q$ 时，$(A,B,P,Q)$ 和 $(B,A,P,Q)$ 中有一个符合条件。

所以综合所有结论的逻辑过程，我们得到这等价于从高位到低位比较 $P \oplus Q $ 和 $ A\oplus B$。

所以最后的结论是：

- $(A,B,P,Q)$ 和 $(B,A,P,Q)$ 中有一个符合条件，当且仅当 $P \oplus Q \le A\oplus B$。

好！

接下来扩展到序列，如果序列 $a_1,a_2,\dots,a_n$ 对 $(p,q)$ 合法，那么一定有 $\forall 1\le i < j \le n, p \oplus q \le a_i \oplus a_j$。即 $p \oplus q \le \min_{i\neq j}\{a_i \oplus a_j\}$。

而充分性，可以把 $a$ 按照 $a_i\oplus(p \& q)$ 排序，即可得到合法方案。

因此整个条件等价于 $p \oplus q \le \min_{i\neq j}\{a_i \oplus a_j\}$。

那就好办了，先用 01-trie 求出 $\min_{i\neq j}\{a_i \oplus a_j\}$，然后在逐个插入 $X_i$ 的过程中，逐个计算 $X_i \oplus X_j \le \text{前面算的最小值}$ 的 $j$ 的个数，这也可以 01-trie。

于是，做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define wt int tt=d;while(tt--)
#define py puts("Yes")
#define pn puts("No")
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
namespace binom{
	const ll Lim=300010,mod=998244353;
	ll jc[Lim],inv[Lim],inc[Lim];
	void pre(){
		jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
		f(i,2,Lim-1)jc[i]=jc[i-1]*i%mod,inv[i]=(mod-mod/i)*inv[mod%i]%mod,
		inc[i]=inc[i-1]*inv[i]%mod;
	}ll C(ll n,ll m){if(n<0||m<0||n<m)return 0;return jc[n]*inc[m]%mod*inc[n-m]%mod;}
}
// using namespace binom;
ll dx[4]={0,1,0,-1};
ll dy[4]={1,0,-1,0};
#define d rd()
#define pb push_back
ll qp(ll a,ll b,ll p){
	ll ans=1;while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;b>>=1;
	}return ans;
}ll n,m;
ll tr[7000010][2],cnt=1;
ll sz[7000010];
void add(ll x){
    ll u=1;sz[u]++;
    for(int i=30;i>=0;i--){
        ll p=(x>>i)&1;
        if(!tr[u][p])tr[u][p]=++cnt;
        u=tr[u][p];sz[u]++;
    }
}ll get(ll x){
    ll res=0,u=1;
    for(int i=30;i>=0;i--){
        ll p=(x>>i)&1;
        if(tr[u][p])u=tr[u][p];
        else u=tr[u][p^1],res+=(1<<i);
    }return res;
}
ll mn=(1<<30);
ll ask(ll x){
    // cout<<"Running query for "<<x<<endl;
    ll res=0,u=1;
    for(int i=30;i>=0;i--){
        ll p=(mn>>i)&1,q=(x>>i)&1;
        // cout<<"Querying for "<<p<<" and "<<q<<endl;
        if((q^0)<p)res+=sz[tr[u][0]];
        if((q^1)<p)res+=sz[tr[u][1]];
        if((q^0)==p)u=tr[u][0];
        if((q^1)==p)u=tr[u][1];
        if(!u)break;
    }return res;
}
long long res;
int main(){
	n=d,m=d;
    add(d);f(i,2,n){
        ll x=d;mn=min(mn,get(x));
        add(x);
    }mn++;
    f(i,1,cnt)tr[i][0]=tr[i][1]=0,sz[i]=0;cnt=1;
    add(d);f(i,2,m){
        ll x=d;res+=ask(x);
        add(x);
    }cout<<res;

	return 0;
}
```

---

## 作者：spdarkle (赞：0)

可以考虑先手摸一下一对 $(a,b)$ 与 $(p,q)$ 的比较过程，显然按位运算独立，以下为按位讨论，从高位往下比较。

- $p=q=0$，此时若 $a\neq b$，则必须 $0$ 放在 $1$ 前面，否则继续比较下一位。
- $p=q=1$，此时若 $a\neq b$，则必须 $1$ 放在 $0$ 前面，否则继续比较下一位。
- $p\neq q$，此时若 $a=b$，则非法，否则继续比较下一位。

可以发现每次若 $p\oplus q=a\oplus b$，则继续比较，否则结果立出，但是 $p\neq q$ 不可能作为合法终止位，可以得到：

- $p\oplus q=a\oplus b$：两者顺序可以任意。
- $p\oplus q>a\oplus b$：两者无论如何放都非法。
- $p\oplus q<a\oplus b$：两者最终顺序固定。

由此可以得到一个必要条件：$p\oplus q\le \min_{i\neq j}{a_i\oplus a_j}$。

可以发现这也是充分的，证明如下：

考虑 $a,b,c$，设 $a\oplus b\neq p\oplus q,a\oplus c\neq p\oplus q,b\oplus c\neq p\oplus q$。

若现在我们根据比对 $(a,b),(b,c)$，已知摆放顺序是 $a,b,c$，则只需证明可以推出 $a$ 放在 $c$ 前面是可行的（本质上是推传递性）。

考虑 $(a,b),(b,c)$ 比对时，其比较结果确定的位置分别是 $t_1,t_2$，注意是从高到低位。

则有：

1. $a,c$ 在 $\max(t_1,t_2)+1\sim high$ 是相同的，其中 $high$ 表示最高位。
2. 在 $\max(t_1,t_2)$ 这一位，$a,c$ 不同。

由于 $p\oplus q<a\oplus c$，因此在 $\max(t_1,t_2)+1\sim high$，$p,q$ 这些位置都是零。

在 $\max(t_1,t_2)$ 这一位，$p,q$ 必然相同，否则比较结果不会在这里确定。

可以分类讨论：

- $b$ 这一位为 $1$。

  - $p,q$ 这一位为 $0$。
    - $a$ 这一位为 $1$，则 $c$ 在 $b$ 前面，矛盾。
    - $a$ 这一位为 $0$，可以推出 $c$ 这一位为 $1$，合法。
  - $p,q$ 这一位为 $1$。
    - $a$ 这一位为 $0$，则 $a$ 在 $b$ 后面，矛盾。
    - $a$ 这一位为 $1$，可以推出 $c$ 这一位为 $0$，合法。

- $b$ 这一位为 $0$。

  - $p,q$ 这一位为 $0$。

    - $a$ 这一位为 $1$，则 $a$ 在 $b$ 后面，矛盾。
    - $a$ 这一位为 $0$，可以推出 $c$ 这一位为 $1$，合法。

  - $p,q$ 这一位为 $1$。

    - $a$ 这一位为 $0$，则c$ 在 $b$ 前面，矛盾。

    - $a$ 这一位为 $1$，可以推出 $c$ 这一位为 $0$，合法。

对于所有的合法情况，都说明了 $a$ 在 $c$ 前面，因此本条件充分。

我们求出 $\min_{i\neq j} a_i\oplus a_j$，这是简单的，将 $a$ 排序后取相邻元素异或取最小值即可。

然后就是 Trie 树的经典问题了。

---

