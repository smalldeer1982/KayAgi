# Terrible Homework

## 题目背景

“像糟糕的作业一样糟糕。”

## 题目描述

$ben$同学最讨厌做作业了。

现在，老师布置给了$ben$同学$n$份作业，每份作业有一个难度值$A_i$。

一开始，每份作业都是独立的。有一些操作，每次在两份作业$x,y$间加一条边或删除一条边。

由于老师喜怒无常，因此还有一些操作，是将两份作业$x,y$之间路径上的所有作业的难度值都$xor$上一个值。

同时，为了满足$ben$同学的好奇心，你需要回答两份作业$x,y$之间的所有作业的难度$and$和、难度$or$和、难度$xor$和以及难度和。

## 说明/提示

对于$10\%$的数据，$n=100,m=100$。

另有$10\%$的数据，$n=5000,m=5000$。

另有$20\%$的数据，$n=10000,m=10000$。

对于$100\%$的数据，$2\le n,m\le100000,0\le A_i<2^{30}$。

## 样例 #1

### 输入

```
4 10
1 2 3 4
L 1 2
L 2 3
L 2 4
A 1 4
U 3 4 2
O 1 4
C 2 4
L 3 4
X 1 4
S 1 3```

### 输出

```
0
7
6
2```

# 题解

## 作者：hsfzLZH1 (赞：5)

~~这题真是糟糕啊~~

~~重构一遍就过了~~

## 解题思路

观察到题目维护的是动态树上的树链信息问题，不难想到用 LCT 维护。

考虑维护修改操作。由于按位异或操作对按位与，按位或和求和操作不具有分配率，所以我们讨论每一位的情况。

不难发现，异或二进制拆位后具有分配率。如果异或的 $v$ 值在二进制上的第 $i$ 位有值的话，会将这棵子树里的所有值的这一位上都会反转（即 $0$ 变为 $1$ ， $1$ 变为 $0$ ）。

我们以辅助树子树中每一位上 $0$ 和 $1$ 的数量来记录树链的信息并处理查询。

进行修改操作时，提取出 $x$ 到 $y$ 的树链到一棵树上，将根节点上对应位的 $0$ 和 $1$ 的数量交换，然后打上标记。在进行 ```splay``` 操作前，先下传所有路径上会经过的标记。

查询树链信息时，我们同样提取出 $x$ 到 $y$ 之间的树链。

对于每一位，如果子树中这一位上没有 $0$ ，说明这一位上 ```and``` 值为 $1$ ；

如果子树中这一位上至少有一个 $1$ ，说明这一位上 ```or``` 值为 $1$ ；

如果子树中这一位上 $1$ 的个数为奇数，说明这一位上 ```xor``` 的值为 $1$ 。

求树链和时，只需求出所有位上 $1$ 的个数乘这个数位的大小的总和。这里需要使用 ```long long``` 。

时间复杂度 $O(n\log _2 n\log_2 A)$ ，空间复杂度 $O(n\log_2 A)$ 。

