# The Wu

## 题目描述

Childan is making up a legendary story and trying to sell his forgery — a necklace with a strong sense of "Wu" to the Kasouras. But Mr. Kasoura is challenging the truth of Childan's story. So he is going to ask a few questions about Childan's so-called "personal treasure" necklace.

This "personal treasure" is a multiset $ S $ of $ m $ "01-strings".

A "01-string" is a string that contains $ n $ characters "0" and "1". For example, if $ n=4 $ , strings "0110", "0000", and "1110" are "01-strings", but "00110" (there are $ 5 $ characters, not $ 4 $ ) and "zero" (unallowed characters) are not.

Note that the multiset $ S $ can contain equal elements.

Frequently, Mr. Kasoura will provide a "01-string" $ t $ and ask Childan how many strings $ s $ are in the multiset $ S $ such that the "Wu" value of the pair $ (s, t) $ is not greater than $ k $ .

Mrs. Kasoura and Mr. Kasoura think that if $ s_i = t_i $ ( $ 1\leq i\leq n $ ) then the "Wu" value of the character pair equals to $ w_i $ , otherwise $ 0 $ . The "Wu" value of the "01-string" pair is the sum of the "Wu" values of every character pair. Note that the length of every "01-string" is equal to $ n $ .

For example, if $ w=[4, 5, 3, 6] $ , "Wu" of ("1001", "1100") is $ 7 $ because these strings have equal characters only on the first and third positions, so $ w_1+w_3=4+3=7 $ .

You need to help Childan to answer Mr. Kasoura's queries. That is to find the number of strings in the multiset $ S $ such that the "Wu" value of the pair is not greater than $ k $ .

## 说明/提示

In the first example, we can get:

"Wu" of ("01", "00") is $ 40 $ .

"Wu" of ("10", "00") is $ 20 $ .

"Wu" of ("11", "00") is $ 0 $ .

"Wu" of ("01", "11") is $ 20 $ .

"Wu" of ("10", "11") is $ 40 $ .

"Wu" of ("11", "11") is $ 60 $ .

In the first query, pairs ("11", "00") and ("10", "00") satisfy the condition since their "Wu" is not greater than $ 20 $ .

In the second query, all strings satisfy the condition.

In the third query, pairs ("01", "11") and ("01", "11") satisfy the condition. Note that since there are two "01" strings in the multiset, the answer is $ 2 $ , not $ 1 $ .

In the fourth query, since $ k $ was increased, pair ("10", "11") satisfies the condition too.

In the fifth query, since $ k $ was increased, pair ("11", "11") satisfies the condition too.

## 样例 #1

### 输入

```
2 4 5
40 20
01
01
10
11
00 20
00 40
11 20
11 40
11 60
```

### 输出

```
2
4
2
3
4
```

## 样例 #2

### 输入

```
1 2 4
100
0
1
0 0
0 100
1 0
1 100
```

### 输出

```
1
2
1
2
```

# 题解

## 作者：Mickey_snow (赞：2)

注意在这题中01串都很短，长度不超过12，可以使用集合转换为整数表示，然后开一个二维数组，预处理一下所有可能查询的串和最大Wu值存在里面就可以了。

```cpp
int arr[i][v];
```

准确地说，数组第一维保存可能给定的一个01串转换为整数的值 $i$，第二位则是当Wu值 **恰好等于** $v$ 时的答案，随后在线地处理每一个询问，将小于最大Wu值的所有答案加起来即可。

