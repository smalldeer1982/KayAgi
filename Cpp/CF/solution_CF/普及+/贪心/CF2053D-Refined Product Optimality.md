# Refined Product Optimality

## 题目描述

As a tester, when my solution has a different output from the example during testing, I suspect the author first.

— Chris, [a comment](https://codeforces.com/blog/entry/133116?#comment-1190579)



Although Iris occasionally sets a problem where the solution is possibly wrong, she still insists on creating problems with her imagination; after all, everyone has always been on the road with their stubbornness... And like ever before, Iris has set a problem to which she gave a wrong solution, but Chris is always supposed to save it! You are going to play the role of Chris now:

- Chris is given two arrays $ a $ and $ b $ , both consisting of $ n $ integers.
- Iris is interested in the largest possible value of $ P = \prod\limits_{i=1}^n \min(a_i, b_i) $ after an arbitrary rearrangement of $ b $ . Note that she only wants to know the maximum value of $ P $ , and no actual rearrangement is performed on $ b $ .
- There will be $ q $ modifications. Each modification can be denoted by two integers $ o $ and $ x $ ( $ o $ is either $ 1 $ or $ 2 $ , $ 1 \leq x \leq n $ ). If $ o = 1 $ , then Iris will increase $ a_x $ by $ 1 $ ; otherwise, she will increase $ b_x $ by $ 1 $ .
- Iris asks Chris the maximum value of $ P $ for $ q + 1 $ times: once before any modification, then after every modification.
- Since $ P $ might be huge, Chris only needs to calculate it modulo $ 998\,244\,353 $ .

Chris soon worked out this problem, but he was so tired that he fell asleep. Besides saying thanks to Chris, now it is your turn to write a program to calculate the answers for given input data.

Note: since the input and output are large, you may need to optimize them for this problem.

For example, in C++, it is enough to use the following lines at the start of the main() function:

```
<pre class="lstlisting">```
int main() {<br></br>    std::ios::sync_with_stdio(false);<br></br>    std::cin.tie(nullptr); std::cout.tie(nullptr);<br></br>}<br></br>
```
```

## 说明/提示

In the first test case:

- Before the modifications, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = \prod\limits_{i=1}^n \min(a_i, b_i) = 1 \cdot 1 \cdot 2 = 2 $ . We can prove that this is the maximum possible value. For example, if Chris rearranges $ b = [2, 3, 1] $ , $ P $ will be equal $ 1 \cdot 1 \cdot 1 = 1 < 2 $ , which is not optimal.
- After the first modification, Chris can rearrange $ b $ to $ [1, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the second modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 1 \cdot 1 \cdot 3 = 3 $ , which is maximized.
- After the third modification, Chris can rearrange $ b $ to $ [2, 2, 3] $ so that $ P = 6 $ , which is maximized.
- After the fourth modification, Chris can rearrange $ b $ to $ [2, 2, 4] $ so that $ P = 6 $ , which is maximized.

## 样例 #1

### 输入

```
4
3 4
1 1 2
3 2 1
1 3
2 3
1 1
2 1
6 8
1 4 2 7 3 5
7 6 5 6 3 3
2 5
1 6
1 5
1 5
1 5
2 3
2 3
1 6
13 8
7 7 6 6 5 5 5 2 2 3 4 5 1
1 4 1 9 6 6 9 1 5 1 3 8 4
2 2
2 11
2 4
2 4
1 7
1 1
2 12
1 5
5 3
10000000 20000000 30000000 40000000 50000000
10000000 20000000 30000000 40000000 50000000
1 1
2 2
2 1```

### 输出

```
2 3 3 6 6
840 840 1008 1344 1680 2016 2016 2016 2352
2116800 2646000 3528000 3528000 3528000 4233600 4838400 4838400 4838400
205272023 205272023 205272023 264129429```

# 题解

## 作者：cjh20090318 (赞：6)

复活后的第一篇题解和比赛。

感觉这是一个很有意思的题。

## 题意

有两个长度为 $n$ 的序列 $a,b$。

有 $q$ 次修改，每次修改给出两个整数 $o,x$：

- $o=1$ 时，$a_x \gets a_x + 1$。
- $o=2$ 时，$b_x \gets b_x + 1$。

设 $p$ 是 $b$ 的一种排列，在第一次修改前和每次修改后，你需要求出所有满足条件的 $p$ 中 $\prod\limits_{i=1}^n \min(a_i, p_i)$ 的最大值。

由于答案可能很大，所以对 $998244353$ 取模。

## 分析

不难证明，最大值即为将 $a,b$ 升序排列后所求的值。

简单证明一下，假设 $a_1 < a_2, b_1 < b_2$，那么 $\min(a_1,b_2) \times \min(a_2,b_1) \le \min(a_1,b_1) \times \min(a_2,b_2)$，所以降序排列会使答案变得更劣。

于是就可以在 $O(n \log n)$ 的时间复杂度内求出修改前答案的值，接下来考虑修改操作。

修改只会修改一个，也只会增加 $1$ 的值，所以对答案的影响并不会很大。

修改的时候如果要调整序列来维持单调性是一件很麻烦的事情。假设我们修改的是 $a_x$，只需要在排序的序列中修改最后一个值为 $a_x$ 的位置，就不会影响其单调性。

于是求出这个位置后，可以撤销该位置对答案原有的贡献，乘上该位置的逆元，然后修改后再将贡献加入进去即可。

以上操作就可以用二分和快速幂解决，修改 $b$ 序列的情况同理。

总体时间复杂度为 $O(n \log n + q \log n)$

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
#define MAXN 200002
using namespace std;
typedef long long LL;
constexpr int mod=998244353;
int n,q;
int qpow(int a,int b=mod-2){
	int ret=1;
	for(;b;b>>=1,a=(LL)a*a%mod)if(b&1)ret=(LL)ret*a%mod;
	return ret%mod;
}
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];//c,d 序列表示排序后的 a,b 序列。
void solve(){
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i],c[i]=a[i];
	for(int i=1;i<=n;i++) cin>>b[i],d[i]=b[i];
	sort(c+1,c+n+1),sort(d+1,d+n+1);
	int ans=1;
	for(int i=1;i<=n;i++) ans=(LL)ans*min(c[i],d[i])%mod;
	cout<<ans<<' ';
	for(int o,x,p;q--;){
		cin>>o>>x;
		p=0;
		if(o==1)
			p=upper_bound(c+1,c+n+1,a[x])-c-1,//找到第一个大于 a_x 的位置的前一个，即最后一个等于 a_x 的位置。
			ans=(LL)ans*qpow(min(c[p],d[p]))%mod,//除以这个数，即乘这个数的逆元。
			++a[x],++c[p];//对这些位置进行修改。
		else if(o==2)
			p=upper_bound(d+1,d+n+1,b[x])-d-1,//b 序列同理。
			ans=(LL)ans*qpow(min(c[p],d[p]))%mod,
			++b[x],++d[p];
		ans=(LL)ans*min(c[p],d[p])%mod;//乘上修改后这个位置的贡献。
		cout<<ans<<' ';
	}
	cout<<'\n';
}
int main(){
	ios::sync_with_stdio(false),cin.tie(nullptr);
	int T;cin>>T;
	while(T--) solve(); 
	return 0;
}
```

---

## 作者：yvbf (赞：2)

![](bilibili:BV1WN6VYEEGs?t=1367)

---

## 作者：Drifty (赞：2)

### Solution

建议降级。

首先有显然的贪心：题目中式子在 $a$，$b$ 都顺序或逆序时取到最大值，邻项交换易证。

考虑修改，假设我们要修改 $a_x = t$，那么我们找到最后一个等于 $t$ 的位置加一，这样序列一定保持有序。$b$ 的修改同理。更新贡献也好做，乘上原来贡献的逆元然后乘上新的贡献即可。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using i64 = long long;
using u32 = unsigned;
static constexpr int P = 998244353;
int T, n, q;
i64 inv (i64 a, int x = P - 2) {
	i64 res = 1;
	for (; x; x >>= 1, a = a * a % P) 
		if (x & 1) res = res * a % P;
	return res;
}
void solve() {
	cin >> n >> q;
	vector <int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i ++) cin >> a[i];
	for (int i = 1; i <= n; i ++) cin >> b[i];
	vector <int> u(a), v(b);
	sort (a.begin(), a.end());
	sort (b.begin(), b.end());
	i64 ans = 1;
	for (int i = 1; i <= n; i ++)
		ans = ans * min(a[i], b[i]) % P;
	cout << ans << ' ';
	for (int op, x, p; q --; ) {
		cin >> op >> x;
		if (op == 1) {
			p = upper_bound(a.begin(), a.end(), u[x]) - a.begin() - 1;
			ans = ans * inv(min(a[p], b[p])) % P; u[x] ++; a[p] ++;
		}
		if (op == 2) {
			p = upper_bound(b.begin(), b.end(), v[x]) - b.begin() - 1;
			ans = ans * inv(min(a[p], b[p])) % P; v[x] ++; b[p] ++;
		}
		ans = ans * min(a[p], b[p]) % P;
		cout << ans << ' ';
	}
	cout << '\n';
}
int32_t main() {
	cin.tie(NULL) -> sync_with_stdio(false);
	for (cin >> T; T --; ) solve();
	return 0;
}
```

