# 「TOCO Round 1」自适应 PVZ

## 题目背景

爆切今天的毒瘤三维计算几何后，$\color{black}\texttt{Q}\color{red}\texttt{wQcOrZ}$ 打开了某个有趣的 exe 文件。

## 题目描述

可怜的 $\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 在草坪上遇到了 $n$ 只僵尸，第 $i$ 只僵尸在 $l_i$ 时刻出现，会在 $r_i$ 时刻走进房子。

$\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 手头有 $m$ 个豌豆射手。若一个豌豆射手在 $l_i$ 至 $r_i$ 时刻（不包括两个端点）持续攻击 $i$ 僵尸则可以杀死 $i$ 僵尸，但在攻击过程中不能攻击另外两只僵尸且攻击的僵尸不能更换。

现在 $\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 想知道在合理的安排下，最少有几只僵尸会进入他的房子。

## 说明/提示

对于 $30\%$ 的数据，$n,m\leq 6$。  
对于 $60\%$ 的数据，$n,m\leq 10^3$。  
对于另外 $20\%$ 的数据，$m\geq n$。  
对于 $100\%$ 的数据，$1\leq n,m\leq 2\times 10^5$，$1\leq l_i<r_i\leq 10^9$。

## 样例 #1

### 输入

```
2 1
1 2
3 4```

### 输出

```
0```

## 样例 #2

### 输入

```
3 2
1 3
1 3
2 4```

### 输出

```
1```

## 样例 #3

### 输入

```
2 1
1 3
3 5```

### 输出

```
0```

# 题解

## 作者：吴思诚 (赞：10)

