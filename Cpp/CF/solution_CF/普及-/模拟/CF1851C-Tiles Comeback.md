# Tiles Comeback

## 题目描述

Vlad remembered that he had a series of $ n $ tiles and a number $ k $ . The tiles were numbered from left to right, and the $ i $ -th tile had colour $ c_i $ .

If you stand on the first tile and start jumping any number of tiles right, you can get a path of length $ p $ . The length of the path is the number of tiles you stood on.

Vlad wants to see if it is possible to get a path of length $ p $ such that:

- it ends at tile with index $ n $ ;
- $ p $ is divisible by $ k $
- the path is divided into blocks of length exactly $ k $ each;
- tiles in each block have the same colour, the colors in adjacent blocks are not necessarily different.

For example, let $ n = 14 $ , $ k = 3 $ .

The colours of the tiles are contained in the array $ c $ = \[ $ \color{red}{1}, \color{violet}{2}, \color{red}{1}, \color{red}{1}, \color{gray}{7}, \color{orange}{5}, \color{green}{3}, \color{green}{3}, \color{red}{1}, \color{green}{3}, \color{blue}{4}, \color{blue}{4}, \color{violet}{2}, \color{blue}{4} $ \]. Then we can construct a path of length $ 6 $ consisting of $ 2 $ blocks:

 $ \color{red}{c_1} \rightarrow \color{red}{c_3} \rightarrow \color{red}{c_4} \rightarrow \color{blue}{c_{11}} \rightarrow \color{blue}{c_{12}} \rightarrow \color{blue}{c_{14}} $

All tiles from the $ 1 $ -st block will have colour $ \color{red}{\textbf{1}} $ , from the $ 2 $ -nd block will have colour $ \color{blue}{\textbf{4}} $ .

It is also possible to construct a path of length $ 9 $ in this example, in which all tiles from the $ 1 $ -st block will have colour $ \color{red}{\textbf{1}} $ , from the $ 2 $ -nd block will have colour $ \color{green}{\textbf{3}} $ , and from the $ 3 $ -rd block will have colour $ \color{blue}{\textbf{4}} $ .

## 说明/提示

In the first test case, you can jump from the first tile to the last tile;

The second test case is explained in the problem statement.

## 样例 #1

### 输入

```
10
4 2
1 1 1 1
14 3
1 2 1 1 7 5 3 3 1 3 4 4 2 4
3 3
3 1 3
10 4
1 2 1 2 1 2 1 2 1 2
6 2
1 3 4 1 6 6
2 2
1 1
4 2
2 1 1 1
2 1
1 2
3 2
2 2 2
4 1
1 1 2 2```

### 输出

```
YES
YES
NO
NO
YES
YES
NO
YES
YES
YES```

# 题解

## 作者：xiazha (赞：9)

### 思路

贪心题。

本题有一个关键的转化：只有起点和终点的方块是必须经过的，所以其他方块我们可以不管。然后本题就可以分为两种情况讨论，如下。



------------


1. 起点和终点是一种颜色的方块（$c_1=c_n$）：我们将颜色为 $c_1$ 的方块统计出来，如果个数大于等于 $k$，那么就说明有可行的路径方案，因为我们可以只跳其中的 $k$ 个，剩下的不管，这样 $k$ 本身肯定是自己的倍数。

2. 起点和终点是不同颜色的方块（$c_1 \ne c_n$）：我们还是先查找颜色为 $c_1$ 的方块并统计个数，当统计中个数已经等于 $k$ 时，我们就从当前位置的下一个开始找 $c_n$，这样找到 $c_n$ 的个数有可能大于等于 $k$ 的概率就会增加，如果 $c_n$ 的个数大于等于 $k$，那么就说明有可行的路径方案，否则没有，如果连 $c_1$ 都不到 $k$ 个，那么肯定也是是没有的。



------------