```
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CF1017D
{
	class Program
	{
		public class Global{
			public static int[,] arr;
			public static int[] cnt, wuVal;
		}

		static void Main(string[] args)
		{
			string inp;string[] div;

			int len, totTemp, totQuery, maxWu, x, _count;

			inp = Console.ReadLine();div = inp.Split(' ');
			len = Convert.ToInt32(div[0]);totTemp = Convert.ToInt32(div[1]);totQuery = Convert.ToInt32(div[2]);

			Global.arr = new int[(1 << 13), 101];
			Global.cnt = new int[1 << 13];
			Global.wuVal = new int[len];

			//read
			inp = Console.ReadLine(); div = inp.Split(' ');
			for(int i = 0; i < len; i++)
				Global.wuVal[i] = Convert.ToInt32(div[i]);
			for(int i = 0; i < totTemp; i++) {
				inp = Console.ReadLine();
				x = 0;
				for(int j = 0; j < len; j++)
					if(inp[j] == '1') x |= (1 << j);
				Global.cnt[x]++;
			}

			//预处理
			for(int i = 0; i < (1 << len); i++) 
				for(int j = 0; j < (1 << len); j++)
					if(Global.cnt[i] > 0) {
						x = 0;  //代价
						for(int k = 0; k < len; k++)
							if((i & (1 << k)) == (j & (1 << k)))
								x += Global.wuVal[k];
						if(x <= 100) Global.arr[j, x] += Global.cnt[i];
					}

			while(totQuery-- > 0) {
				inp = Console.ReadLine();div = inp.Split(' ');
				maxWu = Convert.ToInt32(div[1]);

				_count = x = 0;
				for(int i = 0; i < len; i++)
					if(inp[i] == '1') x |= (1 << i);

				for(int i = 0; i <= maxWu; i++)
					_count += Global.arr[x, i];
				Console.WriteLine(_count.ToString());
			}

		}
	}
}

```

代码就是这样了，这道题时间卡得非常紧，导致我用C#调了半天还是超时。逐行翻译成 C++ 代码之后就AC了.

---

## 作者：Otue (赞：1)

## 思路
乍看 $n$ 非常小，于是可以从二进制出发，把一个 $01$ 字符串转化为一个具体的数值。

这样做有什么目的？会发现，这个数值大小不会超过 $2^{12}$，也就是说，真正存在的不重复的字符串数量只有 $2^{12}$ 个，那么题目给我们的 $m$ 个字符串其实就有很多重复，完全不需要枚举 $m\times m$，只需要 $2^{12}\times 2^{12}$ 就可以了。

存一个数组 $sum_{i,j}$ 表示跟字符串数值 $i$ 匹配且价值等于 $k$ 的字符串数量。

于是暴力枚举两个字符串，若这两个字符串的价值不超过 $100$（因为 $k\leq 100$），那就更新 $sum$ 数组。但是，最后求的答案是价值不超过 $k$ 的字符串数量，于是统计一个前缀和就好了。

## 代码

代码中定义单独一个字符串价值指的是所有 $1$ 的累计。

```c++
#include <bits/stdc++.h>
using namespace std;

const int N = 15, M = 1e5 + 5;
int n, m, q, w[N], cnt[M], vis[M];
int sum[M][105];

int get(char s[]) {  // 把字符串s转化成一个具体数值
    int res = 0;
    for (int i = n - 1; i >= 0; i--) {
        res = res * 2 + s[i] - '0';
    }
    return res;
}

int main() {
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            // cnt_i 表示单独字符串i的价值
            if (i >> j & 1) cnt[i] += w[j]; 
        }
    }
    while (m--) {
        char a[N];
        scanf("%s", a);
        vis[get(a)]++;  //
    }
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < (1 << n); j++) {
            int t = cnt[i ^ j ^ ((1 << n) - 1)];  // 求出字符串i和字符串j的混合价值
            if (t <= 100) sum[i][t] += vis[j];  // 更新一下
        }
    }
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j <= 100; j++) sum[i][j] += sum[i][j - 1];  // 前缀和 
    }
    while (q--) {
        char a[N];
        int k;
        scanf("%s%d", a, &k);
        cout << sum[get(a)][k] << endl;
    }
}
//  代码中还有许多细节，自己写的时候会发现
```

---

## 作者：Bpds1110 (赞：0)

感觉是比较诈骗的一个题。

注意到，给出的字符串数量 $m \le 5 \times 10^5$，但是串的长度 $n \le 12$，即最多有 $2^{12}$ 个本质不同的串。这启发我们从串中的元素进行考虑。

考虑枚举所有串 $s1$ 和 $s2$，分别表示**给定的串**和**要求匹配的串**，然后暴力统计贡献。对于每个要求匹配的串，其贡献必然 $\le k$，因此只需再进行前缀和即可。

为了方便实现，我们考虑对 01 串**状态压缩**，具体实现见代码。


