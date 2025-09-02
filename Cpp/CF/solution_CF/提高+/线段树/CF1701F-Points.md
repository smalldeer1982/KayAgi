# Points

## 题目描述

若 $ i < j < k $ 且 $ k - i \le d $ 那么在数轴上的三个点 $ i $ , $ j $ 与 $ k $ 是美丽的一组点。 $d$ 是“定义三元组是否美丽的参数”。

在一个初始为空的数轴上给出一些点，你需要：

- 增加一个点
- 移除一个点
- 计算美丽的点的组数

## 说明/提示

对于 $100\%$ 的数据， $1\le q , d\le 2\cdot 10^5$ $ 1 \le a_i \le 2 \cdot 10^5 $

## 样例 #1

### 输入

```
7 5
8 5 3 2 1 5 6```

### 输出

```
0
0
1
2
5
1
5```

# 题解

## 作者：cwfxlh (赞：11)

# [CF1701F](https://www.luogu.com.cn/problem/CF1701F)  
很水的一道 F。   
本题要求计算“美丽”点对数，我们先不考虑修改的问题，考虑如何单纯地去计算。   
根据定义，令 $x$ 为点对最左端的点，$cnt_x$ 表示 $[(x+1),(x+d)]$ 中的点数，则以 $x$ 为左端点的美丽点对数为 $\frac{cnt_x\times(cnt_x-1)}{2}$，这个是很明显的。那么对于整个数轴而言，总点对数就应该是： 
$$\sum_{x\in S}\frac{cnt_x\times(cnt_x-1)}{2}$$   

$S$ 是点集。   
接下来考虑修改。如果加入一个点 $x$，$[x-d,x-1]$ 的 $cnt$ 会加 $1$，$x$ 本身增加 $[x+1,x+d]$ 的点数。减少过程相反。   

