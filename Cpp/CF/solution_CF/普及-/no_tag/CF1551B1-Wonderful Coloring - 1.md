# Wonderful Coloring - 1

## 题目描述

This is a simplified version of the problem B2. Perhaps you should read the problem B2 before you start solving B1.

Paul and Mary have a favorite string $ s $ which consists of lowercase letters of the Latin alphabet. They want to paint it using pieces of chalk of two colors: red and green. Let's call a coloring of a string wonderful if the following conditions are met:

1. each letter of the string is either painted in exactly one color (red or green) or isn't painted;
2. each two letters which are painted in the same color are different;
3. the number of letters painted in red is equal to the number of letters painted in green;
4. the number of painted letters of this coloring is maximum among all colorings of the string which meet the first three conditions.

E. g. consider a string $ s $ equal to "kzaaa". One of the wonderful colorings of the string is shown in the figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1551B1/c8856daa04b74978f65da846cae3db3aad690b80.png)The example of a wonderful coloring of the string "kzaaa".Paul and Mary want to learn by themselves how to find a wonderful coloring of the string. But they are very young, so they need a hint. Help them find $ k $ — the number of red (or green, these numbers are equal) letters in a wonderful coloring.

## 说明/提示

The first test case contains the string from the statement. One of the wonderful colorings is shown in the figure. There's no wonderful coloring containing $ 3 $ or more red letters because the total number of painted symbols will exceed the string's length.

The string from the second test case can be painted as follows. Let's paint the first occurrence of each of the letters "c", "o", "e" in red and the second ones in green. Let's paint the letters "d", "f" in red and "r", "s" in green. So every letter will be painted in red or green, hence the answer better than $ 5 $ doesn't exist.

The third test case contains the string of distinct letters, so you can paint any set of characters in red, as long as the size of this set doesn't exceed half of the size of the string and is the maximum possible.

The fourth test case contains a single letter which cannot be painted in red because there will be no letter able to be painted in green.

The fifth test case contains a string of identical letters, so there's no way to paint more than one letter in red.

## 样例 #1

### 输入

```
5
kzaaa
codeforces
archive
y
xxxxxx```

### 输出

```
2
5
3
0
1```

# 题解

## 作者：wanggk (赞：3)

[CF1551B1题目](https://www.luogu.com.cn/problem/CF1551B1)

**突破口：** 

* **染成红色的字母数量等于染成绿色的字母数量！**

意味着什么呢？我们要两个两个地找。

那么又因为同一个字母不同颜色，所以每找一对红绿色，可以分为两种情况：

* 红绿色同个字母（此字母必须在串中出现两次以上）

* 红绿色不同字母

那么，可以用一个 $cnt[]$ 数组统计每个字母出现的次数。

若 $cnt[i]>=2$ ,成功找到一对，是第一种情况，`ans++;`

若 $cnt[i]=1$ ,说明是单个的，两个单个字母即使第二种情况，`sum++;`

最终答案：`ans+=sum/2；`



------------


完整代码：
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
int T,n;
char s[55];
int cnt[26];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(cnt,0,sizeof(cnt));
		cin>>s;
		n=strlen(s);
		for(int i=0;i<n;i++) cnt[s[i]-'a']++;
		int ans=0,c=0;
		for(int i=0;i<26;i++)
		{
			if(cnt[i]>=2) ans++;
			else if(cnt[i]==1) c++;
		}
		ans+=c/2;
		printf("%d\n",ans);
	}
	return 0;
}
```



---

## 作者：tongzhenxuan (赞：3)

## 思路解析

很简单，我们只要让被染色的字母越多越好（红色越多，绿色也越多）。

假设我们拿到了一个字母，它在这个单词里面出现了 $n$ 次，我们分两类讨论

 
1.	$n\ge1$ 

显然当 $n\ge2$ 时，有两个字母将被进行染色，一红一绿（越多越好策略），而剩下的 $n-2$ 个字母，由于规定了同色的任两个字母不相同，所以只能不被染色。

2.	$n=1$

而当 $n=1$ 时，它得拉一个跟他一样只出现一个的字母，一个染绿，一个染红，才能达到红色与绿色的个数相同。

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[10001];
int a[30],i;
void work()
{
	memset(a,0,sizeof(a));//清零计数数组 
	int l=strlen(ch);
	for(i=0;i<l;i++) a[ch[i]-'a'+1]++;//将每一个字母出现的次数累加 
	int f1=0,f2=0;//f1代表单个出现的字母，f2代表出现大于等于两次的字母 
	for(i=1;i<=26;i++)
	{
		if(a[i]>=2) f2++;
		else if(a[i]==1) f1++;
	}
	int sum=0;
	sum=f2+f1/2;//f2可以直接加入，一红一绿，单个出现则要找搭档，才能保证红色个数等于绿色个数 
	cout<<sum<<"\n";
}
int main()
{
	int T;
	cin>>T;
	while(T)
	{
		cin>>ch;
		work();
		T--;
	}
} 
```


