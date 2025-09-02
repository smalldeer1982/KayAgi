# Subtract Operation

## 题目描述

You are given a list of $ n $ integers. You can perform the following operation: you choose an element $ x $ from the list, erase $ x $ from the list, and subtract the value of $ x $ from all the remaining elements. Thus, in one operation, the length of the list is decreased by exactly $ 1 $ .

Given an integer $ k $ ( $ k>0 $ ), find if there is some sequence of $ n-1 $ operations such that, after applying the operations, the only remaining element of the list is equal to $ k $ .

## 说明/提示

In the first example we have the list $ \{4, 2, 2, 7\} $ , and we have the target $ k = 5 $ . One way to achieve it is the following: first we choose the third element, obtaining the list $ \{2, 0, 5\} $ . Next we choose the first element, obtaining the list $ \{-2, 3\} $ . Finally, we choose the first element, obtaining the list $ \{5\} $ .

## 样例 #1

### 输入

```
4
4 5
4 2 2 7
5 4
1 9 1 3 4
2 17
17 0
2 17
18 18```

### 输出

```
YES
NO
YES
NO```

# 题解

## 作者：qifan_maker (赞：3)

### 题目链接
[洛谷](https://www.luogu.com.cn/problem/CF1656B)

[Codeforces](https://codeforces.com/contest/1656/problem/B)
### 题意分析
有一个长度为 $n$ 的数列 $a$ 和一个整数 $k$，你可以对其进行 $n-1$ 次操作，每次操作删去一个数 $a_i$，然后把数组的每个数都减去 $a_i$。问能不能让数组中只剩下 $k$。
### 题目解法
首先我们可以看到第一个样例：

$n = 4~~~k = 5$

$a = [4,2,2,7]$

在第一个示例中，我们可以通过以下操作得到 $k$：

首先我们选择第三个元素，变成 $[2,0,5]$。接下来，我们选择第一个元素，变成 $[-2,3]$。最后，我们选择第一个元素，变成 $[5]$。

这时候我们可以发现一个规律：

在每一步中，数组中任意两个数的差不变。

所以：

**如果数组中有任意两个数的差为 $k$，那么我们就可以让最后剩下一个 $k$。**

这时候这道题就可以转变为：找到一组 $i,j$ 使 $a_i - a_j = k$。

但是还是有一个问题：直接暴力枚举的时间复杂度是 $O(n^2)$，还是会 TLE。

这时候可能有人~~（指我自己）~~会想到用 桶 来判断有没有差为 $k$ 的两个数，我们看一眼数据范围：$-10^9 \le a_i \le 10^9$，如果用桶明显会爆，需要离散化，但是有点麻烦，所以我们我们需要用到万能的 STL。

首先，用一个 ``map`` 来存储数组中每个数字的出现次数。然后，用一个 ``for`` 循环来判断数组中是否存在两个数字的差为 $k$ 的情况，如果存在则输出 ``YES``，否则输出 ``NO``。

时间复杂度为 $\mathcal{O}(n\log n)$，可以 AC。
### [AC](https://www.luogu.com.cn/record/102274767) Code
```c++
/*
题目编号：
B. Subtract Operation
思路：
如果数组中有任意两个数的差为 k，那么我们就可以让最后剩下一个 k。 
*/
#include <bits/stdc++.h>
using namespace std;
long long t,n,k,a[200100];
map<long long,long long> buc;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--){
		cin >> n >> k;
		buc.clear();
		for (int i=1;i<=n;i++){
			cin >> a[i];
			buc[a[i]]=1;
		}
		bool flag=false;
		for (int i=1;i<=n;i++){
			if (buc[a[i]+k]){
				flag = true;
			}
		}
		if (flag){
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
```

---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定一个长度为 $n$ 的序列 $a$，每次可以在序列中删去一个数 $x$，同时我们需要将整个序列所有的数同时减去 $x$。问在经过 $n-1$ 次操作之后能否将原序列变为一个值为 $k$ 的数。

#### 思路分析


------------
由于每次会将**整个**序列减去 $x$，所以无论如何变化，序列中剩余的所有数的相对差距是不会变的。换句话来说就是序列中任意两个数的差恒定不变。

故可以发现只要序列中有任意两个数的值的差为 $k$，那么一定可以满足题设。

首先将序列 $a$ 排序，用双指针找出一对差为 $k$ 的数。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#define int long long
using namespace std;
const int N = 200050;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int a[N];
signed main(){
	int T = read();
	while(T--){
		int n = read() , k = read();
		for(int i=0;i<n;i++){
			a[i] = read();
		}
		bool ans = false;
		if(n == 1) ans = (a[1] == k);
		else{
			sort(a,a+n);
			int i = 0 , j = 1;
			while(j < n && i < n){
				if(a[i] + abs(k) == a[j]){
					ans = true;
					break;
				}
				else if(a[i] + abs(k) < a[j]) i++;
				else j++;
			}
		}
		if(ans == true){
			printf("YES\n");
		}
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：Hooch (赞：2)

### 题目大意

给定一个长度为 $n$ 的序列 $a$，每次可以选择一个 $a_i$ 并删除它，再将 $a$ 中的每一个元素都减去 $a_i$，能不能有一种操作顺序使得执行了 $n-1$ 此操作后剩下的数为 $0$。

### 思路

我们先模拟一下 $n=4$ 的操作执行的大致过程。

如下：

+ 初始序列 $a_1,a_2,a_3,a_4$
+ 全部减去 $a_1$，则序列为 $a_2-a_1,a_3-a_1,a_4-a_1$
+ 全部减去**现在序列**的 $a_1$，则序列为 $a_3-a_1-(a_2-a_1),a_4-a_1-(a_2-a_1)$，化简后 $a_3-a_2,a_4-a_2$
+ 减去现在的 $a_3$，变为 $a_4-a_3$。

可以发现在这个过程中，$a_4$ 分别减去了 $a_1,a_2,a_3$ 。又因为原序列可随意排列，则只需要判断任意两个数的差是否为 $0$ 即可。

---

## 作者：Disjoint_cat (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1656B)

## 1.题意

给你一个长为 $n$ 的数列，每次操作可以删去一个数，并把其他数字减去这个数字。问是否存在一种操作方式，使在 $(n-1)$ 次操作后剩下一个数 $k$。

## 2.解法

如果直接暴力枚举，复杂度至少是 $O(n!)$，所以这种方法直接 gg。

我们不妨让 $n$ 较小，然后看一下能推出什么东西。

设 $n=4$，四个数分别是 $a,b,c,d$。

假设第一次删除 $a$，则剩下 $b-a,c-a,d-a$。

假设第二次删除 $b-a$，则剩下 $(c-a)-(b-a),(d-a)-(b-a)$，即 $c-b,d-b$。

假设第三次删除 $c-b$，则剩下 $(d-b)-(c-b)$，即 $d-c$。

诶，结果是 $d-c$？那也就是说，最后的结果就是其中 $2$ 个数的差？

不难证明，当 $n$ 为任意值时，最后的结果都是两个数的差。

所以，我们只要判断是否存在 $i$ 和 $j$，满足 $a_i-a_j=k$。

但是，直接枚举 $i$ 和 $j$ 的时间复杂度最坏是 $O(n^2)$，仍然不能通过。

但是，我们只要用 [A-B数对](https://www.luogu.com.cn/problem/P1102) 这道题的解法（二分/单调队列），就可以把复杂度降到 $O(n\log n)$，从而通过本题了。

## 3.code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long n,k,a[200005],p;
bool ok;
int main()
{
	cin>>t;
	while(t--)
	{
		scanf("%lld%lld",&n,&k);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
		sort(a+1,a+n+1);ok=0,p=1,a[n+1]=1000000000000000;
		for(int i=1;i<=n;i++)
		{
			while(a[p]<a[i]+k)++p;
			if(a[p]==a[i]+k)
			{
				ok=1;
				break;
			}
		}
		printf("%s\n",(ok?"YES":"NO"));
	}
	return 0;
}
```

---

## 作者：CodeMao (赞：0)

主算法：**二分**

思路：

- 因为每次修改都会将**整个序列**减去 $x$ , 所以序列中任意两个数之间的差仍然不变。
  
- 所以只需查找序列中是否有两个数的差为 $k$ 即可。
  

使用 `STL` 的 `lower_bound` 需要注意：

- 被查找的序列必须已经有序。
  
- `lower_bound` 返回的值为查找到序列中第一个 $x$ 的**地址**。注意是**地址**！

代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 200005
bool f;
int t,n,k;
int a[maxn];
inline void in(int &x){
    x=0;char ch=getchar();bool k=0;
    while(ch<'0'||ch>'9'){
        if(ch=='-') k=1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    if(k) x=~x+1;
}
int main(){
    in(t);
    while(t--){
        in(n),in(k);f=0;
        std::memset(a,0,sizeof(a));
        for(int i=1;i<=n;++i) in(a[i]);
        std::sort(a+1,a+1+n);
        for(int i=1;i<=n;++i)
            if(a[std::lower_bound(a+1,a+1+n,a[i]-k)-a]==a[i]-k) {f=1;break;}
        if(f) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：lsj2009 (赞：0)

## 题目大意
给定序列 $\{a_n\}$，求是否有一种顺序依次进行 $n-1$ 次操作（每次将其中一个 $a_i$ 从序列中删去，然后将剩下的每个 $a_j$ 都减去 $a_i$），满足最后留下的数 $=k$。
## 思路
最暴力的想法是枚举 $1$ 到 $n$ 的全排列，然后依次删除，判断最后留下来的值是否为 $k$。这样做时间复杂度为 $\Theta(n^2\times n!)$，超时。

考虑更优的做法。

我们假设我们删除的顺序是 $\{b_n\}$，即依次删除 $a_{b_1},a_{b_2},\cdot\cdot\cdot,a_{b_n}$。

容易看出，每次删除 $a_{b_i}$ 后，剩余的数与他们的初时值之差应该是一定的，即 $\sum\limits_{i=1}^n a_{b_i}'$。

值得注意的一点是这里是 $a_{b_i}'$ 而非 $a_{b_i}$。为什么呢？这里的 $a_{b_i}'$ 指的是 $a_{b_i}$ 在被删除前最后的值，即 $a_{b_i}-\sum\limits_{j=1}^{i-1} a_{b_j}'$。

将其带入到 $\sum\limits_{i=1}^n a_{b_i}'$ 里，则变为 $\sum\limits_{i=1}^n (a_{b_i}-\sum\limits_{j=1}^{i-1} a_{b_j}')$。

我们不妨设 $f_i$ 为 $\sum\limits_{j=1}^{i-1} a_{b_j}'$，容易发现，$f_{i+1}$ 包含 $f_i$ 的，即 $f_{i+1}$ 可以写作递推公式 $=f_i+x$。

同理，$a_{b_{i+1}}-f_{i+1}$ 也是包含 $f_i$ 的，则我们不妨将 $a_{b_{i+1}}-f_{i+1}$ 写成 $a_{b_{i+1}}-[f_i+(a_{b_i}-f_i)]=a_{b_{i+1}}-a_{b_i}$。

换言之，$f_{i+1}=a_{b_i}$。

则 $a_{b_i}'=\sum\limits_{i=1}^n (a_{b_i}-a_{b_{i-1}})$，将其展开后得 $a_{b_i}'=a_{b_i}-a_{b_1}$。

我们要求 $a_{b_n}'=k$ 即要求 $a_{b_n}-a_{b_1}=k$。

题目变成寻找一个数对 $(i,j)$ 满足 $a_i-a_j=k$ 且 $i>j$。

直接枚举复杂度为 $\Theta(n^2)$，无法通过此题。

我们不妨把上式移一个项变为 $a_i-k=a_j$，我们可以枚举 $a_i$ 然后判断是否有 $a_j=a_i-k$。对于寻找 $a_j$ 我们可以通过使用二分查找进行，也可以进行一个哈希，但略显繁琐。

下面给出二分查找代码。

## Code:
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define pb pop_back
#define mk make_pair
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
template <typename T> inline void read(T& x) {
	x=0; T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch&15); ch=getchar(); }
	x=x*f;
	return;
}
template <typename T,typename ...Arg> inline void read(T& x,Arg& ...arg){
	read(x); read(arg...);
}
int power(int a,int b) {
	int ans=1;
	do {
		if(b&1) ans*=a; a*=a;
	} while(b>>=1);
	return ans;
}
const int N=2e5+5;
int a[N],n,k,T;
signed main() {
	read(T);
	while(T--) {
		read(n,k);
		_for(i,1,n)
			read(a[i]);
		sort(a+1,a+n+1);
		bool have_ans=0;
		_for(i,1,n)
			if(a[lower_bound(a+1,a+n+1,a[i]-k)-a]==a[i]-k) {
				puts("YES"); have_ans=1; break;
			}
		if(!have_ans)
			puts("NO");
	}
	return 1;
}

```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1656B](https://www.luogu.com.cn/problem/CF1656B)

* **【解题思路】**

首先，我们可以假设，第 $i$ 次操作一定会选取当前数组中的第一个数。如果不是这样，我们可以通过重排数组里的数使得条件被满足。

然后我们就可以用一个小数据模拟了。然后就可以发现，最后的结果一定是最后两个数的差。因为我们可以重排数组，我们只要把差为 $k$ 的两个数放后面就行。

那么原题等价于是否存在一组 $i,j$ 使得 $a_i-a_j=k$。

`map`即可。（已经不敢用 `unordered_map` 了。）

* **【代码实现】**

```cpp
#include <iostream>
#include <array>
#include <set>

using namespace std;

array<int,200000> nums;
set<int> cnter;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		int cnt,target;
		cin>>cnt>>target;
		cnter.clear();
		for(int i=0;i<cnt;i++)
			cin>>nums[i],cnter.insert(nums[i]);
		for(int i=0;i<cnt;i++)
			if(cnter.find(nums[i]+target)!=cnter.end())
			{
				cout<<"Yes";
				goto nextcase;
			}
		cout<<"No";
		nextcase:cout<<'\n';
	}
	return 0;
}


```

---

## 作者：Eric998 (赞：0)

# 题意 #
给你一串 $ n $ 个数 $ a_1,a_2......a_n $,允许以下操作：

1.选一个数 $ i (i \leq n) $

2.对每一个 $ j (j \neq i,j \leq n) $ ,将 $ a_j $ 减少 $ a_i $。

2.从 $ a $ 里删除 $ a_i $

求经过 $ n-1 $ 次操作后，数组里能不能只剩下 $ k $ ?

# 思路
### 1.从简单情况想起
####  $ n = 3 $ 时
此时，有三个数：$ a_1, a_2, a_3 $。假设先选取 $ j = 1 $ ,进行操作，则剩下的$ a_2,a_3 $ 变为 $ a_2-a_1,a_3-a_1 $。
再选取 $ j = 2 $(此时指向 $ a_2-a_1 $),得到最后剩下：$ (a_3-a_1)-(a_2-a_1)=a_3-a_2-a_1+a_1=a_3-a_2 $

各位聪明的读者可能已经看出来了，只有最后一个选中的数会对结果产生影响。那么，出来吧，~~皮卡丘~~ 证明！
### 2.证明
假设有 $ n+1 $个数，每次操作 $ j $ 取值 $ 1,2,3......n $,那么最后剩下：

$ a_{n+1}-a_1-(a_2-a_1)-(a_3-(a_2-a_1))-......-(a_n-(a_{n-1}-(......)))$

设 $ s_i=(a_i-(a_{i-1}-(......))) $

则剩下 $ a_{n+1}-s_n-s_{n-1}-.....-s_1 $

注意！！！根据 $ s_i $ 的定义, $s_{i+1}=a_{i+1}-s_i=$。

$s_n+s_{n-1}+s_{n-1}+......+s_1$

$=s_n+s_{n-1}+......+a_2$

$=s_n+s_{n-1}+......+a_3$

$......$

$=a_i$

所以只有最后一个数会产生影响。

# 实现
原问题被转化为了在 $ a $ 中找到两个差为 $ k $ 的数。
话不多说，直接排序+二分,复杂度 $ N \log N $。~~好像还挺押韵的~~
# 代码
```cpp
#include<iostream>
#include<vector>
#include<map>
#include<math.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define inf 0x3f3f3f3f
#define minf 0x3f
#define inp(x) cin>>x
#define otp(x) cout<<x
#define otp_nl(x) cout<<x<<"\n"
#define otp_sp(x) cout<<x<<" "
#define _int long long
#define veci vector<int>
#define str string
#define pb(x) push_back(x)
#define fr(k,len) for(k=0;k<len;k++)
#define nfr(k,len) for(int k=0;k<len;k++)
#define ret return
void solve(){
	int n,k;
	cin>>n>>k;
	_int sum=0;
	int mx=-inf;
	vector<int> ary;
	for(int i=0;i<n;i++){
		int buf;
		cin>>buf;
		ary.pb(buf);
		sum+=buf;
	}
	sort(ary.begin(),ary.end());
	for(int i=0;i<n;i++){
		if(binary_search(ary.begin(),ary.end(),ary[i]-k)){
			cout<<"YES\n";
			return;
		}
	}
	cout<<"NO\n";
	ret;
}
int main(){
    int t;
    cin>>t;
	nfr(i,t){
		solve();
	}
	ret 0;
}
```
# 后记
笔(ju)者(ruo)在比赛时没有想到二分，卡常卡了一个小时，导致B题得分还没有A题高。

---

## 作者：沉石鱼惊旋 (赞：0)

### 题目翻译

有 $n$ 个数，每次选一个删掉，其他数都减去删掉的数，问最后一个数会不会等于 $k$。

### 题目分析

这题一看就是结论题。我们先把 $a$ 数组假设为删除数字顺序定下来的数组，看最后结果。

![](https://cdn.luogu.com.cn/upload/image_hosting/xhqaiz6i.png)

上述过程每步已经化简。

那么，很容易看出，最后答案是两个数的差。

这题便成为了：$n$ 个数里，是否有两个数字差为 $k$。

那么我想到是用 `map` 和 `set` 做。

`map` 没访问的位置便不存在，不担心 RE，`set` 自带 `count` 找出现次数。

### AC 代码

#### set

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
void solve()
{
	set<ll>s;
	s.clear();
	ll n,k;cin>>n>>k;
	bool f=0;
	for(int i=1;i<=n;i++)
	{
		ll x;
		cin>>x;
		s.insert(x);
		if(s.count(x-k)||s.count(x+k))//差值为k，可能x是较大数，也可能是较小数。
		{
			f=1;
		}
	}
	puts(f==1?"YES":"NO");
}
int main()
{
	int t;cin>>t;
	while(t--)
	{
		solve();
	}
    return 0;
}
```

#### map

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
void solve()
{
	map<ll,bool>mp;
	mp.clear();
	ll n,k;cin>>n>>k;
	bool f=0;
	for(int i=1;i<=n;i++)
	{
		ll x;
		cin>>x;
		mp[x]=1;
		if(mp[x-k]||mp[x+k])
		{
			f=1;
		}
	}
	puts(f==1?"YES":"NO");
}
int main()
{
	int t;cin>>t;
	while(t--)
	{
		solve();
	}
    return 0;
}
```



---

## 作者：Yukinoshita_Yukino (赞：0)

已知数列里最后一个数为 $k$，设删除前最后一个数为 $a$，则删除最后一个数前的数列为 $ \left\lbrace a+k,a \right\rbrace$。

设删除前倒数第二个数为 $b$，则删除倒数第二个数前的数列为 $ \left\lbrace a+b+k,a+b,b \right\rbrace$。

以此类推，可以注意到数列最后能够出现 $k$ 的情况等价于数列中有任意两个数差为 $k$。感性理解就是把除了这两个数之外的数删完，它们的差值不变，为 $k$。所以最后一次操作一定会出现 $k$。

用 map 即可。~~我第一次用 sort + two pointer TLE了两发~~

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
int T,n,k;
int a[maxn];

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--)
	{
		map<int,int> mm;
		cin>>n>>k;
		for(int i=1;i<=n;i++) 
		{
			cin>>a[i];
			mm[a[i]]=1;
		}
		int f=0;
		for(int i=1;i<=n;i++)
		{
			if(mm[a[i]+k]==1) f=1;
		}
		if(f==1) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
		
	}
	return 0;
 } 

```

---

