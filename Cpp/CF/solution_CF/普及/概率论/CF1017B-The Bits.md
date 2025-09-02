# The Bits

## 题目描述

手工翻译qwq，可能掺杂个人情感，但保证题目含义不变。

Rudolf正在去城堡的路上。在大门前，保安问了他一个问题：

已知两个长度为$n$的二进制数$a,b$。你可以任意选择$a$中的两个二进制位，然后把上面的数字调换位置。问题是，有多少中不同的操作，可以生成一个与原来不同的$a\;|\;b$？

换句话说，令$c=a\;|\;b$，你能找到多少种操作，使得更改后的$a$满足$a'\;|\;b \ne c$？

其中$|$表示“按位或”运算。如$(01010)_2\;|\;(10011)_2=(11011)_2$

## 样例 #1

### 输入

```
5
01011
11001
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6
011000
010011
```

### 输出

```
6
```

# 题解

## 作者：KEBrantily (赞：5)

可以发现，若我们要得到一个新的 $a$ 满足要求，必须要至少完成以下两种操作之一。

- 若在第 $i$ 位上，$a$ 为 $1$，$b$ 为 $0$，那么将 $a$ 这一位变为 $0$；

- 若在第 $i$ 位上，$a,b$ 均为 $0$，那么将 $a$ 这一位变为 $1$。

我们设 $a$ 有 $x$ 个 $1$，$y$ 个 $0$。再设有 $z$ 个 $a|b=0$ 的位置，$k$ 个 $a=1,b=0$ 的位置。

那么，将 $a$ 中一个 $0$ 填成 $1$ 有 $x$ 种方案，反过来为 $y$ 种。

所以我们可以将上面操作的方案数算出，分别是 $ky$ 和 $zx$。

又因为某些情况同时包含了这两种操作，会重复计算，所以要减去。

答案就是 $ky+zx-kz$。

---

## 作者：da32s1da (赞：4)

发现若一个位置a串和b串都为0，则a可以移动一个1过来，异或值一定发生变化。

若有位置a为1，b为0---a为0，b为1，则a可以把1移动到0上。
```
#include<cstdio>
const int N=1e5+50;
int n;
long long ans,ans1,ans2,ans3,ans4;
char s[N],t[N];
int main(){
	 scanf("%d%s%s",&n,s,t);
	 for(int i=0;i<n;++i){
	 	if(s[i]=='0'&&t[i]=='1')ans1++;
	 	if(s[i]=='1'&&t[i]=='0')ans2++;
	 	if(s[i]=='1'&&t[i]=='1')ans3++;
	 	if(s[i]=='0'&&t[i]=='0')ans4++;
        //统计各个情况的数量
	 }
	 printf("%I64d\n",ans1*ans2+ans4*(ans2+ans3));
     //计算答案并输出
}
```

---

## 作者：nalemy (赞：3)

说说我是怎么想这道题的吧！

首先，我们要求 $a|b\not=a'|b$，我们先从$b$入手。我们考虑任意一位 $i$，如果 $b_i=1$，那么 $a_i,a_i'$ 的值就根本不会对 $c$ 造成影响。所以我们记录会对 $c$ 造成影响的位置，设 $p_i\ (i\in\{0,1\})$ 为二进制串中会对答案造成影响的位中有几个 $i$，即 $p_i=\sum_{j\in[0,n)}[a_j=i]\times [b_j=0]$。

紧接着，我们发现，只要满足 $a_i\not=a_j$ 并且 $b_i,b_j$ 中有任意一个等于 $0$，交换 $a_i,a_j$ 后都可以对答案造成影响。

看样子，我们还需要设 $t_i$ 表示二进制串中 $i$ 的总个数。

接下来进行一个**容斥**：（由于 $i,j$ 具有轮换对称性，所以统一设 $a_i=1,a_j=0$）

| $b_i$ | $b_j$ |                             说明                             |
| :---: | :---: | :----------------------------------------------------------: |
|  $0$  | $any$ | $b_i=0$ 的 $i$ 和任意一个 $j$ 交换，对答案的贡献为 $p_1\times t_0$ |
| $any$ |  $0$  | $b_j=1$ 的 $j$ 和任意一个 $i$ 交换，对答案的贡献为 $p_0\times t_1$ |
|  $0$  |  $0$  |        前面两条重复计算，所以贡献为 $-p_0\times p_1$         |

