# Cutting Banner

## 题目描述

### 题意简述

给定只由大写英文字母组成的字符串 $s$，问删掉几个连续的字符（即删去一个子串）之后是否能得到 `CODEFORCES`。

## 样例 #1

### 输入

```
CODEWAITFORITFORCES
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
BOTTOMCODER
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
DECODEFORCES
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
DOGEFORCES
```

### 输出

```
NO
```

# 题解

## 作者：Clay_L (赞：4)

### 题意简述

给定一个字符串 $s$ ，问在 $s$ 中删去一个子串后能否得到 `"CODEFORCES"`。

### 算法分析

一个字串，要么在字符串中间，要么在字符串左边，要么在字符串右边。这样才能保证删掉一个子串后，保留的是 `"CODEFORCES"`。

所以我们可以拿出来我们的**分类讨论**大法！

分四种情况：

> 1. `"CODEFORCES"` 在 $s$ 的最左边，即 `"CODEFORCESxxxxxx…"`；
> 2. `"CODEFORCES"` 在 $s$ 的最右边，即 `"xxxx…xxCODEFORCES"`；
> 3. `"CODEFORCES"` 被劈成两半，前一半在 $s$ 的最左边，后一半在 $s$ 的最右边，即 `"C(ODEFORCE)xxxx…xx(ODEFORCE)S"`；
> 4. 不包含 `"CODEFORCES"`。

但是，分三种情况时写的代码非常复杂，那我们怎么优化一下“代码复杂度”呢？

**情况合并**！

仔细观察前三种情况，我们就会惊奇的发现，它们都可以看成第三种情况，只不过在前两种情况 `"CODEFORCES"` 是被劈成 `"CODEFORCES"` 本身和一个空的字符串。

所以我们只需要枚举段首和段尾就可以把答案求出来了。

但别忘了要特判 $|s|<10$ 的情况。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s,c="CODEFORCES"; 
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>s;
	int n=s.size();
	if(n<10){
		cout<<"NO\n";
		return 0;
	}
	int cnt=0;
	for(int i=0;i<10;i++){
		if(s[i]!=c[i]) break;
		cnt++;
	}
	for(int i=n-10+cnt;i<n;i++){
		if(s[i]!=c[cnt]){
			cout<<"NO\n";
			return 0;
		}
		cnt++;
	}
	cout<<"YES\n";
	return 0;
}
```

完结撒花！

---

## 作者：zhuweiqi (赞：2)

分类讨论并模拟即可。

设字符串 $s$ 的长度为 $n$。当 $n<10$ 时，必定无解；如果有解必定会是下列这三种情况之一：字符串 $s$ 的开头是 ```CODEFORCES```；字符串 $s$ 的末尾是 ```CODEFORCES```；字符串 $s$ 的开头包括 ```CODEFORCES``` 的前 $k$ 位，末尾包括 ```CODEFORCES``` 的后 $10-k$ 位，我们尽可能地找一个最大的 $k$，这样 $10-k$ 就会是最小的，满足条件的要求就会低一些，不会误判。如果字符串 $s$ 都不满足这三种情况之一，它就是无解的。

参考代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[105];
char ans[12]={' ','C','O','D','E','F','O','R','C','E','S'};
int main(){
	scanf("%s",a+1);
	int n=strlen(a+1);
	if(n<10){
		printf("%s","NO");
		return 0;
	}
	for(int i=1;i<=10;i++){
		if(a[i]!=ans[i]) break;
		if(i==10){
			printf("%s","YES");
			return 0;
		}
	}
	for(int i=1;i<=10;i++){
		if(a[n-10+i]!=ans[i]) break;
		if(i==10){
			printf("%s","YES");
			return 0;
		}
	}
	int i=1;
	while(a[i]==ans[i]) i++;
	for(;i<=10;i++){
		if(a[n-10+i]!=ans[i]) break;
		if(i==10){
			printf("%s","YES");
			return 0;
		}
	}
	printf("%s","NO");
	return 0;
}
```

---

## 作者：dhclientqwq (赞：2)

**题目大意**:给你一个字符串，问能否去掉一个子串使得剩下的是 `CODEFORCES`

