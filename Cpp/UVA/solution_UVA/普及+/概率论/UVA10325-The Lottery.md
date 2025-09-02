# The Lottery

## 题目描述

给出 $n , m$，和 $m$ 个数 $a[1] \cdots a[m]$。

求 $1 \cdots n$ 中不被 $a[1] \cdots a[m]$ 中任意一个整除的数的个数。

## 样例 #1

### 输入

```
10 2
2 3
20 2
2 4```

### 输出

```
3
10```

# 题解

## 作者：TimeTraveller (赞：5)

容斥入门题一道，~~蒟蒻的第一道自己yy出的容斥~~

其实就是你统计出$n$以内能被整除的个数，再用总个数减去可行的个数，就是不可行的个数啦，但是对于$2^{31}$，显然不能枚举，那么就容斥吧。

我们先对于一个数$x$，$n$以内能被他整除的个数就是$n/x$向下取整这么多个，所以就可以$O(1)$的统计出这个个数。但对于多个数字，如果你加上对于$x$和$y$分别的能被整除的个数的话，那么既能被$x$整除的又能被$y$整除的就多算了一次，(可以自己在本子上画维恩图理解)，那么就要减去多算的个数，然后依次类推啦。

上代码：

```
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
using namespace std;
ll n,m,a,b;
ll ans,num[20];
ll gcd(ll a,ll b){
	if(!b) return a;
	else return gcd(b,a%b);
}
ll lcm(ll a,ll b){
	return a/gcd(a,b)*b;
}
void dfs(int pos,ll a,int pd){
	ll now=-1ll;
	if(!pd) now=1ll;
	if(pos)ans+=(n/a)*now;
	else a=1;
	if(pos==m) return;
	for(int i=pos+1;i<=m;i++){
		dfs(i,lcm(a,num[i]),pd^1);
	}
}
int main(){
	while(scanf("%lld%lld",&n,&m)==2){
		ans=0;
		for(int i=1;i<=m;i++) scanf("%lld",&num[i]);
		dfs(0,0,1);
		printf("%lld\n",n-ans);
	}
	return 0;
}
/*
精简版
void slove(int i,int a,long long v)
{
	if(a%2)ans+=n/v;else ans-=n/v;
    for(;i<=m;i++)
     slove(i+1,a+1,lcm(v,num[i]));
}
int main()
{
    while(scanf("%lld%d",&n,&m)==2)
    {
        for(int i=1;i<=m;i++)
         scanf("%lld",&num[i]);
        for(int i=1;i<=m;i++)
         slove(i+1,1,num[i]);
        printf("%lld\n",n-ans);ans=0;
    }
    return 0;
}
*/
```

---

## 作者：千秋星辰 (赞：2)

**首先，这是一个数学题。**

### 思路

1. ~~概括题意，但题意已经够简练了~~，但是你能发现数据范围 $m\le 15$，易联想到复杂度可能是 $O(2^m)$。

2. 看题目里也没什么特别的地方，手搓一下样例：因为 $a_1=2$，所以去掉了 $\left\lfloor\dfrac{10}{2}\right\rfloor=5$ 个数，因为 $a_2=3$，所以去掉了 $\left\lfloor\dfrac{10}{3}\right\rfloor=3$ 个数，但是其中的 $6$ 多去掉了一次，于是补回来 $\left\lfloor\dfrac{10}{6}\right\rfloor=1$ 个数。所以最终答案是 $10-7=3$。

3. 看到上面，我们便很容易想到**容斥原理**。从全集里面找出几个集合，再把交集去掉，再把交集的交集加上...以此类推，正好能不重不漏地找到集合中所有元素。所以我们要求 $\sum\limits_{i=1}^n{\left\lfloor\dfrac{n}{a_i}\right\rfloor}-\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n{\left\lfloor\dfrac{n}{lcm(a_i,a_j)}\right\rfloor}+...$。

4. 可以看到，如果按这种写法的话，复杂度刚好是 $O(2^m)$，可以状态压缩实现。