### 代码
```
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[200002],cnt,id,f;
signed main()
{
	cin>>t;
	while(t--)
	{
		cnt=0,id=-1,f=0;
		cin>>n>>k;
		for(int i=1;i<=n;i++) 
		{
			if(cnt==k&&f==0) id=i,f=1;
			scanf("%d",&a[i]);
			if(a[i]==a[1]) cnt++;
		}
		if(a[1]==a[n]&&cnt>=k)
		{
			puts("YES");
			continue;
		}
		if(id==-1) puts("NO");
		else
		{
			cnt=0;
			for(int i=id;i<=n;i++)
				if(a[i]==a[n]) cnt++;
			//cout<<id<<" "<<cnt<<"\n";
			if(cnt>=k) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```


---

## 作者：WsW_ (赞：3)


### 更新
这是一篇**已通过**的题解。

- $2023.11.05$ 修改一处笔误。

请管理重新审核，谢谢！  

---

[博客链接](https://www.luogu.com.cn/blog/WsW/solution-cf1851c)  
[洛谷题面](https://www.luogu.com.cn/problem/CF1851C)  
[$\mathtt{CF}$ 题面](https://codeforces.com/contest/1851/problem/C) 

---

### 题意
一个长度为 $n$ 的数列 $c_1,c_2,\dots,c_n$，从 $c_1$ 开始，每次向右移动任意长度，最终移动到 $c_n$。设路径长度 $p$ 为到达（站在上面）的地方个数。  
要求：
1. $k\mid p$。   
2. 将路径分成若干个长度为 $k$ 的块，每个块内的 $c_i$ 相同。

先手玩题面中的例子：  
$n=14,k=3$，数列为：$1,2,1,1,7,5,3,3,1,3,4,4,2,4$。  
那么可以这样走：$1,1,1,3,3,3,4,4,4$。  
也可以这样走：$1,1,1,4,4,4$。  

显然如果对于一个可行路径 $p\div k>2$，那么我们可以将中间的一块直接跨过，不需要经过。换句话来说，当存在可行路径的时候，必定有一种可行路径，只有首尾两块。当首尾颜色相同时，可能存在 $p=k$ 的可行路径，需要特判。  
那么我们就只需要按照上面讲的模拟即可。

---

### 代码与[提交记录](https://www.luogu.com.cn/record/117826275)
```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n,k;
int a[200003];
int cntf,cntl;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		cntf=cntl=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		int j;
		for(j=1;j<=n&&cntf<k;j++){
			if(a[j]==a[1])cntf++;
		}//计算首块
		for(;j<=n&&cntl<k;j++){
			if(a[j]==a[n])cntl++;
		}//首块可行就计算尾快
		if((cntf==k&&cntl==k)||(cntf==k&&a[1]==a[n]))puts("Yes");
		else puts("No");
	}
	return 0;
}
```

---

## 作者：信息向阳花木 (赞：2)

很显然，是否可以满足条件只和第一个和最后一个方块有关。

设第一个方块的颜色为 $x$，最后一个方块的颜色为 $y$，$b_i$ 表示颜色为 $i$ 的方块数量。

想要输出 `YES`，必须满足 $b_x \ge k$ 且 $b_y \ge k$。但是，它们选择的区间还不能有交集。换句人话说，设和第一块方块成组的方块的位置分别为 $p_1, p_2, ..., p_k$，和最后一块方块成组的方块的位置分别为 $q_1, q_2, ..., q_k$。(其中 $p_1 < p_2 < ... < p_k$， $q_1 < q_2 < ... < q_k$）那么必须满足 $p_k < q_1$ 才能输出 `YES`。

**注意**：别忘了考虑 $x = y$ 的情况。若 $x=y$，只要 $b_x \ge k$ 就可以输出 `YES`。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 200010;

inline void in(int &x)
{
	x = 0; bool f = 0; char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-') f = 1;
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + (c & 15);
		c = getchar();
	}
	x = f ? -x : x;
}

inline void out(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x / 10) out(x / 10);
	putchar((x % 10) | 48);
}

int t, n, k;
int a[N], b[N];

int main()
{
	in(t);
	while (t -- )
	{
		memset(b, 0, sizeof b);
		 
		int j = 0;
		in(n); in(k);
		for (int i = 1; i <= n; i ++ )
		{
			in(a[i]);
			b[a[i]] ++;
			if(b[a[1]] == k &&j == 0) j = i + 1;
		}
		
		if(a[n] != a[1])
		{
			b[a[n]] = 0;
			for (int i = j; i <= n; i ++ ) b[a[i]] ++;
		}
		
		if(j == 0) puts("NO");
		else if(b[a[n]] >= k && b[a[1]] >= k) puts("YES");
		else puts("NO");
	}
	return 0;
}
 
 ```

---

## 作者：duchengjun (赞：1)

# 思路

由于如果要使该方案成立，则必定要满足第一个格子和最后一个格子，及第 $k$ 个与 $a_1$ 相等的数（包含 $a_1$）之后有 $k$ 个与 $a_n$ 相等的数（包含 $a_n$）。

### 漏洞

如果 $a_1$ 与 $a_n$ 相等，则只要在 $a_2$ 至 $a_{n-1}$ 中有 $k-2$ 个数与 $a_1$ 相等也可以成立。

# Code

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<string.h>

using namespace std;

const int N=2*1e5+10;

int T;
int n,k;
int c[N];

void Solve(){
	
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	int cnt1=0,tmp1=-1;
	for(int i=1;i<=n;i++)
		if(c[i]==c[1]){
			cnt1++;
			if(cnt1==k){
				tmp1=i;
				break;
			}
		}
	if(tmp1==-1){
		printf("No\n");
		return ;
	}
	if(tmp1!=-1&&c[n]==c[1]){
		printf("Yes\n");
		return ;
	}
	int cnt=0;
	for(int i=tmp1+1;i<=n;i++)
		if(c[i]==c[n])
			cnt++;
	if(cnt>=k)printf("Yes\n");
	else printf("No\n");
	return ;
	
}

int main(){
	
	scanf("%d",&T);
	while(T--){
		Solve();
	}
	return 0;
	
}
```

---

## 作者：xxx2022 (赞：1)

一道贪心题。

根据题意，我们需要在原序列中找出一条从 $1$ 到 $n$ 的路径，这条路径能被分成几个长度为 $k$ 且颜色相等的连续段。我们可以将这个问题简单化，那么这个问题就能被转化为从 $1$ 开始向后找一个颜色连续段，从 $n$ 开始向前找一个颜色相同的连续段，只要这两个连续段不相交即可，代码实现时需要注意特判。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
inline int read(){
	int f=1,w=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		w=(w<<1)+(w<<3)+(c^48);
		c=getchar();
	}
	return f*w;
}
int t;
int n,k;
int a[N];
int main(){
	t=read();
	while(t--){
		n=read();
		k=read();	
		bool fl=0;
		for(int i=1;i<=n;i++){
			a[i]=read();
			if(a[i]!=a[i-1]&&i!=1)	fl=1;
		}	
		if(!fl&&n==k){
			printf("YES\n");
			continue;
		}
		int last=a[n];
		int fir;
		int now=0;
		for(int i=n;i;i--){
			if(a[i]==last)	now++;
			if(now==k){
				fir=i;
				break;
			}	
		}
		if(now!=k){
			printf("NO\n");
			continue;
		}
		int st=a[1];
		int ls;
		now=0;
		for(int i=1;i<=n;i++){
			if(a[i]==st)	now++;
			if(now==k){
				ls=i;
				break;
			}
		}
		if(st==last){
			now=0;
			for(int i=2;i<n;i++){
				if(a[i]==st)	now++;
			}
			if(now+2>=k)	printf("YES\n");
			else	printf("NO\n");
			continue;
		}
		if(now!=k){
			printf("NO\n");
			continue;
		}
		if(ls<=fir){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
}

```

---

## 作者：NBest (赞：1)

## 题意：
你可以按顺序取出包含若干个色块的序列，序列必须包含第一块和最后一块，然后将其分割成若干个数量均为 $k$ 的部分，每个部分的颜色必须一样，不同部分之间颜色可以一样，问你能否找到这样一个序列。
## 思路：
我们从第一块和最后一块必须选入手，实际上我们也只需要考虑最前一段和最后一段是否能顺序凑到 $k$ 个即可。

因为无论中间如何选，最后选出的序列必然包含首尾段，所以我们实际上可以忽略中间的部分，用两个指针分别从前往后和从后往前扫一遍，判断前面和后面的段是否可以有超过 $k$ 个颜色相同即可。

注意一些特判，比如当首尾颜色相同时只需要一段连起来即可。
## $Code$
```cpp
int T,n,c[200005],k;
bool check(){
    int l,r,tl=0,tr=0;
    for(r=1;r<=n;r++){
        if(c[r]==c[1])tr++;
        if(tr==k)break;
    }
    if(tr<k)return 0;
    for(l=n;l;--l){
        if(c[l]==c[n])tl++;
        if(tl==k)break;
    }
    if(tl<k)return 0;
    if(c[1]==c[n])return 1;
    if(r>l)return 0;
    return 1;
}
int main(){
    T=read();
    while(T--){
        n=read(),k=read();
        for(int i=1;i<=n;i++){
            c[i]=read();
        }
        if(check())puts("YES");
        else puts("NO");
    }
}
```

---

## 作者：Zkl21 (赞：1)

## 题目大意
给定一条由 $n$ 个瓷砖拼成的小路，每一块瓷砖都有一种颜色 $c_i$，同时你可以选定其中的某些瓷砖成为你走的路径，给定一个长度 $k$，表示一组瓷砖中有 $k$ 块，求是否存在一条路径，满足：

1. 路径起点为 $a_1$，终点为 $a_n$。
2. 路径由多个组构成，同时分出的每一组在所有选定的瓷砖中是连续的，不存在其中某一块瓷砖不属于任何一组，并且对于相同组中的每一块瓷砖颜色都相同。

## 思路

首先统计一下每一种颜色的位置。考虑一下在哪些情况下找不到合法路径。

显然当第一块或者最后一块相同颜色瓷砖的数量不够凑出一组时，找不到合法路径。

排除以上两种情况后，如果起点瓷砖和终点瓷砖的颜色相同，我们只要选出起点瓷砖和重点瓷砖以及中间部分相同颜色的瓷砖凑够 $k$ 个即可，显然可以找到合法路径。

如果颜色不同，为简化问题，我们直接贪心的找起点的一组和终点的一组共两组瓷砖即可，由于要保证每一组中的瓷砖在所有选出的瓷砖中是连续的，因此我们最后检验一下起点组中的最后一块和终点组中的第一块的位置是否合法即可。
## 代码
```cpp
#include<iostream>
#include<vector>
using namespace std;
const int N=2e5+10;
int n,k,a[N];
vector<int>color[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)color[i].clear();//清空颜色
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			color[a[i]].push_back(i);//记录每一种颜色的位置
		}
		if(color[a[1]].size()<k||color[a[n]].size()<k)//块数不够组成一组，一定不合法
		{
			puts("NO");
			continue;
		}
		if(a[1]!=a[n]&&color[a[1]][k-1]>color[a[n]][color[a[n]].size()-k])
		{//起点组最后一块的位置在终点组第一块的位置后面，由于位置不连续，因此一定无解
			puts("NO");
			continue;
		}
		puts("YES");
	}
	return 0;
}
```

---

## 作者：___w (赞：1)

### [CF1851C Tiles Comeback](https://www.luogu.com.cn/problem/CF1851C)

#### 题意简述
~~题目太长了，看看别的题解吧。~~

#### 题目分析
因为这条路径必定起点为 $1$，终点为 $n$，所有这条路径至少要有 $k$ 个与 $1$ 颜色相同的点，有 $k$ 个与 $n$ 颜色相同的点。而路径中间的颜色我们可以不要。问题就转化为是否有条路径满足开头和结尾分别有 $k$ 个颜色相同的点。

这里我的实现方式有些奇怪。考虑断点 $i$，判断 $[1,i]$ 中 $c_1$ 的个数是否大于等于 $k$，以及 $(i,n]$ 中 $c_n$ 的个数是否大于等于 $k$。正好 $1\le c_i\le n$，那我也没办法，只好开两个桶记录次数了。

还要注意 $c_1=c_n$ 的情况，特判下。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
int t, n, k, a[N], f[N], g[N];

bool solve() {
	if (a[1] == a[n] && g[a[1]] >= k) return 1;
	for (int i = 1; i <= n; ++i) {
		++f[a[i]], --g[a[i-1]];
		if (f[a[1]] >= k && g[a[n]] >= k) return 1;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin >> t;
	while (t--) {
		memset(f, 0, sizeof(f));
		memset(g, 0, sizeof(g));
		cin >> n >> k;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
			++g[a[i]];
		}
		if (solve()) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}
```

