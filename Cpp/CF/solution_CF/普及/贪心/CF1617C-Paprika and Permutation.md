# Paprika and Permutation

## 题目描述

Paprika loves permutations. She has an array $ a_1, a_2, \dots, a_n $ . She wants to make the array a permutation of integers $ 1 $ to $ n $ .

In order to achieve this goal, she can perform operations on the array. In each operation she can choose two integers $ i $ ( $ 1 \le i \le n $ ) and $ x $ ( $ x > 0 $ ), then perform $ a_i := a_i \bmod x $ (that is, replace $ a_i $ by the remainder of $ a_i $ divided by $ x $ ). In different operations, the chosen $ i $ and $ x $ can be different.

Determine the minimum number of operations needed to make the array a permutation of integers $ 1 $ to $ n $ . If it is impossible, output $ -1 $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

For the first test, the only possible sequence of operations which minimizes the number of operations is:

- Choose $ i=2 $ , $ x=5 $ . Perform $ a_2 := a_2 \bmod 5 = 2 $ .

For the second test, it is impossible to obtain a permutation of integers from $ 1 $ to $ n $ .

## 样例 #1

### 输入

```
4
2
1 7
3
1 5 4
4
12345678 87654321 20211218 23571113
9
1 2 3 4 18 19 5 6 7```

### 输出

```
1
-1
4
2```

# 题解

## 作者：RevolutionBP (赞：4)

## 题目描述：
给你一个长度为 $n$ 的序列，让你选择一些数进行取模，使得最后的序列变成一个 $1\sim n$ 的排列，求最少操作次数，取模操作的模数是由你决定的

## 题目解法
首先我们发现这个序列的顺序对答案并没有影响，我们可以先给原序列排个序，接着我们用一些~~小学~~数学知识，观察取模得到的余数的特点，设模数是 $b$ ，原数是 $a$ ，余数是 $r$ 则有：
$$
a \equiv r \pmod b
$$
由于余数小于除数，所以我们有：$r<b$

当 $b>a$ 时，显然 $r=a$ 

当 $b<a$ 时，我们可以发现 $2r<a$

证明如下：
$$
a=\lfloor \dfrac{a}{b}\rfloor \times b+r
$$
$$
b>r
$$
$$
\because a>b~\therefore\lfloor \dfrac{a}{b}\rfloor \ge 1
$$
$$
a=\lfloor \dfrac{a}{b}\rfloor \times b+r\ge 1*b+r>r+r=2r
$$

那么我们现在可以尝试去做这个题了

首先我们容易发现：

如果一个数他本来就是 $1\sim n$ 范围中的话，那么我们不需要管它，继续处理其他的就行

如果说现在 $1\sim n$ 中的一个数是空白的我们应该看看现在我们的数列中有没有能取模得到它的，同时由于我们上面的结论，其实一个数能够取模后得到的，就是$0 \sim \dfrac{n}{2}$ 

所以我们可以选择直接双指针扫一下，对于所有大于 $n$ 的 $a_i$ 我们都让他在 $1\sim n$ 中去找到最小 $i$ 的然后判断是否 $2i<a_i$ 即可，如果是，则操作次数+1，不然的话就输出-1了

但是如果你现在着急提交的话会发现一个问题：
还是过不了！！！

别急，我们找一组数据：
```
5
5 5 5 9 14
```
问题很明显吧，我们没有判重！直接把重复的所有数中除去第一个都扔到vector里面，就大功告成力

