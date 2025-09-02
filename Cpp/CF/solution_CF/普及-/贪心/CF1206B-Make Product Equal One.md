# Make Product Equal One

## 题目描述

给你一个有 $n$ 个数的数组。你可以用 $x$(x为任意正整数) 的代价将数组中的任意一个数增加或减少 $x$ ，你可以重复多次此操作。现在需要你用若干次操作使得 $a_1·a_2·...·a_n = 1$ （数组的乘积为1）。

比如，当 $n=3$ 和数组为 [**1,-3,0**] 时，我们最少需要花费 $3$ 的代价：用 $2$ 的代价把 -$3$ 增加到 -$1$ ，再用 $1$ 的代价把 $0$ 减少到 -$1$ ，数组就变成了 [**1,-1,-1**] ，然后 $1·（-1）·（-1）=1$ 。

现在询问最少需要花费多少的代价使得数组的乘积为 $1$ 。

## 说明/提示

$1\leq n\leq 10^5$

$-10^9\leq a_i\leq 10^9$

## 样例 #1

### 输入

```
2
-1 1
```

### 输出

```
2```

## 样例 #2

### 输入

```
4
0 0 0 0
```

### 输出

```
4```

## 样例 #3

### 输入

```
5
-5 -3 5 3 0
```

### 输出

```
13```

# 题解

## 作者：引领天下 (赞：8)

这个题实际上就是一个不是很裸的贪心

~~然而我比赛时还是WA了2次~~

这个首先要注意的是，要开long long；

至于思路，很明显，<0的我们全部改成-1，>0的全部改成1，0统计数量，最后把所有的±1乘起来，如果有0的话则是不用管是不是1的，因为可以通过修改一个0来达到把-1变成1；否则的话要把其中一个-1变为1，即再加上2的答案。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s=1,cntz;
long long ans,a[100005];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>a[i];
        if(a[i]<0)ans+=-1-a[i],a[i]=-1;//<0的变成-1
        else if(a[i]==0)ans++;//=0的肯定是要动1次的
        else ans+=a[i]-1,a[i]=1;//>0的改成1
    }
    for (int i=1;i<=n;i++)if(a[i])s*=a[i];else cntz++;//统计乘积和0的个数
    if(s==-1&&!cntz)ans+=2;//如果乘起来是-1，又没有可以动手脚的0，则要把其中一个-1改为1，再额外加上2
    cout<<ans;
}
```

---

## 作者：Awdrgysxc (赞：3)

## 【Analysis】
这题应该贪心和DP都能过；

可以发现，一个数只能变成$-1$或$1$,令$Dp_{i,j}$表示前i个数有j个变成了$-1$,发现转移和j的数量无关，只和奇偶性有关，令$Dp_{i,0}$表示前i个数用了偶数个$-1$,那么方程就是
```cpp
Dp[0][1] = 1e18;

Dp[i][0] = std::min(Dp[i - 1][0] + D[i][1], Dp[i - 1][1] + D[i][0]);
Dp[i][1] = std::min(Dp[i - 1][0] + D[i][0], Dp[i - 1][1] + D[i][1]);
```
总复杂度是$O(N)$
## 【Code】
```cpp
#include <cstdio>
#include <set>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
 
namespace IO
{
    inline char gc()
    {
        static char s[1<<20|1]={0},*p1=s,*p2=s;
        return (p1==p2)&&(p2=(p1=s)+fread(s,1,1<<20,stdin),p1==p2)?EOF:*(p1++);
    }
//	inline char gc() { return getchar(); }
	inline long long read()
	{
		long long ret=0;bool flag=0;char c=gc();
		while ((c<'0')|(c>'9')) flag ^= !(c^'-'),c=gc();
		while ((c>='0')&(c<='9')) ret=(ret<<1)+(ret<<3)+(c^'0'),c=gc();
		return flag?-ret:ret;
 	}
 	char OutputAns[1<<20|1],*OutputCur = OutputAns;
 	inline void output()
 	{
 		OutputCur -= fwrite(OutputAns,1,OutputCur - OutputAns,stdout);
	}
	inline void print(long long ans)
	{
		char s[20]={0};
		if (OutputCur - OutputAns + sprintf(s,"%I64d",ans) >> 20) output();
		OutputCur += sprintf(OutputCur,"%I64d",ans);
	}
	inline void printc(char c)
	{
		if (OutputCur - OutputAns + 1 >> 20) output();
		*(OutputCur++) = c;
	}
}
 
