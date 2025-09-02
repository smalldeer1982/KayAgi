# Expensive Number

## 题目描述

一个正整数 $n$ 的代价被定义为数字 $n$ 除以其各位数字之和的结果。

例如，数字 $104$ 的代价为 $\frac{104}{1 + 0 + 4} = 20.8$，而数字 $111$ 的代价为 $\frac{111}{1 + 1 + 1} = 37$。

给定一个不含前导零的正整数 $n$。你可以从数字 $n$ 中删除任意数量的数字（包括不删除），使得剩下的数字至少包含一个数字且严格大于零。剩下的数字不能重新排列。这样操作后，你可能会得到一个包含前导零的数字。

例如，给定数字 $103554$。如果你决定删除数字 $1$、$4$ 和一个数字 $5$，最终得到的数字是 $035$，其代价为 $\frac{035}{0 + 3 + 5} = 4.375$。

你需要删除的最少数字数量是多少，才能使得剩余数字的代价尽可能小？

## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
666
13700
102030
7```

### 输出

```
2
4
3
0```

# 题解

## 作者：zhangli828 (赞：0)

## 题目大意
给你一个字符串 $n$，你要删掉最少的数使得 $\frac{n}{S(n)}$ 最小（$S(n)$ 为 $n$ 的数位和）。
## 题目解法
我们发现 $n$ 一定大于等于 $S(n)$，于是 $\frac{n}{S(n)}$ 的最小值一定是 $1$。我们发现如果 $x$ 前面多了前导零，$\frac{n}{S(n)}$ 的值不会变，所以我们要删掉除了最后一个非零数之前的所有非零的数。但是我们发现如果 $n$ 的后面加上了一个 $0$ 那么 $\frac{n}{S(n)}$ 会变成原来的 $10$ 倍，所以我们还要把最后一个非零数后面的 $0$ 全部删掉。
## 题目代码
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int t, w, ans;
string s;

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  for (cin >> t; t--; ans = 0) {
    cin >> s;
    for (w = s.size() - 1; s[w] == '0'; w--, ans++);  // 求出最后一个非零数位置以及其后面的 0 的数量
    for (int i = 0; i < w; i++) {
      ans += s[i] != '0';  // 求出最后一个非零数之前的所有非零的数的数量
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：Andy1101 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF2093B)
# 思路
不难发现，一个数的最小花费一定为 $1$。所以我们只需要删除除了前导 $0$ 和最低位的非 $0$ 数的数之外的所有数即可。换句话说，我们只需要保留前导 $0$ 和唯一一个非 $0$ 数的数。
# AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin >>t;
	while(t--)
	{
		string s;
		cin >>s;
		int len=s.size();
		bool flag=1;
		int cnt=0;
		for(int i=len-1;i>=0;i--)
		{
			if(flag)
			{
				if(s[i]=='0') cnt++;
				else flag=0;
			}
			else
			{
				if(s[i]!='0') cnt++;
			}
		}
		cout <<cnt<<'\n';
	}
	return 0;
}

```

---

## 作者：NEKO_Daze (赞：0)

