# Long Multiplication

## 题目描述

You are given two integers $ x $ and $ y $ of the same length, consisting of digits from $ 1 $ to $ 9 $ .

You can perform the following operation any number of times (possibly zero): swap the $ i $ -th digit in $ x $ and the $ i $ -th digit in $ y $ .

For example, if $ x=73 $ and $ y=31 $ , you can swap the $ 2 $ -nd digits and get $ x=71 $ and $ y=33 $ .

Your task is to maximize the product of $ x $ and $ y $ using the aforementioned operation any number of times. If there are multiple answers, print any of them.

## 样例 #1

### 输入

```
3
73
31
2
5
3516
3982```

### 输出

```
71
33
5
2
3912
3586```

# 题解

## 作者：xdogg (赞：4)

### 题目简述

给定两个长度相同的数 $x,y$，你可以进行若干次操作，交换 $x,y$ 的第 $i$ 位数字。求怎样操作使得操作后使得两数乘积最大。

### 解题思路

首先我们需要知道，在两数和一定的情况下，两数的差越小，乘积越大。本题中，两数长度相同且只能对每一位进行交换操作，两数之和一定不变。而本题就是让我们找出一种方法，使得在操作后两数的差尽可能小。

本题思路，从高位到低位依次遍历两个数的每一位。当我们遍历到第一个不同的数字时，我们不用管它，但它决定了两数的相对大小；接下来的数字中，不管我们如何操作，都不会影响两数之间的相对大小，我们要让小的数尽可能大。也就是说，要把所有大的数字换到较小数。

以样例为例，第三组数 $3982$ 和 $3516$：

- 第一位相等，不进行操作。

- 第二位使得第一个数大，第二个数小，不过我们也不用管它。

- 第三位要使第二个数尽可能大，将较大的 $8$ 放在第二个数，所以交换当前位。

- 第四位要将较大的 $6$ 放在第二个数，但 $6$ 已经在第二个数，不用操作。

### 繁琐的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[105],b[105];
int len;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--){
		cin>>a>>b;
		len=strlen(a);
		int t=0;
		for(int i=0;i<len;i++){
			if(a[i]>b[i]){
				if(t==0){
					t=1;
				}else if(t==1){
					swap(a[i],b[i]);
				}
			}else if(a[i]<b[i]){
				if(t==0){
					t=2;
				}else if(t==2){
					swap(a[i],b[i]);
				}
			}
		}
		cout<<a<<"\n"<<b<<"\n";
	}
	return 0;
}
```

---

## 作者：kimidonatsu (赞：2)

比起 B 题好打了不止一点，看出结论就是一眼题。

有两个数 $a$ 和 $b$，如何操作使得 $a \times b$ 最大，显然是 $|a - b|$ 越小其积越大，证明如下：

$$\because (a + b)^2 - (a - b)^2 = 4ab$$
$$\therefore ab = \dfrac{(a + b)^2 - (a - b)^2}{4}$$

因此若 $a + b$ 为定值，则当 $|a - b|$ 越小， $(a - b)^2$ 也越小，从而 $ab$ 越大。

从高位开始枚举贪心地往下做即可。

[Submission](https://codeforces.com/contest/1954/submission/257724955)

---

## 作者：ZBH_123 (赞：1)

# 题目分析

## 结论

先说结论。设两个整数 $a,b$，当 $a+b$ 一定时，$a$ 和 $b$ 越接近，$ab$ 越大。这就是所谓的“和一定时，差小积大”。

## 证明

设有两个整数 $x,y$，令 $s=x+y$，再定义 $t=xy$，则 $t=(s-x)x=sx-x^2$。因为这个函数二次项系数小于 $0$，所以这个二次函数的图像开口朝下，即这个函数的顶点的纵坐标是这个函数的最大值。由此可得该函数的最大值是 $-\frac{s}{-2}=\frac{s}2$，即该函数在 $(-\infty,\frac{s}2)$ 上单调递增，在 $(\frac{s}2,\infty)$ 上单调递减。所以当 $x,y$ 越接近时，$xy$ 越大。

证毕。

## 实现

我们一位一位地分析题目给出的 $x,y$，如果当前分析到的位置以前的位置组成的数不相等，那就把 $x,y$ 的分析到的位置的大的数字分配给以前的数更小的那个。最后只需要将分配完的数输出就行了。

# code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

string str1,str2,s,t;

bool check(int x){
	for(int i=0;i<=x;i++) if(s[i]!=t[i]) return s[i]>t[i];
	return false;
}

void solve(){
	cin>>str1>>str2;
	int n=str1.length();
	s=str1[0],t=str2[0];
	for(int i=1;i<n;i++){
		if(check(i)){
			if(str1[i]>str2[i]){
				s+=str2[i],t+=str1[i];
				swap(str1[i],str2[i]);
			}
			else s+=str1[i],t+=str2[i];
		}
		else{
			if(str1[i]<str2[i]){
				s+=str2[i],t+=str1[i];
				swap(str1[i],str2[i]);
			}
			else s+=str1[i],t+=str2[i];
		}
	}
	cout<<str1<<'\n'<<str2<<'\n';
}

int main(){
	int t=1;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：zhanglh (赞：1)

### Description

给定两个长度相同的数，可以任意交换两个数字间同一位上的数字。使得交换后两个数的乘积尽可能的大，输出交换后的两个数。

### Solution

对于给定的两个数 $a$ 和 $b$。在 $a + b$ 为定值的情况下，$a$ 和 $b$ 的差越小，$a \times b$ 的值越大。因此，要使交换后两个数的乘积尽可能大，应使得：较大的数尽可能变小，较小的数尽可能变大。

```
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 110;

