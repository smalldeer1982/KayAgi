# Contrast Value

## 题目描述

For an array of integers $ [a_1, a_2, \dots, a_n] $ , let's call the value $ |a_1-a_2|+|a_2-a_3|+\cdots+|a_{n-1}-a_n| $ the contrast of the array. Note that the contrast of an array of size $ 1 $ is equal to $ 0 $ .

You are given an array of integers $ a $ . Your task is to build an array of $ b $ in such a way that all the following conditions are met:

- $ b $ is not empty, i.e there is at least one element;
- $ b $ is a subsequence of $ a $ , i.e $ b $ can be produced by deleting some elements from $ a $ (maybe zero);
- the contrast of $ b $ is equal to the contrast of $ a $ .

What is the minimum possible size of the array $ b $ ?

## 样例 #1

### 输入

```
4
5
1 3 3 3 7
2
4 2
4
1 1 1 1
7
5 4 2 1 0 0 4```

### 输出

```
2
2
1
3```

# 题解

## 作者：Lovely_Chtholly (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF1832C)

### 【分析】

有 $3$ 种删除数的情况：

1. $a_i = a_{i+1}$：因为它们的差值为 $0$，所以删除它们并不影响整个序列的权值。

1. $a_i < a_{i+1}$：只要它们递增，那么只用留下头尾 $2$ 个元素即可保持整个序列的权值不变。

1. $a_i > a_{i+1}$：若它们递减，那么也只需留下头尾 $2$ 个元素。

记录留下的元素个数即可。

### 【AC 代码】

```cpp
#include<stdio.h>
#include<iostream>
#include<stack>
using namespace std;
const int N=3e5+10;
inline int read(char ch=getchar(),int n=0,int m=1)
{
	while(ch<'0' or ch>'9')
	{
		if(ch=='-')m=-1;
		ch=getchar();
	}
	while(ch>='0' and ch<='9')n=(n<<3)+(n<<1)+ch-'0',ch=getchar();
	return n*m;
}
ostream& operator <<(ostream& o,__uint128_t &a)
{
	__uint128_t x=a;
	stack<int>s;
	while(x)s.push(x%10),x/=10;
	while(!s.empty())o<<s.top(),s.pop();
	return o;
}
int t=read();
signed main()
{
	while(t--)
	{
		int n=read(),a[N],sum=1;
		for(int i=1;i<=n;i++)a[i]=read();
		if(n==2)
		{
			puts(a[1]==a[2]?"1":"2");
			continue;
		}
		for(int i=1;i<n;)
		{
			if(a[i]==a[i+1])i++;
			else if(a[i]<a[i+1])
			{
				for(;i<n and a[i]<=a[i+1];i++);
				sum++;
			}
			else
			{
				for(;i<n and a[i]>=a[i+1];i++);
				sum++;
			}
		}
		cout<<sum<<"\n";
	}
	return 0;
}
```

~~鲁迅说过：~~

>~~莫抄袭，棕了你的名，空悲切！~~

---

## 作者：Night_sea_64 (赞：5)

我们先从样例入手。

$a=\{1,3,3,3,7\}$。它的权值是：$|3-1|+|3-3|+|3-3|+|7-3|=2+0+0+4=6$。而我们令 $b=\{1,7\}$，它的权值也是 $6$。

这是因为，当没有绝对值符号的时候，$a_2-a_1+a_3-a_2+a_4-a_3+\dots+a_n-a_{n-1}$，它中间一堆都抵消掉了，最后只剩下 $a_n-a_1$。

而当一个序列单调不升或不降的时候，就可以等同于没有绝对值符号了，因为每个差都是非负整数或非正整数。

于是我们就找 $a$ 最少分为几段，使得每段都单调不升或不降。用两个变量记录当前这一段是不升还是不降，一开始两种状态都不是。从 $a_2\sim a_n$ 扫一遍，如果现在与刚才记录的状态不同，就新开一段并把答案 $+1$。最后因为点数等于段数 $+1$，所以答案还要再 $+1$。

