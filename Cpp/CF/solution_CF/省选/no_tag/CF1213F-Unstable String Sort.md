# Unstable String Sort

## 题目描述

作者构造了一个由 $n$ 个小写拉丁字母组成的字符串 $s$。

你得到了它的两个下标排列（不一定相同）$p$ 和 $q$（长度均为 $n$）。排列是长度为 $n$ 的数组，包含 $1$ 到 $n$ 的每个整数恰好一次。

对于所有 $i$ 从 $1$ 到 $n-1$，都有：$s[p_i] \le s[p_{i + 1}]$ 且 $s[q_i] \le s[q_{i + 1}]$。也就是说，如果你按照排列下标的顺序写出 $s$ 的所有字符，得到的字符串是非递减排序的。

你的任务是还原出任意一个满足上述条件、长度为 $n$、且包含至少 $k$ 个不同小写拉丁字母的字符串 $s$。

如果有多种答案，你可以输出任意一种。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 2
1 2 3
1 3 2
```

### 输出

```
YES
abb
```

# 题解

## 作者：L______ (赞：11)

这道题是听wqy大佬讲课的时候讲的，最开始一眼缩点就过了，然后又听wqy大佬讲了排序的方法，没怎么注意（~~逃~~），后来又看才发现自己yy的缩点好像有问题（~~我太菜了~~），然后按照大佬讲的排序调了一会儿发现好像思路也不对（上课一定要听讲），然后只能一个人埋着头yy其他思路。

功夫不负有心人，最终在大佬@[ღ觊觎微凉月](https://www.luogu.org/space/show?uid=164319)的指引下yy出了一种极其奇怪的并查集做法，特来分享。

我们考虑对于给出的两个序列a和b，对于a中当前出现的这个数，那么在b中按照顺序至少要到b中这个数出现的位置，才是相同的元素，也就是一个集合。（好像有点抽象，因为我语文不好，给出一张图方便理解）

![](https://cdn.luogu.com.cn/upload/image_hosting/ahtdcspu.png)

例如给定的这个数据，我们可以很显然看到最终的结果里2 1 4是一个集合，也就是一个数，而3是单独的一个集合。

那么我们是如何得到这个结果的呢？首先，在a数组中指针指向1位置，也就是2，b数组中指针指向1位置，也就是4.我们发现目前2和4不在同一个集合内，那么说明当前单独一个位置不能构成上下两个集合相同的情况。那么我们在a数组中将集合向后扩展，也就是2和1合并，接着此时判断4是否在上一个集合内，还是不在，那么就接着向后合并也就是2 1 4所在一个集合，这时判断4在上面的集合中，b数组指针后移，判断2也在集合中，指针后移，接着判断1在集合中，此时我们可以看到，当两个指针在两个数组里所指位置相同时，在这个数据中也就是都是3时，在a数组中的2 1 4这一块也就和b数组中的4 2 1这一块正好完全相同，所以他们至少都要是同一个元素。

最后只要考虑对于答案的构造就好了，题目中给定了k个不同字母，那么只要集合个数大于等于k就是满足的，小于k就是不满足的。当集合个数大于k的时候，对于后面的集合只要全部和前面的元素构造成一样的就好了，比如还是2 1 4 3这个数据，可以构造成aaab，当k==1时也完全可以构造为aaaa。

（~~突然发现以上步骤全部可以用一个标记数组book完成，但是并查集方便理解同在一个集合，就不改了~~）

Code
```
#include<cstdio>
#include<cstring>
#include<algorithm>
#define ll long long
#define N 200010
using namespace std;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,k,a[N],b[N],fa[N],pos[N],cnt=0;
char ch[N];

int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

