# [ABC155E] Payment

## 题目描述

给定正整数 $N$，设 $f(x)$ 表示 $x$ 在十进制下各个数位上的数的和，求一个正整数 $x$ 满足 $x\ge N$ 且最小化 $f(x)+f(x-N)$。

## 说明/提示

$1\le N\le10^{1000000}$。

## 样例 #1

### 输入

```
36```

### 输出

```
8```

## 样例 #2

### 输入

```
91```

### 输出

```
3```

## 样例 #3

### 输入

```
314159265358979323846264338327950288419716939937551058209749445923078164062862089986280348253421170```

### 输出

```
243```

# 题解

## 作者：Grisses (赞：11)

## 题目大意

有 $10^{100}+1$ 种纸币，面值分别为 （$1,10,10^2,\cdots,10^{10^{100}}$），你想买一个价值为 $N$ 的商品，为了买到这个商品，你将付给商家一些钞票，而商家可能会找你一些钞票（如果你实际付款大于 $N$ 的话），问最少需要多少张钞票即可完成这次交易呢？

---

[本题](https://www.luogu.com.cn/problem/AT4866)是一道 DP 题。我们可以设 $s_i$ 表示 $N$ 从低到高第 $i$ 位上的数，$dp_{i,0}$ 表示第 $i$ 位由 $s_i$ 张 $10^{10^i}$ 凑出，$dp_{i,1}$ 表示第 $i$ 位找零凑出。

- 对于 $dp_{i,0}$ 就是求前 $i-1$ 位的最小值加上 $s_i$。我们可以让第 $i - 1$ 位由 $s_i$ 张 $10^{10^{i-1}}$ 凑出的值加上 $s_i$，即 $dp_{i,0}=dp_{i-1,0}+s_i$。或者多支付 1 张纸币，让 $s_{i-1}$ 由找零凑出，即 $dp_{i,0}=dp_{i-1,1}+1+s_i$。所以，$dp_{i,0}=\min(dp_{i-1,0},dp_{i-1,1}+1)+s_i$。

- 对于 $dp_{i,1}$，可以让 $s_{i-1}$ 由 $s_i$ 张 $10^{10^{i-1}}$ 凑出，即 $dp_{i-1,1}=dp_{i-1,0}+(10-s_i)$。也可以让 $s_{i-1}$ 由找零凑出来，这样的话，第 $i-1$ 位会多支付 1 张纸币，即 $s_i$ 要加 1。所以，这时的 $dp_{i,1}$ 就等于 $dp_{i-1,1}+(10-(s_i+1))$，即 $dp_{i-1,1}-1+(10-s_i)$。所以 $dp_{i,1}=\min(dp_{i-1,0},dp_{i-1,1}-1)+(10-s_i)$。

还有几个小细节在代码中讲解。

### 代码

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
char s[1000005];
long long int n,dp[1000005][2];//n表示N的长度，其余各变量意义同题解
int main()
{
	scanf("%s",s+1);//读入N
	n=strlen(s+1);//求N的长度
	dp[0][1]=INT_MAX;//第0位是不能用凑整得到的，将其初始化为极大值
	for(int i=1;i+i<=n;i++)swap(s[i],s[n-i+1]);//将N反转，让最低位到最前
	for(int i=1;i<=n;i++){
		s[i]-='0';
		dp[i][0]=min(dp[i-1][0],dp[i-1][1]+1)+s[i];
		dp[i][1]=min(dp[i-1][0],dp[i-1][1]-1)+(10-s[i]);//DP同题解
	}
	printf("%lld",min(dp[n][0],dp[n][1]+1));//因为dp[n][1]是需要找零的，所以还需1张
	return 0;
}
```

---

## 作者：Tenshi (赞：5)

传送门：[这里](https://www.luogu.com.cn/problem/AT4866)

## 分析
我们采取 dp 的做法。

为了直观地考虑这个问题，我们将原串用 $a$ 表示，根据题意，我们的目标是最小化 $\sum (b_i+c_i)$ （求最小代价）。

（洛谷的编辑器好像打不出竖式所以用图片代替了）
![](https://cdn.luogu.com.cn/upload/image_hosting/n4kmyrw1.png)

不失一般性，考察第 $i$ 位，分成两种情况讨论：

- 第 $i$ 位发生进位。

- 第 $i$ 位不发生进位。

对于第一种情况：
我们有 $a_i + b_i = 10 + c_i$ （因为发生了进位），要最小化 $b_i + c_i$ ，

因为 $b_i + c_i = 2b_i + a_i - 10$ ，我们只需要最小化 $b_i$ ，故让 $b_i = 10 - a_i$ 即可，相应地，可得 $c_i = 0$

类似地，在第二种情况中可得相应的 $b_i = 0,~ c_i = a_i$

下面开始 dp：$f[i][0/1]$ 表示第 $i$ 位不进位 / 进位下前 $i$ 位的最小代价。

如果第 $i-1$ 位没有发生进位，那么第 $i$ 位没有受到影响，直接针对上面的讨论进行转移即可。

如果发生进位，那么第 $i$ 位的 $a_i$ 相当于 $a_i+1$ 类似地进行转移。

结合转移方程理解：
$$f[i][0]=\min(f[i-1][0]+a[i], ~f[i-1][1]+a[i]+1)$$
$$f[i][1]=\min(f[i-1][0]+10-a[i],~ f[i-1][1]+10-1-a[i]);$$

代码：
```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=(a);i<=(b);i++)

