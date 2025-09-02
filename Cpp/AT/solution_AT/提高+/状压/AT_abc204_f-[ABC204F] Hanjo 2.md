# [ABC204F] Hanjo 2

## 题目描述

有一个长 $H$（$1≤H≤6$）米，宽 $W$ 米（$1≤W≤10^{12}$）的房间，现在用两种地板砖铺地板：长 $2$ 米，宽 $1$ 米的长方形地板砖和边长为 $1$ 米的正方形地板砖。

长方形地板砖可以旋转成长 $1$ 米，宽 $2$ 米的长方形地板砖。

求铺满这个房间的总方案数。

## 样例 #1

### 输入

```
2 2```

### 输出

```
7```

## 样例 #2

### 输入

```
3 3```

### 输出

```
131```

## 样例 #3

### 输入

```
5 100```

### 输出

```
379944232```

# 题解

## 作者：泥土笨笨 (赞：8)

数据范围中地板的宽度 $H \leq 6$ ，这提示我们可以状态压缩。而 $W \le 10^{12}$ ，这个数据范围显然不能线性递推，这提示我们要用矩阵快速幂加速DP。于是思路就很明显了。

# 状态压缩

先考虑状态压缩，对于每一列，一共有 $H$ 个格。每一个格都可以选择用地砖铺，还是暂时不铺。注意这里选择暂时不铺是可行的，因为下一列可以用一个长方形的地砖横着铺把这里的空位补上。这样我们用数字 $1$ 表示铺，用数字 $0$ 表示不铺，每一列的状态就可以用一个 $H$ 位二进制数字表示。

当然，对于每个状态，可能有多重不同的铺法。比如 `110` 这个状态，可以用一个竖着的长方形铺，然后空一格。也可以用两个正方形铺，然后空一格。因此，对于每种状态，我们还需要记录这种状态可以有多少种铺法。这里比较简单的方式就是直接 `dfs` 枚举统计。

这个 `dfs` 代码实现比较简单，代码示例如下：

```cpp
//首先dfs枚举状态以及每个状态的方案数
void dfs(ll step, ll last, ll status) {
    //step表示目前在枚举状态的第几位，last表示上一个状态是不是竖着1*2的
    if (step == h) {
        if (last == 0) {
            //到走多一步以后，last必须是0，否则就多伸出来一块了
            cnt[status]++;
        }
    } else {
        if (last == 1) {
            //这里被上一块覆盖了
            dfs(step + 1, 0, status << 1 | 1);//右边直接补一个1，然后继续
        } else {
            dfs(step + 1, 0, status << 1);//这里不放
            dfs(step + 1, 0, status << 1 | 1);//放一个1*1的
            dfs(step + 1, 1, status << 1 | 1);//放一个2*1的
        }
    }
}
```

# 状态转移矩阵

假设目前我们考虑到前 $i-1$ 列，其中前 $i-2$ 列必须都全部铺满，第 $i-1$ 列取到状态 $s$ 。并且令 $ss = 2^H$ ，那么当前这一列有 $ss$ 种状态，我们如果知道每种状态的取值，就可以用一个长度为 $ss$ 的行向量 $X$ 分别表示状态 $0,1,2,...,ss-1$的方案数。

如果已知前 $i-1$ 列每种状态的方案数，如何求前 $i$ 列的行向量呢？我们想预处理出来一个状态转移矩阵 $A$ ，其中 $A_{xy}$ 表示在前一行中取状态 $x$ ，下一行中取状态 $y$ ，方案数转移过来要乘的系数。如果前一行 $x$ 中状态不能转移到下一行的状态 $y$（这种情况是 $x$ 中是 $0$ 的位置， $y$ 中也是 $0$ ，也就是说第 $i$ 列不能横着放一个长方形去补前一列的空，这样最后结果里就有空位置了，这样是不合法的），这时候系数就是$0$。

根据刚才括号里的分析，x中空格的位置，y中必须铺。但是这里要求y要横着铺长方形，也就是其实y的方案数等价于这里也不铺的情况。因为一个横着的长方形在我们一开始预处理的时候是不考虑的。所以系数其实就是在y中把所有x是0的位置也修改为0的状态的初始方案数。这样我们可以把A矩阵计算出来。

