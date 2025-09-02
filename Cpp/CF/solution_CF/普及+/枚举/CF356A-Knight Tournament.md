# Knight Tournament

## 题目描述

（题目大意）：有n个骑士，他们每个人都被从1-n进行编号，他们现在需要进行一次比赛，且总共会进行m场比赛。每场比赛会在编号在Li-Ri这段区间内的骑士之间举行，对于每场比赛，它的胜利者的编号为Xi，其他的骑士会出局，之后无法进行比赛。最后留下的骑士就是这次比赛的最终胜利者。比赛结束后，每个骑士都想知道他被哪一个骑士击败了，请你告诉他们。

## 样例 #1

### 输入

```
4 3
1 2 1
1 3 3
1 4 4
```

### 输出

```
3 1 4 0 ```

## 样例 #2

### 输入

```
8 4
3 5 4
3 7 6
2 8 8
1 8 1
```

### 输出

```
0 8 4 6 4 8 6 1 ```

# 题解

## 作者：Yukinoshita_Yukino (赞：9)

题意：有 $n$ 个骑士，他们每个人都被从 $1 \sim n$ 进行编号，他们现在需要进行一次比赛，且总共会进行 $m$ 场比赛。每场比赛会在编号在 $L_i-R_i$ 这段区间内的骑士之间举行，对于每场比赛，它的胜利者的编号为 $X_i$ ，其他的骑士会出局，之后无法进行比赛。最后留下的骑士就是这次比赛的最终胜利者。比赛结束后，每个骑士都想知道他被哪一个骑士击败了，请你告诉他们。

这是个线段树区间覆盖板子题，不过也可以用其它方法来做。

比如我们可以更简洁的并查集做法。我们知道复杂度瓶颈在于枚举大量已经被访问过的骑士，所以我们要想办法跳过这些骑士。

有一个小 trick ，对于每一个骑士，假设它的父亲是它之后的第一个未被覆盖的节点。枚举的时候只需要枚举节点，跳到它的父亲那里就行。

