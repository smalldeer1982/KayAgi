# Pie Rules

## 题目描述

You may have heard of the pie rule before. It states that if two people wish to fairly share a slice of pie, one person should cut the slice in half, and the other person should choose who gets which slice. Alice and Bob have many slices of pie, and rather than cutting the slices in half, each individual slice will be eaten by just one person.

The way Alice and Bob decide who eats each slice is as follows. First, the order in which the pies are to be handed out is decided. There is a special token called the "decider" token, initially held by Bob. Until all the pie is handed out, whoever has the decider token will give the next slice of pie to one of the participants, and the decider token to the other participant. They continue until no slices of pie are left.

All of the slices are of excellent quality, so each participant obviously wants to maximize the total amount of pie they get to eat. Assuming both players make their decisions optimally, how much pie will each participant receive?

## 说明/提示

In the first example, Bob takes the size $ 141 $ slice for himself and gives the decider token to Alice. Then Alice gives the size $ 592 $ slice to Bob and keeps the decider token for herself, so that she can then give the size $ 653 $ slice to herself.

## 样例 #1

### 输入

```
3
141 592 653
```

### 输出

```
653 733
```

## 样例 #2

### 输入

```
5
10 21 10 21 10
```

### 输出

```
31 41
```

# 题解

## 作者：Lilyana (赞：8)

虽然我也不知道为什么会被评成黑题（这题顶多蓝题难度），因为就连我这样的蒟蒻都能几分钟切掉它....

总有一种恶意评级的感觉来着........

数据范围简直神坑（50很容易让人想到n^3或者以上的算法啊.....）。

然而实际上的时间复杂度是O（n），就算是1e6都能做....（我还一直以为是错的不敢交）

好的那我们步入正题，这道题实际上是一道比较具有博弈性质的题。

介于两方都需要以最优策略进行操作，贪心是肯定行不通的，于是我们考虑dp

首先我们可以发现，由于双方进行的操作**对后面的状态会产生影响**
所以说如果我们直接正着dp，定义dp[i]为选到了前i个城市的时候先手（其实先后手一样）能够取得的最大收益，我们会发现：**它的状态和选择方式（选或者不选以及这里先手到底能不能选）会产生后效性**,因为你这一步选了跟不选，一方面会影响之后的选择的结果，另一方面会影响到之后另一个人最优决策的方式，这样就使得dp的值不仅与它所存在的状态有关系，同时也与**到达这个状态的方式**有关系，这个是dp所不能允许的（就算记录选或不选的状态也解决不了这个问题）

所以我们考虑倒着dp,定义dp[i]为当前的人在从i开始选，一直到游戏结束所能够获得的最大收益，那么我们会发现这个dp的重要性质：由于你选择一个物品之后的最优解是单一的，转移过后最终推得的结果仅与这个状态本身有关系，而两人之后的最优决策都固定了，所以就拥有了无后效性，于是可以使用dp来解决
我们定义从i开始的后缀和为sum[i],那么dp方程就确定了

dp[i]=max(dp[i+1],sum[i+1]-dp[i+1]+a[i]);

如果考虑不选，那么选了这次以后，选择权仍然在自己手上，那么我们直接用下一个的dp值就好（因为i+1的选择权仍然在自己手上）
如果选择了的话，那么我们就会选择所有除去对手选择范围之外的所有城市，再加上这次选择这个城市能够得到的价值

先后手这种问题就在sum[1]-dp[1]和dp[1]之间二选一跟着样例拍一下就知道啦~~~~
```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
const int MAXN(1e5+5);
inline int read()
{
	char ch(getchar());
	int x(0);
	int flag(1); 
	while(!isdigit(ch))
	{
		if(ch=='-')
		{
			flag=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch))
	{
		x=(x<<1)+(x<<3)+(ch^48); 
		ch=getchar();
	}
	return flag*x;
}
int sum[MAXN];
int a[MAXN];
int dp[MAXN];
int main()
{
	int n(read()); 
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
	}
	for(int i=n;i>=1;i--)
	{
		sum[i]=sum[i+1]+a[i]; 
		dp[i]=std::max(dp[i+1],sum[i+1]-dp[i+1]+a[i]);
	}
	std::printf("%d %d\n",sum[1]-dp[1],dp[1]);
	return 0;
}
```

---

## 作者：ljk654321 (赞：7)