```
void DFS()
{
	int cnt,tmp;
	for(int S=1;S<(1ll<<m);++S)
	{
		cnt=BITcount(S),tmp=1;
		for(int i=1;i<=m;++i)
			if(S&(1ll<<(i-1))) tmp=lcm(tmp,a[i]);
		if(cnt%2) ans+=n/tmp;
		else ans-=n/tmp;
	}
}
```

这里的```BITcount()```作用是统计一个数二进制表示下一的个数。

同样地，也可以写递归式dfs。

```
void dfs(int x,bool opt,int res)
{
	if(x>m) return ;
	if(x)
	{
		if(opt) ans+=n/res;
		else ans-=n/res;
	}
	for(int i=x+1;i<=m;++i)
		dfs(i,opt^1,lcm(res,a[i]));
}
```

### AC code

```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define int long long
#define forever() while(true)
#define out(x) write(x),putchar(' ')
#define writen(x) write(x),putchar('\n')

namespace IO
{
	#define gc getchar
	#define pc putchar
	inline int read()
	{
		int x=0,y=1;char c=gc();
		for(;c<'0'||c>'9';c=gc()) if(c=='-') y=-y;
		for(;c>='0'&&c<='9';c=gc()) x=x*10+(c^'0');
		return x*y;
	}
	void write(int x)
	{
		if(x<0) pc('-'),x=-x;
		if(x>9) write(x/10);
		pc(x%10+'0');
	}
	#undef gc
	#undef pc
}

using namespace std;
using namespace IO;
int n,m,a[20],ans;
bool ban[20];

int BITcount(int num)
{
	int res=0;
	while(num)
	{
		if(num&1) ++res;
		num>>=1;
	}
	return res;
}

int lcm(int a,int b)
{
	int GCD=__gcd(a,b);
	return a/GCD*b;
}

void dfs(int x,bool opt,int res)
{
	if(x>m) return ;
	if(x)
	{
		if(opt) ans+=n/res;
		else ans-=n/res;
	}
	for(int i=x+1;i<=m;++i)
		dfs(i,opt^1,lcm(res,a[i]));
}

void DFS()
{
	int cnt,tmp;
	for(int S=1;S<(1<<m);++S)
	{
		cnt=BITcount(S),tmp=1;
		for(int i=1;i<=m;++i)
			if(S&(1<<(i-1))) tmp=lcm(tmp,a[i]);
		if(cnt%2) ans+=n/tmp;
		else ans-=n/tmp;
	}
}

signed main()
{
	while(scanf("%lld%lld",&n,&m)==2)//uva的奇怪输入格式
	{
		ans=0;//这里的ans意为删去的数
		for(int i=1;i<=m;++i) a[i]=read();
		dfs(0,0,1);
		writen(n-ans);
	}
	return (0^0);
}
```

---

## 作者：EnofTaiPeople (赞：2)

本人在学容斥原理入门的时候查 tag 查到了这道题，这道题就是裸的容斥模板。

前置知识：求最小公倍数、容斥原理。

