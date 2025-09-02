# Cats on the Upgrade (easy version)

## 题目描述

This is the easy version of the problem. The only difference between the easy and the hard versions are removal queries, they are present only in the hard version.

"Interplanetary Software, Inc." together with "Robots of Cydonia, Ltd." has developed and released robot cats. These electronic pets can meow, catch mice and entertain the owner in various ways.

The developers from "Interplanetary Software, Inc." have recently decided to release a software update for these robots. After the update, the cats must solve the problems about bracket sequences. One of the problems is described below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1625E1/ad865cfdf37d1aee9e7ac138cc3da0f92a8cbe90.png)First, we need to learn a bit of bracket sequence theory. Consider the strings that contain characters "(", ")" and ".". Call a string regular bracket sequence (RBS), if it can be transformed to an empty string by one or more operations of removing either single "." characters, or a continuous substring "()". For instance, the string "(()(.))" is an RBS, as it can be transformed to an empty string with the following sequence of removals:

 "(()(.))" $ \rightarrow $ "(()())" $ \rightarrow $ "(())" $ \rightarrow $ "()" $ \rightarrow $ "". We got an empty string, so the initial string was an RBS. At the same time, the string ")(" is not an RBS, as it is not possible to apply such removal operations to it.

An RBS is simple if this RBS is not empty, doesn't start with ".", and doesn't end with ".".

Denote the substring of the string $ s $ as its sequential subsegment. In particular, $ s[l\dots r] = s_ls_{l+1}\dots s_r $ , where $ s_i $ is the $ i $ -th character of the string $ s $ .

Now, move on to the problem statement itself. You are given a string $ s $ , initially consisting of characters "(" and ")". You need to answer the queries of the following kind.

Given two indices, $ l $ and $ r $ ( $ 1 \le l < r \le n $ ), and it's guaranteed that the substring $ s[l\dots r] $ is a simple RBS. You need to find the number of substrings in $ s[l\dots r] $ such that they are simple RBS. In other words, find the number of index pairs $ i $ , $ j $ such that $ l \le i < j \le r $ and $ s[i\dots j] $ is a simple RBS.

You are an employee in "Interplanetary Software, Inc." and you were given the task to teach the cats to solve the problem above, after the update.

Note that the "." character cannot appear in the string in this version of the problem. It is only needed for the hard version.

## 说明/提示

Consider the example test case.

The answer to the first query is $ 3 $ , as there are three suitable substrings: $ s[3\dots6] $ , $ s[3\dots4] $ and $ s[5\dots6] $ .

The answer to the second query is $ 4 $ . The substrings are $ s[3\dots6] $ , $ s[3\dots4] $ , $ s[5\dots6] $ and $ s[2\dots7] $ .

The answer to the third query is $ 1 $ . The substring is $ s[8\dots9] $ .

The answer to the fourth query is $ 6 $ . The substrings are $ s[3\dots6] $ , $ s[3\dots4] $ , $ s[5\dots6] $ , $ s[2\dots7] $ , $ s[8\dots9] $ and $ s[2\dots9] $ .

## 样例 #1

### 输入

```
9 4
)(()())()
2 3 6
2 2 7
2 8 9
2 2 9```

### 输出

```
3
4
1
6```

# 题解

## 作者：DaiRuiChen007 (赞：13)

# CF1625E1 - Cats on the Upgrade (easy version) 题解

## 题目大意

给定一个长度为 $n$ 的括号序列 $S$。

共有 $q$ 次询问，每次询问 $S$ 从 $l$ 到 $r$ 的字串 $T$ 的字串中中含有多少个合法括号序列，保证每个 $T$ 一定是合法的括号序列。

数据范围保证：$n,q\le3\times 10^5$。

## 思路分析

首先考虑 $S$ 本身就是一个合法括号序列的情况：

约定 $s[i]$ 是左括号时 $g[i]=0$，否则 $g[i]=1$，$ans(l,r)$ 表示查询从 $l$ 到 $r$ 的字串 $T$ 的字串中中含有多少个合法括号序列的答案。