int t(char ch){ // char 转 int
	return ch-'0';
}

const int N=1e6+5;

int f[N][2];

int main(){
	string s; cin>>s; int n=s.size(); reverse(s.begin(), s.end()); s=' '+s;
	
	f[0][1]=1, f[0][0]=0;
	rep(i,1,n){
		f[i][0]=min(f[i-1][0]+t(s[i]), f[i-1][1]+t(s[i])+1);
		f[i][1]=min(f[i-1][0]+10-t(s[i]), f[i-1][1]+10-1-t(s[i]));
	}
	cout<<min(f[n][1]+1, f[n][0]);
	
    return 0;
}
```

---

## 作者：STARSczy (赞：5)

# 思路：
输入的是字符数组，从末位开始枚举，每一位分类讨论。设下标从 $1$ 开始，每次枚举到 $x$，则：
- 若 $s_x = 5$，则加成 $0$ 或减成 $0$ 的次数都一样，故想到使用标记数组 p 标记第 $i-1$ 位是否可加一的情况，$ans$ 加上 $5$。
- 若 $0 \le s_x \le 4$，则一定是用 $s_x$ 张钞票最优，即将第 $i$ 位减成 $0$，$ans$ 加上 $s_x$。
- 若 $6 \le s_x+p_x \le 9$，则一定是用 $10-s_x-p_x$ 张钞票最优，因为 $p_x$ 是这一位可加可不加的标记，故最优是加一，即将第 $i$ 位加成 $10$，$ans$ 加上 $10-s_x-p_x$，前一位加上 $1$。

[AC code](https://atcoder.jp/contests/abc155/submissions/45983011)

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
const int maxn=1e6+10,mod=1e9+7;
using namespace std;
inline int read(){
	int c,w=0,n=0;
	while((c=getchar())<'0'||'9'<c) w=c=='-';
	do n=n*10+c-'0';while('0'<=(c=getchar())&&c<='9');
	return w?-n:n;
}
inline int write(int n){
	if(n<0) putchar('-'),n=-n;
	if(n>9) write(n/10);
	putchar(n%10+'0');
	return n;
}
using namespace std;
char s[maxn]={'0'};//下标0一定要标记，因为可能会进到最高位
int cnt,lazy[maxn]/*标记数组，标记这一位可加1可不加1*/;

signed main(){
	scanf("%s",s+1);
	for(int i=strlen(s+1);s[i];--i){//从最后一位往前枚
		if(s[i]=='9'+1) s[i-1]++,s[i]='0';//判断后一位是否进了一个1
		if(s[i]<'5') cnt+=s[i]-'0';
		else if(s[i]+lazy[i]>'5') cnt+='9'+1-s[i]-lazy[i],s[i-1]++;
		else cnt+=5,lazy[i-1]++;
	}
	write(cnt);
	return 0;
}
```

