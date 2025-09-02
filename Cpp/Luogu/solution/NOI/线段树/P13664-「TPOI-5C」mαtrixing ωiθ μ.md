# 「TPOI-5C」mαtrixing ωiθ μ

## 题目背景

**本题禁止卡评测。**

![](https://cdn.luogu.com.cn/upload/image_hosting/qphit8fj.png?x-oss-process=image/resize,m_lfit,h_2170,w_2225)

## 题目描述

在东京的大雨后，天野阳菜给了 kele7 一个 $n$ 行 $m$ 列的矩阵 $A$。从上往下第 $i$ 行，从左往右第 $j$ 列的元素被称为 $A_{i,j}$。

kele7 喜欢删除矩阵。对于一个 $r$ 行 $c$ 列的矩阵 $B$，他会对它执行两种操作，同时会用**优雅值**衡量一个操作的优雅程度：

- 删除矩阵的某一行 $B_{i,1},\dots,B_{i,c}$，优雅值为 $\text{mex}_{j=1}^cB_{i,j}$。然后将第 $i+1\sim r$ 行往上平移一行，令 $r\leftarrow r-1$。
- 删除矩阵的某一列 $B_{1,i},\dots,B_{r,i}$，优雅值为 $\text{mex}_{j=1}^rB_{j,i}$。然后将第 $i+1\sim c$ 列往左平移一列，令 $c\leftarrow c-1$。

最终 kele7 要将矩阵内的元素全部删除（即 $r$ 或 $c$ 变为 $0$）。定义一种删除方案 $S$ 的权值 $f(S)$ 为其中所有操作的优雅值的**最小值**。定义矩阵 $B$ 的权值 $F(B)$ 为所有删除它的方案 $S$ 中 $f(S)$ 的**最大值**。

kele7 把这个题目给了 lzyqwq。lzyqwq 觉得还可以加上 $q$ 次查询，每次给出 $x_1,y_1,x_2,y_2$，你需要回答当矩阵 $B$ 为矩阵 $A$ 以 $A_{x_1,y_1}$ 为左上角元素、$A_{x_2,y_2}$ 为右下角元素的子矩阵时，$F(B)$ 的值。

一个集合 $M$ 的 $\operatorname{mex}(M)$ 定义为最小的没有在 $M$ 中出现的自然数。如 $\text{mex}\{1,2,3,4\}=0,\text{mex}\{0,1,3,4\}=2$。

## 说明/提示

**【样例解释】**

以第一个询问为例。初始矩阵 $B$ 为：

$$\begin{bmatrix}0&1&0&1&2\\3&2&0&1&4\\5&4&3&0&1\\0&2&0&3&1\\0&0&0&1&2\end{bmatrix}$$

一种可行的删除方案如下。

先删除第二行，优雅值为 $5$，得到新的矩阵 $B$ 为：

$$\begin{bmatrix}0&1&0&1&2\\5&4&3&0&1\\0&2&0&3&1\\0&0&0&1&2\end{bmatrix}$$

再删除第二列，优雅值为 $3$，得到新的矩阵 $B$ 为：

$$\begin{bmatrix}0&0&1&2\\5&3&0&1\\0&0&3&1\\0&0&1&2\end{bmatrix}$$

再依次删除所有行，优雅值分别为 $3,2,2,3$。

因此这种删除方案的权值为 $2$。可以证明，不存在优雅值的最小值更大的删除方案，因此答案为 $2$。

**【数据范围】**

|$\text{Subtask}$|$n,m$     |$q$       |特殊性质      |分值  |
|:--------:|:--------:|:--------:|:--------:|:--:|
|$0$       |$n\times m\le3\times10^5$|$q=1$     |无         |$11$|
|$1$       |$\color{red}{n,m\le300}$|$q\le10^5$|^         |^   |
|$2$       |$n\times m\le10^5$|^         |^         |$20$|
|$3$       |$n\times m\le2\times10^5$|$q\le2\times10^5$|^         |$24$|
|$4$       |$n\times m\le3\times10^5$|$q\le3\times10^5$|$x_1=y_1=1$|$8$ |
|$5$       |^         |^         |无         |$26$|

对于 $100\%$ 的数据，满足 $1\le n\times m,q\le 3\times 10^5$，$0\le A_{i,j}\le 10^9$。

## 样例 #1

### 输入

```
5 5 5
0 1 0 1 2
3 2 0 1 4
5 4 3 0 1
0 2 0 3 1
0 0 0 1 2
1 1 5 5
2 2 4 4
1 2 4 5
3 2 4 4
1 2 2 3```

### 输出

```
2
1
2
1
1
```

# 题解

## 作者：寄风 (赞：7)

首先你要注意到一直删行或列是一定不劣的。大概意思是，如果你在删除行的过程中混杂了一些删除列，那么之后删除的行的 $\operatorname{mex}$ 一定是不增的。删除列的过程中混杂了一些删除行的话同理。

那么问题转化为询问一个子矩阵所有行的 $\operatorname{mex}$ 的 $\min$ 和所有列的 $\operatorname{mex}$ 的 $\min$ 的 $\max$。

考虑把行列分开做，因为这两个本质上是一样的，所以你只需要解决一个，下面解决询问一个子矩阵所有行的 $\operatorname{mex}$ 的 $\min$。

考虑整体二分，设当前答案在 $[l,r]$ 之间，二分中点为 $mid$，则我们需要判断 $[1,mid]$ 中的数是否都在子矩阵的所有行中出现过。

对子矩阵的左方向的边（也就是 $y_1$）从大到小扫描线，令当前扫到了第 $u$ 列，对每一行 $x$ 维护一个 $w_x$，表示第 $x$ 行最小的列数 $v$ 使得 $[u,v]$ 中出现了 $[1,mid]$ 中的所有数。

考虑如何维护 $w$，考虑加入一个在第 $r$ 行，第 $c$ 列，值为 $val$ 的点，那么我们需要快速更新 $w_r$。考虑对于每一行数维护一个 set，维护这一行中所有在 $[1,mid]$ 中的数字的 $\ge u$ 的最小出现位置，同时对于每一行，对于所有在 $[1,mid]$ 中的数字，维护一个它 $\ge u$ 的最小出现位置。实现上，你可以把行数和值当成二元组哈希，开 unordered_map 维护即可。那么加入一个点就很好处理了，删掉这个点上一次的最小出现位置并且加入这个点的位置，因为你是对子矩阵的左方向的边（也就是 $y_1$）从大到小扫描的，所以这是对的。然后你更新了这一行的 set 之后，就可以重算 $w_x$ 了，在 set 中拿出最大值就是最新的 $w_x$ 了，这显然是对的。

那么考虑如何 check，你发现你要快速知道 $w_x$ 的最大值，再加上前面要支持快速单点更新 $w_x$，线段树维护 $w$ 即可。

但是这样子你发现你每次 check 的复杂度是 $O(mid)$ 的，复杂度是错的。

回归整体二分的本质，我们当前整体二分的当前答案在 $[l,r]$ 之间，那么 $[1,l-1]$ 之间的数一定在当前这些子矩阵的每一行都出现过。

那么你把上面的 $[1,mid]$ 改成 $[l,mid]$，这样每次 check 的复杂度就是 $O(mid-l)$ 的，那么根据整体二分的复杂度分析复杂度就是对的了。

视 $n\times m$ 与 $q$ 同阶，则总时间复杂度为 $O(q\log^2 q)$。

代码核心部分（其中 $d$ 为单点修改区间求 $\max$ 的线段树，请读者自行实现）：
```cpp
struct nd {
    int r, c, v;
};
struct qry {
    int x1, y1, x2, y2, id;
};

struct node {
    struct st {
        int ct = 0;
        std::multiset<int> S;
    };

    int R, C, up;
    std::vector<nd> pt;
    std::vector<qry> qs;
    std::vector<int> ans, res;
    SGT d;

    inline void solve(int l, int r, const std::vector<int> &nq, const std::vector<int> &np) {
        if (nq.empty()) {
            return;
        }

        if (l == r) {
            for (auto id : nq) {
                ans[qs[id].id] = l;
            }
            return;
        }

        int mid = (l + r) >> 1;

        std::vector<int> lp, rp;
        for (int id : np) {
            if (pt[id].v <= mid) {
                lp.push_back(id);
            } else {
                rp.push_back(id);
            }
        }

        std::vector<int> lq, rq, tp1 = lp, tp2 = nq;

        std::sort(tp1.begin(), tp1.end(), [&](int a, int b) {
            return pt[a].c > pt[b].c;
        });
        std::sort(tp2.begin(), tp2.end(), [&](int a, int b) {
            return qs[a].y1 > qs[b].y1;
        });

        
        std::unordered_map<int, st> mp1;

        std::unordered_map<u64, int> mp2;

        auto hsh = [](int r, int v) -> u64 {
            return (u64)r << 21 | v;
        };

        std::vector<int> tp;
        std::vector<char> vis(R + 1, 0);

        int pos = 0;
        for (auto v : tp2) {
            while (pos < (int)tp1.size() && pt[tp1[pos]].c >= qs[v].y1) {
                auto &p = pt[tp1[pos++]];

                int id = p.v - l;
                if (id < 0 || id >= mid - l + 1) {
                    continue;
                }

                u64 k = hsh(p.r, id);
                int lst = -1;
                
                if (mp2.count(k)) {
                    lst = mp2[k];
                }

                if (lst == -1 || p.c < lst) {
                    auto &nw = mp1[p.r];
                    if (lst != -1) {
                        nw.S.erase(nw.S.find(lst));
                    } else {
                        nw.ct++;
                    }

                    nw.S.insert(p.c);
                    mp2[k] = p.c;

                    int v = (nw.ct == mid - l + 1) ? (*nw.S.rbegin()) : inf;

                    if (res[p.r] ^ v) {
                        if (!vis[p.r]) {
                            vis[p.r] = 1;
                            tp.push_back(p.r);
                        }
                        res[p.r] = v;
                        d.upd(p.r, v);
                    }
                }
            }

            int mx = d.qry(qs[v].x1, qs[v].x2);
            if (mx <= qs[v].y2) {
                rq.push_back(v);
            } else {
                lq.push_back(v);
            }
        }

        for (auto v : tp) {
            res[v] = inf;
            d.upd(v, inf);
        }

        solve(l, mid, lq, lp);
        solve(mid + 1, r, rq, rp);
    }

    inline void wk() {
        res.assign(R + 1, inf), ans.assign(qs.size() + 1, 0);
        d.resize(R + 1);

        std::vector<int> qid(qs.size()), pid(pt.size());
        std::iota(qid.begin(), qid.end(), 0), std::iota(pid.begin(), pid.end(), 0);

        solve(0, up, qid, pid);
    }
};

---

## 作者：lzyqwq (赞：5)

首先注意到按行删或者按列删一定不劣。考虑删除一个矩阵一定要 $n$ 次删除行或 $m$ 次删除列。以前者为例，如果中间穿插了一些删除列的操作，导致删除行时这一行变为原矩阵中对应行的子集，从而 $\text{mex}$ 不增。由于行列的情况可以通过旋转原矩阵等价，所以现在问题变成：

> 给出一个矩阵，每次询问一个子矩阵，求每一行 $\text{mex}$ 的最小值。

考虑整体二分，记当前二分的区间为 $[l,r]$，中点为 $M$。考虑检查答案能否 $\ge M+1$。由于我们已经保证了当前的询问的答案都在 $[l,r]$ 中，即这些询问子矩阵的每一行中都包含了 $[0,l-1]$ 这些数。因此判定一行的 $\text{mex}$ 是否 $\ge M+1$，只需要检查这一行是否出现了所有 $[l,M]$ 内的数。

记 $S=\{(i,j)|A_{i,j}\in [l,M]\}$。按照左边那一列 $y$ 从大到小扫描询问，同时加入所有 $S$ 中 $j\ge y$ 的点。对于每一行，维护 $p_x$ 表示最小的列编号 $u$ 使得 $A_{x,y},\dots,A_{x,u}$ 出现了 $[l,M]$ 内的所有数。此时需要维护这一行每个在 $[l,M]$ 内的数在 $y$ 之后出现的第一个位置（后继）。那么 $p_x$ 就是这些位置的最小值。用 `map` 维护每行每种数当前的后继，同时用 `set` 维护所有后继的最小值。加入一个点时，就是在 `map` 中更新后继，并在 `set` 中删除原来的后继，插入当前位置。

对于一个询问，我们要检查每一行的 $\text{mex}$ 是否 $\ge M+1$，等价于判断 $x_1,\dots, x_2$ 这些行的 $p_x$ 是否均 $\le y_2$。维护区间 $p_x$ 的最大值即可。此时还需要支持上一段中的单点修改，所以使用线段树维护。

最后将点和询问划分到对应的子区间递归求解即可。

认为 $nm$ 和 $q$ 同阶，时间复杂度 $\mathcal{O}\left(q\log^2 q\right)$。

---

## 作者：Watersphere (赞：4)

纪念在本题大力卡常翻盘。

首先转换题意，注意到一直进行一种操作一定不劣，则询问转换为对于矩阵内每行 mex 的最小值与每列 mex 最小值的最大值，下面只考虑每行 mex 最小值，另一种情况是相同的。

我们有两种做法：

第一种是对于每行，$O(m^2)$ 地枚举所有区间，将答案记在区间右端点，那么一个矩阵的 mex 最小值就变成第 $y_2$ 列上 $[x_l,x_r]$ 中的最小值了，ST 表预处理即可，复杂度 $O(nm^2\log n)$。

第二种是把询问暴力拆到每行上，此时对于每一行有 $O(q)$ 个询问，考虑扫描线从左到右，在权值线段树上第 $i$ 个位置记录 $i$ 最后一次出现的位置，因为 mex 是 $O(m)$ 级别的所以线段树只用开到 $m$，然后扫到一个询问的右端点在线段树上二分最小的 $i$ 使得 $i$ 最后出现的位置小于询问左端点就是答案，复杂度 $O(nq\log m)$。

考虑平衡复杂度，设 $N=nm$ 以及阈值 $B$，让 $m \le B$ 时使用算法一，$m > B$ 时使用算法二，复杂度即 $O(B^2\frac{N}{B}\log{\frac{N}{B}}+q\frac{N}{B}\log B)$。

取 $B=\sqrt N$，$N,q$ 同阶，总复杂度即 $O(N\sqrt N \log{\sqrt N})$。

实测 $B=800$ 很快，最慢点 1.6s 左右，常数小点能更快。

```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5,B=800;
int n,m,q,vis[N+5],xl[N+5],xr[N+5],yl[N+5],yr[N+5],ans1[N+5],ans2[N+5];
vector<int> ma[N+5],tmp[N+5],ret[N+5];
inline void flip(){
	for(int i=1;i<=n;i++){
	    tmp[i].resize(m+5);
		for(int j=1;j<=m;j++) tmp[i][j]=ma[i][j];
	}
	swap(n,m);
	for(int i=1;i<=n;i++){
		ma[i].resize(m+5);
		for(int j=1;j<=m;j++) ma[i][j]=tmp[j][i];
	}
	for(int i=1;i<=q;i++){
		swap(xl[i],yl[i]);
		swap(xr[i],yr[i]);
	}
	return;
}
vector<int> rec2[N+5];
struct SGT{
	int mn[5*N+5];
	inline void build(int pos,int lp,int rp){
		mn[pos]=0;
		if(lp==rp) return;
		int mid=(lp+rp)/2;
		build(pos*2,lp,mid),build(pos*2+1,mid+1,rp);
		return;
	}
	inline void pushup(int pos){mn[pos]=min(mn[pos*2],mn[pos*2+1]); return;}
	inline void update(int pos,int to,int lp,int rp,int val){
		if(rp<to||to<lp) return;
		if(lp==rp&&lp==to){mn[pos]=val; return;}
		int mid=(lp+rp)/2;
		update(pos*2,to,lp,mid,val),update(pos*2+1,to,mid+1,rp,val);
		pushup(pos); return;
	}
	inline int query(int pos,int lp,int rp,int lim){
		if(lp==rp) return lp;
		int mid=(lp+rp)/2;
		if(mn[pos*2]<lim) return query(pos*2,lp,mid,lim);
		else return query(pos*2+1,mid+1,rp,lim);
	}
}sgt;
inline void work1(){
	for(int i=1;i<=q;i++) ans1[i]=m;
	for(int o=1;o<=n;o++){
		for(int i=1;i<=q;i++) if(xl[i]<=o&&o<=xr[i]) rec2[yr[i]].push_back(i);
		sgt.build(1,0,m);
		for(int i=1;i<=m;i++){
			if(ma[o][i]<=m) sgt.update(1,ma[o][i],0,m,i);
			for(int j:rec2[i]) ans1[j]=min(ans1[j],sgt.query(1,0,m,yl[j]));
			rec2[i].clear();
		}
	}
	for(int i=1;i<=q;i++) ans2[i]=max(ans2[i],ans1[i]);
	return;
}
struct ST{
	int mn[20][N+5],lg[N+5];
	inline void build(int cod){
		for(int i=2;i<=n;i++) lg[i]=lg[i/2]+1;
		for(int i=1;i<=n;i++) mn[0][i]=ret[i][cod];
		for(int i=1;i<=lg[n];i++){
			for(int j=1;j<=n-(1<<i)+1;j++) mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<(i-1))]);
		}
		return;
	}
	inline int query(int l,int r){
		int len=lg[r-l+1];
		return min(mn[len][l],mn[len][r-(1<<len)+1]);
	}
}st;
vector<int> rec[B+5][B+5];
inline void work2(){
	for(int i=1;i<=q;i++) rec[yl[i]][yr[i]].push_back(i),ans1[i]=0;
	for(int i=1;i<=n;i++) ret[i].resize(m+5);
	for(int l=1;l<=m;l++){
		for(int i=1;i<=n;i++){
			int mx=0;
			for(int r=l;r<=m;r++){
				if(ma[i][r]<=m) vis[ma[i][r]]=1;
				while(vis[mx]) mx++;
				ret[i][r]=mx;
			}
			for(int j=0;j<=m;j++) vis[j]=0;
		}
		for(int r=l;r<=m;r++){
			st.build(r);
			for(int i:rec[l][r]) ans1[i]=st.query(xl[i],xr[i]);
			rec[l][r].clear();
		}
	}
	for(int i=1;i<=q;i++) ans2[i]=max(ans2[i],ans1[i]);
	return;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		ma[i].resize(m+5);
		for(int j=1;j<=m;j++) cin>>ma[i][j];
	}
	int jud=1;
	for(int i=1;i<=q;i++) cin>>xl[i]>>yl[i]>>xr[i]>>yr[i],jud&=(xl[i]==1&&yl[i]==1);
	if(m<=B) work2();
	else work1();
	flip();
	if(m<=B) work2();
	else work1();
	for(int i=1;i<=q;i++) cout<<ans2[i]<<"\n";
	return 0;
}

