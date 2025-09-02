# Ugu

## 题目描述

A binary string is a string consisting only of the characters 0 and 1. You are given a binary string $ s_1 s_2 \ldots s_n $ . It is necessary to make this string non-decreasing in the least number of operations. In other words, each character should be not less than the previous. In one operation, you can do the following:

- Select an arbitrary index $ 1 \leq i \leq n $ in the string;
- For all $ j \geq i $ , change the value in the $ j $ -th position to the opposite, that is, if $ s_j = 1 $ , then make $ s_j = 0 $ , and vice versa.

What is the minimum number of operations needed to make the string non-decreasing?

## 说明/提示

In the first test case, the string is already non-decreasing.

In the second test case, you can select $ i = 1 $ and then $ s = \mathtt{01} $ .

In the third test case, you can select $ i = 1 $ and get $ s = \mathtt{010} $ , and then select $ i = 2 $ . As a result, we get $ s = \mathtt{001} $ , that is, a non-decreasing string.

In the sixth test case, you can select $ i = 5 $ at the first iteration and get $ s = \mathtt{100001} $ . Then choose $ i = 2 $ , then $ s = \mathtt{111110} $ . Then we select $ i = 1 $ , getting the non-decreasing string $ s = \mathtt{000001} $ .

## 样例 #1

### 输入

```
8
1
1
2
10
3
101
4
1100
5
11001
6
100010
10
0000110000
7
0101010```

### 输出

```
0
1
2
1
2
3
1
5```

# 题解

## 作者：broniazaichek (赞：11)

我们举个例子：$\mathrm{100111100001100}$（虽然说没有 $15$ 位的......）

 那么我们不难发现一个规律：除第一位外的其它的数判断一下有多少个**连续**的 $0$ 或 $1$，就比如说这样$($开头的 $1$ 省略$)$:
 
 $\underline{00}$ $\underline{1111}$ $\underline{0000}$ $\underline{11}$ $\underline{00}$
 
这里有 $5$ 段，那么将它转化为单调不下降序列就需要 $5$ 次操作$\lgroup$ 因为以 $1$ 开头的序列操作**后必定全是** **$1$，不然无法保证不下降**（开头的 $1$ 省略）
 
#### $\underline{00}$ $\underline{1111}$ $\underline{0000}$ $\underline{11}$ $\underline{00}$ $\Rightarrow$ $\underline{11}$ $\underline{0000}$ $\underline{1111}$ $\underline{00}$ $\underline{11}$ $\Rightarrow$ $\underline{11}$ $\underline{1111}$ $\underline{0000}$ $\underline{11}$ $\underline{00}$ $\Rightarrow$ $\underline{11}$ $\underline{1111}$ $\underline{1111}$ $\underline{00}$ $\underline{11}$ $\Rightarrow$ $\underline{11}$ $\underline{1111}$ $\underline{1111}$ $\underline{11}$ $\underline{00}$ $\Rightarrow$ $\underline{11}$ $\underline{1111}$ $\underline{1111}$ $\underline{11}$ $\underline{11}$ 

一个数列有几个连续的 $0$ 或 $1$ 就代表要操作几次，每操作一次即可将整个快翻转，然而以 $0$ 开头的则可以少操作一次，**因为其不需要保证最后一个块为 $1$**


------------

然而以 $0$ 开头的则相反，因为其一定保证不下降，所以最后的一个连通块可以不操作，共 $4$ 次，比如下面的（开头的 $0$ 省略）

#### $\underline{11}$ $\underline{0000}$ $\underline{1111}$ $\underline{00}$ $\underline{11}$  $\Rightarrow$ $\underline{00}$  $\underline{1111}$ $\underline{0000}$ $\underline{11}$ $\underline{00}$  $\Rightarrow$ $\underline{00}$  $\underline{0000}$ $\underline{1111} $ $\underline{00}$ $\underline{11}$  $\Rightarrow$ $\underline{00}$  $\underline{0000}$ $\underline{0000 }$ $\underline{11}$ $\underline{00}$  $\Rightarrow$ $\underline{00}$  $\underline{0000}$ $\underline{0000} $ $\underline{00}$ $\underline{11}$



------------


