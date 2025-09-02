# Polynomial Divisors

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2019/tasks/tenka1_2019_e

$ N $ 次の整数係数多項式 $ f(x)=a_Nx^N+a_{N-1}x^{N-1}+...+a_0 $ が与えられます。任意の整数 $ x $ に対して $ p $ が $ f(x) $ を割り切るような素数 $ p $ をすべて求めてください。

## 说明/提示

### 制約

- $ 0\ \leq\ N\ \leq\ 10^4 $
- $ |a_i|\ \leq\ 10^9(0\leq\ i\leq\ N) $
- $ a_N\ \neq\ 0 $
- 入力はすべて整数である

### Sample Explanation 1

$ 2,7 $ は例えば、$ f(1)=14 $ や $ f(2)=28 $ を割り切ります。

### Sample Explanation 2

条件を満たす素数がない場合もあります。

## 样例 #1

### 输入

```
2
7
-7
14```

### 输出

```
2
7```

## 样例 #2

### 输入

```
3
1
4
1
5```

### 输出

```
```

## 样例 #3

### 输入

```
0
998244353```

### 输出

```
998244353```

# 题解

## 作者：cwfxlh (赞：1)

# [AT_tenka1_2019_e](https://www.luogu.com.cn/problem/AT_tenka1_2019_e)       

第一次做这种题，独立做出来了，挺有意思的，写一下题解记录一下思路。       

显然第一步应该考虑如何 check 一个模数 $p$。有一个显然的 $O(np)$ 的做法，就是代入 $[0,p-1]$ 的数去跑一遍。但是这样无法处理 $p$ 比较大的情况。         

当 $p>n$ 的时候，我们知道这个多项式的 $p$ 个点值，分别是 $(0,0),(1,0),(2,0)\dots(p-1,0)$。对着前 $n+1$ 个点进行拉格朗日插值，插出来的多项式每项都等于 $0$。所以原来的多项式必须满足所有系数 $a_i\equiv 0\pmod p$。于是这部分可以 $O(n)$ 解决了。      

当 $p<=n$ 的时候，考虑对于 $x\in(0,p)$ 都有 $x^{p-1}\equiv1 \pmod p$。于是对于 $x=0$ 特殊判断，对于 $x\in(0,p)$，将 $a_i$ 加到 $a_{i\bmod {p-1}}$ 上，变成一个 $p-1$ 次多项式，再使用上面的办法即可。      

现在我们能够 $O(n)$ 的 check 一个 $p$ 了。枚举 $[1,n]$ 的质数 check，对于大于 $n$ 的，其必须是所有系数的质因数，取 $\gcd$ 然后枚举质因数即可。       