using IO::read;
using IO::print;
using IO::printc;
using IO::output;
 
const int M = 1e5 + 11;
 
long long A[M], Dp[M][2], D[M][2];
 
int n;
 
int main(void)
{
	n = read();
	for (int i = 1;i <= n; ++i)
		A[i] = read();
//	std::sort(A + 1, A + 1 + n);
	for (int i = 1;i <= n; ++i)
		D[i][0] = abs(A[i] + 1), D[i][1] = abs(A[i] - 1);
	Dp[0][1] = 1e18;
	for (int i = 1;i <= n; ++i)
	{
		Dp[i][0] = std::min(Dp[i - 1][0] + D[i][1], Dp[i - 1][1] + D[i][0]);
		Dp[i][1] = std::min(Dp[i - 1][0] + D[i][0], Dp[i - 1][1] + D[i][1]);
	} printf("%I64d\n", Dp[n][0]);
}
```

---

## 作者：Jayun (赞：2)

   _锅已补。。。_ 

感谢 @一个低调的人 （UID=48417）



# 题目：

![](https://img2018.cnblogs.com/blog/1748322/201908/1748322-20190821212036884-1005135280.png)

[CodeForces链接](http://codeforces.com/problemset/problem/1206/B)

[Luogu链接](https://www.luogu.org/problem/CF1206B)

# 思路：

~~这是一个一眼题~~

我们不妨把所有的数都看做是$1$（取相应的花费，如：$6$ 的花费就是$6 - 1 = 5$， 拿变量$ans$记录）。

如果这一个是负数，拿一个变量$negative$记录负数的数量。

对于负数，当有偶数个的时候，把他们都变成$-1$是无所谓的，因为偶数个$-1$相乘的最终答案是$1$,所以当有偶数个负数时答案为$ans - negative \times 2$（乘上$2$是因为$1$变成$-1$要两步）。

但当有奇数个的时候，我们肯定选$negative-1$个负数改成$-1$，不然最后乘积就是$-1$了。

所以最终答案是$ans - [(negative - negative ~ mod ~ 2) \times 2]$

嗯~我们**充满信心**地交到评测姬上评测：

![](https://s2.ax1x.com/2019/08/22/mafSI0.png)

嗯？？？？（我头像）

真是奇怪。为啥会WA？

在我百思不得其解时，dalao告诉我我错误原因——有$0$的情况。

当我们有奇数个负数，当有$0$时，把所有负数都可以变为$-1$！

因为$0$它变$1$还是变$-1$，都是花费$1$块钱。因此，有奇数个负数并且有$0$时，就**先把**$ans-2$再作偶数个负数的情况。

举个栗子（~~请大家自行手玩~~）：

> 0 5 -3 -6 -9

我们原来的答案是:
$$\begin{matrix}ans - [(negative - negative ~ mod ~ 2) \times  2]\\ =26-[(3-3~mod~2) \times 2]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\ =26-4~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\ =22~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\end{matrix}$$

但实际上应该是$20$（~~不知道为什么？拿草稿纸算算~~）


（请仔细阅读完再看代码）

# AC代码：


![](https://s2.ax1x.com/2019/08/22/maW7Pf.png)

---

## 作者：luguangxing (赞：1)

这是一道偏思维题想明白了就会做。

首先我们以样例为例：
```cpp
5

