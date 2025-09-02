# [CSGRound3] 仙人掌

## 题目背景

ckw 是一个非常菜的菜鸡。

## 题目描述

ckw 有好多边仙人掌。边仙人掌是一个每条边至多在一个简单环里的简单无向连通图。 

ckw 定义了无向图的度数序列，度数序列的长度为图中点的个数，度数序列中第 $i$ 个元素是图中编号为 $i$ 的节点的度数。

ckw 想知道，对于所有 $n$ 个点 $m$ 条边的边仙人掌，其不同的度数序列有多少种。

输出答案模 $998244353$ 之后的结果即可。（如果不存在合法仙人掌输出 $0$ 即可）

## 说明/提示

**【样例解释】**

对于第一组数据，这里给出其中四个合法的度数序列：$\{2,2,2,2\},\{1,2,2,3\},\{1,2,3,2\},\{2,1,3,2\}$。

---

**【数据范围】**

**本题采用捆绑测试。**

- Subtask 1（8 points）：$n \le 5$。
- Subtask 2（10 points）：$n \le 10 $。
- Subtask 3（18 points）：$n \le 35$。
- Subtask 4（12 points）：$n \le 90$。
- Subtask 5（8 points）：$m = n - 1$。
- Subtask 6（10 points）：$m = n$。
- Subtask 7（16 points）：$m = n + 1$。
- Subtask 8（18 points）：无特殊限制。

对于 $100\%$ 的数据，$1 \le T \le 10$，$0 \le n \le 2 \times 10^3$，$0 \le m \le 10^9$。

## 样例 #1

### 输入

```
7
4 4
5 6
50 70
90 102
40 41
2000 1999
1785 2425```

### 输出

```
13
5
442759796
851878741
292277388
943337434
183253103```

# 题解

## 作者：zhouwc (赞：5)

### 前言
这是 CSGRound 3 的 E 题，在月赛上只有 $4$ 个同学做出了此题，且在赛后没有人写题解。所以我在此发布官方题解。


### 做法1：

  暴力枚举仙人掌，可以过第一个 subtask1。说不定加点剪枝可以过 subtask2。

### 做法2：

  考虑把度数序列中所有元素放进一个 multiset，可以发现这样合法的 multiset 非常少，而每一个合法的 multiset 对应的所有的度数序列都是合法的。
  所以可以用园方树进行 dp，这样可以过 subtask1,subtask2。或许可以过 subtask3。

### 做法3：

  对于一棵树的情况，只要所有点度数都至少为 $1$ 且和为 $2n-2$ 即可，所以答案直接可以用组合数算。

### 做法4：

  对于 $n=m$ 的情况，发现只要度数为 $1$ 的点不超过 $n-2$ 即可，所以直接组合数算。

### 做法5：

  考虑什么情况下仙人掌能构造出来。
  定义一个函数

$f(n)=\lbrack n \mod 2=0 \rbrack (\frac{3}{2}n-2)+\lbrack n \mod 2=1\rbrack (\frac{3}{2}(n-1))$

即 $n$ 个点仙人掌边数的上界。
 可以发现当度数均为偶数时，度数序列合法当且仅当边数（度数和/2）$m$ 满足 $n\le m\le f(n)$。

大致证明如下：
 如果边数不在这个范围内，显然不合法。
 如果度数和正好等于 $2n$，那么可以直接连一个大环。
 否则一定存在 $3$ 个点使得他们度数和大于 $6$，那么可以将这三个点连一个环，然后视为缩成一个点。
 都是偶数的情况可以把再连的环边集中到一个点上。

那么之前的条件依然满足，问题变成了一个形式相同，规模更小的子问题，可以归纳证明。
 对于存在奇数的情况，可以发现如果合法那么一定存在一种不连环的方案使得把它缩点之后变成全是偶数的情况，且在偶数的情况下合法。

