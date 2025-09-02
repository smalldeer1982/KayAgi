# Infinite Path

## 题目描述

You are given a colored permutation $ p_1, p_2, \dots, p_n $ . The $ i $ -th element of the permutation has color $ c_i $ .

Let's define an infinite path as infinite sequence $ i, p[i], p[p[i]], p[p[p[i]]] \dots $ where all elements have same color ( $ c[i] = c[p[i]] = c[p[p[i]]] = \dots $ ).

We can also define a multiplication of permutations $ a $ and $ b $ as permutation $ c = a \times b $ where $ c[i] = b[a[i]] $ . Moreover, we can define a power $ k $ of permutation $ p $ as $ p^k=\underbrace{p \times p \times \dots \times p}_{k \text{ times}} $ .

Find the minimum $ k > 0 $ such that $ p^k $ has at least one infinite path (i.e. there is a position $ i $ in $ p^k $ such that the sequence starting from $ i $ is an infinite path).

It can be proved that the answer always exists.

## 说明/提示

In the first test case, $ p^1 = p = [1, 3, 4, 2] $ and the sequence starting from $ 1 $ : $ 1, p[1] = 1, \dots $ is an infinite path.

In the second test case, $ p^5 = [1, 2, 3, 4, 5] $ and it obviously contains several infinite paths.

In the third test case, $ p^2 = [3, 6, 1, 8, 7, 2, 5, 4] $ and the sequence starting from $ 4 $ : $ 4, p^2[4]=8, p^2[8]=4, \dots $ is an infinite path since $ c_4 = c_8 = 4 $ .

## 样例 #1

### 输入

```
3
4
1 3 4 2
1 2 2 3
5
2 3 4 5 1
1 2 3 4 5
8
7 4 5 6 1 8 3 2
5 3 6 4 7 5 8 4```

### 输出

```
1
5
2```

# 题解

## 作者：AutumnKite (赞：9)

首先看到一个排列求 $k$ 次幂，容易想到将排列看成若干置换环的形式。

如排列 $p=\{2,4,1,3,6,5\}$ 可以看成：

```plain
1 --> 2
^     |
|     v
3 <-- 4
```

以及

```plain
5 <==> 6
```

两个置换环。

将一个排列求 $k$ 次幂以后，某个点 $i$ 会重新指向原来环上从 $i$ 开始第 $k$ 个点。

那么由于我们只需要一个环满足颜色相等，容易想到将每个环单独处理以后取 $\min$ 即可。

对于一个环长为 $l$ 的环，我们将环上的点从某个点开始重新标号。我们判断一个 $k$ 是否可行，只需要记 $p=\gcd(k,l)$，我们判断是否存在一个 $0\le t < p$ 使得环上所有模 $p$ 等于 $t$ 的点颜色是否相同即可。

那么显然只要枚举所有 $l$ 的因数 $k$ 即可。

时间复杂度 $O(n\sqrt{n})$。

```cpp
const int N = 200005;
int n, p[N], c[N], vis[N];
int solve(std::vector<int> &a){
	std::vector<int> d;
	int l = a.size();
	for (register int i = 1; 1ll * i * i <= l; ++i) // 求因数
		if (l % i == 0){
			d.push_back(i);
			if (i * i < l) d.push_back(l / i);
		}
	std::sort(d.begin(), d.end());
	for (int k : d){ // 枚举 k
		for (register int i = 0; i < k; ++i){
			bool flag = 1;
			for (register int j = i; j < l; j += k)
				flag &= a[j] == a[i]; // 判断颜色是否相同
			if (flag) return k;
		}
	}
	return l;
}
void solve(){
	read(n);
	for (register int i = 1; i <= n; ++i) read(p[i]), vis[i] = 0;
	for (register int i = 1; i <= n; ++i) read(c[i]);
	int ans = n;
	for (register int i = 1; i <= n; ++i)
		if (!vis[i]){
			std::vector<int> tmp;
			tmp.push_back(c[i]), vis[i] = 1;
			for (register int j = p[i]; j != i; j = p[j])
				tmp.push_back(c[j]), vis[j] = 1;
			ans = std::min(ans, solve(tmp));
		}
	print(ans);
}
```

---

## 作者：syksykCCC (赞：4)

将排列映射为图，$i$ 向 $p_i$ 连边。显然，因为排列由若干个循环构成，所以这个图是若干个环。

