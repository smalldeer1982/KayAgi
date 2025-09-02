# Distinct Characters Queries

## 题目描述

You are given a string $ s $ consisting of lowercase Latin letters and $ q $ queries for this string.

Recall that the substring $ s[l; r] $ of the string $ s $ is the string $ s_l s_{l + 1} \dots s_r $ . For example, the substrings of "codeforces" are "code", "force", "f", "for", but not "coder" and "top".

There are two types of queries:

- $ 1~ pos~ c $ ( $ 1 \le pos \le |s| $ , $ c $ is lowercase Latin letter): replace $ s_{pos} $ with $ c $ (set $ s_{pos} := c $ );
- $ 2~ l~ r $ ( $ 1 \le l \le r \le |s| $ ): calculate the number of distinct characters in the substring $ s[l; r] $ .

## 样例 #1

### 输入

```
abacaba
5
2 1 4
1 4 b
1 5 b
2 4 6
2 1 7
```

### 输出

```
3
1
2
```

## 样例 #2

### 输入

```
dfcbbcfeeedbaea
15
1 6 e
1 4 b
2 6 14
1 7 b
1 12 c
2 6 8
2 1 6
1 7 c
1 2 f
1 10 a
2 7 9
1 10 a
1 14 b
1 1 f
2 1 11
```

### 输出

```
5
2
5
2
6
```

# 题解

## 作者：woshishei (赞：9)

总的来说，你需要对一个字符串完成以下两种操作：

1. 单点修改
2. 区间查询

而用树状数组可以实现这两种操作。

因为英语小写字母只有26个，所以可以开26个数组，分别为每一个字符个数的树状数组。

单点修改：

- 把原先字符数量减1；
- 把指定字符数量加1；
- 修改字符串中的字符。

区间查询：

- 依次求每一个字母的区间和（$sum(r)-sum(l-1)$），如果不为零，$ans$加一；
- 最后的$ans$即为答案。

时间复杂度：$\Theta(kq\text{log}_2n)$，$k$为常数（字母数量，26）

### Code

**Time** 202ms

**Memory** 10280KB

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define debug printf("\n-------------\n")
#define fackit {printf("-1\n");return;}
using namespace std;
typedef long long ll;
char s[100010];
int len,q,tree[26][100010];
//树状数组模板
int lowbit(int x){return x&(-x);}
void add(int ch,int x,int k)//这里的ch代表字母（0~25），下同
{
	while(x<=len)
	{
		tree[ch][x]+=k;
		x+=lowbit(x);
	}
}
int sum(int ch,int x)
{
	int tot=0;
	while(x>0)
	{
		tot+=tree[ch][x];
		x-=lowbit(x);
	}
	return tot;
}
int main()
{
	scanf("%s",s+1);
	len=strlen(s+1);
	for(int i=1;i<=len;i++)
		add(s[i]-'a',i,1);//把字符串中每一个字符进行单点修改
	scanf("%d",&q);
	while(q--)
	{
		int opt,x,y,ans=0;
		char z;
		scanf("%d",&opt);
		switch(opt)
		{
			case 1:
				scanf("%d",&x);
				scanf(" %c",&z);
				add(s[x]-'a',x,-1);//原字符减1
				add(z-'a',x,1);//新字符加1
				s[x]=z;//修改字符串中的字符，用指定字符替换原字符
				break;
			case 2:
				scanf("%d %d",&x,&y);
				for(int i=0;i<=25;i++)//遍历每一个字母
					ans+=(sum(i,y)-sum(i,x-1)>0?1:0);//如果不为零，ans加一
				printf("%d\n",ans);
				break;
		}
	}
	return 0;
}
```

其实这道题也可以用线段树，但是有以下隐患：

- 卡常（时间+空间）
- ~~难写~~

除此之外，本题的pretest过水，导致$\Theta(nq)$的暴力也能AC。这样会有很多人被hack/FST。~~为在比赛中所有打暴力AC的人默哀~~

还有其他很多做法，只要保证时间复杂度正确就可以。

---

## 作者：Katsura_Hinagiku (赞：3)

题意：给一个字符串s，资瓷两种操作

操作1：将某一位的字符改成给定的一个字符

操作2：询问一段区间内不同字符的个数

使用线段树求解，$tree[i][k]$表示$k$代表的这一段区间内，是否有ASCII码为$i+48$的字符，建树、修改、询问按正常的线段树写就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
char cc[2];
int tree[26][400005];
int t[26],len,q,opt;
void pushup(int k)
{
	for(int i=0;i<26;++i)
	{
		tree[i][k]=tree[i][k<<1]|tree[i][k<<1|1];//只要两个子区间中有这个字符，当前区间内就有这个字符
	}
}
void build(int l,int r,int k)
{
	if(l==r)
	{
		tree[s[l-1]-'a'][k]=1;
		return;
	}
	int m=(l+r)>>1;
	build(l,m,k<<1);
	build(m+1,r,k<<1|1);
	pushup(k);
}
void modify(int l,int r,int k,int pos,int v)
{
	if(l==r)
	{
		for(int i=0;i<26;++i)
		{
			tree[i][k]=0;
		}
		tree[v][k]=1;
		return;
	}
	int m=(l+r)>>1;
	if(pos<=m)modify(l,m,k<<1,pos,v);
	else modify(m+1,r,k<<1|1,pos,v);
	pushup(k);
}
void query(int L,int R,int l,int r,int k)
{
	if(L<=l&&r<=R)
	{
		for(int i=0;i<26;++i)t[i]|=tree[i][k];//用t[i]储存当前区间有哪些字符
		return;
	}
	int m=(l+r)>>1;
	if(L<=m)query(L,R,l,m,k<<1);
	if(R>m)query(L,R,m+1,r,k<<1|1);
}
int main()
{
	cin>>s;
	len=s.length();
	build(1,len,1);
	scanf("%d",&q);
	for(int i=1;i<=q;++i)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			int pos;
			scanf("%d",&pos);
			scanf("%s",cc);
			modify(1,len,1,pos,cc[0]-'a');
		}
		else
		{
			int l,r,tmp=0;
			scanf("%d%d",&l,&r);
			query(l,r,1,len,1);
			for(int i=0;i<26;++i)
			{
				if(t[i])
				{
					++tmp;
					t[i]=0;//统计答案时顺带将t数组清空
				}
			}
			printf("%d\n",tmp);
		}
	}
	return 0;
}
```

