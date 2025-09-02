# 【MGVOI R1-D】图上的数（graph）

## 题目描述

你有一张有向图 $G$，这张图中有着无穷多个节点，这些节点的编号为 $1,2,3,...$。

对于任意两个正整数 $i,j$ 而言，当且仅当 $i$ 是 $j$ 的倍数，并且 $i \neq j$ 时，在图 $G$ 中存在一条由 $i$ 号节点指向 $j$ 号节点的边（其长度为 $1$）。

* 下图为 $G$ 中前 $6$ 号节点的状态示例：（点击查看）

::::info[示例]
![](https://cdn.luogu.com.cn/upload/image_hosting/wjfq1qxt.png)
::::

---

对任意的正整数 $x$，给出如下定义：

1. 从 $x$ 号节点到 $1$ 号节点的 **最长路径的长度** 为 $E(x)$；
     
2. 从 $x$ 号节点到 $1$ 号节点的 **最长路径的条数** 为 $T(x)$；
     
3. 设在所有满足 $E(y)=E(x)$ 的正整数 $y$ 中，$T(y)$ 的最大值为 $\max \{ T(y) \}$，则定义 $A(x)$ 的值为 $\dfrac{\max \{ T(y) \} }{T(x)}$；
     
4. 特殊地，规定 $E(1)=0$，$T(1)=A(1)=1$。

可以证明，$A(x)$ 一定是正整数。以下是几个便于你理解上述定义的例子：（点击查看）

::::info[示例]
1. $E(6)=2$，$T(6)=2$，因为从 $6$ 号节点到 $1$ 号节点最多可以经过 $2$ 条边，其对应的 $2$ 条最长路径分别为 $6\rightarrow 3\rightarrow 1$ 和 $6\rightarrow 2\rightarrow 1$。同理可知，$E(4)=2$，$T(4)=1$。

2. $A(6)=1$，因为在所有满足 $E(y)=2$ 的正整数 $y$ 中，可以证明，$T(y)$ 的最大值即为 $2$，与 $T(6)$ 恰好相等。

3. $A(4)=2$，因为在所有满足 $E(y)=2$ 的正整数 $y$ 中，$T(y)$ 的最大值 $2$ 恰好为 $T(4)$ 的 $2$ 倍。

::::


---


给定一个正整数 $N=a^b$，在此基础上，你可以按如下规则构造出一个 $N$ 行 $N$ 列的方格图 $S_N$。

对于正整数 $i,j$（$1\le i,j\le N$）而言：

* 当 $N$ 是 $i$ 的倍数，**并且** $i$ 是 $j$ 的倍数时，第 $i$ 行第 $j$ 列的方格上写有数字 $i\times j\times A(j)$；

* 否则，第 $i$ 行第 $j$ 列的方格上写有数字 $1$。

不难验证 $A(1)=A(2)=A(3)=A(6)=1$。以下是方格图 $S_6$ 的示例：（点击查看）

::::info[示例]
|$1$|$1$|$1$|$1$|$1$|$1$|
|:-:|:-:|:-:|:-:|:-:|:-:|
|$2$|$4$|$1$|$1$|$1$|$1$|
|$3$|$1$|$9$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|
|$6$|$12$|$18$|$1$|$1$|$36$|
::::

---

你需要回答以下两个问题：

* 第一问：$A(N)$ 的值是多少？

* 第二问：在方格图 $S_N$ 中，所有方格上数字的总和是多少？

由于答案可能很大，请将所有答案对 $10^9+7$ 取模。


## 说明/提示

**【样例 #1】**

::::info[样例 #1 解释]

该样例下，$N=6^1=6$。

在【题目描述】中已经解释过 $A(6)=1$（**即第一问的答案**），并画出了方格图 $S_6$，其中所有方格上数字的总和为 $118$（**即第二问的答案**）。

::::

**【样例 #2】**

::::info[样例 #2 解释（第二组测试数据）]

对于第二组测试数据，$N=2^3=8$。

:::success[第一问的答案说明]

首先可以得到 $E(8)=3$，$T(8)=1$，对应的唯一一条最长路为 $8\rightarrow 4\rightarrow 2\rightarrow 1$。

 其次，在所有满足 $E(y)=3$ 的正整数 $y$ 中，有 $\max \{ T(y) \} =6$（详细说明见下），故 $A(8)=\dfrac{6}{T(8)}=6$（**即第一问的答案**）。

 当 $y=30$ 时，有 $E(y)=3$，$T(y)=6$，其对应的 $6$ 条最长路分别为：
 
 * $30\rightarrow 15\rightarrow 5\rightarrow 1$；

 * $30\rightarrow 15\rightarrow 3\rightarrow 1$；

 * $30\rightarrow 10\rightarrow 5\rightarrow 1$；

 * $30\rightarrow 10\rightarrow 2\rightarrow 1$；

 * $30\rightarrow 6\rightarrow 3\rightarrow 1$；

 * $30\rightarrow 6\rightarrow 2\rightarrow 1$。

可以证明，$T(30)=6$ 就是在所有满足 $E(y)=3$ 的正整数 $y$ 中，$T(y)$ 的最大值。

:::

:::success[第二问的答案说明]

列出 $A(x)$ 的值表：

|$x$|$1$|$2$|$4$|$8$|
|:-:|:-:|:-:|:-:|:-:|
|$A(x)$|$1$|$1$|$2$|$6$|

接下来，画出方格图 $S_8$：

|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|$2$|$4$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$4$|$8$|$1$|$32$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$1$|$1$|$1$|$1$|$1$|$1$|$1$|$1$|
|$8$|$16$|$1$|$64$|$1$|$1$|$1$|$384$|


所有方格上数字的总和为 $577$（**即第二问的答案**）。
:::

::::

---



::::info[样例 #2 解释（第三组测试数据）]

对于第三组测试数据，$N=6^2=36$。

分析可知 $E(36)=4$，$T(36)=6$。而在所有满足 $E(y)=4$ 的正整数中，取 $y=210$ 即可最大化 $T(y)$，有 $\max \{ T(y) \} =T(210)=24$，据此可得到 $A(36)=\dfrac{T(210)}{T(36)}=4$（**即第一问的答案**）。

由于方格图 $S_{36}$ 的篇幅过大，下面仅画出其最后一行（也就是第 $36$ 行）的状态，并标出列编号：


| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35 | 36 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: | :-----------: 
| $36$ | $72$ | $108$ | $288$ | $1$ | $216$ | $1$ | $1$ | $648$ | $1$ | $1$ | $864$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1296$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $1$ | $5184$ |

在画出完整的方格图后可以验证，$S_{36}$ 中所有方格上数字的总和为 $12021$（**即第二问的答案**）。

:::warning[温馨提示]
请不要忘记将所有答案对 $10^9+7$ 取模！
:::

::::


**【样例 #3】**

见附件中的 ```graph/graph3.in``` 与 ```graph/graph3.ans```。

这个样例满足测试点 $2 \sim 4$ 的限制。

**【样例 #4】**

见附件中的 ```graph/graph4.in``` 与 ```graph/graph4.ans```。

这个样例满足测试点 $5 \sim 6$ 的限制。

**【样例 #5】**

见附件中的 ```graph/graph5.in``` 与 ```graph/graph5.ans```。

这个样例满足测试点 $7 \sim 10$ 的限制。



---




**【数据范围】**

对于所有测试点，保证 $1\le T\le 100$，$1\le a \le 2\times 10^9$，$1\le b \le 2\times 10^3$。

::cute-table{tuack}

| **测试点编号** | $T \le$ | $a \le$ |  $b \le$ | **特殊性质** |
|:-:|:-:|:-:|:-:|:-:|
| $1$ | $2$ | $10$ | $1$ | **AB**
| $2\sim 4$ | $20$ | $2\times 10^3$ | $10$ | ^
| $5\sim 6$ | $100$ | $2\times 10^9$ | $2\times 10^3$ | **C** | 
| $7\sim 10$ | ^ | ^ | ^ | 无

特殊性质 **A**：保证 $a^b\le 2\times 10^3$，即 $N\le 2\times 10^3$。

特殊性质 **B**：保证存在正整数 $k$（$k\le 5\times 10^5$）满足 $E(k)=E(N)$，$T(k)=A(N)\times T(N)$。

特殊性质 **C**：保证 $a$ 是质数（注意：不保证 $N$ 是质数）。

* 分值分配：每个测试点的分值为 $10$ 分。对于单个测试点，如果你的程序对第一问和第二问均回答正确，则获得满分 $10$ 分；若只回答对了第一问，得 $2$ 分；若只回答对了第二问，得 $8$ 分；若两问均未答对（或输出格式错误），得 $0$ 分。

## 样例 #1

### 输入

```
1
6 1```

### 输出

```
1 118```

## 样例 #2

### 输入

```
5
1 1
2 3
6 2
7 1
15 2```

### 输出

```
1 1
6 577
4 12021
1 103
4 352530```

# 题解

## 作者：zhlzt (赞：8)

由算术基本定理，令 $n=\prod\limits_{i=1}^{k}p_i^{c_i}$。

则 $E(n)=\sum c_i$，$T(n)=\dfrac{E(n)!}{\prod_{i=1}^k c_i!}$，$A(n)=\dfrac{E(n)!}{T(n)}=\prod_{i=1}^k c_i!$。

于是第一问可以在 $\mathcal{O}(\sqrt{a})$ 的时间内解决。

显然也可以通过预处理做到 $\mathcal{O}(\sqrt{a}) - \mathcal{O}\left(\dfrac{\sqrt{a}}{\log{a}}\right)$，但是没有必要。

对于第二问，考虑分别计数 $\text{ans}_1=\sum\limits_{d|n}\sum\limits_{d|k|n}1$，$\text{ans}_2=\sum\limits_{d|n}d\cdot A(d)\cdot \sum\limits_{d|k|n}k$，令 $d=\prod\limits_{i=1}^{k}p_i^{h_i}$。

接下来是非常简单的推式子。虽然看起来有一些恐怖。

$$\begin{aligned} \text{ans}_1 &= \sum_{d|n}\sum_{d|k|n}1 = \sum_{d|n}\prod_{i=1}^k(c_i-h_i+1)= \sum_{d|n}\prod_{i=1}^k(h_i+1) \\ &= \prod_{i=1}^k\sum_{i=0}^{c_i}(i+1)= \prod_{i=1}^k\dfrac{(c_i+1)(c_i+2)}{2} \\ \\\text{ans}_2 &=\sum_{d|n}d\cdot A(d)\cdot \sum_{d|k|n}k= \sum_{d|n} d^2 \cdot A(d) \cdot\sum_{k|\frac{n}{d}} k \\ &= \sum_{d|n}\prod_{i=1}^{k}\left(p_i^{2h_i}\cdot h_i!\cdot\sum_{j=0}^{c_i-h_i}p_i^j\right)\\&=\prod_{i=1}^{k}\sum_{j=0}^{c_i} p_i^{2j} \cdot j! \cdot \dfrac{p_i^{c_i-j+1}-1}{p_i-1}\end{aligned}$$

时间复杂度 $\mathcal{O}(\sqrt{a}+b\log a)$，空间复杂度 $\mathcal{O}(\log a)$。

:::success[【MGVOI R1-D】图上的数 - graph.cpp]
```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=20;
const int mod=1e9+7;
int cnt[maxn],p[maxn];
inline int qkpow(int a,int p){
    int res=1;
    while(p){
        if(p&1) res=1ll*res*a%mod;
        a=1ll*a*a%mod,p>>=1;
    }
    return res;
}
inline int sol(int n,int m){
    ll res=0;
    int val=1,inv=qkpow(n-1,mod-2);
    int invn=qkpow(n,mod-2),pw=qkpow(n,m+1);
    for(int i=0;i<=m;i++){
        if(i){
            val=1ll*val*i%mod*n%mod*n%mod;
            pw=1ll*pw*invn%mod;
        }
        res+=1ll*val*(pw+mod-1)%mod*inv%mod;
    }
    res%=mod;
    return res;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;cin>>t;
    while(t--){
        int a,b,k=0;
        cin>>a>>b;
        int cura=a;
        for(int i=2;i<=sqrt(a);i++){
            if(a%i) continue;
            p[++k]=i,cnt[k]=0;
            while(a%i==0) cnt[k]+=b,a/=i;
        }
        if(a>1) p[++k]=a,cnt[k]=b;
        int ans0=1,ans1=1,ans2=1,ljd=qkpow(cura,b);
        ljd=1ll*ljd*ljd%mod;
        for(int i=1;i<=k;i++){
            for(int j=1;j<=cnt[i];j++) ans0=1ll*ans0*j%mod;
            ans1=1ll*ans1*sol(p[i],cnt[i])%mod;
            ans2=1ll*ans2*(1ll*(cnt[i]+1)*(cnt[i]+2)/2%mod)%mod;
        }
        ans1=(ans1+ljd-ans2);
        ans1=(ans1%mod+mod)%mod;
        cout<<ans0<<" "<<ans1<<"\n";
    }
    return 0;
}
```
:::

---

## 作者：Water__Problem (赞：5)

## 废话

赛时题看错了两次，浪费了30min。

## 题解

先来看第一问题。把所有函数都一个一个推出来。

把每个 $x$ 质因数分解，假设 $x=p_1^{c_1}p_2^{c_2}\dots p_k^{c_k} $。

1) $E(x)$：$x$ 往 $1$ 节点跳边肯定每次除去一个质数，所以 $E(x)=\sum_{i=1}^kc_i$。
2) $T(x)$：根据 $E(x)$ 的计算方式，$T(x)$ 的值就变成有几种删质数的方式使得 $x$ 变成 $1$。学过一点组合数学就知道 $T(x)=\frac{(\sum_{i=1}^kc_i)!}{\prod_{i=1}^kc_i!}$。
3) $A(x)$ 对于所有 $y$ 因为 $E(x)$ 是定值，所以 $T(x)$ 公式中的分子是定值，要使 $T(x)$ 最大，就要使分子最小，当 $c_1=c_2= \dots =c_k=1$ 事最小。所以 $A(x)=\frac{\max{T(y)}}{T(x)}=\prod_{i=1}^kc_i!$。

于是第一问解决。

---

来看第二问。考虑这个式子 
$$$\displaystyle\prod_{i=1}^n\sum_{j=1}^{m_i}a_{i,j}=\sum_{i_1=1}^{m_1}\sum_{i_2=1}^{m_2}\dots\sum_{i_n=1}^{m_n} a_{1,i_1}a_{2,i_2}\dots a_{n,i_n}$$$

很重要，后面全是这东西。

我们把 $S_N$ 里的数分成两部分，一个是普通的一个是特殊的。

---

先考虑普通的怎么算。

一的个数等于全部的个数减去特殊的个数。而特殊的个数很好算。

对于每一行特殊的数就是这一行序列编号的因子个数。

一个数的约数个数是 $\displaystyle\prod_{i=1}^k(c_i+1)$ 所有的个数就是 $\displaystyle\sum_{i=1}^k\frac{(c_i+1)(c_i+2)}{2}$。

这样普通部分的答案就是 $N^2-\displaystyle\sum_{i=1}^k\frac{(c_i+1)(c_i+2)}{2}$。

---

再考虑特殊的。

下面式子中假设 $x=p_1^{x_1}p_2^{x_2}\dots p_k^{x_k}\ \ y=p_1^{y_1}p_2^{y_2}\dots p_k^{y_k}\ \ N=p_1^{c_1}p_2^{c_2}\dots p_k^{c_k}$

$$
\begin{aligned}
ans&=\sum_{x|N}\sum_{y|x} xyA(y)\\
&=\sum_{x|N}x\sum_{y|x}p_1^{y_1}p_2^{y_2}\dots p_k^{y_k}\times y_1!y_2!\dots y_k!\\
&=\sum_{x|N}x\sum_{y|x}(p_1^{y_1}y_1!)(p_2^{y_2}y_2!)\dots (p_k^{y_k}y_k!) \\
&=\sum_{x|N}x\prod_{i=1}^k\sum_{j=0}^{x_i} p_i^jj!\\
&=\sum_{x|N}(\prod_{i=1}^kp_i^{x_i})\times(\prod_{i=1}^k\sum_{j=0}^{x_i} p_i^jj!)\\
&=\sum_{x|N}\prod_{i=1}^k(p_i^{x_i}(\sum_{j=0}^{x_i} p_i^jj!))\\
&=\prod_{i=1}^k\sum_{j=0}^{c_i}(p_i^j\times(\sum_{t=0}^jp_i^tt!))
\end{aligned}
$$

然后就做完了。中间有些步骤需要自己研究一下的。总复杂度 $O(\sum_{i=1}^k c_i)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
void init();void solve();
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int T=1;init();
	cin>>T;
	while(T--) solve();
	return 0;
}
#define mod (1000000007)
int a,b,p[1005],k[1005],t,fac[1000005],ans,ans1,ans2,N,sum[10005];
void init(){
	fac[0]=1;
	for(int i=1;i<=1000000;i++) fac[i]=fac[i-1]*i%mod;
}
int fpow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=res*x%mod;
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
void solve(){
	cin>>a>>b;
	N=fpow(a,b);
	t=0;
	for(int i=2;i*i<=a;i++){
		if(a%i==0){
			t++;
			p[t]=i;
			k[t]=0;
			while(a%i==0){
				a/=i;
				k[t]++;
			}
			k[t]*=b;
		}
	}
	if(a>1){
		t++;
		p[t]=a;
		k[t]=b;
	}
	ans=1;
	for(int i=1;i<=t;i++) ans=ans*fac[k[i]]%mod;
	ans1=ans2=1;
	for(int i=1;i<=t;i++){
		int t1=1,t2=1,t3=1,res=1;
		for(int j=1;j<=k[i];j++){
			t1=t1*p[i]%mod;
			t3=t3*j%mod;
			t2=(t2+t1*t3)%mod;
			res=(res+t1*t2%mod)%mod;
		}
		ans1=ans1*res%mod;
		ans2=ans2*((k[i]+1)*(k[i]+2)/2)%mod;
	}
	cout<<ans<<' '<<(N*N%mod+(ans1+mod-ans2))%mod<<endl;
}
```

---

## 作者：水星湖 (赞：5)

比较显然的是若 $x=\prod p^{c_p}$，则 $A(x)=\prod c_p!$，然后就做完第一问了。

对于第二问，考虑不满足 $j\mid i \land i\mid n$ 的位置有 $n^2-F(n)$ 个，其中 $F(n)$ 为 $n$ 的所有约数的约数个数和。注意到若 $n=p^\alpha$，则 $F(n)=\sum_{d\mid p^\alpha} \tau(d)=\sum_{i=0}^{\alpha} (i+1)=\binom{\alpha+2}{2}$，又因为约数个数函数 $\tau(n)$ 是积性函数，所以对于任意 $n=\prod p^{c_p}$，$F(n)=\prod \binom{c_p+2}{2}$。

接下来考虑满足 $j\mid i \land i\mid n$ 的位置的答案 $\sum_{i\mid n}\sum_{j\mid i} i\cdot j\cdot A(j)$。

对固定的 $j$，令 $i=jm$（其中 $m\mid \frac{n}{j}$），得到（$\sigma$ 为约数和函数）

$$
\sum_{\substack{i\mid n\\ j\mid i}} i\cdot j\cdot A(j)
= \sum_{m\mid \frac{n}{j}} (j m)\cdot j\cdot A(j)
= j^2 A(j)\sum_{m\mid \frac{n}{j}} m
= j^2 A(j)\,\sigma\!\Big(\frac{n}{j}\Big)
$$

因此原式可写为

$$
\;\sum_{j\mid n} j^2\,A(j)\,\sigma\!\Big(\frac{n}{j}\Big)\;
$$

考虑函数 $g(j)=j^2 A(j),h(k)=\sigma(k)$，原式就是 $h,g$ 的狄利克雷卷积，由于 $g,h$ 都为积性，所以可得

$$

(g*h)\!\Big(\prod_p p^{c_p}\Big)=\prod_p\Bigg(\sum_{e=0}^{c_p} g(p^e)\,h\big(p^{c_p-e}\big)\Bigg)
$$


设 $n=\prod p^{c_p}$，则原式为各素因子处的乘积

$$
\prod_p S_p,\qquad S_p=\sum_{e=0}^{c_p} g(p^e)\,h(p^{c_p-e})
$$

把 $g,h$ 代入，得到

$$
S_p=\sum_{e=0}^{c_p} p^{2e}\,e!\,\sigma\big(p^{c_p-e}\big)
$$

由于 $\sigma(p^t)=1+p+\cdots+p^t=\frac{p^{t+1}-1}{p-1}$，带入原式得

$$
S_p=\sum_{e=0}^{c_p} p^{2e}\,e!\cdot\frac{p^{c_p-e+1}-1}{p-1}
$$

可以对于每个质因子暴力算这个式子，答案即为 $\prod S_p + n^2 - F(n)$。

:::info[code]

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace z {

#define int long long
const int N = 1e5 + 5, mod = 1e9 + 7;
int fac[N], vis[N];
int qpow(int a, int b) {
    int r = 1;
    while(b) {
        if(b & 1) r = r * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return r;
}
void main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    fac[0] = 1;
    for(int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % mod;
    vector<int> t;
    for(int i = 2; i <= 5e4; i++) {
        if(vis[i]) continue;
        t.push_back(i);
        for(int j = i; j <= 5e4; j += i)
            vis[j] = 1;
    }
    int T; cin >> T;
    while(T--) {
        int a, b; cin >> a >> b;
        int ans1 = 1, ans2 = 1, mul = 1, sum = qpow(qpow(a, b), 2);
        for(auto p : t) if(a % p == 0) {
            int c = 0;
            while(a % p == 0) {
                a /= p;
                c++;
            }
            c *= b;
            ans1 = ans1 * fac[c] % mod;
            mul *= (c + 2) * (c + 1) / 2, mul %= mod;
            int s = 0;
            for(int e = 0; e <= c; e++) 
                (s += qpow(p, 2 * e) * fac[e] % mod * (qpow(p, c - e + 1) - 1) % mod
                 * qpow(p - 1, mod - 2) % mod) %= mod;
            ans2 = ans2 * s % mod;
        }
        if(a != 1) {
            int s = 0;
            ans1 = ans1 * fac[b] % mod;
            mul *= (b + 2) * (b + 1) / 2, mul %= mod;
            for(int e = 0; e <= b; e++)
                (s += qpow(a, 2 * e) * fac[e] % mod * (qpow(a, b - e + 1) - 1 + mod) % mod
                 * qpow(a - 1, mod - 2) % mod) %= mod;
            ans2 = ans2 * s % mod;
        }
        cout << ans1 << " " << (ans2 + sum - mul + mod) % mod << '\n';
    }

}

#undef int

}


int main()
{
    z::main();
    return 0;
}
```
:::