---

## 作者：wangjingtian1234 (赞：1)

# [洛谷题目](https://www.luogu.com.cn/problem/CF1851C) 

# [CF题目](https://codeforces.com/contest/1851/problem/C)

### 思路分析

显然，如果 $k = 1$，一定满足，因为你可以先走 $c_1$，再走到 $c_n$。

如果 $c_1 = c_n$，只需要走长度为 $k$，颜色为 $c_1$ 的一块，判断 $c$ 数组中是否有 $\ge k$ 个数等于 $c_1$ 即可。

如果 $c_1 \ne c_n$，需要先走长度为 $k$，颜色为 $c_1$ 的一块，再走长度为 $k$，颜色为 $c_n$ 的一块。先从 $c_1$ 开始，找 $k$ 个等于 $c_1$ 的数，再从刚刚找到最后一个数的下一个开始，找 $k$ 个等于 $c_n$ 的数，当然 $c_n$ 也算。如果都能找到，显然可以，不然不能。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n, k, a[200010], i, num, lll;

void Solve()
{
	cin >> n >> k;
	for (i = 1; i <= n; i++)
	{
		cin >> a[i];
	}
	if (k == 1) 
	{
		cout << "YES" << endl;
		return;
	}
	if (a[1] == a[n])
	{
		num = 2; if (num == k) {cout << "YES" << endl; return;}
		for (i = 2; i < n; i++)
		{
			if (a[i] == a[1])num++;
			if (num == k) 
			{
				cout << "YES" << endl;
				return;
			}
		}
		cout << "NO" << endl;
		return;
	}
	lll = a[1]; num = 1;
	for (i = 2; i <= n; i++)
	{
		if (a[i] == lll) num++;
		if (num == k) break;
	}
	lll = a[n]; num = 1;
	for (i = i + 1; i < n; i++)
	{
		if (a[i] == lll) num++;
		if (num == k) 
		{
			cout << "YES" << endl;
			return;
		}
	}
	cout << "NO" << endl;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	long long T; cin >> T;
	while (T--) Solve();
	return 0;
}
```

Thank you for reading this solution！

---

## 作者：Dream__Sky (赞：1)

题意简述：

现在有一串 $n$ 瓷砖和一个数字 $k$。瓦片从左到右依次编号，第 $i$ 块瓦片的颜色是 $c_i$。

你站在第 $1$ 块瓷砖上，可以向右跳任意数量的瓷砖，最终要到达第 $n$ 块瓷砖。你可以得到一条长度为 $p$ 的路径。路径的长度就是你所经过的瓦片数。

路径要求：

- 路径被划分为长度正好为 $k$ 的几块，即 $p \mid k$。
- 每个区块中的瓦片颜色相同。

分析：

下文设 $c$ 为颜色的数组。

对于这一些构造题（差不多），我们要找到特殊的构造方案。

因为 $c_1$ 与 $c_n$ 是必须要经过的，所以我们只需要考虑两块。即，$c_1$ 作为起点的一块，$c_n$ 作为终点的一块。中间的其它颜色不必考虑，它们对最终答案没有影响，最终还是要看起点与终点。

我们从头开始找 $k$ 个与 $c_1$ 颜色相同的瓷砖，最后一个的位置记录为 $p_1$。再从最后开始找 $k$ 个与 $c_n$ 颜色相同的瓷砖，最后一个的位置记录为 $p_2$。

如果 $p_1 < p_2$ 那么方案可行，中间一段可以直接从 $p_1$ 跳过去，反之就不行。

还有一种特殊的情况，就是 $c_1=c_n$，那么我们只要看一共有没有 $k$ 个 $c_1$，如果有，那么是可行的。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,k,a[200001];
string work()
{
	int p1=0,p2=0;
	for(int i=1,x=0;i<=n;i++)
	{
		if(a[i]==a[1]) x++;
		if(x==k) {p1=i;break;} 
	} 
	for(int i=n,x=0;i>=1;i--) 
	{
		if(a[i]==a[n]) x++;
		if(x==k) {p2=i;break;} 
	}//寻找两个位置
	if(p1>p2||!p1||!p2) return "No\n";
	else return "Yes\n";//判断
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		if(a[1]!=a[n])
			cout<<work();//普通情况
		else 
		{
			int x=0; 
			for(int i=1;i<=n;i++)if(a[i]==a[1]) x++;//特殊情况
			if(x>=k) cout<<"Yes\n";
			else cout<<"No\n";
		}
		
	}
	return 0;
}
 
```



