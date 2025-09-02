# New Skateboard

## 题目描述

Max wants to buy a new skateboard. He has calculated the amount of money that is needed to buy a new skateboard. He left a calculator on the floor and went to ask some money from his parents. Meanwhile his little brother Yusuf came and started to press the keys randomly. Unfortunately Max has forgotten the number which he had calculated. The only thing he knows is that the number is divisible by $ 4 $ .

You are given a string $ s $ consisting of digits (the number on the display of the calculator after Yusuf randomly pressed the keys). Your task is to find the number of substrings which are divisible by $ 4 $ . A substring can start with a zero.

A substring of a string is a nonempty sequence of consecutive characters.

For example if string $ s $ is 124 then we have four substrings that are divisible by $ 4 $ : 12, 4, 24 and 124. For the string 04 the answer is three: 0, 4, 04.

As input/output can reach huge size it is recommended to use fast input/output methods: for example, prefer to use gets/scanf/printf instead of getline/cin/cout in C++, prefer to use BufferedReader/PrintWriter instead of Scanner/System.out in Java.

## 样例 #1

### 输入

```
124
```

### 输出

```
4
```

## 样例 #2

### 输入

```
04
```

### 输出

```
3
```

## 样例 #3

### 输入

```
5810438174
```

### 输出

```
9
```

# 题解

## 作者：Marsrayd (赞：8)

## [题目传送门](https://www.luogu.com.cn/problem/CF628B)
## 题意简述：
给定一个只包含数字的字符串 $S$，请计算有多少个子串能够被 $4$ 整除，对于一个子串允许有前导 $0$。

## $\texttt{SOLUTION}$
首先，我们要明白什么样的数能被 $4$ 整除。

小学奥数告诉我们，末两位能被 $4$ 整除的数一定能被 $4$ 整除。

这是为什么呢？

让我来简要证明一下：

>我们设一个数为 $100a+b$ ，则 $b$ 就是这个数的末两位。

>所以 $4|b$。

>又因为 $4|100$。

>所以 $4|(100a+b)$

>即这个数能被 $4$ 整除。

有了这个结论，这道题就非常 $\texttt{naive}$ 了，如果一个字符串以一个能被 $4$ 整除的两位数结尾，那么它也一定能被 $4$ 整除。

所以我们只要看当前的最后两个字符即可。

如果当前的最后两个字符可以被 $4$ 整除，那么以它为结尾的子串都可以被 $4$ 整除（当然自己也以自己结尾）。

于是答案就可以加上这两个字符之前的字符个数$+1$。

不过还有个小细节。上面所计算的子串的长度都是 $>=2$ 的，而 $0,4,8$ 这三个长度为 $1$ 的子串也可以被 $4$ 整除。

这里需要特判。

然后就 $\texttt{AC}$ 啦

时间复杂度 $\mathcal{O}(n)$ （$n$ 为字符串长度）

$\texttt{AC CODE}$

```cpp
#include<bits/stdc++.h>
using namespace std;
char ch,pre;
long long ans,sum;
bool is[10][10];
int main()
{
	ch=pre=getchar(),ans=(ch=='0'||ch=='4'||ch=='8');
	for(int i=0;i<=96;i+=4) is[i/10][i%10]=1;
	while(ch>='0'&&ch<='9')
	{
		ch=getchar(),++sum;
		if(ch>'9'||ch<'0') break;
		if(is[pre-'0'][ch-'0']) ans+=sum;
		if((ch=='0')||(ch=='4')||(ch=='8')) ++ans;
		pre=ch;
	}
	printf("%lld",ans);
	return 0;
}
```

~~如果我的题解对您有帮助的话能不能点个赞呢qwq~~



---

## 作者：Engulf (赞：2)

考虑到一个性质（小学数奥内容），如果 $4 |n$ 的**后两个数字**，那么 $4|n$。

比如 $114514191981024$，后两个数字是 $24$，被 $4$ 整除，那么整个数就被 $4$ 整除。

