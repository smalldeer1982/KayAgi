# Restoring Increasing Sequence

## 题目描述

Peter wrote on the board a strictly increasing sequence of positive integers $ a_{1},a_{2},...,a_{n} $ . Then Vasil replaced some digits in the numbers of this sequence by question marks. Thus, each question mark corresponds to exactly one lost digit.

Restore the the original sequence knowing digits remaining on the board.

## 样例 #1

### 输入

```
3
?
18
1?
```

### 输出

```
YES
1
18
19
```

## 样例 #2

### 输入

```
2
??
?
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5
12224
12??5
12226
?0000
?00000
```

### 输出

```
YES
12224
12225
12226
20000
100000
```

# 题解

## 作者：liruizhou_lihui (赞：2)

## 思路分析

这里说随机符合要求，但实际上你要是真的随机就很好卡。

要把题面改成**最小符合要求的**。



---



先分析第一个数字，他不会受前面的数字影响。因为前面没有数字，所以这个数是没有限制的。所以尽可能的让 $?$ 填 $0$，但如果最高位是 $?$ 就需要填 $1$。

比如：$??1451??32$ 就填成 $1014510032$，$12??412??$ 就填成 $120041200$。

---

考虑第二个数字和后面的数字，这些数字会受到前面数字的影响。

方便表达，这里先设 $x,las,sx,sl$ 分别表示：当前处理的数字，上一个数字，当前处理的数字长度，上一个数字长度。

- 如果 $sx>sl$。

  则 $x$ 中的所有问好填什么都比 $las$ 大，因为 $x$ 的位数比 $las$ 多。

-  如果 $sx<sl$。

这直接就不合法了。

- 如果 $sx=sl$


 先把 $x$ 中的问号改成 $las$ 对应的位置。

比如 $x=1234?????,las=123456789$。替换后得到 $x=123456789$，此时要给 $x$ 的一个数位加一就比 $las$ 打了，但是不能给 $9$ 加一，因为会产生进位。

那么就可以得出 $x=1234567{\color{red}{9}}9$，标红位置是改变的数位。原来是 $8$，现在改成了 $9$。

不难看出改变数位的地方越靠后数越小，所以可以从最低为开始寻找不为 $9$ 且是问号的地方。

但是也会有无解情况，比如 $x=????,las=9999$。那这里先把 $x$ 问号处替换，变成 $x=9999$。然后加一的时候会发现全部都是 $9$ 无法变换。所以不合法。

---


再举一个例子：比如 $x=14?65??32$，$las=14664432$。那么 $x$ 就要替换为 $1265114514331$。

  观察上面的例子。
  ![](https://cdn.luogu.com.cn/upload/image_hosting/zvzulaut.png)

  这个时候我们注意到第五位 $x$ 和 $las$ 分别是 $5$ 和 $4$。那么可以确定 $x$ 第五位之后比 $las$ 的第五位之后始终要大，所以 $x$ 第五位之后的问号可以直接填 $0$。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/l60n2im2.png)

那这个时候就合法且最小。

---


还有一种情况就是如果两个数的同一位当前的比前边的小那么后面的问号可以直接填 $0$，前面找一个不为 $9$ 的问号加一即可