综上所述，最终答案为 $p_1\times t_0+p_0\times t_1-p_0\times p_1$。

最后，**记得开long long**！！！被坑了半个多小时！！！

**AC代码**：

```C++
#include<iostream>
using namespace std;
typedef long long ll;

ll t[2], p[2];
int main() {
    string a, b; int n; cin >> n >> a >> b;
    for (int i=0; i<n; i++) {
        t[a[i]-'0']++;
        if (b[i] == '0')
            p[a[i]-'0']++;
    }
    cout << t[0] * p[1] + t[1] * p[0] - p[0] * p[1];
    return 0;
}
```

一共 15 行，根本不用其他题解 40 50 60 行啦！史上最短代码了解一下~

---

## 作者：仁和_童博扬 (赞：2)

这是一道纯粹的数学题。。。

果然中国场都有毒瘤数学题QAQ

其实也还好想的了，虽然~~我想了一个小时~~，我太菜了。

P.S.@[LJC00118](https://www.luogu.org/space/show?uid=51815)只用了9分钟就想完+写完了。。。我菜死了QWQ

一开始，我看到这道题，首先想到的就是……打暴力。

然后就有了以下程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005], b[100005], c[100005], st[100005];
int n;
bool check()
{
	memset(c,0,sizeof(c));
	for(int i = 1; i <= n; i++)
	{
		if(a[i] || b[i])
			c[i] = 1;
		if(c[i] != st[i])
			return false;
	}	
	return true;
}
int main()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
		scanf("%1d",&a[i]);
	for(int i = 1; i <= n; i++)
		scanf("%1d",&b[i]);
	for(int i = 1; i <= n; i++)
		if(a[i] || b[i])
			st[i] = 1;
	int ans = 0;
	for(int i = 1; i <= n; i++)
		for(int j = i + 1; j <= n; j++)
		{
			int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			if(!check())
				ans++;
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
	printf("%d\n",ans);
	return 0;
} 
```
复杂度为$O(n^3)$。

显然不可能过得了（不然还是什么中国场了嘛），果然，提交后得到Time limit exceeded on pretest 5  
我果然太菜了，写个暴力居然只能过前4个点QAQ

于是我开始想怎么做，大概1h后，我终于想好了。

定义四个变量p,q,r,s。p和q分别统计a中的0和1的个数，而r和s则统计交换无效的情况，最后的ans为p*q-r*s(即总的交换情况数减去交换无效的次数)，而这种算法的复杂度仅为$O(n)$.

于是高高兴兴地写了以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std; 
int a[100005], b[100005];
int main()
{
	int i = 0;
	int p = 0, q = 0;
	int r = 0, s = 0;
	int n = 0;
	int num = 0;
	scanf("%d", &n);
	for (i = 0; i < n; i ++)
		scanf("%1d", &a[i]);
	for (i = 0; i < n; i ++)
		scanf("%1d", &b[i]);
	for (i = 0; i < n; i ++)
		if (0 == a[i])
		{
			p++;
			if(1 == b[i])
				r++;
		}
		else
		{
			q++;
			if(1 == b[i])
				s++;
		}
	num = p * q - r * s;
	cout << num <<endl;
	return 0;
}
```
然而，CF的评测显示：Wrong answer on pretest 7  
smg，我这样还错QAQ难不成是我想错了？我真的太菜了

After 10min，“啊！不会是要开long long吧！”  
我把int改成了long long然后就过了23333  
这个总不用再上一次代码了吧QWQ  
果然是我太菜了QAQ

---

## 作者：Durancer (赞：0)

### 前言

统计好题，建议做一做。

### 思路

提供一种神奇的另类思路，主要是在贡献的容斥上。

首先，可以知道的是，$1$ 和 $1$ 以及 $0$ 和 $0$ 交换是不可能存在的贡献的，所以把这种情况去掉。

我们可以以每一竖列为一个整体来做题。

这里探讨四种情况：

