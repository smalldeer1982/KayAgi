# Ordered Permutations

## 题目描述

给定一个长度为 $n$ 的整数排列 $p_1, p_2, \ldots, p_n$，其中包含从 $1$ 到 $n$ 的所有整数。我们定义一个如下的和式：

$$S(p) = \sum_{1 \le l \le r \le n} \min(p_l, p_{l+1}, \ldots, p_r)$$

我们希望找出所有能使 $S(p)$ 最大的排列，并从中按字典序选择第 $k$ 个。如果这样的排列数量少于 $k$，则输出 -1。

**解释说明：**
- 长度为 $n$ 的排列是一个由 $n$ 个不同的整数组成的序列，这些整数来源于 $1$ 到 $n$ 的一组数字。例如，$[2, 3, 1, 5, 4]$ 是一个符合要求的排列，而 $[1, 2, 2]$ 因为有重复数字 $2$ 而不符合，$[1, 3, 4]$ 也不符合要求，因为它包含了不在 $1$ 到 $n$ 范围内的数 $4$（$n = 3$）。
- 示例计算： 
  - 对于排列 $[1, 2, 3]$，$S(p)$ 计算为 $\min(1) + \min(1, 2) + \min(1, 2, 3) + \min(2) + \min(2, 3) + \min(3) = 1 + 1 + 1 + 2 + 2 + 3 = 10$。
  - 对于排列 $[2, 4, 1, 3]$，$S(p)$ 计算为 $\min(2) + \min(2, 4) + \min(2, 4, 1) + \min(2, 4, 1, 3) + \min(4) + \min(4, 1) + \min(4, 1, 3) + \min(1) + \min(1, 3) + \min(3) = 2 + 2 + 1 + 1 + 4 + 1 + 1 + 1 + 1 + 3 = 17$。
- 字典序小于：数组 $a$ 比数组 $b$ 在字典序上小的条件是：
  1. $a$ 是 $b$ 的一个前缀，且 $a \ne b$；
  2. 或者在第一个不同的位置上，$a$ 的元素小于 $b$ 的对应元素。

## 说明/提示

以下是所有长度为 3 的排列及其对应的 $S(p)$ 值（按字典序排序）：

| 排列 | $S(p)$ 的值 |
|------|-------------|
| $[1, 2, 3]$ | $10$ |
| $[1, 3, 2]$ | $10$ |
| $[2, 1, 3]$ | $9$ |
| $[2, 3, 1]$ | $10$ |
| $[3, 1, 2]$ | $9$ |
| $[3, 2, 1]$ | $10$ |

在第一个测试用例中，需输出长度为 3 的第 2 个符合条件的排列，看表格可以知道是 $[1, 3, 2]$。

在第二个测试用例中，需输出长度为 3 的第 3 个符合条件的排列，对应的是 $[2, 3, 1]$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
6
3 2
3 3
4 11
4 6
6 39
7 34```

### 输出

```
1 3 2 
2 3 1 
-1
2 4 3 1 
-1
2 3 4 5 7 6 1```

# 题解

## 作者：naroto2022 (赞：7)

# CF2040C 题解

### 题面

[原题传送门](https://codeforces.com/problemset/problem/2040/C)

[原题传送门（洛谷）](https://www.luogu.com.cn/problem/CF2040C)

### 题面

定义一个序列 $a$ 的权值为 $\begin{aligned}\sum_{1\leqslant l\leqslant r\leqslant n} \min(a_l,a_{l+1},\cdots,a_r)\end{aligned}$，给定 $n$ 和 $k$，问长度为 $n$ 的排列中权值最大的所有排列中字典序排第 $k$ 大的排列，若没有则输出 `-1`。

### 思路

首先先分析一个数列的权值的求法，单看题目中给的式子有点难想什么时候是最大的，考虑分析排列中每个数字会造成的贡献，设 $i$ 的位置为 $p_i$，$i$ 左边第一个比 $i$ 小的数的位置为 $l_i$，右边第一个比 $i$ 小的数的位置为 $r_i$，则 $i$ 对序列的贡献为 $i\times(p_i-l_i)\times(r_i-p_i)$。

接下来考虑什么时候序列的权值会取到最大值，首先肯定要确保大的数尽可能的被多选，而对于一个序列的权值最大就为 $\begin{aligned}\sum_{i=1}^{n} i\times(n-i+1)\end{aligned}$。

接下来考虑如何才会构成这种权值最大的情况，其实也很简单，首先我们知道对于一个数 $i$ 他的贡献为 $i\times(n-i+1)$，所以 $(p_i-l_i)\times(r_i-p_i)=n-i+1$。

容易想到（或者说暴力打个表），权值最大的排列的构造方式是从小到大放入每个数，每次放入一个数只能放在当前序列的最左边或者最右边，这样就可以满足每个数字的贡献。

所以权值最大的排列数为 $2^{n-1}$，所以若 $k>2^{n-1}$，则无解。

最后考虑字典序第 $k$ 大的排列，因为数字是从小到达放的，每个数字都有放左边或放右边两种选择，所以放入 $i$ 后还有 $2^{n-i-1}$ 种放法，即只要用 $k$ 与 $2^{n-i+1}$ 比较就可以决定当前 $i$ 是放最左端还是最右端，具体的有如下。

- 若 $k<=2^{n-i+1}$，则 $i$ 放左端。
- 若 $k>2^{n-i+1}$，则 $i$ 放右端，并将 $k$ 减去 $2^{n-i+1}$。

### 代码

[赛时记录](https://codeforces.com/contest/2040/submission/295631870)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
using namespace std;
const int MN=2e5+5;
ll n,k,ans[MN];
void write(ll n){if(n<0){putchar('-');write(-n);return;}if(n>9)write(n/10);putchar(n%10+'0');}
ll read(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
ll ksm(ll a, ll b){ll res=1;while(b){if(b&1)res=res*a;a=a*a;b>>=1;}return res;}
void solve(){
    for(int i=1; i<=n; i++) ans[i]=0;
    n=read();k=read();
    if(n<=40&&k>ksm(2,n-1)){write(-1);putchar('\n');return;}
    ll l=1,r=n,op=0;
    for(int i=1,j=n-2; i<n; i++,j--){
        if(j>40){ans[l++]=i;continue;}//作者怕爆 long long
        if(k>ksm(2,j)){
            ans[r--]=i;
            k-=ksm(2,j);
        }
        else{ans[l++]=i;}
    }
    ans[l]=n;
    for(int i=1; i<=n; i++) write(ans[i]),putchar(' ');putchar('\n');
}
int main(){
    ll T=read();while(T--)solve();
    return 0;
}
```

