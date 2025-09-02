# Game With Triangles

## 题目描述

即使小 John 也需要钱买房。但他最近失业了，现在该如何赚钱呢？当然是玩能获得金钱奖励的游戏！不过可能不是你想的那种游戏。平面上有 $n + m$ 个互不相同的点 $(a_1, 0), (a_2, 0), \ldots, (a_n, 0), (b_1, 2), (b_2, 2), \ldots, (b_m, 2)$。初始时你的得分为 $0$。你可以通过以下操作增加得分：

- 选择三个不共线的不同点；
- 将得分增加这三个点形成三角形的面积；
- 从平面中删除这三个点。

![](https://espresso.codeforces.com/5f6a73286fffbc2708f1d388ed58ca5bc0d69d23.png) 游戏示例，其中执行了两次操作。设 $k_{\max}$ 表示可执行操作的最大次数。例如若无法执行任何操作，则 $k_{\max} = 0$。另外定义 $f(k)$ 为恰好执行 $k$ 次操作时可能达到的最大得分。此处 $f(k)$ 对所有满足 $0 \le k \le k_{\max}$ 的整数 $k$ 均有定义。

请找出 $k_{\max}$ 的值，并分别计算所有 $x=1,2,\ldots,k_{\max}$ 对应的 $f(x)$ 值。

## 说明/提示

在第一个测试用例中，共有 $1+3=4$ 个点：$(0,0)$、$(0,2)$、$(1,2)$、$(-1,2)$。

可以证明无法执行两次或更多操作。此时 $k_{\max} = 1$，只需输出 $f(1)$ 的值。选择 $(0,0)$、$(-1,2)$ 和 $(1,2)$ 作为三角形的三个顶点。操作后得分增加该三角形的面积 $2$，随后这三个点被删除。可以证明单次操作后的最大得分为 $2$，因此 $f(1) = 2$。

第五个测试用例中共有 $8+2=10$ 个点。可以证明无法执行三次或更多操作。此时 $k_{\max} = 2$，需要输出 $f(1)$ 和 $f(2)$ 的值。

要最大化单次操作的得分，可选择三点 $(198\,872\,582,0)$、$(-1\,000\,000\,000,2)$ 和 $(1\,000\,000\,000,2)$。操作后这三个点被删除。可以证明此时最大得分为 $2\,000\,000\,000$，因此 $f(1) = 2\,000\,000\,000$。

要最大化两次操作的总得分，可按以下步骤执行：
1. 选择三点 $(-509\,489\,796,0)$、$(553\,177\,666,0)$ 和 $(-1\,000\,000\,000,2)$，删除这三个点；
2. 选择三点 $(-400\,714\,529,0)$、$(564\,040\,265,0)$ 和 $(1\,000\,000\,000,2)$，删除这三个点。

两次操作后总得分为 $2\,027\,422\,256$。可以证明这是两次操作后的最大得分，因此 $f(2) = 2\,027\,422\,256$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5
1 3
0
0 1 -1
2 4
0 100
-100 -50 0 50
2 4
0 1000
-100 -50 0 50
6 6
20 1 27 100 43 42
100 84 1 24 22 77
8 2
564040265 -509489796 469913620 198872582 -400714529 553177666 131159391 -20796763
-1000000000 1000000000```

### 输出

```
1
2
2
150 200
2
1000 200
4
99 198 260 283
2
2000000000 2027422256```

# 题解

## 作者：Register_int (赞：12)

题目操作可以转化成：在一条直线上选两个点 $x,y$ 删去，在另一直线上删一个点，并将价值加上 $|x-y|$。要求最大化价值。

若只考虑一条直线，那么最优策略就是每次在这条直线上选一对相距最远点的删去。设 $y=0$ 上选 $n$ 对的答案为 $f(n)$，$y=2$ 上选 $m$ 对的答案为 $g(m)$，我们当然希望答案可以达到上界 $f(n)+g(m)$。事实上，这是完全可行的！具体地，在一条直线上选点时，我们可以删去另一条直线**最中间**的点，这样就完全不会影响到另一条直线的策略了。

对于 $i=1,\cdots,k_{\max}$，我们要找出一个 $t$，使得 $f(t)+g(i-t)$ 最大。容易发现，$f(t)$ 的增长速度是不断变慢的。因为随着取出的对数增多，新取出来的点对距离一定会越来越小。所以可以得出 $f(t)$ 是上凸的。同理，$g(t)$ 也是上凸的，故 $f(t)+g(i-t)$ 也是上凸的，直接三分找最值即可。时间复杂度 $O(n\log n)$，注意三分边界上的一些细节。

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int MAXN = 2e5 + 10;
 
int T, n, m, k; ll a[MAXN], b[MAXN], ans[MAXN];

int main() {
	for (scanf("%d", &T); T--; ) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
		for (int i = 1; i <= m; i++) scanf("%lld", &b[i]);
		sort(a + 1, a + n + 1), sort(b + 1, b + m + 1);
		for (int i = 1; i <= n / 2; i++) a[i] = a[n - i + 1] - a[i];
		for (int i = 1; i <= m / 2; i++) b[i] = b[m - i + 1] - b[i];
		for (int i = 1; i <= n / 2; i++) a[i] += a[i - 1];
		for (int i = 1; i <= m / 2; i++) b[i] += b[i - 1];
		for (k = 1; ; k++) {
			int l = max(k - m / 2, max(0, k * 2 - m)), r = min(n / 2, min(k, n - k));
			for (; l + 1 < r; ) {
				int mid = l + r >> 1;
				ll x = a[mid - 1] + b[k - mid + 1];
				ll y = a[mid + 1] + b[k - mid - 1];
				if (x < y) l = mid; else r = mid;
			}
			ans[k] = -1;
			for (int i = l; i <= r; i++) ans[k] = max(ans[k], a[i] + b[k - i]);
			if (ans[k] < 0) break;
		}
		printf("%d\n", k - 1);
		for (int i = 1; i < k; i++) printf("%lld ", ans[i]); puts("");
	}
}
```

---

## 作者：Nt_Tsumiki (赞：9)

小清新反悔贪心，但是好像不是官解。

首先 $k_{\max}$ 是好算的，不考虑具体删哪些点，点数多的删两个，点数少的删一个，模拟一遍即可。

然后我们考虑反悔贪心，首先显然的答案的形式一定是形如 $a$ 中最大的 $x$ 个区间和 $b$ 种最大的 $y$ 个区间，组成答案 $ans_{x+y}$，并且第 $k$ 大区间一定可以调整成 $a_{n-k+1}-a_k$ 的形式，那我们考虑动态的加入当前最大的区间然后带走对面一个点。

注意到知道删掉具体的哪个点是不必要的，你只需要维护有多少个点没有被删，相当于最后再分配就行。

那么考虑反悔，这里只会有一种情况，就是己方点数大于等于 $2$，对面没点了，这时考虑删掉对面的一个已删最小区间，换得两个点，这样可能带来己方两个区间的收益。

其实还有一种情况就是己方只有一个点或者没有点，考虑删掉对面的已删最小区间，换得两个点，但是这样一定不优，因为只会带来一个区间的收益。

代码实现上就维护四个堆，一个存 $a$ 方最大的 $\lfloor\frac{n}{2}\rfloor$ 个区间，一个存 $b$ 方最大的 $\lfloor\frac{m}{2}\rfloor$ 个区间，一个存 $a$ 方删掉的最小区间，一个存 $b$ 方删掉的最小区间。

[submission](https://codeforces.com/contest/2063/submission/302459737)

---

## 作者：TTpandaS (赞：5)

显然构成的三角形会有一条边平行于 $x$ 轴，我们称不在这条边上的点为该三角形的顶点。

设 $y=0$ 这一行有 $y$ 个三角形顶点，$y=2$ 这一行有 $x$ 个三角形顶点，那么 $2x+y \leq n,x+2y \leq m$，枚举 $x$ 计算 $y$ 就可以得到第一问 $x+y$ 的最大值。

考虑 $y=2$ 这一行有 $x$ 个三角形顶点时 $y=0$ 这一行能贡献的最大底边总长。考虑有 $4$ 个点时，交叉取与两端两两匹配长度相同，推广可得交叉在 $n>4$ 时会遗漏，因此两端两两匹配最优，所以可以预处理出 $y=2$ 这一行有 $x$ 个三角形顶点时 $y=0$ 这一行能贡献的最大底边总长 $f(x)$ 和 $y=0$ 这一行有 $y$ 个三角形顶点时 $y=2$ 这一行能贡献的最大底边总长 $F(y)$。

枚举 $x+y=i$，那么可以得到 $2i-m \leq x \leq n-i$。答案为 $f(x)+F(y)$，考虑调整到 $f(x+1)+F(y-1)$ 后答案的变化，$f(x)$ 与 $f(x+1)$ 的增量会随着 $x$ 的增大而减小（端点在向内缩），$F(y)$ 与 $F(y-1)$ 的减量会随着 $x$ 的增大而增大（端点在向外扩），因为 $f(x+1)+F(y-1)-f(x)-F(y)$ 在随着 $x$ 的增大而减小，找到最小的 $x$ 满足 $f(x+1)+F(y-1)-f(x)-F(y) <0$，$f(x)+F(y)$ 即为最大值，在 $[2i-m,n-i]$ 区间内二分即可。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+5;
int T;
int n,m;
int a[N],b[N];
int f[N],F[N];
int len1[N],len2[N];
int ask(int x,int y){
	return f[x]+F[y];
}
int ans[N];
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=m;i++){
		cin>>b[i];
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	int l=1,r=n;
	for(int i=1;i<=n/2;i++){
		f[i]=f[i-1]+a[r]-a[l];
		len1[i]=a[r]-a[l];
		l++,r--;
//		cout<<len1[i]<<' ';
	}
//	cout<<endl;
	l=1,r=m;
	for(int i=1;i<=m/2;i++){
		F[i]=F[i-1]+b[r]-b[l];
		len2[i]=b[r]-b[l];
//		cout<<len2[i]<<' ';
		l++,r--;
	}	
//	cout<<endl;
	int maxn=0;
	for(int y=0;y<=n;y++){
		int x=min((n-y)/2,m-2*y);
		if(x>=0){
			if(x+y>maxn){
				maxn=x+y;
			}
		}
	}
	cout<<maxn<<endl;
	for(int i=1;i<=maxn;i++){
		int l=max(0ll,2*i-m),r=min(i,n-i)-1,res=l-1;
//		cout<<i<<':'<<l<<' '<<r<<endl;
//		for(int j=l;j<=r;j++){
//			cout<<ask(j,i-j)<<' ';
//		}
		while(l<=r){
			int mid=(l+r)>>1;
			if(len1[mid+1]-len2[i-mid]>=0){
				res=mid;
				l=mid+1;
			}
			else{
				r=mid-1;
			}
		}
		res++;
		cout<<ask(res,i-res);
//		cout<<'\n';
		cout<<' ';
	}
	cout<<endl;
}
signed main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：喵仔牛奶 (赞：4)

不要三分，不用反悔贪心，来一个小清新 multiset 做法。

## Solution

设第一个序列取两个、第二个序列取一个操作了 $i$ 次，第二个序列取两个操作了 $j$ 次，合法条件为：
$$2i+j\le n\land i+2j\le m$$

首先，枚举 $i$，显然有 $k_{\max}=\sum_{i=0}^{\min(n/2,m)}i+\min(n-2i,\frac{m-i}{2})$。

枚举 $i+j=k$，我们需要求出 $f(k)$。条件变为 $i\le n-k\land j\le m-k$，从小到大枚举 $k$，用数据结构维护前面 $n-k$ 对和 $m-k$ 对，每次取出前 $k$ 大即可。

考虑数据结构怎么实现，每次需要做的是删除两对并查询前 $k$ 大，用一个 multiset 维护前 $k$ 大，另一个维护其它数即可。

## Code

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DEP(i, r, l) for (int i = (r); i >= (l); -- i)
#define fi first
#define se second
#define pb emplace_back
#define mems(x, v) memset((x), (v), sizeof(x))
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
using namespace std;
namespace Milkcat {
	typedef long long LL;
	typedef pair<LL, LL> pii;
	const int N = 1e6 + 5;
	LL n, m, k, w, a[N], b[N]; multiset<int> p; multiset<int, greater<int>> q;
	void del(LL x) {
		if (SZ(p) && x >= *p.begin()) p.erase(p.find(x)), w -= x;
		else q.erase(q.find(x));
	}
	int main() {
		cin >> n >> m, k = w = 0, p.clear(), q.clear();
		REP(i, 1, n) cin >> a[i];
		REP(i, 1, m) cin >> b[i];
		sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + m);
		REP(i, 1, n) q.insert(a[n - i + 1] - a[i]);
		REP(i, 1, m) q.insert(b[m - i + 1] - b[i]);
		REP(i, 0, min(n, m)) k = max(k, i + min(n - i * 2, (m - i) / 2));
		cout << k << '\n';
		REP(i, 1, k) {
			del(a[i] - a[n - i + 1]), del(b[i] - b[m - i + 1]);
			while (SZ(p) < i) {
				auto it = q.begin();
				p.insert(*it), w += *it, q.erase(it);
			}
			cout << w << ' ';
		}
		cout << '\n';
		return 0;
	}
}
int main() {
	cin.tie(0)->sync_with_stdio(0);
	int T = 1; cin >> T;
	while (T --) Milkcat::main();
	return 0;
}
```

---

## 作者：liuhl_weifang (赞：3)

提供一个纯贪心的做法，无需三分/二分/优先队列。

我们将选三角形改为从数组里选两个数配对，然后从另一个数组里面随便删掉一个数。那么显然这两个数应该选的尽量远。

假如现在已经算出来 $f(A+B)$，并且 $a$ 数组里面已经配了 $A$ 对，$b$ 数组里面已经配了 $B$ 对，那么下一步我们有 4 种做法来算出 $f(A+B+1)$：

* $(A,B+1)$
* $(A+1,B)$
* $(A-1,B+2)$
* $(A+2,B-1)$

分类讨论即可。时间复杂度 $\Theta(n \log n + m \log m)$，瓶颈是给序列排序，如果使用优秀的排序算法可做到 $\Theta(n+m)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define FAST ios::sync_with_stdio(false);cin.tie(0)
using namespace std;
int n,m;
int a[200010],b[200010];
int c[400010];
int op;
int check(int i,int j,int l,int r){
	if(i>=0&&j<=n+1&&l>=0&&r<=m+1&&i<j&&l<r&&j-i-1>=l&&r-l-1>=i){
		return true;
	}
	return false;
}
void upd(int x,int y,int z){
	if(y>c[x]){
		c[x] = y;
		op = z;
	}
	return;
}

void solve(){
	cin >> n >> m;
	for (int i=1;i<=n;i++) cin >> a[i];
	for (int i=1;i<=m;i++) cin >> b[i];
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	int i = 0,j = n+1;
	int l = 0,r = m+1;
	int idx = 0;
	while(1){
		++idx;
		c[idx] = op = -1;
		
		if(check(i+1,j-1,l,r)) upd(idx,c[idx-1]+a[j-1]-a[i+1],1);
		
		if(check(i,j,l+1,r-1)) upd(idx,c[idx-1]+b[r-1]-b[l+1],2);
		
		if(check(i-1,j+1,l+2,r-2)) upd(idx,c[idx-1]+b[r-1]-b[l+1]+b[r-2]-b[l+2]-(a[j]-a[i]),3);
	
		if(check(i+2,j-2,l-1,r+1)) upd(idx,c[idx-1]+a[j-1]-a[i+1]+a[j-2]-a[i+2]-(b[r]-b[l]),4);
		
		if(c[idx]==-1) break;
		
		if(op==1) i++,j--;
		else if(op==2) l++,r--;
		else if(op==3) i--,j++,l+=2,r-=2;
		else i+=2,j-=2,l--,r++;
	}
	--idx;
	cout << idx << "\n";
	for (int i=1;i<=idx;i++) cout << c[i] << " ";
	cout << "\n";
	return;
}

signed main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：lsc72 (赞：3)

赛时先写了个假的贪心，想到正解后赶紧写，最后 $10$ 秒交，结果 $k_{max}$ 计算错了。所以想着来写篇题解纪念下。  
首先是有点坑的 $k_{max}$ 的计算，完全可以模拟一遍得出，然而我写了个错的式子，就是某种假掉的贪心。  
首先是一个性质，三角形的高固定为 $2$，因此面积只和其中两个在同一行的点的距离有关，事实上面积的值就是距离的值。所以我们可以将两行的点分别排序再做。  
考虑只有一个三角形时的计算，显然，我们应该取相离最远的同一行的两个点。多个三角形时以此类推，尽量取远的。  
但如果这时候如果发现对面没有一个顶点来配合这同一行的两个点成为顶点了怎么办？这时候我们就考虑释放对面作为底的两个点，成为新的顶点。  
我们来分析这个过程，显然失去了一个三角形，又得到了两个三角形，最后还是新增一个三角形。 
那么我们释放哪两个点呢，显然是相聚最近的两个点。  
于是可以点两两配对（最左边一个，最右边一个成一个组），丢到优先队列里反悔贪心去做。  
Code：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define lll __int128
#define ull unsigned long long
#define pb push_back
#define fi first
#define se second
#define mp make_pair

const int MAXN=200005;

int T,n,m,k;
int a[MAXN],b[MAXN];
ll ans;
priority_queue<int> qa,qb,_qa,_qb;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin>>T;
    while (T--){
        cin>>n>>m;
        for (int i=1;i<=n;i++) cin>>a[i];
        for (int i=1;i<=m;i++) cin>>b[i];
        sort(a+1,a+n+1); sort(b+1,b+m+1);
        ans=0;
        int tn=n,tm=m; k=0;
        while (true){
            if (tn<tm) swap(tn,tm);
            if (tn<2||!tm) break;
            ++k;
            tn-=2; tm--;
        }
        cout<<k<<'\n';
        while (!qa.empty()) qa.pop();
        while (!qb.empty()) qb.pop();
        while (!_qa.empty()) _qa.pop();
        while (!_qb.empty()) _qb.pop();
        for (int i=1;i<=n/2;i++) qa.push(a[n-i+1]-a[i]);
        for (int i=1;i<=m/2;i++) qb.push(b[m-i+1]-b[i]);
        for (int i=1;i<=k;i++){
            ll k1=-1e17,k2=-1e17;
            if (n>=2&&m>=2){
                k1=qa.top(); k2=qb.top();
                if (k1>=k2){
                    qa.pop();
                    _qa.push(-k1);
                    ans+=k1;
                    n-=2; m-=1;
                }
                else{
                    qb.pop();
                    _qb.push(-k2);
                    ans+=k2;
                    m-=2; n-=1;
                }
            }
            else if (n>=2){
                k1=qa.top(); qa.pop();
                ans+=k1; _qa.push(-k1);
                if (!m){
                    k2=_qb.top(); _qb.pop();
                    ans+=k2; 
                    k1=qa.top(); qa.pop();
                    ans+=k1; _qa.push(-k1);
                    n-=3;
                }
                else{
                    n-=2; m--;
                }
            }
            else{
                k2=qb.top(); qb.pop();
                ans+=k2; _qb.push(-k2);
                if (!n){
                    k1=_qa.top(); _qa.pop();
                    ans+=k1; 
                    k2=qb.top(); qb.pop();
                    ans+=k2; _qb.push(-k2);
                    m-=3;
                }
                else{
                    m-=2; n--;
                }
            }
            cout<<ans<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
```