这个 trick 在很多题上都有很好的应用，比如 [P4145](https://www.luogu.com.cn/problem/P4145)。

代码：

```cpp

#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;
int n,m;
int f[maxn];
int find(int x)
{
	return x==f[x]?x:f[x]=find(f[x]);
}
int ans[maxn];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n+1;i++) f[i]=i;
	for(int i=1;i<=m;i++)
	{
		int l,r,x;
		cin>>l>>r>>x;
		for(int i=find(l);i<=r;i=find(i+1))
		{
			if(i!=x)
			{
				ans[i]=x;
				f[i]=i+1;	
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	
	return 0;
}

```

---

## 作者：Elma_ (赞：8)

如果有多个骑士打败的区间包含某一个骑士，那么只应该算第一个骑士。

考虑把询问倒过来处理，那么打败某个骑士的骑士应该是最后一个区间包含他的骑士。于是直接用线段树做一个区间覆盖即可。时间复杂度 $O((m+n)\log n)$。

```cpp
#include <map>
#include <ctime>
#include <stack>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;
 
inline int read() {
	int x = 0, w = 1;char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-')w = -1;ch = getchar(); }
	while (ch >= '0' && ch <= '9')x = x * 10 + ch - '0', ch = getchar();
	return x * w;
}
inline void write(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
 
const int maxn = 1e6 + 5;
const int mod = 1e9 + 7;
const int inf = 1e9;
 
inline int min(int x, int y) { return x < y ? x : y; }
inline int max(int x, int y) { return x > y ? x : y; }

struct query {
	int l, r, x;
}q[maxn];
int n, m; 

#define ls x << 1
#define rs x << 1 | 1
struct SGT {
	int ans[maxn], tag[maxn << 2];
	inline void pushdown(int x) {
		if (tag[x]) {
			tag[ls] = tag[x];
			tag[rs] = tag[x];
			tag[x] = 0;
		} 
	}
	inline void modify(int x, int l, int r, int L, int R, int k) {
		if (l >= L && r <= R) {
			tag[x] = k; return;
		}
		int mid = (l + r) >> 1;
		pushdown(x);
		if (L <= mid) modify(ls, l, mid, L, R, k);
		if (R > mid) modify(rs, mid + 1, r, L, R, k);
	}
	inline void getans(int x, int l, int r) {
		if (l == r) {
			ans[l] = tag[x]; return;
		}
		pushdown(x);
		int mid = (l + r) >> 1;
		getans(ls, l, mid);
		getans(rs, mid + 1, r);
	}
} tree; 
#undef ls
#undef rs

signed main() {
	n = read(), m = read();
	for (int i = 1;i <= m;i++) q[i].l = read(), q[i].r = read(), q[i].x = read();
	for (int i = m;i >= 1;i--) {
		if (q[i].l < q[i].x) tree.modify(1, 1, n, q[i].l, q[i].x - 1, q[i].x);
		if (q[i].r > q[i].x) tree.modify(1, 1, n, q[i].x + 1, q[i].r, q[i].x);
	}
	tree.getans(1, 1, n);
	for (int i = 1;i <= n;i++) printf("%lld%c", tree.ans[i], " \n"[i == n]);
    return 0;
}
```


---

## 作者：Nukumizu_Kaju (赞：6)

[和白雪皑皑重题了，这题还是弱化版，建议白雪皑皑也给整成紫的](https://www.luogu.com.cn/problem/P2391)

比较显然，一个骑士只会被打烂一次，那我们就给这个序列开一个并查集， $find(i)$ 表示第 $i$ 个骑士之后第一个没有被打烂的骑士的编号是多少，最开始的时候 $find(i)=i$ 。

如果第 $i$ 个骑士被打烂了，显然， $find(i)=find(i+1)$ 。

这题和白雪皑皑**唯一**的区别是，骑士不会被自己打烂，所以特判一下，打自己时跳过去就行了。

因为一个骑士顶了天被打烂一次，所以时间复杂度是 $O(n)$ 的。(但是其实并查集的时间复杂度是反阿克曼函数，只不过那玩意太小了，可以忽略不计)

代码如下:

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, p, q;
int father[1000005];
int sl[1000005];
int find(int x) {
  if (father[x] == x) {
    return x;
  }
  return father[x] = find(father[x]);
}
int main() {
  scanf("%d%d", & n,& m);
  for (int i = 1; i <= n + 2; i++) {
    father[i] = i;
  }
  for (int i = 1; i <= m; i++) {
    int lt;
    int rt;
    int color;
    scanf("%d%d%d", &lt, &rt, &color);
    if (lt > rt) {
      swap(lt, rt);
    }
    for (int j = lt; j <= rt;) {
      if (!sl[j]) {
        if (color == j) {//不能打自己
          j++;
          continue;
        }
        father[j] = j + 1;//把别人打烂
        sl[j] = color;//别人是我打烂的
      }
      j = find(j);//找到右边第一个还没被打烂的
    }
  }
  for (int i = 1; i <= n; i++) {
    printf("%d ", sl[i]);
  }
  return 0;
}
```

---

## 作者：封禁用户 (赞：5)

题目其实不难，直接按照题意模拟即可，但不能直接敲暴力。

下面介绍三种方法：

第一种方法：使用set维护哪些人或者，每次使用lower_bound找下一个活着的。

code:

```cpp
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <iostream>
#include <iterator>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <functional>
#include <bitset>
#pragma comment(linker, "/STACK:66777216")
using namespace std;
#define pb push_back
#define ppb pop_back
#define pi 3.1415926535897932384626433832795028841971
#define mp make_pair
#define x first
#define y second
#define pii pair<int,int>
#define pdd pair<double,double>
#define INF 1000000000
#define FOR(i,a,b) for (int _n(b), i(a); i <= _n; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;i--)
#define all(c) (c).begin(), (c).end()
#define SORT(c) sort(all(c))
#define rep(i,n) FOR(i,1,(n))
#define rept(i,n) FOR(i,0,(n)-1)
#define L(s) (int)((s).size())
#define C(a) memset((a),0,sizeof(a))
#define VI vector <int>
#define ll long long

int a,b,c,d,n,m,k;
int won[300002];
set<int> q;
int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	scanf("%d%d", &n, &m);
	rept(i, n) q.insert(i);
	memset(won, -1, sizeof(won));
	rept(i, m) {
		scanf("%d%d%d", &a, &b, &c); --a; --b; --c;
		VI rem;
		for (set<int>::iterator it = q.lower_bound(a); it != q.end() && *it <= b; ++it) {
			won[*it] = c;
			rem.pb(*it);
		}
		rept(i, L(rem)) q.erase(q.find(rem[i]));
		q.insert(c);
		won[c] = -1;
	}
	rept(i, n) {
		if (i) printf(" ");
		printf("%d", won[i] + 1);
	}
	printf("\n");
}
```

第二种方法：

使用并查集维护，每次删除把他和他的下一个连起来即可。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005;
int n,m,i,l,r,x,fa[N],beat[N];
int gf(int x)
{
	if(fa[x]!=x)
		fa[x]=gf(fa[x]);
	return fa[x];
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+1;i++)
		fa[i]=i;
	while(m--)
	{
		scanf("%d%d%d",&l,&r,&x);
		for(i=gf(l);i<=r;i=gf(i+1))
			if(i!=x)
				beat[i]=x,fa[i]=i+1;
	}
	for(int i=1;i<=n;i++)
		printf("%d ",beat[i]);
	return 0;
}

```

第三种方法：

使用树状数组+二分即可

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=600005;
int n,m,s[N],ans[N];
void modify(int x,int v)
{
	while(x<=n)
	{
		s[x]+=v;
		x=(x|(x-1))+1;
	}
}
int findsum(int x)
{
	int v=0;
	while(x>0)
	{
		v+=s[x];
		x&=x-1;
	}
	return v;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		s[i]=0;
	for(int i=1;i<=n;i++)
		modify(i,1);
	for(int i=1;i<=n;i++)
		ans[i]=0;
	while(m--)
	{
		int from,to,win;
		scanf("%d%d%d",&from,&to,&win);
		int dec=findsum(from-1);
		int add=findsum(to);
		while(add>dec)
		{
			int l=from,r=to;
			while(l<r)
			{
				int mid=(l+r)>>1;
				if(findsum(mid)==dec)
					l=mid+1;
				else
					r=mid;
			}
			ans[l]=win;
			modify(l,-1);
			add--; 
		}
		ans[win]=0;
		modify(win,1);
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
	return 0;
}

```

---

## 作者：wjr_jok (赞：3)

分块，但由于是区间修改，并且自己不会被自己打败，所以有相当多细节要处理。

首先肯定要逆序处理，这样才能保证取得每个骑士最先打败他的骑士编号。

开一个数组 $xg$ 记录整块的修改，对于整块直接对 $xg$ 数组所对应的值进行修改即可。

对于散块，我们直接将它所处的整块的单块值全部修改，否则我们后面输出时无法判断单块值与整块修改值的先后顺序，所以我们要保证单块值和整块修改值只有一个生效。

还有一种情况就是含有胜利者的块，由于自己不会被自己打败，所以这个块也要单独处理，方法同散块。

每次处理完散块和含有胜利者的块我们都将这个块的整块修改值清零，以便后面更新值。

输出时注意判断单块值和整块修改值那个生效。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,jl,cnt=1;
int l[300001],r[300001],s[300001],cc[300001];
int x[300001],y[300001],fk[300001],xg[300001];
int main(){
	cin>>n>>m;
	for(int i=1;i<=(int)sqrt(n);i++){
		cnt++;
		x[cnt]=y[cnt-1]+1;
		y[cnt]=x[cnt]+(int)sqrt(n)-1;
		for(int j=x[cnt];j<=y[cnt];j++){
			fk[j]=cnt;
		}
	}
	if(y[cnt]<n){
		cnt++;
		x[cnt]=y[cnt-1]+1;
		y[cnt]=n;
		for(int i=x[cnt];i<=y[cnt];i++){
			fk[i]=cnt;
		}
	}
	for(int i=m;i>=1;i--){//逆序处理
		cin>>l[i]>>r[i]>>s[i];
	}
	for(int i=1;i<=m;i++){
		for(int j=l[i];j<=min(r[i],y[fk[l[i]]]);j++){//左散块
			if(j==s[i]){
				if(xg[fk[l[i]]]){//判断整块修改值是否生效
					cc[j]=xg[fk[l[i]]];
				}
			}
			else{
				cc[j]=s[i];
			}
		} 
		if(xg[fk[l[i]]]){//这个整块剩下的部分
			for(int j=x[fk[l[i]]];j<l[i];j++){
				cc[j]=xg[fk[l[i]]];
			}
		}
		if(r[i]<y[fk[l[i]]]&&xg[fk[l[i]]]){
			for(int j=r[i]+1;j<=y[fk[l[i]]];j++){
				cc[j]=xg[fk[l[i]]];
			}
		}
		xg[fk[l[i]]]=0;
		if(fk[l[i]]!=fk[r[i]]){
			for(int j=x[fk[r[i]]];j<=r[i];j++){//右散块
				if(j==s[i]){
					if(xg[fk[r[i]]]){//同上
						cc[j]=xg[fk[r[i]]];
					}
				}
				else{
					cc[j]=s[i];
				}
			} 
			if(xg[fk[r[i]]]){//这个整块剩下的部分
				for(int j=r[i]+1;j<=y[fk[r[i]]];j++){
					cc[j]=xg[fk[r[i]]];
				}
			}
			xg[fk[r[i]]]=0;
		}
		if(fk[l[i]]!=fk[s[i]]&&fk[r[i]]!=fk[s[i]]){
			for(int j=x[fk[s[i]]];j<=y[fk[s[i]]];j++){//含有胜利者的块
				if(j==s[i]){
					if(xg[fk[s[i]]]){//还是同上
						cc[j]=xg[fk[s[i]]];
					}
				}
				else{
					cc[j]=s[i];
				}
			}
			xg[fk[s[i]]]=0;
		}
		for(int j=fk[l[i]]+1;j<fk[r[i]];j++){//整块
			if(j==fk[s[i]]){
				continue;
			}
			xg[j]=s[i];
		}
	}
	for(int i=1;i<=n;i++){//输出
		if(!xg[fk[i]]){
			cout<<cc[i]<<" ";
		}
		else{
			cout<<xg[fk[i]]<<" ";
		}
	}
	return 0;
}
```

---

## 作者：Z1qqurat (赞：2)

再摆，就废了！！

### 思路

区间覆盖。其实相当于把 $l$ 到 $r$ 的所有除了胜出者的值都赋为胜出者的编号。

但是这题的难点就在于每个骑士被打败之后就会出局。

那我们真的要不要模拟出局的过程？可不可以这样模拟？总司令，不可以。题目给出的每一次击败甚至都是按照没有出局来的。所以，我们只是要给出每个骑士**最早被覆盖时得到的值**，也就是一个骑士不会出局两次，是吧。

但是这个不好维护，于是这里有一种妙妙的思路，就是倒序处理每一次修改。这样子就相当于给出**最晚被覆盖时得到的值**了。于是我们只需要一个支持区间修改，单点查询的数据结构。线段树可以完美胜任，当然我认为也可以树状数组加差分处理。

于是离线后倒序修改，写一个线段树板子就完事了。

注意修改的时候要跳过胜出者，毕竟不可以自己打败自己，总司令。

### Code

可能有注释。

```cpp

#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 3e5 + 10;
int n, m, l[MAXN], r[MAXN], s[MAXN], tree[4 * MAXN], tag[4 * MAXN];

void pushup(int cur){
    tree[cur] = tree[2 * cur] + tree[2 * cur + 1];
    return ;
}

void addtag(int cur, int lt, int rt, int val){
    tag[cur] = val;
    tree[cur] = (rt - lt + 1) * val;
    return ;
}

void pushdown(int cur, int lt, int rt){
    if(tag[cur] == 0){
        return ;
    }
    int mid = (lt + rt) >> 1;
    addtag(2 * cur, lt, mid, tag[cur]);
    addtag(2 * cur + 1, mid + 1, rt, tag[cur]);
    tag[cur] = 0;
    return ;
}

int query(int cur, int lt, int rt, int qx){//单点查询。
    if(lt > qx || rt < qx){
        return 0;
    }
    if(qx == lt && qx == rt){
        return tree[cur];
    }
    pushdown(cur, lt, rt);
    int mid = (lt + rt) >> 1;
    return query(2 * cur, lt, mid, qx) + query(2 * cur + 1, mid + 1, rt, qx);
}

void modify(int cur, int lt, int rt, int qx, int qy, int val){//区间修改。
    if(lt > qy || rt < qx){
        return ;
    }
    if(qx <= lt && rt <= qy){
        addtag(cur, lt, rt, val);
        return ;
    }
    pushdown(cur, lt, rt);
    int mid = (lt + rt) >> 1;
    modify(2 * cur, lt, mid, qx, qy, val);
    modify(2 * cur + 1, mid + 1, rt, qx, qy, val);
    pushup(cur);
    return ;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i){
        scanf("%d%d%d", &l[i], &r[i], &s[i]);//离线修改。
    }
    for (int i = n; i >= 1; --i){
        modify(1, 1, n, l[i], s[i] - 1, s[i]);
        modify(1, 1, n, s[i] + 1, r[i], s[i]);//倒序区间修改。
    }
    for (int i = 1; i <= n; ++i){
        printf("%d ", query(1, 1, n, i));//单点查询。
    }
    return 0;
}

```

---

## 作者：Binary_Lee (赞：1)

## [题面传送门](https://www.luogu.com.cn/problem/CF356A)

本蒟蒻想练习一下并查集，所以是找并查集标签来这里的。写题解加深理解。

#### 解决思路

自然，看到区间修改之类很容易想到线段树，~~但本蒟蒻线段树会写挂~~，所以这里就讲比较简单的并查集思路。

并查集的核心是 $\text{find}$ 函数。$\text{find}$ 函数的目的是找到一个节点的父亲，本题中用于快速地找到下一个点搜谁。不带权的 $\text{find}$ 很好理解也很好写。如果父亲是本身，直接返回即可。否则去找父亲的父亲，并更新。一般这样写：
```cpp
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
```
如果你想压行也可以这样：
```cpp
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
```

然后是主函数。首先，要把所有节点的父亲赋值为自己。注意，一般要赋到 $n+1$ 。例如这题，如果只赋到 $n$ ，那么在找 $fa_{n+1}$ 时会进入死循环。

接着，对于每一个输入的 $l,r,x$ ，如果从 $l$ 到 $r$ 遍历显然会超时。这时候并查集就发挥作用了。我们可以让 $j$ 从 $\text{find(l)}$ 开始，每次都跳到 $\text{find(j+1)}$，这样可以避免反复扫到已经失败的骑士。之后，在这一范围里，如果 $j$ $\ne$ $x$（因为不会打败自己），就将 $ans_j$ 设为 $x$ 。再修改 $fa_j$。若 $j<x$ 则可将 $fa_j$ 设为 $x$，否则就设为 $r+1$。这里可以根据 $fa$ 数组的意义自己理解一下。

最后，只要愉快地输出 $ans$ 数组就可以了。

注意：数据范围是 $3\times10^5$，数组开小了会 **RE** （qwq）。

#### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,fa[300005],ans[300005],l,r,x;
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+1;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&l,&r,&x);
		for(int j=find(l);j<=r;j=find(j+1)){
			if(j!=x){
				if(j<x) fa[j]=x;
				else fa[j]=r+1;
				ans[j]=x;
			}
		}
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	return 0;
}
```


---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1500}$
---
### 解题思路：

一个骑士在被击倒之后不会再次被覆盖，但是下一次覆盖的时候并不能很好地解决不再次覆盖的问题，所以考虑倒序覆盖。

每一次将区间分成 $[l,x)$ 和 $(x,r]$，然后把两段区间都覆盖为 $x$ 即可。

区间覆盖可以使用线段树解决，总复杂度为 $O(n\log n)$。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
const int MAXN=300005<<4;
int n,m,L[MAXN],R[MAXN],X[MAXN],tag[MAXN];
void cover(int L,int R,int l,int r,int p,int num){
	if(l>r||L>R)return;
	if(L<=l&r<=R){tag[p]=num;return;}
//	if(l==r)return;
	if(tag[p]!=0)tag[p*2]=tag[p*2+1]=tag[p],tag[p]=0;
	int mid=l+r>>1;
	if(L<=mid)cover(L,R,l,mid,p*2,num);
	if(R>mid)cover(L,R,mid+1,r,p*2+1,num);
}
int query(int num,int l,int r,int p){
	if(l==num&&num==r)return tag[p];
	if(tag[p]!=0)tag[p*2]=tag[p*2+1]=tag[p],tag[p]=0;
//	if(l==r)return;
	int mid=l+r>>1;
	if(num<=mid)return query(num,l,mid,p*2);
	if(num>mid)return query(num,mid+1,r,p*2+1);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	scanf("%d%d%d",&L[i],&R[i],&X[i]);
	for(int i=m;i>=1;i--){
		cover(L[i],X[i]-1,1,n,1,X[i]);
		cover(X[i]+1,R[i],1,n,1,X[i]);
	}
	for(int i=1;i<=n;i++)printf("%d ",query(i,1,n,1));
	printf("\n");
	return 0;
}
```