---

## 作者：sz_jinzikai (赞：0)

[洛谷传送门](/problem/CF1851C) &[CF 传送门](//codeforces.com/problemset/problem/1851/C)
# 题目大意
有 $n$ 块瓷砖和一个数字 $k$，瓷砖从左到右编号，第 $i$ 个瓷砖的颜色为 $c_i$。如果你站在第 $1$ 块瓷砖上，开始向右跳任意数量的瓷砖，你可以得到一条长度为 $p$ 的路径，路径的长度就是你经过瓷砖的数量。请判断是否有可能得到一条长度为 $p$ 的路径，使得:
1. 它在 $n$ 号瓷砖处结束且 $p$ 能被 $k$ 整除；
1. 每组瓷砖都由 $k$ 块瓷砖组成；
1. 每组中的瓷砖颜色相同。

# 思路
这题其实很简单，只要记录从前往后数第 $k$ 块和 $c_0$ 颜色相同的瓷砖下表 $l$ 和从后往前数第 $k$ 块和 $c_{n-1}$ 颜色相同的瓷砖下表 $r$，看看有没有“碰头”了，即判断 $l<r$ 是否成立即可。当然，如果 $c_0=c_{n-1}$ 的话就要另当别论了，只要看有几个数和 $c_0$ 相等即可。
# 代码
```cpp
//CF1851C
# include <bits/stdc++.h> //万能头 
using namespace std;
int t, n, a[200005], k, suml, sumr, nowl, nowr;
int main () {
	cin >> t;
	while (t --) { //多组数据通用写法
		cin >> n >> k;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		if (a[0] == a[n - 1]) { //特判
			suml = 0; //多组数据要清空
			for (int i = 0; i < n; ++ i)
				suml += (a[i] == a[0]);
			cout << (suml < k ? "NO\n" : "YES\n"); //三目表达式，不懂自行 bdfs
			continue ; //跳转到下一轮循环
		}
		suml = sumr = nowl = 0, nowr = n - 1; //多组数据要清空
		while (nowl < n && suml < k) {
			if (a[nowl] == a[0])
				++ suml;
			++ nowl;
		}
		while (~nowr && sumr < k) {
			if (a[nowr] == a[n - 1])
				++ sumr;
			-- nowr;
		}
		-- nowl, ++ nowr; //别忘了还要退一个回去
		cout << (nowl < nowr ? "YES\n" : "NO\n"); //三目表达式，不懂自行 bdfs
	}
	return 0; //结束程序
}
```

---

## 作者：_Only_this (赞：0)

### CF1851C Tiles Comeback 题解

------------

好吧，我承认是我菜，又是被 wyq 薄纱的一场 cf。

一眼觉得这题好复杂，没有头绪，但是手搓一下样例就会发现，无非就两种情况。

一种是头和尾颜色一样的，一种是头和尾颜色不一样的。

先说第一种，如果颜色一样，那么统计这种颜色出现的次数是否 $\geq k$ 即可。

再说第二种，如果颜色不一样，就看两种颜色出现 $k$ 次的位置，一个从左到右枚举，一个从右到左枚举，如果两个位置交叉了，说明不存在可能跳到对面的情况，反之输出 Yes。

贴个代码。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int T,n,k;
int a[maxn];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		if(a[1]!=a[n]){
			int loc1=n+1,loc2=0;
			map<int,int>mp1,mp2;
			for(int i=1;i<=n;i++){
				mp1[a[i]]++;
				if(mp1[a[1]]==k){
					loc1=i;
					break;
				}
			}
			for(int i=n;i>=1;i--){
				mp2[a[i]]++;
				if(mp2[a[n]]==k){
					loc2=i;
					break;
				}
			}
			printf("%s\n",(loc1<loc2) ? "Yes" : "No");
		}
		else{
			map<int,int>mp;
			bool flag=0;
			for(int i=1;i<=n;i++){
				mp[a[i]]++;
				if(mp[a[1]]==k){
					printf("%s\n","Yes");
					flag=1;
					break;
				}
			}
			if(!flag)
				printf("%s\n","No");
		}
	}
	return 0;
}
```


---

## 作者：xzyg (赞：0)

题意：

```
Vlad记得他有一系列 n 个瓷砖和一个数字 k。
瓷砖从左到右编号，第 i 个瓷砖的颜色为 ci。

