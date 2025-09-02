# [ARC177D] Earthquakes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc177/tasks/arc177_d

AtCoder 街道は、平らな地面の上に伸びる数直線で表される道路です。この道路上に $ N $ 個の高さ $ H $ の電柱が立っています。電柱には $ 1,\ 2,\ \dots,\ N $ の番号が古い順に付けられています。電柱 $ i\ (1\ \leq\ i\ \leq\ N) $ は座標 $ X_i $ に地面と垂直に立っています。**電柱の最下部は地面に固定されています。**ここで、電柱は十分に細いものとして考えます。

AtCoder 街道ではこれから $ N $ 回の地震が発生します。$ i $ 回目 $ (1\ \leq\ i\ \leq\ N) $ の地震では、以下のことが起こります。

1. 電柱 $ i $ がまだ倒れていない場合、それが数直線における左または右の方向に、それぞれ $ \frac{1}{2} $ ずつの確率で倒れる。
2. 倒れようとしている電柱が、まだ倒れていない電柱に衝突した場合（電柱の最下部に衝突した場合を含む）、この電柱も同じ方向に倒れる。場合によってはこれが連鎖的に起こる。
 
ここで、1. で電柱がどちら方向に倒れるかは、他の電柱がどちら方向に倒れたかに関係しません。

以下の図は一回の地震での電柱の倒れ方の一例です。

