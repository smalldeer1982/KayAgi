# Xenia and Hamming

## 题目描述

Xenia is an amateur programmer. Today on the IT lesson she learned about the Hamming distance.

The Hamming distance between two strings $ s=s_{1}s_{2}...\ s_{n} $ and $ t=t_{1}t_{2}...\ t_{n} $ of equal length $ n $ is value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF356B/52be4f702633b5f90851e953f1a83180e97e66f8.png). Record $ [s_{i}≠t_{i}] $ is the Iverson notation and represents the following: if $ s_{i}≠t_{i} $ , it is one, otherwise — zero.

Now Xenia wants to calculate the Hamming distance between two long strings $ a $ and $ b $ . The first string $ a $ is the concatenation of $ n $ copies of string $ x $ , that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF356B/b9012edec23a9faf329465fd2157f0252f5a66d1.png). The second string $ b $ is the concatenation of $ m $ copies of string $ y $ .

Help Xenia, calculate the required Hamming distance, given $ n,x,m,y $ .

## 说明/提示

In the first test case string $ a $ is the same as string $ b $ and equals 100 letters a. As both strings are equal, the Hamming distance between them is zero.

In the second test case strings $ a $ and $ b $ differ in their 3-rd, 5-th, 6-th and 7-th characters. Thus, the Hamming distance equals 4.

In the third test case string $ a $ is rzrrzr and string $ b $ is azazaz. The strings differ in all characters apart for the second one, the Hamming distance between them equals 5.

## 样例 #1

### 输入

```
100 10
a
aaaaaaaaaa
```

### 输出

```
0
```

## 样例 #2

### 输入

```
1 1
abacaba
abzczzz
```

### 输出

```
4
```

## 样例 #3

### 输入

```
2 3
rzr
az
```

### 输出

```
5
```

# 题解

## 作者：素质玩家孙1超 (赞：3)

题意：计算字符串 $a$ 的 $n$ 次循环和字符串 $b$ 的 $m$ 次循环中对应字符不同的个数（ Hamming distance）。数据保证最后两个字符串等长。

$n,m \leq 10^{12}$，$len(a ),len(b)\leq 10^6$


---

看一眼题目，令 $l1 \leq l2$ ,有 $a[i]$ 的贡献为 $\sum b[(j*l1+i)mod \ l2]  \  != a[i]  $ ，其中 $0\leq j\leq n-1$ 。

对于每一个 $a[i]$ 最后和他匹配的 $b$ 字符串上的位置是很容易预处理出来的。

并且大概率会有好几个 $a[i]$ 所匹配的是同一个 $b$ 串的子集。

所以只要预处理出来 $b$ 中的互不相交的所有可能被匹配的子集，然后再在 $a$ 串上分别计算出贡献就可以了。

---
代码：细节在代码里。

然而我写的时候思路不太清晰，所以代码不太好看。

```cpp
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int Maxn=1e6+5;
inline ll R()
{
	char ch=getchar();ll x=0;bool f=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
struct Count
{
    int num[30],S;
}NU;
ll n,m;
int a[Maxn],b[Maxn],l1,l2,To[Maxn];
bool vis[Maxn];
vector<Count>N;
signed main()
{
    n=R();m=R();
    char c;
    while((c=getchar())>'z'||c<'a');
    a[++l1]=c-'a';
    while((c=getchar())<='z'&&c>='a') a[++l1]=c-'a';

    while((c=getchar())>'z'||c<'a');
    b[++l2]=c-'a';
    while((c=getchar())<='z'&&c>='a') b[++l2]=c-'a';
    if(m>n)
    {
        swap(n,m);
        swap(l1,l2);
        swap(a,b);
    }//a是小的
    int p=l1%l2;N.push_back(NU);int Begin=1;
    for(int i=1;;i++)
    {
        bool _=0;
        for(int j=Begin;j<=l2;j++)
            if(vis[j]) continue;
            else 
            {
                Begin=j+1;
                N.push_back(NU);
                while(!vis[j])
                {
                    vis[j]=1;To[j]=i;
                    N[i].num[b[j]]++;
                    N[i].S++;
                    j=(j+l1-1)%l2+1;
                }
                _=1;
                break;
            }
        if(!_) break;
    }
    ll ans=0;
    for(int i=1;i<=l1;i++)
        ans=(ll)ans+N[To[i]].S-N[To[i]].num[a[i]];
    printf("%lld\n",(ll)ans*__gcd(n,m));
}
/*
n m
l1 l2
a[i] -> (j*l1+i)%l2
*/
```

