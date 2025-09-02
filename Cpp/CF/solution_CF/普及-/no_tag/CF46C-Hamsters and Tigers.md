# Hamsters and Tigers

## 题目描述

**题目大意：**

给你个**环**，环上有$n(2<=n<=1000)$个点，每个点为黑色（题目中的仓鼠）或白色（题目中的老虎），你每次可以交换两个点的位置，求最少交换次数使得黑点白点分离（即黑点连续，中间没有白点）

## 样例 #1

### 输入

```
3
HTH
```

### 输出

```
0
```

## 样例 #2

### 输入

```
9
HTHTHTHHT
```

### 输出

```
2
```

# 题解

## 作者：lsy_41 (赞：9)

**题目分析**

首先很容易明白的就是，在最后状态的时候一定会有一串连续的 $H$ ，那么最开始的时候，我们只需要找到一段长度为 $H$ 的总数量的连续序列，$H$ 的数量最多，然后再用总的数量减掉就好啦。

剩下的细节放在了代码里啦！

------------
上代码啦：
```
#include <bits/stdc++.h>
#define maxn 1000005
using namespace std;
int n, sum[maxn << 1], cnt, ans;
//sum来统计前缀和，为当前位置的H的数量，cnt为H的数量，ans统计答案
char A[maxn << 1]; //输入的数组
int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> A[i];
		if (A[i] == 'H') cnt++; //统计H的数量
	}
	for (int i = n + 1; i < n + cnt; i++)
		A[i] = A[(i - 1) % n + 1/*下标从1开始的取模方法*/];
	//把环化成链，而且只需要在后面补cnt-1个数即可
	for (int i = 1; i < n + cnt; i++)
		sum[i] = sum[i - 1] + (A[i] == 'H'); //统计前缀和
	for (int i = 1; i <= n; i++) {
		ans = max(ans, sum[i + cnt - 1] - sum[i - 1]); //统计答案
	}
	cout << cnt - ans;
	return 0;
}
```
完结撒花！

---

## 作者：Szr__QAQ (赞：3)

[题目：CF46C](https://www.luogu.com.cn/problem/CF46C)

本题核心：**前缀和** 
时间复杂度仅为 $O(n)$。

首先审题，当看到 **可以交换两个点的位置，求最少需交换几次使得黑点连续，中间没有白点** 时，就不难想到这题可以用前缀和写，于是有了如下思路及代码。

------------

首先用 $l$ 记录 $H$ 的个数，以便 **将题目所给的环转化成链的形式**，而后就开始计算前缀和，最后再计算答案加上输出即可。

------------
代码如下。
```cpp
#include<bits/stdc++.h> 
#define itn int
using namespace std;

const int MAXN=1e5+10; 
int n,l=0,f,k[MAXN];
int i;
char c[MAXN];

void to(int o){//将环转换为链 
	int m;//存储下标 
	for(i=n+1;i<o;i++)
	{
		m=(i-1)%n+1;//计算下标 
		c[i]=c[m];
	}
	return;
}

void ccout(){//计算答案并输出
	int qwq;
	for(i=1;i<=n;i++) 
	{
		qwq=k[l+i-1]-k[i-1];
		f=max(f,qwq);
	}
	cout<<l-f<<endl;
	return;
}

int main(){
	ios::sync_with_stdio(false);//开个优化
	cin.tie();
	cout.tie();
	cin>>n;
	for(i=1;i<=n;i++)//输入及统计 H 的数量 
	{
		cin>>c[i];
		if(c[i]=='H')
			l++;
	}
	int o=l+n; 
	to(o);//开始转换 
	for(i=1;i<o;i++)//前缀和 
	{
		k[i]=k[i-1]+(c[i]!='T');//注意这里要打括号 
	}
	ccout();//提前庆祝^-^ 
	return 0;//完结撒花
}
```


------------
另外，可以看到我的代码中将部分内容封装成了函数，大家也可以养成这类习惯，以便在调试时修改代码。

本人只是一名蒟蒻，若有错误请指正，谢谢大家。

---

## 作者：分离性漫游 (赞：3)

## 这是一道前缀和。

大致思路：

首先我们要先算出 $ h $ 的个数。

其次很重要的是因为用环来算会很麻烦容易出bug。

所以我们将他转换成链的形式来算。

转换后我们算出前缀和。

最后一个循环用来算答案就可以了。

简陋的代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,h,ans,sum[10005];
char a[100005];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]=='H') h++;
	}
	for(int i=n+1;i<n+h;i++) a[i]=a[(i-1)%n+1];
	for(int i=1;i<n+h;i++) sum[i]=sum[i-1]+(a[i]=='H');
	for(int i=1;i<=n;i++) ans=max(ans,sum[i+h-1]-sum[i-1]);
	cout<<h-ans;
	return 0;
}
```


---

## 作者：Tzs_yousa (赞：3)

### 十一月JY中学用来考试的，只是数据加强了一下，不过还是很水
我的做法是线性，然而二次方的算法也可以过，当时考试为了保险写的线性。

怎么把它弄成线性，只要加个前缀和优化就可以。
```cpp
for (int i = 1; i <= n; i++)
	{
		char c;
		cin >> c;
		if(c == 'H') a[i] = 0;
		else a[i] = 1;//把他们分为1和0两种状态 
		a[i + n] = a[i];
		p[a[i]]++;
		b[i] = b[i - 1] + a[i]; //b相当于存1的数量 
	}
	for (int i = n + 1; i <= n << 1; i++)
	{
		b[i] = a[i] + b[i - 1];//把环拉成链 
	}