如果你站在第一块瓷砖上，开始向右跳任意数量的瓷砖,
你可以得到一条长度为 p 的路径，
路径的长度就是你经过瓷砖的数量。

弗拉德想看看是否有可能得到一条长度为 p 的路径，使得:

1.它在索引为n的瓦片处结束；p能被k整除；
2.路径被分成长度正好为k的块；
3.每个区块中的瓷砖具有相同的颜色，相邻区块中的颜色不一定不同。
```

~~写到一半写不下去了，于是用的机翻。~~

考虑最短路径怎么走：显然是 $ c_1 $ 为一个长度为 $ k $ 的区间左端点，$ c_n $ 为一个长度为 $ k $ 的区间的右端点，最短路径只有这一个或两个区间（因为有 $ c_1 = c_n $ 的情况）。

直接判定最短路径是否存在即可，因为如果最短的路径不存在，长的路径更不可能存在。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define MAXN 200010
using namespace std;
 
ll read(){
	char ch=getchar();
	ll s=0, w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w; 
}
 
ll n, k;
ll c[MAXN];
 
int main(){
	ll T = read();
	
	while(T--){
		n = read(), k = read();
		for(ll i = 1; i <= n; i++){
			c[i] = read();
		}
		
		ll cnt1 = 0, pos = 0;
		
		bool f1 = false, f2 = false;
		
		for(ll i = 1; i <= n; i++){
			if(c[i] == c[1]){
				cnt1++;
				pos = i;
				if(cnt1 == k){
					f1 = true;
					break;
				}
			}
		}
		
		if(c[1] == c[n] && f1){
			cout << "YES\n";
			continue;
		}
		
		ll cnt2 = 0;
		for(ll i = n; i >= pos; i--){
			if(c[i] == c[n]){
				cnt2++;
				if(cnt2 == k){
					f2 = true;
					break;
				}
			}
		}
		
		cout << (f1 && f2 ? "YES" : "NO") << endl;
	}
	return 0;
}
```


