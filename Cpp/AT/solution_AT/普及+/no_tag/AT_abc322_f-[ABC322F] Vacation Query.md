# [ABC322F] Vacation Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc322/tasks/abc322_f

`0`, `1` からなる長さ $ N $ の文字列 $ S $ が与えられます。$ S $ の $ i $ 文字目を $ S_i $ とします。

$ Q $ 個のクエリを与えられた順に処理してください。  
 クエリは $ 3 $ 個の整数の組 $ (c,\ L,\ R) $ で表されて、$ c $ の値によってクエリの種類が異なります。

- $ c=1 $ のとき : $ L\ \leq\ i\ \leq\ R $ を満たす整数 $ i $ について、$ S_i $ が `1` ならば `0` に、`0` ならば `1` に変更する。
- $ c=2 $ のとき : $ S $ の $ L $ 文字目から $ R $ 文字目までを取り出して出来る文字列を $ T $ とする。$ T $ に含まれる連続する `1` の長さの最大値を出力する。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ S $ は長さ $ N $ の `0`, `1` からなる文字列
- $ c\ \in\ \lbrace\ 1,\ 2\ \rbrace $
- $ 1\ \leq\ L\ \leq\ R\ \leq\ N $
- $ N,\ Q,\ c,\ L,\ R $ は全て整数
 
### Sample Explanation 1

クエリを順に処理すると次のようになります。 - はじめ、$ S= $ `1101110` です。 - $ 1 $ 番目のクエリについて、$ T\ = $ `1101110` です。$ T $ に含まれる連続する `1` の中で最も長いものは、$ T $ の $ 4 $ 文字目から $ 6 $ 文字目からなる `111` なので、答えは $ 3 $ になります。 - $ 2 $ 番目のクエリについて、$ T\ = $ `101` です。$ T $ に含まれる連続する `1` の中で最も長いものは、$ T $ の $ 1 $ 文字目あるいは $ 3 $ 文字目の `1` なので、答えは $ 1 $ になります。 - $ 3 $ 番目のクエリについて、操作後の $ S $ は `1110000` です。 - $ 4 $ 番目のクエリについて、$ T\ = $ `00` です。$ T $ に `1` は含まれないので答えは $ 0 $ になります。 - $ 5 $ 番目のクエリについて、操作後の $ S $ は `1111111` です。 - $ 6 $ 番目のクエリについて、$ T\ = $ `1111111` です。$ T $ に含まれる連続する `1` の中で最も長いものは、$ T $ の $ 1 $ 文字目から $ 7 $ 文字目からなる `1111111` なので、答えは $ 7 $ になります。

## 样例 #1

### 输入

```
7 6
1101110
2 1 7
2 2 4
1 3 6
2 5 6
1 4 7
2 1 7```

### 输出

```
3
1
0
7```

# 题解

## 作者：lzyqwq (赞：6)

ABC 居然出板子题。

