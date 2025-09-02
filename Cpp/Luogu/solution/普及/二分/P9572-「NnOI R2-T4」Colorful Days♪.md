# 「NnOI R2-T4」Colorful Days♪

## 题目描述

给出如下定义：

1. 定义 $ AB $ 为 $ A $ 数组后拼接 $ B $ 数组。
2. 定义 $ A^{0}=\{\} $（即空数组），且对 $i=1,2,3,\cdots$，$ A^{i}=A^{i-1}A$。
2. 定义 $ \operatorname{LCS}(A,B) $ 为 $ A $ 数组和 $ B $ 数组的**最长公共子序列**长度。

现给定长度为 $ n $ 的数组 $ S $ 和长度为 $ m $ 的数组 $ T $，数组中的数均为正整数。

你现在需要找到最小的非负整数 $k$，使得 $ \operatorname{LCS}(S^k,T) $ 最大。

出题人很仁慈，如果你无法最小化 $k$，你也可以拿到一部分分数。

## 说明/提示

**【样例 1 解释】**

当 $k = 2$ 时，$S^k = \text{\{23 34 \textcolor{red}{53 23 34} 53\}}$，其中标红的是 $S^k$ 和 $T$ 的最长公共子序列。

**【数据范围】**

**提示：本题开启捆绑测试。**

对于 $ 100\% $ 的数据，保证 $ 1 \le n,m,S_i,T_i \le 10^6 $，$ c_1,c_2 \in \{0,1\} $。

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c}
\textbf{Subtask} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1& c_1=c_2=0 & 2 \r
\textsf2& n \le 10^3，m \le 10^2 & 8 \r
\textsf3& n \le 10^4，m \le 10^3 & 15 \r
\textsf4& c_2=0 & 15 \r
\textsf5& n,m \le 10^5，S_i,T_i \le 26 & 20 \r
\textsf6& 无特殊限制 & 40 \r
\end{array}
$$

在赛后新添加的 hack 测试点会加入 subtask7。

### 题目来源

| 项目 | 人员 |
|:-:|:-:|
|idea| 船酱魔王 |
|data| 船酱魔王 |
|check| Sudohry |
|solution| 船酱魔王 |

## 样例 #1

### 输入

```
3 4 1 1
23 34 53
53 25 23 34```

### 输出

```
3 2```

## 样例 #2

### 输入

```
9 10 1 1
15 12 26 21 26 21 23 12 23
26 11 21 15 16 15 12 23 17 12```

### 输出

```
7 3```

# 题解

## 作者：船酱魔王 (赞：18)

# Colorful Days♪ 官方题解

## 题意回顾

给定长度为 $ n $ 的数组 $ S $ 和长度为 $ m $ 的数组 $ T $。

定义 $ AB $ 为 $ A $ 数组后拼接 $ B $ 数组，定义 $ A^{0}=\{\} $（即空数组），$\forall i \in \mathbb{N^+}$ ，有 $ A^{i}=A^{i-1}A $。

定义 $ \operatorname{LCS}(A,B) $ 为 $ A $ 数组和 $ B $ 数组的最长公共子序列长度。

求出 $ i \in \mathbb{N} $ 使得 $ \operatorname{LCS}(S^i,T) $ 取到最大，**在此基础上** $ i $ 最小，并按照规定要求输出。

$ 1 \le n \le 10^6 $，$ 1 \le m \le 10^6 $，$ 1 \le S_i,T_i \le 10^6 $。

## 分析

输出 ```0 0``` 可得 2 分。

解决第一问（即 sub4）可再得 15 分，先考虑第一问解法，即不择手段地构造最长 $ \operatorname{LCS} $。

可以发现，当一个数不在 $ S $ 中出现，他一定不会存在在 $ \operatorname{LCS} $ 中。

设有 $ m' $ 个 $ T $ 的位置使得该位置数字在 $ S $ 中出现，记为 $ T $ 的合法位置，则复制 $ S $，复制 $ m' $ 次。可以在每次 $ S $ 循环一遍时，第 $ i $ 次可以选出第 $ i $ 个 $ T $ 的合法位置。

因此，第一问答案即为 $ m' $。

我们记 $ T' $ 为将 $ T $ 中合法位置依次串联组成的新数组。

第二问即要求在 $ S $ 的不断重复中找到 $ T' $ 作为子序列。

可以贪心的按照 $ T' $ 中的数依次找，每次找到这个数在上一个数出现后第一次出现在 $ S $ 的不断循环中的位置。

每次暴力去找的时间复杂度最坏是 $ O(n) $ 的，因为捆绑了测试点且数据经过特殊构造只能拿到 sub2~3 的分数。因此考虑快速去找。

我们开辟动态数组 $ g $, $ g_i $ 表示数字 $ i $ 在 $ S $ 中的出现的所有位置。

维护变量 $ sc,pos $ 每次找一个位置之后的字符时只需要在新字符的数组中二分大于 $ pos $（当前位置）的出现位置，如果找不到将 $ sc $ 加一，$ pos $ 更新为新字符第一次的出现位置。

时间复杂度 $ O(m \log n) $。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 1e6 + 5;
int n, m, c1, c2;
int s[N];
int t[N];
vector<int> g[N];
int findx(int p, int val) {
	int l, r, mid;
	l = -1;
	r = g[p].size();
	while(l + 1 < r) {
		mid = (l + r) >> 1;
		if(g[p][mid] > val) {
			r = mid;
		} else {
			l = mid;
		}
	}
	return r;
}
bool vis[N];
int main() {
	scanf("%d%d%d%d", &n, &m, &c1, &c2);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &s[i]);
		vis[s[i]] = 1;
	}
	for(int i = 1; i <= m; i++) {
		scanf("%d", &t[i]);
	}
	for(int i = 1; i <= m; i++) {
		if(!vis[t[i]]) {
			t[i] = -1;
		}
	} 
	int m1 = m;
	m = 0;
	for(int i = 1; i <= m1; i++) {
		if(t[i] != -1) {
			m++;
			t[m] = t[i];
		}
	}
	if(m == 0) {
		printf("0 0\n");
		return 0;
	}
	for(int i = 1; i <= n; i++) {
		g[s[i]].push_back(i);
	}
	int sc = 1;
	int pos = g[t[1]][0];
	for(int i = 2; i <= m; i++) {
		pos = findx(t[i], pos);
		if(pos == g[t[i]].size()) {
			pos = g[t[i]][0];
			sc++;
		} else {
			pos = g[t[i]][pos];
		}
	}
	printf("%d %d\n", m * c1, sc * c2);
	return 0;
}
```

## 总结与评价

本题用到的算法较为基础，但是考察选手的思维能力。

个人认为下位绿。

---

## 作者：Jorisy (赞：10)

赛时口胡的竟然过了。

首先考虑到，在 $S$ 中没出现的 $T_i$ 必然不会对 $\operatorname{LCS}(S^k,T)$ 产生贡献。因此直接删去变成新的 $T'$。显然，$\max\{\operatorname{LCS}(S^k,T')\}=|T'|$。第一问做完了。

然后转向第二问。

考虑记录 $T$ 的每个数 $T_i$ 在 $S$ 中出现的位置，然后我们将 $T_i$ 映射到 $T_i$ 在 $S$ 中的编号 $P_i$。这里我们为了 $k$ 尽可能小，就要尽可能使得 $P_i>P_{i-1}(i>1)$ 且 $P_i$ 尽可能小。如果不行，那我们只能开启新的 $S$（即 $k$ 加一）再次贪心。

时间复杂度 $O(m\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int>v[1000005];
int n,m,p,c1,c2,a[1000005],b[1000005],ans;

int main()
{
	scanf("%d%d%d%d",&n,&m,&c1,&c2);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		v[a[i]].push_back(i);//记录每个数对应的所有编号
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);
		if(v[b[i]].size()) b[++p]=b[i];
	}
	m=p;
	printf("%d ",p*c1);
	int lst=0;
	for(int i=1;i<=m;i++)
	{
		auto t=lower_bound(v[b[i]].begin(),v[b[i]].end(),lst+1);//贪心选择比其大的当中编号尽可能小的
		if(t==v[b[i]].end())//找不到
		{
			ans++;
			lst=*v[b[i]].begin();
		}
		else lst=*t;
	}
	cout<<++ans*c2;
	return 0;
}
```

