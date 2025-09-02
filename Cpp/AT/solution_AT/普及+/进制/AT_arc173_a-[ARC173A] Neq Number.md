# [ARC173A] Neq Number

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc173/tasks/arc173_a

正整数 $ X $ が以下の条件を満たすとき、$ X $ は **“Neq Number”** であるといいます。

- $ X $ を十進法表記した際、どの隣接する $ 2 $ 文字も相異なる
 
例えば $ 1,173,9090 $ は “Neq Number” です。一方、 $ 22,6335 $ は “Neq Number” ではありません。

正整数 $ K $ が与えられます。小さいほうから $ K $ 番目の “Neq Number” を求めてください。

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 100 $
- $ 1\ \leq\ K\ \leq\ 10^{12} $
- 入力される値はすべて整数
 
### Sample Explanation 1

$ 1 $ つめのテストケースについて、 “Neq Number” を小さいものから $ 25 $ 個あげていくと - $ 1 $ から $ 9 $ までの整数の $ 9 $ 個 - $ 10 $ から $ 19 $ までの整数のうち、 $ 11 $ を除いた $ 9 $ 個 - $ 20 $ から $ 27 $ までの整数のうち、 $ 22 $ を除いた $ 7 $ 個 となります。よって、小さいほうから $ 25 $ 番目の “Neq Number” は $ 27 $ となります。

## 样例 #1

### 输入

```
3
25
148
998244353```

### 输出

```
27
173
2506230721```

# 题解

## 作者：无名之雾 (赞：8)

~~赛时一遍过，开心！~~

## 思路

我们对于一个数字进行二分查找一个数字 $x$。判断 $\le x$ 的 Neq 数有多少个。这里我们运用一个类似于数位 dp 的方法来进行判断。

赛后想了想发现：实际上就是与上一个不同，有 $9$ 种选择，类似于 $9$ 进制即可解决这题。~~我好傻。~~

