# [ABC286C] Rotate and Palindrome

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc286/tasks/abc286_c

長さ $ N $ の文字列 $ S $ が与えられます。$ S_i\ (1\leq\ i\ \leq\ N) $ を $ S $ の左から $ i $ 番目の文字とします。

あなたは以下の $ 2 $ 種類の操作を好きな順番で $ 0 $ 回以上好きな回数行うことができます。

- $ A $ 円払う。 $ S $ の左端の文字を右端に移動する。すなわち、$ S_1S_2\ldots\ S_N $ を $ S_2\ldots\ S_NS_1 $ に変える。
- $ B $ 円払う。 $ 1 $ 以上 $ N $ 以下の整数 $ i $ を選び、 $ S_i $ を好きな英小文字で置き換える。
 
$ S $ を回文にするためには最低で何円必要ですか？

 回文とは ある文字列 $ T $ について、 $ T $ の長さを $ |T| $ として、全ての整数 $ i $ ($ 1\ \le\ i\ \le\ |T| $) について、 $ T $ の前から $ i $ 文字目と後ろから $ i $ 文字目が同じであるとき、またそのときに限って、 $ T $ は回文です。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 5000 $
- $ 1\leq\ A,B\leq\ 10^9 $
- $ S $ は英小文字からなる長さ $ N $ の文字列
- $ S $ 以外の入力は全て整数
 
### Sample Explanation 1

最初に $ 2 $ 番目の操作を $ 1 $ 回行います。$ 2 $ 円払い、$ i=5 $ として $ S_5 $ を `e` で置き換えます。 $ S $ は `rrefe` となります。 次に $ 1 $ 番目の操作を $ 1 $ 回行います。$ 1 $ 円払い、$ S $ は `refer` となります。これは回文です。 よって $ 3 $ 円払うことで $ S $ を回文にすることができました。 $ 2 $ 円以下払うことで $ S $ を回文にすることは不可能なので、これが答えです。

### Sample Explanation 2

答えは $ 32 $ bit 整数に収まらない場合があることに注意してください。

## 样例 #1

### 输入

```
5 1 2
rrefa```

### 输出

```
3```

## 样例 #2

### 输入

```
8 1000000000 1000000000
bcdfcgaa```

### 输出

```
4000000000```

# 题解

## 作者：_xEr_ (赞：4)

### 先看题面


------------
~~太简洁了不会有人看不懂吧~~。

### 再想思路


------------
这题可以枚举每一种可能，我的方法如下方所写：

枚举操作 1：可以把 $S$ 复制一份连接上去，假设 $ S\gets \texttt{abc}$ 那么修改后 $S$ 就为 $\texttt{abcabc}$，这样任意截取一个从 $S_i$ 开始，长度为 $n$ 的子串，就相当于进行了 $i$ 次操作 1，相应的，代价也就是 $A \times i$。不理解的话见下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/h5pjgrzi.png)

因为 $n$ 次操作相当于没操作，所以其实我们只需要枚举 $0 \sim n-1$ 次就可以了，~~上图是为了美观才枚举了第 $n$ 次的~~。

记录操作 2：如上图，我们已经得到了 $n$ 次操作（ $0 \sim n-1$ ）。所以我们只要判断是否该次操作得到的字符串为左右是否对称（也就是回文串）就可以了，遇到不对称的字符就把代价增加 $B$。

## _**The Code**_
```cpp
#include<iostream>
using namespace std;
long long n,a,b;
unsigned long long ans=1e35,now;
string s;
int main(){
	cin>>n>>a>>b>>s;
	s=s+s;//复制并连接
	for(int i=0;i<n;i++){
		int l=i,r=i+n-1;//分别从左右扫来检查对称
		now=i*a;
		for(;l<r;l++,r--)
			now+=b*(s[l]!=s[r]);//记录代价
		ans=ans>now?now:ans;//更新最小值
	}
	cout<<ans;
}
```





---

## 作者：Enjoy2024 (赞：2)

因为 $n\le 5\times 10^3$，所以可以使用 $O(n^2)$ 的暴力枚举。

那么考虑枚举 $A$ 操作的次数，判断需要执行多少次 $B$ 操作即可。

容易发现，执行 $A$ 操作后的字符串可以直接暴力算出来，然后使用类似于判断回文字符串的方式判断需要执行几次 $B$ 操作，求最小值即可。

然而需要特判全部执行 $B$ 操作的花费。

注意开 `long long`。

---

## 作者：12345678hzx (赞：1)

## 题目大意
有一个长度为 $n$ 的字符串 $S$，你可以进行如下两种操作任意次：

- 花费 $A$ 代价，让 $S$ 的第一个字符移到最后一位。
- 花费 $B$ 代价，修改 $S$ 的任意一个字符。

## 思路
显然的，操作一最多进行 $n-1$ 次，否则没有意义，则我们就可以枚举使用多少次操作一，剩下的用操作二去满足要求，求出最小代价，最后要注意的点是需要开 `long long`。
## 代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

