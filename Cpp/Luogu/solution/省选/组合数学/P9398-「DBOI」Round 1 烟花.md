# 「DBOI」Round 1 烟花

## 题目背景

回忆本身就是惩罚，惩罚那些不愿往前走的人，将他们困在那条小巷子里，怎么也走不出去。

每一年都有烟花，唯独那一年的烟花最好看。

“我要对烟花许愿，许我们永远在一起。”

“就算不许愿，我们也会永远在一起的。”

再后来，死了的人被葬在了那座山上，活着的人被记忆困在了那条巷中。今天的我们听到这个故事，只是想再放一次故事里的烟花，放给那些再没能陪身旁的人看到一次烟花的人。

## 题目描述

烟花在夜空中绽放连成一片，我们把这些连成一片的烟花看成一棵含有 $n$ 个点的有根树，根为最早点燃的烟花 $1$。

烟花有红蓝两种颜色，为了方便，我们对这棵树黑白染色。最初有 $p$ 个限制，一条限制形如 $(x_i,y_i)$，表示树中编号为 $x_i$ 的点的子树中黑点只能**恰好**有 $y_i$ 个。当年，他们认为满足其**子树内所有有限制点的限制**的子树是**均好的子树**。显然，要想使一个子树成为均好的子树，可能有**多种染色方法**。

你需要回答以下两种询问：

- `Z k c`，表示给点 $k$ 以均等概率在 $[0,c]$ 中选择一个数 $f$，然后给点 $k$ 直接加上 $f$ 个没有限制的儿子，其它儿子状态不变。问点 $k$ 为根的子树成为**均好的子树**的期望染色方法数量。
- `H k`，表示如果去掉 $k$ 的所有有限制儿子的限制，询问 $k$ 为根的子树成为**均好的子树**的染色方法数量。

我们并没有必要点燃更多的烟花，因此所有的询问都是相互独立的，没有询问会真的影响原树。

我们深知可能复现不了当时完整的情况，历史太过斑驳，可能的烟花组合成千上万，因此你只需要得到答案对 $998244353$ 这个大质数取模的值。

## 说明/提示

### 样例解释

