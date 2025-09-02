# Medium Design

## 题目描述

The array $ a_1, a_2, \ldots, a_m $ is initially filled with zeroes. You are given $ n $ pairwise distinct segments $ 1 \le l_i \le r_i \le m $ . You have to select an arbitrary subset of these segments (in particular, you may select an empty set). Next, you do the following:

- For each $ i = 1, 2, \ldots, n $ , if the segment $ (l_i, r_i) $ has been selected to the subset, then for each index $ l_i \le j \le r_i $ you increase $ a_j $ by $ 1 $ (i. e. $ a_j $ is replaced by $ a_j + 1 $ ). If the segment $ (l_i, r_i) $ has not been selected, the array does not change.
- Next (after processing all values of $ i = 1, 2, \ldots, n $ ), you compute $ \max(a) $ as the maximum value among all elements of $ a $ . Analogously, compute $ \min(a) $ as the minimum value.
- Finally, the cost of the selected subset of segments is declared as $ \max(a) - \min(a) $ .

Please, find the maximum cost among all subsets of segments.

## 说明/提示

In the first test case, there is only one segment available. If we do not select it, then the array will be $ a = [0, 0, 0] $ , and the cost of such (empty) subset of segments will be $ 0 $ . If, however, we select the only segment, the array will be $ a = [0, 1, 0] $ , and the cost will be $ 1 - 0 = 1 $ .

In the second test case, we can select all the segments: the array will be $ a = [0, 1, 2, 3, 2, 1, 0, 0] $ in this case. The cost will be $ 3 - 0 = 3 $ .

## 样例 #1

### 输入

```
6
1 3
2 2
3 8
2 4
3 5
4 6
6 3
1 1
1 2
1 3
2 2
2 3
3 3
7 6
2 2
1 6
1 2
5 6
1 5
4 4
3 6
6 27
6 26
5 17
2 3
20 21
1 22
12 24
4 1000000000
2 999999999
3 1000000000
123456789 987654321
9274 123456789```

### 输出

```
1
3
2
3
4
4```

# 题解

## 作者：LiJoQiao (赞：11)

upd on 2024.4.14：完善了翻译，重置了代码。  