---

## 作者：FruitWasTaken (赞：3)

## 出题人题解


### 主要知识点

* 【3】整数唯一分解定理
* 【4】组合
* 【6】多重集上的排列

提示：本题解将分别解释第一问和第二问的做法，请读者根据自身解题进度决定是否跳读。

---


### 第一问：分析 $A(x)$ 的本质

我们先来做第一问。

显然首先要将 $N=a^b$ 质因子分解为 $p_1^{c_1}\cdot p_2^{c_2}\cdot ... \cdot p_k^{c_k}$，其中 $p_i$ 是互不相等的质数，$c_i$ 是正整数（并且也一定是 $b$ 的倍数）。那么首先可以观察到 $E(N)=c_1+c_2+...+c_k$，原因见下：

::::info[E 函数的计算]

  * 考虑在图 $G$ 中由 $N$ 号节点到 $1$ 号节点的最长路。显然每走一步除以一个质因子是最优的（例如 $2^2\times 3^3 \rightarrow 2^1\times 3^3 \rightarrow 2^0\times 3^3 \rightarrow 2^0\times 3^2 \rightarrow 2^0\times 3^1 \rightarrow 2^0\times 3^0$），因为你不可能除以 $1$（没有自环），而在剩下的所有方案中，最优的结果就是让质因子的指数和 $\sum c_i=c_1+c_2+...+c_k$ 减小 $1$，也就是除以一个质因子（否则 $\sum c_i$ 减小得更多，路径长度更短）。
    
  * 综上，由 $N$ 号节点到 $1$ 号节点最长路径的长度 $E(N)$ 就是 $\sum c_i$。
