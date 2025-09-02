# Make Equal With Mod

## 题目描述

You are given an array of $ n $ non-negative integers $ a_1, a_2, \ldots, a_n $ . You can make the following operation: choose an integer $ x \geq 2 $ and replace each number of the array by the remainder when dividing that number by $ x $ , that is, for all $ 1 \leq i \leq n $ set $ a_i $ to $ a_i \bmod x $ .

Determine if it is possible to make all the elements of the array equal by applying the operation zero or more times.

## 说明/提示

In the first test case, one can apply the operation with $ x = 3 $ to obtain the array $ [2, 2, 0, 2] $ , and then apply the operation with $ x = 2 $ to obtain $ [0, 0, 0, 0] $ .

In the second test case, all numbers are already equal.

In the fourth test case, applying the operation with $ x = 4 $ results in the array $ [1, 1, 1, 1] $ .

## 样例 #1

### 输入

```
4
4
2 5 6 8
3
1 1 1
5
4 1 7 0 8
4
5 9 17 5```

### 输出

```
YES
YES
NO
YES```

# 题解

## 作者：RedLycoris (赞：9)

送 300iq 下 2400 的毒瘤题。

这题带有一定的诈骗性质。

首先，如果这个数列中即含有 $0$ 又含有 $1$，那么它肯定就是不合法的，因为模数要 $\geq 2$，所以 $1$ 永远是 $1$，$0$ 永远是 $0$。

然后我们对这个数列有没有 $1$ 进行分类讨论。

+ 这个数列里没有 $1$

诈骗。我们对这个数组按照从大到小排序，每次选择最大的那个数做为模数，让所有数对它取模即可。

因为他是最大的数，所以所有其他数肯定小于等于他。小于它的不变，等于它的和他一起变为 $0$。最终所有数都变为 $0$。

+ 这个数列里有 $1$

我们已经知道 $1$ 是动不了的，所以我们想让所有其他数都变为 $1$。

有个结论，就是当这个序列中存在两个连续的数时，它不合法；反之，他一定合法。

证明：

1.不存在两个连续的数时，这个序列合法

这个比较好证，还是从大到小排，对第 $i$ 大的数 $a_i$，让所有数都对 $a_i-1$ 取模即可。（因为不存在 $a_i-1$，所以不会有数变为 $0$）

2.存在两个连续的数时，这个序列不合法

设存在的两个连续的数为 $x,x+1$，那么无论取什么数做为模数，他们都不可能相等。

（他们之差为 $1$，只有当模数为 $1$ 的时候这个 $1$ 才能被消去，故不可能）

综上，~~写几个 if 和 for 就完事了~~

Code:

```cpp
using namespace std;
const int mxn=2e5+5;
int n,a[mxn];
inline void solve(){
	cin>>n;
	int hv0=0,hv1=0;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		if(a[i]==0)hv0=1;
		if(a[i]==1)hv1=1;
	}
	sort(a+1,a+n+1);
	if(hv0 and hv1){
		cout<<"NO\n";
		return;
	}
	if(!hv1){
		cout<<"YES\n";
		return;
	}
	for(int i=1;i<n;++i)if(a[i+1]==a[i]+1){
		cout<<"NO\n";
		return;
	}
	cout<<"YES\n";
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T=1;
	cin>>T;
	for(;T--;)solve();
	return (0-0);
}
```

---

## 作者：HPXXZYY (赞：4)

$\color{blue}{\texttt{[Analysis]}}$

这是一道思维题。而且是一道挺妙的思维题。

显然，因为模数 $\geq 2$，所以 $a_{1\cdots n}$ 里面的 $0$ 和 $1$ 是不会改变的。因此如果 $a_{1 \cdots n}$ 中同时含有 $0$ 和 $1$，那么答案一定是 `NO`。

如果 $a_{1\cdots n}$ 里不含有数字 $1$，那么我们每次把 $a_{1 \cdots n}$ 中的所有数对 $\max\limits_{i=1}^{n} \{ a_{i} \}$ 取模，则 $\max\limits_{i=1}^{n} \{ a_{i} \}$ 会变成 $0$，其它的数不变，最多 $n$ 次操作可以把 $a_{1 \cdots n}$ 全部变成 $0$。

但是如果 $a_{1 \cdots n}$ 不含 $0$，只含 $1$ 呢？这个比较复杂。

