# [USACO24OPEN] Smaller Averages G

## 题目描述

Bessie 有两个长度为 $N$ 的数组（$1\le N\le 500$）。第一个数组的第 $i$ 个元素为 $a_i$（$1\le a_i\le 10^6$），第二个数组的第 $i$ 个元素为 $b_i$（$1\le b_i\le 10^6$）。

Bessie 希望将两个数组均划分为若干**非空**子数组，使得以下条件成立。

1. 每个元素恰属于 $1$ 个子数组。
2. 两个数组划分为相同数量的子数组。令第一个和第二个数组被划分为的子数组数量为 $k$（即，第一个数组被划分为恰好 $k$ 个子数组，第二个数组被划分为恰好 $k$ 个子数组）。
3. 对于所有 $1\le i\le k$，第一个数组左数第 $i$ 个子数组的平均值**小于或等于**第二个数组左数第 $i$ 个子数组的平均值。 

计算她有多少种方式在满足限制的情况下将两个数组划分为非空子数组，对 $10^9+7$ 取模。两种划分方式被认为是不同的，如果子数组的数量不同或是某个元素属于不同的子数组。 

## 说明/提示

### 样例解释 1

两种合法的方法为：

1. 将第一个数组划分为 $[1],[2]$，第二个数组划分为 $[2],[2]$。
2. 将第一个数组划分为 $[1,2]$，第二个数组划分为 $[2,2]$。

### 样例解释 2

三种合法的方法为：

1. 将第一个数组划分为 $[1,3],[2]$，第二个数组划分为 $[2,2],[2]$。
2. 将第一个数组划分为 $[1,3],[2]$，第二个数组划分为 $[2],[2,2]$。
3. 将第一个数组划分为 $[1,3,2]$，第二个数组划分为 $[2,2,2]$。

### 样例解释 3

唯一合法的方法是将第一个数组划分为 $[2],[5,1,3],[2]$，第二个数组划分为 $[2],[1,5],[2,2]$。

### 测试点性质

- 测试点 $5-6$：$N\le 10$。
- 测试点 $7-9$：$N\le 80$。
- 测试点 $10-17$：$N\le 300$。
- 测试点 $18-20$：$N\le 500$。

## 样例 #1

### 输入

```
2
1 2
2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
3
1 3 2
2 2 2```

### 输出

```
3```

## 样例 #3

### 输入

```
5
2 5 1 3 2
2 1 5 2 2```

### 输出

```
1```

## 样例 #4

### 输入

```
7
3 5 2 3 4 4 1
5 3 5 3 3 4 1```

### 输出

```
140```

# 题解

## 作者：EnofTaiPeople (赞：18)

1.9 小时通关金组，你值得拥有！

考虑设状态进行动态规划！

设 $f_{x,y}$ 表示第一个数组划分到 $x$，第二个数组划分到 $y$ 的方案数。

此时如果在上下两个数组同时选定新的区间，这样是 $O(n^4)$ 的，无法通过。

考虑先走第二个数组，即枚举 $x,y$，将所有 $f_{x,p},p<y$ 的区间 $(p,y]$ 的权值提出来，排序，再枚举 $x$ 走到 $z$，用 $(x,z]$ 的权值进行二分即可。

这样的时间复杂度是 $O(n^3\log n)$ 的，无法通过。

实际上，这里的二分和排序都很慢，但也差不多，表现起来就和卡常了一样，不过 USACO 是不会卡常的，所以考虑进一步优化。

我们想到，如果能将这里的二分改成双指针就好了！

但这样会多排序一次，依旧无法接受。

然而，我们发现，这里每次排序的值对于 $x,y$ 来说都是一样的，所以可以对于每个 $x,y$ 再预处理时进行排序，只有 $O(n^2\log n)$ 的复杂度，转移的时候双指针就好。

总时间复杂度 $O(n^3)$，空间复杂度 $O(n^2)$，可以通过：
```cpp
ll mk(int x,int y){
    return LL(1e12)*x/y;
}
using D1=pair<ll,int>;
int n,a[N],b[N],bt,rt,f[505][505];
pair<ll,int>rp[N];
D1 h[505][505];
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z;
    cin>>n;
    for(x=1;x<=n;++x)cin>>a[x],a[x]+=a[x-1];
    for(x=1;x<=n;++x)cin>>b[x],b[x]+=b[x-1];
    for(y=0;y<n;++y){
        for(k=y+1;k<=n;++k)h[y][k-y]={mk(b[k]-b[y],k-y),k};
        sort(h[y]+1,h[y]+n-y+1);
    }
    f[0][0]=1;
    for(x=1;x<=n;++x){
        for(l=0,rt=0;l<x;++l)rp[l]={mk(a[x]-a[l],x-l),l};
        sort(rp,rp+x);
        for(y=0;y<n;++y){
            for(i=1,l=k=0;i<=n-y;++i){
                while(l<x&&rp[l].first<=h[y][i].first)add(k,f[rp[l++].second][y]);
                add(f[x][h[y][i].second],k);
            }
        }
    }
    printf("%d\n",f[n][n]);
    return 0;
}
```

题外话，赛时刚开始为了卡常使用 `long long` 来存浮点数来卡常，欢迎提出 Hack 数据。

---

## 作者：wuhupai (赞：11)

## 思路
首先想到一个 $n^{4}$ 的 dp。$dp_{i,j}$ 代表表示第一个数组划分到 $i$，第二个数组划分到 $j$ 的方案数。观察数据范围，发现这应该是一个 $n^{3}$ 的算法，考虑如何优化。首先把转移方程写出来：

