# [ABC401D] Logical Filling

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc401/tasks/abc401_d

给定一个长度为 $N$ 的字符串 $S$，仅由 `.`、`o` 和 `?` 组成。将所有 `?` 分别替换为 `.` 或 `o` 后得到的字符串中，满足以下所有条件的字符串集合记为 $X$：

- `o` 的个数恰好为 $K$ 个
- `o` 不连续出现

保证 $X$ 不是空集。

请输出满足以下条件且长度为 $N$ 的字符串 $T$（其中 $T_i$ 表示 $T$ 的第 $i$ 个字符）：

- 若 $X$ 中所有字符串的第 $i$ 个字符都是 `.`，则 $T_i =$ `.`
- 若 $X$ 中所有字符串的第 $i$ 个字符都是 `o`，则 $T_i =$ `o`
- 若 $X$ 中既存在第 $i$ 个字符为 `.` 的字符串，也存在第 $i$ 个字符为 `o` 的字符串，则 $T_i =$ `?`

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $0 \leq K$
- $S$ 是仅由 `.`、`o` 和 `?` 组成的长度为 $N$ 的字符串
- $X$ 不是空集
- 输入的所有数值均为整数

### 样例解释 1

$X$ 包含两个字符串 `o.o.` 和 `o..o`。由于 $X$ 中所有字符串的第 1 个字符都是 `o`，所以 $T_1 =$ `o`。$X$ 中所有字符串的第 2 个字符都是 `.`，所以 $T_2 =$ `.`。$X$ 中既有第 3 个字符为 `.` 的字符串，也有为 `o` 的字符串，因此 $T_3 =$ `?`。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4 2
o???```

### 输出

```
o.??```

## 样例 #2

### 输入

```
5 2
?????```

### 输出

```
?????```

## 样例 #3

### 输入

```
7 3
.o???o.```

### 输出

```
.o.o.o.```

# 题解

## 作者：Little_x_starTYJ (赞：11)

### 解题思路
首先分析题意。

1. 容易发现类似 `?o`，`o?` 的问号其实是“假问号”，因为 `o` 不能连续出现，所以只能是 `.`。

2. 其次就是当 $k$ 为字符串 $s$ 最多能包含 `o` 的数量时才可能会有 `?` 变成 `o`。否则判完第 $1$ 条直接输出就行了。

那我们现在就来看看如何统计 $s$ 所能包含 `o` 的最大数量。

这里我们可以把 $s$ 拆分成若干个只含 `?` 最长连续子串 $t_i$。

由于我们先处理了第 $1$ 种情况，所以 $t_i$ 会类似 `.|????|.`，其中 `|` 之间的字符串就是 $t_i$。我们手动模拟一下：

定义 $|s|$ 为字符串 $s$ 的长度。

- 当 $|t_i|$ 为奇数时，类似 `o.o.o` 时所包含 `o` 的数量最多。最多可以贡献 $\lceil \frac{|t_i|}{2} \rceil$ 个 `o`，在 C++ 中表示为 `len / 2 + 1`。

- 当 $|t_i|$ 为偶数时，类似 `o.o.o.`，`.o.o.o` 时所包含 `o` 的数量都是最多的，最多可以贡献 $\frac{|t_i|}{2}$ 个 `o`。

最后我们将所有贡献统计起来再加上原有的 `o` 的数量，如果为 $k$，那么长度为奇数的 $t_i$ 就可以确定，长度为偶数的 $t_i$ 就还是全是 `?`。

至于为什么只有贡献为 $k$ 时才能确定，比如 $s$ 为 `o.??.o.???`，$k = 4$，符合条件的字符串有 `o.o..o.o..`，`o..o.o.o..`，`o.o..o..o.`，`o.o..o...o`……你会发现每个 `?` 都有多种可能。

CODE：
```cpp
/*
15 7
????.?????.????

5 3
?????

4 2
?..?
*/
/*
15 7
????.?????.????

5 3
?????

4 2
?..?
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int n, k, cnt = 0;
	cin >> n >> k;
	string a;
	cin >> a;
	cnt = (a[0] == 'o' ? 1 : 0);
	for (int i = 1; i < n; i++) {
		if (a[i] == '?' && (a[i - 1] == 'o' || i < n - 1 && a[i + 1] == 'o')) {
			a[i] = '.';
		}
		if (a[i] == 'o') {
			cnt++;
		}
	}
	if (cnt == k) {
		for (int i = 0; i < n; i++) {
			if (a[i] == '?') {
				a[i] = '.';
			}
		}
		cout << a;
		return 0;
	}
	if (a[0] == '?') {
		if (a[1] == 'o') {
			a[0] = '.';
		}
	}
	for (int i = 0; i < n; i++) {
		if (a[i] == '?') {
			//前后面一定是 .
			int j = i;
			while (a[i] == '?' && i < n) {
				i++;
			}
			//o.????.o
			cnt += (i - j + 1) / 2;  //（区间长度 + 1） / 2，算的只是 ？ 最多可以替换成多少个 o，懒得用 ceil
			//不用 i--，因为 a[i] 一定为 . 
		}
	}
	if (cnt == k) {
		for (int i = 0; i < n; i++) {
			if (a[i] == '?') {
				//前后面一定是 .
				int j = i;
				while (a[i] == '?' && i < n) {
					i++;
				}
				if ((i - j) & 1) {
					for (int k = j; k < i; k++) {
						if ((k - j) % 2 == 0) {
							a[k] = 'o';
						} else {
							a[k] = '.';
						}
					}
				}
			}
		}
	}
	cout << a;
	return 0;
}
```

---

## 作者：Clover_Lin (赞：3)

## 博客
点击[这里](https://blog.csdn.net/ArmeriaLeap/article/details/147173639)阅读。
## 前言
这次的 D 题出得很好，不仅融合了数学逻辑推理的知识，还有很多细节值得反复思考。虽然通过人数远高于 E，但是通过率甚至不到 60%，可见这些细节正是出题人的侧重点。
## 题目大意
给定一个长度为 $N$ 的字符串 $S$，由 `o` 和 `.` 组成。现在一些位置的字符不明确，用 `?` 表示，可以替换成 `o` 和 `.` 中的任意一个。要求目标串（所有位置都被替换之后）同时满足以下两个条件：
- $S$ 中有**恰好** $K$ 个 `o`。
- 任意两个 `o` 不相邻。

现在要填这个串，但是因为条件有限，只能完成部分内容。输出所有答案唯一（可以确定）的位置的字符，其他位置仍用 `?` 表示。
## 思路
为了简化问题，我们要先从最简单的位置入手，再解决其他位置。让我们来分析一下都有哪些情况是确定的：
| 描述 | 结果 | 备注 |
|--|--|--|
| 一个问号与 `o` 相邻 | 这里填 `.` | 无 |
| `o` 的数量已经达到 $K$ | 所有问号处填 `.` | 无 |
| `o` 的数量与问号的数量之和恰好为 $K$ | 所有问号处填 `o` | 无 |
| 出现连着 $2\cdot M+1$ 个问号，且这段里必须填 $M+1$ 个 `o` [^1] | 这段形如 `o.o.o.···.o` | 本人赛时曾忽略 |

[^1]: 如何判定这种情况？当且仅当数组中每一段连续的问号（长度为 $L$）都填 $\left \lceil \frac{L}{2} \right \rceil$ 个 `o` 时 `o` 的数量恰好为 $K$。

然后我们执行这些操作无限次，直到无法更新任何地方（执行了之后该轮没有任何格子被更新）为止。
## 代码
赛时 AC 提交记录：[Submission #64790876](https://atcoder.jp/contests/abc401/submissions/64790876)。
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int n, k;
string s;
int t[200010];

int main()
{
	cin >> n >> k >> s;
	s = " " + s + " ";
	int upd = 0;
	do
	{
		upd = 0;
		for (int i = 1; i <= n; i++)
			if (s[i] == '?')
			{
				if (i != 1 && s[i - 1] == 'o')
					s[i] = '.', upd++;
				if (i != n && s[i + 1] == 'o')
					s[i] = '.', upd++;
			}
		int cnt1 = 0, cnt2 = 0;
		for (int i = 1; i <= n; i++)
		{
			if (s[i] == 'o') cnt1++;
			if (s[i] == '?') cnt2++;
		}
		if (cnt1 + cnt2 == k)
		{
			for (int i = 1; i <= n; i++)
				if (s[i] == '?')
					s[i] = 'o', upd++;
//			break;
		}
		else if (cnt1 == k)
		{
			for (int i = 1; i <= n; i++)
				if (s[i] == '?')
					s[i] = '.';
//			break;
		}
		for (int i = 1; i <= n; i++)
			if (s[i] == '?')
			{
				if (s[i - 1] == 'o')
					s[i] = '.', upd++;
				if (s[i + 1] == 'o')
					s[i] = '.', upd++;
			}
		int cnt = 0, c = 0, flag = 1;
		for (int i = 1; i <= n; i++)
			t[i] = 0;
		for (int i = 1; i <= n; i++)
		{
			if (s[i] == '?')
				t[i] = t[i - 1] + 1;
			else
			{
				cnt += (t[i - 1] + 1) / 2;
				t[i] = 0;
			}
		}
		cnt += (t[n] + 1) / 2;
		for (int i = n; i >= 1; i--)
			if (t[i] && t[i + 1])
				t[i] = t[i + 1];
		if (cnt + cnt1 == k)
		{
			for (int i = 1; i <= n; i++)
			{
//				cout << t[i] << " " << i << endl;
				if (t[i] % 2 == 0) continue;
				if (s[i] == '?' && s[i - 1] != 'o')
					s[i] = 'o', upd++;
				else if (s[i] == '?')
					s[i] = '.', upd++;
			}
//			break;
		}
	} while (upd != 0);
	for (int i = 1; i <= n; i++)
		cout << s[i];
	return 0;
}
/*
7 3
?o????.
---
10 5
?????.????
*/
```

---

## 作者：canwen (赞：1)

赛时从错解一步步 AC 的。

我们可以先对原有的 `o` 左右两遍的字符打上标记，必须是 `.`。

接着我们考虑剩下的 `?`，对于每个全部由 `?` 组成的子串 $x_i$，设其长度为 $l_i$，最多能放 $\lfloor \frac{l_i+1}{2} \rfloor$ $l_i$ 个 `o`，当 $l_i$ 为偶数时每个位置都可以放 `.` 或者 `o`，这一点还是很好看出来的。

那么当 $l_i$ 为奇数就要视总的最多能放的 `o` 的数量 $cnt$ 而定了，设字符串 $s$ 中原本存在的 `o` 数量为 $kk$，若 $cnt>k-kk$，也就是我可以将至少任何一个位置空出，放 `.`，其他按照规则放 `o` 就行了，若 $cnt = k-kk$，则每个长度 $l_i$ 为奇数的子串 $x_i$ 都需要放满，也就是样例三的情况，以上分类讨论就行了。

交上去依旧 WA $10$ 个点怎么办，因为毒瘤出题人设置了 $kk = k$ 的情况，此时每个 `?` 只能是 `.`，因为已经不需要更多的 `o` 了。

[通过记录 + 代码](https://atcoder.jp/contests/abc401/submissions/64779660)。

对这道题的个人评价：还是很需要思考的一题。

```cpp
#include <bits/stdc++.h>
//#include <unordered_map>
//#include <unordered_set>
using namespace std;