最后两个特判
 
1.只有一位数的直接输出 $0$
 
2.所有位数都是 $0$ 或 $1$ 的直接输出 $0$


------------


最后贴上代码(码风略丑，不喜勿喷)
```cpp
#include<bits/stdc++.h>
#define int long long
#define M 1000005
using namespace std;
int t,n,b[M],i=1,ans[M];string a;
inline int read()
{
  int x=0,f=1; char ch=getchar();
  while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=getchar();}
  while(ch>='0'&&ch<='9') {x=x*10+ch-48; ch=getchar();}
  return x*f;
}
signed main()
{
  t=read();int u=0;
  for(int j=1;j<=t;j++)
    {
      u++;
      n=read(); cin>>a;
      if(n==1) {ans[u]=0; continue;} //特判，只有一位
      if(a[0]=='1') {int yy=0;
          for(int i=0;i<n;i++) {if(a[i]=='1') yy++;}
          if(yy==n) {ans[u]=0; continue;} }
      if(a[0]=='1') {int yy=0;
          for(int i=0;i<n;i++) {if(a[i]=='1') yy++;}
          if(yy==n) {ans[u]=0; continue;} }//特判，所有的位数相同
      if(a[0]=='1')
        {
          int p_1=0,p_2=0; int ans_1=0,ans_2=0;
          for(int i=0;i<n;i++) if(a[i]=='0') {p_1=i; break;}
          for(int i=p_1+1;i<n;i++) {if(a[i]!=a[i-1]) ans_1++;}//求连通块的数量
          ans_1+=1; ans_2++;//为了保险，把头由1换为0后再求一次以0开头需要操作的次数
          for(int i=0;i<n;i++) {if(a[i]=='0') a[i]='1'; else a[i]='0';}
          for(int i=0;i<n;i++) if(a[i]=='1') {p_2=i; break;}
          for(int i=p_2+1;i<n;i++) {if(a[i]!=a[i-1]) ans_2++;}
          ans[u]=min(ans_1,ans_2); continue; //然后求两者较小值 
        }
      if(a[0]=='0')
        {
          int p_1=0,p_2=0; int ans_1=0,ans_2=0;
          for(int i=0;i<n;i++) if(a[i]=='1') {p_1=i; break;}
          for(int i=p_1+1;i<n;i++) {if(a[i]!=a[i-1]) ans_1++;}
          ans_1+=1; ans_2++;
          for(int i=0;i<n;i++) {if(a[i]=='0') a[i]='1'; else a[i]='0';}
          for(int i=0;i<n;i++) if(a[i]=='0') {p_2=i; break;}
          for(int i=p_2+1;i<n;i++) {if(a[i]!=a[i-1]) ans_2++;}
          ans[u]=min(ans_1-1,ans_2-1); continue;
        }//同上
    }
  for(int i=1;i<=t;i++)
    cout<<ans[i]<<endl;//输出，完美结束
  return 0;
}

```

---

## 作者：Fido_Puppy (赞：7)

$$\texttt{Foreword}$$

只有我写的 $\text{DP}$ 吗？

$$\texttt{Description}$$