---

## 作者：COsm0s (赞：5)

## $\mathcal{Solution}$

我们将本题拆成两个部分。

+ 考虑 $LCS(S^k,T)$。由于序列是无限复制的形式，所以只要 $\exists S_j=T_i$，那么 $T_i$ 就是最长公共子序列的一个元素。 所以第一问即为 $\sum\limits^{m}_{i=1}(\exists S_j=T_i)$。

+ 考虑 $k_{min}$。我们的贪心很简单，就是**能不要进入 $S^{k+1}$ 就不进入**。那么寻找这个最近位置即可。但是由于暴力是 $\Theta(n)$ 的，所以我们要把位置提前存起来，注意将 $S$ 序列复制一遍，为了需要 $k+1$ 的情况。然后二分 $lst$ 最近出现的位置，如果 $>n$，那么 $k$ 加一。

总复杂度 $\Theta(n\log n)$。

实现时注意初始 $lst$ 的位置。

## $\mathcal{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 5, inf = 2e5;
int s[N], t[N], LCS, sum;
vector<int> cnt[N];
int n, m, c1, c2;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m >> c1 >> c2;
	for (int i = 1; i <= n; i ++) cin >> s[i], cnt[s[i]].push_back(i), s[i + n] = s[i];
	for (int i = 1; i <= n; i ++) cnt[s[i]].push_back(i + n);
	for (int i = 1; i <= m; i ++) cin >> t[i];
	int lst = n, flag = 1;
	for (int i = 1; i <= m; i ++) {
		if (!cnt[t[i]].size()) continue;
		sum ++;
		int k = upper_bound(cnt[t[i]].begin(), cnt[t[i]].end(), lst) - cnt[t[i]].begin();
		lst = cnt[t[i]][k];
		if (cnt[t[i]][k] > n)  LCS ++, lst -= n;
	}
	cout << c1 * sum << ' ' << c2 * LCS << '\n';
	return 0;
}
```


---

## 作者：TanX_1e18 (赞：4)

## 题目大意：
有两个数组 $S$, $T$，你可以把 $S$ 进行复制并接到其后面形成 $S^k$，如 $S$=`123`,则 $S^2$=`123123`, $S^3$=`123123123`。  
让你求出 $S^k$ 与 $T$ 的最长公共子序列以及在最长公共子序列最长时$k$的最小值。  
首先思考如果无视 $k$ 最小的要求，最长公共子序列应该是多少。  
设 $T_i$ 表示 $T$ 的第 $i$ 个元素，  对于每个 $T_i$,如果 $S$ 中存在 $T_i$，则将其放入子序列中一定更优，如果 $S$ 中不存在 $T_i$，则 $T_i$ 一定不会在公共子序列中。  
所以对于 $S$ 和 $T$ 都只保留共有元素，则剩下的 $T$ 中每一个元素都应该在最长上升子序列中。  
于是可以得出最长上升子序列，只需将其放入 $S^k$ 即可。  
求 $k$ 的话可以对于每个元素，储存下它在 $S$ 中每次出现的位置接着遍历 $T$ 数组，用 $now$ 表示上一个数字在 $S$ 填的位置，于是只需找到这个元素最前面能填下的位置即可。  
如果这个元素不管怎么填都在 $now$ 后面，则向后面额外添加一个 $S$,并将其放在最先能放下的地方。  
查找可以放下的位置可以二分查找,总复杂度 $O(n\log n+m)$。
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
int s1[N];
int a[N],b[N];
int c[N],d[N];
int top1,top2;
int n,m,c1,c2;
vector<int> wei[N];
signed main()
{
	cin>>n>>m>>c1>>c2;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s1[a[i]]=1;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
		if(s1[b[i]])
		s1[b[i]]=2;
	}
	for(int i=1;i<=n;i++)
	{
		if(s1[a[i]]==2)
		{
			wei[a[i]].push_back(i);
		}
	}
	for(int i=1;i<=m;i++)
	{
		if(s1[b[i]]==2)
		d[++top2]=b[i];
	}
	int now=0,ans=1;
	for(int i=1;i<=top2;i++)
	{
		int nt=lower_bound(wei[d[i]].begin(),wei[d[i]].end(),now+1)-wei[d[i]].begin();
		if(now>=wei[d[i]][wei[d[i]].size()-1])
		{
			ans++;
			now=wei[d[i]][0];
		}
		else
		{
			now=wei[d[i]][nt];
		}
	}
	cout<<c1*top2<<' '<<c2*ans;
	return 0;
}
```

---

## 作者：翟翟 (赞：4)

首先一眼看出只要是 $S$ 和 $T$ 共有的元素必然可以为 $LCS(S^k,T)$ 中的元素（因为最坏情况下只要对于 $T$ 中的每个元素重复一遍 $S$ 即可），判断 $T$ 中元素是否存在于 $S$ 即可。

然后就是求最少重复次数，这可以用一个`vecter`存下 $S$ 中每个数出现的位置，再对于 $T$ 中的每一个元素求解。用 $lst$ 表示上一个数在 $S$ 中的位置，若无 $lst$ 后的相同元素，则计数器加 $1$；若有，用`upper_bound`查找出 $lst$ 后的相同元素。

## Code
```
#include<bits/stdc++.h>
namespace IO{
    static const int buf_size=1000000;
    static unsigned char buf[buf_size];
    static int buf_len,buf_pos;
    bool isEOF(){
        if(buf_pos==buf_len){
            buf_pos=0;
            buf_len=fread(buf,1,buf_size,stdin);
            if(buf_pos==buf_len)return 1;
        }
        return 0;
    }
    char gc(){
        return isEOF()?EOF:buf[buf_pos++];
    }
    template<typename T>
    void read(T&x){
        x=0;
        char c=gc();
        for(;c<48||c>57;c=gc());
        for(;c>=48&&c<=57;c=gc())
            x=(x<<1)+(x<<3)+(c^48);
    }
    template<typename T,typename...Ts>
    void read(T&x,Ts&...rest){
        read(x);
        read(rest...);
    }
}
using IO::read;
using namespace std;
const int N=1e6+1;
int n,m,c1,c2,a[N],b[N],ans,lst=2e6;
vector<int>v[N];
int main(){
	read(n,m,c1,c2);
	for(int i=1;i<=n;++i){
		read(a[i]);
		v[a[i]].push_back(i);//存进vector
	}
	for(int i=1;i<=m;++i){
		read(b[i]);
		if(v[b[i]].size())++ans;
	}
	printf("%d ",c1*ans);
	ans=0;
	for(int i=1;i<=m;++i){
		if(!v[b[i]].size())continue;
		if(v[b[i]][v[b[i]].size()-1]<=lst){//无lst后的相同元素
			++ans;
			lst=v[b[i]][0];
		}
		else{//二分查找
			lst=*upper_bound(v[b[i]].begin(),v[b[i]].end(),lst);
		}
	}
	printf("%d\n",c2*ans);
	return 0;
}
```

