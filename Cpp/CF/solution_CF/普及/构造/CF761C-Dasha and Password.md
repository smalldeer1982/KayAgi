# Dasha and Password

## 题目描述

After overcoming the stairs Dasha came to classes. She needed to write a password to begin her classes. The password is a string of length $ n $ which satisfies the following requirements:

- There is at least one digit in the string,
- There is at least one lowercase (small) letter of the Latin alphabet in the string,
- There is at least one of three listed symbols in the string: '\#', '\*', '&'.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761C/cb0ada85db7c7b0388e7b419452d8653e44781e1.png)Considering that these are programming classes it is not easy to write the password.

For each character of the password we have a fixed string of length $ m $ , on each of these $ n $ strings there is a pointer on some character. The $ i $ -th character displayed on the screen is the pointed character in the $ i $ -th string. Initially, all pointers are on characters with indexes $ 1 $ in the corresponding strings (all positions are numbered starting from one).

During one operation Dasha can move a pointer in one string one character to the left or to the right. Strings are cyclic, it means that when we move the pointer which is on the character with index $ 1 $ to the left, it moves to the character with the index $ m $ , and when we move it to the right from the position $ m $ it moves to the position $ 1 $ .

You need to determine the minimum number of operations necessary to make the string displayed on the screen a valid password.

## 说明/提示

In the first test it is necessary to move the pointer of the third string to one left to get the optimal answer.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761C/89086e09018b91f648aacd8cd5238770a033e69b.png)In the second test one of possible algorithms will be:

- to move the pointer of the second symbol once to the right.
- to move the pointer of the third symbol twice to the right.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF761C/3400aa9e98cacdc13b42e316e367bed427854028.png)

## 样例 #1

### 输入

```
3 4
1**2
a3*0
c4**
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 5
#*&#*
*a1c&
&q2w*
#a3c#
*&#*&```

### 输出

```
3
```

# 题解

## 作者：菲斯斯夫斯基 (赞：2)

## CF761C Dasha and Password 题解

注意到题目的 $n\le50$ 和 $m\le50$ 就很明显是暴力枚举了。

分别枚举提供数字、字母、其它符号是哪个字符串提供的，然后分别计算每个的步数，求和，最后取最小值即可。

注意的是因为是一个环，所以计算步数的时候会有不同。

