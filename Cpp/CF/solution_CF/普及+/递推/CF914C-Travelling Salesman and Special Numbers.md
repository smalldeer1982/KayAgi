# Travelling Salesman and Special Numbers

## 题目描述

The Travelling Salesman spends a lot of time travelling so he tends to get bored. To pass time, he likes to perform operations on numbers. One such operation is to take a positive integer $ x $ and reduce it to the number of bits set to $ 1 $ in the binary representation of $ x $ . For example for number $ 13 $ it's true that $ 13_{10}=1101_{2} $ , so it has $ 3 $ bits set and $ 13 $ will be reduced to $ 3 $ in one operation.

He calls a number special if the minimum number of operations to reduce it to $ 1 $ is $ k $ .

He wants to find out how many special numbers exist which are not greater than $ n $ . Please help the Travelling Salesman, as he is about to reach his destination!

Since the answer can be large, output it modulo $ 10^{9}+7 $ .

## 说明/提示

In the first sample, the three special numbers are $ 3 $ , $ 5 $ and $ 6 $ . They get reduced to $ 2 $ in one operation (since there are two set bits in each of $ 3 $ , $ 5 $ and $ 6 $ ) and then to $ 1 $ in one more operation (since there is only one set bit in $ 2 $ ).

## 样例 #1

### 输入

```
110
2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
111111011
2
```

### 输出

```
169
```

# 题解

## 作者：Yt_pY (赞：10)

数位DP好题

## 题意：

对于一个正整数 $x$，定义一次操作是将其变为它二进制下“1”的个数。显而易见的是，对于一个正整数，在进行若干次操作后，一定会将其变为1。

给定 $n$ 和 $k$，其中 $n$ 是在二进制下给出，求出所有不大于 $n$ 且将其变为1的操作次数为 $k$ 的数的个数（模1e9+7）。  
$1<=n<2^{1000},0<=k<=10000$

## 题目分析：

我们操作一次，就能把 $n$ 变成1000以内的数。

预处理出1000以内所有数需要操作多少次才能变成1。

```cpp
//sum[x]表示x在二进制下有多少个1
//cnt[x]表示x需要操作多少次才能变成1
inline int lowbit(int x){return x&(-x);}
//lowbit(x)就是提取x的右数第一个1表示的数
void init()
{
	sum[0]=0;
	cnt[1]=0;
	for(int i=1;i<=1000;i++)sum[i]=sum[i^lowbit(i)]+1;
	for(int i=2;i<=1000;i++)cnt[i]=cnt[sum[i]]+1;
}
```

接下来进行数位DP。

`f[s][num][lim]`表示当前还剩 $s$ 长度没有填，1的个数为 $num$，$lim$ 为1/0表示有、没有顶上界。

简单说一下顶上界的意思，我们在一位一位填数时，要保证填的数小于等于 $n$，如果之前已经有一位比 $n$ 的那一位小了，那么当前位填什么都可以，即没有顶上界状态；如果依然是顶上界，那么当前位不能超过 $n$ 的当前位，即顶上界状态。

```cpp
int dfs(int s,int c,int lim)//还剩s长度，1有c个，lim为1/0表示顶/没顶上界 
{
	if(s==0)//都填完了
	{
		if(c==0)return 0;//特判，全填的是0
		else return(cnt[c]+1==k);//如果c这个小于1000的数变成1所需次数加一是k，答案加一
	}
	if(f[s][c][lim]!=-1)//记忆化搜索
		return f[s][c][lim];
	
	int res=0;
	if(lim==1)//顶上界状态
	{
		if(num[s]==0)//当前位是0，只能填0
			res=(res+dfs(s-1,c,1))%mod;
		else//填0或1
		{
			res=(res+dfs(s-1,c,0))%mod;
			res=(res+dfs(s-1,c+1,1))%mod;
		}
	}
	else//没有顶上界状态
	{
		res=(res+dfs(s-1,c,0))%mod;
		res=(res+dfs(s-1,c+1,0))%mod;
	}
	return f[s][c][lim]=res;
}
```

当然还有一些细节：

```
主函数
如果k=0
	输出1
记忆化搜索
如果k=1
	答案-=1;//特判如果k=1，那么1这个不该被算的数也被算进去了
```


