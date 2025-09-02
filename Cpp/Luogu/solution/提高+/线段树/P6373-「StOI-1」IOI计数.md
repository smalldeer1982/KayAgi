# 「StOI-1」IOI计数

## 题目背景

蒻`L_C_A`想了解一下`IOI`，可他太菜了，看不懂题目，只会数数。

## 题目描述

给定一个长度为 $n$ 字符串 $S$ ，同时进行 $m$ 次操作：      
操作1：$1$ $x$ $c$ 表示将第 $x$ 个字符改为 $c$（ $c$ 只会为 `I` 或 `O` ）。       
操作2：$2$ $l$ $r$ 询问字符串 $S$ 中有多少对三元组 $(i,j,k)$ 满足：   
$S_{i}=$ `I` ,$S_{j}=$ `O` ,$S_{k}=$ `I` 并且 $l≤i<j<k≤r$ 。

## 说明/提示

对于 $20$% 的数据：$1 ≤ n,m ≤ 100$，$1 ≤ l ≤ r ≤ n$；  
对于另 $20$% 的数据：$1 ≤ n ≤ $ $10^{5}$，$m = 1$，$ 1 ≤ l ≤ r ≤ n$；    
对于另 $20$% 的数据：$1 ≤ n,m ≤  $ $10^{5}$，$l=1,r=n$；   
对于 $100$% 的数据：$1 ≤ n,m ≤ $ $5$ $\times$ $10^{5}$，$1 ≤ l ≤ r ≤ n$。

所有数据保证合法。


## 样例 #1

### 输入

```
4 3
IOOI
2 1 4
1 1 O
2 1 2```

### 输出

```
2
0```

## 样例 #2

### 输入

```
10 10
IIOOIOIIIO
1 1 I
2 1 7
1 5 O
2 5 9
1 4 I
1 10 I
2 1 10
2 5 10
2 2 8
2 3 9```

### 输出

```
11
0
34
0
11
6
```

# 题解

## 作者：1kri (赞：17)

#### ~~GF~~官方题解

普及组线段树（¿）。

每个节点保存 `I`、`O`、`IO`、`OI`、`IOI` 的个数，基于乘法原理转移即可。

当前`I`的个数 = 左区间`I`的个数 + 右区间`I`的个数。

当前`O`的个数同理。

当前`IO`的个数 = 左区间`IO`的个数 + 右区间`IO`的个数 + 左区间`I`的个数 $\times$ 右区间`O`的个数。

当前`OI`的个数同理。

当前`IOI`的个数 = 左区间`IOI`的个数 + 右区间`IOI`的个数 + 左区间`I`的个数 $\times$ 右区间`OI`的个数 + 左区间`IO`的个数 $\times$ 右区间`I`的个数。

然后是并不很难的代码。

```cpp
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
int n,m,a[500005];
char s[500005];
struct node{
	ll i,o,oi,io,ioi;
	inline void mem(){
		i=o=oi=io=ioi=0;
	}
}tree[4000005];
inline node add(register node a,register node b){
	register node c;
	c.mem();
	c.i=a.i+b.i;
	c.o=a.o+b.o;
	c.oi=a.oi+b.oi+a.o*b.i;
	c.io=a.io+b.io+a.i*b.o;
	c.ioi=a.ioi+b.ioi+a.i*b.oi+a.io*b.i;
	return c;
}
inline void pushup(register int now){
	tree[now]=add(tree[now*2],tree[now*2+1]);
	return;
}
inline void update(register int now,register int nowl,register int nowr,register int pos,register int k){
	if (nowl==nowr){
		tree[now].mem();
		if (k==0)tree[now].i=1;
		else tree[now].o=1;
		return;
	}
	register int mid=(nowl+nowr)/2;
	if (pos<=mid)update(now*2,nowl,mid,pos,k);
	else update(now*2+1,mid+1,nowr,pos,k);
	pushup(now);
	return;
}
inline node query(register int now,register int nowl,register int nowr,register int lt,register int rt){
	if (nowl>=lt&&nowr<=rt)return tree[now];
	register int mid=(nowl+nowr)/2;
	register node s;s.mem();
	if (mid>=lt)s=add(s,query(now*2,nowl,mid,lt,rt));
	if (mid+1<=rt)s=add(s,query(now*2+1,mid+1,nowr,lt,rt));
	return s;
}
inline void build(register int now,register int nowl,register int nowr){
	tree[now].mem();
	if (nowl==nowr){
		if (a[nowl]==0)tree[now].i=1;
		else tree[now].o=1;
		return;
	}
	int mid=(nowl+nowr)/2;
	build(now*2,nowl,mid);
	build(now*2+1,mid+1,nowr);
	pushup(now);
	return;
}
int main(){
	cin>>n>>m;
	scanf("%s",s+1);
    for (int i=1;i<=n;i++){
        if (s[i]=='I')a[i]=0;
        else a[i]=1;
    }
	build(1,1,n);
	for (int i=1;i<=m;i++){
		int flag;
		scanf("%d",&flag);
		if (flag==1){
			int x,c;
			char ch[5];
			scanf("%d%s",&x,ch);
			if (ch[0]=='I')c=0;
			else c=1;
			update(1,1,n,x,c);
		}
		else{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%lld\n",query(1,1,n,l,r).ioi);
		}
	}
	return 0;
}
```

---

## 作者：ix35 (赞：8)

抢先写一个无脑动态 DP 解法。

设 $dp(i,0),dp(i,1),dp(i,2)$ 分别表示前 $i$ 个字符中 $\texttt{I},\texttt{IO},\texttt{IOI}$ 作为子序列出现的次数。