## 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n,q,x,y,z;
char op;
typedef long long ll;
ll ans;
struct Splay
{
	int ch[maxn][2],fa[maxn],v[maxn],tag[maxn],xr[maxn],zero[maxn][31],ones[maxn][31];
	void clear(int x)
	{
		ch[x][0]=ch[x][1]=fa[x]=tag[x]=xr[x]=0;
		for(int i=0;i<=30;i++)zero[x][i]=ones[x][i]=0;
	}
	int getch(int x){return ch[fa[x]][1]==x;}
	int isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	void maintain(int x)
	{
		for(int i=0;i<=30;i++)zero[x][i]=ones[x][i]=0;
		for(int i=0;i<=30;i++)if(v[x]&(1<<i))ones[x][i]++;else zero[x][i]++;
		if(ch[x][0])for(int i=0;i<=30;i++)zero[x][i]+=zero[ch[x][0]][i],ones[x][i]+=ones[ch[x][0]][i];
		if(ch[x][1])for(int i=0;i<=30;i++)zero[x][i]+=zero[ch[x][1]][i],ones[x][i]+=ones[ch[x][1]][i];
	}
	void pushdown(int x)
	{
		if(tag[x])
		{
			if(ch[x][0])swap(ch[ch[x][0]][0],ch[ch[x][0]][1]),tag[ch[x][0]]^=1;
			if(ch[x][1])swap(ch[ch[x][1]][0],ch[ch[x][1]][1]),tag[ch[x][1]]^=1;
			tag[x]=0;
		}
		if(xr[x])
		{
			if(ch[x][0])
			{
				for(int i=0;i<=30;i++)if(xr[x]&(1<<i))swap(zero[ch[x][0]][i],ones[ch[x][0]][i]);
				v[ch[x][0]]^=xr[x];xr[ch[x][0]]^=xr[x];
			}
			if(ch[x][1])
			{
				for(int i=0;i<=30;i++)if(xr[x]&(1<<i))swap(zero[ch[x][1]][i],ones[ch[x][1]][i]);
				v[ch[x][1]]^=xr[x];xr[ch[x][1]]^=xr[x];
			}
			xr[x]=0;
		}
	}
	void update(int x)
	{
		if(!isroot(x))update(fa[x]);
		pushdown(x);
	}
	void rotate(int x)
	{
		int y=fa[x],z=fa[y],chx=getch(x),chy=getch(y);
		fa[x]=z;if(!isroot(y))ch[z][chy]=x;
		ch[y][chx]=ch[x][chx^1];fa[ch[x][chx^1]]=y;
		ch[x][chx^1]=y;fa[y]=x;
		maintain(y);maintain(x);
	}
	void splay(int x)
	{
		update(x);
		for(int f=fa[x];f=fa[x],!isroot(x);rotate(x))
		if(!isroot(f))rotate(getch(x)==getch(f)?f:x);
	}
	void access(int x)
	{
		for(int f=0;x;f=x,x=fa[x])
		splay(x),ch[x][1]=f,maintain(x);
	}
	void makeroot(int x)
	{
		access(x);splay(x);
		tag[x]^=1;
		swap(ch[x][0],ch[x][1]);
	}
}st;
int main()
{
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)scanf("%d",&st.v[i]),st.maintain(i);
	while(q--)
	{
		scanf(" %c%d%d",&op,&x,&y);
		if(op=='L')
		{
			st.makeroot(x);st.fa[x]=y;
		}
		if(op=='C')
		{
			st.makeroot(x);st.access(y);st.splay(y);
			st.fa[x]=st.ch[y][0]=0;
			st.maintain(y);
		}
		if(op=='U')
		{
			scanf("%d",&z);
			st.makeroot(x);st.access(y);st.splay(y);
			for(int i=0;i<=30;i++)if(z&(1<<i))swap(st.zero[y][i],st.ones[y][i]);
			st.xr[y]^=z;st.v[y]^=z;
		}
		if(op=='A')
		{
			st.makeroot(x);st.access(y);st.splay(y);
			ans=0;
			for(int i=0;i<=30;i++)if(!st.zero[y][i])ans+=(1<<i);
			printf("%lld\n",ans);
		}
		if(op=='O')
		{
			st.makeroot(x);st.access(y);st.splay(y);
			ans=0;
			for(int i=0;i<=30;i++)if(st.ones[y][i])ans+=(1<<i);
			printf("%lld\n",ans); 
		}
		if(op=='X')
		{
			st.makeroot(x);st.access(y);st.splay(y);
			ans=0;
			for(int i=0;i<=30;i++)if(st.ones[y][i]&1)ans+=(1<<i);
			printf("%lld\n",ans);
		}
		if(op=='S')
		{
			st.makeroot(x);st.access(y);st.splay(y);
			ans=0;
			for(int i=0;i<=30;i++)ans+=(ll)(1<<i)*(ll)st.ones[y][i];
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

---

## 作者：NaCly_Fish (赞：1)

`愿天堂没有J*题和J*出题人。`  

看起来不太好搞，实际上是一道并无技术含量的**水题**。  
(但还是因为LCT板子打错调了2h)  
有动态加边删边，考虑用LCT维护。  

链上操作有整体$\text{xor}$一个值，考虑按位算，维护链上所有数第$i$位$1$的个数。 
给某一位$\text{xor}$上$1$，就相当于把$1$都变成了$0$，$0$都变成了$1$。  

求链上$\text{and}$和，必须每个点的第$i$位都是$1$，结果的第$i$位才会是$1$。  
对于$\text{or}$和，只要有一个点的第$i$位是$1$，结果的第$i$位就是$1$。   
对于求$\text{xor}$和，第$i$位是$1$的点有奇数个，结果的第$i$位才会是$1$。  
直接求和是最简单的，对于所有的$i$，第$i$位$1$的个数左移$i$位之和即是答案。  

由于是LCT，并不是线段树，注意维护子树大小等信息。

Code：  
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<queue>
#define N 100007
#define int long long
#define reg register
#define inf 0x3f3f3f3f
#define ls son[u][0]
#define rs son[u][1]
#define K 32
using namespace std;

int a[N];
int n,q;

struct Link_Cut_Tree{
    int st[N],fa[N],son[N][2],size[N];
    int r[N],s[N][K],tag[N][K];

    inline bool notroot(int u){
        return son[fa[u]][0]==u||son[fa[u]][1]==u;
    }

    inline void pushup(int u){
        size[u] = size[ls]+size[rs]+1;
        for(reg int i=0;i<K;++i) //pushup也按位算
            s[u][i] = s[ls][i]+s[rs][i]+((a[u]>>i)&1);
    }

    inline void pushr(int u){
        swap(ls,rs);
        r[u] ^= 1;
    }

    inline void pushxor(int u,int i){
    	//处理异或标记,给u的第i为异或上1
        a[u] ^= 1<<i;
        tag[u][i] ^= 1; 
        s[u][i] = size[u]-s[u][i];
    }

    inline void pushdown(int u){
        for(reg int i=0;i<K;++i){
            if(!tag[u][i]) continue;
            if(ls) pushxor(ls,i);
            if(rs) pushxor(rs,i);
            tag[u][i] = 0;
        }
        if(!r[u]) return;
        if(ls) pushr(ls);
        if(rs) pushr(rs);
        r[u] = 0;
    }

    inline void rotate(int x){
        int y = fa[x],z = fa[y];
        int k = son[y][1]==x,w = son[x][k^1];
        if(notroot(y)) son[z][son[z][1]==y] = x;
        son[x][k^1] = y;
        son[y][k] = w;
        if(w) fa[w] = y;
        fa[y] = x,fa[x] = z;
        pushup(y);
    }

    inline void splay(int x){
        int y = x,z = 0;
        st[++z] = y;
        while(notroot(y)) st[++z] = y = fa[y];
        while(z) pushdown(st[z--]);
        while(notroot(x)){
            y = fa[x],z = fa[y];
            if(notroot(y)){
                if((son[z][1]==y)==(son[y][1]==x)) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
        pushup(x);
    }

    inline void access(int u){
        for(int y=0;u;u=fa[u]){
            splay(u);
            rs = y;
            pushup(u);
            y = u;
        }
    }

    inline void makeroot(int u){
        access(u),splay(u);
        pushr(u);
    }

    inline int findroot(int u){
        access(u),splay(u);
        while(ls){
            pushdown(u);
            u = ls;
        }
        splay(u);
        return u;
    }

    inline void split(int u,int v){
        makeroot(u);
        access(v),splay(v);
    }

    inline void link(int u,int v){
        makeroot(u);
        if(findroot(v)!=u) fa[u] = v;
    }

    inline void cut(int u,int v){
        makeroot(u);
        if(findroot(v)!=u||son[v][0]||fa[v]!=u) return;
        fa[v] = son[u][1] = 0;
        pushup(u);
    }

    inline void modify(int u,int v,int k){
        split(u,v);
        for(reg int i=0;k;++i){
            if(k&1) pushxor(v,i); //按位打标记
            k >>= 1;
        }
    }

    inline int qsum(int u,int v){
    	//求和
        split(u,v);
        int res = 0;
        for(reg int i=0;i<K;++i)
            res += s[v][i]<<i;
        return res;
    }

    inline int qxor(int u,int v){
    	//求xor和
        split(u,v);
        int res = 0;
        for(reg int i=0;i<K;++i)
            if(s[v][i]&1) res |= 1ll<<i;
        return res;
    }

    inline int qand(int u,int v){
    	//求and和
        split(u,v);
        int res = 0;
        for(reg int i=0;i<K;++i)
            if(s[v][i]==size[v]) res |= 1ll<<i;
        return res;    
    }

    inline int qor(int u,int v){
    	//求or和
        split(u,v);
        int res = 0;
        for(reg int i=0;i<K;++i)
            if(s[v][i]) res |= 1ll<<i;
        return res;    
    }
}T;

inline void read(int &x);
void print(int x);

signed main(){
    int u,v,k;
    read(n),read(q);
    for(reg int i=1;i<=n;++i){
        read(a[i]);
        T.size[i] = 1; //初始每个点的子树大小都是1
    }
    while(q--){
        char c = getchar();
        while(c<'A'||c>'Z') c = getchar();
        read(u),read(v);
        if(c=='U') read(k);
        if(c=='L') T.link(u,v);
        else if(c=='C') T.cut(u,v);
        else if(c=='U') T.modify(u,v,k);
        else if(c=='O') print(T.qor(u,v)),putchar('\n');
        else if(c=='A') print(T.qand(u,v)),putchar('\n');
        else if(c=='X') print(T.qxor(u,v)),putchar('\n');
        else print(T.qsum(u,v)),putchar('\n');
    }
    return 0;
}

inline void read(int &x){
    x = 0;
    char c = getchar();
    while(c<'0'||c>'9') c = getchar();
    while(c>='0'&&c<='9'){
        x = (x<<3)+(x<<1)+(c^48);
        c = getchar();
    }
}

void print(int x){
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
```

---

## 作者：mrsrz (赞：1)

~~不是数论题吗怎么出成数据结构了啊~~

$\rm Link-Cut-Tree$裸题。

我们套路地对每一位分别维护一下和就好了。

每条重链的splay上打一下异或标记就可以了。

也没有什么坑，标记的下放，上传也非常简单。

时间复杂度$O(30n\log n)$。

## Code：
```cpp
#include<cstdio>
#include<algorithm>
const int N=1e5+5;
int n,m;
typedef long long LL;
namespace lct{
	int ch[N][2],tag[N],val[N],fa[N],And[N],Or[N],Xor[N],sum[N][30],xtag[N],sz[N];
	inline int ckr(int x,int p=1){return ch[fa[x]][p]==x;}
	inline int isroot(int x){return!(ckr(x)||ckr(x,0));}
	inline void flip(int x){tag[x]^=1,std::swap(ch[x][0],ch[x][1]);}
	inline void update(int x){
		sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+1;
		And[x]=And[ch[x][0]]&And[ch[x][1]]&val[x];
		Or[x]=Or[ch[x][0]]|Or[ch[x][1]]|val[x];
		Xor[x]=Xor[ch[x][0]]^Xor[ch[x][1]]^val[x];
		for(int i=0;i<30;++i)
		sum[x][i]=sum[ch[x][0]][i]+sum[ch[x][1]][i]+(val[x]>>i&1);
	}
	void modify(int x,int v){
		xtag[x]^=v,val[x]^=v;
		int&A=And[x],&O=Or[x],&X=Xor[x];
		A=O=X=0;
		for(int i=0;i<30;++i){
			if(v>>i&1)sum[x][i]=sz[x]-sum[x][i];
			A|=(sum[x][i]==sz[x])<<i,O|=(!!sum[x][i])<<i,X|=(sum[x][i]&1)<<i;
		}
	}
	inline void pushdown(int x){
		if(tag[x]){
			tag[x]=0;
			if(ch[x][0])flip(ch[x][0]);
			if(ch[x][1])flip(ch[x][1]);
		}
		if(xtag[x]){
			if(ch[x][0])modify(ch[x][0],xtag[x]);
			if(ch[x][1])modify(ch[x][1],xtag[x]);
			xtag[x]=0;
		}
	}
	inline void rotate(int x){
		int y=fa[x],z=fa[y],k=ckr(x);
		if(!isroot(y))ch[z][ckr(y)]=x;
		fa[x]=z,fa[y]=x,fa[ch[x][!k]]=y;
		ch[y][k]=ch[x][!k],ch[x][!k]=y,update(y);
	}
	inline void splay(int x){
		static int sta[N],top;sta[top=1]=x;
		for(int y=x;!isroot(y);sta[++top]=y=fa[y]);
		while(top)pushdown(sta[top--]);
		for(;!isroot(x);rotate(x))
		if(!isroot(fa[x]))rotate((ckr(x)^ckr(fa[x]))?x:fa[x]);
		update(x);
	}
	inline void access(int x){for(int t=0;x;ch[x][1]=t,t=x,x=fa[x])splay(x);}
	inline void makeroot(int x){access(x),splay(x),flip(x);}
	inline void split(int x,int y){makeroot(x),access(y),splay(y);}
	inline int findroot(int x){access(x);for(splay(x);ch[x][0];x=ch[x][0]);splay(x);return x;}
	inline void link(int x,int y){makeroot(x),fa[x]=y;}
	inline void cut(int x,int y){split(x,y),fa[x]=ch[y][0]=0,update(y);}
	inline void modify(int x,int y,int v){split(x,y),modify(y,v);}
	inline LL query(int x,int y,char op){
		split(x,y);
		switch(op){
			case'A':return And[y];
			case'O':return Or[y];
			case'X':return Xor[y];
			case'S':
				LL ans=0;
				for(int i=0;i<30;++i)
				ans+=sum[y][i]*(1LL<<i);
				return ans;
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	lct::And[0]=(1<<30)-1;
	for(int i=1;i<=n;++i)scanf("%d",lct::val+i),lct::update(i);
	while(m--){
		char op[3];int x,y;
		scanf("%s%d%d",op,&x,&y);
		switch(*op){
			case'L':{
				lct::link(x,y);
				break;
			}
			case'C':{
				lct::cut(x,y);
				break;
			}
			case'U':{
				int v;
				scanf("%d",&v);
				lct::modify(x,y,v);
				break;
			}
			default:printf("%lld\n",lct::query(x,y,*op));
		}
	}
	return 0;
}
```

---

## 作者：zhenglier (赞：1)

## 前置知识：LCT（动态树）

看到题目里要求Link和Cut，当然就会想到LCT。

考虑用LCT，但因为有求链上$and$和链上$or$，而$and$的结果和$or$的结果在进行一次链上异或操作后，信息难以直接维护。但$N$的大小是$1e5$的，可以考虑建30棵LCT，第$i(0\leq i<30)$棵维护这棵树上这个点在第$i$个二进制位上的值，复杂度$O(nlog^2n)$，应该是可行的。

考虑维护的东西，记$js[x][i]$为以$x$为根的splay中所有数，二进制第$i$位为1的点数。

对于询问操作，若split出来的splay在第$i$位1的数量为奇数，则异或值加上该$1<<i$；若数量等于该splay的大小，则and值加上$1<<i$；若数量不为0，则or值加上$1<<i$。

对于修改操作，直接将split出来的splay对于该splay中的每一个节点$x$,对于$i(0\leq i<30)$，$js[x][i]=sz[x]-js[x][i]$，当然不能直接暴力，要打懒标记。

然后就是代码实现了。

```cpp#include<bits/stdc++.h>
#define res register int
using namespace std;
const int N=3000010,t=31;
int n,m;
int fa[N],ch[N][2],sz[N],js[N][t+1];
bool rev[N],val[N][t+1],r[N][t+1];
inline bool get(res x){
    return x==ch[fa[x]][1];
}
inline bool nroot(res x){
    return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
}
inline void pushup(res x){
    sz[x]=sz[ch[x][0]]+1+sz[ch[x][1]];
    for(int i=0;i<t;++i){
	    js[x][i]=js[ch[x][0]][i]+val[x][i]+js[ch[x][1]][i];
	}
}
inline void reverse(res x){
    rev[x]^=1;
    swap(ch[x][0],ch[x][1]);
}
inline void assign(res x,int len){
    val[x][len]^=1;
    r[x][len]^=1;
    js[x][len]=sz[x]-js[x][len];
}
inline void pushdown(res x){
    if(rev[x]){
        rev[x]=0;
        if(ch[x][0])reverse(ch[x][0]);
        if(ch[x][1])reverse(ch[x][1]);
    }
    for(int i=0;i<t;++i){
	    if(r[x][i]){
	        r[x][i]=0;
	        if(ch[x][0])assign(ch[x][0],i);
	        if(ch[x][1])assign(ch[x][1],i);
		}
	}
}
inline void rotate(res x){
    res f=fa[x],oldf=fa[f],k=get(x);
    if(!nroot(f))ch[oldf][get(f)]=x;
    fa[x]=oldf;
    ch[f][k]=ch[x][k^1],fa[ch[x][k^1]]=f;
    ch[x][k^1]=f,fa[f]=x;
    pushup(f),pushup(x);
}
int st[N],top;
inline void splay(res x){
    res y=x;
    st[++top]=y;
    while(!nroot(y))st[++top]=fa[y],y=fa[y];
    while(top)
        pushdown(st[top--]);
    while(1){
        res y=fa[x];
        if(nroot(x))return;
        if(get(x)==get(y)&&!nroot(y))rotate(y);
        rotate(x);
    }
}
inline void access(res x){
    for(res y=0;x;y=x,x=fa[x]){
        splay(x),ch[x][1]=y,pushup(x);
    }
}
inline void makeroot(res x){
    access(x),splay(x);
    reverse(x);
}
inline int findroot(int x){
    access(x),splay(x);
    while(ch[x][0])pushdown(x),x=ch[x][0];
    splay(x);
    return x;
}
inline void split(int x,int y){
    makeroot(x);
    access(y),splay(y); 
}
inline bool link(int x,int y){
    makeroot(x);
    if(findroot(y)==x)return 0;
    fa[x]=y;
    return 1;
}
inline int cut(int x,int y){
    makeroot(x);
    if(findroot(y)==x&&sz[x]==2)
        fa[y]=ch[x][1]=0;
    pushup(x);
    return 1;
}
inline int read(){
    res ret=0;char c;
    for(c=getchar();!isdigit(c);c=getchar());
    for(;isdigit(c);ret=(ret<<1)+(ret<<3)+c-'0',c=getchar());
    return ret;
}
int main(){
	cin>>n>>m;
	for(res i=1;i<=n;++i){
	    res x=read();
	    for(res j=0;j<t;++j){
	        val[i][j]=bool(x&(1<<j));
		}
	}
	while(m--){
		char op[2];
		scanf("%s",op);
		if(op[0]=='L'){
		    res x=read(),y=read();
		    link(x,y);
		}else if(op[0]=='A'){
		    res x=read(),y=read(),ans=0;
		    split(x,y);
		    for(res i=0;i<t;++i){
		        if(js[y][i]==sz[y]){
		            ans|=(1<<i);
				}
			}
			printf("%d\n",ans);
		}else if(op[0]=='U'){
		    res x=read(),y=read(),z=read();
			split(x,y);
		    for(res i=0;i<t;++i){
		    	if(z&(1<<i)){
			        assign(y,i);
			    }
			}
		}else if(op[0]=='O'){
		    res x=read(),y=read(),ans=0;
		    split(x,y);
		    for(res i=0;i<t;++i){
		        if(js[y][i]){
		            ans|=(1<<i);
				}
			}
			printf("%d\n",ans);
		}else if(op[0]=='X'){
			res x=read(),y=read(),ans=0;
		    split(x,y);
		    for(res i=0;i<t;++i){
		        if(js[y][i]&1)ans|=(1<<i);
			}
			printf("%d\n",ans);
		}else if(op[0]=='C'){
		    res x=read(),y=read();
		    cut(x,y);
		}else{
		    res x=read(),y=read();
			long long ans=0;
		    split(x,y);
		    for(res i=0;i<t;++i){
		        ans+=(1ll<<i)*js[y][i];
			}
			printf("%lld\n",ans);
		}
	}
}
```

---

## 作者：mzgwty (赞：0)

这题可真是毒瘤啊~~只是对本蒟蒻来说~~

因为$n < (1<<31) $,所以我们可以直接按位记录信息

时间复杂度$O(nlog^2n)$

$sum[x][i]$表示以$x$为根的子树中权值第$i$位为一的节点数

$size[x]$表示以$x$为根的子树大小

有难度的操作就只有$pushup$和$pushdown$了

对于$pushup$，直接把左右儿子的信息和当前节点的信息加起来即可

```cpp
inline void pushup(int x) {
	for(register int i=0 ; i<=30 ; ++i) sum[x][i]=sum[ch[x][0]][i]+sum[ch[x][1]][i]+(bool)((1<<i)&val[x]);
	size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
}

```

然后对于$pushdown$，直接用一个$lazytag$

先建立一个$push$函数

```cpp
inline void push(int x,int c) {
	val[x]^=c,xr[x]^=c;
	for(register int i=0 ; i<=30 ; ++i) sum[x][i]=(c&(1<<i))?size[x]-sum[x][i]:sum[x][i];
}
```

这个函数的意思就是把以节点$x$为根的子树所有的值 $xor$ 上$c$

如果这个节点第$i$位是$1$，那么我们就需要将$sum[x][i]$改成$size[x]-sum[x][i]$，因为以$x$为根的所有$y$节点第$i$位都要改成与它本来不同的值，即$1->0;0->1$,所以其实是$1$的个数与$0$的个数交换了

然后就是$pushdown$函数

```cpp
inline void pushdown(int x) {
	if(tag[x]) {
		swap(ch[x][0],ch[x][1]);
		tag[ch[x][0]]^=1,tag[ch[x][1]]^=1;
		tag[x]=0;
	}
	if(xr[x]) {
		if(ch[x][0]) push(ch[x][0],xr[x]);
		if(ch[x][1]) push(ch[x][1],xr[x]);
		xr[x]=0;
	}
}
```

对于$L$操作，直接$link(x,y)$即可

对于$C$操作，直接$cut(x,y)$即可

对于$U$操作，我们先$split(x,y)$，再$push(y,v)$

$P.S.$我刚开始没把$push$写成这种形式，然后一个点都没$AC$

对于$A$操作，若第$i$位$sum[x][i]==size[x]$,则$ans+=(1<<i)$

对于$O$操作，若第$i$位$sum[x][i]!=0$,则$ans+=(1<<i)$

对于$X$操作，若第$i$位$sum[x][i]$是奇数,则$ans+=(1<<i)$

对于$S$操作，$ans+=sum[x][i]*(1<<i)$
注意这个要开$long \ long$

然后$show \ you \ the \ code$

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read() {
	int res=0,f=1;char ch;
	while(isspace(ch=getchar()));
	if(ch=='-') ch=getchar(),f=-1;
	do {
		res=res*10+ch-'0';
	} while(isdigit(ch=getchar()));
	return res*f;
}

const int N=100005;

int size[N],ch[N][2],f[N],sum[N][32],xr[N],val[N];

bool tag[N];

inline bool nroot(int x) {
	return ch[f[x]][0]==x||ch[f[x]][1]==x;
}

inline bool get(int x) {
	return ch[f[x]][1]==x;
}

inline void pushup(int x) {
	for(register int i=0 ; i<=30 ; ++i) sum[x][i]=sum[ch[x][0]][i]+sum[ch[x][1]][i]+(bool)((1<<i)&val[x]);
	size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
}

inline void push(int x,int c) {
	val[x]^=c,xr[x]^=c;
	for(register int i=0 ; i<=30 ; ++i) sum[x][i]=(c&(1<<i))?size[x]-sum[x][i]:sum[x][i];
}

inline void pushdown(int x) {
	if(tag[x]) {
		swap(ch[x][0],ch[x][1]);
		tag[ch[x][0]]^=1,tag[ch[x][1]]^=1;
		tag[x]=0;
	}
	if(xr[x]) {
		if(ch[x][0]) push(ch[x][0],xr[x]);
		if(ch[x][1]) push(ch[x][1],xr[x]);
		xr[x]=0;
	}
}

inline void rotate(int x) {
	int fa=f[x],grfa=f[fa],k=get(x),c=ch[x][!k];
	if(nroot(fa)) ch[grfa][get(fa)]=x;
	ch[x][!k]=fa,ch[fa][k]=c;
	if(c) f[c]=fa;
	f[fa]=x,f[x]=grfa;
	pushup(fa);
}

int stk[N],top;

inline void pushall(int x) {
	stk[top=1]=x;
	while(nroot(x)) stk[++top]=x=f[x];
	while(top) pushdown(stk[top--]);
}

inline void splay(int x) {
	pushall(x);
	while(nroot(x)) {
		int fa=f[x];
		if(nroot(fa)) rotate((get(x)!=get(fa))?x:fa);
		rotate(x);
	}
	pushup(x);
}

inline void access(int x) {
	for(register int fa=0 ; x ; x=f[fa=x]) splay(x),ch[x][1]=fa,pushup(x);
}

inline void makeroot(int x) {
	access(x),splay(x),tag[x]^=1;
}

inline void split(int x,int y) {
	makeroot(x),access(y),splay(y);
}

inline void link(int x,int y) {
	makeroot(x),f[x]=y;
}

inline void cut(int x,int y) {
	split(x,y),f[x]=ch[y][0]=0,pushup(y);
}

inline long long query_xor(int x) {
	long long ans=0;
	for(register int i=0 ; i<=30 ; ++i) ans+=1LL*((sum[x][i]&1)?(1<<i):0);
	return ans;
}

inline long long query_sum(int x) {
	long long ans=0;
	for(register int i=0 ; i<=30 ; ++i) ans+=1LL*(1<<i)*sum[x][i];
	return ans;
}

inline long long query_or(int x) {
	long long ans=0;
	for(register int i=0 ; i<=30 ; ++i) ans+=1LL*((sum[x][i])?(1<<i):0);
	return ans;
}

inline long long query_and(int x) {
	long long ans=0;
	for(register int i=0 ; i<=30 ; ++i) ans+=1LL*((sum[x][i]==size[x])?(1<<i):0);
	return ans;
}

int main() {
	int n=read(),q=read();
	for(register int i=1 ; i<=n ; ++i) {
		val[i]=read(),size[i]=1;
		for(register int j=0 ; j<=30 ; ++j) sum[i][j]=(bool)((1<<j)&val[i]);
	}
	char opt[10];
	while(q--) {
		scanf("%s",opt);
		int x=read(),y=read();
		if(opt[0]=='L') link(x,y);
		else if(opt[0]=='C') cut(x,y);
		else {
			split(x,y);
			if(opt[0]=='U') push(y,read());
			else if(opt[0]=='A') printf("%lld\n",query_and(y));
			else if(opt[0]=='O') printf("%lld\n",query_or(y));
			else if(opt[0]=='X') printf("%lld\n",query_xor(y));
			else printf("%lld\n",query_sum(y));
		}
	}
	return 0;
}
```

---

## 作者：hl666 (赞：0)

神仙@[TheLostWeak](https://www.luogu.org/space/show?uid=28382)出的题，因为他最近没时间所以我先写一下sol（其实我也没什么时间）

作为一道~~简单~~的数据结构题想必大家都能看出必须用**LCT**维护信息吧

一个朴素的想法就是直接维护四种操作的值，但是这样修改除了异或好像都不能维护

既然一个$\log$不可行那么就大力两个$\log$吧，很容易想到直接把信息拆分成二进制来存，然后记一下子树内所有数每一位上$1$的个数和

同时我们再维护一个子树大小，那么对于每种询问时直接大力枚举每一位的情况判断即可：

- ```and```：判断这一位上$1$的个数是否等于子树大小
- ```or```：判断这一位上是否有$1$
- ```xor```：判断这一位上$1$的个数的奇偶性
- ```sum```：大力累加起来就好了

具体的，修改的时候由于是异或操作，因此直接把对应要变的那一位$0,1$的个数调换，即用子树大小减去$1$的个数

然后还需要下传标记，这个直接**lazy tag**维护一下就好了，类似于[Luogu P1501 [国家集训队]Tree II](https://www.luogu.org/problemnew/show/P1501)

然后我们就把这道水水的送分题写完了，LCT由于是板子所以会比较长，其实是核心代码是很短的

CODE

```cpp
#include<cstdio>
#include<cctype>
#define RI register int
#define CI const int&
#define Tp template <typename T>
using namespace std;
typedef long long LL;
const int N=100005,RG=30;
int n,m,val[N],x,y,z; char opt;
class FileInputOutput
{
    private:
        static const int S=1<<21;
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
        #define pc(ch) (Ftop<S?Fout[Ftop++]=ch:(fwrite(Fout,1,S,stdout),Fout[(Ftop=0)++]=ch))
        char Fin[S],Fout[S],*A,*B; int Ftop,pt[25];
    public:
        Tp inline void read(T& x)
        {
            x=0; char ch; while (!isdigit(ch=tc()));
            while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));
        }
        inline void get_alpha(char& ch)
        {
            while (!isalpha(ch=tc()));
        }
        Tp inline void write(T x)
        {
            if (!x) return (void)(pc('0'),pc('\n')); RI ptop=0;
            while (x) pt[++ptop]=x%10,x/=10; while (ptop) pc(pt[ptop--]+48); pc('\n');
        }
        inline void Fend(void)
        {
            fwrite(Fout,1,Ftop,stdout);
        }
        #undef tc
        #undef pc
}F;
class Link_Cut_Tree
{
    private:
        struct splay
        {
            int ch[2],fa,s[RG],size,tag; bool rev;
        }node[N]; int stack[N],top;
        #define lc(x) node[x].ch[0]
        #define rc(x) node[x].ch[1]
        #define fa(x) node[x].fa
        #define S(x,y) node[x].s[y]
        #define SZ(x) node[x].size
        #define R(x) node[x].rev
        #define T(x) node[x].tag
        inline void swap(int& x,int& y)
        {
            int t=x; x=y; y=t;
        }
        inline void rever(CI now)
        {
            swap(lc(now),rc(now)); R(now)^=1;
        }
        inline void upt(CI now,CI xv)
        {
            for (RI i=0;i<RG;++i) if ((xv>>i)&1)
            S(now,i)=SZ(now)-S(now,i); val[now]^=xv; T(now)^=xv;
        }
        inline void pushup(CI now)
        {
            SZ(now)=SZ(lc(now))+SZ(rc(now))+1; for (RI i=0;i<RG;++i)
            S(now,i)=S(lc(now),i)+S(rc(now),i)+((val[now]>>i)&1);
        }
        inline void pushdown(CI now)
        {
            if (R(now)) rever(lc(now)),rever(rc(now)),R(now)=0;
            if (T(now)) upt(lc(now),T(now)),upt(rc(now),T(now)),T(now)=0;
        }
        inline int identify(CI now)
        {
            return rc(fa(now))==now;
        }
        inline void connect(CI x,CI y,CI d)
        {
            node[fa(x)=y].ch[d]=x;
        }
        inline bool isroot(CI now)
        {
            return lc(fa(now))!=now&&rc(fa(now))!=now;
        }
        inline void rotate(CI now)
        {
            int x=fa(now),y=fa(x),d=identify(now); if (!isroot(x)) node[y].ch[identify(x)]=now;
            fa(now)=y; connect(node[now].ch[d^1],x,d); connect(x,now,d^1); pushup(x); pushup(now);
        }
        inline void splay(int now)
        {
            int t=now; while (stack[++top]=t,!isroot(t)) t=fa(t);
            while (top) pushdown(stack[top--]); for (;!isroot(now);rotate(now))
            t=fa(now),!isroot(t)&&(rotate(identify(now)!=identify(t)?now:t),0);
        }
        inline void access(int x)
        {
            for (int y=0;x;x=fa(y=x)) splay(x),rc(x)=y,pushup(x);
        }
        inline void makeroot(CI now)
        {
            access(now); splay(now); rever(now);
        }
        inline int findroot(int now)
        {
            for (access(now),splay(now);lc(now);now=lc(now)) pushdown(now); return splay(now),now;
        }
        inline void split(CI x,CI y)
        {
            makeroot(x); access(y); splay(y);
        }
    public:
        inline void build(void)
        {
            for (RI i=1;i<=n;++i) for (RI j=0;j<RG;++j) S(i,j)=(val[i]>>j)&1;
        }
        inline void link(CI x,CI y)
        {
            makeroot(x); if (findroot(y)!=x) fa(x)=y;
        }
        inline void cut(CI x,CI y)
        {
            makeroot(x); if (findroot(y)==x&&fa(y)==x&&!lc(y)) rc(x)=fa(y)=0; pushup(x);
        }
        inline void modify_xor(CI x,CI y,CI z)
        {
            split(x,y); upt(y,z);
        }
        inline int query_and(CI x,CI y,int ret=0)
        {
            split(x,y); for (RI i=0;i<RG;++i)
            if (S(y,i)==SZ(y)) ret|=1<<i; return ret;
        }
        inline int query_or(CI x,CI y,int ret=0)
        {
            split(x,y); for (RI i=0;i<RG;++i)
            if (S(y,i)) ret|=1<<i; return ret;
        }
        inline int query_xor(CI x,CI y,int ret=0)
        {
            split(x,y); for (RI i=0;i<RG;++i)
            if (S(y,i)&1) ret|=1<<i; return ret;
        }
        inline LL query_sum(CI x,CI y,LL ret=0)
        {
            split(x,y); for (RI i=0;i<RG;++i)
            ret+=1LL*(1<<i)*S(y,i); return ret;
        }
        #undef lc
        #undef rc
        #undef fa
        #undef S
        #undef SZ
        #undef R
        #undef T
}LCT;
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    RI i; for (F.read(n),F.read(m),i=1;i<=n;++i) F.read(val[i]);
    for (LCT.build(),i=1;i<=m;++i)
    {
        F.get_alpha(opt); F.read(x); F.read(y);
        switch (opt)
        {
            case 'L':
                LCT.link(x,y); break;
            case 'C':
                LCT.cut(x,y); break;
            case 'U':
                F.read(z); LCT.modify_xor(x,y,z); break;
            case 'A':
                F.write(LCT.query_and(x,y)); break;
            case 'O':
                F.write(LCT.query_or(x,y)); break;
            case 'X':
                F.write(LCT.query_xor(x,y)); break;
            case 'S':
                F.write(LCT.query_sum(x,y)); break;
        }
    }
    return F.Fend(),0;
}
```

---

