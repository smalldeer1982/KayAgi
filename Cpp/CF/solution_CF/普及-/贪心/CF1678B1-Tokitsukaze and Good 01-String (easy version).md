# Tokitsukaze and Good 01-String (easy version)

## 题目描述

This is the easy version of the problem. The only difference between the two versions is that the harder version asks additionally for a minimum number of subsegments.

Tokitsukaze has a binary string $ s $ of length $ n $ , consisting only of zeros and ones, $ n $ is even.

Now Tokitsukaze divides $ s $ into the minimum number of contiguous subsegments, and for each subsegment, all bits in each subsegment are the same. After that, $ s $ is considered good if the lengths of all subsegments are even.

For example, if $ s $ is "11001111", it will be divided into "11", "00" and "1111". Their lengths are $ 2 $ , $ 2 $ , $ 4 $ respectively, which are all even numbers, so "11001111" is good. Another example, if $ s $ is "1110011000", it will be divided into "111", "00", "11" and "000", and their lengths are $ 3 $ , $ 2 $ , $ 2 $ , $ 3 $ . Obviously, "1110011000" is not good.

Tokitsukaze wants to make $ s $ good by changing the values of some positions in $ s $ . Specifically, she can perform the operation any number of times: change the value of $ s_i $ to '0' or '1'( $ 1 \leq i \leq n $ ). Can you tell her the minimum number of operations to make $ s $ good?

## 说明/提示

In the first test case, one of the ways to make $ s $ good is the following.

Change $ s_3 $ , $ s_6 $ and $ s_7 $ to '0', after that $ s $ becomes "1100000000", it can be divided into "11" and "00000000", which lengths are $ 2 $ and $ 8 $ respectively. There are other ways to operate $ 3 $ times to make $ s $ good, such as "1111110000", "1100001100", "1111001100".

In the second, third and fourth test cases, $ s $ is good initially, so no operation is required.

## 样例 #1

### 输入

```
5
10
1110011000
8
11001111
2
00
2
11
6
100110```

### 输出

```
3
0
0
0
3```

# 题解

## 作者：_acat_ (赞：3)

此题建议评红

## 题目描述

有一个长度为 $n$ 的 $01$ 串，定义“好的 $01$ 串”为每一个连续的 $0$ 子段或 $1$ 子段的长度都是偶数的 $01$ 串，求把给定的 $01$ 串变为“好的 $01$ 串”的最小操作次数。

## Sol

我们可以采取两个两个的找到方法。

如果 $a_{i} \ne a_{i-1}$，则修改 $a_{i-1}$ 为 $a_{i}$，然后 $cnt+1$。

因为 $n$ **是偶数**，所以不用担心数组越界。

## AC 代码

```cpp
#include<iostream>
#define endl "\n"
using namespace std;
int t,n;
int cnt=0;
char a[300010];
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n;
        cnt=0;
        cin>>a;
        for(int i=1;i<n;i+=2)
        {
            if(a[i]!=a[i-1])
            {
                a[i-1]=a[i];
                cnt+=1;
            }
        }
        cout<<cnt<<endl;
    }
    return 0; 
}
```

---

## 作者：accomplishment (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1678B1)

这是道纯模拟题，大致思路很简单，就是用```vector```数组 $a$ 存储字符串连续的 $0$ 和 $1$ 的个数，举个栗子：

> 10

> 1110011000

此时数组 $a$ 应为：

> 3 2 2 3

存储好数组 $a$，直接模拟，发现数组 $a$ 的某一项 $a_i \equiv 1 \pmod{2}$，直接将 $a_i$ $+1$ 或 $-1$，下一项 $a_{i + 1}$ 对应的 $-1$ 或 $+1$，直到```i = a.size() - 2```结束，因为前面所有项都是偶数，最后一项一定是偶数，最后统计 $+1$ 和 $-1$ 的次数即可，这里我采用 $a_i - 1, a_{i + 1} + 1$ 的方式