如果 $s_i=\texttt{I}$，那么转移：

$$dp(i,0)=dp(i-1,0)+1$$

$$dp(i,1)=dp(i-1,1)$$

$$dp(i,2)=dp(i-1,2)+dp(i-1,1)$$

如果 $s_i=\texttt{O}$，那么转移：

$$dp(i,0)=dp(i-1,0)$$

$$dp(i,1)=dp(i-1,1)+dp(i-1,0)$$

$$dp(i,2)=dp(i-1,2)$$

把转移写成矩阵形式。

用四维向量 $\begin{bmatrix}dp(i,0)\\ dp(i,1)\\ dp(i,2)\\ 1\end{bmatrix}$ 表示一个状态，那么对于 $\texttt{I}$ 的转移矩阵：

$$Mat_{I}=\begin{bmatrix}1\ \ 0\ \ 0\ \ 0\\ 0 \ \ 1\ \ 1\ \ 0\\ 0\ \ 0\ \ 1\ \ 0\\ 1\ \ 0\ \ 0\ \ 1\end{bmatrix}$$

对于 $\texttt{O}$ 的转移矩阵：

$$Mat_{O}=\begin{bmatrix}1\ \ 1\ \ 0\ \ 0\\ 0 \ \ 1\ \ 0\ \ 0\\ 0\ \ 0\ \ 1\ \ 0\\ 0\ \ 0\ \ 0\ \ 1\end{bmatrix}$$

然后我们用线段树维护区间矩阵乘积即可实现区间询问和单点修改。


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=500010;
struct Mat {
	Mat () {memset(v,0,sizeof(v));}
	ll v[4][4];
	Mat operator * (Mat b) {
		Mat c;
		for (int i=0;i<=3;i++) {
			for (int j=0;j<=3;j++) {
				for (int k=0;k<=3;k++) {c.v[i][j]+=v[i][k]*b.v[k][j];}
			}
		}
		return c;
	}
	void print () {
		for (int i=0;i<=3;i++) {
			for (int j=0;j<=3;j++) {printf("%d  ",v[i][j]);}
		printf("\n");
		}
		return;
	}
}_i,_o,_e,v[MAXN<<2];
int n,m,op,x,y;
char c[3],s[MAXN];
void buildt (int p,int l,int r) {
	if (l==r) {v[p]=(s[l]=='I'?_i:_o);return;}
	int mid=(l+r)>>1;
	buildt(p<<1,l,mid),buildt((p<<1)|1,mid+1,r);
	v[p]=v[p<<1]*v[(p<<1)|1];
	//printf("%d  %d  %d\n",p,l,r);
	//v[p].print();
	return;
}
Mat query (int p,int l,int r,int xl,int xr) {
	if (xr<l||r<xl) {return _e;}
	if (xl<=l&&r<=xr) {return v[p];}
	int mid=(l+r)>>1;
	return query(p<<1,l,mid,xl,xr)*query((p<<1)|1,mid+1,r,xl,xr);
}
void modify (int p,int l,int r,int pos,char c) {
	if (l==r) {v[p]=(c=='I'?_i:_o);return;}
	int mid=(l+r)>>1;
	if (pos<=mid) {modify(p<<1,l,mid,pos,c);}
	else {modify((p<<1)|1,mid+1,r,pos,c);}
	v[p]=v[p<<1]*v[(p<<1)|1];
	return;
}
int main () {
	_i.v[0][0]=_i.v[1][1]=_i.v[2][2]=_i.v[3][3]=_o.v[0][0]=_o.v[1][1]=_o.v[2][2]=_o.v[3][3]=1;
	_o.v[0][1]=_i.v[3][0]=_i.v[1][2]=1;
	_e.v[0][0]=_e.v[1][1]=_e.v[2][2]=_e.v[3][3]=1;
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	buildt(1,1,n);
	for (int i=1;i<=m;i++) {
		scanf("%d",&op);
		if (op==1) {
			scanf("%d%s",&x,c+1);
			if (c[1]==s[x]) {continue;}
			else {s[x]=c[1];}
			modify(1,1,n,x,c[1]);
		} else {
			scanf("%d%d",&x,&y);
			Mat ans=query(1,1,n,x,y);
			printf("%lld\n",ans.v[3][2]);
		}
	}
	return 0;
}
```






---

## 作者：Smallbasic (赞：4)

~~比赛时还以为是树状数组~~

实际上这是到线段树好题。

众所周知单点修改线段树的难点在于信息如何合并上传。

设$\text{I,O,IO,OI,IOI}$为它们在这个区间内出现的次数，则：

$$I=left->I+right->I$$

$$O=left->O+right->O$$

$$IO=left->IO+right->IO+left->I\times right->O$$

$$OI=left->OI+right->OI+left->O\times right->I$$

$$IOI=left->IOI+right->IOI+left->I\times right->OI+left->IO\times right->I$$

当然询问的时候不能直接左右儿子答案相加，依然要update，详见代码吧(我的的线段树是指针实现的)。

记得开long long

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

char ch[500005], c;
int n, m, opt, l, r;

struct node {
	int l, r, I, O, IO, OI, IOI;
	node *left = NULL;
	node *right = NULL;
	
	inline void update() {
		I = left -> I + right -> I;
		O = left -> O + right -> O;
		IO = left -> IO + right -> IO + left -> I * right -> O;
		OI = left -> OI + right -> OI + left -> O * right -> I;
		IOI = left -> IOI + right -> IOI + left -> I * right -> OI + left -> IO * right -> I;
	}
	
	inline void me() {
		I = O = IO = OI = IOI = 0;
	}
	
	inline void build(int l, int r) {
		this -> l = l; this -> r = r; me();
		if (l >= r) {
			if (ch[l] == 'I') I = 1;
			else O = 1;
			return ;
		}
		left = new node; left -> build(l, l + r >> 1); 
		right = new node; right -> build((l + r >> 1) + 1, r);
		update();
	}
	
	inline void modify(int l, char k) {
		if (this -> l >= this -> r) {
			I = O = IO = OI = IOI = 0;
			if (k == 'I') I =  1;
			else O = 1;
			return ;
		}
		if (left -> r >= l) left -> modify(l, k);
		else right -> modify(l, k);
		update();
	}
	
	inline node* query(int l, int r) {
		node *ret = new node; ret -> I = I; ret -> O = O; ret -> IO = IO; ret -> OI = OI; ret -> IOI = IOI;
		if (this -> l >= l && this -> r <= r ) return ret;
		if (left -> r >= l) ret -> left = left -> query(l, r);
		else { ret -> left = new node; ret -> left -> me(); }
		if (left -> r < r) ret -> right = right -> query(l, r);
		else { ret -> right = new node; ret -> right -> me(); }
		ret -> update(); delete ret -> left; delete ret -> right;
		return ret;
	}
};

int main() {
	scanf("%d%d", &n, &m); scanf("%s", ch + 1);
	node *root = new node; root -> build(1, n);
	while (m--) {
		scanf("%d%d", &opt, &l);
		if (opt == 1) {
			c = getchar(); while (c != 'I' && c != 'O') c = getchar();
			if (ch[l] == c) continue; ch[l] = c;
			root -> modify(l, c);
		} else {
			scanf("%d", &r); node *cur = root -> query(l, r);
			printf("%d\n", cur -> IOI); delete cur;
		}
	}
	return 0;
} 
```


