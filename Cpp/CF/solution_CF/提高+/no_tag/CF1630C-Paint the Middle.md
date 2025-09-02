# Paint the Middle

## 题目描述

You are given $ n $ elements numbered from $ 1 $ to $ n $ , the element $ i $ has value $ a_i $ and color $ c_i $ , initially, $ c_i = 0 $ for all $ i $ .

The following operation can be applied:

- Select three elements $ i $ , $ j $ and $ k $ ( $ 1 \leq i < j < k \leq n $ ), such that $ c_i $ , $ c_j $ and $ c_k $ are all equal to $ 0 $ and $ a_i = a_k $ , then set $ c_j = 1 $ .

Find the maximum value of $ \sum\limits_{i=1}^n{c_i} $ that can be obtained after applying the given operation any number of times.

## 说明/提示

In the first test, it is possible to apply the following operations in order:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1630C/7c496bb097d511fd66adf529c361a9334d75c9e9.png)

## 样例 #1

### 输入

```
7
1 2 1 2 7 4 7```

### 输出

```
2```

## 样例 #2

### 输入

```
13
1 2 3 2 1 3 3 4 5 5 5 4 7```

### 输出

```
7```

# 题解

## 作者：liuhongyang123 (赞：16)

# 题意

给出一个长度为 $n$ 的序列 $a$。

还有一个初始为 $0$ 的数组 $c$。

可以执行以下操作**任意**次：

> 选择三个元素 $i$, $j$ 和 $k$（$1 \leq i < j < k \leq n$）。
> 
> 条件：$c_i=c_j=c_k=0$ 且 $a_i=a_k$。
> 
> 效果：$c_j=1$。

求操作后 $\sum\limits_{i=1}^n{c_i}$ 的最大值。

# 做法

一眼 ```DP```。

> 设 $f_i$ 表示区间 $1$ 到 $i$ 的没有贡献的数的个数，$lst_i$ 表示元素 $i$ 第一次在 $a_i$ 中的下标。

初始化，$f_1=1$，因为第一个怎么操作都不可能有贡献。

对于每一个 $i$，他可以把 $lst_{a_i}+1$ 到 $i-1$ 赋值，我们枚举 $j$，其中 $\min(lst_{a_i},i-1)\leq j \leq i-1$，考虑将 $j+1$ 到 $i-1$ 赋值。所以 $f_i=f_j+1$，这个 $+1$ 是算上 $i$ 本身无法赋值。

那么 ```DP``` 方程式也就呼之欲出：

> $f_i=\min\limits_{j=\min(lst_{a_i},i-1)}^{i-1}f_j+1$

可这 $n^2$ 的时间复杂度肯定过不了，用个线段树维护一下区间最小值就行了。

~~做蓝题的人应该没有不会线段树吧。~~

但是，有人要问了，如果 $lst_{a_i}$ 的 $c$ 为 $1$ 你都不知道那不是出锅了吗。

表面上来看，这样的问题确实存在，看似不可做，但仔细一想就可发发现，你总能改变赋值顺序来做到理想的贡献（手模几个样例理解更深）。

# Code

```cpp
#include<bits/stdc++.h>
#define ls(a) a<<1
#define rs(a) a<<1|1
using namespace std;
const int MAXN=1e6+10;
const int INF=1e9+7;
int n,g,a[MAXN],tree[MAXN],lst[MAXN];
//----------------线段树板子（求最小值）------------- 
void push_up(int x){
	tree[x]=min(tree[rs(x)],tree[ls(x)]);
}
void build(int x,int l,int r){
	if(l==r){
		tree[x]=INF;
		return;
	} 
	int mid=(l+r)>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	push_up(x);
}
void update(int ql,int qr,int l,int r,int x,int k){
    if(ql<=l&&r<=qr){
    	tree[x]=min(tree[x],k);
        return ;
    }
    int mid=(l+r)>>1;
    if(ql<=mid) update(ql,qr,l,mid,ls(x),k);
    if(qr>mid) update(ql,qr,mid+1,r,rs(x),k);
    push_up(x);
}
int query(int ql,int qr,int l,int r,int x){
    int ans=INF;
    if(ql<=l&&r<=qr) return tree[x];
    int mid=(l+r)>>1;
    if(ql<=mid) ans=min(ans,query(ql,qr,l,mid,ls(x)));
    if(qr>mid) ans=min(ans,query(ql,qr,mid+1,r,rs(x)));
    return ans;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=n;i>=1;i--) lst[a[i]]=i;
	build(1,1,n),update(1,1,1,n,1,1);//初始化，第一个肯定没贡献 
	for(int i=2;i<=n;i++) g=query(min(lst[a[i]],i-1),i-1,1,n,1)+1,update(i,i,1,n,1,g);
	//DP
	printf("%d",n-g);//答案为：总的-没贡献的 
	return 0;
}
```

