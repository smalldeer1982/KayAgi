# [ICPC 2014 WF] Baggage

## 题目描述

一家航空公司有两趟航班几乎同时从 ICPCity 出发，一趟飞往城市 B，另一趟飞往城市 A。航空公司有 $n$ 个柜台供乘客托运行李。每个柜台都有一对相同的行李箱，一个用于城市 B，一个用于城市 A。

就在航班起飞前，每对行李箱会被一辆电动推车移动到一个分拣区。推车总是一次移动两个箱子，一个用于城市 B，一个用于城市 A。所有箱子移动完后，它们在分拣区排成如下的顺序：

B A B A B A ... B A

也就是说，有 $2n$ 个行李箱排成一行，从一个城市 B 的箱子开始，然后是一个城市 A 的箱子，如此交替。现在的任务是重新排列它们，使得所有城市 A 的行李箱都排在城市 B 的行李箱之前。然后这些箱子可以被装载到相应的飞机上。

重新排列是通过移动相邻的一对行李箱（不一定是 B 然后是 A），同样通过电动推车进行。为了保持平衡，推车必须总是携带两个箱子，不能只携带一个。每对箱子必须移动到至少有两个箱子宽度的空位上。在第一个箱子的左边有一些空位，在重新排列过程中可以根据需要使用。

当重新排列过程开始时，箱子的位置从 $1$ 开始编号（最初包含最左边的 B 行李箱）到 $2n$（最初包含最右边的 A 行李箱）。在箱子的左边有 $2n$ 个初始空位，编号从 $0$ 到 $-2n+1$，如图 1 所示，$n=4$ 的情况。

