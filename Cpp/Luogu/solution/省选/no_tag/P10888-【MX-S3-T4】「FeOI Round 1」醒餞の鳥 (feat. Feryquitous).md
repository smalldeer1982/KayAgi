# 【MX-S3-T4】「FeOI Round 1」醒餞の鳥 (feat. Feryquitous)

## 题目背景

原题链接：<https://oier.team/problems/S3D>。

---

![](bilibili:BV16h411Y7YB)

## 题目描述

有 $n$ 个学生（编号为 $1 \sim n$）参加了一场有 $m$ 门学科（编号为 $1 \sim m$）的考试，现在你知道，学生 $i$ 的第 $j$ 门学科考试的成绩为 $a_{i, j}$。

现在你想要给这些学生排名。由于成绩不形成偏序关系的两个学生实力难以比较，所以你打算设置 $m$ 个实数 $p_{1 \sim m}$（要求满足 $\sum_{i = 1}^m p_i = 1$，且 $p_i \ge 0$）作为权值。定义学生 $i$ 的加权总分为 $\sum_{j = 1}^m a_{i, j} \times p_j$，则按照加权总分降序排名，加权总分相等的则排名并列。

现在这 $m$ 个学科的老师都向你提出了要求，第 $k$ 个学科的老师想让你所设置的 $p$ 满足：

- 以这个 $p$ 得到的排名结果中，不存在一对学生 $(x, y)$（$x \ne y$），使得 $x$ 排名更靠前（并列不算），但是 $a_{x, k} < a_{y, k}$；

因为你想要尽量自由的分配权值，所以你需要对于每个 $k$（$1 \le k \le m$），都**分别**求出：

- $p_k$ 至少要为多少，才能保证**无论如何分配其他 $\boldsymbol{p_i}$ 的权值，都能满足**第 $k$ 个学科的老师的要求？请输出答案对 $998244353$ 取模的结果。

## 说明/提示

**【样例解释】**

对于第一组数据，询问的答案取模之前分别为 $\frac{1}{4}, \frac{3}{4}, \frac{1}{4}, \frac{1}{2}$。

对于第二组数据，询问的答案取模之前分别为 $\frac{4}{5}, \frac{4}{5}$。

对于第三组数据，询问的答案取模之前分别为 $0, 0, 0, 0$。

对于第一组数据的 $k = 2$ 的询问，假设 $p = [0.1, 0.75, 0.1, 0.05]$：

- 第 $1$ 个学生的加权总分是 $4 \times 0.1 + 2 \times 0.75 + 4 \times 0.1 + 3 \times 0.05 = 2.45$；
- 第 $2$ 个学生的加权总分是 $1 \times 0.1 + 3 \times 0.75 + 1 \times 0.1 + 2 \times 0.05 = 2.55$；
- 第 $3$ 个学生的加权总分是 $1 \times 0.1 + 2 \times 0.75 + 4 \times 0.1 + 2 \times 0.05 = 2.1$；
- 第 $4$ 个学生的加权总分是 $4 \times 0.1 + 2 \times 0.75 + 4 \times 0.1 + 3 \times 0.05 = 2.45$；

则你令按加权总分降序排名的学生编号为 $[2, 4, 1, 3]$（当然也可以令其为 $[2, 1, 4, 3]$），且 $a_{2, 2} = 3, a_{4, 2} = 2, a_{1, 2} = 2, a_{3, 2} = 2$，不存在排名更靠后但是第 $2$ 个学科成绩更高的情况。

可以证明，在 $p_2 \ge 0.75$ 的情况下，无论其他 $p_i$ 如何分布，都可以满足要求；而 $p_2 < 0.75$ 的情况下，一定存在一种其他 $p_i$ 的分布使得无法满足要求。

**【数据范围】**

**本题开启捆绑测试。**

设 $\sum nm$ 为单个测试点内所有的 $nm$ 之和。

对于 $100\%$ 的数据，$1 \le T \le 5 \times 10^4$，$ 2 \le n, m \le 10^5$，$ \sum nm \le 2 \times 10^5$，$ 0 \le a_{i, j} \leq 10^8$。

| 子任务编号 | $n$ | $m$ | $\sum nm$ | 特殊性质 | 分数 |
| :-: | :-: | :-: | :-: | :-: | :-: |
| $1$ | $\leq 10$ | $\leq 10$ | $\leq 100$ | 无 | $5$ |
| $2$ | $\leq 100$ | $\leq 100$ | $\leq 10^4$ | 无 | $10$ |
| $3$ | $\leq 5 \times 10^3$ | $\leq 5 \times 10^3$ | $\leq 10^4$ | 无 | $15$ |
| $4$ | $\leq 100$ | $\le 10^5$ | $\le 2 \times 10^5$ | 无 | $20$ |
| $5$ | $\le 10^5$ | $\leq 100$ | $\le 2 \times 10^5$ | 无 | $10$ |
| $6$ | $\le 10^5$ | $\le 10^5$ | $\le 2 \times 10^5$ | $a_{i, j} \in \{0, 1\}$ | $20$ |
| $7$ | $\le 10^5$ | $\le 10^5$ | $\le 2 \times 10^5$ | 无 | $20$ |


