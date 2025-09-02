# Safe

## 题目描述

### 题意

给定 $m$ 个串，由 $0$ 或者 $1$ 组成，定义 $num_i$ 表示这个字符串与标准字符串不同的个数。

## 说明/提示

$6 \le n \le 35$，$1 \le m \le 10$。

保证 $num_i \le 5$。

## 样例 #1

### 输入

```
6 2
000000 2
010100 4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
6 3
000000 2
010100 4
111100 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
6 3
000000 2
010100 4
111100 2
```

### 输出

```
1
```

# 题解

## 作者：Marsrayd (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/CF47D)

## 前置芝士
- 只有 ```dfs```，真是道大水题。

## $\texttt{solution：}$

### 题意简述（貌似越说越困难）：
给定 $m\ (1\le m\le 10)$ 个长度为 $n\ (1\le n\le 35)$ 的 01 串以及它们与正确 01 串不同的字符个数(为了方便，我接下来叫它$wr_i$)，求正确 01 串的可能情况个数。
### 思路：
看到数据范围 $1\le n\le 35$，$1\le m\le 10$ 如此之小，不难想到 ```dfs```。

我们可以通过 ```dfs``` 枚举“正确”的 01 串，最后判断符不符合给出的 $m$ 个条件。

于是，我们快速地写完了代码。

