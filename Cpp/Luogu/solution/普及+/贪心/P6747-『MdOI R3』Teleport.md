# 『MdOI R3』Teleport

## 题目背景

凯瑞甘从帝国的围攻下，击毁了大天使号，乘着雷诺的飞船逃了出来，到了休伯利安号上。

“吉米？”凯瑞甘着急地四处寻找着。

“很抱歉，我们没能救出他”马特·霍纳向凯瑞甘走来。

“你丢下了他？”凯瑞甘回想起曾经的自己被蒙斯克丢下，便起了杀心，用灵能将马特抓了起来。

“不是的，凯瑞甘，我们受到了帝国的伏击，现在必须，马上离开，过会可以回头来找他”马特解释道。

“这里没有我们！你走吧，我自己去找他。”凯瑞甘放下了马特，回头坐着雷诺的回到了星球上。

“警告，警告，敌军突破能量场。”帝国的舰队突破了马特舰队设下的能量场，控制着钢铁舰队折越到了这里，并对休伯利安号发起猛烈的攻击。

“立即进行折越，我们必须马上离开！”马特·霍纳下令道。

## 题目描述

马特·霍纳想要控制休伯利安号进行折越，想要进行折越，就要激活休伯利安号上的所有 $n$ 个位点。

休伯利安号上有 $n$ 个位点，每个位点有 $a_i$ 点能量，为了激活，马特·霍纳会消耗 $k\times n$ 点地嗪，这 $k\times n$ 点地嗪会平均分给 $n$ 个位点，每个位点在接受 $k$ 点地嗪后会激发，得到 $a_i \operatorname{xor} k$ 点高能，所有位点的高能总和为这次折越的消耗 $S$。

为了能够快速的进行折越，马特·霍纳决定用最多的 $k\times n$ 点地嗪，但可惜的是，如果地嗪使用太多，使得消耗 $S$ 超过限制值 $m$ ，那么休伯利安号就会不堪重负，最终爆炸。

现在，你的任务是帮助马特·霍纳找到这个最大的 $k$ ，使得休伯利安号能在安全的前提下尽可能快的折越走。如果任何情况下都不能安全的折越走，则输出 $-1$ 。

这里的 $\operatorname{xor}$ 表示的是位运算中的按位异或运算。

## 说明/提示

对于第一个询问，最大的 $k$ 为 $3$ ，此时 $S=2+1+0=3 \le 10$ ，可证没有更大的 $k$ 满足条件。

对于第二个询问，没有任何 $k$ 满足条件。
|数据点  |$n$  |$a_i$  | $m$ | $q$ |
| :------: | :------: | :-------: | :-------: | :----------: |
|$1$|$\le 10$|$\le 2^{20}$| $\le 2^{20}$| $=1$ |
|$2$| $\le 10^3$|$\le10^3$|$\le10^3$|$\le 10^3$|
|$3$|$\le 10^3$  | $\le 2^{30}$ | $\le 10^3$ | $\le 10^3$ |
|$4\sim 6$| $\le 10^5$| $\le 2^{20}$ | $\le 10^6$ | $\le 10^5$ |
|$7\sim 10$| $\le 10^5$ | $\le 2^{30}$ | $\le 2^{30}\times10^6$ | $\le 10^5$ |
**本题不进行捆绑测试。**

所有测试点的数据范围如上所示。对于所有数据，$0<n,q\leq 10^5,\ 0\leq a_i\leq 2^{30},\ 0\leq m\leq 2^{30}\times 10^6$。

## 样例 #1

### 输入

```
3
1 2 3 
2 
10 
1```

### 输出

```
3
-1```

## 样例 #2

### 输入

```
1
0
1
1073741824000000```

### 输出

```
1073741824000000```

# 题解

## 作者：infinities (赞：11)


异或计算方法：两个数二进制下按位比较，相同返回 0，不同返回 1。

首先看数据范围，答案和各种输入的变量都不会爆 long long，于是就可以放心做了。

考虑到有位运算和 $q \le 10^5$ 的数据范围，可以想到一定要按二进制下每一位来进行计算。

要使得 $k$ 尽可能大，且 $\sum_{i=1}^na_i\operatorname{xor}k \le m$。

我们可以按位进行贪心，即先统计 $a_i$ 每一位上 0 和 1 的个数，然后设 $a_i$ 中二进制下位数最多的一个的位数为 $maxx$，则我们对于 $k$ 的每一位，若 1 的个数比较多 $k$ 的这一位就是 1，反之亦然。

这样我们就能保证这时候的 $k$ 会使得 $S$ 最小，于是就可以开始贪心了。

接下来解决判断无解。判断无解即看 $S$ 最小时是否还大于 $m$，大于就无解，否则就可以接着做。

贪心的方法是从高到低贪，如果这一位是 0，我们就看能不能把它变成 1，判断的标准是这一位变成 1 之后当前是否还满足 $S \le m$，满足就可以贪，否则不能。



把一位变成 1 的方式可以使用异或，具体方式可以见代码。