::::

然后看 $T(N)$：

::::info[T 函数的计算]

* 前面已经确定了最长路径共有 $\sum c_i$ 步，那么如何求最长路径的条数呢？实际上，各条最长路径的区别仅在于各个质因子被除掉的顺序：我们先考虑最理想的情况， $N$ 没有重复的质因子，即 $c_1=c_2=...=c_k=1$。

* 在这种情况下，$T(N)$ 的值就是 $\sum c_i$ 的阶乘，即 $k!$，因为此时每一条最长路径都对应了“每个质因子被除掉的顺序”对应的排列，而我们知道 $x$ 个不同元素的排列数就是 $x!$。（举例：$T(2\times 3\times 5\times 7)=4!$ ）

* 那么如果 $N$ 有重复的质因子呢？实际上也一样，只是要等效成多重集合的排列数。例如 $T(2^3 \times 3^4\times 5^2)=\dfrac{(3+4+2)!}{3!\times 4!\times 2!}$，将由“相同质因子之间的不同排列”导致的方案重复系数除掉即可。

* 综上，$T(N)=\dfrac{(c_1+c_2+...+c_k)!}{c_1!\times c_2!\times... \times c_k!}$。

::::

最后看 $A(N)$。分析完 $T(N)$ 之后，我们发现对 $A(N)$ 的分析就非常轻松了：

