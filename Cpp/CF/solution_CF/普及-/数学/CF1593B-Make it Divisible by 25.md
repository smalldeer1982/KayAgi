# Make it Divisible by 25

## 题目描述

给定一个**正整数** $n$，你可以对它进行操作。

对于每一次操作，你可以将这个正整数其中的**任意**一个数位删去，之后这个数剩下的左右两边会相接。

特别地：

- 如果一个数仅剩下一个数位，则不能再对它进行操作；
- 如果一个操作之后的数包含前导零，则这些前导零会被一并删除。

例如：

- 将 $32925$ 的第 $3$ 位删除后，它会变成 $3225$；
- 将 $20099050$ 的第 $1$ 位删除后，它会变成 $99050$（两个前导零被一并删除了）。

请你求出，最少经过多少次操作之后，可以得到一个能被 $25$ 整除的**正整数**。

## 说明/提示

- $1 \le t \le 10^4$；
- $25 \le n \le 10^{18}$。

Translated by @BurningEnderDragon, 2021.10.14

## 样例 #1

### 输入

```
5
100
71345
3259
50555
2050047```

### 输出

```
0
3
1
3
2```

# 题解

## 作者：Coros_Trusds (赞：3)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/15409172.html)

$\rm upd~on~2021/10/17:$ 修改了整体排版，更改了证明。

# 题目大意

有 $T$ 组数据。

对于每组数据：

给定一个整数，求出你至少需要删除该整数的几个数字来使这个整数变成 $25$ 的倍数？

# 题目分析

**结论：任一个 $25$ 的正整数倍数的结尾为 `00` 或 `25` 或 `50` 或 `75`。**

证明：

令一个 $25$ 的倍数的数为 $x$。

先考虑 $0\le x \le100$ 的情况，符合条件的数有 $25,50,75$ 和 $100$。

继续下去，用数学归纳法不难去证明。

----

我们把 $00$、$25$、$50$、$75$ 这四个数存入一个二维字符串，**并称为倍数串。**

在输入数时，可以也用字符串读入，这样方便比较。

如果比对得上，那么立即匹配下一个倍数串，在所有值中取最小值。

----
剩下的看一下代码。

# 代码

```cpp
//2021/10/13

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <cstdio>

#include <string>

#include <algorithm>

#define int long long

#define enter() putchar(10)

#define debug(c,que) cerr<<#c<<" = "<<c<<que

#define cek(c) puts(c)

#define blow(arr,st,ed,w) for(register int i=(st);i<=(ed);i++)cout<<arr[i]<<w;

namespace Newstd
{
	inline int read()
	{
		char c;
		bool flag=false;
		while((c=getchar())<'0' || c>'9')
		{
		    if(c=='-') flag=true;
		}
		int res=c-'0';
		while((c=getchar())>='0' && c<='9')
		{
		    res=(res<<3)+(res<<1)+c-'0';
		}
		return flag?-res:res;
	}
	inline void print(int x)
	{
		if(x<0)
		{
			putchar('-');x=-x;
		}
		if(x>9)
		{
			print(x/10);
		}
		putchar(x%10+'0');
	}
}

using namespace Newstd;

using namespace std;

string tmp[5];

inline void solve(string str)
{
	int ans=str.size(),len=str.size();
	
	for(register int i=0;i<=3;i++)
	{
		int idx=1;
		
		for(register int j=len-1;j>=0;j--)
		{
			if(tmp[i][idx]==str[j])
			{
			    idx--;
			}
			
			if(idx==-1)
			{
			    ans=min(ans,len-j-2);
			    
			    break;
			}
		}
	}
	
	cout<<ans<<'\n';
}

#undef int

int main(void)
{
	#define int long long
	
	std::ios::sync_with_stdio(false);
	
	tmp[0]="00";
	
	tmp[1]="25";
	
	tmp[2]="50";
	
	tmp[3]="75";
	
	int T;
	
	cin>>T;
	
	while(T--)
	{
		string str;
		
		cin>>str;
		
		solve(str);
	} 
	
	return 0;
}
```

---

## 作者：ttq012 (赞：2)

这一道题是一个数学题。

为了能够被 $25$ 整除，我们一定要将答案的后面两位置为 $25, 50, 75, 00$ 中的一个。

我们可以判断一下，答案的末尾是以 $5$ 结尾的（包含 $25$ 和 $75$ 的）需要删掉的数字的个数，或者以 $0$ 结尾的 （包含 $50$ 和 $00$ 的）需要删掉的数字的个数。

