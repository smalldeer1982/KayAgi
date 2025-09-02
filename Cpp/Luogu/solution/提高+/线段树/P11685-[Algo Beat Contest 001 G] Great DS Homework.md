# [Algo Beat Contest 001 G] Great DS Homework

## 题目背景

|               Problem               | Score |                         Idea                          |                             Std                              |                      Data                       |                            Check                             |                           Solution                           |
| :---------------------------------: | :---: | :---------------------------------------------------: | :----------------------------------------------------------: | :---------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|   $\text{G - Great DS Homework}$    | $600$ |  [orchardist](https://www.luogu.com.cn/user/347582)   |      [orchardist](https://www.luogu.com.cn/user/347582)      | [joe_zxq](https://www.luogu.com.cn/user/623577) | [remmymilkyway](https://www.luogu.com.cn/user/551981) & [joe_zxq](https://www.luogu.com.cn/user/623577) | [Link](https://www.luogu.com.cn/article/xkcrwcoz) by [orchardist](https://www.luogu.com.cn/user/347582) |



小 G 觉得上一道数学题太愚蠢了，所以出了一道数据结构题作为作业。

## 题目描述

小 G 有一个长度为 $2N-1$ 的逻辑表达式，形如 $a_1 \space op_2\space a_2\space op_3\space a_3 \dots op_N\space a_N$，其中 $a_i \in \{ 0,1\}$，$op_i$ 为 `&`，`|` 或 `^`。

`&` 表示与运算，`|` 表示或运算，`^` 表示异或运算。运算符之间**不分优先级**。

定义一个表达式的子表达式为它的一个**连续**区间，满足区间左端点，右端点均为数字。特别地，单独一个数字也算在内。

现在小 G 想知道，这个表达式的所有子表达式计算结果的和是多少？

小 G 觉得这个问题太简单了，所以决定进行 $Q$ 次修改。每次修改给定 `pos nop nx`，表示将 $op_{pos}$ 改为 $nop$，$a_{pos}$ 改为 $nx$。特别地，当 $pos=1$ 时，$nop$ 可忽略。你需要在每次修改后，都输出这个表达式的所有子表达式计算结果的和。

## 说明/提示

#### 样例解释 #1

第一次操作后，逻辑表达式为 `1&1^0^1`，子表达式有 `1`、`1`、`0`、`1`、`1&1`、`1^0`、`0^1`、`1&1^0`、`1^0^1`、`1&1^0^1`，计算结果之和为 $1+1+0+1+1+1+1+1+0+0=7$。

#### 数据范围

对于 $100\%$ 的数据，保证 $1 \le N,Q \le 10^6$。

## 样例 #1

### 输入

```
4 4
1&1^0|0
4 ^ 1
4 | 0
1 | 0
2 & 0```

### 输出

```
7
7
3
0```

## 样例 #2

### 输入

```
10 10
1|1|1^1|0^0&0|0|1&1
6 ^ 1
9 & 1
7 ^ 1
1 ^ 1
1 | 0
7 | 1
6 & 1
2 ^ 1
8 | 1
2 & 1```

### 输出

```
32
16
24
24
23
43
40
40
43
42```

# 题解

## 作者：joe_zxq (赞：6)

题解作者是 [orchardist](https://www.luogu.com/user/347582)，以下叙述中的第一人称均指作者。

---

膜拜 [Eric998](https://www.luogu.com.cn/user/678534) 的矩阵做法，此人（~~奶龙~~）锐评为 $1900$ 分。但本人太菜，只会朴素的 dp 和线段树做法。

首先，不难想到一个对于每次修改 $O(n)$ 的 dp 解法：设 $dp_i$ 表示以第 $i$ 位结尾的所有表达式计算结果之和。则对于 $2 \le i \le n$，有：

[![](https://pic1.imgdb.cn/item/679851d8d0e0a243d4f841ae.png)](https://pic1.imgdb.cn/item/679851d8d0e0a243d4f841ae.png)

初始状态为 $dp_1=a_1$，答案即为 $\sum_{i = 1}^{n} dp_i$。

考虑优化这个过程。为了便于表达，以下把上面五种转移方程分别记作 $tp_i=1,2,3,4,5$。不难发现，每次只修改一个 $i$ 的转移方程。

每次修改后，从询问所给的第 $x$ 位开始，若当前对应的 $tp$ 值为 $4$ 或 $5$，则以后位置的 $dp$ 值不受影响。找到第一个 $x$ 后的 $i$ 使 $tp_i=4$ 或 $5$，可以用 set 维护。

对于其他位置，如果从起始位加 $1$ 到当前位出现 $tp_i=3$ 奇数次，则 $dp_i$ 增加起始位的增加量，偶数次则减少。这里需用线段树维护带修改的区间 $dp$ 值的和，区间从第 $1$ 位开始出现 $tp_i=3$ 奇数次的个数与偶数次的个数。另外，计算起始位的增加量，需要单点查询。

修改时不需要全部分类讨论，只要先按 $dp_x$ 的增量修改，然后判断先后是否有 $tp_x=3,4,5$，逐一更新即可。单次修改 $O(\log N)$，总复杂度 $O((N+Q)\log N)$。

最后就是一些细节问题，详见代码。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e6+5;
int n,q,dp[N],tp[N],sum[N];
int mktp(char x,char y){
	if((x=='|'||x=='^')&&y=='0') return 1;
	if(x=='&'&&y=='1') return 2;
	if(x=='^'&&y=='1') return 3;
	if(x=='&'&&y=='0') return 4;
	return 5;
}
set<int> S;
string s;
struct node{
	ll ans;
	int cnt0,cnt1,add;
	bool rev;
	void tgrev(){
		swap(cnt0,cnt1);
		rev^=1;
		add=-add;
	}
	void tgadd(int k){
		ans+=1ll*(cnt0-cnt1)*k;
		add+=k;
	}
}t[N<<2],lst,emp;
node operator+(node a,node b){
	return {a.ans+b.ans,a.cnt0+b.cnt0,a.cnt1+b.cnt1,0,0};	
}
void build(int p,int l,int r){
	if(l==r){
		t[p].ans=dp[l];
		if(sum[l]) t[p].cnt1=1;
		else t[p].cnt0=1;
		return;
	}
	int mid=(l+r)>>1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	t[p]=t[p*2]+t[p*2+1]; 
}
void down(int p){
	if(t[p].rev){
		t[p*2].tgrev();
		t[p*2+1].tgrev();
		t[p].rev=0;
	}
	if(t[p].add){
		t[p*2].tgadd(t[p].add);
		t[p*2+1].tgadd(t[p].add);
		t[p].add=0;
	}
}
void updrev(int p,int l,int r,int ql,int qr){
	if(l>qr||r<ql) return;
	if(ql<=l&&r<=qr){
		t[p].tgrev();
		return;
	}
	down(p);
	int mid=(l+r)>>1;
	updrev(p*2,l,mid,ql,qr);
	updrev(p*2+1,mid+1,r,ql,qr);
	t[p]=t[p*2]+t[p*2+1];
}
void updadd(int p,int l,int r,int ql,int qr,int k){
	if(l>qr||r<ql) return;
	if(ql<=l&&r<=qr){
		t[p].tgadd(k);
		return;
	}
	down(p);
	int mid=(l+r)>>1;
	updadd(p*2,l,mid,ql,qr,k);
	updadd(p*2+1,mid+1,r,ql,qr,k);
	t[p]=t[p*2]+t[p*2+1];
}
node query(int p,int l,int r,int x){
	if(l==r) return t[p];
	down(p);
	int mid=(l+r)>>1;
	if(x<=mid) return query(p*2,l,mid,x);
	return query(p*2+1,mid+1,r,x);
}
int trans(int ldp,int ntp,int i){
	if(ntp==1) return ldp;
	if(ntp==2) return ldp+1;
	if(ntp==3) return i-ldp;
	if(ntp==4) return 0;
	return i;
}
int main(){
	cin>>n>>q>>s;s=" "+s;
	if(s[1]=='0') s[0]='|';
	else s[0]='&';
	for(int i=1;i<=n;i++){
		tp[i]=mktp(s[i*2-2],s[i*2-1]);
		if(tp[i]>=4) S.insert(i);
	}
	S.insert(n+1);
	dp[1]=s[1]-'0';
	for(int i=2;i<=n;i++)
		dp[i]=trans(dp[i-1],tp[i],i);
	for(int i=1;i<=n;i++)
		if(tp[i]<=3) sum[i]=sum[i-1]^(tp[i]==3);
	build(1,1,n);
	while(q--){
		int x;char y,z;
		scanf("%d %c %c",&x,&y,&z);
		if(x==1){
			if(z=='0') y='|';
			else y='&';
		}
		int ntp=mktp(y,z);
		if(tp[x]==ntp){
			printf("%lld\n",t[1].ans);
			continue;
		}
		lst=emp;
		lst.cnt0=1;
		if(x>1) lst=query(1,1,n,x-1);
		int ldp=trans(lst.ans,tp[x],x);
		int ndp=trans(lst.ans,ntp,x);
		int k=ldp-ndp;
		bool lstst=((lst.cnt0&&tp[x]!=3)||(lst.cnt1&&tp[x]>=3));
		bool nowst=((lst.cnt0&&ntp!=3)||(lst.cnt1&&ntp>=3));
		if(lstst) k=-k;
		auto it=S.upper_bound(x);
		int r=(*it)-1;
		updadd(1,1,n,x,r,k);
		if(lstst^nowst) updrev(1,1,n,x,r);
		if(tp[x]>=4&&ntp<4) S.erase(x);
		else if(tp[x]<4&&ntp>=4) S.insert(x);
		printf("%lld\n",t[1].ans);
		tp[x]=ntp;
	}
	return 0; 
}
```

---

## 作者：Louis_lxy (赞：2)

**本题解仅给思路，公式请读者自推。**
# 思路
首先考虑没有修改怎么做，计数常见套路：dp、分治、组合数学。~~这题写组合数学的也真是人才~~。这种题有点像最大子段和，可以 dp 也可以分治，由于 dp 比较无脑（标程神秘做法除外，这里指矩阵做法），所以这里主要介绍分治。

考虑如何合并两个区间，首先考虑十分暴力的做法：计算完左边的一部分后，再依次插入右边每个区间判断是否为 $1$。总复杂度大概是 $O(n^2)$ 级别的，然后再考虑优化，容易发现我们这里只用了左边的后缀以及右边前缀，假设我们已经预处理好左区间的有多少个后缀值为 $0$ 或 $1$，记后缀为 $i$ 的数量为 $cntsuf_i$，以及右区间前面插入数字 $i$ 会得到多少个值为 $1$ 的前缀，记为 $connect_i$。然后我们就可以计算跨区间的了。注意没有修改直接暴力预处理总复杂度是 $O(n\log n)$ 的，可以通过没有修改的（虽然这题没有部分分）。

考虑修改，注意到修改一个数其实仅仅影响了 $O(\log n)$ 个区间。如果我们有办法 $O(1)$ 或者 $O(\text{polylog})$ 地修改区间就好了。一种可能的想法是假设现在修改位置 $l$，我们考虑 $[l,r]$ 与 $[l+1,r]$ 的关联。注意我们如果已经知道区间 $[l+1,r]$ 的答案，那么我们就可以反推 $[l,r]$，但可惜的是我们没法 $O(\text{polylog})$ 的求出所有 $[l+1,r]$ 的值。于是考虑另一种方法，同样考虑处理 $[l,r]$，假设它在向上归并的过程中的儿子区间是 $[l_1,r_1]$ 和 $[l_2,r_2]$，我们考虑通过合并这两个区间来得到 $[l,r]$。注意我们可以合并出 $cnt$（这个区间内值为 $1$ 的子表达式的数量）和 $connect$，但是 $cntsuf$ 不好做，因为我们不知道左区间的一段后缀并入右区间后的值，考虑预处理它，于是我们只需要处理好值 $i$ 运算完 $[l_2,r_2]$ 这个表达式后的值即可。然后我们发现这个过程有点像线段树，用线段树维护即可。

最后贴一个代码供参考：

```cpp
#include <bits/stdc++.h>
#define mid ((l + r) >> 1)
#define lson (x << 1)
#define rson (x << 1 | 1) 
#define int long long
using namespace std;

const int N = 1e6 + 10, M = N << 2;
int n, q, a[N];
char c[N];
struct expr { int cnt, turnto[2], connect[2], cntsuf[2]; } tr[M];
//cnt 这个区间内值为 1 的子表达式的数量，turnto 左边插入一个 i 后这个区间的值，connect 左边插入一个 i 后这个区间的前缀区间为 1 的数量，cntsuf 这个区间后缀为 i 的数量。 

expr merge(expr a, expr b) {
	expr ans;
	ans.cnt = a.cnt + b.cnt + a.cntsuf[0] * b.connect[0] + a.cntsuf[1] * b.connect[1];
	ans.turnto[0] = b.turnto[a.turnto[0]], ans.turnto[1] = b.turnto[a.turnto[1]];
	ans.connect[0] = a.connect[0] + b.connect[a.turnto[0]], ans.connect[1] = a.connect[1] + b.connect[a.turnto[1]];
	ans.cntsuf[0] = b.cntsuf[0] + a.cntsuf[0] * (b.turnto[0] == 0) + a.cntsuf[1] * (b.turnto[1] == 0);
	ans.cntsuf[1] = b.cntsuf[1] + a.cntsuf[0] * (b.turnto[0] == 1) + a.cntsuf[1] * (b.turnto[1] == 1);
	return ans;
}

int calc(int a, char com, int b) {
	if (com == '&') return a & b;
	else if (com == '|') return a | b;
	else return a ^ b;
} 

void build(int x, int l, int r) {
	if (l == r) {
		tr[x].cnt = a[l];
		tr[x].turnto[0] = calc(0, c[l], a[l]), tr[x].turnto[1] = calc(1, c[l], a[l]);
		tr[x].connect[0] = calc(0, c[l], a[l]), tr[x].connect[1] = calc(1, c[l], a[l]);
		tr[x].cntsuf[a[l]] = 1, tr[x].cntsuf[a[l] ^ 1] = 0;
		return;
	}
	build(lson, l, mid), build(rson, mid + 1, r);
	tr[x] = merge(tr[lson], tr[rson]);
}

void update(int x, int l, int r, int d, int k, char ch) {
	if (l == r) {
		a[l] = k, c[l] = ch;
		tr[x].cnt = a[l];
		tr[x].turnto[0] = calc(0, c[l], a[l]), tr[x].turnto[1] = calc(1, c[l], a[l]);
		tr[x].connect[0] = calc(0, c[l], a[l]), tr[x].connect[1] = calc(1, c[l], a[l]);
		tr[x].cntsuf[a[l]] = 1, tr[x].cntsuf[a[l] ^ 1] = 0;
		return;
	}
	if (d <= mid) update(lson, l, mid, d, k, ch);
	else update(rson, mid + 1, r, d, k, ch);
	tr[x] = merge(tr[lson], tr[rson]);
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		if (i != 1) cin >> c[i];
		cin >> a[i];
	}
	build(1, 1, n);
	for (int i = 1; i <= q; ++i) {
		int pos, nx;
		char nop;
		cin >> pos >> nop >> nx;
		update(1, 1, n, pos, nx, nop);
		cout << tr[1].cnt << '\n';
	}
	return 0;
}
```

---

## 作者：hjhAKIOI (赞：2)

## P11685 [Algo Beat Contest 001 G] Great DS Homework 题解

[题目链接](https://www.luogu.com.cn/problem/P11685)

这里贡献一个矩阵题解。

以下令 $a_i$ 表示第 $i$ 个数字，令 $b_i$ 表示第 $i$ 个数字前的运算符。特别地，$b_1$ 为空。

考虑没有修改怎么做。记 $f_i$ 表示以第 $i$ 个数字为结尾的表达式的值的和，那么可以得出以下转移方程：

1. $a_i=0,b_i$ 为 `&`。

   显然 $f_i=0$。
   
3. $a_i=0,b_i$ 为 `|`。

   或 $0$ 之后，所有表达式的值都不会变。故 $f_i=f_{i-1}$。
   
4. $a_i=0,b_i$ 为 `^`。

   异或 $0$ 之后，所有表达式的值都不会变。故 $f_i=f_{i-1}$。

5. $a_i=1,b_i$ 为 `&`。

   与 $1$ 之后，所有表达式的值都不会变。但 $a_i$ 本身也是一个表达式且值为 $1$，故 $f_i=f_{i-1}+1$。

6. $a_i=1,b_i$ 为 `|`。

   显然 $f_i=i$。

7. $a_i=1,b_i$ 为 `^`。

   异或 $1$ 之后，所有表达式的值都取反。而且$a_i$ 本身也是一个表达式且值为 $1$，故 $f_i=i-1-f_{i-1}+1=i-f_{i-1}$。

跑完 dp 以后，答案即为 $\sum_{i=1}^nf_i$。

那么每次修改后只要 $O(n)$ 的跑一次 dp 即可得到 $O(nq)$ 的算法，显然很劣。

我们可以考虑把所有的转移写成矩阵乘法的形式。可以用一个向量 $\begin{bmatrix}
 f_i & 1 & \sum_{j=1}^if_j
\end{bmatrix}$ 来转移。所有转移的矩阵也容易知道。例如对于第 $k$ 个位置，转移 6 的矩阵为：

$$
\begin{bmatrix}
 -1 & 0 & -1 \\
 k & 1 & k\\
 0 & 0 & 1
\end{bmatrix}
$$

其他请读者自行推导。

那么，修改一个 $a_i$ 和 $b_i$ 只会影响一个矩阵。于是可以用线段树来维护 $2\sim n$ 的矩阵乘积，再用一个向量 $\begin{bmatrix}
 a_1 & 1 & a_1
\end{bmatrix}$ 乘上这个乘积即可。答案即为最终乘积的第三维。

单次修改的时间复杂度为 $O(t^3\log{n})$，其中 $t=3$。总时间复杂度为 $O(t^3n+t^3q\log{n})$。由于有 $27$ 的常数，跑得并不快，但不需要卡常。

一个细节是矩阵下标得从 $0$ 开始，不然会爆空间 QAQ。

代码如下：
```cpp
#include<iostream>
#include<cstring>
#define int long long
using namespace std;
const int N=1e6+5;
int n,m;
char num[N],op[N];

struct Mat{
	int r,c;
	int a[3][3];
	Mat(){ r=c=0,memset(a,0,sizeof(a));}
	Mat operator*(const Mat &o){
		Mat res;
		res.r=r,res.c=o.c;
		for(int i=0;i<r;i++){
			for(int j=0;j<o.c;j++){
				for(int k=0;k<c;k++) res.a[i][j]+=a[i][k]*o.a[k][j];
			}
		}
		return res;
	}
	void init(int x,int i){
		a[0][1]=0,a[1][1]=1,a[2][1]=a[2][0]=0,a[2][2]=1;
		if(x==1) a[0][0]=a[1][0]=a[0][2]=a[1][2]=0;
		if(x==2) a[0][0]=a[1][0]=a[0][2]=a[1][2]=1;
		if(x==3||x==5) a[0][0]=a[0][2]=1,a[1][0]=a[1][2]=0;
		if(x==4) a[0][0]=a[0][2]=0,a[1][0]=a[1][2]=i;
		if(x==6) a[0][0]=a[0][2]=-1,a[1][0]=a[1][2]=i;
	}
}t[N<<2],f;

int id(char op,char num){
	if(op=='&') return num-'0'+1;
	if(op=='|') return num-'0'+3;
	if(op=='^') return num-'0'+5;
}

void up(int p){
	t[p]=t[p<<1]*t[p<<1|1];
}

void build(int p,int l,int r){
	t[p].r=t[p].c=3;
	if(l==r){
		t[p].init(id(op[l],num[l]),l);
		return;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	up(p);
}

void change(int p,int l,int r,int x){
	if(l==r){
		t[p].init(id(op[l],num[l]),l);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) change(p<<1,l,mid,x);
	else change(p<<1|1,mid+1,r,x);
	up(p);
}

signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		if(i>1) cin>>op[i];
		cin>>num[i];
	}
	build(1,2,n);
	f.r=1,f.c=3;
	f.a[0][0]=f.a[0][2]=num[1]-'0',f.a[0][1]=1;
	Mat ans;
	while(m--){
		int pos,y;
		char x;
		cin>>pos>>x>>y;
		if(pos==1) f.a[0][0]=f.a[0][2]=y,num[1]=y+'0';
		else{
			num[pos]=y+'0',op[pos]=x;
			change(1,2,n,pos);
		}
		ans=f*t[1];
		cout<<ans.a[0][2]<<endl;
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：2)

### 思路：

考虑线段树维护区间所有子表达式的值。

考虑合并两个区间，我们需要快速算出跨过端点的子表达式的贡献之和。

考虑维护 $nxt_i$ 表示若 $i$ 进入这个区间，出来的是什么；$L_i$ 表示若 $i$ 进入这个区间，有多少个前缀表达式使得值为 $1$；$R_i$ 表示有多少个后缀表达式的值为 $i$。

显然都可以轻松进行合并，那么跨过 $mid$ 的贡献是 $L_{lson, 0} R_{rson, 0} + L_{lson, 1} R_{rson, 1}$。

时间复杂度为 $O(WN \log N)$，其中 $W = 2$ 表示值域大小。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x, y) (x + y >= mod) ? (x + y - mod) : (x + y)
#define lowbit(x) x & (-x)
#define pi pair<ll, ll>
#define pii pair<ll, pair<ll, ll>>
#define iip pair<pair<ll, ll>, ll>
#define ppii pair<pair<ll, ll>, pair<ll, ll>>
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define full(l, r, x) for(auto it = l; it != r; ++it) (*it) = x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i, l, r) for(register int i = l; i <= r; ++i)
#define _For(i, l, r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 1e6 + 10;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct Node{
	int l, r;
	int nxt[2];
	int L[2], R[2];
	ll ans;
}X[N << 2];
char c;
int n, q, x, y;
int a[N];
char op[N];
char s[N << 1];
inline char get(){
	char c;
	while(1){
		c = getchar();
		if(c == '|' || c == '&' || c == '^')
		  break;
	}
	return c;
}
inline int get(int x, int y, char op){
	if(op == '|')
	  return x | y;
	else if(op == '&')
	  return x & y;
	else
	  return x ^ y;
}
inline void pushup(int k){
	X[k].ans = X[k << 1].ans + X[k << 1 | 1].ans;
	for(int i = 0; i < 2; ++i)
	  X[k].nxt[i] = X[k << 1 | 1].nxt[X[k << 1].nxt[i]];
	for(int i = 0; i < 2; ++i)
	  X[k].L[i] = X[k << 1].L[i] + X[k << 1 | 1].L[X[k << 1].nxt[i]];
	for(int i = 0; i < 2; ++i)
	  X[k].R[i] = X[k << 1 | 1].R[i] + X[k << 1].R[0] * (X[k << 1 |1].nxt[0] == i) + X[k << 1].R[1] * (X[k << 1 | 1].nxt[1] == i);
	for(int i = 0; i < 2; ++i)
	  X[k].ans += 1ll * X[k << 1].R[i] * X[k << 1 | 1].L[i];
}
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	if(l == r){
		for(int i = 0; i < 2; ++i){
			X[k].nxt[i] = X[k].L[i] = get(i, a[l], op[l]);
			X[k].R[i] = a[l] == i;
		}
		X[k].ans = a[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline void update(int k, int l){
	if(X[k].l == l && l == X[k].r){
		for(int i = 0; i < 2; ++i){
			X[k].nxt[i] = X[k].L[i] = get(i, a[l], op[l]);
			X[k].R[i] = a[l] == i;
		}
		X[k].ans = a[l];		
		return ;
	}
	int mid = (X[k].l + X[k].r) >> 1;
	if(l <= mid)
	  update(k << 1, l);
	else
	  update(k << 1 | 1, l);
	pushup(k);
}
bool End;
int main(){
	n = read(), q = read();
	scanf("%s", s + 1);
	a[1] = s[1] - '0';
	op[1] = '|';
	for(int i = 2; i <= (n << 1) - 1; ++i){
		if(i & 1)
		  a[(i + 1) >> 1] = s[i] - '0';
		else
		  op[(i >> 1) + 1] = s[i];
	}
	build(1, 1, n);
//	write(X[1].ans);
//	putchar('\n');
	while(q--){
		x = read(), c = get(), y = read();
		a[x] = y, op[x] = c;
		update(1, x);
		write(X[1].ans);
		putchar('\n');
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

