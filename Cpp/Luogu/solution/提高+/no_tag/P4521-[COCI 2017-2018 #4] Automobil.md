# [COCI 2017/2018 #4] Automobil

## 题目描述

米尔科在他的车后座上发现了一个有 N 行 M 列的矩阵。矩阵的第一行由数字 1, 2, … M 组成，第二行由数字 M+1, M+2, … 2⋅M 组成，依此类推，直到第 $N$ 行，其由数字 (N-1)⋅M + 1, (N-1)⋅M + 2, … N⋅M 组成。

例如，对于 N = 3 和 M = 4：

| - | - | - | - |
| :----------: | :----------: | :----------: | :----------: |
| **1** | **2** | **3** | **4** |
| **5** | **6** | **7** | **8** |
| **9** | **10** | **11** | **12** |

这样的矩阵对他来说不够有趣，所以他选择了一行或一列 K 次，并将其值乘以一个非负整数。

自然地，现在他想知道矩阵中所有值的和。由于这个和可能非常大，米尔科将对其取模 $10^9 + 7$。帮助米尔科回答这个问题。

## 说明/提示

在总共价值 50 分的测试用例中，将满足 1 ≤ N, M ≤ 1000。

**第一个测试用例的说明：** 在将第二行乘以 4，第四列乘以 1，第三行乘以 2，再次将第二行乘以 0 之后，最终矩阵如下所示：

| - | - | - | - |
| :----------: | :----------: | :----------: | :----------: |
| **1** | **2** | **3** | **4** |
| **0** | **0** | **0** | **0** |
| **18** | **20** | **22** | **24** |

最终矩阵中元素的和为 1 + 2 + 3 + 4 + 0 + 0 + 0 + 0 + 18 + 20 + 22 + 24 = 94。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3 4 4
R 2 4
S 4 1
R 3 2
R 2 0```

### 输出

```
94```

## 样例 #2

### 输入

```
3 1 1
S 1 4
```

### 输出

```
24```

## 样例 #3

### 输入

```
2 4 4
S 2 0
S 2 3
R 1 5
S 1 3```

### 输出

```
80```

# 题解

## 作者：ikka (赞：4)

### Description

给你一个大小为$n\times m$的矩阵，矩阵中第$i$行第$j$列的数为$(i-1)m+j$，给你$k$次操作，每次操作指定某一行或某一列乘上一个非负整数，求$k$次操作后，矩阵中所有数的和，对$10^9+7$取模。

$n,m\leq 10^6,k\leq 10^4$

### Solution

首先注意到$n,m$都很大，直接算出这个矩阵是不可能的。因为这题只有对一整行或一整列的操作，所以可以考虑对一整行和一整列计算答案。

然后可以注意到，只需要求出最后矩阵中数字的和，所以这个操作的顺序是无所谓的，可以把操作排序，先处理行操作，然后处理出每一列的数字和，记作$f[i]$，这样对于后面的列操作就成了在$f[i]$上的一个一维的问题，这个复杂度就可以接受。

然后考虑如何处理行操作。可以把每一行乘的数算出来，记作$v[i]$，然后就可以把$f[i]$算出来，不过朴素的算法算$f[i]$还是$O(nm)$的，要搞一个优化。

原矩阵的一行中，后一个数等于前一个数$+1$，考虑到这个性质，你一拍大腿，发现这个$f[i]$是可以递推的！根据小学所学的乘法分配律，显然我们可以得到$f[i] = f[i-1] + \sum_{i=1}^{n} v[i]$，后面的这个和式可以$O(n)$预处理得到，$f[1]$也可以$O(n)$计算，所以，$f[i]$就可以$O(m)$递推出来了。

这之后你就可以对着一维问题乱搞了。

时间复杂度$O(n)$。

## Code

``` cpp
#include <cstdio>
#include <algorithm>
const int maxn = 1000010;
const int maxk = 1010;
const int mod = 1000000007;

int inline pls(int a, int b) { int m = a + b; return m < mod ? m : m - mod; }
int inline dec(int a, int b) { int m = a - b; return m < 0 ? m + mod : m; }
int inline mul(int a, int b) { return 1ll * a * b % mod; }

struct qry {
  int o, x, y;
  bool operator < (const qry &rhs) const {
    return o < rhs.o;
  }
} a[maxk];

int val[maxn], f[maxn];

int main() {
  static int n, m, k, x, y, s, ans; char opt[2];
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= k; ++i) {
    scanf("%s%d%d", opt, &x, &y);
    a[i] = (qry){*opt == 'S', x, y};
  }
  std::sort(a + 1, a + k + 1);
  for (int i = 1; i <= n; ++i) val[i] = 1;
  for (int i = 1; i <= k; ++i) {
    if (a[i].o) break;
    val[a[i].x] = mul(val[a[i].x], a[i].y);
  }
  for (int i = 1; i <= n; ++i) s = pls(s, val[i]);
  for (int i = 1; i <= n; ++i) f[1] = pls(f[1], mul(pls(mul(m, i - 1), 1), val[i]));
  for (int i = 2; i <= m; ++i) f[i] = pls(f[i - 1], s);
  for (int i = 1; i <= k; ++i) {
    if (!a[i].o) continue;
    f[a[i].x] = mul(f[a[i].x], a[i].y);
  }
  for (int i = 1; i <= m; ++i) ans = pls(ans, f[i]);
  printf("%d\n", ans);
  return 0;
}
```

---

## 作者：Reanap (赞：2)

题目非常显而易见，我们发现n方算法是过不了的，并且这个矩阵是无法完全储存的，所以我们可以考虑压缩它，把它压缩成一行进行操作。

根据交换律，我们可以分类操作，列操作很显而易见（直接乘上压缩后的数就可以了），行操作则需要对整行进行修改（即我们要算出这个压缩数列），复杂度仍是n方，仍然无法承受。

继续观察，我们发现在执行行操作时，该压缩数列必然等差，而公差就是每一行乘的倍数的和，所以我们只需要维护首项和公差就可以维护出整个数列，复杂度约为O(n + m)

见代码:

```cpp