$$dp_{i,j}=\sum_{0\le ii\le i-1,0\le jj\le j-1,\overline{a_{ii+1}\dots a_{i}}\le \overline{b_{jj+1}\dots b_{j}}} dp_{ii,jj}$$

首先枚举 $i$,$j$ 的两维是不可能被优化的，然后考虑枚举 $jj$，然后找到所有满足条件的 $ii$ 的和就可以了。如果我们枚举了 $jj$，就可以求出 $\overline{b_{jj+1}\dots b_{j}}$，此时就是要求满足 $\overline{a_{ii+1}\dots a_{i}}\le \overline{b_{jj+1}\dots b_{j}}$ 的 $ii$ 显然这样可以二分，然后与处理一下即可做到 $n^{3}\log n$。发现瓶颈在二分上，考虑怎样能把二分去掉。发现如果两个平均数都是单调的，那么我们就可以使用双指针了。
## 实现
思路大概想好了，首先我们枚举了 $i,j,jj$，然后第三层循环里面是一个双指针。
![](https://pic.imgdb.cn/item/661fbe430ea9cb140328e4ff.png)

比如当前的 $ii$（红色），$jj$（蓝色），做到了这里，那么这个蓝色就可以和箭头指向的红色的前面（包含这个）产生贡献。而这个是可以用前缀和优化的。然后这样我们的实现也清楚了，就是搞出 $sum[j][i]$ 表示当 $jj=j$ 时，前 $i$ 的 $a$ 的平均数产生的贡献（可以看代码理解一下）然后就可以了。

~~我也不知道我这个大常数选手怎么没被卡~~
```cpp
#include<bits/stdc++.h>
#define for1(i,a,b) for( int i=(a);i<=(b);i++)
#define for2(i,a,b) for( int i=(a);i<(b);i++)
#define for3(i,a,b) for( int i=(a);i>=(b);i--)
#define for4(i,a,b) for( int i=(a);i>(b);i--)
#define mx(a,b) max(a,b)
#define mn(a,b) min(a,b)
#define puba push_back
#define mem(a) memset((a),0,sizeof((a)))
#define int long long
using namespace std;
const int mod=1e9+7;
int n,a[505],b[505],dp[505][505];
int suma[505],sumb[505],sum[505][505];
struct node{
    int l,sum;
}ai[505][505],bi[505][505];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n;
	for1(i,1,n){
		cin>>a[i];
		suma[i]=suma[i-1]+a[i];
	}for1(i,1,n){
		cin>>b[i];
		sumb[i]=sumb[i-1]+b[i];
	}
    for1(j,1,n){
        for1(i,1,j){
            ai[j][i].sum=(suma[j]-suma[i-1]);
            bi[j][i].sum=(sumb[j]-sumb[i-1]);
            ai[j][i].l=bi[j][i].l=i;
        }
    }
    for1(i,1,n){
        for1(j,1,i){
            for1(k,1,i-1){
                if(ai[i][k].sum*(i-ai[i][k+1].l+1)>ai[i][k+1].sum*(i-ai[i][k].l+1)){
                    swap(ai[i][k],ai[i][k+1]);
                }if(bi[i][k].sum*(i-bi[i][k+1].l+1)>bi[i][k+1].sum*(i-bi[i][k].l+1)){
                    swap(bi[i][k],bi[i][k+1]);
                }
            }//最低级的冒泡排(懒)
        }//还有一个原因是这里为了保证精度需要移项，cmp函数不太好写
    }
	dp[0][0]=1;
	for1(i,1,n){
        for1(j,1,n){
            for1(k,1,i){
                sum[j][k]=(sum[j][k-1]+dp[ai[i][k].l-1][j-1])%mod;
            }//搞出sum
        }
		for1(j,1,n){
			int ii=1;
            for1(jj,1,j){
                while(ai[i][ii].sum*(j-bi[j][jj].l+1)<=bi[j][jj].sum*(i-ai[i][ii].l+1)&&ii<=i) ii++;
                dp[i][j]=(dp[i][j]+sum[bi[j][jj].l][ii-1])%mod;//双指针出的是第一个不满足要求的，所以是ii-1
            }
		}
	}
	cout<<dp[n][n];
	
	return 0;
}
```

---

## 作者：LinkCatTree (赞：5)

首先设计一个朴素的 dp。$f_{i,j}$ 表示 $a_{1 \ldots i}$ 和 $b_{1 \ldots j}$ 同时划分成满足条件的若干段的方案数。一个显然的转移方程是：

$$f_{i,j}=\sum_{p,q}f_{p-1,q-1} (\text{average of }a_{p \ldots i} \leq \text{average of }b_{q \ldots j})$$

其中边界值 $f_{0,0}=1$。如果直接枚举 $p,q$ 则时间复杂度 $\mathcal{O}(n^4)$ 无法接受，考虑进行优化。

发现直接优化比较困难，我们不妨改变一下枚举的方式，枚举 $i$ 和 $q$，再枚举 $p$ 和 $j$，用 $f_{p,q}$ 去更新 $f_{i,j}$，这时候就可以使用双指针优化。具体的：对于 $i$ 和 $q$，可以预处理出所有 $a_{p \ldots i}(p \leq i)$ 的平均值和所有 $a_{q \ldots j}(q \leq j)$ 的平均值，用双指针来维护。

至于为什么要采用这种枚举方式，是因为这样用 $f_{p,q}$ 去进行更新时，被枚举的 $q$ 已经确定，才可以使用前缀和优化。如果采用枚举 $i,j$ 的方式，则转移过来的 $f_{p,q}$ 两维均不确定，较难维护。同理，枚举 $p,j$ 也是可以的，这里就采用枚举 $i,q$ 的方法。

这样子，枚举 $i$、枚举 $q$、枚举 $j,p$，dp 部分复杂度 $\mathcal{O}(n^3)$，预处理 $\mathcal{O}(n^2 \log n)$，可以接受。

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef double db;
typedef pair<db,int> pdi;
const int N=505,mod=1e9+7;
int n,a[N],b[N];
vector<pdi> ave[N];
int f[N][N];

int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++) {
		int sum=0;
		for(int j=i;j<=n;j++) {
			sum+=b[j];
			ave[i].emplace_back(make_pair((db)sum/(j-i+1),j));
		}
		sort(ave[i].begin(),ave[i].end());
	}
	f[0][0]=1LL;
	for(int i=1;i<=n;i++) {
		int sum=0; vector<pdi> res;
		for(int j=i;j>=1;j--) {
			sum+=a[j];
			res.emplace_back(make_pair((db)sum/(i-j+1),j));
		}
		sort(res.begin(),res.end());
		for(int j=1;j<=n;j++) {
			auto p=res.begin();
			int tmp=0;
			for(auto [val,q]:ave[j]) {
				while(p!=res.end()&&(p->first)<=val) tmp=(tmp+f[(p->second)-1][j-1])%mod,p++;
				f[i][q]=(f[i][q]+tmp)%mod;
			}
		}
	}
	printf("%lld\n",f[n][n]);
	return 0;
} 
```

---

## 作者：Nangu (赞：4)

先讲暴力。

设 $f_{i, j}$ 为 $a$ 的第 $i$ 位和 $b$ 的第 $j$ 位相匹配的方案数，则有 $f_{i, j}=\sum f_{k, l}$，其中 $k$ 和 $l$ 满足 $\frac{sa_i-sa_k}{i-k}\le\frac{sb_j-sb_l}{j-l}$。由于除法有精度的问题，将其转化为 $(sa_i-sa_k)\times(j-l)\le (sb_j-sb_l)\times(i-k)$。暴力枚举 $i, j,k,l$ 即可。
```cpp
signed main()
{
	cin>>n;
	F(i, 1, n) cin>>a[i], a[i]+=a[i-1];
	F(i, 1, n) cin>>b[i], b[i]+=b[i-1];
	f[0][0]=1;
	F(i, 1, n) F(j, 1, n)
		F(k, 0, i-1) F(l, 0, j-1)
			if(f[k][l] && (a[i]-a[k])*(j-l)<=(b[j]-b[l])*(i-k))
				pls(f[i][j], f[k][l]);
	cout<<f[n][n]<<'\n';
 	return 0;
}
```

考虑优化这个暴力。

这个暴力慢在了我们需要依次枚举四个变量来求值，因此复杂度为 $O(n^4)$。观察到若复杂度降为 $O(n^3)$ 就足以通过此题，因此如果我们能只枚举三个变量就能求出答案就好了。

因此顺水推舟地，想到单调性优化。若确定 $i,j$，若 $l$ 的取值能随 $k$ 增大而增大/减小就可以了。但原数据并不保证这一点。**因此，在 $i, j$ 不变时，我们可以对每一对二元组 $(k,i)$ 和 $(l,j)$ 进行排序，满足二元组之间平均值单调不降，并对排序完的 $(k,i)$ 依次求解**， 这样就满足单调性。

具体做法：枚举 $i,j,k$，并令指针 $l$ 随着 $k$ 增大而右移，维护 $f$ 数组和 $f$ 数组的前缀和即可。
```cpp
#include<bits/stdc++.h>
#define F(i, j, k) for(int i=(j), ENDD=(k); i<=ENDD; ++i)
#define R(i, j, k) for(int i=(j), ENDD=(k); i>=ENDD; --i)
#define int long long
#define md(x) ((x)<mod?(x):(x)-mod)
using namespace std;
const int N=507, mod=1e9+7;
int n, a[N], b[N], f[N][N], s[N][N], pa[N][N], pb[N][N], R;

