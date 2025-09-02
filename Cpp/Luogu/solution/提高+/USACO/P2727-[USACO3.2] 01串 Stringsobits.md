# [USACO3.2] 01串 Stringsobits

## 题目背景

考虑排好序的 $N$（$1 \leq N \leq 31$）位二进制数。


## 题目描述

他们是排列好的，而且包含所有长度为 $N$ 且这个二进制数中 $1$ 的位数的个数小于等于 $L$（$L \leq N$）的数。

你的任务是输出满足长度为 $N$，且 $1$ 的个数小于等于 $L$ 的第 $i$ 小的那个二进制数（保证这个数存在）。

例：$100101$ 中，$N=6$，含有 $1$ 的个数为 $3$。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 3.2


## 样例 #1

### 输入

```
5 3 19```

### 输出

```
10011```

# 题解

## 作者：约修亚_RK (赞：41)

这题真是杀了我好几刀回马枪……

注意点：“第几小的数”用int不够，要用long long int。


我们的目标是找到第i个长为N的，最多含有L个1的二进制数。那么，用F[k, i]来表示在前k位中，恰有i个1的二进制数的数量。Sum(F[k, 0~i])就表示在前k位中，最多有i个1的二进制数的数量。

转移方程很好写，边界条件是F[k, 0] = 1（在前k位中，没有1的二进制数只有一个，每一位都是0）。

F[k, i] = F[k-1, i] + F[k-1, i-1]，分别是第k位是0和第k位是1。


接下来，for k in [0, n]（注意，从0开始循环），求出Sum(F[k, 0~L])。如果这个和大于p，就说明我们要求的这个数字包含在bit[k]=1的情况里。（因为之前的都小于p）。那么我们就可以把p扣除掉bit[k]=0的情况，也就是扣掉Sum(F[k-1, 0~i])【即第k位是0时，至多有i个1的二进制数的数量。】。

确定了bit[k]=1，那么就可以把L和n各扣掉1，继续找下一个为1的位了（重复上面步骤）。


最后倒序输出这个二进制数就完成了。


```cpp
/* P2727
 * Au: SJoshua
 */
#include <cstdio>
#include <algorithm>

using namespace std;

int dp[33][33];
bool num[33];

void search(int n, int l, long long int p) {
    long long int s, last;
    for (int k = 0; k <= n; k++) {
        last = s;
        s = 0;
        for (int i = 0; i <= l; i++) {
            s += dp[k][i];
            if (s >= p) {
                num[k] = true;
                return search(n-1, l-1, p-last); 
            }
        }
    }
}

int main(void) {
    int n, l;
    long long int p;
    scanf("%d %d %lld", &n, &l, &p);
    for (int k = 0; k <= n; k++) {
        dp[k][0] = 1;
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= k; i++) {
            dp[k][i] = dp[k-1][i] + dp[k-1][i-1];
        }
    }
    search(n, l, p);
    for (int k = n; k >= 1; k--) {
        printf("%d", num[k]);
    }
    return 0;
}
```

---

## 作者：Tarsal (赞：13)

本蒟蒻又双叒叕被爆踩辣！