---

## 作者：ohjun (赞：6)

## 思路分析
容易发现 $s(p)$ 仅当最小的值在当前的最外侧时最小，因为如果在内侧，就会导致一个原来能取更大值的子序列取到更小的值，而在外侧的值还是会取到这个小的值，使 $s(p)$ 变小。综上，可以发现对于 $n$ 一共有 $2^{n - 1}$ 种排列满足最大值（除了最后一个数，其他数都有 $2$ 种选择），可以直接判断是否有解。如果有解，我们从小到大处理每一个数，对于第 $i$ 个数，把它放在前面则当前的字典序会小于等于 $2^{n - i - 1}$, 反之则大于。具体实现中只需要从小到大根据 $k$ 确定每一个数的位置，注意如果把第 $i$ 个数放在后面需要将 $k$ 减去 $2^{n - 1}$。还需要注意因为 $n$ 很大，做平方时开 long long 都会爆，但是 k 的上限却相对较小，所以可以找到一个 $maxv$ 满足只要 $n$ 大于这个值就一定大于 $k$ 的上限。
## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxv = log(1e12) / log(2) + 1;
const int maxn = 2e5 + 5;
ll k;
int t, n;
int ans[maxn];
 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n >> k;
		if(n <= maxv && k > (1LL << (n - 1)))
		{
			cout << "-1\n";
			continue;
		}
		int l = 1, r = n;
		for(int i = 1; i < n; i++)
		{
			if(n - 1 - i > maxv || k <= (1LL << (n - i - 1)))
			{
				ans[l] = i;
				l++;
			}
			else
			{
				k -= (1LL << (n - i - 1));
				ans[r] = i;
				r--;
			}
		}
		ans[l] = n;
		for(int i = 1; i <= n; i++)
			cout << ans[i] << ' ';
		cout << '\n';
	}
	return 0;
}
```

---

## 作者：MrPython (赞：2)

非常典型的 codeforces 小注意力题。

首先，我们发现当排列为 $1$ 到 $n$ 的正序数列时，$S$ 可以取到最大值。此时，$S(p)=1\times n + 2 \times (n-1) + 3 \times (n-2)\dots+n\times 1$。这是因为区间 $[1,1],[1,2],[1,3],\dots [1,n]$ 的最小值为 $1$，共 $n$ 个，区间 $[2,2],[2,3],\dots [2,n]$ 的最小值为 $2$，共 $n-1$ 个，以此类推。

我们考虑如下构造过程。假设现在已经构造好了 $x+1$ 到 $n$ 的排列方式，考虑 $x$ 可以插入到哪些位置。将 $x$ 插入到已排好的内容中间，将会导致原先的许多区间贡献变得更小，不如将 $x$ 放在头尾的位置更优。因此，最优排列的构造方案一定是从大往小，每次将当前的数放在头或尾的位置。

一共需决策 $n-1$ 个数，每个数都有可能放在首尾两个位置，因此一共有 $2^{n-1}$ 中方案。超出可以直接输出 `-1`。否则，对 $k$ 进行二进制拆分，根据当前位的值决定该数应该放在头还是尾。可以直接 deque 维护。

```cpp
#include <cstddef>
#include <deque>
#include <iostream>
using namespace std;
istream& fin = cin;
ostream& fout = cout;
using ui = unsigned int;
using uli = unsigned long long int;
using li = long long int;
int main(void) {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  size_t T;
  fin >> T;
  while (T--) {
    size_t n;
    uli k;
    fin >> n >> k;
    --k;
    if (n - 1 < 64 && k >= (1ull << (n - 1))) {
      fout << "-1\n";
      continue;
    }
    deque<ui> ans{(ui)n};
    for (ui i = n - 1; i > 0; --i) {
      if (k & 1)
        ans.emplace_back(i);
      else
        ans.emplace_front(i);
      k >>= 1;
    }
    for (ui i : ans) fout << i << ' ';
    fout << '\n';
  }
  return 0;
}
```

---

## 作者：TSY48 (赞：1)

**解题思路**

---

考虑如何取到最大值，不难发现，取到最大值等价为每个数有最大贡献。下面分别考虑 $1,\dots,n$ 的贡献。

若数字 $i\ (1\le i \le n)$ 在一个集合有贡献，则此集合只能包含大于等于 $i$ 的数，由此可以推出：要让 $i$ 最大贡献，则 $n,n-1,\dots,i$ 必须连在一起。则满足条件的的构造必为 $n$ 和 $n-1$ 在一起，$n-1$ 和 $n-2$ 在一起，……，$2$ 和 $1$ 在一起。

有上即可推出 $1$ 在第一个位置或者第 $n$ 个位置，$2$ 在第二个位置或者第 $n-1$ 个位置，$i$ 在第 $i$ 个位置或者 $n-i+1$ 个位置。

则构造是先考虑 $i$ 在第 $i$ 个位置上，如果个数不够多，则把 $i$ 放第 $n-i+1$ 个位置上。细节看代码。

**部分代码**

---


```cpp
    k--;
    if(n<=60 && f[n-1]<=k){
        printf("-1\n");
        return ;
    }
    int l=0,r=n+1;
    for(int i=1;i<n;i++){
        if((n-i-1)>60 || k<f[n-i-1]){
            rec[++l]=i;
        }
        else{
            k-=f[n-i-1];
            rec[--r]=i;
        }
    }
    rec[++l]=n;
    for(int i=1;i<=n;i++) printf("%d ",rec[i]);