------------
## 完整代码：
```cpp
#include<bits/stdc++.h>
#define maxn 1005
#define mod 1000000007
using namespace std;

int k;
char s[maxn];
int len,num[maxn];
int sum[maxn],cnt[maxn];
int f[maxn][maxn][2],ans;

inline int lowbit(int x){return x&(-x);}

void init()
{
	sum[0]=0;
	cnt[1]=0;
	for(int i=1;i<=1000;i++)sum[i]=sum[i^lowbit(i)]+1;
	for(int i=2;i<=1000;i++)cnt[i]=cnt[sum[i]]+1;
}

int dfs(int s,int c,int lim)//还剩s长度，1有c个，lim为1/0表示顶/没顶上届 
{
	if(s==0)
	{
		if(c==0)return 0;
		else return(cnt[c]+1==k);
	}
	if(f[s][c][lim]!=-1)
		return f[s][c][lim];
	
	int res=0;
	if(lim==1)
	{
		if(num[s]==0)
			res=(res+dfs(s-1,c,1))%mod;
		else
		{
			res=(res+dfs(s-1,c,0))%mod;
			res=(res+dfs(s-1,c+1,1))%mod;
		}
	}
	else
	{
		res=(res+dfs(s-1,c,0))%mod;
		res=(res+dfs(s-1,c+1,0))%mod;
	}
	return f[s][c][lim]=res;
}

int main()
{
	init();
	scanf("%s%d",s,&k);
	if(k==0)
	{
		printf("1\n");
		return 0;
	}
	len=strlen(s);
	for(int i=1;i<=len;i++)num[i]=s[len-i]-'0';
	
	memset(f,-1,sizeof(f));
	ans=dfs(len,0,1);if(k==1)ans--;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：一个句号 (赞：6)

既然找到这个题了，我认为大家基本都是为了练习数位 DP，笔者很弱，看不太懂楼下题解，参考各个资料琢磨很久后给出此数位 DP 模板化思路及代码（不涉及组合数）。

## 题意
- 给定一个数字 $n$ 的二进制表达，求从 $1 \sim n$ 满足操作的数一共有几个。
- 操作为将二进制表达中 $1$ 的个数赋值给本数。

## 题目分析

我们先忽略操作的具体内容，来看怎么统计个数。

- 大数包含的满足操作的个数必然包含小数的个数，所以可以数位 DP 记忆化进行 DFS。
- （数位 DP 的实质是将答案记录在数位上，再枚举满足条件的下一位数位时直接调用）。
- 观察题目所给样例：发现给出二进制，二进制的数位限制其实和十进制大差不离，只不过设置枚举 $max \sim num$ 时 $9$ 变为 $1$。
- 考虑数位 DP 的十进制 $num$ 数组转存成二进制的 $01$。
- 这样依次来统计满足操作的有多少个。

- 其实就是套数位 DP 的模板。

怎么套模板呢？

- 首先 DFS 的几个状态基本是固定的，$pos$ 当前位置，$sum$ 当前 $1$ 的个数，$flag$ 上界，$zero$ 为前导零。

- 基本上代码都是板子，主要是 DP 状态的设计比较难。

我们再来看怎样判断一个二进制数是否满足操作。

- 赋值为二进制中 $1$ 的数量，并找出其变为 $1$ 的操作次数，操作次数为 $k$ 时满足条件。

- 题目给出的数据范围虽然看起来吓人，但是我们直接读入 $num$ 数组，$1$ 的数量便会指数级下降为 $1000$，所以我们只需要预处理 $1000$ 以内的次数就可以了。

- 那么怎么预处理呢？

1. 统计二进制个数（getbit）。
    ```cpp
    int getbit(int x){
      int ans=0;
      while(x){
          if(x&1)++ans;
          x>>=1;
      }
      return ans;
	}
    ```
    如上述代码，$x$ 与 $00\dots01$ 进行与运算，$x$ 的最后一位为 $1$ 才返回 $1$，不断将 $x$ 右移，判断 $x$ 有效位数的 $1$ 的个数。
    
2. 统计操作次数

递推难以理解？我们用递归看。

```cpp
    int get_cnt(int x){
	if(x==1) return 0;//如果是1 ，那么不需要进行转换操作
	return get_cnt(getbit(x))+1;
    //如果是其他数，我getbit得到的本身就是个十进制表示数字，递归获取他的值即可
    //操作一次加一次，如代码所示
    }//获取操作次数