---

## 作者：时间重洗 (赞：2)

某DIV3原题

看到这题有不少的巨佬用树状数组或线段树做，奈何本蒟蒻在老师将这块内容时没有好好地听课（这就是我蒟的原因吧），所以只能够想别的方法。

首先看题，一串长度为100000的小写字符串，有q次询问，每次有两种情况

1.  1  pos  c     将字符串pos位的字符改为c

2.  2  l  r     搜索l到r中有多少不同字母

当时本蒟蒻在做的时候，最先想到的就是暴力（毕竟n^2什么都能维护），可是就算两秒时限，也是会超时的，于是就是优化，变一下想到了暴力的优化：分块

想好了大致的方向，那接下来该如何做呢？

我们用l[i]表示区间i的起点，r[i]表示终点，belong[i]表示第i个字符属于哪一个区间，num[i][j]表示在第i个区间中，有多少个j字母（我在比赛中用的是int，你们也可以改成bool，但是在修改时可能会难一些），have[i]表示在这次的查询中，i这个字符有没有出现

至于修改，就是将pos所属的区间中原先字符的个数减一，新改成的字符个数加一，然后直接在原数组上改变即可

那么代码就好写了

```cpp
#include<cmath>
#include<stdio.h>
#include<cstring>
#include<algorithm>
#define re register
using namespace std;
const int MAXN=100005,MAXM=350,MAXCH=30;
char ch[MAXN];
int n,q,sum,block,l[MAXM],r[MAXM],belong[MAXN],num[MAXM][MAXCH];
bool have[MAXCH];
template <typename T> void in(register T& a){
    register T x=0,f=1;
	register char c=getchar();
    while(!isdigit(c)){
	    c=='-'?f=-1:f=1;
		c=getchar();
	}
    while(isdigit(c)){
        x=(x<<1)+(x<<3)+c-'0';
	    c = getchar();
	}
    a=x*f;
}
inline void init(){
	scanf("%s",ch+1);
	n=strlen(ch+1);
	sum=sqrt(n);//确认每个区间的长度
	block=n/sum;//确认有多少个区间
	if(n%sum!=0) block++;
	for(re int i=1;i<=n;i++){
		belong[i]=(i-1)/sum+1;
		num[belong[i]][ch[i]-'a'+1]++;
	}//计算i属于哪个区间，并预处理num数组
	for(re int i=1;i<=block;i++){
		l[i]=r[i-1]+1;
		r[i]=l[i]+sum-1;
	}
	r[block]=n;//处理起点和终点
}
inline void Query(int a,int b){
	int ans=0;
	memset(have,0,sizeof have);//将have置零
	for(re int i=a;i<=min(b,r[belong[a]]);i++){//搜索不是整区间的部分
		if(have[ch[i]-'a'+1]==0){
			ans++;
			have[ch[i]-'a'+1]=1;
		}
		if(ans==26){
			printf("26\n");
			return ;//小优化，小写字母都有了就可以不做了
		}	
	}
	if(belong[a]!=belong[b])//左右不是一个区间，把右边的非正区间扫一遍
		for(re int i=l[belong[b]];i<=b;i++){
			if(have[ch[i]-'a'+1]==0){
				ans++;
				have[ch[i]-'a'+1]=1;
			}
			if(ans==26){
				printf("26\n");
				return ;
			}
		}
	for(re int i=belong[a]+1;i<belong[b];i++){
		for(re int j=1;j<=26;j++){//搜索每个整区间的字母
			if(ans==26){
				printf("26\n");
				return ;
			}
			if(num[i][j]==0) continue;
			if(have[j]) continue;
			ans++;
			have[j]=1;
		}
		if(ans==26){
			printf("26\n");
			return ;
		}
	}
	printf("%d\n",ans);
}
inline void Do(){
	in(q);
	for(re int i=1;i<=q;i++){
		int opt;
		in(opt);
		if(opt==1){//修改
			int pos;
			char c;
			in(pos);
			scanf("%c",&c);
			num[belong[pos]][ch[pos]-'a'+1]--;
			num[belong[pos]][c-'a'+1]++;
			ch[pos]=c;
        }
		else{
			int l,r;
			in(l);in(r);
			Query(l,r);//查找
		}
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	init();
	Do();
	return 0;
}
```
本人的码风和语文水平可能不怎么好，请多包涵

