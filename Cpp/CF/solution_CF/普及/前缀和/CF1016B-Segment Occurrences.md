# Segment Occurrences

## 题目描述

You are given two strings $ s $ and $ t $ , both consisting only of lowercase Latin letters.

The substring $ s[l..r] $ is the string which is obtained by taking characters $ s_l, s_{l + 1}, \dots, s_r $ without changing the order.

Each of the occurrences of string $ a $ in a string $ b $ is a position $ i $ ( $ 1 \le i \le |b| - |a| + 1 $ ) such that $ b[i..i + |a| - 1] = a $ ( $ |a| $ is the length of string $ a $ ).

You are asked $ q $ queries: for the $ i $ -th query you are required to calculate the number of occurrences of string $ t $ in a substring $ s[l_i..r_i] $ .

## 说明/提示

In the first example the queries are substrings: "cod", "deforces", "fo" and "for", respectively.

## 样例 #1

### 输入

```
10 3 4
codeforces
for
1 3
3 10
5 6
5 7
```

### 输出

```
0
1
0
1
```

## 样例 #2

### 输入

```
15 2 3
abacabadabacaba
ba
1 15
3 4
2 14
```

### 输出

```
4
0
3
```

## 样例 #3

### 输入

```
3 5 2
aaa
baaab
1 3
1 1
```

### 输出

```
0
0
```

# 题解

## 作者：Frozencode (赞：2)

题意：t次询问，一个长度为n的串a,一个长度为m的串b，

问a的l到r区间中有多少个b。

对于这个数据范围，一遍一遍找是肯定会**超时**的。