long long n,a,b,ans=1e18;
string s;
int main() {
	cin>>n>>a>>b>>s;
	for(int i=0;i<n;i++) {
		long long cnt=i*a;
		string s1="";
		for(int j=i;j<n;j++) s1+=s[j];
		for(int j=0;j<i;j++) s1+=s[j];
		for(int j=(n-1)/2;j>=0;j--) if(s1[j]!=s1[n-j-1]) cnt+=b;
		ans=min(ans,cnt);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Coffee_zzz (赞：1)

一眼题。

### 分析

可以在 $s$ 的后面复制一个 $s$，判断时更方便。

接着 $i$ 从 $0$ 开始，一直到 $n-1$，暴力判断以 $i$ 开始的 $n$ 个字符需要修改几个字符才能形成回文字符串，统计答案并输出即可。

### 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	int n,t,a,b,m,i,j,sum;
	string s,p;
	cin>>n>>a>>b>>s;
	m=n/2*b;
	p=s+s;
	for(i=0;i<n;i++){
		t=n/2,sum=a*i;
		for(j=0;j<t;j++){
			if(p[i+j]!=p[i+n-1-j]) sum=sum+b;
		}
		m=min(m,sum);
	}
	cout<<m;
	return 0;
}
```

---

## 作者：LiaoYF (赞：1)

## 题意
有两种操作：

1. 将字符串的第一个字符移到最后一个，一次花费 $A$ 元。

2. 将字符串的任意一个字符替换为另一个字符，一次花费 $B$ 元。

问最少花费多少元把原字符串变为一个回文串。
## 做法
直接枚举。先进行操作一，再根据左右不同字符的个数，判断要进行多少次操作二。操作一最多只有 $N$ 种情况。  
例如`abc`：
```
abc
bca
cab
```

又回到了`abc`。
## 代码
这里我的实现是每次把开头一个字符放到结尾后面。
```cpp
#include<iostream>
#define int long long
using namespace std;
int n,a,b,ans=9223372036854775807ll;
char s[10005];//数组开两倍
signed main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++)cin>>s[i];
    int mid=n/2;
    for(int i=0;i<n;i++){
        int cnt=0;
        for(int j=1;j<=mid;j++){//比较不同字符的个数
            if(s[i+j]!=s[i+n+1-j]){
                cnt++;
            }
        }
        ans=min(ans,i*a+cnt*b);
        s[n+i+1]=s[i+1];
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

## 思路
暴力枚举操作一，然后剩下的用操作二来进行修改，然后取最小值就行了。

操作一还有一种更好的方法，将两个相同字符串接在一起，虽然不快多少，这种方法和下标模上 $n$ 是一样的。

可以在字符串中间加上 `#`，这样就可以同时解决奇字符串和偶字符串。

最后记得开 `long long`。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=6000;
string s;
signed main(){
	int n,a,b;
	string str;
	cin>>n>>a>>b>>str;
	str+=str,s='#';
	for(auto ch:str)s+=ch,s+='#';
	int ans=LONG_LONG_MAX;
	for(int k=0;k<s.size()/2;k++){
		int i=k+n;
		int cnt=0;
		for(int j=1;j<=n;j++){
			if(s[i+j]!=s[i-j]){
				cnt+=b;
			}
		}
		cnt+=((k+1)/2)*a;
		ans=min(ans,cnt);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：makerlife (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/AT_abc286_c) | [AT 原题传送门](https://atcoder.jp/contests/abc286/tasks/abc286_c)

## 思路

观察题目可以发现 A 操作最多只能执行 $n$ 次，超过以后字符串又会回到初始状态。

首先考虑 A 操作如何实现，一种办法是将 $S$ 在原串后复制一遍，通过移动一个记录初始位置的指针（本文中为 $i$）来实现截取 $n$ 位字符。每次移动指针代价都为 $A$。

接下来考虑 B 操作的代价计算。我们可以判断之前截取的字符串是否为回文。~~回文字符串判断应该都会吧~~通过移动起始位置和结束位置指针，比较两指针对应的字符是否相同进行回文判断，每次遇到不同，总代价都加 $B$。

值得注意的是结束位置指针的取值。每次 A 操作执行完成，截取出的字符串末位下标为 $n+i-1$，在此基础上再减去起始位置即可。

回文判断部分代码：

```cpp
/*i 为 A 操作中起始位置指针，t 为总代价*/
for(int j=0;j<n/2;j++)//回文判断循环变量只需到 n/2
{
	int x=i+j;//起始位置
	int y=n+i-1-j;//结束位置
	if(s[x]!=s[y])
	{
		t+=b;
	}
}
```

以 A 操作中*起始位置指针*作为外层循环变量，范围 $0\sim n-1$，内层循环为回文串判断。总时间复杂度 $O(n^2)$。

### 一些小细节

- 观察数据范围可知需使用 $\text{long long}$；

- 最大值可取值 $2^{62}$ 即 `1ll<<62`。

## 完整代码

```cpp
#include<cstdio>
#include<string>
#include<iostream>
#define INF 1ll<<62
#define ll long long
#define int ll
using namespace std;
int n,a,b;
int ans=INF;
string s;
signed main()
{
	scanf("%lld%lld%lld",&n,&a,&b);
	cin>>s;
	s+=s;
	for(int i=0;i<n;i++)
	{
		int t=a*i;
		for(int j=0;j<n/2;j++)
		{
			int x=i+j;
			int y=n+i-1-j;
			if(s[x]!=s[y])
			{
				t+=b;
			}
		}
		ans=min(ans,t);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc286_c)
## 题意

现在给你一个长度为 $N$ 的字符串，有以下两种操作：

- A 操作：花费 $A$ 将字符串的第一位放到最后一位。
- B 操作：花费 $B$ 修改字符串重任意一个字母。

问至少花多少金币能让原来的字符串 $S$ 变成回文字符串。

## 思路

由题意，不难想出 A 操作的操作次数最多是 $n - 1$ 次，所以我们只需要先确定 A 操作的操作次数，再确定 B 操作的操作次数来构成回文。

```cpp
   s += s;//构成一个环，方便操作
   long long ans = 1e18;//保存答案
   for(int i = 0; i < n; i++){//n次A操作
	long long sum = a * i;//A操作花费的钱
	for(int j = 0; j < n / 2; j++){//B号操作
		int l = i + j;//左点坐标
		int r = i + n - 1 - j;//右点坐标（左点的对称点）
		if(s[l] != s[r])sum += b;//如果两个字符不一样，增加钱数
	}
	ans = min(ans, sum);//更新答案
   }
```
为了方便操作，所以将字符串 $S$ 构成一个环来处理。外层循环 A 操作可能执行的操作次数，同时用 $sum$ 变量存储第一个操作花费的钱；内层循环执行 B 操作可能执行的操作次数：先判断对称位置：$i + j$ 和 $i + n - 1 - j$ 两点的字母是否一致，如果不一致，在变量 $sum$ 上累加上一次执行 B 操作所用的钱，最后需要更新答案，保留最优结果，这样就可以让 A 操作都在 B 操作之前完成了。

## 注意事项：

- 在计算最优答案时，变量要开成 long long  。
- 最后要输出回车。

# AC 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	long long n, a, b;
	string s;
	cin >> n >> a >> b >> s;
	s += s;//构成一个环，方便操作
	long long ans = 1e18;//保存答案
	for(int i = 0; i < n; i++){//n次第一个操作
		long long sum = a * i;//第一个操作花费的钱
		for(int j = 0; j < n / 2; j++){//2号操作
        //两点坐标
			int l = i + j;
			int r = i + n - 1 - j;
			if(s[l] != s[r])sum += b;//如果两个字符不一样，增加钱数
		}
		ans = min(ans, sum);//更新答案
	}
	cout << ans << endl;
	return 0;
}
```

------------

### [AC记录](https://www.luogu.com.cn/record/100401807)

---

## 作者：tZEROちゃん (赞：0)


考虑枚举进行 A 操作的次数，我们设这个次数是 $i$，那么显然当 $i=0$ 时和当 $i=n$ 时，序列就相同了。

我们只需要从 $1\sim n$ 枚举 $i$，对于每次循环将字符串在上一次操作的基础上后移 $1$ 位，然后再枚举有哪些位不是对称的，显然这就是需要 B 操作的次数。

对每次循环更新答案的最小值即可。

特别的，当 $i=n$ 时其实 A 操作次数只需要 $0$ 次。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long

char s[5010];

signed main() {
  int n, a, b; cin >> n >> a >> b;
  cin >> (s + 1);
  int ans = 1E18;
  for (int i = 1; i <= n; ++i) {
    char lst = s[1];
    for (int i = 1; i < n; ++i) s[i] = s[i + 1];
    s[n] = lst;
    auto ck = [&](char c[]) {
      int ans = 0;
      for (int i = 1, j = n; i <= j; ++i, --j) {
        if (c[i] != c[j]) ++ans;
      }
      return ans;
    };
    ans = min(ans, i % n * a + ck(s) * b);
  }
  cout << ans << endl;
}
```

---

## 作者：lfxxx (赞：0)

首先咱们来考虑一个问题。

操作顺序是否与答案有关。

**显示没有**。

因为先对位置 $4$ 进行操作 $2$ 再进行操作 $1$ 和先进行操作 $1$ 再对位置 $3$ 进行操作 $2$ 毫无区别。

那么由于操作 $1$ 做 $n$ 次就会回到原来的序列，因此枚举至多 $n$ 次操作 $1$ 并且每次判断回文位置上字符不相同的数量就可以了。

代码时间：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans=1e18;
int A,B,n;
int sum;
string s;
int work(){
    int cnt=0;
    for(int i=0;i<s.size();i++)
        if(s[i]!=s[s.size()-i-1])
            cnt++;
    return cnt/2*B;
}
signed main(){
    cin>>n>>A>>B;
    cin>>s;
    for(int i=1;i<=s.size()+10;i++){
    ans=min(ans,work()+sum);
    char op=s[0];
    
        for(int i=1;i<s.size();i++)
            s[i-1]=s[i];
    s[s.size()-1]=op;
    sum+=A;        
    }
    cout<<ans;
}
```


---