那么消奇数的过程每连一条边就相当于度数和减少 $2$，节点数减少 $1$，可以发现我们只需要使这样的边连得尽量少。那么可以奇数的点两两连边，但是可以发现，如果度数为 $1$ 的点特别多可能会出问题，因为消完之后出现度数为  $0$ 的点了，这时候我们只能把度数为 $1$ 的点两两挂到度数大的偶数点上了。
 所以度数序列是否合法只和点数，度数和，奇数度数点的个数，度数为 $1$ 的点的个数有关，可以直接 dp 加点优化，可以过 subtask1,2,3，可能能过 subtask4。

### 做法6：

  用组合数优化做法5，可以直接AC。
  
### remark:
subtask7 出题人暂时想不到特殊做法,如果又会做法的可以私信出题人。

### Code
```cpp
#include <cstdio>
#include <algorithm>
#define mo 998244353
using namespace std;
int C[5005][5005];
bool check(int n, int m, int a, int b) {
    if (m == n - 1)
        return 1;
    if (a > b)
        m -= a, n -= a;
    else
        m -= (a + b) >> 1, n -= (a + b) >> 1;
    if (m < n)
        return 0;
    if (m > (n - 1) / 2 * 3 + (n - 1) % 2)
        return 0;
    return 1;
}
int main() {
    int cas;
    scanf("%d", &cas);
    C[0][0] = 1;
    for (int i = 1; i <= 5000; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mo;
    }
    while (cas--) {
        int n, m;
        scanf("%d%d", &n, &m);
        if (m > (n - 1) / 2 * 3 + (n - 1) % 2) {
            puts("0");
            continue;
        }
        if (n == 1) {
            puts("0");
            continue;
        }
        if (n == 2) {
            if (m == 1)
                puts("1");
            else
                puts("0");
            continue;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= n - i; j++) {
                if (i + j * 3 > m + m)
                    continue;
                if (!check(n, m, i, j))
                    continue;
                int m1 = m + m - i - j, n1 = n - i;
                if (m1 & 1)
                    continue;
                ans = ((long long)C[m1 / 2 - 1][n1 - 1] * C[n][n1] % mo * C[n1][j] + ans) % mo;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```
注：在此给出验题人的代码。

---

## 作者：CTime_Pup_314 (赞：5)

upd 20210106 : 感谢 @wlzhouzhuan 的 hack，原题解的问题是在实现的时候没有特判 $n=l$ 的情况导致不合法，现已改正。


这道题考完之后一直也没题解，蒟蒻就自己找了些资料，一知半解地写了这道题，主要参考 [NERC2019 C.Cactus Revenge](https://neerc.ifmo.ru/archive/2019/nerc-2019-tutorial.pdf) 和 [Cactus graph realization of degree sequence](http://www.secmem.org/blog/2019/12/15/cactus-realization/)，接下来的事情也主要复读这两个资料的

我们在之后的讨论中设度数序列为 $d$，图的点集大小为 $n$，边集大小为 $m$，首先有个很明显的性质即

$$
\sum_{i=1}^nd_i=2m
$$

首先考虑树的情况，树的情况很好猜，一个度数序能构成树的充要条件即 

$$
\sum_{i=1}^nd_i=2(n-1)\land \forall i,d_i\ge1
$$

考虑归纳证明，首先 $n=2$ 是 $d_1=d_2=1$ 两者互相连边即可，结论显然成立

对于 $n>2$，若 $\forall i,d_i\ge2$，则 $\sum_{i=1}^nd_i\ge2n$ 所以一定有 $j$ 满足 $d_j=1$，我们将 $j$ 与剩下任意一个 $k,d_k\ge2$ 连边，将 $d_j$ 和 $d_k$ 减 $1$，将 $j$ 删去，得到新的度数序 $d'$，那么由于 $d'$ 是可以构成树的，所以 $d$ 也可以

接着我们考虑边仙人掌的情况

我们任取图的一个生成树，每条非树边都仅代表一个环，所以环数 $c$ 显然满足 
$$
    c=m-(n-1)\in[0,\lfloor\frac{n-1}{2}\rfloor]
$$

若度数都为偶数，分两种情况，都为 $2$ 时，我们只需要构成一个大环即可，否则我们其中一定存在相异的 $u$ 和 $v$ 满足 $d_u=d_v=2$（可以用树的反证法说明)，我们令 $u$ 和 $v$ 与另一个 $w,d_w\ge4$ 构成一个三元环，与树同理构造出 $d'$，这是 $d'$ 满足 $c-1\le\lfloor\frac{n-3}{2}\rfloor$，于是可以归纳证明