看到区间问题，我们应该很自然的想到**前缀和**。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int pre[1005],p,n,m,t,l,r;
char a[1005],b[1005];
int main()
{
	cin>>n>>m>>t;
	cin>>(a+1)>>b;//为了操作方便我们将a整体后移一位。
	for(int i=1;i<=n-m+1;i++)//n-m+1保证了不会超出范围。
	{
		p=0;
		for(int j=0;j<m;j++)
		{
			if(a[i+j]!=b[j])
			{
				p=1;
				break;//此时说明以第i个位置开头是不行的。
			}
		}
		if(p==1)pre[i]=pre[i-1];
		else pre[i]=pre[i-1]+1;//第i个位置可以，那么前缀和+1。
	}
	while(t--)
	{
		cin>>l>>r;
		if(r-l<m-1)cout<<"0"<<endl;//区间长度小于m，肯定没有。
		else
		{
			cout<<pre[r-m+1]-pre[l-1]<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Fengyiwei1234 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1016B)

# 思路-前缀和

如果直接搜肯定超时。

考虑前缀和，${presum}_{i}\ $表示 a 字符串以 i 号为开头的重复次数。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=1009;
int Psum[N],n,m,T;
char a[N],b[N];
int main()
{
	cin>>n>>m>>T;
	cin>>a>>b;
	for(int i=0;i<=n-m;i++)
	{
		bool flag=0;
		for(int j=0;j<m;j++)
		{
			if(a[i+j]!=b[j])
			{
				flag=1;
				break;
			}
		}
		if(flag)Psum[i+1]=Psum[i];
		else Psum[i+1]=Psum[i]+1;
	}
	while(T--)
	{
	    int l,r;
		cin>>l>>r;
		if(r-l<m-1)cout<<"0"<<endl;
		else cout<<Psum[r-m+1]-Psum[l-1]<<endl;
	}
	return 0;
}
```

[AC,记录](https://www.luogu.com.cn/record/111316504)

---

## 作者：Light_Star_RPmax_AFO (赞：1)

# 思路——前缀和

## 前缀和

一看数据，**暴力**绝对会超时。

看到**序列**我们就可以想到前缀和优化时间。

使用前缀和记录**每一个位置**满足条件的个数。

### 暴力

我们使用暴力查找 $a$ 中以 $i$ 开头的字符串，看以这个下标开头是否有 $b$。

1. 有：

```cpp
f[i]=f[i-1]+1;

```
2. 没有:

```cpp
f[i]=f[i-1];
```

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m; char a[1001],b[1001]; int q; int f[1001];
    cin>>n>>m>>q>>(a+1)>>(b+1);
    for(int i=1;i<=n;i++){
    	bool can=0;
    	for(int j=1;j<=m;j++){
    		if(a[i+j-1]!=b[j]){
    			can=1;
    			break;
			}
		}//查找有没有以 i 开头的 b 在序列 a 中。
		if(can==1){
			f[i]=f[i-1];
		}else{
			f[i]=f[i-1]+1;
		}
	}
}

```
## STL

使用 **STL** **find** 函数就可以寻找哪里有 **b**。

使用前缀和记录就可以了。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m; string a,b; int q; int f[1050];
int main(){
    cin>>n>>m>>q>>a>>b;
    int i=0;
    while(1){
    	if(a.find(b,i)>n)break;//如果找不到了，就退出。
    	i=a.find(b,i);
    	f[++i]=1; 
	}
	for(int i=1;i<=n;i++){
		f[i]=f[i-1]+f[i];
	}//前缀和记录。
}
```
说实话还是 **STL** 大法好。
### 输出

输出直接用 $a_r-a_{l-1}$ 吗？

那就错了。

1. 特判 $l-r+1<m$，肯定是不能满足的。

2. 不是 $a_r-a_{l-1}$ 而应该是 $a_{r-m+1}-a_{l-1}$，因为如果是 $a_r$ 那么就有可能有从 $r$ 开始的这样的不包含在 $[l,r]$ 之间的含有 $b$ 的序列。

```cpp
while(q--){
		int l,r;
		cin>>l>>r;
		if(r-l+1<m){
			cout<<"0"<<endl;
		}else{
			cout<<f[r-m+1]-f[l-1]<<endl; 
		}
	}


---

## 作者：Supor__Shoep (赞：1)

既然是一道前缀和的题，那么我们就必须使用前缀和了。

首先我们可以知道需要求出 $[l,r]$ 区间的字符串问题，那么我们就需要通过一个数组 $sum$ 求得 $sum_r-sum_{l-1}$ 的值。按照题目所说，我们可以定义 $sum_i$ 为以第 $1$ 到 $i$ 个字符分别开头，长度为 $m$ 的字符串为 $b$ 的个数总和。由于 $1\leq n ,m\leq10^3$ 的条件，所以我们可以放心大胆地使用 $O(nm)$ 的预处理 $sum_i$ 数组。

因为是以 $i$ 开头，所以求的值并不是 $sum_r-sum_{l-1}$ 而是 $sum_{r-m+1}-sum_{l-1}$，这样以 $r-m+1$ 开头的字符串的右端点就刚好是 $r$。

那么代码就可以轻松加愉快地打出来了：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2005;
char a[MAXN],b[MAXN];
int sum[MAXN];
int n,m,T;
int main()
{
	cin>>n>>m>>T;
	scanf("\n%s",a+1);
	scanf("\n%s",b+1);
	for(int i=1;i<=n-m+1;i++)//以其它字符开头的字符串的右端点都会大于 n 
	{
		bool flag=0;
		for(int j=i;j<i+m;j++)
		{
			if(a[j]!=b[j-i+1])//比较两个数组 
			{
				flag=1;
				break;
			}
		}
		if(flag)	sum[i]=sum[i-1];//前缀和 
		else	sum[i]=sum[i-1]+1;
	}
	while(T--)
	{
		int l,r;
		cin>>l>>r;
		if(r-l+1<m)	puts("0");
		else	cout<<max(sum[r-m+1]-sum[l-1],0)<<endl;//输出 
	}
	return 0;
}
```

---

## 作者：aakennes (赞：1)

挺裸的题，本来想用哈希$O(n)$求解，后来发现有个点难处理，然后就改$O(n^2)$暴力了


## 正文
$O(n)$，每扫到一个字符就判断以当前字符结尾，串长为 $len2$ 的是否与第二个相等，相等让 $sum_i++$ 表示 $1-i$ 内有 $sum_i$ 个匹配串，也就是前缀和

查询时注意一个点：

* 左端点插在了匹配串中要特判

此时前缀和相减可能会算上这插到的半个串

然后就$O(n)$预处理，$O(log_2^{len})$ 查询，得到这样的代码：

```
	for(int i=1;i<=len1;i++){
		sum[i]=sum[i-1],ha1[i]=ha1[i-1]*base+s1[i];
		if(ha1[i]-ha1[i-len2]*poww[len2]==ha2)sum[i]++,b[++tot]=i;
	}
	for(int i=1,x,y;i<=m;i++){
		x=read(),y=read();
		if(x>b[lower_bound(b+1,b+1+tot,x)-b]-len2+1)printf("%d\n",max(sum[y]-sum[x-1]-1,0));//二分找到$x$后第一个右端点，看是否相交
		else printf("%d\n",sum[y]-sum[x-1]);
	}
```
然后你就会在$13$，$16$等点挂掉，原因是一个字符既可以存在于前一个匹配串的后缀，又可以存在于后一个匹配串的前缀

所以算重的贡献可能是 $2$ ，而不是 $1$

可以特殊处理也可以直接改 $O(n^2)$ 预处理

#### 代码：

```
	for(int i=1;i<=len2;i++)ha2=ha2*base+s2[i],poww[i]=poww[i-1]*base;
	for(int i=1;i<=len1;i++){
		sum[i]=sum[i-1],ha1[i]=ha1[i-1]*base+s1[i];
		if(ha1[i]-ha1[i-len2]*poww[len2]==ha2){
			sum[i]++;
			for(int j=i-len2+2;j<=i;j++)b[j]++;
		}
	}
	for(int i=1,x,y;i<=m;i++){
		x=read(),y=read();
		printf("%d\n",max(max(sum[y]-sum[x-1],0)-b[x],0));
	}
```

因为这题数据不强，所以也有其它解法，比如： 在线 $kmp$ 或先离线哈希在一个字符一个字符扫，时间复杂度 $O(n\times q)$，可以自己实现一下

---

## 作者：Qquun (赞：1)

## 1.题目大意：
给定两个字符串s和t，q次询问，每次询问给定区间[l,r]，询问s串的该区间内有有多少个可重叠t串。

#### ps:可重叠意为
```c
s=aaa t=aa
s串中有两个t串


```


## 2.解题思路：
建立前缀和数组sum，sum[i]表示s串中以第i位为末尾的前缀中所包含的t串的个数。

考虑如何求出sum数组。由于lens,lent<=1e3,
即可在O(n*m)的复杂度内求出sum数组，暴力匹配即可。

如何利用sum数组求得答案呢？

①当区间中的长度小于lent时，明显不能构成t串，输出0即可。

②当区间中的长度大于lent时，寻找区间中以l为首字母，长度为lent的子串的末尾位置，即pos=l+lent-1。此位置是区间内第一个长度为lent的子串的末尾位置。因此由前缀和思想，ans=sum[r]-sum[pos-1]。

## Code:
```c
#include<bits/stdc++.h>
using namespace std;
char s1[100005];
char s2[100005];
int sum[100005];//表示a串第i位为结束位前面有几个b串
int main(){
	int len1,len2,t;
	cin>>len1>>len2>>t;
	cin>>s1+1;
	cin>>s2+1;
	for(int i=len2;i<=len1;++i){
		int f=1;
		int cnt=len2;
		for(int j=i;j>=i-len2+1;j--){//暴力匹配
			if(s2[cnt--]!=s1[j])f=0;
		}
		sum[i]=sum[i-1]+f;
	//	cout<<"i=="<<i<<"  sum[i]="<<sum[i]<<endl;
	}	
	while(t--){
		int l,r;
		cin>>l>>r;
		if(r-l+1<len2){
			puts("0");
		}
		else{
			printf("%d\n",sum[r]-sum[l+len2-2]);
		}
	}
	return 0;
}

```

## End.

---

## 作者：叶枫 (赞：1)

看完题应该知道
- 题意：给定两个串$s$和$t$，多次询问$s$的一个区间$[l,r]$中有多少个子串与$t$串相同
____
刚看到题我还以为是$kmp$。

然后想了下，$\sout\text{模拟大法吼啊}$，还要用到**前缀和**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
#include<queue>
#define ll long long
#define maxn 1010
#define inf 2147483647
#define mod 998244353
using namespace std; 
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
    return x*f;
}
char a[maxn],b[maxn];
int s[maxn];
int n,m,QAQ;
signed main(){
`	n=read(); m=read(); QAQ=read();
	cin>>a+1>>b+1;
	for(int i=m;i<=n;i++) 
    {
        int flag=1;
        for(int j=1;j<=m;j++) if(b[m-j+1]!=a[i-j+1]) {flag=0;break;}
        s[i]=s[i-1]+flag;
    }
    while(QAQ--)
    {
        int x=read(),y=read(),t;
        if(y-x+1<m) t=0; 
		else t=s[y]-s[x+m-2];
        printf("%d\n",t);
    }
    return 0;
}
```
[$\sout\text{无耻的安利自己的博客}$](https://yycdeboke.blog.luogu.org/solution-cf1016b)

---

## 作者：流光萤影 (赞：0)

## 前言：

**本题解使用语言：C++14 (GCC 9)。**

引用链接：<https://article.itxueyuan.com/KAZQpD>。

## 正文：

**基本思路：[前缀和](https://article.itxueyuan.com/KAZQpD)。**

**代码实现：**

遍历一遍字符串 $a$，用数组 $map$ 记录前缀和，**$map _ i$ 为 $a _ {[1,i]}$ 中 $b$ 的个数：**

```cpp
for(int i = 0;i < a.length();i++)
{
	if(i+1 < b.length()) continue;
	if(a.substr(i+1-b.length(),b.length()) == b) _map[i+1]++;
	_map[i+1] += _map[i];
}
```

根据前缀和思想，得出核心关系：**$a _ {[l,r]}$ 中 $b$ 的个数为 $map _ r - map _ {l + |b| - 2}$。**

于是输出代码也实现了：

```cpp
for(;q;q--) cin >> l >> r,cout << (r-l+1 < b.length()?0:_map[r]-_map[l+b.length()-2]) << "\n";
```

------------

**AC 代码：**

```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int _map[1005],n,m,q,l,r,first;
string a,b;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m >> q >> a >> b;
	for(int i = 0;i < a.length();i++)
	{
		if(i+1 < b.length()) continue;
		if(a.substr(i+1-b.length(),b.length()) == b) _map[i+1]++;
		_map[i+1] += _map[i];
	}
	for(;q;q--) cin >> l >> r,cout << (r-l+1 < b.length()?0:_map[r]-_map[l+b.length()-2]) << "\n";
	return 0;
}
```

---

## 作者：_zhy (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1016B)。

$l \sim r$ 有多少个给出的字符串。

我们可以从 $l$ 开始枚举，一直枚举到 $r$，看中间有多少合法字符串。

但由于有最多有 $10^5$ 组数据，所以直接暴力肯定不可取。

我们来思考一下优化。

由于我们求的是一个区间的问题，而又没有修改，自然想到前缀和。

不妨定义一个数组 $p$，$p_i$ 就表示以 $1 \sim i$ 开头有多少合法字符串。

那么每次询问就可以用 $O(1)$ 直接输出了，答案是 $p_{r - m + 1} - p_{l - 1}$。

$p_i$ 就表示以 $1 \sim i$ 开头有多少合法字符串，所以一定是 $p_{r - m + 1}$。

### code

```cpp
#include <iostream>

