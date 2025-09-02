# Till I Collapse

## 题目描述

Rick and Morty want to find MR. PBH and they can't do it alone. So they need of Mr. Meeseeks. They Have generated $ n $ Mr. Meeseeks, standing in a line numbered from $ 1 $ to $ n $ . Each of them has his own color. $ i $ -th Mr. Meeseeks' color is $ a_{i} $ .

Rick and Morty are gathering their army and they want to divide Mr. Meeseeks into some squads. They don't want their squads to be too colorful, so each squad should have Mr. Meeseeks of at most $ k $ different colors. Also each squad should be a continuous subarray of Mr. Meeseeks in the line. Meaning that for each $ 1<=i<=e<=j<=n $ , if Mr. Meeseeks number $ i $ and Mr. Meeseeks number $ j $ are in the same squad then Mr. Meeseeks number $ e $ should be in that same squad.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF786C/f2b873f46d1ce1d5117f05fee6c23499da101533.png)Also, each squad needs its own presidio, and building a presidio needs money, so they want the total number of squads to be minimized.

Rick and Morty haven't finalized the exact value of $ k $ , so in order to choose it, for each $ k $ between $ 1 $ and $ n $ (inclusive) need to know the minimum number of presidios needed.

## 说明/提示

For the first sample testcase, some optimal ways of dividing army into squads for each $ k $ are:

1. $ [1],[3],[4],[3,3] $
2. $ [1],[3,4,3,3] $
3. $ [1,3,4,3,3] $
4. $ [1,3,4,3,3] $
5. $ [1,3,4,3,3] $

For the second testcase, some optimal ways of dividing army into squads for each $ k $ are:

1. $ [1],[5],[7],[8],[1],[7],[6],[1] $
2. $ [1,5],[7,8],[1,7],[6,1] $
3. $ [1,5,7],[8],[1,7,6,1] $
4. $ [1,5,7,8],[1,7,6,1] $
5. $ [1,5,7,8,1,7,6,1] $
6. $ [1,5,7,8,1,7,6,1] $
7. $ [1,5,7,8,1,7,6,1] $
8. $ [1,5,7,8,1,7,6,1] $

## 样例 #1

### 输入

```
5
1 3 4 3 3
```

### 输出

```
4 2 1 1 1 
```

## 样例 #2

### 输入

```
8
1 5 7 8 1 7 6 1
```

### 输出

```
8 4 3 2 1 1 1 1 
```

# 题解

## 作者：When (赞：21)

#### 题意

将$n$个数划分成$m$段使得每中不同数字的个数$\le k$,对于每个$k$满足$1\le k\le n$求出最小的$m$。

#### 算法

根号分治+二分

#### 思路

面对那不大不小的数据范围，难以优化的查询方法以及令人疑惑的值域，我们可以联想到根号分治。

首先明确：

+ 答案的范围是不会超过$\frac{n}{k}$的。（就算全都不一样也只要这么多次划分）
+ 当$k$单调递增时，答案单调不减，即答案具有二分性质

根据第一条性质，我们发现，不同答案的个数是不超过$\sqrt{n}$级别的，而结合第二条性质，答案相同的$k$一定是连续的。

所以我们得出一下做法：

+ 对于$k \le \sqrt{n}$的情况：直接暴击$O(n)$统计；

+ 对于$k > \sqrt{n}$的情况：也是暴力统计，但统计完以后，需要二分出与当前答案相同的区间，将这段区间的答案一起输出。

#### 参考代码

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int maxn = 1e5 + 10;
int n,a[maxn],Ans,siz;
bool T[maxn];

int work(int k){
    memset(T,0,sizeof(T));
    int sum = 0, cnt = 0, sta = 1;
    for(int i = 1; i <= n; ++ i){
        if(!T[a[i]]) T[a[i]] = 1, cnt ++;
        if(cnt > k){
            sum++, cnt = 1;
            for(int j = sta; j < i; ++ j) T[a[j]] = 0;
            T[a[i]] = 1; sta = i;
        }
    }
    if(cnt) sum++;
    return sum;
}