```

---

## 作者：sunkuangzheng (赞：3)

最优解一定只会全删行或者全删列，如果同时删行列那么去掉一种一定不劣。由于行列的情况可以通过旋转原矩阵等价，所以现在问题变成每次询问一个子矩阵，求每一行 $\text{mex}$ 的最小值。

不妨先来解决 $n=1$；区间 $\text{mex}$ 做法很多，但是需要找一个修改和查询形式都比较简洁、可以扩展的做法。

考虑对每个值 $j \in [0,m]$，考察其相邻两次出现的列 $c_1 < c_2$，则所有满足 $c_1 < y_1 \le y_2 < c_2$ 的询问答案都不会超过 $j$。

于是考虑从左到右扫描线，扫到位置 $j$ 时，对 $a_{j}$ 找到它的下一次出现 $a_{k}$，将区间 $(j,k)$ 对 $a_{j}$ 取 $\min$。在扫到 $y_1$ 时，$y_2$ 位置的值就是答案。

扩展到 $n\times m$ 的矩阵时，扫描每列时遍历所有行，对每行维护上述结构，到 $y_1$ 列时答案是 $y_2$ 列对应行区间的 $\min$。我们只需要完成 $\mathcal O(nm)$ 次行取 $\min$ 和 $\mathcal O(q)$ 次列求 $\min$，可以使用树套树完成。这里的树套树是 $n\times m$ 的，因此空间是线性。

时间复杂度 $\mathcal O((nm+q)\log^2 nm)$，空间复杂度 $\mathcal O(nm)$。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 07.06.2025 20:45:33
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,m,q;
struct seg{
    vector<int> t; int n;
    void init(int _n){n = _n,t.assign(4 * n + 1,1e9);}
    void upd(int s,int l,int r,int x,int v){
        t[s] = min(t[s],v); if(l == r) return;
        int mid = (l + r) / 2;
        x <= mid ? upd(s*2,l,mid,x,v) : upd(s*2+1,mid+1,r,x,v); 
    }int qry(int s,int l,int r,int ql,int qr){
        if(ql <= l && r <= qr) return t[s];
        int mid = (l + r) / 2,ans = 1e9;
        if(ql <= mid) ans = min(ans,qry(s*2,l,mid,ql,qr));
        if(qr > mid) ans = min(ans,qry(s*2+1,mid+1,r,ql,qr));
        return ans;
    }void upd(int x,int v){upd(1,1,n,x,v);}
    int qry(int l,int r){return qry(1,1,n,l,r);}
};
struct SEG{
    vector<seg> t;
    void init(int n,int m){
        t.resize(4 * m + 1);
        for(int i = 1;i <= 4 * m;i ++) t[i].init(n);
    }void upd(int s,int l,int r,int ql,int qr,int x,int v){
        if(ql <= l && r <= qr) return t[s].upd(x,v),void();
        int mid = (l + r) / 2;
        if(ql <= mid) upd(s*2,l,mid,ql,qr,x,v);
        if(qr > mid) upd(s*2+1,mid+1,r,ql,qr,x,v);
    }int qry(int s,int l,int r,int x,int ql,int qr){
        int as = t[s].qry(ql,qr),mid = (l + r) / 2;
        if(l == r) return as;
        return min(as,x <= mid ? qry(s*2,l,mid,x,ql,qr) : qry(s*2+1,mid+1,r,x,ql,qr));
    }
}t;
int ans[N],tid; vector<tuple<int,int,int,int,int>> qu;
vector<pair<int,int>> f[N]; vector<tuple<int,int,int,int>> uq[N];
void solve(int n,int m,vector<vector<int>> a){
    t.init(n,m);
    auto id = [&](int i,int j){return (i - 1) * m + j;};
    for(int i = 1;i <= n * m;i ++) f[i].clear();
    for(int i = 1;i <= m;i ++) uq[i].clear();
    // for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) cerr << a[i][j] << " \n"[j == m];
    for(auto [x1,y1,x2,y2,i] : qu) uq[y1].emplace_back(y2,x1,x2,i);
    for(int i = 1;i <= n;i ++){
        vector<vector<int>> pos(m + 1);
        for(int j = 0;j <= m;j ++) pos[j].push_back(0);
        for(int j = 1;j <= m;j ++) if(a[i][j] <= m) pos[a[i][j]].push_back(j);
        for(int j = 0;j <= m;j ++) pos[j].push_back(m + 1);
        for(int j = 0;j <= m;j ++){
            for(int k = 1;k < pos[j].size();k ++){
                int x = pos[j][k-1] + 1,y = pos[j][k] - 1;
                if(x <= y) f[id(i,x)].emplace_back(y,j);
            }
        }
    }for(int j = 1;j <= m;j ++){
        for(int i = 1;i <= n;i ++) 
            for(auto [r,v] : f[id(i,j)]) t.upd(1,1,m,j,r,i,v);
        for(auto [y,l,r,id] : uq[j]) ans[id] = max(ans[id],t.qry(1,1,m,y,l,r));
    }
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m >> q;
    vector<vector<int>> a(n + 1,vector<int>(m + 1));
    for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) cin >> a[i][j];
    qu.resize(q);
    for(auto &[x1,y1,x2,y2,i] : qu) cin >> x1 >> y1 >> x2 >> y2,i = ++tid;
    solve(n,m,a); swap(n,m);
    vector<vector<int>> b(n + 1,vector<int>(m + 1));
    for(int i = 1;i <= n;i ++) for(int j = 1;j <= m;j ++) b[i][j] = a[j][i];
    for(auto &[x1,y1,x2,y2,i] : qu) swap(x1,y1),swap(x2,y2);
    solve(n,m,b);
    for(int i = 1;i <= q;i ++) cout << ans[i] << "\n";
}
```

