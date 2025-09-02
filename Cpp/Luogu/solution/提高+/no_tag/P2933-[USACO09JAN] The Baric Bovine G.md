# [USACO09JAN] The Baric Bovine G

## 题目描述

为了研究农场的气候，Bessie 帮助农夫 John 做了  $N$ 次气压测量并按顺序记录了结果  $M_1 \cdots M_n$。Bessie 想找出一部分测量结果来总结一整天的气压分布。她想用  $K(1 \leq K \leq N)$ 个数  $s_j (1 \leq s_1 < s_2 < \cdots < s_K \leq N)$ 来概括所有测量结果。她想限制如下的误差: 对于任何测量结果子集，每一个非此子集中的结果都会产生误差。总误差是所有测量结果的误差之和。更明确地说，对于每一个和所有  $s_j$ 都不同的  $i$：

- 如果  $i$ 小于  $s_1$, 误差是： $2 \times | M_i - M_{(s_1)} |$；
- 如果  $i$ 在  $s_j$ 和  $s_{(j+1)}$ 之间，误差是： $| 2 \times M_i - \operatorname{Sum}(s_j, s_{(j+1)}) |$。注： $\operatorname{Sum}(x, y) = M_x + M_y$  ( $M_x$ 和  $M_y$ 之和)；
- 如果  $i$ 大于  $s_K$ ,误差为： $2 \times | M_i - M_{(s_K)} |$ 给出最大允许的误差  $E$，找出最小的一部分结果使得误差最多为  $E$。

## 说明/提示

对于所有数据， $1 \leq N \leq 100$， $1 \leq M_i \leq 1,000,000$， $1 \leq E \leq 1,000,000$。

### 样例说明

Bessie 做了 4 次测量，最大允许的误差是 20。测量的结果分别为 10，3，20 和 40。

选择第二次和第四次测量结果是最佳的，误差为 17。第一个结果的误差为  $2\times|10-3|=14$，第三个的为  $|2\times20-(3+40)|=3$。

## 样例 #1

### 输入

```
4 20 
10 
3 
20 
40 
```

### 输出

```
2 17 
```

# 题解

## 作者：ccsc (赞：4)

题目大意:
>给你一个集合，告诉你如何判定它的子集是否合法并让你找到一个最优子集

解法：

首先我们预处理出一个数组ero，$ero[i][j]$保存在i到j之间元素对误差的贡献，即我们枚举$k(j-1>=k>=i+1)$，计算$abs(2*m[z]-m[i]-m[j])$

特殊的是，我们还需要处理出$ero[i][0]$和$ero[i][n+1]$，分别表示在i之间和在i之后的元素的各种误差

考虑如何DP

定义$DP[i][j]$表示前j个元素，必选第j个元素，总共选择了i个产生的最小误差。为什么把i放在前，j放在后呢？
>因为我们首先最小化的是子集的大小。

状态转移方程就是：

$dp[i][j]=min(dp[i][j],dp[i-1][q]+sum)(i-1<=q<=j)$

我们有$sum=-pre[q][n+1]+pre[q][j]+pre[j][n+1]$（之前我们是把q当成是子集的结尾并加上了它之后对误差的贡献，于是此时我们减去这个值改为用j来作为最后一个元素）

