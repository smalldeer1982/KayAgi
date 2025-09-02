# [AGC039A] Connection and Disconnection

## 题目描述

给定一个字符串 $S$，令 $T$ 为 $S$ 的 $K$ 个副本首尾相接得到的字符串。  
我们可以重复进行以下操作：选择 $T$ 中的一个字符并将其替换为另一个字符。  
请最小化能使得 $T$ 中任意相邻字符不相同的最少操作数。

## 说明/提示

### 数据限制
- $1 \le |S| \le 100$。
- $S$ 仅由小写字母组成。
- $K \in [1,10^9] \bigcap \mathbb Z$。

### 样例解释 1
$T = \texttt{issiiissii}$。  
一种可行的方案是将其改写为 $\texttt{ispiqisyhi}$，此时任意相邻字符不相同。

## 样例 #1

### 输入

```
issii
2```

### 输出

```
4```

## 样例 #2

### 输入

```
qq
81```

### 输出

```
81```

## 样例 #3

### 输入

```
cooooooooonteeeeeeeeeest
999993333```

### 输出

```
8999939997```

# 题解

## 作者：cqbztz2 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT5615)

# 前言

这么水的题为什么没人写题解呢？

# 思路

我们可以用两个循环来统计：

* 第一个循环计算出把第一个字符串变成相邻字符不相同的操作数结果记为 ans1；

* 第二个循环计算出把字符串重复一次变成相邻字符不相同的操作数，结果记为   ans2；

$ ans2-ans1 $ 即为后续字符串需要的操作数。

这种方法无法准确计算如样例二那样所有的字符都是一样的，所以需要特殊判断，特殊处理。

# 代码

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long k,ans1,ans2;
  string s;
  bool check(){//判断是字符串是否所有的字符都是一样的
      for(int i=1;i<s.length();i++){
          if(s[i]!=s[i-1]){
              return false;
          }
      }
      return true;
  }
  int main(){
      cin>>s>>k;
      if(check()==true){如果所有的字符都是一样的，直接输出
          cout<<s.length()*k/2;
      }
      else{
          for(long long i=0;i<s.length();i++){//第一个循环求ans1
              if(s[i]==s[i+1]){
                  ans1++;
                  i++;
              }
          }
          for(long long i=0;i+1<s.length()*2;i++){//第二个循环求ans2
              if(s[i%s.length()]==s[(i+1)%s.length()]){
                  ans2++;
                  i++;
              }
          }
          cout<<ans1+(ans2-ans1)*(k-1);
      }
      return 0;
  }
```


---

## 作者：MattL (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/AT5615) & [原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/5615) 

很有意思的题目。

这里给一个做法最简单的题解。

---

**题意**

>一个字符串，复制很多遍，问最少改变多少个字符才能使得相邻字符没有一样的。

其实就是变向叫你找相邻一样的字符。

---

**解题**

首先，使得相邻的不重复，最多只需要 $3$ 个字符，$26$ 个字母足够的，不用担心无解。

然后，我们发现，每个字符都重复的一整个子串需要修改的字符数目是：
$$\left\lfloor\left|s\right|\div 2\right\rfloor$$

最后，直接扫一遍字符串，分割成一块块字符均相同的子串，计算出原字符串需要修改的字符个数，再乘上复制次数即可。


这就做完了？没有！还有特殊情况没考虑到！

1. 整个字符串的字符全都一样是，直接输出答案 $\left\lfloor\left|s\right|\times k\div 2\right\rfloor$
2. 首尾分割出的字符一样，且块长均为奇数，字符串的贡献 $+1$，但由于复制后首尾没有额外贡献，所以最终答案还需 $-1$。

---

**代码**

```cpp
#include<bits/stdc++.h> 
using namespace std;
string s;
long long n,cnt=1,ans,qp;//别忘了long long
int main()
{
	cin>>s>>n;
	for(int i=1;i<s.size();i++)
		if(s[i-1]==s[i])cnt++;//累加块长
		else qp=qp?qp:cnt,ans+=cnt/2,cnt=1;//计算贡献
 	if(cnt==s.size()&&(s.size()&1))cout<<cnt*n/2,exit(0);//特殊情况1
	ans+=cnt/2;//别忘了最后一个块
	if(s[0]==s[s.size()-1]&&(qp&1)&&(cnt&1))cout<<(ans+1)*n-1,exit(0);//特殊情况2
	cout<<ans*n<<endl;//别忘了*n
	return 0;
}
```

---

## 作者：ztntonny (赞：0)

## 题意
将一个给定的字符串首尾相接给定次数，形成新的字符串，问怎样消除该字符串中的所有连续字符。
## 思路
- 首先，这里有几个坑点：
1. 可能头尾会一样，就会对结果产生影响；
2. 可能会所有都一样，需要特判；
3. 可能会只有一个字符，需要特判；

所以下面是思路：正规的逐个找连续的数目，加入计数器中，当头尾都一样且长度都是奇数时，每个字符串的贡献加一，总数还需要减一，因为最后尾部不产生贡献。还要特判头尾只有一个的情况
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	string a;
	unsigned long long b , ans = 0 , s = 0 , if1 = 0 , if2 = 0;
	cin >> a >> b;
	long long lena = a.size();
	if ( lena == 1 )//特判只有一个字符
	{
		cout << b / 2 << endl;//这是本代码的一个核心，连续n个相同字符只需要改变n/2个
		return 0;
	}
	for ( int i = 1; i < lena; i++ )
	{
		if ( a[i] == a[i - 1] )//正规计数
		s++;
		if ( s == i - 1 && s % 2 == 0 && a[i] != a[i - 1] && s > 0 )//头部连续奇数次的话
		if1 = s + 1;//标记一下
		if ( if1 % 2 == 1 && i == lena - 1 && s % 2 == 0 && s > 0 && a[0] == a[lena - 1] )//尾部连续奇数个且与头部相等且头部也连续奇数的话
		{
			ans++;//贡献加一
			if2 = s + 1;//标记一下
		}
		if ( s == lena - 1 )//如果全都一样特判
		{
			cout << ( s + 1 ) * b / 2 << endl;
			return 0;
		}
		if ( a[i] != a[i - 1] || i == lena - 1 )//正规判断
		{
			ans += ( s + 1 ) / 2;//计数器加上贡献
			s = 0;
		}
	}
	if ( a[0] == a[lena - 1] && a[1] != a[0] && a[lena - 2] != a[0] )//如果头尾只有一个相等
	{
		ans++;//贡献加一
		if2++;//标记一下
	}
	if ( if2 > 0 )//说过要减一个
	cout << ans * b - 1 << endl;
	else
	cout << ans * b << endl;
	return 0;
}
```