:::info[花絮]
- 赛时通过的 6 份代码中，只有 2 份复杂度是预期的 $\log^2$，另外 4 份有 2 份是根号有 2 份是根号 $\log$。
- 我自己编写的根号 $\log$ 算法是扫描 $n,m$ 较小的那一维。作为 data maker，我造了一些数据将它卡掉了，还造了一些卡以 $n\le2m,2n \le m$ 为分治界限的数据。赛时通过的根号 $\log$ 都是以 $m \le B$ 作为分治界限的，那么不难发现当 $B \ge 780$ 时就可以轻松通过（）
- 本题一些测试点的矩阵随机方式是值 $x \in [0,\max(n,m)+1]$ 的出现频率是 $\dfrac{1}{(x+1)^{1.2}}$，但是效果仍然比较一般（答案还是很小）。怎样随机可以造出更强的数据呢 :)
:::

---

## 作者：SDSXC (赞：2)

非常简单自然的做法，不知道这题凭啥有黑。

首先贪心一下，发现原题等价于求给定子矩形中每一行/列的 $\operatorname{mex}$ 的最小值，然后取两者的最大值。

我们回顾一下序列上区间 $\operatorname{mex}$ 的做法，对每个数 $v$ 的相邻两次出现 $(i,j)$，建一个点权为 $v$ 的点，然后查询 $[l,r]$ 相当于求所有 $i<l\leq r<j$ 的 $(i,j)$ 的点权最小值，二维数点即可。