若度数不全为偶数，则显然奇数个数为偶数并且我们需要找到更强的约束条件，考虑割边的个数为 $b$，奇数个数为 $o$，叶子个数为 $l$，对于 $b$，满足 $b\ge\max(\frac{o}{2},l)$，所以对 $c$ 有更强的约束为 

$$
c\le\lfloor\frac{n-1-\max(\frac{o}{2},l)}{2}\rfloor\le\lfloor\frac{n-1-b}{2}\rfloor
$$

首先对于一些平凡的情况，若序列满足上述条件即可构造出仙人掌，对于剩下的分两种情况考虑当 $l\ge1$ 时我们从度数最大的点 $u$ 向叶子 $v$ 连边，构造出 $d'$ 这时 $d'$ 满足 $c\le\lfloor\frac{n-1-\max(\frac{o-1-k}{2},l-1)}{2}\rfloor,k\le1$ 成立，我们从度数最大的点 $u$ 向度数最小的 $v$ 和 $w$ 构成三元环，与上面同理可证成立

所以我们就得到判断度数序列是否可以构成仙人掌的条件

计数就很简单了，我们考虑枚举 $o$ 和 $l$，用组合数计算出不定方程 
$$
\sum_{i=1}^nd_i=2m
$$

其中满足有 $o-l$ 个 $d_i$ 不小于 $3$ 且为奇数，$l$ 个 $d_i$ 为 $1$，$n-o$ 个 $d_i$ 为不小于 $2$ 且为偶数的解的方案数

这里我不太会用隔板法算，所以用生成函数暴力算很显然我们要求出的就是

$$
\binom{n}{o}\binom{o}{l}[x^{2m-l}](\frac{1}{1-x^2}-1)^{n-o}(\frac{x}{1-x^2}-x)^{o-l}
$$

