# [CEOI 2013] Board

## 题目描述

给出这样一棵“二叉树”:
 - 每个节点有左右两个儿子，并如下定义每个节点的高度：假设父亲节点的高度为 $h$，那么他的两个儿子的节点的高度都是 $h+1$，相同高度的所有节点称作一层。

 - 每个节点的左儿子的子树都在右儿子的子树的左边，每一层相邻的两个节点之间有一条边。 下面是一个例子：

![](https://cdn.luogu.com.cn/upload/pic/74384.png)

每一条图上的路径用一个字符串表示，字符串中的每一个字符表示一 个移动。字符仅包含如下五种：

 - $\tt 1$：表示移动到当前节点的左儿子 
 - $\tt 2$：表示移动到当前节点的右儿子
 - $\tt U$：表示移动到当前节点的父亲节点 
 - $\tt L$：表示移动到当前节点同层的左边的节点（保证当前节点在这一层中不是最左边的节点）
 - $\tt R$：表示移动到当前节点同层的右边的节点（保证当前节点在这一层中不是最右边的节点）

 用一条路径来表示这条路径的终点，例如路径：$\tt  221LU$ 就表示上图中的节点 $A$。 给出两条路径，你的任务是求出着两条路径的终点之间的最短路。

## 说明/提示

用 $D$ 表示所有经过的节点中，深度最大的节点的深度；$S$ 表示输入字符串的最大长度。 

- 对于 $10\%$ 的数据，$D \leq 10$;
- 对于 $30\%$ 的数据，$D \leq 50$;
- 对于 $50\%$ 的数据，$D \leq 10^3$;
- 对于 $70\%$ 的数据，$D\leq 2 \times 10^4$; 
- 对于 $100\%$ 的数据，$D \leq 10^5, S \leq 10^5$。

## 样例 #1

### 输入

```
221LU
12L2```

### 输出

```
3```

## 样例 #2

### 输入

```
111RRRRRRR
222```

### 输出

```
0```

## 样例 #3

### 输入

```
11111
222222```

### 输出

```
10```

# 题解

## 作者：AaronJance (赞：11)

水个题解。

巨佬们轻喷。

二进制高精度肯定是要用的(见题目提供者的分析)线段树大可不必~~本蒟蒻也写不来~~。

解决进位的最简方式就是~~不理它~~**暂时不必进位,最后复原格式,不影响最终数据**。

用官方题解代码
```cpp

// CEOI 2013 - Task: Board - Solution

// Author: Gustav Matula


#include <cstdio>

#include <cstring>

#include <cassert>

#include <algorithm>


using namespace std;


#define MAX 100005


char pa[MAX]; int _a[MAX], loga, *a;

char pb[MAX]; int _b[MAX], logb, *b;


void carry(int *idx, int i) {

  idx[i - 1] += idx[i] / 2 - (idx[i] % 2 == -1);
  
  idx[i] = abs(idx[i]) % 2;//从后往前复原格式 
  
}


void trace(char *path, int *idx, int &log) {

  int n = strlen(path);
  
  idx[0] = log = 1;
  

  for (int i = 0; i < n; ++i) {
  
    if (path[i] == '1') idx[log++] = 0;
    
    if (path[i] == '2') idx[log++] = 1;
    
    if (path[i] == 'L') --idx[log - 1];
    
    if (path[i] == 'R') ++idx[log - 1];//总和与是否进退位无关 (最后结果正确只需一次进退位) 
    
    if (path[i] == 'U') carry(idx, --log);//复原末尾格式便于消除(利用局部格式性质) 
    
  }
  

  for (int i = log - 1; i >= 1; --i) carry(idx, i);
  

  int r = 0; while (idx[r] == 0) ++r;
  
  for (int i = r; i < log; ++i) idx[i - r] = idx[i];//从后往前依次复原格式 
  
  log -= r;
  
}

int main(void)
{
  scanf("%s", pa); trace(pa, a = _a, loga);
  
  scanf("%s", pb); trace(pb, b = _b, logb);
  

  int log = min(loga, logb);
  
  int sol = 1 << 20;
  
  int delta = 0;
  

  for (int i = 0; i < log && delta < (1 << 20); ++i) {
  
    delta = delta * 2 + a[i] - b[i];
    
    sol = min(sol, abs(delta) + 2 * (log - i - 1));
    
  }

  printf("%d\n", sol + abs(loga - logb));
  

  return 0;
  
}
```


---

## 作者：Froggy (赞：11)

作为本题的贡献者,个人认为这是一道很好的题目..

奋斗了5h,还是窝太菜...

---

咱们一点一点地看

很容易想到(~~似乎并不那么容易~~),可以先把节点从左到右,从上到下依次编个号,那么每个操作就相当于:(设当前节点为$now$)

- $1:$ now*2 
- $2:$ now*2+1
- $U:$ now/2
- $L:$ now--
- $R:$ now++

---

 1. $D \le 10$的部分
 
 由于边数最多有$10*2^{D-1}$条,所以可以先找到两个节点,暴力建边,跑最短路
 
 代码:
 
 ```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
#define N 100010
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
char a[N],b[N];
int x,y,vis[N];
int Get(char *s,int n){
	int now=1;
	for(int i=1;i<=n;i++){
		if(s[i]=='1'){
			now=(now<<1);
		}
		else if(s[i]=='2'){
			now=(now<<1|1);
		}
		else if(s[i]=='U'){
			now=(now>>1);
		}
		else if(s[i]=='L'){
			now--;
		}
		else if(s[i]=='R'){
			now++;
		}
	}
	return now;
}
int head[N],cnt=0,no[N],dis[N];
struct Edge{
	int to,nxt;
}edge[N<<3];
void add(int a,int b){
	cnt++;
	edge[cnt].to=b;
	edge[cnt].nxt=head[a];
	head[a]=cnt;
}
int main(){
	scanf("%s",a+1);
	scanf("%s",b+1);
	int lena=strlen(a+1);
	int lenb=strlen(b+1);
	x=Get(a,lena);
	y=Get(b,lenb);
	memset(dis,0x3f,sizeof(dis));
	for(int i=0;i<=10;i++){
		no[1<<i]=1;
	}
	for(int i=1;i<1<<11;i++){
		if(i>1)add(i,i>>1);
		if(i*2+1<(1<<11))add(i,i*2),add(i,i*2+1);
		if(!no[i])add(i,i-1);
		if(!no[i+1])add(i,i+1);
	}
	dis[x]=0;
	q.push(make_pair(0,x));
	while(!q.empty()){
		int u=q.top().second;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				q.push(make_pair(dis[v],v));
			}
		}
	}
	cout<<dis[y]<<endl;
	return 0;
}
```

期望得分:10分 

实际得分:14分

---

 2. $D \le 50$的部分
 
 仔细观察,可以观察到一个性质:
 
 **当确定了两个节点之后，最短路就一定是两个节点先分别向上移动到同一个高度，然后再沿着这一层中间的边走过去**
 
 那么只需要枚举两个节点向上跳到了哪一层即可。(可以把数除以2,就相当于往上蹦了一层)
 
 $2^{50}$,long long可以存的下,枚举取最大值
 
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
#define N 100010
typedef long long ll;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
char a[N],b[N];
ll p,q,ans;
ll Get(char *s,int n){
	ll now=1;
	for(int i=1;i<=n;i++){
		if(s[i]=='1'){
			now=(now<<1);
		}
		else if(s[i]=='2'){
			now=(now<<1|1);
		}
		else if(s[i]=='U'){
			now=(now>>1);
		}
		else if(s[i]=='L'){
			now--;
		}
		else if(s[i]=='R'){
			now++;
		}
	}
	return now;
}
ll Abs(ll x){
	return x<0?-x:x;
}
int main(){
	scanf("%s",a+1);
	scanf("%s",b+1);
	p=1,q=1;
	int lena=strlen(a+1);
	int lenb=strlen(b+1);
	p=Get(a,lena);
	q=Get(b,lenb);
	if(p<q)swap(p,q);
	ans=999999999;
	int tot=0;
	while((int)log2(p)>(int)log2(q)){
		p>>=1;
		tot++;
	}
	if(p==q){
		ans=min(ans,1LL*tot);
	}
	while(p!=q){
		ans=min(Abs(p-q)+tot,ans);
		tot+=2;
		p>>=1,q>>=1;
	}
	cout<<ans<<endl;
	return 0;
}
```

期望得分:30分

实际得分:38分

---

 3. $D \le 1000$和$D \le 20000$的部分
 
 既然 "北冥有鱼, 其名为D, D之大, long long存不下",那么就考虑高精
 
 发现可以用二进制表示,那么就再套个bitset优化一下呗~
 
 代码:
 
 ```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<bitset>
using namespace std;
#define N 100010
typedef long long ll;
const ll inf=999999999;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
char a[N],b[N];
ll ans;
int lp,lq;
int e[N];
bitset<N> p,q,tmp;
void Get(char *s,int n,bitset<N> &now){
	for(int i=1;i<=n;i++){
		if(s[i]=='1'){
			now<<=1;
		}
		else if(s[i]=='2'){
			now<<=1;
			now[0]=1;
		}
		else if(s[i]=='U'){
			now=(now>>1);
		}
		else if(s[i]=='L'){
			int j=0;
			while(now[j]==0){
				now.flip(j);
				j++;
			}
			now.flip(j);
		}
		else if(s[i]=='R'){
			int j=0;
			while(now[j]==1){
				now.flip(j);
				j++;
			}
			now.flip(j);
		}
	}
}
ll Abs(ll x){
	return x<0?-x:x;
}
ll Get(){
	ll tmp=0;
	int d=0;
	for(int i=0;i<=lp;i++){
		e[i]=p[i]-q[i]-d;
		if(e[i]<0){
			d=1;
			e[i]+=2;
		}
		else d=0;
		if(e[i]&&i>30)return inf;
	}	
	int j=32;
	while(!e[j]&&j>-1)j--;
	while(j>-1){
		tmp=(tmp<<1)+e[j];
		j--;
	}
	return tmp;
}
int main(){
	scanf("%s",a+1);
	scanf("%s",b+1);
	p=1,q=1;
	int lena=strlen(a+1);
	int lenb=strlen(b+1);
	Get(a,lena,p);
	Get(b,lenb,q);
	int tot=0;
	lp=lq=100001;
	while(p[lp]==0){
		--lp;
	}
	while(q[lq]==0){
		--lq;
	}
	if(lp<lq)swap(lp,lq),swap(p,q);
	while(lp>lq){
		tot++;
		p>>=1;
		lp--;
	}
	for(int i=lp;i>=0;i--){
		if(p[i]<q[i]){
			swap(p,q);
		}
		if(p[i]!=q[i])break;
	}
	ans=inf;
	while((p&q).any()){
		int j=lp;
		ll d=0;
		d=Get();
		ans=min(ans,d+tot);
		tot+=2;
		lp--,lq--;
		p>>=1;
		q>>=1;
	}
	cout<<ans<<endl;
	return 0;
}
```

期望得分:50~70分

实际得分:58分 ~~(开O2变成0分,全RE)~~ (bitset不太会用,如果用的更好的话可以再多拿几分)

---

 4. $D \le 1000000$ (就是正解)
 
 发现进位和退位操作要花很多时间,那么可以把编号的二进制表示搞到一棵线段树上来维护进位和退位操作,这样保证时间复杂度是$O(nlogn)$。
 
 对于$R$操作,找到从右往左第一个0,记为$pos$,然后从$pos+1$到最后都变成0,$pos$变成1,这样就可以完成+1的操作
 
 对于$L$操作,就是-1,那么就和$L$操作相反,不细讲了
 
 剩下的就是插入和删除,~~(什么?插入和删除?那就写个平衡树呗)~~
 
 然后我就写了个$fhq Treap$
 
 代码:
 
 ```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<cmath>
using namespace std;
#define N 200010
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<3)+(x<<1)+c-'0';
        c=getchar();
    }
    return x*f;
}
char s[N];
int a[N],b[N],lena,lenb,root,cnt=0;
struct node{
	int ch[2],siz,sum,key,val;
	int cov;
	void Cover(int d){
		cov=d;
		val=d;
		sum=d*siz;
	}
}t[N];
int NewNode(int data){
	int k=++cnt;
	t[k].key=rand();
	t[k].ch[0]=t[k].ch[1]=0;
	t[k].siz=1;
	t[k].sum=t[k].val=data;
	t[k].cov=-1;
	return k;
}
void update(int k){
	t[k].siz=t[t[k].ch[0]].siz+t[t[k].ch[1]].siz+1;
	t[k].sum=t[t[k].ch[0]].sum+t[t[k].ch[1]].sum+t[k].val;
}
void pushdown(int k){
	if(t[k].cov!=-1){
		if(t[k].ch[0])t[t[k].ch[0]].Cover(t[k].cov);
		if(t[k].ch[1])t[t[k].ch[1]].Cover(t[k].cov);
		t[k].cov=-1;
	}
}
void Split(int k,int data,int &l,int &r){
	if(!k){
		l=r=0;
		return;
	}
	pushdown(k);
	if(t[t[k].ch[0]].siz+1<=data){
		l=k;
		Split(t[k].ch[1],data-t[t[k].ch[0]].siz-1,t[k].ch[1],r);
	}
	else{
		r=k;
		Split(t[k].ch[0],data,l,t[k].ch[0]);
	}
	update(k);
}
int Merge(int l,int r){
	if(!l||!r)return l+r;
	pushdown(l),pushdown(r);
	if(t[l].key<t[r].key){
		t[l].ch[1]=Merge(t[l].ch[1],r);
		update(l);
		return l;
	}
	else{
		t[r].ch[0]=Merge(l,t[r].ch[0]);
		update(r);
		return r;
	}
}
int askr(int k){//查找从右往左第一个1,注意细节
	int ans=0;
	while(1){
		pushdown(k);
		if(t[k].ch[1]&&t[t[k].ch[1]].sum>0){
			ans+=t[t[k].ch[0]].siz+1;
			k=t[k].ch[1];
		}
		else if(t[k].val){
			return ans+t[t[k].ch[0]].siz+1;
		}
		else{
			k=t[k].ch[0];
		}
	}
}
int askl(int k){//查找0,同上
	int ans=0;
	while(1){
		pushdown(k);
		if(t[k].ch[1]&&t[t[k].ch[1]].sum<t[t[k].ch[1]].siz){
			ans+=t[t[k].ch[0]].siz+1;
			k=t[k].ch[1];
		}
		else if(!t[k].val){
			return ans+t[t[k].ch[0]].siz+1;
		}
		else{
			k=t[k].ch[0];
		}
	}
}
void Change(int x,int y,int data){
	int l=0,p=0,r=0;
	Split(root,y,l,r);
	Split(l,x-1,l,p);
	t[p].Cover(data);
	root=Merge(Merge(l,p),r);
}
void Get(int k,int *p,int &pn){
	pushdown(k);//这里窝一开始忘记pushdown了,查了3个小时QAQ
	if(t[k].ch[0])Get(t[k].ch[0],p,pn);
	p[++pn]=t[k].val;
	if(t[k].ch[1])Get(t[k].ch[1],p,pn);
}
void solve(char *s){
	int len=strlen(s+1);
	memset(t,0,sizeof(t));
	root=0;
	cnt=0;
	root=Merge(root,NewNode(1));
	for(int i=1;i<=len;i++){
		if(s[i]=='1'){
			root=Merge(root,NewNode(0));
		}
		else if(s[i]=='2'){
			root=Merge(root,NewNode(1));
		}
		else if(s[i]=='U'){
			int tmp;
			Split(root,t[root].siz-1,root,tmp);
		}
		else if(s[i]=='L'){
			int pos=askr(root);
			Change(pos+1,t[root].siz,1);
			Change(pos,pos,0);
		}
		else{
			int pos=askl(root);
			Change(pos+1,t[root].siz,0);
			Change(pos,pos,1);
		}
	}
}
int main(){
	//freopen("board.in","r",stdin);
	//freopen("board.out","w",stdout);
	srand(time(0));
	scanf("%s",s+1);
	solve(s);
	Get(root,a,lena);
	scanf("%s",s+1);
	solve(s);
	Get(root,b,lenb);
	int r=abs(lena-lenb);
	int n=min(lena,lenb);
	int ans=2*n,dis=0;
	bool d=1;
	for(int i=1;i<=n;i++){
		if(!d){
			dis=dis*2;
			if(a[i]==0)dis++;
			if(b[i]==1)dis++;
		}
		if(a[i]!=b[i]&&d){
			d=0;
			if(a[i]==1)swap(a,b);
		}
		if(dis>ans)break;
		ans=min(ans,dis+!d+2*(n-i));
	}
	cout<<ans+r<<endl;
	return 0;
}
```

不会平衡树的$OIer$可以看这里,std用的是线段树,虽然有插入删除,但也只在序列的末尾,可以提前建好树

这是std的代码:~~(很显然和我的马蜂很不同)~~

[挂在剪贴板里了](https://www.luogu.org/paste/a0x5l1nr)

大家可以参考一下

[*Froggy's blog*](https://www.luogu.org/blog/1445353309froggy/) 欢迎来踩,**呱**!!


---

## 作者：Tony102 (赞：8)

[Link](https://www.luogu.com.cn/problem/P5513)

因为是考试的题目，所以讲下部分分（无疑是暴露了考试的时候没有切掉这道题


**更好的阅读体验[My Blog](https://tony102.xyz/index.php/2020/10/22/luogu5513-ceoi2013board/)**


### 10pts

这一档部分分最多只会有$2^{10}$个点，所以可以直接按照题目描述的方法建图，然后跑一边最短路



### 30pts

现在我们要从$u$到$v$，假设一条路径上最浅的点是$w$

那么从$u$到$w$同深度的点纵方向上至少要跳$dep[u] - dep[w] - 1$个点，对于$v$同理

在$dep[w]$层上，$u$,$v$相遇就要跳$|u\ mod\ 2^{dep[w]} - v\ mod\ 2^{dep[d]}|$条边

所以我们可以枚举这个$w$的深度，则纵向边还需跳$dep[u] - dep[v] - 2 * dep[w]$



### 100pts

考虑正解

**这个题最妙的地方就在于如何用给定字符串求出其与根最短路(只通过纵向边)**

实际上返祖操作和往同层左右点跳的操作都可以转换为往左跳和往右跳

比如说返祖操作，相当于最后一个往左右儿子跳的那个操作不做

对于往同层右边的点跳，假如这个点现在是左儿子，那么相当于跳到右儿子去，就是一次返祖+往右跳

我们用$0$表示往左儿子跳，$1$往右儿子跳，我们现在只要维护一个二进制数，并且可以做一些操作

（建议在纸上手动模拟所有操作和与之对应的二进制操作，下面会直接给出答案）

1. 对于往左儿子跳，相当于在二进制数的末尾填了一个$0$，往右儿子就是$1$
2. 返祖就是去掉最后一位，注意要考虑进位
3. 往同层左边的点跳，相当于给整个数$-1$,右边就是$+1$ （此部分墙裂建议模拟验证）

好了，我们现在只要维护一个二进制数的加法和进位操作就可以了

特别要注意的是，如果直接这么写一个二进制的高精度会被最后一个点卡（卡成$O(n^2)$，可以构造一下）。所以你可以考虑使用线段树把操作的复杂度降到$log$级别，也可以看下文介绍的方法。

注意到返祖和同层跳点这里两种操作是互不影响的。也就是说，改变这两种操作的顺序对答案不会造成影响。同时这两种操作是唯二涉及进位的操作。如果每次进行这两种操作就进位就会被卡，所以其实可以把这两种操作记下来，最后同一进位。



### Summary

这道题的启发就是，把一个不太好维护的操作转换成数的操作。在一棵二叉树上可以优先考虑二进制数。



### Code

又到了我最喜欢的代码环节
```cpp
#include <bits/stdc++.h>
using namespace std;

