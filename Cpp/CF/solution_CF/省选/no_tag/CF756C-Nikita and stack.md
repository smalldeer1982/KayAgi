# Nikita and stack

## 题目描述

NK有一个栈。 此问题中的栈是支持两个操作的数据结构。 push(x)操作将整数$x$放在栈顶，而pop()操作则从栈中删除顶部的整数，即最后添加的整数。 如果栈为空，则pop()函数不执行任何操作。

NK用堆栈进行了$m$次操作，但忘记了那$m$次操作干了什么。在第$i$个步骤中，他记得他进行过第$p_{i}$个操作。 换句话说，他以某些排列$p_{1}$，$p_{2}$，...，$p_{m}$的顺序记住操作。 在完成每一步之后，NK想要以相应的顺序知道在已经记住的操作后栈的顶部的数是什么。帮帮NK！

## 说明/提示

在第一个示例中，在NK记住第一步的操作之后，操作push(2)是唯一的操作，因此答案是2。 在他记住在push(2)之前完成的pop()操作之后，答案保持不变。

在第二个示例中，操作是push(2)，push(3)和pop()。 NK按照顺序记住它们。

在第三个示例中，NK以相反的顺序记住了所有的操作。

## 样例 #1

### 输入

```
2
2 1 2
1 0
```

### 输出

```
2
2
```

## 样例 #2

### 输入

```
3
1 1 2
2 1 3
3 0
```

### 输出

```
2
3
2
```

## 样例 #3

### 输入

```
5
5 0
4 0
3 1 1
2 1 1
1 1 2
```

### 输出

```
-1
-1
-1
-1
2
```

# 题解

## 作者：Hoks (赞：1)

## 前言
差点没能想出来，还好看出来我搞反了。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
题意就很有意思了，让你用数据结构实现支持在时间轴上插入操作的栈。

但是也有特殊的条件，也就是只询问栈顶元素。

比较难想到，但是想到好像就秒了？

考虑对于时刻 $i$ 维护还要几次弹出会把这个时刻压入的数弹出。

那么对于区间 $[l,r]$ 即为维护时刻 $l\sim r$ 压入的数弹出还需要弹出次数的最大值。

所以在时刻 $x$ 加入一个数就相当于直接区间 $1\sim x$ 修改 $+1$。

而在时刻 $x$ 弹出栈顶则相同了，区间 $-1$ 即可。

那么我们要找到的就是从后往前第一个点 $j$ 满足其维护的值 $>0$。