int n;
char a[N], b[N];

inline void solve()
{
   cin >> a >> b;
   n = strlen(a);
   int x = 0, t = 0;
   while (a[x] == b[x]) x ++ ;
   if (a[x] - '0' > b[x] - '0') t = 1;
   for (int i = x + 1; i < n; i ++ )
   {
      if (t == 0 && a[i] - '0' < b[i] - '0') swap(a[i], b[i]);
      else if (t == 1 && a[i] - '0' > b[i] - '0') swap(a[i], b[i]);
   }
   if (t == 0) cout << b << endl << a << endl;
   else cout << a << endl << b << endl;
}

int main()
{
   int T;
   scanf("%d", &T);
   while (T -- ) solve();
   return 0;
}
```

---

## 作者：JerryGuoZhe (赞：1)

由于同一位上交换不影响和，所以可以使用定律“和一定，差小积大”来解决。

具体实现：

1. 找到前几位相同的，从第一位不同的数位 $j$ 开始。
2. 找到第一位不同的数位后，令 $s1_j=\min\{a_j, b_j\}$，令 $s2_j=\min\{a_j, b_j\}$。
3. 后面和第二步相反安排即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int tc;
    cin >> tc;
    while(tc--) {
        string a, b;
        cin >> a >> b;
        string s1, s2;
        int j=0;
        s1.resize(a.size());
        s2.resize(b.size());
        for(;j<a.size()&&a[j]==b[j]; j++)
            s1[j]=a[j], s2[j]=b[j];
        if(j==a.size()) {
            cout << a << endl << b << endl;
            continue;
        }
        s1[j]=max(a[j], b[j]);
        s2[j]=min(a[j], b[j]);
        for(int k=j+1; k<a.size(); k++)
            s1[k]=min(a[k], b[k]), s2[k]=max(a[k], b[k]);
        cout << s1 << endl << s2 << endl;
    }
    return 0;
}

```

---

## 作者：dingyyds11111 (赞：1)

