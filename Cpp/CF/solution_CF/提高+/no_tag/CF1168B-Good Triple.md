# Good Triple

## 题目描述

Toad Rash 有一个二进制字符串 $s$。二进制字符串只包含 $0$ 和 $1$。

设 $n$ 为 $s$ 的长度。

Rash 需要找出满足以下条件的整数对 $(l, r)$ 的数量：$1 \leq l \leq r \leq n$，并且存在至少一组整数 $x, k$，使得 $1 \leq x, k \leq n$，$l \leq x < x + 2k \leq r$，且 $s_x = s_{x+k} = s_{x+2k}$。

请你帮 Rash 计算满足条件的 $(l, r)$ 对的数量。

## 说明/提示

在第一个样例中，需要计数的 $(l, r)$ 对有三组：$(1, 6)$、$(2, 6)$ 和 $(1, 5)$。

在第二个样例中，原始字符串不存在满足条件的 $x, k$，因此答案为 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
010101
```

### 输出

```
3
```

## 样例 #2

### 输入

```
11001100
```

### 输出

```
0
```

# 题解

## 作者：81179332_ (赞：4)

神仙题

多试几个字符串，可以发现，只要长度稍微长一点，很容易就是合法的

实际上，所有长度大于 $9$ 的字符串都是合法的，这一点可以暴搜证明

那么接下来就简单极了，从 $n$ 到 $1$ 枚举左端点 $l$，暴力求出最近的合法右端点 $r$，累加答案，$r$ 显然单调不升

```cpp
const int N = 300010;
char s[N];int n;
ll ans;
int main()
{
	scanf("%s",s + 1),n = strlen(s + 1);
	int l,r = n + 1;
	for(l = n;l;l--)
	{
		for(int i = 1;l + 2 * i <= n;i++)
			if(s[l] == s[l + i] && s[l] == s[l + 2 * i])
			{ r = min(r,l + 2 * i);break ;}
		ans += max(n - r + 1,0);
	}fprint(ans);
 	return 0;
}
```

---

## 作者：small_john (赞：1)

## 前言

新的一年，就用水题解来开始吧！

## 思路

一道非常巧妙的题。

手玩几组数据，发现长度较长的字符串大概率能找到合法的三元组，于是毫不犹豫地打了个暴搜证明猜想，程序如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main()
{
	for(int len = 3;len<=100;len++)
	{
		bool fl = 1;
		for(int z = 0;z<(1<<len);z++)
		{
			bool ok = 0;
			for(int i = 0;i<len-2;i++)
				for(int j = 1;i+2*j<len;j++)
					if(((z>>i)&1)==((z>>(i+j))&1)&&((z>>i)&1)==((z>>(i+2*j))&1))
					{
						ok = 1;
						break;
					}
			if(!ok)
			{
				fl = 0;
				break;
			}
		}
		if(fl) return cout<<len,0;//长度为 len 的字符串无论如何都合法
	}
	return 0;
}
```

得到的答案为 $9$，那就可以直接打暴力。

