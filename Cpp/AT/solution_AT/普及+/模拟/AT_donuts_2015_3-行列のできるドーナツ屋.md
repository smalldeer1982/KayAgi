# 行列のできるドーナツ屋

## 题目描述

在甜甜圈小镇里，有一家每天都排长队的超人气甜甜圈店。现在有 $N$ 个人在这家甜甜圈店排队。排队的人担心在排到自己之前甜甜圈就会卖完。于是甜甜圈店的店长决定计算表示每个人不安程度的「不安度」。

设第 $i$ 个人的身高为 $H_i$，第 $i$ 个人的「不安度」即为「第 $i$ 个人向前看时看到的人数」。第 $i$ 个人向前看时看到第 $j$ 个人需要满足以下条件。

- 第 $j$ 个人需要排在第 $i$ 个人的前面，也即 $j<i$。
- 第 $i$ 个人与第 $j$ 个人之间没有人比第 $j$ 个人更高，也即不存在 $k$ 同时满足 $j<k<i$ 和 $H_j<H_k$。

例如，如果排队的人从前往后的身高分别为 $2,5,3,4,1$，那么排在最后的人向前看时可以看到排在第 $2$ 和第 $4$ 的两人，因此第 $5$ 个人的「不安度」就为 $2$。

## 说明/提示

对于 $10\%$ 的测试数据，满足 $N\leqslant100$；

对于 $40\%$ 的测试数据，满足 $N\leqslant5000$；

对于 $100\%$ 的测试数据，满足 $1\leqslant N\leqslant10^5$ 且 $1\leqslant H_i\leqslant10^6$。

## 样例 #1

### 输入

```
5
2 5 3 4 1```

### 输出

```
0
1
1
2
2```

## 样例 #2

### 输入

```
1
1000000```

### 输出

```
0```

## 样例 #3

### 输入

```
8
66 52 56 32 27 50 72 23```

### 输出

```
0
1
2
2
3
4
3
1```

# 题解

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_donuts_2015_3)

### 题目大意

有 $N$ 个人在排队，第 $i$ 个人的身高是 $H_i$，请求出第 $i$ 个人向前能看到多少个人（需满足依次越来越高）。

### 思路

考虑使用**单调栈**。用单调栈维护一个身高递减的序列，第 $i$ 个答案就是当前栈的长度。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=1e5+10;
int a[N];
stack<int>st;
int main(){
	int n=read();
	for(int i=1;i<=n;++i){
		a[i]=read();
		printf("%llu\n",st.size());
		while(!st.empty()&&st.top()<a[i])
			st.pop();
		st.push(a[i]);
	}
	return 0;
}
```

---

## 作者：osfly (赞：1)

根据题意，发现我们要维护一个身高递减的序列。

因此，我们可以直接使用单调栈维护第 $i$ 个人能看到的人数即可。

答案就是当前栈内的元素数量。

注意应先输出答案再将当前高度入栈。

```cpp
#include<cstdio>
int n;
int h[100010];
int st[100010];
int top;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&h[i]);
		printf("%d\n",top);
		while(top>0&&st[top]<h[i]) top--;
		st[++top]=h[i];
	}
	return 0;
}
```

---

## 作者：technopolis_2085 (赞：1)

### AT_donuts_2015_3 题解

算法：单调栈。

暴力：

很好做，二重循环枚举两个端点，然后用倍增表求出区间最小值，然后判断即可。可以拿到 $40$ 分。

正解：

考虑单调栈。

对于 $i$ 元素，我们需要找到第一个 $j$ 使得 $a_j$ 大于 $a_i$。明显可以用单调队列完成。

此时对于 $i$ 到 $j$ 之间的每一个元素，这个人的不安度就会加 $1$。

最后用前缀和和差分计算每个人的不安度，然后就做完了。

预计得分 $100$ 分。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+10;
int a[maxn];
int r[maxn];
int sum[maxn];

int main(){
	int n;
	scanf("%d",&n);
	
	for (int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	
	a[n+1]=1e9+7;
	
	stack<int> st;
	while (!st.empty()) st.pop();
	st.push(n+1);
	
	for (int i=n;i>=1;i--){
		while (!st.empty()&&a[i]>a[st.top()]) st.pop();
		
		r[i]=st.top();
		st.push(i);
	}	

	for (int i=1;i<=n;i++){
		sum[i+1]++;
		sum[r[i]+1]--;
	}
	
	for (int i=1;i<=n;i++){
		sum[i]+=sum[i-1];
		printf("%d\n",sum[i]);
	}
	return 0;
}
```