注意：因为如果数组 $a$ 的长度为 $1$，```a.size() - 2```为 $-1$，程序就会```RE```，所以要特判一下，而且题目保证 $s$ 的长度为偶数，所以如果数组 $a$ 的长度为 $1$，直接跳过模拟，输出```0```。

$Code: $

```cpp
// Problem: B1. Tokitsukaze and Good 01-String (easy version)
// Contest: Codeforces Round #789 (Div. 2)
// URL: https://codeforces.com/contest/1678/problem/B1
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)
 
/*
 * Author: guzheran @YYXX
 */
 
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
 
#define fi first
#define se second
#define register rg
#define mp make_pair
#define pb push_back
#define pf push_front
 
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)
 
namespace IO {
	
	template <typename type>
	inline void Read (type &theNum) {
	
		char theChar = 0;
		int negative = 0; 
		
		theNum = 0;
		theChar = getchar();
		negative = 1;
		
		while (theChar < '0' || theChar > '9') {
			if (theChar == '-') {
				negative = -1;
			}
			
			theChar = getchar();
		}
		
		theNum = theChar ^ 48;
		
		while ((theChar = getchar()) > '0' - 1 && theChar < '9' + 1) {
			theNum = (theNum << 3) + (theNum << 1) + (theChar ^ 48);
		}
		
		theNum *= negative;
		
	}
	
	template <typename type>
	inline void RecursionWrite (type theNum) {
		
		if (theNum) {
			RecursionWrite(theNum / 10);
			putchar(theNum % 10 + 48);
		}
		
	}
	
	template <typename type1, typename type2>
	inline void Write (type1 theNum, type2 endChar) {
		
		if (!theNum) {
			putchar('0');
		}
		
		if (theNum < 0) {
			putchar('-');
			theNum *= -1;
		}
		
		if (theNum) {
			RecursionWrite(theNum / 10);
			putchar(theNum % 10 + 48);
		}
		
		putchar(endChar);
		
	}
	
}
 
using namespace IO;
 
/* template ends here */
 
int main () {
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int T;
	
	cin >> T;
	
	while (T--) {
		int n, index = 0, cnt = 0, res = 0;
		string s;
		vector<int> list;
		
		cin >> n >> s;
		
		while (index < n) {
			if (s[index] == s[index + 1]) {
				index++;
				cnt++;
				continue;
			}
			
			list.push_back(cnt + 1);
			cnt = 0;
			index++;
		}
		
		if (list.size() > 1) {
			rep (i, 0, list.size() - 2) {
				if (list[i] % 2 == 1) {
					list[i]--;
					list[i + 1]++;
					res++;
				}
			}
		}
		
		cout << res << '\n';
	}
	
	return 0;
	
}
```


---

## 作者：SSqwq_ (赞：1)

## 题意
给定一个长度为 $n$ 的 $01$ 串，定义“好的 $01$ 串”为每一个连续的 $0$ 子段或 $1$ 子段的长度都是偶数的 $01$ 串，求把给定的 $01$ 串变为“好的 $01$ 串”的最小操作次数。保证 $n$ 是偶数。

## 思路
经过分析题意之后不难发现，对于一个 $01$ 串 $S$ ，如果 $S$ 是一个“好的 $01$ 串”，那 $S00$ 和 $S11$ 也是“好的 $01$ 串”。

因此，我们两个两个元素遍历，若相邻的两个元素不同则把它们变为相同的，记录操作次数输出就可以了。由于题目保证了 $n$ 是偶数，所以不用担心会越界。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char a[300001];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		cin>>a;
		int ans=0;
		for(int i=1;i<n;i+=2)//两个两个遍历
		{
			if(a[i]!=a[i-1])
			{
				a[i-1]=a[i];
				ans++;
			}
		}
		printf("%d\n",ans);
	}
	return 0; 
}
```


---

## 作者：Engulf (赞：1)

### 题意

给定 01 字符串 $s$，每次可以选择一个 $i$ 改变 $s_i$。将 $s$ 按照 01 划分成段，问全部段的长度为偶数的最小操作次数。

### 分析

考虑 dp，设 $dp_i$ 表示 $s$ 前 $i$ 个字符的最小操作次数，显然 $i$ 只能为偶数。
换句话说，可以将 $s$ 划分成若干二元组。

若当前组的两个字符不一致，肯定需要修改其中一个字符。

~~就搞定了~~

```cpp
// author: TMJYH09
// create time: 2022/05/08 23:11:09
#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