那么，只要发现有连续两个数字 $x,y$ 是被 $4$ 整除的，那么前面所有以 $x,y$ 结尾的都会对答案产生贡献。

最后再加上单个数字的情况即可。

```cpp
// author: TMJYH09
// created on: 2022/05/28 19:11:02
#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;
    cin>>s;
    long long ans=0;
    for(auto &c:s)if((c-'0')%4==0)ans++;
    for(int i=s.size()-1;i>=1;i--){
        int x = (s[i-1]-'0')*10+(s[i]-'0');
        if(x%4==0)ans+=i;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：ZBN2022 (赞：0)

### 解法引入

首先，我们思考一个问题：什么样的数可以被 $4$ 整除。

结论：末两位数被 $4$ 整除的数可以被 $4$ 整除

证明：设一个数形如：
$a_1 \times 10^{n-1} + a_2 \times 10^{n-2}+...+a_{n-1} \times 10^1+a_n \times 10^0$

这个数被 $4$ 整除。

那么，我们可以把这个数写成：
$(a_1 \times 10^{n-3}+a_2 \times 10^{n-4}+...+a_n-2 \times 10^0) \times 100 + a_{n-1} \times 10 + a_n \times 1$

$\because 100 = 25 \times 4$

所以 $4$ 整除末两位数。

因此，我们可以使用一个数的末两位数是否能被 $4$ 整除来判断一个数是否能被 $4$ 整除。

### 对于本题

我们从字符串的第一位开始扫描，如果碰到有两位整除 $4$，则以这两位结尾的字符都被 $4$ 整除。

假设这是字符串的第 $i$ 位( $i$ 从 $0$ 开始)，字符串为 $s$,长度为 $len$。

显然经过观察可以发现，这样的两个字符可以对答案做出 $i+1$ 的贡献。

然后累加到 $ans$ 即可。

### 小细节

对于上面的情况，是无法考虑到 $s_i$ 本身被 $4$ 整除的情况。

所以说当我们扫描的第 $i$ 位的时候要判断。

如果 $s_i = 0,4,8$ 则 `ans++`。

然后，因为最后一位 $s_{len-1}$ 是无法和下一位组成两位数的。

所以，我们把这一位单独拿出循环判断是否为 $2,4,8$。

最后，本题的 $ans$ 如果用 int 类型会爆掉，所以我们得使用 long long 定义 $ans$。

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

string s;
ll ans;

int main() {
    cin >> s;
    for(int i(0); i < s.length() - 1; ++i) { //末两位整除4
        if(((s[i] - '0') * 10 + (s[i + 1] - '0')) % 4 == 0)
            ans += (i + 1);
        if(s[i] == '0' || s[i] == '4' || s[i] == '8') //单独一位整除4
            ans++;
    }
    if((s[s.length() - 1] - '0') % 4 == 0) //最后一位特殊判断
        ans++;
    cout << ans << endl;

    return 0;
}
```

---

## 作者：EthanOI (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF628B)
## 思路分析
我们首先要考虑如何判断一个多位数为 $4$ 的倍数