[Ugu](https://www.luogu.com.cn/problem/CF1732B)

$$\texttt{Solution}$$

楼上说思路很简单，所以就我没想到。

考虑 $\text{DP}$，发现使这个序列单调不将，必定是前面若干个 $0$ 加上后面若干个 $1$。

注意到每次是后缀翻转，所以我们可以从前往后枚举，设 $f_{i, 0/1, 0/1}$ 表示当前枚举到第 $i$ 位，当前这位填 $0/1$，当前是否 $(1/0)$ 翻转所需的最小翻转次数。

然后转移就很简单了，具体可以看一下代码。

$$\texttt{Code}$$

```cpp
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define lep(i, a, b) for (int i = (a); i >= (b); --i)
#define ln putchar('\n')
#define sp putchar(' ')

inline char gc() {
	static char buf[1000000], *p1 = buf, *p2 = buf;
	return p1 == p2 and (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++; 
}
template <class I> void read(I &x) {
	x = 0; int f = 1; char c = gc();
	for (; c < '0' or c > '9'; c = gc()) if (c == '-') f = -1;
	for (; c >= '0' and c <= '9'; c = gc()) x = x * 10 + c - '0';
	x *= f;
}
template <class I> void write(I x) {
	static int sta[50], top = 0;
	if (x < 0) putchar('-'), x = -x;
	do {
		sta[ ++top ] = x % 10; x /= 10;
	} while (x);
	while (top) putchar(sta[ top-- ] + '0'); 
}
const int maxn = 1e5 + 5;
const int inf = 0x3f3f3f3f;
int t, n, f[maxn][2][2];
char s[maxn], *p;
void solve() {
	read(n); p = s; char c = gc(); for (; c != '0' and c != '1'; c = gc());
	for (; c == '0' or c == '1'; c = gc()) *(++p) = c;
	f[0][0][1] = f[0][1][1] = inf; f[0][0][0] = f[0][1][0] = 0;
	rep(i, 1, n) {
		if (s[i] == '0') {
			f[i][0][0] = std :: min(f[ i - 1 ][0][0], f[ i - 1 ][0][1] + 1);
			f[i][0][1] = inf;
			f[i][1][0] = inf;
			f[i][1][1] = std :: min({f[ i - 1 ][1][0] + 1, f[ i - 1 ][0][0] + 1, f[ i - 1 ][0][1], f[ i - 1 ][1][1]});
		}
		else {
			f[i][0][0] = inf;
			f[i][0][1] = std :: min(f[ i - 1 ][0][1], f[ i - 1 ][0][0] + 1);
			f[i][1][0] = std :: min({f[ i - 1 ][0][0], f[ i - 1 ][1][0], f[ i - 1 ][1][1] + 1, f[ i - 1 ][0][1] + 1});
			f[i][1][1] = inf;
		}
	}
	write(std :: min({f[n][0][0], f[n][0][1], f[n][1][0], f[n][1][1]}));
	ln;
}
int main() {
	read(t);
	while (t--) solve();
	return 0;
}
```


$$\texttt{Thanks for watching!}$$

---

## 作者：ljk654321 (赞：4)

思路：

因为一次修改会翻转整个后缀，会导致后面的数会受影响，并且如果前面的数不满足条件，后面的数一定不满足，所以考虑从前往后处理。

因为要从前往后处理，所以就要判断字符串开头是什么，满足两者不相等就可以了

详见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
char s[114514];//定义字符数组
int main()
{
    cin>>t;//输入
    while(t--)
    {
        cin>>n>>s;
		int ans=0;//清零
        for(int i=1; i<n; i++)//遍历
            ans+=(int)s[i-1]^(int)s[i];
        printf("%d\n",std::max(ans-49+(int)s[0],0));//只有一段数字且为0时没有第二段，直接输出0即可。进行比较，如果小于等于0直接输出
    }
    return 0;//结束
}

```


---

## 作者：lrqlrq250 (赞：2)

感觉现有题解看上去都好奇怪？

## 解题思路
首先给出一个引理：

- 连续的若干个相同的 $0$ 或 $1$ 与一个 $0$ 或 $1$ 是等价的，换言之，在给一个后缀取反时，取若干段连续的 $0$ 或 $1$ **一定不会比其他方式更劣**。

证明是比较显然的，这里就省略了。

所以我们只需要考虑将原序列中连续相同的数**缩**成一个数，而此时（可以证明）新序列一定是零一交替的形式，形如：
$$01010101\dots$$
或者：
$$10101010\dots$$

要想取反使得原序列单调不减，和让新序列单调不减也是等价的，也就是让序列变成：
$$00000\dots011111\dots1$$

为了达成这样的形式，不难看出，设我们的新序列总共有 $k$ 个 $0/1$，那么：

- 若原/新序列以 $0$ 开头，则从第二段开始到倒数第二段每一段都需要取一次反，一共 $k - 2$ 次（最后一段是什么不重要，不需要取反）

- 若原/新序列以 $1$ 开头，则第一段也需要取一次反，一共 $k - 1$ 次

同样根据这样的操作方式我们可以发现，操作完后只有最后一段连续 $0/1$ 可能是 $1$，而前面一定全为 $0$。

统计新序列的 $k$ 只需要统计有多少个相邻的 $s_i, s_{i+1}$ 满足两者不相等就可以了。这样统计出来是 $k - 1$，计算也差不多。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100005];


int main(){
	int t;
	scanf("%d", &t);
	while (t--){
		scanf("%d", &n);
		for (int i=1; i<=n; i++) scanf("%1d", &a[i]);
		int num = 0;
		for (int i=1; i<n; i++) if (a[i] != a[i + 1]) num++;
		if (a[1] == 1) printf("%d\n", num);//因为统计出来num就是k-1，所以这里就不需要再减一了
		else{
			if (!num) printf("0\n");//要特判本来就满足整个序列全0或全1的情况，不然输出-1
			else printf("%d\n", num - 1);
		}
	}
	return 0;
}

```


---

## 作者：UniGravity (赞：0)

## Solution CF1732B Ugu
[题目传送门](https://www.luogu.com.cn/problem/CF1732B)   
[博客食用风味更佳](https://www.luogu.com.cn/blog/ansmod998244353/)

### 题意简述
对于一个只有 $0$ 和 $1$ 的序列，定义一次操作是选择一个后缀并把这个后缀的所有元素取反，求最少使用多少次操作可以让这个序列单调不降。

### 题目分析
可以发现，由于序列只有 $0$ 和 $1$，序列单调不降也就是将数列分为两部分，使得数列的前部均为 $0$，后部均为 $1$。  

分析题目，我们发现连续的 $0$ 和 $1$ 对题目没有影响（可以证明从中间断开序列一定劣于对整个序列进行取反），我们可以忽略它们，就能得到这样一个序列：
$$0\space1\space0\space1\space0\space1\space\dots$$
或是：
$$1\space0\space1\space0\space1\space0\space\dots$$

写出序列的开头几项：$0,1,01,10,010,101\dots$    

为简单起见，记开头为 $a$，长度为 $s$ 的**化简后**序列为 $S(a,s)$，最小操作数为 $f_{a,s}$。

可以发现，对于序列 $S(0,s)$，我们**忽略它的开头** $0$，那么它与序列 $S(1,s-1)$ 相同，$f_{0,s}=f_{1,s-1}$。    
同理，对于序列 $S(1,s)$，我们只需对它**进行全部取反**，它就与序列 $S(0,s)$ 相同，$f_{1,s}=f_{0,s}+1$。

发现 $n\le10^5$，我们预处理进行 dp，询问时直接调取即可。

时间复杂度 $O(n+t)$。

### 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int T, n;
char s[100005];

int f[2][100005]; // i表示s第一位，j表示s长度

int main() {
    // dp初始状态
    f[0][1] = f[1][1] = 0;
    for (int i = 2; i <= 100005; i++) {
        f[0][i] = f[1][i - 1];
        f[1][i] = f[0][i] + 1;
    }
    
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        scanf("%s", s + 1);
        int cnt = 1; // 统计化简后s的长度
        for (int i = 2; i <= n; i++) {
            if (s[i] != s[i - 1]) cnt++;
        }
        
        // 判断0/1
        if (s[1] == '0') printf("%d\n", f[0][cnt]);
        else printf("%d\n", f[1][cnt]);
    }
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/119547597)

完结散花！

---

## 作者：cff_0102 (赞：0)

考虑下面这个字符串：`010000100011011111001`（$542457$ 的二进制表示）。首先开头的 $0$ 不用考虑。接下来：

- 第二个字符出现不同，最优策略当然是修改这个字符（和后面的字符），字符串变为 `001111011100100000110`。
- 第三个字符又变了，采取一样的策略，把字符串改为 `000000100011011111001`。
- 第七个字符再次变了，采取同样的策略，后面的也以此类推。
- 现字符串为 `000000000000000000110`，需要修改倒数第三个字符，字符串变为 `000000000000000000001`。
- 发现最后一个字符又变成 `1` 了，接着再次改变这个 `1`，让它变成 `0`。

现在这个字符串都是 $0$ 了。现在修改了 $x-1$ 次，其中 $x$ 就是字符串的块数。但是修改最后一块是没有必要的，所以再减去 $1$。答案就是 $x-2$。

要是原来的串以 $1$ 开头呢？

看一下这个串：`1100111111110000000100000010`（`0xcff0102`），首先把字符串操作一次变为 `0011000000001111111011111101` 后，就和前面一样了。所以，答案是 $x-1$。

那么，只需要判断字符串开头是什么，再判断字符串的块数就能得到答案。怎么得到块数？就看看有几个字符串和前面的不一样，最后遍历下来就得到了 $x-1$ 的值。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int n;cin>>n;
		string a;cin>>a;
		int x=0;
		for(int i=1;i<n;i++)if(a[i]!=a[i-1])x++;
        //现在得到了 (x-1) 的值
        if(x==0)cout<<0<<endl;//都是0的话说明不需要变，但是如果直接执行下面一句会变成-1，所以要特判
		else cout<<x-(1-(a[0]-48))<<endl;/*是0就再减一，否则就是1，不需要再减了*/
	}
	return 0;
}
```


---

## 作者：alm_crax (赞：0)

### [洛谷原题传送门](https://www.luogu.com.cn/problem/CF1732B)

### [CF原题传送门](https://codeforces.com/problemset/problem/1732/B)

## 思路
题目要让序列 $s$ 单调不减，因序列只包含 $0$ 和 $1$，所以不难发现操作主要取决于 $1$。

由于操作更改的是序列的后缀，那么更改第一个肯定不是最优的，如此，就要以第一个数字作为后面的序列的操作的基准。

再进一步，把连续的相同数字定为一段，可以发现，每一次操作的左端点 $l$ 在最优情况下一定满足 $s_{l-1} \neq s_l$，举个简单的例子：

$1100$ 若操作为 $\underline{1}$ $\underline{100}\Rightarrow\underline{1}$ $\underline{011}$ 还需多次才能达到最终状态。

$1100$ 若操作为 $\underline{11}$ $\underline{00}\Rightarrow\underline{11}$ $\underline{11}$ 则只需要 $1$ 次。

将序列按相同数字分成 $k$ 段，此时有两种情况：

-  第一段数字为 $1$。

-  第一段数字为 $0$。

为 $1$ 需要 $k-1$ 次操作，因为每一次操作可以更改一段，只需更改除第一段外的后 $k-1$ 段。

为 $0$ 需要 $k-2$ 次操作，因为第二段为 $1$，不需要更改，跟为 $1$ 时差不多。

特殊的情况，只有一段数字且为 $0$ 时没有第二段，直接输出 $0$ 即可。

注：代码有简化的地方，看起来会跟思路不一样（实际效果跟思路一样）。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s;
char a[100005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%s",&n,&a);
		s=a[0]-'0';//第一段为1时比为0时多操作一次
		for(int i=1;i<n;i++)//要去掉第一段，所以从1开始
		{
			if(a[i]!=a[i-1])//求段数
			{
				s++;
			}
		}
		printf("%d\n",max(s-1,0));
		//段数-1，只有一段数字且为0时，s-1会成-1，比0小就输出0
	}
	return 0;
}
```


