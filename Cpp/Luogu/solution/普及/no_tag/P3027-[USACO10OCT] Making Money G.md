# [USACO10OCT] Making Money G

## 题目描述

FJ 进入了古玩生意，买卖像牛形圣诞树装饰品这样的古玩。他知道他可以卖掉他能从一个包含 $N$ 种不同牛形古玩（$1 \leq N \leq 100$）的目录中进货的每一件古玩，并且他可以根据自己的心愿购买任意数量的每种古玩。他只有 $M$ 的资金（$1 \leq M \leq 100,000$）可以投资，但希望在第一年末最大化他的利润（利润的定义稍有不同）。  古玩类型 $i$ 的购买成本为 $C_i$（$1 \leq C_i \leq 100,000$），每售出一个古玩可获得 $R_i$（$1 \leq R_i \leq 100,000$）的收入（利润为 $R_i - C_i$）。FJ 可以以任何方式混合搭配他出售的古玩。他在购买古玩时不需要花光所有的钱。  在第一年末，FJ 能获得的最大总利润是多少（利润 = 初始资金 - 所有成本 + 所有销售额）？这个数字保证小于 1,000,000,000。  考虑当 FJ 只有 3 种古玩并且开始时有 $M=17$ 的情况。以下是每种古玩的成本和收入：  | 古玩 | 成本 $C_i$ | 收入 $R_i$ | |------|-----------|-----------| | 1    | 2         | 4         | | 2    | 5         | 6         | | 3    | 3         | 7         |  在这种情况下，FJ 应该购买 5 个类型 3 的古玩，花费 15 钱，并再购买 1 个类型 1 的古玩，花费 2 钱，总共花费 17 钱。他的利润将是 $5 \times (7-3) + 1 \times (4-2) = 5 \times 4 + 1 \times 2 = 22$ 钱。根据成本和收入结构，他不能做得更好。  注意：第二个测试用例具有挑战性，但我们的答案是正确的。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3 17 
2 4 
5 6 
3 7 
```

### 输出

```
22 
```

# 题解

## 作者：Yizhixiaoyun (赞：6)

### [题目传送门](https://www.luogu.com.cn/problem/P3027)

## 前置知识

[完全背包](https://oi-wiki.org/dp/knapsack/)

[完全背包模板](https://www.luogu.com.cn/problem/P1616)

## 做法

我们做题的方法考虑**完全背包**。

找到每个物品的利润，我们发现就是 $r_i - c_i$ ,花费 $c_i$

由此推出状态转移方程：

$dp_j = \max(dp_j,dp_{j-c_i} + r_i - c_i)$

## 代码

```cpp
#include<cstdio>
using namespace std;
const int maxn=105;
int n,m,ans,c[maxn],r[maxn],dp[100005];
int max(int a,int b){if(a>b) return a;else return b;}
int main(){
	scanf("%d%d",&n,&m);
	for(register int i=1;i<=n;++i) scanf("%d%d",&c[i],&r[i]);
	for(register int i=1;i<=n;++i){
		for(register int j=c[i];j<=m;++j){
			dp[j]=max(dp[j],dp[j-c[i]]+r[i]-c[i]);
		}
	}
	for(register int i=1;i<=m;++i) ans=max(ans,dp[i]-i+m);
	printf("%d",ans);
}
```


---

## 作者：暮影灰狼 (赞：5)

完全背包问题。

读入的时候把Ci和Ri处理成纯利润（Ri-Ci）val.

dp[j]表示花费j元取得的最大利润，转移方程：

**dp[j] = Max(dp[j],dp[j-C[i]]+val[i])**

其中C[i]和val[i]对应同一个物品的成本和纯利润。

注意最后答案不是dp[M],因为这M元你可能没有全部用完，所以把dp数组扫一遍，答案是**Max(dp[i]-i+M)**。

代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>

inline void read(int &x)
{
    char ch = getchar(),c = ch;x = 0;
    while(ch < '0' || ch >'9') c = ch,ch = getchar();
    while(ch <= '9' && ch >= '0') x = x*10+ch-'0',ch = getchar();
    if(c == '-') x = -x;
}

int n,m,tmp,ans;
int w[110],val[110],dp[100005];

inline int Max(int a,int b)
{return a>b?a:b;}

int main()
{
    read(n),read(m);
    for(int i = 1;i <= n;++ i)
    {
        read(w[i]),read(tmp);
        val[i] = tmp-w[i];
    } 
    for(int i = 1;i <= n;++ i)
        for(int j = w[i];j <= m;++ j)
            dp[j] = Max(dp[j],dp[j-w[i]]+val[i]);
    for(int i = 1;i <= m;++ i)
        ans = Max(ans,dp[i]-i+m);
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：ShineEternal (赞：3)

[$My\ blog$](https://blog.csdn.net/kkkksc03)

## solution：

完全背包的好题。

每次的价值是利润（r-c），花费是c

然后套板子就行了

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int f[100005],a[105],c[105];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int r;
		scanf("%d%d",&c[i],&r);
		a[i]=r-c[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=c[i];j<=m;j++)
		{
			f[j]=max(f[j],f[j-c[i]]+a[i]);
		}
	}
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		ans=max(ans,f[i]-i+m);
	}
	printf("%d\n",ans);
	return 0;
} 
```

