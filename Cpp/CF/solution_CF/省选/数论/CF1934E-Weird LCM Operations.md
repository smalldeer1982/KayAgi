# Weird LCM Operations

## 题目描述

Given an integer $ n $ , you construct an array $ a $ of $ n $ integers, where $ a_i = i $ for all integers $ i $ in the range $ [1, n] $ . An operation on this array is defined as follows:

- Select three distinct indices $ i $ , $ j $ , and $ k $ from the array, and let $ x = a_i $ , $ y = a_j $ , and $ z = a_k $ .
- Update the array as follows: $ a_i = \operatorname{lcm}(y, z) $ , $ a_j = \operatorname{lcm}(x, z) $ , and $ a_k = \operatorname{lcm}(x, y) $ , where $ \operatorname{lcm} $ represents the least common multiple.

 Your task is to provide a possible sequence of operations, containing at most $ \lfloor \frac{n}{6} \rfloor + 5 $ operations such that after executing these operations, if you create a set containing the greatest common divisors (GCDs) of all subsequences with a size greater than $ 1 $ , then all numbers from $ 1 $ to $ n $ should be present in this set.After all the operations $ a_i \le 10^{18} $ should hold for all $ 1 \le i \le n $ .

We can show that an answer always exists.

## 说明/提示

In the third test case, $ a = [1, 2, 3, 4, 5, 6, 7] $ .

First operation:

 $ i = 3 $ , $ j = 5 $ , $ k = 7 $

 $ x = 3 $ , $ y = 5 $ , $ z = 7 $ .

 $ a = [1, 2, \operatorname{lcm}(y,z), 4, \operatorname{lcm}(x,z), 6, \operatorname{lcm}(x,y)] $ = $ [1, 2, \color{red}{35}, 4, \color{red}{21}, 6, \color{red}{15}] $ .

Second operation:

 $ i = 5 $ , $ j = 6 $ , $ k = 7 $

 $ x = 21 $ , $ y = 6 $ , $ z = 15 $ .

 $ a = [1, 2, 35, 4, \operatorname{lcm}(y,z), \operatorname{lcm}(x,z), \operatorname{lcm}(x,y)] $ = $ [1, 2, 35, 4, \color{red}{30}, \color{red}{105}, \color{red}{42}] $ .

Third operation:

 $ i = 2 $ , $ j = 3 $ , $ k = 4 $

 $ x = 2 $ , $ y = 35 $ , $ z = 4 $ .

 $ a = [1, \operatorname{lcm}(y,z), \operatorname{lcm}(x,z), \operatorname{lcm}(x,y), 30, 105, 42] $ = $ [1, \color{red}{140}, \color{red}{4}, \color{red}{70}, 30, 105, 42] $ .

Subsequences whose GCD equal to $ i $ is as follows:

 $ \gcd(a_1, a_2) = \gcd(1, 140) = 1 $

 $ \gcd(a_3, a_4) = \gcd(4, 70) = 2 $

 $ \gcd(a_5, a_6, a_7) = \gcd(30, 105, 42) = 3 $

 $ \gcd(a_2, a_3) = \gcd(140, 4) = 4 $

 $ \gcd(a_2, a_4, a_5, a_6) = \gcd(140, 70, 30, 105) = 5 $

 $ \gcd(a_5, a_7) = \gcd(30, 42) = 6 $

 $ \gcd(a_2, a_4, a_6, a_7) = \gcd(140, 70, 105, 42) = 7 $

## 样例 #1

### 输入

```
3
3
4
7```

### 输出

```
1
1 2 3
1
1 3 4
3
3 5 7
5 6 7
2 3 4```

# 题解

## 作者：sunkuangzheng (赞：3)

$\textbf{CF1934E *3000}$

> - 给定长度为 $n$ 的序列 $a$，初始时满足 $a_i=i$。一次操作为选择三个互不相同的下标 $i,j,k$，设 $x=a_i,y=a_j,z=a_k$，令 $a_i = \operatorname{lcm}(y,z),a_j = \operatorname{lcm}(x,z),a_k = \operatorname{lcm}(x,y)$。
> - 在 $\lfloor \dfrac{n}{6} \rfloor +5$ 次操作内，将序列 $a$ 变成好的。好的序列指的是，对于任意 $x \in [1,n]$，都存在 $a$ 的一个长度至少为 $2$ 的子序列 $a'$，使得 $\gcd\{a'\} = x$。
> - $3 \le n \le 3 \cdot 10^4$。

对这种 ad-hoc 构造真没一点思路，做法参考了官方题解。

- 性质一：对于三元组 $(x,y,z)$，如果满足 $\gcd(x,y)=\gcd(x,z) = \gcd(y,z)=\gcd(x,y,z)$，则操作一次后序列中将存在 $\gcd$ 为 $x,y,z$ 的子序列。

