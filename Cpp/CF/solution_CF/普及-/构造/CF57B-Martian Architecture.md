# Martian Architecture

## 题目描述

Chris the Rabbit found the traces of an ancient Martian civilization. The brave astronomer managed to see through a small telescope an architecture masterpiece — "A Road to the Sun". The building stands on cubical stones of the same size. The foundation divides the entire "road" into cells, into which the cubical stones are fit tightly. Thus, to any cell of the foundation a coordinate can be assigned. To become the leader of the tribe, a Martian should build a Road to the Sun, that is to build from those cubical stones on a given foundation a stairway. The stairway should be described by the number of stones in the initial coordinate and the coordinates of the stairway's beginning and end. Each following cell in the coordinate's increasing order should contain one cubical stone more than the previous one. At that if the cell has already got stones, they do not count in this building process, the stairways were simply built on them. In other words, let us assume that a stairway is built with the initial coordinate of $ l $ , the final coordinate of $ r $ and the number of stones in the initial coordinate $ x $ . That means that $ x $ stones will be added in the cell $ l $ , $ x+1 $ stones will be added in the cell $ l+1 $ , ..., $ x+r-l $ stones will be added in the cell $ r $ .

Chris managed to find an ancient manuscript, containing the descriptions of all the stairways. Now he wants to compare the data to be sure that he has really found "A Road to the Sun". For that he chose some road cells and counted the total number of cubical stones that has been accumulated throughout the Martian history and then asked you to count using the manuscript to what the sum should ideally total.

## 样例 #1

### 输入

```
5 2 1
1 5 1
2 4 1
3
```

### 输出

```
5
```

## 样例 #2

### 输入

```
3 2 1
1 3 1
1 3 1
2
```

### 输出

```
4
```

## 样例 #3

### 输入

```
3 2 1
1 3 1
1 3 1
3
```

### 输出

```
6
```

# 题解

## 作者：Mysterious_bird (赞：3)

这...

翻译很讨厌，我来说明一下

### 大意

有一个长度为 $n$ 的序列，初始全为 $0$ ，经过 $m$ 此操作和 $k$ 个询问，求出最终答案

 $m$ 此操作为 [ $Left$ , $Right$ ] $h$

操作方法为：

$a$ [ $l$ ] += $h$

$a$ [ $l$ + $1$ ] += $h$ + $1$

$a$ [ $l$ + $2$ ] += $h$ + $2$

…………

$a$ [ $r$ ] += $h$ + $r$ - $1$

询问 $f$ ，答案记录为所有 $a$ [ $f$ ] 的和（ $f$ 表示每次询问的位置）

### 做法
可以看出，这是一道容易的纯模拟题目

#### 一开始的思路：

既然有 $m$ 次操作，那我就每次读入时给 $a$ 数组赋值，最后 $ans$ 记录 $a$ [ $f$ ] 的和就行了

但是这样操作不仅效率低，而且还会TLE，so，考虑新做法

#### 新做法：

通过计算样例发现，如果需要查询的 $f$ 在区间 $Left$ 和 $Right$ 之间，则答案记录为

加数 + 在 $Left$ 与 $Right$ 中怎加的「级数」

而级数的计算方法也就是

当前查询位置 - $Left$

#### 代码实现

```cpp
for(int i=1;i<=k;i++)
{
    int f;
    cin>>f;     //读入k个询问时直接做运算
    for(int j=1;j<=m;j++)    //之前读入的 m 次操作
    {
        if(f>=wsl[j].Left&&f<=wsl[j].Right)		//如果f在第j次的操作范围内
        {
            ans+=f-wsl[j].Left+wsl[j].H;    //记录答案，也就是H+[l,r]区间内增加的级数
        }
    }
}
```

### 完整代码

```cpp
#include <iostream>
using namespace std;

struct awsl
{
    long long Left,Right,H;
}wsl[100010];

int main()
{
    long long n,m,k,ans=0;
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++)
    {
        cin>>wsl[i].Left>>wsl[i].Right>>wsl[i].H;
    }
    for(int i=1;i<=k;i++)
    {
        int f;
        cin>>f;     //读入 k 个询问时直接做运算 
        for(int j=1;j<=m;j++)    
        {
            if(f>=wsl[j].Left&&f<=wsl[j].Right)	//判断是否在区间内
            {
                ans+=f-wsl[j].Left+wsl[j].H;    //记录答案，关于这个式子的来源看上面
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}
```

