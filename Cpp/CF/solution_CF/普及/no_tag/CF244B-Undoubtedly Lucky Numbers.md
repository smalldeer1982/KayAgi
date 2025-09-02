# Undoubtedly Lucky Numbers

## 题目描述

**题意**

若一个正整数的十进制表示（最高位不为0）只包含数字x和y，则我们称它为幸运数。例如，如果x=4，y=7，那么47，744，4等数是幸运的。请你计算n以内有多少个幸运数。

## 说明/提示

1<=n<=1e9

## 样例 #1

### 输入

```
10
```

### 输出

```
10
```

## 样例 #2

### 输入

```
123
```

### 输出

```
113
```

# 题解

## 作者：wuyixiang (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF244B)

题目大意：问有多少个不超过 $n$ 的正整数只由数字 $x$ 和 $y$ 构成。

思路：如果直接把每个数依次枚举，肯定是会超时的。这时，我们不妨可以直接枚举 $x$ 和 $y$。因为可以估算得到，只由数字 $x$ 和 $y$ 构成的且小于 $10^9$ 的数最多只有 $2^{10} = 2048$ 个，再枚举 $100$ 次 $x$ 和 $y$ 也远不会超时。所以，一开始我们只要在主函数枚举 $x$ 和 $y$，然后在函数里计算输出结果就好了。此时的代码如下：

```cpp
#include <iostream>
#define int long long
using namespace std;
int n,ans;
void dfs(int x,int y,int num)
{
    if(num > n)return ;
    if(num != 0)ans ++;
    if(x != 0 || num != 0)dfs(x,y,num * 10 + x);//避免死循环
    dfs(x,y,num * 10 + y);
}
signed main()
{
    cin >> n;
    for(int i = 0;i <= 9;i ++)//枚举
        for(int j = i + 1;j <= 9;j ++)//枚举
            dfs(i,j,0);
    cout << ans;//答案
}
```
但是你会发现答案却多了好几倍。为什么呢？因为没有去重！当 $i = 1$ 时，不管 $j$ 是什么数，$\operatorname{dfs}$ 函数都会先枚举 $1$ 和 $11$ 这些数。所以，这里需要开一个 $\operatorname{map}$ 数组来记录去重。下面是调整后的代码：

```cpp
#include <iostream>
#include <map>
#define int long long
using namespace std;
map<int,int>mp;
int n,ans;
void dfs(int x,int y,int num)
{
    if(num > n)return ;
    if(num != 0 && !mp[num])ans ++;//去重
    mp[num] = 1;//记录过了，设为1
    if(x != 0 || num != 0)dfs(x,y,num * 10 + x);//避免死循环
    dfs(x,y,num * 10 + y);
}
signed main()
{
    cin >> n;
    for(int i = 0;i <= 9;i ++)//枚举
        for(int j = i + 1;j <= 9;j ++)//枚举
            dfs(i,j,0);
    cout << ans;//输出答案
}
```

提示：有时 $num$ 变量 $\le 10^9$ 但是乘上 $10$ 就会大于 $int$ 范围，所以请记得开 $long \space long$。

---

## 作者：QCurium (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF244B)
如有错误，我会立即更正。

## 题意简述

输入一个 $n$，求 $1$ 到 $n$ 中幸运数的个数。

幸运数是例如 $122$，$848$，$1$ 等由一个数或两个不同的数字组成的数的数字。

## 数据范围

$1\le n\le 10^9$

通过观察数据范围，我们知道如果用暴力一个一个算，只能得部分分。

可通过对幸运数的定义，我们可以得到思路。

我们可以枚举这两个数，再通过递归来对两个数进行组合。这样，时间复杂度就可以通过了。


然而这样递归，就会产生重复，可能有同学会用 bool 来存。
但是数据范围是 $10^9$，会 $MLE$，所以要用 **map** ~~别问我怎么知道的~~。