先判断数的大小，决定将当前数加给谁。如果一个大于等于另一个数，则将当前数加给这个数，否则将当前数加给另一个数。只要一个数大于另一个数就把数加到另一个数这边，反之，加到这个数那边。所以我们只需要算出两个人中一个人的分数，再用总分数减就能得到另一个人的分数了。而这题说每个人都会是最优策略，即不是考虑当前最优解，而是考虑未来最优解，典型的博弈论。
* 首先，要使个人获得的分数越多，肯定要挑大的数选，其他的数都可以给对方。
* 其次如果两人都抱着这样一个心态来选的话，两人的分数差都不会太大（除非有一个特别大的数被某一个人选了）。



可以先定义一个数组，将其遍历一遍，然后进行判断大小，最后输出就可以了。



代码：
```cpp
#include<bits/stdc++.h>//头文件。 
using namespace std;
int n,i,shu[10005],a,b;//定义变量和数组。
int main()//主函数。 
{
    cin>>n;//输入。
    for(i=1;i<=n;i++)//循环。
	{
        cin>>shu[i]; //遍历一遍。 
    }
    for(i=n;i>=1;i--)//还是循环循环。
	{
		if(a>=b) b=b+shu[i];//判断他们谁大。
		else a=a+shu[i];      
	}
	cout<<min(a,b)<<" "<<max(a,b);//输出Alice和Bob的最终得分。
	return 0;
}
```



---

## 作者：yyz1005 (赞：5)

# Part 1 思路
记 dp 数组为 $dp[i][j]$，当 $j=1$ 时表示当 Alice 有第 $i$ 个数的决策权时在第 $i$ 至第 $n$ 个数中可获得的最大收益；当 $j=0$ 时表示当 Bob 有第 $i$ 个数的决策权时在第 $i$ 至第 $n$ 个数中可获得的最大收益。

记 $sum[i]$ 为第 $i$ 至第 $n$ 个数的和，第 $i$ 个数为 $a[i]$。

则以 $j=0$ 为例：

$dp[i][0] = max(dp[i+1][0],sum[i+1]-dp[i+1][1]+a[i])$

$dp[i+1][0]$ 表示 Bob 将 $a[i]$ 给 Alice，自己继续决策 $a[i+1]$。

$sum[i+1]-dp[i+1][1]+a[i]$ 表示 Bob 拿走 $a[i]$,Alice 将获得 $a[i+1]$ 的决策权，而 Alice 在第 $i+1$ 至第 $n$ 个数中最多获得 $dp[i+1][1]$，剩下 $sum[i+1]-dp[i+1][1]$，Bob 总共获得 $sum[i+1]-dp[i+1][1]+a[i]$。

显然，$dp[n][0] = dp[n][1] = a[n]$。

然而对于任何一个数，无论是 Alice 决策还是 Bob 决策，获得的最大值显然不变，所以 $dp[i][0] = dp[i][1]$，原状态转移方程可变为：$dp[i] = max(dp[i+1],sum[i+1]-dp[i+1]+a[i])$
## Part 2 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a[55],sum = 0;
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	int dp[55];
	dp[n] = a[n];
	sum = a[n];//这里将思路中的sum简化为一个变量 
	for(int i = n-1; i >= 1; i--){
		dp[i] = max(dp[i+1],sum-dp[i+1]+a[i]);
		//在进行第i个数的计算时sum恰好为思路中的sum[i+1] 
		sum+=a[i];
	}
	//此时sum变为了所有数的和 
	cout << sum-dp[1] << " " << dp[1];
	//由于第一个数的决策权在Bob，所以Bob是dp[1],Alice是sum-dp[1] 
	return 0;
}
```


---

## 作者：Xdl_rp (赞：5)

就是 `前缀和`$+$`DP` 嘛。

像我这种蒟蒻都~~能一小时~~切的题目

进入正题 ：
------------
题意： 就是给你一个长度为 $n$ 的整数序列 $a$，共有两个人，每一个人都有一个决策，要不把这个数给你，我继续选；要不这个数归我，换你来选。

- 首先，要使个人获得的分数越多，肯定要挑大的数选，其他的数都可以给对方。
- 其次如果两人都抱着这样一个心态来选的话，两人的分数差都不会太大（除非有一个特别大的数被某一个人选了）。

就看样例：

3

141 592 653


1. `Bob` 选 $141$。
2. `Alice` 不选 $592$，将其给 `Bob`。
3. `Alice` 获得 $653$，游戏结束。

结果：也就是如果从现在开始（设为 $k$)，如果 $\large a_k \ge sum_{k - 1}$，就选 $a_k$ 作为选择，否则就加给对方。
     
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[55],sum[55],dp[55];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=n;i>=1;i--){
		sum[i]=sum[i+1]+a[i];
	}
	dp[n]=a[n];
	for(int i=n;i>=1;i--) dp[i]=max(dp[i+1],sum[i+1]-dp[i+1]+a[i]);
	cout<<sum[1]-dp[1]<<" "<<dp[1]<<endl;
	return 0;
}
```