---

## 作者：zhengrunzhe (赞：1)

已有的线段树/树状数组做法都是开26个的，或者是一个树里面每个点26个桶的，提供一个不带26的做法

考虑二进制压缩，把0(a)~25(z)变成1<<0到1<<25，累计区间or和

修改就直接单点修改

查询就直接求区间or和，然后看这个or和里有几个1

```cpp
#include<cstdio>
#include<cstring>
const int N=1e5+10;
inline const int lowbit(int x)
{
	return x&-x;
}
int n,m;
char s[N];
class Segment_Tree
{
	private:
		struct tree
		{
			int orsum;
			tree *lson,*rson;
			inline const void pushup()
			{
				orsum=lson->orsum|rson->orsum;
			}
			inline const void update(int l,int r,int pos,char c)
			{
				if (l==r)return orsum=1<<c-'a',void();
				int mid=l+r>>1;
				if (pos<=mid)lson->update(l,mid,pos,c);
				else rson->update(mid+1,r,pos,c);
				pushup();
			}
			inline const int query(int l,int r,int L,int R)
			{
				if (l>R||r<L)return 0;
				if (l>=L&&r<=R)return orsum;
				int mid=l+r>>1;
				return lson->query(l,mid,L,R)|rson->query(mid+1,r,L,R);
			}
		}*root,memory_pool[N<<1],*tail;
		inline const void build(tree *&p,int l,int r)
		{
			p=tail++;
			if (l==r)return p->orsum=1<<s[l]-'a',void();
			int mid=l+r>>1;
			build(p->lson,l,mid);
			build(p->rson,mid+1,r);
			p->pushup();
		}
	public:
		inline const void build()
		{
			tail=memory_pool;build(root,1,n);
		}
		inline const void update(int x,char c)
		{
			root->update(1,n,x,c);
		}
		inline const int query(int l,int r)
		{
			int sum=root->query(1,n,l,r),cnt=0;
			for (;sum;sum^=lowbit(sum))cnt++;
			return cnt;
		}
}sgt;
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	sgt.build();
	scanf("%d",&m);
	while (m--)
	{
		int opt;
		scanf("%d",&opt);
		if (opt&1){int x;char c;scanf("%d %c",&x,&c);sgt.update(x,c);}
		else {int l,r;scanf("%d%d",&l,&r);printf("%d\n",sgt.query(l,r));}
	}
	return 0;
}
```