------------
~~分析的差不多了~~上代码。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e9+5;
int n,len=0;
map<int,bool>a;
int js(int x,int y,int ws,int num){
	if(ws==0){
		if(a[num])//判断是否重复 
			return 0; 
		a[num]=1;
		if(num<=n)
			return 1;
		else
			return 0;
	}
	int as=0;
	as+=js(x,y,ws-1,num*10+x);
	as+=js(x,y,ws-1,num*10+y);
	return as;
}
signed main(){
	cin>>n;
	int a=n;
	while(1){//计算n是几位数 
		if(a>=10){
			len++;
			a=a/10;
		}
		else
			break;
	}
	len++;
	int ans=0;
	for(int ln=1;ln<=len;ln++){//枚举数的位数 
		for(int i=0;i<=9;i++){
			for(int j=i+1;j<=9;j++){
				ans+=js(i,j,ln,0);
			}
		}
	}
	cout<<ans-1;//因为会把0算进去，所以要减一 
	return 0;
}
```
[提交记录](https://www.luogu.com.cn/record/117356998)

感谢观看，谢谢。

---

## 作者：Fiendish (赞：1)

本题难度不高，一眼看上去似乎是数位 $\text{dp}$，但其实是道搜索。

考虑搜索。题目中符合条件的数只由两个或以下不同的数字组成，比如 $22332$ 等。枚举这两个数字 $n,m$，要让已经构造出来的数 $now$ 依然符合要求就只能在它的后面插入 $i$ 或 $j$，实现方法就是 `now*10+n` 或者是 `now*10+m`，再拿上述构造出来的数进行搜索。

注意三个事情：

1. 在 $now$ 大于 $n$ 时就停止搜索；
2. 为了防止重复计算，可以用 `set` 维护构造出来的 $now$ 来去重；
3. 不开 `long long` 见祖宗。

贴上丑陋的代码：

```cpp
#include<iostream>
#include<set>
using namespace std;
long long n1;
set<long long> s;//用于去重
void dfs(long long n,long long m,long long now){
	if(now>n1) return;//及时回溯
	s.insert(now);
	if(now*10+n!=now) dfs(n,m,now*10+n);
	if(now*10+m!=now) dfs(n,m,now*10+m);//递归，构造下一种可能的答案
	return;
}
int main(){
	cin>>n1;
	for(int i=0;i<=9;i++)
		for(int j=0;j<i;j++)//枚举两种数字
			dfs(1ll*i,1ll*j,0);
	cout<<s.size()-1;//因为0会被算作正确答案，所以要减一
	return 0;
}
```

若有疏漏、不详之处，恳请各位大佬指点。

---

## 作者：sinestrea (赞：1)

### 答案可递推，才适合间隔打表。

我们设 $\operatorname{F}(N)$ 为 $[1,N]$ 的答案，$\operatorname{Check}(X)$ 表示判断 $X$ 是否合法，那么 $\operatorname{F}(N)=\operatorname{F}(N-1)+\operatorname{Check}(N)$。

### 用法

观察数据 $(1\le n\le 10^9)$ 那么我们就可以记录 $[1,1\times 10^6],[1,2\times 10^6],[1,3\times 10^6],\ldots,[1,1000\times 10^6]$ 的答案。

由此可见 $\operatorname{Check}(i)$ 执行次数不会超过 $10^6$。


### 打表的代码


```cpp
#include <bits/stdc++.h>


bool Check(int Num) {
    int X = Num % 10, Y{};
    while (Num % 10 == X) Num /= 10;
    Y = Num % 10;
    while (Num) {
        if (Num % 10 != X && Num % 10 != Y) return 0;
        Num /= 10;
    }
    return 1;
}


int Cnt{};


int main() {
    freopen("out", "w", stdout);
    std::cout << "int Arr[] = {0";
    for (int i = 1; i <= 1000; i++) {
        for (int j = (i - 1) * 1000000 + 1; j <= i * 1000000; j++) {
            Cnt += Check(j);
        }
        std::cout << ',' << Cnt;
    }
    std::cout << "};";
}
```

### AC代码

```cpp
#include <bits/stdc++.h>