---

## 作者：MyukiyoMekya (赞：4)

$len\le 1000000$

像这种数据范围基本就是 $O(n)$ 扫了

我们倒着扫，记 $s_{i}$ 为当前位的数字，$s_{i-1}$ 为前一位

如果 $s_i$ 为 10（在后面的操作中会出现的），那么就执行进位 $s_i=0,s_{i-1} =s_{i-1}+1$

如果 $s_i<5$，那么很明显用 $s_i$ 张是最优的

如果 $s_i>5$，那么就用一张大的去换 $10-s_i$ 张小的，因为 $s_i>5$，即使是最坏的情况 $s_{i-1}<5$：进一位会让前一位多消耗一张，但 $10-s_i+1+1\le s_i $ 明显成立，所以一定不会更劣，反而有可能更优

如果 $s_i=5$，就要分类讨论了

如果 $s_{i-1}\ge5$，那么此时进一位会让前一位**少**使用一张，明显更**优**，于是就用一张大的去换 $10-5=5$ 张小的

如果 $s_{i-1}<5$，那么此时进一位会让前一位**多**使用一张，明显更**劣**，于是直接用 5 张就行了

注意要判断 $s_0$ 最后是否有被进位

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
const int MaxN=1000050;
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
char s[MaxN];
signed main(void)
{
	scanf("%s",s+1);
	reg int n=strlen(s+1);
	s[0]=0;
	reg int ans=0;
	for(int i=1;i<=n;++i)
		s[i]-='0';
	for(int i=n;i>=1;--i)
	{
		if(s[i]==10)
		{
			s[i]=0;
			++s[i-1];
		}
		if(s[i]==5)
		{
			if(s[i-1]>=5)
			{
				++s[i-1];
				ans+=5;
			}
			else
			{
				ans+=5;
			}
		}
		else if(s[i]<5)
		{
			ans+=s[i];
		}
		else if(s[i]>5)
		{
			ans+=10-s[i];
			++s[i-1];
		}
	}
	ans+=s[0];
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：MikukuOvO (赞：2)

贪心$+$大力分类讨论固然是可以的。

这里提供一种$DP$做法，从低位往高位考虑，我们考虑$f[i][0/1]$表示考虑到第$i$位，第$i$为是否进位了，不难列出转移方程：

$f[i][0]=min(f[i-1][0]+s[i],f[i-1][1]+s[i]+1)$

$f[i][1]=min(f[i-1][0]+10-s[i],f[i-1][1]+9-s[i])$

直接转移即可。

---

## 作者：Lydia1010__ (赞：2)

## 本题思路：
这道题其实很简单，我们只需要用到贪心的方法去做。

我们只需要先用字符串把数据存进去，然后用数组把每一位给存进去。

然后就可以进行判断：

* 如果当前这一位超过了九就进位，不算。

* 如果当前这位比五要小就直接把答案加上当前这一位的值。

* 如果比五要大就直接加上十去减当前一位即可，注意这里要进位。

* 如果等于五就判定下一位的值，下一位小于五就直接把答案加五，否则加上十减去这一位的数值，然后进位。

这里特别注意一下第一位直接加，不用判定，这样输出答案即可。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000001],cnt,ans;
string n;
int main()
{
	cin>>n;
	int m=n.size();
	for(int i=0;i<m;i++) a[++cnt]=n[i]-'0'/*,cout<<a[cnt];*/;
	for(int i=m;i>=1;i--)
	{
		if(a[i]>9) a[i]=0,a[i-1]++;
		if(a[i]<5) ans+=a[i];
		if(a[i]>5) ans+=10-a[i],a[i-1]++;
		if(a[i]==5)
		{
			if(a[i-1]<5) ans+=a[i];
			else ans+=10-a[i],a[i-1]++;
		}
	}
	cout<<ans+a[0];
	return 0;
}
```


---

## 作者：gac497 (赞：0)

# 问题描述

给定一个字符串 $N$，表示一个非负整数。我们需要通过以下操作将 $N$ 转换为一个数字 $d$：

1.将 $N$ 的每一位数字加到 $d$ 上。

2.如果某一位数字加上 $d$ 后大于等于 $10$，则需要进位。

3.每次进位需要额外支付 $1$ 的代价。

目标是找到一个 $d$，使得总代价最小。

# 解题思路

我们可以使用动态规划来解决这个问题。定义 $dp[i][carry]$ 表示处理到第 $i$ 位时，是否进位的最小代价。

## 状态定义

- $dp[i][0]$：处理到第 $i$ 位时，没有进位的最小代价。
- $dp[i][1]$：处理到第 $i$ 位时，有进位的最小代价。

## 状态转移

对于每一位数字 $N[i]$，我们尝试所有可能的数字 $d$，并计算相应的代价：
1. 如果 $d$ 加上当前位的数字 $N[i]$ 和进位 $carry$ 后小于 $10$，则不需要进位。

2. 如果 $d$ 加上当前位的数字 $N[i]$ 和进位 $carry$ 后大于等于 $10$，则需要进位，并支付 $1$ 的代价。

## 初始状态

- $dp[0][0] = 0$：表示处理到第 $0$ 位时，没有进位的代价为 $0$。
- $dp[0][1] = 10^9$：表示处理到第 $0$ 位时，有进位的代价为无穷大（不可能的情况）。

## 最终结果

我们取 $dp[n][0]$ 和 $dp[n][1] + 1$ 的最小值，因为最后一位可能会有进位。

# 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
char N[1000010];
int n,cost,digit,new_carry;
vector<vector<int> >dp(1000010,vector<int>(2,1e9));
int main(){
    scanf("%s",N);
    n=strlen(N);
    dp[0][0]=0;
    for(int i=0;i<n;i++){
        digit=N[n-i-1]-'0';
        for(int carry=0;carry<2;carry++){
            if(dp[i][carry]==1e9){
				continue;
            }
            for(int d=0;d<10;d++){
                new_carry=0;
                if(d<digit+carry){
					new_carry=1;
                }
                cost=(d-carry>=digit)?(d-digit-carry):(d-digit-carry+10);
                dp[i+1][new_carry]=min(dp[i+1][new_carry],dp[i][carry]+d+cost);
            }
        }
    }
    printf("%d",min(dp[n][0],dp[n][1]+1));
    return 0;
}

```

