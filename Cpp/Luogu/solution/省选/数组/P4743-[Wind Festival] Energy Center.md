# [Wind Festival] Energy Center

## 题目背景

$[Noon - 12:13$ $P.M.]$

$Curtis$ $Nishikino$看到大家为晚会准备地如此认真，~~可爱的~~她也做起了志愿者！

## 题目描述

$Curtis$ $Nishikino$来到了风筝节的能源中心，大家正在为晚会做准备. 这里共有 $N$ 台设备. 当然，由于计划的调整，可能会随时发生增删设备的操作. 但设备的总数不会超过$10^4$. 随时记录设备的数量也是志愿者的工作之一.

每台设备都有一些属性，比如设备$i$, 对于她拥有的每个属性, 比如属性$j$, 都会有一个给定的值, 记为$value_{ij}$.但属性是共有的, 这意味着即便一台设备没有某个属性, 也只会使她这个属性的值为$0$. 属性的数量是$M$. 注意属性的编号是从$0$到$M-1$.

现在志愿者们正尝试将一部分相邻设备联系在一起，效果如下：

- 对于从$j$到$k$的设备, 最终效果$i$的值为 $\sum_{p=j}^{k}value_{pi}$.

志愿者需要$Curtis$帮忙，但做计算太麻烦了，$Curtis$ $Nishikino$也希望你能帮帮她.

## 说明/提示

对于 $15\%$ 的数据, $0 < N \le 10^3\ , \ 0<M \le 10\ , \ 0 < q \le 10^3$.

对于额外的 $5\%$ 数据, $0<N \le 10^4\ , \ 0<M \le 200\ , \ 0 < q \le 10^4$, 保证没有 $QS$ 操作.

对于 $100\%$ 的数据, $0<N \le 10^4\ ,\ 0<M \le 200\ , \ 0<q\le10^4$.

## 样例 #1

### 输入

```
4 4
4 0 1 1 2 2 2 3 1
2 0 1 2 1
0
2 1 2 3 1
5
QA
I 2 
2 1 1 3 2
QS 2 4
QA
QS 1 1```

### 输出

```
4
1 1 1 2
5
1 2 2 1
end```

# 题解

## 作者：niiick (赞：3)

~~抢到第一篇题解啦~~

很裸的splay，然而还是没明白为什么出题人把这题排最简单，可能是蒟蒻我想太复杂了

一开始建立splay要加两个哨兵(烧饼)结点1和n+2，
原始的每个设备序列编号加1，令n+=2

$I \ x$操作，在splay tree中找到**第x+1个**结点x旋转到根，找到**第x+2个**结点y旋转到根的右子树，
新节点编号为++n，将其作为y的左子树，更新y和x维护的值

$D \ x$操作，在splay tree中找到**第x个**结点x旋转到根，找到**第x+2个**结点y旋转到根的右子树
断掉y的左子树

$QA$操作，用一个变量rem记录删掉了多少节点就好，输出n-2-rem

$QS\ ll\ rr$操作，在splay tree中找到**第ll个**结点x旋转到根，找到**第rr+2个**结点y旋转到根的右子树，输出y的左子树维护的值

