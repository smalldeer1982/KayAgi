# [ABC118D] Match Matching

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc118/tasks/abc118_d

ちょうど $ N $ 本のマッチ棒を使って作れる整数の中で最大のものを求めてください。

ただし、以下の条件を満たさなければなりません。

- 作る整数の各桁は、$ 1 $ から $ 9 $ までの数字のうち $ A_1,\ A_2,\ ...,\ A_M\ (1\ \leq\ A_i\ \leq\ 9) $ のいずれかでなければならない。
- 数字 $ 1,\ 2,\ 3,\ 4,\ 5,\ 6,\ 7,\ 8,\ 9 $ を $ 1 $ つ作るには、それぞれちょうど $ 2,\ 5,\ 5,\ 4,\ 5,\ 6,\ 3,\ 7,\ 6 $ 本のマッチ棒を使う。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 2\ \leq\ N\ \leq\ 10^4 $
- $ 1\ \leq\ M\ \leq\ 9 $
- $ 1\ \leq\ A_i\ \leq\ 9 $
- $ A_i $ は全て異なる。
- ちょうど $ N $ 本のマッチ棒を使って条件を満たすように作れる整数が存在する。

### Sample Explanation 1

整数 $ 777773 $ は $ 3\ +\ 3\ +\ 3\ +\ 3\ +\ 3\ +\ 5\ =\ 20 $ 本のマッチ棒を使って作れ、ちょうど $ 20 $ 本のマッチ棒を使って条件を満たすように作れる整数の中でこれが最大です。

### Sample Explanation 2

出力が $ 64 $ ビット整数型に収まらない場合があります。

## 样例 #1

### 输入

```
20 4
3 7 8 4```

### 输出

```
777773```

## 样例 #2

### 输入

```
101 9
9 8 7 6 5 4 3 2 1```

### 输出

```
71111111111111111111111111111111111111111111111111```

## 样例 #3

### 输入

```
15 3
5 4 6```

### 输出

```
654```

# 题解

## 作者：忘怜城羡 (赞：22)

# 思路
这道题是典型的完全背包问题，需要求的是最大数字，而数字中的每一位需要的火柴数之和是一定的，所以要排序把大的数放在前面。

long long 在这道题肯定会超大小，最大会有 $5 \cdot 10^3$ 位数，于是就用 string 类型来存，而 string 类型大小的比较需要自定义函数比较，每次取较大的一个，在取之前需要判断能不能加，即 $dp[j-v[i]]$ 非空或 $j-v[i]=0$ ，到最后输出 $dp[n]$ 表示刚好用完 $n$ 个火柴的最大数。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string dp[10010];
struct node{
	int w,v;
}a[100010];
char add(int a,int b)//增加的字符 
{
	int c=a+b;
	return char(c);
}
bool cmp(node x_,node _x)
{
	return x_.w>_x.w;
}
string ma(string a,string b)//比较数字大小 
{
	if(a.size()>b.size())//长度比较 
	return a;
	else
	if(a.size()<b.size())
	return b;
	else
	{
		for(int i(0);i<a.size();++i)//按每个字符比较 
		if(a[i]>b[i])
		return a;
		else
		if(b[i]>a[i])
		return b;
		return a;
	}
}
int main()
{
	int n,m,tot=0;
	scanf("%d%d",&n,&m);
	for(int i(1);i<=m;++i)
	{
		int x;
		scanf("%d",&x);
		a[++tot].w=x;
		if(x==1)//记录在组成的数字需要的火柴数 
		a[tot].v=2;
		if(x==2||x==3||x==5)
		a[tot].v=5;
		if(x==4)
		a[tot].v=4;
		if(x==6||x==9)
		a[tot].v=6;
		if(x==7)
		a[tot].v=3;
		if(x==8)
		a[tot].v=7;
	}
	sort(a+1,a+n+1,cmp);//排序数字 
	dp[0]="";
	for(int i(1);i<=tot;++i)
	{
		for(int j(a[i].v);j<=n;++j)
		{
			char x=add(a[i].w,'0');
			if(dp[j-a[i].v]!=""||j-a[i].v==0)//判断能不能加 
			dp[j]=ma(dp[j],dp[j-a[i].v]+x);
		}
	}
	printf("%s\n",dp[n].c_str()); 
	return 0;
}
```

---

## 作者：Dark_Sky (赞：13)

简单的完全背包问题,先dp得出拼成的数字的最大位数然后将dp倒回去查找路径,查找路径的过程中可以贪心从最大的数字开始考虑。

上代码：
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;

const int M = 1000001;

int s[] = {0,2,5,5,4,5,6,3,7,6};
int a[M],ans[M];
int n,m;
int dp[M];

int cmp(int a,int b){
    return a > b;
}
 
int main(){
    cin>>n;
    cin>>m;
    for(int i = 0;i < m;i++){
        cin>>a[i];
    }
    memset(dp,-1,sizeof(dp));
    dp[0] = 1;
 
    int vis[10] = {0};
    for(int i = 0;i < m;i++){
        for(int j = s[a[i]];j <= n;j++){
            dp[j] = max(dp[j],dp[j-s[a[i]]]+1);
        }
    }
 
    sort(a,a+m,cmp);
    while(n){
        for(int i = 0;i < m;i++){
            if(n >= s[a[i]] && dp[n-s[a[i]]]+1 == dp[n]){
                putchar(a[i]+'0');
                n = n-s[a[i]];
				break;
            }
        }
    }
 
    cout<<endl;
    return 0;
}
```