[洛谷CF2093B](https://www.luogu.com.cn/problem/CF2093B) || [CodeForces 2093 B](https://codeforces.com/contest/2093/problem/B)

### 简要题意
定义一个数 $n=\overline{a_1a_2\cdots a_k}$ 的花费为 $\frac{\overline{a_1a_2\cdots a_k}}{a_1+a_2+\cdots+a_k}$。对其进行若干次操作，每次操作删除其中一位数，求使其花费最小的最少操作数。最多删除 $k-1$ 个数位且最后得到的数必须大于  $0$。

### 思路
当只有一个非 $0$ 数位，即 $n=\overline{a} >0$ 时，花费为 $\frac{a}{a}=1$，容易证得此为最小花费。因此对于所有数，最小花费一定为 $1$。我们只需要在此基础上保留不影响该花费的数位，以最小化操作数。

我们选取最后一个非零数位 $a_{end}$ 为分界点，对两边的数进行分类讨论：

* 当 $i < end$ 时，若 $a_i$ 不为 $0$，保留后花费必然增加，所以必须删除。在删除所有不为 $0$ 的数后，所有前面的 $0$ 变为前导零，并不会增加花费，不必删除。
* 当 $i>end$ 时，所有数都是 $0$，每有一个 $0$ 就会使分子变大，而分母不变，因此也必须删除。

综上，我们删除 $a_{end}$ 前所有不为 $0$ 的数位，删除 $a_{end}$ 后所有的数位。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
string s;
int main()
{
    cin >>t;
    while (t--)
    {
        cin >> s;
        int cnt = 0, end = s.length() - 1;
        for (int i = s.length() - 1; i >= 0; i--)
        {
            if (s[i] != '0') {end=i;break;}
        }
        for (int i = 0; i < s.length(); i++)
        {
            if (i==end) continue;
            if (s[i] != '0' && i < end) cnt++;
            if (s[i] == '0' && i > end) cnt++;
        }
        cout << cnt << endl;
    }
}
```

---

## 作者：IGpig (赞：0)

## CF2093B

### Solution

可以发现，只要想删，一定可以做到把除了前导零和唯一一个非零数的数全部删了，此时的值就是唯一一个数加上前导零除以它自己也就是 $1$。

所以从后往前找到第一个非零的位置，后面的零全都删掉，前面保留，个数即为答案。

### Code

~~~cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
string s;
LL n,ans,t,loc;
int main(){
    cin>>t;
    while(t--){
        ans=0;
        cin>>s;
        n=s.size();
        s=' '+s;
        for(int i=n;i>=1;i--){
            if(s[i]>'0'){
                loc=i;
                break;
            }
        }
        for(int i=1;i<loc;i++)if(s[i]>'0') ans++;
        cout<<n-loc+ans<<endl;
    }
    return 0;
}
~~~

---

## 作者：cwxcplh (赞：0)

~~我又来水题解了……~~

**题目大意：** 给一个数字，已知这个数字 $\overline{a_1a_2a_3a_4\dots}$ 的代价为 $\cfrac{\overline{a_1a_2a_3a_4\dots}}{a_1+a_2+a_3+a_4\dots}$，求当这个数变为最小代价所删减的最少数字个数（允许有前导 $0$）。

首先我们要思考这两个问题：最小代价为多少？怎样变成最小代价？

我们先来考虑第一个问题。这个问题的答案很好想，就是 $1$，因为当这是一个一位数时，分子分母的值都一样，那除下来不就是 $1$ 了（当然这个一位数肯定不是 $0$，不然你试试看）。

至于第二个问题，其实答案早就出来了：构一位数。因为允许有前导 $0$，所以我们只需要把当前某个位数的高位中不是 $0$ 的数全部删掉，而把后面的数全部删掉就行了。那我们应该找哪一位呢？

后面的部分全部都会被删掉，没什么优化的余地。而前面的部分只会删不是 $0$ 的，那我们尽可能的把 $0$ 放在前面，那后面就会少删一点 $0$，前面又不会删 $0$，所以我们要找的那一位其实就是从低到高第一个不是 $0$ 的那一位。

OK，整个思路非常完美，可以写代码了！

**代码实现：**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,ans;
string s;
signed main()
{
    cin>>t;
    while(t--)
    {
        cin>>s;//记得字符串输入哦。
        int n=s.size(),t=0;
        for(int i=n-1;i>=0;i--)
        {
            if(s[i]!='0')
            {
                t=i;
                ans+=n-1-i;
                break;
            }
        }
        for(int i=0;i<t;i++)
        {
            if(s[i]!='0')
            {
                ans++;
            }
        }
        cout<<ans<<endl;
        ans=0;
    }
    return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[洛谷](https://www.luogu.com.cn/problem/CF2093B)

[CF](https://codeforces.com/problemset/problem/2093/B)

题目大意：设一个数 $x=\overline{a_1a_2\ldots a_n}$，则其价值为 $\dfrac{\overline{a_1a_2\ldots a_n}}{a_1+a_2+\ldots+a_n}$，求从 $x$ 中最少删去多少位可以使其价值最小。

首先我们进行一个转换：

$$\dfrac{\overline{a_1a_2\ldots a_n}}{a_1+a_2+\ldots+a_n}=\dfrac{a_1\times10^{n-1}+a_2\times10^{n-2}+\ldots+a_n}{a_1+a_2+\ldots+a_n}\ge\dfrac{a_1+a_2+\ldots+a_n}{a_1+a_2+\ldots+a_n}=1$$

当且仅当 $a_1=a_2=\ldots=a_{n-1}=0$ 且 $a_n\neq0$ 时，即 $x$ 为可能有前导零的一位数时等号成立。所以 $x$ 的价值的最小值一定是 $1$。

我们找到 $x$ 中的最后一个非 $0$ 的数和它前面所有的 $0$，保留这些数即可。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
pii mkp(int x, int y){pii p; p.first = x, p.second = y; return p;}
int t, pos, n, ans; char s[2001];
signed main(){
	scanf("%lld", &t);
	while (t--){
		scanf("%s", s + 1);
		n = strlen(s + 1), ans = 1;
		for (int i = n; i >= 1; i--)
			if (s[i] != '0'){pos = i; break;}//pos为最后一个非0数
		for (int i = pos; i >= 1; i--) if (s[i] == '0') ans++;//保留pos前面所有的0
		printf("%lld\n", n - ans);
	}
	return 0;
}
```

---

## 作者：DashZhanghanxu (赞：0)

# 解析
首先，先展示下通过记录。

[AC](https://codeforces.com/submissions/Dashzhanghx)

题意：一个正整数的花费定义为将数字除以其各位数字之和的结果（可以有前导 $0$）。为了使数字的花费达到最小，输出你至少需要从这个数字中移除多少位数字。

首先，从右往左找到第一个非 $0$ 数字，将其右边所有数字（$0$）删去，并且将其左边所有非 $0$ 数字删去，即为最小花费。
# CODE

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define O2 ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
string n;
int t;
signed main(){
    O2;
    cin>>t;
    while(t--){
    	cin>>n;
    	int ans=0;
    	for(int i=n.size()-1;i>=0;i--){
    		if(n[i]!='0'){
    			for(int j=0;j<=i-1;j++){
    				if(n[j]!='0'){
						ans++;
					}
				}
    			break;
			}else{
				ans++;
			}
		}
		cout<<ans<<'\n';
	}
    return 0;
}
```

---

## 作者：Tsz1024_AK (赞：0)

### 解析思路
题目让你求找出最少需要从数字 $n$ 中移除多少个数字（比如从 $1234$ 中移除 $2$ 个数字：$1$ 和 $2$），使得剩余数字组成的数的“成本”达到最小。

而“成本”指 $n$ 除以其各位数字之和所得的结果，就比如题目中举的例子：$\frac{104}{1+0+4}=20.8$。

因为最终得到的数“成本”一定为 $1$，且一个数一定不比它的数字和小，所以方法就是一直删，只要不小于 $0$ 就可以。

---
### 示例代码
```cpp
#include<bits/stdc++.h>
using namespace std;
signed main(){
	int T=1;
	cin>>T;
	while(T--){
		string str; cin>>str;
		bool flag=0;
		int num=0,len=str.size();
		for(int i=len-1;i>=0;i--){
			if(str[i]!='0')
				flag=1;
			else if(flag==0)
				num++;
		}
		cout<<len-num+1<<"\n";
	}
	return 0;
}
```

---

## 作者：LVFUyang1 (赞：0)

这道题是贪心，非常简单。


思路：
只保留从右往左，第 $1$ 个非 $0$ 的数位和它前面的 $0$ ，它的数位都移除。


代码：


```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		string s;
		cin>>s;
		int n=s.size();
		int ans=0,wei;
		for(int i=0;i<n;i++)
			if(s[i]>'0')
				ans++,wei=i;
		for(int i=wei;i<n;i++)
			if(s[i]=='0')
				ans++;
		cout<<ans-1<<'\n';
	}
	return 0;
} 
```

---

## 作者：volatile (赞：0)

应该有前置的初中知识

# 题目大意

给你一个数 $n$，它的价值是它本身除以它各个位上的和，比如说，$114514$ 的价值就是 $\frac{114514}{1+1+4+5+1+4}$，你可以删掉任意一个数位上的数字（注意得出的结果要大于 $0$），题目问的是如何使这个数的价值尽可能小同时删除的数字也尽可能少。

# 思路

我们设这个数为 $\overline{n_1n_2\dots{n_k}}$，那么这个数的价值为

$$\frac{\overline{n_1n_2\dots{n_k}}}{n_1+n_2+\dots+n_k}=\frac{n_1\times10^{k-1}+n_2\times10^{k-2}+\dots{n_k}}{n_1+n_2+\dots{n_k}}$$

显而易见，我们要使这个数的价值最少，就得让这个数删减为一个一位数，同时要让删除的数字尽可能少，就需要保留前导零，比如说 $1040504$，需要删除为 $0004$。

# 代码

```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--){
        string n;
        cin>>n;
        int flag=0,s=0;
        for(int i=n.size()-1;i>=0;i--){
            if(n[i]!='0') flag=1;
            else if(flag) s++;
        }
        cout<<n.size()-s-1<<endl;
    }
    return 0;
}
```

---

## 作者：Kratos_Charger (赞：0)

## CF2093B Expensive Number 题解

### 题目大意

正整数“成本”的定义与计算为：一个正整数 $n$ 的“成本”是该数 $n$ 除以其各位数字之和所得的结果。

例如，$104$ 的成本是 $\frac{104}{1 + 0 + 4} = 20.8$，$111$ 的成本是 $\frac{111}{1 + 1 + 1} = 37$。

给定一个不包含前导零的正整数 $n$，可以从中移除任意数量（包括零个）的数字，但要保证剩余数字形成的数至少有一位且严格大于零，同时剩余数字的顺序不能改变，可能会出现剩余数字有前导零的情况。

要求找出最少需要从数字 $n$ 中移除多少个数字，使得剩余数字组成的数的“成本”达到最小。

### 思路

要让成本最小，因为成本的计算方式是数字本身除以各位数字之和，为了使成本最小，可以考虑让各位数字之和尽量大，同时让数字本身尽量小。

从数字的特点来看，末尾的非零数字对数字大小影响较大，而末尾连续的零对数字大小无影响，但会增加各位数字之和。所以可以从数字的末尾开始，找到第一个非零数字，然后统计其后零的个数。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t; 
int main() {
    cin>>t;
    while(t--) {
        string n;
        cin>>n;
        // 标记是否遇到非零数字
        bool f=false;
        // 统计末尾连续零的个数
        int cnt=0;
        // 从数字的末尾开始向前遍历
        for(int i=n.size()-1;i>=0;i--) {
            // 如果遇到非零数字，标记为已遇到非零数字
            if(n[i]!='0') f=true;
            // 如果已经遇到非零数字，且当前数字是零，则统计零的个数
            else if(f) cnt++;
        }
        // 输出需要移除的数字个数，即数字总位数减去（末尾连续零的个数加 1）
        cout<<n.size()-(cnt+1)<<endl;
    }
    return 0;
}
```

