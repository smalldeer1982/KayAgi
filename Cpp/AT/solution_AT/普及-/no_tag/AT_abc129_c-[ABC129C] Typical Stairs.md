# [ABC129C] Typical Stairs

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc129/tasks/abc129_c

$ N $ 段の階段があります。高橋君は現在、上り口($ 0 $ 段目)にいます。 高橋君は一歩で $ 1 $ 段か $ 2 $ 段上ることができます。

ただし、$ a_1,a_2,a_3,....a_M $ 段目の床は壊れており、その段に足を踏み入れることは危険です。

壊れている床を踏まないようにしながら、最上段($ N $ 段目)にたどりつくまでの移動方法は何通りあるでしょうか？ 総数を $ 1,000,000,007 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 10^5 $
- $ 0\ \leqq\ M\ \leqq\ N-1 $
- $ 1\ \leqq\ a_1\ ... $ $  $

### Sample Explanation 1

移動方法は以下の $ 4 $ 通りです。 - $ 0\ \to\ 1\ \to\ 2\ \to\ 4\ \to\ 5\ \to\ 6 $ - $ 0\ \to\ 1\ \to\ 2\ \to\ 4\ \to\ 6 $ - $ 0\ \to\ 2\ \to\ 4\ \to\ 5\ \to\ 6 $ - $ 0\ \to\ 2\ \to\ 4\ \to\ 6 $

### Sample Explanation 2

壊れている床を踏まないような移動方法がない場合もあります。

### Sample Explanation 3

総数を $ 1,000,000,007 $ で割った余りを出力することに注意して下さい。

## 样例 #1

### 输入

```
6 1
3```

### 输出

```
4```

## 样例 #2

### 输入

```
10 2
4
5```

### 输出

```
0```

## 样例 #3

### 输入

```
100 5
1
23
45
67
89```

### 输出

```
608200469```

# 题解

## 作者：Grisses (赞：4)

