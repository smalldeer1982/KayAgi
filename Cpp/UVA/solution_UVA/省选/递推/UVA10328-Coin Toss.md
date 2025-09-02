# Coin Toss

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=15&page=show_problem&problem=1269

[PDF](https://uva.onlinejudge.org/external/103/p10328.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10328/79179092b3e0642a6c5e276c376ecc97c711e80c.png)

## 样例 #1

### 输入

```
4 1
4 2
4 3
4 4
6 2```

### 输出

```
15
8
3
1
43```

# 题解

## 作者：Hiraeth (赞：3)

抛n次硬币,求至少出现 连续k次 正面的有多少次

dp,f[i][j]表示第i次为出现j (j = 0为正面,j = 1为反面 ),

出现至多连续p次正面,q次反面的所有可能情况

至少出现k次正面,就是连续至多出现n次正面,n次反面,至多出现k-1次正

面,n次反面

f[i][j] = f[i - 1][0] + f[i - 1][1](i <= p)

f[i][j] = f[i - 1][0] + f[i - 1][1] - 1(i = p + 1)

f[i][j] = f[i - 1][0] + f[i - 1][1] - f[i - p - 1][1](i > p + 1)

~~但是由于题目的数据范围比较毒瘤，所以要用高精度..~~

高精度打不熟

Emmmmmmm

~~痛苦 呜呜呜呜呜呜呜呜呜呜呜呜~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int L = 110;
string f[110][2];
int n,k;
string add(string a,string b)
{
    string ans;
    int na[L]={0},nb[L]={0};
    int la=a.size(),lb=b.size();
    for(int i=0;i<la;i++) na[la-1-i]=a[i]-'0';
    for(int i=0;i<lb;i++) nb[lb-1-i]=b[i]-'0';
    int lmax=la>lb?la:lb;
    for(int i=0;i<lmax;i++) na[i]+=nb[i],na[i+1]+=na[i]/10,na[i]%=10;
    if(na[lmax]) lmax++;
    for(int i=lmax-1;i>=0;i--) ans+=na[i]+'0';
    return ans;
}
 string sub(string a,string b)
{
    string ans;
    int na[L]={0},nb[L]={0};
    int la=a.size(),lb=b.size();
    for(int i=0;i<la;i++) na[la-1-i]=a[i]-'0';
    for(int i=0;i<lb;i++) nb[lb-1-i]=b[i]-'0';
    int lmax=la>lb?la:lb;
    for(int i=0;i<lmax;i++)
    {
        na[i]-=nb[i];
        if(na[i]<0) na[i]+=10,na[i+1]--;
    }
    while(!na[--lmax]&&lmax>0);lmax++;
    for(int i=lmax-1;i>=0;i--) ans+=na[i]+'0';
    return ans;
}
string work(int u)
{
    f[0][0] = "1";
    f[0][1] = "0";
    for(int i = 1; i <= n; i++)
    {
        f[i][1] = add(f[i - 1][0],f[i - 1][1]);
        if(i <= u)
        {
            f[i][0] = add(f[i - 1][0],f[i - 1][1]);
        }
        else if(i == u + 1)
        {
            f[i][0] = add(f[i - 1][0],f[i - 1][1]);
            f[i][0] = sub(f[i][0],"1");
        }
        else
        {
            f[i][0] = add(f[i - 1][0],f[i - 1][1]);
            f[i][0] = sub(f[i][0],f[i - u - 1][1]);
        }
    }
    return add(f[n][0],f[n][1]);
}
int main()
{
 
    while(~scanf("%d%d",&n,&k))
    {
        string res;
        res = sub(work(n),work(k - 1));
        cout<<res<<endl;
    }
    return 0;
}

```

---

## 作者：0x00AC3375 (赞：1)

### 1. 题意
连续抛掷 $n$ 次质地均匀的硬币，求出现连续 $k$ 次正面朝上（连续超过 $k$ 次的正面朝上也算在内）有多少种情况。

### 2. 分析
本题的数据范围很小，但是结果的值可能很大，考虑直接使用 $O(n^3)$ 的复杂度进行暴力 dp，利用 Java 的 BigInteger 来存储数值。

设 $f[i][j][k]$ 表示已经抛掷了 $i$ 次，当前的正面朝上的 combo 的长度为 $j$ 次正面，最长的正面朝上的 combo 的长度为 $k$，则在抛掷下一次硬币时：
- 如果这一次还是正面，则最长的 combo 变为 $j+1$。已经抛掷的次数为 $i+1$。如果 $j+1>k$，则更新最长的 combo 长度；
- 如果这一次是反面，则最长的 combo 长度仍然是 $k$，但是当前的 combo 要清零。
由此可以得到转移方程
$$f[i+1,j+1,\max(i+1,k)]\leftarrow f[i+1,j+1,\max (i+1,k)]+ f[i][j][k]$$
$$f[i+1][0][k] \leftarrow f[i+1][0][k] + f[i][j][k]$$

预处理一次性求出所有可能情况的种数（相当于打表）后，针对每一组输出，对表中满足情况的数进行求和输出答案即可。

### 3. 代码
```java
import java.util.*;
import java.math.*;
public class Main {

    static int n, k;
    static BigInteger[][][] result = new BigInteger[110][110][110];
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        for(int i=0;i<=109;i+=1) for(int j=0;j<=109;j+=1) for(int k=0;k<=109;k+=1) result[i][j][k]=new BigInteger("0");
        result[0][0][0] = new BigInteger("1");
        for (int i = 0; i < 100; i += 1)
            for (int j = 0; j <= i; j += 1)
                for (int k = 0; k <= i; k += 1) {
                    result[i + 1][j + 1][Math.max(k, j + 1)] = result[i + 1][j + 1][Math.max(k, j + 1)].add(result[i][j][k]);
                    result[i + 1][0][k] = result[i + 1][0][k].add(result[i][j][k]);
                }
        while (cin.hasNext()) {
            BigInteger answer = new BigInteger("0");
            n = cin.nextInt();
            k = cin.nextInt();
            for (int i = 0; i <= n; i += 1) for (int j = k; j <= n; j += 1) answer = answer.add(result[n][i][j]);
            System.out.println(answer);

        }
    }
}
```

### 4. Trivia
1. 本题中“掷出正面 combo 增加 1，掷出反面 combo 清零，保留目前最长的 combo 长度”这个机制和很多的音乐游戏和跳舞机游戏的机制非常类似；
2. C# 作为和 Java 高度相似的语言，也可以直接使用 BigInteger 类且内部重载了四则运算符和 Max 等函数。而 Java 执行大整数运算时只能使用成员方法（且不能直接用整数字面常量进行赋值），因此前者能在一定程度上增强代码的可读性。
```csharp
using System;
using System.Numerics;
using static System.Convert;
using static System.Console;
using static System.Numerics.BigInteger;
public class MainClass 
{
    static int n, k;
    static BigInteger[,,] result = new BigInteger[110,110,110];
    public static void Main(string[] args)
    {
        result[0,0,0] = 1;
        for (int i = 0; i < 100; i += 1) for (int j = 0; j <= i; j += 1) for (int k = 0; k <= i; k += 1)
        {
            result[i + 1, j + 1, (int)Max(k, j + 1)] += result[i, j, k];
            result[i + 1,0,k] += result[i,j,k];
        }
        while (true)
        {
            try
            {
                BigInteger answer = 0;
                string[] arg_lst = ReadLine().Split();
                n = ToInt32(arg_lst[0]);
                k = ToInt32(arg_lst[1]);
                for (int i = 0; i <= n; i+=1) for (int j = k; j <= n; j+=1) answer += result[n,i,j];
                WriteLine(answer);
            }
            catch(Exception)
            {
                return;
            }
        }   
    }
}
```
3. 接第 2 条，只可惜 Uva 不能使用 C#。
4. 抛硬币属于概率论中最为典型的概率模型之一，若设 $P(n,k)$ 表示出现题中所求情况的概率，则将题目的情况数除以 $2^n$ 即为概率的值。

---

## 作者：Nero_Claudius (赞：1)

这道题目其实就是说有N张纸牌，问至少连续K张正面朝上的可能性是多少。


可以用递推做。
首先我们将题目所求从
```cpp
至少K张
```
转化为
```cpp
总数 - 至多K张
```
（为什么要这样自己想）

设F[i][j]为前i个纸牌至多K张的种数。其中j记录第i张纸牌的状态，1为正面朝上，0为反面。

那么可以总结出
```cpp
f[i][0] = f[i - 1][0] + f[i - 1][1]; 
```
```cpp
f[i][1] = f[i - 1][0] + f[i - 1][1];
if(i == k) f[i][1] -= 1;
else if(i > k) f[i][1] -= f[i - k][0];
```

最后要记住这道题需要写高精，我第一次就是这么扑街的。

注：高精用的模板，手残就全加上了，事实上只用加减法。

AC代码如下（洛谷上不知道为什么被积极拒绝，只好去Vjudge上提交。。。没去UVa才不是因为我没有注册。）

```cpp
#include <iostream> 
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath> 
#include <vector>
#include <cassert>
using namespace std;