---

## 作者：484A51 (赞：0)

我们可以发现，如果前一个相邻的 $0$ 在 $1$ 前面，那么下一个相邻不同的两位一定是 $1$ 在 $0$ 前面。因此我们只要看第一个不同的就行了。记相邻两数不同的数量为 $k$ 。

先拿一个例子来分析一下：
```
6
100010
```
想要它单调不下降，遇到 $1$ 在 $0$ 前面的，肯定要调换位置。第一次调整过后如下：
```
011101
```
这样我们发现，原来 $0$ 在 $1$ 前面的变成了 $1$ 在 $0$ 前面。由此我们可以推出，当第一个不相同的是 $1$ 在 $0$ 前面，答案就是 $k$ 。

再看一个：
```
7
0101010
```
它的第一对相邻的不同数字不需要调整，那么答案就是 $k-1$ 。

代码也很简单，如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int t,n;
char a[N];
int main()
{
	cin>>t;
	while(t--){
		cin>>n;
		int k=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(i>1&&a[i]!=a[i-1]) k++;	//求出k
		}
		for(int i=1;i<n;i++){
			if(a[i]<a[i+1]){	//0在1前
				k--;
				break;
			}
			if(a[i]>a[i+1]) break;	//1在0前
		}
		cout<<k<<endl;
	}
	return 0;
} 
```


---

## 作者：Remilia1023 (赞：0)

~~听说 CSP 之前写题解会 rp++。~~

因为一次修改会翻转整个后缀，所以后面的数会受前面的数影响，并且如果前面的数不满足条件，后面的数一定不满足，于是可以考虑从前往后处理。

**引理：**
因为题目要求是单调不降序列，所以结果一定是由前面一段 $0$ 和后面一段 $1$ 组成的。


记原序列为 $s$，$cnt_{i,j}$ 表示 $s_i$ 之后（包括 $s_i$）一共有多少个数 $j$，$last_{i,j}$ 表示从 $s_i$ 开始**连续的**数 $j$ 的长度。
 
假设现在正在处理 $s_i$ ，$s_i$ 之前的数全部处理完毕，即都为 $0$，分类讨论一下 $s_i$ 的情况。

1. 若 $s_i$ 为 $0$，由引理得 $cnt_{i,0}=last_{i,0} $ 时满足条件，因为 $s_i$ 之后所有的 $0$ 都连在 $s_i$ 后面，序列末尾的肯定是若干个 $1$ （或者干脆没有 $1$）；若不满足，当前位为 $0$ 必然不会影响结果，直接跳过即可。

2. 若 $s_i$ 为 $1$，则 $s_i$ 之后必须全部为 $1$ 才能满足条件，否则某一位 $1$ 之后接个 $0$，不满足单调不降。因此，$cnt_{i,1}=n-i+1$，若不满足，则当前后缀需要翻转，直接打翻转标记即可。

时间复杂度 $O(\sum n)$。

提供两份代码，一份完整按照分析模拟，较长，一份比较精简，加上头文件即可食用。

```cpp
#include <copy>
using namespace std;