---

## 作者：songge888 (赞：2)

### 题意

Alice 和 Bob 在长度为 $n$ 的序列 $a$ 中选数，Bob 先选，对于每次选数。

- 选了这个数，把这个数加给自己，下次对方选。
- 不选这个数，把这个数加给对方，下次自己选。

求 Alice 和 Bob 最后的分数。

### 思路

考虑 DP，$dp_{i}$ 表示在区间 $(i,n)$ 中通过最优选法的得分，$sum_i$ 表示后缀和。

- 如果当前不选这个数，分数不变，$dp_{i}=dp_{i+1}$。
- 如果当前选了这个数，$dp_{i}=sum_{i+1}-dp_{i+1}+a_i$，以 Bob 为例，Bob 选了第 $i$ 个数，加上 $a_i$，下一次让 Alice 选，大小为 $dp_{i+1}$，用 $sum_{i+1}-dp_{i+1}$ 就是 Bob 在 $(i+1,n)$ 得到的分数，Alice 同理。

化简得：

$$dp_i= \max (dp_{i+1},sum_i-dp_{i+1})$$

时间复杂度 $O(n)$。

### Code

```c++
#include<bits/stdc++.h>
#define bug cout<<"songge888"<<'\n';
#define int long long
using namespace std;
int n;
int a[114],sum[114],dp[114]; 
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
	}
	for(int i=n;i>=1;i--){
		sum[i]=sum[i+1]+a[i];
	}
	for(int i=n;i>=1;i--){
		dp[i]=max(dp[i+1],sum[i]-dp[i+1]);
	}
	cout<<sum[1]-dp[1]<<' '<<dp[1];
	return 0;
}
```