设这个数为 $\overline{a_na_{n-1}a_{n-2}\cdots a_1a_0}$ ，则根据[位值原理](https://baike.baidu.com/item/%E4%BD%8D%E5%80%BC%E5%8E%9F%E7%90%86/56162290?fr=aladdin)，

$\overline{a_na_{n-1}a_{n-2}\cdots a_1a_0}=100\times\overline{a_na_{n-1}a_{n-2}\cdots a_2}+\overline{a_1a_0}\equiv\overline{a_1a_0}\pmod{4}$

因此，我们只需要判断末两位数是否为 $4$ 的倍数即可
## 代码实现
设数字串为 $s$ ，若 $4\mid\overline{s_is_{i+1}}$ ，则 $\overline{s_0s_1\cdots s_is_{i+1}}$ ， $\overline{s_1s_2\cdots s_is_{i+1}}$ ， $\cdots$ ， $\overline{s_is_{i+1}}$ 均为 $4$ 的倍数，共有 $i+1$ 个满足的数字串，代码如下（不加注释版）：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
long long ans;
int main()
{
	cin >> s;
	int len = s.length();
	for (int i = 0; i < len - 1; i++)
		if (((s[i] - '0') * 10 + (s[i + 1] - '0')) % 4 == 0) ans += (i + 1);
	return 0;
}
```
结果连样例都过不了，想想问题

可以发现，先前的推导中，满足的数字串一定有至少 $2$ 位，那如果只有一位呢？所以要加上一位的情况，详情见代码。

[$\mathcal{AC}\text{ }\mathcal{CODE}$](https://www.luogu.com.cn/record/76810725) （希望大家觉得我的代码很好看）：
```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
long long ans; //int会爆空间 
int main()
{
	cin >> s;
	int len = s.length(); //可以优化时间 
	for (int i = 0; i < len - 1; i++)
	{
		if (((s[i] - '0') * 10 + (s[i + 1] - '0')) % 4 == 0) ans += (i + 1);
		if ((s[i] - '0') % 4 == 0) ans++;
	}
	if ((s[len - 1] - '0') % 4 == 0) ans++; //注意最后一位 
	cout << ans;
	return 0;
}
/*
输入样例：5810438174
输出样例：9 
*/
```
珍惜生命，请勿抄袭
## 总结
这道题最重要的是发现如何判断是否为 $4$ 的倍数，代码实现并不难，但有一些坑需要注意

~~求管理员通过~~

---

## 作者：chlchl (赞：0)

## 题意简化
给定一个由数字字符组成的字符串 $s$，问有多少个子串能被 $4$ 整除。

## 思路
由小学奥数可知，一个数的后两位如果能被 $4$ 整除，那么这个数一定能被 $4$ 整除。

我们可以枚举相邻两位组成的两位数（记为 $i$），看看能否被 $4$ 整除。若能，则所有以这两位为结尾的子串都符合要求，数量就是 $i$（因为子串只能连续）。

但是，我们还需判断一位的情况。而一位的情况是不需要延伸的，答案 $+1$ 即可。

时间、空间复杂度都是 $O(n)$。

别忘了开 ``long long``。
## 代码
珍爱生命，远离抄袭。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
long long n, ans;//别忘了 long long 
char s[N];

int main(){
    scanf("%s", s);
    n = strlen(s);
    for(int i=0;i<n;i++){
    	int a = s[i] - '0';
    	if(a % 4 == 0)	ans++;//特判一位数的情况 
	}
	for(int i=0;i<n-1;i++){
    	int a = (s[i] - '0') * 10 + (s[i + 1] - '0');
    	if(a % 4 == 0)	ans += i + 1;//因为我的下标从0开始，所以是i+1 
	}
	printf("%lld\n", ans);
    return 0;
}
```


---

## 作者：hxhhxh (赞：0)

## 大意

给定一个数字字符串 $ S $ ，求有多少个字串，使得该字串转化为数字后能被 $ 4 $ 整除。

## 思路

众所周知，末两位能被 $ 4 $ 整除的整数能被 $ 4 $ 整除。

对于这道题，如果 $ S_i = 0,4,8 \; (1 \leq i \leq |S|) $ ，那么单独抽出来 $ S_i $ 作为字串，它是能被 $ 4 $ 整除的（废话）。

如果 $ 4 \mid \overline{S_{i-1}S_i} (1 < i \leq n) $ ，那么如果选择一个 $ j(1 \leq j \leq i - 1) $ ，那么 $ 4 \mid \overline{S_jS_{j+1}\dots S_{i-1}S_i} $ ，而 $ j $ 有 $ i - 1 $ 种选法，所以答案要加上 $ i - 1 $ 。

将字符串全部扫一遍就可以了，记得开`long long`。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans;
char ch[300005];
signed main(){
	cin>>ch+1;
	n=strlen(ch+1);
	for(int i=1;i<=n;i++){
		if((ch[i]-'0')%4==0) ans++;
		if(i>1) if((ch[i]-'0'+10*(ch[i-1]-'0'))%4==0) ans+=i-1;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有一个长度为 $n$ 的数字串 $s$，求出有多少个子串能够被 $4$ 整除。

**数据范围：$1\leqslant n\leqslant 3\times 10^5$。**
## Solution
众所周知，如果最后两位数能够被 $4$ 整除，这个数也能够被 $4$ 整除，所以我们只需要看最能被 $4$ 整除的长度为 $1$ 或者 $2$ 的子串有多少个就好。

设能被 $4$ 整除的长度为 $1$ 的子串的个数是 $n_1$，能被 $4$ 整除的长度为 $2$ 的子串的个数是 $n_2$ 且第 $i$ 个子串的最高位在原串的位置是 $p_i$，答案就是 $\sum\limits_{i=1}^{n_2}p_i+n_1$。
## Code
```cpp
string s;
long long ans;

int main() {
	//This program is written in Windows 10 by Eason_AC
	cin >> s;
	int len = s.size();
	_for(i, 0, len - 1) {
		if(!((s[i] - '0' + (s[i - 1] - '0') * 10) % 4)) ans += i;
		if(!((s[i] - '0') % 4))	ans++;
	}
	writell(ans);
	return 0;
}
```

---

## 作者：Franka (赞：0)

~~没人写题解？我来水一发QAQ。~~
### **题目**
给出一个长度$\le 3×10^5$的字符串$S$，求$S$中能被$4$整除的字串有多少个。
### **思路**
因为长度$\le 3×10^5$，故用单重循环做。

因为是被**4整除**，所以只用判断最后两位是否能被4整除即可。

抓住以上重点，单重循环要枚举什么也就出来了：`从第一位枚举到字符串长度减一位，将S[i]和S[i+1]转成数字，累加即可`。

### 累加分两种情况

* #### 判断$S[i]+S[i+1]$是否是$4$的倍数，如果是，和加上现在的$i$。

* #### 判断$S[i]$是否是$4$的倍数，如果是，和加$1$。

$PS$：因为这里的长度$\le 3×10^5$，所以要开$int64$。

### **代码**
```pascal
var i,sum:longint;x:ansistring;s:int64;//不开int64见祖宗
begin
 readln(x);//读入x
 for i:=1 to length(x)-1 do//1到字符串x的长度-1
  begin
   val(x[i]+x[i+1],sum);//将两位转换到sum变量里
   if sum mod 4=0 then s:=s+i;//如果最后两位能被4整除，那么说明前面的任何一个数加上这两个数都可以被4整除
   if (x[i]='0') or (x[i]='4') or (x[i]='8') then s:=s+1;//如果这个数本身就能被4整数，s加1
  end;
 if (x[length(x)]='0') or (x[length(x)]='4') or (x[length(x)]='8') then inc(s);//特判最后一位
 writeln(s);//输出
end.
```

---

## 作者：kska (赞：0)

很明显，所有整百数都能被4整除，所以判断子串是否被4整除就可以只判断最后两位。
然而实际上在子串中，我们每发现一个子串能被4整除，其前面的字符加上该2位子串都能被4整除，所以在此时应ans++，但我们仍需考虑一位子串便能整除4的情况，所以要单独判断
~~~
#include <bits/stdc++.h>
using namespace std;
long long ans,k;
int main(){
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++){
		if(i==0){
			if(s[i]%4 == 0){
				ans++;
			}
			continue;
		}
		int k = (s[i-1]-'0');
		int t = (s[i]-'0');
	//	cout<<k<<t<<endl;
		if(t%4==0){
			ans++;
		}
		if((k*10+t) %4 == 0){
			ans+=i;
		}
	}
	cout<<ans<<endl;
	return 0;
}
~~~

---