[$\texttt{TLE CODE}$](https://www.luogu.com.cn/paste/e6m5snpv)

时间复杂度：$\mathcal{O}(2^n\times m\times n)$

显然，直接搜索肯定会超时，但我们又发现正确 01 串是很少的，所以我们只要增加一个剪枝就可以大幅度提升时间复杂度。

具体如何剪枝呢？

我们可以在 ```dfs``` 时，用数组 $d$ 维护它与题目给出的 $m$ 个 01 串不相同的字符个数。如果在某一时刻，$d_i>wr_i$ 那么这个 01 串就一定不可能是正确 01 串。

$\texttt{AC CODE}$
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAX=40;
int n,m,ans,d[MAX],wr[MAX],tmp[MAX],str[MAX][MAX];
char s[MAX][MAX];
bool check()
{
	int cnt=0;
	for(int i=1;i<=m;i++)
	{
		cnt=0;
		for(int j=1;j<=n;j++)
		{
			if(tmp[j]^str[i][j]) ++cnt;
		}
		if(cnt!=wr[i]) return false;
	} 
	return true;
}
void dfs(int step)
{
	if(step==n)
	{
		ans+=check();
		return;
	}
	bool flag0=1,flag1=1;
	for(int i=1;i<=m;i++)
	{
		if(str[i][step+1]==1) d[i]++;
		if(d[i]>wr[i]) flag0=0;
	}
	if(flag0)
	{
		dfs(step+1);
	}
	for(int i=1;i<=m;i++)
	{
		if(str[i][step+1]==1) d[i]--;
		else d[i]++;
		if(d[i]>wr[i]) flag1=0;
	}
	if(flag1)
	{
		tmp[step+1]=1;
		dfs(step+1);
		tmp[step+1]=0;
	}
	for(int i=1;i<=m;i++)
	{
		if(str[i][step+1]==0) d[i]--;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%s%d",s[i]+1,&wr[i]);
		int len=strlen(s[i]+1);
		for(int j=1;j<=len;j++)
		{
			str[i][j]=s[i][j]-'0';
		}
	}
	dfs(0);
	printf("%d",ans);
	return 0;
}
```
时间复杂度：比较玄学（因为使用了剪枝）

~~如果你有收获的话请给我点个赞吧 qwq 。~~

---

## 作者：Lavande (赞：1)

# 算法

深度优先搜索

# 题目

[rt，LINK！](https://www.luogu.com.cn/problem/CF47D)

# 思路

很明显这是一道深搜题。最简单的思路就是对于每个字符，都有 $0$ 和 $1$ 两种情况，所以我们只需要枚举出所有的可能性再判断是否满足要求就行了。但是如果只暴力枚举的话就会**超时**，所以我们要用**剪枝**来优化程序。

问题来了，我们该如何剪枝呢？

在当前搜索的字符串不同的字符数量已经**超过**指定数量时，这个字符串就**不可能**是正确的，所以直接结束就可以了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int c[25],n,m,ans;
string str[25];
bool f(string s){//判断 
	for(int i=1;i<=m;i++){
		int sum=0;
		for(int j=0;j<str[i].size();j++){
			if(s[j]!=str[i][j]) sum++;
		}
		if(sum!=c[i]) return false;
	}
	return true;
}
void dfs(int ans,int cnt,string s){
	if(ans==n){//达到长度 
		if(f(s)){
			ans++;
		}
		return ;
	}
	if(cnt<m){//如果超过的数量已经满足第一个的要求，就不能与第一个字符不同了
		if(str[1][ans]=='0'){
			dfs(ans+1,cnt+1,s+"1");
		}
		else {
			dfs(ans+1,cnt+1,s+"0");
		}
	}
	//搜索 
	if(str[1][ans]=='0'){
		dfs(ans+1,cnt,s+"0");
	}
	else{
		dfs(ans+1,cnt,s+"1");
	}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(false);
	//输入 
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>str[i]>>c[i];
	}
	dfs(0,0,"");
	cout<<ans;
	return 0;
} 
```


---

## 作者：XXh0919 (赞：1)

~~一道大大的 dfs 水题~~

# CF47D Safe 题解

### 题意

给定 $m$ 个长度为 $n$ 的 01 字符串和一个表示这个字符串与标准字符串不同的个数的数 $num_i$，问你共有多少种可能的标准字符串。

### 正文

这道题其实并不难，一个 dfs 就可以解决的题，只不过要一些剪枝。

怎样剪枝呢？我们知道因为不同的字符数量是不会减少的，所以我们可以在当前搜索的字符串不同的字符数量已经超过输入的数量时，就判定这个字符串不可能是标准的的。

**Code**:

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[15];
long long n,m,num[15],ans;
void dfs(int size_now,string now)//size_now:当前字符串长度  now:当前字符串
{
	for(int i=1;i<=m;i++)
	{
		int sum=0;
		for(int j=0;j<size_now;j++)
		{
			if(s[i][j]^now[j])//如果不同 
			   sum++;//+1
			if(sum>num[i])return;//超出限制则退出 
		}
	}
	if(size_now==n)
	{
		for(int i=1;i<=m;i++)
		{
			int sum=0;
			for(int j=0;j<size_now;j++)
			{
				if(s[i][j]^now[j])//如果不同 
				   sum++;//+1
			}
			if(sum^num[i])return;//超出限制则退出 
		}
		ans++;//符合要求
		return;
	}
	dfs(size_now+1,now+"0");//长度+1，字符串往后移一位 
	dfs(size_now+1,now+"1");//同上 
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	   cin>>s[i]>>num[i];
	dfs(0,"");
	cout<<ans<<endl;
	return 0;
} 
```
管理员求过！！！！！

（补充：借鉴了用户 [LiaoYF](https://www.luogu.com.cn/user/633466) 的思路）

---

## 作者：zjjc1104111 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF47D)

# 思路

这题一看就是深搜。

首先，对于每个字符，都有 ${0}$ 和 ${1}$ 两种情况，我们只需要枚举出所有的可能性再判断是否满足要求就行了。但由于字符串的长度有一点大，所以我们需要剪枝。

那我们该如何剪枝呢？

不难发现，我们可以对于其中一个字符串进行判断，如果当前我们构造出的字符串已经和该字符串不同的字符超过了指定数量，那么便可以直接结束。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int num[11],n,m,ans;
string str[11];
int f(string s){
	for(int i=1;i<=m;i++){
		int cnt=0;
		for(int j=0;j<str[i].size();j++){
			if(s[j]!=str[i][j]) cnt++;
		}
		if(cnt!=num[i]) return 0;
	}
	return 1;
}
void dfs(int step,int cnt,string s){//构造字符串，cnt表示与第一个字符串不同字符的个数
	if(step==n){
		if(f(s)) ans++;//如果满足要求，ans++
		return ;
	}
	if(cnt<m){//如果超过的数量已经满足第一个的要求，就不能与第一个字符不同了
		if(str[1][step]=='0') dfs(step+1,cnt+1,s+"1");
		else dfs(step+1,cnt+1,s+"0");
	}
	if(str[1][step]=='0') dfs(step+1,cnt,s+"0");
	else dfs(step+1,cnt,s+"1");
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>str[i]>>num[i];
	dfs(0,0,"");
	cout<<ans;
	return 0;
} 
```


---

## 作者：fp0cy1tz6mn4rd_ (赞：0)

# CF47D 题解

[洛谷传送门](https://www.luogu.com.cn/problem/CF47D)

[CF 传送门](https://codeforces.com/problemset/problem/47/D)

[更好的阅读体验](https://www.luogu.com.cn/blog/Death-Basic/solution-cf47d)

## 题意简述

给定 $m$ 个由 $1$ 和 $0$ 组成的字符串，并给出这个字符串与标准字符串相差的字符个数，求标准字符串的所有可能性。

## 思路

暴力 ```dfs```，水题一道。

数据范围很水，```dfs``` 足够，但是要剪枝，否则会 ```TLE```。

### 知识点：什么是 ```dfs```

~~如果你是已经会 ```dfs``` 以及其剪枝方法的神犇，请跳过这段。~~

```dfs``` 全称深度优先搜索 ```Depth-First Search```，主要思想是递归求解问题的思路。就好比你走迷宫的时候，在一条路上走到底，不行就换一条路。知道了思想，```dfs``` 就变得很简单了。

#### ```dfs``` 模板

```cpp
void dfs(当前状态){
    if(当前状态 == 目的状态){
        ···
    }
    for(寻找新状态){
        if(状态合法){
            vis[访问该点]；
            dfs(新状态);
            ?是否需要恢复现场->vis[恢复访问]	//回溯
        } 
    }
}
```

#### 剪枝

有时候，我们会发现某个节点对应的子树的状态都不是我们要的结果，那么我们其实没必要对这个分支进行搜索。这就是剪枝。

剪枝的原则：
- 正确性
- 准确性
- 高效性

我们要尽可能让剪枝的时间复杂度低，否则可能会出现这样的情况：原本的算法效率其实比较高，这么一剪枝，每次判断一下，效率反倒变低了。



## 思路

**好了，我们继续讲题目思路**

所以我们可以从字符串的第一个字符开始，每次填充一个字符，如果不符合要求就回退一步，寻找下一种方法。

什么时候需要判断方案可行呢？我们不难发现，如果这个字符串的长度 $\neq n$，那么这个方案是不可能可行的。

这时候还没完，会 ```TLE```。我们需要剪枝。如何剪枝？

如果现在的标准字符串与任意一个字符串相差超过 $num_i$，那么这个 “标准字符串” 肯定不会是解。

**代码不写了，我敲得累死了**

---

## 作者：zhang_kevin (赞：0)

目前其他题解全是 `dfs` 的，这里给出一种时间复杂度较大但很好理解的方法。

# Solution

我们可以先枚举出**符合第一个输入字符串要求**的全部字符串，然后一个一个判断。

当然，这种方法是会超时的（除非运气好，CF 评测机喜欢你）。

于是开始优化：

我们可以想到，$num_i$ 与 $n$ 的差越小，符合要求的数量就越少。

因此我们可以先用 `sort` 进行排序，然后计算。

每次计算枚举出 $num_1$ 个位置，将这些位置上的字符串取反，判断得到的字符串是否可以符合所有字符串的要求即可。

# Code


```cpp
#include<bits/stdc++.h>
#define f(ch) (ch=='0'?'1':'0')
using namespace std;
struct Node{
	string s;
	int num;
}a[11];
int n, m;
inline bool cmp(Node x, Node y){
	return min(x.num, n-x.num) < min(y.num, n-y.num);
}
inline int dif(string s1, string s2){
	int res = 0;
	for(int i = 0; i < min(s1.size(), s2.size()); i++){
		if(s1[i] != s2[i]) res++;
	}
	return res;
}
inline bool check(string s){
	for(int i = 1; i <= m; i++){
		if(dif(s, a[i].s) != a[i].num) return false;
	}
	return true;
}
int main(){
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		cin >> a[i].s >> a[i].num;
	}
	sort(a+1, a+1+m, cmp);
	int p = a[1].num, ans = 0;
	string str = a[1].s;
	if(p == 0){
		ans += check(str);
	}else if(p == 1){
		for(int i = 0; i < n; i++){
			str[i] = f(str[i]);
			ans += check(str);
			str[i] = f(str[i]);
		}
	}else if(p == 2){
		for(int i = 0; i < n; i++){
			for(int j = i + 1; j < n; j++){
				str[i] = f(str[i]);
				str[j] = f(str[j]);
				ans += check(str);
				str[i] = f(str[i]);
				str[j] = f(str[j]);
			}
		}
	}else if(p == 3){
		for(int i = 0; i < n; i++){
			for(int j = i + 1; j < n; j++){
				for(int k = j + 1; k < n; k++){
					str[i] = f(str[i]);
					str[j] = f(str[j]);
					str[k] = f(str[k]);
					ans += check(str);
					str[i] = f(str[i]);
					str[j] = f(str[j]);
					str[k] = f(str[k]);
				}
			}
		}
	}else if(p == 4){
		for(int i = 0; i < n; i++){
			for(int j = i + 1; j < n; j++){
				for(int k = j + 1; k < n; k++){
					for(int l = k + 1; l < n; l++){
						str[i] = f(str[i]);
						str[j] = f(str[j]);
						str[k] = f(str[k]);
						str[l] = f(str[l]);
						ans += check(str);
						str[i] = f(str[i]);
						str[j] = f(str[j]);
						str[k] = f(str[k]);
						str[l] = f(str[l]);
					}
				}
			}
		}
	}else{
		for(int i = 0; i < n; i++){
			for(int j = i + 1; j < n; j++){
				for(int k = j + 1; k < n; k++){
					for(int l = k + 1; l < n; l++){
						for(int z = l + 1; z < n; z++){
							str[i] = f(str[i]);
							str[j] = f(str[j]);
							str[k] = f(str[k]);
							str[l] = f(str[l]);
							str[z] = f(str[z]);
							ans += check(str);
							str[i] = f(str[i]);
							str[j] = f(str[j]);
							str[k] = f(str[k]);
							str[l] = f(str[l]);
							str[z] = f(str[z]);
						}
					}
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：Zhhhy09 (赞：0)

## 题目大意：

给定 $m$ 个长度为 $n$ 的 $01$ 字符串和一个表示这个字符串与标准字符串不同的个数的数 $num$，问你共有多少种可能的标准字符串。

## 算法：

dfs 加剪枝。

剪枝:通过判断是否标准。

最后用 $ans$ 记录并输出。

## 代码：
```c

#include<bits/stdc++.h>
using namespace std;
string s[16];
int n,m,a[16],ans;//定义
void dfs(int q,string now){
	for(int i=1;i<=m;i++){
		int sum=0;
		for(int j=0;j<q;j++){
			if(s[i][j]!=now[j])sum++;
			if(sum>a[i])return;//最重要的剪枝。
		}
	}
	if(q==n){//判断是否为标准。
		for(int i=1;i<=m;i++){
			int sum=0;
			for(int j=0;j<q;j++){
				if(s[i][j]!=now[j])sum++;
			}
			if(sum!=a[i])return;
		}
		ans++;
		return;
	}
	dfs(q+1,now+"0");
	dfs(q+1,now+"1");//dfs中最重要的递归。
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>s[i]>>a[i];//输入。
	}
	dfs(0,"");//调用。
	cout<<ans;
	return 0;
}
```


---

## 作者：LiaoYF (赞：0)

## CF47D Safe题解
[传送门](https://www.luogu.com.cn/problem/CF47D)

从时限和范围一看就是一个```DFS```的题目，比较水，最多评黄。但是需要剪枝，否则会[TLE](https://codeforces.com/contest/47/submission/169028263)。

所以，怎么剪枝呢？**在当前搜索的字符串不同的字符数量已经超过输入的数量时，这个字符串就不可能是正确的，因为不同的字符数量不会减少。**

代码还是比较短的。
## AC代码
```cpp
#include<iostream>
#include<string>
using namespace std;
string s[15];
int n,m,a[15],ans;
void dfs(int k,string now){//k:当前长度,now:当前字符串
	for(int i=1;i<=m;i++){//剪枝部分
		int sum=0;
		for(int j=0;j<k;j++){
			if(s[i][j]!=now[j])sum++;
			if(sum>a[i])return;
		}
	}
	if(k==n){//长度达到n
		for(int i=1;i<=m;i++){
			int sum=0;
			for(int j=0;j<k;j++){
				if(s[i][j]!=now[j])sum++;
			}
			if(sum!=a[i])return;
		}
		ans++;//符合要求
		return;
	}
	dfs(k+1,now+"0");//搜索
	dfs(k+1,now+"1");
}
int main(){//简单的主函数
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>s[i]>>a[i];
	}
	dfs(0,"");
	cout<<ans;
	return 0;
}
```

---

## 作者：Allanljx (赞：0)

## 题意

有 $m$ 个串，由 $0$ 或 $1$ 组成，每个串有 $n$ 个数。对于每个串，都会给定一个数 $num_i$ 表示当前这个字符串与标准字符串有多少个字符不一样，问有多少种可能的标准字符串。

### 输入描述

第一行两个数 $n$ 和 $m$，接下来 $m$ 行每行一个串和 $num_i$ 。

### 输出描述

一个数 $ans$ 表示有多少种可能的标准字符串。

## 思路

因为 $n$ 比较小，所以我们可以用深搜，但是肯定要剪枝，所以当现在与任何一个字符串不同的字符超过 $num_i$ 时就可以返回。当搜完后与每个给定的字符串比对，查看是否有恰好 $num_i$ 个字符不同。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans;
string s[15];
char c[105];
int num[15];
bool check(int x)
{
	for(int i=1;i<=m;i++)
	{
		int sum=0;
		for(int j=0;j<x;j++) if(c[j]!=s[i][j]) sum++;
		if(sum>num[i]) return 1;//当不同的字符超过num[i]时，剪枝
	}
	return 0;
}
void dfs(int x)
{
	if(check(x)) return;//剪枝
	if(x==n)
	{
		int f=0;
		for(int i=1;i<=m;i++)
		{
			int sum=0;
			for(int j=0;j<n;j++)
				if(c[j]!=s[i][j]) sum++;
			if(sum!=num[i])//只有当不同的字符数量等于每个num[i]时，才是标准字符串
			{
				f=1;
				break;
			}
		}
		if(!f) ans++;
		return;
	}
	c[x]='0';
	dfs(x+1);
	c[x]='1';
	dfs(x+1);
	return;
}
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>s[i]>>num[i];
	}
	dfs(0);
	cout<<ans<<endl;
}
```



---

