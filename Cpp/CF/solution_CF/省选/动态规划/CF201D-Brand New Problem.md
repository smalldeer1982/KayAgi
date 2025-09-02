# Brand New Problem

## 题目描述

A widely known among some people Belarusian sport programmer Lesha decided to make some money to buy a one square meter larger flat. To do this, he wants to make and carry out a Super Rated Match (SRM) on the site Torcoder.com. But there's a problem — a severe torcoder coordinator Ivan does not accept any Lesha's problem, calling each of them an offensive word "duped" (that is, duplicated). And one day they nearely quarrelled over yet another problem Ivan wouldn't accept.

You are invited to act as a fair judge and determine whether the problem is indeed brand new, or Ivan is right and the problem bears some resemblance to those used in the previous SRMs.

You are given the descriptions of Lesha's problem and each of Torcoder.com archive problems. The description of each problem is a sequence of words. Besides, it is guaranteed that Lesha's problem has no repeated words, while the description of an archive problem may contain any number of repeated words.

The "similarity" between Lesha's problem and some archive problem can be found as follows. Among all permutations of words in Lesha's problem we choose the one that occurs in the archive problem as a subsequence. If there are multiple such permutations, we choose the one with the smallest number of inversions. Then the "similarity" of a problem can be written as ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF201D/7915a415961b72b48e6cd878bc6adf37cd6bd951.png), where $ n $ is the number of words in Lesha's problem and $ x $ is the number of inversions in the chosen permutation. Note that the "similarity" $ p $ is always a positive integer.

The problem is called brand new if there is not a single problem in Ivan's archive which contains a permutation of words from Lesha's problem as a subsequence.

Help the boys and determine whether the proposed problem is new, or specify the problem from the archive which resembles Lesha's problem the most, otherwise.

## 说明/提示

Let us remind you that the number of inversions is the number of pairs of words that follow in the permutation not in their original order. Thus, for example, if the original problem is "add two numbers", then permutation "numbers add two" contains two inversions — pairs of words "numbers" and "add", "numbers" and "two".

Sequence $ b_{1},b_{2},...,b_{k} $ is a subsequence of sequence $ a_{1},a_{2},...,a_{n} $ if there exists such a set of indices $ 1<=i_{1}&lt;i_{2}&lt;...\ &lt;i_{k}<=n $ that $ a_{ij}=b_{j} $ (in other words, if sequence $ b $ can be obtained from $ a $ by deleting some of its elements).

In the first test case the first problem contains the "find the palindrome next" permutation as a subsequence, in which the number of inversions equals 1 (words "palindrome" and "next").

In the second test case there is no problem that contains a permutation of words from Lesha's problem as a subsequence.

## 样例 #1

### 输入

```
4
find the next palindrome
1
10 find the previous palindrome or print better luck next time
```

### 输出

```
1
[:||||||:]
```

## 样例 #2

### 输入

```
3
add two numbers
3
1 add
2 two two
3 numbers numbers numbers
```

### 输出

```
Brand new problem!
```

## 样例 #3

### 输入

```
4
these papers are formulas
3
6 what are these formulas and papers
5 papers are driving me crazy
4 crazy into the night
```

### 输出

```
1
[:||||:]
```

## 样例 #4

### 输入

```
3
add two decimals
5
4 please two decimals add
5 decimals want to be added
4 two add decimals add
4 add one two three
7 one plus two plus three equals six
```

### 输出

```
3
[:|||:]
```

# 题解

## 作者：chenxia25 (赞：5)

首先吐槽一下为什么远古 CF 的题都这么奇怪……题面内容、输入、输出都非常恶心，让人很不爽……不过这道题倒是蛮好的（

---

