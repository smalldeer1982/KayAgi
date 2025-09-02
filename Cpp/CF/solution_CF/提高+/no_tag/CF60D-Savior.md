# Savior

## 样例 #1

### 输入

```
1
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
2
3 5
```

### 输出

```
1
```

# 题解

## 作者：Jesselrj (赞：4)

首先证明一下勾股数公式的正确性。

$a = n^2 - m^2$， $b = 2nm$， $c = n^2 + m ^2$

证明: 当$(a,b) = 1$时，如果$a,b$均为奇数, 则有$a^2+b^2\equiv 2\pmod{4}$，此时产生矛盾，$∴a$，$ b$间必有一数为偶数，不妨设$b =2k$。

$∵b^2 = c^2 - a^2$，

$∴$ 原式可等化为$4k^2 = (c+a)(c-a)$

显然右式为偶数，设$M = \frac{c+a}{2}$，$N = \frac{c-a}{2}$，显然，$N,M\in \mathbb{Z}^{+}$

若存在一质数$p$ 使得 $p|M$，$p|N$，则有$p|M+N(=c)$, $p|N-M(=a)$，从而，$p|c$，$p|a$，$∴p|b$，此时与$(a,b)=1$产生矛盾，$∴(M,N)=1$

根据算术基本定理，$k^2=p_1^{a_1}×p_2^{a_2}×p_3^{a_3}×…$，其中$a_1,a_2,a_3…$均为偶数，$p_1,p_2,p_3…$均为质数

若对于某个$p_i$，$M$的$p_i$因子个数为奇数个，则$N$所对应的$p_i$因子必为奇数个（否则加起来不为偶数），从而$p_i|M$，$p_i|N$，$(M,N)=p_i>1$与刚才的证明矛盾，$∴$对于所有质因子，$p_i^2|M$，$p_i^2|N$，即$M$，$N$都是平方数。

设$M=m^2$，$N=n^2$，从而有

$c+a = 2m^2$

$c-a = 2n^2$
 
(不会打大括号.....) 
  
 解得：

$c = n^2+m^2$

$a = n^2-m^2$
  
从而，$b = 2nm$。

证明出勾股数公式的正确性后，这道题就是一道大水题了，直接枚举勾股数，然后用并查集算连通块个数就完事了。

$\mathbb{code:}$
```cpp
#include <bits/stdc++.h>
#define Maxn 10010000
#define ll long long
using namespace std;

int fa[Maxn], n, ans; 

int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y) {
	if (!fa[x] || !fa[y]) return ;
	x = find(x), y = find(y);
	if (x == y) return ;
	fa[x] = y, ans--;
}

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

int main() {
	cin >> n, ans = n;
	for (int i = 1, x; i <= n; i++)
		scanf("%d", &x), fa[x] = x;
	for (ll y = 1; y <= 1e7; y++) {
		for (ll x = y + 1; 2 * x * y <= 1e7 && x * x - y * y <= 1e7; x++) {
			ll a = x * x - y * y, b = 2 * x * y, c = x * x + y * y;
			if (gcd(a, b) == 1) {
				merge(a, b);
				if (c <= 1e7) {
					merge(a, c);
					merge(b, c);
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：黑影洞人 (赞：1)

题意：

>给你一堆数（单个组成连通块），若两两可以组成原始勾股数的其中两个那么合并，问你最后有多少个连通块。

首先，我们可以很快的码出模拟的代码：

只需要记录一下原始的数，然后开始枚举平方数，不断刷新答案。

```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<map>
#define N 10000007
#define int long long
using namespace std;
int f[N],mx,ans,a[N];
int n;
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	if(!x||!y)return;
	f[x]=y;ans--;
}
map<long long,bool>mp;
signed main(){
	scanf("%lld",&n);ans=n;
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		mx=max(mx,a[i]);
		mp[a[i]]=1;
		f[a[i]]=a[i];
	}
	for(int i=1;i<=min((int)1e14,mx*mx);i+=2*sqrt(i)+1){
		for(int j=1;j<=n;j++){
			double chk=sqrt(i+a[j]*a[j]);
			int now=sqrt(i+a[j]*a[j]);
			if(chk!=now)continue;
			if(now==0)continue;
			if(now==i)continue;
			if(now==a[j])continue;
			if(i==a[j])continue;
			if(__gcd(a[j],now)==1&&mp.find(now)!=mp.end())merge(a[j],now);
		}
	}
	for(int i=1;i<=min((int)1e14,mx*mx);i+=2*sqrt(i)+1){
		for(int j=1;j<=n;j++){
			double chk=sqrt(i+a[j]*a[j]);
			int now=sqrt(i+a[j]*a[j]);
			if(chk!=now)continue;
			if(now==0)continue;
			if(now==i)continue;
			if(now==a[j])continue;
			if(i==a[j])continue;
			if(__gcd(a[j],i)==1&&mp.find(now)!=mp.end())merge(a[j],now);
		}
	}
	for(int i=1;i<=min((int)1e14,mx*mx);i+=2*sqrt(i)+1){
		for(int j=1;j<=n;j++){
			double chk=sqrt(a[j]*a[j]-i);
			int now=sqrt(a[j]*a[j]-i);
			if(chk!=now)continue;
			if(now==0)continue;
			if(now==i)continue;
			if(now==a[j])continue;
			if(i==a[j])continue;
			if(__gcd(a[j],i)==1&&mp.find(now)!=mp.end())merge(a[j],now);
		}
	}
	printf("%lld",ans);
	return 0;
}
```
当然这种方法复杂度高达 $O(na_{max})$ 显然是行不通的。

我们考虑对数字进行分解。

$$a^2+b^2=c^2,a,b,c\in Z$$

珂以被拆做：

$$(i^2-j^2)^2+4i^2j^2=(i^2+j^2)^2,i,j\in Z$$

显然，$a=|i^2-j^2|,b=2ij,c=i^2+j^2$

我们令 $j>i$，那么不断枚举 $i$ ,同时枚举 $j$，处理一下 $j$ 上限问题。

那么最高复杂度为 $O(n^{\frac{5}{4}}\times \log n)$

上代码：

```cpp
#include<cstdio>
#include<algorithm>
#define N 10000007
#define int long long
using namespace std;
bool mp[N*2];
int f[N],ans,n,mx;
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
void merge(int x,int y){
	int u=x,v=y;
	x=find(x),y=find(y);
	if(x==y)return;
	if(!x||!y)return;
	printf("%lld %lld\n",u,v);
	f[x]=y;ans--;
}
signed main(){
	scanf("%lld",&n);
	ans=n;
	for(int i=1;i<=n;i++){
		int x;
		scanf("%lld",&x);
		f[x]=x;
		mp[x]=1;
		mx=max(mx,x);
	}
	for(int i=1;i<=mx;i++){
		for(int j=i+1;2*i*j<=1e7&&j*j-i*i<=1e7;j++){
			int a=j*j-i*i,b=2*i*j,c=i*i+j*j;
			if(mp[a]+mp[b]+mp[c]<2)continue;
			if(__gcd(a,b)==1){
				merge(a,b);
				if(c<=1e7){
					merge(a,c);
					merge(b,c);
				}
			}
		}
	}
	printf("%lld",ans);
	return 0;
}

