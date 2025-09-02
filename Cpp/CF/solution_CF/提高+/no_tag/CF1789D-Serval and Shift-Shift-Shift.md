# Serval and Shift-Shift-Shift

## 题目描述

Serval has two $ n $ -bit binary integer numbers $ a $ and $ b $ . He wants to share those numbers with Toxel.

Since Toxel likes the number $ b $ more, Serval decides to change $ a $ into $ b $ by some (possibly zero) operations. In an operation, Serval can choose any positive integer $ k $ between $ 1 $ and $ n $ , and change $ a $ into one of the following number:

- $ a\oplus(a\ll k) $
- $ a\oplus(a\gg k) $

In other words, the operation moves every bit of $ a $ left or right by $ k $ positions, where the overflowed bits are removed, and the missing bits are padded with $ 0 $ . The bitwise XOR of the shift result and the original $ a $ is assigned back to $ a $ .

Serval does not have much time. He wants to perform no more than $ n $ operations to change $ a $ into $ b $ . Please help him to find out an operation sequence, or determine that it is impossible to change $ a $ into $ b $ in at most $ n $ operations. You do not need to minimize the number of operations.

In this problem, $ x\oplus y $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) of $ x $ and $ y $ . $ a\ll k $ and $ a\gg k $ denote the [logical left shift](https://en.wikipedia.org/wiki/Logical_shift) and [logical right shift](https://en.wikipedia.org/wiki/Logical_shift).

## 说明/提示

In the first test case:

The first operation changes $ a $ into $ 00111\oplus\sout{001}11\underline{000}=11111 $ .

The second operation changes $ a $ into $ 11111\oplus\underline{00}111\sout{11}=11000 $ .

The bits with strikethroughs are overflowed bits that are removed. The bits with underline are padded bits.

In the second test case, $ a $ is already equal to $ b $ , so no operations are needed.

In the third test case, it can be shown that $ a $ cannot be changed into $ b $ .

## 样例 #1

### 输入

```
3
5
00111
11000
1
1
1
3
001
000```

### 输出

```
2
3 -2
0
-1```

# 题解

## 作者：Tx_Lcy (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1789D)

较为阴间的 $\rm Div2\ D$。

## 思路

先考虑无解的情况，只有两种：

+ $a$ 都是 $0$，$b$ 不是都是 $0$。

+ $a$ 不是都是 $0$，$b$ 都是 $0$。

发现 $a$ 在执行操作的时候会改变自身，这个比较麻烦，我们考虑能不能在操作的时候使一个前缀 $1...i$ 不改变。

这显然是可以的，我们只需要让它们都异或 $0$ 就可以了。

于是，我们先找到原串的第一个 $1$，那么我们只要每次右移的时候把这个 $1$ 移到 $i$ 之后就可以保持前缀不变。

设 $a$ 中第一个 $1$ 的位置为 $j$。

设 $b$ 中第一个 $1$ 的位置为 $k$。

当 $j \le k$ 时，我们从 $j+1$ 开始往右扫到 $n$，如果当前 $s_i \neq t_i$，那么直接把第一个 $1$ 拉到这个位置，然后异或一下，$s_i$ 就会与 $t_i$ 相等，不难发现此时的操作次数最多为 $n-j$。

发现此时只可能存在 $s_j \neq t_j$，且此时 $s_j=1,t_j=0$。现在我们需要把 $s_j$ 这个 $1$ 往左推出去，不难发现我们可以利用最后一个 $1$ 实现，此时等价于一个后缀不变，直接把那个 $1$ 往左拉到 $j$ 即可，此时操作次数最多为 $j$。


当 $j>k$ 时，我们先把 $s_k$ 设为 $1$，然后套用 $j \le k$ 的解法即可，不难发现此时操作次数最多为 $n-k+1$。

至此，这道题就被解决了，代码有一些细节。

时间复杂度 $\mathcal O(n^2)$。

## 代码

[Link](https://codeforces.com/contest/1789/submission/194968613)


---

## 作者：Exp10re (赞：3)

神仙构造题。

## 解题思路

记 $p$ 为 $a$ 中最靠左的 $1$ 的位置，$q$ 为 $b$ 中最靠左的 $1$ 的位置。

显而易见的，当我们仅使用右移并异或操作时，如果移动了 $k$ 位（$k$ 至少为 $1$），那么 $a_1,a_2,\cdots,a_{p+k-1}$ 的数值一定不変，并且第 $p+k$ 位必定取反。

考虑 $p=q$ 的情况，此时我们顺序枚举 $[p+1,n]$ 范围内的每一个 $i$，然后判断此时 $a_i$ 是否与 $b_i$ 相等，如果不是，进行一次右移 $i-p$ 位并异或的操作。那么在枚举结束后，一定有 $a=b$。

为什么以上操作是正确的？

当我们枚举到第 $i$ 位时，一定保证 $a_1,a_2,\cdots,a_{i-1}$ 与 $b_1,b_2,\cdots,b_{i-1}$ 全等。而进行一次右移 $i-p$ 位并异或的操作之后 $a_1,a_2,\cdots,a_{i-1}$ 的数值一定不変，并且第 $i$ 位必定取反，那么只需要顺次操作就一定能在 $n-p$ 次操作之内做到 $a=b$。

如果 $p \gt q$，那么只需要一次左移 $p-q$ 位并异或的操作，使得 $a$ 中最靠左的 $1$ 的位置从 $p$ 左移到 $q$，其余操作同上，操作次数最大为 $n-p+1$。

如果 $p \lt q$，考虑在 $p$ 不变的情况下顺序枚举 $[p+1,n]$ 范围内的每一个 $i$，使其能保证 $a_{p+1},a_{p+2},\cdots,a_n$ 与 $b_{p+1},b_{p+2},\cdots,b_n$ 全等，然后找到 $a$ 中最靠**右**的 $1$ 的位置，记为 $c$ ，然后**逆**序枚举 $[1,p]$ 范围内的每个 $i$，然后判断此时 $a_i$ 是否与 $b_i$ 相等，如果不是，进行一次**左**移 $c-i$ 位并异或的操作，以保证 $a_1,a_2,\cdots,a_p$ 与 $b_1,b_2,\cdots,b_p$ 全等，此时进行了最多 $n$ 次操作保证了 $a=b$。

原理同上，不再赘述。

## 代码

没加注释，但是上文个人认为已经足够清晰了，故不加。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=20010;
int a[MAXN],b[MAXN],n,ans[MAXN],v;
char sa[MAXN],sb[MAXN];
void lstxor(int dist)
{
	if(dist==0)
	{
		return;
	}
	ans[++v]=dist;
	int i;
	if(dist<0)
	{
		dist=-dist;
		for(i=n-dist;i>=1;i--)
		{
			a[i+dist]^=a[i];
		}
	}
	else
	{
		for(i=1+dist;i<=n;i++)
		{
			a[i-dist]^=a[i];
		}
	}
	return;
}
void work()
{
	v=0;
	int i,j,cnt;
	scanf("%d\n%s\n%s",&n,sa+1,sb+1);
	int flaga=n+1,flagb=n+1,flagc;
	for(i=n;i>=1;i--)
	{
		a[i]=sa[i]-'0';
		b[i]=sb[i]-'0';
		if(a[i]==1)
		{
			flaga=i;
		}
		if(b[i]==1)
		{
			flagb=i;
		}
	}
	if(flagb==n+1||flaga==n+1)
	{
		if(flaga==n+1&&flagb==n+1)
		{
			printf("0\n");
		}
		else
		{
			printf("-1\n");
		}
		return;
	}
	if(flaga>flagb)
	{
		lstxor(flaga-flagb);
		flaga=flagb;
	}
	for(i=flaga+1;i<=n;i++)
	{
		if(b[i]!=a[i])
		{
			lstxor(flaga-i);
		}
	}
	for(i=n;i>=1;i--)
	{
		if(a[i]==1)
		{
			break;
		}
	}
	flagc=i;
	if(flaga<flagb)
	{
		for(i=flaga;i>=1;i--)
		{
			if(b[i]!=a[i])
			{
				lstxor(flagc-i);
			}
		}
	}
	printf("%d\n",v);
	for(i=1;i<=v;i++)
	{
		if(ans[i]!=0)
		{
			printf("%d ",ans[i]);
		}
	}
	if(v>0)
	{
		printf("\n");
	}
	return;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：2)

首先考虑一些无解的情况：

* $a$ 全 $0$，$b$ 非全 $0$。
* $b$ 全 $0$，$a$ 非全 $0$。

有考虑到两者都是全 $0$ 的时候不需要操作，所以接下来只需要考虑两者都不是全 $0$ 的情况。

由于最多操作 $n$ 次，所以设法使每次操作都能固定一位。

设 $l_a$ 表示 $a$ 中最高位 $1$ 的位置，$l_b$ 同理，若 $l_a<l_b$，则先令 $k=l_b-l_a$ 左移一次，保证 $a_{l_b}=1$。接下来考虑所有比 $l_b$ 低的位 $j$，如果 $a_j\ne b_j$，可以通过异或右移 $l_b-j$ 位使得 $a_j=b_j$。接下来再考虑 $a_{l_b}\ne b_{l_b}$ 的情况，$l_b$ 及比 $l_b$ 高的位一样可以通过用最低位 $1$ 异或当前位来实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Wilson_Inversion {
int T, n, cnt, a[2010], cz[2010];
char s[2][2010], t[2010];
void work(int x) {
	cz[++cnt] = x;
	memcpy(t, s[0], sizeof(t));
	for (int i = 1; i <= n; ++i) {
		if (i + x >= 1 && i + x <= n) s[0][i] ^= t[i + x];
	}
}
void solve() {
	scanf("%d", &n);
	cnt = 0;
	scanf("%s%s", s[0] + 1, s[1] + 1);
	int cnt1 = 0, cnt2 = 0, ls1 = 0, ls2 = 0, rs2 = 0;
	for (int i = 1; i <= n; ++i) {
		if (s[0][i] == '1') ++cnt1, ((!ls1) ? (ls1 = i) : 0);
		if (s[1][i] == '1') ++cnt2, rs2 = i, ((!ls2) ? (ls2 = i) : 0);
	}
	if ((!cnt1) && (!cnt2)) {
		puts("0");
		return;
	}
	if ((!cnt1) || (!cnt2)) {
		puts("-1");
		return;
	}
	for (int i = 1; i <= n; ++i) s[0][i] -= 48, s[1][i] -= 48;
	for (int i = min(ls1, ls2); i <= n; ++i) {
		if (i == min(ls1, ls2)) {
			if (ls1 > ls2) {
				work(ls1 - ls2);
			}
		} else {
			if (s[0][i] != s[1][i]) work(min(ls1, ls2) - i);
		}
	}
	if (ls1 < ls2) {
		for (int i = ls1; i; --i) {
			if (s[0][i] != s[1][i]) {
				work(rs2 - i);
			}
		}
	}
	printf("%d\n", cnt);
	if (cnt) {
		for (int i = 1; i <= cnt; ++i) printf("%d ", cz[i]);
		puts("");
	}
}
void main() {
	scanf("%d", &T);
	while (T--) solve();
}
}  // namespace Wilson_Inversion
#undef int
int main() {
	Wilson_Inversion::main();
	return 0;
}
```


---

## 作者：happybob (赞：0)

有趣的构造题。

考虑到两个字符串最多有 $n$ 位不同，而我们最多只能操作一次，不难想到每次操作修改一位，且不影响之前已经操作过的位。

一个数异或 $0$ 不变，所以可以想到不影响之前操作的位等价于将那些数异或上 $0$。

接着考虑左移和右移如何构造出 $0$？可以发现左移时，后缀的一段自动补 $0$。右移时，前缀一段自动补 $0$。我们找到两个字符串最靠左的 $1$，设为 $x$ 和 $y$。

如果 $x=y$，我们从 $x+1$ 扫到 $n$，只要有不同的就通过右移的方式把 $x$ 点的 $1$ 挪过去，前缀不变。

如果 $x>y$，先左移一次，让 $s_x=1$，然后按照 $x=y$ 做。

如果 $x<y$，先按照 $x=y$ 做，最后只有 $s_x$ 和 $s_y$ 不同。用 $s$ 中最靠右的 $1$ 一直左移直到把这个 $x$ 点的 $1$ 推出去即可。

当两个字符串一个全 $0$ 另一个非全 $0$ 时无解。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e3 + 5;

int t, n, x, y;
string a, b;
vector<int> ans;

void op(string& s, int k)
{
    if (!k) return;
    ans.emplace_back(k);
    string g;
    for (int i = 0; i <= n; i++) g += "0";
    for (int i = 1; i <= n; i++)
    {
        if (i - k >= 1 and i - k <= n) g[i - k] = s[i];
    }
    for (int i = 1; i <= n; i++)
    {
        if (g[i] - '0')
        {
            s[i] = ((s[i] - '0') xor 1) + '0';
        }
    }
}

void pre()
{
    op(a, x - y);
    x = y;
}

void solve()
{
   for (int i = x + 1; i <= n; i++)
   {
       if (a[i] != b[i])
       {
            op(a, -i + x);
       }
   }
}

void solve2()
{
    int lpos = n;
    for (int i = n; i >= 1; i--)
    {
        if (a[i] - '0')
        {
            lpos = i;
            break;
        }
    }
    for (int i = x; i >= 1; i--)
    {
        if (a[i] != b[i])
        {
            op(a, lpos - i);   
        }
    }
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--)
    {
        cin >> n;
        cin >> a >> b;
        a = " " + a, b = " " + b;
        ans.clear();
        x = 0, y = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!x and a[i] == '1') x = i;
            if (!y and b[i] == '1') y = i;
        }
        if (x and !y) cout << "-1\n";
        else if (!x and y) cout << "-1\n";
        else if (a == b) cout << "0\n";
        else
        {
            if (x > y) pre();
            solve();
            if (x < y) solve2();
            cout << ans.size() << "\n";
            for (auto &i : ans) cout << i << " ";
            cout << "\n";
        }
    }
    return 0;
}
```


---

## 作者：eastcloud (赞：0)

[更好的阅读体验](https://www.cnblogs.com/eastcloud/p/17178474.html)

## 题目分析

首先，看到题目中的左移右移之后再异或，我们自然可以想到在移动的过程中字符串的一段前缀和后缀不会改变，考虑通过这个性质逐位还原。

因为异或 0 不会改变原本的值，所以我们可以找到整个字符串的第一个 1，把这个位置即为 $i$，用它右移异或其他与另一字符串不同值的位置，因为我们每次异或的副作用只作用在那一位之后，所以经过这个操作可以保证第 $i+1$ 到第 $n$ 位被全部还原。

那前面部分的不同值呢，将其拉到前面异或会导致其他因素改变，如果拉最后一个则有可能只有这一个 1 而自己也需要改变，注意到如果小于 $i$ 的所有位置都为 0 就好操作的多，只需复制前面的操作，改变一下方向把这个 1 往前推即可，那么我们如何将所有情况转化为这种情况呢？

其实很简单，记一开始的两个字符串第一个 1 的位置分别为 $j$ 和 $k$，$j\leq k$ 则无需操作，否则把一个后面的 1 拉过来与这位异或一下即可，可以发现情况一最多操作 $n$ 次，情况二最多 $n-k+1$ 次。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector> 
#define ll long long
using namespace std;
bool jud(int n,string s){
	for(int i=0;i<n;i++) if(s[i]!='0') return false;
	return true;
}
int find(int n,string s){
	for(int i=0;i<n;i++) if(s[i]=='1') return i;
}
char change(char x){
	return x=='0'?'1':'0';
}
string ope(int n,string s,int k){
	string tmp=s;
	for(int i=0;i<n;i++){
		int ti=i+k;
		if(ti<0 || ti>=n) continue;
		if(tmp[ti]=='1') s[i]=change(s[i]); 
	}
	return s;
}
int opt[1000001],tot=0;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;tot=0;
		string a,b;
		cin>>n>>a>>b;
		if((jud(n,a) && !jud(n,b))||(!jud(n,a) && jud(n,b))){
			cout<<-1<<endl;
			continue;
		}
		if(a==b){cout<<0<<endl;continue;}
		int j=find(n,a),k=find(n,b);
		if(j>k) {opt[++tot]=j-k;a=ope(n,a,j-k);j=k;}
		for(int i=j+1;i<n;i++) if(a[i]!=b[i]){opt[++tot]=j-i;a=ope(n,a,j-i);}
		int pl=0;
		for(int i=n;i>0;i--) if(a[i]=='1') {pl=i;break;}
		for(int i=j;i>=0;i--)if(a[i]!=b[i]){opt[++tot]=pl-i;a=ope(n,a,pl-i);}
		cout<<tot<<endl;
		for(int i=1;i<=tot;i++) cout<<opt[i]<<' ';
		cout<<endl;
	}
}
```


---