> 不妨令 $d = \gcd(x,y,z),x=ad,y=bd,z=cd$，则 $a,b,c$ 应当两两互质。那么操作完后，三元组 $(x,y,z)$ 将变为 $(bc \cdot d,ac \cdot d,ab \cdot d)$，两两组成子序列即可得到 $\gcd$ 为 $x,y,z$ 的子序列。

这样一来，如果我们能把序列 $a$ 分成若干个满足上述条件的三元组，对其分别操作后序列 $a$ 将满足条件，需要 $\dfrac{n}{3}+\mathcal O(1)$ 次操作。

- 性质二：采用上述方法，对于 $i \le \dfrac{n}{2}$，我们不需要进行任何操作。

> 显然序列中一定存在元素 $2i$ 的倍数 $k \cdot 2i$，那么子序列 $\{i,k \cdot 2i\}$ 的 $\gcd$ 为 $i$，已经满足要求。

这样我们的操作次数降到 $\dfrac{n}{6}+\mathcal O(1)$ 次，可以满足条件。接下来考虑如何划分。

- 性质三：对于 $x \bmod 4 \ge 2$，$[x,x+1,\ldots,x+10,x+11]$ 这个长度为 $12$ 的连续段一定可以拆成 $4$ 个满足条件的三元组。

>   - 对于 $x \bmod 4=3$，$(x,x+1,x+2),(x+4,x+5,x+6),(x+8,x+9,x+10)$ 的结构都是 $(2k-1,2k,2k+1)$，满足条件。$(x+3,x+7,x+11)$ 的结构是 $(4k+2,4k+6,4k+10)$，除以 $2$ 后变为 $(2k+1,2k+3,2k+5)$，两个奇数 $x,y$ 满足 $|x-y| \le 4$ 一定互质，那么 $(2k+1,2k+3,2k+5)$ 满足条件。
>   - 对于 $x \bmod 4 = 2$，$(x+1,x+2,x+3),(x+5,x+6,x+7),(x+9,x+10,x+11)$ 的结构是 $(2k-1,2k,2k+1)$，而 $(x,x+4,x+8)$ 的结构是 $(4k+2,4k+6,4k+10)$，满足要求。

注意到如果 $n \bmod 4 = 1$ 或 $2$，我们直接选择 $[n-11,n-10,\ldots,n-1,n]$ 就是一个满足 $x \bmod 4 \ge 2$ 的段，将 $n \gets n-12$ 后继续操作即可。当 $n \bmod 4 = 0$ 或 $3$ 时，我们执行操作 $(1,n-1,n-2)$，即可转化为上述情况。

总操作次数 $\dfrac{n}{6}+1$，满足要求。

有个细节是当 $n \le 12$ 时不存在满足条件的长度为 $12$ 的连续段，这个时候我们需要爆搜或者手玩寻找答案。