一旦A矩阵计算出来，只要用$X \times A$就可以得到下一列的状态了，这样最终结果其实就是初始行向量 $X$ 乘以 $A$ 的 $n-1$ 次幂。这样用矩阵快速幂把 $A$ 的 $n-1$ 次幂求出来，最后直接用初始行向量乘这个矩阵的最后一列，计算出最后状态为 $ss-1$ 的方案数即为答案。

# 代码
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
typedef long long ll;
const ll MAXN = (1 << 6) + 5;
const ll MOD = 998244353;

struct Matrix {
    ll n, m, d[105][105];//n表示行，m表示列

    //矩阵清零
    void clear() {
        memset(d, 0, sizeof(d));
    }

    //生成单位矩阵，仅限方阵n和m相等的时候
    void identity() {
        clear();
        for (int i = 0; i < n; ++i) {
            d[i][i] = 1;
        }
    }

    Matrix(ll n, ll m) : n(n), m(m) {}
};

Matrix mul(const Matrix &a, const Matrix &b) {
    Matrix c(a.n, b.m);
    c.clear();
    for (int k = 0; k < a.m; ++k) {//k本来应该是最内层循环，拿到外面也可以优化一些时间
        for (int i = 0; i < a.n; ++i) {
            for (int j = 0; j < b.m; ++j) {
                c.d[i][j] += (a.d[i][k] * b.d[k][j]) % MOD;
                c.d[i][j] %= MOD;
            }
        }
    }
    return c;
}

Matrix pow(Matrix &a, ll p) {
    Matrix result(a.n, a.n);
    result.identity();
    Matrix base = a;
    while (p) {
        if (p & 1) {
            result = mul(result, base);
        }
        base = mul(base, base);
        p >>= 1;
    }
    return result;
}

//对于每一列，铺用1表示，不铺用0表示，对于每个状态压缩成二进制
ll cnt[MAXN];//每个状态的方案数
ll h, w;//输入的h和w
ll ss;//最大方案数

//首先dfs枚举状态以及每个状态的方案数
void dfs(ll step, ll last, ll status) {
    //step表示目前在枚举状态的第几位，last表示上一个状态是不是竖着1*2的
    if (step == h) {
        if (last == 0) {
            //到走多一步以后，last必须是0，否则就多伸出来一块了
            cnt[status]++;
        }
    } else {
        if (last == 1) {
            //这里被上一块覆盖了
            dfs(step + 1, 0, status << 1 | 1);//右边直接补一个1，然后继续
        } else {
            dfs(step + 1, 0, status << 1);//这里不放
            dfs(step + 1, 0, status << 1 | 1);//放一个1*1的
            dfs(step + 1, 1, status << 1 | 1);//放一个2*1的
        }
    }
}

//初始化转移矩阵
//假设一个行向量表示只考虑前i-1列，前i-2列全铺满，并且第i-1列分别取状态0到ss-1的方案数
//用这个行向量*转移矩阵，即可得到只考虑前i列，前i-1列全铺满，并且第i列分别取状态0到ss-1的方案数的行向量
Matrix init() {
    Matrix r(ss, ss);
    for (int i = 0; i < ss; ++i) {
        ll mask = i ^ ((1 << h) - 1);//与h个1异或，找到i当中所有是0的位置
        for (int j = 0; j < ss; ++j) {
            //对于i当中所有是0的位置，j当中必须都是1，这样用一个横着的1*2的把前一行欠的0补上
            if ((mask & j) == mask) {
                //这时候相当于j中这些1已经被占用了，方案数和把这些1扣掉是一样的
                r.d[i][j] = cnt[i & j];
            }
        }
    }
    return r;
}