int main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();
	int top1=1,top2=1;
	while(1){
		if(top1>n || top2>n) break;
		int fx=find(a[top1]),fy=find(b[top2]);
		if(fx==fy){
			if(top1==top2){
				pos[++cnt]=top1;
				top1++,top2++;
			}
			else top2++;
		}
		else fa[find(a[top1])]=find(a[top1+1]),top1++;
	}
	if(cnt<k) return printf("NO\n"),0;
	int last=1,tot=1,tmp=0;
	while(1){
		if(tot>cnt) break;
		for(int i=last;i<=pos[tot];i++){
			ch[a[i]]=tmp+'a';
		}
		last=pos[tot]+1;
		tot++;
		if(tot<=k) tmp++;
	}
	printf("YES\n");
	for(int i=1;i<=n;i++){
		printf("%c",ch[i]);
	}
	return 0;
}
```


---

## 作者：Twlight！ (赞：5)

# 题目大意
给定两种 $1 \sim n$ 的排列 $p,q$，和一个正整数 $k$，你需要构造一个由小写字母组成的字符串 $s$，满足：
1. 字符串至少包含 $k$ 种小写字母。
2. 按照 $p,q$ 的值作为下标排列字符串 $s$，组成字符串 $s1,s2$，满足 $s1,s2$ 中的字母单调不降。


# 思路
#### $Update$ $in$ $2024.10.11$ 简化了证明过程。

在这里提供一种特别简单的写法以及思路。

先说一个结论，若 $x$ 这个数分别出现在 $p,q$ 的 $i,j$ 位置，且按照 $p,q$ 排列后的字符串 $s1,s2$ 单调不降，则一定会满足：
$$
s1[i] = s1[i + 1] = \cdots = s1[j - 1] = s1[j]
\\
s2[i] = s2[i + 1] = \cdots = s2[j - 1] = s2[j]
\\
s1[i \ldots j] = s2[i \ldots j]
$$
（这里以及后文钦定 $i \leq j$，其实 $i \geq j$ 也是一样的。）


## 一种感性的证明
拿一种 $p,q$ 举例：
```
6 2 3 1 8 4 5 7
6 2 1 4 8 3 5 7
（我们查找 3 的位置）
则 i = 3, j = 5
```

当 $i \neq j$ 时，显然 $p[i],q[j]$ 左右两边数的个数不同，所以一定存在另一个数对应的位置 $i_1, j_1$ 满足 $i \leq i_1 \wedge j_1 \leq j$。

根据题目要求的单调不降性质，我们有：
$$s1[i] \leq s1[i + 1] \leq \cdots \leq s1[i_1 - 1] \leq s1[i_1]$$
$$s2[j_1] \leq s2[j_1 + 1] \leq \cdots \leq s2[j - 1] \leq s2[j]$$
$$s1[i_1] = s2[j_1] \wedge s1[i] = s2[j]$$

再由不等式的性质，我们便可以得到：
$$s1[i] = s1[i + 1] = \cdots = s1[i_1 - 1] = s1[i_1]$$
$$s2[j_1] = s2[j_1 + 1] = \cdots = s2[j - 1] = s2[j]$$

同样地，因为一定存在两个数的对应位置分别满足 $i_k \geq j \wedge j_k \leq j$ 和 $j_k \leq i \wedge i_k \geq i$，由上述推论可以再得到：

$$
s1[i] = s1[i + 1] = \cdots = s1[j - 1] = s1[j]
\\
s2[i] = s2[i + 1] = \cdots = s2[j - 1] = s2[j]
\\
s1[i \ldots j] = s2[i \ldots j]
$$

到此就证明了一开始的结论。

（因为本人能力有限，不清楚更严谨的证明过程，如果有更好的思路话也可以补充一下。）

## 具体的做法
那么知道了上述的结论，你可以尝试找到所有 $x$ 在 $p,q$ 中的不同位置，然后得到若干条等式链。

如果你整理这些等式链，你会发现原序列被这些相等关系拆成了若干条区间，每个区间里的字符都相等，而区间与区间之间的字符必须满足字母单调不降，于是就做完了。

由等式链的性质，你只需要扫一遍 $p[i],q[i]$，看看它们所对应的数分别出现在对方 $q,p$ 的位置，不断对这个位置取个 $\max$，记为 $j$，当 $i = j$ 时就说明这一段区间已经到了结尾，第 $i + 1$ 位置开始的便是新的区间了。

求出了不同的区间后，怎么构造字符串和判断是否有解就不再赘述，看代码即可。

时间复杂度：$O(n)$。


## 参考代码

```cpp
#include <iostream>
#include <algorithm>
#include <cstdlib>

