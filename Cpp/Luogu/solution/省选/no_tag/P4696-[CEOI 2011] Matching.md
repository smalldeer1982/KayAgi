# [CEOI 2011] Matching

## 题目描述

对于整数序列 $(a_1,a_2,\cdots,a_n)$ 和 $1\sim n$ 的排列 $(p_1,p_2,\cdots,p_n)$，称 $(a_1,a_2,\cdots,a_n)$ 符合 $(p_1,p_2,\cdots,p_n)$，当且仅当：

-    $\{a\}$ 中任意两个数字互不相同；

-    将 $(a_1,a_2,\cdots,a_n)$ 从小到大排序后，将会得到 $(a_{p_1},a_{p_2},\cdots,a_{p_n})$。

现在给出 $1\sim n$ 的排列 $\{p\}$ 和序列 $h_1,h_2,\cdots,h_m$​​，请你求出哪些 $\{h\}$ 的子串符合排列 $\{p\}$。


## 说明/提示

对于 $100\%$ 的数据，有 $2\le n\le m\le 1\ 000\ 000;1\le h_i\le 10^9;1\le p_i\le n$，保证 $\{h\}$ 中的元素互不相同，且 $\{p\}$ 是一个排列。

## 样例 #1

### 输入

```
5 10
2 1 5 3 4
5 6 3 8 12 7 1 10 11 9```

### 输出

```
2
2 6```

# 题解

## 作者：maowuyou (赞：34)

# KMP + 重新定义相等