-5 -3 5 3 0
```
这组样例输出是 $13$ 我们先把 $-5$ 改为 $-1$ 代价是 $4$ 把 $-3$ 改为 $-1$ 代价是 $2$ 把 $5$ 改为 $1$ 代价是 $4$ 把$3$ 改为 $1$ 代价是 $2$ 最后把$0$ 改为 $1$ 代价是 $1$ 再来算一下 $4+2+4+2+1=13$ 根据这个样理解释我们知道了，需要把负数改为 $-1$，把 $0$ 改为 $1$，把正数也改为 $1$。

思路：我们写一个循环判断 $a_i$ 是哪类数，接着去做那个数对应的做法，累加代价。负数就例如 $-5$ 改成 $-1$ 代价是 $4$ 是 $|-5+1|$，$0$ 代价是 $1$，正数例如 $5$ 是  $5-1$。

来归顺一下 $-x$ 改成 $-1$ 是 $|x+1|$，$0$ 加 $1$ 代价为 $1$，$x$ 改成 $1$ 是 $|x-1|$。

这样就改完了，不过还有一步需要判断负数的数量是奇是偶。是奇数的话就还要再花费 $2$ 的代价去把他改为 $1$。

总结一下就是负数改 $-1$，零改 $1$，正数改成 $1$，好理清思路就可以开始打程序了。

代码展示：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	long long a[n+5],sum=0,ans=0,o=0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]<=-1)//这里要写小于等于避免类似第一组样例的情况
		{
			sum+=abs(a[i]+1);
			ans++;
		}
		else if(a[i]==0)
		sum++,o++;
		else if(a[i]>1)
		sum+=a[i]-1;
	}
	if(ans%2==1&&o==0)
	cout<<sum+2<<endl;
	else
	cout<<sum<<endl;
	return 0;
}
```

---

## 作者：fuwei123 (赞：1)

不难发现，我们可以把每一个数 $x$ 分开考虑，但最终都要把所有数变成 $1$ 或 $-1$ 中的一种。

- 若 $x<0$，则将 $x$ 变为 $-1$，花费代价 $\lvert x + 1 \lvert$。

- 若 $x=0$，则花费 $1$ 的代价，将 $x$ 变为 $1$ 或 $-1$，具体怎么变，得看负数的**个数**（这个后面会说到）。

- 若 $x>0$，将它变为 $1$ 显然代价最少，且最优。

最后，不要忘记，如果负数的个数是**奇数**，那么它们相乘就不是 $1$ 了。所以要么把**一个负数变成 $1$**，在此前的基础上花费 $2$ 的代价；或者把**一个 $0$ 变成 $-1$**，在此前基础上再花费 $1$ 的代价，但在之前答案的计算中，我们已经计算过一次将 $0$ 变成 $1$ 或 $-1$ 的代价，所以不需要再计算。

所以，综上所述，把所有答案累加起来，就是最终的操作数。


```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	ios::sync_with_stdio(0);
	int a = 0, b = 0, c = 0, ans = 0;//负数个数，0个数，正数的个数
	cin >> n;
	for(int i = 1;i <= n;i++){
		int x;
		cin >> x;
		if(x < 0){
			a++;
			ans += abs(x + 1);
		}
		else if(x == 0)b++, ans++;
		else c++, ans += x - 1; 
//		cout << a << " " << b << " " << c << "\n";
	}
	if(a % 2 == 1 && b == 0)ans += 2;
	cout << ans;
	return 0;
}
```

别着急，如果你将这份代码直接交上去，你会 WA。

为什么呢？

十年 OI 一场空，不开 long long 见祖宗。

一定要开 long long 啊！

恭喜你通过了此题！

---

## 作者：Konnyaku_ljc (赞：1)

