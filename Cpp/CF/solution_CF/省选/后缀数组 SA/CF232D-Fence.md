# Fence

## 题目描述

John Doe has a crooked fence, consisting of $ n $ rectangular planks, lined up from the left to the right: the plank that goes $ i $ -th $ (1<=i<=n) $ (from left to right) has width 1 and height $ h_{i} $ . We will assume that the plank that goes $ i $ -th $ (1<=i<=n) $ (from left to right) has index $ i $ .

A piece of the fence from $ l $ to $ r $ $ (1<=l<=r<=n) $ is a sequence of planks of wood with indices from $ l $ to $ r $ inclusive, that is, planks with indices $ l,l+1,...,r $ . The width of the piece of the fence from $ l $ to $ r $ is value $ r-l+1 $ .

Two pieces of the fence from $ l_{1} $ to $ r_{1} $ and from $ l_{2} $ to $ r_{2} $ are called matching, if the following conditions hold:

- the pieces do not intersect, that is, there isn't a single plank, such that it occurs in both pieces of the fence;
- the pieces are of the same width;
- for all $ i $ $ (0<=i<=r_{1}-l_{1}) $ the following condition holds: $ h_{l1+i}+h_{l2+i}=h_{l1}+h_{l2} $ .

John chose a few pieces of the fence and now wants to know how many distinct matching pieces are for each of them. Two pieces of the fence are distinct if there is a plank, which belongs to one of them and does not belong to the other one.

## 样例 #1

### 输入

```
10
1 2 2 1 100 99 99 100 100 100
6
1 4
1 2
3 4
1 5
9 10
10 10
```

### 输出

```
1
2
2
0
2
9
```

# 题解

## 作者：xtx1092515503 (赞：4)

SA解法。

------

考虑对于一次询问 $[l,r]$，另一个区间 $[L,R]$ 能够符合该询问，其必须满足如下条件：

1. $r-l=R-L$

有了这个条件，我们便可以根据 $L$ 来唯一确定可能合法的 $R$ 了。

2. $[l,r]\cup[L,R]=\varnothing$

有了这个条件，我们便可以进一步得出所有可能合法的 $L$ 的位置：其必位于区间 $\Big[1,l-(r-l+1)\Big]\cup[r+1,n]$ 中。

3. $R\leq n$

这个条件对我们没有任何帮助。

4. $\forall i\in[0,r-l],h_{l+i}+h_{L+i}=h_l+h_L$

首先，依照该条件，我们发现对于所有 $l=r$ 的询问，其答案都只会是 $n-1$（因为所有 $L\neq l$ 都是合法的 $L$）。故我们接下来只考虑 $l<r$ 的情形。

然后，如果我们把原序列差分，定义差分后的数组 $s_i=h_{i+1}-h_i$（明显，$s$ 数组的长度应为 $n-1$，下标是 $1\sim n-1$），则上述条件，可以被等价于

$$\forall i\in[0,r-l-1],s_{l+i}=-s_{L+i}$$

即在 $s$ 中，$l$ 开头、长度为 $r-l$ 的子串，与 $L$ 开头、长度为 $r-l$ 的子串，每个位置上的数互为相反数。

我们考虑将 $s$ 复制一份所有数都是其相反数的串，然后将该新串接在原串后面，中间插上一个从未出现过的字符跑SA（明显，应该先把数组中所有东西离散化掉，不然没法跑桶排）。于是，现在得到的大串，下标是 $1\sim2n-1$，其中 $1\sim n-1$ 来自于原串，$n+1\sim 2n-1$ 来自于新串，位置 $n$ 是分隔符。

后缀排序后，我们找到以位置 $n+l$ 开头的后缀，其开头 $r-l$ 位即为我们需要的东西的相反数。在后缀数组里该后缀两边二分出所有与其 $\text{LCP}$ 长度不小于 $r-l$ 的后缀，即为所有合法后缀的备选。

接着，我们发现，我们需要的，就是在上述区间中，符合我们之前要求（来自 $\Big[1,l-(r-l+1)\Big]\cup[r+1,n]$ 内）的后缀的数量。

这是一个二维数点问题，直接上个线段树或是主席树之类随随便便跑一下就出来了。

