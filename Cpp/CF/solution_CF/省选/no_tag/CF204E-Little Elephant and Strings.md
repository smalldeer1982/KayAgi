# Little Elephant and Strings

## 题目描述

The Little Elephant loves strings very much.

He has an array $ a $ from $ n $ strings, consisting of lowercase English letters. Let's number the elements of the array from 1 to $ n $ , then let's denote the element number $ i $ as $ a_{i} $ . For each string $ a_{i} $ $ (1<=i<=n) $ the Little Elephant wants to find the number of pairs of integers $ l $ and $ r $ $ (1<=l<=r<=|a_{i}|) $ such that substring $ a_{i}[l...\ r] $ is a substring to at least $ k $ strings from array $ a $ (including the $ i $ -th string).

Help the Little Elephant solve this problem.

If you are not familiar with the basic notation in string problems, you can find the corresponding definitions in the notes.

## 说明/提示

Let's assume that you are given string $ a=a_{1}a_{2}...\ a_{|a|} $ , then let's denote the string's length as $ |a| $ and the string's $ i $ -th character as $ a_{i} $ .

A substring $ a[l...\ r] $ $ (1<=l<=r<=|a|) $ of string $ a $ is string $ a_{l}a_{l+1}...\ a_{r} $ .

String $ a $ is a substring of string $ b $ , if there exists such pair of integers $ l $ and $ r $ $ (1<=l<=r<=|b|) $ , that $ b[l...\ r]=a $ .

## 样例 #1

### 输入

```
3 1
abc
a
ab
```

### 输出

```
6 1 3 
```

## 样例 #2

### 输入

```
7 4
rubik
furik
abab
baba
aaabbbababa
abababababa
zero
```

### 输出

```
1 0 9 9 21 30 0 
```

# 题解

## 作者：oisdoaiu (赞：14)

贡献一个用广义$SAM$，不用大力数据结构的做法

把问题分成两部分解决

- 求一个字符串在多少个$a_i$中出现过
- 枚举一个串的一个点$i$，求以$i$为右端点的，在至少$k$个$a_i$中出现过的字符串个数

## Case 1

对于第一个问题，可以建广义$SAM$，记录${a_i}_j$在$SAM$上对应的节点为${pos_i}_j$

然后对于一个串$a_i$来说，它的贡献相当于是所有${pos_i}_j$在$SAM$上构成的一棵虚树，虚树每个节点sz+1

那么具体实现可以用差分，按$dfs$序排序，每个$pos$的$sz$+1，然后每对相邻的$pos$的$lca$的$sz$-1

```cpp
inline bool cmp(const int &u, const int &v){return dfn[u]<dfn[v];}

for(register int i=1; i<=n; i++){
    sort(pos[i]+1,pos[i]+len[i]+1,cmp);
    for(register int j=1; j<=len[i]; j++) sz[pos[i][j]]++;
    for(register int j=1; j<len[i]; j++) sz[lca(pos[i][j],pos[i][j+1])]--;
}
```

然后跑个$dfs$累加差分数组
```cpp

void addmk(int x){
	for(register int u=fst[x]; u; u=edge[u].nxt) 
    	addmk(edge[u].to),
        sz[x] += sz[edge[u].to];
}
```

然后就求出了每个节点的出现次数

## Case 2

考虑一个很暴力的做法
`while(x and sz[x]<K) x = fa(x);`
即找到第一个$sz\geq K$的祖先然后把$len$累加进答案

实际上这个过程可以用倍增去代替，因为越往上走，出现的次数肯定越多。所以用类似于求$lca$的做法，先跳到最上面的一个$sz< K$的位置，然后再跳一步
```cpp
int x = pos[i][j];
for(register int k=Log[dep[x]]; compl k; k--) 
	if(sz[fa[k][x]]<K) x = fa[k][x]; 
if(sz[x]<K) x = fa[0][x];
ans += len(x);
```

完整代码就不放了，关键代码全部已经给出来了


---

## 作者：Crabby_Maskiv (赞：14)

## SA+单调队列

首先转化成$SA$可以解决的问题：对于每一个字符串的每一个后缀，我们找出来自 $k$ 个不同字符串的后缀，使得它们的 $LCP$ 最大，然后这个字符串的答案加上 $LCP$的大小

相当于在统计答案 $(l,r)$ 的个数时，对于每个字符串的每一个 $l$ ，求出 $r$ 最大是多少，然后该字符串的答案加上 $r-l+1$

因此按照套路，我们把这 $n$ 个字符串首尾相接，并且为了防止跨越字符串的子串影响答案，需要在每两个字符中间插入一个间隔符，并且需要**两两不同**

我们发现$LCP$有一个很好的性质：对于两个后缀$i$、$j$，它们在 $SA$ 中的距离越远，$LCP$就越短（结合 “ $LCP$ 是由 $Height$ 数组取区间最小值求得的 ” 可以形象理解）

所以，我们找到的 $k$ 个后缀在SA数组中的排名必须尽可能与该后缀 “近”

如何量化这个 “近” 呢？

我们找出SA数组上所有 “ 包含**恰好** $k$ 个不同字符串中的后缀 ” 的区间，求出这个区间的$LCP$ 作为它的 “价值” ，这样一个后缀的答案就一定在所有包含它的区间中（因为如果包含了大于k个，那么这些后缀一定离它 “ 不够近 ” ），取max即可

用双指针维护，并把这些区间塞到一个vector里，结合维护过程可以得知这样的区间只有$O(N)$个（$N$表示字符串长度和）

然后对于SA数组中的每一个位置求出对应的答案，由于vector里的区间满足左右端点都随着下标递增而单调不降（因为是双指针维护出来的），所以可以抽象成一个区间求max，单调队列维护即可

