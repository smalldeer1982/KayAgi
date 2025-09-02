# Plasticine zebra

## 题目描述

Is there anything better than going to the zoo after a tiresome week at work? No wonder Grisha feels the same while spending the entire weekend accompanied by pretty striped zebras.

Inspired by this adventure and an accidentally found plasticine pack (represented as a sequence of black and white stripes), Grisha now wants to select several consequent (contiguous) pieces of alternating colors to create a zebra. Let's call the number of selected pieces the length of the zebra.

Before assembling the zebra Grisha can make the following operation $ 0 $ or more times. He splits the sequence in some place into two parts, then reverses each of them and sticks them together again. For example, if Grisha has pieces in the order "bwbbw" (here 'b' denotes a black strip, and 'w' denotes a white strip), then he can split the sequence as bw|bbw (here the vertical bar represents the cut), reverse both parts and obtain "wbwbb".

Determine the maximum possible length of the zebra that Grisha can produce.

## 说明/提示

In the first example one of the possible sequence of operations is bwwwbww|bw $ \to $ w|wbwwwbwb $ \to $ wbwbwwwbw, that gives the answer equal to $ 5 $ .

In the second example no operation can increase the answer.

## 样例 #1

### 输入

```
bwwwbwwbw
```

### 输出

```
5
```

## 样例 #2

### 输入

```
bwwbwwb
```

### 输出

```
3
```

# 题解

## 作者：ouuan (赞：10)

抽象派题解...

设原串长这样（被分成了两段）：