![](https://cdn.luogu.com.cn/upload/image_hosting/523p3yhk.png)

如图为样例 #1 的烟花，构成一个有 $14$ 个点，其中 $5$ 个限制点的树。与题目中不同的是，我们用红色烟花表示限制点，蓝色烟花表示无限制点。红色烟花右上角的浅蓝色数字表示其限制的黑点数量。

初始情况下每一个点为根子树的合法烟花燃放方法数量如下（从左至右第 $i$ 项表示以第 $i$ 个点为根的子树的答案）：

$$
[320,10,4,4,2,8,1,2,2,1,2,2,1,1]
$$

下面我们给出询问的答案与部分解释：

- `Z 2 5`，为 $2$ 号点添加 $i$ 个儿子后的 $2$ 号点子树内合法烟花燃放数量表示为此数列的第 $i+1$ 项：$[10,20,35,56,84,120]$。总期望即为 $\frac{325}{6}$。对 $998244353$ 取模之后得到 $166374113$。
- `H 14`，由于 $14$ 号点没有儿子，因此答案仍然为 $1$。
- `Z 7 3`，共有 $10$ 种可能的合法烟花燃放方案，总期望即为 $\frac{5}{2}$，对 $998244353$ 取模之后得到 $499122179$。
- `Z 7 1` 的答案为 $499122178$。
- `H 6` 的答案为 $16$。
- `Z 1 9` 的答案为 $32736$。
- `H 1`，去除 $1$ 的所有有限制儿子（仅有节点 $2$）的限制后有 $1024$ 种可能的合法烟花燃放方案。
- `H 8` 的答案为 $8$。
- `H 12` 没有儿子，因此答案不变，此询问的答案仍然为 $2$。
- `Z 10 1` 的答案为 $1$。

最终，所有询问的 $i\times ans_i$ 的异或和即为 $665340330$。

### 数据范围

**请注意常数因子对程序效率的影响。**

**本题采用捆绑测试与子任务依赖。**

下面定义 $S=3\times 10^5$。

| $\rm Subtask$ | $n$ | $q$ | $y_i$ | $c$ | 特殊性质 | 得分 | 子任务依赖 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $\leqslant 10$ | $\leqslant 10$ | $\leqslant 5$ | $\leqslant 5$ | 无 | $10$ | 无 |
| $2$ | $\leqslant 200$  | $\leqslant 200$ | $\leqslant 200$ | $\leqslant 200$ | 无 | $15$ | $1$ |
| $3$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $\leqslant 10$ | 无 | $20$ | $1,2$ |
| $4$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $A$ | $15$ | 无 |
| $5$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $B$ | $20$ | 无 |
| $6$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | $\leqslant S$ | 无 | $20$ | $1,2,3,4,5$ |

特殊性质 $A$：$p=0$。

特殊性质 $B$：满足不存在 `Z` 询问。

对于 $100\%$ 的数据，存在输入的所有数均为 $\leqslant S$ 的整数。特别地，存在 $0\leqslant p\leqslant n$，输入的任何树的节点编号 $x$ 都满足 $1\leqslant x \leqslant n$。保证输入的询问字符都为 `Z` 或 `H`，输入的一定是一棵树。保证对于所有限制存在 $x_i\neq x_j(i\neq j)$。


------------

冬天的最后一场雪如约而至，很快又要迎来一个新的春天。万物都在等待复苏，可峰城里的一个小巷子，再也不复往日繁荣。

八十多年过去，我们早已找不到当初的巷子，只留下这样一个故事。

感谢你放的烟花。

## 样例 #1

### 输入

```
14 5
1 2
1 3
4 1
5 2
2 6
3 7
3 8
9 4
12 6
11 6
6 10
8 13
14 8
2 3
10 0
7 1
13 1
14 0
10
Z 2 5
H 14
Z 7 3
Z 7 1
H 6
Z 1 9
H 1
H 8
H 12
Z 10 1```

### 输出

```
665340330```

# 题解

## 作者：Shunpower (赞：9)

$\text{upd:}$ 修改了 std 里的一些过于抽象的码风和部分题解表述。

出题人题解。

首先 $\rm Subtask\ 1$ 给了指数级暴搜所有方案然后一一检验的。

实际上真正有启发性的是 $\rm Subtask\ 3,4$，下面我们会提到为什么设置每一个子任务。

下文统一定义 $s_i$ 表示 $i$ 所在子树的大小，${i\choose j}=0$ 如果 $j>i,i<0,j>0$ 三者任占一个。$x_i,y_i$ 的含义同题面所示。

不妨先在最开始算一遍答案。先考虑根是限制点的子树的答案。

下文定义，从某个点向其子树内移动，不用经过别的限制点就能到达的限制点为“顶层限制点”。如果其本身是限制点，不算“顶层限制点”。没有顶层限制点时有 $mul_i=1,cnt_i=0$（这两个变量的具体含义见后文）。

假设这个点是 $i$，首先你需要得到该点为根的子树内所有顶层限制点的答案乘积，显然可以维护，不妨记为 $mul_i$。然后是该点子树内所有顶层限制点的限制 $y$ 之和，显然也很好维护，不妨记为 $cnt_i$。最后是该点子树内所有顶层限制点的子树大小 $siz$ 之和，不妨记为 $ssiz_i$。显然这个点的答案为 $mul_i\times {{s_i-ssiz_i}\choose{y_i-cnt_i}}$。值得注意的是右边的两个减法如果有一个是负值答案都为 $0$。

为了方便，我们下面把点 $i$ 的初始答案称作 $ans_i$。

以上讨论的都是这个根为限制点的情况。对于根为非限制点的，答案即为 $mul_i\times 2^{s_i-ssiz_i}$。而显然，总是存在 $s_i>ssiz_i$。

上文两种情况在没有顶层限制点（整个子树内除了根都没有限制）时仍然正确。

以上的部分主要的就是如何快速处理答案。会这个可以通过 $\rm Subtask\ 1,2$。

下面假设你掌握了处理答案的 $O(siz\log M)$ 以内的做法，其中 $siz$ 是树大小。

现在考虑询问二，容易发现可以在一开始就给每个点都预处理出来询问二的答案。

注意到当点 $i$ 不再是限制点的时候，对于它的父亲，$i$ 的顶层限制点成为 $i$ 父亲的顶层限制点。由于在第一次预处理答案的时候我们对于每一个限制点 $x$ 在算完 $x$ 的答案后要让 $mul_x\leftarrow ans_x,cnt_x\leftarrow y_x,ssiz_i\leftarrow siz_i$ 来方便在树上累积，因此我们考虑存一个 $pmul,pcnt,pssiz$ 表示在改变之前的 $mul,cnt,ssiz$，存留下该点的顶层限制点的各项数据。然后对于预处理询问二答案时，对于限制点儿子我们用 $pmul,pcnt,pssiz$ 去累积、累加（而不是 $mul,cnt,ssiz$），剩余的部分就和预处理普通答案一样。

还可以注意到记忆化询问二的复杂度也是正确的（每个点只会被访问一次）。但出题人十分邪恶，因为询问二的答案可能是 $0$，所以如果记忆化时判断目前答案数组里面是 $0$ 就重算答案会 TLE 在 #21。

会这个可以通过 $\rm Subtask\ 5$。

现在考虑询问一。容易发现我们可以把概率提取出来，也就是 $\frac{1}{c+1}$。然后仍然对于非限制点和限制点分类。

$1'$ 对于非限制点

容易发现其实每次多加一个儿子，就是在给 $k$ 的染色方法数量乘以 $2$，所以甩掉概率后的权值和即为 $ans_k+2^1ans_k+2^2ans_k+2^3ans_k+\cdots+2^{c}ans_k$，直接提取公因数然后做一个等比数列求和，然后乘上概率即可。

做到这里可以通过 $\rm Subtask\ 4$，甚至不需要完全做到这里，处理答案你只需要会非限制点内无限制点的 case 就可以。

$2'$ 对于限制点

容易发现如果一开始 $pmul_k=0$ 或者 $y_k<pcnt_k$ 无论加多少儿子都还会是 $0$。

对于其他情况，可以发现实际上权值和当中的 $pmul_k$ 并不会变，每次变大的只有组合数里面的 $s_k$。为了方便，下面存在 $d_1=y_k-pcnt_k,d_2=s_k-pssiz_k$，所以甩掉概率后的权值和为 $pmul_k\times({{d_2+0}\choose{d_1}}+{C_{d_2+1}\choose{d_1}}+\cdots+{{d_2+c}\choose{d_1}})$。

意思就是说我们要算下面这个式子的值：

$\sum\limits_{i=l}^r {{d_2+i}\choose{d_1}}$，其中 $l$ 我们为了使得组合数不为 $0$，为 $\max (y_k-pcnt_k-s_k+pssiz_k,0)$，$r=c$，特判 $r<l$ 为 $0$。

然而这个式子如果你不会快速算，你可以暴算去通过 $\rm Subtask\ 3$。可以发现，推到这里其实你可以通过 $\rm Subtask\ 1\sim5$，得分可以达到 $80$。下面介绍做这个式子的正解。

根据上指标求和公式有：

$$
\sum\limits_{i=0}^n {{i}\choose{m}}={{n+1}\choose{m+1}}
$$

于是我们可以把这个和式改成 ${{d_2+r+1}\choose{d_1+1}}-{{d_2+l+1-1}\choose{d_1+1}}$，然后就可以在 $O(\log M)$ 以内的时间复杂度算出来了（$M$ 为模数）。注意右边的组合数可能出现组合数下面大于上面的情况，特判为 $0$。

把这个东西乘上概率和 $pmul_k$ 即可。

上指标求和公式不知道也可以推出，下面是 @StayAlone 的推导：

首先我们推一个 $\sum\limits_{i=0}^n {i\choose m}$。然后利用前缀和相减。

首先你知道 ${{i}\choose{m}}=\frac{i!}{m!(i-m)!}$，在这里你发现 $m$ 是定值（$d_1$），所以先提取 $\frac{1}{m!}$ 到求和外面，然后考虑 $\frac{i!}{(i-m)!}$。然后当你把除法打开变成乘法的时候，你可以发现这是一个极其经典的整数裂项，它的答案为 $\frac{1}{m+1}\prod_{g=n+1-m}^{n+1}g$。

再乘上一个 $\frac{1}{m!}$ 可以得到：

$$
\sum\limits_{0\leqslant i\leqslant n} {i\choose m}=\frac{1}{(m+1)!}\prod_{g=n+1-m}^{n+1}g=\frac{1}{(m+1)!}\times\frac{(n+1)!}{(n+1-m-1)!}={{n+1}\choose{m+1}}
$$

本质上还是上指标求和，但是可以现场推。后面的方法就和前面一样了。

通过线性预处理阶乘逆元和 $2$ 的次幂，最开始计算答案的时间复杂度为 $O(n)$。再加上线性预处理逆元，询问一复杂度可以做到 $O(1)$。询问二复杂度为 $O(1)$。

最终 std 的复杂度为 $O(n+q)$。数据应该足以把绝大多数错误复杂度卡掉（以及一些常数过分大的 $\log$，简单优化就能过了），正确性写错的应该也基本卡了。不过错法太多，具体出题人也不清楚。/kel/kel/kel

------------

下面是 std。


```cpp
//Author:Leftist / Shunpower
//Spade Su & Griffin BAO
//May the force be with you and me.
#include <bits/stdc++.h>
#define ET return 0
#define fi first
#define se second
#define mp make_pair
#define pb emplace_back
#define ll long long
#define ull unsigned long long
#define inf INT_MAX
#define uinf INT_MIN
#define pii pair<int,int>
#define pll pair<ll,ll>
#define debug puts("--------Chery AK IOI--------");
#define Yes cout<<"Yes"<<endl;
#define No cout<<"No"<<endl;
#define pt puts("")
#define fr1(i,a,b) for(int i=a;i<=b;i++)
#define fr2(i,a,b) for(int i=a;i>=b;i--)
#define fv(i,p) for(int i=0;i<p.size();i++)
#define ld long double
#define il inline
#define ptc putchar
using namespace std;
const int N=6e5+100;
const ll P=998244353;
namespace Cream_H{
    int lowbit(int x){
        return x&-x;
    }
    template <typename T>
    inline void read(T &x){
       T s=0,w=1;
       char ch=getchar();
       while(ch<'0'||ch>'9'){
            if(ch=='-'){
                w=-1;
            }
            ch=getchar();
        }
        while(ch>='0'&&ch<='9'){
            s=s*10+ch-'0';
            ch=getchar();
        }
        x=s*w;
    }
    template <typename T>
    inline void write(T x){
        if(x<0){
            putchar('-');
            x=-x;
        }
        if(x>9){
            write(x/10);
        }
        putchar(x%10+'0');
    }
}
using namespace Cream_H;
int n,m;
int u,v;
vector <int> p[N];
int x,y;
int lim[N];
bool hlim[N];
ll mul[N],cnt[N],ans[N],siz[N],fac[N<<1];
ll pmul[N],pcnt[N],ans2[N],ssiz[N],pssiz[N];
ll pow2[N],invf[N],dpinv[N];
int q;
char opt;
int k,c;
ll allans;
il ll qpow(ll b,ll p,ll k){
    if(!p){
        return 1;
    }
    ll d=qpow(b,p>>1,k);
    if(p&1){
        return d*d%k*b%k;
    }
    else{
        return d*d%k;
    }
}
il void init(int n){
    fac[0]=1;
    pow2[0]=1;
    dpinv[1]=1;
    fr1(i,1,n){
        pow2[i]=pow2[i-1]*2ll;
        pow2[i]%=P;
        fac[i]=fac[i-1]*(ll)i;
        fac[i]%=P;
        if(i!=1){
        	dpinv[i]=((1ll*(-P/i)*dpinv[P%i])%P+P)%P;
		}
    }
    invf[n]=qpow(fac[n],P-2,P);
    fr2(i,n-1,0){
        invf[i]=1ll*invf[i+1]*(i+1)%P;
    }
}
il ll C(ll n,ll m){//m choose n
    if(n<0||m<0||n>m){
        return 0;
    }
    return fac[m]*invf[n]%P*invf[m-n]%P;
}
il void dfs(int x,int fa){
    mul[x]=1;
    siz[x]=1;
    fv(i,p[x]){
        if(p[x][i]==fa){
            continue;
        }
        dfs(p[x][i],x);
        mul[x]*=mul[p[x][i]];
        mul[x]%=P;
        cnt[x]+=cnt[p[x][i]];
        siz[x]+=siz[p[x][i]];
        ssiz[x]+=ssiz[p[x][i]];
    }
    if(hlim[x]){
        ans[x]=mul[x]*C(lim[x]-cnt[x],siz[x]-ssiz[x])%P;
        pmul[x]=mul[x];
        pcnt[x]=cnt[x];
        pssiz[x]=ssiz[x];
        mul[x]=ans[x];
        cnt[x]=lim[x];
        ssiz[x]=siz[x];
    }
    else{
        ans[x]=mul[x]*pow2[siz[x]-ssiz[x]]%P;
        pmul[x]=mul[x];
        pcnt[x]=cnt[x];
        pssiz[x]=ssiz[x];
    }
}
il void dfs2(int x,int fa){
    ll muld=1,cntd=0,sizd=0;
    fv(i,p[x]){
        if(p[x][i]==fa){
            continue;
        }
        dfs2(p[x][i],x);
        muld*=pmul[p[x][i]];
        muld%=P;
        cntd+=pcnt[p[x][i]];
        sizd+=pssiz[p[x][i]];
    }
    if(hlim[x]){
        ans2[x]=muld*C(lim[x]-cntd,siz[x]-sizd)%P;
    }
    else{
        ans2[x]=muld*pow2[siz[x]-sizd]%P;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>n>>m;
    init(600050);
    fr1(i,1,n-1){
        cin>>u>>v;
        p[u].pb(v);
        p[v].pb(u);
    }
    fr1(i,1,m){
        cin>>x>>y;
        lim[x]=y;
        hlim[x]=1;
    }
    dfs(1,0);
    dfs2(1,0);
    cin>>q;
    fr1(i,1,q){
        ll qans=0;
        cin>>opt>>k;
        if(opt=='Z'){
        	cin>>c;
            ll div=dpinv[c+1];
            if(!hlim[k]){
                ll muls=pow2[c+1]-1;
                qans=muls*ans[k]%P*div%P;
            }
            else{
                if(!pmul[k]||lim[k]-pcnt[k]<0){
                    continue;
                }
                ll l=max(lim[k]-pcnt[k]-siz[k]+pssiz[k],0ll);
                ll r=c;
                if(r<l){
                    continue;
                }
                ll d1=lim[k]-pcnt[k];
                ll d2=siz[k]-pssiz[k];
				qans=(((C(d1+1,d2+r+1)-C(d1+1,d2+l))%P+P)%P)*pmul[k]%P*div%P;
            }
        }
        else{
            qans=ans2[k];
        }
        allans^=1ll*i*qans;
    }
    cout<<allans<<endl;
    ET;
}
//ETERNAL LOVE FOR Zhang Junhao, Mu Zhicheng and Zuo Hang.
//ALL FOR Zhang Junhao.
```


---