---

## 作者：quanjun (赞：2)

# CF356B - Xenia and Hamming 题解

题目链接：[https://codeforces.com/problemset/problem/356/B](https://codeforces.com/problemset/problem/356/B)

题目大意：  

字符串 $a$ 是字符串 $x$ 循环 $n$ 次（$a = \sum\limits_{n} x$），  

字符串 $b$ 是字符串 $y$ 循环 $m$ 次（$b = \sum\limits_{m} y$）。

字符串 $a$ 和 $b$ 长度相同，求字符串 $a$ 和 $b$ 存在多少个字符不相同。

解题思路（参考自：[官方题解](https://codeforces.com/blog/entry/9210)）：

让我们定义第一个字符串 $x$ 的长度为 $lenX$，第二个字符串 $y$ 的长度为 $lenY$。令 $L = LCM(lenX, lenY)$。很明显 $L$ 是字符串 $a$ 和 $b$ 的一个循环节，所以我们可以计算两个字符串的长度为 $L$ 的前缀的汉明距离，计算的结果再乘上 $\frac{len(a)}{L}$ 就是最终的答案了。

对于字符串 $x$ 中的任意位置 $i$，我们可以思考 $x$ 中的下标 $i$ 能够对应 $y$ 中的哪些下标 $j$。

很容易证明：若定义 $g = GCD(lenX, lenY)$，则当 $i \equiv j(\ mod \ g)$，则 $x_i$ 将和 $y_j$ 作比较。  

对于任意一个位置除以 $g$ 的余数，以及任意一个字符 $c$ 我们可以计算得到 $count(r, c)$，它在字符串 $y$ 中存在多少个下标 $j$ 满足 $j \ mod \ g = r$ 且对应下标 $j$ 对应的字符为 $c$。

当计算（前面长度为 $L$ 的）汉明距离时，$x_i$ 将和恰好 $count(i \mod g, x_i)$ 个字符对应的位置相等且字符也相等，其余位置都是不相等的。

示例程序：  
```c++
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int cnt[maxn][26];
long long n, m, lenX, lenY, L, g, ans;
char x[maxn], y[maxn];
int main() {
    scanf("%lld%lld%s%s", &n, &m, x, y);
    lenX = strlen(x);
    lenY = strlen(y);
    g = __gcd(lenX, lenY);
    L = lenX * lenY / g;
    for (int i = 0; i < lenY; i++)
        cnt[i%g][y[i]-'a']++;
    ans = L;
    for (int i = 0; i < lenX; i++)
        ans -= cnt[i%g][x[i]-'a'];
    printf("%lld\n", ans * (n * lenX / L));
    return 0;
}
```



---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF356B)

## 思路

我的思路似乎奇怪一点。

把两个字符串 $x$ 和 $y$ 按照块长为 $\gcd(len_x,len_y)$ 分块，然后你会发现 $x$ 中的每一块都需要恰好与 $y$ 中的每一块匹配一次。

于是使用多指针维护一下便找到了一个循环节中的答案，最后答案有 $\dfrac{n}{\operatorname{lcm}(len_x,len_y)}$ 个循环节，于是乘一下即可。

## 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long long
int const N=1e6+10;
int l[N],L[N],sum[26],qsum[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;cin>>n>>m;
	string x,y;cin>>x>>y;
	int l1=x.length(),l2=y.length();
	x=" "+x;y=" "+y;
	int g=__gcd(l1,l2);int q=l1*l2/g;
	n*=l1;n/=q;
	for (int i=1;i<=l1/g;++i) l[i]=(i-1)*g+1;
	for (int i=1;i<=l2/g;++i) L[i]=(i-1)*g+1;
	for (int i=1;i<=g;++i){
		for (int j=0;j<26;++j) sum[j]=0;
		for (int j=1;j<=l2/g;++j) ++sum[y[L[j]++]-'a'];
		for (int j=1;j<=l1/g;++j) qsum[j]+=((l2/g)-sum[x[l[j]++]-'a']);
	}
	int ans=0;
	for (int j=1;j<=l1/g;++j) ans+=qsum[j];
	ans*=n;
	cout<<ans<<'\n';
	return 0;
}
```


---

