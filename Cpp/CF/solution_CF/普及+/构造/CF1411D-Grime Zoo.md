# Grime Zoo

## 题目描述

Currently, XXOC's rap is a string consisting of zeroes, ones, and question marks. Unfortunately, haters gonna hate. They will write $ x $ angry comments for every occurrence of subsequence 01 and $ y $ angry comments for every occurrence of subsequence 10. You should replace all the question marks with 0 or 1 in such a way that the number of angry comments would be as small as possible.

String $ b $ is a subsequence of string $ a $ , if it can be obtained by removing some characters from $ a $ . Two occurrences of a subsequence are considered distinct if sets of positions of remaining characters are distinct.

## 说明/提示

In the first example one of the optimum ways to replace is 001. Then there will be $ 2 $ subsequences 01 and $ 0 $ subsequences 10. Total number of angry comments will be equal to $ 2 \cdot 2 + 0 \cdot 3 = 4 $ .

In the second example one of the optimum ways to replace is 11111. Then there will be $ 0 $ subsequences 01 and $ 0 $ subsequences 10. Total number of angry comments will be equal to $ 0 \cdot 13 + 0 \cdot 37 = 0 $ .

In the third example one of the optimum ways to replace is 1100. Then there will be $ 0 $ subsequences 01 and $ 4 $ subsequences 10. Total number of angry comments will be equal to $ 0 \cdot 239 + 4 \cdot 7 = 28 $ .

In the fourth example one of the optimum ways to replace is 01101001. Then there will be $ 8 $ subsequences 01 and $ 8 $ subsequences 10. Total number of angry comments will be equal to $ 8 \cdot 5 + 8 \cdot 7 = 96 $ .

## 样例 #1

### 输入

```
0?1
2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
?????
13 37```

### 输出

```
0```

## 样例 #3

### 输入

```
?10?
239 7```

### 输出

```
28```

## 样例 #4

### 输入

```
01101001
5 7```

### 输出

```
96```

# 题解

## 作者：moqizhu2005 (赞：3)


### CF 1411D Grime Zoo

我们可以考虑字符串中的任意两个问号 `? ··· ?` 。

设两个问号之间有$c0$个$0$，$c1$个$1$，考虑两个问号的填法。

如果填 `0 ··· 1` ，那么此区间的总价值为：

$$c0*x+c1*x+x$$

如果填 `1 ··· 0` ，那么此区间的总价值为：

$$c0*y+c1*y+y$$

比较两个式子的大小，即两式相减：

$$(c0*x+c1*x+x)-(c0*y+c1*y+y)$$

可以得到一个式子：

$$(c0+c1+1)(x-y)$$

我们可以发现：

若 `x>y` ，那么我们可以把所有的 `0 1` 换成 `1 0` 。

若 `x<y` ，那么我们可以把所有的 `1 0` 换成 `0 1` 。

接下来把所有的问号随机填上 `0,1` 。

那么通过以上的结论将所有可替换的问号组替换成更优解。

如果是把所有的 `0 1` 换成 `1 0`，易证所有的 `1` 会移到最左边。

所以可知答案一定是全填 `0`，全填 `1`，或者存在一个位置，左边问号全填`1`，右边全填`0` ，反之同理。

可以通过先把所有的问号改为`0`或`1`，再反向进行替换并更新最小值即可。

