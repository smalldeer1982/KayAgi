# Fibonacci Strings

## 题目描述

In all schools in Buryatia, in the $ 1 $ class, everyone is told the theory of Fibonacci strings.

"A block is a subsegment of a string where all the letters are the same and are bounded on the left and right by the ends of the string or by letters other than the letters in the block. A string is called a Fibonacci string if, when it is divided into blocks, their lengths in the order they appear in the string form the Fibonacci sequence ( $ f_0 = f_1 = 1 $ , $ f_i = f_{i-2} + f_{i-1} $ ), starting from the zeroth member of this sequence. A string is called semi-Fibonacci if it possible to reorder its letters to get a Fibonacci string."

Burenka decided to enter the Buryat State University, but at the entrance exam she was given a difficult task. She was given a string consisting of the letters of the Buryat alphabet (which contains exactly $ k $ letters), and was asked if the given string is semi-Fibonacci. The string can be very long, so instead of the string, she was given the number of appearances of each letter ( $ c_i $ for the $ i $ -th letter) in that string. Unfortunately, Burenka no longer remembers the theory of Fibonacci strings, so without your help she will not pass the exam.

## 说明/提示

In the first test case, a one-character string is semi-Fibonacci, being itself a Fibonacci string.

In the second test case, a string of two different characters is Fibonacci.

In the third test case, the string "abb" (let the first of the alphabet letter be a, the second letter b) is not a semi-Fibonacci string, since no permutation of its letters ("abb", "bab", and "bba") is a Fibonacci string.

In the fourth test case, two permutations of the letters of the string "abaccac" (the first letter is a, the second letter is b, the third letter is c) are Fibonacci strings — "abaaccc" and "cbccaaa".

## 样例 #1

### 输入

```
6
1
1
2
1 1
2
1 2
3
3 1 3
2
7 5
6
26 8 3 4 13 34```

### 输出

```
YES
YES
NO
YES
NO
YES```

# 题解

## 作者：happy_dengziyue (赞：8)

### 1 视频题解

![](bilibili:BV1HB4y1L7qy)

### 2 思路

设 $s_i=\sum_{j=0}^if_j$。

首先我们要找到一个 $pos$ 使得 $s_{pos}=\sum c_i$。找不到就说明直接无解。

否则，从大到小地枚举块。

枚举到一个块，就将暂时剩下最多的字符放进去。如果有 $2$ 种这样的字符，就放不是刚刚放过的任意一种；否则，如果这种字符刚刚放过了，此题就无解。同时，如果这种字符放不满这个块，此题就无解。

如何证明这个贪心策略呢？

设枚举到第 $f_i$ 的块。

如果有且仅有 $1$ 种个数不小于 $f_i$ 的字符：

+ 如果它放给了 $f_{i+1}$，无解；

+ 否则放给 $f_i$。

如果存在 $2$ 种或更多这样的字符：

+ 如果它们个数相等，明显可以放置任意一种；

+ 如果它们个数不相等，放较大的那种。

    因为，设较大那种还有 $x$ 个字符，很明显 $x\ge f_i+1$。如果它没能被放置在 $f_i$，就算 $f_{i-1},f_{i-3},...,f_1\operatorname{or}f_2$ 都被放一遍，都不够。

以上就是贪心过程的证明，具体实现看代码。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int t;
int n;
long long a[102];
long long sum;
long long f[100002];
long long s[1000002];
int fi=2;
priority_queue<long long>q;
int pos;
bool ans;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1718B_1.in","r",stdin);
	freopen("CF1718B_1.out","w",stdout);
	#endif
	f[0]=f[1]=1;
	s[0]=1;
	s[1]=2;
	for(;f[fi-1]<=2000000000;++fi){
		f[fi]=f[fi-1]+f[fi-2];
		s[fi]=s[fi-1]+f[fi];
	}
	--fi;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		sum=0;
		for(int i=1;i<=n;++i){
			scanf("%lld",a+i);
			sum+=a[i];
		}
		pos=lower_bound(s,s+fi+1,sum)-s;
		if(s[pos]!=sum){
			printf("NO\n");
			continue;
		}
		while(!q.empty())q.pop();
		for(int i=1;i<=n;++i)q.push(a[i]);
		ans=true;
		while(!q.empty()){
			long long u=q.top();
			q.pop();
			if(f[pos]>u){
				ans=false;
				break;
			}
			u-=f[pos];
			if(u){
				if(q.empty()){
					ans=false;
					break;
				}
				if(q.top()<u){
					ans=false;
					break;
				}
				q.push(u);
			}
			--pos;
		}
		if(!ans)printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/84159760)