具体的，从后往前扫左端点，暴力维护最小的右端点即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5+5;
int n;
long long ans;
string s;
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>s,n = s.size(),s = ' '+s;
	int p = n+1;
	for(int i = n;i;i--)
	{
		for(int j = 1;i+2*j<=n;j++)
			if(s[i]==s[i+j]&&s[i+j]==s[i+2*j])
			{
				p = min(p,i+2*j);
				break;
			}
		ans+=n-p+1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ZMQ_Ink6556 (赞：0)

## 题解：CF1168B Good Triple

神仙诈骗题。

### 题意简述

给你一个字符串 $s$，请你统计所有满足存在 $x,k \in \mathcal Z^+$ 使 $1 \le l \le x < x + 2 \times k \le r \le n$ 且 $s_x = s_{x + k} = s_{x + 2 \times k}$ 的数对 $(1,r)$ 的数量。

### 解题思路

观察可得，若 $r - l$ 足够大，那么一定存在合法的 $x , k$。具体说，若 $r - l \ge 9$，那么 $(l,r)$ 一定合法。

所以所有 $r - l < 9$ 的区间直接暴力枚举 $x , k$ 判断即可，大于 $9$ 的区间直接判为存在即可（因为长度 $> 9$ 的字符串总能取出一段长度 $= 9$ 的字串，而所有长度 $= 9$ 的 $01$ 串都有合法的 $x,k$）。

复杂度分析：设区间的存在阈值为 $V(V=9)$，则复杂度为 $\Theta(V^3 + n)$。

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n;
string s;
bool a[300005];
long long ans;
inline bool check(int l , int r)
{
	for(int i = l ; i <= r ; i++)
	{
		for(int j = 1 ; i + j + j <= r ; j++)
		{
			if(a[i] == a[i + j] && a[i + j] == a[i + j + j])
			{
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s;
	n = s.size();
	for(int i = 1 ; i <= n ; i++)
	{
		a[i] = s[i - 1] - '0';
	}
	for(int i = 1 ; i <= n ; i++)
	{
		for(int j = i ; j <= min(i + 10 , n) ; j++)
		{
			if(check(i , j))
			{
				ans++;
			}
		}
		ans += max(n - i - 10 , 0);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Eazin_star (赞：0)

### 思路
如果有两个满足要求的 $x$ 和 $k$ 那么 $k$ 小的那个能产生的区间一定更多。所以我们从后往前枚举左端点，再枚举 $k$，如果满足要求，记录最小的右端点。因为此时我们最小右端点，所以对于当前的左端点来说所能贡献的区间就是从右端点开始到最后一个字符的字符个数。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long //ans要开long long，不开long long只有40分！！！
using namespace std;

int n, ans;
string s, t;

signed main() {
	cin >> t;
	s = ' '+t;
	n = t.size();
	int minn = n+1;
	for (int i = n; i; i--) { //从后往前枚举左端点
		for (int j = 1; i+2*j <= n; j++) { //枚举k
//			cout << i << " " << j << endl;
			if (s[i] == s[i+j] && s[i+j] == s[i+2*j]) {
				minn = min(minn, i+2*j); //记录最小右端点
//				cout << minn << endl;
				break;
			}
		}
		ans += n-minn+1; //记录当前左节点所能贡献的最多区间个数
	}	
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：Disjoint_cat (赞：0)

# CF1168B Good Triple

[Link - Luogu](https://www.luogu.com.cn/problem/CF1168B)，[Link - Codeforces](http://codeforces.com/problemset/problem/1168/B)。

## 题意

给定 $\texttt{01}$ 序列 $s$，求其满足以下条件的（连续）子串数量：

> 存在下标成等差数列的 $3$ 个相等的字符。

$\left\vert s\right\vert\le10^5$。

## 题解

下令 $n=\left\vert s\right\vert$。

我们看到样例：$\texttt{11001100}$，答案是 $0$。

根据经验，很多样例都是有意放的，其中有可能暗示着某些信息。那我们看看这个？

这个字符串的答案是 $0$，也就是说，整个串都不合法。

那这会不会是最长的不合法的串呢？

看起来不太好证明。那我们暴力枚举：

```cpp
for(int i=0;i<1<<9;i++)//用二进制枚举
{
    bool ok=1;
    for(int j=1;j<=7&&ok;j++)
        for(int k=1;j+2*k<=9;k++)
        {
            bool x=i&(1<<j),y=i&(1<<j+k),z=i&(1<<j+(k<<1));
            if(x==y&&x==z){ok=0;break;}
        }
    if(ok)cout<<i<<endl;//不合法就输出
}
```

没有输出，所以确实没有长度更长（$\ge9$）的不合法的串了。

那就简单了！

那我们只要枚举长度 $\le8$ 的子串，如果不合法就从答案中减掉即可。

时间复杂度为 $\Theta(n\cdot\text{const})$，其中 $\text{const}$ 是常数。

## 代码

```cpp
string s;
int n;
ll ans;
void Solve()
{
	cin>>s;n=s.size();s="$"+s;
    ans=1ll*n*(n+1)/2;
    for(int i=1;i<=n;i++)
        for(int l=1;l<=8&&i+l-1<=n;l++)
        {
            string t=s.substr(i,l);t="$"+t;
            bool ok=1;
            for(int j=1;j<=l-2&&ok;j++)
                for(int k=1;j+2*k<=l;k++)
                    if(t[j]==t[j+k]&&t[j]==t[j+k*2])
                    {
                        ok=0;
                        break;
                    }
            ans-=ok;
        }
    cout<<ans;
}
```



---

## 作者：StudyingFather (赞：0)

我们对于每个 $ l $ ，暴力地计算出能构成好的字符串的 $ r $ 的最大值，则对于一切 $ r \in [l,r_{max}] $ 都能满足题目所给出的条件。

这样算的复杂度似乎是 $ O(n^2) $ 的？实际上并非如此。我们可以证明：不存在长度超过 $ 9 $ 的字符串。因而实际的复杂度是 $ O(9n) $ （说白了就是 $ O(n) $ ）。

```cpp
#include <iostream>
#include <cstring>
using namespace std;
char s[300005];
int main()
{
 cin>>s;
 int len=strlen(s),r=len+1;
 long long ans=0;
 for(int i=len-1;i>=0;i--)
 {
  for(int j=1;i+2*j<len;j++)
   if(s[i]==s[i+j]&&s[i+j]==s[i+2*j])
   {
    r=min(r,i+2*j);
    break;
   }
  ans+=max(len-r,0);
 }
 cout<<ans<<endl;
 return 0;
}
```


---

