# Stadium and Games

## 题目描述

有若干队伍参加足球赛。
如果队伍数量为偶数，则两两配对进行比赛，最终淘汰一半的队伍。
当所剩队伍数量为奇数，若剩下一支队，比赛结束；若剩下多支队，这些队伍进行单循环赛（即若有x支队，再进行x（x-1）/2场比赛）。

比如，如果20支队参加比赛：

1.两两配对，进行10场比赛，剩10支队

2.两两配对，进行5场比赛，剩5支队

3.剩下5支队进行单循环比赛，共10场比赛

综上，一共进行了25场比赛

给定比赛场数，计算可以有多少支队进行比赛，升序输出所有可能的队伍数。若无解，输出-1。

## 样例 #1

### 输入

```
3
```

### 输出

```
3
4
```

## 样例 #2

### 输入

```
25
```

### 输出

```
20
```

## 样例 #3

### 输入

```
2
```

### 输出

```
-1
```

# 题解

## 作者：danlao (赞：2)

首先，我们来推一下队伍数量与比赛场数的关系。

我们设队伍数量为 $m$，比赛场数为 $n$。

根据题目，我们可以发现，当 $m$ 为偶数时，会进行 $\dfrac{m}{2}$ 场比赛，然后剩下 $\dfrac{m}{2}$ 支球队，然后重复以上操作；否则，进行 $\dfrac{m \times (m-1)}{2}$ 场比赛，然后比赛结束。

由此，我们设最后剩下的奇数为 $x$，且 $x \times 2^f = m$，则 $x$ 与 $n$ 的关系为 $\dfrac{x\times (x-1)}{2}+x\times \sum_{i=1}^{f-1} 2^i = n$，整理得 $\dfrac{x \times (x-1)}{2}+x \times (2^f-1)=n$。我们要求 $m$，就需要知道 $x$ 的值。但是因为 $n \le 10^{18}$，直接枚举 $x$ 是不行的。此时，我们想到了二分，但由于还有一个未知数 $f$，我们不能直接二分，我们可以枚举一个，二分另一个。众所周知，$2$ 的幂增长很快，对于 $n \le 10^{18}$，$f$ 最大为 $61$，所以我们只需要枚举 $f$，二分 $x$ 即可。对于二分的边界，$x$ 的上限为满足 $\dfrac{x\times (x-1)}{2}+x\times \sum_{i=1}^{f-1} 2^i \le n$ 的 $x$ 的最大值。

