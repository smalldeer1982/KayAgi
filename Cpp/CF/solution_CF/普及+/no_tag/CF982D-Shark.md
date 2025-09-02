# Shark

## 题目描述

科学家们研究鲨鱼的习性已经有一段很长的时间了。鲨鱼，就像其他的生物一样，在某一地点交替短途移动, 并在不同地点之间长途移动。

Max 是一位年轻的生物学家。他观察一只特别的鲨鱼已有 $n$ 天，现在他也清楚地知道这只鲨鱼在某一天游动的距离。每天鲨鱼游动的距离都是不同的。Max 想知道鲨鱼抵达了多少个位置。他假定：如果鲨鱼在某天游动的距离严格小于 $k$，那么它的位置不发生变化；否则，如果鲨鱼在某天游动的距离大于或等于 $k$，则它的位置在那天发生了变化。注意：有可能鲨鱼的位置连续几天都发生了变化，只要这几天每天鲨鱼游动的距离都至少为 $k$。

从某个地方游走后，鲨鱼就不会再回来了。也就是说，我们可以将这个 $n$ 天的序列划分成若干断连续的、非空子段，使得每一子段内每天鲨鱼游动的距离都小于 $k$，那么每一个子段就代表一个位置。Max 想找出这样的 $k$，使得每个子段的长度都相等。

找到这样的整数 $k$，令位置的数量尽可能地多。如果存在多个满足条件的 $k$，输出最小的一个。

## 样例 #1

### 输入

```
8
1 2 7 3 4 8 5 6
```

### 输出

```
7```

## 样例 #2

### 输入

```
6
25 1 2 3 14 36
```

### 输出

```
2```

# 题解

## 作者：QwQcOrZ (赞：7)

其它题解做法看上去比较麻烦，发个简单点的

先把 $a_i$ 升序排序，这样就相当于每次加一个点，然后判断这些子段是否合法，并找出使子段最多的最小的 $k$

考虑用并查集维护每个区间（接下来都将子段视为若干个区间）