[赛时通过记录](https://atcoder.jp/contests/arc173/submissions/51135942)

### 数位 dp 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair <int, int> pii;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int f[30][10][2][2],ch[30];
int calc(int x){
	memset(f,0,sizeof f);
	memset(ch,0,sizeof ch);
	int len=0;
	while(x)ch[++len]=x%10,x/=10;
	for(int i=0;i<=ch[len];i++)f[len][i][i==ch[len]][i==0]=1;
	for(int i=len-1;i>=1;i--){
		for(int j=0;j<=9;j++){
			for(int k=0;k<=9;k++){
				for(int op=0;op<=1;op++){
					for(int qd=0;qd<=1;qd++){
						if(j==k&&!qd)continue;
						if(op&&j>ch[i])continue;
						f[i][j][op&&j==ch[i]][qd&&j==0]+=f[i+1][k][op][qd];
					}
				}
			}
		}
	}
	int res=0;
	for(int i=0;i<=9;i++)res+=f[1][i][0][1]+f[1][i][1][1]+f[1][i][1][0]+f[1][i][0][0];
	return res;
}

signed main() {
	int n=read();
	for(int i=1;i<=n;i++) {
		int p=read();
		int l=0,r=1e18;
		while(l<=r){
			int mid=(l+r)>>1;
			if(calc(mid)<=p)l=mid+1;
			else r=mid-1;
		}
		cout<<l<<"\n";
	}
	return 0;
}
```

### $9$ 进制解决问题代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
    int T;
	cin>>T;
	while(T--){
		int k;
        cin>>k;
        int wei=0,cheng=1,last=0;
        while(k>=cheng) k-=cheng,wei++,cheng*=9;
        while(wei){
            cheng/=9,wei--;
            cout<<k/cheng+(k/cheng>=last);
            last=k/cheng+(k/cheng>=last);
            k-=k/cheng*cheng;
        }
        cout<<endl;
    }
	return 0;
}
```

---

## 作者：Cells (赞：4)

#### 思路

很简单的记忆化搜索，二分答案，然后数位 DP 返回答案，检查答案是否符合要求

#### 注意事项

1. 二分上界不会很大，因为这种数会很集中，`r` 只用到 $10^{13}$ 左右就可以了。
2. 需要判断前导零的特殊情况，0 不是正整数，所以不在答案计算范围之内。
3. 判断当前数字是否和前一个数相等时需要判断当前数字并且有前导 0 的情况，不能算作不合法

**Code**

```c++
# include <bits/stdc++.h>
# define mem(a, b) memset(a, b, sizeof (a))
using namespace std;

typedef long long LL;

const LL UP = 1e13;//最大就是这么多 

int T, len, a[20];
LL k;
LL f[20][11];

LL dfs(int pos, int pre, bool limit, bool lead){//pos是当前在第几位,pre是前一位,limit表示顶住上限没有,lead表示有没有前导零 
	if(!pos) return !lead;//0不是正整数,不能算在答案里 
	if(!limit && !lead && ~f[pos][pre]) return f[pos][pre];//记忆化 
	
	LL sum = 0;//答案 
	int range = limit ? a[pos] : 9;//有限制最大只能是a[pos] 
	for(int i = 0; i <= range; i ++){
		if(!lead && (i == pre)) continue;//有前导零并且i==0时不能排除 
		sum += dfs(pos - 1, i, limit & (i == range), lead & (!i));
	}
	
	if(!limit && !lead) f[pos][pre] = sum;//记忆化 
	return sum;
}

LL solve(LL x){
	len = 0; //注意f数组不需要清成-1,因为我特判了lead和limit 
	while(x) a[++ len] = x % 10, x /= 10;
	return dfs(len, 0, true, true);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> T;
	mem(f, -1);//f数组初始化-1 
	
	while(T --){
		cin >> k;
		LL l = 0, r = UP;
		while(l < r){
			LL mid = l + r >> 1; // 二分答案 
			if(solve(mid) < k) l = mid + 1;//Neq数太少,l不可能是答案 
			else r = mid;
		}
		
		cout << r << "\n";
	}
	
	return 0;
}
```

感谢大佬们的支持。

完结撒花！！！

---

## 作者：liangjindong0504 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc173_a)\
[AT 题目传送门](https://atcoder.jp/contests/arc173/tasks/arc173_a)

~~我绝对不会告诉你这是我赛时唯一通过的题。~~

这题做起来有数位 dp 的感觉啊。
### 题意简述
给你一个数 $n$，让你求第 $n$ 个没有两个相邻数字是相同的数，从 1 开始计数。

注意有多组数据。
### 思路分析
为了简洁，将上面所述的这种数称为“好数”。

既然第 $n$ 个数不太好求（对我来说），我们考虑查找某一个数，小于或等于它的好数的个数。

显然，暴力枚举会超时（$10^{18}$），因此考虑二分查找，这样时间复杂度便降了下来。而因为最后查找到的数一定是好数（否则还可以继续往前二分），所以这种方法是正确的。

对于每一个数，应该分成三部分去考虑。

1. 第一部分，是对于位数小于它的数。

   对于这种，最高位有 9 种选择（1 到 9）。而下一位，则是也有 9 种选择（0 到 9 中不是前一位的）。经过推理，$x$ 位数一共有 $9^x$ 个好数。于是，答案很快就能够统计出来：$\sum_{k=1}^{len-1} 9^k$，其中 $len$ 为二分的数的位数。

1. 第二部分，是对于位数等于它的数，其中最高位小于二分的数的最高位（有点数位 dp 的意思了）。

   显然，我们可以枚举最高位，同时统计答案。这时候，与第一部分不同了，因为最高位已经确定。但是，后面几位统计答案方式都与第一部分相同，故答案为 $(a-1) \times 9^{len-1}$，其中 $a$ 为最高位的数字，$len$ 为这个数的位数。

1. 第三部分，是对于位数等于它的数，其中最高位等于它的数。

   这时候，我们可以逐位枚举（当然每一位都要小于这个数的这一位，才能保证大小）。当第 $x$ 位确定时，答案应该增加 $9^{x-1}$。这时答案即为第 $x$ 位前面的数字都与该数相同，第 $x$ 位正在被枚举，后面这些数位的总共数量。（这部分可能表述不清，详见代码）。

特别地，刚开始统计答案值要设置为 1，因为还有一种：就是等于该数的一种。（如果这个数不是好数也没关系，最后肯定会二分到一个好数上）。
### 代码实现
码风较丑，勿喷
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n,t,l,r,mid;
int get1(int x){
	//初始sum设为0 
	int a[17],sum=1,len=0;
	//一位一位拆分这个数 
	while(x){
		a[++len]=x%10;
		x/=10;
	}
	//第一部分
	for(int i=1;i<len;i++) sum+=pow(9,i);
	//第二部分 
	sum+=(a[len]-1)*pow(9,len-1);
	//第三部分 
	for(int i=len-1;i>=1;i--){
		//枚举小于该位的数 
		for(int j=0;j<a[i];j++){
			//统计答案，当然前一位显然不能等于这一位 
			if(a[i+1]!=j) sum+=pow(9,i-1);
			else continue;
		}
		//出现了等于，直接退出（再往下没有意义，前面已经有相邻两位相等了） 
		if(a[i]==a[i+1]) break;
	}
	return sum;
}
signed main(){//我将int都设成了long long 
	cin>>t;
	while(t--){
		cin>>n;
		//二分。这个范围不会太大，上界明显设太大了（赛时保险起见） 
		l=1,r=1e15; 
		while(l<=r){
			mid=l+(r-l)/2;
			//这个get1就是统计个数的 
			if(get1(mid)<=n) l=mid+1;
			else r=mid-1;
		}
		//这里是保证l<r的 
		if(l>r) swap(l,r);
		//最后答案当然是在l和r之间的一个
		//肯定要取最小（取较大的不能保证它是不是好数），因此输出l。 
		cout<<l<<endl;
	}
	return 0;//功德圆满
}
```

---

## 作者：GI录像机 (赞：3)

## 思路


简单的数位 dp。设 $dp_{i,j}$ 表示十进制下有 $i$ 位且以 $j$ 开头的 neq 数数量。

这个很好转移，即 $dp_{i,j}=\sum^9_{k=0} dp_{i-1,k}[j\neq k]$，初值就是 $dp_{1,j}=1$。

重点是怎么通过这个数组来求出第 $k$ 小的 neq 数。

设 $sum_i$ 表示位数小于等于 $i$ 的 neq 数数量，那么我们只需要找到最大的 $i$ 使得 $k>sum_{i-1}$ 就能得知答案的位数。

这个也很好求，就是把前面所有 $j\neq0$ 的 $dp_{i,j}$ 加起来。

使 $k=k-sum_{i-1}$，这样问题变为寻找 $>10^{i-1}$ 的数中第 $k$ 小的数是谁。

现在只需要求第一位的数是谁，第二位的数是谁，以此类推。发现寻找的过程高度相似，于是使用递归做法。

在寻找的过程中，延续我们之前的想法，让 $k$ 减去前面的 neq 数数量，缩小问题范围。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 20, MOD = 1e9 + 7, INF = 0x3f3f3f3f;
int t = read(), dp[N][N], tmp, sum[N];
void fin(int idx, int las) {
	if(!idx)return;
	for (int i = 0; i <= 9; i++) {
		if(las == i)continue;//要保证减去的是 neq 数
		if(tmp > dp[idx][i])tmp -= dp[idx][i];
		else {
			putchar(i + '0');
			fin(idx - 1, i);
			return;
		}
	}
}
signed main() {
	for (int i = 0; i <= 9; i++)dp[1][i] = 1;
	sum[1] = 9;
	for (int i = 2; i <= 13; i++) {
		for (int j = 0; j <= 9; j++) {
			for (int k = 0; k <= 9; k++) {
				if (j == k)continue;
				dp[i][j] += dp[i - 1][k];
			}
			if (j)sum[i] += dp[i][j];
		}
		sum[i] += sum[i - 1];
	}
	while (t--) {
		int n = read(), idx = 0;
		tmp = n;
		for (int i = 13; i >= 1; i--) {
			if (tmp > sum[i - 1]) {//比之前的 neq 数数量大
				idx = i;
				tmp -= sum[i - 1];
				break;
			}
		}
		fin(idx, 0);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：TankYu (赞：2)

和 std 非常不同的做法，应该优于 std，但细节极多，若您不是这个思路，建议不要按这种写法。

整体上思路是按位构造出第 $k$ 小的 `Neq Number`。

记 `Neq Number` 为 **好** 的数，预处理的位数均令 **最高位** 是第一位，而构造时则令 **最低位** 是第 $1$ 位。

首先除去 $0$，所有一位数都是好的，对于两位数，发现只有 $11,22,33,\cdots,99$ 不是好的。那么两位数中便有 $90 - 9$ 即 $81$ 个数是好的。

接下来考虑 $n \ge 3$ 位好数，发现 $n$ 位好数中，第一位共有 $9$ 种可能，对应的第二位若为 $0$，则第三位不为 $0$ 即可，观察出 **第三位及以后不受前两位影响**；若第二位不为 $0$，则第二位共有 $8$ 种可能，可以视作一个 $n-1$ 位数，前面添了一位。

接下来看出有一个比较显然但极其有用的性质：对于一个 $x$ 位数，设 $pos_{x,i}$ 表示第一位填 $i$、其它位任意时能生成多少个好数，则有 $pos_{x,1} = pos_{x,2} = \cdots = pos_{x,9}$。

故设 $num_n$ 为 $n$ 位数中好数的数量，则有

$$num_n = 9(\frac{8 \cdot num_{n - 1}}{9}+num_{n-2})=8\cdot num_{n-1} + 9\cdot num_{n-2}$$

这个式子的含义是第一位数 $9$ 种选法，其后对于第二位不填 $0$ 由上述分析可知有 $\dfrac{8}{9}num_{n-1}$ 种，选 $0$，则在后面接一个 $n-3$ 位数。

注意不会有连续 $2$ 个 $0$，所以是对的。

接下来，令 $e_n = \frac{num_n}{9}$，$pre_n = \sum\limits_{i=1}^{n} num_i$，$e_n$ 表示的便是 $n$ 位数中第一位固定时好数的个数，$pre_n$ 表示 $1$ 至 $n$ 位数中好数的和。

从高位至低位构造第 $k$ 小的好数。

不妨设第 $k$ 小的好数为 $n$ 位数 $\overline{x_nx_{n-1}x_{n-2}\dots x_1}$，已经构造 $m$ 位为 $\overline{a_na_{n-1}\dots a_{n-m+1}}$，现在我们构造第 $n - m$ 位，这一位上的数设为 $P$。

再设 $\overline{a_na_{n-1}\dots (a_{n-m+1} - 1)\dots}$ 中最大的好数是第 $S$ 小的。

首先考虑 $m > 0$，即已经至少有一位被构造出，这样做是为处理前导 $0$ 的问题。

能发现的是，这一位能填 $P$ 首先需要满足 $\overline{a_n\dots a_{n-m+1}(P-1)\dots}$ 中最大的好数是第 $l < k$ 个好数，注意上面式子 $P-1$ 是第 $n - m$ 位上的数。

而这个数，是第 $S + P \times e_{n - m} + pre_{n-m-1}$ 个好数 $^\dagger$。

那么 $S + P \times e_{n - m} + pre_{n-m-1} < k$。

解不等式得 $P < \dfrac{k - S - pre_{n-m-1}}{e_{n-m}}$。

由整数的离散性：

$P \le \left\lceil\dfrac{k - S - pre_{n-m-1}}{e_{n-m}} \right\rceil - 1$。

$\dagger$：注意，可能存在因 $P \ge a_{n-m+1}$ 而出现以上式计算贡献时出现了多算一个 $e_{n-m}$的情况（此时多算了一个两位相等即不是好数的贡献），这需要特判，此情况下 $P \le \left\lceil\dfrac{k - S - pre_{n-m-1}}{e_{n-m}} \right\rceil$。

对第一位要考虑不能放 $0$ 的问题，对个位也要考虑可以 $0$ 的问题。

以下是实现时做出的一些变通：

+ 为了简化代码，省去了计算 $S$，每次直接把 $\Delta S$ 算进 $k$ 里。

+ 特判 $pre > k$ 以免算出 $P < 0$

+ 实现时因为 ans 先乘上 $10$，所以 `ans / 10 % 10` 即 $a_{n-m+1}$。

```cpp
LL num[20];
LL every[20];
LL pre[20];

int main()
{
    int t;
    cin >> t;
    num[1] = 9;
    num[2] = 81;
    for (int i = 3; i <= 17; i++)
    {
        num[i] = num[i - 1] * 8 + num[i - 2] * 9;
    }
    for (int i = 1; i <= 17; i++)
    {
        pre[i] = pre[i - 1] + num[i];
    }
    for (int i = 1; i <= 17; i++)
    {
        every[i] = num[i] / 9;
    }
    while (t--)
    {
        LL k;
        cin >> k;
        if (k <= 9)
        {
            cout << k << '\n';
            continue;
        }
        int now = 17;
        LL ans = 0;
        while (k)
        {
            ans *= 10;
            if (ans == 0)
            {
                if (pre[now - 1] <= k)
                {
                    if (now != 1)
                    {
                        LL tmp = (k - pre[now - 1] + every[now] - 1) / every[now];
                        ans += tmp;
                        k -= tmp * every[now];
                    }
                    else
                    {
                        ans += k - 1;
                        break;
                    }
                }
            }
            else
            {
                if (pre[now - 1] <= k)
                {
                    if (now != 1)
                    {
                        LL tmp = (k - pre[now - 1] + every[now] - 1) / every[now];
                        if (tmp >= ans / 10 % 10)
                        {
                            ans += tmp - 1;
                        }
                        else
                        {
                            ans += tmp;
                        }
                        k -= (tmp + 1) * every[now];
                    }
                    else
                    {
                        if (k > ans / 10 % 10)
                        {
                            ans += k;
                        }
                        else
                        {
                            ans += k - 1;
                        }
                        break;
                    }
                }
            }
            now--;
            if (now == 0)
            {
                break;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
```

后记：赛时没过，因为特判 $k\le 9$ 时 **没换行**，于是写篇题解纪念一下。个人感觉思路比较自然，强于 std 的二分套数位 dp。这个写法是 $\Theta(t \log_{10} k)$ 的，应该比 std 优。

另外，有些地方可能讲的不太明白，不理解可以手模小数据，感性理解一下。

---

## 作者：Shadow_T (赞：2)

### 前言

建议难度蓝。

### 题目大意

定义 Neq 数的十进制相邻数位不相同。求第 $k$ 小的 Neq 数。

### 题目分析

省流：[windy 数](https://www.luogu.com.cn/problem/P2657)套二分。

可以用数位 dp 条件为相邻数位差 $\geq 1$ 求出小于 $x$ 的 Neq 数数量。设 $dp_{i,j}$ 为长度为 $i$ 中最高位是 $j$ 的 Neq 数的个数，状态转移方程大概是这样：

- 如果 $|j-k|\geq 1$，$dp_{i,j}= \sum dp_{i-1,k}$。

然后二分 $x$，找到刚好数量为 $k$ 且最小的数。

对于二分上限差不多 $10^{14}$ 就可以了，因为 Neq 数比较密集。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int p,q,dp[19][19],a[19];
void init()
{
	for(int i=0;i<=9;i++) dp[1][i]=1;
	for(int i=2;i<=14;i++)
	for(int j=0;j<=9;j++)
	for(int k=0;k<=9;k++)
	if(abs(j-k)>=1)	dp[i][j]+=dp[i-1][k];
}
int work(int x)
{
	memset(a,0,sizeof(a));
	int len=0,ans=0;
	while(x)
	{
		a[++len]=x%10;
		x/=10;
	}
	for(int i=1;i<=len-1;i++)
	for(int j=1;j<=9;j++)
	ans+=dp[i][j];
	for(int i=1;i<a[len];i++)
	ans+=dp[len][i];
	for(int i=len-1;i>=1;i--)
    {
        for(int j=0;j<=a[i]-1;j++)
		if(abs(j-a[i+1])>=1) ans+=dp[i][j];
		if(abs(a[i+1]-a[i])<1) break;
    }
	return ans;
}
signed main()
{
	init();
	int n;
	cin>>n;
	while(n--)
	{
		int k;
		cin>>k;
		int l=1,r=1e14;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(work(mid)<k) l=mid+1;
			else r=mid;
		}
		cout<<l-1<<"\n";
	}
}
```

---

## 作者：CBC18 (赞：2)

## 思路
因为题目中“Neq 数”的数量满足单调性：范围越大，“Neq 数”越多。
所以用二分答案。判断标准为 $1$ 到 $x$ 之间的“Neq 数”是否大于 $mid$，如果大于，则右边界 $r=mid$；反之左边界 $l=mid$。\
剩下的部分与[windy 数](https://www.luogu.com.cn/problem/P2657)大致相同。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, dp[20][20]; 
void init(){
	for(int j = 0; j <= 9; j++) dp[1][j] = 1;
	for(int i = 2; i <= 13; i++){
		for(int j = 0; j <= 9; j++){
			for(int k = 0; k <= 9; k++){
				if(abs(j - k) >= 1){
					dp[i][j] += dp[i - 1][k];
				}
			}
		}
	}
}
int get(int x){
	if(x == 0) return 0;
	int num[20] = {}, cnt = 0, ans = 0;
	while(x){
		num[++cnt] = x % 10;
		x /= 10;
	}
	for(int i = cnt; i >= 0; i--){
		for(int j = 0; j <= num[i] - 1; j++){
			if(i == cnt and j == 0)
				continue;
			if(i != cnt and abs(j - num[i + 1]) < 1) continue;
			ans += dp[i][j];
		}
		if(i != cnt and abs(num[i] - num[i + 1]) < 1) break;
		if(i == 1){
			ans++;
		}
	}
	for(int i = cnt - 1; i >= 1; i--){
		for(int j = 1; j <= 9; j++){
			ans += dp[i][j];
		}
	}
	return ans;
}
bool check(int x){
	return get(x) >= n;
}
signed main(){
	cin >> t;
	init();
	while(t--){
		cin >> n;
		int lt = 0, rt = 1e13;
		while(lt + 1 != rt){
			int mid = lt + rt >> 1;
			if(check(mid)) rt = mid;
			else lt = mid;
		}
		cout << rt << endl;
	}
	return 0;
}
```

---

## 作者：_QWQ__QWQ_ (赞：1)

简单二分。

## 思路
数位 dp 预处理和判断。

init 预处理出 dp 数组，与 [windy 数](https://www.luogu.com.cn/problem/P2657)大致相同。

二分答案，如果 $1$ 至 $mid$ 的 Neq 数数量大于等于 $ k $，$rt=mid$；否则 $ lt=mid $，最后输出 $ rt $。

 query 直接当 check 用。

AC code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
int dp[100][100]; 
int l,r;
void init(){
	for(int i=0;i<=9;i++){
		dp[1][i]=1;
	}
	for(int i=2;i<=19;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<=9;k++){
				if(j!=k){
					dp[i][j]+=dp[i-1][k];
				}
			}
		}
	}
}
int query(int x){
	if(x==0){
		return 0;
	}
	int num[25],cnt=0,ans=0;
	while(x!=0){
		cnt++;
		num[cnt]=x%10;
		x/=10;
	}
	
	for(int i=cnt;i>=1;i--){
		for(int j=0;j<num[i];j++){
			if(i==cnt&&j==0)continue;
			if(i!=cnt&&num[i+1]==j)continue;
			ans+=dp[i][j];
			
		}
		if(i!=cnt&&num[i]==num[i+1])break;
		if(i==1)ans++;
	}
	for(int i=cnt-1;i>=1;i--){
		for(int j=1;j<=9;j++){
			ans+=dp[i][j];
		}
	}
	return ans;
}
signed main(){
	init();
	int t,k;
	cin>>t;
	while(t--){
		cin>>k;
		int lt=-1,rt=1e15+1;
		while(lt+1!=rt){
			int mid=(lt+rt)/2;
			if(query(mid)>=k){
				rt=mid;
			}
			else{
				lt=mid;
			}
		}
		cout<<rt<<endl; 
	}
	
	return 0;
}
```

---

## 作者：wflhx2011 (赞：1)

数位 dp 看不懂，于是来数数了。

首先，一位数的有 $9$ 个，每一个都是。两位数有 $81$ 个，即  $90-9=81$（两位数一共 $90$ 个，减去 $11$，$22$ 到 $99$ 共 $9$ 个数），以此类推。

不难发现，这些数都是 $9$ 的次幂。因为第一位不能是 $0$，以后每一位都不能是前面的数字，所以每位都有 $9$ 种选择，设这个数的位数为 $x$，把所有的都乘起来，于是就是 $9^x$。

那么，我们把输入的数转成 $9$ 进制数就可以。

代码太丑就不放了，觉得第一篇题解的代码写得很简洁，可以参考大佬的。

---

## 作者：Sorato_ (赞：1)

# ARC173A Neq Number

## 题目大意

正整数 $X$ 如果满足以下条件，则称为 **"Neq 数"**：

- 当 $X$ 用十进制符号书写时，没有两个相邻的字符是相同的。

例如，$1$、$173$ 和 $9090$ 是 Neq 数，而 $22$ 和 $6335$ 不是。

给你一个正整数 $K(1\leq K\leq10^{12})$。请找出第 $K$ 小的 Neq 数。

---

## Solve

大体思路就是 对于每次询问的 $K$，判断出 $K$ 的位数 $n$，然后按位枚举，使我们枚举出的这个数的位次不断逼近 $K$。具体见下。

首先想办法处理处 $[1,10^n-1]$（即 $n$ 位数）之间的 Neq 数的数量，记为 $sum_n$，那么**若 $sum_{n-1}<K\leq sum_n$，则第 $K$ 个 Neq 数是一个 $n$ 位数**。

然后考虑处理出 $[a\times10^i,(a+1)\times10^i-1]$ 之间 Neq 数的数量，记为 $sum1_i$。接着按位枚举。**若 $(a-1)\times sum1_{i-1}<K\leq a\times sum1_{i-1}$，则 $K$ 的第 $i$ 位是 $a$**。

接下来考虑 $sum$ 和 $sum1$ 怎么求。

先看 $sum1$，拿 $sum1_3[1000,1999]$ 举例。$[1000,1999]$ 可拆分为 $[1000,1099],[1100,1199],\cdots,[1899,1999]$ 这 $10$ 个区间，其中 $[1100,1199]$ 中由于前两位都是 $1$，所以无 Neq 数，不计。所以 $sum1_3=sum1_2\times9$。

**以此类推，我们有 $\large sum1_i=sum1_{i-1}\times9,sum1_0=1$。**

至于 $sum$，以 $sum_4[1,9999]$ 举例。$[1,9999]$ 可拆分为 $[1,999],[1000,1999],[2000,2999],\cdots,[8999,9999]$。所以 $sum_4=sum_3+sum1_3\times9$。

**以此类推，$\large sum_i=sum_{i-1}+sum1_{i-1}\times9=sum_{i-1}+sum1_i,sum_0=0$。**

注意，单独看 $[0\times10^i,1\times10^i-1]$之间的 Neq 数，应该是 $sum_i$，但我们在计算时应记为 $sum1_i$，$i=n$ 时除外。以 $n=5,i=4$ 即 $[10000,10999]$ 为例。显然 $sum_2[10000,10099]$ 之间的 Neq 数都由于相邻的两个 $0$ 而不计数了，即 $[10000,10999]$ 之间的 Neq 数应为 $sum_3-sum_2$。

**以此类推，$[0\times10^i,1\times10^i-1](i\neq n)$ 之间的 Neq 数为 $\large sum_{i-1}-sum_{i-2}=sum_{i-2}+sum1_i-sum_{i-2}=sum1_i$。**

## Code

```c++
#include<bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","inline")
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int T,k,sum[20]/*1~10^n-1*/,n,sum1[20]={1}/*a*10^n~(a+1)*10^n-1*/;
signed main()
{
	for(int i=1;i<=13;i=-~i)//预处理
		sum1[i]=sum1[i-1]*9,
		sum[i]=sum1[i]+sum[i-1];
	T=read();
	for(int t=1;t<=T;t=-~t)
	{
		k=read();
		for(n=1;n<=13;n=-~n)	if(sum[n]>=k)	break;//枚举位数
		int res=0,x=-1,now;
		for(int i=n;i;i--)
			for(int j=0;j<=9;j=-~j)
			{
				now=res;
				if(j!=x)	res+=i==n&&j==0?sum[i-1]:sum1[i-1];
				//只有当枚举第n位为0时才加sum，其余都加sum1，证明见上
				if(res>=k)
				{
					printf("%lld",x=j);
					res=now;//回溯
					break;
				}
			}
		puts("");
	}
	return 0;
}
```

---

## 作者：XYQ_102 (赞：0)

## 题目
一个数合法当且仅当在十进制下没有相邻两个字符是相同的。

问第 $K$ 小的合法的正整数。
## 思路
考虑十进制下长度为 $i$ 的合法数字有 $9^i$ 个，那么我们容易确定答案数字的位数，接下来一位一位填就可以。

时间复杂度 $\Theta(T\times\log_{10}K)$
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace fastIO{
	inline int read(){
		int x=0,f=1;char ch=getchar();
		while(ch<'0'||ch>'9'){if(ch=='-') f=-f;ch=getchar();}
		while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
		return x*f;
	}
	int buf[20],TOT;
	inline void print(int x,char ch=' '){
		if(x<0) putchar('-'),x=-x;
		else if(x==0) buf[++TOT]=0;
		for(int i=x;i;i/=10) buf[++TOT]=i%10;
		do{putchar(buf[TOT]+'0');}while(--TOT);
		putchar(ch);
	}
}
using namespace fastIO;
int T,n; 
signed main(){
	T=read();
	while(T--){
		n=read(); 
		int len=1;
		while(pow(9,len)<n) n-=pow(9,len++);
		int pre=0;
		for(int i=1;i<=len;i++){
			for(int j=0;j<=9;j++){
				if(j==pre) continue;
				if(pow(9,len-i)>=n){
					putchar('0'+j);
					pre=j;
					break;
				}
				else n-=pow(9,len-i);
			}
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：qwq___qaq (赞：0)

二分答案。

我们需要求出 $\le mid$ 的符合条件的数有多少个。

考虑数位 dp。

$dp_{now,lst,0/1}$ 表示的是 $now$ 位，上一位是 $lst$，现在是否处于前导零状态。

然后就做完了。

---

## 作者：OIer_Tan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc173_a)

## 思路

看起来可以用数位 DP 的思想做，但是思考后可以得出更简单的办法。

显然，每位都只有 $9$ 种选择方式（第一位不能取 $0$，后面的不能和上一位相同），所以考虑按 10 进制转 9 进制的思路做。

## 代码

```cpp
#include<bits/stdc++.h>
#define endl '\n' 

using namespace std ;

typedef long long ll ;
typedef unsigned long long ull ;
typedef long double ld ;

ll T ;

void solve ()
{
	ll k ;
	cin >> k ;
	ll len = 0 , last = 0 , temp = 1 ;
	while ( k >= temp )
	{
		k -= temp ;
		len ++ ;
		temp *= 9 ;
	}
	temp /= 9 ;
	while ( len )
	{
		ll now = k / temp ;
		if ( now >= last )
		{
			now ++ ;
		}
		cout << now ;
		last = now ;
		k -= k / temp * temp ;
		temp /= 9 , len -- ;
	}
	cout << endl ;
	return ;
}

int main ()
{
	// freopen ( ".in" , "r" , stdin ) ;
	// freopen ( ".out" , "w" , stdout ) ;
	ios::sync_with_stdio ( 0 ) ;
	cin.tie ( 0 ) ;
	cout.tie ( 0 ) ;
	cin >> T ;
	while ( T -- )
	{
		solve () ;
	}
	return 0 ;
}
```

---