inline bool Check(int Num) {
    int X = Num % 10, Y{};
    while (Num % 10 == X) Num /= 10;
    Y = Num % 10;
    while (Num) {
        if (Num % 10 != X && Num % 10 != Y) return 0;
        Num /= 10;
    }
    return 1;
}


int N{}, Cnt{};
//int Arr[] = 此处过于磅礴;


int main() {
    std::ios::sync_with_stdio(0);
    std::cin >> N;
    int K = N / 1000000;
    Cnt = Arr[K];
    for (int i = K * 1000000 + 1; i <= N; i++) {
        Cnt += Check(i);
    }
    std::cout << Cnt;
}
```

---

## 作者：fz20181223 (赞：1)

这是一篇不用搜索的题解（缺点就是码量有点大）。

一种暴力的做法是枚举 $1$ 到 $n$ 的所有数，复杂度 $O(n\log_{10}n)$ （我的暴力复杂度为 $O(\log_{10}n)$ ），对于 $n=10^9$ 的数据肯定过不了。

但是我们可以构造出哪些数可行：

首先，对于一个 $x$ 位的 $n$ ，

如果 $x<3$ ，由于数位只有两个（甚至只有一个），所以所有小于等于 $n$ 的数都是幸运的。

如果 $x\ge3$ ，则设初始答案为 $99$ （即 $1$ 到 $99$ 的所有数都行）。

先算对于位数 $k$ （保证 $3\le k<x$ ）对答案的贡献。由于 $k$ 位的数肯定小于 $x$ 位的 $n$ ，所以构造出来的答案都可行。我们可以用下面的方法：

1. 对于每两个非零不等数字，不难发现一共有 $2^k - 2$ 种答案（每一位都有两种可能，一共 $k$ 位，但是要防止两种只用一种数码的情况）。通过计算，我们发现一共有 $9 \times 8 \div 2 = 36$ 种不同的排列组合，所以答案要加上 $36 \times (2^k-2)$ 。

2. 对于 $0$ 和一个非零数字，由于最高位不能为 $0$ ，所以最高位一定是那个非零数字，此时对于其他 $k-1$ 位，每位都有两种可能（但需要去除其他位数与最高位相等的情况），对于每种情况，一共 $2^{k-1}-1$ 种答案。由于十进制下非零的数字一共九个，所以对于这种情况，答案需要加上 $9 \times (2^{k-1}-1)$ 。

3. 对于一个只用一个非零数字的数，每一种位数只有 $9$ 个答案，所以答案要再加 $9$ ，与上一种情况加起来就是答案要加上 $9 \times 2^{k-1}$ 。其实这种情况可与上面那种合并。

对于 $x$ 位数的全体数对答案的贡献，思路与上面的方法大致相同，只不过你需要判断每一个组成的数是否大于 $n$ 。

最后，**一定要开 long long ！**（否则 \#6 过不去）

另附： AC 代码（不要抄！）
```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
#define pii pair<int,int>
#define mii map<int,int>
#define mset(a,x) memset(a,x,sizeof(a))
#define msetl(a) memset(a,0x3f,sizeof(a))
#define int ll
using namespace std;
const int err=-120712^7869^12174,eps=1e-9;
int n,fdig;
int size(int n,int &p){
	string st;stringstream ss;
	ss<<n;ss>>st;
	p=st[0]-'0';
	return st.size();
}
bool check(int x,int y,int s,int size){
	int q=0;
	for(int i=0;i<size;++i){
		int d;
		if(s&(1<<i)) d=x;
		else d=y;
		q=(q<<1)+(q<<3)+d;
	}
//	if(q<=n) printf("%d\n",q);
//	printf("%d %d %d %d %d\n",x,y,s,q,q<=n);
	return q<=n;
}
signed main(){
	cin>>n;
	if(n<102){
		printf("%d",n);
		return 0;
	}
	//not up to n's len
	int ans=99,sz=size(n,fdig);//1~99 all avaliable
	for(int dig=3;dig<sz;++dig){
		ans+=(1<<dig)*36-72;//1~9 match 1~9(different)
		ans+=(1<<dig-1)*9;//0 match 1~9 & 1~9 match itself
	}
//	printf("%d\n",ans);
	//up to n's len
	for(int i=1;i<=fdig;++i){
		for(int j=i+1;j<10;++j){//1~9 match 1~9(different)
			for(int s=1;s<(1<<sz)-1;++s){
				ans+=check(i,j,s,sz);
			}
		}
//		if(i<fdig){
//			ans+=(1<<sz-1);
//			continue;
//		}
		for(int s=0;s<(1<<sz-1);++s){//0 match 1~9 & 1~9 match itself
			ans+=check(i,0,s<<1|1,sz);
		}
	}
	printf("%d",ans);
	return 0;}
