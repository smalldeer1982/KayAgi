# Kuroni and Simple Strings

## 题目描述

Now that Kuroni has reached 10 years old, he is a big boy and doesn't like arrays of integers as presents anymore. This year he wants a Bracket sequence as a Birthday present. More specifically, he wants a bracket sequence so complex that no matter how hard he tries, he will not be able to remove a simple subsequence!

We say that a string formed by $ n $ characters '(' or ')' is simple if its length $ n $ is even and positive, its first $ \frac{n}{2} $ characters are '(', and its last $ \frac{n}{2} $ characters are ')'. For example, the strings () and (()) are simple, while the strings )( and ()() are not simple.

Kuroni will be given a string formed by characters '(' and ')' (the given string is not necessarily simple). An operation consists of choosing a subsequence of the characters of the string that forms a simple string and removing all the characters of this subsequence from the string. Note that this subsequence doesn't have to be continuous. For example, he can apply the operation to the string ')()(()))', to choose a subsequence of bold characters, as it forms a simple string '(())', delete these bold characters from the string and to get '))()'.

Kuroni has to perform the minimum possible number of operations on the string, in such a way that no more operations can be performed on the remaining string. The resulting string does not have to be empty.

Since the given string is too large, Kuroni is unable to figure out how to minimize the number of operations. Can you help him do it instead?

A sequence of characters $ a $ is a subsequence of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters.

## 说明/提示

In the first sample, the string is '(()(('. The operation described corresponds to deleting the bolded subsequence. The resulting string is '(((', and no more operations can be performed on it. Another valid answer is choosing indices $ 2 $ and $ 3 $ , which results in the same final string.

In the second sample, it is already impossible to perform any operations.

## 样例 #1

### 输入

```
(()((```

### 输出

```
1
2
1 3```

## 样例 #2

### 输入

```
)(```

### 输出

```
0```

## 样例 #3

### 输入

```
(()())```

### 输出

```
1
4
1 2 5 6```

# 题解

## 作者：xht (赞：3)

要求最终不能再存在 `()` 这样的子串，因此只能是若干个 `)` 后接若干个 `(`。

因此我们要找到一个位置，这个位置左边的 `(` 全部被删掉，右边的 `)` 全部被删掉。

由于只能删掉同等数量的 `(` 和 `)`，而这个位置一定存在，因此答案要么为 $0$，要么为 $1$。

```cpp
const int N = 1e3 + 7;
int n, a[N], b[N];
char s[N];

int main() {
	rds(s, n);
	vi ans;
	for (int i = 1; i <= n; i++)
		a[i] = a[i-1] + (s[i] == '(');
	for (int i = n; i; i--)
		b[i] = b[i+1] + (s[i] == ')');
	for (int i = 0; i <= n; i++)
		if (a[i] == b[i+1]) {
			for (int j = 1; j <= i; j++)
				if (s[j] == '(') ans.pb(j);
			for (int j = i + 1; j <= n; j++)
				if (s[j] == ')') ans.pb(j);
			if (!ans.size()) {
				print(0);
				return 0;
			}
			print(1);
			print(ans.size());
			for (int x : ans) print(x, ' ');
			return 0;
		}
	return 0;
}
```

---

## 作者：cyh_toby (赞：3)

# 题意

