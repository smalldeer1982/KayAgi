# Reverse Binary Strings

## 题目描述

You are given a string $ s $ of even length $ n $ . String $ s $ is binary, in other words, consists only of 0's and 1's.

String $ s $ has exactly $ \frac{n}{2} $ zeroes and $ \frac{n}{2} $ ones ( $ n $ is even).

In one operation you can reverse any substring of $ s $ . A substring of a string is a contiguous subsequence of that string.

What is the minimum number of operations you need to make string $ s $ alternating? A string is alternating if $ s_i \neq s_{i + 1} $ for all $ i $ . There are two types of alternating strings in general: 01010101... or 10101010...

## 说明/提示

In the first test case, string 10 is already alternating.

In the second test case, we can, for example, reverse the last two elements of $ s $ and get: 0110 $ \rightarrow $ 0101.

In the third test case, we can, for example, make the following two operations:

1. 11101000 $ \rightarrow $ 10101100;
2. 10101100 $ \rightarrow $ 10101010.

## 样例 #1

### 输入

```
3
2
10
4
0110
8
11101000```

### 输出

```
0
1
2```

# 题解

## 作者：yu__xuan (赞：9)

### 题目

[CF1437B Reverse Binary Strings](https://www.luogu.com.cn/problem/CF1437B)

### 思路

一次翻转可以使得连续的 $0$ 的个数减一并且连续的 $1$ 的个数减一，或者只是连续的 $0$ 的个数减一或连续的 $1$ 的个数减一。答案是连续的 $0$ 的个数和连续的 $1$ 的个数的最大值。

### Code

```cpp
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>

int max(int a, int b) { return a > b ? a : b; }

int t, n;
std::string sss;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        std::cin >> sss;
        int ans1 = 0, ans0 = 0;
        //std::cout << sss << '\n';
        for (int i = 1; i < n; ++i) {
            if (sss[i] == '1' && sss[i - 1] == '1') ++ans1;
            if (sss[i] == '0' && sss[i - 1] == '0') ++ans0;
        }
        printf("%d\n", max(ans1, ans0));
    }
    return 0;
}

```

---

## 作者：itisover (赞：4)

前置：

1.**两个相邻的相等的数**：如 $1100$，有两组**两个相邻的相同的数**，分别为 "11" 和 "00"，这两组是相反的。

对于一个串，有两种情况：

①有偶数$(cnt)$个两个相邻的相同的数：对于其中一组两个相邻的相同的数，一定对应一组与它相反的两个相邻的相同的数(一组"11"一定对应一组"00")，每次翻转这相反的两组之间的数（不包括两端点），都可以让这两组相反的两个相邻的相同的数配对，即变为两组"10"或两组"01"。

>如："$\textcolor{blue}{1}\textcolor{red}{10010}\textcolor{blue}{0}110$"，可以翻转红色部分的数，蓝色的为两端点，两组相反的两个相邻的相等的数是开头的"$\textcolor{blue}{1}\textcolor{red}{1}$"和末尾的"$\textcolor{red}{0}\textcolor{blue}{0}$"。翻转之后变成了"101**00**10**11**0"，再翻转一次就成了"1010101010"

所以一共需要 $cnt/2$ 步。

②有奇数$(cnt)$个两个相邻的相同的数，则一定只有一组两个相邻的相同的数找不到与它相反的，则需要多用一步来翻转它，使其合法。翻转它之后，就有偶数个了。所以一共需要 $(cnt+1)/2$ 步。

综上，一共需要 $(cnt+1)/2$ 步就可以翻转成目标串。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,ans;
char s[N];
int main(){
  scanf("%d",&T);
  while(T--){
    ans=0;
    scanf("%d%s",&n,s);
    for(int i=1;i<n;i++)
      if(s[i]==s[i-1]) ++ans;
    printf("%d\n",(ans+1)>>1);
  }
  return 0;
}
```


---

## 作者：Thomas_Cat (赞：2)

这题我们需要先推到一个式子：

当这个数 $x,y$ 需要反转的时候，反转步骤如下：

> 前置知识：$[i,j]$ 表示 区间 $i$ 到 $j$ ，如果命名一个一维数组 $a$ ，则 $[i,j]$ 表示 $a_i \sim a_j$ 

- 反转 $[x,y]$
- 反转 $[x+1,y-1]$
- 反转之后 $x,y$ 的 $\texttt{0,1}$ 字符串即可翻转

---

于是这题的思路我们就完美的解决了。

于是我们现在令 $s$ 为 $\texttt{0,1}$ 字符串即：$s \in {0,1}$ 。

我们只需要找到连续的 $\texttt{0,1}$ 然后反转中间的部分即可。

通过观察发现：我们只需要找到连续的 $\texttt{0,1}$，令 连续 $\texttt{0,1}$ 为 $sum$。

于是答案就等于 $\left\lfloor\dfrac{sum+1}{2}\right\rfloor$ 。

于是代码就简单了许多：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int n,sum=0;
       	string s;
        cin>>n>>s;
        for(int i=0;i<n;i++)
            if(s[i]==s[i+1]) sum++;
        cout<<ceil((sum+1)/2)<<endl;
    }
    return 0;
}
```

---

## 作者：skyskyCCC (赞：1)

## 前言。
打模拟赛自闭了，找这么一道题练练思维。
## 分析。
声明：该篇题解的字符串下标均是从 $0$ 开始。

所谓翻转，就是将一个数组 $a_i,a_{i+1},a_{i+2}\ldots a_{i+n}$ 变换成 $a_{i+n},a_{i+n-1}\ldots a_{i+1},a_i$ 的过程。我们首先分析一下样例 $3$ 的变化过程。

首先初始为 $11101000$ 然后将下标从 $1$ 到 $5$ 的字符串 $11010$ 翻转成为 $01011$ 构成新的 $10101100$ 字符串，其次将下标从 $5$ 到 $6$ 的字符串 $10$ 翻转成为 $01$ 构成新的 $10101010$ 字符串，满足要求，故最多需要翻转 $2$ 次。

我们发现，这两次翻转中的子串都是含有至少一个 $1$ 包含在原先连续的 $1$ 子串中。我们考虑 $11$ 与 $00$ 的情况。

为什么？很显然，对于一个字符串，如果其中包含 $11$ 那么它必须至少经过一次翻转才能使两个 $1$ 分离，对于 $00$ 同理。所以我们直接看有几个 $11$ 然后进行暴力翻转，再看有几个 $00$ 然后进行暴力翻转即可。

为什么不能同时拆散 $00$ 与 $11$ 使他们分离？因为对于同一个字符串，我们要考虑到翻转后**不会再出现**相同且相邻的两个数，所以不能同时翻转 $00$ 与 $11$ 防止重新组合，或再次形成原字符串。举个例子：
- 例如 $0011$ 显然翻转 $01$ 就可以了，但如果我们统计 $00$ 并同时统计 $11$ 就会形成 $1100$ 很显然陷入了死循环。

总结一下，我们找 $11$ 和 $00$ 并不是为了翻转它们自身，而是为了分离他们。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;
int t,n;
string s;
int ans,ans2;
int main(){
	cin>>t;
	while(t--){
		ans=ans2=0;//注意初始化。
		cin>>n>>s;
		for (int i=0;i<n;i++){
			if(s[i]=='1'&&s[i+1]=='1'){
				ans++;
			}
			else if(s[i]=='0'&&s[i+1]=='0'){
				ans2++;
			}
		}
		if(ans<ans2) ans=ans2;
		cout<<ans<<"\n";
	}
	return 0;
}
```
## 后记。
这个翻转还是很简单的，起码没有后续操作。

大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：小王子2021 (赞：1)

## 题意分析

这个题目其实并没有多么麻烦，也是一道比较结论的题，先从样例中找规律：

	10->转换0次

	0110->转换1次（有两个连续的1）
    
	111010000->转换2次（有三个连续的1和三个连续的0）
    
规律：可以从有几个连续的 $0$ 和几个连续的 $1$  中入手。

由样例可得要取两个中个数大的，即为 $ans$ ,输出 $ans-1$ 即可。

如有三个连续的1，两个连续的0，即最少转换两次。（3-1=2）

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100001];
int T,n;
int main()
{
	cin>>T;
	while(T--)
	{
		int ans0=0,ans1=0;
		cin>>n>>s+1;
		for(int i=2;i<=n;i++)
            if(s[i]==s[i-1])//如果两者连续
			{
                if(s[i]=='0')ans0++;//求连续的0
                else ans1++;//求连续的1
            }
       	cout<<max(ans0,ans1)<<endl;
	}
   return 0;
}
```







---

## 作者：Archy_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1437B)

## 题目简述：

$T$ 组数据，每组数据给出字符串长度 $len$ 和字符串 $s$。

求出通过翻转 $s$ 的子串使 $s$ **变为 $0$，$1$ 交替的串的最小次数**。

## 思路：

细看样例，对于**每 $2$ 个连续的数，必定要翻转 $1$ 次**，所以我们可以求出最大连续出现的 $0$ 和最大连续出现的 $1$ 中**较大的那个**。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,len,cnt1,cnt0;
string s;
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){//t组数据
		cin>>len>>s;//长度与字符串
		cnt1=0,cnt0=0;//初始化
		for(register int i=0;i<len-1;i++)
			if(s[i]==s[i+1]){
				if(s[i]=='0')cnt0++;//连续的0
				if(s[i]=='1')cnt1++;//连续的1
			}
		cout<<max(cnt0,cnt1)<<"\n";//输出较大的
	}
	return 0;
}
```

---

## 作者：xyta (赞：0)

这题不多说啊，很简单。

## 思路：
我们只需要用两个变量来记录连续两个字符都为 0 或者都为 1 。然后取 max 即可。

原理就是你找到一个连续的相同的字符就需要把他们分开，及就需要进行一次反转，而取 max 是因为，你把相邻最多的都分开，由于字符串中非零及一，所以剩下的就自动排好了。
## AC 代码：

废话少说，直接上代码！

```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)//多组数据 
	{
		int n;
		string a;
		cin>>n>>a;//字符串输入 
		int o1=0,o2=0;//用来存储连续两个字符为0和1的数量 
		for(int i=1;i<a.size();i++)
		{
			if(a[i]==a[i-1] and a[i]=='0')//连续两个0 
			{
				o1++;//o1哈哈哈 
			}
			if(a[i]==a[i-1] and a[i]=='1')//连续两个1 
			{
				o2++;//十年o1一场空， 不开o2见祖宗 
			}
		}
		cout<<max(o1,o2)<<endl;//求最大值为答案 
	}
	return 0;//结束 
}
```

带注释代码 AC 记录：

[在这里](https://www.luogu.com.cn/record/73340899)


好了，讲完了，不要抄题解 o ~ （ 动动你发财的小手给个赞呗！）

---

## 作者：一啦啦啦一 (赞：0)

### 解题思路

 明确题意：我们要用最少的操作将 $0 1$ 串变得 $0$  $1$ 相间。
 
 首先，我们可以将任意一个子序列翻转。显而易见，我们每次只能使一对**相邻的相同数字**分开，即 $00$ 或 $11$。
 
 所以，我们只需要统计有多少对**相邻的相同数字**即可。（因为 $0$ 和 $1$ 相互匹配，所以 相邻的 $0$ 的对数 和 相邻的 $1$ 的对数 要分开计数，最后答案取最大值。）
 
### Code

~~看代码可能更好理解。~~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		string s;
		cin>>n;
		cin>>s;
		int ans=0,anss=0;
		for(int i=0;i<n;i++)
		{
			if(s[i]=='1'&&s[i+1]=='1') ans++;
			if(s[i]=='0'&&s[i+1]=='0') anss++;
		}	
		cout<<max(ans,anss)<<endl;
	}
	return 0;
}
```