```

---

## 作者：lfxxx (赞：1)

所有合法排列的生成方式是从小往大依次将每个数放到当前剩余位置的开头或者结尾。证明考虑归纳。前 $n-1$ 个数的两种选择均会使得后面生成的排列不同，并且 $i$ 放剩余位置开头的排列字典序一定小于 $i$ 放剩余位置结尾的排列的字典序。

于是计算第 $k$ 个合法排列就从小的数往大的数一个个确定放的位置即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+114;
int a[maxn],n,k;
void work(){
    cin>>n>>k;
    if(k>(1ll<<min(1ll*60,n-1))) cout<<"-1\n";
    else{
        int l=1,r=n;
        for(int i=1;i<=n-1;i++){
            if(k<=(1ll<<min(1ll*60,n-1-i))){
                a[l]=i;
                l++;
            }else{
                k-=(1ll<<min(1ll*60,n-1-i));
                a[r]=i;
                r--;
            }
        }
        a[l]=a[r]=n;
        for(int i=1;i<=n;i++) cout<<a[i]<<' ';
        cout<<'\n';        
    }
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}

```

---

## 作者：wfc284 (赞：0)

首先考虑何时 $S(p)$ 取最大值。  
设有最大的 $l$ 满足 $l < i \wedge p_l > p_i$，最小的 $r$ 满足 $r > i \wedge p_r > p_i$，则 $p_i$ 对 $S(p)$ 的贡献就是 $p_i(r-l+1)$。（证明不难）  
而对于 $p_i = v$，有 $(v-1)$ 个元素小于 $p_i$，则其 $(r-l+1)_{max} = n-(v-1)$。  
我们恰好可以构造出这样的序列。方法就是让小的元素尽量往两边填，这样对更大元素的影响更小。  
考虑这样的构造方式：从 $1$ 到 $n$ 扫，对于值 $v$，有两种填充方式，填在未填的最左或最右。  
一共显然有 $2^{n-1}$ 种方案。若小于 $k$，则无解。  
然后就可以逐位确定了。把 $k$ 二进制化，从 $n-2$ 往 $0$ 扫，若该位是 0，则填最左；反之填最右。正确性类似于二分（~只可意会不可言传~）。
```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define int long long
#define pii pair<int, int> 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 2e5+2;
	
	int n, k;
	int a[N];
	
	void main() {
		cin >> n >> k;
		if(n <= 40 && 1ll << n-1 < k) {
			printf("-1\n");
			return;
		} 
		
		--k;
		int h = 0, t = n-1, x = 0;
		for(int c = n-2; c >= 0; --c) {
			if(c > 40 || (k & 1ll << c) == 0) a[h++] = ++x;
			else a[t--] = ++x;
		}
		a[h] = ++x;
		for(int i = 0; i < n; ++i) printf("%lld ", a[i]);
		puts("");
	}
}

signed main() {
	#ifdef filename
		FileOperations();
	#endif
	
	int _;
	cin >> _;
	while(_--) Traveller::main();
	return 0;
}


```

