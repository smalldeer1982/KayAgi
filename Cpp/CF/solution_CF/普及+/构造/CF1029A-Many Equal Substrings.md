# Many Equal Substrings

## 题目描述

You are given a string $ t $ consisting of $ n $ lowercase Latin letters and an integer number $ k $ .

Let's define a substring of some string $ s $ with indices from $ l $ to $ r $ as $ s[l \dots r] $ .

Your task is to construct such string $ s $ of minimum possible length that there are exactly $ k $ positions $ i $ such that $ s[i \dots i + n - 1] = t $ . In other words, your task is to construct such string $ s $ of minimum possible length that there are exactly $ k $ substrings of $ s $ equal to $ t $ .

It is guaranteed that the answer is always unique.

## 样例 #1

### 输入

```
3 4
aba
```

### 输出

```
ababababa
```

## 样例 #2

### 输入

```
3 2
cat
```

### 输出

```
catcat
```

# 题解

## 作者：Acapplella (赞：17)

这道题目主要考查KMP算法中的next数组具体含义，当然为了防止next与库函数中的重名，我一般都是用ne,来表示next的，反正无伤大雅的啦。

关于KMP算法有这样一个结论，分享给大家：**如果len%(len-next[len])==0就说明有循环节，len-next[len]的值，就是s的最小循环节的长度，而len/（len-next[len]）就是最大循环次数！（其中len是字符串的长度）。**

抓住字符串中最后一个字符的前缀与后缀相同的值（即next[n]），这道题就很好解决啦。
话不多说，代码如下：
```cpp
#include<iostream>
using namespace std;
int n, k;
char a[53];
int ne[53];
int main()
{
	cin >> n >> k;
	cin >> a + 1;
	for (int i = 2, j = 0;i <= n;i++)
	{
		while (a[j + 1] != a[i] && j)   j = ne[j];
		if (a[j + 1] == a[i])     j++;
		ne[i] = j;
	}
	for (int i = 1;i <= n;i++)
		cout << a[i];
	int ans = k - 1;
	while (ans--)
		cout << a+ne[n]+1;
	return 0;
}
```
本蒟蒻第一次写题解，求通过。QWQ.

希望各位大佬在食用之余能顺手点个赞，码字不易，谢谢！

我这个好像是最短的代码了吧！~~滑稽~~



---

## 作者：CreeperK (赞：9)

人生第一次CF&愉快地爆炸祭……然而还是来写一篇比较正经（不正常）的题解。

看到题目，要求构造一个新串，使其有$k$个相同的给定字串。

我看到这道题，马上就想到KMP了（竟然不是模拟QAQ）

它要求新串尽可能短，即用旧串构造时不仅没有新的字符，而且重叠部分尽可能多，那不就是求最长前缀和后缀相同的长度吗？KMP直接上啊。

求出来了，该如何输出？

比如样例：
```cpp
3 4
aba
```
可得知$next[n]=1$，因此第二个字符串的第一个字符不用输出，只要输出后两个字符。

我的字符串是从零开始的，所以$f[n]$刚刚好就是最长前缀后一个位置，即我们需要输出的开始处。

附上代码：
```cpp
/*
Codeforces Round #506
A Many Equal Substrings
*/
#include<cstdio>
#include<algorithm>
using namespace std;
int f[60],n,k;
char s[60];
void Cal_Next(){
	f[0]=f[1]=0;
	for(int i=1;i<n;i++){
		int j=f[i];
		while(j>0 && s[i]!=s[j])j=f[j];
		if(s[i]==s[j])f[i+1]=j+1;
		else f[i+1]=0;
	}
}
int main(){
	scanf("%d%d",&n,&k);
	scanf("%s",s);
	Cal_Next();
	printf("%s",s);
	for(int i=1;i<k;i++){
		for(int j=f[n];j<n;j++)printf("%c",s[j]);
	}
}
```

---

## 作者：Yaha (赞：4)

## KMP

我们想让构造出的新串尽可能短，容易想到，要让旧串构造时不出现新字符，且重叠部分尽可能多。**KMP**。

比如：$abca$这个模式串，$abca'bca$就比$abca'abca$优。


再如下面这一个短串：（$A,B$ 视为子串）

|  A| B  | A  |
| -----------: | -----------: | -------:|


我们在构造时就要尽可能地利用重复子串，即$A$。

$k=3$：$ABA' BA' BA$ 就比 $ABA' ABA'ABA$优。