---

## 作者：NXYorz (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF1551B1)

--------
### 题目翻译
给定字符串 $s$，并用两种颜色（红色和绿色）给它涂色。

规定:

- 每一个字符要么被涂一个颜色，要么不涂色。
- 相同的字符不会一个颜色
- 两种颜色所涂的字符数量应该相同。

在上述约束条件下，一个颜色最多可以涂 $s$ 中的几个字符。

---------
### 分析

把字符相同的放在一起分析:在某一堆相同的字符中最多两个可以被涂色。

记录下所有相同字符的数量，如果大于两个直接涂色，不够两个的字符互相配对即可。

---------
### $Code$
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int Len = 51;

int t;
int sum[27];
char s[Len];

void work()
{
	memset(sum , 0 , sizeof(sum));
	cin>>s; int len = strlen(s);
	for(int i = 0; i < len; i++)
		sum[s[i] - 'a' + 1]++;
	int ans = 0; int cnt = 0;
	for(int i = 1; i <= 26; i++)
		if(sum[i] > 1) ans++;
		else if(sum[i] == 1) cnt++;
	printf("%d\n", ans + cnt / 2);
}

int main()
{
//	freopen("aa.in","r",stdin);
	scanf("%d",&t);
	while(t--)
		work();
	return 0;
}
```

---

## 作者：Forever1507 (赞：0)

比较友好的一道题了。

显然贪心的思想，一种字母要尽可能地同时被两种颜色染，这样的话，那么假设字母 $letter$ 的出现次数为 $num_{letter}$，那么，它的贡献就是 $\min(2,num_{letter})$，因为最多只有两种颜色。

最后答案要除以二，因为这里是两种颜色。

那么代码就呼之欲出了：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
string s;
int flag[300];
int main(){
	cin>>t;
	while(t--){
		memset(flag,0,sizeof(flag));//多测不清空，保龄两行泪
		cin>>s;
		int ans=0;
		for(int i=0;i<s.size();i++){
			if(flag[s[i]]<=1)ans++;
			flag[s[i]]++;
		}
		cout<<ans/2<<'\n';
	}
	return 0;
}
```


---

## 作者：Wu_while (赞：0)

# 题意

将一个字符串的每个字符染色，满足以下条件：

1. 每个点或被染成红色，或被染成红色，亦或不被染色

2. 同色的任两个字母不相同

3. 染成红色的字母数量等于染成绿色的字母数量

# 分析

我们来看一下第二条和第三条。

这表示了什么？

表示对于每种字母，最多**填一个红色，一个绿色**。也就是说，当这个字母的数量不少于 $2$ 时，它对答案的贡献为 $1$。

如下：

