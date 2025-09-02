# [AGC050D] Shopping

## 题目描述

有$N$个人编号从$1$到$N$, $K$个商品编号从$1$到$K$。从现在开始进行回合制的游戏。从号码为$1$的人开始，到号码为$2$的人，再到号码为$3$的人，号码为$N$的人，号码为$1$的人，$ \ldots $号码为$N$的人，号码为$1$的人，$\ldots$,他们将不断重复这一过程，直到所有商品被获得为止。

每个回合对应的人会进行以下的操作

自己已经获得商品的情况下，什么都不进行。

如果不是，这个人就从自己还没有选择的商品中，以等概率随机选择一个，秘密地告诉身为裁判的空井君。如果那个商品已经被别人获得了，就什么都不会发生。如果不是，那个商品就由那个人获得。

对于每个$i$，请用$\bmod \ 998244353$来计算编号为$i$的人获得任一商品的概率(参见样例解释)。

## 说明/提示

$1<=N,K<=40$

## 样例 #1

### 输入

```
3 2```

### 输出

```
1
249561089
748683265```

## 样例 #2

### 输入

```
4 3```

### 输出

```
1
314262112
767169272
915057324```

## 样例 #3

### 输入

```
40 10```

### 输出

```
1
868517173
27621563
837064957
222682471
512462123
662169358
927654899
421237429
47896491
462367772
888812171
300869511
63754652
144548024
358216674
895724239
274552277
722622637
946769993
579325471
777654313
142897955
607284898
8038340
863909530
63295741
862961672
335905745
944425523
358698956
299986928
847582651
197657467
180361665
412489246
762713624
410322243
646538576
79047758```

# 题解

## 作者：grass8cow (赞：6)

一年前觉得不太可做的题。

我们要算什么？每个人能拿物品的概率，所以 dp 的状态值肯定是某种概率。

事实上，如果一个人领到了物品，我们直接当成把他删掉，显然不影响答案。

考虑没有领到的物品的人，令当前是第 $x$ 轮，显然他试过 $x-1$ 个物品，那么就是在 $k-(x-1)$ 个物品里随机选。

我们令现在剩下 $m$ 个人，那么就只有 $k-m$ 个物品是未选的，当前这个人能领到物品的概率就是 $(k-m)/(k-x+1)$ 。

我们就针对一个人能选到的概率设计 $dp$ ：


$dp_{x,y,z,w}$ 表示"小明"左边有 $x$ 个人，右边有 $y$ 个人，然后游戏进行到了 $x+y+1$ 个人中的第 $z$ 个人，当前是第 $w$ 轮，"小明"能拿到物品的概率。