---

## 作者：Linne (赞：1)

提供一个新思路：
考虑到小写字母只有26个，
对于每个字母开一个multiset，维护其出现的**位置**

------------

对于每个修改，在原字串中修改的同时，在multiset里相应修改；
对于每个查询，对所有字母，在multiset里二分找是否有[l,r]其中的一个位置，
如果存在答案就加一，最后求和回答。显而易见一次查询是O(26*logn)的。


------------
优点是代码直观较短，我知道还能用很多log数据结构比如线段树平衡树，你开心就好。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1000005;
string s;
int q,x,l,r,pos;char c;
set<int>M[200];
int main(){
	ios::sync_with_stdio(0);
	cin>>s;
	cin>>q;
	for(int i=0;i<s.size();++i){
		M[s[i]].insert(i+1);
	}
	while(q--){
		cin>>x;
		if(x==1){
			cin>>pos>>c;
			M[s[pos-1]].erase(pos);
			s[pos-1]=c;
			M[c].insert(pos);
		}else{
			cin>>l>>r;
			int sum=0;
			for(int i='a';i<='z';++i){
				if(M[i].lower_bound(l)==M[i].end())continue;
				int p=*(M[i].lower_bound(l));
				if(p<=r)sum++;
			}
			cout<<sum<<endl;
		}
	}
	return 0;
	}

```


---

## 作者：kouylan (赞：1)

## Solution to CF1234D

### 【题目大意】
有一个序列，两种操作：

1. 把$x$位置上的元素改为$v$
2. 找出$l$到$r$之间不同元素的个数

### 【大体思路】
因为元素是26个（小写字母），又要区间求和，很快就想到用[树状数组](https://www.luogu.org/problem/P3374)（不会树状数组的先点一下链接）。

我们可以开26个树状数组，分别记录每一个字母的区间个数。

修改时，需要做依次以下三件事：

1. 把修改字母的区间个数$+1$
1. 把被修改字母的区间个数$-1$
3. 把被修改字母替换为修改字母

查询时，求出每一个字母在这段区间上的个数。如果大于$0$，则$ans+1$。

下面是AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) x&-x

int n,q,oper;
int c[30][100005]; // 树状数组 
char s[100005];

void fix(int ch,int x,int val)
{
	while(x<=n)
	{
		c[ch][x] += val;
		x += lowbit(x);
	}
}

int ask(int ch,int x)
{
	int s=0;
	while(x)
	{
		s += c[ch][x];
		x -= lowbit(x);
	}
	return s;
}

int main()
{
	scanf("%s",s+1); // 读入初始字符串 
	n = strlen(s+1); 
	for(int i=1;i<=n;i++)
		fix(s[i]-96,i,1); // 先把初始的串中字母累计区间个数(初始化) 
	cin>>q;
	while(q--)
	{
		cin>>oper;
		if(oper==1) // 修改 
		{
			int x;
			char ch;
			cin>>x>>ch;
			fix(ch-96,x,1); // 把修改字母的区间个数+1
			fix(s[x]-96,x,-1); // 把被修改字母的区间个数-1
			s[x] = ch; // 把被修改字母替换为修改字母
		}
		else if(oper==2) // 查询 
		{
			int l,r,ans=0;
			cin>>l>>r;
			for(int i=1;i<=26;i++)
			{
				int s=ask(i,r)-ask(i,l-1); // 求出每一个字母在这段区间上的个数
				if(s>0)
					ans++; // 如果大于0，则ans++(不是ans+=s)
			}
			cout<<ans<<endl;
		}
	}
	
	return 0;
}
```
祝大家AC愉快！

---

## 作者：Smallbasic (赞：1)

泥萌都维护26个线段树？？？

其实可以在线段树每个节点中维护一个lt数组，lt[i]表示第i个字母出没出现过。查询的时候就模仿小白逛公园的方法，直接一边查询一边在建一棵线段树就好了。这样常树应该要小一些。

详见代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

char s[100005], c;
int q, md, l, r, ans = 0;