---

## 作者：Eason_cyx (赞：2)

第一次自己做出 Div.2D（虽然是 Div.1+2），纪念一下。

Good Bye，2024！

-------

首先考虑没有修改操作怎么做。不难发现，我们将 $a$ 和 $b$ 都从小到大排序，结果显然是最优的。

接下来考虑修改。因为每次修改结束后，如果暴力的话，我们都会重新排序，并且由于每次都是 $+1$ 操作，所以除了相等的数以外数组仍然是有序的。那么实际上你可以直接找到最后一个和原来应该修改的那个数相等的一个数，修改这个数即可。

但是如果暴力修改，复杂度仍然是 $O(Tnq)$，无法通过。所以我们可以考虑初始时求出答案，记为 $ans$。对于每一次操作，假设最终修改的位置是 $x$，那么假设更新的是 $a$，实际上答案更新为 $ans \div \min(a_x,b_x) \times \min(a_x+1,b_x)$。$b$ 同理。由于有除法，所以需要再算一个逆元。这样就可以快速维护答案了。

最终时间复杂度 $O(Tn\log M)$，$M$ 是模数，此处 $M=998,244,353$。可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int inv(int x) {
	int a = x, b = 998244351ll, ans = 1;
	while(b) {
		if(b & 1) ans = (ans * a) % 998244353ll;
		a = a * a % 998244353ll; b >>= 1;
	} return ans;
} struct node {
	int id, x;
	bool operator < (const node& y) const {
		return x < y.x;
	}
} a[200005], b[200005];
int ato[200005], bto[200005];
signed main() {
	int t; cin >> t;
	while(t--) {
		int n, q; cin >> n >> q; 
		for(int i = 1;i <= n;i++) cin >> a[i].x, a[i].id = i;
		for(int i = 1;i <= n;i++) cin >> b[i].x, b[i].id = i;
		sort(a+1,a+n+1); sort(b+1,b+n+1);
		for(int i = 1;i <= n;i++) ato[a[i].id] = a[i].x, bto[b[i].id] = b[i].x;
		long long ans = 1;
		for(int i = 1;i <= n;i++) ans = (ans * min(a[i].x, b[i].x)) % 998244353ll;
		cout << ans << " ";
		while(q--) { int o, x; cin >> o >> x;
			if(o == 1) { int y = x; x = ato[x]; 
				int pos = upper_bound(a+1, a+n+1, (node){y, x}) - a - 1;
				ans = (ans * inv(min(a[pos].x,b[pos].x))) % 998244353ll;
				ans = (ans * min(a[pos].x+1,b[pos].x)) % 998244353ll;
				a[pos].x++; ato[y]++;
			} else { int y = x; x = bto[x];
				int pos = upper_bound(b+1, b+n+1, (node){y, x}) - b - 1;
				ans = (ans * inv(min(a[pos].x,b[pos].x))) % 998244353ll;
				ans = (ans * min(a[pos].x,b[pos].x+1)) % 998244353ll;
				b[pos].x++; bto[y]++;
			} cout << ans << " ";
		} cout << "\n";
	} 
	return 0;
}
```

---

## 作者：Komeijizen (赞：1)

## Preface

成功靠切这题上了蓝名，写个题解纪念一下。

## Problem

给定长度为 $n$ 的序列 $A,B$，可以把 $B$ 以任意顺序重排，令 $P = \prod\limits_{i=1}^n \min(A_i, B_i)$，给出 $q$ 个更改操作，每次将 $A$ 或 $B$ 中的某个数加一，求每次操作后（包括未操作时）$P$ 的最大值 $\bmod \ 998244353$ 的结果。

## Solution

看到能将序列重排，考虑邻项交换贪心。   
设$A_i \ge A_j$，$B_p \ge B_q$，不妨设在一开始把 $A_i$ 与 $B_p$ 相匹配，把 $A_j$ 与 $B_q$ 相匹配。如果把 $B_p$ 与 $B_q$ 交换的话，就会变成 $A_i$ 与 $B_q$ 相匹配，$ A_j$ 与 $B_p$ 相匹配。    
然后进行分类讨论。首先，当 $A_j\ge B_p$ 或 $A_i\le B_q$ 时，交不交换没有影响，对答案造成贡献的一定是较小的两个数。    
其次，则有 $A_i \ge B_p \ge A_j \ge B_q$ 或 $B_p \ge A_i \ge B_q \ge A_j$
。这里只证前一种情况，后一种同理。  
于是可得在交换之前，这两项对答案的贡献为 $P_0=\min (A_i , B_p) \times \min(A_j,B_q)=A_i\times A_j$，交换之后的贡献为 $P_1=\min (A_i , B_q) \times \min(A_j,B_p)=A_j\times B_p$。令两式相减，得 $P_0-P_1=A_j\times (A_i-B_p)$。由于 $A_j$ 和 $(A_i-B_p)$ 一定都非负，所以此时交换一定不优。   
因此，我们得到了最大化 $P$ 的方案：将 $A$ 与 $B$ 分别排序后逐个匹配即可。（因为可以先把 $A$ 排序，然后把 $B$ 中的每个逆序对互相交换，根据上文的证明，一定是不劣的）。

然后考虑如何实现修改操作。由于每次只会把一个数加一，因此它的排名会且仅会上升 $1$。考虑维护 $C,D$ 序列，表示 $A,B$ 序列排序后的结果，以及  $lst1,lst2$ 数组，分别表示 $C,D$ 序列中某个数最后一次出现的位置。修改时，被修改的数就会被调整到对应的 $lst$ 的位置，用快速幂逆元撤销被更改的一项的贡献后乘上新的贡献即可。    
每组数据的时间复杂度为 $O(n\log n)$。

## Code

```cpp
signed main()
{
    int t = read();
    while (t--) {
        lst1.clear(),lst2.clear();
        n=read(),q=read();
        for(int i=1;i<=n;i++)A[i]=read(),C[i]=A[i];
        for(int i=1;i<=n;i++)B[i]=read(),D[i]=B[i];
        sort(C+1,C+1+n);
        sort(D+1,D+1+n);
        int tans=1;
        for(int i=1;i<=n;i++){
            lst1[C[i]]=i;
            lst2[D[i]]=i;
            tans=tans*min(C[i],D[i])%mod;
        }
        printf("%lld ",tans);
        for(int i=1;i<=q;i++){
            int o=read(),x=read();
            if(o==1){
                int pre=A[x],lst=lst1[pre];
                int pd=min(C[lst],D[lst]);
                tans=tans*qpow(pd,mod-2)%mod;
                A[x]++;
                
                C[lst]++;
                lst1[pre]--;
                lst1[C[lst]]=max(lst1[C[lst]],lst);
                tans=tans*min(C[lst],D[lst])%mod;
            }else{
                int pre=B[x],lst=lst2[pre];
                int pd=min(C[lst],D[lst]);
                tans=tans*qpow(pd,mod-2)%mod;
                B[x]++;
                
                D[lst]++;
                lst2[pre]--;
                lst2[D[lst]]=max(lst2[D[lst]],lst);
                tans=tans*min(C[lst],D[lst])%mod;
            }
            printf("%lld ",tans);
        }
        printf("\n");
    }
}