**[AT](https://atcoder.jp/contests/abc322/tasks/abc322_f) [洛谷](https://www.luogu.com.cn/problem/AT_abc322_f)**

> - 给出长度为 $n$ 的 **$\boldsymbol{01}$ 串**，支持 $m$ 次操作，每次操作为区间 $0,1$ 取反，或询问区间内最长的连续 $1$ 的长度。
>
> - $n\le 5\times 10^5$，$m\le 10^5$。

一眼[序列操作](https://www.luogu.com.cn/problem/P2572)。考虑使用线段树维护。

线段树的节点内维护 $8$ 个信息：

- $l_0$ 表示左起最长连续 $0$ 的长度。

- $l_1$ 表示左起最长连续 $1$ 的长度。

- $r_0$ 表示右起最长连续 $0$ 的长度。

- $r_1$ 表示右起最长连续 $1$ 的长度。

- $len$ 表示区间长度。

- $len_0$ 表示当前区间内，最长的连续 $0$ 的长度。

- $len_1$ 表示当前区间内，最长的连续 $1$ 的长度。

- $ept$ 表示当前信息是否为空，合并信息的时候方便一点。定义 $+$ 为合并运算。若有两个信息 $a,b$，且 $ept_a=1$，则 $\boldsymbol{a+b=b}$。

合并信息就考虑当前信息是否跨过区间中点，这里直接给出代码：

```cpp
struct node {
    int l0, l1, r0, r1, len0, len1, len; bool ept;
    node() { ept = 1; }
    node operator+(const node &o) const {
        if (ept) return o; if (o.ept) return *this;
        node ret; ret.ept = 0; ret.len = len + o.len;
        ret.l0 = l0 + (l0 == len ? o.l0 : 0);
        ret.r0 = o.r0 + (o.r0 == o.len ? r0 : 0);
        ret.l1 = l1 + (l1 == len ? o.l1 : 0);
        ret.r1 = o.r1 + (o.r1 == o.len ? r1 : 0);
        ret.len0 = max({len0, o.len0, r0 + o.l0});
        ret.len1 = max({len1, o.len1, r1 + o.l1}); return ret;
    }
};
```
修改操作就使用一个“是否 $01$ 反转”的懒标记，翻转一次后，$0$ 和 $1$ 的信息要互换。然后记得标记下传。

做法就这样。时间复杂度为 $\mathcal{O}(m\log n)$，空间复杂度为 $\mathcal{O}(n)$。

这题作为线段树练手题还是不错的，但是放 ABC 里就有点板了吧。~~我不会告诉你就是这题助我上分的~~。

```cpp
#include <bits/stdc++.h>
using namespace std; const int N = 5e5 + 5;
int n, m; string s;
struct node {
    int l0, l1, r0, r1, len0, len1, len; bool ept;
    node() { ept = 1; }
    node operator+(const node &o) const {
        if (ept) return o; if (o.ept) return *this;
        node ret; ret.ept = 0; ret.len = len + o.len;
        ret.l0 = l0 + (l0 == len ? o.l0 : 0);
        ret.r0 = o.r0 + (o.r0 == o.len ? r0 : 0);
        ret.l1 = l1 + (l1 == len ? o.l1 : 0);
        ret.r1 = o.r1 + (o.r1 == o.len ? r1 : 0);
        ret.len0 = max({len0, o.len0, r0 + o.l0});
        ret.len1 = max({len1, o.len1, r1 + o.l1}); return ret;
    }
};
struct SegmentTree {
    #define ls(x) ((x) << 1)
    #define rs(x) (((x) << 1) | 1)
    bool rev[N << 2]; node seg[N << 2];
    void build(int x, int l, int r) {
        rev[x] = 0; int mid = (l + r) >> 1;
        if (l == r) {
            seg[x].len = 1; seg[x].ept = 0;
            if (s[l] - '0') {
                seg[x].l1 = seg[x].r1 = seg[x].len1 = 1;
                seg[x].l0 = seg[x].r0 = seg[x].len0 = 0;
            }
            else {
                seg[x].l0 = seg[x].r0 = seg[x].len0 = 1;
                seg[x].l1 = seg[x].r1 = seg[x].len1 = 0;
            } 
            return;
        }
        build(ls(x), l, mid); build(rs(x), mid + 1, r);
        seg[x] = seg[ls(x)] + seg[rs(x)];
    }
    void upd(int x) {
        rev[x] ^= 1; swap(seg[x].len0, seg[x].len1); 
        swap(seg[x].l0, seg[x].l1); swap(seg[x].r0, seg[x].r1);
    }
    void down(int x) { if (rev[x]) upd(ls(x)), upd(rs(x)), rev[x] = 0; }
    void modify(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return upd(x), void(); 
        int mid = (l + r) >> 1; down(x);
        if (ql <= mid) modify(ls(x), l, mid, ql, qr);
        if (qr > mid) modify(rs(x), mid + 1, r, ql, qr);
        seg[x] = seg[ls(x)] + seg[rs(x)];
    }
    node query(int x, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return seg[x]; 
        int mid = (l + r) >> 1; down(x); node ret;
        if (ql <= mid) ret = query(ls(x), l, mid, ql, qr);
        if (qr > mid) ret = ret + query(rs(x), mid + 1, r, ql, qr); return ret;
    }
} SGT;
signed main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0); 
    cin >> n >> m >> s; s = ' ' + s; SGT.build(1, 1, n);
    for (int op, l, r; m--;) {
        cin >> op >> l >> r;
        if (op & 1) SGT.modify(1, 1, n, l, r);
        else cout << SGT.query(1, 1, n, l, r).len1 << '\n';
    }
    return 0;
}
```


---

## 作者：Genius_Star (赞：5)

### 题意：

给出一个长度为 $n$ 的 $01$ 序列，有两个操作：

- 将 $[l,r]$ 区间内的数字异或 $1$（翻转）。

- 查询 $[l,r]$ 区间最长连续 $1$ 的长度。

### 思路：

~~如果你是把序列操作的代码拿过来的话，会 RE，需要开 $8$ 倍空间，因为那题叶子节点也会下传标记……~~

注意到 $n$ 比较大，于是考虑线段树。

因为是询问区间最长连续 $1$ 的长度，所以我们需要维护：

- 区间长度 $k$。

- 区间最长连续 $1$ 的长度与区间最长连续 $0$ 的长度 $M_1,M_2$。

- 包含最左边点的区间最长连续 $1$ 的长度 $z_1$ 与包含最右边点的区间最长连续 $1$ 的长度 $y_1$。

- 包含最左边点的区间最长连续 $0$ 的长度 $z_2$ 与包含最右边点的区间最长连续 $0$ 的长度 $y_2$。

- 区间异或（翻转的懒标记） $t$。

因为我们可能会将区间翻转（即 $0$ 翻转为 $1$，$1$ 翻转为 $0$），所以 $0$ 和 $1$ 的区间最长连续长度我们都要存。

现在想想怎么区间合并（定义 $X$ 为线段树，$k$ 为当前需要合并的节点编号，其左儿子为 $k \times 2$，右儿子为 $k \times 2 + 1$）：

- 更新最左边点的区间最长连续 $1$ 的长度：

    1. 如果左区间的包含最左边点的最长连续 $1$ 覆盖了整个左区间：$X_k \to z_1 = X_{k \times 2} \to k + X_{k \times 2 + 1} \to z_1$。（即如果左区间都是 $1$，那么就可以加上右区间包含最左边点的区间最长连续 $1$ 的长度）
    
    2. 否则 $X_k \to z_1 = X_{k \times 2} \to z_1$（即直接赋值）

- 更新最右边点的区间最长连续 $1$ 的长度：

    1. 如果右区间的包含最右边点的最长连续 $1$ 覆盖了整个右区间：$X_k \to y_1 = X_{k \times 2+1} \to k + X_{k \times 2} \to y_1$。（即如果右区间都是 $1$，那么就可以加上左区间包含最右边点的区间最长连续 $1$ 的长度）
    
    2. 否则 $X_k \to y_1 = X_{k \times 2 + 1} \to y_1$（即直接赋值）

- 更新区间最长连续 $1$ 的长度（在以下三种情况下取个最大值即可）：

    1. 就等于左区间的最长连续 $1$ 的长度。
    
    2. 就等于右区间的最长连续 $1$ 的长度。
    
    3. 左区间包含最右边点的最长连续 $1$ 的长度加上右区间包含最左边点的最长连续 $1$ 的长度。
    
- 更新 $0$ 的思想和 $1$ 没什么区别，这里就不细说了。

现在考虑区间翻转的操作，即懒标记如何下传：

首先，如果当前区间如果要被翻转了，那么更新的值如下：

- 首先将懒标记 $t \to t \ \text{xor} \ 1$，就是相当于翻转了，毕竟如果之前翻转过这个区间，现在在翻转一次，相当于是不变的。

- 因为进行翻转，将 $0$ 的所有信息和 $1$ 的所有信息交换一下即可。

下传懒标记的时候这样更新一下即可了。

查询的时候注意一下细节，也是需要类似区间合并的操作的。

时间复杂度：$O(n \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=500500;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
void Swap(ll &a,ll &b){
	ll t=a;
	a=b;
	b=t;
}
struct Node{
	ll l,r;
	ll t,k; //t 为区间取反，k 为区间长度 
	ll M1,M2; //M1 为 0 的区间最长、M2 为 1 的区间最长 
	ll z1,y1;
	ll z2,y2;
}X[N<<2];
ll n,m,op,x,y;
ll a[N];
string s;
void SWAP(ll k){ //交换 1 和 0 的信息 
	Swap(X[k].M1,X[k].M2);
	Swap(X[k].z1,X[k].z2);
	Swap(X[k].y1,X[k].y2);
}
void pushup(ll k){ //区间合并 
	if(X[k<<1].k==X[k<<1].z1)
	  X[k].z1=X[k<<1].k+X[k<<1|1].z1;
	else
	  X[k].z1=X[k<<1].z1;
	if(X[k<<1|1].k==X[k<<1|1].y1)
	  X[k].y1=X[k<<1|1].k+X[k<<1].y1;
	else
	  X[k].y1=X[k<<1|1].y1;
	if(X[k<<1].k==X[k<<1].z2)
	  X[k].z2=X[k<<1].k+X[k<<1|1].z2;
	else
	  X[k].z2=X[k<<1].z2;
	if(X[k<<1|1].k==X[k<<1|1].y2)
	  X[k].y2=X[k<<1|1].k+X[k<<1].y2;
	else
	  X[k].y2=X[k<<1|1].y2;
	X[k].M1=max(max(X[k<<1].M1,X[k<<1|1].M1),X[k<<1].y1+X[k<<1|1].z1);
	X[k].M2=max(max(X[k<<1].M2,X[k<<1|1].M2),X[k<<1].y2+X[k<<1|1].z2);
}
void push_down(ll k){ //懒标记下传 
	if(X[k].t){
		X[k<<1].t=!X[k<<1].t;
		X[k<<1|1].t=!X[k<<1|1].t;
		SWAP(k<<1);
		SWAP(k<<1|1);
		X[k].t=0;
	}
}
void build(ll k,ll l,ll r){ //初始化 
	X[k].l=l,X[k].r=r;
	X[k].t=0;
	X[k].k=r-l+1;
	if(l==r){
		X[k].M1=X[k].z1=X[k].y1=(a[l]==0);
		X[k].M2=X[k].z2=X[k].y2=(a[l]==1);
		return ;
	}
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	pushup(k);
}
void updata(ll k,ll l,ll r){ //区间翻转 
	if(X[k].l==l&&X[k].r==r){
		X[k].t=!X[k].t;
		SWAP(k);
		return ;
	}
	push_down(k);
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  updata(k<<1,l,r);
	else if(l>mid) 
	  updata(k<<1|1,l,r);
	else{
		updata(k<<1,l,mid);
		updata(k<<1|1,mid+1,r);
	}
	pushup(k);
}
Node search(ll k,ll l,ll r){ //查询 
	if(X[k].l==l&&X[k].r==r)
	  return X[k];
	push_down(k);
	ll mid=(X[k].l+X[k].r)>>1;
	if(r<=mid)
	  return search(k<<1,l,r);
	else if(l>mid)
	  return search(k<<1|1,l,r);
	else{
		Node x=search(k<<1,l,mid),y=search(k<<1|1,mid+1,r),z;
		if(x.z2==x.k)
		  z.z2=x.k+y.z2;
		else
		  z.z2=x.z2;
		if(y.y2==y.k)
		  z.y2=y.k+x.y2;
		else
		  z.y2=y.y2;
		z.k=x.k+y.k;
		z.M2=max(max(x.M2,y.M2),x.y2+y.z2);
		return z;
	}
}
int main(){
	n=read(),m=read();
	cin>>s;
	for(int i=1;i<=n;i++)
	  a[i]=s[i-1]-'0';
	build(1,1,n);
	while(m--){
		op=read(),x=read(),y=read();
		if(op==1)
		  updata(1,x,y);
		else
		  write(search(1,x,y).M2),putchar('\n');
	}
	return 0;
}
```

---

## 作者：tZEROちゃん (赞：3)

> 有一个长为 $n$ 的 01 序列，对序列有 $2$ 个操作：
> - `1 a b`，将 $[a,b]$ 范围内的所有数字：$0$ 变为 $1$，$1$ 变为 $0$；
> - `2 a b`，统计 $[a,b]$ 范围内的最长连续 $1$ 的个数并输出。

考虑线段树。

我们考虑要维护哪些量。

对于每个区间，我们需要知道这个区间内的最长的连续的 $1$ 的长度（$tlen1$），这样才能合并。那显然父节点的答案等于两个子节点的较大的 $tlen1$，但这样并不正确。考虑两个子节点如果分别是 $[1,1,1,1,0,1,1,1]$ 和 $[1,1,1,0,1,1,1,1]$，那么显然答案应该是 $6$，即左子节点右边最长连续 $1$ 的长度 $llen1$ 和右子节点左边最长连续 $1$ 的长度 $rlen1$ 之和。

那么我们对每个区间再分别维护一个「左边最长连续 $1$ 的长度」和「右边最长连续 $1$ 的长度」，所以父节点的 $tlen1$ 就是等于「左子节点 $tlen1$」，「右子节点 $tlen1$」，和「左节点 $rlen1$ + 右节点 $llen1$」中的最大值。

然后我们考虑在 `pushup` 过程中 $llen1$ 和 $rlen1$ 应该如何更新。显然，父节点的 $llen1$ 就是左子节点的 $llen1$，父节点的 $rlen1$ 就是右子节点的 $rlen1$，但是，如果左节点全是 $1$，右节点又以 $1$ 开头，这种做法就会寄掉，所以我们还要特判一下这种情况。

此外，我们维护一下 $0$ 和 $1$ 在区间内的数量，直接相加即可。

注意到有区间反转操作，因此我们也维护一下 $0$ 的对应值。

我们在维护一个 $all$ 和 $init$，分别表示区间里所有数都是 $all$ 和区间内 $0$ 表示的数（比如，$init = 0$，那么区间里 $0$ 表示 $0$，否则，$0$ 表示 $1$），这两个变量的内容在后续会提到。


在这个基础上，思考一下如何实现题目里的操作。

### 区间反转

我们并不需要去真正意义上把所有 $0$ 变成 $1$，只要在区间的 $init$ 上做个标记，把它赋值为 $1$，就可以实现。

但这样并不够，我们还需要将区间内表示 $0$ 和 $1$ 的量都 `swap`，比如说 $zero$ 现在表示的是 $1$ 的数量了，但这样不好处理，干脆直接 `swap(ichi, zero)`，其他也同理。

### 区间查询

在我们查询的过程中，如果我们目前二分到的区间 $[L,R]$，已经被要查询的区间 $[l, r]$ 完全覆盖，我们就直接返回结果。

否则，如果区间 $[l,r]$ 全部在左边，我们就在左节点里查询，如果全部在右边，我们就在右节点里查询，否则，我们的答案可能是左边的，也可能是右边的，也可能是合起来的。

合起来的如果直接写左节点的 $rlen1\ +$ 右节点的 $llen1$ 显然是错误的，我们要考虑查询的区间可能会超过这个 $rlen1$ 和 $llen1$ 的范围。

比如 $[0, 0, 1, 1]$ 和 $[1, 1, 0, 0]$，如果区间只是左节点的最后一个和右节点的第一个，那答案是 $2$，但是按照这种做法会返回 $4$，因此我们需要取一下 $\min$。

然后这个题就做完了。代码我直接抄的我之前写的 [P2572 [SCOI2010] 序列操作](https://www.luogu.com.cn/problem/P2572)，见 [46121133](https://atcoder.jp/contests/abc322/submissions/46121133)。

---

## 作者：WilliamFranklin (赞：2)

### 主要思路

这题一眼就是线段树吧。

我们考虑维护什么：$lazy$ 懒标记，表示这个区间被取反了几次；$l0$ 表示满足这个区间的第 $1$ 个位置到第 $l0$ 个位置全为 $0$ 的条件的最大值；$l1$ 表示满足这个区间的第 $1$ 个位置到第 $l1$ 个位置全为 $1$ 的条件的最大值；$r0$ 表示满足这个区间的第 $r0$ 个位置到最后一个位置全为 $0$ 的条件的最小值；$r1$ 表示满足这个区间的第 $r1$ 个位置到最后一个位置全为 $1$ 的条件的最小值；$maxn0$ 表示这个区间中所有满足全为 $0$ 的字串的最大长度；$maxn1$ 表示这个区间中所有满足全为 $1$ 的字串的最大长度。

然后我们考虑一下最简单的 $01$ 翻转操作：其实就是交换一下 $l0$ 和 $l1$，$r0$ 和 $r1$，$maxn0$ 和 $maxn1$。

最后，就是我们重量级的操作 ~~（这还能算得上重量级？）~~，区间合并：

假设当前两个区间为 $i$ 和 $j$，其中 $i$ 为左边的区间，$j$ 为右边的区间，最后合并成的区间为 $k$，那么 $k$ 的 $maxn0$ 就是等于 $i$ 的 $maxn0$ 和 $j$ 的 $maxn0$ 的最大值。然后我们就会发现当两区间合并时，$i$ 的 $r0$ 和 $j$ 的 $l0$ 还会组成一个全是 $0$ 的字串，所以 $maxn0$ 最终就等于 $i$ 的 $maxn0$、$j$ 的 $maxn0$ 和 $i$ 的 $r0$ 加上 $j$ 的 $l0$ 的最大值，$k$ 的 $maxn1$ 同理。

再考虑 $k$ 的 $l0$、$l1$、$r0$ 和 $r1$。我们先讨论一下 $l0$，首先 $i$ 的 $l0$ 一定是一个候选人，然后再考虑两区间合并的情况。我们发现当 $i$ 的 $l0$ 等于 $i$ 这个区间的长度时，那么就可以加上 $j$ 的 $l0$，由此，当 $i$ 的 $l0$ 等于 $i$ 的区间长度时，$k$ 的 $l0$ 就等于 $i$ 的 $l0$ 加上 $j$ 的 $l0$；否则就等于 $i$ 的 $l0$。其他三个同理。

如果您觉得说的不太仔细，那么请看下面代码。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define mp(Tx, Ty) make_pair(Tx, Ty)
#define For(Ti, Ta, Tb) for(auto Ti = (Ta); Ti <= (Tb); Ti++)
#define Dec(Ti, Ta, Tb) for(auto Ti = (Ta); Ti >= (Tb); Ti--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define range(Tx) begin(Tx),end(Tx)
const int N = 5e5 + 5;
int n, q;
string s;
int a[N];
struct node {
	int l0, l1, r1, r0, maxn1, maxn0;
	int l, r;
	int lazy;
} tr[N << 2]; 
struct answer{
	int ans;
	int l1;
	int r1;
	int l;
	int r;
};
void pushup(int u) {
	tr[u].maxn1 = max(tr[u << 1].maxn1, tr[u << 1 | 1].maxn1);
	tr[u].maxn1 = max(tr[u << 1].r1 + tr[u << 1 | 1].l1, tr[u].maxn1);
	tr[u].maxn0 = max(tr[u << 1].r0 + tr[u << 1 | 1].l0, max(tr[u << 1].maxn0, tr[u << 1 | 1].maxn0));
	tr[u].l0 = tr[u << 1].l0;
	tr[u].l1 = tr[u << 1].l1;
	tr[u].r1 = tr[u << 1 | 1].r1;
	tr[u].r0 = tr[u << 1 | 1].r0;
	if (tr[u << 1].l1 == tr[u << 1].r - tr[u << 1].l + 1) tr[u].l1 = tr[u << 1].l1 + tr[u << 1 | 1].l1;
	if (tr[u << 1].l0 == tr[u << 1].r - tr[u << 1].l + 1) tr[u].l0 = tr[u << 1].l0 + tr[u << 1 | 1].l0;
	if (tr[u << 1 | 1].r0 == tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1) tr[u].r0 = tr[u << 1 | 1].r0 + tr[u << 1].r0;
	if (tr[u << 1 | 1].r1 == tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1) tr[u].r1 = tr[u << 1].r1 + tr[u << 1 | 1].r1;
}
void pushdown(int u) {
	tr[u << 1].lazy += tr[u].lazy;
	tr[u << 1 | 1].lazy += tr[u].lazy;
	if (tr[u].lazy % 2 == 1) {
		swap(tr[u << 1].l0, tr[u << 1].l1);
		swap(tr[u << 1].r0, tr[u << 1].r1);
		swap(tr[u << 1].maxn0, tr[u << 1].maxn1);
		swap(tr[u << 1 | 1].l0, tr[u << 1 | 1].l1);
		swap(tr[u << 1 | 1].r0, tr[u << 1 | 1].r1);
		swap(tr[u << 1 | 1].maxn0, tr[u << 1 | 1].maxn1);
	}
	tr[u].lazy = 0;
}
void build(int u, int l, int r) {
	if (l == r) {
		tr[u].l = l;
		tr[u].r = r;
		if (a[l] == 1) tr[u].l0 = tr[u].r0 = 0, tr[u].l1 = tr[u].r1 = 1, tr[u].maxn1 = 1, tr[u].maxn0 = 0;
		else tr[u].l0 = tr[u].r0 = 1, tr[u].l1 = tr[u].r1 = 0, tr[u].maxn1 = 0, tr[u].maxn0 = 1;
		return;
	}
	tr[u].l = l;
	tr[u].r = r;
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	pushup(u);
}
void modify(int u, int l, int r) {
	if (tr[u].l >= l && tr[u].r <= r) {
		tr[u].lazy++;
		swap(tr[u].l0, tr[u].l1);
		swap(tr[u].r0, tr[u].r1);
		swap(tr[u].maxn0, tr[u].maxn1);
		return;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if (l <= mid) modify(u << 1, l, r);
	if (r > mid) modify(u << 1 | 1, l, r);
	pushup(u);
}
answer query(int u, int l, int r) {
	if (tr[u].l >= l && tr[u].r <= r) {
		return {tr[u].maxn1, tr[u].l1, tr[u].r1, tr[u].l, tr[u].r};
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	answer al = {0, 0, 0, 1000000000, 0}, ar = {0, 0, 0, 1000000000, 0};
	answer tans = {0, 0, 0, 0, 0};
	if (l <= mid) al = query(u << 1, l, r);
	if (r > mid) ar = query(u << 1 | 1, l, r);
	pushup(u);
	tans.l = min(al.l, ar.l);
	tans.r = max(ar.r, al.r);
	tans.ans = max(al.ans, max(ar.ans, al.r1 + ar.l1));
	tans.l1 = al.l1;
	tans.r1 = ar.r1;
	if (al.l1 == al.r - al.l + 1) tans.l1 = al.l1 + ar.l1;
	if (ar.r1 == ar.r - ar.l + 1) tans.r1 = ar.r1 + al.r1;
	return tans;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> q;
	cin >> s;
	For(i, 0, n - 1) a[i + 1] = s[i] - '0';
	build(1, 1, n);
	while (q--) {
		int op, l, r;
		cin >> op >> l >> r;
		if (op == 1) {
			modify(1, l, r);
		} else {
			cout << (query(1, l, r)).ans << endl;
		}
	}
	return 0;
} 
```

### 谢谢观看

---

## 作者：不知名用户 (赞：1)

线段树板题，而且是 [P2572](https://www.luogu.com.cn/problem/P2572) 的简化版。~~（顺便资瓷一下粉兔的[题解](https://www.luogu.com.cn/blog/PinkRabbit/solution-p2572)）~~

题意：给定一个 01 序列要支持一下几种操作：

- 查询区间里连续的 1 最多有多少个
- 反转一个区间的数：把区间 1 变成 0，0 变成 1

如果只有查询怎么做？

显然是线段树，但是一个区间要维护那些信息？

最多有多少个连续的 1 是肯定要的，但是两个区间合并的时候连续的 1 可能在两个区间，也可能横跨两个区间，这时候就要记录每个区间靠左/右连续的 1 的个数。但是靠左连续 1 的个数合并的时候还要看是否能延申到右边的区间，所以需要记录（左边的）区间是否全为 1。

根据刚刚的分析，要维护以下几个变量：

- `fu`(full)：是否全部为 1
- `lm`(LeftMaxlen)：靠左最多有多少个连续的 1
- `rm`(RightMaxlen)：靠右最多有多少个连续的 1
- `m`(Maxlen)：最长连续 1 的数量

```
struct node
{
	int lm, rm, m, fu;
};
```

合并时候上面的分析应该很清楚了吧：

```
node merge(node a, node b)
{
	node c;
	if(a.fu) c.lm = a.m + b.lm;
	else c.lm = a.lm;
	if(b.fu) c.rm = a.rm + b.m;
	else c.rm = b.rm;
	c.m = max({a.rm+b.lm,a.m,b.m});
	c.fu = a.fu & b.fu;
	return c;
}
```

考虑区间数值反转。

把 0 当 1 也开一个含义一样（把定义中的 1 改成 0） `struct node`，反转时 `swap` 0 和 1 的 `struct node` 即可了，同时注意改变懒标记并在查询/修改时传下去即可：

```inline void rev(int p){swap(ze[p],on[p]);lazy[p] ^= 1;}```

[AC code](https://atcoder.jp/contests/abc322/submissions/46109272)：

```cpp
#include<bits/stdc++.h>
//#define int long long
#define lf long double
#define I inline
#define deb(x) std::cout<<#x<<" = "<<x<<std::endl
#define fio(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout)
using namespace std;

template <typename T>
inline void rd(T &x)
{
	x = 0; bool f = true; char ch = getchar();
	while(ch < '0' || ch > '9')
	{ if(ch == '-') f = false; ch = getchar();}
	while(ch >= '0' && ch <= '9')
	{ x = (x << 1) + (x << 3) + (ch ^ '0'); ch = getchar();}
	if(!f) x = -x;
}
inline long long rd(){ long long x; rd(x); return x;}
template <typename T, typename ...Args>
inline void rd(T &x, Args &...args){ rd(x); rd(args...);}

const int N = 5e5 + 10;

struct node
{
	int lm, rm, m, fu;
}ze[N*4],on[N*4],
f1{1,1,1,1},f0{0,0,0,0};
int lazy[N*4];

node merge(node a, node b)
{
	node c;
	if(a.fu) c.lm = a.m + b.lm;
	else c.lm = a.lm;
	if(b.fu) c.rm = a.rm + b.m;
	else c.rm = b.rm;
	c.m = max({a.rm+b.lm,a.m,b.m});
	c.fu = a.fu & b.fu;
	return c;
}

char str[N];

inline void upd(int p)
{
	ze[p] = merge(ze[p*2],ze[p*2+1]);
	on[p] = merge(on[p*2],on[p*2+1]);
}
inline void rev(int p){swap(ze[p],on[p]);lazy[p] ^= 1;}
inline void spd(int p)
{
	if(lazy[p]) rev(p*2), rev(p*2+1);
	lazy[p] = 0;
}

void build(int p, int l, int r)
{
	if(l==r)
	{
		if(str[l]=='0') ze[p] = f1, on[p] = f0;
		if(str[l]=='1') ze[p] = f0, on[p] = f1;
		return;
	}
	int mid = l + r >> 1;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	upd(p);
}

void ch(int p, int l, int r, int L, int R)
{
	if(l<=L&&R<=r)
	{
		rev(p);
		return;
	}
	spd(p);
	int mid = L + R >> 1;
	if(l<=mid) ch(p*2,l,r,L,mid);
	if(mid<r) ch(p*2+1,l,r,mid+1,R);
	upd(p);
}

node ask(int p, int l, int r, int L, int R)
{
	if(l<=L&&R<=r) return on[p];
	spd(p);
	int mid = L + R >> 1;
	if(l>mid) return ask(p*2+1,l,r,mid+1,R);
	if(mid>=r) return ask(p*2,l,r,L,mid);
	return merge(ask(p*2,l,r,L,mid),ask(p*2+1,l,r,mid+1,R));
}

inline void Main()
{
	int n, q, i;
	cin>>n>>q;
	cin>>str;
	for(i=n;i;i--) str[i] = str[i-1];
	build(1,1,n);
	while(q--)
	{
		int c, l, r;
		rd(c,l,r);
		if(c==1) ch(1,l,r,1,n);
		else cout<<ask(1,l,r,1,n).m<<'\n';
	}
}

signed main()
{
	int t = 1;
//	rd(t);
	while(t--) Main();
	return 0;
}
```

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc322_f)

哦线段树我的线段树。

赛时因为 D,E 两个奇葩的题目，我失去了做这个题的时间。

## $\mathbf{Solution1}$

考虑珂朵莉树（[模板题链接](https://www.luogu.com.cn/problem/CF915E)）。

每次暴力地区间异或，暴力地查找最长的 $1$ 序列。

但是这样会被卡（例如 $101010\dots$），只是提供一个思路而已。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    int l, r;
    mutable int v;//即使被设为常量，也能对v进行修改
    node(int L, int R = -1, int V = 0):l(L), r(R), v(V) {}
    bool operator<(const node& o)const{
        return l < o.l;
    }
};
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
set<node>s;
const int MAXN = 5e5 + 5;
int n, m, sum, a[MAXN];
set<node>::iterator split(int pos){
    auto it = s.lower_bound(node(pos));
    if(it != s.end() && it->l == pos) return it;
    --it;
    int L = it->l, R = it->r, V = it->v;
    s.erase(it);
    s.insert(node(L, pos-1, V));
    return s.insert(node(pos, R, V)).first;
}
void assign_val(int l, int r, int val){//区间赋值
    auto itr = split(r+1), itl = split(l);
    s.erase(itl, itr);
    s.insert(node(l, r, val));
}
void Xor(int l, int r){//暴力Xor
    auto itr = split(r+1), itl = split(l);
    for(auto it = itl;it != itr;++ it)(it -> v) = !(it -> v);
}
int query(int l, int r){//区间查询
	int res = 0, ans = 0;
	auto itr = split(r+1), itl = split(l);
    for(auto it = itl;it != itr;++ it){
    	if(it -> v)res += (it -> r - it -> l + 1);
    	else res = 0;
    	ans = max(ans, res);
	}
    return ans;
}
int main(){
	scanf("%d%d", &n, &m);
	s.insert({1, n, 0});
	for(int i = 1;i <= n;i ++)scanf("%1d", &a[i]);
	int last = a[1], pos = 1;
	for(int i = 2;i <= n;i ++){
		if(last != a[i])assign_val(pos, i - 1, last), last = a[i], pos = i;
	}
	assign_val(pos, n, last);
//	return 0;
	while(m --){
		int opt = read(), l = read(), r = read();
		if(opt == 2)printf("%lld\n", query(l, r));
		else Xor(l, r);
	}
	return 0;
}
```

## $\mathbf{Solution2}$

考虑线段树。

想想我们最大子段和怎么维护的？没错，就是维护 $1$ 的前缀，后缀最大的一段 $lp1,rp1$，以及区间本身的最大子段和和区间和 $num1,sum1$。

令根节点为 $rt$，左右子树分别为 $left, right$。

由于有区间 `xor` 操作，所以我们还要维护 $0$ 的前缀，后缀最大的一段 $lp0,rp0$，以及区间本身的最大子段和和区间和 $num0,sum0$。

接下来考虑合并两个区间：

首先 $0,1$ 的数量直接加上：$sum1_{rt}=sum1_{left} + sum1_{right}$，$sum0_{rt}=sum0_{left} + sum0_{right}$。

然后更新一下前缀，后缀：

$lp1_{rt}=lp1_{left},lp0_{rt}=lp0_{left}$。
$rp1_{rt}=rp1_{right},rp0_{rt}=rp0_{right}$。

再更新一下最大子段和：

$num1_{rt} = \max\{num1_{left},num1_{right},rp1_{left}+lp1_{right}\}$

$num0_{rt} = \max\{num0_{left},num0_{right},rp0_{left}+lp0_{right}\}$

为什么还要对 $rp0_{left}+lp0_{right}$ 取最大值呢？因为这个最大子段和的区间很有可能横跨两边。

但是还有一种情况，如果左边或者右边全是 $0/1$，那么不就是可以全部取走吗？

所以这个时候要特判然后更新 $num,lp,rp$。

其他的同理，就不再赘述。

代码：
```cpp
#include<bits/stdc++.h>
#define left rt * 2
#define right rt * 2 + 1
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){s = s * 10 + (ch - '0');ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 5e5 + 5, MR = 2e6 + 5;
int n, m, a[MAXN];
struct LYN{
	int x, y, z, w;
};
struct Segment_tree{
	int lf[MR], rf[MR], num0[MR], num1[MR], sum[MR], lp0[MR], rp0[MR], lp1[MR], rp1[MR], lazy[MR];
	void push_up(int rt){
		num1[rt] = max({num1[left], num1[right], rp1[left] + lp1[right]});
		num0[rt] = max({num0[left], num0[right], rp0[left] + lp0[right]});
		lp1[rt] = lp1[left], lp0[rt] = lp0[left];
		rp1[rt] = rp1[right], rp0[rt] = rp0[right];
		sum[rt] = sum[left] + sum[right];
		if(sum[left] == 0)lp0[rt] = rf[left] - lf[left] + 1 + lp0[right], num0[rt] = max(num0[rt], lp0[rt]);
		if(sum[right] == 0)rp0[rt] = rf[right] - lf[right] + 1 + rp0[left], num0[rt] = max(num0[rt], rp0[rt]);
		if(sum[left] == (rf[left] - lf[left] + 1))lp1[rt] = sum[left] + lp1[right], num1[rt] = max(num1[rt], lp1[rt]);
		if(sum[right] == (rf[right] - lf[right] + 1))rp1[rt] = sum[right] + rp1[left], num1[rt] = max(num1[rt], rp1[rt]);
	}
	void build(int rt, int l, int r){
		lf[rt] = l, rf[rt] = r;
		if(l == r){
			if(a[l])lp1[rt] = rp1[rt] = sum[rt] = num1[rt] = 1;
			else lp0[rt] = rp0[rt] = num0[rt] = 1;
			return ;
		}
		int mid = l + r >> 1;
		build(left, l, mid);
		build(right, mid + 1, r);
		push_up(rt);
	}
	void push_down(int rt){
		if(!lazy[rt])return ;
		lazy[rt] = 0;
		lazy[left] ^= 1, lazy[right] ^= 1;
		swap(lp0[left], lp1[left]);
		swap(lp0[right], lp1[right]);
		swap(rp0[left], rp1[left]);
		swap(rp0[right], rp1[right]);
		swap(num0[left], num1[left]);
		swap(num0[right], num1[right]);
		sum[left] = (rf[left] - lf[left] + 1) - sum[left];
		sum[right] = (rf[right] - lf[right] + 1) - sum[right];
	}
	void Xor_list(int rt, int l, int r){
		if(l > rf[rt] || lf[rt] > r)return ;
		if(l <= lf[rt] && rf[rt] <= r){
			lazy[rt] ^= 1;
			swap(lp0[rt], lp1[rt]);
			swap(rp0[rt], rp1[rt]);
			swap(num0[rt], num1[rt]);
			sum[rt] = (rf[rt] - lf[rt] + 1) - sum[rt];
			return ;
		}
		push_down(rt);
		Xor_list(left, l, r);
		Xor_list(right, l, r);
		push_up(rt);
	}
	LYN query(int rt, int l, int r){
		if(l > rf[rt] || lf[rt] > r)return {0, 0, 0, 0};
		if(l <= lf[rt] && rf[rt] <= r)return {num1[rt], sum[rt], lp1[rt], rp1[rt]};
		push_down(rt);
		LYN lpos = query(left, l, r), rpos = query(right, l, r), res;
		res.x = max({lpos.x, rpos.x, lpos.w + rpos.z});
		res.y = lpos.y + rpos.y;
		res.z = lpos.z, res.w = rpos.w;
		if(lpos.y == rf[left] - lf[left] + 1)res.z = max(res.z, lpos.y + rpos.z), res.x = max(res.x, res.z);
		if(rpos.y == rf[right] - lf[right] + 1)res.w = max(res.w, rpos.y + lpos.w), res.x = max(res.x, res.w);
//		printf("%d %d %d %d %d %d %d\n", rt, lf[rt], rf[rt], res.x, res.y, res.z, res.w);
		return res;
	}
}tr;
int main(){
	n = read(), m = read();
	for(int i = 1;i <= n;i ++)scanf("%1d", &a[i]);
	tr.build(1, 1, n);
	while(m --){
		int opt = read(), l = read(), r = read();
		if(opt == 1)tr.Xor_list(1, l, r);
		else{
			LYN h = tr.query(1, l, r);
			printf("%d\n", h.x);
		}
	}
	return 0;
}

```


---

## 作者：BINYU (赞：1)

## 题意

给定一个长度为 $n$ 的 01 序列 $a$，要求支持下面两种操作：

1. 把下标在 $l$ 与 $r$ 之间的数取反（0 变成 1，1 变成 0）;

2. 求下标在 $l$ 与 $r$ 之间的连续的 1 的个数的最大值。

## 思路

这道题要求支持区间修改和区间查询，很容易想到数据结构，笔者这里写的是线段树。

先来看操作一区间取反，这启发我们将所有信息对称的存，只要存了关于 1 的信息，就要把 0 的也一起存上，在更新过程中，直接把对应的信息交换，再打上标记下传即可。

再来看操作二，我们考虑具体要维护那些值，我们很容易想到先要维护下标在 $l$ 到 $r$ 内的连续的 1 的个数的最大值（0 同理），接下来我们对转移进行分类讨论：

1. 最大的连续串全部在左儿子部分或右儿子部分，我们可以直接从儿子处继承状态；

2. 最大的连续串跨过了左右儿子的分界线，我们将从分界线处尽量往左右扩展，知道碰到边界或 0。这需要我们记录一段区间的左边界处 1 的个数与右边界处 1 的个数。

再考虑左边界处 1 的个数该怎么维护（右边界同理），还是分类讨论：

1. 左儿子部分有 0，这种情况下左边界处连续的 1 不可能跨过左右儿子分界线，直接从左儿子处继承。

2. 左儿子部分没有 0，此时左边界处连续的 1 可能跨过分界线，则右儿子部分最靠左连续的 1 也会被计算在内，所以此时的值就是左儿子的大小加上右儿子最靠左连续的 1 的个数。

此时，我们还需要维护的值只有一个节点对应区间的大小，这是可以直接求的。

综上，我们需要一颗线段树维护区间左右边界处连续的 0 和 1 的个数，区间内连续的最大的 0 和 1 的个数，区间的大小（也可以直接求）和一个下传的标记，转移已经在上面了。

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$，可过。

---

## 作者：small_john (赞：0)

## 前言

Update：修改了一下表述问题。

这道题也是 [P2572](/problem/P2572) 的双倍经验，可以去做一下那道题。

## 思路

有亿点点简单的线段树题。

由于有区间翻转操作，所以 $0,1$ 的最大的连续的一段都要记录，所以记 $mx0,mx1$ 分别表示最大连续的一段 $0,1$。现在考虑如何将两个区间合并。

![](https://cdn.luogu.com.cn/upload/image_hosting/oa3bwyus.png)

很明显，至少都有两种选择，即选左儿子的最大值或者右儿子的最大值。当然，做过最大子段和的人都知道还要考虑中间连接处对答案的贡献。而中间可以连起来当且仅当左儿子的右端点和右儿子的左端点相同。

而计算中间的答案则需要从左儿子右端点的最大值和右儿子左端点的最大值。那如何维护这两个值呢？

首先，左端点的最大值可以由左儿子左端点的最大值继承。但当左儿子的整个区间都相同并且右儿子左端点和左儿子右端点相同时，左端点的最大值还可以扩展到右儿子左端点的最大值。右端点的最大值也是同样的。因此，我们还需要记录左右端点的值、整个区间是否相等。

那么，两个区间合并就做完了。代码如下：

```cpp
struct node{
	int mx0,mx1,ml,mr;
	//分别对应：最大连续的一段0,最大连续的一段1，左端点的最大值，右端点的最大值
	bool tag,all,lc,rc;
	//分别对应：懒标记，区间是否全部相同，左端点的值，右端点的值 
	friend node operator + (node x,node y)
	{
		node res;
		res.mx0 = max({x.mx0,y.mx0,(x.rc==0)*x.mr+(y.lc==0)*y.ml});
		res.mx1 = max({x.mx1,y.mx1,(x.rc==1)*x.mr+(y.lc==1)*y.ml});
		res.ml = x.ml+(x.rc==y.lc)*x.all*y.ml;
		res.mr = y.mr+(x.rc==y.lc)*y.all*x.mr;
		res.all = x.all&&y.all&&(x.rc==y.lc);
		res.lc = x.lc;
		res.rc = y.rc;
		return res;
	}
}t[N*4];
```

接下来考虑区间修改操作。因为区间修改不会改变区间内部的相对情况，所以只用把 $0,1$ 对应的信息交换。即交换 $mx0,mx1$ 的值，$lc,rc$ 都取反。代码如下：

```cpp
void sol(int k)
{
	swap(t[k].mx0,t[k].mx1);
	t[k].tag = !t[k].tag,t[k].lc = !t[k].lc,t[k].rc = !t[k].rc;
}
```

那这道题就变成了一道简单的区间更改、区间查询的线段树。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls (k*2)
#define rs (k*2+1)
using namespace std;

template<typename T> void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T> T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x<=9) return putchar(x+48),void();
    write(x/10);
    putchar(x%10+48);
}
template<typename T> void writen(T x)
{
    write(x);
    puts("");
}
const int N = 5e5+5,inf = 2e9;
struct node{
	int mx0,mx1,ml,mr;
	//分别对应：最大连续的一段0,最大连续的一段1，左端点的最大值，右端点的最大值
	bool tag,all,lc,rc;
	//分别对应：懒标记，区间是否全部相同，左端点的值，右端点的值 
	friend node operator + (node x,node y)
	{
		node res;
		res.mx0 = max({x.mx0,y.mx0,(x.rc==0)*x.mr+(y.lc==0)*y.ml});
		res.mx1 = max({x.mx1,y.mx1,(x.rc==1)*x.mr+(y.lc==1)*y.ml});
		res.ml = x.ml+(x.rc==y.lc)*x.all*y.ml;
		res.mr = y.mr+(x.rc==y.lc)*y.all*x.mr;
		res.all = x.all&&y.all&&(x.rc==y.lc);
		res.lc = x.lc;
		res.rc = y.rc;
		return res;
	}
}t[N*4];
string s;
int n,q;
void pushup(int k)
{
	t[k] = t[ls]+t[rs];
}
void sol(int k)
{
	swap(t[k].mx0,t[k].mx1);
	t[k].tag = !t[k].tag,t[k].lc = !t[k].lc,t[k].rc = !t[k].rc;
}
void down(int k)
{
	if(t[k].tag==0) return;
	sol(ls),sol(rs);
	t[k].tag = 0;
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		t[k].all = t[k].ml = t[k].mr=1;
		if(s[l]=='0') t[k].mx0 = 1,t[k].lc = t[k].rc = 0;
		else t[k].lc = t[k].rc = t[k].mx1 = 1;
		return;
	}
	int mid = (l+r)/2;
	build(ls,l,mid),build(rs,mid+1,r);
	pushup(k);
}
void change(int k,int l,int r,int x,int y)
{
	if(l>y||r<x) return;
	if(l>=x&&r<=y) return sol(k);
	int mid = (l+r)/2;
	down(k);
	change(ls,l,mid,x,y),change(rs,mid+1,r,x,y);
	pushup(k);
}
node ask(int k,int l,int r,int x,int y)
{
	if(l>=x&&r<=y) return t[k];
	int mid = (l+r)/2;
	down(k);
	if(mid<x) return ask(rs,mid+1,r,x,y);
	if(mid>=y) return ask(ls,l,mid,x,y);
	return ask(ls,l,mid,x,y)+ask(rs,mid+1,r,x,y);
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(q);
	cin>>s;
	s = ' '+s;
	build(1,1,n);
	while(q--)
	{
		int op,x,y;
		read(op),read(x),read(y);
		if(op==1) change(1,1,n,x,y);
		else writen(ask(1,1,n,x,y).mx1);
	}
	return 0;
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc322_f)
### 题意
略。

简单线段树。
### 题解
题目要求最长连续 $1$ 的长度，还有区间取反操作，不难想到结合 P2894 直接得出思路。

思路：分别对 $0$  和 $1$ 求出左边连续长度，右边连续长度，和无限制连续长度，还有个数（注意这里是针对 $0$ 或 $1$ 说明的）。区间取反时，直接把要修改的区间的 $0$ 和 $1$ 的数据交换即可，其他和 P2894 没有区别。
### 代码
```cpp
#include <iostream>
using namespace std;
const int N = 500010;
int n,m;
int a[N];
struct node {
    int l,r;
    int sum[2],lmax[2],rmax[2],vmax[2];
    bool rev;
}tr[4 * N];
void push_up (node &root,node left,node right) {
    for (int i = 0;i < 2;i++) {
		root.sum[i] = left.sum[i] + right.sum[i];
		root.lmax[i] = left.lmax[i];
		if (left.lmax[i] == left.r - left.l + 1) root.lmax[i] = left.lmax[i] + right.lmax[i];
	    root.rmax[i] = right.rmax[i];
	    if (right.rmax[i] == right.r - right.l + 1) root.rmax[i] = right.rmax[i] + left.rmax[i];
    	root.vmax[i] = max (max (left.vmax[i],right.vmax[i]),left.rmax[i] + right.lmax[i]);
    }
}
void push_up (int u) {
    push_up (tr[u],tr[u << 1],tr[u << 1 | 1]);
}
void opt_rev (int u) {
	swap (tr[u].lmax[0],tr[u].lmax[1]);
	swap (tr[u].rmax[0],tr[u].rmax[1]);
	swap (tr[u].vmax[0],tr[u].vmax[1]);
	swap (tr[u].sum[0],tr[u].sum[1]);
	tr[u].rev ^= 1;
}
void push_down (int u) {
	if (tr[u].rev) {
		opt_rev (u << 1),opt_rev (u << 1 | 1);
		tr[u].rev = false;
	}
}
void build (int u,int l,int r) {
    tr[u] = {l,r,{!a[l],a[l]},{!a[l],a[l]},{!a[l],a[l]},{!a[l],a[l]},false};
    if (l == r) return ;
    int mid = l + r >> 1;
    build (u << 1,l,mid),build (u << 1 | 1,mid + 1,r);
    push_up (u);
}
void modify (int u,int l,int r) {
	if (l <= tr[u].l && tr[u].r <= r) {
		opt_rev (u);
		return ;
	}
    push_down (u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid) modify (u << 1,l,r);
    if (r >= mid + 1) modify (u << 1 | 1,l,r);
    push_up (u);
}
node query (int u,int l,int r) {
    if (l <= tr[u].l && tr[u].r <= r) return tr[u];
    push_down (u);
    int mid = tr[u].l + tr[u].r >> 1;
    if (l <= mid && r >= mid + 1) {
        node ans;
        push_up (ans,query (u << 1,l,r),query (u << 1 | 1,l,r));
        return ans;
    }
    if (l <= mid) return query (u << 1,l,r);
    return query (u << 1 | 1,l,r);
}
int main () {
    cin >> n >> m;
    for (int i = 1;i <= n;i++) {
    	char ch;
    	cin >> ch;
    	a[i] = ch - '0';
	}
    build (1,1,n);
    while (m--) {
        int op,l,r;
        cin >> op >> l >> r;
        if (op == 1) modify (1,l,r);
        else cout << query (1,l,r).vmax[1] << endl;
    }
    return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 思路

可以看出来是个很典的套路线段树，这里大概主要讲 `pushup` 和 `pushdown` 怎么写。

首先我们先来维护一段区间的左边零最长的和一最长的，右边同理，然后对于答案维护一个最长的零和最长的一，对于标记，表示的是区间反转，这里我再维护一个长度，根据写法可以不维护。

首先以左边最长的一为例，因为别的都可以对称。

他可以通过左儿子最长的一来更新，如果最长的一和长度相等就说明左儿子全是一，那么就是左边的长度加上右儿子最长的一。

然后答案的更新就是从子节点的最大的更新过来，如果左边最长的一或者右边最长的一更长就用他们来更新。

然后 `pushdown` 就是交换所有零和一的数组，然后记得更新的勤点就好了。

# 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (l); i >= (r); i--)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
using i64 = long long;
const int maxn = 5e5 + 10;
struct node {
    int mxl1, mxl0;
    int mxr1, mxr0;
    int ans1, ans0;
    int len, tag;
} tr[maxn * 4];
char s[maxn];
void pushup(node& u, node lc, node rc) {
    u.ans1 = max(max(lc.ans1, rc.ans1), lc.mxr1 + rc.mxl1);
    u.ans0 = max(max(lc.ans0, rc.ans0), lc.mxr0 + rc.mxl0);
    u.len = lc.len + rc.len;
    u.mxl1 = max(lc.mxl1, (lc.len == lc.mxl1) * (lc.len + rc.mxl1));
    u.mxl0 = max(lc.mxl0, (lc.len == lc.mxl0) * (lc.len + rc.mxl0));
    u.mxr1 = max(rc.mxr1, (rc.len == rc.mxr1) * (rc.len + lc.mxr1));
    u.mxr0 = max(rc.mxr0, (rc.len == rc.mxr0) * (rc.len + lc.mxr0));
}
void pushup(int p) {
    pushup(tr[p], tr[p * 2], tr[p * 2 + 1]);
}
void pushdown(int p) {
    if (tr[p].tag) {
        tr[p * 2].tag ^= 1;
        tr[p * 2 + 1].tag ^= 1;
        swap(tr[p * 2].mxl1, tr[p * 2].mxl0);
        swap(tr[p * 2].mxr1, tr[p * 2].mxr0);
        swap(tr[p * 2].ans1, tr[p * 2].ans0);
        swap(tr[p * 2 + 1].mxl1, tr[p * 2 + 1].mxl0);
        swap(tr[p * 2 + 1].mxr1, tr[p * 2 + 1].mxr0);
        swap(tr[p * 2 + 1].ans1, tr[p * 2 + 1].ans0);
        tr[p].tag = 0;
    }
}
void build(int p, int l, int r) {
    if (l == r) {
        tr[p].len = 1;
        if (s[l] == '1') {
            tr[p].ans1 = tr[p].mxl1 = tr[p].mxr1 = 1;
        } else {
            tr[p].ans0 = tr[p].mxl0 = tr[p].mxr0 = 1;
        }
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    pushup(p);
}
void update(int l, int r, int p, int L, int R) {
    if (L >= l && R <= r) {
        swap(tr[p].mxl1, tr[p].mxl0);
        swap(tr[p].mxr1, tr[p].mxr0);
        swap(tr[p].ans1, tr[p].ans0);
        tr[p].tag ^= 1;
        return;
    }
    pushdown(p);
    int mid = (L + R) / 2;
    if (l <= mid) {
        update(l, r, p * 2, L, mid);
    } if (mid < r) {
        update(l, r, p * 2 + 1, mid + 1, R);
    }
    pushup(p);
}
node query(int l, int r, int p, int L, int R) {
    if (L >= l && R <= r) {
        return tr[p];
    }
    pushdown(p);
    int mid = (L + R) / 2;
    if (r <= mid) {
        return query(l, r, p * 2, L, mid);
    } else if (l > mid) {
        return query(l, r, p * 2 + 1, mid + 1, R);
    } else {
        node res;
        pushup(res, query(l, r, p * 2, L, mid), query(l, r, p * 2 + 1, mid + 1, R));
        return res;
    }
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, Q;
    cin >> n >> Q;
    cin >> (s + 1);
    build(1, 1, n);
    while(Q--) {
        int op, l, r;
        cin>>op;
        if (op == 1) {
            cin >> l >> r;
            update(l, r, 1, 1, n);
        } if (op == 2) {
            cin >> l >> r;
            cout << query(l, r, 1, 1, n).ans1 << "\n";
        }
    }
    return 0;
}
```

---