[P2727 01串 Stringsobits](https://www.luogu.org/problem/P2727)

其实只要理解了就会觉得这是个~~傻逼题~~！

这题给的标签是 dp，搜索，数论

但是可以用二分的思路做！

Solution：

从最高位开始枚举，

我们考虑每一位，是不是只可以取0/1

那么我们就先求出当此位置为0时，它可以做到的方案数（等会再告诉你们为什么要求

我们想一想，什么时候此位该为0，什么时候此位该为1？？？

我们求出它的方案数，那这个方案数是不是就是但此位为0时可以达到的最大值；

如果i比这个最大值还要大的话，此位为0是不是就做不到了。

result：

所以，如果这个方案数比i大，说明排名为i的数一定属于最高位是0的数，否则就属于最高位为1的数。

你就逐位考虑下来就可以了！

这就是运用了二分的思路，对其进行求解。

至于方案数的话，在最开始跑一遍dp就行了，

```
g[i][j] = g[i - 1][j - 1] + g[i - 1][j];
```

就是它为0/1前一位的值相加即可。

code：

```
#include<bits/stdc++.h>//万能头 

using namespace std;

#define maxn 60//可以稍微大一点 
#define int long long//这是个坑 
#define Rep(x, a, b) for(int x = a; x <= b; ++ x)
#define Dep(x, a, b) for(int x = a; x >= b; -- x)

int n, l, k, g[maxn][maxn], sum[maxn][maxn], a[maxn];
//g[k][i]是来表示在前k位中，恰有i个1的二进制数的数量
//sum[k][i]是来表示在前k位中，最多有i个1的二进制数的数量
//a[i]是当前这一位是0/1，输出是用。 

void dfs(int x, int l, int k){
	if(x == 0){//跑到了最后一位了 
		Dep(i, n, 1){//输出路径 
			printf("%d", a[i]);
		}
		exit(0);//不可以用return，return只结束当前这一轮函数，exit(0)就可以直接结束程序。 
	}
	if(k <= sum[x - 1][l]){//如果它小于或等于此位取0时的最大值 
		a[x] = 0;//当前这位就取0； 
		dfs(x - 1, l, k);//并且直接跑到下一位 
	}
	else{//如果它大于的话 
		a[x] = 1;//当前就取1； 
		dfs(x - 1, l - 1, k - sum[x - 1][l]);//并且跑下一位的时候要把还可以取的‘1’的数量-1，然后要跑的数位也会减去这位取了‘1’以后减下的值。 
	}
}

signed main(){
	scanf("%d%d%d", &n, &l, &k);//RT 
	g[0][0] = 1;//初始化，一定要记得 
	Rep(i, 1, n){
		g[i][0] = 1;//如果只要0个‘1’，肯定只有1种方法。 
		Rep(j, 1, n){
			g[i][j] = g[i - 1][j - 1] + g[i - 1][j];//递归求恰有i个1的二进制数的数量
		}
	}
	Rep(i, 0, n){
		Rep(j, 0, n){
			Rep(k, 0, j){
				sum[i][j] += g[i][k];//跑一下求最多有i个1的二进制数的数量
			}
		}
	}
	dfs(n, l, k);//搜索一下就可以了 
	return 0;
}
```

在这里还说一下我前两次Wa在那

First：

[错误1](https://www.luogu.org/record/24308698)

我求sum[ ][ ]的时候，不是从第0位开始跑的。。。

Second：

[错误2](https://www.luogu.org/record/24309273)

没开long longQAQ

Ps：~~请看懂再抄~~

---

## 作者：communist (赞：9)

看到题解里好像都是用$DP$解决的~~，本着禁止DP的原则，~~我来提供一发纯数学~~其实和DP本质相同~~的题解~~，前两天刚反演题，脑子炸了，本来说换换脑子，结果还是数学~~

首先受进制思想启发，我们不妨按位考虑，考虑这一位选一对排列编号造成的影响——即让整个数的编号向后推移了多少

容易想到，这一位选一，编号增加了之后几位满足条件任选的方案数,即第$i$位选一，$cnt$表示前几位选了几个一

$$id+=\sum_{j=0}^{min(i-1,L-cnt)}calc(i-1,j)$$

$clac(x,y)$表示前面$y$位，选$x$位为一的方案数，这个就是一个可重集排列问题，即

$$clac(x,y)=\frac{y!}{x!*(y-x)!}$$

因为$n!$太大会爆$long~long$，所以我们可以使用唯一素数分解定理把阶乘拆成质因子的乘积，然后再乘起来

上代码：

```
#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long
using namespace std;
int pr[10]={2,3,5,7,11,13,17,19,23,29};
int n,k,rk,cnt,ans[50],cp[20];
void add(int x,int c)
{
	//唯一素数分解
    for(int i=1;i<=x;i++)
        for(int tmp=i,j=0;j<10&&tmp>1;j++)
            while(tmp%pr[j]==0)
                tmp/=pr[j],cp[j]+=c;
}
int make(int x,int y)
{
	//可重集排列
    int ret=1;
    memset(cp,0,sizeof(cp));
    add(x,1),add(y,-1),add(x-y,-1);
    for(int i=0;i<10;i++)
        for(int j=1;j<=cp[i];j++)
            ret*=pr[i];
    return ret;
}
signed main()
{
    scanf("%lld%lld%lld",&n,&k,&rk);
    rk--;	//因为有=0的情况，所以rk-1
    if(!rk)
    {
        for(int i=1;i<=n;i++)
            printf("0");
        printf("\n");
        return 0;
    }
    for(int i=n;i;i--)
    {
    	//按位考虑选或不选
        int sum=0;
        for(int j=0;j<=min(i-1,k-cnt);j++)
            sum+=make(i-1,max(j,i-1-j));
        if(rk>=sum)
            rk-=sum,ans[i]=1,cnt++;
    }
    for(int i=n;i;i--)
        printf("%lld",ans[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：7)

题解by：redbag

原题解地址：http://redbag.duapp.com/?p=1420

![](http://redbag.duapp.com/wp-content/uploads/20180804.png)

于是我们先求出所有的方案数。


边界为f[i][0]=1; f[0][i]=1;


很容易发现，不论是哪一位，如果前面一样，那一位为1的话一定比那一位为0的大小大。


所以，如果k>f[i-1][j]的话，第i位一定为1，之后k减去f[i-1][j]，剩下的数重复该操作。


还是看代码吧。也可以画图理解以下。

[code lang="cpp"]

/\*
ID: ylx14271

PROG: kimbits

LANG: C++

\*/

```cpp
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
long long n,m,k,i,j,l;
long long f[50][50];//f[i][j]表示i位数中有j个括号的方案种数
int main() 
{
    freopen("kimbits.in","r",stdin);//抄题解者记得去掉
    freopen("kimbits.out","w",stdout); 
    scanf("%l64d%l64d%l64d",&n,&m,&k); 
    for (i=0;i<=n;i++)//初始值 
    {
        f[i][0]=1;
        f[0][i]=1;
    }  
    for (i=1;i<=n;i++)
    {
        for (j=1;j<=n;j++)
        {
            if (j<=i) f[i][j]=f[i-1][j-1]+f[i-1][j]; //dp求方案数
            else f[i][j]=f[i][i];//再多的1只有那么多位所以方案数还是f[i][i] 
        } 
    }
    i=n;j=m;
    while (i!=0)
    {
        if (k>f[i-1][j]&&k!=0) 
        {
            printf("1");
            k=k-f[i-1][j];//余下的重复操作 
            i--;j--;//各减1继续搜 
        } else //第s+1位为1 
        {
            printf("0");//输出0 
            i--;
        } 
    }
    printf("\n");
    return 0;
}
[/code]
```

---

## 作者：thhhty (赞：6)

花了时间心思打的~希望管理员让过~

小蒟蒻到5.3刷不下去了跑来发个题解~
这道题。。emm用的DP，思路楼下也讲过了
f[i][j]先保存i位中j个一的二进制数的个数
递推式f[i-1][j]+f[i-1][j-1]（第i位0、1的情况加起来）
我是后面在改成f[i][j]是i位不大于j个一（不确定弄在一起会不会出问题，安全为主）
这题是原谅色主要还是输出。。（个人认为）
用了一种神奇的思路。
拿样例开刀：
x==5 19>f[4][3]=15----输出1,19-15
x==4 4<f[3][2]=11----输出0
x==3 4<f[2][2]=7----输出0
x==2 4>f[1][2]=2----输出1,4-2
x==1 2>f[0][1]=1----输出1，2-1
x==0，结束
主要是看这个i是否大于f[x-1][l]
如果第i位选0后面几位都能弄到结果就不用选1了嘛
如果后几位用l个1不能满足，那第i位就只能选1，
再让后面用l-1个1来凑i-f[x-1][l];(因为已经跳过第i位为0的，所以减去f[x-1][l])
之后就没了~（输出成功卡了30min+QAQ）
代码：
```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
long long f[35][35];
void print(long long x,long long k,long long l)
{
    if(x<=0)return;
    if(f[x-1][l]<k&&l>0)//第i位选0不能满足，l还能选（感觉后一个用处不大。。保险还是写了）
    {
        printf("1");
        print(x-1,k-f[x-1][l],l-1);
    }
    else //不然就选0咯（能选尽量选嘛，小的优先）
    {
        printf("0");
        print(x-1,k,l);
    }
}
int mymin(int x,int y){return x<y?x:y;}
int main()
{
    long long n,l,k;
    scanf("%lld%lld%lld",&n,&l,&k);
    memset(f,0,sizeof(f));
    for(int i=1;i<=n;i++)f[i][0]=1;
    for(int i=1;i<=l;i++)f[0][i]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=mymin(i,l);j++)
        {
            if(j<i)
            {
                f[i][j]=f[i-1][j-1]+f[i-1][j];//这里f[i][j]=i位j个1
            }
            else if(j==i)f[i][j]=1;
        }
    }
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=l;j++)f[i][j]+=f[i][j-1];//这里就是i位不大于j个1了
	}
    int max=0;
    print(n,k,l);//输出
    printf("\n");
    return 0;
}
```
这种题目还是独立思考比较好玩的~
（想通了再看就是zz的操作题了）

---

## 作者：宁一 (赞：6)

既然没有人写pascal的题解，那么我来~~（组成头部）~~献一篇拙作……

首先考虑排好序的N(N<=31)位二进制数。

你会发现，这很有趣。因为他们是排列好的，而且包含所有可能的长度为N且含有1的个数小于等于L(L<=N)的数。
你的任务是输出第I（1<=I<=长度为N的二进制数的个数）大的，长度为N，且含有1的个数小于等于L的那个二进制数。
共一行，用空格分开的三个整数N，L，I。

这道题很难，构思巧妙,先用dp求出所要求f[i,j]前i位1的个数不大于j的方案数，然后便是print了。

那么问题来了，~~（挖掘机技术哪家强）~~如何计算f[i,j]。

f[i,j]表示前i位，1的个数不大于j的方案数。

显然：f[i,j]=f[i-1,j]+f[i-1,j-1]

f[i-1,j]表示当前第i位以0开头所得到的方案数,f[i-1,j-1]表示当前第i位以1开头得到的方案数。


如何根据得到的f[i,j]来print呢？如果当前我要确定第i位，那么肯定要看f[i-1]集合中的值判断，例如我当前确定第5位，前4位不超过3个1的方案数为15，而我现在要求第19位，则第5为1，因为19>15，为什么呢？因为第5位可能为0,1，而为0的占了15个，为1的开头也是占15个，显然19属于为1开头的数，所以输出1。

注意：如果答案当前的一位是1，那么有些值也应当改变。1的个数要减一。当前的答案在接下来的01串的序数要减去第一位为0的01串个数。至于为什么请自行考虑。

以此类推...

代码：
```pascal
var
        f:array[0..31,0..31] of longint;
        n,l,i,j:longint;
        k:int64;