![图 1](https://cdn.luogu.com.cn/upload/image_hosting/fwkcv2gq.png)

图 1：$n = 4$ 时箱子和空位的初始配置

给定 $n$，找出一个最短的移动序列，以便重新排列箱子，使得所有 A 箱子都在所有 B 箱子的左边。在过程结束时，最左边的 A 箇可能在位置 $1$ 之外的某个位置，但箱子必须在 $2n$ 个位置的序列中相邻。

## 说明/提示

时间限制：1000 毫秒，内存限制：1048576 KB。

国际大学生程序设计竞赛（ACM-ICPC）世界总决赛 2014。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
```

### 输出

```
8 to -1
3 to 8
6 to 3
0 to 6
9 to 0
```

## 样例 #2

### 输入

```
8
```

### 输出

```
10 to -1
3 to 10
14 to 3
7 to 14
0 to 7
11 to 0
4 to 11
15 to 4
```

# 题解

## 作者：win114514 (赞：14)

很有意思的构造题。

### 思路

首先考虑最小步数。

由于最终要达到的状态相邻部分相同的对数需要为 $2\times n-2$。

我们的操作中，第一次操作最多产生 $1$ 对相同，其余操作最多产生 $2$ 对相同。

所以我们有了最小步数的下界 $n$。

考虑能否达到这个最小步数。

考虑状态：

$$
\color{black}OOBABABABABABABABABABABABA
$$

一个较长的序列，$O$ 代表空位，$A$ 代表一，$B$ 代表二。

考虑构造：

$$
\color{red}AB\color{black}BABABABABABABABABABAB\color{blue}OO\color{black}A
$$

$$
\color{black}ABBA\color{blue}OO\color{black}BABABABABABABABAB\color{red}BA\color{black}A
$$

发现了什么。

$$
\color{black}ABBA\color{red}OOBABABABABABABABA\color{black}BBAA
$$

红色段变成了一个相同的子问题，$n\rightarrow n-4$。

假如我们把红色段排好序之后。

$$
\color{black}ABBA\color{red}AAAAAAAABBBBBBBBOO\color{black}BBAA
$$

很容易继续构造。

$$
\color{black}A\color{blue}OO\color{black}AAAAAAAAABBBBBBBB\color{red}BB\color{black}BBAA
$$

$$
\color{black}A\color{red}AA\color{black}AAAAAAAAABBBBBBBBBBBB\color{blue}OO
$$

这样就做到了在四步的操作下将 $n\rightarrow n-4$。

由于 $n=1,2$ 无法操作且 $n=3$ 无法再仅空两格的情况下复原。

所以我们只在 $n\ge 8$ 的情况下递归求解。

至于 $n<8$ 的情况可以直接暴搜求解。

### Code

由于 $n=7$ 跑的不是很快（几百毫秒），所以追求速度也可以打表（不打表也能过）。

```cpp
#include <cstdio>
#include <vector>
using namespace std;

const int N = 5010;

int *a, d[N << 1];
vector<pair<int, int>> res;
vector<pair<int, int>> ans;

inline bool dfs(int l, int r, int k) {
	// if (k == 7) {
	// 	res.emplace_back(l + 9, l);
	// 	res.emplace_back(l + 6, l + 9);
	// 	res.emplace_back(l + 13, l + 6);
	// 	res.emplace_back(l + 4, l + 13);
	// 	res.emplace_back(l + 10, l + 4);
	// 	res.emplace_back(l + 1, l + 10);
	// 	res.emplace_back(l + 14, l + 1);
	// 	return 1;
	// }
	int x = l + k, y = l + k + k, flag = 1;
	for (int i = l; i < x && flag; i++) if (a[i] != 1) flag = 0;
	for (int i = x; i < y && flag; i++) if (a[i] != 2) flag = 0;
	if (flag == 1) return 1;
	if (res.size() == k) return 0;
	vector<int> id;
	for (int i = l; i <= r; i++) {
		if (a[i] == 0 && a[i + 1] == 0) {
			id.emplace_back(i);
		}
	}
	for (int i = l; i <= r; i++) {
		if (a[i] != 0 && a[i + 1] != 0) {
			for (auto j : id) {
				swap(a[i], a[j]), swap(a[i + 1], a[j + 1]);
				res.emplace_back(i, j);
				if (dfs(l, r, k)) return 1;
				res.pop_back();
				swap(a[i], a[j]), swap(a[i + 1], a[j + 1]);
			}
		}
	}
	return 0;
}
inline void get(int x, int y) { ans.emplace_back(x, y); }
inline void sol(int l, int r) {
	if (r - l + 1 >= 16) {
		get(r - 2, l - 2), get(l + 2, r - 2);
		sol(l + 4, r - 4);
		get(l - 1, r - 5), get(r - 1, l - 1);
	} else {
		a[l - 2] = a[l - 1] = 0, res.clear();
		for (int i = l; i <= r; i++) a[i] = (i & 1 ? 2 : 1);
		if ((r - l + 1) / 2 != 3) dfs(l - 2, r, (r - l + 1) / 2);
		if ((r - l + 1) / 2 == 3) dfs(l - 4, r, (r - l + 1) / 2);
		for (auto i : res) get(i.first, i.second);
	}
}

int main() {
	int n;
	scanf("%d", &n), a = d + N, sol(1, n * 2);
	for (auto i : ans) {
		printf("%d to %d\n", i.first, i.second);
	}
	return 0;
}
```

---

## 作者：Varuxn (赞：13)

>[推销](https://www.cnblogs.com/Varuxn/p/15089787.html)

# 解题思路
非常好的一道**构造**题。

在手动模拟几个样例（也许不止几个）之后呢。

就可以发现其实这些操作的开始以及最后几步是有相通之处的。

关于手动模拟的样例放在了文章末尾，需要的自取。

先考虑操作次数。

尝试探索答案的下界，设 x 为序列中相邻的相同元素对数。

那么初始为 $x=0$，而最终 $x=2(n-1)$.

且除了第一次操作每次操作最多可以使 x 加 2。

那么答案下界就是 n。

然后，通过手动模拟的样例可以发现：

除了三操作之外的所有操作，其实都可以通过递归从以前的状态转移过来。

![](https://cdn.luogu.com.cn/upload/image_hosting/l4m2f7zk.png)

接下来就是边界，我们发现其实每一次的递归都会把序列的长度缩小 8 。

因此，边界就是 $\bmod\;8$ 之后的 4 种余数。

由于 3 的转移是不规则的，因此我们要将此种边界调整到 7。
# 其它

洛谷的评测机好像并不会告诉你这道题出错的地方。

我们可以自己写一个 Special_Judge 。

将 n 的大小以及自己的程序输出，放进去，看看最后的序列是否符合要求。

当然我也写了一份，放在后面

# code
## AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define f() cout<<"Pass"<<endl
using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')	f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
const int N=110;
int n;
void print(int x,int y)	{printf("%lld to %lld\n",x,y);}
void Judge(int l)
{
	print(l+1,l-2);
	print(l+4,l+1);
	print(l+2,l-4);
}
void solve(int l,int r)
{
	if(r-l+1<=2)	return ;
	if(r-l+1==10)
	{
		print(r-2,l-2);
		print(l+2,r-2);
		print(r-4,l+2);
		print(l-1,r-4);
		print(r-1,l-1);
		return ;
	}
	if(r-l+1==12)
	{
		print(r-2,l-2);
		print(r-5,r-2);
		print(l+1,r-5);
		print(r-6,l+1);
		print(l-1,r-6);
		print(r-1,l-1);
		return ;
	}
	if(r-l+1==14)
	{
		print(l+7,l-2);
		print(l+4,l+7);
		print(l+11,l+4);
		print(l+2,l+11);
		print(l+8,l+2);
		print(l-1,l+8);
		print(l+12,l-1);
		return ;
	}
	print(r-2,l-2);
	print(l+2,r-2);
	solve(l+4,r-4);
	print(l-1,r-5);
	print(r-1,l-1);
}
signed main()
{
	n=read();
	if(n==3)	Judge(1);
	else	solve(1,2*n);
	return 0;
}
```
## Special_Judge
```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define f() cout<<"Pass"<<endl
using namespace std;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0')
	{
		if(ch=='-')	f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int n;
char ch[500];
void move(int y,int x)
{
	ch[x]=ch[y];
	ch[x+1]=ch[y+1];
	ch[y+1]=ch[y]='_';
}
void print()
{
	for(int j=2*n-1;j<=4*n;j++)
		cout<<ch[j];
	cout<<'\n';
}
signed main()
{
	n=read();
	fill(ch+1,ch+4*n+1,'_');
	for(int i=2*n+1;i<=4*n;i++)
		if(i&1)	ch[i]='B';
		else	ch[i]='A';
	for(int i=1,l,r;i<=n;i++)
	{
		l=read();
		r=read();
		print();
		move(l+2*n,r+2*n);
	}
	print();
	return 0;
}
```
# 样例
* n=3 
```cpp
__BABABA
ABB__ABA
ABBBAA__
ABBB____
```
* n=4
```cpp
__BABABABA
ABBABAB__A
ABBA__BBAA
A__ABBBBAA
AAAABBBB__
```
* n=5
```cpp
__BABABABABA
ABBABABAB__A
ABBA__BABBAA
ABBAABB__BAA
A__AABBBBBAA
AAAAABBBBB__
```
* n=6
```cpp
__BABABABABABA
ABBABABABAB__A
ABBABABA__BBAA
ABB__ABAABBBAA
ABBAAAB__BBBAA
A__AAABBBBBBAA
AAAAAABBBBBB__
```
* n=7
```cpp
__BABABABABABABA
ABBABABAB__ABABA
ABBABA__BBAABABA
ABBABAABBBAAB__A
ABBA__ABBBAABBAA
ABBAAAABBB__BBAA
A__AAAABBBBBBBAA
AAAAAAABBBBBBB__
```

---

## 作者：xxgirlxx (赞：6)

## 题外话

这题我之前看见过，但没做。后来同学去打 NOI 模拟赛的 T3 是这道题，他叫我帮他做一下（~~我也不知道为什么找我，可能是我平时构造做多了~~），我肝了一整天，终于过了。

结果他跟我说：“我不要啦！”

我：“······”

对了，快膜拜这位初一跟着初三打模拟赛的[大佬](https://www.luogu.com.cn/user/726525)。

## 题目思路

首先，你得先明白：这是一道**构造**题。

既然是**构造**，那么肯定要找每个方案之间的规律。

对于这道题，我想到一句俗语，很符合这题的解题思路：“大事化小，小事化了。”

首先我们先处理好**最小化**，~~因为经过多个样例的模拟，我们可以大胆猜测~~，因为我们最后会有 $2 \times n -2$ 个 $1$ 或 $2$ 相匹配，算上中间的 $1$ 和 $2$ 的相连部分就是 $2 \times n -1$ 个部分，第一次操作最多满足一个部分（前面**或**后面），之后的操作最多满足两个部分（前面**和**后面），算下来刚好 $n$ 步，枚举几个样例发现没问题，便可确定最小步数是 $n$。

然后考虑**大事化小**，也就是将一个大问题化成一个小问题。

多枚举几个样例并结合上面关于最小化的推断便可以发现一个很明显的规律：

```cpp
..BA|BABA···BABA|BABA
ABBA|BABA···BABA|B..A
ABBA|..BA···BABA|BBAA
···
ABBA|AAAA···BB..|BBAA
A..A|AAAA···BBBB|BBAA
AAAA|AAAA···BBBB|BB..
```

可以发现，这个规律可以用 $4$ 步处理 $4$ 个对子，符合我们 $n$ 步解决所有部分的期望，所以我们选择使用这种办法。

再考虑**小事化了**，因为 $4$ 步处理 $4$ 个对子后会剩下 $0,1,2,3$ 个对子，我们需要特殊考虑。但是因为剩下 $1,2$ 个对子不可做（不然 $n$ 为什么最小只有 $3$），而 $3$ 的交换过程又会跳出我们规定的最多向前跳 $1$ 个对子的距离的限制（它要向前跳 $2$ 个对子的距离，因此我们要**对 $3$ 进行特判**）。

那怎么办呢？我们发现 $3$ 之后的 $4,5,6,7$ 都是正常的解法，而且对 $4$ 的余数也是 $0,1,2,3$，于是我们尝试将最后的解决放到 $4,5,6,7$ 中来，这样我们就只需要在剩下的对子数等于 $4,5,6,7$ 时输出它们的解法就好了。

最后建议大家在枚举小样例的时候可以编一个代码来实时模拟，我写了一份，会放在代码后面，但是注意：**它不会自动结束！**。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
void dfs(int l,int r){
	if((r-l+1)/2==4)cout<<l+5<<" to "<<l-2<<"\n"<<l+2<<" to "<<l+5<<"\n"<<l-1<<" to "<<l+2<<"\n"<<l+6<<" to "<<l-1<<"\n";
	else if((r-l+1)/2==5)cout<<l+7<<" to "<<l-2<<"\n"<<l+2<<" to "<<l+7<<"\n"<<l+5<<" to "<<l+2<<"\n"<<l-1<<" to "<<l+5<<"\n"<<l+8<<" to "<<l-1<<"\n";
	else if((r-l+1)/2==6)cout<<l+9<<" to "<<l-2<<"\n"<<l+6<<" to "<<l+9<<"\n"<<l+1<<" to "<<l+6<<"\n"<<l+5<<" to "<<l+1<<"\n"<<l-1<<" to "<<l+5<<"\n"<<l+10<<" to "<<l-1<<"\n";
	else if((r-l+1)/2==7)cout<<l+7<<" to "<<l-2<<"\n"<<l+4<<" to "<<l+7<<"\n"<<l+11<<" to "<<l+4<<"\n"<<l+2<<" to "<<l+11<<"\n"<<l+8<<" to "<<l+2<<"\n"<<l-1<<" to "<<l+8<<"\n"<<l+12<<" to "<<l-1<<"\n";
	else cout<<r-2<<" to "<<l-2<<"\n"<<l+2<<" to "<<r-2<<"\n",dfs(l+4,r-4),cout<<l-1<<" to "<<r-5<<"\n"<<r-1<<" to "<<l-1<<"\n";
	return;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	if(n==3){cout<<"2 to -1\n5 to 2\n3 to -3\n";return 0;}
	else dfs(1,n*2);
	return 0;
}
```

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100000],x,y,z;
int main(){
	cin>>n,n*=2;
	for(int i=n+2;i<=n*2+1;i++)a[i]=(i+1)%2+1;
	while(1){
		for(int i=1;i<=n*2+1;i++){
			if(a[i]==2)cout<<"B";
			else if(a[i]==1)cout<<"A";
			else cout<<".";
		}
		cout<<"\n";
		cin>>x>>y;
		x+=n+1,y+=n+1;
		if(x<0-n*2-1||y<0-n*2-1||x==n*2+1||y==n*2+1)cout<<"超出边界！\n";
		else if(a[x]==0||a[x+1]==0||a[y]!=0||a[y+1]!=0)cout<<a[x]<<" "<<a[x+1]<<" "<<a[y]<<" "<<a[y+1]<<"交换不符合条件！\n";
		else z=a[x],a[x]=a[y],a[y]=z,z=a[x+1],a[x+1]=a[y+1],a[y+1]=z;
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：6)

感觉这题递归的思想挺值得借鉴的。

特判 $n = 3$。

首先根据样例不难猜测最小次数为 $n$。事实上最小次数下界为 $n$，因为设 $x$ 为当前相邻元素相同对数，不难发现除第一次操作外 $x$ 最多增加 $2$，而终态中 $x = 2n - 2$。我们尝试构造能达到下界的方案。

手玩几组数据发现，有一个看起来很通用的解法，使得只左移两位。例如 $n = 8$（`O` 代表空位）：

`OOBABABABABABABABA`

此时我们把最右边的 `AB` 移到左边去：

`ABBABABABABABABOOA`

然后把不是左端点的最左侧的 `BA` 移到右边去：

`ABBAOOBABABABABBAA`

此时中间的 `BABABABA` 恰好转化为 $n' = n - 4 = 4$ 的子问题，并且能在只左移两位的前提下排好序：

`ABBAAAAABBBBOOBBAA`

我们把左边的 `BB` 移到右边去，再把右边的 `AA` 移到左边去：

`AAAAAAAABBBBBBBBOO`

做完了！

事实上这个可以推广到任意 $n \ge 8$ 的情况。$n < 8$ 时我们手玩或者暴搜求出方案，然后打表即可。

```cpp
// Problem: P6892 [ICPC2014 WF] Baggage
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6892
// Memory Limit: 1 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair<int, int> pii;

vector<pii> ans;

void dfs(int l, int r) {
	if (r - l + 1 == 6) {
		ans.pb(l + 1, l - 2);
		ans.pb(l + 4, l + 1);
		ans.pb(l + 2, l - 4);
		return;
	}
	if (r - l + 1 == 8) {
		ans.pb(l + 5, l - 2);
		ans.pb(l + 2, l + 5);
		ans.pb(l - 1, l + 2);
		ans.pb(l + 6, l - 1);
		return;
	}
	if (r - l + 1 == 10) {
		ans.pb(l + 7, l - 2);
		ans.pb(l + 2, l + 7);
		ans.pb(l + 5, l + 2);
		ans.pb(l - 1, l + 5);
		ans.pb(l + 8, l - 1);
		return;
	}
	if (r - l + 1 == 12) {
		ans.pb(l + 9, l - 2);
		ans.pb(l + 6, l + 9);
		ans.pb(l + 1, l + 6);
		ans.pb(l + 5, l + 1);
		ans.pb(l - 1, l + 5);
		ans.pb(l + 10, l - 1);
		return;
	}
	if (r - l + 1 == 14) {
		ans.pb(l + 7, l - 2);
		ans.pb(l + 4, l + 7);
		ans.pb(l + 11, l + 4);
		ans.pb(l + 2, l + 11);
		ans.pb(l + 8, l + 2);
		ans.pb(l - 1, l + 8);
		ans.pb(l + 12, l - 1);
		return;
	}
	ans.pb(r - 2, l - 2);
	ans.pb(l + 2, r - 2);
	dfs(l + 4, r - 4);
	ans.pb(l - 1, r - 5);
	ans.pb(r - 1, l - 1);
}

void solve() {
	int n;
	scanf("%d", &n);
	dfs(1, n * 2);
	for (pii p : ans) {
		printf("%d to %d\n", p.fst, p.scd);
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```

打表代码：

```cpp
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef pair<int, int> pii;

int n, a[110];
vector<pii> ans;

void dfs(int d) {
	if (d > n / 2) {
		bool flag = 1;
		for (int i = 0; i < n / 2; ++i) {
			flag &= (a[i] == 1);
		}
		for (int i = n / 2; i < n; ++i) {
			flag &= (a[i] == 2);
		}
		if (flag) {
			for (pii p : ans) {
				printf("%d to %d\n", p.fst - 1, p.scd - 1);
			}
		}
		return;
	}
	int x = -1;
	for (int i = 0; i <= n; ++i) {
		if (!a[i] && !a[i + 1]) {
			x = i;
			break;
		}
	}
	for (int i = 0; i <= n; ++i) {
		if (a[i] && a[i + 1]) {
			ans.pb(i, x);
			swap(a[i], a[x]);
			swap(a[i + 1], a[x + 1]);
			dfs(d + 1);
			ans.pop_back();
			swap(a[i], a[x]);
			swap(a[i + 1], a[x + 1]);
		}
	}
}

void solve() {
	scanf("%d", &n);
	n <<= 1;
	for (int i = 2; i <= n + 1; ++i) {
		a[i] = ((i & 1) ? 1 : 2);
	}
	dfs(1);
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
```


---

## 作者：FangZeLi (赞：4)

## Link

[P6892 [ICPC2014 WF]Baggage](https://www.luogu.com.cn/problem/P6892)

## Solution

~~算是瞄了眼提示做出来的吧~~

大概思路就是考虑将一个规模为 $n$ 的问题不断地转化为规模为 $n-4$ 的问题，然后准备分别准备好  $n=3$，$4$，$5$，$6$ 时的表，递归搞一搞就可以了。

具体点，比如你有一个这样的东西（$n=8$）：

```
l              r
2121212121212121
```

那么你先转化一下，具体过程是 $r-2\to l-2$，$l+2\to r-2$：

```
  l   l'     r'  r
122100212121212211
```

然后从 $l'$ 到 $r'$ 的部分就是一个 $n-4$ 的问题，注意到我们可以将其在左移 $2$ 位的前提下解决，像这样：

```
  l   l'     r'  r
122111112222002211
```

然后就是解决边角，具体过程是 $l-1\to r-5$，$r-1\to l-1$：

```
100111112222222211
111111112222222200
```

然后就做完了。

$4$ 张表：

```
4321012345(位置)
0000212121
0012200121
0012221100
1112220000
```

```
2101234567(位置)
0021212121
1221212001
1221002211
1001222211
1111222200
```

```
210123456789(位置)
002121212121
122121212001
122100212211
122112200211
100112222211
111112222200
```

```
210123456789AB(位置)
00212121212121
12212121212001
12212121002211
12200121122211
12211120022211
10011122222211
11111122222200
```

```
210123456789ABCD(位置)
0021212121212121
1221212120012121
1221210022112121
1221211222112001
1221001222112211
1221111222002211
1001111222222211
1111111222222200
```

啥，你问我怎么搞出这几张表？

手玩下样例，大概就能找到规律了。

## Code

```cpp
#include <cstdio>
#include <algorithm>

#define _N 110

int n;

void inline excg(int x, int y) {
	printf("%d to %d\n", x, y);
}

void inline mov3(int pt) {
	excg(pt + 1, pt - 2);
	excg(pt + 4, pt + 1);
	excg(pt + 2, pt - 4);
}
void inline mov4(int pt) {
	excg(pt + 5, pt - 2);
	excg(pt + 2, pt + 5);
	excg(pt - 1, pt + 2);
	excg(pt + 6, pt - 1);
}
void inline mov5(int pt) {
	excg(pt + 7, pt - 2);
	excg(pt + 2, pt + 7);
	excg(pt + 5, pt + 2);
	excg(pt - 1, pt + 5);
	excg(pt + 8, pt - 1);
}
void inline mov6(int pt) {
	excg(pt + 9, pt - 2);
	excg(pt + 6, pt + 9);
	excg(pt + 1, pt + 6);
	excg(pt + 5, pt + 1);
	excg(pt - 1, pt + 5);
	excg(pt + 10, pt - 1);
}
void inline mov7(int pt) {
	excg(pt + 7, pt - 2);
	excg(pt + 4, pt + 7);
	excg(pt + 11, pt + 4);
	excg(pt + 2, pt + 11);
	excg(pt + 8, pt + 2);
	excg(pt - 1, pt + 8);
	excg(pt + 12, pt - 1);
}

void calc(int l, int r) {
	int len = r - l + 1;
	if (len <= 14) {
		switch (len) {
			case 6:
				mov3(l);
				break;
			case 8:
				mov4(l);
				break;
			case 10:
				mov5(l);
				break;
			case 12:
				mov6(l);
				break;
			case 14:
				mov7(l);
				break;
		}
		return;
	}
	excg(r - 2, l - 2);
	excg(l + 2, r - 2);
	calc(l + 4, r - 4);
	excg(l - 1, r - 5);
	excg(r - 1, l - 1);
}

int main() {
	scanf("%d", &n);
	calc(1, n << 1);
	return 0;
}
```

## Inspiration

我认为这题看出递归之后的分析并不难，关键就是问题向小规模的一个转化，这个在这道题中并没有那么显然，要能准确的找到突破口还是没那么容易的。

核心结论：

- 可以递归处理
- 长 $2n$ 的序列只需要 $n$ 次操作（在寻找小情况的解时这个信念很有用）

---

## 作者：BlackPanda (赞：3)

构造题。

首先我们知道达到终态需要满足相邻元素相同的对数为 $2\times(n-1)$，初态为 $0$ 对，操作过程中除第一次操作外（$1$ 对）其余每次最多产生 $2$ 对，所以答案的下界为 $n$。考虑如何构造达到下界的方案。

先手模样例，以 $n=8$ 为例，按如下步骤置换：
$$
\texttt{\textcolor{blue}{\_\_}BABABABABABABABA}\\
\texttt{\textcolor{red}{AB}BABABABABABAB\textcolor{blue}{\_\_}A}\\
\texttt{ABBA\textcolor{blue}{\_\_}BABABABAB\textcolor{red}{BA}A}\\
$$
此时，中间的 $\texttt{\textcolor{blue}{\_\_}BABABABA}$ 变成了一个类似的子问题，长度为 $n-4$。我们继续往下递归，直到中间部分有序：
$$
\texttt{ABBA\textcolor{red}{AAAABBBB}\textcolor{blue}{\_\_}BBAA}
$$
继续构造。
$$
\texttt{A\textcolor{blue}{\_\_}AAAAABBBB\textcolor{red}{BB}BBAA}\\
\texttt{A\textcolor{red}{AA}AAAAABBBBBBBB\textcolor{blue}{\_\_}}\\
$$
可以从上例中发现一个更为通用的解法：
$$
\texttt{\_\_BA|BA...BA|BABA}\\
\texttt{\textcolor{red}{AB}BA|BA...BA|B\textcolor{blue}{\_\_}A}\\
\texttt{ABBA|\textcolor{blue}{\_\_}...BA|B\textcolor{red}{BA}A}\\
...\\
\texttt{ABBA|AAAA...BB\textcolor{blue}{\_\_}|BBAA}\\
\texttt{A\textcolor{blue}{\_\_}A|AAAA...BB\textcolor{red}{BB}|BBAA}\\
\texttt{A\textcolor{red}{AA}A|AAAA...BBBB|BB\textcolor{blue}{\_\_}}\\
$$
考虑 $n=3$ 的情况，模拟可以发现，我们无法在左侧拓展 $2$ 格的条件下完成转移，特判一下即可。

初始时有 $2n$ 个位置，我们每次递归需要隔离出 $8$ 个位置，我们要保证下一次递归序列有效需满足 $2n-8\ge8,n\ge8$。如果 $n \in [3,7]$，则 $n-4\le3$ 方案对此序列无效。所以对于 $n\ge 8$ 的序列进行递归操作，$3\le n \le 7$ 的序列直接打表输出方案即可。
```cpp
void work(int l, int r) {
    if (r - l + 1 == 8) {
        cout << r - 2 << " to " << l - 2 << endl;
        cout << l + 2 << " to " << r - 2 << endl;
        cout << l - 1 << " to " << l + 2 << endl;
        cout << r - 1 << " to " << l - 1 << endl;
    } else if (r - l + 1 == 10) {
        cout << r - 2 << " to " << l - 2 << endl;
        cout << l + 2 << " to " << r - 2 << endl;
        cout << r - 4 << " to " << l + 2 << endl;
        cout << l - 1 << " to " << r - 4 << endl;
        cout << r - 1 << " to " << l - 1 << endl;
    } else if (r - l + 1 == 12) {
        cout << r - 2 << " to " << l - 2 << endl;
        cout << r - 5 << " to " << r - 2 << endl;
        cout << l + 1 << " to " << r - 5 << endl;
        cout << r - 6 << " to " << l + 1 << endl;
        cout << l - 1 << " to " << r - 6 << endl;
        cout << r - 1 << " to " << l - 1 << endl;
    } else if (r - l + 1 == 14) {
        cout << l + 7 << " to " << l - 2 << endl;
        cout << l + 4 << " to " << l + 7 << endl;
        cout << r - 2 << " to " << l + 4 << endl;
        cout << l + 2 << " to " << r - 2 << endl;
        cout << r - 5 << " to " << l + 2 << endl;
        cout << l - 1 << " to " << r - 5 << endl;
        cout << r - 1 << " to " << l - 1 << endl;
    } else {
        cout << r - 2 << " to " << l - 2 << endl;
        cout << l + 2 << " to " << r - 2 << endl;
        work(l + 4, r - 4);
        cout << l - 1 << " to " << r - 5 << endl;
        cout << r - 1 << " to " << l - 1 << endl;
    }
    return;
}
/*====================*/
void Solve() {
    cin >> n;
    if (n == 3) {
        cout << "2 to -1\n" << "5 to 2\n" << "3 to -3\n";
    } else {
        work(1, 2 * n);
    }
    return;
}
```

---

## 作者：FutaRimeWoawaSete (赞：2)

2014 ACM ICPC World Finals A baggage。

~~为什么都看过题解还做了这么久啊（~~

一个重要的想法是证明答案的下界是不低于 $n$ 的。

我们发现如果想要构造合法序列那么前后相同的链接数量为 $2n - 1$，一次操作只能造成最多两个合法链接，所以下界操作次数可以证明不低于 $\lceil \frac{2n - 1}{2}\rceil = n$。

对于 $n \leq 7$ 的答案通过爆搜发现最小的操作次数都是 $n$，推测 $n \geq 8$ 的答案也是 $n$。

发现存在这样一种构造方案，设 $L$ 为 $1$，$R$ 为 $2n$：

```cpp
move(R - 2 , L - 2) , move(L + 2 , R - 2);
```
那么中间的节点就会变为一个 $n - 4$ 规模的问题，递归处理；
结束后再进行一次
```cpp
move(L - 1 , R - 5) , move(R - 1 , L - 1);
```
即可解决原问题，因为样例就是这么构造的所以这里的思维难度其实还好（（（（（（

所以有谁教我怎么写比较块的搜索吗。

```cpp
/*
考虑一个问题的归约。
由于 n >= 3，我们先来看一下 n >= 3 的答案。
搞了 30min。。。 
等一下，也就是说我还要把 n <= 4 的情况全部打出来表。。。 
*/
#include "bits/stdc++.h"
using namespace std;
#define ll long long
const int Len = 405;
int n,m;
struct Node
{
	int x,y;
	Node(){x = y = 0;}
	Node(int X,int Y){x = X , y = Y;}
};
vector<Node> Psy[15];
inline void pt(int x,int y){printf("%d to %d\n",x,y);}
void work(int N,int ad)
{	
	int L = ad + 1 , R = ad + 2 * N;//[1,2n]
	if(N <= 7) 
	{
		if(N <= 4) for(int i = 0 ; i < Psy[N].size() ; i ++) printf("%d to %d\n",Psy[N][i].x + ad,Psy[N][i].y + ad);
		else
		{	
			if(N == 5) 
			{
            	pt(R - 2 , L - 2);
            	pt(L + 2 , R - 2);
            	pt(R - 4 , L + 2);
            	pt(L - 1 , R - 4);
            	pt(R - 1 , L - 1);
        	}
        	if(N == 6) 
			{
            	pt(R - 2 , L - 2);
            	pt(R - 5 , R - 2);
            	pt(L + 1 , R - 5);
            	pt(R - 6 , L + 1);
            	pt(L - 1 , R - 6);
            	pt(R - 1 , L - 1);
        	}
        	if(N == 7) 
			{
            	pt(R - 6 , L - 2);
            	pt(L + 4 , R - 6);
            	pt(R - 2 , L + 4);
            	pt(L + 2 , R - 2);
            	pt(R - 5 , L + 2);
            	pt(L - 1 , R - 5);
            	pt(R - 1 , L - 1);
        	}
		}
		return;
	}
	else
	{
		pt(R - 2 , L - 2) , pt(L + 2 , R - 2);
		work(N - 4 , ad + 4);
		pt(L - 1 , R - 5) , pt(R - 1 , L - 1);
	}
}
map<ll,ll> dp,pre[3];//B:1,A:2
int now[Len];
bool check()
{
	for(int i = 1 ; i <= 4 * n ; i ++) 
	{
		if(now[i] == 0) continue;
		if(now[i])
		{
			for(int j = i ; j <= i + n - 1 ; j ++) if(now[j] != 2) return 0;
			for(int j = i + n ; j <= i + 2 * n - 1 ; j ++) if(now[j] != 1) return 0;
 		}
 		return 1;
	}
	return 0;
}ll bg;
inline ll ds(){ll res = 0,ml = 1;for(int i = 1 ; i <= (n * 4) ; i ++) res += ml * now[i] , ml *= 3;return res;}
inline void rec(ll ml){for(int i = 1 ; i <= (4 * n) ; i ++) now[i] = ml % 3 , ml /= 3;}
inline void bk(ll Now){if(!dp[Now] && Now != bg) dp[Now] = 114;}
inline void Out(){for(int i = 1 ; i <= (4 * n) ; i ++) printf("%d ",now[i]);puts("");}
bool flaw;
void dfs(int as)
{
	if(flaw) return;
	if(as >= 6) return;
	ll Now = ds();bk(Now);
	if(as > dp[Now]) return;
	dp[Now] = as;
	//if(as == 3){printf("%d %lld\n",as,Now);Out();}
	if(check()) 
	{
		if(as == 5) flaw = 1;
		return;
	}
	for(int i = 1 ; i < (4 * n) ; i ++) 
	{
		if(now[i] && now[i + 1]) 
		{
			for(int j = 1 ; j < (4 * n) ; j ++)
			{
				if(!now[j] && !now[j + 1]) 
				{
					int a = now[i] , b = now[i + 1];
					now[i] = now[i + 1] = 0;
					now[j] = a , now[j + 1] = b;
					ll to = ds();bk(to);
					if(dp[to] > as + 1) 
					{
						pre[0][to] = Now , pre[1][to] = i - 2 * n , pre[2][to] = j - 2 * n;
						dfs(as + 1);
					}
					now[j] = 0 , now[j + 1] = 0;
					now[i] = a , now[i + 1] = b;
				}
			}
		}
	}
}

void Output(ll rec)
{
	if(rec == bg) return;
	Output(pre[0][rec]);
	printf("Psy[5].push_back(Node(%lld, %lld));\n",pre[1][rec],pre[2][rec]); 
}
int main()
{
	/*n = 5;int op = 1;
	for(int i = 2 * n + 1 ; i <= 4 * n ; i ++) now[i] = op , op = 3 - op;
	bg = ds();
	dfs(0);	
	const int LEN = 2 * n;ll as = 114,ass = 0;
	for(int i = 2 * n ; i <= 4 * n ; i ++)
	{
		ll rs = 0;int l = i - LEN + 1;ll ml = 1;
		for(int j = 1 ; j < l ; j ++) ml *= 3;
		for(int j = l ; j <= l + n - 1 ; j ++) 
		{
			rs += 2 * ml;
			ml *= 3;
		}
		for(int j = l + n ; j <= l + LEN - 1 ; j ++) rs += ml , ml *= 3;
		if(dp[rs] && dp[rs] < as) as = dp[rs] ,  ass = rs;
	}
	if(ass) Output(ass);*/
	Psy[3].push_back(Node(2, -1));
	Psy[3].push_back(Node(5, 2));
	Psy[3].push_back(Node(3, -3));
	Psy[4].push_back(Node(6, -1));
	Psy[4].push_back(Node(3, 6));
	Psy[4].push_back(Node(0, 3));
	Psy[4].push_back(Node(7, 0));
	scanf("%d",&n);work(n , 0);
	
	return 0;
}
```

---

## 作者：CommandSR (赞：0)

## 题意

[link](https://www.luogu.com.cn/problem/P6892)

## 题解

首先答案下界一定是 $n$，因为一共 $2n$ 个位置每两个都要调整一次。考虑通过某种构造方式达到这个下界。

用 $1$，$2$，$0$ 分别表示 $A$，$B$ 和空，以下是一个方案：

```
002121212121212121212121
122121212121212121212001
1221[0021212121212121]2211
```

容易发现框出来个一个区域是一个和原来一样的规模更小的子问题。

我们考虑直接分治，分治后这一段区间是排好序的。

```
122111111112222222002211
100111111112222222222211
111111111112222222222200
```

为了确定分治的边界的同时平衡复杂度，我们分治到 $n < 8$ 时直接爆搜即可。

实现上的细节问题，$n=3$ 不能只使用左边两个位置就达成目标，需要借用左边四个位置。 


## Code

```cpp
// Problem: P6892
#include <bits/stdc++.h>
#define ll long long
#define sz(x) (int)x.size()
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
#define D(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
inline ll rd() {
	ll x = 0; bool f = 1; char ch = getchar();
	while (ch < '0' || ch > '9') { if (ch == '-') f = 0; ch = getchar(); }
	while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return (f ? x : (-x));
}
const int N = 1e3 + 5;
int n, *a, d[N<<1];
struct V { int x, y; };
vector<V> ans, res;
void Ins(vector<V> &A, int x, int y) { A.push_back((V){x, y}); }
bool Dfs(int l, int r, int len) {
	bool flag = 1;
	F(i, l, l+len-1) if (a[i] != 1) { flag = 0; break; }
	F(i, l+len, l+len+len-1) if (a[i] != 2) { flag = 0; break; }
	if (flag) return 1;
	if (sz(res) == len) return 0;
	vector<int> vo;
	F(i, l, r) if (a[i] == 0 && a[i+1] == 0) vo.push_back(i);
	F(i, l, r) {
		if (a[i] == 0 || a[i+1] == 0) continue;
		for (int j : vo) {
			swap(a[i], a[j]), swap(a[i+1], a[j+1]), Ins(res, i, j);
			if (Dfs(l, r, len)) return 1;
			swap(a[i], a[j]), swap(a[i+1], a[j+1]), res.pop_back();
		}
	}
	return 0;
}
void Solve(int l, int r) {
	if (r-l+1 >= 16) {
		Ins(ans, r-2, l-2), Ins(ans, l+2, r-2);
		Solve(l+4, r-4);
		Ins(ans, l-1, r-5), Ins(ans, r-1, l-1);
	} else {
		a[l-1] = a[l-2] = 0, res.clear();
		F(i, l, r) a[i] = ((i & 1) ? 2 : 1);
		int len = (r-l+1)>>1;
		if (len == 3) Dfs(l-4, r, len);
		else Dfs(l-2, r, len);
		for (V u : res) ans.push_back(u);
	}
}
int main() {
	n = rd(), a = d + N;
	Solve(1, 2 * n);
	for (V v : ans) cout << v.x << " to " << v.y << '\n'; 
	return 0;
}
```

---

## 作者：scp020 (赞：0)

# P6892 [ICPC2014 WF] Baggage 题解

这构造太抽象了，我做了一天。

## 解法

观察两个样例发现，所需最小步数是 $n$，考虑如何证明答案下界是 $n$。

这里使用比较经典的容分析，定义每个位置的容为两侧两个相邻和该位置相同的个数，一个状态的容为所有位置的容的和。初始状态的容为 $0$，目标状态的容为 $4 n - 4$，没进行一次操作最多使容增加 $4$，而第一次操作只能将中间的相邻行李移动到两侧的空位上，所以靠外的位置的容没办法增加，而我们期望的本来应该与外侧位置相邻的那个位置的容也没办法增加（就是说只能是内测和与内测相邻的两个位置的容增加），所以第一次移动只能使容增加 $2$，所以答案理论下届为 $n$ 次操作。

考虑如何达到理论下界。

考虑使用暴力搜索找 $n \le 6$ 的规律（因为我这个暴力当 $n=7$ 的时候已经跑不出来了）。

![3](https://cdn.luogu.com.cn/upload/image_hosting/zuhqk23m.png)

![4](https://cdn.luogu.com.cn/upload/image_hosting/ncsoq50g.png)

![5](https://cdn.luogu.com.cn/upload/image_hosting/t8ypzylx.png)

![6](https://cdn.luogu.com.cn/upload/image_hosting/4db8ryau.png)

并没有发现什么很直观的规律，故考虑归纳构造。

依次由小到大尝试将 $n$ 仅花费 $x$ 次操作规约为 $n - x$，发现当 $x = 4$ 时可以实现（手玩过程非常漫长），如图。

![图](https://cdn.luogu.com.cn/upload/image_hosting/lozbw8mz.png)

但是很容易发现 $n = 7$ 的情况不能规约为 $n = 3$ 的情况，否则中间会有两个空位，所以还要手玩一下 $n = 7$ 的情况。

![7](https://cdn.luogu.com.cn/upload/image_hosting/93kuhwcs.png)

然后就做完了。

## 代码

### 暴力核心代码

```cpp
int n,a[100],ans;
inline bool check2(int l,int r,int val)
{
    for(int i=l;i<=r;i++) if(a[i]!=val) return false;
    return true;
}
inline bool check()
{
    for(int i=0;i<=20;i++) if(a[i]==1) return check2(i,i+n-1,1) && check2(i+n,i+n*2-1,2);
    return false;
}
inline void print()
{
    for(int i=0;i<=21;i++) out<<a[i]<<' ';
    out<<'\n';
}
inline bool dfs(int dep)
{
    if(dep==n)
    {
        if(check())
        {
            print();
            ans++;
            return true;
        }
        return false;
    }
    bool flag=false;
    for(int i=0,tmp1,tmp2;i<=20;i++)
        if(a[i] && a[i+1])
            for(int j=0,fl;j<=20;j++)
                if(!a[j] && !a[j+1])
                {
                    tmp1=a[i],tmp2=a[i+1],a[j]=a[i],a[j+1]=a[i+1],a[i]=a[i+1]=0,fl=false;
                    if(dfs(dep+1)) flag=fl=true;
                    a[j]=a[j+1]=0,a[i]=tmp1,a[i+1]=tmp2;
                    if(fl) print();
                }
    return flag;
}
```

### 归纳构造代码

```cpp
#include<bits/stdc++.h>
namespace fast_IO
{
    /**
     * useless fastio
     */
};
using namespace fast_IO;
int n;
inline void dfs(int n,int l,int r)
{
    if(n==3)
    {
        out<<l+1<<" to "<<l-2<<'\n';
        out<<r-1<<" to "<<l+1<<'\n';
        out<<l+2<<" to "<<-3<<'\n';
        return;
    }
    if(n==4)
    {
        out<<r-2<<" to "<<l-2<<'\n';
        out<<l+2<<" to "<<r-2<<'\n';
        out<<l-1<<" to "<<l+2<<'\n';
        out<<r-1<<" to "<<l-1<<'\n';
        return;
    }
    if(n==5)
    {
        out<<r-2<<" to "<<l-2<<'\n';
        out<<l+2<<" to "<<r-2<<'\n';
        out<<r-4<<" to "<<l+2<<'\n';
        out<<l-1<<" to "<<r-4<<'\n';
        out<<r-1<<" to "<<l-1<<'\n';
        return;
    }
    if(n==6)
    {
        out<<r-2<<" to "<<l-2<<'\n';
        out<<r-5<<" to "<<r-2<<'\n';
        out<<l+1<<" to "<<r-5<<'\n';
        out<<l+5<<" to "<<l+1<<'\n';
        out<<l-1<<" to "<<l+5<<'\n';
        out<<r-1<<" to "<<l-1<<'\n';
        return;
    }
    if(n==7)
    {
        out<<r-6<<" to "<<l-2<<'\n';
        out<<l+4<<" to "<<r-6<<'\n';
        out<<r-2<<" to "<<l+4<<'\n';
        out<<l+2<<" to "<<r-2<<'\n';
        out<<r-5<<" to "<<l+2<<'\n';
        out<<l-1<<" to "<<r-5<<'\n';
        out<<r-1<<" to "<<l-1<<'\n';
        return;
    }
    out<<r-2<<" to "<<l-2<<'\n';
    out<<l+2<<" to "<<r-2<<'\n';
    dfs(n-4,l+4,r-4);
    out<<l-1<<" to "<<r-5<<'\n';
    out<<r-1<<" to "<<l-1<<'\n';
}
int main()
{
    in>>n;
    dfs(n,1,2*n);
    fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
    return 0;
}
```

---

## 作者：s4CRIF1CbUbbL3AtIAly (赞：0)

与通常的构造题不同，本题要求的为最短操作序列，看起来难以下手。但是经过尝试或对较小的 $n$ 进行搜索，会发现它们的最短操作序列长度都是 $n$。

证明操作次数不少于 $n$ 并不麻烦：考虑有多少对相邻的包裹类型相同，设为 $d$。初始时 $d=0$，目标状态的 $d=2n-2$。一次操作中，取出包裹时 $d$ 不会增加，而放回时假设放的位置为 $t$ 和 $t+1$，则只可能增加 $(t-1,t)$ 和 $(t+1,t+2)$ 这两对。容易发现第一次操作至多使 $d$ 增加 $1$，因此总操作次数不少于 $1+\lceil\frac{2n-3}2\rceil=n$。

接下来就要尝试对于所有 $n$ 构造长为 $n$ 的操作序列。对于 $n$ 较小时可以直接搜索出操作序列。

观察发现，在 $n>3$ 的情形中，我们都是将这些包裹从编号为 $1\sim 2n$ 的格子移到编号为 $-1\sim 2n-2$ 的格子。

于是我们定义 $solve(n,x)$ 表示将包裹从编号为 $x+1$ 到 $x+2n$ 的格子（形如初始状态）移到编号为 $x-1$ 到 $x+2n-2$ 的格子并排列成形如目标状态。

通过对较大的 $n$ 的情形的观察，对于 $n\ge 8$ 的情况有如下构造（其中 $\texttt/$ 表示空格子）：

$$\texttt{/ / B A B A B A B A ... B A B \color{red}{A B}\color{black}{ A}}$$

$$\texttt{\color{blue}{A B}\color{black}{ B A }\color{red}{B A}\color{black}{ B A B A ... B A B / / A}}$$

$$\texttt{A B B A \color{red}{/ / B A B A ... B A}\color{black}{ B }\color{blue}{B A}\color{black}{ A}}$$

在这里，我们发现最后一行的红色部分正好符合 $solve$ 函数的输入，因此我们调用 $solve(n-4,x+4)$。

$$\texttt{A \color{red}{B B}\color{black}{ A }\color{blue}{A A A ... B B B / /}\color{black}{ B B A A}}$$

$$\texttt{A / / A A A A ... B B B \color{blue}{B B}\color{black}{ B B }\color{red}{A A}}$$

$$\texttt{A \color{blue}{A A}\color{black}{ A A A A ... B B B B B B B / /}}$$

至此，我们便完成了长度为 $n$ 的操作序列的构造。

构造过程虽然比较复杂而且难想，不过最终代码还是比较好写的，只要先把 $n=3\sim 7$ 的方案全都打表即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
void prt(int f,int t,int x=0){cout<<x+f<<" to "<<x+t<<"\n";}// 方便输出
void solve(int n,int x){
	if(n==4){
		prt(6,-1,x);
		prt(3,6,x);
		prt(0,3,x);
		prt(7,0,x);
		return;
	}
	if(n==5){
		prt(8,-1,x);
		prt(3,8,x);
		prt(6,3,x);
		prt(0,6,x);
		prt(9,0,x);
		return;
	}
	if(n==6){
		prt(10,-1,x);
		prt(7,10,x);
		prt(2,7,x);
		prt(6,2,x);
		prt(0,6,x);
		prt(11,0,x);
		return;
	}
	if(n==7){
		prt(8,-1,x);
		prt(5,8,x);
		prt(12,5,x);
		prt(3,12,x);
		prt(9,3,x);
		prt(0,9,x);
		prt(13,0,x);
		return;
	}
	prt(2*n-2,-1,x);
	prt(3,2*n-2,x);
	solve(n-4,x+4);
	prt(0,2*n-5,x);
	prt(2*n-1,0,x);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int n;
	cin>>n;
	if(n==3){
		prt(2,-1);
		prt(5,2);
		prt(3,-3);
		return 0;
	}
	solve(n,0);
	return 0;
}
```

---

