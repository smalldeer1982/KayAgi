# Roman and Numbers

## 题目描述

Roman is a young mathematician, very famous in Uzhland. Unfortunately, Sereja doesn't think so. To make Sereja change his mind, Roman is ready to solve any mathematical problem. After some thought, Sereja asked Roma to find, how many numbers are close to number $ n $ , modulo $ m $ .

Number $ x $ is considered close to number $ n $ modulo $ m $ , if:

- it can be obtained by rearranging the digits of number $ n $ ,
- it doesn't have any leading zeroes,
- the remainder after dividing number $ x $ by $ m $ equals 0.

Roman is a good mathematician, but the number of such numbers is too huge for him. So he asks you to help him.

## 说明/提示

In the first sample the required numbers are: 104, 140, 410.

In the second sample the required number is 232.

## 样例 #1

### 输入

```
104 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
223 4
```

### 输出

```
1
```

## 样例 #3

### 输入

```
7067678 8
```

### 输出

```
47
```

# 题解

## 作者：枫林晚 (赞：17)

### 题意：
将n(n<=10^18)的各位数字重新排列（不允许有前导零） 求 可以构造几个mod m等于0的数字 

### 分析：

状态压缩

#### 状态：

设f[s][k]表示对于选择数字组合的s来说，%m等于k的排列数量。

第一维大小：2^18
第二维大小：100

#### 阶段：

对于s的选择的枚举。s直接从1枚举到1<<（cnt+1） 这样到了s（n）时，所有能转移到s(n)的状态都已经处理完毕。不会有后效性。

由于对于1~n的所有排列，可以考虑是从中选择任意的n-1个数的所有排列，再在最末尾选上剩余的一个数。
所以之后的s(n)所能转移到的最优解，都是与s(n)有关系的（都是通过在s(n)末尾接上一个数转移的），所以满足最优子结构性质。

#### 转移：

对于给定的s，它的18位二进制表示中的每一位是0或者是1表示这一位上的数选择或者不选择。
我们将i从0循环到cnt，（cnt=n的位数-1）想要枚举的是s的每一位1，即枚举出来这个s所选的所有的数的位置，也就知道了所选择的数。

再枚举一下余数j，这样，可以写出这样的状态转移方程：

f[s][(j x 10+w[i])%m]+=f[s^(1<<i)][j]

意义是：每一位的选择都是通过这一位不选择的剩下状态，再把这一位放在末尾组成状态s转移的。

设之前的数为X,X=km+j;

选择了w[i]之后，X=10km+10j+w[i];
余数就变成了:(10j+w[i])%m

#### 然而有一个缺陷。。。

在于对于有重复数字时，会将一个状态转移从“其实是同一个组合”转移多遍，

举例：n=221
111会从101 转移一次，还会从011转移一次。然而这两个组合其实都是2、1,所以会算重。

所以可以在最后的时候进行多重集合的处理。
也可以每次枚举的时候，判断这一位的值是否之前已经处理过了。