const int SIZE = 2e5 + 5;
const int inf = (1 << 20);

int lena, lenb;
int a[SIZE], b[SIZE];
char stra[SIZE], strb[SIZE];

inline void carryA(int pos)
{
	a[pos - 1] += ((a[pos] - (a[pos] & 1)) >> 1);
	a[pos] &= 1;
}

inline void carryB(int pos)
{
	b[pos - 1] += ((b[pos] - (b[pos] & 1)) >> 1);
	b[pos] &= 1;
}

inline void solve()
{
	int lentha = strlen(stra), lenthb = strlen(strb);
	for (register int i = 0; i < lentha; ++ i) {
		if (stra[i] == '1') a[++ lena] = 0;
		else if (stra[i] == '2') a[++ lena] = 1;
		else if (stra[i] == 'U') carryA(lena), -- lena;
		else if (stra[i] == 'L') -- a[lena];
		else if (stra[i] == 'R') ++ a[lena];
	}	
	for (register int i = lena; i > 1; -- i) carryA(i);

	for (register int i = 0; i < lenthb; ++ i) {
		if (strb[i] == '1') b[++ lenb] = 0;
		else if (strb[i] == '2') b[++ lenb] = 1;
		else if (strb[i] == 'U') carryB(lenb), -- lenb;
		else if (strb[i] == 'L') -- b[lenb];
		else if (strb[i] == 'R') ++ b[lenb];
	}	
	for (register int i = lenb; i > 1; -- i) carryB(i);
}

