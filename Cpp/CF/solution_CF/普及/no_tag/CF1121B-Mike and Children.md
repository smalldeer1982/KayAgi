# Mike and Children

## 题目描述

Mike decided to teach programming to children in an elementary school. He knows that it is not an easy task to interest children in that age to code. That is why he decided to give each child two sweets.

Mike has $ n $ sweets with sizes $ a_1, a_2, \ldots, a_n $ . All his sweets have different sizes. That is, there is no such pair $ (i, j) $ ( $ 1 \leq i, j \leq n $ ) such that $ i \ne j $ and $ a_i = a_j $ .

Since Mike has taught for many years, he knows that if he gives two sweets with sizes $ a_i $ and $ a_j $ to one child and $ a_k $ and $ a_p $ to another, where $ (a_i + a_j) \neq (a_k + a_p) $ , then a child who has a smaller sum of sizes will be upset. That is, if there are two children who have different sums of sweets, then one of them will be upset. Apparently, Mike does not want somebody to be upset.

Mike wants to invite children giving each of them two sweets. Obviously, he can't give one sweet to two or more children. His goal is to invite as many children as he can.

Since Mike is busy preparing to his first lecture in the elementary school, he is asking you to find the maximum number of children he can invite giving each of them two sweets in such way that nobody will be upset.

## 说明/提示

In the first example, Mike can give $ 9+2=11 $ to one child, $ 8+3=11 $ to another one, and $ 7+4=11 $ to the third child. Therefore, Mike can invite three children. Note that it is not the only solution.

In the second example, Mike can give $ 3+9=12 $ to one child and $ 1+11 $ to another one. Therefore, Mike can invite two children. Note that it is not the only solution.

## 样例 #1

### 输入

```
8
1 8 3 11 4 9 2 7
```

### 输出

```
3
```

## 样例 #2

### 输入

```
7
3 1 7 11 9 2 12
```

### 输出

```
2
```

# 题解

## 作者：Z_M__ (赞：5)

题目主要意思是，在n个数中每次找2个数，使每次找的2个数的和都相等，问最多能找出几对数？

我们可以计算出每个数$ai$与其他数$a_j$的和，再算出最多出现次数的**和值**即可

观察到$a\le 1e5,n\le 1000$所以可以用**桶**来统计数出现的个数。

这个桶记得就是该下标数值出现的次数

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
int n, res, maxn, a[MAXN], b[MAXN + MAXN]; // b数组要开到2e5,！
int main ()
{
	ios :: sync_with_stdio (0), cin.tie (0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i], maxn = max (maxn, a[i]);
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) // j从i+1开始枚举，这样不会重复
			b[a[i] + a[j]]++;
	for (int i = 2; i <= maxn * 2; i++) // 最小的值只能是2，最大的数只能是2e5
		res = max (res, b[i]);
	cout << res << endl;
	return 0;
}
```

---

## 作者：WsW_ (赞：2)

### 更新：
* 2023/7/23 更改两处错误。

感谢指正！

---

### 思路：
由于 $n\le10^3$，可以进行 $O(n^2)$ 的暴力枚举，得出每对数的和。  
由于 $a_i\le10^5$，可以开一个数组作为桶，以和为下标，记录每次的加和出现的次数。  
记录的过程中，不断更新答案，取出现次数的最大值。

---

### 代码和[提交记录](https://codeforces.com/problemset/submission/1121/215143925)  
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[1003];
int cnt[200003];
int ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(int j=1;j<i;j++){
			cnt[a[i]+a[j]]++;
			if(cnt[a[i]+a[j]]>ans){
				ans=cnt[a[i]+a[j]];
			}
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Rbu_nas (赞：1)

**题意简述**

长度为$n$的序列$a$中，满足$a_i+a_j = a_k+a_m(i≠j≠k≠m)$性质个数的最大值

$ $

一道简单的模拟qwq，结合样例解释差不多就出来了。

首先用类似于桶的思想，把能达到$a_i+a_j(i+1≤j≤n)$值的个数记录下来，然后再循环遍历这个桶，最大的次数即为最大值

可能唯一的难点在循环变量取值吧233，因为$a_i+a_j$
是不断往后推的，所以每次$j$从$i+1$开始，感性理解一下就能明白

具体细节见代码

$ $

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

#define gcc getchar
template <typename T> inline void read(T&x)
{
    x=0; bool f=true; char ck=gcc();
    for( ; ck<'0'||ck>'9'; ck=gcc()) if(ck == '-') f=false;
    for( ; ck>='0'&&ck<='9'; ck=gcc()) x=(x<<1)+(x<<3)+(ck^48);
    x=f?x:-x; return ;
}

#define N 1003
#define M 200003
int n, res, a[N], flag[M];

int main(void)
{
    read(n);
    for(int i=1; i<=n; ++i) read(a[i]);
    for(int i=1; i<=n; ++i)
        for(int j=i+1; j<=n; ++j)
            ++flag[a[i]+a[j]];
    //更新ai+aj的值的次数       
    for(int i=1; i<=M; ++i)
        res=max(res, flag[i]);
    //取相同值的最大次数    
    printf("%d", res);
    return 0;
}

```