简单提一句，最小公倍数的求法参照这个公式：$\operatorname{lcm}(x,y) * \gcd(x,y)=x * y$，容斥原理的介绍参照[这个链接](https://oi-wiki.org/math/combinatorics/inclusion-exclusion-principle/)，不难发现，容斥原理是一个求并集的好方法，此题也可以转化为求被 $a[1]-a[m]$ 中某一个数整除这 $m$ 个数集的并集对于 $[1,n]$ 的补集的元素个数。用容斥原理展开之后，交集就是被它们最小公倍数的数的个数。具体详见代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,num[20],i,len,ans,l,r;
inline ll LCM(ll &x,ll &y){return x*y/__gcd(x,y);}
//求最小公倍数	
void DFS(int x,int Tp,ll now){
//dfs中，x表示当前数的下标，Tp用作统计答案，now表示之前数的lcm
	if(x>m)return;DFS(x+1,Tp,now);//考虑不选x
	now=LCM(now,num[x]);ans+=Tp*(n/now);
//如果选x，那么之后的数不选也是一种方案。	 
	return DFS(x+1,-Tp,now);
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0); 
	while(cin>>n>>m){
		for(i=1;i<=m;++i)cin>>num[i];
		ans=0;DFS(1,1,1);ans=n-ans;//记得我们求的是补集		 
		cout<<ans<<endl;
	}return 0;
}
```

---

## 作者：SJH__qwq (赞：0)

容斥入门题。容易发现奇怪的数据范围 $m\le \color{red}{15}$，所以考虑有关 $m$ 的指数级算法。

先正难则反，即求 $n$ 减去至少能被一个数整除的个数。后面这个求解是容易的，根据容斥原理可以得到答案为 $n$ 减去至少能被一个数整除的数量加上至少能被两个数整除的数量减去至少能被三个数整除的数量加上……

后半部分直接暴力搜索即可。总的时间复杂度为 $O(2^m)$。

---

## 作者：david0911 (赞：0)

容斥入门题。

要求出 $1$ 到 $n$ 之间不能被 $a_1$ 到 $a_m$ 中任意一个数整除的个数，可以考虑用总数减去不合法的个数。

记 $f_i$ 表示 $1$ 到 $n$ 之间被 $a_1$ 到 $a_m$ 中至少 $i$ 个数整除的数的个数，$k$ 表示不合法的个数，运用容斥原理可以得到下式。

$$k=\sum_{i=1}^m(-1)^{i+1}\times f_i$$

现在考虑如何处理 $f$ 数组，我们想到可以搜索。

我们知道 $1$ 到 $n$ 之间能被 $i$ 整除的数的个数为 $\lfloor n/i \rfloor$。设当前已经从 $a$ 数组里挑出了 $x$ 个数，记这些数的最小公倍数为 $s$，则其对 $f_x$ 的贡献为 $\lfloor \frac{n}{s} \rfloor$。

最终答案即为 $n-k$，时间复杂度为 $O(2^m)$。

**AC Code**

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int n,m,a[20];
ll ans;

ll gcd(ll a,ll b){
	if(b==0) return a;
	return gcd(b,a%b);
}


void dfs(int cnt,int now,ll s){
	if(now>m){
		return;
	}
	dfs(cnt,now+1,s);
	int k=gcd(s,a[now]);
	s=s/k*a[now];
	if(s<1||s>n) return;
	ans+=((cnt+1)&1?1:-1)*(n/s);
	dfs(cnt+1,now+1,s);
}

int main(){
	while(scanf("%d%d",&n,&m)==2){
		for(int i=1;i<=m;++i){
			scanf("%d",&a[i]);
		}
		dfs(0,1,1);
		printf("%lld\n",n-ans);
		memset(a,0,sizeof(a));
		ans=0;
	}
	return 0;
} 
```


---

## 作者：极寒神冰 (赞：0)

不被$m$个数的任意一个数整除，可以理解为总数减去$m$个数的任意一个数整除。

使用容斥原理。

![](https://bkimg.cdn.bcebos.com/formula/7d7995fe072ad886e2c5a4d5dddc1237.svg)![](https://bkimg.cdn.bcebos.com/formula/c14b2ae75dc2656967cb2e2dedbe57cd.svg)

即所有一个数的倍数减去两个数的倍数加上三个数的倍数。（多个数倍数即为这些数最小公倍数的倍数

```

#include<bits/stdc++.h>
#define int long long
using namespace std;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
const int M=20;
int n,m;
int a[M];
int sum;

int gcd(int a,int b){return (b==0)?a:gcd(b,a%b);}
int lcm(int a,int b){return 1ll*a*b/gcd(a,b);}

void dfs(int dep,int tot,int mul,int has)
{
	if(dep==tot+1)
	{
		if(!has) return;
		else if(has%2==1) sum+=n/mul;
		else sum-=n/mul;
		return;
	}
	dfs(dep+1,tot,lcm(mul,a[dep]),has+1);
	dfs(dep+1,tot,mul,has);
}


signed main()
{
	while(scanf("%lld%lld",&n,&m)==2)
	{
		sum=0;
		for(int i=1;i<=m;i++) a[i]=read();
		dfs(1,m,1,0);
		printf("%lld\n",n-sum);
	}
}
```


---

