# Raging Thunder

## 题目描述

You are a warrior fighting against the machine god Thor.

Thor challenge you to solve the following problem:

There are $ n $ conveyors arranged in a line numbered with integers from $ 1 $ to $ n $ from left to right. Each conveyor has a symbol "&lt;" or "&gt;". The initial state of the conveyor $ i $ is equal to the $ i $ -th character of the string $ s $ . There are $ n+1 $ holes numbered with integers from $ 0 $ to $ n $ . The hole $ 0 $ is on the left side of the conveyor $ 1 $ , and for all $ i \geq 1 $ the hole $ i $ is on the right side of the conveyor $ i $ .

When a ball is on the conveyor $ i $ , the ball moves by the next rules:

If the symbol "&lt;" is on the conveyor $ i $ , then:

- If $ i=1 $ , the ball falls into the hole $ 0 $ .
- If the symbol "&lt;" is on the conveyor $ i-1 $ , the ball moves to the conveyor $ i-1 $ .
- If the symbol "&gt;" is on the conveyor $ i-1 $ , the ball falls into the hole $ i-1 $ .

If the symbol "&gt;" is on the conveyor $ i $ , then:

- If $ i=n $ , the ball falls into the hole $ n $ .
- If the symbol "&gt;" is on the conveyor $ i+1 $ , the ball moves to the conveyor $ i+1 $ .
- If the symbol "&lt;" is on the conveyor $ i+1 $ , the ball falls into the hole $ i $ .

You should answer next $ q $ queries, each query is defined by the pair of integers $ l, r $ ( $ 1 \leq l \leq r \leq n $ ):

- First, for all conveyors $ l,l+1,...,r $ , the symbol "&lt;" changes to "&gt;" and vice versa. These changes remain for the next queries.
- After that, put one ball on each conveyor $ l,l+1,...,r $ . Then, each ball falls into some hole. Find the maximum number of balls in one hole. After the query all balls disappear and don't considered in the next queries.

## 说明/提示

- In the first query, the conveyors change to "&gt;&gt;&lt;&lt;&lt;". After that, put a ball on each conveyor $ \{2,3,4\} $ . All three balls fall into the hole $ 2 $ . So the answer is $ 3 $ .
- In the second query, the conveyors change to "&gt;&gt;&gt;&gt;&gt;". After that, put a ball on each conveyor $ \{3,4,5\} $ . All three balls fall into the hole $ 5 $ . So the answer is $ 3 $ .
- In the third query, the conveyors change to "&lt;&lt;&lt;&lt;&lt;". After that, put a ball on each conveyor $ \{1,2,3,4,5\} $ . All five balls fall into the hole $ 0 $ . So the answer is $ 5 $ .
- In the fourth query, the conveyors change to "&gt;&gt;&gt;&lt;&lt;". After that, put a ball on each conveyor $ \{1,2,3\} $ . All three balls fall into the hole $ 3 $ . So the answer is $ 3 $ .
- In the fifth query, the conveyors change to "&gt;&lt;&lt;&gt;&lt;". After that, put a ball on each conveyor $ \{2,3,4\} $ . Two balls fall into the hole $ 1 $ , and one ball falls into the hole $ 4 $ . So, the answer is $ 2 $ .
- In the sixth query, the conveyors change to "&lt;&gt;&gt;&lt;&gt;". After that, put a ball on each conveyor $ \{1,2,3,4,5\} $ . Three balls fall into the hole $ 3 $ , one ball falls into the hole $ 0 $ and one ball falls into the hole $ 5 $ . So, the answer is $ 3 $ .

## 样例 #1

### 输入

```
5 6
><>><
2 4
3 5
1 5
1 3
2 4
1 5```

### 输出

```
3
3
5
3
2
3```

# 题解

## 作者：Sunny郭 (赞：8)

注意到答案只会是序列中间的 `>>><<<`，或者最左边是 $1$ 号传送带的 `<<<`，或者最右边是 $n$ 号传送带的 `>>>` 这些形状。

这些都是可以用线段树维护的，考虑维护序列最左边的 `<` 的长度，和最右边的 `>` 的长度，`>>><<<` 形状的维护方式也很好从这些推过来。

考虑反转，也很经典。维护多一个 `<<<>>>` 这个形状的，修改的时候把 `>>><<<` 和 `<<<>>>` 的东西交换一下就行了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define dw(l, r) ((l + r) | (l != r))
#define mid (l + r >> 1)
#define p dw(l, r)
#define lc dw(l, mid)
#define rc dw(mid + 1, r)
const int N = 5e5 + 7;
int i, j, k, n, m, l, r, s[N];
string t;
struct Yoimiya {
	int ls[2], rs[2], l[2], r[2], s[2], t, len;
	Yoimiya() {ls[0] = ls[1] = l[0] = l[1] = rs[0] = rs[1] = r[0] = r[1] = s[0] = s[1] = t = len = 0;}
	Yoimiya operator + (const Yoimiya&x) const {
		Yoimiya a;
		a.len = len + x.len;
		a.s[0] = max({s[0], x.s[0], r[0] + x.ls[0], x.l[1] + rs[0]});
		a.s[1] = max({s[1], x.s[1], r[1] + x.ls[1], x.l[0] + rs[1]});
		a.l[0] = max(l[0], len == l[0] ? len + x.l[0] : 0);
		a.l[1] = max(l[1], len == l[1] ? len + x.l[1] : 0);
		a.r[0] = max(x.r[0], x.len == x.r[0] ? x.len + r[0] : 0);
		a.r[1] = max(x.r[1], x.len == x.r[1] ? x.len + r[1] : 0);
		a.ls[0] = max({ls[0], len == ls[0] ? len + x.l[1] : 0, len == l[0] ? len + x.ls[0] : 0});
		a.ls[1] = max({ls[1], len == ls[1] ? len + x.l[0] : 0, len == l[1] ? len + x.ls[1] : 0});
		a.rs[0] = max({x.rs[0], x.len == x.rs[0] ? x.len + r[0] : 0, x.len == x.r[1] ? x.len + rs[0] : 0});
		a.rs[1] = max({x.rs[1], x.len == x.rs[1] ? x.len + r[1] : 0, x.len == x.r[0] ? x.len + rs[1] : 0});
		return a;
	}
	inline void upd() {
		swap(s[0], s[1]), swap(l[0], l[1]), swap(r[0], r[1]);
		swap(ls[0], ls[1]), swap(rs[0], rs[1]), t ^= 1;
	}
} Yoi, d[N<<1];
void build(int l, int r) {
	if(l ^ r) build(l, mid), build(mid + 1, r), d[p] = d[lc] + d[rc];
	else d[p].l[s[l]] = d[p].r[s[l]] = d[p].ls[s[l]] = d[p].rs[s[l]] = d[p].s[s[l]] = d[p].len = 1;
}
inline void push(int l, int r) {
	d[lc].upd(), d[rc].upd(), d[p].t = 0;
}
void chg(int x, int y, int l=1, int r=n) {
	if(x <= l && r <= y) {
		d[p].upd();
		return;
	}
	if(d[p].t) push(l, r);
	if(x <= mid) chg(x, y, l, mid);
	if(y > mid) chg(x, y, mid + 1, r);
	d[p] = d[lc] + d[rc];
}
Yoimiya ask(int x, int y, int l=1, int r=n) {
	if(r < x || l > y) return Yoimiya();
	if(x <= l && r <= y) return d[p];
	if(d[p].t) push(l, r);
	return ask(x, y, l, mid) + ask(x, y, mid + 1, r);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> t;
	for(i=0; i<t.length(); i++) s[i + 1] = t[i] ^ '<' ? 1 : 0;
	build(1, n);
	while(m--) {
		cin >> l >> r;
		chg(l, r), Yoi = ask(l, r);
		cout << max({Yoi.s[1], Yoi.l[0], Yoi.r[1]}) << "\n";
	}
	return 0;
}
 
