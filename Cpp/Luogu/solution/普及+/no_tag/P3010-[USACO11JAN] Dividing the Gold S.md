# [USACO11JAN] Dividing the Gold S

## 题目描述

Bessie 和 Canmuu 找到了一袋 $N (1 \leq N \leq 250)$ 枚金币，他们希望尽可能均匀地分配这些金币。第 $i$ 枚金币的价值为 $v_i (1 \leq v_i \leq 2,000)$。奶牛们希望尽可能均匀地分割这堆金币，但这并不总是可能的。两个堆之间的最小价值差是多少？

此外，Bessie 和 Canmuu 发现可能有多种方法以该最小差异分割金币。他们还想知道以最公平方式分割金币的方法数。如果无法均匀分割，Bessie 将得到价值较高的一堆。

例如，考虑一袋五枚金币，价值分别为：$2、1、8、4$ 和 $16$。Bessie 和 Canmuu 将金币分成两堆，一堆有一枚价值为 16 的金币，另一堆有剩下的金币，价值为 $1+2+4+8=15$。因此，差异为 $16-15 = 1$。这是他们以这种方式分割金币的唯一方法，所以均匀分割的方法数只有 $1$。

注意，相同价值的金币可以在堆之间交换，以增加执行最佳分割的方法数。因此，硬币集合 $\{1, 1, 1, 1\}$ 有六种不同的方法分割成两个最佳分区，每个分区有两枚硬币。

## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5 
2 
1 
8 
4 
16 
```

### 输出

```
1 
1 
```

# 题解

## 作者：妖怪i (赞：6)

#### 此题一共有两个问题：

1. 求金币分为两份的最小差值。
1. 求分为最小差值时的方案数。

#### 分步解答这两个问题。

##### 第一个：
求两份金币的最小差值，那么我们很自然的想到，当两份金币相同时，差值最小。
那么题目就可以转化为，金币的价值最多能达到金币总价值的一半的多少。那么就是01背包了。


##### 第二个：
直接求出第一问的金币价值的方案数即可。

下面贴下代码：


```cpp

#include<bits/stdc++.h>
#define mod 1000000
using namespace std;
int n,a[350],tot,sum,f[500005];
long long dp[500005];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),sum+=a[i];
	tot=sum;
	sum/=2;
	for(int i=1;i<=n;i++)
		for(int j=sum;j>=a[i];j--)
			f[j]=max(f[j],f[j-a[i]]+a[i]);
	printf("%d\n",tot-2*f[sum]);
	dp[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=tot;j>=a[i];j--)
			dp[j]=(dp[j]+dp[j-a[i]])%mod;
	printf("%lld",dp[f[sum]]);
	return 0;
}

