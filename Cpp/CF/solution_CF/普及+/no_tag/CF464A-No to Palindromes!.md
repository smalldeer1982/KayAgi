# No to Palindromes!

## 题目描述

Paul hates palindromes. He assumes that string $ s $ is tolerable if each its character is one of the first $ p $ letters of the English alphabet and $ s $ doesn't contain any palindrome contiguous substring of length 2 or more.

Paul has found a tolerable string $ s $ of length $ n $ . Help him find the lexicographically next tolerable string of the same length or else state that such string does not exist.

## 说明/提示

String $ s $ is lexicographically larger (or simply larger) than string $ t $ with the same length, if there is number $ i $ , such that $ s_{1}=t_{1} $ , ..., $ s_{i}=t_{i} $ , $ s_{i+1}&gt;t_{i+1} $ .

The lexicographically next tolerable string is the lexicographically minimum tolerable string which is larger than the given one.

A palindrome is a string that reads the same forward or reversed.

## 样例 #1

### 输入

```
3 3
cba
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
3 4
cba
```

### 输出

```
cbd
```

## 样例 #3

### 输入

```
4 4
abcd
```

### 输出

```
abda
```

# 题解

## 作者：panyanppyy (赞：2)

## Solution

很显然的两个性质：

- 字符串可以转化成一个长度为 $n$ 的 $p$ 进制数。

- 长度 $> 3$ 的回文串一定包含长度 $\le3$ 的回文串，所以长度 $>3$ 的回文串就不用考虑了。

接下来考虑做法：

由于他给定的本来就是一个没有回文的字符串，所以 $+1$ 后改变的一定是一段后缀，所以考虑那段后缀怎么消除回文串就行了。

1. 如果有进位，就把当前位设成最小值，进位，并向前考虑前一位。

2. 如果有回文，那就让当前这位 $+1$。

3. 这一位考虑完了，向后考虑。

如果进位一直到 $0$ 了那就说明无解，否则直接输出即可。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register
#define all(x) (x).begin(),(x).end()
using namespace std;
template<typename T_>void operator+=(vector<T_>&x,const T_&y){x.emplace_back(y);}
int n,m;
string s;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>s,s=' '+s;
	int i=n;s[i]++;//初始进位
	for(;1<=i&&i<=n;){
		if(s[i]>=m+'a')s[i]='a',s[--i]++;
		else if((i>1&&s[i]==s[i-1])||(i>2&&s[i]==s[i-2]))s[i]++;
			//有无回文
		else i++;
	}
	if(!i)cout<<"NO\n";
	else s.erase(s.begin()),cout<<s<<'\n';
	return 0;
}
```

---

## 作者：Transparent (赞：1)

很容易可以想到把字符串当作一个${p}$进制数，
每次在最后以为加${1}$，再判断回文，
如果没有就输出，如果最高位溢出就一定不存在解。

------------

出现新的回文串只有${2}$种可能：

1、长度为${2}$的回文串，即当前位与它的前一位或后一位相等（${str[i]=str[i-1]}$或${str[i]=str[i+1]}$）。

2、长度为${3}$的回文串，即当前为与它前面的第二位或后面的第二位相等。（${str[i]=str[i-2]}$或${str[i]=str[i+2]}$）。

因为原串中不含长度为${2}$或长度${>2}$的回文串，
而长度${>3}$的回文串中心一定有一个长度大于${1}$的回文串，
所以不需要判断长度更长的回文串是否存在

------------

很显然如此优秀的暴力是很难通过的。。。

------------

如果某一位不符合要求（即与其它位构成了回文串），
那么就可以直接修改这一位，
如果还是每次在最末一位${+1}$，
除非进位修改了这一位，
那当前串一定不符合要求。

为了让下一次循环可以修改这一位，
可以把这一位后面的所有位都置为最大值（即${'a'+p-1}$），
这样下一次就可以通过进位直接处理不符合要求的字符

------------

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
char str[1001];
int n,p;
int main()
{
	scanf("%d%d",&n,&p);
	scanf("%s",str+1);//从第一位开始输入
	bool ans=0; 
	register int i,j;
	while(1)
	{
		j=n;
		str[j]++;
		while(j>1&&str[j]>='a'+p)//进位
		{
			str[j]-=p;
			str[--j]++;
		}
		if(j==1&&str[j]>='a'+p)//如果最高位溢出
		{
			ans=0;//标记
			break;
		}
		bool f=0;
		for(i=j;i<=n;i++)
		{
			if(i>2&&str[i]==str[i-2])//长度为3的回文串
			{
				f=1;
				break;
			}
			if(i>1&&str[i]==str[i-1])//长度为2的回文串
			{
				f=1;
				break;
			}
		}
		if(f)//如果不符合要求
		{
			for(j=i+1;j<=n;j++)//赋予最大值
			{
				str[j]='a'+p-1;
			}
		}
		else
		{
			ans=1;//符合要求就退出
			break;
		}
	}
	if(ans==0)//没有解输出NO
	printf("NO\n");
	else
	printf("%s\n",str+1);
	return 0;
}
```
~~又是恶评题~~

---

## 作者：小杨小小杨 (赞：1)

## 题意
浅显易懂。
## 思路
~~高精度滚出OI。~~     
用一个类似于高精度的方式，把字符串看成一个 $g$ 进制数，然后暴力枚举就行啦！    
评测结果：$\texttt{TLE}$    
~~那没事了。~~
分析一下，发现如果在第 $i$ 个位置（开始位置）发现了回文，那么就必须要把这个位置改变才能成立？    
所以就可以把这之前的直接修改，能快很多。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p,i,len,flag,ss[10010];
char s[10010];
int main(){
	scanf("%d %d%s",&n,&p,s+1);len=n;
	for (i=1;i<=n;i++) ss[n-i+1]=s[i]-'a';
	while (len==n){
		ss[1]++;flag=0;
		for (i=1;i<=len;i++) if (ss[i]>=p) ss[i+1]+=ss[i]/p,ss[i]%=p;
		if (ss[len+1]>0) break;
		for (i=1;i<=n-1;i++) if (ss[i]==ss[i+1]) flag=i;
		for (i=1;i<=n-2;i++) if (ss[i]==ss[i+2]) flag=max(flag,i);
		for (i=1;i<flag;i++) ss[i]=p-1;
		if (flag==0){for (i=len;i>=1;i--) printf("%c",ss[i]+'a');return 0;}		
	}
	printf("NO\n");
	return 0;
}
```


---