[原题链接](https://codeforces.com/problemset/problem/1884/C) [洛谷题面](https://www.luogu.com.cn/problem/CF1884C) [提交记录](https://www.luogu.com.cn/record/155832709)  
### 题意简述  
>有一个长度为 $m$ 的数组 $a$ 和 $n$ 条线段，$a$ 初值为 $0$。  
>你可以选定线段的子集（可以为空），使得 $a$ 在每条线段覆盖的区间 $\left[l_i,r_i \right]$ 里的所有元素加 $1$。  
>求操作后数组的极差（最大值与最小值的差）最大是多少。  

### 题目分析  
假设我们进行操作后出现了一个最大值 $a_i$，观察可以发现覆盖 $a_i$ 的线段会有两种情况。  
1. 只增加 $a_i$ 的值。  
2. 同时增加 $a_i$ 和其他数的值。  

很容易发现当我们选定 $a_i$ 为最大值的时候，覆盖它的线段对极差是只增加不减少的（第一种情况会使得极差加 $1$，而第二种情况在不增加最小值的情况下会使极差加 $1$，增加最小值则使极差不变）。  

因此我们可以枚举每个数为最大值，只选择覆盖该数的线段，然后找到最小值更新答案。  

很明显题目 $m$ 的范围太大，但是 $n$ 的范围较小，于是我们需要将线段离散化。  
离散化也要将 $1$ 和 $m$ 加入进去将这个数组包裹起来，否则会漏掉两侧数组无线段覆盖但没有考虑到导致答案错误。  

到此为止得到一个时间复杂度为 $O(n^3)$ 的做法。  

考虑优化。  

#### 优化一：线段的遍历  
我们会发现每次遍历所有线段会很费时间，如果我们从 $a_1$ 开始有序考虑的话只需要添加刚好覆盖到的线段和删去刚好覆盖不到的线段会节省很多时间。  

我们可以将线段按照左端点排序，然后将添加进去的线段放入优先队列中，如果线段的右端点覆盖不到则删去并出队。  

#### 优化二：最小值的查询  
显然这个查询最小值就是区间加和查询的问题，我们可以用线段树维护。  

优化之后，时间复杂度变为 $O(n\log n)$。

代码如下。  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define lid (id<<1)
#define rid (id<<1|1)
#define mid ((l+r)>>1)
const int MAXN=1e5+10;
int lsh[MAXN<<1],chafen[MAXN<<1],a[MAXN<<1],n,m;
struct line{
	int l,r;
	bool operator<(const line x)const{
		return r>x.r;
	}
}li[MAXN];
struct linetree{
	int minv,lazy;
}lt[MAXN<<3];
int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x;
}
void buildtree(int id,int l,int r){
	lt[id].lazy=lt[id].minv=0;
	if(l==r)return;
	buildtree(lid,l,mid);buildtree(rid,mid+1,r);
}
void pushdown(int id){
	if(lt[id].lazy){
		lt[lid].lazy+=lt[id].lazy;lt[rid].lazy+=lt[id].lazy;
		lt[id].lazy=0;
		lt[id].minv=min(lt[lid].minv+lt[lid].lazy,lt[rid].minv+lt[rid].lazy);
	}
}
void pushup(int id){
	lt[id].minv=min(lt[lid].minv+lt[lid].lazy,lt[rid].minv+lt[rid].lazy);
}
void add(int id,int l1,int r1,int k,int l,int r){
	if(l==l1&&r==r1){
		lt[id].lazy+=k;
		return;
	}
	pushdown(id);
	if(r1<=mid)add(lid,l1,r1,k,l,mid);
	else if(l1>=mid+1)add(rid,l1,r1,k,mid+1,r);
	else{
		add(lid,l1,mid,k,l,mid);
		add(rid,mid+1,r1,k,mid+1,r);
	}
	pushup(id);
}
int query(int id,int l1,int r1,int l,int r){
	if(l1==l&&r1==r){
		return lt[id].minv+lt[id].lazy;
	}
	pushdown(id);
	if(r<=mid)return query(lid,l1,r1,l,mid);
	else if(l>=mid+1)return query(rid,l1,r1,mid+1,r);
	else return min(query(lid,l1,mid,l,mid),query(rid,mid+1,r1,mid+1,r));
}
bool cmp(line x,line y){
	return x.l<y.l;
}
int main(){
	int t=read();
	while(t){
		--t;
		priority_queue<line>q;
		memset(chafen,0,sizeof(chafen));
		n=read();m=read();
		int lshcnt=0;
		for(int i=1;i<=n;++i){
			lsh[++lshcnt]=li[i].l=read();
			lsh[++lshcnt]=li[i].r=read();
		}
		lsh[++lshcnt]=1;lsh[++lshcnt]=m;
		sort(lsh+1,lsh+lshcnt+1);
		int lshn=unique(lsh+1,lsh+lshcnt+1)-(lsh+1);
		for(int i=1;i<=n;++i){
			li[i].l=lower_bound(lsh+1,lsh+lshn+1,li[i].l)-lsh;
			li[i].r=lower_bound(lsh+1,lsh+lshn+1,li[i].r)-lsh;
			chafen[li[i].l]+=1;chafen[li[i].r+1]-=1;
		}
		for(int i=1;i<=lshn;++i){
			a[i]=a[i-1]+chafen[i];
		}
		buildtree(1,1,lshn);
		sort(li+1,li+1+n,cmp);
		int ans=0,p=1;
		for(int i=1;i<=lshn;++i){
			while(p<=n&&li[p].l<=i){
				add(1,li[p].l,li[p].r,1,1,lshn);
				q.push(li[p]);
				++p;
			}
			while(!q.empty()&&q.top().r<i){
				add(1,q.top().l,q.top().r,-1,1,lshn);
				q.pop();
			}
			ans=max(ans,a[i]-query(1,1,lshn,1,lshn));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：One_JuRuo (赞：6)

## 思路

### Step1. 贪心

拿到题后，第一时间想到贪心，如果这个区间加上会使答案变小或不变就不加。

但是很显然，这个贪心是错误的。

如果答案的最大值在区间 B，但是先加了区间 A，导致加区间 B 使答案不变，那么这样就会使答案变劣。

所以贪心是错误的。

### Step2. 枚举

接着，想到了可以枚举最小值，如果某个区间包含了这个最小值，那么这个区间加上后的答案一定是不优于不加上这个区间的答案，所以所有包含了这个最小值的区间都不需要加，那么再把所有最小值的答案取个最大值即可。

当然了，区间的值大，所以需要离散化。

有个巨佬朋友写过这种做法的[题解](https://www.luogu.com.cn/blog/makerY/cf1884c-medium-design-ti-xie)。

这里就不赘述了。

### Step3. 优化

事实上，最小值的选择的讨论是多余的，假设最小值选在 $x$ 点，那么所有横跨 $x$ 的区间都是无效的，那么可以对答案做出贡献的只有两个端点都在 $x$ 左侧或者都在右侧的区间才有用，那么假设最后的最大值在 $x$ 左侧，那么在 $x$ 右侧的区间无用，这样的话，把 $x$ 右移可以让区间变多或不变，那么答案将会变优或者不变，同理最大值在 $x$ 右侧也可以得到 $x$ 在左端点不劣。

总而言之就是，如果 $x$ 选在中间，那么答案一定不优于 $x$ 选择两端的情况。

所以我们只需要讨论两种情况即可。

所以如果一个区间左端点没有 $1$ 的话，就把这个区间加给第一组线段树。

如果一个区间右端点没有 $m$ 的话，就把这个区间加给第二组线段树。

注意：一个区间可以加给两个线段树。

那么最后的答案就是两组线段树维护的最大值的较大值。

同样地，需要离散化。

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct segtree
{
	struct node{int l,r,maxn,tag;}t[800005];
	inline void pushup(int p){t[p].maxn=max(t[p<<1].maxn,t[p<<1|1].maxn);}
	inline void addtag(int p,int k){t[p].maxn+=k,t[p].tag+=k;}
	inline void pushdown(int p){addtag(p<<1,t[p].tag),addtag(p<<1|1,t[p].tag),t[p].tag=0;}
	void build(int p,int l,int r)
	{
		t[p].l=l,t[p].r=r,t[p].maxn=t[p].tag=0;
		if(l==r) return;
		int mid=l+r>>1;
		build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	}
	void update(int p,int l,int r)
	{
		if(t[p].l>=l&&t[p].r<=r){addtag(p,1);return;}
		if(t[p].tag) pushdown(p);
		int mid=t[p].l+t[p].r>>1;
		if(mid>=l) update(p<<1,l,r);
		if(mid<r) update(p<<1|1,l,r);
		pushup(p);
	}
}t1,t2;
int T,n,m,l[200005],r[200005],a[400005],num;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i) scanf("%d%d",&l[i],&r[i]),a[i*2-1]=l[i],a[i*2]=r[i];a[n*2+1]=1,a[n*2+2]=m;
		sort(a+1,a+2*n+3),num=unique(a+1,a+2*n+3)-a-1;
		t1.build(1,1,num),t2.build(1,1,num);
		//cout<<num<<endl;
		for(int i=1;i<=n;++i)
		{
			l[i]=lower_bound(a+1,a+num+1,l[i])-a,r[i]=lower_bound(a+1,a+num+1,r[i])-a;
			if(l[i]!=1) t1.update(1,l[i],r[i]);
			if(r[i]!=num) t2.update(1,l[i],r[i]);
		}
		printf("%d\n",max(t1.t[1].maxn,t2.t[1].maxn));
	}
	return 0;
}

```

### Step4. 进一步优化

可以发现，只需要区间修改和一次区间查询，所以实际上可以直接使用差分数组进行维护，如果不算上离散化要用到的排序的话，时间复杂度更优，代码也更简单。

主要是因为前面的方法需要线段树，所以最开始没想到差分，辛辛苦苦写完了才发现根本不需要。

因为代码难度低，所以这里就不放差分版的代码了 ~~（绝对不是我懒得再写一个差分了）~~。

---

## 作者：xs_siqi (赞：6)

一个码量巨小，思路清晰，速度飞快的解法。

洛谷最优解第二。没加读优等常数优化。

一个错误的想法是，直接找每个点被覆盖了多少次，然后取被覆盖的最多的那个点。这个思路错在，有可能覆盖这个点的若干区间同时把整个区间覆盖了，导致最小值不为 $0$，难以统计最大值。

令整个区间的左端点为 $1$，右端点为 $m$。假如说有一个区间为 $[1,m]$，那么选择了这个区间就相当于没选择。因为最大值和最小值都增加了 $1$。

假如说有一个区间为 $[1,R]$，另一个为 $[L,m]$，且有 $L\leq R$，那么选择了这两个区间就相当于将答案的贡献增加了 $1$。因为区间 $[L,R]$ 增加 $2$ 的同时，最小值也增加了 $1$。

那么接下来不难想到以下这个思路：

我们把所有区间的左端点右端点和点 $1$ 和点 $m$ 全部离散化下来，然后直接枚举假设被覆盖次数最多的点是点 $x$，那么答案会是多少，然后直接取所有答案的最大值即可。

考虑如何计算每个点的答案。我们考虑把答案拆开来，一个点被覆盖后，答案就是它被所有区间覆盖的次数，减去整段区间被覆盖的次数。

前面这个“被所有区间覆盖的次数”我们可以简单差分一下解决。主要是考虑后面这个东西如何解决。不难想到我们可以维护一个，左端点为 $1$ 的所有线段，对右端点做一个前缀和，对右端点为 $m$ 的所有线段，对左端点做一个后缀和。然后被覆盖次数即是两个东西的最小值。当然你也可以写个双指针啥的吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+5;
int t,n,m,k,ans,b[maxn],cntl[maxn],cntr[maxn];
int vis[maxn];
struct node{int l,r;}a[maxn];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&a[i].l,&a[i].r),
			b[i*2-1]=a[i].l,b[i*2]=a[i].r;
		b[2*n+1]=1,b[2*n+2]=k;
		sort(b+1,b+2*n+3);
		m=unique(b+1,b+2*n+3)-b-1;
		for(int i=1;i<=n;i++)
			a[i].l=lower_bound(b+1,b+m+1,a[i].l)-b， 
			a[i].r=lower_bound(b+1,b+m+1,a[i].r)-b;
		k=lower_bound(b+1,b+m+1,k)-b;
		for(int i=1;i<=n;i++)
			vis[a[i].l]++,vis[a[i].r+1]--;
		for(int i=1;i<=k;i++)
			vis[i]=vis[i]+vis[i-1];
		for(int i=1;i<=n;i++){
			if(a[i].l==1)cntr[a[i].r]++;
			if(a[i].r==k)cntl[a[i].l]++;
		}
		for(int i=k;i>=1;i--)cntr[i]+=cntr[i+1];
		for(int i=1;i<=k;i++)cntl[i]+=cntl[i-1];
		for(int i=1;i<=k;i++)
			ans=max(ans,vis[i]-min(cntr[i],cntl[i]));
		printf("%d\n",ans);
		for(int i=1;i<=k+1;i++)cntl[i]=cntr[i]=vis[i]=0;
		for(int i=1;i<=n;i++)a[i].l=a[i].r=0;
		for(int i=1;i<=m;i++)b[i]=0;
		ans=0,m=0;
	}
	return 0;
}
```


---

## 作者：0000pnc (赞：5)

考虑你已经选了若干个区间，那么如果此时再选一个覆盖了所有最小值的区间，这是一定不优的。证明显然，因为最小值增加了 $1$，而最大值增加的不会比 $1$ 大，所以这个区间不如不选。

于是我们什么都不选开始考虑。如果这个时候有一个区间覆盖了所有的 $0$，那么你一定不会选它。

所以最优的方案肯定是留着一个 $0$，然后把与这个位置不交的所有区间全部选上。那么就可以对所有区间离散化后进行扫描线，然后用一个线段树维护区间加，全局 $\max$ 操作即可。

时间复杂度 $\mathcal{O}(n\log n)$。

下面是赛时代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int T, n, m, l[200005], r[200005], id[200005], id2[200005], tmp[400005];
long long ans;
bool cmp1(int x, int y) { return l[x] < l[y]; }
bool cmp2(int x, int y) { return r[x] < r[y]; }
 
#define lson (id << 1)
#define rson (id << 1 | 1)
struct sgt {
	int mx[1700005], lz[1700005];
	void init() { for (int i = 1; i <= (n << 4) + 20; i++) mx[i] = lz[i] = 0; }
	void pushup(int id) { mx[id] = max(mx[lson], mx[rson]); }
	void pushdown(int id) {
		if (lz[id]) {
			lz[lson] += lz[id]; lz[rson] += lz[id];
			mx[lson] += lz[id]; mx[rson] += lz[id];
		}
		lz[id] = 0;
	}
	void change(int l, int r, int id, int x, int y, int v) {
		if (l >= x && r <= y) {
			mx[id] += v; lz[id] += v;
			return;
		}
		pushdown(id);
		int mid = (l + r) >> 1;
		if (x <= mid) change(l, mid, lson, x, y, v);
		if (y > mid) change(mid + 1, r, rson, x, y, v);
		pushup(id);
	}
} t;
 
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		t.init();
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &l[i], &r[i]);
			tmp[(i << 1) - 1] = l[i], tmp[(i << 1)] = r[i];
			id[i] = id2[i] = i;
		} tmp[(n << 1) + 1] = 1, tmp[(n << 1) + 2] = m;
		sort(tmp + 1, tmp + (n << 1) + 3);
		int len = unique(tmp + 1, tmp + (n << 1) + 3) - tmp - 1;
		for (int i = 1; i <= n; i++) {
			l[i] = lower_bound(tmp + 1, tmp + len + 1, l[i]) - tmp;
			r[i] = lower_bound(tmp + 1, tmp + len + 1, r[i]) - tmp;
			t.change(1, len, 1, l[i], r[i], 1);
		}
		sort(id + 1, id + n + 1, cmp1);
		sort(id2 + 1, id2 + n + 1, cmp2);
		int cur1 = 1, cur2 = 1, ans = 0;
		for (int i = 1; i <= len; i++) {
			while (cur1 <= n && l[id[cur1]] <= i) {
				t.change(1, len, 1, l[id[cur1]], r[id[cur1]], -1);
				cur1++;
			}
			while (cur2 <= n && r[id2[cur2]] < i) {
				t.change(1, len, 1, l[id2[cur2]], r[id2[cur2]], 1);
				cur2++;
			}
			ans = max(ans, t.mx[1]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：Louis_lxy (赞：3)

一个思路简单的做法。

显然我们可以对每个线段用差分进行填充，然后枚举每个点并删除不需要的线段。

但是此时复杂度是 $O(n^2)$ 的，考虑优化。我们可以考虑处理哪些是无需的线段。

发现这样并不好处理，于是我们考虑线段重合的本质。

如果有两个线段重合了，且两端都连着整个区间的两端，显然就相当于增加了重合的部分，因为其他的部分抵消了。

此时我们就能想到一个思路，答案就是当前点被所有线段覆盖的次数剪掉整个区间被覆盖的次数。

当前点被覆盖的次数刚刚已经讲过了，接下来考虑如何计算整个区间被覆盖的次数。

注意覆盖这整个区间并覆盖了当前点有两种方案，要么就是前面一串加上中间的一串线段或者后面一串加上中间的一串线段。我们可以直接对所有连接着整个区间右端点的线段的左端点开一个桶存，然后用前缀和统计一下，对于连着区间左端点的线段的右端点开一个桶存下来并用后缀和维护。或者也可以排序后用双指针维护上述的东西。

注意数据范围，发现我们无法直接开桶。但是只要对所有点离散化一下就可以了。

AC 记录：https://www.luogu.com.cn/record/168679851

---

## 作者：_O_v_O_ (赞：3)

首先，设 $x=\max(a)$ 的下标，$y=\min(a)$ 的下标。

我们来讨论哪些线段应该被加上：

- 这条线段穿过 $x$ 不穿过 $y$：要加。
- 这条线段穿过 $y$ 不穿过 $x$：不加。
- 这条线段穿过 $x$ 和 $y$：可以不加。
- 这条线段没有穿过 $x$ 和 $y$：可以加。

综上，可以得出一个结论：在一条线段穿过 $y$ 时，不能加，否则可以加。

现在这个问题就变成了一个确定 $x,y$ 的问题：

首先，$y$ 只可能是 $1$ 或 $n$，因为这样才能让中间的影响 $y$ 的次数最小。

然后根据上述结论，所有没有覆盖 $y$ 的线段都能被选，所以分开讨论在更新答案即可。

区间覆盖的过程就可以用差分来解。

因为 $m$ 有点大，所以还要离散化。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1e5+5;
int T,n,m,mx;
struct seg{
	int l,r;
}s[N];
set<int> st;
map<int,int> mp;
int cf[N*2];

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>T;
	while(T--){
		mx=0;
		st.clear();
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>s[i].l>>s[i].r;
			st.insert(s[i].l),st.insert(s[i].r);
		}
		st.insert(1),st.insert(m);
		set<int>::iterator it;
		int xx=0;
		for(it=st.begin();it!=st.end();it++){
			mp[*it]=++xx;
		}
		m=xx;
		for(int i=1;i<=n;i++){
			s[i].l=mp[s[i].l],s[i].r=mp[s[i].r];
		}
      //离散化
		fill(cf+1,cf+m+1,0);
		for(int i=1;i<=n;i++){
			if(s[i].l==1) continue;
			cf[s[i].l]++;
			cf[s[i].r+1]--;
		}
      //差分
		for(int i=1;i<=m;i++){
			cf[i]+=cf[i-1];
			mx=max(mx,cf[i]);
		}
		fill(cf+1,cf+m+1,0);
		for(int i=1;i<=n;i++){
			if(s[i].r==m) continue;
			cf[s[i].l]++;
			cf[s[i].r+1]--;
		}
		for(int i=1;i<=m;i++){
			cf[i]+=cf[i-1];
			mx=max(mx,cf[i]);
		}
		cout<<mx<<'\n';
	}
	return 0;
}