再考虑 $cnt_x$ 的变化对于总和的影响。如果 $cnt_x$ 增加 $1$，则总和增加 $cnt_x$，如果 $cnt_x$ 减少 $1$，则总和减少 $cnt_x-1$。于是我们用两个线段树维护区间内的点数和 $cnt$ 和，即可做到 $\Theta(\log n)$ 复杂度的修改了。  
上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,d,mp[500003],k1,k2,k3,k4,k5,ans;
struct SegT{
	int st;
	int ed;
	int sum1; 
	int sum2;
	int lzmk;
}T[2000003];
void build(int now,int l,int r){
	T[now].st=l;
	T[now].ed=r;
	if(l==r)return;
	build(now*2,l,((l+r)>>1));
	build(now*2+1,((l+r)>>1)+1,r);
	return;
}
void pushdown(int now){
	T[now*2].sum1+=T[now].lzmk*T[now*2].sum2;
	T[now*2+1].sum1+=T[now].lzmk*T[now*2+1].sum2;
	T[now*2].lzmk+=T[now].lzmk;
	T[now*2+1].lzmk+=T[now].lzmk;
	T[now].lzmk=0;
	return;
}
void add1(int now,int X,int Y,int val){
	if(T[now].st>Y||T[now].ed<X)return;
	if(T[now].st>=X&&T[now].ed<=Y){
		T[now].sum1+=val*T[now].sum2;
		T[now].lzmk+=val;
		return;
	}
	pushdown(now);
	add1(now*2,X,Y,val);
	add1(now*2+1,X,Y,val);
	T[now].sum1=T[now*2].sum1+T[now*2+1].sum1;
	return;
}
void add2(int now,int X,int Y,int val){
	if(T[now].st>Y||T[now].ed<X)return;
	if(T[now].st==T[now].ed){
		T[now].sum2+=val;
		return;
	}
	pushdown(now);
	add2(now*2,X,Y,val);
	add2(now*2+1,X,Y,val);
	T[now].sum2=T[now*2].sum2+T[now*2+1].sum2;
	return;
}
int getval1(int now,int X,int Y){
	if(T[now].st>Y||T[now].ed<X)return 0;
	if(T[now].st>=X&&T[now].ed<=Y)return T[now].sum1;
	pushdown(now);
	return getval1(now*2,X,Y)+getval1(now*2+1,X,Y);
}
int getval2(int now,int X,int Y){
	if(T[now].st>Y||T[now].ed<X)return 0;
	if(T[now].st>=X&&T[now].ed<=Y)return T[now].sum2;
	pushdown(now);
	return getval2(now*2,X,Y)+getval2(now*2+1,X,Y);
}
signed main(){
	scanf("%lld%lld",&n,&d);
	build(1,1,200000);
	for(int i=1;i<=n;i++){
		scanf("%lld",&k1);
		if(mp[k1]==0){
			mp[k1]=1;
			k2=getval2(1,k1+1,k1+d);
			ans+=k2*(k2-1)/2;
			ans+=getval1(1,k1-d,k1-1);
			add1(1,k1-d,k1-1,1);
			add2(1,k1,k1,1);
			add1(1,k1,k1,k2);
		}
		else{
			mp[k1]=0;
			k2=getval1(1,k1,k1);
			ans-=k2*(k2-1)/2;
			ans-=getval1(1,k1-d,k1-1);
			ans+=getval2(1,k1-d,k1-1);
			add1(1,k1,k1,-k2);
			add2(1,k1,k1,-1);
			add1(1,k1-d,k1-1,-1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：Messywind (赞：10)

**题意**

给定两个正整数 $q, d$，定义三元组 $(i, j, k)$ 满足 $i < j < k, k - i \le d$，为**美丽三元组**，现在有一个空集和 $q$ 组询问，每次给定一个正整数 $x$，若 $x$ 不在集合，那么将 $x$ 加入集合，若 $x$ 在集合中，那么将 $x$ 从集合中删除，每次询问计算集合中**美丽三元组**的个数。

**分析：**

考虑每个数从集合加入或删除的贡献，对于一个数 $x$，从区间 $[x, x + d]$ 中选出任意两个不同的数都可以组成美丽三元组(假设 $x$ 为三元组中的最小值)，记区间中在集合的数量为 $cnt$，那么方案数为 $\dbinom{cnt}{2}$，那么考虑区间 $[x - d, x - 1]$，对区间中的每个数 $i$，考虑 $x$ 加入后的影响，设区间 $[i, i + d]$ 在集合中的个数为 $a_i$，那么美丽三元组的个数为 $\dbinom{a_i}{2}$，则 $x$ 加入后的美丽三元组数量为 $\dbinom{a_i + 1}{2}$，设整个集合为 $S$，那么在区间 $[x - d, x - 1]$ 中新增的美丽三元组数量就为 $\sum\limits_{i = x - d} ^ {x - 1} \left (\dbinom{a_i + 1}{2} - \dbinom{a_i}{2} \right ) [i \in S] = \sum\limits_{i = x - d} ^ {x - 1}a_i [i \in S]$，对于 $x$ 删除后的影响就为 $\sum\limits_{i = x - d} ^ {x - 1} \left (\dbinom{a_i}{2} - \dbinom{a_i - 1}{2} \right ) [i \in S] = \sum\limits_{i = x - d} ^ {x - 1} a_i [i \in S]$

考虑使用线段树，我们重点要维护的是每个数 $x$ 在区间 $[x, x + d]$ 中在集合里的个数，那么每次加入或删除操作就相当于对区间 $[x - d, x - 1]$ 进行区间 $+1$ 或 $-1$ 操作，线段树中维护四个值：$\text{cnt}$ 代表区间里在集合中的数的个数，$\text{add}$ 代表区间加的懒标记，$\text{val}$ 代表每个数 $i$ 在区间 $[i, i + d]$ 中在集合里的个数，$\text{sum}$ 代表**存在集合中的每个数** $i$ 在区间 $[i, i + d]$ 中在集合里的个数。因为每个数是否存在于集合中由 $\text{cnt}$ 是否为 $1$ 来决定，相当于 $\text{val}$ 是全部的值，也就是说无论区间 $[x - d, x - 1]$ 的某个数存不存在于集合，我们都要维护，那么真正的答案是 $\text{sum}$，也就是那些存在于集合里的数的值，通过懒标记用 $\text{cnt} \times \text{val}$ 来下传，这样就巧妙地算出了一段区间存在于集合中的数对答案的贡献，至于区间 $[x, x + d]$ 的贡献可以直接查询 $\text{val}_x$ 的单点值并给答案贡献 $\dbinom{\text{val}_x}{2}$

## 代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 2e5;
struct SegmentTree {
    struct Info {
        int l, r, cnt, add, val, sum;
    };
    vector<Info> tr;
    SegmentTree(int n) : tr(n << 2) {
        function<void(int, int, int)> build = [&](int u, int l, int r) {
            if (l == r) {
                tr[u] = {l, r};
            } else {
                tr[u] = {l, r};
                int mid = l + r >> 1;
                build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
                pushup(u);
            }
        };
        build(1, 1, n);
    }
    void pushdown(int u) {
        if (tr[u].add) {
            tr[u << 1].add += tr[u].add, tr[u << 1 | 1].add += tr[u].add;
            tr[u << 1].val += (tr[u << 1].r - tr[u << 1].l + 1) * tr[u].add;
            tr[u << 1 | 1].val += (tr[u << 1 | 1].r - tr[u << 1 | 1].l + 1) * tr[u].add;
            tr[u << 1].sum += tr[u << 1].cnt * tr[u].add;
            tr[u << 1 | 1].sum += tr[u << 1 | 1].cnt * tr[u].add;
            tr[u].add = 0;
        }
    }
    void pushup(int u) {
        tr[u].cnt = tr[u << 1].cnt + tr[u << 1 | 1].cnt;
        tr[u].val = tr[u << 1].val + tr[u << 1 | 1].val;
        tr[u].sum = tr[u << 1].sum + tr[u << 1 | 1].sum;
    }
    void modifycnt(int u, int pos, int c) {
        if (!pos) return ;
        if (tr[u].l == tr[u].r) {
            tr[u].cnt += c;
            if (!tr[u].cnt) {
                tr[u].sum = 0;
            } else {
                tr[u].sum = tr[u].val;
            }
            return ;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (pos <= mid) {
            modifycnt(u << 1, pos, c);
        } else {
            modifycnt(u << 1 | 1, pos, c);
        }
        pushup(u);
    }
    void modifysum(int u, int l, int r, int c) {
        if (l > r) return ;
        if (tr[u].l >= l && tr[u].r <= r) {
            tr[u].val += (tr[u].r - tr[u].l + 1) * c;
            tr[u].sum += tr[u].cnt * c;
            tr[u].add += c;
            return ;
        }
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modifysum(u << 1, l, r, c);
        if (r > mid) modifysum(u << 1 | 1, l, r, c);
        pushup(u);
    }
    int askval(int u, int pos) {
        if (!pos) return 0;
        if (tr[u].l == tr[u].r) return tr[u].val;
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1, res = 0;
        if (pos <= mid) {
            return askval(u << 1, pos);
        } else {
            return askval(u << 1 | 1, pos);
        }
    }
    int asksum(int u, int l, int r) {
        if (l > r) return 0;
        if (tr[u].l >= l && tr[u].r <= r) return tr[u].sum;
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1, res = 0;
        if (l <= mid) res += asksum(u << 1, l, r);
        if (r > mid) res += asksum(u << 1 | 1, l, r);
        return res;
    }
};
signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, d;
    cin >> n >> d;
    vector<int> st(N + 1);
    SegmentTree tr(N + 1);
    int ans = 0;
    for (int i = 1; i <= n; i ++) {
        int x;
        cin >> x;
        int l = max(1ll, x - d), r = x - 1;
        if (!st[x]) {
            ans += tr.asksum(1, l, r);
            tr.modifysum(1, l, r, 1);
            int cnt = tr.askval(1, x);
            ans += cnt * (cnt - 1) / 2;
            tr.modifycnt(1, x, 1);
        } else if (st[x]) {
            tr.modifysum(1, l, r, -1);
            ans -= tr.asksum(1, l, r);
            int cnt = tr.askval(1, x);
            ans -= cnt * (cnt - 1) / 2;
            tr.modifycnt(1, x, -1);
        }
        st[x] ^= 1;
        cout << ans << "\n";
    }
}
```

---

## 作者：_SeeleVollerei_ (赞：4)

这场 edu 应该是最近最简单的一次了。

考虑简化统计问题的答案，对于每个存在的数 $x$ 维护 $cnt_x$ 表示 $[x+1,x+d]$ 有多少个数，那么答案为 $\sum\binom{cnt_x}{2}$，考虑怎么维护。

考虑插入一个数 $x$ 的时候 ，相当于令 $cnt_{[x-d,x-1]}$ 区间加 $1$，随便列一下式子就会发现 $\binom{x}{2}\to\binom{x+1}{2}$ 相当于 $+x$，那么只要维护一个区间的 $cnt$ 的和即可。

然后求 $[x+1,x+d]$ 有多少个数存在，相当于直接求 $cnt_x$，这就是一个简单的单点修改。

删除反过来即可，相当于区间减，单点清空，最后都是查询全局和。

复杂度 $O(q\log n)$，$n$ 是值域。

https://codeforces.com/contest/1701/submission/163386880

---

## 作者：TTpandaS (赞：2)

考虑 $x$ 作为 $i,j,k$ 的贡献。

当 $x$ 作为 $i$ 时，令 $n=\operatorname{ask}(x+1,x+d),\operatorname{ask} (l,r)$ 表示在值域 $l$ 到 $r$ 中存在的点的个数。那么贡献就是在 $n$ 个点中任取 $2$ 个的数量，即 $\dfrac{n(n-1)}{2}$。

当 $x$ 作为 $k$ 时，令 $m=\operatorname{ask}(x-d,x-1)$，那么贡献就是在 $m$ 个点中任取 $2$ 个的数量，即 $\dfrac{m(m-1)}{2}$。

当 $x$ 作为 $j$ 时，贡献就是有多少点对 $(l,r)$ 满足 $r-l \leq d,l <x <r$。对于一个 $x$，我们是不容易直接计算出点对的个数的，那么就解决逆向问题，考虑 $x$ 会将哪些点变成“能成为 $j$ 的点”。

对于一个点 $x$，先找到最小的存在的点 $y$ 满足 $x>y,x-y \leq d$，那么点 $y+1$ 到 $x-1$ 都可以作为“能成为 $j$ 的点”。再找到最大的存在的点 $y$ 满足 $x<y,y-x \leq d$，那么点 $x+1$ 到 $y-1$ 都可以作为“能成为 $j$ 的点”。

寻找 $y$ 点可以使用一个二分实现。计算作为 $i$ 点和 $k$ 点时的贡献相当于区间查询，单点修改。计算作为 $i$ 点和 $k$ 点时的贡献相当于单点查询，区间修改。

时间复杂度 $O(n \log^2n)$，本题时间充裕，可以通过。

```cpp
  void Dhxqwq(){
      build(1,1,200000,0);
      build(1,1,200000,1);
      for(int i=1;i<=q;i++){
          ans[i]=ans[i-1];
          if(!f[a[i]]){
              f[a[i]]=1;
              int n=ask(1,a[i]+1,min(a[i]+d,200000ll),0);
              ans[i]+=n*(n-1)/2;
              int m=ask(1,max(1ll,a[i]-d),a[i]-1,0);
              ans[i]+=m*(m-1)/2;
              ans[i]+=ask(1,a[i],a[i],1);
              add(1,a[i],a[i],1,0);
              int l=a[i]+1,r=min(a[i]+d,200000ll);
              int R=-1;
              while(l<=r){
                  int mid=(l+r)>>1;
                  if(ask(1,a[i]+1,mid,0)==n){
                      R=mid;
                      r=mid-1;
                  }
                  else{
                      l=mid+1;
                  }
              }
              if(R!=-1){
                  add(1,a[i]+1,R-1,1,1);
              }
              l=max(1ll,a[i]-d),r=a[i]-1;
              int L=-1;
              while(l<=r){
                  int mid=(l+r)>>1;
                  if(ask(1,mid,a[i]-1,0)==m){
                      L=mid;
                      l=mid+1;
                  }
                  else{
                      r=mid-1;
                  }
              }
              if(L!=-1){
                  add(1,L+1,a[i]-1,1,1);
              }
          }
          else{
              f[a[i]]=0;
              int n=ask(1,a[i]+1,min(a[i]+d,200000ll),0);
              ans[i]-=n*(n-1)/2;
              int m=ask(1,max(1ll,a[i]-d),a[i]-1,0);
              ans[i]-=m*(m-1)/2;
              ans[i]-=ask(1,a[i],a[i],1);
              add(1,a[i],a[i],-1,0);
              int l=a[i]+1,r=min(a[i]+d,200000ll);
              int R=-1;
              while(l<=r){
                  int mid=(l+r)>>1;
                  if(ask(1,a[i]+1,mid,0)==n){
                      R=mid;
                      r=mid-1;
                  }
                  else{
                      l=mid+1;
                  }
              }
              if(R!=-1){
                  add(1,a[i]+1,R-1,-1,1);
              }
              l=max(1ll,a[i]-d),r=a[i]-1;
              int L=-1;
              while(l<=r){
                  int mid=(l+r)>>1;
                  if(ask(1,mid,a[i]-1,0)==m){
                      L=mid;
                      l=mid+1;
                  }
                  else{
                      r=mid-1;
                  }
              }
              if(L!=-1){
                  add(1,L+1,a[i]-1,-1,1);
              }
          }
      }
  }
```


---

## 作者：daniEl_lElE (赞：2)

考虑用线段树维护对于每个 $k$ 在 $k-d$ 到 $k-1$ 的范围内有多少符合要求的 $i$。计其数量为 $m$，则其贡献为 $\binom{m}{2}$。稍微拆分一下，$\frac{m^2}{2}-\frac{m}{2}$，那么我们只需要维护区间和和区间平方和即可。这就是最基础的思路。

考虑一下修改操作，加入或删除一个点 $x$ 可以起到哪些作用呢？

首先，对这个点，加入他后可以很快算出来 $x-d$ 到 $x-1$ 范围内的点，那么我们需要区间查询。

其次，对于 $x+1$ 到 $x+d$ 的点也会受到影响，本质上就是区间加。对于区间平方和来说，也算是一个较为经典的套路，区间和增加 $l$，那么区间平方和增加了 $2\times sum\times l+l^2$，其中 $sum$ 为区间和。

查询不怎么用讲，甚至你可以直接全局。

算是一道不错的线段树小拼接题目。

代码的话，我觉得你要是会线段树基本就会写了。如果有疑惑的可以对照相应部分查看呢，给一些细节部分吧：

### `pushup` 和 `pushdown` 操作

```cpp
void pushup(int i){
	f[i]=f[i*2]+f[i*2+1];
	g[i]=g[i*2]+g[i*2+1];
	cnt[i]=cnt[i*2]+cnt[i*2+1];
	size[i]=size[i*2]+size[i*2+1];
}
void pushdown(int i){
	g[i*2]+=f[i*2]*2*lzt[i]+cnt[i*2]*lzt[i]*lzt[i];
	f[i*2]+=lzt[i]*cnt[i*2];
	lzt[i*2]+=lzt[i];
	g[i*2+1]+=f[i*2+1]*2*lzt[i]+cnt[i*2+1]*lzt[i]*lzt[i];
	f[i*2+1]+=lzt[i]*cnt[i*2+1];
	lzt[i*2+1]+=lzt[i];
	lzt[i]=0;
}
```

### 添加与删除部分（更新目前点）

```cpp
int qry(int i,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr){
		return cnt[i];
	}
	if(ql>r||qr<l) return 0;
	pushdown(i);
	return qry(i*2,l,mid,ql,qr)+qry(i*2+1,mid+1,r,ql,qr);
}
void add(int i,int l,int r,int pos){
	if(l==r){
		cnt[i]++;
		if(i==1) return ;
		f[i]=qry(1,1,M,max(pos-k,1ll),pos-1);
		g[i]=f[i]*f[i];
		return ;
	}
	pushdown(i);
	if(pos<=mid) add(i*2,l,mid,pos);
	else add(i*2+1,mid+1,r,pos);
	pushup(i);
	return ;
}
void del(int i,int l,int r,int pos){
	if(l==r){
		cnt[i]--;
		f[i]=g[i]=0;
		return ;
	}
	pushdown(i);
	if(pos<=mid) del(i*2,l,mid,pos);
	else del(i*2+1,mid+1,r,pos);
	pushup(i);
	return ;
}
```

### 区间修改

```cpp
void modify(int i,int l,int r,int ql,int qr,int cg){
	if(ql<=l&&r<=qr){
		g[i]+=(f[i]*2*cg+cnt[i]);
		f[i]+=cg*cnt[i];
		lzt[i]+=cg;
		return ;
	}
	if(ql>r||qr<l) return ;
	pushdown(i);
	modify(i*2,l,mid,ql,qr,cg);
	modify(i*2+1,mid+1,r,ql,qr,cg);
	pushup(i);
	return ;
}
```

### 查询

```cpp
int qf(int i,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return f[i];
	if(ql>r||qr<l) return 0;
	pushdown(i);
	return qf(i*2,l,mid,ql,qr)+qf(i*2+1,mid+1,r,ql,qr);
}
int qg(int i,int l,int r,int ql,int qr){
	if(ql<=l&&r<=qr) return g[i];
	if(ql>r||qr<l) return 0;
	pushdown(i);
	return qg(i*2,l,mid,ql,qr)+qg(i*2+1,mid+1,r,ql,qr);
}
```

### 主函数：添加，删除，查询

```cpp
if(mp[a]){
	mp[a]=0;
	tree.del(1,1,M,a);
	tree.modify(1,1,M,a+1,min(a+k,200001ll),-1);
}
else{
	mp[a]=1;
	tree.add(1,1,M,a);
	tree.modify(1,1,M,a+1,min(a+k,200001ll),1);
}
cout<<(tree.qg(1,1,M,1,200000)-tree.qf(1,1,M,1,200000))/2<<endl;
```

---

## 作者：Sellaris (赞：1)

- **TAG :** 线段树 

- 为了讲述方便，首先定义 $c_i$ 为数字 $i$ 出现的次数。阅读题意发现每个数最多只存在一个。

- **于是不难想到对于一个数 $i$，使它是三元组中最小的。**

- 于是定义两个函数，很容易理解其含义：

$$g(i) = \sum_{j=i+1}^{i+d} c_j$$

$$f(i) = \binom{g(i)}{2}$$ 

- 则答案即为(其中 $size$ 为值域 )：

$$\sum_{i=1}^{size} f(i) \quad c_i = 1$$

- 发现二项式系数中 $2$ 是不变的，于是把组合数拆开来。即:

$$f(i) = \frac{1}{2} \times g(i) \times ( g(i) - 1)$$

- 当插入一个数字 $x$ 的时候，对 $i \in [x-d,x-1]$ 这个区间的每个 $g(i)$ 贡献是 $1$，反之是 $-1$。

- 对于一个数 $i$，在 $[i+1,i+d]$ 区间插入 $k$ 个数 ,对于 $f(i)$ 的贡献是 :

$$ \frac{1}{2} \times (f(i)+k) \times (f(i)+k-1) - \frac{1}{2} \times f(i) \times (f(i) - 1) $$

- 化简即得到 ：

$$ k \times f(i)+\frac{k \times (k - 1)}{2} $$

- 同理删去 $k$ 个数同上式，不同的是化简之后：

$$ - ( k \times f(i) )+\frac{k \times (k + 1)}{2} $$

- 于是考虑线段树维护函数 $f(x)$ 和 $g(x)$。同时维护一个变量 $tot$ 表示当前线段树区间内有几个数存在，因为向上更新的时候需要乘上区间内的个数。因为线段树维护前缀和，于是最后线段树的根结点的 $f(x)$ 即为答案。

- 具体实现方面，我们只需要维护 $f(x)$、$g(x)$ 和变量 $tot$ 的区间更新和单点更新，同时实现 $tot$ 的单点查询为 $g(x)$ 服务即可。


```cpp
///*****Sellaris*****///
//#pragma once
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include <bits/stdc++.h>
//#include <bits/extc++.h>
#define ll long long
using namespace std;
//using namespace __gnu_pbds;
const int mo=1e9+7;
const int N=2e5+10;
inline int read(){
    int ret=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+ch-'0';ch=getchar();}
    return ret*f; //x=(x<<1)+(x<<3)+(ch^48);
}
inline int mod(int x){return x>=mo? x%mo :x;}

int n; 
int vis[N];
//g[i]=[i+1,i+d]的数目，f(i) = (g[i]*(g[i]-1))/2 

struct node{
	int l,r;
	ll sum, tag, ans;//g[]，l-r区间数个数，f[]
	ll tot;
}tr[N*8];

void pushup(int p){
	tr[p].ans=tr[p<<1].ans+tr[p<<1|1].ans;
	tr[p].sum=tr[p<<1].sum+tr[p<<1|1].sum;
	tr[p].tot=tr[p<<1].tot+tr[p<<1|1].tot;
}
void pushdown(int p){
	if(tr[p].tag!=0){
		int k=tr[p].tag;
		
		if(k>0){
			tr[p<<1].ans+=1ll*k*tr[p<<1].sum;
			tr[p<<1].ans+=1ll*k*(k-1)/2*tr[p<<1].tot;
			
			tr[p<<1|1].ans+=1ll*k*tr[p<<1|1].sum;
			tr[p<<1|1].ans+=1ll*k*(k-1)/2*tr[p<<1|1].tot;
		}else{
			tr[p<<1].ans+=1ll*k*tr[p<<1].sum;
			tr[p<<1].ans+=1ll*(-k)*(-(k-1))/2*tr[p<<1].tot;
			
			tr[p<<1|1].ans+=1ll*k*tr[p<<1|1].sum;
			tr[p<<1|1].ans+=1ll*(-k)*(-(k-1))/2*tr[p<<1|1].tot;
		}
		tr[p<<1].sum+=1ll*k*tr[p<<1].tot;
		tr[p<<1|1].sum+=1ll*k*tr[p<<1|1].tot;
		tr[p<<1].tag+=1ll*k;
		tr[p<<1|1].tag+=1ll*k;
		
		tr[p].tag=0;
	}
}
void build(int p,int l,int r){
	tr[p].l=l;
	tr[p].r=r;
	tr[p].sum=tr[p].ans=tr[p].tot=tr[p].tag=0;
	if(l==r) return;
//	cout<<p<<" "<<l<<" "<<r<<endl;
	int mid=l+r>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	pushup(p);
}
void change(int p,int k,int v,int vtot){
	if(tr[p].l==tr[p].r){
		tr[p].sum=1ll*v;
		tr[p].ans=1ll*v*(v-1)/2;//C[2][V]//0*(0-1)/2=0//1*(1-1)/2=0
		tr[p].tot=1ll*vtot;
		return; 
	}
	int mid=tr[p].l+tr[p].r>>1;
	pushdown(p);
	if(k<=mid) change(p<<1,k,v,vtot);
	else change(p<<1|1,k,v,vtot);
	pushup(p);
}
/*
加入k个数对答案的贡献是(f[i]+k)*(f[i]+k-1)/2- f[i]*(f[i]-1)/2 = k*f[i] +k*(k-1)/2
*/
void modify(int p,int ql,int qr,int k){
	//if(k>0) cout<<tr[p].l<<" x "<<tr[p].r<<endl;
	if(ql<=tr[p].l && tr[p].r<=qr){
		if(k>0){//ans=∑(f[i] && c[i]!=0 c是原数组的桶)
			tr[p].ans+=1ll*k*tr[p].sum; 
			tr[p].ans+=1ll*k*(k-1)/2*tr[p].tot;
		}else{
			tr[p].ans+=1ll*k*tr[p].sum;//k是-的 
			tr[p].ans+=1ll*(-k)*(-(k-1))/2*tr[p].tot;//-k是正的 
		}
		tr[p].sum+=1ll*k*tr[p].tot;//区间f[]+=区间结点总数每个加k 
		tr[p].tag+=1ll*k;
		return;
	}
	
	//if(k>0) cout<<tr[p].l<<" x "<<tr[p].r<<endl;
	int mid=tr[p].l+tr[p].r>>1;
	pushdown(p);
	if(ql<=mid) modify(p<<1,ql,qr,k);
	if(qr>mid) modify(p<<1|1,ql,qr,k);
	pushup(p);
}
ll query(int p,int ql,int qr){
	if(ql<=tr[p].l && qr>=tr[p].r){
		return tr[p].tot;
	}
	//cout<<tr[p].l<<" "<<tr[p].r<<" "<<endl;
	ll res=0;
	pushdown(p);
	int mid=tr[p].l+tr[p].r>>1;
	if(ql<=mid) res+=query(p<<1,ql,qr);
	if(qr>mid) res+=query(p<<1|1,ql,qr);
	//pushup(p);
	return res;
}
int main(){
	int d;
	scanf("%d %d",&n,&d);
	const int maxn=2e5;
	build(1,1,maxn);
	for(int i=1;i<=n;i++){
		int x;
		scanf("%d",&x);
 		if(vis[x]){
 			modify(1,max(1,x-d),max(1,x-1),-1);
			change(1,x,0,0);
 		}
		else{
			modify(1,max(1,x-d),max(1,x-1),1);
			ll ask=query(1,min(x+1,maxn),min(maxn,x+d));
			change(1,x,ask,1);
		}
		vis[x]^=1;
		printf("%lld\n", tr[1].ans);
	}
	return 0;
}
```


---

## 作者：ifffer_2137 (赞：0)

树形数据结构入门题。

~~于是脑瘫写了两 log~~。
### 题意
数轴上动态加点删点，求全局满足 $i<j<k\le i+d$ 的点组数量。
### 分析
首先有个显然观察是钦定 $i
$ 以后点组数是 $[i+1,i+d]$ 内的点中选两个的方案数。设 $\text{cnt}_i$ 表示 $[i+1,i+d]$ 内点数，答案即为 $\sum_{i}\frac{\text{cnt}_i(\text{cnt}_i-1)}{2}$

考虑动态维护答案。看加入一个点 $x$ 的贡献，删除类似。

首先以 $x$ 为 $i$，那么求出 $\text{cnt}_i$ 直接加上贡献就好了。数轴上单点修区间数点朴素 BIT 即可。

然后以 $x$ 为 $[i+1,i+d]$ 内的点，发现相当于对所有 $[x-d,x-1]$ 内存在的点 $j$，$\text{cnt}_j$ 加 $1$。
求个差量得到 $\frac{(\text{cnt}_j+1)\text{cnt}_j}{2}-\frac{\text{cnt}_j(\text{cnt}_j-1)}{2}=\text{cnt}_j$，所以用个 sgt 维护 $\text{cnt}_i$，区间内**存在的点**加区间求和即可。注意是区间内存在的点，所以下传标记要注意区间和数组的增量不应乘区间长度而应该乘区间内点数，这个直接在 BIT 上查即可。

事实上 sgt 同时维护区间数点显然少 log，但是我先写了 BIT 不想改了，随便它。

时间复杂度 $O(n\log^2n)$。
### 代码
实现注意修改或查询区间的边界，注意删点带来影响的操作步骤。
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=2e5+5;
const int N=2e5;
namespace Data_Structure{
	class Fenwick_Tree{
	public:
		int c[maxn];
		int lowbit(int x){return x&(-x);}
		void update(int x,int k){while(x<=N){c[x]+=k;x+=lowbit(x);}}
		int query(int x){if(x>N) x=N;int res=0;while(x){res+=c[x];x-=lowbit(x);}return res;}
		int getsum(int l,int r){return query(r)-query(l-1);}
	}tr;
	class Segment_Tree{
	public:
		int sm[maxn<<2],tag[maxn<<2];
		void pushup(int o){sm[o]=sm[o*2]+sm[o*2+1];}
		void pushdown(int o,int l,int r){
			if(!tag[o]) return;
			int m=(l+r)>>1;
			tag[o*2]+=tag[o],sm[o*2]+=tr.getsum(l,m)*tag[o];
			tag[o*2+1]+=tag[o],sm[o*2+1]+=tr.getsum(m+1,r)*tag[o];
			tag[o]=0; return;
		}
		void update(int o,int l,int r,int x,int y,int k){
			if(x>y) return;
			if(x<=l&&r<=y){
				tag[o]+=k,sm[o]+=tr.getsum(l,r)*k;
				return;
			}
			int m=(l+r)>>1;pushdown(o,l,r);
			if(x<=m) update(o*2,l,m,x,y,k);
			if(y>m) update(o*2+1,m+1,r,x,y,k);
			pushup(o);
		}
		void assign(int o,int l,int r,int x,int k){
			if(l==r){sm[o]=k;return;}
			int m=(l+r)>>1;pushdown(o,l,r);
			if(x<=m) assign(o*2,l,m,x,k);
			else assign(o*2+1,m+1,r,x,k);
			pushup(o);
		}
		int query(int o,int l,int r,int x,int y){
			if(x>y) return 0;
			if(x<=l&&r<=y) return sm[o];
			int m=(l+r)>>1,res=0;pushdown(o,l,r);
			if(x<=m) res+=query(o*2,l,m,x,y);
			if(y>m) res+=query(o*2+1,m+1,r,x,y);
			return res;
		}
	}sgt;
}
using namespace Data_Structure;
//-------------------------------------------
int q,d,ans;
int a[maxn];
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	q=read(),d=read();
	while(q--){
		int x=read();
		if(!a[x]){
			int cnt=tr.getsum(x+1,x+d);
			ans+=cnt*(cnt-1)/2;
			tr.update(x,1);
			ans+=sgt.query(1,1,N,max(1ll,x-d),x-1);
			sgt.update(1,1,N,max(1ll,x-d),x-1,1);
			sgt.assign(1,1,N,x,cnt);
		}else{
			int cnt=tr.getsum(x+1,x+d);
			ans-=cnt*(cnt-1)/2;
			tr.update(x,-1);
			sgt.update(1,1,N,max(1ll,x-d),x-1,-1);
			ans-=sgt.query(1,1,N,max(1ll,x-d),x-1);
			sgt.assign(1,1,N,x,0);
		}
		cout<<ans<<'\n';
		a[x]^=1;
	}
	return 0;
}
//Begin Coding: 8:48
//Finish Debugging: 9:23
```

---

## 作者：C_Pos_Princess (赞：0)

## 题目描述
若 $ i < j < k $ 且 $ k - i \le d $ 那么在数轴上的三个点 $ i $，$ j $ 与 $ k $ 是美丽的一组点。$d$ 是“定义三元组是否美丽的参数”。

在一个初始为空的数轴上给出一些点，你需要：

- 增加一个点
- 移除一个点
- 计算美丽的点的组数

## 题解
对于这种计数的题，尤其这种几元的问题，我们一般铆钉一个数值维护信息，这里我们铆钉左端点，找右面的点。

令 $x$ 为最左端的点，然后 $cnt_x$ 表示 $[x+1,x+d]$ 中的点数，那么答案为：
$$
ans = \sum_{i = 1}^{n} \frac{cnt_i \times (cnt_i-1)} {2}
$$

如果增加一个点，那么区间 $[x-1,x-d]$ 全部加一，$cnt_x$ 加上 $[x+1,x+d]$ 中的点数。减少过程也一样。

当 $cnt$ 减一时 $ans$ 会减少 $cnt-1$，加一时，$ans$ 会增加 $cnt$。

所以线段树中，我们需要维护**区间中的点数**和 $cnt$ **的和**。

## 代码
```cpp
#define int long long
int q,d;
int flag;
struct node{
	int l,r;
	int cnt;
	int lazy;
	int sum;
}tr[N<<2];
void pushup(int rt){
	tr[rt].cnt = tr[rt<<1].cnt+tr[rt<<1|1].cnt;
	tr[rt].sum =tr[rt<<1].sum+tr[rt<<1|1].sum;
}
void build(int rt,int l,int r){
	tr[rt].l = l;
	tr[rt].r = r;
	if(l == r){
		return;
	}
	int mid = l+r>>1;
	build(rt<<1,l,mid);
	build(rt<<1|1,mid+1,r);
}


void pushdown(int rt){
	int l = tr[rt].lazy;
	if(l){
		tr[rt<<1].sum+=tr[rt<<1].cnt*l;
		tr[rt<<1|1].sum+=tr[rt<<1|1].cnt*l;
		tr[rt<<1].lazy+=l;
		tr[rt<<1|1].lazy+=l;
		tr[rt].lazy = 0;
	}
}

void update1(int rt,int l,int r,int k){
	if(l<=tr[rt].l && r>=tr[rt].r){
		tr[rt].sum+=k*tr[rt].cnt;
		tr[rt].lazy+=k;
		return;
	}
	pushdown(rt);
	int mid = tr[rt].l+tr[rt].r>>1;
	if(l<=mid) update1(rt<<1,l,r,k);
	if(r>mid) update1(rt<<1|1,l,r,k);
	pushup(rt);
}

void update2(int rt,int x,int k){
	if(tr[rt].l == tr[rt].r){
		tr[rt].cnt+=k;
		return;
	}
	pushdown(rt);
	int mid = tr[rt].l+tr[rt].r>>1;
	if(x<=mid) update2(rt<<1,x,k);
	else update2(rt<<1|1,x,k);
	pushup(rt);
}


int query(int rt,int l,int r){
	if(l<=tr[rt].l && r>=tr[rt].r){
		return tr[rt].cnt;
	}
	int mid = tr[rt].l+tr[rt].r>>1;
	int ans = 0;
	if(l<=mid) ans+=query(rt<<1,l,r);
	if(r>mid) ans+=query(rt<<1|1,l,r);
	return ans; 
}


int get_cnt(int rt,int l,int r){
	if(l<=tr[rt].l && r>=tr[rt].r){
		return tr[rt].cnt;
	}
	pushdown(rt);
	int mid = tr[rt].l+tr[rt].r>>1;
	int ans = 0;
	if(l<=mid) ans+=get_cnt(rt<<1,l,r);
	if(r>mid) ans+=get_cnt(rt<<1|1,l,r);
	return ans;
}

int get_sum(int rt,int l,int r){
	if(l<=tr[rt].l && r>=tr[rt].r){
		return tr[rt].sum;
	}
	pushdown(rt);
	int mid = tr[rt].l+tr[rt].r>>1;
	int ans = 0;
	if(l<=mid) ans+=get_sum(rt<<1,l,r);
	if(r>mid) ans+=get_sum(rt<<1|1,l,r);
	return ans;
}

//  铆钉一个基准 
ll ans;
int vis[N]; 
signed main(){
	read(q,d);
	build(1,0,200005);
	while(q--){
		int a;
		read(a);
		
		if(vis[a]){
			vis[a] = 0;
			int l = max((ll)0,a-d);
			int r = max((ll)0,a-1);
			int cnt = get_sum(1,a,a);
			ans-=cnt*(cnt-1)/2;
			ans-=get_sum(1,l,r);
			ans+=get_cnt(1,l,r); 
//			ans-=get_cnt(1,a+1,min(a+d,200003));
			update1(1,a,a,-cnt);
			update2(1,a,-1);
			update1(1,l,r,-1); 
			
		}else{
			vis[a] = 1;
			int l = max((ll)0,a-d);
			int r = max((ll)0,a-1);
			int cnt = get_cnt(1,a+1,min(a+d,(ll)200003));
			ans+=cnt*(cnt-1)/2;
			ans+=get_sum(1,l,r);
			update1(1,l,r,1);
			update2(1,a,1);
			update1(1,a,a,cnt);
		}
		write(ans);
		LF;
		
		
	}

	return 0;
}

```

---

## 作者：Leeb (赞：0)

### 题意简述

定义“美丽三元组”为 $(i,j,k)$ 满足：$i<j<k$ 且 $k-i\leq d$。

给定 $d$，动态维护一个点集，支持单点添加和删除操作，在每次操作后输出全集中“美丽三元组”的数量。

### 解题思路

设 $f_i$ 表示点 $i$ 存在的情况下，$[i+1,i+d]$ 中有多少个点。那么答案就是 $\sum C_{f_i}^2=\frac{f_i(f_i-1)}{2}$。

考虑添加一个点 $i$ 会产生什么影响：

- 答案要加上 $f_i(f_i-1)/2$（$f_i$ 是修改前的值）。
- $[i-d,i-1]$ 当中的每个点 $j$ 的 $f$ 值 $+1$，答案增加 $\frac{f_j(f_j+1)}{2}-\frac{f_j(f_j-1)}{2}=f_j$。
- 所以答案要增加一个 $f_i$ （修改前的）的区间和。

删除点同理，但是要注意操作顺序：
- $f_i$ 是修改前的。
- 答案变化 $\frac{(f_j-1)(f_j-2)}{2}-\frac{f_j(f_j-1)}{2}=-(f_j-1)$，所以是修改后的值。
写一个支持区间修改、区间查询的线段树即可。**注意**，还要维护每个点是否存在。

### 参考代码

```cpp
// -- More and More vegetales, what should I do?
// -- AFO! AFO YYDS!
// Code Author : Leeb
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 200005
#define inf 0x3f3f3f3f
#define endl '\n'
#define elif else if
#define int long long 
// #define ll long long
#define ub upper_bound
#define lb lower_bound
#define ls (x << 1)
#define rs (x << 1 | 1)
#define mem(a, x) memset(a, x, sizeof(a))
using namespace std;
int q, d, ans, val[N << 2], cnt[N << 2], lay[N << 2];
inline int in() {
    int a = 0; bool f = 0; char ch = getchar();
    while (ch < '0' || ch > '9')
        {if (ch == '-') f = 1; ch = getchar();}
    while (ch >= '0' && ch <= '9')
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f) return ~a + 1;   
    return a;
}
inline void print(int x) {
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
inline void out(int x, char ch) {
    print(x);
    putchar(ch);
}
inline void init() {return ;}
inline void push_up(int x) {
    val[x] = val[ls] + val[rs];
    cnt[x] = cnt[ls] + cnt[rs];
}
inline void push_down(int x) {
    if (lay[x]) {
        val[ls] += lay[x] * cnt[ls], lay[ls] += lay[x];
        val[rs] += lay[x] * cnt[rs], lay[rs] += lay[x];
        lay[x] = 0;
    }   
}
inline void update(int x, int l, int r, int p, int v, int w) {
    if (l == r) {
        cnt[x] = v;
        val[x] = w;
        return ;
    }
    push_down(x);
    int mid = l + r >> 1;
    if (p <= mid) update(ls, l, mid, p, v, w);
    else update(rs, mid + 1, r, p, v, w);
    push_up(x);
}
inline void add(int x, int l, int r, int L, int R, int d) {
    if (L <= l && r <= R) {
        val[x] += d * cnt[x];
        lay[x] += d;
        return ;
    }   
    push_down(x);
    int mid = l + r >> 1;
    if (L <= mid) add(ls, l, mid, L, R, d);
    if (R > mid) add(rs, mid + 1, r, L, R, d);
    push_up(x);
}
inline int query(int x, int l, int r, int L, int R, int *arr) {
    if (L <= l && r <= R) return arr[x];
    if (R < l || L > r) return 0;
    push_down(x);
    int ans = 0;
    int mid = l + r >> 1;
    if (L <= mid) ans += query(ls, l, mid, L, R, arr);
    if (R > mid) ans += query(rs, mid + 1, r, L, R, arr);
    return ans;
}
inline int max(int a, int b) {
    return a > b ? a : b;
}
inline int min(int a, int b) {
    return a < b ? a : b;
}
inline void work() {
    q = in(), d = in(); ans = 0;
    int n = 2e5;
    while (q--) {
        int x = in();
        if (query(1, 1, n, x, x, cnt)) {
            int tp = query(1, 1, n, min(n, x + 1), min(n, x + d), cnt);
            add(1, 1, n, max(1, x - d), max(1, x - 1), -1);
            update(1, 1, n, x, 0, 0);
            ans -= tp * (tp - 1) / 2 + query(1, 1, n, max(1, x - d), max(1, x - 1), val);
        }
        else {
            int tp = query(1, 1, n, min(n, x + 1), min(n, x + d), cnt);
            ans += tp * (tp - 1) / 2 + query(1, 1, n, max(1, x - d), max(1, x - 1), val);
            add(1, 1, n, max(1, x - d), max(1, x - 1), 1);
            update(1, 1, n, x, 1, tp);
        }
        out(ans, '\n');
    }
}
signed main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    int t = 1;
    while (t--) {
        init();
        work();
    }
    return 0;
}
```

---