代码：        


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[500003],gd,ans[500003],tot,k1,k2,k3,k4,k5,k6;
bool chk(int X){
    if(X<=1)return false;
    if(gd%X==0)return true;
    if(X>n)return false;
    if(a[0]%X!=0)return false;
    for(int i=0;i<X-1;i++){
        k4=0;
        for(int j=i;j<=n;j+=(X-1))k4=(k4+a[j])%X;
        k4%=X;
        k4+=X;
        k4%=X;
        if(k4!=0)return false;
    }
    return true;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=n;i>=0;i--)cin>>a[i];
    gd=abs(a[0]);
    for(int i=1;i<=n;i++)gd=__gcd(gd,abs(a[i]));
    k1=gd;
    for(int i=2;i*i<=k1;i++){
        if(k1%i!=0)continue;
        if(i>n&&chk(i))ans[++tot]=i;
        while(k1%i==0)k1/=i;
    }
    if(k1!=1&&k1>n)if(chk(k1))ans[++tot]=k1;
    for(int i=2;i<=n;i++){
        k5=1;
        for(int j=2;j*j<=i;j++)if(i%j==0)k5=0;
        if(k5==0)continue;
        if(chk(i))ans[++tot]=i;
    }
    sort(ans+1,ans+tot+1);
    for(int i=1;i<tot;i++)cout<<ans[i]<<'\n';
    if(tot!=0)cout<<ans[tot];
    return 0;
}
```

---

## 作者：Super_Cube (赞：1)

# Solution

~~不会有人看到这题去想正解吧。~~

注意到 $n$ 不大，还给了 2s，考虑乱搞。

首先 $\displaystyle\gcd_{i=0}^na_i$ 的所有质因数肯定是答案。猜测除去这些答案剩下的质因数不多也不大，于是暴力枚举 $2\sim 10^5$ 的所有质数（可以提前筛或者直接判），然后检查是否符合要求。检查的方法也很随意，随机 $20$ 个 $x$ 然后 $O(n)$ 计算 $f(x)\bmod p$，若全为 $0$ 就合法，否则不行。最后排序去重之后输出就可以了。

上述阈值可以根据你的想法随意调整。

---

## 作者：Grisses (赞：0)

给定 $N$ 次多项式 $f(x)=a_N\times x^N+a_{N-1}\times x^{N-1}+\dots+a_0$ ，请求出所有满足以下条件的质数 $p$ ：对于任意整数 $x$ ，$f(x)$ 都是 $p$ 的倍数。从小到大输出。

---
注意到对于一个质数 $p$，有 $a_ix^i\equiv a_ix^{i\bmod(p-1)}\pmod p$，所以我们可以 $O(n)$ 将 $f(x)$ 转化为一个 $\min(n,p-2)$ 次的多项式并判断其是否符合要求。

接下来我们对 $a_0$ 的值进行分讨：

- 若 $a_0\not=0$，则 $f(0)=a_0$，所以符合条件的只有 $a_0$ 的质因子。
- 若 $a_0=0$，那我们设 $g=\gcd\limits_{i=1}^na_i$，显然所有 $g$ 是质因子是满足条件的。同时对于一些小于 $n+1$ 的质数也有可能通过降幂改变系数让 $p$ 是满足条件的。所以我们再暴力判断小于 $n+1$ 的质数，并把合法的加入答案。

---
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char buf[1000005],*p1,*p2;
#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++)
int read(){
	int x=0,f=0,c=gc();
	while(!isdigit(c))f|=(c=='-'),c=gc();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=gc();
	return f?-x:x;
}
char puf[1000005];
int ptot;
#define pc(x) (ptot==1000000?(fwrite(puf,1,1000000,stdout),ptot=0,puf[ptot++]=x):puf[ptot++]=x)
void print(int x){
	if(x<0){
		pc('-');
		print(-x);
		return;
	}
	if(x>9)print(x/10);
	pc(x%10+'0');
}
int n,a[10005],b[10005];
vector<int>ans;
void ch(int x){
	for(int i=0;i<=min(x,n);i++)b[i]=0;
	for(int i=0;i<=n;i++)b[i%(x-1)]=(b[i%(x-1)]+a[i]%x+x)%x;
	for(int i=0;i<=min(x,n);i++){
		if(b[i])return;
	}
	ans.push_back(x);
}
int p[10005],tot;
bool f[100005];
void ss(){
	for(int i=2;i<=10000;i++){
		if(!f[i])p[++tot]=i;
		for(int j=1;i*p[j]<=10000&&j<=tot;j++){
			f[i*p[j]]=1;
			if(i%p[j]==0)break;
		}
	}
}
signed main()
{
	n=read();
	for(int i=n;i>=0;i--)a[i]=read();
	if(a[0]!=0){
		int x=abs(a[0]);
		for(int i=2;i*i<=x;i++){
			if(x%i==0){
				ch(i);
				while(x%i==0)x/=i;
			}
		}
		if(x>1)ch(x);
	}
	else{
		ss();
		int gcd=0;
		for(int i=0;i<=n;i++)gcd=__gcd(gcd,a[i]);
		gcd=abs(gcd);
		for(int i=2;i*i<=gcd;i++){
			if(gcd%i==0){
				if(i>n)ans.push_back(i);
				while(gcd%i==0)gcd/=i;
			}
		}
		if(gcd>1&&gcd>n)ans.push_back(gcd);
		for(int i=1;i<=tot&&p[i]<=n;i++){
			ch(p[i]);
		}
		sort(ans.begin(),ans.end());
	}
	for(int x:ans)print(x),pc(10);
	fwrite(puf,1,ptot,stdout);
	return 0;
}
```

---

## 作者：masterhuang (赞：0)

推销[博客](https://www.cnblogs.com/HaHeHyt/p/17773631.html)！第 $14$ 题。

前置知识：[拉格朗日定理](https://zhuanlan.zhihu.com/p/646388312)。

设 $g=\gcd\limits_{i=0}^n a_i$，则 $|g|$ 的所有素因子都满足条件。

考虑剩下的，若 $p$ 为满足条件的素数，则多项式 $A$ 必有因式 $\prod\limits_{i=0}^{p-1}(x-i)\equiv x^p-x\pmod p$。同余这步可以参考前置知识中文章。

于是得出 $\forall k\sum\limits_{i=0}^n [i\equiv k\pmod {p-1}]a_i=0$。

对于每个素数判一下即可，由拉格朗日定理得 $p\le n$。

复杂度 $O(\dfrac{n^2}{\ln n})$，跑不满。

代码：

```cpp
//洛谷 AT_tenka1_2019_e
//https://www.luogu.com.cn/problem/AT_tenka1_2019_e
#include<bits/stdc++.h>
#define LL long long
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
const int N=1e4+5;
int n,g,a[N],b[N],pr[N];bool v[N];
basic_string<int>ans;
inline void init(int M)
{
	for(int i=2;i<=M;i++)
	{
		if(!v[i]) pr[++pr[0]]=i;
		for(int j=1;j<=pr[0]&&i*pr[j]<=M;j++)
		{
			v[i*pr[j]]=1;
			if(i%pr[j]==0) break;
		}
	}
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);cin>>n;
	for(int i=n;~i;i--) cin>>a[i],g=__gcd(g,a[i]);g=abs(g);
	for(int i=2;i*i<=g;i++) if(!(g%i)){ans+=i;while(!(g%i)) g/=i;}
	if(g^1) ans+=g;init(n);
	for(int i=1;i<=pr[0];i++)
	{
		int p=pr[i];bool ok=1;if(a[0]%p) continue;
		for(int j=0;j<p-1;j++) b[j]=0;
		for(int j=0;j<=n;j++) b[j%(p-1)]=(b[j%(p-1)]+a[j]%p+p)%p;
		for(int j=0;j<p-1;j++) if(b[j]){ok=0;break;}if(ok) ans+=p;
	}sort(ans.begin(),ans.end());ans.erase(unique(ans.begin(),ans.end()),ans.end());
	for(int i:ans) cout<<i<<"\n";
	return 0;
}

```

---