下面的代码中 $n \le 12$ 的情况复制自官方题解。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 02.03.2024 10:07:11
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n; vector<tuple<int,int,int>> pans[15];
void los(){
    cin >> n;
    vector<tuple<int,int,int>> ans;
    pans[3]={{1,2,3}};
    pans[4]={{1,3,4}};
    pans[5]={{3,4,5}};
    pans[6]={{1,3,5},{2,4,6}};
    pans[7]={{2,4,6},{3,5,7}};
    pans[8]={{2,6,8},{3,5,7}};
    pans[9]={{1,3,5},{2,4,6},{7,8,9}};
    pans[10]={{3,4,5},{2,6,8},{7,9,10}};
    pans[11]={{2,6,8},{3,5,7},{9,10,11}};
    pans[12]={{1,11,12},{6,8,10},{5,7,9}};
    auto add = [&](int x,int y,int z){ans.emplace_back(x,y,z);};
    if(n <= 12) ans = pans[n];
    else{
        if(n % 4 == 0 || n % 4 == 3) add(1,n-1,n),n -= 2;
        int rn = n / 2;
        while(n > rn){
            int d = n - 11; 
            if(d % 4 == 3) add(d,d+1,d+2),add(d+4,d+5,d+6),add(d+8,d+9,d+10),add(d+3,d+7,d+11);
            else add(d+1,d+2,d+3),add(d+5,d+6,d+7),add(d+9,d+10,d+11),add(d,d+4,d+8);
            n -= 12; 
        }
    }cout << ans.size() << "\n";
    for(auto [x,y,z] : ans) cout << x << " " << y << " " << z << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(cin >> T;T --;) los();
}
```

---

## 作者：Rainbow_qwq (赞：2)

一种比较乱搞的做法，但操作次数更优。

我们发现有一种比较优的操作方法：操作三个互质的数 $(4i-1,4i,4i+1)$，这样可以满足 $4i-1,4i,4i+1,2\times (4i-1),2\times (4i+1)$ 的要求，后两个也就同时满足了 $4i+2$ 的要求。

需要判一下边界：当 $n\bmod 4 = 3$ 时，操作 $(1,2,n)$；当 $n\bmod 4 = 0$ 时，操作 $(1,n-1,n)$。

这样的操作次数为 $\frac{n}{4}$ 级别，还需要优化。

优化的方式是：一个个考虑 $i$，如果当前序列中的其他位置已经有 $\ge 2$ 个 $4i-1,4i,4i+1,2\times (4i-1),2\times (4i+1)$ 的倍数（如果后两个 $>n$ 就不用判），就不操作 $(4i-1,4i,4i+1)$。

发现这样优化后，如果从小到大加入 $i$，在 $n=30000$ 时只需要 $4269$ 次；如果从大到小加入 $i$，在 $n=30000$ 时只需要 $3808$ 次，远低于 
$\frac{n}{6}=5000$ 次的限制。

直接判断的复杂度是 $O(n^2)$，会 [TLE](https://codeforces.com/problemset/submission/1934/257409018)。

但我们可以每次操作完就暴力标记掉新出现的 $\operatorname{lcm}(x,y)$ 的所有因数，这样复杂度为 $\sum (d_id_{i+1}+d_{i-1}d_i+d_{i-1}d_{i+1})$（$d_i$ 为 $i$ 的因数个数），就可以过了。

[submission](https://codeforces.com/problemset/submission/1934/257410858)

---

## 作者：Hanghang (赞：1)

思路借鉴了 rainboy 大佬，拜谢。

主要记录一下思考过程吧，这题还是比较巧妙的。

首先注意到操作次数的上界大约是 $\dfrac{n}{6}$，每次操作只能改变 $3$ 个位置的值，中间大概差了两倍。

这成为了突破口，我们大胆猜测每个位置至多操作一次的话，那么将会有一半的位置值不会变。

那这一半左右的位置究竟是哪些呢？

跟一半有关的东西大概有：奇偶，前一半后一半。

这题看样子就跟奇偶没差本质联系，所以从后者开始思考。

首先大胆猜测应该前一半尽量不操作，后一半操作。因为不断操作小的数 $x$ 容易使得无法使得最后没有最大公因数为 $x$。

那我们可以从 $n$ 往小的数考虑。

如果 $n$ 是奇数，我们可以将 $(n-2,n-1,n)$ 一起操作，这样我们要查询最大公因数为其中某个数的时候选其中的两个数即可。

如果 $n$ 不是 $4$ 的倍数，我们可以操作 $(\dfrac{n}{2},n-2,n-1)$，原因是，如果我们跟奇数一样操作的话，那么一次操作中就会出现两个偶数，在变成最小公因数的时候就不是简单的相乘了，那么我们在查询最大公因数的时候也就不是想要的值了。而这么操作的原因是 $n$ 质因数分解后只会有一个 $2$，那么，我们 $\operatorname{lcm}(n-2,\dfrac {n}{2})$ 后恰好是 $n$ 的倍数，查询的时候将两者一起询问即可构造出最大公因数为 $n$ 的值。$n-1,n-2$ 的值不会被影响，跟奇数类似。$\dfrac{n}{2}$ 这个值其实也不用担心，因为它和 $n-1,n-2$ 互质，那么查询 $n-1,n-2$ 的最大公因数也就能找到 $\dfrac{n}{2}$。

如果 $n$ 是 $4$ 的倍数，我们可以操作 $(\dfrac{n}{2}-1,n-1,n)$，原因跟上者类似。

还有些细节就是这么构造可能会剩下不到三个数，有点讨厌。

方法是在一开始的时候操作 $(1,n-1,n-2)$，这样就解决了。

总而言之就是这种构造需要大胆猜测加上细致分析，还是非常困难的。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
typedef long long ll;
const int N=1e6+3;
void Solve()
{
	ll n,m,k;cin>>n;k=n;m=(n+1)/2;
	cout<<(m+2)/3<<endl;
	if(m%3)cout<<1<<" "<<k-1<<" "<<k<<endl,k-=2;
	for(;k*2>n;k-=3)
	{
		if(k%2)cout<<k-2<<" "<<k-1<<" "<<k<<endl;
		else if(k%4)cout<<k/2<<" "<<k-2<<" "<<k-1<<endl;
		else cout<<k/2-1<<" "<<k-1<<" "<<k<<endl; 
	}
}
int main()
{
	int T;cin>>T;
	while(T--)Solve();
	return 0; 
}
```