procedure print;
begin
        for i:=n-1 downto 0 do
                if f[i,l]<k then
                begin
                        write(1);
                        dec(k,f[i,l]);
                        dec(l);
                end
                else
                write(0);
        writeln;
end;
 
begin
        readln(n,l,k);
        fillchar(f,sizeof(f),0);
        for i:=0 to n do
                f[i,0]:=1;
        for i:=0 to L do
                f[0,i]:=1;
        for i:=1 to n do
            for j:=1 to n do
                f[i,j]:=f[i-1,j]+f[i-1,j-1];
        print;
end.

```

---

## 作者：funky_monkey (赞：3)

## 大家都是递归，我来发个循环版的

```cpp
/*
LGOJ P2727 01串 Stringsobits
主要算法：先算出来C(i,j)的值(递推预处理)，然后再逐位判断这一位是1还是0 
*/ 
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=31+10;
ll C[MAXN][MAXN],n,L,m;//要开long long 因为最大为2^31=max_int+1，开int爆精度 
int main()
{
	scanf("%lld%lld%lld",&n,&L,&m);
	for(int i=0;i<=36;i++) C[i][0]=1;
	for(int i=0;i<=36;i++)
		for(int j=1;j<=i;j++)
		C[i][j]=C[i-1][j-1]+C[i-1][j];//C(i,j)=C(i-1,j-1)+C(i-1,j)
	ll temp1=L;//还剩几个可选 
	ll temp3=n;//操作的是第几位 
	while(temp3>0)
	{
		ll temp2=0;
		for(int i=0;i<=temp1;i++)
		{
			temp2+=C[temp3-1][i];//算出如果这一位要想是1，低位需要先占用的方案个数 
		}
		if(temp2<m)//如果"挨得上"这一位是1 
		{
			m-=temp2;
			temp3--;//将操作指针后移 
			temp1--;//选掉一个1，剩下可选的-1 
			printf("1");
		}
		else//"挨不上"这一位是1 
		{
			temp3--; 
			printf("0");
		}
	}
	printf("\n");
	return 0;
}
```

---

## 作者：Celebrate (赞：3)

这一题先定义数组f表示长度为i并且有j个1的二进制数的总数。

递推公式：f[i][j]=f[i-1][j]+f[i-1][j-1]

f[i-1][j]:第j位放0

f[i-1][j-1]:第j位放1

因为题目说要求不大于的数，所以要把f[i][j]改成长度i并且1的

个数不大于的二进制数的个数

最后for从大到小，没什么好说的二进制吗

详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; 
ll n,m,k;
ll f[51][51];//f[i][j]表示长度为i并且刚好j个1的数的个数 
int main()
{
	ll i,j;
	scanf("%lld%lld%lld",&n,&m,&k);
	for(i=1;i<=n;i++) f[i][0]=1;//一开始不管长度等于多少，放0个1都是0000..... 
    for(i=1;i<=m;i++) f[0][i]=1;//长度0不管放多少个也都是1，这样才可以递推 
	for(i=1;i<=n;i++)//枚举长度
	{
		for(j=1;j<=min(i,m);j++)//枚举1的个数，但是大于m就没有意义了 
		{
			if(j>m) break;//大于就退出（这一句好像可以不用） 
			f[i][j]=f[i-1][j]+f[i-1][j-1];//递推 
		}
		f[i][i]=1;//长度i放i个1就是一种 
	}
	for(i=1;i<=n;i++)//改变f的意义，为最后输出做一个帮助 
	{
		for(j=1;j<=m;j++) f[i][j]=f[i][j]+f[i][j-1];//因为这样可以一直往后叠加 
	}
	for(i=n;i>=1;i--)//二进制需要反过来输出 
	{
		//如果k是多出长度i-1,放m个1的方案数，为什么不是f[i][m]<k呢
		//这里比较难理解
		//因为k是介于i<k<i-1（我指的是方案数）
		//所以k其实是i-1（方案数）多出来的，同时又在i的方案总数以内 
		//如果是f[i][m]<k，那么找的应该是i+1 
		//举个例子，就是说sqrt(n)的整数部分 
		if(f[i-1][m]<k && m>0)//如果可行的话，并且1的数量大于0 
		{
			printf("1");
			k-=f[i-1][m];m--;//k减掉i-1的方案数，用掉一个0，就减去了一个 
		}
		else
		{
			printf("0");//不然就是0 
		}
	}
	printf("\n");
	return 0;
}
```

