# [SCOI2009] windy 数（加强版）

## 题目背景

**本题与 [P2657 [SCOI2009] windy 数](https://www.luogu.com.cn/problem/P2657) 的区别在于 $\bm{a}$ 与 $\bm{b}$ 的范围。**

windy 定义了一种 windy 数。

## 题目描述

不含前导零且相邻两个数字之差至少为 $2$ 的正整数被称为 windy 数。windy 想知道，在 $a$ 和 $b$ 之间，包括 $a$ 和 $b$，总共有多少个 windy 数？

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq a \leq b \leq 10^{18}$。

## 样例 #1

### 输入

```
1 10```

### 输出

```
9```

## 样例 #2

### 输入

```
25 50
```

### 输出

```
20
```

# 题解

## 作者：LinkCatTree (赞：14)

~~来水题解了。~~

由于 $a,b$ 范围较大，直接搜索肯定是不行的，考虑数位 dp。为方便，以下“第 $i$ 位”均表示从高位开始的第 $i$ 位（如最高位为“第一位”）。

令 $f[i][j]$ 表示 $i$ 位且以最高位为数字 $j$ 的 windy 数的个数。显然 $f[i][j]$ 可以通过枚举第二位的数字得到：$\displaystyle f[i][j]=\sum_{k=\max(j-2,0)}^{\min(j+2,9)} f[i-1][k]$，初始状态为 $f[1][i]=1(1 \leq i \leq 9)$。

接下来考虑如何计算 $a$ 到 $b$ 之间的 windy 数的个数。我们可以把答案拆成两个部分：**小于等于 $b$ 的 windy 数个数**与**小于 $a$ 的 windy 数个数**之差。我们发现这两部分是相似的（小于 $a$ 即为小于等于 $a-1$），只需要考虑如何计算小于等于某个数的 windy 数个数。

假设我们要求小于等于一个数 $a$ 的 windy 数个数，设其为 $m$ 位，其第 $i$ 位表示为 $r_i$。首先考虑位数比 $m$ 小的数中有多少个 windy 数：$\displaystyle \sum_{i=1}^{m-1}\sum_{j=1}^9 f[i][j]$。接着我们考虑有 $m$ 位但首位小于 $r_1$ 的 windy 数：$\displaystyle \sum_{j=1}^{r_1-1}f[m][j]$。

最后考虑 $m$ 位且首位为 $r_1$ 的 windy 数,这时我们需要考虑第二位的取值（因为第二位不能随便取，不能使用 $f[m][r_1]$ 来计算个数）。类似上面的，枚举第二位小于 $r_2$ 的（且小于等于 $r_1-2$）：$\displaystyle \sum_{j=1}^{\min(r_2-1,r_1-2)} f[m-1][j]$，然后考虑第二位为 $r_2$（如果 $r_1$ 和 $r_2$ 满足 windy 数的标准），枚举第三位的取值……

总的来说，如果 $a$ 的前 $l$ 位均满足 windy 数的性质（相邻两位之差大于等于 $r$），那么小于等于 $a$ 的 windy 数个数为：

$$\displaystyle \sum_{i=1}^{m-1}\sum_{j=1}^9 f[i][j]+\sum_{i=1}^{l+1}\sum_{j=1}^{\min(r_i-1,r_{i-1}-2)}f[i][j]$$

计算 $f$ 的时间复杂度为 $\mathcal{O}(n^2m)$，计算小于等于某个数的 windy 数个数的时间复杂度为 $\mathcal{O}(nm)$（其中 $n$ 为数字个数即 $10$，$m$ 为数字位数），空间复杂度为 $\mathcal{O}(nm)$。

代码如下，仅供参考：

```cpp
#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

ull f[20][10],power[20];
void init() {
	power[0]=1;
	for(int i=1;i<=19;i++) power[i]=power[i-1]*10;
	for(int i=0;i<=9;i++) f[1][i]=1;
	for(int i=2;i<=19;i++)
		for(int j=0;j<=9;j++)
			for(int k=0;k<=9;k++)
				if(abs(j-k)>=2)
					f[i][j]+=f[i-1][k];
	return ;
}
ull solve(ull x) {
	int w=0,y,pre;
	ull ans=0;
	while(power[w]<=x) w++;
	for(int i=1;i<w;i++)
		for(int j=1;j<=9;j++)
			ans+=f[i][j];
	y=x/power[w-1];
	for(int j=1;j<y;j++) ans+=f[w][j];
	pre=y,x%=power[w-1];
	for(int i=w-1;i>=1;i--) {
		y=x/power[i-1];
		for(int j=0;j<y;j++)
			if(abs(j-pre)>=2)
				ans+=f[i][j];
		if(abs(pre-y)<2) break;
		pre=y,x%=power[i-1];
	}
	return ans;
}

int main() {
	ull a,b;
	cin>>a>>b;
	init();
	cout<<solve(b+1)-solve(a)<<endl;
	return 0;
}
```

---

## 作者：__liujy (赞：12)

数位 DP 板子题。

一般的题，都能用 $dp_{pos,pre,up,zero}$ 来推公式。

其中 $pos$ 表示在哪一位，$pre$ 表示所传递的值，$up$ 表示这一位是否是最大值，$zero$ 表示这一位是否是 $0$。

实际上，在大多数情况下这才是最简单的一种实现方法，配合记忆化搜索就能免去一些循环了。同时思路更为清晰，但在限制过多时也有可能会被恶心到，但这样写前导零卡最高位也会变得十分简单。

然后来说一下动态转移方程：$dp_{pos,pre,up,zero}=dp_{pos,pre,up,zero}+dp_{pos-1,i,up\&\&(i==mx),0}$，其中 $i$ 在 $[zero?1:0,up?num_{pos}:9]$ 之间，$num_{i}$ 表示该数字的从后往前数第 $i$ 位，并且附加条件是 $|i-pres|\ge 2$，因为差值至少为 $2$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=20;
typedef long long LL;
typedef unsigned int UI;
typedef unsigned long long ULL;
int num[M],pos;
LL l,r,ans,dp[M][M][2][2];
inline LL dfs(int pos,int pre,bool up,bool zero)
{
	if(dp[pos][pre][up][zero]!=-1) return dp[pos][pre][up][zero];
	else if(!pos) return dp[pos][pre][up][zero]=1;
	dp[pos][pre][up][zero]=0;
	int mi=zero?1:0,mx=up?num[pos]:9;
	for(int i=mi;i<=mx;i++)
	{
		if(abs(i-pre)<2) continue;
		dp[pos][pre][up][zero]+=dfs(pos-1,i,up&&(i==mx),0);
	}
	return dp[pos][pre][up][zero];
}
inline LL solve(LL n)
{
	if(n<=9) return n;
	memset(dp,-1,sizeof(dp));
	LL ans=0;
	pos=0;
	do
	{
		num[++pos]=n%10;
		n/=10;
	}while(n);
	ans+=dfs(pos,11,1,1);
	for(int i=pos-1;i>=1;i--) ans+=dfs(i,11,0,1);
	return ans;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>l>>r;
	cout<<solve(r)-solve(l-1)<<'\n';
	return 0;
}
```

---

## 作者：Little_Deer_Peach (赞：9)

背景：由于写法前后矛盾导致出错，现已改正。

题意已经够简洁了不再赘述。

作为一道数位 DP 基础题，肯定要写一篇题解造福初学者。

先介绍一下数位 DP 实现的原理：类似于我们平常数数时，从 $1000$ 数到 $9999$，除了千位，后面三位都是从 $000$ 到 $999$ 的，所以我们可以把这些过程合并起来，并将所产生的计数答案也都存在一个的数组里，然后根据题目具体要求设置状态，用递推或 DP 的方式进行状态转移。

求一个区间内的答案我们可以利用前缀和的思想，将这个区间拆成两部分相减。这样就转换成求一个数内满足要求的数的数量。

那么怎么统计答案呢？考虑从高位开始枚举，考虑每一位可以填哪一些数，利用上文求出的数组求出答案。

回到这道题，是求相邻两个数的差不小于 $2$ 的数字数量。可以这样预处理：
```cpp

//dp[i][j]表示第i位填j的数字数量
for(int i=0;i<10;i++)dp[1][i]=1;//一位数都是 windy 数
for(int i=2;i<N;i++){//枚举位数
	for(int j=0;j<10;j++){//枚举当前填什么数
		for(int k=0;k<10;k++){//枚举上一位填什么数
			if(abs(j-k)>=2)dp[i][j]+=dp[i-1][k];//满足要求就加起来
		}
	}
}
```
统计答案：
```cpp
inline int solve(int x){
	len=0;//拆解数位
	while(x){
		num[++len]=x%10;
		x/=10;
	}
	int res=0;
	for(int i=1;i<len;i++){//因为不能有前导0，所以不满len位的数字特殊处理
		for(int j=1;j<10;j++){
			res+=dp[i][j];
		}
	}
	//开始处理len位数，接下来每处理完一位，都可以确定一位的数字（言语可能难以表达，可以模拟一下计数过程理解）
	for(int i=1;i<num[len];i++)res+=dp[len][i];
	for(int i=len-1;i>=1;i--){//逐渐枚举低位
		for(int j=0;j<num[i];j++){//枚举数字，必须小于num[i]（自行理解）
			if(abs(j-num[i+1])>=2)res+=dp[i][j];
		}
		if(abs(num[i]-num[i+1])<2)break;//因为前面几位已经确定，所以如果已经不满足了，就不用继续枚举
	}
	return res;
}
```
完整代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define endl '\n'
const int N=20;
int l,r;
int dp[N][N];
int num[N];
int len;
inline int solve(int x){
	len=0;
	while(x){
		num[++len]=x%10;
		x/=10;
	}
	int res=0;
	for(int i=1;i<len;i++){
		for(int j=1;j<10;j++){
			res+=dp[i][j];
		}
	}	
	for(int i=1;i<num[len];i++)res+=dp[len][i];
	for(int i=len-1;i>=1;i--){
		for(int j=0;j<num[i];j++){
			if(abs(j-num[i+1])>=2)res+=dp[i][j];
		}
		if(abs(num[i]-num[i+1])<2)break;
	}
	return res;
}
signed main(){
	IOS;
	for(int i=0;i<10;i++)dp[1][i]=1;
	for(int i=2;i<N;i++){
		for(int j=0;j<10;j++){
			for(int k=0;k<10;k++){
				if(abs(j-k)>=2)dp[i][j]+=dp[i-1][k];
			}
		}
	}
	cin>>l>>r;
    if(l>r)swap(l,r);
	cout<<solve(r+1)-solve(l);//solve中没有计算x，根据前缀和，((r+1)-1)-(l-1)就包含了整个区间
	return 0;
}
```
[记录](https://www.luogu.com.cn/record/224352972)。

---

## 作者：lcfollower (赞：5)

好不容易蹭到一个题解。

[前情回顾](https://www.luogu.com.cn/discuss/1099130)还有[这个](https://www.luogu.com.cn/discuss/1099363)，于是就有了这题。

---

某个帖子已经提示我们了，要写数位 dp。

数位 dp 的思想是 dp 与前缀和，我们记 $windy_i$ 为 $[1,i]$ 之间的 Windy 数，则 $windy_{[l ,r]} = windy_r - windy_{l - 1}$。

然后我们进行 dp，来设 $f_{pos ,lst}$ 表示到了第 $pos$ 位，前一位值是 $lst$ 的 Windy 数个数。我们从高位向低位 dp，这样方便我们后续做某些事情，下文展开。那么转移方程为 $f_{pos ,lst} = \sum\limits_{i = 0}^9 [i - lst \ge 2]\times f_{pos + 1 ,i} $，$i$ 表示枚举当前位数。

等一下，是不是有什么没有考虑？

是的，我们逐一攻破。

- 这一位数的可能范围一定是 $[0,9]$ 之间的整数。

  - 错误。假设正在求 $windy_x$，位数为 $cnt$，如果你是贴着边界的，也就是说第 $cnt\sim pos+1$ 位与 $x$ 的 $cnt\sim pos + 1$ 位是一样的，这样这一位的范围只能为 $[0,a_{pos}]$，其中 $a_{pos}$ 表示 $x$ 的第 $pos$ 位的值，因为 dp 要保证答案在 $x$ 及以内。
 
  - 反之，这一位可以随便选，范围为 $[0,9]$ 间的整数。

- 如果我们选了多个 $0$，该怎么办？

  - 这就表示可能有前导零的存在，但是多个 $0$ 分情况，并非一定是前导零。
 
  - 当这多个零前面已经有至少一个非零位的时候，无影响，这不是前导零。
 
  - 否则没有，这就是前导零，而理论上这个数不合法，但是这样我们考虑到了非 $cnt$ 位数的情况，这样我们把这一前导零视作没有就可以了，但是需要用变量记录一下。

- 所以好复杂，用啥实现啊。

  - dfs 即可，它更简单。如果你硬要不写 dfs 我也没办法。

- 我们的状态过多了，dfs 会超时。

  - 记忆化呗。

- 我们定的状态在贴着边界的时候不适用。

  - 因为当高位不贴边界时，低位可以自由选择，此时；若仍贴着上界，则需继续判断后续位是否越界‌，不可返回。
 
  - 同理在贴着边界的时候我们不应赋值 $f$ 数组。
 
- 好像在有前导零的时候也不适用。

  - 是的。前面有好多前导零，后面随便选，而这个状态默认前面没有前导零，是正常 $0$，选的范围也不同，比如 $[2,9]$。我们状态默认没有前导零，前面的就不能返回了。
 
  - 同理在有前导零的时候我们不应赋值 $f$ 数组。

```cpp
# include <bits/stdc++.h>

# define int long long
# define up(i ,x ,y) for (int i = x ; i <= y ; i ++)
# define dn(i ,x ,y) for (int i = x ; i >= y ; i --)
# define inf 1e14
 
using namespace std;
 
inline int read (){int s = 0 ; bool w = 0 ; char c = getchar () ; while (!isdigit (c)) {w |= (c == '-') ,c = getchar () ;} while (isdigit (c)){s = (s << 1) + (s << 3) + (c ^ 48) ; c = getchar ();}return w ? -s : s;}
inline void write (int x){if (x < 0) putchar ('-') ,x = -x; if (x > 9) write (x / 10) ; putchar (x % 10 | 48);}
inline void writesp (int x){write (x) ,putchar (' ');}
inline void writeln (int x){write (x) ,putchar ('\n');}

const int N = 25 ,mod = 1e9 + 7;
int f[25][10] ,a[25];
inline int dfs (int pos ,int lst ,bool leading ,bool limit){
//leading = 0 : 前导 0. 反之。
  if (!pos) return 1;
  if (leading && !limit && f[pos][lst] != -1) return f[pos][lst];//无前导零 + 不贴边界 + 记忆化.
  int lim = limit ? a[pos] : 9 ,res = 0;//lim 为选择边界。
  up (i ,0 ,lim)
    if (abs (i - lst) >= 2) res += dfs (pos - 1 ,
    (!leading && !i) ? -2 : i /*如果还能保持前导零那么 lst 为 -2，这样后面随便填，因为 0~9 - (-2) 都大于等于 2.*/,
    leading || i ,/*1.已经没有前导零了，2.这一位不为 0.*/
    limit && (i == lim));//是否贴着边界.
  if (!limit && leading) f[pos][lst] = res;//记忆化.
  return res;
} inline int solve (int x){
  int cnt = 0 ;
  memset (f ,-1 ,sizeof f);
  while (x) {
    a[++ cnt] = x % 10;
    x /= 10;
  } return dfs (cnt ,-2 ,0 ,1);
} signed main (){
  int l = read () ,r = read ();//writeln (solve (r));
  writeln (solve (r) - solve (l - 1));
  return 0 ;
}
```

---

## 作者：lyms_Hz17 (赞：4)

### 芝士：
数位 dp。

什么是数位 dp？

数位 dp 是指把一个数字按位数拆开。并按位数统计答案的一种 dp。为了做到不重不漏，一般从高位到低位统计。

如果这样说不太明了，不妨直接放到题目中理解。
### ~~自认为还行的~~讲解：
以本题举例，假设 $a = 1$、$b = 10$。我们很容易统计出答案，分别是 $1$、$2$、$3$、$4$、$5$、$6$、$7$、$8$、$9$。如果扩展到 $b=120$ 呢？注意到它具有很多完整的 $10$，那么我们有没有什么办法利用起来之前得到的结果来减少运算呢？

显然可以！不难想到按位数将 $120$ 打散成一些部分。如 $[1,10]$、$[1,100]$。但是考虑到每一位的前一位也影响统计，我们不妨将前一位也作为打散的标准来。于是变成了另一些部分，如 $[1,10]$、$[11,20]$、$[21,30]$、$[1,100]$、$[101,200]$。如此一来，便可以很容易的利用之前得到的结果了。

结合代码来看，所谓结合了上一位也就是给记忆化数组多开了一维作为一个状态。这样，数位 dp 的大体思路就得到了。但仍有细节需要注意，我们结合代码讲解。
```cpp
int dig[20];//拆完的数
lint dp[20][10];//记忆化数组

lint dfs(int pos, int last, bool lim, bool lead/*这两个就是细节了*/) {
	if(!pos) return 1;
	if(!lead and !lim and dp[pos][last] != -1) return dp[pos][last];//上文所说的再利用
	lint res=0; const int up = lim ? dig[pos] : 9;
	for(int i = 0; i <= up; i ++)
		if(abs(i - last) >= 2) {//题目要求
    		if(lead and !i) res+=dfs(pos-1, -100, lim and i==up, 1);
    		else res += dfs(pos-1, i, lim and i==up, 0);
        }
	return !lim and !lead ? dp[pos][last] = res : res;
}
```
注意到以上代码中有两个前面没有提到过的东西，$lim$ 和 $lead$，我们分别来说。

$lim$ 用来判断这个区间的完整性，从而判断可否拿来记忆，可否利用之前记忆的结果以及搜索的上界是什么。考虑这样一个情形，假如你要计算 $[1,13]$，你要处理 $[1,10]$，但你如何区分你处理的不是 $[11,13]$ 呢？于是 $lim$ 有用了。再考虑一个情景，假如你已经处理了 $[101,200]$ 的结果并将其记录，而你现在要运算的是 $[1,2122]$，你看到了一个 $[1101,1122]$，你知道不应该直接返回 $[101,200]$ 的结果，于是 $lim$ 就又有用了。

$lead$ 用来判断前导零的存在，有着判断可否向下一位传递结果和可否利用之前记忆的结果的作用。前导零是一个数最前面的 $0$。如 $011$ 有前导零而 $11$ 没有。可以将有前导零的数看做不完整的数字，它前面还要有东西的。所以它的作用就显然了（吧）。

如果还不明白的话，希望代码会有帮助。
### 完整代码：
```cpp
// code by 樓影沫瞬_Hz17
#include <bits/extc++.h>
using namespace std;
using lint = long long;

int dig[20];
lint dp[20][10];

lint dfs(int pos, int last, bool lim, bool lead) {
	if(!pos) return 1;
//已经搜到了第零位，说明返回后是第一位，故返回1
	if(!lead and !lim and dp[pos][last] != -1) return dp[pos][last];
//前两个条件表示我要搜完整的区间，后一个表示我搜过这个区间
	lint res=0; const int up = lim ? dig[pos] : 9;//有限制的话当然不能搜完所有了
	for(int i = 0; i <= up; i ++)
		if(abs(i - last) >= 2) {//题目条件
    		if(lead and !i) res += dfs(pos-1, -100/*意思是还没完呢，一串0*/, lim and i==up/*只有既到上界又有限制才能把限制下传*/, 1/*有前导0*/);
    		else res += dfs(pos-1, i/*last*/, lim and i==up, 0);//同理
        }
	return !lim and !lead ? dp[pos][last] = res : res;//记忆化
}

lint work(lint num) {
	int t = 0;//位数
	do dig[++t] = num % 10;//拆数
    while(num /= 10);
	return dfs(t, -100, 1, 1);//从上往下搜
}

int main(){
    memset(dp, -1, sizeof dp);
	lint A, B;
	cin >> A >> B;
//简单的容斥
	cout << work(B) - work(A-1) << endl;
	return 0;
}
```

---

## 作者：jojo_fan (赞：2)

## 思路
注意到：求 $a$ 与 $b$ 之间的 windy 数个数即为求小于等于 $b$ 的 windy 数个数减去小于 $a$ 的 windy 数个数。

用数位 dp 写。\
先预处理出  $dp$ 数组，再询问小于等于 $b$ 的 windy 数个数与小于 $a$ 的 windy 数个数后相减即可。

数位 dp 思路：
 $$dp[i][j]=\sum dp[i-1][k]$$
 其中： $i$ 代表位数， $j$ 代表当前位的数， $|j-k|\leqslant2$。

 剩下的详见代码。


```cpp
#include"bits/stdc++.h"
#define int long long  // 定义int为long long类型，以处理大数
using namespace std;

const int N=20;  // 定义常量N为20，用于表示数字的位数（最多18位+2位用于处理边界情况）
int n,m;  // 定义变量n和m，分别用于存储输入的a和b
int dp[N][N];  // 定义动态规划数组dp，dp[i][j]表示i位数且最高位为j的windy数的个数

// 动态规划预处理函数，计算dp数组
void Dp()
{
	for(int i=1;i<=18;i++)  // 遍历位数，从1位到18位
	{
		if(i==1) for(int j=0;j<=9;j++) dp[i][j]=1;  // 1位数时，每个数字都是windy数
		else for(int j=0;j<=9;j++) for(int k=0;k<=9;k++)  // 多位数时，遍历所有可能的最高位和次高位
			if(abs(j-k)>=2) dp[i][j]+=dp[i-1][k];  // 如果相邻两位数字之差大于等于2，则累加次高位为k的windy数个数
	}
}

// 计算小于等于给定数字x的windy数的个数
int work(int x)
{
	if(x==0) return 0;  // 如果x为0，则返回0
	vector<int> d;  // 定义一个vector存储x的每一位数字
	while(x) d.push_back(x%10),x/=10;  // 将x拆分为每一位数字并存储到vector中
	reverse(d.begin(),d.end());  // 反转vector，使其从高位到低位排列
	int ans=0,len=d.size(),last=-2;  // 初始化答案、长度和上一个数字为-2（边界条件）
	// 累加所有位数比x少的windy数的个数
	for(int i=1;i<len;i++) for(int j=1;j<=9;j++) ans+=dp[i][j];
	// 遍历x的每一位数字，累加小于等于当前位的windy数的个数
	for(int i=0;i<len;i++)
	{
		int start=(i==0)?1:0;  // 如果是最高位，则从1开始，否则从0开始
		for(int j=start;j<d[i];j++) if(i==0||abs(j-last)>=2) ans+=dp[len-i][j];  // 累加小于当前位的windy数的个数
		if(i>0&&abs(d[i]-last)<2) break;  // 如果相邻两位数字之差小于2，则提前退出循环
		last=d[i];  // 更新上一个数字为当前数字
		if(i==len-1) ans++;  // 如果是最后一位且满足条件，则当前数字本身也是一个windy数，累加1
	} 
	return ans;
}

// 主函数
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);  // 加速输入输出
	cin>>n>>m;  // 输入a和b
	Dp();  // 预处理dp数组
	cout<<work(m)-work(n-1);  // 输出结果，即小于等于m的windy数的个数减去小于n的windy数的个数
	return 0;
}

```

---

## 作者：be_RISK (赞：2)

数位 dp 板子题，只是不知道为什么被加强到这来了。

原理很简单，从高位到低位依次考虑，同时记录状态，总共 $4$ 个状态：
1. 当前位置；
2. 上一位数字；
3. 前导零是否到上一位；
4. 高位限制是否到上一位。
这里解释一下高位限制，即在跑数位 dp 时有一个上限，如果当前位以前的位上的数都等于上限的那几位数（如给定上限为 $1145141919810$，且此时 dp 的数为 $114514\_\ \_\ \_\ \_\ \_\ \_\ \_$），那么这一位也不能高于上限的这一位的数（延续刚才举的例子，那么下一位填的数只能 $\le 1$）。

在维护状态的同时维护一下题目给的 windy 数的条件，并记忆化地去搜索就好了。最后用 $r$ 为上限的答案减去 $l-1$ 为上限的答案输出就做完了（可以理解成类似于前缀和的东西）。

**注意：不开 long long 见祖宗。**

## 代码
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
/*
快读及定义数组不给
*/
int dfs(int id,int la,int q,int g){
	if(id>len)return 1;
	if(!g&&f[id][la]>=0)return f[id][la];
	int tmp=0,ret=0;
	if(g)tmp=s[id]-'0';
	else tmp=9;
	for(int i=0;i<=tmp;i++){
		if(abs(la-i)<2)continue;
		if(q&&i==0)ret+=dfs(id+1,-2,1,g&&i==tmp);
		else ret+=dfs(id+1,i,0,g&&i==tmp);
	}if(!g&&!q)f[id][la]=ret;
	return ret;
}
int solve(int x){
	int t=read()+x;
	memset(f,-1,sizeof f);
	s=to_string(t);
	len=s.size();
	s=" "+s;
	return (x>=0?1LL:-1LL)*dfs(1,-2,1,1);
}
main(){
  write(solve(-1)+solve(0),0);
  return ;
}
```

---

## 作者：FamousKillerconan (赞：2)

## 思路
可以使用数位 DP（以下用记搜写法，记搜更通俗易懂）。


首先，我们根据容斥原理，可以得知答案为 $[0,r]$ 里 windy 数的个数减去 $[0,l-1]$ 的 windy 数个数。


接下来就要计算区间里 windy 数的个数。


我们首先拆解这个右端点，然后进行遍历，把每一位进行计算，就这样，计算结束了。


可真只有这么简单吗？


你这么做肯定会超时，这时，我们就可以开一个数组来记录当前结果，介于重复情况很多，所以就可以减少计算。


AC 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define PII pair<int,int>
using namespace std;
const int N=105;
const int INF=0x3f3f3f3f;
const double EPS=10e-6;
const int MOD=1e9+7;
int a,b,dp[N][N],num[N];
int dfs(int dep,int lst,bool lead,bool limit){
	int ans=0;
	if(dep==0)return 1;
	if(!lead&&!limit&&dp[dep][lst]!=-1)return dp[dep][lst];
	int len;
	if(limit)len=num[dep];
	else len=9;
	for(int i=0;i<=len;i++){
		if(abs(i-lst)<2)continue;
		if(lead&&i==0)ans+=dfs(dep-1,-2,1,limit&&i==len);
		else ans+=dfs(dep-1,i,0,limit&&i==len);
	}
	if(!lead&&!limit)dp[dep][lst]=ans; 
	return ans;
}
int calc(int x){
	int len=0;
	while(x)num[++len]=x%10,x/=10;
	memset(dp,-1,sizeof dp);
	return dfs(len,-2,1,1);
}
void solve(){
	cin>>a>>b;
	cout<<calc(b)-calc(a-1);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T=1;
//	cin>>T;
	while(T--)solve();
	return 0;
}
```


### 闲话
这道加强版感觉和没加强一样。


可能是要卡分块打表吧。

---

## 作者：zph0717 (赞：1)

~~竟然还能写题解~~

## 1. 题意
统计 $[a,b]$ 范围内，相邻两位数字相差至少为 $2$ 的数的个数。

注意，前导零不算数字，也就是数字的第一位不受与前导零相差至少为 $2$ 的约束。

## 2. 解析
本题数据范围大，无法使用常规 $O(n \times log_{10}n)$ 方法。

显然能将原问题转换为求 $[1,n]$ 范围内该种数的个数。

发现，每一位上数字选取的可能性仅由以下因素决定：

1. 上一位选取的数（保证相差为 $2$）;
2. 之前是否一直为零（特判前导零情况）;
3. 之前是否一直卡着上界（确保不超过最大值）。

很自然地想到使用数位 DP 。由于需要维护第三点，故从高位向低位遍历。

 DP 数组 $dp[i][num][pre\in\{0,1\}][lim\in\{0,1\}]$ 表示：当前遍历到第 $i$ 位，选取的数为 $num$ ，之前为/不为前导零，是/不是一直卡着上界时，合法的数的总数。

其他详见代码。

## 3. 代码

```cpp
#include<bits/stdc++.h>
#define int long long//有用的东西
using namespace std; 
int a,b;
int dp[101][10][2][2];//第i位，为x，是否非前导零，是否卡着上限 
int lwg(int x){//数的位数
	int ans=0;
	while(x>0)
		x/=10,ans++;
	return ans;
}
int find(int x){
	if(x==0)
		return 0;
	memset(dp,0,sizeof(dp));
	int len=lwg(x),a[101];
	for(int i=1,j=1;j<=x;j*=10,i++)
		a[len-i+1]=(x/j)%10;//预处理出数的每一位
	dp[1][0][1][0]=1;
	for(int i=1;i<10;i++){//初始化dp数组
		if(i<a[1])
			dp[1][i][0][0]=1;
		else if(i==a[1])
			dp[1][i][0][1]=1;
	}
	for(int i=1;i<len;i++){ //当前位状态转移到下一位
		//前面全为前导零，一定不卡上界 
		dp[i+1][0][1][0]+=dp[i][0][1][0];//仍为前导零
		for(int j=1;j<10;j++)//下一位不再为前导零
			dp[i+1][j][0][0]+=dp[i][0][1][0]; 
		//前面并非全为前导零 
		for(int j=0;j<10;j++){
			for(int k=0;k<10;k++){
				if(abs(k-j)<2)
					continue;
				//卡上界 
				if(k<a[i+1])
					dp[i+1][k][0][0]+=dp[i][j][0][1];
				else if(k==a[i+1])
					dp[i+1][k][0][1]+=dp[i][j][0][1];
				//不卡上界 
				dp[i+1][k][0][0]+=dp[i][j][0][0];
			}
		}
	}
	int ans=0;//统计答案
	for(int i=0;i<10;i++)
		ans+=dp[len][i][0][0]+dp[len][i][0][1];
	return ans;
}
signed main(){
	cin>>a>>b;
	int c=find(a-1),d=find(b);
	cout<<d-c;
	return 0;
}
```

---

## 作者：Tracy_Loght (赞：1)

## 题目描述：

通过题目“相邻两个数字之差至少为 $2$ 的正整数”；

以及“在 $a$ 和 $b$ 之间，总共有多少个 windy 数”。

我们可以合理的推断，此题用**数位**动态规划做（因为此题要求的数是以每一位的差异区分的）。

这也变相告诉我们了，如果一道题目紧扣这一个数进行类位上的操作，那么大概率是**数位**动态规划了。

## 思路：

考虑这道题怎么做，显然唯一区分的条件只有相邻的数位差至少为 $2$。

考虑用微分的思想，先简化题目条件。

那么我们不处理大的数据，考虑处理类似于 $n \times 10^m$ 的答案。

这是好做的，考虑使用基本的动态规化：

```cpp
for(ll i=0;i<=20;i++)	zxy[1][i]=1;
for(ll i=2;i<=20;i++){
    for(ll j=0;j<=9;j++){
        for(ll k=0;k<=9;k++)
          if(abs(j-k)>=2)	zxy[i][j]+=zxy[i-1][k]; 
      }
}	
```

$zxy_{i,j}$ 表示做到了第 $i$ 位，现在的首位为 $j$ 的方案数。

接下来考虑拆位。

显然对于一个数 $x$，比如它是 51210。

我们将它进行分解：

```cpp
位数： 1       2       3       4       5

对应： 5       1       2       1       0

加乘： 5*10^4  1*10^3  2*10^2  1*10^1  0*10^0
```

然后想想为什么上一次我们要求出 $n \times 10^m$ 的答案。

是不是发现了什么规律。

我们的上一个朴素动规我们可以在拆位后使用。

有的同学问了，你的动规如果直接加的话有问题。

因为对于除了第一位，以后每一位的上一位都会有值，那么就会出现错误的情况。

是的，由于只有上一位的影响，考虑枚举上一位以及这一位即可。

呃？为什么要枚举这一位？因为上一位的不同，导致如果上一位比它的上限小，那么这一位的上限就是 $9$ 了。

及，如果考虑小于 $54$ 的 windy 数，那么 $49$ 也是一种情况（可能 $49$ 不在答案内，但仍然要考虑）。

最后，由于求的是一个区间（假设从 $a$ 到 $b$）的 windy 数，那么我们可以先求 $1$ 到 $b$ 的，然后减去 $1$ 到 $a-1$ 的即可。

## 代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,zxy[50][50],v[50],p[50];
void intor(){
	for(ll i=0;i<=20;i++)	zxy[1][i]=1;
	for(ll i=2;i<=20;i++){
		for(ll j=0;j<=9;j++){
			for(ll k=0;k<=9;k++)
				if(abs(j-k)>=2)	zxy[i][j]+=zxy[i-1][k]; 
		}
	}			
}
ll windy(ll x){
	ll ans=0,sl=0;
	while(1){//取位---直接取是反着的 
		if(x==0) break;
		else{v[++sl]=x%10;x=x/10;}
	}
	
	for(ll i=sl;i>=1;i--) p[i]=v[sl-i+1];//反转，其实也可以不用 
	for(ll i=1;i<=sl;i++) v[i]=p[i]; 
	
	for(ll i=1;i<=sl;i++) 
		for(ll j=1;j<=9;j++) 
			if(i!=sl||j<=v[1]-1) ans=ans+zxy[i][j];//直接加上 
			 
	for(ll i=sl;i>=1;i--) p[i]=v[sl-i+1];//反转，其实也可以不用 
	for(ll i=1;i<=sl;i++) v[i]=p[i];
	
	for(ll i=sl-1;i>=1;i--){
		for(ll j=0;j<=v[i]-1;j++)
			if(abs(j-v[i+1])>=2) ans=ans+zxy[i][j];//这里就是考虑上一位的影响了 
		if(abs(v[i+1]-v[i])<2) break;
	}
	for(ll i=1;i<=sl;i++) if(v[i]!=0) v[i]=0;//清空，下次还要用 
	return ans;
}
int main(){
	ios::sync_with_stdio(0);
	std::cin.tie(0);
	std::cout.tie(0);
	intor();cin>>n>>m;
	cout<<windy(m+1)-windy(n);
	return 0;
}

```

---

