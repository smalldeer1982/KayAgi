# 【MX-X9-T3】『GROI-R3』Powerless

## 题目背景

> 你能走到这里很了不起......

## 题目描述

白给了你一个长度为 $n$ 的整数序列 $a_1,\ldots, a_n$ 和一个整数 $m$，她请你求出以下式子的值：

$$ \sum_{i=1}^n \sum_{j=1}^n \sum_{k=0}^m \min(a_i \oplus k, a_j \oplus k)$$

其中，$\oplus$ 表示二进制下按位异或。

由于答案可能很大，所以你仅需要输出答案对 $998244353$ 取模后的值。

## 说明/提示

**【样例解释 #1】**

当 $i = j = 1$ 时，$\sum\limits_{k=0}^m \min(x_i \oplus k, x_j \oplus k) = (1 \oplus 0) + (1 \oplus 1) + (1 \oplus 2) + (1 \oplus 3) = 1 + 0 + 3 + 2 = 6$；

当 $i = j = 2$ 时，$\sum\limits_{k=0}^m \min(x_i \oplus k, x_j \oplus k) = (5 \oplus 0) + (5 \oplus 1) + (5 \oplus 2) + (5 \oplus 3) = 5 + 4 + 7 + 6 = 22$；

当 $i = 1, j = 2$ 或 $i = 2, j = 1$ 时，$\sum\limits_{k=0}^m \min(x_i \oplus k, x_j \oplus k) = \min(1, 5) + \min(0, 4) + \min(3, 7) + \min(2, 6) = 6$。

因此，答案为 $6 + 22 + 6 \times 2 = 40$。

**【数据范围】**

**本题采用捆绑测试。**

| 子任务编号 | $n\le$ | $m\le$ | $a_i\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| 1 | $100$ | $100$ | $100$ |  | $1$ |
| 2 | $2\times 10^5$ | $0$ | $10^9$ |  | $8$ |
| 3| $3000$ | $10^6$ | $10^6$ |  | $21$ |
| 4 | $2\times 10^5$ | $10^6$ | $10^9$ |  | $16$ |
| 5 | $2\times 10^5$ | $10^9$ | $10^9$ | A | $9$ |
| 6 | $2\times 10^5$ | $10^9$ | $10^9$ | B | $24$ |
| 7 | $2\times 10^5$ | $10^9$ | $10^9$ |  |  $21$ |

- 特殊性质 A：保证 $a_1 = a_2 = \cdots = a_n$。
- 特殊性质 B：保证存在非负整数 $k$ 使得 $m = 2^k - 1$。

对于 $100\%$ 的数据，保证 $1 \leq n \leq 2\times 10^5$，$0 \leq m \leq 10^9$，$0 \leq a_i \leq 10^9$。

## 样例 #1

### 输入

```
2 3
1 5
```

### 输出

```
40
```

## 样例 #2

### 输入

```
5 7
1 2 3 4 5
```

### 输出

```
460
```

## 样例 #3

### 输入

```
10 197
1 5 102 289 445 326 117 64 100 266
```

### 输出

```
2788560
```

## 样例 #4

### 输入

```
10 0
3701780 6015893 9822195 8016360 992671 8828219 5674666 4815987 1784800 995151
```

### 输出

```
333221210
```

## 样例 #5

### 输入

```
8 33554432
2117455 10849252 28912108 3049487 10134324 20812345 26061978 24220183
```

### 输出

```
42695030
```

## 样例 #6

### 输入

```
8 51937970
93102591 5826965 25429632 51808294 13143740 21293750 85706705 22127009
```

### 输出

```
345700571
```

## 样例 #7

### 输入

```
13 189320127
90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115 90228115
```

### 输出

```
425145733
```

## 样例 #8

### 输入

```
10 1000000000
530093637 530093637 530093637 540208320 451233002 540208320 540208320 895132935 619514612 895132935
```

### 输出

```
644847220
```

# 题解

## 作者：UniGravity (赞：7)

提供一种没啥思维难度的做法，理清思路后也并不算难写。

记 $k_p$ 表示 $k$ 二进值下第 $p$ 位。

先考虑如何判断 $a_i\neq a_j$ 的相对大小，假设 $a_i,a_j$ 第一个不同的位在 $p$。假设有 $a_i<a_j$，则 $k_p=0$ 时 $a_i\oplus k<a_j\oplus k$，否则 $a_i\oplus k>a_j\oplus k$。而其它位的情况并不会对该位造成影响。

考虑对于 $x=a_i$ 找出其作为最小值时的贡献。对 $a$ 从小到大排序，那么发现 $x,a_j$ 第一个不同的位在 $p$ 且 $x<a_j$ 的 $j$ 必定是一段**连续区间**，可以通过二分找出。然后考虑拆位统计 $x$ 的贡献。假设当前贡献的位为 $t$，则变成我们需要统计 $k_p=1$ 且 $k_t\neq x_t$ 的 $k\in[0,m]$ 的数量。

记 $\operatorname{cnt}(p_1,v_1,p_2,v_2)$ 表示 $k_{p_1}=v_1\wedge k_{p_2}=v_2$ 的 $k$ 的数量。如果直接对每个 $p_1,p_2$ 都跑一遍数位 dp 就是 $O(n\log^3V)$ 的了，不太牛。但是发现这个式子是可以通过分类讨论和位运算直接算出来的。