::::info[A 函数的计算]

> * 设在所有满足 $E(y)=E(x)$ 的正整数 $y$ 中，$T(y)$ 的最大值为 $\max \{ T(y) \}$，则定义 $A(x)$ 的值为 $\dfrac{\max \{ T(y) \} }{T(x)}$。
> 
> * $T(N)=\dfrac{(c_1+c_2+...+c_k)!}{c_1!\times c_2!\times... \times c_k!}$。

很显然，这个所谓的 $\max \{ T(y) \}$ 对应的 $y$ 一定是之前提到过的“$c_1=c_2=...=c_k=1$”的情况。这是因为在 $E(y)$ 的值 （也就是 $\sum c_i$ 的值）固定的前提下，它对应的分母 $c_1!\times c_2!\times... \times c_k!$ 取得最小值 $1$。（例如，对 $x=2^3\times 3^2$ 可以构造 $y=2\times 3\times 5\times 7\times 11$，在保证 $\sum c_i$ 不变的前提下尽可能地将质数均摊）

所以，$A(N)=\dfrac{\max \{ T(y) \} }{T(x)}=c_1!\times c_2!\times ... \times c_n!$。

::::

直接通过质因子分解和预处理阶乘实现以上做法，可获得 $20$ 分。如果再模拟得到前四个点第二问的答案，可获得 $52$ 分。

---

### 第二问：计算方格图中的数字总和

我们先来回顾一下题面：

> 对于正整数 $i,j$（$1\le i,j\le N$）而言：
>
> * 当 $N$ 是 $i$ 的倍数，**并且** $i$ 是 $j$ 的倍数时，第 $i$ 行第 $j$ 列的方格上写有数字 $i\times j\times A(j)$；**（以下记为特殊方格）**
>
> * 否则，第 $i$ 行第 $j$ 列的方格上写有数字 $1$。**（以下记为普通方格）**

那么考虑对普通方格和特殊方格分别计数，再把二者累加。

#### 第一部分：普通方格的计数

首先，我们显然可以注意到普通方格对答案的贡献为 $N^2-x$（其中 $x$ 为特殊方格的个数）。那么问题来了，$x$ 的值怎么求呢？

根据特殊方格的定义可知，求 $x$ 的值，就等价于求 “$N$ 的所有约数”的约数个数之和（举例，$N=6$，就相当于求 $1,2,3,6$ 的约数个数之和，为 $1+2+2+4=9$）。承第一问，仍设 $N=p_1^{c_1}\cdot p_2^{c_2}\cdot ... \cdot p_k^{c_k}$（质因子分解）。

先考虑一个弱化版的问题：$N$ 的约数和是多少？这是一个板子问题，答案是用乘法原理计数，得到 $\prod\limits_{i=1}^k (p_i^0+p_i^1+...+p_i^{c_i})$，即 $(p_1^0+p_1^1+...+p_1^{c_1})\times (p_2^0+p_2^1+...+p_2^{c_2})... \times(p_k^0+p_k^1+...+p_k^{c_k})$。

::::warning[接下来的思想很重要，之后会多次用到！]{open}

思考上面这个式子的本质，实际上相当于用乘法“拼接”了所有质因子的选择：

* 首先，作为 $N$ 的约数来说，$p_1$ 这个质因子的幂次可以在 $0,1,...,c_1$ 中任选，而 $p_2$ 这个质因子的幂次可以选 $0,1,...,c_2$，以此类推。

* 考虑只有两个质因数的情况，$(p_1^0+p_1^1+...+p_1^{c_1})\times (p_2^0+p_2^1+...+p_2^{c_2})$ 在完全展开后会得到总共 $(c_1+1)(c_2+1)$ 个单项式的和，其中每一个单项式都对应了 $N$ 的一个约数。例子见下（$N=2^2\times 3^1$）：

* $(\red{2^0}+\orange{2^1}+\blue{2^2})\times(\green{3^0}+\purple{3^1}) = (\red{2^0} \times \green{3^0}) + (\orange{2^1} \times \green{3^0}) + (\blue{2^2} \times \green{3^0}) + (\red{2^0} \times \purple{3^1}) + (\orange{2^1} \times \purple{3^1}) + (\blue{2^2} \times \purple{3^1})$

