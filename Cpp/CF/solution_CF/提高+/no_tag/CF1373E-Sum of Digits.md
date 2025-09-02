# Sum of Digits

## 题目描述

Let $ f(x) $ be the sum of digits of a decimal number $ x $ .

Find the smallest non-negative integer $ x $ such that $ f(x)       + f(x + 1) + \dots + f(x + k) = n $ .

## 样例 #1

### 输入

```
7
1 0
1 1
42 7
13 7
99 1
99 0
99 2```

### 输出

```
1
0
4
-1
599998
99999999999
7997```

# 题解

## 作者：SegmentTree (赞：9)

# 题解 $CF1373E$

### $Statement$

### 略

### $Solution$

+ 我的方法比较暴力，VP的时候差点想出来了，但是一直wrong answer +TLE、
+ 打打表就发现大部分的都是可以暴力跑出来的，然而我以为只有$k=0$的时候要手动构造，结果当$k = 1 $,$n$比较大的时候也需要构造，当时暴力跑出来$-1$,以为本来就不存在，结果一直wrong answer ,调大就T，最后发现是跑不到那个数字后来不及改了。

+ 就是对于$k \leq 1 $的手动构造，然后$k > 1$的暴力搞

+ $k=0$时，不停填$9$ ,最后填一个取模的数

+ $k=1$时，打表看看就发现规律了，具体看代码吧

  
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1000000;
int T,n,k;
int cnt[N+50];
void Init()
{
    cnt[0]=0;
    for(int i=1;i<=N;i++) cnt[i]=cnt[i/10]+i%10;
    for(int i=1;i<=N;i++) cnt[i]+=cnt[i-1];
    return;
}
int f(int x)
{
    int sum=0;
    while(x)
    {
        sum+=x%10;
        x/=10;
    }
    return sum;
}
void out(int num)
{
    if(num%9) printf("%d",num%9);
    for(int i=1;i<=num/9;i++) printf("9");
    return;
}
void put(int num)
{
    if(num%2==0) 
    {
        num-=26;
        num/=2;
        out(num);
        printf("89\n");
    }
    else
    {
        num-=17;
        num/=2;
        out(num);
        printf("8\n");
    }
    return;
}
signed main()
{
    scanf("%lld",&T);
    Init();
    for(int amo=1;amo<=T;amo++)
    {
        scanf("%lld%lld",&n,&k);
        if(n==0&&k==0)
        {
            printf("0\n");
            continue;
        }
        if(k==0)
        {
            out(n);
            printf("\n");
            continue;
        }
        if(k==1&&n>=100)
        {
            put(n);
            continue;
        }
        int flag=0;
        if(cnt[k]==n)
        {
            printf("0\n");
            continue;
        }
        for(int i=1;i<=N;i++)
        {
            // if((i*(k+1)+k*(k+1)/2)%9!=n%9) continue;
            if(cnt[i+k]-cnt[i-1]==n)
            {
                printf("%lld\n",i);
                flag=1;
                break;
            }
        }
        if(!flag) printf("-1\n");
    }
    return 0;
}

```

---

## 作者：一叶知秋。 (赞：5)

如果没有进位，直接枚举最后一位是几即可

对于连续几个数的数位和的和，考虑枚举除了最后一位在后面连续有几个 $9$ ，进行枚举即可

实现题，直接看代码比较直观：

```cpp
#include<cstdio>
#include<cctype>

#define INF 1000000000000000000

inline int read(){
	int r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}

inline long long min(long long a,long long b){
	return a<b?a:b;
}

int n,k,top,sta[111];

long long ans,p[22];

inline long long calc(long long x){
	if(x<8)return x;
	top=1;
	sta[1]=8;
	x-=8;//贪心，只有最后一位选8（因为我们已经枚举最后9的位数，这里不能在线选9）
	while(x>9){
		sta[++top]=9;
		x-=9;//再前面就可以全选9了
	}
	long long ans=x;
	while(top)ans=(ans<<1)+(ans<<3)+sta[top--];
	return ans;
}

inline void work(){
	ans=INF;
	n=read(),k=read();
	for(int x=n/9;x>=0;x--){//显然最多只有n/9个9
		for(int i=0;i<=9;i++){
			long long m=n,cnt=0;
			for(int j=0;j<=k;j++){
				m-=(i+j)%10;//把最后一位的贡献先减掉
				cnt+=(i+j)/10;//计算经过位的个数
			}
            if(m<cnt+9*x*(k+1-cnt))continue;//都不够减了，直接退掉
			if((m-cnt-9*x*(k+1-cnt))%(k+1))continue;//因为有k+1个，要除以k+1
			m=(m-cnt-9*x*(k+1-cnt))/(k+1);
			m=calc(m)*p[x+1]+(p[x]-1)*10+i;
			ans=min(ans,m);
		}
	}
	if(ans==INF)puts("-1");
	else printf("%lld\n",ans);
}