## P7391 「TOCO Round 1」自适应 PVZ 题解
[题目传送门](https://www.luogu.com.cn/problem/P7391)

### 思路
这道题贪心的方案有点多，这里一一列举。第一，把僵尸出现时刻和走进房子时刻想成左端点和右端点，按照右端点从小到大排序。第二对于同样可以使用的豌豆射手，我们一定选择上次攻击时间最近的豌豆射手攻击僵尸，因为这样可以更灵活的攻击后面的僵尸。

___
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,ans;
multiset<int>s;//multiset维护上次攻击时间最近的豌豆射手
struct zombie{
	int l,r;
}z[200001];
bool cmp(zombie x,zombie y){
	return x.r<y.r;
}
int main(){
	multiset<int>::iterator it;
	scanf("%d%d",&n,&m);
	if(m>=n){
		printf("0");
		return 0;
	}
	for(i=1;i<=n;i++)
		scanf("%d%d",&z[i].l,&z[i].r);
	sort(z+1,z+1+n,cmp);
	for(i=1;i<=n;i++){
		it=s.upper_bound(z[i].l);
		if(it!=s.begin()){
			it--;
			s.erase(it);
			s.insert(z[i].r);
		}
		else{
			if(s.size()+1>m)//打不死的情况
				ans++;
			else
				s.insert(z[i].r);	
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：sunrise1024 (赞：6)

本题可以贪心，按 $l$ 从小到大排序。

考虑存储当前正在被打的僵尸的 $r$。

新加一只僵尸可以分3类讨论:
- 第一种情况：当前还有空闲的豌豆射手，直接存储当前僵尸的 $r$。
- 第二种情况：当前被打的僵尸最早被杀的已经死了，删除死的僵尸的 $r$ 并插入当前僵尸的 $r$。
- 第三种情况：没有已经死的僵尸的话答案加1，并比较最晚死的僵尸的 $r$ 与当前僵尸的 $r$ 的大小。如果当前僵尸的 $r$ 小，则将最晚死的僵尸的 $r$ 删除并插入当前僵尸的 $r$ 。

综上，需要的操作有：插入一个值，查找最小值，查找最大值，删除最小值，删除最大值

所以很自然的就能想到平衡树

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
const int Inf=1e9+5;
int n,m,tot,ans=0,root;
struct zz{
	int l,r;
}a[MAXN];
bool cmp(zz x,zz y){
	return x.l!=y.l?x.l<y.l:x.r<y.r;//贪心的排序
}
struct tr{
	int v,l,r,pr,k;
}t[MAXN];
void zig(int& x){
	int y=t[x].l;
	t[x].l=t[y].r;
	t[y].r=x;
	x=y;
}
void zag(int& x){
	int y=t[x].r;
	t[x].r=t[y].l;
	t[y].l=x;
	x=y;
}
void Insert(int& no,int vi){//插入
	if(no==0){
		no=++tot;
		t[tot].pr=rand();
		t[tot].v=vi;
		t[tot].k++;
		return;
	}
	if(t[no].v==vi){
		t[no].k++;
		return;
	}
	if(t[no].v<vi){
		Insert(t[no].r,vi);
		if(t[no].pr>t[t[no].r].pr)zag(no);
	}
	else{
		Insert(t[no].l,vi);
		if(t[no].pr>t[t[no].l].pr)zig(no);
	}
}
void de(int& no,int vi){//删除
	if(t[no].v==vi){
		if(t[no].k>1){
			t[no].k--;
			return;
		}
		if(t[no].l==0||t[no].r==0){
			no=t[no].l^t[no].r;
		}
		else{
			if(t[t[no].l].pr<t[t[no].r].pr){
				zig(no);
				de(no,vi);
			}
			else{
				zag(no);
				de(no,vi);
			}
		}
		return;
	}
	if(vi<t[no].v){
		de(t[no].l,vi);
	}
	else{
		de(t[no].r,vi);
	}
}
int qi(int x){//查找前驱
	int ans;
	int roo=root;
	while(roo){
		if(t[roo].v<=x){
			ans=t[roo].v;
			roo=t[roo].r;
		}
		else{
			roo=t[roo].l;
		}
	}
	return ans;
}
int ho(int x){//查找后继
	int ans;
	int roo=root;
	while(roo){
		if(t[roo].v>=x){
			ans=t[roo].v;
			roo=t[roo].l;
		}
		else{
			roo=t[roo].r;
		}
	}
	return ans;
}
int main(){
	srand(time(NULL));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		scanf("%d%d",&a[i].l,&a[i].r);
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i){
		if(m!=0){//情况一
			m--;
			Insert(root,a[i].r);
			continue;
		}
		if(ho(0)/*一个极小值的后继是当前树里的最小值*/<=a[i].l){//情况二
			//cout<<ho(0)<<"\n";
			de(root,ho(0));
			Insert(root,a[i].r);
			continue;
		}
		//cout<<i<<"\n";
		ans++;
		if(qi(Inf)/*一个极大值的前驱是当前树里的最大值*/>a[i].r){//情况三
			de(root,qi(Inf));
			Insert(root,a[i].r);
		}
	}
	cout<<ans;
	return 0;
}

```



---

## 作者：UID341736 (赞：6)

### 算法一

暴力枚举每只僵尸被哪个植物打死。

期望得分 $30$。

### 算法二

考虑记录当前正在被打的僵尸的右端点。

新进来一只僵尸，如果还有豌豆射手空着，就去干他，否则与死得最晚的僵尸比较，如果新僵尸死得更早就换掉它。正确性显然。

期望得分 $60$。

### 算法三

可以安排每个豌豆射手最多只打一只僵尸，所以输出 $0$。

期望得分 $20$。

### 算法四

只需要支持查询全局最小、删除全局最小、查询全局最大、删除全局最大、插入一个数，可以用 `multiset` 或堆替换暴力。

期望得分 $100$。

---

## 作者：ForgotMe (赞：5)

写一个不一样的思路。

考虑 $m=1$ 的时候就是凌乱的线段，直接按照右端点排序然后能打就打。

推广一下，$m>1$ 的时候能不能有豌豆能打就打的去这样子贪心呢，这个是不对的，因为这样只是局部最优解，不是全局最优。

错误代码如下

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
int n,m,ans,dou[200005];
struct node{
	int l,r;
}a[200005];
bool tag[200005];
bool cmp(node x,node y){
	if(x.r==y.r)return x.l<y.l;
	return x.r<y.r;
}
int main() {
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d %d",&a[i].l,&a[i].r);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i].l>=dou[j])ans++,dou[j]=a[i].r;
	printf("%d\n",n-ans);
    return 0;
}
```

发现这个贪心会有一个致命的缺点，即是如果一个豌豆当前保存的右端点很小，有一个很大，但是当前有一个僵尸的左端点都大于等于它们，如果选到了这个很小的，岂不是浪费？于是考虑每次选后从大到小排序，可以获得 `60 pts`。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define LL long long
int n,m,ans,dou[200005];
struct node{
	int l,r;
}a[200005];
bool tag[200005];
bool cmp(node x,node y){
	if(x.r==y.r)return x.l<y.l;
	return x.r<y.r;
}
bool Cmp(int x,int y){
	return x>y;
}
int main() {
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d %d",&a[i].l,&a[i].r);
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			if(a[i].l>=dou[j]){
				ans++,dou[j]=a[i].r;
				break;
			}
		sort(dou+1,dou+m+1,Cmp);
	}
	printf("%d\n",n-ans);
    return 0;
}
```
这不就是查个前驱吗，可以用权值线段树搞，不过直接上平衡树就行，这里用的 `fhq-treap`。
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>
#include <ctime>
#include <algorithm>
using namespace std;
#define LL long long
int n,m,ans;
struct node{
	int l,r;
}a[200005];
const int INF=2e9;
bool cmp(node x,node y){
	if(x.r==y.r)return x.l<y.l;
	return x.r<y.r;
}
struct fhq_treap{
	int cnt,root,x,y,z,ch[400005][2],size[400005],rnd[400005],val[400005];
	int newnode(int value){
		size[++cnt]=1;
		val[cnt]=value;
		rnd[cnt]=rand()*rand()%998244353+1;
		return cnt;
	}
	void updata(int now){
		size[now]=size[ch[now][0]]+size[ch[now][1]]+1;
	}
	void split(int now,int value,int &x,int &y){
		if(!now)x=y=0;
		else {
			if(val[now]<=value){
				x=now;
				split(ch[now][1],value,ch[now][1],y);
			}else{
				y=now;
				split(ch[now][0],value,x,ch[now][0]);
			}
			updata(now);
		}
	}
	int merge(int x,int y){
		if(!x||!y)return x+y;
		if(rnd[x]<rnd[y]){
			ch[x][1]=merge(ch[x][1],y);
			updata(x);
			return x;
		}else{
			ch[y][0]=merge(x,ch[y][0]);
			updata(y);
			return y;
		}
	}
	void ins(int value){
		split(root,value,x,y);
		root=merge(merge(x,newnode(value)),y);
	}
	void del(int value){
		split(root,value,x,z);
		split(x,value-1,x,y);
		y=merge(ch[y][0],ch[y][1]);
		root=merge(merge(x,y),z);
	}
	int rank(int value){
		split(root,value-1,x,y);
		int res=size[x]+1;
		root=merge(x,y);
		return res;
	}
	int kth(int now,int k){
		while(1){
			if(k<=size[ch[now][0]])now=ch[now][0];
			else if(k==size[ch[now][0]]+1)return now;
			else k=k-size[ch[now][0]]-1,now=ch[now][1];
		}
	}
	int pre(int value){
		split(root,value,x,y);
		int res=val[kth(x,size[x])];
		root=merge(x,y);
		return res;
	} 
	int nxt(int value){
		split(root,value,x,y);
		int res=val[kth(y,1)];
		root=merge(x,y);
		return res;
	} 
}T;
int main() {
	srand(time(0));
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d %d",&a[i].l,&a[i].r);
	sort(a+1,a+n+1,cmp);
	T.ins(-INF),T.ins(INF);
	for(int i=1;i<=m;i++)T.ins(0);
	for(int i=1;i<=n;i++){
		int x=T.pre(a[i].l);
		if(x==-INF)continue;
		else {
			ans++;
			T.del(x);
			T.ins(a[i].r); 
		}
	}
	printf("%d\n",n-ans);
    return 0;
}
```


---

## 作者：liaoxingrui (赞：4)

## Content

有 $n$ 个僵尸，第 $i$ 只僵尸在 $l_i$ 时刻出现，会在 $r_i$ 时刻走进房子。

有 $m$ 个豌豆射手。若一个豌豆射手在 $l_i$ 至 $r_i$ 时刻（不包括两个端点）持续攻击 $i$ 僵尸则可以杀死 $i$ 僵尸，但在攻击过程中不能攻击另外的僵尸且攻击的僵尸不能更换。

问最少有几只僵尸会进入房子。

## Solution

这道题可以使用 [multiset](https://blog.csdn.net/qq_50285142/article/details/136097982)。

首先以右端点从小到大排序，由于保证了 multiset 有单调性，所以可以二分查找，找出已经打完僵尸的豌豆射手来打这一个僵尸。

如果没有满足条件的豌豆射手，则判断以有的豌豆射手是否超出数量，如果没有就新增一个，否则答案加一。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,ans;
multiset<int> q;
struct node{
	int l,r;
}a[N];
inline bool cmp(node x,node y){
	return x.r<y.r;
} 
int main(){
	multiset<int>::iterator it;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i].l>>a[i].r;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		it=q.upper_bound(a[i].l);
		if(it!=q.begin()){
			it--;
			q.erase(it);
			q.insert(a[i].r);
		}
		else if(q.size()==m)
			ans++;
		else
			q.insert(a[i].r);
	} 
	cout<<ans;
	return 0;
}
```

---

## 作者：Cutest_Junior (赞：4)

## 题解 P7391 【「TOCO Round 1」自适应 PVZ】

### 题意

+ $n$ 个左闭右开区间 $[l,r)$，选取区间，使每个点都被不超过 $m$ 个区间覆盖；
+ 最大化选取的区间数；
+ $1\le n,m\le2\times10^5$，$1\le l_i,r_i\le10^9$。

### 做法

发现似乎和 P1803 很像？

仔细比较，发现主要有两点不同：
1. P1803 保证 $m=1$；
2. P1803 的 $l,r$ 是 $10^6$ 次方级别的。

对于第二点，加个离散化即可，不再赘述。

然后是第一点。

先回忆一下 P1803 的做法。

> 显然放右端点最靠左的线段最好，从左向右放，右端点越小妨碍越少  

> 其他线段放置按右端点排序，贪心放置线段，即能放就放

——kkksc03

简单证明一下：

如果按右端点升序排序，那两个区间如果相交，那选右端点小的区间结果不会更差。

如果还有一个右端点更大的区间：
1. 如果与两个区间都相交，那选哪个答案都一样；
2. 如果与两个区间都不相交，那选哪个答案都一样；
3. 如果与右端点大的区间相交，与右端点小的区间相交，那选右端的小的区间显然更优；
4. 如果与右端点小的区间相交，与右端点大的区间相交，你会发现没有这种可能。

这个证明同样适用于本题。

本题做法也是按右端点升序排序，能放就放。

问题又来了，怎么判断能不能放呢？

选一个区间，就把这个区间全部加上 $1$，要保证加后每个点都不超过 $m$，那加之前区间最大值就要小于 $m$。

区间加，区间求最大值，线段树维护即可。

### 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 2e5 + 5;

vector<int> v;

int id(int x) {
	return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

struct Node {
	int l, r;
	
	bool operator < (Node a) {
		if (r != a.r) {
			return l > a.l;
		}
		return r < a.r;
	}
} a[N];

struct Tree {
	Tree *ls, *rs;
	int maxx, lazy;
	
	Tree() {
		maxx = lazy = 0;
	}
	
	void update(int k) {
		lazy += k;
		maxx += k;
	}
	
	void merge(Tree t1, Tree t2) {
		maxx = max(t1.maxx, t2.maxx);
	}
} seg[N << 2], *root = seg;
int tot;

void build(Tree *t, int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	t->ls = &seg[++tot];
	t->rs = &seg[++tot];
	build(t->ls, l, mid);
	build(t->rs, mid + 1, r);
}

void pushdown(Tree *t) {
	t->ls->update(t->lazy);
	t->rs->update(t->lazy);
	t->lazy = 0;
}

void change(Tree *t, int l, int r, int x, int y, int k) {
	if (x <= l && r <= y) {
		t->update(k);
		return;
	}
	pushdown(t);
	int mid = (l + r) >> 1;
	if (x <= mid) {
		change(t->ls, l, mid, x, y, k);
	}
	if (mid < y) {
		change(t->rs, mid + 1, r, x, y, k);
	}
	t->merge(*t->ls, *t->rs);
}

Tree query(Tree *t, int l, int r, int x, int y) {
	if (x <= l && r <= y) {
		return *t;
	}
	pushdown(t);
	int mid = (l + r) >> 1;
	Tree ans;
	if (x <= mid) {
		ans.merge(ans, query(t->ls, l, mid, x, y));
	}
	if (mid < y) {
		ans.merge(ans, query(t->rs, mid + 1, r, x, y));
	}
	return ans;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].l, &a[i].r);
		++a[i].l;
		v.push_back(a[i].l);
		v.push_back(a[i].r);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	sort(a + 1, a + n + 1);
	int cnt = 0;
	build(root, 1, n + n);
	for (int i = 1; i <= n; ++i) {
		if (query(root, 1, n + n, id(a[i].l), id(a[i].r)).maxx == m) {
			continue;
		}
		++cnt;
		change(root, 1, n + n, id(a[i].l), id(a[i].r), 1);
	}
	printf("%d", n - cnt);
}
```

---

## 作者：Loser_Syx (赞：3)

考虑枚举每个时间，我们发现，对于当前答案有重要影响的只有 $n$ 个时间，即 $l_i$，我们考虑分配每个植物的工作，对于当前时间 $l_i$，我们只能暂时选出 $m$ 个僵尸 $l_j < l_i$ 且 $r_j > l_i$ 的 $j$ 被我们打，因为我们想要杀的最多，所以我们要满足 $r_j$ 最小，如果满足条件的比 $m$ 多，那么一定要舍去一些。

考虑使用什么数据结构维护，发现 `multiset` 可以维护每个 $r_j$ 的大小进行排序，每次舍去一定是舍去最大的（即 `.end()`），这就是一个进入房子的僵尸。  
因为按照 $r_j$ 从小到大排序，所以如果有能完成任务的，那么最前面的一定是完成的，需要删除。  
使用 `.erase()` 进行删除。

复杂度 $O(n \log n)$。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
struct node {
    int l, r;
    bool operator < (const node &a) const {
        if (l == a.l) return r < a.r;
        return l < a.l;
    }
};
int main() {
    multiset<int> s;
    int n, m, ans = 0;
    cin >> n >> m;
    vector<node> v(n);
    for (auto &i : v) {
        cin >> i.l >> i.r;
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n && v[i].l == v[j].l; i = j, j++) s.insert(v[j].r);
        while (s.size() && *s.begin() <= v[i].l) s.erase(s.begin());
        while (s.size() > m) {
            auto e = s.end();
            --e;
            s.erase(e);
            ans++;
        }
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：xkcdjerry (赞：3)

~~（本题解写的时候）接近 2k 提交只有 60 多个通过，可以被称为当之无愧的毒瘤题。~~    

为了使得进入屋子的僵尸最少，那么显然是让被消灭的僵尸最多，对于 $m=1$ 的时候可以参考 [P1083](https://www.luogu.com.cn/problem/P1803) 的做法，按照右端点排序之后线性扫一遍。  

对于 $m>1$ 也可以参考这个思路，维护 $m$ 个完成任务的时间 $f_i$，每次从可以接这个任务（即 $f_j \leqslant l_i$）的里面选取浪费（空闲时间）**最少**（即 $l_i-f_j$ 最小）的一个，将 $f_j$ 更新为 $r_i$ 即可。  

但是如果每次都通过 $O(m)$ 的扫描来确定最小值那么显然会 TLE ~~明明是 Time Limit Excellent~~。所以必须要快速求出某个数在序列中最小大于等于其的数据结构。  

由于一个数先查询多少个数小于它（假如有 $k$ 个）然后在去找序列中最小的有 $k$ 个数小于它的数，就可以找出最小的大于等于它的数，那么在插入和查询的时候给所有数乘 $-1$ 就可以用这个操作找出最大的小于等于它的数。  

看到这几个操作就可以想到平衡树，由于本蒟蒻太菜了所以只会写替罪羊树。$O(n\log m+n\log n)$ 很愉快的就过了：~~才不会告诉你因为需要调平衡因子才能卡过去提交了半页呢~~

```cpp
#include <cstdio>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#define N 200010
#define ALPHA 0.85
struct node
{
    int v,c;
    node *l,*r;
    int size,nodes;
    int empty;
	void update()
	{
		size=c+(l?l->size:0)+(r?r->size:0);
		nodes=(c>0)+(l?l->nodes:0)+(r?r->nodes:0);
		empty=(c==0)+(l?l->empty:0)+(r?r->empty:0);
	}
}*head;
typedef node* sgt;
inline bool bad(sgt o)
{
    return (o->l&&o->l->size > ALPHA*o->size)||
            (o->r&&o->r->size > ALPHA*o->size)||
            (o->empty > ALPHA*o->nodes);
}
int tmpv[N],tmpc[N];
sgt build(int l,int r)
{
    if(l>r) return NULL;
    int mid=(l+r)/2;
    sgt o=(sgt)malloc(sizeof(node));
    o->l=build(l,mid-1);
    o->r=build(mid+1,r);
    o->v=tmpv[mid];
    o->c=tmpc[mid];
	o->empty=0;
    o->update();
	return o;
}
int cur;
void splat(sgt &o)
{
    if(!o) return;
    splat(o->l);
    if(o->c)
    {
        tmpv[cur]=o->v;
        tmpc[cur]=o->c;
        cur++;
    }
    splat(o->r);
    free(o);
}
void rebuild(sgt &o)
{
    cur=1;
    splat(o);
    o=build(1,cur-1);
}
inline void check(sgt &o)
{
	if(bad(o)) rebuild(o);
}
void insert(int v,sgt &o)
{
    if(!o)
    {
        o=(sgt)malloc(sizeof(node));
        o->l=o->r=NULL;
        o->v=v;
        o->c=1;
        o->size=1;
		o->nodes=1;
        o->empty=0;
        return;
    }
    if(o->v==v) o->c++;
    else if(v<o->v) insert(v,o->l);
    else insert(v,o->r);
	o->update();
    check(o);
}
void remove(int v,sgt &o)
{
	if(!o)
	{
		puts("FUCK");
		abort();
	}
	if(v<o->v) remove(v,o->l);
	else if(v>o->v) remove(v,o->r);
	else o->c--;
	o->update();
	check(o);
}
int rank(int v,sgt o)
{
	if(!o) return 0;
	if(v<o->v) return rank(v,o->l);
	else if(v==o->v) return o->l?o->l->size:0;
	else return (o->l?o->l->size:0)+o->c+rank(v,o->r);
}
int query(int rk,sgt o)
{
	int s=o->l?o->l->size:0;
	if(rk<s) return query(rk,o->l);
	rk-=s;
	if(rk<o->c) return o->v;
	rk-=o->c;
	return query(rk,o->r);
}
using std::sort;
struct seg
{
	int l,r;
	bool operator<(seg b) const
	{
		return r<b.r;
	}
}a[N];
int n,m;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d%d",&a[i].l,&a[i].r);
	sort(a,a+n);
	//f[i]=i不接受l<i
	int ans=n;
	sgt head=NULL;
	for(int i=0;i<m;i++) insert(0,head);
	for(int i=0;i<n;i++)
	{
		//把f塞到平衡树里
		//需要的就是>=a[i].l的最小
		int rk=rank(-a[i].l,head);
		if(rk!=m)
		{
			int mn=query(rk,head);
			ans--;
			remove(mn,head);
			insert(-a[i].r,head);
		}
	}
	printf("%d",ans);
}
```

---

## 作者：lsy_41 (赞：2)

分析可以得出这样一个贪心结论，我们首先将时间按 $r$ 排序，之后，对于每一个到来的僵尸，我们通过查询比 $l$ 小的最大数，安排其来攻击这只僵尸，这样可以有更多的机会让空余时间在前的豌豆攻击到来时间早的僵尸，查询我们很容易想得到用平衡树，也就是查找前驱，不过需要注意的一点是边界问题，题目中说不包含 $l_i$， $r_i$，意思就是，豌豆从 $l_i + 1$ 开始打，打到 $r_i - 1$ 即可，这样我们就得到了最终的做法。

首先，将 $m$ 个 $0$ 插入到平衡树中，代表有 $m$ 个豌豆从时刻 $0$ 开始就可以攻击僵尸，对于每一个僵尸，我们查询 $l_i + 1$ 的前驱，注意不是 $l_i$，因为我们从 $l_i + 1$ 开始打就行（主要因为我的 splay 查询前驱是严格小于，因此就要查 $l_i + 1$ 了），安排了这一个豌豆之后，我们要更新它的可用时间，也就是从平衡树中删掉 $l_i + 1$ 的前驱，再插入 $r_i$，这里为什么不是 $r_i - 1$ 了呢，因为打到 $r_i - 1$ 时还在打，到 $r_i$ 才能用于下一个，这样就做完啦。

下面贴上代码：

```cpp
#include <bits/stdc++.h>
#define inf 0x3fffffff
#define maxn 2000005
using namespace std;
struct node {
	int l, r;
	bool operator<(const node& x) const {
		return r == x.r ? l < x.l : r < x.r;
	}
}N[maxn];
class Splay {
private:
    int rt, tot, fa[maxn], ch[maxn][2], cnt[maxn], siz[maxn];
    void maintain(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + cnt[x]; }
    bool get(int x) { return x == ch[fa[x]][1]; }
    void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = cnt[x] = siz[x] = val[x] = 0; }
    void rotate(int x) {
        int y = fa[x], z = fa[y], chk = get(x);
        ch[y][chk] = ch[x][chk ^ 1];
        if (ch[x][chk ^ 1]) fa[ch[x][chk ^ 1]] = y;
        ch[x][chk ^ 1] = y;
        fa[y] = x; fa[x] = z;
        if (z) ch[z][y == ch[z][1]] = x;
        maintain(x); maintain(y);
    }
    void splay(int x) {
        for (int f = fa[x]; f = fa[x], f; rotate(x))
            if (fa[f]) rotate(get(x) == get(f) ? f : x);
        rt = x;
    }
public:
    int val[maxn];
    void insert(int k) {
        if (!rt) {
            val[++tot] = k;
            cnt[tot]++;
            rt = tot;
            maintain(rt);
            return;
        }
        int cur = rt, f = 0;
        while (1) {
            if (val[cur] == k) {
                cnt[cur]++;
                maintain(cur);
                maintain(f);
                splay(cur);
                return;
            }
            f = cur;
            cur = ch[cur][val[cur] < k];
            if (!cur) {
                val[++tot] = k;
                cnt[tot]++;
                fa[tot] = f;
                ch[f][val[f] < k] = tot;
                maintain(tot);
                maintain(f);
                splay(tot);
                return;
            }
        }
    }
    int rank(int k) {
        int ans = 0, cur = rt;
        while (1) {
            if (k < val[cur])
                cur = ch[cur][0];
            else {
                ans += siz[ch[cur][0]];
                if (k == val[cur]) {
                    splay(cur);
                    return ans + 1;
                }
                ans += cnt[cur];
                cur = ch[cur][1];
            }
        }
    }
    int kth(int k) {
        int cur = rt;
        while (1) {
            if (ch[cur][0] && k <= siz[ch[cur][0]])
                cur = ch[cur][0];
            else {
                k -= cnt[cur] + siz[ch[cur][0]];
                if (k <= 0) {
                    splay(cur);
                    return val[cur];
                }
                cur = ch[cur][1];
            }
        }
    }
    int pre() {
        int cur = ch[rt][0];
        if (!cur) return cur;
        while (ch[cur][1]) cur = ch[cur][1];
        splay(cur);
        return cur;
    }
    int nxt() {
        int cur = ch[rt][1];
        if (!cur) return cur;
        while (ch[cur][0]) cur = ch[cur][0];
        splay(cur);
        return cur;
    }
    void del(int k) {
        rank(k);
        if (cnt[rt] > 1) {
            cnt[rt]--;
            maintain(rt);
            return;
        }
        if (!ch[rt][0] && !ch[rt][1]) {
            clear(rt);
            rt = 0;
            return;
        }
        if (!ch[rt][0]) {
            int cur = rt;
            rt = ch[cur][1];
            fa[rt] = 0;
            clear(cur);
            return;
        }
        if (!ch[rt][1]) {
            int cur = rt;
            rt = ch[cur][0];
            fa[rt] = 0;
            clear(cur);
            return;
        }
        int cur = rt, x = pre();
        fa[ch[cur][1]] = x;
        ch[x][1] = ch[cur][1];
        clear(cur);
        maintain(rt);
        return;
    }
}spl;
int n, m, ans;
int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> N[i].l >> N[i].r;
	sort(N + 1, N + 1 + n);
    spl.insert(inf), spl.insert(-inf);
    for (int i = 1; i <= m; i++) spl.insert(0);
    for (int i = 1; i <= n; i++) {
        spl.insert(N[i].l + 1);
        int x = spl.val[spl.pre()];
        spl.del(N[i].l + 1);
        if (x == -inf)continue;
        else {
            ans++;
            spl.del(x);
            spl.insert(N[i].r);
        }
    }
    cout << n - ans;
    return 0;
}
```

完结撒花！

---

## 作者：wizard（偷开O2 (赞：1)

一道平衡树维护序列的好题。

## 题意

有 $n$ 个僵尸，$m$ 个豌豆射手，第 $i$ 个僵尸在 $l_{i}$ 点出现 $r_i$ 消失，如果要消灭这个僵尸，单个豌豆射手必须在僵尸存在的时间里面进行无休止攻击且不能半途而废。

## 分析

按贪心思想，直接按照僵尸出现的右端点排序，如果当前僵尸的左端点有前继，那就说明前一个僵尸已经杀完了，直接把当前僵尸的右端点扔到平衡树里面就行了。

右端点小的优先杀，所以右端点大的且没有豌豆射手空余下来杀他的答案就 $+1$，他也永远不会被杀。

其实我们可以算出满足要求不被杀的僵尸，剩下的就是要被杀的。

直接范浩强维护就好了，我喜欢范浩强，这个做法。

## 代码
```cpp
//ways:fhq-freap
//noip 2024 rp++ 
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ls ((now<<1))
#define rs ((now<<1)|1)
#define mid ((l+r)>>1)
const int maxn=1e6+10;
const int inf=2147483647;
const int maxa=2e3+10;
const int modd=998244353;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
//只考虑僵尸出现的右端点
//所以每一个豌豆射手存的都是杀死僵尸的时间点
//杀完了一个，插入另一个，那就是删除之前的右端点，插入新的右端点
//右端点小的优先杀，所以右端点大的要是没机会被杀答案就+1； 
int ch[maxn][2],val[maxn],cnt[maxn],rnd[maxn],len[maxn];
void pushup(int now){
	len[now]=len[ch[now][0]]+len[ch[now][1]]+1;
}
int tot;
int add(int v){
	len[++tot]=1;
	val[tot]=v;
	rnd[tot]=rand();
	return tot;
}
int merge(int x,int y){
	if(!x||!y)return x+y;
	if(rnd[x]<rnd[y]){
		ch[x][1]=merge(ch[x][1],y);
		pushup(x);
		return x;
	}else{
		ch[y][0]=merge(x,ch[y][0]);
		pushup(y);
		return y;
	}
}
int x,y,z;
int root;
void split(int now,int k,int &x,int &y){
	if(!now){
		x=y=0;
	}else{
		if(val[now]<=k){
			x=now;
			split(ch[now][1],k,ch[now][1],y);
		}else{
			y=now;
			split(ch[now][0],k,x,ch[now][0]);
		}
		pushup(now);
	}
}
int kth(int now,int k){
	if(k<=len[ch[now][0]]){
		return kth(ch[now][0],k);
	}else if(k==len[ch[now][0]]+1){
		return now;
	}else{
		return kth(ch[now][1],k-len[ch[now][0]]-1);
	}
}

void insert(int a){
	split(root,a,x,y);
	root=merge(merge(x,add(a)),y);
}
int pre(int a){
	int x,y; 
	split(root,a,x,y);
	int ans=kth(x,len[x]);
	root=merge(x,y);
	return val[ans];
}
void del(int v){
	split(root,v,x,z);
	split(x,v-1,x,y);
	y=merge(ch[y][0],ch[y][1]);
	root=merge(merge(x,y),z);
}
int n,m;
struct node{
	int l,r;
}dead[maxn];
bool cmp(node a,node b){
	if(a.r==b.r){
		return a.l<b.l;
	}
	return a.r<b.r;
}
int ans;
signed main(){
	cin >> n>> m;
	for(int i=1;i<=n;i++){
		cin >> dead[i].l >> dead[i].r;
	}
	sort(dead+1,dead+n+1,cmp);
	insert(-inf);insert(inf);
	for(int i=1;i<=m;i++)insert(0);
	for(int i=1;i<=n;i++){
		int now=pre(dead[i].l);
		if(now!=-inf){
			ans++;
			del(now);
			insert(dead[i].r);
		}
	}
	cout << n-ans << endl;
	return 0;
}
```

---

## 作者：_zhx (赞：1)

# P7391 「TOCO Round 1」自适应 PVZ 题解

## 题目大意

若一个豌豆射手在 $l_i$ 至 $r_i$ 时刻（不包括两个端点）持续攻击 $i$ 僵尸则可以杀死 $i$ 僵尸，但在攻击过程中不能攻击另外两只僵尸且攻击的僵尸不能更换。

有 $n$ 个僵尸，和 $m$ 个豌豆射手。

接下来 $n$ 行，每行两个整数 $l_i$ 和 $r_i$ 表示僵尸 $i$ 的出现时刻和走进房子时刻。

### 大致思路

我们可以先把 $l_i$ 到 $r_i$ 这段区间看成一条线段。
  
然后，我们可以把右端点从小到大贪心一下。

对于都可以用的豌豆射手，我们选择离上次攻击最近的豌豆射手更优，因为这样可以更优地干掉后面的僵尸。

所以，我们可以用 `multiset` 来维护离上次攻击时间最近的豌豆射手。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s=0;
multiset<int>ms;
struct PVZ{int l,r;}a[200001];
bool cmp(PVZ x,PVZ y){return x.r<y.r;}
int main()
{
	scanf("%d%d",&n,&m);
	if(m>=n) cout<<"0",exit(0);//如果豌豆射手的数量比僵尸多，就不会有僵尸闯入
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].l,&a[i].r);
	sort(a+1,a+1+n,cmp);//将a.r（右端点）从小到大排序
	for(int i=1;i<=n;i++)
	{
		auto it=ms.upper_bound(a[i].l);//寻找第一个大于a[i].l的数
		if(it!=ms.begin()) ms.erase(--it),ms.insert(a[i].r);
		else if(ms.size()<m) ms.insert(a[i].r);
		else s++;	
	}
	cout<<s;
	return 0;
}
```


---

## 作者：Mistybranch (赞：1)

[传送门](https://www.luogu.com.cn/problem/P7391)

题目大概意思是：有 $n$ 个开区间 $(l_i, r_i)$，有 $m$ 条直线，现在将这 $n$ 个开区间覆盖在 $m$ 条直线上，使得每条直线上的每个点都不被一个以上的区间覆盖。问最少有多少个开区间覆盖不到直线上。

这道题显然是贪心，具体思路如下：

先将所有区间以 $l_i$ 为第一关键字，$r_i$ 为第二关键字排序。

```cpp
struct zom {
	int l, r;
	
	bool operator < (const zom & z) const {
		if (l == z.l) {
			return r < z.r;
		}
		
		return l < z.l;
	}
};

sort(_z + 1, _z + _n + 1);
```

对于第 $i$ 个区间：

- 若现在有一条直线没有区间覆盖，那么就将区间 $i$ 覆盖在这条直线上。

- 否则，如果一条直线的最右覆盖点在 $l_i$ 的左边（肯定是要找最右覆盖点在最左边的直线），那么就将区间 $i$ 覆盖在这条直线上。

- 否则就肯定覆盖不上了。但还有一种小情况：

	- 如果一条直线的最右覆盖点在 $r_i$ 的右边（肯定是要找最右覆盖点在最右边的直线），那么就将这条直线的最右覆盖点改为 $r_i$（因为 $l_i$ 是递增的，所以这条直线原来的最右覆盖点所在区间的左端点一定在 $l_i$ 的左边或是与 $l_i$ 相等，使得这条直线原来的最右覆盖点所在区间能被替换成第 $i$ 个区间。这段话有点绕可以多读几遍）。
    
但是这样的话复杂度是 $O(n^2)$，太高了，我们需要一种数据结构来存每条直线的最右覆盖点，可以进行以下操作：

- 插入元素
- 查找最小值
- 删除最小值
- 查找最大值
- 删除最大值

所以题解区里就有了各式各样的解法，我用的是 ```multiset```，它的底层实现是红黑树，是一种自平衡二叉搜索树，能保证以上操作都是 $O(logN)$ 的复杂度，这样就满足我们的需求了。

```cpp
for (int i = 1; i <= _n; i++) {
	if (_m) {
		_s.insert(_z[i].r);
		_m--;
	}
	 
	else if ((*(_s.begin())) <= _z[i].l) {
		_s.erase(_s.begin());
		_s.insert(_z[i].r);
	}
	
	else {
		_res++;
		
		it = _s.end();
		it--;
		
		if ((*it) > _z[i].r) {
			_s.erase(it);
			_s.insert(_z[i].r);
		}
	}
}
```
完整代码：

```cpp


#include <bits/stdc++.h>

using namespace std;

struct zom {
	int l, r;
	
	bool operator < (const zom & z) const {
		if (l == z.l) {
			return r < z.r;
		}
		
		return l < z.l;
	}
}_z[200009];

int _n, _m, _res; 
multiset<int> _s;

void ParseIn () { 
	cin >> _n >> _m;
	
	for (int i = 1; i <= _n; i++) {
		cin >> _z[i].l >> _z[i].r;
	}
}

void Core () {
	int tmp = _m;
	multiset<int>::iterator it;
	
	sort(_z + 1, _z + _n + 1);
	
	for (int i = 1; i <= _n; i++) {
		if (_m) {
			_s.insert(_z[i].r);
			_m--;
		}
		 
		else if ((*(_s.begin())) <= _z[i].l) {
			_s.erase(_s.begin());
			_s.insert(_z[i].r);
		}
		
		else {
			_res++;
			
			it = _s.end();
			it--;
			
			if ((*it) > _z[i].r) {
				_s.erase(it);
				_s.insert(_z[i].r);
			}
		}
	}
}

void WriteOut () {
	cout << _res << endl;
}

int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	ParseIn();
	Core();
	WriteOut();
	
	return 0;
}
```


---

## 作者：Lian_zy (赞：0)

这道题让我想起了一道 USACO 的题，[P2255 [USACO14JAN] Recording the Moolympics S](https://www.luogu.com.cn/problem/P2255)，算是这道题的弱化版。

那道题相当于这道题 $m = 2$ 的一种特殊情况，你把录音机理解为豌豆射手，节目理解为僵尸就好了。

那道题就是按照每个节目的右端点排序，然后每次选择结束时间最晚的空闲录音机录制节目，如果没有录音机符合条件，那么这个节目就放弃录制了。

那么同理，我们每次在 $m$ 个豌豆射手里面进行这个操作就好了。

**但 是！！！**

每次在 $m$ 个豌豆射手里面寻找复杂度是 $O(nm)$ 的，对于 $n,m \le 2 \times 10^5$ 的数据显然过不去。

注意到我们的目标是寻找结束时间最大且已经结束的录音机，即满足 $end_i \le S_i$ 中 最大的 $end_i$。

可以用一个 set 或者平衡树维护这个操作，剩下的就很简单了，set 里面 $m$ 个元素，$n$ 次操作，复杂度就只有 $O(n \log m)$ 了。

#### code

于是就快乐的 AC 了，由于搞不懂那些神奇的指针操作，我没用 set，而是平衡树，虽然代码长，但是错误少，出错也好找。

可能平衡树的常数比较大，这玩意硬是在 C++20 O2 下跑了将近 900ms。

[AC 记录](https://www.luogu.com.cn/record/188334713)
``` cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 4e5 + 10;
int n, m, edt, tot, ans, root;
struct node {
	int l, r;
} a[maxn];
struct npde {
	int l, r, rd, val, size;
} t[maxn];
bool cmp(node x, node y) {
	return x.r < y.r;
}
void push_up(int now) {
	t[now].size = t[t[now].l].size + t[t[now].r].size + 1;
	return ;
}
void spilt(int now, int key, int &x, int &y) {
	if (now) {
		if (t[now].val <= key) {
			x = now;
			spilt(t[now].r, key, t[now].r, y);
		} else {
			y = now;
			spilt(t[now].l, key, x, t[now].l);
		}
		push_up(now);
	} else x = y = 0;
	return ;
}
int merge(int x, int y) {
	if (x && y) {
		if (t[x].rd <= t[y].rd) {
			t[x].r = merge(t[x].r, y);
			push_up(x);
			return x;
		} else {
			t[y].l = merge(x, t[y].l);
			push_up(y);
			return y;
		}
	}
	return x + y;
}
int new_node(int key) {
	tot++;
	t[tot].l = t[tot].r = 0;
	t[tot].val = key;
	t[tot].size = 1;
	t[tot].rd = rand();
	return tot;
}
void insert(int key) {
	int x, y;
	spilt(root, key, x, y);
	root = merge(merge(x, new_node(key)), y);
	return ;
}
void del(int key) {
	int x, y, z;
	spilt(root, key, x, y);
	spilt(x, key - 1, x, z);
	z = merge(t[z].l, t[z].r);
	root = merge(merge(x, z), y);
	return ;
}
int get_key(int now, int k) {
	int cnt = t[t[now].l].size + 1;
	if (cnt == k) return t[now].val;
	else if (cnt < k) return get_key(t[now].r, k - cnt);
	return get_key(t[now].l, k);
}
int pre(int key) {
	int x, y;
	spilt(root, key - 1, x, y);
	if (x) {
		int ans = get_key(x, t[x].size);
		root = merge(x, y);
		return ans;
	}
	root = y;
	return -1;
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d %d", &a[i].l, &a[i].r);
	for (int i = 1; i <= m; i++) insert(0);
	sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		edt = pre(a[i].l + 1);
		if (edt == -1) continue;
		del(edt);
		ans++;
		insert(a[i].r);
	}
	printf("%d\n", n - ans);
	return 0;
}
```

---

## 作者：liguangjun2023 (赞：0)

#### 框架思维
主要的数据结构体为：multiset 、结构体数组。因为关键词有重复，所以要选择 multiset ，不能选择 set 。

主要算法为：排序、二分查找。

具体思路

1. 对结构体数组排序，按照结束时间进行递增排序，结束相同，按照开始时间递增排序。
2. multiset 集合保存 $m$ 个射手，干掉的 $m$ 个僵尸的结束时间。
3. 如果当前的僵尸开始时间不等于集合的最早时间，则使用距离僵尸开始最早的射手把它干掉。
4. 如果当前的僵尸开始时间等于集合中最后的结束时间，且 multiset 不够 $m$ 个则进入 multiset ,即安排一个射手把它干掉。
5. 如果当前的僵尸开始时间等于集合中最后的结束时间，且 multiset 够 $m$ 个，则该僵尸无法干掉。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct node{
	int lef,rig;
}a[N];
bool cmp(node x,node y){
	if(x.rig!=y.rig)	return x.rig<y.rig;
	return x.lef<y.lef;
}
int n,m;
multiset<int> s; 

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		 cin>>a[i].lef>>a[i].rig;
	}
	sort(a+1,a+1+n,cmp);
	int ans=0;
	for(int i=1;i<=n;i++){
		auto at=s.upper_bound(a[i].lef);
		if(at==s.begin()){
			if(s.size()<m){
				s.insert(a[i].rig);
			}else{
				ans+=1;
			}
		}else{
			at--;
			s.erase(at);
			s.insert(a[i].rig);
		} 
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：run_away (赞：0)

## 题意

有 $n$ 个豌豆射手，$m$ 个僵尸。

对于第 $i$ 个僵尸，如果任意一个豌豆射手在 $l_i\sim r_i$ 的时间里持续攻击它，僵尸 $i$ 就会被杀死。

每一个豌豆射手在同一时间只能攻击一个僵尸，求最少无法杀死多少僵尸。

## 分析

首先有一个很显然的贪心，就是优先攻击 $r$ 较小的僵尸，因为可以给后面的僵尸预留时间。

给所有僵尸按照左右端点排序，现在会有几种情况：

1. 当前有空余的豌豆射手。直接放一个攻击就可以了。
2. 没有空余的豌豆射手。那么给答案加 $1$。

但是这么做会有一个漏洞，因为我们以左端点为第一关键字排序，那么后面来的僵尸可能右端点要小一些，当前的僵尸和后来的僵尸都无法杀死，那么就应该选择一个右端点小的攻击，理由和贪心策略相同。

这样我们只需要维护当前正在被攻击的僵尸的 $r$ 即可。

这个数据结构需要支持查询全局最大值（如上）、全局最小值（判断是否有空余）；进行单点插入、删除，很明显就是平衡树了。

我用的 Splay，STL 的 set 应该也可以过。~~（吐槽一句：平衡树板子不是蓝吗？虽然它可以用 set，但是不至于是黄吧！）~~

总时间复杂度 $O(m\log n)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define dbg(x) cout<<#x<<": "<<x<<"\n"
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll mod=1e9+7,maxn=2e5+5,maxt=505;
ll n,m;
struct node{
    ll l,r;
}zom[maxn];
template<typename tp=int,int N=maxn>class Splay{
private:
    int rt,node_cnt,INF=INT_MAX;
    struct node{
        tp val;
        int cnt,siz,pre,ch[2];
    };
    vector<node>t;
    inline void pushup(int x){
        t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz+t[x].cnt;
    }
    inline void rotate(int x){
        int y=t[x].pre,z=t[y].pre,k=(t[y].ch[1]==x);
        t[z].ch[t[z].ch[1]==y]=x,t[x].pre=z;
        t[y].ch[k]=t[x].ch[k^1],t[t[x].ch[k^1]].pre=y;
        t[x].ch[k^1]=y,t[y].pre=x;
        pushup(y),pushup(x);
    }
    inline void splay(int x,int to){
        while(t[x].pre!=to){
            int y=t[x].pre,z=t[y].pre;
            if(z!=to){
                ((t[z].ch[0]==y)^(t[y].ch[0]==x))?rotate(x):rotate(y);
            }
            rotate(x);
        }
        if(!to)rt=x;
    }
    inline void find(int x){
        int cur=rt;
        if(!cur)return;
        while(t[cur].ch[x>t[cur].val]&&x!=t[cur].val){
            cur=t[cur].ch[x>t[cur].val];
        }
        splay(cur,0);
    }
public:
    Splay(){
        rt=node_cnt=0;
        t.resize(N);
        t[0].siz=t[0].cnt=t[0].pre=0;
        insert(INF),insert(-INF);
    }
    inline void reserve(int cap){
        if(t.capacity()<cap)t.reserve(cap);
    }
    inline void insert(tp x){
        int cur=rt,frm=0;
        while(cur&&x!=t[cur].val){
            frm=cur,cur=t[cur].ch[x>t[cur].val];
        }
        if(cur)++t[cur].cnt;
        else{
            cur=++node_cnt;
            if(!frm)rt=cur;
            else t[frm].ch[x>t[frm].val]=cur;
            t[cur].val=x,t[cur].cnt=1,t[cur].pre=frm;
            t[cur].siz=1,t[cur].ch[0]=t[cur].ch[1]=0;
        }
        splay(cur,0);
    }
    inline int get_pre(tp x){
        find(x);
        if(t[rt].val<x)return rt;
        int cur=t[rt].ch[0];
        while(t[cur].ch[1])cur=t[cur].ch[1];
        splay(cur,0);
        return cur;
    }
    inline int get_nxt(tp x){
        find(x);
        if(t[rt].val>x)return rt;
        int cur=t[rt].ch[1];
        while(t[cur].ch[0])cur=t[cur].ch[0];
        splay(cur,0);
        return cur;
    }
    inline tp get_pre_val(tp x){return t[get_pre(x)].val;}
    inline tp get_nxt_val(tp x){return t[get_nxt(x)].val;}
    inline void erase(tp x){
        int x_pre=get_pre(x),x_nxt=get_nxt(x);
        splay(x_pre,0),splay(x_nxt,x_pre);
        int cur=t[x_nxt].ch[0];
        if(t[cur].cnt>1)--t[cur].cnt,splay(cur,0);
        else t[x_nxt].ch[0]=0;
    }
    inline tp kth(int rank){
        ++rank;
        int cur=rt,son;
        if(t[cur].siz<rank)return INF;
        while(1){
            son=t[cur].ch[0];
            if(rank>t[son].siz+t[cur].cnt){
                rank-=t[son].siz+t[cur].cnt;
                cur=t[cur].ch[1];
            }
            else if(t[son].siz>=rank)cur=son;
            else{
                splay(cur,0);
                return t[cur].val;
            }
        }
    }
    inline int get_rank(tp x){
        find(x);
        if(t[rt].val>=x)return t[t[rt].ch[0]].siz;
        else return t[t[rt].ch[0]].siz+t[rt].cnt;
    }
};
Splay<ll>splay;
inline void solve(){
    n=read(),m=read();
    for(ll i=1;i<=n;++i)zom[i].l=read(),zom[i].r=read();
    sort(zom+1,zom+n+1,[](node a,node b){
        return a.l!=b.l?a.l<b.l:a.r<b.r;
    });
    ll ans=0;
    for(ll i=1;i<=n;++i){
        ll fir=splay.get_nxt_val(-INT_MAX),sec=splay.get_pre_val(INT_MAX);
        if(m){
            --m;
            splay.insert(zom[i].r);
        }
        else if(fir<=zom[i].l){
            splay.erase(fir);
            splay.insert(zom[i].r);
        }
        else{
            ++ans;
            if(sec>zom[i].r){
                splay.erase(sec);
                splay.insert(zom[i].r);
            }
        }
    }
    printf("%lld",ans);
}
signed main(){
    ll t=1;
    srand(time(0));
    while(t--){
        solve();
    }
    return 0;
}
```

---

## 作者：lizhengdong (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/P7391)

$l_i$ 到 $r_i$ 我们很容易可以把它看成一个线段。

这时，我们可以把右端点从小到大贪心一下。

对于同样可以使用的豌豆射手，观察发现，选择攻击事件最近的豌豆射手更优，因为这样可以更灵活地干掉后面的僵尸，可以用 `multiset` 来维护。

Code:

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,ans;
multiset<int>s;//multiset维护上一次攻击时间最近的豌豆射手
struct no{
    int l,r;
}a[200010];
bool cmp(no x,no y){ 
    return x.r<y.r;//按右端点从小到大排序
}
int main(){
    multiset<int>::iterator it;
    cin>>n>>m;
    if(m>=n)return cout<<0,0;
    for(i=1;i<=n;i++)cin>>a[i].l>>a[i].r;
    sort(a+1,a+1+n,cmp);
    for(i=1;i<=n;i++){
        it=s.upper_bound(a[i].l);
        if(it!=s.begin()){
            it--;
            s.erase(it);
            s.insert(a[i].r);
        }
        else{
            if(s.size()+1>m)ans++;//打不死
            else s.insert(a[i].r);	
        }
    }
    cout<<ans;
}
```

---

