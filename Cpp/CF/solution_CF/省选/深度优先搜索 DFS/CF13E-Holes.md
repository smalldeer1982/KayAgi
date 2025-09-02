# Holes

## 题目描述

Little Petya likes to play a lot. Most of all he likes to play a game «Holes». This is a game for one person with following rules:

There are $ N $ holes located in a single row and numbered from left to right with numbers from 1 to $ N $ . Each hole has it's own power (hole number $ i $ has the power $ a_{i} $ ). If you throw a ball into hole $ i $ it will immediately jump to hole $ i+a_{i} $ , then it will jump out of it and so on. If there is no hole with such number, the ball will just jump out of the row. On each of the $ M $ moves the player can perform one of two actions:

- Set the power of the hole $ a $ to value $ b $ .
- Throw a ball into the hole $ a $ and count the number of jumps of a ball before it jump out of the row and also write down the number of the hole from which it jumped out just before leaving the row.

Petya is not good at math, so, as you have already guessed, you are to perform all computations.

## 样例 #1

### 输入

```
8 5
1 1 1 1 1 2 8 2
1 1
0 1 3
1 1
0 3 4
1 2
```

### 输出

```
8 7
8 5
7 3
```

# 题解

## 作者：FourteenObsidian (赞：8)

此题做法与[弹飞绵羊](https://www.luogu.com.cn/problem/P3203)做法基本一致。~~双倍经验！~~

考虑用分块处理。

令$pla[i]$为小球在第$i$个洞时会被弹到的洞的编号，$num[i]$为球在第$i$个洞弹出这个洞所在的块所弹的次数。

块大小为$\sqrt n$

预处理复杂度为$O(n\sqrt n)$，修改和查询的复杂度均为$O(\sqrt n)$

总复杂度为$O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200001;
int n,c,m,a[N],bl[N],st[N],ed[N],pla[N],num[N],siz[N],ans1,ans2;
inline int get(){//快读
    char ch=getchar();
	int sum=0,fl=1;
    while(ch<'0'||ch>'9'){
        ch=getchar();
        if(ch=='-') 
			fl=-1;
	}
    while(ch>='0'&&ch<='9')
        sum*=10,sum+=ch-'0',ch=getchar();
    return sum*fl;
}
inline void build(){//分块
    int sum=sqrt(n);
    for(register int i=1;i<=sum;++i)
        st[i]=(n/sum)*(i-1)+1,ed[i]=(n/sum)*i;
    ed[sum]=n;
    for(register int i=1;i<=sum;++i){
        for(register int j=st[i];j<=ed[i];++j)
            bl[j]=i;	 
    }
    for(register int i=1;i<=sum;++i)
		for(register int j=ed[i];j>=st[i];--j){
			if(a[j]+j>ed[i])
				num[j]=1,pla[j]=a[j]+j;
			else	
				num[j]=num[j+a[j]]+1,pla[j]=pla[j+a[j]];//预处理
		}
    return;   
}
inline void ask(int x){//查询
	int tim=0;
   	for(register int i=x;i<=n;i=pla[i])
   		tim+=num[i],ans1=i;
   	for(register int i=ans1;i<=n;i+=a[i]){
   		if(i+a[i]>n)
   			ans1=i;
	   }	
   	ans2=tim;
}
inline void modify(int x,int y){ //修改
	a[x]=y;
	int blx=bl[x];
	for(register int i=x;i>=st[blx];--i){
		if(a[i]+i>ed[blx])
			num[i]=1,pla[i]=a[i]+i;
		else	
			num[i]=num[i+a[i]]+1,pla[i]=pla[i+a[i]];
	}
	return;
}
int main(){
	n=get(),m=get();
    for(register int i=1;i<=n;++i)
        a[i]=get();
    build();//分块
	int op,p,q,ans=0;
    while(m--){
        op=get(),p=get();
        if(op==1){
			ask(p);
        	printf("%d %d\n",ans1,ans2);	//输出答案
		}
        	
		else
			q=get(),modify(p,q); 
	}
    return 0;
}
```

---

## 作者：于丰林 (赞：6)

其实这道题和弹飞绵羊区别并不大，同样也是利用分块来解决，只不过还要求离开前的最后位置。我们还是简单的理顺一下这道题的思路吧：

思路其实很简单，我们将整个序列分成若干个块（块的大小取决于数据，但是我们一般都会默认为√n），对于每一块的每一个点我们只要维护他弹出这个块还需几步和弹出之后会到达哪一个点即可。

关于修改，由于每一个块之间都是相互独立的，所以单点修改只需要维护每一个块就可以了，并且由于每一个点的数据都建立在他后面块的基础上，所以我们对于每一个块都需要倒着来进行维护。

而对于查询次数我们只要循着每一个点的指向，累加每一个点的sum值，大于n的时候跳出即可。

可是如果要查询位置呢？

这里就隐藏着一个巨大的坑点：由于每一个点记录的只是弹出这个方块所到达的位置，所以求得的最终位置并不是实际的位置，还要再往后找一遍（就在一个块内，时间复杂度可以忽略）就完事了！

最后，附上本题代码：

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct pot
{
    int to,k,conti,sum;
}p[100005];
int size,cnt=1,n,ac,ans;
void change(int ct)
{
    //printf("%d\n",size);
    for(int j=min(ct*size,n);j>(ct-1)*size;j--)
    {
        if(j + p[j].k > ct * size || j + p[j].k > n) p[j].sum = 1,p[j].to = j + p[j].k;
        else
        {
            p[j].to=p[j+p[j].k].to;
            p[j].sum=p[j+p[j].k].sum + 1;
        }
        //printf("%d\n",p[j].to);
    }
}
void query(int y)
{
    ans=0;
    while(y<=n)
    {
        ans+=p[y].sum;
        //printf("%d\n",ans);
        if(p[y].to>n) ac=y;
        y=p[y].to;
    }
    while(ac+p[ac].k<=n)
    {
        ac+=p[ac].k;
    }
}
int main()
{
    int temp = 0,m;
    scanf("%d%d",&n,&m);
    size=sqrt(n);
    for(int i=1;i<=n;i++)
    {
        temp++;
        if(temp>size)
        {
            cnt++;
            temp=1;
        }
        scanf("%d",&p[i].k);
        p[i].conti=cnt;
    }
    //if(temp != 0) cnt++;
    //printf("%d\n",cnt);
    for(int i=cnt;i >= 1;i--)
        change(i);
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        scanf("%d%d",&x,&y);
        if(x==0)
        {
            scanf("%d",&z);
            p[y].k=z;
            //printf("%d\n",p[y].k); 
            change(p[y].conti);
        } 
        else
        {
            query(y);
            printf("%d %d\n",ac,ans);
        }
    }
    return 0;
}
```

---

## 作者：lhm_ (赞：4)

这个题和$P3203\ $弹飞绵羊基本上完全一致

我的做法是用$LCT$维护信息，开一个节点$fly$，表示到此节点时，小球会弹飞，那么查询弹多少次即为$siz[fly]-1$

最后一次落在哪个洞可以用维护链上最大值来解决

一些小细节看代码就行了

$code:$
```cpp
#include<bits/stdc++.h>
#define maxn 400010
using namespace std;
template<typename T> inline void read(T &x)
{
	x=0;char c=getchar();bool flag=false;
	while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	if(flag)x=-x;
}
int n,m,flag,root,tot,fly;
int p[maxn],fa[maxn],ch[maxn][2],siz[maxn],ma[maxn],rev[maxn];
bool check(int x)
{
	return ch[fa[x]][1]==x;
}
void pushr(int x)
{
	rev[x]^=1;swap(ch[x][0],ch[x][1]);
}
void pushup(int x)
{
	siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
	if(x!=fly) ma[x]=max(x,max(ma[ch[x][0]],ma[ch[x][1]]));
	else ma[x]=max(ma[ch[x][0]],ma[ch[x][1]]);
}
void pushdown(int x)
{
	if(!rev[x]) return;
	pushr(ch[x][0]),pushr(ch[x][1]);
	rev[x]=0;
}
bool notroot(int x)
{
	return ch[fa[x]][0]==x||ch[fa[x]][1]==x;
}
void rotate(int x)
{
	int y=fa[x],z=fa[y],k=check(x),w=ch[x][k^1];
	if(notroot(y)) ch[z][check(y)]=x;
	fa[x]=z;
	ch[y][k]=w;
	if(w) fa[w]=y;
	ch[x][k^1]=y;
	fa[y]=x;
	pushup(y);
}
void all(int x)
{
	if(notroot(x)) all(fa[x]);
	pushdown(x);
}
void splay(int x)
{
	all(x);
	for(int y;notroot(x);rotate(x))
		if(notroot(y=fa[x]))
			rotate(check(x)^check(y)?x:y);
	pushup(x);
}
void access(int x)
{
	for(int y=0;x;y=x,x=fa[x])
		splay(x),ch[x][1]=y;
}
void makeroot(int x)
{
	access(x),splay(x),pushr(x);
}
void split(int x,int y)
{
	makeroot(x),access(y),splay(y);
}
void link(int x,int y)
{
	split(x,y),fa[x]=y;
}
void cut(int x,int y)
{
	split(x,y),fa[x]=ch[y][0]=0;
}
int main()
{
	read(n),read(m);
	fly=n+1;
	for(int i=1;i<=n;++i)
	{
		read(p[i]);
		if(i+p[i]<=n) link(i,i+p[i]);
		else link(i,fly);
	}
	while(m--)
	{
		int x,y;
		read(flag);
		if(flag)
		{
			read(x);
			split(x,fly);
			printf("%d %d\n",ma[fly],siz[fly]-1);
		}
		else
		{
			read(x),read(y);
			if(x+p[x]<=n) cut(x,x+p[x]);
			else cut(x,fly);
			p[x]=y;
			if(x+p[x]<=n) link(x,x+p[x]);
			else link(x,fly);
		}
	}
	return 0;
}
```

---

## 作者：feicheng (赞：3)

## Description：

>有 $N$ 个洞，每个洞有相应的弹力，能把这个球弹到 $i+power[i]$ 位置。当球的位置 $>N$ 时即视为被弹出。

>有两种操作：

>1. 修改某个点的弹力值。

>2. 询一个球从某点几次能够弹出，弹出前的最后一个位置是哪里。


------------
## Solution
考虑分块，对于每个点，记录其弹几次能够弹出其所在块，记作$cnt_i$，弹出其所在块前的最后一个位置，记作$ls_i$，弹出其所在块后的位置，记作 $to_i$。

记块长为 $s$，
由于修改操作只会影响一个块内的答案，所以可以在 $\Theta(s)$ 的时间里完成修改，又一个球最多跳块数次就可以跳出，所以可以在 $\Theta(\frac n s)$ 的时间完成查询，取 $s=\sqrt n$ 可取得最优解，总复杂度 $\Theta(n\sqrt n)$。

[双倍经验](https://www.luogu.com.cn/problem/P3203)。

------------
## Code
```cpp
/*If you are full of hope,you will be invincible*/
#include <ctime>
#include <cstdio>
#include <random>
#include <cstring>
#include <iostream>
#include <algorithm>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define ri register int
typedef long long ll;
std::mt19937 hpy(time(nullptr)+(unsigned long long)(new char));
namespace IO{
	constexpr int HL=1<<20;
	char buf[HL],*t1=buf,*t2=buf;
	#ifndef ONLINE_JUDGE
	#define getc() getchar()
	#else
	#define getc() t1==t2&&(t2=(t1=buf)+fread(buf,1,HL,stdin),t1==t2)?EOF:*t1++
	#endif
	inline int read(){static int an,f;an = 0,f = 1;static char ch;ch=getc();
	while(!isdigit(ch))ch=='-'?f=-1:1,ch=getc();
	while(isdigit(ch))an=(an<<3)+(an<<1)+(ch^48),ch=getc();
	return an*f;}
	char buff[HL],*T=buff;
	void flush(){fwrite(buff,1,T-buff,stdout);T=buff;}
	inline void putc(char ch){if(T==buff+HL)flush();*T++=ch;}
	template<typename Tp>
	inline void print(Tp x){if(x<0)putc('-'),x=-x;if(!x)return putc('0'),void();
	static int st[20],tp;while(x)st[++tp]=x%10,x/=10;while(tp)putc(st[tp]^48),--tp;}
}
using IO::read;
using IO::print;
using IO::putc;
constexpr int inf = 0x3f3f3f3f,N = 1e5 + 10,M = sqrt(N) + 10;
int a[N],to[N],bl[N],L[M],R[M],cnt[N],la[N],n,m,siz,tot;
inline int pos(int x){return (x-1)/siz+1;}
inline void Init() {
    n=read(),m=read(),siz=sqrt(n),tot=pos(n);
    for(ri i=1;i<=n;++i) a[i]=read(),bl[i]=pos(i);
    for(ri i=1;i<=tot;++i) L[i] = R[i-1]+1,R[i]=i*siz;
    R[tot] = n;
    for(ri i=n;i>=1;--i) {
        if(i+a[i] > R[bl[i]]) 
            cnt[i] = 1,to[i] = i + a[i],la[i]=i;
        else 
            cnt[i] = cnt[i+a[i]]+1,to[i] = to[i+a[i]],la[i]=la[i+a[i]];
    }
} 
inline void Modify(int x,int k) {
    a[x] = k;
    int pn = pos(x);
    for(ri i=R[pn];i>=L[pn];--i) {
        if(i+a[i] > R[pn]) cnt[i] = 1,to[i] = i + a[i],la[i] = i;
        else cnt[i] = cnt[i+a[i]] + 1,to[i] = to[i+a[i]],la[i]=la[i+a[i]];
    }
}
inline std::pair<int,int> query(int p) {
    int res = 0,lst;
    while(p <= n) {
        res += cnt[p],lst = la[p],p = to[p];
    }
    return std::make_pair(lst,res);
}
int main() {
    Init();
    for(ri i=1;i<=m;++i) {
        int opt=read(),x,y;
        if(opt) {
            x=read();
            std::pair<int,int> p = query(x);
            print(p.first),putc(' '),print(p.second),putc('\n');
        } else  {
            x=read(),y=read();
            Modify(x,y);
        }
    }
    return IO::flush(),0;
}
```

---

## 作者：KiDDOwithTopTree (赞：3)

题目在这：[传送门](https://www.luogu.com.cn/problem/CF13E)。

[P3203](https://www.luogu.com.cn/problem/P3203)。

建议先做做上面那到双倍经验的题再来做这一题（当然你也可以写完这题顺便把上一题也 A 了）。

我们先看看 P3230 怎么写：（会的可以自行跳过）

不难发现，题目所给出的条件其实可以构成一棵树。

我们可以建一个虚拟节点 $n+1$，绵羊到此处即为弹飞。

对于节点 $i$，我们把 $i$ 和 $i+k_i$ 进行 link。如果 $i+k_i>n$，则对 $i$ 和 $n+1$ 进行 link。

查询几次弹飞可以先把 $x$ 到 $n+1$ 的路径 split 出来， $n+1$ 号节点个数 -1 即为结果。

修改操作即为把 $x$ 和 $i+k_i$ 进行 cut，然后把 $k_i$ 更新，再把 $x$ 和 $i+k_i$ 进行 link。同样需要注意 $i+k_i$ 是否大于 $n$。

那么到这里，P3230 就可以 A 了。

这一题和 P3230 几乎一样，但是多了一个东西：输出最后一次落在哪个洞。

因为 splay 辅助树是按照深度来建树的，又因为是最后一个被弹飞的位置，所以这个问题相当于问 $n+1$ 的前驱。所以我们只要多一个 pre 函数去寻找 $n+1$ 号点的前驱便可以了。

当然，这题还是有一些**坑点**。

1. 因为有点卡时间，所以应该要开 scanf 和 printf。
2. pre 函数也不要忘了 pushdown 哦。

放上代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=1e6+10;
struct splay{
	int fa,son[2];
	int size;
	int rev;
};
splay spl[N];
int a[N];
inline bool check_root(int pos){
	return spl[spl[pos].fa].son[0]!=pos&&spl[spl[pos].fa].son[1]!=pos;
}
inline int relation(int pos,int fa){
	return spl[fa].son[1]==pos;
}
inline void connect(int pos,int fa,int son){
	spl[fa].son[son]=pos;
	spl[pos].fa=fa;
}
inline void pushup(int pos){
	spl[pos].size=spl[spl[pos].son[0]].size+spl[spl[pos].son[1]].size+1;
}
inline void pushdown(int pos){
	if(!spl[pos].rev)
		return ;
	swap(spl[pos].son[0],spl[pos].son[1]);
	spl[spl[pos].son[0]].rev^=1;
	spl[spl[pos].son[1]].rev^=1;
	spl[pos].rev=0;
}
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
	spl[pos].fa=gf;
	if(spl[gf].son[t2]==fa)
		spl[gf].son[t2]=pos;
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
void link(int x,int y){
	make_root(x);
	spl[x].fa=y;
}
void cut(int x,int y){
	make_root(x);
	access(y);
	splaying(y);
	spl[y].son[0]=0;
	spl[x].fa=0;
	pushup(y);
}
void split(int x,int y){
	make_root(x);
	access(y);
	splaying(y);
}
int pre(int pos){
	//因为pos已经旋为根，所以直接去找就行了
	pos=spl[pos].son[0];
	pushdown(pos);//别忘了pushdown哦
	while(spl[pos].son[1]){
		pos=spl[pos].son[1];
		pushdown(pos);//别忘了pushdown哦
	}
	splaying(pos);
	return pos;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+1;i++)
		spl[i].size=1;
	int x,y;
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		a[i]=i+x>n?n+1:i+x;
		link(i,a[i]);
	}
	int opt;
	while(m--){
		scanf("%d",&opt);
		if(opt){
			scanf("%d",&x);
			split(x,n+1);
			printf("%d %d\n",pre(n+1),spl[n+1].size-1);
		}
		else{
			scanf("%d%d",&x,&y);
			cut(x,a[x]);
			a[x]=x+y>n?n+1:x+y;
			link(x,a[x]);
		}
	}
}
```

---

## 作者：Captain_Paul (赞：2)

这题和[弹飞绵羊](https://www.luogu.org/problemnew/show/P3203)差不多

依然是暴力的分块

在原题基础上多了一问：最后一次落在哪个洞中

先预处理出每个点向后跳到达的点

每次记录$pre$，跳到$>n$的位置或者超出了块的数量就$break$

但是这样找到的$pre$不一定是最后一个洞

如果它还可以往后跳，就让它继续跳

这个地方坑我$WA$了好几发orz

```
#include<cstdio>
#include<cstring>
#include<cctype>
#include<cmath>
#include<algorithm>
#define reg register
using namespace std;
const int N=2e5+5;
struct block
{
    int l,r;
}s[500];
int n,m,q,num,a[N],to[N],belong[N],step[N];
inline int read()
{
    int x=0,w=1;
    char c=getchar();
    while (!isdigit(c)&&c!='-') c=getchar();
    if (c=='-') c=getchar(),w=-1;
    while (isdigit(c))
    {
        x=(x<<1)+(x<<3)+c-'0';
        c=getchar();
    }
    return x*w;
}
inline void getblock()
{
    int now=1;
    while (now<=n)
    {
        s[++num].l=now;
        s[num].r=min(n,now+m-1);
        now+=m;
    }
    if (num<m) s[++num].l=num*m+1,s[num].r=n; num=1;
    for (reg int i=1;i<=n;i++)
    {
        if (i>s[num].r) ++num;
        belong[i]=num;
    }
}
inline void change(int l,int r)
{
    for (reg int i=r;i>=l;i--)
    {
        if (i+a[i]>s[belong[i]].r) step[i]=1,to[i]=i+a[i];
        else step[i]=step[i+a[i]]+1,to[i]=to[i+a[i]];
    }
}
int main()
{
    n=read(),q=read(); m=sqrt(n); if (m*m<n) ++m;
    for (reg int i=1;i<=n;a[i++]=read());
    getblock(); change(1,n);
    while (q--)
    {
        int opt=read(),x=read();
        if (opt==1) 
        {
            int ans=step[x],y=to[x],pre=x;
            for (reg int i=belong[x];i<=m&&y<=n;i++) ans+=step[y],pre=y,y=to[y];
            while (pre+a[pre]<=n) pre+=a[pre];
            printf("%d %d\n",pre,ans);
        }
        else
        {
            int y=read(); a[x]=y;
            change(s[belong[x]].l,s[belong[x]].r);
        }
    }
    return 0;
}
```

---

## 作者：狛枝凪斗 (赞：1)

题解不多，LCT更少，来写一篇顺便加深自己对LCT的理解。这道题和P3203弹飞绵羊几乎一模一样，多了个输出最后落点。

对于每个点，我们可以把当前点与它所能弹到的下一个位置相连。如果跳出n的范围，就与n+1号终止点相连。终止点是为了便于之后把i->n+1用split拎出来。

然后对于询问，先看一共能跳几步，我们维护splay的size，然后直接把i->n+1用split拎出来，这条链的链长-1就是步数。链长即这个splay的size。

对于最后一个落点的询问，其实就是这个splay里n+1终止点的前驱或后继。我的代码里由于是以i为根，n+1是深度最大的点，所以是找前驱。把n+1这个点splay上去，找比它小的最大值，和找根很像。

要注意的是，splay这个操作并不能下放由splay的根到下面所有的翻转标记，在寻找前驱的时候要老老实实pushdown。（找根标准写法）

当然也有可以不用考虑什么前驱什么pushdown的做法，最后一个落点一定是整条链上除了n+1以外的最大值，维护一个最大值就可以了。

代码（里面包含两种询问第一问的做法）：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,t,top,q[100101],id,u,v;
struct node{
	int ch[2],fa,maxx,sum,tag;
}a[100101];
int b[100101];
int isroot(int x){
	return a[a[x].fa].ch[0]!=x&&a[a[x].fa].ch[1]!=x;
}
void work(int x){
	a[x].tag^=1;
	swap(a[x].ch[0],a[x].ch[1]);
}
void pushup(int x){
	a[x].sum=a[a[x].ch[0]].sum+a[a[x].ch[1]].sum+1;
	a[x].maxx=max(max(a[a[x].ch[0]].maxx,a[a[x].ch[1]].maxx),((x==t)?0:x));
	//这里是维护最大值
}
void pushdown(int x){
	if(a[x].tag){
		a[x].tag=0;
		if(a[x].ch[0])work(a[x].ch[0]);
		if(a[x].ch[1])work(a[x].ch[1]);
	}
}
void rotate(int x){
	int y=a[x].fa,z=a[y].fa;
	int k=(a[y].ch[1]==x);
	if(!isroot(y))a[z].ch[a[z].ch[1]==y]=x;
	a[x].fa=z;
	a[y].ch[k]=a[x].ch[k^1];
	a[a[x].ch[k^1]].fa=y;
	a[x].ch[k^1]=y;
	a[y].fa=x;
	pushup(y);
}
void splay(int x){
	top=1,q[top]=x;
	for(int i=x;!isroot(i);i=a[i].fa)q[++top]=a[i].fa;
	for(int i=top;i;i--)pushdown(q[i]);
	while(!isroot(x)){
		int y=a[x].fa,z=a[y].fa;
		if(!isroot(y)){
			(a[y].ch[0]==x)^(a[z].ch[0]==y)?rotate(x):rotate(y);
		}
		rotate(x);
	}
	pushup(x);
}
void access(int x){
	for(int y=0;x;y=x,x=a[x].fa){
		splay(x);
		a[x].ch[1]=y;
		pushup(x);
	}
}
void makeroot(int x){
	access(x);
	splay(x);
	work(x);
}
void link(int x,int y){
	makeroot(x);
	a[x].fa=y;
}
void split(int x,int y){
	makeroot(x);
	access(y);
	splay(y);
}
void cut(int x,int y){
	split(x,y);
	a[y].ch[0]=a[x].fa=0;
	pushup(y);
}
int main()
{
	scanf("%d%d",&n,&m);
	t=n+1;
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		if(i+b[i]<=n)link(i,i+b[i]);
		else link(i,t);
	}
	while(m--){
		scanf("%d",&id);
		if(id){
			scanf("%d",&u);
			split(u,t);
			int k=a[t].ch[0];//这种是前驱 
			pushdown(k);
			while(a[k].ch[1])k=a[k].ch[1],pushdown(k);
			printf("%d %d\n",k,a[t].sum-1);
		}
		else{
			scanf("%d%d",&u,&v);
			if(u+b[u]<=n)cut(u,u+b[u]);
			else cut(u,t);
			b[u]=v;
			if(u+b[u]<=n)link(u,u+b[u]);
			else link(u,t);
		}
	}
	return 0;
}
```
以上，感谢阅读

---

## 作者：yzx72424 (赞：1)

emmm看完题目本来想用线段树写的，但是本蒟蒻写炸了，样例都过不了，所以写了个水水的纯模拟，谁知道居然过了。。
太意外了。（不需要一点优化）

程序里字母和题面一样，注意它是先输出最后落到哪个洞！

tt记录的是次数，bbb是落地位置，然后..然后就没有了。。

附代码:

```
#include<bits/stdc++.h>
using namespace std;
int n,power[10000],m,a,b,kk,bbb;
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&power[i]);
	while(m--){
	     scanf("%d",&kk);
		 if(kk==0){
		 	scanf("%d%d",&a,&b);
		 	power[a]=b;
		 }	
		 else {
		 	scanf("%d",&a);
		 	 bbb=a;
      		int tt=0;
	 		while(1){
			     tt++;
			    if(power[a]+a>n)break;
		 	    bbb=power[a]+a;a=bbb; 
		 	   
		 	}
		 	printf("%d %d\n",bbb,tt );
		 }
		

	}
}
```


---

## 作者：年华天地 (赞：0)

这道题首先看数据范围，$10^5$,那首先想到分块维护吧，但这道题的分块与普通的分块不太一样，它是一种叫做块状链表的东西维护的。块状链表是什么呢？
![块状链表](https://cdn.luogu.com.cn/upload/image_hosting/6g122yrj.png)
（其实就是用链表吧块与块之间连了起来）

那我们要用块状链表维护什么呢？

显而易见，维护每一个点跳出这个块以后会跳在哪里以及所需时间，这样我们一个点只会跳一次，就把一次询问时间复杂度就是$O$($\sqrt{n}$)。

那么对于修改操作呢？因为一次修改只会改变一个块里的信息，所以我们需要从右向左的维护，可以实现$O(1)$,为什么要从右向左呢？因为从右向左你可以发现你只需要向右跳一次就可以更新答案，如果你向右跳一步还在块内，因为你向右跳过的点以及更新过了，所以直接继承，如果在块外，那么直接更新。所以修改的时间复杂度也是$O$($\sqrt{n}$)的。

修改代码
```
void change(int x,int y)//x为位置，y为值
{
	int tmp=x,cnt=0;
	a[x]=y;
	while (pos[tmp].k==pos[x].k)tmp+=a[tmp],cnt++;
	pos[x].next=tmp;
	pos[x].w=cnt;
	for (int i=x-1;i>=l[pos[x].k];i--)
	{
		int tmp=i,cnt=0;
		tmp=tmp+a[tmp];//向右跳一步
		if (pos[tmp].k==pos[i].k)//在块内直接继承
		{
			pos[i].next=pos[tmp].next;
			pos[i].w=pos[tmp].w+1;
		}
		else//在块外
		{
			pos[i].next=tmp;
			pos[i].w=1;
		}
	}
}
```

完整代码
```
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=2e5+10;
int n,m,a[maxn],k,l[maxn];
struct node{
	int next,w,k;
}pos[maxn*2];
void ask(int x)
{
	int tmp=x,ans=0,cnt=tmp;
	while(pos[tmp].k)
	{
		ans+=pos[tmp].w;
		cnt=tmp;
		tmp=pos[tmp].next;
	}
	tmp=cnt;
	while(pos[tmp].k==pos[cnt].k)cnt=tmp,tmp+=a[tmp];
	printf("%d %d\n",cnt,ans);
}
void change(int x,int y)
{
	int tmp=x,cnt=0;
	a[x]=y;
	while (pos[tmp].k==pos[x].k)tmp+=a[tmp],cnt++;
	pos[x].next=tmp;
	pos[x].w=cnt;
	for (int i=x-1;i>=l[pos[x].k];i--)
	{
		int tmp=i,cnt=0;
		tmp=tmp+a[tmp];
		if (pos[tmp].k==pos[i].k)
		{
			pos[i].next=pos[tmp].next;
			pos[i].w=pos[tmp].w+1;
		}
		else
		{
			pos[i].next=tmp;
			pos[i].w=1;
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]);
	k=sqrt(n);
	for (int i=1;i<=n;i++)pos[i].k=(i-1)/k+1;	
	for (int i=1;i<=n;i++)if (pos[i].k!=pos[i-1].k)l[pos[i].k]=i;
	for (int i=1;i<=n;i++)
	{
		int tmp=i,cnt=0;
		while (pos[tmp].k==pos[i].k)tmp+=a[tmp],cnt++;
		pos[i].next=tmp;
		pos[i].w=cnt;
	}
	for (int i=1;i<=m;i++)
	{
		int opt,x,y;
		scanf("%d",&opt);
		if (opt==1)
		{
			scanf("%d",&x);
			ask(x);
		}
		else
		{
			scanf("%d%d",&x,&y);
			change(x,y);
		}
	}
	return 0;
}
```



---

## 作者：da32s1da (赞：0)

显然与弹飞绵羊是一个题，只不过加了一个求**n+1的前驱**。

记录最大点的编号，令n+1的编号为0。

```
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+50;
inline void swap(int &u,int &v){int o=u;u=v;v=o;}
struct lct{
    int ch[N][2],fa[N],siz[N],tagrev[N],Max[N],val[N];
    bool isrot(int x){
        return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
    }
    void rev(int x){
        tagrev[x]^=1;
        swap(ch[x][0],ch[x][1]);
    }
    void pushdown(int x){
        if(!isrot(x))pushdown(fa[x]);
        if(!x||!tagrev[x])return;
        tagrev[x]=0;
        rev(ch[x][0]);rev(ch[x][1]);
    }
    void update(int x){
        if(!x)return;
        siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
        Max[x]=max({val[x],Max[ch[x][0]],Max[ch[x][1]]});//直接取max更新就好
    }
    void rotate(int x){
        int y=fa[x],z=fa[y],opt=(ch[y][1]==x),w=ch[x][opt^1];
        if(!isrot(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
        ch[y][opt]=w;fa[w]=y;
        ch[x][opt^1]=y;fa[y]=x;
        update(y);update(x);
    }
    void splay(int x){
        int y,z;pushdown(x);
        while(!isrot(x)){
            y=fa[x];z=fa[y];
            if(!isrot(y))
            rotate(((ch[y][0]==x)^(ch[z][0]==y))?x:y);
            rotate(x);
        }
    }
    void access(int x){
        for(int y=0;x;y=x,x=fa[x])
        splay(x),ch[x][1]=y,update(x);
    }
    void mktrot(int x){
        access(x);splay(x);rev(x);
    }
    void mkvrot(int x){
        access(x);splay(x);
    }
    void query(int x,int y){
        mktrot(x);mkvrot(y);
        printf("%d %d\n",Max[y],siz[y]-1);
    }
    void link(int x,int y){
        mktrot(x);mkvrot(y);
        fa[x]=y;
    }
    void cut(int x,int y){
        mktrot(x);mkvrot(y);
        ch[y][0]=fa[x]=0;
        update(y);
    }
}s;
int n,m,a[N],opt,x,y;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)s.siz[i]=1,s.Max[i]=s.val[i]=i;//记录最大点编号
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(i+a[i]<=n)s.link(i,i+a[i]);
        else s.link(i,n+1);
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&opt);
        if(opt==1){
            scanf("%d",&x);
            s.query(x,n+1);
            continue;
        }else{
            scanf("%d%d",&x,&y);
            if(x+a[x]<=n){
                s.cut(x,x+a[x]);
                if(x+y<=n)s.link(x,x+y);
                else s.link(x,n+1);
            }else{
                s.cut(x,n+1);
                if(x+y<=n)s.link(x,x+y);
                else s.link(x,n+1);
            }
            a[x]=y;
        }
    }
}
```

---

## 作者：newbiechd (赞：0)

# CF13E Holes

[LG传送门](https://www.luogu.org/problemnew/show/CF13E)

双倍经验题，几乎同[[HNOI2010]弹飞绵羊](https://www.luogu.org/problemnew/show/P3203)，LCT练手题，LG没有LCT题解于是发一波。

从当前点向目标点连边，构成一棵树，带修改就用LCT动态维护答案，由于不用查询修改链上信息，不需要与makeroot有关的函数。分块也可以写。

不会LCT的话可以看看我的[LCT总结](https://www.cnblogs.com/cj-chd/p/10065274.html)。

```cpp
#include<cstdio>
#include<cctype>
#define R register
#define I inline
using namespace std;
const int S=100003;
char buf[1000000],*p1,*p2;
I char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,S,stdin),p1==p2)?EOF:*p1++;}
I int rd(){
	R int f=0; R char c=gc();
	while(c<48||c>57) c=gc();
	while(c>47&&c<58) f=f*10+(c^48),c=gc();
	return f;
}
struct splay{int p,d[2],s;}e[S];
I int min(int x,int y){return x<y?x:y;}
I int nrt(int x){return e[e[x].p].d[0]==x||e[e[x].p].d[1]==x;}
I void psu(int x){e[x].s=e[e[x].d[0]].s+e[e[x].d[1]].s+1;}
I void rtt(int x){
	R int f=e[x].p,g=e[f].p,b=e[f].d[0]==x,c=e[x].d[b];
	if(nrt(f)) e[g].d[e[g].d[1]==f]=x;
	if(c) e[c].p=f;
	e[x].p=g,e[f].p=x,e[x].d[b]=f,e[f].d[!b]=c,psu(f);
}
I void spl(int x){
	for(R int f,g;nrt(x);rtt(x)){
		f=e[x].p,g=e[f].p;
		if(nrt(f))
			rtt((e[g].d[1]==f)^(e[f].d[1]==x)?x:f);
	}
	psu(x);
}
I void acc(int x){
	for(R int y=0;x;x=e[y=x].p)
		spl(x),e[x].d[1]=y,psu(x);
}
I void cut(int x){acc(x),spl(x),e[e[x].d[0]].p=0,e[x].d[0]=0,psu(x);}
I int frt(int x){
	acc(x),spl(x);
	while(e[x].d[0])
		x=e[x].d[0];
	return x;
}
int main(){
	R int n=rd(),m=rd(),i,x,y,z;
	for(i=1;i<=n;++i){
		x=rd(),z=i+x;
		if(z<=n)
			e[i].p=z;
	}
	for(i=1;i<=m;++i){
		x=rd(),y=rd();
		if(x)
			printf("%d ",frt(y)),printf("%d\n",e[y].s);
		else{
			x=rd(),cut(y),z=x+y;
			if(z<=n)
				e[y].p=z;
		}
	}
	return 0;
}

```



---