```


---

## 作者：jiazhichen844 (赞：2)

# 题意
有一个区间集合 $S=\{[l_1,r_1],[l_2,r_2],\cdots,[l_n,r_n] \}$，定义一个集合 $S' \subseteq S$ 的价值如下计算：

一个长度为 $m$，初始全为 $0$ 的数组 $a$，依次遍历 $S'$ 里的所有区间，将 $a$ 的第 $l_i$ 至 $r_i$ 位置上的数全 $+1$ ，最后的价值为 $\max(a)-\min(a)$。

现在，你需要选出一个集合 $T \subseteq S$，使得 $T$ 的价值最大，输出这个最大的价值。

$t$ 组数据，$t \le 10^4,n \le 10^5,\sum n \le 2 \times 10^5,1 \le l_i \le r_i \le m \le 10^9$
# 思路
## 思路 0：线段树
我不会啊！去看其他题解吧。
## 思路 1：赛时贪心
看到 $\max(a)-\min(a)$ 以及 $O(n^2)$ 会挂的复杂度，就可以考虑枚举一个，维护另一个的最优值。

易证一定存在 $\max(a)$ 的位置为某一区间的端点，枚举此位置为 $x$。
现在只需要求 $a_x-\min(a)$ 的最大值即可。

重要结论：我们选出的 $T$ 一定有 $T=\{[l_i,r_i]\in S | l_i \le x \le r_i\}$。

证明：令 $S_x=\{[l_i,r_i]\in S | l_i \le x \le r_i\}$，考虑 $T$ 比 $S_x$ 多出的元素，它不会使 $a_x$ 变大，答案一定不会变优,再考虑 $T$ 比 $S_x$ 少的元素，$a_x$ 一定被减少 $1$，$\min(a)$ **最多**减少 $1$,答案也不会变优。

综上 $T=S_x=\{[l_i,r_i]\in S | l_i \le x \le r_i\}$。

还有一个结论：由上面所述的 $T=S_x$，$\min(a)=\min(a_1,a_m)$，这个易证。

于是，我们把线段按 $l_i$ 从小到大排序，再维护一个以 $r_i$ 为关键字，从小到大的堆，来维护目前合法的线段。

从左往右依次扫所有合法的 $\max(a)$ 的位置，每次扫到一个 $x$，就将所有 $l_i=x$ 的线段插进堆里，再将堆中所有 $r_i<x$ 的线段弹出，同时，实时在插入和删除时维护 $a_1$ 与 $a_m$，此时答案即为堆的大小减 $\min(a_1,a_m)$。

更新最大值即可。
# code
赛时代码，不经修改
```cpp
#include<bits/stdc++.h>
using namespace std;
struct q
{
	int l,r;
	bool operator < (const q a) const
	{
		return r>a.r;
	}
}a[100005];
bool cmp(q a,q b)
{
	return a.l<b.l;
}
int d[200005];
void test()
{
	int n,m;
	cin>>n>>m;
	int t1=0,tm=0;
	for(int i=1;i<=n;i++)
		cin>>a[i].l>>a[i].r,d[2*i-1]=a[i].l,d[i+i]=a[i].r;
	sort(a+1,a+n+1,cmp);
	priority_queue<q> q;
	sort(d+1,d+2*n+1);
	a[n+1].l=m+1;
	int pos=1; 
	int maxn=0;
	for(int i=1;i<=2*n;i++)
	{
		if(d[i]==d[i-1])
			continue;
		while(a[pos].l<=d[i])
		{
			if(a[pos].l==1)
				t1++;
			if(a[pos].r==m)
				tm++;
			q.push(a[pos]);
			pos++;
		}
		while(!q.empty()&&q.top().r<d[i])
		{
			if(q.top().l==1)
				t1--;
			if(q.top().r==m)
				tm--;
			q.pop();
		}
		maxn=max(maxn,(int)q.size()-min(t1,tm));
	}
	cout<<maxn<<endl;
}
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
		test(); 
}
```

---

## 作者：Diaоsi (赞：1)

[Medium Design](https://codeforces.com/contest/1884/problem/C)

提供一个正解，首先将所有的区间端点离散化（为了保证合法性，区间端点旁边的点也需要离散化），然后单独考虑每个位置 $p\ \left(1\leq p \leq m\right)$ 是否会成为出现最大值的地方。

我们可以考虑把所有包含 $p$ 的区间都进行加一操作，并且注意到最小值只可能在 $1$ 或 $m$ 的位置出现，为什么这个做法是正确的呢？

考虑把包含 $p$ 的区间全部进行加一操作的过程，如果这个区间的左右端点同时不为 $1$ 和 $m$，则该区间对答案一定有正向的贡献（因为 $1$ 和 $m$ 不变而 $p\leftarrow p+1$ ）。

而若这个区间的左右端点为 $1$ 或 $m$，答案只可能加一或者不变，不会变得更劣。

于是我们可以使用线段树分治来维护对所有包含 $p$ 的区间都进行加一操作的过程，具体操作就是在线段树的每个节点都开个 ```std::vector```，然后把每个区间挂在对应的 $\log n$ 个 ```std::vector``` 里。

在分治的过程中统计当前的加入的区间数作为最大值，而 $1$ 和 $m$ 被覆盖的次数的最小值作为最小值，遍历到叶子节点时统计答案即可，时间复杂度 $\mathcal{O(n\log n)}$。

```Code:```

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll N=1000010,M=2000010,INF=0x3f3f3f3f;
inline ll max(ll x,ll y){return x>y?x:y;}
inline ll min(ll x,ll y){return x<y?x:y;}
inline void swap(ll &x,ll &y){x^=y^=x^=y;}
ll T,n,m,ans,cnt[3],b[N<<2];
struct rec{ll l,r;}q[N];
vector<rec> h[N<<2];
struct SegmentTree{
	ll l,r;
	#define l(x) tree[x].l
	#define r(x) tree[x].r
}tree[N<<2];
void build(ll x,ll l,ll r){
	l(x)=l,r(x)=r;
	h[x].clear();
	if(l==r)return;
	ll mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
}
void insert(ll x,ll L,ll R,rec t){
	ll l=l(x),r=r(x);
	if(L<=l&&r<=R){h[x].push_back(t);return;}
	ll mid=(l+r)>>1;
	if(L<=mid)insert(x<<1,L,R,t);
	if(R>mid)insert(x<<1|1,L,R,t);
}
void upd(ll x,ll op){
	cnt[0]+=op*h[x].size();
	for(rec z:h[x])cnt[1]+=op*(z.l==1),cnt[2]+=op*(z.r==m);
}
void query(ll x){
	ll l=l(x),r=r(x);
	upd(x,1);
	if(l==r)ans=max(ans,cnt[0]-min(cnt[1],cnt[2]));
	else query(x<<1),query(x<<1|1);
	upd(x,-1);
}
int main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%lld%lld",&n,&m);
		ll tot=0;ans=0;
		for(ll i=1;i<=n;i++){
			scanf("%lld%lld",&q[i].l,&q[i].r);
			b[++tot]=q[i].l;b[++tot]=q[i].r;
			if(q[i].l>1)b[++tot]=q[i].l-1;
			if(q[i].l<m)b[++tot]=q[i].l+1;
			if(q[i].r>1)b[++tot]=q[i].r-1;
			if(q[i].r<m)b[++tot]=q[i].r+1;
		}
		sort(b+1,b+tot+1);
		m=unique(b+1,b+tot+1)-b-1;
		build(1,1,m);
		for(ll i=1;i<=n;i++){
			q[i].l=lower_bound(b+1,b+m+1,q[i].l)-b;
			q[i].r=lower_bound(b+1,b+m+1,q[i].r)-b;
			insert(1,q[i].l,q[i].r,q[i]);
		}
		query(1);
		printf("%lld\n",ans);
	}
	return 0;
}
```