码风比较丑，见谅一下
```cpp
//BlackPink is the Revolution
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<cctype>
#include<vector>
using namespace std;
const int N=2e5+5;
typedef long long ll;
typedef pair<int,int> P;
namespace scan{
    template <typename T>
    void read(T &x){
        x=0; char c=getchar(); int f=0;
        for(; !isdigit(c); c=getchar()) f |= c=='-';
        for(; isdigit(c); c=getchar()) x = x*10+(c^48);
        if(f) x = -x;
    }

    template <typename T>
    void write(T x,char ch){
        if(x<0) putchar('-'), x = -x;
        static short st[30],tp;
        do st[++tp] = x%10, x/=10; while(x);
        while(tp) putchar(st[tp--] | 48);
        putchar(ch);
    }
}
using namespace scan;
int T;
int n;
int a[N];
bool vis[N];
void work(){
	vector<int> v;
	memset(vis,0,sizeof(vis));
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	sort(a+1,a+1+n);
	int pos=1,ans=0;
	while(a[pos]<=n) vis[a[pos++]]=true;
	for(int i=1;i<pos;i++)
		if(a[i]==a[i-1]) v.push_back(a[i]);
	for(int i=pos;i<=n;i++) v.push_back(a[i]);
	int siz=v.size(); pos=0;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			if(i*2<v[pos] && pos<siz) ans++,pos++;
			else{
				write(-1,'\n');
				return;
			}
		}
	}
	write(ans,'\n');
}
int main(){
	read(T);
	while(T--) work();
    return 0;
}	

---

## 作者：HerikoDeltana (赞：3)

## CF1617C Paprika and Permutation

[洛谷 RemoteJudge](https://www.luogu.com.cn/problem/CF1617C)

[Paprika and Permutation](https://codeforces.com/problemset/problem/1617/C)

首先，题目要求将整个序列转化为一个 $1$ 到 $n$ 的排列，所以我们把已经符合条件的 $a_i$ 扔掉不用管。

然后将剩下的排序，按照大小顺序去一个一个判断能不能往排列里面填，判断的依据是：对于一个数 $x$，它在本题所述的变换中，只能变为自己本身或 $\le \dfrac{x}{2}$ 的数，于是 $x$ 越小，能变成的数的范围也就越小，所以我们贪心让小的数先去填补排列。

于是我们每次判断是否 $\dfrac{x}{2} \ge i$ 即可。如果不行的话就说明不存在解，输出 $-1$，否则累加答案。

为了方便，我这里直接在最一开始将整个序列都排序了。

* [Code](https://codeforces.com/contest/1617/submission/140574571)

---

## 作者：heaksicn (赞：3)

## 1 题意
给定一个长度为 $n$ 的数列 $a$ ，对他进行几次操作，每次操作可以选择任意的 $i$ 和 $x$，使得 $a_i=a_i\mod x$ ，使得 $a$ 变成 $1$ 到 $n$ 的一种排列。

求最小操作数。

多组数据。
## 2 思路
首先给出一个结论：对于每个 $a_i$，它可以变成他自己**或者 $\frac{(n-1)}{2}$ 以内的任意一个数。**

有了这个结论，就很好做了。

首先，找出 $a$ 中原本满足 $1\leq a_i\leq n$ 的数，将他们与 $a_{a_i}$ 交换。

然后，对于那些没有直接对应的数，我们应在剩下的序列中选出一个数与之对应。

明显，越小的数对应的数应该尽量小。

所以，我们把剩下的数进行排序，一一对应，如果不匹配就输出 $-1$，否则输出剩下的数的个数即可。

时间复杂度 $O(Tn\log n)$。
## 3 code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int T,n;
int a[100001],b[100001];
int main(){
	T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
		}
		sort(a+1,a+n+1);//排序
		int ans=0,fl=0;
		for(int i=n;i>=1;i--){
			if(a[i]<=n&&a[i]>i){//处理已经有的数
				int q=a[i];
				swap(a[i],a[q]);
			}
		}
		int cnt=0;
		for(int i=1;i<=n;i++){//剩下的数
			if(i==a[i]) continue;
			b[++cnt]=a[i];
		}
		sort(b+1,b+cnt+1);//再排序
		int now=0;
		for(int i=1;i<=n;i++){//对应
			if(i==a[i]) continue;
			a[i]=b[++now];
		}
		//for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		//cout<<endl;
		for(int i=1;i<=n;i++){
			if(a[i]==i) continue;
			if(a[i]<=i*2){//判断是否可行
				fl=1;
				break;
			}else ans++;
		}
		if(fl) cout<<-1<<endl;//不可行
		else cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：Fu_Da_Ying (赞：2)

## [原题链接](https://www.luogu.com.cn/problem/CF1617C)
## 题意：

有一个长度为 $n$ 的数组 $a_1,a_2,\dots,a_n$。每次操作你可以选择数组中的一个元素 $a_i$ 和 $x$，然后将 $a_i$ 替换为 $a_i\bmod x$。

求至少要多少次操作才能够将数组 $a$ 变为一个 $1$ 到 $n$ 的排列。如果无法实现，输出 $-1$。

## 思路：

先说结论，任意的 $x$ 可以变成小于 $\lfloor \frac{x+1}{2} \rfloor$ 的数。

证明：设模数为 $y(1\le y < n)$，可以发现当 $y \ge \lfloor \frac{x+1}{2} \rfloor$ 时，$y$ 越大，$x \bmod y$ 就越小。当 $y < \lfloor \frac{x+1}{2} \rfloor$ 时，$y$ 越大，$x \bmod y$ 就越大。所以函数 $z \equiv x \pmod y$ 的最大值是在 $y=\lfloor \frac{x+1}{2} \rfloor$ 的时候。此时 $z=\lfloor \frac{x+1}{2} \rfloor-1$。所以 $z$ 的范围是 $[1,\lfloor \frac{x+1}{2} \rfloor)$。

所以我们只要排序，然后那些 $\ge n$ 的数取出，判断是否可以变成第一个序列中没有的数，是的话就将这个数标记，不是的话就退出输出 ```-1```。

~~然后你就 WA 了。~~

原因是我们没有判重，在条件上加一个即可。

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[1000001],sum,j;
bool vis[1000001],flag;//vis[i]表示现在的序列中,i是否在里面 
signed main(){
    scanf("%lld",&t);
    while(t--){
        sum=0;
        j=1;
        flag=0;
        scanf("%lld",&n);
        for(int i=1;i<=n;i++) vis[i]=0;//清除vis数组 
        for(int i=1;i<=n;i++){
            scanf("%lld",&a[i]);
            if(a[i]<=n) vis[a[i]]=1;//如果a[i]在区间[1,n]中,用vis数组标记 
        }
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++){
        	if(a[i]<=n&&a[i-1]!=a[i]) continue;//如果a[i]在区间[1,n]中,且a[i]与a[i-1]不重复,跳过 
        	while(vis[j]==1) j++;//如果这个数已经有了,则换到下一个序列中没有的数 
        	if(j>=(a[i]+1)/2){//如果j不小于(a[i]+1)/2,说明找不到一个正整数x使得a[i]%x=j
        	    flag=1;
				break;//退出 
			}
			sum++;
			vis[j]=1;//将j加入序列,并将答案+1 
		}
        if(flag==0) printf("%lld\n",sum);
        else printf("-1\n");
    }
    return 0;
}
```

