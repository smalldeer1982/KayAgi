# Replacement

## 题目描述

Daniel has a string $ s $ , consisting of lowercase English letters and period signs (characters '.'). Let's define the operation of replacement as the following sequence of steps: find a substring ".." (two consecutive periods) in string $ s $ , of all occurrences of the substring let's choose the first one, and replace this substring with string ".". In other words, during the replacement operation, the first two consecutive periods are replaced by one. If string $ s $ contains no two consecutive periods, then nothing happens.

Let's define $ f(s) $ as the minimum number of operations of replacement to perform, so that the string does not have any two consecutive periods left.

You need to process $ m $ queries, the $ i $ -th results in that the character at position $ x_{i} $ ( $ 1<=x_{i}<=n $ ) of string $ s $ is assigned value $ c_{i} $ . After each operation you have to calculate and output the value of $ f(s) $ .

Help Daniel to process all queries.

## 说明/提示

Note to the first sample test (replaced periods are enclosed in square brackets).

The original string is ".b..bz....".

- after the first query $ f( $ hb..bz.... $ ) $ = 4 ("hb\[..\]bz...." $ → $ "hb.bz\[..\].." $ → $ "hb.bz\[..\]." $ → $ "hb.bz\[..\]" $ → $ "hb.bz.")
- after the second query $ f( $ hbс.bz.... $ ) $ = 3 ("hbс.bz\[..\].." $ → $ "hbс.bz\[..\]." $ → $ "hbс.bz\[..\]" $ → $ "hbс.bz.")
- after the third query $ f( $ hbс.bz..f. $ ) $ = 1 ("hbс.bz\[..\]f." $ → $ "hbс.bz.f.")

Note to the second sample test.

The original string is ".cc.".

- after the first query: $ f( $ ..c. $ ) $ = 1 ("\[..\]c." $ → $ ".c.")
- after the second query: $ f( $ .... $ ) $ = 3 ("\[..\].." $ → $ "\[..\]." $ → $ "\[..\]" $ → $ ".")
- after the third query: $ f( $ .a.. $ ) $ = 1 (".a\[..\]" $ → $ ".a.")
- after the fourth query: $ f( $ aa.. $ ) $ = 1 ("aa\[..\]" $ → $ "aa.")

## 样例 #1

### 输入

```
10 3
.b..bz....
1 h
3 c
9 f
```

### 输出

```
4
3
1
```

## 样例 #2

### 输入

```
4 4
.cc.
2 .
3 .
2 a
1 a
```

### 输出

```
1
3
1
1
```

# 题解

## 作者：lailai0916 (赞：3)

## 原题链接