假设 $v_1=1$，类似数位 dp 的思路分成到达 $p_1$ 时是否取到上界。如果没取到则之后的位可以随意取，否则我们再记 $\operatorname{cnt1}(p,v,m)$ 表示 $k_p=v$ 且 $k\in[0,m]$ 的 $k$ 的数量。则发现问题转化为了求上面这个式子。这个式子同样可以通过分类讨论是否取到上界来计算贡献。这里建议自己画图推一下，其实只是有点复杂，并不算难。

这样我们就可以做到 $O(1)$ 求 $\operatorname{cnt}(p_1,v_1,p_2,v_2)$。那么即可 $O(n\log^2V)$ 求所有 $a_i<a_j$ 的贡献。当然还有 $a_i>a_j$ 的贡献，要求变成了 $k_p=1$，同样做即可。

最后还要算上与自己相同值的贡献，因此一开始需要对 $a$ 去重并统计每个值出现次数。时间复杂度 $O(n\log^2V)$。

```cpp
const int N=200005,P=998244353;
int n,m,a[N],tmp[N],c[N],s[N];
il int findr(int l,int v,int k){
    int r=n,mid,ans=1;
    while(l<=r){
        mid=(l+r)>>1;
        if((a[mid]>>k)==(v>>k))ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}
il int findl(int r,int v,int k){
    int l=1,mid,ans=n;
    while(l<=r){
        mid=(l+r)>>1;
        if((a[mid]>>k)==(v>>k))ans=mid,r=mid-1;
        else l=mid+1;
    }
    return ans;
}
il int c1(int p,int v,int m){
    int ans=0;
    if(v==1){
        ans=(m>>(p+1))*(1<<p);
        if((m>>p)&1)ans+=m&((1<<p)-1),ans++;
    }else{
        if((m>>p)&1)ans=((m>>(p+1))+1)*(1<<p);
        else ans=(m>>(p+1))*(1<<p),ans+=m&((1<<p)-1),ans++;
    }
    return ans;
}
il int count(int p1,int v1,int p2,int v2){
    if(p1==p2){
        if(v1!=v2)return 0;
        else return c1(p1,v1,m);
    }else if(p2>p1)return count(p2,v2,p1,v1);
    int ans=0;
    if(v1){
        ans=(m>>(p1+1))*(1<<(p1-1));
        if((m>>p1)&1)ans+=c1(p2,v2,m&((1<<p1)-1));
    }else{
        if((m>>p1)&1)ans=((m>>(p1+1))+1)*(1<<(p1-1));
        else{
            ans=(m>>(p1+1))*(1<<(p1-1));
            ans+=c1(p2,v2,m&((1<<p1)-1));
        }
    }
    return ans;
}

signed main(){
    int n1=read();n=0,m=read();tmp[0]=-1;
    forto(i,1,n1)tmp[i]=read();sort(tmp+1,tmp+n1+1);
    forto(i,1,n1)if(tmp[i]==tmp[i-1])c[n]++;else a[++n]=tmp[i],c[n]=1;
    forto(i,1,n)s[i]=s[i-1]+c[i];
    int l,r,ans=0,cnt;
    forto(i,1,n){
        forv(k,31){
            if(!((a[i]>>k)&1)){
                l=findr(i,a[i],k)+1,r=findr(i,a[i],k+1);if(l>r)continue;
                forv(k1,31)ans+=1ll*count(k,0,k1,((a[i]>>k1)&1)^1)*(1ll<<k1)%P*(s[r]-s[l-1])%P*c[i]%P,ans%=P;
            }else{
                l=findl(i,a[i],k+1),r=findl(i,a[i],k)-1;if(l>r)continue;
                forv(k1,31)ans+=1ll*count(k,1,k1,((a[i]>>k1)&1)^1)*(1ll<<k1)%P*(s[r]-s[l-1])%P*c[i]%P,ans%=P;
            }
        }
    }
    ans=2*ans%P;
    forto(i,1,n)forv(k,31)ans=(ans+1ll*c[i]*c[i]%P*c1(k,((a[i]>>k)&1)^1,m)%P*(1<<k)%P)%P;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：是青白呀 (赞：7)

预处理出 $f_{i,j,0/1,0/1}$ 表示 $\le m$ 的所有数中，第 $i$ 位为 $0/1$ 且第 $j$ 位为 $0/1$ 的数的数量；$g_i$ 表示 $\le m$ 的所有数中，第 $i$ 位为 $1$ 的数的数量。可以使用数位 dp 求这两个数组，枚举首个 $<m$ 的位即可。

对于 $a_i=a_j$ 的情况，开个桶并利用 $g$ 数组特殊处理即可。下面只考虑 $a_i<a_j$ 的情况，注意求出来的值要乘 $2$。

考虑把所有 $a_i$ 插入 01 Trie，在 Trie 上枚举每一个 $a_i$，并枚举其与 $a_j$ 首个不同的位置。然后再枚举每一位，统计有多少个不同的 $k$ 和 $a_j$ 会在这一位上作出贡献，其中 $k$ 需要满足在当前位与 $a_i$ 相同，在贡献位与 $a_i$ 不同，个数可以利用预处理的 $f$ 简单求出；$a_j$ 需要满足在当前位与 $a_i$ 不同且在之前的位与 $a_i$ 相同，可以通过在 Trie 上维护子树中的元素个数快速得到。

总复杂度 $O(n\log^2V)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define pii pair<int,int>
#define mp make_pair
#define fir first
#define sec second
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define lowbit(i) (i&-i)
#define int long long
#define qingbai qwq
using namespace std;
typedef long long ll;
const int N=2e5+5,M=2e6+5,mo=998244353,inf=(ll)1e18+7;
const double PI=acos(-1);
void read(int &a){
    int x=0,w=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')w=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+ch-'0';
        ch=getchar();
    }
    a=x*w;
}
int n,m,a[N];
int ch[N*31][2],sz[N*31],cntp=1,rt=1;
int f[31][31][2][2],g[31];
int ans=0;
void insert(int &x,int dep,int v){
    if(!x)x=++cntp;
    if(!dep){
        sz[x]++;
        return;
    }
    insert(ch[x][(v>>(dep-1))&1],dep-1,v);
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]];
}
void dfs(int x,int dep,int v){
    if(!x)return;
    if(!dep)return;
    int nxtv=(v>>(dep-1))&1;
    if(!nxtv){
        rep(j,0,29){
            if((v>>j)&1)ans+=f[dep-1][j][0][0]*sz[ch[x][1]]%mo*(1<<j);
            else ans+=f[dep-1][j][0][1]*sz[ch[x][1]]%mo*(1<<j);
            ans%=mo;
        }
    }
    else{
        rep(j,0,29){
            if((v>>j)&1)ans+=f[dep-1][j][1][0]*sz[ch[x][0]]%mo*(1<<j);
            else ans+=f[dep-1][j][1][1]*sz[ch[x][0]]%mo*(1<<j);
            ans%=mo;
        }
    }
    dfs(ch[x][nxtv],dep-1,v);
}
unordered_map<int,int>cnt;
signed main(){
    read(n),read(m);
    rep(i,1,n)
        read(a[i]),insert(rt,30,a[i]),cnt[a[i]]++;
    rep(i,0,29){
        if(!((m>>i)&1))continue;
        else g[i]++;
        rep(j,0,i-1)
            g[j]+=(1<<(i-1));
        rep(j,i+1,29)
            if((m>>j)&1)g[j]+=1<<i;
    }
    rep(i,0,29){
        rep(j,0,i-1){
            f[i][j][(m>>i)&1][(m>>j)&1]++;
            rep(k,0,29){
                if(!((m>>k)&1))continue;
                if(k>i){
                    rep(x,0,1){
                        rep(y,0,1)
                            f[i][j][x][y]+=1<<(k-2),f[i][j][x][y]%=mo;
                    }
                }
                else if(k==i){
                    rep(y,0,1)
                        f[i][j][0][y]+=1<<(k-1),f[i][j][0][y]%=mo;
                }
                else if(k>j){
                    rep(y,0,1)
                        f[i][j][(m>>i)&1][y]+=1<<(k-1),f[i][j][(m>>i)&1][y]%=mo;
                }
                else if(k==j)f[i][j][(m>>i)&1][0]+=1<<k,f[i][j][(m>>i)&1][0]%=mo;
                else f[i][j][(m>>i)&1][(m>>j)&1]+=1<<k,f[i][j][(m>>i)&1][(m>>j)&1]%=mo;
            }
        }
        f[i][i][0][0]=m+1-g[i],f[i][i][1][1]=g[i];
    }
    rep(i,0,29){
        rep(j,i+1,29){
            rep(x,0,1){
                rep(y,0,1)
                    f[i][j][x][y]=f[j][i][y][x];
            }
        }
    }
    rep(i,1,n)
        dfs(rt,30,a[i]);
    ans*=2,ans%=mo;        
    rep(i,1,n){
        rep(j,0,29){
            if((a[i]>>j)&1)ans+=(m+1-g[j])*cnt[a[i]]%mo*(1<<j);
            else ans+=g[j]*cnt[a[i]]%mo*(1<<j);
            ans%=mo;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：modfish_ (赞：6)

下面是十分复杂且比较电波（？的 DP。我相信其他题解的会更简单，请酌情观看。

## 思路
考虑交换求和顺序：

$$\sum_{k=0}^m\sum_{i=1}^n\sum_{j=1}^n\min(a_i\oplus k,a_j\oplus k)$$

考虑内层求和如何计算。不妨考虑每个数 $i$ 的贡献。不难推得，令数列 $b_k$ 表示 $a_i\oplus k$ 构成的序列，$b_{k,i}=a_i\oplus k$。并记 $rk_{k,i}$ 表示 $b_{k,i}$ 在 $b_k$ 中大小的排名（从小往大排）。那么有：

$$
\begin{aligned}
&\sum_{i=1}^n\sum_{j=1}^n\min(a_i\oplus k,a_j\oplus k)\\=&\sum_{i=1}^n(a_i\oplus k)\times(2(n-rk_{k,i})+1))\\=&(2n+1)\sum_{i=1}^nb_{k,i}-2\sum_{i=1}^nrk_{k,i}b_{k,i}
\end{aligned}
$$

考虑建出 Trie 树在上面 DP。

我们定义一个二元组 $(k,i)$ 为一个单元，定义其权值 $\text{val}(k,i)=(2n+1)b_{k,i}-2rk_{k,i}b_{k,i}$。我们要求的即为每一个单元的权值和。

这个权值与 $i$ 的相关性不大，或者说计算一个 $i$ 的权值，不需要事先知道其余 $i$ 的权值。我们考虑将 $k$ 视作对 0-1 Trie 的每一个节点的左右子树的一种翻转方案。在一棵独立的子树内，我们计算所有可能的翻转方案中，$i$ 的权值之和，通过 DP 转移即可得到答案。

先不考虑 $m$ 的限制。设 $f_x,g_x,q_x,h_x$ 分别表示：

- $f_x$ 表示对 $x$ 这棵子树进行翻转的方案数（对于每一个 $i$ 都要计算并加和）。
- $g_x$ 表示对 $x$ 这棵子树进行翻转的所有方案中，所有 $b_{k,i}$ 的总和。
- $q_x$ 表示对 $x$ 这棵子树进行翻转的所有方案中，所有 $rk_{k,i}$ 的总和。
- $h_x$ 表示对 $x$ 这棵子树进行翻转的所有方案中，所有 $rk_{k,i}b_{k,i}$ 的总和。

下面讨论如何转移。

对于 $f_x$，显然，左右子树都会产生贡献，而左右子树是否互换会给方案翻倍。故：

$$f_x=2(f_{lc}+f_{rc})$$

对于 $g_x$，分成不翻转左右子树，与翻转左右子树两种情况进行转移：

$$g_x=(g_{lc}+g_{rc}+pw\times f_{rc})+(g_{lc}+pw\times f_{lc}+g_{rc})$$

其中 $pw$ 表示 0-1 Trie 上这一节点的二进制位值。第一个括号表示不翻转，此时右子树的左边多出来了一棵左子树，故所有单元的 $b_{k,i}$ 都多出了 $pw$，故要加上。第二个括号表示翻转，意义类似。

$q_x$ 类似于 $g_x$：

$$ q_x=(q_{lc}+q_{rc}+siz_{lc}\times f_{rc})+(q_{lc}+siz_{rc}\times f_{lc}+q_{rc})$$

其中 $siz_x$ 表示 $x$ 的子树内有多少个被插入的 $a_i$。转移原理与 $g_x$ 相同，若不翻转，右子树中每个单元的 $rk_{k,i}$ 会多出 $siz_{lc}$，所以要加上。

而 $h_x$ 较为复杂。我们先思考：假设我们要给下式中：

$$\sum rk_{k,i}b_{k,i}$$

的 $rk_{k,i}$ 与 $b_{k,i}$ 分别加上 $\Delta r$ 与 $\Delta b$，则其变为：

$$\sum rk_{k,i}b_{k,i}+\Delta r\sum b_{k,i}+\Delta b\sum rk_{k,i}+\Delta r\Delta b\sum1$$

于是根据以上原理可以导出如下转移：

$$h_x=(h_{lc}+h_{rc}+pw\times q_{rc}+siz_{lc}\times g_{rc}+pw\times siz_{lc}\times f_{rc})\\+(h_{lc}+pw\times q_{lc}+siz_{rc}\times g_{lc}+pw\times siz_{rc}\times f_{lc}+h_{rc})$$

以第一个括号为例，$h_{rc}$ 对应 $\sum rk_{k,i}b_{k,i}$，$siz_{lc}$ 对应 $\Delta r$，$pw$ 对应 $\Delta b$，$g_{rc}$ 对应 $\sum b_{k,i}$，$q_{rc}$ 对应 $\sum rk_{k,i}$，$f_{rc}$ 对应 $\sum1$。

于是转移完成了。那么问题来了，有 $m$ 的限制有如何呢？

翻转一个节点的左右子树，就是在决定 $k$ 的这一位是否为 $1$。所以只要多设一维状态即可：

设 $f_{x,0/1},g_{x,0/1},q_{x,0/1},h_{x,0/1}$。其中 $0$ 表示：当前所有翻转方案的 $k$ 均无限制；$1$ 表示：当前所有翻转方案的 $k$ **在该子树所代表的二进制位以下**是不超过 $m$ **在该子树所代表的二进制位以下**的值的。

第 $0$ 维的转移同上，第 $1$ 维的只需稍作修改，详请见代码。

因为这是在 0-1 Trie 上 DP，所以时间复杂度为 $O(n\log V)$，其中 $V$ 为值域。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 2e5 + 5, p = 998244353;

ll a[maxn], f[maxn * 40][2], g[maxn * 40][2], h[maxn * 40][2], q[maxn * 40][2];

namespace trie{
int lc[maxn * 40], rc[maxn * 40], tot = 0;
ll val[maxn * 40], siz[maxn * 40];
void update(int &x, int d, ll v){
    if(!x) x = ++ tot;
    siz[x] ++;
    if(!d){
        val[x] = v;
        return;
    }
    if((v >> d - 1) & 1) update(rc[x], d - 1, v);
    else update(lc[x], d - 1, v);
}
void DP(int x, int d, ll m){
    if(!d){
        f[x][0] = f[x][1] = siz[x], g[x][0] = g[x][1] = h[x][0] = h[x][1] = 0, q[x][0] = q[x][1] = (siz[x] * (siz[x] + 1) / 2) % p;
        return;
    }
    if(lc[x]) DP(lc[x], d - 1, m);
    if(rc[x]) DP(rc[x], d - 1, m);
    ll pw = (1ll << (ll)d - 1) % p;
    f[x][0] = (f[lc[x]][0] + f[rc[x]][0]) * 2 % p;
    g[x][0] = (g[lc[x]][0] + (g[lc[x]][0] + pw * f[lc[x]][0] % p) + (g[rc[x]][0] + pw * f[rc[x]][0] % p) + g[rc[x]][0]) % p;
    q[x][0] = (q[lc[x]][0] + (q[lc[x]][0] + siz[rc[x]] * f[lc[x]][0] % p) + (q[rc[x]][0] + siz[lc[x]] * f[rc[x]][0] % p) + q[rc[x]][0]) % p;
    h[x][0] = (h[lc[x]][0] + (h[lc[x]][0] + pw * q[lc[x]][0] % p + siz[rc[x]] * g[lc[x]][0] % p + pw * siz[rc[x]] % p * f[lc[x]][0] % p) + (h[rc[x]][0] + pw * q[rc[x]][0] % p + siz[lc[x]] * g[rc[x]][0] % p + pw * siz[lc[x]] % p * f[rc[x]][0]) + h[rc[x]][0]) % p;
    if((m >> d - 1) & 1){
        f[x][1] = (f[lc[x]][0] + f[rc[x]][0]) % p;
        f[x][1] = (f[x][1] + f[lc[x]][1] + f[rc[x]][1]) % p;
        g[x][1] = (g[lc[x]][0] + (g[rc[x]][0] + pw * f[rc[x]][0] % p)) % p;
        g[x][1] = (g[x][1] + (g[lc[x]][1] + pw * f[lc[x]][1] % p) + g[rc[x]][1]) % p;
        q[x][1] = (q[lc[x]][0] + (q[rc[x]][0] + siz[lc[x]] * f[rc[x]][0] % p)) % p;
        q[x][1] = (q[x][1] + (q[lc[x]][1] + siz[rc[x]] * f[lc[x]][1] % p) + q[rc[x]][1]) % p;
        h[x][1] = (h[lc[x]][0] + (h[rc[x]][0] + pw * q[rc[x]][0] % p + siz[lc[x]] * g[rc[x]][0] % p + pw * siz[lc[x]] % p * f[rc[x]][0] % p)) % p;
        h[x][1] = (h[x][1] + (h[lc[x]][1] + pw * q[lc[x]][1] % p + siz[rc[x]] * g[lc[x]][1] % p + pw * siz[rc[x]] % p * f[lc[x]][1] % p) + h[rc[x]][1]) % p;
    }else{
        f[x][1] = (f[lc[x]][1] + f[rc[x]][1]) % p;
        g[x][1] = (g[lc[x]][1] + (g[rc[x]][1] + pw * f[rc[x]][1] % p)) % p;
        q[x][1] = (q[lc[x]][1] + (q[rc[x]][1] + siz[lc[x]] * f[rc[x]][1] % p)) % p;
        h[x][1] = (h[lc[x]][1] + (h[rc[x]][1] + pw * q[rc[x]][1] % p + siz[lc[x]] * g[rc[x]][1] % p + pw * siz[lc[x]] % p * f[rc[x]][1] % p)) % p;
    }
}
}

int main(){
    int n;
    ll m;
    scanf("%d %lld", &n, &m);
    int rt = 0;
    for(int i = 1; i <= n; i ++){
        scanf("%lld", &a[i]);
        trie::update(rt, 32, a[i]);
    }
    trie::DP(rt, 32, m);
    ll ans = (g[rt][1] * (2 * n + 1) % p + p - h[rt][1] * 2 % p) % p;
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：rhineofts (赞：4)

来一个不用 trie，但是需要大力分讨的做法。

这个 min 的限制是很难受的：因为如果两个数在某一位上分别是 $0$ 和 $1$，那个 $1$ 仍然可能有贡献。

先考虑一下性质 A： $a_i$ 全相等的做法。也即求 $n^2\sum_{j=0}^{m}x\oplus j$。这个东西就能拆位了，考虑第 $i$ 位什么时候有贡献，当 $x$ 的这一位和 $j$ 的这一位不同时，有 $2^j$ 的贡献。那么我们实际上把问题转化成了一个计数问题：求 $0\sim m$ 中钦定第 $i$ 位为 $0$（或是 $1$）的数的个数。这个东西是很好做的，但是需要一些分讨。可以看代码。

然后我们把 min 转化成 max。方法是先求出 $\sum_i\sum_j\sum_ka_i\oplus k+a_j\oplus k$。 这个东西 $i,j$ 无关，是很好做的。然后这个东西减去 max 就是 min（不转化好像也能做，但是我场上把题看错了，只好这样将错就错。）

重新观察一下式子：要求和的项是两个数异或上同一个数，这个东西有一个很好的性质：若 $x,y$ 的第 $i$ 位不同，那么它们异或上同一个数后仍不同。

这个性质是很强的！对于两个**不相等**的数，我们可以在它们最高的不相同的位处确定大小关系，进而很方便的算贡献：仍然是拆位，然后问题被转化成了上面的计数问题的加强版：限制的位置变成了两个，这个东西仍然可以大力分讨完成，当然也可以数位 DP。

最后，怎么快速进行这个过程呢？用类似基数排序的方法：我们要对一些最高的 $x$ 位都相同的数按第 $x$ 位是什么给它们分组。然后组和组间的贡献就可以用上面的方法算。组内贡献只需要递归到最后一层，这时组内所有数都相等，然后用性质 A 的方法去做。

这样这个题就做完了，复杂度为 $O(n\log V)$。

我的代码可能写的有些冗长，应该有更简单的写法。如果把那几个计数的函数换成数位 DP 应该能短不少。

```c++
int calc0(int m, int j) { // 计算 [0, m] 中第 j 位是 0 的数的个数，下同
    int tot = (1 << j) * (m >> j + 1);
    if (m & (1 << j)) {
        tot += 1 << j;
    } else {
        tot += (m & ((1 << j) - 1)) + 1;
    }
    return tot;
}