---

## 作者：haotian1234 (赞：0)

## 题意暗示
其实这道题就是数一数有多少个一样的字符（~~呵呵呵~~）
## 题目分析
- 首先，你要算出在原先的字符串中将它改成任意相邻字符不相同的最少操作数。——说人话，就是打一遍暴力。
- 其次，你要求出，将一个相同的字符串放在后面将这个字符串改成任意相邻字符不相同的最少操作数。——说人话，就在打一遍暴力（因为这样能够找出开头与结尾加上后的小差错）
- 最后，将这两个步数一减（第二个减第一个）乘上 $K - 1$ ，再加上第一个，答案就在你眼前。
- 还有像样例二这样所有字母都一样的点，要用特判
## 题目坑点
1. 要开 long long
1. 就没了（~~额~~）

下面上大家最最最关心的东西——代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long ls,n,i,ans1,ans2;//开long long
string s;
int pd(){
	for (i=0;i<ls-1;i++)
		if (s[i]!=s[i+1]) return 0;
	return 1;
}//特判
int main(){
	cin>>s;ls=s.size();
	scanf("%lld",&n);
	if (pd()) {
		printf("%lld\n",ls*n/2);
		return 0;
	}//特判
	for (i=0;i<ls;i++)
		if (s[i]==s[i+1])
			ans1++,i++;//暴力
	for (i=0;i+1<ls*2;i++)
		if (s[i%ls]==s[(i+1)%ls])
			ans2++,i++;//暴力
	printf("%lld\n",ans1+(ans2-ans1)*(n-1));
	return 0;
}
```


---

## 作者：Obviathy (赞：0)

## 前言：
本蒟蒻又来写水题题解了！
## 解题思路：
### 一、整体思路
因为经过副本拼接后的字符串 $T$ 的长度会非常长，所以我们就直接考虑怎样只通过计算一个 $S$，推导出全部需要的操作数。
### 二、具体做法
1. 我们可以用一个 $a$ 数组，记录字符串 $S$ 的结构。所谓结构，就是这个字符串里，相同字母的分布顺序和数量。比如：$S$ 是 $  \texttt {"aabbbcdddd"}$，那么它的结构可以记为 $2,3,1,4$。实现这一步操作的代码也很简单:
```cpp
int cnt = 0,top = 0;
	for(int i = 1;i <= s.size();i ++){//计算 s 构成 
		if(s[i] == s[i-1])cnt++;
		else{
			a[top++] = cnt+1;
			cnt = 0;	
		} 
	}
```

2. 有了结构，就可以进一步计算了。一个长度为 $l$ 的字母全部相同的字符串要想让它相邻字母互不相同，我们只需要隔一个改变一个就行，最小操作数就是 $[l/2] $。由于复制体是首位相接，所以对中间的几段结构是没有影响的，直接计算即可。（当然，在此之前，我们要特判：如果字符串字母全部相同，即上文代码中的 $top == 1$是，要直接输出）
```cpp
if(top == 1){
		ans = (s.size()*k)/2;
		cout<<ans<<endl;
		return 0;
	}
for(int i = 1;i < top-1;i ++)ans+=a[i]/2;//除去头尾要特判  
```
3. 接下来就是判断首尾，就是两种情况：$\begin{cases}head = tail:ans=ans \times k+(head+tail)\div 2 \times (k-1)+head\div 2 +tail\div 2;\\else:ans = (ans + head\div 2 +tail\div 2)\times k;\end{cases}$（前面的是头尾字符的判断，后面的 $head$ 和 $tail$ 是数量）

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,a[200];
long long ans;
string s;
int main(){
	cin >> s >> k;
	int cnt = 0,top = 0;
	for(int i = 1;i <= s.size();i ++){//计算 s 构成 
		if(s[i] == s[i-1])cnt++;
		else{
			a[top++] = cnt+1;
			cnt = 0;	
		} 
	}
	if(top == 1){
		ans = (s.size()*k)/2;
		cout<<ans<<endl;
		return 0;
	}
	for(int i = 1;i < top-1;i ++)ans+=a[i]/2;//除去头尾要特判  
	if(s[s.size()-1] == s[0]){
		ans*=k;
		ans+=(a[0]+a[top-1])/2*(k-1);
		ans+=a[0]/2 + a[top-1]/2;	
	}
	else{
		ans += a[0]/2 + a[top-1]/2;//因为有取整，所以必须这样写
		ans*=k;
	}  
	cout<<ans<<endl;
	return 0;
}

```



---