---

## 作者：dayz_break404 (赞：4)

[博客食用更佳](https://www.luogu.com.cn/blog/lmzz/solution-at-abc118-d)

### 题目描述

已知每种数字拼得所需的火柴数，给出所拥有的火柴棒数 $n$ 以及可以拼 $m$ 种数字 $a_1,a_2,\dots,a_m$，求出所能拼成的最大数字。

### 题目分析

题目给出的各个数字所用的代价可以用数组 $value$ 存下来。

我们现在要求出所能拼成的最大数字，且使用的每个数字有对答案的贡献，以及所需要的代价，很显然想到 dp。

这里 dp 的状态就很明显了，只有一个维度：所使用火柴棒数量。

我们立马想到，用 $dp_i$ 来表示当此时使用了 $i$ 根火柴棒时所能拼成的数字的最大值。

但这样会遇到一个问题：就算用 `unsigned long long` 也无法存下拼成数字的值。

怎么办呢？

我们不妨考虑判断两个数字之间的大小的方法：

1. 比较数位大小。

2. 若数位大小一样，从高位到低位比较各个位置上的数字。


这样，我们不妨设 $dp_i$ 为当前使用 $i$ 根火柴棒时所能拼成的最大数字位数，初始状态为 $dp_0=0$。

设 $value_j$ 为拼成数字 $j$ 所花费的火柴棒数量。

转移方程显然：

$$dp_i=dp_{i-value_j}+1$$

求出所能拼成的数字最大位数后，考虑贪心，从高位到低位放置数字。

先对给出的可以拼成的数字从大到小排序，并在每次确定每一位数字时从大到小遍历，对于每个数字 $j$，设 $k$ 表示当前未匹配的火柴棒数量，若 $dp_k=dp_{k-value_j}+1$，则对于数字 $j$，是可以被放置于当前位置的，且是最优的方案。这样一直确定每一位上的数字，直至 $k=0$。

时间复杂度 $O(nm)$，至此，我们已经求得了答案。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000020
int n,m,a[15],value[15]={0,2,5,5,4,5,6,3,7,6},dp[maxn];
bool cmp(int a,int b){
	return a>b;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&a[i]);
	}
	memset(dp,-1,sizeof(dp));//记得初始化
	dp[0]=0;
	for(int	i=1;i<=m;i++){
		for(int j=value[a[i]];j<=n;j++){
			dp[j]=max(dp[j-value[a[i]]]+1,dp[j]);
		}
	}
	sort(a+1,a+1+m,cmp);
	while(n){
		for(int i=1;i<=m;i++){
			if(n>=value[a[i]]&&dp[n-value[a[i]]]+1==dp[n]){
				printf("%d",a[i]);
				n-=value[a[i]];
				break;
			} 
		}
	}
	puts("");
	return 0;
}
```


---

## 作者：DPseud (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT4298)

# 思路

两个变量 $n$ 和 $m$，两个数组输入的 $a$ 与 $a$ 的火柴数 $w$，每种数字可以用无限遍（虽然题目没说，但样例明显），很显然，这就是一道完全背包问题。

但是，我们可不可以用 DFS 来做呢？

```cpp
#include<bits/stdc++.h>
using namespace std;
const int dab_but_not_dab[10]={0,2,5,5,4,5,6,3,7,6};
int n,m,a[999];
string ma="0";
string strmax(string a,string b)
{
	if(a.length()>b.length())return a;
	else if(a.length()<b.length())return b;
	else
	{
		for(int i=0;i<a.length();i++)
		{
			if(a[i]>b[i])return a;
			else if(a[i]<b[i])return b;
		}
	}
	return "IAKIOI";
}
void dg_to_dp(int boom,string strick)
{
	if(boom>=n)
	{
		if(boom==n)ma=strmax(ma,strick);
		return;
	}
	else
	{
		for(int i=0;i<m;i++)
		{
			char c=a[i]+48;
			string strickler="#";
			strickler[0]=c;
			dg_to_dp(boom+dab_but_not_dab[a[i]],strick+strickler);
		}
		return;
	}
}
int main()
{
	cin>>n>>m;
	for(int i=0;i<m;i++)cin>>a[i];
	dg_to_dp(0,"");
	cout<<ma;
    return 0;
}
```

DFS 的时间复杂度是 $O(2^n)$，因此，第一个点便会超时，那么这道题的正解就只能是完全背包了。

我们都知道完全背包的模板如下（不会的自己百度）：

```cpp
for(int i=1;i<=m;i++)
	{
		for(int j=a[i];j<=n;j++)dp[j]=max(dp[j],dp[j-w[i]]+a[i]);
	}