## 样例 #1

### 输入

```
4
4 4
4 2 4 3
1 3 1 2
1 2 4 2
4 2 4 3
10 2
1 2
4 0
3 1
2 4
0 5
2 3
3 2
1 1
2 2
4 4
4 4
0 0 0 0
0 0 0 0
1 0 1 0
0 0 0 0
2 10
92603107 17358677 20869254 22085089 68529385 51524980 47064864 17692636 31121387 37022044
25517267 69562538 61254114 54886162 15087981 27505611 76082026 59892091 54661294 59475460```

### 输出

```
748683265
249561089
748683265
499122177
399297742
399297742
0
0
0
0
892513752
105730602
366911811
374997189
954012663
897963459
891479524
220357565
706471693
519276178
```

# 题解

## 作者：vegetable_king (赞：9)

出题人题解。

首先考虑一个最基本的策略：

假设我们要 check $p_k \ge X$ 是否合法。

那么我们只需要对于所有的 $1 \le l \le m, l \ne k$，**分别**令 $p_k = X, p_l = 1 - X$，其他的 $p$ 为 $0$，都 check 一次即可。

证明是显然的，如果我们要在 $p_k = X$ 的情况下分配其他的 $p$ 使得第 $i$ 个学生的加权总分超过第 $j$ 个学生的加权总分 $(a_{i, k} < a_{j, k})$，那么将剩下的 $1 - X$ 集中在 $a_{i, l} - a_{j, l}$ 最大的第 $l$ 个学科上一定不劣。

于是根据上述策略，我们得到了一个单组数据 $O(m^2 n \log n \log v)$ 并且需要二分的做法，但是答案需要输出有理数，无法二分。

考虑不排序而是直接暴力枚举 $i, j, k, l (a_{i, k} < a_{j, k}, a_{i, l} > a_{j, l})$，则我们得到一个不等式：

$$
X a_{i, k} + (1 - X) a_{i, l} \le X a_{j, k} + (1 - X) a_{j, l}
$$

解得：

$$
X \ge \frac{a_{i, l} - a_{j, l}}{a_{i, l} - a_{j, l} + a_{j, k} - a_{i, k}}
$$

于是题意就相当于对于每个 $k$，求上式的最大值，这个东西显然可以暴力 $O(n^2 m^2)$ 做。

### $n \le 100$

发现需要最大化的分式是 $\frac p{p + q}$ 形式的，所以我们枚举 $i, j, l$ 确定 $p = a_{i, l} - a_{j, l}$ 并枚举 $k$ 最小化 $q = a_{j, k} - a_{i, k}$。

因为 $q$ 只与 $i, j, k$ 相关，并且 $k \ne l$，所以我们可以对每一对 $i, j$ 枚举 $k$ 来 $O(n^2m)$ 预处理出最小次小的 $q$，即可做到 $O(1)$ 查询 $q$。

于是我们得到了一个单组数据时间复杂度为 $O(n^2m)$ 的做法。

### $m \le 100$

实际上，如果我们先枚举了 $k, l$，我们就不需要对所有的 $i, j$ 去判断了。根据比较的传递性，如果存在 $o$ 满足 $a_{i, k} < a_{o, k} < a_{j, k}$，则无需考虑 $i, j$ 这一对是否满足要求。于是我们对于某个 $(k, l)$，将 $a_{i, k}$ 相等的 $i$ 划为一类，则我们只需要考虑数值相邻的两个类。

考虑固定类别之后，$a_{i, k}, a_{j, k}$ 都被固定了，则 $\frac p{p + q}$ 中的 $q = a_{j, k} - a_{i, k}$ 已经被确定，则我们为了让分式最大，应该最大化 $p = a_{i, l} - a_{j, l}$，而 $p$ 是在两个类中各选取一个数作差，$a_{i, l}$ 选最大，$a_{j, l}$ 选最小即可。

每个点只会被一个类包含，对于每个类暴力扫一遍求出最大值与最小值，时间复杂度是 $O(n)$ 的。

于是我们又得到了一个单组数据时间复杂度为 $O(nm^2)$ 的做法。

### 结合一下

考虑数据分治，$n \le m$ 时跑 $O(n^2m)$，$n > m$ 时跑 $O(nm^2)$，则单组数据时间复杂度为 $O(nm\min(n, m))$。

设 $S = nm$，则 $\min(n, m) \le \sqrt S$。所以单组数据时间复杂度为 $O(S \sqrt S)$，可以通过本题。

另外，涉及到的分数分子和分母显然都不会超过 $2v = 2 \times 10^8$，不是 $998244353$ 的倍数，必定存在逆元。

关于分数比大小，因为分子分母都在 int 范围内，所以可以写一个 frac 类，比大小的时候开 long long 交叉相乘就不会有精度损失。

