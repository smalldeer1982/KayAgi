# Ladder

## 题目描述

You've got an array, consisting of $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Also, you've got $ m $ queries, the $ i $ -th query is described by two integers $ l_{i},r_{i} $ . Numbers $ l_{i},r_{i} $ define a subsegment of the original array, that is, the sequence of numbers $ a_{li},a_{li}+1,a_{li}+2,...,a_{ri} $ . For each query you should check whether the corresponding segment is a ladder.

A ladder is a sequence of integers $ b_{1},b_{2},...,b_{k} $ , such that it first doesn't decrease, then doesn't increase. In other words, there is such integer $ x $ $ (1<=x<=k) $ , that the following inequation fulfills: $ b_{1}<=b_{2}<=...<=b_{x}>=b_{x+1}>=b_{x+2}...>=b_{k} $ . Note that the non-decreasing and the non-increasing sequences are also considered ladders.

## 样例 #1

### 输入

```
8 6
1 2 1 3 3 5 2 1
1 3
2 3
2 4
8 8
1 4
5 8
```

### 输出

```
Yes
Yes
No
Yes
No
Yes
```

# 题解

## 作者：wxzzzz (赞：6)

### 题意

给定一个长度为 $n$ 的序列，$q$ 次询问，每次询问给定 $l,r$，问区间 $[l,r]$ 是不是单峰的。

### 思路

记 $bl_i$ 为 $i$ 左边连续的大于等于 $a_i$ 的数的个数，记 $br_i$ 为 $i$ 右边连续的大于等于 $a_i$ 的数的个数。

对于每次询问，如果 $br_l+bl_r\ge r-l+1$，那么这个区间就是单峰的。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q, l, r, a[1000005], bl[1000005], br[1000005];
int main() {
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
        cin >> a[i], bl[i] = 1, br[i] = 1;

    for (int i = 1; i <= n; i++)
        if (a[i] <= a[i - 1])
            bl[i] = bl[i - 1] + 1;

    for (int i = n; i >= 1; i--)
        if (a[i] <= a[i + 1])
            br[i] = br[i + 1] + 1;

    while (q--) {
        cin >> l >> r;

        if (br[l] + bl[r] >= r - l + 1)
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}
```

---

## 作者：梧桐灯 (赞：2)

此题是要求区间是否是“山峰”状的。（虽然英文题面是梯子）。

首先，对于一个区间，最大值肯定是该区间的“山峰”，因为如果它不是山峰的话则它比山峰大，而这是不合法的。

查询区间最大值的位置可以用线段树或ST表来实现。

然后考虑如何快速的判断一个区间是否单调不降（升）。

记$mu[i]$，$md[i]$表示以i为起点的最长的单调不降（升）的区间的终点。显然这个可以用双指针$O(n)$的预处理。

然后就做完了QwQ

代码：
```
#include <cstdio>
#define Max(p,q) a[p] > a[q] ? p : q;
using namespace std;

template <typename T>
inline void read (T& s) {
	s = 0;
	static char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c ^ 48), c = getchar ();
	return ;
}

const int N = 100003;
int n, Q, a[N], mu [N], md[N];
int mx[17][N], lg[N];

