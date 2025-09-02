# LPERMUT - Longest Permutation

## 题目描述

You are given a sequence A of n integer numbers (1<=A $ _{i} $ <=n). A subsequence of A has the form A $ _{u} $ , A $ _{u+1} $ ... , A $ _{v} $ (1<=u<=v<=n). We are interested in subsequences that are permutations of 1, 2, .., k (k is the length of the subsequence).

 Your task is to find the longest subsequence of this type.

## 样例 #1

### 输入

```
5
4 1 3 1 2```

### 输出

```
3```

# 题解

## 作者：shadowice1984 (赞：20)

_和bzoj3100是重复题目，但是那道题的内存限制是16mb，不过这份代码可以通过bzoj3100_

_________________

这道题主要是一些神奇的结论套在一起，然后我们做到了$O(n)$的神奇复杂度

我们发现合法的区间当且仅当这个区间满足以下条件

1.必须包含一个1

2.和必须等于$\frac{len(len+1)}{2}$

3.最大值等于区间长度

4.没有重复元素

那么我们可以根据这组条件尝试实现一个算法

就是找到每一个1的位置，然后从这个1出发枚举区间的右端点j，枚举到下一1为止，假设这个最大值在1的右侧，那么这个区间唯一可能的左端点位置就是j-max+1

此时我们只需要判断这个区间是否合法就行了，如果合法就更新一下答案

然后将整个区间reverse一遍再跑一次就行了

如果你数据结构学傻了的话你会想到用主席树判一下区间内是否有重复值，然后前缀和判一下区间的和

但是其实真的需要主席树？

我们考虑这样一个暴力，我们强行使用一个数组维护区间里每种值的出现次数，并且使用一个变量维护区间的和

那么我们此时就是像莫队一样的暴力插点和删点强行维护这个区间

那么问题来了，这个暴力真的不会卡到$O(n^2)$吗？

我们来分析一波复杂度

首先右端点j最多把整个序列扫一遍，复杂度O(n)

然后此时是麻烦的左端点，我们发现如果认为左端点是-max的话，由于左端点单调，所以复杂度也是$O(n)$

但是我们发现右端点每+1，左端点就会回退1次，但是，最多回退$O(n)$次，然后我们最多会撤销这个操作$O(n)$次

所以总复杂度$O(n)$

上代码~

```C
#include<cstdio>
#include<algorithm>
using namespace std;const int N=1e6+10;typedef long long ll;
int res;int a[N];int col[N];ll sum;int cf;int n;
inline void ins(int i){++col[a[i]];if(col[a[i]]==2)++cf;sum+=a[i];}
inline void del(int i){--col[a[i]];if(col[a[i]]==1)--cf;sum-=a[i];}
inline void solve()
{
    for(int i=1,j,mx,nl,lstone=0;i<=n;i++)
        if(a[i]==1)
        {
            j=i,mx=1,nl=i;
            do
            {
                ins(j);int dl=j-mx+1;
                if(lstone<dl&&dl<=i)
                {
                    if(nl>dl)while(1){ins(--nl);if(nl==dl)break;}
                    else if(nl<dl)while(1){del(nl++);if(nl==dl)break;}
                    if(cf==0&&sum==(ll)mx*(mx+1)/2)res=max(res,mx);
                }++j;mx=max(mx,a[j]);
            }while(a[j]!=1&&j<=n);
            while(1){del(nl++);if(nl==j)break;}lstone=i;
        }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    solve();reverse(a+1,a+n+1);solve();
    printf("%d",res);return 0;
}
```

---

## 作者：Hoks (赞：4)

## 前言
这题是不是和 CF1175F 没区别啊。貌似把那题的加全部改成和长度取 $\max$ 就过了。

~~其实是看到另一篇题解说前缀和写更精简才来写的题解。~~
## 思路分析
这种题目，稍加观察就能看到题目中求的子集排列顺序是无关紧要的，关心的只是是否存在。

所以套路的想到了异或 Hash，先处理出前缀异或。

不难得到这个子集一定不会很多，接着考虑怎么求。

因为一个子集肯定要包含 $1$，所以我们考虑从 $1$ 的位置开始扫。

扫的时候取区间长度为前面那段区间中出现过的最大 $a_i$ 判断即可。

因为扩展方向可能向左，可能向右，所以我们考虑正着扫一遍，倒着扫一遍。