复杂度$O(N\log N)+O(N)+O(N)=O(N\log N)$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=200005;
int n,m,k;
int sa[N],rk[N],tmp[N<<1],cnt[N],h[N];
int a[N];
int st[N][20],lg[N];
void SA(){
	int i,j,num=m+200;
	for(i=1;i<=n;i++) cnt[rk[i]=a[i]]++;
	for(i=2;i<=num;i++) cnt[i]+=cnt[i-1];
	for(i=1;i<=n;i++) sa[++cnt[rk[i]-1]]=i;
	for(j=1;j<n;j<<=1){
		for(i=0;i<=num;i++) cnt[i]=0;
		for(i=1;i<=n;i++) cnt[rk[i]]++;
		for(i=2;i<=num;i++) cnt[i]+=cnt[i-1];
		for(i=n-j+1;i<=n;i++) tmp[++cnt[rk[i]-1]]=i;
		for(i=1;i<=n;i++)
			if(sa[i]>j) tmp[++cnt[rk[sa[i]-j]-1]]=sa[i]-j;
		for(i=1;i<=n;i++) sa[i]=tmp[i];
		for(i=1;i<=n;i++) tmp[i]=rk[i];
		num=0;
		for(i=1;i<=n;i++)
			rk[sa[i]]=((tmp[sa[i]]==tmp[sa[i-1]]&&tmp[sa[i]+j]==tmp[sa[i-1]+j])?num:++num);
	}
	for(i=1;i<=n;i++){
		if(rk[i]==1) continue;
		h[rk[i]]=max(h[rk[i-1]]-1,0);
		int x=sa[rk[i]-1];
		while(i+h[rk[i]]<=n&&a[i+h[rk[i]]]==a[x+h[rk[i]]]) h[rk[i]]++;
	}
	for(i=1;i<=n;i++) st[i][0]=h[i];
	for(j=1;(1<<j)<n;j++){
		for(i=1;i+(1<<j)-1<=n;i++)
			st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
	}
}
string s[N];
int len[N];
int pos[N];
ll ans[N];
inline int qmin(int l,int r){
	if(l>r) return len[sa[r]];
	int len=lg[r-l+1];
	return min(st[l][len],st[r-(1<<len)+1][len]);
}
int q[N],hd,tl;
struct seg{
	int l,r,w;
	inline seg(int l,int r,int w):l(l),r(r),w(w){}
};
vector<seg> v;
int main(){
	int i,j;
	cin>>m>>k;//我设n为字符串总长，m为字符串个数
	lg[1]=0;for(i=2;i<N;i++) lg[i]=lg[i-1]+(1<<lg[i-1]+1==i);
	for(i=1;i<=m;i++){
		cin>>s[i];int l=s[i].length();
		for(j=0;j<l;j++){
			a[++n]=s[i][j]-'a'+m;
			pos[n]=i;len[n]=l-j;
		}
		a[++n]=i;
	}
	a[n--]=0;
	SA();//求SA,Height
	memset(cnt,0,sizeof(cnt));
	int p=m,ck=0;
    //循环变量从m开始是因为前m-1个一定是分隔符打头，没有意义
	for(i=m;i<=n;i++){//预处理区间以及价值
		int x=pos[sa[i]];//注意枚举顺序是sa[1]~sa[n]，而不是1~n
		if(!cnt[x]) ck++;
		cnt[x]++;
		while(ck>=k){
			if(ck==k) v.push_back(seg(p,i,qmin(p+1,i)));
			if(cnt[pos[sa[p]]]==1){
				if(ck==k) break;
				ck--;
			}
			cnt[pos[sa[p]]]--;p++;
		}
	}
//	for(auto x:v) cout<<x.l<<" "<<x.r<<" "<<x.w<<endl;
	p=0;
	for(i=m;i<=n;i++){//单调队列统计答案
		while(hd<tl&&v[q[hd]].r<i) hd++;
		while(p<v.size()&&v[p].l<=i){
			while(hd<tl&&v[p].w>=v[q[tl-1]].w) tl--;
			q[tl++]=p;
			p++;
		}
		if(hd==tl) continue;
		ans[pos[sa[i]]]+=v[q[hd]].w;
	}
	for(i=1;i<=m;i++) cout<<ans[i]<<" ";
	return 0;
}
```


---

## 作者：KokiNiwa (赞：6)

这是一个 线段树合并+后缀树 好的练手题。[题目链接](https://codeforces.com/contest/204/problem/E)

## 题目叙述

给你一堆字符串，求每一个字符串有多少个二元组$(l,r)$，使得这个字符串的$[l,r]$区间内的字符按顺序形成一个字符串，这个字符串至少在$k$个字符串（就是这堆里的）中出现过。

## 题解

建立广义后缀树，线段树合并，求出每个点子树中有多少中字符串，判断每个节点所代表的子串是否可以。然后对于每个后缀的结尾节点，看那个节点到根节点的路径上有多少个可行的节点。然后累加到答案上。就完了...其实也挺简单的题吧。

## 代码

```cpp
#include <cstdio>
#include <cstring>
#include <map>

using namespace std;

typedef long long ll;
const int maxLen = 2e5 + 5, maxNode = maxLen << 1, inf = 1e8;
int strNum, common;
struct SuffixTree {
	int curLen, actLen, now, tail;
	map<int, int> ch[maxNode];
	int link[maxNode], curStr[maxLen], start[maxNode], len[maxNode], tag[maxNode], end[maxNode];
	SuffixTree() {
		curLen = actLen = 0;
		now = tail = 1;
		len[0] = inf;
	}
	int NewNode(int st, int le, int flag, int ed) {
		link[++tail] = 1;
		start[tail] = st;
		len[tail] = le;
		tag[tail] = flag;
		end[tail] = ed;
		return tail;
	}
	void Extend(int ins, int flag, int ed) {
		curStr[++curLen] = ins;
		++actLen;
		for (int last = 1; actLen; ) {
			while (actLen > len[ch[now][curStr[curLen - actLen + 1]]])
				actLen -= len[now = ch[now][curStr[curLen - actLen + 1]]];
			int &son = ch[now][curStr[curLen - actLen + 1]], val = curStr[start[son] + actLen - 1];
			if (!son || val == ins) {
				link[last] = now;
				last = now;
				if (!son)
					son = NewNode(curLen - actLen + 1, inf, flag, ed);
				else
					break ;
			} else {
				int split = NewNode(start[son], actLen - 1, 0, inf);
				ch[split][val] = son;
				ch[split][ins] = NewNode(curLen, inf, flag, ed);
				start[son] += actLen - 1;
				len[son] -= actLen - 1;
				link[last] = son = split;
				last = split;
			}
			if (now == 1)
				--actLen;
			else
				now = link[now];
		}
	}
	void Check() {
		for (int pos = 1; pos <= curLen; ++pos)
			printf("%c", curStr[pos] + 'a');
		printf("\n");
		for (int id = 1; id <= tail; ++id) {
			printf("id : %d end : %d start : %d len : %d\n", id, end[id], start[id], len[id]);
			for (auto son : ch[id]) {
				printf("	to : %d\n", son.second);
			}
		}
	}
} sft;
char str[maxLen];
struct SegmentTree {
	int tail;
	int ch[maxNode << 5][2], kind[maxNode << 5];
	void PushUp(int now) {
		if (ch[now][0] || ch[now][1]) 
			kind[now] = kind[ch[now][0]] + kind[ch[now][1]];
		else
			kind[now] = 1;
	}
	void Insert(int &now, int lEP, int rEP, int val) {
		if (!now)
			now = ++tail;
		if (lEP == rEP) {
			kind[now] = 1;
			return ;
		}
		int mid = (lEP + rEP) >> 1;
		if (val <= mid)
			Insert(ch[now][0], lEP, mid, val);
		else
			Insert(ch[now][1], mid + 1, rEP, val);
		PushUp(now);
	}
	void Merge(int &to, int from) {
		if (!to || !from) {
			to |= from;
			return ;
		}
		Merge(ch[to][0], ch[from][0]);
		Merge(ch[to][1], ch[from][1]);
		PushUp(to); //因为这里不一定不更新叶子节点，所以 PushUp的时候要小心 
	}
	void dfs(int now) {
		if (!now)
			return ;
		printf("********* now : %d ls : %d rs : %d\n", now, ch[now][0], ch[now][1]);
		dfs(ch[now][0]);
		dfs(ch[now][1]);
	}
} seg;
int can[maxNode], rt[maxNode], sum[maxNode];
ll ans[maxNode];
void dfs1(int now) {
	if (!now)
		return ;
	sft.len[now] = min(sft.len[now], sft.end[now] - sft.start[now]);
	for (auto son : sft.ch[now]) {
		int to = son.second, charac = son.first;
		dfs1(to);
		seg.Merge(rt[now], rt[to]);
	}
	if (sft.tag[now]) {
		seg.Insert(rt[now], 1, strNum, sft.tag[now]);
	}
	if (seg.kind[rt[now]] >= common) {
		can[now] = 1;
	}
}
void dfs2(int now) {
	if (!now)
		return ;
	if (can[now])
		sum[now] += sft.len[now];
	for (auto son : sft.ch[now]) {
		int to = son.second;
		sum[to] = sum[now];
		dfs2(to);
	}
	if (sft.tag[now]) {
		ans[sft.tag[now]] += sum[now];
//		printf("now : %d tag[now] : %d sum : %d\n", now, sft.tag[now], sum[now]);
	}
}