## 代码+注释

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s[1005];
vector<string> ans; 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		string x=s[i];//x为当前的 
		if(i==1)
		{
			for(int j=0;j<x.size();j++)
				if(x[j]=='?')
					x[j]=(j==0?'1':'0');//按照思路分析来构造第一个数字 
			ans.push_back(x);//压入答案数组 
			continue;
		}
		string las=ans.back();//上一个数字las 
		if(x.size()<las.size())//如果当前的比前面的小就不合法 
		{
			cout<<"NO";
			return 0;
		}
		if(x.size()>las.size())//数位比las多直接按照类似i=1处理 
		{
			for(int j=0;j<x.size();j++)
				if(x[j]=='?')
					x[j]=(j==0?'1':'0');
			ans.push_back(x);//压入答案数组 
			continue;
		}
		//长度相等 
		bool f=0;//标记是否确定答案 
		for(int j=0;j<x.size();j++)
		{
			if(x[j]=='?')//如果是问号 
				x[j]=las[j];
			else if(x[j]>las[j])//如果现在这一位比上一个数字的这一位大 
			{//后面填多少都不需要考虑总会满足x>las，最小就填 0 
				for(int k=j;k<x.size();k++)
					if(x[k]=='?')
						x[k]='0';
				ans.push_back(x);////压入答案数组 
				f=1;//标记 
				break;
			}
			else if(x[j]<las[j])//如果这一位比las的这一位小 
			{//后面填多少都不需要考虑总会满足x<las，最小就填 0 
				for(int k=j;k<x.size();k++)
					if(x[k]=='?')
						x[k]='0';
				bool flag=1;//一个小标记 
				for(int k=j;k>=0;k--)
				{
					if(s[i][k]=='?' && x[k]!='9')//如果找到第一个非9问号 
					{
						flag=0;
						x[k]++;//加一，这时x>las 
						ans.push_back(x);
						break;
					}
					else if(x[k]=='9')//否则就改成0不影响 
						x[k]='0';
				}
				if(flag)//如果始终没有遇到非9问号 
				{
					cout<<"NO\n";
					return 0;
				}
				f=1;
			}
			if(f)
				break;
		}
		if(f)
			continue;
		f=1;
		//确定数位全部相同时处理 
		for(int j=x.size()-1;j>=0;j--)//这里同理 
			if(s[i][j]=='?' && x[j]!='9')
			{
				f=0;
				x[j]++;
				ans.push_back(x);
				break;
			}
			else if(s[i][j]=='?')
			{
				x[j]='0';
			}
		if(f)
		{
			cout<<"NO";
			return 0;
		}
	}
	cout<<"YES\n";
	for(string i:ans)
		cout<<i<<'\n';
	return 0; 
}
```

---

## 作者：Phobia (赞：2)

给一个相对比较好想好写的做法。

从贪心的角度来说，每个数字越小越好，因为只有这样才更可能接上后面的数字。

因为填问号时数字大小满足单调性，不妨二分问号内填的数字的大小，若最大都不能接上前面的数字，直接无解。

时间复杂度 $O\left(8n\log W\right)$。

~~~cpp
#include <bits/stdc++.h>

using namespace std;

const int maxn = 100005;

int n;

int w[10];

char s[maxn][10];

int main()
{
    w[0] = 1;
    for (int i = 1; i <= 8; ++i) // 预处理 10 的整数次幂
        w[i] = w[i - 1] * 10;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%s", s[i] + 1);
    for (int i = 1, lst = 0; i <= n; ++i)
    {
        int l = strlen(s[i] + 1), now = 0, cnt = 0;
        for (int j = 1; j <= l; ++j)
        {
            if (s[i][j] != '?')
                now += (s[i][j] & 15) * w[l - j];
            else
                ++cnt;
        }
        if (!cnt && lst > now) // 特判没有 '?' 的情况
        {
            puts("NO");
            return 0;
        }
        else
        {
            int le = (s[i][1] == '?' ? w[cnt - 1] : 0), ri = w[cnt] - 1, ans = -1; // 注意，首数字不能为 0
            while (le <= ri)
            {
                int mid = le + ri >> 1, tmp = mid, sum = now;
                for (int j = l; j >= 1; --j) // 构造数字
                {
                    if (s[i][j] == '?')
                    {
                        sum += (tmp % 10) * w[l - j];
                        tmp /= 10;
                    }
                }
                if (sum > lst)
                    ans = mid, ri = mid - 1;
                else
                    le = mid + 1;
            }
            if (ans == -1) // 无解
            {
                puts("NO");
                return 0;
            }
            for (int j = l; j >= 1; --j)
            {
                if (s[i][j] == '?')
                {
                    s[i][j] = ans % 10 | 48;
                    now += (ans % 10) * w[l - j];
                    ans /= 10;
                }
            }
            lst = now;
        }
    }
    puts("YES");
    for (int i = 1; i <= n; ++i)
        puts(s[i] + 1);
    return 0;
}

~~~

---

## 作者：FutaRimeWoawaSete (赞：2)

做过最拉的 E （             

考虑我们从最后一个数开始，尽量选大就好了。            

具体而言，我们想选出一种合法情况，我们令最后一个数的上界为一个无穷大的数然后我们每次尽量把这个数搞大一点，可以保证这样每次选出来的上界会尽量大。那么如果一个数不能满足这个上界那么自然就不可能构造出合法情况。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e5 + 5;
int n,a[Len],b[Len][15],len[Len],p[15];
char s[Len][15];
int Print[Len];
int main()
{
	scanf("%d",&n);
	p[0] = 1;
	for(int i = 1 ; i <= 8 ; i ++) p[i] = p[i - 1] * 10;
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%s",s[i] + 1);
		len[i] = strlen(s[i] + 1);
		for(int j = len[i] ; j >= 1 ; j --) 
		{
			if(s[i][j] != '?') a[i] += p[len[i] - j] * (s[i][j] - '0') , b[i][j] = 1;
			else b[i][j] = 0;
		}
	}
	int maxn = 1e9;
	for(int i = n ; i >= 1 ; i --) 
	{
		for(int j = 1 ; j <= len[i] ; j ++) 
		{
			if(b[i][j]) continue;bool flag = false;
			for(int k = 9 ; k >= 0 ; k --)
			{
				if(!k && j == 1) continue;
				if(a[i] + k * p[len[i] - j] < maxn) 
				{
					a[i] += k * p[len[i] - j];
					flag = true;
					break;
				}
			}
			if(!flag)
			{
				puts("NO");
				return 0;
			}
		}
		if(a[i] >= maxn)
		{
			puts("NO");
			return 0;
		}
		Print[i] = maxn = a[i];
	}
	puts("YES");
	for(int i = 1 ; i <= n ; i ++) printf("%d\n",Print[i]);
	return 0;
}
```

---

## 作者：SSHhh (赞：2)

这道题其实就是一道代码能力神题，其实说是贪心也没错，不过暴力就能过。说到暴力，大家想到的肯定有很多思路，什么从后往前扫一遍然后逐个判断啊，什么~~**_蛇皮_**~~搜索每一个问号啊。。。其实这些方法有很多优化优化说不定就能过，不过我采用的是一种写政治作业时想出来的玄学算法，打了 30 分钟就过了，这个算法具体思路如下：