![](https://cdn.luogu.com.cn/upload/image_hosting/vium67fr.png)

每次加点无非就三种情况：

1. 合并两段区间
2. 延长一段区间
3. 新建一段区间

维护的具体实现只需要用一个 $f$ 数组记录每个点是否被加入过，并且每次合并对应的区间即可

接下来考虑如何判断这些区间是否合法

更新区间后显然区间的长度只会变长，不会变短

那么考虑动态维护几个简单的东西：区间的总数量，最长区间的长度，长度等于最长区间的区间个数，合法区间的最大个数及此时最小的 $k$

这些显然在合并区间是可以轻松维护（具体可以看代码实现）

那么也就是说当 区间的总数量$=$长度等于最长区间的区间个数 时，这些区间是合法的。此时可以用区间的总数去更新答案，最后输出最优解即可

$Code\ Below$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;

inline int read()
{
	register int s=0;
	register char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(register int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
inline void print(const register int x,const register char c='\n')
{
	write(x);
	putchar(c);
}
bool f[N];
int p[N],a[N],fa[N],siz[N];
bool cmp(int x,int y)
{
	return a[x]<a[y];
}
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
	int u=find(x),v=find(y);
	fa[u]=v;
	siz[v]+=siz[u];
}

int main()
{
	memset(f,0,sizeof(f));
	int n=read();
	for (int i=1;i<=n;i++) p[i]=fa[i]=i,siz[i]=1;
	for (int i=1;i<=n;i++) a[i]=read();
	sort(p+1,p+1+n,cmp);
	int tot=0,cnt=0,L=1,Max=0,ans;//tot区间的总数量，cnt长度等于最长区间的区间个数，L最长区间的长度，Max合法区间的最大个数及此时最小的答案ans
	for (int i=1;i<=n;i++)
	{
		int now=p[i];
		f[now]=1;
		if (!f[now-1]&&!f[now+1])
		{
			tot++;
			if (L==1) cnt++;
		}
		else if (f[now-1]&&f[now+1])
		{
			tot--;
			merge(now-1,now);
			merge(now+1,now);
			if (siz[now]>L)
			{
				L=siz[now];
				cnt=1;
			}
			else if (siz[now]==L) cnt++;
		}
		else
		{
			if (f[now-1]) merge(now-1,now);
			if (f[now+1]) merge(now+1,now);
			if (siz[now]>L)
			{
				L=siz[now];
				cnt=1;
			}
			else if (siz[now]==L) cnt++;
		}
		if (tot==cnt)
		if (tot>Max)
		{
			Max=tot;
			ans=a[now]+1;
		}
	}
	print(ans);

	return 0;
}
```

---

## 作者：Acfboy (赞：3)

翻译有点啰嗦了，其实这题输入一串数，要求你找到一个满足以下条件的 $k$。

1. 所有小于 $k$ 的数组成的连续子段长度要相等。
2. 满足 $1$ 的情况下段尽可能多。
3. 满足前两条的情况下 $k$ 尽可能小。

遇到这样限制很多的题目，一般考虑排个序去掉一个再考虑剩下的，所以直接排个序然后依次插入就保证满足 $1$ 了。

那么只需要考虑怎么处理子段就行了。这题没有对一段里面数相对位置的要求，所以看成集合，用并查集即可。合并的时候顺便记录一下每个集合的大小，以及最大的，如果集合大小等于最大的的数量就是集合的数量就可以更新答案了。

代码其实很短啊，为什么其它题解看上去那么长。  

```cpp
// eq 是大小和最大的相等的段的数量，ml 是最大的大小，num 是集合数
void add(int x) {
	flag[x] = 1;
	flag[x-1] && (num --, eq -= size[find(x-1)] == ml, merge(x, x-1)), 
	flag[x+1] && (num --, eq -= size[find(x+1)] == ml, merge(x, x+1));
	num ++;
	int t = size[find(x)];
	if(ml < t) eq = 1, ml = t;
	else if(ml == t) eq ++;
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", &a[i].v), a[i].id = i;
	std::sort(a+1, a+1+n);
	for(int i = 1; i <= n; i++) fa[i] = i, size[i] = 1;
	for(int i = 1; i <= n; i++) {
		add(a[i].id);
		if(num == eq && (num > ann || (num == ann && ank > a[i].v+1))) 
			ank = a[i].v+1, ann = num;
	}
	printf("%d", ank);
}
```

---

## 作者：redegg (赞：3)

题目意思：

给你一个序列$a$，让你求出一个$k$，$a$中小于$k$的部分形成了很多段连续的序列，要求这些序列必须全部一样长，并且要求序列的数量尽量多，在序列数量最多的情况下要求$k$最小。

那么我们用一个更好理解的模型来说明，我们看成这里有个一维沙盒，$a_i$表示$i$地区的地面高度，现在我们给定一个水位$k$，小于$k$的地方都被水淹没了，被淹没的区域被没被淹没的区域隔开了。

现在我们假设通过序列来建立了一棵二叉树，$son$表示子节点，$father$则是父亲节点，这棵二叉树中保证$a[i] \ge a[son[i]]$，那么$i$点与$son[i]$的关系是，当$i$点被淹没后，他的左儿子$lson[i]$和右儿子$rson[i]$本来是两个分开的被淹没的块，现在变成了一块被淹没的块了。那么同理，当$father[i]$被淹没，$i$点和他所有子节点形成的那个被淹没的块就会和$father[i]$的另一个子节点所属的被淹没的块合并。

我们建立有这样性质的二叉树，我暂时只想到了通过线段树，我们设找到区间$[l,r]$里面最大值的位置的函数为$max[l,r]$，然后当$x=max[l,r]$，有$father[max[l,x-1]]=x$和$father[max[x+1,r]]=x$，这样便构建一个有这样性质的二叉树

剩下的，便是从小到大枚举点，相当于添点，添点$i$后，$i$所在的子树的结点树便是它所在的被淹没的块的长度，那么我只需要记录一个现在有多少个独立的还没有合并的二叉树$tree$，记录一下这些树中等于现在最长淹没块的数量$u$，记录一下现在最长的淹没块长度$now$，当$u=tree$时更新答案就好了。

剩下的看代码吧。

```
#include <bits/stdc++.h>
using namespace std;


int n;

struct in
{
    int maxn,id;
    bool operator < (const in &aa)const
    {
        return maxn<aa.maxn;
    }
}b[100005];
in c[500005];
int a[100005];

bool cmp(const in &aa,const in &bb)
{
    return aa.maxn<bb.maxn;
}

//---------------------------------

void build(int l,int r,int id)
{
    if(l==r)
    {
        c[id].maxn=a[l];
        c[id].id=l;
        return ;
    }
    int mid=(l+r)/2;
    build(l,mid,id*2);
    build(mid+1,r,id*2+1);
    c[id]=max(c[id*2],c[id*2+1]);
}

in cck(int l,int r,int z,int y,int id)//区间最大值
{
    if(l==z&&r==y)
        return c[id];
    int mid=(l+r)/2;
    if(mid>=y)return cck(l,mid,z,y,id*2);
    else if(mid<z)return cck(mid+1,r,z,y,id*2+1);
    else return max(cck(l,mid,z,mid,id*2),cck(mid+1,r,mid+1,y,id*2+1));
}


//-------------------------------------


int l[100006];//左儿子
int r[100006];//右儿子
int t[100005];//子树个数
int v[100005];//子树点数

int now;//现在这些独立的树中最大的点数
int u;//点数等于现在独立的树中最大点数的树的个数
int tree;//现在独立的树的个数
int an;//最大的相等分段数
int ans;//答案

int dfs(int x,int z,int y)//建树
{
    if(z>y)return 0;
    int nx=cck(1,n,z,y,1).id;
    v[nx]++;
    if(nx<x)
        l[x]=nx;
    if(nx>x)
        r[x]=nx;
    t[x]++;
    if(nx+1<=y)
        v[nx]+=dfs(nx,nx+1,y);
    if(nx-1>=z)
        v[nx]+=dfs(nx,z,nx-1);
    return v[nx];
}

void run()
{
    build(1,n,1);
    int first=cck(1,n,1,n,1).id;
    if(first+1<=n)
        v[first]+=dfs(first,first+1,n);
    if(first-1>=1)
        v[first]+=dfs(first,1,first-1);
    v[first]++;
    an=1;
    ans=b[1].maxn;

    for(int i=1;i<=n;i++)//从小到大加点
    {
        int x=b[i].id;
        tree-=(t[x]-1);

        if(v[x]==now)
            u++;
        if(v[x]>now)
        {
            u=1;
            now=v[x];
        }
        if(u==tree&&u>an)//当所有独立的树都是同样长时，更新答案
        {
            an=u;
            ans=b[i].maxn;
        }
    }

}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        b[i].maxn=a[i];
        b[i].id=i;
    }
    sort(b+1,b+1+n,cmp);
    run();
    printf("%d\n",ans+1);
    return 0;
}
```

---

## 作者：jch123 (赞：2)

## 思路：

显然可以先对 $a$ 排序，然后一个一个去求 $k$。每加入一个数，只会新建一段区间、合并两段区间、延长一段区间。加入一个数后区间长度不会变短。可以维护区间总数量、最长区间长度、长度等于最长区间长度的区间数量，然后就能更新合法区间的最大个数与目前答案 $k$。当区间总数量与长度等于最长区间长度的区间数量相等时，则可以更新答案。可以用并查集来做。

## 代码：

 ```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int fa[N],sz[N],book[N];
