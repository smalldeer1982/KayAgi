# Pocket Book

## 题目描述

One day little Vasya found mom's pocket book. The book had $ n $ names of her friends and unusually enough, each name was exactly $ m $ letters long. Let's number the names from $ 1 $ to $ n $ in the order in which they are written.

As mom wasn't home, Vasya decided to play with names: he chose three integers $ i $ , $ j $ , $ k $ ( $ 1<=i&lt;j<=n $ , $ 1<=k<=m $ ), then he took names number $ i $ and $ j $ and swapped their prefixes of length $ k $ . For example, if we take names "CBDAD" and "AABRD" and swap their prefixes with the length of $ 3 $ , the result will be names "AABAD" and "CBDRD".

You wonder how many different names Vasya can write instead of name number $ 1 $ , if Vasya is allowed to perform any number of the described actions. As Vasya performs each action, he chooses numbers $ i $ , $ j $ , $ k $ independently from the previous moves and his choice is based entirely on his will. The sought number can be very large, so you should only find it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample Vasya can get the following names in the position number $ 1 $ : "AAB", "AAA", "BAA" and "BAB".

## 样例 #1

### 输入

```
2 3
AAB
BAA
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 5
ABABA
BCGDG
AAAAA
YABSA
```

### 输出

```
216
```

# 题解

## 作者：莫奈的崖径 (赞：5)

qwq一开始感觉这道题不可做，~~后来看懂了发现挺水的~~......


------------
## 题意
有n个长度为m的字符串，按照1~n对它们进行编号，现在对它们进行一个操作：将任意两个字符串长度为k的字符前缀进行交换，问最终编号为1的字符串将产生多少种结果，答案可能很大，所以要对1e9+7取模。


------------
## 分析
首先，这是一道组合数学题目（弱弱的我一开始还以为是字典树...）

因为k的取值范围是[1,m]，那么显而易见我们的交换操作会一直到每个字符串的最后一个字符，对于编号为1的那个字符串，它的每一位字符都有很多可能，这里分析一下第二组样例。


这四个字符串的第一位有3个不同的字符:A,B,Y.