1. 首先，我们先看当前要构造的第 i 个数字的长度和上一个数字的长度。

	如果 s[i].size() 大于 s[i-1].size()，那么把这个数字所有问号都填 0 即可（注意一下，如果第一位上是问号，那么第一位上必须填 1 ）。这个想必大家都能理解，我就不再多说了。

	如果 s[i].size() 小于 s[i-1].size()，那么直接 return 0 就行了，主函数中直接输出 NO 。现在保证 s[i] 和 s[i-1] 的长度都相等了，就可以瞎~~**_JB_**~~搞了。

2. 我们把两个字符串从前往后扫一遍，如果 s[i][j]（即当前数字的第 j 位）不是问号且比 s[i-1][j] 大，那么后面的问号无论怎么填，最后这个数字肯定比上一个数字大。所以直接把后面所有问号填成 0，前面的问号都填成上一个数字对应位上的数即可。

	如果 s[i][j] 比 s[i-1][j] 小，那么在当前位之前一定有一个问号比上一个数字对应位上的数大。从 j-1 开始往前枚举，找到最靠后的那个满足条件的问号即可。（这里也要注意一个细节，如果上一个数在某一位上是 9，那么因为进位的原因，这一位上的问号无论填几都不可能比上一个数的这一位更大）

	如果找不到这样的问号，那么说明一定构不成符合条件的递增数列，直接 return 0 即可。

3. 如果处理完前两步仍然没有找到答案，说明 s[i] 中所有的数字（非问号）都遇上一位相同，所以直接从后往前枚举问号，如果上一个数字这一位上不是 9，那么把这一位上的问号填成上一位上对应的数+1，然后把后面所有问号填成 0，前面的问号都填成上一个数字对应位上的数，最后直接 return 1（就是找到了这一位上的答案）就行了。

4. 如果还没找到，就说明找不到合法答案，直接 return 0。


### 最后注意两个细节：

1. i=1 时，前面是没有数的，所以直接构造最小即可。

2. 如果当前数字中没有问号，还需再判断 a[i] 是否大于 a[i-1]。（a[i] 代表第 i 个数字的值）