---

## 作者：GIFBMP (赞：4)

### 正题

显然可以用线段树维护。

然后我们分类讨论，当两个区间合并时，```IOI``` 会有多少种情况？

1. ```IOI``` 都在左区间。
2. ```IOI``` 都在右区间。
3. ```IO``` 在左区间，```I``` 在右区间。
4. ```I``` 在左区间，```OI``` 在右区间。

于是，我们要维护每个区间内的 ```I```，```O```，```IO```，```OI```，```IOI``` 的数量。

转移很显然：

$$I_x=I_{lson}+I_{rson}$$

$$O_x=O_{lson}+O_{rson}$$

$$IO_x=IO_{lson}+IO_{rson}+I_{lson}\times O_{rson}$$

$$OI_x=OI_{lson}+OI_{rson}+O_{lson}\times I_{rson}$$

$$IOI_x=IOI_{lson}+IOI_{rson}+I_{lson}\times OI_{rson}+IO_{lson}\times I_{rson}$$

### Code：

```cpp
#include <cstdio>
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
using namespace std ;
typedef long long ll ;
const int MAXN = 5e5 + 10 ;
int n , m ;
char s[MAXN] ;
struct sgt {
	ll i , o , io , oi , ioi ;
	int l , r ;
	sgt () {i = io = oi = o = ioi = 0 ;}
} t[MAXN << 2] ;
void push_up (sgt &o , sgt x , sgt y) {
	o.i = x.i + y.i ;
	o.o = x.o + y.o ;
	o.io = x.io + y.io + x.i * y.o ;
	o.oi = x.oi + y.oi + x.o * y.i ;
	o.ioi = x.ioi + y.ioi + x.i * y.oi + x.io * y.i ;
}
void build_tree (int o , int l , int r) {
	t[o].l = l ; t[o].r = r ;
	if (l == r) {
		s[l] == 'I' ? t[o].i = 1 : t[o].o = 1 ;
		return ;
	}
	int mid = l + r >> 1 ;
	build_tree (lc(o) , l , mid) ;
	build_tree (rc(o) , mid + 1 , r) ;
	push_up (t[o] , t[lc(o)] , t[rc(o)]) ;
}
void update (int o , int x , char *ch) {
	if (t[o].l == t[o].r) {
		ch[0] == 'I' ? (t[o].i = 1 , t[o].o = 0) : (t[o].i = 0 , t[o].o = 1) ;
		return ;
	}
	int mid = t[o].l + t[o].r >> 1 ;
	if (x <= mid) update (lc(o) , x , ch) ;
	else update (rc(o) , x , ch) ;
	push_up (t[o] , t[lc(o)] , t[rc(o)]) ;
}
sgt query (int o , int x , int y) {
	if (x <= t[o].l && t[o].r <= y) 
		return t[o] ;
	int mid = t[o].l + t[o].r >> 1 ;
	sgt ret , tmp ;
	if (x <= mid) {
		tmp = query (lc(o) , x , y) ;
		push_up (ret , ret , tmp) ;
	}
	if (mid < y) {
		tmp = query (rc(o) , x , y) ;
		push_up (ret , ret , tmp) ;
	}
	return ret ;
}
int main () {
	scanf ("%d %d" , &n , &m) ;
	scanf ("%s" , s + 1) ;
	build_tree (1 , 1 , n) ;
	while (m--) {
		int opt , x , y ;
		char ch[5] ;
		scanf ("%d" , &opt) ;
		if (opt == 1) {
			scanf ("%d %s" , &x , ch) ;
			update (1 , x , ch) ;
		}
		else {
			scanf ("%d %d" , &x , &y) ;
			printf ("%lld\n" , query (1 , x , y).ioi) ;
		}
	}
	return 0 ;
}
```