---

## 作者：__little__Cabbage__ (赞：2)

## Solution

首先问题可以转化成在 $a,b$ 两个数组中选数，每次必须在一个数组中选 $2$ 个（设为 $x,y$），另一个选 $1$ 个，产生贡献 $|x-y|$，求分别对于每个可能的 $k$，贡献和的最大值。

设 $f_i$ 为在 $a$ 中选 $i$ 对点的最大答案，$g_i$ 为在 $b$ 中选 $i$ 对点的最大答案，显然从两边依次向中间取就可以把 $f,g$ 预处理出来。

那么对于一个 $k$，要求的就是一个 $x$ 使得 $f_x + g_{k-x}$ 最大，发现这个东西显然是上凸的（因为 $f,g$ 都是增长速度越来越慢），于是三分就行了。

不过注意三分边界，即在一个数组中选的数不能 $<0$ 也不能 $>$ 数组长度：

$$
\begin{cases}
2x + (k-x) \le n \\
x + 2(k-x) \le m \\
x \ge 0 \\
k-x \ge 0
\end{cases}
$$

可以解得 $\max(0,2k-m) \le x \le \min(k,n-k)$。

## Code

```cpp
int n,m,a[MAXN],b[MAXN],f[MAXN],g[MAXN];

il int sol(int k)
{
    auto check=[](int k,int x){return f[x]+g[k-x];};

    int l=max(0ll,2*k-m),r=min(k,n-k),midl=0x66CCFF,midr=0x66CCFF;
    while(l+3<r)
    {
        midl=l+(r-l+1)/3,midr=r-(r-l+1)/3;
        check(k,midl)<check(k,midr) ? (l=midl) : (r=midr);
    }

    int ans=-0x66CCFF;
    rep(i,l,r) ans=max(ans,check(k,i));
    return ans;
}

il void solve(int __Ti)
{
    read(n,m),_::r(a,n),_::r(b,m);
    sort(a+1,a+n+1),sort(b+1,b+m+1);

    rep(i,1,n) f[i]=f[i-1]+a[n-i+1]-a[i];
    rep(i,1,m) g[i]=g[i-1]+b[m-i+1]-b[i];

    vector <int> v;
    rep(k,1,inf)
    {
        v.pb(sol(k));
        if(v.back()<0) break;
    }

    v.pop_back();
    write((int)v.size(),'\n');
    _::w(v);
}
```