## 题解：CF1954C Long Multiplication
[题目传送门](https://www.luogu.com.cn/problem/CF1954C)

- 由题意可得：给出两个长度相同的整数 $x$ 和 $y$，由 $1$ 到 $9$ 的数字组成。需要交换 $x$ 中的第 $i$ 位和 $y$ 中的第 $i$ 位。使得 $x \times y$ 最大。
- $x, y \le 10^{100}$，所以用 `string` 来存。

可以知道，在 $x + y$ 一定的情况下，差越小，$x \times y$ 越大。所以我们可以将两个 `string` 转成长度相等的数组，判断每一位谁大，只用判断到两个数不相等的后一位在这一位之后，不管后面的多大，都比他小。所以之后就在小一点的串里添加大的，在大一点的串里添加小的。

根据上面的思路，我们可以得出三种情况：

- $a_i = b_i$
- $a_i < b_i$
- $a_i > b_i$

在后两种中，我们让大的一位添加到小的里面，小的一位添加到大的里面，即可得到答案。

**注意：题目要先输出大的，在输出小的，记得多测清空，但是用动态就好了。**

#### code：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define all(x) (x).begin(),(x).end()
#define cmax(x,y) x=max(x,y)
#define cmin(x,y) x=min(x,y)
#define add(x,y) x=(x+y)%mod
#define endl '\n'
#define re register

using namespace std;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
int t; 

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>t;
	while(t--){
		string a,b;
		cin>>a>>b;
		int n=a.length(),m=b.length();
		vector<int> la(n,0),lb(m,0),ans1(n),ans2(n);
		for (int i=0;i<n;i++) la[i]=a[i]-'0';
		for (int i=0;i<m;i++) lb[i]=b[i]-'0';
		for (int i=0;i<n;i++){
			if(la[i]==lb[i]){
				ans1[i]=la[i];
				ans2[i]=lb[i];
			}
			if(la[i]>lb[i]){
				ans1[i]=la[i];
				ans2[i]=lb[i];
				for (int j=i+1;j<n;j++){
					ans1[j]=min(la[j],lb[j]);
					ans2[j]=max(la[j],lb[j]);
				}
				break;
			}
			if(la[i]<lb[i]){
				ans1[i]=la[i];
				ans2[i]=lb[i];
				for (int j=i+1;j<n;j++){
					ans1[j]=max(la[j],lb[j]);
					ans2[j]=min(la[j],lb[j]);
				}
				break;
			}
		}
		for (int i=0;i<n;i++){
			if(ans1[i]<ans2[i]){
				swap(ans1,ans2);
				break;
			} 
			else if(ans1[i]!=ans2[i]) break;
		}
		for (int i=0;i<n;i++) cout<<ans1[i];cout<<endl;
		for (int i=0;i<n;i++) cout<<ans2[i];cout<<endl;
	}
	return 0;
}
```

---

## 作者：Expert_Dream (赞：1)

如何将两个数通过交换相同位的数来使得他们的积最大呢？

发现两个数位数相同，所以不论如何交换，他们的和都是一样的。

首先，我们引入小学二年级学到的知识：和不变，差小积大。

具体证明的话，你问小学生吧。

所以，我们的问题由此转换成如何将它的差变得更小。

那么我们可以直接枚举每一位，如果当前 $x$ 比 $y$ 大了，那么把下一位更大的数填到 $y$ 上，反之填 $x$。

因此，我们用贪心的策略可以将 $x$ 和 $y$ 的差尽可能缩小。

于是得到代码：


```cpp
// Author: gsczl71
// Copyright (c) 2024 gsczl71 All rights reserved.
// Problem: C. Long Multiplication
// Contest: Codeforces - Educational Codeforces Round 164 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1954/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Date: 2024-04-12 22:53:55