---

## 作者：Hexarhy (赞：2)

### Preface

思路不难的线段树基础题，然而坑点还是不少的。

### Solution

直接讲正解。

刚开始看到单点修改和区间查询，第一感觉就是树状数组来维护。但是树状数组维护的是前缀和，自己瞎搞了几下发现很难维护。故考虑线段树维护。

根据计数原理，我们能轻松得到`IOI`的计算方式。其中，$k$ 表示当前节点，$L,R$ 分别表示当前节点的左右儿子。

- $\mathrm{I_k=I_L+I_R}$
- $\mathrm{O_k=O_L+O_R}$
- $\mathrm{IO_k=IO_L+IO_R+I_L\times O_R}$
- $\mathrm{OI_k=OI_L+OI_R+O_L\times I_R}$
- $\mathrm{IOI_k=IOI_L+IOI_R+IO_L\times I_R+I_L\times OI_R}$

用线段树维护上述五个值即可。

### Notice

思路不难，但是坑点还是不少的。

1. 上述维护的值要开`long long`。

1. 结构体还是要写上构造函数，赋初值为 $0$。

1. 由于特殊的计数方式，`query()`的时候统计答案也要使用上述规则。这个时候重载运算符`+`会显得方便很多。

1. 单点修改的时候，记得把另一个字母的统计的值变为 $0$。

1. 合并的时候，由于重载运算符的整体赋值，根节点的保存的`l,r`（即当前节点所维护的区间）会改变，因此要用一个临时变量保存。

1. 别忘了线段树数组开到 $4$ 倍。

1. 注意卡常。

### Code

本代码开了 O2 优化才能卡常通过……大概是自带大常数 debuff。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long ll;
typedef const int cint;
cint MAXN=5e5+5;
int n,m;
char ch[MAXN];

class segment_tree
{
private:
	struct node
	{
		int l,r;
		ll i,o,io,oi,ioi;
		node(ll L=0,ll R=0,ll I=0,ll O=0,ll IO=0,ll OI=0,ll IOI=0):l(L),r(R),i(I),o(O),io(IO),oi(OI),ioi(IOI){}; //构造函数，赋初始值为0
		node operator+(const node a)const//重载运算符
		{
			node res;
			res.i=i+a.i;
			res.o=o+a.o; 
			res.io=io+a.io+i*a.o;
			res.oi=oi+a.oi+o*a.i;
			res.ioi=ioi+a.ioi+i*a.oi+io*a.i; 
			return res;//注意这里会改变原来节点的l,r
		}
	}tree[MAXN<<2];//别忘了内存要开够
	void pushup(cint now)
	{
		node res;cint lson=now<<1,rson=now<<1|1;
		res=tree[lson]+tree[rson];
		res.l=tree[now].l;res.r=tree[now].r;//临时变量保存原来节点的l,r
		tree[now]=res;
	}
public:
	void build(cint now,cint l,cint r)//无坑点
	{
		tree[now].l=l;tree[now].r=r;
		if(l==r)
		{
			if(ch[l]=='I')	tree[now].i=1;
			if(ch[l]=='O')	tree[now].o=1;
			return;
		}
		cint mid=(l+r)>>1,lson=now<<1,rson=now<<1|1;
		build(lson,l,mid);
		build(rson,mid+1,r);
		pushup(now);
	}
	void modify(cint now,cint pos,const char c)
	{
		if(tree[now].l==tree[now].r && tree[now].l==pos)
		{
			if(c=='I')	tree[now].i=1,tree[now].o=0;//注意改变另一个字母的值
			if(c=='O')	tree[now].o=1,tree[now].i=0;
			return;
		}
		cint mid=(tree[now].l+tree[now].r)>>1,lson=now<<1,rson=now<<1|1;
		if(pos<=mid)	modify(lson,pos,c);
		else			modify(rson,pos,c);
		pushup(now);
	}
	node query(cint now,cint l,cint r)
	{
		if(l<=tree[now].l && tree[now].r<=r)
		 return tree[now];
		cint mid=(tree[now].l+tree[now].r)>>1,lson=now<<1,rson=now<<1|1;
		node res;//特殊的统计方式，用重载运算符+的优点体现在这里
		if(l<=mid)	res=res+query(lson,l,r);
		if(mid<r)	res=res+query(rson,l,r);
		return res;
	}
}t;