* 对于更多的质因数（设有 $k$ 个），可以进行数学归纳，只需在“只考虑前 $k-1$ 个质因数时的约数和”的基础上，乘上 $(p_k^0+p_k^1+...+p_k^{c_k})$，就能通过乘法分配律得到答案（将式子完全展开之后，之前的所有单项式，都会和第 $k$ 个质因子的选择通过乘法“自由组合”）。

* 综上，我们通过 $\prod\limits_{i=1}^k (p_i^0+p_i^1+...+p_i^{c_i})$ 这种形式的多项式乘法，用乘法“拼接”了所有质因子的选择，得到**所有选择的乘积的总和**，从而得到 $N$ 的约数和。

::::

此时再考虑求“$N$ 的所有约数”的约数个数之和。实际上就是 $\prod\limits_{i=1}^k \sum\limits_{j=0}^{c_i}{(j+1)}$，也即 $\prod\limits_{i=1}^k \dfrac{(c_i+1)(c_i+2)}{2}$（用等差数列求和公式化简）。原理见下：

::::info[原理]
回顾通过 $\prod\limits_{i=1}^k (p_i^0+p_i^1+...+p_i^{c_i})$ 用乘法“拼接”各个质因子的选择，从而计算约数和的方式。现在，我们对这个式子中“质因子对应的每个选项”进行替换，换为对应指数的幂次再加 $1$：例如如果原来是 $p^z$，就替换成 $z+1$，即化为 $\prod\limits_{i=1}^k (1+2+...+(c_i+1))$。

这个式子与约数和公式的结构完全相同，只是更改了每个质因子对应的“选项”。

我们注意到，与替换前相比，最终我们展开出来的每一项（将所有选项乘起来后）不再是具体的约数，而是每个约数对应的 $\prod(c_i+1)$，而这恰恰是我们想要的！（可以手动模拟一下，这类似于一个二维的“求约数个数”问题，第一层枚举约数，第二层枚举约数的约数）

这样就实现了求“$N$ 的所有约数”的约数个数之和。
::::

综上，我们求出了 $x$ 的值（即特殊方格的个数），也就完成了普通方格的计数！~~完结撒花doge~~

#### 第二部分：特殊方格的计数

理解了求约数和利用的组合思想之后，这一部分就不难了。

首先，第一问已经推过 $A(N)=\prod c_i!$。我们很喜欢的一点是这恰好是个积性函数，换而言之你可以模仿之前的方法，瞬间秒杀一个弱化问题：求 $N$ 的所有约数的 $A$ 函数值之和（如 $N=6$，就是 $A(1)+A(2)+A(3)+A(6)$），答案即为

$\prod\limits_{i=1}^k (0!+1!+...+c_i!)$，

从第一部分说过的原理容易看出，这和求约数和并没有什么本质的区别。

现在回到原问题：对每个 $N$ 的约数 $i$，都有 $i\cdot \sum( j\times A(j))$ 的贡献，其中 $j$ 是 $i$ 的约数。和之前的思路一样，我们仍考虑“替换”每个质因子对应的选项：

 $\prod\limits_{i=1}^k (p_i^0\times 0!+p_i^1\times 1!+...+p_i^{c_i}\times c_i!)$，

这样首先能乘出来“$N$ 的所有约数 $j$”对应的 $j\times A(j)$ 之和（弱化问题）。回到原问题，再嵌套一层 $i$ 对应的选项去计数即可：

$\prod\limits_{i=1}^k \sum\limits_{j=0}^{c_i}(p_i^j\times \sum\limits_{k=0}^j(p_i^k\times k!))$，

相当于对第一层乘出来的每个 $\prod p_i^j$  的结果（相当于枚举题目中的 $i$），还要再乘上第二层 $\sum\limits_{k=0}^j(p_i^k\times k!)$ 的结果（相当于在枚举 $i$ 的基础上，再去枚举题目中的 $j$，并得到 $j\times A(j)$ 的总和）。

（另一种理解方式：尝试做一下特殊性质 C，也就是上面 $k=1$ 的情况，答案为 $\sum\limits_{j=0}^{c_1}(p_1^j\times \sum\limits_{k=0}^j(p_1^k\times k!))$，其中 $c_1=b$，$p_1=a$。然后回到没有特殊性质的一般情况，你只需根据上述原理，用乘法拼接所有质因子的选择）

那么，第二部分的分析也就告一段落了，我们直接模拟一下这个式子，然后拼接两个部分的答案即可。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int a, b;
int cnt, primes[105], powers[105];
const int mod = 1e9 + 7;

void calc(int x)
{
	++cnt;
	primes[cnt] = x;
	powers[cnt] = 0;
	
	while (a % x == 0)
	{
		a /= x;
		++powers[cnt];
	}
	
	powers[cnt] *= b;
	powers[cnt] %= mod;
	return;
}

int facts[100005];