int main(){
    scanf("%d", &n); siz = sqrt(n);
    for(int i = 1; i <= n; ++ i) scanf("%d", a + i);
    for(int k = 1; k <= n; ++ k){
        if(k <= siz) printf("%d ", work(k));
        else{
            Ans = work(k);
            int l = k, r = n, mid;
            while(l <= r){
                mid = (l + r) >> 1;
                if(work(mid) < Ans) r = mid - 1;
                else l = mid + 1;
            }
            for(int i = k; i <= l - 1; ++ i) printf("%d ", Ans);
            k = l - 1;
        }
    }
    printf("\n");
    return 0;
}
```





---

## 作者：Legitimity (赞：10)

有一个不需要主席树的时间 $O(n\log^2 n)$ 、空间 $O(n)$做法。

考虑贪心，对于划分出的每个区间使其在满足 $k$ 的限制下最长，一定不劣。即对于每个 $k$，每次固定当前区间 $[l,r]$ 的 $l$ （初始时 $l=1$） ，满足 $k$ 的限制下尽量让 $r$ 大。

问题转化为如何找到满足条件最大的 $r$，怎么实现？常见套路：预处理出每个位置 $i$ 下一个与其值相同的位置记为 $nex_i$，然后转化为二维数点问题。从前往后扫，确定左端点 $l$，用一颗线段树或者树状数组维护每个 $r$ 上的值：$[l,r]$ 中不同的数的个数，答案满足单调性，所以可以线段树上二分或树状数组上二分；左端点从 $l$ 变为 $l+1$ 的时候，原本的 $a_l$ 消失，区间 $[l+1,n]$ 所有数减一，下一个相同的值是 $a_{nex_l}$，区间 $[nex+l,n]$ 所有数加一。

这样对于每个询问 $k$ 我们暴力从前往后扫一遍数组，时间复杂度为 $O(n^2\log n)$。

但是我们发现中间有很多信息是被浪费的：询问为 $k$ 时，答案至多有 $\lceil\dfrac{n}{k}\rceil$ 个区间，一共只有 $\sum_{k=1}^n \lceil\frac{n}{k}\rceil=H_n=O(n\ln n)$ 个有用的 $r$ 端点，而我们中间计算了 $n^2$ 次 $l$ 端点，中间的计算是浪费的。

有一个选择是将上面的线段树可持久化，记录下每个左端点对应的线段树，开始 $O(n\log n)$ 预处理，每个查询确定 $r_x$ 时只查询 $r_{x-1}+1$ 对应的线段树，总时间复杂度是 $O(n\log^2 n)$，空间复杂度为 $O(n\log n)$。

但是不要学 DS 学傻了，没必要这样做。

发现不同的 $k$ 之间计算相互独立，可以放在一起算。具体的说，可以用队列 $q_i$ 存放当前 $[1,l-1]$ 已经划分完毕、等待从 $l$ 开始划分一段新区间的询问 $k$。从前往后扫，确定左端点 $l$ 及其对应的每个区间的不同值的个数（一个普通的树状数组），将队列 $q_l$ 中所有的询问更新，设更新后询问 $k$ 的已划分区间的右端点为 $r$ ，在队列 $q_{r+1}$ 加入 $k$。

时间复杂度依然是 $O(n\log^2 n)$，但空间复杂度降为 $O(n)$

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rg register
#define ll long long
#define ull unsigned ll
#define inf 0x3f3f3f3f
#define djq 1000000007
#define lowbit(x) (x&(-x))
#define eps 1e-8
inline void file(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
char buf[1<<21],*p1=buf,*p2=buf;
inline int getc(){
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	rg int ret=0,f=0;char ch=getc();
    while(!isdigit(ch)){if(ch==EOF)exit(0);if(ch=='-')f=1;ch=getc();}
    while(isdigit(ch)){ret=ret*10+ch-48;ch=getc();}
    return f?-ret:ret;
}
int n,a;
int precol[100005],nex[100005],ans[100005];
int t[100005];
vector<int> q[100005],nw;
inline void add(int x,int v){
	while(x<=n){
		t[x]+=v;
		x+=x&(-x);
	}
}
inline int find(int v){
	int mid=0,sum=0;
	for(rg int i=20;~i;--i)
		if(mid+(1<<i)<=n&&sum+t[mid+(1<<i)]<=v){
			mid+=(1<<i);
			sum+=t[mid];
		}
	return mid;
}//二分 r 端点。 
signed main(){
	//file();
	n=read();
	for(rg int i=1;i<=n;++i){
		a=read();
		if(!precol[a]) nw.push_back(i);  //单独处理一下第一次出现的值。 
		else nex[precol[a]]=i;
		precol[a]=i;
		q[1].push_back(i);
	}
	for(rg int i=0;i<n;++i){
		if(i){
			add(i,-1);  
			if(nex[i]) add(nex[i],1);
		}else for(auto v:nw) add(v,1);
		for(auto v:q[i+1]){  //将当前左端点对应的队列中的询问更新。 
			++ans[v];  
			q[find(v)+1].push_back(v);
		}
		q[i+1].clear(); 
	}
	for(rg int i=1;i<=n;++i) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：伟大的王夫子 (赞：7)

首先，这道题暴力的思路应该比较显然，直接每次贪心，跳到能够到达的最远的地方即可，暴力的时间复杂度为 $O(n^2)$。

然后我们想一下能否优化这个跳的过程。一般情况下，我们查询一段区间中不同的数的个数用的是可持久化线段树，而这个最后可以跳到的点显然是有单调性的，完全可以二分求出。二分则可以直接在线段树上二分。

于是我们倒序插入 $a$，对于每个 $i$，我们在第 $i$ 棵线段树上的位置 $i$ 将其值加一，再将这个数上一次出现的位置减去一，询问时直接在左端点对应根上的线段树查询 $l,r$ 的区间和即可。因为 $1$ 到 $l-1$ 上所有数的值为 0，所以也可以询问 $1,r$ 的区间和，那么二分便可以直接在线段树上二分了。

分析一下时间复杂度。

设 $ans_i$ 为 $k=i$ 的答案。则时间复杂度为 $O(\sum_{i=1}^n ans_i \log n)$

而括号里的东西 $\le \sum_{i=1}^n \log n \le1+(\dfrac{1}{2}+\dfrac{1}{2})+\cdots +2^m \times(\dfrac{1}{2^m})$

$m$ 的大小大概在 $O(\log n)$ 级别。

故时间复杂度为 $O(n \log^2 n)$

思维过程：先想到暴力贪心，再想到可以用可持久化线段树加速查询的过程（因为是求区间不同数的个数）并在线段树上二分。先想一个像样的暴力，再用数据结构进行优化，这是一种很好的思维方式。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, las[N], a[N];
struct Seg {
	struct {
		int l, r, cnt;
	} t[N * 40];
	int rt[N], tot;
	int insert(int now, int l, int r, int x, int d) {
		int p = ++tot;
		t[p] = t[now];
		if (l == r) {
			t[p].cnt += d;
			return p;
		}
		int mid(l + r >> 1);
		if (x <= mid) t[p].l = insert(t[p].l, l, mid, x, d);
		else t[p].r = insert(t[p].r, mid + 1, r, x, d);
		t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
		return p;
	}
	void copy(int x, int y) {
		rt[y] = rt[x];
	}
	void upd(int x, int v, int d) {
		rt[x] = insert(rt[x], 1, n, v, d);
	}
	int ask(int p, int l, int r, int v) {
		if (l == r) return l;
		int mid(l + r >> 1);
		if (v <= t[t[p].l].cnt) return ask(t[p].l, l, mid, v);
		else return ask(t[p].r, mid + 1, r, v - t[t[p].l].cnt); 
	}
	int ask(int x, int v) {
		if (t[rt[x]].cnt < v) return n + 1;
		return ask(rt[x], 1, n, v);
	}
} t;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", a + i);	
	for (int i = n; i; --i) {
		t.copy(i + 1, i);
		if (las[a[i]]) t.upd(i, las[a[i]], -1);
		t.upd(i, las[a[i]] = i, 1);
	} 
	for (int k = 1; k <= n; ++k) {
		int ans = 0;
		for (int i = 1, r; i <= n; ++i) {
			r = t.ask(i, k + 1) - 1;
			i = r;
			++ans;
		}
		printf("%d ", ans);
	}
}
```