注意到特殊性质 $T$ 一定是合法括号序列，所以只需要分析 $T$ 内部的合法括号子序列。

考虑对 $S$ 里的括号对进行分层，用 $d[i]$ 表示右括号在 $i$ 位置上的括号对嵌套了几个括号，这可以在用栈匹配的时候完成。

- $g[i]=0$ 时 $d[i]=0$。
- $g[i]=1$ 时 $d[i]=$对应左括号出栈后栈的大小。

所以我们可以把整个括号序列转成一棵树，一对括号对应一个节点，每对括号内部嵌套的就是其子节点，形成一个森林后，新建一个虚拟根节点转成树。

用 $f[i]$ 表示每个节点的兄弟节点中有多少个在其之前出现，显然这也可以在栈维护的时候顺便完成：
- $g[i]=0$ 时 $f[i]=0$。
- $g[i]=1$ 时 $f[i]=$对应左括号出栈前一位的 $f$ 值 $+1$。

以序列"（（（  ）（  ）（  ））（  ））（（  ））"为例，我们把这棵树建出来看一看（节点上的编号是右括号的位置，root是虚拟根节点）。

![](https://cdn.luogu.com.cn/upload/image_hosting/xbut7jsk.png)

此时树中的没一个节点都代表了一个合法括号序列。

然后再把对应的 $f$ 值写出来：

| i     | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    | 10   | 11   | 12   | 13   | 14   | 15   | 16   |
| ----- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| $f[i]=$ | 0    | 0    | 0    | 1    | 0    | 2    | 0    | 3    | 1    | 0    | 2    | 1    | 0    | 0    | 1    | 2    |

然后我们来看一看这和合法括号序列对数的关系，来造几组样例测试一下！
$$
\begin{cases}
ans(3,8)=6=\sum_{i=3}^8f[i]\\
ans(1,12)=10=\sum_{i=1}^{12}f[i]\\
ans(1,16)=13=\sum_{i=1}^{16}f[i]
\end{cases}
$$
好像发现了一些规律，大胆猜想一下 $ans(l,r)=\sum_{i=l}^rf[i]$

让我们来尝试证明一下这个结论：

考虑第一组样例：查询 $3\sim8$ 的答案时，考虑三个括号 $(3\sim4,5\sim6,7\sim8)$ 选还是不选，发现既不能一个都不选，也不能选分开的几个括号，所以满足条件的答案是 $\operatorname{C}_{3}^{2}+3$ 的值，相当于考虑左右端点不相同的加上左右端点相同的。

又注意到 $f[4]=1,f[6]=2,f[8]=3$

所以 $\sum_{i=3}^8f[i]=f[4]+f[6]+f[8]=1+2+3=\dfrac{2\times3}{2}+3=\operatorname{C}_{3}^{2}+3$ 并不是一个巧合。

考虑第二组样例：查询 $1\sim12$ 的答案，这好像和第一组样例没什么不同，不过是出现了括号嵌套的现象，但是同层之间的括号匹配时对更高层的括号匹配并没有关系，例如：对于合法括号序列 $2\sim9$ 和合法括号序列 $10\sim11$ 的匹配时，$2\sim9$ 内部是一定全部选上的，所以统计的 $ans(2,9)$ 对于这里并没有贡献，同理 $2\sim9$ 内部的匹配也和 $10\sim11$ 没有任何关系，所以不同层之间的合法括号序列是互不影响的（更准确的说，是某一些父节点相同的同层节点之间互不影响），所以这也是对的。

第三组样例同理，因为 root 节点没有 $f$ 值，所以没有影响，正确性同二。

所以这个结论貌似是对的！ 

然而。。。再来一组样例：

$ans(5,8)=3\ne5=\sum_{i=5}^8f[i]$

所以这个结论是错误的~~但也不完全错误~~，我们来找一下 $ans(5,8)$ 和 $ans(3,8)$ 之间的区别。

发现他们之间的区别是 $ans(3,8)$ 统计的是某一层同父亲的**所有**兄弟节点，而 $ans(5,8)$ 并不是，这个时候的答案应该是 $1+2=3$ 而不是 $2+3=5$ 所以要进行去重，$ans(5,8)$ 统计的起点应该是 $1$，而不是 $2$ 这意味着每个数都少了 $1$，所以这种情况要减去 $f[l-1]\times(f[r]-f[l-1])$。

所以我们得到了最终的答案：
$$
ans(l,r)=\sum_{i=l}^rf[i]-f[l-1]\times(f[r]-f[l-1])
$$


然后这个式子就是对的了，因为第一种情况个 $g[l-1]=0$ 也就是前面是一个左括号，$f[l-1]=0$ 对 $ans(l,r)$ 没有影响。

发现前面求和的操作可以用前缀和优化在 $\Theta(1)$ 的时间复杂度内计算。

所以总的时间复杂度是 $\Theta(n)$ 预处理，$\Theta(1)$ 回答。

然后考虑对于 $S$ 不是合法括号序列的情况，可以证明，这种情况下没有被匹配的字符一定不在 $T$ 的选择范围之内，所以直接忽略掉这些字符，正常做就可以了

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=3e5+1;
int f[MAXN],s[MAXN];
stack <int> st; //用来匹配的括号栈 
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int n,q;
	cin>>n>>q;
	for(register int i=1;i<=n;++i) {
		char ch;
		cin>>ch;
		switch(ch) {
			case '(': {
				st.push(i);
				break;
			}
			case ')': {
				if(!st.empty()) {
					f[i]=f[st.top()-1]+1;
					st.pop();
				}
				break;
			}
		}
		s[i]=s[i-1]+f[i];
	}
	while(q--) {
		int d,l,r;
		cin>>d>>l>>r;
		cout<<s[r]-s[l-1]-f[l-1]*(f[r]-f[l-1])<<'\n';
		//式子的含义题解里已经说得很清楚了 
	}
	return 0;
}
```

---

## 作者：double_zero (赞：3)

刚刚学完 whk 时无聊看了下提交记录，发现这道富有启发意义的题目。

首先，注意到这实际上就是个序列的 《括号树》，拿来做就行，$f_i$ 为以 $i$ 结尾的合法括号串数量，$f_i=f_{L_i-1}+1$，然后再做一遍前缀和，相减求出以区间 $[x,y]$ 为结尾的数量，但是我们发现会算重，具体的，算重了 $[1,x-1]$ 取后缀，$[x,y]$ 取前缀所组合成的合法串数量。

目前题目还有一个性质没用到，就是保证每次询问 $[x,y]$ 合法。那么，显然一定是以 $x-1$ 为右端点的合法括号序列与以 $x$ 为左端点的合法括号序列的组合。因为不可能出现一个合法的由这 $2$ 个不合法的组成。若有，显然存在一个 $p\in [x,y]$ 为右括号，需要匹配 $q\in [1,x-1]$，那么 $[x,y]$ 不合法。

首先 $f_{x-1}$ 即后缀合法括号序列，那么还要有 $[x,y]$ 的前缀合法然后相乘才对，于是我们期望找到一个能表示 $[x,y]$ 的前缀合法括号序列。

考虑对于每个前缀合法括号序列，一定是 $[x,p]$，那么因为 $[x,y]$ 合法，显然 $[p+1,y]$ 也合法。

于是，每个前缀合法括号序列都存在唯一一个以 $y$ 为结尾，开头在 $[x,y]$ 的合法括号序列与之对应。（双射）

于是，我们现在期望通过 $f$ 求后者。

发现倘若以 $y$ 为右端点，但左端点在 $[1,x-1]$ 的合法括号序列，它一定可以划分为 $s:[p,x-1]+[x,y]$。否则，若左端点在 $[x,y]$ 则一定无法划分，即不会计入 $f_{x-1}$，但 $2$ 部分都会计入 $f_y$。

综上，减去 $f_{x-1}\cdot(f_y-f_{x-1})$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int rd() {
	int f=1,sum=0; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)) {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum*f;
}
const int N=(int)(3e5+5);
char s[N];
int n,m,f[N],st[N],sum[N],top;
signed main() {
	n=rd(); m=rd(); scanf("%s",s+1);
	for(int i=1;i<=n;i++) {
		if(s[i]=='(') st[++top]=i;
		else {
			if(!top) continue ;
			f[i]=f[st[top]-1]+1; --top;
		}
	}
	for(int i=1;i<=n;i++) {
		sum[i]=sum[i-1]+f[i];
//		printf("%d ",f[i]);
	}
	while(m--) {
		rd(); int x=rd(),y=rd();
		printf("%lld\n",sum[y]-sum[x-1]-f[x-1]*(f[y]-f[x-1]));
		// [1,x-1]*[x,y] ,[x,y]=[y,x]
	}
	return 0;
}
```

