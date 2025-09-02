# [ARC020C] A mod B Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc020/tasks/arc020_3

高橋君が高校生の頃参加していたコンテストでは、$ 2 $ つの整数の和を求める問題が出題されたことがありました。あんなものは最強最速の手に掛かればお茶の子さいさいでした。

大学生になった高橋君は、現在あなたと大学生向けのコンテストに参加している真っ最中です。しかし、得意な言語を使う際に必要な統合開発環境が壊れていて、問題を解くどころではないらしいのです。 そこで、チームメイトであるあなたは、統合開発環境の問題が審判団によって対応されるまでに、彼の代わりに以下の問題を解いておくことにしました。

整数 $ A $ と $ B $ が与えられる。 $ A $ を $ B $ で割った余りを出力しなさい。ただし、整数 $ A $ と整数 $ B $ について以下のような特徴があります。

- 整数 $ A $, $ B $ はどちらも $ 10 $ 進数である。
- 整数 $ B $ は $ 100 $ 点中 $ 99 $ 点分のテストケースで $ B=1000000007(10^9+7) $ を満たしている。
- 整数 $ A $ は非常に大きく、かつ部分的に周期性を持ち、以下のような形式で与えられる。
- $ N $ と $ a_1,a_2,..,a_N $ と $ L_1,L_2,..,L_N $ が与えられる。これは、整数 $ A $ が上の桁から $ a_1 $ が $ L_1 $ 回、$ a_2 $ が $ L_2 $ 回、..、$ a_N $ が $ L_N $ 回と繰り返された形であることを意味する。


例えば、 $ N=3,a=\{123,4,56\},L=\{2,2,1\},B=1000000007 $のとき、$ A=1231234456 $であり、$ A $ を $ B $ で割った余りは $ 231234449 $ です。

## 说明/提示

### 部分点

この問題には3つのデータセットがあり、データセット毎に部分点が設定されている。

- $ L_1+L_2+..+L_N\ ≦\ 100,000 $ かつ、$ B=1000000007 $ を満たすデータセット 1 に正解した場合は $ 20 $ 点が与えられる。
- $ B=1000000007 $ を満たすデータセット 2 に正解した場合は、上記のデータセットとは別に $ 79 $ 点が与えられる。
- 追加制約のないデータセット 3 に正解した場合は、上記のデータセットとは別に $ 1 $ 点が与えられる。

### Sample Explanation 1

問題文中の例です。

### Sample Explanation 2

$ A=123123123 $ です。

### Sample Explanation 3

このテストケースはデータセット 1,2,3 の制約を満たしています。

### Sample Explanation 4

このテストケースはデータセット 2,3 の制約を満たしています。

### Sample Explanation 5

このテストケースはデータセット 3 の制約を満たしています。

## 样例 #1

### 输入

```
3
123 2
4 2
56 1
1000000007```

### 输出

```
231234449```

## 样例 #2

### 输入

```
1
123 3
1000000007```

### 输出

```
123123123```

## 样例 #3

### 输入

```
1
123456789 10000
1000000007```

### 输出

```
372735614```

## 样例 #4

### 输入

```
4
810143056 100000000
81671422 99999999
1639053 99999998
1657560 99999997
1000000007```

### 输出

```
476685993```

## 样例 #5

### 输入

```
3
2 3
3 2
5 3
99```

### 输出

```
36```

# 题解

## 作者：Autream (赞：4)

看到题解区没有用矩乘写的，所以我来~~水一发~~。
#### 题意简述
现在有一个很大的整数，由 $N$ 个部分组成，第 $i$ 个部分由 $a_i$ 重复 $l_i$ 次得到。

求大整数模 $B$ 的值。

---
#### 题目分析
如果不考虑取模的话，那么这个数字 $ans$ 可以写为

$$
\overline{\underbrace{a_1 a_1 \cdots a_1} _{l_1个}\underbrace{a_2 a_2 \cdots a_2} _{l_2个}\underbrace{a_3 a_3 \cdots a_3} _{l_3个} \cdots \underbrace{a_n a_n \cdots a_n} _{l_n个}}
$$

如果从 $1$ 开始遍历，对于每个 $i$，$ans$ 就会乘上 $a_i$ 的位数再加上 $a_i$，重复 $l_i$ 次。