最后还有一些代码实现上的小细节，可以看代码和注释。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define rint regester int
const int maxn = 1e6 + 10;
const int INF = 1e9;
using std::ios;
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::sort;
using std::unique;
using std::lower_bound;
using std::swap;
using std::abs;
using std::acos;
using std::queue;
using std::map;
using std::string;
int read(){
    int x = 0,f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
int n, q, a[maxn], num01[233][2], maxsize;
signed main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		a[i] = read();
		int aa = a[i];
		if(aa == 0)maxsize = max(maxsize, 1ll);//特判为0的情况，如果只有一个数且为0那就必须得特判
		for(int i = 1; aa; aa = aa >> 1, i++){
			maxsize = max(maxsize, i);//求出最大位数
			++num01[i][aa & 1];//统计每一位的0/1个数
		}
	}
	for(int i = 1; i <= maxsize; i++){
		num01[i][0] = n - num01[i][1];//因为有的数高位全是0，所以要这样计算一下
	}
	q = read();
	for(int i = 1; i <= q; i++){
		int m = read(), kmax, qwq = 0;
		int k = 0, fl = 0;//fl用来判无解
		for(int j = maxsize - 1; j >= 0; j--){
			if(min(num01[j + 1][1], num01[j + 1][0]) * (1ll << j) > m){
			    cout << -1 << "\n";
			    fl = 1;
			    break;
			}
		}//这一段判无解似乎也可以删了，但是我比较懒，所以就留着了
		if(fl == 1)continue;
		for(int j = maxsize; j >= 1; j--){
			if(num01[j][1] > num01[j][0])k = (k ^ (1ll << (j - 1)));//用异或解决把一位变成1
			qwq = qwq + min(num01[j][1], num01[j][0]) * (1ll << (j - 1));//贪心使S最小
		}
		if(qwq > m){
			cout << -1 << "\n";
			fl = 1;
		}
		if(fl == 1)continue;
		kmax = maxsize;
		for(int j = maxsize; ; j++){
			if(qwq + n * (1ll << j) <= m)kmax = j + 1;//先从高位贪心，顺便记录一下k的最高位
			else break;
		}
		if(kmax > maxsize)k = (k ^ (1ll << (kmax - 1))), qwq += n * (1ll << (kmax - 1));
		//这里要特判k的最高位在a_i的最高位之上再把这一位变成1，否则会出错
        for(int j = kmax; j >= 1; j--){//贪心看能不能把0变成1
			if(!(k & (1ll << (j - 1)))){
				if(j > maxsize){
					if(qwq + n * (1ll << (j - 1)) <= m){
						qwq += n * (1ll << (j - 1));
						k = k ^ (1ll << (j - 1));
					}
				}else
				if(j <= maxsize){
					if(qwq + (num01[j][0] - num01[j][1]) * (1ll << (j - 1)) <= m){
						qwq += (num01[j][0] - num01[j][1]) * (1ll << (j - 1));
						k = k ^ (1ll << (j - 1));
					}
				}
			}
		}
		cout << k << "\n";
	}
} 
```

---

## 作者：Rubidium_Chloride (赞：9)

2020.8月月赛C题题解。

## 0.前言

[$\color{Red}{\text{在}}\color{orange}\text{博}\color{yellow}\color{green}\text{客}\color{Turquoise}\text{里}\color{blue}\text{看}\color{purple}\color{Red}\text{效}\color{orange}\text{果}\color{yellow}\text{更}\color{green}\text{好}\color{Turquoise}\text{哦}\color{blue}!$](https://www.luogu.com.cn/blog/Rolling-blog1424/solution-p6747)

接下来我们开始啦：

## 1.题目大意

- 有 $n$ 个数 $a_1,a_2\dots a_{n-1},a_n$；

- 有 $q$ 次问询，每次问询给定一个非负整数 $m$，求最大的非负整数 $k$，使得总高能值不超过 $m$，如果不存在这样的 $k$，输出 $-1$；

- 当上一条中的 $k=k_0$ 时，总高能值 $S$ 计算如下：

$$S=\sum\limits_{i=1}^{n} a_i\operatorname{xor} k_0$$

其中 $\operatorname{xor}$ 代表按位异或；

- $0<n,q\le 10^5,0\le a_i\le 2^{30},0\le m \le 2^{30}\times 10^6$。

PS：经过计算器的计算，确认 $2^{30}\times 10^6$ 就是题目中所给的 $1073741824000000$，而 $2^{50}$ 是 $1125899906842624$，也就是说 $2^{30}\times 10^6<2^{50}$。

也就是说，二进制位最多只要考虑 $51$ 位就可以了（为下文做一点铺垫）。

下文中的二进制第 $i$ 位均表示单位为 $2^{i-1}$ 的位。

## 2.算法分析

首先，我们能够轻易地发现，$a_i$ 和 $k$ 的每一个二进制位都是独立的。

而且问询要的结果是 $k$ 的最大值。

于是，我们想到了**按位贪心**。

那么，怎么贪呢？

首先，我们先统计两个数据：$s_{i,1}$ 和 $s_{i,0}$，其中 $i=0,1,2\dots 50,51$，$s_{i,1}=\sum\limits_{j=1}^{n} \left[\dfrac{\left(a_j \operatorname{xor} 2^i\right) \bmod 2^i}{2^i}\right]\times 2^i$，而$s_{i,0}=\sum\limits_{j=1}^{n} \left[\dfrac{\left( a_j\operatorname{xor} 0\right) \bmod 2^i}{2^i}\right]\times 2^i$。

有人可能会问上面两个式子的实际含义。说起来很简单。

$s_{i,1}$ 就是 $a_1,a_2\dots a_{n-1},a_n$ 分别与 $2^i$ 异或后取二进制第 $i+1$ 位的值乘以 $2^i$ 的和，也就是取 $k$ 的二进制第 $i+1$ 位为 $1$ 该位能够提供的高能值总和。

$s_{i,0}$ 就是 $a_1,a_2\dots a_{n-1},a_n$ 分别与 $0$ 异或后，取二进制第 $i+1$ 位的值乘以 $2^i$ 的和，也就是取 $k$ 的二进制第 $i+1$ 位为 $0$ 的时候该位能够提供的高能值总和。

接下来我们要考虑一个问题：在按位贪心的时候，如何判断该方案是否可行？

这个不太难，假设我们已经统计到第 $i$ 位，如果即使以后的位数全部选择最小的 $s$，也超过了界限 $m$，那么这种方案一定不行。

所以我们预处理一个数组 $mn$，其中 $mn_i=\sum\limits_{j=0}^{i} \min(s_{j,0},s_{j,1})$。

基本的思路就是这样。我会在代码里另外注明一些细节。

如果每一个问询依次处理的话，复杂度大概是 $\Theta(50(n+q))$。

据说有可以将所有问询全部放在一起然后一遍处理的做法？但是我没有想出来。如果有大佬想出来的话请务必让我学习一下。

## 3.Code

PS：由于本人过懒，不想特判一些情况，就直接使用了`__int128`，请各位见谅。

```cpp
#include<bits/stdc++.h>
#define N 100009
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;
typedef __int128 ll;
inline ll read() {
    ll x=0,f=1;int c=getchar();
    while(!isdigit(c)) {if(c=='-') f=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*f;
}
ll n,q,a[N],p[69]={1},s[69][2],mn[69];
//a[i]记录初始数值，p[i]记录2的i次幂，s[i][1]统计选中第i位能够获得的高能值,s[i][0]则是统计不选第i位能够获得的高能值
ll solve(ll k){//按位贪心，结果不能超过k 
	ll ans=0,tot=0;//ans代表能够达到的最大值，tot表示当前的总高能值 
	for(int i=51;i>=0;i--){//每一位单独考虑 
		if(tot+mn[i]>k) return -1;//如果不能再选，输出-1 
		if(i&&s[i][1]+mn[i-1]+tot<=k){tot+=s[i][1],ans+=p[i];continue;}//如果可以选择那一位，更新最大值并加上高能值 
		if(i&&s[i][0]+mn[i-1]+tot<=k){tot+=s[i][0];continue;}//不能选择那一位，更新
		if(!i&&s[i][1]+tot<=k){return ans+1;}//如果到了尽头，直接返回 
	}
	return ans;
}
inline void print(ll x){
	if(x<0){putchar('-');x=-x;}
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	n=read();
	for(int i=1;i<=61;i++) p[i]=p[i-1]*2;//预计算2的次幂 
	for(int i=1;i<=n;i++){
		a[i]=read();
		for(int j=0;j<=51;j++) s[j][!((a[i]&p[j])>>(ll)j)]+=p[j];//预先统计这一位，能够获得多少高能值
	}
	mn[0]=min(s[0][0],s[0][1]);
	for(int i=1;i<=51;i++) mn[i]=min(s[i][0],s[i][1])+mn[i-1];//统计前缀最小值的和 
	q=read();
	for(ll i=1,m;i<=q;i++){
		m=read();
		print(solve(m));//按位贪心 
		printf("\n");
	}
	return 0;
}
```

## 4.结语

终于把C的题解淦完了。

还是那句话，希望月赛越办越好！

---

## 作者：monstersqwq (赞：5)

~~来自一位场上被卡精度到40分的菜鸡选手的题解~~

### 题意：

给出 $n$ 个数字 $a_i$，并 $q$ 次询问对于每次给定的 $m$，$k$ 的最大值使得 $\sum\limits_{i=1}^n{a_i \oplus k}\le m$。

### 题解：

约定：$k$ 的第 $i$ 位表示 $k$ 的二进制表示中从右往左的第 $i$ 位。

首先我们来证明一个东西：

$$k\text{的二进制位数}\le\max(m\text{的二进制位数},\min\limits_{i=1}^{n}{a_i\text{的二进制位数}})$$

其中这个二进制位数也可以表示为 $\left\lfloor\log_2{k}\right\rfloor+1$

这东西可以用反证法证：如果取到了大于的话那么 $k$ 的二进制最高位是 $1$，但是最小的 $a_i$ 同样的位置为 $0$，所以异或后为 $1$，但 $m$ 相同位置是 $0$，且更高位也是 $0$，所以一定有总贡献 $S>m$。

然后再考虑怎么求出最大的 $k$。

因为异或同其它大部分位运算一样，每位答案只同该位的数有关系，所以我们考虑拆位计算贡献，对于 $k$ 的第 $i$ 位，若取 $1$，则贡献为：

$$\sum\limits_{j=1}^n{1}\ (a_j\text{的第}i\text{位为}0)\times 2^{i-1}$$

取 $0$ 则为：

$$\sum\limits_{j=1}^n{1}\ (a_j\text{的第}i\text{位为}1)\times 2^{i-1}$$

前面的求和可以在输入时用桶记录一下优化一波。

为了取得更大的 $k$，考虑贪心，从最高位开始枚举能取 $1$ 就取 $1$，不能取就取 $0$，但是这样做有个问题，如果当前位取 $1$ 无论如何都无法满足要求，但是取 $0$ 可以满足就不行了，所以这个贪心需要反悔，可以考虑使用 dfs 来完成这个问题：从最高位开始枚举，先选择取 $1$，不行再选择取 $0$，能取到的第一个解自然是最大的最优解。（这里应当可以自行证明）

这个 dfs 复杂度看起来高，但是因为会剪枝掉一些以及只需查找到第一个解所以跑的还蛮快，不会超时。

关于最高位的位数：$\log_2 2^{30}\times 10^6$ 约为 $30+20=50$ 所以 $m$ 二进制位最多有 $51$ 位，设到 $52$ 左右即可。

然后就是计算贡献与 $m$ 的大小时最大 $10^5\times 2^{51}$ 会爆 ll，所以可以使用 double 或 int128 来规避这个问题。

程序效率不错，总用时不吸氧可以到 $700ms$ 左右（所以 dfs 真是玄学复杂度）

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
#include <map>
using namespace std;
typedef long long ll;
ll n,a[100005],q,t[55],m,ans,poww[55];
bool flag=false;
void tong(ll x)
{
	for(int i=1;i<=52;i++)
	{
		if(x==0) break;
		if(x%2==1)
		{
			t[i]++;
		}
		x/=2;
	}
}//开桶统计一下
void dfs(int w,ll x)
{
	if(flag) return;
	if(w==0)
	{
		printf("%lld\n",ans);
		flag=true;
		return;
	}
    ans+=poww[w-1];
    if(double(x)+double(n-t[w])*double(poww[w-1])<=double(m))//转化一下double
	dfs(w-1,x+(n-t[w])*poww[w-1]);
    ans-=poww[w-1];
    if(double(x)+double(t[w])*double(poww[w-1])<=double(m))
	dfs(w-1,x+t[w]*poww[w-1]);
}
int main()
{   
    poww[0]=1;
    for(int i=1;i<=52;i++)
        poww[i]=poww[i-1]*2;//预处理一下2的幂
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		tong(a[i]);
	}
	scanf("%lld",&q);
	for(int i=1;i<=q;i++)
	{
		flag=false;
        ans=0;
		scanf("%lld",&m);
		dfs(52,0);
		if(!flag) printf("-1\n");//判无解
	}
	return 0;
}
```


---

## 作者：Mophie (赞：5)

做法各位大佬讲的都十分清晰了，就是把每个数做成二进制，按位贪心。

这里来讲一些常数的小优化。

**P.S:现在为第二优解**

#### 优化1：

我们可以先将最优的情况讨论出来，即消耗的最小值。

如果输入的 $m$ 都已经是小于这个最小值了的话，可以直接跳出。

最小值可以按位来算，显然对于最后结果的每一位来讲，他最后消耗的最小数是这个位上的 $0$ 和 $1$ 个数的最小值。

可能有点绕，再配上这个代码来理解吧。

```cpp
for(int i=1;i<=qwq;i++)
        cal[i]=cal[i-1]+min(p[i][0],p[i][1])*mult[i];//muit[i]=2^i,p为每一位0或1的个数
```

#### 优化2：

如果当 $m$ 很大时，一些算法就会跑的很慢，甚至会爆精度。

所以来看一下该如何优化它。

我们先可以计算出最小值，而现在不已经有现成了的吗——$cal[i]$

设最高有 $qwq$ 位。

那么如果 $m$ 减去 $cal[qwq]$ 后还能够大于 $2^{qwq+1}*n$，那么就可以在 $2^{qwq+1}$ 后面的位置上放进数字。

显然 $k$ 越大越好，所以高位的数越多越好。最后处理即可

可能讲的还是有点晕乎乎，大家配合代码来理解吧……

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read()
{
	long long sum=0,naga=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')naga=-1;ch=getchar();}
	while(ch<='9'&&ch>='0')sum=sum*10+ch-'0',ch=getchar();
	return sum*naga;
}
inline void write(long long X)
{
	if(X<0)putchar('-'),X=-X;
	if(X>9)write(X/10);
	putchar(X%10+'0');
}
long long kkk,ans,qwq,zxy,n,mult[59],p[59][2],a[100009],cal[59],Q,m;
int main()
{
    n=read();
    mult[0]=1;
    for(int i=1;i<=55;i++)mult[i]=mult[i-1]*2;
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        zxy=0;
        kkk=a[i];
        while(kkk)
        {
            zxy++;
            kkk/=2;
        }
        zxy--;
        if(qwq<zxy)qwq=zxy;
    }
    for(int i=1;i<=n;i++)
    {
        zxy=0;
        while(zxy<=qwq)
        {
            p[zxy++][a[i]%2]++;
            a[i]/=2;
        }
    }
    cal[0]=min(p[0][0],p[0][1]);
    for(int i=1;i<=qwq;i++)
        cal[i]=cal[i-1]+min(p[i][0],p[i][1])*mult[i];
    Q=read();
    for(int i=1;i<=Q;i++)
    {
        ans=0;
        m=read();      
        if(m<cal[qwq])
        {
            puts("-1");//不可能的状态
        }
        else
        {
            if(m>=cal[qwq]+mult[qwq+1]*n)//在qwq+1后面还可以放
            {
                kkk=(m-cal[qwq])/(n*mult[qwq+1]);//前面最多可以放多少
                ans+=kkk*mult[qwq+1];//统计答案
                m-=kkk*n*mult[qwq+1];//m减掉后就可以按照普通的做了
            }
            for(int i=qwq;i>=0;i--)
            {
                if(m-p[i][0]*mult[i]>=cal[i-1])ans+=mult[i],m-=p[i][0]*mult[i];
                else m-=p[i][1]*mult[i];//普通的做即可
            }
            write(ans);//输出
            puts("");
        }
    }   
    return 0;//完结撒花
}
```

$$ending$$

---

## 作者：Konnyaku_LXZ (赞：4)

比赛的时候用了 3min 想正解，然后调了 1h+ 的代码，终于在最后 20min 调出来了，之前一直WA的原因是爆了 long long，~~然后臭不要脸地开了int128~~。

因为是异或运算，所以我们首先考虑将所有的 $a_i$ **转换成二进制**然后**按位分别考虑**。

先考虑无解情况。显然当**最小的 $S$ 都比 $m$ 大**的时候必然无解。我们用一个 $sum$ 数组记录二进制下的第 $i$ 位上总共的 $1$ 的个数。对于当前的第 $i$ 位，如果 $1$ 的个数**大于或等于** $0$ 的个数，这一位就填 $1$ ，否则填 $0$，然后累加 $S$ 和 $k$，一旦 $S$ 大于 $m$ 我们就马上返回无解即可。

关于**等于**的时候也要填 $1$ 这里做一个解释：当 $0$ 的个数等于 $1$ 的个数时，显然我们不管填 $0$ 还是 $1$，当前的 $S$ 都是**一样的**，而我们又希望 **$k$ 尽可能大**，所以填 $1$ 会更优。

判完无解之后，我们考虑将 $k$ **增大**，即**从高到低**对每一个**之前填 $0$ 的**二进制位进行**修改**，如果将当前位改成 $1$ 之后 $S$ 仍然小于等于 $m$，则我们将 $S$ 的这一位改成 $1$ 并累加 $k$，直到无法修改为止。

对于之前已经填了 $1$ 的二进制位，我们不必进行修改，因为既然之前已经填了 $1$，那说明填 $1$ 会让 $S$ 更小，如果我们把 $1$ 改成 $0$，不但 $S$ 变大， $k$ 还变小了，所以没有必要更改。

最后输出 $k$ 就好啦。

Code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
#include<stack>
using namespace std;

const int MAXN=1e5+50;
typedef long long LL;

LL N,Q,a[MAXN],b[MAXN][35],sum[MAXN],poww[MAXN],Ans=0,maxx=0; 
bool flag=true;
//b[i][j]表示a[i]二进制下的第j位，poww记录2^n，Ans即题目中的k，maxx记录所有a[i]二进制的最高位，flag记录是否有解

void change(){//将a[i]转换成二进制并记录最高位 
	for(int i=1;i<=N;++i){
		for(int j=0;a[i];++j){
			b[i][j]=(a[i]&1);
			a[i]>>=1;
			maxx=max(maxx,LL(j));
		}
	}
}

void get(){//统计每一位上1的个数并预处理2^n 
	for(int k=0;k<=32;++k) for(int i=1;i<=N;++i) if(b[i][k]) ++sum[k];
	poww[0]=1;
	for(int i=1;i<=60;++i) poww[i]=poww[i-1]*2;
}

void Init(){
	scanf("%lld",&N);
	for(int i=1;i<=N;++i) scanf("%lld",&a[i]);
	scanf("%lld",&Q);
	change();
	get();
}

void Solve(){
	LL m,summ=0;
	Ans=0;flag=true;
	scanf("%lld",&m);
	for(int k=0;k<=maxx;++k){
		LL minn=min(sum[k],N-sum[k]);//记录0和1中个数较少的那个 
		if(minn<=(m-summ)/poww[k]) summ+=poww[k]*minn,Ans+=((sum[k]>=(N-sum[k]))?poww[k]:0);//注意if里面需要将乘法变为除法，否则会爆longlong 
		else{flag=false;return;}//直接返回无解 
	}
	for(int k=49;k>=maxx+1;--k) if(N<=(m-summ)/poww[k]) summ+=poww[k]*N,Ans+=poww[k];//对于maxx以上的二进制位的修改，//注意if里面需要将乘法变为除法，否则会爆longlong 
	for(int k=maxx;k>=0;--k){//对于maxx及以下二进制位的修改 
		if(sum[k]<(N-sum[k])){//这一位填0则尝试修改 
			if(N-2*sum[k]<=(m-summ)/poww[k]){//注意if里面需要将乘法变为除法，否则会爆longlong
				summ=summ+(N-2*sum[k])*poww[k];
				Ans+=poww[k];
			}
		}
	}
}

void Print(){
	if(!flag) puts("-1");
	else cout<<Ans<<endl;
}

int main()
{
	Init();
	while(Q--){
		Solve();
		Print(); 
	}
	return 0;
}
```