int main(){
	freopen("code.in","r",stdin);
	freopen("code.out","w",stdout);
	p[0]=1;
	for(int i=1;i<=18;i++)p[i]=p[i-1]*10;//预处理方便直接跳到第几位
	int t=read();
	while(t--)work();
	return 0;
}
```

如果不是很理解，建议可以手模一下（毕竟是个这样的题）

---

## 作者：奇米 (赞：5)

# 题解 - $\mathrm{CF1373E}$

## 题目意思

* [题目传送门](https://www.luogu.com.cn/problem/CF1373E)


## $\mathrm{Sol}$

* 考场时差点没做出来，最后还是$rush$出来了。

* 我们考虑 $k\leq 9$ ，相当于他只会产生 $1$ 次进位。以及$n\leq 150$，相当于最多只会有 $\frac{150}{9}=17$ 位。

* 于是我们只需要枚举最后一位 $x$ 是什么，我们就能算出前面$bit-1$位的和。于是我们贪心地从后往前填$9$即可，直到不能填。最后我们只要判断那些$x+k>9$的数需要进位，处理很简单只要把倒数第二位填$8$（避免了进位），再倒着贪心填$9$即可。

## $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,b,a) for ( int i=(b);i>=(a);i-- )
#define GO(i,x) for ( int i=head[x];i;i=e[i].nex )
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define YES return puts("YES"),0
#define NO return puts("NO"),0
#define GG return puts("-1"),0
#define pb push_back
#define int long long
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int mod=1e9+7;
const int mo=998244353;
const int N=55;

int n,m,Q,b[111];

signed main()
{
	Q=read();
	For(q,1,Q)
	{
		n=read();
		m=read();
		int mx=1e18; 
		For(i,0,9) 
		{
			int sum=0,gs=0;
			For(j,i,i+m) 
			{
				if(j>9) gs++;
				sum+=j%10;
			}
			int rem=n-sum;
			if(rem<0) continue;
			if((rem-gs)%(m+1)!=0) continue;
			int x=(rem-gs)/(m+1);
			mem(b,0);
			int bit=0;b[++bit]=i;
			int flg=0;
			while(x)
			{
				if(x>=9) 
				{
					if(i+m<=9||flg) b[++bit]=9,x-=9;
					else b[++bit]=8,x-=8,flg=1;
				}
				else b[++bit]=x,x=0;
			}
			int tot=0;
			reverse(b+1,b+bit+1); 
			For(j,1,bit) tot=tot*10+(b[j]);
			mx=min(mx,tot);
		}
		if(mx==1e18) puts("-1");
		else cout<<mx<<endl;
	}
}
			

```


---

## 作者：Lynkcat (赞：3)

这里有一种更容易思考的方法，即使它有点麻烦。

首先因为 $k \leq 9$ 说明它最多进一次位，那么我们可以直接枚举进位是哪一位，再枚举当前的 $x$ 的个位是什么，然后列出方程求出 $x$ 的所有位上之和是多少，接着可以直接构造出符合条件的 $x$ 。


至于代码实现，确实非常复杂，我到现在都没有调出来就不放了。（但是 $xxy$ 巨佬用这个方法交了一发直接 $A$ 了！

---

## 作者：BMTXLRC (赞：2)

这道题我打了真的很久，我的方法特判可能较多。

## 思路

观察题目发现一个很重要的信息：$0\leqslant k\leqslant 9$。

换句话说：**这个序列最多只会有一次是进位的。** 啊你可能听不懂，就是说我最多只会有一次 $9\to 0$ 的转换。

考虑我们这个序列为：

$$
f(x),f(x)+1,\ldots,f(x)+i,f(x)+i-9j+1,\ldots,f(x)+i-9j+k-i
$$

上面的 $i$ 表示 $x+i+1$ 一定是进位的。$x+i$ 是最后一个不进位的数字，而 $j$ 就是进了多少位，比如说 $99\to 100,j=2$。

我们将这个序列全部加起来可以得到：

$$
(k+1)f(x)+\dfrac{k(k+1)}{2}-9(k-i)j=n
$$