const int N = 200000 + 10;
using namespace std;

int read() {
	int x = 0, k = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') k = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return  x * k;
}

int n, k;
int p[N], q[N], rkp[N], rkq[N];
int Rng[N], cnt;
char c[N];

signed main() {
	n = read(), k = read();
	for (int i = 1; i <= n; ++i) p[i] = read(), rkp[p[i]] = i;
	for (int i = 1; i <= n; ++i) q[i] = read(), rkq[q[i]] = i;
	for (int i = 1, j = 0; i <= n; ++i) {
		j = max(j, rkq[p[i]]);
		j = max(j, rkp[q[i]]);
		if (j == i) Rng[++cnt] = i;
	}

	if (cnt < k) printf("NO\n"), exit(0);

	printf("YES\n");
	for (int i = 1, j = 1; i <= n; ++i) {
		if (i > Rng[j]) ++j;
		c[p[i]] = 'a' + min(k, j) - 1;
	}

	printf("%s\n", c + 1);
	return 0;
}

```
顺着这个思路走，其实代码实现非常的简单，而且运行时间也比较快，大概只有 $140ms$ 左右。

---

## 作者：Tx_Lcy (赞：2)

[更垃圾的阅读体验](https://www.cnblogs.com/tx-lcy/p/16872666.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1213F)

## 思路

我们可以根据 $p_i$ 和 $q_i$ 建有向边，边 $u,v$ 表示 $u$ 需要小于等于 $v$。

然后跑一遍缩点。

不难发现在一个强连通分量里的点必须要相等，于是最多的不同字母个数即为 $\min(26,tot)$，其中 $tot$ 表示强连通分量的个数。

接下来我们已经把图缩成了一个 DAG，于是直接跑拓扑排序即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int const N=2e5+10;
char color[N];int rd[N],n,k,p[N],q[N];
vector<int>a[N],b[N];
int dfn[N],co[N],low[N],s[N],ind[N],top,cnt,tot;
inline void tarjan(int x){
    dfn[x]=low[x]=++cnt;s[++top]=x;ind[x]=1;
    for (auto v:a[x])
        if (!dfn[v]) tarjan(v),low[x]=min(low[x],low[v]);
        else if (ind[v]) low[x]=min(low[x],low[v]);
    if (low[x]==dfn[x]){
        ++tot;
        while (1){
            int X=s[top--];
            co[X]=tot;ind[X]=0;
            if (!(x^X)) break;
        }
    }
}
inline void topo_sort(){
    queue<int>q;
    for (int i=1;i<=n;++i) if (!rd[i]) q.push(i),color[i]='a';
    while (!q.empty()){
        int x=q.front();q.pop();
        for (auto v:b[x]){--rd[v];color[v]=max(color[v],min('z',char(color[x]+1)));if (!rd[v]) q.push(v);}
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>n>>k;
    for (int i=1;i<=n;++i) cin>>p[i];
    for (int i=2;i<=n;++i) a[p[i-1]].push_back(p[i]);
    for (int i=1;i<=n;++i) cin>>q[i];
    for (int i=2;i<=n;++i) a[q[i-1]].push_back(q[i]);
    for (int i=1;i<=n;++i) if (!dfn[i]) tarjan(i);
    if (tot<k) return cout<<"NO\n",0;
    for (int i=1;i<=n;++i)
        for (auto v:a[i])
            if (co[i]^co[v]) b[co[i]].push_back(co[v]),++rd[co[v]];
    topo_sort();
    cout<<"YES\n";
    for (int i=1;i<=n;++i) cout<<color[co[i]];cout<<'\n';
    return 0;
}
```


---

## 作者：思考人生中 (赞：1)

