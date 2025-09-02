# [USACO07CHN] Summing Sums G

## 题目描述

$N$ 头奶牛（$1 \leq N \leq 5 \times 10^4$）刚刚学习了不少密码学知识，终于，她们创造出了属于奶牛的加密方法，由于她们经验不足，她们的加密方法很简单：

第 $i$ 头奶牛掌握着密码的第 $i$ 个数字，起始的时候是 $C_i$（$0 \leq C_i \lt 9 \times 10^7$）。加密的时候，第 $i$ 头奶牛会计算其他所有奶牛的数字和，并将这个和对 $98\,765\,431$ 取模。在所有奶牛计算完成后，每头奶牛都会用自己算的数字代替原来的数字。即，

$$
C_{i}'=(\sum_{k=1}^NC_k-C_i) \bmod 98\,765\,431
$$

这样，她们完成了一次加密。

在十一月，奶牛们把这个加密方法告诉了驼鹿卡门。卡门想了一会后，说：“你们的算法还很原始，为了达到加密效果，你们要重复这个加密过程 $T$ 次（$1 \leq T \leq 1\,414\,213\,562$）”。

奶牛们很懒，于是就把这个任务交给了你。

## 说明/提示

每次加密后的 $C_i$ 如下：

| 次数 | $C_1$ | $C_2$ | $C_3$ |
| ---- | ----- | ----- | ----- |
| 0    | 1     | 0     | 4     |
| 1    | 4     | 5     | 1     |
| 2    | 6     | 5     | 9     |
| 3    | 14    | 15    | 11    |
| 4    | 26    | 25    | 29    |

## 样例 #1

### 输入

```
3 4
1
0
4```

### 输出

```
26
25
29
```

# 题解

## 作者：Dehydration (赞：6)

### 前言：

简单的矩阵乘法。

