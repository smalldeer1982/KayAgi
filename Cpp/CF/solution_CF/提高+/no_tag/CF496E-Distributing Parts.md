# Distributing Parts

## 题目描述

You are an assistant director in a new musical play. The play consists of $ n $ musical parts, each part must be performed by exactly one actor. After the casting the director chose $ m $ actors who can take part in the play. Your task is to assign the parts to actors. However, there are several limitations.

First, each actor has a certain voice range and there are some parts that he cannot sing. Formally, there are two integers for each actor, $ c_{i} $ and $ d_{i} $ ( $ c_{i}<=d_{i} $ ) — the pitch of the lowest and the highest note that the actor can sing. There also are two integers for each part — $ a_{j} $ and $ b_{j} $ ( $ a_{j}<=b_{j} $ ) — the pitch of the lowest and the highest notes that are present in the part. The $ i $ -th actor can perform the $ j $ -th part if and only if $ c_{i}<=a_{j}<=b_{j}<=d_{i} $ , i.e. each note of the part is in the actor's voice range.

According to the contract, the $ i $ -th actor can perform at most $ k_{i} $ parts. Besides, you are allowed not to give any part to some actors (then they take part in crowd scenes).

The rehearsal starts in two hours and you need to do the assignment quickly!

## 样例 #1

### 输入

```
3
1 3
2 4
3 5
2
1 4 2
2 5 1
```

### 输出

```
YES
1 1 2
```

## 样例 #2

### 输入

```
3
1 3
2 4
3 5
2
1 3 2
2 5 1
```

### 输出

```
NO
```

# 题解

## 作者：Ray662 (赞：1)

