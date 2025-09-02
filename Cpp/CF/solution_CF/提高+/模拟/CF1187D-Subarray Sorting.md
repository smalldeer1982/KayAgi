# Subarray Sorting

## 题目描述

给定一个数组 $a_1, a_2, \dots, a_n$ 和一个数组 $b_1, b_2, \dots, b_n$。

每次操作，你可以将数组 $a$ 的任意一个子数组 $a[l \dots r]$ 按非递减顺序排序。

例如，如果 $a = [4, 2, 2, 1, 3, 1]$，你选择子数组 $a[2 \dots 5]$，那么数组会变成 $[4, 1, 2, 2, 3, 1]$。

请你判断，是否可以通过若干次（可以为零次）上述操作，将数组 $a$ 变成数组 $b$。

## 说明/提示

在第一个测试用例中，可以先将子数组 $a_1 \dots a_5$ 排序，此时 $a$ 变为 $[1, 1, 4, 4, 7, 5, 6]$，然后再将子数组 $a_5 \dots a_6$ 排序。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
7
1 7 1 4 4 5 6
1 1 4 4 5 7 6
5
1 1 3 3 5
1 1 3 3 5
2
1 1
1 2
3
1 2 3
3 2 1
```

### 输出

```
YES
YES
NO
NO
```

# 题解

## 作者：mrsrz (赞：19)

要求$a$和$b$对应位置相等，则每种元素的出现次数也要相等，这个直接判掉。

我们每次只对长度为2的区间排序（即选择相邻的两个数，小的放左边，大的放右边），这样也是可以达到相同的效果（冒泡排序的原理）。

考虑从$a_1\sim a_n$依次确定为正确的值。

假设当前考虑的是$a_i$，前面$i-1$个已经正确对应。

我们在位置$i$后面找到第一个等于$b_i$的元素$a_j$，并考虑把它交换到$a_i$位置。不难发现，当且仅当$a_i\sim a_{j-1}$都大于$a_j$的值的时候，才有可能交换过来。并且交换是不改变其他元素的相对顺序的。由于我们每次都是把后面某个元素换到最前面，所以这里的$a_i\sim a_j$在最原始的数组中也是按照这样的相对顺序排列的。也就是说，我们在把一个元素移动到前面的时候，它对后面就没有任何影响了，因此可以直接删除。

那么我们相当于做这样一个过程：

从小到大枚举$i$，在$a$中找到$b_i$下一次出现的位置$p$，判断$a_p$是不是$a_1\sim a_p$中的最小值。如果不是则输出NO。然后把$a_p$改成无穷大（相当于删除了这个元素）。

用线段树进行单点修改、区间最值的维护即可。

时间复杂度$O(n\log n)$。

## Code：
```cpp
#include<cstdio>
#include<queue>
const int N=3e5+6;
int T,n,a[N],b[N],tot[N],pos[N];
std::queue<int>q[N];
int d[N<<2];
void build(int l,int r,int o){
	if(l==r)d[o]=a[l];else{
		const int mid=l+r>>1;
		build(l,mid,o<<1),build(mid+1,r,o<<1|1);
		d[o]=std::min(d[o<<1],d[o<<1|1]);
	}
}
int query(int l,int r,int o,const int&L,const int&R){
	if(L<=l&&r<=R)return d[o];
	const int mid=l+r>>1;
	if(L<=mid&&mid<R)return std::min(query(l,mid,o<<1,L,R),query(mid+1,r,o<<1|1,L,R));
	if(L<=mid)return query(l,mid,o<<1,L,R);return query(mid+1,r,o<<1|1,L,R);
}
void modify(int l,int r,int o,const int&pos){
	if(l==r)d[o]=9999999;else{
		const int mid=l+r>>1;
		if(pos<=mid)modify(l,mid,o<<1,pos);else modify(mid+1,r,o<<1|1,pos);
		d[o]=std::min(d[o<<1],d[o<<1|1]);
	}
}
int main(){
	for(scanf("%d",&T);T--;){
		scanf("%d",&n);
		for(int i=1;i<=n;++i)tot[i]=0;
		for(int i=1;i<=n;++i)scanf("%d",a+i),++tot[a[i]];
		for(int i=1;i<=n;++i)scanf("%d",b+i),--tot[b[i]];
		int ok=1;
		for(int i=1;i<=n&&ok;++i)if(tot[i]){
			puts("NO");ok=0;
		}
		if(!ok)continue;
		for(int i=1;i<=n;++i)
		q[a[i]].push(i);
		for(int i=1;i<=n;++i)pos[i]=q[b[i]].front(),q[b[i]].pop();
		build(1,n,1);
		for(int i=1;i<=n&&ok;++i){
			if(query(1,n,1,1,pos[i])!=b[i])ok=0;
			modify(1,n,1,pos[i]);
		}
		puts(ok?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：肖然 (赞：7)

### 题意
给2个长度=N的序列a,b，每次操作可以将a的连续子序列[l,r]排序。问能否通过若干次操作使序列a变为序列b。
多组询问。


### 题解
转化：将"子序列`[l,r]`排序" -> 若干`len=2`的操作 -> 通过相邻swap消除掉`[l,r]`中所有逆序对

观察到操作"不会产生新的逆序对"，即ans=`yes`的**必要条件**是"没有新的逆序对"。

设`pos[b[i]]` = `b[i]`在`a`序列中的位置。

即对于`b`序列中的所有元素`b[i]`：不存在`j`满足`j<i且b[j]>b[i]且pos[b[j]]>pos[b[i]]`
  
那么：`max{pos[b[j]]|j<i, b[j]>b[i]} < pos[b[i]]`，转化成二维偏序上的最值问题，单点修改后缀求max，可以使用线段树维护。

这个条件的**充分性**可以考虑从小到大加入所有元素，用归纳法证明。


```cpp
#include<bits/stdc++.h>
#define MAXN 300005
#define LL long long
#define P int(1e4+7)
using namespace std;
 
int N;
 
int a[MAXN], b[MAXN];
 
vector<int> adj[MAXN];//存i中下标，维护pos[]信息
 
//segTree
 
struct Node{
	int l,r,d;
	Node *ls, *rs;
	
	void update(){
		d = max(ls->d, rs->d);
	} 
} pool[3*MAXN], *rt;
 
int top = 0;
 
Node* buildT(int l, int r){
	Node* p = pool + (++top);
	p->l = l; p->r = r;
	p->d = 0;
	if(l==r) return p;
	
	int mid = (l + r)/2;
	p->ls = buildT(l, mid);
	p->rs = buildT(mid+1,r);
	
	return p;
}
 
void change(Node* p, int id, int x){
	if(p->l==id && p->r==id){
		p->d = x;
		return;
	}
	
	int mid = (p->l + p->r)/2;
	if(id <= mid) change(p->ls, id, x);
	else change(p->rs, id, x);
	
	p->update();
}
 
int query(Node* p, int l, int r){
	if(l > r) return 0;
	if(p->l==l && p->r==r){
		return p->d;
	}
	
	int mid = (p->l + p->r)/2;
	if(r <= mid) return query(p->ls, l, r);
	else if(l >= mid+1) return query(p->rs, l, r);
	else return max(query(p->ls, l, mid), query(p->rs, mid+1, r));
}
 
//segTree End
 
int cnt[MAXN];
 
bool chk(){
	int x;
	for(int i=1;i<=N;i++){
		x = a[i];
		adj[x].push_back(i);
	}
	
	int pos;
	for(int i=1;i<=N;i++){
		x = b[i];
		if(++cnt[x] > adj[x].size()) return 0;
		else pos = adj[x][cnt[x]-1];
 
		if(query(rt,x+1,N) > pos) return 0;
		change(rt, x, pos);
	}
	return 1;
}
 
int main(){
	ios::sync_with_stdio(0);
	int T;
	cin>>T;
	
	while(T--){
		cin>>N;
		for(int i=1;i<=N;i++) cin>>a[i];
		for(int i=1;i<=N;i++) cin>>b[i];
		
		//init
		
		top = 0;
		rt = buildT(1,N);
		for(int i=1;i<=N;i++){
			adj[i].clear();
			cnt[i] = 0;
		}
 
		if(chk()) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
 
	return 0;
}

```



---

## 作者：DPair (赞：5)

### 敢问这题真的难吗？
废话不多说了。。。
## 【思路】
还是可以想的，明显是$O(nlogn)$的复杂度，而且很想逆序对和其他一些倾向于数学题的建模题，于是考虑对这道题中所给操作的一些性质。

## 【性质】
### 性质1·我要往前走！
我们可以发现，序列$A$变成$B$时，如果我们从$B_1$开始往后遍历，会发现我们肯定是通过把$A$中对应的数往前移动完成变化的，比如$A_i \neq B_i$时，且$A_k = B_i$，如果前面的数已经全部一一匹配，那我们就不用考虑这些数（即$A_1 = B_1 ...... A_{i-1} = B_{i-1}$），说明$k > i$，所以要“往前走”。

### 性质2·我要比你小！
如果一个数的前面（未匹配部分）有比它小的数，那么它一定不能和自己要对应的数匹配，为什么呢？因为我们是通过排序位移数字的。所以，当我们的一个数大于前面某个数时，这两个数的顺序就无法改变了。比如：
$$\{1,2,5,4,3\}$$
中，$5$、$4$、$3$就不可能到$1$、$2$所在的位置，但是$4$可以向前换到$5$的位置。
（自己理解）

### 性质3·我们要一样！
这一条好理解的。$A$能变成$B$，必要条件之一是$A$中所有数字个数与$B$中所有数字个数完全相同（~~就是质量守恒~~）

## 【算法】
然后就简单了。

根据以上性质，我们容易看出要这么做：

对于每组数据。

我们先存$A$中每一个数的所有位置（爱用链表用链表，我用的$vector$）。

然后看$B$可不可以匹配就行了。从$B_1$开始往后扫，找$B_i$在$A$中**没有被匹配过的最前面的位置**，然后找这之前**没有被使用的**最小值，比较$B_i$与这个最小值的大小就可以判断出是否要输出$NO$（~~一氧化氮~~）了。这里由于是在线的，用线段树维护（还不用打标记）。

## 【代码】
```cpp
//Frame_mzq
#include <bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x)
{
    char c;
    x = 0;
    int fu = 1;
    c = getchar();
    while(c > 57 || c < 48)
    {
        if(c == 45)
        {
            fu = -1;
        }
        c = getchar();
    }
    while(c <= 57 && c >= 48)
    {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x)
{
    if(x < 0)
    {
        putchar(45);
        x = -x;
    }
    if(x > 9)
    {
        fprint(x / 10);
    }
    putchar(x % 10 + 48);
}
vector <int> num[300010];
int n, x, cnt[300010];
int tree[1200010];

void pushup(int rt)
{
	tree[rt] = min(tree[rt << 1], tree[rt << 1 | 1]);
}

int query(int rt, int l, int r, int x, int y)
{
	if(x <= l && r <= y) return tree[rt];
	int mid = (l + r) >> 1;
	int ans = 0x3f3f3f3f;
	if(x <= mid) ans = min(ans, query(rt << 1, l, mid, x, y));
	if(y > mid) ans = min(ans, query(rt << 1 | 1, mid + 1, r, x, y));
	pushup(rt);
	return ans;
}

void modify(int rt, int l, int r, int x, int y)
{
    if (x <= l && r <= x)
    {
        tree[rt] = y;
        return;
    }
    int mid = (l + r) >> 1; 
    if (x <= mid) modify(rt << 1, l, mid, x, y);
    if (x > mid) modify(rt << 1 | 1, mid + 1, r, x, y);
    pushup(rt);
}

void work()
{
	read(n);
	for (register int i = 1;i <= n;i ++)
	{
		num[i].clear();
		cnt[i] = 0;
	}
	for (register int i = 1;i <= n;i ++)
	{
		read(x);
		num[x].push_back(i);
		modify(1, 1, n, i, x);
	}
	for (register int i = 1;i <= n;i ++)
	{
		read(x);
		if(num[x].size() - cnt[x] == 0)
		{
			printf("NO\n");
			for (register int j = i + 1;j <= n;j ++) read(x);
			return ;
		}
		int pos = num[x][cnt[x]];
		int ret = query(1, 1, n, 1, pos);
		if(ret < x)
		{
			printf("NO\n");
			for (register int j = i + 1;j <= n;j ++) read(x);
			return ;
		}
		modify(1, 1, n, pos, 0x3f3f3f3f);
		cnt[x] ++;
	}
	printf("YES\n");
}
int Q;
int main()
{
    read(Q);
    while(Q --)
    {
    	work();
	}
}

```

---

## 作者：dengyaotriangle (赞：2)

之前使用了线段树通过了此题，现在重新看，发现树状数组也可以做。



------------

首先，如果 $a$ 与 $b$ 的元素可重集不同，则直接非法，否则，继续判断。

先考虑如果 $a_i$ 中元素两两不同的情况。

我们考虑我们干的事情，把 $a$ 变成 $b$ 其实就是把 $a$ 数组的第 $i$ 个元素移动到 $r_i$ 个位置，因为 $a$ 中元素两两不同，所以每个 $i$ 有唯一的 $r_i$。

那么，考虑我们可以进行的这个排序操作，首先假设我们只操作长度为2的子串，任何更长的东西肯定可以由它组成（冒泡排序），那么我们真正进行的操作使对**两个相邻逆序元素进行交换**。

那么我们考虑，一个数 $a_i$ 从 $i$ 走到 $r_i$，要与哪些元素 $a_j$ 进行交换呢？

我们发现，如果 位置 $j$ 满足 $j<i,r_j>r_i$ 或 $j>i,r_j<r_i$，那么它们一定会发生交换，因为 $j$ 本来在 $i$ 的一边，最后跑到了另一边。反之，$j$ 会一直在 $i$ 的一侧，不会发生交换。

那么，我们只需要求出 $r$，判断所有交换是否合法。

考虑判断是否有 $(\forall j<i,r_j>r_i),(a_j>a_i)$

首先判断这个条件是因为我们交换的是相邻逆序，所以它左边的要比它大方可交换。

而判断的方法则是看 $j<i,r_j>r_i$ 的所有 $a_j$ 的 min 是否 $ >a_i$即可，这个是一个经典的二维偏序中求信息问题，可以使用单点修改，后缀求 min 的树状数组解决。

而另一边 $(\forall j>i,r_j<r_i),(a_j<a_i)$ 对称，同理。

所以就做完了。

最后有一个小细节：如果有相同元素怎么办？

给出结论：$a$ 中第一个 $x$ 与 $b$ 中第一个 $x$配对，第二个与第二个配...即可。

首先感性理解这是对的。

而正确的原因是因为我们很容易证明，这样做， $x$ 与其它元素发生的交换是最少的，任何方案的改变只可能使增加不必要的交换（类似排序不等式的证法），很简单就不详细说了。

所以复杂度 $O(n\log n)$


------------

```cpp
#include<bits/stdc++.h>
using namespace std;
//dengyaotriangle!

const int maxn=300005;

int a[maxn],r[maxn];
vector<int> p[maxn];

int bit1[maxn],bit2[maxn];

void chgi(int i,int x){while(i<maxn)bit1[i]=max(bit1[i],x),i+=i&-i;}
void clri(int i){while(i<maxn)bit1[i]=INT_MIN,i+=i&-i;}
int qryi(int i){int ret=INT_MIN;while(i)ret=max(ret,bit1[i]),i-=i&-i;return ret;}
void chgx(int i,int x){while(i<maxn)bit2[i]=min(bit2[i],x),i+=i&-i;}
void clrx(int i){while(i<maxn)bit2[i]=INT_MAX,i+=i&-i;}
int qryx(int i){int ret=INT_MAX;while(i)ret=min(ret,bit2[i]),i-=i&-i;return ret;}
int mi[maxn],mx[maxn];

int main(){
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)p[i].clear();
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++){int x;cin>>x;p[x].push_back(i);}
        bool ok=1;
        for(int i=n;i>=1;i--){
            if(p[a[i]].empty()){ok=0;break;}
            r[i]=p[a[i]].back();p[a[i]].pop_back();
        }
        if(ok){
            for(int i=1;i<=n;i++)clri(i),clrx(i);
            for(int i=1;i<=n;i++){
                int v=qryx(n-r[i]+1);
                if(v<a[i])ok=0;
                chgx(n-r[i]+1,a[i]);
            }
            for(int i=n;i>=1;i--){
                int v=qryi(r[i]);
                if(v>a[i])ok=0;
                chgi(r[i],a[i]);
            }
        }
        cout<<(ok?"YES\n":"NO\n");
    }
    return 0;
}
```

---

## 作者：zcxnb (赞：1)

## 更新
2024/8/19  删去了不严谨的异或判重,感谢 @Ether13 大佬的提醒详见[此帖](https://www.luogu.com.cn/discuss/710111)
## 题目大意：
给定长为 $n$ 的序列 $a$，$b$。可以进行操作选择 $a$ 的一个区间并将其升序排序，问若干次操作后能否将 $a$ 变为 $b$。
## 感性理解：
首先序列 $a$ 与 $b$ 进行排序后一定要相等（可重集相同）。

其次排序的过程，考虑冒泡排序，对每个无序的长度为 $2$ 的区间进行排序，相当于交换相邻的两个逆序对。

从前往后考虑依次将 $a$ 的每一位变成 $b$，若 $a$ 的第 $i$ 位与 $b$ 的第 $j$ 位相对应，就把它移到位置 $j$。

此时我们考虑排序过程是相邻逆序对交换，若出现在 $a$ 的第 $j$ 位到第 $i$ 位中有比 $a$ 的第 $i$ 位小的数，那么就无法交换至第 $j$ 位，那么就无法完成排序。

简化为 $3$ 步：
1. 判重（异或判重，也可用随机值判重）
2. 找 $j$ 到 $i$ 中的最小值
3. 标记已排好序的数

### 暴力 70pts 代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,ah,bh;
int a[N],b[N],vis[N];
bool pan(){
	if(ah!=bh)  return 0;//异或判重(不严谨,建议不要使用)
	int ma=n;
	for(int i=1;i<=n;i++){
		int cnt=1;
		for(int j=1;j<=n;j++){//暴力搜索最小值
			if(vis[j])  continue;
			if(a[j]==b[i]&&cnt){
				vis[j]=1;//标记排好序的数
				break;
			} 
			if(a[j]<b[i])  return 0;
		}
	}
	return 1;
}
int main(){
	scanf("%d",&t);
	while(t--){
		ah=bh=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)  vis[i]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			ah^=a[i];
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
			bh^=b[i];
		}
		if(pan())  printf("YES\n");
		else  printf("NO\n");
	}
}
```
## 优化
我们考虑打标记对取最小值的影响，可以将已排好序的数赋值为 $\inf$，这样在取最小值时肯定不会受影响。

现在问题简化成单点修改，前缀查询最小值，我们发现一个事情——这很线段树。

用线段树进行优化。

### AC 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5,inf=1e9+5;
int q,n,ha,hb,suma,sumb;
int a[N],b[N],v[N],t[4*N],c[N],tota[N],totb[N];
map<int,map<int,int> >s;
void build(int k,int l,int r){
	if(l==r){
		t[k]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(2*k,l,mid);
	build(2*k+1,mid+1,r);
	t[k]=min(t[2*k],t[2*k+1]);
	return;
}
void dotchange(int k,int l,int r,int x){
	if(l==r&&l==x){
		t[k]=inf;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)  dotchange(2*k,l,mid,x);
	if(x>mid)  dotchange(2*k+1,mid+1,r,x);
	t[k]=min(t[2*k],t[2*k+1]);
}
int longquery(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y){
		return t[k];
	}
	int res=inf;
	int mid=(l+r)>>1;
	if(x<=mid)  res=min(longquery(2*k,l,mid,x,y),res);
	if(y>mid)  res=min(longquery(2*k+1,mid+1,r,x,y),res);
	return res;
}
bool pan(){
	for(int i=1;i<=n;i++)  if(tota[i])  return 0;
//	if(ha!=hb||suma!=sumb)  return 0;再次强调,异或判重和前缀和判重都不严谨
	for(int i=1;i<=4*n+1;i++)  t[i]=inf;//注意多测
	build(1,1,n);
	for(int i=1;i<=n;i++){
		++v[b[i]];
		int z=longquery(1,1,n,1,max(s[b[i]][v[b[i]]]-1,1));//前缀查询最小值
		if(z<b[i])  return 0;
		dotchange(1,1,n,max(s[b[i]][v[b[i]]],1));//单点修改 inf
		
	}
	return 1;
}
int main(){
	scanf("%d",&q);
	while(q--){
//		ha=0,hb=0,suma=0,sumb=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)  v[i]=0,c[i]=0,tota[i]=0;
		s.clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			s[a[i]][++c[a[i]]]=i;//依次记录每个 a[i] 出现的位置
//			ha^=a[i];
//			suma+=a[i];
			tota[a[i]]++;
		}
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
//			hb^=b[i];
//			sumb+=b[i];
			tota[b[i]]--;
		}
		if(pan())  printf("YES\n");
		else  printf("NO\n");
	}
}

---

## 作者：zsyyyy (赞：1)

## CF1187D 2400

### 题目描述

给定长度为 $n$ 的数组 $a$ 和 $b$。你每次可以选择一段区间 $[l,r]$，令 $a_l-a_r$ 的元素从小到大排序。你可以进行任意次操作。问能否使 $a$ 与 $b$ 完全相等。


### 思路

考虑从前往后凑出 $b$ 数组，凑 $b_i$ 时，应该把没凑成的最靠前的 $a_j$ 移到 $i$，而两个一起排序一定比多个一起排序更有可能成功，所以，成功的条件就变为了 $a_j$ 比 $a_i-a_j$ 都更小，用线段树维护即可，删除一个数等价为将它赋成 $INF$。


### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=3e5+10;
int T,n,a[MAXN],b[MAXN],aa[MAXN],bb[MAXN],tr[MAXN*5],book[MAXN];
bool flag;
queue<int> q[MAXN];
void build(int node,int l,int r)
{
	if(l==r)
	{
		tr[node]=a[l];
		return;
	}
	int mid=(l+r)/2,lnode=node*2,rnode=node*2+1;
	build(lnode,l,mid);
	build(rnode,mid+1,r);
	tr[node]=min(tr[lnode],tr[rnode]);
}
void update(int node,int l,int r,int x,int num)
{
	if(l==r)
	{
		tr[node]=num;
		return;
	}
	int mid=(l+r)/2,lnode=node*2,rnode=node*2+1;
	if(x<=mid)  update(lnode,l,mid,x,num);
	else  update(rnode,mid+1,r,x,num);
	tr[node]=min(tr[lnode],tr[rnode]);
}
int query(int node,int l,int r,int R)
{
	if(l>R)  return LONG_LONG_MAX;
	if(r<=R)  return tr[node];
	int mid=(l+r)/2,lnode=node*2,rnode=node*2+1;
	return min(query(lnode,l,mid,R),query(rnode,mid+1,r,R));
}
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		flag=0;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)  scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++)  scanf("%lld",&b[i]);
		for(int i=1;i<=n;i++)
		{
			aa[i]=a[i];
			bb[i]=b[i];
		}
		sort(aa+1,aa+n+1);
		sort(bb+1,bb+n+1);
		for(int i=1;i<=n;i++)
		{
			if(aa[i]!=bb[i])  flag=1;
		}
		if(flag)
		{
			puts("NO");
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			while(q[i].size())  q[i].pop();
		}
		for(int i=1;i<=n;i++)  q[a[i]].push(i);
		for(int i=1;i<=n;i++)
		{
			book[i]=q[b[i]].front();
			q[b[i]].pop();
		}
		build(1,1,n);
		for(int i=1;i<=n;i++)
		{
			if(query(1,1,n,book[i])!=a[book[i]]&&book[i])
			{
				flag=1;
				break;
			}
			update(1,1,n,book[i],LONG_LONG_MAX);
		}
		if(flag)  puts("NO");
		else  puts("YES");
	}
	return 0;
}
```


---

## 作者：FZzzz (赞：1)

一道不错的思维题。

我们从左往右考虑 $b$ 的每一位，发现我们肯定要从 $a$ 里找一个和这一位相同的拉过来。发现我们肯定是找还没有被用到的第一个。我们用队列维护一下每种数出现的位置即可。

考虑什么情况下可以被拉过来。发现当且仅当这个数前面所有没用过的数都比它大的时候它才能被拉过来。

我们再考虑怎么把它拉过来。可以像冒泡一样相邻两个进行一次操作，这样原来在它前面的所有数的顺序还是没有变的。感性理解一下，这样拉过来以后后面的怎么处理还是可以怎么处理，所以说如果这样不行那一定不行。

所以再看一下我们需要什么操作：
- 用队列维护每种数在 $a$ 中出现的位置。
- 判断一个数前面所有没用过的数是否都比它大。
- 从“没用过的数”里删掉一个数。

对于删除操作，你写个平衡树当然也没问题。不过我们可以直接把这个数设成无穷大。这样我们需要的就是单点修改区间最值，直接上线段树就行。

代码：
```cpp
#include<algorithm>
#include<queue>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
	while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=3e5+5;
int n,a[maxn],b[maxn];
queue<int> q[maxn];
struct node{
	int l,r;
	node* ch[2];
	int v;
	void pushup(){
		v=min(ch[0]->v,ch[1]->v);
	}
	node(int l,int r):l(l),r(r){
		if(l<r){
			int mid=l+(r-l)/2;
			ch[0]=new node(l,mid);
			ch[1]=new node(mid+1,r);
			pushup();
		}
		else{
			ch[0]=ch[1]=0;
			v=a[r];
		}
	}
	void modify(int x,int k){
		if(l==r) v=k;
		else{
			if(x<=ch[0]->r) ch[0]->modify(x,k);
			else ch[1]->modify(x,k);
			pushup();
		}
	}
	int query(int ql,int qr){
		if(ql==l&&qr==r) return v;
		else{
			if(qr<=ch[0]->r) return ch[0]->query(ql,qr);
			else if(ql>=ch[1]->l) return ch[1]->query(ql,qr);
			else return min(ch[0]->query(ql,ch[0]->r),ch[1]->query(ch[1]->l,qr));
		}
	}
	~node(){
		if(l<r){
			delete ch[0];
			delete ch[1];
		}
	}
}*rt;
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    int t=readint();
    while(t--){
    	n=readint();
    	for(int i=0;i<n;i++) a[i]=readint();
    	for(int i=0;i<n;i++) b[i]=readint();
    	for(int i=0;i<n;i++) q[a[i]].push(i);
    	rt=new node(0,n-1);
    	bool ok=1;
    	for(int i=0;i<n;i++){
    		if(q[b[i]].empty()){
    			ok=0;
    			break;
			}
    		if(rt->query(0,q[b[i]].front())<b[i]){
    			ok=0;
    			break;
			}
			rt->modify(q[b[i]].front(),maxn);
			q[b[i]].pop();
		}
		printf(ok?"yes\n":"no\n");
    	for(int i=1;i<=n;i++) queue<int>().swap(q[i]);
    	delete rt;
	}
    return 0;
}
```


---

## 作者：Erica_N_Contina (赞：0)

## 思路

我们来考虑这道题目应该怎么思考。我们把数组 $a$ 拆成一对对逆序对来看，然后我们注意到我们的操作。

操作是将任意一个区间在区间内进行排序。那么对于逆序对的影响，很显然操作只能使逆序对减少而不能产生新的逆序对。因此我们可以得到初步的结论：如果 $b$ 中有 $a$ 中没有的逆序对，那么不能。

现在来介绍主要过程。

### 初始状态

我们被给定了 $a,b$。然后我们从前往后逐个匹配。

### 匹配

假定我们的前 $i-1$ 个已经匹配成功了，我们现在来匹配第 $i$ 个位置。

- $a_i=b_i $ 不用说了。

- $a_i<b_i$。那么说明我们不可能匹配这个位置了。因为首先如果我们要修改这个位置的值，那么我们的操作 $[l,r]$ 就应该包含 $a_i$ 和 $a_j(a_j=b_i)$，但是 $a_i<a_j$，所以 $a_i$ 一定在最前面。又因为前 $i-1$ 个位置我们已经匹配好了，所以不能做改变，故位置 $i$ 不能被匹配。

- $a_i>b_i$，这种情况我们就要考虑 $a_{i+1}\sim a_{j-1}(a_j=b_i)$ 了。如果在些数字里面有比 $a_j$ 小的数，那么我们也是不能匹配的。为什么呢？因为我们前面说过我们的操作不能创造逆序对。但是如果 $a_{i+1}\sim a_{j-1}(a_j=b_i)$ 里面有比 $a_j$ 小的数，后来我们又要求 $a_j$ 要排在这些数的前面，那么一定会产生新的逆序对，这是不可能的。

综上所述，如果 $a_{i}\sim a_{j-1}(a_j=b_i)$ 里面有比 $a_j$ 小的数，那么我们就不能把 $a_j$ 转移到位置 $i$ 来。否则我们就可以转移过来。

### 算法

我们使用线段树维护区间最小值即可。对于存在 $a_i=\dots=a_j=b_k$ 的情况，我们优先选择没有匹配的、下标最小的那个（链表实现）。当我们匹配了一个 $a_i$ 后，在最小值线段树中我们要将其值改为 $inf$。

## 代码

```Plain Text
/*////////ACACACACACACAC///////////
       . Code  by  Ntsc .
       . Earn knowledge .
/*////////ACACACACACACAC///////////

#include<bits/stdc++.h>
#define int long long
#define db double#
#define pb push_back
#define rtn return
using namespace std;

const int N=3e5+5;
const int M=1e5;
const int Mod=1e5;
const int INF=1e9;

int n,m,p,q,T,s[N],ans;
list<int> ls[N];
int tr[N<<2],a[N],b[N];



void pushup(int x){
	tr[x]=min(tr[x<<1],tr[x<<1|1]);
}
void build(int x,int l,int r){
	if(l==r){
		tr[x]=a[l];return ;
	}
	int mid=l+r>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void change(int x,int l,int r,int p,int v){
	if(l==r){
		tr[x]=v;
		return ;
	}
	int mid=l+r>>1;
	if(p<=mid) change(x<<1,l,mid,p,v);
	else change(x<<1|1,mid+1,r,p,v);
	pushup(x);
}
int query(int x,int l,int r,int pl,int pr){
	if(l>r)return INF;
	if(pl>pr)return INF;
	if(l>=pl&&r<=pr){
		return tr[x];
	}
	int res=INF;
	int mid=l+r>>1;
	if(pl<=mid)res=min(res,query(x<<1,l,mid,pl,pr));
	if(pr>mid)res=min(res,query(x<<1|1,mid+1,r,pl,pr));
	return res;
}
void solve(){
	for(int i=1;i<=n;i++){
		if(!ls[b[i]].size()){
			cout<<"NO\n";
			return ;
		}		
		int id=ls[b[i]].front();
		ls[b[i]].pop_front();
//		cerr<<"id="<<id<<endl;;
		int mn=query(1,1,n,1,id-1);
		if(mn<b[i]){
			cerr<<mn<<endl;
			cout<<"NO\n";return ;
		}
		change(1,1,n,id,INF);
	}
	cout<<"YES\n";
}
signed main(){
	int t;cin>>t;
	while(t--){
		for(int i=1;i<=n;i++){
			while(ls[i].size())ls[i].pop_back();
		}
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i],ls[a[i]].pb(i);
		for(int i=1;i<=n;i++)cin>>b[i];
		
		build(1,1,n);
//		cerr<<"f\n";
		solve();
	}
	
	return 0;
}


```




---

## 作者：MatrixGroup (赞：0)

- 题意

给定长度为 $n$ 的序列 $a$ 和 $b$。你每次可以选择 $a$ 的一个子段从小到大排序。你可以进行任意次操作。问能否使 $a$ 与 $b$ 完全相等（对应位置上的元素相等）。

- 解法

首先显然等价于 swapcheck（对于一对相邻的逆序对交换）。先判掉元素不一样的，然后离散化为排列（如果相同数字前者更小）。

引理：答案为 `YES` 当且仅当不存在 $x<y$ 使得 $a$ 中 $x$ 在 $y$ 前但 $b$ 中 $x$ 在 $y$ 后。

证明：必要性显然。用反证法证充分性。若不存在，我们证明要么已经 $a$ 和 $b$ 一样了，要么可以再 swapcheck 一次。显然，如果 $a$ 和 $b$ 不一样，那么必定存在 $a$ 中 $x$ 在 $y$ 后且 $b$ 中 $x$ 在 $y$ 前。假如 $x,y$ 在 $a$ 中不相邻，设之间有 $u$。（形如 $y\cdots u\cdots x$）若 $u<x$，则 $b$ 中为 $u\cdots x\cdots y$，范围可以进一步缩小到 $x'=u,y'=y$，$u>y$ 同理，否则 $y>u$ 且 $u>x$，根据 $u$ 的位置一定有范围更小的。综上，范围可以不断减小直到相邻，也就是说一定可以 swapcheck 一次。swapcheck 会让逆序对数量不断变小，所以一定会达到 $a$ 与 $b$ 相同的情况。

设 $a$ 逆排列为 $u$，$b$ 逆为 $v$。于是就判断是否存在 $\begin{cases}x<y\\u_x<u_y\\v_x>v_y\end{cases}$。这是简单的三维偏序题。CDQ 分治即可。

---

## 作者：H2O_TX (赞：0)

## 一、思路

这道题的问题在于可以排序的区间是不固定的，这一点对于我们选择策略十分麻烦，所以思考一下，发现可以每次只排两个数，即交换他们的位置。

这样做是正确的，因为如果按照冒泡排序来看，的确就是每次交换两个数的位置。

接下来枚举第 $i$ 个位置，假设前 $i-1$ 个位置都已完成了。

找到 $a_j$ 等于 $b_i$，然后判断它是否能被交换到当前位置，也就是判断它是否是 $[1,j]$ 中的最小值，然后删除它（因为已经不影响结果了）。

因为我们是通过交换的方式把 $a_j$ 归位的，所以剩下部分的顺序不会受到影响。

## 二、实现

首先要预处理每一个 $b_i$ 对应的 $a_j$ 的位置，可以使用队列来完成，具体见代码：

```cpp
for(int i=1;i<=n;i++) q[a[i]].push(i);
for(int i=1;i<=n;i++) go[i]=q[b[i]].front(),q[b[i]].pop();
```

然后来看区间求最值，直接上线段树就好了，当然其他随便什么数据结构也可以。

注意删除的时候可以直接赋值为无穷大。

贴代码（附注释）：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;

}

const int N = 3e5+10, INF = 1e9;
int n,a[N],b[N],go[N];
int tonga[N],tongb[N];
queue<int> q[N];
struct sgt
{
    int minn,l,r;
}tr[N*4];

void update(int p)
{
    tr[p].minn=min(tr[p*2].minn,tr[p*2+1].minn);
}

void build(int p,int l,int r)
{
    tr[p].l=l,tr[p].r=r;
    if(l==r)
    {
        tr[p].minn=a[l];
        return;
    }
    int mid=l+r>>1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    update(p);
}

int query(int p,int l,int r)
{
    if(tr[p].l>=l&&tr[p].r<=r) return tr[p].minn;
    int mid=tr[p].l+tr[p].r>>1;
    int minn=INF;
    if(l<=mid) minn=min(minn,query(p*2,l,r));
    if(r>mid) minn=min(minn,query(p*2+1,l,r));
    return minn;
}

void change(int p,int x,int k)
{
    if(tr[p].l==tr[p].r)
    {
        tr[p].minn=k;
        return;
    }
    int mid=tr[p].l+tr[p].r>>1;
    if(x<=mid) change(p*2,x,k);
    else change(p*2+1,x,k);
    update(p);
}

int main()
{
    int T;
    T=read();
    while(T--)
    {
        n=read();

        for(int i=1;i<=n;i++) tonga[i]=tongb[i]=0;
        for(int i=1;i<=n;i++)
        {
            a[i]=read();
            tonga[a[i]]++;
        }
        for(int i=1;i<=n;i++)
        {
            b[i]=read();
            tongb[b[i]]++;
        }
        //一开始要先判断数字的个数是否一一对应
        int fl=1;
        for(int i=1;i<=n;i++)
            if(tonga[i]!=tongb[i])
            {
                fl=0;
                break;
            }
        if(!fl)
        {
            puts("NO");
            continue;
        }

        for(int i=1;i<=n;i++) q[a[i]].push(i);
        for(int i=1;i<=n;i++) go[i]=q[b[i]].front(),q[b[i]].pop();
        
        build(1,1,n);//建树
        for(int i=1;i<=n;i++)
        {
            if(query(1,1,go[i])!=a[go[i]])//如果它不是最小值，那他就无法归位，直接退出
            {
                fl=0;
                break;
            }
            change(1,go[i],INF);//删除
        }
        if(!fl) puts("NO");
        else puts("YES");
    }
    return 0;
}

```


---

