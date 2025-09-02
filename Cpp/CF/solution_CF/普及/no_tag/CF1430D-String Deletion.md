# String Deletion

## 题目描述

You have a string $ s $ consisting of $ n $ characters. Each character is either 0 or 1.

You can perform operations on the string. Each operation consists of two steps:

1. select an integer $ i $ from $ 1 $ to the length of the string $ s $ , then delete the character $ s_i $ (the string length gets reduced by $ 1 $ , the indices of characters to the right of the deleted one also get reduced by $ 1 $ );
2. if the string $ s $ is not empty, delete the maximum length prefix consisting of the same characters (the indices of the remaining characters and the string length get reduced by the length of the deleted prefix).

Note that both steps are mandatory in each operation, and their order cannot be changed.

For example, if you have a string $ s = $ 111010, the first operation can be one of the following:

1. select $ i = 1 $ : we'll get 111010 $ \rightarrow $ 11010 $ \rightarrow $ 010;
2. select $ i = 2 $ : we'll get 111010 $ \rightarrow $ 11010 $ \rightarrow $ 010;
3. select $ i = 3 $ : we'll get 111010 $ \rightarrow $ 11010 $ \rightarrow $ 010;
4. select $ i = 4 $ : we'll get 111010 $ \rightarrow $ 11110 $ \rightarrow $ 0;
5. select $ i = 5 $ : we'll get 111010 $ \rightarrow $ 11100 $ \rightarrow $ 00;
6. select $ i = 6 $ : we'll get 111010 $ \rightarrow $ 11101 $ \rightarrow $ 01.

You finish performing operations when the string $ s $ becomes empty. What is the maximum number of operations you can perform?

## 说明/提示

In the first test case, you can, for example, select $ i = 2 $ and get string 010 after the first operation. After that, you can select $ i = 3 $ and get string 1. Finally, you can only select $ i = 1 $ and get empty string.

## 样例 #1

### 输入

```
5
6
111010
1
0
1
1
2
11
6
101010```

### 输出

```
3
1
1
1
3```

# 题解

## 作者：vectorwyx (赞：6)

~~这题比C简单多了~~

------------

每次操作包含两步：删除任意一个字符，删除最前面的连续字段。

考虑最简单的情况，即 $s=010101……$ 或 $s=101010……$，设 $s$ 的长度为 $len$，显然答案为 $\lceil\frac{len}{2}\rceil$。

而如果 $0/1$ 在某些地方连续出现了多次，我们在删去这些连续的字段之前贪心地把删除单个字符的操作放在这些字段里肯定是最优的。由于我们只关心连续字段的长度，因此可以开一个数组记录每个字段的长度，对于每次操作，先删掉任意一个还未被删去的连续字段中的一个字符，再删去最前面的连续字段。前者具有单调性，维护一下就可做到 $O(n)$ 的复杂度。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=2e5+5;
string s;
int a[maxn],top;

