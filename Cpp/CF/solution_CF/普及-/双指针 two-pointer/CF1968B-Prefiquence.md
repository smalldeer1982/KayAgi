# Prefiquence

## 题目描述

给定两个二进制字符串 $a$ 和 $b$。二进制字符串是仅由字符 '0' 和 '1' 组成的字符串。

你的任务是确定最大的整数 $k$，使得字符串 $a$ 的长度为 $k$ 的前缀是字符串 $b$ 的一个子序列。

如果序列 $a$ 可以通过从序列 $b$ 中删除若干（可能为零或全部）元素得到，则称 $a$ 是 $b$ 的一个子序列。

## 说明/提示

在第一个样例中，字符串 '10' 是 '1\color{red}11\color{red}0' 的一个子序列，但字符串 '100' 不是。所以答案是 $2$。

在第五个样例中，$a = '100'$，$b = '1\color{red}{10}1\color{red}0'$，整个字符串 $a$ 是字符串 $b$ 的一个子序列。所以答案是 $3$。

在第六个样例中，字符串 $b$ 不包含 '1'，所以答案是 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6
5 4
10011
1110
3 3
100
110
1 3
1
111
4 4
1011
1111
3 5
100
11010
3 1
100
0```

### 输出

```
2
2
1
1
3
0```

# 题解

## 作者：Pursuewind (赞：5)

简单题赛时都写了 6 分钟，菜。

## 题意简述

给你两个串，$a$ 和 $b$，找出一个长度最大的串 $s$，满足：

- $s$ 是 $a$ 的前缀。
- $s$ 是 $b$ 的子串。

输出这个最大值。

## 做法

看到第一条限制，可以想到对于字符串 $a$，我们把它从前往后便利，假设当前遍历到位置 $i$，再根据子串的定义，我们可以记录一个 $pos$，表示 $b$ 中上一个出现 $a_{i-1}$ 的位置。

那么我们从 $[pos,lenb]$ 中找到第一个 $a_i$ 出现的位置即可，如果没找到，答案即为 $i-1$。

附赛时代码，由于 $pos$ 最坏情况下会从 $1$ 扫到 $lenb$，所以复杂度最坏为 $O(m)$：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int n, m;
string a, b;
void solve()
{
	cin >> n >> m;
	cin >> a >> b;
	a = " " + a; b = " " + b;
	int pos = 0;
	for (int i = 1; i <= n; i ++){
		while (1){
			if (pos > m) break;
			pos ++;
			if (b[pos] == a[i]){
				break;
			}
		}
		if (pos > m){
			cout << i - 1 << "\n";
			return ;
		}
	}
	cout << n << "\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t --) solve();
	return 0;
}
```

---

## 作者：JuRuoOIer (赞：3)

# 题解 CF1698B - Prefiquence

本题解为 **贪心** 做法。

### 题意

已提交翻译。

给定两个 01 串 $a,b$，长度分别为 $n,m$。你要求一个最大的 $1 \le k \le n$，使得 $\overline{a_1a_2a_3\dots a_k}$ 是 $b$ 的子序列。

数据范围：$\sum n\le 2\times10^5,\sum m\le 2\times10^5$。

### 做法

枚举 $a$ 的每个字符并在 $b$ 中从找到上一个字符的位置往后找即可。时间复杂度 $O(n+m)$。

例如第一组样例：

```
10011
1110
```

这里：
- $a_1=1$，从 $b_1$ 开始第一个 $1$ 在 $b_1$ 上；
- $a_2=0$，上一个找到的位置为 $b_1$，从 $b_2$ 开始第一个 $0$ 在 $b_4$ 上；
- 此时已经找到 $b$ 的最后一位，因此答案为 $2$。

```cpp
ll t,n,m;
string a,b;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		cin>>a>>b;
		ll k=0;
		for(int i=0;i<m;i++){
			if(b[i]==a[k])k++;
		}
		cout<<k<<endl;
	}
	return 0;
}
```

---

## 作者：JXR_Kalcium (赞：3)

## 题目大意
给出两个长度为 $N$ 和 $M$ 的字符串 $a,b$，若字符串 $a$ 的前缀为 $b$ 的子序列，求这个前缀的最长长度。
## 解题思路
很明显，这个是**双指针**问题。

我们先枚举 $a$ 中的每个字符，再在 $b$ 中从前往后找即可。假如指针为 $i,j$，那么一开始它们都等于 $0$，然后后移 $j$，直到 $a[i]=b[j]$ 或者 $j\geq M$。最后的答案就应该是 $i+1$（$i$ 从 $0$ 开始枚举），并且还要将 $j$ 后移 $1$ 位，以便后续判断。