int main()
{
	scanf("%s", stra); scanf("%s", strb);
	solve();
	// printf("%d %d\n", lena, lenb);
	int len = std::min(lena, lenb), ans = 2e9, del = 0;
	for (register int i = 0; i <= len && abs(del) < inf; ++ i) {
		del = (del << 1) + (a[i] - b[i]);
		ans = std::min(ans, abs(del) + ((len - i) << 1));
	}	
	printf("%d\n", ans + abs(lena - lenb));
	return 0;
}
```








---

## 作者：Pengzt (赞：4)

[cnblogs](https://www.cnblogs.com/Pengzt/p/17929936.html)

[P5513](https://www.luogu.com.cn/problem/P5513)

容易发现，每次等价于对一个二进制数进行操作。但是这个二进制数长为 $n$，即需要高精。但是这样支持加一和减一是复杂度会退化为 $\mathcal{O}(n^2)$，有一个很正常的做法就压位，仿照 bitset 的做法进行操作，复杂度 $\mathcal{O}(\frac{n ^ 2}{w})$。

这样已经可以通过了，但发现乘除法就是单点赋值，加减法只需要找到最长的一段后缀 $0/1$ 的位置并覆盖，可以使用线段树维护。找最长后缀串可以直接线段树上二分。时间复杂度线性对数。

如果觉得线段树上二分写起来有点麻烦的话可以直接在外面套一个二分，复杂度多出一只 $\log$。

最后统计答案是简单的，一定是到某一层后横向移动在到另一个点，枚举这个层即可。

代码（$\mathcal{O}(n\log^2n)$）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector < int >
#define eb emplace_back
#define pii pair < int, int >
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
int Mbe;
mt19937_64 rng(35);
constexpr int N = 1e5 + 10, inf = 1e9;
int n, m, na, nb;
string a, b;
int val[N << 2], laz[N << 2];
void tag(int x, int v, int L, int R) {
	laz[x] = v;
	val[x] = (R - L + 1) * v;
}
void down(int x, int L, int R) {
	if(~laz[x]) {
		int m = (L + R) >> 1;
		tag(x << 1, laz[x], L, m);
		tag(x << 1 | 1, laz[x], m + 1, R);
		laz[x] = -1;
	}
}
void modify(int x, int L, int R, int l, int r, int v) {
	if(l <= L && R <= r) {
		tag(x, v, L, R);
		return;
	}
	down(x, L, R);
	int m = (L + R) >> 1;
	if(l <= m) modify(x << 1, L, m, l, r, v);
	if(r > m) modify(x << 1 | 1, m + 1, R, l, r, v);
	val[x] = val[x << 1] + val[x << 1 | 1];
}
int ask(int x, int L, int R, int l, int r) {
	if(l <= L && R <= r) return val[x];
	down(x, L, R);
	int m = (L + R) >> 1, res = 0;
	if(l <= m) res += ask(x << 1, L, m, l, r);
	if(r > m) res += ask(x << 1 | 1, m + 1, R, l, r);
	return res;
}
void query(int x, int L, int R, int type) {
	if(L == R) {
		if(type == 1) a[L] = val[x] + '0';
		else b[L] = val[x] + '0';
		return;
	}
	down(x, L, R);
	int m = (L + R) >> 1;
	query(x << 1, L, m, type);
	query(x << 1 | 1, m + 1, R, type);
}
int search(int R, int len, int type) {
	int l = 1, r = R;
	while(l <= r) {
		int m = (l + r) >> 1;
		if(ask(1, 1, len, m, R) == (R - m + 1) * type) r = m - 1;
		else l = m + 1;
	}
	return l;
}
void solve(int n, int type) {
	int now = 0;
	memset(laz, -1, sizeof(laz));
	memset(val, 0, sizeof(val));
	string s;
	if(type == 1) s = a;
	else s = b;
	for(int i = 1; i <= n; ++i) {
		if(s[i] == '1') {
			++now;
			modify(1, 1, n, now, now, 1);
		} else if(s[i] == '2') {
			++now;
			modify(1, 1, n, now, now, 2);
		} else if(s[i] == 'U') {
			modify(1, 1, n, now, now, 0);
			--now;
		} else if(s[i] == 'L') {
			int p = search(now, n, 1);
			if(p <= now) modify(1, 1, n, p, now, 2);
			modify(1, 1, n, p - 1, p - 1, 1);
		} else {
			int p = search(now, n, 2);
			if(p <= now) modify(1, 1, n, p, now, 1);
			modify(1, 1, n, p - 1, p - 1, 2);
		}
	}
	query(1, 1, n, type);
	if(type == 1) na = now;
	else nb = now;
}
int Med;
int main() {
	fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
	ios :: sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> a >> b;
	n = a.size(), m = b.size();
	a = " " + a, b = " " + b;
	solve(n, 1);
	solve(m, 2);
	if(a > b) {
		swap(na, nb);
		swap(a, b);
	}
	int now = 0, ans = na + nb;
	for(int i = 1; i <= na; ++i) {
		if(now < inf) {
			now *= 2;
			if(a[i] == '1' && b[i] == '2') ++now;
			else if(a[i] == '2' && b[i] == '1') --now;
		}
		ans = min(ans, na - i + nb - i + now);
	}
	cout << ans << "\n";
	cerr << TIME << "ms\n";
	return 0;
}
```

