# [POI 2007] WAG-Quaternary Balance

## 题目描述

Byteasar the dragon intends to throw a party, to which he would like to invite many guests. Byteasar wouldalso like to present each guest with an amount of gold to honour the party. Each should receive the sameamount, so that no one's pride is hurt. The dragon is going to weigh out gold for subsequent guests with abeam balance. He has different types of standard masses at his disposal, each type weighing a certain powerof four. Conveniently, Byteasar has lots of the standard masses, hence he may use any number of masses ofany type (power of four) he finds appropriate. Byteasar will always lay the gold on the left weighing basinand the masses on the right or both weighing basins. The dragon wishes to use the least number of massespossible for each weighing. Furthermore, to entertain his guests, Byteasar would like to measure out the goldin unique manner for each person (ie. using different masses or distributing them among the weighing basinsin a different way).

Since dragons' lack of arithmetic skills is legendary, Byteasar has aksed you to write a programme thatwill determine how many guests he may invite, that is, finds the maximum number of ways in which $n$ grammes of gold can be weighed out using the minimum number of masses possible. Should you fare well,you will also get your share!

TaskWrite a programme that:

reads from the standard input the amount of gold (in grammes) which Byteasar intends to present each    guest with,        calculates the number of ways in which this amount of gold can be weighed out using the minimum    number of masses possible,        writes out the remainder of dividing the result by $10^9$ to the standard output.

给定一个数 $n$，要求将 $n$ 表示成一些 $4^k$ 的数之和/差的形式，要求用的数最少，求方案数模 $10^9$ 的结果。


## 样例 #1

### 输入

```
166```

### 输出

```
3```

# 题解

## 作者：rickyxrc (赞：8)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

模拟赛 T1 是这个，然后喜提保龄，有感而发，写一篇题解。