```

虽然题目只给出了 $a$，但其实 $w$ 就是 $a$ 需要的火柴数，所以我们就能愉快地 DP 了，然而这道题并不是求数字最大位数而是求数字，所以我们在求出位数之后还得再来一个 $O(nm)$ 的枚举，大致思路就是先对数组 $a$ 进行排序，然后在 $n> 0$ 的情况下不断遍历 $a$，每次遍历，我们做出下列操作：

1. 如果 $w_i\ge n$，就算一个数火柴都不够，直接下一个数。

2. 求出火柴总数减去这一个数对应的火柴数量的位数方案与火柴总数的位数方案，如果两者相差一，输出数字，并且将火柴数减去火柴数量（即 $w_i$），以此用于求下一位，然后退出循环。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int match[10]={-1,2,5,5,4,5,6,3,7,6};//先打个小小的表
int main()
{
	static int n,m,a[11],w[11],dp[11111];
	cin>>n>>m;
	dp[0]=1;
	for(int i=1;i<=m;i++)cin>>a[i],w[i]=match[a[i]];//初始化两个必备元素
	sort(a+1,a+1+m);//排序，升序还是降序都行
	for(int i=1;i<=m;i++)
	{
		for(int j=w[i];j<=n;j++)dp[j]=max(dp[j],dp[j-w[i]]+1);//动态规划
	}
	for(int i=1;i<=m;i++)w[i]=match[a[i]];//还得再初始化一遍排序后的a数组
	while(n)//注意不是n--
	{
		for(int i=m;i>=1;i--)
		{
			if(w[i]>n)continue;//注意不是>=
			if(dp[n-w[i]]+1==dp[n])
			{
				cout<<a[i];
				n-=w[i];
				break;
			}
		}
	}
	return 0;
}
```


---

## 作者：EityDawn (赞：1)

# 思路：

~~考过的原题~~

非常有意思的完全背包题，定义背包容量为 $n$，物品即为给出的 $m$ 个数，每个数的花费即为需要火柴棍的数量，那么我们定义 dp 数组，$dp[v]$ 表示花费为 $v$ 时的最大数，~~应该不需要我多讲~~，我们发现，因为拼出来的数很大，所以可以用 string 类型存储，注意开一个结构体维护 string 型长度，初始置为无穷小，因为我们要刚好用完火柴棍。

# code

``` cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e4+10;
struct node{
	string s;
	int len=-0x7fffffff;//初始化为负无穷
} dp[N];
int map_[10]={6,2,5,5,4,5,6,3,7,6};//0到9所需火柴数，当然0不用
int num[10];
int n,m;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>num[i];
	sort(num+1,num+m+1);
	dp[0].len=0;
	for(int i=1;i<=m;i++)//妥妥的完全背包板子
	{
		for(int v=map_[num[i]];v<=n;v++)
		{
			if(dp[v-map_[num[i]]].len+1>=dp[v].len) //状态转移，长度越长越好，还要保证最大
				dp[v]=(node){(char)(num[i]+48)+dp[v-map_[num[i]]].s,dp[v-map_[num[i]]].len+1};
		}
	}
	cout<<dp[n].s;
	return 0;
}
```





