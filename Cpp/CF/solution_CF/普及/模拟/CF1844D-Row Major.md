# Row Major

## 题目描述

The row-major order of an $ r \times c $ grid of characters $ A $ is the string obtained by concatenating all the rows, i.e. $ $$$ A_{11}A_{12} \dots A_{1c}A_{21}A_{22} \dots A_{2c} \dots A_{r1}A_{r2} \dots A_{rc}.  $ $ </p><p>A grid of characters  $ A $  is <span class="tex-font-style-it">bad</span> if there are some two adjacent cells (cells sharing an edge) with the same character.</p><p>You are given a positive integer  $ n $ . Consider all strings  $ s $  consisting of only lowercase Latin letters such that they are <span class="tex-font-style-bf">not</span> the row-major order of <span class="tex-font-style-bf">any</span> bad grid. Find any string with the minimum number of distinct characters among all such strings of length  $ n$$$.

It can be proven that at least one such string exists under the constraints of the problem.

## 说明/提示

In the first test case, there are $ 3 $ ways $ s $ can be the row-major order of a grid, and they are all not bad:

tththathatat It can be proven that $ 3 $ distinct characters is the minimum possible.In the second test case, there are $ 2 $ ways $ s $ can be the row-major order of a grid, and they are both not bad:

iiss It can be proven that $ 2 $ distinct characters is the minimum possible.In the third test case, there is only $ 1 $ way $ s $ can be the row-major order of a grid, and it is not bad.

In the fourth test case, there are $ 4 $ ways $ s $ can be the row-major order of a grid, and they are all not bad:

ttotomtomatoomaatomtoato It can be proven that $ 4 $ distinct characters is the minimum possible. Note that, for example, the string "orange" is not an acceptable output because it has $ 6 > 4 $ distinct characters, and the string "banana" is not an acceptable output because it is the row-major order of the following bad grid: banana

## 样例 #1

### 输入

```
4
4
2
1
6```

### 输出

```
that
is
a
tomato```

# 题解

## 作者：蒟蒻君HJT (赞：9)

翻译一下题意，即对任意 $i,j\in N_+$，若 $j-i\mid n$，则 $s_i \neq s_j$。

先特判 $n=1,2$；

然后必要性探路。设 $d$ 是最小的不是 $n$ 的约数的正整数，则 $s$ 中不同字母的个数不可能少于 $d$，且 $d<n$。

原因：由于 $1,2,\cdots d-1$ 均为 $n$ 的约数，所以任取 $i,j\in[1,d]$ 且 $i\neq j$，均满足 $s_i\neq s_j$，即 $s$ 的前 $d$ 个字符各不相同，至少涉及 $d$ 个不同字母。

另一方面，$d$ 个不同字母一定可以组成一个合法的 $s$。可以令 $s_i$ 为第 $(i\bmod d)+1$ 的字母，则当 $i< j,s_i=s_j$ 时，必有 $j-i=kd,k\in N_+$，而 $d\nmid n$，故 $kd\nmid n$，满足题意。

时间复杂度 $\mathcal{O}(n)$。

---

## 作者：细数繁星 (赞：4)

> 感谢 @Zimo_666 同学给我提供的思路。

这篇题解应该很通俗了，题解区里的题解我看了半晌才看懂。

有一说一，这道题目很有意思！

---

矩阵 $A$ 可以被划分成 $r\times c$，那么可以确定的是，在同一列上的它们的下标差肯定是 $r$ 或者 $c$，所以说就可以将题面简化成：

构造一个串 $s$，使得若 $(j-i)\mid n$，$s_i\neq s_j$。

既然要求我们做到用最少的字符串，那就是说我们要尽可能的把字符串的周期压缩到最小，因此我们需要一个数 $p$，使得 $p\nmid n$，我们直接将 $p$ 作为周期即可，在视觉上来看，整个矩阵就像是错开来了一样。

好像官方题解的代码也没这么少，直接上代码：

```cpp
// Problem: Row Major
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1844D
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Coding by 2044_space_elevator

#include <bits/stdc++.h>
#define rty printf("Yes\n");
#define RTY printf("YES\n");
#define rtn printf("No\n");
#define RTN printf("NO\n");
#define rep(v,b,e) for(int v=b;v<=e;v++)
#define repq(v,b,e) for(int v=b;v<e;v++)
#define rrep(v,e,b) for(int v=b;v>=e;v--)
#define rrepq(v,e,b) for(int v=b;v>e;v--)
#define stg string
using namespace std;

typedef long long ll;
typedef unsigned long long ull;


void solve() {
	int n;
	cin >> n;
	int minD = 1;
	for (; !(n % minD); minD++);
	rep(i, 1, n) {
		cout << char((i % minD) + 98);
	} 
	cout << endl;
}


int main() {
	int t; cin >> t; while (t--) solve();
	return 0;
}

```

---

## 作者：aeiouaoeiu (赞：3)

考虑暴力处理。

