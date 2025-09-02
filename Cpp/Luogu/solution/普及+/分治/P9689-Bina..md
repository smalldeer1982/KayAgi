# Bina.

## 题目描述

小 J 家门前有两棵树，一棵是二叉树，一棵是三叉树。

你被小 J 叫来修剪他的二叉树，使得他的二叉树的“美丽值”最大，所谓一棵树的美丽值 $=$ 这棵树的点的编号之和 $\div$ 这棵树的深度（结果向下取整）。

这棵二叉树有一个构建参数 $n$，构建方式如下：

```cpp
void build(int s,int t,int p){
  if(s==t) return ;
  build(s,(s+t)/2,2*p);
  build((s+t)/2+1,t,2*p+1);
  add_edge(p,2*p),add_edge(p,2*p+1);
}

int main(){
  build(1,n,1);
  return 0;
}
```

其中 `build(s,t,p)` 函数参数中的 $p$ 是当前点的编号，`add_edge(x,y)` 函数是指将编号为 $x$ 的点向编号为 $y$ 的点连接一条有向边。

容易发现这棵树的根节点是 $1$，并且我们规定节点的深度为节点到根节点路径上经过的点的个数（包括自己和根节点），这棵树的深度即为所有节点深度的最大值。

对于 $n=3$ 的情况，最后构建出来的结果如下，这棵树的深度为 $3$，你需要选择一个深度 $k$ 把深度大于 $k$ 的点都剪掉，但是 $k$ 必须**大于等于** $1$ 且**小于等于**这棵树的深度。

