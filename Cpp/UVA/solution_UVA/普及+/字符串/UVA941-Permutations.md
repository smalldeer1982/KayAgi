# Permutations

## 题目描述

## 题目大意：

输入一个不超过20个字符并且全由小写字母构成的字符串以及一个数N，输出原字符串重新排列顺序得到的所有字符串中字典序从小到大第N+1个的字符串。

## 样例 #1

### 输入

```
2
abc
3
abcde
119```

### 输出

```
bca
edcba```

# 题解

## 作者：SisconHL (赞：1)

因为组合比较弱就找了个比较板的题（

分析一下，$N$ 可能达到 $20!$，一个一个 `std::next_permutation` 一定是不行的。

考虑一个字符串 $a_1a_2...a_n$，求第 $x$ 个排列，假设字符串已排序。

第一个为什么后面都会有 $A_{n-1}^{n-1}=(n-1)!$ 种方式，我们就把 $x$ 整除 $(n-1)!$，把余数拿来考虑第二位，以此类推就行啦~

$20!>INT\_MAX$，要开 `long long`。

有一个小 trick，阶乘可以预处理 ~~（虽然没啥用）~~

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#define int ll
using namespace std;
typedef long long ll;
const int maxn=25;
ll JC[maxn];int permu[maxn];char ch[maxn];bool b[maxn];
void getJC(){JC[0]=1;for(int i=1;i<maxn;i++)JC[i]=JC[i-1]*i;}
void getPERMU(int cur,int len,ll x){
	if(cur==len)return;
	int to=x/JC[len-cur-1];
	int i;for(i=0;i<to;i++)if(b[i])to++;
	while(b[i])i++;
	permu[cur]=i;b[i]=true;
	getPERMU(cur+1,len,x%JC[len-cur-1]);
}
signed main(){
	int T;
	ll x;string s;cin>>T;getJC();
	while(T--){
		for(int i=0;i<maxn;i++)b[i]=false;
		cin>>s>>x;
		int len=s.length();
		for(int i=0;i<len;i++)ch[i]=s[i];
		sort(ch,ch+len);
		getPERMU(0,len,x);
		for(int i=0;i<len;i++)cout<<ch[permu[i]];
		cout<<endl;
	}
}
```

---

## 作者：itzxianfish (赞：0)

# 思路：

逆康托展开的板子，记得每次对输入的字符串排序一下即可。

# 逆康托展开：

一种求字典序下第 $n$ 个排列的算法，这里的 $n$ 一般下标从 $0$ 开始计算。

### 推导：

我们知道一个长度为 $n$ 且无重复字符的字符串的排列总数为 $n!$，假设这个字符串记作 $s$ 且这个字符串已经排序，$s_i$ 记作某一个下标为 $i$ 的字符。

那么，这个字符串的一个以 $s_p$ 为开头的排列共有 $(n - 1)!$ 个。

也就是说，如果这个字符串所有的排列按照字典序拍好并赋予下标，你会发现 $0$ 到 $(n-1)!-1$ 下标的排序开头都是 $s_0$，$(n-1)!$ 到 $2(n-1)!-1$ 下标的排序开头都是 $s_1$，以此类推。

如果给定我们要求的是第 $k$ 排列，那么答案中的第一个字符就是 $s_{\lfloor\frac{k}{(|s|-1)!}\rfloor}$，此时不论是自己手写还是调用字符串的方法，实现删去 $s$ 中，下标为 $\lfloor \frac{k}{(|s|-1)!} \rfloor$ 的字符，并将其加入 $ans$ 字符串，之后我们下一轮的选择就被限制在了剩下的字符内，我们令 $k' = k \bmod (|s|-1)!$ 即可获取下一轮的第 $k'$ 排列的序号（注意 $k'=k\bmod(|s|-1)!$ 中的 $|s|$ 是修改之前的字符串长度），迭代直到 $|ans|$ 等于原字符串的长度，或者判断 $s$ 是否为空即可。

# 复杂度分析：

对于一次求解，记字符串长度为 $n$，我们主要的时间开销在，排序和逆康托展开。

排序开销是 $O(n\log{n})$，逆康托展开对每一个字符操作，开销 $O(n)$，但是每一次操作都要进行字符删除，开销也是 $O(n)$，于是一次逆康托展开的复杂度是 $O(n^2)$，那么对于 $T$ 次询问求解，复杂度就是 $O(Tn^2)$，如果不要求高精度的话 $n$ 一般是 $n \le 20$ 的，可以应付多次询问。

# 注意事项：

给 $n$ 开~~龙龙~~，以及预处理阶乘（开~~龙龙~~）结果用于 $O(1)$ 调用。

# Code：


```cpp
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
long long n, t, p, fac[21];
char ans[22];
string str;
int main() {
    fac[0] = 1; for (int i = 1; i <= 20; i++) fac[i] = 1ll * i * fac[i - 1];
    cin >> t;
    while (t--) {
        cin >> str >> n;
        sort(str.begin(), str.end());
        int len = str.size();
        p = 0;
        while (p != len) {
            int a = str.size();
            int g = n / fac[a - 1];
            ans[p++] = str[g];
            str.erase(g, 1);
            n %= fac[a - 1];
        }
        for (int i = 0; i < p; i++) putchar(ans[i]);
        puts("");
    }
    return 0;
}
```

---

