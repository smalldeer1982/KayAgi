# Common Prefixes

## 题目描述

The length of the longest common prefix of two strings $ s = s_1 s_2 \ldots s_n $ and $ t       = t_1 t_2 \ldots t_m $ is defined as the maximum integer $ k $ ( $ 0 \le k \le min(n,m) $ ) such that $ s_1 s_2 \ldots s_k $ equals $ t_1 t_2 \ldots t_k $ .

Koa the Koala initially has $ n+1 $ strings $ s_1, s_2, \dots, s_{n+1} $ .

For each $ i $ ( $ 1 \le i \le n $ ) she calculated $ a_i $ — the length of the longest common prefix of $ s_i $ and $ s_{i+1} $ .

Several days later Koa found these numbers, but she couldn't remember the strings.

So Koa would like to find some strings $ s_1, s_2, \dots,       s_{n+1} $ which would have generated numbers $ a_1, a_2, \dots,       a_n $ . Can you help her?

If there are many answers print any. We can show that answer always exists for the given constraints.

## 说明/提示

In the $ 1 $ -st test case one of the possible answers is $ s =       [aeren, ari, arousal, around, ari] $ .

Lengths of longest common prefixes are:

- Between $ \color{red}{a}eren $ and $ \color{red}{a}ri $ $ \rightarrow 1 $
- Between $ \color{red}{ar}i $ and $ \color{red}{ar}ousal $ $ \rightarrow 2 $
- Between $ \color{red}{arou}sal $ and $ \color{red}{arou}nd $ $ \rightarrow 4 $
- Between $ \color{red}{ar}ound $ and $ \color{red}{ar}i $ $ \rightarrow 2 $

## 样例 #1

### 输入

```
4
4
1 2 4 2
2
5 3
3
1 3 1
3
0 0 0```

### 输出

```
aeren
ari
arousal
around
ari
monogon
monogamy
monthly
kevinvu
kuroni
kurioni
korone
anton
loves
adhoc
problems```

# 题解

## 作者：SpeedStar (赞：5)

#### 算法分析

先初始化字符串$s$，即在位置$0 \sim 99$上置为 $'a'$ ，把这个字符串作为$s[0]$输出即可，然后遍历$lcp$数组里的每个元素$x$，判断$s[x]$是否为$'a'$，若是，则把$s[x]$置为$'b'$，否则置为$'a'$即可，并输出该字符串。

#### C++ 代码

```cpp
#include <iostream>

using namespace std;

int main() {
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		string s(100, 'a');
		cout << s << '\n';
		for (int i = 0, x; i < n; ++i) {
			cin >> x;
			if (s[x] == 'a') s[x] = 'b';
			else s[x] = 'a';
			cout << s << '\n';
		}
	}
	
	return 0;
}
```


---

## 作者：Ninelife_Cat (赞：2)

构造题反正有spj所以~~乱搞~~就完事了。

一时想不出什么好的构造方法于是直接上随机数。

思路就是先随机一个字符串出来，然后只要保证下一个字符串的前 $a_i$ 个字符与当前字符串相等，另外的随便再造几个字符就行。

~~马蜂可能有点诡异~~

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define ri register
#define int long long
#define inf 2147483647
#define mp(x,y) make_pair((x),(y))
#define reset(x,y) memset((x),(y),sizeof((x)))
using namespace std;
inline int read()
{
	int x=0;bool f=false;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=true;c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^'0');c=getchar();}
	return f?-x:x;
}
int t,n,a[201];
char b[201],c[201];
signed main()
{
	srand(time(0));//注入灵魂
	t=read();
	while(t--)
	{
		reset(b,0);reset(c,0);n=read();
		for(ri int i=1;i<=n;++i)
			a[i]=read();
		ri int x=rand()%100+100; 
		for(ri int i=1;i<=x;++i)
			b[i]=char(rand()%26+'a'),cout<<b[i];
      		//生成一个长度为100~199的字符串,+100是防止长度不够 
		cout<<endl;
		for(ri int i=1;i<=n;++i)
		{
			for(ri int j=1;j<=a[i];++j)
				c[j]=b[j],cout<<c[j];
         		//保证字符串c的前几个字符与字符串b相等
			for(ri int j=1;j<=100;++j)
			{
				c[j+a[i]]=char(rand()%26+'a');
				while(c[j+a[i]]==b[j+a[i]]) c[j+a[i]]=char(rand()%26+'a');
				cout<<c[j+a[i]];
			}
            		//再随机生成几个字符
			cout<<endl;
			memcpy(b,c,sizeof(c));
            		//将字符串c复制给字符串b,进行下一轮乱搞
		}
	}
	return 0;
}