一个点指向的点的编号就是它的 $p$ 的值。

考虑乘方操作的实质，$p^k$ 其实是 $i$ 指向的点按照环的方向顺移 $k-1$ 位。也就是，如果原来这个指针指向的是换上的第 $1$ 个数，那么现在指向的就是环上的第 $k$ 个数。

如图所示是将一个循环平方后的变化。

![image.png](https://i.loli.net/2020/03/25/CD8GFNS2ouUxH9p.png)

所以现在我们可以分别处理每一个环。

题目无非就是说，对一个环进行一种等距离遍历，使得路径上所有点的颜色相等。一个大小为 $s$ 的环的本质不同遍历方式只有 $d(s)$ 种，$d(s)$ 表示 $s$ 的因子个数，所以我们可以先枚举因数，再枚举起点，再遍历。

因数显然可以 $O(\sqrt{s})$ 处理出来，设当前因子为 $x$，那么枚举起点只需要枚举 $[0, x)$ 即可，而遍历一遍需要遍历 $\frac{s}{x}$ 个，所以时间复杂度是 $O(\sqrt{s} + s \cdot d(s))$。我的代码里对因子排了个序，其实是不必要的，只要确保都枚举就行。

判断方案的合法性无非就是路径上所有颜色拉出来看看是不是都相同。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, p[N], c[N], ans;
bool vis[N];
vector<int> col, fact;
void GetFact()
{
	fact.clear();
	fact.push_back(1);
	for(int i = 1; i * i <= col.size(); i++)
	{
		if(col.size() % i) continue;
		fact.push_back(i);
		if(i * i != col.size()) fact.push_back(col.size() / i);
	}
	sort(fact.begin(), fact.end());
}
void Solve()
{
	GetFact();
	for(int s : fact) for(int i = 0; i < s; i++)
	{
		bool ok = true;
		for(int j = i; j < col.size(); j += s)
			if(col[j] != col[i]) { ok = false; break; }
		if(ok) { ans = min(ans, s); return; }
	}
}
int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		cin >> n;
		ans = n;
		for(int i = 1; i <= n; i++) vis[i] = false; 
		for(int i = 1; i <= n; i++) cin >> p[i];
		for(int i = 1; i <= n; i++) cin >> c[i];
		for(int i = 1; i <= n; i++)
		{
			if(vis[i]) continue;
			col.clear();
			int j = i;
			while(!vis[j]) col.push_back(c[j]), vis[j] = true, j = p[j];
			Solve();
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：一扶苏一 (赞：2)

## CF1327D Infinite Path

### Analysis

对于每个 $i$，将 $i$ 向 $p_i$ 连边。容易看出，这样连边以后 $p^k$ 的第 $i$ 个位置就是从 $i$ 出发走 $i$ 步的到达的点。并且这张图是若干个简单环。对于每个环，考虑单独处理答案。

设答案为 $k$，则意味着所有经过的点是从某个节点出发，每次跳 $k$ 个节点所能到达的节点集合。一个结论是，在一个长度为 $n$ 的环上，每次跳 $k$ 步，所经过的所有结点的集合就是从该结点出发每次跳 $\gcd(n, k)$ 步，所到达的所有节点集合。

简单证明如下：

将环上的点从 $0$ 到 $(n - 1)$ 编号，不妨设从 $0$ 开始跳。  
那么每次跳 $\gcd(n, k)$ 步跳到的节点显然是所有编号为 $i \times \gcd(n, k) \bmod n$ 的节点，其中 $i$ 取 $0$ 到 $(n - 1)$。   
而每次跳 $k$ 步跳到的节点是所有编号为 $jk \bmod n$ 的节点。也即所有编号为 $(\frac{jk}{\gcd(k, n)} \bmod n) \times \gcd(k, n) \bmod n$ 的节点。  
由于 $n$ 与 $\frac{k}{\gcd(k, n)}$ 互质，所以当 $j$ 取 $0$ 到 $(n - 1)$ 时，$\frac{jk}{\gcd(k, n)} \bmod n$ 可以取到 $0$ 到 $(n - 1)$ 的所有整数。当 $j$ 更大的时候，由于对 $n$ 取模，$\frac{jk}{\gcd(k, n)} \bmod n$ 还是只能取到 $0$ 到 $(n - 1)$ 的全部整数。因此此时能跳到的节点编号还是 $i \times \gcd(n, k) \bmod n$，其中 $i$ 取 $0$ 到 $(n - 1)$。两种情况取到的点的编号相同，因此点集相同。证毕。

所以对于每个环，我们暴力枚举环长 $L$ 的因子，然后 check 选出的所有节点是不是颜色相同即可。时间复杂度 $O(n \operatorname d(n))$。其中 $\operatorname d(n)$ 表示 $n$ 的因子个数。

### Code

```cpp
namespace Fusu {

const int maxn = 200005;

int T;
int n;
int p[maxn], c[maxn];
bool vis[maxn];
std::vector<int> e;

int calc(const int x, const int y);

void Main() {
  for (qr(T); T; --T) {
    qr(n);
    int ans = n;
    qra(p + 1, n); qra(c + 1, n);
    for (int i = 1; i <= n; ++i) vis[i] = false;
    for (int i = 1; i <= n; ++i) if (vis[i] == false) {
      e.clear();
      for (int u = i; vis[u] == false; u = p[u]) {
        vis[u] = true;
        e.push_back(u);
      }
      for (int u = 1, v = e.size(); (u * u) <= v; ++u) if ((v % u) == 0) {
        ans = std::min({ans, calc(u, v), calc(v / u, v)});
      }
    }
    qw(ans, '\n');
  }
}

int calc(const int x, const int y) {
  for (int i = 0; i < x; ++i) {
    bool flag = true;
    for (int j = i; j < y; j += x) if (c[e[j]] != c[e[i]]) {
      flag = false;
      break;
    }
    if (flag == true) return x;
  }
  return n;
}

} // namespace Fusu
```

---

## 作者：gyh20 (赞：2)

数据 $1$ 和数据 $2$ 都没有什么好分析的，看一看数据三。

如果将每一个 $i$ 向 $p_i$ 连边那么样例三就是一个这样的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/nf9dtwoo.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

可以发现，这是一个由一些**互不影响**的环组成的。可以单独处理然后求 $\min$，之后的讲解都是针对原图中的某一个环。

$p^k$ 表示的即为每个点向距离为 $k$ 的点连边。

结束条件即为某一个环上颜色相同。

这其实就是一个类似置换的东西，设环的长度为 $len$，那么如果存在两个 $k$ 值 $x,y$，如果 $\gcd(len,x)=\gcd(len,y)$，那么 $x,y$ 带来的结果是一样的。

所以只需要求不同的 $\gcd(len,x)$ 个数即可，即 $len$ 的约数个数。

枚举每一个约数，检查答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[200002],c[200002],tim,h[200002],ans,tot;
int v[200002];
inline bool check(re int x,re int y){
	for(re int i=1;i<=x;++i){
		re int tmp=i;
		re bool ia=1;
		for(re int j=1;j<=y;++j){
			if(c[h[tmp]]!=c[h[i]]){
				ia=0;
				break;
			}
			tmp+=x;
			tmp=(tmp-1)%tot+1;
		}
		if(ia)return 1;
	}
	return 0;
}
inline void dfs(re int x){
	tot=0;h[++tot]=x;v[x]=1;
	for(re int y=a[x];y!=x;y=a[y]){v[y]=1,h[++tot]=y;}
	re int k=sqrt(tot);
	for(re int i=1;i<=k;++i){
		if(tot%i==0){
		if(check(i,tot/i)){ans=min(ans,i);return;}
		if(check(tot/i,i)){
			ans=min(ans,tot/i);
			
		}	}
	}
}
signed main(){
	t=read();
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)a[i]=read(),v[i]=0;
		for(re int i=1;i<=n;++i)c[i]=read();
		ans=1e9;
		for(re int i=1;i<=n;++i){
		if(!v[i])dfs(i);}
		printf("%d\n",ans);
	}
}
```




---

## 作者：George1123 (赞：2)

# 题解-Infinite Path

[$\color{#88bb22}{\texttt{In cnblogs}}$](https://www.cnblogs.com/Wendigo/p/12565666.html)

> [$\color{#9933cc}{\texttt{Infinite Path}}$](https://www.luogu.com.cn/problem/CF1327D)

> $T$ 组测试数据。每次给你一个 $n$ 的排列 $\{p_n\}$，以及排列中第 $i$ 个数的颜色 $c_i$。
> 令两个排列 $A$ 和 $B$ 的乘积 $C=A\times B$ 满足 $C_i=A_{B_i}$。
> 对于排列 $p$， $p^k=\underbrace{p \times p \times \cdots \times p}_{k\ p}$。
> 求最小的 $k$，使 $P=p^k$ 中存在 $i$ 满足 $c_i=c_{P_i}=c_{P_{P_i}}=\cdots$。

> 数据范围：$1\le T\le 10^4$，$1\le n,\sum n\le 2\times 10^5$。

---

可以把每个 $p_i$ 看做一条 $i\to p_i$ 的边。

因为 $p$ 是个排列，所以会形成**多个环，每个点每条边都在一个环上**。

所以可以**单独考虑每个环的最小 $k$，然后答案取其最小值。**

设当前环大小为 $sz$：

$k$ 每 $+1$ 就使原来的边 $i\to p^k_{i}$ 变成了 $i\to p^{k+1}_{i}$。

设 $g=\gcd(k,sz)$，很明显 $p^k$ 的图中每个环元素和 $p^g$ 中的一样。

所以**只需考虑 $k$ 是 $sz$ 的因数的情况**：

每一整个大环会被分成 $\frac{sz}{k}$ 个环，环上相邻元素在原环上距离为 $k$。

然后对 $\frac{sz}{k}$ 个环判断是否颜色相等，如果有颜色相等的环，就说明对于该环该 $k$ 是合法的。

然后枚举 $k$，找到最小合法 $k$ 即可。

**时间复杂度 $\Theta(n\sigma(n))$（$\sigma(n)$ 表示 $n$ 的约数个数）。**

---

**蒟蒻讲不清楚，放个只有一个环情况的例图：**

![CF1327D2.jpg](https://i.loli.net/2020/03/25/sd1Pvkn4zJYjMa9.jpg)

---

**$\texttt{vector}$ 代码实现**：

```cpp
#include <bits/stdc++.h>
using namespace std;