int main() {
    cin >> h >> w;
    ss = 1 << h;
    dfs(0, 0, 0);
    Matrix t = init();//初始化一个转移矩阵，t[x][y]表示从状态x转移到状态y需要乘的系数
    t = pow(t, w - 1);
    //最后结果是ss-1状态的合法，等于初始行向量乘t矩阵的k-1次幂的最后一列
    ll ans = 0;
    for (int i = 0; i < ss; ++i) {
        ans = (ans + cnt[i] * t.d[i][ss - 1] % MOD) % MOD;
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：CaiZi (赞：6)

数据范围已经把正解告诉你了。

以下记 $n=H,m=W$。

考虑状压 DP，设 $f_{i,S}$ 表示处理第 $1\sim i-1$ 列全部填完，且第 $i$ 列的状态为 $S$ 的方案数。

我们首先需要知道一个 $S$ 有多少种铺法可以铺满，显然某些 $0$ 把 $1$ 分割成若干连续段，每个长度为 $l$ 的 $1$ 的连续段可以有 $g_{l+1}$ 种方案，其中 $g_{l+1}$ 为斐波那契数列第 $l+1$ 项，相乘起来就好了。记这个数为 $C_S$。

考虑如何从 $f_{i-1,T}$ 转移到 $f_{i,S}$。我们发现，对于 $T$ 中为 $0$ 的位置，必需放置一块横向的 $1\times2$ 的块，因为如果你放置一块 $1\times1$ 的块，会与前面的状态重合，所以对应位置 $S$ 必需为 $1$。因此只有 $T$ 和 $S$ 中均为 $1$ 的位置才能产生贡献，其贡献为 $C_{T\And S}$。因此可以列出转移方程：
$$f_{i,S}=\sum_{T|S=2^n-1}(f_{i-1,T}\times C_{T\&S})$$
最终答案即为 $f_{m,2^n-1}$。

发现这个东西是一个线性递推形式，使用矩阵快速幂加速即可。

时间复杂度 $O(8^n\log m)$。

代码展示：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
int n,m,q,s,c[64],g[]={1,1,2,3,5,8,13};
struct matrix{
	int num[64][64];
	inline matrix operator * (matrix x){
		matrix y;
		for(int i=0;i<=q;i++){
			for(int j=0;j<=q;j++){
				for(int k=0;k<=q;k++){
					y.num[i][k]+=num[i][j]*x.num[j][k];
					y.num[i][k]%=mod;
				}
			}
		}
		return y;
	}
	inline int* operator [] (int x){
		return num[x];
	}
	inline matrix(){
		memset(num,0,sizeof(num));
	}
}a,b;
signed main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin>>n>>m;
	q=(1<<n)-1;
	for(int i=0;i<=q;i++){
		s=0;
		c[i]=1;
		for(int j=n-1;j>=0;j--){
			if(i>>j&1){
				s++;
			}
			else{
				c[i]*=g[s];
				s=0;
			}
		}
		c[i]*=g[s];
	}
	for(int i=0;i<=q;i++){
		for(int j=0;j<=q;j++){
			if((i|j)==q){
				a[i][j]=c[i&j];
			}
		}
	}
	for(int i=0;i<=q;i++){
		b[i][i]=1;
	}
	while(m){
		if(m&1){
			b=b*a;
		}
		a=a*a;
		m>>=1;
	}
	cout<<b[q][q];
	return 0;
}
```

---

## 作者：Cure_Wing (赞：3)

[AT_abc204_f [ABC204F] Hanjo 2](https://www.luogu.com.cn/problem/AT_abc204_f)

### 做这题你需要掌握的

- [矩阵乘法](http://oi-wiki.com/math/linear-algebra/matrix/#%E7%9F%A9%E9%98%B5%E4%B9%98%E6%B3%95)/矩阵快速幂

### 思路

别问我为什么要掌握上述内容，讲的时候就知道了。

首先我们要想到一个朴素的 dp：设 $f_{i,j}$ 表示铺到第 $i$ 行，其中 $1\sim i-1$ 行全部铺满，第 $i$ 行铺设状态为 $j$（第 $p$ 位上为 $1$ 表示已铺，为 $0$ 表示暂时未铺）。转移很好想，枚举状态 $j,k$，执行 $f_{i-1,j}\to f_{i,k}\times c_{j,k}$，其中 $c_{j,k}$ 表示铺设状态 $j$ 变为铺设状态 $k$ 的方案数。

显然 $c$ 是可以预处理的：对于同一行上相邻的两个方格，显然不能都不铺（此时 $c_{j,k}=0$），如果有一个不铺那么后一格的方案是确定的（用 $1\times2$ 的和不铺），否则后一格有两种选择（用 $2\times1$ 或 $1\times1$）。我们用 $a_i$ 表示这一格是否有两种选择，再设 $g_i$ 表示前 $i$ 行的铺设方案数，显然有：

$g_i=\begin{cases}g_{i-1}&&a_{i-1}=0\;\text{or}\;a_{i}=0\\g_{i-1}+g_{i-2}&&\text{otherwise}\end{cases}$

初始 $g_0=1$ 我想不需要多提。

然后 $c_{j,k}$ 就应当等于此时处理出的 $g_h$。

但是这样时间复杂度是 $O(4^h\times h+2^h\times w)$，肯定爆炸。

我们把 $f_i$ 看成一个 $2^h$ 维的向量，那么 $c$ 就是每次它所做的线性变换，$f_{i+1}$ 也就是线性变换的结果。于是我们可以这样看待 $f_w$：

$f_w=c\times f_{w-1}=c^2\times f_{w-2}=\cdots=c^{w-1}\times f_1$

$c^{w-1}$ 是个标准的矩阵快速幂，于是乎我们只要计算 $f_1$ 就可以了（你会发现这个限制条件和 $c$ 是差不多的，那样算就可以了）。

时间复杂度降为 $O(4^hh+8^h\log_2w)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
constexpr int N=7,H=70,p=998244353;
int h,f[N];
long long w;
bool a[N];
struct A{
	int a[H][H],n,m;
	inline A(int x=0,int y=0){memset(a,0,sizeof(a));n=x;m=y;}
	inline int* operator[](int i){return a[i];}
}g,ans;
inline A operator*(A a,A b){//矩阵乘法/快速幂
	A c(a.n,b.m);
	for(int i=1;i<=a.n;++i)
		for(int j=1;j<=b.m;++j)
			for(int k=1;k<=a.m;++k)
				c[i][j]=(c[i][j]+1ll*a[i][k]*b[k][j]%p)%p;
	return c;
}
inline A qpow(A a,long long b){A c(a.n,a.m);for(int i=1;i<=a.n;++i) c[i][i]=1;for(;b;b>>=1,a=a*a) if(b&1) c=c*a;return c;}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>h>>w;f[0]=1;ans=A(1<<h,1);g=A(1<<h,1<<h);
	for(int i=0;i<(1<<h);++i){//预处理f_1
		for(int j=1;j<=h;++j) a[j]=(i>>j-1)&1;
		for(int j=1;j<=h;++j)
			if(a[j]&&a[j-1]) f[j]=f[j-1]+f[j-2];
			else f[j]=f[j-1];
		ans[i+1][1]=f[h];
	}
	for(int i=0;i<(1<<h);++i)
		for(int j=0;j<(1<<h);++j){//预处理c
			bool vis=1;
			for(int k=1;k<=h;++k){
				bool k1=(i>>k-1)&1,k2=(j>>k-1)&1;
				if(!k1&&!k2){vis=0;break;}
				a[k]=k1&&k2;
			}
			if(!vis) continue;
			for(int k=1;k<=h;++k)
				if(a[k]&&a[k-1]) f[k]=f[k-1]+f[k-2];
				else f[k]=f[k-1];
			g[i+1][j+1]=f[h];
		}
	ans=qpow(g,w-1)*ans;
	cout<<ans[1<<h][1];//答案显然是f[w][1<<h]，因为最后一行必须填满
	return 0;
}
```

---

## 作者：Day_Tao (赞：2)

### Sol

首先抛开题目，考虑 $H=1$ 的情况，设 $f_{1,i}$ 为第 $1$ 行到了第 $i$ 列的方案数，那么就容易得到：

$$\begin{cases}f_1 =1,f_2=2 \\ f_i = f_{i-1}+f_{i-2}\end{cases}$$

用矩阵快速幂优化即可。

---

接下来考虑 $N\neq 1$。

如果只能放小正方形和横着的长方形，那么到了第 $i$ 列的答案就是 $N\times f_i$。但是现在还要考虑竖着的长方形，如果转移方程的第一维还是设为横向的话那肯定就比较麻烦了，所以我们设 $g_{i}$ 表示到了第 $i$ 列的方案数。

接着考虑设第二维的状态。现在的问题就成了如何处理横着的长方形，这其实可以看做在第 $i-2$ 列及以前整个矩形都是完整的，假设这之前还有空缺，那么可以加入小正方形或者长方形来转移到 $g_{i-1}$。现在矩形的样子应该是：在 $i-2$ 列之前都是完整的，第 $i-1$ 列是参差不齐的。考虑第 $i-1$ 列的状态，由于行数很小，$W$ 最多只有 $6$，所以总状态个数就是 $2^6=64$ 种。所以第二维我们就能设成是哪一种状态，即 $g_{i,j}$。

然后考虑转移。从 $i-1$ 转移到 $i$，那么就必须要保证 $i-1$ 的全部空缺都被填满，再在第 $i$ 列中填一部分。对于 $i-1,j$ 没被填的情况有两种选择，要么填两个小正方形，要么填一个横着的长方形。但是如果是前者的话，在填入一个小正方形后状态将会变成在第 $i-1$ 列的另一个状态，会与这个状态算重复，所以只考虑加入一个长方形。而对于 $i-1,j$ 已经被填过了的状态，那么就考虑在 $i,j$ 填一个正方形进行转移。

容易发现每次转移本质上都是一样的，是一次次的线性变换，所以只需要对上一次得到的 $g_{i,j}$ 对一个状态转移矩阵进行矩乘，再用矩阵快速幂优化即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define ls root << 1
#define rs root << 1 | 1
#define int long long
#define ull unsigned long long
const int INF = 0x7fffffff;
const int mod = 998244353;
const int MAX = 65;
const int f[]={1,1,2,3,5,8,13};
int w,n,m,res[MAX];
struct matrix
{
    int a[MAX][MAX];
    matrix()
    {
        memset(a,0,sizeof(a));
    }
    inline matrix operator*(const matrix &Day_Tao) const
    {
        matrix c;
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
                for(int k=0;k<m;k++)
                    c.a[i][j]+=a[i][k]*Day_Tao.a[k][j]%mod,c.a[i][j]%=mod;
        return c;
    }
}G,A; // G 表示状态转移矩阵，从状态 i 转移到状态 j 的方案数
inline matrix qpow(matrix a,int b)
{
    b--;
    matrix res=a;
    for(;b;b>>=1,a=a*a)
        if(b&1)
            res=res*a;
    return res;
}
signed main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    scanf("%lld%lld",&n,&w);
    m=1<<n;
    for(int i=0;i<m;i++) // 二进制位为 0 表示不填，res 统计方案数
    {
        int x=0;
        res[i]=1;
        for(int j=0;j<n;j++)
            if((i>>j)&1)
                x++;
            else res[i]*=f[x],x=0; // 累乘填的方案数
        res[i]*=f[x];
    }
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++) // 枚举两列的状态
            if((i|j)==m-1) // 不能从空的转移到空的，不符合前面推出的转移
                G.a[i][j]=res[i&j]; // 空的转移到非空要填一个长方形，非空转移到空的不用填
                                    // 两者的方案数都只有一种，交集表示非空转移到非空，这才有多种方案的贡献
    A.a[m-1][0]=1; // 初始矩阵
    A=qpow(G,w)*A;
    printf("%lld\n",A.a[m-1][0]);
    system("pause");
    return 0;
}
```
---
### END

---

## 作者：大眼仔Happy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc204_f)

# Easy Version

第一时间想到的是简单版。

显然 $H=1$ 的时候就是一个简单的递推了，加个矩阵快速幂即可。

那么 $H\ne 1$ 可以这么做吗？~~显然不行。~~

# Hard Version

不过 $H$ 还是挺小的，我们考虑一列一列做，就是状压 dp。设 $f_{i,S}$ 表示前 $i-1$ 列都被填满，第 $i$ 列的状态为 $S$ 的方案数。显然是 $f_{i,S}\to f_{i+1,T}$，中间还乘一个常数 ${\rm num}(S,T)$，表示前一行是 $S$，转移到后一行是 $T$ 的方案数。

- 注意的是这里 $S\to T$ 的时候不能改变第 $i$ 行（不然就是 $S'\to T$ 了），只能用 $1\times 2$（横着的长方形）来填。

发现这个东西可以滚掉 $i$ 这一维，常数也不随 $i$ 的变化而变化，然后就可以愉快的对 $\rm num$ 使用矩阵快速幂了。

考虑 $\rm num(S,T)$ 这个东西怎么去算。两列还是有点难算，那我们先算一列的，令其为 ${\rm cnt}(sta)$。如果前一列的状态 $S$ 和后一列的状态 $T$ 在某一位上面都是 $0$，那么 ${\rm num}(S,T)$ 就是 $0$，因为这一行没有被填所以会有空，不合法；否则 ${\rm num(S,T)}={\rm cnt}(S\cap T)$，这是因为相当于把 $S$ 中的 $0$ 要补上，$T$ 中对应的位置就必须要放一个横着的长方形，于是就是剩下的方案数。

最后的时间复杂度为 $O(N^3\log W)$。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,st,ed) for(int i=st;i<=ed;i++)
#define ROF(i,st,ed) for(int i=st;i>=ed;i--)
#define ll long long
const int N=1<<6,f[]={1,1,2,3,5,8,13};
const ll mod=998244353;
ll n,m,sz;ll cnt[N];
ll inline read()
{
	ll num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
struct Matrix
{
	ll M[N][N];
	Matrix(){memset(M,0,sizeof(M));}
	void reset(){FOR(i,0,sz)M[i][i]=1;}
	Matrix friend operator *(const Matrix A,const Matrix B)
	{
		Matrix res;
		FOR(i,0,sz)FOR(j,0,sz)FOR(k,0,sz)
			res.M[i][j]=(res.M[i][j]+A.M[i][k]*B.M[k][j])%mod;
		return res;
	}
}A,ans;
void print(Matrix a){FOR(i,0,sz){FOR(j,0,sz)printf("%lld ",a.M[i][j]);printf("\n");}}
Matrix qp(Matrix a,ll b){Matrix res;res.reset();while(b){if(b&1)res=a*res;a=a*a;b>>=1;}return res;}
void init()
{
	FOR(i,0,sz)
	{
		int s=0;cnt[i]=1;
		ROF(j,n-1,0)
		{
			if(i>>j&1)s++;
			else cnt[i]*=f[s],s=0;
		}
		cnt[i]*=f[s];
	}
	FOR(i,0,sz)FOR(j,0,sz)
		if((i|j)==sz)A.M[i][j]=cnt[i&j];
}
int main(){
	n=read();m=read();sz=(1<<n)-1;
	init();ans.M[sz][0]=1; 
	ans=qp(A,m)*ans;
	printf("%lld\n",ans.M[sz][0]);
	return 0;
}
```