还有一种情况，就是 $j\geq M$ 并且 $a[i+1]$ 跟 $b[j]$ 都超出原字符串的范围，就要直接跳出循环。
## AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int t,n,m,j,ans,bz;
char a[200001],b[200001];

int main()
{
	scanf("%d",&t);
	
	while(t--)
	{
		scanf("%d%d%s%s",&n,&m,a,b);
		j=0; ans=0;
		
		for(int i=0; i<n; ++i)
		{
			bz=1;
			
			while(a[i]!=b[j])
			{
				++j;
				
				if(j>=m)
				{
					bz=0; break;
				}
			}
			
			if(bz) ans=i+1, ++j;
			if(a[i+1]==b[j] && j>=m) break;
		}
		
		printf("%d\n",ans);
	}

	return 0;
}
```

---

## 作者：Harrylzh (赞：2)

## 题意

有两个二进制字符串 $a,b$ 请找出 $a$ 中的最长前缀使得它是 $b$ 的子序列。

## 思路

遍历 $a$ 串中的元素，依次在 $b$ 中找，找不到时停止，统计找到的元素个数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t;
long long n,m;
string a,b;
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&m);
		cin>>a>>b;
		long long cur=0;//在b中找过的位置
		long long ans=-1;//答案
		for(long long i=0;i<a.size()&&cur<b.size();i++)
		{
			while(cur<b.size()&&b[cur]!=a[i]) cur++;
			if(cur==b.size()) break;//找完也找不到
			cur++;
			ans=i;
		}
		printf("%lld\n",ans+1);
	}
	return 0;
}
```

---

## 作者：junee (赞：2)

# CF1968B 题解

## 题目分析

