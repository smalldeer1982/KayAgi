# [ABC089C] March

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc089/tasks/abc089_c

$ N $ 人の人がいて、$ i $ 番目の人の名前は $ S_i $ です。

この中から、以下の条件を満たすように $ 3 $ 人を選びたいです。

- 全ての人の名前が `M`,`A`,`R`,`C`,`H` のどれかから始まっている
- 同じ文字から始まる名前を持つ人が複数いない

これらの条件を満たすように $ 3 $ 人を選ぶ方法が何通りあるか、求めてください。ただし、選ぶ順番は考えません。

答えが $ 32 $ bit整数型に収まらない場合に注意してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ S_i $ は英大文字からなる
- $ 1\ \leq\ |S_i|\ \leq\ 10 $
- $ S_i\ \neq\ S_j\ (i\ \neq\ j) $

### Sample Explanation 1

次のような名前の $ 3 $ 人を選ぶと良いです。 - `MASHIKE`,`RUMOI`,`HABORO` - `MASHIKE`,`RUMOI`,`HOROKANAI` よって、$ 2 $ 通りとなります。

### Sample Explanation 2

与えられた条件を満たすように $ 3 $ 人を選ぶ方法が存在しない場合に注意してください。

## 样例 #1

### 输入

```
5
MASHIKE
RUMOI
OBIRA
HABORO
HOROKANAI```

### 输出

```
2```

## 样例 #2

### 输入

```
4
ZZ
ZZZ
Z
ZZZZZZZZZZ```

### 输出

```
0```

## 样例 #3

### 输入

```
5
CHOKUDAI
RNG
MAKOTO
AOKI
RINGO```

### 输出

```
7```

# 题解

## 作者：_Han (赞：4)

##  题意：
在 $N$ 个人名中选择以 $M$、$A$、$R$、$C$、$H$ 为首的无重复首字母的名字 $3$ 个，求方案数。
##  _Solution_ 
对于每一行读入的名字，仅有首字母有意义，我们考虑采用桶的形式统计 $M$、$A$、$R$、$C$、$H$ 的出现次数。
```cpp
cin>>st;
if (st[0]=='M') m++;
if (st[0]=='A') a++;
if (st[0]=='R') r++;
if (st[0]=='C') c++;
if (st[0]=='H') h++;
```
我们已经知道了各字母的出现次数，接下来可以通过**乘法原理**计算结果。

我们设 $M$、$A$、$R$、$C$、$H$ 的出现次数分别为 $m$、$a$、$r$、$c$、$h$。

显然，选择以 $M$、$A$、$R$ 为首的方案数为 $m \times a \times r$。

以 $M$、$A$、$C$ 为首的方案数为 $m \times a \times c$。

以 $M$、$A$、$H$ 为首的方案数为 $m \times a \times h$。

同理可得其他各情况的方案数。

最终的答案即为各个情况的方案数之和。


##  _Code_ 
```cpp
#include<bits/stdc++.h>
#define int long long //题面已经说了要开long long
using namespace std;
int n,m,a,r,c,h,ans;
string st;
signed main()
{ 
	cin>>n;
	for (int i=1;i<=n;i++) 
	{
		cin>>st;
		if (st[0]=='M') m++;
		if (st[0]=='A') a++;
		if (st[0]=='R') r++;
		if (st[0]=='C') c++;
		if (st[0]=='H') h++;
	} //统计各个目标首字母出现次数
	ans+=m*a*r;
	ans+=m*a*c;
	ans+=m*a*h;
	ans+=m*r*c;
	ans+=m*r*h; 
	ans+=m*c*h;
	ans+=a*r*c;
	ans+=a*r*h;
	ans+=a*c*h; 
	ans+=r*c*h; //计算答案数
	cout<<ans<<endl; 
} 
```


---

## 作者：achjuncool (赞：2)