---

## 作者：LinkyChristian (赞：2)

~~在打模拟赛的时候写题解好刺激啊~~

首先考虑不包含嵌套关系的括号序列选取，那这个问题就变成了从一个序列中选取一个非空子段的方案数，为 ${ n+1 \choose 2 }$ 种。

考虑有嵌套关系的括号序列，同层（即互相没有嵌套关系）的括号按照上面所说的方式选取。若选取一个括号，则被这个括号包含的一整段括号序列必须全部选取，因此不同层的括号之间不互相影响，可以分开考虑。

考虑如何统计每一层的贡献。用栈匹配括号，观察到一个右括号对应的左括号，这个左括号的左边要么是右括号，即为同层括号，要么是左括号，即为包含自己的括号。因此我们在右括号的位置上记 $f_i$ 表示同层的括号中，以这个括号为右端点，能选取几段非空子段。设 $i$ 位置的右括号对应的左括号的位置为 $l_i$ ，则 $f_i=f_{l_i-1}+1$。选取这一层括号的总贡献即为这一层括号的 $f_i$ 之和。

考虑询问。询问的区间是一段合法括号，因此直接统计 $f_i$ 之和即可。询问区间的 $f_i$ 之和可以很简单地用前缀和求出来，这里注意一点由于询问区间内的不一定是同层的所有括号，因此要减去 $f_{l-1} \times (r-l+1)$ 。至此题目圆满完成。



