# [ABC122C] GeT AC

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc122/tasks/abc122_c

`A`, `C`, `G`, `T` からなる長さ $ N $ の文字列 $ S $ が与えられます。以下の $ Q $ 個の問いに答えてください。

- 問 $ i $ ($ 1\ \leq\ i\ \leq\ Q $): 整数 $ l_i,\ r_i $ ($ 1\ \leq\ l_i\ <\ r_i\ \leq\ N $) が与えられる。$ S $ の先頭から $ l_i $ 文字目から $ r_i $ 文字目までの (両端含む) 部分文字列を考える。この文字列に `AC` は部分文字列として何回現れるか。

## 说明/提示

### 注記

文字列 $ T $ の部分文字列とは、$ T $ の先頭と末尾から $ 0 $ 文字以上を取り去って得られる文字列です。

例えば、`ATCODER` の部分文字列には `TCO`, `AT`, `CODER`, `ATCODER`, `` (空文字列) が含まれ、`AC` は含まれません。

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ S $ は長さ $ N $ の文字列である。
- $ S $ の各文字は `A`, `C`, `G`, `T` のいずれかである。
- $ 1\ \leq\ l_i\ <\ r_i\ \leq\ N $

### Sample Explanation 1

\- 問 $ 1 $: $ S $ の先頭から $ 3 $ 文字目から $ 7 $ 文字目までの部分文字列は `ACTAC` です。この文字列に `AC` は部分文字列として $ 2 $ 回現れます。 - 問 $ 2 $: $ S $ の先頭から $ 2 $ 文字目から $ 3 $ 文字目までの部分文字列は `CA` です。この文字列に `AC` は部分文字列として $ 0 $ 回現れます。 - 問 $ 3 $: $ S $ の先頭から $ 1 $ 文字目から $ 8 $ 文字目までの部分文字列は `ACACTACG` です。この文字列に `AC` は部分文字列として $ 3 $ 回現れます。

## 样例 #1

### 输入

```
8 3
ACACTACG
3 7
2 3
1 8```

### 输出

```
2
0
3```

# 题解

## 作者：BlackPanda (赞：7)