在毕克老师给的贪心题单中发现这道水紫，然后在AC后发现题解做法缤纷多彩，遂决定分享自己的做法。

（以及吐槽一句毕克老师上课完全不按照提前给的“上课的题单”讲）

---
## 思路

我们记 $T$ 为 $S$ 排序后满足 $\forall i\in[1,n-1],T[i]\le T[i+1]$ 的字符串，那么我们可以认为给出的排序 $a$ , $b$ 等价于给出了 $T$ 中字符相同的位置。

即我们对于所有的 $a_i=b_j=k$ 我们可以知道，$T_{\min\{i,j\}\cdots\max\{i,j\}}$ 中的每个字符都是同一个 。

事实上我们可以得到 $n$ 个类似于 $[\min\{i,j\},\max\{i,j\}]$ 的区间，表示区间内的字符都是同一个。

现在我们希望总的字符集合大小尽量大，因此我们只让有交的区间用同一个字符，即合并有交的区间。这一步可以按照左端点排序后贪心地维护。

维护后我们得到了一些两两不交的区间，同时由于 $i$ 和 $j$ 都遍历 $1\cdots n$，因此这些区间的并是 $[1,n]$，所以直接根据这些区间来构造方案是可行的，同时我们也可以根据这些区间的数量是否小于 $k$ 来判断是否不能做到至少用 $k$ 个字符。

只要按照区间从左到右的顺序依次赋值为 $a,b,c,\cdots$，如过超出 $26$ 个全都赋值为 $z$，这样我们就能构造出 $T$，此时再根据给出的排列 $a$ 或者 $b$ 就可以得到 $S$。

这样做显然是 $\mathcal O(n\log n)$ 或者 $\mathcal O(n)$ 的，这取决于按照左端点排序时是用计数排序还是比较排序。

## 代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#define MAXN 200000
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define rep(i,j,k) for (int i=(j);i<=(k);++i) 
using namespace std;

struct seg{int l,r;}num[MAXN+5],ans[MAXN+5];
//seg表示区间
//ans是最终合并后的区间，num是一开始得到的区间
inline bool cmp(seg x,seg y) {return x.l<y.l;}
int a[MAXN+5],b[MAXN+5],ina[MAXN+5],inb[MAXN+5];
//a,b如题意，ina和inb分别表示值为i在a与b中的下标
int val[MAXN+5],cnt=-1;
//val是T中每个位置赋的值，cnt是合并后区间的个数
char ch[MAXN+5];
//ch是S

int main() {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,k,l=0,r=0;
    cin>>n>>k;
    rep(i,1,n) cin>>a[i];
    rep(i,1,n) cin>>b[i];
    rep(i,1,n) ina[a[i]]=i;
    rep(i,1,n) inb[b[i]]=i;
    rep(i,1,n)
        num[i]=(seg){min(ina[i],inb[i]),max(ina[i],inb[i])};
    sort(num+1,num+n+1,cmp);
    rep(i,1,n) {
        if (num[i].l<=r) r=max(r,num[i].r);
        else {
            ans[++cnt]=(seg){l,r};
            l=num[i].l;r=num[i].r;
        }
    } 
    ans[++cnt]=(seg){l,r};
    if (cnt<k) {
        cout<<"NO\n";
        return 0;
    }
    cout<<"YES\n";
    rep(i,1,cnt)
        rep(j,ans[i].l,ans[i].r)
            val[j]=i;
    rep(i,1,n)
        ch[a[i]]='a'-1+min(26,val[i]);
    rep(i,1,n) cout<<ch[i];
    cout<<"\n";
    return 0;
} 