[题目](https://www.luogu.com.cn/problem/AT3932)

[博客](https://www.luogu.com.cn/blog/achjuncool/solution-at3932)

# 题目大意

给出一些字符串，从中选出三个，满足：

- 三个字符串的名字都以 ```M```、```A```、```R```、```C``` 或 ```H``` 开头。

- 三个字符串的首字母互不相同。

求选择的方案数。

# 解法

这题需要运用到一些数学知识。

根据~~小学奥数中的~~乘法原理，方案 $=$ 第一个人的选择数量 $\times$ 剩下的人中第二个人的选择数量 $\times$ 剩下的人中第三个人的选择数量。

而一共有五种可以选的人，分别是`M`、`A`、`R`、`C` 与 `H` 开头的人，那么 $($ 第一个人的首字母 $,$ 第二个人的首字母 $,$ 第三个人的首字母 $)$ 可以是 $(M,A,R)$、$(M,A,C)$、$(M,A,H)$ 等。

可以选择把所有可能都打一遍，也可以选择像我一样~~多此一举地~~打一个深搜。

深搜有一个问题是，$(M,A,R)$ 与 $(A,R,M)$ 是同一种，但是基础的深搜会将这两种都算上。

解决办法类似于 [P1025](https://www.luogu.com.cn/problem/P1025)，每次枚举的数都比上一个大，这样就能避免把组合写成排列。

# Code

[AC](https://www.luogu.com.cn/record/80875338)

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
ll n, a[6], ans, b[4]; //题目中说了会爆 int
/*
a[1]、a[2]、a[3]、a[4]、a[5]分别表示所有字符串中M、A、R、C、H开头的字符串数量
b 数组表示当前选择的三种可以选择的字符串在 a 数组中对应的下标
*/
string t;
bool vis[6];
void dfs(int step){
	if(step == 4){ //如果当前是第四个说明已经搜了三个了
        ans += a[b[1]] * a[b[2]] * a[b[3]];
        return;
    }
	for(ll i = step > 1 ? b[step - 1] : 1; i <= 5; i++){ //三目运算避免重复
		if(!vis[i]){
			vis[i] = true;
			b[step] = i;
			dfs(step + 1);
			vis[i] = false;
		}
	}
}
int main(){
	cin >> n;
	for(ll i = 1; i <= n; i++){
		cin >> t;
		if(t[0] == 'M') a[1]++; //注意字符串下标从 0 开始
		if(t[0] == 'A') a[2]++;
		if(t[0] == 'R') a[3]++;
		if(t[0] == 'C') a[4]++;
		if(t[0] == 'H') a[5]++;
	}
	dfs(1); //从第一个开始搜
	cout << ans << endl;
    return 0;
}
```

---

## 作者：shenmadongdong (赞：1)

### 题意：
在 $n\ (1 \leq n \leq 10^5)$ 个字符串 (长度不超过 $10$ ) 中选 $3$ 个字符串，开头必须为`M`、`A`、`R`、`C`或`H`，第一个字母相同的串不能选两次，求选法的种类数

温馨提示：答案可能爆 $int$

### 解法：
先统计每个字母开头的字符串出现的次数，然后暴力统计选的 $3$ 个开头字母，用乘法原理算出总方案数即可

```
#include<bits/stdc++.h>
using namespace std;
long long n,f[6],ans;
string s;
int main()
{
	cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        if (s[0]=='M') f[1]++;
        if (s[0]=='R') f[2]++;
        if (s[0]=='A') f[3]++;
        if (s[0]=='C') f[4]++;
        if (s[0]=='H') f[5]++;
    }//逐个统计开头字母
    for(int i=1;i<=3;i++) 
		for(int j=i+1;j<=4;j++) 
			for(int k=j+1;k<=5;k++) 
				ans+=f[i]*f[j]*f[k];//暴力枚举开头字母方案，计入总数
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：HYdroKomide (赞：0)

# **正文：**

题意：本题就是计算出以M，A，R，C，H这几个字母开头的名字的个数，再求出其中**取出三个不一样的所有情况**。

情况求解式：如果选择其中的三个字母，求解情况，那么答案就是**这三个字母的积**。如果有五个字母，选择其中的三个，就要把所有情况的积相加，如果我们将M、A、R、C、H出现的数量分别设为a、b、c、d、e，并将答案储存到ans中，则求解式为：$ans=abc+abd+abe+acd+ace+ade+bcd+bce+bde+cde$ ，这样能够枚举出所有的配对情况。

程序说明：先求出所有的首字母出现的个数，再从中挑取M，A，R，C，H的个数，进行情况数量的运算。
```cpp
#include<iostream>
#include<cstring>
using namespace std;
long long initial[26],n,ans;              //题目上注明了可能会超int，所以我们这里使用long long
int main(){
    cin>>n;
    for(long long i=1;i<=n;i++){
        string s;
        cin>>s;
        initial[s[0]-'A']++;           //统计每个字母出现的个数
    }
    long long a=initial['M'-'A'],         //找出m，a，r，c，h
        b=initial['A'-'A'],
        c=initial['R'-'A'],
        d=initial['C'-'A'],
        e=initial['H'-'A'];
    ans=a*b*c+a*b*d+a*b*e+a*c*d+a*c*e+a*d*e+b*c*d+b*c*e+b*d*e+c*d*e;
    //计算答案
    cout<<ans<<endl;
    return 0;
}
```

# **THE END**

---