---

## 作者：Arghariza (赞：1)

奇妙的线段树题。

考虑一个骑士被击败当且仅当他在**第一个包含他，并且他不是胜利者的区间里面**，击败他的人就是那个区间的胜利者。于是题目转换为求：对于每个 $i$ ，求 $\min\limits_{1\le j\le m}^{x_j≠i,l_j\le i\le r_j}\{j\}$。

然后我们把这些 $battles$ 倒序排列，不难发现：原来第一个包含 $i$ 且 $x_j≠i$ 的区间 $j$ 的胜利者（即打败 $i$ 的那个人），就是**倒序**把所有 $l_j$ 到 $r_j$ 除 $x_j$ 位外覆盖成 $x_j$ 之后第 $i$ 位的数。

为啥？因为是倒序排列，所以最后一个覆盖这一位的一定是原来第一个覆盖的。

于是题目再转换为区间覆盖，使用线段树维护即可。

```cpp
#include <bits/stdc++.h>
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 3e5 + 300;
struct segtree { int ls, rs, vl, cov; } tr[maxn << 2];
int n, m, rt, cnt, ql[maxn], qr[maxn], qx[maxn];

void pushup(int x) { tr[x].vl = tr[tr[x].ls].vl + tr[tr[x].rs].vl; }
void pushcov(int l, int r, int c, int x) { tr[x].vl = (r - l + 1) * c, tr[x].cov = c; }
void pushdown(int l, int r, int x) {
	if (!tr[x].cov) return;
	int mid = (l + r) >> 1;
	pushcov(l, mid, tr[x].cov, tr[x].ls);
	pushcov(mid + 1, r, tr[x].cov, tr[x].rs);
	tr[x].cov = 0;
}

int build(int l, int r, int x) {
	if (!x) x = ++cnt;
	if (l == r) { tr[x].vl = l; return x; }
	int mid = (l + r) >> 1;
	tr[x].ls = build(l, mid, tr[x].ls);
	tr[x].rs = build(mid + 1, r, tr[x].rs);
	pushup(x); return x;
}

void update(int l, int r, int s, int t, int c, int x) {
	if (s <= l && r <= t) { pushcov(l, r, c, x); return; }
	int mid = (l + r) >> 1; pushdown(l, r, x);
	if (s <= mid) update(l, mid, s, t, c, tr[x].ls);
	if (t > mid) update(mid + 1, r, s, t, c, tr[x].rs);
	pushup(x); 
}

int query(int l, int r, int p, int x) {
	if (l == r) return tr[x].vl;
	int mid = (l + r) >> 1; pushdown(l, r, x);
	if (p <= mid) return query(l, mid, p, tr[x].ls);
	else return query(mid + 1, r, p, tr[x].rs);
} 

int main() {
	n = read(), m = read();
	for (int i = m; i >= 1; i--) ql[i] = read(), qr[i] = read(), qx[i] = read();
	rt = build(1, n, rt);
	for (int i = 1; i <= m; i++) {
		if (ql[i] < qx[i]) update(1, n, ql[i], qx[i] - 1, qx[i], rt);
		if (qr[i] > qx[i]) update(1, n, qx[i] + 1, qr[i], qx[i], rt);
	}
	for (int i = 1; i <= n; i++) {
		int res = query(1, n, i, rt);
		write(i == res ? 0 : res);
		putchar(' ');
	}
	return 0;
}

```