---

## 作者：5G信号塔报装 (赞：1)

洛谷的翻译很简洁，但是，太抽象了！

## 题意

你有 $n$ 个糖果，每个糖果有不同的“尺寸”。

你可以从中任意选取 $2k$ 个糖果给 $k$ 个孩子，(一个孩子两个糖果)。

要求是满足尽可能多的孩子得到的糖果的尺寸之和相等。

## 思路

观察一下题目数据：$a_i$ 很小，只有 $10^5$，同时 $n$ 最大只有 $10^3$。

自然地，我们考虑到 **桶**。

$bucket_i$ 表示数的和为 $i$ 的出现次数。

对于每对数的 $2$ 个数字，我们把他们的和相加得到的 $num$ 在桶内标记（$+1$）。

好了，本题就解完了：**最优的尺寸（即答案），自然就是桶的** $\bold{max}$。

## Code

**Think Twice, Code Once**

```cpp
# include <bits/stdc++.h>
using namespace std;

int ans;
int a[10005];
int bucket[10000005]; // 桶，开大一点，不爆就行 

signed main() {
	puts("5G 赋能未来！");
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i < n; i++) { // 注意两个 for 的边界！起止点！
		for (int j = i + 1; j <= n; j++) {
			bucket[a[i] + a[j]]++; // 桶标记
			ans = max(ans, bucket[a[i] + a[j]]); //每次取max，不用重新算了！
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

// 2020.01.05 更新了一下，加了一段桶的定义。


---

## 作者：liushuaishuai (赞：0)

## 题目

[传送带](https://www.luogu.com.cn/problem/CF1121B)

## 思路

+ 用双重循环枚举下标 $i$，$j$。
+ 数的范围较小，可以用一个桶统计个数。

## 注意事项

+ 桶的数组必须开到 $100000 \times 2$。

## 代码
```cpp
#include <bits/stdc++.h>

#define N 1010
#define M 100010 

using namespace std;

int n, a[N], l[M + M]; //注意a <= M, b <= M, 则 a + b <= 2M 
int maxn = -1;

