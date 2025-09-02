# [NWRRC 2015] Concatenation

## 题目描述

著名的程序员 Gennady 喜欢创造新单词。其中一种方法是连接现有单词。

举个例子：如果 Gennady 有 `cat` 和 `dog` 两个词，那么他会得到一个新词： `catdog`，这可能意味着带有两个头的生物的名字：一个猫头和一个狗头。

Gennady 觉得这种创建新单词的方式有点无聊，因此他发明了另一种方法：使用第一个单词的非空前缀，第二个单词的非空后缀，并将它们连接起来。例如，如果他有单词 `tree` 和 `heap` ，则可以得到诸如 `treap`，`tap` 或 `theap` 之类的单词。

Gennady 选择了两个单词，并想知道他可以使用新方法创建多少个不同的单词。当然，作为著名的程序员，他已经计算出了答案。他突然想考考你，那么你能编写一个程序把答案计算出来吗？

## 样例 #1

### 输入

```
cat
dog
```

### 输出

```
9
```

## 样例 #2

### 输入

```
tree
heap
```

### 输出

```
14
```

# 题解

## 作者：kkxacj (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/P7050)

#### 引言

这个蒟蒻没有认真读题，交了几遍才过，写个题解纪念一下。

#### 思路

一道简单的模拟，但要注意细节。

拿样例来说
```cpp
cat
dog

分别可以组成

cg cog cdog cag caog cadog catg catog catdog

这九种可能。
```
那么，在没有构成重复单词的情况下，它一共可以构成第一个单词的字母个数乘上第二个单词的字母个数，现在我们需要知道如何去掉重复单词，那么，请看第二个样例

```cpp
tree
heap

构成的不再展示，这里展示重复单词

(tre eap  tree ap)  (tre ap  tr eap)
```

不难发现，重复单词就是两个单词相同的字母数量乘积。

#### 注意：他的构成方法是：使用第一个单词的非空前缀，第二个单词的非空后缀。

code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum,ans,a[60],b[60];
string s,s1;
int main()
{
	cin >> s >> s1;
	ans = s.size() * s1.size();
	for(int i = 1;i < s.size();i++) a[s[i] - 'a']++;
	for(int i = 0;i < s1.size() - 1;i++) b[s1[i] - 'a']++;
	for(int i = 0;i < 26;i++) sum += a[i] * b[i];
	printf("%lld",ans - sum);
	return 0;
}


```


---

## 作者：1qaz234Q (赞：2)

### 题意简述
输入两个单词 $s_1$ 和 $s_2$。取出 $s_1$ 的非空前缀和 $s_2$ 的非空后缀，将它们拼接起来，形成一个新的单词。求可以组成多少个新的单词。
### 题目分析
我们先不考虑重复。设 $s_1$ 的长度为 $a$，为了取出 $s_1$ 的非空前缀，我们可以从第 $0$ 个字符取到第 $1,2,3,\dots,a-1$ 个字符，则 $s_1$ 的取法共有 $a$ 种。设 $s_2$ 的长度为 $b$，为了取出 $s_2$ 的非空后缀，我们可以从第 $0,1,2,\dots,b-2$ 个字符开始取，取到第 $b-1$ 个字符，则 $s_2$ 的取法共有 $b$ 种。

那么根据乘法原理，在不考虑重复的情况下共有 $a\cdot b$ 种取法。

然后我们考虑怎么去掉重复的单词。如果我们从 $s_1$ 中取的非空前缀为 $c+d$，在 $s_2$ 中取的非空后缀为 $e$，且 $s_2$ 的前面为 $d$，那么拼接后的单词为 $c+d+e$。如果在 $s_1$ 中取非空前缀为 $c$，在 $s_2$ 中取的非空后缀为 $d+e$，并且 $s_1$ 后面为 $d$，那么拼接后的单词也为 $c+d+e$。这两种情况重复了。

于是我们用两个数组 $cnt1,cnt2$ 分别储存 $s_1,s_2$ 的每个字符的出现次数。然后我们枚举每个字符，求出在 $s_1$ 中的出现次数和在 $s_2$ 中的出现次数的乘积，然后加起来。最后去重。

注意，因为 $1\leq\left|s_1\right|,\left|s_2\right|\leq10^5$，所以要开 long long。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long // C++ 要注意开 long long
const int N = 1e5 + 10;
int cnt1[N]; // s1 中每个字符的出现次数
int cnt2[N]; // s2 中每个字符的出现次数
signed main()
{
    string s1, s2;
    int sum = 0; // s1 和 s2 中重复的单词的出现次数
    cin >> s1 >> s2;
    for (int i = 1; i < s1.size(); i++) // 因为要取出 s1 非空前缀，所以 i 要从 1 开始枚举
    {
        int a = s1[i] - 'a' + 1; // 求出当前的字符是第几个
        cnt1[a]++;               // s1 中 a 的出现次数增加 1
    }
    for (int i = 0; i < s2.size() - 1; i++) // 因为要取出 s2 非空后缀，所以 i 要枚举到 s2.size() - 2
    {
        int b = s2[i] - 'a' + 1;
        cnt2[b]++;
    }
    for (int i = 1; i <= 26; i++)
    {
        int tmp = cnt1[i] * cnt2[i]; // 当前字符在 s1 和 s2 中的出现次数的乘积
        sum = sum + tmp;             // 更新 s1 和 s2 中重复的单词的出现次数
    }
    int ans = s1.size() * s2.size(); // 不考虑重复的情况下答案为两个单词的长度的乘积
    ans = ans - sum;                 // 去掉重复出现的单词
    cout << ans;
}
```