异或 hash 推荐用 mt19937 随机附点权。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=100010,INF=0x3f3f3f3f3f3f3f,p=13331;
int n,ans,a[N],rd[N],sa[N],op[N];
mt19937_64 rnd(time(0));
static char buf[1000000],*paa=buf,*pd=buf;
#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
inline int read(void){
	int u(0),t(1);char fc(getchar());
	while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
	while(isdigit(fc)) u=(u<<1)+(u<<3)+(fc^48),fc=getchar();
	return u*t;
}
inline void print(int u)
{
	if(u<0) putchar('-'),u=-u;
	if(u>9) print(u/10);
	putchar(u%10+'0');
}
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),rd[i]=rnd(),op[i]=op[i-1]^rd[i];
	for(int i=1;i<=n;i++) sa[i]=rd[a[i]]^sa[i-1];
	for(int i=1,j=1;i<=n;i++)
		if(a[i]==1) j=1,ans=max(ans,1ll);
		else
		{
			j=max(j,a[i]);
			if(i>=j&&(sa[i]^sa[i-j])==op[j]) ans=max(ans,j);
		}
	for(int j=1;2*j<=n+1;j++) swap(a[j],a[n-j+1]);
	for(int i=1;i<=n;i++) sa[i]=rd[a[i]]^sa[i-1];
	for(int i=1,j=1;i<=n;i++)
		if(a[i]==1) j=1;
		else
		{
			j=max(j,a[i]);
			if(i>=j&&(sa[i]^sa[i-j])==op[j]) ans=max(ans,j);
		}
	print(ans);return 0;
}
```

---

## 作者：IkunTeddy (赞：4)

# 题目分析

这里提供两种做法。

### 思路一：

我们可以对题目条件进行转化，只要这个区间满足以下条件即是合法区间：

1. $\min\limits_{i=l}^r{a[i]} =1$
2. $\max\limits_{i=l}^r{a[i]}=r-l+1$
3. $\sum\limits_{i=l}^{r}{a[i]}=\frac{(r-l+1)\cdot(r-l+2)}{2}$
4. $\forall i\in \{l\dots r+1\},a[i]$ 出现次数为 $1$

题目是关于区间的求解，所以我们就可以考虑定一求一。

那么如果我们枚举了 $l$ 怎么快速求 $r$ 呢？我们根据上面条件可知，最小值为 $1$，所以 $r$ 一定位于 $l$ 右侧最靠近 $l$ 的 $1$ 的右边，我们设这个 $1$ 的位置为 $i$。再考虑最大值，若最大值位于 $l\sim i$ 间，则 $r$ 为 $l+max-1$。若最大值位于 $i+1\sim n$ 我们会发现 $r$ 十分难求。但是我们逆向思维一下，就会惊奇的发现这一部分情况可以通过枚举 $r$ 定 $l$ 求出。

现在就是给你多个区间判合法，考虑到区间种类数用莫队较好求，所以我们可以用莫队。

因为区间个数为 $O(2n)$，所以莫队时间复杂度为$O(n\sqrt{n})$。预处理 ST 表时间复杂度 $O(n\log{n})$。

总时间复杂度 $O(n\log{n}+n\sqrt{n})$。

### 思路二：

我们也可以考虑正难则反，枚举区间长度判合法。

我们发现，枚举长度就可以用到笛卡尔树的性质：合法区间一定在当前枚举的长度 $len$ 的子树中。只要我们每次都去到较小子树中找答案，就类似于启发式合并，每个节点最多被遍历 $O(\log{n})$ 次。判断区间是否合法可以用异或和 hash 进行 $O(1)$ 判断。

总时间复杂度 $O(n\log{n})$ 比莫队优秀。

# Code

### 莫队：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+10;
int n,q,B;
int s[maxn],st[maxn][25];
int bel[maxn],cnt[maxn],num,sum,ans;
void init_ST(){
	for(int i=1;i<=n;i++)st[i][0]=s[i];
	for(int j=1;(1<<j)<=n;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
		}
	}
}
int get(int l,int r){
	int k=__lg(r-l+1);
	return max(st[l][k],st[r-(1<<k)+1][k]);
}
struct Query{
	int l,r,id;
}qry[maxn]; 
bool cmp(Query x,Query y){
	if(bel[x.l]==bel[y.l]){
		return bel[x.l]&1?x.r<y.r:x.r>y.r;
	}else{
		return x.l<y.l;
	}
}
void init(){
	B=sqrt(n);
	for(int i=1;i<=n;i++)bel[i]=(i-1)/B+1;
	sort(qry+1,qry+1+q,cmp);
}
void add(int x){
	cnt[x]++;
	sum+=x;
	if(cnt[x]==1)num++;
}
void del(int x){
	cnt[x]--;
	sum-=x;
	if(cnt[x]==0)num--;
}
void solve(){
	int l=1,r=0;
	for(int i=1;i<=q;i++){
		while(l>qry[i].l)add(s[--l]);
		while(r<qry[i].r)add(s[++r]);
		while(l<qry[i].l)del(s[l++]);
		while(r>qry[i].r)del(s[r--]);
		if(num==r-l+1&&sum==(r-l+1)*(r-l+2)/2)ans=max(ans,r-l+1);
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&s[i]);
	init_ST();
	int pos=0;
	for(int i=n;i>=1;i--){
		if(s[i]==1)pos=i;
		if(pos){
			int r=i+get(i,pos)-1;
			if(r<=n){
				qry[++q].l=i;
				qry[q].r=r;
			}
			
		}
	}
	pos=0;
	for(int i=1;i<=n;i++){
		if(s[i]==1)pos=i;
		if(pos){
			int l=i-get(pos,i)+1;
			if(l>=1){
				qry[++q].l=l;
				qry[q].r=i;
			}
			
		}
	}
	init();
	solve();
	printf("%lld\n",ans);

	return 0;
}

```