代码如下

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const ll inf=(1ll<<60);
char s[100005];
ll x,y;
ll c0,c1,d0,d1,ans,len;
//c0和c1表示正向搜索0和1的数量
//d0和d1表示反向搜索0和1的数量 
void big()//若x>y 
{
	ll mans=inf;
	for(int i=0;i<len;i++)
		if(s[i]=='0') c0++,ans+=y*c1;
		else c1++,ans+=x*c0;
	mans=ans;
	for(int i=len-1;i>=0;i--)
		if(s[i]=='0') d0++,c0--;
		else if(s[i]=='1') d1++,c1--;
		else if(s[i]=='?')
		{
			c1--;
			ans=ans-c0*x-d0*y+c1*y+d1*x;
			mans=min(mans,ans);
			d0++;
			//注意要先更新ans再更新d0的值
			//small操作同理 
		}
	printf("%lld\n",mans);
}
void small()//若x<y
{
	ll mans=inf;
	for(int i=0;i<len;i++)
		if(s[i]=='1') c1++,ans+=x*c0;
		else c0++,ans+=y*c1;
	mans=ans;
	for(int i=len-1;i>=0;i--)
		if(s[i]=='0') d0++,c0--;
		else if(s[i]=='1') d1++,c1--;
		else if(s[i]=='?')
		{
			c0--;
			ans=ans-c1*y-d1*x+c0*x+d0*y;
			mans=min(mans,ans);
			d1++;
		}
	printf("%lld\n",mans);
}
int main()
{
	scanf("%s%lld%lld",s,&x,&y);
	len=strlen(s);
	if(x>y) big();
	else small();
	return 0;
}
```


---

## 作者：AkeuchiTsuzuri (赞：2)

# Description

翻译很友好。

# Solution
贪心。

结论：最优解的填数方案是存在于字符串中某一个 `?` 前边的 `?` 全部填 `0` 或者 `1`，后边的填 `1` 或者 `0`。

然后考虑对每对 `0` 和 `1` 的贡献计算，对原数组从头到尾扫一遍，扫到 `0` 对价值贡献即为 $\text{cnt}_1\times y$，反之扫到 `1` 则为 $\text{cnt}_0\times x$。其中 $\text{cnt}_{0/1}$ 表示当前位之前有多少个 `0` 或 `1`。

这样就得到了当 `?` 全为 `0` 或者全为 `1` 时的字符串价值。

接下来倒序枚举每个 `?` 修改，设当前倒序扫到的 `0` 或 `1` 数量为 $\text{tnc}_{0/1}$，字符串总价值为 $\text{v}$，则对于每个 `?` 修改时贡献应当做出如下修改：

$$\text{v}\leftarrow\begin{cases}
	\text{v}-(\text{cnt}_1\times y+\text{tnc}_1\times x-\text{cnt}_0 \times x-\text{tnc}_0\times y),\text{初始时全填0}\\
   \text{v}-(\text{cnt}_0\times x+\text{tnc}_0\times y-\text{cnt}_1 \times y-\text{tnc}_1\times x),\text{初始时全填1}\\
	\end{cases}$$

其中 “$\leftarrow$” 表示赋值给。

同时更新 $\text{cnt}_{0/1}$、$\text{tnc}_{0/1}$ 与最价值，时间复杂度 $\text{O}(n)$。

---

## 作者：ConstantModerato (赞：0)

这道题非常的妙，建议在看本篇题解之前先自行思考个几个小时。

看到这题的时候，我们能想到一个很简单的 dp 做法。

不妨设 $dp_{i,j}$ 为在第 $i$ 位，此时有 $j$ 个 $0$ 的最小价值。不难想到转移。

$$dp_{i,j} = \min\{dp_{i - 1,j} + j \times a,dp_{i - 1,j - 1} + (i -j) \times b\}$$

具体来说是这样的：

```
const int N = 1010;
int n,x,y,a,b;
char s[N];
int dp[N][N];
signed main(){
    cin >> s + 1;n = strlen(s + 1);
    a = read(),b = read();int cnt = 0,cnt0 = 0;
    memset(dp,0x3f,sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1;i <= n;i++){
        if (s[i] == '0' || s[i] == '?') cnt++;
        if (s[i] == '0') cnt0++;
        for (int j = cnt0;j <= cnt;j++){
            if (s[i] == '0' || s[i] == '?')
                if (j >= 1) dp[i][j] = min(dp[i][j],dp[i - 1][j - 1] + (i - j) * b);
            if (s[i] == '1' || s[i] == '?')
                dp[i][j] = min(dp[i][j],dp[i - 1][j] + j * a); 
        }
    } int res = INF;
    for (int i = cnt0;i <= cnt;i++)
        res = min(res,dp[n][i]);
    cout << res << endl;
    return 0;
}
```


然后考虑优化。

不难看到，优化个头啊这能怎么优化，果断放弃。

观察到状态数那么大，还不让 dp，那极有可能是贪心题，或者是神秘题，所以我们往这方面考虑。

假设我们在第 $i$ 个问号那边填了 $0$，我们来考虑第 $i + 1$ 个问号填 $1$ 和填 $0$ 的贡献。不妨设 $\delta$ 为填 $0$ 比填 $1$ 能节省多少价值（可能是负数）。

设 $i$ 前面（不包括 $i$) 有 $sum_0$ 个 $0$，$sum_1$ 个 $1$。第 $i$ 个问号到第 $i + 1$ 个问号之间有 $cnt_0$ 个 $0$，$cnt_1$ 个 $1$，第 $i + 1$ 个问号之后（不包括 $i + 1$）有 $num_0$ 个 $0$，$num_1$ 个 $1$。

用手推一推就不难得出：

$$\delta = -a + (sum_1 + cnt_1 - num_0)\times b - (sum_0 + cnt_0 - num_1)\times a$$

同理，我们来考虑在第 $i$ 个问号那边填了 $1$，我们来考虑第 $i + 1$ 个问号填 $0$ 和填 $1$ 的贡献。不妨设 $\delta'$ 为填 $1$ 比填 $0$ 能节省多少价值（可能是负数，注意这里和上面的假设略有不同）。

$$\delta' = -b - (sum_1 + cnt_1 - num_0)\times b + (sum_0 + cnt_0 - num_1)\times a$$

不妨设：

$$b \ge a$$

$$X = -(sum_1 + cnt_1 - num_0)\times b + (sum_0 + cnt_0 - num_1)\times a$$

所以，当第 $i$ 位为 $0$ 时，第 $i + 1$ 填 $1$ 时当切仅当 $\delta \ge0$ 也就是 $-a \ge X$。

当第 $i$ 位为 $1$ 时，第 $i + 1$ 位填 $1$ 时当切仅当 $\delta'\le0$ 也就是 $b \ge X$。

不难发现：

$$X = (num_0 \times b + sum_0 \times a + cnt_0 \times a) - (num_1 \times a + sum_1 \times b + cnt_1 \times b)$$

随着 $i$ 的增大，$(num_0 \times b + sum_0 \times a + cnt_0 \times a)$ 在不断减小，$(num_1 \times a + sum_1 \times b + cnt_1 \times b)$ 在不断增大，所以 $X$ 是不断在减小的。

原因的话可以考虑每一个 $0$ 所在的位置，每一个所在 $1$ 的位置所乘上的权重即可。

从上面可以观察到，如果有一个 $i$ 位置，存在 $-a \ge X$，那么下一个位置，下下个位置，直到末尾一定有 $b \ge X$，因为 $b > -a$。

同时，我们反过来考虑，假设 $a > b$ 的话，正好能得到相反的结论。

总结上面，存在一个问号位置 $i$，前面全部填 $0$，后面全部填 1。
或者是前面全部填 $1$，后面全部填 $0$。

知道了上面的结论，然后我们就能愉快的写代码了。

```
const int N = 1e5 + 5;
int a,b,n,cnt;
string s;
int ans = 2e18;
int solve(){
    int cnt0 = 0,cnt1 = 0,num0 = 0,num1 = 0;
    int sum = 0,res = 2e18;
    for (int i = 0;i < n;i++){
        if (s[i] == '0' || s[i] == '?'){
            cnt0++; sum += cnt1 * b;
        } else {
            cnt1++; sum += cnt0 * a;
        }
    } res = sum; //debug(sum);
    for (int i = n - 1;i >= 0;i--){
        if (s[i] == '0') num0++,cnt0--;
        if (s[i] == '1') num1++,cnt1--;
        if (s[i] == '?'){
            cnt0--;
            sum = sum - cnt1 * b - num1 * a + num0 * b + cnt0 * a;
            num1++;
            res = min(res,sum);
        }
    } return res;
}
signed main(){
    cin >> s;n = s.size();
    a = read(),b = read();
    if (a >= b) swap(a,b),reverse(s.begin(),s.end());
    ans = min(ans,solve());
    cout << ans << endl;
    return 0;
}
```

p.s. 如果你知道怎么优化 dp，请联系 ```ConstantModerato```。

---

## 作者：Muse_Dash (赞：0)

绿题只会暴力 $n^2$，我还是太菜了。

假定第 $i,i+1$ 个 `?` 下标分别为 $x,y$，那么记 $(x,y)$ 区间内的 $0,1$ 个数分别为 $a,b$。

把两个 `?` 任意填上 $0,1$。如果填上的值相同，无需考虑交换；如果填上的值不同，可以考虑交换 $x,y$。注意到交换并不会影响这两个 `?` 与 $[x,y]$ 外的值的贡献，故只需考虑 $[x,y]$ 内部贡献的改变。

具体地，如果前面那个 `?` 的值设为 $0$，后面的是 $1$，那么区间内的贡献为 $ax+bx+x$，而前后分别为 $1,0$，则区间内贡献为 $ay+by+y$，相减即为贡献差，即 $(a+b+1)(x-y)$，此时判断 $x-y$ 的正负性即可判断是否交换 `?` 的值。

事实上随机赋给每个 `?` 权值之后，因为 $x-y$ 的正负性是固定的，在考虑每对 `?` 是否交换之后，提取每个 `?` 的值组成新的子序列，会发现其会形如 `00...011...1` 或者 `11...100...0` 的形式，枚举这个断点 `?` 的位置即可。

---

## 作者：AxDea (赞：0)

设 `?` 将 `01` 串分成了 $k$ 段，设 $b_i$ 表示第 $i$ 段内部自身所产生的贡献， $f_i,g_i$ 分别表示第 $i$ 段数字为 `0` 和 `1` 的个数。

下面设在一段左边的，离这一段最近的 `?` 属于这一段中。

那么答案为：
$$
\sum_{i = 1} ^ k b_i + y\cdot f_i \sum_{j = 1} ^ {i - 1} g_j + x\cdot g_i\sum_{j=1} ^ {i - 1} f_{j}
$$
要使得答案最小，就要让 $y\cdot f_i \sum_{j = 1} ^ {i - 1} g_j + x\cdot g_i\sum_{j=1} ^ {i - 1} f_{j}$ 最小。

考虑每一个 `?` 的贡献，若填一个 `0` 进去，就是 $y\cdot \sum_{j = 1} ^ {i - 1} g_j + x\cdot \sum_{j = i + 1} ^ k g_j$ ，若填个 `1` 进去，就是 $y\cdot \sum_{j = i + 1} ^ k f_j + x\cdot \sum_{j = 1} ^ {i - 1} f_j$ 。

但是操作之间会互相影响，考虑枚举 `1` 或 `0` 的个数，这样每个操作对于上述的原局面贡献是一样的，且规模是 $\mathcal{O}(n)$ 的。

考虑让相互影响的贡献达到最小值，发现填一个 `0` 进去，对后面填的 `1` 都有 $x$ 的贡献，反之，对右面的 `0` 都有 $y$ 的贡献。

贡献就是 $\sum_{i = 1} ^ k x\cdot[a_i = 1] \sum_{j = 1} ^ {i - 1} f_j + y\cdot[a_i = 0]\sum_{j  = 1} ^ {i - 1} g_j$ ，发现把式子中的 $x,y$ 去掉后，该式子的值是不变的，因为若将原序列中位置相邻的 `0` 和 `1` 互相换位后，只不过是一种贡献加一，另一种少一，这样就可以推广到任意两个不同数字交换的情况了。

后面就考虑贪心，比较 $x$ 和 $y$ 的大小，使得较小的一种出现，另一种不出现，很明显，只要让 `1` 全部靠左或 `0` 全部靠左放就行了，答案贡献还是比较好推的。

时间复杂度 $\mathcal{O}(n)$ 。

```cpp
#include <bits/stdc++.h>
#define forn(i,s,t) for(register int i=(s); i<=(t); ++i)
#define form(i,s,t) for(register int i=(s); i>=(t); --i)
using namespace std;
typedef long long LL;
const int N = 1e5 + 3;
int n; char s[N]; LL x, y;
int main() {
	scanf("%s", s + 1), n = strlen(s + 1);
	scanf("%lld%lld", &x, &y);
	if(x < y) {
		swap(x, y);
		forn(i,1,n) s[i] ^= isdigit(s[i]);
	}
	static LL f[N], g[N], Pre[N], Suf[N];
	forn(i,1,n) {
		if(s[i] == '0') f[i] = f[i - 1] + y * Pre[i - 1];
		else f[i] = f[i - 1] + x * (i - 1 - Pre[i - 1]);
		Pre[i] = Pre[i - 1] + (s[i] != '0');
	}
	form(i,n,1) {
		if(s[i] == '1') g[i] = g[i + 1] + y * Suf[i + 1];
		else g[i] = g[i + 1] + x * (n - i - Suf[i + 1]);
		Suf[i] = Suf[i + 1] + (s[i] != '1');
	}
	LL res = 1e18;
	forn(i,0,n) res = min(res, f[i] + g[i + 1] + x * (i - Pre[i]) * (n - i - Suf[i + 1]) + y * Pre[i] * Suf[i + 1]);
	printf("%lld\n", res);
	return 0;
} 
```



---