```

---

## 作者：HyyypRtf06 (赞：1)

~~我相信肯定有把$∣n∣$看作是绝对值的童鞋（比如我~~，这里的$∣n∣$是$n$的长度。

附一张图：~~(不算灵魂画手吧……~~
![](https://cdn.luogu.com.cn/upload/image_hosting/mly2h6c1.png)

口胡：枚举$i,j$，要求$i,j$不等且不与之前的重复（（2,5）(5,2)也算重复），然后$2^{∣n∣}$爆搜，统计答案

↑纯属口胡

**Tip:下面这个程序答案要`-1`，因为这个set里面第一个元素是0，所以需要减$1$把$0$去掉**

先上代码（其实差不多：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<set>
using namespace std;
set<long long>s;//set自动去重
long long n;
void dfs(long long now,int x,int y){//now表示构造的数，x，y如题
	if(now>n){//如果构造的数大于了n，就直接return
		return;
	}
	s.insert(now);//压入set
	if(10*now+x!=now){//后端加上x
		dfs(10*now+x,x,y);
	}
	if(10*now+y!=now){//后端加上y
		dfs(10*now+y,x,y);
	}
	return;
}
int main(){
	cin>>n;
	for(int i=0;i<10;i++){
		for(int j=0;j<i;j++){//这里注意j<i，因为i=1,j=2和i=2,j=1是一样的。
			dfs(0,i,j);
		}
	}
	cout<<s.size()-1<<endl;
	return 0;
}
```

The End.

---

## 作者：codeLJH114514 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF244B)

## 题目大意

如果一个数仅包含由 $x,y$ 构成则称这个数为幸运数字。（$x$ 可以等于 $y$，$0 \le x, y \le 9$，**幸运数字不包含前导零**，**幸运数字均为正整数**。）

问有多少个幸运数字不超过 $n$。

## 数据范围

$1 \le n \le 10^9$。

## 题目解法

最朴素的解法就是直接枚举 $i = 1 \to n$，判断 $i$ 是否是幸运数字，判断一次时间复杂度为 $\mathcal{O}(\log_{10} n)$，总时间复杂度 $\mathcal{O}(n \log_{10} n)$，明显过不了。

可以发现，幸运数字其实在 $n = 10^9$ 时很稀疏，实际 $10^9$ 以内只有不到 $5 \times 10^4$ 的幸运数字。

所以，我们可以构造幸运数字。

首先枚举 $x,y$，然后再深搜，每一次深搜都要搜到小于等于 $n$ 且仅有 $x,y$ 组成的幸运数字。

深搜时，记录现在构造出的幸运数字 $m$，如果 $m$ 已经超过了 $n$ 则返回，否则继续向 $m \times 10 + x$ 和 $m \times 10 + y$ 深搜。

小细节：因为 $x,y$ 和 $y,x$ 构造出的幸运数字完全一样，所以我们默认 $y \le x$。

如果 $x = y = 0$ 就无法构造出任何合法的幸运数字。

该算法时间复杂度为 $\mathcal{O}(k)$，$k$ 是幸运数字的个数，之所以是这个复杂度是因为几乎每次进入深搜函数都可以搜出来一个幸运数字。

注意，因为 $n$ 为 $10^9$ 量级时，有可能会爆 `int`，出现负数，然后就会死循环。如果不开 `int64/ll` 的话会在 $\#6$ 超时。

## 完整代码

