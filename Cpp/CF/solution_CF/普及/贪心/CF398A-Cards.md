# Cards

## 题目描述

User ainta loves to play with cards. He has $ a $ cards containing letter "o" and $ b $ cards containing letter "x". He arranges the cards in a row, and calculates the score of the deck by the formula below.

1. At first, the score is $ 0 $ .
2. For each block of contiguous "o"s with length $ x $ the score increases by $ x^{2} $ .
3. For each block of contiguous "x"s with length $ y $ the score decreases by $ y^{2} $ .

For example, if $ a=6,b=3 $ and ainta have arranged the cards in the order, that is described by string "ooxoooxxo", the score of the deck equals $ 2^{2}-1^{2}+3^{2}-2^{2}+1^{2}=9 $ . That is because the deck has 5 blocks in total: "oo", "x", "ooo", "xx", "o".

User ainta likes big numbers, so he wants to maximize the score with the given cards. Help ainta make the score as big as possible. Note, that he has to arrange all his cards.

## 样例 #1

### 输入

```
2 3
```

### 输出

```
-1
xoxox
```

## 样例 #2

### 输入

```
4 0
```

### 输出

```
16
oooo```

## 样例 #3

### 输入

```
0 4
```

### 输出

```
-16
xxxx```

# 题解

## 作者：密期望 (赞：3)

我们可以知道，如果'o'有$a$段，则一定是$a-1$段只有一个'o'剩下的1段包括其他'o'，而如果'x'有$a$段，那么最长的一段与最小的一段一定最多相差一个'x'。（数学归纳法应该可以证明，考场上没想这么多，就直接贪心了）

基于这个条件，我们就可以枚举'o'和'x'的段数，然后找最大值就可以了（也许可以三分或者退火？）

然后放一下我修改过后的考场代码
```
#include<cstdio>
#include<cstdlib>
typedef long long ll;
typedef long double ld;
const ll LLINF=0x3f3f3f3f3f3f3f3f;
ll read(){
    ll a=0;int op=1;char ch=getchar();
    while(ch<'0'||'9'<ch){if(ch=='-')op=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){a=a*10+ch-'0';ch=getchar();}
    return a*op;
}
void file(const char *str){
    char in[100],out[100];
    sprintf(in,"%s.in",str),sprintf(out,"%s.out",str);
    freopen(in,"r",stdin),freopen(out,"w",stdout);
}
ll n,m;
ll ans=-LLINF;
ll ansi;//'o'的段数
ll ansj;//'x'的段数减去'o'的段数，即相差的段数
ll get_max(ll x,ll k){//x个'o'，分k段
    return k-1+(x-k+1)*(x-k+1);
}
ll get_min(ll x,ll k){//x个'x'，分k段
    ll mod=x%k,div=x/k;
    return div*div*(k-mod)+(div+1)*(div+1)*mod;
}
void put(char ch,int ct){
    for(int i=0;i<ct;i++){
        putchar(ch);
    }
}
void print(int xi,int ki,int xj,int kj){
    int div=xj/kj;
    int mod=xj%kj;
    switch(ki-kj){//考场上的沙雕写法，不要在意
        case 1:{//oxoxo
            put('o',xi-ki+1);
            for(int i=1;i<=kj;i++){
                put('x',i<=mod?div+1:div);
                put('o',1);
            }
            break;
        }
        case 0:{//oxox
            put('o',xi-ki+1);
            for(int i=1;i<kj;i++){
                put('x',i<=mod?div+1:div);
                put('o',1);
            }
            put('x',div);
            break;
        }
        case -1:{//xoxox
            put('x',mod?div+1:div);
            put('o',xi-ki+1);
            put('x',2<=mod?div+1:div);
            for(int i=3;i<=kj;i++){
                put('o',1);
                put('x',i<=mod?div+1:div);
            }
            break;
        }
    }
}
void input(){
    n=read();
    m=read();
//这一段我在考场上并没有想到
//导致我re和wa掉了20分
//完全没考虑会有0，就gg了
    if(!n){
        printf("%lld\n",-m*m);
        for(int i=0;i<m;i++){
            printf("x");
        }
        exit(0);
    }
    if(!m){
        printf("%lld\n",n*n);
        for(int i=0;i<n;i++){
            printf("o");
        }
        exit(0);
    }
}
void ini(){
}
void solve(){
    ll ret;
    for(int i=1;i<=n;i++){//枚举'o'的段数
        for(int j=-1;j<=1;j++){//枚举相差的段数
            if(i+j>=1&&i+j<=m){
                ret=get_max(n,i)-get_min(m,i+j);
                if(ret>ans){
                    ans=ret;
                    ansi=i;
                    ansj=j;
                }
            }
        }
    }
}
void output(){
    printf("%lld\n",ans);
    print(n,ansi,m,ansi+ansj); 
}
void test(){
    input();
    ini();
    solve();
    output();
}
void all(){
    file("cards");
    test();
}
int main(){
    all();
    return 0;
}
```