形式化的来讲，$ans \to ans \times 10^{\log a_i + 1} + a_i$，重复 $l_i$ 次。

对于这种转移柿子，我们可以~~自然而然地~~想到矩乘。

考虑初始矩阵。需要记录 $ans$，并且每次要加上 $a_i$，所以可以设初始矩阵为
$$
\begin{bmatrix}
ans & a_i
\end{bmatrix}
$$
每次 $ans$ 变为 $ans \times 10^{(\log a_i + 1)} + a_i$，重复 $l_i$ 次，所以需要转移矩阵为
$$
\begin{bmatrix}
10^{\log a_i+1}& 0\\
1&1
\end{bmatrix}^{l_i}
$$
遍历 $1 \sim n$，每次乘上转移矩阵，最终值为初始矩阵的 $ans$。

**注意：本题为早期 Atcoder 结尾需要输出换行。**

---
#### AC Code
```cpp
#include<bits/stdc++.h>
#define arrout(a,n) rep(i,1,n)std::cout<<a[i]<<" "
#define arrin(a,n) rep(i,1,n)std::read()
#define rep(i,x,n) for(int i=x;i<=n;i++)
#define dep(i,x,n) for(int i=x;i>=n;i--)
#define erg(i,x) for(int i=head[x];i;i=e[i].nex)
#define dbg(x) std::cout<<#x<<":"<<x<<" "
#define mem(a,x) memset(a,x,sizeof a)
#define all(x) x.begin(),x.end()
#define arrall(a,n) a+1,a+1+n
#define PII std::pair<int,int>
#define m_p std::make_pair
#define u_b upper_bound
#define l_b lower_bound
#define p_b push_back
#define CD const double
#define CI const int
#define int long long
#define il inline
#define ss second
#define ff first
#define itn int
int read() {
    char ch=getchar();
    int r=0,w=1;
    while(ch<'0'||ch>'9') w=ch=='-'?-1:w,ch=getchar();
    while(ch>='0'&&ch<='9') r=r*10+ch-'0',ch=getchar();
    return r*w;
}
CI N=1e4+5;
int n,a[N],l[N],mod;
struct matrix {
    int mat[2][2];
    matrix() {
        mem(mat,0);
    }
    matrix operator*(const matrix& b)const {
        matrix ans;
        rep(i,0,1) {
            rep(j,0,1) {
                rep(k,0,1) {
                    ans.mat[i][j]=(ans.mat[i][j]+mat[i][k]*b.mat[k][j]%mod)%mod;
                }
            }
        }
        return ans;
    }
    matrix operator^(int& b)const {
        matrix ans,a=*this;
        ans.mat[0][0]=ans.mat[1][1]=1;
        while(b) {
            if(b&1) {
                ans=ans*a;
            }
            a=a*a;
            b>>=1;
        }
        return ans;
    }
}g,t;
int32_t main() {
    n=read();
    rep(i,1,n) {
        a[i]=read();
        l[i]=read();
    }
    mod=read();
    rep(i,1,n) {
        g.mat[0][1]=a[i];
        t.mat[0][0]=(int)pow(10,(int)log10(a[i])+1)%mod;
        t.mat[1][0]=1;
        t.mat[1][1]=1;
        g=g*(t^l[i]);
    }
    std::cout<<g.mat[0][0]%mod<<"\n";
    return 0;
}
```

---

## 作者：μηδσ (赞：3)

## Definition

### 题目描述

给出两个整数$A$和$B$，两个数均为$10$进制的

$100$分中$99$分的测试样例中满足$B=1000000007(1e9 + 7)$

整数$A$非常大，且部分具有周期性，以下列形式给出

给整数$N$、$a_1,a_2,a_3,\cdots,a_N$以及$L_1,L_2,L_3,\cdots.L_N$这意味着整数$A$是由$a_1$个$L_1$,$a_2$个$L_2$,$\cdots$,$a_N$个$L_N$组成的

例如$N=3,a=\{123, 4, 56\},L=\{2, 2, 1\},B=1000000007$
时$A=1231234456$，A除以B的余数就是$231234449$

### 输入格式

