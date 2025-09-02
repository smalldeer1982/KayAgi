# Smart Beaver and Resolving Collisions

## 题目描述

The Smart Beaver from ABBYY has a lot of hobbies. One of them is constructing efficient hash tables. One of the most serious problems in hash tables is resolving collisions. The Beaver is interested in this problem very much and he decided to explore it in detail.

We assume that the hash table consists of $ h $ cells numbered from $ 0 $ to $ h-1 $ . Objects are added to and removed from it. Every object has its own unique identifier. In addition, every object has a corresponding hash value — an integer between $ 0 $ and $ h-1 $ , inclusive. When an object is added to the table, if the cell corresponding to the hash value of the object is free, then this object goes there. If the cell is already occupied by another object, there is a collision. When an object is deleted from the table, the cell which it occupied becomes empty.

The Smart Beaver has recently learned about the method of linear probing to resolve collisions. It is as follows. Let's say that the hash value for the added object equals $ t $ and cell $ t $ of the table is already occupied. Then we try to add this object to cell $ (t+m) mod h $ . If it is also occupied, then we try cell $ (t+2·m) mod h $ , then cell $ (t+3·m) mod h $ , and so on. Note that in some cases it's possible that the new object can not be added to the table. It is guaranteed that the input for this problem doesn't contain such situations.

The operation $ a mod b $ means that we take the remainder of the division of number $ a $ by number $ b $ .

This technique immediately seemed very inoptimal to the Beaver, and he decided to assess its inefficiency. So, you are given a sequence of operations, each of which is either an addition of an object to the table or a deletion of an object from the table. When adding a new object, a sequence of calls to the table is performed. Calls to occupied cells are called dummy. In other words, if the result of the algorithm described above is the object being added to cell $ (t+i·m) mod h $ $ (i>=0) $ , then exactly $ i $ dummy calls have been performed.

Your task is to calculate the total number of dummy calls to the table for the given sequence of additions and deletions. When an object is deleted from the table, assume that no dummy calls are performed. The table is empty before performing the operations, that is, initially it doesn't contain any objects.

## 样例 #1

### 输入

```
10 2 7
+ 11 0
+ 22 2
+ 33 6
+ 44 0
+ 55 0
- 22
+ 66 0
```

### 输出

```
7
```

## 样例 #2

### 输入

```
5 1 6
+ 123 0
+ 234 1
+ 345 2
- 234
+ 456 0
+ 567 0
```

### 输出

```
4
```

# 题解

## 作者：sodalyghat (赞：2)

## 分析
我们注意到当产生冲突时，每次加一个固定的 $m$ 值，所以显然整个哈希表会被划分成几个循环。因此我们预先把循环求出来。分别用数组记录下来每个点属于哪个循环，循环排开后的第几个点以及循环的左右端点。

然后用线段树来维护这几个循环，代码中 $lest$ 记录了这段区间中最左端的空闲点。

对于加操作，我们把一个循环断开成前后两部分，先求后半段有没有空余点，如果没有再去前半段找。

对于减操作，直接找到那个点并把它的 $lest$ 赋值成 $-1$ 就好。