---

## 作者：i_love_tym (赞：2)

这题我们先观察样例。

显然，$S_1$ 和 $S_2$ 可以组成的字符串数量是 $S_1$ 的长度 $\times S_2$ 的长度。

可是如果按照上面的方法计算，样例二因该输出 $16$，可为什么输出的是 $14$ 呢？

我们来看看它们所构成的字符串。

``tp trp trep treep``

``tap trap treap treeap``

`` teap treap treeap treeeap``

``theap trheap treheap treeheap``

我们可以发现第二行和第三行有两个词重复了，如果减去这两个词的话答案就正确了。

所以，答案 $=S_1$ 的长度 $\times S_2$ 的长度 $-$ 重复的单词数。

两个长度好求，但重复的数量怎么求呢？

首先，我们可以想到用 ``map`` 容器。

于是，我们可以写出下面的代码。

```
#include<iostream>
#include<map>
using namespace std;
map<string,bool> t;
int main(){
	string a,b;
	cin>>a>>b;
	for(int i=1;i<=a.size();i++){
		for(int j=0;j<b.size();j++) {
			string c=a.substr(0,i)+b.substr(j);
			t[c]=1;
		}
	}
	cout<<t.size();
}

```

MLE 了。

那我们想想还有什么方法可以得到重复的数量。

再次观察样例二后发现，重复的数量就是两个单词的相同字母数量之积。

为什么每出现一个相同的字母，就会有重复的单词出现呢？

就拿 ``tree`` 和 ``heap`` 证明一下：

可见，两个词中重复的字母是可以构成的重复词为:

``treap`` 和 ``treeap``

我们在设 $a$ 为字符串 1 的非空前缀 $+x$，$b$ 为 $x+$ 字符串 2 的非空后缀，重复的字母为 $x$。

可得 $(a-x)+b=a+(b-x)$。

其中 $-$ 的意思就是去掉这个字母。

所以，我们只需要开两个数组分别记录两个字符串中每个字母的出现次数，然后计算出有多少重复的字母就好了。 

# ACCODE

```
#include<bits/stdc++.h>
using namespace std;
long long sum,ans,a[60],b[60];
string s,s1;
int main()
{
	cin >> s >> s1;
	ans = s.size() * s1.size();
	for(int i = 1;i < s.size();i++) a[s[i] - 'a']++;
	for(int i = 0;i < s1.size() - 1;i++) b[s1[i] - 'a']++;
	for(int i = 0;i < 26;i++) sum += a[i] * b[i];
	printf("%lld",ans - sum);
	return 0;
}
```

---

## 作者：_Above_the_clouds_ (赞：2)

# 思路：
算出两个给定的单词中创建不同单词的数量。因为使用第一个单词的非空前缀，第二个单词的非空后缀，所以第一个单词的第一个字母和第二个单词的最后一个字母是确定的，则下标应分别从 $1\sim{n-1}$ 和 $0\sim{n-2}$（下标从 $0$ 开始）。用 $ans$ 记录答案，初始化先设为两个单词的长度之积，也就是所能创造的所有单词（可能有重复），再减去所有重复单词，重复单词就是两个单词相同的字母数量乘积，最后输出即可。

# 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long ans;
string s, t;
long long v[100005], v2[100005];

int main() {
	cin >> s >> t;//输入
	ans = s.size() * t.size();//初始化
	for (int i = 1; i < s.size(); i++)
		v[s[i] - 'a']++;//标记
	for (int i = 0; i < t.size() - 1; i++)
		v2[t[i] - 'a']++;//同上
	for (int i = 0; i <= 25; i++)
		ans -= v[i] * v2[i];//减去所有重复单词
	cout << ans;//输出
	return 0;
}

