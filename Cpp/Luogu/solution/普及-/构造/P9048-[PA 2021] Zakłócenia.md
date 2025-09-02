# [PA 2021] Zakłócenia

## 题目描述

定义一种小写字母到 $8$ 位 01 串的映射：

- 将小写字符的 ASCII 码转为 $8$ 位二进制数，如：$a \rightarrow 97 \rightarrow 01100001$。

现在小 A 有一个长度为 $n$ 的只含小写字母的字符串 $s$，他将这个字符串映射到了一个长为 $8n$ 的 01 字符串 $t$。

他打乱了 01 串 $t$ 得到 01 串 $t'$，请你根据打乱后的结果还原出一个 $s$。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq n \leq 10^5$。

## 样例 #1

### 输入

```
2
1100000011110111```

### 输出

```
ao```

## 样例 #2

### 输入

```
8
1011111010101100011011011010001010100011111111110001001001011010
```

### 输出

```
potyczki```

## 样例 #3

### 输入

```
1
00011000```

### 输出

```
NIE```

# 题解

## 作者：Furina_Hate_Comma (赞：8)

 一道**方程**数学题。

[题目传送门](https://www.luogu.com.cn/problem/P9048)
  
注意：
1. 由于 $t'$ 为乱序，所以我们不需要管输入的顺序，只需要关注 $0$ 与 $1$ 的数量。
2. $a$ 的 ASCII 码为 $97$，$z$ 的 ASCII 码为 $122$。
即 $01100001$ 到 $01111010$，其中含 $1$ 的数量不同情况分别有：   
$a$ 即 $01100001$，$c$ 即 $01100011$，$g$ 即 $011000111$，$o$ 即   $011001111$。  
他们分别代表了 $3,4,5,6$ 的情况(也可以是其他，但 $a,c,g,o$ 较小)。

至此，问题变成了用 $a,c,g,o$ 构造 $01$ 串。
接下来设 $S$ 表示 $t'$ 中 $1$ 的数量，$x_i$ 表示 ASCII 中含有 $i$ 个 $1$ 的字母在 $s$ 串中的数量 $(3 \le i \le 6)$。

列方程得：
$\begin{cases} 3x_3 + 4x_4 + 5x_5 +6x_6= S\\x_3+x_4+x_5+x_6=n\end{cases}$ 

解得 $x_4+2x_5+3x_6=S-3n$。
所以当且仅当 $3n \le S \le 6n$ 时有解。

最后就是利用贪心构造让 $x_3$ 非负。只需要先让 $x_6$ 尽量大，再具体将剩下的情况分类讨论，即：
- 如果 $S-3n-3x_6=1$ 则 $x_4=1,x_5=1$。
- 如果 $S-3n-3x_6=2$ 则 $x_4=0,x_5=0$。

最后就是大家最期待的放代码环节了！
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[800010];
int main(){
	int n,S=0;
	cin>>n>>s;
	for(int i=0;i<8*n;i++)S+=s[i]-'0';
	if(S<3*n||S>6*n){
		cout<<"NIE";
		return 0;
	}
	int x[4];
	x[1]=0;
	x[2]=0;
	x[3]=0;
	x[0]=0;
	x[3]=(S-3*n)/3;
	x[S%3]=1;
	x[0]=n-x[3]-x[2]-x[1];
	while(x[0]--)cout<<'a';
	while(x[1]--)cout<<'c';
	while(x[2]--)cout<<'g';
	while(x[3]--)cout<<'o';
	return 0; 
}
```


---

## 作者：ProzacPainkiller (赞：4)

不是背包题，而是**数学题**。

首先，因为 $t'$ 是被打乱的二进制 ASCII 码串，所以我们要还原成字符，只需要关注 $t'$ 和每个小写字符的二进制 ASCII 码串中 $1$ 的数量就行了。

遍历得到，小写字符中二进制 ASCII 码串中 $1$ 的数量只有 $3,4,5,6$ 四种可能，分别可以对应 ```a,c,g,o```。

设 $t'$ 中 $1$ 的数量为 $tot$，```a,c,g,o``` 的数量分别为 $x_0,x_1,x_2,x_3(x_0,x_1,x_2,x_3\in \mathbb{N})$，则可以得到一个方程组

$$
\begin{cases}
x_0+x_1+x_2+x_3=n\\
3x_0+4x_1+5x_2+6x_3=tot
\end{cases}
$$

下式减去三倍上式得 $x_1+2x_2+3x_3=tot-3n$。

容易看出当 $tot<3n$ 的时候无解（$3$ 个自然数不可能加出负数），同时要注意 $tot>6n$ 的时候显然同样无解（$x_0$ 绝对是负数了）。而当其他时候方程组是有解的。接下来让我们构造出一组解。

观察式子，我们通过要让 $x_0$ 尽量为非负的这么一个贪心思维，可以先让 $x_3=\lfloor \dfrac{tot-3n}{3}\rfloor$，那么 $tot-3n-3x_3$ 就只能是 $1$ 或者 $2$。很容易想到这样一种方案：
- 如果是 $1$，就让 $x_1=1,x_2=0$。
- 如果是 $2$，就让 $x_2=1,x_1=0$。

接下来让 $x_0=n-x_1-x_2-x_3$ 就行。

通过验证可以知道，当 $3n\le tot \le 6n$ 时，此方案确实是合法的。

最后贴上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
const char back[4]={'a','c','g','o'};
char t[8*N];
int n,tot;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>t;
	for(int i=0;i<8*n;i++)	tot+=t[i]-'0';
	if(tot<3*n||tot>6*n)	cout<<"NIE";
	else
	{
		int x[4]={0,0,0,0};
		x[3]=(tot-3*n)/3;
		x[tot%3]=1;
		x[0]=n-x[3]-x[2]-x[1];
		for(int i=0;i<4;i++)
			while(x[i]--)	cout<<back[i];
	}
	return 0;
}
```

---

## 作者：Light_Star_RPmax_AFO (赞：2)

## P9048 [PA2021] Zakłócenia 题解
这题我们先需要知道 ASCII 表中每个字符对应的二进制。

# [请看这里](https://blog.csdn.net/m0_59113542/article/details/122636186?ops_request_misc=&request_id=&biz_id=102&utm_term=%E6%AF%8F%E4%B8%AA%E5%AD%97%E6%AF%8Dascii%E7%A0%81%E7%9A%84%E4%BA%8C%E8%BF%9B%E5%88%B6&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-3-122636186.142^v73^wechat,201^v4^add_ask,239^v2^insert_chatgpt&spm=1018.2226.3001.4187)

因为有多种解我们只需要输出其中一种，所以我们在写的时候可以选择一的个数不一样多的字母各一个。



------------


其中有四种一数量不同的方案。

一：在二进制下出现了三个一。

选取 b。

二：在二进制下出现了四个一。

选取 e。

三：在二进制下出现了五个一。

选取 y。

四：在二进制下出现了六个一。

选取 w。


------------


输出什么的问题解决了，接下来我们来判断无解的情况：

我们可以看到最多一的时候也只有六个一，所以如果我们一的个数超过了  $6 \times$ 字母的总数 那么此时就是无解的。

同理如果在小于 $3 \times$ 字母的总数 时也是无解的。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
   	long long N,sum=0;
	string A;
	cin>>N>>A;//读入字母个数，与字符串。
	for(int i=0;i<8*N;i++){
		if(A[i]=='1')sum++;//计算有几个一。
	}
	if(sum<3*N||sum>6*N)cout<<"NIE";//判断无解。
	else {
		sum-=N*3;//先保证有 N 个 b。
		while(sum>=3&&N>0){//我们直接开始输出一最多的 w.
			sum-=3;
			cout<<'w';
			N--;//还需要输出字母数量减少。
		}
		if(N!=0&&sum){//把还剩下的 1 的个数，要特判，防止有全部 w 的情况
		    if(sum==1){
		        cout<<'e';
		    }
		    else if(sum==2)cout<<'y';
		    N--;
		}
		while(N>0){//把最后保底的 b 输出。
			cout<<'b';
			N--;
		}
	}
}
```



---

## 作者：NotNaLocker (赞：1)

## P9048 Zakłócenia 题解
先来展示一下我的 A 题历程……

总共 $15$ 次。

0,27,0,2,9,10,47,42,43,$CE$,40,55,52,54,$AC$

接下来进入正题。

## 题目思路

由于题目是 SPJ，可以不用和样例完全一样，于是我们的初步思路就是：
贪心算法。

先把字符串的 `1` 字符统计，再把可以造出的最大字母输出，即**二进制 ASCII 码的 `1` 字符最多的、并且范围在 $a-z$ 的字母**。然后再判断第二大的、第三大的。最后输出 `1` 字符最少的字母。这四个字母我使用 `a c g o` 四个字母（由小到大），如果不知道二进制ASCII码的点击[此处](https://blog.csdn.net/m0_59113542/article/details/122636186?ops_request_misc=&request_id=&biz_id=102&utm_term=%E6%AF%8F%E4%B8%AA%E5%AD%97%E6%AF%8Dascll%E7%A0%81%E7%9A%84%E4%BA%8C%E8%BF%9B%E5%88%B6&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-1-122636186.nonecase&spm=1018.2226.3001.4187)。

来演示一波：

就拿样例1来解释，它的原字符串为 `1100000011110111`。

我们知道 `o` 的二进制ASCII是 `01101111`，于是原字符串的前八个字符可改为： `01101111`。

此时用掉了 $6$ 个 `1`。原字符串有 $9$ 个 `1`。剩下 $3$ 个刚好可以填上一个 `a`。于是答案就是 `oa`。

下面的看代码吧，代码有更详细的解释。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string t;
int main(){
	int n,sum=0;
	cin>>n>>t;
	for(int i=0;i<8*n;i++){
		if(t[i]=='1') sum++; //统计1字符数量。
	}
	if(sum>6*n||sum<3*n){  //o字符6个1，a字符3个1，如果在这个范围之外，就直接输出NIE。
		cout<<"NIE"<<endl;
		return 0;
	}
	else{
		sum-=n*3;  //保留最后输出的a，等下直接输出。
		while(sum-3>=0&&n>0){  //每次输出最多的o，sum-3方便后面的if语句判断前二和前三大的字母。
			sum-=3;
			cout<<"o";
			n--;  //减去能输出的字母数量。
		}
		if(n!=0&&sum){  //如果还可以输出字母且sum大于0
			if(sum==1) cout<<"c";  //前三大
			else if(sum==2) cout<<"g";  //前二大
			n--;
		}
		while(n>0){  //如果还可以输出，只剩下a字符了，直接输出。
			cout<<"a";
			n--;
		}
	}
	return 0;  //华丽结束。
}
```
## Thanks for watching.