具体操作看代码。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ac{
	const int MAXN = 200005;
	struct node{
		int lson, rson, lest;
	}seg[4 * MAXN];
	int cnt;
	void pushup(int x){
		int ls = seg[x].lson, rs = seg[x].rson;
		if(seg[ls].lest != -1) seg[x].lest = seg[ls].lest;
		else if(seg[rs].lest != -1) seg[x].lest = seg[rs].lest;
		else seg[x].lest = -1;
	}
	void Build(int &x, int l, int r){
		x = ++cnt;
		if(l == r){
			seg[x].lest = l;
			return ;
		}
		int mid = l + r >> 1;
		Build(seg[x].lson, l, mid);
		Build(seg[x].rson, mid + 1, r);
		pushup(x);
	}
	int find(int x, int l, int r, int L, int R){
		if(L == l && r == R) return seg[x].lest;
		int mid = l + r >> 1;
		if(R <= mid) return find(seg[x].lson, l, mid, L, R);
		if(L > mid) return find(seg[x].rson, mid + 1, r, L, R);
		int lans = find(seg[x].lson, l, mid, L, mid), rans = find(seg[x].rson, mid + 1, r, mid + 1, R);
		if(~lans) return lans;
		if(~rans) return rans;
		return -1;
	}
	void change(int x, int l, int r, int w, int v){
		if(l == r && r == w){
			if(v) seg[x].lest = -1;
			else seg[x].lest = l;
			return ;
		}
		if(l > w || r < w) return ;
		int mid = l + r >> 1;
		change(seg[x].lson, l, mid, w, v);
		change(seg[x].rson, mid + 1, r, w, v);
		pushup(x);
	}
	map<int, int> t;
	int vis[MAXN], d[MAXN][2], val[MAXN], last = 1, num;
	int main(){
		int h, n, m, rt;
		long long ans = 0;
		scanf("%d%d%d", &h, &m, &n);
		for(int i = 0;i < h;i++){
			if(vis[i]) continue;
			d[++num][0] = last;
			for(int j = i;!vis[j];j = j + m < h ? j + m : j + m - h){
				val[j] = last++;
				vis[j] = num;
			}
			d[num][1] = last - 1;
		}
		Build(rt, 1, h);
		int id, hash;
		char ch[2];
		for(int i = 1;i <= n;i++){
			scanf("%s%d", ch, &id);
			if(ch[0] == '+'){
				scanf("%d", &hash);
				int tmp = vis[hash];
				int l = d[tmp][0], r = d[tmp][1], v = val[hash];
				int v1 = find(1, 1, h, v, r);
				if(~v1) ans += v1 - v; 
				else{
					ans += r - v;
					v1 = find(1, 1, h, l, v);
					ans += v1 - l + 1;
				}
				change(1, 1, h, v1, 1);
				t[id] = v1;
			}
			else{
				int v = t[id];
				change(1, 1, h, v, 0);
				t[id] = 0;
			}
		}
		printf("%lld", ans);
		return 0;
	}
}
signed main(){
	return ac::main();
}
```


---

## 作者：Crazyouth (赞：0)

## 分析

我们发现，对于哈希冲突后元素会落到的位置，会形成一个或多个循环，这取决于 $h,m$ 是否互质。例如 $h=9,m=3$ 时会形成三个循环：$0\rightarrow 3\rightarrow6\rightarrow0$，$1\rightarrow4\rightarrow7\rightarrow1$，$2\rightarrow5\rightarrow8\rightarrow2$；而 $h=9,m=4$ 时只会形成一个循环：$0\rightarrow4\rightarrow8\rightarrow3\rightarrow7\rightarrow2\rightarrow6\rightarrow1\rightarrow5\rightarrow0$。这时候我们发现我们可以维护每个循环，判断从循环中的某一个点进去，下一个有空位的点在哪，并通过二者作差得出哈希冲突次数。我们对每个循环开一个结构体，这样对于每个结构体，题目转化为：

> 给定一个动态的环形 01 序列，求某个给定的位置 $k$ 及以后首个为 $0$ 的位置。

这样我们可以二分这个位置并使用一些数据结构来检查（线段树亲测会被卡常，请使用树状数组）。

另外我们还需要维护哈希表中每个下标都对应了第几个循环的第几个数，在处理循环的时候顺便记录即可。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
struct arr
{
	int n;
	vector<int> tr,ipos;
	inline void build(int x)
	{
		n=x;
		for(int i=0;i<=n;i++) tr.push_back(0);
	}
	void upd(int k,int c)
	{
		while(k<=n)
		{
			tr[k]+=c;
			k+=k&-k; 
		}
	}
	inline int qry(int k)
	{
		int ret=0;
		while(k)
		{
			ret+=tr[k];
			k-=k&-k;
		}
		return ret;
	}
	inline int check(int k)
	{
		if(qry(n)-qry(k-1)!=n-k+1)
		{
			int l=k,r=n,mid,res;
			while(l<=r)
			{
				mid=l+r>>1;
				if(qry(mid)-qry(k-1)!=mid-k+1) res=mid,r=mid-1;
				else l=mid+1;
			}
			return res;
		}
		else
		{
			int l=1,r=k-1,mid,res;
			while(l<=r)
			{
				mid=l+r>>1;
				if(qry(mid)!=mid) res=mid,r=mid-1;
				else l=mid+1;
			}
			return res;
		}
	}
	inline void del(int k)
	{
		upd(k,-1);
	}
}hsh[100010];
int vis[200010];
map<int,int> mp;
pair<int,int> pos[200010];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int h,m,q;
	cin>>h>>m>>q;
	vector<int> v;
	int ncnt=0;
	for(int i=0;i<h;i++)
	{
		if(vis[i]) continue;
		v.clear();
		ncnt++;
		int now=i;
		int cnt=1;
		hsh[ncnt].ipos.push_back(0);
		while(!vis[now])
		{
			vis[now]=1;
			pos[now]={ncnt,cnt};
			hsh[ncnt].ipos.push_back(now);
			cnt++;
			now=(now+m)%h;
		}
		hsh[ncnt].build(cnt-1);
	}
	long long ans=0;
	while(q--)
	{
		char opt;
		int id,hs;
		cin>>opt>>id;
		if(opt=='+')
		{
			cin>>hs;
			auto p=pos[hs];
			int ch=hsh[p.first].check(p.second);
			mp[id]=hsh[p.first].ipos[ch];
			hsh[p.first].upd(ch,1);
			ans+=(ch<p.second?hsh[p.first].n-(p.second-ch):ch-p.second);
		}
		else
		{
			auto p=pos[mp[id]];
			hsh[p.first].del(p.second);
		}
	}
	cout<<ans;
}

---