signed main()
{
    cin>>n;
    F(i, 1, n) cin>>a[i], a[i]+=a[i-1];
    F(i, 1, n) cin>>b[i], b[i]+=b[i-1];
    F(i, 1, n){
        iota(pa[i]+1, pa[i]+i+1, 0);
        sort(pa[i]+1, pa[i]+i+1, [=](int x, int y){
            return (a[i]-a[x])*(i-y)>(a[i]-a[y])*(i-x);
        });
        iota(pb[i]+1, pb[i]+i+1, 0);
        sort(pb[i]+1, pb[i]+i+1, [=](int x, int y){
            return (b[i]-b[x])*(i-y)>(b[i]-b[y])*(i-x);
        });
    }
	f[0][0]=1;
    F(j, 1, n){
        F(i, 0, n){
            s[i][0]=0;
            F(k, 1, j) s[i][k]=md(s[i][k-1]+f[i][pb[j][k]]);
        }
        F(i, 1, n){
            int pos=0;
            F(kk, 1, i){
                int k=pa[i][kk];
                while(pos<j && (a[i]-a[k])*(j-pb[j][pos+1])<=(b[j]-b[pb[j][pos+1]])*(i-k))
                    ++pos;
                f[i][j]=md(f[i][j]+s[k][pos]);
            }
        }
    }
    cout<<f[n][n]<<endl;
    return 0;
}
```

---

## 作者：Claire0918 (赞：3)

我们记 $S(l, r) = \dfrac{\sum_{i = l}^{r} a_i}{r - l + 1}, T(l, r) = \dfrac{\sum_{i = l}^{r} b_i}{r - l + 1}$。

考虑 DP。设 $f_{i, j}$ 表示 $\{a_i\}$ 长为 $i$ 的前缀，$\{b_i\}$ 长为 $j$ 的前缀的方案数。我们有暴力的转移 $\displaystyle f_{i, j} = \sum_{i' = 1}^{i} \sum_{j' = 1}^{j} f_{i' - 1, j'- 1} \times [S(i', i) \leq T(j', j)]$。时间复杂度为 $\mathcal{O}(n^4)$ 不能通过。

$\mathcal{O}(n^2)$ 的状态难以优化，我们从转移入手。化简转移式
$$
\begin{aligned}
f_{i, j}
&= \sum_{i' = 1}^{i} \sum_{j' = 1}^{j} f_{i' - 1, j' - 1} \times [S(i', i) \leq T(j', j)]\\
&= \sum_{j' = 1}^{j} \sum_{i' \in [1, i], S(i', i) \leq T(j', j)} f_{i' - 1, j' - 1}\\
\end{aligned}
$$
只要我们能够将原序列的顺序进行一定的重排，使得合法的 $i'$ 是一段前缀，那么就可以使用前缀和优化掉一维，达到转移过程 $\mathcal{O}(n^3)$ 的复杂度。

我们发现在 $(i, j)$ 确定时，我们仅关心 $\{a_i\}$ 中以 $i$ 结尾的区间的平均数和 $\{b_i\}$ 中以 $j$ 结尾的区间的平均数。不妨设 $s_{i, j} = S(j, i)$。对于每一个 $i$，将 $s_i$ 升序排序。那么，对于确定的 $j'$，$T(j', j)$ 就是确定的，此时使得 $S(i', i) = s_{i, i'} \leq T(j', j)$ 的 $s_{i, i'}$ 就是 $s_i$ 的一段前缀。二分前缀右端点，可以做到 $\mathcal{O}(n^3\log n)$ 的复杂度，接近通过但仍然无法通过。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 500 + 10, mod = 1e9 + 7;

int n;
int a[maxn], b[maxn], f[maxn][maxn], pre[maxn][maxn];
pair<int, int> suma[maxn][maxn], sumb[maxn][maxn];

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        a[i] += a[i - 1];
    }
    for (int i = 1; i <= n; i++){
        scanf("%d", &b[i]);
        b[i] += b[i - 1];
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= i; j++){
            suma[i][j] = make_pair(a[i] - a[j - 1], j);
            sumb[i][j] = make_pair(b[i] - b[j - 1], j);
        }
    }
    for (int i = 1; i <= n; i++){
        const auto cmp = [i](pair<int, int> x, pair<int, int> y){return (long long)x.first * (i - y.second + 1) < (long long)y.first * (i - x.second + 1);};
        sort(suma[i] + 1, suma[i] + i + 1, cmp);
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            for (int k = 1; k <= i; k++){
                pre[j][k] = mod_add(pre[j][k - 1], f[suma[i][k].second - 1][j - 1]);
            }
        }
        for (int j = 1; j <= n; j++){
            for (int k = 1; k <= j; k++){
                int l = 0, r = i;
                while (l < r){
                    const int mid = l + r + 1 >> 1;
                    if ((long long)suma[i][mid].first * (j - sumb[j][k].second + 1) <= (long long)sumb[j][k].first * (i - suma[i][mid].second + 1)){
                        l = mid;
                    }else{
                        r = mid - 1;
                    }
                }
                f[i][j] = mod_add(f[i][j], pre[sumb[j][k].second][l]);
            }
        }
    }
    printf("%d\n", f[n][n]);

return 0;
}
```