---

## 作者：qwq___qaq (赞：2)

第一问式子写假了，但是不管怎么样，你算出所有值之后只需要找有效的值的数量就行了。

显然需要先对 $a,b$ 分别排序。

显然我们先选差大的，所以说就是从两头开始选，也就是说，上面的第 $i$ 对贡献是 $f(i)=a_{n-i+1}-a_i$，下面的第 $j$ 对贡献是 $g(j)=b_{m-j+1}-b_j$。

我们记上面选了 $i$ 对，下面选了 $j$ 对，那么上面就占用了 $2i+j$ 个点，下面就占用了 $2j+i$ 个点。

然后我们每一步都考虑扩展一对点，显然，贪心地，我们是选的 $f(i+1)$ 和 $g(j+1)$ 中的较大值。

但是边界情况需要再讨论一下：

- $2i+j=n-1$：此时上面只能取一个点，那么此时下面必须取两个点，如果去不了就不行了，$2j+i=m-1$ 同理。

- $2i+j=n$：此时需要增加数量的话，必须拆掉上面的一个点对，贪心地，显然是拆掉最小的，即 $f(i)$，然后再在下面取两个点对，如果去不了就不能再多了，$2j+i=m$ 同理。

下面来说明一下为什么最多只会反悔一次，因为我们每一步都取的是最大的，所以现在选的点对的贡献一定比还没选的大。而我们只需要拆一步就可以让选的点对多 $1$；如果我们多拆了一对的话，那么在另一边一对没选过的点就会造成贡献，而这个贡献显然是没有拆掉的多的。所以说，如果这样目的不是让点对增加，那么它一定不优。因此，只有在 $2i+j=n$ 或 $2j+i=m$ 这两种情况下，只能通过拆点对来让点对数量增加的情况下，才会取主动地拆点，否则就会在另一边选出一个点对来补偿，这个点对一定是更劣的。