---

## 作者：makerY (赞：1)

一道不错的用线段树考虑贡献的题。

这里提供一种和官方题解思路不太一样的方法。

## 简要题意

给定 $n$ 个区间，和一个长度为 $m$ 且初始值全部为 $0$ 的序列，任选其中的一些区间，在序列中进行区间加 $1$ 操作，要使操作后序列的最大值与最小值之差最大，求出这个最大的差值。

## 思路

如果操作后最大值和最小值的位置确定，考虑每个区间，发现只有**仅覆盖了最大值的区间**会对答案产生贡献，其他区间（即**覆盖了最小值**的区间）则不用考虑，故可以反过来枚举所有最小值可能在的位置，对于每一个最小值的位置，可能的答案就是所有**未覆盖该位置的区间**进行区间加 $1$ 后得到的序列里的最大值（即把最小值当成 $0$ 考虑，每次区间加如果加到了最小值上一定不会使答案变大，故直接不考虑覆盖了最小值的区间），最后答案就是所有最大值里取最大。

显然这是个 RMQ 问题，用线段树维护。但每次枚举最小值直接暴力区间修改不覆盖最小值的区间复杂度无法接受，所以可以换一下思路，先把所有区间都覆盖一遍，然后从左到右枚举最小值的时候考虑每个区间的贡献：枚举到点 $i$ 时，对于所有左端点在 $i$ 的区间进行区间减 $1$，即这些区间**会覆盖** $i$ 及后面的一些位置，对于这些位置需要**消除**掉覆盖它们的区间的影响；同理，对于所有右端点在 $i$ 的区间进行区间加 $1$，**加入**这些区间对后面位置的影响（注意实现时加入影响的操作要在得到该位置的答案之后，因为该位置还在这些区间内，不能被这些区间贡献）。实现时只需要把区间分别挂到其左右端点上，用两个 vector 数组存即可（详见代码）。