int main(){
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i]; //输入
	
	for (int i = 1; i < n; i++)
		for (int j = i+1; j <= n; j++) //枚举
			l[a[i] + a[j]]++; //标记
	for (int i = 1; i <= 200000; i++) maxn = max(maxn, l[i]); //求最大值 
	cout << maxn; 
	return 0;
}
```


---

## 作者：黑影洞人 (赞：0)

题意翻译十分简洁，我说几点需要注意的。

>最多能选几个数？

这是错的，要给出最多选出几对数。

现在我们就珂以开始了。

我的做法理论时间复杂度是 $O(n^3)$ 的暴力，但是因为常数较小于是珂以通过。

首先我们观察发现 $a_i$ 的范围很小，只有 $10^5$ 于是我们把给出的数标记一下。

```cpp
scanf("%d",&n);
for(int i=1;i<=n;i++)scanf("%d",&a[i]),vis[a[i]]=1;
//标记一下a[i]方便后面查找
```
然后枚举任意两个数，得到一个和 $a_i+a_j(i\not=j)$ 再循环一次，判断 $a_i+a_j-a_k$ 是否被之前标记过，如果被标记过，那么说明这个答案珂行，把当前答案加一，最后统计最大值即可。

注意以下两点：

- 防止数组越界，当 $(a_i+a_j-a_k)<1$ 时直接跳过。

- 最后答案两两统计过，所以答案要除以二。

```cpp
#include<cstdio>
#include<algorithm>
#define N 1919810
using namespace std;
int n,a[N],l,r,ans;
bool vis[N];
signed main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),vis[a[i]]=1;
	for(int ii=1;ii<=n;ii++){
		for(int jj=ii+1;jj<=n;jj++){
			int v=a[ii]+a[jj],cnt=0;
			for(int i=1;i<=n;i++){
				if(v-a[i]<=0)continue;
				if(vis[v-a[i]])cnt++;
			}
			cnt/=2;
			ans=max(ans,cnt);
		}
	}	
	printf("%d",ans);
	return 0;
}
```



---

## 作者：TLEWA (赞：0)

[题目传送门（这道题真的是蓝题吗？？？）](https://www.luogu.com.cn/problem/CF1121B)

这道题目的 $a_i$ 范围很小，所以之间用一个桶来统计就可以了

我们可以计算出每个数与比它下标大的数的和，把桶对应下标的数值加一（因为数字互不相同，所以这么做可以保证不重复），最后统计一下桶里的最大值就可以了。

AC 代码：
```cpp
#include<bits/stdc++.h>
#define MAXN 1005
#define MAX_AI 100005

using namespace std;

int arr[MAXN],barrel[MAX_AI*2]; //桶要开到两倍最大值

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0); //解除流绑定
	
	int n;
	cin >> n;
	for(int i=0;i!=n;++i) cin >> arr[i];
	
	for(int i=0;i!=n;++i) {
		for(int j=i+1;j<n;++j) { //避免重复
			++barrel[arr[i]+arr[j]];
		}
	}
	
	int maxn=0;
	
	for(int i=0;i!=MAX_AI*2;++i) { //遍历整个桶
		maxn = max(maxn,barrel[i]);
	}
	
	cout << maxn;
	return 0;
}