---

## 作者：da32s1da (赞：2)

首先可能会有一些奇怪的贪心。。

- $\mathrm{xoxox....xoxoooo....o}$
- $\mathrm{xx...xxooooo...oooooxx...xx}$

看这组数据``5 8``。

- 第一个$\ \mathrm{xxoxxoxoxoxox}\ $，答案是$\ \mathrm{-7}$
- 第二个$\ \mathrm{xxxxoooooxxxx}\ $，答案是$\ \mathrm{-7}$

正确答案$\ \mathrm{xxooooxxxoxxx}\ $，答案是$\ \mathrm{-5}$

----

正解：**枚举x分几份**

具体来说$\ \mathrm{x...xooo...ooox...xox...xox...x}\ $。

那位什么后面的$\ \mathrm{x...x}\ $要用**一个**$\ \mathrm{o}\ $分开，而不是**多个**$\ \mathrm{o}\ $呢?

设前面有$\ t\ $个$\ \mathrm{o}\ $，分开$\ \mathrm{x...x}\ $用了$\ k\ $个$\ \mathrm{o}\ \ (1\lt k\lt n)$。

- $\ \ \ \ [\ (t-1)^2+1\ ]-[\ (t-k)^2+k^2\ ]$
- $=[\ (t-1)^2+1\ ]-[\ (t-k)^2+k^2\ ]$
- $=2(k-1)[t-(k+1)] \ge0$

所以用$\ 1\ $个$\ \mathrm{o}\ $是最优的。

```
#include<cstdio>
#include<cstdlib>
using namespace std;
typedef long long LL;
int n,m,r,p,q,res;
LL Ans,ans;
inline int min(int u,int v){return u<v?u:v;}
void spj(){//特判一些特殊情况
	if(!n){
		printf("%I64d\n",-1ll*m*m);
		for(int i=1;i<=m;i++)putchar('x');
		exit(0);
	}
	if(!m||m==1){
		printf("%I64d\n",1ll*n*n-m);
		for(int i=1;i<=n;i++)putchar('o');
		if(m)putchar('x');
		exit(0);
	}
}
int main(){
	scanf("%d%d",&n,&m);spj();
	Ans=-1e15;
	r=min(n+1,m);
	for(int i=2;i<=r;i++){//枚举分成几段
		p=m/i;q=m%i;
		ans=1ll*(n-i+2)*(n-i+2)+i-2-1ll*q*(p+1)*(p+1)-1ll*(i-q)*p*p;
		if(ans>Ans)Ans=ans,res=i;
	}
	printf("%I64d\n",Ans);
	p=m/res;q=m%res;r=res-q;
	for(int i=1;i<=p;i++)putchar('x');r--;
	for(int i=1;i<n-res+2;i++)putchar('o');
    //输出前面连续的 o
	for(int i=1;i<=r;i++){
		putchar('o');
		for(int j=1;j<=p;j++)putchar('x');
	}
	for(int i=1;i<=q;i++){
		putchar('o');
		for(int j=1;j<=p+1;j++)putchar('x');
	}
}
```

---

## 作者：Laisira (赞：0)

### 思路
简单题。

对于一个连续的 `x/o`，我们考虑分段从哪里分。设长度为 $a$ 有：
$$\frac{a}{2}\leq a^2-2a+2\leq a^2\ (a > 0)$$
则：
$$2\times(\frac{a}{2})^2\leq (a-1)^2+1^2\leq a^2\ (a > 0)$$