因为只能去掉一个字符串，所以我们就可以从串头和串尾分别看和`CODEFORCES`相同的字母数量，若串头和串尾字母数量和不超过单词的字母数量，就是不能。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[1005],t[1005],y[1005];
int main()
{
  int i,len,tmp,j,k,x;
  scanf("%s",s);
  strcpy(t,"CODEFORCES");
  if (strcmp(s,t)==0){printf("YES\n"); return 0; }
  len=strlen(s);
  for (i=0;i<len;i++)
    for (j=i;j<len;j++)
    {
      x=-1;
      for (k=0;k<len;k++)
        if (k<i||k>j) y[++x]=s[k];
      y[x+1]='\0';
      if (strcmp(y,t)==0){printf("YES\n"); return 0; }
    }
  printf("NO\n");
  return 0;
}
```
```

---

## 作者：Deteled_User (赞：1)

## Part 1 题目描述
一个字符串 $s$，判断是否可以从 $s$ 中去掉一个子串使得 $s$ 变为 `CODEFORCES`。
## Part 2 思路
模拟。

由于只会留下 $10$ 个字符，所以在 $s$ 的前面取 $i(0\le i \le10)$ 个字符，在 $s$ 的后面取 $10 - i$ 个字符可以保证去掉的一定是 $s$ 的一个子串。

最后注意特判长度小于 $10$ 的情况。
## Part 3 代码
```
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s,c = "CODEFORCES";
    cin >> s;
    int l = s.length();
    if(l >= 10) for(int i = 0;i <= 10;i++)
    {
        int flag = 0;
        for(int j = 0;j < i;j++)
            if(s[j] != c[j])
                flag = 1;
        for(int j = l - 10 + i;j < l;j++)
            if(s[j] != c[j - l + 10])
                flag = 1;
        if(!flag)
        {
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";
    return 0;
}
```


---

## 作者：SMall_X_ (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF538A)


---
## 题目大意

给定一个只由大写英文字母组成的字符串 $s$，问删去一个子串之后是否能得到 `CODEFORCES`。

## 思路分析

$s$ 的长度不超过 $100$，数据范围很小，考虑暴力。

我们可以枚举删除的子串，看删除字串后的 $s$ 是不是 `CODEFORCES`，是则输出 `YES`，枚举后若都是，输出 `NO`。

代码：
```cpp
/*Written by smx*/
#include<bits/stdc++.h>
using namespace std;

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); 
	cout.tie(0); 
	string s;
	cin>>s;
	for(int i=0;i<s.size();i++){
		for(int j=0;j+i<s.size();j++){
			string str=s.substr(0,i)+s.substr(i+j+1);
			if(str=="CODEFORCES"){
				cout<<"YES";
				return 0;
			}
		}
	}
	cout<<"NO";
	return 0;
}
```

---

## 作者：lgydkkyd (赞：0)

这题数据不大，可以暴力水过。首先输入字符串就不用我多说了吧。随后就是蒟蒻最喜欢的暴力枚举，上两重循环分别用来枚举区间的左端点与右端点，接下来就可以删掉区间，最好提前用一个字符串存下来题目要让我们得到的字符串，方便直接与删除后的字符串比较是否相同，如果是则表示可以，如果枚举完毕之后仍然没有方案则表示该数据无解。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
string s1;
string c="CODEFORCES";//记录要获得的字符串，方便枚举时比较 
int main(){
    cin>>s1;//输入字符串 
    int s1len=s1.size();//提前记好字符串长度，如果在循环中用s1.size()替换s1len会浪费时间 
    for(int i=0;i<s1len;i++){//枚举左端点 
    	for(int j=i;j<s1len;j++){//枚举右端点
			string shenxia=s1.substr(0,i)+s1.substr(j,s1len);//此代码的核心部分，拼接两段未删除的字符串 
			if(shenxia==c){//判断是否能够拼出CODEFORCES 
				printf("YES");//有解输出YES 
				return 0;//有解就没必要再枚举了，结束循环 
			}
		}
	}
	printf("NO");//说明没有能拼出CDEFORCES的方案，则输出NO 
	return 0;//华丽结束``` ，代码较长，请耐心阅读，请勿抄袭
}
```

---

## 作者：Fa_Nanf1204 (赞：0)

## string 大法好！！！
### 分析
我们可以用 string 存下输入的字符。然后用两重循环枚举删除的字符的区间左端点和右端点，然后将此区间的字符删去，判断剩下的字符是否符合要求。
- - -
### 代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,s1,s2="CODEFORCES";
int n;
int main(){
	cin>>s;//输入 
	n=s.size()-1;
	for (int l=0;l<=n;l++){//枚举左端点 
		for (int r=l;r<=n;r++){//枚举右端点 
			s1=s.substr(0,l)+s.substr(r+1);//拼接剩下的字符 
			if (s1==s2){//判断 
				cout<<"YES"<<endl;
				return 0;
			}
		}
	}
	cout<<"NO"<<endl;
	return 0;
} 
```