```cpp
// CF244B Code by luogu|528472
#include <algorithm>
#include <iostream>
#include <unordered_set>
#define int int64_t
int n, ans;
std::unordered_set<int> s; // 为了判重用了 unordered_set
void Search(int, int, int);
signed main() {
    std::cin >> n;
    for (int x = 0; x <= 9; x++)
        for (int y = 0; y <= x; y++)
            if (x != y or y != 0)  
                Search(x, y, 0);
    std::cout << s.size() << "\n";
    return 0;
}
void Search(int n, int m, int now) {
    if (now > ::n) 
        return ;
    if (now != 0) {
        s.insert(now);
        Search(n, m, now * 10 + n);
        Search(n, m, now * 10 + m);
    } else { // 如果现在搜出来的幸运数字等于零，也就是还没有开始搜索，就只能进入到没有前导零的分支中去。
        if (n != 0)
            Search(n, m, now * 10 + n);
        if (m != 0)
            Search(n, m, now * 10 + m);
    }
}
```

---

## 作者：Zhuluoan (赞：0)

## 题目简述

给定一个 $n$，问有多少个小于等于 $n$ 的数只由两个不同的数字 $x$ 和 $y$ 组成。

## 题目分析

直接枚举肯定不行，我们考虑枚举 $x$ 和 $y$，再利用深搜，生成所有不大于 $n$ 且只由 $x$ 和 $y$ 组成的数字，利用 `map` 去重，统计答案即可。

## 代码
```cpp
#include<iostream>
#include<map>
using namespace std;
#define int long long
int n,ans;
map<int,bool> vis;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
	    if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
	    x=(x<<1)+(x<<3)+ch-48;
	    ch=getchar();
	}
	return x*f;
}
inline void write(int x)
{
    if(x<0)
	{
    	putchar('-');
		x=-x;
	}
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
void check(int a,int x,int y,int cnt)
{
	if(cnt>10||a>n) return;
	if(a<=n&&a!=0&&!vis[a])
	{
		ans++;
		vis[a]=1;
	}
	check(a*10+x,x,y,cnt+1);
	check(a*10+y,x,y,cnt+1);
}
signed main()
{
	n=read();
	for(int i=0;i<=9;i++)
	{
		for(int j=i+1;j<=9;j++)
		{
			check(0,i,j,0);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：FreedomKing (赞：0)

### 思路

很诈骗的题，某不知名夏季集训在讲数位 DP 的时候挂上了这道题，许多同学惨遭诈骗。

考虑数据范围，发现虽然 $1\le n\le 10^9$，但是事实上我们只需要用 $10\times 10$ 的复杂度枚举那两个数 $x,y$，然后再枚举数的每一位是 $x$ 还是 $y$，时间复杂度完全没有问题。

然后需要考虑一下 $0$ 的问题，在搜索时特判以避免出现类似 $0\times 10+0$ 构造完的数依然等于 $0$ 的情况。由于可能有重复的数，可以用 `set` 存储然后直接输出它的大小。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define lc (p<<1)
#define rc (p<<1|1)
using namespace std;
const int N=1e6+5,xN=1e7+5,mN=1e4+5;
//const int mod=1e9+7,mmod=998244353;
int mod;
map<pair<int,int>,bool>mp;
priority_queue<int,vector<int>,less<int>>pq;
vector<int>e[N];
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
namespace FreedomKing_qwq{
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){x/=gcd(x,y);return (x*y);}
	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int abs(int x){return (x>0?x:-x);}
}
int n=qr;
set<int>ans;
inline void dfs(int now,int x,int y){
	if(now>n) return;
	ans.insert(now);
	if(now*10+x!=now) dfs(now*10+x,x,y);
	if(now*10+y!=now) dfs(now*10+y,x,y);
	return;
}
signed main(){
	for(int i=0;i<=9;i++)
		for(int j=0;j<=9;j++)
			dfs(0,i,j);
	qw(ans.size()-1);//一开始把 0 也算进去了，需要减去。
	return  0;
}
```

---

## 作者：Crazyouth (赞：0)

**翻译**

给定 $n$，求 $[1,n]$ 内有多少最多由两个数字组成的数。

**分析**