ps：[题目](https://www.luogu.com.cn/problem/P6202)。


### 思路：

令原数和加密后的数构成一个矩阵，设矩阵 $A$ 为 
$\begin{bmatrix}c_i&sum-c_i\end{bmatrix}$，则加密一次后的矩阵 $A'$ 为 $\begin{bmatrix}sum-c_i&(n-1)\times sum-(sum-c_i)\end{bmatrix}$，因为显而易见所有数加密一次后总和变为原来的 $n-1$ 倍。

推出 $A$ 乘矩阵 $\begin{bmatrix}0&n-1\\1&n-2\end{bmatrix}$ 可以得到 $A'$，设这个矩阵为 $B$。

按照这个规律，加密 $T$ 次和 $T+1$ 次构成的矩阵为 $A\times B^T$。

对于每个数，处理出矩阵 $A$，就可以用快速幂解决 $A\times B^T$，得到加密 $T$ 次的数。

**记住，不开 long long 见祖宗！！！**


### 代码：

```
#include <bits/stdc++.h>
#define MOD 98765431
typedef long long lint;
struct matrix
{
    int x , y;
    lint num[3][3];
    matrix operator*(const matrix a) const
    {
        matrix t;
        int i , j , k;
        memset(t.num , 0 , sizeof(t.num));
        t.x = x , t.y = a.y;
        for(i = 1 ; i <= t.x ; i ++ )
            for(j = 1 ; j <= t.y ; j ++ )
                for(k = 1 ; k <= y ; k ++ )
                    t.num[i][j] = (t.num[i][j] + num[i][k] * a.num[k][j]) % MOD;
        return t;
    }
}a , b;
lint c[50010];
matrix qpow(matrix a , int b)
{
    matrix t;
    int i;
    t.x = a.x , t.y = a.y;
    memset(t.num , 0 , sizeof(t.num));
    for(i = 1 ; i <= t.x ; i ++ )
        t.num[i][i] = 1;
    while(b)
    {
        if(b & 1)
            t = t * a;
        a = a * a;
        b >>= 1;
    }
    return t;
}
typedef long long LL;
inline LL read()
{
	register LL x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}

int main()
{
    int n , t , i;
    lint sum = 0;
    n=read(),t=read(); 
    for(i = 1 ; i <= n ; i ++ )
        c[i]=read() , sum = (sum + c[i]) % MOD;
    b.x = b.y = 2;
    b.num[1][1] = 0 , b.num[1][2] = n - 1 , b.num[2][1] = 1 , b.num[2][2] = n - 2;
    b = qpow(b , t);
    a.x = 1 , a.y = 2;
    for(i = 1 ; i <= n ; i ++ )
    {
        a.num[1][1] = c[i] , a.num[1][2] = (sum - c[i] + MOD) % MOD;
        printf("%lld\n" , (a * b).num[1][1]);
    }
    return 0;
}//别问我为什么要加快输，因为我要最优解
```


~~要看就看我的，我是最优解呢~~

c++14 + O2 = 最优解。

---

## 作者：皮卡丘最萌 (赞：3)

这~~不~~真是一个找规律的好题。

#### 前置知识：找规律，快速幂，乘法逆元。

仔细观察样例可以发现，在经过**偶数轮**之后，每个数的**增大的值相同**。

接下来给出~~简略的~~证明：

设$n$个数分别为$a_1,a_2,...,a_n$。

此时总和$S=a_1+a_2+...+a_n$。

设第$1$轮后，$n$个数分别为$b_1,b_2,...,b_n$。

则$b_1=S-a_1=a_2+a_3+...+a_n$，

$b_2=S-a_2=a_1+a_3+...+a_n$,

$...$

$b_n=S-a_n=a_1+a_2+...+a_{n-1}$。

此时总和$S'=b_1+b_2+...+b_n=(n-1)(a_1+a_2+...+a_n)=(n-1)S$。

设第$2$轮后，$n$个数分别为$c_1,c_2,...,c_n$。

则$c_1=S'-b_1=(n-2)(a_1+a_2+...+a_n)+a_1$，

则$c_2=S'-b_2=(n-2)(a_1+a_2+...+a_n)+a_2$，

$...$

则$c_n=S'-b_n=(n-2)(a_1+a_2+...+a_n)+a_n$。

此时$c_1-a_1=c_2-a_2=...=c_n-a_n=(n-2)(a_1+a_2+...+a_n)$。

这是经过$2$次操作后的结果，可以由此推出在经过**偶数轮**之后，每个数的**增大的值相同**。

------------

仔细观察样例可以发现，每经过$1$轮操作后，总和会**乘以$n-1$**。

这是因为每一轮都少加了一个$a_1,a_2,...,a_n$，也就是少加了一个$S$。

那么经过$m$轮之后，数字和就为$S×(n-1)^{m}$。

**一共增加了$S×[(n-1)^{m}-1]$**

根据之前的结论，每个数的**增大的值相同**，所以每个数增加$\dfrac{S×[(n-1)^{m}-1]}{n}$。

------------

注意到以上结论的前提是**经过了偶数次操作**。

那么如果一共要做奇数次，就在之前的基础上**再模拟一次**。

当然你也可以像神犇[Baylor](https://www.luogu.com.cn/user/213699)一样对奇数的情况另外找规律。

代码：
```pascal
const md=98765431;
var n,m,i:longint; s,sum:int64;
a:array[0..100001] of int64;
function kuai(m,p:int64):int64;
begin
if p=0 then exit(1);
if p=1 then exit(m);      //边界情况
kuai:=sqr(kuai(m,p>>1) mod md) mod md; 
if odd(p) then kuai:=kuai*m mod md;
end;                  //快速幂

begin
readln(n,m);
for i:=1 to n do
  begin
  read(a[i]); inc(s,a[i]);
  end;                 //读入数据并求和
s:=s mod md;
sum:=(kuai(n-1,m-m mod 2)-1)*s mod md*kuai(n,md-2) mod md;
                       //求出每个数的增加量
s:=0;
for i:=1 to n do
  begin
  a[i]:=(a[i]+sum) mod md;
  inc(s,a[i]);
  end;                    //对每个数进行累加
if odd(m) then 
  for i:=1 to n do writeln((s+md-a[i]) mod md) //奇数就再做一次
 else 
  for i:=1 to n do writeln(a[i] mod md);   //偶数就直接输出
end.
```


---

## 作者：KarL05 (赞：1)

由于本题目前只有唯一的找规律题解, 故提供一篇题解。

## 前置知识

1. 快速幂
2. 费马小定理求逆元
3. 等比数列求和

## 寻找思路

首先需要通过找规律寻取思路，明显操作$N$次后的总和和前一次总和有联系，即构成一个公比为$N-1$的等比数列。

然后根据这个思路，化简式子即可。本题解将会提供化简的详细步骤。有能力的读者请尝试自行化简。

## 推导

### 定义


$C{_i,_j} = $ $i$ 次转换后 $j$ 上的数字，显然输入中的数组为$C{_0}$。

$S{_i} = $ $\sum{C{_i}}$

### 推理
---

$C{_T,_k} = S{_{T-1}}-C{_{T-1},_k}$

$C{_T} = S{_{T-1}}-(S{_{T-2}}-C{_{T-2},_k})$

$C{_T} = S{_{T-1}}-(S{_{T-2}}-(S{_{T-3}}-C{_{T-3},_k}))$

$C{_T} = S{_{T-1}}+S{_{T-2}}-S{_{T-3}}+S{_{T-4}}-  \cdots ± C{_0,_k}$

$C{_T} = (S{_{T-1}} + S_{T-3} + S_{T-5}\cdots) - (S{_{T-2}} + S_{T-4} + S_{T-6}\cdots) ± C{_0,_k}$

$C{_T} = \frac{S{_{T+1}}-S{_{0/1}}}{(N-1)^2-1} - \frac{S{_{T}}-S{_{0/1}}}{(N-1)^2-1} - C{_0,_k}$ 

分奇偶性讨论即可。特判公比为$1$即可。

代码

```cpp
#include<iostream>
typedef long long ll;
using namespace std;

ll N;
ll T, S0, S1;
const int maxn = 5e4+5;
const ll MOD = 98765431;
ll C[maxn];

ll pow (ll a, ll b,ll mod) {
    if (b==1) return a;
    if (b%2==1) {
        return ((a%mod)*pow(a,b-1,mod)%mod)%mod;
    }
    else {
        ll tot = pow(a,b/2,mod)%mod;
        return tot*tot%mod;
    }
}
void prepare () {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
}

int main () {
    prepare();
    cin>>N>>T;
    for (int i=1;i<=N;i++) {cin>>C[i];S0=(S0+C[i])%MOD;}
    ll S1 = S0*(N-1)%MOD;
    ll ST = S0*pow(N-1,T,MOD)%MOD;
    ll ST1 = S0*pow(N-1,T+1,MOD)%MOD;
    ll dec = N*N-N-N;
    ll dem = pow(dec,MOD-2,MOD)%MOD;
    if (N==2) {
        if ((T+1)%2) {
            ll ans = (ST1-S1+MOD)%MOD;
            ans = (MOD+ans-(ST-S0+MOD))%MOD;
            for (int i=1;i<=N;i++) cout<<(ans+C[i])%MOD<<endl;
        }
        else {
            ll ans = (ST1-S0+MOD)%MOD;
            ans = (MOD+ans-(ST-S1+MOD))%MOD;
            for (int i=1;i<=N;i++) cout<<(ans-C[i]+MOD)%MOD<<endl;
        }
    }
    if ((T+1)%2) {
        ll ans = (((ST1-S1+MOD)%MOD)*dem)%MOD;
        ans = (MOD+ans-(((ST-S0+MOD)%MOD)*dem%MOD))%MOD;
        for (int i=1;i<=N;i++) cout<<(ans+C[i])%MOD<<endl;
    }
    else {
        ll ans = (((ST1-S0+MOD)%MOD)*dem)%MOD;
        ans = (MOD+ans-(((ST-S1+MOD)%MOD)*dem%MOD))%MOD;
        for (int i=1;i<=N;i++) cout<<(ans-C[i]+MOD)%MOD<<endl;
    }
}
```



---

## 作者：lostxxx (赞：0)

# 题目分析

首先，我们可以设 $\sum_{i=1}^{N}c_i=S$，我们发现，对于一个答案 $c_i$，经过一次变换后会变为 $S-c_i$。那么我们可以构造一个矩阵 $A$ 为 $\begin{bmatrix}c_i\\S\end{bmatrix}$，然后根据模拟可得转移矩阵 $B$ 为 $\begin{bmatrix}-1 & 1\\0 & n-1\end{bmatrix}$。那么对于单个数 $c_i$ 的答案就很显然易见了。

答案就是 $A \times B^T$，但是注意一定要开 `long long`，而且因为转移矩阵中有 $-1$ 这一项，所以一定要先加上 $p$ 再对 $p$ 取模。而且要多取模。

代码如下。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,t;
ll c[200100];
ll sum=0;
struct node{
	ll a[10][10];
};
const ll p=98765431;
node operator * (node a,node b){
	node c;
	for (int i=1;i<=2;i++)
		for (int j=1;j<=2;j++)
			c.a[i][j]=0;
	for (int i=1;i<=2;i++)
		for (int j=1;j<=2;j++)
			for (int k=1;k<=2;k++)
				(c.a[i][j]+=(a.a[i][k]*b.a[k][j]+p)%p)%=p;
	return c;
}
node qumi(node a,ll b){
	node res;
	for (int i=1;i<=2;i++)
		for (int j=1;j<=2;j++)
			res.a[i][j]=0;
	for (int i=1;i<=2;i++)
		res.a[i][i]=1;
	while(b){
		if (b&1)
			res=res*a;
		a=a*a;
		b>>=1;
	}
	return res;
}
int main(){
	cin>>n>>t;
	for (int i=1;i<=n;i++){
		cin>>c[i];
		(sum+=c[i])%=p;
	}
	node la;
	for (int i=1;i<=2;i++)
		for (int j=1;j<=2;j++)
			la.a[i][j]=0;
	la.a[1][1]=-1,la.a[1][2]=1,la.a[2][1]=0,la.a[2][2]=n-1;
	la=qumi(la,t);
	for (int i=1;i<=n;i++){
		node ans;
		for (int i=1;i<=2;i++)
			for (int j=1;j<=2;j++)
				ans.a[i][j]=0;
		ans.a[1][1]=c[i],ans.a[2][1]=(sum)%p;
		cout<<(la*ans).a[1][1]%p<<endl;
	}
}
```

---

## 作者：Gaode_Sean (赞：0)

令 $S_n=\sum_{i=1}^n c_i$

通过找规律可得（不必作过多阐述）：

$ans_{i,T}=\frac{S_n \times (n-2)((n-1)^T-1)}{(n-1)^2-1}+c_i=\frac{S_n \times (n-2)((n-1)^T-1)}{n^2-2n}+c_i=\frac{S_n \times ((n-1)^T-1)}{n}+c_i$

注意逆元。

由费马小定理可得 $a^{-1} \equiv a^{p-2} (\ mod \ p)$，由此可以解决有关 $\frac{1}{n}$ 的取余问题。

## AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=5e4+1;
ll n,T,t,a[N],sum,ans[N],mod=98765431;
ll power(ll x,ll y)
{
	ll ans=1;
	for(;y;y>>=1){
		if(y&1) ans=(ans*x)%mod;
		x=(x*x)%mod;
	}
	return ans;
}
int main()
{
	scanf("%lld%lld",&n,&T);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		a[i]%=mod;
		sum=(sum+a[i])%mod;
	} 
	if(T%2==1) t=T-1;
	else t=T;
	for(int i=1;i<=n;i++){
		ans[i]=(power(n-1,t)-1)%mod*sum%mod+(a[i]*n%mod)%mod;
		ans[i]=(ans[i]*power(n%mod,mod-2))%mod;
	}
	sum=0;
	for(int i=1;i<=n;i++) sum=(sum+ans[i])%mod;
	if(T%2==1) for(int i=1;i<=n;i++) ans[i]=((sum-ans[i])+mod)%mod;
	for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:P6202](https://www.luogu.com.cn/problem/P6202)

* **【解题思路】**

定义 $c_{i,j}$ 为第 $i$ 个数经过 $j$ 次变换的结果，$s_j=\sum\limits_{i=1}^nc_{i,j}$。

我们对于 $c_{i,j}$ 暴力展开，有

$$
\begin{aligned}
c_{i,j}&=\sum_{k=1}^nc_{k,j-1}-c_{i,j-1}\\
&=s_{j-1}-c_{i,j-1}\\
&=s_{j-1}-\left(\sum_{k=1}^nc_{k,j-2}-c_{i,j-2}\right)\\
&=s_{j-1}-s_{j-2}+c_{i,j-2}\\
&=s_{j-1}-s_{j-2}+s_{j-3}-c_{i,j-3}\\
&=(-1)^jc_{i,0}+\sum_{k=1}^j(-1)^{k-1}s_{j-k}\\
&=(-1)^jc_{i,0}+\sum_{k=0}^{j-1}(-1)^{j-k+1}s_k\\
&=(-1)^jc_{i,0}-\sum_{k=0}^{j-1}(-1)^{j}(-1)^ks_k\\
&=(-1)^j\left(c_{i,0}-\sum_{k=0}^{j-1}(-1)^ks_k\right)\\
\end{aligned}
$$

然后我们发现推不下去了。还有一个关于 $s_j$ 的式子：

$$s_j=\sum_{i=1}^nc_{i,j}=\sum_{i=1}^n(s_{j-1}-c_{i,j-1})=ns_{j-1}-\sum_{i=1}^nc_{i,j-1}=(n-1)s_{j-1}\implies s_{j}=(n-1)^js_0$$

把它带进去然后套等比数列求和公式：

$$
\begin{aligned}
c_{i,j}&=(-1)^j\left(c_{i,0}-\sum_{k=0}^{j-1}(-1)^ks_k\right)\\
&=(-1)^j\left(c_{i,0}-\sum_{k=0}^{j-1}(-1)^k(n-1)^ks_0\right)\\
&=(-1)^j\left(c_{i,0}-s_0\sum_{k=0}^{j-1}(1-n)^k\right)\\
&=(-1)^j\left(c_{i,0}+s_0\frac{(1-n)^j-1}{n}\right)
\end{aligned}
$$

* **【代码实现】**

```cpp
#include <iostream>
#include <array>

using namespace std;

long long fast_pow(long long base,long long exp,long long moder)
{
    long long result;
    for(result=1;exp;exp&1?result=result*base%moder:true,base=base*base%moder,exp>>=1);
    return result;
}
inline long long inv(long long num,long long prime)
{
    return fast_pow(num,prime-2,prime);
}

array<int,50000> nums;
const int prime=98765431;

int main(int argc,char *argv[],char *envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt,target,sum_n=0;
	cin>>cnt>>target;
	for(int i=0;i<cnt;i++)
		cin>>nums[i],sum_n=(sum_n+nums[i])%prime;
	for(int i=0;i<cnt;i++)
		cout<<((target&1?-1:1)*(nums[i]+(fast_pow(1-cnt+prime,target,prime)-1+prime)%prime*inv(cnt,prime)%prime*sum_n%prime+prime)%prime+prime)%prime<<'\n';
 	return 0;
}
```

---

## 作者：Purslane (赞：0)

## Solution

找规律题 . 一开始以为模数是 $987654321$ 想了半天 ......

其实也不是找规律 . 很显然要把每一个数单独看 , 看他对最终答案的贡献 .

假设这是第一个数 .  对于每个答案的贡献为 $k_i$ .

发现经过一轮 , $\sum k_i$ 会乘以 $n-1$ . 那么第 $T$ 轮后贡献总和为 $(n-1)^T$ .

我们可以归纳的证明 : 奇数次后 , $k_1$ 比其余的大 $1$ ; 偶数次后 , $k_1$ 比其余的少 $1$ .

那么既然知道了 $\sum k_i$ ,就可以计算出每个 $k_i$ 啦 !

code :

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e4+10,MOD=98765431;
int n,t,c[MAXN],ans[MAXN];
int qpow(int base,int p) {
	int ans=1;
	while(p) {
		if(p&1) ans*=base,ans%=MOD;
		base*=base,base%=MOD,p>>=1;
	}
	return ans;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>t;ffor(i,1,n) cin>>c[i];
	int sum=qpow(n-1,t);
	if(t&1) {
		int tot=0,mul=(sum+1)*qpow(n,MOD-2)%MOD;
		ffor(i,1,n) tot+=c[i],tot%=MOD;
		tot*=mul,tot%=MOD;
		ffor(i,1,n) cout<<((tot-c[i])%MOD+MOD)%MOD<<'\n';
	}
	else {
		int tot=0,mul=(sum-1)*qpow(n,MOD-2)%MOD;
		ffor(i,1,n) tot+=c[i],tot%=MOD;
		tot*=mul,tot%=MOD;
		ffor(i,1,n) cout<<((tot+c[i])%MOD+MOD)%MOD<<'\n';
	}
	return 0;
}
```



---