**[题目传送门](https://www.luogu.com.cn/problem/AT4306)**

------------
### 题意：
给定一个长度为 $N$ 的字符串 $S$，有 $Q$ 次操作，每次给出 $L$ 和 $R$，求在 $L$ 到 $R$ 的区间中字符串 $\verb!AC!$ 出现了多少次？

------------
### 思路：
这里写出两种解法：

#### 1.暴力解法：

- 直接暴力枚举字符串下标 $L$ 到 $R$，然后记录字符串 $\verb!AC!$ 的出现次数即可。由于 $ 1\ \leq\ L\ <\ R\ \leq\ N $，所以最坏的时间复杂度是 $\mathcal{O}(n^2)$ 的，因为 $ 2\ \leq\ N\ \leq\ 10^5 $，所以肯定会超时。这里只给出核心代码：

```cpp
int main(){
	cin >> n >> q;
	cin >> s;
	while(q--){
		cin >> L >> R;
		int ans = 0;
		for(int i = L-1; i < R-1; ++i){
			if(s[i] == 'A' && s[i+1] == 'C'){
				ans++;
				++i;
			}	
		}
		cout << ans << endl;
	}
	return 0;
}

```

#### 2.动态规划解法：

- 由于  $ 2\ \leq\ N\ \leq\ 10^5 $，数据太大，每次进行查询的话很可能会超时，所以我们可以考虑动态规划的方法，预处理每 种情况，每次查询的复杂度可以从每次查询的 $\mathcal{O}(n^2)$  优化到仅 $\mathcal{O}(1)$。

- 具体做法为：我们定义 $\mathit{dp}_{i}$ 表示前 $i$ 个字符中 $\verb!AC!$ 的数量，从 $\mathit{dp}_{i-1}$ 到 $\mathit{dp}_{i}$ 转移方法为：如果 $\mathit{s}_{i-1}$ 和 $\mathit{s}_{i}$ 组成字符串 $\verb!AC!$，那么 $\mathit{dp}_{i}=\mathit{dp}_{i-1}+1$，否则 $\mathit{dp}_{i}=\mathit{dp}_{i-1}$。

$$
\begin{cases}
   \mathit{dp}_{i}=\mathit{dp}_{i-1}+1 &\text{} \mathit{s}_{i-1}=\text{'A'} \text{ and } \mathit{s}_{i}=\text{'C'} \cr
   \mathit{dp}_{i}=\mathit{dp}_{i-1} &\text{otherwise } 
\end{cases}
$$

#### code：
```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 100005

int n, q;
string s;
int L, R;
int dp[N];
//dp[i] 表示前 i 个字符中 AC 数量 

int main(){
	cin >> n >> q;
	cin >> s;
	dp[0] = 0;
	for(int i = 0; i < n; ++i){
		if(s[i] == 'A' && s[i+1] == 'C'){
			dp[i+1] = dp[i] + 1;
		}
		else{
			dp[i+1] = dp[i];
		}
	}
	while(q--){
		cin >> L >> R;
		cout << dp[R-1] - dp[L-1] << endl;
	}
	return 0;
}
```

---

## 作者：Lizj (赞：2)

## 分析题意

题目大意：给你一串长度为 $n$ 的字符串，其中包含 $\texttt{ACGT}$ 四种字符。给定 $m$ 次询问，每次询问包含两个整数，表示在 $[l,r]$ 这个区间。问区间内包含多少个  $\texttt{AC}$？

### 方法 $1$:

暴力枚举出区间内的 $\texttt{AC}$ 数量，代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,ans=0;
	string s;
	cin>>n>>m;
	cin>>s;
	while(m--){
		ans=0;
		int l,r;
		cin>>l>>r;
		for(int i=l-1;i<r-1;i++){	//因为字符串下标从零开始存储，所以一定要减1
			if(s[i]=='A'&&s[i+1]=='C'){	//判断区间内的AC数量
				ans++;
			}
		}cout<<ans<<endl;
	}
    return 0;
}
```
时间复杂度为 $O({n^2})$ 。但字符串长度有 ${10^5}$ 所以会超时。
于是，我们想到了动态规划……

### 方法 $2$：

$\texttt{DP}$ 的状态为：在前 $i$ 个字符中 $\texttt{AC}$ 的数量。由此可以得出：当 $S_i$ 与 $S_{i+1}$ 构成 $\texttt{AC}$ 时，状态转移方程为：
$$
\begin{aligned}

dp_i=dp_{i-1}+1

\end{aligned}
$$

当$S_i$ 与 $S_{i+1}$ 不构成 $\texttt{AC}$ 时，状态转移方程为：
$$
\begin{aligned}

dp_i=dp_{i-1}

\end{aligned}
$$
这样就把任意个位置的 $\texttt{AC}$ 个数存下来了，然后用末尾位置的 $\texttt{AC}$ 个数减去起始位置的个数就是答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,dp[100010];
string s;
int main(){
	cin>>n>>m;
	cin>>s;
	dp[0]=0;
	for(int i=0;i<n;i++){
		if(s[i]=='A'&&s[i+1]=='C'){
			dp[i+1]=dp[i]+1;//因为字符串下标从零开始存储，所以要加1才是正确的答案
		}
		else{
			dp[i+1]=dp[i];
		}
	}
	while(m--){
		int l,r;
		cin>>l>>r;
		cout<<dp[r-1]-dp[l-1]<<endl;//查询AC个数
	}
	return 0;
}
```

---

## 作者：Ryo_Yamada (赞：2)

开始看到这题不就是模拟嘛，直接打了暴力交上去，16pts，TLE*10:

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int cnt;
int main() {
	string s;
    int n, q, l, r;
    cin >> n >> q >> s;
    for(int i=0; i<q; i++) {
    	scanf("%d%d", &l, &r);
    	for(int j=l - 1; j<r - 1; j++) {
    		if(s[j] == 'A' && s[j + 1] == 'C') {
    			cnt++;
    			j++;
			}
		}
		printf("%d\n", cnt);
		cnt = 0;
	}
    return 0;
}
```
后来发现了数据范围：我$O((l - r)q)$的时间复杂度最坏情况$O(nq),nq \leq 1e10$。也就是说，此题需要写$dp$来优化查询到$O(1)$。

这也好办，~~但我WA了~~。因为……没写换行。在这里也悲痛地提醒大家记得换行！

最终$Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int dp[100000];//dp[i]表示前i个字符组成的字符串中有几个"AC".
int main() {
	string s;
    int n, q, l, r;
    cin >> n >> q >> s;
	for(int i=1; i<s.size(); i++) {
    	if(s[i] == 'C' && s[i - 1] == 'A') {
    		dp[i] = dp[i - 1] + 1;//如果有字符串"AC"，dp[i] = dp[i - 1] + 1.
		}
		else dp[i] = dp[i - 1];//拷贝dp[i - 1]的值
	}
    for(int i=0; i<q; i++) {
    	scanf("%d%d", &l, &r);
		printf("%d\n", dp[r - 1] - dp[l - 1]);//做出回答，记得换行！
	}
    return 0;
}
```