### 笛卡尔树：

代码来源：同机房的大佬[1234567s](https://www.luogu.com.cn/user/549001)。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000005
random_device R;
mt19937 G(R());
int rd(int l,int r){
	return uniform_int_distribution<int>(l,r)(G);
}
//建立笛卡尔树
//枚举区间最大值=区间长度,找到对应区间,异或和hs O(1)判断 
int n,a[N];
int val[N];//值分配的hash值 
int hs[N],sum[N];//数列前缀hash,值域前i个hash 
int stk[N],top;
struct node{
	int min;
	int max;//由于是连续区间,一定小于这个数 
	int size;
	int ls,rs;
}tree[N];
int root;
int ans;
int maxx[N][28];
void init(){
	for(int i=1;i<=n;i++)maxx[i][0]=a[i];
	for(int j=1;j<=log2(n);j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			maxx[i][j]=max(maxx[i][j-1],maxx[i+(1<<(j-1))][j-1]);
		}
	}
}
int query(int l,int r){
	int k=__lg(r-l+1);
	return max(maxx[l][k],maxx[r-(1<<k)+1][k]);
}
void dfs(int root,int u,int len){//结点与区间长度 
	if(!u)return ;
	if(abs(len)<=ans)return ;
	if(len>0){
		if((u+len-1)<=n&&((hs[u+len-1]^hs[u-1])==sum[len])&&query(u,u+len-1)==a[root]){
			ans=max(ans,len);
			return ;
		}
	}
	else{
		if(u>=(-len)){
			if((hs[u]^hs[u+len+1-1])==sum[-len]&&query(u+len+1,u)==a[root]){
				ans=max(ans,-len);
				return ;
			}
		}
	}
	dfs(root,tree[u].ls,len);
	dfs(root,tree[u].rs,len);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		val[i]=rd(1,1e9);
		sum[i]=(sum[i-1]^val[i]);
	}
	for(int i=1;i<=n;i++)hs[i]=(hs[i-1]^val[a[i]]);
	init();
	for(int i=1;i<=n;i++){//建立大根堆 
		bool flag=0;
		tree[i].min=i;
		tree[i].max=i;
		tree[i].size=1;
		while(top&&a[stk[top]]<=a[i])top--,flag|=1;
		if(top)tree[stk[top]].rs=i,tree[stk[top]].size+=tree[i].size;
		else root=i;
		if(flag)tree[i].ls=stk[top+1],tree[i].size+=tree[stk[top+1]].size;
		stk[++top]=i;
	}
	for(int i=1;i<=n;i++){//以a[i]作为最大值 
		if((hs[i+a[i]-1]^hs[i-1])==sum[a[i]]&&query(i,i+a[i]-1)==a[i]){
			ans=max(ans,a[i]);
		}
		else if(i-a[i]+1>=1){
			if((hs[i]^hs[i-a[i]+1-1])==sum[a[i]]&&query(i-a[i]+1,i)==a[i]){
				ans=max(ans,a[i]);
			}
		}
		if((tree[tree[i].ls].size<=tree[tree[i].rs].size))dfs(i,tree[i].ls,a[i]);
		else dfs(i,tree[i].rs,-a[i]);
	}
	printf("%d\n",ans);
	return 0;
}