#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 1e6 + 5;
LL mod = 1e9 + 7;
LL n , m , k;
LL tot = 0 , R[MAXN] , S[MAXN];
int main() {
	scanf("%lld %lld %lld" , &n , &m , &k);
	for (LL i = 1; i <= n; ++i) {
		tot = (tot + (i - 1) * m % mod + 1) % mod; // 维护首项
		R[i] = 1;
	}
	for (LL i = 1; i <= m; ++i) S[i] = 1;
	for (LL i = 1; i <= k; ++i) {
		char s = getchar();
		while(s != 'R' && s != 'S') s = getchar();
		LL x , y;
		scanf("%lld %lld" , &x , &y);
		if(s == 'S') {
			S[x] = S[x] * y % mod; // 先储存
		}
		else {
			tot = (tot + (y - 1) * R[x] % mod * ((x - 1) * m % mod + 1) % mod) % mod;
            //计算乘上这一行的第一个数对压缩数列每个数的影响
			R[x] = R[x] * y % mod;
		}
	}
	LL gc = 0;
	for (LL i = 1; i <= n; ++i) gc += R[i];//计算公差
	LL ans = 0;
	for (LL i = 1; i <= m; ++i) {
		ans = (ans + tot * S[i] % mod) % mod; // 统计答案
		tot = (tot + gc) % mod;
	}
	printf("%lld" , ans);
	return 0;
}