---

## 作者：Special_Tony (赞：3)

[题目传送门](/problem/P9572)
# 思路
这题中的第一问我们只要看 $T$ 中有几个数是在 $S$ 中出现过即可，因为 $k$ 可以无限扩大，这意味着 $S$ 中出现过的数的个数也可以无限扩大，这样 $T$ 中的在 $S$ 中出现过的数肯定都可以到最长公共子序列中去。

对于第二问，我们可以想到用贪心的思路去解决。所谓贪心，就是能不让 $k$ 变大就不变大。对于贪心，我们要做到以下两点：
1. 能不让 $k$ 变大就不变大；
1. 在做到第 $1$ 点的同时，我们要让这个位置在 $S$ 中尽可能靠前。

而让这个位置在 $S$ 中尽可能靠前，那可以把这个元素的所有位置都存在一个 STL_vector 里，并进行二分查找。二分查找也不用手写，有个叫 `upper_bound` 的库函数，它可以找到一个区间内第 $1$ 个比 $x$ 大的元素的地址，如果仍不理解，请看代码注释。
# 代码 
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, m, c1, c2, tot, last = 1919810, ans1, ans2, a[1000005], x;
vector <int> v[1000005]; //vector 可以动态调整空间！
int main () {
	cin >> n >> m >> c1 >> c2;
	if (! c1 && ! c2) { //如果你想写正解，这个 if 没啥用
		cout << "0 0";
		return 0;
	}
	for (int i = 0; i < n; ++ i)
		cin >> a[i], v[a[i]].push_back (i);
	while (m --) {
		cin >> x;
		if (v[x].empty ()) //在 S 中没有这个元素，说明不能被选到最长公共子序列中
			continue ;
		++ ans1; //统计第一问的答案
		if (v[x][v[x].size () - 1] <= last) //在这之后没有了，说明要新开一次数组
			++ ans2, last = v[x][0];
		else
			last = v[x][upper_bound (v[x].begin (), v[x].end (), last) - v[x].begin ()]; //在上一个之后的第 1 个比 last 大的元素位置
	}
	cout << c1 * ans1 << ' ' << c2 * ans2;
	return 0;
}
```

---

## 作者：ScottSuperb (赞：2)

## 解法分析
贪心。  
先看第一个子问题，因为数组 $S$ 可以无限复制，所以两数组共同出现的部分将组成最长公共子序列。再看第二个子问题，很容易就能想到按照 $T$ 的顺序匹配 $S$ 以最小化段数。那么开一个变量记录上次选到的是 $S$ 第几个数，二分查找此位置之后的下个所需数，如果没找到就新开段。
## 代码
读写函数定义已省略。
```cpp
#include <bits/stdc++.h>

using namespace std;
const int MXN = 1e6;
int n, m, c1, c2, len, cnt = 1;
vector<int> v[MXN + 5];

int main() {
  n = read(), m = read(), c1 = read(), c2 = read();
  for (int i = 1; i <= n; ++i) v[read()].push_back(i);
  for (int i = 1, b, last = 0, now; i <= m; ++i) {
    b = read();
    if (v[b].size()) {
      ++len;
      if (!c2) continue;
      auto it = upper_bound(v[b].begin(), v[b].end(), last);
      if (it == v[b].end())
        ++cnt, now = v[b][0];
      else
        now = *it;
      last = now;
    }
  }
  write(len * c1, ' '), write(cnt * c2 * (bool)len);
  fls();
  return 0;
}
```

---

## 作者：LCat90 (赞：2)

考场打了两个二分，改成一个就对了。

重要的事情说一遍：**子序列不用连续！**

首先思考询问 1：要使答案最大，我们肯定要尽可能使 $T$ 中的数被选，当且仅当 $S$ 中也存在这个数。所以记 $s_i,t_i$ 分别表示 $S,T$ 中数 $i$ 的个数，第一问的答案为 $\sum _ {i=1}^{10^6} [s_i,t_i>0]t_i$。

然后关键在于求出 $k$，我们考虑模拟整个过程。记录当前在 $S$ 中走到的位置 $i$，遍历最终的 $T$。往后走直到 $S_i=T_j$，此时将 $j\gets j+1$。如果 $i$ 回到了开头，那么 $k\gets k+1$。

但是上面那样做是暴力的，会 T。考虑优化。

在求符合条件的 $i$ 时，我们选择了暴力往下找。但我们其实可以记录下当前值 $x$ 对应在 $S$ 中有哪些位置，并且将这些位置从小到大排序。这样我们就可以二分去找这个值了。根据贪心，肯定是希望走得越近越好，所以我们二分大于当前位置 $i$ 的最小解；若没有，则走到 $i$ 前面的最左的位置，即这些位置中的第一位。
 
这样对于 $T$ 的每个位置，我们都能在 $O(\log n)$ 的时间里求出在 $S$ 中对应的位置，时间复杂度为 $O(m\log n)$。 

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, m, cnt, cnt2, p[N], q[N], c1, c2, a[N], d[N], b[N], c[N], ans, k;
bool vis[N];
int read() {
	char c; int sum = 0; while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') sum = (sum << 3) + (sum << 1) + (c ^ 48), c = getchar();
	return sum;	
} 
vector <int> G[N];
signed main() {
	cin >> n >> m >> c1 >> c2;
	for(int i = 1;i <= n; ++i) a[i] = read(),b[a[i]] ++;
	for(int i = 1;i <= m; ++i) d[i] = read(), c[d[i]] ++;
	for(int i = 1;i <= 1000000; ++i) 
		if(b[i] and c[i]) ans += c[i], vis[i] = 1;
	cout << c1 * ans << " ";
	if(c2 == 0) return cout << "0", 0;
	for(int i = 1;i <= m; ++i) if(vis[d[i]]) p[++cnt] = d[i];
	for(int i = 1;i <= n; ++i) 
		if(vis[a[i]]) {
			q[++cnt2] = a[i];
			G[a[i]].push_back(cnt2);
		}
	for(int i = 1;i <= 1000000; ++i) 
		if(G[i].size()) sort(G[i].begin(), G[i].end());
	if(cnt) k = 1;
 	for(int i = 0, j = 1;j <= cnt;) {
 		int l = 0, r = G[p[j]].size() - 1;
 		while(l < r) {
 			int mid = l + r >> 1;
 			if(G[p[j]][mid] > i) r = mid;
 			else l = mid + 1;
		}
		if(G[p[j]][l] > i) i = G[p[j]][l], j ++;
		else i = G[p[j]][0], j ++, k ++;
	}
	cout << c2 * k;
	return 0;
}
```

---

## 作者：聊机 (赞：2)

~~快抢题解~~

rank1 赛时只用了 4 分钟，而我做了将近 20 分钟才写完，失败。

赛时我把几乎每一部分部分分都写了。

首先是 $c2$ 为 $0$ 的部分，对于在 $T$ 中的数字，只要在 $S$ 出现过，就可以是最长公共子序列的一部分，所以 17 分拿下。

```cpp
for(int i=1;i<=n;i++) S[i]=qr(),vis[S[i]]=1;
for(int i=1;i<=m;i++) T[i]=qr();
for(int i=1;i<=m;i++)
	if(vis[T[i]]) ++cnt;
if(c2==0) {
	printf("%d %d",cnt*c1,0);
	return 0;
}
```

再看数据，有一部分 $n$，$m$ 很小，所以可以暴力枚举 $T$ 的每一个元素，然后在 $S$ 里面找，如果找不到就把 $k$ 加一，于是 40 分拿下。