```cpp
#include <bits/stdc++.h>
#define int long long

const int ML = 20, N = 5e5 + 10, MV = (1 << 12) + 10; 
int len, n, q, w[ML], cnt[MV], dp[MV][110];


void work() {
	for (int s1 = 0; s1 < (1 << len); ++ s1)
		if (cnt[s1]) 
			for (int s2 = 0; s2 < (1 << len); ++ s2) {
				int ret = 0;
				for (int bit = 0; bit < len; ++ bit) {
					int b1 = s1 & (1 << bit), b2 = s2 & (1 << bit);
					if (b1 == b2) ret += w[len - bit]; 
				}
				if (ret <= 100) dp[s2][ret] += cnt[s1]; 
			}
	for (int s = 0; s < (1 << len); ++ s)	
		for (int j = 1; j <= 100; ++ j)	dp[s][j] += dp[s][j - 1];
	return void(); 
}

int to(std::string str) {
	int ret = 0;  
	for (int j = 0; j < len; ++ j)
		if (str[j] == '1') ret += (1 << len - 1 - j);
	return ret; 
}

signed main() {
	
	std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr); 
	
	std::cin >> len >> n >> q;
	for (int i = 1; i <= len; ++ i) std::cin >> w[i]; 
	
	for (int i = 1; i <= n; ++ i) {
		std::string str; std::cin >> str;
		++ cnt[to(str)]; 
	}
	work(); 
	while (q --> 0) {
		std::string str; std::cin >> str;
		int k; std::cin >> k;
		std::cout << dp[to(str)][k] << "\n";
	}
	
	
	return 0; 
}
```

感觉 *1900 夸张了吧，虽然但是，笔者被 $m$ 的范围卡了很久。

---

## 作者：hcywoi (赞：0)

$n \le 12$，由此可得我们可以把`01`串映射成 $0 \sim 2^{12}-1$，方便存储。

$m \le 5 \times 10^5$，说明有很多 `01` 字符串是重复的。

先说明一下$\sum\limits_{i=1}^{n}w_i[s_i=t_i]$这里的 $s$ 和 $t$ 是 `01` 串，其它的 $s$ 和 $t$ 都是映射值。

先设 $sum_{i, j}$ 为 $t$ 为 $i$，且 $\sum\limits_{i=1}^{n}w_i[s_i=t_i]$ 恰好为 $j$ 的数量。

然后我们可以把枚举每一个 $s$ 和每一个 $t$，设 $x$ 为  $\sum\limits_{i=1}^{n}w_i[s_i=t_i]$，则把 $sum_{t, x} + cnt_s$ 其中 $cnt_s$ 表示 $s$ 出现的次数。

但题目要我们求 $\le k$ 的数量，所以我们要把 $sum$ 求一个前缀和。即 $sum_{i, j} = \sum\limits_{k=1}^{j}sum_{i, k}$。

### 时间复杂度

预处理 $ans$ 数组的时间复杂度为，$s$ 有 $2^n$ 个取值，$t$ 有 $2^n$ 个取值，求$\sum\limits_{i=1}^{n}w_i[s_i=t_i]$ 的时间复杂度是 $O(n)$，求前缀和的时间复杂度为 $O((2^n)^2k)$，总的时间复杂度为 $O((2^n)^2n + 2^nk)$。

每一次询问的时间复杂度是 $O(1)$ 的。

### Ac Code

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 4096;

int n, m, q;
char s[20];
int w[20], cnt[N], sum[N][110];