```

---

## 作者：lmgoat (赞：2)

可以把每行和每列要乘的因数在输入先算出来，存在两个个数组 *vr* , *vs* 里，然后算出如果不修改的答案 *ans* ，加出差值。对于行列交叉的点 *(i,j)* ，把其横纵坐标从在 vector 里，最后处理：算出不修改的值: $ a = (i - 1) * m + j $ 先减去算行、列时多加的值: $ b = a * (vr [i] -1)$ 、 $c=a * (vs[i]-1)$ ，加上实际上该加的值 $ d=(vr[i] * vs[j]-1)* a $ , 所以 $ans=ans+d-b-c$ 。

因为枚举了交叉点所以时间复杂度 $\Theta(k^2)$ 。

注意 *mod* ：只要有乘或者加就模

具体实现看代码:
```cpp
#include<bits/stdc++.h>
#define int long long//懒得区分int,long long不建议这么搞
#define reg register
using namespace std;
int mod=1000000007,ans,sr[1000005],ss[1000005],vr[1000005],vs[1000005];
int n,m,k;
struct node{
	int x,y;
};
vector<node>cf;
vector<int>ts,tr;
signed main()
{
	scanf("%lld%lld%lld",&n,&m,&k);
	for(reg int i=1;i<=n;i=-~i)ss[1]=(ss[1]+1+((i-1)*m+mod)%mod+mod)%mod;//算第一列
	for(reg int i=1;i<=m;i=-~i)
	{
		if(i>1)ss[i]=(ss[i-1]+n+mod)%mod;//算其他列
		sr[1]=(sr[1]+i+mod)%mod;//第一行
		vs[i]=1;//因为要乘，所以初始化1
	}
	for(reg int i=1;i<=n;i=-~i)
	{
		if(i>1)sr[i]=(sr[i-1]+(m*m+mod)%mod+mod)%mod;//算其他行
		ans=(ans+sr[i]+mod)%mod;//算不修改时的ans
		vr[i]=1;
	}
	char cc;int x,y;
	for(int i=1;i<=k;i=-~i)
	{
		cin>>cc;
		scanf("%lld%lld",&x,&y);
		if(cc=='R')vr[x]=(y*vr[x])%mod;//算行要乘的因数
		else vs[x]=(y*vs[x])%mod;//算列要乘的因数
	}
	for(reg int i=1;i<=n;i=-~i)
	{
		ans=(ans+(sr[i]*(vr[i]-1)+mod)%mod+mod)%mod;//加上行修改后的差值
		if(vr[i]!=1)tr.push_back(i);//把要交叉的点的横坐标加进vector
	}
	for(reg int i=1;i<=m;i=-~i)
	{
		ans=(ans+(ss[i]*(vs[i]-1)+mod)%mod+mod)%mod;//加上列修改后的差值
		if(vs[i]!=1)ts.push_back(i);//把要交叉的点的纵坐标加进vector
	}
	int a,b,c,d;
	for(reg int i=0;i<tr.size();i=-~i)
	{
		for(reg int j=0;j<ts.size();j=-~j)
		{
			x=tr[i],y=ts[j];
			a=(m*(x-1)+y+mod)%mod;//如果不修改的值
			b=((a*(vr[x]-1)+mod)%mod+mod)%mod;//算行时多加的值
			c=((a*(vs[y]-1)+mod)%mod+mod)%mod;//算列时多加的值
			d=(((a*(vr[x]*vs[y]%mod-1+mod)%mod))+mod)%mod;//实际上要加的值
			ans=(ans-b-c+d+mod)%mod;
		}
	}
	printf("%lld",(ans+mod)%mod); 
	return 0;
}
```


---

## 作者：strlen_s_ (赞：1)

## 分析

肯定不能把矩阵存下来，所以根据题目性质分析一下。

题目只要求出操作完后矩阵里每个数的和，这跟操作顺序没有关系。

所以先处理所有行，再处理所有链。

设 $f_i$ 表示操作完所有行上的操作后这一列的数之和,$mul_i$ 表示操作完所有行上的操作后第 $i$ 

应为 $a_{i,j}$ 于 $a_{i,j+1}$ 在未操作前只相差 $1$,所以在行操作后 $a_{i,j+1}-a_{i,j}=mul_i$。

所以 $a_{i,j+1}=mul_i+a_{i,j}$。

所以 $f_i=\sum^{m}_{j=1}  a_{i,j}=f_{i-1}+\sum^{n}_{i=1}mul_i $。

所以可以暴力求出 $f_1$,然后 $O(n)$ 暴力求所有 $f_i$。

所以就可以把二维问题转化为一维问题。

### 代码

```
#include<bits/stdc++.h>
#define int long long
#define re register
#define in inline
using namespace std;
in int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
const int N=1e6+100,mod=1e9+7;
int f[N],mul[N];
int n,m,q,sul,ans;
struct qries{
	int id,l,v;
}t[N];
bool cmp(qries a,qries b){return a.id<b.id;}
signed main(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=q;i++){
		char c;
		cin>>c;
		int id=c-'R'+1,l=read(),v=read();
		t[i]=(qries){id,l,v};
	}
	sort(t+1,t+1+q,cmp);
	for(int i=0;i<=n;i++)mul[i]=1;
	for(int i=1;i<=q;i++){
		if(t[i].id!=1)break;
		mul[t[i].l]*=t[i].v,mul[t[i].l]%=mod;
	}
	for(int i=1;i<=n;i++)f[1]+=(1+(i-1)*m%mod)*mul[i]%mod,f[1]%=mod,sul+=mul[i],sul%=mod;
	for(int i=2;i<=m;i++)f[i]=f[i-1]+sul,f[i]%=mod;			//递推求fi。
	for(int i=0;i<=m;i++)mul[i]=f[i];
	for(int i=1;i<=q;i++){			//再进行列上的操作。
		if(t[i].id==1)continue;
		mul[t[i].l]*=t[i].v,mul[t[i].l]%=mod;
	}
	for(int i=1;i<=m;i++)ans+=mul[i],ans%=mod;
	cout<<ans;
}
/*
3 3 2
1 2 2 5
2 1 3 2
*/
```

最后一句：不要用 getchar。

---

## 作者：NDFS (赞：1)

观察题目给出的矩阵，可以发现每一行都是由上一行的数加 $m$ 得到的，所以第 $i$ 行第 $j$ 列的数字为 $(i-1)m+j$。

再观察操作，每次操作都是一整行或一整列同时乘某个数，而且答案与操作顺序无关，所以可以设 $X_i$ 表示第 $i$ 行最后乘 $x_i$ 倍，设 $Y_j$ 表示第 $j$ 列最后乘 $Y_j$ 倍，那么要求的答案就可以表示为 $\sum_{i=1}^n\sum_{j=1}^m ((i-1)\cdot m+j)\cdot X_i\cdot Y_j$。
化简式子：
$$\sum_{i=1}^n\sum_{j=1}^m ((i-1)\cdot m+j)\cdot X_i\cdot Y_j=\sum_{i=1}^n X_i\cdot\sum_{j=1}^m (i-1)\cdot m\cdot Y_j+j\cdot Y_j$$
$$=\sum_{i=1}^n X_i\cdot(\sum_{j=1}^m (i-1)\cdot m\cdot Y_j+\sum_{j=1}^m j\cdot Y_j)$$
$$=\sum_{i=1}^n X_i\cdot(i-1)\cdot m\cdot\sum_{j=1}^m Y_j+X_i\cdot\sum_{j=1}^m j\cdot Y_j$$
然后发现 $\sum_{j=1}^m Y_j$ 和 $\sum_{j=1}^m j\cdot Y_j$ 完全可以预处理。

所以解法流程：
1. 统计 $X_i$ 和 $Y_j$；
2. 预处理 $\sum_{j=1}^m Y_j$ 和 $\sum_{j=1}^m j\cdot Y_j$；
3. 计算答案。

总的时间复杂度：$O(n+m)$。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
#define mod 1000000007
using namespace std;
int n,m,k,a,b;
ll x[1000005],y[1000005],s1=0,s2=0,ans=0;
char op[1];
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)x[i]=1;
	for(int i=1;i<=m;i++)y[i]=1;
	for(int i=1;i<=k;i++)
	{
		scanf("%s",op),scanf("%d%d",&a,&b);
		if(op[0]=='R')x[a]=x[a]*b%mod;
		else y[a]=y[a]*b%mod;
	}
	for(int i=1;i<=m;i++)s1=(s1+y[i])%mod,s2=(s2+y[i]*i%mod)%mod;
	for(int i=1;i<=n;i++)ans=((ans+x[i]*(i-1)%mod*m%mod*s1%mod)%mod+x[i]*s2%mod)%mod;
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：xiaofu15191 (赞：0)

做模拟赛的时候做到了这道题的类似物。结果赛时打线段树常数和答案都爆炸了。

首先发现题目中的直接相乘是满足交换律的，也就是说操作的次序对答案没有影响。

于是我们想到将形如 `R X Y` 的操作放到前面先做。计算出做完所有 `R X Y` 操作后每一行的乘法系数，以及第一列的数字和 $num_1$。此时相邻两列的数字和，$num_i$ 与 $num_{i+1}$ 之差就是每一行的乘法系数之和。接着再将 `S X Y` 操作给处理了，最终答案直接统计即可。

但是在模拟赛中，题面中的操作改成了形如 `R/S l r x` 的形式，变成了区间更改。不过 $x \ge 1$。

赛时我想到的是线段树维护行、列的系数，然而模拟赛题的数据范围是 $1 \le n,m,q \le 10^6$，时限一秒。那么这种做法就行不通了。

考虑差分。假如我当前正在维护 $mul$ 数组为乘法系数，$[l,r]$ 为目标区间，系数为 $v$。那么用另一个差分数组 $R$，修改时使 $R_l \leftarrow R_i \times v$，$R_{r+1} \leftarrow R_{r+1} \times v^{-1}$，其中 $v^{-1}$ 是 $v$ 在模 $10^9+7$ 意义下的逆元。接着将 $mul_i=mul_{i-1} \times R_i$ 扫一遍即可。


这是那道模拟赛题目的代码：
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cctype>
using namespace std;
const __int128 mod=1000000007;
__int128 n,m,q,mul1[1000010],r1[1000010],mul2[1000010],r2[1000010],num[1000010];
struct operation
{
	__int128 opt,l,r,x;
}queries[1000010];
bool cmp(operation a,operation b)
{
	return a.opt<b.opt;
}
namespace FastIO {
#define il inline
const int iL = 1 << 25;
char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
#define GC() (iS == iT) ? \
	(iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), (iS == iT) ? EOF : *iS++) : *iS++
template <class T>il void read(T &x) {
	x = 0;
	char c = GC(); bool flg = false;
	while (!isdigit(c)) {flg |= c == '-'; c = GC();}
	while (isdigit(c)) {x = (x << 1) + (x << 3) + (c & 15); c = GC();}
	if (flg) x = -x;
}
char Out[iL], *iter = Out;
#define Flush() fwrite(Out, 1, iter - Out, stdout); iter = Out
template <class T>il void write(T x, char LastChar = '\n') {
	int c[35], len = 0;
	if (x < 0) {*iter++ = '-'; x = -x;}
	do {c[++len] = x % 10; x /= 10;} while (x);
	while (len) *iter++ = c[len--] + '0';
	*iter++ = LastChar; Flush();
}
}
using namespace FastIO;
__int128 pow(__int128 a,__int128 b)
{
	__int128 res=1;
	while(b)
	{
		if(b&1) res=(res*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}
int main()
{
	freopen("you.in","r",stdin);
	freopen("you.out","w",stdout);
	read(n),read(m),read(q);
	for(__int128 i=0;i<=max(n,m);i++) mul1[i]=1,r1[i]=1,mul2[i]=1,r2[i]=1;
	for(__int128 i=1;i<=q;i++) read(queries[i].opt),read(queries[i].l),read(queries[i].r),read(queries[i].x);
	sort(queries+1,queries+q+1,cmp);
	__int128 cur=1;
	for(;cur<=q;cur++)
	{
		if(queries[cur].opt==1)
		{
			r1[queries[cur].l]=r1[queries[cur].l]*queries[cur].x%mod;
			r1[queries[cur].r+1]=r1[queries[cur].r+1]*pow(queries[cur].x,mod-2)%mod;
		}
		else break;
	}
	__int128 mul_sum=0;
	for(__int128 i=1;i<=n;i++)
	{
		mul1[i]=mul1[i-1]*r1[i]%mod;
		mul_sum=(mul_sum+mul1[i])%mod;
	}
	for(__int128 i=1,tmp=1;i<=n;i++,tmp+=m) num[1]+=tmp*mul1[i];
	for(__int128 i=2;i<=m;i++) num[i]=num[i-1]+mul_sum;
	for(;cur<=q;cur++)
	{
		r2[queries[cur].l]=r2[queries[cur].l]*queries[cur].x%mod;
		r2[queries[cur].r+1]=r2[queries[cur].r+1]*pow(queries[cur].x,mod-2)%mod;
	}
	for(__int128 i=1;i<=m;i++) mul2[i]=mul2[i-1]*r2[i]%mod;
	__int128 ans=0;
	for(__int128 i=1;i<=m;i++)
	{
		__int128 tmp=num[i]*mul2[i]%mod;
		ans=(ans+tmp)%mod;
	}
	write(ans);
	return 0;
}
```

