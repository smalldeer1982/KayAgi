# Hometask

## 题目描述

Sergey attends lessons of the $ N $ -ish language. Each lesson he receives a hometask. This time the task is to translate some sentence to the $ N $ -ish language. Sentences of the $ N $ -ish language can be represented as strings consisting of lowercase Latin letters without spaces or punctuation marks.

Sergey totally forgot about the task until half an hour before the next lesson and hastily scribbled something down. But then he recollected that in the last lesson he learned the grammar of $ N $ -ish. The spelling rules state that $ N $ -ish contains some "forbidden" pairs of letters: such letters can never occur in a sentence next to each other. Also, the order of the letters doesn't matter (for example, if the pair of letters "ab" is forbidden, then any occurrences of substrings "ab" and "ba" are also forbidden). Also, each pair has different letters and each letter occurs in no more than one forbidden pair.

Now Sergey wants to correct his sentence so that it doesn't contain any "forbidden" pairs of letters that stand next to each other. However, he is running out of time, so he decided to simply cross out some letters from the sentence. What smallest number of letters will he have to cross out? When a letter is crossed out, it is "removed" so that the letters to its left and right (if they existed), become neighboring. For example, if we cross out the first letter from the string "aba", we get the string "ba", and if we cross out the second letter, we get "aa".

## 说明/提示

In the first sample you should remove two letters b.

In the second sample you should remove the second or the third letter. The second restriction doesn't influence the solution.

## 样例 #1

### 输入

```
ababa
1
ab
```

### 输出

```
2
```

## 样例 #2

### 输入

```
codeforces
2
do
cs
```

### 输出

```
1
```

# 题解

## 作者：Andy_Li (赞：4)

# CF154A Hometask 题解

## 题意

见题目，题目写的很清楚。

## 思路