我们可以发现题目要我们找到一个字符串是 $a$ 的最长前缀且是 $b$ 的子串，那么我们可以先把 $a$ 数组读入，然后依次读入 $b$ 数组，当 $a_i = b_j$ 时，那么答案加一。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
char a[N],x; 
int T,n,m,tt=1,ans;
int main(){
	cin>>T;
	while(T--){
		tt=1,ans=0; 
		cin>>n>>m;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=m;i++){
			cin>>x;
			if(x!=a[tt]||tt>n)continue;
			tt++,ans++;
		}
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：__YSC__ (赞：1)

# 题目描述

给定只包含 `0` 和 `1` 的长度分别为 $N,M$ 的字符串 $A,B$。求 $A$ 的最长的前缀长度使得这个前缀与 $B$ 的一个子序列相等。

# 思路

使用贪心的思想。

从前往后扫描字符串 $A$，并记录一个变量 $pos$，表示当前匹配到了 $B$ 的哪一个位置。所以要先预处理出 $B$ 中每一个位置后第一个 $0,1$ 的位置 $r_{0/1,i}$，如果不存在则设为 $M+1$，这个可以通过倒着扫描一遍 $B$ 得到。

在扫描 $A$ 时每次让 $pos \leftarrow r_{A_i,pos + 1}$，如果找不到该位置则代表已经不存在合法的子序列了。

时空复杂度均为 $O(N+M)$。

## 细节

要把 $r_{0/1,M+1}$ 设为 $M+1$，因为你有可能会访问到那个位置。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int t, n, m, r[2][MAXN];
string a, b;

void Solve() {
  cin >> n >> m >> a >> b;
  a = ' ' + a, b = ' ' + b, r[0][m + 1] = r[1][m + 1] = m + 1;
  for(int i = m, pos = m + 1, pos2 = m + 1; i >= 1; --i) {
    pos = (b[i] == '0' ? i : pos), pos2 = (b[i] == '1' ? i : pos2);
    r[0][i] = pos, r[1][i] = pos2;
  }
  for(int i = 1, pos = 0; i <= n; ++i) {
    pos = r[a[i] - '0'][pos + 1];
    if(pos >= m + 1) {
      cout << i - 1 << "\n";
      return;
    }
  }
  cout << n << "\n";
}

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  for(cin >> t; t--; Solve()) {
  }
  return 0;
}
```

---

## 作者：lgx57 (赞：1)

不用想得很复杂。

$k$ 从 $1$ 开始枚举。

维护一个指针 $now$, 指向 $b$ 目前所匹配到的字符，若 $a_{k}=b_{now}$，那么跳出循环，进行下一轮枚举。反之，若 $now$ 枚举到 $m$ 都无法与 $a_{k}$ 匹配，那么跳出循环。

最后的 $k$ 即为答案。
```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
void fio(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}
const int N=2e5+5;
int a[N],b[N];
signed main(){
	fio();
	int t;
	cin>>t;
	while (t--){
		int n,m;
		cin>>n>>m;
		for (int i=1;i<=n;i++){
			char x;
			cin>>x;
			a[i]=x-'0';
		}
		for (int i=1;i<=m;i++){
			char x;
			cin>>x;
			b[i]=x-'0';
		}
		bool f;
		int j=1,ans=0;
		for (int i=1;i<=n;i++){//枚举 k
			f=0;
			for (;j<=m;j++){
				if (a[i]==b[j]){
					j++;
					f=1;
					break;
				}
			}
			if (!f){
				break;
			}
			else{
				ans=i;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：lailai0916 (赞：1)

## 原题链接

- [洛谷 CF1968B Prefiquence](https://www.luogu.com.cn/problem/CF1968B)

## 题意简述

求字符串 $a$ 的最长前缀是字符串 $b$ 的子序列。

## 解题思路

枚举字符串 $b$。如果等于 $a_i$，说明目前长度为 $i$ 的前缀符合要求，后续判断长度为 $i+1$ 的前缀是否符合要求，所以令 $i\gets i+1$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int inf=0x3f3f3f3f;
const int mod=1e9+7;
const int N=200005;
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,m;
		string a,b;
		cin>>n>>m>>a>>b;
		int i=0,j=0;
		while(i<n&&j<m)
		{
		    if(a[i]==b[j])i++;
		    j++;
		}
		cout<<i<<'\n';
	}
	return 0;
}
```

---

## 作者：Vitamin_B (赞：0)

# 思路
首先很显然，如果 $a_1\sim a_i$ 是 $b$ 的子序列，那 $a_1\sim a_{i-1}$ 肯定也是 $b$ 的子序列，所以我们可以贪心枚举 $i$，直到不满足条件的就退出循环。但也不需要对每个 $i$ 都单独做一遍判断，我们用变量 $j$ 表示 $a_1\sim a_{i-1}$ 是 $b_1\sim b_j$ 的子序列时，$j$ 的最小值。然后每次判断只要在上一次的基础上找到第一个 $b_k=a_i(k>j)$ 的 $k$ 来作为新的 $j$，如果找不到就是不符合条件了，输出答案退出循环。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, m, now;
string a, b;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m >> a >> b;
		now = 0;
		for (int i = 0; i < n; ++ i) {
			while (now < m && b[now] != a[i])
				++ now;
			if (++ now > m) {
				cout << i << '\n';
				goto end;
			}
		}
		cout << n << '\n';
end:
		;
	}
	return 0;
}
```

---

## 作者：DrAlfred (赞：0)

摘要：贪心，字符串匹配

[传送门：https://www.luogu.com.cn/problem/CF1968B](https://www.luogu.com.cn/problem/CF1968B)

## 题意

给定两个由 `0` 和 `1` 组成的字符串 $a, b$。找到最大的 $k$，使得长度为 $k$ 的 $a$ 的前缀为 $b$ 的子序列。

## 分析思路

考虑贪心匹配。我们使用两个指针 $x$ 和 $y$ 分别表示 $a$ 与 $b$ 已经匹配到的位置。对于枚举到的每个位置 $x$，一直右移 $y$ 直到 $a_x$ 与 $b_y$ 匹配或 $y$ 越界。最终 $x$ 的值即为答案。

时间复杂度 $O\left(n + m\right)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
i64 t = 1, n, m;
inline void solve(void) {
    string a, b;
    cin >> n >> m >> a >> b;
    int k = 0, beg = 0;
    while (beg < m) {
        if (k < n && a[k] == b[beg]) k++;
        beg++;
    }
    cout << k << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：_H17_ (赞：0)

## 题目分析

读完题看到数据范围是 $1\le n,m\le2 \times10^5$ 那时间复杂度肯定是 $O(n)$ 或 $O(n\log n)$。


首先 $a$ 的前缀是 $b$ 的子序列。那我们可以从 $a_1 \sim a_n$ 依次和 $b$ 上匹配（因为是子序列，只要找到相同的就换 $a_{i+1}$）。

似乎不太行？复杂度是 $O(n\times m)=O(n^2)$？其实不是，子序列虽然不要求连续，但是顺序需要满足，也就是如果 $a_1$ 和 $b_j$ 匹配。那 $a_2$ 只能和 $b_{j+1}\sim b_m$ 匹配，这样 $a$ 遍历一边，$b$ 同时遍历一遍，所以时间复杂度是 $O(\max\{n,m\})=O(n)$。

## 代码实现

```cpp
void Main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%1d",a+i);
    for(int j=1;j<=m;j++)
        scanf("%1d",b+j);//注意：只读入 1 位
    int i=1,j=1;
    for(;i<=n&&j<=m;i++){//枚举 a[i]
        for(;j<=m;)//枚举 b[j]
            if(a[i]==b[j++])//匹配
                break;
        if(a[i]!=b[j-1])//失配
        	break;
    }
    printf("%d\n",i-1);//注意：失配前一位才能匹配
    return;
}
```

---

