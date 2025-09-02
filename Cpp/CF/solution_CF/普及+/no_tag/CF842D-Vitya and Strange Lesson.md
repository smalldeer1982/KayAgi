# Vitya and Strange Lesson

## 题目描述

## 问题描述
mex 是一个序列中没有出现过的最小非负整数。

给出你一个长度为 $n$  的非负整数序列以及 $m$  个询问，每次询问先给你一个整数 $x$ ，然后：

- 把序列中所有数异或上 $x$ 
- 输出序列的 mex

注意，在每个询问过后序列是发生变化的。

## 样例 #1

### 输入

```
2 2
1 3
1
3
```

### 输出

```
1
0
```

## 样例 #2

### 输入

```
4 3
0 1 5 6
1
2
4
```

### 输出

```
2
0
0
```

## 样例 #3

### 输入

```
5 4
0 1 5 6 7
1
1
4
5
```

### 输出

```
2
2
0
2
```

# 题解

## 作者：试试事实上吗 (赞：11)

感觉应该是个经典问题，亏我还不知道。

实际上就是询问你集合中的数都异或上某个数的的$\text{mex}$。

考虑常用的操作异或集合的手段，我的第一反应是线性基，然而线性基只能插入，不能修改，再者她也不能查询$\text{mex}$这么奇怪的东西。

先不考虑异或，显然$\text{mex}$是有可二分性的，我们需要一个数据结构支持查询小于某个数的数是否都出现过，然后我们就可以二分了，我的第一反应是值域线段树，显然是可以做的，直接在线段树上二分就可以了，具体来说走到线段树的某个节点时，看一下左儿子存在的数是不是等于左儿子对应的值域大小，即看一下左儿子是不是满的。然而，线段树也不能维护异或这么奇怪的东西。

实际上我们可以选取和线段树结构相同的另一个数据结构（或者说她们就是同一个东西），$\text{01trie}$。

我们也可以在$\text{01trie}$上二分查$\text{mex}$，并且走到$\text{trie}$上某个点时，如果异或的数这一位为1，意义就是交换$\text{trie}$的左右儿子，然后就可以用和线段树一样的方法做了。

有一个细节就是，在计算$\text{trie}$一个点的$\text{size}$时，注意一个数出现多次只计算一次。

其他具体实现可以看一下代码，还是比较易懂的。

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
const int maxn=3e5+5,Lim=18;

int tr[maxn*19][2],nowxor,cnt=1,siz[maxn*19],n,m;

template<typename T>
inline void read(T &x)
{
    char c;int f=1;
    while(!isdigit(c=getchar())) (c=='-')&&(f=-1);
    x=c^48;
    while(isdigit(c=getchar())) x=x*10+(c^48);
    x*=f;
}

void insert(int x,int u=1,int now=Lim)
{
    if(now==-1) return siz[u]=1,void();
    int s=x>>now&1;
    if(!tr[u][s]) tr[u][s]=++cnt;
    insert(x,tr[u][s],now-1);
    siz[u]=siz[tr[u][0]]+siz[tr[u][1]];
}

inline int query(int x=nowxor)
{
    int u=1,res=0;
    for(int i=Lim;i>=0;--i)
    {
        int s=x>>i&1;
        if(siz[tr[u][s]]==((1<<i))) u=tr[u][s^1],res|=(1<<i);
        else u=tr[u][s];
        if(!u) return res;
    }
    return res;
}