[code](https://www.luogu.com.cn/paste/krfam9v2)

---

## 作者：luanyanjia (赞：7)

话说这题真的有紫吗（问号

注意到数据范围中提到 $\sum{nm} \le 2 \times 10^5 $，这里实际上是隐含了 $\min(n,m) \le \sqrt{2\times 10^5}$ 的。我们考虑根据 $n$ 和 $m$ 的大小关系设计出不同的算法。

- $m<n$

一个比较直接的想法是对于每一个科目先按该科目的分数排序，这样我们只需要考虑相邻两个人的关系即可。

对于排名相邻的两种分数的人，最坏情况下的赋值一定是把剩下的权值全部给后面一名的优势科目，若枚举到第 $j$ 个科目，第 $i$ 个人，后面的人超出前面的人最多分数的科目为 $k$ 的话，那么 $p_k$ 需满足：

$$ p_j \times (a_{i,j} - a_{i-1,j}) > (1-p_j) \times (a_{i-1,k} - a_{i,k}) $$

直接计算，最后取最大值即可。时间复杂度 $O(nm^2)$。

- $n<m$

和上一种情况类似，但这一次我们要尽量避免枚举 $m$。

双层循环枚举学生 $i$ 和 $j$，遍历每一科目，先找到 $j$ 相对 $i$ 的优势科目，再对任意 $k$ 使得 $c_{i,k} > c_{j,k}$ （即 $i$ 的排名比 $j$ 高）计算贡献即可。 

时间复杂度 $O(n^2m)$。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	char ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
const int N=1e5+5,mod=998244353;
int T,n,m;
struct node{vector<int> v;}a[N],tmp[N],tmp2[N];
inline int KSM(int x,int n){
	int ans=1;
	while(n){
		if(n&1)ans=1ll*x*ans%mod;
		x=1ll*x*x%mod;
		n>>=1;
	}
	return ans;
}
namespace m2n{
	inline void Solve(){
		for(int j=0;j<m;j++){
			int mxm=1,mxz=0,cnt=0;
			sort(a+1,a+n+1,[=](node a,node b){return a.v[j]<b.v[j];});
			tmp[++cnt]=a[1];tmp2[cnt]=a[1];
			for(int i=2;i<=n;i++){
				if(a[i].v[j]!=a[i-1].v[j])tmp[++cnt]=a[i],tmp2[cnt]=a[i];
				else {
					for(int k=0;k<m;k++)
						tmp[cnt].v[k]=min(tmp[cnt].v[k],a[i].v[k]),
						tmp2[cnt].v[k]=max(tmp2[cnt].v[k],a[i].v[k]);
				}
			}
			for(int i=2;i<=cnt;i++){
				int c1=tmp[i].v[j]-tmp[i-1].v[j],c2=0;
				for(int k=0;k<m;k++){
					if(k==j)continue;
					c2=max(c2,tmp2[i-1].v[k]-tmp[i].v[k]);
				}
				if(!c2)continue;
				if(1ll*c2*mxm>1ll*(c1+c2)*mxz)mxm=c1+c2,mxz=c2;
			}
			printf("%lld\n",1ll*mxz*KSM(mxm,mod-2)%mod);
		}
		for(int i=1;i<=n;i++)a[i].v.clear();
	}
}
namespace n2m{
	int mxz[N],mxm[N];
	inline void Solve(){
		for(int i=0;i<=m;i++)mxz[i]=0,mxm[i]=1;
		for(int x=1;x<=n;x++){
			for(int y=1;y<=n;y++){
				if(x==y)continue;
				int c2=0;
				for(int i=0;i<m;i++)
					c2=max(c2,a[y].v[i]-a[x].v[i]);
				for(int i=0;i<m;i++){
					if(a[y].v[i]>=a[x].v[i])continue;
					int c1=a[x].v[i]-a[y].v[i];
					if(a[x].v[i]>a[y].v[i])
						if(1ll*(c1+c2)*mxz[i]<1ll*mxm[i]*c2)mxm[i]=c1+c2,mxz[i]=c2;
				}
			}
		}
		for(int i=0;i<m;i++)
			printf("%lld\n",1ll*mxz[i]*KSM(mxm[i],mod-2)%mod);
		for(int i=1;i<=n;i++)a[i].v.clear();
	}
}
signed main(){
	rd(T);
	while(T--){
		rd(n,m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int x;rd(x);
				a[i].v.push_back(x);
			}
		}
		if(n<=m)n2m::Solve();
		else m2n::Solve();
	}
	return 0;
}

