# XOR Inverse

## 题目描述

给定长度为 $n$ $(1\le n\le3\times 10^5)$ 的数列 $\{a_n\}$ $(0\le a_n\le 10^9)$，请求出最小的整数 $x$ 使 $\{a_n\oplus x\}$ 的逆序对数最少，其中 $\oplus$ 是异或

## 样例 #1

### 输入

```
4
0 1 3 2```

### 输出

```
1 0```

## 样例 #2

### 输入

```
9
10 7 9 10 7 5 5 3 5```

### 输出

```
4 14```

## 样例 #3

### 输入

```
3
8 10 3```

### 输出

```
0 8```

# 题解

## 作者：AFOier (赞：10)

因为是异或，所以先把所有数转化为二进制（以下“位”均指二进制位）.

从高到低一位一位地考虑，在第$i$位，统计前面位全部相等且第$i$位不等的数对和逆序对个数

若逆序对个数大于正序对个数，那么$x$的第$i$位应为$1$，否则为$0$

考虑01trie，可以$O(nlogn)$求上面的两个量

具体求法（$siz[i]$为以$i$为根的子树内数字个数）：

逆序对即在插入时若当前位为$0$，则当前节点逆序对数$+=siz[son[1]]$

数对即$siz[son[0]]*siz[son[1]]$

注意开$long long$统计答案
```
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5;
struct node {
	int son[2];
	ll siz, inv, num;
} a[N*30+11];
int tot, n, b[31], cnt, s, rt;
ll ans, x;
ll sum[31], Inv[31];
void ins(int &k, int w) {
	if(!k) k = ++tot;
	if(w < 0) {
		a[k].siz ++;
		return;
	}
	ins(a[k].son[b[w]], w-1);
	if(b[w] == 0) a[k].inv += a[a[k].son[1]].siz;
	a[k].siz = a[a[k].son[0]].siz + a[a[k].son[1]].siz;
	a[k].num = a[a[k].son[0]].siz * a[a[k].son[1]].siz;
}
void dfs(int k, int w) {
	if(!k || w < 0) return;
	sum[w] += a[k].num;
	Inv[w] += a[k].inv;
	dfs(a[k].son[0], w-1);
	dfs(a[k].son[1], w-1);
}
int main() {
	scanf("%d", &n); rt = 1; tot = 1;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &s);
		cnt = 0; memset(b, 0, sizeof(b));
		while(s) {
			b[cnt++] = s % 2;
			s /= 2;
		}
		ins(rt, 30);
	}
	dfs(rt, 30); 
	for(int i = 30; i >= 0; i--) {
		if(Inv[i] > sum[i] - Inv[i]) x += (1 << i), ans += sum[i] - Inv[i];
		else ans += Inv[i];
	}
	cout << ans << " " << x << endl;
	return 0;
}
```

---

## 作者：AlanSP (赞：6)

### Description
>给定一个长度为n的序列a，找到一个x $x\le 10^9$，让每个a中的元素异或x得到序列b，求b的最小逆序对数以及此时x的取值。
> $n\le 3\times10^5$
---
### Soluton

看到异或，我们可以想到对原序列建立01trie。

将每个元素依次插入trie，并在插入的路径上维护插入元素的下标。

如果 $i$ 节点有插入的值 $v$ 经过，那么就在他所在节点上插入 $v$ 的下标。

不难发现下标一定是递增的，这为求逆序对提供了很好的基础。

对于01trie上的一个确定的节点，经过它右儿子的数一定严格大于左儿子。

因为他们的前几位是相同的，大小关系由不同位中最高的一位决定。

再利用我们之前维护的节点下标，那么我们可以很轻易的求出当前节点贡献的逆序对数，即右儿子下标小于左儿子下标的对数。

如果求出的 $x$ 的当前位是0，那么对答案没有影响。

反之，那么左右儿子维护的下标对调。

这样的话，当前的逆序对数=总对数-原逆序对数。

在对每个节点求出这样的贡献后，我们就可以贪心并求出交换次数了。

**如果当前位调换比不调换优，就把 $x$ 的当前位赋为 $1$。**

这道题就结束了。
---
### Code:
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define ll long long
const int N = (3e5+9)*30;
int tr[2][N];
ll f[2][39],ans,inv;
vector<int> pos[N];
int n,a[N],cnt=1;

inline void insert(int x,int v,int p,int k)
{
	if(k<0) return;
	int c=(v>>k)&1;
	if(!tr[c][x]) tr[c][x]=++cnt;
	pos[tr[c][x]].push_back(p);
	insert(tr[c][x],v,p,k-1);
}