也就是说，**短串中，如果存在一个前缀，同时是串的后缀的话，我们就让它在构造的新串中，即作为一个串的后缀，又作为下一个串的前缀。**

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[51];
int kmp[51],n,k;
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		cin>>a[i];
	int i=2,j=0;
	while(i<=n)
	{
		while(j&&a[i]!=a[j+1]) j=kmp[j];
		if(a[i]==a[j+1]) kmp[i++]=++j;
		else kmp[i++]=j;
	}
	for(int i=1;i<=n;i++)
		cout<<a[i];
	for(int i=2;i<=k;i++)
		for(int j=kmp[n]+1;j<=n;j++)
			cout<<a[j];
	return 0;
}
```


---

## 作者：sc84bbs (赞：3)

刚看一眼这题：trie？

然后:不对，kmp

看到数据范围：不对，暴力

代码里边讲具体思路

```cpp
#include<iostream>
#include<cstdio>
#include<cctype> 
#include<cstring>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;
	char t[100005];
	cin>>t;
	int maxsize=-1;//记录最多能给ka掉多少位
	for(int i=0;i<n-1;i++){
		bool flag=0;//插个旗子
		for(int j=0;j<=i;j++){
			if(t[j]!=t[n-i+j-1]){//我匹配我自己 如果匹配不上...
				flag=1;//...就拔掉旗子 然后break掉省时间
				break;
			}
		}
		if(!flag)maxsize=i;//如果旗子没被拔掉就记录下
	}
    maxsize++; //因为j<=i,所以当i=0时j其实会跑一次，i=1时跑两次，以此类推。既然这样那就要把跑的次数记到maxsize里边，也就是给它++下

	for(int i=1;i<k;i++){
		for(int j=0;j<n-maxsize;j++){//先少输出一遍 
			cout<<t[j];
		} 
	}
	cout<<t;//最后把完整的输出上
	return 0;
}

```

顶多橙题水平（

看不懂私我

---

## 作者：zheysq_147 (赞：2)

蒟蒻初学$KMP$，搜到了这道题，做完感觉对$next$数组的意义理解的更深刻了，一道非常好的$KMP$练手题，值得一刷。

这题暴力就不说了，一定会$TLE$的，~~再说了，这种题暴力最多是入门~~。如果没学过$KMP$，请看 [这个](https://www.luogu.com.cn/blog/pks-LOVING/zi-fu-chuan-xue-xi-bi-ji-qian-xi-kmp-xuan-xue-di-dan-mu-shi-chuan-pi-post)，然后做一下[这道题](https://www.luogu.com.cn/problem/P3375)。

这道题先来看题意，题目说：

“构造一个字符串s，使得它的可能长度最小，要求s中存在k个位置i,可以找到k个以i为出发点的子串t。”

我们可以理解为在原有字符串中前面和后面找到两个相同的子串，然后......（~~突然忘了要说神马~~），在原有子串的基础上复制$k-1$个包含**中间部分+重复部分**的字符串，即可得到答案。

为神马呢？请看，这是一个字符串：$abccbbabc$，要构造一个字符串，里面含有k个$abccbbabc$，我们可以把这个串前后一样的部分省略掉一个，留下一个就足够了。

假设$k=3$：

如果不省略：$abccbbabcabccbbabcabccbbabc$

长度为$9k$。但是，我们再把这个字符串仔细看一看，会发现，中间有两个$abcabc$，可以把这个子串简化为$abc$，也就是说把前一个的最后和后一个的开头连起来，既然重合就一定会减少，所以这才是最优的方案，长度为$9k-3*2=9k-6$，明显比上一种要短。

这样，可以先把$1$ ~ $next[n]$这一段先打出来，然后输出$k$个残缺（~~没头~~）的字符串，或者先输出整个原始字符串，然后再输出$k-1$个残缺字符串，即可获得答案。

贴重点部分code：

```
for(i=1;i<=n;++i)
printf("%c",s[i]);
for(i=1;i<k;++i)
{
	for(j=nxt[n]+1;j<=n;++j)
	printf("%c",s[j]);
}
```

要注意，$next$是关键字符，不能当数组名，（~~看我的CE记~~~~录~~）。

求个赞

---

## 作者：codesonic (赞：1)

因为要构造一个字符串使它包含另一个字符串p次，所以最显而易见的答案是输出p次这个字符串，然而这不是最短。

显然一个单词的前缀可以与其后缀重叠，所以直接用kmp算法求出前缀与后缀相同的长度，略去那一部分输出即可

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

int kmp[100];

int main()
{
	string s;
	int n,p;
	scanf("%d%d",&n,&p);
	cin>>s;
	int len=s.length();
	int k=0;
	for(int i=1;i<len;i++){
        while(k&&s[i]!=s[k])
            k=kmp[k];
        if(s[i]==s[k])kmp[i+1]=++k;
    }
    cout<<s;
    for(int i=2;i<=p;i++){
    	for(int j=kmp[len];j<len;j++)
    		cout<<s[j];
	}
	return 0;
}
```