统计 $k$ 个字符串在 $s$ 种出现的个数，将最小值相加即为答案。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+7;
map<char,int> mp;
int main()
{
	cin.tie(0);
	std::ios::sync_with_stdio(false);
	//	srand((unsigned)time(NULL));
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	string s;
	cin>>s;
	int t,ans=0;
	cin>>t;
	while(t--)
	{
		char c,cc;
		int cnt1=0,cnt2=0;
		cin>>c>>cc;
		for(int i=0;i<s.size();i++)
			if(s[i]==c)
				cnt1++;
			else if(s[i]==cc)
				cnt2++;
			else
			{
				ans+=min(cnt1,cnt2);
				cnt1=0;
				cnt2=0;
			}
		ans+=min(cnt1,cnt2);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：fuxuantong123 (赞：4)

# CF154A Hometask 题解
## 题意
给你一个字符串，再给你 $k$ 个只有两个字符的字符串，且这些字符不重复，问你需要在原串中删除多少个字符才能保证原串中不含这 $k$ 个串及其反串。
## 思路
统计原串中不合法的连续字符个数，累加最小值即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	int n;
	scanf("%d",&n);
	int ans=0;
	for(int i=1;i<=n;i++){
		string fw;
		cin>>fw;
		int sum1=0,sum2=0;
		for(int i=0;i<s.size();i++){
			if(fw[0]==s[i]){
				sum1++;
			}
			if(fw[1]==s[i]){
				sum2++;
			}
			if(fw[0]!=s[i] && fw[1]!=s[i]){
				if(sum1 && sum2){
					ans+=min(sum1,sum2);
				}
				sum1=0;
				sum2=0;
			}
		}
		if(sum1 && sum2){
			ans+=min(sum1,sum2);
		}
	}
	printf("%d",ans);
return 0;
}
```


---

## 作者：WLR__jr (赞：2)

# 思路：

#### 既然k个两字符串中没有重复的串，那么你删除一些必要的字符后肯定不会造成新的不符合要求的串，所以只要统计下串中连续的不合法的字符的个数，取最小值就可以了。

# 下面上代码

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[110000];
int main()
{
	scanf("%s",s);
	int len=strlen(s);
	int k,ans=0;scanf("%d",&k);
	while(k--)
	{
		char ch[5];scanf("%s",ch);
		int n1=0,n2=0;
		for(int i=0;i<len;i++)
		{
			if(s[i]==ch[0])n1++;
			else if(s[i]==ch[1])n2++;
			else
			{
				ans+=min(n1,n2);
				n1=n2=0;
			}
		}
		ans+=min(n1,n2);
	}
	printf("%d\n",ans);
	return 0;//完结撒花！！！
}
```

---

## 作者：yyyh_h (赞：2)

# 题意
读入一串字符串，再读入 $k$ 与 $k$ 个只有两个字符的字符串，且这些字符不重复。

输出要在原串中删除多少个字符才能保证原串中不含这 $k$ 个串及其反向串。

# 思路
既然题目中说到读入的 $k$ 个字符串不会重复，那么我们只需要统计原串里连续含有读入的 $k$ 个字符串中的字符的数目，再取最小值即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string x;
int k;
long long ans=0;
int main()
{
	cin>>x;
	scanf("%d",&k);//读入 
	while(k--)//循环k次 
	{
		int a=0,b=0;
		char x1,y1;
		string w;
		cin>>w;//读入 
		x1=w[0],y1=w[1];//取字符串中的字符，由于只有两个字符，所以直接可以处理 
		for(int i=0;i<x.size();i++)
		{
			if(x[i]==x1) a++;
			else if(x[i]==y1) b++;//统计原串中含有当前字符串中字符的数目
			else ans=ans+min(a,b),a=b=0;//取最小值 
			//下面是三目运算符，与上面代码等效 
			//(x[i]==x1)?(a++):((x[i]==y1)?(b++):(ans=ans+min(a,b),a=b=0));
		}
		ans=ans+min(a,b);
	}
	printf("%lld",ans);//输出答案
	return 0;//完结撒花
}
```


---

## 作者：Spir1t (赞：0)

### [ CF154A](https://www.luogu.com.cn/problem/CF154A) Hometask 题解


------------
这道题还算简单，题目大意给的也比较清晰，思路就是把这 $k$ 个字符串逐一在原串中枚举是否出现了它自己或它的倒序即可。

#### [Ac Code](https://www.luogu.com.cn/paste/90e7p1uk)


---

## 作者：smydahaoren (赞：0)

[CF154A Hometask 原题链接](https://www.luogu.com.cn/problem/CF154A)


### **题目大意**：

给定一个字符串 $s$，再给出一些两个字符的子串，求出删除至少多少个字符才能让 $s$ 中没有这些子串的正序或者逆序形式。

### **代码实现**：

题目要求删去字符来破坏所有的非法子串，那么就需要统计出所有的子串数量，同时因为题目有正/逆序的的子串都不能有的要求，所以尤其注意非法子串连在一起的情况，需要对该子串计算出删去字符数量的最小值。

遍历 $s$ 字符串，遍历计算出每个子串出现的个数。

其中，注意：

字符串：```ababa```，子串：```ab```。

这时候，我们只用删去其中的两个 $b$ 就可以在剩余字符串中没有目标子串了。

**综上，最小值为每连续子串的最少子串中的字符数量的和。**

### **AC 代码**：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100009;
string s,x;
int ans,n;
int main(){
	cin>>s>>n;
	for(int i=0;i<n;i++){
		cin>>x;
		int a=0,b=0;//统计连续子串的字符出现数量
		for(int j=0;j<s.size();j++)
			(s[j]==x[0])?(a++):((s[j]==x[1])?(b++):(ans+=max(a,b)-abs(a-b),a=b=0));//条件运算符，这里判断了连续子串里面的最小字符出现数量
		ans+=max(a,b)-abs(a-b);//防止最后的连续子串没有被统计到
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：ZM____ML (赞：0)

## 题意
读入一串字符串，再读入 $k$ 与 $k$ 个只有两个字符的字符串，**且这些字符不重复**。

问你需要在原串中删除多少个字符才能保证原串中不含这 $k$ 个串及其反向串。

## 分析
既然这 $k$ 个字符串中没有重复，那么你删除一些字符后肯定不会造成矛盾，只要统计下字符串中连续的不合法的字符的个数，取最小值就可以了。

## 代码
```c
#include<cstdio>
#include<cstring>
#define min(a,b) (a<b?a:b)
using namespace std;
const int N=1e5+5;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-48;
		c=getchar();
	}
	return x*f;
}
int k,ans;
char s[N],ch[2];
int main(){
	scanf("%s",s);
	int len=strlen(s);
	k=read();
	while(k--){
		scanf("%s",ch);
		int n1=0,n2=0;
		for(int i=0;i<len;i++){
			if(s[i]==ch[0])n1++;
			else if(s[i]==ch[1])n2++;
			else{
				ans+=min(n1,n2);
				n1=n2=0;
			}
		}
		ans+=min(n1,n2);
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：BreakPlus (赞：0)

## [$\text{CF154A Hometask}$](/problem/CF154A)

### $\text{Discribe}$

给定一个字符串，还有 $k$ 个只有两个字符的串，问需要在原串中删除多少个字符才能保证原串中不含这 $k$ 个串及其反向串。

### $\text{Solution}$

没救了，就我一个用 DP 做……

先考虑设 $f_{i}$ 表示使得前 $i$ 个字符满足条件，最多能保留多少个字符。我们可以分两种情况讨论：

1. 第 $i$ 个字符删去，此时 $f_{i}=f_{i-1}$ 。
2. 保留第 $i$ 个字符。此时需要满足上一个字符与第 $i$ 个字符不能出现语法错误，但是我们不知道当 $f_{i-1}$ 最优的时候的最后一个字符是什么，这就没法推导了。

为了记录保留的最后一个字符，我们可以给 $f_{i}$ 加一维。设 $f_{i,j}$ 表示前 $i$ 个字符，最后一个保留的字符是 $j$，在满足条件的情况下最多能保留的字符数。再分两种情况讨论：

1. 第 $i$ 个字符删去，此时 $f_{i,j}=f_{i-1,j}$。
2. 保留第 $i$ 个字符（此情况需要满足 $s_{i}=j$，$s$ 是原串），对于任何可以与字符 $j$ 拼接在一起的字母 $k$，$f_{i,j}=\max\{f_{i-1,k}+1\}$。

另：我们要将 $f$ 初始化为 $-\infty$，因为某些情况是不可能的。还有，$f_{1,s_{1}}=1$。

此时我们的程序会被 Hack：

```
abcdefg
6
ab
ac
ad
ae
af
ag
```

按照上面的方法会输出 $6$（最多能保留 $1$ 个字符），答案是 $1$。这是为什么？因为我们还没有考虑前 $i$ 个字符全部删去的情况。我们设 $f_{i,m}$ 表示前 $i$ 个字符全部删去的情况，数值为 $0$，$m$ 任选；或者当 $j=s_i$ 时，$f_{i,j}=\max(f_{i,j},1)$ ，因为肯定能保留第 $i$ 个字符。

### $\text{Code}$

因为上面已经很详细，代码就不写注释了。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int n,k,f[100010][27],ans; char str[100010],tmp[5];
bool use[10010];
inline int maxx(int a,int b){
	return a>b?a:b;
}
int main(){
	scanf("%s",(str+1));
	n=strlen(str+1);
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		scanf("%s",tmp);
		use[(tmp[0]-'a')*26+(tmp[1]-'a')]=true;
		use[(tmp[1]-'a')*26+(tmp[0]-'a')]=true;
	}
	memset(f,128,sizeof f);
	f[1][str[1]-'a']=1; f[1][26]=0;
	for(int i=2;i<=n;i++){
		for(int j=0;j<=25;j++){
			if(str[i]-'a'==j){
				for(int k1=0;k1<=25;k1++){
					if(!use[j*26+k1]) f[i][j]=maxx(f[i][j],f[i-1][k1]+1);
				}
				f[i][j]=maxx(f[i][j],f[i-1][26]+1);
			}
			f[i][j]=maxx(f[i][j],f[i-1][j]);
		}
		f[i][26]=0;
	}
	for(int j=0;j<=25;j++) ans=maxx(ans,f[n][j]);
	printf("%d\n",n-ans);
//	for(int i=1;i<=n;i++){
//		for(int j=0;j<=6;j++) printf("%d ",f[i][j]);
//		puts("");
//	}
	return 0;
}								
```

---

## 作者：Rosmarinus (赞：0)

## 思路分析

由于给出的 $k$ 个字符串长度都为 $2$ 并且这些字符串内不会有字符重复出现，那么我们就没必要考虑其他的东西，直接暴力。

对于每个字符串，在原串中扫描一遍，如果有它的正/倒序有出现就让 $ans$ 加 $1$。

需要特别注意类似于：
```
aba
1
ab
```
这样的正序倒序重叠出现的情况。

## 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	string s, x;
	int k, a, b, ans = 0;
	cin >> s >> k;

	for(int i = 1; i <= k; i ++)
	{
		cin >> x;
		a = b = 0;
		for(int i = 0; i < s.size(); i ++)
		{
			if(s[i] == x[0]) a ++;
			else if(s[i] == x[1]) b ++;
			else
			{
				ans += min(a, b);
				a = b = 0;
			}
		}
		ans += min(a, b);
	}
	cout << ans << endl;
	return 0;
}
```

---