```

---

## 作者：Sakura_Emilia (赞：1)

# Solution

本题比较有意思，使用排序、二分和乘法逆元。

题目要求对于 $a$ 和 $b$ 两个数组依次的相同位置上，较小值的乘积最大。怎样排列两个数组 $a$ 和 $b$ 才能使得乘积最大？一种直观地想法是，当数组 $a$ 和 $b$ 排列顺序一致时，也就是都是从小到大排列时，值最大。该结论可以使用数学归纳法或阿贝尔变换来证明，思路类似于排序不等式的证明方法，其实就是排序不等式的一个变种问题，顺序和大于等于乱序和大于等于逆序和，这里变种为最小值乘积。

当然直接观察样例数据，其实也很容易发现这个规律。

因此读入数据后，备份原始顺序后再进行排序。当修改一个值时，根据备份的原始顺序，确定修改对象的目标值，再根据目标值进行二分查找，定位到其在排序后数组中的位置。之后同时修改排序数组和备份数组中的值，以做更新。

由于是乘积，在更新的时候，取模的除法操作可以使用乘法逆元来完成。由于 $998244353$ 是著名质数，因此可以使用快速幂求逆元。当然也可以预处理提前把 $998244353$ 的逆元计算出来作为常数。

# Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
#define el else
#define wl while
#define rt return
#define il inline
#define br cout << endl;
using namespace std;
const int N = 1e6 + 8, mod = 998244353;

int T, n, q, o, x;
int a[N], b[N], ak[N], bk[N];

il int qmi(int _a, int _b, int _p) {
    int _res = 1;
    wl(_b) {
        if(_b & 1)
            _res = _res * _a % _p;

        _a = _a * _a % _p;
        _b >>= 1;
    }
    rt _res;
}

int inverseElement(int _a) {
    rt qmi(_a, mod - 2, mod);
}

il void solve() {
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> a[i], ak[i] = a[i];
    for(int i = 1; i <= n; i++)
        cin >> b[i], bk[i] = b[i];
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    int ans = 1;
    for(int i = 1; i <= n; i++)
        ans = ans * min(a[i], b[i]) % mod;
    cout << ans << " ";
    wl(q--) {
        cin >> o >> x;
        if(o == 1) {
            if(a[n] == ak[x]) {
                if(a[n] < b[n]) {
                    ans = ans * inverseElement(a[n]) % mod;
                    ans = ans * (a[n] + 1) % mod;
                }
                a[n]++;
            } el {
                int id = lower_bound(a + 1, a + n + 1, ak[x] + 1) - a - 1;
                if(a[id] < b[id]) {
                    ans = ans * inverseElement(a[id]) % mod;
                    ans = ans * (a[id] + 1) % mod;
                }
                a[id]++;
            }
            ak[x]++;
        } el {
            if(b[n] == bk[x]) {
                if(b[n] < a[n]) {
                    ans = ans * inverseElement(b[n]) % mod;
                    ans = ans * (b[n] + 1) % mod;
                }
                b[n]++;
            } el {
                int id = lower_bound(b + 1, b + n + 1, bk[x] + 1) - b - 1;
                if(b[id] < a[id]) {
                    ans = ans * inverseElement(b[id]) % mod;
                    ans = ans * (b[id] + 1) % mod;
                }
                b[id]++;
            }
            bk[x]++;
        }
        cout << ans << " ";
    }
    br
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    wl(T--)
        solve();

    rt 0;
}
```