---

## 作者：mzyc_yang2021 (赞：1)

思路：由于题目让我们求最大利润，且物品数量无限，所以是完全背包，并且这是一道模板题。不了解的可以看[这里](https://blog.csdn.net/wumuzi520/article/details/7014830)。

方程：因为是完全背包，于是可得一个十分基础的方程：

${dp}_{j} = \max (dp_{j},dp_{ j - c_{i} } + r_{i})$

注意：唯一需要注意的是，有可能最大利润并不是花完钱得到的，所以遍历一遍数组得到答案。

下面附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100010
int n,m,ans,C[N],R[N],dp[N];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>C[i]>>R[i];
		R[i]=R[i]-C[i];
	}
	for(int i=1;i<=n;i++)
	for(int j=C[i];j<=m;j++)
		dp[j]=max(dp[j],dp[j-C[i]]+R[i]);
	for(int i=1;i<=m;i++) ans=max(ans,dp[i]-(i-m));
	cout<<ans;
}
```

做完这道题，建议看看[这道题](https://www.luogu.com.cn/problem/P1853)，比较基础，但是有坑，可以练练手。

---

## 作者：NATO (赞：1)

### 题目大意：
$n$ 种物品，给定其花费与利润，求在规定本金内获得的最大利润。
### 思路：
因为物品数量无限，考虑完全背包。
#### 状态转移方程：
设 $f(j)$ 表示花费 $j$ 时投资的最大利润。
$f(j)=\max(f(j),f(j-C(i))+R(i))$
非常模板的状态转移方程。
### 注意事项：
因为题目描述中最大总利润=初始钱数-总花费+总收入，因此不是输出 $f(m)$ ，而是遍历 $f$ ，找 $m-j+f(j)$ 的最大值。
### 代码参考：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
ll c[105],r[105],dp[100005],ans;
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for(ll i=1;i<=n;++i)
		cin>>c[i]>>r[i],r[i]-=c[i];
	for(ll i=1;i<=n;++i)
		for(ll j=c[i];j<=m;++j)
			dp[j]=max(dp[j],dp[j-c[i]]+r[i]);
	for(ll i=1;i<=m;++i)
		ans=max(ans,dp[i]+m-i);
	cout<<ans;
}

```


---

## 作者：Gaode_Sean (赞：1)

这题是一道有技巧的背包问题。

首先，我们先要知道每件物品的利润，也就是 $r_i-c_i$，代价是 $c_i$ 。

这样做就是一个裸的 0/1 背包问题，转移方程为 $dp_j=\max(dp_j,dp_{j-c_i}+r_i-c_i)$ 。

注意最后的答案是 $\max(dp_i+m-i)$，期中 $dp_i$ 表示利润，$m$ 为本金，$i$ 为花费的代价。