---

## 作者：Miraik (赞：1)

CF div2A。 还是一个比较简单的题。

为了思维简单，我们先求出$r=\max(a_{i})$，再构造出$n$个长度为$r$的字符串即可。

题目中写：$a_{i}$表示$s_{i}$和$s_{i+1}$的前$a_{i}$个字符相同

所以我们只需要让$s_{i+1}$的前$a_{i}$个字符相同即可。

具体代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int t,n,r,a[105];
char s[105][55];
inline int _max(int x,int y){return x>y?x:y;}
int main(){
	t=read();
	while(t--){
		n=read(),r=0;//r表示max{a[i]} 
		for(int i=1;i<=n;i++)a[i]=read(),r=_max(r,a[i]);
		for(int i=0;i<=r;i++)s[1][i]='a';//先构造s[1] 
		for(int i=2;i<=n+1;i++){//构造s[2]到s[n+1] 
		    for(int j=0;j<a[i-1];j++)//前a[i-1]个字符相等 
		        s[i][j]=s[i-1][j];
		    for(int j=a[i-1];j<=r;j++)//后面的变为s[i-1]的下一个字符即可 
		        if(s[i-1][j]=='z')s[i][j]='a';
		        else s[i][j]=s[i-1][j]+1;
		}
		for(int i=1;i<=n+1;i++,putchar('\n'))//输出 
		    for(int j=0;j<=r;j++)
		        putchar(s[i][j]);//注意不要直接puts(s[i])！！！因为每个字符串未清空，直接puts可能会输出之前的数据构造的字符！ 
	}
	return 0;
}

```


---

## 作者：CodingOIer (赞：0)

## CF1384A Common Prefixes 题解

## 思路分析

有 SPJ 当然随便瞎搞啊~

我们可以先生成一个字符串，然后直接输出。接着输入一个 $x$，便是题目中的 $A_i$，接着按照以下规则进行输出：

- 对于从 $1$ 到 $x$ 的部分，直接原样输出。
- 对于从 $x + 1$ 到 $50$ 的部分，将其改为任意一个其他字符后输出。

为什么是 $50$ 呢？因为题目中的 $A_i$ 最大为 $50$，所以只需要 $50$ 即可。

## 代码实现

为洛谷打广告~

```cpp
#include <cstdio>
#include <cstring>
const int MaxN = 1e3 + 5;
int t;
int n;
int x;
char s[MaxN];
char base[MaxN] = {"luoguluoguluoguluoguluoguluoguluoguluoguluoguluogu"};
char not_same(const char c)
{
    return 'a' + (c - 'a' + 1) % 26;
}
void solve()
{
    scanf("%d", &n);
    memcpy(s, base, sizeof(s));
    printf("%s\n", s);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        for (int i = 0; i < x; i++)
        {
            printf("%c", s[i]);
        }
        for (int i = x; i < 50; i++)
        {
            s[i] = not_same(s[i]);
            printf("%c", s[i]);
        }
        printf("\n");
    }
}
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

轻松通过。

---

## 作者：chlchl (赞：0)

## 题意简述
给定 $n$ 个数 $a_i$，要求构造 $n+1$ 个字符串，使得第 $i$ 个和第 $i+1$ 个字符串的最长公共前缀长度为 $a_i$,$\ i\in \lbrack1,n\rbrack$。