好了就这么多了。下面附上代码：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n,a[100005];string s[100005];
void clear(int i,int j)
{
	for(int k=j-1;k>=0;k--)
		if(s[i][k]=='?')
			s[i][k]=s[i-1][k];
	for(int k=j+1;k<s[i].size();k++)
		if(s[i][k]=='?')
			s[i][k]='0';
	a[i]=0;
	for(int k=0;k<s[i].size();k++)
		a[i]*=10,a[i]+=(s[i][k]-'0');
}
bool getsum(int i)
{
	if(a[i])	return a[i]>a[i-1];
	if(i==1)	//i=1 时，因为前面没有数，所以直接构造最小即可。
	{
		int sum=0;
		for(int j=0;j<s[i].size();j++)
		{
			if(s[i][j]=='?' && j==0)	s[i][j]='1';
			else if(s[i][j]=='?')	s[i][j]='0';
			sum*=10,sum+=(s[i][j]-'0');
		}
		a[i]=sum;
		return 1;
	}
	//第一步
	if(s[i].size()<s[i-1].size())	return 0;
	else if(s[i].size()>s[i-1].size())
	{
		s[i][0]=(s[i][0]=='?'?'1':s[i][0]),clear(i,0);
		return 1;
	}
	//第二步
	for(int j=0;j<s[i].size();j++)
		if('0'<=s[i][j] && s[i][j]<='9')
		{
			if(s[i][j]-'0'>s[i-1][j]-'0')
				{clear(i,j); return 1;}
			else if(s[i][j]-'0'<s[i-1][j]-'0')
			{
				for(int k=j-1;k>=0;k--)
					if(s[i][k]=='?' && s[i-1][k]!='9')
						{s[i][k]=(char)((int)s[i-1][k]+1),clear(i,k); return 1;}
				return 0;
			}
		}
	//第三步
	for(int j=s[i].size()-1;j>=0;j--)
		if(s[i][j]=='?' && s[i-1][j]-'0'<=8)
			{s[i][j]=(char)((int)s[i-1][j]+1),clear(i,j); return 1;}
	return 0;
}
int main()
{
	cin>>n;
	s[0]="0";
	for(int i=1;i<=n;i++)
	{
		int sum=0;
		cin>>s[i];
		for(int j=0;j<s[i].size();j++)
		{
			if(s[i][j]=='?')	{sum=0; break;}
			sum*=10,sum+=(s[i][j]-'0');
		}
		a[i]=sum;
	}
	for(int i=1;i<=n;i++)
		if(!getsum(i))
			{cout<<"NO"; return 0;}
	cout<<"YES\n";
	for(int i=1;i<=n;i++)
		cout<<s[i]<<endl;
	return 0;
}
```

---

## 作者：songzhixin (赞：1)

[原题](https://www.luogu.com.cn/problem/CF490E)

### 思路

根据贪心，因为我们要让可以的尽可能的多，所以我们要让这个数字尽可能的下，可知一下三种情况：

- 若这一个数的长度小于上一个数的长度，直接输出 `NO`，结束程序。

- 若这一个数的长度大于上一个数的长度，就可以将所有除首位外的为 `?` 数字变为 0，首位若为 `?`，变为 1。

- 若这一个数的长等于上一个数的长度，则又分三种情况：

	1.这一个数每一个非问号的的每一个数字等于上一个数对应位的数字，则从后往前遍历，设一个 `bool` 变量表示有没有加。若上一个数字为 9，则这一个问号改为 0，`bool` 变量不改变。其余情况 这一个问号改为上一个数字加一，`bool` 变量改变，以后问号改为上一个数的对应数字。

    2.这一个数每一个非问号的的每一个数字大于上一个数对应位的数字，则这一位前面的所有问号改为上一个数的对应数字，这一为以后问号改为 0。

    3.这一个数每一个非问号的的每一个数字小于上一个数对应位的数字，则这一位前面问号的同步骤 1 一样改变，这一位后边的问号全部变为 0。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N=100005;
long long a[N];
string c;
long long b[N];
long long d[20];
int main() {
	long long n;
	scanf("%lld",&n);
	for(long long i=1; i<=n; i++) {
		cin>>c;
		b[i]=c.size();
		if(b[i]<b[i-1]) {
			printf("NO\n");
			return 0;
		}
		if(b[i]>b[i-1]) {
			if(c[0]=='?') {
				c[0]='1';
			}
			for(long long j=1; j<b[i]; j++) {
				if(c[j]=='?') {
					c[j]='0';
				}
			}
			long long x=0;
			for(long long j=0; j<b[i]; j++) {
				x*=10;
				long long y=(long long)c[j]-'0';
				x+=y;
			}
			a[i]=x;
			continue;
		}
		long long flag=0;
		long long x=a[i-1];
		long long cnt=-1;
		while(x) {
			d[++cnt]=x%10;
			x/=10;
		}
		for(long long j=0; j<=cnt/2; j++) {
			swap(d[j],d[cnt-j]);
		}
		long long l=0;
		for(long long j=0; j<b[i]; j++) {
			if(c[j]!='?'&&d[j]<(long long)c[j]-'0'){
				flag=1;
				l=j;
				break;
			}
			if(c[j]!='?'&&d[j]>(long long)c[j]-'0'){
				flag=2;
				l=j;
				break;
			}
		}
		if(flag==1){
			for(long long j=l-1;j>=0;j--){
				if(c[j]=='?'){
					c[j]=d[j]+'0'; 
				}
			}
			for(long long j=l+1;j<b[i];j++){
				if(c[j]=='?'){
					c[j]='0';
				}
			}
		}
		if(flag==0){
			bool f=false;
			bool fl=false;
			for(long long j=b[i]-1;j>=0;j--){
				if(c[j]=='?'&&f==false){
					if(d[j]==9){
						c[j]='0';
						f=false;
					}
					else{
						c[j]=d[j]+'0'+1;
						f=true;
					}
					continue; 
				}
				if(c[j]=='?'&&f==true){
					c[j]=d[j]+'0';
				}
				if(c[j]=='?'&&d[j]!=9){
					fl=true;
				}
			} 
			if(f==false){
				printf("NO\n");
				return 0;
			}
		}
		if(flag==2){
			bool f=false,fl=false;
			for(long long j=l-1;j>=0;j--){
				if(c[j]=='?'&&f==false){
					if(d[j]==9){
						c[j]='0';
						f=false;
					}
					else{
						c[j]=d[j]+'0'+1;
						f=true;
					}
				}
				if(c[j]=='?'&&f==true){
					c[j]=d[j]+'0';
				}
				if(c[j]=='?'&&d[j]!=9){
					fl=true;
				}
			} 
			for(long long j=l;j<b[i];j++){
				if(c[j]=='?'){
					c[j]='0';
				} 
			}
			if(f==false){
				printf("NO\n");
				return 0;
			}
		}
		long long fx=0;
		for(long long j=0; j<b[i]; j++) {
			fx*=10;
			long long y=(long long)c[j]-'0';
			fx+=y;
		}
		a[i]=fx;
	}
	printf("YES\n");
	for(long long i=1; i<=n; i++) {
		printf("%lld\n",a[i]);
	}
	return 0;
}
```

### 注意事项

* 若位数相同时步骤 1 时 `bool` 变量若未被标记，则直接输出 `NO`。

* 位数更多时首位不能为 1。

---

## 作者：__AFO__ (赞：0)

## 题解

一道可怕的大模拟，思路其实很简单，特别考验代码力，就是先看长度，如果后面比前面的大，问号都为 0 就行了，注意开头不能为 0，反之直接输出 NO，如果是相等，就要分类讨论: 

1. 遍历时有后面有一个数字比前面大，且两个都是纯数字，将这个数后的问号全为 0，前面的与上一个数相同即可。 

2. 遍历时有后面有一个数字比前面小，且两个都是纯数字，向前寻找问号，只要问号对应的上一个数不是 9，就在上一个数的那里加 1，如果是 9，就为 0，并继续向前寻找，找到后，前面的问号与前面相同即可，后面的都为 0。

3. 果前面的数全相同，直到最后一位，再用第 2 种相同的办法。

最后完成输出。