---

## 作者：Guizy (赞：1)

- ## 题目大意

我们需要对于每一个人，看他前面有多少个满足条件的人。如果直接暴力做，

时间复杂度是 $O(n^2)$，所以考虑单调栈。

- ## 单调栈

其实，单调栈就是一个栈（废话）。但是这个栈，是只有有用的东西的，没有

用的东西我们会把它清出去。具体是怎么用的呢？我们边看样例边分析。

- ## 理性分析

首先看到样例1。
```cpp
5
2 5 3 4 1
```
第一个人身高：$2$。没有在他前面的人，故答案为 $0$。此时栈中元素为：`2`。

第二个人身高：$5$。在他前面的只有第一个人，而第一个人身高比他矮，所以在后续的查找中，他一定不会满足条件。所以，这个人（元素）已经对答案没有用，我们就把他清出去。此时栈中元素为：`5`。答案为 $1$。

以此类推，在第三个人之后栈中元素为：`5 3`。答案为 $1$。
第四个人之后栈中元素为：`5 4`。答案为 $2$。
第五个人之后栈中元素为：`5 4`。答案为 $2$。

这时，我们发现，对于第 $i$ 个人，答案就是第 $i-1$ 个人查找完之后栈中的元素个数，而栈里要清出的元素，就是在查找第 $i$ 个人的时候在他前面比他矮的那些人（元素）。在遇到一个不比他矮的人的时候停止。

- ## 实现

直接来看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[100010];
stack<int>s;//STL实现