```
一、

A: 0                               A: 1
          这种情况下的贡献会出于   
B: 1                               B: 0

二、

A: 1                               A: 0  A: 0
          这种情况下的贡献会出于   
B: 0                               B: 0  B: 1

三、

A: 1                               A: 0
          这种情况下的贡献会出于
B: 1                               B: 0

四、

A：0                               A: 1  A: 1
          这种情况下的贡献会出于    
B: 0                               B: 0  B: 1
```

只有这四种情况下的这些对应情况中才会有对应情况产生。

找到贡献的产生方式了，那么就思考一下，如何不重不漏的计算贡献值，那么如果是全部乘起来肯定是有重复的，所以这里就考虑只考虑靠后的竖列，不考虑前面的，那么这样通过手模样例发现确实可以全部计算出来。

### 代码实现

```cpp
/*

	1和1交换是不可能有贡献的/cy
	0和0交换同样不可能有贡献
	只能找1和0交换的方案数 

*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#define int long long 
using namespace std;
const int N=1e5+9;
char a[N],b[N];
int sum01[N];
int sum10[N];
int sum11[N];
int sum00[N];
int n;
int ans;
void prepare()
{
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='0' and b[i]=='1')
			sum01[i]++;
		if(a[i]=='1' and b[i]=='0')
			sum10[i]++;
		if(a[i]=='1' and b[i]=='1')
			sum11[i]++;
		if(a[i]=='0' and b[i]=='0')
			sum00[i]++;
		sum01[i]+=sum01[i-1];
		sum10[i]+=sum10[i-1];
		sum11[i]+=sum11[i-1];
		sum00[i]+=sum00[i-1];
	}
	//for(int i=1;i<=n;i++)
	//{
	//	printf("%lld: 01: %lld , 10: %lld , 11: %lld , 00: %lld\n",i,sum01[i],sum10[i],sum11[i],sum00[i]); 
	//}
}
void work()
{
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='0' and b[i]=='1')
			ans+=(sum10[n]-sum10[i]);
		if(a[i]=='1' and b[i]=='0')
		{
			ans+=(sum00[n]-sum00[i]);
			ans+=(sum01[n]-sum01[i]);
		}
		if(a[i]=='1' and b[i]=='1')
			ans+=(sum00[n]-sum00[i]);
		if(a[i]=='0' and b[i]=='0')
		{
			ans+=(sum10[n]-sum10[i]);
			ans+=(sum11[n]-sum11[i]); 
		}
	}
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		cin>>b[i];
	prepare();
	work();
	printf("%lld\n",ans);
	return 0;
} 
```

---

## 作者：_zjr (赞：0)