```
 有了上述两个函数，我们的预处理迎刃而解，在主函数里枚举 $0 \sim 1000$ 这些数字的对应操作次数，在数位 DP 板子中直接进行判断即可。
 
 ## 注意事项
1. 特判
 
 看楼下只给出了特判没说为什么，这里给出逻辑思考链。
 
- 因为我们预处理时直接读入了 $num$ 数组，其实已经处理了一次，所以现在实际上要数位 DP 判断的操作次数为 $k-1$。
 
-  $k$ 为 $0$ 时需要 $dp$ 数组为负数，显然无实际意义，特判输出。
 
-  $k$ 为 $1$ 时需要 $dp$ 数组为 $0$，但是 $1$ 的操作次数为 $0$，两者矛盾，特判减去 $1$ 的影响。

2. 分享一点我关于数位 DP 维度设置的理解。

	数位 DP 很板，真的很板（~~所以各种题紫掉绿紫掉蓝~~）（~~虽然还是不会做~~）。
    
    它的状态设置一般都是四个上述维度，但是关于 $flag$ 和 $zero$，只需在存读 $dp$ 数组，终止返回时特判就可以代替维度产生的影响！
    
 	实际意义的理解：
    
  -  $flag$ 为 $0$ 时才可以记录答案，$flag$ 为 $1$ 时有限制，需要单独进行枚举。
  - $zero$ 为 $1$ 代表有前导零，前导零无效，进行统计时 $zero$ 为 $0$ 时才可以使用。
  
3. 输入时注意字符串和 $num$ 数组的存储数据是刚好相反的。
  
 ## 完整代码
 
```cpp
   //二进制数组上的数位dp
  #include<iostream>
  #include<cstring>
  using namespace std;
  const int N=1005;
  const int mod=1e9+7;
  #define ll long long 
  string s;
  ll k;

  int getbit(int x){
      int ans=0;
      while(x){
          if(x&1)++ans;
          x>>=1;
      }
      return ans;
  }//获得十进制数的二进制表达中的1的个数（十进制输出）

  int get_cnt(int x){
      if(x==1) return 0;
      return get_cnt(getbit(x))+1;
      //如果是其他数，我getbit得到的本身就是个十进制表示数字，递归获取他的值即可
      //操作一次加一次，如代码所示
  }//获取操作次数

  ll num[N];
  //存二进制数组
  ll dp[N][N],f[N];
  //dp代表到第pos位置时，已经枚举了j个1，此时这个数所能拆分的最多的1的个数
  //f存一个二进制中含i个1时的操作次数（至于个数有关，只存个数）
  ll DFS(int pos,int sum,bool flag,bool zero){//看二进制是否符合
      //sum代表当前的1的数量
      if(!pos)
          return (!zero)&&(f[sum]+1==k);//满足就算是有一个数啦！
      if(!zero&&!flag&&dp[pos][sum]!=-1)
          return dp[pos][sum];
      ll cnt=0,max_num=1;
      if(flag)max_num=num[pos];
      //num里存的不再是十进制数字，而是二进制的01
      //上界使我们第一次求出来的num数组，如果上一个数位没限制，可以取最大1
      //如果有限制，那么我只能取上界对应位置的数及其往下了
      for(int i=0;i<=max_num;i++){
          cnt+=DFS(pos-1,sum+(i==1),flag&&(i==max_num),zero&&(i==0));
          cnt%=mod;
      }
      if(!zero&&!flag)dp[pos][sum]=cnt;
      return cnt;
  }

  int main(){
      memset(dp,-1,sizeof dp);
      cin>>s>>k;
      int len=s.length();
      for(int i=0;i<len;i++){
          num[len-i]=s[i]-'0';
      }//初始化num数组，要特别注意字符串和数位数组的存储顺序问题
      //因为已经算是预先处理了一次，所以后续判断方案数时要+1
      if(k==0){
          cout<<1;return 0;
      }//0次操作？本身就是1
      for(int i=1;i<=1000;i++){
          f[i]=get_cnt(i);//预处理1000以内需要操作的次数
      }
      ll ans=DFS(len,0,1,1);
      if(k==1)ans--;//如果k==1，那么f[1]+1==1会被误判，特殊处理
      cout<<ans;
      return 0;
  }