答案就是这两种情况需要删掉的数字的个数的最小值。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t --)
    {
        string s;
        cin >> s;
        int ans1 = 0, ans2 = 0;
        int n = s.length();
        // ans1代表 转换成为 25/75 需要使用的次数
        // ans2代表 转换成为 50/00 需要使用的次数
        for (int i = n - 1; i >= 0; i --)
            // 一定要从后往前遍历！
        {
            if (s[i] != '5')
                ans1 ++; // 需要继续删除数字
            else
            {
                for (int j = i - 1; j >= 0; j --)
                {
                    if (s[j] == '2' || s[j] == '7')
                        // 因为 25/75 在5的前面的位置，是只有 2/7 的
                        break;
                    else
                        ans1 ++; // 还需要继续删除数字。
                }
                break;
            }
        }
        for (int i = n - 1; i >= 0; i --)
            // 后面和前面的是基本一样的
        {
            if (s[i] != '0')
                ans2 ++;
            else
            {
                for (int j = i - 1; j >= 0; j --)
                    if (s[j] == '0' || s[j] == '5')
                        // 因为题目保证没有前导零，所以 '00' 这种情况是不会出现的。
                        break;
                    else
                        ans2 ++;
                break;
            }
        }
        int ans = min(ans1, ans2); // 答案是 末尾是 25/75 的和末尾是 50/00 中需要删除的数的个数最小的那一个
        cout << ans << endl;
    }
    return 0;
}

```


---

## 作者：wheneveright (赞：1)

[lnk CF1593B Make it Divisible by 25](https://www.luogu.com.cn/problem/CF1593B)

## 解析

一个数被 $25$ 整除只有四种情况：

- 该数字末尾两位为 `00`
- 该数字末尾两位为 `50`
- 该数字末尾两位为 `75`
- 该数字末尾两位为 `25`

然后只要找最后面的字串属于这四个之一的。

考虑一个好写的实现方式：

将其分为最后一位为 `0` 和 `5` 两种。

然后写两个函数，先找到 `0` 或者 `5`，然后再找对应的十位上的字符。

因为写了一个 `solve` 函数以后只要复制一遍改三个字符就好了，所以写起来是挺快的，逻辑也很清晰。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

struct reader {
	template <typename Type>
	reader & operator >> (Type & ret) {
		int f = 1; ret = 0; char ch = getchar ();
		for (;!isdigit (ch); ch = getchar ()) if (ch == '-') f = -f;
		for (; isdigit (ch); ch = getchar ()) ret = (ret * 10) + ch - '0';
		ret *= f; return * this;
	}
} fin;

int T; long long n, m;
int x, y, a, b;

int solve1 () {
	m = n; x = y = -1;
	for (int i = 0; m; i++, m /= 10)
		if (m % 10 == 5) { x = i, m /= 10; break ; }
	for (int i = 0; m; i++, m /= 10)
		if (m % 10 == 7 || m % 10 == 2) { y = i; break ; }
	if (x != -1 && y != -1) return x + y;
	else return 114514;
}
int solve2 () {
	m = n; x = y = -1;
	for (int i = 0; m; i++, m /= 10)
		if (m % 10 == 0) { x = i, m /= 10; break ; }
	for (int i = 0; m; i++, m /= 10)
		if (m % 10 == 0 || m % 10 == 5) { y = i; break ; }
	if (x != -1 && y != -1) return x + y;
	else return 114514;
}

int main () {
	fin >> T;
	while (T--) {
		fin >> n; m = n;
		a = solve1 (); b = solve2 ();
		if (a > b) swap (a, b);
		printf ("%d\n", a == -1 ? b : a);
	}
	return 0;
}
```

---

## 作者：sycqwq (赞：1)

__题意：__

给你一个数 $n$ ，问从 $n$ 中最少删除几个数使 $n$ 被 $25$ 整除。

__思路：__

因为 $25$ 可以整除 $100$ ，所以我们只需要考虑最后两位数。

而只有末尾为 $00,25,50,75$ 的数，才能被 $25$ 整除。

所以我们只需要暴力枚举删除，使得末尾是这几个数就行了。

__代码__

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
char a[1005];
signed main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        
        cin>>a+1;
        int s=0,ans=INT_MAX;
        int n=strlen(a+1);
        int l=0,r=0;
        for(int i=n;i>=1;i--)//00的情况
        {
            if(a[i]=='0')
            {
                if(!l)
                    l=i;
                else
                {
                    r=i;
                    break;
                }
            }
        }
        if(r&&l)
            ans=min(ans,n-l+l-r-1);
        l=r=0;
        for(int i=n;i>=1;i--)//25的情况
        {
            if(a[i]=='5'&&!l)
            {
                l=i;
            }
            if(a[i]=='2'&&l)
            {
                r=i;
                break;
            }
        }
        if(r&&l)
        {
            ans=min(ans,n-l+l-r-1);
        }
        l=r=0;
        for(int i=n;i>=1;i--)//50的情况
        {
            if(a[i]=='0'&&!l)
            {
                l=i;
            }
            if(a[i]=='5'&&l)
            {
                r=i;
                break;
            }
        }
        if(r&&l)
            ans=min(ans,n-r-1);
        l=r=0;
        for(int i=n;i>=1;i--)//75的情况
        {
            if(a[i]=='5'&&!l)
                l=i;
            if(a[i]=='7'&&l)
            {
                r=i;
                break;
            }
        }
        // cout<<l<<' '<<r<<' '<<n<<endl;
        if(r&&l)
            ans=min(ans,n-r-1);
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：feicheng (赞：1)