事实上，有多种方式可以使得在枚举 $j'$ 时访问的前缀和空间是连续的，优化了常数，可以艰难通过。

另一种方式是设 $t_{i, j} = T(j, i)$，将 $t_i$ 也排序。我们注意到注意到随 $j'$ 上升，$t_{j, j'}$ 单调不降，从而满足 $s_{i, i'} \leq t_{j, j'}$ 的 $s_{i}$ 中前缀右端点单调不降，考虑双指针维护右端点，可以做到 $\mathcal{O}(n^3)$ 的复杂度，可以通过。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 500 + 10, mod = 1e9 + 7;

int n;
int a[maxn], b[maxn], f[maxn][maxn], pre[maxn][maxn];
pair<int, int> suma[maxn][maxn], sumb[maxn][maxn];

template<typename Tp_x, typename Tp_y>
inline int mod_add(Tp_x x, Tp_y y){
    x += y;
    return x >= mod ? x -= mod : x;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        a[i] += a[i - 1];
    }
    for (int i = 1; i <= n; i++){
        scanf("%d", &b[i]);
        b[i] += b[i - 1];
    }
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= i; j++){
            suma[i][j] = make_pair(a[i] - a[j - 1], j);
            sumb[i][j] = make_pair(b[i] - b[j - 1], j);
        }
    }
    for (int i = 1; i <= n; i++){
        const auto cmp = [i](pair<int, int> x, pair<int, int> y){return (long long)x.first * (i - y.second + 1) < (long long)y.first * (i - x.second + 1);};
        sort(suma[i] + 1, suma[i] + i + 1, cmp);
        sort(sumb[i] + 1, sumb[i] + i + 1, cmp);
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            for (int k = 1; k <= i; k++){
                pre[j][k] = mod_add(pre[j][k - 1], f[suma[i][k].second - 1][j - 1]);
            }
        }
        for (int j = 1; j <= n; j++){
            int p = 1;  
            for (int k = 1; k <= j; k++){
                while (p <= i && (long long)suma[i][p].first * (j - sumb[j][k].second + 1) <= (long long)sumb[j][k].first * (i - suma[i][p].second + 1)){
                    p++;
                }
                f[i][j] = mod_add(f[i][j], pre[sumb[j][k].second][p - 1]);
            }
        }
    }
    printf("%d\n", f[n][n]);

