# 国際情報オリンピック日本代表プログラミングコンテスト (Welcome to IJPC)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/ijpc2012pr/tasks/ijpc_ijpc



# 题解

## 作者：Clare613 (赞：3)

## 题意
可以修改字符串，是字符串中含有 IJPC 的子序列，求最小修改次数。
## 思路
不难发现，这是一道 DP 题，所以说我们只要设计转移方程就可以了。\
我们对于第 $i$ 个字符，它可能是新起一个，或者接上之前的，所以需要考虑每种可能。如果正好符合的话，那么就可以直接接，不然就修改一下，最后只要特判一下开头就可以了。
## code

```cpp
#include <bits/stdc++.h>
using namespace std;
bool flag=0;
char a[4]={'I','J','P','C'};
int dp[100005][5];
signed main(){
	int n,cnt=0;
	memset(dp,0x3f,sizeof(dp));
	string x;
	cin>>n>>x;
	x=" "+x;
	if(x[1]=='I') dp[1][1]=0;
	else dp[1][1]=1;
	for(int i=1;i<=n;i++){
		if(x[i]=='I')dp[i][0]=0;
		else dp[i][0]=dp[i-1][0];
		for(int j=1;j<4;j++){
			if(x[i]==a[j]) dp[i][j]=min(dp[i-1][j],dp[i-1][j-1]);
			else dp[i][j]=min(dp[i-1][j],dp[i-1][j-1]+1);
		}
	}
	cout<<dp[n][3];
    return 0;
}
```

---

## 作者：Doveqise (赞：3)

