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

## 作者：紊莫 (赞：0)

STL 练手题怎么还有树状数组二分这种东西啊。

---

对于 $0\le i < h$ 的每个 $i$，向 $(i+m)\bmod h$ 连边，会形成 $\gcd(h, m)$ 个环，且每个环大小相同。

对于每个环，建立一个 ``set`` 保存未被使用过的点，那么查询就是 ``set`` 上的后继（或者开头）。

按照题意算贡献即可。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 200005;
int ans, n, m, h, len, vis[N], rk[N];
set<int> c[N];
signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> h >> m >> n;
	len = __gcd(h, m);
	for (int i = 0; i < len; i++)
		for (int j = i, o = 0; !vis[j]; j = (j + m) % h)
			vis[j] = 1, c[i].insert(o), rk[j] = o++;
	map<int, int> mp, val;
	while (n--) {
		char op;
		int id, v;
		cin >> op >> id;
		if (op == '+') {
			cin >> v;
			val[id] = v % len;
			int d = rk[v];
			auto x = c[v % len].begin();
			if (*c[v % len].rbegin() >= d)
				x = c[v % len].lower_bound(d);
			else ans += h / len;
			ans += *x - d;
			mp[id] = *x;
			c[v % len].erase(x);
		} else {
			c[val[id]].insert(mp[id]);
		}
	}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：LEE114514 (赞：0)

## 思路

首先我们把 $0$ 到 $h-1$ 看成 $h$ 个点，其中 $u$ 向 $(u+m) \bmod h$ 连边，发现会形成 $\gcd(h,m)$ 个不交的环。

进一步的，一个点只会在环上不停绕，不会出环，于是问题转化成找到环上第一个没有被标记的点和删除一个点的标记。

环上问题不好处理，通过破环成链解决。至于找到第一个没有标记的点，可以使用数据结构上二分，复杂度最优 $O(\log h)$，为了代码编写方便使用了 $O(\log^2 h)$ 的树状数组配合二分。（当然理论上来说你也可以写文艺平衡树上二分，能卡到最优复杂度）。删除标记就是单点减，但是注意破环成链。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int h,m,n,tot,len,ans;
const int maxn=2e5+5;
struct BIT{
	vector<int> trr;
	int n;
	void init(int N){
		n=N;
		trr.resize(N+1);
	}
	void upd(int p,int x){
		while(p<=n) trr[p]+=x,p+=p&-p;
	}
	int qry(int p){
		int res=0;
		while(p) res+=trr[p],p^=p&-p;
		return res;
	}
	int sum(int l,int r){
		return qry(r)-qry(l-1);
	}
}t[maxn];
char op[2];
int x,y;
int pos[maxn];
map<int,pair<int,int> > mp;
int main(){
	scanf("%d%d%d",&h,&m,&n);
	tot=__gcd(h,m);
	len=h/tot;
	for(int i=0;i<tot;++i){
		for(int j=1,p=i;j<=len;++j,p=(p+m)%h) pos[p]=j;
		t[i].init(2*len);
	}	
	while(n--){
		scanf("%s%d",op,&x);
		if(op[0]=='+'){
			scanf("%d",&y);
			int blo=y%tot;
			int p=pos[y];
			//ÔÚ [p,p+len-1] ÖÐ¶þ·Ö³öµÚÒ»¸ö·ÇÈ«Ò»µÄ
			int L=p,R=p+len-1,MID;
			while(L<R){
				MID=(L+R)>>1;
				if(t[blo].sum(p,MID)<MID-p+1) R=MID;
				else L=MID+1;
			}
			ans+=R-p;
			if(R>len) t[blo].upd(R,1),t[blo].upd(R-len,1),mp[x]={blo,R-len};
			else t[blo].upd(R,1),t[blo].upd(R+len,1),mp[x]={blo,R};
		}else{
			y=mp[x].second;
			x=mp[x].first;
			t[x].upd(y,-1);
			t[x].upd(y+len,-1);	
		}
	}
	printf("%d",ans);
}
```

---