#define int long long

#define _rep(i,a,b) for(int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for(int i=(a);i<=(b);c)
#define _rrep(i,a,b) for(int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for(int i=(a);i>=(b);c)
#define _graph(i) for(int i=head[u];i;i=e[i].nxt)
#define pc putchar('\n')
#define pb emplace_back
#define mk make_pair
#define fst first
#define snd second
#define pint pair<int,int>
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define nowtime (double)clock()/CLOCKS_PER_SEC
#define i128 __int128

//#define getchar getchar_unlocked
//#define putchar putchar_unlocked
int in(){
	char a = getchar();
	int res = 0, k = 1;
	while(!isdigit(a)){
		if(a == '-') k = 1;
		a = getchar();
	}
	while(isdigit(a)){
		res = res * 10 + a - '0', a = getchar();
	}
	return res * k;
}
void out(int a){
	if(a < 0) putchar('-'),a=-a;
	if(a > 9) out(a/10);
	putchar(a%10+'0');
}
void solve();

signed main(){
	int T = 1;
	while(T--){
		solve();
	}
	return 0;
}
const int N = 2e5 + 5;
int f[N];
void solve(){
	int n,k;
	cin >> n >> k;
	string s;
	cin >> s;
	for(int i=0;i<s.size();++i){
		if(s[i] == 'o'){
			--k;
			f[i] = 1;
			if(i != 0) f[i-1] = 2;
			if(i < (int)s.size()-1) f[i+1] = 2;
		}else if(s[i] == '.'){
			f[i] = 2;
		}else ;
	}
	
	if(k == 0){
		for(int i=0;i<s.size();++i){
			cout << (s[i] == 'o' ? "o" : ".");
		}
		return;
	}
	int cnt = 0;
	for(int i=0;i<s.size();++i){
		if(f[i] != 0) continue;
		int _ = 1;
		int lasti = i;
		while(i < (int)s.size()-1 && f[i+1] == 0) _++,++i;
		cnt += (_+1) / 2;
		if(_ % 2 == 0){
			_rep(j,lasti,i) f[j] = 4;
		}
	}
	
//	cout << "maxn = " << cnt << endl;
	if(cnt == k){
		for(int i=0;i<s.size();++i){
//			cout << "i = " << i << endl;
			if(f[i] == 4) cout << "?";
			else if(f[i] == 1){
				cout << "o";
			}else if(f[i] == 0){
				cout << "o", f[i+1] = 2;
			}
			else cout << ".";
		}
		return;
	}
	for(int i=0;i<s.size();++i){
		if(f[i] == 0 || f[i] == 4) cout << "?";
		else cout << (f[i] == 1 ? "o" : ".");
	}
	
}
```

---

## 作者：fr_dr (赞：0)

## 题目大意  
给定一个长度为 $n$ 的字符串，包含字符 $\texttt. \texttt o \texttt ?$。三种字符，要求将一定是 $\texttt. \texttt o$ 的 $\texttt ?$ 替换为对应字符，不一定的保留，并给出变化后的字符串。
## 思路
发现 $\texttt o$ 旁边的的 $\texttt ?$ 一定是$\texttt.$。所以将这种情况优先处理好，发现处理后的字符串连续的问号区间两边一定是 $\texttt.$，所以我们考虑在什么情况下，可以使得该区间的字符确定。我们假设有一条全问号字符串，发现对于奇数的区间使其确定的情况一定是当 $\texttt o$ 的数量等于其长度（记为 $len$）除以 $2$ 上取整即（$⌈\frac{len}{2}⌉$）或者没有时能有唯一的 $\texttt.\texttt o$ 字符串。当长度为偶数时只有 $\texttt o$ 的数量为 $0$ 时有唯一的字符串。所以我们单独考虑每一个问号区间，只有当未确定的 $\texttt o$ 的数量为零时所有 $\texttt ?$ 都可以变为 $\texttt.$，或者，每一个问号区间都放最大数量的 $\texttt o$ 时，奇数区间的字符串确定，偶数区间 $\texttt o$ 的数量确定。对于第一种情况是显然的，对于第二种情况，因为对于偶数区间虽然没有确定字符串的情况，但其有最大存在 $\texttt o$ 的数量，对于奇数区间也有最大存在 $\texttt o$ 的数量，如果有剩余未确定的 $\texttt o$，且 $\texttt o$ 的数量不是所有问号区间最大存在 $\texttt o$ 的数量之和，那么一定存在空隙，可以使得 $\texttt o$ 自由变化位置，所以其问号区间一定都不能确定，而如果是最大数量，那么奇数区间确定而偶数区间仍不确定。（具体区间形式见代码注释）

#### 综上所述共有三种情况：
- 没有剩余的 $\texttt o$，所以问号全部填 $\texttt.$。
- 有剩余的 $\texttt o$,但不是最大能填 $\texttt o$ 的数量，那么所有问号都不确定
- 是最大能填 $\texttt o$ 的数量，偶数区间不确定，奇数区间确定
## 代码

```cpp
	#include<iostream>
	using namespace std;
	long long n,k,sum,k1;
	char ans[200010],temp;
	int main(){
		cin>>n>>k;
		k1=k;
		for(int i=1;i<=n;i++){
			cin>>temp;
			if(temp=='o'){//将已经确定的？修改 
				ans[i]='o';
				ans[i-1]='.';
				ans[i+1]='.';
				k--;
				k1--;
			}
			if(temp=='.'){
				ans[i]='.';
			}
			if(ans[i]!='.'&&ans[i]!='o') ans[i]='?'; 
		}
		long long len=0;
		ans[n+1]='.';
		for(int i=1;i<=n+1;i++){
			if(ans[i]=='?'){
				len++;
			}
			else{
				k1-=(len+1)>>1;
				len=0; 
			}
		}//将剩余的未确定的 o 的数量减去最大存在o的数量 
		if(k1!=0&&k!=0){//如果既有剩余的 o，又不是最多的情况那么原样输出 
			for(int i=1;i<=n;i++){
				cout<<ans[i];
			}
		}
		else if(k==0){//如果没有剩余的 o，那么？一定全部为. 
			for(int i=1;i<=n;i++){
			    if(ans[i]=='?') cout<<'.';
			    else            cout<<ans[i];
			}
		}
		else{//如果是最大值，那么奇数区间确定，偶数区间不确定 
			for(int i=1;i<=n+1;i++){
			if(ans[i]=='?'){
				len++;
			}
			else{
				long long r=i-1,l=i-len;
				if(len%2==1){
			    	for(int j=l;j<=r;j++){
			    		if((j-l+1)%2==1) ans[j]='o';
			    		else             ans[j]='.';
					}
				}
				len=0;
			}
		}
		    for(int i=1;i<=n;i++){	
		    	cout<<ans[i];
			}	
		}
	}
	/*
	   当问号区间o数量最大的情况下 
	   奇数区间形如：o.o.o(....)o.o.o  
	   例如长度为 5：o.o.o 
	   偶数区间形如：o.o.(....)o. 或 .o.o.(...)o.o
	   例如长度为 4：o.o. 或 .o.o 
	*/ 