![ ](https://cdn.luogu.com.cn/upload/vjudge_pic/AT_arc177_d/2bf5e733d9f95c4209b1b2a6093b423312351960.png)

地震対策のため、$ t\ =\ 1,\ 2,\ \dots,\ N $ それぞれについて、ちょうど $ t $ 回目の地震ですべての電柱が倒れた状態になる確率を $ 2^N $ 倍した値を $ 998244353 $ で割った余りを求めてください。なお、出力すべき値は整数になることが証明できます。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ H\ \leq\ 10^9 $
- $ 0\ \leq\ X_i\ \leq\ 10^9\ (1\ \leq\ i\ \leq\ N) $
- $ X_1,\ X_2,\ \dots,\ X_N $ はすべて異なる
- 入力はすべて整数
 
### Sample Explanation 1

以下の図は、この入力例における電柱の倒れ方の可能性を示しています。図中の分数はその状態になる確率を示しています。 !\[ \](https://img.atcoder.jp/arc177/1b1ec413ff3069cd13b19efd64b9c9d2.png) したがって、ちょうど $ 1,\ 2,\ 3 $ 回目の地震ですべての電柱が倒れた状態になる確率は、それぞれ $ \frac{1}{2},\ \frac{1}{4},\ \frac{1}{4} $ です。これを $ 8 $ 倍した $ 4,\ 2,\ 2 $ を出力しましょう。

### Sample Explanation 2

以下の図は、この入力例における電柱の倒れ方の可能性を示しています。図中の分数はその状態になる確率を示しています。 !\[ \](https://img.atcoder.jp/arc177/f2ce4d20221071c814e204d8a2adc60d.png) したがって、ちょうど $ 1,\ 2,\ 3,\ 4 $ 回目の地震ですべての電柱が倒れた状態になる確率は、それぞれ $ 0,\ \frac{1}{4},\ \frac{1}{4},\ \frac{1}{2} $ です。これを $ 16 $ 倍した $ 0,\ 4,\ 4,\ 8 $ を出力しましょう。

### Sample Explanation 3

ちょうど $ 1,\ 2,\ 3,\ 4,\ 5,\ 6,\ 7,\ 8 $ 回目の地震ですべての電柱が倒れた状態になる確率は、それぞれ $ 0,\ \frac{1}{4},\ \frac{1}{8},\ \frac{3}{16},\ \frac{3}{32},\ \frac{7}{64},\ \frac{7}{64},\ \frac{1}{8} $ です。

### Sample Explanation 4

$ 37 $ 回目の地震までにすべての電柱が倒れることはありません。ちょうど $ 38,\ 39,\ 40 $ 回目の地震ですべての電柱が倒れた状態になる確率は、それぞれ $ \frac{3}{8},\ \frac{3}{8},\ \frac{1}{4} $ です。

## 样例 #1

### 输入

```
3 2
0 3 1```

### 输出

```
4 2 2```

## 样例 #2

### 输入

```
4 10
10 55 20 45```

### 输出

```
0 4 4 8```

## 样例 #3

### 输入

```
8 1
5 0 6 3 8 1 7 2```

### 输出

```
0 64 32 48 24 28 28 32```

## 样例 #4

### 输入

```
40 20
695 793 11 502 114 861 559 4 212 609 894 435 429 94 91 258 161 45 33 605 673 634 629 163 283 826 409 84 507 548 31 248 588 340 357 168 926 949 322 912```

### 输出

```
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 41942627 41942627 360709869```

# 题解

## 作者：ma_niu_bi (赞：9)

### D - Earthquakes

### 思路

#### 1.分析

我们发现，所有的电线杆可以被划分为若干段。

定义一段为左端点的电线杆向右倒能让整段电线杆全部倒完的极长子区间。

不同段之间不会有任何影响。因此，我们可以将原问题拆分为子问题：

有一段长度为 $l$ 位置升序的电线杆。

从左往右第 $i$ 个电线杆在第 $p_i$ 次地震中倒塌，求最后倒塌的电线杆是第 $i$ 个电线杆的概率。

#### 2.解决子问题

##### 2.1分析子问题

我们发现任何时刻，一段区间均可被分成三部分：

向左倒塌的一部分，站立的一部分，向右倒塌的一部分。

第 $i$ 个电线杆未倒塌，当且仅当：

所有 $p$ 中 $1$ 到 $i$ 的前缀最小值都向左倒塌；

所有 $p$ 中 $l$ 到 $i$ 的后缀最小值都向右倒塌。

这些代表了在 $i$ 之前主动倒塌的电线杆（不是被其他推倒的）。

第 $i$ 个电线杆是最后倒塌的，当且仅当 $i$ 未倒塌且 $i$ 是站立的一段的起点或终点。

##### 2.2分析概率

我们发现，第 $i$ 个电线杆是最后倒塌的概率为 $1/2^a\times b/2$。

其中 $a$ 为 $p$ 到 $i$ 的前缀最小值和后缀最小值的个数之和。

因为必须保持 $i$ 站立，所以左边的必须往左倒，右边的必须往右倒，概率为 $1/2^a$。

若 $i$ 为站立区间的左端点或右端点，$b=1$。

若 $i$ 是单独的一个（即既是左端点又是右端点），$b=2$。

若 $i$ 是左右端点中的一个，则 $i$ 倒下的方向有要求，概率为 $1/2$。

若 $i$ 同时是左右端点（单独），则 $i$ 倒下的方向没有要求，概率为 $1$。

##### 2.3求解概率

我们发现，概率中 $a$ 的求解过程为单调栈的板子，$b$ 的解决平凡。

至此，子问题已经解决，时间复杂度 $O(l)$。

#### 3.合并子问题

设一共有 $c$ 段，电线杆 $i$ 所在的段的编号为 $g_i$。

时间 $t$ 的答案为 $s_1\times s_2\times \ldots \times s_{g_t-1}\times x \times s_{g_t+1} \times \ldots \times s_c$。

其中 $x$ 为子问题 $g_t$ 中最后倒下的电线杆是 $t$ 的概率，

$s_i$ 为子问题 $i$ 中最后倒下的电线杆编号小于 $t$ 的概率之和。

直接朴素计算是 $O(n^2)$。

我们发现这是一个单点修改，区间查询问题，考虑使用线段树优化。

线段树中维护 $s$，每次将答案算出后，将 $x$ 加到 $s_{g_t}$ 中。

时间复杂度 $O(n\log n)$。

#### 实现细节

题目要求要将答案乘上 $2^N$，但我们解决子问题时不能乘 $2^N$，而要乘 $2^l$，这样所有子问题乘起来才是 $2^N$。

### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
const int mod = 998244353;
const int N = 2e5 + 5;
using namespace std;
struct segt {
    struct node {int l, r, v;} t[N << 2];
    #define ls (p << 1)
    #define rs (p << 1 | 1)
    void build(int p, int l, int r) {
        t[p].l = l, t[p].r = r, t[p].v = 0;
        if (l == r) return ;
        int mid = (l + r) >> 1;
        build(ls, l, mid);
        build(rs, mid + 1, r); 
    }
    void add(int p, int id, int v) {
        if (t[p].l == t[p].r) {
            t[p].v += v, t[p].v %= mod;
            return ;
        }
        if (id <= t[ls].r) add(ls, id, v);
        else add(rs, id, v);
        t[p].v = t[ls].v * t[rs].v, t[p].v %= mod;
    }
    int query(int p, int l, int r) {
        if (l <= t[p].l && t[p].r <= r) return t[p].v;
        int res = 1;
        if (t[ls].r >= l) res *= query(ls, l, r), res %= mod;
        if (t[rs].l <= r) res *= query(rs, l, r), res %= mod;
        return res;
    }
} T; // 线段树板子
struct Point {int x, y;};
bool cmp(Point a, Point b) {return a.x < b.x;}
int n, h, c, x[N], g[N], t[N], k[N], pow2[N];
Point a[N];
vector <int> p[N];
vector <int> res[N];
void solve(int id) { // 解决子问题
    int m = p[id].size() - 1;
    stack <int> stk; 
    for (int i = 1; i <= m; i ++) {
        while (!stk.empty() && // 单调栈板子
        p[id][i] < stk.top()) stk.pop();
        stk.push(p[id][i]);
        k[i] = stk.size() - 1;
    }
    stack <int> sstk;
    for (int i = m; i >= 1; i --) {
        while (!sstk.empty() && // 单调栈板子
        p[id][i] < sstk.top()) sstk.pop();
        sstk.push(p[id][i]);
        k[i] += sstk.size() - 1;
    }
    res[id].emplace_back(0);
    for (int i = 1; i <= m; i ++) { // 计算概率
        int b = (i == 1 || p[id][i - 1] < p[id][i]) // 左端点
                + (i == m || p[id][i] > p[id][i + 1]); // 右端点
        res[id].emplace_back(b * pow2[m - k[i] - 1] % mod); // 乘2^l
    }
}
signed main() {
    cin >> n >> h, pow2[0] = 1;
    for (int i = 1; i <= n; i ++) {
        cin >> x[i];
        a[i].x = x[i], a[i].y = i;
        pow2[i] = (pow2[i - 1] << 1) % mod;
    }
    for (int i = 1; i <= n; i ++) 
        p[i].emplace_back(0);
    sort(a + 1, a + n + 1, cmp);
    g[a[1].y] = ++ c, 
    p[c].emplace_back(a[1].y), 
    t[a[1].y] = p[c].size() - 1;
    for (int i = 2; i <= n; i ++) { // 分段
        if (a[i].x - a[i - 1].x <= h) 
            g[a[i].y] = c, 
            p[c].emplace_back(a[i].y), 
            t[a[i].y] = p[c].size() - 1;
        else g[a[i].y] = ++ c, 
            p[c].emplace_back(a[i].y), 
            t[a[i].y] = p[c].size() - 1; 
    }
    for (int i = 1; i <= c; i ++) solve(i); // 解决子问题
    T.build(1, 1, c);
    for (int i = 1; i <= n; i ++) { // 合并答案
        int x = res[g[i]][t[i]], ans = 1;
        if (g[i] - 1) 
            ans *= T.query(1, 1, g[i] - 1);
        if (g[i] + 1 <= c) 
            ans *= T.query(1, g[i] + 1, c), ans %= mod;
        ans *= x, ans %= mod;
        T.add(1, g[i], x);
        cout << ans << ' ';
    }
    return 0;
}
```

---

## 作者：破壁人罗辑 (赞：4)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/AT_arc177_d)/[AtCoder](https://atcoder.jp/contests/arc177/tasks/arc177_d)

## 题目大意

有一列 $N$ 个高度相同的电线杆，其中第 $i$ 个电线杆位于位置 $x_i$ 处。第 $i$ 次地震会导致第 $i$ 个电线杆向左或向右倒下。若一个电线杆倒下，则在其倒下方向的距离小于其高度的电线杆也会被推倒。求第 $i$ 次地震导致所有电线杆全部倒下的概率，$i=1,2,\cdots,N$。

## 解题思路

若存在多组电线杆，使得每两组电线杆之间的距离大于电线杆高度，则这几组电线杆是否倒下是独立事件。所以我们可以先分组处理，然后合并。

对于一组满足相邻电线杆距离都小于电线杆高度的电线杆，假设其中最先地震的是第 $i$ 号电线杆，则分三类讨论：

- 若这组电线杆的数量为 $1$，则仅需一次地震就可全部倒下，即在第 $i$ 次地震中本组所有地震杆会全部倒下，将 $(i,1)$ 压入时间-概率数组即可。

- 第 $i$ 号在这一组电线杆中的最左侧或最右侧，则在第 $i$ 次地震中有 $\frac12$ 的概率导致全部电线杆倒下，有 $\frac12$ 的概率仅导致此电线杆倒下。我们可以将时间 $i$ 以及当前情况的概率的 $\frac12$ 压入这组电线杆的时间-概率数组，然后将这一组的其它电线杆当作单独的一组，概率设为当前情况概率的 $\frac12$，递归求解。

- 第 $i$ 号在这一组电线杆的中间某个位置，则在第 $i$ 次地震中有 $\frac12$ 的概率导致左侧全部电线杆倒下，只要等到右侧全部电线杆倒下即可；有 $\frac12$ 的概率导致右侧全部电线杆倒下，只要等到左侧全部电线杆倒下即可。我们可以分别将第 $i$ 号电线杆的左侧和右侧所有电线杆当作单独的一组，概率都设为当前情况概率的 $\frac12$，递归求解。

接下来讨论合并步骤。我们将处理得到的概率组两两合并。若第一组在 $t_{1,i}$ 时有 $p_{1,i}$ 的概率全部倒下，第二组在 $t_{2,j}$ 时有 $p_{2,j}$ 的概率全部倒下，则两组合并后在 $t_{1,i}$ 时有 $p_{1,i}\cdot\sum_{t_{2,j}<t_{1,i}}p_{2,j}$ 的概率全部倒下，在 $t_{2,j}$ 时有 $p_{2,j}\cdot\sum_{t_{1,i}<t_{2,j}}p_{1,i}$ 的概率全部倒下。由此可知若合并前的两组的时间-概率数组大小分别为 $m_1,m_2$，则合并后的新的时间-概率数组大小一定小于等于 $m_1+m_2-1$。

时间复杂度分析如下：

- 输入电线杆并将其按位置排序的时间复杂度是 $O(N\log N)$；
- 用 ST 表存储和获取区间 $(l,r]$ 中最早遭受地震的电线杆编号，预处理的时间复杂度是 $O(N\log N)$；
- 递归求解各组倒下的时间-概率数组的时间复杂度的 $O(N)$；
- 合并时采用启发式合并，每次合并大小最小的两个时间-概率数组，并使用堆来对时间-概率数组大小进行排序，时间复杂度是 $O(N\log N)$；

综上所述，程序的总时间复杂度为 $O(N\log N)$

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MOD 998244353ll
int Read(){
	char c=getchar();while(c<'0'||c>'9')c=getchar();
	int r=0;while(c>='0'&&c<='9'){r=r*10+(c^48);c=getchar();}
	return r;
}
int mini[200001][19],lg2[200001],ss[200000];
pair<int,int>x[200001];
struct vGreater{
	bool operator()(int x,int y)const{return ss[x]>ss[y];}
};
vector<pair<int,int> >vi[200000];//时间,概率
int imini(int l,int r){//(l,r]
	int l2=lg2[r-l]-1;
	return x[mini[r][l2]].second<x[mini[l+(1<<l2)][l2]].second?mini[r][l2]:mini[l+(1<<l2)][l2];
}
void dfs(int l,int r,int n,int p){
	if(l==r)vi[n].push_back(make_pair(x[l].second,p));
	else if(l<r){
		int k=imini(l-1,r);p=p*499122177ll%MOD;
		if(k==l){
			vi[n].push_back(make_pair(x[l].second,p));
			dfs(l+1,r,n,p);
		}
		else if(r==k){
			vi[n].push_back(make_pair(x[r].second,p));
			dfs(l,r-1,n,p);
		}
		else{
			dfs(l,k-1,n,p);
			dfs(k+1,r,n,p);
		}
	}
}
int main(){
	int n=Read(),h=Read(),ansx=1;
	for(int i=1;i<=n;i++){
		ansx=(ansx<<1)%MOD;
		lg2[i]=lg2[i-1]+(i==1<<lg2[i-1]);
	}
	for(int i=1;i<=n;i++){
		x[i].first=Read();x[i].second=i;
	}
	sort(x+1,x+n+1);
	for(int i=1;i<=n;i++){
		mini[i][0]=i;
		for(int j=1;j<lg2[i];j++)
			mini[i][j]=(x[mini[i][j-1]].second<x[mini[i-(1<<(j-1))][j-1]].second)?mini[i][j-1]:mini[i-(1<<(j-1))][j-1];
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		int j=i;
		while(i<n&&x[i+1].first<=x[i].first+h)i++;
		dfs(j,i,cnt++,1);
	}
	priority_queue<int,vector<int>,vGreater>q;
	for(int i=0;i<cnt;i++){
		ss[i]=vi[i].size();
		sort(vi[i].begin(),vi[i].end());
		q.push(i);
	}
	while(--cnt){
		int i=q.top();q.pop();
		int j=q.top();q.pop();
		int toti=0,totj=0,l=0,r=0;
		vector<pair<int,int> >v;
		while(l<ss[i]&&r<ss[j]){
			if(vi[i][l].first<vi[j][r].first){
				if(totj)v.push_back(make_pair(vi[i][l].first,vi[i][l].second*(long long)totj%MOD));
				toti=(toti+vi[i][l++].second)%MOD;
			}
			else{
				if(toti)v.push_back(make_pair(vi[j][r].first,vi[j][r].second*(long long)toti%MOD));
				totj=(totj+vi[j][r++].second)%MOD;
			}
		}
		while(l<ss[i]){
			v.push_back(make_pair(vi[i][l].first,vi[i][l].second*(long long)totj%MOD));
			l++;
		}
		while(r<ss[j]){
			v.push_back(make_pair(vi[j][r].first,vi[j][r].second*(long long)toti%MOD));
			r++;
		}
		ss[i]=v.size();
		swap(vi[i],v);
		q.push(i);
	}
	int p=0,f=q.top();
	for(int i=1;i<=n;i++)
		printf("%d ",(p<ss[f]&&i==vi[f][p].first)?vi[f][p++].second*(long long)ansx%MOD:0);
	return 0;
}
```

---

## 作者：Lavaloon (赞：2)

可以看到目前题解区多采用手写线段树或其它数据结构来维护带修的若干数之积，这里介绍一种无需数据结构进行维护的方法，谨以此作为对其它题解的补充。

首先，目前题解区采用的计算答案的方式为直接进行计算，而更加便于维护的方法是：计算所有电线杆在某时刻**及其之前**倒塌的概率，而非**恰**在某时刻倒塌的概率。
于是，转化后需要维护的操作如下：

- 单点修改；

- **全局乘积**（规避了题解区常见的维护区间乘积的方式）。

我们最先想到的、解决这个问题的方法肯定是直接乘逆元消除原来那个数的贡献（目的是变为不包含那个位置的全局乘积），然后再把新数乘上去。但是这个做法有个问题，就是单点修改成 $0$ 之后再进行单点修改时，无法将之前的乘积变为不包含这个位置的全局乘积，即，**修改为 $0$ 具有不可逆性**。

那么为了避免这一点，自然想到维护 ban 掉所有**目前**值为 $0$ 的位置，**只维护所有非 $0$ 位置的乘积**（不妨记为 $mul$）。

下面说明这个做法是可行的：

- 支持把值不为 $0$ 的位置（不妨设其值为 $v$）置为 $0$：将 $mul$ 乘上 $v$ 的逆元；
- 支持把值为 $0$ 的位置置为非 $0$（不妨设其值为 $v$）：将 $mul$ 乘上 $v$；
- 支持把值 $0$ 的位置置为 $0$：显然；
- 支持把值非 $0$ 的位置置为非 $0$：显然；

- 假如全局存在至少一个为 $0$ 的位置，那么答案为 $0$；否则为 $mul$。

若在线求逆元，这一部分的时间复杂度为 $\mathcal{O}(n \log n)$，可以通过此题。

提交记录请参见：[Submission #62453399 - AtCoder Regular Contest 177](https://atcoder.jp/contests/arc177/submissions/62453399)

---

## 作者：AC_love (赞：1)

我们把可能产生连锁反应的电线杆合并成一段，每根电线杆是最后一个倒下的概率可以拆成两部分：其他段都倒完了的概率 $\times$ 它是自己这一段最后一个倒的概率。

我们发现：如果我们能计算每根电线杆是自己这一段最后一个倒下的概率，我们把这个概率加入这个段中，就能得到这一段倒完了的概率。因此我们只要计算每根电线杆是自己这一段最后一个倒下的概率即可。

考虑怎么计算这个玩意。

第 $i$ 根电线杆是这一段最后一个倒下的，那么它就不能和之前任何一根电线杆产生连锁反应。

$i$ 之前在 $i$ 左侧的电线杆都应该向左倒，$i$ 之前在 $i$ 右侧的电线杆都应该向右倒。

将一段内的所有电线杆按照位置排序，然后去找有几个 $i$ 左面的电线杆倒下的时间是一个后缀最小值即可。同理找一下 $i$ 右面有几根电线杆倒下的时间是一个前缀最小值。这个找的过程可以用单调栈。

这些电线杆倒下的方向是定死的，其他的都无所谓。

顺便需要注意：我们需要判断一下 $i$ 的前驱和后继是否倒下了。如果都倒下了，那么 $i$ 向哪倒都行；如果倒下了一个，那么 $i$ 只能向一个方向倒；如果两个都没倒下，那么 $i$ 不管怎么倒都不可能成为这一段最后一个倒下的。

然后就很好算了。

最后的答案是一个形如 $s_1 \times s_2 \times \cdots \times p \times \cdots \times s_{cnt}$ 之类的东西，这个东西随便维护一下就行了。

[code](https://atcoder.jp/contests/arc177/submissions/59544167)

---

## 作者：gan1234 (赞：1)

### 分析

首先 $H$ 相同，所以如果 $A$ 能压倒 $B$，$B$ 一定能压倒 $A$。

想到可以将所有能互相影响的柱子划分成若干个集合，不同集合之间没有影响，因此可以单独考虑。

对于一个集合还有一个很好的性质，即如果一个柱子向一侧倒下，那么集合中所有这一侧的柱子都会倒下。

显然我们需要将编号从小到大依次考虑。

令当前第 $i$ 个集合全部倒下的概率为 $s_i$。

假如我们已经求出前 $x-1$ 个柱子的所有 $s$，考虑到第 $x$ 个柱子，$x$ 属于集合 $i$，该柱子对 $s_i$ 的影响。

如果此时第 $x$ 个柱子在之前就倒下了，那么不会有任何影响。

如果没倒下，考虑这个柱子如何能使该集合中所有柱子都倒下。

发现当且仅当以下两种情况：

- 柱子 $x$ 左右两侧有一侧柱子全部倒下，那么有 $\frac{1}{2}$ 的概率。

- 柱子 $x$ 左右两侧柱子都倒下了，那么有 $1$ 的概率。

还要乘上前 $x-1$ 次地震 $x$ 都没倒，第 $x$ 次该柱子倒下的概率。

考虑该集合中所有编号小于 $x$ 的都不能倒向 $x$。同时我们注意到在此基础上对于那些已经被压倒的柱子一定不会倒向 $x$，那些会对概率产生影响的柱子构成了随着位置远离 $x$，编号单调减的序列。

这个序列可以单调栈维护。这个序列的大小为 $cnt$，概率就是 $\frac{1}{2}^{cnt}$。

### 代码

```cpp
#include<bits/stdc++.h>
#define MAXN 200005
#define int long long
#define mod 998244353
using namespace std;
int ksm(int x,int k){
	int res=1,t=x;
	while(k){
		if(k&1)res=(res*t)%mod;
		k>>=1;t=(t*t)%mod;
	}
	return res;
}
int pa[MAXN]; 
int find(int x){
	return x==pa[x]?x:pa[x]=find(pa[x]);
}
struct Node{
	int x,id;
}a[MAXN];
int cmp(Node n1,Node n2){
	return n1.x<n2.x;
}
int cmp2(Node n1,Node n2){
	return n1.id<n2.id;
}
vector<int>v[MAXN],v2[MAXN],cnt[MAXN];
int l[MAXN],s[MAXN],pos[MAXN];
int n,H,ans;
int cnt1,cnt2;
signed main(){
	cin>>n>>H;
	for(int i=1;n>=i;i++)cin>>a[i].x,a[i].id=i;
	for(int i=1;n>=i;i++)pa[i]=i;
	sort(a+1,a+n+1,cmp);
	for(int i=2;n>=i;i++)
		if(a[i].x-a[i-1].x<=H)
			pa[find(a[i].id)]=find(a[i-1].id);
	for(int i=1;n>=i;i++)pos[a[i].id]=v2[find(a[i].id)].size(),v2[find(a[i].id)].push_back(a[i].id);
	sort(a+1,a+n+1,cmp2);
	for(int i=1;n>=i;i++)v[find(a[i].id)].push_back(a[i].id);
	for(int i=1;n>=i;i++)
		if(pa[i]==i)cnt1++;
	for(int i=1;n>=i;i++){
		stack<int>st;
		for(int j=0;v2[i].size()>j;j++){
			while(!st.empty()&&st.top()>a[v2[i][j]].id)st.pop();
			st.push(v2[i][j]);
			cnt[i].push_back(st.size());
		}
		while(!st.empty())st.pop();
		for(int j=v2[i].size()-1;j>=0;j--){
			while(!st.empty()&&st.top()>a[v2[i][j]].id)st.pop();
			st.push(v2[i][j]);
			cnt[i][j]+=(st.size())-1;
		}
	}
	int lst=0;
	for(int i=1;n>=i;i++){
		int t=find(i);
		int j=l[t];
		int x=a[v[t][j]].x;
		int p=s[t];
		int r=v[t][j];
		if(!pos[r]||v2[t][pos[r]-1]<r){
			p=(p+ksm(ksm(2,cnt[t][pos[r]]),mod-2))%mod;
		}
		if(pos[r]==v2[t].size()-1||v2[t][pos[r]+1]<r){
			p=(p+ksm(ksm(2,cnt[t][pos[r]]),mod-2))%mod;
		}
		if(p&&!s[t])cnt2++;
		ans=ans*ksm(s[t],mod-2)%mod*p%mod;
		s[t]=p;
		if(cnt2==cnt1){
			ans=1;
			for(int j=1;n>=j;j++)
				if(s[j])
					ans=ans*s[j]%mod;
			cnt2=0;
		}
		cout<<(((ans-lst+mod)%mod)*ksm(2,n)%mod)%mod<<" ";
		l[t]++;
		lst=ans;
	}
	return 0;
}
```

---

## 作者：tuget (赞：0)

思维与代码的缝合怪。

赛时想出了前半部分，赛后花了 3 个小时才做完。

先按坐标排序，可以观察到，一个建筑倒下后能影响到的必然是一个连续段，而且连续段中的任意建筑倒塌不会影响到其他段，故先分段分别处理。

发现在一个段内倒塌的建筑朝左或右倒都必然会使得该建筑左边或右边的所有建筑倒塌，证明是显然的，由此可知，当且仅当一个建筑是目前剩余的段的端点，他才有 $\frac{1}{2} \times \text{出现当前区间的概率}$ 使得在这次地震后该段清空，特别的，如果这次地震是该段唯一剩下的建筑物，那么其需要再 $\times 2$。

接下来思考如何计算 $\text{出现当前区间的概率}$，实际上，区间的左右端点在某次地震后是固定的，故只需要计算这次地震对应的建筑物还存在的概率即可。场上的想法比较简单，这个段内所有地震顺序在其前面的都会影响到这个建筑，设这次地震是该段中第 $i$ 次地震，那么有 $\text{出现当前区间的概率} = 2^i$。

很遗憾，这是错的，以下是一组 hack：

```
5 5
9 5 3 4 7 
```
首先这五个建筑属于同一段，所以不用考虑段的合并，直接按上面所述的写代码会输出：
```
16 0 4 4 2
```
正确应是：
```
16 0 4 4 8
```
怎么回事？

观察一下图片(数字代表第几次地震，箭头是建筑倒的方向)：

![](https://cdn.luogu.com.cn/upload/image_hosting/ftkno85w.png)

按我们算法，此时 $i=5$ 的概率为 $\frac{1}{2^4}$，可实际上，当 $i=2$ 向左倒后，$i=3,4$ 倒的方向不再重要了，所以答案是 $\frac{1}{2^2}$。

进一步思考，我们发现这里的概率实际上和左边和右边所有地震顺序在 $i$ 前，且不被 $i$ 左边或右边建筑先推倒的建筑的数量之和有关。如上图，满足条件的只有 $i=1,2$，因为 $i=3,4 < i=2$ 不影响到 $i=5$。总结起来就是求出到 $i$ 为止前缀最小值的个数 $lf_i$，和后缀最小值的个数 $rg_i$，那么能影响到 $i$ 的建筑总数为 $Num=min(lf_i,lf_{left_i}+1)+min(rg_i,rg_{right_i}+1)$，相应的，轮到 $i$ 且 $i$ 未倒的概率为 $\frac{1}{2^{Num}}$。

现在记 在第 $i$ 次地震后，$i$ 所在段在这次地震中整段倒塌的概率为 $mul_i$，容易发现直接合并段的概率不好做，考虑求前缀和，记 $s_i$ 为第 $i$ 次地震后，$i$ 所在段整段倒塌的概率，那么第 $i$ 次地震后，原序列全部倒塌的概率为所有段的 $s_i$ 的乘积，最终答案只需要再做个差分即可。

压力给到求 $s_i$ 的乘积了，容易发现，一个段中只有若干个关键点（当前段内的点）的 $s_i$ 的值有意义，因为后面一段（指地震发生的时间轴）不属于关键点的 $s_i$ 是一样的，这就变成了对每个关键点到下一个关键点之间左闭右开的区间进行区间乘法，而且关键点总数为 $n$，线段树维护即可，时间复杂度 $O(n\log n)$。

挺抽象的，细节见代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
#define DEBUG
#define db double
#define ll long long
#define usd unsigned
#define ull usd ll
#define i128 __int128
#define frp(in,m,st) freopen(in,m,st)
#define fio(in,out) frp(in,"r",stdin),frp(out,"w",stdout)
#ifndef DEBUG
char B[1<<20 | 5],*P,*G;
#define gc() ((P==G && (G=(P=B)+fread(B,1,1<<20,stdin)),P==G)?EOF:*P++)
#else
#define gc() getchar()
inline void bug(){cout<<endl;}
template<typename TS,typename ... T>
inline void bug(TS p,T ... x){cout<<p<<" ";bug(x...);}
#endif
template<class T>
inline T Read()
{
	T res=0,f=1;char c;
	for(;(c=gc())<'0' || c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9')res=(res<<3)+(res<<1)+(c^48),c=gc();
	return res*f;
}
#define read() Read<int>()
const int mod=998244353;
int n,h,x[maxn],mul[maxn],ans[maxn],k[maxn],rev[maxn],tag[maxn<<2],st[maxn],top,
lf[maxn],rg[maxn];
bool vis[maxn];
inline bool cmp(int a,int b){return x[a]<x[b];}
inline int qpow(int a,int num)
{
	int ans=1;
	while(num)
		(num&1)&&(ans=1ll*ans*a%mod),a=1ll*a*a%mod,num>>=1;
	return ans;
}
inline void modify(int l,int r,int o,int L,int R,int v)
{
	if(L<=l&&r<=R){tag[o]=1ll*tag[o]*v%mod;return;}
	int mid=l+r>>1;
	if(L<=mid)modify(l,mid,o<<1,L,R,v);
	if(mid<R)modify(mid+1,r,o<<1|1,L,R,v);
}
inline int ask(int l,int r,int o,int i)
{
	if(i<1)return 0;
	if(l==r)return tag[o];
	int mid=l+r>>1,ans=1;
	if(i<=mid)ans=ask(l,mid,o<<1,i);
	else ans=ask(mid+1,r,o<<1|1,i);
	return 1ll*ans*tag[o]%mod;
}
inline void solve(int l,int r)
{
	top=0;int i,j;
	for(i=l;i<=r;++i)
	{
		while(top&&st[top]>k[i])--top;
		lf[i]=top,st[++top]=k[i];
	}
	top=0;
	for(i=r;i>=l;--i)
	{
		while(top&&st[top]>k[i])--top;
		rg[i]=top,st[++top]=k[i];
	}
	sort(k+l,k+r+1),vis[l-1]=vis[r+1]=1,lf[l-1]=rg[r+1]=0;
	for(i=l;i<=r;++i)vis[i]=0;
	for(j=l;j<=r;++j)
	{
		i=rev[k[j]];
		if(vis[i-1])
			mul[k[j]]+=qpow(qpow(2,min(lf[i-1]+1,lf[i])+min(rg[i+1]+1,rg[i])+1),mod-2),
			mul[k[j]]%=mod;
		if(vis[i+1])
			mul[k[j]]+=qpow(qpow(2,min(lf[i-1]+1,lf[i])+min(rg[i+1]+1,rg[i])+1),mod-2),
			mul[k[j]]%=mod;
		vis[i]=1;
	}
	for(j=l+1;j<=r;++j)mul[k[j]]+=mul[k[j-1]],mul[k[j]]%=mod;
	if(k[l]>1)modify(1,n,1,1,k[l]-1,0);
	for(i=l;i<r;++i)modify(1,n,1,k[i],k[i+1]-1,mul[k[i]]);
	modify(1,n,1,k[r],n,mul[k[r]]);
}
int main()
{
	int i,l=1,p2;
	n=read(),h=read(),p2=qpow(2,n);
	for(i=1;i<=n;++i)x[i]=read(),k[i]=i,ans[i]=1;
	sort(k+1,k+n+1,cmp),x[0]=x[k[1]];
	for(i=1;i<=(n<<2);++i)tag[i]=1;
	for(i=1;i<=n;rev[k[i]]=i,++i)
		if(x[k[i]]-x[k[i-1]]>h)solve(l,i-1),l=i;
	solve(l,n);
	for(i=1;i<=n;++i)printf("%lld ",1ll*(ask(1,n,1,i)-ask(1,n,1,i-1)+mod)%mod*p2%mod);
	return 0;
}
```

---

## 作者：K8He (赞：0)

[Earthquakes .](https://atcoder.jp/contests/arc177/tasks/arc177_d)

赛时没好好想，躺床上睡觉时会的，急了 .

首先显然可以划分成若干组互不相关的骨牌，所有骨牌的倒塌时间就是每一组的倒塌时间取 max。那么很自然想到一种统计方法是对于每个组先算出每种倒塌时间的概率，统计时算上其他组比当前组倒塌时间更早的概率之积。

接下来考虑每个子问题，枚举最后倒塌的是哪一个，发现组内除了当前枚举的骨牌以外，哪些骨牌自然倒塌和所有骨牌的倒塌方向都是一定的，否则会把这个骨牌提前推倒。对于自然倒塌的骨牌（不是被其他推倒的），每个都是方向二选一贡献 $\dfrac{1}{2}$ 的概率，不过考虑到最后输出乘上 $2^n$，可以直接算被非自然推倒的骨牌数量，每个产生 $2$ 的贡献。对于「哪些骨牌自然倒塌」的问题，当前骨牌的左右两边是独立的，可以使用单调栈两次推完。

注意如果某一侧相邻的骨牌倒塌时间比当前骨牌晚，那么当前骨牌不能向另一侧倾倒，否则会剩下这一侧的一些骨牌，需要特判一下。

概率之积好像有更优秀做法，不过懒了写的线段树。

时间复杂度 $O(n\log n)$，常数比较小。

[AtCoder Submission .](https://atcoder.jp/contests/arc177/submissions/53438151)

---

## 作者：g1ove (赞：0)

好题。2300 分。

## 思路
我们发现我们可以把这些这些电线杆分成若干组，每组之间互不影响。

然后，如果一个电线杆往左倒，等同于把这组内这个电线杆往左的电线杆全部推倒。往右同理。

我们想想怎么在第 $x$ 次操作把所有电线杆推倒。

那么无非就两种情况：
+ 情况 $1$：$x$ 往左推，推倒 $1\sim x-1$，$x+1$ 往右推，推倒 $x+1\sim n$。
+ 情况 $2$：$x$ 往右推，推倒 $x\sim n$，$x-1$ 往左推，推倒 $1\sim x-1$。

显然，如果第 $x$ 次推倒所有电线杆，明显要在 $x-1$ 次推倒在不是同一组的所有电线杆。

设 $f_i$ 表示推倒第 $i$ 组电线杆的概率。那么我们边动态更新 $f$ 数组边求答案。

根据乘法原理，假设有 $m$ 组，$x$ 在 $bel_x$ 组，那么 $x-1$ 次推倒所有电线杆的概率容易算得为 $\prod\limits_{i=1,i\ne bel_x}^m f_i$。

现在我们考虑第 $bel_x$ 组的情况。

因为我们要求**恰好在第 $x$ 次推倒所有电线杆**，所以对于所有电线杆，对于 $bel_x$ 组内任意一根电线杆 $p$，假设现在是情况 $1$，我们分类讨论一下：

- 电线杆 $x$ 的后继 $x+1$ 在 $x$ 之后被推倒。

显然，这种情况下，不可能推倒全部电线杆。

- 电线杆 $x$ 的后继 $x+1$ 在 $x$ 之前被推倒。 

这种情况是合法的。我们考虑任意一根电线杆 $p$，它有几种情况。

+ $p$ 已经被推倒。

那么，贡献为 $2$，因为选择左推和右推都不会影响答案（可以理解为操作不了）。

+ $p$ 还没有被推倒。

明显，$p$ 推向的方向是唯一的，就是往非 $x$ 的方向推，因为不能推倒 $x$，所以对贡献为 $1$。

最终的第 $x$ 次推倒所有电线杆的概率就是所有贡献的乘积。不妨设其为 $w$，那么我们更新 $f_{bel_x}\leftarrow f_{bel_x}+w$。

现在问题转化为怎么算一个电线杆会不会被推倒。

我们考虑一个 $p$ 怎么才会没有被推倒。即 $p\sim x$ 这一部分没有操作时间比 $p$ 小的电线杆，才会没有被推倒。换句话说，我们需要求 $x$ 在时间戳序列上分别往左、往右的降序序列的长度。

这里的降序序列的意思是遇见小于最小值的数才加入序列。举个例子，$11,9,10,5,7,3,4,1$ 的降序序列是 $11,9,5,3,1$。这个东西可以用线段树或者二分和ST表解决。

然后我们就能求出有多少个被推倒的电线杆。然后就能很容易解决问题了。

记得注意 $0$ 的情况。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
using namespace std;
int n,m;
const ll mod=998244353,inv2=mod-mod/2;
ll inv(ll a,ll x=mod-2)
{
	ll s=1;
	while(x)
	{
		if(x&1) s=s*a%mod;
		a=a*a%mod;
		x>>=1;
	}
	return s;
}
ll pw[N];
int x[N];
struct node{
	int x,id;
}a[N];
int bel[N],ids;
ll res=1;
ll cur[N];
int tag;
int d[N];
ll ans[N];
int pre[N],nxt[N];
int l[N],r[N];
set<int>st;
struct ST{
	int f[N][20];
	void prest(int n)
	{
		for(int i=n;i>=1;i--)
			for(int j=1;j<=__lg(n-i+1);j++)
				f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
	}
	int ask(int l,int r)
	{
		int len=__lg(r-l+1);
		return min(f[l][len],f[r-(1<<len)+1][len]);
	}
}tr;
int main()
{
//	freopen("m.txt","w",stdout);
	scanf("%d%d",&n,&m);
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<=n;i++)
		scanf("%d",&x[i]),a[i]=(node){x[i],i};
	sort(a+1,a+1+n,[](node a,node b){return a.x<b.x;});
	int lst=1;
	a[n+1].x=(2e9)+5;
	for(int i=1;i<=n;i++) tr.f[i][0]=a[i].id;
	tr.prest(n); 
	for(int i=2;i<=n+1;i++)
		if(a[i].x-a[i-1].x>m)
		{
			++ids;
			for(int j=lst;j<=i-1;j++)
				bel[a[j].id]=ids,++d[ids],pre[a[j].id]=a[j-1].id,nxt[a[j].id]=a[j+1].id;
			pre[a[lst].id]=nxt[a[i-1].id]=0;
			for(int j=i-1;j>=lst;j--)
			{
				int lo=j+1,hi=i-1;
				while(lo<=hi)
				{
					int mid=(lo+hi)/2;
					if(tr.ask(j,mid)<a[j].id) hi=mid-1;
					else lo=mid+1;
				}
				if(hi+1==i) r[a[j].id]=0;
				else r[a[j].id]=r[a[hi+1].id]+1;
			}
			for(int j=lst;j<=i-1;j++)
			{
				int lo=lst,hi=j-1;
				while(lo<=hi)
				{
					int mid=(lo+hi)/2;
					if(tr.ask(mid,j)<a[j].id) lo=mid+1;
					else hi=mid-1;
				}
				if(lo==lst) l[a[j].id]=0;
				else l[a[j].id]=l[a[lo-1].id]+1;
			}
			for(int j=i-1;j>=lst;j--) l[a[j].id]=j-lst-l[a[j].id];
			for(int j=i-1;j>=lst;j--) r[a[j].id]=i-1-j-r[a[j].id];
			lst=i;
		}
	for(int i=1;i<=n;i++)
	{
		int b=bel[i];
		d[b]--;
		ll w=0;
		if(pre[i]<i)
			w+=pw[l[pre[i]]]*pw[r[i]]%mod;
		if(nxt[i]<i)
			w+=pw[r[nxt[i]]]*pw[l[i]]%mod,w%=mod;
		if(!w) 
		{
			printf("0 ");
			continue;
		}
		if(!cur[b]) tag++;
		else res=res*inv(cur[b])%mod;
		if(tag==ids) printf("%lld ",res*w%mod);
		else printf("0 ");
		cur[b]=(cur[b]+w)%mod;
		if(!cur[b]) tag--;
		else res=res*cur[b]%mod;
	}
	return 0;
}
```

---