# 复杂度分析

时间复杂度：$O(n \times 10 \times 2)$，其中 $n$ 是 $N$ 的位数。

空间复杂度：$O(n \times 2)$。

这个算法能够有效地处理 $N$ 的范围，即使 $N$ 的位数非常大。

# 总结

通过动态规划，我们可以有效地解决这个问题，并找到使总代价最小的数字 $d$。

---

## 作者：封禁用户 (赞：0)

## 本题思路

#### 这题 $n$ 范围很大，可以考虑对 $n$ 每一位 $a_i$ 进行分类讨论，算贡献：

- $a_i>5$：$a_i$ 下一位 $a_{i+1}$ 加上个一，则 $a_i$ 本身贡献为 $10-a_i<a_i$。

- $a_i<5$：$a_i$ 的贡献就是他本身，因为如果进位贡献 $10-a_i>a_i$。

- $a_i=5$：看 $a_i$ 后一位 $a_{i+1}$ 如果加一后大于 5，则进位，否则不进，$a_i$ 贡献为 5。


## AC代码

```c
#include<bits/stdc++.h>
using namespace std;
string n;
int a[1000005];
long long ans=0;
int main()
{
	cin>>n;
	int len=n.size();
	for(int i=0;i<len;i++)
		a[len-i]=n[i]-'0';
	for(int i=1;i<=len;i++)
	{
		if(a[i]<5)ans+=a[i];
		if(a[i]>9)//处理进位
		{
			if(i==len)
				len++;
			a[i+1]+=a[i]/10;
			a[i]%=10;
		}
		if(a[i]==5)
		{
			ans+=5;
			if(a[i+1]>=5)//分类讨论
				a[i+1]++;
		}
		if(a[i]>5)
		{
			if(i==len)
				len++;
			a[i+1]++;
			ans+=10-a[i];
		}
	}
	cout<<ans;
	return 0;//完美结束
 } 
 ```