## 做法
由于本题是 spj，所以直接乱搞。

随机生成一个长度为 $200$ 的字符串（其实 $100$ 以上就够了，为了方便而已）。

接着，对于待生成的第 $i$ 个字符串，因为前一个字符串是确定的，所以其前 $a_{i-1}$ 位是确定的。至于后面的位置，直接随机生成即可。

有几个地方是要注意的：
- 大可不必开数组，两个字符串轮流替换即可。
- 如果使用 ``string``，注意是不能出现 ``s[i] = c`` 这类语句的（其中 $s$ 是 ``string`` 类型的，$c$ 是 ``char`` 类型的）。如果你需要删除末尾字符，可以使用 ``pop_back()``。
- 注意，生成的是 $n+1$ 个字符串。
- 字符串长度不能太短，这样你就没有足够的长度匹配最长公共前缀了。
- 如果你随机生成到的字符与上一个刚好相同，是不行的（这样长度会增加），要重新生成（体现在 $22$、$23$ 行）。
- 最后别忘了复制，否则你的 $t$ 全都是根据第一个字符串生成的。 


## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100 + 10;
int T, n, a[N];
string s, t;

int main(){
	srand(time(NULL));//用时间作为种子随机化 
	scanf("%d", &T);
	while(T--){
		s = "";
		scanf("%d", &n);
		for(int i=1;i<=n;i++)	scanf("%d", &a[i]);
		for(int i=0;i<200;i++)	s += char('a' + rand() % 26);//随机生成字符串 
		cout << s << endl;
		for(int i=2;i<=n+1;i++){
			t = "";//初始化 
			for(int j=0;j<a[i-1];j++)	t += s[j];//前a[i-1]个字符相同 
			for(int j=a[i-1];j<200;j++){
				t += char('a' + rand() % 26);
				while(s[j] == t[j])	t.pop_back(), t += char('a' + rand() % 26);//第22行
				//第23行 
			}
			cout << t << endl;
			s = t;
		}
	}
	return 0;
} 
```


---

## 作者：帝千秋丶梦尘 (赞：0)

[小哥哥小姐姐们先看题目](https://www.luogu.com.cn/problem/CF1384A)

作为%你赛第一题，这题贼水（我不会告诉你这题我爆0了

注意事项：仔细一点

我的大致思路：先构造字符串，然后直接找到那个需要通过A[i]改变的字母，

然后改掉就好了，我用的是++，但是如果是z就要特判了。

so，up代码：


```
#include<bits/stdc++.h>
#define ri register//纯属习惯
using namespace std;
int t,n,a[101];
string s;
int main(void)
{
	scanf("%d",&t);//切记多组数据
	while(t--)
	{
		s="wtdyydswtdaknoikcmyydskcmakioiandcspwtdyydswtdaknoi";
		scanf("%d",&n);
		a[0]=-1;
		cout<<s<<endl;//直接输出第一串
		for(ri int i(1);i<=n;++i)
		{
			scanf("%d",&a[i]);
			s[a[i]]++;
			if(s[a[i]]>'z') s[a[i]]='a';
			cout<<s<<endl;//改变后，第二串
		}
	}
	return 0;//好习惯
}
```
# 各位看官走好，掰掰QwQ

---

## 作者：syf2008 (赞：0)

这是一道~~毒瘤~~题，题目输入字符串公共前缀长度，要我们输出这样的字符串，当然，字符串是可以自己构造的

上代码
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	int t,n,a[105];
	cin>>t;
	while(t--)
	{
	s="akioiwtdakioiwtdakioiwtdakioiwtdakioiwtdakioiwtdakioi";//自己构造
	cin>>n;
	cout<<s<<endl;//先输出原字符串
	for(int i=1;i<=n;i++)
	{
	cin>>a[i];
	s[a[i]]+=1;//把公共前缀长度后的字符改掉
	if(s[a[i]]>'z')//过z就回到a
	s[a[i]]='a';
	cout<<s<<endl;//输出
	}
	}
	return 0;
}
```

---