int main()
{
    int x;
    read(n);read(m);
    for(int i=1;i<=n;++i)
        read(x),insert(x);
    while(m--)
    {
        read(x);nowxor^=x;
        printf("%d\n",query());
    }
    return 0,QAQ;
}
```



---

## 作者：Taduro (赞：4)

差不多是01trie的模板吧。

所谓01trie，就是把我们平时处理字符串的普通trie树边的信息改为一个数字二进制下这一位是0还是1。

这样就可以将一个数字变成一个01串存下来，做一些ans,or,xor之类的二进制操作。

本题要求序列在xor一个数下的mex，正常求mex的方法是在值域上建树，如果左子树不满就走向左子树，否则走向右子树。

同理，在trie里计一下数的个数就好了。

一些细节：不用把满二叉树建出来，找到一个不存在的节点直接默认我们之后的位上全是0，return好了。

我的代码有一些奇怪的小优化，可能不太好懂。

```c++
#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int t[6000005][2],k,n,maxn,num;
int c[300005],sum[600005][2],m;
inline void insert(int x){
	int u=1;
	for (int i=maxn; i>=0; i--){
		int a=((x&(1<<i))!=0);
		if (!t[u][a]) t[u][a]=++num;
		sum[u][a]++;u=t[u][a];
	}
}
inline int query(){
	int u=1,ans=0;
	for (int i=maxn; i>=0; i--){
		int a=((k&(1<<i))!=0);
		if (sum[u][a]<(1<<i)){
			u=t[u][a]; if (!u) return ans;
		}
		else{
			u=t[u][a^1];
			ans|=(1<<i); if (!u) return ans;
		}
	}
	return ans;
}
int main(){
	int x;
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) scanf("%d",&c[i]);
	sort(c+1,c+n+1);
	maxn=min((int)log2(c[n])+1,20);
	if (c[n]==0) maxn=1;
	num=1; c[0]=-1;
	for (int i=1; i<=n; i++)
		if (c[i]!=c[i-1]) insert(c[i]);
	while (m--){
		scanf("%d",&x);
		k^=x; printf("%d\n",query());
	}
	return 0;
}
```



---

## 作者：Gloaming (赞：3)

## 题目描述

给你一个长度为 $n(n\leq 3\times 10^5)$ 整数数列，对于每一次询问，我们将序列中每一个元素都异或上一个数字 $x$ 然后查询序列 $mex$，其中 $mex$ 定义为最小没有出现的自然数。

## 分析

我们先想想如何快速求一个序列的 $mex$，一种~~可能很常见的~~方法是建立一颗权值线段树，然后对于每一个值域，如果左儿子中数的数量等于区间长度，那么说明答案在右子树中，否则就在左子树中。

但是这种做法不能很好的处理异或，那我们怎么办呢？处理异或的问题，我们通常采用的是 01trie，那么我们如何使用 01trie 呢？

经过我们画图观察可以发现**如果出现了一段连续的数字，01trie 上对应的子树一定是满的**

然后我们和上面不带修改的方法类似，再插入的过程中对于每一个01trie上的节点，我们记录一下它的子树大小，如果它是满的，说明它的 $mex$ 在另外一边。

在考虑如何处理异或的条件，在01trie上就是相当于交换两颗子树，我们只需要加上一点小小的判断就可以了。

```c++
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n,m,tr[N*30][2],tot,sz[N*30];
inline void Ins(int cur,int weis,int x){
	if(weis<0) {sz[cur]=1;return;}
	int ch=x>>weis&1;
	if(tr[cur][ch]==0) tr[cur][ch]=++tot;
	Ins(tr[cur][ch],weis-1,x);
	sz[cur]=sz[tr[cur][0]]+sz[tr[cur][1]];
}
inline int Qry(int cur,int axor){
	int res=0;
	for(int weis=25;weis>=0;weis--){
		int ch=axor>>weis&1;
		if(sz[tr[cur][ch]]==(1<<(weis))) {
			res|=(1<<(weis));
			cur=tr[cur][ch^1];
		} else {
			cur=tr[cur][ch];
		}
		if(cur==0) return res;
	}
	return res;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>m;tot=1;
	for(int i=1;i<=n;i++){
		int x;cin>>x;Ins(1,25,x); 
	}
	int axor=0;
	for(int i=1;i<=m;i++){
		int x;cin>>x;axor^=x;
		cout<<Qry(1,axor)<<endl;
	}
	return 0;
} 
```

辛苦管理大大审核了

---

## 作者：是个汉子 (赞：3)

[洛谷传送门](https://www.luogu.com.cn/problem/CF842D)	[CF传送门](http://codeforces.com/problemset/problem/842/D)

题外话：做这个题之前我对 $\operatorname{mex}$ 的认知仅限于 $\operatorname{SG}$ 函数

### Solution

思考一下：为什么要给异或而不是别的什么呢？

说明我们要用到和异或有关的东西——线性基，$\operatorname{01trie}\cdots$ 

但是这个题线性基有点不太行，所以用 $\operatorname{01trie}$ 。

##### 先考虑没有异或操作，只询问 $\operatorname{mex}$ 

那其实就是在 $\operatorname{01trie}$ 上找最靠左的一个空位。

实现的话就是判断每一个节点的子树是否已经满了，满了往右，没满继续往左。

##### 现在加上异或操作

如果每次都先将所有数异或一遍，不管 $\operatorname{mex}$ 的运询问，复杂度也要达到 $O(nm)$ ，显然不行

但是异或是对于整个序列的，所以可以直接在 $\operatorname{01trie}$ 上进行操作（相当于一个全局标记）

按位考虑异或的数 $x$ ：

1. 如果第 $k$ 位是 $1$ ，那就相当于将 $\operatorname{01trie}$ 所对应节点的子树进行了反转操作。

   不要真的反转，因为之前判断的是左子树，现在判断右子树即可

2. 如果第 $k$ 位是 $0$ ，那就相当于什么都没变，该干啥干啥╮(╯▽╰)╭

注意：因为 $\operatorname{01trie}$ 上每个叶子节点对应的数字都不一样，所以在插入数字的时候应该先去重

### Code

```c++
#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=3e5+10;
int ch[N*20][2],cnt=1,siz[N*20],n,m,s,a[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

void insert(int x){
    int now=1;
    for(int i=20;i>0;i--){
        siz[now]++;
        if(x&(1<<(i-1))){
            if(!ch[now][1]) ch[now][1]=++cnt;
            now=ch[now][1];
        }
        else{
            if(!ch[now][0]) ch[now][0]=++cnt;
            now=ch[now][0];
        }
    }
    siz[now]++;
}

int query(){
    int now=1,ans=0;
    for(int i=20;i>0;i--)
        if(s&(1<<(i-1))){
            if(!ch[now][1]) return ans;
            else if(siz[ch[now][1]]<(1<<(i-1))) now=ch[now][1];
            else now=ch[now][0],ans+=(1<<(i-1));
        }
        else{
            if(!ch[now][0]) return ans;
            else if(siz[ch[now][0]]<(1<<(i-1))) now=ch[now][0];
            else now=ch[now][1],ans+=(1<<(i-1));
        }
    return ans;
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) 
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    n=unique(a+1,a+n+1)-a-1;
    for(int i=1;i<=n;i++)
        insert(a[i]);
    int x;
    while(m--){
        scanf("%d",&x);
        s^=x;
        printf("%d\n",query());
    }
    return 0;
}
```



---

## 作者：Foreverxxx (赞：2)

前言：如果对 ``01Trie`` 以及异或相关操作比较熟悉的话，做这道题就会感觉比较简单，否则思考起来难度比较大。

### 思路

首先看到题目中说的异或操作，那么脑海里面就会立刻浮现线性基以及 ``01Trie`` 两种数据结构，但是仔细一想，线性基并不支持修改查询 $mex$ 的操作，所以说这个方法寄了。

所以我们想一想 ``01Trie`` 能不能解决这个问题。

先暴力地思考一下，如果每次把每个数进行异或的操作，那么时间复杂度已经达到了 $O(nm)$ 级别，明显是不能接受的，那么我们就应该思考异或的性质。

由于异或是对二进制的每一位单独进行操作，每一位之间相互不会影响，所以我们考虑每个数字的二进制表示并对每一位进行思考。

对于询问的一个数 $x$，在原来的字典树上，假设此时本来应该向左儿子走，但是如果 $x$ 的这一位是 $1$，即相当于进行左右子树的交换操作，那么我们就应该**调转方向**，向右儿子走。

如果现在输入的是 $x_i$，那么现在真正进行操作的 $x$ 就应该是 $x = x_1 \oplus x_2 \oplus x_3 \dots x_{i-1} \oplus x_i$。

所以现在已经解决了 $m$ 个查询的问题，只需要思考如何在 ``01Tire`` 上查找 $mex$，这比较简单，只需要判断当前子树是否为满二叉树，如果是只能调转方向，否则尽量向着 $0$ 的方向走，以保证 $mex$ 最小的性质。

但我们还必须注意一个坑点：**同一个数不能被插入两次**！因为这会导致子树的大小发生变化，造成答案错误。

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int sss=0;
	char chh=getchar();
	while(chh<'0'||chh>'9') chh=getchar();
	while(chh>='0'&&chh<='9'){
		sss=sss*10+chh-'0';
		chh=getchar();
	}
	return sss;
}
int n,m;
int trie[6000005][2],tot=0;
int siz[12000005];
bool vis[300005];
void insert(int x){
	int p=0;
	for(register int i=(1<<20);i;i>>=1){
		bool tmp=x&i;
		if(!trie[p][tmp]) trie[p][tmp]=++tot;
		p=trie[p][tmp];
		siz[p]++;
	}
}
int query(int x){
	int p=0,ans=0;
	for(register int i=(1<<20);i;i>>=1){
		bool tmp=x&i;
		if(siz[trie[p][tmp]]==i){//如果子树是满二叉树 
			p=trie[p][tmp^1];
			ans=ans*2+1;
		}
		else {
			p=trie[p][tmp];
			ans*=2;
		}
	}
	return ans;
}
int main(){
	n=read(),m=read(); int now;
	for(register int i=1;i<=n;i++){
		now=read(); 
		if(!vis[now]){
			vis[now]=true;
			insert(now);
		}
	}
	now=0; int now_xor;
	while(m--){
		now_xor=read();
		now^=now_xor;
		cout<<query(now)<<"\n";
	}
	return 0;
}
```