```cpp
#include<iostream>
using namespace std;
int a[300010];
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        int cnt=0;
        bool flag1=0,flag2=0;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            if(i>1)
                if(a[i]>a[i-1]&&!flag1)
                    flag1=1,flag2=0,cnt++;
                if(a[i]<a[i-1]&&!flag2)
                    flag2=1,flag1=0,cnt++;
        }
        cout<<cnt+1<<endl;
    }
    return 0;
}
```

---

## 作者：Furina_Hate_Comma (赞：3)

可以考虑挖掘性质。

首先不难发现对于任意相邻的数字，如果他们相同，则贡献为 $0$ 可以删去。

然后对于以下这种情况

$$a_{i-1}\le a_i \le a_{i+1}$$

显然可以删去 $a_i$，它对结果没有贡献。

尝试推广这个性质，我们发现，对于任意 $1$ 个递增或递减的连续子序列，我们可以只留下头尾 $2$ 个数字。

直接扫增减块，相同跳过，答案就是块数 $+ 1$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[500000];
signed main()
{
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int i=1,ans=1;
		while(i<n){
			if(a[i]==a[i+1])i++;//相同
			else if(a[i]<a[i+1]){
				while(a[i]<=a[i+1]&&i<n)
					i++;
				ans++;
			}//递增，只留下头尾，但是由于尾部与下一个子序列重合，所以只算一次
			else if(a[i]>a[i+1]){
				while(a[i]>=a[i+1]&&i<n)
					i++;
				ans++;
			}//递减，同上
		}
		cout<<ans<<'\n';
	}
    return 0;
}
```

---

## 作者：sto_5k_orz (赞：2)

什么水题。

当 $a_{i-1}\le a_i\le a_{i+1}$ 或者 $a_{i-1}\ge a_i\ge a_{i+1}$ 时，$i$ 可以没有。

$a_{i-1}\le a_i\le a_{i+1}$ 时，$|a_{i+1}-a_{i-1}|=a_{i+1}-a_{i-1}$，$|a_{i+1}-a_i|+|a_i-a_{i-1}|=a_{i+1}-a_i+a_i-a_{i-1}=a_{i+1}-a_{i-1}$。

同理可得 $a_{i-1}\ge a_i\ge a_{i+1}$ 时，$i$ 可以没有。

为什么我这种题目还吃两发罚时？

```cpp
#include<bits/stdc++.h>
using namespace std;
#define CI const int
#define gc getchar
#define Mt(a, b) memset(a, b, sizeof a)
#define pc putchar
#define W while
#define I inline
#define pb push_back
#define ll long long
#define int long long
namespace SlowIO {
	I int read() {
		int x = 0, f = 1; char ch = gc();
		W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void Read(int &x) {x = read();}
	I void Read(int &x, int &y) {Read(x), Read(y);}
	I void write(int x) {
		if(x < 0) pc('-'), x = -x;
		if(x > 9) write(x / 10);
		pc(x % 10 + '0');
	}
	I void writeln(int x) {write(x); pc('\n');}
	I void Write(int x) {write(x); pc(' ');}
} using namespace SlowIO;
const int N = 300010; int a[N];
signed main() {
	int t; Read(t);
	W(t--) {
		int n; Read(n); for(int i = 1; i <= n; i++) Read(a[i]);
		int cnt = 1; int flag = -1;
		for(int i = 1; i < n; i++) {
			if(a[i] < a[i + 1]) {
				if(flag != 1) cnt++;
				flag = 1;
			}
			if(a[i] > a[i + 1]) {
				if(flag != 0) cnt++;
				flag = 0;
			}
		}
		writeln(cnt);
	}
	return 0;
}
```

---

## 作者：PCCP (赞：2)

作为 CF div.2 的第三题，没有在至多半个小时里写出来真的是太不应该了。

题目要求我们对于每一个数组 $ a $ 求出一个新数组 $ b $，设数组 $ b $ 的大小为 $ m $ ，使得 $ |a_1-a_2|+|a_2-a_3|+\cdots+|a_{n-1}-a_n| = |b_1-b_2|+|b_2-b_3|+\cdots+|b_{m-1}-b_m| $ 成立并且数组 $ b $ 中的每一个数都来自数组 $ a $ 。

这其实等效于要我们从数组 $ a $ 里删除一些数。

我们考虑一些特殊情况：

1. 如果整个数组都是同一个数，保留一个数即可，因为题目要求我们所求出来的数组 $ b $ 不能为空。

2. 对于其他情况，首先 $ a_1 $ 和 $ a_n $ 肯定是不能删除的，这是毋庸置疑且极为简单的结论。

3. 如果一个数等于两边的任何一个数，那么他都可以被删除并被取而代之，这也是毋庸置疑且极为简单的结论。

对于一般情况，我们单独拿出一个数以及它两侧的数来分析：

情况一： ![](https://cdn.luogu.com.cn/upload/image_hosting/mk7ywgdz.png)

情况二： ![](https://cdn.luogu.com.cn/upload/image_hosting/ngsyr49u.png)

情况三： ![](https://cdn.luogu.com.cn/upload/image_hosting/tzp7q0vu.png)

情况四： ![](https://cdn.luogu.com.cn/upload/image_hosting/z7vys2s3.png)

观察上述四种情况，不难发现：对于情况一、二，$ a_i $ 都是不能删除的；而对于情况三、四， $ a_i $ 都是一定可以删除的。

也就是说，不考虑相等的情况，在一个单调增或减区间内，除了两端的转折点外，其他点都是多余的。

以上就是本题的做法了，确实是相当简单的（记得去重）。

代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int N=1e6+10;
int t,n,a[N],b[N],res;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		res=0;
		int last=0;
		b[0]=-1;
		for(int i=1;i<=n;i++){
			if(a[i]==b[last]){
				continue;
			}
			else{
				b[++last]=a[i];
			}
		}
		for(int i=2;i<=last-1;i++){
			if(b[i-1]<b[i]&&b[i]>=b[i+1]){
				res++;
			}
			if(b[i-1]>b[i]&&b[i]<=b[i+1]){
				res++;
			}
		}
		if(last!=1){
			res+=2;
		}
		else{
			res=1;
		}
		for(int i=1;i<=n;i++){
			b[i]=a[i]=0;
		}
		printf("%d\n",res);
	}
}
```

---

## 作者：yangmingshuo114514 (赞：2)

## 思路

首先对于 $a_i=a_{i+1}$ 这种情况删除 $a_{i+1}$ 肯定是对权值没有影响的。

然后对于 $a_i<a_{i+1}<a_{i+2}$ 或者 $a_i>a_{i+1}>a_{i+2}$ 这两种情况可以删除 $a_{i+1}$。

最后，我们可以把结论推到 $a_i<a_{i+1}<...<a_{j-1}<a_{j}$ 及 $a_i>a_{i+1}>...>a_{j-1}>a_{j}$ 这两种情况，从 $a_{i+1}$ 到 $a_{j-1}$ 这段区间里的数都是可以删除的。

我们可以用一个变量判断之前序列处于降序还是升序，判断若当前状态是否与之前状态相同，如果相同就删除。

## 代码

```cpp
#include<cstdio>
int t,n,a[300005],now,ans;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		ans=n;
		now=-1;
		for(int i=1;i<n;i++){
			if(a[i]==a[i+1]) --ans;//相邻两个数相等就删除
			else if(now==0&&a[i]<a[i+1]) --ans;
			else if(now==1&&a[i]>a[i+1]) --ans;//与之前状态相同就删除
			else now=(a[i]>a[i+1]);//改变状态
		}
		printf("%d\n",ans);
	}
	return 0;
}

---

## 作者：shinzanmono (赞：1)

三年 OI 一场空，不开 long long 见祖宗！！！

题目很简单，但是实现却不太好写。

这道题的第一感觉就是，初中数学讲过，若 $a>b>c$，则 $|a-b|+|b-c|=|a-c|$。

于是我们可以推出来：对于一个单调序列 $\{x_n\}$，那么 $\sum^{n-1}_{i=1}|x_i-x_{i+1}|=|x_n-x_1|$。

我们以这个考虑，求出所有的单调区间，那么最后的答案就是所有单调区间端点的个数（特判 $n=1$，$n=2$，$a$ 中元素相同三种情况）。

我们设一个 $hill$ 数组，储存的是 $a_i-a_{i-1}$，也就是 $a_i$ 的变化率（可以近似的认为是导数），根据导数的定义，我们可知 $hill_i\cdot hill_{i-1}<0$ 的时候，$a_{i-1}$ 便是一个端点，这里有两个坑点：

* 不要忽略的两边的端点
* $hill_i\cdot hill_{i-1}$ **可能超出 int**（赛时因为这个没有 AC）

然后最后我们求得答案就撒花了！！！

给出大坑代码：
```cpp
#include<iostream>
#include<algorithm>
const int sz = 3e5 + 10;
int arr[sz], carr[sz];
long long hill[sz];
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        for (int i = 1; i <= n; i++) std::cin >> arr[i];
        int npp = 1;
        carr[1] = arr[1];
        for (int i = 2; i <= n; i++) 
            if (arr[i] != arr[i - 1]) carr[++npp] = arr[i];
        int cnt = 1;
        n = npp, std::copy(carr + 1, carr + npp + 1, arr + 1);
        if (n <= 2) {
            std::cout << n << "\n";
            continue;
        }
        if (arr[1] > arr[2]) arr[0] = 1e9 + 1;
        else arr[0] = -1;
        for (int i = 1; i <= n; i++) {
            hill[i] = arr[i] - arr[i - 1];
            if (hill[i] * hill[i - 1] < 0) cnt++;
        }
        std::cout << cnt + 1 << "\n";
    }
    return 0;
} 
```

---

## 作者：__Dist__ (赞：0)

### 题目描述

[原题](https://www.luogu.com.cn/problem/CF1832C)

共 $ T $ 组测试样例。对于每组样例，给定 $ n $ 和一个长度为 $ n $ 的 $ a $ 数组，让你求出与 $ a $ 数组权值相同的 $ b $ 数组的最小长度。

### 思路分析

数据范围较大，考虑 $ O(Tn) $ 做法。

先给出权值定义：

对于一个数组 $ [a_1,a_2,\cdots ,a_n] $，它的权值就是 $ |a_1-a_2|+|a_2-a_3|+ \cdots +|a_n-1-a_n| $。举个简单的例子：对于一组数 $ [1,1,4,5,1,4] $ 其权值为 $ |1-1|+|4-1|+|5-4|+|1-5|+|1-4|=11 $。

我们可以这样想，假使这个数组具有单调性，那么它的权值是什么呢？不难推算出来，答案是 $ a_1+a_n $，这样就可以使计算长度大大缩小，时间复杂度降低。

因为本原理只限于单调数组，所以我们不妨把 $ a $ 数组拆分成 $ k $ 个单调性的小数组。类似于植树问题，我们把段数求出来了（属于输中间的空），而 $ b $ 让你输出的是点（第一棵树到最后一棵的距离），所以只需输出 $ m+1 $ 即可。

代码码量不长，但是有一定思维含量，是个好题。

### 代码环节

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<iomanip>
#include<cstdio>
#include<stack>
#include<queue>
#include<map>
#include<vector>
using namespace std;
int main(){
	int T;
	cin>>T;
	while(T--){
		int f=114514;//标记此时是减序还是增序
		//0为减序，1为增序，最开始时啥也不是
		int now;//储存这一个数
		int a;//储存这一个数
		int n;
		int m=0;//储存长度
		cin>>n>>a;//因为a[1]没啥用
		for(int i=2;i<=n;i++){
			cin>>now;
			if(now>a){
				if(f!=1) m++;//打破原来的单调性，创建下一个空
				f=1;//改为增序
			}
			if(now<a){
				if(f!=0) m++;//同上
				f=0;
			}
			a=now;//更新a的值
		}
		cout<<m+1<<endl;
	}
	return 0;
}
```


