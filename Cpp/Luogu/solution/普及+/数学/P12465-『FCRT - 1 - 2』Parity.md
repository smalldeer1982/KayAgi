# 『FCRT / 1 - 2』Parity

## 题目背景

CuteChat 发现自己乘坐的是 $\color{#d20000}01\color{black}010$ 号车，他来到了 $1$ 号车厢，因此看到了 $\color{#d20000}{010101}$ 的车厢号。车厢号中有奇数个 $1$，而对应的列车号中有偶数个 $1$。

## 题目描述


定义函数 $\operatorname{Pari}(x)$，表示非负整数 $x$ 的二进制表示中 $1$ 的个数模 $2$ 的结果。例如，$\operatorname{Pari}(5) = 2 \bmod 2 = 0$。

给定一个长度为 $n$ 的二进制字符串 $S$，定义 $\text{Sub}(l, r)$ 表示 $S$ 的第 $l$ 到第 $r$ 个字符组成的二进制数转换成十进制数的值。

你需要处理 $q$ 次询问，每次询问给定两个参数 $l, r$，求解 $\displaystyle\sum_{x=0}^{\operatorname{Sub}(l, r)}\operatorname{Pari}(x)$，结果对 $998244353$ 取模。

注意字符串下标从 $1$ 开始。

## 说明/提示

#### 【样例 1 解释】

- 对于 $x = 1$，二进制为 $1$，$\text{Pari}(1) = 1$。
- 对于 $x = 2$，二进制为 $10$，$\text{Pari}(2) = 1$。
- 对于 $x = 4$，二进制为 $100$，$\text{Pari}(4) = 1$。
- 对于 $x = 7$，二进制为 $111$，$\text{Pari}(7) = 1$。
- 对于 $x = 8$，二进制为 $1000$，$\text{Pari}(8) = 1$。

因此，在 $0\sim10$ 的范围内，$\operatorname{Pari}$ 函数值为 $1$ 的有 $1, 2, 4, 7, 8$，这些数字的二进制表示中有奇数个 $1$。

- 对于第一次询问，$\operatorname{Sub}(3,6)=5$，故答案为 $3$。
- 对于第二次询问，$\operatorname{Sub}(2,5)=10$，故答案为 $5$。
- 对于第三次询问，$\operatorname{Sub}(1,2)=1$，故答案为 $1$。
- 对于第四次询问，$\operatorname{Sub}(5,5)=0$，故答案为 $0$。

#### 【数据范围】

**本题采用捆绑测试。**

对于所有测试数据，保证 $1\le n,q \le 2\times10^{5}$，$1\le l\le r\le n$，$S_i\in\{0,1\}$。所有输入数据均为非负整数或 $01$ 字符串。

- Subtask 1（15 Points）：$n,q\le20$。
- Subtask 2（10 Points）：$n\le20$。
- Subtask 3（15 Points）：$S$ 的所有字符都是 $1$。
- Subtask 4（10 Points）：$n,q\le10^3$，$S_r=1$。
- Subtask 5（15 Points）：$n,q\le10^3$。
- Subtask 6（15 Points）：$S_r=1$。
- Subtask 7（20 Points）：无特殊限制。


## 样例 #1

### 输入

```
6 4
010101
3 6
2 5
1 2
5 5```

### 输出

```
3
5
1
0```

# 题解

## 作者：lilong (赞：10)

应该是最好想的做法了。

注意到对于任意非负整数 $k$，$2k$ 和 $2k+1$ 两个数的二进制下 $1$ 的出现次数必定一奇一偶，即贡献和为 $1$。为什么？因为一个偶数的二进制最后一位一定是 $0$，比它大 $1$ 的奇数一定是最后一位变成 $1$（一定不会进位），故 $1$ 的个数刚好相差一，得证。于是这道题就变为判断原题中的 $\text{Sub}(l,r)$ 的奇偶性并分类讨论即可。

时间复杂度 $O(n+q)$，代码中有注释。


```cpp
#include<iostream>
#include<cstdio>
#define int long long
#define N 500010
#define mod 998244353
#define inv2 (mod+1)/2
using namespace std;
string s;
int n,q,p2[N],a[N],s1[N],s2[N];
int gt(int l,int r){//返回原题中的 Sub(l,r)
    if(l>r)return 0;
    return ((s1[r]-s1[l-1]*p2[r-l+1])%mod+mod)%mod;
}
int pd(int l,int r){//原题中的 Pari 的作用
    return (s2[r]-s2[l-1])%2;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int l,r;
    cin>>n>>q;
    cin>>s;
    p2[0]=1;
    for(int i=1;i<=n;i++)//预处理 2 的幂
        a[i]=s[i-1]-'0',p2[i]=p2[i-1]*2%mod;
    for(int i=1;i<=n;i++){
        s1[i]=(s1[i-1]*2%mod+a[i])%mod;//前 i 个位置构成的二进制数转为十进制数
        s2[i]=s2[i-1]+a[i];//前 i 个位置 1 的个数
    }
    while(q--){
        cin>>l>>r;
        if(a[r])
            cout<<(gt(l,r-1)+1)%mod<<'\n';//除以 2 相当于去掉二进制下最后一位，这里要上取整，故要加上 1
        else
            cout<<(gt(l,r-1)+pd(l,r))%mod<<'\n';//由于多出最后一个偶数，需要另外判断
    }
    return 0;
}
```

---

## 作者：CuteChat (赞：4)

## 题解

### Subtask 1, 2

直接模拟即可。对于 Subtask 2，可以预处理所有可能的区间答案，方便快速查询。

### Subtask 3

当 $S$ 的所有字符都是 $1$ 时，$\operatorname{Sub}(l, r)$ 是一个全 $1$ 的二进制数。因此，我们需要计算所有在 $[0,2^{r-l+1})$ 之间的 $x$ 的 $\operatorname{Pari}(x)$ 之和。

这个问题相当于问，在 $r-l+1$ 位的二进制数中，选出偶数个 $1$ 的方案数量（选了当前这个二进制位就是 $1$，否则就是 $0$）。显然，$1$ 的个数为奇数和偶数的数各占一半，因此答案为 $2^{r-l}$（即 $\lfloor \frac{\operatorname{Sub}(l, r)}{2}\rfloor+1$）。

如果需要证明，注意到 $(1+(-1))^x$ 的二项式展开正好是偶数个的选法减去奇数个的选法，恰好为 $0$，故两者相等。


### Subtask 4, 5

对于一个给定的二进制数，我们可以将其拆分成若干段再合并计算，每段的形式是 $[k \times 2^m, (k+1) \times 2^m - 1]$。

例如，$10110$ 可以拆分为：
- $[0, 01111]$（即 $0$ 到 $15$）
- $[10000, 10011]$（即 $16$ 到 $19$）
- $[10100, 10101]$（即 $20$ 到 $21$）
- 单独的 $10110$（即 $22$）

之所以这样拆分，是因为每一段的 $\operatorname{Pari}(x)$ 之和可以通过区间长度除以 $2$ 再加一来计算，因为在去除掉二进制意义下的共同前缀之后，都转换成了 $S_i=1$ 性质。

因此，只需计算 $\lfloor \frac{\text{Sub}(l, r)}{2} \rfloor$，并额外判断最后一个数的 $\text{Pari}(x)$ 值。

不过需要注意的是，如果原数字是奇数，最后一个数字不会被单独分开，这一点需要额外注意。

这样，我们可以通过逐位拆分和区间计算，得到一个 $O(nq)$ 的做法。

### Subtask 6, 7

计算 $\text{Sub}(l, r)$ 的 $\text{Pari}$ 值可以通过前缀和优化。用 $Cnt_i$ 表示 $S$ 的前 $i$ 位有多少个 $1$，然后直接看 $Cnt_r - Cnt_{l-1}$ 的奇偶性即可。

现在的瓶颈在于如何计算 $\lfloor\frac{\operatorname{Sub}(l, r)}{2}\rfloor \bmod 998244353$，这个问题等同于问 $\operatorname{Sub}(l, r-1)\bmod 998244353$。解决这个问题我们也可以使用前缀和技巧。

定义 $Val_i$ 表示 $S$ 的前 $i$ 位组成的二进制数，递推公式为 $Val_i = Val_{i-1} \times 2 + S_i$。

对于区间 $[l, r]$，$\operatorname{Sub}(l, r)$ 可以通过 $Val_r - Val_{l-1} \times 2^{r-l+1}$ 计算得到。这样只需要额外预处理 $2$ 的幂次即可。

这样，我们可以在 $O(n+q)$ 的时间内处理所有询问。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, q, bas[200006], val[200006], cnt[200006];
const int p = 998244353;
char s[200006];

int slv(int i) {
	if (i % 2 == 1) {
		return (i + 1) / 2;
	} else {
		return i / 2 + (__builtin_parity(i) == 1); 
	}
}

signed main() {
	cin >> n >> q >> (s + 1);
	bas[0] = 1;
	for (int i = 1; i <= n; ++i) {
		bas[i] = bas[i - 1] * 2 % p; // 预处理 2 的幂次
		val[i] = (val[i - 1] * 2 + s[i] - '0') % p; // 预处理关于区间 Sub 的前缀和
		cnt[i] = cnt[i - 1] + s[i] - '0'; // 预处理关于区间 1 个数的前缀和
	}
	while (q--) {
		int l, r;
		cin >> l >> r;
		int res = (val[r - 1] - val[l - 1] * bas[r - l]);
		int flg = ((cnt[r] - cnt[l - 1]) % 2 == 0 && s[r] == '0');
		cout << ((res + 1 - flg) % p + p) % p<< "\n";
	}
	return 0;
}
```

---

## 作者：HZY1618yzh (赞：4)

题意
---
对于求从 $0$ 至 $\operatorname{Sub}(l,r)$ 的每一个 $x$，求 $\operatorname{Pari}(x)$。

思路
---
由于数据太恶心，所以需要找到一种方法快速求出 $\operatorname{Pari}(0)$ 到 $\operatorname{Pair}(\operatorname{Sub}(l,r))$ 的和还有 $\operatorname{Sub}(l,r)$。快速求和就要用到——前缀和。
#### $\operatorname{Sub}$ 的快速计算
定义 $x_i$ 为 $Sub(1,i)$。计算公式为上一位（$x_{i-1}$）的数乘 $2$（由于是二进制，所以位权是 $2$，因此乘 $2$）加上当前为的值（零或一，因为是二进制）。也就是 $x_i\gets x_{i-1}+s_i-'0'$。  
但 $x_i$ 仅仅只能计算 $Sub(1,i)$，但不能通过 $x_r-x_l$ 计算任意的 $Sub(l,r)$。需要用 $x_r-x_l\times2^{r-l+1}$（就是将 $x_l$ 乘以与其对应的位权）。但计算 $2^n$ 也很费时间，所以干脆也用 $pow2_i$ 数组存储 $2^i$。计算公式：$pow2_i\gets pow2_{i-1}\times2$。  
代码：
```cpp
int sub(int l,int r){
    if(l>r)return 0;
    return ((x[r]-x[l-1]*pow2[r-l+1])%mod+mod)%mod;
}
```
#### $\operatorname{Pari}$ 的快速计算
定义 $y_i$ 为从第一位到第 $i$ 为的一的数量。计算方法为上一位的加当前这位的数。计算公式：$y_i\gets y_{i-1}+s_i-'0'$。  
代码：
```cpp
int pari(int l,int r){
    return (y[r]-y[l-1])%2;
}
```
#### 预处理

```cpp
pow2[0]=1;
for(int i=1;i<=n;i++)
  pow2[i]=pow2[i-1]*2ll%mod,
  x[i]=(x[i-1]*2ll+s[i]-'0')%mod,
  y[i]=y[i-1]+s[i]-'0';
```
#### 主函数
由于 $2n$ 为 $2$ 的倍数，所以 $2n$ 的末尾为 $0$，因此 $2k$ 和 $2n+1$ 的一的个数相差 $1$，所以必定一个是奇数，一个是偶数。于是，本题变成求 $\operatorname{Sub}(l,r)$ 的奇偶性。  
代码：
```cpp
while(q--){
	cin>>l>>r;
	if(s[r]=='1') cout<<(sub(l,r-1)+1)%mod<<'\n';
	else cout<<(sub(l,r-1)+pari(l,r))%mod<<'\n';
}
```


代码实现
---

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,q,l,r,pow2[200001],x[200001],y[200001];
const int mod=998244353;
char s[200001];
int sub(int l,int r){
    if(l>r)return 0;
    return ((x[r]-x[l-1]*pow2[r-l+1])%mod+mod)%mod;
}
int pari(int l,int r){
    return (y[r]-y[l-1])%2;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>q>>(s+1);
	pow2[0]=1;
	for(int i=1;i<=n;i++)
		pow2[i]=pow2[i-1]*2ll%mod,
		x[i]=(x[i-1]*2ll+s[i]-'0')%mod,
		y[i]=y[i-1]+s[i]-'0';
	while(q--){
		cin>>l>>r;
		if(s[r]=='1') cout<<(sub(l,r-1)+1)%mod<<'\n';
		else cout<<(sub(l,r-1)+pari(l,r))%mod<<'\n';
	}
	return 0;
}
```

---

## 作者：39xiemy (赞：2)

首先很容易发现一个结论，当 $\operatorname{Sub}(l, r)$（下文记作 $x$）为 $2^k-1$ 时，答案恰为 $\frac{x+1}{2}$。

~~不太严谨的~~**证明**：这个问题相当于给出 $k$ 个空位，每个空位上填 $0$ 或 $1$，求填奇数个 $1$ 的方案数；也可以把这个问题看作求杨辉三角第 $k+2$ 行中奇数项之和。根据杨辉三角的性质，就可以证明这个结论。因此**填偶数个 $1$ 时的答案也为 $\frac{x+1}{2}$。**

那么对于其他数字，我们就可以把其拆分为以上情况。以 $x$ 等于二进制数 $11010$ 时举例，由于第四位（从 $0$ 开始）上有 $1$，可以拆成 $0\sim 1111$ 的答案和 $10000 \sim 11010$ 的答案，而前者与上面的结论吻合，可以直接计算。

而对于后者，再从下一个有 $1$ 的位拆分，同理可拆为 $10000\sim10111$ 和 $11000\sim 11010$，而对于前者，忽略掉第五位的 $1$ 后，可以把问题转化为求 $0\sim 111$ 中 $1$ 的个数为**偶数**的数的数量，也可以套用最初的结论。按这样一直拆下去便可以算出答案。

容易发现，在第 $k$ 位拆分后，增加的答案为 $2^{k-1}$，所以答案就是在 $x$ 上往右移一位，为 $\lfloor \frac{x}{2}\rfloor$。**特殊的**，当 $x$ 为偶数时，最后会剩下一个数 $x$，直接判断其是否有奇数个 $1$ 即可；当 $x$ 为奇数时，会剩下两个数 $x$ 和 $x-1$，由于一奇一偶，对答案的贡献必定为 $1$，然后就做完了。

用前缀和预处理后，时间复杂度 $O(n+q)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=200002,mod=998244353;
int n,q,pre[N],pow2[N],l,r,len,ans,sum[N];char s[N];
signed main()
{
    scanf("%lld%lld%s",&n,&q,s+1);
    pow2[0]=1,pre[0]=0;
    for(int i=1;i<=n;i++) pow2[i]=pow2[i-1]*2%mod,pre[i]=(pre[i-1]*2+(s[i]^48))%mod,sum[i]=sum[i-1]+(s[i]^48);
    //pre数组为前i个字符组成的十进制数，sum数组为前i个字符1的个数 
    while(q--)
	{
        scanf("%lld%lld",&l,&r),len=r-l;
        ans=(pre[r-1]-pre[l-1]*pow2[len]%mod+mod)%mod;
        if(s[r]=='1') ++ans,ans%=mod;
		else ans=(ans+(sum[r]-sum[l-1])%2)%mod; 
        printf("%lld\n",ans);
    }
    return 0;
}
```

---

## 作者：Phoenix_2010 (赞：2)

提供一个 $O(q \log n)$ 的矩阵优化 dp 的做法。

考虑设 $dp_{i,0/1}$ 表示 $[0,\operatorname{Sub}(i,r)]$ 中有多少个数 $x$ 二进制表示中 $1$ 的个数模 $2$ 等于 $0/1$。

考虑转移方程：

当 $a_i=0$ 时，因为 $x\le\operatorname{Sub}(i,r)$，所以这一位只能是 $0$，而且由于第 $i$ 位相等，$x$ 第 $[i+1,r]$ 位组成的数要小于等于 $\operatorname{Sub}(i+1,r)$。即 $dp_{i,0/1}=dp_{i+1,0/1}$。

当 $a_i=1$ 时，这一位可以是 $0$ 或 $1$。

如果是 $0$，那么第 $[i+1,r]$ 位只要满足奇偶性无论怎么取都可以，因为此时 $x$ 的第 $i$ 位更小。所以 $dp_{i,0/1}=2^{r-i-1}$。

如果是 $1$，那么和 $a_i=0$ 同理，$dp_{i,0/1}=dp_{i+1,1/0}$。

综上，
$$
dp_{i,0/1}=
\begin{cases}
dp_{i+1,0/1} & a_i=0\\
dp_{i+1,1/0}+2^{r-i-1} & a_i=1
\end{cases}
$$
即
$$
dp_{i,0}=!a_i\times dp_{i+1,0}+a_i\times dp_{i+1,1}+a_i\times \frac{2^r}{2^{i+1}}\\
dp_{i,1}=a_i\times dp_{i+1,0}+!a_i\times dp_{i+1,1}+a_i\times \frac{2^r}{2^{i+1}}
$$

特别地，$dp_{r,0}=1$，$dp_{r,1}=a_r$。答案即为 $dp_{l,1}$。

发现每次询问是把这个东西做一遍，而且 $dp_{i,0/1}$ 只和 $dp_{i+1,0/1}$ 有关。于是考虑矩阵优化，每次回答区间积。

考虑设矩阵
$
\begin{bmatrix}
dp_{i,0}&dp_{i,1}&1\\
0&0&0\\
0&0&0
\end{bmatrix}
$
表示答案。因为转移方程中有常数项（即和 dp 无关的项），所以要加一行一列表示常数。

根据转移方程，有转移矩阵
$
\begin{bmatrix}
!a_i&a_i&0\\
a_i&!a_i&0\\
a_i\times \frac{2^r}{2^{i+1}}&a_i\times \frac{2^r}{2^{i+1}}&1
\end{bmatrix}
$

所以对于每次询问只需要回答
$
\begin{bmatrix}
1&a_r&1\\
0&0&0\\
0&0&0
\end{bmatrix}
\times
\prod\limits_{i=l}^{r-1}
\begin{bmatrix}
!a_i&a_i&0\\
a_i&!a_i&0\\
a_i\times \frac{2^r}{2^{i+1}}&a_i\times \frac{2^r}{2^{i+1}}&1
\end{bmatrix}
$。

可以用线段树维护区间乘积。

但是这还稍微有一点问题。因为 $r$ 是在变化的，所以每次所以转移矩阵都要修改。不过我们可以把 $2^r$ 这一项放到初始矩阵的常数项中，即
$
\begin{bmatrix}
1&a_r&2^r\\
0&0&0\\
0&0&0
\end{bmatrix}
\times
\prod\limits_{i=l}^{r-1}
\begin{bmatrix}
!a_i&a_i&0\\
a_i&!a_i&0\\
\frac{a_i}{2^{i+1}}&\frac{a_i}{2^{i+1}}&1
\end{bmatrix}
$
，这样转移矩阵只和 $i$ 有关了。


```cpp
#include<bits/stdc++.h>
#define mid (l+r>>1)
using namespace std;
typedef long long ll;
const int N=2e5+5,mod=998244353,inv=499122177;
struct node{ll c[3][3];};
node operator * (node a,node b){node ans;memset(ans.c,0,sizeof(ans.c));for(int i=0;i<=2;i++) for(int j=0;j<=2;j++) for(int k=0;k<=2;k++) (ans.c[i][j]+=a.c[i][k]*b.c[k][j])%=mod;return ans;}
struct{node val;}t[4*N];
int n,q,a[N];char c[N];ll pw[N],ipw[N];
inline void pushup(int p){t[p].val=t[p<<1].val*t[p<<1|1].val;}
inline void build(int p,int l,int r)
{
	if(l==r)
	{
		t[p].val.c[0][0]=!a[l],t[p].val.c[0][1]=a[l],t[p].val.c[1][0]=a[l],t[p].val.c[1][1]=!a[l];
		t[p].val.c[2][0]=a[l]*ipw[l+1],t[p].val.c[2][1]=a[l]*ipw[l+1],t[p].val.c[2][2]=1;
		return;
	}
	build(p<<1,l,mid);build(p<<1|1,mid+1,r);
	pushup(p);
}
inline node query(int p,int l,int r,int ql,int qr)
{
	if(l==ql&&r==qr) return t[p].val;
	if(qr<=mid) return query(p<<1,l,mid,ql,qr);
	else if(ql>mid) return query(p<<1|1,mid+1,r,ql,qr);
	else return query(p<<1,l,mid,ql,mid)*query(p<<1|1,mid+1,r,mid+1,qr);
}
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>q;
	pw[0]=ipw[0]=1;for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod,ipw[i]=ipw[i-1]*inv%mod;//预处理2的幂及其逆元
	for(int i=1;i<=n;i++) cin>>c[i],a[i]=c[i]-'0';
	build(1,1,n);
	while(q--)
	{
		int l,r;cin>>l>>r;
		node x;memset(x.c,0,sizeof(x.c));x.c[0][0]=1,x.c[0][1]=a[r],x.c[0][2]=pw[r];
		cout<<((l==r?x:x*query(1,1,n,l,r-1))).c[0][1]<<"\n";//l=r时要特判
	}
	return 0;
}
```

---

## 作者：粥2414 (赞：2)

# 题面描述
给你一个二进制串，从高位向低位排列。每次选出一个区间 $[l,r]$，求不超过它的并且二进制下含有奇数个 $1$ 的数的数量。
# 思路
以下称二进制下有奇数个 $1$ 的数为奇数，称目标区间表示的数为目标数。
## Subtask $1$
首先可以想到利用 `__builitn_popcount()`，快速判断一个数是否为奇数，然后预处理出从 $1$ 到整个串表示的数的前缀和，然后查询时将目标区间转化为十进制数直接输出结果。

时间复杂度 $O(2^n)$，空间复杂度 $O(2^n)$。
## Subtask $4$ & $5$ 
由 Subtask $1$ 已经可以发现，将其转化为十进制的写法是行不通的，必须从二进制下手。

我们只关心奇数的情况，所以可以考虑计算小于目标数的奇数有多少个。

发现只要将目标数的最高位变为 $0$，剩下的所有位置都可以任选 $1$ 或 $0$。设可选位置有 $k$ 位，每位可以任选 $1$ 或 $0$，由组合数的性质可知合法方案数为 $2^{k-1}$。然后钦定这一位为 $1$，枚举下一个 $1$ 即可。

那么我们可以预处理第 $i$ 个 $1$ 的下标 $p_i$，从高到低枚举每个 $1$，将答案加上 $2^{r-p_i-1}$ 即可。

注意如果最后一位为 $1$ 的话，需要特判，将答案加 $1$ 即可。因为如果不特判，这一位将会对应 $2^{-1}$，这显然是不行的，且这一位可以决定目标数的奇偶性，所以直接加 $1$ 即可。另外如果最后一位不为 $1$，且目标数为奇数，那么也需要特判加 $1$。

快速幂优化后时间复杂度 $O(n^2\log n)$，空间复杂度 $O(n)$。
## 正解
重新定义 $p_i$ 表示字符串第 $i$ 个 $1$ 到末尾的距离。即 $n-(\text{第 }i\text{ 个 }1\text{ 的下标})$。然后设目标区间包含第 $i$ 至第 $j$ 个 $1$（不含末位的 $1$），设 $k=n-r$，那么答案可以表示为：
$$
2^{p_i-k-1}+2^{p_{i+1}-k-1}+\cdots+2^{p_{j}-k-1}\\
=\frac{\sum_{x=i}^j 2^{p_x}}{2^{k+1}}
$$

那么我们直接预处理出前缀和，然后乘上 $2^{n-r+1}$ 的逆元即可。可以利用费马小定理求逆元，快速幂优化。别忘了特判。

预处理复杂度 $O(n\log n)$，查询复杂度 $O(q\log n)$，视 $n,q$ 同阶，总复杂度 $O(n\log n)$。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define ll long long
const int N=2e5+9,MOD=998244353;
int n,q;
string s;
ll sum[N];
ll cnt[N];
inline ll qp(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1)ans*=a,ans%=MOD;
		a=a*a%MOD,b>>=1;
	}
	return ans;
}
inline void init(){
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1];
		cnt[i]=cnt[i-1];
		if(s[i]=='1'){
			sum[i]+=qp(2,n-i);
			sum[i]%=MOD;
			cnt[i]++;
		}
	}
}
int main() {
	cin>>n>>q;
	cin>>s;
	s=' '+s;
	init();
	for(int i=1;i<=q;i++){
		ll l,r;
		cin>>l>>r;
		ll ne=qp(qp(2,n-r+1),MOD-2);
		ll ans=((sum[r-1]*ne%MOD)-(sum[l-1]*ne%MOD)+MOD)%MOD;
		if(s[r]=='1')ans++;
		else if((cnt[r]-cnt[l-1])%2==1)ans++;
		cout<<ans%MOD<<endl;
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：1)

看到自己同学不会，于是就来做了。由于我非常喜欢数据结构，所以用线段树通过了本题。

我们考虑先计算 $\operatorname{Sub}(l,r)=2^k-1(k\in \mathbb{N^*} )$ 的答案，也就是当 $s_l\dots s_r$ 都为 $1$ 的时候。这是简单的，通过打表可以发现答案为 $2^{r-l}$，此时二进制下模 $2$ 为 $0$ 的数和 $1$ 的数个数相等。

接着考虑一般情况，发现很难统计。正难则反，我们用 $2^{r-l}$ 减去 $x>\operatorname{Sub}(l,r)$ 的情况。

我们从 $i=l$ 开始选择，每一位可以选择 $0$ 和 $1$。令选出来的字符串为 $t$。

当 $s_i=0$ 时，把前面的数和 $s_i$ 选上肯定会使 $x>\operatorname{Sub}(l,r)$，而 $s_{i+1}\dots s_r$ 可以随便选，共有 $2^{r-i}$ 种选择方法。由于要满足 $\operatorname{Pari}(t)=1$，因此 $s_{i+1}\dots s_r$ 中 $1$ 的个数需要为偶数或者奇数。根据前面的结论，最终选择方案就是 $2^{r-i-1}$，把所有情况 $i$ 的答案加在一起，用总方案数 $2^{r-l}$ 减去他。最后结论就是：

$$\displaystyle\sum_{x=0}^{\operatorname{Sub}(l, r)}\operatorname{Pari}(x)=2^{r-l}-\sum_{i=l}^r [s_i=0]\cdot 2^{r-i-1}$$

别急着抄，还需要考虑一种情况。当 $i=r$ 的时候，$r-i-1$ 为负数。此时如果 $s_r=0$ 且 $[l,r]$ 中 $s_i$ 中 $1$ 的个数为偶数，就会发现多统计了一种情况，最后答案还需要 $-1$。把这个式子写一下，再判一下上面的情况可以获得 $O(nq)$ 复杂度的分数 $50$ 分，代码如下。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define N 200005
using namespace std;
int n,q,sum[N],p[N];
char c[N];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n>>q;
	p[0]=1;
	for(int i=1;i<=n;i++) p[i]=p[i-1]*2%mod;
	for(int i=1;i<=n;i++) cin>>c[i],sum[i]=sum[i-1]+(c[i]=='1');
	while(q--)
	{
		int l,r,tmp=0;
		cin>>l>>r;
		for(int i=l;i<r;i++) if(c[i]=='0') tmp=(tmp+p[r-i-1])%mod;
		if(c[r]=='0'&&(sum[r]-sum[l-1])%2==0) tmp++;
		cout<<(p[r-l]-tmp%mod+mod)%mod<<"\n";
	}
	return 0;
}
```

