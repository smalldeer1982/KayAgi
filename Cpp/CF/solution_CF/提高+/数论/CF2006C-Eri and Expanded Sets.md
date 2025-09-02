# Eri and Expanded Sets

## 题目描述

### 题目翻译


------------

有一个包含合法的数的集合。为了将这个集合扩展的尽可能大，Eri可以在集合中选择两个整数 $x \neq y $ ，它们的平均数 $ \frac{x+y}2 $ 是一个合法的不在集合中的数，然后把 $ \frac{x+y}2 $ 置入这个集合。整数 $ x $ 和 $ y $ 仍在这个集合中。

如果我们称这个集合为连续集，那么，当集合内的元素被排序后，相邻的两个元素之间极差为 $1$ 。例如, 集合 $ \{2\} $ , $ \{2, 5, 4, 3\} $ , $ \{5, 6, 8, 7\} $ 是连续集, 但 $ \{2, 4, 5, 6\} $ , $ \{9, 7\} $ 不是。

Eri 喜欢连续集. 假使我们有一序列 $ b $ ,  Eri 把 $ b $ 中所有的元素置入集合。 如果经过上述若干次操作后，该集合转化为了一个连续集，这个序列 $ b $ 就会被我们称作是“闪耀的”。

需要注意的是，如果一个相同的整数多次出现在序列中，我们只会把它加入集合一次，集合总是只包含合法的数。

Eri 有一个序列 $ a $ 包含 $ n $ 个合法的数。请帮他算出整数数对 $ (l,r) $ 的数量$( 1 \leq l \leq r \leq n )$ ，令子序列 $ a_l, a_{l+1}, \ldots, a_r $ 是闪耀的。

## 样例 #1

### 输入

```
6
2
2 2
6
1 3 6 10 15 21
5
6 30 18 36 9
1
1000000000
6
1 1 4 5 1 4
12
70 130 90 90 90 108 612 500 451 171 193 193```

### 输出

```
3
18
5
1
18
53```

# 题解

## 作者：liyixin0514 (赞：3)

# Eri and Expanded Sets

> 计数题。刻画合法条件。

观察到对一个集合进行操作，最后的结果一定是一个等差数列。

如果不是等差数列，则集合一定可以继续进行操作。

方差为 $1$ 或集合只有 $1$ 个数字，就是优秀的集合。

如何求最后结果的公差？首先如果相邻 $2$ 个数字的差为偶数，则可以除以 $2$。

因此首先对所有差除以若干个 $2$。

不难猜到和 $\gcd$ 有关，发现公差就是所有差的 $\gcd$。根据 $\gcd(a-b,b-c)=\gcd((a-b)+(a-c),b-c)$，直接原序列做差分然后求 $\gcd$。左端点一定时，$\gcd$ 为 $1$ 的右端点一定是一段后缀。且随着左端点上升，右端点单调不降。