**注意**
>i=1的情况必须我们提前处理出来才可以

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,e;
long long m[110],ero[110][110],dp[110][110];
//ero选i和j产生的误差
//dp以j结尾的时候，有i个最少测量数目 能达到的最小误差 
long long abss(long long a)
{
    if(a<0)return -a;
    return a;
}
int main()
{
    int i,j,k;
    scanf("%d%d",&n,&e);
    for(i=1;i<=n;i++)scanf("%lld",&m[i]);    
    long long ans=n,anss=999999999;
    for(k=1;k<=n;k++)//计算误差 
    {
        for(i=k+1;i<=n;i++)
            for(j=k+1;j<=i-1;j++) /*枚举题中的i*/ 
				ero[k][i]+=abss(2*m[j]-m[i]-m[k]);//误差 计算---情况一 
            
        for(i=1;i<k;i++) ero[k][0]+=2*abss(m[i]-m[k]); //误差 计算---情况二 
        for(i=k+1;i<=n;i++) ero[k][n+1]+=2*abss(m[i]-m[k]);// 误差 计算---情况三 
    }
    for(i=1;i<=n;i++) //处理只取一个数的情况，也就是只取数i的情况 预处理 
    {
        dp[1][i]=ero[i][0]+ero[i][n+1]; 
        if((dp[1][i]<=e) && (dp[1][i]<anss))
        {
            anss=dp[1][i];ans=1;
        }
    }
    
    if(ans==1){printf("%lld %lld\n",ans,anss);return 0;}
    
    for(k=2;k<=n;k++)//最少能达到误差小于等于E的测量数目
        for(i=k;i<=n;i++)//枚举结尾的数 
        {
            dp[k][i]=0x7fffffff;
            for(j=k-1;j<i;j++)//枚举上一轮的结尾数 
            {
                long long err=ero[j][i]+ero[i][n+1]-ero[j][n+1]; //相比上一轮多的误差 
                dp[k][i]=min(dp[k][i],dp[k-1][j]+err);
            }
            if((dp[k][i]<=e)&&(dp[k][i]<anss)&&(k<=ans))
				anss=dp[k][i],ans=k; 
        }
    printf("%lld %lld",ans,anss);
	return 0;
}
```


---

## 作者：巨型方块 (赞：3)

先预处理

g[i][j]表示i-1点选和j+1点选，i~j这段区间的值

然后n^3dp

f[i][j]表示i点选了，总共选了j个的最小方案数

                    
```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const Ll N=105;
Ll a[N],f[N][N],g[N][N];
Ll n,m;
int main()
{
    scanf("%lld%lld",&n,&m);
    for(Ll i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(Ll i=0;i<=n+1;i++)
        for(Ll j=i+1;j<=n+1;j++)
            for(Ll k=i+1;k<=j-1;k++)
                if(i==0)g[i+1][j-1]+=abs(a[k]*2-a[j]-a[j]);else
                if(j==n+1)g[i+1][j-1]+=abs(a[k]*2-a[i]-a[i]);else
                    g[i+1][j-1]+=abs(a[k]*2-a[j]-a[i]);
    memset(f,63,sizeof f);
    f[0][0]=0;
    for(Ll i=0;i<=n;i++)
        for(Ll j=0;j<=n;j++)
            if(f[i][j]<=m)
            {
//                cout<<i<<' '<<j<<' '<<f[i][j]<<endl;
                for(Ll k=i+1;k<=n+1;k++)
                    f[k][j+1]=min(f[k][j+1],f[i][j]+g[i+1][k-1]);
            }
    for(Ll i=2;i<=n+1;i++)
        if(f[n+1][i]<=m){
            printf("%lld %lld",i-1,f[n+1][i]);
            return 0;
        }
}
```

---

## 作者：钛战机 (赞：3)

这题仔细想一想会发现，选的数越少，造成的误差就越大（和现实经验也相符）

继而发现，哇，符合最优子结构，假设要选i个数，那肯定可以从选i-1个数的情况中再取一个。具体哪一个？DP来决策。

预处理一个s数组，s[i,j]表示在[i,j]这个区间下，只取i,j造成的误差。多处理一组s[0,i]和s[i,n+1]分别表示在这个区间中，0~i-1和i+1~n全都不取的误差。


-  顺着题目想，以取多少数为状态，那么可以设f[i,j]表示前j个数,一定取j的情况下，取了i个数造成的误差。
- 可以得到状态转移方程
```
f[i,j]:=min{f[i-1,k]+s[k,j]}    (f[i,j]<=e，i-1<=k<j)
```
- 当然可以故意砸自己的脚（我），比如逆着题目想，以删了多少数为状态，设f[i,j]为前i个数，一定取i的情况下删了j个数造成的误差（风格和上面不大一样不过不影响啦）
- 但是这样更加复杂，因为在枚举k的过程中，s[k,i]的区间长度是在不断变化的，也就是这部分删去的数在不断变化，那么就不能用f[i-1,k]这么简单地来表示了

- 方程

```
     f[i,j]:=min{f[k,j-(i-k-1)]+s[k,i]}  (f[i,j]<=e,i-j-1<=k<=i-1)

```
- 为什么是这个鬼样在纸上画画就知道了

附第二种想法代码
```pascal
var
        i,j,k,n,e:longint;
        a:array[0..101]of longint;
        f,s:array[0..101,0..101]of longint;
begin
        fillchar(f,sizeof(f),$7);
        readln(n,e);

        for i:=1 to n do
         readln(a[i]);
        for i:=1 to n-2 do
         for j:=i+2 to n do
          for k:=i+1 to j-1 do
           s[i,j]:=s[i,j]+abs(2*a[k]-(a[i]+a[j]));
        for i:=2 to n do
         for j:=1 to i-1 do
          s[0,i]:=s[0,i]+2*abs(a[j]-a[i]);
        for i:=n-1 downto 1 do
         for j:=i+1 to n do
          s[i,n+1]:=s[i,n+1]+2*abs(a[j]-a[i]);//初始化s
          
        for i:=0 to n+1 do
        begin
                f[i,0]:=0;
                f[0,i]:=0;
        end;
        for j:=1 to n-1 do
        begin
                for i:=j+1 to n+1 do
                begin
                        if (s[0,j+1]<f[i,j])and(s[0,j+1]<=e) then f[i,j]:=s[0,j+1];
                        for k:=i-j-1 to i-1 do
                        begin
                                if (f[k,j-(i-k-1)]+s[k,i]<f[i,j])and(f[k,j-(i-k-1)]+s

[k,i]<=e)
                                then f[i,j]:=f[k,j-(i-k-1)]+s[k,i];
                        end;
                end;

                if f[n+1,j]=117901063 then break;//新状态都不可行了退出即可
        end;
        if f[n+1,j]=117901063 then writeln(n-j+1,' ',f[n+1,j-1])
                            else writeln(n-j,' ',f[n+1,j]);

end.

```


---

## 作者：Tang_chao (赞：1)

## P2933 [USACO09JAN] The Baric Bovine G 题解

有一个显然的动态规划。由于 $E$ 较大，考虑设 $f_{i,k}$ 为前 $i$ 个记录选 $k$ 个，最后一个为 $i$ 的最小误差。可以假设第 $n+1$ 个为代价也为 $1$ 的必选项。

- 初始化：$f_{0,k}$ 全为 $0$，其余全为无限大。
 
- 转移方程：$f_{i,k} = \min{f_{j,k-1} + \operatorname{cal}(j + 1,i - 1,x_j,x_i)}\,\,(0 \le j < i)$，  
其中 $\operatorname{cal}(l,r,a,b)$ 为 $[l,r]$ 区间内左边最近的记录是 $a$，右边最近的记录是 $b$ 的误差和。可以暴力算。
 
- 答案：设第一个答案为 $mnK$，则要找到最小的 $mnK$ 满足 $f_{n+1,mnK} \le E$，第二个答案为在此基础上 $f_{n+1,mnK}$ 的最小值。输出时记得减 $1$。

没了。  
时间复杂度 $O(n^4)$，但是跑不满，还是可以创过去的。代码很简短。

代码变量名可能和原题有所出入，见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 109
int n,m,ansK = 1e18,ansS = 1e18,x[N],f[N][N];
int cal(int l,int r,int a,int b){
	int sum = 0;
	for(int i = l;i <= r;i++)
		if(a == 0) sum += 2 * abs(x[i] - b);
		else if(b == 0) sum += 2 * abs(x[i] - a);
		else sum += abs(2 * x[i] - a - b);
	return sum;
}
signed main(){
	cin>>n>>m;
	for(int i = 1;i <= n;i++) cin>>x[i];
	for(int i = 1;i <= n + 1;i++)
		for(int k = 0;k <= i;k++){
			f[i][k] = 1e18;
			if(!k) continue;
			for(int j = 0;j <= i - 1;j++){
				f[i][k] = min(f[i][k],f[j][k - 1] + cal(j + 1,i - 1,x[j],x[i]));
				if(i == n + 1 && k != 1 && f[i][k] <= m){
					if(ansK > k) ansK = k; 
					if(ansK == k) ansS = min(ansS,f[i][k]);
				}
			}
		}
	cout<<ansK - 1<<" "<<ansS<<endl;
}
```

---

## 作者：hzoi_liuchang (赞：1)

### 分析
这一道题是一道DP题

我们设$f[i][j]$为前$i$个数中已经选择了$j$个数的价值，并且处于$i$位置上的数一定选择

那么就有$ f[i][j]= \min (f[i][j],f[k][j-1]+sum[k][i]);$
其中$j-1 \leq k < i$

$sum[i][j]$为选走$i,j$位置上的数，区间$[i,j]$中的数产生的误差

这一道题要注意初始化和最后的处理

我们需要将$f[i][1]$和$f[i][i]$预处理一下

同时，当$DP$结束后，因为最右边的价值没有计算，所以我们需要把最右边的价值加上

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=105;
int n,vis[maxn],jud;
ll e,a[maxn],sum[maxn][maxn],f[maxn][maxn];
int main(){
    memset(f,0x3f,sizeof(f));
    scanf("%d%lld",&n,&e);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=i+1;k<j;k++){
                sum[i][j]+=abs(a[k]*2-a[i]-a[j]);
            }
        }
    }
    for(int i=1;i<=n;i++) f[i][i]=0;
    for(int i=1;i<=n;i++){
        f[i][1]=0;
        for(int j=1;j<i;j++){
            f[i][1]+=2*abs(a[i]-a[j]);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            for(int k=j-1;k<i;k++){
                f[i][j]=min(f[i][j],f[k][j-1]+sum[k][i]);
            }
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=i;j++){
            ll ans=0;
            for(int k=i+1;k<=n;k++){
                ans+=2*abs(a[k]-a[i]);
            }
            f[i][j]+=ans;
        }
    }
    int jl=n;
    ll ans=0;
    for(int i=1;i<=n;i++){
        ll now=0x3f3f3f3f3f3f3f3f;
        for(int j=i;j<=n;j++){
            now=min(now,f[j][i]);
        }
        if(now<=e){
            ans=now;
            jl=i;
            break;
        }
    }
    printf("%d %lld\n",jl,ans);
    return 0;
}
```

---