return 0;
}
```

---

## 作者：lnw143 (赞：3)

## [Smaller Averages](https://www.luogu.com.cn/problem/P10282) 题解

- $N \le 10$

  暴力即可。

- $N \le 80$

  考虑 DP，设 $f_{i,j}$ 为 $a$ 数组中划分到 $i$，$b$ 数组中划分到 $j$ 时的合法方案数。

  显然划分组数不重要，因此有转移式

  $$
  f_{i,j}\gets\sum_{i' \in [0,i)} \sum_{j' \in [0,j)} [\overline{a_{i'+1,i}} \le \overline{b_{j'+1,j}}]f_{i',j'}
  $$

  于是我们得到了一个 $O(N ^ 4)$ 的 DP。

- $N \le 300$

  考虑加速 DP

  我们发现如果固定 $i$，那么以 $\overline{a_{i'+1,i}}$ 为关键字对 $i'$ 进行排序，并处理前缀和后，即可对于一个 $j'$ 通过二分用 $O(\log N)$ 的时间求出所有合法的 $\sum f_{i',j'}$。

  时间复杂度 $O(N^3 \log N)$。

- $N \le 500$

  我们发现对于 $j$，同样可以预处理出 $j'$ 的顺序，因此枚举 $j'$ 时 $i'$ 单调不减。

  时间复杂度 $O(N^3)$。

AC code:

```cpp
#include<cstdio>
#include<algorithm>
using ll = long long;
using namespace std;
const int N = 5e2, P = 1e9 + 7;
int n,a[N + 2],b[N + 2],f[N + 2][N + 2],g[N + 2][N + 2],u[N + 2],v[N + 2][N + 2];
ll su[N + 2],sv[N + 2];
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]),su[i]=su[i-1]+a[i];
	for(int i=1; i<=n; ++i)
		scanf("%d",&b[i]),sv[i]=sv[i-1]+b[i];
	f[0][0]=1;
	for(int i=1; i<=n; ++i) {
		for(int j=0; j<i; ++j)
			v[i][j]=j;
		sort(v[i],v[i]+i,[&](int x,int y) {
			return (sv[i]-sv[x])*(i-y)<(sv[i]-sv[y])*(i-x);
		});
	}
	for(int i=1; i<=n; ++i) {
		for(int j=0; j<i; ++j)
			u[j]=j;
		sort(u,u+i,[&](int x,int y) {
			return (su[i]-su[x])*(i-y)<(su[i]-su[y])*(i-x);
		});
		for(int j=1; j<=n; ++j) {
			g[j-1][0]=0;
			for(int k=1; k<=i; ++k) {
				g[j-1][k]=g[j-1][k-1]+f[u[k-1]][j-1];
				if(g[j-1][k]>=P) g[j-1][k]-=P;
			}
			for(int k=0,l=0; k<j; ++k) {
				while(l<i&&(su[i]-su[u[l]])*(j-v[j][k])<=(sv[j]-sv[v[j][k]])*(i-u[l])) ++l;
				f[i][j]+=g[v[j][k]][l];
				if(f[i][j]>=P) f[i][j]-=P;
			}
		}
	}
	printf("%d",f[n][n]);
	return 0;
}
```

---

## 作者：do_it_tomorrow (赞：2)

不得不感叹 USACO 的质量真的高，从来没有见过怎么猎奇的 DP 题。

暴力的，考虑设 $f_{x,y}$ 表示第一个数组选择到了 $x$，第二个数组选择到了 $y$ 的方案数。

显然可以枚举上一个在 $1,2$ 两个数组中位置，于是有 $O(n^4)$ 的 DP。

令 $A(x,y)$ 表示 $a[x,y]$ 的平均数，而 $B(x,y)$ 表示 $b[x,y]$ 的平均数，那么转移为：

$$f_{x,y}=\sum\limits_{i=1}^{x-1}\sum\limits_{j=1}^{y-1} f_{i,j}\times[A(i,x)\le B(j,y)]$$

显然 $x,y$ 是无法优化的，考虑把转移的时间复杂度降下来：

$$f_{x,y}=\sum\limits_{i=1}^{x-1}\sum\limits_{j\in[1,j]\wedge A(i,x)\le B(j,y)} f_{i,j}$$

那么如果我们可以对 $\forall p\in[1,y)$ 的 $f_{i,p}$ 按照 $B(p,y)$ 的顺序降序排列然后再写一个前缀和优化，那么就可以把时间复杂度降低到 $O(n^3\log n)$。

对于每一次询问我们找出满足 $B$ 值比钦定区间 $A$ 小的最大的 $p$ 然后转移过来。

有人告诉我们，这并不是正解。

观察可以发现主要的冲突在于二分的 $\log$ 把 $O(n^3)$ 的复杂度吃满了而且搞成了 $O(n^3\log V)$，考虑把这个东西搞掉，一个很自然的想法就是写双指针。

但是需要写双指针就需要 $A$ 的值同时也是递增的，那么通过观察转移其实不会遇到这一维，所以对 $a$ 数组也进行类似的操作。

于是就可以用双指针维护转移，时间复杂度为 $O(n^3)$。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int N=505,mod=1e9+7;
int n,a[N],b[N],f[N][N];
struct node{double v;int id;};
bool cmp(node a,node b){return a.v<b.v;}
vector<node> A[N],B[N];
int Mod(int x){return x>=mod?x-mod:x;}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i],a[i]+=a[i-1];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i],b[i]+=b[i-1];
	}
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			B[i].push_back({1.0*(b[j]-b[i-1])/(j-i+1),j});
		}
		for(int j=i;j>=1;j--){
			A[i].push_back({1.0*(a[i]-a[j-1])/(i-j+1),j});
		}
		sort(A[i].begin(),A[i].end(),cmp);
		sort(B[i].begin(),B[i].end(),cmp);
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int s=0,p=0;
			for(node x:B[j]){
				while(p!=A[i].size()&&A[i][p].v<=x.v){
					s=Mod(s+f[A[i][p++].id-1][j-1]);
				}
				f[i][x.id]=Mod(f[i][x.id]+s);
			}
		}
	}
	cout<<f[n][n]<<'\n';
	return 0;
}
```