---

## 作者：fisheep (赞：0)

## 题意：

长度为$N$的只含$0/1$的子串，$0$的数目和$1$的数目均为$\frac{2}{n}$

操作：$[L,R]$内的子串反转

求使得整个串`01`交替的最少操作数

## 想法：

这种题，只需记录结果，而不用去管交替的过程。

如果碰到`00`，那么找到下一个`11`，中间的`01`所有进行反转。所以一个`00`，就需要消耗一个`11`来恢复`01/10`

所以记录一下`00`，`11`的数目$c1$,$c2$，然后取两者之间的最大值即可。

如果$sum1!=sum2$，结尾是可能存在`001`这种的，这个时候就不是成对消耗了。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}

int t,n;
int main(){
    t=read();
    while(t--){ 
    int n;
        n=read();
        string s;
        cin>>s;
        int sum1=0,sum2=0;
        for(int i=0;i<n;i++){
            if(s[i]==s[i+1]&&s[i]=='1') sum1++;
            if(s[i]==s[i+1]&&s[i]=='0') sum2++;
        }
        
       printf("%d\n",max(sum1,sum2));
    }
}
```

---

## 作者：Sora1336 (赞：0)

和 zzy 讨论了一段时间才过的题，还是比较有意思的。

大概题意就不多赘述了。

我们对于一个长度为 $n$ 的 01 串，我们如果发现有连续的 0 或 1 ，我们就可以把其中一个区间旋转，用一个与其不同的数来代替。这样的话，我们统计的区间就会被分为连续的 0 和连续的 1，最坏情况下每一次至多可以把两个数归位，则答案就是 01 串中 0 或 1 连续的数量除以 2 向上取整。

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
	int t;
	cin >> t;
	while(t --) {
		int n, ans = 0;
		char a[100005];
		cin >> n >> a;
		for(int i = 0; i < n; i ++) if(a[i - 1] == a[i]) ans ++;
		cout << ceil((double)ans/2) << endl;
	}
}
```