```

 完结撒花！

 是第一篇题解，感谢冷门的数位 DP 给我这次机会（激动）（鞠躬）。

 求过求过求过 qvq。
 
 格式真的没再错了！！！！



---

## 作者：qwaszx (赞：2)

首先一次操作一定会把$n$变成$\log$级别，对于$2^{1000}$最多会变成$1000$

然后我们预处理出$1000$以内每个数变成$1$的最小次数$f[i]$，显然所有$f[i]=k-1$的$i$是可能的变换后结果.这样子我们就只需要算出$1$到$n$中有多少个数含有$i$个$1$.

这个就是一个简单的数位dp.从高往低考虑，如果当前位填的数达到限制那么就要继续算剩下的，如果没达到限制那么后面怎么填都可以，拿个组合数算一下就好了.

特判一下$k=1$和$k=0$的情况.

$O(\log^2 n)$

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int mod=1e9+7;
int f[2000],k,c[1005][1005];
char st[2000];
int count(int x){int ans=0;for(;x;x-=x&-x)++ans;return ans;}
void make()
{
    c[0][0]=1;
    for(int i=1;i<=1000;i++)
    {
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++)c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
    }
}
int main()
{
    make();
    scanf("%s",st+1);
    int len=strlen(st+1);
    scanf("%d",&k);if(k==0){puts("1");return 0;}
    f[1]=0;for(int i=2;i<=1000;i++)f[i]=f[count(i)]+1;//预处理
    int ans=0;if(k==1)--ans;
    for(int i=1;i<=1000;i++)
        if(f[i]==k-1)
        {
            int t=i;
            for(int j=1;j<=len&&t>=0;j++)
                if(st[j]=='1')ans=(ans+c[len-j][t])%mod,--t;//这一位填0和这一位填1的影响
            if(t==0)++ans;//上面算的是<n的答案 如果n也满足就再+1
        }
    cout<<ans<<endl;
}

---

## 作者：JimmyLee (赞：1)

# 题意

> 定义 $\operatorname{popcount}(x)$ 为 $x$ 二进制下 $1$ 的个数。
> 
> 定义对 $x$ 的一次操作：$x\gets\operatorname{popcount}(x)$，显然任意正整数经过若干次操作后会变为 $1$。
>
> 给定 $n$ 和 $k$，其中 $n$ 是在二进制下被给出，求出所有不大于 $n$ 且将其变为 $1$ 的最小操作次数为 $k$ 的数的个数对 $10^9+7$ 取模的结果。

# 分析

因为 $n<2^{1000}$，所以数 $x(x<n)$ 经过 $1$ 次操作后得到的 $x'\leq1000$。

所以我们可以预处理 $[2,1000]$ 中的数变成 $1$ 的最少操作次数。

考虑在二进制下使用数位 dp 解决。

定义 $dp_{n,i,v}$ 为目前搜索至第 $n$ 位，该位之前有 $i$ 个 $1$，上一位填的是 $v$ 的满足题意的数的个数。

记忆化搜索即可，时间复杂度 $O(\log^2n)$。

[AC 记录](https://codeforces.com/contest/914/submission/278595979)

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define maxn 1003
#define popc __builtin_popcount
#define mod 1000000007

int ks[maxn];

void init()
{
    for(int i=2;i<=1000;i++)
        ks[i]=ks[popc(i)]+1;

}

string s;
bitset<maxn> bs;
int dp[maxn][maxn][2], k;

int dfs(int n, int cnt=0, bool la=0, bool lim=1)
{
    if(!lim&&~dp[n][cnt][la]) return dp[n][cnt][la];
    if(!n) return cnt==1&&la?0:cnt&&ks[cnt]==k-1;
    int ret=0, up=lim?bs[n]:1;
    for(int i=0;i<=up;i++)
        ret=(ret+dfs(n-1, cnt+i, i, lim&&i==up))%mod;
    if(!lim) dp[n][cnt][la]=ret;
    return ret;
}

int main()
{
    init();
    memset(dp, -1, sizeof dp);
    cin>>s>>k;
    if(k==0) return cout<<1, 0;
    for(int i=0;i<s.size();i++)
        bs[s.size()-i]=s[i]^48;
    cout<<dfs(s.size());
}
```

---

## 作者：carp_oier (赞：1)

# advertisement