可以考虑用线段树维护，因为要找从后往前第一个，所以要先走右儿子。
## 代码
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
// #define int long long
using namespace std;
const int N=1e5+10,INF=0x3f3f3f3f,mod=998244353;
int n,a[N],t[N<<2],lz[N<<2];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='#'||c=='.'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void pushdown(int p){lz[ls]+=lz[p];lz[rs]+=lz[p];t[ls]+=lz[p],t[rs]+=lz[p];lz[p]=0;}
inline void modify(int p,int l,int r,int s,int e,int x)
{
    if(l>=s&&r<=e) return lz[p]+=x,t[p]+=x,void();pushdown(p);
    if(mid>=s) modify(ls,l,mid,s,e,x);
    if(mid<e) modify(rs,mid+1,r,s,e,x);
    t[p]=max(t[ls],t[rs]);
}
inline int query(int p,int l,int r)
{
    if(l==r) return a[l];pushdown(p);
    if(t[rs]>0) return query(rs,mid+1,r);
    if(t[ls]>0) return query(ls,l,mid);
    return -1;
}
signed main()
{
    n=read();memset(a,-1,sizeof a);
    for(int i=1,op,x;i<=n;i++)
    {
        x=read(),op=read();if(op) a[x]=read();modify(1,1,n,1,x,op?1:-1);
        print(query(1,1,n)),put('\n');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：zhimao (赞：1)

# 分块是万能的！
因此，我用分块过了此题。
## 题意
此题深刻地告诉了我语文的重要性 ~~语文大佬可跳过此部分~~。

NK每次回忆起第 $p_i$ 个操作，按顺序做**每一个当前已经回忆起来的**操作，输出栈顶元素（没有输 -1 ）。

举个例子（样例 3 ）：
1. 空$\quad$空$\quad$空$\quad$空$\quad pop()$ ，无元素，输出 -1。
2. 空$\quad$空$\quad$空$\quad pop()\quad pop()$ ，无元素，输出 -1。
3. 空$\quad$空$\quad push(1) \quad pop()\quad pop()$ ，无元素，输出 -1。
4. 空$\quad push(1) \quad push(1) \quad pop()\quad pop()$ ，无元素，输出 -1。
5. $push(2) \quad push(1) \quad push(1) \quad pop()\quad pop()$ ，有一元素 1 ，输出 1。

## 做法
先考虑朴素做法：每次记录新回忆起的操作，然后从 1 到 m 做每个操作得出结果。

这样显然有很多操作被重复做，效率太低。于是考虑分块，一个块有两种情况：一是所有插入的元素都被弹出，于是我们只要记录还有几个弹出操作；二是有插入的元素未被弹出，这时候我们就要顺次记录遗留元素，**注意**，此时依然有可能弹出操作没有用到，我们可以很容易地知道这些弹出操作都在遗留元素的左边，这个的次数也要记录。

所以，对于每个块，我们要记录遗留元素和遗留弹出操作数。

更新时暴力重算一个块，求答案时加减遗留元素数和遗留弹出操作数，当栈里元素个数大于零就输出，否则输 -1 。

**tip**：求答案时从后往前枚举块，因为我们要求栈顶元素。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int N,M,n,sta[10000];
struct arr1
{
	int bo,x;
}a[100005];
struct arr2
{
	int x,cnt,a[505];
}b[3005];
void update(int k)
{
	int l=0,t=0;
	for(int i=1;i<=N;i++)
		if(a[k*N-N+i].bo)
		{
			int j=k*N-N+i;
			if(a[j].bo==1)
			{
				++l;
				sta[l]=a[j].x;
			}
			else --l;
			if(l<0) ++t,l=0;
		}
	b[k].x=t;
	b[k].cnt=l;
	for(int i=1;i<=l;i++) b[k].a[i]=sta[i];
}
int main()
{
	scanf("%d",&n);
	N=min(n,500);
	M=(n+N-1)/N;
	for(int i=1;i<=n;i++)
	{
		int x,y,z;
		scanf("%d%d",&x,&y);
		if(y)
		{
			scanf("%d",&z);
			a[x]={y,z};
			update((x+N-1)/N);
		}
		else
		{
			a[x]={y+2,0};
			update((x+N-1)/N);
		}
		int t=0;
		for(int j=M;j>0;j--)
		{
			t+=b[j].cnt;
			if(t>0)
			{
				printf("%d\n",b[j].a[t]);
				break;
			}
			t-=b[j].x;
		}
		if(t<=0) puts("-1");
	}
}
```


---

## 作者：鱼跃于渊 (赞：0)

# 线段树更好！
因此，我用线段树过了此题。  
## 题意  
NK 每次回忆起第 $p_i$ 次操作，**按顺序**做每一个已经回忆起的操作，输出栈顶元素（没有输出 $-1$）。  
## 做法  
我们开一颗权值线段树来维护区间最大值，并将 push 看作 $1$、pop 看做 $-1$，每次回忆将 $1$ 到 $p_i$ 的区间进行区间加减；查询时则返回一个最大的下标使得它到 $m$ 的区间最大值大于 $0$，记它为 $x$，输出第 $p_x$ 次操作所操作的元素。  
**tip1**：查询时优先查询右子树，因为我们要求栈顶元素。  
**tip2**：当 $m$ 为 $1$ 时注意特判。  
## 代码  
```
#include <bits/stdc++.h>
using namespace std;
#define ls(x) ((x)<<1)
#define rs(x) ((x)<<1|1)
const int N=1e6+5;
struct tree{
	int mx,tag;
}t[N*4];
void modify(int i,int k){
	t[i].mx+=k;
	t[i].tag+=k;
}
void push_down(int i){
	if(!t[i].tag) return;
	modify(ls(i),t[i].tag);
	modify(rs(i),t[i].tag);
	t[i].tag=0;
}
void push_up(int i){
	t[i].mx=max(t[ls(i)].mx,t[rs(i)].mx);
}
void update(int nl,int nr,int l,int r,int i,int k){
	if(nl<=l&&r<=nr){
		modify(i,k);
		return;
	}
	push_down(i);
	int mid=l+r>>1;
	if(nl<=mid) update(nl,nr,l,mid,ls(i),k);
	if(mid<nr) update(nl,nr,mid+1,r,rs(i),k);
	push_up(i);
}
int query(int i,int l,int r){
	if(l==r) return l;
	push_down(i);
	int mid=l+r>>1;
	if(t[rs(i)].mx>0) return query(rs(i),mid+1,r);
	if(t[ls(i)].mx>0) return query(ls(i),l,mid);
	return 0;
}
void build(int i,int l,int r){
	t[i]={0,0};
	if(l==r) return;
	int mid=l+r>>1;
	build(ls(i),l,mid);
	build(rs(i),mid+1,r);
}
int n,a[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n;
	build(1,1,n);
	for(int i=1,x,op,ans;i<=n;i++){
		cin>>x>>op;
		if(op) cin>>a[x];
		update(1,x,1,n,1,(op?1:-1));
		ans=query(1,1,n);
		cout<<(n==1?(op?a[1]:-1):(ans?a[ans]:-1))<<'\n';
	}
	return 0;
}
```

---