输入以以下形式输入

```
N
a1 L1
a2 L2
...
aN LN
B
```

第$1$行输入一个整数表示整数($N$)的长度

第$2$行至$N+1$行，提供关于整数$A$的信息，其中，在第$i$行，输入两个整数$a_i(1\le a_i\le 10^9)$和$L_i(1\le L_i\le 10^9)$表示将$a_i$循环$L_i$遍放到$A$的后面

第$N+2$行给出$B(1\le B\le 1000000007(1e9+7)\ )$

### 输出格式

将$A$除以$B$的余数输出，在输出的末尾加入换行符

### 样例说明

样例比较多，此处仅说明样例3和样例4

### 样例3

$N=1$

$a=\{123456789\},L=\{10000\}$

$B=1000000007$

此时$A=\overbrace{123456789\cdots123456789}^{10000\text{个}}$

所以$A$除以$B$的余数为$372735614
$

### 样例4

$N=4$

$a=\{810143056,881671422,1639053,1657560\},L=\{100000000,99999999,99999998,99999997\}$

$B=1000000007$

此时$A=\overbrace{810143056\cdots810143056}^{100000000\text{个}}\overbrace{81671422\cdots81671422}^{99999999\text{个}}\overbrace{1639053\cdots1639053}^{99999998\text{个}}\overbrace{1657560\cdots1657560 }^{99999997\text{个}}$

所以$A$除以$B$的余数为$476685993
$

## Solution

拿到这道题的第一反应是模拟，每次把$A$往前移动$digit(a_i)$位$(digits(i)\text{表示i的位数})$但这样实在是太慢了，因为这个$l_i$可以很大啊

不难发现一个事情，就是每一段都是由$a_i$重复而来的，于是我们可以考虑一下用倍增

第一次算$\overline{a_i}\%B$

第二次算$\overline{a_i a_i}\%B$

以此类推，可以算出每一段$\%B$的结果

注意中途不要重复的计算$digit(a_i)$以防模$B$之后数位发生变化

思路差不多就是这样了，直接看代码吧

## Code

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define re register
#define Mem(a, b) memset(a, b, sizeof(a));
#define rep(a, b, c) for(re long long a = b;a <= c;a++)
#define per(a, b, c) for(re long long a = b;a >= c;a--)

using namespace std;
typedef long long ll;

const int MAXN = 10005;

template <typename T>					//快读 
inline void read(T &x){
    x = 0;
    char c = 0;
    T w = 0;
    while(!isdigit(c))
        w |= c == '-', c = getchar();
    while(isdigit(c)) x = x * 10 + (c ^ 48), c = getchar();
    if(w)
        x = -x;
}

ll n, ans, mod;							//分别定义循环部分个数,答案以及模数 
ll a[MAXN], l[MAXN]; 					//分别定义每一个循环部分的循环节以及循环次数 

ll fastpow(ll b, ll mod){				//倍增快速幂
    ll base = 10;						//底数赋值为10(这个只是之后用来给A偏移用的,所以这里直接赋值为10) 
    ll ret = 1;							//定理返回值(10^b%mod) 
    while(b){
        if(b & 1)						//如果b是奇数就把base撑到ret里 
            (ret *= base) %= mod;
        (base *= base) %= mod;			//base自乘 
        b >>= 1;						//b右移以为 
    }
    return ret % mod;					//返回ret%mod的值 
}

ll getdigit(ll x){						//取位数函数 
    ll ret = 0;
    while(x){							//每一次将x除以10,数位++ 
        ret++;
        x /= 10;
    }
    return ret % mod;
}

void solve(ll x){						//这里和倍增快速幂的思路差不多 
	ll pow10 = fastpow(getdigit(a[x]), mod);
    ll base = a[x];						//分别定义基础的左移量以及 
    while(l[x]){
        if(l[x] & 1){					//如果l[x]是奇数 
            ans = ans * pow10;			//将ans左移 
            ans += base;				//ans加上base 
            ans %= mod;					//取一下mod 
        }
        base = base * pow10 + base;		//base自增一下 
        pow10 = pow10 * pow10;			//左移量自增 
        pow10 %= mod;					//这里用到的是余数法则,不懂的可谓问问度娘 
        base %= mod;					//分别将base和左移量模一下模数 
        l[x] >>= 1;						//l[x]右移一下 
    }
    ans %= mod;							//返回 
}