```

---

## 作者：Composite_Function (赞：2)

给出一种可能不是正解但跑得很快而且是赛时想到的一个做法。

一开始要理解这个 $p_k$ 代表着什么。贪心的思想，为了把 $p_k$ 卡到上界，一定是把除了 $p_k$ 另一个 $p_l$ 写成 $1-p_k$（因为这样可以一个学科分数差最大的发挥最大的权值）。于是，$p_k = \max_{1 \le i,j,l \le n,a_{i,k}<a_{j,k},a_{j,l}<a_{i,l}}\{\frac{a_{i,l} - a_{j,l}}{a_{j,k} - a_{i,k} + a_{i,l} - a_{j,l}},0\}$。直接做是 $\Theta(n^2m^2)$ 的。

首先注意到 $\Theta(n^2m)$ 的方法。枚举 $i,j$，注意到原来这个式子中 $a_{j,l} - a_{i,l}$ 是越大越好，那么直接枚举出来最大值，再和其他 $k$ 算一次答案即可。

这样可以通过 $n$ 较小的点。那么考虑 $n$ 较大的时候，也就是 $m$ 较小的时候。

给出一个 $\Theta(nm^2\log_{2}m)$ 的方法。注意到把 $\frac{a_{i,l} - a_{j,l}}{a_{j,k} - a_{i,k} + a_{i,l} - a_{j,l}}$ 写成 $\frac{1}{1 - \frac{a_{i,k} - a_{j,k}}{a_{i,l} - a_{j,l}}}$。那么注意到了底下的式子这其实是两个点 $(a_{i,k},a_{j,k})$ 和 $(a_{i,l}, a_{j,l})$ 之间的斜率。算一个斜率的最值，直接对其按 $x$ 坐标排序即可。

结合上述两种做法，直接分类讨论一些即可。没有可以卡时间就过了。

```cpp
#include <bits/stdc++.h>
using namespace std;