---

## 作者：jimmyfj (赞：1)

本题题目求 `AC` 作为子字符串在给定的区间 $[l, r]$ 内出现了多少次。

普通的思路: 先寻找字符 `A`， 如果找到了，在判断一下 `A` 后面是不是 `C`，然后对其累计数目。

但是这种做法肯定会 $TLE$ 的，所以我们要换一种做法。

基于本题是计算每个区间 `AC` 的个数，我们可以开一个前缀和数组 $cnt$，在每一个位置上记录下从字符串的开头到该位置的 `AC` 的个数，最后区间 $[l, r]$ 内的 `AC` 数量就是 $cnt[r - 1] - cnt[l - 1]$。（这里之所以是这样是因为我这里的前缀和数组下标是从 $0$ 开始的）

很简单的一道前缀和模子题，对吧，模板就不至于我再说了吧。

参考代码 :
```cpp
#include <bits/stdc++.h>

using namespace std;

string str;
int n, q;
int l, r;
int cnt[100005];

int main () {
    cin >> n >> q;
    cin >> str;
    cnt[0] = 0;
    for (int j = 1; j < str.size(); j ++) {
        if (str[j] == 'C' && str[j - 1] == 'A') {
            cnt[j] = cnt[j - 1] + 1;//如果这一位和前一位能组成 AC, 前缀和数组上加1
        }
        else {
            cnt[j] = cnt[j - 1];//否则就将前一位的数复制过来
        }
    }
    // for (int i = 0; i < n; i ++) cout << cnt[i] << endl;
    while (q --) {
        cin >> l >> r;
        cout << cnt[r - 1] - cnt[l - 1] << endl;
    }
    return 0;
}
```


---

## 作者：achjuncool (赞：0)