using namespace std;

const int N = 1e3 + 5;

string a, b;
int n, m, q, l, r, p[N];

int main() {
	cin >> n >> m >> q >> a >> b;
	for (int i = 0; i + m - 1 < n; i++) {
		if (i)	//防止下标为负。 
			p[i] = p[i - 1];
		if (a.substr(i, m) == b)	//看以i开头的字符串有没有和给定字符串相等的。 
			p[i]++;	
	}
	while (q--) {
		cin >> l >> r;
		if (r - l + 1 < m)	//如果长度都不够，肯定没有合法字符串。 
			puts("0");
		else
			printf("%d\n", p[r - m] - p[l - 2]);	//由于是从0输入的所以下标都减1。 
	}
	return 0;
}
```

---

## 作者：许多 (赞：0)

## 思路

我们用 $a[i]$ 表示为前 $i$ 个字符中，有多少子串 $b$。

枚举开头 $i$ 预处理，再向后遍历 $m$ 个字符，进行暴力处理。

运用了前缀和的思想。答案即是 $a[r-m+1]-a[l-1]$。

有人可能对 $r-m+1$ 不太理解，我们倒着想，如果在 $a$ 数组中有一个子串 $b$，结尾在 $r$ 处，那它的开头即是 $r-m+1$。

## 细节

我们要注意 $m>n$ 的情况，这时我们就要加特判，否则很容易 T 或 RE。

# 代码

```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define N 2222
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
using namespace std;
int n,m,a[N],q;
char s[N],t[N];
int main(){
    n=read();m=read();q=read();
    scanf("%s%s",s+1,t+1);
    for(int i=1;i+m-1<=n;i++){//预处理
        int This=1;
        for(int j=1;j<=m;j++)
            if(s[i+j-1]!=t[j]){
                This=0;
                break;
            }
        a[i]=a[i-1];
        if(This)a[i]++;
    }
    if(m<=n)for(int i=n-m+2;i<=n;i++)a[i]=a[i-1];//记得处理后面
    for(int i=1;i<=q;i++){
        int l=read(),r=read();
        if(r-l+1<m){printf("0\n");continue;}
        printf("%d\n",a[r-m+1]-a[l-1]);
    }
    return 0;
}
```


---

## 作者：COsm0s (赞：0)

## 题意 
有长度为 $n$ 的串 $a$，长度为 $m$ 的串 $b$，共 $q$ 次询问，每次询问 $a$ 在 $l$ 到 $r$ 区间中有多少个 $b$。

注意，$b$ 可以重叠。

## 思路
+ 如果每次模拟的话，复杂度为 $O(q*(l-r)^2)$，时间超限。

+ 这时，我们就需要用到前缀和，并将数据进行预处理。设 $s_i$ 表示为前 $i$ 个字符中，有多少子串 $b$。

	即循环寻找区间中以 $l$ 为首字母，长度为 $len$ 的子串的末尾位置，如果是 $a_i ≠ b_j$ 则判定这个字串非 $b$。如果是，则前缀和加 $1$。
    
    此时，复杂度为 $O(nm+q)$。
    
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read() {
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)) {
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)) {
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x) {
	if(x < 0) {
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
//快读快输
const int N = 1e5 + 10;
char s1[N];//a 
char s2[N];//b 
int ans[N];//前缀和数组 
int l1,l2,t,l,r;
inline bool check(int i, int cnt) {
	for(int j = i; j >= i - l2 + 1; j --)
		if(s2[cnt --] != s1[j]) return 0;
	return 1;
}
//判断是否等于b 
signed main() {
	l1 = read(), l2 = read(), t = read();
	cin >> s1 + 1 >> s2 + 1;
	for(int i = l2; i <= l1; ++ i)
		ans[i] = ans[i - 1] + check(i, l2);//前缀和操作 
	while(t --) {
		cin >> l >> r;
		if(r - l + 1 < l2) puts("0");//长度不够输出0 
		else write(ans[r] - ans[l + l2 - 2]), puts("");
	}
}

```


---