时间复杂度 $O(n\log n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100100],s[200100],m,N,sa[200100],ht[200100],rk[200100],buc[200100],st[200100][20],LG[200100];
vector<int>v;
void SA(){
	for(int i=1;i<=N;i++)buc[rk[i]=s[i]]++;
	for(int i=1;i<=m;i++)buc[i]+=buc[i-1];
	for(int i=N;i;i--)sa[buc[rk[i]]--]=i;
	for(int k=1;k<=N;k<<=1){
		int num=0;
		for(int i=N-k+1;i<=N;i++)ht[++num]=i;
		for(int i=1;i<=N;i++)if(sa[i]>k)ht[++num]=sa[i]-k;
		for(int i=1;i<=m;i++)buc[i]=0;
		for(int i=1;i<=N;i++)buc[rk[ht[i]]]++;
		for(int i=1;i<=m;i++)buc[i]+=buc[i-1];
		for(int i=N;i;i--)sa[buc[rk[ht[i]]]--]=ht[i],ht[i]=0;
		swap(ht,rk),rk[sa[1]]=num=1;
		for(int i=2;i<=N;i++)rk[sa[i]]=(ht[sa[i]]==ht[sa[i-1]]&&ht[sa[i]+k]==ht[sa[i-1]+k]?num:++num);
		m=num;
		if(num==N)break;
	}
	for(int i=1;i<=N;i++)ht[i]=0;
	for(int i=1,k=0;i<=N;i++){
		if(rk[i]==1)continue;
		if(k)k--;
		int j=sa[rk[i]-1];
		while(i+k<=N&&j+k<=N&&s[i+k]==s[j+k])k++;
		ht[rk[i]]=k;
	}
	for(int i=2;i<=N;i++)LG[i]=LG[i>>1]+1;
	for(int i=1;i<=N;i++)st[i][0]=ht[i];
	for(int j=1;j<=LG[N];j++)for(int i=1;i+(1<<j)-1<=N;i++)st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int LCP(int x,int y){//the LCP between two suffixes, ranked x and y in the sa array.
	if(x>y)swap(x,y);
	x++;
	int k=LG[y-x+1];
	return min(st[x][k],st[y-(1<<k)+1][k]);
}
void range(int l,int r,int &L,int &R){
	int x=rk[n+l],len=r-l;
	l=1,r=x;
	while(l<r){
		int mid=(l+r)>>1;
		if(LCP(mid,x)>=len)r=mid;
		else l=mid+1;
	}
	L=r;
	l=x,r=N;
	while(l<r){
		int mid=(l+r+1)>>1;
		if(LCP(mid,x)>=len)l=mid;
		else r=mid-1;
	}
	R=l;
}

#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
int sum[400100];
void modify(int x,int l,int r,int P){
	if(l>P||r<P)return;
	sum[x]++;
	if(l!=r)modify(lson,l,mid,P),modify(rson,mid+1,r,P);
}
int query(int x,int l,int r,int L,int R){
	if(l>R||r<L)return 0;
	if(L<=l&&r<=R)return sum[x];
	return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
}

int ql[100100],qr[100100],res[100100];
vector<int>u[200100];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<n;i++)s[i]=a[i+1]-a[i],s[n+i]=-s[i],v.push_back(s[i]),v.push_back(s[n+i]);
	sort(v.begin(),v.end()),v.resize(m=unique(v.begin(),v.end())-v.begin());
	for(int i=1;i<n;i++)s[i]=lower_bound(v.begin(),v.end(),s[i])-v.begin()+1,s[n+i]=lower_bound(v.begin(),v.end(),s[n+i])-v.begin()+1;
	s[n]=++m,N=2*n-1,SA();
