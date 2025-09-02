# Editor

## 题目描述

The development of a text editor is a hard problem. You need to implement an extra module for brackets coloring in text.

Your editor consists of a line with infinite length and cursor, which points to the current character. Please note that it points to only one of the characters (and not between a pair of characters). Thus, it points to an index character. The user can move the cursor left or right one position. If the cursor is already at the first (leftmost) position, then it does not move left.

Initially, the cursor is in the first (leftmost) character.

Also, the user can write a letter or brackets (either (, or )) to the position that the cursor is currently pointing at. A new character always overwrites the old value at that position.

Your editor must check, whether the current line is the correct text. Text is correct if the brackets in them form the correct bracket sequence.

Formally, correct text (CT) must satisfy the following rules:

- any line without brackets is CT (the line can contain whitespaces);
- If the first character of the string — is (, the last — is ), and all the rest form a CT, then the whole line is a CT;
- two consecutively written CT is also CT.

Examples of correct texts: hello(codeforces), round, ((i)(write))edi(tor)s, ( me). Examples of incorrect texts: hello)oops(, round), ((me).

The user uses special commands to work with your editor. Each command has its symbol, which must be written to execute this command.

The correspondence of commands and characters is as follows:

- L — move the cursor one character to the left (remains in place if it already points to the first character);
- R — move the cursor one character to the right;
- any lowercase Latin letter or bracket (( or )) — write the entered character to the position where the cursor is now.

For a complete understanding, take a look at the first example and its illustrations in the note below.

You are given a string containing the characters that the user entered. For the brackets coloring module's work, after each command you need to:

- check if the current text in the editor is a correct text;
- if it is, print the least number of colors that required, to color all brackets.

If two pairs of brackets are nested (the first in the second or vice versa), then these pairs of brackets should be painted in different colors. If two pairs of brackets are not nested, then they can be painted in different or the same colors. For example, for the bracket sequence ()(())()() the least number of colors is $ 2 $ , and for the bracket sequence (()(()())())(()) — is $ 3 $ .

Write a program that prints the minimal number of colors after processing each command.

## 说明/提示

In the first example, the text in the editor will take the following form:

1. ```
  <pre class="verbatim">(<br></br>^
  ```
2. ```
  <pre class="verbatim">(<br></br> ^
  ```
3. ```
  <pre class="verbatim">(a<br></br> ^
  ```
4. ```
  <pre class="verbatim">(a<br></br>  ^
  ```
5. ```
  <pre class="verbatim">(ab<br></br>  ^
  ```
6. ```
  <pre class="verbatim">(ab<br></br>   ^
  ```
7. ```
  <pre class="verbatim">(ab)<br></br>   ^
  ```
8. ```
  <pre class="verbatim">(ab)<br></br>  ^
  ```
9. ```
  <pre class="verbatim">(a))<br></br>  ^
  ```
10. ```
  <pre class="verbatim">(a))<br></br> ^
  ```
11. ```
  <pre class="verbatim">(())<br></br> ^
  ```

## 样例 #1

### 输入

```
11
(RaRbR)L)L(
```

### 输出

```
-1 -1 -1 -1 -1 -1 1 1 -1 -1 2 ```

## 样例 #2

### 输入

```
11
(R)R(R)Ra)c
```

### 输出

```
-1 -1 1 1 -1 -1 1 1 1 -1 1 ```

# 题解

## 作者：reyik (赞：9)

建议紫题左右（可能比紫题简单吧）

这题其实很好考虑

考虑对于一个字符的贡献

如果字符为   $($   那么记它的贡献为$1$

如果字符为 $)$ 那么记它的贡献为$-1$

否则记他的贡献为$0$

瞎想以下，发现

如果整个序列的和不为$0$或者这个序列的前缀和的最小值$<0$，那么就不是括号序列

否则答案就是这个序列的前缀和的最大值

然后就线段树维护，没了

```cpp
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int maxn[4000005],minn[4000005],sum[4000005];
int n,pos=1;
char ch[1000005];
void pushup(int x) {
        sum[x]=sum[x<<1]+sum[x<<1|1];
        minn[x]=min(minn[x<<1],minn[x<<1|1]+sum[x<<1]);
        maxn[x]=max(maxn[x<<1],maxn[x<<1|1]+sum[x<<1]);
}
void modify(int x,int l,int r,int y,int z) {
        if(l==r && l==y) {
                sum[x]=minn[x]=maxn[x]=z;
                return ;
        }
        int mid=(l+r)>>1;
        if(y<=mid) modify(x<<1,l,mid,y,z);
        else modify(x<<1|1,mid+1,r,y,z);
        pushup(x);
}
int main() {
        scanf("%d",&n);
        scanf("%s",ch+1);
        for (int i=1;i<=n;++i) {
                if(ch[i]=='R') ++pos;
                else if(ch[i]=='L') {if(pos>1) --pos;}
                else {
                        if(ch[i]=='(') modify(1,1,n,pos,1);
                        else if(ch[i]==')') modify(1,1,n,pos,-1);
                        else modify(1,1,n,pos,0);
                }
                if(sum[1]!=0 || minn[1]<0) printf("-1 ");
                else printf("%d ",maxn[1]);
        }
        cout<<endl;
        return 0;
}


```

---

## 作者：COsm0s (赞：3)

经典括号问题。

对于一个括号串，我们有一条基本规则：

**对于任意前缀，左括号数 $\geq$ 右括号数，且两括号总数相等。**

满足此条件，即可称此括号串为合法括号串。

在本题中，我们不妨设左括号为 $1$，右括号为 $-1$，普通字符为 $0$。这样的话，刚才的判断条件就转化成了如下式子。

$$
	\begin{cases}
         \forall sum_i,sum_i \geq0\\
         sum_n=0
     \end{cases}
     
$$

其中 $sum_i$ 表示前缀和数组。

然后再来观察这样的定义下“最深嵌套”是什么。

从左往右每出现一个左括号就会使嵌套层数增加，而每出现一个右括号就会使嵌套层数减少，因此最深嵌套层数就是最大的前缀和。

线段树维护区间和，区间 $\min/\max$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define REP(i, l, r) for(int i = (l); i <= (r); i ++)
const int N = 1e6 + 5;
int maxn[N << 2], minn[N << 2], sum[N << 2];
int n, pos = 1;
char ch[N];
void pushup(int x) {
	sum[x] = sum[x << 1] + sum[x << 1 | 1];
	minn[x] = min(minn[x << 1], minn[x << 1 | 1] + sum[x << 1]);
	maxn[x] = max(maxn[x << 1], maxn[x << 1 | 1] + sum[x << 1]);
}
void Update(int x, int l, int r, int y, int z) {
	if (l == r && l == y) {
		sum[x] = minn[x] = maxn[x] = z;
		return ;
	}
	int mid = (l + r) >> 1;
	if (y <= mid) Update(x << 1, l, mid, y, z);
	else Update(x << 1 | 1, mid + 1, r, y, z);
	pushup(x);
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> (ch + 1);
	REP(i, 1, n) {
		if (ch[i] == 'R') ++ pos;
		else if (ch[i] == 'L')
			pos -= (pos > 1);
		else {
			if (ch[i] == '(') Update(1, 1, n, pos, 1);
			else if (ch[i] == ')') Update(1, 1, n, pos, -1);
			else Update(1, 1, n, pos, 0);
		}
		if (sum[1] != 0 || minn[1] < 0) cout << "-1 ";
		else cout << maxn[1] << ' ';
	}
	return 0;
}
```

---

## 作者：luogu_gza (赞：1)

根据经典套路，我们定义左括号权值为 $1$，右括号权值为 $-1$，普通字符权值为 $0$。

一个括号序列合法，当且仅当全序列和为 $0$，没有一个前缀的和小于 $0$。

我们维护整个序列的前缀和数组，即需要支持区间加，全局 $\max$，全局 $\min$ 的线段树。

[record](https://codeforces.com/contest/1263/submission/247890998)

---

## 作者：囧仙 (赞：1)

## 题目大意

$n$ 次操作，每次修改一个字符。询问每次操作后嵌套层数最多的括号有多少层。如果这个括号序列不合法，输出 $-1$ 。

## 题解

括号问题，一般需要给括号加上权值，然后统计前缀和。我们不妨将左括号赋值为 $1$ ，右括号赋值为 $-1$ 。显然，如果这个括号序列合法，必定满足：

- 所有括号的权值和为 $0$ 。（即左右括号数量相等）。

- **不存在一个位置，它的前缀和是负数**。（否则某个位置左侧的右括号多余左括号，显然不合法）。

若括号序列合法，那么括号嵌套的最多次数就是前缀和的最大值。

这点比较显然。设某个点的前缀和为 $x$ ，那么就说明它左侧的左括号比右括号多 $x$ 个，也即这个点在第 $x$ 层里。

想到这里，就可以直接用线段树维护前缀和最大值、前缀和最小值了。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;++i)
#define dn(r,l,i) for(int i=r;i>=l;--i)
using namespace std ;
int qread(){
	int w=1,c,r=0;
	for(c=getchar();!isdigit(c);c=getchar())
	if(c=='-') w=-1; else w=1; r=c-'0';
	for(c=getchar(); isdigit(c);c=getchar())
	r=r*10+c-'0';
	return r*w;
}
const int MAXN =1e6+3,MAXM=1e6+3,SIZ=4e6+3;
#define lc(o) (o<<1)
#define rc(o) (o<<1|1)
int M[SIZ],N[SIZ],T[SIZ],n;
void upd(int o,int a,int b){
	if(!T[o]) return; int d=T[o];
	M[lc(o)]+=d,M[rc(o)]+=d,T[lc(o)]+=d;
	N[lc(o)]+=d,N[rc(o)]+=d,T[rc(o)]+=d;
	T[o]=0;
}
void cng(int o,int l,int r,int k,int a,int b){
	int c=(a+b)>>1;
	if(l<=a&&b<=r){
		M[o]+=k,N[o]+=k,T[o]+=k;
		return ;
	}
	upd(o,a,b);
	if(l<=c) cng(lc(o),l,r,k,a,c);
	if(r> c) cng(rc(o),l,r,k,c+1,b);
	M[o]=max(M[lc(o)],M[rc(o)]);
	N[o]=min(N[lc(o)],N[rc(o)]);
}
void get(int o,int l,int r,int a,int b,int &p,int &q){
	int c=(a+b)>>1;
	if(l<=a&&b<=r){
		p=max(p,M[o]),q=min(q,N[o]);
		return ;
	}
	upd(o,a,b);
	if(l<=c) get(lc(o),l,r,a,c,p,q);
	if(r> c) get(rc(o),l,r,c+1,b,p,q);
}
int w=1,A[MAXN],s;
int main(){
	n=qread(); up(1,n,i){
		int op=getchar();
		if(op=='L') --w; else if(op=='R') ++w; else{
			if(A[w]=='(') cng(1,w,n,-1,1,n),--s; else
			if(A[w]==')') cng(1,w,n, 1,1,n),++s;
			if(op=='(') cng(1,w,n, 1,1,n),++s; else
			if(op==')') cng(1,w,n,-1,1,n),--s;
			A[w]=op;
		}
		if(w<1) ++w;
		int a=-1e9,b=1e9,t; get(1,1,n,1,n,a,b);
		if(s!=0||b<0) printf("%d ",-1); else printf("%d ",a);
	}
	return 0;
} 
```

---

## 作者：H2O_TX (赞：0)

首先要考虑如何判定是否合法。
合法要满足两个条件：

1. 左括号和右括号总数相等。
2. 任意一段前缀中左括号的数量不少于右括号。

所以想到给左括号赋值 $1$，右括号赋值 $-1$，这样当总和为 $0$ 时就满足条件 $1$ 了。

要满足条件 $2$，需要最小的前缀和大于等于 $0$。

然后再来考虑这样的定义下最深嵌套是什么。

从左往右每出现一个左括号就会使嵌套层数增加，而每出现一个右括号就会使嵌套层数减少，因此最深嵌套层数就是最大的前缀和。

看看我们需要维护什么：

- 一段总和

- 一段前缀和的最大最小值

很明显直接写线段树就可以了。

贴代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6+10;
int n;
char a[N];
struct sgt
{
    int l,r,qzmin,qzmax,sum;
}tr[N*4];

void build(int p,int l,int r)//建树
{
    tr[p].l=l,tr[p].r=r;
    if(l==r) return;
    int mid=l+r>>1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
}

void update(int p)//线段树从下向上更新
{
    tr[p].sum=tr[p*2].sum+tr[p*2+1].sum;
    tr[p].qzmin=min(tr[p*2].qzmin,tr[p*2].sum+tr[p*2+1].qzmin);
    tr[p].qzmax=max(tr[p*2].qzmax,tr[p*2].sum+tr[p*2+1].qzmax);
}

void change(int p,int x,int k)//单点修改
{
    if(tr[p].l==tr[p].r&&tr[p].l==x)
    {
        tr[p].qzmax=tr[p].qzmin=tr[p].sum=k;
        return;
    }
    int mid=tr[p].l+tr[p].r>>1;
    if(x<=mid) change(p*2,x,k);
    else change(p*2+1,x,k);
    update(p);
}

int main()
{
    cin>>n;
    cin>>a+1;
    int pos=1;//表示现在光标位置
    build(1,1,n);
    for(int i=1;i<=n;i++)
    {
        if(a[i]=='R') pos++;
        else if(a[i]=='L')
        {
            if(pos>1) pos--;
        }//注意这里要打括号，否则下面的 else if 会跟着里面这个 if
        else if(a[i]=='(') change(1,pos,1);
        else if(a[i]==')') change(1,pos,-1);
        else change(1,pos,0);
        if(tr[1].qzmin<0||tr[1].sum!=0) cout<<-1<<" ";
        else cout<<tr[1].qzmax<<" ";
    }
    return 0;
}

```


---

## 作者：peterwuyihong (赞：0)

vp 被打爆了！！！/ll

题意：您要设计一个只有一行的打字机，这一行的长度是无限大，一开始可以认为每个字符都是空，您的打字机有一个光标只指向一个字符，一开始指向最左侧的字符，你可以输入 L 让光标向左动一下，已经最左即忽略，也可以输入 R 让光标向右动一下，也可以输入一个字符把光标处改成这个字符，你需要动态的维护出这个序列是否是合法括号序列，并输出它的最大括号匹配数。

总结一下 Bracket 题套路。

把左括号看成 $1$，右括号看成 $-1$，其他看成 $0$，然后做前缀和。一个括号序列合法的充要条件是前缀前缀和非负，以及末尾前缀和为 $0$。

然后用线段树维护即可，可能有一点细节。

现在是 $8:12$，我看我什么时候写完。

```cpp
#define maxn 500010
int n,pos;
char s[maxn*2];
struct prpr{
  int l,r;
  int mn,mx,tg;
}tree[maxn<<2];
void pushup(int x){
  tree[x].mn=min(tree[x<<1].mn,tree[x<<1|1].mn);
  tree[x].mx=max(tree[x<<1].mx,tree[x<<1|1].mx);
}
void pushdown(int x){
  if(tree[x].tg){
    tree[x<<1].tg+=tree[x].tg;
    tree[x<<1|1].tg+=tree[x].tg;
    tree[x<<1].mx+=tree[x].tg;
    tree[x<<1|1].mx+=tree[x].tg;
    tree[x<<1].mn+=tree[x].tg;
    tree[x<<1|1].mn+=tree[x].tg;
    tree[x].tg=0;
  }
}
void build(int l,int r,int x=1){
  tree[x].l=l,tree[x].r=r;
  tree[x].mx=0;
  tree[x].mn=0;
  tree[x].tg=0;
  if(l==r)return;
  int mid=(l+r)>>1;
  build(l,mid,x<<1);
  build(mid+1,r,x<<1|1);
}
int askmx(int l,int r,int x=1){
  if(tree[x].l>=l&&tree[x].r<=r)return tree[x].mx;
  pushdown(x);
  int mid=(tree[x].l+tree[x].r)>>1,ans=0xcfcfcfcf;
  if(l<=mid)ans=max(ans,askmx(l,r,x<<1));
  if(r>mid)ans=max(ans,askmx(l,r,x<<1|1));
  return ans;
}
int askmn(int l,int r,int x=1){
  if(tree[x].l>=l&&tree[x].r<=r)return tree[x].mn;
  pushdown(x);
  int mid=(tree[x].l+tree[x].r)>>1,ans=0x3f3f3f3f;
  if(l<=mid)ans=min(ans,askmn(l,r,x<<1));
  if(r>mid)ans=min(ans,askmn(l,r,x<<1|1));
  return ans;
}
void change(int l,int r,int d,int x=1){
  if(tree[x].l>=l&&tree[x].r<=r){
    tree[x].mn+=d;
    tree[x].mx+=d;
    tree[x].tg+=d;
    return;
  }
  pushdown(x);
  int mid=(tree[x].l+tree[x].r)>>1;
  if(l<=mid)change(l,r,d,x<<1);
  if(r>mid)change(l,r,d,x<<1|1);
  pushup(x);
}
char G[maxn];
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
  cin>>n>>s+1;
  pos=1;
  build(1,(n+1)/2);
  rep(i,1,n){
    if(s[i]=='L')pos=max(1,pos-1);
    else if(s[i]=='R')pos++;
    else{
      int from,to;
      if(G[pos]=='(')from=1;
      else if(G[pos]==')')from=-1;
      else from=0;
      G[pos]=s[i];
      if(G[pos]=='(')to=1;
      else if(G[pos]==')')to=-1;
      else to=0;
      change(pos,(n+1)/2,to-from);
    }
    if(askmn(1,(n+1)/2)<0||askmn((n+1)/2,(n+1)/2))cout<<-1<<' ';
    else cout<<askmx(1,(n+1)/2)<<' ';
//    rep(j,1,(n+1)/2)cout<<askmn(j,j)<<' ';cout<<endl;
  }
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
哟，原来没有细节啊。

---