---

## 作者：ice_fish01 (赞：1)

## $\text{P9048 [PA2021]}$ Zakłócenia 题解

### 思路分析

这道题要使用一些~~小小的~~二进制知识和一些 ASCII 码知识。

~~由于洛谷禁止把读者当成没学过语言的**，所以这里只放一张图来解释。~~

![](https://cdn.luogu.com.cn/upload/image_hosting/vutv7267.png)

我们发现，小写字母的 $8$ 位 01 串的映射最少有 $3$ 个 1，最多有 $6$ 个 1。我们可以先判断无解的情况。

其中 $\texttt{a,c,m,w}$ 这 $4$ 个字母的 $8$ 位 01 串映射分别有 $3,4,5,6$ 个 1。我们可以就此完成对所有 1 的分配。

思路分析部分至此结束。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
string s,c = " acmw";
int n,len,sum1;
signed main()
{
	cin >> n;
	getline(cin,s);
	getline(cin,s);
	len = s.size();
	for(int i = 0;i < len;i++)
	{
		if(s[i] == '1') // 统计 1 的个数 
			sum1++;
	}
	if(sum1 < 3 * n || sum1 > 6 * n) // 无解 
	{
		puts("NIE");
		return 0;
	}
	int a[1+1+4+5+14];
	memset(a,0,sizeof(a));
	a[4] = (sum1 - 3 * n) / 3; // 统计次数 
	a[sum1 % 3 + 1] = 1;
	a[1] = n - a[4] - a[3] - a[2];
	for(int i = 1;i <= 4;i++)
	{
		while(a[i]--)
			cout << c[i]; // 按照已经算好的次数输出答案 
	}
	return 0;
}
```


**题解结束。**

---