---

## 作者：Purslane (赞：1)

# Solution

不需要脑子的做法。

注意到一个匹配括号串是若干个“最简匹配括号串”合并得到的，每个最简匹配括号串形如 `(...)`。

设 $dp_{S}$ 表示最简匹配括号串 $S$，它的所有真子串中匹配括号串的个数。

如何计算它？考虑把 $S$ 拆分成 $'(' + S_1 + S_2 + \dots + S_t + ')'$。那么 $dp_S = \sum_{i=1}^t dp_{S_i} + \dbinom{t}{2}$。

我们对每个点求出他开始的最简匹配括号串的右端点，设为 $l$ 和 $r$，则在 $l \to r+1$ 间连边。

这样的形态变成了树。我们只需要计算树上前缀和即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=3e5+10;
int n,q,cnt[MAXN],pre[MAXN],nxt[MAXN],mn[MAXN][20]; string S;
int pre_len[MAXN],pre_dp[MAXN],dp[MAXN];
int query(int l,int r) {int k=log2(r-l+1);return min(mn[l][k],mn[r-(1<<k)+1][k]);}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q>>S,S="&"+S;
	ffor(i,1,n) pre[i]=pre[i-1]+(S[i]=='('?1:-1),mn[i][0]=pre[i];
	ffor(k,1,19) for(int l=1,r=(1<<k);r<=n;l++,r++) mn[l][k]=min(mn[l][k-1],mn[l+(1<<k-1)][k-1]);
	map<int,int> psl;
	roff(i,n,1) {
		psl[pre[i]]=i;
		if(psl.count(pre[i-1])==0) nxt[i]=-1;
		else if(query(i,psl[pre[i-1]])>=pre[i-1]) nxt[i]=psl[pre[i-1]]+1;
		else nxt[i]=-1;
	}
	roff(i,n,1) {
		if(nxt[i]!=-1) {
			pre_len[i]=pre_len[nxt[i]]+1;
			dp[i]=pre_dp[i+1]+pre_len[i+1]*(pre_len[i+1]+1)/2;
			pre_dp[i]=pre_dp[nxt[i]]+dp[i];
		}
	}
	ffor(i,1,q) {
		int t,l,r;
		cin>>t>>l>>r,cout<<pre_dp[l]-pre_dp[r+1]+(pre_len[l]-pre_len[r+1])*(pre_len[l]-pre_len[r+1]+1)/2<<'\n';	
	}
	return 0;
}
//看远方的星 如果听得见 它一定实现
```

---

## 作者：QQ82272760 (赞：1)

由于太菜了所以只能想到带根号的做法，而且是离线的不支持修改。

按照右端点排序后离线下来。每次加入一个括号时都要看一下是否有配对，如果有的话，就把与它并列的所有左端点都加上 $1$，询问就是查询区间内所有左端点的和。

显然不能真暴力把所有并列的左端点都修改，因此设一个阈值 $B$，每次只暴力修改长度为 $B$ 的块以内的，满一块后再给前面的所有并列的左端点都加上 $B$。询问的时候就要额外加上当前块大小乘上块前面并列的数量。

一个点被修改 $\mathcal O\left(\dfrac nB\right)$ 次，取 $B=\sqrt n$ 就可以做到总修改次数为 $\mathcal O(n\sqrt n)$，采用 $\mathcal O(1)-\mathcal O(\sqrt n)$ 的分块就可以做到总复杂度 $\mathcal O((n+q)\sqrt n)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
const int N=300000,B=550;
int n,q;
char s[N+5];
int a[N+5],b[N/B+5];
int id[N+5],L[N/B+5],R[N/B+5];
int stk[N+5],top,pr[N+5],cnt[N+5];
int lst[N+5],pre[N+5],ad[N+5];
ll ans[N+5];
struct qry{
	int l,r,id;
}p[N+5];
bool operator<(qry x,qry y){
	return x.r<y.r;
}
void init(){
	for(int i=1;i<=n;i+=1){
		id[i]=(i-1)/B+1;
		if(i%B==1) L[id[i]]=i;
		R[id[i]]=i;
	}
	return;
}
void update(int x,int y){
	a[x]+=y; b[id[x]]+=y;
	return;
}
ll sum(int l,int r){
	ll res=0;
	if(id[l]==id[r]){
		for(int i=l;i<=r;i+=1) res+=1ll*a[i];
		return res;
	}
	for(int i=l;i<=R[id[l]];i+=1) res+=1ll*a[i];
	for(int i=L[id[r]];i<=r;i+=1) res+=1ll*a[i];
	for(int i=id[l]+1;i<id[r];i+=1) res+=1ll*b[i];
	return res;
}
void insert(int x){
	if(s[x]=='('){
		stk[++top]=x;
		return;
	}
	if(s[stk[top]]==')'||!top){
		stk[++top]=x;
		return;
	}
	pr[x]=stk[top--];
	pr[pr[x]]=x;
	x=pr[x];
	lst[x]=pr[x-1];
	cnt[x]=cnt[lst[x]]+1;
	if(ad[lst[x]]) pre[x]=x;
	else pre[x]=pre[lst[x]];
	for(int i=x;i;i=lst[i]){
		update(i,1);
		if(pre[i]==i) break;
	}
	if(cnt[x]-cnt[lst[pre[x]]]==B){
		ad[x]=1;
		for(int i=lst[pre[x]];i;i=lst[i]){
			update(i,B);
		}
	}
	if(pr[x]==x+1) return;
	x=pr[pr[x]-1];
	if(!ad[x]){
		int now=cnt[x]-cnt[lst[pre[x]]];
		for(int i=lst[pre[x]];i;i=lst[i]){
			update(i,now);
		}
	}
	return;
}
ll query(int l,int r){
	ll res=sum(l,r);
	if(pr[l]==r) return res;
	if(pre[pr[r]]==pre[l]) return res;
	if(ad[pr[r]]) return res;
	int cnt1=cnt[pr[r]]-cnt[lst[pre[pr[r]]]];
	int cnt2=cnt[lst[pre[pr[r]]]]-cnt[lst[l]];
	res+=1ll*cnt1*cnt2;
	return res;
}
int main(){
	int t,l,r;
	scanf("%d%d",&n,&q); init();
	scanf("%s",s+1);
	for(int i=1;i<=q;i+=1){
		scanf("%d%d%d",&t,&l,&r);
		p[i].l=l; p[i].r=r; p[i].id=i;
	}
	sort(p+1,p+q+1);
	for(int i=1,j=0;i<=n;i+=1){
		insert(i);
		while(p[j+1].r==i){
			l=p[++j].l; r=p[j].r;
			ans[p[j].id]=query(l,r);
		}
	}
	for(int i=1;i<=q;i+=1){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```

