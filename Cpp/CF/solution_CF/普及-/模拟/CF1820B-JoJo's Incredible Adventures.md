# JoJo's Incredible Adventures

## 题目描述

给定一个长度为 $n$ 的二进制字符串 $s$，构建一个 $n \times n$ 的方格表。首行写下原始字符串 $s$，次行右移一个字符的循环移位字符串 $s$，第三行右移两个字符的循环移位字符串 $s$，以此类推。因此，第 $k$ 行包含一个从 $s$ 右移 $k$ 个字符的循环移位字符串。行从上到下编号 $0$ 至 $n-1$。

在生成的表中，需要找到只由数字 $1$ 构成的矩形并计算其面积，返回最大的面积。

注意：字符串 $s$ 向右循环移动 $k$ 位是指将其最后 $k$ 个字符移动到前面，即字符串 $s_{n-k+1} \cdots s_n \; s_1 \cdots s_{n-k}$。

## 样例 #1

### 输入

```
5
0
1
101
011110
101010```

### 输出

```
0
1
2
6
1```

# 题解

## 作者：Loser_Syx (赞：5)

## 思路

本题求的是构成的最大的矩形面积，但是很容易发现，这题暴力不能过，那么考虑分类讨论。

第一步先把两个字符串拼一起，因为有首尾相连的情况

第一类：

那个字符串全是 `1`，显然能构成 $len \times len$ 的矩阵。

第二类：

那个字符串不全是 `1`，那么我们求出最长连续出现 `1` 的出现次数，此时构成的矩形**周长**为最长连续次数 $+1$，如果我们再往下叠矩阵呢？出现 `1` 的次数 $-1$，但是宽 $+1$，可以发现，**周长永远都是那么多**，既然已经知道了周长，再运用小学的数学知识“已知两个数总和，要使两个数的乘积最大，两个数必须最接近”，问题就迎刃而解了。