![](https://z3.ax1x.com/2021/08/27/hQ5Eg1.png)

最多填一个红色和一个绿色：
![](https://z3.ax1x.com/2021/08/27/hQ5pHU.png)

而对于只有一个的字母，每一个字母填红色，就要有一个字母填绿色。也就是说，设所有个数为 $1$ 的字母的数量为 $tot$，则对答案的贡献为 $\left\lfloor\frac{tot}{2}\right\rfloor$。

如下：
![](https://z3.ax1x.com/2021/08/27/hQ5Hr6.png)

每一个字母填红色，就要有一个字母填绿色：

![](https://z3.ax1x.com/2021/08/27/hQIUQ1.png)

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
string s;
int a[30];
int ans,tot;
void work()
{
	ans=tot=0;
	memset(a,0,sizeof(a));
	cin>>s;
	for(int i=0;i<s.length();i++)
		a[s[i]-'a']++;
	for(int i=0;i<26;i++)
	{
		if(a[i]>=2)
			ans++;
		if(a[i]==1)
			tot++;
	}
	ans+=tot/2;
	printf("%d\n",ans);
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
		work();
	return 0;
}
```

---

## 作者：Starlit_Night (赞：0)

#### 题目大意
1. 给定一个字符串，每个字母可以染成红色和蓝色或者不染色。  
2. 保证红色和蓝色的字母数量一样多
3. 同样的字母不能染成同样颜色
4. 使染色数量尽可能多  

#### 题目分析  
依题意每个字母有 $3$ 种情况：红色、蓝色、不染色，而根据上面的第 $3$ 条原则，我们可以看出来如果一个字母出现了第 $3$ 次及以上，那么第 $3$ 次及以后的该字母不能被染色，因此我们可以建一个数组来记录某个字符的出现次数，进而统计出能被染色的字母数目。  
进一步分析，假定有 $5$ 个字母可以被染色，那么能染色的最大数量为 $4$ ，即染红色数量为 $2$ 。假定有 $4$ 个字母可以被染色，那么能染色的最大数量为 $4$ ，即染红色数量为 $2$ 。同理推知，用 $N$ 表示能染色的数目，最终被染成红色的最大数目为 $N \div 2$。

#### 核心代码  
```cpp
int main() {
	int n;
	scanf("%d",&n);
	while(n--){
		string str;
		int a[26]={0};//统计26个字母的个数
		cin>>str;	
		int cnt=str.size();//设cnt为能被染色的字母大小
		int tmp=cnt;//用tmp存储字符串大小
		for(int i=0;i<tmp;i++){//计算能被染色的字母个数
			a[str[i]-'a']++;//该字母出现次数加1
			if(a[str[i]-'a']>=3){
				cnt--;//如果该字母重复3次及以上 则该字母的第三次及以后重复都无法被染色
			}
		}//算出来能被染色的字母个数
		cout<<cnt/2<<endl;
        }
	return 0;
}
```

---

## 作者：black_trees (赞：0)


整场比赛的题解：[Link](https://www.luogu.com.cn/blog/Junko-Youmu/cfr-734)（目前还没补完）。

---

题目大意：
>有两种颜色红和绿，现在给你一个只有小写字母的字符串。

>现在要求你给每个元素涂上一种颜色（可以不涂）。

>一个涂法是“漂亮的”，需要满足以下条件：

> 1.涂上同一种颜色的所有字母不能相同。

> 2.涂成红色的字母个数和涂成绿色的字母个数需要相等。

>给定一个字符串，请问它涂成红色（或绿色）的字母最多有多少个？

首先考虑第一个条件。

转化一下也就是说每一种字母最多只能有两个被涂上颜色。

所以我们开一个桶统计一下每一个字母的出现次数并对其进行判断。

再考虑第二个条件。

因为只会有两种颜色，所以涂上颜色的点的个数必须是偶数（ $2$ 的倍数）。

那么思路就出来了，统计一下每一个字母出现的次数，并且统计它最多有多少个字母可以被涂上颜色。

对于每一种字母，如果它的个数小于等于 $2$ 那么就都可以被涂色，如果大于等于 $3$ 就只有两个可以被涂上颜色。

因为有两种颜色，所以答案就是可以被涂上颜色的字母个数除以 $2$。

如果最后可以被涂上颜色的字母个数是个奇数，就需要先减 $1$ 再除 $2$。

Code：

```cpp

#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ln(s) s.size();
int T;
int lett[27];
int cal(char c){
	return (int)c-'a'+1;
}
string s;

signed main(){
	scanf("%lld",&T);
	while(T--){
		memset(lett,0,sizeof lett);//多测不清空，只有见祖宗
		cin>>s;
		int l=ln(s);
		for(register int i=0;i<l;++i){
			lett[cal(s[i])]++;
			// cout<<cal(s[i])<<" ";
		}
		// puts("");
		bool f=false;
		int res=0;
		// for(register int i=1;i<=26;++i){
		//     cout<<lett[i]<<endl;
		// }
		for(register int i=1;i<=26;++i){
			if(lett[i]==1) res+=1;
			if(lett[i]>1) res+=2;
		}
		printf("%lld\n",res/2);//C++自动向下取整所以不用减。
	}
	return 0;
}
```

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1551B1)

一句话题意：每个格子可以涂红色或绿色或不涂色，相同字母的格子不能涂相同颜色，红绿两种颜色的格子数必须相等，求最多能涂多少个红色格子。

考虑统计相同字母的格子数，字母 $i$ 的格子数记作 $a_i$。

对于 $a_i≥2$，只有两个格子能够分别涂成红色和绿色，其余格子不能涂色，对答案的贡献为 $1$。

对于 $a_i=1$，这个格子既可以涂成红色也可以涂成绿色，即两个这样的格子对答案贡献为 $1$。

于是分别计算贡献再相加即可。

时间复杂度 $O(t|s|)$。

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#define ll long long
#define back return
#define ri register int 
using namespace std;
int read()
{
	int x=0,f=1;
    char ch=getchar();
	while(!isdigit(ch))
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
	while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
	back x*f;
}
string s;
ll t,n,m,a[200005];
int main()
{
	cin>>t;
	while(t--)
	{
		ll sum=0,ans=0;
		for(ri i=97;i<=122;i++)
			a[i]=0;
		cin>>s;
		ll ls=s.size();
		for(ri i=0;i<ls;i++)
			a[(int)s[i]]++;
		for(ri i=97;i<=122;i++)
		{
			if(a[i]>=2)
				ans++;
			if(a[i]==1)
				sum++;
		}
		cout<<sum/2+ans<<endl;
	}
    back 0;
}
```

---

## 作者：KSToki (赞：0)

# 题目大意
给定一个字符串，取出两个相离的大小相同的下标集合，集合中每个下标对应的字母需不同，最大化集合的大小。

其实就是 B2 的 $k=2$ 且字符集大小仅为 $26$ 的特殊情况，且不需要输出方案，就挂一个[B2题解](https://www.luogu.com.cn/blog/ypcaeh/solution-cf1551b2)。
# 题目分析
首先统计每个数字出现的次数，如果大于等于 $2$ 那么显然每个集合分一个，否则待定。贪心地，最后将待定的数字依次 $2$ 个一组分配给每个集合即可，这里直接用两个变量实现。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,cnt[26],a,b;
string s; 
int main()
{
	T=read();
	while(T--)
	{
		memset(cnt,0,sizeof(cnt));
		cin>>s;
		for(R int i=0;i<s.length();++i)
			++cnt[s[i]-'a'];
		a=b=0;
		for(R int i=0;i<26;++i)
		{
			if(cnt[i]>1)
				++a;
			if(cnt[i]==1)
				++b;
		}
		putint(a+b/2);
	}
	return 0;
}

```

---