```

---

## 作者：issue_is_fw (赞：3)

这不就是一个01背包求方案数字吗~

我们令$dp[i]$表示价格为$i$的方案数

初始化$dp[0]=1$

然后正常转移即可

```cpp
for(int i=1;i<=n;i++)
for(int j=m;j>=a[i];j--
	dp[j]+=dp[j-a[i]];
```
然后我们再往中间价值，也就是m/2逐个往下找可行解。

## 可行解是$dp[i]!=0$吗

很遗憾，因为我们一直在$mod 1e6$

所以可能出现可行解刚好被$mod$成0的情况

判断这个你可以再求一边01背包不去mod

我这里比较懒，用了个不保险的方法。

```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[1000009],a[309],n;
bool vis[1000009];
const int mod=1e6;
int main()
{
	cin>>n;
	int m=0;
	dp[0]=1;
	for(int i=1;i<=n;i++)	cin>>a[i],m+=a[i];
	for(int i=1;i<=n;i++)
	for(int j=m;j>=a[i];j--)
	{
		dp[j]+=dp[j-a[i]];
		if(dp[j])	vis[j]=1;
		dp[j]%=mod;
	}
	int x=(m)/2;
	for(int i=x;i>=0;i--)
	{
		if(vis[i])
		{
			cout<<(m-i-i)<<endl;
			cout<<dp[i];
			return 0;
		}
	}
}


```


---

## 作者：happy_zero (赞：2)

首先要明确，当两堆中的其中一堆为金币总数的一半时两堆差值最小。

先考虑第一问，记 $vis_i$ 表示能否取到**正好**价值为 $i$ 的物品，初始化是 $vis_0=1$，转移就类似正常 01 背包：`vis[j]=vis[j]||vis[j-a[i]]`，这个的含义是原来就可以或通过选 $a_i$ 使 $j$ 可以。

第二问也类似，设 $dp_i$ 为**正好**取到价值 $i$ 的物品时的方案数，转移类似第一问。


代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Mod=1e6;
int n,sum;
int a[255];
int dp[500005];
bool vis[500005];
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sum+=a[i];
    }
    dp[0]=1;vis[0]=1; 
    for(int i=1;i<=n;i++){
        for(int j=sum/2;j>=a[i];j--){
            dp[j]=(dp[j]+dp[j-a[i]])%Mod; 
            vis[j]=vis[j]||vis[j-a[i]];
        }
    }
    for(int i=sum/2;i>=0;i--){
        if(vis[i]){
            cout<<sum-i*2<<endl; 
            cout<<dp[i]%Mod;
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：RainFestival (赞：2)

此题考到的知识点有：01背包，背包方案总数

两堆金差距最小，就是少的一堆金与金总数/2差距最小

求出最接近的，计算方案总数

```pascal
var
  n,min,i,s,j,s1,s2:longint;
  b:array[0..1000005] of boolean;
  a:array[1..10005] of longint;
  c:array[0..1000005] of longint;
begin
  readln(n);
  min:=$7fffffff;
  for i:=1 to n do
    begin
      read(a[i]);
      s:=s+a[i];
    end;
  b[0]:=true;
  for i:=1 to n do
    for j:=s downto a[i] do
      if b[j-a[i]] then
        b[j]:=true;
  for i:=1 to s div 2 do
    if b[i] and b[s-i] then
      begin
        s1:=i;
        s2:=s-i;
        min:=abs(i-(s-i));
      end;
  writeln(min);
  min:=(s-min) div 2;
  c[0]:=1;
  for i:=1 to n do
    for j:=min downto a[i] do
      c[j]:=(c[j]+c[j-a[i]]) mod 1000000;
  writeln(c[min]);
end.

```

---

## 作者：荣耀南冥 (赞：1)

# P3010 [USACO11JAN]Dividing the Gold S
[题目传送门](https://www.luogu.com.cn/problem/P3010)

~~一看有一道水题又没有题解，我当然要来水一发~~

首先看题目，均分钱币，并求方案

## Task1
求均分钱币的金币差还是比较好求的，这道题可以等价转化为 01 背包问题，即为求背包容量为 $\frac {\sum w[i]}{2}$ 的最大价值。那么先定义状态，设 $ f [ j ] $ 为背包容量为 j 时的最大价值，然后枚举钱币
```cpp
for(int i=1;i<=n;++i)
	for(int j=maxn;j>=w[i];++j)
		f[j]=max(f[j],f[j-w[i]]+w[i]);
```
## Task2
定义 $ num [ i ] $ 为容量为 i 最大价值的方案

枚举到第 i 枚金币时，设 $ d = w[i] $ ，首先， $ f [ j ] $ 此时可以又 $ f[ j - d ] + d $ 转移过来，当 $ f [ j ] > f [ j - d ] + d $ 时，那么之前 $ num [ j ] $ 答案不是最大值方案数，所以 $ num [ j ] = num [ j - d ] $ ，当相等时， $ num [ j ] + =num [ j - d ] $ ， **注意取膜**

最后融合一下
```
for(int i=1;i<=n;++i){
	for(int j=max(mid,k);j>=w[i];--j){
		if(f[j]<f[j-w[i]]+w[i]){
			f[j]=f[j-w[i]]+w[i];
			num[j]=num[j-w[i]];
		}else if(f[j]==f[j-w[i]]+w[i]){
			num[j]=(num[j]+num[j-w[i]])%mod;
		}
	}
}
```
然后你会变成91分
 
 Hack 数据
 
 **input**
 ```
 2
 1 
 3
 ```
 **output**
 ```
 2
 0
 ```
 **正确结果**
 ```
 2
 1
 ```
 出现这样的原因就是最终结果并没有转移到这里，因为当转移到 $ f[ mid ] $ 时， $ num [ mid - w [ i ] ] $ 还是 0 ，所以最后出锅了，解决方案就是计算一个每个 $ w [ i ] $ 的最大值，然后使用 $ mid $ 与 $ k $ 的$max$
 
 $ Code $
 ```cpp
 #include <bits/stdc++.h>
using namespace std;
const int mod=1e6;
int n,maxn,mid,k;
int w[1000000+10];
int f[1000000+10];
int num[1000000+10];

inline int read(){
	int r=0,l=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')l=-1;ch=getchar();}
	while(isdigit(ch)){r=(r<<3)+(r<<1)+ch-'0';ch=getchar();}
	return r*l;
}

int main(){
	n=read();num[0]=1;
	for(int i=1;i<=n;++i)w[i]=read(),maxn+=w[i],k=max(k,w[i]);
	mid=maxn/2.0;mid=max(mid,k);
	for(register int i=1;i<=n;++i)
		for(register int j=mid;j>=w[i];--j)
			if(f[j]<f[j-w[i]]+w[i]){
				f[j]=f[j-w[i]]+w[i];
				num[j]=num[j-w[i]];
			}else if(f[j]==f[j-w[i]]+w[i]){
				num[j]=(num[j]+num[j-w[i]])%mod;//注意取膜
			}
	printf("%d\n%d\n",abs(maxn-2*f[mid]),num[mid]);
	return 0;
}
 ```

---

## 作者：Velix (赞：1)

一道思路较为明显的DP题。

首先，找差值最小的，就是找在$1 \sim (\sum v[i])/2$里找可行的最大的数。可以用类似于01背包的DP进行可行性的计算。

具体DP的代码(此时的$b$为$(\sum v[i])$)：

```cpp
	for(int i=1;i<=n;i++)
		for(int j=b/2;j>=a[i];j--)
			dp1[j]=max(dp1[j],dp1[j-a[i]]+a[i]);
```
对于第二问，求方案数，相信求出了第一问，第二问也是很简单的。

~~[第二问双倍经验](https://www.luogu.com.cn/problem/P2563)~~

依然像01背包一样，但递推式要改为：

$$dp[j]=dp[j]+dp[j-a[i]]$$

注意这个式子要取模。

### Final Code

```cpp
#include<iostream>
using namespace std;
int dp1[500001],dp2[500001],a[251],b,n;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b+=a[i];
	for(int i=1;i<=n;i++)
		for(int j=b/2;j>=a[i];j--)
			dp1[j]=max(dp1[j],dp1[j-a[i]]+a[i]);
	cout<<b-dp1[b/2]*2<<endl;
	dp2[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=b;j>=a[i];j--)
			{dp2[j]=dp2[j]+dp2[j-a[i]];if(dp2[j]>=1000000)dp2[j]-=1000000;} 
	cout<<dp2[dp1[b/2]];
}
```


---

## 作者：DengDuck (赞：0)

一眼 01 背包。

我们把目光投向较小的金币堆，显然确定了它就确定了方案。

我们求出所有金币的总数 $sum$，显然较小的金币堆数量不超过 $\lfloor\dfrac {sum}2\rfloor$。

利用 01 背包我们可以算出小金币堆每种金币数对应的方案数。

接下来我们枚举小金币堆的大小，找出最大的有解的数量，输出其与大金币堆的金币差和方案数即可。

不过方案数有模数，值为 $0$ 不代表无解，需要再开一个数组表示是否有解。

时间复杂度为 $\mathcal O(n^2m)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=255;
const LL M=1e6;
const LL mod=1e6;
LL n,a[N],f[M],vis[M],sum,m;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		sum+=a[i];
	}
	m=sum/2;
	f[0]=1,vis[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=m;j>=a[i];j--)
		{
			f[j]=(f[j]+f[j-a[i]])%mod;
			vis[j]|=vis[j-a[i]];
		}
	}
	for(int i=m;i>=0;i--)
	{
		if(vis[i])
		{
			cout<<sum-2*i<<endl<<f[i]<<endl;
			return 0;
		}
	}
}
```