**总结：** 多写代码，增强代码力。

 _代码_：
 ```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100005],k,w,l;
string s[100005];
int main() {
	scanf("%lld",&n);
	for(long long i=1; i<=n; i++) {
		cin>>s[i];
	}
	for(long long i=1; i<=n; i++) {
		if(s[i].size()<s[i-1].size()) {
			printf("NO");
			return 0;
		} else if(s[i].size()>s[i-1].size()) {
			for(long long j=0; j<s[i].size(); j++) {
				if(s[i][j]=='?') {
					if(j==0) s[i][j]='1';
					else s[i][j]='0';
				}
			}
		} else {
			for(long long j=0; j<s[i].size(); j++) {
				if(s[i][j]>s[i-1][j]&&s[i][j]!='?') {
					for(long long k=j+1; k<s[i].size(); k++) {
						if(s[i][k]=='?') s[i][k]='0';
					}
					for(long long k=0;k<=j-1;k++){
						if(s[i][k]=='?') s[i][k]=s[i-1][k];
					}
					break;
				} else if(s[i][j]<s[i-1][j]&&s[i][j]!='?') {
					w=0;
					l=0;
					if(j==0){
						printf("NO");
						return 0;
					}
					for(long long k=j-1; k>=0; k--) {
						if(w==1&&s[i][k]=='?') s[i][k]=s[i-1][k];
						if(s[i][k]=='?'&&s[i-1][k]!='9') {
							s[i][k]=char(int(s[i-1][k])+1);
							w=1;
						}
						if(k==0&&w==0){
							printf("NO");
							return 0;		 
						}
					}
					for(long long k=0; k<s[i].size(); k++) {
						if(s[i][k]=='?') s[i][k]='0';
					}
					break;
				}
				if(j==s[i].size()-1){
					for(long long k=s[i].size()-1;k>=0;k--){
						if(l==1&&s[i][k]=='?'){
							s[i][k]=s[i-1][k];
						}
						if(s[i][k]=='?'&&l==0&&s[i-1][k]!='9'){
						s[i][k]=char(int(s[i-1][k])+1);
						l=1;	
						}
						if(k==0&&l==0){
							printf("NO");
							return 0;
						}
					}
					for(long long k=0;k<s[i].size();k++){
						if(s[i][k]=='?') s[i][k]='0';
					}
					l=0;
				} 
			}
		}
	}
	printf("YES\n");
	for(long long i=1; i<=n; i++) {
		cout<<s[i]<<endl;
	}

	return 0;
}
```

完结撒花

---

## 作者：Addicted_Game (赞：0)

## [Restoring Increasing Sequence](https://www.luogu.com.cn/problem/CF490E)
~~我爱你，大模拟！~~

### 题意
给出一串严格递增的序列，隐藏其中的一些数字，求该序列是否存在。

### 思路
越前的数字尽可能小。（也可以从后往前，尽量大）

分 $3$ 大种情况。

-  $len_i < len_{i-1}$
不合法，输出 `NO`。

-  $len_i > len_{i-1}$
第一位放 $1$，其他为 $0$。

-  $len_i = len_{i-1}$
又分三种。
##### 1.除隐藏的 $s_i > s_{i-1}$
不同点之前的隐藏数字保持与 $s_{i-1}$ 一致，之后全部为 $0$。

##### 2.除隐藏的 $s_i < s_{i-1}$
将离不同点最近的对应非 $9$ 的隐藏数字变为对应数 $+1$，它之前跟对应点相同，其余为0。

##### 3.除隐藏的 $s_i = s_{i-1}$
找离最后对应非 $9$ 的隐藏数字变为对应数 $+1$，其余隐藏数字相同。