---

## 作者：Fraction (赞：1)

本题的意思就是，要你求一个制胡窜的最长的相同的前缀和后缀

~~这不是$kmp$吗~~

于是，按照$kmp$初始化的步骤写就行了

代码：

```
#include <bits/stdc++.h>
#define fp(i, l, r) for(register int i = (l); i <= (r); i++)
#define fd(i, l, r) for(register int i = (l); i >= (r); i--)
#define ANTISYNC ios::sync_with_stdio(false)
#define full(a, b) memset(a, b, sizeof(a))
#define MAXN (int)1e3 + 5
#define ll long long
#define il inline
using namespace std;

template <typename T>il void read(T &dig) {
	char c = getchar();
	bool flag = false;
	dig = 0;
	while(!isdigit(c) && c != '-') c = getchar();
	if(c == '-') flag = true, c = getchar();
	while(isdigit(c)) dig = dig * 10 + c - '0', c = getchar();
	if(flag) dig = -dig;
}

int n, m, cnt = 0, len;
int fail[MAXN];
char str[MAXN];

il int init() {
	read(n), read(m);
	scanf("%s", str+1);
	len = strlen(str+1);
	int j = 0;
	fail[0] = 0;
	fp(i, 2, len) {
		while(j > 0 && str[i] != str[j+1]) j = fail[j];
		if(str[i] == str[j+1]) ++j;
		fail[i] = j;
	}
	int cnt = fail[n];
	printf("%s", str+1);
	--m;
	fp(i, 1, m) {
		fp(j, cnt+1, len) {
			printf("%c", str[j]);
		}
	}
	return 0;
}

int main() {
	init();
	return 0;
}
```

---

## 作者：让风忽悠你 (赞：0)

