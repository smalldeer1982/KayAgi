# [国家集训队] Tree II

## 题目描述

一棵 $n$ 个点的树，每个点的初始权值为 $1$。  
对于这棵树有 $q$ 个操作，每个操作为以下四种操作之一：

- `+ u v c`：将 $u$ 到 $v$ 的路径上的点的权值都加上自然数 $c$；
- `- u1 v1 u2 v2`：将树中原有的边 $(u_1,v_1)$ 删除，加入一条新边 $(u_2,v_2)$，保证操作完之后仍然是一棵树；
- `* u v c`：将 $u$ 到 $v$ 的路径上的点的权值都乘上自然数 $c$；
- `/ u v`：询问 $u$ 到 $v$ 的路径上的点的权值和，将答案对 $51061$ 取模。


## 说明/提示

【数据范围】   
对于 $10\%$ 的数据，$1\le n,q \le 2000$；   
另有 $15\%$ 的数据，$1 \le n,q \le 5\times 10^4$，没有 `-` 操作，并且初始树为一条链；    
另有 $35\%$ 的数据，$1 \le n,q \le 5\times 10^4$，没有 `-` 操作；  
对于 $100\%$ 的数据，$1\le n,q \le 10^5$，$0\le c \le 10^4$。

By (伍一鸣)


## 样例 #1

### 输入

```
3 2
1 2
2 3
* 1 3 4
/ 1 1```

### 输出

```
4
```

# 题解

## 作者：FlashHu (赞：55)