---

## 作者：Usada_Pekora (赞：0)

分析题意：

第一问：求两份金币的最小差值，那么肯定是容量均分差距最小，则变成了一个容量为总量一半的 01 背包。设 $f[i]$ 为 $i$ 容量下背包的最大值，则 $f[i]=\max \{f[i-a[j]]+a[j] \}(j\leq n)$ 。

第二问：求最小差值下的分配方案，这是 01 背包求方案数的板子， 设 $F[i]$ 为容量为 $i$ 时最优解的方案，则 $F[0]=1,F[i]= \Sigma_{j=1}^n F[i-a[j]]$ 。

代码如下

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int f[N], n, a[N], sum, F[N] ;
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], sum += a[i];
	for (int i = 1; i <= n; i++)
		for (int j = sum / 2; j >= a[i]; j--)
			f[j] = max(f[j], f[j - a[i]] + a[i]);
	cout << sum - 2 * f[sum / 2] << endl;
	F[0]=1;
	for (int i = 1; i <= n; i++)
		for (int j = sum / 2; j >= a[i]; j--)
			F[j] = (F[j] + F[j - a[i]]) % 1000000;
	cout << F[f[sum / 2]] << endl;
	return 0;
}

```


---

## 作者：_edge_ (赞：0)

~~我也不敢想象 $10^8$ 是怎么过去的 ……~~

就是首先进行一个拼数，这些数中可以拼出的数都赋值为 $1$ 否则就是赋值为 $0$ ，这个过程可以用 $O(n^2)$ 的 DP 来实现，同时维护一下拼出的方案数，然后暴力的遍历了一下最小差值。

于是就 A 了。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
using namespace std;
const int INFN=255;
const int INF=(2e3+5)*INFN;
const int Mod=1e6;
bool f[INF];
int f1[INF],sum,n,Min,Minv;
int fzx_abs(int x) {
        return x<0 ? -x : x;
}
signed main()
{
        memset(f,false,sizeof f);
        memset(f1,0,sizeof f1);
        scanf("%lld",&n); f[0]=true; f1[0]=1;
        for (int i=1; i<=n; i++) {
                int a=0; scanf("%lld",&a); sum+=a;
                for (int j=5e5; j>=a; j--) {
                        if (!f[j-a]) continue;
                        f[j]=true; f1[j]+=f1[j-a];
                        f1[j]%=Mod;
                }//n^2 DP 进行拼数。
        }
        Min=1e9;
        for (int i=0; i<=5e5; i++) {
                if (!f[i]) continue;
                if (Min<=fzx_abs((sum-i)-i)) continue;
                Min=fzx_abs((sum-i)-i);
                // cout<<fzx_abs((sum-i)-i)<<" "<<i<<"\n";
                Minv=f1[i];//暴力寻找最小值。
        }
        cout<<Min<<"\n"<<Minv<<"\n";
        return 0;
}

```