struct FastIO
{
    inline FastIO& operator >> (int& x) {
        x = 0; char f = 0, ch = getchar();
        while(ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
        while(ch <= '9' && ch >= '0') x = x * 10 + ch - 48, ch = getchar();
        return x = (f ? -x : x), *this;
    }
    inline FastIO& operator >> (long long& x) {
        x = 0; char f = 0, ch = getchar();
        while(ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
        while(ch <= '9' && ch >= '0') x = x * 10 + ch - 48, ch = getchar();
        return x = (f ? -x : x), *this;
    }
    inline FastIO& operator >> (double& x) {
        x = 0; char f = 0, ch = getchar();
        double d = 0.1;
        while(ch > '9' || ch < '0') f |= (ch == '-'), ch = getchar();
        while(ch <= '9' && ch >= '0') x=x * 10 + ch - 48, ch = getchar();
        if(ch == '.')
        {
            ch = getchar();
            while(ch <= '9' && ch >= '0') x += d * (ch ^ 48), d *= 0.1, ch = getchar();
        }
        return x = (f ? -x : x), *this;
    }
}rin;

#define ll long long
#define uint unsigned int
#define reg register
#define ld long double
#define uint unsigned int
#define ull unsigned long long
#define qint const int&
#define qll const ll&
#define quint cosnt uint&
#define qull const ull&
#define endl "\n"

inline void qmod(int& x, const int& mod) {
	x = x >= mod? x - mod : x;
}

const int N = 2e5 + 10, mod = 998244353;
int T, n, m;
vector<vector<int> > a;
struct Node {
	int x, y;
} ans[N];
pair<int, int> point[N];
inline bool operator <(Node x, Node y) {
	return 1ll * x.x * y.y < 1ll * y.x * x.y;
}

inline int qpow(int a, int b) {
	int ret = 1;
	while (b) {
		if (b & 1) ret = 1ll * ret * a % mod;
		a = 1ll * a * a % mod, b >>= 1;
	}
	return ret;
}

inline int inv(int a) {
	return qpow(a, mod - 2);
}

inline void init(int n, int m) {
	vector<int> row;
	row.assign(m + 1, 0);
	a.assign(n + 1, row);
	for (int i = 1; i <= m; ++i) ans[i].x = 0, ans[i].y = 1;
}

signed main() {
	rin >> T;
	while (T--) {
		rin >> n >> m;
		init(n, m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				rin >> a[i][j];
		if (n < m * log2(m)) {
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j) if (i != j) {
					int maxx = -0x3f3f3f;
					for (int k = 1; k <= m; ++k)
						if (a[i][k] >= a[j][k]) maxx = max(maxx, a[i][k] - a[j][k]);
					if (maxx >= 0) {
						for (int k = 1; k <= m; ++k)
							if (a[i][k] < a[j][k]) {
								Node ret;
								ret.x = maxx;
								ret.y = maxx + a[j][k] - a[i][k];
								if (ans[k] < ret) ans[k] = ret;
							}
					}
				}
		}
		else {
			for (int k = 1; k <= m; ++k)
				for (int l = 1; l <= m; ++l) if (k != l) {
					for (int i = 1; i <= n; ++i) point[i] = make_pair(a[i][k], a[i][l]);
					sort(point + 1, point + n + 1);
					for (int i = 1; i < n; ++i) {
						if (point[i].second < point[i + 1].second) continue;
						Node ret;
						ret.x = point[i].second - point[i + 1].second;
						ret.y = point[i + 1].first - point[i].first + ret.x;
						if (ans[k] < ret) ans[k] = ret;
					}
				}
		}
		for (int i = 1; i <= m; ++i)
			cout << 1ll * ans[i].x * inv(ans[i].y) % mod << endl;
	}
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：1)

限制等价于对于任意 $a_{x,k} < a_{y,k}$ 均满足 $\sum_{j=1}^m a_{x,j} \times p_j \leq \sum_{j=1}^m a_{y,j} \times p_j$。

那么显然，想要取到最紧的限制，就要对于一组满足 $a_{x,k} < a_{y,k}$ 的 $x,y$ 把剩余的权重全部加在 $a_{x,l} - a_{y,l}$ 最大的 $l$ 上，于是推推式子可以得到 $\min(p_k) = \max(1 + \frac{a_{y,k} - a_{x,k}}{\min(a_{y,l} - a_{x,l})})$。

于是对于每个 $x,y$ 预处理出 $\min(a_{y,l} - a_{x,l})$ 的值即可做到 $O(m \times n^2)$ 预处理，$O(m \times n^2)$ 地求解答案。

考虑进一步地化简限制，真的有必要 $O(n^2)$ 地枚举 $x,y$ 吗？考虑到这是一个求解限制使得所有数保持原顺序的问题，所以实际上我们只需要让相邻的数保持相对顺序即可使得所有数保持顺序，具体地，实际上对于一个 $x$ 只需要要考虑最小的满足 $a_{y,k} > a_{x,k}$ 的所有 $y$ 即可。因为相邻的数有序后，可以通过归纳得到整个序列依然保持有序。

所以考虑枚举学科时将所有的 $a_{x,k}$ 离散化，再枚举另一种学科，求解当 $a_{x,k} = t$ 时的 $\max(a_{x,l})$ 与 $\min(a_{x,l})$，然后枚举离散化后相邻的值计算贡献即可。

这么做时间复杂度是 $O(n \times m^2 + n \times m \log n)$ 的，考虑在 $n \leq \sqrt{n \times m}$ 时跑上一种算法，否则跑这种算法即可做到 $O(n \times m \sqrt{n \times m} + n \times m \log n)$。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int warma = 320;
const int maxn = 1e5+114;
const int mod = 998244353;
int n,m;
vector<int> a[maxn];
int Min[warma+1][warma+1];
int qpow(int a,int b){
	if(b==0) return 1;
	if(b==1) return a;
	int res=qpow(a,b/2);
	res=res*res%mod;
	if(b%2==1) res=res*a%mod;
	return res;
}
//n<=warma
void init(){
	for(int x=1;x<=n;x++){
		for(int y=1;y<=n;y++){
			if(x!=y) Min[x][y]=INT_MAX;
		}
	}
	for(int k=1;k<=m;k++){
		for(int x=1;x<=n;x++){
			for(int y=1;y<=n;y++){
				if(a[x][k]>a[y][k]){
					if(a[y][k]-a[x][k]<=Min[x][y]){
						Min[x][y]=a[y][k]-a[x][k];
					}
				}
			}
		}
	}
}
int ans1(int k){
	int ansa=0,ansb=1;//ansa/ansb
	for(int x=1;x<=n;x++){
		for(int y=1;y<=n;y++){
			if(a[x][k]<a[y][k]){
				if(Min[x][y]!=INT_MAX){
					int B=-Min[x][y];
					int A=B+a[y][k]-a[x][k];
					// B/A >= ansa/ansb
					//B*ansb>=ansa*A
					if(B*ansb>=ansa*A) ansa=B,ansb=A;
				}
			}
		}
	}
	return ansa%mod*qpow(ansb%mod,mod-2)%mod;
}
//n>warma
int p[maxn];
int now;
bool cmp(int x,int y){
	return a[x][now]<a[y][now];
}
//按照第 now 科升序排序的结果
int Mx[maxn],Mi[maxn];//其余学科最大 /最小
int tot,lsh[maxn];
int ans2(int k){
    for(int i=1;i<=n;i++) p[i]=i;
    now=k;
    sort(p+1,p+n+1,cmp);
    int ansa=0,ansb=1;
    for(int k1=1;k1<=m;k1++){
        if(k1==k) continue;
        for(int i=1;i<=n;i++) Mx[i]=-INT_MAX,Mi[i]=INT_MAX;
        tot=0;
        for(int i=1;i<=n;i++){
            if(i==1||a[p[i]][k]!=a[p[i-1]][k]) tot++,lsh[tot]=a[p[i]][k];
            //贡献到 tot 上
            Mx[tot]=max(Mx[tot],a[p[i]][k1]);
            Mi[tot]=min(Mi[tot],a[p[i]][k1]);
        }
        for(int i=1;i<tot;i++){
            //比较 i i+1
            if(Mx[i]>Mi[i+1]){
                int B=-(Mi[i+1]-Mx[i]);
                int A=B+lsh[i+1]-lsh[i];
                if(B*ansb>=ansa*A) ansa=B,ansb=A;
            }
        }
    }
    return ansa%mod*qpow(ansb%mod,mod-2)%mod;
}
void work(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		a[i].clear();
		a[i].push_back(0);
		for(int j=1;j<=m;j++){
			int x;
			cin>>x;
			a[i].push_back(x);
		}
	}
	if(n<=warma){
        init();
        for(int i=1;i<=m;i++) cout<<ans1(i)<<'\n';
	}
    else{
        for(int i=1;i<=m;i++) cout<<ans2(i)<<'\n';
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--) work();
	return 0;
}
/*
1
4 4
4 2 4 3
1 3 1 2
1 2 4 2
4 2 4 3
*/

```

---

## 作者：紊莫 (赞：1)

简单题，但是一开始做法比较玩原神，我头脑太简单。

---

首先来一点基础的：

假设我们现在求满足 $x$ 这位老师的情况下 $p$ 的最大值。

对于一组 $i,j$ 满足 $a_{i, x} < a_{j, x}$，设 $y$ 是 $a_{i, y} - a_{j, y}$ 最大的 $y$，那么最坏情况显然是把剩下的权值全都给了 $y$。

这个时候要求满足：

$$p_xa_{i, x} + (1 - p_x)a_{i, y} \le p_xa_{j, x} + (1 - p_x)a_{j, y}$$

化简一下得到：

$$p_x \ge \dfrac{a_{i, y} - a_{j, y}}{a_{j, x} - a_{i, x} + a_{i, y} - a_{j, y}}$$

我们枚举 $i, j$，再加上之前知道的 $x$，问题变成计算 $a_{i, y} - a_{j, y}$ 的最大值。

而 $a_{i, y} - a_{j, y}$ 只和 $i, j, y$ 有关，不妨预处理出所有情况。

特别的，因为要保证 $x \not= y$（否则导致分母为 0），所以额外记录次大值即可。

现在我们有了一个 $\mathcal{O}(n^2m)$ 的算法。

---

下面是另一个算法。

还是上面的式子：

$$p_x \ge \dfrac{a_{i, y} - a_{j, y}}{a_{j, x} - a_{i, x} + a_{i, y} - a_{j, y}}$$

只不过我们现在枚举的是 $j, y$。

### 解决方法一（赛时想法）

观察这个式子，把 $(a_{i, y} - a_{i, x},a_{i, y})$，$(a_{j, y} - a_{j, x},a_{j, y})$ 看作是两个二维平面上的点。

那么 $p_x$ 就是对于每个点，求出到其他点的斜率最大值，可以利用单调栈维护凸壳，在上面二分即可。

时间复杂度 $\mathcal{O}(nm^2\log (nm))$。

### 解决方法二（官方解法）

在此之前，我们将序列按照 $a_{i,x}$ 从小到大排序。

那么不难发现题目要求的相当于是按照这样的顺序，加权分也要递增。

重要性质在于**递增**是有传递性的，也就是只需要考虑相邻的两个即可！

我们把 $a_{i, x}$ 相同的看作是一个连通块。

考虑相邻的两个块，考虑 $i,j$ 分别在这两个块内的情况。

那么 $a_{i,x}，a_{j,x}$ 就是确定的了。

回去看一下式子，发现要最大化 $a_{i,y} - a_{j,y}$，那么左边的块取 $\max(a_{i, y})$，右边取最小即可。

时间复杂度 $\mathcal{O}(nm^2)$。

---

观察数据范围 $nm \le 2 \times 10^5$，那么根号分治即可，时间复杂度 $\mathcal{O}(nm\sqrt{nm})$。

---

## 作者：北文 (赞：0)

好，模拟。  
首先让我们想想题目让我们求什么，如果只有两个学生 $x,y$，而要求满足第 k 个老师（即学科）的要求时如何计算出最小的 $p_k$。不妨设 $a_{x,k}<a_{y,k}$，很显然我们只关注 $a_{y,k}-a_{x,k}$ 和最大的 $a_{x,j}-a_{y,j}$。  
为什么呢？总权重只有 1，如强制分给第 $k$ 个学科，剩下的权重应全部分给**差值**最大的另一门学科，这样的情况是最容易使得 $x$ 超过 $y$ 的。  
我们记 $d_1=a_{y,k}-a_{x,k},d_2=a_{x,j}-a_{y,j}$，设分给 $k$ 的权重为 $x$，那么我们有：  
$$d_1x \ge d_2(1-x)$$  
时可以保证 $x$ 一定不能超过 $y$，注意到 $d_1+d_2$ 是正数，那么 $x$ 的最小值为 $\frac{d_2}{d_1+d_2}$  
此时我们就有了一个 $\mathcal(n^2m)$ 的暴力算法，具体来说，算出每对学生之间的 $d_2$，记为 $d_{i,j}$。然后枚举每个学科 $k$，再枚举每对学生，要求他们都不能超越，即求每对学生之间的 $x$ 的最大值。  

从数据上来看， $nm \le 2\times10^5$ 启示我们分类讨论。  
我们已经解决了 $n$ 较小的情况，当 $n<m$ 即 $n\le \sqrt {2\times10^5}$ 时可以通过。  
考虑 $m<n$ 的时候，这个时候学生大小 $n$ 没有保证，因此枚举所有学生对的方法是不可行的。  
我们依然枚举学科 $k$，并对学生按照该科目排序。  
断言：最大的 $x$ 一定存在于排序后相邻两个学生之间。  
证明：排序后，若存在三个学生 $i,j,k$ 满足 $i>j>k$，和一个 $x$ 使得 $k$ 能超过 $i$，那么 $j$ 一定会是以下两种情况之一：  
1.$j$ 超过了 $i$  
2.$k$ 超过了 $j$  
因此，最**紧**的限制一定存在于排序后相邻两个学生之间。
排序后，相邻的两个学生之间暴力求出最大的 $d_2$ 再用刚刚的公式计算即可。  
值得一提的是：若考虑一个科目时，两个学生出现同分的情况，这两个学生之间的贡献是不需要计算的，而需要将这两个学生合并，具体来说就是对应位置取最大值/最小值。然后再和不同分的学生计算。  
代码还是比较丑的。  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5, P=998244353;
using ll=long long;
struct Frac{
	ll f, m;	
}; 
ll fsp(ll a, ll b=P-2) {
	ll c=1;
	for(; b; b>>=1, a=a*a%P)
		if(b&1) c=c*a%P;
	return c;
}
bool sml(const Frac &a, const Frac &b) {
	return a.f*b.m<b.f*a.m;
}

int n, m, id[N];
vector<vector<int> > a, b, c;
int mxs[500][500];
void solve() {
	scanf("%d %d", &n, &m);
	a.clear(); 
	a.resize(n+5);
	for(int i=1; i<=n; i++) a[i].resize(m+5);
	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			scanf("%d", &a[i][j]);
		}
	
	if(n<m) { //从这里开始就是分类讨论了 /ll 
		for(int i=1; i<=n; i++)
			for(int j=1; j<=n; j++)
				mxs[i][j]=0;
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++) {
				for(int k=1; k<=m; k++) {
					int d=a[i][k]-a[j][k];
					mxs[i][j]=max(mxs[i][j], d);
				}
			}
		}
		for(int k=1; k<=m; k++) {
			Frac mx; mx.f=0, mx.m=1;
			for(int i=1; i<=n; i++) {
				for(int j=1; j<=n; j++) {
					int d=a[j][k]-a[i][k];
					if(d<=0) continue ;
					int mxd=mxs[i][j];
					if(mxd==0) continue ;
					Frac tmp; tmp.f=mxd; tmp.m=d+mxd;
					if(sml(mx, tmp)) {
						mx=tmp;
					}
				}
			}
			printf("%d\n", 1ll*mx.f*fsp(mx.m)%P);
		}
		
	} else {
		for(int k=1; k<=m; k++) {
			c=b=a;
			for(int i=1; i<=n; i++) id[i]=i;
			sort(id+1, id+1+n, [&](int x, int y) {return a[x][k]<a[y][k];});
			int tot=1;
			for(int j=1; j<=m; j++) c[tot][j]=b[tot][j]=a[id[1]][j];
			for(int i=1; i<n; i++) {
				int x=id[i], y=id[i+1];
				if(a[y][k]!=a[x][k]) { 
					++tot;
					for(int j=1; j<=m; j++)
						c[tot][j]=b[tot][j]=a[y][j]; 
				} else 
					for(int j=1; j<=m; j++)
						b[tot][j]=max(b[tot][j], a[y][j]),
						c[tot][j]=min(c[tot][j], a[y][j]);
			}
			Frac mx; mx.f=0, mx.m=1;
			for(int i=1; i<tot; i++) {
				int mxd=0, x=i, y=i+1;	
				int d=b[y][k]-b[x][k];
				
				
				for(int j=1; j<=m; j++) {
					if(j==k) continue ;
					if(b[x][j]-c[y][j]>mxd) mxd=b[x][j]-c[y][j]; 
				}
				if(!mxd) continue ;
				Frac tmp;
				tmp.f=mxd, tmp.m=d+mxd;
				if(sml(mx, tmp)) mx=tmp;
			}
			printf("%d\n", 1ll*mx.f*fsp(mx.m)%P);
		}
	}
}
int main() {
	int T;
	scanf("%d", &T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：Lu_xZ (赞：0)

### 醒餞の鳥 (feat. Feryquitous)  

枚举性质 $k$，如果 $i, j$ 满足 $a_{i, k} > a_{i, k}$，那么 $k$ 分配的系数 $X$ 必须保证 $i, j$ 最坏也只能排名相同（不能 $j$ 在 $i$ 前面）。

贪心的把 $1 - X$ 分配给与 $k$ 不同且 $a_{j, l} - a_{i,l}$ 最大的性质 $l$，则
$$
X \ge \dfrac{a_{j, l} - a_{i,l}}{a_{j, l} - a_{i,l} + a_{i, k} - a_{j, k}}
$$

1. $O(nm^2)$

   将所有人按照性质 $k$ 排序，$a_{i, k}$ 相同的 $i$ 划分到类 $\{a_{i, k}\}$。

   如果 $\{s_1\}, \{s_2\}, \{s_3\}$ 是按序排好的三类人。

   使 $\{s_3\} > \{s_2\}$  的系数为 $X_3$，使 $\{s_2\} > \{s_1\}$  的系数为 $X_2$。

   由于不等号的传递性，我们不再需要考虑 $\{s_1\},\{s_3\}$，需要考虑的偏序对数降到 $O(n)$。

   考虑相邻的两类人 $j, i$，现在要最大化 $X$：
   $$
   X \ge \dfrac{1}{1 + \dfrac{a_{i, k} - a_{j, k}}{\max a_{j, l} - \min a_{i,l}}}
   $$

2. $O(n^2m)$

   考虑枚举 $i, j, k$，$l$ 为等于 $k$ 且满足 $a_{j, l} - a_{i, l}$ 最大。

   预处理每对 $i, j$ 最大和次大 $a_{j, l} - a_{i, l}$ 对应的编号。（$k$ 为最大值时用最大值转移）

   这样预处理和转移都是 $O(n^2m)$ 的。

最后根据数据分治一下，$m < n$ 用算法1，否则用算法2，可以做到 $O(nm\sqrt {nm})$。

```cpp
#include<bits/stdc++.h>
#define eb emplace_back
#define ep emplace
using namespace std;

using ll = long long;
constexpr int P = 998244353;

ll qpow(ll a, int b = P - 2) {
	ll c = 1;
	while(b) {
		if(b & 1) c = c * a % P;
		b >>= 1;
		a = a * a % P;
	}
	return c;
}
struct Q {
	ll a, b;
	Q(ll a = 0, ll b = 1) : a(a), b(b) {}
	ll get() {
		return a * qpow(b) % P;
	}
	bool operator < (const Q& o) const {
		return a * o.b < o.a * b;
	}
};
void solve() {
	int n, m; cin >> n >> m;
	
	vector a(n + 5, vector<int>(m + 5));
	for(int i = 1; i <= n; ++ i) {
		for(int j = 1; j <= m; ++ j) {
			cin >> a[i][j];
		}
	}
	if(m <= n) {
		for(int k = 1; k <= m; ++ k) {
			Q res;
			vector<int> r(n);
			iota(r.begin(), r.end(), 1);
			sort(r.begin(), r.end(), [&](int i, int j) {
				return a[i][k] < a[j][k]; 
			});
			vector b(n + 5, vector<int>(m + 5)); 
			vector c(n + 5, vector<int>(m + 5, 1e9));
			
			int tt = 0;
			vector<int> vec;
			for(int i = 0; i < n; ++ i) {
				int v = a[r[i]][k];
				for(int j = 1; j <= m; ++ j) {
					b[tt][j] = max(b[tt][j], a[r[i]][j]);
					c[tt][j] = min(c[tt][j], a[r[i]][j]);
				}
				while(i + 1 < n && a[r[i + 1]][k] == v) {
					++ i;
					for(int j = 1; j <= m; ++ j) {
						b[tt][j] = max(b[tt][j], a[r[i]][j]);
						c[tt][j] = min(c[tt][j], a[r[i]][j]);
					}
				}
				++ tt;
			}
			for(int i = 1; i < tt; ++ i) {
				int o = 1 + (k == 1);
				for(int t = 1; t <= m; ++ t) {
					if(t == k) continue;
					if(b[i - 1][t] - c[i][t] > b[i - 1][o] - c[i][o]) o = t;
				}
				int d = b[i - 1][o] - c[i][o];
				if(d <= 0) continue;
				res = max(res, Q(d, d + b[i][k] - b[i - 1][k]));
			}
			cout << res.get() << '\n';
		}
	}
	else {
		vector b(n + 5, vector<int>(n + 5)); 
		vector c(n + 5, vector<int>(n + 5));
		
		for(int i = 1; i <= n; ++ i) {
			for(int j = 1; j <= n; ++ j) {
				int x = 1, y = 1;
				for(int t = 1; t <= m; ++ t) {
					if(a[j][t] - a[i][t] >= a[j][x] - a[i][x]) {
						y = x;
						x = t;
					}
					else if(a[j][t] - a[i][t] >= a[j][y] - a[i][y]) y = t;
				}
				b[i][j] = x, c[i][j] = y; 
			}
		}
		for(int k = 1; k <= m; ++ k) {
			Q res;
			for(int i = 1; i <= n; ++ i) {
				Q tmp;
				for(int j = 1; j <= n; ++ j) {
					if(a[i][k] > a[j][k]) {
						int x = b[i][j];
						if(x == k) x = c[i][j];
						int d = a[j][x] - a[i][x];
						if(d <= 0) continue;
						tmp = max(tmp, Q(d, d + a[i][k] - a[j][k]));
					}
				}
				res = max(res, tmp);
			}
			cout << res.get() << '\n';
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int T;
	cin >> T;
	
	while(T --) {
		solve();
	}
	return 0;
}
```

---