struct node {
	int l, r;
	bool lt[26];
	node *left = NULL;
	node *right = NULL;
	
	inline void update() {
		if (this -> left == NULL) return ;
		for (int i = 0; i < 26; ++i)
			this -> lt[i] = 0;
		for (int i = 0; i < 26; ++i)
			this -> lt[i] = (this -> left -> lt[i] || this -> right -> lt[i]);
	}
	
	inline void build(int l, int r) {
		this -> l = l; this -> r = r;
		memset(this -> lt, 0, sizeof(this -> lt));
		if (l >= r) this -> lt[s[l] - 'a'] = 1;
		else {
			this -> left = new node; this -> left -> build(l, l + r >> 1);
			this -> right = new node; this -> right -> build((l + r >> 1) + 1, r);
			this -> update();
		}
	}
	
	inline void modify(int t, char c) {
		if (this -> l >= this -> r) {
			this -> lt[s[t] - 'a'] = 0;
			this -> lt[c - 'a'] = 1;
			return ;
		}
		if (t <= this -> left -> r) this -> left -> modify(t, c);
		else this -> right -> modify(t, c); this -> update();
		return ;
	}
	
	inline node* query(int l, int r) {
		node *cur = new node; cur -> l = this -> l; cur -> r = this -> r;
		for (int i = 0; i < 26; ++i) cur -> lt[i] = this -> lt[i];
		if (l <= this -> l && r >= this -> r) return cur;
		if (r <= this -> left -> r) { delete cur; return this -> left -> query(l, r); }
		if (l >= this -> right -> l) { delete cur; return this -> right -> query(l, r); }
		cur -> left = this -> left -> query(l, r); cur -> right = this -> right -> query(l, r);
		cur -> update(); delete cur -> left; delete cur -> right; return cur;
	}
};