## 代码

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
#define int long long
#define f(W, X, Y, Z) for(int W = X; W <= Y; W += Z)
#define F(W, X, Y, Z) for(int W = X; W >= Y; W -= Z)
#define debug puts("QAQ")
namespace fastIO{
	inline int read(){
		int x = 0, s = 1;
		char c = getchar();
		while(c < '0' || c > '9'){
			if(c == '-') s = -1;
			c = getchar();
		}
		while(c >= '0' && c <= '9'){
			x = (x << 3) + (x << 1) + (c ^ '0');
			c = getchar();
		}
		return x * s;
	}
	inline void write(int x){
		if(x < 0){
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace fastIO;
signed main() {
	int T = read();
	while(T--){
		string s;
		cin >> s;
		s = s + s;
		int len = s.size();
		bool flag = 0;
		int maxlen = 0, nowlen = 0;
		f(i, 0, len-1, 1){
			if(s[i] == '0') flag = 1, nowlen = 0;
			if(s[i] == '1'){
				nowlen++;
				maxlen = max(maxlen, nowlen);
			}
		}
		if(flag == 0){
			len /= 2;
			write(len * len);
		}else{
			maxlen++;
			write((maxlen / 2) * ((maxlen + 1) / 2));//一个向上取整。一个向下取整。
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Scrolling_Ball (赞：3)

题意是求最大面积嘛，转换一下那不就是求最大长度吗（因为有 $0$ 在，所以两堆 $1$ 是完全分开的）。

然后 $s$ 要右移 $n$ 次，所以首尾相接的也要算在里面，直接把 $s$ 翻个倍就行了。

然后就剩把长度转换成最大面积这个问题了。

随便打几个表就很容易发现规律了：

```
1111    11111    111111      1111111
 1111    11111    111111      1111111
  1111    11111    111111      1111111
   1111    11111    111111      1111111
            11111    111111      1111111
                      111111      1111111
                                   1111111
```
要求最大面积，长方形的长宽的差就要最小（小学知识，易得）。

发现 $4$ 的是 $2\times 3$，$5$ 的是 $3\times 3$，$6$ 的是 $3\times 4$，$7$ 的是 $4\times 4$。

所以就可以发现 $n$ 为偶数时，面积是 $\dfrac{n\times (n+2)}{4}$，$n$ 为奇数时为 $\dfrac{(n+1)\times (n+1)}{4}$。

把这两种情况合起来就是 $\dfrac{n+2}{2}\times\dfrac{n+1}{2}$ 啦。

哦，对了，还需要特判一下 $s$ 全为 $1$ 的情况，这样是不能算首尾相接的。


上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t;
string s;
int main()
{
    cin >> t;
    while(t -- )
    {
        cin >> s;
        s = s + s;
        ll sum = 0, ma = 0;
        for(ll i = 0; i < s.size(); i ++ )
            if(s[i] == '0')ma = max(ma, sum), sum = 0;
            else sum ++ ;
        ma = max(ma, sum);
        if(ma == s.size())cout << ma / 2 * ma / 2 << endl;//特判
        else cout << (ma + 2) / 2 * ((ma + 1) / 2) << endl;
    }
    return 0;
}
```

---

## 作者：liaoxingrui (赞：3)

# [题目](https://www.luogu.com.cn/problem/CF1820B)

## 这道题可以分为两种情况：

### 1 . 全是 1 的字符串 ：

这种情况下 ， 我们可以特判 ：
```cpp
cout<<s.size()*s.size()<<endl;
```


### 2 . 有 0 的字符串 ：

这种情况下 ， 由于要最大的一块 ， 所以我们要取最长的部分 ， 把最开头的和最末尾的 1 可以连接起来就可以了 ， 实现起来很简单，只用将字符串复制一份拼接在末尾即可 ：
```cpp
s+=s
```

在这样的情况下 ， 我们可以找到一个规律 ：
$$\frac{n+2}{2} \times \frac{n+1}{2}$$

# 代码 ：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define st string
using namespace std;
st s;
ll t;
int main(){
	ios::sync_with_stdio(0);**CF1820B**
    cin.tie(0); 
    cout.tie(0);
	cin>>t;
	while(t--){
		cin>>s;
		s+=s;
		ll len=s.size(),ma=0,sum=0;
		for(ll i=0;i<len;i++){
			if(s[i]=='1') sum++;
			else ma=max(ma,sum),sum=0;
		}
		ma=max(ma,sum);
		if(ma==len) cout<<((len/2)*(len/2))<<endl;
		else cout<<(((ma+2)/2)*((ma+1)/2))<<endl;
	}
	return 0;
}
```

---

## 作者：wei2013 (赞：1)

萌新第一篇题解，如有错误还请指出。

[题目传送门](https://www.luogu.com.cn/problem/CF1820B)

**题目大意**：简单来说就是求最大的面积。

***思路***：

这题可以分成两个类别。


第一种：
字符串全部都是 $1$。

那便可以组成 $len\times len$ 个单位的矩阵。

第二种：
字符串不全是 $1$。

不难发现，结果只和最长连续全一子串有关。我们也就只用思考最长连续全一子串所能围成最大的图形面积。

求最大面积需要用到小学知识：长与宽的差最小，长方形的面积越大。

由于要最长连续全一子串，所以我们要取最长的部分，需要把最开头的和最末尾的 $1$ 可以连接起来，实现起来很简单，只用将字符串复制一份拼接在末尾即可：
`
s+=s
`

打表找个规律可得公式：

 $$\frac{len+1}{2} \times \frac{len+2}{2}$$
 
其中，$len$ 为字符串长度。
 
***代码***：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	long long t;
	scanf("%lld",&t);
	while(t--){
		string s;
		cin>>s;
		s+=s;// 首尾连接
		long long sum=0,cnt=0,len=s.length();
		for(int i=0;i<len;i++){// 求最长连续全一子串
			if(s[i]=='1'){
				cnt++;
			}else{
				sum=max(sum,cnt);
				cnt=0;
			}
		}
		sum=max(sum,cnt);
		if(sum==len){
			printf("%lld\n",(len/2)*(len/2));
		}else{
			printf("%lld\n",((sum+1)/2)*((sum+2)/2));
		}
	}
	return 0;
} 
```
望审核通过！

---

## 作者：Zimo_666 (赞：1)

## B. JoJo's Incredible Adventures

有点意思的一道题，我们考虑这样一个序列循环转换为矩阵的样子，必然是一种类似错位的感觉，则我们考虑长宽的和是一定被确定的，即为连续 $1$ 的个数加一。我们考虑在长宽和被确定的时候显然是长和宽更接近使得面积更大。由于可以从结尾循环到前面，我们考虑把序列复制两遍，扫一遍上面的即可。当然，如果序列全部为 $1$ 时即为整个序列长度平方。

复杂度 $O(n)$。

[Code](https://codeforces.com/contest/1820/submission/223799186)

---

## 作者：Rookie_t (赞：0)

首先特判，如果该序列全部为 $1$，直接输出以字符串长度 $len$ 为边长的正方形面积，就是 $len^2$。

然后就是字符串有 $0$ 也有 $1$ 的情况。

首先统计出最长连续的 $1$ 的数量，如果遇到一个 $0$ 就把这个 $sum$ 清零。

首先，和不变，差小积大。

就把首尾两端的 $1$ 连接起来，$s = s+s$。 

最后就是 ${{len+1}\over2}\times{{len+2}\over2}$。 

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long T;
long long sum,maxn;
string s;
int main(){
    cin>>T;
    while(T--){
        cin>>s;
        s = s + s;
        sum = maxn = 0;
		for(long long i = 0;i<s.size();i++){
			if(s[i] == '0'){
				if(sum>maxn){
					maxn = sum;
				}
				sum = 0;
			}
			else{
				sum++;
			}
		}       
		if(sum>maxn){
			maxn = sum;
		}
        if(maxn == s.size()){
        	cout<<maxn*maxn/4<<endl;
		}
		else{
			cout<<(maxn+2)/2*((maxn+1)/2)<<endl;
		}
    }
    return 0;
}
```

---

## 作者：wxy11130 (赞：0)

### 思路分析
首先，长和宽的**数值差**越小，**面积**就越大。

由题意得，有一下两种情况：

- 全为 `1` 字符串。
- 有一个或多个 `0` 的字符串。

第一种情况很好解决，只用输出 `s.size()*s.size()` 即可。

第二种情况，由于 `0` 会将 `1` 的段分成**若干个**部分，所以我们要取**最长**的部分，但是最开头的和最末尾的 `1` 可以**连接**起来，也就是说，只用将字符串复制一份拼接在末尾即可。

```cpp
//by 1013713 1/6 9:32,2024
#include<bits/stdc++.h>
using namespace std;
string s;
long long t;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		cin>>s;
		s+=s;
		long len=s.size(),ma=0,sum=0;
		for(long long i=0;i<len;i++)
			if(s[i]=='1') sum++;
			else ma=max(ma,sum),sum=0;
		ma=max(ma,sum);
		if(ma==len) cout<<((len/2)*(len/2))<<endl;
		else cout<<((ma+2)/2)*((ma+1)/2)<<endl;
	}
	return 0;
}
```


---

## 作者：xu222ux (赞：0)

## [CF1820B](https://www.luogu.com.cn/problem/CF1820B)

## 思路


不难发现，结果只和最长连续全一子串有关。

因为只有最长的全一子串有关组成的正方形矩阵才最大。

**所以题目就变成了这个字符串的最长全一子串能够够成多大的矩形？？**

找一找规律不难发现这个公式：

$$\dfrac{ans+1}{2}\times\dfrac{ans+2}{2}$$



其中 $ans$ 为最长全一子串长度。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        s+=s;
        long long cnt=0,ans=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='1')cnt++;
            else{
                ans=max(ans,cnt);
                cnt=0;
            }
        }
        ans=max(ans,cnt);
        if(ans==s.size())cout<<(ans/2)*(ans/2)<<endl;
        else cout<<((ans+1)/2)*((ans+2)/2)<<endl;
    }
    return 0;
}
```

---

## 作者：tmp_get_zip_diff (赞：0)

## 思路

首先我们知道，长和宽越接近，面积就越大。

那么，我们分两种情况讨论：

- 全 `1` 字符串。
- 有 `0` 的字符串。

第一种情况很好解决，只用输出 `s.size()*s.size()` 即可。

关键是第二种情况，由于 `0` 会将 `1` 的段分成若干个部分，所以我们要取最长的部分，很好解决，但是最开头的和最末尾的 `1` 可以连接起来，所以只用将字符串复制一份拼接在末尾即可。

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long

__inline__ __attribute__((always_inline)) int read()
{
	char ch=getchar();
	int f=1,x=0;
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))x=x*10+(ch-'0'),ch=getchar();
	return x*f;
}

inline void _write(int x)
{
	if(x>9)_write(x/10);
	putchar((x%10)+'0');
}

__inline__ __attribute__((always_inline)) void write(int x,int f=0)
{
	if(x<0)putchar('-'),x=-x;
	_write(x);
	if(f!=0)putchar(char(f));
}

int t;
string s;

signed main()
{
	int T=read();
	while(T--)
	{
		cin>>s;
		int len=s.size()*2;
		s="S"+s+s;
		bool flag=false;
		int maxi=0,nl=0;
		for(int i=1;i<=len;i++)
		{
			if(s[i]=='0')
			{
				flag=true;
				nl=0;
			}
			else
			{
				nl++;
				maxi=max(maxi,nl);
			}
		}
		if(flag==false)
			write(len*len/4,'\n');
		else
			write((maxi/2+1)*((maxi+1)/2),'\n');
	}
	return 0;
}
```

---

## 作者：Light_az (赞：0)

显然根据题意我们先得到两种特殊情况：

- 字符串全部为 `1`，此时最大矩阵的面积是 $n \times n$。

- 字符串全部位 `0`，此时最大矩阵的面积是 $0$。

然后对于普通情况讨论：

首先观察样例我们发现，最大矩阵的长宽之和是字符串中 `1` 的最长连续长度 $len$ 再加上 $1$。

又因为当一个矩阵的长宽之差最小时，矩阵面积最大，因此我们将长定为 $\frac{len+1}{2} $，宽定为总长度减去长 $len+1-\frac{len+1}{2} $，此时矩阵的面积就一定最大。

但是注意，根据样例 $3$ 我们发现头和尾的 `1` 也连续，因此破环为链，将下标取模字符串长度即可。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(ll i=j;i<=n;i++)
#define D double
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10;
ll n,m,k,x,y,u,v,w,cnt,ans,t,l,r,len,T,id;
ll mn=INT_MAX,mx=0,p,opt;
string s;

int main(){
	cin>>T;
	while(T--){
		cin>>s;
		ans=0;
		len=s.size();
		F(i,0,len-1) ans+=s[i]-'0';
		if(ans==len) cout<<ans*ans<<"\n";
		else if(ans==0) cout<<0<<"\n";
		else{
			ans=cnt=0;
			F(i,0,2*len-1){
				if(s[i%len]=='1') cnt++;
				else cnt=0;
				ans=max(ans,cnt);
			}
			ans++;
			cout<<(ans/2)*(ans-ans/2)<<"\n";
		}
	}

	return 0;
}


```


---