时间复杂度 $O(n\log n)$，瓶颈在排序，只不过写起来特别臭。

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int N=3e5+5;
int T,n,m,a[N],b[N];
vector<int> ANS;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=1;i<=m;++i) cin>>b[i];
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		int s=0,i=0,j=0;
		while(1){
			if(2*i+j==n){
				if(2*(j+2)+(i-1)>m||!i) break;
				s-=(a[n-i+1]-a[i]);
				--i;
				++j;
				s+=(b[m-j+1]-b[j]);
				++j;
				s+=(b[m-j+1]-b[j]);
			} else if(2*j+i==m){
				if(2*(i+2)+(j-1)>n||!j) break;
				s-=(b[m-j+1]-b[j]);
				--j;
				++i;
				s+=(a[n-i+1]-a[i]);
				++i;
				s+=(a[n-i+1]-a[i]);
			} else if(2*i+j==n-1){
				if(2*(j+1)+i>m) break;
				++j;
				s+=(b[m-j+1]-b[j]);
			} else if(2*j+i==m-1){
				if(2*(i+1)+j>n) break;
				++i;
				s+=(a[n-i+1]-a[i]);
			} else if(a[n-(i+1)+1]-a[i+1]>b[m-(j+1)+1]-b[j+1]){
				++i;
				s+=(a[n-i+1]-a[i]);
			} else{
				++j;
				s+=(b[m-j+1]-b[j]);
			}
			ANS.emplace_back(s);
		}
		cout<<ANS.size()<<endl;
		for(auto x:ANS) cout<<x<<' ';
		cout<<endl;
		ANS.clear(),ANS.shrink_to_fit();
	}
	return 0;
}
```

---

## 作者：Night_sea_64 (赞：1)

我这解法有点麻烦，导致赛后 1h 才调过。赛时连绿都切不掉了真恐怖。

显然这个问题就是每次在同一条横线上选两个点 $p,q$ 配对，再在另一条横线上选一个点，贡献为 $p,q$ 的坐标之差。

不难发现肯定是每次选取并配对的两个点距离越远越好，那对于每条横线，一定是最小与最大配对、次小与次大配对……。至于三角形中剩下那一个点是什么并不重要，所以只需要随便选一个最没用的。

设现在进行了 $i$ 次操作，其中 $y=0$ 上的点一共配 $j$ 对，那么需要满足如下条件：

$$2\times j+i-j\le n$$

其中 $2\times j$ 就指的是配对用掉的点，$i-j$ 就是剩下的在这条横线上随便选的点。解得 $j\le n-i$，同时显然有 $j\le i$。

求 $k_{max}$ 是容易的，暴力枚举即可。由上面的约束可以贪心求出 $x=k_{max}$ 时的答案，然后直接贪心倒推回前面的答案。具体就是先选择一个贡献最小的配对删掉，然后如果有某个未选配对比某个已选配对权值高就替换掉（因为上面所说的那个约束，那个权值更高的配对不一定能被选上，但是倒推时随着 $i$ 的减少，限制会变宽，所以就有可能出现这种情况）。

代码及其冗长，时间复杂度 $O(n\log n+m\log m)$。

```cpp
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
int t,n,m,a[200010],b[200010],ans[200010];
signed main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=m;i++)cin>>b[i];
        sort(a+1,a+n+1);
        sort(b+1,b+m+1);
        int kmax;
        for(int i=1;i<=n+m;i++)
        {
            int nn=n-i,mm=m-i;
            if(nn<0||mm<0||nn+mm<i)
            {
                kmax=i-1;
                break;
            }
        }
        for(int i=1;i<=n;i++)
        {
            a[i]=a[n-i+1]-a[i];
        }
        for(int i=1;i<=m;i++)
        {
            b[i]=b[m-i+1]-b[i];
        }
        int lim1=n-kmax,lim2=m-kmax;
        int cur1=0,cur2=0,sum=0;
        for(int i=1;i<=kmax;i++)
        {
            if(cur1==lim1)
            {
                sum+=b[++cur2];
            }
            else if(cur2==lim2)
            {
                sum+=a[++cur1];
            }
            else
            {
                if(a[cur1+1]>b[cur2+1])
                {
                    sum+=a[++cur1];
                }
                else
                {
                    sum+=b[++cur2];
                }
            }
        }
        ans[kmax]=sum;
        for(int i=kmax-1;i>=1;i--)
        {
            lim1++,lim2++;
            if(cur1==0)sum-=b[cur2--];
            else if(cur2==0)sum-=a[cur1--];
            else if(a[cur1]<b[cur2])sum-=a[cur1--];
            else sum-=b[cur2--];
            if(cur1)
            {
                if(b[cur2+1]>a[cur1])
                {
                    sum+=b[++cur2];
                    sum-=a[cur1--];
                }
            }
            if(cur2)
            {
                if(a[cur1+1]>b[cur2])
                {
                    sum+=a[++cur1];
                    sum-=b[cur2--];
                }
            }
            ans[i]=sum;
        }
        cout<<kmax<<endl;
        for(int i=1;i<=kmax;i++)cout<<ans[i]<<" ";cout<<endl;
    }
    return 0;
}
```

---

## 作者：liruixiong0101 (赞：1)

本题有多种做法，下面讲两种做法。

---

## $\text{Solution 1}:$
首先由小学知识易发现，三角形的面积只与底边长度有关，也即底边两点的坐标差。

我们考虑枚举 $k$，设用了 $x$ 个底边在 $y=2$ 上的三角形，$k-x$ 个底边在 $y=0$ 上的三角形。我们发现当 $k$ 固定时，令 $f_k(x)$ 为选了 $x$ 个底边在 $y=2$ 上的三角形所能得到的最大得分，有 $f_k(x)$ 是一个单峰函数，显然 $x$ 个三角形需要最远连最远，次远连次远，$k-x$ 个三角形同理，当 $x$ 由 $0$ 变到 $k$ 时，$y=2$ 上的三角形的 $\Delta S$ 变大，$y=0$ 上的三角形的 $\Delta S$ 变小，所以 $f_k(x)$ 是单峰的。

这就说明了我们可以三分或二分找到 $f_k(x)$ 的峰值，单次查询复杂度 $\mathcal{O}(\log n)$，三分范围解不等式算一下即可。（但是重复值好像并不多，可以这样做）

AC 链接：<https://codeforces.com/contest/2063/submission/302434596>。

## $\text{Solution 2}:$
这个做法应该是代码最好写，最简单的。

再次考虑函数 $f_k(x)$ 和 $f_{k+1}(x)$：
![](https://cdn.luogu.com.cn/upload/image_hosting/0glp6xfj.png)

由图，我们有：
$$
f_k(x)=AD+FI+EJ\\
f_k(x+1)=AD+BC+EJ\\
f_{k+1}(x)=AD+EJ+FI+GH\\
f_{k+1}(x+1)=AD+BC+EJ+FI
$$
若 $f_k(x)\le f_k(x+1)$，则有 $FI\le BC$。

那么 $f_{k+1}(x)=AD+EJ+FI+GH\le AD+EJ+BC+GH\le AD+EJ+BC+FI=f_{k+1}(x+1)$，这说明了 $f_{k+1}(x)$ 的取到峰值的横坐标在 $f_k(x)$ 右边。

这样，我们就可以建立一个指针，从左到右扫过，暴力判断峰值在哪里，除去排序均摊 $\mathcal{O}(n)$。

AC 链接：<https://codeforces.com/contest/2063/submission/302821607>。

---

## 作者：movefast (赞：1)

我很愤怒！

因为学三分的时候学的题解有 bug，我三分 WA 了，我很愤怒！

****

我们看到题，觉得答案应该是个单峰函数，我们想想怎么证。

其实也很好证，因为，每次增加的那个三角形的面积也是递减的。

换句话说，$f_i-f_{i-1}$ 是越来越小的。

为什么呢？

使用反证法，若第 $i-1$ 次增加的比第 $i$ 次增加的少，那么可以把第 $i$ 次使用的三角形与第 $i-1$ 次使用的互换，这样就能使 $f_{i-1}$ 更大。

推而广之，因为要求 $f_i$，我们考虑枚举 $i$，三分 $y=0$ 使用的三角形数量，单峰原理与答案是一样的。

至于三分的范围，解不等式即可。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
typedef double db;
using namespace std;

const int N=200005;
ll T,n,m;
ll a[N],b[N],suma[N],sumb[N];
ll ans[N];

ll work(ll doa,ll dob)
{
	return suma[doa]+sumb[dob];
}

int main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&m);
		for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(ll i=1;i<=m;i++) scanf("%lld",&b[i]);
		
		sort(a+1,a+1+n);
		sort(b+1,b+1+m);
		
		ll san=0,sbn=0;
		for(ll l=1,r=n;l<r;l++,r--) suma[san+1]=a[r]-a[l]+suma[san],san++;
		for(ll l=1,r=m;l<r;l++,r--) sumb[sbn+1]=b[r]-b[l]+sumb[sbn],sbn++;
		
		ll mxk;
		for(ll i=1;;i++)
		{
			ll l=max(2*i-m,0ll),r=min(i,n-i),mid,mid2;
			if(l>r)
			{
				mxk=i-1;
				break;
			}
			while(l+2<r)
			{
				mid=l+r>>1;
				mid2=mid+r>>1;
				if(work(mid,i-mid)<work(mid2,i-mid2)) l=mid;
				else r=mid2;
			}
			if(l+1<=r) ans[i]=max({work(l,i-l),work(l+1,i-l-1),work(r,i-r)});
			else ans[i]=work(l,i-l);
		}
		
		printf("%lld\n",mxk);
		for(ll i=1;i<=mxk;i++)
			printf("%lld ",ans[i]);
		puts("");
	}
	return 0;
}
```