int main () {
	read (n), read (Q);
	int i, j; for (i = 1; i <= n; ++i) read (a[i]), mx[0][i] = i;
	j = 1;
	for (i = 1; i <= n; ++i) {
		if (j < i) j = i;
		while (j < n && a[j] <= a[j + 1]) ++j;
		mu[i] = j;
	} //双指针预处理单调不降
	j = 1;
	for (i = 1; i <= n; ++i) {
		if (j < i) j = i;
		while (j < n && a[j] >= a[j + 1]) ++j;
		md[i] = j;
	}
	for (j = 1; j < 17; ++j) {
		const int p = (1 << j) - 1;
		for (i = 1; i + p <= n; ++i) mx[j][i] = Max (mx[j - 1][i], mx[j - 1][i + (1 << j - 1)]);
	} //st表预处理
	for (i = 1, j = 0; i <= n; ++i) {
		if (1 << j + 1 == i) ++j;
		lg[i] = j;
	} //预处理对数
	int x, y; while (Q--) {
		read (x), read (y);
		const int k = lg[y - x + 1], p = Max (mx[k][x], mx[k][y - (1 << k) + 1]);
		puts (mu[x] >= p && md[p] >= y ? "Yes" : "No");
	} //O1输出答案
	return 0;
}
```

---

## 作者：iPhoneSX (赞：1)

本人蒟蒻，考场上刚做出来这道题，简单发表一下自己的做法。

# 题解

考虑把序列看成平面直角坐标系上的一条折线，样例如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0pl4wqif.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们把每条线段的斜率存下来，正的标成 $2$，负的标成 $1$，平的标成 $0$ 那么就可以得到一个 $n-1$ 个元素的数组：$2120211$。

考虑题目中所说的“梯子”有两种情况：
- 所有的 $1$ 都在所有的 $2$ 后面。
- 全是 $1,0$ 或全是 $2,0$。

也就是说只需要排除掉有 $1$ 在 $2$ 前面的情况。定义两个数组：
- $one_i$ 表示 $i$ 到 $n-1$ 中的第一个 $1$。
- $two_i$ 表示 $1$ 到 $i$ 中的最后一个 $2$。

对于区间 $[l,r]$，如果 $one_l<two_{r-1}$ 就说明要输出 $\mathtt{No}$，其它输出 $\mathtt{Yes}$。

# 代码

```cpp
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<iomanip>
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>
#include<stack>
#include<string>
#include<vector>
#define ll long long
#define DBG(x) cout << #x << "=" << x << endl
#define inf 0x3f3f3f3f
#define mod 1000000007
#define N 100005
using namespace std;
template <typename T>
void read(T& x) {
    x = 0;
    ll t = 1;
    char ch;
    ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            t = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
    x *= t;
}
template <typename T, typename... Args>
void read(T& first, Args&... args) {
    read(first);
    read(args...);
}
template <typename T>
void write(T y) {
    T x = y;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
template <typename T, typename... Ts>
void write(T arg, Ts... args) {
    write(arg);
    if (sizeof...(args) != 0) {
        putchar(' ');
        write(args...);
    }
}
int n,m,a[N],l,r,k[N],one[N],two[N]; 
int main(){
	read(n,m);
	for(int i=1;i<=n;i++){
		read(a[i]);
	}
	for(int i=1;i<=n-1;i++){
		if(a[i+1]>a[i]){
			k[i]=2;
		}
		if(a[i+1]<a[i]){
			k[i]=1;
		}
	}
	for(int i=1;i<=n-1;i++){
		if(k[i]==2){
			two[i]=i;
		}
		else{
			two[i]=two[i-1];
		}
	}
	one[n]=inf;//注意先把one数组赋成inf，即先假设所有的1都在很后面。
	for(int i=n-1;i>=1;i--){
		if(k[i]==1){
			one[i]=i;
		}
		else{
			one[i]=one[i+1];
		}
	}
	while(m--){
		read(l,r);
		if(l==r||r==l+1){//特判只有一个点或只有一条线段的情况。
			cout<<"Yes"<<endl;
		}
		else{
			if(one[l]<two[r-1]){
				cout<<"No"<<endl;
			}
			else{
				cout<<"Yes"<<endl;
			}
		}
	}
    return 0;
}
``````

---

## 作者：fish_love_cat (赞：1)

**简要题意：**

先给一个长度为 $n$ 的序列，然后 $q$ 次询问，每次询问给 $L,R$，问 $[L,R]$ 是不是单峰的。

**思路：**

开两个数组 $l,r$，一个 $l$ 记录 $a_i$ 右边连续大于等于 $a_i$ 的值的数量，另一个 $r$ 记录 $a_i$ 左边同样的。注意左右边包括自己。

然后判断 $l_L+r_R \ge r-l+1$ 是否成立即可。

如果成立，那么必然会有一个点左边有长度为 $l_L$ 连续递增的序列并且右边有长度为 $r_R$ 连续递减的序列，所以存在。

否则不存在。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],l[100005],r[100005];
int main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i],l[i]=1,r[i]=1;
        if(a[i]<=a[i-1])r[i]=r[i-1]+1;
    }
    for(int i=n;i>=1;i--)
    if(a[i]<=a[i+1])l[i]=l[i+1]+1;
    while(q--){int L,R;cin>>L>>R;
        puts((l[L]+r[R]>=R-L+1?"Yes":"No"));
    }
    return 0;
}
```

---

## 作者：lhc0707 (赞：0)

记录差分数组。对于一个区间，先找到最大点，如果最大点左侧差分数组都大于等于 0 且右侧差分数组都小于等于 0，则该序列满足要求。可以开线段树维护最大最小值。

代码：

```cpp
#include<iostream>
#include<cstdio>
#define ls(p) (p<<1)
#define rs(p) (p<<1|1) 
using namespace std;
typedef pair<int,int> pii;
const int INF=1e9,N=1e5+10;
int n,m,a[N][2];
pii t[N<<2],dmx[N<<2],dmn[N<<2];
//a:mx; b:mx,mn;
void build(int p,int pl,int pr)
{
	if(pl==pr)
	{
		t[p]=make_pair(a[pl][0],pl);
		dmx[p]=make_pair(a[pl][1],pl);
		dmn[p]=make_pair(a[pl][1],pl);
		return;
	}
	int mid=(pl+pr)>>1;
	build(ls(p),pl,mid);
	build(rs(p),mid+1,pr);
	t[p]=max(t[ls(p)],t[rs(p)]);
	dmx[p]=max(dmx[ls(p)],dmx[rs(p)]);
	dmn[p]=min(dmn[ls(p)],dmn[rs(p)]);
}
pii qmax(int p,int pl,int pr,int L,int R)
{
	if(L<=pl&&pr<=R)return t[p];
	int mid=(pl+pr)>>1;pii res=make_pair(-INF,0);
	if(L<=mid)res=max(res,qmax(p*2,pl,mid,L,R));
	if(R>mid)res=max(res,qmax(p*2+1,mid+1,pr,L,R));
	return res;
}
int dmax(int p,int pl,int pr,int L,int R)
{
	if(L<=pl&&pr<=R)return dmx[p].first;
	int mid=(pl+pr)>>1,res=-INF;
	if(L<=mid)res=max(res,dmax(p*2,pl,mid,L,R));
	if(R>mid)res=max(res,dmax(p*2+1,mid+1,pr,L,R));
	return res;
}
int dmin(int p,int pl,int pr,int L,int R)
{
	if(L<=pl&&pr<=R)return dmn[p].first;
	int mid=(pl+pr)>>1,res=INF;
	if(L<=mid)res=min(res,dmin(p*2,pl,mid,L,R));
	if(R>mid)res=min(res,dmin(p*2+1,mid+1,pr,L,R));
	return res;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i][0];
	for(int i=1;i<=n;i++)a[i][1]=a[i][0]-a[i-1][0];
	build(1,1,n);
	while(m--)
	{
		int l,r;cin>>l>>r;
		if(l==r){cout<<"Yes\n";continue;}
		int x=qmax(1,1,n,l,r).second;
		if(l==x)
		{
			int mxr=dmax(1,1,n,x+1,r);
			if(mxr<=0)cout<<"Yes\n";
			else cout<<"No\n";
			continue;
		}
		if(r==x)
		{
			int mnl=dmin(1,1,n,l+1,x);
			if(mnl>=0)cout<<"Yes\n";
			else cout<<"No\n";
			continue;
		}
		int mnl=dmin(1,1,n,l+1,x);
		int mxr=dmax(1,1,n,x+1,r);
		if(mnl<0||mxr>0){cout<<"No\n";continue;}
		cout<<"Yes\n";
	}
	return 0;
}
/*
8 6
1 2 1 3 3 5 2 1
1 3
2 3
2 4
8 8
1 4
5 8
*/
```

---

## 作者：Linge_Zzzz (赞：0)

# 闲话

我是大力 DS 选手。

# 题解

对于每个询问 $[l,r]$，不难想到：如果这个区间是梯子区间，那么峰一定是最大的数。进一步，如果有多个等于最大值的位置，如果这些最大值的位置不是连续的，那么肯定不是梯子区间，否则我们任选一个当做峰即可。本题中选择最靠左的最大值。

知道了最大值，我们只需要知道最大值的左右两侧是不是不降和不减的，而这个可以用线段树轻松维护。

具体地，在线段树节点记录这个区间的左右端点的值、是否不增 / 不减、最大值、最大值的位置，则 `pushup` 是显然的。

```cpp
struct node{
	bool up,dn;
	int mx,id;
	int l,r;
	node(){mx=l=r=0,up=dn=0;}
}t[N*4];
node operator+(node x,node y){
	node re;
	if(x.mx>=y.mx)re.mx=x.mx,re.id=x.id;
	else re.mx=y.mx,re.id=y.id;
	re.l=x.l,re.r=y.r;
	if(x.up&&y.up&&x.r<=y.l)re.up=1;
	if(x.dn&&y.dn&&x.r>=y.l)re.dn=1;
	return re;
}
void pushup(int p){
	t[p]=t[p*2]+t[p*2+1];
}
```

至此，已成艺术！

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
int n,m,a[N];
struct node{
	bool up,dn;
	int mx,id;
	int l,r;
	node(){mx=l=r=0,up=dn=0;}
}t[N*4];
node operator+(node x,node y){
	node re;
	if(x.mx>=y.mx)re.mx=x.mx,re.id=x.id;
	else re.mx=y.mx,re.id=y.id;
	re.l=x.l,re.r=y.r;
	if(x.up&&y.up&&x.r<=y.l)re.up=1;
	if(x.dn&&y.dn&&x.r>=y.l)re.dn=1;
	return re;
}
void pushup(int p){
	t[p]=t[p*2]+t[p*2+1];
}
void build(int p,int l,int r){
	if(l==r){
		t[p].mx=t[p].l=t[p].r=a[l];
		t[p].id=l;
		t[p].up=t[p].dn=1;
		return;
	}
	int m=(l+r)>>1;
	build(p*2,l,m);
	build(p*2+1,m+1,r);
	pushup(p);
}
node query(int p,int l,int r,int L,int R){
	if(L<=l&&r<=R)return t[p];
	int m=(l+r)>>1;
	if(R<=m)return query(p*2,l,m,L,R);
	if(L>m)return query(p*2+1,m+1,r,L,R);
	return query(p*2,l,m,L,R)+query(p*2+1,m+1,r,L,R);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	build(1,1,n);
	while(m--){
		int l,r;
		cin>>l>>r;
		int mxid=query(1,1,n,l,r).id;
		node ll=query(1,1,n,l,mxid);
		node rr=query(1,1,n,mxid,r);
		if(ll.up&&rr.dn){
			cout<<"Yes\n";
		}else{
			cout<<"No\n";
		}
	}
	return 0;
}
```