那么这一题的做法就呼之欲出了，我们对每个数 $v$ 在第 $x$ 行的相邻两次出现 $(i,j)$ 建一个点 $(x,i,j)$，点权为 $v$，查询相当于找 $x_1\leq x\leq x_2\wedge i<l\leq r<j$ 的 $(x,i,j)$ 的点权最小值。

这看似是一个四位偏序，但是只要把 $x$ 放到最后一维，然后把三位偏序的树状数组改线段树就行了。

复杂度，$O((nm+q)\log(nm)\log (nm+q))$。

代码，人傻常数大，仅供参考。

```cpp
#include<bits/stdc++.h>
#define N 300009
#define ls (rt<<1)
#define rs (rt<<1|1)
using namespace std;
int n,m,q,tot;
vector<int> c[N],d[N];
struct node{
	int x,y,l,r,id;
	bool operator<(const node &b){
		return x<b.x||(x==b.x&&y>b.y)||(x==b.x&&y==b.y&&l>b.l)||(x==b.x&&y==b.y&&l==b.l&&id<b.id);
	}
} a[N<<2],b[N<<2];
int ans[N],res[N];
int tr[N<<2],Q[N][4];
inline void up(int rt){
	tr[rt]=min(tr[ls],tr[rs]);
}
void upd(int rt,int l,int r,int x,int v,bool flag){
	if(l==r){
		if(flag)tr[rt]=v;
		else tr[rt]=min(tr[rt],v);
	}
	else{
		int mid=l+r>>1;
		if(x<=mid)upd(ls,l,mid,x,v,flag);
		else upd(rs,mid+1,r,x,v,flag);
		up(rt);
	}
}
int qry(int rt,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r)return tr[rt];
	else{
		int mid=l+r>>1;
		if(ql<=mid&&qr>mid)return min(qry(ls,l,mid,ql,qr),qry(rs,mid+1,r,ql,qr));
		else if(ql<=mid) return qry(ls,l,mid,ql,qr);
		else return qry(rs,mid+1,r,ql,qr);
	}
}
void cdq(int l,int r){
	if(l==r)return;
	int mid=l+r>>1;
	cdq(l,mid);cdq(mid+1,r);
	for(int i=l,j=l,k=mid+1;i<=r;i++){
		if(j<=mid&&(k>r||a[j].y>=a[k].y)){
			b[i]=a[j++];
			if(b[i].id<=0)upd(1,1,n,b[i].l,-b[i].id,0);
		}
		else{
			b[i]=a[k++];
			if(b[i].id>0)ans[b[i].id]=min(ans[b[i].id],qry(1,1,n,b[i].l,b[i].r));
		}
	}
	for(int i=l;i<=r;i++){
		a[i]=b[i];
		if(a[i].id<=0)upd(1,1,n,a[i].l,m,1);
	}
}
int lst[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=(n<<2);i++)tr[i]=m;
	for(int i=1;i<=n;i++){
		c[i].resize(m+1);
		for(int j=1;j<=m;j++)cin>>c[i][j];
		for(int j=1;j<=m;j++){
			if(c[i][j]>=m)continue;
			a[++tot]=node{lst[c[i][j]]+1,j-1,i,i,-c[i][j]};
			lst[c[i][j]]=j;
		}
		for(int j=0;j<m;j++){
			a[++tot]=node{lst[j]+1,m,i,i,-j};
			lst[j]=0;
		}
	}
	for(int i=1;i<=q;i++){
		cin>>Q[i][0]>>Q[i][1]>>Q[i][2]>>Q[i][3];
		a[++tot]=node{Q[i][1],Q[i][3],Q[i][0],Q[i][2],i};
		ans[i]=m;
	}
	sort(a+1,a+tot+1);
	cdq(1,tot);
	swap(ans,res);swap(n,m);tot=0;
	for(int i=1;i<=(n<<2);i++)tr[i]=m;
	for(int i=1;i<=n;i++){
		d[i].resize(m+1);
		for(int j=1;j<=m;j++)d[i][j]=c[j][i];
		for(int j=1;j<=m;j++){
			if(d[i][j]>=m)continue;
			a[++tot]=node{lst[d[i][j]]+1,j-1,i,i,-d[i][j]};
			lst[d[i][j]]=j;
		}
		for(int j=0;j<m;j++){
			a[++tot]=node{lst[j]+1,m,i,i,-j};
			lst[j]=0;
		}
	}
	for(int i=1;i<=q;i++){
		a[++tot]=node{Q[i][0],Q[i][2],Q[i][1],Q[i][3],i};
		ans[i]=m;
	}
	sort(a+1,a+tot+1);cdq(1,tot);
	for(int i=1;i<=q;i++)cout<<max(ans[i],res[i])<<"\n";
	return 0;
}
```