---

## 作者：lele2002 (赞：5)

裸的

首先发现对于第i次询问，找i个不同颜色的数，最多有n/i组，所以对于n个i，如果我们能O(1)的找到每i种数的结尾，我们就可以O（nlogn）的解决这道题；

考虑用主席树来维护，表示1到i某个位置是不是这个位置表示的颜色的最后一位，这样我们就从后往前扫，对于某一个位置开始，看包含i个颜色的最左位置，就在主席树上看右儿子的有值的个数，然后不断进左儿子或右儿子，最后找到下一个可行位置。

这样的复杂度是O(nlogn^2)的，即可通过

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define mid (l+r)/2

using namespace std;
const int MN=401010;
int last[MN],p,qz[30*MN],ls[30*MN],rs[30*MN],t[MN],cnt;
void build(int &p,int l,int r)
{
	p=++cnt;
	if(l==r)
		return;
	build(ls[p],l,mid);
	build(rs[p],mid+1,r);
}
void upd(int p)
{
	qz[p]=qz[ls[p]]+qz[rs[p]];
}
void del(int &p,int recen,int l,int r,int pos)
{
	p=++cnt;
	if(l==r)
	{
		qz[p]=0;
		return;
	}
	ls[p]=ls[recen];
	rs[p]=rs[recen];
	if(pos>mid)
		del(rs[p],rs[recen],mid+1,r,pos);
	else
		del(ls[p],ls[recen],l,mid,pos);
	upd(p);
}
void add(int &p,int recen,int l,int r,int pos)
{
	p=++cnt;
	ls[p]=ls[recen];
	rs[p]=rs[recen];
	if(l==r)
	{
		qz[p]=1;
		return;
	}
	if(pos>mid)
		add(rs[p],rs[recen],mid+1,r,pos);
	else
		add(ls[p],ls[recen],l,mid,pos);
	upd(p);
}
int find(int p,int l,int r,int si)
{
	if(l==r&&si!=1)
		return -1;
	else if(l==r)
		return l;
	if(qz[rs[p]]>=si)
		return find(rs[p],mid+1,r,si);
	return find(ls[p],l,mid,si-qz[rs[p]]);
}
int main()
{
	int n;
	cin>>n;
	build(t[0],1,n);
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(last[x])
			del(t[i],t[i-1],1,n,last[x]);
		else
			t[i]=++cnt,ls[t[i]]=ls[t[i-1]],rs[t[i]]=rs[t[i-1]];
		add(t[i],t[i],1,n,i);
		last[x]=i;
	}
	for(int i=1;i<=n;i++)
	{
		int ans=0,pr=n;
		while(pr>0)
		{
			if(qz[t[pr]]<=i)
			{
				ans++;
				break;
			}
			pr=find(t[pr],1,n,i+1);
			ans++;
		}
		cout<<ans<<' ';
	}
	cout<<endl;
	return 0;
}
```


---

## 作者：yyy爱编程 (赞：4)

整除分块思想，二分，根号分治。

给定一个长度为$n$的数列$a_1,a_2,a_3,···,a_n$，将其划分为最少的段，使得每个段里不同的数只有不超过$m$个。

对于$m \in [1,n]$都要求出答案。

对于一个$m$,答案的上界为$\lceil \frac{n}{m} \rceil$。

由整除分块思想，这个不同的取值只有$O(\sqrt n)$种，所以不同的答案只有$O(\sqrt n)$种。

答案是单调不增的，相同的答案一定是连续出现。

有一个简单的做法：枚举每个答案位置的$m$,$O(n)$求出它的答案，然后二分这个答案最右边的出现位置。

这个做法$O(n \sqrt n \log n)$，无法通过。

发现当$m$比较小的时候，这个答案相同的区间是很短的，都要在后面剩余的位置进行二分，这就浪费时间了。

所以在$m$比较小的时候，我们枚举每个位置并$O(n)$求出答案，在$m$比较大的时候用上面的方法求出答案。

当阈值为$\sqrt {n \log n}$时，总时间复杂度最优，为$O(n \sqrt{n \log n})$。可过。

---

## 作者：ARIS2_0 (赞：3)

### 前言

实际上本题的根号分治可以不使用二分，以达到 $O(n\sqrt{n})$ 的复杂度。

### 思路

$O(n^2)$ 的暴力是显然的：当 $k$ 固定时，对于每一个左端点，将右端点尽可能多的向右移，然后将右端点右边的数设为左端点，以此类推。

不难发现，分组的组数不会超过 $\lceil\frac{n}{k}\rceil$，考虑根号分治。

记 $B=\lceil{\sqrt{n}}\rceil$。

我们对于 $k\le B$ 的 $k$，直接暴力计算答案，时间复杂度 $O(n\sqrt{n})$；

对于 $k>B$ 的 $k$，由于其分组组数不超过 $B$，我们**记录每一组的右端点**，更新时只需要**将这 $B$ 个右端点尽量向右移，直到无法移动**即可。

右端点最多只会移动 $O(n\sqrt{n})$ 次，遍历的复杂度也是 $O(n\sqrt{n})$ 的，总时间复杂度为 $O(n\sqrt{n})$。

### 实现细节

实现上，我们开 $B$ 个桶，第 $i$ 个桶记录第 $i$ 块的信息。当我们移动第 $i$ 块的右端点时，我们去更新第 $i$ 块和第 $i+1$ 块的桶（移动第 $i$ 块的右端点的同时也移动了第 $i+1$ 块的左端点），同时判断能否继续向右移。

当遇到一个块的右端点移到了 $n$ 时，说明答案就是这个块的编号，直接输出即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=1e5+10,maxs=330;
int n,a[maxn],B,cnt[maxn],z[maxn],cz[maxs][maxn],ans[maxs];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    B=ceil(sqrtl(n));
    int tot=0;
    //这个循环是暴力，同时用 z 记录分界点
    for(int i=1;i<=B;i++){
        int last=1,res=0;
        tot=0;
        for(int j=1;j<=n;j++){
            if(cnt[a[j]]==0 and res+1>i){
                z[++tot]=j-1;
                for(int k=last;k<j;k++)cnt[a[k]]--;
                last=j;
                res=0;
            }
            if(cnt[a[j]]==0)res++;
            cnt[a[j]]++;
        }
        z[++tot]=n;
        for(int k=last;k<=n;k++)cnt[a[k]]--;
        cout<<tot<<" ";
    }
    //预处理 ans[i]（第 i 块中数字的种类数）和 cz[i]（对第 i 块开的桶）
    for(int i=1;i<=tot;i++){
        for(int j=z[i-1]+1;j<=z[i];j++){
            if(cz[i][a[j]]==0)ans[i]++;
            cz[i][a[j]]++;
        }
    }
    for(int i=B+1;i<=n;i++){
        int eans=0;
        for(int j=1;j<=tot;j++){
            //这里是有可能出现 z[j]<z[j-1] 的情况的，但是不会影响到答案统计。
            //因为在 z[j]<z[j-1] 时，ans[j] 永远为 0，cz[j] 这个桶随着 z[j] 变大也会自动还原。
            while(z[j]<n and ans[j]+(cz[j][a[z[j]+1]]==0)<=i){
                z[j]++;
                ans[j]+=(cz[j][a[z[j]]]==0);
                cz[j][a[z[j]]]++;
                cz[j+1][a[z[j]]]--;
                ans[j+1]-=(cz[j+1][a[z[j]]]==0);
                //这里要计算对下一块的影响
            }
            if(z[j]==n){eans=j;break;}
        }
        cout<<eans<<" ";
    }
	return 0;
}
```

