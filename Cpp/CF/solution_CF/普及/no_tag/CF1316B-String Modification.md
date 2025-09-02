# String Modification

## 题目描述

Vasya 有一个长度为 $n$ 的字符串 $s$。他想要对它进行以下的修改：
1. 选择一个整数 $k$ 且 $1\leq k\leq n$。
2. 让 $i$ 从 $1$ 循环到 $n - k + 1$，每一次反转 $s$ 在 $[i,i + k - 1]$ 范围中的子串。

比如说，字符串 $s$ 是 $\texttt{qwer}$ 且 $k = 2$，以下就是 $s$ 被修改的过程：

- $\texttt{qwer}$（原字符串）
- $\texttt{wqer}$（旋转了第一个长为 $2$ 的子串）
- $\texttt{weqr}$（旋转了第二个长为 $2$ 的子串）
- $\texttt{werq}$（旋转了最后一个长为 $2$ 的子串）

所以，$s$ 经过 $k = 2$ 的一系列变化后最终会变成 $\texttt{werq}$。

Vasya 希望选择一个 $k$,使得经过上述变化的字符串字典序最小。如果多个不同的 $k$ 都能满足要求，他想要取最小的一个。他正忙着参加 Felicity 2020，于是他叫你来帮他。

一个字符串 $a$ 比 $b$ 字典序更小需要以下条件中只有一个满足：

- $a$ 是 $b$ 的前缀，但 $a \ne b$;
- 在从左往右 $a$ 和 $b$ 第一个不同的位置，$a$ 上的字符在字母表中比 $b$ 上字符更靠前。

## 样例 #1

### 输入

```
6
4
abab
6
qwerty
5
aaaaa
6
alaska
9
lfpbavjsm
1
p```

### 输出

```
abab
1
ertyqw
3
aaaaa
1
aksala
6
avjsmbpfl
5
p
1```

# 题解

## 作者：Andrewzdm (赞：5)

# [CF1316B String Modification](https://www.luogu.com.cn/problem/CF1316B)
这道题我在参加比赛的时候AC的方法是强行找规律。
然后我按自己找到的规律写代码，就过了……
先把代码给出，读者可通过阅读代码体会我发现的规律。
```cpp
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
struct res
{
	string str;
	int k;
};
res ans[5005];

bool cmp(res x, res y)
{
	if(x.str < y.str)
		return true;
	if(x.str > y.str)
		return false;
	return x.k < y.k;
}

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		string s;
		cin >> s;
		for(int i = 1; i <= n; i++)
		{
			ans[i].k = i;
			string tmp = s;
			string st = tmp.substr(0, i - 1);
			if(i % 2 == n % 2)
				reverse(st.begin(), st.end());
			tmp += st;
			tmp.erase(0, i - 1);
			ans[i].str = tmp;
		}
		sort(ans + 1, ans + n + 1, cmp);
		cout << ans[1].str << endl << ans[1].k << endl;
	}
	return 0;
}
```
时间复杂度 $O(n^2)$

相信大家已经通过阅读程序明白了我发现的规律。
接下来我们来简略地证明一下：

首先我们有一个字符串 $s$ ，
我们可以把它表示为 $s_1s_2s_3\dots s_n$。

然后我们选择一个 $k$ ：
- 经过第一次反转： $s_ks_{k-1}s_{k-2}\dots s_1s_{k+1}s_{k+2}\dots s_n$
观察到之后 $s_k$ 的位置就不会发生变化了。
- 经过第二次反转： $s_ks_{k+1}s_1\dots s_{k-2}s_{k-1}s_{k+2}\dots s_n$
观察到之后 $s_ks_{k+1}$ 的位置都不会发生变化。
- 经过第三次反转： $s_ks_{k+1}s_{k+2}\dots s_2s_1s_{k+3}\dots s_n$
观察到之后 $s_ks_{k+1}s_{k+2}$ 的位置不会再发生变化。

**……**

以此类推，最后反转变换过后的字符串 $s'$ 前 $n-k+1$ 个字符一定是 $s_ks_{k+1}s_{k+2}\dots s_n$ 。

通过观察还可发现， $s$ 中的前 $k-1$ 个字符 $s_1s_2s_3\dots s_{k-1}$ 一定会被搬到 $s'$ 的后半部分，但是方向不确定。

实际上，不难得到，若反转次数为奇数，则最后 $s'$ 的后半部分为$s_{k-1}s_{k-2}s_{k-3}\dots s_1$ ；反之，若反转次数为偶数，则最后 $s'$ 的后半部分为$s_1s_2s_3\dots s_{k-1}$ 。

我们的反转次数是 $n-k+1$ ，所以当且仅当 $n$ 与 $k$ 奇偶性相同时反转次数为奇数。

于是代码就不难理解了。

---

## 作者：xxxr_2024 (赞：1)

# CF1316B String Modification 题解
## 分析
找规律题。

举个例子就知道了。比如说 `ghostwalker` 这个单词翻转的过程如下：
- 翻转长度为 $1$ 时：`ghostwalker`；
- 翻转长度为 $2$ 时：`hostwalkerg`；
- 翻转长度为 $3$ 时：`ostwalkergh`；
- 翻转长度为 $4$ 时：`stwalkerohg`；
- 翻转长度为 $5$ 时：`twalkerghos`；
- 翻转长度为 $6$ 时：`walkertsohg`；
- ……