int main(){
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		printf("%d\n",s.size());
		while(!s.empty()&&s.top()<a[i]) s.pop();//清出无用元素
		s.push(a[i]);
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

阅读理解题。

考虑使用单调栈维护第 $i$ 个人能看到的人数，第 $i$ 个答案就是当前栈的长度，即 `sta.size ()`。

具体的：首先使用循环，输入 $a_i$。然后前面已经所过了，第 $i$ 个答案就是当前栈的长度，所以输出当前栈的长度。然后就是模板了。

### 代码实现

```cpp
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <bits/stdc++.h>

#define unmap unordered_map
#define unset unordered_set
#define muset multiset
#define ll long long
#define unint unsigned int
#define ull unsigned ll
#define please return
#define AC 0
#define il inline
#define cst const
#define db double
#define ld long db
#define pii pair<int,int>
#define pll pair<ll,ll>
#define str string

using namespace std;

cst ll INF = 9223372036854775807;
cst int inf = 2147483647;
cst int xinf = 0x3f3f3f3f;
cst ll XINF = 0x3f3f3f3f3f3f3f3fll;
cst db pi = acos (-1.0), eps = 1e-12;
cst int MAXN = 1e5 + 10;

#define rep(i, a, b) for (int i = a; i <= b; i++)
#define repr(i, a, b) for (int i = a; i >= b; i--)

// #define int long long

il int _abs(int a) { if (a < 0) return -a; return a; }
il int _pow(int a, int b) { int x = 1, y = a; while(b > 0) {if (b & 1) x *= y; y *= y; b >>= 1; } return x; }

int read () { int sum = 0, f = 1; char ch; ch = getchar (); while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar ();} while (ch >= '0' && ch <= '9') {  sum = sum * 10 + ch - '0'; ch = getchar ();} return sum * f;}

int a[MAXN];
stack <int> sta;

int main (void) {
	
	int n = read ();
	
	rep(i, 1, n) {
		
		a[i] = read ();
		cout << sta.size () << endl;
		
		while (!sta.empty () && sta.top () < a[i]) sta.pop ();
		sta.push (a[i]);
	}	 
	please AC;
}
```

---

## 作者：yyycj (赞：0)

## [题目传送门](https://atcoder.jp/contests/donuts-2015/tasks/donuts_2015_3)

## 题目简述
有 $n$ 个人排队，第 $1$ 个人排在最前面，他们的身高分别为 $H_{1} \sim H_{n}$。求对于每个 $i \in [1,n]$，第 $i$ 个人向前看能看到几个人，并且看到的人里面最前面的人的身高是看到的人里面最高的。

## 主要思路
采用单调栈的算法，本题与洛谷主题库 [P2866 [USACO06NOV] Bad Hair Day S](https://www.luogu.com.cn/problem/P2866) 几乎相同，只不过操作顺序反了过来，答案变成了依次输出。

单调栈的主要思想即在栈内保持一个单调的序列，在本题中每次输出的答案即栈内的元素数，因为在这一个序列中，不管当前人的身高多高，栈内的人他都能看见。最后不断弹掉栈顶直到空栈或栈顶的人的身高大于等于当前人的身高，保持序列的单调性。

由于 `stack` 与 `queue` 一样效率都不高，所以建议手写，并且本题中操作也只有 `push()` 与 `pop()` 两种操作。

### 时间复杂度
$O(n)$

## AC Code
```cpp
#include<cstdio>
#include<iostream>
using namespace std;

#ifdef ONLINE_JUDGE
#define getchar getchar_unlocked
#endif

#define endl '\n'
#define pc putchar
#define gc getchar
typedef long long ll;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
#define rep(i, a, b) for (int i = a; i <= b; i++)
#define repr(i, a, b) for (int i = a; i >= b; i--)
void print(int x) { if (x < 0) { pc('-'); x = -x; }if (x > 9) { print(x / 10); }pc(char(x % 10 + 48)); }
inline int read_int() { int f = 1, x = 0; char ch = gc(); while (!isdigit(ch)) { if (ch == '-')f = -1; ch = gc(); }while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = gc(); }return x * f; }
// ----------------------------

// ----------------------------
int st[N];
// ----------------------------


int main() {
	int n = read_int(); 
	// ----------------------------
	int h, top = 0;
	rep(i, 1, n) {
		h = read_int();
		print(int(top));
		pc('\n');
		while (top > 0 && st[top] < h) --top;
		st[++top] = h;
	}
	return 0;
}
/*
				 .-~~~~~~~~~-._       _.-~~~~~~~~~-.
			 __.'              ~.   .~              `.__
		   .'//   A    C    之   \./  之    真    理  \`.
		 .'//                     |                     \`.
	   .'// .-~"""""""~~~~-._     |     _,-~~~~"""""""~-. \`.
	 .'//.-"                 `-.  |  .-'                 "-.\`.
   .'//______.============-..   \ | /   ..-============.______\`.
 .'______________________________\|/______________________________`.
*/
```

## 后言
建议降黄，正文中提到的 P2866 也是黄。

---

## 作者：Brute_Force (赞：0)

### 题意
题面太复杂了，我们先简化一下题面：

有 $N$ 个人在排队，第 $i$ 个人的身高是 $H_i$，输出从前往后到第 $i$ 个人由高到低的有多少个人，即题面所说的「不安度」。

看到简化体面中的“越来越高”，就说明我们需要输出容器中从大到小的数列的长度。不难发现，容器是单调栈，接下来，只需要满足栈中数是从大到小的即可。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
stack <int> s;
int a[100005], n;
int main () {
	ios :: sync_with_stdio (0);
	cin.tie (0), cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		cout << s.size () << endl;
		while (s.size () && s.top () < a[i]) s.pop ();
		s.push (a[i]);
	}
	return 0;
}
```

---

## 作者：Rainbow_SYX (赞：0)

## 题意
有 $N$ 个人在排队，第 $i$ 个人的身高是 $H_i$，问第 $i$ 个人能看到前面几个人。
## 思路
考虑使用单调栈，原理就是每一次把 $H_i$ 加入栈中前，弹出栈中所有小于等于 $H_i$ 的元素（因为已经被 $H_i$ 挡住看不见了），这样的话，每一个人的「不安度」就是当前还未操作时栈的长度。
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
stack<int> st;
int n,a[100005];
signed main()
{
	cin.tie(0);ios::sync_with_stdio(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		cout<<st.size()<<"\n";
		while(!st.empty() && st.top()<a[i]) st.pop();
		st.push(a[i]);
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 前言：
竟然有如此水的绿题。

## 思路：

这是一道非常经典的单调栈问题。

我们可以发现题目要我们来维护一个身高递减的序列。

所以，我们可以直接使用单调栈维护第 $i$ 个人来看见所有的人数。

最后再输出 $sum$ 即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,sum;
const long long N=100010;
long long a[N],b[N];

int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(long long i=1;i<=n;i++)
	{
		cin >> a[i];
		cout << sum << endl;
		while(sum>0 && b[sum]<a[i])
		{
			sum--;
		}
		b[++sum]=a[i];
	}
	return 0;
}
``````

---

## 作者：cppcppcpp3 (赞：0)

[Link](https://atcoder.jp/contests/donuts-2015/tasks/donuts_2015_3)

考虑每个人对其身后的人的贡献，记 $r_i$ 为满足 $H_i=\max_{k=i}^j H_k$ 的最大的 $j$，则第 $i$ 个人对区间 $[i+1,r_i+1]$ 的人有 $1$ 的贡献，差分一下。$r_i$ 可以单调栈或悬线法求。$O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;

int n,a[N],r[N],d[N];

signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=n;i;--i){
		r[i]=i;
		while(r[i]<n && a[i]>=a[r[i]+1]) r[i]=r[r[i]+1];
		++d[i+1],--d[r[i]+2];
	}
	for(int i=1;i<=n;++i) printf("%d\n",d[i]+=d[i-1]);
	return 0;
}
```

---

## 作者：TankYu (赞：0)

比较套路。

令 $r_i$ 表示在第 $i$ 个人后第一个比他高的人的编号。

那么对于任意一个人 $i$，会对第 $i + 1$ 到第 $r_i$ 个人的不安度造成 $1$ 的贡献。原因是对于第 $j(j > r_i)$ 个人，他会被第 $r_i$ 个人挡住而看不到第 $i$ 个人。

注意如果第 $i$ 个人比后面的人都高，那么 $r_i = n$，他对他后面的人都造成贡献。

这个 $r_i$ 可以单调栈做，再做个差分求贡献即可。

时间复杂度 $O(n)$。

```cpp
#include <stack>
#include <iostream>
using namespace std;

int a[100010], r[100010], sum[100010];

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	stack <int> s;//单调栈
	for (int i = n; i >= 1; i--)
	{
		while (!s.empty() && a[s.top()] < a[i])
		{
			s.pop();
		}
		if (s.empty())//特判一下
		{
			r[i] = n;
		}
		else
		{
			r[i] = s.top();
		}
		s.push(i);
	}
	for (int i = 1; i <= n; i++)//差分，注意第i个人不会被贡献（他看不到自己）
	{
		sum[i + 1]++;
		sum[r[i] + 1]--;
	}
	for (int i = 1; i <= n; i++)
	{
		sum[i] += sum[i - 1];
	}
	for (int i = 1; i <= n; i++)
	{
		cout << sum[i] << '\n';
	}
	return 0;
}

```

---