### 完结散花

---

## 作者：清烛 (赞：10)

## Description
给定长度为 $n$ 的序列 $a_i$，一开始 $c_i = 0$。可以进行如下操作：

- 选择 $1\le i < j < k\le n$，满足 $c_i = c_j = c_k = 0\land a_i = a_k$，然后 $c_j:=1$。

问若干次操作之后最大的 $\sum_{i = 1}^nc_i$。$3\le n\le 2\times 10^5$。

## Solution
提供一种相当简洁的做法，该做法来自[评论区](https://codeforces.com/blog/entry/99384?#comment-881614)。

考虑一个 DP，设 $f_i$ 为区间 $[1, i]$ 的答案，显然 $f_1 = 0$。有如下 $3$ 种转移到 $f_i$ 的办法：

- $a_i$ 在 $a_j$ 出现过（$j < i$），考虑将 $(j, i)$ 全部涂色，则 $f_i = f_j + (i - j - 1)$。
- $a_i$ 在 $a_k$ 出现过（$k < j < i$），考虑取 $f_j$ 的最优解但是留下 $c_k$ 不涂，然后再涂上 $[j, i)$，同样有 $f_i = f_j + i - j - 1$。
- 直接继承 $f_{i - 1}$，写规范一点就是 $f_i = f_{i - 1} + (i - (i - 1) - 1)$。

于是若我们令 $\mathrm {first}(a_i)$ 表示 $a_i$ 第一次出现时的下标，则转移方程就有了：
$$
f_i = \max_{\mathrm{first}(a_i)\le j < i}\{f_{j} - j \} + i - 1
$$
此时这个做法是 $O(n^2)$ 的，需要优化。改写转移方程：
$$
f_i - i = \max_{\mathrm{first}(a_i)\le j < i\lor j = i - 1}\{f_{j} - j \} - 1
$$
不难发现这可以拿一个维护 $f_i - i$ 的最大值的线段树来优化，于是 $O(n\log n)$。

## Implementation
```cpp
const int maxn = 2e5 + 5;
int t[maxn << 2], n, a[maxn], first[maxn];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void modify(int i, int j, int k, int x, int v) {
    if (i == j) {
        chkmax(t[k], v);
        return;
    }
    if (x <= M) modify(i, M, L, x, v);
    else modify(M + 1, j, R, x, v);
    t[k] = max(t[L], t[R]);
    return;
}

int query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k];
    int ret = -1e9;
    if (x <= M) chkmax(ret, query(i, M, L, x, y));
    if (y > M) chkmax(ret, query(M + 1, j, R, x, y));
    return ret;
}

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]);
    DEC(i, n, 1) first[a[i]] = i;
    memset(t, 0x80, sizeof t);
    modify(1, n, 1, 1, -1);
    FOR(i, 2, n) {
        int now = query(1, n, 1, min(first[a[i]], i - 1), i - 1) - 1;
        modify(1, n, 1, i, now);
        if (i == n) print(now + n);
    }
    return output(), 0;
}
```

---

## 作者：vectorwyx (赞：9)

把每个值出现的位置单拎出来，显然中间的那些都不用管，不平凡的在于第一次出现的位置和最后一次出现的位置。把这些二元组看做线段，那么所有线段的并集减去所有线段的端点一定都能染色，问题在于最多能染几个端点。

首先如果某条线段被其他线段所包含，那这条线段的两个端点先全都染色肯定是不劣的。排除掉这些线段，剩下的线段会形成若干个连通块，每个连通块之间显然独立，所以对每个连通块单独考虑。

我们的策略肯定是先选出若干条线段，用这些线段把其他没选的线段的端点全都干掉，剩下的互相了断，假设所选出的线段共有 $x$ 条，有个平凡的解是干掉 $x-1$ 个端点，换句话说只有最开始的线段是两个端点都无法染色，其余的线段都可以被干掉一个端点。

你再仔细想想非平凡的情况都能归到平凡的情况里去，因为这里暗含着一个限制是**所选出的线段必须覆盖整个连通块对应的区间**。为什么？如果说把这个连通块分裂成两个块分别做，假设分别选出了集合 $A,B$，那我加一条横跨两个集合的线段进去一定不劣，因为这两个块之间一定有间隙，我加入这条线段后会至少收获 $1$ 的收益，而有一个平凡的解是 $x-1$ 保证了我增加的代价不会超过 $1$。而平凡的情况中会有一个两端点都不染色的线段，这个是没法避免的，因为你最后总要拿一条线段去把别的线段端点干掉。所以非平凡的情况只能是把一些线段的两个端点都干掉了，也就是在保证其余线段能覆盖整个区间的前提下去掉某些线段。那这问题是啥？选最少的线段覆盖整个区间！直接贪心，做完了/cy。

代码如下：

```cpp
//author:望远星
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1;char ch=getchar();while(!isdigit(ch)){if(ch=='-')fh=-1;ch=getchar();}while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}return x*fh;}
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=1e6+5;
int mp1[N],mp2[N],a[N],n,m,top;
pii b[N],c[N];

int solve(){
	if(top<=0) return 0;
	int r=c[1].se,cnt=1,mx=0;
	fo(i,2,top){
		if(c[i].fi>r){
			cnt++;
			r=mx;
			mx=0;
		}
		big(mx,c[i].se);
	}
	if(r<c[top].se) cnt++;
	return c[top].se-c[1].fi-cnt;
}

signed main(){
	cin>>n;
	fo(i,1,n) a[i]=read();
	fo(i,1,n) mp1[i]=0,mp2[i]=n+1;
	go(i,n,1) mp1[a[i]]=i;
	fo(i,1,n) mp2[a[i]]=i;
	fo(i,1,n) if(mp2[i]-mp1[i]!=n+1&&mp2[i]!=mp1[i]) b[++m]=mk(mp1[i],mp2[i]);
	sort(b+1,b+1+m);
	int ans=0;
	fo(i,1,m){
		if(!top) c[++top]=b[i];
		else if(b[i].se>c[top].se){
			if(b[i].fi>c[top].se){
				ans+=solve();
				top=0;
			}
			c[++top]=b[i];
		}
	}
	ans+=solve();//c[top].se-c[1].fi+1-(top+1);
	cout<<ans<<'\n';
	return 0;
}
/*
6
3 4 5 3 4 5
-------------------------------------------------
3
*/

```


---

## 作者：Daidly (赞：8)

虽然有 dp 解法，但是我觉得这题贪心很自然。

对于一个值，我们只需要记录最左和最右段的下标，将它们看成线段。

对于线段之间的包含情况，可以直接舍去被包含的区间，因为无论如何也没有多余贡献。

这些在 $[1,n]$ 之间被筛过的线段满足：端点不交，互不包含。

考虑按左端点排序，对于与其他线段无交的，可以直接算出贡献 $r_i-l_i-1$。

而对于若干条线段重叠覆盖则需要考虑端点情况，即若端点被染色，则线段作废，记 $[l_i,r_i]\sim [l_j,r_j]$ 覆盖了区间 $[L,R]$，其中 $i<j$ 且 $l_i$ 递增。

显然，所有非端点的位置可以完成染色，而剩下的 $j-i+1$ 条线段共 $2(j-i+1)$ 个端点的分配需要注意。

如何分配染色使得 $2(j-i+1)$ 个端点有尽可能多的端点被染色，一种显而易见的染色策略是第 $k$ 条线段染去第 $k-1$ 条线段的右端点，这种策略只能染去 $(j-i)$ 个端点，似乎有些太固定了。考虑一种 hack 情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/dsnv2uth.png)