int main() {
	scanf("%d%d", &strNum, &common);
	int tmp = 0;
	for (int sI = 1; sI <= strNum; ++sI) {
		scanf("%s", str + 1);
		int len = strlen(str + 1);
		tmp += len + 1;
		for (int pos = 1; pos <= len; ++pos)
			sft.Extend(str[pos] - 'a', sI, tmp);
		sft.Extend(25 + sI, sI, tmp);
	}
	dfs1(1);
	dfs2(1);
	for (int sI = 1; sI <= strNum; ++sI)
		printf("%I64d\n", ans[sI]);
	return 0;
}
```



注意：

+ 这种线段树合并的写法（就是不传$[l,r]$区间的线段树合并），要在```PushUp```的时候判断是否到了叶子节点，因为```merge```完了之后就```PushUp```不一定不是叶子。

---

## 作者：ez_lcw (赞：3)

# 后缀数组$SA$ + 线段树

好看点的题目：

> 给出$n$个字符串，求每个字符串有多少个子串满足这个子串同时是其他$k$个字符串的子串。

我们可以先将所有串用不同的且不是字母的字符连接起来，再跑一遍后缀数组。

**这样就能把所有串的每一个后缀都排序出来。**

例如对于字符串集合：$\{abab,babb,abaa\}$。

我们就可以这样把它们拼起来：$S=abab1babb2abaa$。

这时我们如果要比较某两个后缀，例如第一个串的后缀$ab$与第二个串的后缀$abb$，它们在$S$中分别是

后缀$ab1babb2abaa$（$ab\color{red}ab1babb2abaa$）

和后缀$abb2abaa$（$abab1b\color{blue}abb2abaa$）。

**那么当我们对$S$进行后缀排序时，一旦比较到连接符或两字符不一样时，就会立即停止排序（因为每一个连接符与所有其它的字符都不一样）。**

**所以按照这种拼法就能所有串的每一个后缀都排序出来。**

把所有后缀排完序后，我们把所有$height$按照$SA$顺序放进线段树里面。

然后我们对于$SA$中的每一个后缀$i$，往后寻找，直到找到某一个串$j$，使得在$SA$中的$i$后缀到$j$后缀来自于至少$k$个原串。

然后找到$i$到$j$中的$height$的最小值，说明这$i$到$j$的后缀中，每一个都是其它$k$个串（包括它自己）的子串。

这一过程我们可以用类似与莫队的方法实现。

代码如下：

```cpp
#include<bits/stdc++.h>
  
#define N 200010
#define INF 0x7fffffffffffffff
  
using namespace std;
 
struct Tree
{
    long long l,r,x;
}t[N<<2];
 
char ch[N];
long long n,nn,m,k,sa[N],x[N],y[N],buckets[N],rk[N],height[N],s[N],ans[N],to[N],vis[N],maxn[N];
 
void build(long long l,long long r,long long k)//建线段树
{
    t[k].l=l,t[k].r=r;
    if(l==r)
    {
        t[k].x=height[l];
        return;
    }
    long long mid=(l+r)>>1;
    build(l,mid,k<<1);
    build(mid+1,r,k<<1|1);
    t[k].x=min(t[k<<1].x,t[k<<1|1].x);
}
 
long long ask(long long k,long long x,long long y)//询问最小值
{
    if(x<=t[k].l&&t[k].r<=y)return t[k].x;
    long long mid=(t[k].l+t[k].r)>>1,ans=INF;
    if(x<=mid)ans=min(ans,ask(k<<1,x,y));
    if(y>mid)ans=min(ans,ask(k<<1|1,x,y));
    return ans;
}
  
void Resort()
{
    for(long long i=1;i<=m;i++)buckets[i]=0;
    for(long long i=1;i<=n;i++)buckets[x[i]]++;
    for(long long i=2;i<=m;i++)buckets[i]+=buckets[i-1];
    for(long long i=n;i>=1;i--)sa[buckets[x[y[i]]]--]=y[i];
}
 
void Suffix_sort()//后缀排序
{
    m=nn+122;
    for(long long i=1;i<=n;i++)x[i]=s[i],y[i]=i;
    Resort();
    for(long long w=1;w<=n;w<<=1)
    {
        long long tot=0;
        for(long long i=n-w+1;i<=n;i++)y[++tot]=i;
        for(long long i=1;i<=n;i++)if(sa[i]>w)y[++tot]=sa[i]-w;
        Resort();
        swap(x,y);
        x[sa[1]]=1,tot=1;
        for(long long i=2;i<=n;i++)x[sa[i]]=((y[sa[i]]==y[sa[i-1]]&&y[sa[i]+w]==y[sa[i-1]+w])?tot:++tot);
        if(tot==n)break;
        m=tot;
    }
}
  
void get_height()//求height
{
    long long k=0;
    for(long long i=1;i<=n;i++)rk[sa[i]]=i;
    for(long long i=1;i<=n;i++)
    {
        if(rk[i]==1)continue;
        if(k)k--;
        long long j=sa[rk[i]-1];
        while(i+k<=n&&j+k<=n&&s[i+k]==s[j+k])k++;
        height[rk[i]]=k;
    }
}
  