---

## 作者：w9095 (赞：1)

[CF2063D Game With Triangles](https://www.luogu.com.cn/problem/CF2063D)

小清新三分，有几个细节赛时没有调完，遗憾离场，破防了。

注意到如果我们可以求 $f(k)$，那么 $k_{\text{max}}$ 只需要一直枚举 $k$ 直到 $f(k)$ 求不出来为止，因此我们直接考虑求 $f(k)$。

我们考虑枚举在 $y=0$ 选择三角形的底边数量 $x$，注意到答案关于 $x$ 是单峰的。因为如果 $x$ 不够多，可能 $y=0$ 上一些距离较远的点无法被利用，如果 $x$ 太多了，可能 $y=2$ 上一些距离较远的点无法被利用。如果赛时不敢确定可以打个表看看。

考虑如何快速计算。我们可以预处理出来 $y=0$ 和 $y=2$ 上距离前 $i$ 大的点两两匹配后得到的贡献，因为我们可以贪心地取这些点对使答案最大。然后取三角形需要另一条线段也贡献一个点，我们判断一下 $y=0$ 和 $y=2$ 两条线段上用的总点数，如果有一个超了，直接返回负无穷表示不成立。

现在唯一的问题是答案左右两边有一些不成立的位置，如果全部返回负无穷，我们无法确定该舍去哪一段。也就是说，这个函数并不是严格单峰。因此，我们在负无穷上面加上一些东西，使得答案变成严格单峰。具体的，我们可以通过使其不成立的条件判断出来是左边的不成立还是右边的不成立，如果是左边的不成立，那么返回负无穷加上 $x$，否则返回负无穷加上 $k-x$。

还有一些坑点，重复地元素需要特判，以及三分遇到相等的点应该舍左边而不是舍右边。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,m,a[300000],b[300000],pa[300000],pb[300000],ou[300000];
long long check(long long x,long long k)
{
	if((x*2+k-x)>n||pa[x]==-1e18)return -(long long)1e18+k-x;
	if((x+(k-x)*2)>m||pb[k-x]==-1e18)return -(long long)1e18+x;
	return pa[x]+pb[k-x];
}

int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	scanf("%lld%lld",&n,&m);
	   	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	   	for(int i=1;i<=m;i++)scanf("%lld",&b[i]);
	   	sort(a+1,a+n+1),sort(b+1,b+m+1);
	   	for(int i=1;i<=max(m,n);i++)pa[i]=pb[i]=-1e18;
	   	for(int i=1;i<n-i+1;i++)
		    if(a[n-i+1]!=a[i])pa[i]=pa[i-1]+a[n-i+1]-a[i];
		    else break;
	   	for(int i=1;i<m-i+1;i++)
		    if(b[m-i+1]!=b[i])pb[i]=pb[i-1]+b[m-i+1]-b[i];
		    else break;
		long long flag=0;
	   	for(int i=1;i<=max(m,n);i++)
	   	    {
	   	    long long l=0,r=i,ans=-1e18;
	   	    while(l<=r)
	   	       {
	   	       long long lmid=(l*2+r)/3,rmid=(l+r*2)/3;
			   if(check(lmid,i)>check(rmid,i))ans=max(ans,check(lmid,i)),r=rmid-1;
			   else ans=max(ans,check(rmid,i)),l=lmid+1;
			   }
			ou[i]=ans;
			if(ou[i]<0)
			   {
			   	printf("%d\n",i-1),flag=i-1;
			   	for(int j=1;j<=i-1;j++)printf("%lld ",ou[j]);
			   	break;
			   }
			}
		if(flag)printf("\n");
	   }
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# CF2063D 题解