void work(){
	int n=read(),last=0,ans;
	top=0;
	cin>>s;
	fo(i,1,n-1){
		if(s[i]!=s[i-1]) a[++top]=i-last,last=i;//记录连续字段的长度 
	}
	a[++top]=n-last;
	int pos=1;//pos用来记录上一次操作中长度大于1的连续字段的下标 
	fo(i,1,top){
		while(pos<=top&&a[pos]==1) pos++;
		//printf("%d ",pos);
		a[pos]--;
		if(pos>top){
			ans=i-1+(top-i+2)/2;
			printf("%d\n",ans);
			return;
		}
		if(pos<=i) pos=i+1;
	}
	printf("%d\n",top);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：explorerxx (赞：3)

### 题意概括


------------
给一个0/1串，每次选择删除一个字符，然后将整个串前面的一个连续0串或者连续1串(0串在前就删0串，1串在前就删1串)给删除，这两个删除算一次操作，求删空字符的时候最大操作数量是多少

------------
### 分析


------------
先摆样例方便下面的说明
下文中叙述时均定字符串的最左端是第一位，不按照字符串实际下标表示,即本文字符串的第一位是1。

**eg1: 10010011**

**求最大操作数量，所以每次尽量删除更少的字符**。

对于一个串比如[eg1]，如果删除了某个单字符（eg1的第4位），当它在中间的时候，删掉它有可能会把左右两个串给合并，使得它们可以被一次性删除(删它产生1000011,消除了前缀1就是000011，然后下一次必定会把这一长串0给删掉)，对以后造成不利影响。

模拟一下: 10010011->000011->1(选某个1)或11(选某个0)->空  ---共3次

当这个单字符是前缀的时候(比如eg1的第1位，删了它变成0010011，接着前缀消除变成10011，消了3位)，如果删掉它，有可能它紧邻的后面存在一个连续串，那么删掉它就会有一个连续串直接被删除，一次性删掉了很多字符。

模拟一下:10010011->10011->11->空 ----共3次

综上我们不该直接删除单字符。那么先删除多字符中的字符呢？

**eg2 0001010**

对于前缀是多字符(eg2的前三位)，只选择它自己中间的任意字符显然最优，这样它只会删掉自己，而不会多删任何一个字符。如果选择了它之外的字符，显然不但删除了它，还在它之外又多删除了一个，使得答案更劣。

**eg3 10010011**(其实还是eg1)

对于前缀是单字符(eg3的第一位)，优先选择利用后面的长串（**长串即长度大于等于2的串**）删一个字符然后让这个单字符作为前缀被删掉;

模拟过程: 10010011->010011->1011->01->空 . . .一共删了4次

这样每次前缀为单字符的时候只删掉了两个字符,显然最优,否则就是我们在eg1中提到过的。

当然，只剩下单字符的时候，只能一次删除两个了，删到最后就好。没的玩。

### 具体实现


------------

我们的贪心只和块的长度有关，所以我们把字符串化作块集，用数组储存每个块的长度，然后按照上述贪心，如果前缀是单字符，用一个指针q(下标)来往后寻找大于2的块，没有的话就全都是单字符，一次减2长度来干掉他们并累计答案。如果前缀是多字符，更好办，直接删掉这个块，累计一次答案。

代码如下


------------

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
char s[200100];
int bl[200100],blo;//第i块里有多少个数，有多少块
int main()
{
	cin>>t;
	for(register int j=1;j<=t;j++)
	{
		memset(bl,0,sizeof(bl));blo=0;
		int n;int q=1;int ans=0;
		scanf("%d",&n);scanf("%s",s);
		for(register int i=0;i<n;i++)
		{
			blo++;
			while(1)
			{
				bl[blo]++;
				if(s[i+1]!=s[i]) 
				break;
				i++;
			}
		}
		int flag=0;
		for(int i=1;i<=blo;i++)//现在已经可以用块来处理这件事情了 
		{
			if(flag)//只剩单块，每次两个 
			{
				ans++;i++;
				continue;
			}
			if(bl[i]>=2)//对于一个大于等于2的联通块，删除自己 
			{
				ans++;
			}
			else
			{
				while(q<i||(q<=blo&&bl[q]<2))q++;//后置指针如果没有跟上枚举让它先跟上枚举，然后往后面找大于2的块
				if(q>blo)//如果q直接飞了出去,说明后面没有大于等于2的块了,直接跳过前缀的两个单字符块 
				{
					flag=1;
					ans++;
					i++;
				}
				else{//如果存在大于等于2的块,这个块少1个 
					bl[q]--;
					ans++;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
1
6
100100

*/



```


------------


------------
ps:
**eg4 101100**

(   其实长串的定义也可以是长度大于2的串，比如说eg4，如果定义长串是大于2的串，现在没有大于2的串了，我们只好一个个(两个两个)删，显然可以删三次  

101100->1100->00->空

如果说我们定义长串是大于等于2的话，会先选择第三位的1，然后删前缀1，得到0100，然后再删第三位的0，接着前缀0没了，剩下10，依然是一步删除了。

101100->0100->10->空

从上边我们发现，不管我们定义长串是大于还是大于等于2，删到它不是长串的时候(各自定义下的长串)，再删它的时候(按照每次只看前缀再选择删除的贪心原则)最多也最少减掉两个字符，真的定义大于2的块是长串的话，手动模拟是没有问题的，只是如果定义大于2的块是长串的话，我的程序会认为有两个字符的块为一个字符，一次跳过两个块的时候其实删去三个字符，会使答案变少，所以在我的操作中，大于等于2的串是长串 ）

------------


---

## 作者：vеctorwyx (赞：2)



### 题目大意：

给你一个01串，每次操作删除一个元素并删除最前面的连续一串1或一串0，求最大操作次数。

[CF原题链接](https://codeforces.com/problemset/problem/1430/D)

### SOL：

~~手玩一下~~得到想要得到最大操作次数只能有两种操作情况：

1. 长度为1的连续串$(010101...)$每次操作会删除两个连续串，如果只有长度为1的连续串最多操作$len/2$次

1. 长度大于1的连续串每次操作会删除一个连续串，如果只有长度大于一的就会有$cnt$（连续串个数）次操做。

将以上两种情况结合可以得到做法：

每次删除最靠前的长度大于1连续串，然后再删除最前面的连续串，重复此操作直到只剩长度为1的连续串（假设操作了$x$次），剩余的操作次数就是$len/2$，最大总操作次数就是$x+len/2$次。

code：

```
#include<bits/stdc++.h>
using namespace std;
int t,n;
char a[200010];
int sta[200010],cnt;
int main()
{
	cin>>t;
	while(t--)
	{
		int ans=0;
		int cnt=0;
		cin>>n;
		cin>>a;
		int pre=0;
		for(int i=1;i<=n-1;i++)
		{
			if(a[i]!=a[i-1])
			sta[++cnt]=i-pre,pre=i;;
		}
		sta[++cnt]=n-pre;//记录每一个连续串的长度
		int x=1;
		for(int i=1;i<=cnt;i++)
		{
			while(x<=cnt&&sta[x]==1)//只能删除长度大于1的连续串
			x++;
			sta[x]--;
			if(x>cnt)
			{
				cout<<(i-1+(cnt-i+2)/2)<<endl;//输出答案
				ans=1;
				break;
			}
			if(x<=i)
			x=i+1;
		}
		if(ans)
		continue;
		cout<<cnt<<"\n";//只有长度大于1的串
	}
	return 0;
}
```

---

## 作者：NXYorz (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1430D)

贪心

可以发现，对于连续的$1$或者连续的$0$的字符串，当它们成为**前缀**时，一定是一下子就删除完了，这就使得我们造成了一定的“损失”，而题目要求我们是操作次数最多，这就为我们提供了一种思路：优先删除**连续**的子串，尽量使其周围的字符与其不同，但是也要量力而行，因为**前缀是不停删除的**。

考虑双指针，其中一个指针$1$来删除前缀，另一个指针$2$去扫描整个区间，尽量删除**连续的子串**，当指针$2$扫描完整个区间后，就说明此时区间已经是$10101010$类似的字符串了，我们就只能每次删除两个字符了，可以直接$O(1)$回答，也可以用指针$2$往回扫，指针$1$继续往后扫，直到相遇。注意还可能存在最后前缀直接把剩下的序列消除的情况！

### $Code$

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
 
using namespace std;
 
const int N = 2e5 + 10;
 
int t,n,cnt,ans;
bool v[N];
 
void work()
{
	scanf("%d",&n); memset(v,0,sizeof(v));
	string s; cin >> s; ans = 0;
	bool flag = 0;
	for(int li = 0 , ri = 0; ri < n ;)
	{
		ans++;
		if(li >= n - 1) flag = 1;
		if(!flag)
		{
			while((s[li] != s[li + 1] || v[li]) && li < n - 1) 
				li++;
			v[li] = 1;
		}
		else 
		{
			while(v[li] && li >= ri) li--;
			if(li < ri) return;
			v[li] = 1;li--;
		}
		if(li < ri && flag) return;
		while(ri < n)
		{
			while(v[ri]) ri++;
			while(s[ri] == s[ri + 1]) v[ri] = 1 , ri++;
			break;
		}
		v[ri] = 1; ri++;
		while(v[ri] && ri < n) ri++;
	}
	return;
}
 
int main()
{
//	freopen("aa.in","r",stdin);
	scanf("%d",&t);
	while(t--)
		work() , printf("%d\n",ans);
	return 0;
}
```

~~英语一定要学好啊！一开始理解错题意了以为字符任意位置随便删，结果prefix的意思原来是前缀啊~~

感谢翻译的大佬

---

## 作者：do_while_true (赞：1)

[$\text{更佳的阅读体验}$](https://www.cnblogs.com/do-while-true/p/13799080.html)

# D. String Deletion

### Translate

$T$ 次询问，对于每一次询问：

给定一个长度为 $n$ 的 $01$ 串，每次操作可以选择一个位置 $i$，消除第 $i$ 位，然后把 $01$ 串前面连续的一串 $1$ 或者是一串 $0$ 消除，求最大操作数。

### Solution

先把一个个连续的串的长度存下来。

肯定不希望消掉一个位置之后会有串合并，而这种合并的情况就是消单个的数的情况。

所以说对于前面的单个的数，利用后面的多数删掉，如果前面的就是多数，直接删掉即可。直到不能删为止，剩下的肯定是交替的单数，这个时候只能一个一个消，因为不管怎样花式消答案都是一样的。

具体来讲，对于 $1110100010$:

消 $i=1$，得到 $0100010$。

消 $i=3$，得到 $10010$。

消 $i=2$，得到 $010$。

这个时候剩下的 $010$，一个一个消可以消 $2$ 次。

### Code

我的代码实现比较难理解，建议自己写写吧。

```cpp
const int N = 1e6 + 10;

int n, k;
int a[N], ant;
signed main() {
	int T = read();
	while(T--) {
		n = read();
		ant = 0;
		int last = -1, now, cnt = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%1d", &now);
			if(last != now) {
				if(i != 1) a[++ant] = cnt;
				last = now;
				cnt = 1;
			} else ++cnt;
		}
		a[++ant] = cnt;
		int ans = 0, ans2 = 0;
		int l = 1;
		for(int i = 1; i <= ant; ++i) {
			if(i < l) continue;
			if(a[i] != 1) {
				while(a[i] > 1 && l < i) {
					if(a[l] == 0) {
						++l;
						continue;
					}
					a[i]--;
					a[l] = 0;
					++ans;
					++l;
				}
				if(l == i) if(a[i] != 1) a[i] = 0, ++ans;
			}
		}
		for(int i = 1; i <= ant; ++i) if(a[i] == 1) ++ans2;
		printf("%d\n", ans + (ans2 + 1) / 2);
	}
	return 0;
}
```

---

## 作者：luan341502 (赞：1)

降智了，vp 时一时没想出做法。

对于整个字符串，显然有用的信息是每个连续数字串的长度，因此我们对串长进行统计。

然后可以发现，若先删除单个字符，即前后都是不相同字符，这样肯定是不优的，因为会导致前后串合并，使结果变劣。

因此我们先删除连续串中长度大于 $1$ 的字符，先删除前面连续串的字符比先删后面字符要优，因为显然是前面的连续串更有可能因为删除前缀连续串被删掉。

直接模拟即可，时间复杂度为 $O(cnt^2)$，其中 $cnt$ 为连续串的数目。

实际上无法达到这个复杂度，因为每次操作删除完前面的串长大于 $1$ 的连续串中的一个字符后就可以退出循环，而且若整个串中找不到这样的连续串，即为 $010101\dots$ 这样的形式，也可以直接统计答案并退出。

```cpp
#include<bits/stdc++.h>
using namespace std;
int tt;
int n;
char str[200005];
int cnt=0,sum[200005];
void solve(){
	cin>>n>>(str+1);
	for(int i=1;i<=cnt;i++) sum[i]=0;
	cnt=0;
	for(int i=1;i<=n;i++){
		if(str[i]!=str[i-1]) sum[++cnt]=1;
		else sum[cnt]++;
	}
	int ans=0;
	for(int i=1;i<=cnt;i++){
		int f=0;
		for(int j=i;j<=cnt;j++){
			if(sum[j]>1){
				sum[j]--;
				ans++;
				f=1;
				break;
			}
		}
		if(!f){
			ans+=ceil((cnt-i+1)/2.0);
			break;
		}
	}
	cout<<ans<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>tt;while(tt--) solve();
	return 0;
}
```


---

## 作者：tongyf (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1430D)

思路：

首先把01串划分为若干数字相等的连续段。

然后发现每一次最靠前的连续段肯定被消掉。如果最前面的一段长度超过了2，那么第一步肯定选最前面一段的，因为不会影响后面，答案不会变劣。

如果最前面的一段长度等于1，那么如果第一步还选前面1段的话，那么有可能第二步会删除很长的一段，答案可能变劣。那么考虑删后面的。如果删长度等于1的，那么会导致两侧的两段融合为1段，答案变劣。

所以当最前面一段长度等于1的时候应该从后面长度大于2的地方删。

如果在后面找不到这样的段那么答案显然再加上剩余段数除以2上取整。

重点就是如果后面有很多段长度大于1，那么找哪一段？

**找尽量靠前的段。**

下面简单证明一下，如果有不严谨的地方还感谢各位神犇指出。

![B0KZHs.png](https://s1.ax1x.com/2020/11/01/B0KZHs.png)

如图，前面有$c$个长为1的连续段，后面有两个长为$a$和$b$的连续段。

当$a=b$时：

若$c<a-1$，先消去哪段都一样。

当$a-1 \leq c < a+b-2$的时候，如果先消$a$，那么$a$,$b$变为$1$,$b$，但如果先消$b$，那么变为$a$,$1$，到了要消去$a$这一段的时候一定是消掉$a$这一段，留下$b$这一段。先消去$a$则留下的$b$的长度更大，答案肯定更优。

当$c \geq a+b-2$的时候，先消去哪段都一样。

当$a<b$时：

当$c<a-1$时，先消去哪段都一样。

当$a-1 \leq c < a+b-2$时，如果先消$a$，那么$a$,$b$变为$1$,$b-(c-a+1)$，如果先消$b$，那么$a$,$b$变为$a$,$b-c$，无论如何$b$那一段长度都大于等于1，那么怎么选都一样。

当$c \geq a+b-2$的时候，先消去哪段都一样。

当$a>b$时：

当$c<b-1$时，先消去哪段都一样。

当$b-1 \leq c < a+b-2$时，如果先消$a$，那么$a$,$b$变为$a-c$,$b$，如果先消$b$，那么$a$,$b$变为$a-(c-b+1)$,$1$,先消$a$则$b$那一段长度大于1，答案更优

当$c \geq a+b-2$的时候，先消去哪段都一样。

为什么所有情况下让$b$段留下的尽量长更优？因为$a$段要么长度大于2，不借助$b$消掉，要么借助$b$消掉，消完$a$之后$b$一定会留下。留下$b$之后如果$b$的长度大于等于2，那么消掉他对后面没有影响，答案更优。

综上所述，先消$a$更优。推广到更多段长度大于等于2的情况也可以类似地证明。

---

时间复杂度$O(nt)$

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,siz[300005],tot,sum;
char s[300005];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		memset(siz,0,sizeof(siz));
		tot=0,sum=0;
		int temp=1;
		scanf("%s",s+1);
		for(int i=2;i<=n;i++){
			if(s[i]!=s[i-1]){
				siz[++tot]=temp;
				temp=1;
			}
			else temp++;
		}
		siz[++tot]=temp;
		int pos=1,flag=0;
		for(int i=1;i<=tot;i++){
			while(pos<=tot&&siz[pos]==1) pos++;
			siz[pos]--;
			if(pos>tot){
				int ans=i-1+(tot-i+2)/2;
				printf("%d\n",ans);
				flag=1;
				break;
			}
			if(pos<=i) pos=i+1;
		}
		if(!flag) printf("%d\n",tot);
	}
	return 0;
}
```

---

## 作者：Theophania (赞：0)

先统计每一个连续相同段的长度，然后从左往右扫一遍，容易发现无论如何当前最左边的连续段都是要被删除的。因此我们的最优选择如下：

- 如果左边第一段长度 $\ge 2$，第一类操作删去当前段中的一个元素，第二类操作删除当前段。

- 如果左边第一段长度 $=1$，寻找之后的连续段中是否存在长度 $\gt 2$ 的，如果有，第一类操作从找到的段中删除，第二类操作删除当前段；如果没有，只好第一类操作删除下一个元素，第二类操作删除当前段。

可以用两个 `set` 来模拟上面的策略，第一个保存所有的连续段，第二个保存长度 $\gt 2$ 的连续段，每次操作后修改。具体实现见代码。


```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;

template <typename T>
inline void read(T &x)
{
    T data = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        data = (data << 3) + (data << 1) + ch - '0';
        ch = getchar();
    }
    x = f * data;
}
template <typename T, typename... Args>
inline void read(T &t, Args &... args)
{
    read(t);
    read(args...);
}
const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int maxn = 2e5 + 9;
int a[maxn];
struct node
{
    int l;
    mutable int r, len; // 需要在set中修改长度
    node() {}
    node(int a, int b, int c) : l(a), r(b), len(c) {}
    bool operator<(const node &b) const
    {
        return l < b.l;
    }
};

set<node> st, st2;
signed main()
{
    int T;
    read(T);
    a[0] = -1;
    while (T--)
    {
        int n;
        read(n);
        st.clear();
        st2.clear();
        for (int i = 1; i <= n; ++i)
            scanf("%1d", &a[i]);
        int pos = 1, ans = 0;
        a[n + 1] = -1;
        for (int i = 2; i <= n + 1; ++i)
        {
            if (a[i] != a[i - 1])
            {
                st.insert(node(pos, i - 1, i - pos));
                if (i - pos > 2)
                    st2.insert(node(pos, i - 1, i - pos));
                pos = i;
            }
        }
        while (!st.empty())
        {
            node x = *st.begin();
            st.erase(x);
            ans++;
            if (x.len < 2)
            {
                node y = *st2.upper_bound(x);
                auto it = st2.upper_bound(x);
                if (it != st2.end()) // 找得到
                {
                    it->len--;
                    st.find(y)->len--;
                    if (it->len < 3)
                        st2.erase(it);
                }
                else // 找不到
                {
                    if (!st.empty())
                    {
                        auto it2 = st.begin();
                        if (it2->len == 1)
                            st.erase(st.begin());
                        else
                            it2->len--;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
```
虽然复杂度没有 $O(n)$ 这么优秀，但跑的还是挺快的，并且也非常好写。

---

## 作者：mot1ve (赞：0)

由于每次操作之后会删除一个前缀，我们要最大化操作次数，也就是构造出一个  $010101$ 序列，这样可以使每次删除前缀的时候只删除一个字符。贪心，每次从头开始找，删长度大于 $1$ 的同 $0$ 或同 $1$ 的子序列中的一个字符（下面称之为块）。但这样显然是 $O(n^2)$ 的。如何优化呢？可以考虑用一个数组存下每个块的长度，维护一个指针，使其指向第一个长度大于 $1$ 的块就行了。如果指针越界了，说明后面的全是 $010101$ 交替的序列，显然答案是 $(idx-i+1+1)/2 $ ，注意这里又加了一个1是因为要向上取整。然后再加上之前的答案，也就是 $i-1$ 。 注意，如果题目给的序列中全是大于 $2$ 的块，那么 $p$ 指针是不会越界的，答案没法被统计，但其实这种情况很简单，答案就是 $idx$ 。一定不要忘特判这个地方！！！

```
#include<bits/stdc++.h>
using namespace std;
int n,idx,T,ans,pre;
string s;
int siz[1000010];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		cin>>s;
		pre=0,idx=0,ans=0;
		for(int i=1;i<s.size();i++)
		{
			if(s[i]!=s[i-1])
			{
				siz[++idx]=i-pre;
				pre=i;
			}
		}
		siz[++idx]=n-pre;
		//所有块分好了
		int p=1,flag=0;//维护一个指针 
		for(int i=1;i<=idx;i++)
		{
			while(p<=idx&&siz[p]==1)
			p++;
			siz[p]--;
			if(p>idx)
			{
				ans=i-1+(idx-i+1+1)/2;
				flag=1;
				break;
			}
			if(p<=i)
			p=i+1;
		} 
		if(flag==0)
		cout<<idx<<endl;
		else cout<<ans<<endl;
	}
	return 0;
}
```

---