因为 $1$ 是不会改变的，所以最后所有数都必须想方设法地变成 $1$。对于一个数 $u$，如果 $u \mod v =1$，那么 $(u-1) \mod v =0$（显然吧），因此如果 $a_{1 \cdots n}$ 中同时含有 $k,k-1(k\geq 1)$，那么答案一定是 `NO`。

$\color{blue}{\texttt{[Solution]}}$

算法就特别简单啦，直接记录一下有没有 $0$ 和 $1$，分类讨论就可以了。

$\color{blue}{\texttt{[code]}}$

```cpp
const int N=2e5+100;

int a[N],n;

int main(){
	for(int T=1,Q=read();T<=Q;T++){
		bool Zero=false,One=false;
		
		n=read();
		for(int i=1;i<=n;i++){
			a[i]=read();
			if (a[i]==0) Zero=true;
			if (a[i]==1) One=true;
		}
		
		sort(a+1,a+n+1);
		n=unique(a+1,a+n+1)-a-1;
		
		bool flag=true;
		
		if (Zero&&One) flag=false;
		else if (!One) flag=true;
		else{
			for(int i=1;i<n;i++)
				if (a[i]+1==a[i+1]){
					flag=false;
					break;
				}
		}
		
		if (flag) printf("YeS\n");
		else printf("nO\n");
	}
	
	return 0;
}
```

---

## 作者：0xFF (赞：1)

#### 题目大意


------------
给定一个长度为 $n$ 的序列 $a$，每次选择一个大于等于 $2$ 的 $x$，将序列中所有的数替换成其除以 $x$ 后的余数。问能否在有限的操作次数内将整个序列中的数全部相等。

#### 思路分析


------------
可以将所有的序列分为两种，一种是操作后全部为 $0$ 的，一种是操作后全部为 $1$ 的。

首先考虑操作后全部为 $0$ 的情况。想要使得所有的数都为 $0$ 只需要每次令 $x$ 为序列中最大数的值。如果序列中没有 $1$ 出现那么必然可以满足题设，因为 $x \ge 2$，所以所有大于等于 $2$ 的数最终都可变为 $0$。

如果序列中有 $1$ 出现就考虑第二种情况，即序列中的数最终全部变化为 $1$，但是如果序列中有两个数差为 $1$，那么就无法找到一个数 $x$ 使得两个数都变为 $1$。因为可以发现想要使得两个数中的较大者变化为 $1$，那么必然需要 $x$ 等于此数减一，但是如果这样构造 $x$ 就会使得两数中的较小者变为 $0$，所以无法满足题意。