THE END.

---

## 作者：YCE__22 (赞：2)

题意：n长的序列（初始全为0） m个操作 k个查询

下面m个操作[l,r] h 代表 a[l] +=h; a[l+1] += h+i; a[l+i] += h+i;  l<=i<=r

然后问k个位置的和

因为k<=100 所以直接暴力也可以

-----------------------

如果k<=100000 也是可以做的

只需要给区间记录一个标记lazy，表示从左端点开始 l, l+1, l+i ··· l+r

而向下更新时， 左区间则直接更新， 右区间先给整个区间加上一个值tree[L(id)].r , 然后再传个标记下去，这样就能解决了。。



先来份暴力的。。
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<string.h>
using namespace std;
#define ll long long
#define N 100005
#define mod 1000000007
ll l[N], r[N], hehe[N];
ll n, m, k;
int main(){
	ll i, j;
	while(cin>>n>>m>>k){
		for(i = 1; i <= m; i++)scanf("%I64d %I64d %I64d", &l[i], &r[i], &hehe[i]);
		ll ans = 0;
		while(k--)
		{
 
			scanf("%I64d",&j);
			for(i = 1; i <= m; i++)
			{
				if(j < l[i] || j > r[i])continue;
				ans += hehe[i];
				ans += j - l[i];
			}
 
		}
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：phil071128 (赞：1)


这道题还是比较有意义的，不算特别氵，首先我们尝试理解题目（毕竟翻译实在太离谱了）

对于样例1的解释:

```latex
0 0 0 0 0
1 2 3 4 5 
1 3 5 6 8
```

这样我们就能理解此题的意思了，第一眼就能看出模拟
## 1.模拟（暴力）

其中，稍微要需要注意一点：
```cpp
s[j]+=(h+(j-l)); 
```
其实是：
```cpp
s[j]+=(h+(j-l+1)-1); 
```
**莫不可写成：**
```cpp
s[j]+=(h+j-1); 
```
### 暴力代码
大约在90pts左右 

[评测记录](https://www.luogu.com.cn/record/41894841)
```cpp
#include <bits/stdc++.h>
using namespace std;
long long s[100000];
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		long long l,r,h;
		cin>>l>>r>>h;
		for(int j=l;j<=r;j++){
			s[j]+=(h+(j-l)); 
		}
	}
	long long sum=0;
	for(int i=1;i<=k;i++){
		int x;
		cin>>x;
		sum+=s[x];
		 
	}
	cout<<sum;
	return 0;
}
```

既然这样不行，我们就要换一种~~暴力~~思路：
## 2.优化
楼上讲的已经很清楚了，如果需要查询的数在这个区间内，则每次查询答案为$f-s[j].l+s[j].v$

### 代码：
[评测记录](https://www.luogu.com.cn/record/41893809)
```pascal
#include <bits/stdc++.h>
using namespace std;
struct node{
	long long l,r,v;
}s[1000000];
long long f[1000000];
int main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>s[i].l>>s[i].r>>s[i].v;
	}
	long long ans=0;
	for(int i=1;i<=k;i++){
		int f;
		cin>>f;
		for(int j=1;j<=m;j++){
			if(f<=s[j].r&&f>=s[j].l){
				ans+=f-s[j].l+s[j].v;
			}
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：_shine_ (赞：0)

## 题目大意
现在有长度为 $n$ 的序列，并且有 $m$ 次操作，并且有 $k$ 次询问，让你求查询的和。
## 思路
因为 $k$ 的大小最大只能为 $100$，并且 $1 \le m \le 10^5$，所以，我们可以直接暴力查找累计所有的和即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e5+10;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')w=-1;ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';
        ch=getchar();
    }
    return s*w;
}
inline void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)write(x/10);
    putchar(x % 10 + '0');
}
int n,m,k;
int l[maxn],r[maxn],w[maxn],ans;
signed main(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=m;++i){
		l[i]=read(),r[i]=read(),w[i]=read();
	}
	for(int i=1;i<=k;++i){
		int x=read();
		for(int j=1;j<=m;++j){
			if(x>=l[j] && r[j]>=x)ans+=x-l[j]+w[j];
		}
	}
	write(ans);
	return 0;
}
```


---

## 作者：Symbolize (赞：0)

# 思路
## 第一步
输入 $n,m,k$，与数组 $l,r,w$。$m$ 是区间个数，$k$ 是询问次数，$l$ 数组表示阶梯的起始坐标，$r$ 数组表示阶梯的终止坐标。
## 第二步
通过样例推导，易得对于每个被 $i$ 区间包含的 $x$，都有 $ans \gets ans + x - l_i +w_i$。所以我们暴力循环对答案进行累加。
## 第三步
输出即可。
## Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e5+10;
using namespace std;
int n,m,k,l[N],r[N],w[N],x,ans;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}
signed main()
{
	//第一步：输入
	n=read();
	m=read();
	k=read();
	rep1(i,1,m)
	{
		l[i]=read();
		r[i]=read();
		w[i]=read();
	}
    //第二步：暴力
	rep1(i,1,k)
	{
		x=read();
		rep1(i,1,m) if(l[i]<=x&&x<=r[i]) ans+=x-l[i]+w[i];//循环遍历，若x在i区间，则累加答案
	}
    //第三步：输出
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：AlicX (赞：0)

### 题意
有一个长为 $n$ 的序列，给你 $m$ 个区间以及区间的值，$k$ 次操作，让你求最终的答案。

### 分析
这道题很容易就看出来是一道模拟题。

通过计算样例发现，每次操作对于每一个 $i$，都有公式 $ans+=x-a[i].l+a[i].w$，其中 $x$ 是每次读入的数，$a[i].l$ 是区间左端点，$a[i].w$ 是区间的值，执行完 $k$ 次操作，最后输出 $ans$ 就可以了。

细节看代码

## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=1e5+10;
int n;
int m,k;
struct Node{
	int l,r;//区间左右端点 
	int w;//区间的值 
}a[N];
signed main(){
	cin>>n;
	cin>>m>>k;
	for(int i=1;i<=m;i++) cin>>a[i].l>>a[i].r>>a[i].w;//读入区间的左右端点，以及它的值 
	int ans=0;//累加变量 
	while(k--){
		int x;
		cin>>x;
		for(int i=1;i<=m;i++) if(a[i].l<=x&&x<=a[i].r) ans+=x-a[i].l+a[i].w;
		//遍历m个区间，如果x被第i个区间包含，就将x减去这个区间的层数（左端点）加上值 
	}
	cout<<ans<<endl;//输出 
	return 0;//Bye~ 
}
```
$$Thanks$$

---

## 作者：linyuhao (赞：0)

###  **题意**
第一行输入 $n,m,k$。接下来 $m$ 行输入 $L,R,Z$。从 $L$ 到 $R$，$L+i$ 位 $+i+Z$ 接下来 $k$ 行输入一个 $X$。询问第 $X$ 位石块个数。$ans$ 加上 $X$ 上石块个数，答案输出 $ans$。
# 做法
每次询问 $X$，从 $1$ 到 $m$ 进行暴力枚举，如果 $L \leq X \leq R$。则加上贡献。时间复杂度 $\mathcal{O}(mk)$。不会超时。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
    long long x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}//快速读入（可以用cin代替） 
long long l[100002],r[100002],kk[100002];
int main(){
	long long n,m,k;
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++){
		l[i]=read();r[i]=read();kk[i]=read();
	}
	long long x,ans=0;
	while(k--){
		x=read();
		for(int i=1;i<=m;i++){//枚举所有L,R
			if(l[i]<=x&&x<=r[i])ans+=(x-l[i])+kk[i];//若在区间内则加上贡献
		}
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：EthanOI (赞：0)

这道题主要是翻译有亿点玄幻，事实上本质就是找到一个递推关系式。通过计算样例发现，如果需要查询的 $f$ 在区间 $[l,r]$ 中，则答案记录为加数 $+$ 在 $Left$ 与 $Right$ 中怎加的级数，最后暴力就可以了

递推关系式：
```cpp
ans += num[i] - c[j].a + c[j].c;
```
核心代码（就是两层循环的递推）：
```cpp
for (ll i = 1; i <= k; i++)
	for (ll j = 1; j <= m; j++)
    	if (num[i] >= c[j].a && num[i] <= c[j].b)
        	ans += num[i] - c[j].a + c[j].c;
```
[AC CODE](https://www.luogu.com.cn/record/76845341) 
```cpp
#include <bits/stdc++.h>
#define maxn 100010
using namespace std;
typedef long long ll;
ll num[maxn];
struct node{ll a, b, c;}c[maxn];
int main()
{
    ll n, m, k;
    cin >> n >> m >> k;
    for (ll i = 1; i <= m; i++)
        cin >> c[i].a >> c[i].b >> c[i].c;
    for (ll i = 1; i <= k; i++)
        cin >> num[i];
    ll ans = 0;
    for (ll i = 1; i <= k; i++)
        for (ll j = 1; j <= m; j++)
            if (num[i] >= c[j].a && num[i] <= c[j].b)
                ans += num[i] - c[j].a + c[j].c;
    cout << ans;
    return 0;
}
```
~~这次希望可以过~~

---

## 作者：fuzhelin1984 (赞：0)

## 题意

初始有 $ n $ 个元素，有 $ m $ 次操作，在区间 $ l-r $上累加，$ l $ 上加 $ x $，$ l+1 $ 上加 $ x+1 $ ,以此类推，在 $ r $ 上加 $ x+r-1 $ 。共有 $ q $ 次询问，每次只询问一个元素最终的值。
        
## 思路
由于除询问次数外的数都很大，所以朴素作法一定过不了。但是思路也不难想，我们只需要处理每次询问指定的部分，这样做的时间复杂度可以接受。
        
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int _read()
{
    register int x=0,f=0;register char ch=getchar();
    while(ch<'0'||ch>'9')f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return f?-x:x;
}
inline void read(int& t)
{
	t=_read();
}
template<typename ...Arg> inline void read(int& t, Arg& ...args)
{
	t = _read();
	read(args...);
}
const int N = 114514;
int l[N],r[N],c[N];
signed main()
{
	int n,m,k,syy,ans = 0;
	read(n,m,k);
	for(int i = 1;i <= m;++i) 	read(l[i],r[i],c[i]);
	for(int i = 1;i <= k;++i) 
	{
		read(syy);
		
		for(int j = 1;j <= m;++j)
		{
			if(l[j] > syy || r[j] < syy) continue;//无关部分
			ans += syy-l[j]+c[j];//累加
		}
	}
	return cout<<ans,0;
}

```


---

## 作者：duchengjun (赞：0)

# 题目简化

定义一个数组 $t$.

每次给你 $a,b,c$.

及题目的操作可以简化成一下操作。

$t[a]=t[a]+c$

$t[a+1]=t[a+1]c+1$

$t[a+2]=t[a+2]+c+2$

$……$

$t[b]=t[b]+(c+b-a)$

再给你 $k$ 个整数 $tmp$。

让你求 $k$ 个 $t[tmp]$ 的总和。

# 分析

首先，我们第一想法是模拟，即枚举 $[a,b]$ 的每一个位置。

时间复杂度 $O(nm)$。

$1 \le n,m \le 10^5$

**超时**

但是，我们看到了 $k$ 范围：

$1 \le k \le \min(n,100)$

说明 $k$ 最大是 100，并不大。

思路转化一下，求 $k$ 个 $t[tmp]$ 的总和可以转化成 $tmp$ 在 $m$ 个区间内所有符合条件的所有加数之和。

时间复杂度 $O(km)$.

**不超时！！！**

# AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=1e5+10;
int n,m,k;
int a[N],b[N],c[N];
int t;
int ans;
signed main(){
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
		cin>>a[i]>>b[i]>>c[i];
	for(int i=1;i<=k;i++){
		cin>>t;
		for(int j=1;j<=m;j++)
			if(a[j]<=t&&t<=b[j])
				ans+=t-a[j]+c[j];
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：谦谦君子 (赞：0)

### 这就是一道简单的模拟题


真正的核心代码其实只有一个双重循环：
```cpp
for(i=1;i<=k;++i)
{
    for(j=1;j<=m;++j)
    {
        if(num[i]>=c[j].a&&num[i]<=c[j].b)
        {
            ans+=num[i]-c[j].a+c[j].c;
        }
    }
}
```
**代码见下**


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100010;
long long num[maxn];
struct node
{
    long long a,b,c;
}c[maxn];
int main()
{
    long long n,m,k,i,j;
    cin>>n>>m>>k;
    for(i=1;i<=m;++i)
    {
        cin>>c[i].a>>c[i].b>>c[i].c;
    }
    for(i=1;i<=k;++i)
    {
        cin>>num[i];
    }
    long long ans=0;
    for(i=1;i<=k;++i)
    {
        for(j=1;j<=m;++j)
        {
            if(num[i]>=c[j].a&&num[i]<=c[j].b)
            {
                ans+=num[i]-c[j].a+c[j].c;
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
```


---