---

## 作者：hxhhxh (赞：1)

## 大意

计算出最大的 $ N $ ，使得 $ N $ 只由给定某些数码构成，且恰好使用 $ n $ 根火柴棍。 

## 思路

动态规划。

手写一个储存大数的结构体，表示该数有 $ cnt_i $ 个数码 $ a_i $ ，输出时从大到小输出。

记 $ dp_i $ 表示用 $ i $ 根火柴棍能获得的最大数。

则有 $ dp_i=\max(add(dp_{i-c_{a_i}},a_i),dp_i) $ ，其中 $ c_i $ 表示数 $ i $ 要用的火柴棍根数， $ a_i $ 表示第 $ i $ 个给定数码，$ add(i,j) $ 表示向大数 $ i $ 中加入数码 $ j $ 。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[15],c[15]={0,2,5,5,4,5,6,3,7,6};
struct bgnm{
    int cnt[10],len;
    bool operator>(const bgnm&b)const{
        if(len!=b.len) return len>b.len;
        for(int i=m;i>=1;i--) if(cnt[i]!=b.cnt[i]) return cnt[i]>b.cnt[i];
        return false;
    }
}dp[10005];
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    sort(a+1,a+m+1);
    for(int i=1;i<n;i++) dp[i].len=-1000005;
    for(int i=m;i>=1;i--){
        for(int j=0;j<=n;j++){
            if(c[a[i]]<=j){
                bgnm t=dp[j-c[a[i]]];
                t.cnt[i]++;
                t.len++;
                if(t>dp[j]) dp[j]=t;
            }
        }
    }
    for(int i=m;i>=1;i--) for(int j=1;j<=dp[n].cnt[i];j++) putchar(a[i]+'0');
    return 0;
}
```

---

## 作者：Nightingale_OI (赞：1)

### 大意

问你恰好 $ n $ 根火柴可以拼出来最大的数是多少。

保证存在答案。

### 思路

显然答案的大数字在前面，不然一定不优。

则最终答案的数组最多有 $ m $ 段，可以用结构体存。

从大到小枚举在后面拼什么数字，背包问题。

时间复杂度 $ O(nm^2) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int a[10];
int v[10]={0,2,5,5,4,5,6,3,7,6};
struct dn{
    int x[10],y;
}ls;
dn dp[10101];
bool operator > (const register dn& a,const register dn& b){
    if(a.y!=b.y)return a.y>b.y;
    f(i,1,m){
        if(a.x[i]<b.x[i])return 0;
        if(a.x[i]>b.x[i])return 1;
    }
    return 0;
}
int main(){
    cin>>n>>m;
    f(i,1,m)scanf("%d",&a[i]);
    f(i,1,m)a[i]=-a[i];
    sort(a+1,a+m+1);
    f(i,1,m)a[i]=-a[i];
    f(i,1,n)dp[i].y=(i==n?0:-10101);
    f(i,1,m)g(j,n,0)if(j+v[a[i]]<=n){
        ls=dp[j+v[a[i]]];
        ++ls.x[i];++ls.y;
        if(ls>dp[j])dp[j]=ls;
    }
    f(i,1,m)f(j,1,dp[0].x[i])putchar(a[i]^48);
    putchar('\n');
    return 0;
}
```

---

## 作者：ilibilib (赞：0)

### 分析

一道蛮有意思的完全背包题目。

我们用 $dp[i]$ 记录用 $i$ 跟火柴能摆出的最大数字。

我们发现这个数字非常大，所以可以用 string 类型存储。

然后再自己手写一个比较函数。

如何状态转移？

一共最多有 $9$ 个数字，即 $9$ 件物品。

它们的费用即摆出它所需的火柴数。

将它装进背包有两种情况。

一种是放在已经摆好数字的**前面**，另一种是放在其**后面**，

再用刚刚手写的比较函数比较取最大值即可。

因为要求 $n$ 根火柴全部都用完，所以开了个 bool 数组记录这个火柴花费能被到达。



### code：