int main()
{
    scanf("%lld%lld",&nn,&k);
    if(k==1)//特判k=1的情况
    {
    	for(long long i=1;i<=nn;i++)
    	{
    		scanf("%s",ch+1);
    		long long len=strlen(ch+1);
    		printf("%lld ",(len*(len+1))>>1);
        }
        return 0;
    }
    for(long long i=1;i<=nn;i++)
    {
        scanf("%s",ch+1);
        long long len=strlen(ch+1);
        for(long long j=1;j<=len;j++)s[++n]=ch[j]+nn,to[n]=i;//把这个串拼在S后
        s[++n]=i;
    }
    Suffix_sort();//后缀排序
    get_height();//求height
    build(1,n,1);//根据height建线段树
    long long cnt=0,now=nn;//now就是j
    for(long long i=nn+1;i<n;i++)
    {
        while(now<n){//求出来自于不同的k个串的后缀
            if(cnt>=k)break;
            now++;
            if(!vis[to[sa[now]]])cnt++;
            vis[to[sa[now]]]++;
        }
        if(cnt<k)break;
        long long t=ask(1,i+1,now);//求出height的最小值
        for(long long j=i;j<=now;j++)maxn[j]=max(maxn[j],t);//把i到j每个串都更新一下
        vis[to[sa[i]]]--;//把i串去掉
        if(!vis[to[sa[i]]])cnt--;
    }
    for(long long i=nn+2;i<=n;i++)maxn[i]=max(maxn[i],min(maxn[i-1],height[i]));//类似于前缀和的东东
    for(long long i=nn+1;i<=n;i++)ans[to[sa[i]]]+=maxn[i];//统计答案
    for(long long i=1;i<=nn;i++)printf("%lld ",ans[i]);
    return 0;
}
```


---

## 作者：Fading (赞：3)

可能是我对广义后缀自动机还是不太熟练吧，$10$分钟想到正解但是细节写了很久很久。。。

非常套路的一道题，不知道为什么大家都写后缀数组。。。

我们建出广义后缀自动机，然后我们求出一个节点被多少个字符串覆盖了多少次，暴力跳 parent 树就好了。

有人问为什么不会被卡成$O(n^2)$？我们只要再开一个数组记录这个点上一次被哪一个字符串覆盖，暴力跳的时候如果这个节点已经被这个字符串覆盖过了，就不用跳了。根据广义后缀自动机的性质可以确定复杂度是正确的。

upd：时间复杂度好像是$O(n\sqrt n)$。

~~有本事你们把我卡掉~~

最后我们考虑一个串的前缀节点，分类讨论：

$1:$ 如果这个节点被覆盖次数$\geq k$，贡献就是$\text{len}_u-\text{len}_{pa_u}$。

$2:$ 如果这个节点被覆盖次数$<k$，也许他的 parent 祖先中有覆盖次数$\geq k$的节点。暴力跳 parent 统计贡献，这个可以预处理出来。


其实这是一道水题，我一开始想复杂了。。。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define int long long
#define ljc 998244353
using namespace std;
inline ll read(){
    ll x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();};
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();};
    return x*f;
}
inline char getch(){
    char ch=getchar();
    while (!isalpha(ch)) ch=getchar();
    return ch;
}
int n,m,len[1000001];
char ss[1000001];
namespace sam{
    int cnt,last,Vis[500001],fg[500001],las[500001],pa[500001],c[500001],len[500001];
    int g[500001][26];
    inline void INIT(){
        cnt=last=1;
    }
    inline void insert(int s,int tr){
        if (g[last][s]&&len[last]+1==len[g[last][s]]){
            last=g[last][s];return;
        }
        int pos=last;last=++cnt;int newp=cnt;
        len[newp]=len[pos]+1;
        for (;pos&&!g[pos][s];pos=pa[pos]) g[pos][s]=newp;
        if (!pos) pa[newp]=1;
        else{
            int posx=g[pos][s];
            if (len[posx]==len[pos]+1) pa[newp]=posx;
            else{
                int q=++cnt;len[q]=len[pos]+1;
                for (int i=0;i<26;i++) g[q][i]=g[posx][i]; 
                pa[q]=pa[posx];pa[posx]=pa[newp]=q;
                for (;pos&&g[pos][s]==posx;pos=pa[pos]) g[pos][s]=q;
            }
        }
    }
    inline void update(int x,int y){
        for (;x&&las[x]!=y;x=pa[x]) fg[x]++,las[x]=y;
    }
    void dfs(int u){
    	if (u==1||Vis[u]) return;
    	Vis[u]=1; dfs(pa[u]);c[u]+=c[pa[u]];
    }
    inline void doit(){
        for (int i=1;i<=cnt;i++){
    		c[i]=len[i]-len[pa[i]];
    		if (fg[i]<m) c[i]=0;
        }
        for (int i=1;i<=cnt;i++) dfs(i);
    }
}
vector<char> S[100021];
signed main(){
    n=read(),m=read();
    int tot=0,tt=0;
    sam::INIT();
    for (int i=1;i<=n;i++){
    	scanf("%s",ss+1);
        sam::last=1;
        int L=strlen(ss+1);len[i]=L;
        for (int j=1;j<=L;j++){
        	S[i].push_back(ss[j]);
            sam::insert(ss[j]-'a',i);
        }
    }
    int pos=1;
    for (int i=1;i<=n;i++){
        pos=1;
        for (int j=1;j<=len[i];j++){
            int x=S[i][j-1]-'a';
            pos=sam::g[pos][x];
            sam::update(pos,i);
        }   
    }
    sam::doit();
    for (int i=1;i<=n;i++){
    	pos=1;
    	int ans=0;
        for (int j=1;j<=len[i];j++){
            int x=S[i][j-1]-'a';
            pos=sam::g[pos][x];
            ans+=sam::c[pos];
        }
        printf("%lld ",ans);
    }
    return 0;
}
```


---

## 作者：GoPoux4 (赞：3)

#### 后缀数组+ST表+~~分块~~。

---

合法的子串必须满足至少是k个串的字串。这个要求让我们~~自然而然~~想到一道相似的题 [P5546 [POI2000]公共串](https://www.luogu.com.cn/problem/P5546) ，这道题用后缀数组很容易想到解法。

于是开始后缀数组乱搞。

先将所有字符串用分隔符隔开连接成一个串。注意，这里的分隔符必须**两两不同**，否则求出的 $height$ 数组将会不正确。

在所得串上跑一遍后缀排序，得到 $height$ 数组。

然后我们使用双指针在 $height$ 数组上来枚举合法的区间，左右端点的扩展类似于莫队，当区间内出现了 $K$ 个原串的字串时，此区间合法。

用ST表求出区间内 $height$ 的最小值 $t$，即为区间内所有后缀的最长公共前缀，此时区间内所有后缀的长度为 $t$ 的前缀均为合法字串。

不难发现一个性质：若后缀的长度为 $t$ 的前缀合法，则该后缀长度为 $t' \leq t$ 的前缀均合法。也就是说只需要记录每个后缀最长的合法前缀的长度即可。

需要支持区间对一个值取max，并单点查询。

因为 ~~懒得想其他方法~~ 分块好写，所以这里就直接上分块了。

---

$\text{Code}:$

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define maxn 200005
#define R register
#define INF 0x3f3f3f3f
using namespace std;
typedef long long lxl;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}