嘿，你看我们这不就得到 $f(x)$ 了吗，通过枚举 $i$，$j$ 就能得到 $f(x)$ 的值，是不是看起来很简单呢？不是。

在这里再讲一下如何枚举：

- $i\neq k$，因为不可能最后一个之后还能进位
- $i$ 从 $0$ 开始，因为我的末尾有可能是 $0$
- $j\leqslant 17$，这是因为 $n\leqslant 150$，最多只会进 $17$ 次位。

--------

**第一个特判：**$k=0$。

这个很显然大家都能想到了，但是 $k=0$ 应该如何构造呢？其策略应该是 $n$ 对 $9$ 的余数尽可能靠前，剩下全部用 $9$ 填充。

$\tt Hack\;Input\;1$

```
1
35 0
```

$\tt Hack\;Output\;1$

```
8999
```

------------

**第二个特判：** 存在不进位情况。

在这里我们推导一下不进位情况，即 $j=0$。

$$
(k+1)f(x)+\dfrac{k(k+1)}{2}=n
$$

其构造方式是：末位一定是有限制的：$lst\leqslant 10-k-1,k\leqslant 8$。

再除去末位之后（这是可以枚举的），余数作为最开头，剩下用 $9$ 填充，最后加上末位。

$\tt Hack\;Input\;2$

```
1
18 3
```

$\tt Hack\;Output\;2$

```
3
```

-------------

**第三个特判：** 细心的读者可能已经发现了：我刚刚强调第二特判中 $k\leqslant 8$，这是因为这个从 $1$ 开始枚举的循环无法枚举到末位是 $9$ 的情况，至于为什么，我不能光让一个本来就不进位但 $0$ 又在最末尾出现答案吧。。。

这种情况对应的数据是：

$\tt Hack\;Input\;3$

```
3
45 9
55 9
145 9
```

$\tt Hack\;Output\;3$

```
0
10
190
```
~~对没错我给了三个数据。~~

这种特判的构造方式是，最后一位必须为 $0$，前面用余数和若干个 $9$ 填充。

------------

**第四个特判：** 存在 $\dfrac{k(k+1)}{2}> n$ 且 $n-\dfrac{k(k+1)}{2}\equiv 0\pmod {(k+1)}$

这种情况直接输出 `-1`。

$\tt Hack\;Input\;4$

```
1
3 5
```

$\tt Hack\;Output\;4$

```
-1
```

---------

特判到此结束，而普通情况下的构造方案是：

首先排除掉 $(j-1)$ 个 $9$ 和末位，剩下的数做前缀，且前缀的最后一位不得是 $9$，必须填上 $8$（如果能填的话），$8$ 的前面用若干 $9$ 和余数填充。

举个例子：

$\tt Hack\;Input\;5$

```
2
28 1
30 1
```

$\tt Hack\;Output\;5$

```
189
289
```

判完这些这题就结束了！代码如下：

```cpp
//CF1373-E
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,k;
signed main(){
    scanf("%lld",&T);
    while(T--){
        int ans=1e18;
        bool flag=false;
        scanf("%lld %lld",&n,&k);
        if(k==0){
            if(n%9!=0) printf("%lld",n%9);
            while(n>=9) printf("9"),n-=9;
            printf("\n");
            continue;
        }
        int y=n-(k+1)*k/2;
        if(y%(k+1)==0){
            if(y<0){
                printf("-1\n");
                continue;
            }
            y/=(k+1);
            if(k==9&&(n-45)%10==0){
                int delta=(n-45)/10;
                int cnt=delta%9;
                delta-=delta%9;
                while(delta>=9) cnt=cnt*10+9,delta-=9;
                ans=min(ans,cnt*10);
                flag=true;
            }
            for(register int i=1;i<=10-k-1;i++){
                int fx=y;
                if(i>=fx){
                    ans=min(ans,fx);
                    flag=true;
                    continue;
                }
                int cnt=0;
                fx-=i;
                cnt=cnt*10+fx%9;
                while(fx>=9) cnt=cnt*10+9,fx-=9;
                cnt=cnt*10+i;
                ans=min(ans,cnt);
                flag=true;
            }
        }
        for(register int i=0;i<k;i++){
            for(register int j=1;j<=17;j++){
                int p=n+(k-i)*j*9-(1+k)*k/2;
                if(p%(k+1)!=0) continue;
                int fx=p/(k+1);//找到一个数字和是fx，最后一位是10-i-1，最后一位前有j-1个9的最小数字
                //e.g. fx=40,j=4,i=2,最后一位7,9997答案是34，还差6，故数字是69997
                if(fx<0) continue;
                int lst=10-i-1,cnt=0;
                if(fx==(j-1)*9+lst&&fx<10){
                    ans=min(ans,fx);
                    flag=true;
                    continue;
                }
                fx-=(j-1)*9+lst;
                if(fx<0) continue;
                if(fx>=9){
                    fx-=8;
                    if(fx%9!=0) cnt=cnt*10+fx%9;
                    while(fx>=9) cnt=cnt*10+9,fx-=9;
                    cnt=cnt*10+8;
                    //构造方案应该是保证最后一位不是9的前提下，将前面尽可能用9填
                }else cnt=fx;
                for(register int r=1;r<=(j-1);r++) cnt=cnt*10+9;
                cnt=cnt*10+lst;
                if(cnt<0) continue;
                ans=min(ans,cnt);
                flag=true;
            }
        }
        if(flag) printf("%lld\n",ans);
        else printf("-1\n");
    }
}
```