[题目传送器](https://www.luogu.org/problem/P4696)

题目很绕 ， 其实就是一句话 

#### 给你两个排列 P 、H， 求 H 中 任意一段 连续的 排列 与P相同的序列 

怎么求 ？？？？？ ~~（白问）~~

这很明显是一个匹配问题

具体得说 ： 两个串进行匹配 

KMP 就是 在线性时间 完成这种题目 的 算法

### 考虑怎么 KMP ？

很容易想到 ， 匹配数字串 和 匹配 字符串的大致思路没有差别 

匹配 单纯的数字串 和 匹配 “排列串” 的差别 仅仅在只是在 判断相等 上有差别

### 所以 匹配 “排列串” 和 比配 字符串的差别 在于 判断相等

现在所有人应该都能理解标题中的 “重新定义相等” 了 吧

#### 现在难点变为 ： 如何重新定义 “相等”

以前看到过一句话 ： 你定义两个事物的某个特性一样时，称两个事物相等

   那么 你定义的标准 肯定是你 最看重的
 
P 是 一个排列 

何为排列 ？ 排序后的列的顺序

顺序与什么有关 ？ “比他大的数的个数” 和 “比他小的数的个数 ” 

所以相等就被定义为 在一个范围内 h[i] 与和其匹配的c[i] 有 一样多的 “比他大的数的个数” 和 “比他小的数的个数 ” 

于是乎 离散化 + 树状数组 的解法 就出现了 

但对于我这种蒟蒻而言 ， 数据结构太难了！！！ 

所以我们换一种角度 

其实很容易就能想到 

c[i] 若满足 p[i] 的排列（即 c[i] 在这一段范围内排在与 p[i] 同样的位置） 

也是能算作匹配的

于是我们预处理处 P 排列中 p[i] 的 前驱和后继 的位置

匹配时 ，判断 c[i] 是否 大于（或小于） 他所要匹配的 p[i] 的 前驱 （或后继） 

这样的匹配是 O(1) 的 

~~似乎比 树状数组还快~~

就形成了这个玄学算法 

请各位仔细感性理解 

代码如下
```cpp
#include<bits/stdc++.h>
#define MAXN 1000005
int a[MAXN],b[MAXN],c[MAXN],p[MAXN];
int pre[MAXN],net[MAXN],L[MAXN],R[MAXN];
int ans[MAXN];
int n,m,k;
bool check(int P[],int u,int v)
{
	return P[v+L[u]]<=P[v] && P[v+R[u]]>=P[v];
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		a[b[i]]=i;
		pre[i]=i-1;
		net[i]=i+1;
	}
	for(int i=n;i>=1;i--)
	{
		int j=a[i];
		if (pre[j]) L[i]=b[pre[j]]-i;
		if (net[j]<=n) R[i]=b[net[j]]-i;
		pre[net[j]]=pre[j];
		net[pre[j]]=net[j];
	}
	for(int i=2,j=0;i<=n;i++)
	{
		while (j && !check(a,j+1,i)) j=p[j];
		if (check(a,j+1,i)) j++;
		p[i]=j;
	}
	for(int i=1;i<=m;i++) scanf("%d",&c[i]);
	for(int i=1,j=0;i<=m;i++)
	{
		while (j && !check(c,j+1,i)) j=p[j];
		if (check(c,j+1,i)) j++;
		if (j==n)
		{
			ans[++k]=i-n+1;
			j=p[j];
		} 
	}
	printf("%d\n",k);
	if (k==0)
	{
		puts("");
		return 0;
	}
	for(int i=1;i<=k;i++) printf("%d ",ans[i]);
	return 0;
}
```
   
希望这道题能让你更好理解KMP 

理解 事物间的相等关系

理解匹配的真谛

---

## 作者：夜临 (赞：29)

线段树加哈希的写法，时间复杂度 $O(m*log2(m))$。


kmp是有 $O(n)$ 写法的但是比较难懂，如果用线段树的话思路会比较清晰

------------
ps：本题比较卡空间推荐使用unsigned int或使用树状数组

------------
我们先考虑一个等长的两段字符的匹配，即$n$=$m$。

此时就是将$m$个数排列，然后将下标哈希后比较。

如果吗$m $>$n$那么就会产生下标并不是n的排列的情况。

如${1,2,3,4,5,6}$这样的数组，当$n$=$5$时，我们还要匹配$2$-$6$这一段是否与$n$的字符串相等，那么很明显此时的下标也是$2$-$6$，但是我们的下标时按顺序增加的，所以如果我们将$2$-$6$的所有数都减去  $1$  那么就会是我们想要的排列。

虽然减  $1$  是 $O(n)$ 的，但是我们体现在哈希值上是就是减去
$\operatorname{sum}\gets 1+base+base^2+base^3+....+base^{n-1}$。

那么显然这样的$\operatorname{sum}$是可以预处理出的，同理所有下标减去  $2$  的时候减去这个$\operatorname{sum}\times 2$即可。


~~所以说哈希真是个好东西(٩(๑❛ᴗ❛๑)۶~~

------------


那么我们就需要一个数据结构，能支持以下操作:

1. 删除和增加某个元素，即能维护长度为n的数列的答案。

1. 能够维护元素按大小排序。

1. 能够维护哈希的值。

那么问题来了，线段树能够做到吗？

能的，因为哈希有另一个优秀的性质。

~~所以还是哈希厉害（滑稽）~~

即，能满足两段哈希O（1）合并，只要右边的一段乘上$base$的左边一段的元素的个数次幂,即:$\operatorname sump=sumls+sumrs\times base^{sz[ls]}$

------------


那么已知可以维护哈希的值后，我们只需能够维护元素的大小顺序，这样就再加上一个离散化。

开一个大小为m的线段树每次加入一个数的就将它加到线段树上它离散化后的位置，再维护一个区间的元素个数就能再保证维护大小顺序的同时维护哈希值。

所以这题可以用哈希+线段树+离散化这三个小知识点拼接写成，主要是从哈希切入，再想到用线段树这些工具来维护。

 
下面是代码，没有读懂解释可以配合代码理解一下。

------------
```cpp
#include<bits/stdc++.h>
#define N 1000005
#define H 233
#define ls p<<1
#define rs p<<1|1
using namespace std;
unsigned int n,m,a,A[N],B[N],t[N],T,sum,sz[N*3],res[N*3],tot;//res为区间的哈希值，sz为区间的元素数量
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}//不开快读可能会T。。
void update(int l,int r,int p,int x,int e,int k){
	if(l==r){
		res[p]=x;
		sz[p]=e;
		return;//将单个元素的哈希值和数量复制给线段树
	}
	int mid=l+r>>1;
	if(k<=mid)update(l,mid,ls,x,e,k);
	else update(mid+1,r,rs,x,e,k);
	sz[p]=sz[ls]+sz[rs];
	res[p]=res[ls]+t[sz[ls]]*res[rs];//线段树up向上更新
}
bool cam(int d,int e){
	return A[d]<A[e];
}
int main(){
	cin>>n>>m;
	t[0]=1;
	for(int i=1;i<=n;i++){
		a=read();
		T=T+t[i-1]*a;
		t[i]=t[i-1]*H;//t为base的次幂
		sum=sum+t[i-1];//sum为减1的值
	}
	for(int i=1;i<=m;i++){
		A[i]=read();
		B[i]=i;
	}
	sort(B+1,B+m+1,cam);
	for(int i=1;i<=m;i++)A[B[i]]=i;//之所以离散化写这么阴间也是为了卡空间
	for(int i=1;i<=m;i++){
		update(1,m,1,i,1,A[i]);
		if(i>=n){
			int Y=res[1]-sum*(i-n);//Y记录的是当前的答案
			update(1,m,1,0,0,A[i-n+1]);//将超出部分删除
			if(T==Y)B[++tot]=i-n+1;
		}
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++)printf("%d ",B[i]);
}
```
~~写题解不易，给个赞再走吧QAQ~~

---

## 作者：RedreamMer (赞：14)

[$\Large\texttt{P4696}$](https://www.luogu.com.cn/problem/P4696)

[更好的体验](https://www.cnblogs.com/RedreamMer/p/14813788.html)

标签：KMP，链表结构

## 前言

我靠网上怎么全是带 $\log$ 的做法，看题目限制应该是放了一支 $\log$，但是由于我太菜没想出来，所以来写 $\mathcal O(n)$ 的题解了。

~~似乎常数比较小。~~

## 题意

不做赘述，注意给定的序列 $\{p\}$ 其实是类似于后缀数组中的 sa 数组，不是每个下标的排名。

## 思路

子串匹配问题，输出方案，哇这限制条件，这好 $\mathcal O(n)$ 啊，而且是逐字匹配，感觉很像 KMP。

我们就先向 KMP 方向考虑，注意到输入序列 $\{p\}$ 是以排名为下标，没有意义，转换成每个下标的排名数组，注意此时还是一个排列。

我们考虑一个成功的匹配是怎样的，即序列 $\{a\}$ 的某一个子串离散化排序后对应的下标是和序列 $\{p\}$ **完全一致**的。

那我们如何重新定义这个 “匹配” 和 “一致”，如何在 KMP 建立正确的 next 数组中进行最优的比较操作？

在建立 next 的数组的过程中，当我们考虑到下标 $i$ 时，我们假设已经像普通的 KMP 思路已经继承了 $i - 1$ 的最优匹配，我们比较两个 $i$ 和 $next[i] + 1$ （在比较序列 $p[1,\dots,next[i - 1] + 1]$ 和 $p[i - next[i - 1], \dots, i]$ 的意义下）是否相等，即比较 $p[next[i - 1] + 1]$ 在其前缀序列的排名和 $p[i]$ 在其后缀序列的排名是否相等，否则一直跳 next，正确性显然是对的。

到这里，是可以用树状数组做了。

对于 $\mathcal O(n)$ 的做法，我们可以更好地利用一个性质：已匹配的两个字串排名是完全相等的，所以我们只需要比较一下 $i$ 的前驱和后继与 $next[i - 1] + 1$ 的前驱和后继（相对于分别的匹配子串的）位置是否相等，这样同样保证了两者在匹配子串的相对位置。

而我们只需要求得模式串的前驱和后继即可，将其拿来比较即可。

（这里的前驱和后继是指值小于/大于某个数，且下标小于某个数）

## 代码

-O2 854ms 目前最优解。

```cpp
int a, b, s[2][N + 5], L[N + 5], R[N + 5], nxt[N + 5], p[N + 5], l[N + 5], r[N + 5];
vector<int> ans;

bool check(int o, int i, int j, int mn, int mx) {
	int res = 1;
	if (mn) res &= (s[o][i - (j - mn)] < s[o][i]);
	if (mx) res &= (s[o][i - (j - mx)] > s[o][i]);
	return res;
}

void init() {
	rep(i, 1, a) l[i] = p[s[0][i] - 1], r[i] = p[s[0][i] + 1];
	per(i, a, 1) {
		L[i] = l[i];
		R[i] = r[i];
		l[r[i]] = l[i];
		r[l[i]] = r[i];
	}
	int j = 0;
	rep(i, 2, a) {
		while (j && !check(0, i, j + 1, L[j + 1], R[j + 1])) j = nxt[j];
		if (check(0, i, j + 1, L[j + 1], R[j + 1])) ++j;
		nxt[i] = j;
	}
}

signed main() {
	// freopen("in1.in", "r", stdin);
	// freopen("out.out", "w", stdout);
	a = read();
	b = read();
	rep(i, 1, a) p[i] = read();
	rep(i, 1, a) s[0][p[i]] = i;
	rep(i, 1, b) s[1][i] = read();
	init();
	int j = 0;
	rep(i, 1, b) {
		while (j && !check(1, i, j + 1, L[j + 1], R[j + 1])) j = nxt[j];
		if (check(1, i, j + 1, L[j + 1], R[j + 1])) ++j;
		if (j == a) ans.PB(i - a + 1), j = nxt[j];
	}
	printf("%d\n", siz(ans));
	rep(i, 0, siz(ans) - 1) printf("%d ", ans[i]);
	return 0;
}
```

---

## 作者：da32s1da (赞：10)

kmp搞一搞

找到**转化后的p排列**，对于每个位置，**之前**比它大的最小的位置和比它小的最大的位置。

然后就kmp搞一搞就好啦。只不过原来的kmp是判断字母相同，现在是判断放这个数合不合法，其余的相同。

这个方法是线性的

```
#include<cstdio>
const int N=1e6+50;
inline void rad(int &_){
    static char ch;
    while(ch=getchar(),ch<'0'||ch>'9');_=ch-48;
    while(ch=getchar(),ch<='9'&&ch>='0')_=_*10+ch-48;
}
int Out[10],out;
inline void prt(int u){
	if(!u)++out;
	else for(;u;Out[++out]=u%10,u/=10);
	for(;out;putchar(48+Out[out--]));
	putchar(' ');
}
int n,m,x,ans;
int a[N],b[N],c[N],kmp[N];
int pre[N],net[N],L[N],R[N],Ans[N];
inline bool get(int *p,int u,int v){
	return (!L[u]||p[v+L[u]]<p[v])&&(!R[u]||p[v+R[u]]>p[v]);
    //判断合不合法
}
int main(){
	rad(n);rad(m);
	for(int i=1;i<=n;i++){
		rad(b[i]);a[b[i]]=i;
		pre[i]=i-1;net[i]=i+1;
	}
    //a[]即为转化后的p数组
	for(int i=n;i>=1;i--){
		x=a[i];
		if(pre[x])L[i]=b[pre[x]]-i;
		if(net[x]<=n)R[i]=b[net[x]]-i;
		pre[net[x]]=pre[x];
		net[pre[x]]=net[x];
	}
	//双向链表求比它大的最小的位置和比它小的最大的位置
	x=0;
	for(int i=2;i<=n;i++){
		while(x&&!get(a,x+1,i))x=kmp[x];
		if(get(a,x+1,i))x++;
		kmp[i]=x;
	}
    //先自身匹配
	x=0;
	for(int i=1;i<=m;i++)rad(c[i]);
	for(int i=1;i<=m;i++){
		while(x&&!get(c,x+1,i))x=kmp[x];
		if(get(c,x+1,i))x++;
		if(x==n)Ans[++ans]=i-n+1,x=kmp[x];
	}
    //然后与h串匹配
	prt(ans);putchar('\n');
	for(int i=1;i<=ans;i++)prt(Ans[i]);
}
```

---

## 作者：FutaRimeWoawaSete (赞：9)

这道题我是真的被淦了……   

首先我们正常人想法：暴力 $O(nm)$ 来一发。   

然而 $T$ 飞不用说了。   

又观察了一会儿后，突然发现这道题有点像 $KMP$ 。如果用 $KMP$ 的特殊匹配模型解决是否可以解决？     

经过手动模拟后我们发现，其实确定当前匹配的状态就是相对位置，如果相对位置相同那不就匹配起了？    

然而相对位置又和一个数在一个序列的排名有关，所以我很快就想出来了一个思路：维护这个数在当前查询里的排名。    

再观察数据范围，老 $1e6$ 了。果断离散后搬树状数组大哥。    

然而此时我突然发现，我们 $KMP$ 的匹配是需要一个阶段性，    

抽象一点来说需要“递推”上来的啊，可是我们此时维护排名需要知道当前区间的所有数啊，然后我就被卡死了。    

眼看已经想超时了，果断开了题解，看到有一篇树状数组的 $TJ$ 还是挺开心的，终于能自己独立想对黑题算法了……    

读了前面才发现自己确实太莽了，没分析清楚，其实我们只要知道 $p$ 数组前面有多少个数比它小就 $OK$ 了。   

这就很有意思了，也许很多人在这里会有疑惑。    

我们以样例先举例子试试？   

```
2 1 5 3 4 
0 0 2 2 3
```
上一行为 $p$ 数组，下一行就是每个数前面有多少个数比它小。    

这里我稍微讲的好理解一点，我们单一一个元素的排名就是 $1$ ，这点不用废话吧，那么现在我们进行递推，   

我们此时得到了第二个元素知道它前面有多少个数比它小，要么前面的数比它大要么比它小，此时序列中的相对排名我们还是可以确定。    

这时你就会发现这个递推状态就相当于此时前面的所有元素的排名我们都确定了，而此时我们新增的元素又知道它前面有多少个比它小，那么就相当于我们当前这个元素加入前面的序列排序后，它的排名就是有多少个数比它小这个值再加上 $1$ 。    

这个解释已经很详细了吧……    

再~~数学~~一点，我们可以把记录下来的每个数前面有多少个数比它小的数组成的集合，当成一个状态，它和最后组成的相对排名成一个一一对应关系。    
于是我们直接维护上述条件就行了，由于我们本来的 $KMP$ 算法就只有 $O(n + m)$ ， 所以现在的时间复杂度就是 $O(n + mlogn)$ 。   

不得不说，这是一道 $KMP$ 好题。    
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 1e6 + 5;
int n,m,tot,p[Len],s[Len],kmp[Len],cnt[Len],c[Len],lsh[Len],Print[Len];
int lowbit(int x){return x & (-x);}
void add(int x){while(x <= n) c[x] ++ , x += lowbit(x);}
void del(int x){while(x <= n) c[x] -- , x += lowbit(x);}
int query(int x)
{
	int res = 0;
	while(x)
	{
		res += c[x];
		x -= lowbit(x);
	}
	return res;
}
void Clear_p(int l,int r){for(int i = l ; i <= r ; i ++) del(p[i]);}
void Clear_s(int l,int r){for(int i = l ; i <= r ; i ++) del(s[i]);}
int main()
{
	scanf("%d %d",&m,&n);
	for(int i = 1 ; i <= m ; i ++){int x;scanf("%d",&x);p[x] = i;}
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%d",&s[i]);
		lsh[i] = s[i];
	} 
	sort(lsh + 1 , lsh + 1 + n);
	for(int i = 1 ; i <= n ; i ++) s[i] = lower_bound(lsh + 1 , lsh + 1 + n , s[i]) - lsh;
	int j = 0;
	for(int i = 1 ; i <= m ; i ++) cnt[i] = query(p[i]) , add(p[i]);//num数组就是表示前面有多少个数小于它
	memset(c , 0 , sizeof c);
	for(int i = 2 ; i <= m ; i ++)
	{
		while(j && query(p[i]) != cnt[j + 1]){Clear_p(i - j , i - kmp[j] - 1) ; j = kmp[j];}//中间全部甩掉
		if(query(p[i]) == cnt[j + 1]){add(p[i]) ; j ++;}
		kmp[i] = j;
	}
	j = 0;
	memset(c , 0 , sizeof c);
	for(int i = 1 ; i <= n ; i ++)
	{
		while(j && query(s[i]) != cnt[j + 1]){Clear_s(i - j , i - kmp[j] - 1) ; j = kmp[j];}
		if(query(s[i]) == cnt[j + 1]){j ++ ; add(s[i]);}
		if(j == m) Print[++ tot] = i - m + 1;
	}
	printf("%d\n",tot);
	for(int i = 1 ; i <= tot ; i ++) printf("%d ",Print[i]);
	return 0;
}
```


---

## 作者：lhm_ (赞：8)

题意即为在序列中找出给定排列能匹配相同的位置，这里的匹配相同指的是相对大小关系相同，即离散化后相同。

因为是相对大小关系相同，所以只需考虑每个数所在的排名。可以对给定排列处理出 $num_i$，为位置 $i$ 之前小于位置 $i$ 对应的数的个数，发现对于序列，$num_i$ 相同，相对大小关系就相同。

那么就只用考虑序列和给定排列 $num_i$ 的匹配，这个可以通过 $KMP$ 来实现，用树状数组来维护，匹配成功时在树状数组上加入贡献，失配时在树状数组上删去贡献。

$code:$

```cpp
#include<bits/stdc++.h>
#define maxn 1000010
#define lowbit(x) (x&(-x))
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,m,pos,cnt;
int p[maxn],a[maxn],s[maxn],t[maxn],num[maxn],nxt[maxn],ans[maxn];
void update(int x,int v)
{
    while(x<=m) t[x]+=v,x+=lowbit(x);
}
int query(int x)
{
    int v=0;
    while(x) v+=t[x],x-=lowbit(x);
    return v;
}
void clear()
{
    pos=0;
    for(int i=1;i<=m;++i) t[i]=0;
}
int main()
{
    read(n),read(m),num[n+1]=-1;
    for(int i=1;i<=n;++i)
    {
        int x;
        read(x),p[x]=i;
    }
    for(int i=1;i<=m;++i) read(a[i]),s[i]=a[i];
    sort(s+1,s+m+1);
    for(int i=1;i<=m;++i) a[i]=lower_bound(s+1,s+m+1,a[i])-s;
    for(int i=1;i<=n;++i) num[i]=query(p[i]),update(p[i],1);
    clear();
    for(int i=2;i<=n;++i)
    {
        while(pos&&query(p[i])!=num[pos+1])
        {
            for(int j=i-pos;j<i-nxt[pos];++j) update(p[j],-1);
            pos=nxt[pos];
        }
        if(query(p[i])==num[pos+1]) update(p[i],1),pos++;
        nxt[i]=pos;
    }
    clear();
    for(int i=1;i<=m;++i)
    {
        while(pos&&query(a[i])!=num[pos+1])
        {
            for(int j=i-pos;j<i-nxt[pos];++j) update(a[j],-1);
            pos=nxt[pos];
        }
        if(query(a[i])==num[pos+1]) update(a[i],1),pos++;
        if(pos==n) ans[++cnt]=i-n+1;
    }
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;++i) printf("%d ",ans[i]);
    return 0;
}
```

---

## 作者：Iratis (赞：6)

## 前言

很适合练习 KMP 的一道紫。

本文链表使用链表的做法。

## 解法

首先我们发现读入的序列 $ p $ 并不方便操作，所以我们可以先将 $ p $ 进行改动，从而成为一个模式串 $ v $ 。

然后我们就遇到了一个棘手的问题，应该如何求出每个数之间的大小关系，有部分题解使用了树状数组，而链表同样可以解决。从大到小，记录出每一个数字 $ v_i $ 的前驱 $ v_i-1 $ 在 $ p $ 中的位置，与后继 $ v_i+1 $ 在 $ p $ 中的位置。

最后便可直接使用 KMP 求解，只需更改一下判断两个位置是否能接上的函数：
```cpp
bool check1(int n1,int n2)
{
	bool flag=true;
	if(les[n1]&&val[n2-(n1-les[n1])]>=val[n2])flag=false;
	if(mor[n1]&&val[n2-(n1-mor[n1])]<=val[n2])flag=false;
	return flag;
}
bool check2(int n1,int n2)
{
	bool flag=true;
	if(les[n1]&&h[n2-(n1-les[n1])]>=h[n2])flag=false;
	if(mor[n1]&&h[n2-(n1-mor[n1])]<=h[n2])flag=false;
	return flag;
}
```
最后是完整代码：
```cpp
#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int n,m;
int p[1000001],h[1000001];
int pos[1000001],val[1000001];
int les[1000001],mor[1000001];
int nex[1000001];
int ans,ge[1000001];
struct Node
{
	int next,prev;
}node[1000001];
bool check1(int n1,int n2)
{
	bool flag=true;
	if(les[n1]&&val[n2-(n1-les[n1])]>=val[n2])flag=false;
	if(mor[n1]&&val[n2-(n1-mor[n1])]<=val[n2])flag=false;
	return flag;
}
bool check2(int n1,int n2)
{
	bool flag=true;
	if(les[n1]&&h[n2-(n1-les[n1])]>=h[n2])flag=false;
	if(mor[n1]&&h[n2-(n1-mor[n1])]<=h[n2])flag=false;
	return flag;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&p[i]);
		val[p[i]]=i;
	}
	for(int i=1;i<=m;i++)scanf("%d",&h[i]);
	for(int i=1;i<=n;i++)pos[i]=p[i];
	for(int i=1;i<=n;i++)node[i].next=i+1,node[i].prev=i-1;
	for(int i=n;i>=1;i--)
	{
		les[i]=pos[node[val[i]].prev];
		mor[i]=pos[node[val[i]].next];
		node[node[val[i]].next].prev=node[val[i]].prev;
		node[node[val[i]].prev].next=node[val[i]].next;
	}
	for(int i=1;i<=n;i++)
	{
		int j=nex[i-1];
		while(j>0&&check1(j+1,i)==false)j=nex[j];
		if(check1(j+1,i)==true&&j+1<i)j++;
		nex[i]=j;
	}
	int j=0;
	for(int i=1;i<=m;i++)
	{
		while(j>0&&check2(j+1,i)==false)j=nex[j];
		if(check2(j+1,i)==true)j++;
		if(j==n)
		{
			j=nex[j];
			ge[++ans]=i-n+1;
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=ans;i++)printf("%d ",ge[i]);
	return 0;
}
```

---

## 作者：zplqwq (赞：4)

这道题挺妙的。

首先我们需要一个数组 $a$，存的是转化后的 $p$ 数组。例如，我们将序列 ${2,1,5,3,4}$ 转化为 ${2,1,4,5,3}$ ，分别对应的是 $h$ 数组中的 ${6,3,8,1,2,7}$。

实现如下：

```cpp

	for(int i=1;i<=n;i++)
	{
		p[i]=read();
		a[p[i]]=i;
		pre[i]=i-1;
		net[i]=i+1;
		
	}
```

然后我们维护一个双向链表，用它来求比序列中的某个数大的最小位置和比它小的最大位置。那么，为什么呢？

因为我们考虑一个序列是否合法，不用枚举整个。只需要判断每一个数是否比它前一个位置大，后一个位置小。即大于它的前驱，小于它的后继。

之后就是一个类似 kmp 的思路。

在 kmp 的板子中，我们比对的是子串与要匹配的串是否相同。而现在我们判断的是该子串是否合法。

其余与 kmp 基本一致。

```cpp
	int j=0;
	for(int i=2;i<=n;i++)
	{
		while(j>0 and !check(a,j+1,i)) j=kmp[j];
		if(check(a,j+1,i)) j++;
		kmp[i]=j;
	}
	j=0;
	for(int i=1;i<=m;i++)
	{
		while(j>0 and !check(h,j+1,i)) j=kmp[j];
		if(check(h,j+1,i)) j++;
		if(j==n)
		{
			qwq[++ans]=i-n+1;
			j=kmp[j];
		}
	}
    
```

其余请自行实现。如果有问题，可以私信我要完整代码。



---

## 作者：Iscream2001 (赞：3)

本题第一个题解

这应该算是一道很套路的题吧。。。

显然要求的子串的长度肯定等于给的序列p长度一样。。

然后发现合法的序列的各个元素顺序一定。。

于是应该要想到kmp。。但是普通的kmp无法维护。。发现排名可以转化为小于等于该元素的个数，就可以用树状数组搞了。。

然后就是kmp+树状数组的套路题了。。。

代码就不上了。。只是给个思路。。

---

## 作者：Mihari (赞：2)

# 壹、题目描述 &para;

[传送门 to LOJ](https://loj.ac/p/2507) .

# 贰、题解 &para;

>*也可以去[这里](https://www.cnblogs.com/Arextre/p/15212338.html)看*。
>
>与原文不同的一些地方：
>
>- 删掉了一些不当用语；
>

我们可以通过 $a_i$ 得到某个区间离散化之后应该长得样子，我们记这个样子为 $p$，那么，我们现在考察的就是 $p$ 和 $b$ 中任意长度为 $n$ 的区间离散化之后的匹配。

显然这俩都是排列，于是我们进行的是排列的匹配，这可以使用反序表进行。不难发现过程挺像 $\rm KMP$，那么我们可以先处理出 $p_i$ 的反序表，并且处理出 $\rm KMP$ 使用的 $nxt$ 数组，具体处理该数组，就是考虑在加入 $p_i$ 时，在目前已经匹配到的长度中，比 $p_i$ 大的数个数是否与已经匹配长度 $len$ 的 $d_{len+1}$ 相同，这是可以使用 $\rm BIT$ 维护，如果匹配失败，就暴力将 $[i-len, i-nxt[len]-1]$ 的数字撤回，使用均摊分析，该过程仍然是 $\mathcal O(n)$ 的，由于使用 $\rm BIT$，复杂度达到了 $\mathcal O(n\log n)$.

匹配过程和处理 $nxt$ 基本上是一样的，唯一需要注意的就是在达成一次匹配之后的撤回区间和 $\rm KMP$ 失配时的撤回区间稍微有点不同，至于为什么可以自行思考一下。

# 叁、参考代码 &para;

```cpp
# include <cstdio>
# include <algorithm>
# include <vector>
using namespace std;

# define NDEBUG
# include <cassert>

namespace Elaina {

# define rep(i, l, r) for(int i=(l), i##_end_=(r); i<=i##_end_; ++i)
# define drep(i, l, r) for(int i=(l), i##_end_=(r); i>=i##_end_; --i)
# define fi first
# define se second
# define mp(a, b) make_pair(a, b)
# define Endl putchar('\n')
# define mmset(a, b) memset(a, b, sizeof (a))
# define mmcpy(a, b) memcpy(a, b, sizeof (a))

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;

template <class T> inline T fab(T x) { return x<0? -x: x; }
template <class T> inline void getmin(T& x, const T rhs) { x=min(x, rhs); }
template <class T> inline void getmax(T& x, const T rhs) { x=max(x, rhs); }
template <class T> inline T readin(T x) {
    x=0; int f=0; char c;
    while((c=getchar())<'0' || '9'<c) if(c=='-') f=1;
    for(x=(c^48); '0'<=(c=getchar()) && c<='9'; x=(x<<1)+(x<<3)+(c^48));
    return f? -x: x;
}

template <class T> inline void writc(T x, char s='\n') {
    static int fwri_sta[1005], fwri_ed=0;
    if(x<0) putchar('-'), x=-x;
    do fwri_sta[++fwri_ed]=x%10, x/=10; while(x);
    while(putchar(fwri_sta[fwri_ed--]^48), fwri_ed);
    putchar(s);
}

} using namespace Elaina;

const int maxn=1000000;

int a[maxn+5], b[maxn+5], n, m;
int p[maxn+5], t[maxn+5];

inline void input() {
    n=readin(1), m=readin(1);
    rep(i, 1, n) {
        a[i]=readin(1);
        p[a[i]]=i;
    }
    rep(i, 1, m) t[i]=b[i]=readin(1);
}

inline void getHash() {
    sort(t+1, t+m+1);
    rep(i, 1, m) b[i]=lower_bound(t+1, t+m+1, b[i])-t;
}

/** @warning the upper limit should be set to @p maxn */
namespace saya {

int c[maxn+5];

# define lowbit(i) ((i)&(-(i)))

inline void modify(int i, int v) {
    for(; i; i-=lowbit(i)) c[i]+=v;
}
inline int query(int i, int ret=0) {
    for(; i<=maxn; i+=lowbit(i)) ret+=c[i];
    return ret;
}
inline void clear() {
    rep(i, 1, maxn) c[i]=0;
}

} // using namespace saya;

int nxt[maxn+5], d[maxn+5];
inline void getNxt() {
    rep(i, 1, n) {
        d[i]=saya::query(p[i]);
        saya::modify(p[i], 1);
    }
    saya::clear(); nxt[1]=0, nxt[0]=-1;
    for(int i=2; i<=n; ++i) {
        int len=nxt[i-1];
        while(~len && d[len+1]!=saya::query(p[i])) {
            rep(j, i-len, i-nxt[len]-1) saya::modify(p[j], -1);
            len=nxt[len];
        }
        nxt[i]=len+1, saya::modify(p[i], 1);
    }
}

vector <int> ans;
inline void compare() {
    saya::clear();
    int len=0; // successfully matched length
    rep(i, 1, m) {
        while(~len && d[len+1]!=saya::query(b[i])) {
            rep(j, i-len, i-nxt[len]-1) saya::modify(b[j], -1);
            len=nxt[len];
        } assert(~len);
        ++len, saya::modify(b[i], 1);
        if(len==n) { // a successful match
            /** @warning pay attention to this special fallback interval */
            rep(j, i-len+1, i-nxt[len]) saya::modify(b[j], -1);
            len=nxt[len], ans.push_back(i-n+1);
        }
    }
}

inline void print() {
    writc(ans.size());
    for(auto x: ans) writc(x, ' ');
}

signed main() {
    // freopen("match.in", "r", stdin);
    // freopen("match.out", "w", stdout);
    input();
    getHash();
    getNxt();
    compare();
    print();
    return 0;
}
```

# 肆、关键の地方 &para;

进行排列的比较时，可以考察使用反序表，因为反序表唯一对应每一个排列，至于为什么我记得曾经自己给出过一种构造方法，通过这个构造方法确是可以说明一一映射的关系的。

另外，$\rm KMP$ 也是可以魔改的，该题便是利用了 $\rm KMP$ 判等条件的变化，另外对于 $\rm KMP$ 复杂度分析稍微有点不熟，差点忘记摊还了......

---