```

观察代码发现，实际上有很多优化工作珂以做。

例如先设置好 $mx$ 来枚举 $i$ 的上界，开一个 $mp$ 数组 
看上去复杂度很大的样子，实际上我们枚举的时候珂以加一些剪枝。
 
如：
```
if(mp[a]+mp[b]+mp[c]<2)continue;

```
珂以是复杂度趋近于 $O(n^{\frac{5}{4}})$ 乘以一个小常数，总体下来效率还是很高的。

于是拿下了最优解。






---

## 作者：LJB00131 (赞：1)

对于所有的"可以传递"的，只需要放一个。所以题目让我们求的是联通块个数。

我们知道枚举勾股数的公式 $a = x^2 - y^2, b = 2xy , c = x^2 + y ^2$

当a, b 互质时，对于a的任意质因子p， 有$b^2 \equiv c^2$，所以显然$c^2 $与a互质， a与c互质

同理，b与c互质。

所以只需要枚举所有x, y, 判断一下a, b是否互质，再用并查集求一下联通就可以了

```cpp
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
#define N 10000005

int n, f[N], ans = 0;

int find(int x)
{
	return (f[x] == x) ? x : f[x] = find(f[x]);
}

int gcd(int x, int y) {return (y == 0) ? x : gcd(y, x % y);}

void connect(int a, int b)
{
	int fx = find(a), fy = find(b);
	if(fx != fy)
	{
		ans--;
		f[fy] = fx;
	}
}

int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		f[x] = x;
	}
	ans = n;
	int maxn = 1e7;
	for(ll y = 1; y <= maxn; y++)
		for(ll x = y + 1; (x * x - y * y <= maxn && 2 * x * y <= maxn); x++)
		{
			ll a = 2 * x * y, b = x * x - y * y, c = x * x + y * y;
			if(gcd(a, b) == 1)
			{
				if(f[a] && f[b])
					connect(a, b);
				if(c <= maxn)
				{
					if(f[a] && f[c])
						connect(a, c);
					if(f[b] && f[c])
						connect(b, c);
				}
			}
		}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：MaxDYF (赞：1)

这题真的神题，$Google$上竟然一篇题解都没有……

对于$a^2+b^2=c^2$， 当我们取$a=x^2-y^2, b=2xy$时，原式左边变为：

$(x^2-y^2)^2+(2xy)^2 = x^4+2x^2y^2+y^4=(x^2+y^2)^2$

此时$c=x^2+y^2$

也就是说，我们可以枚举$x,y$，当满足其中两个互质时，我们把它们并入同一个集合。

合并集合我们可以用并查集直接搞。