```

---

## 作者：OldVagrant (赞：1)

## 题意
给定两个 $1\sim n$ 的排列 $p,q$ ，和一个正整数 $k$，求是否存在一个合法的小写字母字符串 $s$ ，满足：

1. 包含恰好 $k$ 种不同的小写字母   
2. 对于 $\forall i\in [1,n)$，满足 $s[p_i]\le s[p_{i+1}],s[q_i]\le s[q_{i+1}]$，其中 $s[m]$ 代表 字符串 $s$ 的第 $m$ 个字符。


$1\le n\le 2\times 10^5,1\le k\le 26$。


## Solution
~~一发入魂抢到历史最优解rk1，只有几年前某个趁CF评测机不注意只测了20多个点的人比我快。~~   
前置知识：强连通分量（[B3609【模板】强连通分量](https://www.luogu.com.cn/problem/B3609)）缩点（[P3387【模板】缩点](https://www.luogu.com.cn/problem/P3387)）。
首先，我们可以发现这个关系是单向、可传递的，即如果 $s[a]\le s[b],s[b]\le s[c]$，那么 $s[a]\le s[c]$，并且 $s[b]\ge s[a],s[c]\ge s[b]$。这提示我们把这些关系放到一张 $n$ 个点的有向图中来处理，对关系 $s[a]\le s[b]$，我们就连一条有向边 $(a,b)$，共 $2(n-1)$ 条边，可能存在环。这个有向图一定是联通的，因为显然一个 $1\sim n$ 的排列所提供的 $n-1$ 条有向边恰好会形成一条很长的链，第二个排列就是在这个链上再加一些边，不影响联通性。    
然后考虑环，比如 $s[a]\le s[b]$ 且 $s[b]\le s[a]$，那么此时唯一的合法解就是 $s[a]=s[b]$ ，由此不难推出同一强连通分量内所有点的值必定相等，所以我们直接对原图进行缩点即可。
再考虑无解的情况。只要 $k$ 大于缩点后图的总点数 $sum$ 就是无解的，因为缩点之后每个点显然不可能同时取两种值。    
最后考虑怎么构造。这个很简单，缩点后的图一定是一个有向无环的联通图，且只有一个点的入度为 0，那我们可以找到这个点，然后遍历整个图去给每个点赋值，这个赋值方法有很多种，我是把前 $k$ 个点的值分别赋为 $1\sim k$ ，然后后面的全部赋成 $k$。注意一下要标记途中访问过的点，已经访问过就直接跳过即可，不标记会喜提 ```TLE on #10```。
## Code
```c
#include <bits/stdc++.h>
using namespace std;
int head[200001],to[400001],ne[400001],dfn[200001],l[200001],top,cnt,tot,s[200001],fa[200001],ecnt,eecnt;//fa为每个点对应的缩点之后的点的编号，其他数组相信学过tarjan缩点的都能看懂
int t[400001],hd[200001],nxt[400001],in[200001],col[200001],n,k,la;
bool vis[200001],vv[200001];//vv是上面说的用来标记的数组，vis是求强连通分量的时候用来判断一个点在不在栈内的数组
const int LEN=1<<21;
char BUF[LEN],*Pin,*Pin_last,PUF[LEN],*Pout=PUF,*Pout_last=PUF+LEN-1;
inline char gc(){
	return Pin==Pin_last&&(Pin_last=(Pin=BUF)+fread(BUF,1,LEN,stdin),Pin==Pin_last)?EOF:*Pin++;
}
inline void pc(char x){
	if(Pout==Pout_last) fwrite(PUF,1,Pout-PUF,stdout),Pout=PUF;
	*Pout++=x;
}
inline int read(){
	int x=0;
	char ch=gc();
	while(ch<48||ch>57) ch=gc();
	while(ch>47&&ch<58) x=x*10+ch-48,ch=gc();
	return x;
}
void write(int x){
    if(x>9) write(x/10);
    pc(x%10+48);
}
void tarjan(int x){//tarjan找出原图中所有的强连通分量
	dfn[x]=l[x]=++cnt,s[++top]=x,vis[x]=1;
	for(int i=head[x];i;i=ne[i]){
		int y=to[i];
		if(!dfn[y]) tarjan(y),l[x]=min(l[x],l[y]);
		else if(vis[y]) l[x]=min(l[x],dfn[y]);
	}if(l[x]==dfn[x]){
		fa[x]=++tot,vis[x]=0;
		int tp=s[top];
		while(tp!=x) fa[tp]=tot,vis[tp]=0,tp=s[--top];
		top--;
	}
}
void work(int x,int now){//遍历一遍图，对每个点赋值
	col[x]=now,vv[x]=1;
	for(int i=hd[x];i;i=nxt[i]){
		int y=t[i];
		if(!vv[y]){
		    if(now<k) now++;
		    work(y,now);
		}
	}
}
signed main(){
	n=read(),k=read(),la=read();
	for(int i=1;i<n;i++){//将给定的关系转化成有向图的边
		int x=read();
		to[++ecnt]=x,ne[ecnt]=head[la],head[la]=ecnt,la=x;
	}la=read();
	for(int i=1;i<n;i++){
		int x=read();
		to[++ecnt]=x,ne[ecnt]=head[la],head[la]=ecnt,la=x;
	}for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	if(tot<k) pc('N'),pc('O');//如果总点数（强连通分量数）小于k，则无解
	else{
	    for(int i=1;i<=n;i++){//重构出缩点后的图
    		int u=fa[i];
    		for(int j=head[i];j;j=ne[j]){
    			int v=fa[to[j]];
    			if(u!=v) t[++eecnt]=v,nxt[eecnt]=hd[u],hd[u]=eecnt,in[v]++;
    		}
    	}for(int i=1;i<=tot;i++) if(!in[i]) work(i,1),i=tot;//找到那个入度为0的点作为起点去遍历整个图，然后直接推出循环，这里的i=tot起的是和break一样的作用
    	pc('Y'),pc('E'),pc('S'),pc('\n');
    	for(int i=1;i<=n;i++) pc(col[fa[i]]+96);//找到每个点所在的缩点后的点v，然后输出v的值
	}fwrite(PUF,1,Pout-PUF,stdout);
	return 0;
}
```