---

## 作者：atarashiTLE (赞：1)

珂朵莉树模板题。

### 思路：
因为它是区间覆盖且需要跳过之前覆盖过的点，所以考虑时光倒流。

之后利用珂朵莉树区间推平即可。

注意：跑得有点慢（

code:
```cpp
#include<iostream>
#include<set>
#define int long long
#define il inline
#define re register
using namespace std;
struct node{
	int l,r;
	mutable int v;
	node(int L,int R=-1,int V=0){
		l=L;
		r=R;
		v=V;
	}
};
bool operator<(const node &n,const node& m){
	return n.l<m.l;
}
set<node> s;
#define IT set<node>::iterator
il IT split(int pos){
	IT it=s.lower_bound(node(pos));
	if(it!=s.end()&&it->l==pos)return it;
	it--;
	int l=it->l,r=it->r,v=it->v;
	s.erase(it);
	s.insert(node(l,pos-1,v));
	return s.insert(node(pos,r,v)).first;
}
il int assign(int l,int r,int v=0){//or sub2
	if(l>r)return 0;
	IT itr=split(r+1),itl=split(l);
	s.erase(itl,itr);
	s.insert(node(l,r,v));
	return 0;
}
il int sum(int i){//sub4
	IT itr=split(i+1),itl=split(i);
	return (itl->r-itl->l+1)*itl->v;
}
int n,m;
int l[300010][3];
signed main(){
	cin>>n>>m;
	for(re int i=1;i<=n+1;i++)
		s.insert(node(i,i,0));
	for(re int i=0;i<m;i++)
		cin>>l[m-i][0]>>l[m-i][1]>>l[m-i][2];
	for(re int i=1;i<=m;i++)
		assign(l[i][0],l[i][2]-1,l[i][2]),assign(l[i][2]+1,l[i][1],l[i][2]);
	for(re int i=1;i<=n;i++)
		cout<<sum(i)<<' ';
	return 0;
}
/*
10 7
7 8 7
7 9 9
5 9 5
5 10 10
1 2 2
3 4 4
2 10 4

2 4 4 0 10 5 9 7 5 4
*/
```