---

## 作者：cff_0102 (赞：2)

考虑 dp。设 $dp_{an,bn}$ 为两个数组分别剩下前 $an,bn$ 个数时的方案数，可以暴力转移，即每次枚举这一组两个数组分别存几个数，或者枚举下一组时剩下前几个数。显然时间复杂度是 $O(n^4)$，不能通过。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[505],b[505];
int sa[505],sb[505];
int dp[505][505];
const int mod=1e9+7;
int dfs(int an,int bn){
	if(dp[an][bn]!=-1)return dp[an][bn];
	int ans=(1.0*sa[an]/an<=1.0*sb[bn]/bn);
	for(int i=an-1;i>0;i--){
		for(int j=bn-1;j>0;j--){
			if((1.0*sa[an]-sa[i])/(an-i)<=(1.0*sb[bn]-sb[j])/(bn-j))ans+=dfs(i,j);
			ans%=mod; 
		}
	}
	return dp[an][bn]=ans;
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	memset(dp,-1,sizeof dp);
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)sa[i]=sa[i-1]+a[i],sb[i]=sb[i-1]+b[i];
	cout<<dfs(n,n);
	return 0;
}
```

考虑优化。注意到转移时我们枚举每一个可能的 $i,j$ 并把 $i$ 和 $j$ 的“一个属性”（即一段的平均值）相比，如果符合条件就能转移。注意到 $i$ 的这个“属性”与 $bn$ 没有关系，$j$ 的这个“属性”也和 $an$ 没有关系，那么就可以在不枚举 $bn$ 和 $j$ 的情况下计算出每个 $i$ 和 $an$ 的“属性”，反之类似。

但是这样算出来又有什么用呢？最后不还是要四重循环枚举 $an,bn,i,j$ 吗？

既然已经把每个“属性”提前算出来了，并且转移的时候是当 $i$ 的这个“属性”小于 $j$ 的这个“属性”就能转移，不难想到排序后双指针，这样就能把转移从 $O(n^2)$ 变成 $O(n)$ 的。

需要注意的是，此处还需要同时维护一个 $dp$ 数组的“前缀”和，方便转移，具体可以参照代码里的注释。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[505],b[505];
int sa[505],sb[505];
pair<double,int>aa[505][505],bb[505][505];
int dp[505][505];
int sdp[505][505];
const int mod=1e9+7;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	int n;cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++)cin>>b[i];
	for(int i=1;i<=n;i++)sa[i]=sa[i-1]+a[i],sb[i]=sb[i-1]+b[i];
	for(int an=1;an<=n;an++){
		for(int i=an-1;i>0;i--){
			aa[an][i]={(1.0*sa[an]-sa[i])/(an-i),i};
		}
		sort(aa[an]+1,aa[an]+an);
	}
	for(int bn=1;bn<=n;bn++){
		for(int j=bn-1;j>0;j--){
			bb[bn][j]={(1.0*sb[bn]-sb[j])/(bn-j),j};
		}
		sort(bb[bn]+1,bb[bn]+bn);
	}
	dp[0][0]=1;
	for(int an=1;an<=n;an++){
		for(int bn=1;bn<=n;bn++){
			dp[an][bn]=(1.0*sa[an]/an<=1.0*sb[bn]/bn);
			for(int k=1;k<=n;k++){
				sdp[k][bn]=sdp[k-1][bn]+dp[aa[an][k].second][bn];
				sdp[k][bn]%=mod;
			}
		}
		for(int bn=1;bn<=n;bn++){
			int i=1;
			for(int j=1;j<bn;j++){
				while(i<an&&aa[an][i].first<=bb[bn][j].first)i++;
				//此时 i 是第一个不满足 aa[i].f<=bb[j].f 的 i
				//1 - i-1 就都满足
				//dp[an][bn] 要加上 sum[k=1,i-1]dp[aa[an][k].s][bb[bn][j].s]，即 sdp[i-1][bb[bn][j].s]
				dp[an][bn]+=sdp[i-1][bb[bn][j].second];
				dp[an][bn]%=mod;
			}
		}
	}
	cout<<dp[n][n];
	return 0;
}
```