![](https://i.loli.net/2019/08/27/arReoBfkX6gNcEh.png)


这四个字符串的第二位有3个不同的字符:B,C,A.

![](https://i.loli.net/2019/08/27/v5qD2EuF9QCi6MW.png)

以此类推，第三位有3个，第四位有4个，第五位有2个。

##### 也就是说，这四个字符串的第i位有xi个不同的字符，那么编号为1的字符串的第i位就有xi种可能。

最后根据乘法原理可得，编号为1的字符串有216种可能。


------------
## AC代码
```cpp
#include<cstdio>
#include<cstring>
#define N 1005
const int mod=1e9+7;
using namespace std;
char s[N][N];
int n,m;
long long ans=1,cnt=0;
bool flag[27];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	scanf("%s",s[i]);
	for(int i=0;i<m;i++)
	{
		memset(flag,false,sizeof(flag));
		cnt=0;
		for(int j=1;j<=n;j++)
		if(!flag[s[j][i]-'A']) flag[s[j][i]-'A']=true,cnt++;//如果在n个字符串的第i位出现了某个字符，就记录下来。 
		ans*=cnt;
		ans%=mod;
	}
	printf("%lld\n",ans);
	return 0;
}
```


------------
原谅我弱弱的表达能力和coding能力啦，感觉只要懂了题意就很好看懂代码，希望能帮到大家qwq。


---

## 作者：封禁用户 (赞：1)

个人感觉题目描述得不清楚，所以有必要简化一下。

***题目大意***

给定 $n$ 行字符串，每行字符串有 $m$ 个字符，每行的每一个字母都能与其他行当前位置的字母交换，求有多少种组合方法。

**浅浅的分析：**

先看样例：

```
AAB
BAA
```

有四种分配方法，``` AAB ``` ```BAB``` ```AAA``` ```BAA``` 这四种。

再举个栗子：

```
ACDFG
DFSGG
WSXHZ
JNTAM
```
有七百六十八种分配方案。不难发现，其实就是每列不同的字母数量相乘，再取余就行了。

这其实是个排列组合。

有 $1$ $3$ $4$ $2$ 这四个数字，求能组成多少个四位数。

第一位：能选四个数。

第二位：能选四个数。

第三位：能选四个数。

第四位：能选四个数。

那么就有 $4^4$ 种方案。

~~（应该能懂了吧）~~

**Code**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define re ra()

const int MOD = 1e9 + 7;

int n, m, ans, s = 1, v[1100];
char a[1001][1001];
inline int ra()
{
	int jjy = 0,txy = 1;
	char ch = getchar();
	while(!isdigit(ch)){if(ch == '-') txy = -1; ch = getchar(); }
	while(isdigit(ch)){jjy = jjy * 10 + ch - '0'; ch = getchar(); }
	
	return jjy * txy;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n = re, m = re;
	for (int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
		 cin >> a[i][j];
	for(int j = 1; j <= m; j ++)
	{
		ans = 0;
		memset(v, 0, sizeof v);
		
		for(int i = 1; i <= n; i ++)
		{
			if(!v[a[i][j] - 'A' + 1]) ans ++;
			v[a[i][j] - 'A' + 1] = 1;
		}
		if(ans == 0) ans = 1;	
		s = (s*ans) % MOD;
	}
	printf ("%lld ", s);
	return 0;
}


```

完结撒花！

---

## 作者：_ZML_ (赞：1)

# 思路
一道简单的排列组合。

把每一列出现的不同的字母数量相乘就行了。

# 代码
```cpp
#include<bits/stdc++.h>
const int M=1000000007;
#define int long long
#mem(x,y) memsset(x,y,sizeof(x))
using namespace std;
char s[1010][1010];
int ued[27];
signed main() {
	int n,m;	
	cin>>n>>m;
	for(int i=1; i<=n; i++) scanf("%s",s[i]);
	int ans=1;
	for(int i=0; i<m; i++) {
		mem(ued,0);
		int cnt=0;
		// 算不同的字母
		for(int j=1; j<=n; j++) if(!ued[s[j][i]-'A']) ued[s[j][i]-'A']=1,cnt++;
		ans=ans*cnt%M;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：qingchenMC (赞：0)

## 思路

发现情况数是每列不同字母个数相乘，别的题解也都提到了。下面来证明一下。

题目中的意思很明确，交换任意两个字符串的任意长度前缀字串为一次操作，求操作最多可以得到多少个不同的字符串。

看样例：

```
AAB
BAA
```

交换长度为 $1,2,3$ 的前缀，共有下面三种结果。

```
BAB  BAB  BAA
AAA  AAA  AAB
      ^
```

注意这个小三角指的这一次操作，他是和第一种情况一样的。

其中不同的只有 $4$ 个。注意到是因为第 $2$ 位上两个字母相同，所以第 $2$ 位交换和不交换都没有意义，而本来交换一位上两个不同字母的情况数就是 $2$ ，因此答案为 $2\times1\times2=4$。

这个答案是怎么算出来的？其实是用了乘法原理，分步枚举交换每一个长度的前缀，看能有多少种不同，再乘起来，即可得到所有的情况数。

而字符串多于两个时也是一样的。不同的字符个数，就是这一位上任意交换后，能产生的情况个数。

所以最终答案为每列不同字母个数相乘。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

const int mod=1e9+7;

string s[102];
bool vis[1145];

int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>s[i];
	}
	long long ans=1;
	for(int i=1;i<=m;i++){
		memset(vis,0,sizeof(vis));
		for(int j=1;j<=n;j++){
			if(!vis[s[j][i-1]-'A']){
				vis[s[j][i-1]-'A']=1;
			}
		}
		int cnt=0;
		for(int k=0;k<=25;k++){
			if(vis[k]){
				cnt++;
			}
		}
		ans*=cnt;ans%=mod;
	}
	cout<<ans;
	return 0;
}
//https://codeforces.com/contest/152/submission/304399376
```

---

## 作者：Phoenix114514 (赞：0)

# CF152C Pocket Book
题目一开始没看懂，在那里弄了半天，前缀互换是什么意思？
## 翻译
给定 $n$ 个长度为 $m$ 的字符串，第 $i$ 个字符串的编号为 $i$，对于任意两个字符串，定义一次操作为可以交换相同位置上的字符。问经过若干次交换后，最多产生了多少中不同的字符串？（答案可能很大，请对 $10^9+7$ 取模后输出）
## 思路
先看样例 1：
```
AAB
BAB
```

答案是 $4$。不难发现答案是每一列不同的字符个数相乘，再取模。

样例 2：

```
ABABA
BCGDG
AAAAA
YABSA
```
第一列有 $3$ 种不同的字符，第二列有 $3$ 种不同的字符，第三列有 $3$ 种不同的字符，第四列有 $4$ 种不同的字符，第五列有 $2$ 种不同的字符。得出答案就是 $216$。

再举个例子：

```
DJFPQ
LKMAH
DNXUH
LETXB
```

$2 \times 4 \times 4 \times 4 \times 3 \bmod 1000000007=384$，也是对的。

由此，我们得出一个结论：若第 $i$ 列有 $a_i (a_i \le 26)$ 种字符，则答案等于：
$$
 \prod_{ i = 1 }^m a_i
$$

如何解释呢？这就是数学中的排列组合，例如：有写着 $4、7、9、5、1$ 这五个数字的若干张卡片，问一共能组成多少个不同的五位数？
因为所有数位都有 $5$ 种数字可选，所以最终答案是 $5^5=3125$ 种。这道题也一样。
## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
string s[1010];
int n,m,ans=1,sum;
bool status[30];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    cin>>n>>m;
    for (int i=0;i<n;i++)cin>>s[i];
    for (int j=0;j<m;j++){
        memset(status,0,sizeof(status));
        sum=0;
        for (int i=0;i<n;i++){
            if (!status[s[i][j]-'A']){
                status[s[i][j]-'A']=true;
                sum++;
            }
        }
        ans=ans*sum;
        ans=ans%mod;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：The_jester_from_Lst (赞：0)

~~题面好抽象，什么前缀互换的~~

简易数学题。

所谓“前缀互换”，通俗地讲，就是与同一列的数互换。为了考虑去重，我们规定互换的字母不能相同。

设我们已经在访问第 $i$ 个字符串，则我们引入 $vis$ 数组表示第 $i$ 个字符串中每个字符的出现次数，$sum$ 数组表示第一列中不同字符的个数。每出现应该新的字符，我们在 $vis$ 数组标记这个字符并让 $sum$ 数组加一。根据排列组合的计算方式，我们最后把所有的 $sum_i$ 相乘即可。注意若有 $sum_i$ 为 $0$ 时应跳过。

个人感觉此题难在题面的理解，代码实现真的很简单。

附上代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
inline int rd(){
	int jya=0,tl=1;char jyt=getchar();
	while(!isdigit(jyt)){if(jyt=='-')tl=-1;jyt=getchar();}
	while(isdigit(jyt)){jya=jya*10+(jyt-'0');jyt=getchar();}
	return jya*tl;
}
inline void wr(int jjy){
	if(jjy<0)putchar('-'),jjy=-jjy;
	if(jjy>9)wr(jjy/10);
	putchar(jjy%10+48);
}
int n,m,vis[10086][123],sum[10086],ans=1;
string s[10086];
signed main(){
	n=rd();m=rd();
	for(int i=1;i<=n;++i){
		cin>>s[i];
		for(int j=0;j<m;++j){
			if(vis[j][s[i][j]]==0)++sum[j];
			++vis[j][s[i][j]];
		}
	}
	for(int i=0;i<m;++i)if(sum[i]>0)ans=ans*(sum[i])%mod;
	wr(ans);
	return 0;
}
```


---

## 作者：smydahaoren (赞：0)

### 解题思路：

经过分析后，题目可以简化成以下形式。

给定 $n$ 个 $m$ 长度的字符串。计算出每个字符串的第 $i$ 个字符总共有 $k_i$ 种。然后通过排列组合，将所有的 $k_i$ 相乘，可以得到集合所包含的最多的元素个数。

AC 代码
-------------
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e9+7;
int n,m,cnt[10009]; 
bool g[10009][26];
char ch;
signed main(){
	//freopen(" ","r",stdin);
	//freopen(" ","w",stdout);
	cin>>n>>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) {
			cin>>ch;
			if(g[j][ch-'A']==0) cnt[j]++;
			g[j][ch-'A']=1;
		}
	}
	long long ans=cnt[0];
	for(int i=1;i<m;i++){
		ans=ans*cnt[i]%N;
	}
	cout<<ans;
	return 0;
}

```


---