---

## 作者：GoodLuckCat (赞：0)

直接判断。

先看几个数据：`CODEIAKIOIFORCES`、`CODEFORCEODEFORCES` 和 `CODEFORCEIOIAKME`。

`CODEIAKIOIFORCES` 中，我们可以找到前面的 `CODE`，它是 `CODEFORCES` 的前面一部分，并且长度为 $4$。我们还可以找到后面的 `FORCES`，它是 `CODEFORCES` 的后面一部分，并且长度为 $6$。所以这个字符串一共有 $10$ 个有效字符满足条件。

根据这个规律，可以算出，`CODEFORCEODEFORCES` 的满足条件的有效字符为 $18$，而 `CODEFORCEIOIAKME` 的满足条件的有效字符为 $9$。可以看出，将前面的和后面的拼起来、，如果能得到 $10$ 个字符，那这个字符串就满足条件，否则就不满足。

但是如果这个字符串本来就短，删去以后更短，所以肯定不行。

`return(cout<<"NO",0);` 这种写法其实相当于 `{cout<<"NO";return 0;}`，就是逗号表达式。代码如下，~~很暴力~~：

```cpp
#include<iostream>
using namespace std;
int main()
{
    string a;
    int s=0,t=0,n;
    cin>>a;
    n=a.size();
    if(n<10)return(cout<<"NO",0);
    if(a[0]=='C')
    {
		s++;
		if(a[1]=='O')
		{
			s++;
			if(a[2]=='D')
			{
				s++;
				if(a[3]=='E')
				{
					s++;
					if(a[4]=='F')
					{
						s++;
						if(a[5]=='O')
						{
							s++;
							if(a[6]=='R')
							{
								s++;
								if(a[7]=='C')
								{
									s++;
									if(a[8]=='E')
									{
										s++;
										if(a[9]=='S')s++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if(a[n-1]=='S')
	{
		t++;
		if(a[n-2]=='E')
		{
			t++;
			if(a[n-3]=='C')
			{
				t++;
				if(a[n-4]=='R')
				{
					t++;
					if(a[n-5]=='O')
					{
						t++;
						if(a[n-6]=='F')
						{
							t++;
							if(a[n-7]=='E')
							{
								t++;
								if(a[n-8]=='D')
								{
									t++;
									if(a[n-9]=='O')
									{
										t++;
										if(a[n-10]=='C')t++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout<<(s+t>=10?"YES":"NO");
}
```

---

## 作者：_txb_ (赞：0)

## 思路：
因为只能删一段，所以情况只有三种，

- 字符串在最开头。
- 字符串在最后面。
- 字符串一部分在前，一部分在后。