---

## 作者：liangjindong0504 (赞：0)

### 前言

我的做法代码非常复杂，如果想看更简单的解法请移步其他题解。

### 思路

发现 $n$ 的范围较小。

同时发现 $k \le 9$，这告诉我们一个关键信息，就是只有最后一位会发生改变，前面只有进位。

于是考虑枚举个位数 $t$。

本人特判了答案为 $0$ 的情况，因为我的代码没有考虑这种情况。

特判很好搞，只需要暴力验证即可。

```cpp
if (k * (k + 1) / 2 == n) {
    std::cout << 0 << std::endl;
    return;
}
```

接下来是主体部分。

我们知道答案位数很小，因为如果每一位都填 9，k 取最小值 0 也只有 $\lceil \frac{150}{9} \rceil = 17$ 位。本人怕炸掉，所以使用了字符串存储。

我们分为最后一位进位和不进位两种情况。

#### 不进位。
这种情况比较简单，因为前面都是不会变的。所以知道了最后一位数 $t$ 就可以求出前面这些数位的位数和，进行贪心，尽可能填 9 即可。代码如下。


```cpp
if (t + k <= 9) {
	int tmp = n;
	tmp -= (t + t + k) * (k + 1) / 2;//个位数的总和
	if (tmp < 0) {//如果位数和已经超过 n 那么无效，可以退出
		continue;
	}

	if (tmp % (k + 1)) {//这时求出的 tmp 是 (k + 1) 个前面位数之和，所以如果不能被 (k + 1) 整除也要退出
		continue;
	}
	tmp /= (k + 1);

	std::string sum = "p";
	sum[0] = t + '0';

	while (tmp) {//进行贪心，尽可能填 9
		if (tmp >= 9) {
			sum = "9" + sum;
			tmp -= 9;
		} else {
			std::string k = "p";
			k[0] = tmp + '0';
			sum = k + sum;
			tmp = 0;
		}
	}
	ans = strmin(ans, sum);//由于字符串比较是按照字典序比，所以手写了一个比较函数
}
```

#### 进位
这种情况麻烦一点，因为我们要分最后一位有无发生进位讨论。并且，我们需要枚举终止进位的那一位，记为 $i$，这一位的数也需要枚举，记为 $x$。我们既然确定了终止进位的那一位，那么这一位和个位之间的数必然全是 9，不然前面就会终止。

这个时候我们会发现，第 $i$ 位之后的每一位都不会改变。于是我们可以求出这些不改变的数的和。


```cpp
tmp -= (t + k - 9) * (x + 1);//进位终止那一位最后会 +1
tmp -= (t + k - 10) * (t + k - 9) / 2;//末尾那一位进位了
tmp -= 9 * (i - 2) * (10 - t);//中间的 9，如果进位了都变成 0，不用考虑，故只考虑不进位的时候
tmp -= x * (10 - t);//进位终止的那一位在不进位的情况下的贡献
tmp -= (t + 9) * (10 - t) / 2;//末尾那一位
```

这样，我们就算出来了 (k + 1) 倍的前面那些数的和。于是我们依然运用尽可能多地填 9 的策略进行贪心，就能够完成了。

细节：注意 x 的范围是 $0 \sim 8$，因为这一位如果是 9 则可以接着进位。