```cpp
#include<bits/stdc++.h>
#define sc scanf
#define pt printf
#define gc getchar
#define pc putchar
#define N 10010
using namespace std;
template<typename T>
inline void read(T &x)
{
	x=0;char ch=gc();
	while(ch<'0'||ch>'9') {ch=gc();}
	while(ch>='0'&&ch<='9') {x=(x<<3)+(x<<1)+ch-48,ch=gc();}
}
template<typename T>
inline void write(T x)
{
	if(x>9) write(x/10);
	pc(x%10^48);
}
bool cmp(string a,string b)
{
	if(a.length()!=b.length()) return a.length()>b.length();
	return a>b;
}
string dp[N];
int w[15]={0,2,5,5,4,5,6,3,7,6};
char c[15]={'0','1','2','3','4','5','6','7','8','9'};
bool bl[15],f[N];
string max(string a,string b)
{
	return cmp(a,b)?a:b;
}
signed main()
{
	int m,n,a;
	read(m),read(n);
	for(int i=0;i<=m;++i) dp[i]="";
	while(n--)
	{
		read(a);
		bl[a]=true;
	}
	f[0]=true;
	for(int i=1;i<=9;++i)
		if(bl[i])
		{
			for(int v=w[i];v<=m;++v)
				if(f[v-w[i]])
					dp[v]=max(dp[v],max(dp[v-w[i]]+c[i],c[i]+dp[v-w[i]])),f[v]=true;
		}
	cout<<dp[m];
	return 0;
}
```



---

## 作者：xxxalq (赞：0)