```

---

## 作者：一念之间、、 (赞：5)

## 题意简述
说：给定长度为 $n\le 5\times 10^5$ 的字符串，每个位置是 $<$ 或者 $>$，$q\le 10^5$ 次询问，每次给定区间 $[l,r]$ 问：先翻转这个区间的元素，再询问**如果**将每个位置放一个球，球的移动沿着箭头方向，直到不能移动，个数最多的空有多少个球。

## 题解
介绍好写的分块做法，注意到时限 $3s$ 且询问只有 $10^5$ 次。

考虑一个询问，可以视为在 $<>$ 之间放一块板子，则答案就是最大相邻板子的距离，默认区间开头结尾有一块板子。

直接考虑分块，维护当前块内部答案，块内最靠左板子位置，块内最靠右板子位置，合并是简单的，注意到会有翻转修改，同时维护当前块翻转后的信息。

复杂度 $O(q\sqrt n)$。

## 代码

```cpp
#include<bits/stdc++.h>
namespace ifzw{
//~ #define int LL
#define ll long long
#define dd double
#define ull unsigned ll 
#define LL __int128
#define siz(A) ((int)A.size())
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
#define getchar gc
ll read()
{
	char c;
	ll w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	ll ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&(s==t)))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x),pc(op,0);
}
char ST;
const int xx=5e5+5;
const int B=700;
int n,q;
int a[xx],tag[xx],mn[xx][2],mx[xx][2],ans[xx][2],L[xx],R[xx],bel[xx];
char s[xx];
void pre(int x)
{
	int l=L[x],r=R[x];
	if(tag[x])
	{
		for(int i=l;i<=r;i++)s[i]^=tag[x];
		tag[x]=0;
	}
	mn[x][0]=-1,mx[x][0]=-1;
	mn[x][1]=-1,mx[x][1]=-1;
	int ct=0;ans[x][0]=ans[x][1]=0;
	for(int i=l;i<r;i++)
	{
		++ct,ans[x][0]=max(ans[x][0],ct);
		if(s[i]==0&&s[i+1]==1)
		{
			ct=0;
			mx[x][0]=i;
			if(mn[x][0]==-1)mn[x][0]=i;
		}
	}
	++ct,ans[x][0]=max(ans[x][0],ct);
	ct=0;
	for(int i=l;i<r;i++)
	{
		++ct,ans[x][1]=max(ans[x][1],ct);
		if(s[i]==1&&s[i+1]==0)
		{
			ct=0;
			mx[x][1]=i;
			if(mn[x][1]==-1)mn[x][1]=i;
		}
	}
	++ct,ans[x][1]=max(ans[x][1],ct);
}
int get(int x){return tag[bel[x]]^s[x];}
char ED;
int main(){
	cerr<<abs(&ST-&ED)/1024.0/1024<<"\n";
	#ifdef AAA
	system("ulimit -s 524288");
	cerr<<" stack is on \n";
	#endif 
	//~ freopen("a.in","r",stdin);
	//~ freopen("a.out","w",stdout);
	n=read(),q=read();
	//0: < 1：>
	for(int i=1;i<=n;i++)
	{
		char c;
		while((c=getchar())!='<'&&c!='>');
		if(c=='<')s[i]=0;
		if(c=='>')s[i]=1;
	}
	for(int i=1;i<=n;i++)
	{
		bel[i]=(i-1)/B+1;
		R[bel[i]]=i;
		if(!L[bel[i]])L[bel[i]]=i;
	}
	for(int i=1;i<=bel[n];i++)pre(i);
	while(q--)
	{
		int l=read(),r=read();
		if(bel[l]==bel[r])
		{
			for(int i=l;i<=r;i++)s[i]^=1;
			pre(bel[l]);
			int ct=0,an=0;
			for(int i=l;i<=r;i++)
			{
				++ct,an=max(an,ct);
				if(s[i]==0&&s[i+1]==1)ct=0;
			}
			cout<<an<<"\n";
			continue;
		}
		for(int i=l;i<=R[bel[l]];i++)s[i]^=1;
		for(int i=L[bel[r]];i<=r;i++)s[i]^=1;
		for(int i=bel[l]+1;i<=bel[r]-1;i++)tag[i]^=1;//提前翻转。
		pre(bel[l]),pre(bel[r]);
		int ct=0,an=0;
		for(int i=l;i<=R[bel[l]];i++)
		{
			++ct,an=max(an,ct);
			if(get(i)==0&&get(i+1)==1)ct=0;
		}
		//~ for(int i=1;i<=n;i++)cout<<get(i);
		//~ puts("");
		//~ cerr<<ct<<" "<<an<<"@#@#\n";
		for(int i=bel[l]+1;i<=bel[r]-1;i++)
		{
			if(mn[i][tag[i]]==-1)ct+=R[i]-L[i]+1,an=max(an,ct);
			else ct+=mn[i][tag[i]]-L[i]+1,an=max(an,ct),ct=R[i]-mx[i][tag[i]];
			an=max(an,ans[i][tag[i]]);
			if(get(R[i])==0&&get(R[i]+1)==1)ct=0;
		}
		for(int i=L[bel[r]];i<=r;i++)
		{
			++ct,an=max(an,ct);
			if(get(i)==0&&get(i+1)==1)ct=0;
		}
		cout<<an<<"\n";
	}
	pc('1',1);
	return 0;
}

}signed main(){return ifzw::main();}

```

---

## 作者：huayucaiji (赞：3)

**~~思路10min，程序2h，调试7h。~~**

看到上面的字，没有深厚代码功底和强大毅力的同学建议不要尝试切这道题。

**忠告：建议大家别看代码，因为太乱，基本上看不懂，看看思路和下面的细节提醒即可，代码当且仅当是在不知道哪里错是，对拍一下，对拍程序下面会给**

我们回到正题，看到这个题。我们发现所有满足 ```>>><<<```,```>>>>```,```<<<<```形式的区间会调到一个地方，所以我们要重点关注这个结构，下面我们称之为 “小可爱”（因为它像>_<这个表情）:D。我们给三种“小可爱”起个代号吧（也就是他们的类型）：

|“小可爱”形状|编号|
|:--:|:--:|:---:|:--:|
|>>>|$1$|
|<<<|$2$|
|><<|$3$|

看到区间的维护，很容易想到线段树，但是怎么维护？我们只需要维护 $l,r,ln,rn,lt,rt,lazy$ ~~即可~~，见下表：

||全称|意义|
|:--:|:--:|:---:|
|$l$|$l$|左节点编号|
|$r$|$r$|右节点编号|
|$ln$|$rnum$|从左起最长的“小可爱”的长度|
|$rn$|$lnum$|从右起最长的“小可爱”的长度|
|$lt$|$l type$|从左起最长的“小可爱”的编号|
|$rt$|$r type$|从右起最长的“小可爱”的编号|
|$lazy$|$lazy$|懒标记|

**线段树的定义**

```cpp
struct seg_tree {
	int ln,rn,mn,l,r;
	short lt,rt;
	int lazy;
	