**[Portal]( https://www.luogu.com.cn/problem/CF201D )**

首先映入脑帘的是一个状压 DP：$dp_{i,j}$ 表示当前考虑到第 $i$ 位，bitmask $j$ 内的单词都被选的时候的最小逆序对数。转移就看当前这位选不选，$\mathrm O(1)$。这样显然光空间就 $\mathrm O(k2^n)$ 了。

然后我想的是，从 5e5 里面只选 $n$ 个，那绝大多数都是没用的，能不能找点什么性质把一定没用的给筛掉，这样可以减小 $i$ 的值域。我想了一天，没想出来一个做法，然后就去看题解了（

注意到题解里的这样一句话：「Let's make use of a standard technique: make the value of DP a new parameter and make one of the existing parameters the value of DP.」（然后后面的笑脸「:)」有些邪恶）。意思就是注意到 DP 值是逆序对数，是 $\mathrm O(n^2)$ 的，非常小，显然要远小于 DP 数组的任意一维的定义域，于是我们考虑常用套路：调换 DP 数组的定义域和值域（这个套路在 809D 里也用到了，我怎么就还是不会呢）。这个大概要求 DP 值关于这维有单调性，那么用 bitmask 那维来换显然是不行的，难道记录逆序对数等于某个数的任意一个 bitmask？那就显然无法转移了。但是第一维有单调性。于是我们考虑 $dp_{i,j}$ 表示逆序对数等于 $i$，bitmask 为 $j$ 的最小满足要求的前缀的位置（其实 809D 也大概差不多是这个意思）。

突破了瓶颈，接下来就好办了。考虑如何转移，我们枚举最后一位的单词，然后不难得到上一个 bitmask（和所对应逆序对数，这个要减去前面那些对当前这个单词的贡献）所对应的最小前缀，然后根据贪心显然是找那个前缀后面的第一个这个字符，转移就可以了。这个每个位置的后面第一个每个字符可以预处理出来，那么复杂度就是 $\mathrm O\!\left(m(kn+2^nn^3)\right)$，看起来挺大的，但实际常数算是小的，而且时限 5s。

**_[code]( https://www.luogu.com.cn/paste/459rhmko )_**

---

## 作者：Tyyyyyy (赞：1)

## Tags:DP，优化
[原题](https://codeforces.com/contest/201/problem/D)
#### 题目大意
有 $n$ 个按顺序排列的单词，$m$ 句话，每句话由 $k$ 个单词组成。定义一句话的“差异度” $x$ 为这句话中是给出单词排列的子序列与原单词排列的最小交换次数。找到最小的 $x$，定义相似度 $p=\frac{n(n-1)}{2}-x+1$ ，输出最小 $x$ 所在话的编号，然后输出`[:`，`|`重复 $p$ 次和 `:]`。如果没有匹配的话，输出`Brand new problem!`。

这里，“交换次数”的定义如下：

假设原来的序列是`1 2 3 4`，现在的序列是`1 4 2 3`，则交换次数为 $2$。更通俗地说，将原序列中的单词按 $1,\dots,n$ 编号，则交换次数就是新序列对应后的逆序对数量。

数据范围：

$1 \leq n \leq 15,1 \leq m \leq 10,1 \leq \sum k \leq 5 \times 10^5$

保证 $n$ 个单词两两不同，每句话中单词可以重复。

#### 分析
为简化题意，我们可以用 map 给单词编号，然后取每句话中有编号的单词形成一个由 $1,\dots,n$ 构成的序列。问题转化为：

求一个包含 $1,\dots,n$ 的序列中是 $1,\dots,n$ 排列的子序列中最小的逆序对数。

注意到 $1 \leq n \leq 15$，可以很容易地想到一个状压 dp：

定义 $dp_{i,j}$ 表示考虑前 $i$ 个数，选数状态为 $j$ 时最小的逆序对数。

对于每个 $i$ 有选或不选两种情况，从 $i-1$ 转移即可。这里不再赘述。

可以知道上述方法尽管可以用滚动数组将空间优化到 $O(n)$，但时间复杂度不可避免地是 $O(k2^n)$，无法优化。

考虑交换上述方法中的 dp 定义和值，得到一个新的 dp：

定义 $dp_{i,j}$ 表示**最小**的 $k$，使在新序列中前 $k$ 个数满足选数状态为 $i$，且相似度 $p$ 为 $j$。

考虑从当前状态向后转移，需要知道之后第一个出现某数的位置。

我们记 $next_{i,j}$ 表示满足 $k>i$ 且 $sequence_k=j$ 的**最小**的 $k$。

每次从后往前扫，可以在 $O(nk)$ 的时间复杂度下完成 $next$ 数组的统计如下：

```cpp
for(int i=1;i<=n;i++)nxt[cnt][i]=cnt+1;
for(int i=cnt-1;i>=0;i--)
{
	for(int j=1;j<=n;j++)
        	nxt[i][j]=nxt[i+1][j];
	if(seq[i+1])nxt[i][seq[i+1]]=i+1;
}
```
（$cnt$ 是序列的长度）

那么有转移方程如下：

```cpp
for(int c=0;c<(1<<n);c++)
{
	for(int i=0;i<=n*(n-1)/2;i++)
	{
		if(dp[c][i]<cnt)
		{
			int ord=0;//顺序对（相似度增量） 
			for(int j=1;j<=n;j++)
			{
				if((c&(1<<j-1))==0&&nxt[dp[c][i]][j]<=cnt)
				{
					dp[c^(1<<j-1)][i+ord]=min(dp[c^(1<<j-1)][i+ord],nxt[dp[c][i]][j]);
				}
				else if(c&(1<<j-1))ord++;
			}
		}
	}
}
```

总共时间复杂度为 $O(m(nk+n^32^n))$，约为 $2 \times 10^8$。本题时间限制为 $5$ 秒，可以通过。

（代码关键部分上文已给出，不再给出全代码）

---

## 作者：LastKismet (赞：0)

# Sol
首先把字符串转换成数字，使用原序列中顺序为其编号。注意这里的原序列指的是给出的 $s_0$。

对于每一个长句，其中有用的字符串只有在原序列中出现过的，考虑把这些字符串相应编号提取出来，即可得到一个数字序列。那么题目所求也就是这个序列中某个子序列是原序列的一种排序，最大化这个子序列的顺序对数，答案即为这个顺序对数加一。

考虑 DP，发现 $n$ 很小，于是考虑状压，令 $f_{i,j}$ 表示当前序列前 $i$ 个数选出了 $j$ 状态的原序列数的最大顺序对数，转移是简单的，但是复杂度不对，是 $O(k2^n)$ 的。

发现逆序对数很少，于是考虑换维，换完后状态变成 $f_{i,j}$ 表示选出 $i$ 状态且顺序对为 $j$ 的最短前缀长度，显然前缀越短越优。转移是简单的，我们可以转移时实时统计已在序列中比当前数小的数，来得到这次转移会增加的逆序对数，同时我们预处理好每个位置的下一个某数的位置，即可快速转移新的前缀长度。

最后从大到小遍历顺序对数看是否可行（前缀长度小于等于序列长度）即可。

# Code
```cpp
const int N=15,K=500005;
 
int n,m;
string s;
map<string,int> mp;
vec<int> v;
int nxt[K][N];
int f[1<<N][N*N];
int rec[N],ans=-1;
 
inline void Main(){
    read(n);
    repl(i,0,n)read(s),mp[s]=i;
    read(m);
    rep(i,1,m){
        int len,k;read(k);
        v.clear();
        rep(i,1,k){
            read(s);
            if(!mp.count(s))continue;
            v.pub(mp[s]);
        }
        len=v.size();
        repl(i,0,n)nxt[len][i]=len+1;
        per(i,len-1,0){
            repl(j,0,n)nxt[i][j]=nxt[i+1][j];
            nxt[i][v[i]]=i+1;
        }
        repl(s,0,1<<n)rep(j,0,n*(n-1)>>1)f[s][j]=len+1;
        f[0][0]=0;
        repl(s,0,1<<n)rep(j,0,n*(n-1)>>1)if(f[s][j]<=len){
            int ans=0;
            repl(i,0,n){
                if(s&1<<i)++ans;
                else chmin(f[s|1<<i][j+ans],nxt[f[s][j]][i]);
            }
        }
        per(j,n*(n-1)>>1,0)if(f[(1<<n)-1][j]<=len){
            rec[i]=j+1;
            if(!~ans||rec[i]>rec[ans])ans=i;
            break;
        }
    }
    if(~ans){
        put(ans);
        put("[:",0);while(rec[ans]--)putchar('|');put(":]");
    }else put("Brand new problem!");
}

```

---