```

然后要做什么操作的，0 和 1 分别是两种动物，$b_i$ 就是指从一到 $i$ 有多少个 1 ，然后我们分别统计两种动物的数量，然后以其中最少的那种动物的个数为长度进行查询，找出最少的需要改变的次数即可。
```cpp
int minn, maxn = 0;
	if(p[0] < p[1]) 
	{
		minn = p[0];
		f = 0;
	}
	else 
	{
		minn = p[1];
		f = 1;
	}//看我到底是找那个动物，最后的计算会根据f加减 
	for (int l = 1; l <= n + 1; l++)
	{
		int r = l + minn - 1;
		if(f == 1) maxn = max(maxn, b[r] - b[l - 1]); 
		else maxn = max(maxn, p[0] - (b[r] - b[l - 1]));//找需要插入的最少的那个区间，就是最优解 
	}
	cout << minn - maxn;
```

全套代码到这里差不多就全了。
再发一下吧。
```cpp
#include <bits/stdc++.h>
#define int long long
const int MAXN = 1e6 + 10;
using namespace std;
int n, a[MAXN * 2], p[3], b[MAXN * 2], f;
signed main()
{
	//freopen("cycle.in","r",stdin);
	//freopen("cycle.out","w",stdout);
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		char c;
		cin >> c;
		if(c == 'H') a[i] = 0;
		else a[i] = 1;//把他们分为1和0两种状态 
		a[i + n] = a[i];
		p[a[i]]++;
		b[i] = b[i - 1] + a[i]; //b相当于存1的数量 
	}
	for (int i = n + 1; i <= n << 1; i++)
	{
		b[i] = a[i] + b[i - 1];//把环拉成链 
	}
	if(n <= 3) 
	{
		cout << 0;
		return 0;
	}//小特判 
	int minn, maxn = 0;
	if(p[0] < p[1]) 
	{
		minn = p[0];
		f = 0;
	}
	else 
	{
		minn = p[1];
		f = 1;
	}//看我到底是找那个动物，最后的计算会根据f加减 
	for (int l = 1; l <= n + 1; l++)
	{
		int r = l + minn - 1;
		if(f == 1) maxn = max(maxn, b[r] - b[l - 1]); 
		else maxn = max(maxn, p[0] - (b[r] - b[l - 1]));//找需要插入的最少的那个区间，就是最优解 
	}
	cout << minn - maxn;
	return 0;
}
```

完结撒花！


---

## 作者：Gogococoyoyo (赞：2)

这道题……

# 枚举+前缀和

其他都在代码里了吧……

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1005;
const int INF=0x7fffffff;
int n,h[N],t[N],ans=INF;//h表示仓鼠的前缀和，t表示老虎的前缀和(hamsters and tigers) 
string s;

int main(){
    scanf("%d",&n);
	cin>>s;
    for(int i=1;i<=n;++i){
        h[i]=h[i-1];
        t[i]=t[i-1];
        if(s[i-1]=='H')
            ++h[i];
        if(s[i-1]=='T')
            ++t[i];
    }//处理时先将前一位的前缀和保留过来，然后再加上这一位的仓鼠或老虎 
    for(int i=1;i<=n-h[n]+1;++i)
        ans=min(ans,t[i+h[n]-1]-t[i-1]);
    for(int i=1;i<=n-t[n]+1;++i)
        ans=min(ans,h[i+t[n]-1]-h[i-1]);
    //分两步枚举 分别枚举将仓鼠和老虎移到一起 比如计算仓鼠时 步数就老虎总数减去当前枚举到的仓鼠前所有的老虎(移动步数) 
    printf("%d\n",ans);//输出答案 
}
```