	int ans() {
		return max(max(ln,rn),mn);
	}
	int len() {
		return r-l+1;
	}
	void make() {
		ln=rn=mn=lt=rt=l=r=lazy=0;
	}
	bool operator == (const seg_tree x) {
		return ln==x.ln&&rn==x.rn&&mn==x.mn&&lt==x.lt&&rt==x.rt&&l==x.l&&r==x.r;
	}
}s[2][maxn*20],ret[maxn*20];
```

知道两个区间的这些信息，我们就可以合并出一个新的区间，我们也就可以可以解决线段树的 ```build```。这个讨论太复杂了，讲不太清楚，可以自己思考一下 :)。

**合并：**

```cpp
seg_tree pushup(seg_tree a,seg_tree b) {
	calcnum++;
	seg_tree ret;
	ret.make();
	if(a==ret) {
		return b;
	}
	if(b==ret) {
		return a;
	}
	//l:
	//1:>>>>
	//2:<<<<
	//3:>><<
	if(a.len()==a.ln) {
		if(a.lt==1) {
			ret.ln=a.ln+b.ln;
			if(b.lt==1) {
				ret.lt=1;
			}
			else {
				ret.lt=3;
			}
		}
		else {
			if(b.lt==2) {
				ret.lt=a.lt;
				ret.ln=b.ln+a.ln;
			}
			else {
				ret.ln=a.ln;
				ret.lt=a.lt;
			}
		}
	}
	else {
		ret.ln=a.ln;
		ret.lt=a.lt;
	} 
	//r:
	//1:>>>>
	//2:<<<<
	//3:>><<
	if(b.len()==b.rn) {
		if(b.rt==2) {
			ret.rn=a.rn+b.rn;
			if(a.rt==2) {
				ret.rt=2;
			}
			else {
				ret.rt=3;
			}
		}
		else {
			if(a.rt==1) {
				ret.rt=b.rt;
				ret.rn=b.rn+a.rn;
			}
			else {
				ret.rn=b.rn;
				ret.rt=b.rt;
			}
		}
	}
	else {
		ret.rn=b.rn;
		ret.rt=b.rt;
	}
	//m:
	//1:>>>>
	//2:<<<<
	//3:>><<
	if(a.rt==1) {
		ret.mn=a.rn+b.ln;
	}
	else if(a.rt==2) {
		if(b.lt==2) {
			ret.mn=a.rn+b.ln;
		}
	}
	else {
		if(b.lt==2) {
			ret.mn=a.rn+b.ln;
		}
	}
	//
	if(ret.mn<a.mn) {
		ret.mn=a.mn;
	}
	if(ret.mn<b.mn) {
		ret.mn=b.mn;
	}
	
	ret.l=a.l;ret.r=b.r;
	
	return ret;
}
```

**build**

```cpp
void build(int l,int r,int p) {
	calcnum++;
	if(l==r) {
		s[0][p].ln=s[0][p].rn=s[0][p].mn=1;
		s[0][p].l=s[0][p].r=l;
		s[0][p].lazy=0;
		if(a[0][l]==0) {//'>' 对应 0
			s[0][p].lt=s[0][p].rt=1;
		}
		else {//'<' 对应 1
			s[0][p].lt=s[0][p].rt=2;
		}//初始化，也要讨论qwq
		
		s[1][p].ln=s[1][p].rn=s[1][p].mn=1;
		s[1][p].l=s[1][p].r=l;
		s[1][p].lazy=1;
		if(a[1][l]==0) {
			s[1][p].lt=s[1][p].rt=1;
		}
		else {
			s[1][p].lt=s[1][p].rt=2;
		}
		return ;
	}
	
	int mid=(l+r)>>1;
	
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	
	s[0][p]=pushup(s[0][p<<1],s[0][p<<1|1]);
	s[1][p]=pushup(s[1][p<<1],s[1][p<<1|1]);
}
```

那么有的小伙伴会发现我的线段树定义了```s[2][maxn]```。这是因为我们的特殊修改操作。我们发现，我们要处理这个修改操作最好的办法就是要建两颗树，一颗是原来的，一颗是倒过来的。只要涉及到翻转????，就交换一下信息。所以我们要维护两颗树。注意懒标记。

**modify**

```cpp
void modify(int l,int r,int p,int x,int y) {
	calcnum++;
	pushdown(p);
	if(y<l||r<x) {
		return ;
	}
	if(x<=l&&r<=y) {
		swap(s[0][p],s[1][p]);
		s[0][p].lazy^=1;
		return ;
	}
	int mid=(l+r)>>1;
	modify(l,mid,p<<1,x,y);
	modify(mid+1,r,p<<1|1,x,y);
	s[0][p]=pushup(s[0][p<<1],s[0][p<<1|1]);
	s[1][p]=pushup(s[1][p<<1],s[1][p<<1|1]);
}
```

最后是```query```。我们可以直接写一个返回类型为 seg_tree 的函数，当然这里提一下 void。我们可以在开一个数组放 答案，因为不会一个完整区间里数都是答案需要的。比如说对于 $n=5$ 一次询问为 $[2,4]$，那么在我们已经维护好的 $[1,3]$ 中，只有 $[2,3]$ 这个区间在内，我们的 ```ret```数组维护的就是 $[2,3]$ 中的信息。这样一路合并上去，我们得到的```ret[1]```就是最后答案区间啦。

**query**

```cpp
void query(int l,int r,int p,int x,int y) {
	pushdown(p);
	if(y<l||r<x) {
		seg_tree qwq;
		qwq.make();
		ret[p]=qwq;
		return ;
	}
	if(x<=l&&r<=y) {
		ret[p]=s[0][p];
		return ;
	}
	
	int mid=(l+r)>>1;
	
	query(l,mid,p<<1,x,y);
	query(mid+1,r,p<<1|1,x,y); 
	
	ret[p]=pushup(ret[p<<1],ret[p<<1|1]);
	return ;
}
```

最后说一下细节问题，这个题调试7h就是因为细节太多 :(

1.懒标记我们一定要小心，因为如果一个区间的懒标记为 $1$，他的父区间要下传的时候，我们就要把这个区间先换过来，但是懒标记改为 $1$。  
2.注意 $s_1$ 这颗树上的懒标记必须时时刻刻全部为 $0$！这样换过来的时候不会出问题。  
3.在 ```pushup```里面一定要小心小心再小心，一不留神就会写错。  
4.建议多对拍  
5.对于调试，有一个比较好的方法，特别是复杂度不对时（因为我遇到了），可以屏蔽一个函数，看看耗时是否减小很多，如果是的，那么这个函数一定出大问题了

**对拍程序见下**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}
int n,q;

signed main() {
	freopen("F.in","w",stdout);
	
	srand(time(NULL));
	
	n=400000+rand()+rand()+rand();
	q=90000+rand();
	cout<<n<<" "<<q<<endl;
	
	for(int i=1;i<=n;i++) {
		printf("%c",rand()%2==0? '>':'<');
	}
	cout<<endl;
	for(int i=1;i<=q;i++) {
		int x,y;
		x=35000+rand();
		y=rand()+x+rand();
		printf("%lld %lld\n",x,y);
	}
	return 0;
}
//造数据
```

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