```cpp
if(m<=10000) {
	int j=1,k=1;
	for(int i=1;i<=m;i++) {
		if(!vis[T[i]]) continue;
		while(j<=n&&S[j]!=T[i]) ++j;
		if(j==n+1) {
			j=1;++k;
			while(j<=n&&S[j]!=T[i]) ++j;
		}
	}
	printf("%d %d",cnt*c1,k*c2);
	return 0;
}
```

到这里就离正解不远了，我们发现每次我们只需要在 $S$ 中去寻找某一个值，那我们为何不预处理出来每一个值在 $S$ 里的位置呢？

具体的：对每一个值开一个动态数组，然后按顺序差入它的位置，这样在枚举 $T$ 中元素并寻找时可以直接二分查找出现的位置，100 分拿下。

```cpp
for(int i=1;i<=n;i++) S[i]=qr(),vis[S[i]]=1,p[S[i]].push_back(i);
for(int i=1;i<=m;i++) T[i]=qr();
    
int j=1,k=1;
for(int i=1;i<=m;i++) {
	if(!vis[T[i]]) continue;
	if(p[T[i]][p[T[i]].size()-1]<j) j=1,++k;
	vector<int>::iterator x=lower_bound(p[T[i]].begin(),p[T[i]].end(),j);
	j=*x+1; ++cnt;
}
printf("%d %d",cnt*c1,k*c2);
```

---

## 作者：玄学OIER荷蒻 (赞：1)

第一次打基础赛，感觉不错。

个人感觉难度作为 T4 来讲不大，本人花了 8 min 不到 AC。

而且值域 $10^6$ 感觉有点提示做法的感觉，~~真的不考虑开大值域加个离散化吗~~。补充：出题人在讨论区说了离散化超纲，不过还是说说离散化做法。

首先 $S^k$ 是 $k$ 个 $S$ 拼接而成，所以贪心考虑，先不想最小 $k$ 的事情，至少说我们拼 $m$ 个 $S$ 必定是可以的，而第一问的答案就是 $T$ 数组中在 $S$ 数组里的数的个数。

接下来继续考虑 $k$ 最小是多少。

继续贪心，开两个变量，`nwk` 代表现在已经拼接了的次数，和 `nwi` 代表现在的坐标。

对于每一个 $T$ 中的元素，如果在 $S$ 里出现，那么找到 `nwi` 之后的第一个这个元素的位置，并把 `nwi` 改成这个位置，如果找不到，代表这个元素在其前面，我们将 `nwk` 增加，再将 `nwi` 变成这个元素在 $S$ 里第一次出现的位置即可。最后的 `nwk` 就是答案。

问题来了？如何维护某个数在某个位置之后第一次出现的位置？

可以提前预处理，复杂度 $O(nV)$（$V$ 是 $\max{(\max^{i=n}_{i=1}S_i,\max^{i=m}_{i=1}T_i)}$），可以拿到 $V$ 很小的 $20$ 分。

不过看起来...某个位置之后第一个，这不是很像二分吗？

考虑用邻接表记录每一种元素在 $S$ 中出现的所有位置，查询时二分即可。

预处理是 $O(n)$，每次查询复杂度 $O(\log n)$，整体时间复杂度 $O(n+m \log n)$，空间复杂度 $O(n+V)$。

如果将 $V$ 增大到 $10^{18}$ 怎么办？内存会炸掉的）

考虑离散化，因为答案还有计算步骤与具体大小无影响，所以只要相同的数离散成相同的数，不同的数离散成不同的数即可。（事实上离散化是超纲内容）

$T$ 里的元素无需离散化，但是要查询其对应离散化后的数值，查到 $0$ 就是未出现在 $S$ 中，实现以上效果可以用 `map` 进行离散化。

最终时间复杂度 $O(n \log n + m\log n)$，空间复杂度 $O(n)$。

---

## 作者：One_JuRuo (赞：1)

## 思路

### Step0.骗分

显然，题目中的 $c_1,c_2$ 就是为了送分，如果比赛中没有思路，倒是可以直接输出两个 $0$ 先得到 $2$ 分，聊胜于无。

### Step1.暴力不出奇迹

显然第一个想到的是暴力，枚举 $k$，容易观察得出，若一次增加 $k$ 而 LCS 不变，则再增加 $k$ 也无用。可凭借这个结论暴力验证，然后得出答案。

但是非常显然，这样时间复杂度及其高，定然会 TLE。

### Step2.观察性质

我们发现，如果 $k$ 足够大，那么所有同时存在于数组 $S,T$ 的数字都可以贡献答案，所以最大的 $LCS$ 就是同时存在数组 $S,T$ 的个数。

### Step3.从模拟入手

想要直接找到最小 $k$ 不是一件简单的事情，不如逐步模拟。

因为我们在 Step2 中得出结论，只要是同时存在于数组 $S,T$ 的，都需要计算，所以我们可以遍历数组 $T$。

假设当前遍历到的数是 $x$。

如果 $x$ 不在数组 $S$ 中，则可以直接跳过，因为无论 $k$ 多大，也没有任何用处。

如果 $x$ 在数组 $S$ 中，那么就可以贡献答案，如果前一个可贡献答案的数在数组 $S$ 中的位置之后有 $x$ 的话，那么不需要增加 $k$，如果没有的话，则需要增加一次 $k$，用新增加的一段中的 $x$ 满足要求。

这样就完美地解决了 $k$ 的问题。

### Step4.代码写法

可以用 vector 储存每个数字在数组 $S$ 中的位置。

用一个变量，储存上一个可贡献答案的数在数组 $S$ 中的位置。