有了上面的分析满分做法就很好想了。考虑每个 $s_i=0$ 的贡献 $val_i$，发现 $2^{r-i-1}$ 这一项比较难算，考虑钦定 $r$ 计算。于是把询问离线下来，按照 $r$ 从小到大排序。那么遇到 $s_{r-1}=0$ 就把 $val_{r-1}$ 设为 $1$。当 $r$ 需要往后移动的时候，就相当于把 $val_1\dots val_i$ 全部 $\times 2$。最后算答案的时候就是查询 $\sum_{i=l}^r val_i$。因此只需要写一个支持单点赋值，区间乘和查询区间和的线段树就行了。最后时间复杂度 $O(q\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
#define N 200005
using namespace std;
int n,q,l[N],r[N],sum[N],res[N],p[N];
char c[N];
vector<int>v[N];
struct Data{int sum,tag;};
struct SGT
{
	Data t[N*4];
	void maketag(int k,int x)
	{
		t[k].sum=t[k].sum*x%mod;
		t[k].tag=t[k].tag*x%mod;
		return;
	}
	void pushdown(int k)
	{
		maketag(k*2,t[k].tag);
		maketag(k*2+1,t[k].tag);
		t[k].tag=1;
		return;
	}
	void build(int k,int l,int r)
	{
		t[k].tag=1;
		if(l==r) return;
		int mid=l+r>>1;
		build(k*2,l,mid);
		build(k*2+1,mid+1,r);
		return;
	}
	void update1(int k,int l,int r,int pos,int x)//单点赋值
	{
		if(l==r) {t[k].sum=x;return;}
		pushdown(k);
		int mid=l+r>>1;
		if(pos<=mid) update1(k*2,l,mid,pos,x);
		else update1(k*2+1,mid+1,r,pos,x);
		t[k].sum=(t[k*2].sum+t[k*2+1].sum)%mod;
		return;
	}
	void update2(int k,int l,int r,int ql,int qr,int x)//区间乘
	{
		if(ql<=l&&r<=qr) {maketag(k,x);return;}
		pushdown(k);
		int mid=l+r>>1;
		if(ql<=mid) update2(k*2,l,mid,ql,qr,x);
		if(qr>mid) update2(k*2+1,mid+1,r,ql,qr,x);
		t[k].sum=(t[k*2].sum+t[k*2+1].sum)%mod;
		return;
	}
	int query(int k,int l,int r,int ql,int qr)//查询区间和
	{
		if(ql<=l&&r<=qr) return t[k].sum;
		pushdown(k);
		int mid=l+r>>1,res=0;
		if(ql<=mid) res=(res+query(k*2,l,mid,ql,qr))%mod;
		if(qr>mid) res=(res+query(k*2+1,mid+1,r,ql,qr))%mod;
		return res;
	}
}t;
signed main()
{
	ios::sync_with_stdio(0);
	cin>>n>>q;
	p[0]=1;
	for(int i=1;i<=n;i++) p[i]=p[i-1]*2%mod;//预处理 2^k
	for(int i=1;i<=n;i++) cin>>c[i],sum[i]=sum[i-1]+(c[i]=='1');
	for(int i=1;i<=q;i++) cin>>l[i]>>r[i],v[r[i]].push_back(i);//把询问按照 r 压在 v 里面
	t.build(1,1,n);
	for(int i=1;i<=n;i++)//枚举 r
	{
		t.update2(1,1,n,1,i,2);//把 val[1~i]*2
		if(c[i-1]=='0') t.update1(1,1,n,i-1,1);//把 val[i-1] 设置为 1
		for(int now:v[i])//now 表示右端点为 r 的询问编号
		{
			int tmp=t.query(1,1,n,l[now],r[now]);
			if(c[i]=='0'&&(sum[r[now]]-sum[l[now]-1])%2==0) tmp++;
			res[now]=((p[r[now]-l[now]]-tmp)%mod+mod)%mod;
		}
	}
	for(int i=1;i<=q;i++) cout<<res[i]<<"\n";
	return 0;
}
```

---

## 作者：dingxiongyue (赞：1)

# 题解：P12465 『FCRT / 1 - 2』Parity

## Solution：

注意到：
$$
\sum _ {i = 1} ^ n \operatorname {Pari} (i)= 
\begin {cases} 
\frac{n + 1}{2} & \text{if } n \text{ is odd}, \\ 
\frac{n}{2} + \operatorname{Pari}(n) & \text{otherwise}.
\end{cases}
$$
**Proof：**

考虑**数学归纳法**。

* 若 $n$ 为奇数，设 $n = 2k + 3$。

  假设公式 $\sum _ {i = 1} ^ {2k + 1} \operatorname {Pari} (i) = k + 1$ 成立。

  则：
  $$
  \begin {aligned} 
  \sum _ {i = 1} ^ {2k + 3} \operatorname {Pari} (i) &= \sum _ {i = 1} ^ {2k + 1} \operatorname {Pari} (i) + \operatorname {Pari} (2k + 2) + \operatorname {Pari} (2k + 3) \\
  &= k + 1 + \operatorname {Pari} (2k + 2) + \operatorname {Pari} (2k + 3)\\
  \end {aligned}
  $$
  计算 $\operatorname {Pari} (2k + 2) $ 与 $\operatorname {Pari} (2k + 3)$：

  * $2k + 2$ 为 $k + 1$ 的二进制后加一个 $0$，所以 $\operatorname {Pari} (2k + 2) = \operatorname {Pari} (k + 1)$。
  * $2k + 2$ 为 $k + 1$ 的二进制后加一个 $1$，所以 $\operatorname {Pari} (2k + 2) = \operatorname {Pari} (k + 1) \oplus 1 $。

  代入：
  $$
  \begin {aligned} 
  \sum _ {i = 1} ^ {2k + 3} \operatorname {Pari} (i) &= k + 1 +\operatorname {Pari} (k + 1)+ (\operatorname {Pari} (k + 1) \oplus 1) \\
  &= k + 2 \\
  &= \frac {(2k + 3) + 1} {2}
  \end {aligned}
  $$
  公式成立。

* 若 $n$ 为偶数，设 $n = 2k$。

  则：
  $$
  \begin {aligned} 
  \sum _ {i = 1} ^ {2k} \operatorname {Pari} (i) &= \sum _ {i = 1} ^ {2k - 1} \operatorname {Pari} (i) + \operatorname {Pari} (2k) \\ 
  &= k + \operatorname {Pari} (n) \\
  &= \frac {n} {2} + \operatorname {Pari} (n)
  \end {aligned}
  $$
  
  公式成立。



证毕。

有了这个公式后，只需要预处理前缀十进制值 $sum_i$ 与前缀异或和 $pre_i$。

对于询问 $(l,r)$：
$$
\operatorname{Sub}(l,r) = sum_r - sum_{l - 1} \times 2 ^ {r - l + 1}\\
\operatorname{Pari}(\operatorname{Sub}(l,r)) = (pre_r - pre_{l - 1}) \bmod 2
$$
答案代入公式计算即可。

时间复杂度 $O(N + Q)$。

**注意：**

* 别忘了取模。
* 除以 $2$ 要用逆元。
* 因为有取模，所以不能直接 $\operatorname{Sub}(l,r) \bmod 2$ 判断 $\operatorname{Sub}(l,r)$ 的奇偶性，应该判断 $s_r = 1$。

## Code：

[AC记录](https://www.luogu.com.cn/record/216625815)

```cpp
#include <iostream>

#define int long long
const int N = 2e5 + 10, mod = 998244353, inv2 = 499122177;
int n, q;
int l, r;
int sum[N], pre[N];
int pow[N];
std::string s;
inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

inline void write(int x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

signed main() {
	n = read(), q = read();
	std::cin >> s;
	s = " " + s;
	for (int i = 1; i <= n; i++) {
		sum[i] = (sum[i - 1] * 2 % mod + (s[i] - '0')) % mod;
		pre[i] = (pre[i - 1] + (s[i] - '0')) % 2;
	}
	pow[0] = 1;
	for (int i = 1; i <= n; i++)
		pow[i] = pow[i - 1] * 2 % mod;
	while (q--) {
		l = read(), r = read();
		int len = r - l + 1;
		int num = (sum[r] - sum[l - 1] * pow[len] % mod + mod) % mod;
		int tmp = (pre[r] - pre[l - 1] + 2) % 2;
		if (s[r] == '1') write((num + 1) * inv2 % mod);
		else write((num * inv2 % mod + tmp) % mod);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Targanzqq (赞：0)

提供一种可能和正解不一样但是很暴力的做法。

我们看到需要从小到大统计数与每一位有关的贡献，自然要想到数位 dp 常用的策略（虽然这个题不是数位 dp），就是固定前面的某一部分，求后面和前面固定的部分共同组成的贡献，最后再加起来。

对于这个题我们怎么做呢？我们对于区间 $[l,r]$，钦定 $s_i=1$，固定 $[l,i-1]$，把 $s_i$ 改成 $0$，$[i+1,r]$ 就可以随便选。我们发现这部分随便选的答案是 $2^{r-(i+1)}$ 的，也就是说 $1$ 的数量奇数和偶数是相同的，因此无论前面那部分有奇数个 $1$ 还是偶数个 $1$，后面的答案都不变。因此我们只需要统计一下所有 $1$ 的位置到末尾这一段的贡献，也就是 $\sum\limits_{a_i=1}2^{r-(i+1)}$，就可以得到答案了。这个地方还有个小细节，就是固定所有位的贡献，如果最后一位是 $1$ 或者区间 $1$ 的个数为奇数就增加 $1$ 的贡献。

但是这个东西怎么求呢？我们考虑到它的值和末位有关，末位向后移动一位，前面的点贡献就会 $\times 2$。那么我们把区间按照右端点排序，每次向后加点，维护一个区间乘和区间和即可。时间复杂度 $O((n+q)\log n)$。

源代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;

int n,q,a[200005],ans[200005],pos[200005];
string s;

struct segtree{
	int a[1000005],lz[1000005];
	void push_down(int k,int l,int r){
		int mid=(l+r)/2;a[2*k]*=lz[k];a[2*k+1]*=lz[k];
        a[2*k]%=mod;a[2*k+1]%=mod;
		lz[2*k]*=lz[k];lz[2*k+1]*=lz[k];lz[k]=1;
        lz[2*k]%=mod;lz[2*k+1]%=mod;
	}
	void change(int k,int l,int r,int pos,int num){
		if(l==r){a[k]+=num;return;}
		int mid=(l+r)/2;
        if(pos<=mid)change(2*k,l,mid,pos,num);
        if(pos>mid)change(2*k+1,mid+1,r,pos,num);
        a[k]=a[2*k]+a[2*k+1];
	}
	void modify(int k,int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r){a[k]*=2;a[k]%=mod;lz[k]*=2;lz[k]%=mod;return;}
		push_down(k,l,r);int mid=(l+r)/2;
		if(ql<=mid)modify(2*k,l,mid,ql,qr);
		if(qr>mid)modify(2*k+1,mid+1,r,ql,qr);
		a[k]=a[2*k]+a[2*k+1];a[k]%=mod;
	}
	int query(int k,int l,int r,int ql,int qr){
		if(ql<=l&&qr>=r)return a[k];
		push_down(k,l,r);int mid=(l+r)/2,res=0;
		if(ql<=mid)res+=query(2*k,l,mid,ql,qr);
		if(qr>mid)res+=query(2*k+1,mid+1,r,ql,qr);
		return res%mod;
	}
}tr,tr3;//tr3是求区间1个数的，因为我不想再写一个前缀和了

struct rgs{
	int l,r,id;
	friend bool operator<(rgs a,rgs b){
		return a.r<b.r;
	}
}b[200005];

signed main(){
	ios::sync_with_stdio(false);
    cin>>n>>q;
    cin>>s;
    for(int i=1;i<=4*n;i++)tr.lz[i]=1,tr3.lz[i]=1;
	for(int i=1;i<=n;i++)a[i]=s[i-1]-'0';
	for(int i=1;i<=n;i++){
		if(!a[i])continue;
		tr.change(1,1,n,i,a[i]);
		tr3.change(1,1,n,i,a[i]);
	} 
	for(int i=1;i<=q;i++){
		cin>>b[i].l>>b[i].r;b[i].id=i;
	}
	sort(b+1,b+q+1);
	for(int i=1,j=0;i<=q;i++){
		//cout<<j<<" ";
		while(j+1<b[i].r){
			if(j>=1)tr.modify(1,1,n,1,j);j++;
		}
		//cout<<tr3.query(1,1,n,b[i].l,j)<<" ";
		if(b[i].l<=j)ans[b[i].id]=tr.query(1,1,n,b[i].l,j);
		if(a[b[i].r]==1)ans[b[i].id]++;
		else if(tr3.query(1,1,n,b[i].l,b[i].r)%2)ans[b[i].id]++;
        ans[b[i].id]%=mod;
	}
	for(int i=1;i<=q;i++)cout<<ans[i]<<"\n";
}

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12465)

对于一个正整数 $x$，当 $x$ 为奇数时，因为 $x$ 的二进制比 $x-1$ 的二进制多一个 $1$，所以 $\text{Pari}(x)+\text{Pari}(x-1)=1$。

设 $f(n)=\sum_{x=0}^{n} \text{Pari}(x)$，则容易得出式子：

$$f(n)=\begin{cases} \lceil \frac{n}{2} \rceil & n \equiv 1 \pmod 2 \\ \frac{n}{2} + \text{Pari(x)} & n \equiv 0 \pmod 2 \end{cases}$$

我们用数组 $pre_i$ 表示 $s$ 的前 $i$ 位中 $1$ 的个数，用数组 $pref_i$ 表示 $s$ 的前 $i$ 位所代表的数。易得 $\text{Sub}(l,r)=pref_r-pref_{l-1} \times 2^{r-l+1}$，$\text{Pari(Sub}(l,r))=(pre_r-pre_{l-1}) \bmod 2$。运用快速幂可以在 $O(\log n)$ 的时间复杂度下完成一个测试点。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
pii mkp(int x, int y){pii p; p.first = x, p.second = y; return p;}
const int mod = 998244353;
int n, q, pre[300001], pref[300001]; char s[300001];
int fpow(int a, int b){
	int ans = 1;
	while (b){
		if (b & 1) ans = ans * a % mod;
		a = a * a % mod; b /= 2;
	}
	return ans;
}//快速幂
signed main(){
	scanf("%lld%lld%s", &n, &q, s + 1);
	for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + s[i] - '0';
	for (int i = 1; i <= n; i++) pref[i] = (pref[i - 1] * 2 + s[i] - '0') % mod;//初始化
	for (int i = 1; i <= q; i++){
		int l, r; scanf("%lld%lld", &l, &r);
		int x = (pref[r] - pref[l - 1] * fpow(2, r - l + 1) % mod + mod) % mod;
		if (s[r] == '1'){//此时的x是模后的结果，奇偶性必须看s[r]
			if (x % 2 == 0) x += mod;//把x变成奇数
			printf("%lld\n", (x / 2 + 1) % mod);
		}
		else{
			if (x % 2) x += mod;//同理
			printf("%lld\n", (x / 2 + (pre[r] - pre[l - 1]) % 2) % mod);
		}
	}
    return 0;
}
```

---