---

## 作者：onlycre (赞：2)

先列出暴力方程吧：

$$f_{i,j}=\sum _{p<i,q<j,\frac{sa_i-sa_p}{i-p}\le \frac{sb_j-sb_q}{j-q} } f_{p,q}$$

也就是说，转移成立需要满足三个偏序关系。我们考虑着手于第三个条件，在 $i$ 与 $j$ 固定的情况下，我们可以分别对他们建立转移候选序列，也就是将 $p$ 与 $q$ 分别放进两个数组，使得这两个序列都是单调的，这里的单调指的是平均值的单调。

这个时候我们再在 $j$ 对应的序列里枚举 $q$，由于两个序列的单调性，显然合法的 $p$ 在 $i$ 对应的序列里是一段前缀，那么可以双指针然后前缀和优化。

我们在 dp 前先将所有的候选序列预处理出来，这样总复杂度就是 $O(n^3)$

赛时代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring> 
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define rpe(i,x) for(int i=_he[x];i;i=_ne[i])
#define lb(x) (x&(-x))
using namespace std;
typedef long long LL;
typedef pair<int,int>pii;
typedef pair<double,int>pdi;
const int N=4e5+10,MOD=1e9+7;

int n,a[505],b[505],f[505][505],d[505][505],u[505][505],g[505][505];
LL sa[505],sb[505];