---

## 作者：pomelo_nene (赞：3)

考场上面打了很久，写篇题解记录一下月赛的 T3。

考虑将 $a_k$ 按二进制位划分，计算所有 $a_k$ 二进制上的第 $i$ 位上有多少个 $1$，记为 $bit_i$。

考虑怎么去使用这个 $bit_i$。我们要对所有的 $a_i$ 进行 $\operatorname{xor}$ 操作，也就是说将一位上面的 $1$ 全部变成 $0$，也就是原来有 $bit_i$ 个 $1$，操作这一位之后就会变成 $n- bit_i$ 个 $1$。所以判断无解的方法就很简单，我们只需要贪心的让每一位的 $bit_i$ 变得更小，判断一下这样的 $\sum a_i$ 是否小于等于 $m$ 即可。计算 $\sum a_i$ 可以用 $bit$ 去计算。

$$\sum a_i = \sum_{i=0}^{63} 2^i \times bit_i$$

现在我们已经解出了使 $\sum a_i \operatorname{xor} k$ 最小的 $k$，我们要让 $k$ 尽量大并且还要满足范围。于是从高位开始贪心，如果 $k$ 加入这一位之后仍能使 $\sum a_i \operatorname{xor} k'\leq m$，我们就加入（因为这一位加入之后，即使后面的 $1$ 全部选入，仍然没有这一个 $1$ 大）。