---

## 作者：diqiuyi (赞：0)

显然所有 $\le \dfrac{n}{2}$ 的数在一开始就已经满足了。

注意到对于任意连续的 $3$ 个数 $x,y,z$，把它们分成一组都可以让 $\gcd$ 出现 $x$ 和 $z$。对 $> \dfrac{n}{2}$ 的数分组操作次数恰好会出现 $\dfrac{n}{6}$，看起来很有道理。

但是当 $z$ 为偶数时 $\gcd(\operatorname{lcm}(x,y),\operatorname{lcm}(y,z))=2y$，并不能满足。

进一步地，对于任意的 $(x-d,x,x+d)$，若 $x+d$ 不为 $2d$ 的倍数，那么这么操作完我们可以让这三个数都变得合法。

于是我们考虑把所有待操作的数按照连续 $4$ 个数分组。则每组的前 $3$ 个或者后 $3$ 个可以被一次操作满足。考虑从大到小分组。最后几个无法被分成一组的可以和 $\le \dfrac{n}{2}$ 的数进行一次操作。

注意到没有被满足的数是一个等差数列，那么我们可以继续完成这个操作直到剩余的数 $<3$ 个，不继续操作的原因是当剩余数 $<3$ 个时，$x-2d$ 不一定存在。

但是我们发现如果剩余 $2$ 个数，$(1,x,y)$ 恰好可以满足。如果剩余 $1$ 个数，$(1,2,x)$ 恰好可以满足。

正确性证明不太好描述，手模观察一下就好了，大概就是由于每次公差会 $\times 4$，之前操作被用到的 $\le \dfrac{n}{2}$ 的数之后不会再被用到了。然后 $n$ 较大的时候 $1,2$ 都不会被用到。

这样做的操作次数似乎是 $\dfrac{n}{6}+\log_4n$，但是并不满，所以可以通过。
```cpp
#include <bits/stdc++.h>
#define ll long long	
using namespace std;
int t,n;
vector<int> v,vc;
vector<array<int,3> > res;
bitset<30005> vis;
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>t;
	while(t--){
		cin>>n,v.clear(),res.clear();
		for(int i=n/2+1;i<=n;i++) v.push_back(i);
		int now=1;
		while(v.size()>=3){
			vc.clear();
			for(int i=0;i<v.size();i++) vis[i]=0;
			for(int i=(v.back()%(now*2)?v.size()-1:v.size()-2);i>=0;i-=4){
				res.push_back({v[i],v[i]-now,v[i]-now*2});
				vis[i]=1;
				if(i) vis[i-1]=1;
				if(i>1) vis[i-2]=1;
			}
			for(int i=0;i<v.size();i++)
				if(!vis[i])
					vc.push_back(v[i]);
			v=vc,now*=4;
		}
		if(v.size()==1) res.push_back({1,2,v[0]});
		if(v.size()==2) res.push_back({1,v[0],v[1]});
		cout<<res.size()<<'\n';
		for(auto x:res)
			cout<<x[0]<<' '<<x[1]<<' '<<x[2]<<'\n';	
	}
	return 0;
}
```

---

## 作者：zyh_helen (赞：0)

需要特判**大**量情况的唐氏做法。

---
---

显然小于 $\frac{n}{2}$ 的不操作问题不大，对于大于 $\frac{n}{2}$ 的三个合并下就行。

考虑分组，对于所有 $i$，$(3\times2^i\times(p-1),3\times2^i\times p,3\times2^i\times(p+1))$ 分为一组，特别的，剩下的 $(2k-1,2k+1,2k+3)$ 也分为一组，易证满足条件，并且不重不漏。

---

边界是很麻烦的，一开始直接无脑延伸极限情况是会被卡掉的。

考虑把两层的落单一个合并再配上一个别的东西，一层剩下两个的仍然延伸，发现大概率是能合并的。

合并的时候简单判一下，不是特别难打。

但是，要特判的特别多，用简单的打个表特判。

---

最后，有个唐氏情况，$n=21065$，还是大了，很极限。

把方案打出来，居然可以合并最后两步，解决了。

---
---