Thanks~

---

## 作者：shinkuu (赞：0)

正解+嘴巴做法。

### 正解

括号序列，可以从坐标系上的折线图角度理解。将左括号看作 $+1$，否则 $-1$。记前缀和为 $s$，以此画折线图。

首先一个可行区间的左右端点在折线图上纵坐标相同。并且要求该区间内折线所在的纵坐标的 $\min$ 在左右端点处取到，即 $\min_{i\in [l,r]}s_i=s_l=s_r$。

可能同时有三个或以上的点互相满足这个条件，将这些点记录为一个集合。发现一个大小为 $k$ 的集合内每个位置，以它为结尾的合法括号序列个数为 $1,2,\cdots,k-1,k$。记以 $i$ 结尾合法区间有 $f_i$ 个，这个东西也可以用经典的栈匹配 $f_i=f_{lst}+1$ 求出来。所以给答案加上 $\sum_{i\in[l,r]}f_i$。

但是有可能出现的情况是这个集合内有一些数不在询问区间内。考虑减去多余贡献。~~一定要看好题，这种集合只会有一个因为 $[l,r]$ 是合法括号序列~~。举个例子，原本每个数贡献分别为 $1,2,3,4,5$，现在只有 $3,4,5$ 有贡献，发现就是减去了 $2\times(5-2)$。所以答案即为 $\sum_{i\in[l,r]}f_i-f_{i-1}\times(f_r-f_{l-1})$。