void dfs(int u,int p)
{
	int ls=tr[0][u],rs=tr[1][u];
	if(ls) dfs(ls,p-1);
	if(rs) dfs(rs,p-1);
	if(!ls&&!rs) return;
	int num=0;
	ll res=0;
	for(auto i:pos[ls])
	{
		while(num<pos[rs].size()&&pos[rs][num]<i) ++num;
		res+=num;
	}
	f[0][p]+=res;
	f[1][p]+=1ll*pos[ls].size()*pos[rs].size()-res;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
		insert(1,a[i],i,29);
	}
	dfs(1,29);
	for(int i=29;i>=0;i--)
	{
		inv+=min(f[0][i],f[1][i]);
		if(f[1][i]<f[0][i])
			ans|=(1<<i);
	}
	printf("%lld %lld",inv,ans);
	return 0;
}
```

---

## 作者：Gmt丶FFF (赞：4)

一道十分不错的分治题。

因为要进行异或操作，所以先将所有数拆成二进制数。

可以知道的是对于每一个二进制数，比较时是先比较最高位，然后接着往下面比，直到同一位上一个为 $1$，一个为 $0$。

所以对于每两个不相同的二进制数，只要对它们第一个不同的地方异或 $1$，即可交换两数大小。

那么我们可以从 $2^{30}$ 往下找，找到每一位上对应的数字为 $1$ 或 $0$。

由于每一位上只有 $0$ 与 $1$，所以可以 $O(n)$ 处理出来这一位上的顺序对与逆序对个数，顺序即是将这一位异或 $1$ 后的逆序对个数。如果顺序对的个数小于逆序对的个数，说明异或 $1$ 以后得到的解更优，就将答案累计上。

统计完一个数位以后，会将所有数以此位上的数字分成 $0$ 和 $1$，那么这些数字因为这个位上相同，所以要比较下一位，那么再利用 $O(n\log{n})$ 的复杂度进行排序，然后分别处理 $0$ 与 $1$ 的区间。最后将下一位的逆序对与顺序对的个数累加，再判断顺序对是否大于逆序对个数，再累加答案即可。

最后求出异或的数 $x$ 后，将 $a_i$ 异或上 $x$,最后离散化加树状数组统计逆序对个数。

递归实现，利用了分治思想，复杂度 $O(30\times n\log{n})$。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#define int long long 
using namespace std;
const int N=3e5+5;
int n,a[N],ans,f[N],cnt,p1[35],p2[35];
struct node
{
	int data,name;
}t[N],s[N];
int cmp(node fi,node se)
{
	if(fi.data==se.data)return fi.name<se.name;
	return fi.data<se.data;
}
int cmp2(node fi,node se)
{
	return fi.name<se.name;
}
inline int lowbit(int x)
{
	return x&-x;
}
void update(int x)
{
	while(x)
	{
		f[x]++;
		x-=lowbit(x);
	}
}
int search(int x)
{
	int sum=0;
	while(x<=cnt)
	{
		sum+=f[x];
		x+=lowbit(x);
	}
	return sum;
}
void dfs(int i,int beg,int ed)
{
	if(beg>=ed)return;
	if(i<0)return;
	bool ss=((a[beg]&(1<<i)));
	int bef=beg,sum1=0,sum2=0,tot1=0,tot2=0;
	for(int j=beg;j<=ed;j++)
	{	
		int x=s[j].name;
		if(((a[x]&(1<<i))>0)!=ss)
		{
			if(ss==1)tot1+=sum2*(j-bef);
			if(ss==0)tot2+=sum1*(j-bef);
			ss=((a[x]&(1<<i)));
			bef=j;
		}
		sum1+=((a[x]&(1<<i))>0),sum2+=((a[x]&(1<<i))==0);
		s[j].data=((a[x]&(1<<i))>0);
	}
	sort(s+beg,s+ed+1,cmp);
	if(ss==1)tot1+=sum2*(ed-bef+1);
	if(ss==0)tot2+=sum1*(ed-bef+1);
	dfs(i-1,beg,ed-sum1);
	dfs(i-1,beg+sum2,ed);
	p1[i]+=tot1;
	p2[i]+=tot2;
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]),s[i].name=i;
	dfs(30,1,n);
	for(int i=0;i<=30;i++)if(p2[i]>p1[i])ans^=(1<<i);
	for(int i=1;i<=n;i++)
	{
		t[i].name=i;
		t[i].data=a[i]^ans;
	}
	sort(t+1,t+1+n,cmp);
	int bef=-1;
	for(int i=1;i<=n;i++)
	{
		if(t[i].data!=bef)cnt++;
		bef=t[i].data;
		t[i].data=cnt;
	}
	sort(t+1,t+1+n,cmp2);
	int tot=0;
	for(int i=1;i<=n;i++)
	{
		tot+=search(t[i].data+1);
		update(t[i].data);
	}
	printf("%lld %lld",tot,ans);
	return 0;
}
```


---

## 作者：Keids (赞：3)

# CF1416C XOR Inverse题解
原题链接 https://www.luogu.com.cn/problem/CF1416C