---

## 作者：YuYuanPQ (赞：0)

自己做的时候如果考虑 $a_i=5$ 的情况就做出来了。

结合题意及不寻常的数据范围，可以想到贪心。

用字符数组输入 $N$，将它转换为整型数组 a。其中，$a_i$ 对应着 $N$ 从左起的第 $i$ 位。

分类讨论（从最低位开始）。

先处理好 $a_i>9$，即进位的情况：把当前 $a_i$ 置零，下一位 $a_{i-1}$ 加上 $1$。

接下来：

- 当 $a_i<5$ 时：保持原数 $a_i$ 最优，贡献为 $a_i$。
- 当 $a_i>5$ 时：显然，改变为 $10-a_i$ 最优，贡献为 $10-a_i$，注意进位。
- 当 $a_i=5$ 时：
- 同理，再往前考虑一位。
- - 当 $a_{i-1}<5$ 时：保持原数 $a_i$ 最优，贡献为 $a_i$。
- - 当 $a_{i-1}>5$ 时，改变为 $10-a_i$ 最优，贡献为 $10-a_i$。

---

## 作者：Erica_N_Contina (赞：0)

# [ABC155E] Payment

## 题目描述

给定正整数 $N$，设 $f(x)$ 表示 $x$ 在十进制下各个数位上的数的和，求一个正整数 $x$ 满足 $x\ge N$ 且最小化 $f(x)+f(x-N)$。

$1\le N\le10^{1000000}$。

## 大意

有 $10^{100}+1$ 种纸币，面值分别为 （$1,10,10^2,\cdots,10^{10^{100}}$，实际上我们只用得到 $10^{10^6}$），你想买一个价值为 $N$ 的商品，为了买到这个商品，你将付给商家一些钞票，而商家可能会找你一些钞票（如果你实际付款大于 $N$ 的话），问最少需要多少张钞票（在支付与找零过程中）即可完成这次交易呢？

## 思路

我们用 $x_i$ 表示 $x$ 的第 $i$ 位。个位为第 $1$ 位，最高位为 $k$。

对于最差的办法，当然是取 $x=N$ 时，答案为 $\sum\limits_{i=1}^k x_i$。

那么我们怎么样让这个答案变小呢？我们考虑一个例子：假设 $N=190$，那么我们可以有一下方法。

- $x=100+10\times 9$

- $x=2\times 100-10$

很明显，下面的方法要用到的钞票更少。所以貌似进位是一个不错的办法。那么我们在什么时候考虑进位呢？我们再看到一个例子：

- $x=100+10\times 5$，代价 $6$。

- $x=2\times 100-10\times 5$，代价 $7$。

- $y=100+10\times 6$，代价 $7$。

- $y=2\times100-10\times 4$，代价 $6$。

我们发现，如果 $x_i≥6$，那么我们考虑进位是更优的。如果 $x_i≤4$，那么出 $4$ 张更优。

但是如果 $x_i=5$，我们要分类讨论：

- 如果 $x_{i+1}≥6$，那么进位之后 $x_{i+1}$ 变成了 $x_{i+1}+1$，类比例子中的 $y$，会让代价 $-1$，更优。考虑 $65$（代价 $1+4+5$）和 $70-5$（即 $100-30-5$）（代价 $1+3+5$）。