---

## 作者：Wf_yjqd (赞：0)

又掉大分哩。

好吧，这个题也很水啊。

------------

考虑忽略中间过程，考虑合法的最低要求。

如果两端颜色相同，只需要这个颜色出现 $\ge k$ 次即可。

否则我们要使其经过左端点后同颜色的 $k$ 个后，能向右跳到右端点同色的倒数的 $k$ 个。

相当于第 $k$ 个左端点同色的位置要小于倒数第 $k$ 个跟右端点同色的位置。

$\operatorname{O}(n)$ 判断即可。

------------

这种题代码是真的没必要放。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+84;
int T,n,k,c[maxn],ans1,ans2,cnt;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%d",&c[i]);
        if(c[1]==c[n]){
            cnt=0;
            for(int i=1;i<=n;i++)
                if(c[i]==c[1])
                    cnt++;
            puts(cnt>=k?"Yes":"No");
            continue;
        }
        int i;
        cnt=0;
        for(i=1;i<=n;i++)
            if(c[i]==c[1]){
                cnt++;
                if(cnt==k)
                    break;
            }
        cnt=0;
        for(;i<=n;i++)
            if(c[i]==c[n])
                cnt++;
        puts(cnt>=k?"Yes":"No");
    }
    return 0;
}
```


---

## 作者：MornStar (赞：0)

# CF1851C Tiles Comeback 题解

## 题目大意

$T$ 组数据。

每组数据给定一个长度为 $n$ 序列 $a$ 和一个整数 $k$，序列中的每个元素 $a_i$ 都有一个颜色 $c_i$，问是否能从中选出一个子序列（即选出的元素可以在原序列中不相邻），使得：

- 原序列第一个元素为选出的序列的第一个元素，原序列最后一个元素为选出的序列的最后一个元素。

- 选出的序列的长度为 $k$ 的倍数

- 序列可以分成若干个长度为 $k$ 的连续的块，使得每个块里的元素颜色相同。

## 思路

先小小地贪一下心，我们可以发现，除了第一个元素和最后一个元素的颜色，其他颜色都是没有意义的，我们只需要统计首尾的颜色的个数，而且也只需要统计 $k$ 个（因为首和尾的颜色都只选 $k$ 个，也可以满足条件）。

记从前往后第 $k$ 个跟第一个元素同一颜色的数的下标为 $n$，从后往前第 $k$ 个跟最后一个元素同一颜色的数的下标为 $m$。

如果 $m<n$，则仍然不满足条件，因为将新序列分成两块后并不能使每个块里的元素颜色相同，当然，如果序列中根本没有这么多与首尾相同颜色的元素的话，肯定也不满足条件。

最后，特判一下首尾颜色相同的情况就行了。

## code

```cpp
//by MornStar
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int T,n,k;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		for(int i=1;i<=n;i++)	cin>>a[i];
		int j,r,cnt=0;
		for(j=1;j<=n;j++){
			if(a[j]==a[1])	cnt++;
			if(cnt==k)	break;
		}
		if(cnt<k){
			cout<<"no\n";
			continue;
		}else if(a[1]==a[n]){
			cout<<"yes\n";
			continue;
		}
		cnt=0;
		for(r=n;r>=1;r--){
			if(a[r]==a[n])	cnt++;
			if(cnt==k)	break;
		}
		if(cnt<k||r<=j)	cout<<"no\n";
		else	cout<<"yes\n";
	}
}
```


---

