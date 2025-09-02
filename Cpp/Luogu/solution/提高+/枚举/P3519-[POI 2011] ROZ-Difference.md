# [POI 2011] ROZ-Difference

## 题目描述

给定一个由 $n$ 个小写英文字母（'a'-'z'）组成的单词。

我们希望选择该单词的一个非空连续（即一段）片段，以最大化该片段中出现次数最多的字母与出现次数最少的字母之间的差异。

我们假设出现次数最少的字母在结果片段中至少出现一次。

特别地，如果片段中只包含一种字母的出现，那么其中出现次数最多和最少的字母是相同的。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
10
aabbaaabab```

### 输出

```
3```

# 题解

## 作者：bzy369258147 (赞：9)

不同的解法 : 更简单的思想. 

前置知识: 需要对归并排序的实现有所了解 ).

由于这个题目的字符集大小只有26,我们显然可以枚举出现次数最多与最少的字符是什么。然后把这两个字符离散出来问题就变成了只有1与-1且强制选取至少一个-1的最大连续子段和问题。

然后关于离散，我们显然可以用vector把每中字符的出现位置记录下来。然后用类似归并的方法求解即可。

关于强制选取至少一个-1的最大连续子段和问题,我们可以先把答案预设为-1然后到第一个-1时不减即可解决。

由于每种字符作为最大与最小总共被枚举52次，所有字符的数量和为n

所以时间复杂度为 $O(52n)$

空间复杂度 $O(n)$

以下是代码:

```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int> bin[26];
char s[1000005]; int n;

int ans = 0;