我们就只需要遍历 vector，找到位置之后的满足条件的坐标，如果找不到，就增加 $k$，并把变量赋值为该数字第一次出现的位置。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,c1,c2,s[1000005],t[1000005],res,k=1,p,cnt;
vector<int>v[1000005];
int main()
{
	scanf("%d%d%d%d",&n,&m,&c1,&c2);
	for(int i=1;i<=n;++i) scanf("%d",&s[i]),v[s[i]].push_back(i);
	for(int i=1;i<=m;++i) scanf("%d",&t[i]);
	for(int i=1;i<=m;++i)
	{
		if(!v[t[i]].size()) continue;//如果在S中不存在就直接跳过
		else
		{
			int flag=0;res++;//用flag标记是否找到位置
			for(int j=0;j<v[t[i]].size();++j) if(v[t[i]][j]>p){flag=1,p=v[t[i]][j];break;}//找到第一个大于p的位置
			if(!flag) k++,p=v[t[i]][0];//没找到就需要增加k了，记得赋值
		}
	}
	printf("%d %d",res*c1,k*c2);//别忘了乘以c1,c2
	return 0;
}
```

### 题外话

这个代码其实有个小问题，如果 LCS 为 $0$，那么非负整数 $k$ 的最小值应该是 $0$。只不过因为太细节，加了可能会影响公平性，所以没加。

改代码也很简单，只需要判断 $res$ 是不是 $0$ 就好。~~这里不改是看看到时候会不会有人直接复制交（滑稽）。~~

### Step5.进一步的优化

原本交了，但是被巨佬同学说了，我这个复杂度过了是因为数据水，所以我有屁颠屁颠地跑回来修改了。

显然如果数据构造合适，在查找位置的时候会被卡，所以考虑在查找优化时间复杂度，第一时间就想到是二分。~~绝对不是看到标签里有二分。~~

这样的话就容易了，只需要再写个二分查找就好了。

仅贴出部分代码（二分查找函数和调用部分的循环代码）

```cpp
int find(int i,int x)
{
	int l=0,r=v[i].size()-1,mid,ans=-1;
	while(l<=r)
	{
		mid=l+r>>1;
		if(v[i][mid]>x) r=mid-1,ans=v[i][mid];
		else l=mid+1;
	}
	return ans;
}
/////////////
for(int i=1;i<=m;++i)
{
	if(!v[t[i]].size()) continue;
	else
	{
		int l=find(t[i],p);res++;
		if(l==-1) k++,p=v[t[i]][0];
		else p=l;
	}
}
```

---

## 作者：Eltaos_xingyu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9572)

~~(姐姐砍我！)~~

令两个指针 $ si $ 与 $ ti $，分别指向 $ s $ 数组与 $ t $ 数组中的一个元素，他们的初始值均为 $ 1 $。

首先统计 $ s $ 数组中所有数的下标：

```cpp
cin>>n>>m>>c1>>c2;
for(int i=1;i<=n;i++){
	cin>>s[i];
	v[s[i]].push_back(i);
}
```

对，要开 $ 10^6 $ 个 vector。并且我们能保证每个 $ v[i] $ 存的下标是单调递增的。

然后，对于每一个 $ ti $，先判断 $ v[t[ti]] $ 是否为空，即判断 $ t[ti]] $ 是否在 $ s $ 数组中出现过，如果没有就直接 `ti++` 就行了。

如果有，就在 $ v[t[ti]] $ 中用 `lower_bound` 查找第一个 $ c $ 使 $ s[c]=t[ti] $。如果返回值为 `v[t[ti]].end()`，那么没有查到任何一个 $ c \leq si $，需要再拼一个 $ s $ 数组，即 `k++`，并且将 $ si $ 指向 $ s $ 数组内第一个等于 $ t[ti] $ 的数的下一个数，以便 `lower_bound` 正常运行。如果正常返回，那么直接把 $ si $ 指向查找结果的下一个就行了。对于上面两种情况，最长公共子序列的长度都要加 $ 1 $。

什么？你说你不知道什么是 `lower_bound`？这个函数返回的是一个升序区间内第一个大于等于参数值的指针，这你懂了吧？

指针 $ ti $ 最多遍历 $ m $ 次，`lower_bound` 的时间复杂度最坏为 $ O(\log n) $，故总时间复杂度为 $ O(m\log n) $。

下面是 AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int si,ti,c1,c2,t[10000001],s[10000001],k=1,cnt=0;
vector<int> v[1000001];
vector<int>::iterator it;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m>>c1>>c2;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		v[s[i]].push_back(i);
	}
	for(int i=1;i<=m;i++){
		cin>>t[i];
	}
	ti=1;
	si=1;
	while(1){
		while(v[t[ti]].empty()&&ti<=m)ti++;
		if(ti>m)break;
		cnt++;
		it=lower_bound(v[t[ti]].begin(),v[t[ti]].end(),si);
		if(it==v[t[ti]].end()){
			k++;
			si=*v[t[ti]].begin()+1;
		}
		else{
			si=*it+1;
		}
		ti++;
	}
	cout<<c1*cnt<<" "<<c2*k;
}
```


---

## 作者：lraM41 (赞：1)

~~赛场上看到T3是数学就弃了（哭。~~

~~开始打纯暴力，又红又紫又黑。~~

因为数组 $A$ 可以复制无数遍，很容易想到答案就是 $B$ 中在 $A$ 中出现过的数的个数。由于下标单调递增，考虑二分。

对于这题我的做法：对于每个数 $a$ 记录下它的下标（存在 vector 里），并且可以靠它来计算答案。接着记录下所有 $B$ 在 $A$ 中出现过的数（按输入顺序），对于这些数在 vector 的下标中二分，如果上一个数的下标在不大于该数的最后一个下标，便返回离上个下标最近的该数的下标，并且更新上一个下标， $k$ 加一。具体还是看代码吧qwq。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int k,t,l,c1,c2;
int n,m,s,p[1000005],a[1000005],c,b[10000005];
vector<int> v[1000005];
signed main()
{
   cin>>n>>m>>c1>>c2;
   for(int i=1;i<=n;i++)
      cin>>a[i],p[a[i]]=1,v[a[i]].push_back(i);//记录下标。
   for(int i=1;i<=m;i++){
      cin>>c;
      if(p[c]) b[++s]=c;//记录 b 中 a 出现过的数。
   }
   if(!c1&&!c2) puts("0 0"),exit(0);//特判，下同。
   if(!c2)cout<<s<<" 0",exit(0);
    for(int i=1;i<=s;i++){
        k=upper_bound(v[b[i]].begin(),v[b[i]].end(),t)-v[b[i]].begin();//二分。
        if(k>=v[b[i]].size()) t=v[b[i]][0],l++;//没找到符合条件的下标，更新上一个下标， k 加一。
        else t=v[b[i]][k];//符合条件，更新上一个下标。
    }cout<<s<<' '<<l+1;//由于不复制数组时 k 就是一，因此最后要加一。
   return 0;
}

---

## 作者：DengDuck (赞：1)

这题还是蛮有意思的，但是考时我被卡常了......加了一个快读就过了。

我们可以解决第一问先，首先 $T$ 不变，所以答案显然会是 $T$ 的一个子序列，我们只需要考虑 $T$ 的每个元素是否在 $\text{LCS}$ 中 即可。

进一步地，我们发现只要 $T_i\in S$，那么这个元素就可以算到 $\text{LCS}$ 中，这一点是显然的，在无限拓展的 $S$ 中，我们显然可以考虑克隆一次 $S$ 数组选择一项的方式，这样一定保证 $T_i\in S$ 的元素就可以算到 $\text{LCS}$ 中。

显然反之不可以，因为 $S$ 不能无中生有。

解决了第一问的同时我们处理出来 $\text{LCS}$ 本身，所以我们可以直接在无限拓展的 $S$ 中找到就可以了，此时 $S$ 拓展了多少遍也就求出来了。

但是真的无限拓展是不可能的，我们可以直接在 $S$ 上找，找不到就从头找，记录从头的次数，就是拓展的次数。

这里的求法可以对于每个值出现的位置建立多个 `set`，直接查找就相当于找当前位置在 `set` 中的后继。

时间复杂度分析一下，$\text{LCS}$ 大小不超过 $m$，所以是 $\mathcal O(m\log n)$，需要常数优化。

```cpp
#include<bits/stdc++.h>
#define LL int
using namespace std;
const LL N=1e6+5;
LL n,m,c1,c2,s[N],t[N],ans1,ans2,pos=0,ma[N],mx[N];
set<LL>S[N];
inline LL read() {
	char c = getchar();
	LL f = 1;
	LL sum = 0;
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') {
		f = -1;
		c = getchar();
	}
	do {
		sum = (sum << 3) + (sum << 1) + c - '0';
		c = getchar();
	} while (c >= '0' && c <= '9');
	return sum * f;
}
int main()
{
	n=read(),m=read(),c1=read(),c2=read();
	for(int i=1;i<=n;i++)
	{
		s[i]=read();
		ma[s[i]]++;
		S[s[i]].insert(i);
		mx[s[i]]=i;
	}
	for(int i=1;i<=m;i++)
	{
		t[i]=read();
		if(ma[t[i]])
		{
			ans1++;
			if(ans1==1)ans2++;
			while(1)
			{	
				
				if(mx[t[i]]<=pos)ans2++,pos=0;
				else 
				{
					pos=*S[t[i]].upper_bound(pos);
					break;
				}
			}
		}
	}
	printf("%d %d",c1*ans1,c2*ans2);
}
```