十分感谢 [itshawn](https://www.luogu.com.cn/user/401479) 和 [刘辰雨](https://www.luogu.com.cn/user/524906) 对本题解的二次润色打磨，并修复了很多讲的不清楚和错误的细节。

## 题面大意

给定一个数 $n$，要求将 $n$ 表示成一些 $4^k$ 的数之和/差的形式，要求用的数最少，求方案数模 $10^9$ 的结果。

## 解题思路

首先我们不难想到使用高精度，将 $n$ 进行四进制拆分，拆成低位起的数组。

例如 $(166)_{10} = (2212)_{4}$，我们的 $c$ 数组就是 $[2,1,2,2]$，下文所讨论的状态转移均在此前提下进行。

然后我们考虑状态设计，我们定义第一维为已经规划到的位数，第二维为使用的数字总量，第三维为是否有数字进位到**下一位**。

注意：在我们的状态转移过程中，使用的数字凑出的总和始终不变，我们只是在进行等价变换。

那么我们就针对进位和不进位分别讨论。

如果这一位不进位，那么我们就直接将数放上去。

$$f_{i,j+c_i,0} \leftarrow f_{i-1,j,0}+f_{i-1,j,1}$$

如果这一位有进位，那么我们需要考虑两种情况：

1. 将值加上 $1$ 个更大（是现在 $4$ 倍）的数，为了保持这两位的数字总和不变，仍是原来的 $4^{i-1}(c_{i-1})+4^ic_i$，将其减去 $4^{i-1}(4-c_{i-1})$，总花费为 $5-c_{i-1}$ 个数。
$$f_{i,j+5-c_{i-1},1} \leftarrow f_{i-1,j,0}$$
2. 将值加上 $1$ 个更大（是现在 $4$ 倍）的数，为了保持这两位的数字总和不变，仍是原来的 $4^i (c_i+1)$（因为上一位有进位），将其减去 $3-(c_{i-1}+1) = 2-c_{i-1}$，总花费为 $3-c_{i-1}$ 个数。
$$f_{i,j+3-c_{i-1},1} \leftarrow f_{i-1,j,1}$$
然后代码就不难写了，容易发现第一位可以滚掉节省空间（校内赛只给 32M），最后结果是第一个非零的 $f_{n,i,0}+f_{n,i,1}$。

代码如下：

```cpp
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <vector>

#define maxn 3007

typedef long long i64;

const i64 mod = 1000000000;

int min(int a, int b);
int max(int a, int b);

struct Int
{
    int li[maxn], len;
    Int();
    void fix();
    void read();
    void write();
    int &operator[](int x);
};
Int operator+(Int a, Int b);
Int operator*(Int a, i64 b);
i64 pow(i64 x, i64 p);
bool operator>(Int a, Int b);
bool operator==(Int a, Int b);
Int operator-(Int a, Int b);

Int n, c, pow4[maxn];
i64 res = 0, mxval, cnt[maxn], now, dp[2][maxn][2];

int main()
{
    n.read();

    pow4[0][0] = 1, pow4[0].len = 1;

    for (mxval = 1; mxval < maxn; mxval++)
    {
        pow4[mxval] = pow4[mxval - 1] * 4;
        if (pow4[mxval] > n)
            break;
    }

    for (int j = mxval - 1; j >= 0; j--)
    {
        while (n > pow4[j])
            cnt[j]++,
                n = n - pow4[j];
        if (pow4[j] == n)
        {
            cnt[j]++;
            break;
        }
    }

    dp[now][0][0] = 1;
    for (int i = 0; i < mxval; i++)
    {
        now ^= 1;
        memset(dp[now], 0, sizeof dp[now]);
        for (int j = 0; j + cnt[i] < maxn; j++)
        {
            dp[now][j + cnt[i]][0] = (dp[now][j + cnt[i]][0] + dp[now ^ 1][j][0]) % mod;
            dp[now][j + cnt[i]][0] = (dp[now][j + cnt[i]][0] + dp[now ^ 1][j][1]) % mod;
            dp[now][j + 5 - cnt[i]][1] = (dp[now][j + 5 - cnt[i]][1] + dp[now ^ 1][j][0]) % mod;
            dp[now][j + 3 - cnt[i]][1] = (dp[now][j + 3 - cnt[i]][1] + dp[now ^ 1][j][1]) % mod;
        }
    }

    for (int i = 0; i < maxn; i++)
        if (dp[now][i][0] + dp[now][i][1])
        {
            printf("%d", dp[now][i][0] + dp[now][i][1]);
            return 0;
        }

    return 0;
}
```

---

## 作者：Wolfycz (赞：6)

首先将n进行转成四进制，记录在T数组里面(T[1]为最低位)，然后考虑从低位到高位DP。

我们设f[i]表示不进行借位，g[i]表示向高位借一位。

如果借到了一位是不能算在第i位里面的，因为不论是f[i]还是g[i]记录的都是$4^i$，不论正负。

转移方程如下:

f[i]=merge(f[i-1]+T[i],g[i-1]+1+T[i]);

g[i]=merge(f[i-1]+4-T[i],g[i-1]+3-T[i]);

之所以要用merge是因为f[i],g[i]记录了两个参数，一个是用了多少个数，一个是方案数。

代码详见[我的博客](http://www.cnblogs.com/Wolfycz/p/8945344.html)

---

## 作者：Caiest_Oier (赞：4)

# [P3464](https://www.luogu.com.cn/problem/P3464)     
首先随便高精搞一下转成 $4$ 进制，接下来考虑每一位上如何加减。第 $i$ 位上有两种选择，第一种是从 $0$ 加到当前位的值 $a_i$，第二种是第 $i+1$ 位多加一个 $1$，然后当前位从 $4$ 减到 $a_i$，于是有一个 dp，令 $f_i$ 表示前 $i$ 位，第 $i$ 位从 $0$ 往上加，所需的最小次数，$g_i$ 表示前 $i$ 位，第 $i$ 位从 $4$ 往下减，所需的最小次数。则有转移：    

$$f_i=\min(f_{i-1}+a_i,g_{i-1}+a_i+1)$$
$$g_i=\min(f_{i-1}+4-a_i,g_{i-1}+3-a_i)$$    

最后的答案就是 $\min(f_{len},1+g_{len})$，转移的时候顺便记一下方案数就好了。     

另外提一嘴，ABC231E 和这题几乎一样。    

代码：     

```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 1000000000
using namespace std;
string s;
int len,a[500003],dp[500003][2],dp2[500003][2],ans,ans2;
signed main(){
	cin>>s;
	for(int i=0;i<s.length();i++){
		for(int j=1;j<=len;j++)a[j]*=10;
		a[1]+=s[i]-'0';
		for(int j=1;j<=3000;j++){
			if(a[j]!=0)len=j;
			a[j+1]+=a[j]/4;
			a[j]%=4;
		}
	}
	dp[1][0]=a[1];
	dp[1][1]=1;
	dp2[1][0]=4-a[1];
	dp2[1][1]=1;
	for(int i=2;i<=len;i++){
		dp[i][0]=min(dp[i-1][0]+a[i],dp2[i-1][0]+a[i]+1);
		if(dp[i][0]==dp[i-1][0]+a[i])dp[i][1]=(dp[i][1]+dp[i-1][1])%MOD;
		if(dp[i][0]==dp2[i-1][0]+a[i]+1)dp[i][1]=(dp[i][1]+dp2[i-1][1])%MOD;
		dp2[i][0]=min(dp[i-1][0]+4-a[i],dp2[i-1][0]+3-a[i]);
		if(dp2[i][0]==dp[i-1][0]+4-a[i])dp2[i][1]=(dp2[i][1]+dp[i-1][1])%MOD;
		if(dp2[i][0]==dp2[i-1][0]+3-a[i])dp2[i][1]=(dp2[i][1]+dp2[i-1][1])%MOD;
	}
	ans=min(dp[len][0],dp2[len][0]+1);
	if(ans==dp[len][0])ans2=(ans2+dp[len][1])%MOD;
	if(ans==dp2[len][0]+1)ans2=(ans2+dp2[len][1])%MOD;
	cout<<ans2;
	return 0;
}
```


---

## 作者：Pengzt (赞：4)

[P3464](https://www.luogu.com.cn/problem/P3464)

首先先将原数变为四进制的数。

由于算的是进位 / 不进位的代价最小值和方案数，容易想到 dp。

这里假定该四进制数是从高位到低位的，顺序显然是由低位到高位。

令 $f_{i,0/1}$ 表示第 $i$ 位进 / 不进位的最小代价，$g_{i,0/1}$ 表示的是最小代价下的方案数。

对当前位的值分讨一下即可。

时空复杂度线性。

[评测记录](https://www.luogu.com.cn/record/118591080)

---

## 作者：小塘空明 (赞：3)

借鉴了clairs大佬的想法

首先对数进行四进制分解

f[i]表示当前位置不从i+1借位拼完前i位数所需要的数的最小值，即从当前位从0开始选

g[i]表示当前位置从i+1借位拼完前i位数所需要的数的最小值，当前位从4开始选

注意因为第n位可能对第n+1位借位，需要对n+1位进行计算

最后取f[n+1],g[n+1]中较小值，dp的过程中记录方案数

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#define N 3005
#define mod 1000000000
using namespace std;
typedef long long ll;
struct node{
	int x,y;node(){};
	node(int _x,int _y){x=_x,y=_y;}
	inline node operator+(int _x){return node(x+_x,y);}
	inline node operator+(node b){return x==b.x?node(x,(y+b.y)%mod):(x<b.x?node(x,y):b);}
}f[N],g[N];
int n,i,l,a[N],b[N];char s[N];
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	scanf("%s",s);l=strlen(s);for(i=1;i<=l;i++) a[i]=s[l-i]-'0';
	while(l){
		for(i=l,a[0]=0;i;i--) a[i-1]+=(a[i]&3)*10,a[i]>>=2;
		for(b[++n]=a[0]/10;l&&!a[l];l--);
	}
	f[0]=node(0,1);g[0]=node(N,0);
	for(i=1,n++;i<=n;i++) f[i]=(f[i-1]+b[i])+(g[i-1]+b[i]+1),g[i]=(f[i-1]+(4-b[i]))+(g[i-1]+(3-b[i]));
	return printf("%d\n",f[n].y),0;
}
```


---

## 作者：SunsetLake (赞：2)

数位DP。

首先分析下题目，将 $n$ 表示成一些 $4^k$ 的数之和/差的形式 ，就可以理解为一个天平，$n$ 放在左边，可以选一些数值为 $4$ 的幂的砝码，放左/右都行，在让天平平衡，求方案数。

$4^k$ 很容易联想到四进制，于是考虑把 $n$ 转换为四进制后进行数位 DP，就比较好想了。

设 $dp[i][j][k]$ 表示（$4$ 进制下的 $n$）从低到高第 $i$ 位，已经用了 $j$ 个砝码，这一位进/不进位，$k:0/1$ 的方案数。关于进位这一状态，转移时会讲解。

记 $fr[i]$ 表示 $n$ 在四进制下第 $i$ 位的值。

那么状态设计好了，就可以开始~~愉快~~的转移了。

首先考虑和的形式（砝码和物品不在一边）:

- $dp[i][j+fr[i]][0]=dp[i][j+fr[i]][0]+dp[i-1][j][0]$ 直接填当前数位上的值，从更低位转移过来。
- $dp[i][j+fr[i]+1][0]=dp[i][j+fr[i]+1][0]+dp[i-1][j][1]$ 上一位有进位的情况，要加上低位进的一位再填。

关于进位：因为我们从低到高填砝码，在放的时候可能会有物品和砝码放一边，也就是减法的情况，这时我们就需要在另一边补一个更大的砝码来使天平平衡，相当于在更高位填一个砝码。

然后是差的形式（砝码和物品在一边）：

- $dp[i][j+4-fr[i]][1]=dp[i][j+4-fr[i]][1]+dp[i-1][j][0]$
- $dp[i][j+4-fr[i]-1][1]=dp[i][j+4-fr[i]-1][1]+dp[i-1][j][1]$ 上一位有进位的情况，就可以少放一个砝码。

差形式因为砝码和物品放在了同一边，又因为这是四进制的数，所以我们考虑在这一边补上 $4-fr[i]$ 个砝码，让这一位合成更大的一位，也就是进位，在天平另一边再放上这更大的一位使其平衡。所以差的形式 $k$ 值为 $1$，表示需要进位。

这样就转移完了。

统计答案的话记 $len$ 为 $n$ 在四进制下的长度，从小到大枚举 $j$ （因为要满足砝码数最少），找到第一个不为零的  $dp[len][j][0]+dp[len][j-1][1]$，输出即可。（因为如果用了 $j-1$ 个砝码还要进位时，他就得再补一个砝码，最后总数也是 $j$，因此也要计入答案）。

注意：
- 本题 $n<10^{1000}$，需要用字符串读入。
- 直接开数组会炸空间，需要滚动数组优化。

其余细节在代码中呈现。

## code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
string s;
int n,a[100005],fr[100005],sum,num,cnt,dp[2][50005][2];
int now;
const int mod=1e9;
int main(){
	cin>>s;
	n=s.size();
	for(int i=0;i<n;++i)a[i+1]=s[i]-'0';
	while(1){//预处理四进制
		bool f=0;
		sum=0;
		for(int i=1;i<=n;++i){
			if(a[i])f=1;
			sum=sum*10+a[i];//每次边乘边模，求出当前数除以四的余数，变转成四进制了。
			a[i]=sum/4;//把这个数除以4。
			sum%=4;
		}
		if(f)fr[++num]=sum;
		else break;
	}
	dp[0][0][0]=1;//边界初始化。
	for(int i=1;i<=num;++i){
		now=i&1;//滚动数组
        
      //因为每一位可以填四个，所以枚举个数时要为长度的4倍。
      
      
		for(int j=0;j<=4*num;++j)dp[now][j][0]=dp[now][j][1]=0;
		for(int j=0;j<=num*4;++j){
			dp[now][j+fr[i]][0]=(dp[now][j+fr[i]][0]+dp[now^1][j][0])%mod;
			dp[now][j+fr[i]+1][0]=(dp[now][j+fr[i]+1][0]+dp[now^1][j][1])%mod;
			dp[now][j+4-fr[i]][1]=(dp[now][j+4-fr[i]][1]+dp[now^1][j][0])%mod;
			dp[now][j+4-fr[i]-1][1]=(dp[now][j+4-fr[i]-1][1]+dp[now^1][j][1])%mod;
		}
	}
   //找答案
	for(int i=1;i<=4*num;++i)if(dp[now][i][0]+dp[now][i-1][1])return cout<<(dp[now][i][0]+dp[now][i-1][1])%mod,0;
	return 0;
}
```

---

## 作者：Creeper_l (赞：2)

### 题意

给定一个数 $n$，要求将 $n$ 表示成一些 $4^{k}$ 的数之和或差的形式，要求用的数最少，求方案数。

### 思路

首先看到这道题的数据范围 $n\le10^{1000}$，又是求方案数，所以想到用数位 DP。因为每一个数都是 $4$ 的次幂，显然我们需要讲原数转化为 $4$ 进制，具体方法不多讲述。

最重要的还是 DP 方程的设计了。题目说可以在两数之间做加减运算，所以必须考虑一个很重要的东西——借位。因为减法运算的过程中会出现向高位借位的情况。举个例子：$(013)_{4} = (020)_{4} - (001)_{4}$，可以发现，如果要借位的话，当前数位上的数从 $3$ 变成了 $1$，也就是从 $i$ 变成了 $4-i$。被借的那一位上从  $1$ 变成了 $2$，也就是从 $i$ 变成了  $i+1$。于是 DP 方程便可以推出来了。

设 $f_{i}$ 表示不向高位借位时算到第 $i$ 位时的方案数，$g_{i}$ 表示要向高位借位时算到第 $i$ 位时的方案数，则有：

-  $f_{i} = (f_{i - 1} + b_{i}) + (g_{i - 1} + b_{i} + 1)$

- $g_{i} = (f_{i - 1} + 4 - b_{i}) + (g_{i - 1} + 3 - b_{i} )$

**注意**：这里的 f 和 g 均是结构体数组，加号的意义在结构体内经过了重定义，具体意义详见代码。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls id << 1
#define rs id << 1 | 1
#define inf 0x3f3f3f3f
typedef pair <int,int> pii;
const int MAXN = 5e3 + 10;
const int mod = 1e9;
int a[MAXN],cnt,b[MAXN],n;
char c[MAXN];
struct Node
{
	int x,y;Node(){};
	//x为数的个数，y为方案数 
	Node(int a,int b){x = a,y = b;}
	inline Node operator + (int a){return Node(x + a,y);}
	//结构体加普通数：数的个数相加，方案数不变 
    inline Node operator + (Node b){return x == b.x ? Node(x,(y + b.y) % mod) : (x < b.x ? Node(x,y) : b);}
    //结构体加结构体：如果数的个数相等，则方案数相加；否则选数的个数较少的情况时的方案数。 
}f[MAXN],g[MAXN];
signed main()
{
	cin >> c + 1;
	int len = strlen(c + 1);
	for(int i = len;i >= 1;i--) a[i] = c[len - i + 1] - '0';
	while(len)
	{
		a[0] = 0;
		for(int i = len;i >= 1;i--)
		{
			a[i - 1] += ((a[i] % 4) * 10);
			a[i] = (a[i] - a[i] % 4) / 4;
		}
		b[++cnt] = a[0] / 10;
		if(a[len] == 0) len--;
	}
	cnt++;
	f[0] = Node(0,1),g[0] = Node(MAXN,0);
	for(int i = 1;i <= cnt;i++)
	{
		f[i] = (f[i - 1] + b[i]) + (g[i - 1] + b[i] + 1);
		g[i] = (f[i - 1] + (4 - b[i])) + (g[i - 1] + (3 - b[i]));
	}	
	cout << f[cnt].y;
	return 0;
}

```


---