int main() {
	scanf("%s", s + 1); scanf("%d", &q);
	node *root = new node; root -> build(1, strlen(s + 1));
	while (q--) {
		scanf("%d", &md);
		if (md == 1) {
			scanf("%d %c", &l, &c);
			root -> modify(l, c);
			s[l] = c;
		} else if (md == 2) {
			scanf("%d %d", &l, &r); node *rt = root -> query(l, r);
			for (int i = 0; i < 26; ++i) ans += rt -> lt[i];
			printf("%d\n", ans); ans = 0; delete rt;
		}
	}
	return 0;
} 
```


---

## 作者：Meatherm (赞：1)

似乎直接线段树会出问题？

为了保险起见我用了动态开点，保证不会挂。

建 $26$ 棵线段树，然后正常操作就可以了。


--- 


设字符串为 $s$。

对于把第 $x$ 个字符修改为 $y$ 的操作：

1. 将第 $s[x]-'a'+1$ 棵线段树的第 $x$ 个位置修改为 $0$。
2. 将 $s[x]$ 修改为 $y$。
3. 将第 $s[x]-'a'+1$ 棵线段树的第 $x$ 个位置修改为 $1$。注意此时 $s[x]$ 已经发生改变。

对于查询 $[l,r]$ 中不同字符数量的操作：

将 $26$ 棵线段树分别拎出来求解。如果第 $i$ 棵线段树的 $[l,r]$ 区间和不为 $0$，则本次答案 $+1$。

另外由于是单点修改区间查询，所以线段树显得有点浪费。用树状数组也是可以的，但是我感觉很难写...

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=100010;
struct Node{
	int lc,rc,sum;
}tree[(N<<2)*26];
int id;
int root[30];
char s[N];
int n,q;
inline void make(int &x){
	if(!x)
		x=++id;
	return;
}
void change(int &k,int l,int r,int x,int v){
	make(k);
	if(l==r&&l==x){
		tree[k].sum+=v;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
		change(tree[k].lc,l,mid,x,v);
	else
		change(tree[k].rc,mid+1,r,x,v);
	tree[k].sum=tree[tree[k].lc].sum+tree[tree[k].rc].sum;
	return;		
}
int ask(int &k,int l,int r,int L,int R){
	make(k);
	if(L<=l&&r<=R){
		return tree[k].sum;
	}
	int mid=(l+r)>>1,res=0;
	if(L<=mid)
		res+=ask(tree[k].lc,l,mid,L,R);
	if(mid<R)
		res+=ask(tree[k].rc,mid+1,r,L,R);
	return res;		
}
int main(void){
	scanf("%s",s+1);
	n=strlen(s+1);
	for(rr int i=1;i<=n;++i){
		change(root[s[i]-'a'+1],1,n,i,1);
	}
	scanf("%d",&q);
	int opt,x,y;
	char tmp;
	while(q--){
		scanf("%d%d",&opt,&x);
		if(opt==1){
			std::cin>>tmp;
			change(root[s[x]-'a'+1],1,n,x,-1);
			s[x]=tmp;
			change(root[s[x]-'a'+1],1,n,x,1);
		}else{
			scanf("%d",&y);
			int sum=0;
			for(rr int i=1;i<=26;++i){
				if(ask(root[i],1,n,x,y))
					++sum;
			}
			printf("%d\n",sum);
		}
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：0)

这不是树状数组裸题？
## 思路
由于都是小写字母，显然我们可以开 $\verb!26!$ 个树状数组/线段树来记录每一个小写字母在每个区间内的个数。由于只需要支持单点修改/区间查询，我们选择易于实现以及常数小的树状数组。

每次修改时我们在原来字母对应的树状数组内 $\verb!update!$ 一个 $\verb!-1!$，在修改字母对应的树状数组内 $\verb!update!$ 一个 $\verb!1!$。至于查询则可直接暴力查询 $\verb!26!$ 个树状数组，遇到在这个区间内字母数总和不为零的答案就加一。那么这题就做完了。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rint register int
int n;
int const N=1e5+10;
struct Tree{
	int c[N];
	inline int lowbit(int x){return x&-x;}
	inline void update(int x,int plus){while (x<=n) c[x]+=plus,x+=lowbit(x);}
    inline int query(int x){
    	int now=0;
    	while (x) now+=c[x],x-=lowbit(x);
	    return now;
	}
}T[26];//把树状数组合为一个结构体，上面都是基本操作
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	string s;cin>>s;n=s.length(),s=" "+s;
    for (rint i=1;i<=n;++i) T[s[i]-'a'].update(i,1);//预处理
	int q;cin>>q;
    while (q--){
    	int type;cin>>type;
    	if (type&1){
    		int pos;char c;cin>>pos>>c;
    		T[s[pos]-'a'].update(pos,-1);
    		T[c-'a'].update(pos,1);
    		s[pos]=c;
		}else{
			int l,r;cin>>l>>r;
			int ans=0;
			for (rint i=0;i<26;++i)
			    if (T[i].query(r)-T[i].query(l-1)>0) ++ans;
		    cout<<ans<<'\n';
		}
	}
	return 0;
}
```


---

## 作者：Naffygo (赞：0)

### 前言

~~看到几乎所有巨佬都是用树状数组或线段树通过这道题的,但小蒟蒻最近做莫队已做傻,所以就用莫队写的啦,然后来写篇题解~~

### 关于莫队

莫队实质就是个优雅的暴力，核心为分块 $+$ 排序,再加上左右两个指针跳来跳去。排序的话一般是先按左端点所在块排序，若相同，再按右端点所在块排序。然后再将左右指针跳来跳去。

### 关于这道题

我们发现这道题需要修改，普通莫队显然维护不了，那么就需要使用带修莫队了。

带修莫队就是在普通莫队的基础上，多维护一维时间（此时修改到了哪里）。若当前时间大了，那么说明当前进行的修改操作比需要的多，则改回来，否则改过去。只有当前区间和时间与询问区间和时间相同时才记录答案。

那么接下来就上代码了：