signed main() {
	
	int t=read();
	system("cls");
	for(int i=1;i<=t;i++) {
		double a,b;
		printf("Test Case %d\n",i);
		
		printf("I'm makeing datum :D\n");
		system("duipai.exe");
		
		printf("I'm working on the answer ^_^\n");
		a=time(NULL);
		system("F_std.exe");
		b=time(NULL);
		printf("Done in %lf s\n",b-a);
		
		printf("Running.......\n");
		a=time(NULL);
		system("F.exe");
		b=time(NULL);
		printf("Done in %lf s\n",b-a);
		
		
		if(!system("fc my.out std.out")) {
			cout<<"Accepted !!!\n\n";
		}
		else {
			cout<<"Wrong answer>_<\n\n";
		}
	}

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
//测试
```

完整程序在[这里](https://www.luogu.com.cn/paste/do8i69x5)

~~不要在意火车头 :D~~

---

## 作者：duyi (赞：3)

# 进去看看吧↓

[更好的阅读体验](https://www.cnblogs.com/dysyn1314/p/13224383.html)

[题目链接](https://codeforces.com/contest/1371/problem/F)

首先，不难发现，对于每个形如``>>>...>><<...<<<``的结构，球会掉到中间的那个洞里。我们可以形象地把``>``看做向下的坡，``<``看做向上的坡，那么这个球运动的情况，就是顺着坡向下滚，很好理解。我们把每个这样的（下坡再上坡的）结构，称作一个“坑”，那么题目就是要询问一段区间里，“最大的坑”的大小。

因为是区间操作，区间查询，我们考虑用**线段树**维护。

具体来说，对线段树上一个区间，我们维护三个东西：

- 这段区间**最前面**的一个坑（也可能是半个坑，也就是只有下坡或只有上坡）。
- 这段区间**最后面**的一个坑（也可能是半个坑；也可能根本不存在，因为整段区间就只有一个坑，已经记录在上一条里了）。
- 这段区间，中间（不算最前面、最后面的坑），最大的坑的大小。

例如：``><<>><>><<>>>>``这段区间。

- 最前面的坑，就是``><<``。我们记录的时候，记录它的下坡长度：$1$，上坡长度：$2$。
- 最后面的坑，就是``>>>>``。我们记录的时候，记录它的下坡长度：$4$，上坡长度：$0$。
- 中间的，就是指``>><>><<``这段，有：``>><``和``>><<``两个坑。其中最大的是第二个，大小为$4$。我们就记录这个大小：$4$。

接下来，我们要重点解决两个问题。

问题一，是区间怎么合并？也就是在线段树上，当前区间有一左一右两个儿子，怎么把它们的信息合并起来（$\texttt{push_up}$）呢？发现重点，在于处理中间的拼接情况，也就是左儿子的“后面的坑”，和右儿子的“前面的坑”，如何结合。结合后，可能新产生$0$, $1$或$2$个“中间的坑”，也可能会影响到合并后的区间的“前面的坑”或“后面的坑”的形态。大力分类讨论即可。

问题二，是如何实现区间反转？我们可以在一开始建线段树的时候，就处理好“反转前”和“反转后”两套信息。当需要把一个区间反转时，就把这两套信息交换一下即可。

时间复杂度$O(n+q\log n)$。

参考代码（分类讨论写的比较麻烦，建议读者自己实现）：

```cpp
//韩信带净化，只有你们想不到的，没有毛队做不到的
//大力讨论就完事了，奥利给！！！
//problem:CF1371F
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int MAXN=5e5;
int n,q;
char s[MAXN+5];

struct RangeInfo{
	int left_down,left_up;
	int right_down,right_up;
	int ans;//除去头尾后的最大答案
	RangeInfo(){
		left_down=left_up=right_down=right_up=ans=0;
	}
};
RangeInfo merge(const RangeInfo& a,const RangeInfo& b){
	RangeInfo res;
	res.left_down=a.left_down;
	res.left_up=a.left_up;
	res.right_down=b.right_down;
	res.right_up=b.right_up;
	res.ans=max(a.ans,b.ans);
	
	if(a.right_up){
		assert(a.right_down!=0);
		if(b.left_down){
			res.ans=max(res.ans,a.right_down+a.right_up);
			if(b.left_up){
				if(b.right_down)res.ans=max(res.ans,b.left_down+b.left_up);
				else{
					res.right_down=b.left_down;
					res.right_up=b.left_up;
				}
			}
			else{
				res.right_down=b.left_down;
			}
		}
		else{
			assert(b.left_up!=0);
			if(b.right_down){
				res.ans=max(res.ans,a.right_down+a.right_up+b.left_up);
			}
			else{
				res.right_down=a.right_down;
				res.right_up=a.right_up+b.left_up;
			}
		}
	}
	else{
		if(a.right_down){
			if(b.left_down){
				if(b.left_up){
					if(b.right_down)res.ans=max(res.ans,a.right_down+b.left_down+b.left_up);
					else{
						res.right_down=a.right_down+b.left_down;
						res.right_up=b.left_up;
					}
				}
				else{
					res.right_down=a.right_down+b.left_down;
				}
			}
			else{
				assert(b.left_up!=0);
				if(b.right_down)res.ans=max(res.ans,a.right_down+b.left_up);
				else{
					res.right_down=a.right_down;
					res.right_up=b.left_up;
				}
			}
		}
		else{
			if(a.left_down){
				if(a.left_up){
					if(b.left_down){
						if(b.left_up){
							if(b.right_down)res.ans=max(res.ans,b.left_down+b.left_up);
							else{
								res.right_down=b.left_down;
								res.right_up=b.left_up;
							}
						}
						else{
							res.right_down=b.left_down;
						}
					}
					else{
						assert(b.left_up!=0);
						res.left_up=a.left_up+b.left_up;
					}
				}
				else{
					res.left_down=a.left_down+b.left_down;
					res.left_up=b.left_up;
				}
			}
			else{
				assert(a.left_up!=0);
				if(b.left_down){
					if(b.left_up){
						if(b.right_down)res.ans=max(res.ans,b.left_down+b.left_up);
						else{
							res.right_down=b.left_down;
							res.right_up=b.left_up;
						}
					}
					else{
						res.right_down=b.left_down;
					}
				}
				else{
					assert(b.left_up!=0);
					res.left_up=a.left_up+b.left_up;
				}
			}
		}
	}
	return res;
}
int getans(const RangeInfo& a){
	int ans=a.ans;
	ans=max(ans,a.left_down+a.left_up);
	ans=max(ans,a.right_down+a.right_up);
	return ans;
}
struct SegmentTree{
	RangeInfo cur[MAXN*4+5],rev[MAXN*4+5];
	bool tag[MAXN*4+5];
	void push_up(int p){
		cur[p]=merge(cur[p<<1],cur[p<<1|1]);
		rev[p]=merge(rev[p<<1],rev[p<<1|1]);
	}
	void build(int p,int l,int r){
		if(l==r){
			if(s[l]=='>'){
				cur[p].left_down=1;
				rev[p].left_up=1;
			}
			else{
				cur[p].left_up=1;
				rev[p].left_down=1;
			}
			return;
		}
		int mid=(l+r)>>1;
		build(p<<1,l,mid);
		build(p<<1|1,mid+1,r);
		push_up(p);
	}
	void upd(int p){
		tag[p]^=1;
		swap(cur[p],rev[p]);
	}
	void push_down(int p){
		if(tag[p]){
			upd(p<<1);
			upd(p<<1|1);
			tag[p]=0;
		}
	}
	void modify(int p,int l,int r,int ql,int qr){
		//区间反转
		if(ql<=l && qr>=r){
			upd(p);
			return;
		}
		int mid=(l+r)>>1;
		push_down(p);
		if(ql<=mid)modify(p<<1,l,mid,ql,qr);
		if(qr>mid)modify(p<<1|1,mid+1,r,ql,qr);
		push_up(p);
	}
	RangeInfo Q_res;
	bool flag;
	void query(int p,int l,int r,int ql,int qr){
		if(ql<=l && qr>=r){
			if(!flag){
				Q_res=cur[p];
				flag=1;
			}
			else Q_res=merge(Q_res,cur[p]);
			return;
		}
		int mid=(l+r)>>1;
		push_down(p);
		if(ql<=mid)query(p<<1,l,mid,ql,qr);
		if(qr>mid)query(p<<1|1,mid+1,r,ql,qr);
		push_up(p);
	}
	RangeInfo query(int l,int r){
		Q_res=RangeInfo();
		flag=0;
		query(1,1,n,l,r);
		return Q_res;
	}
}T;

int main() {
	cin>>n>>q;
	cin>>(s+1);
	T.build(1,1,n);
	while(q--){
		int l,r;cin>>l>>r;
		T.modify(1,1,n,l,r);
		RangeInfo res=T.query(l,r);
		cout<<getans(res)<<endl;
	}
	return 0;
}
```


---

## 作者：Exp10re (赞：2)

大码量数据结构练手题。

线段树可爱捏。

## 解题思路

考虑到答案一定是以下三种情况当中的一种：

- 靠左的极长 `<<<` 段，记为 $ll$。
- 靠右的极长 `>>>` 段，记为 $rr$。
- 任意位置的极长 `>>...><...<` 段，记为 $mt$。

考虑如何维护 $ll$。

- 维护每一段的 $ll$。
- 上传时，若左儿子 $ll$ 等于左儿子本身长度，则父亲的 $ll=$ 左儿子长度 + 右儿子的 $ll$。
- 否则，父亲的 $ll=$ 左儿子的 $ll$。

类比可以得出 $rr$ 维护方式类似。

现在考虑如何维护 $mt$。

要想维护 $mt$，就要先维护：

- 靠左的极长 `>>...><...<` 段，记为 $lt$。
- 靠右的极长 `>>...><...<` 段，记为 $rt$。

首先考虑 $lt$ 如何维护，注意到 $lt$ 为以下四个数值中的最大值。

- 左儿子的 $lt$。
- 左儿子的长度 + 右儿子的 $ll$，当且仅当左儿子的 $rr=$ 左儿子的长度。（即：`>>>>>>`+`<<<<<` 的情况）
- 左儿子的长度 + 右儿子的 $lt$，当且仅当左儿子的 $rr=$ 左儿子的长度。（即：`>>>>>>`+`>><<<` 的情况）
- 左儿子的长度 + 右儿子的 $ll$，当且仅当左儿子的 $rt=$ 左儿子的长度。（即：`>>>><<`+`<<<<<` 的情况）

$rt$ 同理。

这些维护出来之后 $mt$ 就很好算了，$lt$ 为以下五个数值中的最大值。

- 左儿子的 $mt$。
- 右儿子的 $mt$。
- 左儿子的 $rt$ + 右儿子的 $ll$。（即：`...>><`+`<<<...` 的情况）
- 右儿子的 $lt$ + 左儿子的 $rr$。（即：`...>>>`+`><<...` 的情况）
- 右儿子的 $ll$ + 左儿子的 $rr$。（即：`...>>>`+`<<<...` 的情况）

这些就是查询时所有需要维护的值了，但别忘了还有修改（区间取反）操作。

我们对于每一个数值，维护一个意义相反的数值即可。（例：对于靠左的极长 `<<<` 段 $ll$，我们额外维护靠左的极长 `>>>` 段 $lr$）

那么在区间取反时，交换两个意义相反的数值即可。

建议搭配代码食用。

## 代码

三目运算符滥用警告。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=500201;
struct segtree
{
	long long l,r,len,lazy;
	long long ll,lr,lt,ld;
	long long mt,md;
	long long rl,rr,rt,rd;
};
segtree a[MAXN*4];
char s[MAXN];
long long n,q;
segtree pushup_(segtree L,segtree R)
{
	segtree ans;
	ans.l=L.l;
	ans.r=R.r;
	ans.len=L.len+R.len;
	ans.lazy=0;
	ans.ll=(L.ll==L.len?L.len+R.ll:L.ll);
	ans.lr=(L.lr==L.len?L.len+R.lr:L.lr);
	ans.lt=max((L.lt==L.len?L.len+R.ll:L.lt),(L.lr==L.len?L.len+max(R.ll,R.lt):L.lt));
	ans.ld=max((L.ld==L.len?L.len+R.lr:L.ld),(L.ll==L.len?L.len+max(R.lr,R.ld):L.ld));
	ans.rl=(R.rl==R.len?R.len+L.rl:R.rl);
	ans.rr=(R.rr==R.len?R.len+L.rr:R.rr);
	ans.rt=max((R.rt==R.len?R.len+L.rr:R.rt),(R.rl==R.len?R.len+max(L.rr,L.rt):R.rt));
	ans.rd=max((R.rd==R.len?R.len+L.rl:R.rd),(R.rr==R.len?R.len+max(L.rl,L.rd):R.rd));
	ans.mt=max(max(L.mt,R.mt),max(L.rr+R.ll,max(L.rt+R.ll,R.lt+L.rr)));
	ans.md=max(max(L.md,R.md),max(L.rl+R.lr,max(L.rd+R.lr,R.ld+L.rl)));
	return ans;
}
void reverse(segtree &x)
{
	swap(x.ll,x.lr);
	swap(x.ld,x.lt);
	swap(x.rl,x.rr);
	swap(x.rd,x.rt);
	swap(x.md,x.mt);
	return;
}
void pushdown(long long x)
{
	if(a[x].lazy==1)
	{
		reverse(a[x*2]);
		a[x*2].lazy^=1;
		reverse(a[x*2+1]);
		a[x*2+1].lazy^=1;
		a[x].lazy=0;
	}
	return;
}
void pushup(long long x)
{
	a[x]=pushup_(a[x*2],a[x*2+1]);
	return;
}
void build(long long x,long long l,long long r)
{
	a[x].l=l;
	a[x].r=r;
	a[x].len=r-l+1;
	a[x].lazy=0;
	if(l==r)
	{
		if(s[l]=='<')
		{
			a[x].ll=1;
			a[x].rl=1;
		}
		else
		{
			a[x].lr=1;
			a[x].rr=1;
		}
		return;
	}
	long long mid=(a[x].l+a[x].r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	pushup(x);
	return;
}
void inc(long long x,long long l,long long r)
{
	if(a[x].l==l&&a[x].r==r)
	{
		reverse(a[x]);
		a[x].lazy^=1;
		return;
	}
	pushdown(x);
	long long mid=(a[x].l+a[x].r)/2;
	if(l<=mid)
	{
		inc(x*2,l,min(mid,r));
	}
	if(r>=mid+1)
	{
		inc(x*2+1,max(mid+1,l),r);
	}
	pushup(x);
	return;
}
segtree query(long long x,long long l,long long r)
{
	if(a[x].l==l&&a[x].r==r)
	{
		return a[x];
	}
	pushdown(x);
	segtree ans,ans1,ans2;
	long long mid=(a[x].l+a[x].r)/2,flag1=0,flag2=0;
	if(l<=mid)
	{
		ans=ans1=query(x*2,l,min(mid,r));
		flag1=1;
	}
	if(r>=mid+1)
	{
		ans=ans2=query(x*2+1,max(l,mid+1),r);
		flag2=1;
	}
	if(flag1&&flag2)
	{
		ans=pushup_(ans1,ans2);
	}
	return ans;
}
int main()
{
	segtree ans;
	long long i,ta,tb;
	scanf("%lld%lld",&n,&q);
	scanf("%s",s+1);
	build(1,1,n);
	for(i=1;i<=q;i++)
	{
		scanf("%lld%lld",&ta,&tb);
		inc(1,ta,tb);
		ans=query(1,ta,tb);
		printf("%lld\n",max(max(ans.ll,ans.rr),ans.mt));
	}
	return 0;
}
```

---

## 作者：Jsxts_ (赞：2)

来个短一点的。

还是考虑用线段树直接维护区间 $[l,r]$ 都有球时的答案。那么考虑合并时需要什么信息。

先看看合并的种类：

`>>>> + >><< , >><< + <<<<`

就只有这两种，所以直接维护 $lv,rv$ 表示从左端点开始的连续 `<<<` 和从右端点开始的 `>>>`、$ls,rs$ 表示从左/右端点开始的 `>><<` 即可。

取反可以偷个懒，分别维护取反/不取反的结构体，修改直接交换即可。

具体合并细节看代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int inf = 1e9;
const ll INF = 1e15;
const int N = 5e5;
inline int read() {
	int s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = (s << 3) + (s << 1) + ch - '0', ch = getchar();
	return s*f;
}
int n,q;
char s[N + 10];
struct node {
	int v,len,lv,rv,ls,rs;
	//ls,rs:贴着左/右边的一个>><<
	//lv,rv:贴着左/右边的一个<<</>>>> 
	friend node operator + (node a,node b) {
		node c;
		c.len = a.len + b.len;
		c.lv = a.lv + (a.lv == a.len) * b.lv;
		c.rv = b.rv + (b.rv == b.len) * a.rv;
		c.ls = a.ls + (a.ls == a.len) * b.lv;//>><< + <<<<
		if (a.rv == a.len) c.ls = max(c.ls,a.len + b.ls);// >>>> + >><<
		c.rs = b.rs + (b.rs == b.len) * a.rv;//>>>> + >><<
		if (b.lv == b.len) c.rs = max(c.rs,b.len + a.rs);// >><< + <<<<
		c.v = max({a.v,b.v,a.rv + b.ls,a.rs + b.lv});
		return c;
	}
};
struct Seg {
	int l,r,tag;
	node v,vf;
}t[N * 4 + 10];
void pushup(int x) {
	t[x].v = t[x<<1].v + t[x<<1|1].v;
	t[x].vf = t[x<<1].vf + t[x<<1|1].vf;
}
void build(int x,int l,int r) {
	t[x].l = l, t[x].r = r;
	if (l == r) {
		t[x].v = {1,1,s[l] == '<',s[l] == '>',1,1};
		t[x].vf = {1,1,s[l] == '>',s[l] == '<',1,1};
		return;
	}
	int mid = l + r >> 1;
	build(x<<1,l,mid), build(x<<1|1,mid + 1,r);
	pushup(x);
}
void f(int x) {
	swap(t[x].v,t[x].vf);
	t[x].tag ^= 1;
}
void pushdown(int x) {
	if (t[x].tag) f(x<<1), f(x<<1|1), t[x].tag = 0;
}
void modify(int x,int l,int r) {
	if (t[x].l >= l && r >= t[x].r) {
		f(x);
		return;
	}
	int mid = t[x].l + t[x].r >> 1;
	pushdown(x);
	if (mid >= l) modify(x<<1,l,r);
	if (mid < r) modify(x<<1|1,l,r);
	pushup(x);
}
node query(int x,int l,int r) {
	if (t[x].l >= l && r >= t[x].r) return t[x].v;
	int mid = t[x].l + t[x].r >> 1;
	if (mid >= r) return query(x<<1,l,r);
	if (mid < l) return query(x<<1|1,l,r);
	return query(x<<1,l,r) + query(x<<1|1,l,r);
}
int main() {
	n = read(), q = read();
	scanf("%s",s + 1);
	build(1,1,n);
	while (q -- ) {
		int l = read(),r = read();
		modify(1,l,r);
		printf("%d\n",query(1,l,r).v);
	}
	return 0;
}
```


---

## 作者：FreedomKing (赞：1)

巨长逆天线段树题，大概是我写过的维护元素最多的线段树了。

### 思路

通过观察题目，需要我们维护一个序列支持查询形如 `><` 的最长子串的长度，并且可以在较优的时间内进行区间取反操作。

考虑使用线段树进行维护，下面记 `<` 为 $1$，`>` 为 $0$。我们需要维护以下几个元素：子串最长的 $01$ 串的长度，子串最长的 $10$ 串的长度，子串的左极长 $0$ 串的长度，子串的右极长 $0$ 串的长度，子串的左极长 $1$ 串的长度，子串右极长 $1$ 串的长度，子串左极长 $01$ 串的长度，子串右极长 $01$ 串的长度，子串左极长 $10$ 串的长度，子串右极长 $10$ 串的长度，子串取反次数。维护元素非常多，特别容易写混，你怎么知道我调了一天。

然后开始解释各元素的作用。显然，子串最长的 $01$ 串的长度就是子串的答案，然后考虑每次反转后 `><` 会变成 `<>`，而 `<>` 也会变成 `><`，所以维护子串最长的 $10$ 串的长度，每当反转子串时交换两个元素的值即可；在合并区间时，以左子串为例，我们需要讨论几种情况：左子串存在部分连续，整个子串并不是完全连续的；左子串不仅存在连续，且整个子串都是连续的某种元素，那么子串的右端点在合并时就有可能与右边的区间形成合法子串。合并时取最大值即可。

---

## 作者：stoorz (赞：1)

$\operatorname{Update\ on\ 2020.07.13:}$ 修改了一些表述错误。

首先可以把若干个 `>>><<` 看做一个块，也就是求会落到同一个洞里的区间看做一个块。

这道题一眼看过去就很线段树。我们考虑将 $[l,mid]$ 和 $(mid,r]$ 合并时，区间 $[l,r]$ 的答案 $ans$ 就等于左右区间各自的 $ans$ 以及 $[l,mid]$ 的最右一个块和 $(mid,r]$ 最左一个块产生的贡献的最大值。

所以我们在线段树的每一个节点上维护 $llen,lpos,rlen,rpos$ 分别表示最左/右的块的长度以及求会落到哪一个洞内。

那么合并时，分别讨论四种情况，以合并最左的块为例：（`|` 表示 $mid$ 的位置）

- 如果 $[l,mid].llen$ 等于其区间长度，那么需要考虑以下三种情况：`>>>|<<<`，`>>>|><<`，`><<|<<<`。
- 否则 $[l,r]$ 最左的块就和 $[l,mid]$ 一样。

具体细节请自行思考，注意每种情况 $lpos$ 的位置。合并最右区间同理。

那么接下来就是区间修改操作了。我们发现直接修改不好在较优复杂度内重新维护那四个信息。但是在不修改其子区间的情况下，一个区间就只会有两种情况（正着和反着），所以我们可以在维护正着的四个信息时，同时维护如果把这个区间反过来的话的四个信息。维护其实是同理的，都是从子区间向上合并。

那如果修改区间 $[l,r]$，那么就把该区间的正反的四个标记互换。然后给这个区间打上懒标记。回溯时再重新维护其祖先区间的值。

对于区间询问，其实和合并是一个道理的。我直接暴力维护一个八元组 $(l,r,llen,lpos,rlen,rpos,ans,len)$，然后将每一个子区间合并。应该有更简单的方法。欢迎神仙 D 爆我 Orz。

时间复杂度 $O(n\log n)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N=500010;
int n,Q,ql,qr;
char ch[N];

struct Treenode  //询问时的八元组
{
	int l,r,lpos,rpos,llen,rlen,ans,len;
	
	friend Treenode operator +(Treenode p,Treenode q)  //其实和 pushup 是完全一样的
	{
		Treenode x;
		int mid=p.r;
		x.l=p.l; x.r=q.r;
		if (p.llen==p.len && p.lpos>=mid && q.lpos<=mid)
			x.lpos=mid,x.llen=p.llen+q.llen;
		else if (p.llen==p.len && p.lpos>=mid && q.lpos>mid)
			x.lpos=q.lpos,x.llen=p.llen+q.llen; 
		else if (p.llen==p.len && p.lpos<mid && q.lpos<=mid)
			x.lpos=p.lpos,x.llen=p.llen+q.llen;
		else 
			x.lpos=p.lpos,x.llen=p.llen;
			
		if (q.rlen==q.len && p.rpos>=mid && q.rpos<=mid)
			x.rpos=mid,x.rlen=p.rlen+q.rlen;
		else if (q.rlen==q.len && p.rpos>=mid && q.rpos>mid)
			x.rpos=q.rpos,x.rlen=p.rlen+q.rlen;
		else if (q.rlen==q.len && p.rpos<mid && q.rpos<=mid)
			x.rpos=p.rpos,x.rlen=p.rlen+q.rlen;
		else
			x.rpos=q.rpos,x.rlen=q.rlen;
			
		x.ans=max(p.ans,q.ans);
		if (p.rpos>=mid || q.lpos<=mid) x.ans=max(x.ans,p.rlen+q.llen);
		return x;
	}
};

struct SegTree
{
	int l[N*4],r[N*4],lpos[2][N*4],rpos[2][N*4],llen[2][N*4],rlen[2][N*4],ans[2][N*4],len[N*4],lazy[N*4];
	
	void rev(int x)  //区间翻转，直接将正反两种情况的值交换
	{
		lazy[x]^=1;
		swap(llen[0][x],llen[1][x]); swap(lpos[0][x],lpos[1][x]);
		swap(rlen[0][x],rlen[1][x]); swap(rpos[0][x],rpos[1][x]);
		swap(ans[0][x],ans[1][x]);
	}
	
	void pushup(int x)  //合并
	{
		int mid=(l[x]+r[x])>>1;
		for (int id=0;id<=1;id++)  //两种情况都要合并
		{
        //每一组有四个 if 分别对应上述四种情况
        //请注意当左子区间的 llen 等于其长度时，右子区间的 llen 也可能会产生贡献
			if (llen[id][x*2]==len[x*2] && lpos[id][x*2]>=mid && lpos[id][x*2+1]<=mid)
				lpos[id][x]=mid,llen[id][x]=llen[id][x*2]+llen[id][x*2+1];
			else if (llen[id][x*2]==len[x*2] && lpos[id][x*2]>=mid && lpos[id][x*2+1]>mid)
				lpos[id][x]=lpos[id][x*2+1],llen[id][x]=llen[id][x*2]+llen[id][x*2+1]; 
			else if (llen[id][x*2]==len[x*2] && lpos[id][x*2]<mid && lpos[id][x*2+1]<=mid)
				lpos[id][x]=lpos[id][x*2],llen[id][x]=llen[id][x*2]+llen[id][x*2+1];
			else
				lpos[id][x]=lpos[id][x*2],llen[id][x]=llen[id][x*2];
				
			if (rlen[id][x*2+1]==len[x*2+1] && rpos[id][x*2]>=mid && rpos[id][x*2+1]<=mid)
				rpos[id][x]=mid,rlen[id][x]=rlen[id][x*2]+rlen[id][x*2+1];
			else if (rlen[id][x*2+1]==len[x*2+1] && rpos[id][x*2]>=mid && rpos[id][x*2+1]>mid)
				rpos[id][x]=rpos[id][x*2+1],rlen[id][x]=rlen[id][x*2]+rlen[id][x*2+1];
			else if (rlen[id][x*2+1]==len[x*2+1] && rpos[id][x*2]<mid && rpos[id][x*2+1]<=mid)
				rpos[id][x]=rpos[id][x*2],rlen[id][x]=rlen[id][x*2]+rlen[id][x*2+1];
			else
				rpos[id][x]=rpos[id][x*2+1],rlen[id][x]=rlen[id][x*2+1];
		
			ans[id][x]=max(ans[id][x*2],ans[id][x*2+1]);
			if (rpos[id][x*2]>=mid) ans[id][x]=max(ans[id][x],rlen[id][x*2]+llen[id][x*2+1]);
			if (lpos[id][x*2+1]<=mid) ans[id][x]=max(ans[id][x],rlen[id][x*2]+llen[id][x*2+1]);
        //后面两个 if 是计算左子树的最右一个块和右子树的最左一个块合并产生的贡献
		}
	}
	
	void pushdown(int x)
	{
		if (lazy[x])
		{
			lazy[x]=0;
			rev(x*2); rev(x*2+1);
		}
	}
	
	void build(int x,int ql,int qr)
	{
		l[x]=ql; r[x]=qr; len[x]=qr-ql+1;
		if (ql==qr)
		{
			ans[0][x]=llen[0][x]=rlen[0][x]=ans[1][x]=llen[1][x]=rlen[1][x]=1;
			if (ch[ql]=='<') lpos[0][x]=rpos[0][x]=ql-1,lpos[1][x]=rpos[1][x]=qr;
			if (ch[ql]=='>') lpos[0][x]=rpos[0][x]=qr,lpos[1][x]=rpos[1][x]=ql-1;
			return;
		}
		int mid=(ql+qr)>>1;
		build(x*2,ql,mid); build(x*2+1,mid+1,qr);
		pushup(x);
	}
		
	void update(int x,int ql,int qr)
	{
		if (l[x]==ql && r[x]==qr)
		{
			rev(x);
			return;
		}
		pushdown(x);
		int mid=(l[x]+r[x])>>1;
		if (qr<=mid) update(x*2,ql,qr);
		else if (ql>mid) update(x*2+1,ql,qr);
		else update(x*2,ql,mid),update(x*2+1,mid+1,qr);
		pushup(x);
	}
	
	Treenode query(int x,int ql,int qr)
	{
		if (l[x]==ql && r[x]==qr)
			return (Treenode){l[x],r[x],lpos[0][x],rpos[0][x],llen[0][x],rlen[0][x],ans[0][x],len[x]};
		pushdown(x);
		int mid=(l[x]+r[x])>>1;
		if (qr<=mid) return query(x*2,ql,qr);
		if (ql>mid) return query(x*2+1,ql,qr);
		return query(x*2,ql,mid)+query(x*2+1,mid+1,qr);
	}
}seg;

int main()
{
	scanf("%d%d",&n,&Q);
	scanf("%s",ch+1);
	seg.build(1,1,n);
	while (Q--)
	{
		scanf("%d%d",&ql,&qr);
		seg.update(1,ql,qr);
		printf("%d\n",seg.query(1,ql,qr).ans);
	}
	return 0;
} 
```

---

## 作者：C_Pos_Princess (赞：0)

### 题解

这个题重点在抽象题意，题意转化完了其实就转换成了最长的什么什么区间的问题。

这里我们把 \ 看作 0，把 / 看作 1，那么我们维护的答案即为最长的前缀全是 0，后缀全是 1 的序列。

考虑维护，我么只需要维护每个区间反转之前的答案和反转之后的答案。

类似的，我们要维护从每个左端点开始的答案，从右端点开始的答案，以及反转后的答案。


### 代码


```
#include<bits/stdc++.h>
using namespace std;
int n, m;
const int N = 500010;
struct node {
	int l, r;
	int ans10, ans01;
	int l0, r0;
	int l1, r1;
	int len;
	int l01, l10;
	int r01, r10;
	int m1, m0, m01, m10;
	int lazy;
} tree[N << 2];


void rev(int root) {
	swap(tree[root].l0, tree[root].l1);
	swap(tree[root].r0, tree[root].r1);
	swap(tree[root].m0, tree[root].m1);
	swap(tree[root].l01, tree[root].l10);
	swap(tree[root].r01, tree[root].r10);
	swap(tree[root].m01, tree[root].m10);
	tree[root].lazy ^= 1;
}

void push_down(int root) {
	if (tree[root].lazy) {
		tree[root].lazy = 0;
		rev(root << 1);
		rev(root << 1 | 1);
	}
}


void pushup(node &rt, node ls, node rs) {
	rt.len = ls.len + rs.len;

	rt.l0 = ls.l0 + (ls.l0 == ls.len) * rs.l0;
	rt.r0 = rs.r0 + (rs.r0 == rs.len) * ls.r0;
	rt.m0 = max(ls.r0 + rs.l0, max(ls.m0, rs.m0));

	rt.l1 = ls.l1 + (ls.l1 == ls.len) * rs.l1;
	rt.r1 = rs.r1 + (rs.r1 == rs.len) * ls.r1;
	rt.m1 = max(ls.r1 + rs.l1, max(ls.m1, rs.m1));

	int ans = max(rt.m0, rt.m1);

	rt.m01 = max(max(max(ls.m01, rs.m01), max(ls.r0 + rs.l01, ls.r01 + rs.l1)), ans);
	rt.m10 = max(max(max(ls.m10, rs.m10), max(ls.r1 + rs.l10, ls.r10 + rs.l0)), ans);

	rt.l01 = max(max(ls.l0 + (ls.l0 == ls.len) * rs.l01, ls.l01 + (ls.l01 == ls.len) * rs.l1), rt.l0);
	rt.l10 = max(max(ls.l1 + (ls.l1 == ls.len) * rs.l10, ls.l10 + (ls.l10 == ls.len) * rs.l0), rt.l1);
	rt.r01 = max(max(rs.r1 + (rs.r1 == rs.len) * ls.r01, rs.r01 + (rs.r01 == rs.len) * ls.r0), rt.r1);
	rt.r10 = max(max(rs.r0 + (rs.r0 == rs.len) * ls.r10, rs.r10 + (rs.r10 == rs.len) * ls.r1), rt.r0);

}

string s;
void build(int root, int l, int r) {
	tree[root].l = l;
	tree[root].r = r;
	tree[root].len = r - l + 1;
	if (l == r) {
		tree[root].m01 = tree[root].m10 = tree[root].l01 = tree[root].l10 = tree[root].r01 = tree[root].r10 = 1;
		if (s[l - 1] == '/') {
			tree[root].m1 = tree[root].r1 = tree[root].l1 = 1;
		} else {
			tree[root].m0 = tree[root].r0 =  tree[root].l0 = 1;
		}
		return;
	}
	int mid = l + r >> 1;
	build(root << 1, l, mid);
	build(root << 1 | 1, mid + 1, r);
	pushup(tree[root], tree[root << 1], tree[root << 1 | 1]);
}

void solve(int root, int l, int r) {
	if (l <= tree[root].l && r >= tree[root].r) {
		rev(root);
		return;
	}
	int mid = tree[root].l + tree[root].r >> 1;
	push_down(root);
	if (l <= mid) solve(root << 1, l, r);
	if (r > mid) solve(root << 1 | 1, l, r);
	pushup(tree[root], tree[root << 1], tree[root << 1 | 1]);
}

node query(int root, int l, int r) {
	if (l <= tree[root].l && r >= tree[root].r) {
		return tree[root];
	}
	int mid = tree[root].l + tree[root].r >> 1;
	node ans;
	push_down(root);
	if (l <= mid && r > mid) {
		pushup(ans, query(root << 1, l, mid), query(root << 1 | 1, mid + 1, r));
		return ans;
	}
	if (l <= mid) return query(root << 1, l, r);
	else return query(root << 1 | 1, l, r);
}


int main() {
	freopen("ball.in","r",stdin);
	freopen("ball.out","w",stdout);
	cin >> n >> m;
//	string s;
	cin >> s;
	build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		int l, r;
		scanf("%d%d", &l, &r);
		solve(1, l, r);
		node ans = query(1, l, r);
		printf("%d\n", max(ans.m01, max(ans.m1, ans.m0)));
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：hellolin (赞：0)

# CF1371F Raging Thunder 题解

痛苦大码量大分讨 DS。

看到【区间反转】和【区间查询】两种操作，首先想到可以用线段树维护。

我们记录形如 `>>><<<` 区间的最大长度（记为 $a$），在这个区间内的球都会滚动到中间的空隙。同时注意在边缘上的 `<<<` 和 `>>>` 区间也要考虑进来，因为这里的球可以滚动到传送带两侧的空隙（即代码中的 `val()` 函数）。

为了方便反转操作，还要记录 `<<<>>>` 区间的最大长度（记为 $b$）。

然后考虑节点合并，这里的合并方案并不唯一，我使用的方法是记录左端的第一段极长传送带长度及其方向（记为 $lc_1$ 和 $ld$），以及第二段极长传送带长度（记为 $lc_2$），右端同理记录，记为 $rc_1, rc_2, rd$。

以下，`>` 为 $1$ 方向，`<` 为 $0$ 方向。

按照以下规则合并 $x$ 和 $y$ 两个区间：

1. 如果 $x$ 仅由一个方向的传送带构成，即 $lc_{x,2} = 0$：
   - 如果 $x$ 左端第一段与 $y$ 方向相同（$ld_x = ld_y$），结果的 $lc_1 = lc_{x,1} + lc_{y,1}, lc_2 = lc_{y,2}$；
   - 如果 $x$ 左端第一段与 $y$ 方向不同（$ld_x \not = ld_y$），结果的 $lc_1 = lc_{x,1}, lc_2 = lc_{y,1}$。
2. 如果 $x$ 由两个方向的传送带区间构成，即 $lc_{x,1} + lc_{x, 2} = len_{x}$：
   - 如果 $x$ 左端第一段与 $y$ 方向相同，结果的 $lc_1 = lc_{x,1}, lc_2 = lc_{x,2}$；
   - 如果 $x$ 左端第一段与 $y$ 方向不同，结果的 $lc_1 = lc_{x,1}, lc_2 = lc_{x,2} + lc_{y,1}$。
3. 如果 $x$ 由两个以上方向的传送带区间构成，结果的 $lc_1 = lc_{x,1}, lc_2 = lc{x,2}$。
4. 无论 $x$ 内部情况如何，结果的 $ld = ld_x$。
5. 对于以上规则，右端同理，只需相应替换即可。

接下来合并两个区间的 $a, b$：

1. 结果的 $a$ 取下列数的最大值：
   - $a_x$；
   - $a_y$；
   - 如果 $rd_x=1 \wedge ld_y=0$，考虑 $rc_{x,1} + lc_{y,1}$；
   - 如果 $rd_x=1 \wedge ld_y=1 \wedge lc_{y,2} \not = 0$，考虑 $rc_{x,1} + lc_{y,1} + lc_{y,2}$；
   - 如果 $rd_x=0 \wedge ld_y=0 \wedge rc_{x,2} \not = 0$，考虑 $rc_{x,1} + rc_{x,2} + lc_{y,1}$。
2. 结果的 $b$ 同理取下列数的最大值：
   - $b_x$；
   - $b_y$；
   - 如果 $rd_x=0 \wedge ld_y=1$，考虑 $rc_{x,1} + lc_{y,1}$；
   - 如果 $rd_x=0 \wedge ld_y=0 \wedge lc_{y,2} \not = 0$，考虑 $rc_{x,1} + lc_{y,1} + lc_{y,2}$；
   - 如果 $rd_x=1 \wedge ld_y=1 \wedge rc_{x,2} \not = 0$，考虑 $rc_{x,1} + rc_{x,2} + lc_{y,1}$。

这样我们可以写出线段树节点合并：

``` cpp
static constexpr int N = 5e5 + 5;
struct node {
  // 左端第一长、第二长
  int l1, l2;
  bool ld;
  // 右端第一长、第二长
  int r1, r2;
  bool rd;
  // 10 长度 & 01 长度
  int a, b;
  // 区间左右端点和长度
  int l, r, len;

  friend node operator+(const node &a, const node &b) {
    return {
        a.l1 + b.l1 * (a.l2 == 0 && a.ld == b.ld),
        a.l2 + b.l2 * (a.l2 == 0 && a.ld == b.ld) + b.l1 * (a.l1 + a.l2 == a.len && a.ld != b.ld),
        a.ld,

        b.r1 + a.r1 * (b.r2 == 0 && a.rd == b.rd),
        b.r2 + a.r2 * (b.r2 == 0 && a.rd == b.rd) + a.r1 * (b.r1 + b.r2 == b.len && a.rd != b.rd),
        b.rd,

        max({a.a, b.a, a.rd == 1 && b.ld == 0 ? a.r1 + b.l1 : 0, a.rd == 0 && a.r2 && b.ld == 0 ? a.r1 + a.r2 + b.l1 : 0, a.rd == 1 && b.ld == 1 && b.l2 ? a.r1 + b.l1 + b.l2 : 0}),
        max({a.b, b.b, a.rd == 0 && b.ld == 1 ? a.r1 + b.l1 : 0, a.rd == 1 && a.r2 && b.ld == 1 ? a.r1 + a.r2 + b.l1 : 0, a.rd == 0 && b.ld == 0 && b.l2 ? a.r1 + b.l1 + b.l2 : 0}),

        a.l, b.r, a.len + b.len};
  }

  void rev() { // 进行反转操作
    ld ^= 1, rd ^= 1;
    swap(a, b);
  }
  int val() { // 这个函数计算区间最终答案，最后要输出 query(l, r).val()。
    return max({a, ld == 0 ? l1 : 0, rd == 1 ? r1 : 0});
  }
} tr[N << 2];
```

剩余部分就和正常线段树无异了，注意两次反转操作可以抵消。

``` cpp
int n, m;
bool d[N]; // 方向 > 为 1，< 为 0
bool lz[N << 2];

void update(int x) {
  tr[x] = tr[x << 1] + tr[x << 1 | 1];
}
void pushdown(int x) {
  if (lz[x]) {
    lz[x] = false;
    tr[x << 1].rev(), tr[x << 1 | 1].rev();
    lz[x << 1] ^= 1, lz[x << 1 | 1] ^= 1;
  }
}
void build(int l = 1, int r = n, int x = 1) {
  if (l == r) return tr[x] = {
                         1, 0, d[l],
                         1, 0, d[l],
                         0, 0,
                         l, r, 1},
                     void();
  int mid = (l + r) >> 1;
  build(l, mid, x << 1), build(mid + 1, r, x << 1 | 1);
  update(x);
}
void modify(int l, int r, int x = 1) {
  if (l <= tr[x].l && tr[x].r <= r) return lz[x] ^= 1, tr[x].rev(), void();
  int mid = (tr[x].l + tr[x].r) >> 1;
  pushdown(x);
  if (l <= mid) modify(l, r, x << 1);
  if (r > mid) modify(l, r, x << 1 | 1);
  update(x);
}
node query(int l, int r, int x = 1) {
  if (l <= tr[x].l && tr[x].r <= r) return tr[x];
  int mid = (tr[x].l + tr[x].r) >> 1;
  pushdown(x);
  if (l <= mid && r > mid)
    return query(l, r, x << 1) + query(l, r, x << 1 | 1);
  else if (l <= mid)
    return query(l, r, x << 1);
  else
    return query(l, r, x << 1 | 1);
}
```

时间复杂度 $O(n+m\log n)$。

---