中间的线段端点是被包含的，能染色并且有一种方式可以染色。

所以说我们只需要找到一些线段能覆盖 $[L,R]$，那么剩下的线段两端都能选掉。而我们想让覆盖的点尽可能多，所以选择的线段尽可能少，转换成了区间覆盖问题，可以贪心解决。选择的线段按照之前的线段数减一策略，不选的线段按照总体，计入答案中即可。

复杂度 $O(n\log n)$，瓶颈在排序。

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=2e5+5;
int n,a[N],tmp,num,ans,l[N],r[N];
struct node{
	int L,R;
	bool operator<(const node &p)const{return (L==p.L)?R<p.R:L<p.L;}
}p[N],q[N];

int main(){
	n=read();
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=n;++i){
		if(!l[a[i]])l[a[i]]=i,r[a[i]]=i;
		else r[a[i]]=i;
	}
	for(int i=1;i<=n;++i){
		if(l[i]>0&&l[i]+1<r[i])p[++tmp]=(node){l[i],r[i]};
	}
	sort(p+1,p+tmp+1);
	for(int i=1;i<=tmp;++i){
		int nxt=i+1;
		while(nxt<=tmp&&p[nxt].R<=p[i].R)nxt++;
		q[++num]=p[i];
		i=nxt-1;
	}
	int cnt,ll,rr;
	for(int i=1;i<=num;++i){
		int nxt=i+1;ll=q[i].L,rr=q[i].R,cnt=1;
		while(q[nxt].L<rr&&nxt<=num){
			while(q[nxt].L<rr&&nxt<=num)nxt++;
			rr=q[nxt-1].R,cnt++;
		}
		ans+=rr-ll-cnt;
		i=nxt-1;
	}
	print(ans);
	return 0;
}
```



---

## 作者：Wander_E (赞：3)

很自然地想到贪心。

对于每个位置明显只能染一次色，于是这题就转化成了：选若干个互不相交的线段使得它们的长度总和最大。

不难发现如果有某个数出现多次，一定是取头尾两个最优，这样组成的区间最大。所以我们只要记录每个数最后一次出现的位置（记为 $pos_{a_i}$），再顺序遍历，从首次出现的位置开始一直染到 $pos_{a_i}$ 即为答案。

时间复杂度 $O(n)$。

代码异常好写：
```cpp
for (int i = 1; i <= n; i++)
{
    maxn = max(maxn, pos[a[i]]);
    if (end > i)
        ans++;
    else
        end = maxn;
}
```

---

## 作者：XL4453 (赞：3)

### $\text{Difficulty : 2200}$

---
### 解题思路：

首先进行简单的问题转化。

先将所有的相同的数字中取第一个和最后一个作为可染色区间，其余的数字直接无视，因为一定可以利用第一个和最后一个做到任何一个中间小区间能做到任何染色。

可以将这些可染色区间缩掉一些，任何完全包含在另一个可染色区间的区间都可以直接删除，理由同样是大区间可以做到任意小区间能做到的染色。（分成两步可能会好理解一点，也可以用统一定义，也不是很难。）

到此也就是一堆不互相包含的区间，选择一些按照一定顺序染色，满足每一次染色时左右端点都没有被染色。当区间没有相交的时候，直接全都染上就行了，关键就在于如何处理有交集的区间。

---
不妨考虑从左往右依次考虑染色（否则一定能转化一种结果相同的从左往右的染色方式），那么每一次利用某一个区间染色就一定要求之前为这个区间留下一个位于端点处的空白点。换言之，就是染色用的区间数量每多一个，能染到色的点就少一个。而一个不被包含的区间至少有一个位置包括其他空白位置，所以最后选出的区间把整个可能的范围都覆盖一定是一种不劣的解。

所以问题最后就转换为若干个区间中取若干区间使得整个可能的覆盖的范围被完全覆盖。

这是一个比较经典的贪心问题，按照左端点排序，从相交区间选择右端点最靠右的一个就行了。

---
### 代码：

```cpp
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int MAXN=400005;
struct str{
	int l,r;
	bool operator <(str a){
		if(l==a.l)return r<a.r;
		return l<a.l;
	}
}s[MAXN];
int n,col[MAXN],l[MAXN],r[MAXN],book[MAXN],cnt,ans,maxn;
queue <int> q;
void work(int now){
	if(s[now].r<=maxn){
		book[now]=1;
		return;
	}
	q.push(now);int i=now+1;
	book[now]=1;maxn=max(maxn,s[now].r);
	int ll=s[now].l,tot=-1,maxi=-1;
	while(!q.empty()){
		now=q.front();
		q.pop();
		maxi=-1;
		for(;i<=cnt;i++){
			if(s[now].r<s[i].l)break;
			book[i]=1;
			if(s[i].r>=maxn){
				maxn=s[i].r;
				maxi=i;
			}
		}
		tot++;
		if(maxi!=-1)
		q.push(maxi);
	}
	ans+=maxn-ll-1-tot;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)l[i]=2147483647;
	for(int i=1;i<=n;i++){
		scanf("%d",&col[i]);
		l[col[i]]=min(l[col[i]],i);
		r[col[i]]=max(r[col[i]],i);
	}
	for(int i=1;i<=n;i++){
		if(l[i]<r[i]-1){
			s[++cnt].l=l[i];
			s[cnt].r=r[i];
		}
	}
	s[cnt+1].l=2147483647;
	sort(s+1,s+cnt+1);
	for(int i=1;i<=cnt;i++){
		if(book[i])continue;
		else work(i);
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：DarkMoon_Dragon (赞：2)

## 题意

可以转化为任意相同的两个数 $a_i =a_k$, 可以选择 $(i,j)$ 上的任意一个数字 $a_j$ 并删去 $(1\le i<j<k\le n)$，问最多能删去多少个数字

## Sol 1 Model Constructing

### 结论

1. 考虑一系列相同的数字出现的位置，哪些位置非常关键？
   1. 首尾
   2. 事实上，对于一系列相同的数字，只用考虑它第一次出现的位置和最后一次出现的位置
   3. 因为中间数能消去的部分一定能被最左最右的数字消除
2. 考虑将这些最先最后出现的数的位置看成一段区间(线段)，这些区间满足什么性质？
   1. 区间的端点一定不会重合
   2. 若有包含的区间，可以直接用大区间替换掉(证明和上面相同)
   3. 转化为了只有相交关系且端点不会重合的一系列区间
3. 考虑消掉区间中的数
   1. 首先不为区间端点的数一定能被消除掉
   2. 每个区间的左右端点至多有一个被消除掉
4. 重新考虑问题
   1. 如何尽量多地消除掉区间端点？
   2. 首先一段数字如果没有任意区间选择一定是最劣的(虽然很显然，但这是最终结论的前提)
   3. 每个区间的左右端点至多有一个被消除掉，即每个区间至少有一个端点消除不掉，设当前区间的集合为 $S$, 集合中区间个数为 $|S|$，则对于一系列连续相交的区间至少有 $|S|+1$ 的端点无法被消去
   4. 具体消去的方法：首先消去不为区间端点的数，然后剩下若干区间端点。考虑消去的后效性，对于当前区间 $x$，每次选择它的下一个区间 $x+1$ 消去它的右端点，这样最终会剩下所有区间的左端点和最右边一个区间的右端点，即有 $|S|+1$ 的端点无法被消去。
   5. 上述方法为先消除非端点的点，再消除端点，使得最后的区间连续。如果选择不连续的方案(即分段)？
   6. 前面说过了覆盖区间一定比不覆盖更优，则分段方案的前提是两个区间本来能合为一段(采用上述保留左端点的方法)，但强制分为两段
   7. 考虑每新划分一个区间段，最终的结果都会多一个右端点无法消去 (c. 中所述)，所以一定要区间段尽量小最优
5. 问题转为选择若干区间，使得最后所得的区间分段数尽量少的前提下，选择的区间数尽量少。这个可以通过 $n^2$ 的 dp 线段树优化或者排序扫描线解决。(区间覆盖模板)

### Implementation

```cpp
const int N = 2e5 + 56;
int a[N];
int lpos[N], rpos[N];
typedef pair<int, int> pii;
set<pii> st;
vector<pii> now;
/*
    set 中维护的结构，第一关键字为左端点，第二关键字为右端点
    保证 now 中记录的线段当前段的 r[i] >= l[i + 1]
    此题中 r[i] > l[i + 1]
    贪心，每次选择扫描线范围中最右边端点
*/
int getans() { //扫描线
    int cnt = now.back().second - now.front().first + 1;
    // 总长度 - 区间数 - 1
    int res = 1, nowr = 0/*扫描线位置*/, sz = now.size();
    for (int i = 0; i < sz; ++i) {
        if (i == sz - 1 || now[i + 1].first > nowr) { //注意特判最后一个区间，一定要选
            res++;
            nowr = now[i].second;
        }
    }
    return cnt - res;
}
int main() {
    int n = read();
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        if (!lpos[a[i]]) lpos[a[i]] = i;
        rpos[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
        if (lpos[i] < rpos[i]) st.emplace(lpos[i], rpos[i]);
    if (st.empty()) {
        puts("0");
        return 0;
    }
    int ans = 0;
    for (auto P : st) {
        int l = P.first, r = P.second;
        // 当前区间 l, r
        // 之前的区间段 
        if (now.empty()) now.emplace_back(l, r);
        else if (now.back().second < l) { // 新开一段
            ans += getans();
            now.clear();
            now.emplace_back(l, r);
        } else if (now.back().second < r) now.emplace_back(l, r); // 排除掉区间覆盖的情况 
    }
    ans += getans();
    cout << ans << endl;
    return 0;
}
```

## Sol 2 Dynamic Programming

数据范围大概率只能线性 dp

考虑 $dp_i$ 表示到第 $i$ 位时(区间 $[1, i]$ )的答案。

考虑第 $i$ 位的状态：

1. 第 $i$ 位与前面的第 $j$ 位 $a_i=a_j$，消掉他们中间所有的数
   1. `dp[i] = max{dp[j] + i - j + 1}`
   2. `dp[i] = max{dp[j] - j} + i - 1`
2. 第 $i$ 位与前面的第 $j$ 位 $a_i=a_j$，但不直接消掉他们中间的所有数，考虑中间点 $k,(i<k<j)$，先消除完开区间 $(k,i)$ 中的所有数，再划分为子问题 `dp[k]`
   1. `dp[i] = max{dp[k] + i - k + 1}`
   2. `dp[i] = max{dp[j] - j} + i - 1`
3. 直接舍弃掉第 $i$ 位
   1. `dp[i] = dp[i - 1]`
   2. 上式等价于 $j=i-1$ 的情况
4. 这样做到了状态更新的不重不漏

维护为区间静态最大值，Segment Tree 解决即可。









---

## 作者：Red_river (赞：1)

### 最简题意

给定一个长度为 $n$ 的数组，数组中的元素初始值都为零。可以通过以下操作来修改颜色：

- 选择三个元素 $(i,j,k)$ 满足 $1\leq i<j<k \leq n$，并且保证 $a_i=a_k$，同时 $c_i=c_k=0$，那么可以令 $c_j=1$。

问题要求找出应用给定操作任意次数后，能够使得 $\sum_{i=1}^{n}c_i$ 最大的情况。

### 题意分析
本题的本质是寻找满足条件的三元组，通过反复操作使得尽可能多的 $c_i$ 被设置为一。可以通过 `DP` 来解决。设 $f_i$ 为这个数第一次出现的位置，而 $dp_i$ 为在处理到第 $i$ 位时最多能取多少。则当 $a_i=a_j$ 时 $dp_i=dp_j+(j-i-1)$。所以 $dp_i+i+1=\max{(dp_j+j)}$，维护最大值用线段树就可以做到 $O(n\log n)$ 的了。
### CODE
[https://www.luogu.com.cn/paste/yq95w9p4](https://www.luogu.com.cn/paste/yq95w9p4)

---

## 作者：huhaoming2011 (赞：0)

## 题解：CF1630C Paint the Middle

### 题目大意

给你编号从 $1$ 到 $n$ 的 $n$ 个元素，元素 $i$ 的值为 $a_i$，颜色为 $c_i$。最初，所有 $i$ 的值为 $c_i = 0$。选择三个元素 $i$、$j$ 和 $k$（$1 \leq i < j < k \leq n$），如果 $c_i=c_j=c_k=0$ 同时 $a_i = a_k$，可以将 $c_j$ 赋值为 $1$。

问：$\sum_{i=1}^{n}c_i$ 的最大值。

### 思路

很明显，同一种数值的数，其实**需要重点关注的只有第一个**。

我们可以自然地想到 $O(n^2)$ 的动态规划（$st_i$ 表示数值 $i$ 第一次出现的位置）

$$
f_i=\max_{\min(i-1,st_{a_i}) \leq j < i}\{ f_j-j \}+i-1
$$

然后移一下项，则有

$$
f_i-i=\max_{\min(i-1,st_{a_i}) \leq j < i}\{ f_j-j \}-1
$$

发现可以用数据结构维护。

这里用线段树的区间最大值（单点修改）优化动态规划。

### 代码

```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (p<<1|1)
using namespace std;
const int MAXN=2e5+100;
int a[MAXN],n,st[MAXN],f[MAXN];     //st[i]的含义见题解 
struct SegmenTree {
    int tr[MAXN<<2];
    void build(int l,int r,int p) {
        tr[p]=INT_MIN;              //初值注意要赋小一点 
        if(l==r)
            return ;
        int mid=(l+r)>>1;
        build(l,mid,ls);
        build(mid+1,r,rs);
        tr[p]=max(tr[ls],tr[rs]);
        return ;
    }
    void change(int s,int t,int p,int x,int val) {
        if(s>x or t<x)
            return ;
        if(s==t) {
            tr[p]=max(tr[p],val);
            return ;
        }
        int mid=(s+t)>>1;
        change(s,mid,ls,x,val);
        change(mid+1,t,rs,x,val);
        tr[p]=max(tr[ls],tr[rs]);
        return ;
    }
    int query(int s,int t,int p,int l,int r) {
        if(s>r or t<l)
            return INT_MIN;
        if(s>=l and t<=r)
            return tr[p];
        int mid=(s+t)>>1,res=-1;
        res=max(query(s,mid,ls,l,r),query(mid+1,t,rs,l,r));
        return res;
    }
} T;
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        if(!st[a[i]])
            st[a[i]]=i;
    }
    //该部分（下面注释的）为原来的动态规划 
    /*
    f[1]=0;
    for(int i=2;i<=n;i++) {
        f[i]=f[i-1];
        for(int j=min(st[a[i]],i-1);j<i;j++) {
            f[i]=max(f[i],f[j]+i-j-1);
        }
    }
    */
    T.build(1,n,1);
    T.change(1,n,1,1,-1);
    for(int i=2;i<=n;i++) {
        int val=T.query(1,n,1,min(st[a[i]],i-1),i-1)-1;
        T.change(1,n,1,i,val);
        if(i==n)
            printf("%d",val+i);   //因为维护的减掉了i，所以要加回去！ 
    }
    return 0;
}
```

**感谢观看！感谢审核员！**

---

## 作者：james1BadCreeper (赞：0)

设 $f_i$ 代表考虑到 $i$ 的答案。我们考虑 $a_i$ 最先出现的位置 $l_{a_i}$，可以考虑给 $[j+1,i-1],j\ge l_{a_i}$ 染成 $1$，也就是说：

$$
f_i=\max_{l_{a_i}\le j<i}\{f_j+i-j-1\}
$$

可以把 $i-1$ 扔到外面去然后使用线段树维护，时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std; 
const int INF = 0x3f3f3f3f; 

int n, l[200005]; 
int a[200005], f[200005], T[800005]; 

void update(int o, int l, int r, int x, int k) {
    if (l == r) return T[o] = max(T[o], k), void(); 
    int mid = l + r >> 1; 
    if (x <= mid) update(o << 1, l, mid, x, k); 
    else update(o << 1 | 1, mid + 1, r, x, k); 
    T[o] = max(T[o << 1], T[o << 1 | 1]); 
}
int query(int o, int l, int r, int x, int y) {
    if (x <= l && r <= y) return T[o]; 
    int mid = l + r >> 1; 
    if (y <= mid) return query(o << 1, l, mid, x, y); 
    if (mid < x) return query(o << 1 | 1, mid + 1, r, x, y); 
    return max(query(o << 1, l, mid, x, y), query(o << 1 | 1, mid + 1, r, x, y)); 
}

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n; memset(l, 0x3f, sizeof l); memset(T, 0xbf, sizeof T); 
    for (int i = 1; i <= n; ++i) cin >> a[i], l[a[i]] = min(l[a[i]], i); 
    for (int i = 1; i <= n; ++i) {
        f[i] = f[i - 1]; 
        if (l[a[i]] <= i - 1) f[i] = max(f[i], query(1, 1, n, l[a[i]], i - 1) + i - 1); 
        update(1, 1, n, i, f[i] - i); 
    }
    cout << f[n] << "\n"; 
    return 0; 
}
```

---

## 作者：Nightingale_OI (赞：0)

## CF1631E Paint the Middle

### 大意

给定一个数组 $ a $ ，初始全为 $ 0 $ 的数组 $ c $ 。

如果 $ c_i = c_k = 0 $ 且 $ a_i = a_k $ ，可以把 $ c_j $ 设为 $ 1 \  (i < j < k) $ 。

求最后 $ c $ 数组的和的最大值。

### 思路

考虑设 $ dp_i $ 表示 $ c_i = 0 $ 情况下 $ c $ 数组前 $ i $ 项最少有几个位置为 $ 0 $ 。

首先， $ dp $ 数组一定是单调递增的。

若 $ a_i $ 第一次出现，我们就只能使 $ dp_i = dp_{i-1} + 1 $ 。

否则，考虑最小的 $ j $ 使得 $ a_i = a_j $ ，我们的答案可以是 $ \min_{k=j}^{i-1}(dp_k) + 1 $ 。

证明：设 $ \min_{k=j}^{i-1}(dp_k) = dp_x $ ，显然若 $ x = j $ 该式子成立。

若 $ dp_x $ 对应选择的值 $ dp_y + 1 $ 的 $ y $ 满足 $ j <= y $ ，则显然 $ dp_y < dp_x $ ，与我们找的值最小的 $ x $ 矛盾。

剩下的情况就是 $ dp_x $ 对应选择的值 $ dp_y + 1 $ 的 $ y $ 满足 $ y < j $ 。

我们可以先让 $ y $ 和 $ x $ 修改时留下 $ c_j $ ，再用 $ j $ 和 $ i $ 修改时会修改 $ c_x $ ，得到的最优答案即 $ dp_x + 1 $ 。

根据定义，最后的结果就是 $ n - dp_n $ 。

注：下面代码将 $ dp $ 数组取了相反数，故求区间最大而非最小。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
struct xds{
	int l,r,c;
}a[4040404];
int b[202020];
int c[202020];
inline int Max(int x,int y){return x>y?x:y;}
void bt(int id,int l,int r){
	a[id]=(xds){l,r,-l};
	if(l<r){
		int mid=(l+r)>>1;
		bt(id*2,l,mid);
		bt(id*2+1,mid+1,r);
	}
}
void add(int id,int x,int v){
	if(a[id].l==a[id].r){
		a[id].c=v;
		return;
	}
	int mid=(a[id].l+a[id].r)>>1;
	if(x<=mid)add(id*2,x,v);
	else add(id*2+1,x,v);
	a[id].c=Max(a[id*2].c,a[id*2+1].c);
}
int sum(int id,int l,int r){
	if(l<=a[id].l && a[id].r<=r)return a[id].c;
	int mid=(a[id].l+a[id].r)>>1;
	if(r<=mid)return sum(id*2,l,r);
	else if(mid<l)return sum(id*2+1,l,r);
	return Max(sum(id*2,l,mid),sum(id*2+1,mid+1,r));
}
int main(){
	cin>>n;
	f(i,1,n)scanf("%d",&b[i]);
	g(i,n,1)c[b[i]]=i;
	bt(1,1,n);
	f(i,2,n)add(1,i,sum(1,c[b[i]]-(c[b[i]]==i),i-1)-1);
	printf("%d\n",sum(1,n,n)+n);
	return 0;
}
```

---

## 作者：氧少Kevin (赞：0)

# CF1630C - Paint the Middle
>- 链接：https://codeforces.com/problemset/problem/1630/C
>- 知识点：DP、线段树优化
>- 难度：

## 题意
给定 $n$ 个元素，第 $i$ 个元素有 $a_i$ 和 $c_i$，$a_i$ 在输入中给定，所有 $c_i=0$。你可以执行若干次操作，每次操作你可以选择满足 $1\leqslant i<j<k\leqslant n$，$c_i=c_j=c_k=0$ 且 $a_i=a_k$ 的三个位置 $i,j,k$，然后将 $c_j$ 变为 $1$。你希望最大化 $\sum\limits_{i=1}^n c_i$ 的值，求这个最大值。
数据范围：
- $3\leqslant n\leqslant 2\times 10^5$。
- $1\leqslant a_i\leqslant n$。

## 思路
- 对于同一个 $a_i$，可能有多个位置填有此数，根据贪心策略，$a_i$之间的连边一定是其它元素和第一个连边。
- 现在问题转化为：已知一堆线段，线段之间可以相互覆盖，线段的左右两端点必须填 $0$，中间的元素可以填 $1$，怎么安放能让整个序列中的 $1$ 尽可能多。
- 对于某一条线段的右端点，有两种情况：
    - 1. 这个点不跟前面的点配对，$dp[i]=dp[i-1]$
    - 2. 该线段跟之前的线段没有任何覆盖关系，$dp[r]=dp[l]+(r-l-1)$
    - 3. 该线段覆盖了其他线段，并且我们设被覆盖的这些线段中，最靠右的右端点为 $k$。$dp[r]=dp[k]+(r-k-1)$。我们当然希望能选一个合适的 $k$ 使得它对 $dp[r]$ 造成的贡献最大，所以使用线段树维护 $dp[i]-i$ 即可。
- 我们能够发现，以上三种情况不重不漏。

## 代码
```cpp
#include <cstdio>
#include <iostream>
const int N	= 1e6+10;
const int INF	= 1e9;
using namespace std;

int tree[N*4];

void UPD(int cur,int l,int r,int pos,int d)
{
	if(r<pos || l>pos)return;
	if(l==r){tree[cur]=d;return;}
	int mid=(l+r)/2;
	UPD(cur*2, l, mid, pos, d);
	UPD(cur*2+1, mid+1, r, pos, d);
	tree[cur] = max(tree[cur*2], tree[cur*2+1]);
}

int QRY(int cur,int l,int r,int ql,int qr)
{
	if(r<ql || l>qr){return -INF;}
	else if(l>=ql && r<=qr){return tree[cur];}
	int mid=(l+r)/2;
	return max(QRY(cur*2, l, mid, ql, qr),  QRY(cur*2+1, mid+1, r, ql, qr));
}

int arr[N];
int prei[N],dp[N];
int n;

void Sol()
{
	for (int i=1; i<=n*4; i++)
	{
		tree[i] = -INF;
	}
	for (int i=1; i<=n; i++)
	{
		dp[i] = dp[i-1];
		if(i > prei[ arr[i] ])
		{
			dp[i] = max(dp[i], dp[ prei[arr[i]] ] + i-prei[arr[i]]-1 );
			int res = QRY(1, 1, n, prei[ arr[i] ]+1, i-1);
			dp[i] = max(dp[i], res+i-1);
		}
		UPD(1, 1, n, i, dp[i]-i);
	}
	printf("%d\n",dp[n]);
}

int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++)
	{
		scanf("%d",&arr[i]);
		if(!prei[ arr[i] ]) prei[ arr[i] ] = i;
	}
	Sol();
	
	return 0;
}

```

---