时间复杂度是$O(\sum_{i=1}^{MaxNum}{log(N)\sqrt{i}}) \approx O(MaxNum*log(N)\sqrt{\frac{MaxNum}{2}})$,实际上应该达不到上界，可以通过此题。

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
int ans;
// 并查集
int father[(int)1e7 + 10];
int get(int x) 
{
    return father[x] == x ? x : father[x] = get(father[x]);
}
void get_union(int x, int y)
{
    x = get(x);
    y = get(y);
    if(x != y)
    {
        ans--;
        father[x] = y;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1, x; i <= n; i++)
    {
        cin >> x;
        father[x] = x;
    }
    ans = n;
    int max_num = 1e7;
    for(long long y = 1; y <= max_num; ++y)
    {
        for(long long x = y + 1; (x * x - y * y) <= max_num && (2 * x * y) <= max_num; ++x)
        {
            long long a = x * x - y * y, b = 2 * x * y, c = (x * x + y * y);
            if(__gcd(a, b) == 1)
            {
                if(father[a] && father[b])
                    get_union(a, b);
                if(c <= max_num)
                {
                    if(father[a] && father[c])
                        get_union(a, c);
                    if(father[b] && father[c])
                        get_union(b, c);
                }
            }
        }
    }
    cout << ans << endl;
    system("pause");
}
```

---

## 作者：PosVII (赞：0)

## 前言

不出意料的话真的应该是退役前的最后一篇题解了。

## 题解

这道题本身比较简单：直接枚举勾股数然后进行联通块计数即可。

关于这道题直接暴力做为什么是对的，可以手动打表发现勾股数对数量大概是 $O(n)$ 级别。如果你做过 [Min25 出的勾股数对计数](https://www.luogu.com.cn/problem/SP19913) 可以直接跑一遍代码发现在 $V \leq 10^7$ 时数对有 $2.3 \times 10^7$ 个。

尝试理解一下它的数量级，我们已知一个结论：

设斜边为 $c$，若

$c = 2^e \prod_{p_i = 4k + 1 } p_i^{k_i} \prod_{p_i = 4k + 3 } p_i^{k_i}$。

它对答案的贡献为 $\frac{\prod_{i}{2k_i + 1} - 1}{2}$。

感性理解一下函数增长的速度，它在 $n$ 较小时候贡献并不大，大概是 $O(n \log \log n)$ 级别。

---

## 作者：hxhhxh (赞：0)

## 大意

给定 $ n $ 格子里的 $ n $ 个数，两个格子联通当且仅当两个格子上的数能与另一个正整数形成本原勾股数（三数互质的勾股数），求共有多少个联通块。（所有数各不相同）

## 思路

首先，[~~由百度知~~](https://baike.baidu.com/item/%E5%8B%BE%E8%82%A1%E6%95%B0/2674064)本原勾股数可以表示成 $ (x,y,z) = (n^2-m^2,2nm,n^2+m^2) $，$ (n+m \equiv 1( \bmod 2) \;,\;\gcd(x,y)=1),m < n $ 的形式。

然后，题目里说所有数各不相同，并且 $ a_i \leq 10^7 $，所以可以把所有 $ a_i $ 放在一个`vis`数组里，然后用并查集维护联通块。

记 $ m = \max_{i=1}^n a_i $，对于 $ 2 \leq i \leq 1 $，枚举 $ 1 \leq j < i $，检查 $ (i^2-j^2,2ij,i^2+j^2) $ 是否满足条件，如果满足，将其中 $ \leq m $ 的数分别合并（如果出现过至少两个，把出现过的两两合并）。时间复杂度 $ O(m^2) = O(10^{14}) $，不可能不会`TLE`。

发现对于同样的 $ i $，$ 2ij $ 和 $ i^2+j^2 $ 随着 $ j $ 的增加而单增，所以当 $ 2ij > m $ 且 $ i^2+j^2 > m $ 时就可以不用管了。又因为 $ i^2+j^2-2ij\geq 0 $，所以 $ 2ij \leq i^2+j^2 $，所以只用判断 $ 2ij $ 与 $ m $ 的大小关系。

时间复杂度 $ O(\sum_{i=1}^m \frac{m}{2i} ) \approx O(\frac{1}{4} m \sqrt m) \approx 7.9 \times 10^{9} $，跑不满，能过。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,f[10000007],a[1000006],ans,mx;
bool vis[10000007];
int find(const int&x){
	return f[x]==x?x:f[x]=find(f[x]);
}
inline bool ck(const int&a,const int&b){
	return a<=mx&&b<=mx?vis[a]&&vis[b]&&find(a)!=find(b):false;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]),vis[a[i]]=true,mx=max(mx,a[i]);
	for(int i=1;i<=mx;i++) f[i]=i;
	for(int i=2;i<=mx;i++){
		for(int j=1;j<i&&2*i*j<=mx;j++){
			if(i*i-j*j>mx) continue;
			int x=2*i*j,y=i*i-j*j,z=i*i+j*j;
			if(__gcd(x,y)!=1) continue;
			if(ck(x,y)){
				f[find(x)]=find(y);
				ans++;
			}
			if(ck(x,z)){
				f[find(x)]=find(z);
				ans++;
			}
			if(ck(y,z)){
				f[find(y)]=find(z);
				ans++;
			}
		}
	}
	cout<<n-ans;
} 
```

---