---

## 作者：AK_400 (赞：0)

注意到最后得到的数的代价一定是 $1$，因为一个数一定不比它的数字和小，构造方案就是一直删直到小于 $0$。

考虑最小化次数，也就是想办法保留最多的前导零，只需要选最后一个非零的数和它前面所有的 $0$ 就好了。

复杂度：$O(\log n)$。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
template<typename T>
inline void read(T &x){x=0;char c=getchar();bool neg=0;while(!isdigit(c)){if(c=='-')neg=1;c=getchar();}while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();if(neg)x=-x;}
#define read2(a,b) read(a),read(b)
#define read3(a,b,c) read2(a,b),read(c)
#define read4(a,b,c,d) read3(a,b,c),read(d)
#define read5(a,b,c,d,e) read4(a,b,c,d),read(e)
#define read6(a,b,c,d,e,f) read5(a,b,c,d,e),read(f)
string s;
void slv(){
    cin>>s;
    bool flg=0;
    int ans=0;
    for(int i=s.size()-1;i>=0;i--){
        if(s[i]!='0')flg=1;
        else if(flg)ans++;
    }
    cout<<s.size()-ans-1<<endl;
    return;
}
signed main(){
    int T;read(T);while(T--)
    slv();
    return 0;
}
```

---

## 作者：Lyw_and_Segment_Tree (赞：0)

## 开始解题！

由于可以任意删除，但最终的数字不能为 $0$，所以我们考虑一个数字 $\overline{a_1a_2\ldots a_k}$，若只有 $a_k \not= 0$，而其他项均为 $0$，那么这个数字的价值就是 $1$，达到了最小。

所以我们保留尽可能多的 $0$，而要保留尽可能多的 $0$，就要求我们选取最右边的第一位不为 $0$ 的数字，并计算 $0$ 的个数，而这是简单的。

注意由于 $n$ 很大，所以我们使用字符串将 $n$ 存下。

上代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define vec vector
#define pll pair<ll, ll>
#define mkp make_pair
#define endl "\n"

using namespace std;

const ll mod = 998244353;

namespace fastio {
	char buf[1 << 21], *p1 = buf, *p2 = buf;
	
	const ll getc() {
	    return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
	}
	
	const ll read() {
		ll x = 0, f = 1;
		
		char ch = getc();
		
		while (ch < '0' || ch > '9') {
			if (ch == '-') f = -1; ch = getc();
		}
		
		while (ch >= '0' && ch <= '9') {
			x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
		}
		
		return x * f;
	}
	
	const void write(ll x) {
		if (x < 0) {
			putchar('-'), x = -x;
		}
		
	    ll sta[35], top = 0;
	    
	    do {
	        sta[top++] = x % 10, x /= 10;
	    } while (x);
	    
	    while (top) putchar(sta[--top] + 48);
	}
}

#define rd fastio::read
#define wt fastio::write
#define gc fastio::getc

ll n, m, q, a[200005]; string s;

ll opt, l, r, ans = 0;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
    
    ll i, j, k, x, y, z, res = 0, now;
    
    ll T; cin >> T;
    
    while (T--) {
        cin >> s, n = s.size(), res = 0;
        
        bool flag = false;
        
        for (i = n - 1; i >= 0; i--) {
            if (s[i] != '0') {
                flag = true;
            } else if (flag) {
                res ++;
            }
        }
        
        cout << n - res - 1 << "\n";    
    }
    
	return 0;
}
```