---

## 作者：ChthollyTree (赞：2)

然而并不需要主席树

对于$k <= \sqrt{n}$的情况，暴力即可

对于$k > \sqrt{n}$ ，答案 $<= \frac{n}{k} < \sqrt{n}$

此时，最多只有sqrt(n)种答案，且答案随着k的增大而减小

所以我们可以二分

时间复杂度 $n\sqrt{n}log(n)$ 可以通过

当然可以微调边界 使得时间复杂度变为 $n\sqrt{nlogn}$

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 100005
int n,m; 
int a[MAXN];
int c[MAXN];
int ans[MAXN];


int solve(int x) {
	int rt = 0,ans = 0;
	int ls = 0;
	memset(c,0,sizeof(c));
	for(int i = 1; i <= n; i ++) {
		c[a[i]] ++; 
		if(c[a[i]] == 1) {
			rt ++;
		}
		if(rt > x) {
			i --;
			for(int j = ls; j <= i+1; j ++)
				c[a[j]] --;
			rt = 0;
			ls = i+1;
			ans ++;
		}
	}
	ans ++;
	return ans;
}

void orz(int l,int r)
{
	int sl = solve(l),sr = solve(r);
	if(sl == sr) {
		for(int j = l; j <= r; j ++)
			ans[j] = sl;
	 } else {
	 	int mid = (l+r)>>1;
	 	orz(l,mid);
	 	orz(mid+1,r);
	 }
} 

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i ++)
		cin >> a[i];
	int o = 0;
	for(int i = 1; i*i <= n*log2(n); i ++)
	{	 o = i;
		ans[i] = solve(i);
	}
	orz(o+1,n);
	for(int i = 1; i <= n; i ++)
		cout<<ans[i]<<"\n"; 
	return 0;
}
```

---

## 作者：Hanx16Kira (赞：1)

# Till I Collapse

[Luogu CF786C](https://www.luogu.com.cn/problem/CF786C)

[Codeforces 786C](https://codeforces.com/problemset/problem/786/C)

## Solution

显然一个贪心的想法是每个选择的区间包含的颜色数量都尽可能多，这样总的段数就会很小。那么当每段区间内的颜色数量为 $k$ 的时候，显然总的段数会是 $\le \lfloor\dfrac{n}{k}\rfloor$ 的。这也就意味着枚举每一个颜色段的时间复杂度将会是调和级数的 $\mathcal O(n\log n)$。

现在问题转化成为了已知左端点 $l$，要求找到一个最大的 $r$，使得 $[l,r]$ 间的颜色数量为 $k$。如果你不会数区间颜色个数，建议先去试一试 [P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)。那这道题也可以尝试用主席树来做。

延续那道题的做法，记录一个 $pre_i$ 表示数字 $i$ 上一次出现的位置。特殊的，如果数字 $i$ 没有出现，则定义 $pre_i=0$。但是如果继续按照之前的做法，会发现 $r$ 并不能在主席树上二分解决，如果直接二分找到对应位置的话时间复杂度是 $\mathcal O(\log^2n)$ 的。所以考虑改变一下主席树的形态。

原来的主席树是建一棵值域线段树，然后按照位置进行可持久化。而这道题为了能够在线段树上二分到 $r$ 的位置，所以需要建的是普通的维护区间信息的线段树，然后根据值域来进行可持久化。根据那道题的思路，需要查询 $pre$ 小于 $l$ 的数量，那么此题就应该按照 $pre$ 进行可持久化。

那么思路就显而易见了。先建出主席树，查询 $l$ 对应的 $r$ 的话就在前 $l-1$ 棵线段树上查找到最后一个前缀和为 $k$ 的位置就行了。

代码实现上有一点细节需要注意。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace Hanx16qwq {
constexpr int _SIZE = 2e5;
int n;
int a[_SIZE + 5], pre[_SIZE + 5], last[_SIZE + 5];
int T[_SIZE + 5];
int ls[(_SIZE << 5) + 5], rs[(_SIZE << 5) + 5];
int sum[(_SIZE << 5) + 5], totNode, tail = 0;

#define mid ((l + r) >> 1)

int Build(int l, int r) { // 建一个全空的线段树
    int cur = ++totNode;

    if (l < r)
        ls[cur] = Build(l, mid), 
        rs[cur] = Build(mid + 1, r);
    
    return cur;
}

int Update(int pre, int l, int r, int v) { // 新建节点
    int cur = ++totNode;
    ls[cur] = ls[pre], rs[cur] = rs[pre], sum[cur] = sum[pre] + 1;

    if (l < r) {
        if (v <= mid) ls[cur] = Update(ls[pre], l, mid, v);
        else rs[cur] = Update(rs[pre], mid + 1, r, v);
    }
    
    return cur;
}

pair<int, int> Find(int u, int v, int l, int r, int a, int b, int k) { // 在主席树上二分，first 返回位置，second 返回 [a,b] 间的节点数量
    if (l > b || r < a || k <= 0) return make_pair(0, 0); // 非法节点

    if (l == r) { // 叶子节点
        return make_pair(l, sum[v] - sum[u]);
    }

    if (l >= a && r <= b) { // 刚好在区间内
        int res = sum[ls[v]] - sum[ls[u]];

        if (k <= res) return make_pair(Find(ls[u], ls[v], l, mid, a, b, k).first, sum[v] - sum[u]); // second 返回的应该是这整个区间的和
        else return make_pair(Find(rs[u], rs[v], mid + 1, r, a, b, k - res).first, sum[v] - sum[u]);
    }

    auto lres = Find(ls[u], ls[v], l, mid, a, b, k);
    auto rres = Find(rs[u], rs[v], mid + 1, r, a, b, k - lres.second); // 递归到左右子树，右侧查找的 k 应该减去左侧询问区间内的数量

    return make_pair(max(lres.first, rres.first), lres.second + rres.second);
}

int range[_SIZE + 5];

void main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    vector<pair<int, int>> all;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = last[a[i]];
        last[a[i]] = i;
        all.emplace_back(pre[i], i);
    }

    T[0] = Build(1, n + 1);
    sort(all.begin(), all.end()); // 按照 pre 分组并排序

    for (auto it : all) {
        ++tail;
        T[tail] = Update(T[tail - 1], 1, n + 1, it.second);
        range[it.first] = max(range[it.first], tail); // 记录一下每个 pre 对应的最后一棵线段树
    }

    for (int i = 1; i <= n; i++)
        range[i] = max(range[i], range[i - 1]); // 处理一下没有出现的 pre 的位置

    for (int k = 1; k <= n; k++) {
        int ans = 0;

        for (int l = 1; l <= n;) {
            int r = Find(T[0], T[range[l - 1]], 1, n + 1, l, n + 1, k + 1).first - 1; // 相当于是找到 k + 1 的前驱
            ans++, l = r + 1; // 继续找下一个区间
        }
        
        cout << ans << ' ';
    }
}
}

signed main() {
    Hanx16qwq::main();
    return 0;
}
```