---

## 作者：Tenshi (赞：0)

~~这不是昨天的比赛吗qwq~~

【分析】：首先我们需要明白一件事：在01串中对换任意位置的一对0和1（而且不引起其他的变化）是完全可行的：如果说该对01是相邻的，直接翻过来；如果不相邻，将他们所在的区间（记为[l,r]）翻过来，然后再将区间[l+1,r-1]翻一次就可以了。

那么，如何实现操作数最小化呢？

第一步就是，确定你最终想要的01串的形态（有且仅有下面两种）：

①： 1010……10

②： 0101……01

好，怎么确定呢？

给个例子：1111010000

这个串中第一个元素是1，如果你想要01串形态变为②

那么就要使第一个1变为0，最后的0变为1，如果将它们直接对换，可知操作数是增加的（这里值得动手证一下）。类似地，可以讨论得到其他方式让第一个1变为0，最后的0变为1也会使操作数增加。（其他情况也可以类似讨论）

确定形态后，我们可以将当前串和最终串写出来进行比对：
```cpp

1 1 1 1 0 1 0 0 0 0
  ↓   ↓ ↓ ↓ ↓   ↓
1 0 1 0 1 0 1 0 1 0
```
在这里，将没有箭头的区间称为“相同的区间”，有箭头的则称为“不相同的区间”