---

## 作者：codecode (赞：1)

#### 题解：

由题意可知，对于一个人，杀死他的是第一个覆盖他且他不为胜者的那个区间的胜者。于是，我们倒序执行区间覆盖，最后得到的结果就是杀死他的人。

区间覆盖可以用线段树实现。

注意到本题实质上线段树只需要维护一个 `lazytag`，具体见代码。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn=3e5+5;
int n,m,l[maxn],r[maxn],x[maxn],tree[maxn*4];
void pushdown(int root){ //标记下传并清空标记
	if(tree[root]){
		tree[root*2]=tree[root];
		tree[root*2+1]=tree[root];
		tree[root]=0;
	}
}
void update(int root,int l,int r,int xl,int xr,int val){ //区间赋值
	if(r<xl||l>xr)return;
	if(xl<=l&&r<=xr){ //当前区间被完全覆盖，由于只需要关注最后一个标记，直接打上标记即可
		tree[root]=val;
		return;
	}
	pushdown(root);
	int mid=(l+r)/2;
	update(root*2,l,mid,xl,xr,val);
	update(root*2+1,mid+1,r,xl,xr,val);
}
void print(int root,int l,int r){
	if(l==r){
		cout<<tree[root]<<" ";
		return;
	}
	pushdown(root);
	int mid=(l+r)/2;
	print(root*2,l,mid);
	print(root*2+1,mid+1,r);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>l[i]>>r[i]>>x[i];
	for(int i=m;i>=1;i--){ //倒序覆盖
		if(x[i]==l[i])update(1,1,n,l[i]+1,r[i],x[i]);
		else if(x[i]==r[i])update(1,1,n,l[i],r[i]-1,x[i]);
		else update(1,1,n,l[i],x[i]-1,x[i]),update(1,1,n,x[i]+1,r[i],x[i]);
	}
	print(1,1,n);
	return 0;
}

