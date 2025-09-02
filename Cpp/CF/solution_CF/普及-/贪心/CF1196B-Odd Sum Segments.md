# Odd Sum Segments

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \dots, a_n $ . You want to split it into exactly $ k $ non-empty non-intersecting subsegments such that each subsegment has odd sum (i. e. for each subsegment, the sum of all elements that belong to this subsegment is odd). It is impossible to rearrange (shuffle) the elements of a given array. Each of the $ n $ elements of the array $ a $ must belong to exactly one of the $ k $ subsegments.

Let's see some examples of dividing the array of length $ 5 $ into $ 3 $ subsegments (not necessarily with odd sums): $ [1, 2, 3, 4, 5] $ is the initial array, then all possible ways to divide it into $ 3 $ non-empty non-intersecting subsegments are described below:

- $ [1], [2], [3, 4, 5] $ ;
- $ [1], [2, 3], [4, 5] $ ;
- $ [1], [2, 3, 4], [5] $ ;
- $ [1, 2], [3], [4, 5] $ ;
- $ [1, 2], [3, 4], [5] $ ;
- $ [1, 2, 3], [4], [5] $ .

Of course, it can be impossible to divide the initial array into exactly $ k $ subsegments in such a way that each of them will have odd sum of elements. In this case print "NO". Otherwise, print "YES" and any possible division of the array. See the output format for the detailed explanation.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
3
5 3
7 18 3 14 1
5 4
1 2 3 4 5
6 2
1 2 8 4 10 2
```

### 输出

```
YES
1 3 5
NO
NO
```

# 题解

## 作者：HoshizoraZ (赞：3)

**这道题可以用类似贪心的策略做。**

首先，分析一下题面：

大意：把 $n$ 个数分成连续 $k$ 部分，使得每一部分和都是奇数。

我们的策略是：前面分的组别长度尽量短。

换种说法就是，一碰到和是奇数的时候就分成一组。

因为如果我们按照这个策略分，如果分不出 $k$ 组，那么一定无解；

如果超过了 $k$ 组，那么就将第 $k$ 组后面的所有组整到第 $k$ 组去，最后特殊判断第 $k$ 组的奇偶性即可。

小技巧：**前缀和**

前缀和可以通过 $O(n)$ 的预处理，$O(1)$ 求出一段区间的和。

代码如下：

```cpp
#include <cstdio>
typedef long long ll;
 
ll q, n, k, a, ans[200010], sum[200010], cnt, last;
// last 记录上一个区间的右端点
 
int main(){
	
	scanf("%lld", &q);
	while(q--){
		cnt = last = 0;
		scanf("%lld%lld", &n, &k);
		
		for(ll i=1; i<=n; i++){
			scanf("%lld", &a);
			sum[i] = sum[i - 1] + a;		// 前缀和
		}
 
		for(ll i=1; i<=n; i++){
			if(cnt + 1 == k) break;			// 分了 k-1 部分就跳出，把剩下的全部归为第 k 部分
			if((sum[i] - sum[last]) & 1){
				ans[++cnt] = i;
				last = i;
			} 
		}
		
		if(cnt + 1 == k && ((sum[n] - sum[last]) & 1)){	//注意特判最后一组
			puts("YES");
			for(ll i=1; i<=cnt; i++)	
				printf("%lld ", ans[i]);
			printf("%lld\n", n);
		}
		else puts("NO");
	}
 
	return 0;
}
```

---

## 作者：__shadow__ (赞：2)

【问题分析】 

本题考了奇数。

由此想到以下定律：

奇数+偶数=奇数；

奇数+奇数=偶数；

偶数+偶数=偶数；

所以偶数可以忽略不计，只有奇数可以对结果产生影响, 
所以我们只要注意奇数即可。

经过思考可得奇数的个数至少为 $k$ 个且比 $k$ 多的个数为偶数，此时多出的奇数可组成偶数，对结果不产生影响。

【设计程序】
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<cstdio>
#include<queue>
using namespace std;
const int N = 2 * 1e5;
int a[N];//用来存每一个奇数的位置
int n, k, t, sum;//sum是奇数的总个数
int main()
{
	int Q;//有Q组数据
	scanf ("%d", &Q);//输入Q
	while (Q--)
	{
		sum = 0;//归零
		scanf ("%d%d", &n, &k);
		for (int i = 1;i <= n; i++)
		{
			scanf ("%d", &t);//输入这个数
			if (t % 2 != 0)//如果是奇数
				a[++sum] = i;
           			//个数加1，把位置存下来
		}
		if (sum < k || (sum - k) % 2 != 0)
		//如果奇数个数少于k或者比k多奇数个
		{
			printf ("NO\n");//输出不行
			continue;//开始下一组数据
		}
		printf ("YES\n");//输出可行
		for (int i = 1;i <= k - 1; i++)//输出前k – 1 个奇数的位置
			printf ("%d ", a[i]);
		printf ("%d\n", n);//最后一个位置肯定在n的位置
	}
	return 0;
}
```

【代码调试】

1.	测试样例

2.	自测数据（边界值，特殊值）

自测：

输入： 

5

3 2

2 2 2

5 1

1 1 1 1 1

6 2

1 1 1 1 1 1

6 3

1 1 1 3 5 1

5 2

1 1 1 1 1

输出：

NO

YES

5

YES

1 6

NO

NO


------------
完结撒花

---

## 作者：xh001 (赞：1)