下直接给出结论：相同的区间若参与变换，则操作数是不减的。

所以我们尽量对“不相同的区间”进行操作，可知连续的该类区间贡献是1（直接翻过来），而如果一定要在操作中包含“相同的区间”（如上面的两个单独的箭头），则贡献为2（还要翻回去），所以分别对他们统计一次就可以了。

由此，可以结合一下代码理解：

```cpp
if(s[0]=='1'){
			for(int i=0;i<len;i++){
				if(i&1) b[i]=0;
				else b[i]=1;
			} 
			
			int ans=0;
			for(int i=0;i<len;i++){
				bool flag=0;
				while(a[i]!=b[i]){
					flag=1;
					i++;
				}
				if(flag) ans++;
			} 
```

这里很多结论都是直接给的，可能不严格，希望大家提出哪里有问题qwq谢谢

完整代码：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int a[100001];//a储存原串
int b[100001];//b储存目标串
int main(){
	int t;
	cin>>t;
	while(t--){
		int len;cin>>len;
		string s;
		cin>>s;
		for(int i=0;i<len;i++) a[i]=s[i]-'0';
		if(s[0]=='0'){
			for(int i=0;i<len;i++){
				if(i&1) b[i]=1;
				else b[i]=0;
			} 
			
			int ans=0;
			for(int i=0;i<len;i++){
				bool flag=0;
				while(a[i]!=b[i]){
					flag=1;
					i++;
				}
				if(flag) ans++;
			} 
			cout<<ans<<endl;
		}
		if(s[0]=='1'){
			for(int i=0;i<len;i++){
				if(i&1) b[i]=0;
				else b[i]=1;
			} 
			
			int ans=0;
			for(int i=0;i<len;i++){
				bool flag=0;
				while(a[i]!=b[i]){
					flag=1;
					i++;
				}
				if(flag) ans++;
			} 
			cout<<ans<<endl;
		}
	}
	return 0;
}
```




---

## 作者：qian_shang (赞：0)

 [题目传送门](https://www.luogu.com.cn/problem/CF1437B)

经过简单的手摸+打表可以得出一个玄学结论：

记连续两个相同0或1的个数$sum$,最后翻转次数为 $\frac{sum+1}{2}$

考虑如何证明：

如果现有一排列好的序列，只有第$i$位和第$j$位的01顺序错位了，那么一般它们会产生四个连续段如：111和000，对于这种情况我们可以交换两次变为正常序列，即翻转$[i,j]$和$[i+1,j-1]$,但还有一些特殊情况

- $j-i=1$ 这时序列为（0011或1100）产生两个连续段，也只用翻转一次
- $i=1$ 或 $j=n$ 这时只产生了三个连续段，但还是需要两次翻转
- $i=1$ 且 $j=n$ 这时产生了两个连续段，只需要翻转一次$[2,n-1]$

### 所以我们可以得出结论$ans=\frac{sum+1}{2}$

---