char s[maxn];
int N,M,K,a[maxn],n;
lxl ans[maxn];
int SA[maxn],rnk[maxn],tax[maxn],tp[maxn],ht[maxn],belong[maxn];

inline void Qsort()
{
	for(int i=0;i<=M;++i) tax[i]=0;
	for(int i=1;i<=N;++i) ++tax[rnk[i]];
	for(int i=1;i<=M;++i) tax[i]+=tax[i-1];
	for(int i=N;i>=1;--i) SA[tax[rnk[tp[i]]]--]=tp[i];
}

inline void SuffixSort()
{
	M=30+n;
	for(int i=1;i<=N;++i)
		rnk[i]=a[i],tp[i]=i;
	Qsort();
	for(int w=1,p=0;p<N;M=p,w<<=1)
	{
		p=0;
		for(int i=1;i<=w;++i) tp[++p]=N-w+i;
		for(int i=1;i<=N;++i) if(SA[i]>w) tp[++p]=SA[i]-w;
		Qsort();
		swap(tp,rnk);
		rnk[SA[1]]=p=1;
		for(int i=2;i<=N;++i)
			rnk[SA[i]]=(tp[SA[i]]==tp[SA[i-1]]&&tp[SA[i]+w]==tp[SA[i-1]+w]) ? p : ++p;
	}
	for(int i=1,k=0;i<=N;++i)
	{
		if(k) --k;
		while(a[i+k]==a[SA[rnk[i]-1]+k]) ++k;
		ht[rnk[i]]=k;
	}
}

struct ST_Table
{
	int d[maxn][30],lg[maxn];
	inline void init()
	{
		lg[0]=-1;
		for(int i=1;i<=N;++i) d[i][0]=ht[i],lg[i]=lg[i>>1]+1;
		for(int j=1;j<=25;++j)
			for(int i=1;i+(1<<(j-1))<=N;++i)
				d[i][j]=min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
	}
	inline int query(int l,int r)
	{
		int k=lg[r-l+1];
		return min(d[l][k],d[r-(1<<k)+1][k]);
	}
}st;

struct BIG_Block// 大分块 （雾）
{
	#define BN 400
	lxl a[maxn],tag[maxn/BN];
	inline int pos(int x) {return (x-1)/BN+1;}
	inline void Get_Max(int l,int r,lxl d)
	{
		int bl=pos(l),br=pos(r);
		for(int i=bl+1;i<br;++i)
			tag[i]=max(tag[i],d);
		if(bl==br)
			for(int i=l;i<=r;++i)
				a[i]=max(a[i],d);
		else
		{
			for(int i=l;i<=bl*BN;++i)
				a[i]=max(a[i],d);
			for(int i=(br-1)*BN+1;i<=r;++i)
				a[i]=max(a[i],d);
		}
	}
	inline void Get_Val(int x)
	{
		a[x]=max(max(a[x],tag[pos(x)]),min(a[x-1],1ll*ht[x]));
	}
}_9baka;

int cnt[maxn],flag;

inline void Add(int i)
{
	if(!belong[i]) return;
	if(!cnt[belong[i]]) ++flag;
	++cnt[belong[i]];
}

inline void Del(int i)
{
	if(!belong[i]) return;
	--cnt[belong[i]];
	if(!cnt[belong[i]]) --flag;
}

int main()
{
	// freopen("CF204E.in","r",stdin);
	n=read(),K=read();
	if(K==1)
	{
		for(int i=1;i<=n;++i)
		{
			scanf(" %s",s+1);
			int len=strlen(s+1);
			printf("%lld ",1ll*(1+len)*len>>1);
		}
		return 0;
	}
	for(int i=1;i<=n;++i)
	{
		scanf(" %s",s+1);
		int len=strlen(s+1);
		for(int j=1;j<=len;++j)
			a[++N]=s[j]-'a'+1,belong[N]=i;
		a[++N]=26+i;
	}
	SuffixSort();
	st.init();
	for(int i=1,j=0;i<=N;++i)
	{
		while(j<=N&&flag<K) Add(SA[++j])
        // 为了使 t 尽量大，这里只枚举出最短的合法区间
		if(flag<K) break;
        // 如果右端点枚举到边界都不合法，则左端点再缩小还是不合法，直接break
		int t=st.query(i+1,j);
		_9baka.Get_Max(i,j,t);
		Del(SA[i]);
	}
	for(int i=2;i<=N;++i)
		_9baka.Get_Val(i);
        //若前后两后缀有公共前缀，则可能前面的后缀更新后面的后缀的答案
	for(int i=1;i<=N;++i)
		ans[belong[SA[i]]]+=_9baka.a[i];
        // 最长合法前缀的长度即为合法前缀的个数
	for(int i=1;i<=n;++i)
		printf("%lld ",ans[i]);
	return 0;
}