// #pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<long long, long long>
#define fs first
#define sc second
#define x0 _x0_
#define y1 _y1_
#define endl '\n'
#define re register
#define pb push_back
#define vi vector<int>
#define pq priority_queue
#define mem(a,x) memset((a),(x),sizeof(a))
#define debug puts("AK IOI")
#define sz(s) (int)(s.size())
#define all(a) a.begin(),a.end()
#define rd(l,r) (myrand()%(r-l+1)+l)
#define print(x) {cout<<x<<endl;return;}
#define ctn(e) if(e) continue
#define brk(e) if(e) break
#define rt(e) if(e) return
#define ll_(e) (1ll*(e))
#define For(x,y,z) for(int x = y;x <= z;x++)
#define For_(x,y,z) for(int x = y;x >= z;x--)
#define mkp make_pair
using namespace std;
// #include <atcoder/all>
// using namespace atcoder;
#define int long long
const int mod = 1e9+7;
//const int mod = 998244353;
mt19937 myrand(time(0));
const int inf = 0x3f3f3f3f,N = 2e5+5,M = 1e6+5,K = 3000+5;
const long long linf = 0x3f3f3f3f3f3f3f3f;
void solve(){
	string a,b;
	cin >> a >> b;
	int n=sz(a);
	a=a,b=b;
	int flag=0;
	string x,y;
	For(i,0,n-1){
		if(!(flag ^ (a[i] < b[i]))) swap(a[i],b[i]);
		x+=a[i],y+=b[i];
		flag=x<y;
	}cout<<a<<endl<<b<<endl;
}
signed main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T=1;
	cin >> T;
	For(_,1,T) solve();
	return 0;
}
```

---

## 作者：Shadow_T (赞：1)

### 前言

C 题严重水于 B 题。

### 题目思路

我们二年级就知道，如果周长一定，越接近正方形的长方体面积越大。其实可以总结为，如果 $x$ 越接近 $y$，那么 $xy$ 越大。

所以我们从高位开始枚举：

- 如果此时 $x<y$ 但是 $x_i<y_i$，那么交换 $x_i$ 和 $y_i$ 可以让积尽量大。

- 如果此时 $x>y$ 但是 $x_i>y_i$，那么交换 $x_i$ 和 $y_i$ 可以让积尽量大。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
bool cmp(string a,string b)
{
	if(a.size()==b.size()) return a>b;
	else return a.size()>b.size();
}
void solve()
{
	string x,y;
	cin>>x>>y;
	for(int i=0;x[i];i++)
	if(cmp(x,y)&&x[i]>y[i]) swap(x[i],y[i]);
	else if(!cmp(x,y)&&x[i]<y[i]) swap(x[i],y[i]);
	cout<<x<<"\n"<<y<<"\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--) solve();
}
```

---

## 作者：ljk8886 (赞：1)

## 题目大意
给你两个长度相等的数 $x$ 和 $y$。你可以让同一个位置的数字交换，使得这两个数的乘积最小。如果有多种答案，输出任意一种即可。

## 题目分析
关注数据范围，发现最大有 $100$ 位。所以肯定得用字符串来解决。根据常识我们知道和不变，差小积大。~~应该不会有人这不知道吧~~知道这些以后，我们就可以直接开始模拟。

首先，我们得先固定一个字符串为较大数。然后遍历字符串时，相同的字符直接跳过，而第一个不相等的字符也不用交换，因为要保证较大数不变，其余字符就直接交换。