int calc1(int m, int j) {
    int tot = (1 << j) * (m >> j + 1);
    tot += max(0, 1 + (m & ((1 << j + 1) - 1)) - (1 << j));
    return tot;
}

int calc00(int m, int x, int y) { // 第 x 位是 0，第 y 位也是 0
    int cnt = 0;
    cnt += (m >> x + 1) * (1 << x - 1);
    if (m & (1 << x)) {
        cnt += 1 << (x - 1);
    } else cnt += calc0(m & ((1 << x) - 1), y);
    return cnt;
}

int calc01(int m, int x, int y) {
    int cnt = 0;
    cnt += (m >> x + 1) * (1 << x - 1);
    if (m & (1 << x)) {
        cnt += 1 << x - 1;
    } else {
        cnt += calc1(m & ((1 << x) - 1), y);
    }
    return cnt;
}

int calc10(int m, int x, int y) {
    int cnt = 0;
    cnt += (m >> x + 1) * (1 << x - 1);
    if (m & (1 << x)) {
        int t = m & ((1 << x) - 1);
        cnt += calc0(t, y);
    }
    return cnt;
}

int calc11(int m, int x, int y) {
    int cnt = 0;
    cnt += (m >> x + 1) * (1 << x - 1);
    if (m & (1 << x)) {
        int t = m & ((1 << x) - 1);
        cnt += calc1(t, y);
    }
    return cnt;
}