## AC Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,c[101],r[101],f[100001],ans;
int main()
{
	cin>>n>>m;
	for(i=1;i<=n;i++) cin>>c[i]>>r[i];
	for(i=1;i<=n;i++){
		for(j=c[i];j<=m;j++) f[j]=max(f[j],f[j-c[i]]+r[i]-c[i]);
	}
	for(i=1;i<=m;i++) ans=max(ans,f[i]-i+m);
	cout<<ans;
	return 0;
}
```

---

## 作者：kfhkx (赞：1)

看到题解里没有pascal，就来一波吧~

刚开始看到这题时，马上有了一个贪心的想法，不就将a[i,2]-a[i,1]按从大到小快排一遍，然后直接统计答案不就行了吗?刚开始试了几个自创数据（**数据），发现都对了，就自信满满提交了，结果60分（可能是本题数据水）

### 60分代码P3027.pas

------------

```pascal
var
        n,m,i,h:longint;
        ans:int64;
        a:array[0..100000,0..3] of longint;
function max(x,y:longint):longint;//自定义max函数
begin
        if x>y then exit(x) else exit(y);
end;
procedure kp(x,y:longint);//自定义快排
var
        l,r,m:longint;
begin
        l:=x;
        r:=y;
        m:=a[(l+r)>>1,3];
        repeat
                while a[l,3]>m do inc(l);
                while a[r,3]<m do dec(r);
                if l<=r then begin
                        a[0]:=a[l];
                        a[l]:=a[r];
                        a[r]:=a[0];
                        inc(l);
                        dec(r);
                end;
        until l>r;
        if x<r then kp(x,r);
        if l<y then kp(l,y);

end;
begin
        readln(n,m);
        for i:=1 to n do begin
                read(a[i,1],a[i,2]);
                a[i,3]:=a[i,2]-a[i,1];
        end;
        kp(1,n);
        for i:=1 to n do begin
                if m=0 then break;//发现剩余钱为0就break
                h:=m div a[i,1];//贪心，从大到小
                if h=0 then continue;//如果当前剩余钱数无法购买一个，就找下一个
                if h*a[i,3]<m then begin//贪心，如果发现当前利润少于剩余钱，就exit
                        writeln(ans+m);
                        exit;
                end;
                ans:=h*a[i,3]+ans;
                m:=m-h*a[i,1];
        end;
        if m=0 then writeln(ans) else writeln(ans+m);
end.

```


------------


后来细想了一下，发现当前个体利润不是最大时，总体利润可能会比当前利润最大的大

###附hack数据

input
```
2 50
49 100
1 10

```
output
```
450
```
而我的程序是输出60，所以有60分很不错了~

后来仔细yy了一下，将古董想成物品，将钱数想成背包容量，再看看题目说古董（物品）无限，所以就发现是个完全背包问题

所以问题就解决了。。。


### P3027（1）.pas


------------

```pascal
var
        n,m,i,j,k,x,y:longint;
        ans:array[0..1000000] of int64;
function max(x,y:int64):int64;
begin
        if x>y then exit(x) else exit(y);
end;
begin
        readln(n,m);
        for i:=1 to m do ans[i]:=i;
        for i:=1 to n do begin
                read(x,y);
                k:=y-x;
                for j:=x to m do ans[j]:=max(ans[j],ans[j-x]+k);
        end;
        writeln(ans[m]);
end.
```

---

## 作者：Halberd_Cease (赞：0)

一道完全背包模板题

因为题目求总利润所以我们让利益最大化，即令每一件贡献为 $R_i-C_i$ ，花费为 $C_i$ ；

令 $dp_j$ 表示花费 $j$ 元得到的最大利润；

转移方程为：

$$dp_j=max(dp_j,dp_{j-C_i}+R_i-C_i)$$

因为有可能不花完所有钱就找到最佳情况，所以扫一遍数组得到答案。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int f[10000001],c[10000001],r[10000001],n,m;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i]>>r[i];
		r[i]-=c[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=c[i];j<=m;j++)
		f[j]=max(f[j],f[j-c[i]]+r[i]);
	}
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		ans=max(ans,f[i]-i+m);
	}
	cout<<ans;
}
```

---