---

## 作者：csyakuoi (赞：2)

提供一种不同的思路。

从高到低考虑每一位数，用组合数计算这一位为$0$的方案数，并与要求的$i$比较，具体见注释。
```cpp
#include<cstdio>
using namespace std;
unsigned int n;
int mx,len,C[35][35];

int main(void)
{
	scanf("%d%d%u",&len,&mx,&n);
	for(int i=0;i<=len;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}//组合数
	for(int i=len-1;i>=0;i--){
		int t=0;
		for(int j=0;j<=mx;j++)//枚举1的个数
			t+=C[i][j];//计算方案数
		if(n<=(unsigned int)t)
			putchar('0');
		else{
			putchar('1');
			n-=t;
			mx--;//处理当前一位，并更新信息
		}
	}
	putchar('\n');
	return 0;
}
```

---

## 作者：爱喝敌敌畏 (赞：2)

我这么一个蒟蒻！做出绿题啦，先祭一下这一天！（~~你们搜索一下提交记录，满屏全是我的蛙~~）

先讲一下思路吧，定一个数组a[i][j]代表a[i][j]代表长度为i，1的个数小于等于j的二进制个数，先初始将a[1-N][0]=a[0][0-L]=1;并且将a[1][1-L]=2;

然后，不难发现，转移方程为：a[i][j]=a[i-1][j-1](第i位为1的数)+a[i-1][j](第i位为0的数);