```

---

## 作者：世末OIer (赞：1)

题解1.bit+2分

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s[600010],ans[600010];
inline void modi(int x,int v){      //单点修改
	while(x<=n){
		s[x]+=v;
		x=(x|(x-1))+1;
	}
}
inline int fds(int x){             //区间查询
	int v(0);
	while(x){
		v+=s[x];
		x&=(x-1);
	}
	return v;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	int i,j;
	for(i=1;i<=n;++i) modi(i,1);           
	while(m--){
		int fr,to,win;
		cin>>fr>>to>>win;
		int dec(fds(fr-1));               //查出有多少个人需要杀掉
		int add(fds(to));
		while(add>dec){                 
			int l=fr,r=to;
			while(l<r){                   //利用树状数组中累加的个数二分
				int md((l+r)>>1);
				if(fds(md)==dec) l=md+1;
				else r=md;
			}
			ans[l]=win;                   //赋值
			modi(l,-1);                   //杀掉他
			--add;
		}
		ans[win]=0;                       //复活他(因为他赢了)
		modi(win,1);
	}
	for(i=1;i<=n;++i) cout<<ans[i]<<' ';  //输出
	return 0;
}
```

题解2.并查集（与楼下不同）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,l,r,x,fa[310000],beat[310000];
inline int gf(int x){                      //求父亲
	if(fa[x]!=x) fa[x]=gf(fa[x]);
	return fa[x];
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(i=1;i<n+2;++i) fa[i]=i;            //初始化
	while(m--){
		cin>>l>>r>>x;
		for(i=gf(l);i<=r;i=gf(i+1)) if(i!=x) beat[i]=x,fa[i]=i+1;  //把他归并到右节点上，就相当于最后一个打败他的人是x
	}
	for(i=1;i<=n;++i) _write(beat[i]);     //输出
	return 0;
}
```

---

## 作者：Letriomphant7396 (赞：1)

这道题乍看之下非常水，~~其实就是很水~~，思维难度很低，于是我看到题后就兴冲冲地写了一个暴力，emmmmm，结果显而易见，我在第11个点的时候T掉了。我问了我同学，他说用链表，之后自信地写了一个很优秀的链表，然后果然很好，他在第61个点才T......

闲话少叙，之后我又询问了一下大佬，得知了这道题的正解————并查集。先看一下代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+1;
int fa[N],beat[N],n,m;
int find(int x){return fa[x]==x?fa[x]:fa[x]=find(fa[x]);}
void bcj(int l,int r,int x)
{
	while(l<=r)
	{
		int v=find(l);
		if(v==l)
		{
			beat[l]=x;
			fa[l]=l+1;
		}
		l=fa[l];
    }
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n+1;i++) fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int l,r,x;
		scanf("%d%d%d",&l,&r,&x);
		bcj(l,x-1,x);//分两段处理
		bcj(x+1,r,x);
	}
	for(int i=1;i<=n;i++)
	printf("%d ",beat[i]);
}
```