---

## 作者：ykuouzf (赞：2)

### $01trie$

本题需要支持全局异或操作，显然我们会想到上面这个东西

考虑到暴力全局修改的时间复杂度是$O(N * L)$，不能接受，于是想到用一个变量来存下每次修改的值，在查询时去对应相反的子树即可

查询实质上就是寻找01trie上最靠左的一个空位，于是可以在建树时就记录下每个节点的子树大小，判断时如左子树未满就走左边，反之则走右边

其余仍有一些细节，在建树时相同的数只算一次，于是要先对原数组进行离散化操作。还有在二进制数长度不足时，前面记得用零补齐，使得每个数的长度都是一个常量，可以避免很多不必要的错误

### Code：

```
#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
const int L = 20;
const int M = N * L * 2 + 10;

int n, m, tot = 1, q;
int a[N], t[M][2], siz[M], l[M];

void Insert(int x) {
	int c[50], len = 0, p = 1;
	for (int i = 1; i <= L; i++) { c[i] = 0; }
	do { c[++len] = x % 2; x /= 2; } while (x);
	for (int i = L; i >= 1; i--) {
		if (!t[p][c[i]]) { t[p][c[i]] = ++tot; }
		l[p] = i - 1; p = t[p][c[i]]; siz[p]++;
	}
}

int query(int x) {
	if (!x) { return 0; }
	int p = q >> l[x] & 1;
	if (siz[t[x][p]] < (1 << l[x])) { return query(t[x][p]); }
	else { return query(t[x][p ^ 1]) | (1 << l[x]); }
}

signed main() {
	ios::sync_with_stdio(0);
	cin >> n >> m;
	for (int x, i = 1; i <= n; i++) { cin >> a[i]; }
	sort(a + 1, a + n + 1); a[0] = -1;
	for (int i = 1; i <= n; i++) {
		if (a[i] != a[i - 1]) { Insert(a[i]); }
	}
	for (int x, i = 1; i <= m; i++) {
		cin >> x; q ^= x;
		cout << query(1) << "\n";
	}
	return 0;
} 
```