还需要注意的一点，由于区间范围很大，需要离散化，离散化之后会使原本不相邻的两个区间变成相邻的，这会漏掉一些情况，当然可以人为在离散化对不相邻的区间之间增加一个位置，但实现起来稍微有点麻烦，而可以发现这道题如果存在**不相邻的区间**，就意味着序列的最小值一定是 $0$，答案就是对全部区间进行区间加以后的最大值，只需特判即可（注意序列最左边或最右边没被覆盖的情况需要单独考虑）。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500010;

struct Seg{int l,r;}seg[N];
bool cmp(Seg a,Seg b){return a.l==b.l?a.r<b.r:a.l<b.l;}
struct Node{int ma,tag;}tr[N<<2];
vector<int> dl[N],dr[N];//分别存左、右端点在 i 的区间编号 

inline void pushup(int p){tr[p].ma=max(tr[p<<1].ma,tr[p<<1|1].ma);}
inline void addtag(int p,int d){tr[p].tag+=d,tr[p].ma+=d;}
inline void pushdown(int p)
{
	if(tr[p].tag)
	{
		addtag(p<<1,tr[p].tag),addtag(p<<1|1,tr[p].tag);
		tr[p].tag=0;
	}
}
void build(int p,int pl,int pr)//只是方便对整棵树清零 
{
	tr[p].ma=tr[p].tag=0;
	if(pl==pr) return;
	int mid=pl+pr>>1;
	build(p<<1,pl,mid),build(p<<1|1,mid+1,pr);
}
void update(int p,int pl,int pr,int L,int R,int d)
{
	if(L<=pl&&pr<=R)
	{
		addtag(p,d);
		return;
	}
	pushdown(p);
	int mid=pl+pr>>1;
	if(mid>=L) update(p<<1,pl,mid,L,R,d);
	if(mid<R) update(p<<1|1,mid+1,pr,L,R,d);
	pushup(p);
}