非常好赛时又稳定切绿。

## 思路

先来看第一个问怎么做。

一个三角形需要占用 $a,b$ 两个数组其中一个的 $2$ 个点以及另一个二的 $1$ 个点，那么让剩余点数较多的去减掉 $2$，另一个减去 $1$，直到无法进行操作即可。

接下来看如何统计 $f(x)$。

假设我要从剩余的点中选出三个点组成三角形，要让这个三角形面积尽可能大，由于 $a,b$ 之间的距离 $2$ 是固定的，于是只需要让底边的两个端点离得更远一点，因此将 $a,b$ 两个序列排序，每一次取出未取的最靠外边的两个点，至于从另一者取出的一个点怎么取，这个可以不用管，因为可以通过 $a$ 需要排掉几个点和 $b$ 需要排掉几个点来计算剩余点数，其它的有剩，则可以直接取。

可以用双指针来做，记 $i$ 为 $a$ 数组取了 $i-1$ 组底边，$j$ 为 $b$ 数组取了 $j-1$ 组底边，用 $mxcnt$ 来表示题目中的 $k_{\max}$ 的话，则当 $i-1+j-1<mxcnt$ 的时候，一定能够在剩余的点中再取。

下一组三角形底边在 $a$ 取，记录这样做需要让另一指针缩回去多少，以及对答案的贡献，在 $b$ 取的同理。