重点来了，具体看图！
![原理很好想的！](https://cdn.luogu.com.cn/upload/pic/17427.png)


实现如下：
```cpp
#include<cstdio>
#include<cstring>
using  namespace  std;
int  n,m,l;
long  long  k;
int  ss[210];
long  long  a[40][40];/*a[i][j]代表长度为i，1的个数小于等于j的二进制个数*/ 
int  mymin(int  x,int  y){return  x<y?x:y;}
int  main()
{
     scanf("%d%d%lld",&n,&m,&k);
     a[1][0]=1;
     for(int  i=1;i<=m;i++)
	 {
	 	a[0][i]=1;a[1][i]=2;
	 }
     if(k<=2)//特判，大佬们不要吐槽！ 
     {
     	if(k==1)
     	{
     		for(int  i=1;i<=n;i++)printf("0");
     		printf("\n");
     		return  0;
         }
         else
         {
         	for(int  i=1;i<n;i++)printf("0");
     		printf("1\n");
     		return  0;
         }
     }
     for(int  i=2;i<=n;i++)
     {
     	int  ed=mymin(m,i);
     	a[i][0]=1;
 		for(int  j=1;j<=ed;j++)a[i][j]=a[i-1][j-1]+a[i-1][j];/*状态转移方程*/ 
 		for(int  j=ed+1;j<=m;j++)a[i][j]=a[i][ed];/*为后面着想*/
        if(a[i][ed]>=k)
        {
            l=i;int  dian=m;
            ss[l]=1;
            if(k==a[l-1][dian]+1)k-=a[l-1][dian]+1;
            else  k-=a[l-1][dian];
            --dian;
            if(k!=0)
            {
                for(int  j=l-1;j>=1;j--)/*最精华的循环*/
             	{
             		if(a[j-1][dian]<k-1)
             		{
             			ss[j]=1;
                        k-=a[j-1][dian];
                        --dian;
                     }
                     else  if(a[j-1][dian]+1==k)
                     {
                     	ss[j]=1;
                        break;
                     }
                }
            }
            for(int  j=n;j>=1;--j)printf("%d",ss[j]);
            printf("\n");
            return  0;
        }
     }
     return  0;
}

```

---

## 作者：动物世界 (赞：1)

这道题虽然~~看起来~~并不是非常难，但作为DP蒟蒻，着实费了极大的脑筋……（QAQ）权当对其他题解更详细的说明与补充，也为了纪念与提醒自己，本蒟蒻决定写一篇题解（或者说心得感悟吧）

**首先**  我思考能不能用f[n][L][i][0or1]通过f[n][L][i/2][0or1]<<1或<<1+1的方法直接推出所要答案（emmm我试了将近一个小时），但是始终发现连样例也过不了。什么原因呢？我发现由于L的限制，末尾为1与末尾为0的数个数未必相同，那么也就没有办法通过假想的对半分来推出答案了……（~~看不懂也无所谓，这是一个蒟蒻的自我嘲讽~~）

**那么怎么办呢？**

我们发现，换个思路就能使题目变得很简单。既然第i大的数具体是几很难求，那么长度为n，1的个数为L的数的方案数总是很好求了吧！那我们就先求出方案数。

设f[n][l]表示长度为n，1的个数为l的方案数（注意，这里不是小于等于，而是确切地等于，所有小于等于的方案数是用下面的sum变量存放的）可以用DP，即f[n][l]=f[n-1][l]+f[n-1][l-1]，意思就是可以由已经具有l个1的长为n-1的数<<1而来，也可由已经具有l-1个1的长为n-1的数<<1+1而来；

此外，要是DP理解有困难~~比如我~~，还可以用**组合数**来理解，因为所有的方案数就相当于在n个0中取l个变成1，然后用**杨辉三角形**求解，反正递推式都是一样的。

**OK**，我们已经求出了方案数，那么下面我们应该怎么做呢？我们可以for k=0~n（从0开始，因为0算第一个数，1是第二个数），用sum记下f[k][0~l]的和，用last记下f[k-1][0~l]的和，当sum>=k时，说明此时第i大的数一定大于第last大的数，小于第sum大的数。因此，从右往左数第k位一定为1，否则无法做到恰在中间的某个位置。此时我们用掉了一个1，将l减1，可用的位数也少了1，将n减1。至于i，将其减去当第k位为0的方案数，此时i就等于除去第k位不看，其它符合条件的数的方案数，然后继续做下去即可。最终得到一个ans数组，再将它依次输出即可。

**注意两个坑点**，第一个是要求二进制数的长度为n，最高位是0也没有关系，第二个是注意一下0也算一个（这么说就是有可能爆int的。。）

下面是代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long f[40][40];
int ans[40];
int N,L;
long long I;
void work(int n,int l,long long p){
    if(l==0) return;
    long long last=0;
    for(int i=0;i<=n;i++){
        long long sum=0;
        for(int j=0;j<=l;j++) sum=sum+f[i][j];
        if(sum>=p){
            ans[i]=1;
            work(n-1,l-1,p-last);
            return;
        }
        last=sum;
    }
}
int main(){
    cin>>N>>L>>I;
    f[0][0]=1;
    for(int i=1;i<=N;i++){
        f[i][0]=1;
        f[i][i]=1;
        for(
		int j=1;j<i;j++){
            f[i][j]=f[i-1][j-1]+f[i-1][j];
        }
    }
    work(N,L,I);
    for(int i=N;i>=1;i--) cout<<ans[i];
    cout<<endl;
    return 0;
}

```
第一次写题解，难免疏漏，请大佬们批评指正！

---

## 作者：Bzy_temp (赞：1)

**看大家都在DP中，那我就发一个暴力出奇迹的方法→0ms**




```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;//流操作命名空间 
void H_2(int f,int w){bool h[32];for(int i=0;i<=w-1;i++){h[i]=f&1;f=f>>1;}for(int i=w-1;i>=0;i--)cout<<h[i];}
//输出答案函数 
int mp[32][32];//预处理组合数 
int main(){
    int a,b,c,i;cin>>a>>b>>c;//输入 
    for(i=0;i<=31;i++){mp[i][0]=1;for(int j=1;j<=i-1;j++)mp[i][j]=mp[i-1][j]+mp[i-1][j-1];mp[i][i]=1;}//用杨辉三角预处理组合数 
    for(i=0;i<=31;i++)for(int j=1;j<=i;j++)mp[i][j]+=mp[i][j-1];//得到同一排组合式的前缀和 
    int va=0;int al=0;//va总共数字数//al符合的数字数 
    while(1){
        //每一回求最高位//方法：找到到这一位时的符合数字的总数不大于c
        //所找到的数为mp[i][min(i,b)]//及当前可用位数的组合数 
        for(i=0;i<=a;i++){
            if(al+mp[i][min(i,b)]>c){
                i--;//若大于就减一退出 
                al+=mp[i][min(i,b)];//符合总数加上组合数 
                break;
            }
            else if(al+mp[i][min(i,b)]==c){
                va+=pow(2,i);//若等于就加上 2的i次幂为遍历的数字 
                al+=mp[i][min(i,b)];H_2(va-1,a);return 0;//去除/加上第一个0的情况 
            }
        }
        b--;//每回可用位数减一 
        va+=pow(2,i);//加上总数 
    }
    return 0;
}

```

---

## 作者：brealid (赞：0)

一道可以使用数论解决的思维题。

## 思路分析

思路：设 $n$ 位中 $1$ 的个数小于等于 $m$ 的 01串 的可能情况数为 $get(n, m)$

那么可以得出一个程序流程：  
> 1. 读入 $n,l,k$  
> 2. 从最高位（设为第 $n$ 位）开始向最低位（设为第 $1$ 位）枚举（枚举变量：$i$）  
> >	1. 计算 $get(i-1, l)$ （即 : 若高位确定，这一位为 $0$，可能的方案总数）  
> > 2. 判断 $get(i-1, l)>k$ 的真假  
> > >  	- true: 易知 $01$ 串的这一位为 $0$  
> > >   - false: 易知 $01$ 串的这一位为 $1$，并 $k=k-get(i-1, l)$
> > 3. 输出这一位
> 3. 结束程序      

上方时间复杂度为 $O(n)$ 即 $O(N)$

现在问题为怎么求 $get(n, m)$

其实很简单， 
$$get(n, m)=\sum_{i=0}^{m}C(n, i)$$
唯一一个注意点：$i$ 要从 $0$ 开始枚举，因为全 $0$ 串也是符合条件的。（时间复杂度 $O(m)$ 即 $O(L)$）

然后求 $C(n, i)$

传统做法是 $C(n, i)=\dfrac{n!}{(n-m)!m!}$。尽管这题求出来的 $C(n, i)$ 一定在 $long\ long$ 范围内，但这样中间过程可能会爆 $long\ long$。

所以提供一种不会溢出的方法：
```cpp
typedef long long int64;
int64 C(int64 n, int64 m)
{
    int64 res = 1;
    for (int i = 1; i <= m; i++) {
        res *= (n - i + 1);
        res /= i;
    }
    return res;
}
```
(时间复杂度 $O(m)$ 即 $O(L)$）

可以自行理解一下这样做为什么是对的（即，为什么每次都能整除）

## 时间复杂度分析

易知时间复杂度为 $O(N) * O(L) * O(L)= O(NL^2)≈2^{15}≈32768$, 妥妥的

## Code 
现在解决了所有问题，该放代码了
```cpp
/*************************************
 * problem:      P2727 01串 Stringsobits.
 * user ID:      63720.
 * user name:    Jomoo.
 * time:         2019-11-09.
 * language:     C++.
 * upload place: Luogu.
*************************************/ 

#include <bits/stdc++.h>
using namespace std;

typedef signed char          int8;
typedef unsigned char       uint8;
typedef short                int16;
typedef unsigned short      uint16;
typedef int                  int32;
typedef unsigned            uint32;
typedef long long            int64;
typedef unsigned long long  uint64;

template <typename Int>
inline Int read()       
{
    Int flag = 1;
    char c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline Int read(char &c)       
{
    Int flag = 1;
    c = getchar();
    while ((!isdigit(c)) && c != '-') c = getchar();
    if (c == '-') flag = -1, c = getchar();
    Int init = c & 15;
    while (isdigit(c = getchar())) init = (init << 3) + (init << 1) + (c & 15);
	return init * flag;
}

template <typename Int>
inline void write(Int x)
{
    if (x < 0) putchar('-'), x = ~x + 1;
    if (x > 9) write(x / 10);
    putchar((x % 10) | 48);
}  

template <typename Int>
inline void write(Int x, char nextch)
{
    write(x);
    putchar(nextch);
}

int64 n, l, k;
int64 C(int64 n, int64 m)
{
    int64 res = 1;
    for (int i = 1; i <= m; i++) {
        res *= (n - i + 1);
        res /= i;
    }
    return res;
}

int64 get(int64 n, int64 m) {
    int64 res = 0;
    for (int i = 0; i <= m; i++) res += C(n, i);
    return res;
}

int main()
{
    cin >> n >> l >> k;
    k--; //注意一下这一句，因为按我的逻辑求出来的实际是第 k + 1 名，所以需要减 1
    for (int i = n, t; i >= 1; i--) {
        t = get(i - 1, l);
        if (k >= t) {
            k -= t;
            l--;
            putchar(49);
        } else putchar(48);
    }
    return 0;
}
```

---

## 作者：Thaumaturge (赞：0)

今年3月份看到这道题的时候还一筹莫展。。。。

以下是一个菜鸡的思考过程：

考虑题目里已经说了，这些数是由大到小排好序的，所以答案必定随i的增大而增大，这样就很显然可以用类似树上倍增的方法逐步确定答案。设当前答案为$ans$考虑从高位开始，逐步确定每个位应不应该填。如果填了后，在$1$～$ans$中，符合条件的数仍小于等于$l$，则可以填，否则不填。因为我们要始终保证$ans$小于等于最终的答案

使用类似P2657的方法，设$f[i][j][0]$表示从高位到低位已经填了$i$位，其中有$j$位为0，且所填的数必定小于$m$。$f[i][j][1]$表示从高位到低位已经填了$i$位，其中有$j$位为0，且$bitnum(i,j)==bitnum(m,j)$。转移方程就可以列出来了：

$f[i][j][0]=f[i-1][j-1][0]+f[i-1][j][0]+f[i-1][j][1]$

$f[i][j][1]=[bitnum(m,i)==j,j<=l]$

其中$bitnum(x,y)$表示数x在从高到低的前y位中位上为1的数量，保证f数组中的数都符合要求

可以看出来，$f[i][j][1]$其实可以用一个变量代替的，因为本人习惯不太好，就没有切掉这一维。。。

还有一些需要注意的地方：

1. 之前的大佬已经已经说过了，输入的数是会爆int的，最好用uint（我偷懒用了long long）

2. 必须注意，填数前必须保证当前的$ans$的位上为$1$的位数小于等于$l$，不然就会出现因为新增答案恰好为$0$而导致的错误判断。正确性显然，因为题目是保证有解的（没有给出无解的情况该输出什么）

其他的看代码吧:

```
#include <bits/stdc++.h>

#define N 60
#define int long long

using namespace std;

int n,l,m;

int f[N][N][2];

int ans;

//多dp几次，就能确定答案的0的位置


//我永远讨厌数位dp！！！！！！！

inline int read(){
	int x=0;char c=getchar();bool y=1;
	for(;c<'0' || c>'9';c=getchar()) if(c=='-') y=0;
	for(;c>='0' && c<='9';c=getchar()) x=(x<<1)+(x<<3)+c-48;
	if(y) return x;
	return -x;
}

inline bool check(int x){
	memset(f,0,sizeof(f));
	int now=0,ask=0;
	f[0][0][1]=1;//这么初始化是因为一开始没有位数时显然与m相等，如果是f[0][0][0]就会因0不受限制而到处乱转
	for(int i=1;i<=n;i++)
	{
		if((x>>(n-i))&1) now++;
		for(int j=0;j<=min(i,l);j++)
		{
			if(j>0)
			f[i][j][0]+=f[i-1][j-1][0];
			
			f[i][j][0]+=f[i-1][j][0];
			if((x>>(n-i))&1)//这一位是否为1，为1才能保证当前位可以填0从而摆脱对当前数必须小于等于m的限制，转到f[i][j][0]中
			f[i][j][0]+=f[i-1][j][1];
		}
		if(now<=l) f[i][now][1]=1;
	}
	for(int i=0;i<=l;i++)
	ask+=f[n][i][0]+f[n][i][1];
	return (ask<=m);
}

int control=0;

signed main(){
	n=read(),l=read(),m=read();
	for(int i=n;i>=1;i--)//逐步求出满足答案所需要的最小的0的位数
	{
		if(check(ans+(1<<(i-1))) && control+1<=l) ans+=1<<(i-1),control++;
	}
	for(int i=n-1;i>=0;i--)
	printf("%lld",(ans>>i)&1);
	return 0;
}
```


---

## 作者：crashed (赞：0)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problem/P2727)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;一言以蔽之——好题！  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先，我们不难想到，用$f(i,j)$表示长度为$i$的$01$串里面有$j$个$1$的组合方案数，可以发现就是组合数的转移方式~~所以转移就偷懒不写了~~。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;然后记$s(i,j)=\sum_{k=0}^jf(i,k)$，这个很有用。怎么有用呢？~~请听下回分解~~  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;注意！$s$数组是需要开$long\ long$的。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;下面我们开始从高到低来构造这个$01$串。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其实只有一个问题需要解决——如何判断第$i$位上需不需要放$1$？  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;假如已知后$i$位的排名为$r$。在第$i$位上出现$1$,就说明后$i-1$位就算排满走一遍，也无法累积出$r$，所以进位了。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;判断$r$是否**大于**$s(i-1,\min\{i-1,L\})$，如果大于就说明需要进位，第$i$位就得是$1$。然后$L$和$r$都得减少，这个就~~懒一下~~不说透了，看代码吧。  
# 代码
```cpp
#include <cstdio>

typedef long long LL;

const int MAXN = 40, MAXL = 40;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

LL DP[MAXN][MAXL], s[MAXN][MAXL];
LL indx;
int N, L;
char res[MAXN];

void init()
{
	DP[0][0] = 1;
	s[0][0] = 1;
	for( int i = 1 ; i <= N ; i ++ )
	{
		DP[i][0] = DP[i][i] = 1;
		s[i][0] = 1;
		for( int j = 1 ; j < i && j <= L ; j ++ )
		{
			DP[i][j] = DP[i - 1][j] + DP[i - 1][j - 1];
			s[i][j] += s[i][j - 1] + DP[i][j];
		}
		s[i][i] = s[i][i - 1] + DP[i][i];
	}
}

int main()
{
	read( N ), read( L ), read( indx );
	init();
	for( int i = N ; i >= 1 ; i -- )
	{
		if( indx > s[i - 1][MIN( L, i - 1 )] )
		{
			res[N - i + 1] = '1';
			indx -= s[i - 1][MIN( L, i - 1 )];
			L --;
		}
		else res[N - i + 1] = '0';
	}
	puts( res + 1 );
	return 0;
}

```

---

## 作者：Sarah (赞：0)

我发一个乱搞题解给大家拓展下思路：
初看题目，我第一眼没看出来是dp（逃），认真读题目之后觉得需要一个函数get_num（x），返回值是小于等于x的数中多少个数是不符合条件的（即有多少个数的二进制形式含有'1'的个数超出了题目所给的'L'）于是解题过程是一开始将题目中的'i'减1（因为0也算进了排名）；然后设置一个前驱pre代表着i是从pre这个数得来的。每i表示去掉了get_num(pre)时的答案。但是很显然这个答案是不一定对的，因为pre到i之间的不符合条件的数还没有被去掉，所以需要不停迭代，过程如下
```cpp
i--;
int pre=0;
while(get_num(i)!=pre){
	int p=pre;
	pre=get_num(i);
	i+=(get_num(i)-p);
}
```
再说get_num(x)这个函数如何实现，看代码吧
```cpp
long long get_num(long long x){
	long long ans=0,digit_cnt=0;
	for(int k=n-1;(1<<k)>0;k--){
		if((1<<k)&x){
			for(int i=l+1-digit_cnt;i<=k;i++){
				if(i>=0)
					ans+=c[k][i];//这里的c[k][i]就是组合数学中的kCi
			}
			digit_cnt++;
		}
	}
	if(digit_cnt>l)
		ans++;
	return ans;
}
```
完整代码
```cpp
/*
ID: z8493331
LANG: C++
TASK: kimbits
*/
#include<iostream>
#include <cstdio>
#include <cstring>
using std::cout;
using std::endl;
long long n,i,l;
long long c[200][200];
void init(){
	scanf("%d %d %lld",&n,&l,&i);
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i;j++){
			c[i][j]=c[i-1][j-1]+c[i-1][j];
			//c[i][j]+=c[i][j-1];
		}
	}
}
long long get_num(long long x){
	long long ans=0,digit_cnt=0;
	for(int k=n-1;(1<<k)>0;k--){
		if((1<<k)&x){
			/*if(l+1-digit_cnt<0)
				ans+=(c[k][k]);
			else
				ans+=(c[k][k]-c[k][l+1-digit_cnt-1]);*/
			for(int i=l+1-digit_cnt;i<=k;i++){
				if(i>=0)
					ans+=c[k][i];
			}
			digit_cnt++;
		}
	}
	if(digit_cnt>l)
		ans++;
	return ans;
}
void process(){
	i--;
	int pre=0;
	while(get_num(i)!=pre){
		int p=pre;
		pre=get_num(i);
		i+=(get_num(i)-p);
	}
	for(int k=n-1;k>=0;k--){
		if((1<<k)&i){
			cout<<"1";
		}else{
			cout<<"0";
		}
	}
	cout<<endl;
}
int main(){
	freopen("kimbits.in","r",stdin);
	freopen("kimbits.out","w",stdout);
	init();
	process();
	return 0;
}
```

---