同第二种，将不同点设为 $len_i +1$ 即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s[100005];
int len[100005];
int flag;
int check(int x){
	for(int i=0;i<len[x];i++){
		if(s[x][i]!='?'&&s[x][i]>s[x-1][i]){
			flag=i;
			return 1;
		}
		if(s[x][i]!='?'&&s[x][i]<s[x-1][i]){
			flag=i;
			return -1;
		}
	}
	return 0;
}
void cz(){
	for(int i=0;i<len[1];i++){
		if(s[1][i]=='?'){
			if(!i) s[1][i]='1';
			else s[1][i]='0';
		}
	}//先处理第一个
	for(int i=2;i<=n;i++){
		if(len[i]>len[i-1]){
			for(int j=0;j<len[i];j++){
				if(s[i][j]=='?'){
					if(!j) s[i][j]='1';
					else s[i][j]='0';
				}
			} 
		}else{//一样
			int p=check(i);
			if(!p){
				p=-1;
				flag=len[i]+1;
			}
			if(p==1){//原本更大 
				for(int j=0;j<=flag;j++){
					if(s[i][j]=='?') s[i][j]=s[i-1][j];
				} 
				for(int j=flag+1;j<len[i];j++){
					if(s[i][j]=='?') s[i][j]='0';
				}
			}else{//原本更小 
				int j=flag-1;
				for(;j>=0;j--){
					if(s[i][j]=='?') {
						if(s[i-1][j]=='9') continue;
						s[i][j]=s[i-1][j]+1;
						break;
					}
					if(!j){
						puts("NO");
						exit(0);
					}
				}
				int t=j-1;
				for(;t>=0;t--){
					if(s[i][t]=='?'){
						s[i][t]=s[i-1][t];
					}
				}
				j++;
				for(;j<len[i];j++){
					if(s[i][j]=='?') s[i][j]='0';
				}
			}
		} 
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>s[i];
		len[i]=s[i].size();
		if(len[i]<len[i-1]){
			puts("NO");
			return 0;
		}
	}
	cz();
	for(int i=1;i<=n;i++){
		if(len[i]<len[i-1]||len[i]==len[i-1]&&s[i]<=s[i-1]){
			puts("NO");
			return 0;
		}
		for(int j=0;j<len[i];j++){
			if(s[i][j]=='?'){
				puts("NO");
				return 0;
			}
		}
		if(s[i][0]=='0'){
			puts("NO");
			return 0;
		}
	}
	puts("YES");
	for(int i=1;i<=n;i++){
		cout<<s[i]<<"\n";
	}
	return 0;
} 
```

---

## 作者：DHT666 (赞：0)

### 题意
给 $n$ 个数，数的位会被换成问号，把问号换成数字，使 $n$ 个数字按顺序严格单调递增。

### 思路
大模拟。

对于第一个数，最小即可，于是将问号换为 0。特别地，问号在首位则为 1。  

对于后面的所有情况，化为子问题：一个完整的数 $a$，一个不完整的数 $b$，想要使 $b>a$ 且 $b$ 尽量小。

分讨：

$lena > lenb$  
无解。

$lena < lenb$  
因为位数比 $a$ 多，因此随便填都可以满足要求。于是将问号换为 0。特别地，问号在首位则为 1。

$lena=lenb$  
较为复杂，继续分讨。  
1. 有 $a_i < b_i$  
说明有一位可以把 $a$ 比下去，那么 $i$ 以前的问号变为 $a_i$，$i$ 后的问号变为 $0$。

2. 有 $a_i > b_i$  
说明必须在 $i$ 前面变一个数把 $a$ 比下去，那么在 $i$ 前面找这样的一个位置（$a_i\ne 9$）。如有，则变化该问号，然后把更前面的问号变为 $a_i$，后面的所有问号都变为 0；如无，则无解。

3. 否则 $a_i=b_i$  
和 2 类似，也需要在 $i$ 前找一个数把 $a$ 比下去，代码也类似。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;

int n;
string s[N];

void work(int id,int len) {
	if(id == 1) {
		for(int i = 0;i < len;i++) {
			if(s[id][i] == '?' && i != 0) s[id][i] = '0';
			if(s[id][i] == '?' && i == 0) s[id][i] = '1';
		}
	} else {
		int llen = s[id - 1].size();
		
		if(llen > len) {
			cout << "NO";
			exit(0);
		}
		
		if(llen < len) {
			for(int i = 0;i < len;i++) {
				if(s[id][i] == '?' && i != 0) s[id][i] = '0';
				if(s[id][i] == '?' && i == 0) s[id][i] = '1';
			}
		}
		
		if(llen == len) {
			int f = 1;
			for(int i = 0;i < len;i++) {
				if(s[id][i] != '?' && s[id - 1][i] != '?' && s[id][i] - '0' > s[id - 1][i] - '0') {
					f = 2;
					break;
				}
				if(s[id][i] != '?' && s[id - 1][i] != '?' && s[id][i] - '0' < s[id - 1][i] - '0') {
					f = 0;
					break;
				}
			}
			
			if(f == 2) {
				int tot = 0;
				for(int i = 0;i < len;i++) {
					if(s[id][i] != '?' && s[id - 1][i] != '?' && s[id][i] - '0' > s[id - 1][i] - '0') {
						tot = i;
						break;
					}
				}
				
				for(int i = tot - 1;i >= 0;i--) {
					if(s[id][i] == '?') {
						s[id][i] = s[id - 1][i];
					}
				}
				for(int i = tot + 1;i < len;i++) {
					if(s[id][i] == '?') {
						s[id][i] = '0';
					}
				}
			}
			
			if(f == 1) {
				int tot = 1, f1 = 1, f2 = 1;
				for(int i = len - 1;i >= 0;i--) {
					if(s[id][i] == '?' && s[id - 1][i] != '9') {
						f1 = 0;
					}
					if(s[id][i] == '?') {
						f2 = 0;
					}
					if(tot && s[id][i] == '?' && s[id - 1][i] == '9') {
						s[id][i] = '0';
					}
					if(tot && s[id][i] == '?' && s[id - 1][i] != '9') {
						s[id][i] = s[id - 1][i] + 1;
						tot = 0;
					}
					if(!tot && s[id][i] == '?') {
						s[id][i] = s[id - 1][i];
					}
				}
				if(f1 || f2) {
					cout << "NO";
					exit(0);
				}
			}
			
			if(f == 0) {
				int tot = 0;
				for(int i = 0;i < len;i++) {
					if(s[id][i] != '?' && s[id - 1][i] != '?' && s[id][i] - '0' < s[id - 1][i] - '0') {
						tot = i;
						break;
					}
				}
				
				int qwq = 1, f1 = 1, f2 = 1;
				for(int i = tot - 1;i >= 0;i--) {
					if(s[id][i] == '?' && s[id - 1][i] != '9') {
						f1 = 0;
					}
					if(s[id][i] == '?') {
						f2 = 0;
					}
					if(qwq && s[id][i] == '?' && s[id - 1][i] == '9') {
						s[id][i] = '0';
					}
					if(qwq && s[id][i] == '?' && s[id - 1][i] != '9') {
						s[id][i] = s[id - 1][i] + 1;
						qwq = 0;
					}
					if(!qwq && s[id][i] == '?') {
						s[id][i] = s[id - 1][i];
					}
				}
				if(f1 || f2) {
					cout << "NO";
					exit(0);
				}
				
				for(int i = tot;i < len;i++) { 
					if(s[id][i] == '?') {
						s[id][i] = '0';
					}
				}
			}
		}
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	
	cin >> n;
	for(int i = 1;i <= n;i++) {
		cin >> s[i];
		int len = s[i].size();
		work(i, len);
	}
	
	cout << "YES" << endl;
	for(int i = 1;i <= n;i++) {
		cout << s[i] << endl;
	}
	
	return 0;
}
```