```
复杂度大概是 $O(n)$，如有错误请指正

---

## 作者：copper_ingot (赞：0)

[洛谷](https://www.luogu.com.cn/problem/AT_abc401_d)

[AtCoder](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc401_d)

首先，我们把一些一定能确定的位置先确定了：如果一个 `?` 有 `o` 相邻，那么它一定是 `.`。

```
.o.o???????o??o.?????o????
            ↓ 
.o.o.?????.o..o.????.o.???
```

做完这一步后，整个字符串被分为了若干个段，就像这样：

```
.o.o.?????.o..o.????.o.???
     [ 1 ]      [2 ]   [3]
```

设第 $i$ 个段的长度为 $len_i$，则第 $i$ 个段最多可以提供 $\lceil\frac{len_i}{2}\rceil$ 个 `o`。设所有段总共可以提供 $ans$ 个 `o`，字符串还需要 $k$ 个 `o`。因为保证 $X$ 不为空，所以 $ans\ge k$。

当 $ans=k$ 时：每一个段都必须提供全部 `o`。如果一个段的长度是偶数，那么有 `o.o.` 和 `.o.o` 两种形式，所以 $t$ 在这一段全是 `?`。而如果长度是奇数，则只有 `o.o.o` 一种形式，$t$ 在这一段是 `o` 和 `.` 交替。

当 $ans>k$ 时：每一个段都有可能少提供若干个 `o`，容易证明 $t$ 在每一段都全是 `?`。

特殊情况，当 $k=0$ 时：显然不能再添加 `o`，所以 $t$ 在每一段都是 `.`。笔者因此 WA 了一发。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
pii mkp(int x, int y){pii p; p.first = x, p.second = y; return p;}
int n, k, cnt, a[300001], b[300001], ans; char s[300001], t[300001];
signed main(){
	scanf("%lld%lld%s", &n, &k, s + 1);
	for (int i = 1; i <= n; i++) if (s[i] == 'o') k--;
	for (int i = 1; i <= n; i++){
		if (s[i] != '?') t[i] = s[i];
		else if (s[i + 1] == 'o' || s[i - 1] == 'o') t[i] = '.';
	}
	for (int i = 1; i <= n; i++){
		if (cnt % 2 == 0 && !t[i]) a[cnt / 2 + 1] = i, cnt++;
		else if (cnt % 2 && t[i] == '.') b[cnt / 2 + 1] = i - 1, cnt++;
	}
	if (cnt % 2) b[cnt / 2 + 1] = n, cnt++;
	cnt /= 2;
	for (int i = 1; i <= cnt; i++) ans += (b[i] - a[i]) / 2 + 1;
	if (ans == k){
		for (int i = 1; i <= cnt; i++){
			if ((b[i] - a[i] + 1) % 2)
				for (int j = a[i]; j <= b[i]; j++) t[j] = ((j - a[i]) % 2 ? '.' : 'o');
			else for (int j = a[i]; j <= b[i]; j++) t[j] = '?';
		}
	}
	else if (k == 0) for (int i = 1; i <= cnt; i++) for (int j = a[i]; j <= b[i]; j++) t[j] = '.';
	else for (int i = 1; i <= cnt; i++) for (int j = a[i]; j <= b[i]; j++) t[j] = '?';
	printf("%s\n", t + 1);
	return 0;
}
```