---

## 作者：intel_core (赞：1)

首先有一个很明显 $O(n)$ 对一个 $k$ 求答案的方法：

> 贪心的，我们依次将这些数加入当前组，如果加入后不同数的个数 $>k$，那就新开一组并把这个数加进去。

如果这样一个一个求，那么复杂度是 $O(n^2)$ 的。

很明显，答案不超过 $\left\lceil \frac{n}{k} \right\rceil$ ，所以我们根号分治。

* 对于 $k \in [1,\sqrt{n \log n})$，一个一个求。

* 对于 $k \in [\sqrt{n \log n},n]$，答案不超过 $\sqrt{\frac{n}{\log n}}$ ，枚举答案，二分取到这个答案的范围。

（因为答案明显满足单调性，所以可以二分。

总复杂度 $O(n \sqrt{n \log n})$。

---

## 作者：o51gHaboTei1 (赞：0)

**CF786C sol**。

记 $lst_i$ 表示与 $a_i$ 颜色相同的上一个位置，显然区间数颜色可以查询区间内 $lst_i < l$ 的点数。

自己一眼一个很蠢的做法：根号分治 $k$，对于 $k \leq \sqrt n$ 暴力 $O(n)$ 能分就分统计，对于 $k > \sqrt n$ 由于答案 $< \sqrt n$，变化一下维度用主席树上二分即可暴力 $O(\log n)$ 跳。