---

## 作者：CCCCOrz (赞：2)

赛时写出来的莫名其妙线性空间树套树做法。

~~花了几乎3个小时调试这个题导致T2的重剖的60分没时间写~~

## 分析

先来证明一个小结论，“矩阵 $B$ 的权值 $F(B) \ge k $ ”当且仅当“$[0,k-1]$里的所有整数都在 $B$ 的每一行里出现过或都在 $B$ 的每一列里出现过”

后推前是简单的，直接删每一行或每一列即可。

前推后不是很显然（也可能是我太菜），相当于要求通过“只删除 $\mathrm{mex} \ge k$ 的行或列”来删空矩阵。首先删除过程不会让某行某列的 $\mathrm{mex}$ 变大，因此注意到如果同时有某一行和某一列的 $\mathrm{mex}$ 都不到 $k$ ，那么它们的交点就无法被删去。

因此题目变成了求询问矩阵的“每行 $\mathrm{mex}$ 最小值”和“每列 $\mathrm{mex}$ 最小值”的较大值。

## 实现

以下是“每列 $\mathrm{mex}$ 最小值”的维护，行的维护同理。

回忆一下 [P4137](https://www.luogu.com.cn/problem/P4137) 的线段树做法，求一维序列上一个后缀 $[l,n]$ 的 $mex$ 可以相当于求“在序列中最后一次出现的位置在 $l-1$ 及以前”的最小数（没出现过视作最后一次出现在$0$位置，即整个序列之前）。

同理，本题询问（记作第$l$到$r$列，第$u$到$d$行）离线后按下边界排序，从上到下依次将原矩阵每行的值扔进某个数据结构维护，到达某个询问的下边界就直接查出答案来存下，这个查询可以表示为求满足某个条件的最小数，这个条件是“在第 $l$ 到 $r$ 列的某一列中，这个数最后一次出现是在第 $u-1$ 行及以前”。

相当于这里是处理 $r-l+1$ 个 P4137。

肯定不能直接枚举每一列分别查。考虑到查询一个序列就已经需要 $\Theta(\log )$ 的时间，我们希望能够只查询 $O(\log )$ 个序列。或者说将一些列捆绑起来维护，把第 $l$ 到 $r$ 列分解为 $O(\log )$ 个维护好的列来考虑。这显然又是个线段树。

于是做法很自然就出来了，用线段树套权值线段树来维护，外层线段树叶节点处的权值线段树维护的就是这一列里每个数最后出现的位置。非叶节点处的权值线段树维护的就是这些列里的“最后出现的位置”的最小值。

实现上有个细节，外层线段树叶节点和非叶节点的修改是不同的，叶节点需要直接进入权值线段树修改，非叶节点则需要外层线段树子节点处对应的权值线段树维护的值取 $\min$。

最后是空间，列的 $\mathrm{mex}$ 显然不会超过行数 $n$，故超过 $n$ 的值当作 $n$ 即可，因此值域为 $[0,n]$ ，共 $n+1$ 个数，内层权值线段树每一个所用空间不超过$2(n+1)$，而外层线段树用了 $2m$ 个结点，所以空间是线性的。

时间复杂度 $O((nm+q)\log n\log m)$，空间 $O(nm+q)$

代码：
```cpp
#include <cstdio>
#include <algorithm>
inline int rd(){
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+(c^48),c=getchar();
	return x;
}
const int SZ=300010;
int n,m,q,lm;
inline int mmin(const int x,const int y){return x<y?x:y;}
inline int mmax(const int x,const int y){return x>y?x:y;}
struct mtr{
	int v[SZ];
	inline int *const operator [](const int x){return v+(x-1)*m;}
	inline const int *const operator [](const int x)const{return v+(x-1)*m;}
}a;
const int node_cnt=SZ*5;
int ls[node_cnt],rs[node_cnt],mn[node_cnt];
int rt[SZ<<2],tot;
inline int nw(){return ++tot,ls[tot]=rs[tot]=mn[tot]=0,tot;}
inline void refresh(const int p){mn[p]=mmin(mn[ls[p]],mn[rs[p]]);}
void in_chg(const int l,const int r,const int p,const int w,const int v){
	if(l==r){mn[p]=v;return;}
	const int mid=l+r>>1;
	if(w<=mid){
		if(!ls[p])ls[p]=nw();
		in_chg(l,mid,ls[p],w,v);
	}
	else{
		if(!rs[p])rs[p]=nw();
		in_chg(mid+1,r,rs[p],w,v);
	}
	refresh(p);
}
void refresh_out(const int l,const int r,const int p,const int lp,const int rp,const int w){
	mn[p]=mmin(mn[lp],mn[rp]);
	if(l==r)return;
	const int mid=l+r>>1;
	if(w<=mid){
		if(!ls[p])ls[p]=nw();
		refresh_out(l,mid,ls[p],ls[lp],ls[rp],w);
	}
	else{
		if(!rs[p])rs[p]=nw();
		refresh_out(mid+1,r,rs[p],rs[lp],rs[rp],w);
	}
}
void chg(const int l,const int r,const int p,const int w,const int v,const int ocr){
	if(!rt[p])rt[p]=nw();
	if(l==r)return in_chg(0,lm,rt[p],v,ocr);
	const int mid=l+r>>1;
	if(w<=mid)chg(l,mid,p<<1,w,v,ocr);
	else chg(mid+1,r,p<<1|1,w,v,ocr);
	refresh_out(0,lm,rt[p],rt[p<<1],rt[p<<1|1],v);
}
int pts[40],ptot;
void drag(const int l,const int r,const int p,const int b,const int e){
	if(b<=l && e>=r){pts[++ptot]=rt[p];return;}
	const int mid=l+r>>1;
	if(b<=mid)drag(l,mid,p<<1,b,e);
	if(e>mid)drag(mid+1,r,p<<1|1,b,e);
}
inline int qus(const int b,const int e,const int v,const int nlm){
	ptot=0,drag(1,nlm,1,b,e);
	int l=0,r=lm,mid;
	while(l<r){
		int mns=lm;
		for(int i=1;i<=ptot;++i)
			mns=mmin(mns,mn[ls[pts[i]]]);
		mid=l+r>>1;
		if(mns<v){
			for(int i=1;i<=ptot;++i)
				pts[i]=ls[pts[i]];
			r=mid;
		}
		else{
			for(int i=1;i<=ptot;++i)
				pts[i]=rs[pts[i]];
			l=mid+1;
		}
	}
	return l;
}
int l[SZ],r[SZ],u[SZ],d[SZ],p[SZ],ans[SZ];
inline bool cmp1(const int x,const int y){return d[x]<d[y];}
inline bool cmp2(const int x,const int y){return r[x]<r[y];}
int main(){
	n=rd(),m=rd(),q=rd();
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			a[i][j]=rd();
	for(int i=1;i<=q;++i)
		u[i]=rd(),l[i]=rd(),d[i]=rd(),r[i]=rd(),p[i]=i;
	std::sort(p+1,p+q+1,cmp1),lm=n;
	for(int i=1,at=1;i<=n;++i){
		for(int j=1;j<=m;++j)
			chg(1,m,1,j,mmin(a[i][j],lm),i);
		while(at<=q && d[p[at]]==i){
			const int atq=p[at];
			ans[atq]=qus(l[atq],r[atq],u[atq],m),++at;
		}
	}
	tot=0;
	for(int i=mmin(n,m)<<2;i;--i)rt[i]=0;
	std::sort(p+1,p+q+1,cmp2),lm=m;
	for(int j=1,at=1;j<=m;++j){
		for(int i=1;i<=n;++i)
			chg(1,n,1,i,mmin(a[i][j],lm),j);
		while(at<=q && r[p[at]]==j){
			const int atq=p[at];
			ans[atq]=mmax(ans[atq],qus(u[atq],d[atq],l[atq],n)),++at;
		}
	}
	for(int i=1;i<=q;++i)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：CheeseFunction (赞：0)

### 问题重述：

有一个 $n \times m$ 的矩阵，矩阵中的元素是自然数，需要处理 $q$ 次询问，每次给出一个矩阵，其左上角为 $A_{x_1,y_1}$ 和右下角 $A_{x_2 , y_2}$， 对于每一个子矩阵，需要通过删除行和列来清空矩阵，其每次操作都有优雅值：

- 删除第 $i$ 行，优雅值为当前行所有元素的 $\text{mex}$ 值。
- 删除第 $j$ 列，优雅值为当前列所有元素的 $\text{mex}$ 值。$\text{mex}$ 表示最小的没有在该集合中出现过的元素。现在求子矩阵的最大值。

### 思路：

这个问题看似复杂，但是问题一眼二分，而且有一些特殊性质：

- 首先，mex 具有以下性质满足：一个集合的 mex 值为 $k$，意味着该集合包含 $0$ 到 $k-1$ 的所有数，但不包含 $k$。
- 然后我们定义 $f(S)$ 表示所有操作中的删除方案中的最小值，$F(S)$ 表示所有删除方案最大值，那么等价于矩阵中所有行和列的 mex 值都不小于 $k$。因为如果某行 / 列的 mex 值小于 $k$，那么删除该行 / 列时的优雅值就会小于 $k$。

基于上述的性质，二分的思路是显而易见的，因此：

- 对于每一个查询，我们查找最大的 $k$ 让矩阵满足条件。
- 然后，对于行的方向，检查每一行的最小值是否 $\geq k$， 对于列方向同理。
- 接下来，我们用线段树维护区间最小值，CDQ 分治来维护这个平面。让后题目就做完了。

### Code:

这么好玩的题目当然应该自己写代码，没错吧？

---