```cpp
#include<bits/stdc++.h>
#define fr(i,a,b) for(register int i = a;i <= b;++i)
#define N 100010
#define M 50
using namespace std;

string s;
int a[N],cnt[M],id[N],ans[N];
struct query{
	int l,r,t,pos;
	bool operator < (const query &p)const{
		return id[l] ^ id[p.l] ? l < p.l : ((id[r] ^ id[p.r]) ? r < p.r : t < p.t);
	}
}q[N];
struct upd{
	int pos,w;
}d[N];
int cnt1,cnt2,tot;

inline int read(){
	int x = 0,f = 1;char c = getchar();
	while(!isdigit(c)){if(c == '-')f = -1;c = getchar();}
	while(isdigit(c)){x = x * 10 + c - '0';c = getchar();}
	return f * x;
}

int main(){
	cin>>s;
	int n = s.size(),m = read(),sum = pow(n,2.0 / 3.0);
	fr(i,1,n)a[i] = s[i - 1] - 'a' + 1,id[i] = (i - 1) / sum + 1;
	fr(i,1,m){
		int opt = read();
		if(opt == 2){int x = read(),y = read();q[++cnt1] = {x,y,cnt2,cnt1};}
		else{int x = read();char c;cin>>c;d[++cnt2] = {x,c - 'a' + 1};}
	}
	sort(q + 1,q + cnt1 + 1);
	int l = 1,r = 0,t = 0;
	fr(i,1,cnt1){
		int ql = q[i].l,qr = q[i].r,qt = q[i].t;
		while(l < ql)tot -= !--cnt[a[l++]];//利用运算符优先级可以这么写
		while(l > ql)tot += !cnt[a[--l]]++;
		while(r < qr)tot += !cnt[a[++r]]++;
		while(r > qr)tot -= !--cnt[a[r--]];
		while(t < qt){//当前时间比询问区间小，说明需要多进行修改
			t++;
			if(ql <= d[t].pos && qr >= d[t].pos)tot -= !--cnt[a[d[t].pos]] - !cnt[d[t].w]++;
			swap(a[d[t].pos],d[t].w);
		}
		while(t > qt){//当前时间比询问区间大，说明需要把之前改过的改回来
			if(ql <= d[t].pos && qr >= d[t].pos)tot -= !--cnt[a[d[t].pos]] - !cnt[d[t].w]++;
			swap(a[d[t].pos],d[t].w);
			t--;
		}
		ans[q[i].pos] = tot;
	}
	fr(i,1,cnt1)printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：littleseven (赞：0)

### 题目解析：

[博客地址](http://littleseven.top/)

看着给出的这俩类型的操作这么熟呢？？？

~~线~~   ~~段~~   ~~树~~

~~树~~   ~~状~~   ~~数~~   ~~组~~

那就整啊！！！！

26颗线段树   OR   26颗树状数组

（显然后者好写，那就写）

数据结构题直接看代码就好，这是26颗树状数组。

```cpp
#include <bits/stdc++.h>

using namespace std;

int tree[26][100010];

int n, m;

char s[100010];

void update(int ch, int x, int v) {
	for (int i = x; i <= n; i += (i & -i)) {
		tree[ch][i] += v;
	}
}