## B. Make it Divisible by 25



### Task

给定整数 $n$，求出最少删去其中的几个数能使 $n$ 被 $25$ 整除（不含前导 $0$，即如果给 $2005$ 删去 $2$ 会变成 $5$）。

数据保证有解，多测。 

**限制：**$25\le n\le 10^{18},1\le t\le 10^4$。

### Solution

考虑一个数能被 $25$ 整除，当且仅当它的后两位数为 $25,50,75,00$，所以我们可以枚举是否出现这样的两位数（注意这里的两位数是需要有序的，其实很好想，你不可能把 $5,2$ 调换位置）。

时间复杂度：$\mathcal O(t\log^2n)$

---

## 作者：智子 (赞：0)

## 题意

输入一个正整数 $n$，删去若干位数使其能被 25 整除，求最少要删去多少位数字。

数据范围：$25 \leq n \leq 10^{18}$

## 思路

25 的倍数的特征很简单：末尾两位数是 00、25、50、75，所以我们可以考虑进行贪心：

从最后一位出发，找到最低位的 0 和最低位的 5，记录为第 $p$ 位和第 $q$ 位。

然后再从第 $p$ 位出发，向左找到遇到的第一个 0 或 5，将这两位后面的所有数都删去，更新答案；从第 $q$ 位出发，向左找到遇到的第一个 2 或 7，将这两位后面的所有数都删去，更新答案。

## 代码

代码实现比较简单，但要注意细节。

```cpp
#include<iostream>
using namespace std;

const int MAXN = 100 + 5;

int a[MAXN];
int len = 0;

int main() {
    int T;

    cin >> T;
    while(T--) {
        long long n;

        cin >> n;
        len = 0;
        long long t = n;
        while(t != 0) {
            a[++len] = t % 10;
            t /= 10;
        }
        int p = len, q = len, ans = len;
        for(int i = len; i >= 1; i--) {
            if(a[i] == 0) {
                p = i;
            } else if(a[i] == 5) {
                q = i;
            }
        }
        for(int i = p + 1; i <= len; i++) {
            if(a[i] == 0 || a[i] == 5) {
                ans = min(ans, i - 2);
            }
        }
        for(int i = q + 1; i <= len; i++) {
            if(a[i] == 2 || a[i] == 7) {
                ans = min(ans, i - 2);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：happy_dengziyue (赞：0)

### 1 思路

很明显，一个能被 $25$ 整除的数，有四种：

+ 个位为 $5$，十位为 $2$；

+ 个位为 $5$，十位为 $7$；

+ 个位十位均为 $0$；

+ 个位为 $0$，十位为 $5$。

首先考虑个位为 $5$ 的情况。设这种情况下的答案为 $ans_1$。

首先找到最低位的 $5$ 的位置，设为 $l$，再去找位置比它高的 $2$ 或 $7$，设为 $r$。

如果满足不了要求，直接给 $ans_1$ 赋一个 $inf$。否则，$ans_1$ 为 $r-2$，指除了 $l$ 位和 $r$ 位以外的全删了。

然后考虑个位为 $0$ 的情况，设这种情况下的答案为 $ans_2$。

首先找到最低位为 $0$ 的位置，设为 $l$，再去找位置比它高的 $0$ 或 $5$，设为 $r$。

如果满足不了要求，则 $ans_2$ 为 $n$ 的位数；否则为 $r-2$，意义同上。

在 $ans_1$ 和 $ans_2$ 中取最小值即可。

### 2 代码与记录

```cpp
#include<cstdio>
using namespace std;
int t;
long long n;
int a[25];
int ai;
int l,r;
int ans1,ans2;
int mi(int a,int b){
	return a<b?a:b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1593B_2.in","r",stdin);
	freopen("CF1593B_2.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%lld",&n);
		ai=0;
		while(n){
			a[++ai]=n%10;
			n/=10;
		}
		for(l=1;l<=ai;++l){
			if(a[l]==5)break;
		}
		for(r=l+1;r<=ai;++r){
			if(a[r]==2||a[r]==7)break;
		}
		if(r>ai)ans1=0x3f3f3f3f;
		else ans1=r-2;
		for(l=1;l<=ai;++l){
			if(a[l]==0)break;
		}
		if(l>ai)ans2=ai;
		else{
			for(r=l+1;r<=ai;++r){
				if(a[r]==0||a[r]==5)break;
			}
			if(r>ai)ans2=ai;
			else ans2=r-2;
		}
		printf("%d\n",mi(ans1,ans2));
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/59838974)

By **dengziyue**

---

