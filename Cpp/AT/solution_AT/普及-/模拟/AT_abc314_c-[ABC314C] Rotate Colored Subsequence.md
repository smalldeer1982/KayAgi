# [ABC314C] Rotate Colored Subsequence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc314/tasks/abc314_c

英小文字からなる長さ $ N $ の文字列 $ S $ が与えられます。 $ S $ の各文字は色 $ 1 $ 、色 $ 2 $ 、$ \ldots $ 、色 $ M $ の $ M $ 色のうちのいずれかで塗られており、 $ i\ =\ 1,\ 2,\ \ldots,\ N $ について、$ S $ の $ i $ 文字目は色 $ C_i $ で塗られています。

各 $ i\ =\ 1,\ 2,\ \ldots,\ M $ について、この順番に下記の操作を行います。

- $ S $ の色 $ i $ で塗られた文字からなる部分を、右に $ 1 $ つ巡回シフトする。 すなわち、$ S $ の 色 $ i $ で塗られた文字の位置が先頭のものから順に $ p_1,\ p_2,\ p_3,\ \ldots,\ p_k $ 文字目であるとき、 $ S $ の $ p_1,\ p_2,\ p_3,\ \ldots,\ p_k $ 文字目を、それぞれ、$ S $ の $ p_k,\ p_1,p_2,\ \ldots,\ p_{k-1} $ 文字目で同時に置き換える。

上記の操作をすべて行った後の、最終的な $ S $ を出力してください。

なお、$ M $ 色あるどの色についても、その色で塗られた $ S $ の文字が必ず $ 1 $ つ以上存在することが、制約として保証されます。

## 说明/提示

### 制約

- $ 1\ \leq\ M\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ C_i\ \leq\ M $
- $ N,\ M,\ C_i $ はすべて整数
- $ S $ は英小文字からなる長さ $ N $ の文字列
- 任意の整数 $ 1\ \leq\ i\ \leq\ M $ に対して、ある整数 $ 1\ \leq\ j\ \leq\ N $ が存在して $ C_j\ =\ i $ が成り立つ

### Sample Explanation 1

はじめ、$ S\ = $ `apzbqrcs` です。 - $ i\ =\ 1 $ に対する操作では、$ S $ の $ 1,\ 4,\ 7 $ 文字目からなる部分を右に $ 1 $ つ巡回シフトします。その結果、$ S\ = $ `cpzaqrbs` となります。 - $ i\ =\ 2 $ に対する操作では、$ S $ の $ 2,\ 5,\ 6,\ 8 $ 文字目からなる部分を右に $ 1 $ つ巡回シフトします。その結果、$ S\ = $ `cszapqbr` となります。 - $ i\ =\ 3 $ に対する操作では、$ S $ の $ 3 $ 文字目からなる部分を右に $ 1 $ つ巡回シフトします。その結果、$ S\ = $ `cszapqbr` となります（操作の前後で $ S $ は変わりません）。 よって、最終的な $ S $ である `cszapqbr` を出力します。

## 样例 #1

### 输入

```
8 3
apzbqrcs
1 2 3 1 2 2 1 2```

### 输出

```
cszapqbr```

## 样例 #2

### 输入

```
2 1
aa
1 1```

### 输出

```
aa```

# 题解

## 作者：AC_love (赞：3)

题意：给定一个长度为 $N$ 的字符串 $S$，每个字母有一个对应的颜色 $C_i$，每次操作针对一种颜色，将这种涂有这种颜色的字母 $p_1 , p_2 , p_3 … p_k$ 全部右移到下一个涂有这个颜色的位置，特别地，$p_k$ 位的字符会移动到 $p_1$ 位置，所以进行操作之后这个序列变成了 $p_k , p_1, p_2 , … p_{k - 1}$。

看起来可能不太好理解，我们结合样例看一看

```
a p z b q r c s
1 2 3 1 2 2 1 2
```

首先我们执行第一次操作，将颜色为 $1$ 的全部右移，序列变成：

```
c p z a q r b s
1 2 3 1 2 2 1 2
```

然后我们进行第二次操作：

```
c s z a p r b q
1 2 3 1 2 2 1 2
```

最后是第三次操作：

```
c s z a p r b q
1 2 3 1 2 2 1 2
```

所以最终得到的字符串是：

```
cszapqbr
```

------------

讲完题意，咱来理一理思路：

不难发现，每个字符都会且只会被执行一次右移操作，因此我们只需要记录每个位置的字符是从哪里转移来的就可以。