这位靓仔，你都来看我的题解了，为什么不来我的[我的博客](https://www.cnblogs.com/carp-oier/p/17747674.html)看看呢。

# prologue

模拟赛的一道题，结果没做出来，丢大人，败大兴。所以过来糊一篇题解。

# analysis

我们看到数据范围这么大，那么肯定不可以一个一个遍历（废话），所以就要考虑这个题目的性质。

我们先假设，极端数据 $2 ^ {1000} - 1$，这个数字中包含了 $999$ 个 1（~~正好感冒了能不能让我喝了~~）。下一次的数据就是 $999$，这个时候，$999$ 的二进制表示为 $11 1110 0111$，下次就是 $8$，再下次就是 $1$ 了。这个时候的最少变换次数是 $3$。

我们看到这个数据缩小是很快的。那我们再进一步研究观察。

由于上限原因，所以我们第一次变换之后的数字一定为 $\le 1000$ 的数字。我们又知道（不知道的掏计算器） $2 ^ {10} = 1024$ 已经大于 1000 了，为了方便统计，适当放大数据。下次需要进行操作的数字就变成了 $ [0, 10] $ 就更小了，这个时候手搓一下，发现 $7$ 这个数据是 $[0, 10]$ 之间的二进制表示下包含 1 最多的一个数字。

我们就求出来了这个恰好变换次数的上限。对于 100% 的数据而言，一定有：
1. $2 \le k \le 5$ 有解。
2. $k > 5$ 无解。

这个时候特判两个情况：
1. $k = 1$ 时，答案的个数为 $length_s - 1$。
2. $k = 0$ 时，答案为 1（只有 1 这种情况）。

我们之后就去考虑怎么计算这个值。

我们可以考虑一种类似于数位 dp 的思想，从高位往低位，用 $f[i][j]$ 表示已经填了 i 个 1，剩下 j 位随便填，并且恰好 k 次变换之后能够变成 1 的方案数。

考虑递推式，从定义出发，预处理出来可能的值：

$$f[i][j] \gets f[i - 1][j]$$
$$f[i][j] \gets f[i][j] + f[i - 1][j + 1],  (j \le n - 1) $$

计算方案数量：

$$res \gets (res + f[n - i - 1][t + 1]) \bmod P$$

注意，如果我们最后的这个数字符合我们的最后变换数量少一，就是最后可以变到 1，我们要给方案数加 1。

# code time

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define rl register ll 
#define endl '\n'

const ll N = 1010, P = 1e9 + 7;

char ch[N];

ll n, m, g[N], f[N][N];

int main()
{
    scanf("%s%lld", ch, &m);
    
    n = strlen(ch);
    
    if(m == 0) puts("1");
    else if(m == 1) cout << n - 1 << endl;
    else if(m > 5) cout << "0" << endl;
    else 
    {
        for(rl i=2; i <= 1000; ++ i)
        {
            ll cnt = 0;
            for(rl j=i; j; j >>= 1)
                if(j & 1) cnt ++; 
                
            g[i] = g[cnt] + 1;
        }
        
        for(rl i=1; i <= n; ++ i) f[0][i] = g[i] == m - 1;
        for(rl i=1; i <= n; ++ i)
            for(rl j=0; j <= n; ++ j)
            {
                f[i][j] = f[i - 1][j];
                if(j + 1 <= n) f[i][j] = (f[i][j] + f[i-1][j + 1]) % P;
            }
            
        ll res = 0, t = 0;
        for(rl i=0; i < n; ++ i)
            if(ch[i] == '1')
            {
                res = (res + f[n - i - 1][t]) % P; t ++ ;
            }
            
        if(g[t] == m - 1) cout << res + 1 << endl;
        else cout << res << endl;
    }
    return 0;
}
```

---

## 作者：LiRewriter (赞：1)

首先，我们发现一个性质：由于这个数是小于$2^{1000}$的，所以在第一次的变化之后结果一定是小于1000的。

因此，我们可以想到预处理出来1000以内的数需要多少次变化，而这一过程可以递推求解：$f[i] = f[getbit(i)] +1$，其中getbit()是用来求出一个数二进制下有多少位是1的：

```cpp
inline int getbit(int x) {
    int ans = 0;
    while(x) {
        if(x & 1) ++ans;
        x >>= 1;
    }
    return ans;
}
```
然后呢？现在的问题集中在，如果给定$i$，如何求出比$i$小并且位数的dp值是$k - 1$的，也就是变化之后只需要$k - 1$次。

不妨讨论一下如果某个位是0，那么我们就可以忽略它，而如果某个位是1，那么它之后的每个值全部可以变，前提是只需要它变成0。

所以，我们发现，对于第pos位来说，假如前面有$m$个位是1：

$ans += \sum ^{i = m} _ n C_{n - pos}^{i - m} \cdot [dp[i] == k-1]$

这是因为，对于某个确定的位置，如果前面的部分已经全部确定，那么后面的部分就可以自由选择了。所以，后面的就可以用组合数去求！

还有一个问题，就是为什么我们只考虑某一位变成0后面的随意改变的情况。这是因为，这一位是1的情况我们在对这位之前的东西进行求解的时候已经处理过了。

而组合数怎么求？用递推法预处理：$C_m^n = C_{m - 1}^{n - 1} + C_{m} ^{n - 1}$。

还有三个特例需要注意：

如果1的位数的dp值恰是$k - 1$，那么结果还要加1。这是因为我们在枚举的时候已经忽略的第一位的情况，所以现在要再考虑进来。

如果$k = 0$，那么结果是0，因为1不在答案里。

如果$k = 1$，那么结果要-1，也是因为1不在答案里。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define LL long long
const LL MOD = (LL)1e9+7;
LL k, C[1003][1003], dp[1003], cnt, num;
string str;
inline int getbit(int x) {
    int ans = 0;
    while(x) {
        if(x & 1) ++ans;
        x >>= 1;
    }
    return ans;
}
int main() {
    cin>>str>>k;
    if(!k) return puts("1"), 0;
    for(int i = 0; i <= 1000; ++i)
        C[i][0] = 1;
    for(int i = 1; i <= 1000; ++i) {
        for(int j = 1; j <= 1000; ++j)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    dp[1] = 0;
    for(int i = 2; i <= 1000; ++i)
        dp[i] = dp[getbit(i)] + 1;
    int N = str.size();
    for(int i = 0; i < N; ++i) {
        if(str[i] == '0') continue;
        for(int j = max(1LL, cnt); j < N; ++j) {
            if(dp[j] == k - 1) {
                num = (num + C[N - 1 - i][j - cnt]) % MOD;
            }
        }
        ++cnt;
    }
    if(k == 1) --num;
    if(dp[cnt] == k - 1) num = (num + 1) % MOD;
    cout<<num<<endl;
    return 0;
}
```

---

感觉是很精妙的思想...原来这个就是数位DP吗（x


---

## 作者：Yoimiyamwf (赞：0)

# 题意
给定二进制数 $n$，求区间 $[1,n]$ 内**至少**经过 $k$ 次连续的 $\operatorname{popcount}$ 操作（求二进制下数位 $1$ 的个数）后所得结果为 $1$ 的数的个数。

# 分析
由于 $1\le n \le 2^{1000}$，显然不能暴力查找，考虑用数位 dp 解决。

首先对于 $k\le1$ 的特殊情况，不难发现当 $k=0$ 时符合条件的数仅有 $1$，当 $k=1$ 时符合条件的数为 $n$ 以内所有 $2$ 的幂数，其数量即为二进制数 $n$ 的位数，因此这两种情况直接特判即可。

对于 $k\ge2$ 的情况，注意到对于任意 $n \in [1,2^{1000}] , \operatorname{popcount}(n)\le1000$，因此第一次操作用数位 dp 解决，剩下几次可直接预处理出变为 $1$ 的最小次数。

设 $f_i$ 为 $i$ 变为 $1$ 至少经过的操作数，显然有

$$f_i=f_{\operatorname{popcount}(i)}+1$$

数位 dp 部分，我们只需要当前位数、已填入的 $1$ 的个数和是否有限制三个状态，直接套板子即可。

# 代码
```cpp
#include <bits/stdc++.h>
#define in inline
#define rint register int
#define r(a) runtimerror(a)
#define w(a) wronganswer(a)
#define wl(a) wronganswer(a),putchar('\n')
#define ws(a) wronganswer(a),putchar(' ')
#define mod 1000000007
using namespace std;
typedef long long ll;
string s;
int n,len,f[1010][1010],t[1010];
bool can[1010];
template <typename t> void wronganswer(t a){
	if(a<0) putchar('-'),a=-a;
	if(a>9) wronganswer(a/10);
	putchar(a%10^48);
}
template <typename t> in void runtimerror(t &a){
	char ch=getchar();
	t x=1,f=0;
	while(!isdigit(ch)){
		if(ch=='-') x=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		f=(f<<3)+(f<<1)+(ch^48);
		ch=getchar();
	}
	a=x*f;
}
int dp(int pos,int now,bool lim){
	if(pos==len) return t[now]+1==n;
	if(!lim&&~f[pos][now]) return f[pos][now];
	int ans=0;
	ans=dp(pos+1,now,lim&&s[pos]=='0')%mod;
	if(!lim||s[pos]=='1') ans=(ans+dp(pos+1,now+1,lim&&s[pos]=='1'))%mod;
	return f[pos][now]=ans;
}
in void dp(){
	memset(f,-1,sizeof(f));
	for(rint i=2;i<=len;i++){
		t[i]=t[__builtin_popcount(i)]+1;
	}
	w(dp(0,0,true));
}
int main(){
	cin>>s;
	r(n);
	len=s.length();
	if(n==0) putchar('1');
	else if(n==1) w(len-1);
	else dp();
	return 0;
}
```


---

## 作者：lmy_2011 (赞：0)

### 首先说明
本文思路借鉴了[此](https://blog.csdn.net/weixin_30256901/article/details/95834918?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167079724216800213078487%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=167079724216800213078487&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-4-95834918-null-null.142^v68^control,201^v4^add_ask,213^v2^t3_control2&utm_term=CF914C&spm=1018.2226.3001.4187)文章。
### 算法思想
这题一看到，发现他不求中间过程，只求方案数，是一道数位动态规划。
### 题目思路
#### 状态
因为 $n$ 在二进制下长度最大为 $1000$，所以最多有 $1000$ 个 $1$，所以转化一次最多是 $1000$。

所以我们可定义状态：$dp_{i,j}$ 表示前 $i$ 位小于 $(dp_{i,j})_2$ 而且 $1$ 的个数为 $j$ 的总数。
#### 状态转移方程
我们先循环枚举 $(dp_{i,j})_2$ 中的每一位，再将当前的这一位分类讨论：

- 如果是 $1$，则我们再定义组合数 $C_{j}^{i-1}$，$dp_{i,j}$ 就是他的左上角 $dp_{i-1,j-1}$ 加上 $C_{j}^{i-1}$，所以状态转移方程就是：
$$dp_{i,j}=dp_{i-1,j-1}+C_{j}^{i-1}$$
- 如果是 $0$，就是他的上一位，状态转移方程就是：
$$dp_{i,j}=dp_{i-1,j}$$

#### 边界条件
我们要按照 $x$ 的第一位进行分类讨论：
- 是 $1$，$dp_{1,0}$ 与 $dp_{1,1}$ 均设为 $1$。
- 是 $0$，$dp_{1,1}$ 设为 $1$，而 $dp_{1,0}$ 要设为 $0$。

---

## 作者：Yukinoshita_Yukino (赞：0)

给定一个小于 $2^{1000}$ 的数 $n$ ，记把原数二进制下的 $1$ 的个数赋值给原数为一次操作，求小于这个数且操作 $k$ 之后结果为 $1$ 的数的个数。

操作使原数下降速度很快，考虑人工剥掉一层。

预处理 $1000$ 以内的数的操作次数即可。

考虑简单的递推

```cpp
dp[i]=dp[get(i)]+1;
```

其中 ```get(i)``` 为求整数 $i$ 的二进制下 $1$ 的个数。

接下来我们就要求 $1000$ 内操作次数为 $k-1$ ，且原数小于 $n$ 的数的个数。

用组合数算一下即可。

然后注意一下特判 $k=1$ , $k=0$ 的情况。~~太毒瘤了~~


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int maxn=1010;
char str[maxn];
int k,C[maxn][maxn],f[maxn];
int get(int num){
	int ans=0;
	while(num) 
	{
		if(num&1) ans++;
		num>>=1;
	}
	return ans;	 
}
void init()
{
	int n=1001;
	for(int i=0;i<=n;i++) C[i][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	f[1]=0;
	for(int i=2;i<=n;i++)
	{
		f[i]=f[get(i)]+1;
	}
}
signed main()
{
	scanf("%s",&str);
	cin>>k;
	if(k==0)
	{
		cout<<1;
		return 0;
	}
	init();
	int ans=0,m=0;
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]=='0') continue;
		for(int j=(m==0?1:m);j<strlen(str);j++)
		{
			if(f[j]==k-1) 
			{
				ans+=(C[strlen(str)-i-1][j-m]%mod);
				ans%=mod;
			//	cout<<strlen(str)-i-1<<' '<<j-m<<' '<<C[strlen(str)-i-1][j-m]<<endl;
			}
		}
		m++;
		ans%=mod;
		//cout<<ans<<' '<<m<<endl;
	}
	if(k==1) ans--;

	if(f[m]==k-1) ans++;
	cout<<ans;
	return 0;
 } 