int main(){
	while(scanf("%lld", &n) != EOF){	//以防万一,多组数据输入 
		Mem(a, 0);						//初始化 
		Mem(l, 0);
		ans = 0;
	    rep(i, 1, n)					//循环输入每一个循环部分循环节以及次数 
	    	scanf("%lld%lld", &a[i], &l[i]);
	    read(mod); 						//输入模数 
	    if(mod == 0){					//特判一下是否为0(好习惯 
	    	printf("ERROR\n"); 
	    	return 0;
		}
	    rep(i, 1, n)					//循环加入每一个循环节 
	        solve(i);
	    printf("%lld\n", ans % mod);	//输出,注意要加换行 
	}
    return 0;							//结束程序 
}
```


---

## 作者：nanatsuhi (赞：2)

一道着实有趣的数学题。

用到了分段计算的方法，将$L$个$a$分解成每次要么折半要么减掉$1$的几段。

个人觉得和快速幂有异曲同工之妙QwQ

具体的实现参考代码。

```cpp
#include <algorithm>
#include <iostream>
#define ll long long
using namespace std;
ll a[100001];
ll L[100001];
ll B;
ll digit(ll x) //统计位数
{
    ll cnt = 0;
    while (x != 0)
    {
        x /= 10;
        cnt++;
    }
    return cnt;
}
ll dpow(ll x, ll y) //快速幂
{
    if (y == 0)
    {
        return 1;
    }
    if (y % 2 == 1)
    {
        return x * dpow(x, y - 1) % B;
    }
    else
    {
        return dpow(x * x % B, y / 2);
    }
}
ll rem(ll x, ll y) //主体
{
    if (y == 0) //到底了
    {
        return 0;
    }
    ll d = digit(x);
    if (y % 2 == 0)
    {
        ll r = rem(x, y / 2); //折半的情况
        return (dpow(10, y / 2 * d) % B * r % B + r) % B;
    }
    else
    {
        ll r = rem(x, y - 1); //减掉1的情况
        return (dpow(10, d) % B * r % B + x % B) % B;
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i] >> L[i];
    }
    cin >> B;
    ll result = 0;
    for (int i = 0; i < n; i++)
    {
        ll d = digit(a[i]);
        ll offset = dpow(10, L[i] * d);
        result = (result * offset % B + rem(a[i], L[i])) % B;
    }
    cout << result << endl;
    return 0;
}
```


---

## 作者：run_away (赞：1)

## 题意

最开始有一个空的数 $s$，给定 $n$ 组整数 $a,l$，表示把 $a$ 复制 $l$ 次再粘贴到 $s$ 后，求最终 $s$ 对 $b$ 取模的值。

## 分析

考虑用 $s_{i}$ 表示第 $i$ 次操作后的值，我们只需要模拟每一次操作就行了，但是这个 $l$ 的范围卡的很死。

但我们发现 $n$ 不是很大~~且刚好学完矩乘~~，所以考虑矩阵优化递推，然后发现这题和 [ABC129F](https://www.luogu.com.cn/problem/AT_abc129_f) 很像了。

用矩阵 $[s_i,1]$ 表示一次操作后的数据（由于要加 $a_{i-1}$，所以有一位常数项），我们要做的是从 $[s_{i-1},1]$ 转移过来，设 $lg$ 为 $\lfloor\log_{10} a_{i-1}\rfloor+1$，可以构造出转移矩阵 $tot$：

$$
\begin{bmatrix}
  10^{lg}&0\\
  a_{i-1}&1
\end{bmatrix}
$$

初始矩阵 $ans$ 为 $[0,1]$，每次更新答案为 $ans\times tot^l$。**注意取模，一定要给 $10^{lg}$ 和 $a_{i-1}$ 取模！**

最终时间复杂度为 $O(n\log l)$，有 $2^3$ 的常数。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll maxn=1e4+5,maxt=2;
ll n,mod;
struct node{ll a,l;}p[maxn];
struct matrix{
    ll mat[maxt][maxt];
    inline matrix operator*(const matrix&u)const{
        matrix res;
        memset(res.mat,0,sizeof(res.mat));
        for(ll i=0;i<maxt;++i){
            for(ll j=0;j<maxt;++j){
                for(ll k=0;k<maxt;++k){
                    res.mat[i][j]=(res.mat[i][j]+mat[i][k]*u.mat[k][j]%mod+mod)%mod;
                }
            }
        }
        return res;
    }
}ans;
inline matrix qpow(matrix a,ll b){
    matrix res;
    memset(res.mat,0,sizeof(res.mat));
    for(ll i=0;i<maxt;++i)res.mat[i][i]=1;
    while(b){
        if(b&1)res=res*a;
        a=a*a,b>>=1;
    }
    return res;
}
signed main(){
    n=read();
    for(ll i=1;i<=n;++i)p[i].a=read(),p[i].l=read();
    mod=read();
    memset(ans.mat,0,sizeof(ans.mat));
    ans.mat[0][1]=1;
    for(ll i=1;i<=n;++i){
        ll lg=1,A=p[i].a;
        while(A)A/=10,lg*=10;
        matrix tot;
        memset(tot.mat,0,sizeof(tot.mat));
        tot.mat[0][0]=lg%mod,tot.mat[0][1]=0;
        tot.mat[1][0]=p[i].a%mod,tot.mat[1][1]=1;
        ans=ans*qpow(tot,p[i].l);
    }
    printf("%lld\n",ans.mat[0][0]);
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

想到使用十进制拆分分别记录贡献，最后相加。

考虑从后往前递推，因为最后一位的贡献就是它本身，而前面则要考虑自己后面有多少位数。

考虑第 $i$ 个数重复 $l_i$ 次单独的贡献，遍历 $l_i$，假设目前是第 $j$ 次，贡献就是 $10^{(j-1)\times |a_i|}\times a_i$。

一个数的总贡献即为 $\sum\limits_{j=1}^{l_i}10^{(j-1)\times |a_i|}\times a_i$。

$|a_i|$ 即为 $a_i$ 的位数。

但这样太慢了，所以考虑使用矩阵加速递推。

也就是：

$$\begin{bmatrix}
 sum & 10^{|a_i|\times (j-1)}
\end{bmatrix}\times \begin{bmatrix}
1 & 0 \\
a & 10^{|a_i|} \\
\end{bmatrix}= \begin{bmatrix}
 sum' & 10^{|a_i|\times j}
\end{bmatrix}$$

初始矩阵就是

$$\begin{bmatrix}
 a_i & 10^{|a_i|} 
\end{bmatrix}$$

然后直接矩阵快速幂。

注意只处理 $l_i-1$，因为初始矩阵即为有一个 $a_i$ 的情况了。

最后在计算答案时要计算目前自己的位数的贡献，即 $10^{sum}$，最后两者相乘。

$sum= \sum\limits_{j=1}^{i} l_j\times |a_j|$，即后面的位数。

## code

```cpp
#include<bits/stdc++.h>
#define sd std::
#define int long long
#define il inline
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define f(i,a,b) for(int i=(a);i>=(b);i--)
il int read(){int w=1,c=0;char ch=getchar();for(;ch>'9'||ch<'0';ch=getchar()) if(ch=='-') w=-1;for(;ch>='0'&&ch<='9';ch=getchar()) c=(c<<3)+(c<<1)+ch-48;return w*c;}
void printt(int x){if(x>9) printt(x/10);putchar(x%10+48);}
il void print(int x){if(x<0) putchar('-'),printt(-x);else printt(x);}
il void put(int x){print(x);putchar('\n');}
const int N=1e4+10;
int n,mod;
struct M
{
	int a[25][25];
	il void init(){F(i,1,2) a[i][i]=1;}
    il M operator*(M t)
	{
	    M res;
	    F(i,1,2) F(j,1,2) res.a[i][j]=0;
	    F(i,1,2) F(j,1,2) F(k,1,2) res.a[i][j]=(res.a[i][j]+a[i][k]*t.a[k][j]%mod)%mod;
    	return res;
	}
}ans,base;
il M qow(M a,int k)//矩阵快速幂
{
	M res=a,_=a;
	k--;//因为此时res相当于a的一次幂，所以只算k-1次 
	while(k)
	{
		if(k&1) res=res*_;
		_=_*_;
		k>>=1;
	}
	return res;
}
int size[N];//记录|ai|
int a[N],l[N];
int ksm(int p,int q)//整数快速幂，用来计算10次幂 
{
	if(!q) return 1;
	if(q&1) return p*ksm(p,q-1)%mod;
	int tmp=ksm(p,q/2)%mod;
	return tmp*tmp%mod;
}
int res,sum;//计算答案 
il void solve()
{
	n=read();
	F(i,1,n)
	{
		a[i]=read(),l[i]=read();
		size[i]=1+(sd log10(a[i]));//计算位数 
	}
	mod=read();
	f(i,n,1)
	{
		if(l[i]==1) res=(res+ksm(10,sum)*a[i]%mod)%mod;//因为l[i]=1 时运行下面的程序次幂会直接变成-1所以需要特殊处理 
		else
		{
			ans.a[1][1]=a[i];
			ans.a[1][2]=ksm(10,size[i]);
			base.a[1][1]=1;
			base.a[2][1]=a[i];
			base.a[2][2]=ksm(10,size[i]);
			ans=ans*qow(base,l[i]-1);res=(res+ksm(10,sum)*ans.a[1][1]%mod)%mod;
		}
		sum+=size[i]*l[i];
	}
	put(res);
}
signed main()
{
	int T=1;
//	T=read();
	while(T--) solve();
    return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# arc020 解题报告

## 前言

你说的对，但是这看起来就很像矩阵乘法。

## 思路分析

考虑对每一组 $a_i,l_i$ 分别快速计算答案。

设 $f_j$ 表示连续 $j$ 个 $a$ 拼接的答案，$len_a$ 表示 $a$ 在十进制下的长度，则有：

$$f_j=10^{len_a}f_{j-1}+a$$

这个形式肯定可以用矩阵乘法加速递推。

设初始矩阵为：

$$\begin{bmatrix}
  f_i& f_{i-1} & 1
\end{bmatrix}$$

转移一次矩阵为：

$$\begin{bmatrix}
  f_{i+1}& f_i & 1
\end{bmatrix}$$

不难得到转移矩阵为：

$$\begin{bmatrix}
  10^{len_a}& 1& 0\\
  0& 0& 0&\\
  a& 0& 1
\end{bmatrix}$$

直接用矩阵快速幂计算就行。

总体复杂度为 $O(n\log v)$，但是带一个 $9$ 倍常数，所以跑的不是很快。

## 代码实现

```cpp

#include<bits/stdc++.h>
#define int long long
using namespace std;
long long ans;
int n,x[200005],l[200005],len,mod;
struct node{
	long long h[4][4];
	node(){
		memset(h,0,sizeof(h));
	}
	node operator *(const node &a)const{
		node ans;
		for(int i=1;i<=3;i++){
			for(int j=1;j<=3;j++){
				for(int k=1;k<=3;k++){
					ans.h[i][j]=(ans.h[i][j]+h[i][k]*a.h[k][j]%mod)%mod;
				}
			}
		}
		return ans;
	}
}a,b,c;
node binpow(node a,int b){
	if(b==0) return c;
	node res=binpow(a,b/2);
	if(b&1) return (res*res)*a;
	else return res*res;
}
int getlen(int x){
	int cnt=0,ans=1;
	while(x){
		cnt++;
		x/=10;
	}
	while(cnt--){
		ans=ans*10%mod;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x[i]>>l[i];
	}
	cin>>mod;
	c.h[1][1]=1;
	c.h[2][2]=1;
	c.h[3][3]=1;
	for(int i=1;i<=n;i++){
		len=getlen(x[i]);
		if(l[i]==1){
			ans=(ans*len%mod+x[i])%mod;
			continue;
		}
		a.h[1][3]=1;
		a.h[1][2]=ans;
		ans=(ans*len%mod+x[i])%mod;
		a.h[1][1]=ans;
		b.h[1][1]=len;
		b.h[1][2]=1;
		b.h[3][1]=x[i];
		b.h[3][3]=1;
		a=a*binpow(b,l[i]-1);
		ans=a.h[1][1];
	}
	cout<<ans<<'\n';
	return 0;
}

```

## 后记

祝大家 CSP2024 rp++

怎么有 $4$ 倍常数的做法啊，被吊打了。

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/arc020c-a-mod-b-problem-de-ti-jie/)
## 题目大意
将 $l_i$ 个 $a_i$ 依次拼接在一起，结果对 $10^9+7$ 取模。
## 思路
假设答案为 $ans$，那么递推的方程为 $ans=ans\cdot 10^{\lfloor\log_{10}a_i\rfloor}+a_i$。