#### 这道题挺有意思的，~~做完这一道题之后就弃疗了~~
##### 其实吧，我的做法比较奇葩，找了一下规律，还真叫我找着了
###### 首先你得读进去 ~~我读入花了半个小时~~
###### 因为有俩数组嘛，我就写了俩读入函数 ~~智障操作请勿模仿~~
```cpp
void read_a()
{
	int len = 0;
	char c = getchar();
	while(c == '0' || c == '1')
	{
		a[++len] = c - '0';
		c = getchar();
	}
}
void read_b()
{
	int len = 0;
	char c = getchar();
	while(c == '0' || c == '1')
	{
		b[++len] = c - '0';
		c = getchar();
	}
}
```
##### 其实我有点贪心的思想在里面，比如说b数组1的位置你不管怎么换，xor之后的值是不会变的
##### 然后b数组0的位置对应a数组可能为0可能为1~~(废话啊~~
##### 这时你记录一下这两种情况出现的次数（前面为b数组，后面为a数组）0-0为s1，0-1为s2，最后的答案要减去这两者的乘积
##### 然后扫一遍
##### 如果b[i] = 0 a[i] = 1那么他可以有s1种情况的交换方法，反之亦然
##### 那么答案就是两者之和减去重叠的部分
###### 下面上比赛代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 100010;
int n;
int a[maxn], b[maxn];
void read_a()
{
	int len = 0;
	char c = getchar();
	while(c == '0' || c == '1')
	{
		a[++len] = c - '0';
		c = getchar();
	}
}
void read_b()
{
	int len = 0;
	char c = getchar();
	while(c == '0' || c == '1')
	{
		b[++len] = c - '0';
		c = getchar();
	}
}
int main()
{
	scanf("%d", &n);
	getchar(); //行末有字符，别问我怎么知道的
	ll ans = 0;
	read_a();
	read_b();
	ll num0 = 0, num1 = 0, s1 = 0, s2 = 0, cut = 0;
	for(int i = 1; i <= n; i++)
	{
		if(a[i] == 0) num0++;
		if(a[i] == 1) num1++;
		if(b[i] == 0 && a[i] == 0) s1++;
		if(b[i] == 0 && a[i] == 1) s2++;
	}
	cut = s1 * s2;
	for(int i = 1; i <= n; i++)
	{
		if(b[i] == 0 && a[i] == 0) ans += num1;
		if(b[i] == 0 && a[i] == 1) ans += num0;
	}
	ans -= cut;
	printf("%I64d\n", ans);
	return 0;
}
```
### 然后这道题就可以用O(n)的复杂度A掉啦！

---

## 作者：KJGKMTZB (赞：0)

首先，对于每个数位的 $a$ 和 $b$ , 都有4钟情况——$a:1 , b:1$与$a:1 , b:0$与$a:0 , b:1$与$a:0 , b:0$ ，先用四个变量保存情况的次数$.$  接下来，我们开始分析$.$

因为异或是只要有其中一个的位数是$1$,那么这位就是$1$，因为只能交换a，我们就把 $b$ 是 $1$ 而 $a$ 也是 $1$ 的次数用k1记录下来 $.$ 那么这些位数只能与 $a$ 其他位数上不是 $1$ 且那个位数所对应的 $b$ 上的数也不是 $1$ 才能交换。

那么如果 $a$ 上的数是 $1$ 且 $b$ 上对应的数为 $0$ ，则那位数，只要与其他的 $a$ 位上为 $0$ 的数且那位数对应的 $b$ 的位数也为 $0$ 便可以交换

接着，把两个算出来的加起来，就是 $ans$ 了 $.$

```
#include<bits/stdc++.h>
using namespace std;/*大胆，竟敢抄题解*/
string a,b;/*大胆，竟敢抄题解*/
long long n,i,j,k1=0,k2=0,k3=0,k4=0,a1=0,a0=0,b1=0,b0=0;
//a1指a中出现了1的次数，a0指a中出现了0的次数。b也如此。
int main(){/*大胆，竟敢抄题解*/
	cin>>n;/*大胆，竟敢抄题解*/
	cin>>a>>b;/*大胆，竟敢抄题解*/
	for(i=0;i<n;i++)/*大胆，竟敢抄题解*/
	{/*大胆，竟敢抄题解*/
		if(b[i]=='1')/*大胆，竟敢抄题解*/
		{/*大胆，竟敢抄题解*/
			b1++;/*大胆，竟敢抄题解*/
			if(a[i]=='1')/*大胆，竟敢抄题解*/
			{/*大胆，竟敢抄题解*/
				k1++;/*大胆，竟敢抄题解*/
				a1++;/*大胆，竟敢抄题解*/
			}/*大胆，竟敢抄题解*/
			else/*大胆，竟敢抄题解*/
			{/*大胆，竟敢抄题解*/
				k2++;/*大胆，竟敢抄题解*/
				a0++;/*大胆，竟敢抄题解*/
			}/*大胆，竟敢抄题解*/
		}/*大胆，竟敢抄题解*/
		else/*大胆，竟敢抄题解*/
		{/*大胆，竟敢抄题解*/
			b0++;/*大胆，竟敢抄题解*/
			if(a[i]=='1')/*大胆，竟敢抄题解*/
			{/*大胆，竟敢抄题解*/
				k3++;/*大胆，竟敢抄题解*/
				a1++;/*大胆，竟敢抄题解*/
			}/*大胆，竟敢抄题解*/
			else/*大胆，竟敢抄题解*/
			{/*大胆，竟敢抄题解*/
				k4++;/*大胆，竟敢抄题解*/
				a0++;/*大胆，竟敢抄题解*/
			}/*大胆，竟敢抄题解*/
		}/*大胆，竟敢抄题解*/
	}/*大胆，竟敢抄题解*/
	cout<<k1*(b0-k3)+k3*(n-a1);/*大胆，竟敢抄题解*/
}/*大胆，竟敢抄题解*/
```
为防止抄题解如此做

大胆，竟敢抄题解

---