---

## 作者：SamHJD (赞：0)

## [P9572 「NnOI R2-T4」Colorful Days♪](https://www.luogu.com.cn/problem/P9572)

### 题目大意

定义 $s^k$ 为 $k$ 个数组 $s$ 首尾相接。求数组 $s^k$ 和数组 $t$ 的最长公共子序列和满足最长下最小的 $k$。

### 解法

题目中，$s$ 是可以变的，而 $t$ 不变。也就是说，最长公共子序列的长度最大值是确定的，也就是 $len_t$。对于每一个 $t_i$，只要它存在于 $s$，我们都可以通过复制一遍 $s$ 使它在最长公共子序列中出现。那么第一问就解决了，循环 $t$，只要 $t_i$ 存在于 $s$ 便将答案加一。

既然第一问是一个个找 $t_i$，我们想让复制的次数尽可能小，总不能每一个 $t_i$ 都复制一遍 $s$。

所以用一个记录枚举 $s$ 下标的变量，每次从这个下标开始在 $s$ 中找 $t_i$。每当这个变量从 $n$ 变到 $1$，意味着要复制一遍 $s$，将答案加一。

然而这是 $O(n^2)$ 的，考虑优化。

可不可以跳跃的找 $t_i$ 呢？不妨用 $\text{vector}$ 预处理每个 $t_i$ 在 $s$ 中的每一个位置，这样找 $t_i$ 时便可以遍历它每一个出现的位置，复杂度肯定降低不少。

再对这个过程优化，由于我们的预处理使得 $\text{vector}$ 中对于一个 $t_i$ 位置是连续的，考虑二分。二分至一个位置使得它在下标变量的右边并且距离它最近即可。

最终复杂度：$O(m\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int n,m,c1,c2,s[N],t[N];
int ans,ans1=1,it=0,mp[N];
vector<int> pos[N];
int main(){
    scanf("%d%d%d%d",&n,&m,&c1,&c2);
    for(int i=1;i<=n;++i){
        scanf("%d",&s[i]),mp[s[i]]=1;//标记出现
        pos[s[i]].push_back(i);//预处理位置
    }
    for(int i=1;i<=m;++i) scanf("%d",&t[i]);
    for(int i=1;i<=m;++i){
        if(!mp[t[i]]) continue;
        ans++;
        if(pos[t[i]][pos[t[i]].size()-1]<=it){//最后一个位置也比当前枚举s的下标小，意味着必须得复制
            it=pos[t[i]][0];//复制完距离it最近的就是第一个位置
            ans1++;
            continue;
        }
        int l=0,r=pos[t[i]].size()-1;//二分
        while(l<=r){
            int mid=(l+r)>>1;
            if(pos[t[i]][mid]>it) r=mid-1;
            else l=mid+1;
        }
        it=pos[t[i]][l];
    }
    printf("%d %d",c1*ans,c2*ans1);
    return 0;
}
```

---

## 作者：hh弟中弟 (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/P9572)

定义 $A^i=A^{i-1}A$ 其实就是 $i$ 个 $A$ 数组拼接在一起。所以对于 $k$ 我们需要求出最少几个 $S$ 拼接在一起能够与 $T$ 数组构成最长公共子序列，这里我们用一个 $cnt$ 来维护。

不难发现，$LCS(S^k,T)$ 最大时，就是 $T$ 与 $S$ 所有公共的元素都出现时。我们不妨用一个桶在输入时来记录 $S$ 中元素是否出现，再用另一个动态数组来记录这个数每次出现的位置。在输入 $T$ 时判断此数是否出现过即可，将他们存入一个 vector 中。

然后我们用 $pre$ 来记录当先元素的下标，去枚举第 $i$ 个公共元素，在它的数组中用 upper\_bound 去查询第一个大于 $pre$ 的位置，如果找不到就再增加一个 $S$，同时 $cnt$ 增加 $1$，用这个数组中第一个元素去更新 $pre$。知道我们将所有公共元素遍历完。

此时 $cnt\cdot c1$ 和 $ans\cdot c2$ 即为答案。

附代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N(1e6+5);
int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())if(ch=='-')f=-1;
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
void write(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+48);
}int s[N],t[N];
vector<int> v[N],z,b;bool pot[N];
int main(){
    z.push_back(1);
    int n=read(),m=read(),c1=read(),c2=read();int cnt=0;
    for(int i=1;i<=n;++i)s[i]=read(),pot[s[i]]=1,v[s[i]].push_back(i);
    for(int i=1;i<=m;++i){
        t[i]=read();
        if(pot[t[i]])z.push_back(t[i]),cnt++;
    }int pre=0,ans=1;
    for(int i=1;i<=cnt;++i){
        int k=upper_bound(v[z[i]].begin(),v[z[i]].end(),pre)-v[z[i]].begin();
        if(k==v[z[i]].size()) ++ans,pre=v[z[i]][0];
        else pre=v[z[i]][k];
    }
    cout<<cnt*c1<<' '<<ans*c2<<'\n';
    return 0;
}
```


---

## 作者：无钩七不改名 (赞：0)

显而易见，$\operatorname{LCS}(S^k,T)$ 的长度为 $T$ 中在 $S$ 中出现过的数字数。

那么我们可以直接贪心。记录每个数在 $S$ 中出现的位置，从小到大排序。对于每个 $T_i$，如果没有在 $S$ 中出现过，跳过。否则二分查找当前数在 $S$ 中第一个大于当前位置 $now$ 的数，并更新当前位置。如果没有，则增加使用的 $S$ 的数量 $k$，更新当前位置为 $T_i$ 在 $S$ 中第一次出现的位置。初始化 $k$ 为 $0$，$now$ 为 $n$。

### 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1000005;

int n,m,c1,c2;
int s[N],t[N];
int a[N];
vector<int> vc[N];
int lcs,k,nw;

int read(){
	int f=1,k=0;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	} 
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return f*k;
}