void solve() {
    int n, m; cin >> n >> m;
    vi a(n + 1);
    F (i, 1, n) cin >> a[i];

    i64 ans = 0;

    auto solve = [&](auto&& solve, int bit, int l, int r) -> void {
        if (bit == -1) {
            int x = a[l], cnt = 1LL * (r - l + 1) * (r - l + 1) % mod;
            DF (j, w - 1, 0) {
                if (x & (1 << j)) {
                    ans += 1LL * (1 << j) * calc0(m, j) % mod * cnt % mod;
                    ans %= mod;
                } else {
                    ans += 1LL * (1 << j) * calc1(m, j) % mod * cnt % mod;
                    ans %= mod;
                }   
            }
            return;
        }
        vi h; h.reserve(r - l + 1);
        int st = 0, ed = r - l;
        F (i, l, r) {
            if (!(a[i] & (1 << bit))) {
                h[ed--] = a[i];
            }  else h[st++] = a[i];
        }

        F (i, l, r) a[i] = h[i - l];
        // 这里 [l, l + st - 1] 这个区间中的数第 bit 位是 1，其余的数这一位是 0.
    
        if ((st and l + st <= r)) { // 这里有一个小剪枝，删了也不影响复杂度。
            {
                i64 res = 0;
                F (i, l, l + st - 1) {
                    DF (j, w - 1, bit + 1) {
                        if (a[i] & (1 << j)) {
                            res += 1LL * (1 << j) * calc00(m, j, bit) % mod;
                        } else {
                            res += 1LL * (1 << j) * calc10(m, j, bit) % mod;
                        }
                    }

                    res += 1LL * (1 << bit) * calc0(m, bit) % mod;

                    DF (j, bit - 1, 0) {
                        if (a[i] & (1 << j)) {
                            res += 1LL * (1 << j) * calc00(m, bit, j) % mod;
                        } else {
                            res += 1LL * (1 << j) * calc01(m, bit, j) % mod;
                        }
                    }
                    res %= mod;
                }
                ans += 2 * res * (r - (l + st) + 1) % mod; ans %= mod;
            }

            {
                i64 res = 0;

                F (i, l + st, r) {
                    DF (j, w - 1, bit + 1) {
                        if (a[i] & (1 << j)) {
                            res += 1LL * (1 << j) * calc01(m, j, bit) % mod;
                        } else {
                            res += 1LL * (1 << j) * calc11(m, j, bit) % mod;
                        }
                    }

                    res += 1LL * (1 << bit) * calc1(m, bit) % mod;

                    DF (j, bit - 1, 0) {
                        if (a[i] & (1 << j)) {
                            res += 1LL * (1 << j) * calc10(m, bit, j) % mod;
                        } else {
                            res += 1LL * (1 << j) * calc11(m, bit, j) % mod;
                        }
                    }

                    res %= mod;
                }
                ans += 2 * res * st % mod; ans %= mod;
            }
        }

        if (l <= l + st - 1) solve(solve, bit - 1, l, l + st - 1);
        if (l + st <= r) solve(solve, bit - 1, l + st, r);
    }; 

    solve(solve, w - 1, 1, n);
    //  进行完这个过程，a 是降序的。

    i64 ALL = 0;

    F (i, 1, n) { // 这里就是利用 a + b - max(a, b) = min(a, b)
        int x = a[i]; i64 res = 0;
        DF (j, w - 1, 0) {
            if (x & (1 << j)) {
                res += 1LL * (1 << j) * calc0(m, j);
                res %= mod;
            } else {
                res += 1LL * (1 << j) * calc1(m, j);
                res %= mod;
            }   
        }
        res = res * 2 * n % mod;
        ALL = (ALL + res) % mod;
    }

    ALL -= ans; ALL %= mod;
    if (ALL < 0) ALL += mod;

    cout << ALL << "\n";

}
```

---

## 作者：RainWetPeopleStart (赞：3)

赛时打到一半就去听 SegTree 讲题了，所以没切。

我们先思考一个能过 $n=3000$ 的做法。

下文记 $h(x)$ 表示 $x$ 最高位的 $1$ 在第几位，$x=0$ 时，我们令 $h(x)=30$（可以理解为 $+\infty$）。

考虑把 $\min$ 拆掉，不难发现，$\min$ 里面取 $a_i\oplus k$ 或 $a_j\oplus k$ 取决于 $k$ 的第 $h(a_i\oplus a_j)$ 位。

这时就可以逐位计算贡献了，考虑求出一个 $f_{i,j,0/1,0/1}$ 表示有多少个 $k$ 满足第 $i$ 位是 $0/1$，第 $j$ 位是 $0/1$，直接枚举从哪里开始顶不到 $m$ 即可 $O(\log^3V)$ 求解。

枚举 $i,j$，就得到了一个 $O(n^2\log V+\log^3 V)$ 的做法。

考虑优化，单独计算 $a_i=a_j$ 的部分，对于其他部分，发现 $a_i$ 对答案的贡献只和 $h(a_i\oplus a_j)$ 有关，只需要建 01trie，对每一个 $k$ 求出有多少个 $j$ 满足 $h(a_i\oplus a_j)=k$ 即可。

因为 $k$ 只有 $\log V$ 种，从大到小查就可以做到 $O(n\log V)$。 

总复杂度 $O(n\log V+\log^3 V)$。

代码：


```cpp
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define ll long long
#define sq(x) 1ll*(x)*(x)
#define ppc(x) __builtin_popcount(x)
using namespace std;
const int N=2e5+10,mod=998244353,inf=1e9+10;
int f[40][40][2][2];
int n,m;
int a[N];
int gp(int x,int p){
    return (x>>p)&1;
}
void Add(int &a,int b){
    a+=b;if(a>=mod) a-=mod;
}
struct trie{
    int trie[N<<5][2];
    int cnt[N<<5];
    int tot=1;
    void insert(int x){
        int now=1;cnt[now]++;
        for(int i=30;i>=0;i--){
            int op=gp(x,i);
            if(!trie[now][op]) trie[now][op]=++tot;
            now=trie[now][op];cnt[now]++;
        }
    }
}Trie;
int cnt[32];
void qry(int x){
    memset(cnt,0,sizeof(cnt));
    int now=1;
    for(int i=30;i>=0;i--){
        int op=gp(x,i);
        cnt[i]+=Trie.cnt[Trie.trie[now][op^1]];
        now=Trie.trie[now][op];
    }//cnt[30]+=Trie.cnt[now];
}
int calc(int x,int pos){
    int res=0;
    for(int k=0;k<=30;k++){
        Add(res,(1ll<<k)*f[pos][k][gp(x,pos)][gp(x,k)^1]%mod);
    }return res;
}int calc(int x){
    int res=0;
    for(int k=0;k<=30;k++){
        Add(res,(1ll<<k)*f[30][k][1][gp(x,k)^1]%mod);
        Add(res,(1ll<<k)*f[30][k][0][gp(x,k)^1]%mod);
    }return res;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=0;i<=30;i++){
        for(int j=0;j<=30;j++){
            for(int o1=0;o1<=1;o1++){
                for(int o2=0;o2<=1;o2++){
                    if(i==j&&o1!=o2) continue;
                    int cnt=(i==j)?1:2;bool fl=1;
                    for(int k=30;k>=0;k--){
                        if(k==i||k==j){
                            cnt--;
                            if(k==i&&o1!=gp(m,k)){
                                fl=0;
                                if(!o1) Add(f[i][j][o1][o2],(1<<(k-cnt)));
                                break;
                            }
                            if(k==j&&o2!=gp(m,k)){
                                fl=0;
                                if(!o2) Add(f[i][j][o1][o2],(1<<(k-cnt)));
                                break;
                            }
                            continue;
                        }if(gp(m,k)){
                            //cout<<k<<' '<<cnt<<' ';
                            Add(f[i][j][o1][o2],(1<<(k-cnt)));
                        }
                    }
                    if(fl) if(((o1*(1<<i))|(o2*(1<<j)))<=m) Add(f[i][j][o1][o2],1);
                    //cout<<i<<' '<<j<<' '<<o1<<' '<<o2<<' '<<f[i][j][o1][o2]<<endl;
                }
            }
        }
    }for(int i=1;i<=n;i++) Trie.insert(a[i]);
    map<int,int> q;for(int i=1;i<=n;i++) q[a[i]]++;
    int ans=0;
    for(int i=1;i<=n;i++){
        qry(a[i]);
        for(int j=0;j<=30;j++){
            Add(ans,2ll*cnt[j]*calc(a[i],j)%mod);
        }//Add(ans,mod-calc(a[i],30));
    }for(auto ed:q){
        Add(ans,1ll*sq(ed.se)%mod*calc(ed.fi)%mod);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：sbno333 (赞：1)

原式不好处理，考虑最一点变化。

$$\sum_{i=1}^n \sum_{j=1}^n \sum_{k=0}^m \min(a_i \oplus k, a_j \oplus k)=2\sum_{i=1}^n \sum_{j=i+1}^n \sum_{k=0}^m \min(a_i \oplus k, a_j \oplus k)+\sum_{i=1}^n\sum_{j=0}^m (a_i\oplus j)$$

我们先看后面的式子，我们避不开计算它，我们不妨设 $f(n,m)=\sum_{i=0}^m (n\oplus i)$。

只能拆位！

对于每一位分别考虑，这一位为 $1$ 的数量要考虑 $0\sim m$ 中 $0$ 的数量和 $1$ 的数量，看 $n$ 这一位是 $0$ 还是 $1$，然后选一个计算答案，这并不困难。

后面的可以完成了，问题是前面的。

由于最小值的存在，先排序。

然后我们考虑 $O(n^2\log V)$ 的算法，即我们要解决 $g(x,y,m)=\sum_{i=0}^m \min(x\oplus i,y\oplus i)$。

拆位！

考虑对于每一位，二者可能相同，可能不同。

相同不影响选择哪一个。

不相同才是重点！

二者怎么异或同一个值这个不同和相同都不变。

考虑对于不相同的最高位，显然二者存在 $0$，哪个这一位是 $0$ 就选择哪个。

于是这一位就惨了，永远为 $0$。

具体选择哪一个其实由二者异或的数这一位的值决定。

容易看出会分很多段，仍然不好处理。

我们再仔细考虑，二者异或的值从 $0$ 到 $m$ 增加时，这一位发生变化，此时 $\min(x\oplus i,y\oplus i)$ 这一位不变，相同位不需要考虑选择哪个，不同位此时其实也不改变，对象变了，但是 $i$ 这些位也变了，相当于没变，我们可以当做对象没变，接下来相当于低位变小，知道临近最高不同位在此临近改变，我们可以将这一段翻转一下，和对象不变，一直增加没区别，之后又一次变成自己变化。

但是最后一段走不完，而且是对象变化阶段，还是需要当做对象变化，这样就分成了两段，每一段调用 $f$ 函数就可以让复杂度只有 $O(\log V)$ 了。

我们可以额定小的那个为自己，方便处理。

然后我们继续尝试改良算法，我们两段分别考虑，先考虑第一段，我们从大到小枚举，我们对于一个数，额定它为自己，然后枚举每一位表示最高不同位，维护前面有多少满足条件（如果用哈希表，常数巨大，略找性质可知这是一段连续区间，降低常数），然后第一段只和自己有关，直接乘就行了。

然后第二段，从小到大枚举，枚举的是对象，与上面同理，不再赘述。

这个算法常数巨大~~虽然不知道为什么~~，卡了两个半小时才过。

时间复杂度 $O(n\log^2 V)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353ll
inline int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') { 
    if (ch == '-') w = -1;       
    ch = getchar();               
  }
  while (ch >= '0' && ch <= '9') { 
    x = x * 10 + (ch - '0'); 
    ch = getchar();
  }
  return x * w;
}
int a[200009];
int N;
int dp[200009][39];
int n,m;
inline int dd(int n,int m,int i){
	if(i==114514ll){
		return 0ll;
	}
	if(n&(1ll<<i)){
		return (m+1-((m+1)/(1ll<<(i+1))*(1ll<<i)+max((m+1)%(1ll<<(i+1))-(1ll<<i),0ll)))*(1ll<<i);
	}
	return ((m+1)/(1ll<<(i+1))*(1ll<<i)+max((m+1)%(1ll<<(i+1))-(1ll<<i),0ll))*(1ll<<i);
}
inline int c(int n,int mm,int x){
	int zz;
	if(mm!=31ll)
	zz=((m>>(mm+1))<<(mm+1))+(1ll<<mm)-1;
	else
	zz=m;
	return (dp[n][mm]-dd(a[n],zz,x))%mod;
}
int ans;
int mp[39];
inline void _main(){
	for(int i=n;i>=1;i--){
		for(int j=0;j<=N+1;j++){
			if((a[mp[j]]>>j)!=(a[i]>>j)||!mp[j]){
				mp[j]=i;
			}
		}
		for(int j=0;j<=N;j++){
			if(a[i]&(1ll<<j)){
				continue;
			}
			int gs;
			gs=(mp[j+1]-i)-(mp[j]-i);
			gs%=mod;
			if(m&(1ll<<j)){
				ans+=gs*c(i,j,j);
			}else{
				ans+=gs*c(i,31ll,j);
			}
			ans%=mod;
		}
		ans+=(mp[0]-i)*c(i,31ll,114514ll);
		ans%=mod;
		
	}
	for(int j=0;j<=N+1;j++){
		mp[j]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<=N+1;j++){
			if((a[mp[j]]>>j)!=(a[i]>>j)||!mp[j]){
				mp[j]=i;
			}
		}
		for(int j=0;j<=N;j++){
			if((a[i]&(1ll<<j))==0){
				continue;
			}
			int gs;
			gs=(i-mp[j+1])-(i-mp[j]);
			gs%=mod;
			if(m&(1ll<<j)){
				ans+=((c(i,31ll,j)-c(i,j,j)+mod))%mod*gs%mod;
				ans%=mod;
			}
		}
	}
}
signed main(){
	std::ios::sync_with_stdio(0);
	cin.tie(0);
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+1+n);
	N=30;
	for(int i=1;i<=n;i++){
		for(int j=0ll;j<=30ll;j++){
			int mm;
			mm=((m>>(j+1ll))<<(j+1ll))+(1ll<<j)-1ll;
			for(int c=0ll;c<=30ll;c++){
				dp[i][j]+=dd(a[i],mm,c);
			}
		}
		for(int c=0;c<=30;c++){
			dp[i][31]+=dd(a[i],m,c);
		}
	}
	_main();
	ans*=2;
	ans%=mod;
	for(int i=1;i<=n;i++){
		ans+=c(i,31ll,114514ll);
		ans%=mod;
	}
	cout<<ans;
	return 0;
}
```

---