**谢谢观赏！**

---

## 作者：Hog_Dawa_IOI (赞：0)

题目大意都很显然，有 $n$ 堆金币，要尽可能平均地分成两堆，问这两堆的差值最小是多少，并求出得到这个差值的方案数。     
对于问题一，我们可以转化成一个大小为 $\lfloor \dfrac{n}{2} \rfloor$ 的背包问题，因为这样求出的答案会尽量地接近于 $\lfloor \dfrac{n}{2} \rfloor$，达到了“尽可能平均”的目的。    
设求出的背包答案为 $a$，则另一堆较大的金币堆的金币数量为 $ (\sum^n_{i=1}  v_i)-a$。       
第二个问题让我们求方案数，我们可以在求背包的时候顺便一求当前状态的方案数，递推代码为 `ans[j]+=ans[j-v[i]]`。不过要记得初始化 `ans[0]=1`，要不然整个数组加来加去都是零。    
最后记得对 $10^6$ 取模。     
时间复杂度 $O(n \times (\sum^n_{i=1} v_i))$，数据规模撑死就是 $250 \times 250 \times 2000=125000000$，可以通过。           
截至二零二三年十月三日我的代码洛谷排名第三。
```cpp
#include<stdio.h>
int n,s[255],f[250005],ans[250005];
int main()
{
    scanf("%d",&n),ans[0]=1;
    for(int i=1;i<=n;i++) scanf("%d",&s[i]),s[0]+=s[i];
    for(int i=1;i<=n;i++) for(int j=s[0]>>1;j>=s[i];j--)
    f[j]=f[j]>f[j-s[i]]+s[i]?f[j]:f[j-s[i]]+s[i],
    ans[j]=(ans[j]+ans[j-s[i]])%1000000;
    printf("%d\n%d",s[0]-f[s[0]>>1]-f[s[0]>>1],ans[f[s[0]>>1]]);
}
```

---