int main(){
	n=read();m=read();
	c1=read();c2=read();
	for(int i(1);i<=n;++i){
		s[i]=read();
		++a[s[i]];
		vc[s[i]].push_back(i);
	}lcs=m;nw=n;
	for(int i(1);i<=m;++i){
		t[i]=read();
		if(!a[t[i]])--lcs;
		else{
			if(vc[t[i]][a[t[i]]-1]<=nw){
				++k;nw=vc[t[i]][0];
			//	cout<<"*"<<vc[t[i]][a[t[i]-1]]<<'\n';
			}
			else nw=vc[t[i]][upper_bound(vc[t[i]].begin(),vc[t[i]].end(),nw)-vc[t[i]].begin()];
			//cout<<i<<" "<<nw<<'\n';
		}
	}
	printf("%d %d\n",c1*lcs,c2*k);
	return 0;
}
```


---

## 作者：Ryder00 (赞：0)

题意比较清楚，不再阐述。

以下简要称输入的两数组为 $A$ 数组和 $B$ 数组。

## 思路
考虑第一问如何作答。

观察到，LCS（最长公共子序列）中的元素，必须都出现在 $A$ 数组和 $B$ 数组中。所以，只在一个数组中出现过的元素，就一定不会在 LCS 中出现。我们可以先把这些元素去除掉，得到新的 $A$ 和 $B$。

由题意，$A$ 数组可以复制无限次。这说明，$A$ 一定可以通过复制操作，将 $B$ 中所有的元素全都囊括在内。故第一问的答案为 $B$ 与 $A$ 的共同元素个数。

考虑第二问。

为了方便，我们将两数组“离散化”。用样例 $2$ 举例子，此处的 $A$ 数组和 $B$ 数组都是经过第一问操作处理过的，看图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/3p7cn6vw.png)

处理完之后就好做了。我们发现，$B$ 数组一定会作为一个子序列出现在答案数组中 。所以对于 $A$ 数组中的每个元素，使用 vector 记录相同元素出现过的位置。枚举 $B$ 数组中的每个元素，维护元素当前对应到 $A$ 数组中的位置 $now$。使用 map 维护 $A$ 中出现过多次的元素的位置在 vector 中的对应下标。如果下标大于元素出现过的次数，或者当前枚举元素的位置对应到 $A$ 中小于 $now$，则说明可用元素都用完了，该复制这个数组了，答案加一。

使用 map 时要卡常数。

文字太抽象，建议看代码理解。

## Code
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define db double
#define mkp make_pair
#define pb push_back
#define P pair<int,int>
#define _ 0
const int N=1e6+10,mod=1e9+7,MOD=1e9+123,inf=1e18;
int T=1,n,m,c1,c2,a[N],b[N],ans1,vis[N],val[N],lst[N],c[N],vis2[N];
vector<int> vec[N];
unordered_map<int,int> mp;
void solve(){
    cin>>n>>m>>c1>>c2;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        vis[a[i]]=1;
    }
    int ans1=m,cnt=0;
    for(int i=1;i<=m;i++){
        cin>>b[i];
        if(!vis[b[i]]) {
            ans1--;
            continue;
        }
        cnt++;
        if(!vis2[b[i]]) lst[b[i]]=cnt,vis2[b[i]]=1;
        val[cnt]=lst[b[i]];
    }
    m=cnt,cnt=0;
    for(int i=1;i<=n;i++){
        if(lst[a[i]]){
            a[++cnt]=lst[a[i]];
        }
    }
    n=cnt;
    for(int i=1;i<=n;i++){
        vec[a[i]].pb(i);
    }
    int ans2=0,now=0;
    for(int i=1;i<=m;i++){
        if(mp[val[i]]>=(int)vec[val[i]].size()){
            ans2++,mp.clear(),now=0;
        }
        int &mpp=mp[val[i]];
        while(vec[val[i]][mpp]<now&&mpp<(int)vec[val[i]].size()) mpp++;
        if(mp[val[i]]>=(int)vec[val[i]].size()){
            ans2++,mp.clear(),now=vec[val[i]][mp[val[i]]],mp[val[i]]++;
        }
        else{
            if(vec[val[i]][mp[val[i]]]>now){
                now=vec[val[i]][mp[val[i]]];
                mp[val[i]]++;
            }
            else ans2++,mp.clear(),now=vec[val[i]][mp[val[i]]],mp[val[i]]++;
        }
    }
    cout<<c1*ans1<<" "<<c2*(ans2+1);
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    ios::sync_with_stdio(false),cin.tie(0);
    while(T--){
        solve();
    }
    return ~~(0^_^0);
}
```

好像代码也很丑陋呢。。

---

## 作者：251Sec (赞：0)

发现一个颜色在最终的 LCS 中，则它一定在 $S$ 和 $T$ 中都存在。并且 $k$ 足够大时 $\text{LCS}(S^k, T)$ 一定为 $T$ 中在 $S$ 中存在的颜色的出现次数之和。

不妨从左到右匹配 $T$ 中每个在 $S$ 中存在的颜色的元素，则在满足条件的情况下我们倾向于选择在 $S$ 中更靠左的位置匹配，且下次匹配位置要么在该位置的右侧，要么使得 $k$ 增加 $1$ 并从 $S$ 的开头开始重新匹配。

直接模拟该过程，我们需要维护「在某个位置右侧的最靠左的某种颜色」，直接对每种颜色开个 set / vector 然后二分查找即可。因为 set 常数巨大所以这里用的是 vector。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, c1, c2;
int s[1000005], t[1000005];
vector<int> app[1000005];
int ans1, ans2;
class IO {
    template <class T>
    void write(T a) {
        if (a > 9)
            write(a / 10);
        putchar(a % 10 + '0');
    }
public:
    template <class T>
    IO operator<<(T a) {
        if (a < 0) {
            putchar('-');
            a = -a;
        }
        write(a);
        return *this;
    }
    IO operator<<(char a) {
        putchar(a);
        return *this;
    }
    template <class T>
    IO operator>>(T &a) {
        int sign = 1;
        a = 0;
        char c = getchar();
        while (c < '0' || c > '9') {
            if (c == '-') {
                sign = -1;
            }
            c = getchar();
        }
        while (c >= '0' && c <= '9') {
            a = (a << 1) + (a << 3) + (c ^ 48);
            c = getchar();
        }
        a *= sign;
        return *this;
    }
} io;
int main() {
    io >> n >> m >> c1 >> c2;
    for (int i = 1; i <= n; i++) {
        io >> s[i];
        app[s[i]].emplace_back(i);
    }
    ans2 = 1;
    for (int i = 1, j = 0; i <= m; i++) {
        io >> t[i];
        if (app[t[i]].size()) {
            ans1++;
            auto it = lower_bound(app[t[i]].begin(), app[t[i]].end(), j + 1);
            if (it == app[t[i]].end()) {
                j = 0;
                ans2++;
                it = app[t[i]].begin();
            }
            j = *it;
        }
    }
    if (!ans1) ans2 = 0;
    io << ans1 * c1 << ' ' << ans2 * c2 << '\n';
    return 0;
}
```

---

## 作者：Mr_Biantainne (赞：0)

## 前言
第一次 AK Div3 比赛，写篇题解庆祝一下。
## 题意简述
有两个数组 $s$ 和 $t$，现在要选一个 $k$，将 $s$ 复制 $k$ 次（设结果为 $s'$），求使得 $t$ 与 $s'$ 的最长公共子序列最长的最小的 $k$。
## 题意分析
一开始我想的是动态规划来做，但看数据非常多，必然不对。

后来就想到有一个策略：因为要使最长公共子序列最长，所以 $t$ 里面的数只要 $s$ 里面有，那一定会加上去。
## 策略的证明
假设 $t$ 和 $s'$ 的最长公共子序列为 $a$，而且 $s$ 中有的元素没有在 $a$ 中存在，则必然可以将 $s'$ 增加一段，变为 $s' + s$，使得 $t$ 与 $s' + s$ 的最长公共子序列比 $a$ 长。
## 继续分析
有了这个策略就好做了。先把 $s$ 中所有的数字装入桶中。假设现在循环到 $i$，那么桶的下标是 $s_i$，装的内容是 $i$。

随后在 $t$ 中寻找。先要准备一个记录当前下标的 $idex$（即当前 $s'$ 的末尾元素下标），和一个记录最长公共子序列长度的 $ans$。

同样假设现在循环到 $i$：
- 如果桶里面没有 $t_i$，那就丢弃掉。
- 如果有 $t_i$，那就必然能够装进最长公共子序列中，因此把 $ans$ 增加 $1$，随后在桶中找到第一个 $> idex$ 的值，将 $idex$ 更新为它。如果找到末尾也没有 $> idex$ 的值，就需要新开一段，$s'$ 变为 $s' + s$，随后将 $idex$ 更新为桶中的第一个元素。
## 优化与提示
1. 可以发现，$s$ 和 $t$ 数组在计算完以后就不需要用了，因此不需要开数组。

2. 而且每个桶中的内容具有单调性，因此寻找第一个 $> idex$ 的值的位置可以用二分。

3. 一开始就是第一段，所以要初始化 $k$ 为 $1$。
## 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#define ll long long
using namespace std;
ll n, m, c1, c2, k = 1, ans, idex, s, t; //注意 k = 1
vector <ll> v[1000005]; //桶
int main()
{
	cin >> n >> m >> c1 >> c2;
	for (ll i = 1; i <= n; i++) cin >> s, v[s].push_back(i); //把下标扔进桶中
	for (ll i = 1; i <= m; i++)
	{
		cin >> t;
		if (v[t].size() == 0) continue; //桶中无物，直接跳过
		ans++; //添加最长公共子序列的长度
		ll p = upper_bound(v[t].begin(), v[t].end(), idex) - v[t].begin(); //寻找第一个下标 > idex 的位置
		if (p == v[t].size()) //找到末尾也没有
		{
			k++; //新开一段
			idex = v[t][0]; //更新下标为第一个元素
		}
		else idex = v[t][p]; //更新下标为当前元素
	}
	cout << ans * c1 << " " << k * c2;
}
```