void solve()
{
	cin >> a >> b;
	
	cnt = 0;
	for (int i = 2; i * i <= a; i++)
	{
		if (a % i == 0)
			calc(i);
	}
	
	if (a > 1)
		calc(a);
	
	int ans1 = 1, ans2 = 1;
	int cnt1 = 1, cnt2 = 1;
	int res = 0, res2 = 0, sum = 0, sum2 = 0;
	int prime_power = 1;
	
	for (int i = 1; i <= cnt; i++)
	{
		ans1 *= facts[powers[i]];
		ans1 %= mod;
		
		res = 0, sum = 0, sum2 = 0, prime_power = 1;
		for (int j = 0; j <= powers[i]; j++)
		{ 
			sum += prime_power * facts[j] % mod;
			sum %= mod;
			
			res += prime_power * sum % mod;
			res %= mod;
			
			sum2 += j + 1;
			sum2 %= mod;
			
			prime_power *= (j < powers[i] ? primes[i] : 1);
			prime_power %= mod;
		}
		
//		cout << "[*]" << primes[i] << ' ' << powers[i] << ' ' << res << '\n';
		ans2 *= res;
		ans2 %= mod;
		
		cnt1 *= sum2;
		cnt1 %= mod;
		
		cnt2 *= prime_power * prime_power % mod;
		cnt2 %= mod;
	}
	
	ans2 += (cnt2 - cnt1 + mod) % mod;
	ans2 %= mod;
	
	cout << ans1 << ' ' << ans2 << '\n';
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); 
	
	const int inf = 50005;
	facts[0] = 1;
	
	for (int i = 1; i <= inf; i++)
	{
		facts[i] = facts[i - 1];
		facts[i] *= i;
		facts[i] %= mod;
	}
	
	int _;
	cin >> _;
	while (_--)
	{
		solve();
	}
	
	return 0;
}
```

---

## 作者：luuia (赞：2)

### Solution

记 $a = \prod_{i=1}^m p_i^{k_i}$，那么有 $n = a^b = \prod_{i=1}^m p_i^{k_ib} = \prod_{i=1}^m p_i^{c_i}$。

首先容易发现为了使路径最长，我们每次只除掉任意一个质因子，那么有 $E(x) = \sum_{i=1}^m c_i$。

$T(x)$ 就是任意排列 $c_i$ 个 $p_i$，方案数为：$\dfrac{E(x)!}{\prod_{i=1}^m c_i!}$。

那么，因为 $E(x)$ 是一定的，所以要让分母最小，此时为 $\forall i \in [1,m],c_i = 1$，于是可以得到 $A(x) = \prod_{i=1}^m c_i!$，于是第一问就做完了。

然后来看第二问，显然答案就是 $n^2$ 减去不为 $1$ 的格子的数量，再加上所有特殊格子的和。其中不为 $1$ 的格子的数量其实就是 $n$ 所有约数的约数的和，这个是经典的式子：

  $$\sum_{d \mid n} \tau(d) = \prod_{i=1}^m\sum_{j=0}^{c_i}(i+1)= \prod_{i=1}^m\frac{(c_i+1)(c_i+2)}{2}$$

接下来需要求所有的 $ijA(j)$ 的和，我们记为：

$$S = \sum_{i \mid n,j \mid i} ijA(j)$$

我们改变枚举顺序，得到：

$$S = \sum_{j \mid n} jA(j) \sum_{d \mid \frac{n}{j}} jd = \sum_{j \mid n} j^2A(j)\sigma(\frac{n}{j})$$

不妨设 $j = \prod_{i=1}^m p_i^{e_i}$，其中满足 $\forall i \in [1,m],0 \le e_i \le c_i$，于是我们对于任意一个 $j$ 有：

$$\sum_{j \mid n} j^2A(j)\sigma(\frac{n}{j}) = \prod_{i=1}^m p_i^{2e_i} \times e_i! \times \sigma(p_i^{c_i - e_i})$$

于是我们得到：

$$
\begin{aligned}
S &= \sum_{j \mid n}\prod_{i=1}^m p_i^{2e_i} \times e_i! \times \sigma(p_i^{c_i - e_i})\\ 

&= \prod_{i=1}^m(\sum_{e=0}^{c_i} p_i^{2e}\times e!\times\sigma(p_i^{c_i - e}))
\end{aligned}
$$

然后直接计算 $S$ 即可。具体的，我们有：

$$\sigma(p^k) = 1+p+p^2+\cdots+p^k = \frac{p^{k+1}-1}{p - 1}$$

因为 $a \le 2\times 10^9$，因此不会出现 $p \equiv 1 \pmod {10^9+7}$ 的情况，因此不用特判。

### Code

```cpp
/**
 *    author: luuia
 *    created: 2025.08.16 16:19:42
**/
#include<bits/stdc++.h>
using ll = long long;
#define For(i,j,k) for(int i = j;i <= k;i++)
#define Rep(i,j,k) for(int i = j;i >= k;i--)
#define eb emplace_back
#define pll pair<ll,ll>
using namespace std;
const int N = 1e6 + 10,mod = 1e9 + 7,iv2 = 5e8 + 4;
struct math{ll n;vector<ll> fc,iv,nv;
    void ad(ll &x,ll y){x += y,x >= mod && (x -= mod);}
    ll qpow(ll c,ll n = mod - 2,ll m = mod){ll r = 1;for(;n;n >>= 1,c = c * c % m) if(n & 1) r = r * c % m;return r;}
    math():math(0){}math(ll m){n = m,fc.resize(n + 1),iv.resize(n + 1);
        nv.resize(n + 1),fc[0] = nv[0] = iv[1] = 1;
        For(i,1,n) fc[i] = fc[i - 1] * i % mod;
        For(i,2,n) iv[i] = (mod - mod / i) * iv[mod % i] % mod;
        For(i,1,n) nv[i] = nv[i - 1] * iv[i] % mod;
    }ll C(ll n,ll m){return (n < 0 || m < 0 || n < m) ? 0 : fc[n] * nv[m] % mod * nv[n - m] % mod;}
}mt(N - 5);vector<ll> pr;ll sf[N];
void sol(){ll a,b;cin >> a >> b;vector<pll> fc;ll tp = a;
    for(auto p : pr){if(p * p > tp) break;
        if(tp % p == 0){ll ct = 0;while(tp % p == 0) tp /= p,ct++;fc.eb(p,ct);}
    }if(tp > 1) fc.eb(tp,1);ll o1 = 1,o2 = 1,o3 = 1;
    for(auto [x,y] : fc) o1 = o1 * mt.fc[y * b] % mod;
    for(auto [x,y] : fc) o2 = o2 * (y * b % mod + 1) % mod * (y * b % mod + 2) % mod * iv2 % mod;
    for(auto [x,y] : fc){ll e = y * b;vector<ll> bn(e + 2);bn[0] = 1;
        For(i,1,e + 1) bn[i] = bn[i - 1] * (x % mod) % mod;ll t1 = mt.qpow(x % mod - 1),t2 = 0;
        For(i,0,e) t2 = (t2 + (bn[e - i + 1] - 1) % mod * t1 % mod * bn[i] % mod * bn[i] % mod * mt.fc[i] % mod) % mod;
        o3 = o3 * t2 % mod;
    }ll o = mt.qpow(mt.qpow(a % mod,b),2) - o2 + o3;
    cout << (o1 % mod + mod) % mod << " " << (o % mod + mod) % mod << '\n';
}int main(){
    // freopen("input.in","r",stdin);
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    For(i,2,1e6){if(!sf[i]) sf[i] = i,pr.pb(i);
        for(auto p : pr){if(p * i > 1e6 || p == sf[i]) break;sf[p * i] = p;}
    }ll T;cin >> T;while(T--) sol();return 0;
}
```

---

## 作者：imnoob (赞：1)

## 第一问

首先我们要搞懂这个图和路径是什么意思。

容易发现，从 $ x $ 向外走一步本质上是将 $ x $ 除掉它的一个因子（$ 1 $ 除外）。

先将 $ N $ 因数分解为 $ \prod_{i = 1}^n p_i^{f_i} $，令 $ sum = \sum_{i = 1}^n f_i $。

则我们可以贪心的每次除掉一个质因子，所以 $ E(x) $ 就是 $ \sum_{i = 1}^n f_i $。

然后考虑算 $ T(N) $ 方案数，由基础的排列组合我们容易发现 $ T(N) = \binom{sum}{f_1} \binom{sum - f_1}{f_2} \cdots \binom{sum - \sum_{i = 1}^{n - 1} f_i}{f_n} $。

而在 $ sum $ 一定的情况下，$ T(N) $ 的最大值显然为 $ sum! $。

:::info[证明]

考虑化简 $ T(N) $。

$$
\begin{aligned}

& \binom{sum}{f_1} \binom{sum - f_1}{f_2} \cdots \binom{sum - \sum_{i = 1}^{n - 1} f_i}{f_n} \\

= & \frac{sum!}{(sum - f_1)! f_1!} \frac{(sum - f_1)!}{(sum - f_1 - f_2)! f_2!} \cdots \frac{(sum - \sum_{i = 1}^{n - 1} f_i)!}{f_n!} \\

= & \frac{sum!}{\prod_{i = 1}^n f_i!}

\end{aligned}
$$

显然 $ \prod_{i = 1}^n f_i! \geq 1 $，而当 $ n = sum $，$ f_1 = f_2 = \cdots = f_n = 1 $ 时，$ \prod_{i = 1}^n f_i! = 1 $。

故 $ T(N) \leq sum! $，证毕。

:::

所以：

$$
A(x) = \frac{sum!}{\binom{sum}{f_1} \binom{sum - f_1}{f_2} \cdots \binom{sum - \sum_{i = 1}^{n - 1} f_i}{f_n}} = \prod_{i = 1}^n f_i!
$$

## 第二问

由于当且仅当 $ j \mid i $ 且 $ i \mid N $ 时 $ S_{i, j} = i j A_{i, j} $，我们自然可以分成两部分处理：为 $ 1 $ 的格子和不为 $ 1 $ 的格子（为了方便计算，$ S_{1, 1} $ 属于第二部分）。

而我们可以通过容斥转换为：计算不为 $ 1 $ 的格子上面的数的和 $ H $，和计算不为 $ 1 $ 的格子的数量 $ T $。

### 计算 $ T $

容易发现 $ T = \sum_{i \mid N} \sigma(i) $，其中 $ \sigma(x) $ 表示 $ x $ 的因数数量。

考虑如何计算 $ \sigma(x) $：对于每个 $ x $ 的质因数 $ p $，求出它的质数 $ f $，则质因数 $ p $ 对 $ \sigma(x) $ 的贡献为 $ f + 1 $（因为一个数分解质因数后 $ p $ 的指数的情况一共有 $ f + 1 $ 种）。将贡献乘起来就是 $ \sigma(x) $。

所以通过对于每个质因数分开处理，我们能得出：

$$
T = \sum_{i \mid N} \sigma(x) = \prod_{i = 1}^n \sum_{j = 1}^{f_i + 1} j = \prod_{i = 1}^n \frac{(f_i + 1) (f_i + 2)}{2}
$$

### 计算 $ H $

由定义可得：

$$
H = \sum_{i \mid N} \sum_{j \mid i} i j A(j)
$$

由于 $ A(j) $ 与质因数的指数密切相关，且每个质因数之间又互不相关，我们可以仿照 $ \sigma(x) $ 的算法，对每个质因数分开处理：

$$
H = \prod_{x = 1}^n \sum_{i = 0}^{f_x} \sum_{j = 0}^i p_x^{i + j} j!
$$

由于 $ j! $ 比较难搞，考虑调换枚举顺序：

$$
H = \prod_{x = 1}^n \sum_{j = 0}^{f_x} j! p_x^{j} \sum_{i = j}^{f_x} p_x^{i}
$$

推到这里其实已经差不多结束了，因为我们可以用等比数列公式优化掉 $ \sum_{i = j}^{f_x} p_x^{i} $。

最后通过化简我们可以得到：

$$
H = \prod_{x = 1}^n \frac{1}{1 - p_x} \Big( \sum_{i = 0}^{f_x} i! p_x^{2 i} - p_x^{f_x + 1} \sum_{i = 0}^{f_x} i! p_x^i \Big)
$$

由于 $ N $ 的 $ sum $ 是 $ O(b \log a) $ 级别的，所以最终的时间复杂度为 $ O(T b \log a) $，能够通过此题。

## 代码

```cpp
#include <bits/stdc++.h>
#define Code using
#define by namespace
#define zzx std
Code by zzx;