设答案字符串为 $s$ ，则必然有 $s_i\neq s_{i+1}$，这个不等关系包括了所有同一行字符的不等关系，则我们现在只需要考虑所有不同行的不等关系即可，易知这类不等关系有 $\mathcal{O}(nd(n))$ 对，其中 $d(x)$ 表示 $x$ 的因数个数。

求出这类不等关系后，我们可以对于 $s$ 的每个位置开一个数组记录其不能选哪些字母，对于第 $i$ 个位置，贪心地选取最前面能选的字母，然后将大于 $i$ 且与 $i$ 有不等关系的位置打上不能选 $s_i$ 的标记，不断重复即可，时间复杂度是 $\mathcal{O}(nd(n)+Vn)$ 的，其中 $V=26$。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef long double db;
const int maxn=1000007;
const ll inf=1300000007ll,p=998244353;
ll n,fac[maxn],inv[maxn],cnt;
bool vis[maxn<<1][26];
ll ans[maxn],tar;
int main(void){
	ios::sync_with_stdio(false);
	cin.tie(0);
	ll T=1;
	cin>>T;
	for(int tcs=1;tcs<=T;tcs++){
		cin>>n; cnt=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<26;j++) vis[i][j]=0;
		}
		for(int i=2;i*i<=n;i++){
			if(n%i==0) fac[++cnt]=i,inv[cnt]=n/i,fac[++cnt]=n/i,inv[cnt]=i;
		}
		for(int i=1;i<=n;i++){
			for(int j=0;j<26;j++){
				if(!vis[i][j]){
					tar=j;
					break;
				}
			}
			ans[i]=tar,vis[i+1][tar]=1;
			for(int j=1;j<=cnt;j++) vis[i+fac[j]][tar]=1;
		}
		for(int i=1;i<=n;i++) cout<<(char)(ans[i]+'a');
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：_adil_ (赞：2)

首先我们观察到，任意一个 $f(A)$ 中的元素位置 $x$，它和位于 $x\pm1  ,x\pm r$ 的元素不能相同（当然这些位置得在边界内）。又由于 $r,c$ 可取任意 $n$ 的约数，我们就得出一种 $O(n^2)$ 的做法：遇到没填的位置时使用一种新的字符向后枚举，跳过所有 $n$ 的约数，在每一个能放的位置贪心地放，直到放满为止。这满足了最小字符种类的数量，但是每次放置都要循环 $n$ 次贪一轮，会超时。


进一步观察，定义 $c$ 为最小不能整除 $n$ 的数，可以发现以下结论：

- 填满时最少需要 $c$ 种不同字符，并且每 $c$ 位为一段循环出现，每段内字符都不相同。

这是因为，对于最前面的 $c$ 个位置，根据定义，除 $c$ 外所有数都是 $n$ 的约数，是不能放同样数的。而对于后面每个 $kc+i$ 都会被 $(k-1)c+i$ 的数贪心地选到，这样我们就可以通过 $i\%c$ 来高效地确定每个位置填什么了。时间复杂度 $O(n)$。

```
#include<bits/stdc++.h>
#define N 1000009
#define INF 0x3f3f3f3f
#define mod 998244353
using namespace std;
typedef long long ll;
typedef long double ldb;
typedef pair<int,int> pii;
ll n,k,t,mx;
char a[N];
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin>>t;
  for(int j=0;j<t;j++){
    cin>>n;
    int c=1;
    while(n%c==0)c++;
    for(int i=0;i<n;i++)a[i]='a'+(i%c);
    for(int i=0;i<n;i++)cout<<a[i];cout<<endl;
  }
  return 0;
}
```


---

## 作者：linan04195 (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1844D)
---
## 思路
待我们读完这难懂的题，我们可以得出一些思路：

1. 对于 $n$ 的因数 $x$，$s_i$ 不等于 $s_{i \pm x}$。
2. 输出的字母 $s_i$ 就是第 $i \bmod x$ 个字母。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int t;
int n; 

void slv(){
	cin>>n;
	
	int x=1;
	while(n%x==0) x++;
	
	for(int i=0;i<n;i++) cout<<char((i%x)+'a');
	
	puts("\n");
}

int main(){
	
	cin>>t;
	while(t--) slv();
	
	return 0;
}

```

---

## 作者：Zimo_666 (赞：0)

## D. Row Major

我们考虑对于 $n$ 的因数 $d$，显然对于距离为 $d$ 的两个字母，不能相同。因而我们找到最小的不是 $n$ 的因数的数 $x$，然后对于 $a_i$，每次直接填入从 `a` 开始的第 $i \bmod{x}$ 个字母即可。

[Code](https://codeforces.com/contest/1844/submission/223180805)

---

## 作者：andyli (赞：0)

注意到对于 $n$ 的每一个约数 $d$，字符串中距离为 $d$ 的两个字符不能相同。  
故寻找最小的正整数使其不是 $n$ 的约数，记为 $p$，让 $s_i$ 为第 $i \bmod p + 1$ 个英文字母即可。
```cpp
int main() {
    multipleTests([&]() {
        dR(int, n);
        int p = 1;
        while (n % p == 0)
            p++;
        _for (i, n)
            io.putch(i % p + 'a');
        writeln();
    });
    return 0;
}
```

---