故只需讨论上述两种情况即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<vector>
#define int long long
using namespace std;
const int N = 100010;
const int INF = (1<<30);
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int a[N];
bool flag1,flag2;
signed main(){
	int T = read();
	while(T--){
		int n = read();
		for(int i=0;i<n;i++){
			a[i] = read();
		}
		sort(a,a+n);
		flag1 = true , flag2 = true;
		for(int i=0;i<n;i++){
			if(a[i] == 1) flag1 = false;
			if(i < n - 1 && a[i] == a[i+1] - 1) flag2 = false;
		}
		if((flag1 == false)&&(flag2 == false)){
			printf("NO\n");
		}
		else printf("YES\n");
	}
	return 0;
}
```


---

## 作者：Dedaka (赞：1)

## 题意简述

------------
- 给定 $T$ 组数据，每组数据包括 $n$ 和 $n$ 个非负整数。

- 每次操作可将数列中每个数对一个任意的整数 $x$ 取模。

- 询问是否可以通过一次或多次操作使数列中的每个数相同。

- $x \ge 2$，$1 \leq T \leq 10^4$，$1 \leq n \leq 10^5$，$1 \leq a_i \leq 10^4$。

## 题目分析

------------
本题只要求询问是与否，不要求输出 $x$，所以应该是一道数论题。

### 思路

------------
如果使 $x$ 为最大的那个数，那么最大的那个数会变成 $0$，其它数不变。
每次这样操作就可以使所有大于等于 $2$ 的数变为 $0$。那么，剩下的就是解决剩下的 $0$ 和 $1$ 的问题了。我们可以分类讨论：

第一种情况，所有数都大于等于 $2$ 或等于 $0$，肯定可以使所有数变为 $0$。

第二种情况，同时有 $0$ 和 $1$，因为不能通过操作影响小于 $2$ 的数，所以肯定不能成功。

第三种情况，只有 $1$ 存在，这种情况会比较复杂。我们可以让每个数都对该数减去 $1$ 取模使它变为 $1$。然而如果存在某两个数差值为 $1$ 则必然使小的那个数变为 $0$，不能成功。反之就能是每个数都变成 $0$ 了，成功！

### 细节

------------
对于第三种情况，我们可以对数列从大到小排序，来检查是否存在相差为 $1$ 的数。另外，我们可以可以用两个布尔型变量 $fg$ 和 $fg1$ 来标记是否存在 $1$ 和 $0$，从而进行判断。

**记得清空数组和标记！**

## 代码

------------
```
#include<bits/stdc++.h>
#define mx 200010
using namespace std;
int t,n,a[mx];
bool fg,fg1;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		memset(a,0,sizeof(a));
		fg=fg1=0;//清空标记 
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]==0){//如果有0 
				fg=1;
			}
			if(a[i]==1){//有1 
				fg1=1;
			}
		}
		if(fg==1&&fg1==1){//情况2
			puts("NO");
			continue;
		}
		if(fg1==0){//情况1
			puts("YES");
			continue;
		}
		fg=0;
		sort(a+1,a+1+n);//排序 
		for(int i=2;i<=n;i++){
			if(a[i]-a[i-1]==1){//存在两个数之间差1 
				fg=1;
				break;
			}
		}
		if(fg==1){
			puts("NO");
		}else{
			puts("YES");
		}
	}
	return 0;
}
```


---

## 作者：zbk233 (赞：0)

## 解题思路

这道题实际就是一道分类讨论题。

- 当序列中同时有 $0$ 和 $1$ 时：

所有大于或等于 $2$ 的模数，都不能改变 $0$ 和 $1$，所以这种情况显然是不合法的。

- 当序列中没有 $1$ 时：

无论是什么模数，都不能改变 $0$，所以我们的思路是让剩下的所有数变成 $0$。

很明显，每个数取模它的因数就能变成 $0$，并且对于每个数，$1$ 和它本身都一定是它的因数。由于无法取 $1$，模数就只能取它本身。

于是我们的策略就是从大到小，把每个数都取模它本身，这样就能使当前最大值变成 $0$ 而比它小的值不变。

- 当序列中有 $1$ 而没有 $0$ 时：

大于或等于 $2$ 的模数，都不能改变 $1$，所以我们的思路是让剩下的所有数变成 $1$。

类似于上面的思路，我们可以从大到小地让每一个 $a_i$ 都取模 $a_i-1$。

但是当 $a_i-1$ 存在时，$a_i-1$ 取模 $a_i-1$ 就会变成 $0$。

所以，有连续的数时这个序列不合法；反之，这个序列合法。

## 参考代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100005];
int main(){
    int T;
    cin>>T;
    while(T--){
        int n,flag1=0,flag2=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(a[i]==1) flag1=1;
            if(a[i]==0) flag2=1;
        }
        if(flag1&&flag2){
            cout<<"NO\n";
            continue;
        }
        sort(a+1,a+n+1,greater<int>());
        if(flag1){
            bool f=1;
            for(int i=1;i<=n;i++){
                if(a[i]==a[i-1]-1){
                    f=0;
                    break;
                }
            }
            if(f){
                cout<<"YES\n";
            }else{
                cout<<"NO\n";
            }
        }else{
            cout<<"YES\n";
        }
    }
    return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1656C](https://www.luogu.com.cn/problem/CF1656C)

* **【解题思路】**

当数组中小于 $2$ 的数没有 $1$ 时，我们可以每次操作都模最大的数。最后数组会变成全 $0$。

否则，我们可以每次操作都模最大的数减 $1$。容易发现当存在一个数 $x$，使得数组中存在 $x$ 与 $x-1$ 时无解。无论模什么数，它们在模意义下都差 $1$。因此它们不可能相等。

这个无解条件同样对 $0,1,2$ 适用。不过比赛的时候为了求稳还是判了一下。

* **【代码实现】**

```cpp
#include <algorithm>
#include <iostream>
#include <array>

using namespace std;