code：

```cpp
int n,m,top,st[N],f[N];ll g[N];
char s[N];
void Yorushika(){
	scanf("%d%d%s",&n,&m,s+1);
	rep(i,1,n){
		if(s[i]=='(')st[++top]=i;
		else if(s[st[top]]=='(')f[i]=f[st[top--]-1]+1;
		else st[++top]=i;
		g[i]=g[i-1]+f[i];
	}
	while(m--){
		int op,l,r;scanf("%d%d%d",&op,&l,&r);
		printf("%lld\n",g[r]-g[l-1]-1ll*f[l-1]*(f[r]-f[l-1]));
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

### 嘴巴1

还是求出上面的集合，~~但是不保证 $[l,r]$ 是合法括号串~~。设集合中的数分别为 $S_1,S_2,S_3,\cdots,S_k$。则每个 $S_i,S_j(j>i)$ 都会对答案有 $1$ 的贡献，变成二维偏序问题。

但是这样可能变成 $O(n^2)$ 的，考虑将 $|S|>\sqrt n$ 的拉出来，每次查询 $O(\sqrt n\log n)$ 对于每个集合二分出有多少个在查询区间内，直接加上贡献。其他正常二维偏序，BIT 维护。$O(n\sqrt n\log n)$。

欸，前面那个是不是可以预处理每个位置对于每个集合的前驱后继。

看题解，后面那个可以 $O(1)-O(\sqrt n)$ 分块维护。

那就是 $O(n\sqrt n)$ 的了。

### 嘴巴2

发现我们 cf 有 divide and conquer 标签。考虑分治，从分治中心往两边记录合法的，在折线图上纵坐标为 $y$ 的位置数量，好像是可以做的？看有没有人实现……

---