[原题](https://www.luogu.com.cn/problem/CF1029A)

KMP 裸题，因为是将 $k$ 个相同的字符串拼在一起，所以只需找到首尾的最长公共部分，即做自身 KMP，最后输出稍作处理即可。

直接上代码

```cpp
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define N 55

using namespace std;

int n,k,j;
int nxt[N];
char s[N];

int main(){
	scanf("%d%d",&n,&k);
	scanf(" %s",s+1);
	for(int i=2;i<=n;++i){
		while(j && s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) ++j;
		nxt[i]=j;
	} // KMP 部分 
	for(int i=1;i<k;i++)
		for(int j=1;j<=n-nxt[n];j++)
			printf("%c",s[j]);
	printf("%s",s+1);
	// 先将前 k-1 次输出，最后一次是完整的 
	return 0;
}
```


---

## 作者：苏打青柠水 (赞：0)

题解没有java的做法，这里我发表一下java的hash做法。
首先需要计算该串的hash值，然后通过前后匹配，来找前缀和后缀最大的重叠部分，找到就退出，如果到达边界也退出，即证明该串前后没有重叠部分，迭代的串就应该是它本身。
```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class Main {

	public static void main(String[] args) throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String number[] = reader.readLine().split(" ");
		int n = Integer.parseInt(number[0]);
		int m = Integer.parseInt(number[1]);

		String ss = reader.readLine().trim();
		char s[] = ss.toCharArray();
		if (m == 0) {
			return;
		}
		
		
		final int base = 131;  //基数
		long hash[] = new long[n + 1];
		//保存p[i]==base的i次方
		long p[] = new long[n + 1];
		p[0] = 1;

		for (int i = 1; i <= n; i++) {
			
			hash[i] = hash[i - 1] * base + s[i - 1];   //计算前i个字符串的哈希值
			p[i] = p[i - 1] * base;     
		}
		
		
		int end = n - 1, start = 2;     

		
		/*以aba为例
		 * 先匹配ab 和 ba的哈希值 ，不同则，end--，start++
		 * 再匹配a 和 a的哈希值  ，相同，则退出循环
		 */
		while (true) {
			if ((hash[end]) == (hash[n] - hash[start - 1] * p[n - start + 1])) {
				break;

			}
			end--;  
			start++;
			if (end == 0 || start == n + 1)  //如果超过边界，则证明该串头尾没有公共部分
				break;
		}
		String part = "";  //保存需要迭代m-1次的部分 
		if (end == 0 || start == n + 1)  //超过边界即为整个串
			part = ss;
		else
			part = ss.substring(end);   

		StringBuffer sb = new StringBuffer();
		
		sb.append(ss);  
		for (int i = 0; i < m - 1; i++)   
			sb.append(part);
		System.out.println(sb);

	}
}
```


---

## 作者：TechZ (赞：0)

#### 首先题目要求字符串尽可能地短并且要找到k个字串，那么我们可以想到
如果字符串的头部与尾部有**相同部分**那么这一部分就可以省略满足最短.  
而相同部分则被称为最长相同前后缀那么KMP算法就是以这个为核心本题
只要求出最长相同前后缀即可解决  
我们用F数组存储字符串第i位的最长相同前后缀，那么我们输出时先输出整个字符串在循环k-1次每次从F[n]+1处开始输出

```cpp
#include<cstdio>
#include<iostream>
#include<string>//使用string
using namespace std;
string a;
int n,k;
int f[55];
void get_next()//求F数组不懂可以去百度，有非常多的优秀博客
{
    f[0]=-1;
    for(int i=1;i<n;i++)
    {
        int j=f[i-1];
        while(a[j+1]!=a[i]&&(j>=0))
       j=f[j];
        
        if(a[j+1]==a[i])
        {f[i]=j+1;
        continue;
        }
        f[i]=-1;
        
    }

}
int main()
{
    scanf("%d%d",&n,&k);
    cin>>a;
   get_next();
    int p=f[n-1]+1;//从f[n-1]+1输出因为string从0开始储存
    
    cout<<a;
    for(int i=1;i<k;i++)
    {
        for(int j=p;j<n;j++)
        cout<<a[j];
    }
    return 0;
}
```


---

## 作者：oneman233 (赞：0)

**这道题不知道是数据有问题还是~~也许题意就是如此~~**

基本想法是求出kmp的前缀数组p，但是之后每一次只需要从p[t.length()]的位置往后输出就行了，意思是只有最后一位的前缀值才有用，每一次从那儿继续输出到末尾就行了。

我的代码中是用string把答案先存好再输出的，并且首先把t复制进去了，不管怎么样至少要首先完整的输出一遍t才行嘛。

下面上代码，关键部分已有注释：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n,k;
int p[55];
string t;

void getp()
{
    int j=0;
    p[0]=p[1]=0;
    for(int i=1;i<t.length();++i){
        while(j&&t[j]!=t[i])
            j=p[j];
        if(t[j]==t[i])
            j++;
        p[i+1]=j;
    }
}

void build()
{
    getp();
    string ans=t;
    ///at least print once
    int cnt=1;
    ///nums of matchings
    while(cnt<k){
        for(int i=p[t.length()];i<t.length();++i)
            ans.append(1,t[i]);
        cnt++;
    }
    cout<<ans;
}

int main()
{
    cin>>n>>k>>t;
    build();
    return 0;
}

```


---

## 作者：Leap_Frog (赞：0)

## CF1029A Many Equal Substrings（题解）

题目传送门：[点我](https://www.luogu.org/problemnew/show/CF1029A)

主要思路：求出字符串的[前缀数组](https://www.cnblogs.com/AndyJee/p/4474073.html)，然后再根据前缀数组求出答案。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline void Find_Next(string s,ll next[])//求前缀数组
{
	ll k=-1;
	next[0]=-1;
	for(ull i=1;i<s.size();i++)
	{
		while(k>-1&&s[k+1]==s[i]) k=next[k];
		if(s[k+1]==s[i]) k++;
		next[i]=k;
	}
}
int main()
{
	ll k,ne[55];
	string s;
	cin>>ne[0]>>k>>s;
	Find_Next(s,ne);//调用函数
	for(ll i=1;i<=k-1;i++)
		for(ull i=0;i<s.size()-1-ne[s.size()-1];i++)
			cout<<s[i];//最后重复的不输。
	cout<<s<<endl;
	return 0;
}
```

~~以上程序手模一下就理解了。~~

---

## 作者：ljk_Elaina (赞：0)

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;
string str;
int i,j;

int main() {
	cin>>n>>k; //简单题就不用scanf或qiuck_read了QwQ
	cin>>str; //string比char输入输出更容易QwQ
	int len=str.length();
	for(i=1;i<len;i++){ //暴力找最长相同子串的长度,i是枚举长度,j是枚举位置
		bool flag=true; //记录用的flag
		for(j=0;j<len-i;j++)
			if(str[j]!=str[i+j]){
				flag=false;
				break;
			}
		if(flag==true){//如果可以,输出QwQ
			cout<<str;
			for(int d=2;d<=k;d++)
				for(int s=len-i;s<len;s++)
					cout<<str[s];
			return 0;
		}
	}
	for(i=1;i<=k;i++)
	    cout<<str;
	return 0;
}
```
好吧，没什么好说的（暴力出奇迹QwQ）……

先暴力扫一遍字符串，记录下最长相同子串的长度，然后重复$K-1$遍，最后把原来的字符串输出。

---