因为 $l_i$ 有 $10^9$ 进行模拟是不可行的，所以考虑使用矩阵快速幂加速递推。

$$\begin{bmatrix} ans & a_i\end{bmatrix}=\begin{bmatrix} ans & a_i\end{bmatrix} \times  \begin{bmatrix} 10^{\lfloor\log_{10}a_i\rfloor} & 0\\1&1\end{bmatrix}^{l_i}$$

## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+6;
struct node{
	int a[3][3];
	node(){
		memset(a,0,sizeof(a));
	}
}ans,aa;
int n,mod,a[N],l[N];
node times(node x,node y){
	node cnt;
	for(int i=1;i<=2;i++){
		for(int j=1;j<=2;j++){
			for(int k=1;k<=2;k++)
				cnt.a[i][j]=(cnt.a[i][j]+x.a[i][k]*y.a[k][j])%mod;
		}
	}return cnt;
}node ksm(int x){
	while(x){
		if(x&1) ans=times(ans,aa);
		x>>=1;
		aa=times(aa,aa);
	}return ans;
}int f(int x){
	int cnt=0;
	while(x){
		cnt++;
		x/=10;
	}
	x=1;
	for(int i=1;i<=cnt;i++){
		x*=10;
	}
	return x;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>l[i];
	}
	cin>>mod;
	ans.a[1][1]=0;
	for(int i=1;i<=n;i++){
		ans.a[1][2]=a[i]%mod;
		aa.a[1][1]=f(a[i])%mod;
		aa.a[2][1]=aa.a[2][2]=1;
		ksm(l[i]);
	}
	cout<<ans.a[1][1]<<'\n';
	return 0;
}
```

---

## 作者：diamond_153 (赞：0)

题目大意：有两个长度为 $n$ 的数列 $a_i,l_i\in \mathbb N^+$ 以及正整数 $B$，$A$ 为将每个 $a_i$ 重复拼接 $l_i$ 次然后全部依次拼接得到的结果，求 $A \mathrm{\ mod\ } B$。所以若 $a=\{4,128,16\},l=\{2,2,1\},B=1000$，则 $A=4412812816$，答案为 $A \mathrm{\ mod \ } 1000=816$。

这题首先考虑模拟，设 $a_i$ 在十进制下的长度为 $w_i=\lceil\log_{10}(a_i+1)\rceil$，将 $a_i$ 重复拼接 $l_i$ 次得到的数为 $m_i$，则 $m_i=(1+10^{w_i}+10^{2w_i}+\cdots+10^{l_iw_i})a_i$，最后再将 $m_i$ 依次拼接（$m_i$ 的长度为 $l_iw_i$）。这个值如果直接计算的话复杂度就是 $O(\sum l_i)$，无法通过本题，考虑优化。

发现

$$
(1+10^x+\cdots+10^{(k-1)x})(1+10^{kx})=1+10^x+\cdots+10^{(2k-1)x}
$$

所以考虑用倍增法求 $m_i$，与快速幂类似，复杂度为 $O(\sum \log l_i)$。
```cpp
//快速幂
for(;pow;pow>>=1,base=base*base)
    if(pow&1)ret=ret*base;