看题解多是 01tree，于是写了一份暴力的算法(也更好理解）。

首先读题，题干要求我们从在范围内找到一个 $x$，对数列 $a$ 的每个元素异或 $x$，使得异或后的 $a$ 数组的逆序对最小。

最简单的暴力思想是直接枚举 $x$，但是很明显数据范围要炸。

所以我们考虑如何优化枚举的过程。

我们观察一个数异或上另一个数，每次异或，都是对当前位置产生影响，而不会影响后面或前面的位置，所以对于一个数的异或，我们考虑在二进制下进行。

考虑所有数字的二进制表达。

我们先关注最高位，只有 $0$，$1$ 两种数字。

我们异或上去的这个数字，要么在这一位是 $0$，也就不改变这一位的数字；

要么异或上去这个数字，在这一位是 $1$，就会使得最高位 $0$ 变 $1$，$1$  变 $0$ 。

目前看来，就这两种情况。

1. 那么我们先考虑这两种情况会产生的逆序对数目，在只关注最高位的情况下，我们只知道，最高位为 $1$ 的数字，一旦出现在了最高位为 $0$ 的数字前面，那么他们一定形成逆序对。

2. 而对于最高位相同的数字，由于我们目前只关注最高位，所以我们看不出它们的差异。

因此我们目前只用考虑第 $1$ 种情况下的逆序对数目，来确定最高位到底是异或  $0$ 还是 $1$ 更优。

从 $2$ 的 $32$ 次方开始枚举，可以完全覆盖需求。

定义一个数 $xo$ 表示最后的答案，最开始令 $xo$ 为 $0$ 。

从 $2$ 的 $32$ 次方开始枚举每一位数，先令 $xo$ 加上这个数，让 $xo$ 对 $a$ 数组进行异或操作，判断结果是否更优。如果更优，则保留加上的这一位，否则去掉。然后继续枚举到 $2$ 的 $0$ 次方，这样我们就得到了结果。过程中记录一下逆序对个数最小值，输出即可。

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
ll a[500010],c[500010];
ll ans,minn,xo;
ll b[500010];
int n;
void msort(int x,int y)//归并排序求逆序对
{
    if(x==y)  return;
    int mid=(x+y)/2,i=x,j=mid+1,k=x;
    msort(x,mid),msort(mid+1,y);
    while(i<=mid&&j<=y){	 
    	if(a[i]<=a[j])c[k++]=a[i++];
    	else c[k++]=a[j++],ans+=mid-i+1;
    }	
    while(i<=mid)c[k++]=a[i++];
    while(j<=y)c[k++]=a[j++];
    for(int i=x;i<=y;i++)a[i]=c[i];
} 
void deal(){//复原a，c数组
	for(int i=1;i<=n;i++){
		a[i]=b[i];
	}
	memset(c,0,sizeof(c));
}
int main()
{
    scanf("%d",&n); 
    for(int i=1;i<=n;i++)scanf("%lld",&b[i]),a[i]=b[i];
    ll xx=2147483648;//枚举起点
    msort(1,n); deal();//初始化
    minn=ans;//记录最开始的值
    for(int i=31;i>=0;i--){
		ans=0;   //每次先把ans复原，用来存储逆序对个数
		xo^=xx;  //xo+=xx
		for(int j=1;j<=n;j++){
			a[j]^=xo; //暴力修改每一个数
		}
		msort(1,n);deal();//求值并复原
		if(ans<minn){//如果更优则替换
			minn=ans;
			xo^=xx;//因为下面操作还要异或一次，所以这里必须先进行一次
		}
		xo^=xx;//不优则复原
		xx>>=1;//枚举下一位
	} 
    printf("%lld %lld",minn,xo);
    return 0;
}
```
（谢谢dottle老师教我写题解的格式！）

---

## 作者：ケロシ (赞：2)

## 解题思路

本题要求一个数列加上 $x$ 后逆序对的最小值。

不难想到两个数的大小比较取决去最高不同的数位的值，所以考虑构建 01trie。

先把所有的数插进 trie 中，先记录每一个子树的所有经过的数，随后构建 dp 数组 $f_{i,0}$，$f_{i,1}$ 分别表示第 $i$ 位为零的逆序对的个数和第 $i$ 位为一的逆序对的个数。

然后遍历整个 trie，随后用左指针统计 $f_{i,0}$，$f_{i,1}$。

最后，逆序对的个数就为每一位逆序对的最小值的和，即为 $\sum_{i=0}^{30}\min(f_{i,0},f_{i,1})$。

当这一位为零的逆序对大于为一的逆序对后，就需要 $x$ 来进行反转，则 $x$ 的值为 $\sum_{i=0}^{30}[f_{i,0}>f_{i,1}] \times 2^i$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 3e5 + 5;
const int M = 30;
int n,a[N];
int t[N*M][2],idx;
vector<int>g[N*M];
ll f[M + 1][2];
void insert(int x,int rt) { // 01trie
    int pos = 0;
    for(int i=M;i>=0;i--) {
        int u = (x >> i) & 1;
        if(!t[pos][u]) t[pos][u] = ++idx; 
        pos = t[pos][u];
        g[pos].push_back(rt);
    }
}
void dfs(int pos,int u) {
    int tl = t[pos][0], tr = t[pos][1];
    if(!tl && !tr) return;
    if(tl) dfs(tl, u - 1);
    if(tr) dfs(tr, u - 1);
    ll res = 0;
    int pl = 0; // 左指针计算逆序对个数
    for(int i=0;i<g[tl].size();i++) {
        while(pl < g[tr].size() && g[tr][pl] < g[tl][i]) pl++;
        res += pl;
    }
    f[u][0] += res;
    f[u][1] += 1ll * g[tl].size() * g[tr].size() - res;
}
void solve() {
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) insert(a[i], i);
    dfs(0, M);
    ll ans1 = 0;
    int ans2 = 0;
    for(int i=0;i<=M;i++) {
        ans1 += min(f[i][0], f[i][1]);
        if(f[i][1] < f[i][0]) ans2 += 1 << i;
    }
    cout << ans1 << " " << ans2 << endl;
}
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
```



---

## 作者：KellyFrog (赞：2)

用一种类似 CDQ 的思路（比赛的时候看有人写了 CDQ）。

对于当前的一个数列，我们先讨论最高位，然后递归计算接下来的低位。

对于逆序对，有这么几种：

- 当前位都是 0 或 都是 1 的逆序对 ——这个我们递归调用
- 当前位有 0 有 1 的逆序对——显然我们只关心这一位的大小关系，因为当前位是 0 或 1 的内部逆序对会被上面一种情况讨论到

如果我们这一位 $\operatorname{xor}$ 了一个 1，那么原来有 0 有 1 的顺序对就会变成逆序对，所以我们分别做顺序对和逆序对存起来最后比一下就行了。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define int long long

using namespace std;

const int N = 3e5 + 5;

typedef long long ll;
typedef vector<int> vi; 

#define pb push_back

int n;
ll dp[N][2];

void Solve(vi& cur, int p) {
	if(p < 0 || cur.size() == 0) {
		return;
	}
	int cnt1 = 0, cnt2 = 0;
	int ans1 = 0, ans2 = 0;
	vi left, right;
	for(int x : cur) { 
		if((x >> p) & 1) {
			ans2 += cnt1;
			cnt2++;
			right.pb(x);
		} else {
			ans1 += cnt2;
			cnt1++;
			left.pb(x);
		}
	}
	dp[p][0] += ans2;
	dp[p][1] += ans1;
	Solve(left, p-1), Solve(right, p-1);
}

signed main() {
	cin >> n;
	vi a(n);
	for(int& x : a) {
		cin >> x;
	}
	reverse(a.begin(), a.end());
	
	Solve(a, 30);
	ll res = 0, ans = 0;
	for(int i = 0; i <= 30; i++) {
		if(dp[i][0] <= dp[i][1]) {
			ans += dp[i][0];
		} else {
			ans += dp[i][1];
			res += 1 << i;
		}
	}
	cout << ans << " " << res << endl;
	return 0;
}
```

---

## 作者：Logey (赞：2)

给一个 $Trie$ 树的做法。

一个逆序对要满足大小和位置的偏序关系。

从二进制的角度考虑大小关系。考虑 $a_i > a_j$，时，这两个数的二进制表示必然有一个极长的公共前缀，然后 $a_i$ 的下一位变成了 $1$， $a_j$ 的下一位变成了 $0$。

再考虑如果 $x$ 某个二进制位是 $1$ 的话，就意味着这一位的大小关系翻转了。对于一对 $a_i, a_j$，如果翻转他们的公共前缀，是不影响大小关系的。

所以用 $Trie$ 分别统计每个二进制位上产生的逆序对和顺序对个数，取个最小值就可以了。


```cpp

void ins(int u, int a) {
    per(i, 30, 0) {
        int k = (a >> i) & 1;
        if (!ch[u][k]) ch[u][k] = ++tot;
        s[u]++;
        u = ch[u][k];
    }
    s[u]++;
}

void query(int u, int a) {
    per(i, 30, 0) {
        int k = (a >> i) & 1;
        cc[i][k ^ 1][k] += s[ch[u][k ^ 1]];

        if (!ch[u][k]) break;
        u = ch[u][k];
    }
}

signed main() {
    rd(n);
    rep(i, 1, n) rd(a[i]), query(1, a[i]), ins(1, a[i]);
    int x = 0;
    ll ans = 0;
    per(i, 30, 0) {
        if (cc[i][1][0] > cc[i][0][1]) x |= (1 << i), ans += cc[i][0][1];
        else ans += cc[i][1][0];
    }
    printf("%lld %lld\n", ans, x);
    return 0;
}
```

---

## 作者：__ryp__ (赞：1)

看到题解区大神都写了 01 trie / 分治，根本看不懂，怎么办！

但是不要急！**本题可以用根本没有思维含量的小常数基数排序 + 树状数组 $O(n\log n \log V)$ 狠狠草过去**！

**这就是基数排序带给我的自信**

---

我们直接狠狠贪心，从高到低枚举每一位，然后计算异或上这一位或是不异或的逆序对数。如果变少了，就直接选上这一位。然后就做完了。

**但是……**

如果你就这样天真的写了一颗平衡树 / 离散化 + 树状数组交上去，**就会发现出题人狠狠的草爆了你的码**！

**但是！**

众所周知，存在一种叫做基数排序的东西……它可以用线性的时间把一堆整数排序。

我们这里的问题是，离散化的速度太慢，是个线性对数。考虑到可以用基数排序替代快速排序 + 二分进行离散化，于是我们就做完了。

附一个基数排序离散化模板，它是本题的大功臣！

```c++
void radix_sort (int n)
{
	int mx = 0;
	for (int i = 1; i <= n; i++) ww[i] = { w[i], i };
	for (int i = 1; i <= n; i++) q[w[i] & 0x7fff]++, mx = max (mx, w[i] & 0x7fff);
	for (int i = 1; i <= mx; i++) q[i] += q[i - 1];
	for (int i = n; i >= 1; i--) rr[q[w[i] & 0x7fff]--] = ww[i];
	for (int i = 0; i <= mx; i++) q[i] = 0;
	mx = nr = 0;
	for (int i = 1; i <= n; i++) q[rr[i].fi >> 15]++, mx = max (mx, rr[i].fi >> 15);
	for (int i = 1; i <= mx; i++) q[i] += q[i - 1];
	for (int i = n; i >= 1; i--) ww[q[rr[i].fi >> 15]--] = rr[i];
	for (int i = 0; i <= mx; i++) q[i] = 0;
	for (int i = 1; i <= n; i++) w[ww[i].se] = nr += i == 1 || ww[i].fi != ww[i - 1].fi;
}
```

以及 [Submission](https://codeforces.com/contest/1416/submission/281990854)

---

## 作者：_ldyex_ (赞：1)

## 题目

[戳这里](https://www.luogu.com.cn/problem/CF1416C)

## 解决方法

这道题有异或和逆序对，我们一个一个地解决。

### 逆序对

逆序对要用分治的方法，和归并排序很像（解析在模板中），看模板：
```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 1;

int n, q[maxn], tmp[maxn];
long long res;       

void qsort(int q[], int l, int r){
  if(r <= l) return ;
  int k = 0, mid = (l + r) >> 1, i = l, j = mid + 1;
  qsort(q, l, mid), qsort(q, mid + 1, r);        //分
  while(i <= mid && j <= r){						
    if(q[i] <= q[j]){                    //治
      tmp[++k] = q[i++];
    }
    else{
      tmp[++k] = q[j++];
      res += mid - i + 1;                //如果这两个数为逆序对，
    }                                    //则其q[i]至q[mid]都会与其组成逆序对，
  }                                      //共有mid - i + 1个
  while(i <= mid) tmp[++k] = q[i++];     //将未处理的数加入数组
  while(j <= r) tmp[++k] = q[j++];
  for(int i = l; i <= r; i++){
    q[i] = tmp[i - l + 1];
  }
}

```

### 异或

异或的解决方法很简单，因为它是逐位异或，所以只要枚举 $30$ 次，看看如果将第 $i$ 位与 $1$ 异或后能使结果变得更优，便将其加入答案。

### 注意事项：
如果数组中的数以降序排列，则逆序对数量会爆 ```int```，要开 ```long long```!


## Code

```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn = 3e5 + 1;

int n, a[maxn], q[maxn], tmp[maxn], ans;
long long res, cnt = LLONG_MAX; //不开longlong见祖宗

void qsort(int q[], int l, int r){
  if(r <= l) return ;
  int k = 0, mid = (l + r) >> 1, i = l, j = mid + 1;
  qsort(q, l, mid), qsort(q, mid + 1, r);
  while(i <= mid && j <= r){
    if(q[i] <= q[j]){
      tmp[++k] = q[i++];
    }
    else{
      tmp[++k] = q[j++];
      res += mid - i + 1;
    }
  }
  while(i <= mid) tmp[++k] = q[i++];
  while(j <= r) tmp[++k] = q[j++];
  for(int i = l; i <= r; i++){
    q[i] = tmp[i - l + 1];
  }
}

long long sum(int q[], int x){
  res = 0;
  qsort(q, 1, x);
  return res;
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
    q[i] = a[i];
  }
  cnt = sum(q, n);
  for(int i = 0; i <= 30; i++){  //枚举每一位，并将其与1异或
    int x = (1 << i);			
    for(int j = 1; j <= n; j++){
      q[j] = a[j] ^ x;
    }
    if(sum(q, n) < cnt){
      ans += x;    
    }
  }
  for(int j = 1; j <= n; j++){
    q[j] = a[j] ^ ans;
  }
  cout << sum(q, n) << ' ' << ans;
  return 0;
}
```



---

## 作者：封禁用户 (赞：1)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1416C)

[CF](https://codeforces.com/problemset/problem/1416/C)

### 分析

由于逆序对要求 $i < j$ 且 $a_i > a_j$，我们从二进制位的高位到低位考虑，可以发现，如果已经开始考虑某位二进制位，它的前面的所有位必须都相等。

我们维护 01 字典树，每次插入一个数，求出它在每个二进制位产生的顺序对和逆序对个数。

如果该二进制位逆序对个数大于顺序对个数，则异或以下逆序对或更少，答案的这一个二进制位为 $1$，否则，答案的这一个二进制位为 $0$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define N 300010
int a[N],n;
ll sum[35][2];
struct Trie
{
	int son[N<<5][2],sz[N<<5],cnt;
	Trie() {cnt = 1;}
	int update(int u,int dep,int num)
	{
		if(!u) u = ++cnt;
		++sz[u];
		if(dep < 0) return u;
		int t = (num>>dep)&1;
		son[u][t] = update(son[u][t],dep-1,num);
		return u;
	}
	void calc(int u,int dep,int num)
	{
		if(!u||dep < 0) return;
		int t = (num>>dep)&1;
		sum[dep][t] += sz[son[u][t^1]];
		calc(son[u][t],dep-1,num);
	}
}tree;
int main()
{
	read(n);
	F(i,1,n)
	{
		read(a[i]);
		tree.calc(1,30,a[i]);
		tree.update(1,30,a[i]);
	}
	ll ans1 = 0;
	int ans2 = 0;
	D(i,30,0)
	{
		if(sum[i][0] > sum[i][1])
		{
			ans2 |= 1<<i;
			ans1 += sum[i][1];
		}
		else ans1 += sum[i][0];
	}
	write(ans1),putchar(' '),write(ans2);
	return 0;
}

```