//	for(int i=1;i<=N;i++)printf("%2d ",i);puts("");
//	for(int i=1;i<=N;i++)printf("%2d ",s[i]);puts("");
//	for(int i=1;i<=N;i++)printf("%2d ",sa[i]);puts("");
//	for(int i=1;i<=N;i++)printf("%2d ",rk[i]);puts("");
	scanf("%d",&m);
	for(int i=1,l,r;i<=m;i++){
		scanf("%d%d",&l,&r);
		if(l==r){res[i]=n-1;continue;}
		int L,R;range(l,r,L,R);
		u[L-1].push_back(-i),u[R].push_back(i);
		ql[i]=l-(r-l+1),qr[i]=r+1;
//		printf("%d %d %d %d\n",L,R,ql[i],qr[i]);
	}
	for(int i=1;i<=N;i++){
		if(sa[i]<n)modify(1,1,n,sa[i]);
		for(auto x:u[i]){
			int now=query(1,1,n,1,ql[abs(x)])+query(1,1,n,qr[abs(x)],n);
			if(x>0)res[x]+=now;
			else res[-x]-=now;
		}
	}
	for(int i=1;i<=m;i++)printf("%d\n",res[i]);
	return 0;
}
```



---

## 作者：居然有个高手 (赞：3)

来个在线的 SA 做法。

题目中的三个条件分别带来三个信息：

1.$r_2-l_2 = r_1-l_1$

则我们可以通过 $l_2$ 确定唯一的 $r_2$。问题转化为寻找一个合法的 $l_2$。

2.$[l_1,r_1]$ 与 $[l_2,r_2]$ 没有交集。

这意味着 $l_2 \in [1,l_l-(r_1-l_1+1)] \cup [r_1+1,n-(r_1-l_1)]$。

3. $\forall i \in [1,r_1-l_1],h_{l_1+i}+h_{l_2+i} = h_{l_1}+h_{l_2}$

令 $a_i = h_{i+1}-h_i$（显然，此处 $i \in [1,n-1]$）。

则对于所有合法的 $l_2$，必然满足 $\forall i \in [0,r_1-l_1-1],a_{l_1+i} = -a_{l_2+i}$。（即二者差分数组对应位置均为相反数）

当 $l_1=r_1$ 时，答案为 $n-1$。

对于剩下的询问，我们可以用 SA 维护。令 $a_{i+n-1}=-a_i$，在求出 $SA$、$rnk$ 与 $height$ 等一众数组后，建立一棵以 $rnk$ 为下标的主席树，下标为 $i$ 的主席树维护后缀 $[n,2n-2]$ 在 $rnk{1...i}$ 内出现了几次。注意，后缀 $[n,2n-2]$ 一一对应**原数列中**的 $[1,n-1]$。

查询时二分找出一段最长的区间 $[l,r]$，满足 $lcp(l...r) >= r_1-l_1$ 且 $sa_{l_1} \in [l,r]$。则我们就可以分别在下标为 $r$ 与 $l-1$ 的主席树中查询**原数列中** $[1,l_l-(r_1-l_1+1)] \cup [r_1+1,n-(r_1-l_1)]$ 在本主席树中总共出现几次，记作 $ans$。则答案为 $ans_r-ans_{l-1}$。至此，本题得到解决。

时间复杂度：$O((n+q)\log n)$，空间复杂度：$O(n\log n)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int len,n,q,s[N],p[N],a[N],m,tax[N],sa[N],tp[N],rnk[N],st[20][N],lg[N],rt[N],tot;
inline void sort(){
	for(int i = 0;i<=m;i++)tax[i]=0;
	for(int i = 1;i<=n;i++)tax[rnk[i]]++;
	for(int i = 1;i<=m;i++)tax[i]+=tax[i-1];
	for(int i = n;i>=1;i--)sa[tax[rnk[tp[i]]]--]=tp[i];
}
inline int query(int x,int y){
	if(x>y)return N*2;
	int k=lg[y-x+1];
	return min(st[k][x],st[k][y-(1<<k)+1]);
}
struct tree{
	int lc,rc,k;
}t[N*30];
inline void insert(int&p,int q,int l,int r,int pos){
	p=++tot;t[p]=t[q];t[p].k++;
	if(l==r)return ;
	int mid=l+r>>1;
	if(pos<=mid)insert(t[p].lc,t[q].lc,l,mid,pos);
	else insert(t[p].rc,t[q].rc,mid+1,r,pos);
}
inline int query(int p,int q,int l,int r,int ql,int qr){
	if(!p||ql>qr)return 0;
	if(ql<=l&&r<=qr)return t[p].k-t[q].k;
	int mid=l+r>>1,ans=0;
	if(ql<=mid)ans=query(t[p].lc,t[q].lc,l,mid,ql,qr);
	if(qr>mid)ans+=query(t[p].rc,t[q].rc,mid+1,r,ql,qr);
	return ans;
}
int main(){
	scanf("%d",&len);
	for(int i = 1;i<=len;i++)scanf("%d",&s[i]);
	for(int i = 1;i<len;i++)a[++n]=s[i+1]-s[i],p[n]=a[n];
	for(int i = 1;i<len;i++)++n,a[n]=-a[n-len+1],p[n]=a[n];
	sort(p+1,p+n+1);m=unique(p+1,p+n+1)-p-1;
	for(int i = 1;i<=n;i++)rnk[i]=a[i]=lower_bound(p+1,p+m+1,a[i])-p,tp[i]=i;
	m=n;sort();
	for(int w = 1,p=0;p<n;m=p,w<<=1){
		p=w;
		for(int i = 1;i<=w;i++)tp[i]=n-i+1;
		for(int i = 1;i<=n;i++)if(sa[i]>w)tp[++p]=sa[i]-w;
		sort();
		swap(tp,rnk);
		p=rnk[sa[1]]=1;
		for(int i = 2;i<=n;i++)rnk[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+w]==tp[sa[i-1]+w])?p:++p;
	}
	lg[0]=-1;
	for(int i = 1,k=0,j;i<=n;i++){
		lg[i]=lg[i>>1]+1;
		if(k)k--;
		j=sa[rnk[i]-1];
		while(a[i+k]==a[j+k])++k;
		st[0][rnk[i]]=k;
	}
	for(int i = 1,k=0,j;i<=n;i++){
		if(sa[i]>len-1)insert(rt[i],rt[i-1],1,len,sa[i]-len+1);
		else rt[i]=rt[i-1];
	}
	for(int j = 1;j<=lg[n];j++)for(int i = 1;i+(1<<j)-1<=n;i++)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	scanf("%d",&q);
	int d,u,L,R,l,r,mid;
	while(q--){
		scanf("%d%d",&d,&u);
		if(d==u){
			printf("%d\n",len-1);
			continue;
		}
		l=1,r=rnk[d];
		while(l<=r){
			mid=l+r>>1;
			if(query(mid+1,rnk[d])>=u-d)r=mid-1;
			else l=mid+1;
		}
		L=r+1;
		l=rnk[d],r=n;
		while(l<=r){
			mid=l+r>>1;
			if(query(rnk[d]+1,mid)>=u-d)l=mid+1;
			else r=mid-1;
		}
		R=l-1;
		printf("%d\n",query(rt[R],rt[L-1],1,len,1,d-(u-d+1))+query(rt[R],rt[L-1],1,len,u+1,len-(u-d)));
	}
	return 0;
}

```

