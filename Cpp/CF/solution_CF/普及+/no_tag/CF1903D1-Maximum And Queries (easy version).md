# Maximum And Queries (easy version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is the constraint on $ n $ and $ q $ , the memory and time limits. You can make hacks only if all versions of the problem are solved.

Theofanis really likes to play with the bits of numbers. He has an array $ a $ of size $ n $ and an integer $ k $ . He can make at most $ k $ operations in the array. In each operation, he picks a single element and increases it by $ 1 $ .

He found the maximum [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) that array $ a $ can have after at most $ k $ operations.

Theofanis has put a lot of work into finding this value and was very happy with his result. Unfortunately, Adaś, being the evil person that he is, decided to bully him by repeatedly changing the value of $ k $ .

Help Theofanis by calculating the maximum possible [bitwise AND](https://en.wikipedia.org/wiki/Bitwise_operation#AND) for $ q $ different values of $ k $ . Note that queries are independent.

## 说明/提示

In the first test case, in the first query, we add $ 1 $ in the first and last elements of the array.

Thus, the array becomes $ [2,3,7,6] $ with bitwise AND equal to $ 2 $ .

In the second test case, in the first query, we add $ 1 $ in the first element, $ 5 $ in the second, and $ 3 $ in the third and now all the elements are equal to $ 5 $ .

## 样例 #1

### 输入

```
4 2
1 3 7 5
2
10```

### 输出

```
2
6```

## 样例 #2

### 输入

```
3 5
4 0 2
9
8
17
1
3```

### 输出

```
5
4
7
0
1```

## 样例 #3

### 输入

```
1 2
10
5
2318381298321```

### 输出

```
15
2318381298331```

# 题解

## 作者：tbdsh (赞：6)

# 题意简述
[洛谷原题面](//www.luogu.com.cn/problem/CF1903D1)

[CodeForces 原题面](//codeforces.com/problemset/problem/1903/d1)

给定长度为 $n$ 的数组 $a$。

有 $q$ 次询问，每次询问给定 $k$。定义一次操作为选择一个 $i$ 然后 $a_i\gets a_i+1$。

问当你进行最多 $k$ 次操作后，你能达到的数组 $a$ 的按位与的最大值。


# 分析
注意到本题的特殊数据范围：$1\le n\times q \le 10^5$，所以我们考虑按照每一位进行贪心。

可以发现 $2^{60}\ge10^{18}$，所以我们只需要枚举 $60$ 位即可。

那么，我们如果要得到答案 $2^i$，那么就需要所有数二进制下表示的第 $i + 1$ 位都为 $1$。

所以我们就判断所有数修改到满足二进制下表示的第 $i+1$ 位为 $1$ 需要进行的操作数的和 $p\ge k$ 即可。如果满足，那么进行修改，同时 $k\gets k-p$。

时间复杂度：$O(n\times q)$。

空间复杂度：$O(n)$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 1e5 + 5;
int n, q, a[MAXN], b[MAXN], c[MAXN];
void Solve(){
  cin >> n >> q;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
  }
  while (q--){
    int x, ans = 0;
    cin >> x;
    for (int i = 1; i <= n; i++){
      b[i] = a[i];
    }
    for (int i = 60; i >= 0; i--){
      int p = 1ll << i, cnt = 0;
      for (int j = 1; j <= n; j++){
        c[j] = b[j];
      }
      for (int j = 1; j <= n; j++){
        if (!((b[j] >> i) & 1)){
          int p = ((b[j] >> i) + 1) << i;
          cnt += p - b[j];
          b[j] = p;
        }
        if (cnt > x){
          break;
        }
      }
      if (cnt <= x){
        x -= cnt;
      }else {
        for (int j = 1; j <= n; j++){
          b[j] = c[j];
        }
      }
    }
    ans = b[1];
    for (int i = 1; i <= n; i++){
      ans &= b[i];
    }
    cout << ans << '\n';
  }
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t = 1;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：FQR_ (赞：6)

## 题目大意

给定一个长度为 $n$ 的序列 $a$。共 $q$ 次询问，每次询问给出整数 $k$，表示最多可以进行 $k$ 次操作。在每次操作中，可以任选序列中的一个数字，并将它增加 $1$。问经过至多 $k$ 次操作后，整个序列所有数字**按位与**的结果的最大值。

## 思路

我们可以将数字表现为二进制形式。我们知道，若想使答案的第 $i$ 位为 $1$，那么序列中所有数字的第 $i$ 位都应该是 $1$。我们可以贪心，从高位向低位枚举，如果答案的第 $i$ 位可以变成 $1$，那么我们就通过若干次操作，使序列中所有数字的第 $i$ 位都变成 $1$，此时答案的第 $i$ 位也就变成了 $1$。

假设当前在枚举第 $i$ 位。如果序列中存在一个数字，它在比 $i$ 更高的位上的数字是 $1$，那么无论如何加，这一位都不会对第 $i$ 位产生影响，所以我们只保留数字前 $i$ 位。假设一个数字的第 $i$ 位是 $1$，那么就不需要任何操作。如果第 $i$ 位是 $0$，那么我们可以将它变成 $2^i$，操作次数即为 $2^i$ 减去这个数字。

假设使答案的第 $i$ 位变为 $1$ 的操作次数为 $p$，剩余的操作次数为 $k$。如果 $p\le k$，那么我们就可以将答案的第 $i$ 位变成 $1$，于是我们将第 $i$ 位是 $0$ 的数字变成 $2^i$，并将 $k$ 减去 $p$。如果 $p>k$，我们没办法将答案的第 $i$ 位变成 $1$，于是我们不需要做任何事。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n' 
#define ll long long
namespace Main
{
    int n, q;
    int a[100010], aa[100010];
    void solve()
    {
        ll k;
        cin >> k;
        for(int i = 1; i <= n; i++) a[i] = aa[i];//a 数组会发生改变，所以我们要把它复原
        ll ans = 0;
        for(ll i = 62; i >= 0; i--)
        {
            ll p = 0;
            bool flg = 0;
            for(int j = 1; j <= n; j++)
            {
                if((a[j] & (1ll << i)) == 0)//如果 a[j] 的第 i 位是 0
                {
                    p += (1ll << i) - a[j];
                    if(p > k) break;//注意要不停判断 p 是否大于 k，否则 p 可能会超出 long long 范围
                }
            }
            
            if(p <= k)//如果可以将答案的第 i 位变成 1
            {
                ans += (1ll << i), k -= p, flg = 1;//记录答案，将 k 减少 p
            }
            for(int j = 1; j <= n; j++)
            {
                if((a[j] & (1ll<<i)) == 0 && flg) a[j] = 1ll << i;//如果 a[j] 的第 i 位是 0，且可以将答案的第 i 位变成 1，就将 a[j] 变成 2^i
                if((a[j] & (1ll<<i)) != 0)
                    a[j] -= (1ll << i);//如果 a[j] 的第 i 位是 1，就把这一位清除，因为接下来这个 1 不会对更小的数位产生影响
            }
        }
        cout << ans << endl;
    }
    void main()
    {
        ios::sync_with_stdio(0);
        cin.tie(0);cout.tie(0);
        cin >> n >> q;
        for(int i = 1; i <= n; i++) cin >> a[i], aa[i] = a[i];
        while(q--) solve();
    }
};

signed main()
{
    Main::main();
    return 0;
}
```

---

## 作者：Big_Dinosaur (赞：1)

模拟赛试题，考场通过。

考虑贪心，尽可能让高位获得 $1$。为了让第 $i$ 位得到 $1$，需要加 $\sum^{n}_{j=1}(2^j-a_j)[2^j>a_j]$ 次，记为 $ans$，如果 $ans\le k$，则对这位操作，总次数减 $ans$，并且对 $2^j>a_j$ 的 $j$，使 $a_j$ 变为 $0$。从大到小枚举 $i$，判断是否合法，合法进行上面操作，答案加 $2^i$，此外再对每一个 $a_j$ 对 $2^i$ 取模。

下面是代码。
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define rep(j,y,a)for(int j=(y);j<=(a);++j)
using namespace std;
namespace io {
	inline int r() {
		int J=1,Y=0;
		char A=getchar();
		while(A<'0'||A>'9') {
			if(A=='-')J=-1;
			A=getchar();
		}
		while(A>='0'&&A<='9') {
			Y=(Y<<1)+(Y<<3)+(A^48);
			A=getchar();
		}
		return Y*J;
	}
	inline void wi(int N) {
		if(N<0) {
			N=-N;
			putchar('-');
		}
		if(N!=0)wi(N/10),putchar(N%10+48);
	}
	inline void ww(int a) {
		if(a==0)putchar('0');
		else wi(a);
		putchar(' ');
	}
	inline void wln(int a) {
		if(a==0)putchar('0');
		else wi(a);
		putchar('\n');
	}
	inline void w(int a) {
		if(a==0)putchar('0');
		else wi(a);
	}
}
namespace dino {
	using namespace io;
	int a[113],n,q,k,Ans,ss,s,b[114514],C[114514],c,T;
	inline int lg2(int m) {
		rep(i,0,62)if((int)pow(2,i)>=m)return i;
	}
	inline void p(int k) {
		ss=s;
		T=0;
		for(int i=max(lg2((k+ss)/n)+1,30ull); i; --i) {
			Ans=0;
			c=pow(2,i);
			rep(i,1,n)if(c>C[i])Ans+=c-C[i];
			if(Ans<=k) {
				T+=c,k-=Ans;
				rep(i,1,n)if(c>C[i])C[i]=0;
			}
			rep(i,1,n)if(c<=C[i])C[i]-=c;
		}
		Ans=0;
		c=1;
		rep(i,1,n)if(c>C[i])Ans+=c-C[i];
		if(Ans<=k)T+=c,k-=Ans;
		wln(T);
	}
	inline void _() {
		n=r(),q=r();
		rep(i,1,n) {
			b[i]=r();
			s+=b[i];
		}
		rep(o,1,q) {
			k=r();
			for(int i=1; i<=n; ++i)C[i]=b[i];
			p(k);
		}
	}
}
signed main() {
	dino::_();
}
```
注意，计算 $0$ 次方用 pow 会 CE。

---

## 作者：AKPC (赞：1)

$nq\leq10^5$ 为 Easy Version 突破点。

考虑枚举每个二进制位，即每个 $2^i$，$i$ 从 $60$ 枚举到 $0$（大了容易爆 `long long`）。

因为比较两个数的大小关系是由高位到低位决定，所以贪心地想如果高位能够通过操作达到 $\text{and}$ 值对应的这一位为 $1$，就一定要让这一位达到 $1$。

然后这题统计一下就做完了。

[code](/paste/0nyc7bbh)

---

## 作者：蒟蒻君HJT (赞：1)

注意到 $nq$ 很小，考虑对每个询问按位贪心。

简单计算得二进制表示下，最终答案的最高位不会超过 $2^{59}$。因为 $2^{60}-10^6>10^{18}$。

从 $2^{59}$ 这一位一直遍历到 $2^{0}$ 这一位，假设当前在考虑 $2^i$ 是否能在答案中出现。可以模拟当前所有数补到存在 $2^i$ 这一位的代价之和，与目前能进行的操作次数比较即可。如果能的话，剩余操作次数减去总代价，并更新答案和所有数的值。

具体来说，设某个数为 $x$，令 $y:=x\pmod {2^{i+1}}$。若 $y\geq 2^i$，说明 $x$ 有 $2^i$ 这一位，代价是 $0$，否则代价为 $2^i-y$。

有一个坑点（笔者因此 WA 了一发）：求和可能会爆 long long。一种解决办法是用 \_\_int128 代替。另一种解决办法是当总和大于 $10^{18}$ 时，直接退出报不合法就行。

时间复杂度是 $\Theta(nq\log K)$。

[for reference only.](https://codeforces.com/contest/1903/submission/235095674)

---

## 作者：Tiago (赞：0)

## Solution

考虑按位贪心。

简单计算发现 $2^{60}>10^{18}$，所以我们从 $60$ 倒着枚举。

对于每一位，我们发现要使最终答案的当前位为 $1$，则一定要保证所有数的当前位全部为 $1$，所以我们可以考虑要使所有数的当前位为 $1$ 需要进行的操作数，再与 $k$ 判断大小，若大则 $k$ 减掉继续，若小则忽略当前位，最终计算最终结果（我们不需要全部使用 $k$ 次操作）。

注意多定义几个数组临时存放数据。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define FOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define int long long

const int N=1e5+4;
int n,a[N],b[N],c[N];
void solve()
{
	int k;cin>>k;
	For(i,1,n)a[i]=b[i];
	FOR(w,60,0)
	{
		For(i,1,n)c[i]=a[i];
		int cnt=0;
		For(i,1,n)
		{
			if((a[i]>>w)%2==0)
			{
				int p=((a[i]>>w)+1)<<w;
				cnt+=p-a[i];
				a[i]=p;
			}
			if(cnt>k)break;
		}
		if(cnt<=k)k-=cnt;
		else For(i,1,n)a[i]=c[i];
	}
	int ans=a[1];
	For(i,2,n)ans&=a[i];
	cout<<ans<<"\n";
}
signed main()
{
	IOS;
	int q;cin>>n>>q;
	For(i,1,n)cin>>a[i],b[i]=c[i]=a[i];
	while(q--)solve();

	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
若 $a_i$ 的与结果中第 $i$ 位是 $1$，则必须每个 $a_i$ 的第 $i$ 位都是 $1$。然后我们只需要从高位开始枚举 $i$，如果次数足够那就操作，否则就不操作。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, q;
ll k, a[100005], b[100005], c[100005], s, ans;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> q;
	for (int i = 0; i < n; ++ i)
		cin >> a[i];
	while (q --) {
		cin >> k;
		for (int i = 0; i < n; ++ i)
			b[i] = a[i];
		for (int i = 60; ~i; -- i) {
			s = 0;
			for (int j = 0; j < n; ++ j)
				if (b[j] >> i & 1)
					c[j] = b[j];
				else {
					c[j] = (b[j] >> i) + 1 << i;
					s += c[j] - b[j];
					if (s > k)
						goto end;
				}
			k -= s;
			for (int j = 0; j < n; ++ j)
				b[j] = c[j];
end:
			;
		}
		ans = b[0];
		for (int j = 1; j < n; ++ j)
			ans &= b[j];
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

~~Hard Version 不会写，所以就来 Easy Version 水一篇题解。~~

本题贪心。

这题我开始是读错了的，导致我在正确性上思考了比较久的时间，浪费了一定时间，注意操作次数是 `at most k`，而不是恰好 $k$ 次。

注意到特殊条件 $n\times q\le10^5$（而且是 Hard Version 中没有的条件），说明每次 $q$ 可以枚举一遍 $a$ 数组。

那么一位一位往下贪心即可。

不知道 `__int128` 可不可行，但是用 `long long` 的需要注意，如果从 $61$ 开始贪心，搞一个都比较小的数据，$2^{61}\times n$ 很容易超过 `long long` 的范围，所以我开始贪心的 $dep$ 值是根据 $\dfrac{k+S}{n}$ 求出来的，其中 $S$ 是 $a$ 数组的总和，这样可以不暴 `long long`。

同时注意一下贪心之后增加的值的大小，并且记得复制数组，并且在复制数组中改变值的大小，这样下一位的时候才不会出错。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 5;
int n, k, a[N], q, b[N], tot, ans, tem, S, dep;
inline void solve(){
	ans = S = 0;
	for(int i = 1; i <= n; i++) b[i] = a[i], S += b[i];
	S = (k + S) / n;
	for(dep = 0; (1ll << dep) <= S; dep++) ;
	for(; ~dep; dep--){
		tot = 0;
		for(int i = 1; i <= n; i++){
			tem = b[i] >> dep;
			if(tem & 1) continue ;
			tem = b[i] ^ (tem << dep);
			tot += (1ll << dep) - tem;
		}
		if(tot <= k){
			ans += (1ll << dep);
			k -= tot;
			for(int i = 1; i <= n; i++){
				tem = b[i] >> dep;
				if(tem & 1) continue ;
				tem >>= 1;
				b[i] = (tem << dep + 1) + (1ll << dep);
			}
		}
	}
}
signed main(){
	scanf("%lld%lld", &n, &q);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]), S += a[i];
	while(q--){
		scanf("%lld", &k);
		solve();
		printf("%lld\n", ans);
	}
	return 0;
}
/*
10 1
0 0 0 0 0 0 0 0 0 0
1000000000000000000
*/
```

[评测记录](https://codeforces.com/contest/1903/submission/236450865)

---

## 作者：technopolis_2085 (赞：0)

题目大意：

给你 $n$ 个数字，然后有 $q$ 次询问，每次给你 $k$，让你完成不超过 $k$ 次操作，每次操作可以使任意一个元素加 $1$，问操作后所有元素的与运算结果的最大值为多少。

观察数据范围，发现一个比较神奇的限制：$n × q ≤ 10^5$。这说明我们可以用 $O(n)$ 的复杂度来处理每一次询问。

然后考虑从高位到低位的贪心：每一次看当前剩余的操作次数能否使得所有元素的这一位都为 $1$，因为只有这样才能使得它们进行按位与操作后还为 $1$。

贪心显然是正确的，因为假设每个元素的这一位都能变成 $1$ 对答案的贡献比它后面所有位都变成 $1$ 的贡献还要大。

接着考虑这一位能否变成 $1$。可以 $O(n)$ 遍历数组，分类讨论：

- 如果当前位已经是 $1$，则不用操作。
- 如果当前位不是 $1$，则如果此数小于 $2^i$，则直接变成 $2^i$。
- 否则，就将第 $i$ 位变成 $1$，更低位全部变成 $0$。

然后判断操作次数是否能够满足即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=1e5+10;
int a[maxn];
int tmp[maxn];

signed main(){
    int n,q;
    scanf("%lld%lld",&n,&q);
    for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
    int big=0;
    for (int i=1;i<=n;i++) big=max(big,a[i]);
    
    while (q--){
        int k;
        scanf("%lld",&k);
        
        if (n==1){
            printf("%lld\n",a[1]+k);
            continue;
        }
        for (int i=1;i<=n;i++) tmp[i]=a[i];
        
        int ans=0;
        
        //2^i大于2^(i-1)+2^(i-2)+...+2+1，所以从高位往地位更优
        for (int i=log2(big+k);i>=0;i--){
        	int flag=0;
            int now=0;
            for (int j=1;j<=n;j++){
                if (tmp[j]<(1ll<<i)) now+=(1ll<<i)-tmp[j];
                else if ((tmp[j]&(1ll<<i))==0){
                    int sum=0;
                    for (int p=0;p<i;p++){
                        if ((tmp[j]&(1ll<<p))) sum+=(1ll<<p);
                    }
                    now+=(1ll<<i)-sum;
                }
                if (now>k){
                	flag=1; break;
				}
            }
            
            if (flag==0&&k>=now){
                k-=now;
                ans+=(1ll<<i);
                for (int j=1;j<=n;j++){
                    if (tmp[j]<(1ll<<i)) tmp[j]=(1ll<<i);
                    else if ((tmp[j]&(1ll<<i))==0){
                        int sum=0;
                        for (int p=0;p<i;p++){
                            if ((tmp[j]&(1ll<<p))) sum+=(1ll<<p);
                        }
                        tmp[j]+=(1ll<<i)-sum;
                }
                }
            }
        }
        
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：引领天下 (赞：0)

题意：

给定一个长为 $n$ 的序列 $a$，总共可以进行 $k$ 次选择一个元素 $+1$ 的操作，最大化 $a_1\operatorname{AND} a_2\dots\operatorname{AND}a_n$。

$n,q\le10^6,n\times q\le 10^6,k\le10^{18}$。

做法：

很简单的暴力。

考虑直接枚举最后的答案哪些位是 1，然后判断该位能否是 1。

将 $a_j$ 的第 $i$ 位变成 1，有两种情况：

- $a_j$ 的第 $i$ 位本来就是 1，花费为 0。

- $a_j$ 的第 $i$ 位是 0，则补全后就是 $1<<i$，花费为 $1<<i-a_j$（不考虑 $a_j$ 的高位部分）。

那么将这些加起来，和 $k$ 作比较即可。

时间复杂度 $O(Vqn)$，$V$ 的量级在 $10^2$，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,q,k,a[1000005],b[1000005];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(signed i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
    while(q--){
        cin>>k;
        signed i=60;bool flag=1;
        int s=0;
        for(;~i;i--){
            unsigned __int128 t=0;
            for(int j=1;j<=n;j++)t+=max(0ll,(1ll<<i)-(a[j]%(1ll<<(i+1))));
            if(t<=k){
                k-=t,s+=1ll<<i;
                for(int j=1;j<=n;j++)a[j]+=max(0ll,(1ll<<i)-(a[j]%(1ll<<(i+1))));
            }
        }
        for(int i=1;i<=n;i++)a[i]=b[i];
        cout<<s<<'\n';
    }
    return 0;
}
```

---

## 作者：The_jester_from_Lst (赞：0)

简易贪心题。

既然是按位与，为了方便操作我们将所有数字转为二进制。然后这个题目就好做了：从高位往低位枚举，只要这一位还够改成 $1$ 的，我们果断改掉，并将改成 $1$ 的花费记录下来。大于 $k$ 了就代表不够改了。

改好后再枚举统计答案即可。

附上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define il inline
#define mod 1000000007
using namespace std;
il int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
il void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
il int min(int x,int y){return (x<=y)?x:y;}
il int max(int x,int y){return (x>y)?x:y;}
int n,q,a[100086],k,maxn,fa[100086];
inline void manba_out(){for(int i=1;i<=n;++i)fa[i]=a[i];}
namespace man{
	il void what_can_i_say(){
		n=rd();q=rd();
		for(int i=1;i<=n;++i)a[i]=rd();
		while(q--){
			int s=0;
			k=rd();
			manba_out();
			for(int i=62;i>=0;--i){
				int p=0;bool f=0;
				for(int j=1;j<=n;++j){
					if((fa[j]&(1ll<<i))==0){
						p+=(1ll<<i)-fa[j];
						if(p>k){
							f=1;
							break;
						}
					}
				}
				if(f==0){
					s+=(1ll<<i);
					k-=p;
				}
				for(int j=1;j<=n;++j){
					if((fa[j]&(1ll<<i))==0&&!f)fa[j]=(1ll<<i);
					if((fa[j]&(1ll<<i))!=0)fa[j]-=(1ll<<i);
				}
			}
			wr(s);
			putchar('\n');
		}
	}
}
signed main(){
	man::what_can_i_say();
    return 0;
}
```

---