---

## 作者：Tenshi (赞：1)

~~这题是我练 CF DP 标签题目的时候遇到的，但我做完之后根本没见到 DP 的影子啊。。~~

## 分析

考虑从高位到低位拆位决策。

从最高位考虑起，记为第 $k$ 位。

采取分治的思想，只考虑第 $k$ 位造成的贡献，也就是说，我们可以将第 $k$ 位为 $0, 1$ 的数分成 $l, r$ 两份，可以发现二者的逆序对数贡献互不干扰，递归下去即可。

现在的问题转化为给你一个 $0, 1$ 序列，然后统计逆序对数，结果记为 $fir$。

这个问题很简单，我们就统计每次枚举到 $0$ 的时候前缀有多少个 $1$ 即可。

然后我们将原 $0, 1$ 序列取反，再统计一次逆序对数，作为第 $k$ 位如果选择取反后的逆序对数，记为 $sec$。

最后做个贪心，假如第 $k$ 层所有 $fir$ 的和**小于等于** $sec$ 的和，那就没必要取反，否则为了最小化逆序对数必须取反。

## 实现

```cpp
// Problem: C. XOR Inverse
// Contest: Codeforces - Codeforces Round #673 (Div. 1)
// URL: https://codeforces.com/problemset/problem/1416/C
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
 
#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define pb push_back
#define all(x) (x).begin(), (x).end()
 
#define x first
#define y second
using ll = long long;
using pii = pair<ll, ll>;
 
inline void read(int &x){
    int s=0; x=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0' && ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=3e5+5;

int n;
vector<int> w;
ll res, det;
vector<pii> c[35];

void solve(vector<int> &w, int k){
	if(k==-1 || !w.size()) return;
	vector<int> l, r;
	vector<int> b;
	int n=w.size();
	rep(i, 0, n-1){
		int val=w[i]>>k&1;
		b.pb(val);
		if(!val) l.pb(w[i]);
		else r.pb(w[i]);
	}
	int cnt=0;
	ll fir=0, sec=0;
	
	for(auto &i: b){
		if(i) cnt++;
		else fir+=cnt;
		i^=1;
	}
	cnt=0;
	for(auto &i: b){
		if(i) cnt++;
		else sec+=cnt; 
	}
	c[k].pb({fir, sec});
	solve(l, k-1), solve(r, k-1);
}

signed main(){
	cin>>n;
	w.resize(n);
	rep(i, 0, n-1) read(w[i]);
	solve(w, 30);
	rep(i, 0, 30){
		ll fir=0, sec=0;
		for(auto [x, y]: c[i]) fir+=x, sec+=y;
		if(fir>sec) det|=(1<<i);
		res+=min(fir, sec);
	}
	cout<<res<<" "<<det<<endl;
	
	return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## solution

ChiFAN 是 $\log^2$ 的，致敬传奇 DS 神。

但是这道题并不需要用到高级数据结构。

首先我们把所有数丢到 Trie 上，然后发现目前所有数的逆序对个数其实就变成了 Trie 树上从左到右的下标逆序对个数，因为最高不相同的一位已经决定了两个数 $x, y$ 的大小，我们规定 $0$ 子树在左，$1$ 子树在右。

然后我们再考虑异或上 $x$ 怎么解决，发现其实在 Trie 树上的描述很简单，如果 $x$ 第 $dep$ 位为 $1$，那么我们将 Trie 树上的第 $dep$ 层全部 $0, 1$ 翻转，否则我们就不动。

然后我们发现 Trie 树上求下标逆序对有个类似归并的写法，可以快速求出逆序对，**而且最重要的是他可以将第 $dep$ 层分拆开来处理**，因为 Trie 树本身就侧面是一个描述大小的工具，我们只需要考虑相同前缀的数的逆序对即可。

于是你求出每个结点的逆序对和顺序对，如果逆序对比顺序对大就肯定要翻转这一层，否则不需要翻转。仔细分析一下发现这种归并做法时空复杂度均为 $O(n \log V)$，不过我们并不需要直接写归并，那样太狗屎了，我们用类似标记永久化的方式来维护，具体细节见代码。

## code

code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 3e5 + 5;

int n, cnt, rt, ans, ans2;
int a[N], p[N], sum[N];

struct Node {
  int ch[2], siz;
} trie[N * 32];

void insert ( int &node, int x, int dep ) {
  if ( !node ) {
    node = ++ cnt;
  }
  trie[node].siz ++;
  if ( dep == -1 ) {
    return ;
  }
  insert ( trie[node].ch[( x >> dep ) & 1], x, dep - 1 );
  if ( !( ( x >> dep ) & 1 ) ) {
    p[dep] += trie[trie[node].ch[1]].siz;
  }
}

void dfs ( int node, int dep ) {
  if ( !node ) {
    return ;
  }
  dfs ( trie[node].ch[0], dep - 1 ), dfs ( trie[node].ch[1], dep - 1 );
  sum[dep] += trie[trie[node].ch[0]].siz * trie[trie[node].ch[1]].siz;
}

void Solve () {
  cin >> n;
  for ( int i = 1; i <= n; i ++ ) {
    cin >> a[i];
    insert ( rt, a[i], 31 );
  }
  dfs ( rt, 31 );
  for ( int i = 0; i <= 31; i ++ ) {
    if ( p[i] > sum[i] - p[i] ) {
      ans |= ( 1 << i );
      ans2 += sum[i] - p[i];
    }
    else {
      ans2 += p[i];
    }
  }
  cout << ans2 << " " << ans;
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

---

## 作者：lfxxx (赞：0)

由于要两个数异或上 $x$ 后比较大小，所以我们在二进制下看比大小。

不难发现就是二进制下找到两个数最长公共前缀后比较后一位。

那么假若在前面的一个数最长公共前缀后一位是 $1$，在后面的一个数最长公共前缀后一位是 $0$，那么当 $x$ 这一位是 $1$ 时这是顺序对，否则是逆序对。

那么将所有数插入 trie 后在 trie 上以数在原序列中下标做线段树合并，并在这个过程中计算左右儿子带来的贡献，这些贡献形如 $x$ 某一位是 $0/1$ 带来多少个逆序对，由于 $x$ 每一位之间独立，所以每一位都贪心的选择最少的即可。

时间复杂度 $O(n \times (\log n + \log V))$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5+114;
int rot[maxn*31],ls[maxn*31],rs[maxn*31];
int tr[maxn*31],lson[maxn*31],rson[maxn*31];
int tot,tt;//trie sgt
int root;
long long val[31][2];
int a[maxn],n;
void add(int &cur,int lt,int rt,int pos){
    if(cur==0) cur=++tt;
    tr[cur]++;
    if(lt==rt) return ;
    int mid=(lt+rt)>>1;
    if(pos<=mid) add(lson[cur],lt,mid,pos);
    else add(rson[cur],mid+1,rt,pos);
}
long long ans;
int merge(int u,int v,int lt,int rt){
    if(u==0||v==0) return u+v;
    //0 1
    tr[u]+=tr[v];
    if(lt==rt){
        return u;
    }
    ans+=1ll*tr[rson[u]]*tr[lson[v]];
    int mid=(lt+rt)>>1;
    lson[u]=merge(lson[u],lson[v],lt,mid);
    rson[u]=merge(rson[u],rson[v],mid+1,rt);
    return u;
}
void ins(int x,int pos){
    int u=root;
    for(int i=30;i>=0;i--){
        if((1<<i)&x){
            if(rs[u]==0) rs[u]=++tot;
            u=rs[u];
        }else{
            if(ls[u]==0) ls[u]=++tot;
            u=ls[u];
        }
    }
    add(rot[u],1,n,pos);
}
void solve(int u,int h){
    if(u==0) return ;
    solve(ls[u],h-1);
    solve(rs[u],h-1);
    if(ls[u]!=0&&rs[u]!=0){
        ans=0;
        val[h][1]+=1ll*tr[rot[ls[u]]]*tr[rot[rs[u]]];
        rot[ls[u]]=merge(rot[ls[u]],rot[rs[u]],1,n);
        val[h][0]+=ans;
        val[h][1]-=ans;
        rot[u]=merge(rot[u],rot[ls[u]],1,n);
    }else{
        rot[u]=merge(rot[u],rot[ls[u]],1,n);
        rot[u]=merge(rot[u],rot[rs[u]],1,n);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    root=++tot;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],ins(a[i],i);
    solve(root,30);
    long long sum=0,X=0;
    for(int i=30;i>=0;i--){
        if(val[i][0]<=val[i][1]) sum+=val[i][0];
        else sum+=val[i][1],X+=(1<<i);
    }
    cout<<sum<<' '<<X<<'\n';
}
```