另一指针缩回去太多的，就不要了，选那个缩回去更少的，如果缩回相同，则对答案贡献更大的保留。

尽管指针在中途会随回去，但最终都是会走到 $k_{\max}$ 所表示的状态的。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define TIMESTAMP cerr<<fixed<<setprecision(3)<<clock()*1.0/CLOCKS_PER_SEC<<"s"<<endl;
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long
typedef pair<int,int> pii;

const int N=200005;
const int inf=1e18;

int T,n,m;
int a[N],b[N];
int ans1[N],ans2[N];
int ans[N];

int solve_cnt(int n,int m) {
    int ans=0;
    while (n && m && n+m>=3) {
        if (n<m) swap(n,m);
        n-=2,m--,ans++;
    }
    return ans;
}

signed main() {
    scanf("%lld",&T);
    while (T--) {
        scanf("%lld %lld",&n,&m);
        _rep(i,1,n) ans1[i]=-inf;
        _rep(i,1,m) ans2[i]=-inf;
        _rep(i,1,n) scanf("%lld",&a[i]);
        _rep(i,1,m) scanf("%lld",&b[i]);
        sort(a+1,a+1+n);
        sort(b+1,b+1+m);
        int mxcnt=solve_cnt(n,m);
        printf("%lld\n",mxcnt);
        _rep(i,0,mxcnt) ans[i]=-inf;
        int i=1,j=n,idx=0;
        while (i<j) ans1[++idx]=a[j]-a[i],i++,j--;
        // printf("ans1: "); _rep(i,1,idx) printf("%lld ",ans1[i]); putchar(10);
        i=1,j=m,idx=0;
        while (i<j) ans2[++idx]=b[j]-b[i],i++,j--;
        // printf("ans2: "); _rep(i,1,idx) printf("%lld ",ans2[i]); putchar(10);
        i=1,j=1;
        int cur=0;
        while (i-1+j-1<mxcnt) {
            int ansL=-inf,ansR=-inf,minusL=inf,minusR=inf;
            if (ans1[i]!=-inf) {
                minusL=0;
                ansL=ans1[i];
                while (i*2+j-minusL-1>n || (j-1-minusL)*2+i>m) minusL++;
                _rep(g,1,minusL) ansL-=ans2[j-g];
            }
            if (ans2[j]!=-inf) {
                minusR=0;
                ansR=ans2[j];
                while (j*2+i-minusR-1>m || (i-1-minusR)*2+j>n) minusR++;
                _rep(g,1,minusR) ansR-=ans1[i-g];
            }
            if (minusL<minusR || (minusL==minusR && ansL>ansR)) {
                ++i;
                j-=minusL;
                cur+=ansL;
            } else {
                ++j;
                i-=minusR;
                cur+=ansR;
            }
            ans[i+j-2]=max(ans[i+j-2],cur);
            // cout<<"TEST: "<<i<<" "<<j<<" "<<cur<<endl;
            // string stop;
            // cin>>stop;
        }
        _rep(i,1,mxcnt) printf("%lld ",ans[i]);
        putchar(10);
    }
    return 0;
}