## 作者：B_1168 (赞：0)

题目链接：[CF1384A](https://www.luogu.com.cn/problem/CF1384A)

本次比赛大型毒瘤现场，B题难度爆炸……

留意到$a_1,a_2,a_3,\dots,a_n\leq50$，我们不妨令我们的第一个字符串是`aaa...a(60个a)`。

如果第一个字符串是60个连续的`a`，我们如何让第二个字符串**有且只有前$a_1$个字符**和第一个相同呢？

显然，第二个字符串前$a_1$个字符应当是`a`；至于第$a_1+1$到第$60$个字符，则可以是其他任何不是`a`的东西。我们可以维护**上一个输出的字符串**原本，然后用类似维吉尼亚密码的思想，如果上一个输出的字符串对应位置ascii值为$k$，则输出ascii值为$k+1$的字母（如果$k=90$，即字母为`z`，可输出`a`），如此可以构造出保证有且只有前$a_i$个字母一致的字符串。

多说无益，上代码：

```cpp
#include<bits/stdc++.h>
#define maxn 1000
using namespace std;

int t,n,a[maxn];

int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		char s[105];
		for(int i=1;i<=60;i++) s[i]='a';
		for(int i=1;i<=60;i++) printf("%c",s[i]);
		printf("\n");
		for(int i=1;i<=n;i++){
			for(int j=a[i]+1;j<=60;j++){
				s[j]+=1;
				if(s[j]>'z') s[j]='a';
			} 
			for(int j=1;j<=60;j++) printf("%c",s[j]);
			printf("\n");
		}
	}
} 
```


---

## 作者：daniEl_lElE (赞：0)

# 题面描述

有$n+1$个字符串，已知第$i$个和第$i+1$个的公共前缀长度为$a_i$，请问每个字符串分别是多少。你要完成$t$组测试数据。

# 思路

样例给的答案太坑了，每次给奇葩的答案。

这题我们可以假设第$1$个字符串为好多$"a"$，然后一个一个推，第$2$个只需要在第$1$个的基础上保留前$a_1$个字符，把后面的字符$"a"$反转成$"b"$，$"b"$反转成$"a"$，以此类推。

这样，我们就把第一个字符串设置成$"aaaaaaaa...."$共好多$"a"$（大于$50$）。然后一个一个推即可。

# 代码

```

#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int t;//多测
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int a[n+1];
		string s="aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";//第一个串
		for(int i=1;i<=n;i++){
			cin>>a[i];
			cout<<s<<endl;//输出第i个串
			int j=0;
			for(j=a[i];j<s.size();j++){//更新
				if(s[j]=='a'){
					s[j]='b';
				}
				else{
					s[j]='a';
				}
			}
		}
		cout<<s<<endl;//最后一个串
	}

	return 0;
}


```

---

## 作者：Meatherm (赞：0)

考虑构造出足够长的 $s_1$，然后对于每一个 $1 < i \leq n+1$，将 $s_i$ 的前 $a_i$ 位构造得和 $s_{i-1}$ 相同，后 $|s_{i-1}|- a_i$ 位和 $s_{i-1}$ 不同。

**Code**

```cpp
# include <bits/stdc++.h>
# define rr
const int N=110,INF=0x3f3f3f3f;
char s[N];
int n;
int a[N];
char temp[N];
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
int main(void){
	int T=read();
	while(T--){
		n=read();
		for(rr int i=1;i<=n;++i){
			a[i]=read();
		}
		a[n+1]=0;
		for(rr int i=1;i<=100;++i){
			s[i]='a',putchar('a');
		}
		puts("");
		for(rr int i=1;i<=n;++i){
			for(rr int j=1;j<=100;++j){
				if(j<=a[i]){
					temp[j]=s[j];
				}else{
					temp[j]=(s[j]=='z')?('x'):'z';
				}
				putchar(temp[j]);
			}
			puts("");
			for(rr int j=1;j<=100;++j){
				s[j]=temp[j];
			}
		}
	}

	return 0;
}
```

---