int main(){
    cin >> n >> s;
    for(int i = 1;i <= n;i ++) bin[ s[i - 1] - 'a' ].push_back(i);
    for(int i = 0;i < 26;i ++) if( bin[i].size() ) 
        for(int j = 0;j < 26;j ++) if( bin[j].size() ) if( i ^ j ) {
            int pt1 = 0, pt2 = 0, fir = 0;
            int all = -1;
            while( pt1 < bin[i].size() or pt2 < bin[j].size() ) {
                int tp1 = pt1 == bin[i].size() ? 1e9 : bin[i][pt1];
                int tp2 = pt2 == bin[j].size() ? 1e9 : bin[j][pt2];
                if( tp1 < tp2 ) all ++, pt1 ++;
                if( tp1 > tp2 ) { if( fir ) all --; pt2 ++; fir = 1; }
                if( all < 0 ) all = -1, fir = 0;
                ans = max( ans, all );
            }
        }
    cout << ans;
    return 0;
}
```


---

## 作者：huangjinxiu (赞：4)

~~今天联考T2，蒟蒻抢了最优解来水篇题解~~ 其实是蒟蒻的第一篇题解

前置知识: 最大子段和。

由于字符集很小，只有 $26$ 所以我们可以钦定最多出现次数的字符 $$a$$ 与最少的字符 $$b$$（注意 $$a,b$$ 都必须是字符串中出现过的），将所有 $$a$$ 赋值为 $$1$$，所有 $$b$$ 赋值为 $$-1$$，其余字符赋值为 $$0$$，求强制至少选一个 $$-1$$ 的最大字段和。

我们用 $$f[a][b]$$ 表示以钦定 $$a$$ 为最多出现次数的字符，$$b$$ 为最少出现次数的字符的最大子段和。容易发现 $$f[a][b]$$ 的转移只与上一次的 $$f[a][b]$$ 和下一次的 $a,b$ 出现的位置有关，于是可以直接滚动数组，从左往右枚举字符 $$s[i]$$，并处理 $$a=s[i]$$ 与 $$b=s[i]$$ 的情况，剩下的一维则枚举。

记 $$a=s[i]$$。

$$f[a][b]$$ 更新为 $$f[a][b]+1$$ 表示一定会选当前这个 $$a$$。

$$f[b][a]$$ 更新为 $$\max(0, f[b][a] - 1)$$。

考虑如何强制至少选一个 $$-1$$：

我们用 $$h[a][b]$$ 表示当前选/没选至少一个 $$-1$$
。则统计答案时记为 $$f[a][b]- (\neg h[a][b])$$。

$$h[b][a]$$ 随 $$f[b][a]$$ 转移，当 $$f[b][a]\ge1$$ 时有 $$h[b][a]=1$$。

代码很好写：
```cpp
#include <bits/stdc++.h>
#define a s[i]
using namespace std;
int f[26][26], n, A, i, v[26];
bool h[26][26];char s[1000001];
vector<int> e;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> s;
    for (i = 0; i < n; ++i)
        if (!v[a -= 'a']) {
            v[a] = 1;
            e.push_back(a);//记录出现过的字符集 
        }
    for (i = 0; i < n; ++i)
        for (int b : e)
            if (b ^ a) {
                ++f[a][b];  
                A = max(A, f[a][b] - !h[a][b]);//记录答案，如果没有选-1要减去1 
                h[b][a] = f[b][a];//h为bool类型 表示h[b][a]=[f[b][a]>=1],若上一次的f[b][a]不为0表示可选这个-1 
                f[b][a] = max(0, f[b][a] - 1);
            }
    cout << A;
    return 0;
}
```
时间复杂度 $O(n)$ 常数极小，跑了124ms。

---

## 作者：Manjusaka丶梦寒 (赞：4)

联考考试考到了这个题，随机化40分，现在来秒掉它吧。

挂个[blog](https://www.cnblogs.com/rmy020718/p/9615482.html)

我们定义$cnt[i][j]$表示区间$[1,i]$中，j出现的次数,

定义字符a，b(非字符a，b),a为出现最多的字符，b为出现最少的字符。

我们利用前缀和统计每一个字符出现的次数。

那么对于一个区间$[i,j]$，字符a出现的次数为$cnt[j][a]-cnt[i][a]$，字符b出现的次数为$cnt[j][b]-cnt[i][b]$，我们枚举每一个字符的配对情况。

对于26个字符$$ans=max \{ ans,(cnt[j][a]-cnt[i][a])-(cnt[j][b]-cnt[i][b]) \}$$。

这样枚举时间复杂度$O(n^2 \times 26 \times 26)$，还可以啦。

现在我们来优化一下上边的过程。

$$(cnt[j][a]-cnt[i][a])-cnt[j][b]-(cnt[i][b])$$

可以变为

$$(cnt[j][a]-cnt[j][b])-(cnt[i][a]-cnt[i][b])$$

对于算式的前半边O(n \times 26)枚举，我们来优化一下后半边。

对于后边的式子，求得为j以前$cnt[i][a]-cnt[i][b]$的最小值，然而j是怎么过来的，到了j必然前边的数都有经过，所以我们在枚举是维护一个$cnt[i][a]-cnt[i][b]$的最小值即可(代码中用到minv数组)。

代码中有p[i][j]数组表示更新字符i和字符j差的最小值的位置。
```cpp
#include<complex>
#include<cstdio>
using namespace std;
const int N=1e6+7,M=27;
int n,ans;
int last[M],num[M],p[M][M],minv[M][M];
//last表示字符最后出现的位置，num表示字符出现的次数。
//p数组表示更新维护最小值的位置，minv表示维护的最小值。 
char s[N];
int main()
{
//	freopen("B.in","r",stdin);
//	freopen("B.out","w",stdout);
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++)
	{
		int c=s[i]-'a';
		num[c]++;last[c]=i;
		for(int j=0;j<26;j++)
			if(j!=c && num[j])
				ans=max(ans,max(num[c]-num[j]-minv[c][j]-(last[j]==p[c][j])
				,num[j]-num[c]-minv[j][c]-(last[c]==p[j][c])));
		//这个判断：如果成立，那么那个点属于前一段区间。 
		for(int j=0;j<26;j++)
			if(num[j]-num[c]<minv[j][c])
			{
				minv[j][c]=num[j]-num[c];
				p[j][c]=i;
			}
		//更新最小值。 
	}
	printf("%d\n",ans);
//	fclose(stdin);fclose(stdout);
	return 0;
}
```

---

## 作者：fuqingchen (赞：3)

# 原题链接

[P3519 POI2011 ROZ-Difference](https://www.luogu.com.cn/problem/P3519)

# 题目简述

给一个字符串，求其中的一段，使得出现次数最多的字符与出现次数最少的字符的出现次数之差最大。

# 解题思路

因为小写字母只有 $26$ 个，所以可以枚举最小的字符、最大的字符是哪个，然后将最小字符的位置设为 $-1$，最大字符的位置设为 $1$，其余设为 $0$。接着统计出每个字符出现的位置，对于枚举的两个字符按下标类似归并的方法排序，最后在这些下标中做一遍最大子段和。

# 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
int n, f[N], res, cnt[30];
char s[N];
bool fl[N];
vector<int> vec[30];
signed main() {
    cin >> n >> (s + 1);
	for (int i = 1; i <= n; ++i) vec[s[i] - 'a'].push_back(i), ++cnt[s[i] - 'a'];
    for (int i = 0; i <= 25; ++i) {
        for (int j = 0; j <= 25; ++j) {
            if (i == j || !cnt[i] || !cnt[j]) continue;
			int l1 = 0, l2 = 0, ma = 0, fl = 0, now = -1;
			int len1 = (int)vec[i].size() - 1, len2 = (int)vec[j].size() - 1;
			while (l1 <= len1 || l2 <= len2) {
				int x = vec[i][l1], y = vec[j][l2];
				if (l1 > len1) x = 0x3f3f3f3f;
				if (l2 > len2) y = 0x3f3f3f3f;
				if (x < y) {
					++now;
					++l1;
				}
				else {
					if (fl) --now;
					++l2;
					fl = 1;
				}
				if (now < 0) now = -1, fl = 0;
				res = max(res, now);
			}
			// res = max(ma, res); 
        }
    }
	cout << res;
    return 0;
}
```