/*
1
2 4
0 1000
-100 -50 0 50

ans:
2
1000 200
*/
```

---

## 作者：rogeryi (赞：0)

[CF2063D Game With Triangles](https://www.luogu.com.cn/problem/CF2063D)

本题 $O(n^2)$ 暴力可过。

显然，每次尽可能选取较长的底边。对于同一条直线，一定是从两端向中间取。假设直线 $y=0$ 选择了 $a$ 条底边，$y=2$ 选择了 $b$ 条底边，满足：

- $2a+b \le n$
- $2b+a \le m$

题目相当于对每一个 $k$，计算满足 $a+b=k$ 的 $\max(\text{up}_a+\text{down}_b)$。

其中 $\text{up}_a$ 为上方选择 $a$ 条底边的最大权值， $\text{down}_b$ 为下方选择 $b$ 条底边的最大权值。

显然 $\text{up}$ 和 $\text{down}$ 数组可以排序加前缀和预处理。

这样就得到了 $O(n^2)$ 的算法。

然后有一些优化：

- 贪心选择两条直线中较大底边，直到出现不合法情况。
- 枚举 $a$ 和 $b$ 时，优先枚举 $n$ 和 $m$ 的较小值。
- 枚举时计算上下界，跳过已经贪心计算的部分。

这样就能跑得飞快，在 $1.5$ 秒内通过此题。

代码（为了降低常数，快读比较奇怪）：

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf[1<<24],puf[1<<24];
char *p1,*p2,*p3=puf;
#define input() (p2=(p1=buf)+fread(buf,1,1<<24,stdin))
#define getchar() (*p1++)
#define flush() (p3-=fwrite(puf,1,p3-puf,stdout))
#define putchar(x) (*(p3++)=(x))
int read(){
	int tmp=0;bool flag=0;
	char ch=getchar();
	while(ch<'0'&&ch!='-')	ch=getchar();
	if(ch=='-'){flag=1;ch=getchar();}
	while(ch>='0'){(tmp*=10)+=(ch^'0');ch=getchar();}
	return (flag?-tmp:tmp);
}
char st[18];int num;
void write(long long x){
	do{st[num++]=x%10;x/=10;}while(x);
	while(num)	putchar(st[--num]|'0');
}
int n,m,cnt;
int a[200005],b[200005];
long long sumA[100005],sumB[100005];
long long ans[200005];
void work(){
	n=read();m=read();
	for(int i=1;i<=n;i++)	a[i]=read();
	for(int i=1;i<=m;i++)	b[i]=read();
	sort(a+1,a+n+1);sort(b+1,b+m+1);
	for(int i=1;i<=(n>>1);i++)	a[i]=a[n-i+1]-a[i];
	for(int i=1;i<=(m>>1);i++)	b[i]=b[m-i+1]-b[i];
	if(n>m){swap(n,m);swap(a,b);}cnt=(n>>1);
	for(int i=1;i<=(n>>1);i++)	sumA[i]=sumA[i-1]+a[i];
	for(int i=1;i<=(m>>1);i++)	sumB[i]=sumB[i-1]+b[i];
	int posl=0,posr=0;
	for(int i=1;((posl<<1)+posr)<=n&&(posl+(posr<<1))<=m;i++)
		if(a[posl+1]>b[posr+1])	ans[i]=ans[i-1]+a[++posl];
		else	ans[i]=ans[i-1]+b[++posr];
	ans[posl+posr]=0;
	for(int i=0;i<=(n>>1);i++){
		int lim=min(n-(i<<1),(m-i)>>1);
		for(int j=(posl+posr)-i;j<=lim;j++)	ans[i+j]=max(ans[i+j],sumA[i]+sumB[j]);
		cnt=max(cnt,i+lim);
	}
	write(cnt);putchar('\n');
	for(int i=1;i<=cnt;i++){write(ans[i]);putchar(' ');ans[i]=0;}
	putchar('\n');
}
int main(){
	input();int T=read();
	while(T--)	work();
	flush();return 0;
}
```

---