仔细观察，发现每个字符串翻转后都是原字符串的一部分前缀扔到后面。再仔细观察，当翻转长度为偶数时，扔到后面的前缀是**经过倒置**的。翻转长度为奇数时就是原来的前缀不变。

知道了这个规律，代码就很好写了。

## 代码
码风巨丑，不喜勿喷（

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Raiden
{
    string s, ss, sa, sb;
    int n, ans;
    signed work()
    {
        int t;
        cin >> t;
        while (t--)
        {
            cin >> n >> s;
            int ans = 1;
            string ss = s;
            for (int i = 1; i < n; i++)
            {
            	  //substr用于截取子串，substr(i,j)就是从下标i开始截取j位，substr(i)就是从第i位截取到结尾
                string sa = s.substr(i), sb = s.substr(0, i);
                if (((n - i - 1) & 1) == 0)
                    reverse(sb.begin(), sb.end());
                sa += sb;
                if (sa < ss)
                    ss = sa, ans = i + 1;
            }
            cout << ss << endl;
            cout << ans << endl;
        }
        return 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return Raiden::work();
}
```

---

## 作者：鹤箩芠 (赞：0)

解：对于每一次大反转（即每次$k$) 我们对于原字符串$s$设立一个前缀$t$ ， 即$t = t + s_i$ （$1 \le i\le k - 1$）, 我们发现对于每一次的小翻转，便是将当前$t$的位置$+1$的字符挪到$t$前面 , 然后$t$自身反转....(继续次操作) ， 不难发现：新生成的字符串前$n - k + 1$个必定是$s_{k - 1}\to s_n$ ，剩下就是要考虑$t$是正向放在后面 ， 还是反向放在后面 ， 也就是说 ， $t$他自身反转了几次 ， 不妨设翻转次数为$res$  , 仔细思考可以发现若$res$为偶数 ， 则正着放 ，反之便反转放 。且有$res = n - k +1$ , 这样我们就可以轻松的解决掉这道水题

代码~（我这里初始下标为$0$

```cpp
#include <bits/stdc++.h>
using namespace std ;
int n ;
void solve () {
	cin >> n ;
	string s , t ;
	cin >> s ;	
	pair <string , int> ans ;
	ans = make_pair (s , 1) ;
	for (int k = 1 ; k < n ; k ++) {
		pair <string , int> now ; 
		t = "" ;
		for (int i = k ; i < n ; i ++) t += s[i] ;
		if ((n - k) % 2) for (int i = k - 1 ; i >= 0 ; i --) t += s[i] ;
		else for (int i = 0 ; i <= k - 1 ; i ++) t += s[i] ;
		now= make_pair (t , k + 1) ;
		ans = min (ans , now) ; 
	}
	cout << ans.first << endl << ans.second << endl ; 
}
int main () {
	int t ;
	cin >> t ;
	while (t --) {
		solve () ;
	}
	return 0 ;
}
```


---

## 作者：流绪 (赞：0)

模拟一下几组数据会发现以 k 的长度来翻转，那么就是整个字符串向左移动 k-1 格，那么最前面几个字母就会被放到最后面，且每进行一次翻转，这一段字符串都会翻转，那翻转操作就可以转化为先将字符串左移 k-1 格，然后一共翻转了 n-k 次，如果 n-k 为奇数最终前面的字符串就会翻转过来，反之不会。这样翻转操作就简化为 O(n) 了。然后我们枚举翻转的长度，翻转完比较和答案字符串哪个小就好了。

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 200010
#define ri register int
#define il inline
#define mod 1000000009
#define db() cout << 1 << endl
using namespace std;
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		char a[5010],b[5010],c[5010];//分别为原数组,翻转数组,答案数组
		cin >> n;
		cin >> a;
		for(int i=0;i<=n;i++)
			c[i]=a[i];//初始化答案数组为原数组
		int p=1;
		for(int i=0;i<n-1;i++)//枚举翻转i+1长度,也就是左移i格
		{
			for(int j=0;j<n-i;j++)//先把后面的往前移动
				b[j] = a[j+i];
			if((n-i)%2==0)//看看前面的字符串移动到后面要不要翻转
			{
				int pp=0;
				for(int j=n-i;j<n;j++)
					b[j] = a[pp++];
			}
			else
			{
				int pp = i-1;
				for(int j=n-i;j<n;j++)
					b[j] = a[pp--];
			}
			if(strcmp(b,c) < 0)//更新答案数组
			{
				for(int j=0;j<=n;j++)
					c[j] = b[j];
				p=i+1;
			}
		}
		int pp=0;
		for(int i=n-1;~i;i--)//我把翻转长度为n的另外写了
			b[pp++] = a[i];	 //因为他可以直接翻转整个字符串
		if(strcmp(b,c) < 0)
		{
			for(int i=0;i<=n;i++)
				c[i] = b[i];
			p=n;
		}
		for(int i=0;i<n;i++)
			cout << c[i];
		cout << endl<<p << endl;
	}
  	return 0;
}
```


---