---

## 作者：Forever1507 (赞：1)

鸣谢：
- 思路来源：@apple365
- DeBug：@刘洢含

先考虑简化版本：不带修。

显然，我们可以开一棵 01字典树。

如果某个子树没有 $mex$，那么一定是满二叉树，否则一定能找到。

所以，我们只要搜下去，为了保证最小，优先走左边，如果左边满了就走右边，直到尽头输出即可。

问题在于：带修怎么做？

考虑记变量 $tag$，初始设为 $0$，每次与 $x$ 异或。

当考虑到第 $i$ 层时，取 $tag$ 二进制下的第 $i$ 位（从前往后），若为 $1$，说明要异或，变为向右走，否则不管。

还有一个细节，就是说不能重复插入。

```
Author:Forever1507
using namespace std;
int n,node[6000005][2],m,tot,tag,siz[6000005];
void insert(int x){
	int u=0;
	for(register int i=31;i>=0;i--){
		int c=(x>>i)&1;
		if(node[u][c]==0)node[u][c]=++tot;
		u=node[u][c];
		siz[u]++;//用来判断左右子树
	}
	return;
}
map<int,bool>mp;
int query(int x){
	tag^=x;
	int u=0,num=0;
	for(int i=31;i>=0;i--){
		int c=(tag>>i)&1;
		if(siz[node[u][c]]==(1<<i)){//满了，向右
			u=node[u][c^1];
			num=num<<1|1;
		}
		else{//可以向左
			u=node[u][c];
			num=num<<1;
		}
	}
	return num;
}
int main(){
	cin>>n>>m;
	for(register int i=1;i<=n;++i){
		int s;
		cin>>s;
		if(!mp[s])//判重
		insert(s);
		mp[s]=1;
	}
	for(register int i=1;i<=m;++i){
		int x;
		cin>>x;
		cout<<query(x)<<'\n';
	}
	return 0;
} 
```


---

## 作者：BigJoker (赞：0)

# Solution