---

## 作者：CheZiHe929 (赞：0)

# CF1832C 题解

## 原题链接
[**Codeforces**](https://codeforces.com/contest/1832/problem/C)

[**洛谷**](https://www.luogu.com.cn/problem/CF1832C)

## 题目大意
有 $T$ 组测试样例，每组样例给你一个长度为 $n$ 的 $a$ 数列，让你求出与 $a$ 数组权值相同的 $b$ 数组的最小长度。

**权值定义：**

我们把 $ [a_1, a_2, \dots, a_n] $ 定义为 $a$ 数组的权值，他的权值就等于 $ |a_1-a_2|+|a_2-a_3|+\cdots+|a_{n-1}-a_n| $。

例：

$ [ 1 , 5 , 3 , 8 , 6 ] = |1 - 5| + |5 - 3| + |3 - 8| + |8 - 6| = 4 + 2 + 5 + 2 = 13$。

## 思路分析
一看数据范围就知道是一道 $ O (Tn) $ 的题。

只要保证某一个序列具有**单调性**（即单调递增、单调递减、单调不增、单调不减四种情况），其间的数就可以相互抵消。比如说我们假设 $ [a_1, a_2, \dots, a_n] $ 这个数列具有单调性，那么它的权值就等于 $a_1+a_n$，这个答案也就是 $ [a_1,a_n] $ 的权值的答案，长度自然就可以缩小。因为本条性质只针对于有单调性的数列，所以我们可以把原数列拆分为 $m$ 个具有单调性的数列，那么答案就是 $m + 1$（因为 $m$ 代表的是有几组，而我们要求的 $b$ 数组的最小长度则是点的个数，所以要 $+ 1$。这和小学的种树问题有点类似）。

最后：**多测不清空，爆零两行泪**（不过本题好像不需要清空，因为可以不用数组，但是为了保险起见还是加上）。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[300005];//本题可以不用定义数组，只需要定义一个now记录上一个数就行了
signed main(){
	int T;
	cin>>T;
	while(T--){
		//memset(a,0,sizeof(a));
		int n;
		cin>>n;
		int m=0;//有几个单调性的数列
		int f=-1;//判断目前的数列是增还是减，0为减，1为增，刚开始什么数列也不是 
		cin>>a[1];//第一个数无法形成数列，所以我们提前读入 
		for(int i=2;i<=n;i++){
			cin>>a[i];
			if(a[i]>a[i-1]){
				if(f!=1)m++;//已经无法保证单调性，因为f刚开始为-1，所以我们要用!=1 
				f=1;//把f改变为增 
			}
			if(a[i]<a[i-1]){
				if(f!=0)m++;//同上 
				f=0;//把f改变为减 
			}
			//因为=可以化作为1个数，所以我们不用考虑 
		}
		cout<<m+1<<endl;//点数=间隔的数量（组数）+1 
	}
	return 0;
} 
```

无注释版的在[**这里**](https://www.luogu.com.cn/paste/ks46u22a)。

## AC 记录
[**Codeforces**](https://codeforces.com/contest/1832/submission/207418165)

[**洛谷**](https://www.luogu.com.cn/record/111344150)

**THE END.**

**THANK YOU.**

---

## 作者：MYJ_aiie (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1832C)

------------

我们发现，$n$ 为 $3\times10^{5}$，所以暴力肯定是不行的。   
看样例：   
$5\;4 \;2 \;1 \;0 \;0\;4$  
每两项直接的绝对值是：  
$\,\,1\; 2 \;1 \;1 \;0 \;4$  

又发现, $5$ 和 $1$ 直接虽然有 $4$ 和 $2$，但是因为是不递增的,删去之后不会影响权值，所以可以简化成 $5$ 和 $1$ 。不递减的序列也同样。于是问题就变成了统计有序序列。   
发现连接两端有序的数一定是小于前一个数大于后一个数，或者大于前一个数小于后一个数的，所以直接统计这个转折即可。  
所以我们可以把问题转化成有几段转折再 $+1$ 。

code
------------
```
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map> 
#include<algorithm>
using namespace std;
int t;
int ans,n;
int a[300005];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		int p=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
			if(a[i]!=a[i-1]&&i!=1) p++; 
		}
		int m=unique(a+1,a+1+n)-a-1;
		if(p==0) printf("1\n");//注意特判，若所有数字都相等，就直接输出1
		else
		{
			ans=2;
			int k=0;
			for(int i=2;i<m;i++)
			{
				if(a[i]>a[i-1]&&a[i]>a[i+1]) ans++;
				if(a[i]<a[i-1]&&a[i]<a[i+1]) ans++;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
```


---

## 作者：Kedit2007 (赞：0)

### 题目大意

给定一个序列 $[a_1, a_2, ..., a_n]$ ，定义一个序列的权值为每两个相邻元素之差的绝对值之和，即 $\sum^{n-1}_{i=1}{\left|a_i-a_{i+1}\right|}$ 。找出序列 $a$ 中最小的**子序列**，使得其权值与原序列相同。

### 思路

容易发现，如果一个序列是有序的（非严格降序或升序皆可），如 $[1, 1, 3, 5]$ ，那么只保留这个序列的开头和结尾不会影响权值。如 $[1, 1, 3, 5]$ 与 $[1, 5]$ 权值相同
。

所以我们只需要判断这个序列有几个“转折”，也就是从某个数字开始由降序转为升序或由升序转为降序即可。

如序列 $[1, 2, 3, 5, 2, 1]$ ，从第四个数字，即 $5$ 开始由升转降，故取子序列 $[1, 5, 1]$ 即可。 

### 核心参考代码

```cpp
int contrast_value(vector<int>& input)
{
	int state = -1; // 0 for inc, 1 for dec
	int a, b = input.front();
	int ans = 1;
	for (int i = 1; i < input.size(); i++)
	{
		a = b;
		b = input[i];
		if (b > a && state != 1)
		{
			state = 1;
			ans++;
		}
		else if (b < a && state != 0)
		{
			state = 0;
			ans++;
		}
	}
	return ans;
}
```

---

## 作者：Mikefeng (赞：0)

## 题意

定义一个数列的价值是每相邻两个数的差的绝对值之和，要求找出长度最短的数列 $b$，使得 $b$ 的价值与 $a$ 相等，并且 $b$ 是 $a$ 的子序列。

## 做法

先从 $b$ 是 $a$ 的子序列入手，也就是说 $b$ 是 $a$ 删去最多的数得到的。

首先相邻的一样的数显然可以只留下一个。

又因为要求两个数列价值相等，所以只有形如 $a_{i-1}<a_i<a_{i+1}$ 或 $a_{i-1}>a_i>a_{i+1}$ 时，可以删掉 $a_i$，贪心从左往右扫，每遇到一个不能删的数就输出。

时间复杂度 $O(n)$。

## 代码
```cpp
const int N=3e5+5;
int T,n;
int a[N];
vector<int> v;
bool M2;
int main(){
	int Time=clock();
	look_memory;
	T=read();
	while(T--){
		n=read();
		F(i,1,n) a[i]=read();
		v.clear();
		v.emplace_back(a[1]);
		F(i,2,n) if(a[i]!=a[i-1]) v.emplace_back(a[i]);
		int ans=v.size();
		F(i,2,v.size()-1){
			if(v[i-2]<v[i-1]&&v[i-1]<v[i]) --ans;
			if(v[i-2]>v[i-1]&&v[i-1]>v[i]) --ans;
		}
		cout<<ans<<'\n';
	}
	look_time;
	return 0;
}

```

---