int main()
{
    ios_base::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
     cin>>ch[i];
    t.build(1,1,n);
    while(m--)
    {
    	int opt;cin>>opt;
    	if(opt==1)
    	{
    		int pos;char c;cin>>pos>>c;
    		t.modify(1,pos,c);
		}
		if(opt==2)
		{
			int l,r;cin>>l>>r;
			cout<<t.query(1,l,r).ioi<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Minecraft万岁 (赞：2)

这题不难 但是真的很坑      
先说说不毒瘤的地方     
首先发现这道题有 **单点修改 区间查询** 的特征 再看看题目让维护的东西 得知这题可以用线段树做     
#### 考虑如何维护   
看见题目中的 $IOI$ 被分开了 这给我们启发   
我们开一个存线段树的数组 就叫它 $t[i]$ 里面维护 $I$ $O$ $I$ $IO$ $OI$ $IOI$ 分别作为字串出现的次数 我们让 $ls$ $rs$ 分别为 $i$ 的左孩子 右孩子 ~~方便叙述~~  
显然我们有 
$$t[i].i=t[ls].i+t[rs].i$$
$$t[i].o=t[ls].o+t[rs].o$$  
根据乘法原理：左边区间拿出一部分 右边区间拿出**后面**一部分 拼在一起就可以得到一个目标字串 不要忘记再加上左右区间已经得到的目标字串的个数！ 于是我们可以写出 
$$t[i].io=t[ls].i*t[rs].o+t[ls].io+t[rs].io$$
$$t[i].oi=t[ls].o*t[rs].i+t[ls].oi+t[rs].oi$$  
最后的BOSS 区间 $IOI$ 的次数     
$$t[i].ioi=t[ls].i*t[rs].oi+t[ls].io*t[rs].i+t[ls].ioi+t[rs].ioi$$  
为了代码的简洁 我们写出一个合并两个区间的函数 $mergy(p1,p2)$ 用于合并 

#### 讲讲坑一点的 照样从简单的开始     

- 不开 $long$ $long$ 见祖宗     
- 由于本题的特性 区间查询不能简单的加上 $IOI$ 出现的次数 而是要合并区间并返回 直到最后才是查询的 $IOI$ 出现的次数 

上代码！


------------
```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
char a[500005];//读入的字符串 从下标1开始读入 方便建树 
struct node
{
	ll i;//五个需要维护的值 
	ll o;
	ll io;
	ll oi;
	ll ioi;
}t[2000005];//线段树开4倍空间 
ll n,m;//字符串长度 操作个数 
ll op,l,r;//按照题目中变量名定义 
char c;
ll x;
inline void read(ll &x)//快读 
{
	ll f=1;char c;
	for(x=0,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48); x*=f;
}
inline void readc(char &x)//读字符 其实并不快 
{
	for(x=getchar();x!='I'&&x!='O';x=getchar()) ;	
} 
inline node mergy(node p1,node p2)//合并两个区间的函数 mergy 
{
	node rest;
	rest.i=p1.i+p2.i;//按照思路去计算 
	rest.o=p1.o+p2.o;
	rest.io=p1.i*p2.o+p1.io+p2.io;
	rest.oi=p1.o*p2.i+p1.oi+p2.oi;
	rest.ioi=p1.i*p2.oi+p1.io*p2.i+p1.ioi+p2.ioi;
	return rest;
}
inline void build(ll l,ll r,ll p)//建树 
{
	if(l==r)
	{
		if(a[l]=='I') t[p].i=1;//单个的点 只可能出现 I 或者 O 所以只要维护这个就可以了 
		else t[p].o=1;
		return ;
	}
	ll mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	t[p]=mergy(t[p<<1],t[p<<1|1]);//定义的结构体 直接赋值就好了  
} 
inline void update(ll l,ll r,ll x,char c,ll p)//修改 
{
	if(l==r)
	{
		a[l]=c;//修改原串 写完发现并没有什么用 
		t[p].i=t[p].o=0;//先全部赋值为 0 
		if(a[l]=='I') t[p].i=1;//再重新赋值 
		else t[p].o=1;
		return ;
	}
	ll mid=(l+r)>>1;
	if(x<=mid) update(l,mid,x,c,p<<1);//修改的在左区间 
	else update(mid+1,r,x,c,p<<1|1);//修改的在右区间 
	t[p]=mergy(t[p<<1],t[p<<1|1]);//照样合并赋值 
}
inline node query(ll ql,ll qr,ll l,ll r,ll p)//查询操作 
{
	if(ql<=l&&r<=qr) return t[p];//返回结构体 
	ll mid=(l+r)>>1;
	node rest1,rest2;
	rest1.i=rest1.o=rest1.io=rest1.oi=rest1.ioi=0;//清空 
	rest2.i=rest2.o=rest2.io=rest2.oi=rest2.ioi=0;
	if(ql<=mid) rest1=query(ql,qr,l,mid,p<<1);
	if(qr>mid) rest2=query(ql,qr,mid+1,r,p<<1|1);
	return mergy(rest1,rest2); //返回是合并两个区间的值 并不是直接相加 IOI出现的次数 
}
int main()
{
	read(n);read(m);
	scanf("%s",1+a);//从下标1开始读入字符串 
	build(1,n,1);//建树 
	while(m--)
	{
		read(op);
		if(op==1)
		{
			read(x);
			readc(c); 
			update(1,n,x,c,1);//修改操作 
		}
		else
		{
			read(l);
			read(r);
			printf("%lld\n",query(l,r,1,n,1).ioi);//查询操作 
		}
	}
	return 0;
}
```


---

## 作者：tobie (赞：1)

这是一道很好的线段树的进阶题。

这道题要求的是 `IOI` 的个数，所以需要存储 `I,O,IO,OI,IOI` 这些字符串的数量。

```
I的数量=左子树I的数量+右子树I的数量
O的数量=左子树O的数量+右子树O的数量
IO的数量=左子树IO的数量+右子树IO的数量+左子树I的数量*右子树O的数量
OI的数量=左子树OI的数量+右子树OI的数量+左子树O的数量*右子树I的数量
IOI的数量=左子树IOI的数量+右子树IOI的数量+左子树IO的数量*右子树I的数量+左子树I的数量*右子树OI的数量
```
这样就可以维护每一个区间的信息，并且也比较方便合并（就是代码繁杂了点）。

另外的一些细节：

对于合并数据的操作其实可以看成是一个 `数据a+数据b` ，所以我使用了重载运算符的办法来简化代码。

另外，一定要开 `long long` ！

我的代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N=500009;
struct segment_tree{
	long long I,O,IO,OI,IOI;//这些字符串出现的次数
}tree[N*4];
int n,m;
char ch[N];
segment_tree set(segment_tree &a)//将a存储的数据清空为全0（初始化）。
{
	a.I=a.O=a.IO=a.OI=a.IOI=0;
}
segment_tree operator+(segment_tree now1,segment_tree now2)//相当于当时提到的合并操作。
{
	segment_tree ans;
	set(ans);
	ans.I=now1.I+now2.I;
	ans.O=now1.O+now2.O;
	ans.IO=now1.IO+now2.IO+(1ll*now1.I*now2.O);
	ans.OI=now1.OI+now2.OI+(1ll*now1.O*now2.I);
	ans.IOI=now1.IOI+now2.IOI+(1ll*now1.I*now2.OI)+(1ll*now1.IO*now2.I);
	return ans;
}
void make(int l,int r,int now)
{
	set(tree[now]);
	if(l==r)
	{
		if(ch[l]=='I') tree[now].I=1;
		if(ch[l]=='O') tree[now].O=1;
		return;
	}
	int mid=(l+r)/2;
	make(l,mid,now*2);
	make(mid+1,r,now*2+1);
	tree[now]=tree[now*2]+tree[now*2+1];//重载运算符的好处就是能让线段树核心代码部分和普通区间加线段树代码相似，方便调试。
//	printf("%d %d %d %d %d %d %d\n",l,r,tree[now].I,tree[now].O,tree[now].IO,tree[now].OI,tree[now].IOI);
}
void change(int nowl,int nowr,int pos,char k,int now)
{
	if(nowr<pos||pos<nowl) return;
	if(nowl==nowr&&nowl==pos)
	{
		set(tree[now]);
		if(k=='I') tree[now].I=1;
		if(k=='O') tree[now].O=1;
		return;
	}
	int mid=(nowl+nowr)/2;
	if(pos<=mid) change(nowl,mid,pos,k,now*2);
	else change(mid+1,nowr,pos,k,now*2+1);
	tree[now]=tree[now*2]+tree[now*2+1];
}
segment_tree query(int nowl,int nowr,int posl,int posr,int now)
{
	if(posl<=nowl&&nowr<=posr) return tree[now];
	int mid=(nowl+nowr)/2;
	segment_tree ans;
	set(ans);//别忘了初始化
	if(posl<=mid) ans=ans+query(nowl,mid,posl,posr,now*2);
	if(mid<posr) ans=ans+query(mid+1,nowr,posl,posr,now*2+1);
	return ans;
}
int flg;
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",ch+1);
	make(1,n,1);
	while(m--)
	{
	//	for(int i=1;i<=20;i++)
	//	printf("%d %d %d %d %d %d %d\n",tree[i].l,tree[i].r,tree[i].I,tree[i].O,tree[i].IO,tree[i].OI,tree[i].IOI);
		scanf("%d",&flg);
		if(flg==1)
		{
			int x;
			char ch,c[5];
			scanf("%d%s",&x,c);//关于这个字符读入的问题，本机总是会出现一些奇奇怪怪的问题，所以我借鉴了题解的方法，使用字符串来读入字符。
			ch=c[0];
		//	cout<<ch<<endl;
			change(1,n,x,ch,1);
		}
		else
		{
			int l,r;
			scanf("%d%d",&l,&r);
			segment_tree ans=query(1,n,l,r,1);
			printf("%lld\n",ans.IOI);
		}
	}
}
```


---

## 作者：MuYC (赞：1)

官方题解对于思路的讲述已经非常的清晰了.

### 分享一个个人心得:

#### 线段树对于左右区间的运用

线段树主要就是妙在它的合并区间功能以及对于一个整块进行分治的思想.你会发现，每次线段树的更新基本上都是基于左右儿子这两个左右区间的.对于可以区间维护的信息(基本上也就是可以分裂成子问题的问题)，我们总是每次更新后就递归回溯根据当前点的左右儿子节点维护信息.线段树最妙的地方正是在于此处，不管是合并信息(合并答案),或者是分治处理信息(修改 or 查询)，实际上我们都是得用到左右区间的.

#### 例如这个题目:

要求我们维护一段区间内"IOI"的个数，实际上我们可以把问题转化为左右两个区间来解决.假设我们要查询的区间是$[L,R]$,我们可以先处理$[L,mid]$的答案以及$[mid+1,R]$ 的答案.

同时我们发现有一部分答案是横跨了左右两个区间的,这时候我们就可以处理出左边的"I"的数量以及"IO"的数量(显然左区间的"OI"对于这种横跨左右两边的答案没有贡献)，同时也处理出右区间"OI"、"I"的数量,这时候我们根据乘法原理(具体可以看官方题解)递归处理问题即可

而线段树是可以很好的适应这个问题的,因为其实线段树运用的也是分治的思想，它刚好也有左右区间，而且可以维护区间信息,并且有着优秀的$logn$(尽管常数比较大......)的时间复杂度,所以线段树就可以解决这道题目了.

贴上这道题的ＡＣ代码:

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long 
int n,Q;
char A[500005];
int a[500005];

struct node{
	
	int i,o,oi,io,ioi,l,r;
	void clean()
	{
		i = o = io = oi = ioi = 0;
		return ;
	}
	
}T[2000005];

node updata(node x,node l,node r)
{
	x.oi = l.o * r.i + l.oi + r.oi;
	x.io = l.i * r.o + l.io + r.io;
	x.i = l.i + r.i;
	x.o = l.o + r.o;
	x.ioi = l.i * r.oi + l.io * r.i + l.ioi + r.ioi;
	return x;
}

void build_tree(int x,int l,int r)
{
	T[x].clean();
	T[x].l = l , T[x].r = r;
	if(l == r)
	{
		if(a[l] == 0)T[x].o = 1;
		else T[x].i = 1;
		return ;
	}
	int mid = (l + r) >> 1;
	build_tree(x << 1 , l , mid);
	build_tree(x << 1 | 1 , mid + 1 , r );
	T[x] = updata(T[x],T[x << 1] , T[x << 1 | 1]);
	return ;
}

node getans(int x,int l,int r)
{
	if(T[x].l >= l && T[x].r <= r)return T[x];
	int mid = (T[x].l + T[x].r) >> 1;
	node Sum ;
	Sum.clean();
	if(l <= mid)Sum = updata(Sum,Sum,getans(x << 1, l , r));
	if(r  > mid)Sum = updata(Sum,Sum,getans(x << 1 | 1, l , r ));
	return Sum;
}

void change(int x,int pos,int k)
{
	if(T[x].l == T[x].r && T[x].l == pos)
	{
		if(k == 1)T[x].i = 1, T[x].o = 0;
		else T[x].i = 0 , T[x].o = 1;
		return ;
	}
	int mid = (T[x].l + T[x].r) >> 1;
	if(pos <= mid)change(x << 1 , pos , k);
	else change(x << 1 | 1 , pos , k );
	T[x] = updata(T[x],T[x << 1] , T[x << 1 | 1]);
	return ;
}

signed main()
{
	cin >> n >> Q;
	cin >> A;
	for(int i = 0 ; i < n ; i ++)
	{
		if(A[i] == 'I')
		a[i + 1] = 1;
		else a[i + 1] = 0;
	}
	build_tree(1 , 1 , n);
	while(Q)
	{
		int op,l,r;
		char pos;
		cin >> op >> l;
		if(op == 2)
		{
			cin >> r;
			cout << getans(1,l,r).ioi << endl;
		}
		else 
		{
			cin >> pos;
			if(pos == 'I')
			change(1,l,1);
			else change(1,l,0);
		}
		Q--;
	}
	return 0;
}
```

#### 小结

线段树的题目我们不应该一开始就直接线段树暴力搞，而是应该先分析问题为什么能用线段树做，线段树做这道题优越性在哪里，这样子收获也许会多一点，也可以加深自己对于线段树的理解，线段树不仅仅是一个数据结构，或许也可以说成是一种思想　

---

## 作者：LeavingZzz (赞：1)

## $\mathsf{Solution\space To\space P6373}$  

是一道线段树的好题  

通过这题可以学到有时候并不能一口气直接求出答案，考虑到线段树操作的核心是合并子问题，所以本题解题的关键即在于将 `IOI` 分解成 `I O IO OI` 几个比较好合并的参数最后得到所求  

几个量的维护方式  

`I:` 左右区间 `I` 数量之和  
`O:` 同 `I`  
`IO:` 左右区间的 `IO` 数量之和，再加上左区间的 `I` 乘以右区间的 `O`  
`OI:` 同 `IO`  
`IOI:` 左右区间的 `IOI` 数量之和，加上左区间的 `IO` 乘以右区间的 `I`，加上右区间的 `OI` 乘以左区间的 `I`  

线段树节点定义部分
```
struct seg_tree{
    LL I,O,IO,OI,IOI;
}tree[maxn<<2];
//此处重载加号效果和pushup效果一样，但是在区间查询的时候更简洁
seg_tree operator + (const seg_tree &x,const seg_tree &y)
{
    seg_tree t;
    t.I=x.I+y.I;
    t.O=x.O+y.O;
    t.IO=x.IO+y.IO+x.I*y.O;
    t.OI=x.OI+y.OI+x.O*y.I;
    t.IOI=x.IOI+y.IOI+x.IO*y.I+x.I*y.OI;
    return t;
}
```

------------
然鹅传统线段树通过本题的总用时大概在 $2\sim3s$ 左右  
虽然可以通过，但是可以追求更好的做法  
所以就可以用zkw线段树来大幅度优化常数了  
### zkw线段树

#### 1.优化原理：  
传统线段树采用的是递归实现，递归本身常数会大于迭代，并且内部的各种判断以及较多的参数传递导致传统线段树的常数会比较大  
zkw线段树采用的是迭代实现，常数上远优于传统线段树  
~~而且码量小（不会这才是主要原因吧不会吧不会吧~~  
#### 2.实现方式  
zkw线段树存储方式和线段树类似，节点 $i$ 的左右儿子分别为 $i\times2$ 和 $i\times2+1$，使用最下面一层节点来表示单个点。  
叶子结点表示的信息是一开始就知道的（单点）  
传统线段树是递归建树，先要递归到最底层然后更新上层  
zkw线段树模拟这个过程，但是省去了递归到最底层这一步  

所以我们首先要找到第一个叶子节点  
按照传统线段树的编号方式，第一个叶子结点编号应该为 $2^k$ （$k=\lceil \log_2 N\rceil$）  

但是zkw线段树因为区间查询方式比较特殊，叶子编号整体要加一，可以先不管这个，看完区间查询就知道为什么了  

故建树代码如下  
```
void build()
{
    M=1;
    while(M<N) M<<=1;
    //M+1即为第一个叶子结点
    for(int i=1;i<=N;i++)
        tree[i+M].I=(s[i]=='I'),tree[i+M].O=(s[i]=='O');//叶结点单点信息
    for(int i=M-1;i;i--) tree[i]=tree[ls]+tree[rs];
    //重载了加号，此处即为pushup
    return ;
}
```  


------------

单点修改也比较简单，还是想传统的修改，先递归找到叶子节点更新信息然后逐级更新祖先  
建树过程中的变量 `M` 可以帮我们 $O(1)$ 定位到叶子结点位置  
故单点修改代码如下  
```
void update(int i)
{
    i+=M;//定位到叶子节点
    swap(tree[i].I,tree[i].O);//修改信息
    //我在主函数中特判掉了修改位置原值等于修改值的修改
    while(i>>=1) tree[i]=tree[ls]+tree[rs];//逐级更新到根
    return ;
}
```  
短，而且常数很小  


------------

最后是区间查询，这也是本题zkw线段树最难理解的部分  
![](https://cdn.luogu.com.cn/upload/image_hosting/0kp5zsc9.png)  
图中标绿的区间是传统线段树递归过程中会返回的几个节点，也就是答案由这几个区间拼成  
zkw大神告诉我们把区间 $[L,R]$ 转成 $(L-1,R+1)$（这也是为啥建树的时候要加一，不然会让 $L-1$ 去到错误的地方）  
所以逐级向上的过程就是  
![](https://cdn.luogu.com.cn/upload/image_hosting/4z04duu9.png)  
然后zkw大神就总结出来了规律  
1. 在左端点向上的过程中，当左端点代表的区间是某个节点的左儿子的时候，其兄弟节点代表的区间一定在我们所求的区间中  
2. 在右端点向上的过程中，当右端点代表的区间是某个节点的右儿子时，其兄弟节点代表的区间一定在我们所求的区间中  
3. 上述向上过程一直进行到左右端点互为对方兄弟节点  

所以我们区间查询的代码也有啦  
（注意本题的区间是分左右的，也就是如果采用加号代替pushup的话，这个加法是不满足交换律的，好在zkw线段树累加的区间在左端点和右端点处都是分别有顺序的，可以分成两个变量做）  
```
seg_tree query(int l,int r)
{
    seg_tree lre,rre;
    lre.I=lre.IO=lre.IOI=lre.O=lre.OI=0;
    rre.I=rre.IO=rre.IOI=rre.O=rre.OI=0;
    //l^r^1=0的时候l,r互为兄弟节点，可以从线段树标号方式理解这一点
    //l>>=1,r>>=1 是将其变为其父亲节点
    for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1)
    {
        //在线段树中，除根节点外一个节点是某个节点左儿子的充要条件就是他是个偶数
        if(~l&1) lre=lre+tree[l^1];
        //同理，是右儿子的充要条件就是他是个奇数
        if(r&1) rre=tree[r^1]+rre;//注意此处加法顺序，+号左侧一定是靠左的区间
        //节点i的兄弟节点即为i^1
    }
    return lre+rre;
}
```  


------------
区间修改本题没有涉及，但是基本思路也是区间修改的思路，然后为了避免pushdown（自底向上怎么pushdown啊），采用标记永久化，此处点到为止  


------------
完整代码  
```
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<ctime>
using namespace std;
#define getchar() (SS==TT&&(TT=(SS=BB)+fread(BB,1,1<<20,stdin),TT==SS)?EOF:*SS++)
char BB[1<<20],*SS=BB,*TT=BB;
inline int R()
{
    int re;
    char c;
    while(!isdigit(c=getchar()));
    re=c-48;
    while(isdigit(c=getchar()))
    re=re*10+c-48;
    return re;
}
const int maxn=500007;
typedef long long LL;
struct seg_tree{
    LL I,O,IO,OI,IOI;
}tree[maxn<<2];
seg_tree operator + (const seg_tree &x,const seg_tree &y)
{
    seg_tree t;
    t.I=x.I+y.I;
    t.O=x.O+y.O;
    t.IO=x.IO+y.IO+x.I*y.O;
    t.OI=x.OI+y.OI+x.O*y.I;
    t.IOI=x.IOI+y.IOI+x.IO*y.I+x.I*y.OI;
    return t;
}
#define ls (i<<1)
#define rs (i<<1|1)
char s[maxn];
int M;
int N,Q;
void build()
{
    M=1;
    while(M<N) M<<=1;
    for(int i=1;i<=N;i++)
        tree[i+M].I=(s[i]=='I'),tree[i+M].O=(s[i]=='O');
    for(int i=M-1;i;i--) tree[i]=tree[ls]+tree[rs];
    return ;
}
void update(int i)
{
    i+=M;
    swap(tree[i].I,tree[i].O);
    while(i>>=1) tree[i]=tree[ls]+tree[rs];
    return ;
}
seg_tree query(int l,int r)
{
    seg_tree lre,rre;
    lre.I=lre.IO=lre.IOI=lre.O=lre.OI=0;
    rre.I=rre.IO=rre.IOI=rre.O=rre.OI=0;
    for(l=l+M-1,r=r+M+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) lre=lre+tree[l^1];
        if(r&1) rre=tree[r^1]+rre;
    }
    return lre+rre;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    N=R();Q=R();
    char c;
    while((c=getchar())!='I'&&c!='O');
    s[1]=c;
    for(int i=2;i<=N;i++)
        s[i]=getchar();
    build();
    int op,l,r;
    while(Q--)
    {
        op=R();
        if(op==1)
        {
            l=R();
            c=getchar();
            if(s[l]!=c) update(l),s[l]=c;
        }
        else
        {
            l=R();r=R();
            printf("%lld\n",query(l,r).IOI);
        }
    }
    return 0;
}
```  
$\huge\mathcal{The\space End}$  
~~zkw+fread稳控最优解/cy~~

---