int query(int ch, int x) {
	int res = 0;
	for (int i = x; i; i -= (i & -i)) {
		res += tree[ch][i];
	}
	return res;
}

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for (int i = 1; i <= n; i ++ ) {
		update(s[i] - 'a', i, 1);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i ++ ) {
		int opt;
		scanf("%d", &opt);
		if (opt == 1) {
			int a;
			char ch;
			scanf("%d %c", &a, &ch);
			update(s[a] - 'a', a, -1);
			update(ch - 'a', a, 1);
			s[a] = ch;
		}
		else {
			int a, b, ans = 0;
			scanf("%d%d", &a, &b);
			for (int i = 0; i < 26; i ++ ) {
				if ((query(i, b) - query(i, a - 1))) {
					ans ++ ;
				}
			}
			printf("%d\n", ans);
		}

	}
	return 0;

}
```

---

## 作者：开始新的记忆 (赞：0)

题目大意：给你一串由小写英文字母组成的字符串，有两种操作：1 x y（y为一个小写字母），把x位置的字母改成y。2 x y 查询x~y中有多少种不同的英文字母。

原题：P1903，用待修莫队实现

PS：代码只是更改第一篇题解的输入输出

```
#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
template<class Read>void in(Read &x){
    x=0;
    int f=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        f|=(ch=='-');
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x=f?-x:x;
    return;
}
int n,q,m,a[1000005],b[1000005],ans,now1,now2,now,sum[1000005],l=2,r=1;
struct Node{
	int x;
	int c;
}g[1000005];
struct node{
    int x;
    int y;
    int c;
    int id;
}f[1000005];
bool cmp(node x,node y){
	return x.x/m==y.x/m?(x.y/m==y.y/m?x.c<y.c:x.y<y.y):x.x<y.x;
}
void add(int x){if(b[x]++==0)++ans;}
void del(int x){if(--b[x]==0)--ans;}
void work(int x,int y){
	if(g[y].x>=f[x].x&&g[y].x<=f[x].y){
		del(a[g[y].x]);
		add(g[y].c);
	}
	int t=a[g[y].x];
	a[g[y].x]=g[y].c;
	g[y].c=t;
}
int main(){
    string s;
    cin>>s;
    for(int i=0;s[i];i++){
    	n++;
    	a[n]=s[i]-'a';
	}
	m=pow(n,2.0/3.0);
	in(q);
	for(int i=1;i<=q;i++){
		int opt;
		in(opt);
		if(opt==1){
			in(g[++now1].x);
			char ch[10];
			scanf("%s",ch);
			g[now1].c=ch[0]-'a';
		}
		else{
			in(f[++now2].x);
			in(f[now2].y);
			f[now2].c=now1;
			f[now2].id=now2;
		}
	}
    sort(f+1,f+1+now2,cmp);
    for(int i=1;i<=now2;i++){
    	while(l>f[i].x)add(a[--l]);
    	while(r<f[i].y)add(a[++r]);
    	while(l<f[i].x)del(a[l++]);
    	while(r>f[i].y)del(a[r--]);
    	while(now<f[i].c)work(i,++now);
    	while(now>f[i].c)work(i,now--);
    	sum[f[i].id]=ans;
	}
    for(int i=1;i<=now2;i++)printf("%d\n",sum[i]);
    return 0;
}
```


---

## 作者：Ludo (赞：0)

对于这种区间操作，单点修改问题，不难想到要用**树状数组**和**线段树**这类数据结构了。

首先先思考问题的本质：要求找到子串s[l,r]中不同字符的个数，并且支持单点修改。

这个问题的关键点，

### **就在于s中只包含小写字母**。

所以？答案很小。

所以？

不要忽略了，小写拉丁字母只有26个。

怎样统计？怎样修改？不要急，

### 建立起26个树状数组或者线段树就好了。

**统计。26个树状数组已经处理好了，我们把有这一字母的位置添上1即可。不要忘记了，树状数组是根据前缀和来求区间和的。我们用s[1,r]减去s[1,l-1]，就可以得到这个字母在区间[l,r]上的个数了。**

**修改。我们一边修改，顺便把修改的内容也在原串标记出来。修改时，原串对应位置上的字符在树状数组中减1；而取代的字符在树状数组中加1。这样处理就很方便了。**

## 代码

下面将使用树状数组进行求解。
```cpp
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
int sz[27][100001],q;　//sz是树状数组, sz[1]代表a的树状数组。
int type,l,r,n,m;
char x,s[100002];
int lowbit(int x)　//lowbit函数 化2进制,取出最低位1及其后的0连接成的2进制数,再化为10进制数
{
	return x&(-x);
}
void modify(int idd,int pos,int s) //idd为第idd个树状数组 pos为修改的位置 s为加上的数值
{
	for (int i=pos;i<=n;i+=lowbit(i))
	{
		sz[idd][i]+=s;
	}
	return;
}
int sum(int idd,int x) //计算树状数组idd中idd在区间[1,x]中出现的次数
{
	int ans=0;
	for (int i=x;i>=1;i-=lowbit(i))
	{
		ans+=sz[idd][i]; 
	}
	return ans;
}
int main(void)
{
	scanf("%s",s+1);n=strlen(s+1);
	for (int i=1;i<=strlen(s+1);i++) //修改树状数组
	{
		modify(s[i]-'a'+1,i,1);
	}
	cin>>m;
	for (int i=1;i<=m;i++)
	{
		cin>>type;
		if (type==1)
		{
			scanf("%d %c",&l,&x);
			modify(s[l]-'a'+1,l,-1); //要把原来的减1
			modify(x-'a'+1,l,1);      //也要把修改的加上1
			s[l]=x;                       //把新的套到原字串上
		}
		if (type==2)
		{
			cin>>l>>r;
			int pk=0;
			for (int j=1;j<=26;j++) //26个字母,遍历26个树状数组
			{
				pk+=((sum(j,r)-sum(j,l-1))==0)?0:1; //若为0,则没有出现过;若不为0,就是有出现过
			}
			cout<<pk<<endl;
		}
	}
}

```


---

