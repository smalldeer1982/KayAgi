# [USACO09HOL] Transmission Delay G

## 题目描述

Farmer John has taken to yodeling from the top of the barn in order to communicate with the cows out in the pastures. Being bovine and all, cows can hear binary messages (0's and 1's) but have trouble with perfect communications because FJ's yodeling echoes off the silo. In fact, in a sequence of N (1 <= N <= 2,000) bits, Bessie will always receive a sequence of N bits, with the same number of 0s and 1s, but each 0 or 1 might be delayed.

Precisely speaking, for a given number D (0 <= D < N), the i-th bit might be heard as the j-th one as long as |i - j| <= D (in other words, no bit appears in a position farther than distance D from its original position). 
Consider the following message as an example: 0110. Four possible messages might be heard if D = 1: 0101, 0110, 1001, and 1010.

Given the message to be yodeled by FJ, along with two numbers D and K (1 <= K <= 100,000,000), determine the number of different messages that might be heard by Bessie, modulo 100,000,000. Also determine the K-th smallest such message in lexicographical order (in binary representation, with 0 coming before 1). It is guaranteed that K will be no larger than the number of different possible messages.

MEMORY LIMIT: 32 MB

TIME LIMIT: 2 seconds

FEEDBACK: Your first 50 submissions for this problem will be run on some of the official test data, and you will receive a summary of the results.

约翰在屋顶上唱歌，以此来与奶牛们交流。但是奶牛们的听力很奇怪，她们只能听到约翰的歌声变成 $0$ 和 $1$ 构成的信息串时的样子。约翰的声音里有 $N  (1 \leq N \leq 2000)$ 个 $0$ 或 $1$，奶牛听到的也是 $N$ 个，而且 $0$ 和 $1$ 的数量不会变化，但是一部分 $0$ 或 $1$ 可能偏离原来的位置，这就是约翰的歌声在传输时发生的“传输延迟”现象。$0$ 或 $1$ 的偏离距离不会超过 $D(O \leq D < N)$，也就是说某一个码的原本位置和现在的位置之差的绝对值不大于 $D$。

比如，对于 `0110`，$D = 1$，传输延迟发生后可能出现 `0101`，`0110`，`1001`，`1010` 这四种串．

给出约翰歌声的 $01$ 串形式和一个整数 $K(1 \leq K \leq10^8)$，请计算传输延迟发生后一共有多少种可能的 $01$ 串，以及其中第 $K$ 大的串是什么。

## 样例 #1

### 输入

```
4 1 3 
0110 
```

### 输出

```
4 
1001 
```

# 题解

## 作者：fy0123 (赞：8)

这题是个dp。

定义方程f[i][j]表示从n~i，用了j个0的方案数。要n~i倒着处理是为之后的第k大做帮助。

第一问就直接dp，我们记录下p0[i],p1[i]分别表示从左往右第i个0的位置，第i个1的位置。转移的时候根据当前位放0还是放1，且是否满足距离小于等于d，计算即可。

然后对于第二问，我们这么做：

- 如果当前位置放0的方案数>=k，当前位就放0。

- 如果不能放0，就放1，并且k减去放0的方案数。

以上所有说的可以放0或放1都是建立在题目要求的前提下的，即距离不超过d

然后我们有一个问题了：如果方案数超过k的超过太多了怎么办？按照题意来说我们应该是要%10^8的，但是由于要求后面的第k大需要用到这个方案数，如果我们直接%10^8，就会导致结果不正确了。

对于这个问题我们再开一个g[i][j]也记录方案数，如果g[i][j]>10^8了就把它设成10^8+1，然后之后算第k大的时候就用g[i][j]当做方案数，这样就没事了。

下面放代码：

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 2010;
const int MOD = 1e8;
int n, d, k, cnt0 = 0, cnt1 = 0;
int p0[N], p1[N], f[N][N], g[N][N];
char s[N];