所以，在分段数相同的情况下，我们对 `x` 分的均匀负贡献越小，对 `o` 越集中越好。具体的，当 $k$ 个 `x` 分成 $d$ 段时，每段接近 $x/d$ 个 `x`，且之间用一个 `o` 隔开，其他 `o` 一起合并到其中一个将 `x` 分开的 `o` 中。

枚举 $k$ 即可，据上述证明得，贡献为：

$$(a-k+2)^2+(k-2)-[\lfloor\frac{b}{k}\rfloor-(b\mod k)]\times \lfloor\frac{b}{k}\rfloor^2-(b\mod k)\times (\lfloor\frac{b}{k}\rfloor+1)^2(2\leq k\leq a+1)$$

上面的式子是针对必须分段的，以便算 `o` 的贡献，然后再把 $k=1/0$ 的单独批判：

$$a^2-b^2$$
### 代码（马蜂抽象勿喷）
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
signed main()
{
	int a,b,o,ans,i;
	cin>>a>>b; o = i = 1;
	ans = a*a-b*b;
	for(i=2;i<=min(b,a+1);i++) {
		int p = (a-i+2)*(a-i+2)+(i-2)-(i-b%i)*(b/i)*(b/i)-(b%i)*(b/i+1)*(b/i+1);
		if(ans < p) o = i,ans = p;
	} cout<<ans<<"\n";
	for(int i=1;i<=o-b%o-(b%o == 0);i++) {
		for(int j=1;j<=b/o;j++) putchar('x');
		if(i != o-b%o-(b%o == 0)) putchar('o');
	} for(int i=1;i<=min(a,a-o+2);i++) putchar('o');
	if(b%o == 0) for(int j=1;j<=b/o;j++) putchar('x');
	for(int i=1;i<=b%o;i++) {
		for(int j=1;j<=b/o+1;j++) putchar('x');
		if(i != b%o) putchar('o');
	} return 0;
}
```

---

## 作者：VIOLET__FOREVER (赞：0)

## 分析
本题主要考察思维和简单的数学能力。  
根据题意我们要尽可能的使得 ```0``` 连续，```2``` 分散  
因为 $1^2+1^2>(1+1)^2$，反之同理。所以我们尽可能使得最后的形式是 ```2020...00...002``` 即是用 ```0```，将 ```2``` 分割开来。

首先我们从让一整段 ```0``` 将 ```2``` 分割成两段的情况开始讨论。此时有一整段 ```0``` 长度为 $n$ ，两段 ```2``` 长度可能都为 $m\div2$ ,或者一段 $m\div2$ 另一段为 $m\div2+1$ ，将 $n, m$ 的分段情况找出来之后就可以按照题目给的算法算出一个一个 $cnt$ 值。

然后我们再将情况拓展开，假设现在所有的 ```0``` 被分割成了 $i$ 段，那么此时所有的 ```2``` 就被分割成了 $i+1$ 段，这 $i$ 段的 ```0``` 中会有 $(i-1)$ 段的长度为 $1$ ，因为拿去用于分割 ```2```，剩下的一段就是我们保证的最长连续的 ```0```，长度为 $n-(i-1)$

此时的 ```2``` 被分成 $i+1$ 段，如果能整除，那么每段的长度就为 $m\div(i+1)$ ，如果无法整除呢，我们令 $m=x\times(i+1)+y$ ,其中 $x=m\div(i+1)$ ，$y=m\bmod(i+1)$，我们假设有 $p$ 段的长度为 $x$ , $q$ 段的长度为  $x+1$ 用一个简单的待定系数法就可以算出 $q=m\bmod(i+1)$，$p=(i+1)- m \bmod (i+1) $;

这样我们就把可以把这种情况下的 $cnt$ 值算出来，现在由于 ```0``` 最多只有 $n$ 个所以最多只能被分成 $n$ 段，那么我们就枚举 $i$ 从 $1$ 到 $n$ ，把每种情况下的 $cnt$ 算出来找到最大的，并把当前的分段情况记录下来用于之后的输出就可以了

---