if(vis[w[i]]) continue；

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
const int maxs=(1<<18)+5;
const int maxn=110;
using namespace std;
int cnt=-1,w[20],m;
ll f[maxs][maxn],n;
bool vis[10];
int main()
{
	for(cin>>n>>m;n;n/=10)
	 w[++cnt]=n%10;
	f[0][0]=1;
	for(int s=1;s<1<<cnt+1;s++)
	{ memset(vis,0,sizeof vis);//注意清空
	  for(int i=0;i<=cnt;i++)
	  {
		if(s==(1<<i)&&!w[i]) break;//去掉前导零
		if(!(s&(1<<i))||vis[w[i]]) continue;//判断是否选择了这一位，并且跳过已经处理过删去w[i]之后转移的情况。
		vis[w[i]]=1;//标记处理过这个数了。
		for(int j=0;j<m;j++)
		 f[s][(j*10+w[i])%m]=(f[s][(j*10+w[i])%m]+f[s^(1<<i)][j]);	
	  }		
	}
	cout<<f[(1<<cnt+1)-1][0];//f[11..1][0]
	return 0;
}
```



---

## 作者：tongyf (赞：13)

[题面](https://www.luogu.com.cn/problem/CF401D)

数的个数一共就$18$个，而且模数也很小，那么考虑状压$DP$

状态设计：

$i$ 每个数选或者不选构成的集合，状压肯定要有这个东西

$j$ 对$m$取模的值为$j$的方案数，这么设计是因为选好所有的数之后再判断是否整除比较麻烦，可以通过余数为$0$来判断整除

$0/1$当前是否已经选了非$0$的数，$0$表示没有选，$1$表示选了。不妨选数是从高位向低位选，那么某个时候选$0$的前提是之前已经选过非$0$的数（似乎题解里没有像我这么处理前导$0$的）

$f(i,j,0/1)$表示方案数

经过计算，本题的空间限制刚好允许这样的状态设计

设$a(k)$表示原数第$k$位的数

根据选数的时候从高位到低位选数的方式，可以得到如下转移方程：

当$a(k)$非零时，$f(i\ or\ 2^k,(j*10+a(k))\ mod\ m,1)=\sum f(i,j,0/1)$

当$a(k)=0$时，$f(i\ or\ 2^k,(j*10+a(k))\ mod\ m,1)=\sum f(i,j,1)$

但是注意，对于原数中多次出现的数，有可能重复转移，那么不妨用$vis$数组记录某个数是否用过，枚举新的状态是清空$vis$

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,f[(1<<18)+10][105][2],a[20],cnt;
bool vis[10];
signed main(){
	cin>>n>>m;
	f[0][0][0]=1;
	while(n){
		a[cnt++]=n%10;
		n/=10;
	}
	for(int i=0;i<(1<<cnt);i++){
		memset(vis,0,sizeof(vis));
		for(int j=0;j<cnt;j++){
			if(i&(1<<j)||vis[a[j]]) continue;
			vis[a[j]]=1;
			for(int k=0;k<m;k++){
				if(a[j]){
					f[i|(1<<j)][(k*10+a[j])%m][1]+=f[i][k][0];
					f[i|(1<<j)][(k*10+a[j])%m][1]+=f[i][k][1];
				}
				else{
					f[i|(1<<j)][(k*10+a[j])%m][1]+=f[i][k][1];
				}
			}
		}
	}
	cout<<f[(1<<cnt)-1][0][1]<<endl;
	return 0;
}
```

---

## 作者：LawrenceSivan (赞：9)

# CF401D Roman and Numbers

> 将 $n,n\le 10^{18}$ 的各位数字重新排列（不允许有前导零） 求 可以构造几个 $\bmod\  m$ 等于 $0$ 的数字 $(m\le 100)$

变进制状压。

为啥没人写变进制状压啊，~~比二进制状压高到不知道到哪里去了。~~

截至 2021.10.29 是 lg 最优解。

---

发现要重新排列 $n$ ，于是肯定和 $n$ 的位数有关。

$n\le10^{18}$ ，可以考虑状压。

先说一下比较常见的二进制状压。

设 $f_{S,i}$ 表示 使用了 $S$ 这个状态中的数字，并且 $\bmod \ m$ 等于 $i$ 的方案数。

每次枚举一个数字填在已经填好的数字后面进行转移。

`f[S|(1<<(i-1))][(j*10+a[i])%m]+=f[S][j];`

对于前导零，只需要在放入第一个数字的时候特判一下是不是 $0$  即可。

考虑到相同数字的排列顺序并不重要，需要去重。

去重也很简单，直接除以所有数字的出现次数的阶乘就好了。

或者标记一下使用过的数字。