---

## 作者：robinyqc (赞：2)

这是一个 C++ 压位高精题解。因为考场上交不了 python 嘤嘤嘤。

***

首先分析题目。可以根据线段树的标号方式对这颗二叉树标号。设当前节点为 $x$，那么：

+ 左儿子是 $2x$。
+ 右儿子是 $2x + 1$。
+ 父亲是 $\left\lfloor \frac x2 \right\rfloor$。
+ 左边兄弟（如果有）是 $x - 1$。
+ 右边兄弟（如果有）是 $x + 1$。

我们还是拿这张图说话：

![](https://cdn.luogu.com.cn/upload/pic/74384.png)

当两个点 $A, B$ 在同一层的时候，一个显然的距离是 $|A - B|$。

贪心地来看，最短路的策略一定是两者跳父亲跳到某层，然后横着走。

当两个点不在同一层的时候，让深度较深的那个跳父亲直到深度相等一定是最优的。可以将总距离分解成纵向（向父亲）距离和横向（向兄弟）距离。纵向距离是不变的，横向距离每往上跳一次都减半。所以跳到同一层是比不在同一层优的。

现在我们就只用关心，怎么求出 $A$ 和 $B$ 的具体位置。

直接无脑高精！反正加一，乘二，除以二这些操作都很好维护。

不过 $O(n^2)$ 的复杂度还是不太能接受。此时我们上压位！复杂度变为 $O(\frac {n^2}w)$。注意到做加法或乘法时，位数都最多加一。所以还会带一个二分之一的常数，那么 $w = 128$。可以接受。

现在我们得到了 $A$ 和 $B$ 的具体位置，最后的答案怎么求？

我们是要枚举深度 $x$，然后求 $A$ 的高 $x + 1$ 位与 $B$ 的高 $x + 1$ 位的差。再写一个高精度减法很不好。首先我们可以让两个数一直往上跳，在 $1$ 处汇合，这样距离是 $O(n)$ 的，答案大于这个值直接跳过即可，这样两个数的差只用 int 就能储存。同时考虑枚举深度 $x$ 的过程，设 $x$ 对应的差是 $d_x$，一定满足 $d_x = 2d_{x - 1} + A_x - B_x$。这样就可以线性推出答案了。

代码：

```cpp
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

#define ull unsigned long long

struct DynInt
{
    vector<ull> b;

    DynInt() { b.reserve(200000); b.push_back(1); }

    void self_add()
    {
        vector<ull>::iterator it = b.begin();
        ++*it;
        while (*it == 0) {
            ++it;
            if (it == b.end()) b.push_back(0ull);
            ++*it;
        }
    }

    void self_dec()
    {
        vector<ull>::iterator it = b.begin();
        while (*it == 0) {
            --*it;
            ++it;
        }
        --*it;
    }

    void self_left_shift()
    {
        ull h = 0;
        for (ull& i : b) {
            if (i >> 63) i = i << 1 | h, h = 1ull;
            else i = i << 1 | h, h = 0ull;
        }
        if (h) b.push_back(1ull);
    }

    void self_right_shift()
    {
        ull h = 0;
        vector<ull>::iterator it = prev(b.end());
        while (it != b.begin()) {
            if (*it & 1) *it = h | (*it >> 1), h = 1ull << 63;
            else *it = h | (*it >> 1), h = 0ull;
            --it;
        }
        *it = h | (*it >> 1);
    }

    void print(string& x)
    {
        for (ull& i : b) {
            for (int j = 0; j < 64; ++j) x.push_back(((i >> j) & 1));
        }
        while (!x.back()) x.pop_back();
    }
};

signed main()
{
    ios::sync_with_stdio(false);
    string s;
    cin >> s;
    DynInt A, B;
    for (char i : s) {
        if (i == '1') A.self_left_shift();
        else if (i == '2') A.self_left_shift(), A.self_add();
        else if (i == 'U') A.self_right_shift();
        else if (i == 'L') A.self_dec();
        else A.self_add();
    }
    cin >> s;
    for (char i : s) {
        if (i == '1') B.self_left_shift();
        else if (i == '2') B.self_left_shift(), B.self_add();
        else if (i == 'U') B.self_right_shift();
        else if (i == 'L') B.self_dec();
        else B.self_add();
    }
    string a, b;
    int up = 0, ans = 300005;
    A.print(a);
    B.print(b);
    if (a.size() < b.size()) swap(a, b);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    while (a.size() > b.size()) a.pop_back(), ++up;
    if (a < b) swap(a, b);
    int diff = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        diff = diff * 2 + a[i] - b[i];
        if (abs(diff) > 1000000) break;
        ans = min(ans, abs(diff) + up + ((int)a.size() - i - 1) * 2);
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Asterviel (赞：1)

考虑在我们已知位置的情况下求出最小距离：我们令 $u$ 的深度大于等于 $v$ 的深度，则最小距离必然是将 $u$ 向上跳到 $dep_v$，再 $u$ 和 $v$ 一起向上跳到某一深度后横向交汇。

答案必然不可能使 $v$ 向下跳若干层再与 $u$ 横向交汇，因为显然越往下点数就越多，横向交汇的代价也会增大，让 $u$ 向上跳的答案不会比这个更劣。

那么在我们知道 $u$ 和 $v$ 的位置之后，我们可以通过枚举 $u$ 和 $v$ 横向交汇的层数以算出答案，显然这个答案不会超过 $dep_u + dep_v$，所以横向交汇的代价不会超过 $2 \times 10 ^ 5$。

那么现在我们发现题目所给的位置表示方式太复杂了，考虑可以将表示位置的形式简化为一个只由 $1$ 和 $2$ 组成的序列。我们考虑朴素维护简化的过程：

- 遇到一个 $\text{1}$：在新序列中加入一个 $\text{1}$；

- 遇到一个 $\text{2}$：在新序列中加入一个 $\text{2}$；

- 遇到一个 $\text{U}$：去掉新序列中最后一个数；

- 遇到一个 $\text{L}$：找到最后一次出现 $\text{2}$ 的位置，我们将其记为 $pos$，则反转 $[pos, len]$。（$len$ 表示目前新序列的长度。）

- 遇到一个 $\text{R}$：找到最后一次出现 $\text{1}$ 的位置，我们将其记为 $pos$，则反转 $[pos, len]$。（$len$ 表示目前新序列的长度。）

我们发现对于 $\text{L}$ 和 $\text{R}$ 的操作不是平凡的，这里我介绍 $\text{L}$ 操作的做法，另一个同理。

观察性质得到：必然是修改最后两个连续颜色段 $22 \dots 2211 \dots 1 \Rightarrow 22 \dots 2122 \dots 2$。我们只维护连续颜色段就可以做到 $\mathcal{O}(1)$ 修改了。

具体地说：我们用 `vector<pair<int, int> v` 存储每个连续颜色段的颜色和长度。`add(x, num)` 表示在序列背后加入 num 个 x，`del()` 表示删除颜色段中最后一个字母。

维护颜色段代码如下：

```cpp
auto add = [&](int x, int num) -> void
{
    if(v.empty()) return void(v.emplace_back(x, num));// 特判颜色段为空，v.back()会RE
    if(v.back().first == x) v.back().second += num;// 和最后一段颜色相同，直接合并
    else v.emplace_back(x, num);// 和最后一段颜色不同，新建一段
};
auto del = [&]() -> void{if(--v.back().second == 0) v.pop_back();};// 最后一段删空了，去掉最后一段。

for(int i(1); i <= n; i++)
{
    if(ch[i] <= '2') add(ch[i] - '0', 1);// 加入到最后
    if(ch[i] == 'U') del();// 去掉最后一个
    if(ch[i] == 'L') 
    {
        if(v.back().first == 2) {del(); add(1, 1); continue;}// 特判
        int num(v.back().second); v.pop_back();// 翻转最后一段
        del(), add(1, 1), add(2, num);// 翻转最后一个1
    }
    if(ch[i] == 'R')
    {
        if(v.back().first == 1) {del(); add(2, 1); continue;}// 特判
        int num(v.back().second); v.pop_back();// 翻转最后一段
        del(), add(2, 1), add(1, num);// 翻转最后一个2
    }
}

n = 0;
for(auto [x, y] : v) for(int i(1); i <= y; i++) a[++n] = x - 1;// 根据颜色段算出新序列。
```

计算最小距离代码如下：

```cpp
int num(n[0] + n[1]), ans(n[0] + n[1]), posa(1), posb(1);
// num表示向上跳到第i层的代价，ans表示最小距离
for(int i(1); i <= min(n[0], n[1]); i++)
{
    posa = (posa << 1) + a[0][i];
    posb = (posb << 1) + a[1][i];
    int mn(min(posa, posb)); posa -= mn, posb -= mn;
    if(abs(posb - posa) > ans) break;// 横向移动的距离不会超过 dep_u + dep_v
    num -= 2;
    ans = min(ans, num + abs(posb - posa));
}
cout << ans << "\n";
```

顺带提一嘴，这题数据太水了，容易发现这份[代码](https://www.luogu.com.cn/paste/k76yqf2n)的时间复杂度是 $O(N ^ 2)$ 级别的，但是它[跑过了](https://www.luogu.com.cn/record/135031148)。。。

---

## 作者：baoziwu2 (赞：1)

~~python可过~~

~~去你的高精~~

节点数是指数级别的，不可能存下，考虑给每个节点下发一个编号，可以类比线段树的编号方式，这样移动节点的操作会十分简便（不妨令当前节点编号为 $p$）：

- 1：移动到左儿子 $p \times 2$。
- 2：移动到右儿子 $p \times 2 + 1$。
- 3：移动到父亲 $p \div 2$。
- 4：移动到左兄弟 $p - 1$。
- 5：移动到右兄弟 $p + 1$。

接下来考虑如何求最短路，没有必要建图跑广搜（~~不然指数复杂度你对节点编号的意义何在呢~~）。可以发现，可能成为最短路的一定是类似先向上走一段，然后中间平着走一段，然后往下走一段这样三段拼成的（看情况可以去掉向下或向上的路线）。

性感理解一下，向走的目的是为了缩短水平的距离，在水平方向走完之前既执行向上又执行向下一定不会更优，因为这种操作一定不会是水平距离变得比直上直下的路径更短，同时因为你反复上下的原因，竖直距离也不会更优，所以不是这种三段式路径一定不会成为最短路。

思考这种路径最多会出现几条，答案是 $O(D)$ 条，因为向上最多走 $D$ 步就不能再走了。

代码实现就很简单了，因为 c++ 要用高精所以选择了 python。

```python3
import math

def leftSon(x): return x << 1
def rightSon(x): return (x << 1) | 1
def fa(x): return x >> 1
def leftBro(x): return x - 1
def rightBro(x): return x + 1

def getDepth(x): return int(math.log2(x))

def shortPath(x, y):
    depX = getDepth(x)
    depY = getDepth(y)
    dis = 0
    if depX < depY:
        x, y = y, x
        depX, depY = depY, depX
    while depX > depY:
        x = fa(x)
        depX -= 1
        dis += 1
    res = dis + abs(x - y)
    while x != y:
        dis += 2
        x = fa(x)
        y = fa(y)
        res = min(res, dis + abs(x - y))
    return res

def getPos(s):
    rt = 1
    for x in s:
        if x == '1': rt = leftSon(rt)
        elif x == '2': rt = rightSon(rt)
        elif x == 'U': rt = fa(rt)
        elif x == 'L': rt = leftBro(rt)
        elif x == 'R': rt = rightBro(rt)
    return rt

a = input()
b = input()
pos1 = getPos(a)
pos2 = getPos(b)
print(shortPath(pos1, pos2))
```

---

## 作者：Azazеl (赞：1)

#### 题意

> $~~~~$ 给出一棵无穷大的满二叉树，给每一层相邻的节点连边，并给出五种操作。从根节点开始用操作序列描述两个点，求这两个点的最短路。

---

#### 题解

$~~~~$ 感觉没有多少人说清楚为什么是往上跳。~~（虽然这个感性理解一下就行~~

$~~~~$ 如果我们把这棵二叉树每个节点像线段树一样编号（每个节点左儿子为该节点编号 $\times 2$，右儿子为该节点编号 $\times 2+1$） ，那么这五种操作依次对应：

- 移动到左儿子：$\times 2$
- 移动到右儿子：$\times 2+1$
- 移动到父亲节点：$/2$
- 移动到同层左边节点：$-1$
- 移动到同层右边节点：$+1$

$~~~~$ 所以我们最终可以得到两个点所在的编号。现在考虑怎么根据编号求最短路。

$~~~~$ 首先不难想到我们会把所在较深的点向上跳（不停 $/2$ ）到与另一个节点同层，因为我们若让较浅的节点向下，由于更深的层数**横向边只会增多**，相当于向下走一步的最好情况是不会增加额外要走的横向边，而向上走的最劣情况是**横向边不减少**，因此答案比起向上一定**不会变优**。

$~~~~$ 因此两个节点一定走到较浅的点所在层数及以上的某层后通过该层之间的横向边相遇，考虑枚举走到的层数，那么在该层相遇要走的横向边为两个点跳到的点的编号之差的绝对值。

$~~~~$ 剩下的部分就像其他题解一样把每个操作改为用二进制高精即可。（或者线段树，平衡树）

$~~~~$ 同时还要注意，在太深的位置的答案同理一定不会比在更浅的位置更优，因此我们设置一个阈值，从浅到深枚举，当现在枚举层的横向边之差超过该值时直接停止枚举即可。

---

#### 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;
const ll INF=(1<<20);
char s1[100005],s2[100005];
int cnta,cntb,A[100005],B[100005];
inline ll Abs(ll x){return x>0?x:-x;}
void SolveA(int k)//将第 k 位进位或者借位 
{
	A[k-1]+=A[k]/2;A[k]%=2;
	if(A[k]<0) A[k-1]--,A[k]=1;
}
void SolveB(int k)
{
	B[k-1]+=B[k]/2;B[k]%=2;
	if(B[k]<0) B[k-1]--,B[k]=1;
}
void Work()
{
	int len1=strlen(s1+1),len2=strlen(s2+1);
	for(int i=1;i<=len1;i++)
	{
		if(s1[i]=='1') A[++cnta]=0;
		if(s1[i]=='2') A[++cnta]=1;
		if(s1[i]=='U') SolveA(cnta),cnta--;
		if(s1[i]=='L') A[cnta]--;
		if(s1[i]=='R') A[cnta]++;
	}
	for(int i=1;i<=len2;i++)
	{
		if(s2[i]=='1') B[++cntb]=0;
		if(s2[i]=='2') B[++cntb]=1;
		if(s2[i]=='U') SolveB(cntb),cntb--;
		if(s2[i]=='L') B[cntb]--;
		if(s2[i]=='R') B[cntb]++;
	}
	for(int i=cnta;i>=1;i--) SolveA(i);
	for(int i=cntb;i>=1;i--) SolveB(i);
}
int main() {
	scanf("%s %s",s1+1,s2+1);
	Work();
	ll Ans=2e9,tmp=0;
	for(int i=1;i<=min(cnta,cntb)&&Abs(tmp)<INF;i++)//
	{
		tmp=(tmp<<1)+(A[i]-B[i]);
		Ans=min(Ans,cnta-i+cntb-i+Abs(tmp));//注意绝对值
	}
	printf("%lld",Ans);
	return 0;
}
```





$~~~~$ 

---

## 作者：warzone (赞：1)

再被奆佬虐了无数回后，难得考场上AC了一道题QWQ。  
这一题考的是高精度和二叉树节点的分析。 


----------------

首先，敲多了堆模板就可以知道，移动的过程相当于在一个堆上跳，设当前编号为 `p`

- `1` 堆中新增一个元素，即 `p++`
- `2` 堆中删除一个元素，即 `p--`
- `U` 跳到父节点，即 `p=p>>1`
- `L` 跳到左儿子，即 `p=p<<1`
- `R` 跳到右儿子，即 `p=p<<1|1`

于是我们可以通过二进制高精（下标低的为高位，方便移位），  
将操作序列直接转化为节点的编号，而这也反映了节点的位置。  
但是这里有一个问题，就是一次暴力 `++` 和 `--` 是 $\Theta(D)$ 的。  
不过可以发现 $S\le10^5$，于是 增加/减少量 $\le 10^5$。  
所以采取 FFT 优化高精乘时的方法：不压位，不在计算时进位，只在最后把所有进位一波推过去。  
由于 `U` 操作时末位会舍去，所以这时也要处理进位的影响。  
至此，我们用 $\Theta(S)$ 而不是 $\Theta(DS)$ 的复杂度处理出了节点的位置。  

----------------

接下来就是计算最短路径了，  
首先如果两个节点深度不同，一定要经过竖直边(显然)。  
我们可以发现，两个深度相同节点的水平距离为二者编号的差（由 `++` 和 `--` 可得），  
于是 **在深度越浅的情况下，水平距离越短(可能相等)** 。  
为了最小化水平距离，肯定是深度深的节点先往上跳到与深度浅的节点相同的深度，而不是相反或互相靠近。  
接下来，有两种选择：  

- 两个节点继续同步往上跳。 
- 计算水平距离。

(为什么是同步？由于高度不同，不同步的上跳与同步在本质上没有区别，如下图)  
![](https://cdn.luogu.com.cn/upload/image_hosting/5xugvsot.png)  
![](https://cdn.luogu.com.cn/upload/image_hosting/nryi72m6.png)  
我们可以发现，向上跳的深度是特别小的，不超过 $D$。  
但是水平距离最大可达到 $2^D$，呈指数增长，当然，也有例外的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/y1q69j8g.png)

（如图，尽管深度不断增加，水平距离始终是 $1$）  
当然，水平距离是可以递推的，设深度为 $i$ 时的水平距离为 $dis_i$，这一位上两点编号的值分别为   
$a_i,b_i(a\ge b)$，则 $dis_i=2dis_{i-1}+(a_i-b_i)$ (显然)。  
由浅入深统计答案，当 $dis_i$ 大于某一个很大的值（比如 $10^6$）时，退出就可以辣 ~\\(≧▽≦)/~  。  
这里最坏复杂度是 $\Theta(D)$，不需要高精度。

---------

最终代码（指针写的，略丑，但是写起来方便，跑得快）
```cpp
#include<stdio.h>
typedef long long ll;
int num1[100010],num2[100010];
int main(){
	int *top1=num1,*top2=num2;
	*top1=*top2=1;
	char c=getchar();
	while(c==' '||c=='\n') c=getchar();
	for(;c!=' '&&c!='\n'&&c!=EOF;c=getchar())
		if(c=='U'){
			if(*(top1--)>=0) *top1+=*(top1+1)>>1;
			else *top1-=(-*(top1+1)+1)>>1;
		}//向父节点跳时计算进位 
		else if(c=='L') --*top1;
		else if(c=='R') ++*top1;
		else if(c=='1') *(++top1)=0;
		else if(c=='2') *(++top1)=1;
	//获取第一个点的编号 
	for(int* i=top1;i!=num1;--i)
		if(*i>=0) *(i-1)+=*i>>1,*i&=1;
		else *(i-1)-=(-*i+1)>>1,*i=(-*i)&1;
	//最后统一计算进位 
	while(c==' '||c=='\n') c=getchar();
	for(;c!=' '&&c!='\n'&&c!=EOF;c=getchar())
		if(c=='U'){
			if(*(top2--)>=0) *top2+=*(top2+1)>>1;
			else *top2-=(-*(top2+1)+1)>>1;
		}
		else if(c=='L') --*top2;
		else if(c=='R') ++*top2;
		else if(c=='1') *(++top2)=0;
		else if(c=='2') *(++top2)=1;
	for(int* i=top2;i!=num2;--i)
		if(*i>=0) *(i-1)+=*i>>1,*i&=1;
		else *(i-1)-=(-*i+1)>>1,*i=(-*i)&1;
	//获取第二个点的编号,同上 
	ll ans=0;
	while(top1-num1>top2-num2) ++ans,--top1;
	while(top2-num2>top1-num1) ++ans,--top2;
	//校正两个点的高度差，计入答案 
	int lca=0;
	for(c=0;lca<=top1-num1;++lca){
		if(num1[lca]>num2[lca]){c=1;break;}
		if(num1[lca]<num2[lca]){c=0;break;}
	}//求两点的LCA(即编号的LCP)，并比较两个点编号的大小 
	if(--lca==top1-num1) printf("%llu",ans);
	else{//从LCA开始往下递增深度 
		ll min=ans+=(top1-num1-lca)<<1,get=0;
		for(++lca;lca<=top1-num1;++lca){
			ans-=2,get=(get<<1)+(c? num1[lca]-num2[lca]:num2[lca]-num1[lca]);
			if(min>ans+get) min=ans+get;//统计答案 
			else if(get>(1<<20))break;//如果水平距离大于某一个值，退出 
		}
		printf("%llu",min);
	}
	return 0;
}
```

既然最终复杂度是 $\Theta(D)$ 的，为什么不加强到 $10^7$ 呢。（求数据加强）

---

## 作者：jr_linys (赞：1)

这篇题解讲一下用栈计算两点编号的方法。

从上到下，从左到右依次给每个点从 $1$ 标号，在二进制下可以发现：  
- `1` 就是在后面加个 `0`
- `2` 就是在后面加个 `1`
- `U` 就是去掉最后一位
- `L` 就是在二进制下 `-1`，即将最后一段连续的 `0` 变为 `1`，最后一个 `1` 变为 `0`
- `R` 就是在二进制下 `+1`，即将最后一段连续的 `1` 变为 `0`，最后一个 `0` 变为 `1`

在最前面塞一个无限长的前导零会好处理一些。  
将连续的相同数字缩在一起即可 $O(1)$ 进行操作。

最后从上到下枚举两点最终会向上跳到哪一层再横向跳，如果横下距离已经比目前答案大就退出。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5,INF=1<<30;
pair<bool,int> st[N+5];
int top,ans=N*2,s;
void del(){//去掉最后一位
	if(st[top].second>1) --st[top].second;
	else --top;
}
int del(bool f){//去掉最后一段连续的 f
	if(st[top].first==f) return st[top--].second;
	return 0;
}
void add(bool f,int s=1){//在末尾加 s 个 f
	if(s==0) return;
	if(st[top].first==f) st[top].second+=s;
	else st[++top]={f,s};
}
string a,b;
void work(string &s){
	cin>>s;
	st[top=0]={0,INF},st[++top]={1,1};
	int sum;
	for(char c:s)
		if(c=='1') add(0);
	else if(c=='2') add(1);
	else if(c=='U') del();
	else if(c=='L') sum=del(0),del(),add(0),add(1,sum);
	else if(c=='R') sum=del(1),del(),add(1),add(0,sum);
	s.clear();
	for(int i=1;i<=top;++i) for(int j=1;j<=st[i].second;++j) s+=st[i].first;
}

int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.in","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	work(a),work(b);
	for(int i=0;i<min(a.size(),b.size());++i){
		s=s*2+a[i]-b[i];
		if(abs(s)>=ans) break;
		ans=min(ans,abs(s)+(int)a.size()+(int)b.size()-i*2-2);
	}
	printf("%d",ans);
}
```
这是我模拟赛的代码注释掉了文件读写，你可以看到两个 `"tree.in"`......

---

## 作者：LCat90 (赞：0)

算是独立切了一道紫题吧。线段树调久了。

从部分分入手。

## $n\le 10$

暴力建树。

## $n\le 50$

暴力建树不行了，我们考虑记录两个点在树上的信息。

记 $(x,y)$ 表示深度为 $x$，此深度中从左往右的第 $y$ 个点。$y$ 最大可以到 $2^x$，所以要用 ``long long``。

现在考虑从 $A$ 到 $B$ 最短路应该怎么走。（$A,B$ 的坐标可以）

+ 一定不会绕到更深的点。

+ 在横向行走之前，一定不会向上走。

证明应该是容易的，建议结合图推一下。

我们考虑先让深度大的点向父亲爬到深度相同的地方，然后枚举两个点一起向上的深度，就可以计算了。（实现可以给点按照 $x,2x,2x+1$ 编号）

## $n\le 10^3$

上面做法的瓶颈在于 $y$ 太大存不下。（所以有一种方法是压位高精）

+ 答案的最大值不超过 $2D$。

显然，$A$ 和 $B$ 一直向上跳到根节点是 $2D$。

首先，记录路径（向左/右儿子）表示出 $A$ 和 $B$。我们就需要对 ``L/R`` 操作进行转化。``L`` 为例，考虑找到前面最近的向右子树的路径，将其改为 ``L``，然后再将剩下后面的路径都改为向左。考虑使用栈来维护之。

然后我们将 $n\le 50$ 的做法依据答案最大值限制优化，从 $A$ 和 $B$ 的 LCA 处出发（设编号为 $1$），从上往下走向 $A$ 和 $B$，等到深度 $d$ 时的答案大于最大值 $2D$ 后，直接退出即可。
 
## $n\le 10^5$

上面的瓶颈在于预处理时不停地出栈入栈会达到 $O(n^2)$。

其实 ``L/R`` 操作的本质是查询前面最后的一个 0/1，然后区间修改。

所以想到使用线段树优化，最后单点查询 0/1，再按照上面的方法做就可以了。

或者我们用两个栈存储 0/1 的最后一个位置，需要时直接去栈顶即可。覆盖就直接在栈顶加。这种方法非常好码。

时间复杂度 $O(n\log n)$。代码很冗余不建议看。

-----

```cpp
#include <bits/stdc++.h>
#define lson p << 1
#define rson p << 1 | 1
#define pb push_back
using namespace std;
const int N = 2e5 + 5;
int n, m, depa, depb, cnta, cntb, ans; // 
char a[N], b[N];
int fn1[N], fn2[N];
stack <int> A, B;

struct node {
	int l, r, num1, num0;
	int m0, m1;
	int tag; // -1:不变   
} T[N << 2]; 
void pushdown(int p) {
	if(T[p].tag != -1) {
		T[p << 1].tag = T[p].tag; T[rson].tag = T[p].tag;
		if(T[p].tag == 0) 	
	T[lson].num0 = T[lson].r - T[lson].l + 1, T[lson].num1 = 0, T[lson].m0 = T[lson].r, T[lson].m1 = -1,
	T[rson].num0 = T[rson].r - T[rson].l + 1, T[rson].num1 = 0, T[rson].m0 = T[rson].r, T[rson].m1 = -1;
		else 
	T[lson].num1 = T[lson].r - T[lson].l + 1, T[lson].num0 = 0, T[lson].m1 = T[lson].r, T[lson].m0 = -1,
	T[rson].num1 = T[rson].r - T[rson].l + 1, T[rson].num0 = 0, T[rson].m1 = T[rson].r, T[rson].m0 = -1;
		T[p].tag = -1;
	}
}
void pushup(int p) {
	T[p].num0 = T[lson].num0 + T[rson].num0;
	T[p].num1 = T[lson].num1 + T[rson].num1;
	T[p].m0 = max(T[p << 1].m0, T[p << 1 | 1].m0);
	T[p].m1 = max(T[lson].m1, T[rson].m1);
}
void build(int p, int l, int r) {
	T[p].l = l, T[p].r = r, T[p].num1 = T[p].num0 = 0, T[p].tag = -1;
	T[p].m0 = T[p].m1 = -1;
	if(l == r) return ;	
	int mid = l + r >> 1; 
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
void update(int p, int l, int r, int x) { // 区间覆盖 
	if(T[p].l >= l and T[p].r <= r) {
		T[p].tag = x;
		if(x == 0) T[p].num0 = T[p].r - T[p].l + 1, T[p].num1 = 0, T[p].m0 = T[p].r, T[p].m1 = -1;
		if(x == 1) T[p].num1 = T[p].r - T[p].l + 1, T[p].num0 = 0, T[p].m1 = T[p].r, T[p].m0 = -1;
		return ;
	}
	pushdown(p);
	int mid = T[p].l + T[p].r >> 1;
	if(l <= mid) update(p << 1, l, r, x);
	if(r > mid) update(p << 1 | 1, l, r, x);
	pushup(p);
}
int query(int p, int l, int r, int x) {
	if(x == -1) { // 单点查询 
		if(T[p].l == l and T[p].r == l) return (T[p].num0 ? 0 : 1);
		int mid = T[p].l + T[p].r >> 1;
		pushdown(p);
		if(l <= mid) return query(p << 1, l, r, x);
		else return query(p << 1 | 1, l, r, x);
	}  
	else { // 查询前驱 
		if(T[p].l >= l and T[p].r <= r) return (x == 0 ? T[p].m0 : T[p].m1);
		int mid = T[p].l + T[p].r >> 1;
		pushdown(p); int ans = 0;
		if(x == 0) {
			if(r > mid) ans = max(ans, query(p << 1 | 1, l, r, x));
			if(l <= mid) ans = max(ans, query(p << 1, l, r, x));
		}
		if(x == 1) {
            if(r > mid) ans = max(ans, query(p << 1 | 1, l, r, x));
			if(l <= mid) ans = max(ans, query(p << 1, l, r, x));
		}
        return ans;
	}
}
signed main() {
	scanf("%s %s", a + 1, b + 1);
	n = strlen(a + 1), m = strlen(b + 1);
	cnta = cntb = 0;
	build(1, 1, n);
	for(int i = 1;i <= n; ++i) {
		if(a[i] == '1') { ++cnta; update(1, cnta, cnta, 0); } 
		if(a[i] == '2') { ++cnta; update(1, cnta, cnta, 1); }
		if(a[i] == 'U') { --cnta; }
		if(a[i] == 'L') { // 查询前面第一个 R 
			int id = query(1, 1, cnta, 1);
			update(1, id, id, 0);
			update(1, id + 1, cnta, 1);
		} 
		if(a[i] == 'R') {
			int id = query(1, 1, cnta, 0);
			update(1, id, id, 1);
			update(1, id + 1, cnta, 0);
		}
	} // 区间修改为 1/2 + 单点修改 + 查询前面第一个 
	for(int i = 1;i <= cnta; ++i) A.push(query(1, i, i, -1)); 
	build(1, 1, m);
	for(int i = 1;i <= m; ++i) {
		if(b[i] == '1') { ++cntb; update(1, cntb, cntb, 0); } 
		if(b[i] == '2') { ++cntb; update(1, cntb, cntb, 1); }
		if(b[i] == 'U') { --cntb; }
		if(b[i] == 'L') { // 查询前面第一个 R 
			int id = query(1, 1, cntb, 1);
			update(1, id, id, 0);
			update(1, id + 1, cntb, 1);
		} 
		if(b[i] == 'R') {
			int id = query(1, 1, cntb, 0);
			update(1, id, id, 1);
			update(1, id + 1, cntb, 0);
		}
	}
	for(int i = 1;i <= cntb; ++i) { B.push(query(1, i, i, -1)); } 
	if(A.size() < B.size()) swap(A, B);
	ans = A.size() - B.size();  //cout << ans << " ";
	while(A.size() != B.size()) A.pop(); 
	cnta = A.size(), cntb = A.size();
	int tmp = A.size(); 
	while(!A.empty()) {
		fn1[cnta--] = A.top();
		fn2[cntb--] = B.top();
		A.pop(); B.pop();
	}
	for(int i = 1;i <= tmp; ++i) 
		if(fn1[i] != fn2[i]) { 
			int tmp1, tmp2; tmp1 = tmp2 = 1; int sum = 1e9; 
			for(int j = i;j <= tmp; ++j) {
				tmp1 = 2 * tmp1 + fn1[j]; tmp2 = 2 * tmp2 + fn2[j];
				if(abs(tmp2 - tmp1) > 1e6) break ; 
				sum = min(sum, abs(tmp2 - tmp1) + 2 * (tmp - j));
			}
			cout << ans + sum;
			return 0;
		}
	cout << ans;
 	return 0;
}
```

---

## 作者：FatOldEight (赞：0)


[更慢的阅读体验。](https://fat-old-eight.github.io/%E9%A2%98%E8%A7%A3/2023/11/14/solution-p5513.html)

---

### 题意

[P5513 [CEOI2013] Board](https://www.luogu.com.cn/problem/P5513)

### 思路

首先给每个节点编个号，类似于线段树，设当前节点为 $x$，则左儿子为 $2x$，右儿子为 $2x+1$。

这样我们就能用一个二进制数表示每个节点的位置。

并且容易发现，点 $x$ 和点 $y$ 之间的最短路为：

$$
\min\limits_{a,b}{ (\lvert\lfloor\frac{x}{2^a}\rfloor-\lfloor\frac{y}{2^b}\rfloor\rvert+a+b)[h(\lfloor\frac{x}{2^a}\rfloor)=h(\lfloor\frac{y}{2^b}\rfloor })]
$$

$h(x)$ 表示 $x$ 的最高二进制位在第几位。

很抽象？说人话就是将 $x,y$ 向上跳到同一高度后，他们的之间的差的绝对值取最小值。

图示：

![piJowut.png](https://z1.ax1x.com/2023/11/14/piJowut.png)

三条线即为 $x,y$ 之间最短路的三种可能取值。

计算答案流程就是：

假设 $x$ 大于 $y$。

先将 $x$ 向上跳至和 $y$ 同一高度，然后计算 $x$ 和 $y$ 的差。 

再把 $x$ 和 $y$ 同时向上跳一个父亲。

重复上面操作直到 $x,y$ 重合。

关于处理 $x,y$ 位置，只需要处理几种操作分别是向哪里转移，模拟即可。

但是还有一个问题：$x,y$ 的最大值为 $2^{10^5}$，这存不下。

所以要使用高精度。

但是普通的高精是 $O(n^2)$ 的，不能通过。

于是我们可以参考一下 bitset，将多个进制位用同一个数存下即可。

时间复杂度 $O(\frac{n^2}{\omega})$，$\omega$ 取 $60$ 即可。

### code

```cpp
#include<cstring>
#include<iostream>
using namespace std;
const int N=61;
struct BYDSET//普通压位高精
{
    long long a[2005];
    int L;
    BYDSET(){L=0;memset(a,0,sizeof(a));}
    void rmove()
    {
        for(int i=L;~i;i--)
        {
            a[i]<<=1;
            if(a[i]&(1ll<<(N+1)))a[i+1]|=1,a[i]^=(1ll<<(N+1));
        }
        if(a[L+1])L++;
    }
    void lmove()
    {
        for(int i=0;i<=L;i++)
        {
            if((a[i]&1)&&i)a[i-1]|=(1ll<<N);
            a[i]>>=1;
        }
        if(!a[L]&&L)L--;
    }
    void push()
    {
        a[0]++;
        for(int i=0;i<=L;i++)
        {
            if(a[i]>=(1ll<<(N+1)))
            {
                a[i]-=(1ll<<(N+1));
                a[i+1]++;
            }
            else break;
        }
        if(a[L+1])L++;
    }
    void idk()
    {
        a[0]--;
        for(int i=0;i<=L;i++)
        {
            if(a[i]<0)
            {
                a[i]+=(1ull<<(N+1));
                a[i+1]--;
            }
            else break;
        }
        if(!a[L]&&L)L--;
    }
    int highbit()
    {
        for(int i=N;~i;i--)if(a[L]&(1ull<<i))return i+L*(N+1);
        return -1;
    }
    void operator=(BYDSET const&s)
    {
        L=s.L;
        for(int i=0;i<=L;i++)a[i]=s.a[i];
    }
    BYDSET operator-(const BYDSET&s)const
    {
        BYDSET ans;
        for(int i=0;i<=L;i++)ans.a[i]=a[i];
        ans.L=L;
        for(int i=0;i<=L;i++)
        {
            ans.a[i]-=s.a[i];
            if(ans.a[i]<0)
            {
                ans.a[i]+=(1ll<<(N+1));
                ans.a[i+1]--;
            }
        }
        while(!ans.a[ans.L]&&ans.L)ans.L--;
        return ans;
    }
}A,B,C;
int cmp(BYDSET a,BYDSET s)
{
    int A=a.highbit(),S=s.highbit();
    if(A!=S)return A>S;
    for(int i=a.L;~i;i--)if(a.a[i]!=s.a[i])return a.a[i]>s.a[i];
    return 2;
}
long long ask()
{
    long long ans=0;
    int AA=A.highbit(),BB=B.highbit();
    if(AA<BB)swap(A,B),swap(AA,BB);
    while(AA>BB)ans++,A.lmove(),AA--;
    int o=cmp(A,B);
    if(o==2)return ans;
    if(!o)swap(A,B);
    BYDSET C=A-B;//C为x与y的差值
    int CC=C.highbit();
    long long num=0,an=1e10;
    o=0;
    while(1)
    {
        C=A-B;
        CC=C.highbit();
        if(!~CC)break;
        o=1;
        if(!C.L)an=min(num+(long long)C.a[0],an);
        //当C的位数大于60时是绝对不优的，不用加入贡献
        A.lmove();
        B.lmove();
        num+=2;
    }
    return ans+an*o;
}
char a[200005],b[200005];
int n,m;
int main()
{
    scanf("%s%s",a+1,b+1);
    n=strlen(a+1);
    m=strlen(b+1);
    A.a[0]=1;
    B.a[0]=1;
    for(int i=1;i<=n;i++)//处理x最后的位置
    {
        if(a[i]=='1')A.rmove();
        else if(a[i]=='2')A.rmove(),A.push();
        else if(a[i]=='U')A.lmove();
        else if(a[i]=='L')A.idk();
        else A.push();
    }
    for(int i=1;i<=m;i++)//同上
    {
        if(b[i]=='1')B.rmove();
        else if(b[i]=='2')B.rmove(),B.push();
        else if(b[i]=='U')B.lmove();
        else if(b[i]=='L')B.idk();
        else B.push();
    }
    printf("%lld",ask());
}
```


---