由题意知，我们要让所有数的乘积为1，那么，所有的数应当为1或-1；  
那么，若n大于0，我们先把他变成1，ans加上n-1；而当一个数等于0时，它既可以变为1也可以变为-1，所以这时肯定成立，ans+1；而当一个小于0时，我们要计算有多少-1，因为只有偶数个-1才能成立  
当计算完后，若有0或偶数个-1，直接输出，否则，输出ans+2；

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
long long n,a,ans,sum;
bool ok;
int main()
{
	cin >> n ;
	for ( int i = 1 ; i <= n ; i ++ )
	{
		cin >> a ;
		if( a >= 1 ) ans += a - 1 ;
		if( a == 0 ) ans += 1 ,ok=true;
		if( a <= -1) ans += -1 - a,sum++;
	}
	if(ok) cout << ans;
	else 
	{
		if(sum % 2 == 0) cout << ans ;
		else cout << ans + 2;
	}
	return 0;
}
```

---

## 作者：Mubuky (赞：1)

# _**CF1206B Make Product Equal One 题解**_ 

![](https://api.gushi.ci/all.svg)

> 十年OI一场空，不开long long见祖宗

~~我就见了祖宗~~

不过做这道题的时候我是真的瞎，没看清数据范围，第一次交没开long long，扣了我的小分分。

**思路&解法：**

对于题目中的“乘积为1”的要求，因为我们知道满足“乘积为1”这一要求仅当所有数都为“1”或“-1”时才有可能满足。题目中求最小操作数，我们不妨贪心求解，分类讨论。

对于所有x：

一般的，

**若x >= 1**，则让它变为“1”，**操作数 += x - 1**；

**若x <= -1**，则让它变成“-1”，**操作数 += -1 - x**；

特殊的，

**若-1 < x < 1，即 x == 0**，它既可以变成“1”，又可以变成“-1”，且都有 **操作数 += 1**。

在按照上述操作执行时，我们同时**统计“0”和变成“-1”的数字个数**。

**首先判断是否有“0”出现**：因为“0”是“万能数”，它既可以变成“1”也可以变成“-1”，当乘积为“-1”是可以变成“-1”使乘积为“1”，所以说只要有“0”出现，就可以直接输出操作数。

**若上述判断为“否”，则继续判断“-1”的个数是否为偶数**：若为偶数，则乘积已经为“1”，符合题意，直接输出。若非偶数，则说明现在所有数的乘积为“-1”，不符合题意，我们这时可以把其中的一个“1”变成“-1”，或是把其中的一个“-1”变成“1”，都有 **操作数 += 2**。

**样例讲解：**

**样例#4：**
```cpp
//样例输入#4：
5
-5 -3 -4 3 0
```

按照上述所有操作，我们执行完第一步后应为：

```
//第一步：
-1 -1 -1 1 0(1/-1)
//统计个数
ans = 4+2+3+2+1 = 12;	//操作数（答案）
sum_1 = 3;		//-1的个数
sum0 = 1;		//0的个数
```
我们发现存在“0”，故输出12(ans)

**样例#5：**

```cpp
//样例输入#5：
5
-5 -3 -4 3 4
```

按照上述所有操作，我们执行完第一步后应为：

```
//第一步：
-1 -1 -1 1 1
//统计个数
ans = 4+2+3+2+3 = 14;	//操作数（答案）
sum_1 = 3;		//-1的个数
sum0 = 0;		//0的个数
```
我们发现没有“0”的存在且“-1”的个数为奇数，现在的乘积为“-1”，我们需要把其中的一个“1”变成“-1”或是把其中的一个“-1”变成“1”。

```
//第一步：
1 -1 -1 1 1
//统计个数
ans = 14+2 = 16;	//操作数（答案）
sum_1 = 4;		//-1的个数
```

输出16(ans)。

**比赛代码：**

```cpp
#include<cstdio>
int main()
{
	long long n;
	scanf("%lld",&n);
	long long t1=0,t_1=0,t0=0;
	long long ans=0;
	for(long long i=1;i<=n;i++){
		long long a;
		scanf("%lld",&a);
		if(a>1){
			ans+=a-1;
			t1++;
		}else if(a<-1){
			ans+=-1-a;
			t_1++;
		}else if(a==1){
			t1++;
		}else if(a==-1){
			t_1++;
		}else if(a==0){
			ans+=1;
			t0++;
		}
	}
	if(t_1%2==1){
		if(t0==0){
			ans+=2;
		}
	}
	printf("%lld",ans);
	return 0;
}
```

**优化代码：**

```cpp
#include<cstdio>
int main()
{
	int n;
	scanf("%d",&n);
	long long sum_1=0,sum0=0,ans=0;
	for(int i=1;i<=n;i++){
		long long x;
		scanf("%lld",&x);
		if(x>=1){
			ans+=x-1;
		}else if(x<=-1){
			ans+=-1-x;
			sum_1++;
		}else if(x==0){
			ans+=1;
			sum0++;
		}
	}
	if(sum0==0&&sum_1%2==1){
		ans+=2;
	}
	printf("%lld",ans);
	return 0;
}
```


 _**Name:** [Codeforces Round #580 (Div. 2)](https://codeforces.com/contest/1206)_ 

 _**Start:** Aug/18/2019 21:45UTC+8_ 

 _**Length** 02:10_ 

##  _**By Mubuky**_ 

---

## 作者：寒鸽儿 (赞：1)

如果一个数为负数，将它变为-1，为正数，变为1.  
我们在此过程中统计出-1的个数，若它为奇数：  
存在0,将1个0变为-1，其他的(若存在)变为1.  
不存在0，将一个-1变为1.
```cpp
#include <iostream>