因此可以预处理 $\gcd$ st 表，然后双指针。复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define sf scanf
#define pf printf
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
typedef long long ll;
namespace wing_heart {
	constexpr int N=4e5+7;
	int t,n;
	int a[N],b[N];
	int st[30][N];
	int gcd(int a,int b) { return b? gcd(b,a%b): a; }
	int getgcd(int l,int r) {
		int k=__lg(r-l+1);
		return gcd(st[k][l],st[k][r-(1<<k)+1]);
	}
    void main() {
		sf("%d",&t);
		while(t--) {
			sf("%d",&n);
			rep(i,1,n) sf("%d",&a[i]);
			if(n==1) {
				puts("1");
				continue;
			}
			rep(i,1,n-1) {
				b[i]=abs(a[i+1]-a[i]);
				while(b[i] && b[i]%2==0) b[i]>>=1;
				st[0][i]=b[i];
			}
			int lg=__lg(n-1);
			rep(k,1,lg) for(int i=1;i+(1<<k)-1<=n-1;i++) st[k][i]=gcd(st[k-1][i],st[k-1][i+(1<<(k-1))]);
			ll ans=n;
			int cnt=0;
			rep(i,1,n-1) {
				if(b[i]==0) ++cnt;
				else if(cnt) {
					ans+=1ll*cnt*(cnt+1)/2, cnt=0;
				}
			}
			if(cnt) ans+=1ll*cnt*(cnt+1)/2;
			rep(i,1,n-1) {
				int l=i,r=n-1;
				while(l<r) {
					int mid=(l+r)>>1;
					if(getgcd(i,mid)==1) r=mid;
					else l=mid+1;
				}
				if(getgcd(i,r)==1) ans+=n-r;
			}
			pf("%lld\n",ans);
		}
    }
}
int main() {
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("my.out","w",stdout);
    #endif
    wing_heart :: main();
}
```

---

## 作者：TernaryTree (赞：3)

出题人题解。考虑一个集合 $S$ 进行“扩展”操作后，得到的 $S'$ 会是什么样子。

- $S'$ 的所有元素在 $[\min\{ S\} ,\max\{S\}]$ 之间。

  显然。

- $S'$ 排序后是等差数列。

   反证，若不是等差数列，设存在三个相邻的数，在数轴上的相邻距离为 $d_1\neq d_2$。若 $d_1,d_2$ 为偶数显然不是最终状态；否则都为奇数，有 $d_1+d_2$ 是偶数，则可以生成新的数。

- $S'$ 的公差是 $S$ 相邻两项差分值的 $\gcd$ 除以 $2$ 的若干次幂。

  设公差为 $d$，设最小值为 $l$。有 $\forall i\in S, i=l+kd$。容易发现 $d$ 一定要是所有差分值的因数，即所有差分 $\gcd$ 的因数。同时发现构造出中间过程公差恰好为 $\gcd$ 是容易的，再往后只有可能将公差缩小一半。

- $S'$ 的公差是奇数。

  显然，若为偶数可以继续拓展。

- 设 $S$ 相邻两项差分值的 $\gcd$ 是 $g$，则 $S'$ 的公差是 $\dfrac{g}{\operatorname{lowbit}(g)}$。

  由上面两条结论不难得到。

于是转化为了这样一个问题：求有多少区间的 $\gcd$ 形如 $2^k$ 或 $0$。对于固定的左端点，区间 $\gcd$ 形如 $2^k$ 的 $r$ 是一段后缀；而形如 $0$ 的是一段 $l$ 开头后缀的前缀。

因为端点有单调性，貌似可以使用 baka's trick 做到比较好看的复杂度，但是我比较蠢，写了个二分 ST 表，两只 $\log$，也可以通过。

```cpp
int query(int l, int r) {
	int d = __lg(r - l + 1);
	return __gcd(st[d][l], st[d][r - (1 << d) + 1]);
} 

bool check(int x) {
	return x && (x & -x) == x;
}