[二进制状压代码](https://gitee.com/lawrencesivan/code-clipboard/blob/master/CF401D%20Roman%20and%20Numbers%EF%BC%88%E4%BA%8C%E8%BF%9B%E5%88%B6%E7%8A%B6%E5%8E%8B%EF%BC%89)

设 $N=\log_{10}n$ 

复杂度为 $\mathcal{O(2^NNm)}$ 。

---

发现上面的状态量很大的。

考虑另外一种状态定义，从每个数字出现次数入手。

对于每一种数字，他在 $n$ 中出现的最多次数可能是 $18$ 次。

那么状态量就是 $19^1=19$  。

考虑极端情况，十种数字出现次数相同。

每个数字出现 $\dfrac{9}{5}$ 次（近似认为是 $2$ 次）。

状态量是 $3^{10}$ （每种数字有三种情况，$0$：一次都不出现，$1$:出现一次：$2$:出现两次）

远远小于刚才的 $2^N$ 。

按照上面的状态定义设计转移：

设 $f_{S,i}$ 表示已经填进去的数字的**次数**的状态为 $S$，并且填出来的数字 $\bmod \ m$ 等于 $i$  的方案数。

之后你会发现每个数字出现次数可能不一样，那么我们不能使用二进制进行状压。

考虑变进制数，以每一种数字的**可以选择的出现次数**作为进制

不熟悉可以去做做[康托展开模板题](https://www.luogu.com.cn/problem/P5367)和[火星人](https://www.luogu.com.cn/problem/P1088)。

先来看看熟悉的进制。

十进制数：$x=x_0×10^0+x_1×10^1+x_2×10^2+x_3×10^3+…$

二进制数：$x=x_0×2^0+x_1×2^1+x_2×2^2+x_3×2^3+…$

他们都可以表示为一个多项式。

每一个变量前面的系数和进制有关（可以发现，定进制数的进制就是系数的底数）。

每一个变量的去取值范围都是 $[0,进制-1]$ ，多余则进位。

一般的，我们可以类似地定义 $m$ 进制数。 

> $m$ 进制数：$x=x_0×m^0+x_1×m^1+x_2×m^2+x_3×m^3+…$

变进制数就是每一位进制不一样。

我们可以向下面这样定义变进制数：

其中每一位的进制是 $p_i$。

> $x=x_0+x_1p_0+x_2p_0p_1+x_3p_0p_1p_2+...$

其中每一位的范围依然是 $[0,进制-1]$ ，即 $[0,p_i-1]$。

发现系数 $k_i$ 就是 $k_i=\prod\limits^{i-1}_{j=0}p_j$。

于是你发现你做到了变进制数与 $10$ 进制数的转化。

$x=x_0+x_1k_1+x_2k_2+x_3k_3+...$

其实和二进制状压差的不怎么多，就是进制不太一样了，该怎么状压还怎么状压。

如何取出变进制的第 $i$ 位？

想想 $10$ 进制。

比如 $10202$ 取出第三位咋取？

是不是可以 `(10202/100)%10` ？

写成变进制形式是什么？

`x/p[i-1]%(a[i]+1)`

但是这样是有问题的。

要是让你取出第 $0$ 位呢？

会出现负下标。

我们用一种等价形式来代替：

`x%p[i+1]/p[i]`

可以用十进制帮助理解：

$10202 \rightarrow 202 \rightarrow 2$。

并且可以很方便的判断前导零，同样是填入第一个数字的时候去掉。

极限状态下复杂度 $\mathcal{O(3^{10}\times10m)}$

代码：

```cpp
read(n,m);
while(n){
    a[n%10]++;
    n/=10;
}

frac[0]=1;
for(int i=1;i<=10;i++){//按照上面说的记录一下每一位的系数    
    frac[i]=frac[i-1]*(a[i-1]+1);
}

f[0][0]=1;

for(int S=0;S<frac[10]-1;S++){//就像是你二进制状压写的是 1<<n 一样，，是全 1 状态
    for(int i=(S==0);i<10;i++){//在填入第一个数字的时候去除前导零，枚举选择哪一种数字
        if(S%frac[i+1]/frac[i]<a[i]){//填入数量限制
            for(int j=0;j<m;j++){//枚举余数
                f[S+frac[i]][(j*10+i)%m]+=f[S][j];
            }
        }
    }
}

write(f[frac[10]-1][0]),puts("");
```



---

## 作者：MeowScore (赞：7)

一道综合状压 dp 和数位 dp 的题目。

我们在转移的时候需要关注已经取用了哪些数字，这样才能判断哪些数是当前可选的。数据范围是 $10^{18}$，数字个数很少，我们可以考虑状压（把 $n$ 拆解后对每个数字编号，然后对编号状压）。如何判断填完之后是否有解？我们还要考虑当前拼出来的数字取模之后的余数，也设到状态里。于是我们设 $f_{s,p}$ 表示当前选取的数字集合为 $s$，当前拼起来得到的数字模 $m$ 意义下等于 $p$ 的方案数。我写的是记忆化搜索，对于一个状态，枚举所有数字，没有被选入当前集合的数字就尝试填到下一位，注意不能有前导零，这个需要特判。

但是写完发现样例都过不了，原因是同种数字内部的顺序是无所谓的，但是我们却计算了多次，解决方案是算完之后除以每种数字的全排列数（也就是个数的阶乘）。

然而超时了，因为先算完再除掉是低效的，怎么做到直接不多算呢？搜索的时候我们规定：如果这一位填入了数字 $i$，这个 $i$ 必须是当前可用的数字 $i$ 中编号最小的那个。于是重复计算的问题解决了。

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll f[1<<18][110];
int tot,a[30];
ll mi[30];
ll n;
int m;
ll dfs(int x,int s,int p){//s:选数的集合; p:当前余数 
	if(!x){
		if(!p)
			return 1;
		return 0;
	}
	if(f[s][p]!=-1)
		return f[s][p];
	ll ans=0;
	int b[10]={0};
	for(int i=0;i<tot;i++){
		if((s>>i)&1)
			continue;
		if(a[i+1]==0&&x==tot)
			continue;
		if(b[a[i+1]])//这个数字不是第一次出现了,不能填 
			continue;
		b[a[i+1]]=1;
		ans+=dfs(x-1,(s|(1<<i)),(p+mi[x-1]*a[i+1])%m);
	}
	f[s][p]=ans;
	return ans;
}
ll solve(ll x){
	while(x){
		tot++;
		a[tot]=x%10;
		x/=10;
	}
	memset(f,-1,sizeof(f));
	ll ans=dfs(tot,0,0);
	return ans;
}
signed main(){
	cin>>n>>m;
	mi[0]=1;
	for(int i=1;i<=18;i++)
		mi[i]=mi[i-1]*10;
	cout<<solve(n);
	return 0;
} 
```

---

## 作者：柏木由纪AKB48 (赞：7)

P4163 [SCOI2007]排列 的升级版，这道题出题者的本意应该是让状压dp的,但是大多数人都用搜索水过了

不同于其他题解里的dp方式，我的dp方式是在前面加数字，数组和楼下的一样

f[ i ][ j ] 其中i表示状态：用a（十进制）下的对应位构造出的mod b == j 的数字有多少 

对于看不懂楼下代码的同学们解释一波：

楼下的状态转移：如38996923 在后面加上3

他现将38996923*10---> 389969230 膜上模数后加上3再膜模数

这种方法思路固然好，但是去除前导零的话就有点复杂

我的方法不同，在这个方程中也要算上所有前导零的情况，只有在最后在祛除一次，例如：

008676876 这在我的方程里面也是一种合法情况，应为我将在前面加上一个状态里面选择的数 比如3，则此数变成 3008676876

状态转移方程：f[i][(sd[t-1]*w[j+1]+u)%b]+=f[i^(1<<j)][u];

其中:

j是状态里所选择的加在数字前面的数

t表示这个数字（新构成的数字）一共有几位

sd[i]表示i所对应的十进制位在mod 模数的情况下需要乘的数(其实就是10^i%mod)

u是转移时循环的模数

上代码，语言表述能力不佳，有疑问欢迎私信，我一定尽全力解答

```cpp
#include<cstdio>
#include<string.h>
long long a,b,sd[20],w[20],cnt,f[262146][102],p;
bool vis[20];
int main(){
    sd[0]=1;for(int i=1;i<=18;i++) sd[i]=sd[i-1]*10;
    scanf("%lld%lld",&a,&b);
    for(int i=1;i<=18;i++) sd[i]=sd[i]%b;
    long long t=a;f[0][0]=1;
    while(t){w[++cnt]=t%10;t/=10;}
    for(int i=1;i<(1<<cnt);i++){
    	memset(vis,false,sizeof(vis));int t=0;
        for(int j=0;j<cnt;j++) if(i&(1<<j)) t++;
        for(int j=0;j<cnt;j++){
        	if(!(i&(1<<j))||vis[w[j+1]]) continue;
        	vis[w[j+1]]=true;
        	for(int u=0;u<b;u++) f[i][(sd[t-1]*w[j+1]+u)%b]+=f[i^(1<<j)][u];
        } 
    }
    for(int j=1;j<=cnt;j++) if(w[j]==0){p=j;break;}
    if(p!=0) f[(1<<cnt)-1][0]-=f[((1<<cnt)-1)^(1<<(p-1))][0];
    printf("%lld\n",f[(1<<cnt)-1][0]);
    return 0;
}
```

---

## 作者：George1123 (赞：5)

# 题解-Roman and Numbers

[$\Huge\color{#7788cc}{\texttt{In Cnblogs}}$](https://www.cnblogs.com/Wendigo/p/12581251.html)

---

**前置知识：**

> **数位 $\texttt{dp}$ [</>](https://www.cnblogs.com/Wendigo/p/12523331.html)**

---
> [$\color{#9933cc}{\texttt{Roman and Numbers}}$](https://www.luogu.com.cn/problem/CF401D)

> 给定 $n$ 和 $m$，求将 $n$ 的各位数字重新排列（不允许有前导 $0$），求可以构造几个能被 $m$ 整除。

> 数据范围：$1\le n\le 10^{18}$，$1\le m\le 100$。

---
用数位 $\texttt{dp}$ 代码又短时间又优又好理解，为什么没人玩呢？

---
把 $n$ 的各位数字拿出来排序一下，然后把每个数有没有用过状压。
```cpp
for(;n;n/=10) d.pb(n%10);
sort(d.begin(),d.end()),len=d.size();
```
**选数字的时候只允许用相同数字中第一个没用过的。**

---

**$\texttt{Dfs}$ 中：**

1. $w$：要找从右往左第几位。
2. $st$：当前数字使用状态。
3. $sum$：左 $len-w$ 位数字形成的数 $\bmod m$ 的余数。 

```cpp
il lng Dfs(re int w,re int st,re int sum){
	if(!w) return sum==0;//判断被 m 整除
	if(~f[st][sum]) return f[st][sum];
	re lng res=0;
	for(re int i=0;i<len;i++)
		if(!((1<<i)&st)&&(i==0||d[i]!=d[i-1]||((1<<(i-1))&st))) //*
			res+=Dfs(w-1,st|(1<<i),(sum*10+d[i])%m);
	return f[st][sum]=res; //记忆化，记录答案
}
```

**其中 $*$ 处的判断：**

1. 该数字未用过。
2. 该数字前的相同数字都用过。

以保证使用顺序，防止重复统计。

**关于 $f$ 记忆化数组：**

现在是 $f_{st,sum}$，本来应该是 $f_{w,st,sum}$。这里就讲讲 $f_{w,st,sum}$ 记忆化的缺点：

1. $1\le w\le 18$，$1\le st\le 2^{18}$，$1\le sum<m\le 100$，必然 $\color{#117}{\texttt{MLE}}$。
2. $st$ 中 $1$ 的数量 $cnt$ 必然满足 $cnt=len-w$，所以只记录 $st$ 不会重合答案。

---

**时间复杂度 $\Theta(2^{len}m)$。**

---

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

//&Start
#define re register
#define il inline
#define mk make_pair
#define pb push_back
#define db double
#define lng long long
#define fi first
#define se second
#define inf 0x3f3f3f3f

//&Data
const int W=18,M=100;
int m,len;
lng n,f[1<<W|7][M|7];
vector<int> d;

//&Digitdp
il void Pre(){memset(f,-1,sizeof f);}
il lng Dfs(re int w,re int st,re int sum){
	if(!w) return sum==0;
	if(~f[st][sum]) return f[st][sum];
	re lng res=0;
	for(re int i=0;i<len;i++)
		if(!((1<<i)&st)&&(i==0||d[i]!=d[i-1]||((1<<(i-1))&st)))
			res+=Dfs(w-1,st|(1<<i),(sum*10+d[i])%m);
	return f[st][sum]=res;
}
il lng DP(){
	for(;n;n/=10) d.pb(n%10);
	sort(d.begin(),d.end()),len=d.size();
	re lng res=0;
	for(re int i=0;i<len;i++)
		if(d[i]&&(i==0||d[i]!=d[i-1])) // 这里也要判断！这是最容易错的地方
			res+=Dfs(len-1,1<<i,d[i]%m);
	return res;
}

//&Main
int main(){
	scanf("%lld%d",&n,&m),Pre();
	printf("%lld\n",DP());
	return 0;
}
```
---

**祝大家学习愉快！**


---

## 作者：Jsxts_ (赞：3)

一种比较特别的数位 DP。

因为 $n$ 只有 $19$ 位，所以我们考虑用一个二进制的状态表示每一位数字有没有出现过。我们拆出 $n$ 的每一位后，要进行排序，否则不方便后面的去重。

设 $f_{i,j}$ 表示当前状态为 $i$，状态 $i$ 组成的数模 $m$ 余 $j$ 的方案数。显然，$f_{0,0}=1$。

对于每一位，我们枚举 $n$ 的每一位数字来填这一位。因为有重复的，所以要看这个数字有没有在状态里出现，即 $a_i\ne a_{i-1}$ 或 $a_{i-1}$ 没有出现。$f$ 数组可以用来记忆化。

注意：本题的数位 DP 枚举的是状态，所以没有最高位的限制（就是选数范围的限制），并且第一位要非 0，所以要单独一个循环。

代码（数位 DP 跑得挺快）：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll s = 0,f = 1;char ch = getchar();
	while (!isdigit(ch)) f = ch == '-' ? -1 : 1, ch = getchar();
	while (isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
	return s*f;
}
ll f[(1<<18)+5][105];
int a[20],m,cnt;
ll dfs(int x,int s,int st) {
	if (!x) return s == 0;//边界 
	if (f[st][s] >= 0) return f[st][s];
	ll ans = 0;
	for (int i = 0;i < cnt;i ++ ) {
		if (st & (1 << i)) continue;
		if (!i || a[i] != a[i-1] || (st & (1<<i-1)))//上面提到的限制 
			ans += dfs(x-1,(s*10+a[i])%m,st|(1<<i));
	}
	return f[st][s] = ans;
}
ll sol(ll x) {
	cnt = 0;
	while (x) a[cnt++] = x % 10, x /= 10;
	sort(a,a+cnt);//排序去重 
	memset(f,-1,sizeof f);
	ll res = 0,t = 0;
	while (!a[t]) t ++;//首位非0 
	for (int i = t;i < cnt;i ++ ) 
		if (a[i] != a[i-1]) res += dfs(cnt-1,a[i]%m,1 << i);
	return res;
}
int main() {
	ll n = read();
	m = read();
	printf("%lld",sol(n));
	return 0;
}
```


---

## 作者：NBest (赞：1)

[原题链接](https://www.luogu.com.cn/problem/CF401D)
# 思路
看到这个数据和范围，果断数位 dp。

因为同一个数字交换顺序是一样的，所以我们直接把它们合并即可。

设计状态，观察到每个数字的个数不一定相同，今天集训的时候学到了一个小技巧，

对于一个哈密顿回路（每个点恰好经过一次），我们可以用二进制表示其状态。

那对于一个广义哈密顿回路（好像没有这个概念，我自己编的），每个点恰好经过 $a_i$ 次。

通常来说，状压是指的二进制状压，因为二进制状压可以方便进行 `and`,`or`,`xor` 等位运算。但是也会有像本题这样非二进制的情况，有些甚至要爆搜出所有情况进行 dp。

但是其实是和二进制同样的状态压缩方式，只是把每个位进位的阈值改了，参考了一下上面巨佬的题解，就叫它变进制数吧。

对于一个二进制数 $x$，我们可以将它表示为：

$x=x_0\times 2^0+x_1\times 2^1+...+x_n\times 2^{n-1}$。

那么设 $n$ 中各个数字出现的次数分别为 $A[i]$，那么可以把第 $i$ 为看为一个 $A[i]+1$ 进制数。

那么我们可以将状态压缩为 $s$，则：

$s=x_0\times 1+x_1\times (A[0]+1)+x_2\times (A[0]+1)\times(A[1]+1)+...$。

然后就可以状态压缩加数位 dp 了。
## $Code1$
```cpp
int A[10],m,p[12];
ll n,f[100][60004];
ll dfs(int zt,int mv){
    if(!zt)return !mv;//没数了就返回
    if(~f[mv][zt])return f[mv][zt];
    ll ans=0;
    for(int i=9;~i;--i){//从大到小枚举数
        if(zt==p[10]-1&&!i)continue;//首位不能为0
        if(zt%p[i+1]<p[i])continue;//去掉前面的位判断是否还有数
        ans+=dfs(zt-p[i],(mv*10+i)%m);//转移
    }
    return f[mv][zt]=ans;
}
int main(){
    cin>>n>>m;
    memset(f,-1,sizeof(f));
    while(n){
        A[n%10]++;
        n/=10;
    }
    p[0]=1;
    for(int i=1;i<=10;i++){
        p[i]=p[i-1]*(A[i-1]+1);//前缀积预处理
    }
    cout<<dfs(p[10]-1,0);//p[10]-1是一开始状态
}
```
## 相似题 P4163 排列
只需要把去前导 $0$ 的步骤删除，然后加点细节即可。
## $Code2$
```cpp
int A[10],m,p[12],T;
int f[1000][1<<10];
int dfs(int zt,int mv){
    if(!zt)return !mv;
    if(~f[mv][zt])return f[mv][zt];
    int ans=0;
    for(int i=9;~i;--i){
        if(zt%p[i+1]<p[i])continue;
        ans+=dfs(zt-p[i],(mv*10+i)%m);
    }
    return f[mv][zt]=ans;
}
int main(){
    scanf("%d",&T);
    while(T--){
        string n;
        cin>>n;
        scanf("%d",&m);
        memset(f,-1,sizeof(f));
        memset(A,0,sizeof(A));
        for(int i=0;i<n.length();i++){
            A[n[i]^48]++;
        }
        p[0]=1;
        for(int i=1;i<=10;i++){
            p[i]=p[i-1]*(A[i-1]+1);
        }
        printf("%d\n",dfs(p[10]-1,0));
    }
}
```

---

## 作者：SunnyYuan (赞：0)

## 思路

1. 把 $n$ 放在二进制下研究每一个数位是否选取，最多有 18 位；
2. 每次可以枚举选取的数字并拼接在原来的数字的最后；
3. 设状态 $f_{i, j}$ 表示选取的数字的状态在二进制下为 $i$，拼成的整数模上 $m$ 的余数为 $j$ 的方案数；
4. 答案为 $f_{2^n - 1, 0}$。
5. 状态转移：$f_{i, (10r + v_x) \bmod m} = f_{i - 2^x, r}$，假设选取第 $x$ 个数字，之前的余数为 $r$，现在的余数为 $10r + v_x$，现在的状态为 $i$，之前的状态没有包括 $x$，为 $i - 2^x$。
6. 初始状态：$f_{0, 0} = 1$；
7. 去重：设置 $vis$ 数组，每次有新状态的时候清空，使用的时候标记该数字。

## 代码

```cpp
/*******************************
| Author:  SunnyYuan
| Problem: Roman and Numbers
| Contest: Luogu
| URL:     https://www.luogu.com.cn/problem/CF401D
| When:    2023-10-04 18:49:29
| 
| Memory:  500 MB
| Time:    4000 ms
*******************************/

#include <bits/stdc++.h>

using namespace std;
using i64 = long long;

const int N = 18, M = 100;

i64 n, m;
i64 f[1 << N][M];
bool vis[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    vector<int> v;
    while (n) v.push_back(n % 10), n /= 10;
    f[0][0] = 1;
    int sz = v.size();
    for (int i = 1; i < (1 << sz); i++) {
        memset(vis, 0, sizeof(vis));
        for (int j = 0; j < sz; j++) {
            if (i == (1 << j) && (!v[j])) continue;
            if (i >> j & 1) {
                if (vis[v[j]]) continue;
                vis[v[j]] = true;
                for (int k = 0; k < m; k++) {
                    f[i][(10 * k + v[j]) % m] += f[i - (1 << j)][k];
                }
            }
        }
    }
    cout << f[(1 << sz) - 1][0] << '\n';
    return 0;
}

```

---

## 作者：liaiyang (赞：0)

很明显的状压 dp。

我们设 $dp_{S,k}$ 表示选的数位状态为 $S$，模 $m$ 为 $k$ 的方案数。

时间复杂度 $O(m\log_{10}n)$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define min(a,b) (a<b?a:b) 
#define P pair<int,int>
#define x first
#define y second
#define modd(x) (((x)%mod+mod)%mod) 
#define rd read()
#define lowbit(x) ((x)&(-x))
mt19937 rnd(time(0));
inline int read(int u=0, char c=getchar(), bool f=false){
    for (;!isdigit(c);c=getchar()) f|=c=='-';
    for (;isdigit(c);c=getchar()) u=(u<<1)+(u<<3)+c-'0';
    return f?-u:u;
}
inline void wt(int x){
    if(x<0) x=-x,putchar('-');
    if(x>9) wt(x/10);
    putchar(x%10+48);
}
inline void wt(int x,char k){wt(x),putchar(k);}
const int inf=~0U>>1,linf=~0ULL>>1; 
const int mod=998244353;
int n,m,vis,dp[(1<<18)][110],a[20],cnt;
main(){
    n=rd,m=rd;
    for(;n;n/=10) a[cnt++]=n%10;
    dp[0][0]=1;
    for(int i=1;i<(1<<cnt);i++){
        vis=0;
        for(int j=0;j<cnt;j++){
            if(i==(1<<j)&&!a[j]) break;
            if(!(i&(1<<j))||(vis&(1<<a[j]-1))) continue;
            vis^=(1<<a[j]-1);
            for(int k=0;k<m;k++) dp[i][(k*10+a[j])%m]+=dp[i^(1<<j)][k];
        }
    }
    wt(dp[(1<<cnt)-1][0],'\n');
    return 0;
}
```

---

## 作者：StillEmpty (赞：0)

**好多篇题解都是常规01状压dp，我有个渐进复杂度更优的思路。**

我的dp状态是 $f_{st, r}$， 其中 $st$ 是一个下标 $[0, 9]$ 的数组。$f_{st, r}$ 的意思是：满足 $0$ 在数位上出现 $st_0$ 次，$1$ 在数位上出现 $st_1$ 次，$2$ 在数位上出现 $st_2$ 次……，且 $\mod m = r$ 的数的数量（假设前导 $0$ 合法）。转移的时候我们可以枚举该数最高位是几，那么除去最高位的数的余数唯一确定，即可转移（相当于我们隐含了一维dp阶段 $\sum st$，因为 $\sum st = s$ 的情况下只会从 $\sum st = s-1$ 那里转移）。转移伪代码：
```
f(s, r) = 0;
for(int i = 0; i < 10; ++i) {
    if(s[i] == 0) continue;
    --s[i];
    f(s, r) += f(s, (r+m-(10^(sum-1))*i%m)%m);
    ++s[i];
}
```

（下文 `st` 均指 $n$ 的 $st$，$l$ 指 $\sum st$

我们还要减去一下有前导 $0$ 的情况，其实就是第一位为 $0$，后面随意，那么 `--st[0]` 再跑一遍dp相减就行了。

复杂度为 $\Theta(m\prod st)$，渐进最劣情况是 $O(m(\frac{l}{10})^{10})$。$n \leq 10^{18}$ 时由于常数，可能没有01状压快，但 $n$ 但凡再大一点就吊打01状压。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct state {
    int data[10];
    int &operator[](const size_t &i) {return data[i];}
};

const int L = 18, M = 100;
int m, pwrem[L+1]; state tot;
string str;
ll dp[59050][M];

inline int access(state s) {
    int ret = 0, mul = 1;
    for(int i = 0; i < 10; ++i) {
        ret += mul*s[i]; mul *= tot[i]+1;
    }
    return ret;
}
ll f(state s, const int &rem) {
    int ac = access(s);
    if(dp[ac][rem] != -1) return dp[ac][rem];
    int sum = 0;
    for(int i = 0; i < 10; ++i) sum += s[i];
    ll ret = 0;
    for(int i = 0; i < 10; ++i) {
        if(s[i] == 0) continue;
        --s[i];
        ret += f(s, (rem+m-pwrem[sum-1]*i%m)%m);
        ++s[i];
    }
    dp[ac][rem] = ret;
    return ret;
}

int main() {
    cin >> str >> m;
    for(int i = 0; i < str.size(); ++i) ++tot[str[i]-'0'];
    memset(dp, 0xff, sizeof(dp));
    pwrem[0] = 1%m;
    for(int i = 1; i <= L; ++i) pwrem[i] = pwrem[i-1]*10%m;
    for(int i = 0; i < 10; ++i) {
        if(tot[i] == 0) continue;
        state tmp; memset(tmp.data, 0, sizeof(tmp.data)); tmp[i] = 1;
        dp[access(tmp)][i%m] = 1;
    }
    ll ans = f(tot, 0), tmp;
    if(tot[0] == 0) {
        tmp = 0; goto Q;
    }
    --tot[0]; memset(dp, -1, sizeof(dp));
    for(int i = 0; i < 10; ++i) {
        if(tot[i] == 0) continue;
        state tmp; memset(tmp.data, 0, sizeof(tmp.data)); tmp[i] = 1;
        dp[access(tmp)][i%m] = 1;
    }
    tmp = f(tot, 0);
    Q: cout << ans-tmp << endl;
    return 0;
}
```

---

## 作者：Tenderfoot (赞：0)

判断当前长度是否选原数中的第 $i$ 为来作为当前长度的最后一位。选择一个数字之后，枚举所有余数并计算出新的余数。最后的长度为原长的余数为 $0$ 的数量。注意需要避免选择相同数字。

虚假の状态转移方程

$$Dp_{now,(j \times10+Num_i)\mathrm{mod}\ n}=\sum Dp_{N,j}$$

代码
```cpp
#include<bits/stdc++.h>

#define Mod 1000000009
#define int long long
#define MAXN 1000010
#define Enter puts("")
#define Space putchar(' ')
#define Test_Begin Enter , puts("Test--------------")
#define Test_End Enter , puts("--------------------")

using namespace std;

constexpr int INF = 2147483647;

static inline int Read()
{
	int Ans = 0;
	char Ch = getchar(), Las = ' ';
	while (!isdigit(Ch))
	{
		if (Ch == '-')
			Las = '-';
		Ch = getchar();
	}
	while (isdigit(Ch))
	{
		Ans = Ans * 10 + Ch - '0';
		Ch = getchar();
	}
	if (Las == '-')
		Ans = -Ans;
	return Ans;
}

static inline void Write(int x)
{
	if (x < 0)
	{
		x = -x;
		putchar('-');
	}
	if (x >= 10)
		Write(x / 10);
	putchar(x % 10 + '0');
}

int Dp[1 << 18][110];
bool Vis[1 << 18] , Chk[MAXN];
int Num[MAXN];
char C[MAXN];
int n , Len;
queue <int> Q;
stack <int> S;

static inline void BFS()
{
    while(!Q.empty())
    {
        int N = Q.front();
        Q.pop();
        memset(Chk , false , sizeof(Chk));
        for(register int i = 0; i < Len; i++)
        {
            if(N & (1 << i))
                continue;
            if(N == 0 and Num[i] == 0)
                continue;
            if(Chk[Num[i]])
                continue;
            else
                Chk[Num[i]] = true;
            int _N = N | (1 << i);
            for(register int j = 0; j < n; j++)
                Dp[_N][(j * 10 + Num[i]) % n] += Dp[N][j];
            if(!Vis[_N])
            {
                Vis[_N] = true;
                S.push(_N);
            }
        }
        if(Q.empty())
            while(!S.empty())
            {
                Q.push(S.top());
                S.pop();
            }
    }
}

signed main()
{
    ios :: sync_with_stdio(false);
    cin >> C >> n;
    Len = strlen(C);
    Dp[0][0] = 1;
    for(register int i = 0; i < Len ; i++)
        Num[i] = C[i] - '0';
    Q.push(0);
    BFS();
    Write(Dp[(1 << Len) - 1][0]) , Enter;
    return 0;
}
```


---