```cpp
#include<bits/stdc++.h>
//#include<Windows.h>
#define int long long
//#define ll long long
//#define double long double
#define fi first
#define se second
//#define ls t[p].l
//#define rs t[p].r
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 3e4 + 10, inf = 2e9, M = 4e3 + 5;
//const double eps = 1e-14, pi = 3.1415926, kou = 0.577215669902;
const int mod = 1e9 + 7;
//const int AQX = 9;
mt19937 rnd(time(0) ^ clock());
int random(int l, int r){
	return rnd() % (r - l + 1) + l;
}
/*
		    	           _      _        _          
			       ____  _| |_   | |_  ___| |___ _ _  
			      |_ / || | ' \  | ' \/ -_) / -_) ' \ 
			      /__|\_, |_||_|_|_||_\___|_\___|_||_|
			          |__/    |___|                              
				       
*/
//struct Graph{
//	int head[N], tot = 1;
//	struct edge{
//		int t, f;
//		int d, fa;
//		int next;
//	}e[N << 1];
//	void edge_add(int u, int v, int w = 0){
//		e[++tot].next = head[u];
//		mp[{u, v}] = tot / 2;
//		e[tot].t = v;
//		e[tot].d = w;
//		e[tot].f = u;
//		head[u] = tot;
//	}
//	void clear(int n){
//		for(int i = 1;i <= tot;i++)e[i].t = e[i].f = e[i].d = e[i].next = 0;
//		for(int i = 1;i <= n;i++)head[i] = 0;
//		tot = 0;
//	}
//}g;
//int qmr(int x, int a){
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}

int n, p[N], pp[N], m, v[N];
int gcd(int x, int y){
	if(!y)return x;
	return gcd(y, x % y);
}
signed main(){
//	freopen("1.out", "w", stdout);
	int T;
	cin >> T;
	p[++m] = 1;
	for(int i = 2;i < N;i++){
		if(pp[i])continue;
		if(i > 2)p[++m] = i;
		for(int j = i + i;j < N;j += i)pp[j] = 1;
	}
	while(T--){
		cin >> n;
		if(n <= 20 || (n >= 24 && n <= 28) || n == 30 || n == 37 || n == 51 || n == 52 || n == 54 || n == 55){
			if(n == 3)cout << "1\n1 2 3\n";
			else if(n == 4)cout << "1\n1 3 4\n";
			else if(n == 16)cout << "4\n13 14 15\n9 10 11\n5 7 16\n4 8 12\n";
			else if(n == 17)cout << "4\n13 14 15\n9 10 11\n7 17 16\n4 8 12\n";
			else if(n == 18)cout << "4\n14 16 18\n9 10 11\n13 15 17\n4 8 12\n";
			else if(n == 19)cout << "5\n14 16 18\n9 10 11\n13 15 17\n4 8 12\n19 7 5\n";
			else if(n == 20)cout << "5\n14 16 18\n9 10 11\n13 15 17\n4 8 12\n7 19 20\n";
			else if(n == 5)cout << "1\n3 4 5\n";
			else if(n == 6)cout << "2\n2 4 6\n1 3 5\n";
			else if(n == 7)cout << "3\n3 5 7\n5 6 7\n2 3 4\n";
			else if(n == 8)cout << "2\n5 6 7\n1 2 8\n";
			else if(n == 9)cout << "2\n1 5 6\n7 8 9\n";
			else if(n == 10)cout << "2\n6 8 10\n1 7 9\n";
			else if(n == 11)cout << "3\n9 10 11\n3 7 8\n1 5 6\n";
			else if(n == 12)cout << "3\n9 10 11\n5 7 12\n1 3 8\n";
			else if(n == 13)cout << "3\n9 10 11\n8 13 7\n1 5 12\n";
			else if(n == 14)cout << "3\n9 5 11\n7 8 13\n10 12 14\n";
			else if(n == 15)cout << "4\n9 10 11\n8 13 15\n1 2 14\n12 5 7\n";
			else if(n == 24)cout << "6\n19 21 23\n13 15 17\n14 18 22\n4 12 20\n3 8 24\n7 5 16\n";
			else if(n == 25)cout << "7\n21 23 25\n15 17 19\n9 11 13\n14 18 22\n4 12 20\n3 8 24\n7 5 16\n";
			else if(n == 26)cout << "7\n21 23 25\n15 17 19\n18 22 26\n6 10 14\n4 12 20\n3 8 24\n7 5 16\n";
			else if(n == 27)cout << "8\n23 25 27\n17 19 21\n11 13 15\n18 22 26\n6 10 14\n4 12 20\n3 8 24\n7 5 16\n";
			else if(n == 28)cout << "7\n23 25 27\n17 19 21\n11 13 15\n18 22 26\n12 20 28\n3 8 24\n7 5 16\n";
			else if(n == 30)cout << "8\n25 27 29\n19 21 23\n13 15 17\n22 26 30\n10 14 18\n12 20 28\n3 8 24\n7 5 16\n";
			else if(n == 37)cout << "9\n33 35 37\n27 29 31\n21 23 25\n15 17 19\n26 30 34\n14 18 22\n20 28 36\n3 8 24\n7 5 32\n";
			else if(n == 51)cout << "12\n47 49 51\n41 43 45\n35 37 39\n29 31 33\n23 25 27\n42 46 50\n30 34 38\n18 22 26\n28 36 44\n8 24 40\n3 16 48\n7 5 32\n";
			else if(n == 52)cout << "12\n47 49 51\n41 43 45\n35 37 39\n29 31 33\n23 25 27\n42 46 50\n30 34 38\n36 44 52\n12 20 28\n8 24 40\n3 16 48\n7 5 32\n";
			else if(n == 54)cout << "13\n49 51 53\n43 45 47\n37 39 41\n31 33 35\n25 27 29\n46 50 54\n34 38 42\n22 26 30\n36 44 52\n12 20 28\n8 24 40\n3 16 48\n7 5 32\n";
			else cout << "13\n51 53 55\n45 47 49\n39 41 43\n33 35 37\n27 29 31\n46 50 54\n34 38 42\n22 26 30\n36 44 52\n12 20 28\n8 24 40\n3 16 48\n7 5 32\n";
			continue;
		}
		vector<pair<int, pair<int, int> > >ans;
		int cnt = 0, X = 0, Y = 0;
		for(int i = 1;i <= 15;i++){
			int o = 1 << i, r = 1 << i - 1, x = 0, y = 0, j = n / r * r;
			for(;j > n / 2;j -= r){
				if(j % o == 0)continue;
				if(!x)x = j;
				else if(!y)y = j;
				else ans.push_back({j, {y, x}}), v[j] = v[y] = v[x] = 1, x = y = 0;
			}
			if(y){
				for(;x && j;j -= r){
					if(j % o == 0)continue;
					if(!y)y = j;
					else ans.push_back({j, {y, x}}), v[j] = v[y] = v[x] = 1, x = y = 0;
				}
			}
			if(x){
				if(!y){
					if(!X)X = x;
					else {
						v[x] = v[X] = 1;
						int g = gcd(X, x), f = 0;
//						cout << g << endl;
						for(int k = 2;k <= 8;k++)if(p[k] * g <= n && !v[p[k] * g] && (X % p[k]) && (x % p[k])){
//							cout << p[k] << endl;
							ans.push_back({p[k] * g, {X, x}}), v[p[k] * g] = 1;
							f = 1;
							break;
						}
						if(!f){
							int aa = p[++cnt], bb = p[++cnt];
							while(v[aa])aa = p[++cnt];
							while(v[bb])bb = p[++cnt];
							ans.push_back({aa, {bb, x}}), v[aa] = v[bb] = v[x] = 1;
							while(v[aa])aa = p[++cnt];
							while(v[bb])bb = p[++cnt];
							ans.push_back({aa, {bb, X}}), v[aa] = v[bb] = v[X] = 1;
						}
						X = 0;
					}
				}
				else {
					int aa = p[++cnt];
					while(v[aa])aa = p[++cnt];
					ans.push_back({aa, {y, x}}), v[aa] = v[y] = v[x] = 1;
				}
			}
		}
		if(X){
			int aa = p[++cnt], bb = p[++cnt];
			while(v[aa])aa = p[++cnt];
			while(v[bb])bb = p[++cnt];
			ans.push_back({aa, {bb, X}});
		}
		if(n == 21065){
			ans.pop_back();
			ans[ans.size() - 1].fi = 16384;
		}
		cout << ans.size() << endl;
		for(auto x : ans)printf("%lld %lld %lld\n", x.fi, x.se.fi, x.se.se);
		for(int i = 1;i <= n;i++)v[i] = 0;
	}
	return 0;
}

---

## 作者：Otomachi_Una_ (赞：0)

**【题目简述】**

你有一个序列，初始 $a_i=i$。你可以进行操作 $(x,y,z)$，同时把 $a_x\leftarrow\operatorname{lca}(a_y,a_z),a_y\leftarrow\operatorname{lca}(a_z,a_x),a_z\leftarrow\operatorname{lca}(a_x,a_y)$。

你需要在 $\mathcal O(\dfrac n6)$ 次操作内使得序列 $a$ 满足对任意 $i=1,2,\dots,n$ 使得存在 $S\subset[n],|S|\geq 2,\gcd_{s\in S}a_s=i$。

$n\leq 3\times 10^4$。

**【解题思路】**

如果对 $i\leq \dfrac n2$，显然不需要管，因为我们恒有 $2i$ 的倍数，我们 $a_i$ 不动就行。

考虑对一个操作 $(x,y,z)$，我们想要在这次操作之后对 $x,y,z$ 都能满足我们的要求。我们发现 $\gcd(x,y)=\gcd(y,z)=\gcd(z,x)=\gcd(x,y,z)$ 的时候这个是能成立的。

于是我们只需要把 $\geq \dfrac n2$ 的部分划分为若干 $(4x-1,4x,4x+1)$ 和 $(4x-2,4x+2,4x+6)$ 即可。

当 $n$ 太小时候直接暴力枚举就行。

**【参考代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
bool check(int x,int y,int z){
	int a=x*y/__gcd(x,y),b=y*z/__gcd(y,z),c=z*x/__gcd(x,z);
	if(__gcd(a,b)!=y||__gcd(b,c)!=z||__gcd(a,c)!=x) return false;
	return true;
}
int main(){
	ios::sync_with_stdio(false);
	// freopen("Otomachi_Una.in","r",stdin);
	// freopen("Otomachi_Una.out","w",stdout);
	int _;cin>>_;
	while(_--){
		vector<array<int,3> > ans;
		int n;cin>>n;
		if(n<=20){
			vector<int> p;
			for(int i=1;i<=n;i++) p.push_back(i);
			while(1){
				shuffle(p.begin(),p.end(),rnd);
				bool flag=true;
				for(int i=n-1;i%3!=2;i--) if(2*p[i]>n) flag=false;
				for(int i=0;i+2<n;i+=3) if(!check(p[i],p[i+1],p[i+2])){
					flag=false;
					break;
				}
				if(flag){
					cout<<n/3<<'\n';
					for(int i=0;i+2<n;i+=3) cout<<p[i]<<" "<<p[i+1]<<" "<<p[i+2]<<'\n';
					break;
				}
			}
			continue;
		}
		if(n%4==3) ans.push_back({n-2,n-1,n}),n-=3;
		if(n%4==0) ans.push_back({1,n-1,n}),n-=2;
		for(int i=(n-1)/4*4+1;i*2>n;i-=4){
			ans.push_back({i-2,i-1,i});
		}
		for(int i=(n-2)/4*4+2;i*2>n;i-=12){
			ans.push_back({i-8,i-4,i});
		}
		cout<<ans.size()<<'\n';
		for(auto i:ans) cout<<i[0]<<" "<<i[1]<<" "<<i[2]<<'\n';
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1934E)

**题目大意**

> 给定长度为 $n$ 的数组 $a_i$，初始 $a_i=i$，每次操作可以选定 $x,y,z$ 使得 $a_x\gets \mathrm{lcm}(a_y,a_z),a_y\gets\mathrm{lcm}(a_z,a_x),a_z\gets \mathrm{lcm}(a_x,a_y)$。
>
> 构造方案在 $\dfrac n6+5$ 次操作内使得对于任意 $x\in[1,n]$，$a_i$ 都存在大小 $\ge 2$ 的子集 $S$ 使得 $\gcd(S)=x$。
>
> 数据范围：$n\le 3\times 10^4$。

**思路分析**

注意到对于三个数 $x,y,z$，如果他们两两互质，那么操作后会形成 $yz,zx,xy$，存在三个大小为 $2$ 的子集的 $\gcd$ 恰好就是 $x,y,z$。

进一步，如果 $\gcd(x,y)=\gcd(y,z)=\gcd(z,x)=\gcd(x,y,z)$，那么操作 $x,y,z$ 就能满足 $x,y,z$ 的限制。

此时操作次数大约是 $\dfrac n3$，需要进一步优化，注意到 $x\le \dfrac n2$ 的数没有操作意义，选择 $i$ 和 $2i$ 的某个倍数即可。

那么此时操作此时大约是 $\dfrac n6$，我们只需要解决分组问题即可。

考虑成若干个较小的组，每个组内可以用若干个操作完美覆盖。

注意到一种基本形式，对于 $x,x+1,x+2$，如果 $x$ 是奇数，那么他们两两互质，尝试构造这种形式：

注意到对于 $x\sim x+11$ 这连续的 $12$ 个数，如果 $x\bmod 4\ge 2$，那么我们可以把其恰好分成 $4$ 组：

-  如果 $x\bmod 4=2$，那么 $(x+1,x+2,x+3),(x+5,x+6,x+7),(x+9,x+10,x+11)$ 每组两两互质，$(x,x+4,x+8)$ 约去 $2$ 后两两互质。
- 如果 $x\bmod 4=3$，那么 $(x,x+1,x+2),(x+4,x+5,x+6),(x+8,x+9,x+10)$ 每组两两互质，$(x+3,x+7,x+11)$ 约去 $2$ 后两两互质。

那么就可以通过这种方法构造，如果 $(n-11)\bmod 4<2$，那么操作 $(n,n-1,1)$ 即可。

特判 $n\le 12$ 的情况。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
vector <array<int,3>> vi[15];
void solve() {
	int n;
	scanf("%d",&n);
	vector <array<int,3>> wys;
	if(n<=12) wys=vi[n];
	else {
		if(n%4==0||n%4==3) wys.push_back({1,n-1,n}),n-=2;
		for(int k=n/2;n>=k;--n) {
			n-=11;
			if(n%4==2) {
				wys.push_back({n+1,n+2,n+3});
				wys.push_back({n+5,n+6,n+7});
				wys.push_back({n+9,n+10,n+11});
				wys.push_back({n,n+4,n+8});
			}
			if(n%4==3) {
				wys.push_back({n,n+1,n+2});
				wys.push_back({n+4,n+5,n+6});
				wys.push_back({n+8,n+9,n+10});
				wys.push_back({n+3,n+7,n+11});
			}
		}
	}
	printf("%d\n",(int)wys.size());
	for(auto z:wys) printf("%d %d %d\n",z[0],z[1],z[2]);
}
signed main() {
	vi[3]={{1,2,3}};
	vi[4]={{1,3,4}};
	vi[5]={{3,4,5}};
	vi[6]={{1,3,5},{2,4,6}};
	vi[7]={{3,5,7},{2,4,6}};
	vi[8]={{3,5,7},{2,6,8}};
	vi[9]={{1,3,5},{2,4,6},{7,8,9}};
	vi[10]={{4,6,10},{7,8,9}};
	vi[11]={{4,6,10},{7,8,9},{1,5,11}};
	vi[12]={{4,6,10},{7,8,9},{1,11,12}};
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：_edge_ (赞：0)

奇怪的做法，和题解区里面的都不太一样，比较劣。

就是，显然手玩一下大概能知道如果 $\gcd(x,y)=\gcd(x,z)=\gcd(y,z)$ 的话，我操作一下这三个数就可以使这三个数合法。

然后那大概率应该是先除以 $2$ 再除以 $3$。

我们考虑如果存在一个 $x$ 以及 $x \times k$，一定满足 $\gcd(x,x\times k) = x$ 合法，换句话说就是，前一半的点其实不操作也没有关系。

然后我们考虑把序列的奇数和偶数分开来考虑，就是奇数大概是三个三个绑，偶数就递归成子问题。

不过么，这有点问题，就是奇数的个数不一定是 $3$ 的倍数，此时我们如果直接从前一半拿出数来合并，那容易次数超出限制，大概是多加个 $\log$ 的常数，有点爆炸。

考虑把他们都拿出来，相邻两个取 $\gcd$，由于每一层不超过 $2$ 个，所以 $\gcd$ 是不重的，最后我们把那个最深的给询问掉，就是 $2^i$ 和 $2^{i+1}$，（建议看一眼代码，这里写的比较抽象）。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back 
using namespace std;
int n,N;
struct P3{
	int x,y,z;
};
vector < P3 > ans;
vector <int> e3;
vector <int> res;
void DFS(vector <int> e3,int ba) {
	int n=e3.size();
	if (n==3) {
		ans.pb({e3[0],e3[1],e3[2]});
		return ;
	}
	if (n==4) {
		ans.pb({e3[0],e3[2],e3[3]});
		return ;
	}
	if (n==5) {
		ans.pb({e3[2],e3[3],e3[4]});
		return ;
	}
	vector <int> A,B;
	for (int i=1;i<=n;i++) {
		if (i&1) A.pb(e3[i-1]);
		else B.pb(e3[i-1]);
	}
	DFS(B,ba*2);
	int len=A.size();
	while (A.size()>len/2) {
		if (A.size()-3>=len/2) { 
			int it=A.back();A.pop_back();
			int it1=A.back();A.pop_back();
			int it2=A.back();A.pop_back();
			ans.pb({it,it1,it2});
		}
		else {
			res.pb(A.back());A.pop_back();
			if (!A.size()) continue;
			if (A.back()>N/2) res.pb(A.back());
			break;
		}
	}
}
void solve() {
	cin>>n;N=n;ans.clear(); e3.clear();res.clear();
	for (int i=1;i<=n;i++) e3.pb(i);
	DFS(e3,1);
	reverse(res.begin(),res.end());
//	sort(res.begin(),res.end());
//	for (int i:res) cerr<<i<<" ";
//	cerr<<" ok?qwq?\n";
	int len2=res.size();
	for (int i=0;i<len2;i+=2) {
		if (i+1<len2) 
			ans.pb({__gcd(res[i],res[i+1]),res[i],res[i+1]});
		else {
			int p=1;
			while (res[i]%(p*2)==0) p*=2;
			ans.pb({p,2*p,res[i]});
		}
	}
	cout<<ans.size()<<"\n";
	for (P3 xx:ans)
		cout<<xx.x<<" "<<xx.y<<" "<<xx.z<<"\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	int t=0;cin>>t;
	while (t--) solve();
	return 0;
}
```

---