---

## 作者：chenxumin1017 (赞：2)

~~联考 T2,场切了，来写篇题解。~~

观察到答案只和出现次数最多的字符的出现次数与出现次数最少的的字符的出现次数有关，考虑枚举出现最多的字符和出现最少的字符。

令枚举出来的字符分别为 $i$ 和 $j$。 

枚举之后，题目就转化成了：
- 出现其它字符答案不变。
- 出现一次 $i$ 答案就会加一。
- 出现一次 $j$ 答案就会减一。

你要选择一个字串进行以上操作，使得答案最大，这显然是最大子段和板子。

最后在对于每一种 $i$ 和 $j$ 的组合的答案取最大值。

## 代码

令字符集为 $S$。

时间复杂度：$O({|S|}^{2}N)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, a[N], sum[N];
string s;
vector<int> v[100];
int main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> s;
  s = ' ' + s;
  for(int i = 1; i <= n; i++){
    v[s[i] - 'a'].push_back(i);
  }
  int ans = 0;
  for(int i = 0; i < 26; i++){
    for(int j = 0; j < 26; j++){
      if(i == j || v[i].size() == 0 || v[j].size() == 0)continue;
      int x = 0, y = 0, cnt = 0;
      while(x < v[i].size() || y < v[j].size()){
        if(x == v[i].size())a[++cnt] = -1, ++y;
        else if(y == v[j].size())a[++cnt] = 1, ++x;
        else{
          if(v[i][x] < v[j][y]){
            a[++cnt] = 1, ++x;
          }else{
            a[++cnt] = -1, ++y;
          }
        }
      }
      int summ = 0, flag = 0, last = 0;
      for(int k = 1; k <= cnt; k++)sum[k] = sum[k - 1] + a[k];
      for(int k = 1; k <= cnt; k++){
        summ += a[k];
        if(a[k] < 0)flag = 1, last = k;
        if(summ < 0){
          flag = 0, summ = 0;
        }
        if(flag)ans = max(ans, summ);
        else if(last)ans = max(ans, sum[k] - sum[last - 1]);
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：Phobia (赞：2)

读完题目，显然有这样一个想法，枚举出现次数最多和最少的字符，统计其答案。

于是我们定义：

- $f[i][j][k][0]$ 表示以第 $i$ 个字符为结尾，字符 $j$ 为出现次数最多，字符 $k$ 为出现最少的字符，最长不含字符 $k$ 的子串中字符 $j$ 的个数。

- $f[i][j][k][1]$ 表示以第 $i$ 个字符为结尾，字符 $j$ 为出现次数最多，字符 $k$ 为出现最少的字符，字符 $k$ 至少出现一次时，字符 $j$ 出现的次数减去字符 $k$ 出现的次数的最大值。若字符 $k$ 没有出现，则 $f[i][j][k][1] = -1$。

转移方程：

- 当 $s[i] = j$时：

	$f[i][j][k][0] = f[i-1][j][k][0]+1$
   
   $f[i][j][k][1] = \begin{cases}
   f[i - 1][j][k][1] + 1, & f[i - 1][j][k][1] \neq -1\\
   -1, & f[i - 1][j][k][1] = -1.
   \end{cases}$
   
- 当 $s[i] = k$时：

	$f[i][j][k][0] = 0$
    
   $f[i][j][k][1] = \max(f[i - 1][j][k][0], f[i - 1][j][k][1]) - 1$

- 否则：
	
   $f[i][j][k][0] = f[i - 1][j][k][0]$
   
   $f[i][j][k][1] = f[i - 1][j][k][1]$

答案为 $\max(f[i][j][k][1], 0)$。

但是直接 dp 时间空间都过不去，考虑优化。

我们发现 $f$ 数组第 $i$ 项只和 $i - 1$ 项有关，于是砍掉 $i$ 这维。

此外，只有 $s[i] = j$ 或 $s[i] = k$ 时 $f$ 数组才会被更新，所以只需要将 $j$ 和 $k$ 其中一个固定为 $s[i]$，然后枚举另一个更新 $f$ 数组即可。

时间复杂度 $O \left( 52n \right)$, 空间复杂度 $O \left( n + 2 \times 26 ^ 2\right) = O \left( n \right)$。

代码:

~~~cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000005, maxs = 26;

char s[maxn];

int f[maxs][maxs][2], n, ans;

int main()
{
    scanf("%d%s", &n, s + 1);
    for (int i = 0; i < 26; ++i)
    {
        for (int j = 0; j < 26; ++j)
            f[i][j][1] = -1; // 最开始并没有字符，所以要给-1
    }
    for (int i = 1; i <= n; ++i)
    {
        int j = s[i] - 'a';
        for (int k = 0; k < 26; ++k)
        {
            if (j == k) // 最多和最少字符不能相同
                continue;

            ++f[j][k][0];
            if (f[j][k][1] != -1)
                ++f[j][k][1];

            f[k][j][1] = max(f[k][j][0], f[k][j][1]) - 1;
            f[k][j][0] = 0;

            ans = max(ans, max(f[j][k][1], f[k][j][1]));
        }
    }
    printf("%d\n", ans);
    return 0;
}
~~~

---

## 作者：_Imaginary_ (赞：2)

看完题目，我下意识地码了一个前缀和，不过似乎没什么用。

## Problem

一个字符串，求其中出现次数最多的字符的出现次数减去出现次数最少的字符出现次数的差的最大值。

显然，对于每一个子串，只和两种字符有关。

## Solution

我们可以尝试枚举这两种字符，假设为 $a$ 和 $b$，随后我们找出子串中出现 $a$ 较多，$b$ 较少的一个子串。

我们想到了前缀和。以样例为例，我们来试着枚举一下。

| |1|2|3|4|5|6|7|8|9|10|
|-|-|-|-|-|-|-|-|-|-|-|
|a|1|2|2|2|3|4|5|5|6|6|
|b|0|0|1|2|2|2|2|3|3|4|
|a-b|1|2|1|0|1|2|3|2|3|2|
|$\Delta$|1|1|-1|-1|1|1|1|-1|1|-1|

经过计算，我们可以发现我们要求的是 $\Delta$ 的最大子序列和，要求必须要选 $-1$。

这我们可以用归并来解决。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod=1000000007;
int n;
char s[1000005];
vector<int> g[30];
int ans=0;
int main()
{
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++) g[s[i]-'a'].push_back(i);
	for(int i=0;i<26;i++)
		if(g[i].size())
		for(int j=0;j<26;j++)
			if(g[j].size()&&i!=j)
			{
				int t1=0,t2=0;
				int cur=-1;
				bool ok=0;
				while(t1<g[i].size()||t2<g[j].size())
				{
					int q1=g[i][t1],q2=g[j][t2];
					if(t1==g[i].size()) q1=0x3f3f3f3f;
					if(t2==g[j].size()) q2=0x3f3f3f3f;
					if(q1<q2) cur++,t1++;
					if(q1>q2)
					{
						if(ok) cur--;
						t2++,ok=1;
					}
					if(cur<0) cur=-1,ok=0;
					ans=max(ans,cur);
				}
			}
	printf("%d",ans);
	return 0;
}

```

---

## 作者：K_yuxiang_rose (赞：1)

这题不值得蓝。

考虑到字母只有 $26$ 个，我们直接枚举所有可能的最多字母减最少字母的情况，共枚举 $26^2$ 次。

然后，对于每种情况寻找最佳答案。似乎是双指针？但是想不起来怎么写了。进一步思考，我们设枚举的情况中，出现次数最多的字母为 $x$，出现次数最多的字母为 $y$。那么，$x$ 会为答案贡献 $+1$，$y$ 会对答案贡献 $-1$，其余字母对答案贡献为 $0$。原字符串就会变成一个只包含 $-1$，$0$，$1$ 的数列了，我们的任务就变为了求数列的最大子段和。那这道蓝题就变成[橙题](https://www.luogu.com.cn/problem/P1115)了。

自信写出代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000005];
int f[1000005];
signed main()
{
	int n,ans=0;
	cin>>n;
	scanf("%s",s+1);
	for(int i=1;i<=n;i++) f[int(s[i]-'a')]=1;
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<26;j++)
		{
			if(!f[i]||!f[j]) continue;
			char x='a'+i,y='a'+j;
			int maxn=0,num=0;
			for(int i=1;i<=n;i++)
			{
				if(s[i]==x) num--;
				if(s[i]==y) num=max(num+1,1);
				maxn=max(maxn,num);
			}
			ans=max(ans,maxn);
		}
	}
	cout<<ans;
	return 0;
}
```

发现 WA 了。

再进一步发现，这题的最大子段和与那道橙题不太一样，必须包含 $x$ 和 $y$，也就是说，所求的子段必须包含 $-1$ 和 $1$。这很好办，只要建两个变量维护 $-1$ 和 $1$ 是否被使用过即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1000005];
int f[1000005];
signed main()
{
	int n,ans=0;
	cin>>n;
	scanf("%s",s+1);
	for(int i=1;i<=n;i++) f[int(s[i]-'a')]=1;
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<26;j++)
		{
			if(!f[i]||!f[j]||i==j) continue;
			char x='a'+i,y='a'+j;
			int maxn=0,num=0;
			int flag1=0,flag2=0;
			for(int i=1;i<=n;i++)
			{
				if(s[i]==x) num--,flag1=1;
				if(s[i]==y)
				{
					if(num+1>=1) flag2=1,num++;
					else flag1=0,flag2=1,num=1;
				}
				if(flag1&&flag2) maxn=max(maxn,num);
				else maxn=max(maxn,num-1);
			}
			ans=max(ans,maxn);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Ristear (赞：1)

## 题解

我们先预处理记录每个字符出现的位置。

然后枚举出现次数最多的字符和出现次数最少的字符。

用两个指针记录两个以 $1$ 为起点的区间的终点，并记录此时的差值。

如果某一指针向右移，能使出现最多的字符数增多，那就向右移，统计的答案加 $1$。如果不能，那就向右移另一个。

如果移动时出现了统计数为负的情况就可以重新从 $0$ 开始统计。

是否存在我们枚举的区间内出现的最多的字符和最少的字符并不是最多和最少的情况？其实是会的，但是这种情况下的答案必然不是最优解，即这个答案会在枚举时被更新。

时间复杂度为 $\mathcal O(26 \times 26 \times n)$。

具体细节可以参照代码。
## Code
~~~ cpp

int n;
int ans=1;
int cnt[27];
int whe[27][1000010];
void init()
{
	char x;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		x-=('a'-1);
		cnt[x]++;//记录出现次数
		whe[x][cnt[x]]=i;//记录位置
	}
}
void solve()
{	
	for(int i=1;i<=26;i++)
	{
		if(!cnt[i]) {continue;}
		for(int j=1;j<=26;j++)
		{
			if(!cnt[j]||i==j) {continue;}int q1=1,q2=1,res=-1,ch=0;
			for(int t=1;t<=cnt[i]+cnt[j];t++)
			{
				if(q2>cnt[j]||(q1<=cnt[i]&&whe[i][q1]<whe[j][q2])) {q1++;res++;}
				//q1在q2前面 q1指向下一个 
				else {q2++;res-=(ch==1?1:0);ch=1;}//q2指向下一个 这个点是否产生贡献
				if(res<0) {ch=0;}//重新开始统计
				ans=max(ans,res);
			}
		}
	}
	return ;
}

~~~

---

## 作者：Poncirus (赞：1)

好耶我会打 $n^3$！这说明这道题肯定是一个我不会写的 $n^2$！

$n$ 是 $10^6$？寄……

---

枚举出现次数最多的字符（假设为 $x$）和出现次数最少的字符（假设为 $y$）。

然后用一个类似于双指针的东西，总之意思就是我们要让 $y$ 和 $x$ 第一次出现的地方分别成为起始区间的起点和终点。

说是起点和终点，但实际上不用特别在意它们一开始的前后顺序，因为我们会把 $26\times 26$ 中情况全部枚举一遍，而且不排除存在 $x$ 反杀的可能性。

然后，如果右端点能往右挪，多塞下一个 $x$，我就肯定往右挪，此时统计的答案增加 $1$。如果 $x$ 挪不了了，那就往右挪 $y$，不停下来是因为虽然 $x$ 现在一时吃瘪，但后面还是有可能反杀 $y$。

那么问题来了，你怎么知道你枚举的这个区间里 $x$ 一定出现次数最多，$y$ 一定出现次数最少？

思考，如果 $x$ 出现次数不是最多，$y$ 出现次数不是最少，说明答案也不是这个区间里最多的，所以后面还会被更新。

关于「往右挪」这个操作，我们预处理一下某个字符某一次出现的位置就好。

**然后注意跳的时候如果出现了数量统计为负的情况就可以从 0 开始统计了！**

然后最后的时间复杂度是 $\mathcal O(n)$，因为要非常严谨地 KA 掉常数，虽然这个常数是一个明显跑不满的 $10^2$ 级别。

---

```cpp
namespace XSC062 {
using namespace fastIO;
const int maxm = 28;
const int maxn = 1e6 + 5;
char s[maxn];
int cnt[maxm];
int d[maxm][maxn];
int n, l, r, res, ans, t, f;
inline int max(int x, int y) {
	return x > y ? x : y; 
}
int main() {
	read(n);
	reads(s + 1);
	for (int i = 1; i <= n; ++i)
		d[s[i] - 'a' + 1][++cnt[s[i] - 'a' + 1]] = i;
	for (int x = 1; x <= 26; ++x) {
		if (!cnt[x])
			continue;
		for (int y = 1; y <= 26; ++y) {
			if (!cnt[y] || x == y)
				continue;
			f = 0;
			t = cnt[x] + cnt[y];
			l = 1, r = 1, res = -1;
			while (t--) {
				if ((l <= cnt[x] && d[x][l] < d[y][r])
					|| r > cnt[y])
					++l, ++res;
				else ++r, res -= f, f = 1;
				if (res < 0)
					f = 0;
				ans = max(ans, res);
			}
		}
	}
	print(ans);
	return 0;
}
} // namespace XSC062
```

---

## 作者：Unnamed114514 (赞：1)

### Step.1

容易想到直接枚举最大和最小两个字符，左端点和右端点，然后用前缀和维护出现次数，对于最大值为 $a$，最小值为 $b$，选择 $[l,r]$ 区间，令 $cnt$ 为前缀和数组，那么则有：

$$ans=\max\{(cnt_{a,r}-cnt_{a,l-1})-(cnt_{b,r}-cnt_{b,l-1})\}$$

时间复杂度 $O(26^2n^2)$。

### Step.2

观察式子，假设我们现在确定了 $r,a,b$，整理得：

$(cnt_{a,r}-cnt_{b,r})+(cnt_{b,l-1}-cnt_{a,l-1})$

那么我们此时这个式子中 $cnt_{a,r}-cnt_{b,r}$ 为定值，那么就是维护 $cnt_{b,l-1}-cnt_{a,l-1}$ 的最值，注意到此时可以使用双指针，在 $r\gets r+1$ 的同时在保证 $cnt_r-cnt_l\ge1$ 的情况下 $l$ 尽量向右移，这样可以求出最大的 $l$，然后直接用前缀 $\max$ 维护即可。

时间复杂度 $O(2\times26^2n)$，折合 $O(1352n)$，发现 $n=10^6$，仍然过不了，需要优化常数。

### Step.3

注意到一个事情：对于字符串中既不是 $a$ 又不是 $b$ 的字符是无法作出贡献的，只有 $a$ 或 $b$ 才能作出贡献。

那么我们可以将 $a$ 和 $b$ 新开一个数组存储，然后再维护。

这样，每个字符只会在做最大值或最小值时被计算到，优化了一个 $26$，时间复杂度 $O(2\times26n)=O(52n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,ans,cnt[26][maxn],t[maxn];
vector<int> num[26];
inline char gc(){
    static char buf[1000000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
    int res=0;
    static char ch=gc();
    while(isdigit(ch)){
		res=(res<<1)+(res<<3)+(ch^'0');
		ch=gc();
	}
    return res;
}
int main(){
	n=read();
    for(int i=1;i<=n;++i){
    	char c=gc();
    	while(c<'a'||c>'z')
			c=gc();
    	for(int j=0;j<26;++j)
			cnt[j][i]=cnt[j][i-1];
		++cnt[c-'a'][i];
		num[c-'a'].push_back(i);
	}
	for(int a=0;a<26;++a)
		if(num[a].size())
			for(int b=0;b<26;++b)
				if(a!=b&&num[b].size()){
					int x=num[a].size(),y=num[b].size(),l=0,tot=0;
					for(int i=0;i<y;++i){
						while(l<x&&num[a][l]<num[b][i])
							t[++tot]=num[a][l++];
						t[++tot]=num[b][i];
					}
					while(l<x)
						t[++tot]=num[a][l++];
					int now=0,maxx=0;
					for(int i=1;i<=tot;++i){
						while(now<i&&cnt[b][t[i]]-cnt[b][t[now]]>=1){
							maxx=max(maxx,cnt[b][t[now]]-cnt[a][t[now]]);
							++now;
						}
						if(cnt[b][t[i]]-cnt[b][t[now-1]]>=1)
							ans=max(ans,cnt[a][t[i]]-cnt[b][t[i]]+maxx);
					}
				}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
写篇题解纪念我调了两小时的细节。
## 思路
首先发现，字符串中只有 $26$ 种不同字符。

可以暴枚哪种字符最多，哪种最少。

但是，这样的时间复杂度会超时四个点~~本人亲测~~,但原题解能过，很极限。

于是我们要优化枚举字符串的地方。

不难发现，当枚举两个字符时，其他字符是没用的，我们开一个 vector 存每种字符的每个位置。

注意，枚举的两个字符必须都用了。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> we[200];
int n,ans=-1,now;
char a[1001000];
bool f1;
int main(){
	cin>>n;
	scanf("%s",a+1);
	for(int i=1;i<=n;i++)we[a[i]].push_back(i);//存位置
	for(char i='a';i<='z';i++){
		for(char j='a';j<='z';j++){
			if(!we[i].size()||!we[j].size())contninue;//玄学优化，必须有
			now=-1;
			f1=0;//初始化，f1表示前面有没有用过i
			if(i==j)continue;
			int k1=0,k2=0;
			while(k1<we[i].size() or k2<we[j].size()){//只要有一个没超限就继续
				int t1=(k1==we[i].size()?1e9:we[i][k1]);
				int t2=(k2==we[j].size()?1e9:we[j][k2]);//用了其他大佬的优美写法
				if(t1>t2){
					if(f1)now--;
					k2++;
					f1=1;
                }//如果t1远于t2，为了用上t1，必然要先用t2
    			if(t1<t2)now++,k1++;//反之，就可以直接选t1，愉快++
    			if(now<0)now=-1,f1=0;//如果小于0，那就不必选前面的了
    			ans=max(ans,now);//实时统计
			}//枚举
		}
	}
	cout<<max(ans,0);
}
```

---

## 作者：鱼跃于渊 (赞：0)

## 解法

我们设 $sum_{i,j}$ 为区间 $[1,i]$ 内字符 $j$ 出现的次数。  
考虑钦定 $x$ 为出现次数最多的字符，$y$ 为出现次数最少的字符。  
则区间 $[j,i]$ 的答案为：  

$$(sum_{i,x}-sum_{i,y})-(sum_{j-1,x}-sum_{j-1,y})$$  

固定 $i$，要想使上式最大，则后面的 $sum_{j-1,x}-sum_{j-1,y}$ 就要最小。  
我们枚举 $x,y$，扫一遍字符串，同时维护最小的 $sum_{j-1,x}-sum_{j-1,y}$。  
这样时间复杂度为 $O(n\lvert\Sigma\rvert^2)$，会 TLE。  

考虑优化，如果当前扫到了位置 $i$、字符 $x$，显然只有钦定 $x$ 为最多/少时的答案会发生改变。  
于是我们只需要枚举所有的 $y$，计算当前的答案，并维护最小的 $sum_{j-1,x}-sum_{j-1,y}$ 即可。  
这样时间复杂度为 $O(n\lvert\Sigma\rvert)$，可以通过此题。  

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fisher{
#define per(i,a,b) for(int i=(a);i<=(b);i++)
#define rep(i,b,a) for(int i=(b);i>=(a);i--)
const int N=1e6+5,S=26;
char s[N];
int n,ans,mn[S+5][S+5],sum[N][S+5];
#define calc(i,x,y) (sum[i][x]-sum[i][y])
void solve(int i,int x,int y){
    int j=mn[x][y];
    if((sum[i][x]-sum[j][x])&&(sum[i][y]-sum[j][y]))
        ans=max(ans,calc(i,x,y)-calc(j,x,y));
    if(calc(i-1,x,y)<calc(j,x,y))
        mn[x][y]=i-1;
}
void main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>(s+1);
    per(i,1,n){
        per(j,1,S) sum[i][j]=sum[i-1][j];
        int x=s[i]-'a'+1;
        sum[i][x]++;
        per(y,1,S) if(x!=y&&sum[i][y]){
            solve(i,x,y);
            solve(i,y,x);
        }
    }
    cout<<ans<<'\n';
}}
signed main(){
	fisher::main();
	return 0;
}
```

---

## 作者：_Flame_ (赞：0)

### $\text{solution}$

口胡一下。

考虑只有两种字母怎么做，可以钦定某一种为最大，dp 简单转移。

于是枚举两种字母，你会了 $O(26^2\times n)$ 成功了一半。

你可以发现对于每种钦定为最大的字母 $s$，你都只会在 $a_i=s$ 时转移，存下来只转移这些点，总的枚举次数为 $n$。

于是时间复杂度为 $O(26\times n)$，能过了。

枚举最多的，最少的字符 $x$ 和 $y$，转移大概是 $dp_i=\max(dp_{lst_i}+sumx_{i}-sumx_{lst_i}-sumy_{i}+sumy_{lst_i},1)$，其中 $lst_i$ 为上一个与 $a_i$ 相同的字符的位置，$sumx$ 和 $sumy$ 是 $x$ 和 $y$ 数量的前缀和，转移保证 $a_i=x$，对每一个 $x$ 分别做并取其中 $dp_i$ 的最大值。

细节比较多，要特判一下 $sumy_{i}-sumy_{lst_i}=0$ 等情况。

---

## 作者：Luciylove (赞：0)

考虑枚举最大的字母所处的位置 $i$ 作为端点和最小的字母 $j$。

然后就有记录一下前缀出现次数 $cnt$，枚举一个区间。

$$cnt_{i, ch_i} - cnt_{i, j} - (cnt_{i',ch_i} -cnt_{i', j})$$

求这个式子最大值。显然这两个式子相似，记录一下关于 $ch_i$ 的 $cnt$ 前缀最小值即可。

大概是 $O(26n)$ 的。

代码自己去贺题解区的，写的都比我好。

---

## 作者：离散小波变换° (赞：0)

## 题解

考虑枚举在最终选出的子段中，出现次数最少的字符为 $a$，出现次数最多的字符为 $b$。即使枚举到的字符不是实际出现最多/最少的，也没关系，因为我们总是能枚举到最多/最少的字符对，而不正确的枚举并不会导致实际不能取得的更优的答案，而是会被正确的字符对取代。

接着考虑把 $a$ 出现的位置的值看作 $-1$，$b$ 出现的位置看作 $+1$，其余字符均为 $0$。那么对于字符对 $\langle a,b\rangle$，我们要求出它的最大子段和。

这是一个经典问题。考虑从左往右依次枚举，用变量 $s$ 存储当前考虑到的最大子段和。每次 $s\gets \max(0,s+w_i)$。对于点对 $a,b$，它们的答案 $\mathrm{ans}_{a,b}$ 赋值为这些过程中最大的 $s$。

需要注意的是，最终选出来的子段里必须同时出现 $a,b$ 才行。在忽略这个条件的情况下，可能出现选出的子段里只有 $b$ 而没有 $a$ 的情形，那我们就随便选个 $a$ 进去，所以最后一步要 $\mathrm{ans}_{a,b}\gets \min(\mathrm{ans}_{a,b},\operatorname{count}(b)-1)$。

直接这样枚举 $a,b$，扫描一遍原数组做最大子段和的复杂度为 $\mathcal O(n|\Sigma|^2)$，考虑优化。

注意到 $a,b$ 以外的字符对应的权值均为 $0$，也就是说，这些字符压根不用考虑。所以我们预处理出 $a,b$ 出现的位置放到 $\text{vector}$ 里，每次做最大子段和的复杂度降为了 $\operatorname{count}(a)+\operatorname{count}(b)$。所以总复杂度为：

$$\begin{aligned}\sum_{a}\sum _b \operatorname{count}(a)+\operatorname{count}(b)&=2\sum _a \sum_b \operatorname{count}(a)\cr
&=2\sum _a \operatorname{count}(a)\sum _b 1\cr
&=\mathcal O(n |\Sigma|)
\end{aligned}$$

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l, r, i) for(int i = l, END##i = r;i <= END##i;++ i)
#define dn(r, l, i) for(int i = r, END##i = l;i >= END##i;-- i)
using namespace std;
typedef long long i64;
const int INF = 2147483647;
const int MAXN= 1e6 + 3;
const int MAXM=  26 + 3;
vector <int> P[MAXM]; char S[MAXN];
int qread(){
    int w = 1, c, ret;
    while((c = getchar()) >  '9' || c <  '0') w = (c == '-' ? -1 : 1); ret = c - '0';
    while((c = getchar()) >= '0' && c <= '9') ret = ret * 10 + c - '0';
    return ret * w;
}
int n, m = 26;
int main(){
    n = qread(); scanf("%s", S + 1);
    up(1, n, i){
        P[S[i] - 'a' + 1].push_back(i);
    }
    int ans = 0;
    up(1, m, a) if(P[a].size())
        up(1, m, b) if(a != b && P[b].size()){
            int p = 0, q = 0, s = 0;
            int ans0 = 0;
            while(p < P[a].size() && q < P[b].size()){
                if(P[a][p] < P[b][q]){
                    s = max(0, s - 1), ++ p;
                    ans0 = max(ans0, s);
                } else {
                    s = max(0, s + 1), ++ q;
                    ans0 = max(ans0, s);
                }
            }
            while(p < P[a].size()) s = max(0, s - 1), ++ p, ans0 = max(ans0, s);
            while(q < P[b].size()) s = max(0, s + 1), ++ q, ans0 = max(ans0, s);
            ans0 = min(ans0, (int)P[b].size() - 1);
            ans = max(ans, ans0);
        }
    printf("%d\n", ans);
    return 0;
}
```

---