- [洛谷 CF570C Replacement](https://www.luogu.com.cn/problem/CF570C)

## 题意简述

给定长度为 $n$ 的字符串，包含 `.` 和小写字母，进行 $m$ 次操作，每次修改一个字符，并询问将所有连续 `.` 转化为单个 `.` 所需的次数。

## 解题思路

设字符串中有 $k$ 个连续的 `.` 子串，长度分别为 $a_i$。每个子串需要 $a_i - 1$ 次转化，总转化次数为：

$$
\sum_{i=1}^k (a_i - 1) = \left( \sum_{i=1}^k a_i \right) - k
$$

注意到，$\sum_{i=1}^k a_i$ 为字符串中所有 `.` 的总数，在每次操作中，判断是否将某个 `.` 替换为字母或字母替换为 `.`，即可更新 `.` 的数量。

对于每次操作分类讨论，维护 `.` 子串数量：

1. 将 `.` 替换为字母：如果左右两边都是字母，则 `.` 子串数量减少 $1$，转化次数加 $1$；如果左右两边都是 `.`，则 `.` 子串数量增加 $1$，转化次数减少 $1$。
2. 将字母替换为 `.`：如果左右两边都是字母，则 `.` 子串数量增加 $1$，转化次数减少 $1$；如果左右两边都是 `.`，则 `.` 子串数量减少 $1$，转化次数增加 $1$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int N=300005;
int a[N];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,m;
	cin>>n>>m;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		char f;
		cin>>f;
		a[i]=f=='.';
		if(a[i]&&a[i-1])ans++;
	}
	while(m--)
	{
		int x;
		char f;
		cin>>x>>f;
		int y=f=='.';
		if(a[x]!=y)
		{
			a[x]=y;
			ans+=(a[x-1]+a[x+1])*(y*2-1);
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：OIerJiang_1017 (赞：2)

## [CF570C 题目传送门](https://www.luogu.com.cn/problem/CF570C)

## 题目大意
给定一个包含小写英文字母和句点符号的字符串 $s$，其中句点符号用 `.` 表示。定义替换操作如下：在字符串 $s$ 中找到子字符串 `..`，即两个连续的句点，选择第一个出现的子字符串并将其替换为 `.`。如果字符串 $s$ 中没有连续的两个句点，则不发生任何操作。定义 $f(s)$ 为使字符串中不再有任何连续句号所需的最小替换次数。您需要处理 $m$ 个查询，第 $i$ 个查询的结果是将字符串 $s$ 中位置为 $x_i$ 的字符赋值为 $c_i$。每次操作完成后，您需要计算并输出 $f(s)$ 的值。

## 解决思路
**分类讨论**是个好东西：
- 如果要被替换的位于 $x$ 的字符是 `.`，且要被字母替换：
  - 如果前面也是点，因为他变成了字母所以要少一种情况；
  - 如果后面也是点，因为他变成了字母所以要少一种情况；
- 如果要被替换的位于 $x$ 的字符是字母，且要被 `.` 替换：
  - 如果前面也是点，因为他变成了点所以要多一种情况；
  - 如果后面也是点，因为他变成了点所以要多一种情况。

## 代码展示
```cpp
#include <iostream>
#define ll long long
//不开long long见祖宗 
using namespace std;

ll n, m;
string s;

int main()
{
	scanf("%lld%lld", &n, &m);
	cin >> s;//建议scanf,更快
	ll cnt = 0, l = s.size();//l记录字符串的长度
	for(int i = 0; i < l; i++)
		if(s[i] == '.' && s[i + 1] == '.')
			cnt++;//cnt记录两个连续的点的个数
	for(int i = 1; i <= m; i++)
	{
		ll x;
		char c;
		scanf("%lld%c", &x, &c);
		x--;//x--是因为字符串下标从0开始 
		if(s[x] == '.' && c >= 'a' && c <= 'z')
		{
			if(s[x-1] == '.' && x > 0) cnt--;
			//如果前面也是点，因为他变成了字母所以要少一种情况
			if(s[x+1] == '.' && x < l) cnt--;
			//如果后面也是点，因为他变成了字母所以要少一种情况
		}
		else if(c == '.' && s[x] >= 'a' && s[x] <= 'z')
		{
			if(s[x-1] == '.' && x > 0) cnt++;
			//如果前面也是点，因为他变成了点所以要多一种情况
			if(s[x+1] == '.' && x < l) cnt++;
			//如果后面也是点，因为他变成了点所以要多一种情况
		}
		s[x] = c;//将位置x换成指定字母
		printf("%lld\n", cnt);//建议printf,更快
	}
	return 0;
}
```

---

## 作者：PeterBei (赞：2)

容易发现，若序列中含有连续的句号串，则可以从末尾开始依次合并，总贡献为句号数减一。

因此，假设现有一长度为 $n$ 的连续句号串，其对答案的贡献为 $n-1$。

1. 若将开头或结尾的句号改为字母，则句号串长度变为 $n-1$，贡献变为 $(n-1)-1$，相对于原贡献减少了 $1$。

2. 若将中间的第 $i$ 个句号改为字母（$2\leq i\leq n-1$），则原句号串分裂为两个长度分别为 $i-1$ 和 $n-i$ 的句号串，其对答案的贡献分别为 $(i-1)-1$ 和 $(n-i)-1$，总贡献为 $[(i-1)-1]+[(n-i)-1]=n-3$，相对于原贡献减少了 $2$。

依次类推，可以得到将字母改成句号时贡献的变化。

先预处理出初始序列总句号串的贡献，随后对于每一次询问，检测该修改是在句号串头/尾或者是串中，将总贡献进行相应的加减即可。

``` cpp
int main(){
	int n = read(), m = read(), ans = 0;
	for(int i = 1; i <= n; i++) a[i] = (getchar() == '.' ? 1 : 0);
	for(int i = 1; i <= n; i++)
		if(a[i] && a[i + 1]) ans++;
	for(int i = 1; i <= m; i++){
		int x = read(), z = (getchar() == '.' ? 1 : 0); 
		if(a[x] != z){
			if(z) ans += (a[x - 1] + a[x + 1]);
			else  ans -= (a[x - 1] + a[x + 1]);
		} cout << ans << '\n'; a[x] = z;
	}
	return 0;
}
```

---

## 作者：joy2010WonderMaker (赞：1)

这题唯一一篇题解是线段树，但显然，这题不用线段树。

### 题目分析

分情况讨论。

- 若把字母改成字母或句号改成句号，则不可能改变。

- 若把句号改成字母，如果它前面是句号或后面是句号，则答案会减一。因为这样会减少一对 `..`。

- 若把字母改成句号，同理，如果前后是，则加一，因为这样会多一对 `..`。 

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,ans,x;
char c[2],s[300005];
int main(){
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=1;i<=n;i++)
		if(s[i]=='.'&&s[i+1]=='.')
			ans++;
	while(m--){
		scanf("%d%s",&x,c);
		if(s[x]!='.'&&c[0]!='.')//分类讨论
			s[x]=c[0];
		else if(s[x]=='.'&&c[0]=='.')
			s[x]=c[0];
		else if(s[x]=='.'&&c[0]!='.'){
			if(x>=1&&s[x-1]=='.')
				ans--;
			if(x<n&&s[x+1]=='.')
				ans--;
			s[x]=c[0];
		}else{
			if(x>=1&&s[x-1]=='.')
				ans++;
			if(x<n&&s[x+1]=='.')
				ans++;
			s[x]=c[0];
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Awdrgysxc (赞：1)

线段树模板题

### 【分析】
先建线段树，考虑如何合并

不难发现两段区间和并时，只有左区间的最右边是 '.' && 右区间的左边是'.'时大区间 + 1

### 【Code】
```cpp
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>

namespace IO
{
	inline long long read()
	{
		long long ret=0;bool flag=0;char c=getchar();
		while ((c<'0')|(c>'9')) flag ^= !(c^'-'),c=getchar();
		while ((c>='0')&(c<='9')) ret=(ret<<1)+(ret<<3)+(c^'0'),c=getchar();
		return flag?-ret:ret;
 	}
 	char OutputAns[1<<20|1],*OutputCur = OutputAns;
 	inline void output()
 	{
 		OutputCur -= fwrite(OutputAns,1,OutputCur - OutputAns,stdout);
	}
	inline void print(long long ans)
	{
		char s[20]={0};
		if (OutputCur - OutputAns + sprintf(s,"%lld",ans) >> 20) output();
		OutputCur += sprintf(OutputCur,"%lld",ans);
	}
	inline void printc(char c)
	{
		if (OutputCur - OutputAns + 1 >> 20) output();
		*(OutputCur++) = c;
	}
}

using IO::read;
using IO::print;
using IO::output;
using IO::printc;

const int M = 3e5 + 11;

int n,m;

char Arr[M];

namespace Seg
{
	int Tree[M<<2];
	
	inline void PushUp(int k,int l,int r)
	{
		int mid = l + r >> 1;
		Tree[k] = Tree[k<<1] + Tree[k<<1|1] + ((Arr[mid] == Arr[mid + 1] && Arr[mid] == '.')
		 ? 1 : 0);
	}
	
	inline void Build(int k,int l,int r)
	{
		if (l == r)
		{
			Tree[k] = 0;
			return ;
		}
		int mid = l + r >> 1;
		Build(k<<1,l,mid);
		Build(k<<1|1,mid + 1,r);
		PushUp(k,l,r);
	}
	
	inline void Modifty(int k,int l,int r,int pos,char c)
	{
		if (l == r)
		{
			Arr[pos] = c;
			Tree[k] = 0;
			return ;
		}
		int mid = l + r >> 1;
		if (pos <= mid) Modifty(k<<1,l,mid,pos,c);
		else Modifty(k<<1|1,mid + 1,r,pos,c);
		PushUp(k,l,r);
	}
	
	inline int Query(int k,int l,int r,int x,int y)
	{
		if (x <= l && y >= r) return Tree[k];
		int mid = l + r >> 1;
		int ret = 0;
		if (x <= mid) ret = Query(k<<1,l,mid,x,y);
		if (y > mid) ret += Query(k<<1|1,mid + 1,r,x,y);
		return ret;
	}
}

using Seg::Build;
using Seg::Query;
using Seg::Modifty;

inline void Input()
{
	n = read(),m = read();
	scanf("%s",Arr + 1);
	Build(1,1,n);
}

inline void Sovle()
{
	while (m--)
	{
		int pos = read();
		char cc;
		scanf("%c",&cc);
		Modifty(1,1,n,pos,cc);
		print(Query(1,1,n,1,n)),printc('\n');
	}
	output();
}

int main(void)
{
	Input();
	Sovle();
}
```

---

## 作者：achjuncool (赞：0)

# 解法

显然每次修改第 $t$ 个字符后，只有相邻的两个字符可能与它的关系发生变化。

- 把字母改成字母或把 `.` 改成 `.` 时，需要操作的次数不变。

- 把字母改成 `.` 时，如果原先有 $n$ 个相邻的字符也是 `.`，则需要操作的次数加上 $n$。

- 把 `.` 改成字母时，如果原先有 $n$ 个相邻的字符是 `.`，则需要操作的次数减去 $n$。

先预处理一遍，每次修改判断一下就行了（注意越界问题）。

时间复杂度为 $O(n+m)$。

# Code

```cpp
#include <bits/stdc++.h> 
using namespace std;
typedef long long ll;
#define qwq ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define endl '\n'
string a;
ll n, tot, t, m;
char c;
int main(){
	qwq;
	cin >> n >> m >> a;
	for(ll i = 0; i < a.length() - 1; i++) if(a[i] == '.' && a[i + 1] == '.') tot++;
	for(ll i = 1; i <= m; i++){
		cin >> t >> c;
		t--;
		if(c == '.' && a[t] >= 'a' && a[t] <= 'z'){
			if(t < a.length() - 1 && a[t + 1] == '.') tot++; 
			if(t > 0 && a[t - 1] == '.') tot++;
		} else if(a[t] == '.' && c >= 'a' && c <= 'z'){
			if(t < a.length() - 1 && a[t + 1] == '.') tot--; 
			if(t > 0 && a[t - 1] == '.') tot--; 
		}
		a[t] = c;
		cout << tot << endl;
	}
	return 0;
}
```

---