inline int calc(int x, int y) // 计算权值。
{
    int res = 0;
    for (int i = 0; i < n; i ++ )
        if ((x >> i & 1) == (y >> i & 1))
            res += w[n - i - 1]; // 这里一定要写n-i-1，如果不懂，可以看题意。
    return res;
}

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; i ++ ) scanf("%d", &w[i]);
    while (m -- )
    {
        scanf("%s", s);
        int cur = 0;
        for (int i = 0; s[i]; i ++ ) // 求映射后的值。
            cur = cur * 2 + s[i] - '0';
        cnt[cur] ++ ; // 把出现的次数 + 1。
    }
    for (int i = 0; i < N; i ++ ) // 预处理 sum 数组。
        for (int j = 0; j < N; j ++ )
        {
            int s = calc(i, j);
            if (s <= 100) sum[i][s] += cnt[j];
        }
    for (int i = 0; i < N; i ++ ) // 求前缀和。
        for (int j = 1; j <= 100; j ++ )
            sum[i][j] += sum[i][j - 1];
    
    while (q -- )
    {
        int k;
        scanf("%s%d", s, &k);
        int cur = 0;
        for (int i = 0; s[i]; i ++ )
            cur = cur * 2 + s[i] - '0';
        printf("%d\n", sum[cur][k]); // 输出答案。
    }
    
    return 0;
}
```

以上代码说实话有点玄学，容易 `TLE`，我们可以发现求$\sum\limits_{i=1}^{n}w_i[s_i=t_i]$ 可以用位运算实现。
- 先求出哪些位要 $+w[i]$，如果要则为 $1$，不用则为 $0$；
- 这个二进制可以用 $s \oplus t$ 然后取反，可以是 $s \oplus t \oplus 2^{n}-1$；
- 然后 $\sum\limits_{i=1}^{n}w_i[s_i=t_i]$ 就为这个二进制中所有 $1$ 所表示权值，这可以用预处理得到。

### Ac Code
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 4096;

int n, m, q;
char s[20];
int w[20], cur[N], cnt[N], sum[N][110];

int main()
{
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 0; i < n; i ++ ) scanf("%d", &w[i]);
    while (m -- )
    {
        scanf("%s", s);
        int cur = 0;
        for (int i = 0; s[i]; i ++ ) // 求映射后的值。
            cur = cur * 2 + s[i] - '0';
        cnt[cur] ++ ; // 把出现的次数 + 1。
    }
    for (int i = 0; i < N; i ++ )
    {
        for (int j = 0; j < n; j ++ )
            if (i >> j & 1)
                cur[i] += w[n - j - 1];
    }
    for (int i = 0; i < N; i ++ ) // 预处理 sum 数组。
        for (int j = 0; j < N; j ++ )
        {
            int s = cur[i ^ j ^ ((1 << n) - 1)];
            if (s <= 100) sum[i][s] += cnt[j];
        }
    for (int i = 0; i < N; i ++ ) // 求前缀和。
        for (int j = 1; j <= 100; j ++ )
            sum[i][j] += sum[i][j - 1];
    
    while (q -- )
    {
        int k;
        scanf("%s%d", s, &k);
        int cur = 0;
        for (int i = 0; s[i]; i ++ )
            cur = cur * 2 + s[i] - '0';
        printf("%d\n", sum[cur][k]); // 输出答案。
    }
    
    return 0;
}
```

---

## 作者：shao0320 (赞：0)

#### CF1017D The Wu

最近碰到好多前缀和题啊……

因为$N$最大才$12$，也就是总情况数就$2^{12}$种情况，那么可以考虑预处理之后直接回答询问。

再一看$K$最大只有$100$，那也就是说进行$Wu()$运算后答案大于$100$的根本没用，那就直接开桶即可，$f[i][j]$表示$multiset$里边所有数和$i$取$Wu$之后等于$j$的个数，处理后前缀和一下就可以了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#define N 500005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,q,w[N],cnt[N],tot,b[N],c[N],f[5000][105],val[N];
char ch[15];
int main()
{
	n=read();m=read();q=read();
	for(int i=1;i<=n;i++)w[i]=read();
	for(int i=1;i<=m;i++)
	{
		scanf("%s",(ch+1));
		int bas=1,x=0;
		for(int j=n;j>=1;j--)
		{
			if(ch[j]=='1')x+=bas;
			bas<<=1;
		}
		//cout<<x<<endl;
		cnt[x]++;
	}
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i&(1<<(j-1)))val[i]+=w[n-j+1];
		}
	}
	for(int i=0;i<(1<<n);i++)if(cnt[i]){b[++tot]=i;c[tot]=cnt[i];}
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=1;j<=tot;j++)
		{
			int anss=val[(i^b[j])^((1<<n)-1)];
			//cout<<i<<" "<<b[j]<<" "<<anss<<endl;
			if(anss<=100)f[i][anss]+=c[j];
		}
	}
	for(int i=0;i<(1<<n);i++)
	{
		for(int j=1;j<=100;j++)f[i][j]+=f[i][j-1];
		//for(int j=1;j<=100;j++)printf("%d ",f[i][j]);
		//puts(""); 
	}
	while(q--)
	{
		scanf("%s",(ch+1));
		int k=read(),xx=0,bas=1;
		for(int j=n;j>=1;j--)
		{
			if(ch[j]=='1')xx+=bas;
			bas<<=1;
		}
		//cout<<xx<<endl;
		printf("%d\n",f[xx][k]);
	}
	return 0;
}
```



---