应该是可以直接改成 P4521 的代码的，但是要做和 $x=0$ 有关的特判。

---

## 作者：Lithium_Chestnut (赞：0)

$100\%$ 得分做法，不难发现我们求完行倍数数组 $h_i$ 和列倍数数组 $l_j$ 后，所求的答案就变成了：$\sum\limits^{n}_{i=1}\sum\limits^{m}_{j=1}\cdot\ h_i\cdot l_j\cdot (j+(i-1)\cdot m)$。我们尝试化简这个式子：

$$\sum\limits^{n}_{i=1}\sum\limits^{m}_{j=1}\cdot\ h_i\cdot l_j\cdot (j+(i-1)\cdot m)$$
$$=\sum\limits^{n}_{i=1}h_i\cdot \sum\limits^{m}_{j=1}l_j\cdot (j+(i-1)\cdot m)$$
$$=\sum\limits^{n}_{i=1}h_i\cdot \sum\limits^{m}_{j=1} (l_j\cdot j+l_j\cdot (i-1)\cdot m)$$
$$=\sum\limits^{n}_{i=1}h_i\cdot( \sum\limits^{m}_{j=1} l_j\cdot j+ \sum\limits^{m}_{j=1} l_j\cdot (i-1)\cdot m)$$
$$=\sum\limits^{n}_{i=1}h_i\cdot (i-1)\cdot m\cdot \sum\limits^{m}_{j=1}l_j+\sum\limits^{n}_{i=1}h_i\cdot \sum\limits^{m}_{j=1}j\cdot l_j$$