- 如果 $x_{i+1}=5$，那么进位后相当于例子中从 $x$ 到 $y$，代价不变，可以进位。这里我们直接考虑 $55$（代价 $5+5$）和 $60-5$（代价 $1+4+5$）。

- 如果 $x_{i+1}≤4$，那么不要进位，考虑 $45$（代价 $4+5$）和 $50-5$（代价 $5+5$）。

还有一个规律，就是每一位的代价都不能 $>5$。

然后我们从低位到高位扫一遍即可。

## 代码

```C++
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;

char n[N];
signed main(void) {
	scanf("%s",n+1);
	int ln=strlen(n+1);
	n[0]=0;
	int ans=0;
	for (int i=1;i<=ln;i++)n[i]-='0';//预处理
	for (int i=ln;i;i--) {
		if(n[i]==10)n[i]=0,++n[i-1];//处理进位 
		if(n[i]==5) {
			if(n[i-1]>=5) {
				n[i-1]++;
				ans+=5;
			} else ans+=5;
		}
		else if(n[i]<5)ans+=n[i];
		else if(n[i]>5) {
			ans+=10-n[i];
			n[i-1]++;
		}
	}
	ans+=n[0];//特判最高位是否向上进位 
	cout<<ans<<endl;
	return 0;
}
```




---

## 作者：cqbzhyf (赞：0)