### [AC 记录](https://www.luogu.com.cn/record/170860791)

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1617/C)
题目给一个数组 $a_1,a_2,\dots,a_n$。每次操作可以选择数组中的一个元素 $a_i$ 并自选一个数 $x$，将 $a_i$ 变为 $a_i \bmod x$。

## 思路
一道十分不错的贪心题。

一种容易想到的思路是：**将需要调整和未被使用的元素一一拿出来，暴力匹配。**

但这种方法的复杂度为 $ \mathcal{O}(n^2) $，显然会超时。

决策具有后效性，因此考虑贪心。

令 $extra_i$ 表示需要调整的元素，$target_i$ 表示未被使用的目标数。

容易发现，若 $target_i$ 无法通过 $extra_j \bmod x$ 的方式得到，那么 $extra_j \leq 2 \times target_i$。

现在，我们要想办法尽可能的让 $extra_j > 2 \times target_i$。

一种贪心策略是：**将 $extra$ 和 $target$ 分别排序，一一判断。**

容易证明，若排序后的 $target_i$ 和 $extra_i$ 无法满足要求，则此样例无解。

具体细节看代码。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005];
bool used[100005]; // 记录1~n中已存在的数
int solve(int n) {
	memset(used,false,sizeof(used));
	vector<int> extra; // 需要调整的元素
	for (int i=0;i<n;i++) {
		if (a[i] >= 1 && a[i] <= n && !used[a[i]]) {
			used[a[i]] = true;
		} else {
			extra.push_back(a[i]);
		}
	}
	vector<int> target; // 未被使用的目标数
	for (int i = 1; i <= n; ++i) {
		if (!used[i]) {
			target.push_back(i);
		}
	}
	// 如果数量不匹配，无法调整
	if (extra.size() != target.size()) {
		return -1;
	}
	// 排序后贪心匹配
	sort(extra.begin(), extra.end());
	sort(target.begin(), target.end());
	for (int i = 0; i < (int)extra.size(); ++i) {
		if (extra[i] <= 2 * target[i]) {
			return -1;
		}
	}
	return extra.size();
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		cout << solve(n) << '\n';
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(tn \log n) $，本题中 $\sum{n} \leq 2 \times 10^5$，可以通过本题。

---

## 作者：postpone (赞：0)

把序列从小到大排序，先填小的再填大的，这样贪心是最优的。

具体地，对于在值域 $[1, n]$ 内的整数，如果没填过，就不用操作直接填，如果填过，就需要操作一次变成更小的数然后填进去。对于在值域外的数，都需要操作一次，找能填到的坑填进去。由于序列从小到大排序过，先填的一定是在值域内的整数，这样就是最优的解。

需要注意，对于整数 $i$，操作之后，$i$ 的取值范围是 $[1, \min{(\frac i2,\  n)}]\cap \mathbb{Z}$。

相比于其他题解，有一个更容易理解的实现方法：用 `std::set` 存放目标排列。遍历序列时，对于值域内且未擦除的数，直接擦除；否则就二分查找**在操作后的取值范围内的，最大的数**，然后擦除，最后判断集合是否为空集即可。

核心代码如下。
```cpp
for (auto i : a) {
    if (S.contains(i)) {
        S.erase(i);
        continue;
    }
    res++;
    int t = min(i / 2 - (i % 2 == 0), n);

    auto it = S.upper_bound(t);
    if (it == S.begin()) {
        break; // 说明这个数没地方填了，那么一定不行。
    }
    S.erase(--it);
}
```
完整代码见[链接](https://codeforces.com/contest/1617/submission/282157906)。

---

## 作者：Special_Tony (赞：0)

# 思路
首先每个数可以不变或变成任意一个 $\le\lceil\frac n2\rceil$ 的数，显然不可以对于 $n\le m$，$\lceil\frac n2\rceil$ 不可能比 $\lceil\frac m2\rceil$ 大，所以我们要先排序。首先 $a_i\le n$ 且没重复的数肯定不改，其它的数就找一个不大于 $\lceil\frac{a_i}2\rceil$ 的数删掉，如果没数了就无解。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, a[100005], sum;
bitset <100005> vis;
set <int> st;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		st.clear ();
		sum = 0;
		for (int i = 1; i <= n; ++ i)
			cin >> a[i], vis[i] = 0, st.insert (i);
		sort (a + 1, a + 1 + n);
		for (int i = 1; i <= n; ++ i)
			if (a[i] > n || vis[a[i]])
				if (*st.begin () * 2 < a[i])
					st.erase (st.begin ()), ++ sum;
				else {
					cout << "-1\n";
					goto there;
				} else
				vis[a[i]] = 1, st.erase (a[i]);
		cout << sum << '\n';
there:
		;
	}
	return 0;
}
```

---

## 作者：Infinite_Loop (赞：0)

# CF1617C
## 题意
给定一个长度为 $n$ 的数组 $a$，每次操作可以将 $a _ {i}$ 变成 $a _ {i} \bmod x$，问能否将数组变成一个 $1$ 到 $n$ 的排列，可以输出最小操作次数，不可以输出 $-1$。
## 思路
首先我们可以发现一个性质：

- 当 $x > a _ {i}$ 时，$a _ {i} \bmod x = a _ {i}$。
- 当 $x \le a _ {i}$ 时，$0 \le a _ {i} \bmod x < \lfloor \frac{a _ {i} + 1}{2} \rfloor$。

然后我们可以先将 $a$ 数组从小到大排个序，然后枚举 $i$，每个 $i$ 有以下几种情况：

- 当 $a _ {i} \le n$ 且 $vis[a _ {i}] = 0$，把 $vis[a _ {i}]$ 标记为 $1$。
- 当 $x \ge \lfloor \frac{a _ {i} + 1}{2} \rfloor$ 或者 $a _ {i} < x$，直接弹出，输出 $-1$。否则把 $vis[a _ {i}]$ 标记为 $1$，将 $ans +1$。

每次别忘了更改下一次 $a _ {i}$ 需要变成的数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t,n,a[N],vis[N]; 
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=0;i<=n;i++)vis[i]=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+1+n);
		int x=1,flag=1,ans=0;
		for(int i=1;i<=n;i++){
			if(a[i]<=n&&!vis[a[i]]){
				vis[a[i]]=1;
				while(vis[x]&&x<=n)x++;
			}else{
				if(x>=(a[i]+1)/2||a[i]<x){
					flag=0;
					break;
				}else{
					vis[x]=1;
					while(vis[x]&&x<=n)x++;
				}
				ans++;
			}
		}
		if(flag)cout<<ans<<endl;
		else cout<<-1<<endl;
	}
	return 0;
}
```

---