---

## 作者：ConstantModerato (赞：0)

这道题的思路其实很容易想到，关键在于考虑一个比较优秀的实现方式。

有两种考虑方式，第一种是尽可能小化位置靠前的数，让后面的数好放。第二种是尽可能最大化后面的数，让前面的数好放。这里两种方法都会有所讲到。

先考虑第二种方法。

1. 显然如果第 $i$ 个数的位数比第 $i + 1$ 个数的位数大，那么肯定无解。

1. 显然如果第 $i$ 个数的位数比第 $i + 1$ 个数的位数小，那么我们肯定贪心的把每一个问号位变成 $9$。

3. 如果位数相同，那么就尽可能的让前面最多的位数相同，来让这个数尽可能的大。

```
const int N = 1e5 + 5;
int n;string s[N];
int solve(string &s,string &t){
    if (s.size() > t.size()) return 1;
    if (s.size() < t.size()){
        for (int i = 0;i < s.size();i++)
            if (s[i] == '?')
                s[i] = '9';
        return 0;
    } int flag = 0,pos = 0;
    string p = s;
    for (int i = 0;i < s.size();i++){
        if (flag && s[i] == '?') s[i] = '9';
        if (!flag && s[i] == '?') s[i] = t[i];
        if (t[i] > s[i]) flag = 1;
        if (!flag && s[i] > t[i]){
            int check = 0;
            for (int j = i;j >= 0;j--){
                if (p[j] == '?'){
                    if (s[j] == '0') s[j] = '9';
                    else {s[j]--;check = 1;break;}
                }
            }
            if (check){flag = 1;}
            else return 1;
        }
    }
    int check = 0;
    if (s == t){
        for (int j = s.size() - 1;j >= 0;j--){
            if (p[j] == '?'){
                if (s[j] == '0') s[j] = '9';
                else {s[j]--;check = 1;break;}
            }
        }
        if (s[0] == '0' || s >= t) return 1;
        if (check) return 0;
        return 1;
    } 
    if (s[0] == '0') return 1;
    return 0;
}
signed main(){
    n = read();
    for (int i = 1;i <= n;i++) cin >> s[i],tmp[i] = s[i];
    s[n + 1] = "1145141919810";
    for (int i = n;i >= 1;i--){
        if (solve(s[i],s[i + 1])){
        puts("NO");
        return 0;}
    }
    puts("YES");
    for (int i = 1;i <= n;i++)
       cout << s[i] << endl;
    return 0;
}//喵内～
```

现在我们来思考一种更为简洁的实现方式。（此时我们考虑第一种方法，也就是尽可能的让前面小）。

考虑找到最高位，然后考虑能让这个数变小的最小值，并且这个数得比上一个数大，然后就改变这个数。然后再考虑下一个数……一直考虑直到不符合要求为止。

```
//code from kmjp
int more(string s,int v) {
    int q[10];
    int L=s.size();
    int i,j;
    while(1) {
        
        int val=0, tq=-1;
        FOR(i,L) if(s[i]=='?' && tq<0) tq=i;
        FOR(i,L) if(s[i]!='?') val += p10[L-1-i]*(s[i]-'0');
        
        if(tq==-1) {
            if(val>v) return val;
            else return -1;
        }
        
        FOR(i,L) if(s[i]=='?' && i>tq) val += p10[L-1-i]*9;//让前面尽可能的大，这样就可以让最高位尽可能的小。
        FOR(j,10) {
            s[tq]='0'+j;
            if(tq==0 && j==0) continue;
            if(val + j*p10[L-1-tq] > v) break;
        }
        if(j==-1) return -1;
    }
    return -1;
    
    
}
 
void solve() {
    int i,j,k,l,r,x,y; string s;
    
    p10[0]=1;
    FOR(i,8) p10[i+1]=p10[i]*10;
    
    cin>>N;
    FOR(i,N) {
        cin>>s;
        V[i+1]=more(s,V[i]);
        if(V[i+1]<0) return _P("NO\n");
    }
    
    
    
    _P("YES\n");
    FOR(i,N) _P("%d\n",V[i+1]);
    
    
}
```

代码相对来说比较简洁。




---

## 作者：RainFestival (赞：0)

显然，我们需要让每一个数尽量小

然而一个数只要高位小，整个数就小

所以我们可以使用贪心通过这道题目

注意判断无解的情况

代码

```cpp
#include<iostream>
#include<string>
int n;
std::string st[100005];
int put(std::string &x,std::string lst)
{
	if (x.size()<lst.size()) return 0;
	if (x.size()>lst.size())
	{
		int first=1;
		for (int i=0;i<x.size();i++)
		{
			if (x[i]=='?'){if (!first) x[i]='0';else x[i]='1';}
			if (x[i]!='0'&&x[i]!='?') first=0;
		}
		return 1;
	}
	int first=1,opt=0;
	for (int k=0;k<x.size();k++)
	{
		if (x[k]!='?')
		{
			if (first&&x[k]=='0') return 0;
			if (x[k]!='0') first=0;
			if (x[k]<lst[k]&&!opt) return 0;
			if (x[k]>lst[k]) opt=1;
			continue;
		}
		if (opt==1){x[k]='0';continue;}
		int can=0;
		for (int i='0';i<='9';i++)
		{
			if (first&&i=='0') continue;
			int flag=0;
			x[k]=i;
			for (int j=k;j<x.size();j++)
				if (x[j]=='?'&&lst[j]!='9'||x[j]!='?'&&x[j]>lst[j]){flag=1;break;}
				else if (x[j]!='?'&&x[j]<lst[j]) break;
			if (flag){can=1;break;}
		}
		if (!can) return 0;
		if (x[k]!='0') first=0;
		if (x[k]>lst[k]) opt=1;
	}
	return opt;
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) std::cin>>st[i];
	st[0]="";
	for (int i=1;i<=n;i++) if (!put(st[i],st[i-1])) return puts("NO"),0;
	puts("YES");
	for (int i=1;i<=n;i++) std::cout<<st[i]<<'\n';
	return 0;
}
```