[题目](https://www.luogu.com.cn/problem/AT4306)

[博客](https://www.luogu.com.cn/blog/achjuncool/solution-at4306)

# 题目大意

给出一个长度为 $N$ 的字符串 $S$，每次询问输入一个子串的左下标 $l$ 与右下标 $r$，输出这个子串中有多少子串 ```AC```。

# 解法

相信有很多人一开始和我一样打的模拟，每个询问都 $\mathcal{O}(n)$ 搜一遍，结果超时了。

回来看了一眼数据范围，好家伙：

- $2\le N\le10^5$
- $1\le Q\le10^5$

这模拟肯定要超时。

那么该如何优化呢？

记得斐波那契数列吗？每次输入一个 $n$，输出这个数列的第 $n$ 项，我们不超时的解法是先预处理好数据范围内的整个数列，然后直接 $\mathcal{O}(1)$ 输出。

这题也是差不多的思路，建一个数组 $dp$，$dp_i$ 表示前 $i$ 个字符组成的子串中有多少字串 ```AC```，每次询问直接输出前 $r$ 个字符中的 ```AC``` 数量减去前 $l$ 个字符中的 ```AC``` 数量的差。

预处理的方式：对于 $dp_i$（$i>1$），如果 ```S.substr(i, 2)``` 是 ```AC```，$dp_i$ 就等于 $dp_{i-1}+1$，否则就等于 $dp_{i-1}$。

# Code

~~大家都最爱看这个是吗~~

```cpp
#include <iostream>
using namespace std;
int n, q, l, r, dp[100005];
string a;
int main(){
	cin >> n >> q;
	cin >> a;
	for(int i = 0; i < n; i++){
		if(a.substr(i, 2) == "AC"){
			dp[i + 1] = 1;
		}
		dp[i + 1] += dp[i];
	}
	for(int i = 1; i <= q; i++){
		cin >> l >> r;
		cout << dp[r - 1] - dp[l - 1] << endl;
	}
   return 0;
}
```

[AC](https://www.luogu.com.cn/record/80525751)

---

## 作者：Aehnuwx (赞：0)

cnblogs 上早就写了这题题解，昨天发现 AtCoder 的题被爬到 Luogu 上来了，赶快来交一发，~~结果今天发现已经有人写了一篇题解了~~

首先可以确定的是,既然 $N$ 已经到了 $10^5$ 的范围,并且还有个同样范围的 $Q$,显然不能用 $O(NQ)$ 的大暴力.

如何优化呢?遂盯着题目看,发现这道题的本质就是一个前缀和.

然后...就不用说了.

哦对了,唯一的坑点:查询时不能用 $sum_y-sum_{x-1}$,而需要使用 $sum_y-sum_x$.原因请读者自己探究.

Code($n$ 年前的代码了...):

```cpp
# include <bits/stdc++.h>
using namespace std;
# define maxN 100005
char s[maxN];
int N, Q, sum[maxN];
int main() {
	cin >> N >> Q >> s + 1;
    // 谨记，在此题中，字符串数组 s 读入时必须读入 s+1,如果直接 cin>>s,前缀和数组就会出现下标为 -1 的情况了
	for(int i = 1; i <= N; ++i) {
		sum[i] = sum[i - 1];
		if(s[i] == 'C' && s[i - 1] == 'A') ++sum[i];
        // 如果前后两个字符组成了一个 "AC",则前缀和数组 sum[i] 自加 1
	}
	while(Q--) {
		int x, y; cin >> x >> y;
        // 每次询问直接调用前缀和数组回答即可
		cout << sum[y] - sum[x] << endl;
	}
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc122_c)

## 思路

看到这个题的时间复杂度就知道没法暴力枚举。暴力枚举的时间复杂度是 $O(n^2)$，无法通过此题 $1\leq N,Q\leq 10^5$ 的数据。

于是我们就想到用前缀和，时间复杂度 $O(N+Q)$。

前缀和的思路呢，就是先定义一个前缀和数组 $P$，输入字符串 $S$ 后循环一遍，如果循环到 $S$ 的子字符串是 ``AC``，前缀和数组 $P_i$ 就 $+1$，否则 $P_i$ 就等于 $P_{i-1}$。

对于每次询问 $l_i$ 和 $r_i$，我们只需要输出 $P_{r_i-1}$ 与 $P_{l_i-1}$ 之差就可以了。

## 代码

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,p[100010];
string s;
int main(){
    cin>>n>>q>>s;
    for(int i=0;i<n-1;++i){
        p[i+1]=p[i];
        if(s[i]=='A'&&s[i+1]=='C')p[i+1]++;
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<p[r-1]-p[l-1]<<endl;
    }
    return 0;
}

~~~

[已经 AC 了](https://www.luogu.com.cn/record/96037477)

---

## 作者：FReQuenter (赞：0)

## 思路

这道题可以预处理 `AC` 的前缀和，每一个询问 $O(1)$ 查询前缀和。

与普通题目不同的是，这里要以两个字母为一个整体前缀和。这其实和普通的前缀和没有多少区别，只要：

1. 以 `A` 或 `C` 为记录一组 `AC` 的“端点”。

2. 预处理时判断当前两个字母是不是 `AC`。

3. 查询时注意边界。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,sum[200005];
string s;
signed main(){
  cin>>n>>q>>s;
  s='#'+s;
  for(int i=2;i<=n;i++) sum[i]=sum[i-1]+(s[i]=='C'&&s[i-1]=='A');//预处理，这里是以 C 为“端点”
  while(q--){
    int l,r;
    cin>>l>>r;
    cout<<sum[r]-sum[l]<<endl;//查询，这里注意因为以C为端点，所以查询区间其实是 [l+1,r]，如果以 A 为端点，区间就是 [l,r-1]。
  }
}
```

---

## 作者：ZXXS (赞：0)

前缀和 dp 储存前 i 个字母的 "AC" 个数。

如果前一个字母为 A 且这个字母为 C 就多了一个 AC。
 
否则就和前一个的 AC 数量一样


```cpp
#include<bits/stdc++.h>
using namespace std;
inline void write(int x)//快写
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9)
		write(x/10);
	putchar(x%10+'0');
}
inline int read()//快读
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
    return x*f;
}
int dp[100005],n,q,l,r;//dp[i]储存储存前i个字母的"AC"个数
char in[100005]; //输入
int main()
{
	n=read(),q=read();//输入
	for(int i=1;i<=n;++i)
	{
		scanf("%c",&in[i]);
		dp[i]=dp[i-1]+(in[i]=='C'&&in[i-1]=='A'?1:0);//前一个字符是"A"并且这个字符是"C"AC个数就加一，否则就是上一个
	}
	for(int i=1;i<=q;++i)
	{
		l=read(),r=read();
		write(dp[r]-dp[l]);//前缀和O(1)查询
		putchar('\n');//换行
	}
    return 0;
}

```

---