考虑暴搜，枚举那两个数字，然后再枚举由这两个数字组成的小于 $n$ 的数，丢到 set 里去重，就做完了。要注意的是，为避免因前导零死循环，我们应特判原数是零且那两个数字有零的情况。最后输出 set 的元素个数减一即可（因为有一个数是 $0$）。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
set<long long> s;//去重set
void dfs(int x,int y,long long now)//暴搜过程
{
	if(now>n) return;//已经大于n，直接退
	s.insert(now);//丢进set
	if(now==0)//特判
	{
		if(x) dfs(x,y,now*10+x);//往没有前导零的地方搜
		if(y) dfs(x,y,now*10+y);
	}
	else
	{
		dfs(x,y,now*10+x);//拓展到下一个数
		dfs(x,y,now*10+y);
	}
}
int main()
{
	cin>>n;
	for(int i=0;i<=9;i++)//枚举那两个数字
	for(int j=0;j<i;j++)
	dfs(i,j,0);
	cout<<s.size()-1;//减去一个数字0再输出
	return 0;
}

---

## 作者：Timon080923 (赞：0)

[原题链接](https://codeforces.com/problemset/problem/244/b)  
这道题还是比较简单的，和[这题](https://codeforces.com/problemset/problem/9/C)比较相似。  
题目大意：求 $n$ 以内有多少个最多包含两个数字的数有多少个。  
思路：因为数字一共只有 $10$ 个，所以可以直接枚举两个数字 $i$ 和 $j$ 的所有情况，然后dfs，每次在当前数字的末尾加上 $i$ 或者 $j$，装到set里自动去重就行了。  
代码:    
```cpp
#include<bits/stdc++.h>
using namespace std;
set<long long>s;//记得开long long
long long n;
void dfs(long long x,int y,int z){//x表示当前的数，y和z表示枚举的两个数字
	if(x>n)//到这里就不用继续搜索了
		return;
	s.insert(x);//装到set里自动去重
	if(10*x+y!=x)//如果y是0的话就会进入死循环
		dfs(10*x+y,y,z);//加上其中一个数字
	if(10*x+z!=x)
		dfs(10*x+z,y,z);
}
int main(){
	scanf("%I64d",&n);//注意输入格式
	for(int i=0;i<10;i++)//枚举两个数字
		for(int j=0;j<i;j++)//可以缩小第二个数字的枚举范围
			dfs(0,i,j);
	printf("%d",s.size()-1);//记得减去0
	return 0;
}
```  
谢谢观赏！  

---

## 作者：Supor__Shoep (赞：0)

首先理解到判重，我们可以使用集合数组存放数值。由于没有给定 $x$ 和 $y$ 的值，我们肯定是要挨个挨个枚举 $x$ 和 $y$ 的值，也就是一个双重循环。

有了这些框架，我们就可以快乐地开始搜索了。萌新们肯定都是一直枚举到 $n$ 统计个数的，这里我们利用给定的两个值，按照位数一直循环，直到这个数字超过 $n$。然后我们要处理分支情况，对于 $k$ 这个数，我们为了满足只有两个数字组成，可以直接在后面加上 $x$ 和 $y$，组成一个新的 $k$ 值，然后搜索。

最后要注意一点，在输出的时候一定要输出:
```
cout<<a.size()-1
```
不要忘记减去一个 $1$。
```
#include<bits/stdc++.h>
using namespace std;
long long n,x,y;
set<long long> a;
void dfs(long long sum,long long pos)//sum表示数值，pos表示位数
{
    if(sum>n||pos>10)   return;//数值超过n或者位数超过10都要终止
    a.insert(sum);//如果合法，存入这个数
    dfs(sum*10+x,pos+1);
    dfs(sum*10+y,pos+1);
    //在末位后面加数等于在原数的基础上乘10再加上数
}
int main()
{
    cin>>n;
    for(x=0;x<10;x++)
    {
        for(y=0;y<10;y++)
        {
            dfs(0,0);//初始状态数值和位数都要清0
        }
    }
    cout<<a.size()-1;
    return 0;
}
```

---