[提交记录](https://codeforces.com/contest/859/submission/297042732)

---

## 作者：TainityAnle (赞：2)

**思路：**

容易发现 Bob 得分一定比 Alice 高，所以我们只需要考虑当 Alice 用最优策略时 Bob 的最高得分，Alice 的得分就是总数减去 Bob 的得分。

思考什么情况下会给对方，什么情况下会给自己。

根据样例分析：

```
3
141 592 653
```

若 Bob 把 $141$ 给到 Alice，那么他也会把 $592$ 给 Alice，因为他选 $653$ 比选 $592$ 更优。但即便如此，Alice 得到了 $733$，即 $a_1+a_2$。所以 Bob 必须选 $141$。

通过以上分析，我们发现不易确定当前这一步选的在下一步是否最优，也就是有后效性，所以正难则反，设 $f_i$ 表示从 $i$ 到 $n$ 的最优值。

如果选这个值，那么下一个位置的决策就给了 Alice，那么 $f_{i+1}$ 就会给 Alice。我们对于 Bob 来讲，就相当于减去了 $f_{i+1}$，这时的 $f_i$ 就是第 $i$ 个数到第 $n$ 个数的和，所以再维护一个前缀和就行了。

如果不选这个值，那么就等于 $f_{i+1}$

设 $b_i$ 表示从 $i$ 到 $n$ 的后缀和，则状态转移方程为：
$$
f_i=\max(f_{i+1},b_i-f_{i+1})
$$

**AC Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[55],sum[55],f[55];
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	for(int i=n; i>=1; i--) sum[i]=sum[i+1]+a[i];
	for(int i=n; i>=1; i--) f[i]=max(f[i+1],sum[i+1]-f[i+1]+a[i]);
	cout<<sum[1]-f[1]<<' '<<f[1];
	return 0;
}
```

---

## 作者：FstAutoMaton (赞：2)

一道绿色小水题~~我只会水题~~。

首先可以知道，每一个得分不是 ```Alice``` 的就是 ```Bob``` 的，所以我们只需要算出两个人中一个人的分数，再用总分数减就能得到另一个人的分数了。而这题说每个人都会是最优策略，**即不是考虑当前最优解，而是考虑未来最优解**，典型的博弈论。那么设状态 ```dfs( int step, int sum, int o )``` 为当前在第 $step$ 格， ```Bob``` 有  $sum$ 分，现在是第 $o$ 个人（ 0 为 ```Bob``` ，1 为  ```Alice``` ），那么可以得 ```dfs``` 函数为：
```
int dfs( int step, int sum, int o )
{
	if( step > n ) return 0;
	if( !o )
	return max( dfs( step + 1, sum + a[step], !o ), dfs( step + 1, sum, o );
	else
   	return max( dfs( step + 1, sum + a[step], o ), dfs( step + 1, sum, !o );
}
```
再加上记忆化，代码如下：
```
int dfs( int step, int sum, int o )
{
	if( step > n ) return 0;
	if( f[step] ) return f[step];
	if( !o )
	return f[step] = max( dfs( step + 1, sum + a[step], !o ), dfs( step + 1, sum, o );
	else
   	return f[step] = max( dfs( step + 1, sum + a[step], o ), dfs( step + 1, sum, !o );
}
```
写出 ```dfs``` 函数后，我们可以考虑进行 ```dp``` 。转移方程可以直接从 ```dfs``` 中搬过来，再设 $sum_i$ 为 $\sum\limits_{i=j}^na_j$ ，方便转移，那转移方程是:
$$ f_{i,0} = max( f_{i+1,0}, sum_{i+1}-f_{i+1,1}+a_i )$$

其中 $f_{i+1,0}$  表 ```Bob``` 接着选下一个，不选这一个，  $sum_{i+1}-f_{i+1,1}+a_i$ 表示 ```Bob``` 选择这一个。
可以发现， $o$ 可以进行省略，代码如下：
```
#include <bits/stdc++.h>
using namespace std;
int n, a[55], f[55], sum[55];
int main()
{
    cin >> n;
    for( int i = 1; i <= n; i ++ ) cin >> a[i];
    f[n] = sum[n] = a[n];
    for( int i = n; i; i -- )
    {
        sum[i] = sum[i + 1] + a[i];
        f[i] = max( f[i + 1], sum[i + 1] - f[i + 1] + a[i] );
    }
    cout << sum[1] - f[1] << " " << f[1];
}
```


---

## 作者：kn_wlq (赞：1)

我们要先知道，每个人一共有两种操作方式，第 $1$ 种方式是数给自己，决策权给对方，第 $1$ 种方式是数给对方，决策权自己保留。

我的思路就是从 $n$ 递减到 $1$，开始判断 $a$ 和 $b$ 的大小，决定将当前数加给谁。如果 $a$ 大于等于 $b$，则将当前数加给 $b$；否则，将当前数加给 $a$。

题目中有一句话：

“假定他们都使用最优策略，求他们最后分别能获得多少分。”

就是都为自己想，尽最大的可能争取自己能赢，所以只要
 Alice 大于 Bob 就把数加到 Alice 这边，反之，加到 Bob 那边。 

~~应该属于最短的了吧。~~

附上 AC 代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,i,c[10005],a,b;
int main(){
cin>>n;
	for(i=1;i<=n;i++){
		cin>>c[i];	
	}
	for(i=n;i>=1;i--){
		if(a>=b) b=b+c[i];//判断他们谁大。
		else a=a+c[i];		
}
cout<<min(a,b)<<" "<<max(a,b);//输出Alice和Bob的最终得分。
}  
```


---

## 作者：ylch (赞：0)

[Luogu - CF859C](https://www.luogu.com.cn/problem/CF859C)

## Analysis

由题意知每个人选择时都是以最佳情况来选，最佳情况是指他的选择能使后面拿的更多。所以决定最佳情况是来自后面。

还有一个重要性质，不管是 Bob 还是 Alice，只要是拥有决策权的人面对同一个局面，其得到的最大得分一定相等。这样，我们找到了固定状态，就可以 dp 了。

因为我们管的是从某个位置往后面取的最大值，所以可以找某一个位置 $i$ 到 $n$ 的值。

设 $f(i,n)$ 表示 $i \sim n$ 区间里，选到 $i$ 时，先手取的最大值。$a$ 数组存储原序列，$sum_{i,j}$ 表示 $a_i \sim a_j$ 的和。

分两种情况：
1. 他要拿的当前的数。相当于增加收益，但把选择权给了对方。转移到 $sum_{i+1,n}-f(i+1,n)+a_i$。\
意思是 $[i+1,n]$ 区间的和，减去后面的人可以取到的最大值，再加上当前可以拿的 $a_i$。

2. 他选当前的数，选后面的。相当于放弃了收益，但保留选择权。转移到 $f(i+1,n)$。

发现 $f$ 函数第二个参数都是 $n$，可以省略。

于是，设 $f[i]$ 表示先手面对 $i \sim n$ 时，可以取到的最大值。
我们只需将两种情况的最大值，赋值给 $f_i$ 即可：
$$f_i=\max\{f_{i+1},\ sum_{i+1,n}-f_{i+1}+a_i\}$$

我们知道第一个选的是 Bob，所以 Bob 得到的就是 $f_1$，Alice 得到的就是 Bob 剩下的，即 $sum_{1,n}-f_1$。

## Code

考虑倒序 dp。注意 $a_i$ 的范围是 $10^6$，不开 long long 必然会炸。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve()
{
    int n;
    cin >> n;
    vector <int> a(n + 1); // 原始数组
    vector <ll> s(n + 1); // 前缀和数组，a[i]<=1e6，开long long！
    vector <ll> f(n + 2); // dp数组，long long
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    for(int i = n; i >= 1; i --){ // 倒推
        f[i] = max(f[i + 1], (s[n] - s[i]/*i+1~n区间和*/) - f[i + 1] + a[i]);
    }
    cout << s[n] - f[1] << ' ' << f[1] << endl;
}

signed main()
{
    ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
```

## End

管理员大大辛苦啦~

这里是 YLCHUP，谢谢大家！

---

## 作者：zqh123b (赞：0)

### [洛谷传送门](https://www.luogu.com.cn/problem/CF859C)
### [CF 传送门](http://codeforces.com/problemset/problem/859/C)

----
### 题意：
对于每个正在操作的人来说，有以下两个操作：
1. 自己得到当前数字，但是失去下个数字的操作权。
2. 对手得到当前数字，但是拥有下个数字的操作权。

求两人在最优策略下的得分。

----
### 分析：
一眼看去，$0 \leq n \leq 50$？！  
这是。。。$O(n^3)$？！  
**但是！**  
这是一道**动态规划**！  

----
先定义 $dp_i$ 表示到第 $i$ 个数时，先手的最大分数。    
提到动态规划，那最重要的一定是**转移方程**。  
这个转移方程不难，就是根据上面的两个操作写的。  
对于当前操作的人，如果选择第一种操作，则：
```cpp
dp[i]=dp[i+1];
```
这个不难吧。  

----
如果选择第二种操作呢？  
这时候，可以换一个角度：  
定义 $dp_i$ 表示到第 $i$ 个数时，操作者的最大分数。  
那么，非操作者的最大分数怎么表示呢？  
只需要一个**前缀和数组**！  
这样，第二种操作的转移方程也出来了：
```cpp
dp[i]=sum[i+1]-dp[i+1]+a[i];
```
由于两人都用最优策略，因此要把以上两种操作取一个最大值。最终的转移方程如下：
```cpp
dp[i]=max(dp[i+1],sum[i+1]-dp[i+1]+a[i]);
```

----
还有一个小细节：需要**反向循环**。  
因为转移方程中，当前项的值取决于下一项的值。  
同时，前缀和数组也要是反向前缀和。

----
### 贴代码
```cpp
//请忽略超长的缺省源
//为了防止抄tj，题目中所有变量名都有特殊含义
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(x) cerr<<x<<endl;
#define read(x) x=read_int()
#define writen(x) write_int(x,1)
#define writes(x) write_int(x,2)
inline int read_int(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return x*f;}
void write_int(int x,short e){if(x<0){putchar('-');x=-x;}if(x>9){write_int(x/10,0);}putchar(x%10+'0');if(e==1){putchar('\n');}if(e==2){putchar(' ');}}
inline ll read_ll(){ll x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return x*f;}
void write_ll(ll x,short e){if(x<0){putchar('-');x=-x;}if(x>9){write_ll(x/10,0);}putchar(x%10+'0');if(e==1){putchar('\n');}if(e==2){putchar(' ');}}
const int N=5e1+10;
int n,zqh123b[N],b123[N]zqh[N];
int main(){
	read(n);
	for(int i=1;i<=n;i++){
		read(zqh123b[i]);
	}
	for(int i=n;i>=1;i--){
		b123[i]=b123[i+1]+zqh123b[i];
		zqh[i]=max(zqh[i+1],b123[i+1]-zqh[i+1]+zqh123b[i]);
	}
	writes(b123[1]-zqh[1]);
	writes(zqh[1]);
	return 0;
}
```


---