---

## 作者：uid_310801 (赞：0)

### 题意概述
给你n个带有“？”的数，让你将“？”填上，问如何构造能使这个序列**严格递增**。

### 分析：
很明显这是一道贪心题，每一次尽量取可以取的最小值就好。

思路是：每次循环确定一个数的值，然后再用下一个字符串和这个数进行比较，如果能构造出来，就返回这个数，否则返回$-1$，即输出“$NO$”。

暂且将待确定数字的值记为$b$，已确定数字的值记为$a$。我们可以分为$3$种情况来讨论。

#### $Type$ $1$：$a$的长度大于$b$的长度
很明显$b$无论如何构造，都无法大于$a$，直接返回$-1$

`if(lenb<lena)	return -1;`

#### $Type$ $2$：$a$的长度小于$b$的长度
此时无论怎样构造，$b$都会大于$a$。所以我们将除了第一位以外的“$？$”都改成$0$，以保证$b$最小。（特别注意：**第一位不能是$0$！**）

```
if(lenb>lena)//这里的a和b已经都转为字符串格式。
{
	int intb=0;
	for(int i=0;i<lenb;i++)
	{
		if(b[i]=='?')
		{
			if(i==0)	b[i]='1';
			else b[i]='0';
		}
		intb=intb*10+b[i]-48;
	}
	return intb;
}
```

现在我们的a和b的长度都**相等**了，但是真正的难点才刚刚开始

#### $Type$ $3$：$a$的长度等于$b$的长度
再看做法之前，请你先自己想一想。我这个做法可能不是唯一的。但是我觉得很妙。

---

首先定义一个变量$flag$，初始值为1。然后从前往后扫一遍$b$数组，遇到“？”跳过

- 当遇到$b_i>a_i$时，$flag$设为$2$，$break$;

- 当遇到$b_i<a_i$时，$flag$设为$0$，$break$;

这样，我们又分成了三种情况。

#### $Type$ $3.1$：

**即$a$的长度等于$b$的长度，且b不是问号的部分大于a对应的部分。（$flag$==$2$）**

首先看一组数据：

$a=566423$

$b=5??5?3$

根据小学知识，我们知道比较长度相等的两个数时，高位上的数字越大，这个数就越大。

而要让$b$尽量小，且大于$a$，可以将$b_i$第一次大于$a_i$的数标记上，往左的“？”都设为$a_i$，往右的“？”都设为0。以保证$b>a$且$b$最小

这样我们将第一次大于$a_i$的数标记上：

$b=5??5?3$

$...........↑..$
(就是第四位的“$5$”）

往高位，“$？$”都设为$a_i$

$a=566423$

$b=5665?3$

然后往低位，“$？$”都设为$0$。

$a=566493$

$b=566503$

大家可以自行推理一下这个算法的正确性。

#### $Type$ $3.2$：

**即$a$的长度等于$b$的长度，且b不是问号的部分等于a对应的部分。（$flag$==$1$）**

再看这组数据：

$a=566493$

$b=5??4?3$

由于要让$b$尽量小，我们从后往前扫$b$，扫到$b_i$为“$？$”，**且**$a_i$**不为**$9$的时候，将$b_i$设置为$a_i+1$（如果$b_i$为“$？$”，$a_i$为$9$时，直接将$b_i$设为$0$），然后继续往前扫，扫到$b_i$为“$？$”时，将$b_i$设置为$a_i$。**特别地，如果从后往前扫，每个“$？$”对应的$a_i$都是$9$或者压根没有“$？$”的时候，返回$-1$**

$a=566493$

$b=5??4?3$

$...........↑..$（第四位的$4$标记上）

从后往前扫：

$a=566493$

$b=5??403$（跳过$9$）

$............↑.$

第一位标记上：

$a=566493$

$b=5?7403$（将第三位设为$a_i+1$）

$.........↑....$

往前的设为$a_i$：

$a=566493$

$b=567403$

$.......↑.......$

则$567403$即为所求。

证明思路不再赘述。

#### $Type$ $3.3$：

**$a$的长度等于$b$的长度，且b不是问号的部分等于a对应的部分。（$flag$==$0$）**

此部分和代码交由你们自己完成吧！

---

~~友情提供主程序代码~~：

```cpp
int main()
{
	int n,answer[100009];//存储答案
	scanf("%d",&n);
	int last=0;
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		last=possible(last,s);
		if(last==-1)	{cout<<"NO";return 0;}
		answer[i]=last;
	}
	cout<<"YES";
	for(int i=1;i<=n;i++)
	{
		printf("\n%d",answer[i]);
	}
	return 0;
}
```

---

