# [PA 2015] Fibonacci

## 题目背景

更新：输出任意满足条件的 $k$ 即可，感谢 @[Karry5307](https://www.luogu.com.cn/user/60990) 的修正和 spj。

## 题目描述

众所周知，斐波那契数列 $F$ 满足：
$$F_0=0,F_1=1,F_m=F_{m-1}+F_{m-2}(2\le m)$$
现在给出一个数字串 $S$，请找到一个**最小**的 $k$ 使得 $F_k$ 以 $S$ 为结尾。

## 说明/提示

对于 $100\%$ 的数据，$S$ 的长度不超过 $18$，$0\le k<10^{100}$。

## 样例 #1

### 输入

```
025```

### 输出

```
1525```

# 题解

## 作者：metaphysis (赞：3)

解决本题需要一定的数论知识，核心是以下结论：给定一个整数 $m$，斐波那契数列 $F_n$ 模 $m$ 具有最小循环节。例如当 $m=2$ 时，$F_n$ 模 $2$ 的值为：
$$0,1,1,0,1,1,0,1,1,0,1,1,...$$
容易得知，当 $m=2$ 时，最小循环节长度为 $3$。

对于本题，有相关的两个结论：

（1）给定正整数 $m$，将 $m$ 进行素因子分解：
$$m=\prod_{i=1}^s{{p_i^{k_i}}}$$
其中 $p_i$ 为素数，令 $c_i$ 表示 $F_n$ 模 ${p_i^{k_i}}$ 的最小循环节长度，$C$ 是 $F_n$ 模 $m$ 的最小循环节长度，则有
$$C=\operatorname{lcm}(c_1,c_2,...,c_s)$$
其中 $\operatorname{lcm}$ 表示最小公倍数。

（证明参见：[Charles W. Campbell II, The Period of the Fibonacci Sequence Modulo j, 2007](https://gradprogram.math.arizona.edu/~ura-reports/071/Campbell.Charles/Final.pdf)）

（2）若 $p$ 为素数，$F_n$ 模 $p^m$ 的最小循环节长度为 
$G(p)×p^{m-1}$，其中 $G(p)$ 表示 $F_n$ 模 $p$ 的最小循环节长度。


通过枚举斐波那契数列可以容易得到：
$$G(2)=3,G(5)=20$$
再结合上述两个结论，有：

$$G(10^m)=6×10^m$$

对于本题来说，由于给定的 $S$ 的最大长度不超过 $18$ 位，如果给定的 $k$ 存在，则有 $0<=k<=6×10^{18}$。

显然通过朴素的计算 $F_n$，然后比对末尾若干位的方法不可行，因为 $k$ 可能很大（参见：[高精度加法这部分有问题，谁看一下？](https://www.luogu.com.cn/discuss/show/260271?page=1)）。

一种可行的方法是使用回溯法，从低位到高位逐位枚举 $k$ 的各个数位上的数值，以期发现符合要求的 $k$。初看该方法似乎不可行，因为每个数位有 $0-9$ 这 $10$ 种可能，总的可能性最大为 $10^{18}$，但由于是逐位枚举，对于每个数位来说，符合之前及当前数位模结果的数字数量是非常少的，因此可以很快得到结果。在枚举的过程中需要充分利用结论 $G(10^m)=6×10^m$ 
以便加快搜索速度，即按照 $10$ 的幂的最小循环节逐次累加。

举个例子，如果给定输入：

```
12345
```
个位是 $5$，由于 $F_n$ 模 $10$ 的最小循环节为 $60$，则从 $0$ 枚举到 $60$，确定一个 $k$，使得 $F_k$ 模 $10$ 的末位是 $5$，容易知道满足要求的最小 $k=5$，即 $F_5=5$，则当 $k=60×i+5(0<=i)$ 时，能够保证 $F_k$ 的末位是 $5$；接着确定十位，由于给定的 $S$ 十位为 $4$，则逐次枚举 $k=60×i+5(0<=i<=9)$，使得 $F_k$ 模 $100$ 为 $45$，得到 $k=245$ 时，$F_{245}$ 模 $100$ 为 $45$；接着确定百位，由于给定的 $S$ 百位为 $3$，逐次枚举 $k=600×i+245(0<=i<=9)$，使得 $F_k$ 模 $1000$ 为 $345$，得到 $k=1345$ 时，$F_{1345}$ 模 $1000$ 为 $345$；...，依此类推，最终可得 $k=149845$（注意，中间结果仅为示例，实际可能并不符合）。

以下是参考解题方案（编码未优化，加
 $O2$ 优化 $Accepted$）：
```cpp
// Fibonacci
// Luogu ID: 5580
// Verdict: Accepted
// Submission Date: 2020-10-01
// UVa Run Time: 2.80s

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ULL;

int found = 0, K;
ULL R, MODULO[20] = {0}, POW[20], CYCLE_OF_TEN[20];

struct matrix
{
    ULL cell[2][2];
    matrix(ULL a = 0, ULL b = 0, ULL c = 0, ULL d = 0)
    {
        cell[0][0] = a, cell[0][1] = b, cell[1][0] = c, cell[1][1] = d;
    }
} one(1, 1, 1, 0), zero(0, 0, 0, 0);

// 注意防止溢出。
ULL multiplyMod (ULL a, ULL b, ULL c)
{  
    ULL r = 0;  
    for ( ; b; b >>= 1)  
    {  
        if (b & 1)  
        {  
            r += a;
            if (r >= c) r -= c;  
        }  
        a <<= 1;
        if (a >= c) a -= c;  
    }  
    return r;  
}  

matrix multiply(const matrix &a, const matrix &b, ULL MOD)
{
    matrix r;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
            {
                r.cell[i][j] += multiplyMod(a.cell[i][k], b.cell[k][j], MOD);
                r.cell[i][j] %= MOD;
            }
    return r;
}

matrix matrixPow(ULL k, ULL MOD)
{
    if (k == 0) return zero;
    if (k == 1) return one;
    matrix r = matrixPow(k >> 1, MOD);
    r = multiply(r, r, MOD);
    if (k & 1) r = multiply(r, one, MOD);
    return r;
}

void dfs(int d, ULL k)
{
    if (found) return;
    if (d == K) { R = k; found = 1; return; }
    for (int i = 0; i < 10; i++)
    {
        // 当前末 d 位已经满足条件，寻找满足末 d+1 位的 k
        ULL nextk = (k + i * CYCLE_OF_TEN[d]) % CYCLE_OF_TEN[d + 1];
        // 检查 nextk 是否符合条件
        ULL fn = matrixPow(nextk, POW[d]).cell[0][0];
        if (fn == MODULO[d]) dfs(d + 1, nextk);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string S; cin >> S;
    if (stoll(S) == 0) { cout << "0\n"; return 0; }
    reverse(S.begin(), S.end());
    K = S.length();
    // MODULO[i] 表示 S 所对应的整数模 10^{i+1} 的结果
    // POW[i] 表示 10^{i+1}
    // CYCLE_OF_TEN[i] 表示 F_k 模 10^{i+1} 的最小循环节
    MODULO[0] = S[0] - '0', POW[0] = 10, CYCLE_OF_TEN[0] = 60;
    for (int i = 1; i <= K + 1; i++) POW[i] = POW[i - 1] * 10, CYCLE_OF_TEN[i] = CYCLE_OF_TEN[i - 1] * 10;
    for (int i = 1; i < K; i++) MODULO[i] = MODULO[i - 1] + (S[i] - '0') * POW[i - 1];
    // for (int i = 0; i < K; i++) cout << POW[i] << ' ' << MODULO[i] << '\n';
    // 对于个位数来说，其最小循环节为 60
    for (int k = 0; k < 60; k++) dfs(0, k);
    if (found) cout << (R + 1) << '\n';
    else cout << "NIE\n";

    return 0;
}
```

---

## 作者：7KByte (赞：2)

难度评分偏低。。。

众所周知 fibonacci 数列有循环节。

对于特殊的模数$P=10^x$，循环节长度为 $6\times P$。

既然是找循环，我们可以借鉴一道普及组的[题目](https://www.luogu.com.cn/problem/P1050)的思路。

从最低位开始考虑，在最个位循环后考虑十位，在个位和十位都循环后考虑百位。

各位的循环节长度为$60$，我们先直接求出Fibonacci数列的前$60$个元素，对于各位与给定串相同的元素我们作为底数。

然后我们从底数开始搜索，每次向高位扩展一位。由于前面已将处理完的位数的循环节为$6\times 10^x$，所以我们一次的步长为$6\times 10^x$。

举个例子，我们现在考虑十位，底数是第$3$个Fibonacci数，那么我就依次枚举第$63$，第$123$，第$183$等等。由于十位的循环长度为$600$，所以我们枚举到$543$就结束，没有符合条件的则说明无解。

这时候我们的最劣复杂度是$O(Ans)$。但由于当前数大概率是在半路就被说明无解，所以能过。

至于如何每次向前跳$6\times 10^x$步，我们可以预处理转移 $18$ 个矩阵，甚至矩阵快速幂都不需要

目前最优解，平均一个点$\rm 3 ms$。

另外其他的两份AC提交与网上唯一一份题解的结构非常类似，提出质疑。

代码奇丑

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
typedef long long ll;
const ll P = 1e18;
struct mat{
	ll a[2][2];
	mat(){memset(a,0,sizeof(a));}
};
ll mul(ll x,ll y){
	ll now=0;
	for(;y;y>>=1,x=(x<<1)%P)if(y&1)now=(now+x)%P;
	return now;
}
mat operator*(mat x,mat y){
	mat now;
	rep(i,0,1)rep(j,0,1)rep(k,0,1)now.a[i][j]=(now.a[i][j]+mul(x.a[i][k],y.a[k][j]))%P;
	return now;
}
mat operator^(mat x,ll y){
	mat now;now.a[0][0]=now.a[1][1]=1;
	for(;y;y>>=1,x=x*x)if(y&1)now=now*x;
	return now;
}
mat u[100];ll ten[100],c[100],k[100];int n;
char s[100];
void ins(ll &now,ll &pre,mat ad){
	ll t=now;
	now=mul(now,ad.a[0][0])+mul(pre,ad.a[1][0]);
	pre=mul(t,ad.a[0][1])+mul(pre,ad.a[1][1]);now%=P;pre%=P;
}
ll bit(ll x,int rc){
	//cout<<x<<" "<<rc<<" "<<ten[rc]<<endl;
	return (x/ten[rc])%10;
}
bool dfs(ll now,ll pre,int i,ll sum){
	//cout<<now<<" "<<pre<<" "<<i<<" "<<n<<" "<<sum<<endl;
	if(i>=n){printf("%llu\n",sum);return true;}
	ll cnt=ten[i]*6;
	rep(j,0,9){
		//cout<<j<<endl;
		if(bit(now,i)==k[i])
			if(dfs(now,pre,i+1,sum))return true;
		sum+=cnt;ins(now,pre,u[i]);
	}
	return false;
}
int main()
{
	ten[0]=1;u[0].a[0][0]=u[0].a[0][1]=u[0].a[1][0]=1;
	u[0]=u[0]^6; 
	rep(i,1,18){
		ten[i]=ten[i-1]*10;
		u[i]=u[i-1]^10;
		//putchar('\n');putchar('\n');
		//rep(x,0,1){rep(y,0,1)printf("%lld ",u[i].a[x][y]);putchar('\n');}
	}
	//rep(i,1,18)printf("%lld ",ten[i]);putchar('\n');
	u[0].a[0][0]=u[0].a[0][1]=u[0].a[1][0]=1;u[0].a[1][1]=0;
	scanf("%s",s);n=strlen(s);
	//cout<<n<<endl;
	rep(i,0,n-1)k[i]=s[n-i-1]-'0';
	c[0]=0;c[1]=1;//puts(s);
	rep(i,2,60)c[i]=(c[i-1]+c[i-2])%P;//,cout<<c[i]<<endl;
	//cout<<(int)s[0]<<endl;
	rep(i,1,60){
		//cout<<c[i]<<" "<<c[i]%10<<" "<<k[0]<<endl;
		if(c[i]%10==k[0]){
			if(dfs(c[i],c[i-1],1,i))return 0;
		}
	}
	puts("NIE");
	return 0;
}
/*
025
*/
```

---