```cpp
if (tmp < 0 || tmp % (k + 1)) {//不能被 (k + 1) 整除或者小于 0
	continue;
}

std::string sum = "p";
sum[0] = t + '0';
for (int j = 2; j < i; ++j) {
	sum = "9" + sum;
}

if (x == 0 && tmp == 0) {//另一个小特判，即如果终止进位的那一位是 0 且没有其他的位数了，那么直接取 min 并退出
	ans = strmin(ans, sum);
	continue;
}
std::string d = "p";
d[0] = x + '0';
sum = d + sum;//加上那一位终止进位的数
tmp /= (k + 1);
while (tmp) {//贪心填数
	if (tmp >= 9) {
		sum = "9" + sum;
		tmp -= 9;
	} else {
		std::string k = "p";
		k[0] = tmp + '0';
		sum = k + sum;
		tmp = 0;
	}
}
ans = strmin(ans, sum);
```

### 代码

最后便是完整代码（无坑，不带注释）。


```cpp
#include <bits/stdc++.h>

#define u32 unsigned
#define i64 long long
#define u64 unsigned long long

const std::string INF = "99999999999999999999999999999999999999999999999999999999999999999999999999999999999";

int n, k;

std::string ans;

std::string strmin (std::string x, std::string y) {
	int lx = x.size(), ly = y.size();
	if (lx < ly) {
		return x;
	} else if (lx > ly) {
		return y;
	}
	return std::min(x, y);
}

void solve() {
	std::cin >> n >> k;
	
	if (k * (k + 1) / 2 == n) {
		std::cout << 0 << std::endl;
		return;
	}
	ans = INF;
	
	for (int t = 0; t <= 9; ++t) {
		if (t + k <= 9) {
			int tmp = n;
			tmp -= (t + t + k) * (k + 1) / 2;
			if (tmp < 0) {
				continue;
			}
			
			if (tmp % (k + 1)) {
				continue;
			}
			tmp /= (k + 1);
			
			std::string sum = "p";
			sum[0] = t + '0';
			
			while (tmp) {
				if (tmp >= 9) {
					sum = "9" + sum;
					tmp -= 9;
				} else {
					std::string k = "p";
					k[0] = tmp + '0';
					sum = k + sum;
					tmp = 0;
				}
			}
			ans = strmin(ans, sum);
		} else {
			for (int i = 2; i <= 25; ++i) {
				for (int x = 0; x <= 8; ++x) {
					int tmp = n;
					tmp -= (t + k - 9) * (x + 1);
					tmp -= (t + k - 10) * (t + k - 9) / 2;
					tmp -= 9 * (i - 2) * (10 - t);
					tmp -= x * (10 - t);
					tmp -= (t + 9) * (10 - t) / 2;
					if (tmp < 0 || tmp % (k + 1)) {
						continue;
					}
					
					std::string sum = "p";
					sum[0] = t + '0';
					for (int j = 2; j < i; ++j) {
						sum = "9" + sum;
					}
					
					if (x == 0 && tmp == 0) {
						ans = strmin(ans, sum);
						continue;
					}
					std::string d = "p";
					d[0] = x + '0';
					sum = d + sum;
					tmp /= (k + 1);
					while (tmp) {
						if (tmp >= 9) {
							sum = "9" + sum;
							tmp -= 9;
						} else {
							std::string k = "p";
							k[0] = tmp + '0';
							sum = k + sum;
							tmp = 0;
						}
					}
					ans = strmin(ans, sum);
				}
			}
		}
	}

	if (ans == INF) {
		std::cout << -1 << std::endl;
	} else {
		std::cout << ans << std::endl;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int t;
	std::cin >> t;
	
	while (t--) {
		solve();
	}

	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

\*2200

考虑这样一个事情：给出 $f(x)$，求最小的 $x$，显然是从个位开始一直填 $9$ 最优。

如果不进位，显然是非常简单的，前面的和不变，枚举最后一位 $x$，那么前面的 $f$ 就是 $\dfrac{n-\frac{(k+1)(2x+k)}{2}}{k+1}$，如果无法整除显然不行。

考虑进位的情况，此时注意到如果后面存在连续的 $9$ 会一直进位，不妨枚举 $9$ 的出现次数 $i$。

枚举 $x$，前面位的 $f$ 仍然好算：$\dfrac{n-9i(10-x)-\frac{(x+9)(10-x)}{2}-\frac{(x+k-10)(x+k-9)}{2}-(x+k-9)}{k+1}$，注意此时个位只能选 $8$，否则会改变末尾 $9$ 的数量。

---