//&Start
#define re register
#define il inline
#define inf 0x3f3f3f3f
typedef long long lng;


//&Data
#define N 200000
bitset<N+5> vis;

//&Main
int main(){
	re int t,n,ans;
	scanf("%d",&t); //多组测试数据！
	for(re int ti=1;ti<=t;ti++){
		scanf("%d",&n);
		vector<int> p(n+1),c(n+1);
		for(re int i=1;i<=n;i++) scanf("%d",&p[i]);
		for(re int i=1;i<=n;i++) scanf("%d",&c[i]);
		vis.reset(),ans=inf;
		for(re int i=1;i<=n;i++)if(!vis[i]){ //如果该点未出现于之前的环
			vector<int> C,d; //C:该环上的点的颜色，d:sz的因素
			for(re int j=i,f=1;f||j!=i;f=0,j=p[j]) C.push_back(c[j]),vis[j]=1;
			re int sz=C.size(),K;
			for(re int j=1;j<=sz;j++)if(sz%j==0) d.push_back(j);
			for(re int k:d){
				re int ok=0;
				for(re int s=0;s<k;s++){
					re int samc=1;
					for(re int j=s;j<sz;j+=k)if(C[j]!=C[s]){samc=0;break;} //判断环上点颜色相等
					if(samc){ok=1;break;}
				}
				if(ok){K=k;break;}
			}
			ans=min(ans,K); //取k最小值
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：ix35 (赞：2)

## CF 1327 D  Infinite Path

首先，建一张有向图，从 $i$ 向 $p_i$ 连边。

容易发现，每个点的入度和出度都为 $1$，所以形成了若干个有向环。

现在来考虑 $p^k$ 的意义，设 $s$ 向后走 $k$ 步到达的点为 $t_{s,k}$，那么这个 $p^k$ 的第 $s$ 项显然就是 $t_{s,k}$，可以用归纳法证明（幂次每增加 $1$ 就代表往前走一步）。

接下来我们要做的，就是找到一个 $k$，使得每个点向走 $k$ 步后到达的点连边后，存在一个同色环，对于每个环求一遍，最后取最小值即可，我们把这个 $k$ 叫做“步长”。

首先一个结论：步长为 $k$ 可行等价于步长 $\gcd(k,l)$ 可行，其中 $l$ 是环上点的数量，这个应该不难证明。

又 $\gcd(k,l)\leq k$，所以答案一定是形如 $\gcd(k,l)$ 形式的数，即 $l$ 的因数。

所以我们只需要暴力枚举 $l$ 的每个因数并判断即可，感觉这个技巧和 NOI OL 的 T3 是相似的。

时间复杂度为 $O(n\log n)$ 左右（把 $d(n)$ 看作 $\log n$ 了）。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=200010;
int t,n,m,p[MAXN],c[MAXN],vis[MAXN],ok[MAXN],nw[MAXN];
bool chk (int x,int len) {
	int flg=0;
	for (int i=0;i<x;i++) {
		int cur=i,flg2=1;
		for (int j=0;j<len/x;j++) {
			if (c[nw[cur]]!=c[nw[(cur+x)%len]]) {flg2=0;break;}
			cur+=x;
		}
		if (flg2) {flg=1;break;}
	}
	return flg;
}
int main () {
	scanf("%d",&t);
	for (int ii=1;ii<=t;ii++) {
		scanf("%d",&n);
		for (int i=1;i<=n;i++) {scanf("%d",&p[i]);}
		for (int i=1;i<=n;i++) {scanf("%d",&c[i]);}
		for (int i=1;i<=n;i++) {
			if (!vis[i]) {
				int cur=i,len=0;
				while (!vis[cur]) {
					vis[cur]=1;
					nw[len++]=cur;
					cur=p[cur];
				}
				for (int j=1;j*j<=len;j++) {
					if (len%j) {continue;}
					if (chk(j,len)) {ok[j]=1;}
					if (chk(len/j,len)) {ok[len/j]=1;}
				}
			}
		}
		for (int i=1;i<=n;i++) {
			if (ok[i]) {printf("%d\n",i);break;}
		}
		for (int i=1;i<=n;i++) {ok[i]=vis[i]=0;}
	}
	return 0;
}
```


---

## 作者：Register_int (赞：0)

首先把图搞出来，发现是很多环。显然对置换求幂不会让两个本不联通的环联通，所以可以对每个环单独考虑。  
根据次幂的定义，可以得到，对一个环求幂，就是将环上每一个点指向他接下来的第 $k$ 个点（~~废话~~）。那么，当 $k$ 是环长 $n$ 的约数时，$p^k$ 是 $\dfrac nk$ 个长度为 $k$ 的小环。其余情况则与 $k'=\gcd(k,n)$ 的情况一致。所以只需枚举倍数判断环上是否同色即可。时间复杂度 $O(n\sqrt n)$。  
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

int p[MAXN], a[MAXN];

bool vis[MAXN];

int b[MAXN], len;

inline 
bool check(int d) {
	bool f1 = 0, f2 = 0;
	for (int i = 1; i <= d; i++) {
		f2 = 1;
		for (int j = i + d; j <= len; j += d) f2 &= b[i] == b[j];
		f1 |= f2;
	}
	return f1;
}

inline 
int solve(int k) {
	int res = 0;
	vis[k] = 1, b[len = 1] = a[k];
	for (int i = p[k]; i != k; i = p[i]) b[++len] = a[i], vis[i] = 1;
	res = len;
	for (int i = 1; i <= len / i; i++) {
		if (len % i == 0) {
			if (check(i)) res = min(res, i);
			if (i != len / i && check(len / i)) res = min(res, len / i);
		}
	}
	return res;
}

int t, n, ans;

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n), ans = n;
		for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) {
			if (vis[i]) continue;
			ans = min(ans, solve(i));
		}
		for (int i = 1; i <= n; i++) vis[i] = 0;
		printf("%d\n", ans);
	}
}
```

---

## 作者：wind_whisper (赞：0)

## ${\text{Description}}$
$T$ 组数据，每次给一个长度为 $n$ 的置换 $p$ 和颜色数组 $c$，求最小的 $k$，使 $p^k$ 中存在一个“同色环”，即存在 $1\le i\le n$，使 $p^k_i,p_{p^k_i}^k,\dots$ 全部同色.

数据范围：$1\le T\le 10^4$ $1\le n,\sum n\le 2\times 10^5$.
## $\text{Solution}$
很不错的一道题.  
置换不难想到找环.  
手推几个可以发现，$p_k$ 的每个点会指向原环往后的 **第 $k$ 个点**.  
设总环的大小为 $siz$，且新环的大小为 $\frac{siz}{\gcd(k,siz)}$.  
那么贪心的想，要使 $k$ 尽可能的小，一定会有 $\gcd(k,siz)=k$，也就是 **$k$ 是 $siz$ 的因数**.  
那么我们找出所有的环，暴力枚举因数判断是否存在同色合法环即可.  
时间复杂度 $O(n\sqrt n)$.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=5e5+100;
const double eps=1e-9;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m,k;
int to[N],c[N];
bool vis[N];
int a[N],tot,ans;
bool check(int num){
  int k=tot/num;
  for(int x=1;x<=k;x++){
    int y=(x-1+k)%tot+1,flag=1;
    while(y!=x){
      if(c[a[x]]!=c[a[y]]){
	flag=0;break;
      }
      y=(y-1+k)%tot+1;
      //debug("x=%d y=%d tot=%d k=%d\n",x,y,tot,k);
    }
    if(flag) return true;
  }
  return false;
}
void work(int x){
  tot=0;
  while(!vis[x]){
    a[++tot]=x;vis[x]=1;
    x=to[x];
  }
  for(int i=tot;i>=1;i--){
    if(tot%i) continue;
    //debug("%d\n",i);
    if(check(i)){
      ans=min(ans,tot/i);return;
    }
  }
  return;
}
int main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  int T=read();
  while(T--){
    n=read();
    ans=2e9;
    for(int i=1;i<=n;i++) to[i]=read(),vis[i]=0;
    for(int i=1;i<=n;i++) c[i]=read();
    for(int i=1;i<=n;i++){
      if(vis[i]) continue;
      work(i);
    }
    printf("%d\n",ans);
  }
  return 0;
}
/*

*/

```


---

## 作者：fanfansann (赞：0)

##  CF1327D Infinite Path（置换循环节）
**Problem**

T 组数据，每组数据给定一个长度为 $n$ 的排列（置换） $p$ 和颜色数组 $c$，求最小的 $k$，使 $p^k$  中存在一个“同色无限环”。即，存在 $i$，使 $p^k_i ,\ p_{p^k_i}^k ,\ \dots$，整个循环节全部同色。其中 $p^k$ 指排列 $p$ 进行 $k-1$ 次 $p$ 置换。

数据范围：$1\le T\le 10^4 ,1\le n,\sum n\le 2\times 10^5$ 。

**Solution**

显然一个置换可以拆分为若干个循环置换，即若干个循环节，并且每一个循环置换之间是没有任何关联的，所以我们可以每次单独对每一个循环置换进行分析，并且题目要求出现一个同色无限环即可，所以我们单独分析，然后取最小值即可。

这里给定的序列一定是一个排列，所以直接暴力计算所有的循环节，设该循环节的长度为 $len$，我们知道对一个循环节进行 $k$ 次置换之后，点 $i$ 将会指向原序列中的点 $i+k$。设我们要找的答案为 $k$，$k$ 的含义就是所有经过的点是从某个点 $i$ 出发，每次走 $k$ 步所能到达的所有点的集合。 

显然 $k\le len \le n$，我们如果每次暴力枚举 $k$ ，时间复杂度 $O(n^2)$ 显然无法接受，我们考虑优化。显然可以想到在学习群论的时候有一个定理，在一个长度为 $len$ 的环上，从 $i$ 出发，每次走 $k$ 步，等价于从 $i$ 出发，每次走 $\gcd(len, k)$ 步，所以我们只需要枚举所有的 $\gcd(len, k)$，即 $len$ 的因子即可。这样时间复杂度仅为 $O(n\times d(n))≈O(nlogn)$，对于每一个 $k$ ，我们判断一下从 $i\in[0,k)$ 出发，每次走 $k$ 步经过的循环节中的点的颜色是否相同即可。


**Code**

```cpp
// Problem: D. Infinite Path
// Contest: Codeforces - Educational Codeforces Round 84 (Rated for Div. 2)
// URL: https://codeforces.com/problemset/problem/1327/D
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h> 
using namespace std;

const int maxn = 2e5 + 7, INF = 0x3f3f3f3f;

template <typename T> inline void read(T& t) {
    int f = 0, c = getchar(); t = 0; 
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}

template <typename T> void print(T x) {
    if (x < 0) x = -x, putchar('-');
    if (x > 9) print(x / 10);
    putchar(x % 10 + 48);
} 
 
int t, n, m, ans;
int a[maxn], col[maxn], tot;
bool vis[maxn];
vector <int> cir;

inline bool work(const int k, const int len)
{
	for(int i = 0; i < k; ++ i) {
		bool flag = true;
		for(int j = i; j < len; j += k) {
			if(col[cir[i]] != col[cir[j]]) {
				flag = false;
				break;
			}
		}
		if(flag) return true;
	}
	return false;
}
 
inline int cal(int k, int len)
{
	if(work(k, len)) return k;
	return INF;
}

int main()
{
	read(t);
	while(t -- ) {  
		ans = INF;
		read(n);
		for(int i = 1; i <= n; ++ i) 
			read(a[i]), vis[i] = 0;
		for(int i = 1; i <= n; ++ i) 
			read(col[i]);
			
		for(int i = 1; i <= n; ++ i) {
			int now = i;
			if(vis[now] == 0) cir.clear();
			else continue;
			while(vis[now] == 0) {
				vis[now] = 1;
				cir.push_back(now);
				now = a[now];
			}
			int len = cir.size();
			for(int i = 1; i * i <= len; ++ i) 
				if(len % i == 0) 
					ans = min({ans, cal(i, len), cal(len / i, len)});					
		}
		print(ans);
		puts("");
	}
	return 0;
}
```


---

## 作者：MikukuOvO (赞：0)

首先我们可以将所有的环找出来，由于只要存在一个满足条件，不难发现环与环之间没有影响。

我们考虑这个$k$的意义，不难发现$k$每增加$1$，就等于将原来连向$v$的边连向了$v+1$号点。

问题就等价于对于每一个$k$，判断$0->k-1$是否存在一个$t$，使得%$k=t$的所有点颜色全部相等。

而对于这样的问题，有一个常见的套路，求所有满足条件的$k$等价于求所有满足条件的$(k,len)$，关于证明也比较简单，不难发现$gcd$相等的内部连成环的形态是相同的。

这样我们只要枚举$len$的约数然后判断即可。

复杂度$n\sqrt n$。

[$code$](https://pastebin.com/JkRGcczc)

---

## 作者：WYXkk (赞：0)

比较恶心的奇奇怪怪的题目。

这里涉及到了置换的幂次，所以我们应该先把置换循环分解。

循环分解后，对于每一个循环，很显然答案只能是它的长度的约数。

此时，我们枚举每个约数，暴力判断是否满足条件。

即，枚举 $len$ 的约数 $i$，枚举 $j=1,2\cdots,i$，假如 $c_j,c_{j+i},c_{j+2i},\cdots,c_{j+tot-i}$ 都一样则 $i$ 可能成为答案。

可以证明这么搞的时间复杂度是 $O(n^{1.5})$。

$\texttt{code:}$

```cpp
#include<cstdio>
#include<iostream>
#include<fstream>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define Set(a) memset(a,0,sizeof(a))
#define F(i,a,b) for(register int i=a,i##end=b;i<=i##end;++i)
#define UF(i,a,b) for(register int i=a,i##end=b;i>=i##end;--i)
#define openf(a) freopen(#a".in","r",stdin);freopen(#a".out","w",stdout)
#define re register
#define ri re int
#define il inline
typedef long long ll;
typedef unsigned long long ull;
template<typename T> inline T rd(T& x)
{
	T f=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(T)(c-'0');
	x*=f;
	return x;
}
ll rd(){ll x;rd(x);return x;}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int inf=1<<30;

const int N=200005;
int p[N],c[N],d[N],tot=0,n,ans;
bool vis1[N],vis2[N];
void dfs(int x)
{
	if(vis2[x]) return;
	if(vis1[x])
	{
		F(i,1,min(tot,ans-1))if(tot%i==0)
		{
			F(j,1,i)
			{
				bool f=true;
				F(k,1,tot/i-1) if(d[j+k*i]!=d[j]) {f=false;break;}
				if(f) {ans=i;break;}
			}
			if(i>=ans) break;
		}
		tot=0;return;
	}
	vis1[x]=true;d[++tot]=c[x];
	dfs(p[x]);
	vis2[x]=true;
}
int main()
{
	int T=rd();while(T--)
	{
		rd(n);ans=n;tot=0;
		F(i,1,n) rd(p[i]);
		F(i,1,n) rd(c[i]);
		F(i,1,n) dfs(i);
		cout<<ans<<endl;
		F(i,1,n) vis1[i]=vis2[i]=false;
	}
	return 0;
}
```



---