[题面](https://www.luogu.com.cn/problem/AT4866)

首先这是一道简单的模拟题，再其次又和四舍五入有关系。

于是先输入，为方便之后处理，我们索性都将字符转化为数字。（这样就变成了整数数组）

几项规则：

1.当前位数字 $\ge10$，更高位（上一位）$+1$；

2.剩下的情况中除 $5$ 外都是借位来算，讲究策略：

（1）当前位数字 $\ge5$，答案加上 $10$ 减当前位数字；

（2）当前位数字 $\le5$，答案加上当前位数字；

3.为 $5$ 时，对上一位进行上一个判断。

**切勿忘记答案要加上最高位（最高位进位）！！！**

## 代码在这里

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000005];
unsigned long long ans;
signed main(){
	cin>>s+1;
	int n=strlen(s+1);
	for(int i=1;i<=n;++i)s[i]-='0';
	for(int i=n;i;--i){
		if(s[i]>=10)++s[i-1];
		else if(s[i]<5)ans+=s[i];
		else if(s[i]>5)ans+=10-s[i],++s[i-1];
		else{
			if(s[i-1]>=5)ans+=10-s[i],++s[i-1];
			else ans+=s[i];
		}
	}
	ans+=s[0];
	cout<<ans;
	return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

本题两种方法。
## 法一
贪心显而易见：我们选取用了当前纸币后剩下最少的钱数。

设每次操作时长度为 $k$，当前得到的数为 $n$。我们分以下 3 中情况讨论：

1. $a_i<5$，我们可以直接减去 $10^k$，次数为 $a_i$ 次。
2. $a_i>5$，我们应该是 $10_{k+1}-n$，因为借位的原因，注意 $a_i\gets a_i+1$，次数为 $10-a_i$ 次。
3. $a_i=5$，这是本题最为复杂的情况，次数显而易见，为 $5$ 次。但方案有点困难此时，我们就必须“顾后”，看后一个选择的是哪个操作：若为 1 操作，什么也不执行，显然是最好的方法；若为 2 操作，我们可以本次执行二操作，这样 $a_i\gets a_i+1$，操作次数少 1，显然最优；若仍为 3 操作，我们执行 2 操作，因为这样可以使后一个数更大，继而使后两个数更大，显然选 2 操作。 
### 注意
注意此处从高到低枚举，因为高精度输出竖式是逆序模拟的；2 操作后可能 $a_i>9$，那么我们不必执行 $a_i\gets a_i\bmod 10$，因为它执行 2 操作，可以使答案变小；如果最后一次执行二操作，那么最后还必须加上 1.
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int len,ans,a[1000005];
int main(){
	cin>>s;
	len=s.size();
	s='0'+s;
	for(int i=0;i<=len;++i)
		a[i]=s[i]-'0';
	for(int i=len;i>=1;--i)
		if(a[i]==5){
			if(a[i-1]>=5)
				++a[i-1];
			ans+=5;
		} else if(a[i]<5)
			ans+=a[i];
		else{
			ans+=10-a[i];
			++a[i-1];
  		}
	cout<<ans+a[0]<<endl;
	return 0;
}
```
## 法二
因为上面的贪心思路显然可以用搜索实现，所以我们可以想到记忆化搜索，也就是 dp。

首先，定义状态：$dp_{i,0}$ 表示选择方案 1；$dp_{i,1}$ 表示选择方案 2.由上面的贪心策略可易得滚动数组优化后的 dp：

$dp_0\gets\min{(dp_0,dp_1+1)}+a_i$

$dp_1\gets\min{(dp_0+1,dp_1)}+9-a_i$

同贪心，本处模拟竖式，仍倒序枚举，然后答案为 $\min{(dp_1+1,dp_0)}$
### AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[2],len,a[1000005];
string s;
int main(){
	while(scanf("%1d",&a[++len])!=EOF);
    --len;
	dp[1]=1;
	for(int i=len;i>=1;--i){
		int k=dp[0];
		dp[0]=min(dp[0],dp[1]+1)+a[i];
		dp[1]=min(k+1,dp[1])+9-a[i];
	}
	printf("%d",min(dp[1]+1,dp[0]));
    return 0;
}
```

---

## 作者：watcher_YBH (赞：0)

# 思路：
这道题我们用贪心并按位考虑。首先我们把每一位 $a_i$：

1. 当 $a_i > 5$ 时，这个时候肯定进个位是最优的，因为进一位的话，$a_i$ 的贡献为 $10 - a_i$。

2. 当 $a_i < 5$ 时，这个时候肯定不进位是最优的，因为进一位的话，$a_i$ 的贡献为 $10 - a_i$，比原本的 $a_i$ 大。

3. 当 $a_i = 5$ 时，这个时候就要分情况，因为这个时候进位或不进位，这一位的贡献都是 $5$，但是当 $a_{i+1} \ge 5$ 时，$a_i$ 进个位后 $a_{i+1}$ 的贡献会 $-1$。

我们来手动模拟一下：

$$65 = 70-5 = 100-35$$

则这个时候的答案为 $1+3+5 = 9$ 比 $6+5 = 11$ 小。

# 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define max(a,b) ((a)>(b)?a:b)
#define min(a,b) ((a)<(b)?a:b)
using namespace std;
const int MAX = 1e6+5;
string n;
int ans,a[MAX];
int main(){
	cin>>n;
	for(int i = 0; i<n.size(); i++)// 把每一位改为int 
		a[i+1] = n[i]-'0';
	for(int i = n.size(); i>=1; i--){
		if(a[i] > 9) a[i] = 0,a[i-1]++;// 处理进位（因为我这里是倒着存的所以更高位是a[i-1]） 
		if(a[i] < 5) ans += a[i];// 情况2 
		else if(a[i] > 5) ans += 10-a[i],a[i-1]++;// 情况1 
		else{// 情况3 
			if(a[i-1] < 5) ans += a[i]; 
			else ans += 10-a[i],a[i-1]++;
		}
	}
	cout<<ans+a[0];// 把最后一位加上 
	return 0;
}
/* 模拟： 
3 = 10-7 => 8
6 = 10-4 => 5
5 = 10-5 => 6（5的前一位是0，这种方法不是最优）

65 = 70-5 = 100-35 => 9
55 = 60-5 = 100-45 => 10
45 = 50-5 => 10 （5的前一位是4，这种方法不是最优）
*/
```


---

