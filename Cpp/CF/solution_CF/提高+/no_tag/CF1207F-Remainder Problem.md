# Remainder Problem

## 题目描述

给你一个长度为 $500000$ 的序列，初值为 $0$ ，你要完成 $q$ 次操作，操作有如下两种：
1. `1 x y` : 将下标为 $x$ 的位置的值加上 $y$
2. `2 x y` : 询问所有下标模 $x$ 的结果为 $y$ 的位置的值之和

## 样例 #1

### 输入

```
5
1 3 4
2 3 0
2 4 3
1 4 -4
2 1 0
```

### 输出

```
4
4
0
```

# 题解

## 作者：BFSDFS123 (赞：12)

是根号算法，然而不是分块。

是论文，然而不是莫队。

----

这道题，我们选择用**根号分治**来做。

顾名思义，根号分治，就是将询问根据数据大小分成两个部分，分别用不同的方法来做。

根号分治，将询问分成两个部分的分界线，就是 $\sqrt n$。

我们可以将询问小于 $\sqrt n$ 的所有问题存到一个数组中，大于等于 $\sqrt n$ 直接暴力查找。

为什么可以这样？

如果直接暴力，是 $O(n^2)$ 的，肯定过不了。

这样分开后。我们分开我们在每次修改的时候更新答案。这样，在这道题中，数组的空间复杂度是 $O(\sqrt n\times \sqrt n)=O(n)$，每次修改的时间复杂度是 $O(\sqrt n)$，查询是 $O(1)$ 的，足够通过。

数据大小大于 $\sqrt n$ 的询问，每次修改，直接 $O(1)$ 修改，在查询时直接暴力 $O(\sqrt n)$ 碾过去。

总时间复杂度就是 $O(\sqrt n)+O(\sqrt n)=O(\sqrt n)$，足以通过此题。