//求 m_i
for(int t=0;l[i];l[i]>>=1,a[i]=a[i]*(qpow(10,w[i]<<t)+1),t++)
    if(l[i]&1)m[i]=m[i]*qpow(10,w[i]<<t)+a[i];

```
为了不计算多次 `qpow(10,w[i]<<t)`，考虑记录然后同时倍增（$10^{2x}=(10^x)^2$）。

完整代码：
```cpp
#include<iostream>
#define int long long
int n,mod,ans=0,w,m,p,a[10100],l[10100];
inline int qpow(int base,int pow,int m){
    static int ret;
    for(ret=1;pow;pow>>=1,base=base*base%m)
        if(pow&1)ret=ret*base%m;
    return ret;
}
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin>>n;
    for(int i=0;i<n;i++)std::cin>>a[i]>>l[i];
    std::cin>>mod;
    for(int i=0;i<n;i++){
        p=qpow(10,w=__builtin_ceil(__builtin_log(a[i]+1)/__builtin_log(10)),mod);
        ans=ans*qpow(10,l[i]*w,mod)%mod;
        for(int j=m=0,t=qpow(10,w,mod);l[i];l[i]>>=1,a[i]=a[i]*(t+1)%mod,j++,t=t*t%mod)
            if(l[i]&1)m=(m*t+a[i])%mod;
        ans=(ans+m)%mod;
    }
    std::cout<<ans<<std::endl;
}
```

---

## 作者：PCCP (赞：0)

## 思路

先想暴力做法，显然把重复的也拆开来，每一小段都算一遍贡献，然后相加，这样的时间复杂度是 $ O(\log_2{V}\displaystyle\sum_{i=1}^{n}{y_i}) $ 的。

思考优化，推一波式子。设第 $ i $ 重复段起始位置前已有 $ pre_i $ 位数，$ x_i $ 的位数为 $ len_i $。则答案为：

$$ \displaystyle\sum_{i=1}^{n}{x_i\times 10^{pre} \times \displaystyle\sum_{j=1}^{y_i}{(10^{len_i})^{j-1}} } $$

实际上可以发现，后面求和求的是一个等比数列的和，只要我们快速算出这个和即可。设 $ sum(1,n)=\displaystyle\sum_{i=1}^{n}{q^{i-1}} $，根据高中数学知识可得求和公式：

$$ sum(1,n)=\frac{1-q^n}{1-q} $$

这里有个除法，只要我们求出对应模意义下的乘法逆元即可，时间复杂度为 $ O(n\log_2{n}) $。

但是，题目给定的模数可**不一定是质数**，~~我赛时没看到直接挂没了，尽管你在 AT 可以获得几乎满分~~。思考如何去掉除法。

考虑给定的 $ y_i $ 的数据范围，当我们没有思路的时候就想想可不可以分块做。可以想到一种分治的做法，这种做法类似二分，后半部分的贡献可以由前半部分快速推出。具体的式子是这样：

$$ sum(1,n)=\begin{cases}
   (1+(10^{len})^{\frac{n}{2}})\ sum(1,\frac{n}{2})  &\text{if } n\equiv0 (\bmod 2) \\
   (1+(10^{len})^{\frac{n}{2}})\ sum(1,\frac{n}{2})+(10^{len})^{n-1} &\text{if } n\equiv1 (\bmod 2)
\end{cases} $$

看起来很像快速幂，最后的时间复杂度是 $ O(n\log_2^2{n}) $。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
typedef pair<int,int> PII;
const int N=1e4+10;
int n,p,len[N],q[N];
long long ans;
PII ar[N];
long long qpow(long long y,long long z){
	long long res=1;
	while(z){
		if(z&1)
			res=(res*y)%p;
		y=(y*y)%p;
		z>>=1;
	}
	return res;
}
long long sov(long long d,long long y){
	if(y==1)
		return 1;
	long long res;
	res=sov(d,y>>1);
	res=(res+res*qpow(d,y>>1))%p;
	if(y&1)
		res=(res+qpow(d,y-1))%p;
	return res;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)
		scanf("%d%d",&ar[i].first,&ar[i].second);
	scanf("%d",&p);
	long long pre=1;
	for(int i=1;i<=n;++i){
		int tem=ar[i].first;
		while(tem){
			tem/=10;
			++len[i];
		}
		q[i]=qpow(10,len[i]);
	}
	for(int i=n;i>=1;--i){
		ans=(ans+ar[i].first*pre%p*sov(q[i],ar[i].second))%p;
		pre=pre*qpow(q[i],ar[i].second)%p;
	}
	printf("%lld\n",ans);
}
```


---