int da[505],db[505],tmp;
bool cmp(int x,int y){return (sa[tmp]-sa[x])*(tmp-y)<(sa[tmp]-sa[y])*(tmp-x);}
bool cmp2(int x,int y){return (sb[tmp]-sb[x])*(tmp-y)<(sb[tmp]-sb[y])*(tmp-x);}
int main()
{
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]),sa[i]=sa[i-1]+a[i];
	rep(i,1,n)scanf("%d",&b[i]),sb[i]=sb[i-1]+b[i];
	
	{
		rep(i,1,n)
		{
			rep(p,0,i-1)u[i][p+1]=p;
			tmp=i;
			sort(u[i]+1,u[i]+1+i,cmp);
		}
		rep(j,1,n)
		{
			rep(q,0,j-1)g[j][q+1]=q;
			tmp=j;
			sort(g[j]+1,g[j]+1+j,cmp2);
		}
	}
	
	f[0][0]=1;
	rep(i,1,n)
	{
		rep(p,1,i)da[p]=u[i][p];
		rep(p,1,i)d[p][0]=d[p-1][0]+(da[p]==0);
		rep(j,1,n)
		{
			rep(q,1,j)db[q]=g[j][q];
			for(int p=0,q=1;q<=j;q++)
			{
				while(p<i&&(sa[i]-sa[da[p+1]])*(j-db[q])<=(sb[j]-sb[db[q]])*(i-da[p+1]))p++;
				(f[i][j]+=d[p][db[q]])%=MOD;
			}
			
			rep(p,1,i)d[p][j]=(d[p-1][j]+f[da[p]][j])%MOD;
		}
	}
	printf("%d\n",(f[n][n]+MOD)%MOD);
	return 0;
}
```

---

## 作者：huhangqi (赞：1)

其实还是比较水的优化，但是太久没有写动态规划了，打比赛时没有场切，遂来写题解。

首先很容易设计状态 $dp_{i,j}$ 表示数组 $a$ 选择了前面 $i$ 个，数组 $b$ 选择了前面 $j$ 个的方案数。

那么直接暴力转移，时间复杂度为 $O(n^4)$。

考虑如何优化。

式子过于简洁，无法使用各种乱七八糟的优化方式，唯一突破口在于第一个数组的平均值小于等于第二组这一个条件。

那么就能够想到对于一个第二组的区间，可以选择的第一组区间是固定的，并且随着第二组区间平均数增大，第一组可选择区间数量也随之变多。

那么就可以进一步想到可以提前按照平均数进行排序，再通过这些值的和去更新答案。

由于我们的转移需要顺序，我们先按照右端点分组，然后再按照平均数进行排序，然后处理出按照这一顺序排序后上一步的值，方便转移。之后，我们去枚举第二段的右端点，然后同样排序，枚举可以选择的区间，用双指针添加第一组答案，最后即可得到结果。

最终时间复杂度即为 $O(n^3)$，可以通过。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,a[505],b[505],dp[505][505],pre[505][505];
pair<double,int> ea[505][505],eb[505][505];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],a[i]+=a[i-1];
	for(int i=1;i<=n;i++)cin>>b[i],b[i]+=b[i-1];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			ea[i][j]={1.0*(a[i]-a[j-1])/(i-j+1),j};
			eb[i][j]={1.0*(b[i]-b[j-1])/(i-j+1),j};
		}
		sort(ea[i]+1,ea[i]+i+1),sort(eb[i]+1,eb[i]+i+1);
	}
	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=i;k++){
				pre[j][k]=pre[j][k-1]+dp[ea[i][k].second-1][j-1];
			}
		}
		for(int j=1;j<=n;j++){
			int w=1;
			for(int k=1;k<=j;k++){
				while(w<=i&&ea[i][w].first<=eb[j][k].first)w++;
				dp[i][j]+=pre[eb[j][k].second][w-1];
				dp[i][j]%=mod;
			}
		}
	}
	cout<<dp[n][n];
	return 0;
}
``````

---

## 作者：qwer6 (赞：0)

[Link](https://www.luogu.com.cn/problem/P10282)

## 1. Description

给定两个数组 $a,b$，要求将两个数组划分成数量相同的几个部分，且对应部分 $b$ 的平均数不小于 $a$ 的平均数。

## 2. Solution

显然的动态规划题，我们考虑定义状态 $f_{i,j}$ 表示合法地划分 $a$ 数组的 $1\sim i$ 项与 $b$ 数组的 $1\sim j$ 项的方案数，转移方程同样显然，$f_{i,j}=\sum_{x=1}^{x\le i}\sum_{y=1}^{y\le j} f_{x-1,y-1}[\overline a_{x,i}\le \overline b_{y,j}]$，其中 $\overline a_{x,i}$ 表示 $a$ 数组 $[x,i]$ 这个区间的平均数，$\overline b_{y,j}$ 同理。

实际实现可以使用刷表法，时间复杂度为 $O(n^4)$，无法通过此题。

```c++
for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
        for(int x=i;x<=n;x++){
            for(int y=j;y<=n;y++){
                //a[i] 此时为前缀和，b[i] 同理
                if((a[x]-a[i-1])*(y-j+1)<=(b[y]-b[j-1])*(x-i+1))
                    dp[x][y]=add(dp[x][y],dp[i-1][j-1]);
            }
        } 
    }
}
```

考虑优化刷表法，我们想到枚举出 $i,j$ 和将要转移的 $y$，此时 $\overline b_{y,j}$ 固定，很容易想到我们预处理所有以 $i$ 为左端点的区间的平均值，然后从大到小排序，二分求解，时间复杂度为 $O(n^3\log n)$，一个很接近通过的时间复杂度，但是仍然不能通过。

继续优化，尝试不要二分，这个时候我们尝试改变一下上面的预处理方式，分别预处理出 $a$ 数组所有以 $i$ 为**右端点**的区间的平均值和 $b$ 数组所有以 $j$ 为**左端点**的区间的平均值并且排序，此时我们枚举 $i,j$ 和以 $i$ 为右端点的区间的左端点 $x$ 与以 $j$ 为左端点的区间的右端点 $y$，从 $f_{x-1,j-1}$ 转移到 $f_{i,y}$，由于经过排序，$\overline a_{x,i},\overline b_{j,y}$ 单调不减，可以直接双指针实现，具体的，我们通过双指针找到最后一个平均数小于 $b_{j,y}$ 的右端点，同时累加 $f_{x-1,j-1}$ 的值即可。

## 3. Code

```c++
/*by qwer6*/
/*略去缺省源和快读快写*/
const int N=505,mod=1e9+7;
int n;
int a[N],b[N],f[N][N];
struct Node{
	int sum,len,l;
	bool operator <(const Node &a)const{
		return 1ll*sum*a.len<1ll*a.sum*len;//防止卡精度，化除为乘
	}
	bool operator ==(const Node &a)const{
		return 1ll*sum*a.len==1ll*a.sum*len;
	}
	bool operator <=(const Node &a)const{
		return *this<a||*this==a;
	}
};
vector<Node>c[N],d[N];
int add(int x,int y){
	x+=y;
	return x>=mod?x-mod:x;
}
signed main(){
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++)read(b[i]);
	for(int i=1;i<=n;i++){
		for(int j=i,suma=0,sumb=0;j>=1;j--){
			suma+=a[i],sumb+=b[i];
			c[i].push_back({suma,i-j+1,j});
			d[j].push_back({sumb,i-j+1,i});
		}
	}
	for(int i=1;i<=n;i++){
		sort(c[i].begin(),c[i].end());
		sort(d[i].begin(),d[i].end());
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int w=0,sum=0;
			for(Node now:d[j]){
				while(w<i&&c[i][w]<=now){
					sum=add(sum,f[c[i][w].l-1][j-1]);
					w++;
				}
				f[i][now.l]=add(f[i][now.l],sum);
			}
		}
	}
	write(f[n][n]);
}
```

---

## 作者：Helenty (赞：0)

很明显我们可以设 $f_{i,j}$ 表示分别划了 $i,j$ 个的方案数，就可以做到 $O(n^4)$，考虑怎么优化。

想到对于 $b$ 的区间产生的平均数，只有 $O(n^2)$ 种，那么我们做 $\dfrac{sum_r-sum_l}{r-l}\leq x$ 的 $sum_r-rx\leq suml-lx$ 处理就可以知道 $f_{*,j}\rightarrow f_{*,k}$ 的转移出现在啥地方了，我们对每个 $j,k$ 做此二维偏序转移可以做到 $O(n^3\log n)$ 了。

最后正解是考虑分别对 $a$ 和 $b$ 的每个右端点 $r$ 的区间 $(i,r)$ 按平均值大小排序，这样我们 $f_{i,j}\rightarrow f_{r1,r2}$ 时，按照 $(i,r1)$ 的排序一个一个转移去找 $(j,r2)$ 排序合法的前缀即可，这个使用双指针就可以做到 $O(n^3)$ 了。

---