using namespace std;

int main() {
	int n, zero = 0, ng = 0, t;
	long long cost = 0;
	cin >> n;
	while(n--) {
		cin >> t;
		if(t >= 1) {
			cost += t - 1;
		} else if(t <= -1) {
			ng^=1; cost += -1 - t;	
		} else {
			zero++;
		}
	}
	cost += zero;
	if(ng % 2 && !zero) cost += 2;
	cout << cost << endl;
	return 0;	
}
```

---

## 作者：dthythxth_Huge_Brain (赞：0)

## 题目分析

> 给你一个有 $n$ 个数的数组。你可以用 $x$ （ $x$ 为任意正整数）的代价将数组中的任意一个数增加或减少 $x$，你可以重复多次此操作。现在需要你用若干次操作使得 $a_{1}\times a_{2} \times ... \times a_{n} = 1$ （数组的乘积为 $1$ ）。

不难发现，当 $a_{1}\times a_{2} \times ... \times a_{n} = 1$ 时，这些数必然就是 $1$ 或者 $-1$，只要判断 $a_{i} $ 离 $1$ 和 $-1$ 距离的最小值，累加起来，就是答案。

但是，你会发现自己 $WA$ 了。

为什么呢？仔细想一想，$-1 \times -1 = 1$，但是 $-1 \times -1 \times -1 =-1$。也就是说，只有偶数个 $-1$ 相乘结果才会为 $1$。若 $a_{i}$ 离 $-1$ 更近，就先把它改成 $-1$，若最后有奇数个 $-1$，就把代价加 $2$，使其中一个 $-1$ 变成 $1$。

遗憾的是，这依然不是正确的答案。

若 $a_{i} = 0$，那么 $a_{i}$ 到 $1$ 和 $-1$ 所花的代价一样，此时若正好有奇数个 $-1$，那么我们可以将一个变成 $-1$ 的 $0$ 改成 $1$ 或者将一个变成 $1$ 的 $0$ 改成 $-1$，这样代价不变。所以我们再需要判断一下数组中是否有 $0$。这样做时间复杂度为 $O(n)$，就可以 $AC$ 啦。

## 参考题解

```
#include <iostream>
#include <vector>
#include <cmath>  //头文件
#define QwQ return 0
using namespace std;
int main() {
    int n;
    cin>>n;
    vector<int>a(n);
    int fushu=0;  //统计数组中负数的个数
    int zero=0;  //统计数组中零的个数
    long long daijia=0;  //代价
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(a[i]< 0) {
            fushu++;
            daijia+=abs(a[i] + 1);  //将负数变为-1需要的代价
        }
		else if(a[i]>0){
            daijia+= abs(a[i] - 1);  //将正数变为1需要的代价
        } else {
            zero++;
            daijia++;  //将零变为1需要的代价
        }
    }
    //如果数组中有偶数个负数，则不需要对任何数进行额外操作
    //如果数组中有奇数个负数，则需要对其中一个负数进行额外操作(将其变为 1)
    if (fushu%2!=0&&zero==0){
        daijia+=2;  //对一个负数进行额外操作需要2个代价
    }
    cout<<daijia<<endl;  //输出代价
	QwQ;  //完结撒花！！！
    return 0;
}