一个常数稍微小点的做法是观察到答案的单调性，由于答案颜色段数量级为 $O(\sqrt n)$，即对于 $k \leq \sqrt n$ 的提供等数量级的颜色段；对于 $k > \sqrt n$ 的 $k$ 的答案 $\leq \sqrt n$，提供的颜色段数量级也为 $O(\sqrt n)$，所以每次暴力二分 $O(n)$ 检查的时间复杂度是 $O(n \sqrt n \log n)$。

对于做法 $1$ 我们可以发现这个分析是不严格的上界，事实上用 $O(\log n)$ 暴力跳的时间复杂度为 $O(\log n(\sum_{i = 1} ^ n \frac{n}{i}))$，内部是调和级数所以总的时间复杂度为 $O(n \omega \log n)$。

给出的是做法二的实现。

```cpp
/*
直接根号分治。
时间复杂度是高明的。
怎么是根号 log ^ 2 的。。。
我不会单根。
好像可以通过反转维度来二分。
就是 n sqrt log n 了。
单根可以怎么做啊？？？
然后题解区有个常数更小的 n \sqrt n log n
sb，这是调和级数，直接暴力就是 n log ^ 2 n 的。。。 
*/
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,m,lst[Len],a[Len];
inline int Q(int k)
{
	memset(lst , 0 , sizeof lst);
	int l = 1 , ct = 0 , as = 0;
	for(int i = 1 ; i <= n ; i ++) 
	{
		if(lst[a[i]] < l) ct ++;
		if(ct > k)
		{
			l = i;
			as ++;
			ct = 1;	
		}
		lst[a[i]] = i;
	}
	if(ct) as ++;
	return as;
}
inline int read() {
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void write(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
int main()
{
	n = read();
	for(int i = 1 ; i <= n ; i ++) a[i] = read();
	int t = sqrt(n);
	for(int i = 1 ; i <= n ; i ++)
	{
		int l = i , r = n , anss = 0 , ms = Q(i);
		while(l <= r)
		{
			int mid = (l + r) >> 1;
			if(ms == Q(mid)) l = mid + 1 , anss = mid;
			else r = mid - 1; 
		}
		for(int j = i ; j <= anss ; j ++) printf("%d ",ms);
		i = anss;
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2400}$
---
### 解题思路：

考虑根号分治。

首先考虑一种朴素的做法，尽可能地往后取数，直到取到出现了超过 $k$ 种数开启下一段。这样做的正确性由如果能往后取则答案一定不劣保证。这样做法的复杂度为 $O(n^2)$，不能接受。这种做法还很好地保证了答案单调。

然后容易发现结论：答案的大小不超过 $\lceil\dfrac{n}{k}
\rceil$，所以对于 $k$ 较大的情况，可能出现的答案也较少。

假设当前以 $B$ 为分界点，分界点之前的 $k$ 采用朴素做法，分界点之后的采用二分，每一次二分出下一个变动的位置。考虑理论能出现的最高复杂度，前一半为 $O(nB)$，后一半由于最多只有 $\lceil\dfrac{n}{B}\rceil$ 种取值，则最高复杂度为 $O(\lceil\dfrac{n}{B}\rceil n\log n)$。最终复杂度为 $O(nB+\lceil\dfrac{n}{B}\rceil n\log n)$。

很快发现取 $B=\sqrt{n\log n}$ 是一个很不错的选择，这样的最终复杂度为 $O(n\sqrt{n\log n})$，可以接受。

---
### 代码：

```cpp
#include<cstdio>
#include<cmath>
using namespace std;
int n,a[100005],c[100005],cnt,ans,lq,B,ANS[100005],l,r,mid,res;
int work(int x){
	for(int i=1;i<=n;i++)c[i]=0;
	cnt=0;ans=0;lq=1;
	for(int i=1;i<=n;i++){
		c[a[i]]++;
		if(c[a[i]]==1)cnt++;
		if(cnt==x+1){
			ans++;
			for(int j=lq;j<=i-1;j++)
			c[a[j]]--;
			lq=i;
			cnt=1;
		}
	}
	ans++;
	return ans;
}
int binary(int x){
	int now=work(x);
	l=x;r=n;res=x;
	while(l<=r){
		mid=(l+r)/2;
		if(work(mid)==now)l=mid+1,res=mid;
		else r=mid-1;
	}
	for(int i=x;i<=res;i++)
	ANS[i]=now;
	return res;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	B=sqrt(n*log2(n));
	for(int i=1;i<=B;i++)ANS[i]=work(i);
	for(int i=B+1;i<=n;i++)i=binary(i);
	for(int i=1;i<=n;i++)
	printf("%d ",ANS[i]);
	printf("\n");
	return 0;
}
```


---

## 作者：daniEl_lElE (赞：0)

根号分治。

## 思路

首先我们很容易求给定的一个 $k$ 求最小的 $m$。

考虑根号分治，取定值 $t$，对于 $k<t$ 暴力计算，然而对 $k>t$，显然至少分成的段数小于等于 $\dfrac{n}{t}$，然后我们对于每个答案 $1\sim\dfrac{n}{t}$ 二分他的边界即可，对于暴力计算的部分复杂度是 $O(tn)$，对于剩余部分则是 $O(\dfrac{n^2}{t}\log n)$。此时并不是 $t=\sqrt n$ 最好，如果你想知道最好取多少可以自己算函数极值，我取的 $t=1000$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[100005];
int qry(int x){
	int num[100005],cnt=0,lst=1,tot=0;
	memset(num,0,sizeof(num));
	for(int i=1;i<=n;i++){
		if(!num[a[i]]) cnt++,num[a[i]]=1;
		if(cnt>x){
			tot++;
			for(int j=lst;j<=i;j++) num[a[j]]=0;
			lst=i;
			num[a[i]]=1,cnt=1;
		}
	}
	if(cnt) tot++;
	return tot;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		if(i<=1000) cout<<qry(i)<<" ";
		else{
			int tmp=qry(i);
			int l=i,r=n;
			while(l<r){
				int mid=(l+r+1)>>1;
				if(qry(mid)<tmp){
					r=mid-1;
				}
				else{
					l=mid;
				}
			}
			for(int j=i;j<=l;j++) cout<<tmp<<" ";
			i=l;
		}
	}
	return 0;
}
```

---