void fake_main() {
	n = read(), ans = n;
	rep(i, 1, n) a[i] = read();
	rep(i, 1, n - 1) st[0][i] = b[i] = abs(a[i] - a[i + 1]);
	rep(d, 1, maxd - 1) rep(i, 1, n - (1 << d)) st[d][i] = __gcd(st[d - 1][i], st[d - 1][i + (1 << d - 1)]);
	rep(i, 1, n - 1) {
		if (check(query(i, n - 1))) {
			int l = i, r = n - 1;
			while (l < r) {
				int mid = l + r >> 1;
				if (check(query(i, mid))) r = mid;
				else l = mid + 1;
			}
			ans += n - l;
		}
		if (!b[i]) {
			int l = i, r = n - 1;
			while (l < r) {
				int mid = l + r + 1 >> 1; 
				if (!query(i, mid)) l = mid;
				else r = mid - 1;
			}
			ans += l - i + 1;
		}
	}
	write(ans), pc('\n'); 
}
```

---

## 作者：wrkwrkwrk (赞：1)

相关人员：验题人

------------
考虑在数轴上插入数，每次插入一个数进行更新答案。

显然，所有偶数的间隔都可以变成奇数。考虑剩下的更新。

若连续两个奇数间隔分别为 $a,b$，$a< b$，则间隔 $\frac{a+b}2$ 在其中。取 $a$ 所在段，则由于辗转相除法得知，得到其中所有间隔为其中 $\gcd$ 的所有段。

若合并两个串，则考虑插入两个端点和其中间隔，这样可以得到合并之后的答案。

以上可以用 $(l,r,c)$ 的三元组表示，用 $ST$ 表预处理和计算。特别的，$c$ 等于 $0$ 需要特判。

之后考虑如何计算答案：要么一共只有一个数，要么间隔 $=1$。

对第一类直接统计连续段，对第二类枚举左端点，二分右端点的最小值计算答案。

时间复杂度 $O( n \log^2 n)$。

验题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace _wrk{;
#define int long long

struct w{
	int l,r,le;
	void insert(int w){
		int a=l%le,aa=w%le;
		if(a>aa)swap(a,aa);
		int x=__gcd(aa-a,le-(aa-a));
		le=__gcd(le,x);
		l=min(l,w);
		r=max(r,w);
	}
};
w operator+(w a,w b){
	if(a.l==a.r){
		if(b.l==b.r){
			if(a.l==b.l)return a;
			w ans={min(a.l,b.l),max(a.l,b.l),max(a.l,b.l)-min(a.l,b.l)};
			while(ans.le%2==0)ans.le>>=1;
			return ans;
		}
		b.insert(a.l);
		return b; 
	}
	if(b.l==b.r)return b+a;
	w c=a;
	c.insert(b.l);
	c.insert(b.r);
	c.le=__gcd(c.le,b.le);
	return c;
}
w p[500005][21];
int a[500005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			p[i][0]={a[i],a[i],0};
		}
		for(int k=1;k<=20;k++){
			for(int i=1;i+(1ll<<k)-1<=n;i++){
				p[i][k]=p[i][k-1]+p[i+(1ll<<(k-1))][k-1];
			}
		}
		int ans=0;
		int c=1;
		a[n+1]=a[n]+1e9;
		for(int i=2;i<=n+1;i++){
			if(a[i]!=a[i-1]){
				ans+=c*(c+1)/2;
				c=1;
			}else{
				c++;
			}
		}
		for(int i=1;i<=n;i++){
			int f=i+1;
			w now={a[i],a[i],0};
			for(int k=20;k>=0;k--){
				while(f+(1ll<<k)-1<=n&&(now+p[f][k]).le!=1){
					now=now+p[f][k];
					f+=(1ll<<k);
				}
			}
			ans+=n+1-f;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
}
signed main(){
	   return _wrk::main();
}
```

---

## 作者：acb437 (赞：0)

# 题解：[CF2006C Eri and Expanded Sets](https://www.luogu.com.cn/problem/CF2006C)
## 题目大意
定义对于一个集合 $T\subset\mathbb{Z}^+$ 是连续的，当且仅当 $\forall_{\min\{T\}\le x\le \max\{T\}}x\in T$。定义一个集合 $S\subset\mathbb{Z}^+$ 是闪耀的，当且仅当它可以通过下列操作变成连续的：选出两个数 $x\in S$ 和 $y\in S$，定义 $z=\frac{x+y}{2}$，如果 $z\in\mathbb{Z}^+$ 并且 $z\notin S$，那么就将 $z$ 加入集合 $S$。

给出一个长为 $n$ 的数列 $a$，求 $a$ 中有多少个子区间 $[l,r]$ 满足 $\{a_i\mid l\le i\le r\}$ 是闪耀的。

## 解法
集合这一概念并无特殊性，而且询问中也是对于数列考虑的，那么把集合转成升序的数列考虑。先手算几组情况，观察出一个结论：对于任意数列 $A$，设它可以生成的最终数列（经过若干次操作后无法再进行任何一次操作了）为 $A'$，那么 $A'$ 一定是一个等差数列。这个结论可以进行如下证明：
   1. $A'$ 中相邻两个数之间的差为奇数，否则可以继续操作。
   2. 反证法，如果不构成等差数列，那么：
      1. 存在相邻的三个数 $x,y,z$ 满足 $y-x$ 和 $z-y$ 不相等且为都奇数。
      2. 于是 $z-x=(y-x)+(z-y)$ 为偶数，并且 $\frac{x+z}{2}$ 不在 $A'$ 中（因为 $x$ 和 $z$ 中间只有 $y$，而 $y\neq \frac{x+z}{2}$。
      3. 可以继续操作，将 $\frac{x+z}{2}$ 插进去，所以 $A'$ 不是最终数列，与预设条件矛盾。