---

## 作者：蔡涵秋2011 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc401_d)

## 1. 题意简述
题意非常清晰，建议没看懂的再读一遍题目，在此不多赘述。

---

简单说明一下几个样例：

```
4 2
o???
```

给出一个长度为 4 的字符串 `o???`，希望有恰好 2 个 `o`。

第一个已经给定。第二个与 `o` 相连，根据 `o` 不连续出现，可以得知一定是 `.`。

接下来第三第四个，可能是 `o.o.`，也可能是 `o..o`。都符合要求，所以不能确定，填为 `o.??`。

---

```
5 2
?????
```

显然，都不能确定，原样输出。

---

```
7 3
.o???o.
```

同样的，由于 `o` 不可以相连，所以可以先变成 `.o.?.o.`，又因为要求恰好有 3 个 `o`，因此中间的 `?` 只能是 `o`。

## 2. 思路分析

目前想到两个思路，由于其中一个思路在官方题解和上一篇题解中都有提到，所以在此解释另一种。

由于本人太菜了，在开始错误的贪心后以为这道题是不可以贪心的，所以考虑了前缀和和后缀和。

具体看代码：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

string s; // 输入的字符串
int n, k, minL[N][2], maxL[N][2], minR[N][2], maxR[N][2];
// n, k 见题目解释
```
$minL_{i,0}$ ：从左到右一直到 $i$ 最少的 `o` 的数量，第 $i$ 位不填 `o`。

$minL_{i,1}$ ：从左到右一直到 $i$ 最少的 `o` 的数量，第 $i$ 位填 `o`。

$minR_{i,0}$ ：从右到左一直到 $i$ 最少的 `o` 的数量，第 $i$ 位不填 `o`。

$minR_{i,1}$ ：从右到左一直到 $i$ 最少的 `o` 的数量，第 $i$ 位填 `o`。

数组的计算在后面会有更详细的解释。

---

```
signed main()
{
	cin >> n >> k >> s; 
	for (int i = 0; i < n; i++)
		if (s[i] == '?' && (s[i - 1] == 'o' || s[i + 1] == 'o'))	s[i] = '.'; // 一个小小的预处理
```

就像上文所说，因为 `o` 不能相连，所以如果出现 `?` 与 `o` 相连，那么 `?` 必为 `.` 。

---

```
cal_L();
cal_R();
```

```
void cal_L()
{
  // 第一个循环计算 min
	for (int i = 0; i < n; i++) // 遍历字符串
	{
		if (s[i] == '.') // 如果这一位是 .
		{
			minL[i][0] = min(minL[i - 1][0], minL[i - 1][1]); // 那只可能是 0 （不填 o），最小的数量可能是上一位填 o 或不填 o
			minL[i][1] = 1e18; // 填 o 不可能，直接设成比较大的值
		}
		else if (s[i] == 'o') // 如果这一位是 o
		{
			minL[i][0] = 1e18; // 显然一定填 o，所以也直接设成较大值
			minL[i][1] = minL[i - 1][0] + 1; // 如果这一位是 o，所以上一位一定是 .，最小值一定由 minL[i - 1][0] 转移过来。因为自己本身是 o，所以记得加上自己
		}
		else // 否则目前是 ?
		{
			minL[i][0] = min(minL[i - 1][0], minL[i - 1][1]); 
			minL[i][1] = minL[i - 1][0] + 1;
            // 和上面同理
		}
	}
  // 这一个循环计算 max，原理和 min 基本一致
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '.')	
		{
			maxL[i][0] = max(maxL[i - 1][0], maxL[i - 1][1]);
			maxL[i][1] = -1e18; // 这里取 max，所以要设成较小值
		}
		else if (s[i] == 'o')
		{
			maxL[i][0] = -1e18;
			maxL[i][1] = maxL[i - 1][0] + 1;
		}
		else
		{
			maxL[i][0] = max(maxL[i - 1][0], maxL[i - 1][1]);
			maxL[i][1] = maxL[i - 1][0] + 1;
		}
	}
}