我们不难发现，答案字符串中某种颜色的 $p_i$ 位的字符，一定会来自原字符串这种颜色的 $p_{i-1}$ 位，特别地，如果 $i=1$，那么这个字符应该来自第 $p_k$ 位。

因此问题转换成了：寻找每个字符前面第一个和这个字符颜色相同的字符。

显而易见，我们能想到一种暴力写法：

```cpp
	for(int i = 1; i <= n; i = i + 1)
	{
		cin >> c[i];
		for(int j = i - 1; j >= 1; j = j - 1)
			if(c[i] == c[j])
			{
				lst[i] = j;
				break;
			}
	}
```

显然，这种暴力的复杂度为 $O(n^2)$，此题 $n \le 2 \times 10^5$，双重循环大概率跑不满，在 $2s$ 的时限下卡卡常写点极端情况的特判有希望艹过去。

但是在本题数据下，这种做法的时间复杂度显然是错误的，我们考虑一下能不能更优的算法。

暴力的复杂度之所以是 $O(n^2)$，主要原因是每次我们读入一个新数据都要从后往前重新扫一遍，那我们能不能不扫一遍直接得出答案呢？

当然是可以的。

我们可以开一个桶数组来记录每个颜色最后一次出现的位置，当读入一个颜色的时候只需要访问这个桶数组找到这种颜色上次出现的位置并赋值一下就行了，最后别忘了更新桶数组，把这个颜色最后一次出现的位置更新为当前位置。

代码实现如下：

```cpp
	for(int i = 1; i <= n; i = i + 1)
	{
		cin >> c[i];
		if(tong[c[i]] != 0)
			lst[i] = tong[c[i]];
		tong[c[i]] = i;
	}
```

然而这时我们注意到，每个颜色的第一项还没有与最后一项相匹配。

不过不用担心，我们的桶数组都已经更新好了，只要跑一遍的时候更新进去就行。

完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
char ch[214514];	// ch 数组记录读入的字符串 
char ans[214514];	// ans 为答案的字符串 
int c[214514];		// c 记录每个位置的颜色 
int lst[214514];	// lst 数组记录每个字符上一个与它颜色相同的字符的位置 
int tong[214514];	// 存储每个颜色最后一次出现的位置 
int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i = i + 1)
		cin >> ch[i];
	for(int i = 1; i <= n; i = i + 1)
	{
		cin >> c[i];
		if(tong[c[i]] != 0)
			lst[i] = tong[c[i]];
		tong[c[i]] = i;
	}
	for(int i = 1; i <= n; i = i + 1)
	{
		if(lst[i] == 0)
			// 如果这个位置我们没有记录过，那么我们就把桶里的元素更新给它 
			lst[i] = tong[c[i]];
		ans[i] = ch[lst[i]];
	}
	for(int i = 1; i <= n; i = i + 1)
		cout << ans[i];
	return 0;
}
// 洛谷提交 UKE，在 AtCoder 上提交 AC
```

完美 ~ 撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：Failure_Terminator (赞：2)

## Solution

考虑将每个颜色的位置编号存到一个对应的 `vector` 里。

然后遍历每种颜色，对其进行操作。

时间复杂度 $\Theta(n)$。

注意的是操作时要先保存最后一个编号上对应的数并逆序操作，否则将导致元素被覆盖。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int now=0,nev=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')nev=-1;c=getchar();}
	while(c>='0'&&c<='9'){now=(now<<1)+(now<<3)+(c&15);c=getchar(); }
	return now*nev;
}

const int N = 2e5 + 5;
vector<int> g[N];
int a[N], n, m;
string s;

signed main()
{
	n = read(), m = read();
	cin >> s;
	s += s[s.size() - 1];
	for (int i = s.size() - 1; i >= 1; i --)
		s[i] = s[i - 1];
	for (int i = 1; i <= n; i ++) a[i] = read();
	for (int i = 1; i <= n; i ++)
		g[a[i]].push_back(i);
	for (int i = 1; i <= m; i ++)
		if (g[i].size()){
			char p = s[g[i][g[i].size() - 1]];
			for (int j = g[i].size() - 2; j >= 0; j --)
				s[g[i][j + 1]] = s[g[i][j]];
			s[g[i][0]] = p;
		} 
	for (int i = 1; i <= n; i ++) cout << s[i];
    	return 0;
}
```

---

## 作者：LegendaryGrandmaster (赞：1)

**注：将下方的数字用权值表示。**

由于所有字符要移动至与其权值相同的下一个位子上，所以对应位置上应存放上一个与其权值相同的字符。