```
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;
typedef double dd;

int read()
{
    int f=1,x=0;
    char ss=getchar();
    while(ss<'0'||ss>'9'){if(ss=='-')f=-1;ss=getchar();}
    while(ss>='0'&&ss<='9'){x=x*10+ss-'0';ss=getchar();}
    return f*x;
}

const int maxn=30010;
int n,m;
int a[maxn][210];
int rt,ch[maxn][2],fa[maxn],rem;
int val[maxn][210],size[maxn];

void update(int p)
{
    int lc=ch[p][0],rc=ch[p][1];
    size[p]=size[lc]+size[rc]+1;
    for(int i=1;i<=m;++i)
    val[p][i]=val[lc][i]+val[rc][i]+a[p][i];
}

void build(int p,int ll,int rr)
{
    if(ll>rr) return;
    int mid=ll+rr>>1;
    fa[mid]=p; size[mid]=1;
    ch[p][mid>p]=mid;
    if(ll==rr)
    {
        for(int i=1;i<=m;++i)val[ll][i]=a[ll][i];
        return;
    }
    build(mid,ll,mid-1); build(mid,mid+1,rr);
    update(mid);
}

void rotate(int &p,int x)
{
    int y=fa[x],z=fa[y];
    int d=(ch[y][0]==x);
    if(y==p) p=x;
    else if(ch[z][0]==y) ch[z][0]=x;
    else ch[z][1]=x;
    fa[y]=x; fa[ch[x][d]]=y; fa[x]=z;
    ch[y][d^1]=ch[x][d]; ch[x][d]=y;
    update(y); update(x);
}

void splay(int &p,int x)
{
    while(x!=p)
    {
        int y=fa[x],z=fa[y];
        if(y!=p)
        {
            if((ch[z][0]==y)^(ch[y][0]==x))rotate(p,x);
            else rotate(p,y);
        }
        rotate(p,x);
    }
}

int find(int p,int k)
{
    int ss=size[ch[p][0]];
    if(k==ss+1) return p;
    else if(k<=ss) return find(ch[p][0],k);
    else return find(ch[p][1],k-ss-1);
}

void ins(int k)
{
    int x=find(rt,k+1); splay(rt,x);
    int y=find(rt,k+2); splay(ch[x][1],y);
    
    ch[y][0]=n; fa[n]=y; size[n]=1;
    for(int i=1;i<=m;++i) val[n][i]=a[n][i];
    update(y); update(x);
}

void del(int k)
{
    int x=find(rt,k); splay(rt,x);
    int y=find(rt,k+2); splay(ch[x][1],y);
    
    fa[ch[y][0]]=0; ch[y][0]=0;
    update(y); update(x); rem++;
}

void get(int ll,int rr)
{
    int x=find(rt,ll); splay(rt,x);
    int y=find(rt,rr+2); splay(ch[x][1],y);
    
    for(int i=1;i<=m;++i)
    printf("%d ",val[ch[y][0]][i]);
    printf("\n");
}

int main()
{
    n=read();m=read();
    for(int i=2;i<=n+1;++i)
    {
        int k=read();
        while(k--)
        {
            int x=read()+1,y=read();
            a[i][x]=y;
        }
    }
    rt=n+3>>1; 
    build(rt,1,n+2); n+=2;
    
    int q=read();
    while(q--)
    {
        char ss[5]; scanf("%s",&ss);
        if(ss[0]=='I')
        {
            int p=read(),k=read(); ++n;
            while(k--)
            {
                int x=read()+1,y=read();
                a[n][x]=y;
            }
            ins(p);
        }
        else if(ss[0]=='D') del(read());
        else if(ss[0]=='Q'&&ss[1]=='A') printf("%d\n",n-2-rem);
        else if(ss[0]=='Q'&&ss[1]=='S') 
        {
            int ll=read(),rr=read();
            get(ll,rr);
        }
    }
    printf("end");
    return 0;
    //niiick
}
```

---

## 作者：黑影洞人 (赞：0)

DS 超级大水题，但是我没看清数据范围 RE 了两次。

题目让我们维护一个矩阵，每一列为一个单位。

数据规模 $10^4\times10^2\times$ 大常数。

我的做法就是对于每一列暴力 pushup，然后码一个 fhq-treap 的模板。

```cpp
#define lc ch[x][0]
#define rc ch[x][1]
int pushup(int x){
	siz[x]=siz[lc]+siz[rc]+1;
	for(int i=1;i<=m;i++)sum[x][i]=sum[lc][i]+sum[rc][i]+val[x][i];
	return x;
}
```
然后新节点的建立也有点不一样，观察到新节点的输入格式相似，我们可以直接写一个函数，大大减少码量。

$I x$ 操作就是把 $x$ 前面的段 `split` 出来，然后 `merge` 上一个 `newnode`。

$D x$ 操作就是单独分离出 $x$，然后合并的时候忽略 $x$。

$QA$ 这个操作直接输出 $t.siz[rt]$ 即树节点个数。