[题面](https://www.luogu.com.cn/problem/AT4787)

本题就是一道简单的递推。$f_0=1$，如果 1 号台阶没有损坏，$f_1=1$，否则 $f_1=0$。然后对于 $f_i(i>1)$ 的话：

- 如果 i 号台阶没有损坏，$f_i=(f_{i-1}+f_{i-2})\mod (10^9+7)$。

- 如果 i 号台阶损坏了，$f_i=0$。

代码：
```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  const int mod=1e9+7;
  int n,m,f[100005];
  unordered_map<int,bool>M;//标记是否损坏
  signed main()
  {
      scanf("%lld%lld",&n,&m);
      for(int i=1,a;i<=m;i++)scanf("%lld",&a),M[a]=1;
      f[0]=1;
      if(M.count(1)==0)f[1]=1;//初始化
      for(int i=2;i<=n;i++){
          if(M.count(i)==1)f[i]=0;
          else f[i]=(f[i-1]+f[i-2])%mod;//DP
      }
      printf("%lld",f[n]);
      return 0;
  }
```

---

## 作者：cqbztz2 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT4787)

[更好的阅读体验？](https://www.luogu.com.cn/blog/493271/solution-at4787)

# Thinking

首先说一下其他题解，比如[这篇题解](https://www.luogu.com.cn/blog/taozhilin/solution-at4787)：

ps:这篇题解后来在我的热心提醒下改了过来 qwq，艹还发帖举报我。

## 动态规划

动态规划是一种通过把原问题分解为相对简单的子问题的方式求解复杂问题的方法，应用于子问题重叠的情况。要去刻画最优解的结构特征，尝试递归地定义最优解的值（就是我们常说的考虑从 $ i-1 $ 转移到 $ i $），计算最优解，利用计算出的信息构造一个最优解。

## 递推

通过已知条件，利用相邻的数据项间的关系（即：递推关系），得出中间推论，直至得到结果的算法。

而本题不需要求最优解，没有最优子结构，只是普通的计数问题，只能称为递推，称为动态规划是不规范的，而题解必须严谨！

回归正题。

定义一个数组 $ a $,$ a_i $ 表示从第 $ 0 $ 级台阶出发走到第 $ i $ 级的方案数，而第 $ i $ 级是怎么走到的呢？是从第 $ i-1 $ 级或第 $ i-2 $ 级走到的，所以 $ a_i $ 的值也就由 $ a_{i-1} $ 和 $ a_{i-2} $ 得到。

对于初始化，从第 $ 0 $ 级台阶出发，所以走到第 $ 0 $ 级台阶的方案数为 $ 1 $。

还有需要注意的事，有 $ m $ 级台阶不能走，所以我们在输入时预处理是哪些台阶不能走，在递推遍历到不能走的台阶时，将走到该台阶的方案数设置为 $ 0 $ 即可。

# Coding

```
  #include<bits/stdc++.h>
  using namespace std;
  const int N=1e5+5,mod=1e9+7;
  int n,m,x,a[N],f[N];
  signed main(){
      a[0]=1;
      cin>>n>>m;
      while(m--){
          cin>>x;
          f[x]=1;
      } 
      for(int i=1;i<=n;i++){
          if(f[i]){
              continue;
          }
          a[i]=a[i-1]+a[i-2];
          a[i]%=mod;
      }
      cout<<a[n];
      return 0;
  }
```

---

## 作者：Ender_NaCl (赞：2)

这是一道**递推**题，而并非其他题解说的**动态规划**

简单讲一下两者的区别

- 递推是根据前面的答案**直接推出**现在的答案

- 而动态规划还需要**取最值**

回到题目
 
设 $f_i$ 是走到第 $i$ 级楼梯的可能

则 $f_i = f_{i - 1} + f_{i - 2}$

最后考虑一下边界值和最终答案

边界值 

- $f_0 = 1$ 因为一开始就一种可能
- $f_1 = 1$ 因为第一层只能从第零层爬上来

最终答案 $f_n$

上代码

```cpp
#include <iostream>

using namespace std;

const int MOD = 1000000007;
bool bad[100010];
long long f[100010];

int main()
{
	int n,m,i;
	cin>>n>>m;
	for(i = 0;i < m;i++)
	{
		int x;
		cin>>x;
		bad[x] = true;
	}
	if(!bad[0]) f[0] = 1; //注意设置边界值的时候需要判断这级楼梯有没有坏 
	if(!bad[1]) f[1] = 1;
	for(i = 2;i <= n;i++)
	{
		if(!bad[i]) //如果这级楼梯没坏 
		{
			f[i] = f[i - 1] + f[i - 2]; //转移 
			if(f[i] > MOD) f[i]%=MOD;
		}
	}
	cout<<f[n];
	return 0;
}
```


---

## 作者：Maxmilite (赞：1)

看到题解中好像没有人提到，这其实是一个变形的 **斐波那契数列**。

考虑一下斐波那契数列的定义，是 $f _ 0 = 1, f _ 1 = 1, \forall i \geq 2, f _ i = f _ {i - 1} + f _ {i - 2}$。

我们考虑一下这个楼梯，首先先不考虑损坏的部分。

那么对于第 $i$ 级楼梯，它**可以从 $i - 1$ 级或者 $i - 2$ 级上来**。

也就是说，上到第 $i$ 级楼梯的方案数，就是**上到第 $i - 1$ 级楼梯的方案数和第 $i - 2$ 级楼梯的方案数之和**。

如果我们用 $f _ i$ 来表示上到第 $i$ 级楼梯的方案数，那么就是 $f _ i = f _ {i - 1} + f _ {i - 2}$。

如果我们令 $f _ 0 = 0$，那么这就是斐波那契数列。

---

接下来考虑一下楼梯损坏的部分，如果第 $i$ 级楼梯损坏，那么是不是可以认为，$f _ i = 0$？

也就是说，上到第 $i$ 级楼梯的方案数，是 $0$。

所以我们在计算的时候，只需要判断一下当前楼梯是不是损坏的，如果是，那么就把当前楼梯的方案书清零，然后接着往下计算就可以了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define lint long long
#define rep(_, __, ___) for (int _ = __; _ <= ___; ++_)

int n, m;
int a[100005];
lint f[100005];

const int modint = 1e9 + 7;

int main()
{
	scanf("%d%d", &n, &m);
	rep(i, 1, m)
		scanf("%d", a + i);
	int ptr = 1;
	f[0] = f[1] = 1;
	if (a[ptr] == 1)
		f[a[ptr]] = 0, ++ptr;
	rep(i, 2, n)
	{
		f[i] = (f[i - 1] + f[i - 2]) % modint;
		if (i == a[ptr])
			++ptr, f[i] = 0;
	}
	printf("%lld\n", f[n]);
	return 0;
}
```

这里有一个小 Trick 是，由于它的损坏的楼梯是按从小到大给出的，所以我们只需要用一个指针 `ptr` 来记录一下当前已经计算到第几个损坏的楼梯，当当前 `ptr` 所指楼梯被计算完后，只需要让 `ptr + 1` 即可。

---

## 作者：houpingze (赞：1)

指正翻译

应该是
> 有 $n$ 级台阶，有 $m$ 级台阶不能走，分别为$a_1,a_2...a_m$级台阶。

思路：

由于
> 每次可以向上一格或两格

所以当我们在第$i$个台阶的时候$(i≥2)$，我们可能从$i-1$级跳上去，也有可能从$i-2$级跳上去

## code:
```cpp
/*
边界：
	f[0]=1,f[1]=1;
递推式：
	f[i]=(f[i-1]+f[i-2])%MOD;
特殊情况：
	如果此条路被破坏，解的总数为0 
解：
	f[n]  
*/

#include<bits/stdc++.h> 
#define MOD 1000000007
using namespace std; 
int n,cnt,m,a[114514],ans,tmp;
int f[1919810];
/*
	a[i]的值如果为1，表示此条路被破坏，走不通
	否则，可以走通 
*/
int main() { 
	cin>>n>>m;
	while(m--) cin>>tmp,a[tmp]=1;//标记，tmp这条路被破坏 
	if(!a[0]) f[0]=1;//注意判断第0条路是否被破坏 
	if(!a[1]) f[1]=1;
	for(int i=2;i<=n;i++) 
		if(!a[i]) //!a[i]也就是a[i]==0，判断是否被破坏 
			f[i]=(f[i-1]+f[i-2])%MOD; 
	cout<<f[n]<<endl;//解就是f[n] 
    return 0;
}

```

---

## 作者：RainFestival (赞：1)

我们使用递推

设到第 $i$ 阶台阶时有 $f_i$ 种方案

$g_i$ 为第 $i$ 阶台阶是否破碎

则 $f_i=[g_i=0](f_{i-1}+f_{i-2})$

时间复杂度 $O(n)$

代码如下：

```cpp
#include<cstdio>
int n,m,vis[100005],f[100005];
int main()
{
	scanf("%d%d",&n,&m);
	f[0]=1;
	for (int i=1;i<=m;i++)
	{
		int x;
		scanf("%d",&x);
		vis[x]=1;
	}
	if (!vis[1]) f[1]=1;
	for (int i=2;i<=n;i++) if (!vis[i]) f[i]=(f[i-1]+f[i-2])%1000000007;
	printf("%d\n",f[n]);
	return 0;
}
```

然后就 AC 了

QAQ

---

## 作者：封禁用户 (赞：1)

这道题目是一道 **[动态规划(DP)](https://oi-wiki.org/dp/)** 的练手题。
# 思路

emm,身为 XXS 我有发言权，这是小学课本题目。

我们仔细的想一想，如果没有坏掉的楼梯，那么这个就是一个斐波那契额数列，即 $fib_i = fib_{i-1} + fib_{i-2}$ 是我们发现会有一些地方没法走，
我们可以开一个 $no$ 数组，代表不能走的，然后再开一个  $dp$ 数组，$dp_i$ 是走到第 $i$ 级台阶的总数量。这样的话，如果 $no_i=0$ 那么 第 $i$ 级台阶没法走，即 $dp_i = 0$，否则，$dp_i=dp_{i-1}+dp_{i-2}$。

不太理解 DP 的看[这里](https://www.cnblogs.com/Wildcxj/p/15151870.html)。

# Code
```
int dp[Max],n,m;
bool no[Max];//不能走的。
int main(void){
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){int temp;scanf("%d",&temp);no[temp]=1;}
    if(!no[0]) dp[0]=1;
	if(!no[1]) dp[1]=1;//注意了，这边要初始化否则会有问题包括 RE。
    for(int i=2;i<=n;i++){
        if(no[i]==1){dp[i]=0;continue;}//如果不能走就 ByeBye。
        else{dp[i]=(dp[i-1]+dp[i-2])%mod;}//如果可以走根据上面的状态转移方程转化，注意要取模。
        
    }
    printf("%d\n",dp[n]);//输出，注意是输出 dp[n] 不是 dp[n-1]。
    return 0;
}
```
The end，谢谢支持。

---

## 作者：chu_K (赞：1)

## 思路：
   首先看到题目就会想到一道与这题十分相似的题，应该是叫**爬楼梯**。
两题唯一不同的就是本题多出了一项条件：第 $a_1,a_2...a_m$ 个台阶是不能走的。

那么这题就和爬楼梯一样，是一个简单 $dp$

首先我们定义 $f_i$ 表示到第 $i$ 阶台阶的**方案数**，因为每次只能上一层或两层，所以状态转移方程也很好推：$f_i=f_{i-1}+ f_{i-2}$  又因为第 $a_1,a_2...a_m$ 个台阶不能走，所以我们要定义一个 $bool$ 数组，若 $ff_{a_i}=true$ 则不进行操作，且若连续的两阶台阶都不能走的话就可以直接输出 $0$ 因为无法走到顶。

知道大致思路后这题还有两个需要注意的小细节
1. 在进行状态转移时别忘了取模。
1. 若第一阶和第二阶台阶均可走 $f_2=2$ 若只有第二阶可走则 $f_2=1$ 
 （刚做时我也做错了）
 
## CODE
```cpp
#include <cstdio>
#include <iostream>
#define int long long
using namespace std;
int i,n,f[1000001],j,m,a,sum;
bool ff[1000001];
const int mod = 1000000007;
signed main()
{
        cin >> n >> m;
        for (i=1; i<=n; i++) {ff[i]=true; f[i]=0;}
        for (i=1; i<=m; i++) {cin >> a; ff[a]=false;}

        if (ff[1]) f[1]=1; if (ff[2]&&ff[1]) f[2]=2; else if (ff[2]) f[2]=1;

        for (i=3; i<=n; i++)
        {
                if (ff[i-1]==false&&ff[i-2]==false) {cout << 0; return 0;}
                if (ff[i-1]==false&&ff[i]==false) {cout << 0; return 0;}
                if (ff[i]) f[i]=(f[i-2]+f[i-1]) % mod;
        }
        sum=f[n]% mod;
        cout << sum << endl;
}

```

再来一份Pascal的伪代码：

```pascal
          if ff[1]=true then f[1]:=1;
          if (ff[2]=true) and (ff[1]=true) then f[2]:=2
                           else if (ff[2]=true)  then f[2]:=1;

        for i:=3 to n do
        begin 
        if (ff[i-1]=false) and (ff[i-2]=false) then 
           begin
              write(0);exit;end;
        if (ff[i-1]=false) and (ff[i]=false) then
           begin
              write(0);exit;end;
          if (ff[i]=true) then 
                 f[i]:=f[i-2]+f[i-1] mod 1000000007; 
        end; 
```


八格缩进有点难看请见谅。

---

## 作者：makerlife (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT4787) | [AT原题传送门](https://atcoder.jp/contests/abc129/tasks/abc129_c)

## 思路

这其实是一道**递推**题。

打眼一看，这道题和[P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)是差不多的，只不过是本题又新增了一个条件：有 $m$ 个楼梯是坏的。

如果没有这个条件，我们可以定义，第 $i$ 阶楼梯的总方案数为 $f_i$，从题目中可以很容易得出：$f_i=f_{i-1}+f_{i-2}(i \geq 2)$，因为只能从第 $i-1$ 和第 $i-2$ 阶楼梯上到第 $i$ 阶楼梯。

加上那个条件后，我们可以定义一个 $\texttt{bool}$ 数组 $\texttt{vis}$，如果第 $i$ 阶楼梯是坏的，那 $vis_i=true$，否则 $vis_i=false$。

有几点需要注意：

1. 每次递推都需 $\bmod 10^9+7$；
2. 如果连续两阶楼梯都是坏的，也就是 $vis_i=true$ 且 $vis_{i-1}=true$，直接输出 $0$ 并退出程序（不判断也不会超时）；
3. 从第 $0$ 阶台阶开始计算；
4. 赋 $f_0$ 和 $f_1$ 的初始值时要特判第 $0$ 和第 $1$ 阶楼梯是否损坏。

## 直接上代码

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
inline int read()//快读
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
const int mod=1e9+7;
int n,m,a,f[100010];
bool vis[100010]={0};
int main()
{
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		a=read();
		vis[a]=1;//标记该台阶已损坏
		if(vis[a] && vis[a-1])//判断是否有连续两个台阶是坏的
		{
			cout<<0<<endl;
			return 0;
		}
	}
	if(!vis[0])//特判第0和第1阶楼梯是否损坏
	{
		f[0]=1;
	}
	if(!vis[1])
	{
		f[1]=1;
	}
	for(int i=2;i<=n;i++)
	{
		if(vis[i]) f[i]=0;//如果该楼梯损坏，则无法上到该楼梯
		else
		{
			f[i]=(f[i-1]+f[i-2])%mod;//递推式(不要忘了取模)
		}
	}
	cout<<f[n]<<endl;
	return 0;
}

```

**记得结尾要换行哦**


---

## 作者：WHJ___ (赞：0)

 一道非常简单的 **dp** 题。
 
##  推导
 
因为第 $k$ 个楼梯可以从第 $k-1$ 个楼梯往上走 $1$ 级得到，也可以从第 $k-2$ 个楼梯向上走 $2$ 级得到，所以我们可以发现：到达第 $k$ 个楼梯的方法总数是到达第 $k-1$ 个楼梯的方法数与到达第 $k-2$ 的楼梯的方法数的总和。当然，可到达不能走的楼梯的方案数一定是 $0$。
 
这样我们就可以得到一个式子：
$dp_i=dp_{i-1}+dp_{i-2}$
 
## 初始化

由于第 $0$ 个台阶一定能走，所以能到达第 $0$ 个楼梯的方案数一定是 $0$。如果第 $1$ 个楼梯可走，则 $dp[1]=1$(即由第 $0$ 个楼梯向上 $1$ 个台阶得到)；否则 $dp_i=0$。

## 代码

```cpp
#include<bits/stdc++.h>
#define I long long
#define RI register int
#define il inline
#define rt return
using namespace std;
const int N=1e5+7;
const int zzh=1e9+7;

I n,m,a[N]; 
bool b[N]; 

il I d(){
	I x=0,f=1;
	char c=0;
	while(!isdigit(c=getchar()))f-=(c=='-')*2;
	while(isdigit(c)){x=(x<<1)+(x<<3)+f*(c-48);c=getchar();}
	rt x;
}

signed main()
{
	RI i,j;
	n=d();m=d();
	memset(b,1,sizeof(b));//初始化所有楼梯可走 
	for(i=1;i<=m;++i) b[d()]=0;//这些楼梯不可走 
	a[0]=1;//第0个楼梯一定可走 
	if(b[1]) a[1]=1;//第1个楼梯是否可走 
	for(i=2;i<=n;++i)
		if(b[i])a[i]=(a[i-1]+a[i-2])%zzh;//递推 
	cout<<a[n];
	rt 0;
}
```


---