将后面的多项式展开就不多赘述了

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
typedef long long int64;
inline int read(int f = 1, int x = 0, char ch = ' ')
{
    while(!isdigit(ch = getchar())) if(ch == '-') f = -1;
    while(isdigit(ch)) x = x*10+ch-'0', ch = getchar();
    return f*x;
}
const int N = 6e3+5, P = 998244353;
int t, n, m, c; int64 C[N][N], ans;
int main()
{ 
    for(int i = 0, n = 6e3; i <= n; ++i)
    {
        C[i][0] = 1;
        for(int j = 1; j <= i; ++j)
            C[i][j] = (C[i-1][j-1]+C[i-1][j])%P;
    }
    t = read();
    while(t--)
    {
        n = read(), m = read(), c = m-(n-1), ans = 0;
        if(0 <= c&&c <= (n-1)/2) 
            for(int o = 0; o <= n; o += 2)
                for(int l = 0; l <= o; ++l)
                {
                    int b = max(o/2, l);
                    if(c <= (n-1-b)/2) 
                        ans = (ans+C[n][o]*C[o][l]%P*(n == l&&2*m == o?1:C[(2*m-o)/2-1][n-l-1]))%P;
                }
        printf("%lld\n", ans);
    }
    return 0;
}
```

这道题应该属于图的可视化问题，这类问题常用这样的归纳证明，欲了解更多可以参照[Graph realization problem](https://en.wikipedia.org/wiki/Graph_realization_problem) 或这道题 [CF1091E](https://www.luogu.com.cn/problem/CF1091E)

---

## 作者：Thinking (赞：1)

首先研究一下subtask 5怎么搞。

手玩一下不难发现：满足总和为$2m-2$且每个数不小于1的数列都是满足要求的。这就给了我们启发：可不可以直接找出度数序列数量呢？

接下来解决一个问题：$n$个结点的仙人掌最多有几条边？

不难发现，所有包含点数大于4个的环都是不优的，例如5个点的环可以改成6条边的两个环：

![](https://cdn.luogu.com.cn/upload/image_hosting/gxaijc1o.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样就可以得到，$n$为奇数时，$m=\frac{3}{2}(n-1)$：

![](https://cdn.luogu.com.cn/upload/image_hosting/6cz4nmrq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

$n$为偶数时，$m=\frac{3}{2}n-2$：

![](https://cdn.luogu.com.cn/upload/image_hosting/r3xb230q.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

同时，不难发现，若所有结点的度数均为偶数，这样的仙人掌必定存在（找出度数最大的3个点，连一个环，缩成一个点，一路执行下去就可以了）

对于奇数点，我们发现，把奇数点像下图一样两两配对，就可以转化到偶数的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/9dv7rmsk.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

（合并两个蓝点，就转化为第二个图）

不过这样有例外：对于度为1的点，我们不能另找一个度为1的点配对（不然就不连通了），只能找一个度更大的奇数点或把它拼到偶数点上去。

那么，结果只跟$n$，$m$，1点个数$c_1$，奇数点个数$c_{odd}$有关，直接DP是$O(n^4)$的，考虑优化求所有结点的度数均为偶数的序列个数的部分。

把每个点的度除以2，那么就变成了把$m$个无差别的小球放入$n$个无差别的口袋，每个口袋至少有一个球的方案数，依据隔板法，答案为$C^{n-1}_{m-1}$。

对于原问题，我们首先求出$n'=n-c_1,m'=m-\frac{c_1+c_{odd}}{2}$的全为偶数的方案数，然后在$n'$个中找$c_{odd}$个变成奇数（方案数$C^{c_{odd}}_{n'}$），再加上$c_1$个度为1的点（方案数$C^{c_1}_{n}$），这样就可以$O(n^2)$计算啦

```cpp
#include<cstdio>
#define For(i,A,B) for(i=(A);i<=(B);++i)
typedef long long ll;
const int mod=998244353;
int f[3005],g[3005];
void exgcd(int a,int b,int &x,int &y){
	if(!b){x=1;y=0;}
	else{
		exgcd(b,a%b,y,x);
		y-=a/b*x;
	}
}
inline int inv(int a){
	int x,y;
	exgcd(a,mod,x,y);
	return x<0?x+mod:x;
}
inline int C(int m,int n){return m<=n?(ll)f[n]*g[m]%mod*g[n-m]%mod:0;}
inline int maxm(int n){return n&1?(n-1>>1)*3:(n>>1)*3-2;}
inline bool check(int n,int m,int c1,int co){  //检查转化后是否是合法情况
	if(c1>co){n-=c1;m-=c1;}  //1点太多，只能去和偶数点配对
	else{n-=c1+co>>1;m-=c1+co>>1;}
	return m>=n-1&&m<=maxm(n);
}
int main(){
	int T,n,m,nn,mm,i,j,ans;
	scanf("%d",&T);
	f[0]=f[1]=g[0]=g[1]=1;
	For(i,2,2997)f[i]=(ll)f[i-1]*i%mod;
	g[2997]=inv(f[2997]);
	for(i=2996;i>1;--i)g[i]=(ll)g[i+1]*(i+1)%mod;
	while(T--){
		scanf("%d%d",&n,&m);
		if(m<n-1||m>maxm(n)){
			puts("0");
			continue;
		}
		ans=0;
		For(i,0,n-1)
			For(j,0,n-i)if(i+j*3<=(m<<1))if(!(i+j&1)&&check(n,m,i,j)){
				nn=n-i;mm=m-(i+j>>1);
				ans=(ans+(ll)C(nn-1,mm-1)*C(i,n)%mod*C(j,nn))%mod;
			}else;
			else break;
		printf("%d\n",ans);
	}
	return 0;
}
```


---