[洛谷题目链接](https://www.luogu.com.cn/problem/AT_abc118_d) & [AT 题目链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/abc118_d)

# 思路分析：

这是一道恰好装满的完全背包问题，和正常的完全背包一样，初始化改一下即可。

这里说一下为什么 $dp[0]$ 要赋成 $0$ 而 $dp[1]$ 到 $dp[n]$ 要赋值成一个极小值，因为只有 $0$ 在背包容量恰好为 $0$ 的时候价值为 $0$，要求最大值所以剩下的要赋成一个极小值。

然后就是一道完全背包模板题了，这道题时间复杂度应该是趋近于 $O(nm^2)$，因为 $m$ 很小所以几乎可以做到 $O(n)$，那就可以用不加优化的 $3$ 层循环来做。

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	char ch=getchar();
	int x=0;
	bool flag=false;
	while(ch<'0'||ch>'9'){
		if(ch=='-'){
			flag=true;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+(ch-'0');
		ch=getchar();
	}
	return flag?-x:x;
}//快读
bool cmp(int x,int y){
	return x>y;
}
int n,m,dp[10003],a[15],num[15]={6,2,5,5,4,5,6,3,7,6};//我的m和n与题目中颠倒的
signed main(){
	m=read(),n=read();
  	//再说一下，我的m和n与题目中是颠倒的
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	sort(a+1,a+1+n,cmp);
	for(int i=1;i<=m;i++){
		dp[i]=-0x3f3f3f3f;
	}
  	//初始化
	for(int i=1;i<=n;i++){
		for(int j=2;j<=m;j++){
			int tmp=10,cnt=a[i];
			for(int k=1;j-k*num[a[i]]>=0;k++){
				if(dp[j-k*num[a[i]]]>=0){
					dp[j]=max(dp[j],dp[j-k*num[a[i]]]*tmp+cnt);//状态转移
				} 
				cnt=cnt*10+a[i];
				tmp*=10;
			}
		}
	}
	cout<<dp[m];//输出答案
	return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc118_d)

一道 dp 题。

在 dp 之前，我们需要明确以下几个东西：

**状态的表示**，**状态转移方程**，**边界条件**跟**答案的表示**。

### 状态的表示

$dp_i$ 表示恰好用完 $i$ 根火柴能拼出来的最大数字。

### 状态转移方程

$$dp_i = \max\{j \times 10^{len(dp_{i-w_j})} + dp_{i-w_j}\}$$

其中 $len(n)$ 表示 $n$ 的位数，$w_i$ 表示拼出数字 $i$ 所需的火柴数量。实际上这里是将 $dp_{i-w_j}$ 拼在 $j$ 后面。

### 边界条件

$$dp_i = 0$$

### 答案的表示

$$dp_n$$


### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll n, m;
ll w[10] = {0, 2, 5, 5, 4, 5, 6, 3, 7, 6};
string dp[10005];
bool vis[10];
string strmax(string x, string y) {
	if (x.size() > y.size()) return x;
	if (x.size() < y.size()) return y;
	for (int i = 0; i < x.size(); i++) {
		if (x[i] < y[i]) return y;
		if (y[i] < x[i]) return x;
	}
}
ll sum(string s) {
	ll res = 0;
	for (int i = 0; i < s.size(); i++) res += w[s[i] - '0'];
	return res;
}
int main() {
	ios :: sync_with_stdio(0);
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		ll x;
		cin >> x;
		vis[x] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 9; j++) {
			if (vis[j] and i >= w[j] and sum(to_string(j) + dp[i - w[j]]) == i) dp[i] = strmax(dp[i], to_string(j) + dp[i - w[j]]);
		}
	}
	cout << dp[n];
	return 0;
}
```


---

## 作者：Ifyoung (赞：0)

[题面](https://www.luogu.com.cn/problem/AT_abc118_d)

# 题目描述

有 $n$ 根火柴 $m$ 种数字，数字 $1,2,3,4,5,6,7,8,9$ 分别需要 $2,5,5,4,5,6,3,7,6$ 根火柴，要求 $n$ 根火柴全部都用完且拼成的数字最大，输出这个数字。

# 输入格式

第一行两个整数 $n, m$；

第二行 $m$ 个整数，分别为 $a_1, a_2, \cdots, a_m$（即 $m$ 种数字是哪几个）。

# 输出格式

一行一个整数，表示能拼成的最大数字。

---

# 题解

做这个题的思路其他题解都讲得很完整了，从完全背包角度进行解决的解法（代码）也基本一样。但是在本人阅读题解时，遇到的问题就是不知道为什么有这样一句 `f[0] = 1`，所以这里主要讲解一下代码中 `f[0] = 1` 的意义。

这里以样例一进行讲解：

样例一

```
20 4
3 7 8 4
```

第一步

进行完全背包时，$f$ 数组的更新状况如下：

![](https://s1.ax1x.com/2023/06/25/pCNRmp6.png)

第二步

反推方案：

$i = 1,a[i] = 8,w[i] = 7,f[20 - 7] = f[12] \ne f[20] - 1$；

$i = 2,a[i] = 7,w[i] = 3,f[20 - 3] = f[17] = f[20] - 1$；

输出 $7$；

$f[17 - 3] = f[14] = f[17] - 1$；

输出 $7$；

$f[14 - 3] = f[11] = f[14] - 1$；

输出 $7$；

$f[11 - 3] = f[8] = f[11] - 1$；

输出 $7$；

$f[8 - 3] = f[5] = f[8] - 1$；

输出 $7$；

$f[5 - 3] = f[2] \ne f[5] - 1$；

$i = 3,a[i] = 4,w[i] = 4,f[5 - 4] = f[1] \ne f[5] - 1$；

$i = 4,a[i] = 3,w[i] = 5,f[5 - 5] = f[0] = f[5] - 1$；

输出 $3$；

综合上面两个步骤，我们可以看出：

将 $f[0]$ 设为 $1$，之后，$f$ 数组中所有由 $f[0]$ 转移得到的数据都加上了 $1$，这样做的目的是，在第二步反推时，倒数几步（即若 $f[0] = 0$，则 $f[0]$ 与 $f[1]$，$f[2]$ 都为 $0$），不会出现“一个状态由多个情况转移而来”的情况（因为根据本题题意可知，本题要求 dp 转移时具有唯一性），故将 $f[0]$ 特殊处理。

同理，我们可知，对于 $f$ 数组的处理也可采用 “先全部赋值为 $-1$，再将 $f[0]$ 赋值为 $0$” 等方法。

最后附上代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;

int n, m;
int number[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int f[N], a[15], w[15];

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i ++ ) {
		cin >> a[i];
		w[i] = number[a[i]];
	}

	f[0] = 1;
	for (int i = 1; i <= m; i ++ )
		for (int j = w[i]; j <= n; j ++ )
			f[j] = max(f[j], f[j - w[i]] + 1);
	sort(a + 1, a + m + 1, greater<int>());//降序
	for (int i = 1; i <= m; i ++ )
		w[i] = number[a[i]];

	while (n) {
		for (int i = 1; i <= m; i ++ )
			if (w[i] <= n && f[n - w[i]] == f[n] - 1) {
				n -= w[i];
				cout << a[i];
				break;
			}
	}
	cout << endl;
	return 0;
}
```