转移简单，复杂度 $O(n^4)$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,inv[60];
const int mod=998244353;
int dp[50][50][50][50];
int dfs(int x,int y,int z,int w){
	if(dp[x][y][z][w]!=-1)return dp[x][y][z][w];
	if(w>m||n-(x+y+1)>=m)return 0;
	int I=inv[m-w+1],p=1ll*(m-n+x+y+1)*I%mod;
	int as;
	if(z==x+1)
		as=(p+1ll*(1-p)*(y?dfs(x,y,z+1,w):dfs(x,y,1,w+1))%mod)%mod;
	else if(z<=x)as=(1ll*p*dfs(x-1,y,z,w)%mod+1ll*(1-p)*dfs(x,y,z+1,w)%mod)%mod;
	else{
		if(z==x+y+1)as=(1ll*p*dfs(x,y-1,1,w+1)%mod+1ll*(1-p)*dfs(x,y,1,w+1)%mod)%mod;
		else as=(1ll*p*dfs(x,y-1,z,w)%mod+1ll*(1-p)*dfs(x,y,z+1,w)%mod)%mod;
	}
	return dp[x][y][z][w]=(as+mod)%mod;
}
int main(){
	inv[1]=1;
	for(int i=2;i<=55;i++)inv[i]=mod-1ll*(mod/i)*inv[mod%i]%mod;
	cin>>n>>m;
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=n;i++)
		printf("%d\n",dfs(i-1,n-i,1,1));
	return 0;
}
```


---

## 作者：Legitimity (赞：4)

### solution

考虑经过 $i$ 轮且已有 $j$ 个人获胜，那么剩下所有人手中的牌数和没被别人选过的牌数都是固定的，分别是 $k-i$ 和 $k-j$。实际上一个局面可以由当前是第几轮、还有几个没获胜的人、当前轮到没获胜的人中的第几个人操作三个参数确定，再加上我们想知道对于每一个 $x$，第 $x$ 个人的获胜概率，加上这个 $x$，一共四个参数即可确定状态。

设 $f_{i,p,a,b}$ 表示当前已经完成了 $i$ 轮（第 $i+1$ 轮正在进行），轮到了剩下的人中的第 $p$ 个人，我们期望知道获胜概率的人前面剩 $a$ 个人，后面剩 $b$ 个人（一共剩 $len=a+b+1$ 个人）的情况下，后面（包括当前）进行若干次操作后这个期望的人的获胜概率。

分情况讨论转移即可（设当前人获胜概率为 $A=\dfrac{k-(n-len)}{k-i}$，失败概率为 $B=1-A$）：

* 当前的人就是期望的人。$A$ 的概率直接获胜，否则 $B\times f_{i+\lfloor\frac{p}{len}\rfloor,p\bmod len+1,a,b}$ 的概率在后面获胜。
* 当前的人在期望的人前面。$A$ 的概率当前人胜，然后期望的人 $A\times f_{i+\lfloor\frac{p}{len}\rfloor,(p-1)\bmod (len-1)+1,a-1,b}$ 概率在后面获胜；$B$ 概率当前的人败，然后期望的人 $B\times f_{i+\lfloor\frac{p}{len}\rfloor,p\bmod len+1,a,b}$ 的概率在后面获胜。
* 当前的人在期望的人后面。$A$ 的概率当前人胜，然后期望的人 $A\times f_{i+\lfloor\frac{p}{len}\rfloor,(p-1)\bmod (len-1)+1,a,b-1}$ 概率在后面获胜；$B$ 概率当前的人败，然后期望的人 $B\times f_{i+\lfloor\frac{p}{len}\rfloor,p\bmod len+1,a,b}$ 的概率在后面获胜。

时间复杂度为 $O(n^4)$。（假设 $n,k$ 同阶）

### code
```cpp
int n,k,inv[45];
int F[41][41][41][41];
int f(int i,int p,int a,int b){
	if(~F[i][p][a][b]) return F[i][p][a][b];
	if(i==k) return F[i][p][a][b]=0;
	if(n-a-b-1==k) return F[i][p][a][b]=0;
	const int len=a+b+1,A=1ll*(k-(n-len))*inv[k-i]%djq,B=(1-A+djq)%djq;
	if(p==a+1) return F[i][p][a][b]=add(1ll*f(i+p/len,p%len+1,a,b)*B%djq,A);
	if(p>a+1) return F[i][p][a][b]=add(1ll*f(i+p/len,p%len+1,a,b)*B%djq,1ll*f(i+p/len,(p-1)%(len-1)+1,a,b-1)*A%djq);
	if(p<a+1) return F[i][p][a][b]=add(1ll*f(i,p+1,a,b)*B%djq,1ll*f(i,p,a-1,b)*A%djq);
	assert(0);
	return 0;
}
signed main(){
	//file(); 
	n=read(),k=read(); memset(F,-1,sizeof(F));
	rep(i,n) inv[i]=ksm(i,djq-2);
	rep(i,n) printf("%d\n",f(0,1,i-1,n-i));
	return 0;
}
```

---

## 作者：2008verser (赞：1)

先描述这个游戏，每个人手上有两种牌，有效的和无效的。拿到有效牌 $x$ 可以退出游戏，并且将其他玩家手上数字为 $x$ 的牌标记为无效。

初始每人手上都是 $k$ 张有效，$0$ 张无效。

简单观察得到，每轮游戏结束后，每个人手上有效无效牌数量都还是一样的。

即一轮游戏是划分子问题的过程。一个问题的答案和人数、两种牌数有关。关心答案的是某个人 win 的概率。

因此设 $f_{n,m_0,m_1,i}$ 游戏剩下 $n$ 个人，两种牌数为 $m_0,m_1$，第 $i$ 个人的获胜概率。

枚举这轮中 $i$ 前后退出的人数 $j_0,j_1$ 转移。

系数不是很困难，应该不需要多做解释，只是需要耐心一点。

$$
\begin{align*}
f_{n,m_0,m_1,i}=&\frac{m_1}{m_0+m_1}\left(\frac{m_0+m_1-1}{m_0+m_1}\right)^{i-1}\\
+&\sum_{j_0=0}^{\min(i-1,m_1)}\sum_{j_1=0}^{\min(n-i,m_1-j_0)}f_{n-j_0-j_1,m_0+j_0+j_1-1,m_1-j_0-j_1,i-j_0}\times\frac{m_0+j_0}{m_0+m_1}\times g_{i-1,m_0,m_1,j_0}\times g_{n-i,m_0+j_0,m_1-j_0,j_1}
\end{align*}
$$

需要用到 $g_{n,m_0,m_1,i}$ 表示 $n$ 个人，两种牌数 $m_0,m_1$ 的情况下，共退出了 $i$ 个人的概率。

$$
g_{n,m_0,m_1,i}=\frac{m_0+i}{m_0+m_1}g_{n-1,m_0,m_1,i}+\frac{m_1-i+1}{m_0+m_1}g_{n-1,m_0,m_1,i-1}
$$

$g$ 的转移顺序很普通，$f$ 的转移，注意到每轮游戏总牌数减一，因此先枚举 $m_0+m_1$ 再枚举 $m_0$ 即可。时间 $O(n^6)$（常数极小），可以通过。

**启示：游戏有人退出求概率，考虑按人数划分子问题。**

[AC 链接](https://atcoder.jp/contests/agc050/submissions/61055168)

---

## 作者：Zi_Gao (赞：1)

## 题意

有 $n$ 个人，$m$ 个物品，初始在一个队列里面排好，然后玩一个游戏：

1. 取出对头的人，这一回合这个人玩。
2. 这个人从自己在之前的回合中没选到过的物品中等概率选择一个物品。
   1. 若这个物品被其他人选走，则让这个人去到队尾。
   2. 若这个物品没被其他人选走，则让这个人离开，并选走这个物品。
3. 若队列里面还有人并且还有物品没被选走，则重复第一步。

问每个人拿到任意一个商品的概率，$n,m\leq 40$。

## 题解

肯定考虑设计一个 $dp$，表示什么什么的概率，但是发现一个很简单的状态难以描述本题这样复杂的局面，那就多记一点东西，设 $dp_{l,r,x,y}$ 表示考虑的这个人获得物品的概率，并且他左边有 $l$ 个人，右边有 $r$ 个人，现在算到这 $l+r+1$ 个人中第 $x$ 个人，在第 $y$ 大轮中。一大轮指队列循环了多少次，这样避免队列循环的问题。

发现可以转移了，分类讨论一下当前人是否拿到了物品即可，而这个概率是可以通过目前记下来的状态算出来的，首先到现在已经有 $n-l-r-1$ 个人被选走了，剩下 $m-\left(n-l-r-1\right)$ 个物品，而对于这个人前 $y-1$ 轮，每轮选一个物品，这些都不会选了，所以是 $m-\left(y-1\right)$，所以记 $p$ 为选走一个物品的概率，显然 $p=\frac{m-\left(n-l-r-1\right)}{m-\left(y-1\right)}$，剩下的就是分类讨论一下每种情况就可以了，看代码就好。

使用记搜要方便一些

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

#define MODINT_TYPE long long

namespace MODINT{
	unsigned long long d;
    __uint128_t m;
    const unsigned int barK=64;
    void init(long long mod){
        m=(((__uint128_t)1)<<barK)/(d=mod);
        return;
    }

    inline unsigned long long mod(register unsigned long long x){
        register unsigned long long w=(m*x)>>barK;
        w=x-w*d;
        return w>=d?w-d:w;
    }

    MODINT_TYPE exgcd(MODINT_TYPE a,MODINT_TYPE b,MODINT_TYPE &x,MODINT_TYPE &y){
        if(!b){
            x=1;
            y=0;
            return a;
        }
        MODINT_TYPE d=exgcd(b,a%b,y,x);
        y-=a/b*x;
        return d;
    }

    MODINT_TYPE inv(MODINT_TYPE n,MODINT_TYPE p){
        MODINT_TYPE x,y;
        exgcd(n,p,x,y);
        x%=p;
        return x>=0?x:x+p;
    }

    struct MODNUM{
        MODINT_TYPE val;
        MODNUM(MODINT_TYPE x){
            if(x<0){
                val=d-mod(-x);
                if(val>=d) val-=d;
            }else val=mod(x);
            return;
        }
        MODNUM(){val=0;}
        inline MODNUM operator + (const MODNUM& o) const{return (MODNUM){(val+o.val>=d)?(val+o.val-d):(val+o.val)};}
        inline MODNUM operator + (const MODINT_TYPE& o) const{return *this+MODNUM(o);}
        friend inline MODNUM operator + (const MODINT_TYPE &o,const MODNUM&a){return a+o;}
        inline MODNUM operator - (const MODNUM& o) const{return (MODNUM){(val-o.val<0)?(val-o.val+d):(val-o.val)};}
        inline MODNUM operator - (const MODINT_TYPE& o) const{return *this-MODNUM(o);}
        friend inline MODNUM operator - (const MODINT_TYPE &o,const MODNUM&a){return MODNUM(o)-a;}
        inline MODNUM operator * (const MODNUM& o) const{return (MODNUM){mod(val*o.val)};}
        inline MODNUM operator * (const MODINT_TYPE& o) const{return *this*MODNUM(o);}
        friend inline MODNUM operator * (const MODINT_TYPE &o,const MODNUM&a){return a*o;}
        inline MODNUM operator / (const MODNUM& o) const{return (MODNUM){mod(val*inv(o.val,d))};}
        inline MODNUM operator / (const MODINT_TYPE& o) const{return *this/MODNUM(o);}
        friend inline MODNUM operator / (const MODINT_TYPE &o,const MODNUM&a){return MODNUM(o)/a;}

        inline MODNUM operator ++(){
            ++val;
            if(val>=d) val-=d;
            return *this;
        }
        inline MODNUM operator ++(const int){
            MODNUM tmp=*this;
            ++val;
            if(val>=d) val-=d;
            return tmp;
        }
        inline MODNUM operator --(){
            --val;
            if(val<0) val+=d;
            return *this;
        }
        inline MODNUM operator --(const int){
            MODNUM tmp=*this;
            --val;
            if(val<0) val+=d;
            return tmp;
        }

        inline MODNUM& operator += (const MODNUM& o) {return *this=*this+o;}
        inline MODNUM& operator += (const MODINT_TYPE& o) {return *this=*this+o;}
        inline MODNUM& operator -= (const MODNUM& o) {return *this=*this-o;}
        inline MODNUM& operator -= (const MODINT_TYPE& o) {return *this=*this-o;}
        inline MODNUM& operator *= (const MODNUM& o) {return *this=*this*o;}
        inline MODNUM& operator *= (const MODINT_TYPE& o) {return *this=*this*o;}
        inline MODNUM& operator /= (const MODNUM& o) {return *this=*this/o;}
        inline MODNUM& operator /= (const MODINT_TYPE& o) {return *this=*this/o;}

        operator MODINT_TYPE(){return val;}

    };
};



MODINT::MODNUM dp[50][50][50][50],inv[50];
std::bitset<50> vis[50][50][50];

int n,k;

MODINT::MODNUM dfs(int x,int y,int z,int w){
    if(vis[x][y][z][w]) return dp[x][y][z][w];
    if(w>k||n-(x+y+1)>=k) return 0;
    register MODINT::MODNUM res=0,p=(k-(n-(x+y+1)))*inv[k-w+1],p2;
    p2=1-p;
    if(z==x+1) res=p*1+p2*(y?dfs(x,y,z+1,w):dfs(x,y,1,w+1));
    else if(z<x+1) res=p*dfs(x-1,y,z,w)+p2*dfs(x,y,z+1,w);
    else{
        if(z==x+y+1) res=p*dfs(x,y-1,1,w+1)+p2*dfs(x,y,1,w+1);
        else res=p*dfs(x,y-1,z,w)+p2*dfs(x,y,z+1,w);
    }

    vis[x][y][z][w]=1;
    return dp[x][y][z][w]=res;
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    MODINT::init(998244353);

    register int i;
    n=read();k=read();
    for(i=1;i<=k;++i)
        inv[i]=1/MODINT::MODNUM(i);

    for(i=1;i<=n;++i) print(dfs(i-1,n-i,1,1)),putchar('\n');

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```

---