int main()
{
    scanf("%d%d%d", &n, &d, &k);
    scanf("%s", s+1);
    for (int i = 1; i <= n; i ++)
        if (s[i] == '0') p0[++ cnt0] = i;
        else p1[++ cnt1] = i;
    f[n+1][0] = g[n+1][0] = 1;
    for (int i = n; i >= 1; i --)
        for (int j = 0; j <= min(n-i+1, cnt0); j ++){
            int k = n-i+1-j;
            if (j && abs(p0[cnt0-j+1]-i) <= d){
                f[i][j] += f[i+1][j-1];
                if (f[i][j] > MOD) f[i][j] -= MOD;
                g[i][j] = min(g[i][j]+g[i+1][j-1], MOD+1);
            }
            if (k && abs(p1[cnt1-k+1]-i) <= d){
                f[i][j] += f[i+1][j];
                if (f[i][j] > MOD) f[i][j] -= MOD;
                g[i][j] = min(g[i][j]+g[i+1][j], MOD+1);
            }
        }
    printf("%d\n", f[1][cnt0]);
    int s0 = cnt0, s1 = cnt1;
    for (int i = 2; i <= n; i ++){
        if (s0 && abs(p0[cnt0-s0+1]-i+1) <= d){
            if (g[i][s0-1] >= k) s0 --, putchar('0');
            else s1 --, k -= g[i][s0-1], putchar('1');
        } else s1 --, putchar('1');
    }
    if (s0) putchar('0'); else putchar('1');
    return 0;
}
```

---

## 作者：黑影洞人 (赞：2)

记忆化搜索

反着一位一位枚举，因为题目要求我们求出字典序第k大的，所以到时候拿出来的时候一定是从前往后贪心的取，所以我们要倒着存搜索值。

注意到题目要求取模，模数是 $10^8$。

因此我们对于一个搜索状态，设为 `dfs(o,h,q)`。

其中，$o$ 代表搜索到第 $o$ 位，也就是要求出 $[o,n]$，用了 $h$ 个 $0$，$q$ 个 $1$ 的方案数。

其中，$q$ 的值可以用 $o,h$ 算出来，因此记忆化只用带着 $h$，可以把 $q$ 去掉。

$t0_i$ 表示第 $i$ 个 $0$ 的位置。

$t1_i$ 表示第 $i$ 个 $1$ 的位置。

$cnt0$ 表示 $0$ 的个数。

$cnt1$ 表示 $1$ 的个数。
```cpp，
pair<int,int> dfs(int o,int h,int q){//枚举从o~n，用了h个0，q个1。
	if(h<0)return {0,0};//越界返回0
	if(q<0)return {0,0};
	if(o>=n+1){
		if(h==0||q==0)return {1,1};//最小状态，也就是啥也没有的方案是1
		else return {0,0};
	}
	if(dp[o][h]!=-1)return {dp[o][h],f[o][h]};//记忆化，如果已经被搜过了，那么标记为访问过。
	int r1=0,r2=0,l=n-o+1;
	if(h&&abs(t0[cnt0-h+1]-o)<=d){//如果这一位可以放0，那么往下搜索
		pair<int,int> ohq=dfs(o+1,h-1,q);//0的个数用了一个于是减去一
		r1=(r1+ohq.first)%p;
		r2=min(r2+ohq.second,p);
	}
	if(q&&abs(t1[cnt1-q+1]-o)<=d){//和上面一个道理
		pair<int,int> ohq=dfs(o+1,h,q-1);
		r1=(r1+ohq.first)%p;
		r2=min(r2+ohq.second,p);
	}
	dp[o][h]=r1;f[o][h]=r2;//最后统计答案
	return {r1,r2};
}
```

为什么要维护两个值呢，因为在后面统计答案的时候，如果使用了取过模的方案。

那么会造成最后答案输出的错误，但是不取模会造成答案太大。

观察一下数据范围，$k$ 的最大值正好是 $10^8$ 那么我们不妨再开一个数组，当 dp 值大于 $10^8$ 的时候，直接设为 $10^8$ 在后来的计算中会直接把 $k$ 变得小于等于 $0$ 这样就可以直接贪心的去取最大的，也就是把剩下的位全部设为 $1$。

```cpp
//这是构造答案的代码。
int j=cnt0;
//逻辑和dfs里的逻辑一样，同样是先判断当前状态，再判断后面的状态。
for(int i=1;i<=n-1;i++){
	if(j&&abs(t0[cnt0-j+1]-i)<=d){//如果可以取0
		if(f[i+1][j-1]>=k)putchar('0'),j--;//而且如果后面的状态不取0的话就不保证第k大，那么取0，也就是必须去0的时候就去0
		else k-=f[i+1][j-1],putchar('1');//否则尽可能取1
	}else putchar('1');//不能取0就取1
}
//这是dfs里去掉0时的代码。
if(h&&abs(t0[cnt0-h+1]-o)<=d){//如果这一位可以放0，那么往下搜索
	pair<int,int> ohq=dfs(o+1,h-1,q);//0的个数用了一个于是减去一
	r1=(r1+ohq.first)%p;
	r2=min(r2+ohq.second,p);
}

```

但是上面的代码只是更新到了 $n-1$，也是我们要判断一下最后一位。

我们在构造第 $k$ 大时，记录一下剩下的 $0$ 的个数 $j$，这样剩下一位可以通过 $j$ 判断。

如果还有 $0$ 没放就放 $0$，反之放 $1$。

```cpp
if(j)putchar('0');
else putchar('1');
```
完结撒花

---