代码：

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
//#define LL_inf 1145141919810
//#define int long long
#define ull unsigned long long
#define ll long long
using namespace std;
int ans[5000][5000]; //ans[i][j]意义：对 j 取模为 i 的答案。针对数据大小为前 sqrt(n)
int Ar[500000]; //数组，保存单点修改和暴力查询。针对数据大小为后sqrt(n)
int main()
{
	int q;
	scanf("%d",&q);
	int siz=sqrt(500000);
	while(q--)
	{
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1)
		{
			for(int i=1;i<=siz;i++)
			{
				ans[x%i][i]+=y; 修改所有 ans 数组
			}
			Ar[x]+=y; //直接单点修改
		}else{
			if(x<=siz)
			{
				printf("%d\n",ans[y%x][x]);
			}else{
				int ans=0;
				for(int i=y;i<=500000;i+=x) 
				{
					ans+=Ar[i];
				}
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}

```

---

## 作者：引领天下 (赞：8)

这个题其实有原题的……[参见P3396](https://www.luogu.org/problem/P3396)

看到$500000$的数据范围想必大家也有感觉，$O(n^2)$的暴力可以不用考虑了……~~要是您能n方过百万那么当我没说~~

然而我们又是对每次%一个数之后的一些数进行操作，所以线段树/树状数组也不太好维护

~~您能写出来那是我太弱，Orz~~

有没有什么方法能快速解决这些关于%的问题的呢？

联想到分块，分块的本质就是对于每个数%之后放进相对应的块中，然后大的直接统计，小的直接暴力。而且$O(\sqrt{n})$的算法复杂度，也是可以承受的。

那么我们就可以采用基于分块的思想解决这个问题了。

于是代码就呼之欲出了：

```cpp
#include <bits/stdc++.h>
using namespace std;
int m,opt,x,y;
#define ll long long
ll ans[710][710],a[500005];
const int n=500000;
struct control
{
    int ct,val;
    control(int Ct,int Val=-1):ct(Ct),val(Val){}
    inline control operator()(int Val)
    {
        return control(ct,Val);
    }
}_endl(0),_prs(1),_setprecision(2);
struct FastIO
{
    #define IOSIZE 1000000
    char in[IOSIZE],*p,*pp,out[IOSIZE],*q,*qq,ch[20],*t,b,K,prs;
    FastIO():p(in),pp(in),q(out),qq(out+IOSIZE),t(ch),b(1),K(6){}
    ~FastIO(){fwrite(out,1,q-out,stdout);}
    inline char getch()
    {
        return p==pp&&(pp=(p=in)+fread(in,1,IOSIZE,stdin),p==pp)?b=0,EOF:*p++;
    }
    inline void putch(char x)
    {
        q==qq&&(fwrite(out,1,q-out,stdout),q=out),*q++=x;
    }
    inline void puts(const char str[]){fwrite(out,1,q-out,stdout),fwrite(str,1,strlen(str),stdout),q=out;}
    inline void getline(string& s)
    {
        s="";
        for(register char ch;(ch=getch())!='\n'&&b;)s+=ch;
    }
    #define indef(T) inline FastIO& operator>>(T& x)\
    {\
        x=0;register char f=0,ch;\
        while(!isdigit(ch=getch())&&b)f|=ch=='-';\
        while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getch();\
        return x=f?-x:x,*this;\
    }
    indef(int)
    indef(long long)
    inline FastIO& operator>>(char& ch){return ch=getch(),*this;}
    inline FastIO& operator>>(string& s)
    {
        s="";register char ch;
        while(isspace(ch=getch())&&b);
        while(!isspace(ch)&&b)s+=ch,ch=getch();
        return *this;
    }
    inline FastIO& operator>>(double& x)
    {
        x=0;register char f=0,ch;
        double d=0.1;
        while(!isdigit(ch=getch())&&b)f|=(ch=='-');
        while(isdigit(ch))x=x*10+(ch^48),ch=getch();
        if(ch=='.')while(isdigit(ch=getch()))x+=d*(ch^48),d*=0.1;
        return x=f?-x:x,*this;
    }
    #define outdef(_T) inline FastIO& operator<<(_T x)\
    {\
        !x&&(putch('0'),0),x<0&&(putch('-'),x=-x);\
        while(x)*t++=x%10+48,x/=10;\
        while(t!=ch)*q++=*--t;\
        return *this;\
    }
    outdef(int)
    outdef(long long)
    inline FastIO& operator<<(char ch){return putch(ch),*this;}
    inline FastIO& operator<<(const char str[]){return puts(str),*this;}
    inline FastIO& operator<<(const string& s){return puts(s.c_str()),*this;}
    inline FastIO& operator<<(double x)
    {
        register int k=0;
        this->operator<<(int(x));
        putch('.');
        x-=int(x);
        prs&&(x+=5*pow(10,-K-1));
        while(k<K)putch(int(x*=10)^48),x-=int(x),++k;
        return *this;
    }
    inline FastIO& operator<<(const control& cl)
    {
        switch(cl.ct)
        {
            case 0:putch('\n');break;
            case 1:prs=cl.val;break;
            case 2:K=cl.val;break;
        }
    }
    inline operator bool(){return b;}
}io;
int main(){
    io>>m;
    int sz=sqrt(n);//每个块的大小
    while (m--){
        io>>opt>>x>>y;
        if (opt==2){
            if (x<=sz)io<<ans[x][y]<<"\n";//可以直接进行的查询操作，直接输出
            else{
                ll sum=0;
                for (int i=y;i<=n;i+=x)sum+=a[i];
                io<<sum<<"\n";//否则暴力解决
            }
        }
        else if (opt==1){
            for (int p=1;p<=sz;p++)ans[p][x%p]+=y;//把修改x会产生影响的块的值都更新
            a[x]+=y;//然后更新原数组
        }
    }
}
```

---

## 作者：parallet (赞：4)

> [**CF1207F Remainder Problem**](https://www.luogu.com.cn/problem/CF1207F)

> 解题报告

考虑设阈值 $B$。

对于询问，若 $x>B$，那么我们暴力跳进行查询，复杂度 $\Theta(\frac{n}{B})$。

若 $x\le B$，考虑设 $F_{i,j}$ 表示位置模 $i$ 结果为 $j$ 的位置上的元素和，那么答案即为 $F_{x,y}$，这里的空间是 $\Theta(B^2)$ 的。

对于修改，我们直接枚举一个模数 $i$，令 $F_{i,x\bmod i}\leftarrow F_{i,x\bmod i}+y$，这是修改的影响，复杂度 $\Theta(B)$。

最终复杂度 $\Theta(B+\frac{n}{B})$，当 $B=\sqrt{n}$ 时，取到最优复杂度 $\Theta(n)$。

---

## 作者：do_while_true (赞：4)

[$\text{更佳的阅读体验}$](https://www.cnblogs.com/do-while-true/p/13874396.html)

# $\mathcal{Solution}$

其实根号分治就可以，这个人傻乎乎地写的树状数组。

$sum_{i,j,k}$ 为模 $i$ 为 $j$ 的答案前缀和的树状数组。

可以有两种方法来处理询问和修改：

1. 树状数组。

2. 暴力一个一个跳。

因为有的 $x$ 很大的时候暴力跳的次数很少，复杂度是对的，所以要设置一个分界线，在分界线下的用树状数组，在分界线上的暴力。

设这个分界线为 $M$，对于树状数组修改一次的复杂度为 $\mathcal{O}(M\log n )$，暴力依次跳的复杂度为 $\mathcal{O}(\frac{n}{M})$，总复杂度就是 $\mathcal{O}(nM\log n +\frac{n^2}{M})$ 这样子。其实是可以卡满的，但是在不超过空间限制的前提下调一下 $M$ 即可，跑CF的 main test 还是很快的。

# $\mathcal{Code}$

其实二维数组记录就可以，没有必要树状数组，仅提供一个思路，代码参考。

```cpp
#include<iostream>
#include<cstdio>
#define re register
#define ll long long
inline int read() {
	re int r = 0; re bool w = 0; re char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : w, ch = getchar();
	while(ch >= '0' && ch <= '9') r = (r << 3) + (r << 1) + (ch ^ 48), ch = getchar();
	return w ? ~r + 1 : r;
}
inline int lowbit(int x) { return x & (-x); }
inline int Max(int x, int y) { return x > y ? x : y; }
inline int Min(int x, int y) { return x < y ? x : y; }
const int M = 10;
const int N = 500010;
ll sum[M + 1][M + 1][N];
int n, optt[N], xx[N], yy[N], a[N]; 
//sum[i][j][k] 模i为j的前k个的前缀和的tree 
void modify(int i, int j, int k, int val) {
	while(k <= n) {
		sum[i][j][k] += val;
		k += lowbit(k);
	}
}
ll query(int i, int j, int k) {
	re ll sumq = 0;
	while(k) {
		sumq += sum[i][j][k];
		k -= lowbit(k);
	}
	return sumq;
}
int main() {
	int q = read();
	for(int i = 1; i <= q; ++i) optt[i] = read(), xx[i] = read(), yy[i] = read(), n = Max(n, xx[i]);
	re int opt, x, y;
	for(int Q = 1; Q <= q; ++Q) {
		opt = optt[Q], x = xx[Q], y = yy[Q];
		if(opt == 1) {
			a[x] += y;
			for(int i = 1; i <= M; ++i) {
				modify(i, x % i, x / i + (x % i > 0), y);
			}
		}
		else {
			re ll sumq = 0;
			if(x >= M + 1) {
				for(int i = y; i <= n; i += x) sumq += a[i];
			}
			else {
				sumq = query(x, y, n);
			}
			printf("%lld\n", sumq);
		}
	}
	return 0;
}
```

---

## 作者：Constant (赞：4)


# 题意简述：
维护一个大小为 $500000$ 的数组，初始时数组元素全为 $0$ ，有两种操作。

1.将 $a[x]$ 增加 $y$ 。

2.求数组下标模 $x$ 等于 $y$ 的所有元素之和。



------------
# Solution：

看到这 $N=500000$ 的数据规模， $O(N^2)$ 的暴力复杂度是绝对不行的，考虑优化算法。

我们发现，比较难解决的其实就是操作2，询问对应的下标和。而   $x$ ， $y$ 其实都是在 $500000$ 之内的，这就给了我们一个启示，可以从模数下手，考虑分块。

具体地，维护一个数组 $sum$ ， $sum[i][j]$ 表示模数为 $i$ 余数为 $j$ 的元素之和。

预处理了这个数组，事情就好办多了。

设一个控制模数的范围 $T$ ，当模数小于 $T$ 时，直接从 $1$ 枚举模数，将 $sum$ 数组的值加起来，显然，这一步的时间复杂度是   $O(T)$ 的。

而模数大于 $T$ 时直接暴力求和，从 $y$ 开始每次加上模数 $x$ ，将对应的数组值加起来，时间复杂度为 $O(\frac{N}{T})$ 
。

当 $T=\sqrt{N}$ 时二者复杂度相同，这时也是最优复杂度，则可以据此，按模数进行分块。

然后对于单点修改的操作，对分出的块维护 $sum$ 数组即可，模数为 $i$ 的元素和增加，单点修改的时间复杂度显然是          $O(\sqrt{N})$ 的。

好了，这道直奔主题的分块题目就结束了，下面上代码。

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
int q; 
int pd,x,y,sq=707,N=5e5;
ll sum[709][709],a[500010],s;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
    return x*f;
}
int main()
{
    q=read();
    while(q--)
    {    
        pd=read();x=read();y=read();
        if(pd==1)
        {
            for(register int i=1;i<=sq;i++) sum[i][x%i]+=y;//单点修改，维护sum数组，所有模数更新a 
            a[x]+=y;
        }
        else
        {
            if(x<sq)
            {
                printf("%lld\n",sum[x][y]); //相当于是一个不完整的块，O（1）回答询问 
            }
            else
            {
                s=0;
                for(register int i=y;i<=N;i=i+x) //暴力统计答案 
                {
                    s+=a[i];	
                }
                printf("%lld\n",s);
            }
        }
    }
    return 0;
}
```












---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定一个长度为 $n$ 的序列，初值全都为 $0$，要完成 $q$ 次操作：

- 单点加
- 询问所有下标模 $x$ 的结果为 $y$ 的位置的值之和

#### 思路分析


------------
朴素的 $\Theta(n^2)$ 暴力显然无法通过此题。

考虑对于每次查询给定的 $x$ 根号分治：

- 若 $x > \sqrt{n}$，那么最多统计 $\sqrt{n}$ 次答案，直接枚举即可，复杂度 $\Theta(\sqrt{n})$。
- 若 $x \le \sqrt{n}$，使用数组 $ans[x][y]$ 记录答案，表示下标模 $x$ 的结果为 $y$ 的位置的和，对于每个 $1$ 操作 $\Theta(\sqrt{n})$ 更新即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#define int long long
using namespace std;
typedef long long LL;
const int Mx = 500010;
const int N = 1010;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
LL ans[N][N];
int a[Mx];
signed main(){
	int q = read();
	int n = sqrt(Mx);
	for(int i=1;i<=q;i++){
		int opt = read() , x = read() , y = read();
		if(opt == 1){
			for(int i=1;i<=n;i++){
				ans[x % i][i] += y; 
			}
			a[x] += y;
		}
		else {
			if(x <= n) printf("%lld\n",ans[y][x]);
			else {
				int ans = 0;
				for(int i=y;i<=Mx;i+=x){
					ans += a[i];
				}
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
```


---

## 作者：Lolierl (赞：2)

根号分治。

$x <= sqrt(500000)$的，把每个模数的答案记录下来，直接查询。空间复杂度$O(sqrt(n) * sqrt(n)) = O(n)$，时间复杂度修改$O(sqrt(n))$，查询$O(1)$

$x > sqrt(500000)$的，直接暴力计算。时间复杂度修改$O(1)$，查询$O(sqrt(n))$

总复杂度：修改$O(sqrt(n))$，查询$O(sqrt(n))$
时限开了四秒，应该可以稳过。
代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#define pii pair<int, int>
using namespace std; 
 
const int T = 707; 
int p[1001][1001], a[1000001], cnt, x, y, ans, maxn; 
int main()
{
	int q; 
	scanf("%d", &q); 
	
	for(int i = 1; i <= q; i++)
	{
		scanf("%d%d%d", &cnt, &x, &y); 
		if(cnt == 1)
		{
			a[x] += y; maxn = max(maxn, x); 
			for(int j = 1; j <= T; j++)
				p[j][x % j] += y; 
		}
		else
		{
			if(x <= T)
				printf("%d\n", p[x][y]); 
			else
			{
				ans = 0; 
				for(int j = y; j <= maxn; j += x)
					ans += a[j]; 
				printf("%d\n", ans); 
			}
		}
	}
	return 0; 
}

```

---

## 作者：Tenshi (赞：1)

## 题目大意
给出一个初始值全部为 $0$ 的，从 $1$ 开始编号，长度为 $500000$ 的序列，要求对 $q$ 次询问做出对应的两个操作：

1. 将下标为 $x$ 的位置的值加上 $y$ 
2. 询问所有下标模 $x$ 的结果为 $y$ 的位置的值之和

## 分析
拿到题目，发现没有什么现成的数据结构可以维护这两个操作，根据经验，我们可以考虑优雅的暴力——分块。

不妨将操作 $2$ 形象地解释为将序列中**初相位**为 $y$ ，**周期**为 $x$ 的**下标**对应的数求和。

那么思路是：
+ 当块长较大时，我们暴力地统计答案，也就是直接枚举进行统计。

+ 而当块长较小时，将答案存在 `ans[T][phi]` 中，并进行维护。

> 这里的 $T$ 意思是周期，而 $phi$ （也就是 $\phi$）指的是初相位。

细节见代码（很短的 $awa$）

```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)

#define int long long

inline void read(int &x) {
    int s=0;x=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=5e5+5, L=707;

int w[N], q;
int ans[L+5][L+5]; // 第一维代表周期，第二维代表初相位，值代表对应的和

signed main(){
	read(q);
	
	while(q--){
		int op, x, y; read(op), read(x), read(y);
		
		if(op&1){
			w[x]+=y;
			rep(i,1,L) ans[i][x%i]+=y;
		}
		else{
			if(x<=L) cout<<ans[x][y]<<endl;
			else{
				int t=0;
				for(int i=y; i<=N; i+=x) t+=w[i];
				cout<<t<<endl;
			}
		}
	}
    return 0;
}
```

---

## 作者：fsy_juruo (赞：1)

[CF1207F - Remainder Problem](https://codeforces.com/contest/1207/problem/F)

可以考虑设置一个整数 $S$ 和一个二维数组 $sum$，在执行一操作时，对于所有的 $k \leq S$，将 $sum[x][k \mod x]$ 也做修改。如果在执行二操作时，$x \geq S$，就暴力扫每一个符合要求的数统计答案。反之直接返回 $sum[x][y]$。

如果这样做，一次操作的最坏时间复杂度为 $\max(S, \frac{n}{S})$，取 $S = \sqrt{n}$，时间复杂度 $q \sqrt{n}$，其中 $n = 500000$。时限 4 秒，可以通过本题。

```cpp
#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; i++)
#define _per(i, x, y) for(int i = x; i >= y; i--)
#define LL long long
using namespace std;
template <typename T>
inline void read(T &x) {
    x = 0;
    LL f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - 48;
    x *= f;
}
template <typename T>
inline void write(T x) {
	if(x < 0) {putchar('-'); x = -x;}
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T>
inline void writesp(T x, char sp = '\n') {
	write(x); putchar(sp);
}
const int maxn = 5e5 + 10, sq = 7e2 + 10;
int q = 0, opt = 0, x = 0, y = 0, sum[sq][sq], a[maxn];
int main() {
	read(q);
	_rep(i, 1, q) {
		read(opt); read(x); read(y);
		if(opt == 1) {
			a[x] += y;
			_rep(j, 1, sq - 5) {
				sum[j][x % j] += y;
			}
		} else {
			if(x <= sq - 5) {
				writesp(sum[x][y]);
			} else {
				int ans = 0;
				for(int j = y; j <= maxn - 5; j += x) {
					ans += a[j];
				}
				writesp(ans);
			}
		}
	}
	return 0;
}
```



---

## 作者：世末OIer (赞：1)

这题真的非常水啊，但我还是花了十分钟/kel

---

具体思路就是根号分治

时间复杂度:$O(n^{3/2})$

```cpp

#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
ll sum[755][755],a[500005];
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	int q;cin>>q;
	for(;q--;){
		int tp,x,y;cin>>tp>>x>>y;
		if(tp==1){
			for(int i=1;i<700;++i)sum[i][x%i]+=y;  //小的答案，因为是问你所有的数，所以可以预处理
			a[x]+=y;   //赋值
		}else{
			if(x<700){
				cout<<sum[x][y]<<endl;  已经处理过了
			}else{
				ll rt=0;   //直接求和
				for(int i=y;i<=500000;i+=x)rt+=a[i];
				cout<<rt<<endl;
			}
		}
	}
}

```

---

## 作者：happybob (赞：0)

## 题意

给定一个初始值全部为 $0$，长度为 $5 \times 10^5$ 的数列，要支持单点加上某个数，以及查询 $y, y + x, y + 2 \cdot x, \cdots, y + k \cdot x$ 的数列的对应的值的和，直到 $y + k \cdot x > n$ 时停止。

## 解法

限时 $4$ 秒，考虑分块或线段树。但是分析后可得，线段树难以维护零散的点的和，而普通分块空间会爆。

那么我们还有一个方法：根号分治。这是一种类似分块的方法，他可以使得平均复杂度在 $O(n \sqrt{n})$ 以内，$n$ 是数列长度。

考虑设 $ans_{i,j}$ 表示询问输入的是 $i, j$ 时的答案，那么理论空间复杂度是 $O(n^2)$ 的，显然不行。我们注意到询问有一个特征，就是当 $y, x$ 都很小的时候暴力会很慢，而当 $y, x$ 很大时暴力可以接受。暴力的每次复杂度大约是 $O(\frac{n}{x})$ 级别的，所以我们只需要记录 $ans_{i,j}$，其中 $i, j \leq \sqrt{n}$，那么询问的时候，如果块内有答案，直接 $O(1)$ 输出，不然暴力的理论最坏复杂度还是 $O(\sqrt{n})$ 的，单点修改就没什么难度了，只需要从 $1$ 到 $\sqrt{n}$ 循环即可，也是 $O(\sqrt{n})$ 的。

所以总复杂度最坏是 $O(n \sqrt{n})$ 的，最坏的点约 $3$ 秒，稍微卡一下常数，可以通过。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int l = 708, N = 5e5 + 5;

int n;
long long ans[l + 5][l + 5], a[N];

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		int opt, x, y;
		scanf("%lld%lld%lld", &opt, &x, &y);
		if (opt == 1ll)
		{
			a[x] += y;
			for (int i = 1; i <= l; i++)
			{
				ans[i][x % i] += y;
			}
		}
		else
		{
			if (x <= l) printf("%lld\n", ans[x][y]);
			else
			{
				long long res = 0;
				for (int i = y; i <= N - 5; i += x) res += a[i];
				printf("%lld\n", res);
			}
		}
	}
	return 0;
}
```




---

## 作者：花园Serena (赞：0)

最近在打莫队和分块的题，然后看到了这个。

首先我们有一种很蠢的方法，遍历每一个数字，如果他 mod x 等于 y ，我们就加上他，不过显然这个是不行的（废话）

如果我们设 $ans_{i, j}$ 表示**模数为 i ，余数为 j** ， 那么我们可以写出一个修改操作，遍历每一个模数，然后修改的时候直接对 ans 数组进行修改，但是这样做的时空复杂度都是是 $n^2$ 的，但是我们离正解已经很近了。

我们考虑用根号分治的思想，对于小于 $\sqrt{n}$的模数我们用 ans 数组统计，而大于等于 $\sqrt{n}$ 的我们直接暴力算答案。

那这样做的复杂度呢？

首先对于修改操作，显然是 $O(\sqrt{n})$ 的，因为我们需要修改的模数只有这么多个。对于查询操作，如果模数小于 $\sqrt{n}$ ，查询是 $O(1)$ 的，如果不是，我们则暴力跳，因为模数大于等于 $\sqrt{n}$ ，所以我们暴力跳的次数是小于等于  $\sqrt{n}$ 的，所以时间复杂度也是 $O(\sqrt{n})$ 的。总复杂度为 $O(q\sqrt{n})$，空间复杂度则是 $O(n)$ 的，因为我们只会开一个二维的 ans 数组，且每一维都是 $\sqrt{n}$ 的，所以对于 n = 5e5 是完全能跑过的。

附上代码，如有问题或是错误，欢迎评论或私信指出

```cpp
#include <bits/stdc++.h>
using namespace std;
#define R register int
const int N = 500000 + 10;
int n, m, a[N], ans[1000][1000];
int inline read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') {if(ch == '-') f = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
    return x * f;
}
int main()  {
    n = 500000; m = read();
    int size = (int) sqrt(n);
    memset(a, 0, sizeof(a));
    for(R i = 1; i <= m; i ++) {
        int tag = read(), x = read(), y = read();
        if(tag == 2) {
            if(x <= size) printf("%d\n", ans[x][y % x]);
            else {
                int Ans = 0;
                for(R j = y; j <= n; j += x)
                    Ans += a[j];
                printf("%d\n", Ans);
            }
        }
        else {
            for(R p = 1; p <= size; p ++)
                ans[p][x % p] += y;
            a[x] += y;
        }
    }
    return 0;
}
```

---