```

---

## 作者：Gmt丶FFF (赞：2)

由于是多个串，还与每个子串的信息有关，很容易想到用 SA 或广义 SAM。这里选择用 SA。

首先先把字符串转化为数组，连接起来，中间用一些不会出现的数。处理出后缀数组与 $height$ 数组，下面简写为 $h$。

所以我们转化后实际上就是求一个后缀中有多长的前缀在 $k$ 个来源不同串的后缀的前缀出现过，答案贡献即为前缀的长度。

对于一个区间 $(l,r)$ 包含了 $k$ 个不同的串中的后缀，那么这些串有公共的长度为 $\min(h_i)\hspace{0.1cm}(l<i\le r)$ 的公共前缀。

可以证明，如果有两个区间 $(l_1,r_1)$，$(l_2,r_2)$，且 $l_1\ge l_2$，$r1 \le r2$，那么 $\min(h_i)>\min(h_j)\hspace{0.1cm}(l_1<i\le r_1,l_2<j\le r_2)$，因为具有单调性。

所以只有刚好包含 $k$ 个来源不同串中的后缀时，才会对这个后缀贡献答案。

那么我们就可以用单调队列维护这个区间，当这个区间达到 $k$ 个来源不同串的后缀时，我们将左端点往右推，并且更新答案，区间最小值用单调队列维护。然而如果多个区间包含一个点，那么求的应该是最大值，因为长度大的符合条件，那么小的也符合条件，那求最大值有很多求法，但线段树一定是最无脑的，所以直接选择线段树。

一个易错点，对于相同的右端点，不能只用最小的包含 $k$ 个来源不同串的后缀的区间更新，因为这样会让这个区间左边的点无法更新到答案，在缩短区间前且满足为 $k$ 个时，可能对于他们这个区间最小则是这个，而如果回退了就不能照顾这些点对应的最小区间（简单来说就是有些值更新不到），所以要边回退边更新。

时间复杂度：$O(n\times \log(n))$。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<queue>
#define int long long
#define pii pair<int,int> 
using namespace std;
const int N=2e5+5;
int T,kt,a[N],b[N],rk[N],sa[N],cnt[N],n,p[N],h[N],vis[N],laz[4*N],f[4*N],sp[N],c[N];
long long ans[N];
char s[N];
deque<pii>q;
inline int ls(int x)
{
	return x<<1;
}
inline int rs(int x)
{
	return x<<1|1;
}
inline void pushup(int x)
{
	f[x]=max(f[ls(x)],f[rs(x)]);
}
inline void fix(int x,int l,int r,int k)
{
	f[x]=max(f[x],k);
	laz[x]=max(laz[x],k);
}
inline void pushdown(int x,int l,int r)
{
	int mid=(l+r)>>1;
	fix(ls(x),l,mid,laz[x]);
	fix(rs(x),mid+1,r,laz[x]);
	laz[x]=0;
}
void update(int x,int l,int r,int nl,int nr,int k)
{
	if(l>=nl&&r<=nr)
	{
		f[x]=max(f[x],k);
		laz[x]=max(laz[x],k);
		return;
	}
	pushdown(x,l,r);
	int mid=(l+r)>>1;
	if(mid>=nl)update(ls(x),l,mid,nl,nr,k);
	if(mid<nr)update(rs(x),mid+1,r,nl,nr,k);
	pushup(x);
}
void getans(int x,int l,int r)
{
	if(l==r)
	{
		//cout<<l<<" "<<sa[l]<<" "<<p[sa[l]]<<" "<<f[x]<<endl;
		ans[p[sa[l]]]+=f[x];
		return;
	}
	pushdown(x,l,r);
	int mid=(l+r)>>1;
	getans(ls(x),l,mid);
	getans(rs(x),mid+1,r);
}
signed main()
{
	scanf("%lld%lld",&T,&kt);
	int m=26;
	for(int i=1;i<=T;i++)
	{
		scanf("%s",s+1);
		int len=strlen(s+1);
		for(int j=1;j<=len;j++)a[++n]=s[j]-'a',p[n]=i,sp[n]=a[n];
		for(int j=n-len+1;j<=n;j++)c[j]=n-j+1;
		a[++n]=i+26,sp[n]=a[n],m=i+26;
		if(kt==1)printf("%lld ",len*(len+1)/2);
	}
	if(kt==1)return 0;
	sp[n+1]=2e9;
	for(int i=1;i<=n;i++)cnt[a[i]]++;
	for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
	for(int i=n;i>0;i--)sa[cnt[a[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int num=0;
		for(int i=n-k+1;i<=n;i++)b[++num]=i;
		for(int i=1;i<=n;i++)if(sa[i]>k)b[++num]=sa[i]-k;
		for(int i=0;i<=m;i++)cnt[i]=0;
		for(int i=1;i<=n;i++)cnt[a[i]]++;
		for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
		for(int i=n;i>0;i--)sa[cnt[a[b[i]]]--]=b[i];
		swap(a,b);
		a[sa[1]]=1;
		num=1;
		for(int i=2;i<=n;i++)
		{
			if(b[sa[i]]==b[sa[i-1]]&&b[sa[i]+k]==b[sa[i-1]+k])a[sa[i]]=num;
			else a[sa[i]]=++num;
		}
		if(num==n)break;
		m=num;
	}
	int r=0;
	//for(int i=1;i<=n;i++)cout<<sa[i]<<" ";
	//cout<<endl;
	for(int i=1;i<=n;i++)rk[sa[i]]=i;
	for(int i=1;i<=n;i++)
	{
		if(rk[i]==1)continue;
		if(r)r--;
		int j=sa[rk[i]-1];
		while(j+r<=n&&i+r<=n&&sp[i+r]==sp[j+r])++r;
		h[rk[i]]=r;
		//cout<<i<<" "<<r<<endl;
	}
	int sum=0,l=1;
	for(int i=1;i<=n;i++)
	{
		if(!vis[p[sa[i]]])sum++;
		vis[p[sa[i]]]++;
		while(!q.empty()&&q.back().second>=h[i])q.pop_back();
		q.push_back({sa[i],h[i]});
		while(sum>=kt)
		{
			if(!q.empty()&&sa[l]==q.front().first)q.pop_front();
			update(1,1,n,l,i,q.front().second);
			if(sum==kt&&vis[p[sa[l]]]==1)break;
			vis[p[sa[l]]]--;
			if(!vis[p[sa[l]]])sum--;
			l++;
			
		}//cout<<l<<" "<<i<<" "<<sum<<" "<<c[sa[i]]<<" "<<q.front().second<<endl;
		
	}
	getans(1,1,n);
	for(int i=1;i<=T;i++)printf("%I64d ",ans[i]); 
	return 0;
}
/*
2 2
aaab
aaababa
*/
```


---

## 作者：KellyFrog (赞：2)

~~SAM 个啥~~

每个串内可以双指针，现在问题转化为一个子串 $S'$ 在几个 $S_i$ 中出现

考虑 SA，二分出 $height\ge |S'|$ 的区间，把每后缀所属的串看成一种颜色，就是区间数颜色，需要在线，把离线的树状数组做法扔到主席树上就行了，令 $m=\sum |S_i|$，复杂度 $O(m\log m)$

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second

#if __cplusplus < 201703L
#define register
#else
#define rg
#endif

#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)
#define OK cerr << "OK!\n"

namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin),
		       (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		char ch = ' ';
		int ps = 1;
		while (!isdigit(ch) && ch != '-') ch = getchar();
		if (ch == '-') ps = -1, ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		x *= ps;
		qread(ls...);
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if (oS == oT) flush();
	}
	template <typename T>
	inline void qwrite(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x < 10) return putchar('0' + x), void();
		qwrite(x / 10), putchar('0' + (x % 10));
	}

	template <typename T>
	inline void qwrite(T x, char ch) {
		qwrite(x), putchar(ch);
	}
};  // namespace fastio

const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;
// const int mod =2017;

template <typename T>
inline void chkadd(T& x, T y) {
	x = x + y >= mod ? x + y - mod : x + y;
}
template <typename T>
inline void chkadd(T& x, T y, T z) {
	x = y + z >= mod ? y + z - mod : y + z;
}
template <typename T>
inline void chkmns(T& x, T y) {
	x = x - y < 0 ? x - y + mod : x - y;
}
template <typename T>
inline void chkmns(T& x, T y, T z) {
	x = y - z < 0 ? y - z + mod : y - z;
}
template <typename T>
inline void chkmax(T& x, T y) {
	x = x < y ? y : x;
}
template <typename T>
inline void chkmax(T& x, T y, T z) {
	x = y > z ? y : z;
}
template <typename T>
inline void chkmin(T& x, T y) {
	x = x < y ? x : y;
}
template <typename T>
inline void chkmin(T& x, T y, T z) {
	x = y < z ? y : z;
}