关于LCT的其它问题可以参考一下[我的博客](http://www.cnblogs.com/flashhu/p/8324551.html)


一道LCT很好的练习放懒标记技巧的题目。


一开始看到又做加法又做乘法的时候我是有点mengbi的。


然后我想起了模板线段树2。。。。。。（相信各位Dalao一定做过这道题）


这里的维护懒标记方法很像。除了翻转标记以外还要维护乘法标记和加法标记。


根据运算优先级，乘法是要先算的，所以先放，放的时候子树的$sum$,乘法标记，加法标记，儿子的$val$统统都要乘一遍。


放加法标记的时候，想到线段树的区间大小是稳定的，而Splay并不是，所以还要维护$size$，于是子树的$sum$要加上子树的$size$再乘上标记，而儿子的$val$和加法标记直接加上该标记的值。


再注意一个小细节。


~~有没有觉得51061这个数好小啊。。。~~我看到的时候特高兴，不用担心longlong的问题了。然而。。。


$51061^2=2607225721>2147483647$


所以要开unsigned int。。。。。。


还是上代码吧

```cpp
#include<cstdio>
#include<cstdlib>
#define R register unsigned int
#define I inline
#define YL 51061
#define lc c[x][0]
#define rc c[x][1]
#define mul(x) x*=c;x%=YL
#define add(x,c) x+=c;x%=YL
#define G ch=getchar()
#define gc G;while(ch<'*')G
#define in(z) gc;z=ch&15;G;while(ch>'*')z*=10,z+=ch&15,G;
const int N=100009;
unsigned int n,f[N],c[N][2],v[N],s[N],sz[N],lm[N],la[N],st[N];
bool r[N];
I bool nroot(R x){//好像Dalao都写的是isroot
    return c[f[x]][0]==x||c[f[x]][1]==x;
}
I void pushup(R x){
    s[x]=(s[lc]+s[rc]+v[x])%YL;
    sz[x]=sz[lc]+sz[rc]+1;
}
I void pushr(R x){//翻转
    R t=lc;lc=rc;rc=t;r[x]^=1;
}
I void pushm(R x,R c){//乘
    mul(s[x]);mul(v[x]);mul(lm[x]);mul(la[x]);
}
I void pusha(R x,R c){//加
    add(s[x],c*sz[x]);add(v[x],c);add(la[x],c);
}
I void pushdown(R x){
    if(lm[x]!=1)pushm(lc,lm[x]),pushm(rc,lm[x]),lm[x]=1;
    if(la[x])   pusha(lc,la[x]),pusha(rc,la[x]),la[x]=0;
    if(r[x])   {if(lc)pushr(lc);if(rc)pushr(rc);r[x]=0;}
}
I void rotate(R x){
    R y=f[x],z=f[y],k=c[y][1]==x,w=c[x][!k];
    if(nroot(y))c[z][c[z][1]==y]=x;c[x][!k]=y;c[y][k]=w;//注意if(nroot(y))，本蒟蒻经常忘写
    if(w)f[w]=y;f[y]=x;f[x]=z;
    pushup(y);
}
I void splay(R x){
    R y=x,z=0;
    st[++z]=y;//手动放个栈
    while(nroot(y))st[++z]=y=f[y];
    while(z)pushdown(st[z--]);
    while(nroot(x)){
        y=f[x];z=f[y];
        if(nroot(y))
            rotate((c[y][0]==x)^(c[z][0]==y)?x:y);
        rotate(x);
    }
    pushup(x);
}
I void access(R x){
    for(R y=0;x;x=f[y=x])
        splay(x),rc=y,pushup(x);
}
I void makeroot(R x){
    access(x);
    splay(x);
    pushr(x);
}
I void split(R x,R y){
    makeroot(x);
    access(y);
    splay(y);
}
I void link(R x,R y){
    makeroot(x);f[x]=y;
}
I void cut(R x,R y){
    split(x,y);f[x]=c[y][0]=0;
}
int main()
{
    register char ch;
    R q,i,a,b,k;
    in(n);in(q);
    for(i=1;i<=n;++i)v[i]=sz[i]=lm[i]=1;//注意乘法标记的初值为1
    for(i=1;i<n;++i){
        in(a);in(b);
        link(a,b);
    }
    while(q--){
        gc;
        switch(ch){
        case '+':
            in(a);in(b);in(k);
            split(a,b);pusha(b,k);
            break;
        case '-':
            in(a);in(b);cut(a,b);
            in(a);in(b);link(a,b);
            break;
        case '*':
            in(a);in(b);in(k);
            split(a,b);pushm(b,k);
            break;
        case '/':
            in(a);in(b);
            split(a,b);
            printf("%d\n",s[b]);
        }
    }
    return 0;
}
```

---

## 作者：Soulist (赞：10)

注意下传标记的$LCT$

下传方法与线段树2异斧同工，乘法优先，加法其次。

每次下传时，注意到一颗$Splay$维护了一条链的信息，所以我只需要$split(x,y)$

把$x-y$这一条链拉出来，然后就再在顶部$(y)$处打上一个标记即可。

其他处理都类似的需要$split$

比如：

询问$x-y$的答案，考虑先$split(x,y)$，然后$y$是$Splay$的根，所以我们直接输出$t[y].val(val$ 表示这颗子树的和$)$

操作$2$是直接：$cut\quad\&\quad link$

乘法和加法一样，先$split$，然后在$Splay$的根部打上一个标记即可。

注意细节，与线段树2较为相似

```cpp

#include<bits/stdc++.h>
using namespace std;
#define il inline
#define int unsigned int
il int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
#define ls(x) t[x].son[0]
#define rs(x) t[x].son[1]
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define mod 51061
const int N = 3e5 + 5;
char s[5];
struct LCT{
	int son[2], val, add, mul, fa, size;
	bool mark;
}t[N];
int w[N], n, q;
void push1( int x, int c ) {
	t[x].val = ( t[x].size * c % mod + t[x].val ) % mod;
	w[x] += c, t[x].add += c, t[x].add %= mod;
	w[x] %= mod;
}
void push2( int x, int c ) {
	t[x].val *= c, w[x] *= c, t[x].mul *= c, t[x].add *= c; //要给add也乘上c 
	t[x].val %= mod, w[x] %= mod, t[x].mul %= mod, t[x].add %= mod;
}
void pushmark( int x ) { //pushmark的部分与线段树2相同QWQ... 
	if( t[x].mul != 1 )  push2( ls(x), t[x].mul ), push2( rs(x), t[x].mul ), t[x].mul = 1;
	if( t[x].add )  push1( ls(x), t[x].add ), push1( rs(x), t[x].add ), t[x].add = 0;
	if( t[x].mark ) {
		t[x].mark = 0, t[ls(x)].mark ^= 1, t[rs(x)].mark ^= 1;
		swap( ls(x), rs(x) );
	}
	t[x].val %= mod, w[x] %= mod; //注意取模 
}
void pushup( int x ) { 
	t[x].val = ( w[x] + t[ls(x)].val + t[rs(x)].val ) % mod, 
	t[x].size = t[ls(x)].size + t[rs(x)].size + 1;
	t[x].val %= mod;
}
bool isroot( int x ) {
	return ( rs(t[x].fa) != x ) && ( ls(t[x].fa) != x );
}
void rotate( int x ) {
	int f = t[x].fa, ff = t[f].fa, qwq = ( rs(f) == x );
	t[x].fa = ff;
	if( !isroot(f) ) t[ff].son[(rs(ff) == f)] = x; //如果父亲不为根才改爷爷 
	t[t[x].son[qwq ^ 1]].fa = f, t[f].son[qwq] = t[x].son[qwq ^ 1],
	t[f].fa = x, t[x].son[qwq ^ 1] = f;
	pushup(f), pushup(x);
} 
int st[N];
void Splay( int x ) {
	int top = 0, now = x;
	st[++top] = x;
	while( !isroot(now) ) st[++top] = ( now = t[now].fa );
	while( top ) pushmark( st[top--] );
	while( !isroot(x) ) {
		int f = t[x].fa, ff = t[f].fa;
		if( !isroot(f) ) ( ( rs(f) == x ) ^ ( rs(ff) == f ) ) ? rotate(x) : rotate(f);
		rotate(x);
	}
}
void access( int x ) {
	for( int y = 0; x; y = x, x = t[y].fa )
		Splay( x ), t[x].son[1] = y, pushup( x );
}
void makeroot( int x ) {
	access( x ), Splay( x ), t[x].mark ^= 1, pushmark( x );
}
int findroot( int x ) {
	access( x ), Splay( x ), pushmark( x );
	while( ls(x) ) pushmark( x = ls(x) );
	return x;
}
void split( int x, int y ) { //split 
	makeroot( x ), access( y ), Splay( y );
}
void link( int x, int y ) {
	makeroot( x );
	if( findroot( y ) != x ) t[x].fa = y; //还是要判断....... 
}
void cut( int x, int y ) { //明明数据保证了合法，但实际上还是要判断...... 
	makeroot( x );
	if( findroot(y) == x && t[x].fa == y && ls(y) == x && !rs(x) )
		t[x].fa = t[y].son[0] = 0, pushup( y );
}
signed main()
{
	n = read(), q = read();  int x, y, u1, u2, v1, v2, c;
	rep( i, 1, n - 1 ) x = read(), y = read(), link( x, y ), t[i].mul = w[i] = 1; //这里要注意初始化。 
	t[n].mul = w[n] = 1;
	rep( i, 1, q ) {
		scanf("%s", s);
		if( s[0] == '+' ) u1 = read(), v1 = read(), c = read() % mod, split( u1, v1 ), push1( v1, c );

		if( s[0] == '-' ) u1 = read(), v1 = read(), u2 = read(), v2 = read(), cut( u1, v1 ), link( u2, v2 );
		
		if( s[0] == '/' ) u1 = read(), v1 = read(), split( u1, v1 ), printf("%d\n", t[v1].val % mod);
			
		if( s[0] == '*')  u1 = read(), v1 = read(), c = read() % mod, split( u1, v1 ), push2( v1, c );
	}
	return 0;
}
```

---

## 作者：KiDDOwithTopTree (赞：5)

题目在这：[传送门](https://www.luogu.com.cn/problem/P1501)。

一道不错的 LCT 练手题。

写这一题之前可以先看看[线段树2](https://www.luogu.com.cn/problem/P3373)，因为这题有它的懒标记思想。

这题同样有加法操作和乘法操作。所以我们的懒标记有三个：1.处理区间反转的 rev 标记，2.对子树整体加的 add 标记，3.对子树整体乘的 mul 标记。

我们用 sum 表示以 y 为根的子树的权值和。

+ \+：就是 split 出 u 到 v 的路径，在 v 处打上 add 标记。

+ \-：就是把 $u_1$ 到 $v_1$ 的路径 cut 掉，再把 $u_2$ 到 $v_2$ 的路径 link 上。

+ \*：就是 split 出 u 到 v 的路径，在 v 处打上 mul 标记。

+ \：就是 split 出 u 到 v 的路径，输出 v 出存储的 sum 值。

当然不要忘记开 long long 哦。

放上代码：

```cpp
#include<iostream>
using namespace std;
#define int long long
const int N=1e5+10,mod=51061;
struct splay{
	int add,mul,rev;
	int fa,son[2];
	int val,sum;
	int size;
};
splay spl[N];
inline bool check_root(int pos){
	return spl[spl[pos].fa].son[0]!=pos&&spl[spl[pos].fa].son[1]!=pos;
}
inline void connect(int pos,int fa,int son){
	spl[fa].son[son]=pos;
	spl[pos].fa=fa;
}
inline int relation(int pos,int fa){
	return spl[fa].son[1]==pos;
}
inline void pushup(int pos){
	int lson=spl[pos].son[0],rson=spl[pos].son[1];
	spl[pos].size=spl[lson].size+spl[rson].size+1;
	spl[pos].sum=(spl[lson].sum+spl[rson].sum+spl[pos].val)%mod;
}
inline void pushdown(int pos){
	if(spl[pos].rev){
		swap(spl[pos].son[0],spl[pos].son[1]);
		spl[spl[pos].son[0]].rev^=1;
		spl[spl[pos].son[1]].rev^=1;
		spl[pos].rev=0;
	}
	int lson=spl[pos].son[0],rson=spl[pos].son[1];
	int lsize=spl[lson].size,rsize=spl[rson].size;
	spl[lson].sum=(spl[lson].sum*spl[pos].mul%mod+spl[pos].add*lsize%mod)%mod;
	spl[rson].sum=(spl[rson].sum*spl[pos].mul%mod+spl[pos].add*rsize%mod)%mod;
	spl[lson].val=(spl[lson].val*spl[pos].mul%mod+spl[pos].add%mod)%mod;
	spl[rson].val=(spl[rson].val*spl[pos].mul%mod+spl[pos].add%mod)%mod;
	spl[lson].add=(spl[lson].add*spl[pos].mul%mod+spl[pos].add%mod)%mod;
	spl[rson].add=(spl[rson].add*spl[pos].mul%mod+spl[pos].add%mod)%mod;
	spl[lson].mul=spl[lson].mul*spl[pos].mul%mod;
	spl[rson].mul=spl[rson].mul*spl[pos].mul%mod;
	spl[pos].mul=1;
	spl[pos].add=0;
}//可以参考线段树2
inline void pushall(int pos){
	if(!check_root(pos))
		pushall(spl[pos].fa);
	pushdown(pos);
}
void rotate(int pos){
	int fa=spl[pos].fa,gf=spl[fa].fa;
	int t1=relation(pos,fa),t2=relation(fa,gf);
	connect(spl[pos].son[t1^1],fa,t1);
	connect(fa,pos,t1^1);
	if(spl[gf].son[t2]==fa)
		connect(pos,gf,t2);
	else
		spl[pos].fa=gf;
	pushup(fa);
	pushup(pos);
}
void splaying(int pos){
	pushall(pos);
	while(!check_root(pos)){
		int fa=spl[pos].fa,gf=spl[fa].fa;
		if(!check_root(fa))
			relation(pos,fa)^relation(fa,gf)?rotate(pos):rotate(fa);
		rotate(pos);
	}
}
void access(int pos){
	int son=0;
	while(pos){
		splaying(pos);
		spl[pos].son[1]=son;
		pushup(pos);
		son=pos;
		pos=spl[pos].fa;
	}
}
void make_root(int pos){
	access(pos);
	splaying(pos);
	spl[pos].rev^=1;
}
int find_root(int pos){
	access(pos);
	splaying(pos);
	while(spl[pos].son[0]){
		pos=spl[pos].son[0];
		pushdown(pos);
	}
	splaying(pos);
	return pos;
}
void link(int x,int y){
	make_root(x);
	access(y);
	splaying(y);
	spl[x].fa=y;
}
void cut(int x,int y){
	make_root(x);
	access(y);
	splaying(y);
	spl[y].son[0]=0;
	spl[x].fa=0;
}
void split(int x,int y){
	make_root(x);
	access(y);
	splaying(y);
}
signed main(){
	int n,m;
	cin>>n>>m;
	int x,y;
	for(int i=1;i<=n;i++)
		spl[i].mul=spl[i].val=spl[i].sum=1;
	for(int i=1;i<=n-1;i++){
		cin>>x>>y;
		link(x,y);
	}
	char opt;
	int u,v,val;
	for(int i=1;i<=m;i++){
		cin>>opt;
		switch(opt){
			case '+':
				cin>>x>>y>>val;
				split(x,y);
				spl[y].add=(spl[y].add%mod+val%mod)%mod;
				spl[y].val=(spl[y].val%mod+val%mod)%mod;
				spl[y].sum=(spl[y].sum%mod+val*spl[y].size%mod)%mod;
				break;
			case '-':
				cin>>x>>y>>u>>v;
				cut(x,y);
				link(u,v);
				break;
			case '*':
				cin>>x>>y>>val;
				split(x,y);
				spl[y].val=spl[y].val*val%mod;
				spl[y].mul=spl[y].mul*val%mod;
				spl[y].add=spl[y].add*val%mod;
				spl[y].sum=spl[y].sum*val%mod;
				//同样可以参考线段树2
				break;
			case '/':
				cin>>x>>y;
				split(x,y);
				cout<<spl[y].sum<<'\n';
				break;
		}
	}
}
```

---

## 作者：Sai0511 (赞：5)

lct。       
根据题面的删边，加边等各种操作基本上十分明显的提示了你这题应该使用lct。      
唯一的难点就在于懒标记（感觉这题和线段树2差不多？）  
因为乘法的优先级比加法高，所以应该优先考虑乘法。   
一个点的真实值应该是原有的值加上加法懒标记所标记的值，我们可以把它括在一个括号里然后用乘法拆掉。   
不难发现$\text{val,tagadd,tagmul,sum}$都要进行改变。         
接着再考虑加法              
因为某一段区间的长度并不是固定的，所以我们需要维护一下$\text{size}$。        
其他的就没什么了。     
注意$\text{pushup}$的时候只能够$\text{pushup}$当前的点和原来的父亲，不能对祖父进行操作，否则会对$\text{size}$产生影响。         
### My Code：
```cpp
#include <bits/stdc++.h>
#define il inline
const int maxn = 1e5 + 10;
const int P = 51061;
using namespace std;
namespace Fast_Input {
    template<class T> il void read(T& res) {
        res = 0;  char ch;  bool sign = 0;  
        do ch = getchar(),sign |= ch == '-'; while(!isdigit(ch));   
        while(isdigit(ch)) res = (res << 1) + (res << 3) + (ch & 15),ch = getchar();
        (sign) && (res = -res);
    }
}
using Fast_Input::read;       
int n,m,i,j,k,Task;     
il void _swap(int& x,int& y) {
    x ^= y ^= x ^= y;  return;
}
struct Link_Cut_Tree {
    int size[maxn],ch[maxn][2],sum[maxn],fa[maxn],val[maxn],sta[maxn];  int tmul[maxn],tadd[maxn];
    bool trev[maxn];        
    il void pre() {
        for(int i = 1;i <= n;i++) size[i] = val[i] = tmul[i] = 1;  
        return;
    }
    il void push_up(int o) {
        size[o] = size[ch[o][0]] + size[ch[o][1]] + 1;         
        sum[o] = (sum[ch[o][0]] + sum[ch[o][1]] + val[o]) % P;
        return;
    }
    il void dmul(int o,int m) {
        tmul[o] = (1ll * tmul[o] * m) % P;  sum[o] = (1ll * sum[o] * m) % P;        
        val[o] = (1ll * val[o] * m) % P;  tadd[o] = (1ll * tadd[o] * m) % P; 
        return;
    }
    il void dadd(int o,int a) {
        sum[o] = (sum[o] + a * size[o]) % P;  tadd[o] += a;  val[o] += a;  return;
    }
    il void push_down(int o) {
        if(tmul[o] != 1) dmul(ch[o][0],tmul[o]),dmul(ch[o][1],tmul[o]),tmul[o] = 1;
        if(tadd[o]) dadd(ch[o][0],tadd[o]),dadd(ch[o][1],tadd[o]),tadd[o] = 0;   
        if(trev[o]) {
            trev[o] = 0;  
            trev[ch[o][0]] ^= 1; 
            trev[ch[o][1]] ^= 1;
            _swap(ch[o][0],ch[o][1]);
        }
        return;
    }
    il bool IsRoot(int o) {
        return ch[fa[o]][0] != o && ch[fa[o]][1] != o;
    }
    il int Ident(int o) {
        return ch[fa[o]][1] == o;
    }
    il void rotate(int u) {
        int oldf = fa[u],oldgf = fa[oldf];  bool whi = Ident(u);
        if(!IsRoot(oldf)) ch[oldgf][Ident(oldf)] = u;              
        ch[oldf][whi] = ch[u][whi ^ 1];   
        fa[ch[u][whi ^ 1]] = oldf;       
        ch[u][whi ^ 1] = oldf;
        fa[oldf] = u;  fa[u] = oldgf;    
        push_up(oldf);  push_up(u);  
    }
    il void splay(int u) {
        sta[0] = 0;  sta[++sta[0]] = u;    
        for(int i = u;!IsRoot(i);i = fa[i]) sta[++sta[0]] = fa[i];     
        while(sta[0]) push_down(sta[sta[0]--]);       
        for(int f = fa[u];!IsRoot(u);rotate(u),f = fa[u]) {
            if(!IsRoot(f)) rotate(Ident(f) == Ident(u) ? f : u);
        }
        push_up(u);
        return;
    }
    il void access(int x) {
        for(int y = 0;x;x = fa[y = x]) {
            splay(x);  
            ch[x][1] = y; 
            push_up(x);
        }
        return;
    }
    il void make_root(int u) {
        access(u);  splay(u);  trev[u] ^= 1;   return;
    }
    il void split(int x,int y) {
        make_root(x);  access(y);  splay(y);  return;
    }
    il void link(int x,int y) {
        make_root(x);  fa[x] = y;  return;
    }
    il void cut(int x,int y) {
        split(x,y);           
        fa[x] = ch[y][0] = 0;   
        return;
    }               
} lct;
int main() {
    read(n);  read(Task);  
    lct.pre();
    for(int i = 1,u,v;i < n;i++) {
        read(u);  read(v);  
        lct.link(u,v);
    }  
    for(int u,v,ru,rv,ov;Task;--Task) {
        char op[3];  scanf("%s",op);          
        if(op[0] == '+') {
            read(u);  read(v);  read(ov);     
            lct.split(u,v);  lct.dadd(v,ov);
        } else if(op[0] == '-') {
            read(u);  read(v);  read(ru);  read(rv);        
            lct.cut(u,v);  lct.link(ru,rv);  		
        } else if(op[0] == '*') {
            read(u);  read(v);  read(ov);
            lct.split(u,v);  lct.dmul(v,ov);
        } else {
            read(u);  read(v);    
            lct.split(u,v);  printf("%d\n",lct.sum[v]);
        }    
    //	for(int i = 1;i <= n;i++) printf("%d %d %d %d %d\n",lct.sum[i],lct.tadd[i],lct.tmul[i],lct.val[i],lct.size[i]);  puts("");
    }
    return 0;
}
```

---

## 作者：Wuyanru (赞：2)

看到这道题，我们肯定会想到使用 LCT 维护树上信息，还不会 LCT 的同学建议先去完成模板。

此外本题需要维护的操作有加法与乘法，使用 Splay 不熟练的同学们可以考虑使用 Splay 完成线段树的前两个模板。

接下来让我们分析每个操作如何完成。

1.  将某条路径上的点权全部增加一个数，这个操作可以先通过 LCT 的 $ split $ 函数将这条路径上的点单独放在一颗 Splay 上，然后对 Splay 的根节点的加法标记进行更改即可。

2.  删除一条边，再加入一条边，直接使用 LCT 的 $ cut $ 函数与 $ link $ 函数即可解决问题。

3.  将某条路径上的点权全部乘一个数，与操作一类似，只需要更改乘法标记即可。

4.  询问某条路径上点权和，与操作一和操作三类似，访问 Splay 根节点的值即可。

读入时只需要根据读入的边不断进行 $ link $ 操作即可建成一棵 LCT。

下面是对 Splay 标记下放的一些细节的说明：

首先乘法标记比加法标记优先级高，这一点和线段树一样。

懒标记的打法我知道的共有以下两种，方法不太一样。

1.  打标记时同时更新这个节点的信息，下传时更新儿子节点标记的同时更新儿子的权值与其子树权值。

2.  打标记时不更新其他信息，下传时更新儿子节点标记的同时更新本身的权值与子树权值。

两种方法都差不多，一定要记住：在更新某个点子树权值时一定要记得懒标记！

其次，因为有加法标记的出现，所以 Splay 还得同时统计子树内的节点个数。

最后，只需要在节点之间关系有变动的时候进行标记下传与权值的更新即可。

小坑点：本题中模数的平方比 $ 2^{31}-1 $ 大，所以使用 int 会炸。

讲真的，这题看上去就比较板，新学 LCT 的同学~~例如我~~来做还是非常不错的，这种题细节也比较多，用于提升码力也是很不错的。

代码（码风略丑勿喷）：

```
#include<bits/stdc++.h>
using namespace std;
namespace lct
{
	inline int read()
	{
		int s=0;
		char ch;
		while((ch=getchar())>'9'||ch<'0');
		while(ch>='0'&&ch<='9')
		{
			s=s*10+ch-'0';
			ch=getchar();
		}
		return s;
	}
	void write(int s,char ch=0)
	{
		if(s>9)
			write(s/10);
		putchar(s-s/10*10+'0');
		if(ch)
			putchar(ch);
	}
	const int mod=51061;
	int sta[100001],top;
	int son[100001][2];
	int tagc[100001];
	int tagj[100001];
	int size[100001];
	bool rev[100001];
	int num[100001];
	int val[100001];
	int fa[100001];
	int n,q;
	inline void swap(int &a,int &b)
	{
		int t=a;
		a=b,b=t;
	}
	void push_up(int x)
	{
		size[x]=size[son[x][0]]+size[son[x][1]]+1;
		val[x]=(((long long)tagc[son[x][0]]*val[son[x][0]]+(long long)tagj[son[x][0]]*size[son[x][0]]+(long long)tagc[son[x][1]]*val[son[x][1]]+(long long)tagj[son[x][1]]*size[son[x][1]]+num[x])*tagc[x]+(long long)tagj[x]*size[x])%mod;
	}
	void push_down(int x)
	{
		if(rev[x])
		{
			swap(son[x][0],son[x][1]);
			rev[x]^=1;
			rev[son[x][0]]^=1;
			rev[son[x][1]]^=1;
		}
		if(son[x][0])
		{
			tagj[son[x][0]]=((long long)tagj[son[x][0]]*tagc[x]+tagj[x])%mod;
			tagc[son[x][0]]=((long long)tagc[son[x][0]]*tagc[x])%mod;
		}
		if(son[x][1])
		{
			tagj[son[x][1]]=((long long)tagj[son[x][1]]*tagc[x]+tagj[x])%mod;
			tagc[son[x][1]]=((long long)tagc[son[x][1]]*tagc[x])%mod;
		}
		val[x]=((long long)val[x]*tagc[x]+(long long)size[x]*tagj[x])%mod;
		num[x]=((long long)num[x]*tagc[x]+tagj[x])%mod;
		tagj[x]=0;
		tagc[x]=1;
	}
	void debug()
	{
		/*for(int i=1;i<=n;i++)
			printf("%d : fa=%d ls=%d rs=%d size=%d val=%d num=%d tagj=%d tagc=%d rev=%d\n",i,fa[i],son[i][0],son[i][1],size[i],val[i],num[i],tagj[i],tagc[i],rev[i]);
		printf("\n");*/
	}
	void rotate(int x)
	{
		//printf("->rotate %d\n",x);
		int y=fa[x];
		int z=fa[y];
		int c=son[y][1]==x;
		son[y][c]=son[x][!c];
		if(son[x][!c])
			fa[son[x][!c]]=y;
		son[x][!c]=y;
		fa[y]=x;
		fa[x]=z;
		if(son[z][0]==y||son[z][1]==y)
			son[z][son[z][1]==y]=x;
		//printf("rotate->\n");
		debug();
		push_up(y);
		push_up(x);
		debug();
	}
	bool isroot(int x)
	{
		return son[fa[x]][0]!=x&&son[fa[x]][1]!=x;
	}
	void Splay(int x)
	{
		//printf("->Splay %d\n",x);
		sta[top=1]=x;
		for(int i=x;!isroot(i);i=fa[i])
			sta[++top]=fa[i];
		while(top)
			push_down(sta[top--]);
		while(!isroot(x))
		{
			int y=fa[x];
			int z=fa[y];
			if(!isroot(y))
				(son[z][1]==y)^(son[y][1]==x)?rotate(x):rotate(y);
			rotate(x);
		}
		//printf("Splay->\n");
		debug();
	}
	void access(int x)
	{
		//printf("->access %d\n",x);
		for(int y=0;x;)
		{
			Splay(x);
			son[x][1]=y;
			if(y)
				fa[y]=x;
			push_up(x);
			y=x;
			x=fa[x];
		}
		//printf("access->\n");
		debug();
	}
	void makeroot(int x)
	{
		//printf("->makeroot %d\n",x);
		access(x);
		Splay(x);
		rev[x]^=1;
		//printf("makeroot->\n");
		debug();
	}
	void link(int x,int y)
	{
		//printf("->link %d,%d\n",x,y);
		makeroot(x);
		fa[x]=y;
		//printf("link->\n");
		debug();
	}
	void split(int x,int y)
	{
		//printf("->split %d,%d\n",x,y);
		makeroot(x);
		access(y);
		Splay(y);
		//printf("split->\n");
		debug();
	}
	void add(int u,int v,int c)
	{
		//printf("->add %d,%d,%d\n",u,v,c);
		split(u,v);
		tagj[v]=(tagj[v]+c)%mod;
		//printf("add->\n");
		debug();
	}
	void times(int u,int v,int c)
	{
		//printf("->times %d,%d,%d\n",u,v,c);
		split(u,v);
		tagc[v]=((long long)tagc[v]*c)%mod;
		//printf("times->\n");
		debug();
	}
	void cut(int x,int y)
	{
		//printf("->cut %d,%d\n",x,y);
		split(x,y);
		push_down(y);
		son[y][0]=fa[x]=0;
		push_up(y);
		//printf("cut->\n");
		debug();
	}
	int ask(int u,int v)
	{
		//printf("ask(%d,%d)\n",u,v);
		split(u,v);
		push_down(v);
		//printf("%d\n",val[v]);
		return val[v];
	}
	void init()
	{
		n=read(),q=read();
		for(int i=1;i<=n;i++)
		{
			tagc[i]=1;
			size[i]=1;
			val[i]=num[i]=1;
		}
		debug();
		for(int i=1;i<n;i++)
		{
			int a=read(),b=read();
			link(a,b);
		}
	}
	void run()
	{
		init();
		for(int i=1;i<=q;i++)
		{
			char op[2];
			scanf("%s",op);
			if(op[0]=='+')
			{
				int u=read(),v=read(),c=read();
				add(u,v,c);
			}
			else if(op[0]=='-')
			{
				int u=read(),v=read();
				cut(u,v);
				u=read(),v=read();
				link(u,v);
			}
			else if(op[0]=='*')
			{
				int u=read(),v=read(),c=read();
				times(u,v,c);
			}
			else
			{
				int u=read(),v=read();
				write(ask(u,v),'\n');
			}
		}
	}
}
int main()
{
	lct::run();
	return 0;
}
```

感谢观看！

---

## 作者：warzone (赞：2)

练习 LCT 的好题，有利于在通过模板后整顿一下凌乱的码风  
~~看的时候就当卡常技巧得了~~  
首先，已知 $2^{15}<51061<2^{16}$，所以用 `unsigned short` 存储，`unsigned int` 计算是最优的。  
其次，由于既要维护乘法又要维护加法，易想到 [P3373 【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)  ，于是优先级为先乘后加。  
注意此处加法还要维护 $\text{size}$，LCT 还要实现区间翻转。  
很容易就实现了标记的下传和更新，放在结构体中。  
```cpp
typedef unsigned int	word;
typedef unsigned short hword;
typedef unsigned char	byte;
const hword mod=51061;
struct splay{
	splay *l,*r,*fa;
	hword sum,size;
	hword plustag,multag;
	byte tag;
	inline splay(){sum=size=multag=1;}
	inline void operator +=(register word num){
		sum=(num*size+sum)%mod;
		if((num+=plustag)>=mod) num-=mod;
		plustag=num;
	}//打上加法标记
	inline void operator *=(register word num){
		plustag=num*plustag	%mod;
		multag=	num*multag	%mod;
		sum=	num*sum		%mod;
	}//打上乘法标记
	inline void operator +=(register splay* p){
		register word num=p->sum;
		if((num+=sum)>=mod) num-=mod;
		sum=num,num=p->size;
		if((num+=size)>=mod) num-=mod;
		size=num;
	}//加入儿子时更新size与和
	inline void operator -=(register splay* p){
		register word num=mod-p->sum;
		if((num+=sum)>=mod) num-=mod;
		sum=num,num=mod-p->size;
		if((num+=size)>=mod) num-=mod;
		size=num;
	}//删除儿子时更新size与和
	inline void pushdown(){
		if(tag){
			if(l) l->tag^=1;
			if(r) r->tag^=1;
			register splay* swap=l;
			l=r,r=swap,tag=0;
		}
		if(multag!=1){
			if(l) *l*=multag;
			if(r) *r*=multag;
			multag=1;
		}
		if(plustag){
			if(l) *l+=plustag;
			if(r) *r+=plustag;
			plustag=0;
		}
	}//三种标记下传
	inline void linepush(){
		if(fa) fa->linepush();
		pushdown();
	}//伸展前的标记下传
}p[100010];
```
接下来实现旋转，从而实现伸展操作。
```cpp
#define cycle(root,l,r)	do{			\
	register splay* rt=root;		\
	register splay* l=rt->l;		\
	register splay* l##r=l->r;		\
	l->fa=rt->fa,(root)=l;			\
	l->r=rt,rt->fa=l; 				\
	*rt-=l,*l+=rt,rt->l=l##r;		\
	if(l##r) *rt+=l##r,l##r->fa=rt;	\
}while(0)
//旋转操作（传由父亲指向儿子的树根）
#define lcycle(root) cycle(root,l,r)
#define rcycle(root) cycle(root,r,l)
#define lsp(root)							\
	if(rff->l==root->fa){					\
		if(root->fa->l==root) lcycle(rff);	\
		else rcycle(rff->l);				\
		lcycle(rff);						\
	}else{									\
		if(root->fa->r==root) rcycle(rff);	\
		else lcycle(rff->r);				\
		rcycle(rff);						\
	}
//对于三个节点的链的伸展，注意旋转时传父亲指向儿子的指针
#define pos(p) ((p)->fa->l==(p)? (p)->fa->l:(p)->fa->r)
//由原指针获取父亲指向儿子的指针
inline void Splay(register splay* root){
	root->linepush();//完成伸展路径上的标记下传
	while(root->fa)
		if(root->fa->fa)
			if(root->fa->fa->fa){
				register splay*&rff=pos(root->fa->fa);
				lsp(root);
			}else{//如果旋转不是根节点，就一定要改成父亲指向儿子的指针
				register splay* rff=root->fa->fa;
				lsp(root);
			}//否则的话直接传指针就是了
		else if(root->fa->l==root){
			root=root->fa;lcycle(root);
		}else{root=root->fa;rcycle(root);}
         //对于最后两个节点的链，特判
}
```
实现了伸展，就可以实现打通实链的操作了
```cpp
typedef unsigned int word;
word fa[100010];
inline void makeline(word id){
	register splay *root=p+id,*top;
	Splay(root),root->pushdown();
	if(top=root->r){
		while(top->pushdown(),top->l) top=top->l;
		fa[top-p]=root-p,root->r->fa=0;
		*root-=root->r,root->r=0;
	}//首先将待打通节点后的实链截断，换为虚边
	for(top=root;top->l;top=top->l,top->pushdown());
	while(fa[top-p]){//每次跳一条虚边
		register splay* next=p+fa[top-p];
		Splay(next),next->pushdown();
		if(top=next->r){
			while(top->pushdown(),top->l) top=top->l;
			fa[top-p]=next-p,next->r->fa=0;
			*next-=next->r;
		}//将父亲原有的实链截断，换为虚边
		next->r=root,root->fa=next,*next+=root;
      		//然后接上所需的链
		for(top=root=next;top->l;top=top->l,top->pushdown());
	}
}
inline void makeroot(word id){
	makeline(id),Splay(p+id);
	p[id].tag^=1,fa[id]=0;
   	//打通实链后区间翻转即可换根，注意根节点父亲设为0
}
```
完成 LCT 基本操作的构建后，让我们分析各个操作

- 连边：$u$ 置为根后， 将 LCT 上的父亲置为 $v$。
- `+` 打通链之后给链打上加法标记。
- `*` 同上。
- `-` $u_1$ 置为根，若 $u_1,v_1$ 之间为实边，断开；  
$v_1$ 父亲设为 $0$，然后连上 $u_2,v_2$。
- `/` 打通链之后输出结果就是了。

最后开始卡常：

- 注意到只输入非负整数，于是 `fread` 读入实现快读。
- 而且每次询问输入的数据量总大于等于输出  
（一次 `/ u v` 操作输入最少 $6$ 字节（包含空格和回车），输出最多 $6$ 字节（包含回车））  
于是 `fwrite` 实现快输，并与快读共享一个数组
- 常用的局部变量打上 `register`（前文已打上）
- 所有函数打上 `inline`（前文已打上）

最后的快读和主函数：
```cpp
typedef unsigned int word;
typedef unsigned short hword;
typedef unsigned char byte;
char pool[3<<20];
struct READ{//快读和快输
	char *top,*outtop;//输入与输出的指针
	inline READ(){fread(outtop=top=pool,3<<20,1,stdin);}
	inline ~READ(){fwrite(pool,outtop-pool,1,stdout);}
    //fread一次性读入，fwrite一次性输出
	template<typename type>
	inline READ& operator >>(register type& num){
		while('0'>*top||*top>'9') ++top;
		for(num=0;'0'<=*top&&*top<='9';)
			num=num*10+(*(top++)-'0');
		return *this;
	}//读入（仅无符号整数）
	inline void outnum(hword num){//输出（仅 unsigned short）
		if(num) outnum(num/10),*(outtop++)='0'+num%10;}
	template<typename type>
	inline READ& operator <<(register type& num){
		num? outnum(num):void(*(outtop++)='0');
		return *(outtop++)='\n',*this;
	}//对于0特判，输出回车
};
int main(){
	register READ cin;//此cin非彼cin，实现如上
	word n,q;
	cin>>n>>q;
	for(register word u,v;n>1;--n)
		cin>>u>>v,makeroot(u),fa[u]=v;
	for(register word u,v;q;--q){
		while(*cin.top==' '||*cin.top=='\n') ++cin.top;
		register byte opt=*cin.top;//获取操作类别
		if(cin>>u>>v,opt=='/'){//输出
			makeroot(u),makeline(v);
			Splay(p+v),cin<<p[v].sum;
		}else if(opt=='-'){//断边
			makeroot(u),Splay(p+v);
			if(p[v].pushdown(),p[v].l==p+u)
				p[v]-=p+u,p[u].fa=0,p[v].l=0;
			fa[v]=0,cin>>u>>v;
			makeroot(u),fa[u]=v;
		}else if(opt=='+'){//打上加法标记
			makeroot(u),makeline(v);
			Splay(p+v),cin>>u,p[v]+=u;
		}else if(opt=='*'){//打上乘法标记
			makeroot(u),makeline(v);
			Splay(p+v),cin>>u,p[v]*=u;
		}
	}
	return 0;
}
```
最终代码（不开 O2 4.10s，开 O2 2.20s 左右，相当快）
```cpp
#include<stdio.h>
typedef unsigned int	word;
typedef unsigned short hword;
typedef unsigned char	byte;
const hword mod=51061;
struct splay{
	splay *l,*r,*fa;
	hword sum,size;
	hword plustag,multag;
	byte tag;
	inline splay(){sum=size=multag=1;}
	inline void operator +=(register word num){
		sum=(num*size+sum)%mod;
		if((num+=plustag)>=mod) num-=mod;
		plustag=num;
	}//打上加法标记
	inline void operator *=(register word num){
		plustag=num*plustag	%mod;
		multag=	num*multag	%mod;
		sum=	num*sum		%mod;
	}//打上乘法标记
	inline void operator +=(register splay* p){
		register word num=p->sum;
		if((num+=sum)>=mod) num-=mod;
		sum=num,num=p->size;
		if((num+=size)>=mod) num-=mod;
		size=num;
	}//加入儿子时更新size与和
	inline void operator -=(register splay* p){
		register word num=mod-p->sum;
		if((num+=sum)>=mod) num-=mod;
		sum=num,num=mod-p->size;
		if((num+=size)>=mod) num-=mod;
		size=num;
	}//删除儿子时更新size与和
	inline void pushdown(){
		if(tag){
			if(l) l->tag^=1;
			if(r) r->tag^=1;
			register splay* swap=l;
			l=r,r=swap,tag=0;
		}
		if(multag!=1){
			if(l) *l*=multag;
			if(r) *r*=multag;
			multag=1;
		}
		if(plustag){
			if(l) *l+=plustag;
			if(r) *r+=plustag;
			plustag=0;
		}
	}//三种标记下传 
	inline void linepush(){
		if(fa) fa->linepush();
		pushdown();
	}//伸展前的标记下传 
}p[100010];
#define cycle(root,l,r)	do{			\
	register splay* rt=root;		\
	register splay* l=rt->l;		\
	register splay* l##r=l->r;		\
	l->fa=rt->fa,(root)=l;			\
	l->r=rt,rt->fa=l; 				\
	*rt-=l,*l+=rt,rt->l=l##r;		\
	if(l##r) *rt+=l##r,l##r->fa=rt;	\
}while(0)
//旋转操作（传由父亲指向儿子的树根）
#define lcycle(root) cycle(root,l,r)
#define rcycle(root) cycle(root,r,l)
#define lsp(root)							\
	if(rff->l==root->fa){					\
		if(root->fa->l==root) lcycle(rff);	\
		else rcycle(rff->l);				\
		lcycle(rff);						\
	}else{									\
		if(root->fa->r==root) rcycle(rff);	\
		else lcycle(rff->r);				\
		rcycle(rff);						\
	}
//对于三个节点的链的伸展，注意旋转时传父亲指向儿子的指针
#define pos(p) ((p)->fa->l==(p)? (p)->fa->l:(p)->fa->r)
//由原指针获取父亲指向儿子的指针
inline void Splay(register splay* root){
	root->linepush();//完成伸展路径上的标记下传
	while(root->fa)
		if(root->fa->fa)
			if(root->fa->fa->fa){
				register splay*&rff=pos(root->fa->fa);
				lsp(root);
			}else{//如果旋转不是根节点，就一定要改成父亲指向儿子的指针
				register splay* rff=root->fa->fa;
				lsp(root);
			}//否则的话直接传指针就是了
		else if(root->fa->l==root){
			root=root->fa;lcycle(root);
		}else{root=root->fa;rcycle(root);}
         //对于最后两个节点的链，特判
}
word fa[100010];
inline void makeline(word id){
	register splay *root=p+id,*top;
	Splay(root),root->pushdown();
	if(top=root->r){
		while(top->pushdown(),top->l) top=top->l;
		fa[top-p]=root-p,root->r->fa=0;
		*root-=root->r,root->r=0;
	}//首先将待打通节点后的实链截断，换为虚边
	for(top=root;top->l;top=top->l,top->pushdown());
	while(fa[top-p]){//每次跳一条虚边
		register splay* next=p+fa[top-p];
		Splay(next),next->pushdown();
		if(top=next->r){
			while(top->pushdown(),top->l) top=top->l;
			fa[top-p]=next-p,next->r->fa=0;
			*next-=next->r;
		}//将父亲原有的实链截断，换为虚边
		next->r=root,root->fa=next,*next+=root;
      		//然后接上所需的链
		for(top=root=next;top->l;top=top->l,top->pushdown());
	}
}
inline void makeroot(word id){
	makeline(id),Splay(p+id);
	p[id].tag^=1,fa[id]=0;
   	//打通实链后区间翻转即可换根，注意根节点父亲设为0
}
char pool[3<<20];
struct READ{//快读和快输
	char *top,*outtop;//输入与输出的指针
	inline READ(){fread(outtop=top=pool,3<<20,1,stdin);}
	inline ~READ(){fwrite(pool,outtop-pool,1,stdout);}
    //fread一次性读入，fwrite一次性输出
	template<typename type>
	inline READ& operator >>(register type& num){
		while('0'>*top||*top>'9') ++top;
		for(num=0;'0'<=*top&&*top<='9';)
			num=num*10+(*(top++)-'0');
		return *this;
	}//读入（仅无符号整数）
	inline void outnum(hword num){//输出（仅 unsigned short）
		if(num) outnum(num/10),*(outtop++)='0'+num%10;}
	template<typename type>
	inline READ& operator <<(register type& num){
		num? outnum(num):void(*(outtop++)='0');
		return *(outtop++)='\n',*this;
	}//对于0特判，输出回车
};
int main(){
	register READ cin;//此cin非彼cin，实现如上
	word n,q;
	cin>>n>>q;
	for(register word u,v;n>1;--n)
		cin>>u>>v,makeroot(u),fa[u]=v;
	for(register word u,v;q;--q){
		while(*cin.top==' '||*cin.top=='\n') ++cin.top;
		register byte opt=*cin.top;//获取操作类别
		if(cin>>u>>v,opt=='/'){//输出
			makeroot(u),makeline(v);
			Splay(p+v),cin<<p[v].sum;
		}else if(opt=='-'){//断边
			makeroot(u),Splay(p+v);
			if(p[v].pushdown(),p[v].l==p+u)
				p[v]-=p+u,p[u].fa=0,p[v].l=0;
			fa[v]=0,cin>>u>>v;
			makeroot(u),fa[u]=v;
		}else if(opt=='+'){//打上加法标记
			makeroot(u),makeline(v);
			Splay(p+v),cin>>u,p[v]+=u;
		}else if(opt=='*'){//打上乘法标记
			makeroot(u),makeline(v);
			Splay(p+v),cin>>u,p[v]*=u;
		}
	}
	return 0;
}
```

---

## 作者：GoldenPotato137 (赞：2)

[戳我获得更好的阅读体验qwq](https://www.goldenpotato.cn/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/luogu-p1501-%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9Ftree-ii/)

---
# Solution
这是一道肥肠考验LCT基本功的一道题。

口胡起来是很容易的：**对于每一个加/乘操作，我们把对应的链split出来，然后打标记即可；Link/Cut是基本操作；查询的话我们也是把对应的链split出来，然后直接输出根的sum即可**。
这里的打标记和线段树II那道题非常像，~~不会的同学可以先去做线段树II~~。 ~~都在写LCT了，怎么可能没打过线段树II~~。我们只需要像线段树II那样pushdown并处理sum即可。


**口胡是口胡，打起来就是另外一码事了**

这里列出我写出的锅，大家写的时候可以考虑注意以下几点：
1. $(5w*5w)$会爆int的，请开longlong 。
2. 我们在$pushdown$算各种标记、sum的时候一定要注意膜$p$，小心爆longlong。
3. LCT的rotate和正常的splay的rotate不一样，我们要特判一下z是否是另外一颗splay的，不能直接无脑rotate。~~当然，这种锅也只有我这种蒟蒻才会错~~
4. 先cut再link，避免连出环来。
5. ~~没了~~

---
# Code
### 数据生成器
[在这里](https://www.goldenpotato.cn/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84/luogu-p1501-%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9Ftree-ii/)
### 正解
```cpp
//Luogu P1501 [国家集训队]Tree II 
//Mar,10th,2019
//LCT+线段树II
#include<iostream>
#include<cstdio>
long long read()
{
	long long x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-') f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-'0';c=getchar();}
	return x*f;
}
using namespace std;
const int N=100000+1000;
const long long poi=51061;
struct LCT
{
	long long son[N][2],fa[N],w[N],sum[N],plus[N],take[N],lazy[N],size[N];
	inline void Mirror(int x)
	{
		lazy[x]=!lazy[x];
		swap(son[x][0],son[x][1]);
	}
	inline void pushdown(int x)
	{
		if(lazy[x]==true)
		{
			Mirror(son[x][0]);
			Mirror(son[x][1]);
			lazy[x]=false;
		}
		if(son[x][0]!=0)
		{
			w[son[x][0]]=(w[son[x][0]]*take[x]+plus[x])%poi;
			take[son[x][0]]=take[son[x][0]]*take[x]%poi;
			plus[son[x][0]]=(plus[son[x][0]]*take[x]+plus[x])%poi;
			sum[son[x][0]]=(sum[son[x][0]]*take[x]+size[son[x][0]]*plus[x])%poi;
		}
		if(son[x][1]!=0)
		{
			w[son[x][1]]=(w[son[x][1]]*take[x]+plus[x])%poi;
			take[son[x][1]]=(take[son[x][1]]*take[x])%poi;
			plus[son[x][1]]=(plus[son[x][1]]*take[x]+plus[x])%poi;
			sum[son[x][1]]=(sum[son[x][1]]*take[x]+size[son[x][1]]*plus[x])%poi;
		}
		plus[x]=0,take[x]=1;
	}
	inline void update(int x)
	{
		size[0]=sum[0]=0;
		sum[x]=(sum[son[x][0]]+sum[son[x][1]]+w[x])%poi;
		size[x]=(size[son[x][0]]+size[son[x][1]]+1);
	}
	inline void rotate(int x,int type)
	{
		int y=fa[x],z=fa[y];
		fa[x]=z;
		if(IsRoot(y)==false)
			son[z][y==son[z][1]]=x;
		fa[son[x][type]]=y,son[y][!type]=son[x][type];
		fa[y]=x,son[x][type]=y;
		update(y),update(x);
	}
	bool IsRoot(int x)
	{
		return (x!=son[fa[x]][0] and x!=son[fa[x]][1]);
	}
	int mstack[N],top;
	void splay(int x)
	{
		mstack[top=1]=x;
		for(int now=x;IsRoot(now)==false;now=fa[now])
			mstack[++top]=fa[now];
		for(;top>0;top--)
			pushdown(mstack[top]);
		while(IsRoot(x)==false)
		{
			if(IsRoot(fa[x])==false and x==son[fa[x]][fa[x]==son[fa[fa[x]]][1]])
				rotate(fa[x],x==son[fa[x]][0]),
				rotate(x,x==son[fa[x]][0]);
			else
				rotate(x,x==son[fa[x]][0]);
		}
	}
	void Access(int x)
	{
		for(int t=0;x!=0;t=x,x=fa[x])
			splay(x),son[x][1]=t,fa[t]=x,update(x);
	}
	int GetRoot(int x)
	{
		Access(x),splay(x);
		while(son[x][0]!=0)
            pushdown(x),x=son[x][0];
		splay(x);
        return x;
	}
	void MakeRoot(int x)
	{
		Access(x);
		splay(x);
		Mirror(x);
	}
	void Link(int x,int y)
	{
		if(GetRoot(x)==GetRoot(y)) return;
		MakeRoot(x);
		fa[x]=y;
	}
	void Split(int x,int y)
	{
		MakeRoot(y);
		Access(x),splay(x);
	}
	void Cut(int x,int y)
	{
		Split(x,y);
		if(y!=son[x][0] or fa[y]!=x) return;
		son[x][0]=0,fa[y]=0;
		update(x);
	}
	void Add(int x,int y,long long num)
	{
		Split(x,y);
		plus[x]=num%poi,w[x]=(w[x]+num)%poi,sum[x]=(sum[x]+size[x]*num)%poi;
	}
	void Take(int x,int y,long long num)
	{
		Split(x,y);
		take[x]=num%poi,w[x]=(w[x]*num)%poi,sum[x]=sum[x]*num%poi;
	}
	long long Query(int x,int y)
	{
		Split(x,y);
		return sum[x]%poi;
	}
}lct;
int n,q;
int main()
{
	n=read(),q=read();
	for(int i=1;i<=n;i++)
		lct.take[i]=lct.w[i]=lct.sum[i]=lct.size[i]=1;
	for(int i=1;i<n;i++)
	{
		int s=read(),t=read();
		lct.Link(s,t);
	}
	
	char OP[5];
	for(int i=1;i<=q;i++)
	{
		scanf("%s",OP+1);
		if(OP[1]=='+')
		{
			long long u=read(),v=read(),x=read()%poi;
			lct.Add(u,v,x);
		}
		else if(OP[1]=='-')
		{
			long long u1=read(),v1=read(),u2=read(),v2=read();
			lct.Cut(u1,v1);
			lct.Link(u2,v2);
		}
		else if(OP[1]=='*')
		{
			long long u=read(),v=read(),x=read()%poi;
			lct.Take(u,v,x);
		}
		else
		{
			long long u=read(),v=read();
			printf("%lld\n",lct.Query(u,v));
		}
	}
	return 0;
}

```

---

## 作者：Regimes (赞：2)

[国家集训队]Tree II

其实看得出来，LCT板板，但这和别的还是有一些细微的区别，每次修改，

查询，都先Split(x , y) 让之前的标记往下传，并拉出一条链，但是要注意的

是，每一次必须把add ，mul，和 sum 一起改掉。当时我一直没有搞懂为什么

sum标记也要一起改（太菜了），因为我认为每次pushup都会对sum进行修改

（更菜了） 

好的，那么我们来看一个例子

![](https://i.loli.net/2019/03/24/5c96d34edd1fd.png)

(蒟蒻手绘，不要太建议)

上图，是一个非常美妙的一棵splay，如果我们假设3求出了sum，接着，

我们打算 splay 4 ，如果你不给3打一个sum标记，当更新2的值时

（pushup 2）就会出错了

可能蒟蒻分析的不太对，如还有问题，可以私信Mital巨佬，或者私信菜菜

Skounputer


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std ;
#define ls ch[x][0]
#define rs ch[x][1]
#define N 100007
#define Mod 51061
#define int long long
int lazy[N] , turn[N] , ch[N][2] , sum[N] , df[N] , mul[N] , fa[N] , st[N] , siz[N] ;
int n , q ;
inline int read()
{
    int x = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
void pushr(int x)
{
    swap( ls , rs ) ;
    turn[x] ^= 1 ; return ;
}
void pushup(int x)
{
    siz[x] = 1 ;
    sum[x] = df[x] ;
    if( ls ) ( sum[x] += sum[ls] ) %= Mod , siz[x] += siz[ls] ;
    if( rs ) ( sum[x] += sum[rs] ) %= Mod , siz[x] += siz[rs] ;
}
void push(int x) {swap(ch[x][0], ch[x][1]), turn[x] ^= 1;}
void push1(int u, int v)
{
    sum[u] = (sum[u] + v * siz[u] % Mod) % Mod;
    lazy[u] = ( lazy[u] + v ) % Mod, df[u] = ( df[u] + v ) % Mod;
}
void push2(int u, int v)
{
    sum[u] = sum[u] * v % Mod;
    df[u] = df[u] * v % Mod;
    lazy[u] = lazy[u] * v % Mod, mul[u] = mul[u] * v % Mod;
}
void pushdown(int x)
{
    if( mul[x] != 1 ) push2( ch[x][0] ,  mul[x] ) , push2( ch[x][1] ,  mul[x] ), mul[x] = 1 ;
    if( lazy[x] ) push1( ch[x][0] , lazy[x] ), push1( ch[x][1] , lazy[x] ) , lazy[x] = 0 ;
    if( turn[x] ) push( ch[x][0] ) , push( ch[x][1] ), turn[x] = 0 ;
}
int nroot(int x)
{
    return ch[fa[x]][1] == x || ch[fa[x]][0] == x ;
}
int Get(int x)
{
    return ch[fa[x]][1] == x ;
}
void rotate(int x)
{
    int boss = fa[x] , gradboss = fa[boss] , w = Get(x) ;
    if( nroot(boss) ) ch[gradboss][ch[gradboss][1] == boss] = x ;
    ch[boss][w] = ch[x][w^1] ;
    if( ch[x][w^1] ) fa[ch[x][w^1]] = boss ;
    ch[x][w^1] = boss ; fa[boss] = x ;
    fa[x] = gradboss ;
    pushup(boss) ;
}
void splay(int x)
{
    int y = x , top = 0 ;
    st[++top] = y ;
    while( nroot(y) ) st[++top] = y = fa[y] ;
    while( top ) pushdown( st[top--] ) ;
    while( nroot(x) ){
        y=fa[x];int z=fa[y];
        if(nroot(y))
            if( Get(x) == Get(y) ) rotate(y) ;
            else rotate(x) ; 
        rotate(x);
    }
    pushup(x) ;
}
void access(int x){
    for(int y = 0 ; x ; x = fa[y=x] )
        splay(x) , rs = y , pushup(x) ;
}
void makeroot(int x){
    access(x) ; splay(x) ;
    pushr(x) ;
}
int findroot(int x)
{
    access(x) ; splay(x) ;
    while( ls ) pushdown(x) , x = ls ;
    splay(x) ;
    return x ;
}
void split(int x , int y)
{
    makeroot(x) ;
    access(y) ; splay(y) ;
}
void link(int x , int y ){
    makeroot(x) ;
    if( findroot(y) !=x ) fa[x] = y ;
}
void cut(int x , int y){
    makeroot(x) ;
    if( findroot(y) == x && fa[y] == x && !ch[y][0] ){
        fa[y] = ch[x][1] = 0 ;
        pushup(x) ;
    }
}
signed main()
{
    //freopen("output.out","r" , stdin ) ;
    scanf("%lld%lld" , &n , &q ) ;
    for(int i = 1 ; i <= n ; i++ ) mul[i] = df[i] =  1 ; 
    for(int i = 1 ; i <= n - 1 ; i++ ){
        int u = read() , v = read() ;
        link( u , v ) ;
    }
   // cout<<"ok"<<endl;
    while( q-- )
    {
       // cout<<"ok1"<<endl;
        char s[5] ;
        scanf("%s" , s ) ;
        int x , y , z ;
        if( s[0] == '+' ){
            x = read() ; y = read() ; z = read() ;
            split( x , y ) ;
            push1( y , z ) ;
        }
        else
        if( s[0] == '-' ){
            int u , v ;
            x = read() ; y = read() ; u = read() ; v = read() ;
            cut( x , y ) ; link( u , v ) ;
        }
        else
        if( s[0] == '/' ){
            x = read() ; y = read() ;
            split( x , y ) ;
            printf("%lld\n" , sum[y] ) ;
        }
        else{
            x = read() ; y = read() ; z = read() ;
            split( x , y ) ; 
            push2( y , z ) ;
        }
        /*for(int i = 1 ; i <= n ; i++ ){
                printf("df[%d] = %d\n" , i , df[i] ) ;
        }
        for(int i = 1 ; i <= n ; i++ ){
                printf("mul[%d] = %d\n" , i , mul[i] ) ;
        }*/
    }
    return 0 ;
}
```




---

## 作者：wrpwrp (赞：1)

# Link-Cut-Tree 小结  

## 支持的操作
+ 连边，断边
+ 换根
+ 查询链上信息
+ 维护子树信息 ~~（我不会~~

## 主要思想/性质
把一棵树分成很多条链（初始的时候都是点），每一条链都是一个Splay，然后来进行维护。  
+ 每个Splay的中序遍历的点的深度必定是严格递增的，它维护的是从上到下深度严格递增的一排点。
+ 每个点都恰好被一个Splay包含
+ 在一个Splay内的点之间的边是实边，不在的为虚边。
+ 在原来的树中，每个点只能向一个儿子连一条实边（因为性质二）。在我们需要修改的时候需要用到这一点。
 
## 操作
### $access(x)$
**这个操作让我们打通从根节点，到$x$这个点的一条实路径，且让$x$成为这个路径上最深的点（也就是说没有在$x$下面的了）**  

(借一下图）  

![avatar](https://images2017.cnblogs.com/blog/1309909/201801/1309909-20180123095924037-1618037447.png)  

假设一开始的划分是这个样子的，我们想要打通一条从根节点$A$到$N$的路径。那么，每个点到这条路以外的实边要变成虚边，这条路上的虚边要变成实边。  
所以先把$N$转到所在Splay的根，然后丢下右边的子树，也就是这里的O点，因为那些是不在$A->N$这条路上的，同时由于儿子发生变化，要更新这里Splay的信息。然后去对$N$的父亲做相同的操作，然后把他的父亲的右边的子树置为$x$因为比它深的实链上的点就是$x$为根的这颗子树上的实链。  
**步骤**：  
+ 旋转到根
+ 置换右儿子
+ 更新信息
+ 记录当前点，当前点置换为父节点

``` cpp
inline void access(int x)
{
	for(R int y=0;x;x=fa[y=x])
		splay(x),rs(x)=y,pushup(x);
}
``` 
按照上图的过程模拟就直接see一下[FlashHu巨佬的博客](https://www.cnblogs.com/flashhu/p/8324551.html)。 
  
### $makeroot(x)$
由于Splay只能维护从上到下深度递增的路径，所以只有$access$是不行的，因为有时候要访问如上图$E->G$的路径，所以还要换根。由于$access(x)$后x会是这条链上最深的点，那么翻转的话就会变成最浅的点，由于原本最浅的点是原来的树的根（注意我说的不是Splay），所以翻转之后，原来的树的根就会变成$x$。
``` cpp
inline void makeroot(int x)
{
	access(x);splay(x);
	pushr(x);
}
```
~~好短啊~~

### $findroot(x)$
打通到$x$的路，然后求这条实链上深度最浅的点，也就是在Splay上往左儿子走就行了。记得找到了之后要$splay(x)$来还原根，一般错得就少。

``` cpp
inline int findroot(int x)
{
	access(x);splay(x);
	while(ls(x)) pushdown(x),x=ls(x);
	splay(x);
	return x;
}
```

### $split(x,y)$
提取从$x$到$y$的路径。直接把$x$搞成根，然后打通到y就行了。同时$splay(y)$让这条链上的信息全部存储到y上。

``` cpp
inline void split(int x,int y)
{
	makeroot(x);
	access(y);splay(y);
}
```

### $link(x,y)$
``` cpp
inline void link(int x,int y)
{
	makeroot(x);
	if(findroot(y)!=x) fa[x]=y;
}
```

### $cut(x,y)$
先把$x$置为根，然后看$y$是否和$x$在一棵树里，然后它的父节点是不是$x$,还有它是否有左子节点。因为如果它有左子节点，它就会和$x$之间不直接连边，从而也不可以断开。

``` cpp
inline void cut(int x,int y)
{
	makeroot(x);
	if(findroot(y)==x&&fa[y]==x&&ls(y)==0)
	{
		fa[y]=ch[x][1]=0;
		pushup(x);
	}
}
```

## luogu1501模板题代码
``` cpp
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define R register
#define int unsigned int
const int MAXN=1e5+10;
const int mod=51061;

#define ls(x) ch[x][0]
#define rs(x) ch[x][1]

int rev[MAXN],siz[MAXN],fa[MAXN],ch[MAXN][2];
int sum[MAXN],plu[MAXN],rid[MAXN],val[MAXN];

inline void pushup(int x)
{
	siz[x]=siz[ls(x)]+siz[rs(x)]+1;
	sum[x]=(sum[ls(x)]+sum[rs(x)]+val[x])%mod;
}

inline void pushr(int x)
{
	swap(ls(x),rs(x));
	rev[x]^=1;
}

inline void add(int &x,int y)
{
	x+=y;x%=mod;
}

inline void mul(int &x,int y)
{
	x*=y;x%=mod;
}

inline void pushp(int x,int c)
{
	add(sum[x],c*siz[x]);
	add(val[x],c);
	add(plu[x],c);
}

inline void pushm(int x,int c)
{
	mul(sum[x],c);
	mul(val[x],c);
	mul(rid[x],c);
	mul(plu[x],c);
}

inline void pushdown(int x)
{
	if(rid[x]!=1)
		pushm(ls(x),rid[x]),pushm(rs(x),rid[x]),rid[x]=1;
	if(plu[x])
		pushp(ls(x),plu[x]),pushp(rs(x),plu[x]),plu[x]=0;
	if(rev[x])
	{
		if(ls(x)) pushr(ls(x));
		if(rs(x)) pushr(rs(x));
		rev[x]=0;
	}	
}

inline int nroot(int x)
{
	return ch[fa[x]][0]==x||ch[fa[x]][1]==x;
}

inline void rotate(int x)
{
	int y=fa[x],z=fa[y];
	int k=ch[y][1]==x;
	int w=ch[x][!k];
	if(nroot(y))
		ch[z][ch[z][1]==y]=x;
	ch[x][!k]=y;ch[y][k]=w;
	if(w) fa[w]=y;
	fa[y]=x;fa[x]=z;
	pushup(y);
}

inline void pushall(int x)
{
	if(nroot(x)) pushall(fa[x]);
	pushdown(x);
}

inline void splay(int x)
{
	int y=x,z=0;
	pushall(x);
	while(nroot(x))
	{
		y=fa[x],z=fa[y];
		if(nroot(y))
			rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
		rotate(x);
	}
	pushup(x);
}

inline void access(int x)
{
	for(R int y=0;x;x=fa[y=x])
		splay(x),rs(x)=y,pushup(x);
}

inline void makeroot(int x)
{
	access(x);splay(x);
	pushr(x);
}

inline int findroot(int x)
{
	access(x);splay(x);
	while(ls(x)) pushdown(x),x=ls(x);
	splay(x);
	return x;
}

inline void split(int x,int y)
{
	makeroot(x);
	access(y);splay(y);
}

inline void link(int x,int y)
{
	makeroot(x);
	if(findroot(y)!=x) fa[x]=y;
}

inline void cut(int x,int y)
{
	makeroot(x);
	if(findroot(y)==x&&fa[y]==x&&ls(y)==0)
	{
		fa[y]=ch[x][1]=0;
		pushup(x);
	}
}

inline void Add(int x,int y,int c)
{
	split(x,y);
	pushp(y,c);
}

inline void Mul(int x,int y,int c)
{
	split(x,y);
	pushm(y,c);
}

inline void Ask(int x,int y)
{
	split(x,y);
	printf("%d\n",sum[y]);
}

signed main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	for(R int i=1;i<=n;i++)
		siz[i]=rid[i]=val[i]=1;
	for(R int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		link(a,b);
	}
	while(q--)
	{
		char op[2];
		scanf("%s",op);
		if(op[0]=='+')
		{
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			Add(u,v,c);
		}
		if(op[0]=='-')
		{
			int a,b,c,d;
			scanf("%d%d%d%d",&a,&b,&c,&d);
			cut(a,b);
			link(c,d);
		}
		if(op[0]=='*')
		{
			int u,v,c;
			scanf("%d%d%d",&u,&v,&c);
			Mul(u,v,c);
		}
		if(op[0]=='/')
		{
			int u,v;
			scanf("%d%d",&u,&v);
			Ask(u,v);
		}
	}
	return 0;
}
```

---