```


---

## 作者：Maxwang (赞：0)

### 前言
这道题的题意翻译十分简洁，以至于本蒟蒻第一次看题时都没有明白题目的含义，在这里给大家简单阐述一下。

---
#### 题目背景

（此部分与做题无关，可以略过。）

迈克决定在一所小学教孩子们编程。他知道要让那个年龄的孩子对代码感兴趣不是件容易的事。所以他决定给每个孩子两个糖果。

#### 题目描述

迈克有 $n$ 个糖果，分别为 $a_1,a_2,a_3 \ldots a_n$，他要给每个小朋友两块糖果，也就是 $a_i+a_j$ 个糖果，但是如果迈克给另一个小朋友 $a_p+a_q$个糖果，且 $a_i+a_j \neq a_p+a_q $，这个小朋友就会沮丧，现在杰克让您求最多会有多少位小朋友不沮丧，也就是求出有最多个相同的 $a_i+a_j$ 的数量。
#### 数据范围
$ 2≤n≤1000 $

$1≤a_i≤10^5$

#### 样例解释
在样例一中 有三对 $a_i+a_j$ 相同，分别为 $9+2=11,8+3=11,7+4=11$。
相等的数量最多，所以答案是 $3$。

***
### 主要思路

首先，这道题目的数据范围不是太大，所以说通过暴力枚举的方法就可行。

其次，我们可以用**桶**的思想来解决这个问题。

我们可以利用桶将所有可能的 $a_i+a_j$ 的结果统计一下，最后出现次数最多的就是答案啦。

具体细节会在代码注释里体现出来，务必仔细阅读哦。

### 完整代码和细节
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>//调用memset时使用 
using namespace std;
#define rint register int//register->玄学优化 
#define isnum(x) ('0' <= (x) && (x) <= '9')
template<typename tint>
inline void readint(tint& x) {//快速读入 
	int f = 1; char ch = getchar(); x = 0;
	for(; !isnum(ch); ch = getchar()) if(ch == '-') f = -1;
	for(; isnum(ch); ch = getchar()) x = x * 10 + ch - '0';
	x *= f;
}
const int MAXN = 1e4 + 99;//题目n的范围 
const int MAXM = 2e5 + 99;//桶的大小 

int a [ MAXN ],tong[ MAXM ];
int n,ans=-1;
int main()
{
	memset( a , 0 , sizeof(a) );//陋习不改 
	memset( tong , 0 , sizeof(tong) );//这两行因为全局变量的缘故即使删掉也不会有影响
	readint(n);
	for(rint i = 1 ; i <= n ; i++)
	{
		readint(a[i]);//读入 
	}
	for(rint i = 1 ; i <= n ; i++)
	{
		for(rint j = i + 1; j <= n; j++)
		{
			tong [ a[i] + a[j] ]++;//枚举每种和的可能 
		}
	}
	for(rint i = 1;i <= MAXM - 99; i++)
	{
		ans= max( ans , tong[i] );//寻找出现次数最多的那个 
	}
	printf( "%d\n" , ans );//输出答案 
	return 0;
} 
```
### 补充说明
这里有两个细节需要强调一下。

1.这里要从 $i+1$ 开始枚举，不然会重复。

```cpp
for(rint i = 1 ; i <= n ; i++)
	{
		for(rint j = i + 1; j <= n; j++)//从i+1开始枚举以防重复 
		{
			tong [ a[i] + a[j] ]++;//枚举每种和的可能 
		}
	}
```
2.关于桶的大小

由于每个数最大就是 $10^5$，因此它们的和最大就是 $2\times 10^5$，所以桶就开到这么大即可。
```cpp
const int MAXM = 2e5 + 99;//桶的大小 

int a [ MAXN ],tong[ MAXM ];
```
 华丽的结束。
 

---

## 作者：WRuperD (赞：0)

简单题

![](https://cdn.luogu.com.cn/upload/image_hosting/5phf13om.png)

所以，因为 $a_i$ 互不相同，所以发现对于一种数的和 $k$，只有唯一的一对 $a_i+a_j=k$，因此不用考虑选数产生后效性。考虑开一个桶记录每个和出现的次数，最终取最大值即可。

```cpp
// Problem: Mike and Children
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1121B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 1e4+10;
int a[MAX];
map <int, int> f;
void solve(){
	int n = read();
	for(int i = 1; i <= n; i++)	a[i] = read();
	for(int i = 1; i <= n; i++)	for(int j = i + 1; j <= n; j++)	f[a[i] + a[j]] ++;
	int maxn = 0;
	for(int i = 1; i <= n; i++)	for(int j = i + 1; j <= n; j++)	maxn = max(maxn, f[a[i] + a[j]]);
	write(maxn), endl;
}

signed main(){
	int t = 1;
	while(t--)	solve();
	return 0;
}
```

---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，不难发现可以用桶来统计每个和出现的次数，最终取最大值即可。但是需要**注意**，桶的大小要开到 $2 \times 10^5$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,a[1005],b[200005],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			b[a[i]+a[j]]++;
		}
	}
	for(int i=1;i<=200000;i++){
		ans=max(ans,b[i]);
	}
	cout<<ans;
	return 0;
}
```


---