---

## 作者：_XHY20180718_ (赞：0)

## 题意简述：

给定 $A$、$B$ 两个数组，让你求至少多少个 $A$ 拼起来能达到与 $B$ 有的最长公共子序列，以及最长公共子序列长度是多少。

## 思路：

既然要求最长公共子序列，那么有效元素一定是在 $A$ 和 $B$ 都出现过的元素，元素个数自然也是最长公共子序列的最大长度，然后我们便以 $B$ 为基准，往后在 $A$ 中找下一个符合的元素即可，这里可以用一个 vector 存各个 $B$ 中的每个字符在 $A$ 中分别在哪些地方出现过，然后在 vector 中二分查找大于上一次匹配到的位置，若匹配失败，则重新加上一个 $A$，然后继续进行匹配。

时间复杂度：$O(n\log n+m)$。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,m,a[N],b[N],k=1;
vector<int>c[N];
char vis[N];
bool c1,c2;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>c1>>c2;
	for(int i=1; i<=n; ++i)cin>>a[i],vis[a[i]]=2;
	for(int i=1; i<=m; ++i){
		cin>>b[i];
		if(!vis[b[i]])--m,--i;
		else vis[b[i]]=1;
	}
	for(int i=1; i<=n; ++i)
		if(vis[a[i]]==1)c[a[i]].push_back(i);
	int lst=0;
	for(int i=1; i<=m; ++i){
		auto t=lower_bound(c[b[i]].begin(),c[b[i]].end(),lst+1);
		if(t==c[b[i]].end())++k,lst=c[b[i]][0];else lst=*t;
	}cout<<m*c1<<' '<<k*c2;
	return 0;
}
```


---

## 作者：引领天下 (赞：0)

前言：本题我读题读了 20min 没读懂，问学弟**最长公共子序列**需不需要连续花了 10min，最后过掉只花了 5min。

既然最长公共子序列不要求连续，那么考虑直接贪心地挨个处理 $T$ 中的元素。

设当前我们已经使用了 $k$ 次 $S$ 串，第 $k$ 次复制的 $S$ 串已经用到了第 $i$ 个位置，$T$ 串已经处理到了第 $j$ 个位置。

那么就分以下几种情况：

- $S$ 串中 $i$ 位置之后仍然存在某个 $S_l=T_j$，那么直接使用第一个 $S_l$ 匹配掉 $T_j$，更新 $i$。

- $S$ 串中 $i$ 位置之后已经不存在某个 $S_l=T_j$ 了，但是 $S$ 串中 $i$ 位置及之前仍然存在 $S_l=T_j$，那么就复制一次 $S$，用第一个 $S_l$ 匹配掉 $T_j$。

- $S$ 串中根本不存在某个 $S_l=T_j$，那么 $T_j$ 显然不可能出现在最终的公共子序列里，放弃对 $T_j$ 的匹配。

这个贪心策略的正确性的显然的，故此略去证明。

有了这个思路之后代码就很好实现了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,c1,c2,i,j,s[1000005],t[1000005],cnt=1,ansk;
vector<int>a[1000005];
signed main(){
    ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
    cin>>n>>m>>c1>>c2;
    for(int i=1;i<=n;i++)cin>>s[i],a[s[i]].push_back(i);
    for(int i=1;i<=m;i++)cin>>t[i];
    for(;j<=m;){
        bool flag=0;
        auto k=upper_bound(a[t[j]].begin(),a[t[j]].end(),i);//通过二分查找来找到第一个 l，注意因为我们是按顺序 push_back 的，所以 a[t[j]] 一定是升序的。
        if(k!=a[t[j]].end())i=*k,flag=1;
        else if(!a[t[j]].empty())i=*a[t[j]].begin(),cnt++,flag=1;
        if(flag)ansk++;
        j++;
    }
    cout<<c1*ansk<<' '<<c2*cnt;
    return 0;
}
```

---

## 作者：Special_Judge (赞：0)

这题虽然提到了最长公共子序列但是和求最长公共子序列并无关系。

对于第一个输出，我们可以想到，由于可以拼接任意个数组 $S$ ，对于 $T$ 中的每一个元素，只要它在 $S$ 中出现了，它就一定能成为最长公共子序列的一部分。设在 $T$ 中出现但不在 $S$ 中出现的元素个数为 $t$ ，那么答案即为 $m-t$。

对于第二个输出，我们枚举 $T$ 的每一个在 $S$ 中出现了的元素，在 $S$ 中找到该元素第一个大于上一个 $T$ 元素在 $S$ 出现位置的位置，如果找不到，说明需要再拼接一个数组 $S$。（这句话略绕，可以看代码理解）

意识到，上述的查找过程会被卡到 $O(n)$。

解决方法也很简单，注意到值域只有 $10^6$ ，因此我们可以开 $10^6$ 个`set`或者`vector`来维护每一个元素在 $S$ 中出现的位置，然后`upper_bound`即可。

我的代码中使用的是`set`。至于为什么不用`vector`，~~我会说`set`插入只需要打`insert`6个字母而`vector`插入需要打`push_back`8个字母加一个下划线吗。~~

代码也很简短：

```cpp
//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<stack>
#include<map>
#include<vector>
#include<set>

#define MAXN_INT 2147483647
#define MAXN_LL 9223372036854775807

#define MOD A_NUMBER
#define N 1000005

//#define x0 fuckcpp1
//#define y0 fuckcpp2

#define mp make_pair

using namespace std;
int n,m,c1,c2;
int len;
int s[N],t[N];
int temp;
bool vis[N];
set<int>q[N];//用set维护每一个元素在s中出现的位置，例如q[114514]这个set维护的就是114514这个元素在s中出现的所有下标
typedef set<int>::iterator IT;
int ans=1;
int last=0;
int main()
{
	scanf("%d%d%d%d",&n,&m,&c1,&c2);
    for(int i=1;i<=n;i++)
    {
    	scanf("%d",&s[i]);
    	q[s[i]].insert(i);
    	vis[s[i]]=1;
    }
    for(int i=1;i<=m;i++)
    {
    	scanf("%d",&temp);
    	if(vis[temp])t[++len]=temp;//去除t中所有在s中未出现过的元素
    }
  	m=len;
  	last=*q[t[1]].begin();
  	for(int i=2;i<=m;i++)
  	{
  		IT it=q[t[i]].upper_bound(last);
  		if(it==q[t[i]].end())//找不到，需要再拼接一个s
  		{
  			ans++;
  			last=*q[t[i]].begin();
  		}
  		else last=*it;//能找到
  	}
  	printf("%d %d",m*c1,ans*c2);
	return 0;
}
```

---