[更好的阅读体验](https://www.luogu.com.cn/blog/sunrize/solution-cf496e)

[洛谷 传送门](https://www.luogu.com.cn/problem/CF496E) | [CodeForces 传送门](https://codeforces.com/problemset/problem/496/E)

---

### 思路

排序是必然的。

对于每个人，我们把右端点小他大的歌曲加入 set。

$k$ 很好处理，循环 $k$ 次即可。对于每次循环，我们在 set 中 lower_bound 找出第一个左端点大于此人左端点的歌曲，此歌曲便是当前这个人的答案。

**记得要把选中的歌曲从 set 中删除（因为一首歌不能被多次选）**。

`NO` 的情况就很好判断了，如果有的歌曲的 ans 为 $0$，则无解。

不熟悉 set 的可以看一下我的博客：[Link](https://www.luogu.com.cn/blog/sunrize/set-multiset-notes)。

---

代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define _for(i, a, b)  for (int i = (a); i <= (b); i ++ )
#define _all(i, a, b)  for (int i = (a); i >= (b); i -- )
using namespace std;
const int N = 1e5 + 5;
int n, m, ans[N];
struct music { int a, b, id; } a[N];
struct actor { int c, d, k, id; } b[N];
struct node {
	int val, id;
	inline bool operator < (const node & b) const { return val < b.val; }
};
multiset<node> s;
multiset<node> :: iterator iter;
inline bool rule_a(music x, music y) { return x.b < y.b; }
inline bool rule_b(actor x, actor y) { return x.d < y.d; }
int main() {
	ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n;
	_for (i, 1, n)  cin >> a[i].a >> a[i].b, a[i].id = i;
	cin >> m;
	_for (i, 1, m)  cin >> b[i].c >> b[i].d >> b[i].k, b[i].id = i;
	sort(a + 1, a + n + 1, rule_a), sort(b + 1, b + m + 1, rule_b);
	int j = 1;
	_for (i, 1, m) {
		while (j <= n && a[j].b <= b[i].d)  s.insert((node){a[j].a, a[j].id}), j ++ ;
		while (b[i].k) {
			iter = s.lower_bound((node){b[i].c, 0});
			if (iter == s.end())  break;
			ans[iter -> id] = b[i].id;
			b[i].k -- ;
			s.erase(s.find(*iter));
		}
	}
	_for (i, 1, n)  if (ans[i] == 0) { puts("NO"); return 0; }
	cout << "YES\n";
	_for (i, 1, n)  cout << ans[i] << " ";
	puts("");
	return 0;
}
```

---

## 作者：Zekrom (赞：1)

## 平衡树   
将曲子和音乐家的右端点排序，对于每个音乐家，取$r$曲<=$r$音乐家，且$l$曲>=$l$音乐家的最小即可，由单调性，曲子单调加入平衡树即可     
上代码    
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<set>
#include<algorithm>
#define inf 0x3f3f3f3f
#define N 100010
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();
	}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();
	}return x*f;
}
struct node{
	int l,r,id,k;
	bool operator  <(const node &s1){return r<s1.r;};
}a[N],b[N];
set<pair<int,int> >q;
int n,m,ans[N],now=1;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i].l=read(),a[i].r=read(),a[i].id=i;
	}
	m=read();
	for(int i=1;i<=m;i++){
		b[i].l=read(),b[i].r=read(),b[i].k=read(),b[i].id=i;
	}
	sort(a+1,a+1+n);
	sort(b+1,b+1+m);
	for(int i=1;i<=m;i++){
		while(b[i].r>=a[now].r&&now<=n){          //单调加入平衡树
			q.insert(make_pair(a[now].l,now));
			now++;
		}
		while(b[i].k--){                            //k个音乐家都要匹配
			set<pair<int,int> >::iterator p;
			p=q.lower_bound(make_pair(b[i].l,0));
			if(p==q.end())break;
			ans[a[p->second].id]=b[i].id;            //注意p为指针 
			q.erase(p);
		}
	}
	for(int i=1;i<=n;i++)if(!ans[i]){
		printf("NO\n");return 0;
	}
	printf("YES\n");
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);printf("\n");
	return 0;
}

```


---

## 作者：alex_liu (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF496E)

## 分析

一首曲子能被一个演奏家演奏，当且仅当演奏曲目被演奏家包含。

故首先对所有演奏家和曲目的区间按左端点排序，相同时把人排在前面。

对于整个序列按顺序枚举，如果是曲目，则需要在当前曲目前的演奏家中选出一个右端点 $r$ 最小且 $d_j>b_i$ 的人。

于是对人维护一个 set，在 set 上二分查找最优的人，选择后令其 `k--`，当 $k=0$ 时移出 set。

时间复杂度 $O((n+m)\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
struct node{
	int r,k,id;
	bool operator<(const node&x)const{return r<x.r;}
};
struct node2{int l,r,k,id;}a[100005],b[100005],c[200005];
bool cmp(node2 x,node2 y){return x.l^y.l?x.l<y.l:x.k>y.k;}
multiset<node>s;
int n,m,ans[100005];
int main(){
	n=read();
	for(int i=1;i<=n;i++)a[i].l=read(),a[i].r=read(),a[i].id=i,c[i]=a[i];
	m=read();
	for(int i=1;i<=m;i++)b[i].l=read(),b[i].r=read(),b[i].k=read(),b[i].id=i,c[i+n]=b[i];
	sort(c+1,c+n+m+1,cmp);
	for(int i=1;i<=n+m;i++){
		if(c[i].k){
			node tmp;tmp.r=c[i].r,tmp.id=c[i].id,tmp.k=c[i].k;
			s.insert(tmp);
		}else{
			multiset<node>::iterator it=s.lower_bound((node){c[i].r,0,0});
			if(it==s.end()){
				puts("NO");
				return 0;
			}
			ans[c[i].id]=(*it).id;
			node tmp=*it;
			s.erase(it);
			tmp.k--;
			if(tmp.k)s.insert(tmp);
		}
	}
	puts("YES");
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	puts("");
	return 0;
}
```

---

## 作者：When (赞：0)

#### 算法

贪心（黑题？）

#### 思路

考虑如何让每一位演奏家发挥最大作用，不难发现，当每一位演奏者优先处理自己能力范围内左端点最小的区间时可以达到最优。

所以，我们可以将乐曲和演奏者按照右端点排序，并用$set$维护乐曲左端点，对于每一个演奏者，将ta的左端点${lower\_bound}$一下就好了。

##### 注意

如果你用的是结构体,那建议使用$multiset$，因为可能出现重复元素。

#### 参考代码

```cpp
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

const int maxn = 1e5 + 10;
int n,m,Ans[maxn];
struct R{
	int l,r,k,id;
}a[maxn],b[maxn];
struct node{
	int val,id;
	friend bool operator<(node x, node y){
		return x.val < y.val;
	}
}tmp;
multiset<node> s;

bool cmp(R x, R y){return x.r < y.r;}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++ i) scanf("%d%d", &a[i].l, &a[i].r), a[i].id = i;
	scanf("%d", &m);
	for(int i = 1; i <= m; ++ i) scanf("%d%d%d", &b[i].l, &b[i].r, &b[i].k), b[i].id = i;
	sort(a + 1, a + 1 + n, cmp); sort(b + 1, b + 1 + m, cmp);
	int j = 1;
	for(int i = 1; i <= m; ++ i){
		while(a[j].r <= b[i].r && j <= n){
			tmp.id = a[j].id;
			tmp.val = a[j].l;
			s.insert(tmp); j++;
		}
		while(b[i].k){
			auto it = s.lower_bound((node){b[i].l, 0});
			if(it == s.end()) break;
			Ans[it->id] = b[i].id; b[i].k--; s.erase(it);
		}
	}
	for(int i = 1; i <= n; ++ i) if(!Ans[i]) return printf("NO\n"), 0;
	printf("YES\n");
	for(int i = 1; i <= n; ++ i) printf("%d ", Ans[i]);
	printf("\n");
	return 0;
}
```



---

## 作者：寒鸽儿 (赞：0)

先对乐曲和歌唱家进行排序。  
依次考虑每一个乐曲$[a_i, b_i]$,有效的音乐家$[c_i, d_i]$应当是$c_i \leqslant a_i$且$d_i \geqslant b_i$的。考虑对所有的$c_i \leqslant a_i$,因为对$a$排过序,对后面的其他乐曲来说$c_i \leqslant a_j$都是恒成立的,这是个废的信息。因此只要选择最小的$d_i \geqslant b_i$即可。  
考虑用平衡树来维护,由于满足$c \leqslant a$的歌唱家只会增加,每次把新增的歌唱家丢到平衡树里(以$d$为关键字),每次要用的时候查找即可。  
复杂度$O(nlogn)$  
```cpp
#include <cstdio>
#include <set>
#include <algorithm>
#define itra multiset<node>::iterator

using namespace std;

const int N = 123456, inf = 0x3f3f3f3f;

struct node {
	int l, r, k, id;
	node() {}
	node(int L, int R, int K, int ID) : l(L), r(R), k(K), id(ID) {}
	bool operator < (const node& o) const { return r == o.r ? l < o.l : r < o.r; }	
}actor[N];

struct node1 {
	int l, r, id;
	node1() {}
	node1(int L, int R, int ID) : l(L), r(R), id(ID) {}
	bool operator < (const node1& o) const { return l < o.l; }
}play[N];

inline bool cmp(node& a, node& b) { return a.l < b.l; }

multiset<node> s;
int ans[N];

int main() {
	int n, m;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d %d", &play[i].l, &play[i].r), play[i].id = i;
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i) scanf("%d %d %d", &actor[i].l, &actor[i].r, &actor[i].k), actor[i].id = i;
	sort(play + 1, play + n + 1);
	sort(actor + 1, actor + m + 1, cmp);
	int p = 1;
	s.insert(node(-inf,-inf,0,0));
	s.insert(node(inf,inf,0,0));
	for(int i = 1; i <= n; ++i) {
		while(p <= m && actor[p].l <= play[i].l) s.insert(actor[p]), ++p;
		itra it = s.lower_bound(node(-inf, play[i].r, 0, 0));
		if(it->r == inf) {
			printf("NO\n");
			return 0;
		}
		node tmp = *it; s.erase(it);
		if(--tmp.k > 0) s.insert(tmp);
		ans[play[i].id] = tmp.id;
	}
	printf("YES\n");
	for(int i = 1; i <= n; ++i) printf("%d ", ans[i]);
	printf("\n");
	return 0; 
} 
```

---