化简到这里我们已经实现了每个 $\sum$ 上的参数分离，这样我们只需动态处理 $\sum^{n}_{i=1}h_i$，而预处理 $\sum^{m}_{j=1}j\cdot l_j$ 和 $\sum^{m}_{j=1} l_j$，就可以实现复杂度的降维，那么这里复杂度是 $\mathcal{O}(n+m+k)$ 的。

特别要说的是，此题的数据如果扩到了 1e9，这个做法也会被卡掉，需要提前等差数列算 sum 而不是循环预处理，将复杂度优化至 $\mathcal{O}(k)$。

```cpp
#include<bits/stdc++.h>
#define Std_Maker lhm
#define ll long long
using namespace std;
const int mod=1e9+7,N=1001,M=1e6+1;
ll n,m,k,x,y,ans,sumj,sumlj;
ll h[M],l[M];
char op;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) h[i]=1;
	for(int i=1;i<=m;i++) l[i]=1;
	while(k--)
	{
		cin>>op;
		cin>>x>>y;
		if(op=='R') h[x]=h[x]*y%mod;
		else l[x]=l[x]*y%mod;
	}
	for(int j=1;j<=m;j++) sumj=(sumj+l[j])%mod,sumlj=(sumlj+(j*l[j])%mod)%mod;
	for(int i=1;i<=n;i++) ans=((ans%mod+h[i]%mod*(i-1)%mod*m%mod*sumj)%mod+(h[i]%mod*sumlj)%mod)%mod;
	cout<<ans%mod;
	return 0;
}
```

---

## 作者：ThySecret (赞：0)

## Description

给定一个 $n \times m$ 的矩阵，一共 $k$ 次操作，在相应的行或者列上乘上一个数，求这 $k$ 次操作后的和，答案对 $10^9 + 7$ 取模。

这里给出一种复杂度仅为 $O(k)$ 的做法。

## Solution

我们令 $row_i$ 表示矩阵第 $i$ 行被乘上的系数，$col_i$ 表示矩阵第 $i$ 列被乘上的系数，显然一开始均为 $1$。

根据题意不难发现，矩阵中的权值 $A_{i, j}$ 最后的值将为这一行被乘的总积再乘上这一列被乘的总积。由此可以得出答案：
$$
\begin{align*}
ans &= \sum_{i = 1}^{n}\sum_{j = 1}^{m}  A_{i, j} \times row_i \times col_j
\end{align*}
$$
由于 $A_{i, j}$ 的初值与其位置有关，我们再进行参数分离，可以得到：
$$
\begin{align*}
ans &= \sum_{i = 1}^{n}\sum_{j = 1}^{m} \left( \left (i - 1 \right ) \times m + j \right ) \times row_i \times col_j \\
&= \sum_{i = 1}^{n}row_i \times \left ( \sum_{j = 1}^{m}j \times col_j + \sum_{j = 1}^{m} \left( i - 1\right) \times m \times col_j \right)\\
&= \sum_{i = 1}^{n}row_i \times (i - 1) \times m \times \sum_{j = 1}^{m}col_j + \sum_{i = 1} ^ {n}row_i \times \sum_{j = 1}^{m}j \times col_j \\
\end{align*}
$$
不难发现我们每次可以 $O(1)$ 的修改 $row_i$ 和 $col_i$ 的值，最后行列各跑一遍，根据上式算出答案。