这个题的翻译有毒吧...先吐槽一下翻译  
## 机翻  
![](https://cdn.luogu.com.cn/upload/pic/58971.png)
## 洛谷翻译
![](https://cdn.luogu.com.cn/upload/pic/58972.png)  
emmm(机翻就敢往上交)  
求助日语大佬大概理解了题意  
就是实现一个replace()函数  
(完全不知道这玩意咋judge)  
emmm AtCoder欢乐多  
切入主题  
一道字符串问题 就是改字符串  
看错题面
#### 不写main函数见祖宗 
## 以下为题解区
字符串模拟题  
就是依次寻找该字符串中的'I''J''P''C'，如果没有的话就自己改  
然后在操作的时候需要一些蜜汁骚操作  
例如QJPCIXYZ这样的，你就应该考虑将'Q'改为'I'获得较小的更改数 而不是将"XYZ"改为"JPC"  
机房dalao果然强如斯(  
细节见代码  
```c++
#include<bits/stdc++.h>
using namespace std;

int N;
char S[1005];

int replace(int N,char *S)
{
	int ans=4;
	for(int i=0;i<16;i++){
		int pos=0,j=0,k=0;
		while(j<4&&k<N)
		{
			pos+=i>>j&1;
			if(i>>j&1)
				k=find(S+k,S+N,"IJPC"[j])-S;
			if(k==N)
				break;
			j++;k++;
		}
		if(j==4)
			ans=min(ans,4-pos);
	}
	return ans;
}
signed main()
{
	scanf("%d",&N);
	cin>>S;
	printf("%d\n",replace(N,S));
	return 0;
}
```

---

## 作者：A_grasser (赞：3)

## 题意简化

求将一个字符串改成依次出现 `I`，`J`，`P`，`C` 四个字符的最小修改次数。

## 需要注意的地方

1. 注意按题目所给方式写出 `replace` 函数。建议到 AT 本地提交，洛谷容易 UKE，可能是代码的特殊要求造成的。

## 解法分析

最小修改次数……有点像 DP，那就写吧！

思路：将 $dp_{i,j}$ 表示前下标为为 $i$ 的输入字符串匹配到目标字符串前下标为 $j$ 的部分的最小修改次数。

目标字符串就是 `IJPC`。

---

初始化部分：

当输入字符串第一位为 `I` 时（有起始点），
$$dp_{0,0}=0$$
否则必须操作一次以获得起始点：
$$dp_{0,0}=1$$
并且后几位赋值最大值：
$$dp_{0,1}=dp_{0,2}=dp_{0,3}=5$$
那么之后下标 $1$ 至 $n-1$ 的部分就好处理多了。

---

当输入字符串第 $i$ 位为 `I` 时（新的开始）：
$$dp_{i,0}=0$$
否则（知道要初始化的原因了吧）：
$$dp_{i,0}=dp_{i-1,0}$$

---

当输入字符串第 $i$ 位为 `J`，`P`，`C` 时，接上去（$x$ 表示当前位在目标字符串的第几位）：
$$dp_{i,x}=\min(dp_{i-1,x-1},dp_{i-1,x})$$
否则：
$$dp_{i,x}=\min(dp_{i-1,x-1}+1,dp_{i-1,x})$$

---

代码也就显而易见了：

```cpp
int dp[n][4];
string t="IJPC";
//初始化 
if(s[0]=='I') dp[0][0]=0;
else dp[0][0]=1;
dp[0][1]=dp[0][2]=dp[0][3]=5;
for(int i=1;i<n;i++){
	//第一位的特殊处理 
	if(s[i]=='I') dp[i][0]=0;
	else dp[i][0]=dp[i-1][0];
	//后三位的处理
	for(int j=1;j<4;j++){
		if(s[i]==t[j]) dp[i][j]=min(dp[i-1][j-1],dp[i-1][j]);
		else dp[i][j]=min(dp[i-1][j-1]+1,dp[i-1][j]);
	} 
}
return dp[n-1][3];
```

最后说一句，我比较推荐万能头文件，这样可以省去很多不必要的麻烦。

## 完整代码

```cpp
//已通过 
#include<bits/stdc++.h> 
//万能头文件 
using namespace std;
int replace(int n,char s[]){//题意要求 
	int dp[n][4];
	string t="IJPC";
	//初始化 
	if(s[0]=='I') dp[0][0]=0;
	else dp[0][0]=1;
	dp[0][1]=dp[0][2]=dp[0][3]=5;
	for(int i=1;i<n;i++){
		//第一位的特殊处理 
		if(s[i]=='I') dp[i][0]=0;
		else dp[i][0]=dp[i-1][0];
		//后三位的处理
		for(int j=1;j<4;j++){
			if(s[i]==t[j]) dp[i][j]=min(dp[i-1][j-1],dp[i-1][j]);
			else dp[i][j]=min(dp[i-1][j-1]+1,dp[i-1][j]);
		} 
	}
	return dp[n-1][3];
}
```

---

## 作者：yangfengzhao (赞：1)

## 前言
正则表达式，是一种由许多标记来表示一个字符串的表达式。\
例如：```[A-Za-z0-9_]``` 就是来匹配**所有大小写字母**+**数字**+**下划线**的一个表达式。
### 标记 ```[]```
这个标记是用来**将一些连续的字串**/单独的符号来包括在其中。\
例如：```[A-Z]``` 是指匹配所有的**大写字母**。
### 标记 ```()```
将标记合成一个**组**。
### 标记 ```|```
这个符号是用来标记两个元素的关系，相当于**或**。\
那么，以下正则表达式：
```
(A|B|C)aa
```
将会匹配：```Aaa``` / ```Baa``` / ```Caa```。
### 标记```-```
表示**连续的字串**。例如：```[A-Z]```。
>注意到**升序原则**[^1]。
### 思路
首先，匹配 ```[IJPC]``` （${0}$ 步，因为不需要替换任何字母）\
然后匹配 ```(I[A-Z]PC)``` 等等（${1}$ 步，只有一个字母需要替换）\
同理，匹配需要替换 ${2,3,4}$ 个字母的表达式。\
大概的表达式应该是：
```
//0
IJPC
//1
[A-Z]JPC
I[A-Z]PC
IJ[A-Z]C
IJP[A-Z]
//2
[A-Z][A-Z]PC
[A-Z]J[A-Z]C
[A-Z]JP[A-Z]
I[A-Z][A-Z]C
I[A-Z]P[A-Z]
IJ[A-Z][A-Z]
[A-Z][A-Z][A-Z]C
[A-Z]...
```
>这个需要在 ```C++17``` 中使用[^2]！
## 后言
[^1]:```-``` 左右两边的元素应当保证左小右大。
[^2]:在 ```C++17``` 中，需要使用 ```<regex>``` 头文件，用来启用**正则表达式**，这个头文件提供了**查找**，**匹配**等函数。
>关于正则表达式的语法远远不止这些，加油 OIer！

---