---

## 作者：togeth1 (赞：1)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF46C)

### [题意解析]
给你一个环，在这个环上有 $n$ 个点，点的颜色只有 $2$ 种：$H$ 或者 $T$。你每次可以交换两个点的位置，求最少交换次数使得黑点白点分离。

### [思路分析]
**黑点白点分离**的意思是连续的一段 $H$ 中，没有 $T$。而题目中说给出的数据是一个环形时，我们就要应用一种思想，叫**破环为链**。我们可以 $H$ 做一个前缀和，然后利用前缀和求出连续一段最长的 $H$，最后用整个数列中的 $H$ 的个数减去我们找出的最长 $H$ 的个数就好了。

### **[贴上代码]**

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[100010];
int n,k,ans,s[10010];
int main()
{
	cin>>n>>(a+1);
	for(int i=1; i<=n; i++)
		k+=(a[i]=='H');
	/* H 的总个数*/
	for(int i=n+1; i<n+k; i++)
		a[i]=a[(i-1)%n+1];
	/*破环为链*/
	for(int i=1; i<n+k; i++)
		s[i]=s[i-1]+(a[i]=='H');
	/*前缀和找出各个部分 H 的个数*/
	for(int i=1; i<=n; i++)
		ans=max(ans,s[i+k-1]-s[i-1]);
	/*算出最长一段 H 的个数*/
	cout<<k-ans;
	/*最少交换次数*/
	return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

## 题意

给出一个环，一个环上有 $n$ 个点，每个点只能是黑色或白色。`H` 表示黑点，`T` 表示白点，你每次可以任意交换两个点的位置，求最少的交换次数使得黑白点分离。

## 思路

首先可以发现让黑白点分离其实很简单，只有两种情况：

1.$1\sim k$ 是黑色或白色，$k+1\sim n$ 是白色或黑色。（左边是一个颜色，右边是另一个颜色）

2.$1\sim k_1$ 是黑色或白色，$k_1+1\sim k_2$ 是白色或黑色，$k_2\sim n$ 是黑色或白色。

用环模拟会比较麻烦，采用链会相对简单一点。意味着我们需要把 $a_i$ 的值在 $a_{i+n}$ 存下来。

经过简易分析可以想到完成后一个链一定会有一堆相同的字母堆在后面。为了方便，我们假设链有 $k$ 个连续的 `H`。

转化为链后我们可以用前缀和来统计 `H` 的个数，然后这些 `H` 在转化为链后需要全部都在最后的位置。最后在从 $1\sim k$ 进行循环，找出前面的字母要交换多少次就可以使得后面全是 `H` 即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,sum,ans;
int qzh[114514],a[114514];
char ch;
signed main(){
	scanf("%lld\n",&n);
	for(int i=1;i<=n;i++){
		cin>>ch;
		if(ch=='H')a[i]=1,a[i+n]=1,sum++;
		else a[i]=0,a[i+n]=0;
	} 
	for(int i=1;i<=n*2;i++)
		qzh[i]=qzh[i-1]+a[i];
	for(int i=1;i<=n;i++)
		ans=max(ans,qzh[i+sum-1]-qzh[i-1]);
	printf("%lld",sum-ans);
	return 0;
}
```

---

## 作者：wpy233 (赞：0)

[可能更好的阅读体验](https://www.luogu.com.cn/blog/woeeeeee/solution-cf46c)

看到本题仅有的一篇题解解释的不太详细，我来详细说明一下思路吧。

## 题目解读

**①字符串是环形，要求黑点全部连在一起**

也就是说，只要把所有的黑点都移到中间，或者将所有的黑点分布在两边，即满足题意。

∴ `TT…THH…HTT…T` 和 `HH…HTT…THH…H` 都满足题目要求。

不难发现，题目中的要求是让我们把白点**或**黑点移到中间连成一整串。

**②每次可以交换任意两个点的位置**

也就是说，要将中间多出来的黑点 / 白点移出去，要满足想要移出去的黑点 / 白点和串外面的白点 / 黑点**一样多**。

自然可以想到前缀和。

**③** $2 \leq n \leq 1000$

明示 $n^2$ 算法。

## 具体实现

我们可以定义两个数组，一个数组记录到 $a_i$ 位置时 `H` 的个数，另一个记录到 $a_i$ 位置时 `T` 的个数。

按照 ② 中提供的解读，套一个两层循环（作为串两端的位置），依次判断串内部的 `T` 或者 `H` 是否跟串外部的 `H` 和 `T` 一样多（因为只有这样才能将串内部的 `H / T` 点移干净），每次取 $\min$ 即可。

## 细节

- 串内部 `H / T` 的个数可以由 $a_j - a_i$ 算得（这样就只需要开2个数组了）。

- 两端 `H / T` 的个数可以由 总数 减去 串内部的个数 算得。

- 注意最后答案比较大小前的初值不能为 `0` （ `2147483647` 欢迎您 ）。

### 代码（含注释）
```
#include <bits/stdc++.h>//万能头
using namespace std;
int a_H[1005];
int a_T[1005];//记录当前位置，H 和 T 的个数
int main()
{
	int n;
	cin>>n;//打酱油的n
    string a;
	cin>>a;
	int ansT=0,ansH=0;//记录 H / T 的总数
	if(a[0]=='T') a_T[0]=1,ansT++;
	else a_H[0]=1,ansH++;//第一位特判
	for(int i=1;i<a.size();i++)
		if(a[i]=='T')
			a_T[i]=a_T[i-1]+1,a_H[i]=a_H[i-1],ansT++;
		else
			a_H[i]=a_H[i-1]+1,a_T[i]=a_T[i-1],ansH++;//前缀和记录
	int ans=2147483647;//ans值初始化
	for(int i=0;i<a.size();i++)
		for(int j=a.size()-1;j>=0;j--)
			if(i<=j)//串的两端不能反
			{
				int T1=a_T[j]-a_T[i];//串内部T的个数
				int T2=ansT-T1;//串两端T的个数
				int H1=a_H[j]-a_H[i];//串内部H的个数
				int H2=ansH-H1;//串两端H的个数
				if(T1==H2)//H连成一串
					ans=min(ans,T1);
				if(T2==H1)//T连成一串
					ans=min(ans,H1);
			}
	cout<<ans<<endl;//打擂台，输出
    return 0;//完结撒花
}
```
$dalao$ 们，点个赞再走呗~

---

## 作者：Cccsk03 (赞：0)

## 题目意思

给你个环，环上有 $n$ 个点，每个点为黑色 $h$ 或白色 $t$ ，你每次可以交换两个点的位置，要使得黑点连续，中间没有白点，求最少交换次数。

## 解题思路

我们用前缀和来做这道题，

因为在最后转换完成的时候肯定会有一串连续的 $h$  ，因此我们在最开始的时候，只需要找到一段长度为 $h$ 的总数量的连续序列，但记住一定要使得在这串数列中 $h$ 的数量是最多的，然后再用 $h$ 的总数量减掉这串数列中 $h$ 的数量就好啦。

既然我们已经知道了方法，所以我们要先算出 $h$ 也就是仓鼠的数量。然后将环转换成链的形式来算。转换后我们算出前缀和。最后一个循环用来算答案就可以了。

## 代码部分

```
#include<bits/stdc++.h>
using namespace std;
int n,h,ans,sum[10005];char a[100005];//定义变量
int main(){
	cin>>n;//输入
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]=='H')//统计h的数量
			h++;
	}
	for(int i=n+1;i<n+h;i++) 
		a[i]=a[(i-1)%n+1];
	for(int i=1;i<n+h;i++) 
		sum[i]=sum[i-1]+(a[i]=='H');
	for(int i=1;i<=n;i++) 
		ans=max(ans,sum[i+h-1]-sum[i-1]);
	cout<<h-ans;
	return 0;
}
```

---

## 作者：_zhx (赞：0)

这道题主要是把 H 和 T（黑和白）用最少的次数给分开。
 
首先是输入，并且统计 H（黑）的个数（输入和统计）：
```cpp
	cin>>n;
	if(n<=3) cout<<"0",exit(0);
        //其实n<=3就能直接得出答案，exit(0)就是return 0;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]=='H') k++;
	}
```

题目中给了我们一个环，但用环作比较麻烦，所以可以把环变成链，这样就比较方便；分析样例后，发现可以用前缀和的方法做，于是就得出了以下代码（建链和前缀和）：
```cpp
	for(int i=n+1;i<n+k;i++) a[i]=a[(i-1)%n+1];
	for(int i=1;i<n+k;i++)
	{
		if(a[i]=='H') s[i]=++s[i-1];//先加后用
		else s[i]=s[i-1];
	}
```
但是，要用最少的次数，那就要求出最长一段的 H 的个数,代码如下：
```cpp
	for(int i=1;i<=n;i++) m=max(m,s[i+k-1]-s[i-1]);
```
最后，在输出答案就行了：
```cpp
	cout<<k-m;
```

---