对于求 $\texttt{mex}$ 的问题很多数据结构都可以实现。并且这个题只需要求一个整体序列的，一个值域的数据结构都可以解决。但是难点在于有一个异或操作，好像可用的只有 $\texttt{01trie}$ 了。

首先把每个数添加进去，并且不能添加重复的。

我们插入完之后记录一下每个节点的大小，节点的大小就是其这棵树的大小。

对于异或操作，由于它是恒存在的，所以用一个变量存下现在该异或多少即可。

然后我们开始在 $\texttt{01trie}$ 上面开始查找。

异或的原则是相同为 $0$，相异为 $1$，由于要查找比较小的，那么无疑优先看一下相同的那一头是不是满的，不是满的就查另一边，直到查完为止。

# Code

```cpp
#include<bits/stdc++.h>
#define re register
#define il inline
using namespace std;
int n,x,fsk;
int tr[9000005][2],sz[9000005],idx;
map<int,bool>q;
void insert(int x){
	int p=0;
	for(int i=20;i>=0;i--){
		int u=x>>i&1;
		if(!tr[p][u]) tr[p][u]=++idx;
		p=tr[p][u];
		sz[p]++;
	}
}
int ask(int x){
	fsk^=x;
	int p=0,res=0;
	for(int i=20;i>=0;i--){
		int u=fsk>>i&1;
		res<<=1;
		if(sz[tr[p][u]]==(1<<i)) p=tr[p][!u],res|=1;
		else p=tr[p][u];
	}
	return res;
}
int main(){
	scanf("%d %d",&n,&x);
	for(int i=1;i<=n;i++){
		int fsk2;
		scanf("%d",&fsk2);
		if(!q[fsk2]) insert(fsk2);
		q[fsk2]=1;
	}
	while(x--){
		int p;
		scanf("%d",&p);
		printf("%d\n",ask(p));
	}
	return 0;
}
```

---

## 作者：recollect_i (赞：0)

我们可以用权值线段树维护最长连续段：线段树每个节点维护 $M,S$ 分别表示这个区间 mex、区间长度，合并时，如果左儿子的 mex 等于区间长度，则这个节点的 mex 为左儿子区间长度加右儿子 mex，否则为左儿子 mex。

这样建的线段树如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/6bnuksd6.png)

其中橙色线段代表左儿子，蓝色线段代表右儿子，下同。

为了方便后文叙述，“层”从下往上、从 $0$ 开始编号，层的最大编号为 $k$，每一层的节点从 $0$ 开始编号。

考虑一个异或 $x$ 的操作，比如 $x=5$，如果固定底层的节点不变，则线段树会长这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/ggyhxoas.png)

可以发现，实际上是把第 $1$ 层和第 $3$ 层的节点交换左右儿子。

实际上，对于异或 $x$ 的操作，若 $x$ 二进制第 $i$ 位（从低到高，从 $0$ 开始编号）为 $1$，则将线段树第 $i+1$ 层的左右儿子交换。

对于所有的异或 $x$ 的操作，线段树的节点会有很多重合部分，把所有的操作的线段树建出来并合并，则会是这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/0maog4tu.png)

有几个性质：

- 对于第 $i(i>0)$ 层第 $j$ 个节点，它的左儿子是第 $i-1$ 层第 $j$ 个节点，右儿子是第 $i-1$ 层第 $j\bigoplus 2^i$ 个节点，其中 $a\bigoplus b$ 表示 $a$ 和 $b$ 的按位异或。
- 对于第 $k$ 层第 $j$ 个节点，以这个点为根的线段树是异或 $j$ 操作后的线段树。

对于本题，第 $k$ 层节点的 $M$ 值便是答案。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int M = 21, N = 1 << 19 | 5;

int m = 19, n = 1 << m, q, t, x, y;
struct node{
    int m, p;
}s[2][N];

void pushup(node &u, node &l, node &r)
{
    u.m = l.p ? l.m + r.m : l.m;
    u.p = l.p & r.p;
}

int main()
{
    scanf("%d%d", &q, &t);
    while(q -- ) scanf("%d", &x), s[0][x] = {1, 1};
    for(int i = 1, x = 1, y = 0; i <= m; i ++ , x ^= 1, y ^= 1)
        for(int j = 0; j < n; j ++ )
            pushup(s[x][j], s[y][j], s[y][j ^ (1 << i - 1)]);
    while(t -- ) scanf("%d", &x), y ^= x, printf("%d\n", s[1][y].m);
    return 0;
}
```

---