$QS$ $l,r$ 这个把 $[l,r]$ 分离出来，然后循环 $m$ 次输出答案即可。
```cpp
int newnode(){
	int x=++tot;
	int k;
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		a++;
		val[x][a]=sum[x][a]=b;
	}
	siz[x]=1;rnd[x]=_rand();
	return x;
}
```
完整代码，别忘记加上 "end"：
```cpp
#include<cstdio>
#include<algorithm>
#define N 5145
using namespace std;
int seed,md=19260817;
void _srand(int x){seed=x;}
int _rand(){seed=((seed*7)%md+13)%md;return seed;}
int n,m,q,rt;
struct fhqtreap{
	int ch[N][2],siz[N],rnd[N],tot;
	int val[N][205],sum[N][205];
	#define lc ch[x][0]
	#define rc ch[x][1]
	int pushup(int x){
		siz[x]=siz[lc]+siz[rc]+1;
		for(int i=1;i<=m;i++)sum[x][i]=sum[lc][i]+sum[rc][i]+val[x][i];
		return x;
	}
	void split(int p,int k,int &x,int &y){
		if(!p)return void(x=y=0);
		if(siz[ch[p][0]]<k)split(ch[x=p][1],k-siz[ch[p][0]]-1,ch[p][1],y);
		else split(ch[y=p][0],k,x,ch[p][0]);
		pushup(p);
	}
	int merge(int x,int y){
		if(!x||!y)return x+y;
		if(rnd[x]<rnd[y]){rc=merge(rc,y);return pushup(x);}
		else{ch[y][0]=merge(x,ch[y][0]);return pushup(y);}
	}
	int newnode(){
		int x=++tot;
		int k;
		scanf("%d",&k);
		for(int i=1;i<=k;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			a++;
			val[x][a]=sum[x][a]=b;
		}
		siz[x]=1;rnd[x]=_rand();
		return x;
	}
}t;
signed main(){
	_srand(114514);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)rt=t.merge(rt,t.newnode());
	scanf("%d",&q);
	while(q--){
		char s[10];
		int l,r,x;
		scanf("%s",s);
		if(s[0]=='I'){
			scanf("%d",&x);
			int a,b;
			t.split(rt,x,a,b);
			rt=t.merge(a,t.merge(t.newnode(),b));
		}else if(s[0]=='D'){
			scanf("%d",&x);
			int a,b,c;
			t.split(rt,x-1,a,b);
			t.split(b,1,b,c);
			rt=t.merge(a,c);
		}else if(s[0]=='Q'&&s[1]=='S'){
			scanf("%d%d",&l,&r);
			int a,b,c;
			t.split(rt,r,a,b);
			t.split(a,l-1,a,c);
			for(int i=1;i<=m;i++)printf("%d ",t.sum[c][i]);
			puts("");
			rt=t.merge(a,t.merge(c,b));
		}else if(s[0]=='Q'&&s[1]=='A')printf("%d\n",t.siz[rt]);
	}
	puts("end");
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：0)

~~语文题（~~

题意：给定 $1\times m$ 矩阵列 $\{a_n\}$，维护单点插入，单点删除，矩阵列长度，区间和。
# 思路
用平衡树维护之，考虑经典平衡树五问：
### 节点信息
因为我们写的是 FHQ，所以要记录左右孩子、两个权值、子树大小。

因为要维护区间和，所以要记录子树和。
### 节点标记 & 下传标记 & 区间修改
没有区间修改，不考虑。
### 上传信息
正常更新子树大小。子树和 = 左子树和 + 右子树和 + 节点本身矩阵。

于是我们可以写出：
```cpp
#define F for(int i = 0;i < m;++i)
inline int R()
{
    int r = 0;char c = getchar();while(!isdigit(c)) c = getchar();
    while(isdigit(c)) r = r * 10 + c - '0', c = getchar();return r;
}
void P(int x) {if(x >= 10) P(x / 10);putchar(x % 10 + '0');}
struct T
{
    T *l, *r;int k, s, v[200], q[200];T() : l(0), r(0), k(rand()), s(1)
    {
        memset(v, 0, m << 2);memset(q, 0, m << 2);g =
        R();while(g--) x = R(), y = R(), v[x] = q[x] = y;
    }
    void u()
    {
        s = 1;memcpy(q, v, m << 2);if(l) {F q[i] += l->q[i];
        s += l->s;}if(r) {F q[i] += r->q[i];s += r->s;}
    }
}*r, *a, *b, *c, *s[30];
void S(T *x, int k, T *&a, T *&b)
{
    if(!x) {a = b = 0;return;}if(!k) {a = 0;b = x;return;}
    if(k >= x->s) {a = x;b = 0;return;}int z = x->l ? x->l->s
    : 0;if(z >= k) b = x, S(x->l, k, a, b->l), b->u();
    else a = x, S(x->r, k - z - 1, a->r, b), a->u();
}
T *M(T *a, T *b)
{
    if(!a) return b;if(!b) return a;if(a->k <
    b->k) {a->r = M(a->r, b);a->u();return a;}
    else {b->l = M(a, b->l);b->u();return b;}
}
```
（可以选择）用笛卡尔树优化建树过程。
```cpp
for(int i = 1;i <= n;++i, s[l++] = a)
{
    a = new T;k = a->k;p = l;while(l && k < s[l - 1]->k)
    s[--l]->u();if(l < p) a->l = s[l];if(l) s[l - 1]->r = a;
}
while(l) s[--l]->u();r = s[0];
```
分别处理每种操作。
```cpp
while(q--)
{
    scanf("%s", o);switch(o[0])
    {
        case 'I': S(r, R(), a, b);r = M(a, M(new T, b));break;
        case 'D': S(r, R() - 1, a, b);S(b, 1, b, c);delete b;r = M(a, c);break;
        case 'Q': if(o[1] == 'A') P(r->s);else {x = R();y = R();S(r, y, a, c);S(a,
        x - 1, a, b);F P(b->q[i]), putchar(' ');r = M(a, M(b, c));}puts("");break;
    }
}
```
这题做完了。
# Code
```cpp
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#define F for(int i = 0;i < m;++i)
inline int R()
{
    int r = 0;char c = getchar();while(!isdigit(c)) c = getchar();
    while(isdigit(c)) r = r * 10 + c - '0', c = getchar();return r;
}
void P(int x) {if(x >= 10) P(x / 10);putchar(x % 10 + '0');}
int n, m, q, l, k, p, g, x, y;char o[3];struct T
{
    T *l, *r;int k, s, v[200], q[200];T() : l(0), r(0), k(rand()), s(1)
    {
        memset(v, 0, m << 2);memset(q, 0, m << 2);g =
        R();while(g--) x = R(), y = R(), v[x] = q[x] = y;
    }
    void u()
    {
        s = 1;memcpy(q, v, m << 2);if(l) {F q[i] += l->q[i];
        s += l->s;}if(r) {F q[i] += r->q[i];s += r->s;}
    }
}*r, *a, *b, *c, *s[30];
void S(T *x, int k, T *&a, T *&b)
{
    if(!x) {a = b = 0;return;}if(!k) {a = 0;b = x;return;}
    if(k >= x->s) {a = x;b = 0;return;}int z = x->l ? x->l->s
    : 0;if(z >= k) b = x, S(x->l, k, a, b->l), b->u();
    else a = x, S(x->r, k - z - 1, a->r, b), a->u();
}
T *M(T *a, T *b)
{
    if(!a) return b;if(!b) return a;if(a->k <
    b->k) {a->r = M(a->r, b);a->u();return a;}
    else {b->l = M(a, b->l);b->u();return b;}
}
int main()
{
    n = R();m = R();for(int i = 1;i <= n;++i, s[l++] = a)
    {
        a = new T;k = a->k;p = l;while(l && k < s[l - 1]->k)
        s[--l]->u();if(l < p) a->l = s[l];if(l) s[l - 1]->r = a;
    }
    while(l) s[--l]->u();r = s[0];q = R();while(q--)
    {
        scanf("%s", o);switch(o[0])
        {
            case 'I': S(r, R(), a, b);r = M(a, M(new T, b));break;
            case 'D': S(r, R() - 1, a, b);S(b, 1, b, c);delete b;r = M(a, c);break;
            case 'Q': if(o[1] == 'A') P(r->s);else {x = R();y = R();S(r, y, a, c);S(a,
            x - 1, a, b);F P(b->q[i]), putchar(' ');r = M(a, M(b, c));}puts("");break;
        }
    }
    return puts("end"), 0;
}
```



---

## 作者：G我就是菜G (赞：0)

# 本题 $FHQ\;Teap$ 写法

裸的 $fhq\; Treap$ 只不过把每个节点用结构体储存，保存每个 $value_i$ 就行了，多一个结构体 $sum[i]$ 表示以 $i$ 为根的子树的每个状态之和，分裂要用排名分裂,查询时将整棵树分成三段，返回中间一段 $l$ 到 $r$ 的信息就行了

最开始插入一个空节点，其 $heap$ 值为 $-INT\_MAX$ 后面每次插入或删除的位置都要加 $1$ ,询问机器个数时就输出 $size[root]-1$ 就行了

### 代码如下:

```cpp
#include <bits/stdc++.h>
#define random(x) rand()*rand()%x;
#define INF random(30000010)+10000010
#define N 50010