原题：[CF 1305B 【Kuroni and Simple Strings】](https://www.luogu.com.cn/problem/CF1305B)

给定一小括号序列。

每次可以删除其形如 `()` 或 `(())` 等形式的子串，子串可以不连续，求最少操作多少次，以及操作方案，使括号序列不再包含这样形式的子串。

# 分析

睿智的我们发现，如果某子串呈现类似于 `)(` 的形式，就不需要管它，一定不可以构成可以删除的子串。

接着，分析一个括号串

$$(\,)\,(\,(\,)\,)\,$$

如果我们把他分成这样

$$\color{Blue}(\,)\;\color{Orange}(\,(\,)\,)$$

就需要操作两次，因为不允许删除形如 `()()` 的子串

可是，如果我们这样

$$\color{Red}(\;\color{Black})\color{Red}(\;\color{Black}(\;\color{Red})\,)$$

删去红色括号，留下不能构成可删除子串的黑色括号，就可以只用操作一次。

进而发现，什么情况可以在同一次操作处理？

就是**左括号和右括号的出现分别连续**，一旦出现左右括号匹配上的情况，就只能继续往后找右括号而不能找左括号了。

此外，上述例子还告诉我们，需要找到一种方法，把 **不得不匹配上** 的括号删去，留下形如 `)(` 的子串。

注意到所谓 `)(` 形式，其实是左右括号位置相反，那我们考虑尽可能删去原串左侧的 `(` ， 原串右侧的 `)`，而不处理左侧的 `)` 和右侧的 `(` 。

因为只有左侧删 `(` ，右侧删 `)` 才能保证上述的左右括号分别连续。

可是何谓左侧右侧呢，并不是相对于原串中心，而是一种**相对关系**

因此，考虑建立两个指针 $i,\,j$，从原串头尾向彼此扫，即

$$i->\;\;\;\;\;\;<-j$$
$$(())())(($$

一旦两个指针所指位置匹配成一对括号，删去，否则跳过。

然后发现操作数要么是 $1$ 要么是 $0$

虽然很玄幻，但考场上试一试发现对的就交了，理论上按上述过程想应该是对的。虽然不会严格证明。

可能有点贪心的思路吧

# 源码
其实可以更精简，但考场上没有顾虑那么多。

一开始有另一个思路，所以建立数组 $a$ ，但那是错的，并且 $a$ 也没啥用。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
char s[N];
int a[N];
int flag = 0, tot = 0;
int main()
{
	scanf("%s", s+1);
	int n = strlen(s+1);
	for (int i = 1; i <= n; i++) {
		if (s[i] == '(') {
			a[i] = 1;
		}
		if (s[i] == ')') {
			a[i] = 2;
		}
	}
	int i = 1, j = n;
	while (1) {
		while (i <= j && (a[i]==2))
			i++;
		while (i <= j && (a[j]==1))
			j--;
		if (i >= j) {
			break;
		}
		a[i] = a[j] = -1;
		flag = 1;
		tot += 2;
		i++, j--;
	}
	if (flag) {
		printf("1\n%d\n", tot);
		for (int i = 1; i <= n; i++)
			if (a[i] == -1)
				printf("%d ", i);
	}
	else {
		printf("0\n");
	}
	return 0;
}

```


---

## 作者：皎月半洒花 (赞：2)

发现显然删除一次和删除多次是等价的。那么只需要记录每个左括号和右括号的位置，找一个位置 $p$ 使得前面的左括号和右面的右括号一样多且最大。$0$ 的情况是存在某个 $p$ 使得 $p$ 前缀都是 `)` 并且 $p+1$ 后缀都是 `(` 。判断一下即可。

```cpp
int main(){
    cin >> (s + 1) ;
    int n = strlen(s + 1) ;
    for (int i = 1 ; i <= n ; ++ i){
        if (s[i] == '(') l[++ l[0]] = i, sum[i] = sum[i - 1] ;
        if (s[i] == ')') r[++ r[0]] = i, sum[i] = sum[i - 1] + 1 ;
    }
    for (int i = 0 ; i <= n ; ++ i)
        if (sum[i] == i && sum[i] == sum[n]) return puts("0"), 0 ;
    int L = 1, R = r[0] ;
    while (1){
        if (l[L] > r[R]) break ; ++ ans;
        stk[++ tp] = l[L], stk[++ tp] = r[R] ;
        L ++ ; R -- ; if (L > l[0] || !R) break ;
    }
    sort(stk + 1, stk + tp + 1) ;
    cout << 1 << endl << ans * 2 << endl ;
    for (int i = 1 ; i <= ans * 2 ; ++ i) cout << stk[i] << " " ;
}

---

## 作者：zct_sky (赞：0)

### Solution:
-----
考虑贪心。

当剩余序列中所有未匹配的 `(` 能匹配数都为 $0$ 时，显然该括号序列无法匹配（`(` 的能匹配数指该括号之后未匹配的 `)` 数）。

每个 `(` 匹配 `)`时，匹配的两个括号中间区间的 `(` 能匹配数 $-1$。

要使剩余序列中未匹配的 `(` 能匹配数尽快为 $0$，就要让匹配的两个括号中间区间尽量大，才能使得未匹配的 `(` 能匹配数减少的快，所以每次使最前面的 `(` 尝试匹配 `)`，若能匹配，则继续，若无法匹配，说明当前序列中的 `(` 能匹配数都为 $0$，退出匹配。

若匹配括号数为 $0$，说明原序列不含「好子序列」，$k=0$。

否则，$k=1$，输出匹配括号数及编号。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll re(){
	ll x=0,y=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')y=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*y;
}
inline void wr(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) wr(x/10);
	putchar(x%10+48);
}
ll cnt1,cnt2;vector<ll>ans;
int main(){
	string s;
	cin>>s;bool frog=1;
	cnt1=0;cnt2=s.length()-1;
	while(cnt1<s.length()&&s[cnt1]==')')cnt1++;
	while(cnt2>=0&&s[cnt2]=='(')cnt2--;
	if(cnt2<cnt1){
		cout<<0;
		return 0;
	}
	cout<<"1\n";
	while(cnt1<cnt2){
		while(cnt1<s.length()&&s[cnt1]==')')cnt1++;
		while(cnt2>=0&&s[cnt2]=='(')cnt2--;
//		cout<<cnt1<<','<<cnt2<<'\n';
		if((cnt1>cnt2))break; 
		ans.push_back(cnt1),ans.push_back(cnt2);
		cnt1++,cnt2--;
	}
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<'\n';
	for(ll i:ans)cout<<i+1<<' ';
	return 0;
}
```

---

## 作者：Strelitzia (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/CF1305B)

-------------------

$\ \ \ \ \ $我认为这道题是带贪心的模拟。

$\ \ \ \ \ $想让这个序列变得没有简单序列。

$\ \ \ \ \ $所以是找一个点，使两边有一边的（删完，或）的删完。

$\ \ \ \ \ $一个重点——由上一句话，可以推出$k=1\ ||\ k==0$，我一开始没想到。

$\ \ \ \ \ $实现的方法不同。

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
template<typename T>void read(T &x) {
	x = 0;T f = 1;char s = getchar();
	while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - 48;s = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if(x < 0)putchar('-'),x = -x;
	if(x > 9)print(x / 10);
	putchar(x % 10 + '0');
}
char a[1005];
int ans[1005][1005],k;
int flag[1005];
int main() {
	scanf ("%s",a + 1);
	int len = strlen(a + 1);
	while (true) {
		int l = 1,r = len,tmp = 0;
		while (l < r) {
			int f1 = 0,f2 = 0;
			for (; l < r ; ++ l) {
				if (flag[l]) continue;
				if (a[l] == '(') {
					f1 = 1;
					flag[l] = 1;
					break;
				}
			}
			for (; r > l ; -- r) {
				if (flag[r]) continue;
				if (a[r] == ')') {
					f2 = 1;
					flag[r] = 1;
					break;
				}
			}
			if (f1 == 0 || f2 == 0) {
				break;
			}
			else {
				ans[k][++ ans[k][0]] = l;
				ans[k][++ ans[k][0]] = r;
			}
		}
		tmp = len;
		len = 0;
		for (int i = 1 ; i <= tmp ; ++ i) {
			if (flag[i] == 0) {
				a[++ len] = a[i];
			}
			flag[i] = 0;
		}
		if (ans[k][0] != 0) {
			k ++;
		}
		else {
			break;
		}
	}
	print(k);
	putchar('\n');
	for (int i = 0 ; i < k ; ++ i) {
		print(ans[i][0]),putchar('\n');
		sort(ans[i] + 1,ans[i] + 1 + ans[i][0]);
		for (int j = 1 ; j <= ans[i][0] ; ++ j) {
			print(ans[i][j]),putchar(' ');
		}
	}
	return 0;
}
```

$\ \ \ \ \ $谢谢♪(･ω･)ﾉ

---

## 作者：gyh20 (赞：0)

之前代码贴错了，修一下。

贪心，假设存在位置 $i,j,k(i<j<k$ 且 $a_i=\text (,a_j=\text ),a_k=\text )$，那么删去 $i,k$ 一定比删去 $i,j$ 更优，因为 $k$ 有可能和 $x(a_x=\text (,j<x<k  )$ 配对，因此删去 $i,k$ 一定更优。

所以，我们只需要从前往后搜索，找到第一个 $\text ($，然后从后往前搜索，找到第一个 $\text )$ 并删掉即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
int t,n,a[1002],cnt[1002],ans[1002][1002],num,lst;
char s[1002];
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	while(1){
		int l=1,r=n;++num;
		while(l<r){
			while(s[l]==')'||s[l]=='$')++l;
			while(s[r]=='('||s[r]=='$')--r;
			if(l<r){
				ans[num][++cnt[num]]=l;
				ans[num][++cnt[num]]=r;
				s[l]=s[r]='$';
				++l;
				--r;
			}
		}
		if(!cnt[num])break;
	}
	printf("%d\n",num-1);
	for(re int i=1;i<num;++i){
		printf("%d\n",cnt[i]);
		sort(ans[i]+1,ans[i]+cnt[i]+1);
		for(re int j=1;j<=cnt[i];++j){
			printf("%d ",ans[i][j]);
		}
		putchar('\n');
	}
}
```


---