fa[N]数组是指下一个要搜索到的骑士，beat[N]数组就是最后的答案。find()函数不多赘述，我们看经过修改后的并查集bcj()函数。首先bcj(int l,int r,int x)均如题中所述，然后我们从l搜到r，令v=find(l)，如果l==find(l),也就是说骑士l还没有出局，那么在这次遍历中，他就会被骑士x打败，所以beat[l]=x;fa[l]=l+1指这个骑士被打败后就出局了，那么下一次他会被略过，也就是说下一次搜到这个骑士时，find(l)!=l,find(l)会指向下一个没有出局的骑士。另一个要注意的问题是因为x不会被自己打败，所以每一次操作需要分两段处理。

~~IGNB！！！~~

---

## 作者：juruo999 (赞：0)

# CF356A Knight Tournament

传送门：[洛谷](https://www.luogu.com.cn/problem/CF356A) [CF](https://codeforces.com/problemset/problem/356/A)

一个非常自(bao)然(li)的解法。考虑模拟题目过程，对于每次比赛，把编号在 $[l,x-1]$ 或在 $[x+1,r]$ 中的骑士删去，并把这些骑士标记为 $x$ 打败的。

这个过程直接用 FHQ Treap 实现，每次操作时，以 $l-1,x-1,x,r$ 四个点为分界点把树分割成五块，然后合并第 $1,3,5$ 块，遍历第 $2,4$ 块中的骑士，并标记被 $x$ 打败。每个点最多只会被标记一次。时间复杂度为 $\Theta(n\log n)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/n65e5zjs.png)

核心代码：

```cpp
split(l-1,rt,a,b);	// 分割
split(x-1,b,b,c);
split(x,c,c,d);
split(r,d,d,e);
rt=merge(merge(a,c),e);	// 合并回去
st(b,x);st(d,x);	// st 是遍历子树标记被 x 打败
```