综上所述，$A'$ 一定是一个等差数列。设其首项为 $l$，公差为 $d$，那么 $\forall_{1\le i\le n}A_i=l+k_i d$，所以 $d$ 一定为 $\gcd\{A_{i+1}-A_i=k_{i+1} d-k_i d\mid 1\le i<n\}$ 的因数。但是在询问中区间中的数并不保证有序，但是这并不影响这一点，因为是否 $A$ 有序影响的只是 $k_i$ 是否有序而已，做差时加上一个绝对值即可。

接下来是一个重要结论，设 $g=\gcd\{a_{i+1}-a_i=k_{i+1} d-k_i d\mid 1\le i<n\}$，那么 $d=\frac{g}{lowbit(g)}$，这个结论可以这样证明：
   1. 对于任意数列 $A$，可以构造方案产生一个 $A''$ 满足 $A''$ 是一个首项为 $l$，公差为 $g$ 的等差数列，证明如下：
      1. 对于 $A$ 中的任意两个数 $l+k_x g$ 和 $l+k_y g$，它们可以形成的数为 $l+\frac{k_x+k_y}{2} g$。
      2. 可以看出，$g$ 的大小在此时没有影响，所以考虑 $g=1$ 的情况。
      3. $g=1$，那么 $d$ 也只能等于 $1$，$A'$ 就是符合条件的 $A''$，显然可以推广到所有 $g$，得证。
   2. 显然对于这样的一个等差数列，可以每次相邻两项进行操作，每次使一个间隔变为原先的 $\frac{1}{2}$，就可以得到目标中的、无法进一步扩展的数列 $A'$ 了。

如此，我们就知道对于一个闪耀的集合应该满足什么条件了：相邻两个数的差的 $\gcd$ 的形式为 $2^k$ 或者为 $0$（只有一个数当然是闪耀的）。所以我们需要找到符合这一条件的区间个数。

容易发现对于同一个左端点，满足前一个条件的右端点是一个后缀，$\gcd$ 具有单调性嘛，用二分 + st 表算即可。而满足后一个条件的就是一个从左端点开始的前缀了，可以双指针求极长连续段，或者也可以二分。

## 代码
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 4e5 + 5;
int t, n, a[N];ll ans;
int lowbit(int x){return x & (-x);}
int abs(int a){return a > 0 ? a : -a;}
int gcd(int a, int b){return b ? gcd(b, a % b) : a;}

int lg2[N], st[N][20];
void init()
{
    lg2[0] = -1;
    for(int i = 1;i <= n;i++)st[i][0] = abs(a[i + 1] - a[i]), lg2[i] = lg2[i >> 1] + 1;
    for(int j = 1;j < 20;j++)
        for(int i = 1;i + (1 << j) <= n;i++)
            st[i][j] = gcd(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
}
int query(int l, int r){int k = lg2[r - l + 1];return gcd(st[l][k], st[r - (1 << k) + 1][k]);}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n), ans = 0;
        for(int i = 1;i <= n;i++)scanf("%d", &a[i]);a[n + 1] = a[n] + 1e9, init();
        for(int s = 1;s <= n;s++)
        {
            int l = s + 1, r = n, res = n + 1;
            while(l <= r)
            {
                int m = (l + r) >> 1, val = query(s, m - 1);
                if(lowbit(val) == val && val)res = m, r = m - 1;
                else l = m + 1;
            }
            ans += n - res + 1;
            l = s + 1, r = n, res = s;
            while(l <= r)
            {
                int m = (l + r) >> 1, val = query(s, m - 1);
                if(!val)res = m, l = m + 1;
                else r = m - 1;
            }
            ans += res - s + 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