[AC record](https://codeforces.com/contest/2093/submission/314835687)

---

## 作者：wangquanbin (赞：0)

### 思路
我们能证明，结果数字的最小可能成本始终等于 $1$。考虑一个任意的正数  
$$n = \overline{a_1a_2 \ldots a_k}$$  
其中 $a_i$ 是按顺序排列的各位数字。我们计算该数字的成本为  
$$\text{cost}(n) = \frac{\overline{a_1a_2 \ldots a_k}}{a_1 + a_2 + \ldots + a_k} = \frac{a_1 \cdot 10^{k-1} + a_2 \cdot 10^{k-2} + \ldots + a_k}{a_1 + a_2 + \ldots + a_k} > \frac{a_1 + a_2 + \ldots + a_k}{a_1 + a_2 + \ldots + a_k} = 1$$  
我们还注意到，如果任何一位数字 $a_1, a_2, \ldots, a_{k-1}$ 不等于零，则不等式将严格成立。因此，可以通过仅保留一个非零数字和其前导的多个零来实现成本 $1$。

因此，我们的任务简化为保留某个非零数字及其左侧的所有零，并删除其他数字。具体而言，我们应保留原数字中最右侧的非零数字及其左侧的所有零，并移除其余数字。
### AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int n=s.size();
        bool f=0;
        int cnt=0;
        for(int i=n-1;i>=0;i--){
            if(s[i]!='0'){
                f=1;
            }
            else if(f){
                cnt++;
            }
        }
        cout<<n-cnt-1<<endl;
    }
    return 0;
}
```
嘻嘻~

---