```


---

## 作者：Doubeecat (赞：0)

### 题目描述：

给你一个有 $n$ 个数字的数列，你有两种操作：将某个数 $+1$ 或 $-1$ 。求用最小的操作次数让这个数列的每一项乘起来等于 1

$n \leq 10^5$

### 解题思路：

~~用C换来的~~

分析一下，每个数字只有两种情况：变成 1 或者变成 -1 

所以每个数字的代价就是`min(abs(1 - a[i]),abs(-1 - a[i]))`

值得一提的几个~~大坑~~点是，最后可能会变成 -1 ，所以顺便记一下，如果最后变成 -1 了记得加上 2 。而且 0 也要记，最后要加上 0 的个数。

时间复杂度$O(n)$

### 代码：

```cpp
#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
#define int long long
inline int read() {
	char v = getchar();int x = 0,f = 1;
	while (!isdigit(v)) {if(v == '-')f = -1;v = getchar();}
	while (isdigit(v)) {x = x * 10 + v - 48;v = getchar();}
	return x * f;
}

const int N = 100010;

int pre[N],n,p1,p2,ans,z,res = 1;

signed main() {
	n = read();
	for (int i = 1;i <= n;++i) {
		pre[i] = read();
		if (pre[i] == 0) {
			z++;
		}
	}
	sort(pre+1,pre+1+n);
	for (int i = 1;i <= n;++i) {
		if (pre[i] <= -1) {
			ans += (-1 - pre[i]);
			res *= -1;
		}
		else if (pre[i] >= 1) {
			ans += (pre[i] - 1);
			res *= 1;
		}
	}
	if (res == -1) {
		if (z) {
			ans += z;
		}
		else {
			ans += 2;
		}
	}
	else {
		ans += z;
	}
	cout << ans;
	
	return 0;
}
```

---

## 作者：ZigZagKmp (赞：0)

本文同步于[CF1206总题解](https://www.luogu.org/blog/zhouzikai/cf1206round-580-div2-post)，欢迎各路神仙来踩。

## B Make Product Equal One
### 题意
给定一个序列$a$，你可以进行若干次操作，每一次操作可以将$a$中某一个数$+1$或者$-1$，求使这个序列的每个元素的乘积为$1$的最小操作次数。
### 解法
1. 贪心($O(n)$)

我们预处理出数组$b,c$，$b_i,c_i$分别表示$a_i$到1，$a_i$到-1的操作次数。枚举每一个数，选择$b_i,c_i$中较小的累加到答案中。

同时我们要统计选取$c_i$的次数，因为这个次数如果是奇数，则乘积为-1，不符合题意。在这种情况下，我们无论是将某一个$b_i$换成$c_i$，还是将某一个$c_i$换成$b_i$，最后选取$c_i$的次数一定是一个偶数，即符合题意的。

因此我们可以维护一个数组$h$，在数组$h$添加所有的$|b_i-c_i|$，这个过程相当于给一个**替换**的机会。因为我们只需要替换最多1次，所以直接取最小值即可。这个可以$O(n)$或者$O(n\logn)$排序实现。

2. 分析性质($O(n)$)

我们把所有整数分为3类：$(-\infty,-1]$,$\{0\}$,$[1,+\infty)$，不难发现第一类数到$-1$的距离比到$1$的距离少`2`，第二类数到$-1$的距离和到$1$的距离相等，第三类数到$-1$的距离比到$1$的距离多`2`。

因此在最优情况下应该尽可能让第一类数变成$-1$，第三类数变成$1$，此时如果有第二类数，那么不管它的乘积是1还是-1，都可以通过改变第二类数的取值，**在不影响总操作次数的情况下**实现乘积为1。（如果乘积为1，将所有的第二类数变成1即可，如果乘积为-1，将奇数个第二类数变成-1，其余的变成1即可）

如果没有第二类数，如果乘积为1，那可以直接作为答案，否则我们要将其中一个第一类数变成1或者将其中一个第三类数变成-1，总操作次数加2。

这种解法其实相当于实现了简化版的**替代**，时间复杂度$O(n)$
### 代码实现
1. 解法1

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define maxm 200005
#define int long long
#define inf 0x3f3f3f3f
#define mod 1000000007
#define local
template<typename Tp>
void read(Tp &x){
	x=0;int f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-'){f=-1;}c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	x*=f;
}
int n,m;
int a[maxn];
int b[maxn];
int c[maxn];
int h[maxn],tot,sum,cnt;
signed main(){
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++){
		b[i]=abs(1-a[i]);
		c[i]=abs(-1-a[i]); 
	}
	for(int i=1;i<=n;i++){
		if(b[i]<=c[i]){
			sum+=b[i];
			h[++tot]=c[i]-b[i];
		} 
		else {
			sum+=c[i];
			cnt++;
			h[++tot]=b[i]-c[i];
		}
	}
	sort(h+1,h+tot+1);//其实可以O(n)找最小值
	if(cnt&1)sum+=h[1];
	cout<<sum<<endl;
	return 0;
}
```
2. 解法2

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	long long int n,i,cost=0,pos=1,count0=0;
	cin>>n;
	long long int a[n];
	for(i=0;i<n;i++){
		cin>>a[i];
	}
	for(i=0;i<n;i++){
		if(a[i]<0){
			cost+=abs(a[i]+1);
			pos*=-1;
		}
		else if(a[i]>0){
			cost+=a[i]-1;
		}
		else {
			count0++;
			cost++;
		}
	}
	if(pos==-1&&count0==0){
		cost+=2;
		cout<<cost;
	}
	else cout<<cost;
	return 0;
}
```


---

## 作者：周子衡 (赞：0)

思路：贪心

显然我们需要先把所有数的**绝对值**变成$1$。那么对于负数先变为$-1$，正数变为$1$。

如果有$0$，那么就好办了，$0$可以轻松变为$1$或$-1$，符号就调好了，直接输出。

如果没有$0$，那么统计一下负数个数，偶数即可直接输出，奇数则要把一个$-1$变成$1$，额外加$2$。

代码：

```cpp
#include<cstdio>