void cal_R() // cal_R 与 cal_L 同理，自行理解一下
{
	for (int i = n - 1; i >= 0; i--)
	{
		if (s[i] == '.')	
		{
			minR[i][0] = min(minR[i + 1][0], minR[i + 1][1]);
			minR[i][1] = 1e18;
		}
		else if (s[i] == 'o')
		{
			minR[i][0] = 1e18;
			minR[i][1] = minR[i + 1][0] + 1;
		}
		else
		{
			minR[i][0] = min(minR[i + 1][0], minR[i + 1][1]);
			minR[i][1] = minR[i + 1][0] + 1;
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		if (s[i] == '.')	
		{
			maxR[i][0] = max(maxR[i + 1][0], maxR[i + 1][1]);
			maxR[i][1] = -1e18;
		}
		else if (s[i] == 'o')
		{
			maxR[i][0] = -1e18;
			maxR[i][1] = maxR[i + 1][0] + 1;
		}
		else
		{
			maxR[i][0] = max(maxR[i + 1][0], maxR[i + 1][1]);
			maxR[i][1] = maxR[i + 1][0] + 1;
		}
	}
}
```

在此只解释 cal_L 中的 min 计算方式，其他同理，解释见注释。

---

```
for (int i = 0; i < n; i++)
	{
		bool iso = false, isdot = false; // iso 表示是否可能是 o，isdot 表示是否可能是 .
		int l = minL[i][1] + minR[i][1] - 1, r = maxL[i][1] + maxR[i][1] - 1;
// 这里计算第 i 位填 o 时的最小值与最大值，由于 L 和 R 会在 i 重复计算一次，所以记得 -1
		if (l <= k && k <= r)	iso = true; // 如果符合要求
		l = minL[i][0] + minR[i][0], r = maxL[i][0] + maxR[i][0]; // 这里计算第 i 位填 . 时的最小值与最大值，这里不涉及到重复计算
		if (l <= k && k <= r)	isdot = true; // 符合要求
		if (iso && isdot)	s[i] = '?'; 
		else if (iso)	s[i] = 'o';
		else if (isdot)	s[i] = '.';
      // 接下来的操作与题目要求一致
	}
	cout << s; // 输出答案
```

解释依旧看注释。

## 3. 代码

如果不是很清楚可以看一下完整代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 5;

string s;
int n, k, minL[N][2], maxL[N][2], minR[N][2], maxR[N][2];

void cal_L()
{
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '.')	
		{
			minL[i][0] = min(minL[i - 1][0], minL[i - 1][1]);
			minL[i][1] = 1e18;
		}
		else if (s[i] == 'o')
		{
			minL[i][0] = 1e18;
			minL[i][1] = minL[i - 1][0] + 1;
		}
		else
		{
			minL[i][0] = min(minL[i - 1][0], minL[i - 1][1]);
			minL[i][1] = minL[i - 1][0] + 1;
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (s[i] == '.')	
		{
			maxL[i][0] = max(maxL[i - 1][0], maxL[i - 1][1]);
			maxL[i][1] = -1e18;
		}
		else if (s[i] == 'o')
		{
			maxL[i][0] = -1e18;
			maxL[i][1] = maxL[i - 1][0] + 1;
		}
		else
		{
			maxL[i][0] = max(maxL[i - 1][0], maxL[i - 1][1]);
			maxL[i][1] = maxL[i - 1][0] + 1;
		}
	}
}

void cal_R()
{
	for (int i = n - 1; i >= 0; i--)
	{
		if (s[i] == '.')	
		{
			minR[i][0] = min(minR[i + 1][0], minR[i + 1][1]);
			minR[i][1] = 1e18;
		}
		else if (s[i] == 'o')
		{
			minR[i][0] = 1e18;
			minR[i][1] = minR[i + 1][0] + 1;
		}
		else
		{
			minR[i][0] = min(minR[i + 1][0], minR[i + 1][1]);
			minR[i][1] = minR[i + 1][0] + 1;
		}
	}
	for (int i = n - 1; i >= 0; i--)
	{
		if (s[i] == '.')	
		{
			maxR[i][0] = max(maxR[i + 1][0], maxR[i + 1][1]);
			maxR[i][1] = -1e18;
		}
		else if (s[i] == 'o')
		{
			maxR[i][0] = -1e18;
			maxR[i][1] = maxR[i + 1][0] + 1;
		}
		else
		{
			maxR[i][0] = max(maxR[i + 1][0], maxR[i + 1][1]);
			maxR[i][1] = maxR[i + 1][0] + 1;
		}
	}
}

signed main()
{
	cin >> n >> k >> s;
	for (int i = 0; i < n; i++)
		if (s[i] == '?' && (s[i - 1] == 'o' || s[i + 1] == 'o'))	s[i] = '.';
	cal_L();
	cal_R();
	for (int i = 0; i < n; i++)
	{
		bool iso = false, isdot = false;
		int l = minL[i][1] + minR[i][1] - 1, r = maxL[i][1] + maxR[i][1] - 1;
		if (l <= k && k <= r)	iso = true;
		l = minL[i][0] + minR[i][0], r = maxL[i][0] + maxR[i][0];
		if (l <= k && k <= r)	isdot = true;
		if (iso && isdot)	s[i] = '?';
		else if (iso)	s[i] = 'o';
		else if (isdot)	s[i] = '.';
	}
	cout << s;
	return 0;
}
```


---

这篇代码其实是用稍微高速一些的方法来暴力模拟，所以说肯定不如正解快，空间复杂度也相对更高一点。

---

## 作者：WuMin4 (赞：0)

## [[ABC401D] Logical Filling](https://atcoder.jp/contests/abc401/tasks/abc401_d)

## 题意

给出一个由 `o`，`.`，`?` 组成的字符串 $T$，其中 `?` 可以被替换为 `o`，`.`。一个字符串合法当且仅当包含 $K$ 个 `o` 且任意俩个 `o` 不相邻。问对于所有替换方案，若 $T_i$ 可以被确定（即对于所有替换方案填法都唯一），则输出可以被确定的字符，否则输出 `?`。

## 思路

可能是这场 ABC 最有含金量的一道题。

首先我们显然可以确定的是若一个位置为 `o`，则与它相邻的位置一定为 `.`。我们将这些位置确定后再来进行分类讨论。

若原字符串的 `o` 数量已经等于 $k$，那么所有剩下的位置只能为 `.`。

否则我们考虑贪心的将所有位置尽可能多的填入 `o`。

若贪心填入后 `o` 的数量等于 $k$，则对于 `?` 的连续段为偶数的段，既可以填入类似 `o.o.o.`，也可以填入类似 `.o.o.o` 的字符，所以填入的字符是不确定的。对于 `?` 的连续段为奇数的段，只能填入类似 `o.o.o` 的字符，所以填入的字符是确定的。

若贪心填入后 `o` 的数量大于 $k$，则表示每个位置都有可能是 `.`，所以所有剩下的位置都是不确定的。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n,k,cnt,cnt2;
char s[200005],s2[200005];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		cin>>s[i];
	for(int i=1;i<=n;i++)
		if(s[i]=='o')
			s[i-1]=s[i+1]='.',cnt++;
	if(cnt==k){
		for(int i=1;i<=n;i++)
			if(s[i]=='?') cout<<'.';
			else cout<<s[i];
		return 0;
	}
	for(int i=1;i<=n;i++) s2[i]=s[i];
	s[n+1]='.';
	for(int len=0,lst=1,i=1;i<=n+1;i++){
		if(s[i]=='?') len++;
		else{
			if(len%2==1){
				for(int j=lst;j<i;j++){
					s[j]=((j-lst)%2?'.':'o');
					if(s[j]=='o') cnt++;
				}
			}
			else cnt+=len/2;
			lst=i+1,len=0;
		}
	}
	if(cnt==k){
		for(int lst=0,i=1;i<=n;i++)
			cout<<s[i];
	}
	else{
		for(int i=1;i<=n;i++)
			cout<<s2[i];
	}
	return 0; 
}
```

---

## 作者：cyq32ent (赞：0)

首先，一个 `?` 旁边有 `o`，那么它一定应该填 `.`。

考虑经过上述过程处理后的字符串 $S'$。如果此时我们已经有足够的 `o`，不必再填入新的，那么我们就直接将所有的 `?` 填成 `.` 即可。

考虑另一种情况。我们知道，每一段长度为 $L$ 的连续的 `?`，它可以填入的 `o` 最多有 $\lfloor \frac{L+1} 2\rfloor$ 个。如果我们把全部能填进去的 `o` 都填入，且发现此时 `o` 的数量刚好达到 $K$，那么我们就把所有的 `?` 段都填入。对于 $L$ 为奇数的段，填法是唯一的，即形如 `o.o.o.o.o`；对于 $L$ 为偶数的段，填法有两种，所以只能全都保留 `?`。

考虑空位足够充足，可以填进所有的 `o` 且没有填满的情况。对于每一个候选的空位，它都可以选择填 `o` 或者填 `.`，因为余下的空位仍然可以满足填入所有 `o` 的要求。因此，在这种情况下，我们保留全部的 `?`。

```cpp
#include<bits/stdc++.h>
using namespace std;
string S,T;int N,K,o,p;
int main(){
	cin>>N>>K>>S;
	for(int i=0;i<N;i++){
		int flg=0;
		if(i>0&&S[i-1]=='o')flg=1;
		if(i+1<N&&S[i+1]=='o')flg=1;
		if(flg)S[i]='.';
		if(S[i]=='o')o++;
	}if(K==o){
		for(auto c:S)if(c=='?')cout<<'.';else cout<<c;
		return 0;
	}T=S;
	int lst=0,flg=0;
	for(int i=0;i<N;i++){
		if(S[i]=='?'&&!flg)lst=i,flg=1;
		if(S[i]!='?'&&flg){
			int x=i-lst;
			flg=0;
			p+=(x+1)/2;
			if(x&1){
				for(int j=lst;j<i;j++){
					if((j-lst)&1)T[j]='.';
					else T[j]='o';
				}
			}
		}
	}
	if(flg){
		int x=N-lst;
		p+=(x+1)/2;
		if(x&1){
			for(int j=lst;j<N;j++){
				if((j-lst)&1)T[j]='.';
				else T[j]='o';
			}
		}
	}
	if(o+p==K)cout<<T;
	else cout<<S;
	return 0;
}
```

---