---

## 作者：Him_shu (赞：0)

## 题意

考虑从 $1$ 到 $n$ 的整数的排列 $p_1, p_2, \ldots, p_n$。我们可以为它引入下面的和：

$$S(p) = \sum_{1 \le l \le r \le n} \min(p_l, p_{l + 1}, \ldots, p_r)$$

设 $n$ 个数的全排列中的一个为 $p$ 且 $p$ 按字典序排列，求其中 $S(p)=S(1,2,3, \ldots,n)$ 的第 $k$ 个 $p$ 的每一个值。


## 分析

比赛时思考了一下，打算打表看一下有没有规律，这是 $n=5$ 且 $S(p)=S(1,2,3,4,5)=35$ 的表（**[打表代码](https://www.luogu.com.cn/paste/d1mknt4x)**）：

![](https://cdn.luogu.com.cn/upload/image_hosting/5vwobgs7.png)

不难发现，答案有 $2^{n-1}$，那么考虑把它分成以 $1,2,4,8 \dots$ 的段。

![](https://cdn.luogu.com.cn/upload/image_hosting/xv2h1t07.png)

又发现每一个可以被表示成另一个串的一个后缀的相反，如 $5$ 号是 $4$ 号的后 $5$ 个相反，再加上图，不难发现：

- 一个串与它上面的线段有关，具体就是：与上面的线段做一个镜像的位置。
- 至于后缀的长度 $=$ 上面的线段在所有线段的位置 $+1$。

那么它上面的线段在所有线段的位置怎么求呢？

- 不妨设它的位置是 $k$，那么上面的线段在所有线段的位置 $=k$ 的上一个二次幂的指数 $+1$。

给出代码：
```cpp
int last_pow2(int x){
	return (int)pow(2,(int)log2(x-1));
}
```

既然知道了上面的线段在所有线段的位置的话，镜像的位置给出代码：
```cpp
int jx(int x){
	return last_pow2(x)-(x-last_pow2(x))+1;
}
```
翻转的后缀的长度给出代码：
```cpp
int qx(int x){
	return (int)log2(x-1)+2;
}
```

那么时间计算呢？

- $O(n \times \log{k})$。

到此问题解决。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define m_p make_pair
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=x*10+ch-'0',ch=getchar();}return x*f;}
void write(int x){if(x<0){putchar('-'),x=-x;}if(x>9){write(x/10);} putchar(x%10+'0');return;}
int qpow(int a,int b,int mod){if(b==0){return 1;}int mid=qpow(a,b/2,mod)%mod;if(b&1){return (mid*mid%mod)*a%mod;}return mid*mid%mod;}
const int N=2e5+5,inf=1e14;
int t;
int n,k;
int a[N];
vector<int>v;
int last_pow2(int x){//上面的线段在所有线段的位置
	return (int)pow(2,(int)log2(x-1));
}
int qx(int x){//翻转的后缀的长度
	return (int)log2(x-1)+2;
}
int jx(int x){//镜像的位置
	return last_pow2(x)-(x-last_pow2(x))+1;
}
signed main(){
	cin>>t;
	while(t--){
		v.clear();
		cin>>n>>k;
//		cout<<"a:";
		if(n<=60&&(int)pow(2,n)<k){
			cout<<"-1\n";
			continue;
		}//判断是否符合
		for(int i=1;i<=n;i++){
			a[i]=i;
		}
		while(k!=1){
			v.push_back(qx(k));
//			cout<<qx(k)<<":"<<jx(k)<<"\n";
			k=jx(k);
		}
		reverse(v.begin(),v.end());
		for(auto i:v){
			reverse(a+(n-i)+1,a+n+1);
		}//翻转
		for(int i=1;i<=n;i++){
			cout<<a[i]<<" ";
		}cout<<"\n";
	}
	return 0;
}
```

---