---

## 作者：lzyqwq (赞：2)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/p/17831284.html)**

好喜欢 SA + DS。

**[洛谷](https://www.luogu.com.cn/problem/CF232D) [CF](https://codeforces.com/problemset/problem/232/D)**

> - 给出序列 $a_1\sim a_n$，有 $q$ 次询问，每次询问给出 $[l,r]$，求有多少个区间 $[x,y]$ 满足 $y-x=r-l$，$[x,y] \bigcap \,[l,r]=\varnothing$ 且 $\forall \,i\in[0,r-l],a_{l+i}+a_{x+i}=a_{l}+a_x$。
>
> - $n,q\le 10^5$。

tags：

- $\text{binary search}$

- $\text{data structures}$

- $\text{string suffix structures}$

- $\color{red}*2900$

这题看着一点都不串串，但是它就是串串。

原题就是让我们求出有多少个满足条件的左端点。

我们记原数组的差分数组 $d_i=a_i-a_{i-1}\,(i\in(1,n])$。**认为 $\boldsymbol{d_1}$ 没有意义，即不存在，其值不与任何一个 $\boldsymbol{d_i}$ 相同**。则满足第二个条件的充要条件是 $\forall \,i\in(0,r-l],d_{l+i}=-d_{x+i}$。

- 证明：

> 根据已知条件可以推出：
>
> - $a_{l+i}+a_{x+i}=a_l+a_x\Leftrightarrow a_{l+i}-a_l=a_x-a_{x+i}$
>
> - $a_{l+i-1}+a_{x+i-1}=a_l+a_x\Leftrightarrow a_{l+i-1}-a_l=a_{x}-a_{x+i-1}$
>
> 两式相减即可得到 $a_{l+i}-a_{l+i-1}=a_{x+i-1}-a_{x+i}$，即 $d_{l+i}=-d_{x+i}$。

我们若倍长 $d$，且令 $d_i=-d_{i-n}\,(i\in(n,2n])$，则上述条件等价于 $d_{l+i}=d_{x+n+i}$。我们要统计有多少个 $x$，就可以去统计有多少个 $x+n$，**同理可以去统计有多少个 $\boldsymbol{x+n+1}$**。

为什么要做这一步转化呢？我们发现，对于 $d[l+1,2n]$ 和 $d[x+n+1,2n]$ 这两个后缀，**它们存在 $\boldsymbol{d[l+1,r]}$ 和 $\boldsymbol{d[x+n+1,x+n+r-l]}$ 这一段长度为 $\boldsymbol{r-l}$ 的公共前缀**。考虑对差分数组进行后缀排序，则可以二分 + ST 表求出与后缀 $d[l+1,2n]$ 的 $\text{LCP}$ 长度不小于 $r-l$ 的排名区间。然后根据不交、长度相等的限制以及差分数组的定义，可以得到 $x+n+1$ 的范围是 $[n+2,n+2l-r]\bigcup\, [n+r+2,2n+l-r+1]$。

这就是个二维数点，在线主席树或离线扫描线 + 树状数组维护一下就行了。

- **注意**

> 使用上述统计方法的前提是**存在差分数组**。当 $l=r$ 时，区间内不存在差分数组，不能这样统计。
>
> 不过容易得知此时答案即为 $n-1$，特判一下即可。

代码里用的是主席树，时间、空间复杂度均为 $\mathcal{O}(n\log n)$。

**[提交记录（$\color{limegreen} \bf{Accepted}$ $\bold{483\,\text{ms}\,/\,73952\,\text{KB}}$，含代码）](https://codeforces.com/contest/232/submission/232696790)**

---

## 作者：zzxLLL (赞：2)

套路的串串题。

---

当 $l_1 = r_1$ 时，显然答案为 $n - 1$。

当 $l_1 \neq r_1$：

对于条件 $2$，设 $len = r_1 - l_1 + 1$，那么有 $1 \leq l_2 \leq l_1 - len$ 或者 $l_1 + len \leq l_2 \leq n$。

再看条件 $3$，考虑转化柿子：

$$ \begin{aligned} h_{l_1 + i} + h_{l_2 + i} &= h_{l_1} + h_{l_2} \\ h_{l_1 + i} - h_{l_1} &= h_{l_2} - h_{l_2 + i} \\ \sum\limits_{j = 1}^i (h_{l_1 + j} - h_{l_1 + j - 1}) &= \sum\limits_{j = 1}^i (h_{l_2 + j - 1} - h_{l_2 + j}) \end{aligned} $$

而对于 $i + 1$，又有

$$ \begin{aligned} \sum\limits_{j = 1}^{i + 1} (h_{l_1 + j} - h_{l_1 + j - 1}) &= \sum\limits_{j = 1}^{i + 1} (h_{l_2 + j - 1} - h_{l_2 + j}) \end{aligned} $$

上下两个柿子相减，有 $h_{l_1 + i + 1} - h_{l_1 + i} = h_{l_2 + i} - h_{l_2 + i + 1}$。

也就是说，$[l_1, r_1]$ 段的差分数组的，和 $[l_2, r_2]$ 段的差分数组，对应元素恰好互为相反数，这样的 $[l_2, r_2]$ 是满足第三个条件的。

构造数组 $h'$，其中当 $1 \leq i < n$ 时 $h'_i = h_{i + 1} - h_i$，$i = n$ 时 $h'_i = -\infin$，$n < i < 2n$ 时 $h'_i = h_{i - n} - h_{i - n + 1}$。即将 $h$ 数组的差分数组和差分数组的相反数数组拼在一起，中间用特殊字符连接。

问题转化为：求有多少个 $[l_2, r_2]$，满足 $n < l_2 \leq n + l_1 - len$ 或者 $n + l_1 + len \leq l_2 < 2n$，且 $h'[l_2, r_2 - 1]$ 与 $h'[l_1, r_1 - 1]$ 相同。

这个可以用 SAM+线段树合并 或者 SA+主席树 做。因为 $|\Sigma|$ 太大所以我用的后者。

[Code](https://codeforces.com/contest/232/submission/224040367)

---

## 作者：noi2077 (赞：1)

首先我们考虑转化题目中的条件，

- $r_1-l_1=r_2-l_2$ 即长度相等。
- 令 $len=r_1-l_1$， $[l_1,r_1]\cup[l_2,r_2]=\varnothing\Longleftrightarrow l_2\in[1,l_1-len-1]\cup[l_1+len+1,n]$，即限制了 $l_2$ 左端点的范围。
- 令 $\Delta h(x)=h(x)-h(x-1)$，则 $\forall i\in[0,r-l]: h(l_1)+h(l_2)=h(l_1+i)+h(l_2+i)$ 等价于 $\forall i\in[1,r-l]:\Delta h(l_1+i)=-\Delta h(l_2+i)$，即差分后两段的对应位置上恰好为相反数。

前两个条件都很简单，但第三个条件比较复杂。我们可以将差分数组复制一份，每个位置求相反数，然后接在原来差分数组的后面。此时条件变为 $\Delta h(l_1+i+n)=\Delta h(l_2+i)$，即满足前两个条件的情况下，差分数组有多少段和 $[l_1+n+1,r_1+n]$ 相同。

这个问题可以用 SA 求解，两段相同就是它们的 $\mathrm{lcp}\ge len$ ，由于 $\mathrm{lcp}(suf_x,suf_y)=\min_{i=rk_x+1}^{rk_y}\{ht_i\}$，因此所有满足 $\mathrm{lcp}(suf_{l_1},suf_{l_2})\ge len$ 的 $l_2$ 一定是在 $sa$ 数组上连续的一段。

我们对 $ht$ 数组建出 st 表，然后对每个询问向前向后分别二分可以得到合法的 $rk$ 的范围。

将每个后缀看成平面上坐标为 $(i,rk_i)$ 的一个点，满足条件 2 的就是横坐标连续的两段，满足条件 3 的是纵坐标连续的一段，因此每个询问相当于求矩形范围内有多少个点，直接扫描线即可。

注意 $l_1=r_1$ 的询问答案为 $n-1$，要特判。

复杂度 $\mathcal O\left((n+q)\log n\right)$。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<fstream>
#include<cassert>
#define mkp make_pair
using namespace std;
int a[800005];
int sa[800005], rk[800005], tmp[800005], ht[800005];
int st[23][400005];
int n, q;
int ql[200005], qr[200005];
struct Qry {
    int jl, jr, id, ans;
    int x;
    bool operator<(Qry o)
    {
        return x < o.x;
    }
} que[800005];
int cnt;
int dif;
int ans_sz[200005];
void work_sa()
{
    for(int i = 0; i <= 800000; i++) rk[i] = 2e9+1500;
    for(int i = 1; i <= n; i++) sa[i] = i, rk[i] = a[i];
    rk[0] = 2e9+100;
    for(int len = 1; len <= n; len*=2)
    {
        sort(sa+1, sa+n+1, [&](int i, int j){ return mkp(rk[i], rk[i+len]) < mkp(rk[j], rk[j+len]); });
        int cur = 0;
        for(int i = 1; i <= n; i++) tmp[sa[i]] = (rk[sa[i]] == rk[sa[i-1]] && rk[sa[i]+len] == rk[sa[i-1]+len])? cur: ++cur;
        memcpy(rk+1, tmp+1, sizeof(int)*n);
    }
    int k = 0;

    for(int i = 1; i <= n; i++)
    {
        if(k > 0) k--;
        while(a[i+k] == a[sa[rk[i]-1]+k]) k++;
        ht[rk[i]] = k;
    }
}
void work_st()
{
    for(int i = 1; i <= n; i++) st[0][i] = ht[i];
    for(int i = 1; i <= 20; i++)
    {
        for(int j = 1; j+(1<<i)-1 <= n; j++)
            st[i][j] = min(st[i-1][j], st[i-1][j+(1<<i-1)]);
    }
}
int S[800005];
void upd(int i, int c) { for(; i <= n; i+=i&-i) S[i] += c; }
int qry(int i) { int ret = 0; for(; i; i-=i&-i) ret += S[i]; return ret; }
void work_sc()
{
    sort(que+1, que+cnt+1);
    sort(pt+1, pt+dif+1);
    int cur = 1;
    for(int i = 1; i < dif; i++)
    {
        upd(rk[i+dif], 1);
        while(cur <= cnt && que[cur].x == i) que[cur].ans = qry(que[cur].jr)-qry(que[cur].jl-1), cur++;
    }
}
int qry(int l, int r)
{
    int ln = 31-__builtin_clz(r-l+1);
    return min(st[ln][l], st[ln][r-(1<<ln)+1]);
}
int main()
{
    // ifstream cin("d.in");
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    dif = n+1;
    for(int i = n; i >= 1; i--) a[i] -= a[i-1];
    a[n+1] = 2e9;
    for(int i = 1; i <= n; i++) a[i+n+1] = -a[i];
    a[n+2] = 2e9+400;
    n = n+n+1;
    a[n+1] = 2e9+200;
    a[1] = 2e9+300;
    cin >> q;
    for(int i = 1; i <= q; i++)
    {
        cin >> ql[i] >> qr[i];
        ql[i]++;
        if(ql[i] > qr[i]) continue;
        int m = rk[ql[i]];
        int l = 1, r = m;
        int len = qr[i]-ql[i]+1;
        while(l <= r)
        {
            int mid = (l+r)>>1;
            if(qry(mid, m) >= len) r = mid-1;
            else l = mid+1;
        }
        Qry tmp = {0,0,0,0,0};
        tmp.jl = max(r, 1);

        l = m+1, r = n;
        while(l <= r)
        {
            int mid = (l+r)>>1;
            if(qry(m+1, mid) >= len) l = mid+1;
            else r = mid-1;
        }
        tmp.jr = r;
        tmp.id = i;
        l = ql[i];
        r = qr[i];
        if(l-len-1 >= 2)
        {
            tmp.id = -i, tmp.x = 1, que[++cnt] = tmp;
            tmp.id = i, tmp.x = l-len-1, que[++cnt] = tmp;
        }
        if(l+len+1 <= dif-1)
        {
            tmp.id = -i, tmp.x = l+len, que[++cnt] = tmp;
            tmp.id = i, tmp.x = dif-1, que[++cnt] = tmp;
        }
    }
    work_sc();
    for(int i = 1; i <= cnt; i++)
    {
        if(que[i].id < 0) ans_sz[-que[i].id] -= que[i].ans;
        else ans_sz[que[i].id] += que[i].ans;
        // cerr << que[i].id << " " << que[i].x << " " << que[i].jl << " " << que[i].jr << endl;
    }
    for(int i = 1; i <= q; i++)
    {
        if(ql[i] > qr[i]) cout << dif-2 << endl;
        else cout << ans_sz[i] << endl;
    }
    return 0;
}

```

---

## 作者：Aiopr_2378 (赞：0)

Solution of CF232D Fence

## 题目大意

给定长度为 $n$ 的整数序列 $h$，有 $Q$ 个询问，每次给出 $l_1,r_1$，询问有多少对 $l_2,r_2$ 满足以下条件

- $r_2-l_2=r_1-l_1$。

- 区间 $[l_1, r_1]$ 与区间 $[l_2, r_2]$ 没有交集。

- 对于任意 $i \le r_1\ -\ l_1$，满足 $h_{l_1 + i} + h_{l_2 + i} = h_{l_1} + h_{l_2}$。

$1\le n,q \leq 10^5$，$1\le h \leq 10^9$。

## 解题思路

因为要求子串问题，考虑后缀数组。

考虑将字符串复制一倍，前 $n$ 个字符串用于匹配 $l_1,r_1$，后 $n$ 个字符串用于匹配 $l_2,r_2$。由于每次给定 $l_1,r_1$，相当于直接定位到一个后缀串 $p$，借助前面的思想，分别向前和向后扩展到位置 $[l,r]$，使得 $\min\limits_{i=l+1}^r height_i=heigth_p$。在这样一个区间里，找到所有由后 $n$ 个字符贡献的后缀串，并判断与 $[l_1,r_1]$ 不相交，即能找到合法的匹配。

考虑怎样在区间 $[l,r]$ 内找到满足要求的匹配串。类似二维数点，横坐标表示后缀串下标（按后缀排序顺序），纵坐标表示由后 $n$ 个字符串带来的后缀串的起始位置。考虑离线。对于每一个询问 $l_1,r_1$，找到对应的 $[l,r]$，即需要在 $[l,r]$ 的后缀里（按后缀排序顺序）找到与 $[l_1+n,r_1+n]$ 不相交的由后 $n$ 个字符带来的后缀串。将每次的 $l,r$ 拆开成两个端点，利用树状数组进行扫描线即可。

时间复杂度 $O(n\log n)$。

## 参考代码

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
#define MAXN 200005
#define lowbit(x) (x&(-x))
int n,o[MAXN],a[MAXN],q,tmp[MAXN],pos[MAXN];
int m,c[MAXN],x[MAXN],y[MAXN],lstx[MAXN],sa[MAXN];
int rnk[MAXN],height[MAXN];
int minn[MAXN][30],f[MAXN][30],lim;
int ans[MAXN],tree[MAXN];
struct node{
    int l,r,id,op,len;
};
vector<node> qry[MAXN];
void get_SA(){
    for(int i=1;i<=n;i++)
    c[x[i]=a[i]]++;
    for(int i=2;i<=m;i++) c[i]+=c[i-1];
    for(int i=n;i;i--) sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1){
        int num=0;
        for(int i=n-k+1;i<=n;i++) y[++num]=i;
        for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
        for(int i=1;i<=m;i++) c[i]=0;
        for(int i=1;i<=n;i++) c[x[i]]++;
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i];
        for(int i=1;i<=n;i++) lstx[i]=x[i],x[i]=0;
        num=1;
        x[sa[1]]=1;
        for(int i=2;i<=n;i++){
            if(lstx[sa[i]]==lstx[sa[i-1]]&&lstx[sa[i]+k]==lstx[sa[i-1]+k]) x[sa[i]]=num;
            else x[sa[i]]=++num;
        }
        m=num;
    }
}
void get_height(){
    for(int i=1;i<=n;i++) rnk[sa[i]]=i;
    for(int i=1,j=0;i<=n;i++){
        if(rnk[i]==1) continue;
        if(j) j--;
        while(i+j<=n&&sa[rnk[i]-1]+j<=n&&a[i+j]==a[sa[rnk[i]-1]+j]) j++;
        height[rnk[i]]=j;
    }
}
void add(int x,int k){
    while(x<=n){
        tree[x]+=k;
        x+=lowbit(x);
    }
}
int query(int x){
    int w=0;
    while(x){
        w+=tree[x];
        x-=lowbit(x);
    }
    return w;
}
int ask(int l,int r){
    if(l>r) return 0;
    return query(r)-query(l-1);
}
void work(){
    for(int i=1;i<=n;i++){
        add(pos[i],1);
        for(auto now:qry[i]){
            int k=ask(n/2+1+1,now.l+1)+ask(now.r+1,n-now.len+1);
            ans[now.id]+=k*now.op;
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>o[i];
    for(int i=1;i<=n;i++) a[i]=o[i]-o[i-1];
    for(int i=n+1;i<=n*2;i++) a[i]=-a[i-n];
    for(int i=1;i<=n*2;i++) tmp[i]=a[i];
    sort(tmp+1,tmp+1+n*2);
    m=unique(tmp+1,tmp+1+n*2)-tmp-1;
    for(int i=1;i<=n*2;i++){
        a[i]=lower_bound(tmp+1,tmp+1+m,a[i])-tmp;
    }
    n*=2;
    get_SA();
    get_height();
    for(int i=1;i<=n;i++) pos[rnk[i]]=i;
    lim=log2(n);
    for(int i=1;i<=n;i++){
        minn[i][0]=height[i];
    }
    for(int i=1;i<=lim;i++){
        for(int j=1;j+(1<<i)<=n;j++){
            minn[j][i]=min(minn[j][i-1],minn[j+(1<<(i-1))][i-1]);
        }
    }
    cin>>q;
    for(int l,r,id=1;id<=q;id++){
        cin>>l>>r;
        if(l==r){
            ans[id]=n/2-1;
            continue;
        }
        l++;
        int al=rnk[l],ar=rnk[l]+1;
        int p=rnk[l],len=r-l+1;
        for(int i=lim;i>=0;i--){
            if(al-(1<<i)+1<=0) continue;
            if(minn[al-(1<<i)+1][i]>=len) al-=(1<<i)-1;
            if(height[al]>=len) al--;
            else break;
        }
        if(height[p]<len) al=p;
        for(int i=lim;i>=0;i--){
            if(ar+(1<<i)-1>n) continue;
            if(minn[ar][i]>=len) ar+=(1<<i)-1;
            if(ar<n&&height[ar+1]>=len) ar++;
            else break;
        }
        if(height[p+1]<len) ar=p;
        qry[al-1].push_back({l-1+n/2-len-1,r+n/2+1,id,-1,len});
        qry[ar].push_back({l-1+n/2-len-1,r+n/2+1,id,1,len});
    }
    work();
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
    return 0;
}
```

---