struct node
{
	int x,id;
}a[N];
bool cmp(node q,node w){return q.x<w.x;}
int find(int x)
{
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx!=fy)
	{
		fa[fx]=fy;
		sz[fy]+=sz[fx];
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		fa[i]=i,sz[i]=1;
	for(int i=1;i<=n;i++)
		cin>>a[i].x,a[i].id=i;
	sort(a+1,a+1+n,cmp);
	int at=0,cnt=0,len=1;//区间总数量、长度等于最长区间长度的区间数量、最长区间长度 
	int maxn=0,ans=0;//合法区间的最大个数、此时最小的k 
	for(int i=1;i<=n;i++)
	{
		int p=a[i].id;
		book[p]=1;
		if(book[p-1]==0&&book[p+1]==0) 
		{
			at++;
			if(len==1) cnt++;
		}
		else if(book[p-1]&&book[p+1])
		{
			at--;
			merge(p-1,p),merge(p+1,p);
			if(sz[p]>len) len=sz[p],cnt=1;
			else if(sz[p]==len) cnt++;
		}
		else
		{
			if(book[p-1]) merge(p-1,p);
			if(book[p+1]) merge(p+1,p);
			if(sz[p]>len) len=sz[p],cnt=1;
			else if(sz[p]==len) cnt++;
		}	
		if(at==cnt&&at>maxn)
			maxn=at,ans=a[i].x+1;
	}
	cout<<ans;
	return 0;
}
 ```

---

## 作者：Yeji_ (赞：2)

## 前言
令人烦躁的并查集。
## 思路

这道题首先想到的就是把序列 a 排序，存入一个新的数组 b 中，为了使 k 尽量小，所以用每个扫一遍原数组 a 判断是否符合要求。但是这样的时间复杂度是 O(n^2)

其实我们可以用并查集来维护，我们在排序的时候将数据的下标存下来，然后用一个数组sum来存以 i 为根结点的的集合大小，用一个数组 cum 来存大小为 i 的集合个数，用 cnt 来存所有集合的个数。

我们每找一个从 b 数组中每找一个数就看它原本数组下标的前一个位置，如果小于就和前面一个位置合并。

然后判断 cnt 是否等于，如果等于，就表明这个数加1符合条件，将答案更新。

给出代码
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int fa[110001],a[110001],cnt,sum[110001],cum[110001],ans,maxn,n;;
struct node
{
    int val,index;
}b[110001];
bool cmp(node a,node b){return a.val<b.val;}
int find(int x)
{
    if(fa[x]==x)
        return x;
    return fa[x]=find(fa[x]);
}
void merge(int a,int b)
{
    a=find(a);b=find(b);
    cum[sum[a]]--;cum[sum[b]]--; 
    sum[a]+=sum[b];
    fa[b]=a;cum[sum[a]]++;cnt--;
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        b[i].val=a[i];b[i].index=i;
        fa[i]=i;
    }
    sort(b+1,b+1+n,cmp);
    for(int i=1;i<=n;i++)
    {
        int ind=b[i].index;
        sum[ind]=1;cum[sum[ind]]++;
        cnt++;
        if (ind!=1&&a[ind-1]<=a[ind])
            merge(ind-1,ind);
        if (ind!=n&&a[ind+1]<=a[ind])
            merge(ind,ind+1);
        for (;b[i].val==b[i+1].val&&i!=n;i++)
        {
            ind=b[i].index;sum[ind]=1;
            cum[sum[ind]]++;cnt++;
            if (ind!=1&&a[ind-1]<=a[ind])
                merge(ind-1,ind);
            if (ind!=n&&a[ind+1]<=a[ind])
                merge(ind,ind+1);
        }
        if (cnt==cum[sum[find(b[i].index)]])
            if (cnt>maxn)
            {
                maxn=cnt;
                ans=b[i].val+1;
            }
    }
    printf("%d",ans);
}
```