const int maxn = 105;

struct BigInteger {
    typedef unsigned long long LL;

    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;

    BigInteger& clean(){while(!s.back()&&s.size()>1)s.pop_back(); return *this;}
    BigInteger(LL num = 0) {*this = num;}
    BigInteger(string s) {*this = s;}
    BigInteger& operator = (long long num) {
        s.clear();
        do {
            s.push_back(num % BASE);
            num /= BASE;
        } while (num > 0);
        return *this;
    }
    BigInteger& operator = (const string& str) {
        s.clear();
        int x, len = (str.length() - 1) / WIDTH + 1;
        for (int i = 0; i < len; i++) {
            int end = str.length() - i*WIDTH;
            int start = max(0, end - WIDTH);
            sscanf(str.substr(start,end-start).c_str(), "%d", &x);
            s.push_back(x);
        }
        return (*this).clean();
    }

    BigInteger operator + (const BigInteger& b) const {
        BigInteger c; c.s.clear();
        for (int i = 0, g = 0; ; i++) {
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;
            int x = g;
            if (i < s.size()) x += s[i];
            if (i < b.s.size()) x += b.s[i];
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c;
    }
    BigInteger operator - (const BigInteger& b) const {
        assert(b <= *this); // 减数不能大于被减数
        BigInteger c; c.s.clear();
        for (int i = 0, g = 0; ; i++) {
            if (g == 0 && i >= s.size() && i >= b.s.size()) break;
            int x = s[i] + g;
            if (i < b.s.size()) x -= b.s[i];
            if (x < 0) {g = -1; x += BASE;} else g = 0;
            c.s.push_back(x);
        }
        return c.clean();
    }
    BigInteger operator * (const BigInteger& b) const {
        int i, j; LL g;
        vector<LL> v(s.size()+b.s.size(), 0);
        BigInteger c; c.s.clear();
        for(i=0;i<s.size();i++) for(j=0;j<b.s.size();j++) v[i+j]+=LL(s[i])*b.s[j];
        for (i = 0, g = 0; ; i++) {
            if (g ==0 && i >= v.size()) break;
            LL x = v[i] + g;
            c.s.push_back(x % BASE);
            g = x / BASE;
        }
        return c.clean();
    }
    BigInteger operator / (const BigInteger& b) const {
        assert(b > 0);  // 除数必须大于0
        BigInteger c = *this;       // 商:主要是让c.s和(*this).s的vector一样大
        BigInteger m;               // 余数:初始化为0
        for (int i = s.size()-1; i >= 0; i--) {
            m = m*BASE + s[i];
            c.s[i] = bsearch(b, m);
			m -= b*c.s[i];
        }
        return c.clean();
    }
    BigInteger operator % (const BigInteger& b) const { //方法与除法相同
        BigInteger c = *this;
        BigInteger m;
        for (int i = s.size()-1; i >= 0; i--) {
            m = m*BASE + s[i];
            c.s[i] = bsearch(b, m);
            m -= b*c.s[i];
        }
        return m;
    }
    // 二分法找出满足bx<=m的最大的x
    int bsearch(const BigInteger& b, const BigInteger& m) const{
        int L = 0, R = BASE-1, x;
        while (1) {
            x = (L+R)>>1;
            if (b*x<=m) {if (b*(x+1)>m) return x; else L = x;}
            else R = x;
        }
    }
    BigInteger& operator += (const BigInteger& b) {*this = *this + b; return *this;}
    BigInteger& operator -= (const BigInteger& b) {*this = *this - b; return *this;}
    BigInteger& operator *= (const BigInteger& b) {*this = *this * b; return *this;}
    BigInteger& operator /= (const BigInteger& b) {*this = *this / b; return *this;}
    BigInteger& operator %= (const BigInteger& b) {*this = *this % b; return *this;}

    bool operator < (const BigInteger& b) const {
        if (s.size() != b.s.size()) return s.size() < b.s.size();
        for (int i = s.size()-1; i >= 0; i--)
            if (s[i] != b.s[i]) return s[i] < b.s[i];
        return false;
    }
    bool operator >(const BigInteger& b) const{return b < *this;}
    bool operator<=(const BigInteger& b) const{return !(b < *this);}
    bool operator>=(const BigInteger& b) const{return !(*this < b);}
    bool operator!=(const BigInteger& b) const{return b < *this || *this < b;}
    bool operator==(const BigInteger& b) const{return !(b < *this) && !(b > *this);}
};

ostream& operator << (ostream& out, const BigInteger& x) {
    out << x.s.back();
    for (int i = x.s.size()-2; i >= 0; i--) {
        char buf[20];
        sprintf(buf, "%08d", x.s[i]);
        for (int j = 0; j < strlen(buf); j++) out << buf[j];
    }
    return out;
}

istream& operator >> (istream& in, BigInteger& x) {
    string s;
    if (!(in >> s)) return in;
    x = s;
    return in;
}

int n, k;
BigInteger f[maxn][2];

int main() {
	while(cin >> n >> k) {
		memset(f, 0, sizeof(f));
		f[0][1] = 1;
		for(int i = 1; i <= n; i++) {
			f[i][0] = f[i - 1][0] + f[i - 1][1]; 
			f[i][1] = f[i - 1][0] + f[i - 1][1];
			if(i == k) f[i][1] = f[i][1] - 1;
			else if(i > k) f[i][1] = f[i][1] - f[i - k][0];
		}
		BigInteger a = 1, t = 2;
		for(int i = 0; i < n; i++) a = t * a;
		cout << a - f[n][1] - f[n][0] << endl;
	}
}
```

---

## 作者：C6H14 (赞：0)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/AT2038)

[My blog](https://www.luogu.com.cn/blog/128433/#)

## 思路

蒟蒻的我只会一个 $O(n^3)$ 的 dp。

设 $f(i,j,k)$ 表示抛 $i$ 次，最后连续出现了 $j$ 次正面，当前序列最长的连续一段正面有 $k$ 个正面的方案数，显然 $f(0,0,0)=1$。

那么每次将 $f(i,j,k)$ 直接累加到 $f(i+1,j+1,\max \{ j+1,k \})$ 和 $f(i+1,0,k)$ 中即可。

预处理一遍即可 $O(n^2)$ 查询。

什么？这题要高精？~~int28 水过不就行了~~。

## 代码

```cpp
__int128 f[105][105][105];
ll n,k;
int main()
{
	f[0][0][0]=1;
	for (int i=0;i<100;++i)
		for (int j=0;j<=i;++j)
			for (int k=0;k<=i;++k)
				f[i+1][j+1][max(k,j+1)]+=f[i][j][k],f[i+1][0][k]+=f[i][j][k];
	while (~scanf("%lld%lld",&n,&k))
	{
		__int128 ans=0;
		for (int i=0;i<=n;++i)
			for (int j=k;j<=n;++j)
				ans+=f[n][i][j];
		write(ans,'\n');
	}
	return 0;
}

```


---

## 作者：wrpwrp (赞：0)

[一刀999](https://www.cnblogs.com/HN-wrp/p/12893374.html)  
考虑把答案拆成至多有$n$张朝上减去至少有$k-1$张朝上。我发现貌似一堆题解都直接写了个$k$，这难道不会错？？？？？  
显然第一部分的答案就是$2^n$，考虑$DP$第二部分。设$dp[i][0/1]$表示第$i$张是反面/正面的情况数。然后有：
$$dp[i][0]=dp[i-1][0]+dp[i-1][1] $$
$$dp[i][1]=dp[i-1][0]+dp[i-1][1]-dp[i-k-1][0]$$
然后处理下边界，比如$i=k+1$之类的。 然后这题的问题就转化为高精度了。~~显然我是不会的~~。所以就用$ int128 $水了。
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

#define R register
#define LL __int128
const int inf = 0x3f3f3f3f;
const int MAXN = 100+10;

int n,k;
LL dp[MAXN][2];

inline void print(LL x) {
	if( x > 9 ) print(x / 10);
	putchar('0' + x % 10);
}

int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	while(cin>>n>>k) {
		k--;
		memset(dp,0,sizeof(dp));
		dp[1][0] = 1; dp[1][1] = k ? 1 : 0;
		for(R int i = 2; i <= n ; i++ ) {
			dp[i][0] = dp[i - 1][0] + dp[i - 1][1];
			if( i <= k ) dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
			if( i == k + 1 ) dp[i][1] = dp[i - 1][0] + dp[i - 1][1] - 1;
			if( i > k + 1) dp[i][1] = dp[i - 1][0] + dp[i - 1][1] - dp[i - k - 1][0];
		}
		LL ans1 = 1;
		for(R int i = 1; i <= n ; i++ ) ans1 = ans1 * 2;
		print(ans1 - dp[n][0] - dp[n][1]); putchar('\n');
	}
	return 0;	
}
```

---