```

码风有所不同请见谅。


---

## 作者：_•́へ•́╬_ (赞：3)

## 思路

对于一个位置 $i$，

找他后面的第一个 $1$，位置 $x$。

找 $[i,x]$ 区间里的最大值，就是 $k$。

$j=i+k-1$。

检查 $[i,j]$ 是否满足要求：没有重复且加和 $=1+2+\cdots k$ 就满足要求了。

记 $nxt[i]$ 为下次出现 $a[i]$ 的位置。

如果 $\min\limits_{k=i}^j nxt[k]\quad >j$，即最早重现都过了右端点，那么 $[i,j]$ 中没有重复。

这还不够，要把从右往左再做一遍（我的写法是吧序列翻转再跑一遍。

## $code$

```cpp
#include<stdio.h>
#define N 100002
#define M 17
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,lg[N],a[N],_1[N],nxt[N],b[N],k[N][M],rpt[N][M],ans;long long pfx[N];
inline int min(const int&x,const int&y){return x<y?x:y;}
inline int max(const int&x,const int&y){return x>y?x:y;}
inline void work()
{
	for(int i=1;i<=n;b[i++]=n+1);
	for(int i=n,nxt1=-1;i;--i)
	{
		if(a[i]==1)nxt1=i;
		_1[i]=nxt1;

		nxt[i]=b[a[i]];
		b[a[i]]=i;

		k[i][0]=a[i];
		for(int j=1;j<M;++j)
			if(i+(1<<j-1)>n)k[i][j]=k[i][j-1];
			else k[i][j]=max(k[i][j-1],k[i+(1<<j-1)][j-1]);

		rpt[i][0]=nxt[i];
		for(int j=1;j<M;++j)
			if(i+(1<<j-1)>n)rpt[i][j]=rpt[i][j-1];
			else rpt[i][j]=min(rpt[i][j-1],rpt[i+(1<<j-1)][j-1]);
	}
	for(int i=1;i<=n;pfx[i]=pfx[i-1]+a[i],++i);
	for(int i=1,j,tmp;i<=n&&~_1[i];++i)
	{
		tmp=lg[_1[i]-i+1];//i~_1[i]
		j=i+max(k[i][tmp],k[_1[i]-(1<<tmp)+1][tmp])-1;

		if(pfx[j]-pfx[i-1]^1ll*(1+j-i+1)*(j-i+1)/2)continue;
		tmp=lg[j-i+1];//i~j
		if(min(rpt[i][tmp],rpt[j-e(1<<tmp)+1][tmp])<=j)continue;

		if(ans<j-i+1)ans=j-i+1;
	}
}
main()
{
	read(n);for(int i=1;i<=n;read(a[i++]));
	lg[0]=-1;for(int i=1;i<=n;lg[i]=lg[i>>1]+1,++i);
	work();
	for(int i=1;i<=(n>>1);a[i]^=a[n-i+1]^=a[i]^=a[n-i+1],++i);
	work();
	printf("%d",ans);
}
```

## 思考

1. 把用加和检查改为用异或和检查可以吗？$\quad \color{white}\texttt{thx tzy}$
2. 算法的正确性？（为啥不会错过正解）$\quad \color{white}\texttt{thx fc}$

## 答案

1. 不行。$1\ \operatorname{xor}\ 2\ \operatorname{xor}\ 3=1\ \operatorname{xor}\ 6\ \operatorname{xor}\ 7$。

2. 记答案为 $[l,r]$，$1$ 的位置是 $x$。

   如果 $k\in[l,x)$，那么从左往右做到 $l$ 的时候能找到答案。

   如果 $k\in(x,r]$，那么从右往左做到 $r$ 的时候能找到答案。



---

## 作者：封禁用户 (赞：2)

## 分析

使用莫队和线段树。

对于这道题，我们只需枚举每一个下标 $i$，然后找到与 $A_i$ 最近的一个值为 $1$ 的点的下标 $j$（$i \le j$）。如果在区间 $A_i$ 到 $A_j$ 中有最大值 $x$，满足 $A_i$ 到 $A_{i+x-1}$ 的所有数字都只出现一次，且 $ \sum_{k=i}^{j} A_k~=~\dfrac{(1+x) \times x}{2}$，则 $A_i$ 到 $A_{i+x-1}$ 就是一个满足条件的子集。相反，我们枚举一遍 $j \le i$ 的情况，找到这两种情况中，满足条件子集的长度最大值即可。

简化一下，我们可以定义 $\mathit{where}_{i}$ 表示距离 $A_i$ 向左（右）最短的值为 $1$ 的点的下标。对于两次情况枚举的 $i$，如果其向左（右）存在最短距离的 $1$，则利用线段树在 $O(\log n)$ 的复杂度求出区间的最大值，再根据上面的判断求值。但是，这里有一个问题：我们无法在小于 $O(r-l+1)$ 的朴素复杂度下判断这个区间是否有重复。

考虑离线，我们将所有满足条件的序列的左右端点下标当做询问来看，定义 $\mathit{q}_{i,j}$ 表示询问区间 $i,j$ 内每个只出现一次的元素个数。如果 $\mathit{q}_{i,j}=j-i+1$，则这个子集就是满足条件的子集。我们直接用普通莫队求解即可。最大复杂度：$O(2n\sqrt{n})$。

注：求和的话用前缀和（后缀和）就行了，不需要线段树。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e6+10;
int c[N],n;
struct tree{
	int l,r,mx;
}tr[N];
void build(int now,int l,int r){
	tr[now].l=l,tr[now].r=r;
	if(tr[now].l==tr[now].r){
		tr[now].mx=c[l];
	}
	else{
		int mid=l+r>>1;
		build(now*2,l,mid),build(now*2+1,mid+1,r);
		tr[now].mx=max(tr[now*2].mx,tr[now*2+1].mx);
	}
} 
int query(int now,int l,int r){
	if(tr[now].l>=l&&tr[now].r<=r){
		return tr[now].mx;
	}
	else{
		int maxx=0;
		int mid=tr[now].l+tr[now].r>>1;
		if(l<=mid){
			maxx=max(maxx,query(now*2,l,r));
		}
		if(mid<r){
			maxx=max(maxx,query(now*2+1,l,r));
		}
		return maxx;
	}
}
int where[N];
int maxx=0;
int last;
int sum[N];
int qidx;
struct node{
	int l,r;
}a[N];
bool cmp(node a,node b){
	int len=sqrt(n);
	if(a.l/len!=b.l/len){
		return a.l<b.l;
	}
	return a.r<b.r;
}
int ans;
int cnt[N];
void add(int x){	
	if(cnt[x]==0){//加之前不存在 
		ans++;
	}
	else if(cnt[x]==1){//加之前刚好出现1次，加之后就重复了 
		ans--;
	}
	cnt[x]++;
}
void del(int x){
	cnt[x]--;
	if(cnt[x]==1){
		ans++;
	}
	else if(cnt[x]==0){
		ans--;
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		sum[i]=sum[i-1]+c[i];//前缀和 
	}
	build(1,1,n);
	last=-1;//最近的1的下标 
	for(int i=n;i>=1;i--){//where[i]：i之后最近的1的下标 
		if(c[i]==1){
			last=i;
		}
		where[i]=last;
	}
	for(int i=1;i<=n;i++){//情况1 
		int l=i,r=where[i];
		if(r!=-1){
			int now_max=query(1,l,r);
			int j=i+now_max-1;
			if(j<=n&&r<=j){
				if(sum[j]-sum[i-1]==(1+now_max)*(j-i+1)/2){
					a[++qidx]={i,j};
				}
			}
		}
	}
	for(int i=n;i>=1;i--){//后缀和 
		sum[i]=sum[i+1]+c[i];
	}
	last=-1;
	for(int i=1;i<=n;i++){//where[i]：i之前最近的1的下标 
		if(c[i]==1){
			last=i;
		}
		where[i]=last;
	}
	for(int i=n;i>=1;i--){
		int r=i,l=where[i];
		if(l!=-1){
			int now_max=query(1,l,r);
			int j=i-now_max+1;
			if(j>=1&&j<=l){
				if(sum[j]-sum[i+1]==(1+now_max)*(i-j+1)/2){
					a[++qidx]={j,i};
				}
			}
		}
	}
	sort(a+1,a+qidx+1,cmp);
	int l=1,r=0;//莫队 
	for(int i=1;i<=qidx;i++){
		while(l>a[i].l) add(c[--l]);
		while(r<a[i].r) add(c[++r]);
		while(l<a[i].l) del(c[l++]);
		while(r>a[i].r) del(c[r--]);
		if(ans==a[i].r-a[i].l+1){//不重复的刚好等于子集长度	
			maxx=max(maxx,ans);
		}
	}
	return cout<<maxx,0;
}
```


