# Submarine in the Rybinsk Sea (easy edition)

## 题目描述

这题与下一个题的不同之处仅在于存在使所有数字$a_1,a_2,\dots,a_n$的相等长度的约束。实际上，这个问题是来自同一竞赛的$D_2$问题的子问题，$D_2$的解决方案也能解决这个子问题。

$SIS$学生团队将乘坐潜水艇去旅游，他们的目标是位于大雷宾斯克$(Rybinsk)$海底沉船中的古代宝藏。不幸的是，学生们不知道船的坐标，因此他们要求$Meshanya$（一位世袭魔法师）来帮助他们。$Meshanya$同意帮助他们，但前提是他们得解决了$Meshanya$的问题。

让我们用一个函数$f(a_1a_2\dots a_{p-1}a_p,b_1b_2\dots b_{p-1}b_p)$来交替两个数字的各位数码，其中$a_1,a_2,\dots,a_p$和$b_1,b_2,\dots,b_p$是以十进制表示的两个整数的数码，不含前导零。

换句话说，函数$f(x,y)$通过将数字$x$和$y$的各位数码从最低位数写到较高位数字，从数字$y$开始，交替地插入数字$x$和$y$。该函数的结果也是从右到左构建的（即从较低的数字到较旧的数字）。如果其中一个参数（不妨设为$x$）的数字已写完，则写下另一个参数（即$y$）的剩余数字，下面我们来看几个例子熟悉一下。

$f(1111, 2222) = 12121212$

$f(7777, 888) = 7787878$

$f(33, 44444) = 4443434$  

$f(555, 6) = 5556$   

$f(111, 2222) = 2121212$

一般的，如果$p \ge q$，那么$f(a_1 \dots a_p, b_1 \dots b_q) = (a_1 a_2 \dots a_{p - q + 1} b_1 a_{p - q + 2} b_2 \dots a_{p - 1} b_{q - 1} a_p b_q)_{(10)}$

$Mishanya$为您提供一个由$n$个整数组成的数组$\left\{a_i\right\}$。此数组中的所有数字长度相等（即每个数字的位数相等）。你的任务是帮助学生们计算$\sum\limits_{i = 1}^{n}\sum\limits_{j = 1}^{n} f(a_i, a_j) \mod 998,244,353$。

## 样例 #1

### 输入

```
3
12 33 45```

### 输出

```
26730```

## 样例 #2

### 输入

```
2
123 456```

### 输出

```
1115598```

## 样例 #3

### 输入

```
1
1```

### 输出

```
11```

## 样例 #4

### 输入

```
5
1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
265359409```

# 题解

## 作者：王梓涵 (赞：0)

## 01. 题目大意
定义一函数函数 $f$，使用 $f(a_1a_2\cdots a_p,b_1b_2\cdots b_q)$ 来交替两个数字的各位数码。

最后输出
$$\sum\limits_{i=1}^n\sum\limits_{j=1}^nf(a_i,a_j)\bmod998,244,353$$
的值。

## 02. 题目分析
这道题不能使用暴力，因为 $n \leqslant 10^5$，所以以 $\mathcal{O}(n^2)$ 的时间复杂度必会超时。

将上述合式展开，可以知道任意的整数 $i$ 属于 $\left[1,n\right]$ 对应的 $a_i$ 都会与任意的整数 $j$ 属于 $\left[1,n\right]$ 对应的 $a_j$ 进行一次 $f$ 运算。也就是 $a_1$ 分别与 $a_1,a_2,\cdots,a_n$ 进行一次 $f$ 运算（$a_1$在前），其它的 $a_i$ 也是。所以有 $f(a_i,a_j)$ 就有$f(a_j,a_i)$。

可以发现，由于给的数是等长的，所以 $f(a_1a_2\cdots a_p,b_1b_2\cdots b_p)=a_1b_1a_2b_2\cdots a_pb_p$ 与 $f(b_1b_2\cdots b_p,a_1a_2\cdots a_p)=b_1a_1b_2a_2\cdots b_pa_p$ 的和可以看成是其中一个结果的 $a_i$ 与另一个结果的 $b_i$ 交换数字。简单来说就是
$$f(a_i,a_j)+f(a_j,a_i)=f(a_i,a_i)+f(a_j,a_j)$$
因为可以改写成这样相同的式子共 $n$ 个，那么我们求一次
$$\sum\limits_{i=1}^nf(a_i,a_j)\cdot n$$
就可以了。

这样时间复杂度就直接从 $\mathcal{O}(n^2)$ 变为 $\mathcal{O}(n)$ 了，肯定不会超时。

**注意一定要随时模一下 $998244353$，不然就会爆掉**，~~（我就这么被卡了一次）~~。

## 03. 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MOD 998244353 //定义一个MOD

signed main()
{
	int n;
	int ans = 0;
	string s;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> s;
		int t = 0, len = s.length();
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				t = t * 10 + s[i] - '0'; //进行前面所说的操作
				t %= MOD; //这块一定要记得模一下
			}
		}
		ans += t;
		ans %= MOD; //这块也要模一下
	}
	ans *= n;
	ans %= MOD;
	cout << ans << endl;
	return 0; //完结撒花~
}
```

---

## 作者：灵光一闪 (赞：0)

~~抢第一！~~  
这题就是一个珂怕的思维难度！代码并不难！

12，33就变成了1323，那么有一个关键的思路了！

# 12所贡献进答案的只有1020*n+102*n

为什么呢？因为这个保证了长度相等，所以我们把1323分解一下：
```
1323
*3*3
1*2*
则把星号看成0，就知道了
0303
1020
```
代码:
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<string>
using namespace std;
const int mod=998244353;
int a[233333];
unsigned long long b[2][233333];
unsigned long long ans;
unsigned long long point(string s){//字符串变成数字
    unsigned long long sum=0;
    reverse(s.begin(),s.end());
    for(int i=0;i<s.size();i++){
        sum=sum*10+(s[i]-'0');
    }
    return sum;
}
string f(int a){
    string s="";
    while(a){
        s+=(a%10+'0');
        s+='0';
        a/=10;
    }
    return s;
}
string F(int a){//上下两个f函数其实差不多。可以归并成1个
    string s="";
    while(a){
        s+=(a%10+'0');
        s+='0';//每一个数码中间都压一个0
        a/=10;
    }
    return s.substr(0,s.size()-1);//因为有一个最后没有0，所以就切掉了
}
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        b[0][i]=point(f(a[i]))*10%mod;
        b[1][i]=point(F(a[i]))%mod;//这题中取%很重要！
        ans+=b[0][i]*n;
        ans=ans%mod;//取%！
        ans+=b[1][i]*n;
        ans=ans%mod;
    }
    cout<<ans<<endl;
    return 0;
}
```
The End.

---