```

---

## 作者：弦巻こころ (赞：0)

~~被特判恶心死的我23333~~

其实并没有紫题那么难,也不需要用数位dp.只需要用组合数+枚举就能解决问题了.  毕竟CF评分才1800~~(你谷恶评现象.)~~

因为在一次操作内,我们可以将数转化为1000以内,所以我们先预处理1000以内的数,然后我们可以思考这样一个问题.如果我们可以转化为,每个 操作数为k-1的数.如果我们当前不计超出当前值的数.就相当于n个数里取tot个1.我们答案就为C[n] [tot] (tot为这个数的值)当然tot要小于n.

然后,我们发现会有超出当前值的数,我们可以采用容斥的思想,枚举每个位数,如果他为0,说明它一定是不合法的,我们就减去不合法的数,不合法的数就相当于在n-j个数里取tot-(num[j]+1)个数,
个数就为 C[n-j] [tot-(num[j]+1)] (j为当前位数 num[j]为前缀和.)

对于每个 操作数为k-1的数,我们先储存一下.然后,对于每个数.我们进行一次O(n)的操作,就查找为0的位置,再按上述操作用答案减去 C[n-j] [tot-(num[j]+1)] 就行了.注意C[0] [0] 也为1.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
char s[10005];
long long C[1015][1015];
long long f[1005]; 
long long tot[1005];
long long ch[1005];
long long num[1005];
long long n,k,ans,kreal;
void Calc(int n)
{
	C[0][0]=1;//C[0][0]也为1 
	C[1][1]=1;
	C[1][0]=1;
	for(int i=2;i<=n;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
		{
			C[i][j]=C[i-1][j-1]+C[i-1][j];
			C[i][j]%=mod;
		}
	}
}
long long Pow(long long a,long long b)
{
	long long ans=1,base=a;
	while(b)
	{
		if(b&1) ans*=base,ans%=mod;
		base*=base;
		b>>=1;
	}
}
int main()
{
	Calc(1005);
	f[1]=0;
	scanf("%s%d",s+1,&k);
	
	int n=strlen(s+1);
	for(int i=1;i<=n;i++)
	{
		kreal*=2;
		if(s[i]=='1')
		{
			kreal++;
			num[i]++;
		
		}
		num[i]+=num[i-1];
		if(kreal>=1000)
		{
			kreal=1001;
		}
	}
	if(kreal>=1000)
	{
		kreal=1001;
	}
	for(int i=2;i<=1000;i++)
	{
		int num=__builtin_popcount(i);
		f[i]=f[num]+1;
	}
	for(int i=1;i<=min(kreal,1000ll);i++)
	{
		if(f[i]==k-1)
		{
			tot[++tot[0]]=i;
		}
		if(f[i]==k)
		{
			ans++;
		}
	}
	if(kreal<=1000)
	{
		cout<<ans;
		return 0;
	}
//	ans=Pow(2,n);
	if(k==0)//特判k等于0的时候输出1
	{
		cout<<1;
		return 0;
	}
	ans=0;
	for(int i=1;i<=tot[0];i++)
	{
		if(n>=tot[i])
		{
			ans+=C[n][tot[i]];
			ans%=mod;
		}else
		{
			break;
		}
		for(int j=1;j<=n;j++)
		{
			if(s[j]=='1')
			{
				continue;
			}
			if((num[j]+1)<=tot[i])
			{
				
				ans-=C[n-j][tot[i]-(num[j]+1)];
				ans=(ans+mod)%mod;
			}else
			{
				break;
			}
		}
		
		
		ans=ans; 
	}
	if(k==1)//k等于1的时候会取到1然而实际上并没有...
	{
		ans--;
	} 
	cout<<(ans+mod)%mod<<endl;
	return 0;
}
```



---