---

## 作者：FQR_ (赞：1)

## 思路

不难发现，如果区间 $[l,r]$ 满足以下条件，则它就是合法的：

1. 包含 $1$，且最大值为 $r-l+1$
2. 每个数字出现的次数都不超过 $1$

于是，我们可以找到所有满足条件一的区间。枚举左端点 $l$，找到它右边第一个 $1$ 的位置，记为 $m$。假设最大值出现在 $[l,m]$ 之间，可以求出区间 $[l,m]$ 的最大值 $max$，则区间长度就是 $max$，由此可以求出右端点 $r$，再判断区间 $[l,r]$ 的最大值是否仍为 $max$ 即可。若最大值出现在 $m$ 的右边，则很难直接处理。我们可以反向枚举，枚举右端点 $r$，找到它左边第一个 $1$ 的位置。

找到所有满足条件一的区间后，我们逐个判断它是否满足条件二。可以使用莫队，记录每个数字出现的个数 $cnt_i$、出现次数大于 $1$ 的数字的个数 $p$。当添加或删除一个数字 $i$ 时，将 $cnt_i$ 加一或减一，然后判断 $cnt_i$ 是否从 $1$ 变成 $2$ 或者是否从 $2$ 变成 $1$，计算修改后 $p$ 的值。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ls o<<1
#define rs o<<1|1
namespace Main
{
    const int N = 300010;
    int a[N], n;

    //线段树，计算区间最大值
    int maxn[N << 2];
    void build(int o,int l,int r)
    {
        if(l==r)
        {
            maxn[o] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r);
        maxn[o] = max(maxn[ls], maxn[rs]);
    }
    int query(int o,int l,int r,int L,int R)
    {
        if(L<=l&&r<=R) return maxn[o];
        int mid = (l + r) >> 1, res = 0;
        if(L<=mid) res = max(res, query(ls, l, mid, L, R));
        if(R>mid) res = max(res, query(rs, mid + 1, r, L, R));
        return res;
    }