ll qpow(ll x, ll p) {
	ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

/* template ends here */

const int N = 2e5 + 5;

int sa[N], rk[N], h[N], sbelong[N];
int st[21][N], lg2[N], nn;
pair<pair<int, int>, int> cur[N], tmp[N];
char SS[N];
string S[N];
int n, k;
int stp[N];
int last[N];
int rt[N], lson[N << 6], rson[N << 6], sum[N << 6], nodecnt;

inline void add(int& cur, int old, int p, int x, int l, int r) {
  cur = ++nodecnt;
  lson[cur] = lson[old];
  rson[cur] = rson[old];
  sum[cur] = sum[old] + x;
  if(l == r) return ;
  int mid = l + r >> 1;
  if(p <= mid) add(lson[cur], lson[old], p, x, l, mid);
  else add(rson[cur], rson[old], p, x, mid + 1, r);
}

inline int querysum(int cur, int ql, int qr, int l, int r) {
  if(!cur) return 0;
  if(ql <= l && r <= qr) return sum[cur];
  int mid = l + r >> 1;
  int res = 0;
  if(ql <= mid) res += querysum(lson[cur], ql, qr, l, mid);
  if(mid < qr) res += querysum(rson[cur], ql, qr, mid + 1, r);
  return res;
}

inline void rsort() {
  static int pre[N];
  static const int m = 2e5;
  memset(pre, 0, sizeof pre);
  rep(i, 1, nn) pre[cur[i].fi.se]++;
  rep(i, 1, m) pre[i] += pre[i-1];
  per(i, 1, nn) tmp[pre[cur[i].fi.se]--] = cur[i];
  


  memset(pre, 0, sizeof pre);
  rep(i, 1, nn) pre[cur[i].fi.fi]++;
  rep(i, 1, m) pre[i] += pre[i-1];
  per(i, 1, nn) cur[pre[tmp[i].fi.fi]--] = tmp[i];

  int p = 1;
  rk[cur[1].se] = 1;
  rep(i, 2, nn) {
    if(cur[i].fi != cur[i-1].fi) p++;
    rk[cur[i].se] = p;
  }
}

inline void SA() {
  rep(i, 1, nn) rk[i] = SS[i];
  for(int len = 1; len / 2 <= nn; len <<= 1) {
    rep(i, 1, nn) cur[i] = mp(mp(rk[i], i+len > nn ? 0 : rk[i+len]), i);
    rsort();
  }
  rep(i, 1, nn) sa[rk[i]] = i;
}

inline void buildheight() {
  int p = 0;
  rep(i, 1, nn) {
    if(p) p--;
    while(i+p <= nn && sa[rk[i]-1]+p <= nn && SS[i+p] == SS[sa[rk[i]-1]+p]) p++;
    h[rk[i]] = p;
  }
}

inline void buildST() {
  lg2[0] = -1;
  rep(i, 1, nn) lg2[i] = lg2[i>>1] + 1;
  rep(i, 1, nn) st[0][i] = h[i];
  rep(j, 1, 19) rep(i, 1, nn) {
    if(i + (1 << j) - 1 > nn) continue;
    st[j][i] = min(st[j-1][i], st[j-1][i+(1<<j-1)]);
  }
}

inline int query(int L, int R) {
  if(L > R) return 0;
  return min(st[lg2[R-L+1]][L], st[lg2[R-L+1]][R-(1<<lg2[R-L+1])+1]);
}
inline int lcp(int x, int y) {
  if(x == y) return n + 1;
  x = rk[x], y = rk[y];
  if(x > y) swap(x, y);
  return query(x + 1, y);
}

inline void getrange(int s, int len, int& resL, int& resR) {
  int p = rk[s];
  resL = resR = p;
  {
    int L = 1, R = p-1;
    while(L <= R) {
      int mid = L + R >> 1;
      if(lcp(sa[mid], sa[p]) >= len) resL = mid, R = mid - 1;
      else L = mid + 1;
    }
  }
  {
    int L = p+1, R = nn;
    while(L <= R) {
      int mid = L + R >> 1;
      if(lcp(sa[mid], sa[p]) >= len) resR = mid, L = mid + 1;
      else R = mid - 1;
    }
  }
}

inline bool check(int s, int t, int id) {
  int p = stp[id] + s - 1;
  int len = t - s + 1;
  int L = -1, R = -1;
  getrange(p, t - s + 1, L, R);
  return querysum(rt[R], L, R, 1, nn) >= k;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> n >> k;
  rep(i, 1, n) {
    stp[i] = nn + 1;
    cin >> S[i];
    rep(j, 0, (int)S[i].length()-1) {
      SS[++nn] = S[i][j];
      sbelong[nn] = i;
    }
    SS[++nn] = '$';
    sbelong[nn] = 0;
  }


  rep(i, 1, n) S[i] = ' ' + S[i];
  
  SA();
  buildheight();
  buildST();

  rep(i, 1, nn) {
    int p = sa[i];
    if(sbelong[p]) {
      if(last[sbelong[p]]) {
	add(rt[i], rt[i-1], last[sbelong[p]], -1, 1, nn);
	add(rt[i], rt[i], i, 1, 1, nn);
      } else {
	add(rt[i], rt[i-1], i, 1, 1, nn);
      }
    } else rt[i] = rt[i-1];
    last[sbelong[p]] = i;
  }
  rep(i, 1, n) {
    int R = 0;
    ll ans = 0;
    rep(L, 1, S[i].length()-1) {
      R = max(R, L-1);
      while(R+1 < S[i].length() && check(L, R+1, i)) R++;
      ans += max(0, R - L + 1);
    }
    cout << ans << " \n"[i == n];
  }
  return 0;
}
```

---

## 作者：chenxia25 (赞：2)

考虑 SA，把串们用互不相同的分隔符连起来然后求。

很自然的想到，枚举每个串的每个位置（按照 SA 的顺序）作为左端点贡献。那么答案显然是所有串与它的最大后缀 lcp 中第 $k$ 大的。而某个串与该后缀的最大后缀 lcp 怎么求呢，显然只可能是左右两边第一个属于该串的后缀到该位置的 $hi$ 的 $\min$，因为再往两端扩展是单调的，这是 SA 的一个常用的性质。

如果该位置等于 $1$ 的话，那就不可能往左边，那就很好办了，就找右边第一个包含 $k$ 个不同串的位置然后贡献就可以了，决策是唯一的。但是普遍情况下，每个串是有两个位置可以选的。对于每个位置都对每个串算出贡献然后排序吗？这就不会维护了。

我自己 yy 出来了一个线根对的方法。考虑根号分治，小串预处理，大串实时枚举。预处理的话，就在 SA 中的每两个相邻位置之间的变化量是和该串长度成线性的，所以线根；实时枚举就比较简单了，也是线根；还要用一个 `set` 维护 $k$ 大值。非常难写，常数也很大，没写了。

事实上遇到这种难维护的东西，可以换一个角度思考。我们不看单串们这种琐碎的东西了，我们考虑往两端扩展到哪里。那么随便推一推就会发现，对于每种往两端扩展的方案，贡献是两端之间的 $hi$ 的 RMinQ。然后就把所有方案给 $\max$ 起来即可。

不难发现，最优的方案一定**恰好**包含 $k$ 个不同的串，容易反证。我们考虑预处理出来这些区间们，然后很简单的差分一下 `multiset` 扫一遍。但是又发现，这些区间的个数很容易被卡到平方，例如 $1\to n,1\to n,1\to n$。我们考虑对这种情况该如何解决。

1. 该位置在中间的话，那显然左右两段各伸出去 $0$ 是最好的；
1. 在两边两段的话，那显然是另一段伸出去 $0$ 最好。

综上可以得出结论，我们只需要预处理那些，往左极小或往右极小的区间。这显然是线性的，正反两遍 two-pointers 即可。

**_[code](https://www.luogu.com.cn/paste/efbd0qi1)_**

---

## 作者：lory1608 (赞：2)

本题是一道很简单的题目，考查对于后缀数组或后缀自动机(后缀树)的应用。

本题很显然可以用后缀数组$\Theta(n\log n)$解。

但是对于不需要多少思维含量的后缀自动机$+$线段树合并，可以不需要多少思维含量的$\Theta(n\log n)$写。

所以我用了后缀自动机。

首先对于所有串建立**广义后缀自动机**，然后对于每个节点所表示的一些串，在后缀自动机的该节点的线段树上插入。

然后在$dfs$一遍，进行线段树合并，把所有出现次数$\geq k$的节点标记一下。

对于询问，如果这个节点是被标记的，对于该节点所代表的所有串的答案可以加上$len_u$。如果该节点没有被标记，那么他的贡献是他的$parent$链上长度最长的后缀的$len$。

由于答案最大为$\dfrac{n\times (n-1)}{2}$，所以一定要开**long long**。

时间复杂度$\Theta(n\log n)$。
```cpp
#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<bitset>
#define ll long long
#define ull unsigned long long
using namespace std;
const int maxn=1e5+5;
int n,belong[maxn<<1],p[maxn<<1],fa[maxn<<1],last=1,tot=1,sz,k,rt[maxn<<1],len[maxn<<1];
char s[maxn];
bool dp[maxn<<1];
ll ans[maxn<<1];
int las[maxn<<1];
vector<int>temp[maxn<<1],vec[maxn<<1];
struct edge
{
	int v,nxt;
	edge(){}
	edge(int vv,int nn)
	{
		v=vv,nxt=nn;
	}
}e[maxn<<2];
inline void add(int u,int v)
{
	e[++sz]=edge(v,p[u]);
	p[u]=sz;
}
struct SAM
{
	int son[maxn<<1][26];
	inline void insert(int c)
	{
		int np=++tot,p=last;
		len[np]=len[p]+1,last=np;
		while(p&&!son[p][c])son[p][c]=np,p=fa[p];
		if(p==0)fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1)fa[np]=q;
			else
			{
				int nq=++tot;
				len[nq]=len[p]+1;
				fa[nq]=fa[q];
				fa[np]=fa[q]=nq;
				memcpy(son[nq],son[q],sizeof(son[q]));
				while(p&&son[p][c]==q)son[p][c]=nq,p=fa[p];
			}
		}
	}
}sam;
struct seg
{
	int tot;
	int sum[maxn*40],ls[maxn*40],rs[maxn*40];
	seg(){tot=0;}
	inline void pushup(int u)
	{
		sum[u]=sum[ls[u]]+sum[rs[u]];
	}
	inline void update(int &u,int l,int r,int x)
	{
		if(!u)u=++tot;
		if(l==r)
		{
			sum[u]=1;
			return ;
		}
		else
		{
			int mid=(l+r)>>1;
			if(x<=mid)update(ls[u],l,mid,x);
			else update(rs[u],mid+1,r,x);
			pushup(u);
		}
	}
	inline int query(int u,int l,int r,int x,int y)
	{
		if(!u)return 0;
		else if(x<=l&&y>=r)return sum[u];
		else
		{
			int mid=(l+r)>>1;
			int ret=0;
			if(x<=mid)ret+=query(ls[u],l,mid,x,y);
			if(y>mid)ret+=query(rs[u],mid+1,r,x,y);
			return ret;
		}
	}
	inline int merge(int x,int y,int l,int r)
	{
		int u=++tot;
		if(!x||!y)return x+y;
		if(l==r)
		{
			sum[u]=sum[x]|sum[y];
			return u;
		}
		else
		{
			int mid=(l+r)>>1;
			ls[u]=merge(ls[x],ls[y],l,mid);
			rs[u]=merge(rs[x],rs[y],mid+1,r); 
			pushup(u);
		}
		return u;
	}
}tree;
struct Trie
{
	int son[maxn][26],tot;
	Trie(){tot=0;}
	inline void insert(char *s,int typ)
	{
		int now=0;
		int len=strlen(s+1);
		for(int i=1;i<=len;++i)
		{
			if(!son[now][s[i]-'a'])son[now][s[i]-'a']=++tot;
			now=son[now][s[i]-'a'];
			temp[now].push_back(typ);
		}
	}
	inline void dfs(int u,int now)
	{
		for(int i=0;i<=25;++i)
		{
			if(son[u][i])
			{
				last=now;
				sam.insert(i);
				dfs(son[u][i],last);
			}
		}
		for(int i=0;i<temp[u].size();++i)tree.update(rt[now],1,n,temp[u][i]);
		vec[now]=temp[u];
	}
}trie;
inline void dfs(int u)
{
	for(int i=p[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		dfs(v);
		rt[u]=tree.merge(rt[u],rt[v],1,n);
		dp[u]|=dp[v];
	}
	if(dp[u]==0)dp[u]|=(tree.query(rt[u],1,n,1,n)>=k);
}
inline void dfs2(int u,ll res)
{
	for(int i=p[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		if(dp[v])dfs2(v,len[v]);
		else dfs2(v,res);
	}
	for(int i=0;i<vec[u].size();++i)
	{
		ans[vec[u][i]]+=res;
	}
}
int main()
{
	last=tot=1;
	memset(p,-1,sizeof(p));
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i)
	{
		scanf("%s",s+1);
		trie.insert(s,i);
	}
	trie.dfs(0,1);
	for(int i=tot;i>=1;--i)add(fa[i],i);
	dfs(1);
	dfs2(1,0);
	for(int i=1;i<=n;++i)printf("%lld ",ans[i]);
	printf("\n");
	return 0;
}
```

---