![](https://cdn.luogu.com.cn/upload/image_hosting/ueggbyn8.png)

小 J 还给了你一个要求，你剪去的节点个数一定得大于等于 $m$ 他才会高兴，你需要保证让他高兴的同时树的“美丽值”最大。

现在小 J 给了你构建树的参数 $n$ 和至少剪的节点个数 $m$，要你求出来他的树在你修剪后最大的美丽值是多少，如果无论如何你也不可能让小 J 高兴，输出 $-1$。

## 说明/提示

#### 【样例解释 #1】

对于第一组样例，$n$ 都等于 $3$，构建出来的树同题面所示。

如果我们选择把深度大于 $1$ 的节点全部剪掉，那么我们剪掉了 $2,3,4,5$ 共 $4$ 个节点，美丽值为 $1$。

如果我们选择把深度大于 $2$ 的节点全部剪掉，那么我们剪掉了 $4,5$ 共 $2$ 个节点，美丽值为 $\lfloor \dfrac{1+2+3}{2}\rfloor = 3$。

如果我们选择把深度大于 $3$ 的节点全部剪掉，那么我们没有剪掉任何节点，美丽值为 $\lfloor \dfrac{1+2+3+4+5}{3}\rfloor = 5$。

所以对于 $m=0$ 的情况，答案为 $5$；对于 $1 \le m \le 2$ 的情况，答案为 $3$；对于 $3 \le m \le 4$ 的情况，答案为 $1$；其它情况，无解输出 $-1$。

#### 【数据范围】

对于所有测试数据，满足 $1 \le T \le 10^5$，$1 \le n \le 10^9$，$0 \le m \le 2 \times 10^9$。

**本题开启捆绑测试，所有数据范围均相同的测试点捆绑为一个 $\text{Subtask}$。**

各测试点的附加限制如下表所示。

| 测试点 | $n \le$ | $m \le$ | $T \le$ | 特殊限制 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1 \sim 2$ | $10^3$ | $10^5$ | $10^3$ | 无 |
| $3 \sim 4$ | $10^6$ | $2 \times 10^6$ | $10^5$ | 无 |
| $5$ | $10^9$ | $1$ | $10^5$ | 无 |
| $6$ | $10^9$ | $2$ | $10^5$ | 无 |
| $7 \sim 8$ | $10^9$ | $3$ | $10^5$ | 无 |
| $9 \sim 10$ | $10^9$ | $2 \times 10^9$ | $10^5$ | $m \ge 1$ |
| $11 \sim 12$ | $10^9$ | $10^3$ | $10^5$ | 无 |
| $13 \sim 16$ | $10^9$ | $2 \times 10^9$ | $10$ | 无 |
| $17 \sim 20$ | $10^9$ | $2 \times 10^9$ | $10^5$ | 所有 $n$ 均相同 |
| $21 \sim 25$ | $10^9$ | $2 \times 10^9$ | $10^5$ | 无 |

## 样例 #1

### 输入

```
6
3 0
3 1
3 2
3 3
3 4
3 5```

### 输出

```
5
3
3
1
1
-1```

## 样例 #2

### 输入

```
10
5 5
10 0
999 155
135 92
1000232 234255
10293845 1239485
123948 1239454
12394 2131094
1000000000 98765432
1000000000 999999999```

### 输出

```
3
40
52377
1161
27487764480
5864061665280
-1
-1
19215358392218419
4969489234738635```

# 题解

## 作者：离散小波变换° (赞：13)

出题人卡常数是什么心态。

## 题解

可以发现，给出的 $\verb!build!$ 函数本质就是建立一棵以 $p$ 为根节点，对应区间 $[l, r]$ 的线段树。这个节点的左儿子是 $2p$，右儿子是 $2p+1$。

套路地，应用大小为 $n$ 的线段树区间长度本质不同的节点个数只有 $\mathcal O(\log n)$ 种的结论。可以使用归纳法证明线段树每一层，区间长度最多只有 $\{2k+1,2k\}$ 两种（也可能只有一种，这个时候认为另外一种长度的数量为 $0$ 即可）：

- 第一层区间长度只有 $n$ 一种，符合归纳条件；
- 假设第 $i$ 层区间长度最多只有 $\{2k+1,2k\}$ 两种，可以发现下一层可能的区间长度只有 $\{k+1,k\}$ 两种。

由于线段树只有 $\mathcal O(\log n)$ 层，所以区间长度本质不同的节点个数只有 $\mathcal O(\log n)$ 个。

现在我们要计算长度为 $i$、根节点编号为 $x$ 的子树，限定它最多生长 $y$ 层，它里面所有结点的编号之和。可以证明对于固定的 $i$ 和 $y$ 而言，答案是一个关于 $x$ 的一次函数。同样是应用归纳证明：

- 对于叶子节点，答案显然是 $1\cdot x+0$；
- 从下往上看每个非叶子节点，它一定会有两个儿子 $2x$ 和 $2x+1$。应用归纳假设可以知道这两个子树里所有结点的编号之和分别可以表示成 $u_1\cdot(2x)+v_1$ 和 $u_2\cdot (2x+1)+v_2$ 的形式，其中 $u_1,v_1,u_2,v_2$ 是和 $x$ 无关的常数。于是对于 $x$ 来说，它子树内所有结点的编号之和是 $(2u_1+2u_2+1)\cdot x+(v_1+v_2+u_2)$，同样是关于 $x$ 的一次函数。

我们对于每个 $x,y$ 计算一下系数，由于本质不同的 $i$ 只有 $\mathcal O(\log n)$ 个，可能的 $y$ 也只有 $\mathcal O(\log n)$ 个，所以直接暴力做单次复杂度就是 $\mathcal O(\log ^2 n)$。不过需要注意到尽管区间长度种类不多，但是值比较大，可能需要用 $\mathrm{map}$ 或者哈希表来存，会有较大的常数。实现不太好的话就会被卡爆。

## 暴力做法

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long i64;

const int MAXN = (1 << 19) + 3;
const int MAXM =  19 + 3;
const int MAXK =  32 + 3;

int o = (1 << 19), g = 20;
tuple<int, i64, i64> H[MAXN][MAXM];

unordered_map <int, tuple<int, i64, i64>> M[MAXK];
void solve(int n, int d){
    if(n <= o && d <= g)
        return;
    if(M[d].count(n))
        return;
    if(n == 1 || d == 1){
        M[d][n] = {1, 1, 0};
        return;
    }
    const int n1 = (n + 1) / 2, n2 = n - n1;
    solve(n1, d - 1);
    solve(n2, d - 1);
    const auto &[c1, u1, v1] = n1 <= o ? H[n1][min(g, d - 1)] : M[d - 1][n1];
    const auto &[c2, u2, v2] = n2 <= o ? H[n2][min(g, d - 1)] : M[d - 1][n2];
    M[d][n] = {
        c1 + c2 + 1, 1 + 2 * u1 + 2 * u2, v1 + u2 + v2
    };
}

int main(){
    int T;
    cin >> T;
    for(int i = 1;i <= o;++ i){
        for(int j = 1;j <= g;++ j){
            if(i == 1 || j == 1){
                H[i][j] = {1, 1, 0};
            } else {
                const int n1 = (i + 1) / 2, n2 = i - n1;
                const auto &[c1, u1, v1] = H[n1][j - 1];
                const auto &[c2, u2, v2] = H[n2][j - 1];
                H[i][j] = {
                    c1 + c2 + 1, 1 + 2 * u1 + 2 * u2, v1 + u2 + v2
                };
            }
        }
    }
    for(int _ = 1;_ <= T;++ _){
        int n, m, h = 32;
        for(int i = 1;i <= h;++ i)
            M[i].clear();
        cin >> n >> m;
        i64 ans = -1, tot = 2 * n - 1;
        for(int k = 1;k <= h;++ k){
            solve(n, k);
            auto [c, x, y] = n <= o ? H[n][min(g, k)] : M[k][n];
            if(c <= tot - m){
                ans = max(ans, (x + y) / k);
            } else break;
        }
        cout << ans << endl;
    }
    return 0;
}
```

为了去掉多余的那个 $\log$，需要对 $y$ 下手。假设在剪掉不少于 $m$ 个节点的情况下树的深度最大为 $t$，可以合理猜测最优的 $t_{\mathrm{best}}$ 要么等于 $t$ 要么等于 $t-1$（证明留给读者）。然后就做完了。时间复杂度 $\mathcal O(T\log n)$。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long i64;

const int MAXN = (1 << 19) + 3;
const int MAXM =  19 + 3;
const int MAXK =  32 + 3;

int o = (1 << 19), g = 20;
tuple<int, i64, i64> H[MAXN][MAXM];

unordered_map <int, tuple<int, i64, i64> > M[MAXK];
void solve(int n, int d){
    if(n <= o && d <= g)
        return;
    if(M[d].count(n))
        return;
    if(n == 1 || d == 1){
        M[d][n] = {1, 1, 0};
        return;
    }
    const int n1 = (n + 1) / 2, n2 = n - n1;
    solve(n1, d - 1);
    solve(n2, d - 1);
    const auto &[c1, u1, v1] = n1 <= o ? H[n1][min(g, d - 1)] : M[d - 1][n1];
    const auto &[c2, u2, v2] = n2 <= o ? H[n2][min(g, d - 1)] : M[d - 1][n2];
    M[d][n] = {
        c1 + c2 + 1, 1 + 2 * u1 + 2 * u2, v1 + u2 + v2
    };
}

int main(){
    int T;
    cin >> T;
    for(int i = 1;i <= o;++ i){
        for(int j = 1;j <= g;++ j){
            if(i == 1 || j == 1){
                H[i][j] = {1, 1, 0};
            } else {
                const int n1 = (i + 1) / 2, n2 = i - n1;
                const auto &[c1, u1, v1] = H[n1][j - 1];
                const auto &[c2, u2, v2] = H[n2][j - 1];
                H[i][j] = {
                    c1 + c2 + 1, 1 + 2 * u1 + 2 * u2, v1 + u2 + v2
                };
            }
        }
    }
    for(int _ = 1;_ <= T;++ _){
        int n, m, h = 32;
        for(int i = 1;i <= h;++ i)
            M[i].clear();
        cin >> n >> m;
        i64 ans = -1, tot = 2 * n - 1 - m;
        i64 sum1 = 1, val1 = n;
        i64 sum2 = 0, val2 = n - 1;
        int t = 0;
        if(tot < 1){
            cout << -1 << endl;
            continue;
        } else 
            -- tot;
        for(int k = 2;k <= h;++ k){
            i64 tval1 = (val1 + 1) / 2;
            i64 tval2 = (val1 + 1) / 2 - 1;
            i64 tsum1 = 0, tsum2 = 0;
            for(auto [sum, val] : {
                make_tuple(sum1, val1),
                make_tuple(sum2, val2)
                }){
                if(val == 1)
                    continue;
                if((val + 1) / 2 == tval1)
                    tsum1 += sum;
                else 
                    tsum2 += sum;
                if(val - (val + 1) / 2 == tval1)
                    tsum1 += sum;
                else
                    tsum2 += sum;
            }
            sum1 = tsum1, val1 = tval1;
            sum2 = tsum2, val2 = tval2;
            tot -= sum1 + sum2;
            if(tot < 0){
                t = k - 1; break;
            } else 
            if(tot == 0){
                t = k; break;
            }
        }
        for(auto &t0 : {t, t - 1}){
            if(t0 == 0)
                continue;
            solve(n, t0);
            auto [c, x, y] = n <= o ? H[n][min(g, t0)] : M[t0][n];
            ans = max(ans, (x + y) / t0);
        }
        
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：qczrz6v4nhp6u (赞：10)

最近脑子一团浆糊，考场上写了一坨没调出来，火大。

**UPD**：添加了对于计算 $cnt$ 的说明。

### Solution

观察建树代码，容易发现其建出的二叉树除最后一层是满二叉树。

显然，我们可以枚举删掉层数 $k$，并计算它的贡献。

当 $k$ 确定时，删除后二叉树的深度容易计算，于是我们只需考虑计算结点的编号和。

- 当 $k>0$ 时，删除后的树是满二叉树，此时结点编号和是容易计算的；

- 当 $k=0$ 时，我们可以将其拆成除最后一层的结点编号和加最后一层的结点编号和，前者容易计算，我们只需讨论后者。

接下来我们考虑如何计算最后一层结点的编号和。

不难证明当 $n\gets n+1$ 时，原树的某个叶结点下将会挂上两个新结点。设这个叶结点为 $u_n$，我们观察 $u_n$ 有什么性质。

首先，对于 $2^p\le n<2^{p+1}$，$u_n$ 显然应该在同一层，否则将会出现非完全二叉树。进一步可以得到 $u_n$ 在第 $p$ 层。

我们观察当 $2^p\le n<2^{p+1}$ 时，这些点的分布情况。以下是 $p=3$ 的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/2yssk4cs.png)

看起来有些规律，我们把它们都减去 $2^p=8$：

![](https://cdn.luogu.com.cn/upload/image_hosting/7rvuga2u.png)

很眼熟有没有。如果你学过 FFT（当然没学过也没关系），你就会发现第二行的每个数分别是第一行对应的数的**二进制翻转**。继续画图：

![](https://cdn.luogu.com.cn/upload/image_hosting/rtczzib0.png)

结果已经明了了。[证明](https://www.luogu.com.cn/paste/fnhe80tm)。

设 $k=n-2^p-1$，$\text{rev}(i)$ 为 $i$ 的**二进制翻转**，则最后一层的结点编号和即为：

$$\begin{aligned}&\sum_{i=0}^k((2^p+\text{rev}(i))\times 2)+((2^p+\text{rev}(i))\times 2+1)\\=&~(k+1)(2^{p+2}+1)+4\sum_{i=0}^k\text{rev}(i)\end{aligned}$$

现在就剩 $\sum_{i=0}^k\text{rev}(i)$ 这玩意了。

拆贡献按位考虑，对于 $0\le x< p$，统计 $[0,k]$ 中第 $x$ 位为 $1$ 的个数 $cnt$，答案累加 $cnt\times 2^{p-x-1}$ 即可。

关于计算 $cnt$，可以看看[这里](https://www.luogu.com.cn/paste/g1q85v4t)。

时间复杂度 $O(T\log n)$，空间复杂度视实现为 $O(\log n)$ 或 $O(1)$。

### Code

```cpp
#include<bits/stdc++.h>
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
using namespace std;
using uint=unsigned int;
using ll=long long;
using ull=unsigned long long;
char buf[1<<20],*p1=buf,*p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();bool f=0;
    for(;c<48||c>57;c=getchar())f|=c=='-';
    for(;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
    f&&(x=-x);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
Tp inline void assign(T *a,int n,T b){while(n--)*a++=b;}
Tp inline void copy(T *a,T *b,int n){while(n--)*a++=*b++;}
Tp inline void ckmin(T &a,T b){b<a&&(a=b);}
Tp inline void ckmax(T &a,T b){a<b&&(a=b);}
int n,m;ll sum[40],cnt[40];
int main(){
	int T;read(T);
	while(T--){
		read(n,m);
		int dep=__lg(n);
		for(int i=0;i<=dep;i++){
			cnt[i]=1<<i;
			sum[i]=(((3ll<<i)-1)<<i)>>1;
		}
		if((1<<dep)<n){
			cnt[dep+1]=(n-(1<<dep))<<1;
			ll k=n-(1<<dep)-1,res=0;
			for(int i=dep-1;i>=0;i--){
				ll tmp=(k&~((2ll<<i)-1))+(2ll<<i);
				res+=((tmp>>1)-min(tmp-k-1,1ll<<i))<<(dep-i-1);
			}
			sum[dep+1]=(k+1)*((1ll<<(dep+2))+1)+(res<<2);
			dep++;
		}
		ll ans=-1;
		for(int i=0;i<=dep;i++){
			if(i>0){
				sum[i]+=sum[i-1];
				cnt[i]+=cnt[i-1];
			}
			if(cnt[i]<=2*n-1-m)ckmax(ans,sum[i]/(i+1));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：zct_sky (赞：9)

### Solution
-----
可以先画出 $n=1\dots16$ 的树，通过观察可知，当 $n=2^d$ 时，该树为满二叉树，否则，若 $n=2^d+q(q> 0)$，则除去最后一层的 $2\times q$ 个节点外，该树为满二叉树。

设满二叉树部分深度为 $d$，则有 $n=2^d+q(q\ge 0)$。设 $k=2^d$。

本题可分 $m=0$ 与 $m \ne 0$ 时的两种情况讨论。

一般情况下，满二叉树的深度越深，其“美丽值”越大，因此，我们要尽可能保留较深的满二叉树。

- $m \ne 0$，则最后一层的 $2\times q$ 个节点一定被删，若 $m\le 2\times q$，则答案为 $\left\lfloor \dfrac{(2k-1)\times k}{2\times d} \right\rfloor$（满二叉树节点编号连续，从 $1$ 至 $2k-1$，求和之后除以当前深度 $d$ 即可）；若 $m> 2\times q$，则 $m$ 先减去 $2\times q$，再一层层减去每层节点个数（深度 $d$ 也随之减少），直至 $m\le 0$ 时输出答案或 $d=1$ 时输出 $-1$ 即可。 

- $m=0$，对于 $q=0$ 时的情况，直接计算即为最优；若 $q > 0$，则用分治计算最后一层节点之和，然后取不去除最后一层与去除最后一层的“美丽值”的最大值 ~~（赛时没取最大值喜提 80 pts）~~。

接下来讲如何分治计算最后一层节点之和。

由于最后一层节点都是成双成对的，我们可以把目光移至上一层，也就是它们的父节点处。

若父节点为 $a$，则产生的两个子节点和为 $4a+1$。

同理，若多个父节点和为 $b$，个数为 $k$，则它们的子节点和为 $4b+k$。

由于父节点个数已知（即 $q$），我们只需求出父节点和即可。然后又由于父节点均在同层，我们可以将其编号减去当前层最小编号 $k$ 后再算，之后加上 $q\times k$ 即可。

下面列出 $n=8\dots16,m=0$ 时的 $n,b$：

$n=8,b={\color{red}{0+2}}+{\color{blue}{1+3}}+4\times 4$

$n=9,b={\color{red}{0}}+1\times 8$

$n=10,b={\color{red}{0+4}}+2\times 8$

$n=11,b={\color{red}{0+4+2}}+3\times 8$

$n=12,b={\color{red}{0+4+2+6}}+4\times 8$

$n=13,b={\color{red}{0+4+2+6}}+{\color{blue}{1}}+5\times 8$

$n=14,b={\color{red}{0+4+2+6}}+{\color{blue}{1+5}}+6\times 8$

$n=15,b={\color{red}{0+4+2+6}}+{\color{blue}{1+5+3}}+7\times 8$

$n=16,b={\color{red}{0+4+2+6}}+{\color{blue}{1+5+3+7}}+8\times 8$（$n=16,8$ 时可以直接计算，这里仅仅是为了便于找最后一层节点和规律）

可以发现，蓝色部分的奇数为红色部分对应位置的偶数 $+1$，且若将偶数部分 $\div 2$，则就变成了上一层的奇数及偶数部分，因此可以用分治计算。

特别的，当该层为满的时候（如 $n=16,8$），可以直接返回 $0\dots k-1$ 的和，以此来节省时间，详见代码。

预计时间复杂度 $\mathcal{O}(T\log n)$ 左右（分治复杂度在 $\mathcal{O}(\log n)$ 左右罢）。

### Code
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	return x*y;

}
int t;
ll n,m,ans;
ll f(ll a,ll b){
	//特判小数据时情况 
	if(b<=1||a==1)return 0;
	if(a==2)return 1;
	//特判满时的情况 
	if(a==b)return (a-1)*a/2;
	//判断是 全偶+奇 还是 只有偶 
	if(b>a/2)return 2*f(a/2,a/2)/*全偶数：上一层总和*2 */+2*f(a/2,b-a/2)+b-a/2/*奇数：在偶数基础上+奇数个数个1*/;
	
	return 2*f(a/2,b)/*偶数*/;
}
int main(){
	t=read();
	while(t--){
		n=read();m=read();
		ll k=1,d=1,q;
		while(k*2<=n)d++,k=k*2;
		q=n-k;
		if(m){
			ll t=q*2;
			m-=t;
			if(m<=0){
				ans=k*(2*k-1)/d;
			}else{
				while(m>0&&k>1){
					t=k;
					m-=t;
					k/=2;
					d--;
				}
				if(m>0)ans=-1;
				else ans=k*(2*k-1)/d;
			}
		}else{
			ans=k*(2*k-1)/d;
			if(n!=k){
				d++;
				ll fuck=(f(k,q)+k*q)*4+q;
				ans=max((k*(2*k-1)+fuck)/d,ans);
				//一定要取最大值！ 
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：libohan0905 (赞：8)

### [P9689 Bina.](https://www.luogu.com.cn/problem/P9689)
### 题意简述
给你一个建树函数：
```cpp
void build(int s,int t,int p){
  if(s==t) return ;
  build(s,(s+t)/2,2*p);
  build((s+t)/2+1,t,2*p+1);
  add_edge(p,2*p),add_edge(p,2*p+1);
}
```
规定一棵树的美丽值 $=$ 这棵树的点的编号之和 $\div$ 这棵树的深度（结果向下取整）。

求 `build(1,n,1)` 的树在只保留前 $k$ 层的的最大美丽值，且要求至少砍掉 $m$ 个结点。不存在输出 $-1$。

多测，$1 \le T \le 10^5$，$1 \le n \le 10^9$，$0 \le m \le 2 \times 10^9$。

### 闲话
不一定是正解。~~坐等被叉，反正我马上就退役了，开摆~~。

退役前来写（应该是）最后一发题解，~~也是第一篇题解~~。

场上最后 10min 写出来，然后 T 成傻子，被隔壁 SYH 吊打。

然后赛后加了个记忆化就过了（大哭），还跑的挺快（~~至少吊打 SYH 的~~）。真的是离 AK 最近的一次。。。

如果需要图的话，使用 [graph_editor](https://csacademy.com/app/graph_editor/) 在左边的 Graph Data 输入（$n=10$ 的树）：
```
1 2
1 3
2 4
2 5
4 8
4 9
8 16
8 17
5 10
5 11
3 6
3 7
6 12
6 13
12 24
12 25
7 14
7 15
```
然后点击右上角 Config - 点击中间蓝色的 Run Command - 跳出来的 Arrange as tree。就可以欣赏这棵树了。

### 题解
首先，~~你先打了个表，放到 [graph_editor](https://csacademy.com/app/graph_editor/) 上看了一下~~。可以发现一些规律：
- 一个结点如果有儿子，那一定有两个。
- 每一层的编号从左到右都是连续的，而且相邻两层的编号也是连续的。
- 只有最后一层缺少结点，其他层全部都是满的，也就是说，这棵树是由一棵**满二叉树**和**一些叶子结点**构成的。

通过更细致的观察可以发现：
- 结点 $n$ 位于满二叉树最下面一层。
- $n$ 和这一层第一个结点编号的差就是满二叉树最后一层有儿子的结点数量。
- 可以通过 $n$ 来计算这棵树的结点数。

~~你不要问我怎么证啊，OI 不需要证明。~~

好的，那么只要 $m>0$，也就是最后一层一定要砍掉，那么只用计算上面的满二叉树。

这东西可以预处理，也就是 $f_i$ 代表层数为 $i$ 的满二叉树的美丽值。

在询问时，如果 $m$ 大于等于结点数，就一定不可能，否则就一步一步减少层数判断是否可行。可行了就把刚才预处理的输出就好了（因为你发现处理出来的 $f$ 数组是单调递增的）。

然后你就有了 16pts。

剩下的就是 $m=0$。

答案就是不砍的美丽值和砍最后一排的美丽值取大的。后者已经预处理出来了，前者就等价于问你**这棵树所有节点的和**。

前面一个满二叉树容易计算节点和，后面的点的**数量**你是知道的。重点是如何计算后面这部分的点权和，用 $n=10$ 的图来说就是如何得知最后一层的点权和是 $82$。会发现每个数都是在 $16$ 的基础上增加的，我们可以先计算贡献；上面一层的点会有两个儿子，我们也可以不管，待会一起处理贡献。

那么问题就转化为在最后这行的 $0\sim15$ 中你前两个是怎么得知是 $0$ 和 $8$ 的（结合下表食用）。

我们看一下每个数别访问的顺序和权值，为了方便理解顺序就从零开始：

|点权  |0  |1  |2  |3  |4  |5  |6  |7  |8  |9  |10  |11  |12  |13  |14  |15  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
|顺序  |0  |8  |4  |12  |2  |10  |6  |14  |1  |9  |5  |13  |3  |11  |7  |15  |

接着也会发现一些规律：
- 左半边每个点的顺序就是右半边减一。
- 如果问顺序前 $k$ 个数的权值和，右半边会有 $\lfloor \dfrac k 2 \rfloor$ 个数。

你发现这好像可以**分治**。只不过在更小块的区间内，左右块元素的差是 $2^{maxdep-dep}$。

然后你写了一个分治上去，~~历经九九八十一难~~终于调出来了。然后喜提 40pts。

你发现直接分治**复杂度不保**，于是就加了一个记忆化。然后就过了~~甚至跑的飞快~~。至于原因。。。手模了一下会发现每个深度不同的非零的 $k$ 最多只有两个，复杂度应该是 $\mathcal{O}(T\log^2n)$ 的，还有一只 $\log$ 在 `map` 上。

~~我自己都不知道为什么是这样却写出了代码，这是人性的扭曲还是道德的沦丧！~~

### 完整代码
抽象的代码。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*f;
}
const int N=2e5+5;
int maxdep;
ll f[N];
map<pair<int,int>,int>mp;
//一开始写 l,r 的 后来发现用不着就删了
int cdq(int k,int dep){//深度为 dep 范围内有 k 个点
	if(dep>maxdep) return 0;
	if(mp[{k,dep}]) return mp[{k,dep}];//记忆化
	ll ans=0;
	if(k-k/2) ans+=cdq(k-k/2,dep+1);
	if(k/2){
		if(k&1) ans+=cdq(k/2,dep+1);
		else ans<<=1;
		ans+=(k/2)*(1ll<<(maxdep-dep));//右端点的额外贡献
	}
	return mp[{k,dep}]=ans;
}
void solve(){
	ll n=read(),m=read();
	int dep=0;
	while((1ll<<dep)<n) ++dep;
	int p=(1ll<<dep)-1+(n-(1ll<<dep-1))*2;//结点数 
	if(m>=p) return puts("-1"),void();
	ll now=0,cnt=0;
	if(m){
		cnt=(n-(1ll<<dep-1))*2;
		while(cnt<m){cnt+=(1ll<<dep-1),--dep;}
		return printf("%lld\n",f[dep]),void();
	}
	ll r=(n-(1ll<<dep-1));//满二叉树最下面一层有儿子的结点的个数
	maxdep=dep-1;mp.clear();
	cnt=cdq(r,0);
	now=max(f[dep],(((1ll<<dep)-1)*(((1ll<<dep)-1)+1)/2+r*2*(1ll<<dep)+cnt*2+r)/(dep+1));
  //满二叉树的贡献加上最后一行奇奇怪怪的贡献
	printf("%lld\n",now);
}
signed main(){
	ll now=1;
	for(int i=1;i<=32;i++) {
		now<<=1;
		f[i]=now/2*(now-1)/i;//预处理满二叉树的美丽值
	}
	int T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：Pengzt (赞：5)

[P9689](https://www.luogu.com.cn/problem/P9689)

难评。

可以直接枚举树的高度，看有没有砍掉 $m$ 个点。

当 $k$ 小于树的深度时，显然节点个数为 $2^k-1$，此时编号和是容易的。

但是当 $k$ 等于树的深度时，编号和不能直接求出，因为最后一层的编号不是连续的。

令 $x=ed-st+1$。子树大小是容易通过记忆化得到的。考虑编号和，容易发现当 $x$ 是偶数时，两边的子树的形态是一致的，考虑从这里下手。

不妨设 $f_x$ 表示传入的参数为 $x$ 时，且该子树根节点为 $1$ 的编号和。

但是转移时变为了以 $2$ 为根的子树和以 $3$ 为根的子树的编号和加 $1$。

然后看它与 $1$ 为子树的编号和的变化。以 $2$ 为例，发现就是如果有 $c$ 个节点，满足 $2^p-1<c\le2^{p+1}-1$，则变化了 $\sum\limits_{i=0}^{p}4^i+2^{p+1}(c-2^p+1)$，即按层考虑。

注意 long long，赛时卡了好久。

和线段树是很像的，每层是不会超过两次查询的，然后每次合并 $sz_{ls}$ 和 $sz_{rs}$ 是 $\mathcal{O}(\log n)$。可以使用 umap 存储 $f$。

时间复杂度：$\mathcal{O}(T\log^2n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n,m;
unordered_map<ll,ll> mp,f;

ll dfs(ll x){
	if(mp[x])return mp[x];
	if(x==1)return 1;
	if(x%2==0)return mp[x]=2*dfs(x/2)+1;
	return mp[x]=dfs(x/2)+dfs(x/2+1)+1;
}
ll calc(ll l,ll r){
	return (l+r)*1ll*(r-l+1)/2;
}
ll work(ll x){
	ll res=0;
	for(int i=1;i<=31;i++)if((1ll<<i)-1<x)res+=(1ll<<(2*i-2));else{
		res+=(1ll<<(i-1))*(x-((1<<(i-1)))+1);
		break;
	}
	return res;
}
ll gh(ll x){
	if(f[x])return f[x];
	if(x==1)return 1;
	int p=dfs(x/2);
	if(x%2==0){
		f[x]=2*gh(x/2)+work(p)+2*work(p)+1;
		return f[x];
	}
	f[x]=gh(x/2+1)+gh(x/2)+2*work(p)+work(dfs(x/2+1))+1;
	return f[x];
}
void solve(){
	cin>>n>>m;
	ll al=dfs(n);ll ans=0;
	if(m>=al){
		cout<<"-1"<<"\n";
		return;
	}
	for(int i=1;i<=31;i++)
		if((1ll<<i)-1<al){
			if((al-(1ll<<i)+1)>=m)ans=max(ans,calc(1,(1ll<<i)-1)/i);
		}else{
			if(!m)ans=max(ans,gh(n)/i);
			break;
		}
	cout<<ans<<"\n";
}

int main(){
	int T;cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：recollect_i (赞：2)

可以发现，一棵线段树的形态是根据长度唯一确定的，所以，可以考虑求一个长度、保留 $k$ 层的节点数量和编号和。

设 $f_n,g_n,h_n$ 分别表示长度为 $n$ 的线段树的节点数量、每个节点所在层最小编号之和、每个节点编号简所在层最小编号之和，则节点编号之和等于 $h_n+g_n$。

设 $l,r$ 分别表示左右子树长度，画图不难发现：

- $r=\lfloor\frac{n}{2}\rfloor,l=n-\lfloor\frac{n}{2}\rfloor$；
- $f_n=f_l+f_r+1$；
- $g_n=2(g_l+g_r)+1$；
- $h_n=h_l+h_r+g_r$。

一个结论是，用这种方法构建的线段树，不同长度的节点数量是 $O(\log n)$ 的，所以涉及到的长度是 $O(\log n)$ 的，可以直接记忆化搜索加 `unordered_map` 实现。但常数太大，完全无法通过此题。

注意到，我们可以用一个堆储存可能涉及的长度，每次取堆顶元素并加入可能涉及长度的数组中，然后在堆中加入左右儿子长度，这样得到的数组是由大到小排序后的。现在就可以直接 DP 了。

对每个保留的深度计算节点数量和编号和，时间复杂度 $O(T\log^2n)$，能通过此题。

注意到除了全部保留，经过修剪的线段树都是满二叉树且编号连续，所以可以直接计算，时间复杂度 $O(T\log n)$。

~~Acoipp 重新定义了基础赛难度。~~

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 100005;

struct node{
	LL x, y, z;
	node() {}
	node(LL _x, LL _y, LL _z) : x(_x), y(_y), z(_z) {}
};
node operator +(node l, node r) {return node(l.x + r.x + 1, (l.y + r.y) * 2 + 1, l.z + r.z + r.y);}

int x[N], tt;
priority_queue<int> pq;
node f[N][35];
map<int, int> mp;

int main()
{
	int MT = 1e5, MN = 1e9, MM = 2e9;
	int T;
	scanf("%d", &T);
	assert(T <= MT);
	while(T -- )
	{
		int n, m, k;
		scanf("%d%d", &n, &m);
		assert(n > 0 && m >= 0 && n <= MN && m <= MM);
		if(m >= n * 2 - 1) puts("-1");
		else
		{
			LL ans = 0;
			k = ceil(log2(n)) + (m == 0);
			pq = priority_queue<int>();
			pq.push(n);
			mp.clear();
			tt = 0;
			while(pq.size())
			{
				int u = pq.top();
				pq.pop();
				if(x[tt] != u)
				{
					x[ ++ tt] = u;
					if(u > 1) pq.push(u / 2), pq.push(u - u / 2);
				}
			}
			
			reverse(x + 1, x + tt + 1);
			for(int i = 1; i <= tt; i ++ ) mp[x[i]] = i;
			for(int i = 1; i <= k; i ++ ) f[1][i] = node(1, 1, 0);
			for(int i = 2; i <= tt; i ++ )
			{
				int r = mp[x[i] / 2], l = mp[x[i] - x[i] / 2];
				f[i][1] = node(1, 1, 0);
				for(int j = 2; j <= k; j ++ ) f[i][j] = f[l][j - 1] + f[r][j - 1];
			}
			
			for(int i = 1; i <= k; i ++ )
			{
				if(m >= n * 2 - f[tt][i].x) break ;
				ans = max(ans, (f[tt][i].y + f[tt][i].z) / i);
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}
```

---

## 作者：Thomas0218 (赞：1)

## 分析
题意：给定 $T\leq 10^5$ 组数据，每次给定 $n,m\leq 10^9$。你要以 $[1,n]$ 作为值域建线段树，然后你可以选择一个 $k$，将线段树上深度大于 $k$ 的结点全都砍掉，且砍掉的结点数必须不小于 $m$。让你最大化砍完之后树上结点编号（结点编号即原始线段树上的编号）之和除以深度。

我们可以发现就是线段树上除了最后一层的结点都是非常规整的，且最后一层上面的所有结点构成了一棵完全二叉树。这棵完全二叉树上的结点编号之和都是易于计算的。而且我们是一层一层地砍，那么如果没有最后一层肯定砍的层数越少越好。所以现在我们只需要求最后一层的结点编号之和。

我们发现，线段树上不同长度的区间数量很少，每层最多只有两种区间，线段树上不同长度的区间最多只有 $O(\log n)$ 种。而且如果两个相同的区间在同一层，那么它们下面的结构也必定是相同的。这就启发我们使用记忆化搜索的方式解决这道题。

我们记 $ans_{dep,len}$ 表示深度为 $dep$，长度为 $len$ 的区间所包含的最后一层的叶子结点编号和，$last_{dep,len}$ 表示这个区间所包含的最后一层的最左端叶子结点的编号，$cnt_{dep,len}$ 表示这个区间所包含的最后一层的叶子结点个数。

当我们遇到一个区间时，如果之前遇到过和它同层同长度的区间，那么我们就可以用上述三个东西更新答案。首先我们先算出这个区间在最后一层最左端的编号。注意这里我们不关心那个编号是否真的有结点。

令这个区间在最后一层最左端的编号 $l=p*2^{mxdep-dep}$，其中 $mxdep$ 为最大深度，$p$ 为当前区间的结点编号。最后一层的叶子结点（如果算上空的）的编号是连续的，因此当前区间所对的叶子结点编号都会较上一次遇到该同层同长度区间时大 $l-last_{dep,len}$。因此 $ans_{dep,len}=ans_{dep,len}+cnt_{dep,len} * (l-last_{dep,len})$。

那么总答案 $sum=sum+ans_{dep,len}$，注意先更新 $ans$ 再更新 $sum$。最后一层结点数 $tot=tot+cnt_{dep,len}$；最后更新 $last_{dep,len}=l$。

如果这个深度和长度的区间是第一次遇到就往下递归。注意递归上来时需要合并左右结点的信息到自己：
```cpp
Build(2 * p, l, mid, dep + 1); 
ans[dep][len] = ans[dep+1][mid-l+1];
if(last[dep+1][mid-l+1]) last[dep][len] = last[dep+1][mid-l+1];
cnt[dep][len] = cnt[dep+1][mid-l+1];
Build(2 * p + 1, mid + 1, r, dep + 1);
ans[dep][len] += ans[dep+1][r-mid], cnt[dep][len] += cnt[dep+1][r-mid];
```
注意这里需要先加上左边的再递归右边的，因为左边的有可能会被右边的覆盖掉。

现在来分析以下复杂度。最坏情况下，设第 $i$ 层的区间长度是 $2k+1,2k$，那么肯定先递归到 $2k+1$。此时区间被拆为 $k+1,k$。同层 $2k$ 长度的区间肯定会被拆为 $k,k$，由于下一层长度为 $k$ 的区间已经被记录过了，会直接返回；而同层长度 $2k+1$ 的区间由于也被记录过了，会直接返回。因此每层实际只会往下递归一次，总复杂度 $O(T\log n)$。注意这里 $ans,last,cnt$ 记录长度那一维需要使用 `map/unordered_map`，且程序实现不好会 T 飞。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 35;
int T, n, m, mx, tot;
unordered_map <int,ll> ans[N];
unordered_map <int,int> last[N], cnt[N]; ll sum;
void BuildDep(int l, int r, int dep) {
	mx = max(mx, dep); int mid = (l + r) / 2;
	if(l == r) return ;
	BuildDep(l, mid, dep + 1);
}
void Build(int p, int l, int r, int dep) {
	int len = r - l + 1, mid = (l + r) / 2;
	if(l == r && dep != mx) return ;
	if(last[dep][len]) {
		int now_l = p * (1 << (mx - dep));
		ans[dep][len] += cnt[dep][len] * 1ll * (now_l - last[dep][len]);
		sum += ans[dep][len], tot += cnt[dep][len], last[dep][len] = now_l;
		return ;
	}
	if(l == r) { last[dep][1] = p, ans[dep][1] = p, cnt[dep][1] = 1, sum += p, tot++; return ; }
	Build(2 * p, l, mid, dep + 1); 
	ans[dep][len] = ans[dep+1][mid-l+1];
	if(last[dep+1][mid-l+1]) last[dep][len] = last[dep+1][mid-l+1];
	cnt[dep][len] = cnt[dep+1][mid-l+1];
	Build(2 * p + 1, mid + 1, r, dep + 1);
	ans[dep][len] += ans[dep+1][r-mid], cnt[dep][len] += cnt[dep+1][r-mid];
}
int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m); mx = 0, sum = 0, tot = 0;
		for(int i = 0; i < N; i++) { last[i].clear(); ans[i].clear(); cnt[i].clear(); }
		BuildDep(1, n, 1); Build(1, 1, n, 1); int all_node = (1 << (mx - 1)) - 1 + tot;
		ll max_ans = -1;
		for(int k = 1; k < mx; k++) {
			int deleted = all_node - (1 << k) + 1;
			if(deleted < m) continue ;
			max_ans = max(max_ans, ((1ll << k) * ((1ll << k) - 1) / 2) / k);
		}
		if(m <= 0) max_ans = max(max_ans, ((1ll << (mx - 1)) * ((1ll << (mx - 1)) - 1) / 2 + sum) / mx);
		printf("%lld\n", max_ans);
	}
	return 0;
}
```

---

## 作者：irris (赞：1)

> 模拟 / 递推 / 线段树 / implementation

## Preface

这是一道很搞笑，但是不好写的题目。

和题解区所有做法都不一样捏。

为啥激励计划评分要是自然数，本来想给 $6.5$ 的 /qd。

## Solution

反手一个强化问题，求线段树每一层的大小和节点标号和。

我们不加证明地给出几个引理（或者说，*常识*）。

> + **引理 1**：设线段树有 $dep$ 层。因为线段树的每个节点儿子个数只有 $0$ 或 $2$，那么 $2^{dep - 1} \leq n \leq 2^{dep} - 1$。这同样告诉我们 $dep = \mathcal O(\log n)$。
> + **引理 2**：线段树的前 $dep - 1$ 层是满的，故大小可以简单得出，标号和可以使用等比数列求和。
> + **引理 3**：总共有 $k = 2n - 1 - \sum\limits_{i=1}^{dep-1} sz_i$ 个节点位于线段树的最后一层。

我们只需要求出最后一层叶子结点的标号和。

考虑这些叶子结点分别挂在哪些 $dep - 1$ 层的节点上。令 $dep = 4$，$n$ 每次增加 $1$ 都会有新的 $2$ 个叶子结点挂在原来的一个叶子节点上。我们不难发现这样一个序列：$[1, 5, 3, 7, 2, 6, 4, 8]$（这里的编号是相对标号，而不是绝对标号）。

我们观察它的构造规律，是先把奇数项提到前面来，然后递归构造。

> **引理 4**：由于 $mid = \lfloor \frac{l+r}2 \rfloor$，一定有 **$\bm{[l, mid]}$ 区间长度不小于 $\bm{[mid + 1, r]}$ 区间长度**。所以如果有多余的叶子节点，优先挂在 $[l, mid]$ 区间再挂在 $[mid + 1, r]$ 区间。

所以问题转化为：求长度为 $2^n$ 的，形如 $[1, 5, 3, 7, 2, 6, 4, 8]$ 类数列的前 $k(0 \leq k \leq 2^n)$ 项和（这里的 $n = dep - 2$，$k = \frac 12 sz_{dep}$）。不难得出：

- $f(0, 0) = 0$，$f(0, 1) = 1$。
- 递归式：$f(n, k) = \begin{cases} 2f(n - 1, k - 2^{n-1}) + 2^{2n-2}, & 2^{n-1} \leq k \leq 2^n \\ 2f(n - 1, k) - k, & 0 \leq k \lt 2^{n-1} \end{cases}$。

解释：若 $k \geq 2^{n-1}$，则说明奇数已经全部被选中，它们的和是等差数列 $(1 + (2^n - 1)) \cdot 2^{n-1} \cdot \frac 12 = 2^{2n-2}$；对后面每个偶数，除以 $2$ 以后即化为了 $n - 1$ 的问题。否则说明奇数没有全部被选中，对其中每个数 $x$ 变为 $\frac{x+1}2$ 后转化为了同样的问题。因为 $n$ 是对数大小级别，可以直接递归计算。

求出来 $S = f(n, k)$ 之后，由于每个 $x$ 对应的叶子结点是 $2x, 2x+1$ 和为 $4x + 1$，随意根据 $S$ 和 $k$ 计算一下实际的和即可。

最终枚举断到哪一层即可。

时间复杂度 $\mathcal O(T\log n)$，特判 $n = 1$。

## Code

```cpp
#include <bits/stdc++.h>

using ull = unsigned long long;
ull f(int n, int k) {
	if (n == 0) return k;
	if (k & (1 << n - 1)) return (1ull << (2 * n - 2)) + (f(n - 1, k ^ (1 << n - 1)) << 1);
	return (f(n - 1, k) << 1) - k;
}

int sz[35];
ull sum[35];
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	int T; std::cin >> T;
	for (int i = 1, N, M; i <= T; ++i) {
		std::cin >> N >> M;
		if (N == 1) { std::cout << (M == 1 ? 1 : -1) << '\n'; continue; }
		int dep = 1, all = 0;
		while ((1 << dep - 1) < N) ++dep;
		for (int i = 1; i < dep; ++i) {
			sz[i] = (1 << i - 1);
			sum[i] = ((1ull + all + all + sz[i]) * sz[i]) >> 1; // (all + 1) ~ (all + sz[i])
			all += sz[i];
		}
		sz[dep] = (N << 1) - all - 1;
		sum[dep] = (f(dep - 2, sz[dep] >> 1) << 2) - (sz[dep] >> 1) + ((1ull << dep - 1) - 1) * sz[dep];
		ull ans = 0, s = std::accumulate(sum + 1, sum + dep + 1, 0ull);
		// for (int k = 1; k <= dep; ++k) std::cout << sz[k] << ' ' << sum[k] << '\n';
		for (int k = dep, p = 0; k; --k) {
			if (p >= M) ans = std::max(s / k, ans);
			p += sz[k], s -= sum[k];
		}
		if (ans == 0) std::cout << "-1\n"; else std::cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：Alphas (赞：1)

### Part 1 初步思考

* 理解题目

发现 build 的代码和平常我们所熟悉的线段树等价，题目仅仅是给线段树的每个节点赋了一个权值。进一步观察树的性质可以发现任意两个叶子节点深度之差不超过 $1$。

* 这棵树有几个节点？

由于长度相等的线段等价，不妨用 $f(x)$ 表示**任意**长度为 $x$ 的区间根据 build 函数建树所产生的节点个数。我们发现 

$$f(x) = \left\{\begin{matrix} 
  1, x = 1
  \\
  f(\lfloor\frac x2\rfloor) + f(\lceil\frac x2\rceil) + 1, x\neq 1
\end{matrix}\right. $$

打表或者手推可以发现 $f(x) = 2 \times x - 1$。

采用数学归纳法证明证明：

1. 当 $x = 1$ 时，$f(x) = 1 = 2\times 1 - 1$，成立；
2. 当 $x\le k$ 成立时，即 $\forall x\le k, f(x) = 2\times x - 1$ 成立。显然有 $1\le \lfloor\frac x2\rfloor,\lceil\frac x2\rceil\le  k$，故 $f(\lfloor\frac x2\rfloor) = 2\times \lfloor\frac x2\rfloor-1, f(\lceil\frac x2\rceil)=2\times \lceil\frac x2\rceil-1$，根据递推式可以推得 $f(x) = f(\lfloor\frac x2\rfloor) + f(\lceil\frac x2\rceil) + 1= 2\times \lceil\frac x2\rceil + 2\times \lfloor\frac x2\rfloor-2+1=2\times (\lceil\frac x2\rceil + \lfloor\frac x2\rfloor)-1 = 2 \times x - 1$。故 $x = k + 1$ 也成立，即 $x\le k + 1$ 成立；
3. 综合 12 所述，对于任意 $x\ge 1$，命题成立。

* 什么时候无解？

根据题目，至少要保留第一层，所以如果树的总节点数减去删掉的节点数 $m$ 小于等于 $0$，那么不符合题意。

### Part 2 计算一部分答案

假设我们现在选取的深度为 $d$，**小于整颗树的深度**，在删掉所有深度大于 $d$ 的节点后，剩下的应该是一个深度为 $d$ 的**满二叉树**。节点权值将为 $1$ 到 $2 ^ d - 1$，故答案为 $\lfloor\frac{\frac 12\times (2^d - 1)\times 2^d}{d}\rfloor$，计算后取 max 即可。

```cpp
for (int i = 1; i <= 32; i++) {
    if ((1ll << i) > 2 * n - m) continue;
    ans = max(ans, (1ll << (i - 1)) * ((1ll << i) - 1) / i);
}
```

### Part 3 计算另一部分答案

我们愉悦的完成了代码，提交，发现样例输入 $n = 10, m = 0$ 时会挂，真正的数据也只能得 $16$ 分。仔细观察发现，当 $m = 0$ 时，并不需要删除任何的节点，这意味着我们可以选择整颗树，问题转换为计算整颗树中所有节点权值之和。本人在赛时面对此问题无从下手，便使用程序打表。为了方便，我们选取树高相同的一段 $n$，如 $n\in(32, 64]$。

```cpp
map<int, int> vis;
int tot = 0;
void add_edge(int x, int y) {
    if (!vis[x]) vis[x] = 1, tot += x;
    if (!vis[y]) vis[y] = 1, tot += y;
}
void build(int s, int t, int p) {
    if (s == t) return;
    build(s, (s + t) / 2, 2 * p);
    build((s + t) / 2 + 1, t, 2 * p + 1);
    add_edge(p, 2 * p), add_edge(p, 2 * p + 1);
}
int main() {
    for (int i = 33; i <= 64; ++i) {
        tot = 0, vis.clear();
        build(1, i, 1);
        cout << tot << " ";
    }
    return 0;
}
```

输出 `2145 2338 2499 2724 2869 3078 3255 3496 3633 3834 4003 4236 4389 4606 4791 5040 5173 5370 5535 5764 5913 6126 6307 6552 6693 6898 7071 7308 7465 7686 7875 8128`。

如此庞大的数据，看上去无从下手，不过回顾相邻两数差值的来源，可以发现是 $n$ 变大一，导致原来一个长度为 $1$ 的子区间（记其权值为 $p$）变成了长度为 $2$ 的，然而这个区间对应的节点仍需拆分为两个单位区间，其对应节点权值为 $2\times p, 2\times p + 1$，总权值变大 $4\times p + 1$。所以我们修改上述打表代码，同过差分，使其输出被改动节点的权值。

```cpp
int last, tot = 0;
build(1, 32, 1), last = tot; // n = 32 时的答案，方便差分计算
for (int i = 33; i <= 64; ++i) {
    tot = 0, vis.clear();
    build(1, i, 1);
    cout << (tot - last - 1) / 4 << " ";
    last = tot;
}
```

观察输出数据 `32 48 40 56 36 52 44 60 34 50 42 58 38 54 46 62 33 49 41 57 37 53 45 61 35 51 43 59 39 55 47 63`，发现如下几点性质：

1. 序列前 $1$ 个数为 $2 ^ 5$ 的倍数；前 $2$ 个数为 $2^4$ 的倍数；等等；前 $2^5$ 个数为 $1$ 的倍数。
2. 若将序列分成前后两段，长度均为 $16$，对应元素相差为 $1$； 若将上一条中的前一半序列分成前后两段，长度均为 $8$，对应元素相差为 $2$； 若将上一条中的前一半区间分成前后两端，长度均为 $4$，对应元素相差为 $2^2$； 依次类推，同理。
3. 所有数在 $[32, 63)$ 范围内。

感性理解一下，线段树追求的是“均匀”，故大小变大而分裂的子区间一定是一左一右，一左一右的来，符合上述数据。

则比如要计算 $n = 34$ 时的结果，我们便要求出 $n = 32$ 时的结果，加上差分数组中的 $32 + 48$。很巧的是，$n = 32$ 为满二叉树，所以可是使用 Part 2 的结论，问题转换为差分数组前缀和。

我们可以使用分治求解，具体的，记录当前的一个区间 $[1, p]$，初始其为 $[1, 32]$：

1. 如果当前求的 $s(1, x)$ 完全处于前半段，即 $x\le \frac p2$，那么缩小区间为 $[1, \frac p2]$，并递归执行；
2. 否则，将 $s(1, x)$ 变为 $s(1, \frac p2) + s(\frac p2+1, x)$，由于性质 1，前半项等价于**求一个区间内 $2$ 的某次方的倍数之和**，由于性质 2，后半项可以整体**加上某个形如 $2$ 的某次方的差值**，将其变为 $s(1, x - \frac p2)$，并递归执行。

读者可以自行思考如何将上文中具体化探讨的深度同为 $7$ 的 $n$ 推广到深度同为任意 $k$ 的 $n$ 的解法，分治的框架并没有变，只是上文加粗部分的具体数值产生了改变。

```cpp
int lsum(int l, int r, int x) { // 求一段区间内某个数倍数的和
    int st = ((l - 1) / x + 1) * x;
    int ed = (r / x) * x;
    return (st + ed) * ((ed - st) / x + 1) / 2;
}
int calc(int l, int r, int x, int v, int ed) { // 分治计算差分数组前缀和
    if (l == r) return ed;
    int mid = l + r >> 1;
    if (mid - l + 1 >= x) return calc(l, mid, x, v * 2, ed); // 完全落在前一段中
    else return lsum(ed, ed * 2 - 1, v * 2) + calc(l, mid, x - (mid - l + 1), v * 2, ed) + (x - (mid - l + 1)) * v; // 部分落在后一段中
}
int sum(int x) {
    if (x == 1) return 0;
    int y = (1 << ((int)log2(x - 1))); 
    return y * (2 * y + 1) + x - y + 4 * calc(1, y, x - y, 1, y) - 2 * y; // 计算结果，注意加上前面满二叉树的贡献，比如在举得例子中就是 n = 32 的贡献
}
```

### Part 4 总结

以上做法，单次询问，Part 2 的复杂度为 $\log n$，Part 3 中分治的区间大小每次减半，复杂度也为 $\log n$，总复杂度为 $\Theta(T\log n)$。

完整代码：https://www.luogu.com.cn/paste/ggahhg4b

**非常短，且最慢的点仅 66ms**。

本文仍存在不严谨的地方，比如 Part 3 中两条性质笔者并不会证明，如果各路大佬知道的话，请私信指导一下，感谢！

本题作为一道基础赛的题目，难度可能略高。其考察了选手对线段树的性质，分治算法等的较为深入的理解，难度约为上位绿到中位蓝，个人认为是一道高质量的题目，在此为出题人点赞并表示感谢！

---

## 作者：lfxxx (赞：1)

考场上一直没过的原因是用了 STL 的哈希表给我整 TLE 了。

哦，考场代码有一个地方忘记忆化了，那没事了。

直接考虑枚举保留多少层的节点，对于除了最后一层以外的层，编号一定是连续的且为 $2^{dep} - 1$ 编号之和和数量可以直接算，现在问题变成求整棵树（应该都看得出来是线段树）的节点数量和节点编号和。

注意到一棵线段树的形态只和他所管辖的区间 **长度** 有关，所以不妨直接以长度为状态去转移，先考虑节点数量，它的转移是 $dp_{l,r} = dp_{l,mid} + dp_{mid+1,r}$。

然后考虑编号和，注意到这个与根节点的编号有关，而且较难找规律所以不妨维护整棵树编号和关于根节点编号的一次函数，也可以利用上面类似的方法去合并。

由于线段树是较为平衡的，所以同一层节点管辖权的区间长度之差最大为 $1$，故只有 $O(\log V)$ 种状态，理论上用哈希表记录可以做到 $O(T \log V)$ 然而实际上远远不如用平衡树的 $O(T \log^2 V)$。

下面给出的代码为了好写写的记忆化。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO{
	const int SIZE=1<<21;
	static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
	#define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
	#define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
	#define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
	#define puts(x) IO::Puts(x)
	template<typename T>
    inline void read(T&x){
    	for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
    	for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15); 
    	x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    inline void Puts(const char*s){
    	for(int i=0;s[i];i++)
			putchar(s[i]);
		putchar('\n');
	}
	struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;
int T;
int sum;
map<int,int> mp,A,B;
inline int build(int l,int r){
	if(mp[r-l+1]!=0) return mp[r-l+1];
	if(l==r){
		A[1]=1;
		B[1]=0;
		return mp[1]=1;	
	}
	int mid=(l+r)>>1;
	if((mid-l+1)==(r-mid)){
		mp[r-l+1]=build(l,mid)*2+1;
		pair<int,int> res1=make_pair(A[mid-l+1],B[mid-l+1]);
		pair<int,int> res2=res1;
		res1.first*=2;
		res2.second+=res2.first;
		res2.first*=2;
		A[r-l+1]=res1.first+res2.first+1;
		B[r-l+1]=res1.second+res2.second;
		return mp[r-l+1];
	}
	else{
		mp[r-l+1]=build(l,mid)+build(mid+1,r)+1;
		pair<int,int> res1=make_pair(A[mid-l+1],B[mid-l+1]);
		pair<int,int> res2=make_pair(A[r-mid],B[r-mid]);
		res1.first*=2;
		res2.second+=res2.first;
		res2.first*=2;
		A[r-l+1]=res1.first+res2.first+1;
		B[r-l+1]=res1.second+res2.second;
		return mp[r-l+1];
	}
}
signed main(){
	//freopen("1.in","r",stdin);
    read(T);
    while(T--){
    	mp.clear();
    	A.clear();
    	B.clear();
        int n,m;
        read(n);
        read(m);
        sum=0;
        int ans=-1;  
		int len=n;	
        n=build(1,n);
        sum=A[len]+B[len];
        for(int k=1;k<=33;k++){
            int end=(1ll<<k)-1;
            if(end>n){
            	if(m==0){
            		ans=max(ans,sum/k);
				}
				break;
			}
            if(n-end>=m){
				ans=max(ans,(end*end+end)/2/k);	
        	}
        }
        write(ans);
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：uid_310801 (赞：0)

之前写了一个超级麻烦的分讨做法，今天重新审视了一下，发现只需要在 $16$ 分的基础上改一改就过了。

本题主要分为两步：

1. 求出每一层节点个数，每一层节点编号和。

2. 枚举要保留多少层，求合法且最大的答案。

显然，难点在于第一步。

很明显，构建二叉树的代码与线段树的代码不能说十分类似吧，只能说是一模一样。而线段树有一个众所周知的特点，就是每一层最多只有两种不同长度的节点，证明自己手玩一下就能理解了。

于是设置递归：

$solve(n,de,c,e,sc,se)$ 分别表示当前第 $de$ 层长度为 $n$ 的节点个数为 $c$，编号和为 $sc$，长度为 $n+1$ 的节点个数为 $e$，编号和为 $se$。

初始调用 $solve(n,1,1,0,1,0)$，每一层统计一下当前层的节点个数和编号和，然后根据 $n$ 的奇偶性确定转移系数即可。

注意最后 $n=1$ 的时候要判断一下 $e$ 是否等于 $0$ 来确定是否再递归一层。

复杂度 $O(\log n)$，代码和思维量都非常简单：

```cpp
//追随天波老师，天波好闪，拜谢天波
void solve(ll nw,ll d,ll c,ll e,ll sc,ll se){
	de[d]+=c+e;
	sur[d]+=sc+se;
	if(nw==1){
		if(e!=0)solve(nw,d+1,e*2,0,se*4+e,0);
		return;
	}
	if(nw%2==0)solve(nw/2,d+1,c*2+e,e,sc*4+c+e+se*2,se*2);
	else	solve(nw/2,d+1,c,e*2+c,sc*2+c,sc*2+se*4+e);
}
void work(){
	ll n=read(),m=read();
	memset(de,0,sizeof(de));
	memset(sur,0,sizeof(sur));
	ll ans=-1,maq=0,sum=0,ans2=0;
	dfs(n,1,1,0,1,0);
	for(int i=1;i<=32;i++)	ans2+=de[i];
	for(int i=1;i<=32;i++){
		sum+=de[i];
		maq+=sur[i];
		if(ans2-sum>=m){
			ans=max(ans,maq/i);
		}
	}
	printf("%lld\n",ans);
}
```


---