using namespace std;

long long a[100010];

int main()
{
	int n=0;scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
	
	bool zero=false;
	for(int i=1;i<=n;i++)if(!a[i])zero=true;
	
	if(zero)
	{
		long long ans=0;
		for(int i=1;i<=n;i++)
		{
			if(!a[i])ans+=1;
			else if(a[i]>0)ans+=a[i]-1;
			else ans+=-1-a[i];
		}
		printf("%I64d",ans);
	}
	else
	{
		long long ans=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]>0)ans+=a[i]-1;
			else ans+=-1-a[i];
		}
		int cnt=0;for(int i=1;i<=n;i++)if(a[i]<0)cnt++;
		if(cnt&1)ans+=2;
		printf("%I64d",ans);
	}
	return 0;
}
```

---

## 作者：xuezhe (赞：0)

首先，可以得到这个结论：一个符合条件的序列中的数字仅可能是 $1$ 和 $-1$。

然后，想到这样一个贪心策略：先让所有正数减少到 $1$，让所有负数增加到 $-1$，暂且不考虑 $0$，然后按情况调整。此时序列中仅有可能有三种数字：$-1,0,1$。

此时若序列中 $-1$ 的数量为奇数，在不考虑 $0$ 的情况下，序列中的积必然为 $-1$。所以我们需要让序列中 $-1$ 的数量增加 $1$ 或减少 $1$。

此时，我们优先考虑将序列中的其中一个 $0$ 变成 $-1$，代价为 $1$。若序列中没有 $0$，则无论将其中一个 $-1$ 变成 $1$ ，还是将其中一个 $1$ 变成 $-1$，代价皆为 $2$。

若在不考虑 $0$ 的情况下，序列中所有数的积为 $1$，则无需进行特殊操作。

最后，我们将序列中所有的 $0$ 变为 $1$ 即可。

以上是模拟过程，代码实现时，仅需将其替换成记录 $0$ 和 $-1$ 出现的次数，然后按上面的思路进行处理即可。

问题得解。

C++代码：
```cpp
#include <cstdio>
using namespace std;
void readInt(int &x){
	char c;
	int f=1;
	while((c=getchar())<'0' || c>'9'){
		if(c=='-'){
			f=-1;
		}
	}
	x=(c^48);
	while('0'<=(c=getchar()) && c<='9'){
		x=x*10+(c^48);
	}
	x*=f;
	return;
}
void prtLL(long long x){
	long long e;
	for(e=1;e*10<=x;e*=10);
	for(;e;e/=10){
		putchar(x/e%10|48);
	}
	puts("");
	return;
}
int main(){
	long long ans=0LL;
	int n,x,cnt0=0,cnt1=0,i;
	readInt(n);
	for(i=0;i<n;++i){
		readInt(x);
		if(x==0){
			++cnt0;
		}else{
			if(x>1){
				ans+=x-1;
			}else{
				if(x<=-1){
					ans+=-x-1;
					++cnt1;
				}
			}
		}
	}
	if(cnt1&1){
		if(cnt0){
			ans+=cnt0;
		}else{
			ans+=2;
		}
	}else{
		ans+=cnt0;
	}
	prtLL(ans);
	return 0;
}
```

---

## 作者：FP·荷兰猪 (赞：0)

> 题意：给你n个数，每次操作可以把其中一个数加上1或减去1，求最少的操作次数使得这n个数之积为1。

我们考虑贪心。

由于1只能分解为1$\times$1或者偶数个-1相乘。操作次数又要最小化，所以我们考虑把所有正数转化为1，所有负数转化为-1。O（n）扫过一遍后，如果负数个数为偶数，直接输出代价，否则输出代价+2。特别的，如果数组中有0，直接输出代价即可。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for (ll i=x;i<=y;i++)
#define per(i,x,y) for (ll i=x;i>=y;i--)
typedef long long ll;
ll max(ll x,ll y)
{
	if (x>y)
	{
		return x;
	}
	else
	{
		return y;
	}
}
 
ll min(ll x,ll y)
{
	if (x<y)
	{
		return x;
	}
	else
	{
		return y;
	}
}
int pos,neg;
int main()
{
	int n;
	cin>>n;
	int a[n+1];
	ll ans;
	ans=0;
	bool f;
	f=false;
	rep(i,1,n)
	{
		cin>>a[i];
		if (a[i]==0)//特判数组中是否有0
		{
			f=true;
		}
		if (fabs(a[i]-1)<fabs(a[i]+1))
		{
			ans+=fabs(a[i]-1);//ans存放当前最小代价
			pos++;
		}
		else
		{
			ans+=fabs(a[i]+1);
			neg++;
		}
	}
	if (f==true)
	{
		cout<<ans<<endl;
		return 0;
	}
	if (neg%2==0)
	{
		cout<<ans<<endl;
	}
	else
	{
		cout<<ans+2<<endl;
	}
	return 0;
}
```