所以可以暴力枚举每一种可能，就可以求出答案。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,c="CODEFORCES"; 
signed main()
{
	cin>>s;
	int cnt=1,j=0,i=0;
	for(int i=0;i<10;i++)
	{
		if(s[i]!=c[i]) break;
		cnt++;
	}
	if(cnt==10)
	{
		cout<<"YES";
		return 0;
	}//第一种 字符串在最开头
	cnt=0;
	for(int i=s.size()-10;i<s.size();i++)
	{
		if(s[i]!=c[j]) break;
		j++;
		cnt++;
	}
	if(cnt==10)
	{
		cout<<"YES";
		return 0;
	}//第二种 字符串在最后面
	while(s[i]==c[i]) i++;//求出前面可以到哪位 
	for(;i<10;i++)
	{
		if(s[s.size()-10+i]!=c[i]) break;
		if(i==9)
		{
			cout<<"YES";
			return 0;
		}
	}//第三种 字符串一部分在前，一部分在后
	cout<<"NO";
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

首先观察样例，$s$ 的长度不超过 $100$，可以使用暴力。

因为是要删除一个连续的字串，使得 $s$ 中只剩下了 $\texttt{CODEFORCES}$（$10$ 个字符），所以我们要删去 $|s|-10$ 个字符。

考虑删除从 $i$ 开始到 $i+|s|-9$ 的字符，即为保留 $0$ 到 $i-1$ 和 $i+|s|-10$ 到 $|s|-1$ 的字符。

注：上文中下标从 $0$ 开始。

AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s,ss="CODEFORCES";
int main(){
    cin>>s;
    int l=s.size();
    if(l<10)return cout<<"NO",0;//特判
    for(int i=0;i<l-10;i++){
        string k="";
        for(int j=0;j<i-1;j++)k+=s[j];//模拟保留的过程
        for(int j=i+l-11;j<l;j++)k+=s[j];//模拟保留的过程
        if(k==ss)return cout<<"YES",0;//符合就输出、
    }return cout<<"NO",0;
}
```

---

## 作者：_Execution_ (赞：0)

## 思路
首先，由于最后要剩下 `CODEFORCES` 这个字符串，所以如果原来的串已经比它短了，也就是长度小于 $10$ 时，结果一定是 `NO`。

接着考虑，可以发现有三种情况可以输出 `YES`：

1. `CODEFORCES` 在串头。

1. `CODEFORCES` 在串尾。

1. `CODEFORCES` 的一部分在串头，剩下的一部分在串尾。

分别模拟即可，如果都不满足，则输出 `NO`。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int i=0;
string ans="CODEFORCES";//需要寻找的串
int main(){
	cin>>s;
	int slen=s.size();
	if(slen<10){
		puts("NO");
		return 0;
	}//长度太短
	for(i=0;i<10;i++){
		if(s[i]!=ans[i]) break;
		if(i==9){
			puts("YES");
			return 0;
		}
	}//判断条件1
	for(i=0;i<10;i++){
		if(s[slen-10+i]!=ans[i]) break;
		if(i==9){
			puts("YES");
			return 0;
		}
	}//判断条件2
	while(s[i]==ans[i]){//寻找前半部分
        i++;//前半部分的长度
    }
	for(;i<10;i++){//对应后半部分
		if(s[slen-10+i]!=ans[i]) break;
		if(i==9){
			puts("YES");
			return 0;
		}
	}//判断条件3
	puts("NO");//三种情况都不满足，无解
}
```
	


---

## 作者：xudiyao (赞：0)

# 洛谷CF538A题解
## 题目大意
给定一个字符串，问字符串 ```CODEFORCES``` 是否可以在此字符串中找到。

## 思路引导

这道题我们可以分情况讨论，因为只能删除一段子串，所以只需分三种情况讨论，为方便，下面输入的字符串为 ```a```，而所寻找的字符串为 ```b```。

1. 字符串 ```b``` 全在字符串 ```a``` 的串头。

2. 字符串 ```b``` 全在字符串 ```a``` 的串尾。

3. 字符串 ```b``` 在字符串 ```a``` 的串头有一部分，串尾有一部分。

## 代码实现

~~~cpp
#include<bits/stdc++.h>
using namespace std;
string a,s="CODEFORCES";
int main()
{
  int i=0,k=0;
	cin>>a;
	for(int i=0;i<10;i++)//整个b都在a的串首。
  {
		if(a[i]!=s[i]) break; 
		if(i==9)
    {
			cout<<"YES";
			return 0;
		}
	}
	for(int i=9;i>=0;i--)//整个b都在a的串首。
  {
		if(a[i]!=s[i]) break;
		if(i==0)
    {
			cout<<"YES";
			return 0;
		}
	}
	while(a[k]==s[k]) k++;//b在a的串首有一部分。 
	for(int i=k;i<10;i++)//b剩余的是否在a的串首的一部分。 
  {
		if(a[a.size()+i-10]!=s[i]) break;
		if(i==9)
    {
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO";
}//AC撒花！！！
//禁止复制题解！！！
~~~

---

