# [SEERC 2018] Matrix Queries

## 题目描述

给定一个 $2^n \times 2^n$ 的矩阵，最开始每个格子都是白色的。格子的颜色可以是白色或黑色。定义一个矩阵的*价值*为：

1. 如果矩阵是单色的，则它的价值为 $1$ 金币；
2. 否则，将矩阵分割成 $4$ 个大小相等的子矩阵，矩阵的价值为子矩阵的价值之和加 $1$ 金币。

给定 $q$ 个询问，每个询问给定一个行/列的编号 $x$，你需要改变这一行/列中每个格子的颜色（黑色变为白色，白色变为黑色），然后计算出改变之后的新矩阵的*价值*。

## 说明/提示

样例中，每个询问后的矩阵如下图所示：

![样例图](https://cdn.luogu.com.cn/upload/image_hosting/1cyezquq.png)

## 样例 #1

### 输入

```
2 7
1 3
0 2
1 1
1 4
0 4
0 3
1 1```

### 输出

```
13
17
21
17
21
17
13```

# 题解

## 作者：xiaolilsq (赞：6)

[题目链接](https://www.luogu.com.cn/problem/P5869)

## 题目分析

这道题目最大的难点就是如何快速求一个矩阵的价值。

不妨认为一个矩阵是合法矩阵，当且仅当在算价值时可能会递归到该矩阵，比如以 $(1,1)$ 和 $(1,1)$ 为两个角的矩阵是合法的，以 $(1,5)$ 和 $(2,6)$ 为两个角的矩阵是合法的。

在原题面中，由于单色矩阵和多色矩阵都会造成贡献，所以价值不太好求，不妨转化一下题面：

1. 如果矩阵是单色的，则它的价值为 $0$ 金币；
2. 否则，将矩阵分割成 $4$ 个大小相等的子矩阵，矩阵的价值为子矩阵的价值之和加 $4$ 金币。

**最后，整个矩阵的价值还要加一。**

这种转化相当于是把**传递下去给每个矩阵造成额外的 $1$ 金币的贡献提前算到当前矩阵处**，由于整个矩阵一开始额外贡献的 $1$ 金币没有提前算，所以还要加一。

如果一个合法矩阵是异色的，那么一定会递归到该矩阵并造成贡献，因为包含它的合法矩阵肯定都是异色的，所以题目就是要求**所有异色的合法矩阵数量乘四加一**。

还是不好求，正难则反，考虑求出所有单色的合法矩阵数量，一个合法矩阵单色，当且仅当它所在的行被改变次数奇偶性相同，同时它所在的列被改变次数奇偶性相同，这个比较显然，题目中给出的结构对于行和列都是和线段树很类似的，而且行和列是可以分开考虑的，维护两个线段树同时维护线段树每一层的操作奇偶性相同的数量即可求得答案。

## 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define ch() getchar()
#define pc(x) putchar(x)
template<typename T>inline void read(T&x){
	int f;char c;
	for(f=1,c=ch();c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c<='9'&&c>='0';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>inline void write(T x){
	static char q[64];int cnt=0;
	if(!x)pc('0');if(x<0)pc('-'),x=-x;
	while(x)q[cnt++]=x%10+'0',x/=10;
	while(cnt--)pc(q[cnt]);
}
const int maxn=25,saxn=(1<<22)+9;
int c[2][maxn],t[2][saxn];
long long ans=0;
void build(int x,int st,int l,int r){
	++c[0][st],++c[1][st];
	t[0][x]=t[1][x]=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(x<<1,st+1,l,mid);
	build(x<<1|1,st+1,mid+1,r);
}
int op;
void change(int x,int st,int l,int r,int pos){
	ans-=1ll*c[op][st]*c[!op][st];if(t[op][x]!=2)--c[op][st];
	if(l==r)t[op][x]^=1;else{
		int mid=(l+r)>>1;
		if(pos<=mid)change(x<<1,st+1,l,mid,pos);
		else change(x<<1|1,st+1,mid+1,r,pos);
		if(t[op][x<<1]!=2&&t[op][x<<1]==t[op][x<<1|1])
		t[op][x]=t[op][x<<1];else t[op][x]=2;
	}
	if(t[op][x]!=2)++c[op][st];ans+=1ll*c[op][st]*c[!op][st];
}
int main(){
	int n,q;read(n),read(q);build(1,0,1,1<<n);
	long long sum=ans=((1ll<<(2*n+2))-1)/3;
	while(q--){
		int x;
		read(op),read(x);
		change(1,0,1,1<<n,x);
		write((sum-ans)*4+1),pc('\n');
	}
	return 0;
}

```

---

## 作者：hinin (赞：0)

这是一个关于矩阵操作和状态压缩的题目。用线段树（或称为树状数组）来维护矩阵的状态。

构建线段树，递归地构建每个节点的状态。更新线段树的状态，根据操作类型和位置更新状态，并更新状态计数。

对于每个询问，根据操作类型（改变行或列的颜色）更新线段树的状态，并计算矩阵的价值。

计算矩阵的价值时，考虑两种情况：全白或全黑，以及子矩阵的价值之和。

### 代码
``` cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define max(x, y) x > y ? x : y
#define min(x, y) x < y ? x : y
#define pii pair<ll, ll>

using namespace std;

const int N = 2e6 + 1, M = 2e1 + 1;
int n, q, a[2][N << 2], cnt[2][M];

void status(int p, int k, int node)
{
	if(a[p][node] != -1) { cnt[p][k]--; }
	if(a[p][node * 2] == a[p][node * 2 + 1]) { a[p][node] = a[p][node * 2]; }
	else { a[p][node] = -1; }
	if(a[p][node] != -1) { cnt[p][k]++; }
}

void build(int p, int k, int l, int r, int node) {
	a[p][node] = 0;
	if(k > 0) { cnt[p][k]++; }
	if(l == r) { return ; }
	int mid = (l + r) >> 1;
	build(p, k - 1, l, mid, node * 2);
	build(p, k - 1, mid + 1, r, node * 2 + 1);
}

void update(int p, int k, int v, int l, int r, int node) {
	if(l == r) {
		a[p][node]^=1;
		return ;
	}
	int mid=(l + r) >> 1;
	if(v <= mid) { update(p, k - 1, v, l, mid, node * 2); }
	else { update(p, k - 1, v, mid + 1, r, node * 2 + 1); }
	status(p, k, node);
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> q;
	int tot = (1 << n);
	build(0, n, 1, tot, 1);
	build(1, n, 1, tot, 1);
	int num = 0;
	for(int i = n, c = 1; i >= 1; i--, c *= 4) { num += c; }
	while(q--) {
		int op, x;
		cin >> op >> x;
		update(op, n, x, 1, tot, 1);
		int eq = 0;
		for(int i = 1; i <= n; i++) { eq += cnt[0][i] * cnt[1][i]; }
		int neq = num - eq;
		int ans = neq * 4 + 1;
		cout << ans << endl;
	}

	return 0;
}
```

---