接下来，给到代码。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string x, y;
        cin >> x >> y;
        if (x < y) swap(x, y); //因为长度相等，所以可以直接比较字符串 
        int l = x.size();
        bool flag = true;
        for (int i = 0; i < l; i++) 
        {
            if (x[i] == y[i]) continue; //如果两个字符一样，就没必要交换 
            if (flag)
            {
                flag = false;
                continue; //第一个不相等的字符不用交换，因为要保证 x>y 
            }
            if (x[i] > y[i]) swap(x[i], y[i]); //交换两个字符 
        }
        cout << x << endl << y << endl;
    }
    return 0;
}
```

---

## 作者：FlipWind (赞：0)

## 1. 题意

给定两个长度相同的数字，可以任意交换两个数字间同一位上的数字。求 $x$ 和 $y$ 积的最大值。

## 2. 思路

### a. 问题导入

求两个数乘积的最大值，不难想到这个简单的数学问题：
> 给定矩形的周长，求该矩形面积的最大值。

不难看出当这个矩形为正方形的时候，面积最大。

#### - 这个问题的证明

设该矩形的两条边为 $a$、$b$，则 $a+b$ 是定值 $\frac{1}{2}C$（$C$ 是周长）。\
那么由[**基本不等式**](https://baike.baidu.com/item/%E5%9D%87%E5%80%BC%E5%AE%9A%E7%90%86)可得出，$S_{max} = a\times b \leq \frac{(a+b)^2}{4}$，当且仅当 $a=b$ 时取等。

而且观察发现，当 $a$,$b$ 越靠近时，$S$ 越大。\
证明：
$$
a+b=\frac{C}{2}\Rightarrow
ab=\frac{(a+b)^2-(a-b)^2}{4}.
$$
那么 $a+b$ 为定值的情况下，使得 $(a-b)$ 越小，那么 $a\times b$ 越大。
### b. 具体思路

由上面得知，这题问题转化为 “给定两个数，可以使两个数之间同一位上的数字交换，使得较大数尽量小，较小数尽量大”，这样可以使两个数乘积尽量大。

## 3. 代码

分为两部分：
1. 确定两数相对大小。
2. 实现目的。

注意点：
1. 数据范围。没必要用 int or long long int 存，这里用 string 即可。
2. 如果两数前几位相同，那就没必要比较，直接跳过即可。

具体代码，注释在代码内：

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    int t;
    cin>>t;
    while(t--){
        string a,b;
        cin>>a>>b;
        int sz = a.size();
        int pos;
        for(pos=0;pos<sz;pos++){
            if(a[pos]!=b[pos])  break;
        } // 跳过相同位
 
        bool flag = (a[pos]>b[pos]); // 比较两数此时相对大小
        pos++; // 跳到下一位
        for(;pos<sz;pos++){
            if(flag){
                if(a[pos]>b[pos])
                    swap(a[pos],b[pos]);
            } else {
                if(b[pos]>a[pos])
                    swap(a[pos],b[pos]);
            }
        }
        cout<<a<<"\n"<<b<<"\n";
    }
 
    return 0;
}
```

[AC Record](https://www.luogu.com.cn/record/155753837).

---

## 作者：2huk (赞：0)

C < B 无疑。

- 给定两个长度相同的数字 $x, y$，由数字 $1 \sim 9$ 组成。你可以进行若干次操作，交换 $x, y$ 的第 $i$ 位，得到 $x', y'$。求使得 $x' \times y'$ 最大任意一组 $x', y'$。
- 多测。$t \le 1000$，$x, y \le 10^{100}$。

由小学知识可以知道，在 $x + y$ 一定的情况下，$|x - y|$ 越小，$x \times y$ 越大。其中 $|x - y|$ 表示 $x$ 与 $y$ 的差的绝对值。

显然在这道题中 $x + y = x' + y'$，我们要让 $x' \times y'$ 最大，也就是让 $|x' - y'|$ 最小。我们不妨人为增加一个条件 $x' > y'$。即需要满足：

- $x' > y'$；
- $x' - y'$ 最小（拆绝对值）。

为了方便描述，我们令 $x_i, y_i$ 表示 $x, y$ 的第 $i$ 位，其中第 $1$ 位为最高位。

显然我们需要找到最小的 $i$ 满足 $x_i \ne y_i$，然后将 $x_i$ 变成这两个的最大值，$y_i$ 变成这两个的最小值。这样我们就满足了 $x' > y'$ 这个条件。

那么我们希望让 $x' - y'$ 最小也就是让经过上面的第一个过程调整后的 $x'$ 尽量小，$y'$ 尽量大。也就是让对于所有 $x_j, y_j(j > i)$ 将 $x_i$ 变成这两个的最小值，$y_i$ 变成这两个的最大值。

模拟即可。

```cpp
void solve() {
	string s, t;
	cin >> s >> t;
	int n = s.size();
	bool flg = false;
	
	for (int i = 0; i < n; ++ i ) {
		if (!flg) {
			if (s[i] < t[i]) swap(s[i], t[i]);
			if (s[i] != t[i]) flg = true;
		}
		else {
			if (s[i] > t[i]) swap(s[i], t[i]);
		}
	}
	
	cout << s << '\n' << t << '\n';
}
``

---

