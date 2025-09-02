# Anfisa the Monkey

## 题目描述

Anfisa the monkey learns to type. She is yet unfamiliar with the "space" key and can only type in lower-case Latin letters. Having typed for a fairly long line, Anfisa understood that it would be great to divide what she has written into $ k $ lines not shorter than $ a $ and not longer than $ b $ , for the text to resemble human speech more. Help Anfisa.

## 样例 #1

### 输入

```
3 2 5
abrakadabra
```

### 输出

```
ab
rakad
abra
```

## 样例 #2

### 输入

```
4 1 2
abrakadabra
```

### 输出

```
No solution
```

# 题解

## 作者：Misaka_Mik0t0 (赞：4)

看到题目等级与‘E’题时，不要惊呆，也不要想太多！实际难度其实并不高，不值得用dp等方法做。

分成 $k$ 段，每段长度为 $[a,b]$，则待分段长度 $len$ 一定在 $[k\times a,k\times b]$ 之间，否则直接输出```No solution```。

分法其实有很多，这里提供一种最好想，最好实现的。可以让每段尽量平均，余下的让一些段摊 $1$ 个数。具体地来说：

- 前 $len\bmod k$ 段长度为 $\left\lfloor len/k\right\rfloor+1$
- 后 $k-(len\bmod k)$ 段长度为 $\left\lfloor len/k\right\rfloor$

主体代码：（仅供参考，建议依照上述自己敲一遍）
```cpp
if(len<a*k||len>b*k){printf("No solution");return 0;}
l=len/k;
for(int i=0;i<len%k;++i){
	for(int j=0;j<=l;++j)printf("%c",str[to++]);
	printf("\n");
}
for(int i=len%k;i<k;++i){
	for(int j=0;j<l;++j)printf("%c",str[to++]);
	printf("\n");
}

```
提供另一种分法：
- 前 $\left\lfloor(len-k\times l)/(r-l)\right\rfloor$ 段长度为 $r$
- 中间 $1$ 段长度为 $l+(len-k\times l)\bmod(r-l)$
- 后 $len-\left\lfloor(len-k\times l)/(r-l)\right\rfloor-1$ 段长度为 $l$

---

## 作者：Priori_Incantatem (赞：4)