using namespace std;

struct node{
	int num[210];
	void clean() {memset(num,0,sizeof(num));}
}xx,sum[N],t[N];

int n,m,T,x,y,_x,X,a,b,cnt,root,l,r;
int son[N][2],heap[N],size[N];
char c;

void add(node x) {t[++cnt]=x,sum[cnt]=x,size[cnt]=1,heap[cnt]=random(INF);}

void update(int x)    		\\更新节点时别忘记更新sum值
{
	size[x]=size[son[x][0]]+size[son[x][1]]+1;
	for (int i=0;i<m;i++)
		sum[x].num[i]=t[x].num[i]+sum[son[x][0]].num[i]+sum[son[x][1]].num[i];
}

void split(int now,int &a,int &b,int val)	\\排名分裂
{
    if (now==0) {a=0,b=0;return;}
    if (size[son[now][0]]+1<=val) a=now,split(son[now][1],son[a][1],b,val-size[son[now][0]]-1);
    else b=now,split(son[now][0],a,son[b][0],val);
    update(now);
}

void merge(int &now,int a,int b)
{
    if (a==0 || b==0) {now=a+b;return;}
    if (heap[a]<heap[b]) now=a,merge(son[now][1],son[a][1],b);
    else now=b,merge(son[now][0],a,son[b][0]);
    update(now);
}