![](http://r.photo.store.qq.com/psb?/V11ZEfn31hRqZy/8gpWNgbn27GsLamvSW*XpfAv7xV0nMH263AwqRwZ51Y!/r/dDABAAAAAAAA)

操作后就长这样：

![](http://r.photo.store.qq.com/psb?/V11ZEfn31hRqZy/6yIfDOM7wI46pFAOoRC2bBJ0sqJDovA9umJzTBn1n14!/r/dDQBAAAAAAAA)

实际上就相当于这样（把后面的串移到前面）：

![](http://r.photo.store.qq.com/psb?/V11ZEfn31hRqZy/TggqPQYFRMN9*R8K03h6MP6KBTruZSB4WH*lRfAEQig!/r/dDYBAAAAAAAA)

所以这个串实际上可以看成一个环.（~~PPT是世界上最好的绘图软件！~~）

化环为链扫一遍就好了，注意答案对串的长度取min

```
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

string s;

int main()
{
    int i,ans,t;
    
    cin>>s;
    
    s+=s;
    
    ans=t=1;
    
    for (i=1;i<s.size();++i)
    {
        if (s[i]==s[i-1])
        {
            t=1;
        }
        else
        {
            ++t;
            ans=max(ans,t);
        }
    }
    
    cout<<min(ans,int(s.size()/2));
    
    return 0;
}
```

---

## 作者：Andy_Li (赞：5)

# CF1025C Plasticine zebra 题解

## 题意

给你一个字符串 $s$，只包含 $b$ 和 $w$。可以选择一个位置，使得这个字符串分成两段（其中一段包括这个位置），并将这两段分别翻转之后拼接起来。问经过若干次翻转之后（包括 $0$ 次），最长的相邻两位不同的字符串长度为多少。

## 思路

以头开始跑跑出最长长度，再从尾巴开始跑跑出最长长度。判断头和尾是否相等，不相等则上面抛出的两次最长长度相加，作为贡献之一。如果相等，则不贡献。

然后再将整个字符串跑一遍，不论开头和结尾字符，跑出最长长度后与上面的两次最长长度的和取一个最大值。

可以将首位开头的字符串答案相加的原因是不论在哪个地方反转，首位都将接头，所以首位两个字符一定不能一样才能有贡献。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	cin.tie(0);
	std::ios::sync_with_stdio(false);
	//srand((unsigned)time(NULL));
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int ans=0,cnt=1,fst=0,snd=0;
	string s;
	cin>>s;
	for(int i=0;i<s.size()-1;i++)
		if(s[i]!=s[i+1])
			cnt++;
		else
		{
			fst+=cnt;
			break;
		}
//	cout<<c<<endl;
	cnt=1;
	for(int i=s.size()-1;i>=1;i--)
		if(s[i]!=s[i-1])
			cnt++;
		else
		{
			snd+=cnt;
			break;
		}
	if(s[0]!=s[s.size()-1])
		ans=fst+snd;
//	cout<<ans<<endl;
	cnt=1;
	for(int i=0;i<s.size()-1;i++)
		if(s[i]!=s[i+1])
			cnt++;
		else
		{
			ans=max(ans,cnt);
			cnt=1;
		}
	ans=max(ans,cnt);
	cout<<ans;
	return 0;
}
```

---

## 作者：fuxuantong123 (赞：5)

# CF1025C Plasticine zebra 题解
## 思路
这个题可以看做求环上的最长交错字段，化环为链（连着存两遍），然后扫一遍就好了，注意答案对串的长度的一半取最小。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	string s;
	cin>>s;
	s=s+s;//化环为链
	int n=s.size();
	int cnt=1;
	int ans=0;
	for(int i=1;i<n;i++){
		if(s[i]!=s[i-1]){
			cnt++;
		}
		else{
			cnt=1;
		}
		//求最长交错字段
		ans=max(ans,min(cnt,n/2));//记得和n/2取最小
	}
	printf("%d",ans);
return 0;
}
```


---

## 作者：GXZJQ (赞：3)

# CF1025C Plasticine zebra 题解


### 题目分析

给出一个字符串 $s$，保证字符串中仅有字母 $b$ 和 $w$，每次操作你可以任选**一个** $k$ 值，使得在区间 $[1,k]$ 和 $(k,|s|]$ 分别反转，求经过人一次操作后能够得到的**最长** $01$ 交替出现的子串的长度。

------------


### string 知识铺垫（大佬可跳过）
本部分均以 $s$ 作为字符串名。

#### 字符串的输入
```cpp
//字符串的输入有几种方式：
cin>>s;
//特点是读入到第一个空格或者回车就会停止，且第一个元素的下标为0。

scanf("%s",s);
//特点同上

getline(cin,s);
//特点是可以直接读入一行。

```
#### 字符串元素的访问

```cpp
//字符串元素访问与数组一样，也是通过下标来访问，例如：
s[1],s[2]...

//字符串元素的判断
//对于字符串元素的判断，因为他每个元素都是char类型，所以要加上‘’，例如：
	if(s[1]=='a'){

	}
//特别的，如果是判断大于或者小于，则会按照ASCLL码判断。
```
------------

### 解题方法

使用模拟，将环状转换为链状，再循环取不同的 $k$ 值即可。需要注意 $k$ 值的上限，不能超过字符串的长度。


------------


###  _AC Code_ 
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int sum = 1; //储存最长的01交错字符串的长度
int ans;//储存答案
int len;//储存字符串长度
int main() {
//	freopen("CF1025C.in", "r", stdin);
//	freopen("CF1025C.out", "w", stdout);
	ios::sync_with_stdio(false);//输入优化，可跳过
	getline(cin, s);
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'w') { //0
			s[i] = '0';
		} else {
			s[i] = '1';
		}
	}
	s += s; //将环状转换为链状结构
	len = s.size(); //记录长度
	for (int i = 1; i < len; i++) {
		if (s[i] != s[i - 1]) { //因为这里是将s[i]与s[i-1]比较，所以下标要从1开始，否则会RE
			sum++;//连续的长度+1
		} else {
			sum = 1; //计数器归零
		}
		ans = max(ans, min(sum, len / 2)); //不断记录答案，记得一定是len/2
	}
	cout << ans;
	return 0;
}
```

---

## 作者：llqw (赞：2)

## CF1025C题解

[题目传送门](https://www.luogu.com.cn/problem/CF1025C)

### 思路：
规律题，这道题规律也不难。如果说原串 $s$ 长这样：$1011100101$，假设我们从第四个开始分割，那么我们就会得到：$1101101001$，如果我们把他抽象成一个环，我们就会发现 $1011100101$ 是环上的从位置 $1$ 开始顺时针顺序读的一串，而翻转后的 $1101101001$ 其实是环上从位置 $4$ 开始逆时针读的一串。这个环如下（后面的索引是他的位置）：
```cpp
    	1[10] 1[1]
	0[9]    0[2]
      1[8]       1[3]
       0[7]     1[4]
         0[6] 1[5]
          