const int kN = 1e6;
int T, n, cnt[kN][2], last[kN][2];
char s[kN];

int main()
{
  scanf("%d", &T);
  while (T--) {
    scanf("%d %s", &n, s + 1);
    cnt[n + 1][0] = cnt[n + 1][1] = 
    last[n + 1][0] = last[n + 1][1] = 0;  // 清零
    for (int i = n; i >= 1 ; i--) {
      int u = s[i] - '0';
      for (int j = 0; j < 2; j++)
        last[i][j] = last[i + 1][j] + 1, 
        cnt[i][j] = cnt[i + 1][j] + (u == j);
      last[i][u ^ 1] = 0; // u 的相反位从此处开始不再连续了
    }
    int rev = 0, ans = 0;  // rev 是翻转标记，ans 是翻转次数
    for (int i = 1; i <= n; i++) {
      int u = s[i] - '0';
      if (rev == 1) {  // u^rev 是当前位真实的数
        if (u == 0) {
          if (cnt[i][0] == n - i + 1) break; // 满足条件直接退出
          else rev ^= 1, ans++; // 当前位为 u^rev = 1,并且不满足条件，需要翻转
        }
        if (u == 1 && cnt[i][1] == last[i][1]) break;
      }
      else {
        if (u == 1) {  // 同上
          if (cnt[i][1] == n - i + 1) break;
          else rev ^= 1, ans++;
        }
        if (u == 0 && cnt[i][0] == last[i][0]) break;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
```

$Another:$

```cpp
#include <copy>
using namespace std;

const int kN = 1e6;
int T, n, cnt[kN][2], last[kN][2];
char s[kN];

int main()
{
  scanf("%d", &T);
  while (T--) {
    scanf("%d %s", &n, s + 1);
    cnt[n + 1][0] = cnt[n + 1][1] = 
    last[n + 1][0] = last[n + 1][1] = 0;
    for (int i = n; i >= 1 ; i--) {
      int u = s[i] - '0';
      for (int j = 0; j < 2; j++)
        last[i][j] = last[i + 1][j] + 1, 
        cnt[i][j] = cnt[i + 1][j] + (u == j);
      last[i][u ^ 1] = 0;
    }
    int rev = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
      int u = s[i] - '0';
      if ((u ^ rev) == 1) {  // u^rev 是当前位真实的数
        if (cnt[i][u] == n - i + 1) break; // 满足条件退出
        else rev ^= 1, ans++;  // 否则翻转
      }
      if ((u ^ rev) == 0 && cnt[i][u] == last[i][u]) break; // 满足条件退出
    }
    printf("%d\n", ans);
  }
  return 0;
}
```


---

## 作者：newbeeglass (赞：0)

建议评黄，思路还是比较简单的。

对于一个 ```01``` 串 ```s```，可以将一个字符（令它下标为 ```i```）及它后面所有字符取反，要求使 ```s``` 不降，就是把 ```0``` 之前的 ```1``` 全部通过操作消除，不难看出，从前往后枚举这个 ```i```，一步步往后推是最优的，因为对于后面的 ```i``` 的操作不会影响前面串，后面再怎么操作也无法消除前面的 ```1```，而对于前面的 ```i``` 的操作是必然会影响后面的串的，每次取反都要取尽量靠前的 ```i```。

如果不理解可以手动模拟一下，比如 ```010101```：

第一次操作：```001010```；

第二次操作：```000101```；

第三次操作：```000010```；

第四次操作：```000001```。

如果多模拟几个类似 ```0101010101...``` 这样的串，会发现它们都有一个特点：除了头尾的操作，中间过程两次操作消一个 ```1```，最后只剩一个 ```1```，当然这仅限于像这样连续的 ```01``` 构成的 ```01``` 串。

刚才讨论了连续的 ```01``` 构成的 ```01``` 串，现在来看普遍情况，对一堆 ```0``` 取反和对一个 ```0``` 取反是类似的，易知，一堆 ```0``` 一起操作绝对比分开操作快，所以操作中，连续的 ```0``` 或 ```1``` 都可以看成是一个字符，所以我们可以把连续的 ```1``` 或 ```0``` 都合并到一起，就有了连续的 ```01``` 构成的 ```01``` 串，可以利用刚才发现的特点求解，~~但是要分类讨论~~：

如果头是 ```0``` 尾是 ```1```：第一次操作直接消去一个 ```1```（相当于 $0$ 次操作），但最后剩下的 ```1``` 在倒数第二个，所以要多一次操作，结合操作过程，可以看出，总操作数为 ```1``` 的个数减一的两倍。

如果头尾都是 ```0```：模拟一下会发现，第一个 ```1``` 在一次操作后消除，其它 ```1``` 都是在两次操作后消除的，但是最后剩下的 ```1``` 直接在末尾，不需要增加操作，总操作数为 ```1``` 的个数减二的两倍再加一，减二表示求经过两次操作消除的 ```1``` 的个数，加一是加上第一次操作（这里讲不太清楚，式子可以自己手推一下）。

对于剩下两种情况可以自己模拟，这里就不赘述了。

总结一下：这题的解法就是先合并再代入式子求答案，时间复杂度 $O(n)$，四种情况的式子都很好推，如果看不懂可以自己推一下，会清晰很多。这题也有其它的方案可以达到最优，但本质都是两步消一个 ```1```，方法类似。

### code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n;
char a[1000005];
char s[1000005];//s 为经过合并的 a 
int main(){
	cin>>T;
	while(T--){
		memset(s,0,sizeof(s));
		cin>>n>>a;
		int flag=a[0],cnt=0;
		s[cnt]=a[0];
		for(int i=1;i<n;i++){//生成 s 
			if(a[i]!=flag){
				cnt++;
				s[cnt]=a[i];
				flag=a[i];
			}
		}
		if(cnt==0){
			cout<<0<<endl;
			continue;
		}
		if(s[0]=='0' && s[cnt]=='1'){//四种情况 
			cout<<2*((cnt+1)/2-1)<<endl;
		}
		else if(s[0]=='0' && s[cnt]=='0'){
			cout<<2*(cnt/2-1)+1<<endl;
		}
		else if(s[0]=='1' && s[cnt]=='0'){
			cout<<2*((cnt+1)/2-1)+1<<endl;
		}
		else{
			cout<<2*((cnt+2)/2-1)<<endl;
		}
	}
}

```


---