```


---

## 作者：pidan (赞：0)

时隔多年窝终于又发了一篇题解

## 【题目描述】

著名的程序员 Gennady 喜欢创造新单词。其中一种方法是连接现有单词。

举个例子：如果 Gennady 有 ``cat`` 和 ``dog`` 两个词，那么他会得到一个新词： ``catdog``，这可能意味着带有两个头的生物的名字：一个猫头和一个狗头。

Gennady 觉得这种创建新单词的方式有点无聊，因此他发明了另一种方法：使用第一个单词的非空前缀，第二个单词的非空后缀，并将它们连接起来。例如，如果他有单词 ``tree`` 和 ``heap`` ，则可以得到诸如 ``treap``，``tap`` 或 ``theap`` 之类的单词。

Gennady 选择了两个单词，并想知道他可以使用新方法创建多少个不同的单词。当然，作为著名的程序员，他已经计算出了答案。他突然想考考你，那么你能编写一个程序把答案计算出来吗？

## 【输入格式】

两行，每行有一个 Gennady 选择的单词 $si$ ($1\leq si\leq100000$，$si$ 仅由小写英文字母组成)。

## 【输出格式】

输出一个整数，这个整数表示 Gennady 可以从这两个给定的单词中创建不同单词的数量。

## 题解

先来分析题目：

用一个字符串$s1$的前缀与另一个字符串$s2$的后缀拼接成一个单词，运用乘法原理，很容易得到可重集大小为$strlen(s1)\times strlen(s2)$

接下来就可以直接考虑如何去重了

我们发现，如``tree``和``heap``，用``tr``与``eap``相拼接等同于用``tre``与``ap``相拼接，而用``tre``与``eap``相拼接等同于用``tree``与``ap``相拼接。由此得到启发，是不是$s1$中与$s2$中每一对相同的字母都能产生一个重复答案呢？

来波证明：

假设当前选中的$s1$的前缀为$p$，$s2$的后缀为$c+q$，且$p$的下一位为$c$，那么拼接得到$p+(c+q)$等同于$(p+c)+q$，并且这样不需要考虑相同子串的情况，因为子串中的每一对相同的字母都已经对答案产生了贡献了。

那么，去重就可以用两个数组$sum1,sum2$分别存储$s1,s2$中每个字母的出现次数，然后计算每个字母在两个数组中的数量的积并求和，最终的答案就是

### $strlen(s1)\times strlen(s2)-\sum_{i=a}^z{sum1_i\times sum2_i}$

贴上代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
using namespace std;
int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
char s1[100010],s2[100010];
int tmp1[26],tmp2[26];
signed main(){
	scanf("%s%s",s1,s2);
	int cnt=0;
	int l1=strlen(s1),l2=strlen(s2);
	for(int i=1;i<l1;i++)tmp1[s1[i]-'a']++;//tips:子串非空，所以要从1开始
	for(int i=0;i<l2-1;i++)tmp2[s2[i]-'a']++;//同理
	for(int i=0;i<26;i++)cnt+=tmp1[i]*tmp2[i];
	printf("%lld\n",l1*l2-cnt);
	return 0;
}
```


---

## 作者：Kobe_BeanBryant (赞：0)

### 题目大意：
求两个单词能组成多少个新单词。


### 举例：
首先我们先拿两个单词来举例一下：

第一种是没有重复的情况：

$ \verb!dog! $ 与 $ \verb!cat! $。 

它们能够组成的单词如下：


$ \verb!dcat , dat , dt , docat , doat , dot , dogcat , dogat , dogt ! $

第二种是有重复的情况：

$ \verb!tree! $ 与 $ \verb!heap! $。

它们能够组成的单词如下：

$ \verb!theap , teap , tap , tp , trheap , treap , trap , trp , trehaep , treeap , treap , trep , treeheap , treeeap , treeap , treep ! $

我们能发现在这些新单词中有重复的，我们就将重复的删除掉。

剩下的单词：
$ \verb!theap , teap , tap , tp , trheap , trap , trp , trehaep , treap , trep , treeheap , treeeap , treeap , treep ! $
### 思路：
构成方法：用第一个单词的**非空前缀**，用第二个单词的**非空后缀**。

那么我们可以用 $ ans $ 记录答案，再初始化设为两个单词长度之积，就是能创造的所有单词。

而前面我们已将两种情况都举例了一遍，就可以先减去所有重复单词，且重复单词就是两个单词相同的字母数量乘积，最后输出。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e1+6;
string s1,s2;
long long a[N],b[N];
long long ans,x,y;
int main(){
	cin>>s1>>s2;
	x=s1.size(),y=s2.size();
	for(int i=1;i<x;i++)
		a[s1[i]-'a']++;
	for(int i=0;i<y-1;i++)
		b[s2[i]-'a']++;
	for(int i=0;i<26;i++)	
		ans+=a[i]*b[i];
	printf("%lld",x*y-ans);
	return 0;
}
```

---