---

## 作者：anonymous_Y (赞：0)

这道题的题目真的超级难懂至少对于我而言。

首先，对于一个 $a_i \geq k$，我们并不是把他单独开一个区间，而是直接忽略他，把它当作一个区间的结束和另一段区间的开始。

其次，对于一个满足条件的 $k$，要使得到的每一个区间长度相等。


题面讲完之后我们来说说思路。其实不难发现答案一定是 $a_i+1$，为什么？我们可以发现将数组 $a$ 从小到大排序后，在 $a_i \sim a_{i+1}$ 这个范围内，对于原数组而言不会加入新的值，所以答案一定是 $a_i+1$。

看到 $k$ 的数据范围太大，而 $n$ 的范围在 $10^5$，同时答案和 $a_i$ 有关，那我们是不是可以枚举一遍 $a$ 数组？

这个时候我们将要进行一个至关重要的操作——排序。此时我们会发现，如果每次将 $k$ 改到一个新的 $a_i+1$ 实质上有三种操作的可能：合并两段区间，延长一段区间，新建一段区间。

这时候问题就很简单了。

我们用一个并查集进行区间合并，统计操作，判断是否符合要求就好了。

---

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+10;
const int inf=0x3f3f3f3f;
int fa[maxn],n,a[maxn],sz[maxn],b[maxn];
int cnt[maxn],ann;
int ans,loc;
map <int,int> mp;
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	fa[fy]=fx;
	cnt[sz[fx]]--,cnt[sz[fy]]--;
	sz[fx]+=sz[fy];
	cnt[sz[fx]]++;
	//ann--;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];b[i]=a[i];
		mp[a[i]]=i;
		sz[i]=1;
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) fa[i]=i;
	b[0]=inf,b[n+1]=inf;
	for(int i=1;i<=n;i++){
		int x=mp[a[i]];
		//a[i]++;
		if(b[x-1]>a[i]&&b[x+1]>a[i]){
			cnt[1]++;ann++;
			if(cnt[1]>ans&&ann==cnt[1]){
				ans=cnt[1];loc=a[i];
			}
			continue;
		}
		if(b[x-1]<a[i]&&b[x+1]>a[i]){
			merge(x,x-1);
			//cout<<1<<" "<<sz[x]<<" "<<cnt[sz[x]]<<" "<<ann<<endl;
			if(cnt[sz[x]]>ans&&ann==cnt[sz[x]]){
				ans=cnt[sz[x]];loc=a[i];
			}
		}
		if(b[x+1]<a[i]&&b[x-1]>a[i]){
			merge(x,x+1);
			//cout<<2<<" "<<sz[x]<<" "<<cnt[sz[x]]<<" "<<ann<<endl;
			if(cnt[sz[x]]>ans&&ann==cnt[sz[x]]){
				ans=cnt[sz[x]];loc=a[i];
			}
		}
		if(b[x+1]<a[i]&&b[x-1]<a[i]){
			merge(x,x+1);merge(x,x-1);ann--;
			//cout<<3<<" "<<sz[x]<<" "<<cnt[sz[x]]<<" "<<ann<<endl;
			if(cnt[sz[x]]>ans&&ann==cnt[sz[x]]){
				ans=cnt[sz[x]];loc=a[i];
			}
		}
		//cout<<a[i]<<endl;
	}
	cout<<loc+1<<endl;
	return 0;
}
/*8
1 2 7 3 4 8 5 6*/
```
完结撒花！

---

## 作者：紊莫 (赞：0)

题意较难理解，放出简述：

求一个 $k$ 使得：  
1. 所有小于 $k$ 的数构成的一些连续段的长度相同。
2. 连续段尽可能多。
3. 在满足上述条件下 $k$ 尽可能小。

例如样例一在钦定 $k=7$ 时会分成 ``12(7)34(8)56`` 三段（括号内是被拿掉的数字，视作不存在）。

然后考虑从小到大枚举这个 $k$，发现随着 $k$ 的增大，这个段会越来越大，会合并，会扩展，于是考虑用并查集维护段与段之间的关系，然后记录集合的大小即可知道段长。

具体的，我们按照 $a_i$ 升序排列，然后对于每个 $a_i$，将其标记为合法，和左右尝试去合并即可，同时维护段的个数，极长段的长度，极长段的个数，以及我们的答案和答案能分到的段数。

[示例代码。](https://codeforces.com/contest/982/submission/244494500)

---

## 作者：doctorZ_ (赞：0)

#### 题目大意：      
给你一个序列 $a$，让你求出一个 $k$ ，$a$ 中小于 $k$ 的部分形成了很多段连续的序列，要求这些序列必须全部一样长，并且要求序列的数量尽量多，在序列数量最多的情况下要求 $k$ 最小。     
这道题首先想到的就是把序列 $a$ 排序，存入一个新的数组 $b$ 中，为了使 $k$  尽量小，所以用每个 $b_1+1$ 来扫一遍原数组 $a$ 判断是否符合要求，如果可以以就将答案更新。但是这样的时间复杂度是 $O(n^2)$的，很明显过不了。      
其实我们可以用并查集来维护，我们在排序的时候将数据的下标存下来，然后用一个数组$sum$来存以 $i$ 为根结点的的集合大小，用一个数组 $cntsum$ 来存大小为 $ i$ 的集合个数，用 $cnt$ 来存所有集合的个数。我们每找一个从 $b$ 数组中每找一个数就看它原本数组下标的前一个位置，如果小于就和前面一个位置合并。后一个位置同理。然后判断 $cnt$ 是否等于 $cntsum[sum[这个数在原数组中的下标]]$，如果等于，就表明这个数加1符合条件，将答案更新。   
#### CODE:
```cpp
#include<cstdio>
#include<algorithm>
#define N 110000
using namespace std;
int fa[N+1],a[N+1],cnt,sum[N+1],cntsum[N+1];
struct node
{
	int val,index;
}b[N+1];
bool cmp(node a,node b)
{
	return a.val<b.val;
}
int find(int x)
{
	if(fa[x]==x)
		return x;
	return fa[x]=find(fa[x]);
}
void merge(int a,int b)
{
	a=find(a); b=find(b);
	cntsum[sum[a]]--; cntsum[sum[b]]--;//和并时要维护cnt,cntsum,sum 
	sum[a]+=sum[b];
	fa[b]=a;
	cntsum[sum[a]]++;
	cnt--;
}
int ans,maxn;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i].val=a[i];
		b[i].index=i;
		fa[i]=i;
	}
	sort(b+1,b+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
//		printf("i %d cnt %d\n",i,cnt);
		int pos=b[i].index;
		sum[pos]=1;
		cntsum[sum[pos]]++;
		cnt++;
		if(pos!=1&&a[pos-1]<=a[pos])
			merge(pos-1,pos);
		if(pos!=n&&a[pos+1]<=a[pos])
			merge(pos,pos+1);
		for(;b[i].val==b[i+1].val&&i!=n;i++)
		{
			pos=b[i].index;
			sum[pos]=1;
			cntsum[sum[pos]]++;
			cnt++;
			if(pos!=1&&a[pos-1]<=a[pos])
				merge(pos-1,pos);
			if(pos!=n&&a[pos+1]<=a[pos])
				merge(pos,pos+1);
		}
		if(cnt==cntsum[sum[find(b[i].index)]])
			if(cnt>maxn)
			{
				maxn=cnt;
				ans=b[i].val+1;
			}
	}
	printf("%d",ans);
	return 0;
}
```



---