int t,m,n,a[N];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int res=0;
		bool k=0,ll=1,rr=1;//k:是否存在不连续的区间，ll:最左边没有被覆盖，rr:最右边没有被覆盖 
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i) 
			scanf("%d%d",&seg[i].l,&seg[i].r),a[(i-1)*2+1]=seg[i].l,a[(i-1)*2+2]=seg[i].r,rr&=(seg[i].r<m),ll&=(seg[i].l>1);
		
		k=(ll||rr);//只要两边有空着的就计入特判的情况 
		sort(seg+1,seg+1+n,cmp);//对区间排序，方便判断是否存在没有被任何一个区间覆盖的位置 
		int rmax=1; 
		for(int i=1;i<=n;++i)
		{
			if(seg[i].l>rmax+1) k=1;//左边的区间最右的端点也与目前左端点间隔了距离 ，即找到了一个没有被任何区间覆盖的位置 
			while(seg[i].l==seg[i+1].l) ++i;//左端点相同的区间找到右端点最右的一个（已经按右端点为第二关键字排序） 
			rmax=max(rmax,seg[i].r);//更新左边区间最右端点的位置，注意一定要取max，因为左端点更靠右的区间右端点可能反而小 
		}
		
		//离散化 
		sort(a+1,a+1+2*n);		
		int cnt=unique(a+1,a+1+2*n)-(a+1);	
			
		//多测清空 
		build(1,1,cnt); 
		for(int i=1;i<=cnt;++i) dl[i].clear(),dr[i].clear();
		
		//离散化后重新赋值，顺便把所有区间进行覆盖，和记录左右端点位置对应的区间编号 
		for(int i=1;i<=n;++i)
			seg[i].l=lower_bound(a+1,a+1+cnt,seg[i].l)-a,seg[i].r=lower_bound(a+1,a+1+cnt,seg[i].r)-a,
			update(1,1,cnt,seg[i].l,seg[i].r,1),dl[seg[i].l].push_back(i),dr[seg[i].r].push_back(i);
		
		if(k){printf("%d\n",tr[1].ma);continue;}//特判存在没有被任何区间覆盖的位置的情况
		
		for(int i=1;i<=cnt;++i)
		{
			for(auto j:dl[i]) update(1,1,cnt,seg[j].l,seg[j].r,-1);//消除覆盖了这个位置的区间的影响 
			res=max(res,tr[1].ma);//更新最大的答案 
			for(auto j:dr[i]) update(1,1,cnt,seg[j].l,seg[j].r,1);//加上没有覆盖这个位置的区间的影响，注意该操作要在更新答案之后 
		}
		printf("%d\n",res);
	}
	return 0;
}
```

[一个朋友的另一种做法](https://www.luogu.com.cn/blog/AuroraWind/cf1884c-medium-design)

---

## 作者：WaterSun (赞：0)

# 思路

假设最后最大值的位置为 $x$，最小值的位置为 $y$。

那么将所有满足 $l_i \leq y \leq r_i$ 的线段选出来一定不优。

因为如果 $x < l_i \vee x > r_i$ 会使答案减 $1$；如果 $l_i \leq x \leq r_i$ 会使答案不变。

考虑 $y$ 的移动对答案的影响。

如果 $x < y$，那么 $y$ 右移一定不会使答案变劣；反之，如果 $x > y$，那么 $y$ 左移一定不会使答案变劣。

所以最后 $y$ 的取值一定会是 $1$ 或 $m$。

将两种情况分别计算一下即可。对于计算的时候由于是静态的问题，可以直接先离散化，然后套一个差分即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 2e5 + 10;
int T,n,m;
int arr[N];

struct sec{
	int l,r;
}s[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

inline void solve(){
	int ans = 0;
	vector<int> p;
	n = read();
	m = read();
	for (re int i = 1;i <= n;i++){
		s[i].l = read();
		s[i].r = read();
		p.push_back(s[i].l);
		p.push_back(s[i].r + 1);
	}
	sort(p.begin(),p.end());
	unique(p.begin(),p.end());
	for (re int i = 1;i <= 2 * n;i++) arr[i] = 0;
	for (re int i = 1;i <= n;i++){
		if (s[i].l > 1){
			int l = lower_bound(p.begin(),p.end(),s[i].l) - p.begin() + 1;
			int r = lower_bound(p.begin(),p.end(),s[i].r + 1) - p.begin() + 1;
			arr[l]++;
			arr[r]--;
		}
	}
	for (re int i = 1;i <= 2 * n;i++){
		arr[i] += arr[i - 1];
		ans = max(ans,arr[i]);
	}
	for (re int i = 1;i <= 2 * n;i++) arr[i] = 0;
	for (re int i = 1;i <= n;i++){
		if (s[i].r < m){
			int l = lower_bound(p.begin(),p.end(),s[i].l) - p.begin() + 1;
			int r = lower_bound(p.begin(),p.end(),s[i].r + 1) - p.begin() + 1;
			arr[l]++;
			arr[r]--;
		}
	}
	for (re int i = 1;i <= 2 * n;i++){
		arr[i] += arr[i - 1];
		ans = max(ans,arr[i]);
	}
	printf("%d\n",ans);
}

int main(){
	T = read();
	while (T--) solve();
	return 0;
}
```

---

## 作者：__CrossBow_EXE__ (赞：0)

# 前言

趁没人刷题解水一发。

我对此题的评判如下：

- 建议升蓝；
- 建议加上标签“排序”、“双指针”、“线段树”。

# 大意

翻译已经很明确了，这里不过多说明。

# 思路

我们假设最优答案中，数组 $a$ 中最大元素的位置为 $i$。因此，我们可以选择 $l \leq i \leq r$ 所在的所有线段，因为如果最小元素的位置在该线段之外，我们就会将答案增加 $+1$；如果在该线段之内，我们就不会使答案更加复杂。所以，最小值要么出现在位置 $1$ 处，要么出现在位置 $m$ 处。然后，我们可以考虑不包含位置 $1$ 的线段（或考虑 $m$ 的线段），找出被最多这样的线段覆盖的位置。其次，线段 $(l, r)$ 对应两个事件：线段打开为 $(l, 0)$ ，线段关闭为 $(r, 1)$。我们对这些事件进行排序和遍历，记录每个时刻打开的线段数量,最后输出这些数量中的最大值即可。

# 代码

作者打上面的字太累了，不准备写代码了……

---