---

## 作者：subcrip (赞：0)

一眼 XOR hashing 板题。

题目叫做 unstable string sort，这启发我们给出的数组 $a$ 和 $b$ 有区别的地方就是在于那些相等的字符可以按照任意的顺序排列。当然，它们未必在两个数组中处于不同位置，但是因为我们想最大化段数，所以只需要考虑极小的满足多重集 $\{a[l],\cdots,a[r]\}=\{b[l],\cdots,b[r]\}$ 的那些段就行了。

怎么找这样的段？我们把 $1$ 到 $n$ 的每个数映射到一个随机数上。记这个映射为 $mp$，然后只需要满足

$$
mp[a[l]]\oplus\cdots\oplus mp[a[r]]=mp[b[l]]\oplus\cdots\oplus mp[b[r]]
$$

就行。而这是可以用前缀和表示的，所以我们只需要统计两个数组在每个位置的异或前缀和的异或值，看看什么时候为 $0$ 说明可以在这里划分一段。最后检查段数是否至少是 $k$，然后每段里赋一个字符就行了。

Code:

```cpp
void solve() {
    read(int, n, k);
    vector<ll> mp(n + 1);
    for (int i = 1; i <= n; ++i) {
        mp[i] = rd();
    }
    readvec(int, a, n);
    readvec(int, b, n);
    vector<ll> ps(n + 1);
    vector<int> splits = { 0 };
    for (int i = 1; i <= n; ++i) {
        ps[i] = ps[i - 1] xor mp[a[i - 1]] xor mp[b[i - 1]];
        if (ps[i] == 0) {
            splits.emplace_back(i);
        }
    }
    if (splits.size() <= k) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        vector<int> res(n);
        int m = splits.size() - 1;
        for (int i = 1; i <= m; ++i) {
            int curr = min(k, i) - 1;
            for (int j = splits[i - 1]; j < splits[i]; ++j) {
                res[a[j] - 1] = curr;
            }
        }
        for (int i = 0; i < n; ++i) {
            cout << char('a' + res[i]);
        }
        cout << endl;
    }
}
```

---