# Optimization

一些奇技淫巧。

矩阵乘法时，将 $i,j,k$ 的顺序改成 $i,k,j$ 的顺序时可以优化常数，理由是 `A.M[i][k]` 的访问地址不变，而 `B.M[k][j]` 和 `res.M[i][j]` 也仅仅只是往下一个地址走。这比原来的跳着访问地址显然可以起到一定的优化。

---

## 作者：AKPC (赞：0)

状压 DP 矩阵快速幂优化板子题。

考虑 $W\leq10^5$ 的做法：

因为 $H$ 很小，考虑状压表示状态。设 $dp_{i,s}$ 表示前 $i-1$ 列全部被覆盖（$>i$ 列为右端的横长条无法覆盖到 $i-1$，故需要全部被覆盖），且第 $i$ 列状态是 $s$ 的方案数。

考虑怎么转移，设需要从 $dp_{i-1,s}$ 转移到 $dp_{i,t}$，那么容易发现 $dp_{i,t}$ 的值就是 $dp_{i-1,s}$ 乘上将第 $i-1$ 列涂满，第 $i$ 列涂成状态 $t$ 的方案数。不难发现，$s$ 中为 $0$ 的位置在 $t$ 中必须为 $1$（因为必须在这个位置放横长调，否则无法涂满 $i-1$ 列），如果不满足，那方案数就为 $0$；其他位置就任意涂竖长条或者正方体了，比较简单，说白了就是涂满 $s\operatorname{AND}t$ 这个状态对应列的方案数。枚举 $i,s,t$ 转移即可。

然后考虑 $W\leq10^{12}$：

当 $H=1$ 时，转移方程就是斐波那契，其存储的项是 $\begin{bmatrix}dp_i\\dp_{i-1}\end{bmatrix}$，转移矩阵为 $\begin{bmatrix}1&1\\1&0\end{bmatrix}$，其值是转移方程中每项的系数。

而当 $H\neq1$ 时，考虑使用类似的构造方法，将 $s,t$ 放入矩阵，令转移矩阵为 $M$，那么构造 $M_{s,t}=f_{s\operatorname{AND}t}$ 即可。其中 $f_s$ 表示涂满列状态 $s$ 的方案数。那么，预处理出 $f$，接着使用矩阵快速幂解决这个问题即可。

[code](/paste/gapzmh6z)。

---