---

## 作者：Red0rangE (赞：0)

## 思路

看到是由火柴棍拼接便可以想到不同数字对应不同权值，由此可以试图使用完全背包。

显然我们的策略是先找出数位最多的（因为这样肯定最大），再反向找出这些数字并由大到小输出。

具体实现方式就是一次完全背包加上一次贪心。

## Part 1

完全背包，价值为数字所带来的数位个数（当然是 1），权值是使用的火柴棒数量，直接上模板。

```cpp
for(int i=1;i<=m;i++)
    for(int j=w[a[i]];j<=n;j++)
        dp[j]=max(dp[j],dp[j-w[a[i]]]+1);
```

## Part 2

贪心，先由大到小将可用数字排序，不断在这些数字中按序寻找可用数字（即不断寻找可用最大数字），不断输出，直到火柴棍用完。

```cpp
sort(a+1,a+1+m,cmp);
while (1)
    for (int i=1;i<=m;i++)
        if (w[a[i]]<=n && dp[n-w[a[i]]]==dp[n]-1){
            putchar(a[i]+'0');
            n-=w[a[i]];
            if (!n) return 0;
            break;
        }
```

以上便是核心代码内容，是对 Dark_Sky 大佬的解释补充（因为我自己有些没看懂想了比较久），希望可以帮到各位大佬。

---

## 作者：Kketchup (赞：0)

## AT-abc118-d