void insert(int val)
{
    int x=0,y=0;
    add(xx);
    int o=cnt;
    split(root,x,y,val);
    merge(x,x,o);merge(root,x,y);
}

void del(int val)
{
	int x=0,y=0,o=0;
	split(root,x,y,val);split(x,x,o,val-1);
	merge(o,son[o][0],son[o][1]);
	merge(x,x,o),merge(root,x,y);
}					\\普通的 fhq Treap

node query(int l,int r)			\\询问区间信息，返回一个结构体
{
	int x=0,y=0,o=0;
	split(root,x,y,l);split(y,y,o,r-l+1);		\\注意由于插入了一个空节点，区间整体向后移一个单位
	node xx=sum[y];
	merge(y,y,o),merge(root,x,y);
	return xx;
}

void write(node x)			\\将返回的结构体输出
{
	for (int i=0;i<m;i++) printf("%d ",x.num[i]);
	printf("\n");
	return;
}

int main()
{
	scanf("%d%d",&n,&m);
	add(xx),root=1,heap[1]=-INT_MAX;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&_x);
		xx.clean();
		for (int j=1;j<=_x;j++)
			scanf("%d%d",&x,&y),xx.num[x]=y;
		insert(i);
	}
	scanf("%d",&T);
	while (T--)
	{
		c=getchar();
		while (c<'A' || c>'Z') c=getchar();
		if (c=='I')
		{
			scanf("%d",&X);
			scanf("%d",&_x);
			xx.clean();
			for (int j=1;j<=_x;j++)
				scanf("%d%d",&x,&y),xx.num[x]=y;
			insert(X+1);
		}
		else if (c=='D') scanf("%d",&x),del(x+1);
		else
		{
			c=getchar();
			if (c=='A') printf("%d\n",size[root]-1);
			else scanf("%d%d",&l,&r),write(query(l,r));
		}
	}
	printf("end\n");		\\别忘记输出 end
	return 0;
}
```

---