完整代码见 [CF 记录](https://codeforces.com/contest/356/submission/170491721)。

---

## 作者：happybob (赞：0)

## 题意

给定一个初始值全为 $0$ 的序列 $a$，有 $q$ 次操作，每次指定一三个数 $l, r, x$，表示将 $a_l \sim a_{x-1}$ 和 $a_{x+1} \sim a_r$ 中每个数设为 $a_i$，对于每个数，若 $a_i=0$，$a_i \leftarrow x$，否则不变。最后要求输出 $a$。

## 解法

~~并查集就不要了，这种题就应该线段树。~~

区间覆盖裸题，提供一个以前题解没有的在线的线段树写法，不需要操作倒序。

考虑对于每一个节点维护一个 $tag$，表示这个区间被赋值成了 $tag$，那么只需要在下传操作时不抹掉父节点的 $tag$，同时仅当左右儿子的 $tag = 0$ 时才对左右儿子下传。

当然倒序也是可以的，就是对操作倒序，这样保证每个点修改都是正序时最先的，也就是倒序时最晚的。

代码：

```cpp
#pragma GCC optimize("-Ofast")
#pragma unroll 10
#include <iostream>
#include <cstdio>
using namespace std;

const int N = 3e5 + 5;

int n, q;

class SegmentTree
{
public:
	struct Node
	{
		int l, r, sum, tag;
	}tr[N << 2];
	void push_up(int u)
	{
		tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
	}
	void push_down(int u)
	{
		auto& root = tr[u], &left = tr[u << 1], &right = tr[u << 1 | 1];
		if (root.tag)
		{
			if (!left.tag)
			{
				left.tag = root.tag;
				left.sum = (left.r - left.l + 1) * root.tag;
			}
			if (!right.tag)
			{
				right.tag = root.tag;
				right.sum = (right.r - right.l + 1) * root.tag;
			}
		}
	}
	void build(int u, int l, int r)
	{
		tr[u] = { l, r, 0, 0 };
		if (l == r) return;
		int mid = l + r >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}
	void update(int u, int l, int r, int k)
	{
		if (tr[u].tag) return;
		if (tr[u].l >= l and tr[u].r <= r)
		{
			tr[u].tag = k;
			tr[u].sum = (tr[u].r - tr[u].l + 1) * k;
		}
		else
		{
			push_down(u);
			int mid = tr[u].l + tr[u].r >> 1;
			if (l <= mid) update(u << 1, l, r, k);
			if (r > mid) update(u << 1 | 1, l, r, k);
			push_up(u);
		}
	}
	int query_node(int u, int x)
	{
		if (tr[u].l == x && tr[u].r == x) return tr[u].sum;
		push_down(u);
		int mid = tr[u].l + tr[u].r >> 1;
		return (x <= mid ? query_node(u << 1, x) : query_node(u << 1 | 1, x));
	}
};

SegmentTree seg;

int main()
{
	scanf("%d%d", &n, &q);
	seg.build(1, 1, n);
	for (int i = 1; i <= q; i++)
	{
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		int lp = l, rp = x - 1, lg = x + 1, rg = r;
		if (lp <= rp) seg.update(1, lp, rp, x);
		if (lg <= rg) seg.update(1, lg, rg, x);
	}
	for (int i = 1; i <= n; i++) printf("%d ", seg.query_node(1, i));
	puts("");
	return 0;
}
```


---

## 作者：SunsetSamsara (赞：0)

## 前置知识

线段树

## 题目分析

如果 $L_i$ 至 $R_i$ 被 $X_i$ 击败，

就标记为 $X_i$

但是，如果一个数 $X_i$ 被多个区间包含，那么只能算被第一个区间击败，所以把询问倒序处理。

## 代码

```cpp
#include <bits/stdc++.h>
#define lld long long
using namespace std;
struct node {
	int data;
	int tag;
	int l, r;
} tr[1500010];
int n, m;
void update(int id, int val) {
	tr[id].data = val;
	tr[id].tag = val;
}
void pushdown(int id) {
	if (tr[id].tag) {
		update(id << 1, tr[id].tag);
		update(id << 1 | 1, tr[id].tag);
		tr[id].tag = 0;
	}
}
void build(int p, int l, int r) {
	tr[p].l = l;
	tr[p].r = r;
	tr[p].tag = 0;
	tr[p].data = 0;
	if (l == r) return ;
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
}
void modify(int p, int l, int r, int v) {
	if (l <= tr[p].l && tr[p].r <= r) {
		update(p, v);
		return;
	}
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if (l <= mid) modify(p << 1, l, r, v);
	if (mid < r) modify(p << 1 | 1, l, r, v);
}
int query(int p, int id) {
	if (tr[p].l == tr[p].r) return tr[p].data;
	pushdown(p);
	int mid = (tr[p].l + tr[p].r) >> 1;
	if (id <= mid) return query(p << 1, id);
	else return query(p << 1 | 1, id);
}
 
int ql[300010], qr[300010], qx[300010];
 
int main(){
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	for(int i = 1;i <= m; ++ i) scanf("%d%d%d", ql + i, qr + i, qx + i);
	for(int i = m;i >= 1; -- i) {
		if(qx[i] > ql[i]) modify(1, ql[i], qx[i] - 1, qx[i]);
		if(qr[i] > qx[i]) modify(1, qx[i] + 1, qr[i], qx[i]);
	}
	for(int i = 1;i <= n; ++ i) printf("%d ", query(1, i));
}
```

---

## 作者：orz_z (赞：0)

## 题目大意

有 $n$ 个骑士，他们每个人都被从 $1-n$ 进行编号。

他们现在需要进行一次比赛，且总共会进行 $m$ 场比赛。

每场比赛会在编号在 $L_i-R_i$ 这段区间内的骑士之间举行，对于每场比赛，它的胜利者的编号为 $X_i$，其他的骑士会出局，之后无法进行比赛。最后留下的骑士就是这次比赛的最终胜利者。

比赛结束后，每个骑士都想知道他被哪一个骑士击败了，请你告诉他们。

## 解题思路

首先可以想到，$L_i - R_i$ 所有人被 $X_i$ 击败。

那么可以用线段树将这一段标记为 $X_i$。

但是会有一个问题，如果一个数 $op$，被多个区间包含，那么只能算被第一个区间击败。

所以将事件倒序处理即可。

时间复杂度 $\mathcal O(m \log n)$。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

const int _ = 5e5 + 7;

int n, m;

int l[_], r[_], x[_];

int tr[_ << 2];

void push_down(int o)
{
	if(tr[o])
	{
		tr[o << 1] = tr[o];
		tr[o << 1 | 1] = tr[o];
		tr[o] = 0;
	}
}

void update(int o, int l, int r, int L, int R, int val)
{
	if(r < L || l > R) return;
	if(L <= l && r <= R)
	{
		tr[o] = val;
		return;
	}
	push_down(o);
	int mid = (l + r) >> 1;
	update(o << 1, l, mid, L, R, val);
	update(o << 1 | 1, mid + 1, r, L, R, val);
}

void print(int o, int l, int r)
{
	if(l == r)
	{
		cout << tr[o] << " ";
		return;
	}
	push_down(o);
	int mid = (l + r) >> 1;
	print(o << 1, l, mid);
	print(o << 1 | 1, mid + 1, r);
}

signed main()
{
	cin >> n >> m;
	for(int i = 1; i <= m; ++i) cin >> l[i] >> r[i] >> x[i];
	for(int i = m; i >= 1; --i)
	{
		if(x[i] == l[i])
		{
			update(1, 1, n, l[i] + 1, r[i], x[i]);
		}
		else if(x[i] == r[i])
		{
			update(1, 1, n, l[i], r[i] - 1, x[i]);
		}
		else
		{
			update(1, 1, n, l[i], x[i] - 1, x[i]);
			update(1, 1, n, x[i] + 1, r[i], x[i]);
		}
	}
	print(1, 1, n);
	return 0;
}
```



---