这个问题就被解决了。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef __int128 LL;
LL read()
{
	LL x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')	x=x*10+(c^'0'),c=getchar();
	return x*f;
}
void write(LL x)
{
	if(x<0)	putchar('-'),x=-x;
	if(x>9)	write(x/10);
	putchar(x%10+'0');
}
const LL M=1;
LL n,a[100005],B[65];
int main(){
	n=read();
	for(LL i=1;i<=n;++i)
	{
		a[i]=read();
		for(LL j=0;j<=60;++j)	if((a[i]>>j)&M)	++B[j];
	}
	LL q=read();
	while(q-->0)
	{
		LL m=read();
		LL c=0;
		for(LL i=0;i<=60;++i)	c+=min(n-B[i],B[i])*(M<<i);
		if(c>m)
		{
			puts("-1");
			continue;
		}
		LL p=0;
		for(LL i=60;~i;--i)
		{
			if(B[i]<=n-B[i])	m-=(M<<i)*B[i];
			else	p|=(M<<i),m-=(M<<i)*(n-B[i]);
		}
		for(LL i=60;~i;--i)
		{
			if(B[i]<=n-B[i])
			{
				if(m>=(n-2*B[i])*(M<<i))
				{
					p|=(M<<i);
					m+=B[i]*(M<<i);
					m-=(n-B[i])*(M<<i);
				}
			}
		}
		write(p);
		puts("");
	}
	return 0;
}
```

---

## 作者：zero4338 (赞：3)

翻译一下题面：有 $n$ 个数字，寻找一个数字 $k$,   
使得$\sum\limits_{i=1}^n(a_i\ xor \ k) \le m $的同时，使 $k$ 最大。  
首先观察消耗 $S$ 的形式。  
由于是位运算，不需要统计 $n$ 个数字的具体大小，只需要统计在二进制上每一位上出现了多少个 $1$ ，就可计算出答案。  
同时，假设答案二进制上的第 $i$ 位为 $1$ 时,存在解使得最终消耗小于 $m$,
若不使第 $i$ 位为 $1$, 即使存在解使得第 $0 \rightarrow i-1$ 位都为 $1$ ,
第 $0 \rightarrow i-1$ 位对答案的贡献也只为 $2^0+2^1+2^2+...+2^{i-1}=2^i -1 < 2^i$, 小于 $i$ 这一位对答案的贡献，所以如果能使第 $i$ 位为 $1$, 就不需要考虑第 $0 \rightarrow i-1$ 位的情况。  
所以，我们可以从高位到低位依次判断，如果当前位可以填 $1$,那么就使当前位为 
$1$, 否则使当前位为 $0$.  

现在的问题是，如何判断一个位置是否可以填 $1$.  
定义 $least_i$ 为填完第 $0 \rightarrow i$ 位时的最小消耗。  
最小消耗只需让每一位消耗都最小即可求出。  
$numsum_i$ 为所有数字中第 $i$ 位为 $1$的数字的个数。  
$used$为已经花费的消耗。  
设当前位为 $now$, 那么只要满足  
已经花费的消耗 $+$ 第 $i$ 位填 $1$ 的消耗 $+$ 第 $0 \rightarrow i-1$ 位的可能最小消耗 $\le m$.  
即$used+2^i*(n-numsum_i)+least_{i-1}\le m$  
第 $i$ 位就可以为 $1$.  
但是在判断时 $2^i*(n-numsum_i)$ 有可能(~~绝对~~)会爆 $long long$ ，
所以把上式等价转换为 $2^i\le(m-used-least_{i-1})/(n-numsum_i)$,  
当然要特判 $(n-numsum_i)=0$
```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
using namespace std;
const unsigned long long maxn=1e5+10;
unsigned long long n,numsum[maxn],q;
unsigned long long least[maxn]; 
unsigned long long m;
bitset<100>a[maxn];//一个很好用的东西，可以直接2进制拆分
unsigned long long qpow(unsigned long long a,unsigned long long b)
{
	unsigned long long ret=1;
	for(;b;b>>=1)
	{
		if(b&1)ret*=a;
		a=a*a;
	}
	return ret;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		unsigned long long num;
		cin>>num;
		a[i]=num; 
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=63;j++)
		{
			numsum[j]=numsum[j]+a[i][j];//统计1
		}
	}
	cin>>q;
	for(int i=0;i<=63;i++)
	{
		if(i==0)
		{
			least[i]=min(numsum[i],n-numsum[i]);
		}
		else
		{
			least[i]=least[i-1]+qpow(2,i)*min(numsum[i],n-numsum[i]);
		}//计算最小消耗值
	}
	for(int i=1;i<=q;i++)
	{
		cin>>m;
		if(m<least[63])//如果比最小消耗还要小，直接无解
		{
			cout<<-1<<'\n';continue;
		}
		unsigned long long used=0,ans=0;
		for(int j=63;j>=0;j--)
		{
			if((n==numsum[j])||qpow(2,j)<=(m-used-least[j-1])/(n-numsum[j]))//判断是否可以填1
			{
				used+=qpow(2,j)*(n-numsum[j]);//累计当前消耗
				ans+=qpow(2,j);//累计答案
			}
			else used+=qpow(2,j)*(numsum[j]);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```


---

## 作者：绝顶我为峰 (赞：2)

### subtask 1,2

暴力即可。

### subtask 3

发现 $a_i$ 上限非常大，我们考虑看第 $i$ 位 $(2^i\geq m)$，如果这一位不能把 $1$ 全部消掉就输出 $-1$，否则算答案。

至于剩下的数位，暴力计算。

### subtask 4

~~可能是给忘记开 long long 的选手准备的。~~

### subtask 5（正解）

看到异或，想到拆位。

可以统计出每一位上 $1$ 的个数 $b_i$，计算答案时如果 $k$ 在二进制下的当前位取 $0$，那么当前位对答案的贡献就是 $2^ib_i$；当前位取 $1$，对答案的贡献就是 $2^i(n-b_i)$。

对于每次询问，由于高位填 $1$ 一定比低位填 $1$ 更优，考虑贪心。

但是这样做可能会有问题，我们还需要保证无后效性。

确保无后效性的方法是预处理后先扫一遍数组 $b$，求出一个模板 $k_0$，表示 $k$ 在取 $k_0$ 时答案最小，这样我们每把 $k_0$ 中的一个 $0$ 改成 $1$ 都可以保证答案是最优的。

询问时从高位到低位扫一遍，如果 $k_0$ 的当前位是 $1$，这一位显然不需要调整，如果当前位是 $0$，则判断当前位改为 $1$ 后答案是否超过 $m$，如果不超过则更新 $k$。

时间复杂度 $O(n\log m)$。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
#define int unsigned long long
int n,a[100001],q,m,ans,sum,res,maxn;
int b[55];
inline int read()
{
    int x=0;
    char c=getchar();
    while(c<'0'||c>'9')
        c=getchar();
    while(c>='0'&&c<='9')
    {
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x;
}
void print(int x)
{
    if(x>=10)
        print(x/10);
    putchar(x%10+'0');
}
signed main()
{
    n=read();
    for(register int i=1;i<=n;++i)
    {
        a[i]=read();
        int p=a[i],cnt=0;
        while(p)
        {
            b[++cnt]+=p&1;
            p>>=1;
        }
    }
    for(register int i=50;i>=1;--i)
    {
        if(b[i]>=n-b[i])
            res+=1ull<<(i-1);
        maxn+=min(b[i],n-b[i])*(1ull<<(i-1));
    }
    q=read();
    while(q--)
    {
        m=read();
        ans=res;
        sum=maxn;
        if(maxn>m)
        {
            puts("-1");//想一想，为什么
            continue;
        }
        int p=log2(m);
        for(register int i=p+1;i>=1;--i)
        {
        	if(ans&(1ull<<(i-1)))
        		continue;
            if((sum-(min(b[i],n-b[i])*(1ull<<(i-1)))+(max(b[i],n-b[i])*(1ull<<(i-1))))<=m)
            {
                sum=sum-(min(b[i],n-b[i])*(1ull<<(i-1)))+(max(b[i],n-b[i])*(1ull<<(i-1)));
                ans+=1ull<<(i-1);
            }
        }
        print(ans);
        puts("");
    }
    return 0;
}

```


---

## 作者：Vocalise (赞：1)

大概题意：

> $n$ 个数，每次询问给出一个上限 $m$，求 $n$ 个数异或最大的一个数 $k$，使它们的和不超过 $m$。

首先考虑每位的贡献是独立的。

设第 $i$ 位它的权值为 $s_i$ 表示该位上有几个数为 $1$。

显然如果 $k$ 在该位上为 $1$，得到的贡献就是 $2^i\times s_i$。

我们有一个按位贪心的思路，从高到低枚举 $k$ ，满足更高位上的限制就设它为 $1$，也显然这样得到的是最优解。因为更低位上即使全部为 $1$ 也没有它大。

如何判断无解？考虑一个恒定的 $\min$ 值，它会等于所有数位上贪心是否取反得到的值，即：

$$\min\{s\}=\sum_{i=0}^{maxbit}\min(s_i,n-s_i)\times 2^i$$

如果给出的 $m<\min\{s\}$，就无解。

然而这是有纰漏的。具体地，高位上贪心的贡献并不能保证低位上得到的贡献满足限制 $m$。

如前所述，一个位上有一个贡献最低值即 $\min(s_i,n-s_i)\times 2^i$。我们需要“预支”出这一部分贡献，再考虑剩下的贪心加入。发现预支的就是 $\min\{s\}$，$m$ 提前减去即可。

贪心时：

如果 $n - s_i > s_i$ 即预支的是 $s_i\times 2^i$，显然选择异或不一定更优，我们判断 $n - 2s_i$ 即 $n-s_i$ 中预支以外的部分是否满足限制然后加入。

否则显然选择异或不仅加大答案而且贡献比不异或更小，就直接选择加入答案即可。

复杂度是 $O(V(n+m))$，$V$ 是位数，实际是 $m$ 的最大位数，取 $50$。

代码中判断一处使用了浮点数，因为 $2^{50}\times 10^6$ 会炸。

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

typedef long long ll;
const int MAXN = 100001;
const int BIT = 50;

inline ll read() {
	ll x = 0, f = 1; char ch = getchar();
	while(ch > '9' || ch < '0') { if(ch == '-') f = -1; ch = getchar(); }
	do x = x * 10 + ch - 48, ch = getchar(); while(ch >= '0' && ch <= '9');
	return x * f;
}

int n,a[MAXN],s[BIT];

int main() {
	n = read();
	for(int i = 1;i <= n;i++) {
		a[i] = read();
		for(int j = 0;j < BIT;j++)
			if(a[i] & (1ll << j)) s[j]++;
	}
	ll min = 0;
	for(int i = 0;i < BIT;i++) min += 1ll * std::min(s[i],n - s[i]) * (1 << i);
	int q = read();
	while(q--) {
		ll m = read(), k = 0;
		if(m < min) { std::puts("-1"); continue; }
		m -= min;
		for(int i = BIT - 1;~i;i--)
			if(n - s[i] > s[i]) {
				if(1.0 * m / (1ll << i) >= n - s[i] - s[i]) {
					m -= (1ll << i) * (n - s[i] - s[i]);
					k |= (1ll << i);
				}
			} else k |= (1ll << i);
		std::printf("%lld\n",k);
	}
	return 0;
}

```

讲的大概不是很清楚，请大家指出。

---

## 作者：Lonely_NewYear (赞：1)

# 洛谷 P6747 Teleport 题解

## 题目分析

可以把每个数转化为二进制，计算答案时从高位到低位考虑答案的这一位能否为 $1$。

这样做会有两个问题：

1. 判断能否完成折越时会出现问题。由于较高位优先选一可能已经产生了大量的高能，导致本来可以完成的折越在较低位时被判断为不能完成。所以要先处理出最小产生多少高能，并记录当前情况下的每一位。计算答案时如果当前位已经为 $1$ 就直接更新 $ans$ 否则考虑能否再消耗一些高能将 $0$ 改为 $1$

1. 时间复杂度为 $O(\log(a_i)qn)$，显然会炸，所以可以先预处理出这一位为 $1$ 会产生多少高能，为 $0$ 会产生多少高能，时间复杂度 $O(\log(a_i)(q+n))$ 可以通过此题。

具体看代码。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int main()
{
	long long n,a[51]={0},b[51]={0};
	//a数组表示当前位选择1产生的高能，b数组表示当前位选择0产生的高能
	scanf("%lld",&n);
	while(n--)
	{
		long long x;
		scanf("%lld",&x);
		for(long long i=1;i<=50;i++)//预处理 
		{
			//因为是异或，所以要反过来 
			if(x%2==1)
			{
				b[i]++;
			}
			else
			{
				a[i]++;
			}
			x/=2;
		}
	}
	long long q;
	scanf("%lld",&q);
	long long x=1;
	for(long long i=1;i<=40;i++)
	{
		x*=2;
	}
	while(q--)
	{
		long long ans=0,m;
		bool op[51]={0};
		scanf("%lld",&m);
		bool flag=1;
		long long y=x;
		for(long long i=40;i>=1;i--)//考虑最少产生多少高能 
		{
			y/=2;
			if(a[i]>b[i])
			{
				op[i]=0;
				m-=y*b[i];
			}
			else
			{
				op[i]=1;
				m-=y*a[i];
			}
			if(m<0)
			{
				flag=0;
				break;
			}
		}
		if(!flag)
		{
			printf("-1\n");
			continue;
		}
		y=x;
		for(long long i=40;i>=1;i--)//计算答案 
		{
			y/=2;
			if(op[i])
			{
				ans+=y;
			}
			else
			{
				if(m>=(a[i]-b[i])*y)
				{
					m-=(a[i]-b[i])*y;
					ans+=y;
				}
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

谢谢观看。

---

## 作者：LeavingZzz (赞：1)

# $\mathsf{Solution\space For\space P6747}$  
~~MdOInb（破音）~~  
## $\mathsf{Description}$  
给出一个长度为 $N$ 非负整数序列 $a_i$，以及 $q$ 次询问，每次询问给出一个限制 $m$，你需要求出最大的整数 $k$ 使得 $\sum\limits_{i=1}^{N}a_i \space\text{xor}\space k\le m$，如果无解，输出 $-1$。  
## $\mathsf{Analysis}$  
本题考虑拆位来做  
什么事拆位？  
拆位是统计一个序列中所有数字在某一个二进制位为 $1$ 的个数和，相当于把一整个序列拆成了一个一个的二进制位进行统计，可以有效的降低一些题目的解法复杂度 （$O(N)->O(loga_i)$）  
所以我们统计出序列的各个二进制位出现的 $1$ 的个数，设第 $i$ 个二进制位上 $1$ 的个数为 $bitsum[i]$，统计代码如下：  
```
for(int i=1;i<=N;i++)
{
	scanf("%d",&A[i]);
	for(int j=0;j<=30;j++)
		bitsum[j]+=(A[i]&(1<<j))!=0;
}
```  
现在对于每一个二进制位你都知道有多少个了  
那么现在对于一个指定的 $k$ 你都能统计其花费了  

根据 $\text{xor}$ 的性质，当 $k$ 的第 $i$ 个二进制位为 $1$ 的时候，这个二进制位会对 $\sum\limits_{i=1}^{N}a_i \space\text{xor}\space k$ 产生 $2^i\times (N-bitsum[i])$ 的贡献（也就是该位为 $0$ 的数字个数），当第 $i$ 个二进制位为 $0$ 的时候会产生 $2^i\times bitsum[i]$ 的贡献。 

所以一个部分分做法就能得到了，我们直接枚举 $k$，对于每个 $k$ 检查一次是否超出 $m$，可过 $1,2$ 两个点  

接着尝试更好的做法  
我们是不是可以直接构造出答案？  

贪心的思想，我们从高位往低位枚举 $k$ 的二进制位，如果某一位能放 $1$ 那么一定放 $1$，因为就算本位不放后面的所有位全部放 $1$ 也比不上本位放 $1$ 的答案大。  
例如 假设现在在第四个二进制位可以放 $1$，如果我们放 $1$ 而后面都是 $0$ ，答案为 $(1000)_2=8$，假如本位不放后面全部都放，答案为 $(0111)_2=7$ 不会更优，也就是说贪心思路是没问题的。  

现在的问题就是，如何判断某一位能不能放 $1$？  
我们设前面的决策已经产生的花费为 $cost$（每次决策后将花费加入，初始为 $0$，已知），而本位如果是 $1/0$ 产生的花费刚刚已经提到了，设为 $curc$（已知），设后面还没枚举到的二进制位会产生的最小花费为 $sum$（未知），如果满足 $cost+curc+sum\le m$ 那么本位就是可以放 $1$ 的。  

而这个不等式中我们只有 $sum$ 是不知道的，但是很明显这个 $sum$ 是可以处理出来的，因为每一位是 $0/1$ 都会产生一个花费，我们预处理出每一位的最小的花费 （$0/1$ 两种花费中取最小），然后做一个前缀和，就能在枚举二进制位的时候直接得到未枚举到的二进制位的最小花费了。  

梳理思路  
1. 拆位统计二进制位  
2. 预处理出前 $i$ 位的最小花费（在 $0$ 和 $1$ 中选择花费更小的累加）  
3. 对于每一个询问，先判断所有位能产生的最小花费是否小于 $m$（直接从第二步的预处理中得到），若小于则输出 $-1$，再从高位向低位枚举答案 $k$ 的二进制位，如果该位能放 $1$ 则放 $1$，否则放 $0$，并且将放 $0/1$ 的花费累加到 $cost$ 中  

注意溢出（悲）  
还是没看懂的话就看代码吧qwq  
$\Large\mathsf{Code}$  
```
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef unsigned long long LL;
const int maxn=100007;
int N,Q;
LL bitsum[51],M,p2[51],sum[51],cost[2][51];
int A[maxn];
char BB[(1<<15)+1],*SS=BB,*TT=BB;
//#define getchar() (SS == TT && (TT = (SS = BB) + fread(BB,1,1 << 15,stdin),TT == SS) ? EOF : *SS++)
inline LL R()
{
	char c;
	LL re;
	while((c=getchar())>'9'||c<'0');
	re=c-48;
	while((c=getchar())>='0'&&c<='9')
	re=re*10+c-48;
	return re;
}
int main()
{
	N=R();
	for(int i=1;i<=N;i++)
	{
		A[i]=R();
		for(int j=1;j<=31;j++)
			bitsum[j]+=(A[i]&(1<<j-1))!=0;
	}
	Q=R();
	p2[1]=1;
	for(register int i=2;i<=50;++i)
		p2[i]=p2[i-1]<<1;
	register LL k,curc;
	for(register int i=1;i<=31;++i)
	{
		cost[0][i]=p2[i]*(N-bitsum[i]);
		cost[1][i]=p2[i]*bitsum[i];
		sum[i]=sum[i-1]+(cost[0][i]>cost[1][i]?cost[1][i]:cost[0][i]);
	}
	for(register int i=32;i<=50;++i)
		sum[i]=sum[i-1],cost[0][i]=p2[i]*N;
	while(Q--)
	{
		M=R();
		curc=0;k=0;
		if(sum[50]>M) {puts("-1");continue;}
		for(register int i=50;i>0;--i)
		if(curc+cost[0][i]+sum[i-1]<=M) curc+=cost[0][i],k|=p2[i];
		else curc+=cost[1][i];
		printf("%llu\n",k);
	}
	return 0;
}
```  
另外，拆位思想还有一题也可以做一下 $->$ [qwq](https://www.luogu.com.cn/problem/P6102)  
$\huge\mathcal{The\space End}$  
谢谢管理大大审核^_^

---

## 作者：Soohti (赞：1)

## 贪心题解  

------------

### 考虑不存在答案的情况  

首先将所有的能量转换成二进制，如样例 `1 2 3` 转换后就是 `01 10 11`。  

由异或运算的性质不难发现，为使消耗最小，`k` 在二进制下某一位的值要尽可能与给定的能量相同，即：若能量值该位的 `1` 较多，则 `k` 的该位为 `1`；若能量值该位的 `0` 较多，则 `k` 的该位为 `0`。特别的，**在两者相等的情况下，为了使 `k` 的值较大，`k` 的该位取 `1`。**  

对于给定的能量值，为了得到二进制下某一位是 `1` 多还是 `0` 多，我们将 `1` 的数量存到 `a` 数组中，这一步可在输入时完成（代码见下文）。  
然后就不难求出最小的消耗和对应的 `k` 。 

最小的消耗为  

$res=\sum_{i=1}^\infty \begin{cases}a_i \times 2^{i-1},& a_i<n-a_i\\ (n-a_i) \times 2^{i-1},& a_i>=n-a_i \end{cases}$  

若最小的消耗大于 `m` 就输出 `-1`。  

### 考虑最小的消耗对应的 `k` 比 `m` 小的情况（贪心）  

此时，`k` 有可能可以继续增大。  

当前求出的 `k` 值在二进制下是一串 `0` 和 `1`，且所对应的消耗最小。因此，**修改 `k` 的任何一位都会使消耗变大。** 

**在这种情况下，将 `k` 的某一位由 `1` 改为 `0` 没有意义，因为这样在增大消耗的同时减小了 `k` 值。**  

**为了使 `k` 尽可能大，我们从高位起从高向低枚举 `k` 的每一位，如果该位为 `0`，则尝试将其修改为 `1`。**  

在本题中，经过测试，“高位”可从 `34` 位开始枚举，若不放心可从 `63-log2(n)` 位开始枚举。~~**不开 `long long` 见祖宗。**~~  

### 代码  

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,q,t,j,a[100];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&t);
		j=1;
		while(t){
			a[j]+=t&1;
			t>>=1;
			j++;
		}
	}
	scanf("%d",&q);
	while(q--){
		ll m,res=0,k=0;
		scanf("%lld",&m);
		for(int i=34;i>=1;i--){
			if(a[i]>=n-a[i])k+=1LL<<i-1,res+=(n-a[i])*(1LL<<i-1);
			else res+=a[i]*(1LL<<i-1);
		}
		if(res>m)printf("-1\n");
		else{
			for(int i=34;i>=1;i--)
				if(!(k&(1LL<<i-1))&&res+(n-a[i]-a[i])*(1LL<<i-1)<=m)k+=1LL<<i-1,res+=(n-a[i]-a[i])*(1LL<<i-1);
			printf("%lld\n",k);
		}
	}
	return 0;
}
```


---

## 作者：a___ (赞：0)

套路题，按位拆分贪心。   

_____

以 $a_{i,j}$ 表示数 $a_i$ 二进制下第 $j$ 位。   

容易发现 $S=\sum_{i=1}^na_i\oplus k$ 直接算是 $\mathbf O(n)$ 的，不好计算，但    
$S=\sum_{i=1}^na_i\oplus k$   
$=\sum_{i=1}^n\sum_{j=0}^{50}2^j(a_{i,j}\oplus k_j)$   
$=\sum_{j=0}^{50}2^j\sum_{i=1}^nk_j\oplus a_{i,j}$   
$=\sum_{j=0}^{50}2^j([k_j=1](\sum_{i=1}^n[a_{i,j}=0])+[k_j=0](\sum_{i=1}^n[a_{i,j}=1]))$，   
发现 $\sum_{i=1}^n[a_{i,j}=0]$ 和 $\sum_{i=1}^n[a_{i,j}=1]$ 可以预处理，所以我们可以 $\mathbf O(\log)$ 完成 $S$ 的计算。    

我们记 $tot_{j,0}=\sum_{i=1}^n[a_{i,j}=0]$，$tot_{j,1}=\sum_{i=1}^n[a_{i,j}=1]$。    

现在问题变成最大化 $k$，使之满足 $\sum_{j=0}^{50}2^j([k_j=1]tot_{j,0}+[k_j=0]tot_{j,1})\leq m$。   

考虑 $\min\{\ \sum_{j=0}^{50}2^j([k_j=1]tot_{j,0}+[k_j=0]tot_{j,1})\ \}=\sum_{j=0}^{50}2^j\min\{tot_{j,0},tot_{j,1}\}$。    

由此我们可以推出两点：   
第一，若 $m<\sum_{j=0}^{50}2^j\min\{tot_{j,0},tot_{j,1}\}$，则不存在合法 $k$。    
第二，当 $S=\sum_{j=0}^{50}2^j\min\{tot_{j,0},tot_{j,1}\}$ 时的 $k$ 应为基础值。     

记此时的 $k$ 为 $mink$。    

我们想要最大化这个 $k$，就相当于从高位开始尽量将 $mink$ 的每一个二进制位变成 $1$。    
若 $mink_j=1$，则保持不变。   
若 $mink_j=0$，如果改为 $1$ 后仍 $S\leq m$，则改为 $1$。    

不以基础值为基础进行的贪心可能会造成前面一位变为 $1$ 之后后面无论如何都会大于 $m$，因为开始没有考虑低位值；但有基础值以后，则有考虑低位最小值，于是正确。   

注意到 $n\times 2^{50}$ 会爆`long long`，所以我们考虑化乘为除。    

AC代码：
```cpp
#include<cstdio>
#include<cctype>
#include<cstdlib>
const int N=1e5+10;
//这里省略fastIO部分
int n,q,a[55];
long long m,sum,ans;
inline int min(int a,int b){return a<b?a:b}
int main()
{
	register int i,j,x;
	n=In::readu();
	for(i=1;i<=n;i++)
	{
		x=In::readu();
		for(j=30;~j;j--)
		if((x>>j)&1)a[j]++;
	}
    //a[j]=tot[j][1],n-a[j]=tot[j][0]
	q=In::readu();
	while(q--)
	{
		m=In::readu();
		sum=ans=0;
		for(i=31;~i;i--)
		sum+=(1ll<<i)*min(a[i],n-a[i]);
		if(sum>m){Out::print(-1);continue;}//不合法
		for(i=60;~i;i--)
		if(n-a[i]<=a[i])ans|=(1ll<<i);//本来是1
		else if(((n-a[i])-a[i])<=(long double)(m-sum)/(1ll<<i))//化乘为除
        //同sum+(__int128)(1ll<<i)*((n-a[i])-a[i])<=m
		ans|=(1ll<<i),sum+=(1ll<<i)*((n-a[i])-a[i]);
		Out::print(ans);
	}
	Out::flush();
	return 0;
}
```

---

## 作者：囧仙 (赞：0)

## 题目大意

有 $n$ 个数字 $a_i$ 和 $q$ 次询问。每次给出一个非负整数 $m$ ，求能够使得 

$$\sum_{i=1}^n a_i \oplus k \le m$$

的最大的非负整数 $k$ ，其中 $\oplus$ 是异或操作。若无解，输出 $-1$ 。

## 题解

题目中提到了位运算，而位运算一般与二进制紧密地结合在一起。考虑从该方面入手。

首先考虑 $k$ 的每一位对总花费的贡献。显然， $k$ 的每一位互相独立，因此我们可以预处理出每一位的贡献。具体而言，我们统计有多少个 $a_i$ ，它的二进制下第 $i$ 位为 $1$ ，记为 $P_i$ 。为什么要统计**多少个**而并非它的直接贡献呢？因为如果统计**贡献和**，那么 $\text{long long}$ 会溢出。

接着，我们能够贪心地选出一个 $k_0$ ，使得它的总花费最小。具体而言，对于 $k$ 的二进制下的第 $i$ 位，判断 $P_i$ 与 $n-P_i$ 的关系，选择更小的那一个。同时，我们统计出最小花费 $x_0$ 。

考察每一次询问。显然，如果 $m<t_0$ ，直接输出 $-1$ 即可。考虑从 $k_0$ 开始，尽可能地获得一个最大的 $k$ 。根据贪心的思想，我们从最高位开始逐步向最低位开始枚举，并更新答案。具体而言，如果 $k_0$ 第 $i$ 位是 $0$ ，就尝试将它改为 $1$ ，此时会产生新的费用 $(n-2\times P_i)\times 2^i$ 。但是要注意的是，如果直接比较新的费用与 $m$ 的值，就会**溢出**。如何解决呢？

观察到，

$$\begin{aligned}&&m'&\ge m+(n-2\times P_i)\times 2^i\cr
&\iff& m' \div 2^i & \ge m \div 2^i+(n-2\times P_i)\end{aligned}$$

于是，我们能够使用位移操作避免溢出的风险。

当然，你也可以使用 $\text{\_\_int128}$ 规避这些溢出，尽管这种方法可能不能在正规比赛中使用。

## 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define up(l,r,i) for(LL i=l;i<=r;i++)
#define dn(l,r,i) for(LL i=l;i>=r;i--)
using namespace std;

typedef long long LL;
LL qread(){
    LL w=1,c,ret;
    while((c=getchar())> '9'||c< '0'); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret;
}
const int MAXN =1e5+3,MAXM=60+3;
LL w,ans,o,t; int n,q,P[MAXM],Q[MAXM],s;
void write(LL x){
    if(x>9) write(x/10); putchar(x%10+'0');
}
int main(){
    n=qread(); up(1,n,i){
        w=qread(); dn(30,0,j) if(w&(1<<j)) ++P[j];
    }
    up(0,60,i) Q[i]=n-P[i];
    up(0,60,i){
        if(P[i]<Q[i]) t+=(LL)P[i]<<i; else t+=(LL)Q[i]<<i,o|=1ll<<i;
    }
    q=qread(); up(1,q,i){
        w=qread(),ans=o,s=64-__builtin_clzll(w);
        if(w<t) puts("-1"); else {
            w-=t;
            dn(s,0,j){
                if(P[j]<Q[j]&&(w>>j)>=Q[j]-P[j])
                w=w-((LL)(Q[j]-P[j])<<j),ans|=(1ll<<j);
            }
            write(ans),putchar('\n');
        }
    }
    return 0;
}
```

---

## 作者：囧仙 (赞：0)

## 题目大意

有 $n$ 个数字 $a_i$ 和 $q$ 次询问。每次给出一个非负整数 $m$ ，求能够使得 

$$\sum_{i=1}^n a_i \oplus k \le m$$

的最大的非负整数 $k$ 。若无解，输出 $-1$ 。

## 题解

观察到，$k$ 二进制下第 $i$ 位对花费的贡献与其他二进制位无关。于是，我们能够预处理出 $k$ 的第 $i$ 位分别是 $0$ 与 $1$ 时会产生的费用 $P_i,Q_i$ 。考虑贪心地决定二进制下第 $i$ 位是多少。

为了达成限制条件，我们优先选择花费更少的那一个。假如 $P_i < Q_i$ ，我们就在第 $i$ 位上选择 $0$ ；否则选择 $1$ 。如果操作后的总花费已经超过了 $m$ ，就说明无解，输出 $-1$ 即可。

若有解，考虑最大化 $k$ 的值。我们从最高位向最低位计算。如果原先选择的是 $0$，且我们能够接受**新增**的花费，就将它改为 $1$ ，并记录花费。

要注意的是，由于答案可能达到 $2^{60}$ 的级别，因此 $Q_i$ 的值域可能很大（达到 $2^{90}$ 左右）。我们可以特判这种情况，将超过 $2^{60}$ 的 $Q_i$ 直接赋值为 $2^{60}$ 。

## 参考代码

```pas
var A:array[1..100000] of longint;
var P:array[0..64]     of int64;
var Q:array[0..64]     of int64;
var T:array[0..64]     of int64;
var n,m:longint; var i,j:longint;
var w,ans:int64;
begin
    T[0]:=1;
    for i:=1 to 60 do T[i]:=T[i-1]*2;
    for i:=0 to 60 do P[i]:=0;
    for i:=0 to 60 do Q[i]:=0;
    read(n); for i:=1 to n do begin
        read(A[i]);
        for j:=0 to 60 do begin
            P[j]:=P[j]+ (A[i]      and T[j]);
            Q[j]:=Q[j]+((not A[i]) and T[j]);
            if Q[j]>T[60] then Q[j]:=T[60];
        end;
    end;
    read(m);
    for i:=1 to m do begin
        read(w);ans:=0; for j:=60 downto 0 do begin
            if P[j]<Q[j] then w:=w-P[j]
            else begin
                    w:=w-Q[j];
                    ans:=ans or T[j];
                end;
            end;
        if w<0 then writeln(-1) else begin
            for j:=60 downto 0 do begin
                if ((P[j]<Q[j]) and (w>=Q[j]-P[j])) then begin
                    w:=w-Q[j]+P[j];
                    ans:=ans or T[j];
                end;
            end;
            writeln(ans);
        end;
    end;
end.
```

---

## 作者：ez_lcw (赞：0)

题意简述：$q$ 次询问，每次给一个数 $m$，求最大的 $k$，使得 $\sum_{i=1}^{n}a_i \operatorname{xor} k<m$。

因为涉及到位运算，所以先想到拆位，不妨设 $a_i$ 拆出来的第 $j$ 位为 $b_{i,j}$，$k$ 拆出来第 $i$ 位为 $c_i$。

那么 $\sum_{i=1}^{n}a_i \operatorname{xor} k$ 就可以按位表示了，也就是：

$$\sum_{i=1}^{n}a_i \operatorname{xor} k=\sum_{j=0}^{30}2^{j}\sum_{i=1}^{n}b_{i,j}\operatorname{xor}c_j$$

而我们发现 $b_{i,j}$ 和 $c_j$ 都是 $0$ 或 $1$，所以设 $sum(j,0/1)$ 表示 $\sum_{i=1}^{n}[b_{i,j}=0/1]$，也就是说所有的 $a_i$ 中，第 $j$ 位为 $0/1$ 的个数。显然，$sum$ 数组可以预处理出来。

那么我们又可以化简那个式子了：

$$\sum_{j=0}^{30}2^{j}\sum_{i=1}^{n}b_{i,j}\operatorname{xor}c_j=\sum_{j=0}^{30}2^{j}\times \underbrace{sum(j,c_j\operatorname{xor}1)}_{\text{$b_{i,j}\operatorname{xor}c_j$ 为 $1$ 的个数}}$$

那么花费我们就可以按位来计算了。

现在考虑贪心取 $k$。

从高位往低位选，假设选到第 $j$ 位，显然这一位优先取 $1$ 才能让 $k$ 最大，但我们要保证总花费不超过 $m$。

分情况讨论：

1. 若 $sum(j,0)<sum(j,1)$，也就是说这一位取 $1$ 的话花费小，而我们又想取 $1$，所以肯定取 $1$。

1. 若 $sum(j,1)>sum(j,0)$，也就是说这一位取 $0$ 的话花费小，但是我们想取 $1$，所以陷入了两难的境地。

	但是我们的目标是 $k$ 最大，而这一位取 $1$ 的话，我不管我后面的位怎么取，无论如何都会比取 $0$ 大（因为后面的位都是低位），所以只要选了 $1$ 之后有一种方案能使总耗费小于等于 $m$，我们就选 $1$。否则选 $0$。

关键是怎么才能知道选了 $1$ 之后是否能有一种方案使总耗费不超过 $m$。

所以考虑设 $f_i$ 表示第 $0$ 位到第 $i$ 位的最小耗费是多少（不考虑 $k$ 最大），显然有 $f_i=f_{i-1}+2^j\times \min(sum(j,0),sum(j,1))$。

这样我们就能知道是否有这种方案了，假设这一位选了 $1$ 之后，这一位和以前（第 $30$ 位到第 $j$ 位）的总花费是 $w$，当 $w+f_{j-1}\leq m$ 时，这一位就可以选 $1$。

那么我们就能贪心地选出最大的 $k$ 了。

总时间复杂度 $O(n \log m)$。（$q$、$n$ 同级）

代码如下：（个人感觉这种做法比较简洁好写）

```cpp
#include<bits/stdc++.h>

#define K 55
#define N 100010
#define ll long long

using namespace std;

int n,q,sum[K][2];
ll a[N],f[K];

signed main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	for(int j=0;j<=50;j++)
		for(int i=1;i<=n;i++)
			sum[j][(a[i]>>j)&1]++;//预处理sum
	f[0]=min(sum[0][0],sum[0][1]);
	for(int i=1;i<=50;i++)
		f[i]=f[i-1]+(1ll<<i)*min(sum[i][0],sum[i][1]);//按照dp式预处理f
	scanf("%d",&q);
	while(q--)
	{
		ll m;
		scanf("%lld",&m);
		if(m<f[50])//当m小于最小花费时
		{
			puts("-1");
			continue;
		}
		ll k=0,sumw=0;//sumw表示当前总花费
		for(int i=50;i>=0;i--)
		{
			__int128 w=(__int128)(1ll<<i)*sum[i][0];//这个可能会炸，懒得特判了，就用了int128
			if(sum[i][0]<=sum[i][1])//第一种情况
			{
				k+=(1ll<<i);
				sumw+=w;
			}
			else
			{
				if((__int128)sumw+w+(i>0?f[i-1]:0)<=m)//第二种情况
				{
					k+=(1ll<<i);
					sumw+=w;
				}
				else sumw+=(1ll<<i)*sum[i][1];
			}
		}
		printf("%lld\n",k);
	}
	return 0;
}
```

---