时间复杂度为 $O(n + m + k)$。

## Code

代码中： $sum1 \leftarrow \textstyle {\sum_{i = 1}^{m} col_i}$，$sum2 \leftarrow \textstyle \sum_{i = 1}^{m}i \times col_i$。

```c++
signed main()
{
    cin >> n >> m >> k;
    for (int i = 1; i <= max(n, m); i ++) tagr[i] = tags[i] = 1;
    while (k --)
    {
        char opt; int x, y; cin >> opt >> x >> y;
        if (opt == 'R') tagr[x] = tagr[x] * y % mod;
        else tags[x] = tags[x] * y % mod;
    }
    int sum1 = 0, sum2 = 0, ans = 0;
    for (int i = 1; i <= m; i ++)
        sum1 = (sum1 + tags[i]) % mod, sum2 = (sum2 + tags[i] % mod * i) % mod;
    for (int i = 1; i <= n; i ++)
        ans = (ans + tagr[i] * (i - 1) % mod * m % mod * sum1 % mod + tagr[i] * sum2 % mod) % mod;
    cout << ans << '\n';
    return 0;
}
```

## Extra

如果 $n,m \le 10^9$，$k \le 10^6$，应该如何做呢？

显然时间会超时，而且数组也存不下。

注意到 $k$ 仍旧是可以接受的范围，而每次只会修改一行或者一列，即这个大型矩阵被修改的行列数上界为 $k$， 我们仅仅记录好被修改过的行列，预处理出剩下的点数，每次修改时在线更新 $sum1$ 和 $sum2$ 的值，即可做到 $O(1)$ 的处理。

此处代码以 `unordered_map` 进行记录，时间复杂度为 $O(k)$。

### Code

```c++
LL n, m, k;
unordered_map<LL, LL> mpr, mps;
LL row1, row2, col1, col2;

// row1 = \sigma{tagr_i}   row2 = \sigma{tagr_i * (i - 1)}
// col1 = \sigma{tags_i}   col2 = \sigma{tags_i * i}

int main()
{
    cin >> n >> m >> k;
    row1 = n, row2 = (n - 1) * n / 2 % mod;
    col1 = m, col2 = (m + 1) * m / 2 % mod;

    while (k --)
    {
        char opt; int x, y; cin >> opt >> x >> y;
        if (opt == 'R')
        {
            if (!mpr.count(x)) mpr[x] = 1LL;
            row1 = (row1 + mpr[x] * (y - 1 + mod) % mod) % mod;
            row2 = (row2 + mpr[x] * (y - 1 + mod) % mod * (x - 1) % mod) % mod;
            mpr[x] = mpr[x] * y % mod;
        }
        else
        {
            if (!mps.count(x)) mps[x] = 1LL;
            col1 = (col1 + mps[x] * (y - 1 + mod) % mod) % mod;
            col2 = (col2 + mps[x] * (y - 1 + mod) % mod * x % mod) % mod;
            mps[x] = mps[x] * y % mod;
        }
    }
    cout << (row2 * m % mod * col1 % mod + row1 * col2 % mod) % mod << '\n';
    return 0;
}
```

---

## 作者：_maze (赞：0)

简单说一下题意。

给你一个 $N\times M$ 矩阵，矩阵的第 $x$ 行第 $y$ 列初始为 $(x-1)\times m+y$。

题目会要求你执行 $K$ 步操作，每种操作为下面的一种

1. 输入 $R, X, Y$，表示对第 $X$ 行的每个元素乘 $Y$。

2. 输入 $S, X, Y$，表示对第 $X$ 列的每个元素乘 $Y$。

执行完 $K$ 步操作后，你需要求出矩阵元素之和。


------------

观察原矩阵，左右相邻的元素差 $1$，上下相邻的元素差 $m$。题目只有行操作和列操作两种，如果我们按行进行计算，可以省去行操作，只要在最后再乘即可。

观察列操作，发现如果没有行操作，每一行的元素之和和上一行的元素之和只有上下元素差的区别。

现在我们思考下面一个例子：

```
1 2 3 4
5 6 7 8
```

两行之间的元素差为 $m$。

我们对其进行以下操作：

```
S 1 3
S 4 2
```

两行之间的差变为：

$3m, m, m, 2m$

局势很明朗了，在进行一次竖操作后，这一列相邻元素的元素差也会乘上对应值。那么两行的贡献差就是每一列的元素差，而这是固定的。

那么我们总结一下算法流程：

1. 求出第一行

2. 对于之后的每一行求出与前一行的差

3. 将当前行的和乘行操作

事实上把操作中的一行一列改为多行多列也是可以做的。。。只要加个差分。如果加差分的话还要单独处理 0 的问题。