但是对于 $m$ 个权值而言，每个权值对应的最后一次出现的字符应移动到每个权值对应的第一次出现的字符的位置，则每个权值第一次出现的字符的位置应存放与其相同权值的最后一个字符。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200001];
map<int,int>mp,id;//mp 代表与其权值相同的上一个字符，id 表示位置。
int main()
{
	int n,m;
	cin>>n>>m;
	string st;
	cin>>st;
	st=' '+st;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		mp[i]=id[a[i]];
		id[a[i]]=i;
	}
	for(int i=1;i<=n;i++)cout<<st[(!mp[i]?id[a[i]]:mp[i])];
}
```

---

## 作者：tbdsh (赞：1)

# 题意简述
[更好的阅读体验](https://www.luogu.com.cn/blog/tianbiandeshenghuo11/solution-at-abc314-c)

[AtCoder 原题面](https://atcoder.jp/contests/314/tasks/abc314_c)

[洛谷原题面](https://www.luogu.com.cn/problem/at_abc314_c)

给定长度为 $N$ 的小写英文字母字符串 $S$。$S$ 中的每个字符被染了 $M$ 种颜色之一，颜色编号为 $1 \sim M$，第 $i$ 个字符染了颜色 $C_i$。

对于 $i = 1,2,\dots, M$，按如下操作：对颜色为 $i$ 的所有字符循环右移一位。

请你求出最终的 $S$。数据保证每种颜色至少有一个字符。
# 分析
这题我觉得是比较简单的。

读入每个颜色，用 `std::vector` 存储每个颜色对应的下表。

因为保证每种颜色至少有一个字符，所以不用考虑 `std::vector` 为空的情况。

然后对于每个颜色扫一遍 `std::vector`，变换即可。

时间复杂度：$O(N)$。

空间复杂度：$O(N)$。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int n, m, a[MAXN];
string s;
vector<int> b[MAXN];
int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  cin >> s;
  s = ' ' + s;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
    b[a[i]].push_back(i);
  }
  for (int i = 1; i <= m; i++){
    char p = s[b[i][b[i].size() - 1]];
    for (int j = b[i].size() - 1; j >= 1; j--){
      s[b[i][j]] = s[b[i][j - 1]];
    }
    s[b[i][0]] = p;
  }
  cout << s;
  return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**翻译**

给定一个 $n$ 个字符的字符串 $S$，对于每一个 $S_i$ 都有一个颜色 $c_i$，你需要对于每一种颜色，把该颜色的字符串“推进”一位，也就是说，设 $S_{a_1},S_{a_2},S_{a_3},\dots,S_{a_k}$ 都是同一个颜色的，$S_{a_1}\leftarrow S_{a_2},S_{a_2}\leftarrow S_{a_3},\dots,S_{a_{n-1}}\leftarrow S_{a_n},S_{a_n}\leftarrow S_{a_1}$。求最后的字符串。

**分析**

同学都是用的 vector，但对 STL 一窍不通的我在这里给大家介绍一种不用 STL 的做法。先思考暴力怎么做，就是对每一个 $i$，枚举它后面与它颜色相同且没有被标记过的 $j$，“推进”一位，并标记 $j$。显然最坏时有 $O(n^2)$。但是假如我们能“预知”下一次哪一个字符颜色相同，那就可以实现线性。

那么我们定义数组 $nxt$，其中 $nxt_i$ 表示 $i$ 的下一个与 $i$ 颜色相同的字符的下标 $j$，特别地，假如 $i$ 后没有这样的 $j$，$nxt_i=0$。为了维护 $nxt$ 数组，我们还需要一个 $last$ 数组，记录上一个与 $i$ 颜色相同的字符的下标，每次执行 `nxt[last[i]]=i` 再更新 $last$ 就做完了。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt[int(2e5+10)],c[int(2e5+10)],n,m,last[int(2e5+10)],nxt[int(2e5+10)];
string s;
void shift(int col,int i)
{
	char lastchar=' ';
	for(int j=i;j;j=nxt[j]) if(c[j]==col)//推进
	{
		vis[j]=1;
		swap(lastchar,s[j]);
	}
	s[i]=lastchar;
}
int main()
{
	cin>>n>>m>>s;
	s=' '+s;
	for(int i=1;i<=n;i++)
	{
		cin>>c[i];
		cnt[c[i]]++;
		nxt[last[c[i]]]=i;//更新nxt
		last[c[i]]=i;//更新last
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i]) continue;//访问过
		shift(c[i],i);//推进
	}
	for(int i=1;i<s.size();i++) cout<<s[i];
	return 0;
}

---