[传送门](https://atcoder.jp/contests/abc118/tasks/abc118_d)

**题意简述**

有 $n$ 根火柴, 一共有 $1-9$ 这 $10$ 种数字，给出 $m$，表示只能用 $m$ 种数字。接下来是 $m$ 个能用的数字。数字 $1,2,3,4,5,6,7,8,9$ 分别需要 $2,5,5,4,5,6,3,7,6$ 根火柴，要求 $n$ 根火柴全部都用完且拼成的数字最大，输出这个数字。

**题目解析**

看到此题，第一反应是完全背包。容量是消耗火柴根数，价值是？

发现要让拼成数字最大，但凡有点数学知识得知位数越多数越大，故首先让位数变多。

设 $f_i$ 表示 $i$ 根火柴在题目给的 $m$ 种数字中正好用完情况下最多的位数。完全背包计算 $f$ 数组。

位数相同，从前向后，前面的数越大越好，考虑递归从大到小枚举此位是否能填此数。

即判断 $f_n=f_{n-id_{a_{i}}}+1$（$n$ 为剩余火柴数，$id$ 数组表示 $1-9$ 消耗的火柴数，$a$ 数组中是数据给出能用的数字，要在枚举前将 $a$ 数组从大到小排序。）

**具体实现**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e4+10;
int n,m;
int id[10]={0,2,5,5,4,5,6,3,7,6};
int f[N],a[N];
bool cmp(int a,int b){return a>b;}

void out(int n){
	for(int i=1;i<=m;++i){
		if(id[a[i]]>n) continue;
		if(f[n]==f[n-id[a[i]]]+1){
			printf("%d",a[i]);
			out(n-id[a[i]]);
			break;
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i) scanf("%d",&a[i]);
	sort(a+1,a+1+m,cmp);
	memset(f,-0x3f,sizeof(f)); 
	f[0]=0;
	for(int i=1;i<=m;++i){
		for(int j=id[a[i]];j<=n;++j){
			f[j]=max(f[j],f[j-id[a[i]]]+1);
		}
	}
	out(n);
	return 0;
}
```

---

## 作者：LaDeX (赞：0)

## 题意

你有 $n$ 根火柴，能拼成 $m$ 种数字，怎么拼能让拼出来的数字最大。

## 思路

一看就是个完全背包，容量 为 $n$ , 物品种类 为 $m$ 。

**要注意是正好拼完所有火柴**

通过观察样例 或 思考 可以发现，````long long```` 存不下答案，所以用 ````string````来存数组。

因此还要自己写一个比较函数。

规则：

1. 如果长度不相同，长度长的那个数更大。

2. 在不满足 条件 1 的情况下，字典序更大的那个数更大。

转移方程：

$dp[i]$ 为 正好用了 $i$ 根火柴能拼出来的最大数字（字符串）。

$Num[i]$ 为 拼 数字 $i$ 所需的火柴数量。

$A[i]$ 为 能拼出的第 $i$ 个数字。

$$ dp[i] = max(dp[i - Num[A[j]] + A[j], dp[i] ) $$

*注：$max$ 为自己写的比较函数，加法操作是字符串的加法*
。
## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N = 1e4 + 10;
string dp[N] = {""};
LL n, m, A[15];
// 每种数字所需火柴数量
LL number[10] = {0, 2, 5, 5, 4, 5, 6, 3, 7, 6};

// 比较函数 :
// （特殊情况，A 为 空('@')，返回 false，B 为 空('@')，返回 true）
// 如果 A > B 返回 true 否则 返回 false
// 比较规则：如果长度不相同，那么长度长的更大，否则按字典序比较 ( 前提是非空('@') )
bool Greater(string A, string B){
	if (A == "@")
		return false;
	if (B == "@")
		return true;
	if (A.size() != B.size())
		return A.size() > B.size();
	return A > B;
}

int main(){
//	ios :: sync_with_stdio(0);
//	cin.tie(0); cout.tie(0);
	
	cin >> n >> m;
	for (LL i = 1; i <= m; i ++){
		cin >> A[i];
	}
	
	// 初始化，要满足正好用完，一开始只有 0 是符合条件的，其他初始化为 ‘@’
	for (LL i = 1; i <= n; i ++){
		dp[i] = "@";
	}
	dp[0] = "";
	
	for (LL i = 1; i <= n; i ++){
		for (LL j = 1; j <= m; j ++){
			LL num = A[j];
			
			/* 
			切记一定要判，不要像我框架写错出现了奇怪的错误：
			terminate called after throwing an instance of 'std::logic_error'
				what():  basic_string::_M_construct null not valid
			*/
			if (number[num] > i || dp[i - number[num]] == "@")
				continue;
			
			// 新字符串
			string str = dp[i - number[num]] + (char)(num + '0');
			// 如果更大，那么转移
			if (Greater(str, dp[i]))
				dp[i] = str;
		}
	}
	
	cout << dp[n];
	return 0;
}

```

## The End

小结一下，
本题是一道完全背包问题，
不过要把数字转换为字符串来比较与操作

---

## 作者：Kobe_BeanBryant (赞：0)

### 题目大意：
给你有 $ n $ 根火柴棒和 $ m $ 种数字,并且告诉你数字 $ 1 $，$ 2 $，$ 3 $，$ 4 $，$ 5 $，$ 6 $，$ 7 $，$ 8 $，$ 9 $ 分别需要 $ 2 $，$ 5 $，$ 5 $，$ 4 $，$ 5 $，$ 6 $，$ 3 $，$ 7 $，$ 6 $ 根火柴。

求 $ n $ 根火柴全部都用完且后能拼成的最大数字。
### 解题思路：
- 运用动态规划。
- 将每个数字所需要的火柴棒存入一个数组中。
- 将较小的数值进行更新。
- 从小到大进行排序。
- 查找 $ n $ 次，及查找每一位上尽可能大的数值。
- 判断如果当前的数字是其中的最大值，输出当前的数字。
- 否则，直接查寻下一个值。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m;
int a[10],dp[10005];
int c[10]={0,2,5,5,4,5,6,3,7,6};//直接将每个数字所需要的火柴棒存入c数组中 
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=0;i<m;i++) 
		scanf("%d",&a[i]);//导入a[i]的值 
	dp[0]=1;//dp初始化 
	for(int i=0;i<m;i++)
		for(int j=c[a[i]];j<=n;j++)
			dp[j]=max(dp[j],dp[j-c[a[i]]]+1);//将较小的数值进行更新，用i根火柴棍能够得到的最大数 
	sort(a,a+m);//从小到大进行排序 
	m--;
	while(n){//查找n次，及查找每一位上尽可能大的数值 
		if(n-c[a[m]]>=0 && dp[n]==dp[n-c[a[m]]]+1)
			n-=c[a[m]],printf("%d",a[m]);//如果当前的数字是其中的最大值，输出当前的数字 
		else
			m--;// 如果当前的数字不是其中的最大值，查找下一个值 
	}
	return 0;//好习惯 
}

```
诚信做题，严禁抄袭。

---