---

## 作者：arrow_king (赞：0)

大家好，我非常喜欢暴力做法，因此我用莫队过了这道题。

题意已经很清楚了。

# 思路

为了方便设 $a_0=a_{n+1}=\infty$。我们定义序列一个区间 $[l,r]$ 为“峡谷”当且仅当：

- $a_l=a_{l+1}=\dots=a_r$；
- $a_{l-1}>a_l,a_{r}<a_{r+1}$。

我们发现一段区间是满足题意的，当且仅当这个区间没有跨过任何一段“峡谷”。所谓跨过“峡谷” $[l,r]$ 是指这个区间包含 $l-1,r+1$。

对于每个“峡谷” $[l_i,r_i]$，我们给 $l_i-1,r_i+1$ 分别打上一个独一无二的标记 $i$。这样一个区间是满足题意的当且仅当这个区间里的标记不存在包含两个的。

可以发现标记总数为 $O(n)$，而一个点的标记数是 $O(1)$ 的（最多 $2$ 个）。这里的操作又不强制在线，因此我们可以使用莫队算法来维护每个标记出现的次数，以及次数为 $2$ 的标记数量。这样我们就在 $O(n\sqrt n)$ 的时间复杂度内过了这道题。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
#define ll long long
#define il inline
#define N 100005
#define bl(x) ((x+sqr-1)/sqr)
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int n,m,a[N],b[N],cnt,sqr,ans[N];
bool vis[N];
vector<int> tags[N];
struct query {
	int l,r,id;
	query() {l=r=id=0;}
	query(int _l,int _r,int _id) {l=_l,r=_r,id=_id;}
};
query que[N];
il bool cmp(query a,query b) {
	if(bl(a.l)!=bl(b.l)) return bl(a.l)<bl(b.l);
	if(bl(a.l)%2==0) return a.r>b.r;
	else return a.r<b.r;
}
il void del(int p) {
	for(auto t:tags[p]) {
		if(b[t]==2) cnt--;
		b[t]--;
	}
}
il void add(int p) {
	for(auto t:tags[p]) {
		b[t]++;
		if(b[t]==2) cnt++;
	}
}
int main() {
	n=read(),m=read();sqr=sqrt(n);
	for(int i=1;i<=n;i++) a[i]=read();
	a[0]=a[n+1]=1e9;
	for(int i=1;i<=n;i++) {		//处理“峡谷”
		if(!vis[i]) {
			int p=i,q=i;
			while(p-1>=0&&a[p-1]==a[p]&&!vis[p-1]) p--,vis[p]=1;
			while(q+1<=n+1&&a[q+1]==a[q]&&!vis[q+1]) q++,vis[q]=1;
			vis[i]=1;
			if(a[p-1]>a[i]&&a[q+1]>a[i]) tags[p-1].push_back(i),tags[q+1].push_back(i);
		}
	}
	for(int i=1;i<=m;i++) {
		int l=read(),r=read();
		que[i]=query(l,r,i);
	}
	sort(que+1,que+m+1,cmp);		//开始莫队
	int l=1,r=0;
	for(int i=1;i<=m;i++) {
		while(l<que[i].l) del(l++);
		while(l>que[i].l) add(--l);
		while(r>que[i].r) del(r--);
		while(r<que[i].r) add(++r);
		ans[que[i].id]=(cnt>=1);
	}
	for(int i=1;i<=m;i++) {
		if(ans[i]) printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}

```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF279C)  
## 题意简述
> 给定一个长度为 $n$ 的数列 $a$，有 $q$ 次询问，询问区间 $[l,r]$ 间是否存在一个整数 $x$，使得 $a_l  < a_{l+1} < \dots a_x > a_{x+1} > \dots > a_r$。是输出 `Yes`，不是输出 `No`。  

## 开始解题！
首先，我们考虑暴力，那么时间复杂度就是 $O(nq)$，无法通过本题。  
仔细阅读题目可以发现，询问取件种可能存在大量的重叠，所以我们直接对一些信息预处理即可。  
关键在于，预处理什么信息呢？对于这个问题，我们可以想到去预处理题目中类似山峰的数列，但是一般预处理会超时，此时我们换一种思路，去预处理包含 $i$ 在内的左边大于等于 $a_i$ 的数的数量，将每一项结果记为 $L_i$ 然后包含 $i$ 在内的右边大于等于 $a_i$ 的数的数量，并将每一项记为 $R_i$。那么此时，如果 $L_r + R_l \ge r-l+1$，即说明存在，也就是有一个整数 $x$，使得它旁边有长度为 $L_r$ 的左山峰和长度为 $R_l$ 的右山峰，读者可以在代码的基础上输出 $L_i$ 和 $R_i$ 进一步理解，综合上述结论，可得代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[100005],L[100005],R[100005];
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        L[i]=1,R[i]=1;
    }
    for(int i=1;i<=n;i++){
        if(a[i]<=a[i-1]) L[i]=L[i-1]+1;
    }
    for(int i=n;i>=1;i--){
        if(a[i]<=a[i+1]) R[i]=R[i+1]+1;
    }
    for(int i=1;i<=q;i++){
        int l,r;
        cin>>l>>r;
        if(L[r]+R[l]>=r-l+1) puts("Yes");
        else puts("No");
    }
}
```

---

## 作者：迟暮天复明 (赞：0)

[题面](https://codeforces.com/contest/279/problem/C)

Description:

给出一个长度为 $n$ 的数列和 $q$ 次询问，每次询问 $L,R$ 区间是否满足单峰。

$1\le n,q \le 10^5$

-----

显然，“单峰”这个要求可以转化为：有两个指针 $curl$ 和 $curr$，$curr$ 从 $R$ 不断向左移动且保证上升，$curl$ 从 $L$ 不断向右移动且保证上升，最后两个指针可以重合。

但是我们不可能去做两个指针，这样的时间复杂度是 $O(n^2)$ 的。所以我们必须要预处理从每个点开始向左和向右最多能移动到何处。这个很简单，只需要正着扫一遍，倒着扫一遍即可。

$$l_i=\begin{cases} 
l_{i-1},  & a_i\le a_{i-1} \\
i, & a_i>a_{i-1}
\end{cases}$$

$$r_i=\begin{cases} 
r_{i+1},  & a_i\le a_{i+1} \\
i, & a_i>a_{i+1}
\end{cases}$$

预处理出了 $l$ 和 $r$ 数组，那区间 $L,R$ 成立当且仅当 $l_R\le r_L$。做完了。时间复杂度 $O(n)$。

---