    struct Q
    {
        int l, r;
        Q(int _l,int _r){l = _l, r = _r;}
    };
    vector<Q> q; //记录符合第一个条件的区间
    int cnt[N], p;//每个数字出现的次数、出现次数大于 1 的数字的个数

    void add(int o)
    {
        int val = a[o];
        cnt[val]++;
        if(cnt[val]==2) p++;  //如果出现次数从 1 变为 2，则 p 加 1
    }
    void del(int o)
    {
        int val = a[o];
        cnt[val]--;
        if(cnt[val]==1) p--;  //如果出现次数从 2 变为 1，则 p 减 1
    }

    void main()
    {
        ios::sync_with_stdio(0);
        cin.tie(0);cout.tie(0);
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        build(1, 1, n);
        int m = 0;
        for (int i = n; i >= 1; i--) //枚举左端点
        {
            if(a[i]==1)
                m = i; //计算右边第一个 1 的位置
            if(!m) continue;
            int mx = query(1, 1, n, i, m), r = i + mx - 1;      //计算区间最大值和右端点
            if(r <= n && r >= m && query(1, 1, n, i, r) == mx)  //判断 r 是否在 [m,n] 之间，以及区间最大值是否仍为 mx
                q.push_back(Q(i, r));
        }
        m = 0;
        for (int i = 1; i <= n; i++)
        {
            if(a[i]==1)
                m = i;
            if(!m) continue;
            int mx = query(1, 1, n, m, i), l = i - mx + 1;    //计算区间最大值和左端点
            if(l <= m && l >= 1&& query(1, 1, n, l, i) == mx) //判断 l 是否在 [1,m] 之间，以及区间最大值是否仍为 mx
                q.push_back(Q(l, i));
        }

        sort(q.begin(), q.end(), [](Q a, Q b) {
            int S = sqrt(n);
            if(a.l / S != b.l / S)
                return a.l < b.l;
            return a.r < b.r;
        });
        int l = 1, r = 1;
        add(1);
        int ans = 0;
        for(auto i:q)
        {
            while(r < i.r) add(++r);
            while(l > i.l) add(--l);
            while(r > i.r) del(r--);
            while(l < i.l) del(l++);
            if(!p) ans = max(ans, r - l + 1);//符合条件，计算答案
        }
        cout << ans;
    }   
};

int main()
{
    Main::main();
    return 0;
}
```

双倍经验：[CF1175F](https://www.luogu.com.cn/problem/CF1175F)。把求得的符合条件 $1$ 的区间去重后，统计个数即可。

---

## 作者：苏联小渣 (赞：0)

upd 2023/7/14：更改了公式书写问题。

提供一种哈希方法。

首先考虑枚举每个数 $a_i$ 作为排列的最大值，也就是排列的长度 $k$。然后，我们需要判断是否存在一个区间 $[l,r]$，满足 $l \le i$，$r \ge i$ 且 $a_l,...,a_r$ 是 $k$ 的一个排列。

看起来不太好做，那我们考虑找一些充要条件：

- $\max\{a_l,...,a_r\} =a_i$；

- $a_l,...,a_r$ 中没有重复的数。

考虑第一个条件。显然，这个东西可以用单调栈转化：设 $i$ 左边第一个不比 $a_i$ 小的数为 $a_L$，$i$ 右边第一个不比 $a_i$ 小的数为 $a_R$。那么，一定有 $L \le l \le i$，$i \le r \le R$。根据结论，我们知道 $\sum_{i=1}^n \min(i-L+1,R-i+1)$ 是 $n \log n$ 级别的，所以我们可以枚举长度较小的一段，不妨设枚举左端，即枚举左端点 $l$。那么此时右端点 $r$ 固定了，我们需要判断的就是 $a_l,...,a_r$ 是否为一个 $k$ 的排列。

这个就是经典的问题了，我们可以使用异或哈希来判断。给每个数赋一个随机的哈希值 $H_x$，那么 $a_l,...,a_r$ 合法就转化为了 $H_{a_l} \oplus H_{a_{l+1}} \oplus ... \oplus H_{a_r}=H_1 \oplus ... \oplus H_k$，用前缀和计算即可。

时间复杂度 $O(n \log n)$。

### Code：

代码实现得麻烦了，直接用前缀和会更加简洁。

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 10000000000
int n, ans, a[100010], fl[100010], fr[100010], mp[100010];
ll val[100010], lim[100010], s[100010];
stack <int> st;
int main(){
	mt19937 rand(time(0));
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){
		scanf ("%d", &a[i]);
		val[i] = rand() % N + 1;
		while (!st.empty() && a[st.top()] < a[i]) st.pop();
		if (st.empty()) fl[i] = 0;
		else fl[i] = st.top();
		st.push(i);
	}
	for (int i=1; i<=n; i++){
		s[i] = s[i-1] ^ val[a[i]];
		lim[i] = lim[i-1] ^ val[i];
	}
	while (!st.empty()) st.pop();
	for (int i=n; i>=1; i--){
		while (!st.empty() && a[st.top()] < a[i]) st.pop();
		if (st.empty()) fr[i] = n+1;
		else fr[i] = st.top();
		st.push(i);
	}
	for (int i=1; i<=n; i++){
	//	printf ("now : %d\n", i);
		ll now = 0;
		if (i-fl[i] < fr[i]-i){
			for (int j=i; j>fl[i]; j--){
				if (mp[a[j]]) break;
				mp[a[j]] = 1, now ^= val[a[j]];//choose i-j+1
				int yu = a[i]-(i-j+1);
				if (i+yu > n) continue;
				if ((s[i+yu]^s[i]) == (lim[a[i]]^now)){
					ans = max(ans, a[i]);
					break;
				}
			}
			for (int j=i; j>fl[i]; j--){
				mp[a[j]] = 0;
			}
		}
		else{
			for (int j=i; j<fr[i]; j++){
				if (mp[a[j]]) break;
				mp[a[j]] = 1, now ^= val[a[j]];
				int yu = a[i]-(j-i+1);
				if (i-yu <= 0) continue;
				if ((s[i-1]^s[i-yu-1]) == (lim[a[i]]^now)){
					ans = max(ans, a[i]);
					break;
				}
			}
			for (int j=i; j<fr[i]; j++){
				mp[a[j]] = 0;
			}
		}
	}
	printf ("%d\n", ans);
	return 0;
}
```