题目：[CF44E Anfisa the Monkey](https://www.luogu.com.cn/problem/CF44E)

DP

#### 题目大意

给出一个字符串 $s$，要求将 $s$，分成连续的 $k$ 段并满足每段长度在区间 $[l,r]$ 之内，也就是每段长度大于等于 $l$ 且小于等于 $r$

#### 解题思路

设 $f[i][j]$ 为长度为 $i$ 的字符串分成 $j$ 段的方案是否可行  
vector 数组 $g[i][j]$ 储存对应的 $f[i][j]$ 方案中所有的字符串分界点

很简单的 $O(n^3)$ 转移

```cpp
f[0][0]=1;
for(int i=1;i<=n;++i)
{
	for(int j=1;j<=i;++j) // 最多只能分成 i 段，因为只有 i 个字符
	{
		for(int k=i-r;k<=i-l;++k)
		{
			if(!f[k][j-1])continue;
			f[i][j]=1;
			g[i][j]=g[k][j-1];
			g[i][j].push_back(i);
			break;
		}
	}
}
```

**完整代码**

```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
const int Maxn=220,inf=0x3f3f3f3f;
char str[Maxn];
bool f[Maxn][Maxn];
vector <int> g[Maxn][Maxn];
int n,m,l,r;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int main()
{
//	freopen("in.txt","r",stdin);
	m=read(),l=read(),r=read();
	
	scanf("%s",str+1);
	n=strlen(str+1);
	f[0][0]=1;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=i;++j)
		{
			for(int k=i-r;k<=i-l;++k)
			{
				if(!f[k][j-1])continue;
				f[i][j]=1;
				g[i][j]=g[k][j-1];
				g[i][j].push_back(i);
				break;
			}
		}
	}
	if(!f[n][m])
	{
		puts("No solution");
		return 0;
	}
	int tmp=0;
	for(int i=1;i<=n;++i)
	{
		putchar(str[i]);
		if(i==g[n][m][tmp])
		{
			putchar('\n');
			++tmp;
		}
	}
	
	return 0;
}
```

---

## 作者：RE_Prince (赞：3)

# Anfisa the Monkey 


[link](https://www.luogu.com.cn/problem/CF44E)


## Sol

没人用深搜吗？我来补一发。


如上，这篇题解的本质是搜索剪枝，我会一步一步地引导大家如何优化和写代码。


## 最基础的深搜


题目意思很清楚了，就是让你把一个字符串分成在给定区间内的长度，分成 $k$ 段。

我一看到这道题就想到了搜索，相当于每次枚举现在这一段长度是多少，然后找到符合要求的解直接输出。

判断无解：如果 $l\times n>len$ 或 $r\times n<len$，直接无解。

判断完无解，就好进行搜索了。

注意一下，用 `pair` 数组来记录一段字符串的左端点和右端点，方便输出。

好像不用讲了吧，暴力代码：

```cpp
inline void dfs(int pos,int dep)
{
	if(pos==len&&dep==n)
	{
		print();
		exit(0);
	}
	else if(pos==len&&dep!=n) return;
	else if(dep==n&&pos!=len) return;
	for(int i=l;i<=r;i++)
	{
		a[dep+1]=make_pair(pos,pos+i-1);
		dfs(pos+i,dep+1);
	}
}
```


写上主函数，发现会在 $18$ 个点上 TLE，显然过不去。点开数据，发现字符串巨长，达到了 $200$，也就是极限数据。因此，我们要优化。


## 优化


再想想，发现 $n,k\le200$，很适合开一个 $vis$ 数组记录 $vis_{n,k}$ 是否到过。这种方法不就是记忆化吗？如果遇到现在的这个状态以前访问过，直接返回，这样能节省很多时间。


优化代码（我直接上全部的了）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,i,j,k,l,r,len;
pair<int,int> a[100009];
bool vis[1009][1009];
string s;
inline void print()//方便输出
{
	int r=0;
//	for(i=1;i<=n;i++) cout<<a[i].first<<" "<<a[i].second<<endl;
	for(int i=1;i<=n;i++)
	{
		for(j=a[i].first;j<=a[i].second;j++) cout<<s[j];
		puts("");
	} 
}
inline void dfs(int pos,int dep)
{
	if(pos==len&&dep==n)
	{
		for(i=1;i<n;i++)
			if(a[i].second!=a[i+1].first-1) return;
		if(a[n].second!=len-1) return;
		print();
		exit(0);
	}
	else if(pos==len&&dep!=n) return;//如果不符合要求，到头了
	else if(dep==n&&pos!=len) return;//同上
	if(vis[pos][dep]) return;//最重要的记忆化
	vis[pos][dep]=1;
	for(int i=l;i<=r;i++)
	{
		a[dep+1]=make_pair(pos,pos+i-1);//记录路径
		dfs(pos+i,dep+1);
        //不用回溯，再次访问直接覆盖原先值
	}
}
signed main()
{
	cin>>n>>l>>r;
	cin>>s;
	len=s.size();
	if(l*n>len||r*n<len) //无解
	{
		puts("No solution");
		return 0;
	}
	dfs(0,0);
	return 0;
}
```

---

## 作者：xiaoxiaoxia (赞：3)

# Part 1 思路分析
首先，我们可以先判断无解的情况，也就是字符串总长度都不够分，或者长度超过了最大值就是无解。最后确定字符串的分解方案：根据题目的意思把字符串平均分成 $k$ 行即可。

最后输出按此方案分的前 $k-1$ 行，因为可能无法平均分，就要判断是否有余数，如果有余数最后一行就需要将剩余无法平均分的再次加上即可。
这道题代码实现比较简单，上代码。
# Part 2 代码部分
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() 
{
	int x,k,a,b,n,y=0,sum=0,z=0;
	string s;
	cin>>k>>a>>b;
	cin>>s;
	n=s.size();
	if(a*k>n||b*k<n)//无解的情况 
	{
		cout<<"No solution";
		return 0;
	}
	if(n/k*k==n)//没有余数的情况 
	{
		for(int i=0;i<n;i++)
		{
			cout<<s[i];
			sum++;
			if(sum==n/k&&y<k-1)
			{
				cout<<endl;
				sum=0;
				y++;
			}
		}
	}
	else//有余数的情况 
	{
		x=n-(n/k*k);
		for(int i=0;i<n;i++)
		{
			cout<<s[i];
			sum++;
			if(sum-1==n/k&&y<k-1&&z<x)
			{
				cout<<endl;
				sum=0;
				y++;
				z++;
			}
			else if(sum==n/k&&y<k-1&&z==x)
			{
				cout<<endl;
				sum=0;
				y++;
			}
		}
	}
	return 0;
}
```


---

## 作者：tryrtj (赞：2)

首先声明一下，样例有毒，不要管第一个样例的输出，就因为这个样例让我想了半天每行的输出长度。

这题一看就知道是取子串，只不过前面加了个判断而已，废话不多说，直接上代码，附注释

```
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
	string s;
	int k,a,b;
	cin>>k>>a>>b;
	cin>>s;
	if(a*k<=s.length()&&b*k>=s.length()){//判断字符串长度是否合理（不够分成k份或分成k分长度超限）
		for(int i=0;i<k;i++){
			for(int j=s.length()/k*i;j<s.length()/k*(i+1);j++){
				cout<<s[j];//输出每一位
			}
			if(i!=k-1)cout<<endl;//如果不是最后一个则换行，最后一个后面还要加东西
		}
	}
	else {
		cout<<"No solution"<<endl;//输出否定结果
		return 0;
	}
	for(int i=s.length()-s.length()%k;i<s.length();i++){
		cout<<s[i];//跟上剩下的一点
	}
	cout<<endl;
	return 0;//程序结束
}
```

---

## 作者：LKY928261 (赞：1)

## 题目分析

题意很简单，就是将字符串拆成 $k$ 个子串，且每个子串的长度均符合 $a \leq size \leq b$ 。若无法拆分则输出 "No solution" 。

不难发现，当字符串长度在 $[ak,bk]$ 区间内时，一定能够进行拆分，反之，直接输出 "No solution" 即可。

至于每行输出几个字符，则可以根据个人喜好。本人选择的方法是尽可能平均分配。

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a,b,t,i;string s;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>a>>b>>s;t=s.size();
	if(t<n*a||t>n*b){cout<<"No solution\n";return 0;}
	for(i=0;i<n-t%n;i++)cout<<s.substr(t/n*i,t/n)<<"\n";
	for(i=0;i<t%n;i++)cout<<s.substr(t/n*(n-t%n)+(t/n+1)*i,t/n+1)<<"\n";
	//本人从不打return 0;
}
```

---

## 作者：_cmh (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/CF44E)

## $\texttt{Description}$

给定一个字符串，要求将它分为 $k$ 行且 $a\le len \le b$，输出这些被划分出来的部分，没有符合要求的划分就输出 `No solution`。

## $\texttt{Solution}$

首先判断无解的情况，如果字符串总长度都不够分，或是长度超过了最大值，那么无解。

后确定其分解方案：

将其平均分，分成 $k$ 行。

则输出按此方案分的前 $k-1$ 行，因为可能无法平均分，所以最后一行需要将剩余无法平均分的再次加上即可。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int k,a,b;
	scanf("%d%d%d",&k,&a,&b);
	string s;
	cin>>s;
	int len=s.length(),now=len/k;
	if(len<a*k||len>b*k){
		puts("No solution");
		return 0;
	}
	int tot=0;
	for(int i=1;i<k;i++,puts(""))
		for(int j=1;j<=now;j++)
			cout<<s[tot++];
	for(int i=tot+1;i<=len;i++)
		cout<<s[i-1];
    return 0;
}
```

感谢观看。

---

## 作者：零殇 (赞：1)

### 很简单的一道题

我们只要判断字符串分成$k$行后，如果大于$b$或者小于$a$，那么这个字符串就是不合法的，输出"No solution"。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int main() 
{
	int x,k,a,b,n,y=0,sum=0;
	string s;
	cin>>k>>a>>b;
	cin>>s;
	n=s.size();
	if(a*k>n||b*k<n)//判断字符串是否合法 
	{
		cout<<"No solution";
		return 0;
	}
	for(int i=0;i<n;i++)
	{
		cout<<s[i];
		sum++;
		if(sum==n/k&&y<k-1)//因为在最后一段可能会有余数,因此用y来计数，换行k-1次后停止 
		{
			cout<<endl;
			sum=0;
			y++;
		}
	}
	return 0;
}
```

然而实际上，这个代码是错误的（虽然也可以水过去），因为最后一行加上余数后，可能会超过$b$

例如：

输入：

$3$ $3$ $4$

$aaaaaaaaaaa$

输出：

$aaa$

$aaa$

$aaaaa$

显然，我们发现，这个程序是错误的。

### 那么怎么解决这种情况呢？

其实，我们可以把余数平均分给其他行。

因为余数一定小于$k$，所以每一行加$1$就可以了

可能你会问：这样其他行不会溢出吗？

实际上不会的,因为如果会溢出，就证明每一行的字符个数都是$b$，那么$b*k$再加上余数就会大于$n$，这个字符串就是不合法的，会被我们提前结束程序。

上代码：
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int main() 
{
	int x,k,a,b,n,y=0,sum=0,z=0;
	string s;
	cin>>k>>a>>b;
	cin>>s;
	n=s.size();
	if(a*k>n||b*k<n)//判断字符串是否合法
	{
		cout<<"No solution";
		return 0;
	}
	if(n/k*k==n)//没有余数的情况 
	{
		for(int i=0;i<n;i++)
		{
			cout<<s[i];
			sum++;
			if(sum==n/k&&y<k-1)
			{
				cout<<endl;
				sum=0;
				y++;
			}
		}
	}
	else
	{
		x=n-(n/k*k);//余数的个数 
		for(int i=0;i<n;i++)
		{
			cout<<s[i];
			sum++;
			if(sum-1==n/k&&y<k-1&&z<x)//将余数平均分给每一行 
			{
				cout<<endl;
				sum=0;
				y++;
				z++;
			}
			else if(sum==n/k&&y<k-1&&z==x)//z==x，说明余数分完了，剩下的照常输出 
			{
				cout<<endl;
				sum=0;
				y++;
			}
		}
	}
	return 0;
}
```

完结撒花~

---

## 作者：infinities (赞：1)

挺简单的一题，只需判断字符串的长度除以 $k$ 上下取整分别是否大于 $b$，小于 $a$ 即可完成对"No solution"的判断。

最后要将字符串分成 $k$ 段,长度除以 $k$（下取整）就是每段的基础长度，然后在前或后 $n$ % $k$ 段的长度上分别加上一即可。

code：
```cpp
#include<bits/stdc++.h>

using namespace std;

signed main(){
    int n,a,b,f[400]={0},ans=0;string s;//f表示每一段的起始位置
    
    cin>>n>>a>>b>>s;
    
    if(ceil((double)s.length()/(double)n)>b||s.length()/n<a){
        cout<<"No solution";
        return 0;
    }//判断
    
    for(int i=n-s.length()%n+1;i<=n;i++)f[i]=1;
    
    for(int i=1;i<=n;i++){
        f[i]+=s.length()/n+f[i-1];
    }
    
    for(int i=1;i<=n;i++){
        for(int j=f[i-1];j<f[i];j++){cout<<s[j];}
        cout<<"\n";
    }//输出字符串
}
```


---

## 作者：晨·曦 (赞：0)

### - 题意

给出 $k,a,b$ 以及一个字符串 $s$，要求把 $s$ 分解成 $k$ 个子串，使得每个子串长度 $l \ge a$ 且 $l \le b$。若无解则输出 `No solution`。

### - 分析

首先判断一下无解的情况：

如果 $s$ 的长度 $len \ge a \times k$ 或者 $len \le b \times k$，即此字符串不能被分解成至少长度为 $a$ 的 $k$ 段或者分解后的 $k$ 段中至少有一段的长度大于 $b$，则无解。 

分解方法：

先取 $l/k$ 为前面 $k-1$ 段的长度，再依次输出子串，最后再把剩下的还未输出的字符输出即可。

### - 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int a,b,k;
	cin>>k>>a>>b;
	string s;
	cin>>s;
	int l=s.size();
    // 判断是否有解
	if(l<a*k||l>b*k) { 
		cout<<"No solution";
		return 0;
	}
	int p=l/k;
	int i,ii,j;
    // 输出前k-1段子串
	for(i=1,ii=0; i<k; i++,ii++) {
		for(j=p*ii; j<p*i; j++) {
			cout<<s[j];
		}
		cout<<"\n";
	}
    // 输出最后一段子串
	for(;j<s.size();j++) cout<<s[j];
	return 0;
}
```

---