# 题意
首先给定一个整数 $t$ 表示有 $t$ 组数据，每组数据包含两个数 $n$，$k$ 和一个长度为 $n$ 的序列 $a$，$n$ 为序列中数的个数，$k$ 为需要分的组数（每组的和为奇数），求是否能分成 $k$ 组以及每组末尾的下标。
# 思路
题目要求分组使每组的和为奇数，和偶数没关系，只要统计奇数就行了，所以我们新开一个数组记录序列中奇数的位置，只有奇数的个数至少为 $k$ 个且比 $k$ 多的个数为偶数时才有解，此时将前 $k-1$ 个奇数分到 $k-1$  组中，剩下的奇数全部分到第 $k$ 组。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//好习惯。 
const ll mn=2e18;
ll a[200001],cnt;//记录奇数的位置和总数。 
ll t,n,k,x;
inline ll read()
{
	ll k=0,f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
	return f?-k:k;
}
int main()
{
	t=read();
	while(t--)
	{
		cnt=0;
		n=read();
		k=read();
		for(ll i=1;i<=n;i++)
		{
			x=read();
			if(x%2==1) a[++cnt]=i;
		}
		if((cnt-k)%2==1 || cnt<k)//分不出k组。 
		{
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
		for(ll i=1;i<k;i++)//分组。 
		{
			cout<<a[i]<<' '; 
		}
		cout<<n<<endl;//最后一组结尾一定是n。 
	}
	return 0;
}
```


---

## 作者：lygmh (赞：1)

## 做题经历
第一眼看到题目，爆搜？？？！！！
第二眼看到题目，这是到大水题。

## 题目分析
奇数+奇数=偶数；
奇数+偶数=奇数；

既然是分组，使每组的和为奇数，那么就和偶数没什么关系了，只要统计奇数就行了。

先统计奇数的个数，如果奇数的个数小于k，那么直接输出NO。
如果奇数的个数大于k，不妨把最后两个奇数合并成偶数（在同一组里）直到奇数的个数等于k，输出YES和解，否则也输出NO。

关于输出解，输出前k-1个奇数的位置，和n。

## 代码附上
```cpp
/*by G_M_H*/
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<utility>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
int line[200005];
int n,k;
int main() {
	int q;
	scanf("%d",&q);
	while(q--){
		scanf("%d%d",&n,&k);
		int ans=0;
		for(register int i=1;i<=n;i++){
			scanf("%d",&line[i]);
			if(line[i]%2) ans++;
		}
		if((ans<k)||(ans-k)%2){
			printf("NO\n");
		}else{
			printf("YES\n");
			int pos=1;
			while(k>1){
				if(line[pos]%2){
					printf("%d ",pos);
					k--;
				}
				pos++;
			}
			printf("%d\n",n);
		}
	}
	return 0;
}
```

---

## 作者：xukuan (赞：1)

这题的翻译比较不负责任，大家可以看一下我的翻译：盘[https://www.luogu.org/blog/xukuan/translation-cf1196b](https://www.luogu.org/blog/xukuan/translation-cf1196b)

让奇数有sum个，

如果$sum \geq k$并且$ sum \mod 2=k \mod 2$就有解，否则无解

输出方案时找到前$k-1$个奇数的位置并输出即可

代码：
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll T,n,k,sum,len,a[200010],ans[200010];

inline ll read(){
	ll x=0,tmp=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') tmp=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return tmp*x;
}

inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	ll y=10,len=1;
	while(y<=x){
		y=(y<<3)+(y<<1);
		len++;
	}
	while(len--){
		y/=10;
		putchar(x/y+48);
		x%=y;
	}
}

int main(){
	T=read();
	while(T--){
		n=read(); k=read(); sum=len=0;
		for(ll i=1; i<=n; i++){
			a[i]=read()&1;
			if(a[i]) sum++;
		}
		if(sum-k>=0&&(sum-k)%2==0){
			printf("YES\n");
			for(ll i=1; i<=n&&k>1; i++){
				if(a[i]){
					write(i); putchar(' ');
					k--;
				}
			}
			write(n);
		}
		else printf("NO");
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：j1ANGFeng (赞：0)

### 分析
可以让前面 $k-1$ 段尽可能短。

因为如果这个数列符合要求，每段数字的数量不同也是符合题意的。

如果这样分不出 $k-1$ 段，就无解。

否则判断第 $k$ 段是否符合要求，并输出。

### AC CODE
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<cmath>
#define int unsigned long long
#define N 10000001
#define inf 2147483647
#define in inline
#define re register
using namespace std;
inline long long rd(){char a=getchar();long long f=1,x=0;while(a<'0'||a>'9'){if(a=='-')f=-1;a=getchar();}while(a>='0'&&a<='9'){x=(x<<3)+(x<<1)+(long(a^48));a=getchar();}return f*x;}in void qwqqwq(long long x){if(x!=0){qwqqwq(x/10);putchar(x%10^48);}return;}inline void wt(long long x){if(x==0){putchar('0');return;}if(x<0){x=-x;putchar('-');}qwqqwq(x);return;}
int a[N],qz[N],ans[N];
signed main(){
	int t=rd()+1;
	while(--t){
		int n=rd(),k=rd(),cnt=1,la=0;
		for(int i=1;i<=n;++i)
		  a[i]=rd(),qz[i]=qz[i-1]+a[i];
		for(int i=1;i<=n;++i){
			if(cnt==k)
			  break;
			if((qz[i]-qz[la])&1){
				ans[cnt++]=i;
				la=i;
			}
		}
		if((qz[n]-qz[la])&1){
			puts("YES");
			for(int i=1;i<cnt;++i)
			  wt(ans[i]),putchar(' ');
			wt(n);
			putchar('\n');
		}else puts("NO");
	}
	return 0;
}
```

---