---

## 作者：OldVagrant (赞：0)

## 题意
[题意传送门](https://www.luogu.com.cn/problem/SP744)
（
## Solution
一种和其余两篇题解有点区别的做法，但时间复杂度仍然是 $O(n)$ 的。 

首先，一个合法的区间必定包含且仅包含一个 $1$，所以先用一个 $pos$ 数组记录下所有 $1$ 的位置。之后遍历 $pos$ 数组，暴力地从每个 $1$ 向左右扩展，如果碰到一个合法区间则更新答案，如果碰到了另外一个 $1$ 则停止扩展。（方便起见，可以将 $pos[cnt+1]$ 的值赋为 $n+1$，$cnt$ 就是 $1$ 的总个数）   
并且，如果扩展到了一个区间内已有的数，也要立刻停止扩展，因为一个合法区间内每个数恰好出现一次。  
   

在扩展的同时，记录下当前区间的 $mex$ （最小的没有出现过的正整数，初值为 $1$），当 $mex$ 大于区间长度时，说明该区间是合法的，更新答案。  
（$mex$ 大于区间长度，意味着 $1\sim mex-1$ 的数都在区间内出现了恰好一次）（这里注意一点，如果用 $mex$ 去更新答案的话，最后输出的时候要减 $1$，因为那个合法区间的实际长度是 $mex-1$）。   

那么如何更新 $mex$ 呢？   
可以肯定的一点是，如果区间是一直在向两侧扩展的，那么该区间的 $mex$ 单调不减。有了这个结论之后就很好办了，用一个数组 $col$ 存下区间内每个数出现的次数，每次扩展完之后都要更新一下 $mex$。
具体更新的方式就是让 $mex$ 自增，直到区间内没有出现过 $mex$。  
这样的总时间复杂度是 $O(n)$ 的，因为每次 $mex$ 的变化量最多就是扩展到的区间的长度，而这些区间的总长度不超过 $n$。

代码可能是这样的：
```
for(int i=1,now,mex,l;i<=cnt;i++){
	now=pos[i],mex=1,l=0;//now是当前位置，l是当前区间左端点。向左扩展时左端点就是 now+1，所以不用管，向右扩展时l才会派上用场。
	while(now>pos[i-1]){
		if(col[a[now]]){//如果该数已经在区间内出现过，则立刻停止扩展，并更新区间左端点。
			l=now+1;
			break;
	}col[a[now]]++,now--;
		while(col[mex]) mex++;//更新mex
		if(mex>pos[i]-now) ans=max(ans,mex);//如果mex大于区间长度则更新答案
	}if(!l) l=now+1;//如果是一路向左扩展到了pos[i-1]+1的位置，那么l此时就会是0，所以要更新一下l。（扩展到pos[i-1]+1时，now的值为pos[i-1]）
	now=pos[i]+1;
	while(now<pos[i+1]){
		if(col[a[now]]) break;
		col[a[now]]++,now++;
		while(col[mex]) mex++;
		if(mex>now-l) ans=max(ans,mex);
	}now--;//这里是因为实际区间的右端点是now-1，为了使下面清空col数组的部分正确，now在这里要减1。
	while(now>=l) col[a[now]]--,now--;
}
```

显然，它看起来问题很大。（并且交上去也 `WA` 了）  
考虑这样一组数据：
```
8
7 8 1 2 2 2 2 2 
```
这份代码会输出 $1$。  
因为包含了$1\sim mex-1$ 的所有数的区间不一定就是当前扩展到的整个区间，所以不能用 $mex$ 和当前扩展到的区间的长度来比较。  
问题又来了，如何得知包含了 $1\sim mex-1$ 的所有数的最短区间的左右端点呢？   

考虑记录下每个数出现的位置，$num[i]$ 表示值为 $i$ 的数在当前扩展到的区间内的出现位置。因为区间内每个数最多出现一次，所以不用担心冲突。在更新 $mex$ 时，再额外记录两个变量 $ma,mi$，$[mi,ma]$ 即为我们所求的那个最短区间，然后让这两个变量跟着  $mex$  一同更新即可。  
```
while(col[mex]){
	ma=max(ma,num[mex]),mi=min(mi,num[mex]);//ma的初值为0,mi的初值为一个很大的数(比如n+1）
  	mex++;
  	if(mex>ma-mi+1) ans=max(ans,mex);//若区间[mi,ma]合法则更新答案
}

```
但还是有问题。    
再考虑下面这样一组数据：  
```
5
2 1 2 3 4
```
改掉上一个bug之后的代码会输出 $2$，但实际答案是 $4$。  
问题在于，如果先往左扩展再往右扩展，并且左右两边有相同的数字，那么这样写的话它会默认选取左边的那个，在碰到右边那个之后立刻 `break`。    
不过这个问题不大，暴力扫两遍就好了，枚举选左边的还是选右边的，反正如果对答案有贡献的话肯定要选一个，没贡献的话也不影响答案。
  
最后证一下复杂度：   
1. 由于我们是枚举每个 $1$，向左右扩展，碰到其他的 $1$ 就 `break`，所以每个位置最多被访问两次（它左边的那个 $1$ 和右边的那个 $1$），总复杂度 $O(n)$。  
2. 更新 $mex$ 的部分上面已经证过了，也是 $O(n)$。   
3. 扫两遍也只是让常数翻倍，并且每次扫完还原 $col$ 数组的总复杂度仍然是 $O(n)$ 的，只需要把访问过的位置上的改动还原即可。   

综上，总时空复杂度均为 $O(n)$。   

最后的最后，一个小优化：$col$ 数组是无用的，判断某个数 $x$ 是否出现过，只需要看 $num[x]$ 是否为 $0$ 即可。
## Code
```
#include <bits/stdc++.h>
#define gc getchar
using namespace std;
int a[100001],pos[100002],num[100002];
int read(){
	int x=0;
	char ch=gc();
	while(ch<48||ch>57) ch=gc();
	while(ch>47&&ch<58) x=x*10+ch-48,ch=gc();
	return x;
}
signed main(){
	int n=read(),ans=1,cnt=0;
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(a[i]==1) pos[++cnt]=i;
	}pos[0]=0,pos[cnt+1]=n+1;
	for(int i=1,mex,l,r,ma,mi;i<=cnt;i++){
		mex=1,l=pos[i],r=pos[i]+1,ma=0,mi=n+1;
		while(l>pos[i-1]){
			if(num[a[l]]) break;
			num[a[l]]=l,l--;
			while(num[mex]){
				ma=max(ma,num[mex]),mi=min(mi,num[mex]),mex++;
				if(mex>ma-mi+1) ans=max(ans,mex);
			}
		}while(r<pos[i+1]){
			if(num[a[r]]) break;
			num[a[r]]=r,r++;
			while(num[mex]){
				ma=max(ma,num[mex]),mi=min(mi,num[mex]),mex++;
				if(mex>ma-mi+1) ans=max(ans,mex);
			}
		}for(int j=l+1;j<r;j++) num[a[j]]=0;
		mex=1,l=pos[i],r=pos[i]+1,ma=0,mi=n+1;
		while(r<pos[i+1]){
			if(num[a[r]]) break;
			num[a[r]]=r,r++;
			while(num[mex]){
				ma=max(ma,num[mex]),mi=min(mi,num[mex]),mex++;
				if(mex>ma-mi+1) ans=max(ans,mex);
			}
		}while(l>pos[i-1]){
			if(num[a[l]]) break;
			num[a[l]]=l,l--;
			while(num[mex]){
				ma=max(ma,num[mex]),mi=min(mi,num[mex]),mex++;
				if(mex>ma-mi+1) ans=max(ans,mex);
			}
		}for(int j=l+1;j<r;j++) num[a[j]]=0;
	}cout<<ans-1;
	return 0;
}
```
~~最优解.jpg~~





---