const int MAXN = 1000000;
const long long mod = 1000000007ll;

long long mul[MAXN + 10];

long long q_pow(long long u, long long v) {
    long long res = 1ll;
    while(v) {
        if(v & 1ll) res = res * u % mod;
        u = u * u % mod; v >>= 1;
    }
    return res;
}

void init() {
    mul[0] = 1ll;
    for(int i = 1; i <= MAXN; ++i) {
        mul[i] = mul[i - 1] * (long long)i % mod;
    }
}

int t, n;
long long a, b;
long long pr[20], cnt[20], inv[20];

void work() {
    cin >> a >> b; n = 0;
    long long N = q_pow(a, b);
    for(long long i = 2ll; i * i <= a; ++i) {
        if(a % i == 0ll) {
            pr[++n] = i; inv[n] = q_pow(a - 1ll, mod - 2ll); cnt[n] = 0ll;
            while(a % i == 0ll) {
                a /= i; ++cnt[n];
            }
        }
    }
    if(a > 1ll) {
        pr[++n] = a; inv[n] = q_pow(a - 1ll, mod - 2ll); cnt[n] = 1ll;
    }
    long long ans = 1ll;
    for(int i = 1; i <= n; ++i) {
        cnt[i] *= b; ans = ans * mul[cnt[i]] % mod;
    }
    cout << ans << ' ';
    long long S = 1ll, T = 1ll;
    for(int i = 1; i <= n; ++i) {
        long long T_p = (cnt[i] + 1ll) * (cnt[i] + 2ll) % mod * q_pow(2ll, mod - 2ll) % mod;
        long long sum1 = 0ll, sum2 = 0ll, Pow = 1ll;
        for(long long j = 0; j <= cnt[i]; ++j) {
            sum1 = (sum1 + mul[j] * Pow % mod) % mod;
            sum2 = (sum2 + mul[j] * Pow % mod * Pow % mod) % mod;
            Pow = Pow * pr[i] % mod;
        }
        long long S_p = (q_pow(pr[i], cnt[i] + 1ll) * sum1 % mod - sum2 + mod) % mod * q_pow(pr[i] - 1ll, mod - 2ll) % mod;
        T = T * T_p % mod; S = S * S_p % mod;
    }
    cout << (N * N % mod + S - T + mod) % mod << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    init(); cin >> t;
    while(t--) work();
    return 0;
}
```

---

## 作者：Ligans (赞：0)

为了叙述方便，先将 $N$ 质因数分解为 $\prod {p_i}^{q_i}$。

## 第一问

考虑 $E(N)$ 的计算。在该有向图上每走一步相当于除掉一个因数，那么最长路径当然是每一步都除掉质因数。即 $E(N)=\sum q_i$。

考虑 $T(N)$ 的计算。这一部分是简单排列组合，得到 $T(N)=\dfrac{(\sum q_i)!}{\prod q_i!}=\dfrac{E(N)!}{\prod q_i!}$。

最后考虑 $A(N)$ 的计算。令上式分母为 $1$，即令 $y$ 为前 $E(N)$ 个质数相乘的积，得到 $T(y)=E(N)!$，此时取最大值。即 $A(N)=\prod q_i!$。

## 第二问

前置芝士：[积性函数](https://oi-wiki.org/math/number-theory/basic/#%E7%A7%AF%E6%80%A7%E5%87%BD%E6%95%B0)。

考虑分别计算普通方格的贡献 $n(N)$ 和特殊方格的贡献 $s(N)$。特殊方格指写有数字 $i×j×A(j)$ 的方格，普通方格指直接写有数字 $1$ 的方格。

第二问的答案显然是 $n(N)+s(N)$。

### 普通方格的贡献

$$n(N)=N^2-\sum_{i\mid N}\sum_{j\mid i}1$$

记后面那个求和式为 $h(N)$，根据积性函数的性质得到这是一个积性函数。

考虑求 $h(p^q)$，不难发现下式。

$$h(p^q)=\prod\frac{(q+1)(q+2)}{2}$$

根据积性函数的定义不难求出 $h(N)$。代入原式，我们求出了普通方格的贡献 $n(N)$。

### 特殊方格的贡献 $s(N)$

$$s(N)=\sum_{i\mid N}i\sum_{j\mid i}jA(j)$$

由第一问知 $A(N)$ 是积性函数，再次根据积性函数的性质得到这也是一个积性函数。

同样考虑求 $s(p^q)$。

在原式的基础上，将枚举因数改为枚举指数。

$$s(p^q)=\sum_{i=0}^{q} p^i \sum_{j=0}^{i} p^j A(j)$$

调换求和顺序。

$$s(p^q)=\sum_{j=0}^{q} p^j A(j) \sum_{i=j}^{q} p^i$$

后面的求和式显然是一个等比数列求和，使用求和公式替换。

$$s(p^q)=\sum_{j=0}^{q}  p^j A(j) \frac{p^{q+1}-p^{j}}{p-1}$$

于是可以在可接受的时间范围内求出 $s(p^q)$。根据积性函数的定义不难求出 $s(N)$。

完结撒花。单次测试复杂度为 $O(\sqrt a+b\log a)$。预处理筛出所用质数，单次测试复杂度为 $O(\dfrac{\sqrt a}{\ln a}+b\log a)$。

```cpp
void calc(ll p,ll q){
	ll res=0;
	_rep(j,0,q) _add(res,fac[j]*(qpow(p,q+j+1)-qpow(p,2*j))%mod*inv(p-1)%mod);
	_mul(ans1,fac[q]);
	_mul(ans2,res);
	_mul(ans3,(q+1)*(q+2)/2);
}
void f(int a){
	ans1=ans2=ans3=1;
	_rep(i,1,cnt){
		int p=P[i],q=0;
		if(p*p>a) break;
		while(a%p==0) a/=p,q++;
		calc(p,q*b);
	}
	if(a!=1) calc(a,b);
}
void sol(){
	a=rd(),b=rd();
	f(a);
	_add(ans2,qpow(a,2*b)-ans3);
	wr(ans1),ptc(' '),wr(ans2),ptc('\n');
}
```

---

题面怎么反复套娃给我看得一愣一愣的。

---

## 作者：xhabc66 (赞：0)

首先考虑路径。路径这个概念很乱斗，考虑转化成比较好想的条件。

不难注意到，每一次走到下一个节点，就相当于将原数除以一个大于 $1$ 的数。我们把这些数排列起来就可以得到一个数列。例如：
```
6->3->1  => 2 3
2025->405->135->27->9->3->1 => 5 3 5 3 3 3
```
那么我们发现，这个数列有两个很重要的性质：
- 每一项都 $>1$；
- 各项之积 $=n$。

那么 $E(x)$ 便很好求出：显然，如果数列中一个数合数，我们可以把它拆成积为它的两个数，而这肯定是最优的。故在最优情况下，**数列中每个数均为质数**，而 $E(x)$ 就等于 $x$ 的质因数的个数。

再考虑 $T(x)$。容易发现，上述“拥有上述两个性质”是“该数列对应了一条路径”的充要条件。并且在最长的情况下，数列中每一个数的数量也都一一确定了。那么 $T(x)$ 就等价于一个经典问题：
- 问：对于 $i \in \{1,A\}$，数列中存在 $a_i$ 个 $i$ 的数列共有多少个？

显然我们可以先算出这 $\sum a_i$ 个数的全排列数量 $(\sum a_i)!$，但我们还要处理内部 $a_i$ 个 $i$ 排列的重复情况，所以我们需要对于每个 $i$，将答案除以 $a_i!$。故答案为：
$$\dfrac{(\sum a_i)!}{\prod(a_i!)}$$
运用唯一分解定理，即设 $x=\prod px_i^{kx_i}$，则有 
$$E(x)=\sum kx_i$$
$$T(x)=\dfrac{(\sum kx_i)!}{\prod(kx_i!)}$$
（**注意 $px$ 和 $kx$ 都是数列名，后文的 $py,ky$ 等也是**）

继续考虑 $A(x)$。由于 $E(x)=E(y)$，故$\sum kx_i=\sum ky_i$。对应到 $T$ 上，其分子相同，那么 $\prod(ky_i!)$ 需要最小。

考虑对于一个正整数阶乘，其最小值为 $1$。故可以考虑构造 $y$ 为 $\sum kx_i$ 个**不同质数之积**，此时分母为 $1$，则有
$$A(x)=\frac{\max\{T(y)\}}{T(x)}=\frac{\sum ky_i}{\frac{\sum kx_i}{\prod(kx_i!)}}=\prod(kx_i!)$$

容易发现，$A(a^b)=\prod((b\times ka_i)!)$。由于 $ka_i \le 31$，故预处理阶乘然后对 $a$ 进行质因数分解即可做出第一问。

继续考虑 $S_n$。设 
- $Ans(n)$ 为：当 $N$ 是 $i$ 的倍数，并且 $i$ 是 $j$ 的倍数时，第 $i$ 行第 $j$ 列的方格的数字之和；
- $Cnt(n)$ 为：满足 $N$ 是 $i$ 的倍数，并且 $i$ 是 $j$ 的倍数的数对 $(i,j)$ 的数量。

显然，答案为 $Ans(n)+a^{2b}-Cnt(n)$。

依据顾恺之吃甘蔗理论，先考虑比较复杂的 $Ans(n)$。

设 $f(i)$ 为满足 $i$ 是 $j$ 的倍数时，$j \times A(j)$ 之和，于是 $Ans(n)=\sum_{d|n}(d\times f(d))$。

发现这个式子很像[狄利克雷卷积](https://oi-wiki.org/math/poly/dgf/#dirichlet-%E5%8D%B7%E7%A7%AF)，于是尝试证明 $A(x)$ 是一个[积性函数](https://oi-wiki.org/math/number-theory/basic/#%E7%A7%AF%E6%80%A7%E5%87%BD%E6%95%B0)。证明如下：
1. 设 $a,b$ 互质；
2. 则 $ab=(\prod pa_i^{ka_i}) \times (\prod pa_i^{ka_i})$；
3. 由于 $a,b$ 互质，故 $\forall (i,j),pa_i\neq pb_j$；
4. 故 $A(ab)=(\prod (ka_i)!) \times (\prod (kb_i)!)=A(a)A(b)$

那么显然，$(xA(x))$ 也是积性函数。

由于有 $f(n)=\sum_{d|n} (dA(d))$，根据狄利克雷卷积的[重要结论](https://oi-wiki.org/math/poly/dgf/#%E4%B8%A4%E4%B8%AA%E7%A7%AF%E6%80%A7%E5%87%BD%E6%95%B0%E7%9A%84-dirichlet-%E5%8D%B7%E7%A7%AF%E4%B9%9F%E6%98%AF%E7%A7%AF%E6%80%A7%E5%87%BD%E6%95%B0)，则 $f(n)$ 为积性函数。显然 $(nf(n))$ 为积性函数。

同理，我们得到了 $Ans(n)$ 为积性函数。

于是，我们有了一个重要结论：
$$Ans(n)=\prod Ans(pn_i^{kn_i})$$
接下来考虑 $Ans(p^k)$ 如何做。

首先注意到 $A(p^k)=k!$，那么有 
$$f(p^k)=\sum_{i=0}^{k} (p^i\times i!)$$
$$Ans(p^k)=\sum_{i=0}^{k}(i\times \sum_{j=0}^{i} (p^j\times j!))$$
那么对于每个 $p$ 可以在 $O(k)$ 的时间复杂度内预处理 $p^j,j!$，然后依据已经预处理好的 $p^j,j!$ 预处理 $\sum_{j=0}^{i} (p^j\times j!)$，最后 $O(k)$ 计算即可。

由于对于每个 $n$，最多有 $\log n$ 个 质因数，故单次复杂度为 $O(\log a^b)=O(b\log a)$ 。

```cpp
//jc 是阶乘 (jie cheng)，不是机惨！！！
long long get_ans(int a,int b){
    long long ans=0,mul=1,mul2=0;
    for(int i=0;i<=b;i++){
        mul2+=(mul*jc[i])%MOD;mul2%=MOD;
        ans+=(mul*mul2)%MOD;ans%=MOD;
        mul*=a;mul%=MOD;
    }
    return ans;
}
```

继续考虑 $Cnt(n)$。显然存在
$$Cnt(n)=\sum_{i|n}(\sum_{j|i}1)$$
由于 $1$ 是积性函数，故 $(\sum_{j|i}1)$ 是积性函数，故 $Cnt(n)$ 是积性函数。

同理，考虑 $Cnt(p^k)$ 的情况。显然有：若 $i=p^k$，则 $(\sum_{j|i}1)=k+1$，则 $Cnt(p^k)=\sum_{i=0}^{k}(k+1) = \dfrac{(k+1)(k+2)}{2}$。

```cpp
long long get_cnt(int a,int b){return (b+1ll)*(b+2ll)/2;}
```

那么我们就做完了。

别看这题解写的很长，但实际上推式子的时候是推的非常舒服的。故这题也没有想象中的那么难。

---