By **dengziyue**

---

## 作者：YBaggio (赞：6)

## 题意
现在我们有 $k$ 种字符，第 $i$ 种字符有 $a_i$ 个，现在我们要将这 $\sum^n_{i=1}a_i$ 个字符按照某种顺序排列，使其符合以下形式，就称它是合法的：

$ \verb 1个相同的-1个相同的-2个相同的-3个相同的-5个相同的-8个相同的 \dots$

很显然这是个菲波那切数列($ \verb 1-1-2-3-5-8- \dots$ )
   
例如： $ \verb abaabbbcccccaaaaaaaa $ 就是合法的，但是 $\verb aabbcccddddd $ 就是不合法的。现在给出你每种字符的数量，让你判断是否可以组成合法的串。

## 思路
很容易看出一个串合法的话，它所有字符的数量肯定是斐波那契数列的前缀和  (1,2,4,7,12)，如果它所有字符的数量都不符合的话，这个串显然是不合法的。

既然一个串的字符数量已经合法了的话，我们就开始考虑如何去分配了。

先看样例的这一组:
```
2
7 5
```
我们可以判断它的数量是合法的，接下来我们把 5 它和斐波那契数列对照起来看:
```
7 5
1 1 2 3 5
```
**这时候我们有两种选择**：
1. **先**用数量少的字符去放小的空
2. **先**用数量多的字符去放大的空

如果我们选择第一种的话:数量为 5 的字符会放满 1,1,2 后留下 1,接下来就无法放了。

如果我们选择第二种的话:数量为 7 的字符会放满 5 后留下 2，接下来因为 5 比 2 大所以用 5 放满 2,3 最后用 2 放满 1,1。

可以发现第二种更优。

#### 灵魂拷问：为什么???
因为斐波那契额数列是升序的，小的放小的后只会越来越小，这剩下的字符就只能放在小的空，但是小的空已经被用了很多了，所以就很难处理了；但是第二种方案虽然也会变得更小，但是小的空没有被填满，所以会更加优秀。

________________
明白了这个道理后我们就可以有一个贪心的做法了，每次选择 $a$ 与 斐波那契额数组中的最大值进行比较，如果 $a$ 的最大值比斐波那契中最大值的大的话，就讲 $a$ 中的最大值减去斐波那契中的，将斐波那契中的最大值删掉（被填满了）。但如果 $a$ 中的最大值小于斐波那契中的最大值，也就是说这个空没有字符能填，即这个串不合法。