```



所以说这道题就变成了给你一个环，求这个环上的最长的两两互不相等的子串长度。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int maxx = -1, countn = 1; //countn用于计数。
int main() {
	cin >> s;
	s += s; //复制该字符串用以建环。
	for (int i = 0; i < s.size(); i++) {
		if (i == 0) { //i=0无法与前一位比较，直接跳过。
			continue;
		}
		if (s[i] != s[i - 1]) {
			countn++;
		} else { //否则计数结束。
			countn = 1; //记得比完之后将countn置为1。
		}
		int lenth=s.size();
		maxx = max(maxx, min(countn, lenth / 2)); //因为建环时将原数组复制了一遍，所以说此处环的真正大小为s.size()/2)，同时countn也有可能会超出环的大小。
	}
	cout << maxx;
	return 0;
}

```



管理员大大求过。


---

## 作者：rui_er (赞：1)

思维题。

为了叙述方便，我们记字符串 $S$ 翻转后的结果为 $\widehat{S}$。

假设我们选择翻转的两段子串为 $A,B$（即 $S=AB$），那么得到的新字符串为 $S^\prime=\widehat{A}\widehat{B}$。

我们把字符串再次翻转，得到 $\widehat{S^\prime}=BA$，显然这次操作不会影响结果，即最长的黑白相间子串。

至此，问题转化为：对字符串 $S$ 进行循环移位（位数随意），最大化最长黑白相间子串长度。直接断环成链统计即可。

```cpp
// Problem: CF1025C Plasticine zebra
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1025C
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int n;
char s[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

int main() {
	scanf("%s", s);
	n = strlen(s);
	rep(i, n, n+n-1) s[i] = s[i-n];
	int now = 1, ans = 0;
	rep(i, 1, n+n-1) {
		if(s[i] == s[i-1]) now = 1;
		else ++now;
		chkmax(ans, now);
	}
	chkmin(ans, n);
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Ouaoan (赞：0)

题目：[Plasticine zebra](http://codeforces.com/contest/1025/problem/C)

思路：
将序列首位相接，题目即求环上的最长交错字段。
为什么可以这样做呢？
![这里写图片描述](https://img-blog.csdn.net/20180820191139424?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3JhYmJpdF9aQVI=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)
（图丑勿喷）
比如说假设我们将序列abcdef从bc处截断并翻转得到第二行的序列得到，可以发现，序列bafedc变成环形后等价于fedcba。由于是求01序列的最长交错子串，变更后的串也就等价于abcdef。同理将第二个串从ed间截断并翻转得到第3个串，也等价于环形上的abcdef。
注意，当原序列本来就是交错的时，要特殊判断。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

#define maxn 100000

int n;
char a[maxn+5];

int main() {
	scanf("%s",a);
	n=strlen(a);
	for(int i=n;i>=1;i--) a[i]=a[i-1];
	a[0]=0;
	int len=0,pre=1,suf=1;
	for(int i=2;i<=n;i++) {
		if(a[i]==a[i-1]) break;
		pre++;
	}
	for(int i=n-1;i>=1;i--) {
		if(a[i]==a[i+1]) break;
		suf++;
	}
	if(suf==n) {
		printf("%d",n);
		return 0;
	}
	if(a[1]!=a[n]) len=pre+suf;
	int s=0;
	for(int i=1;i<=n;i++) {
		if(a[i]==a[i-1]) {
			s=1;
		} else s++;
		len=max(len,s);
	}
	
	printf("%d",max(len,max(pre,suf)));
	return 0;
}
```

---