---

## 作者：lalaji2010 (赞：1)

# CF2053D Refined Product Optimality

## 分析

由于对应位置上的数取最小值相乘，那么大数配小数只会浪费大数，所以贪心，我们升序排列，令大数与大数相对应，然后就做完了第一问。

后面需要我们维护这个升序序列，由于修改是在原序列上进行，所以我们不妨再记录一下原序列的每个位置的元素，当其进行修改时，我们只需要在升序排序的序列中二分找到最后一个等于它的数然后加 $1$ 即可。再加完之后，我们判断一下当前两个升序排列数组中修改位置的两个对应元素的最小值是否变大，若变大，记原最小值为 $mne$，先最小值为 $mn$，答案令 $res$ 的值修改为 $res \div mne \times mn$ 即可。由于需要取模 $998244353$，所以用费马小定理求逆元即可。

## AC CODE
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=998244353;
int t;
int n,q;
int a[200005],b[200005],ae[200005],be[200005];
long long ksm(long long a,long long b){
	long long res=1;
	while(b){
		if(b&1){
			res=res*a%mod;
		}
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
signed main(){
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
	cin>>t;
	while(t--){
		cin>>n>>q;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			ae[i]=a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
			be[i]=b[i];
		}
		sort(a+1,a+1+n);
		sort(b+1,b+1+n);
		long long ans=1;
		for(int i=1;i<=n;i++){
			ans=ans*min(a[i],b[i])%mod;
		}
		cout<<ans<<" ";
		while(q--){
			int o,x;
			cin>>o>>x;
			if(o==1){
				int pos=upper_bound(a+1,a+1+n,ae[x])-a-1;
				int mne=min(a[pos],b[pos]);
				a[pos]++;
				ae[x]++;
				int mn=min(a[pos],b[pos]);
				//if(mne==mn) continue;
				int inv=ksm(mne,mod-2);
				ans=ans*inv%mod*mn%mod;
			}else{
				int pos=upper_bound(b+1,b+1+n,be[x])-b-1;
				int mne=min(a[pos],b[pos]);
				b[pos]++;
				be[x]++;
				int mn=min(a[pos],b[pos]);
				//if(mne==mn) continue;
				int inv=ksm(mne,mod-2);
				ans=ans*inv%mod*mn%mod;
			}
			cout<<ans<<" ";
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：wfc284 (赞：0)

首先让我们输出的是不操作的值。不定序，一看就很贪心。经过分类分类分类可证，$a,b$ 都是升序（降序）的时候是最优的。  
再看加操作的。相当于要维护这两个升序序列。我们发现，每次操作影响的值很少，最多两个值。在一个连续段中，修改的值相当于和末尾值交换，再加一。  

唐点：
找这个末尾没必要维护一堆下标然后写挂，用个二分足矣。反正用了排序，都是带 $\log$ 的。

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define Linf 0x3f3f3f3f3f3f3f3f
#define pii pair<int, int>
#define int long long 
#define all(v) v.begin(), v.end()
using namespace std;

//#define filename "xxx" 
#define FileOperations() freopen(filename".in", "r", stdin), freopen(filename".out", "w", stdout)


namespace Traveller {
	const int N = 4e5+2, mod = 998244353;
	void mul(int &a, int b, int p = mod) { a = (a * b % p + p) % p; }
	int qpow(int a, int b, int p = mod) {
		int res = 1;
		a %= p;
		while(b) {
			if(b & 1) mul(res, a, p);
			b >>= 1;
			mul(a, a, p);
		}
		return res;
	} 
	int inv(int a) { return qpow(a, mod-2); }
	
	int n, q;
	pii a[N], b[N];
	int c[N], d[N];
	int rev1[N], rev2[N];
	
	int ans;
	void work(pii *a, pii *b, int *c, int *rev, int x) {
		x = c[x];
		int y = upper_bound(a+1, a+n+1, pii(a[x].first, inf)) - a - 1;
		int p = rev[x], q = rev[y];
		
		//swap
		c[p] = y, c[q] = x;
		rev[x] = q, rev[y] = p;
		swap(x, y);
		
		mul(ans, inv(min(a[x].first, b[x].first)));
		mul(ans, min(++a[x].first, b[x].first));
	}
	
	void main() {
		cin >> n >> q;
		for(int i = 1, x; i <= n; ++i) {
			scanf("%lld", &x);
			a[i] = pii(x, i);
		}
		for(int i = 1, x; i <= n; ++i) {
			scanf("%lld", &x);
			b[i] = pii(x, i);
		}
		sort(a+1, a+n+1);
		sort(b+1, b+n+1);
		for(int i = 1; i <= n; ++i) c[a[i].second] = i, rev1[i] = a[i].second;
		for(int i = 1; i <= n; ++i) d[b[i].second] = i, rev2[i] = b[i].second;
		
		ans = 1;
		for(int i = 1; i <= n; ++i) mul(ans, min(a[i].first, b[i].first));
		printf("%lld ", ans);
		for(int i = 1, opt, x; i <= q; ++i) {
			scanf("%lld%lld", &opt, &x);
			if(opt == 1) work(a, b, c, rev1, x);
			else work(b, a, d, rev2, x);
			printf("%lld ", ans);
		}
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

## 作者：Redshift_Shine (赞：0)

首先有一个事实，也就是将 $a$ 和 $b$ 全部升序排序是最优的。读者自证不难。

难点在于如何快速维护排序后的序列。

首先按照题目要求读入序列 $a$ 和 $b$，并将它们排序后的结果记为 $c$ 和 $d$。

注意到每次操作对于每个数的增量最多为 $1$，所以操作时选出对应数组中与操作对象相等的排在最后的元素加 $1$ 就不会破坏单调性。

时间复杂度 $O(n\log n+m(\log n+\log V))$。

```c++
// #define Redshift_Debug
#ifdef Redshift_Debug
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdio>
using namespace std;
const int N = 2e5 + 10, mod = 998244353;
template <typename _Tp> inline void read(_Tp &x)
{
	static char ch;
	while (ch = getchar(), !isdigit(ch))
		;
	x = (ch ^ 48);
	while (ch = getchar(), isdigit(ch))
		x = (x << 3) + (x << 1) + (ch ^ 48);
}
template <typename _Tp, typename... _Args> inline void read(_Tp &x, _Args &...args)
{
	read(x);
	read(args...);
}
int n, m, ps;
using ll = long long;
ll a[N], b[N], ca[N], cb[N], res;
inline ll fsp(ll x, ll y)
{
	ll res = 1;
	while (y)
	{
		if (y & 1)
			res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}
void run()
{
	read(n, m);
	for (int i = 1; i <= n; i++)
	{
		read(a[i]);
		ca[i] = a[i];
	}
	for (int i = 1; i <= n; i++)
	{
		read(b[i]);
		cb[i] = b[i];
	}
	sort(ca + 1, ca + n + 1);
	sort(cb + 1, cb + n + 1);
	res = 1;
	for (int i = 1; i <= n; i++)
	{
		res = res * min(ca[i], cb[i]) % mod;
	}
	printf("%lld", res);
	for (int i = 1, x, y; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		if (x == 1)
		{
			ps = upper_bound(ca + 1, ca + n + 1, a[y]) - ca - 1;
			ca[ps]++;
			a[y]++;
			if (ca[ps] > cb[ps])
			{
				printf(" %lld", res);
				continue;
			}
			res = res * fsp(ca[ps] - 1, mod - 2) % mod;
			res = res * ca[ps] % mod;
			printf(" %lld", res);
			continue;
		}
		ps = upper_bound(cb + 1, cb + n + 1, b[y]) - cb - 1;
		cb[ps]++;
		b[y]++;
		if (cb[ps] > ca[ps])
		{
			printf(" %lld", res);
			continue;
		}
		res = res * fsp(cb[ps] - 1, mod - 2) % mod;
		res = res * cb[ps] % mod;
		printf(" %lld", res);
	}
	putchar('\n');
}
int main()
{
#ifdef Redshift_Debug
	auto st = chrono::high_resolution_clock::now();
#endif
	int T = 1;
	read(T);
	while (T--)
		run();
#ifdef Redshift_Debug
	auto ed = chrono::high_resolution_clock::now();
	fprintf(stderr, "%.9lf\n", (ed - st).count() / 1e9);
#endif
}
```

---

## 作者：_lmh_ (赞：0)

题面只允许我们重排 $\{b_i\}$，但这等价于对 $\{a_i\},\{b_i\}$ 都进行重排，所以先将 $\{a_i\}$ 从小到大排序。

下证 $b_1\le b_2\le \cdots \le b_n$ 的重排是一组最优解。

考虑调整法，现在假设 $a_i<a_j,b_i<b_j$，将 $b_i,b_j$ 交换，答案差值为 $\min\{a_i,b_j\}\min\{a_j,b_i\}-\min\{a_i,b_i\}\min\{a_j,b_j\}$，手玩一下六种可能的大小关系发现都 $\le 0$。所以，将 $b$ 中的逆序对交换一定不劣。

然后就简单了，维护原数列和排序后的数列，修改时在排序后的数列找到最后一个与之相同的进行修改即可。都是 $+1$ 操作，所以结果依然有序。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=200007,MOD=998244353;
ll T,n,m,op,x,a[N],b[N],c[N],d[N],ans;
ll qpow(ll x,ll k){
	ll sum=1;
	while(k){
		if (k&1) (sum*=x)%=MOD;
		(x*=x)%=MOD;k>>=1;
	}
	return sum;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;ans=1;
		for (int i=1;i<=n;++i){cin>>a[i];c[i]=a[i];}
		for (int i=1;i<=n;++i){cin>>b[i];d[i]=b[i];}
		sort(c+1,c+1+n);sort(d+1,d+1+n);
		for (int i=1;i<=n;++i) (ans*=min(c[i],d[i]))%=MOD;
		cout<<ans;
		while(m--){
			cin>>op>>x;
			if (op==1){
				ll k=upper_bound(c+1,c+1+n,(a[x]++))-c-1;
				(ans*=qpow(min(c[k],d[k]),MOD-2))%=MOD;++c[k];(ans*=min(c[k],d[k]))%=MOD;
			}
			else{
				ll k=upper_bound(d+1,d+1+n,(b[x]++))-d-1;
				(ans*=qpow(min(c[k],d[k]),MOD-2))%=MOD;++d[k];(ans*=min(c[k],d[k]))%=MOD;
			}
			cout<<' '<<ans;
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：lgx57 (赞：0)

有史以来最水的 D。

首先考虑不操作时怎样能使 $P$ 最大，很明显是当 $a$ 和 $b$ 都升序排序的时候，由于 $b$ 可以任意顺序排列，所以相当于可以任意匹配 $a_i$ 和 $b_j$。

然后考虑修改后的情况。由于 $op=1$ 与 $op=2$ 的情况类似，所以下文只考虑 $op=1$ 时的情况。

我们设 $num=a_x$，那么容易发现修改的一定是最靠后的数（因为这样对应的 $b_i$）比较大。于是二分出 $num$ 最靠后的位置，设这个位置为 $Ans$，然后在模意义下除以 $\min(a_{Ans},b_{Ans})$，再乘上 $\min(a_{Ans}+1,b_{Ans})$，最后不要忘记 $a_{Ans} \gets a_{Ans}+1$。

代码很简单，这里不给了。注意实现二分时 $Ans$ 的初始值为 $n$。

---