array<int,100000> nums;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		int cnt,tmp;
		bool have_1=false,have_0=false,have_2=false;
		cin>>cnt;
		for(int i=0;i<cnt;i++)
			cin>>nums[i],tmp=nums[i],have_1=have_1||tmp==1,have_0=have_0||!tmp,have_2=have_2||tmp==2;
		if(have_1&&(have_2||have_0))
		{
			cout<<"No";
			goto nextcase;
		}
		if(!have_1)
		{
			cout<<"Yes";
			goto nextcase;
		}
		sort(nums.begin(),nums.begin()+cnt);
		for(int i=0;i+1<cnt;i++)
			if(nums[i+1]-nums[i]==1)
			{
				cout<<"No";
				goto nextcase;
			}
		cout<<"Yes";
		nextcase:cout<<'\n';
	}
	return 0;
}


```

---

## 作者：BorisDimitri (赞：0)

## 题意概括
思维题。

给出一个长度为 $n$ 的序列 $a$。

可以进行无限次操作，每次操作可以选择一个整数 $x$ 满足 $2 \le x$，对于所有的 $1 \le i \le n$ 使 $a_i = a_i \bmod x$。

问能否找到一种操作方案使得序列中的每一个元素相等。

## TIPS

给出一个关键性质，建议看完性质，自行思考过后再看题解。

对于一个整数 $t$，有 $t \bmod t = 0$，$t \bmod (t-1) = 1$。

## 题解

考虑分类讨论。

1. 如果序列中不含有 $1$，则每次 $x$ 取序列的最大值 $max(a)$，若干次操作后序列每一个元素都为 $0$。
2. 如果序列中包含 $1$，又分两种情况：
  - 若序列中不包含连续的两个数，即存在 $1 \le i < j \le n$，满足 $a_i = a_j-1$，则每次 $x$ 取序列的最大值 $max(a)-1$，若干次操作后序列每一个元素都为 $1$。
  - 若序列中包含连续的两个数，则不存在合法方案。
  
## code
```cpp
const int N = 1e5 + 10;
int n;
int a[N];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+1+n);
    bool one = 0, suc = 0;
    for(int i=1;i<=n;i++)
    {
        if(a[i] == 1) one = 1;
        if(i < n && a[i] + 1 == a[i+1]) suc = 1;
    }
	
    if(one && suc) cout<<no;
    else cout<<yes;
}
```

---

## 作者：hyman00 (赞：0)

## 001 题意

有一个长度为 n 的序列 a ，每次操作你可以选择一个 x ( $x\ge2$ )，让每一个 $a_i :=a_i\%x$。

多测，问是否能通过任意次操作让 a 全相同。

## 002 思路

首先，设 $mi$ 是最小数，$mx$ 是最大数。

### 1.$mi\ge 2$

我们按 $x=10^9,x=10^9-1,\dots,x=3,x=2$ 的顺序操作，最终一定全为 $0$ ，答案为 `YES` 。

### 2.$mi=1$

易知，$mi$ 一直是 $1$。

如果有两个数相差 $1$ ，答案为 `NO` ，因为要么较大数变成 $0$，要么一直相差 $1$ 。

否则，每次取 $x=mx-1$ ，将 $mx$ 变成 $1$ 。

### 3.$mi=0$

如果有 $1$，答案为 `NO`，因为无论怎么操作，$1$ 永远不会变成 $0$ 。

其他情况与第一个类似，答案为 `YES`。

## 002 代码

附上丑陋的代码

```c++
void run(){
	int n;
	cin>>n;
	vi v(n);
	rep(i,n)cin>>v[i];
	sort(all(v));
	if(v[0]>=2){
		cout<<"YES\n";
		re;
	}
	if(v[0]==1){
		rep(i,n-1){
			if(v[i+1]==v[i]+1){
				cout<<"NO\n";
				re;
			}
		}
		cout<<"YES\n";
		re;
	}
	rep(i,n){
		if(v[i]==1){
			cout<<"NO\n";
			re;
		}
	}
	cout<<"YES\n";
}
```

---

## 作者：I_am_Accepted (赞：0)

### Analysis

文中所有 $mx$ 均表示当前 $\{a\}$ 中最大值。

如果序列中没有 $1$，那我们依次 $\text{mod}\ mx$ 就可以让所有数变为 $0$，故答案为 YES。

否则，判断是否有两个相邻（值为 $x$ 和 $x+1$）的数。若无，则每次 $\text{mod}\ (mx-1)$ 即可使所有数变为 $1$，故答案为 YES。

若有，则答案为 NO，**证明：**

设相邻的两个数值为 $c$ 和 $c+1$，我们证明这两个数自始至终是相邻的，以证明原命题。

若在某次操作后 $c$ 和 $c+1$ 不连续，显然 $c+1$ 变为 $0$（只有通过同余系的循环才能让这两个不连续）。那序列中同时存在了 $0$ 和 $1$，这样无解。$\blacksquare$

### Code

[Link](https://codeforces.com/contest/1656/submission/150891475)

---

## 作者：caibet (赞：0)

### 题意：

有一个长度为 $n$ 的数列 $\{a_i\}$，每次可以把数列所有的数模一个不小于 $2$ 的数，求能否通过若干次操作让整个数列值相等。

### 解法：

分两种情况：

- 最后的数全为 $0$
   
  除了 $1$ 外（题目要求模数不能为 $1$），所有的数都可以通过模它自己来变成 $0$。
  
  于是只要没有出现 $1$，我们就从大到小一个一个模自己（因为当 $x<y$ 时，$x\mod y=x$，不会影响原数），最后达到全为 $0$ 的效果。
  
  举个例子，样例中的 $\{2,5,6,8\}$。
  
  - 整个数列模去 $8$，原数列变为 $\{2,5,6,0\}$。
  - 整个数列模去 $6$，原数列变为 $\{2,5,0,0\}$。
  - 整个数列模去 $5$，原数列变为 $\{2,0,0,0\}$。
  - 整个数列模去 $2$，原数列变为 $\{0,0,0,0\}$。
  
  逐个击破，达到效果。
  
  因此在这种情况下，总能达到题目要求。
  
但是如果出现了 $1$？$1$ 麻烦在它模去任何不小于 $2$ 的数还是 $1$，也就是说如果数列里有 $1$，那么我们只能尽力做到——

- 最后的数全为 $1$

  考虑也从大到小逐个击破。对于数列中的一个数 $x$，我们找一个数 $k$ 使 $x\mod k=1$ 且不会对其它数造成影响。
  
  因为 $k$ 越小，越可能使某个数 $\mod k=0$，因而我们应该取最大的 $k$。
  
  显然，我们要找的 $k$ 就是 $x-1$。如果原数列中存在 $x-1$，那么它模去 $k$ 就会等于 $0$，这样我们就无能为力了，无解。
  
  无解的例子：数列 $\{1,1,4,5,1,4\}$。
  
  - 尝试将整个数列模去 $4$ 使 $5$ 能变为 $1$，但数列中存在 $4$，如果模去 $4$ 数列变为 $\{1,1,0,1,1,0\}$，于是无解。
  
  有解的例子：数列 $\{1,1,45,14\}$。
  
  - 尝试将整个数列模去 $44$ 使 $45$ 能变为 $1$，正好数列中不存在 $44$，于是数列变为 $\{1,1,1,14\}$。
  
  - 尝试将整个数列模去 $13$ 使 $14$ 能变为 $1$，正好数列中不存在 $13$，于是数列变为 $\{1,1,1,1\}$。
  
  这里我们可以通过排序原数组来判断是否有两个数相邻。详见代码。
  
整合两种情况，就能得到代码。

```cpp
namespace{
	const int lim=1e5+2;
	int T;
	int n,a[lim];
	bool tag;
	void solve(){
		n=read();
		F(i,1,<=n) a[i]=read();
		tag=0;
		F(i,1,<=n){
			if(a[i]==1){
				tag=1;//有 1
				break;
			}
		}
		if(tag){
			sort(a+1,a+n+1);
			F(i,1,<n){
				if(a[i]==a[i+1]-1){//如果有两个数相邻，排序后这两个数值一定会在相邻位置出现
					puts("NO");
					return;
				}
			}
		}
		puts("YES");
	}
	void work(){
		T=read();
		while(T--) solve();
	}
}
```

#### 教训：

CF 的操作题做法往往和样例解释有很大差别。本人就因为看了样例解释被出题人限制了思维，卡了一个小时/kk

---

