# [ICPC 2021 WF] Mosaic Browsing

## 题目描述

#### 简要题意
给出两个矩阵, 其中第二个矩阵所有元素非 $0$.

定义第一个矩阵在第二个矩阵中的坐标 $(l, r)$ 处「出现」, 当且仅当存在一种方式任意修改第一个矩阵所有为 $0$ 的元素后, 第一个矩阵的左上角在第二个矩阵的对应位置坐标为 $(l, r)$ 时可以与第二个矩阵的一部分完全重合.

求第一个矩阵在第二个矩阵中所有「出现」的位置和总「出现」次数。

## 样例 #1

### 输入

```
2 2
1 0
0 1
3 4
1 2 1 2
2 1 1 1
2 2 1 3
```

### 输出

```
3
1 1
1 3
2 2
```

# 题解

## 作者：iyaang (赞：1)

[劲爆的阅读体验](https://www.cnblogs.com/LittleTwoawa/p/17601192.html)

[题目链接](https://www.luogu.com.cn/problem/P9445)

数据有点水啊，貌似矩阵大小最大只有 $500$，这导致一堆 bitset 乱搞或者暴力啥的无聊解法能过，这里就不多说了，快进到正题。

二维通配符匹配。

首先根据 Rabin Karp 给每种颜色随机一个权值做哈希，特别的，令通配符（也就是 $0$）的权值为 $0$。下文称模式串为 $A$，匹配串为 $B$。接下来要做的就是设计匹配函数和卷积。

将两个矩阵拍到一维上，套路性的翻转 $A$ 矩阵后相乘。这里有一个小技巧，为了使 $A$ 和 $B$ 能够对应上位置，我们在 $A$ 的前 $r_p - 1$ 行末尾补 $0$，补到长度为 $c_q$。具体的，可以有例子：

$$
\begin{aligned}
& c_q = 4,A = \begin{bmatrix} 1 & 2 & 3 \\ 4 & 5 & 6 \\ \end{bmatrix} \\
& \sf A = \begin{bmatrix} 1 & 2 & 3 & 0 & 4 & 5 & 6 \end{bmatrix} \\
& \sf A' = \begin{bmatrix} 6 & 5 & 4 & 0 & 3 & 2 & 1 \end{bmatrix} \\
& A' = \begin{bmatrix} 6 & 5 & 4 \\ 3 & 2 & 1 \\ \end{bmatrix} \\
\end{aligned}
$$

注意到这样就实现了 $A_{i,j}' = A_{r_p - i + 1,c_p - j + 1}$。此时我们要求匹配函数：
$$
\begin{aligned}
P_{x,y} &= \sum_{1 \leq i < r_p} \sum_{1 \leq j < c_p} A_{i,j} B_{x + i - 1,y + i - 1} \\
&= \sum_{1 \leq i < r_p} \sum_{1 \leq j < c_p} A_{r_p - i + 1,c_p - i + 1}' B_{x + i - 1,y + i - 1}
\end{aligned}
$$

注意到下标里的东西加起来正好是 $(x + r_p,y + c_p)$，然后就可以愉快的卷积求 $P$ 了。

令 $K = \sum_{i = 1}^{r_p} \sum_{j = 1}^{c_p} A_{i,j}^2$，注意到匹配串中不存在通配符，模式串中的通配符 $0$ 不管遇到什么颜色乘出来这一位都是 $0$，能与 $K$ 中所算的一项对应起来。所以如果存在 $P_{x,y} = K$，则说明在 $B_{x,y}$ 这个位置匹配上了。注意最后统计答案的时候再判一下位置是否合法就好了，这是简单的。综上我们做到了 $\mathcal O(T \log T)$，其中 $T = (r_p + r_q)(c_p + c_q)$。个人采用了 NTT 实现，再不要脸的推一波我的[多项式板子](https://lgxtpre.github.io/package/Poly/)，跑的非常优秀。

```cpp
#include<bits/stdc++.h>
#define ld long double
#define ui unsigned int
#define ull unsigned long long
#define int long long
#define eb emplace_back
#define pb pop_back
#define ins insert
#define mp make_pair
#define pii pair<int,int>
#define fi first
#define se second
#define power(x) ((x)*(x))
#define gcd(x,y) (__gcd((x),(y)))
#define lcm(x,y) ((x)*(y)/gcd((x),(y)))
#define lg(x,y)  (__lg((x),(y)))
#define y1 LJBL
using namespace std;
 
namespace FastIO
{
    template<typename T=int> inline T read()
    {
        T s=0,w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        return s*w;
    }
    template<typename T> inline void read(T &s)
    {
        s=0; int w=1; char c=getchar();
        while(!isdigit(c)) {if(c=='-') w=-1; c=getchar();}
        while(isdigit(c)) s=(s*10)+(c^48),c=getchar();
        s=s*w;
    }
    template<typename T,typename... Args> inline void read(T &x,Args &...args)
    {
        read(x),read(args...);
    }
    template<typename T> inline void write(T x,char ch)
    {
        if(x<0) x=-x,putchar('-');
        static char stk[25]; int top=0;
        do {stk[top++]=x%10+'0',x/=10;} while(x);
        while(top) putchar(stk[--top]);
        if(ch!='~') putchar(ch);
        return;
    }
}
using namespace FastIO;
 
inline void file()
{
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
    return;
}
 
bool Mbe;
 
namespace LgxTpre
{
    static const int MAX=4000010;
    static const int inf=2147483647;
    static const int INF=4557430888798830399;
    static const int mod=1e9+7;
    static const int bas=131;
    
    namespace Poly
    {
		namespace MInt
		{
		    static const int Mod=998244353;
		    template<const int Mod> struct ModInt
		    {
		        int x;
		        ModInt(int X=0):x(X) {}
		        inline ModInt operator = (int &T) {*this.x=T; return *this;}
		        inline ModInt operator = (const ModInt &T) {this->x=T.x; return *this;}
		        inline friend ModInt operator + (ModInt a,ModInt b) {return a.x+b.x>=Mod?a.x+b.x-Mod:a.x+b.x;}
		        inline friend ModInt operator - (ModInt a,ModInt b) {return a.x-b.x<0?a.x-b.x+Mod:a.x-b.x;}
		        inline friend ModInt operator * (ModInt a,ModInt b) {return a.x*b.x%Mod;}
		        inline friend ModInt operator ^ (ModInt a,int b) {ModInt res=1; while(b) {if(b&1) res=res*a; a=a*a; b>>=1;} return res;}
		        inline friend ModInt operator / (ModInt a,ModInt b) {return a*(b^(Mod-2));}
		        inline ModInt operator += (const ModInt &T) {*this=*this+T; return *this;}
		        inline ModInt operator -= (const ModInt &T) {*this=*this-T; return *this;}
		        inline ModInt operator *= (const ModInt &T) {*this=*this*T; return *this;}
		        inline ModInt operator ^= (const ModInt &T) {*this=*this^T; return *this;}
		        inline ModInt operator /= (const ModInt &T) {*this=*this/T; return *this;}
		        template<typename T> inline friend ModInt operator + (ModInt a,T x) {return a+ModInt(x);}
		        template<typename T> inline friend ModInt operator - (ModInt a,T x) {return a-ModInt(x);}
		        template<typename T> inline friend ModInt operator * (ModInt a,T x) {return a*ModInt(x);}
		        template<typename T> inline friend ModInt operator / (ModInt a,T x) {return a/ModInt(x);}
		        inline friend bool operator == (ModInt a,ModInt b) {return a.x==b.x;}
		        inline friend bool operator != (ModInt a,ModInt b) {return a.x!=b.x;}
		        inline friend bool operator >  (ModInt a,ModInt b) {return a.x>b.x;}
		        inline friend bool operator <  (ModInt a,ModInt b) {return a.x<b.x;}
		        inline friend bool operator >= (ModInt a,ModInt b) {return a>b||a==b;}
		        inline friend bool operator <= (ModInt a,ModInt b) {return a<b||a==b;}
		        template<typename T> inline friend bool operator == (ModInt a,T b) {return a==ModInt(b);}
		        template<typename T> inline friend bool operator != (ModInt a,T b) {return a!=ModInt(b);}
		        template<typename T> inline friend bool operator >  (ModInt a,T b) {return a>ModInt(b);}
		        template<typename T> inline friend bool operator <  (ModInt a,T b) {return a<ModInt(b);}
		        template<typename T> inline friend bool operator >= (ModInt a,T b) {return a>=ModInt(b);}
		        template<typename T> inline friend bool operator <= (ModInt a,T b) {return a<=ModInt(b);}
		        inline bool operator ! () {return !x;}
		        inline ModInt operator - () {return x?Mod-x:0;}
		    };
		}
		using namespace MInt;
		static const ModInt<Mod> gn=332748118,gni=3,ZERO=0,ONE=1;
		struct poly
	    {
	        vector<ModInt<Mod>> a;
	        inline ModInt<Mod> &operator [] (int i) {return a[i];}
	        inline poly operator = (const poly &T) {this->a=T.a; return *this;}
	        inline int size()         {return a.size();}
	        inline ModInt<Mod> back() {return a.back();}
	        inline void resize(int N) {return a.resize(N),void();}
	        inline void reverse()     {return std::reverse(a.begin(),a.end());}
	        inline void pin(int x)    {return a.emplace_back(ModInt<Mod>(x)),void();}
	        inline void pout()        {for(auto it:a) write(it.x,' ');}
	    };
	    static const int GT=21,GR=31;
	    ModInt<Mod> omega[MAX]; poly zero,one;
	    inline int Sup(int N) {int K=1; while(K<N) K<<=1; return K;}
	    inline void Prework(int N)
	    {
	        zero.a.emplace_back(ZERO),one.a.emplace_back(ONE);
	        int K=1; while((1<<K)<N) ++K; K=min(K-1,21ll);
	        omega[0]=1,omega[1<<K]=(ModInt<Mod>(GR))^(1<<(GT-K));
	        for(int i=K;i>=1;--i) omega[1<<(i-1)]=omega[1<<i]*omega[1<<i];
	        for(int i=1;i<(1<<K);++i) omega[i]=omega[i&(i-1)]*omega[i&(-i)];
	    }
	    inline void NTT(poly &F,int typ)
	    {
	        ModInt<Mod> U,V;
	        int N=F.size();
	        if(typ==1)
	        {
	            for(int mid=N>>1;mid>=1;mid>>=1)
	                for(int i=0,k=0;i<N;i+=mid<<1,++k)
	                    for(int j=0;j<mid;++j)
	                        U=F[i+j],V=F[i+j+mid]*omega[k],
	                        F[i+j]=U+V,F[i+j+mid]=U-V;
	        }
	        if(typ==-1)
	        {
	            for(int mid=1;mid<N;mid<<=1)
	                for(int i=0,k=0;i<N;i+=mid<<1,++k)
	                    for(int j=0;j<mid;++j)
	                        U=F[i+j],V=F[i+j+mid],
	                        F[i+j]=U+V,F[i+j+mid]=(U-V)*omega[k];
	            ModInt<Mod> Ninv=ONE/N;
	            for(int i=0;i<N;++i) F[i]*=Ninv;
	            reverse(F.a.begin()+1,F.a.end());
	        }
	    }
	    inline poly operator * (poly a,poly b)
	    {
	        int K=a.size()+b.size()-1,N=Sup(K);
	        a.resize(N),b.resize(N);
	        NTT(a,1),NTT(b,1);
	        for(int i=0;i<N;++i) a[i]*=b[i];
	        NTT(a,-1);
	        a.resize(K);
	        return a;
	    }
	}
	using namespace Poly;
	
	int rp,cp,rq,cq;
	int tag[MAX],cnt=1;

    inline void lmy_forever()
    {
    	Poly::Prework(4000000);
    	
    	read(rp,cp); vector a(rp,vector<int>(cp));
    	for(int i=0;i<rp;++i) for(int j=0;j<cp;++j) read(a[i][j]);
    	read(rq,cq); vector b(rq,vector<int>(cq));
    	for(int i=0;i<rq;++i) for(int j=0;j<cq;++j) read(b[i][j]);
    	
    	auto random=[&](int l,int r)->int
    	{
        	static mt19937_64 sd(20070707);
        	static uniform_int_distribution<int> range(l,r);
			return range(sd);
		};
    	
    	for(int i=1;i<=rq*cq;++i) tag[i]=1;
		vector<int> col(110);
    	for(int i=1;i<=100;++i) col[i]=random(1,Mod-1);
    	poly A,B,C; ModInt<Mod> tmp;
    	for(int i=0;i<rp;++i) {int j=0; for(;j<cp;++j) A.pin(col[a[i][j]]),tmp+=A.back()*A.back(); if(i<rp-1) for(;j<cq;++j) A.pin(0);}
		for(int i=0;i<rq;++i) for(int j=0;j<cq;++j) B.pin(col[b[i][j]]);
    	A.reverse(),C=A*B;
    	for(int i=0;i<B.size()-A.size()+1;++i) if(C[A.size()+i-1]!=tmp) tag[i+1]=0;
		vector<pii> ans;
		for(int i=1;i<=rq;++i) for(int j=1;j<=cq;++j,++cnt) if(i+rp-1<=rq&&j+cp-1<=cq&&tag[cnt]) ans.eb(mp(i,j));
		write(ans.size(),'\n');
		for(auto [x,y]:ans) write(x,' '),write(y,'\n');
    	return;
    }
}

bool Med;

signed main()
{
//  file();
    fprintf(stderr,"%.3lf MB\n",abs(&Med-&Mbe)/1048576.0);
    int Tbe=clock();
    LgxTpre::lmy_forever();
    int Ted=clock();
    cerr<<1e3*(Ted-Tbe)/CLOCKS_PER_SEC<<" ms\n";
    return (0-0);
}
```

---