void solve(){
    string s;
    int n;
    cin>>n>>s;
    int ans=0;
    for(int i=1;i<s.size();i+=2){
        if(s[i-1]!=s[i])ans++;
    }
    cout<<ans<<endl;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：qfpjm (赞：0)

# 题解

- 题目说只要长度为偶数的 $0,1$ 串，所以我们显然会考虑找到那些长度为奇数的串。

- 因为 $n$ 是偶数，所以我们可以采取两个两个的跳。如果当前的字符与上一个字符不同，那么上一个字符所属的串长度为奇数，我们直接将上一个字符修改为当前的字符即可让原来上一个字符所述的串的长度变为偶数，这样推下去，显然是最优的。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int T, n;
char a[300001];

int main()
{
    cin >> T;
    while(T --)
    {
        cin >> n >> a;
        int ans = 0;
        for(int i = 1 ; i < n ; i += 2)
        {
            if(a[i] != a[i - 1])
            {
                a[i - 1] = a[i];
                ans ++;
            }
        }
        printf("%d\n", ans);
    }
    return 0; 
}
```


---

## 作者：Xeqwq (赞：0)

给出如下定义定义：  
1.一段为（值为）连续的 1 或 0 组成（的下标）的区间。  
2.若一段的**长度**为奇数，则称该段为奇数段，反之称为偶数段。

---
方法：  
首先，我们预处理出来每一段的长度。  
然后，我们记录一个状态 $state$ 和所求的数列更改次数 $cnt$，做以下操作：  
1) 若 $state$ 为 0  
1.1 若当前段为奇数段，则更改 $state$ 为 1 ，并 `cnt++`。  
1.2 若当前段为偶数段，则不做更改。  
2) 若 $state$ 为 1  
2.1 若当前段为奇数段，则将 $state$ 改为 0 。
2.2 若当前段为偶数段，则 `cnt++` 。

---

原理：  
首先我们可以得知：肯定不会连着改两个或多个数。  
依题意得，偶数段不用改。  
对于奇数段，一定会改它的前后之一，我们不妨向后改。  
改完这段后面一个数之后，则后面一段的长度发生奇偶变化。  
所以每次遇到了奇数段，我们改变 $state$ ，对于不同的 $state$ 值我们不同处理。  

---

参考代码：

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int t,n;
char c,last;
bool a[200005];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		int div=0,now=0;
		getchar();
		last=getchar();
		for(int i=2;i<=n;i++)
		{
			c=getchar();
			now++;
			if(c!=last)
			{
				a[++div]=cnt&1;
				now=0;
			}
			last=c;
		}
		bool state=0;
		int cnt=0;
		for(int i=1;i<=div;i++)
		{
			if(a[i]) state^=1; 
			if(state) cnt++;
		}
		printf("%d\n",cnt);
	}
    return 0;
}

```

---

## 作者：ttq012 (赞：0)

**Solution**

贪心。

如果一个全 $1$ 或者全 $0$ 的序列的长度为偶数那么就不用管。

否则，如果当前的序列是全 $1$，那么就让当前的序列的最后一个字符变为 $0$。否则就让当前的序列的最后一个字符变为 $1$ 即可。

时间复杂度 $\mathcal O(T\cdot N)$。

**AC Code**

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

int cnt[1000010];

signed main() {
    int T;
    cin >> T;
    while (T --) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int cnt = 0;
        int c = 1;
        for (int i = 1; i < s.size(); i ++) {
            if (s[i] == s[i - 1])
                c ++;
            else {
                if (c & 1) {
                    cnt ++;
                    s[i - 1] = s[i];
                    c = 2;
                }
                else
                    c = 1;
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}

```



---