代码，[AC记录](https://codeforces.com/contest/325/submission/266057731)：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define hh putchar('\n')
#define int long long
namespace quickread{
	inline int read(){
		int x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
		return x*f;
	}
	inline void write(int x){
	    if(x<0){putchar('-');x=-x;}
	    if(x>9)write(x/10);
	    putchar(x%10+'0');
	}
}
using namespace quickread;
const int N=1e6+10,inf=1;
int n,lg[N],f=0;
int solve(int x,int k){
	int ans=(x-1)*x/2;
	ans+=x*(lg[k]-1);
	return ans;
 }
int binary_search(int l,int r,int k){
	while(l+1<r){
		int mid=l+(r-l+1)/2;
		int x=solve(mid,k);
		if(x<=n) l=mid;
		else r=mid;
	}
	return l;
}
signed main(){
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	n=read();
	lg[0]=1;
	for(int i=1;i<=61;i++) lg[i]=lg[i-1]*2;
	for(int k=0;k<=61;k++){
		int r1=sqrt(n*2),r2=n/max(inf,lg[k]-1);//否则可能会出现除以 0 的情况
		int ans=binary_search(0,min(r1,r2)+2,k);
		if(solve(ans,k)==n&&ans&1)  f=1,write(ans*lg[k]),hh;
	}
	if(!f) write(-1);
	return 0;
}

```

---

## 作者：_Spectator_ (赞：0)

[可能更好的食用体验](/article/0cq4fxwv) $|$ 
[题目传送门](/problem/CF325B) $|$ 
[我的其他题解](/user/523641#article.2)

------------

### ${\color{#00CD00}\text{思路}}$

假设总共有 $x$ 支队伍，且 $x=2^p\cdot a$，其中 $a$ 为奇数。  
此时需要进行的比赛场数 $n=\frac{a(a-1)}{2}+2\cdot a+2^2\cdot a+\dots +2^{p-1}\cdot a=\frac{a(a-1)}{2}+(2^p-1)\cdot a$。

注意到 $p$ 的取值范围很小。那么我们就先枚举 $p$，再看看 $a$ 是否有合法的解。如果 $a$ 有合法的解，就说明 $2^p \cdot a$ 是一个可能的答案。

显然当 $2^p-1$ 确定时，$a$ 与 $n$ 之间是有单调性的。因此用**二分**求出 $a$ 的解就行了。

Trick: 不要直接二分 $a$ 的值，应该令 $a=2k+1$，二分 $k$ 的值，这样可以确保 $a$ 的解为奇数。

实现上可能有一些坑点，具体见代码。

------------

### ${\color{#00CD00}\text{代码}}$

```cpp
#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define int long long //记得开 long long
using namespace std;
int n;
vector<int>ans;
signed main(){
	ios::sync_with_stdio(false),cin.tie(0);
	cin>>n;
	for(int p=0;;p++){
		int s=(1ll<<p)-1; //1ll 后面的 ll 不能漏，不然会爆炸。。。
		if(s>n)break;
		int l=0,r=1e9;
		while(l+1<r){
			int mid=(l+r)>>1;
			double a=2*mid+1; //可能会爆 long long，因此用 double 存，如果你 Wa #38 可能是因为这个
			if(a*(a-1)/2+a*s>n)r=mid;
			else l=mid;
		}
		int a=2*l+1;
		if(a*(a-1)/2+a*s==n) //判断 a 是否为合法的解
          ans.push_back(a<<p);
	}
	if(ans.empty())return cout<<"-1\n",0;
	sort(ans.begin(),ans.end()); //最后排个序
	for(int x:ans)cout<<x<<"\n";
	return 0;
}
```  
PS: 或者也可以不二分，直接用一元二次方程的求根公式求出 $a$ 的根。但是因为精度误差等问题导致我一直无法 AC……如果有大佬用这种方式过了可以告诉我 qwq。

---

## 作者：Wei_Han (赞：0)

假设有 $k$ 只队伍，从特例开始考虑，假设没有最后的单循环赛，也就是当 $k$ 为 $2$ 的某次方时，比如当 $k=16$，我们的比赛场数就为 $8+4+2+1=15$，换句话讲，此时的比赛场数总是在二进制下为 $111....$ 的形式，也就是 $2^a-1$。

推广到一般形式，假如没有了 $k$ 的限制，我们最后一场可能会是单循环赛，如果此时剩了 $m$ 只队伍，那么前一场一定会是淘汰赛，上一场的队伍就是 $2m$ 只，进一步的，上上场就是 $2^2m$ 只。此时的比赛场数就为 $\frac{m(m-1)}{2}+\sum_{i=0}2^im$，将后半部分的 $m$ 提出，剩下的部分写成二进制就还是原本的 $2^a-1$ 形式，那么此时的式子就可以写成 $\frac{m(m-1)}{2}+m\times(2^a-1) = n$，这个 $a$ 不超过 $64$，可以直接枚举，注意到 $m$ 显然具有单调性，就可以二分了。

注意，此处如果直接二分 $m$，$\frac{m(m-1)}{2}$ 是可能爆 long long 的，因为 $m$ 一定为奇数，写成 $2\times m+1$ 再二分即可。

时间复杂度 $O(\log n)$
### Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define pr printf("\n")
#define pp printf(" ")
#define pii pair<int,int>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; i ++ )
#define Fo(a,i,b) for(ll i = a ; i >= b ;-- i  )
#define bug(x,y) (x<1||y<1||x>15||y>15)
using namespace std;
typedef long long ll;
typedef double db;
const int N=3e5+5,M=1e7+5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}
ll n,pw[N];
priority_queue<ll,vector<ll>,greater<ll> > st;
signed main(){
	read(n);
    fo(0,i,62){
        ll l=0,r=1,sum=(1ll<<i)-1,ans=-1;while((2*r+1)*sum+(2*r+1)/2*(2*r+1)<=n) r<<=1; 
        while(l<=r){
            ll mid=l+r>>1;
            if((2*mid+1)*sum+(2*mid+1)/2*(2*mid+1)<=n)  ans=mid,l=mid+1;
            else r=mid-1;
        }
        // wr((ans*2+1)<<i);pr;
        if(~ans&&(2*ans+1)*sum+(2*ans+1)/2*(2*ans+1)==n) st.push((ans*2+1)<<i);
    }
    if(st.empty()) wr(-1),pr;
    else while(!st.empty()) wr(st.top()),pr,st.pop();
	return 0;
}
``````

---

## 作者：Leap_Frog (赞：0)

### P.S.
题解一血！  
不吧，这场什么毒瘤场，T3 T4 T5 全是图论？？？ ![](//xn--9zr.tk/jy)  

### Description.
略

### Solution.
设比赛中有 $X$ 层淘汰赛。  
那么就有 $N=\frac{M\times(M-1)}2+M\times(2^X-1)$。  
同时，有 $M\equiv 1\pmod 2$。  
$\because \frac{M\times(M-1)}2\ge 0$  
$\therefore 2^X-1\le N$  
$\therefore X\le \log_2(N+1)<63$  
所以我们可以枚举 $X$。  
我们发现 $\frac{M\times(M-1)}2+M\times(2^X-1)$ 随 $M$ 单增。  
所以我们直接二分 $M$ 就可以了。  
注意 $M$ 为奇数，我们直接设 $M=2\times m+1$ 即可。  

### Coding.
[略](https://codeforces.com/contest/325/submission/111601552)

---