---

## 作者：KMYC (赞：0)

[$\textbf{题目传送门}$](https://www.luogu.com.cn/problem/CF1416C)

基本思路:

由题目易得：我们需要考虑两个数什么时候会成为逆序对。

其实就是看是否满足 $a_i⊕x>a_j⊕x∧i<j$，我们用二进制的思维去考虑最高位决定大小关系。设 $a_i,a_j$ 的第一个不同的数位是 $d$，那么它们一定会在 $x$ 的 $d$ 这一位判断出大小，如果 $a_i$ 这一位为 $1$，$a_j$ 这一位为 $0$，那么 $x$ 这一位为 $0$ 的时候一定有逆序对,否则一定没有。

所以，每一对数是否产生逆序对是在某一位上决定的，我们可以只统计出这些数对第一个不同的数位，就可以逐位确定 $x$ 了，统计的过程可以用树实现，时间复杂度大概为 $\text{O(n\ log\ n)}$。

---

## 作者：Doubeecat (赞：0)

> [CF1416C XOR Inverse](http://codeforces.com/problemset/problem/1416/C)
>
> 给定长度为 $n$ 的数列 $\{a_n\}$，请求出最小的整数 $x$ 使 $\{a_n\oplus x\}$ 的逆序对数最少
> 
> $n\le3\times 10^5,0\le a_n\le 10^9$

<!-- more -->

## 解题思路：

~~和学长一起打的训练赛，喜提 rank 27.~~

首先观察到跟异或有关，就立刻要想到 **0-1 trie**。

把所有数丢到 0-1 trie 上开始考虑怎么处理。

我们思考一下怎么才会产生逆序对，在我们顺序插入的过程中，有一个性质是**右子树上的数是严格大于左子树上的数**。

这启发我们在顺序插入的过程中记录一下经过每个点的数个数，记为 $siz_p$，那么接下来考虑按层进行一个贪心构造。

$f_{i,0/1}$ 表示在第 $i$ 层走 $0$ 或者 $1$ 时产生的逆序对个数。

假设我们当前插入数的二进制下第 $i$ 位为 $tmp$，则逆序对数会增加 $siz_{trie_{p}{tmp \oplus 1}}$，并且这个逆序对是因为你走了 $tmp \oplus 1$ 产生的，所以我们就有

$f_{i,tmp \oplus 1} += siz_{trie_{p}{tmp \oplus 1}}$

接下来我们按层处理，非常简单，只要比较一下当前层 $f_{i,0},f_{i,1}$ 哪个更小走哪边即可，注意如果走了 $0$，实际上是表示我们 $x$ 当前这位为 $1$，所以需要加上 $2^{dep}$.

考场上比较傻逼加了一个归并排序，实际上不用，走哪边加上哪边的 $f$ 就可以了。

时间复杂度 $O(n \log n)$

## 代码：

```cpp


const int N = 3e5 + 10;
const int K = 31;

int trie[N*K][2],tot,f[N*K][2],siz[N*K*2];

void insert(int x) {
    int p = 0;
    for (int i = 30;i >= 0;--i) {
        int tmp = ((x >> i)& 1);
        if (!trie[p][tmp]) trie[p][tmp] = ++tot;
        f[i][tmp ^ 1] += siz[trie[p][tmp ^ 1]];
        p = trie[p][tmp];
        ++siz[p];
    }
    return ;
}

int n,a[N],b[N],x,ans,tmp[N];

void merge(int l, int mid, int r) {
	if (l == r) return;
	if (l + 1 == r) {
		if (b[l] > b[r]) {
			ans++;
			swap(b[l], b[r]);
		}
		return;
	}
	merge(l, (l + mid) >> 1, mid);
	merge(mid + 1, (mid + 1 + r) >> 1, r);
	int i = l, j = mid + 1;
	for (int k = l; k <= r; k++)
		if (j > r || (i <= mid && b[i] <= b[j])) tmp[k] = b[i++];
		else {
			tmp[k] = b[j++];
			ans += mid - i + 1;
		}
	for (int k = l; k <= r; k++) b[k] = tmp[k];
}

signed main() {
    read(n);
    for (int i = 1;i <= n;++i) read(a[i]),insert(a[i]);
    for (int i = 30;i >= 0;--i) {
        if (f[i][1] > f[i][0]) {
            x += (1 << i);
        }
    }
    for (int i = 1;i <= n;++i) b[i] = a[i] ^ x;
    merge(1,(1 + n) >> 1,n);
    printf("%lld %lld\n",ans,x);
    return 0;
}
```

---

## 作者：11D_Beyonder (赞：0)

### Idea   
&emsp;&emsp;将每个数的二进制形式从高位到低位存在字典树中。我们考虑字典树的其中一棵子树 $T_{Sub}$，由于两个数的大小取决于它们二进制位上第一个不同的高位；因此，$T_{Sub}$ 的左子树里的所有数字都小于右子树中的数。只要枚举左子树里有多少数字下标比右子树的下标大，就能得到 $T_{Sub}$ 中的逆序对个数。  
&emsp;&emsp;接下来考虑贪心构造 $x$ 的过程。我们从低位到高位构造 $x$，每次考虑 $x$ 第 $i$ 位取 $0$ 或 $1$ 时产生的效果。假设当且考察到 $x$ 的第 $i$ 位，若 $x$ 的第 $i$ 位取 $0$，就表明保持所有数字的第 $i$ 位不变；若 $x$ 取 $1$，表面要取反所有数字的第 $i$ 位，即对换第 $i$ 层节点的左右儿子。
&emsp;&emsp;因此，我们需要开两个数组分别记录数字第 $i$ 位保持原样和取反产生的逆序对个数。自底向上遍历字典树节点并枚举其左右儿子包含数字的下标即可。  
### Code  
```cpp
/******************************************************************
Copyright: 11D_Beyonder All Rights Reserved
Author: 11D_Beyonder
Problem ID: CF1416C
Date: 9/29/2020
Description: 01-Trie
*******************************************************************/
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=5000006;
int tot;//Trie节点数量
int trie[N][2];
vector<int>ID[N];//节点表示数字的下标
int n;
ll f[N][2];//表示第i位保持不变或反转的逆序对个数
void insert(const int,const int);
void DFS(const int,const int);
int main(){
	cin>>n;
	int i;
	for(i=1;i<=n;i++){
		int temp;
		scanf("%d",&temp);
		insert(temp,i);
	}
	DFS(0,29);
	ll ans=0;
	int x=0;
	for(i=0;i<=29;i++){
		ans+=min(f[i][0],f[i][1]);
		if(f[i][1]<f[i][0]){
			x|=1<<i;//低位向高位构造
		}
	}
	cout<<ans<<' '<<x<<endl;
	return 0;
}
void insert(const int x,const int index){
	int p=0;
	for(register int i=29;i>=0;i--){
		const bool bit=(x>>i)&1;
		if(!trie[p][bit]){
			trie[p][bit]=++tot;
		}
		p=trie[p][bit];
		ID[p].push_back(index);//节点p包含的数字下标
	}
}
void DFS(const int x,const int bit){
	if(trie[x][0]){
		DFS(trie[x][0],bit-1);
	}
	if(trie[x][1]){
		DFS(trie[x][1],bit-1);
	}
	if(!trie[x][0]||!trie[x][1]){
		return;
	}
	ll sum=0;
	for(auto u:ID[trie[x][0]]){
		int p=trie[x][1];
		//ID中有序，直接二分计数
		sum+=lower_bound(ID[p].begin(),ID[p].end(),u)-ID[p].begin();
	}
	f[bit][0]+=sum;
	f[bit][1]+=1ll*ID[trie[x][0]].size()*ID[trie[x][1]].size()-sum;//容斥原理
}
```

---

## 作者：SSerxhs (赞：0)

考虑 $x$ 某一位为 $0,1$ 有什么区别

对于这一位相同的数而言是没有区别的，只会对这一位不同的数贡献，且对后面位数没有影响。所以只需要判断交换之后是否更优即可

注意两个数之间能在某一位贡献要求更高位的数字都相等（否则不能改变大小关系），所以要按照已经处理的二进制位分治处理

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pa;
const int N=3e5+2;
pa g[N];
int a[N],f[N],b[N];
ll ans[30],tot[30],ta;
int n,c,fh,i,anss;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
void sol(int l,int r,int m)
{
	if ((l>r)||(m==-1)) return;
	int i;
	f[l-1]=0;
	for (i=l;i<=r;i++) f[i]=f[i-1]+(a[i]>>m&1);
	for (i=l;i<=r;i++) ans[m]+=(1^(a[i]>>m&1))*f[i];
	for (i=l;i<=r;i++) g[i]=make_pair(a[i]>>m&1,i);
	sort(g+l,g+r+1);
	for (i=l;i<=r;i++) b[i]=a[g[i].second];
	for (i=l;i<=r;i++) a[i]=b[i];
	for (i=l;i<=r;i++) if (a[i]>>m&1) break;
	tot[m]+=(ll)(r-i+1)*(i-l);
	sol(l,i-1,m-1); sol(i,r,m-1);
}
int main()
{
	read(n);
	for (i=1;i<=n;i++) read(a[i]);
	sol(1,n,29);
	for (i=0;i<=29;i++) if ((ans[i]<<1)>(tot[i]))
	{
		anss|=(1<<i);ta+=tot[i]-ans[i];
	} else ta+=ans[i];
	printf("%lld %d",ta,anss);
}
```

---