---

## 作者：览遍千秋 (赞：0)

本题解同步发布于[本场$\mathrm{CF}$总题解](https://www.luogu.org/blog/kaiming/CF580DIV2)，欢迎来踩

---

## B - Make Product Equal One

要让$n$个数乘积为$1$，必须保证这个数列中只有$1$或者$-1$，且$-1$的个数为偶数个。

考虑贪心，设$b_i$代表$a_i$变为$1$的代价，$c_i$代表$a_i$变为$-1$的代价，优先选择小的一个，同时记录$record_i=abs(b_i-c_i)$，如果选择的是$-1$，令计数器$cnt++$

如果$cnt$为偶数，则直接输出答案

否则需要且仅需要将一个$-1$改为$1$或将一个$1$改为$-1$。

对$record$升序排序，答案加上$record_1$即可。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
int n,m;
int a[maxn];
int b[maxn];
int c[maxn];
int record[maxn],ans,cnt;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[i]=abs(1-a[i]);
		c[i]=abs(-1-a[i]);
		if(b[i]<=c[i]){
			ans+=b[i];
			record[i]=c[i]-b[i];
		} 
		else{
			ans+=c[i];cnt++;
			record[i]=b[i]-c[i];
		}
	}
	sort(record+1,record+n+1);
	if(cnt%2==1) ans+=record[1];
	cout<<ans<<endl;
	return 0;
}
```

---