最后在找最大的时候可以用堆优化，具体看代码（有注释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=110;
ll t,n,a[maxn];
map<ll,ll>mp;//如果mp[x]==true的话就说明所有字符的和为x的串数量合法
struct E{
	ll val,id;
	bool operator==(const E&x)const{
		return id==x.id;
	}bool operator<(const E&x)const{
		return val<x.val;
	}//因为用了STL所以要重载运算符
};
struct Heap{//因为STL的堆不支持删除，所以就加了点料
	priority_queue<E>q;
	priority_queue<E>d;
	void push(E x){q.push(x);}
	void del(E x){d.push(x);}
	E top(){
		while(!q.empty()&&!d.empty()&&q.top()==d.top()){q.pop(),d.pop();}
		if(q.empty())return E{-1,-1};
		return q.top();
	}
	void init(){
		while(!q.empty())q.pop();
		while(!d.empty())d.pop();
		return; 
	}
}heap,fib_heap;
void init(ll M){//初始化
	heap.init();fib_heap.init();//堆清空
	mp[1]=1;fib_heap.push({1,1});
	ll fir=1,sec=1,cnt=1,sum=2;
	while(sum<=M){
		fib_heap.push({sec,++cnt});
		ll tmp=sec;sec+=fir;
		fir=tmp;mp[sum]=cnt;
		sum+=sec;
	}
	return;
}
int main(){
	init(1e11);
    scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		ll sum=0;
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]),sum+=a[i];
		if(!mp[sum]){printf("NO\n");continue;}//数量不合法
		init(sum);
		for(int i=1;i<=n;i++)heap.push(E{a[i],i});
		int last=0;bool flag=0;
		while(1){
			E x=heap.top(),y=fib_heap.top(),tmp=E{0,0};
			if(x.id==-1&&y.id==-1)break;
			if(x.id==last){heap.del(x);tmp=x;x=heap.top();}//不能两次选同一个字符
			if(x.val==y.val)heap.del(x),fib_heap.del(y),last=x.id;//相等就相当于都删去
			else if(x.val<y.val){flag=1;break;}//不合法
			else if(x.val>y.val)fib_heap.del(y),heap.del(x),heap.push(E{x.val-y.val,x.id}),last=x.id;
			if(tmp.id>0)heap.push(tmp);
		}
		if(flag)printf("NO\n");
		else printf("YES\n");
	}//
	return 0;
}
```

---

## 作者：Alex_Wei (赞：5)

> [CF1718B Fibonacci Strings](https://www.luogu.com.cn/problem/CF1718B)

考虑 $c_i$ 表示为若干斐波那契数的和，根据题意，这些斐波那契数不能相邻。

设 $s$ 为 $f$ 的前缀和，则考虑从使得 $s_p = \sum c_i$ 的 $p$ 开始，依次尝试将某个 $c_i$ 减去 $f_p, f_{p - 1}, \cdots, f_0$。若 $p$ 不存在显然无解。

不妨设 $c_1 \leq c_2 \leq \cdots \leq c_k$ 且当前需要将某个数减去 $f_p$。首先若 $c_k < f_p$ 显然无解，否则由于 $f_{p - 1} + f_{p - 3} + \cdots \leq f_p$（经典结论，归纳可证），所以若 $c_k > f_p$ 时，只能选择 $c_k$；当 $c_k = f_p$ 时，我们也只能选择等于 $c_k$ 的值，视为选择 $c_k$。因此只需贪心将 $c_k$ 减去 $f_p$ 即可。

进一步地，由于斐波那契数不能相邻，所以若 $c_k - f_p > c_{k - 1}$，则下一步操作仍然选择当前 $c_k$，不合法；反之可做到不选择当前 $c_k$，合法。因此 $c_k - f_p > c_{k - 1}$ 时同样无解。

若不符合上述所有判断无解的条件，则算法过程给出了一组构造，有解。

时间复杂度 $\mathcal{O}(Tk ^ 2)$ 或 $\mathcal{O}(Tk\log k)$。由于使得 $f_p > \max c_i$ 的 $p$ 的级别为 $\mathcal{O}(\log c_i)$，所以 $k$ 可与 $\mathcal{O}(\log c_i)$ 取较小值。对于本题，$f_{44} > 10 ^ 9$，所以 $k\geq 45$ 时无解。

```cpp
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 105;
int n, p, c[N], f[N];
long long s[N], z;
void solve() {
  cin >> n, p = z = 0;
  for(int i = 1; i <= n; i++) cin >> c[i], z += c[i];
  if(n >= 45) return puts("NO"), void();
  sort(c + 1, c + n + 1);
  while(p < 43 && s[p + 1] <= z) p++;
  while(~p) {
    c[n] -= f[p--];
    if(c[n] < 0 || c[n] > c[n - 1]) return puts("NO"), void();
    for(int i = n; i > 1; i--) if(c[i] < c[i - 1]) swap(c[i], c[i - 1]);
  }
  puts(c[n] ? "NO" : "YES");
}
int main() {
  f[0] = f[1] = s[0] = 1, s[1] = 2;
  for(int i = 2; i < 44; i++) s[i] = s[i - 1] + (f[i] = f[i - 1] + f[i - 2]);
  ios::sync_with_stdio(0);
  int T = 1;
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：D2T1 (赞：3)

## div1B/div2E. Fibonacci Strings

由于斐波那契数列后面的数比前面的数大很多，于是我们大胆猜测，可以从大到小枚举斐波那契数，贪心地选择最大的那个数来“包含”这个斐波那契数！

要注意：因为不能连续两个斐波那契数被同一个数包含，所以我们还要把每个数绑定上一个“编号”，表示他包含的最小的斐波那契数的下标！如果目前最大的数的编号都是目前考虑的斐波那契数的下标 $+1$，则直接输出 `NO` 即可！

证明可以感性理解一下！

> 引理：
$$\begin{cases}fib_0+fib_2+fib_4+...+fib_n=fib_{n+1}\\fib_1+fib_3+fib_5+...+fib_n=fib_{n+1}-1\end{cases}$$

若一个数 $x$ 要包含 $fib_{i-1},fib_i$，那么如果有解，必然有另一个数 $y$ 可以来包含 $fib_{i-1}$！而这个数显然 $\geq fib_{i-1}$。

- 若 $y < x - fib_i$，则 $x > fib_i + fib_{i-1}$。由引理可得 $x > fib_i+fib_{i-2}+fib_{i-4}+...$，所以也是无解！
- 否则，$y$ 在优先队列中必然排在 $x$ 前面，比 $x$ 更先取出！

还有一个要注意的地方：你的代码在如下一组数据中可能会输出 `NO`！

```
1
4
21 1 2 8
```

原因是数列中的 $21$ 在计算中包含了斐波那契数 $21$！而实际上我们并不需要它包含 $21$！于是求出斐波那契数列的前缀和，与 $a$ 数组的和比对一下即可！

```cpp
#define multiple_test_cases
 
const int N = 110;
const ll mx = 1e15;
int n, tot;
ll a[N], fib[N];
 
void init(){
	fib[0] = fib[1] = 1;
	for(int i = 2; i < N; ++ i){
		fib[i] = fib[i-1] + fib[i-2];
		if(fib[i] > mx){
			tot = i;
			return;
		}
	}
}
 
void solve(){
	n = rdi;
	priority_queue<pair<ll, int> > q;
	ll sum1 = 0, sum2 = 0;
	for(int i = 1; i <= n; ++ i){
		a[i] = rdi;
		sum1 += a[i];
		q.push(make_pair(a[i], tot + 2));
	}
	int tmp = 0;
	for(int i = 0; i <= tot; ++ i){
		sum2 += fib[i];
		if(sum2 == sum1){
			tmp = i;
			break;
		} else if(sum2 > sum1){
			puts("NO");
			return;
		}
	}
	if(n == 1){
		if(a[1] == 1){
			puts("YES");
		} else {
			puts("NO");
		}
		return;
	}
	bool flg = false;
	for(int i = tmp; i >= 0; -- i){
		ll x = q.top().first;
		int y = q.top().second;
		if(x < fib[i] && flg){
			puts("NO");
			return;
		}
		if(x >= fib[i]){
			if(y == i + 1){
				puts("NO");
				return;
			}
			q.pop();
			q.push(make_pair(x - fib[i], i));
			flg = 1;
		}
	}
	if(q.top().first == 0){
		puts("YES");
	} else {
		puts("NO");
	}
}
```

---

## 作者：Zeardoe (赞：2)

这题挺有启发意义的，需要利用斐波那契数列的一些性质证明贪心的正确性：
$$ \mathbf{
F_1 + F_2 + F_3 + ... + F_n = F_{n+2} - 1
}$$
这个限制让题目限制很紧。

先找出原数列 $c$ 的字母个数和是斐波那契数列 $F$ 的哪一个前缀和。如果不存在，就输出 NO。否则尝试组成这一个斐波那契数，利用以下贪心策略：

贪心策略：从大到小考虑斐波那契数列的某一项 $F_i$ 被原数列 $c$ 的哪一个字母占领（即构成这一项的是哪一个字母）。对于 $F_i$，找出当前数列 $c$ 中最大的不等于占领了 $F_{i+1}$ 的元素的元素 $c_x$（因为不可以相邻），判断如果 $F_i > c_x$ 则输出 NO，否则让 $c_x$ 占领 $F_i$ 并且前往 $F_{i-1}$。

考虑证明贪心的正确性，也就是为什么总是选择最大的那一个。由上述定理我们首先有个推论：

如果 $c_x > F_i$ 并且未占领 $F_i$ ，那么 $c_x$ 一定最后不会被用完。

为什么呢？考虑从 $F_{i-1}$ 开始往下隔一个取一个数的方案，加起来是 $F_i$，不够用。

那么如果只存在 $ \geq F_i$ 的一个数，那么一定要用掉这个数来占领 $F_i$，不然没有数可以占领 $F_i$。

如果存在两个及以上 $ \geq F_i$ 的数：

- 如果所有数都相等，并且等于 $F_i$，那么由上一种情况知道任意选择一个 $F_i$ 都行。
- 否则一定存在 $> F_i$ 的一个数，由推论知道一定要选择这个数，否则这个数就没法清空了。

时间复杂度：$O(k \log(kc))$，其中 $\log(kc)$ 是斐波那契数列的项数。

---

## 作者：Micnation_AFO (赞：1)

## $\texttt{Discribtion}$
定义一个块，为字符串中的一个子串，且该子串中的所有字母都相等，并且该子串在原字符串中是不可拓展的（即该子串开头左边的字符不与该子串的字母相等，该子串末尾右边的字符也不与该子串的字母相等）。

例如，$\texttt{abbbbc}$ 中，$\texttt{bbbb}$ 就是一个块，而 $\texttt{bbb}$ 不是，因为 $\texttt{bbb}$ 的左边或者右边仍然是 $\texttt{b}$。

现在让你重新对字符串进行排列，能否做到所有块的长度等于斐波那契数列的长度。

例如，$\texttt{abccdddbbbbb}$ 就是合法的，因为第一个块的长度是 $1$，与斐波那契数列的第一项相等，第二个块的长度是 $1$，与斐波那契数列的第二项相等，以此类推。

## $\texttt{Solution}$
首先预处理出斐波那契数列的前缀和，字符串的长度若不等于其中的任何一个元素，则显然是不合法的。

长度合法后，考虑如何分配。

由于斐波那契数列会越来越大，所以分配的时候总是用数量最多的字母去分配斐波那契最大的。否则，这些字母就要分配到其他的块等于其中一个斐波那契数的长度。而题目要求块不能相连，显然长度越大，出现相连的可能性越大，所以要使得长度尽可能小。即数量最大的字母分配到尽可能大的斐波那契数。

所以可以用大根堆维护。注意，题目中有块不能相连的限制，所以要记录一下上一个分配的字母，不能与其相同。

AC 代码：

```cpp
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define int long long
const int N = 10010;

int T;
int a[N];
int Fib[N], sum[N];

signed main() {
    Fib[1] = Fib[2] = 1;
    for (int i = 3; Fib[i - 1] <= 1e9; i++) Fib[i] = Fib[i - 1] + Fib[i - 2];
    for (int i = 1; i <= 45; i++) sum[i] = sum[i - 1] + Fib[i];
    cin >> T;
    while (T--) {
        int Sum = 0, id, n; cin >> n;
        memset(a, 0, sizeof(a));
        for (int i = 1; i <= n; i++) cin >> a[i], Sum += a[i];
        bool flag = false;
        for (int i = 1; i <= 45; i++)
            if (Sum == sum[i]) flag = true, id = i;
        if (!flag) { cout << "NO\n"; continue; }
        priority_queue< pair<int, int> > q;
        for (int i = 1; i <= n; i++) q.push(make_pair(a[i], i));
        flag = false;
        int last = -1;
        while (q.size()) {
            pair<int, int> l = q.top(), r; q.pop();
            if (l.second == last) { 
                if (q.empty()) { flag = true; cout << "NO\n"; break; }
                r = q.top(); q.pop(); q.push(l); l = r; 
            } 
            if (l.first >= Fib[id]) l.first -= Fib[id--], last = l.second;
            else { flag = true; cout << "NO\n"; break; }
            if (l.first != 0) q.push(l);
        }
        if (!flag) cout << "YES\n";
    }
    return 0;
}

```

---

## 作者：ztlh (赞：1)

# Solution

首先，我们可以先做一个初步的判断。

（为符合我的代码，下面内容中 $f_i$ 下标从 $1$ 开始）

易知 $f_i = f_{i+2} - f_{i+1}$

则

$$\sum_{i = 1}^{n} f_i = \sum_{i = 1}^{n} (f_{i + 2} - f_{i - 1}) = f_{n + 2} - f_2 = f_{n + 2} - 1$$

求出所有 $c_i$ 的和 $sum$，观察数据范围，发现 $sum \leq 10^{11}$，又因为 $f_{60} > 10^{11}$，则求出 $f_i$（$1 \leq i \leq 60$），检验是否存在 $f_i$ 使得 $sum = f_i - 1$，不存在则输出 $\verb!NO!$ 即可。

若存在这个 $f_i$，则令 $idx = i - 2$，易知 $sum = \sum_{i = 1}^{idx} f_i$。从大到小遍历 $f_i$ 的前 $idx$ 项，每次贪心选取 $c_j$ 的最大值。同时记录上一次操作的 $c_j$，此次操作不能作用于它。

令当前遍历到的项为 $f_i$。若 $c_{maxid} < f_i$，则输出 $\verb!NO!$，否则将 $c_{maxid}$ 减去 $f_i$，记录 $maxid$。

最后，如果还没输出 $\verb!NO!$，输出 $\verb!NO!$ 即可。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int T;
int k;
ll c[105],sum;
ll f[65];
int main(){
	f[1]=f[2]=1;
	for(int i=3;i<=60;i++)
		f[i]=f[i-1]+f[i-2];
	scanf("%d",&T);
	while(T--){
		sum=0;
		memset(c,0,sizeof(c));
		scanf("%d",&k);
		for(int i=1;i<=k;i++){
			scanf("%lld",&c[i]);
			sum+=c[i];
		}
		int flag=0;
		for(int i=3;i<=60;i++)
			if(sum+1==f[i]){
				flag=i-2;
				break;
			}
		if(!flag){
			printf("NO\n");
			continue;
		}
		int lst=0;
		ll maxn;
		int maxi;
		bool v=1;
		for(int i=flag;i>=1;i--){
			if(lst!=1) maxn=c[1],maxi=1;
			else maxn=c[2],maxi=2;
			for(int j=2;j<=k;j++)
				if(c[j]>maxn&&j!=lst)
					maxn=c[j],maxi=j;
			if(maxn<f[i]) {v=0; break;}
			c[maxi]-=f[i];
			lst=maxi;
		}
		puts(v?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：liuzhongrui (赞：0)

### 前置~~芝士~~知识

#### 斐波那契字符串
斐波那契字符串被定义为当字符串被划分成块时，这些块的长度以斐波那契数列的顺序排列。斐波那契数列的定义如下：

 - $f_0 = f_1 = 1$ 
 - 对于 $i \geq 2$，$f_i = f_{i-1} + f_{i-2}$

因此，前几项斐波那契数列为：
$$f_0 = 1 ,f_1 = 1,f_2 = 2,f_3 = 3,f_4 = 5,f_5 = 8 \cdots$$

基本实现方法为递推，详情[戳这里](https://oi-wiki.org/math/combinatorics/fibonacci/)。

#### 半斐波那契字符串

一个字符串被称为半斐波那契字符串，如果它的字母可以重排列成一个斐波那契字符串。换句话说，我们需要在字符出现次数的基础上，判断是否可以用这些字符组成块，使得这些块的长度符合斐波那契数列的要求。


---



## 思路

首先，我们计算所有字母出现的总次数 $cnt$。接下来查找目标斐波那契数，我们需要查找一个符合 $cnt = f_{k+2} - 1$ 的 $k$ 值，即我们可以用 $k$ 个不同的字符通过斐波那契数列来表示的总字符数量。

如果 $n$（字母的数量）大于等于 $50$，或者找不到合适的 $k$，输出 `NO`。

如果合法，接下来我们尝试将字母组合成块，并不断减去斐波那契数列中的数值，同时用一个记录上一个选择的标记，来保证不连续选择同一个字。

最后如果所有字符的数量都变为 $0$，则输出 `YES`，否则输出 `NO`。

时间复杂度为 $O(n \cdot k)$，空间复杂度为 $O(k)$。

## 代码
代码奉上。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int f[60],a[101];
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	f[0]=f[1]=1;
	for(int i=2; i<=50; i++)f[i]=f[i-1]+f[i-2];
	int T;
	cin>>T;
	while(T--) {
		int cnt=0,n,k=-1;
		bool flag=0;
		cin>>n;
		for(int i=1; i<=n; i++)cin>>a[i],cnt+=a[i];
		for(int i=0; i<50; i++)if(f[i+2]-1==cnt)k=i;
		if(n>=50||k==-1){
			flag=1;
		}
		for(int i=k,m,id=0; ~i; i--) {
			m=0;
			for(int j=1; j<=n; j++)if(j^id)m=(a[j]<a[m])?m:j;
			a[m]-=f[i],id=m;
		}
		for(int i=1; i<=n; i++){
			if(a[i]){
				flag=1;
				break;
			}
		}
		if(flag)cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：ricky_lin (赞：0)

[更好的阅读体验](CF1718.html#cf1718b-fibonacci-strings)

我们首先满足输出 `YES` 的第一个要求显然是 $\sum c_i$ 是 `fibonacci` 序列的前缀和之一。

因为我们需要满足一个数列中的任意数不能删连续的斐波那契数，所以一个数的 `fibonacci` 分解显然是唯一的。

我们考虑一个数的 `fibonacci` 分解显然是斐波那契数列从大到小，能减就减。

对于一堆数的分解我们显然是让当前数列最大的数减去最大的斐波那契数。

---

所以我们从大到小枚举可用的 `fibonacci` 数，然后进行上面的操作即可，对于查找最大数，显然可以使用优先队列。

我们会出现下面两种异常情况：

- 如果说当前数列最大的数**小于**当前的斐波那契数，那么显然就是无解。

- 如果当前数列最大的数被上一个斐波那契数减过，那么就去选**第二大**的（在代码实现的时候可以将一次操作后的数延后压入优先队列）。

**code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN = 1e2 + 8;
typedef long long ll;

int T,n;
ll f[NN],pre[NN];
ll a[NN];
ll p[NN];//p 表示 第 i 个斐波那契数 减去后剩下的数

void solve(){
	scanf("%d",&n);
	ll sum = 0;
	priority_queue<ll> Q;
	for(int i = 1; i <= n; ++i) scanf("%lld",&a[i]),sum += a[i],Q.push(a[i]);
	
	int lim = 0;//可用的 fibonacci 数列的上界
	for(int i = 1; i <= 70; ++i){
		if(sum == pre[i]){
			lim = i;break;
		}
	}
	if(!lim) return puts("NO"),void(0);//没有 `fibonacci` 序列的前缀和 和 数列的和对应
	for(int i = lim; i >= 1; --i){
		if(Q.empty()) return puts("NO"),void(0);
		ll x = Q.top();Q.pop();
		if(x < f[i]) return puts("NO"),void(0);
		x -= f[i];
		p[i] = x;
		if(i <= lim - 1){//延后压入优先队列
			if(p[i+1]) Q.push(p[i+1]);
		}
	}
	puts("YES");
}
int main(){
	f[1] = f[2] = 1;
	pre[1] = 1;pre[2] = 2;
	for(int i = 3; i <= 70; ++i){//预处理 fibonacci & 前缀和
		f[i] = f[i-1] + f[i-2];
		pre[i] = pre[i-1] + f[i];
	}
	scanf("%d",&T);
	while(T--){
		solve();
	}
}
```

---

## 作者：codemap (赞：0)

## 题目分析
我们首先可以求出总字符数，然后将斐波那契数列的各项求出，当总和不能与斐波那契数列的前缀和匹配时，直接输出 NO。

然后，我们只需从大往小进行搜索，对于每一位斐波那契数找一个足够的字母，同时记录一下不能选择上次选择的字母，搜索加回溯即可，如果能搜完，输出 YES，否则输出 NO。

## 代码
```cpp
#include<iostream>
using namespace std;
long long k,tot,a[10001],b[10001];
bool dfs(long long id,long long last)
{
    int i;
    if(!id)//搜完
        return 1;//返回1
    for(i=1;i<=k;i++)
        if(a[i]>=b[id]&&i!=last)//可使用当前字母
        {
            a[i]-=b[id];
            if(dfs(id-1,i))
                return 1;//成功的话返回1
            a[i]+=b[id];//回溯继续搜
        }
    return 0;//不成功返回0
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long t,i,s,sum,x,y,z;
    bool f;
    cin>>t;
    while(t--)
    {
        cin>>k;
        s=0;
        for(i=1;i<=k;i++)
        {
            cin>>a[i];
            s+=a[i];//求和
        }
        if(s==1)
        {
            cout<<"YES\n";
            continue;
        }
        x=1;
        y=1;
        sum=2;
        tot=1
        b[tot]=1;
        if(s>1)
        {
            tot++;
            b[tot]=1;
        }
        f=0;
        while(1)
        {
            if(sum==s)//如果总字符数能符合
                break;
            if(sum>s)//如果总字符数不能符合
            {
                f=1;
                break;
            }
            z=x+y;//模拟斐波那契数列
            x=y;
            y=z;
            sum+=y;
            tot++;
            b[tot]=y;
        }
        if(f)//总字符数不能符合
        {
            cout<<"NO\n";
            continue;
        }
        if(dfs(tot,0))//搜索
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }
    return 0;
}
```


---