这里提供一份使用差分的代码，虽然这道题里没有必要。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn = 1e6 + 5;
const ll mod = 1e9 + 7;
ll n, m, q;
ll cha_hang[maxn], cha_lie[maxn], cha[maxn];
vector<int> hang, lie;
ll qpow(ll u, ll v)
{
    ll ans = 1;
    while(v)
    {
        if(v & 1) ans = (ans * u) % mod;
        u = (u * u) % mod;
        v >>= 1;
    }
    return ans;
}
void change_hang(ll l, ll r, ll v)
{
	if(v == 0) 
	{
		hang.push_back(l);
		return ;
	}
    cha_hang[l] = (cha_hang[l] * v) % mod;
    cha_hang[r + 1] = (cha_hang[r + 1] * qpow(v, mod - 2)) % mod;
}
void change_lie(ll l, ll r, ll v)
{
	if(v == 0) 
	{
		lie.push_back(l);
		return ;
	}
    cha[l] = (cha[l] * v) % mod;
    cha[r + 1] = (cha[r + 1] * qpow(v, mod - 2)) % mod;
    cha_lie[l] = (cha_lie[l] * v) % mod;
    cha_lie[r + 1] = (cha_lie[r + 1] * qpow(v, mod - 2)) % mod;
}
ll a[maxn];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
    cin >> n >> m >> q;
    ll l, r, v;
	string type;
    ll W = 0;
    for(ll i = 1;i <= n;i ++) cha_hang[i] = 1;
    for(ll i = 1;i <= m;i ++) cha[i] = 1;
    a[0] = 1;
    for(ll i = 1;i <= m;i ++)
    {
        cha_lie[i] = (i * qpow(max(i - 1, 1LL), mod - 2)) % mod;
    }
    for(ll i = 1;i <= q;i ++)
    {
        cin >> type >> l >> v;
		r = l;
        if(type[0] == 'S') change_lie(l, r, v);
        else change_hang(l, r, v);
    }
    a[0] = 1;
	int p = 0, o = 1;;
	sort(hang.begin(), hang.end());
	sort(lie.begin(), lie.end());
    for(ll i = 1;i <= m;i ++) 
	{
		a[i] = (a[i - 1] * cha_lie[i]) % mod;
	}
    ll ans = 0, ji = 1, mi = 0, chen = 1;
    for(ll i = 1;i <= m;i ++) 
	{
		chen = (chen * cha[i]) % mod;
		if(lie.size() > p && lie[p] == i)
		{
			p ++;
			continue;
		}
		mi = (mi + chen) % mod;
		W = (W + a[i]) % mod;
	}
    ji = cha_hang[1];
	if(hang.size() >= 1 && hang[0] == 1)
		ji = 0;
    ans = (ans + ((ji * W) % mod)) % mod;
	p = 0;
	if(hang.size() >= 1 && hang[0] == 1)
		ji = 1, p ++;
    for(ll i = 2;i <= n;i ++)
    {
        W = (((m * mi) % mod) + W) % mod;
        ji = (ji * cha_hang[i]) % mod;
		if(hang.size() > p && hang[p] == i)
		{
			p ++;
			continue;
		}
        ans = (ans + ((ji * W) % mod)) % mod;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：DF_Factory (赞：0)

## 思路：

这道题中 $n,m$ 很大，而 $k$ 很小，我们可以把每一个操作存下来。只要没有重复，就直接乘。

注意到操作可合并，且有一些点会重复计算，所以我把每一次的操作的修改位置记录下来，后面算出重复计算的点，再减去重复算的值，就是答案。

## 坑点：

随时取模，有一些答案不对的时候看一看自己哪里没有取模。

~~不开 long long 见祖宗~~

## 代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define int long long
#define mod 1000000007
#define N 1000005
using namespace std;
ll ans,sr[N],ss[N],vr[N],vs[N],n,m,k;
struct node{
	ll x,y;
};
vector<node>cf;
vector<int> ts,tr;
signed main(){
	scanf("%lld%lld%lld",&n,&m,&k);
	for(int i=1;i<=n;i++) ss[1]=(ss[1]+1+((i-1)*m+mod)%mod+mod)%mod;
	for(int i=1;i<=m;i++){
		if(i>1) ss[i]=(ss[i-1]+n+mod)%mod;
		sr[1]=(sr[1]+i+mod)%mod;
		vs[i]=1;
	}
	for(int i=1;i<=n;i++){
		if(i>1)sr[i]=(sr[i-1]+(m*m+mod)%mod+mod)%mod;
		ans=(ans+sr[i]+mod)%mod;
		vr[i]=1;
	}
   //算出行和和列和
	char cc;ll x,y;
	for(int i=1;i<=k;i++){
		cin >> cc;
		scanf("%lld%lld",&x,&y);
		if(cc=='R') vr[x]=(y*vr[x])%mod;
		else vs[x]=(y*vs[x])%mod;
	}
	for(int i=1;i<=n;i++){
		ans=(ans+(sr[i]*(vr[i]-1)+mod)%mod+mod)%mod;
		if(vr[i]!=1)tr.push_back(i);
	}
	for(int i=1;i<=m;i++){
		ans=(ans+(ss[i]*(vs[i]-1)+mod)%mod+mod)%mod;
		if(vs[i]!=1)ts.push_back(i);
	}
   //处理一般的位置
	ll a,b,c,d;
	for(int i=0;i<tr.size();i++){
		for(int j=0;j<ts.size();j++){
			x=tr[i],y=ts[j];
			a=(m*(x-1)+y+mod)%mod;
			b=((a*(vr[x]-1)+mod)%mod+mod)%mod;
			c=((a*(vs[y]-1)+mod)%mod+mod)%mod;
			d=(((a*(vr[x]*vs[y]%mod-1+mod)%mod))+mod)%mod;
			ans=(ans-b-c+d+mod)%mod;
		}
	}
   //减去重复算的位置
	printf("%lld",(ans+mod)%mod); 
	return 0;
}
```


---

## 作者：decoqwq (赞：0)

考虑到$n,m$很大并且$k$很小，自然想到$k^2$复杂度的做法

我们考虑记录两个数组$mul1$和$mul2$，分别代表第$i$行乘了多少倍和第$i$列乘了多少倍，然后记录数组$h$和$l$分别代表我们进行修改的行和列，将这两个数组分别去重后，我们可以先将不用修改的答案算出来，简单容斥即可，然后再将修改了的行和列的答案用$mul1$和$mul2$分别计算出来后，交叉点简单容斥，就可以得到最后的答案

因为每次枚举了修改的行和列，所以时间复杂度$O(k^2)$

具体看代码
```cpp
/*deco loves Chino*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,cnt1,cnt2; 
int h[1010],l[1010];
int mul1[1000010],mul2[1000010];
int app1[1000010],app2[1000010];
const int mod=1e9+7;
main()
{
	//freopen("automobil.in","r",stdin);
	//freopen("automobil.out","w",stdout);
	cin>>n>>m>>k;
	fill(mul1+1,mul1+n+1,1);
	fill(mul2+1,mul2+m+1,1);
	int ans;
	if(n%2==1&&m%2==1)
	{
		ans=((1+n*m)/2)%mod*n%mod*m%mod;
	}
	else
	{
		ans=(1+n*m)%mod*((n*m/2)%mod)%mod;
	}
	char opt[6];
	for(int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%s%lld%lld",opt,&x,&y);
		if(opt[0]=='R')
		{
			h[++cnt1]=x;
			mul1[h[cnt1]]=mul1[h[cnt1]]*y%mod;//行的倍数
		}
		else
		{
			l[++cnt2]=x;
			mul2[l[cnt2]]=mul2[l[cnt2]]*y%mod;//列的倍数
		}
	}
	sort(h+1,h+cnt1+1);
	sort(l+1,l+cnt2+1);
	cnt1=unique(h+1,h+cnt1+1)-h-1;
	cnt2=unique(l+1,l+cnt2+1)-l-1;
  	/*第一次计算不修改部分的答案*/
	for(int i=1;i<=cnt1;i++)
	{
		int qaq;
		if(m%2==1)
		{
			qaq=(2*h[i]*m-m+1)/2%mod;
			qaq=qaq*m;
			qaq%=mod;
		}
		else
		{
			qaq=m/2;
			qaq=qaq*((2*h[i]*m-m+1)%mod); 
			qaq%=mod;
		}
		ans-=qaq;
	}
	for(int i=1;i<=cnt2;i++)
	{
		int qaq;
		if(m%2==0)
		{
			qaq=(2*l[i]+n*m-m)/2%mod;
			qaq=qaq*n%mod;
			qaq%=mod;
		} 
		else if(n%2==0)
		{
			qaq=n/2%mod;
			qaq=qaq*(2*l[i]+n*m-m)%mod;
			qaq%=mod;
		}
		else
		{
			qaq=(2*l[i]+n*m-m)/2%mod;
			qaq=qaq*n%mod;
			qaq%=mod;
		}
		ans-=qaq;
		for(int j=1;j<=cnt1;j++)
		{
			ans+=(h[j]-1)*m+l[i];
			ans%=mod;
		}
	}
   /*计算修改部分最后的答案*/
	for(int i=1;i<=cnt1;i++)
	{
		int qaq;
		if(m%2==1)
		{
			qaq=(2*h[i]*m-m+1)/2%mod;
			qaq=qaq*m;
			qaq%=mod;
		}
		else
		{
			qaq=m/2;
			qaq=qaq*((2*h[i]*m-m+1)%mod);
			qaq%=mod;
		}
		qaq=qaq*mul1[h[i]]%mod;
		ans+=qaq;
		ans%=mod;
	}
	for(int i=1;i<=cnt2;i++)
	{
		int qaq;
		if(m%2==0)
		{
			qaq=(2*l[i]+n*m-m)/2%mod;
			qaq=qaq*n%mod;
			qaq%=mod;
		} 
		else if(n%2==0)
		{
			qaq=n/2%mod;
			qaq=qaq*(2*l[i]+n*m-m)%mod;
			qaq%=mod;
		}
		else
		{
			qaq=(2*l[i]+n*m-m)/2%mod;
			qaq=qaq*n%mod;
			qaq%=mod;
		}
		qaq*=mul2[l[i]];
		qaq%=mod;
		ans+=qaq;
		ans%=mod;
		for(int j=1;j<=cnt1;j++)
		{
			ans+=(((h[j]-1)*m+l[i])%mod*((mul1[h[j]]*mul2[l[i]]-mul1[h[j]]-mul2[l[i]])%mod))%mod;
			ans%=mod;
		}
	}
	cout<<ans;
}
```

---