**代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=1e9;
string s[60]; 
int f(int l,int r)
{
	return min(r-l,m-r+l);
}//计算步数 
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>s[i];
	for(int i=1;i<=n;i++)//枚举数字 
	{
		int x=1e9;
		for(int j=0;j<m;j++)
			if(s[i][j]>='0'&&s[i][j]<='9')
				x=min(x,f(0,j));
		for(int j=1;j<=n;j++)//枚举字母 
		{
			if(i==j)continue;
			int y=1e9;
			for(int k=0;k<m;k++)
				if(s[j][k]>='a'&&s[j][k]<='z')
					y=min(y,f(0,k));
			for(int k=1;k<=n;k++)//枚举其它符号 
			{
				int z=1e9;
				if(i==k||j==k)continue;
				for(int l=0;l<m;l++)
					if(s[k][l]=='#'||s[k][l]=='*'||s[k][l]=='&')
						z=min(z,f(0,l)),ans=min(ans,x+y+z);//更新答案 
			}
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：ALANYQ (赞：1)

~~我恨暴力枚举……~~

这道题最重要的关键是：环形的字符串！  
当我们枚举第几个字符串有数字，字母，符号，紧接着要计算步数时，必须得从头尾考虑！

然后……这道题就很简单了……

## 代码实现 （main）

- 枚举哪个字符串提供数字。  
- 枚举哪个字符串提供字母。
- 枚举哪个字符串提供符号。  
- 若三个字符串有重复 则 `continue`。  
- 用 `while` 寻找第一个字符串中最近的数字。  
- 用 `while` 寻找第二个字符串中最近的字母。  
- 用 `while` 寻找第三个字符串中最近的符号。  
- 将答案加起来。  
- 若此时的答案小于答案，更新答案。

---

## 作者：OIerZhang (赞：1)

# [CF761C Dasha and Password](https://www.luogu.com.cn/problem/CF761C) 题解

~~大水题。~~

这道题乍一看好像非常难，但实际上难度可能连$\small\textcolor{#FE4C61}{\textrm{ 红题 }}$都不到。

细心的 dalao 肯定发现了隐藏在一大串英文中的 $( 3 \le n \le 50, 1 \le m \le 50 )$ ，如此小的范围，用 **暴力** 就能解决了。

## 思路

既然是暴力，这道题就很好解决了。

1. 分别枚举提供字母、数字和符号对应的字符串。

1. 计算字符串内对应的字符需要的光标移动次数，取最小值。

1. 三种字符（字母、数字和符号）光标移动次数最小值之和即是答案。

时间复杂度 $O(n^4)$ ，无需考虑超时问题。

## 代码

题解里面主要是 [枚举一种类型算一次对应的步数](https://www.luogu.com.cn/blog/XufromGD-FS/solution-CF761C) 和 [先枚举三种类型再一起算步数](https://www.luogu.com.cn/blog/CatHome/solution-cf761c) 两种解法，个人推荐第一种，比较好理解。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

string s[55];
int n, m, ans = 2e9; // 注意：ans用来求最小值，需要赋值成无穷大

// 判断是否为字母、数字和其他字符
bool isletter(char c)
{
    return ('a' <= c && c <= 'z');
}
bool isnumber(char c)
{
    return ('0' <= c && c <= '9');
}
bool issymbol(char c)
{
    return (c == '#' || c == '*' || c == '&');
}
int dis(int s, int f) // 计算步数
{
    return min(f - s, m - (f - s));
    // 注意：这里是一个环，要计算向前走和向后走这两种情况中的最小值
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    for (int i = 1; i <= n; i++) // 枚举提供字母的密码环
    {
        int mn1 = 2e9;
        for (int j = 0; j < m; j++) // 枚举第i个密码环中光标移动到字母的最小移动次数
            if (isletter(s[i][j]))
                mn1 = min(mn1, dis(0, j));

        for (int j = 1; j <= n; j++) // 枚举提供数字的密码环
        {
            if (i == j) // 已经选过的密码环不能再选了
                continue;
            int mn2 = 2e9;
            for (int k = 0; k < m; k++)
                if (isnumber(s[j][k]))
                    mn2 = min(mn2, dis(0, k));

            for (int k = 1; k <= n; k++) // 枚举提供符号的密码环
            {
                if (i == k || j == k)
                    continue;
                int mn3 = 2e9;
                for (int l = 0; l < m; l++)
                    if (issymbol(s[k][l]))
                        mn3 = min(mn3, dis(0, l));

                ans = min(ans, mn1 + mn2 + mn3); // 计算最小值之和，更新答案
            }
        }
    }
    cout << ans;
    return 0; // 华丽结束！
}

```

---

## 作者：Ninelife_Cat (赞：1)

由于 $n$ 和 $m$ 的范围较小，所以可以考虑暴力枚举。

枚举 $i$ , $j$ , $k$ 三个字符串，强制在 $i$ 中选数字，$j$ 中选字母，$k$ 中选符号。

接下来的问题就是选择字符串中的哪个字符最优，那就直接扫一遍字符串，在所有可选的字符中取最小值就行了。

时间复杂度 $O(n^3m)$。

核心代码：

```cpp
const int N=101+10;
int n,m,ans=inf;
char a[N][N];
signed main()
{
	cin>>n>>m;
	for(ri int i=1;i<=n;++i)
		for(ri int j=1;j<=m;++j)
			cin>>a[i][j];
	for(ri int i=1;i<=n;++i)
		for(ri int j=1;j<=n;++j)
			if(i!=j) for(ri int k=1;k<=n;++k)//枚举字符串
				if(i!=j&&j!=k)
				{
					ri int res=inf,sum=0;
					for(ri int l=1;l<=m;++l)
						if(a[i][l]>='0'&&a[i][l]<='9') res=min(res,min(l-1,m-l+1));//注意字符串是环形的
					sum+=res;res=inf;
					for(ri int l=1;l<=m;++l)
						if(a[j][l]>='a'&&a[j][l]<='z') res=min(res,min(l-1,m-l+1));
					sum+=res;res=inf;
					for(ri int l=1;l<=m;++l)
						if(a[k][l]=='#'||a[k][l]=='*'||a[k][l]=='&') res=min(res,min(l-1,m-l+1));
					sum+=res;ans=min(ans,sum);
				}
	cout<<ans;
	return 0;
}
```

---

## 作者：__asdf__ (赞：0)

这道题说要让数字、小写字母、特殊符号三种字符里面每种都有至少一个，所以我们可以枚举哪三个字符分别为数字、小写字母、特殊符号，并提前预处理出将每个字符变为这三种的代价，具体一点，设：

$f_{0, i}$ 表示第 $i$ 位变为数字的最小代价。

$f_{1, i}$ 表示第 $i$ 位变为小写字母的最小代价。

$f_{2, i}$ 表示第 $i$ 位变为特殊字符的最小代价。

具体转移见代码：

```cpp
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

#define int long long

const int N = 60;

int n, m;
string s[N];
int f[3][N];  // 0 -> 数字，1 -> 小写字母，2 -> 特殊字符

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    s[i] = " " + s[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 3; j++) {
      f[j][i] = 0x3f3f3f3f;
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int dist = min(j - 1, m - j + 1);  // 这个字符串需要光标移动的最小距离
      if ('0' <= s[i][j] && s[i][j] <= '9') {  // 数字
        f[0][i] = min(f[0][i], dist);
      } else if ('a' <= s[i][j] && s[i][j] <= 'z') {  // 小写字母
        f[1][i] = min(f[1][i], dist);
      } else if (s[i][j] == '#' || s[i][j] == '*' || s[i][j] == '&') {  // 特殊字符
        f[2][i] = min(f[2][i], dist);
      }
    }
  }
  int ans = 0x3f3f3f3f;
  for (int i = 1; i <= n; i++) {  // 数字
    for (int j = 1; j <= n; j++) {  // 小写字母
      for (int k = 1; k <= n; k++) {  // 特殊字符
        if (i == j || j == k || i == k) {
          continue;
        }
        ans = min(ans, f[0][i] + f[1][j] + f[2][k]);
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：xuyifei0302 (赞：0)

因为有 $n,m \le 50$，所以我们直接暴力。设 $dp_{i,j,k,k1}$ 表示前 $i$ 排，选中了 $j$ 个数字，$k$ 个小写字符，$k1$ 个特殊字符。

+ 若我们这一步选择了数字，就从 $dp_{i - 1,j - 1,k,k1}$ 转移，加上当前指向的步骤。

+ 若我们这一步选择了小写字母，就从 $dp_{i - 1,j,k - 1,k1}$ 转移，加上当前指向的步骤。

+ 若我们这一步选择了特殊字符，就从 $dp_{i - 1,j,k,k1 - 1}$ 转移，加上当前指向的步骤。

那么最后答案就是 $dp_{n,i,j,k}$ 中的最小值。

下面是代码环节：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int INF = 1e16;
int n, m, v[5][55], dp[55][55][55][55];
string s;
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= 3; i ++) {
		for (int j = 1; j <= n; j ++) {
			v[i][j] = INF;
		}
	}
	for (int i = 0; i <= n; i ++) {
		for (int j = 0; j <= n; j ++) {
			for (int k = 0; k <= n; k ++) {
				for (int k1 = 0; k1 <= n; k1 ++) {
					dp[i][j][k][k1] = INF;
				}
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		cin >> s;
		s = " " + s;
		for (int j = 1; j <= m; j ++) {
			if (s[j] >= '0' && s[j] <= '9') {
				v[1][i] = min(v[1][i], min(j - 1, m - j + 1));
			} else if (s[j] >= 'a' && s[j] <= 'z') {
				v[2][i] = min(v[2][i], min(j - 1, m - j + 1));
			} else {
				v[3][i] = min(v[3][i], min(j - 1, m - j + 1));
			}
		}
	}
	dp[0][0][0][0] = 0;
	for (int i = 1; i <= n; i ++) {
		for (int j = 0; j <= n; j ++) {
			for (int k = 0; k <= n; k ++) {
				for (int k1 = 0; k1 <= n; k1 ++) {
					if (v[1][i] != INF && j) {
						dp[i][j][k][k1] = min(dp[i][j][k][k1], dp[i - 1][j - 1][k][k1] + v[1][i]);
					}
					if (v[2][i] != INF && k) {
						dp[i][j][k][k1] = min(dp[i][j][k][k1], dp[i - 1][j][k - 1][k1] + v[2][i]);
					}
					if (v[3][i] != INF && k1) {
						dp[i][j][k][k1] = min(dp[i][j][k][k1], dp[i - 1][j][k][k1 - 1] + v[3][i]);
					}
				}
			}
		}
	}
	int minn = INF;
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			for (int k = 1; k <= n; k ++) {
				minn = min(minn, dp[n][i][j][k]);
			}
		}
	}
	cout << minn;
	return 0;
}
```

---

## 作者：rainbow_cat (赞：0)

预处理 $nd_i,na_i,ns_i$ 表示将第 $i$ 个字符串调为数字，字母，特殊符号的次数即可。   
暴力枚举每一种字符出现在哪一个字符串里，剩下的 $n-3$ 个串就不用管。    
时间复杂度为 $O(n^3)$。
```
#include<bits/stdc++.h>
using namespace std;
int n,m,ans=0x7f7f7f7f,nd[60],na[60],ns[60];
char c[60][60];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>c[i][j];
	for(int i=1;i<=n;i++)
	{
		nd[i]=na[i]=ns[i]=100;
		for(int j=1;j<=m;j++)
		{
			if(isdigit(c[i][j]))nd[i]=min(nd[i],min(j-1,m-j+1));
			else if(isalpha(c[i][j]))na[i]=min(na[i],min(j-1,m-j+1));
			else ns[i]=min(ns[i],min(j-1,m-j+1));
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=n;k++)
			{
				if(i==j||i==k||j==k)continue;
				ans=min(ans,nd[i]+na[j]+ns[k]);
			}
		}
	}
	cout<<ans;
	return 0;
}
```

---

