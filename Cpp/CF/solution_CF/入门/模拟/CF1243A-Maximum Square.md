# Maximum Square

## 题目描述

### 题意简述

给定 $n$ 个正整数 $a_1,a_2,···,a_n$。请你从中选取 $x$ 个正整数 $b_1,b_2,···,b_x$，使得其满足：

$$b_i\geq x(1\leq i \leq x)$$

您需要最大化 $x$。

## 样例 #1

### 输入

```
4
5
4 3 1 4 5
4
4 4 4 4
3
1 1 1
5
5 5 1 1 5
```

### 输出

```
3
4
1
3
```

# 题解

## 作者：伟大的王夫子 (赞：2)

令我感到十分疑惑的是，题解里都是二分等一些乱搞做法，竟然没有
最简单的 $O(n)$

令 $cnt_i$ 为该序列中 $ \ge i$ 的数的个数。于是一个 $i$ 能够成为答案充要条件就是 $cnt_i \ge i$。而 $cnt$ 数组可以用后缀和 $O(n)$ 求出，于是正解就诞生了。

```cpp
#include <cstdio>
#include <cctype>
#include <queue>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <assert.h>
#include <set>
#include <cmath>
using namespace std;
template <class T>
inline void Rd(T &x) {
	x = 0;
	bool f = 0;
	char ch = getchar();
	while (!isdigit(ch)) f |= ch == '-', ch = getchar();
	while (isdigit(ch)) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	if (f)
		x = -x;
}
int n, a[1005], cnt[1005];
int main() {
	int T;
	Rd(T);
	while (T--) {
		Rd(n);
		for (int i = 1; i <= n + 1; ++i) cnt[i] = 0;
		for (int i = 1; i <= n; ++i) Rd(a[i]), ++cnt[a[i]];
		for (int i = n; i; --i) cnt[i] += cnt[i + 1];
		for (int i = n; i; --i) 
			if (cnt[i] >= i) {
				printf("%d\n", i);
				break;
			} 
	}
}
```

---

## 作者：lhy339 (赞：2)

#### 一、题意：给定n个长度为f i的木板，求这n个木板最大可以拼成的正方形。
### 二、看题面后，首先想到贪心，先将f i从大到小排序，然后在vis数组上标记，最后我们可以从1~n枚举正方形的长度，显然可以二分答案。
### 三、code

```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
#define N 1001
using namespace std;
int n,m,t,k,f[N];
bool vis[N][N];
inline int read()
{
	int f=1,res=0;char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-') f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0') res=(res<<1)+(res<<3)+(ch^48),ch=getchar();
	return f*res;
}
inline bool cmp(int x,int y)
{
	return x>y;
}
inline bool check(int x)
{
	for(register int i=1;i<=x;i++)
		for(register int j=1;j<=x;j++)
			if(!vis[i][j])
				return false;
	return true;
}
int main()
{
	t=read();
	while(t--)
	{
		memset(vis,0,sizeof(vis));
		n=read();
		for(register int i=1;i<=n;i++)
			f[i]=read();
		sort(f+1,f+n+1,cmp);
		for(register int i=1;i<=n;i++)
			for(register int j=1;j<=f[i];j++)
				vis[i][j]=true;
		int l=0,r=n,mid,ans;
		while(l<=r)
		{
			mid=(l+r)>>1;
			if(check(mid))
				l=mid+1,ans=mid;
			else
				r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```
### 四、这个题还可以用zty算法（一个机房大佬）可以将一个$O(N^{2})$算法降到 O(KN)(其中K为常数),每次随机一个点，向这个点的左侧暴力扫K位，（正确性不能保证，如果是构造的数据可能被卡）。
### 五、CSP-S 2019 rp++


---

## 作者：虫洞吞噬者 (赞：1)

题意:给定$N$个长度为$H$的板子，求能够拼成的最大正方形的边长。

看到题面，不妨先分析一下。因为是正方形，所以它的边长不会超过$N$。而最小的正方形边长一定为$1$，由此可以比较轻易地得出最终答案的范围。嗯，这就比较显然，由于答案具有单调性，由此我们想到，可以用二分答案来确定长方形的边长。然后判断$H$大于当前边界的板子有几个，以此作为二分的$check()$函数。

code:
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int t,n,ans;
int num[10010];
bool check(int qaq)
{
	int sum=0;
	for(int i=1;i<=n;++i)
		if(num[i]>=qaq)++sum;
	return sum>=qaq;
}//判断满足这个边长的板子有几个，不难想出只有sum>=qaq时答案才成立
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		int l=0,r=n;
		for(register int i=1;i<=n;++i)
			scanf("%d",&num[i]);
		while(l<=r)
		{
			int mid=(l+r)/2;
			if(check(mid))
			{
				ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}//万能二分答案的板子建议新手学习记忆
		printf("%d\n",ans);
	}
	return 0;
}
```


这样就是一个二分的板子题qwq

---

## 作者：御前带刀侍卫 (赞：1)

### 0.题目链接

[CF 1243  A  in Luogu](https://www.luogu.org/problem/CF1243A)

### 1。读题

给你n个长短不一的木板，让你把他们并排纵列，

用俄罗斯方块的方式取底部的最大正方形的边长

（div2 A题，向来难点都在读题QAQ）

### 2. 代码

还是比较显而易见，

**想产生一块边长为x的正方形，必须有x条以上的高度大于x的木板**

n<=1000

n^2 暴力程序：

（nlogn二分/O(n)递推也能过，但是毕竟是CF,打代码一定要快）

```cpp
#include<iostream>
#include<stdio.h>

using namespace std;

int n;

int a[10000];

int solve(){
	cin>>n;
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1000;i>0;i--){     //枚举边长 （有大到小） 
		int cnt=0;
		for(int j=0;j<n;j++){    //统计合法木板数 
			if(a[j]>=i)cnt++;
		}
		if(cnt>=i){				//以为是由大到小，因而可以直接输出第一个 
			printf("%d\n",i);
			return 0;
		}
	}
}

int main(){
	int q;
	cin>>q;
	while(q--){
		solve();
	}
	return 0;
}
```



---

## 作者：golden_brick (赞：0)

### 题目大意

给你$n$个长短不一的木板，让你把他们并排纵列，

用俄罗斯方块的方式取底部的最大正方形的边长

---

### 思路

首先想到用二分选木板，

但掐指一算复杂度 $\Theta(k\times n\log n) $，显然跑得过。

首先，我们按照木板长度从大到小排序。

然后先处理出第一块木板做切除正方形的大小的长度。

接着从第二个木板开始，一次遍历每一块木板，比较加入这块木板后，是否大于原来可切出正方形的大小。

1. 如大于，则更新答案。
2. 否则，跳出循环，输出答案

---

### Code

```cpp
#include <bits/stdc++.h>
#define il inline
#define INF 0x3f3f3f3f
#define I using
#define love namespace
#define bianbian std
I love bianbian;
typedef long long ll;
const int N = 1e3 + 5;
int a[N];
int ans;
bool cmp(int a, int b) { return a > b; }
signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        sort(a + 1, a + 1 + n, cmp);
        ans = min(a[1], 1);
        for (int i = 2; i <= n; i++)
        {
            if (ans > min(i, a[i]))
                break;
            ans = min(i, a[i]);
        }
        cout << ans << endl;
    }
    return 0;
}
/*
input:
4
5
4 3 1 4 5
4
4 4 4 4
3
1 1 1
5
5 5 1 1 5
anser:
3
4
1
3
output:
3
4
1
3

Sample AC
*/
```

---

## 作者：Digital_Sunrise (赞：0)

## CF1042A题解

[CF题解合集(包括本场)](https://www.luogu.com.cn/blog/yl2330/I-Love-YR-Forever)

[Markdonw源代码](https://yhwh-group.coding.net/public/codingwiki/files/git/files/master/blog/CF1243/A.Markdown)


### 思路

这题题意算翻译的比较清楚的了。

看完题面，首先想到用二分选木板，

但掐指一算暴力复杂度 $O(k\times n\log n)$ ，显然跑得过，还跑得飞快。

首先，我们按照木板长度从大到小排序。

然后先处理出第一块木板做切除正方形的大小的长度。

接着从第二个木板开始，一次遍历每一块木板，比较加入这块木板后，是否大于原来可切出正方形的大小。

1. 如大于，则更新答案。

2. 否则，跳出循环，输出答案（因为是排序过的，所以后面不会再更新答案了）

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3 + 5;

int T,a[maxn];
int ans;

bool cmp(int a, int b)
{return a > b;}

int main()
{
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		for (int i = 1 ; i <= n ; i ++)
			cin >> a[i];
		sort(a + 1, a + 1 + n, cmp);
		ans = min(a[1], 1);
		for (int i = 2 ; i <= n ; i ++)
		{
            if(ans > min(i, a[i]))
                break;
			ans = min(i, a[i]);
		}
		cout << ans << endl;
	}
	return 0;
}

```

### 写在最后

如果您希望卡到最优解，我们建议您使用 [吴神快读](https://www.luogu.com.cn/paste/hqpywwhz) （目前的最优解就是我的同学加了此快读）

---

## 作者：qfpjm (赞：0)

# 题解

- 虽然这题正解是二分，但是貌似暴力跑得比二分快。

1. 首先，从大到小排序。

1. 然后先算出第一块木板做切除正方形的大小的长度。

1. 接着，从第二块木板开始，比较加入这块木板后，是否大于原来可切出正方形的大小。大于，更新；小于，跳出循环，输出答案。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int k, a[10005];

int cmp(int a, int b)
{
	return a > b;
}

int main()
{
	cin >> k;
	while (k --)
	{
		int n;
		cin >> n;
		for (int i = 1 ; i <= n ; i ++)
		{
			scanf("%d", &a[i]);
		}
		sort(a + 1, a + 1 + n, cmp);
		int ans = min(a[1], 1);
		for (int i = 2 ; i <= n ; i ++)
		{
			if (ans <= min(i, a[i]))
			{
				ans = min(i, a[i]);
			}
			else
			{
				break;
			}
		}
		cout << ans << endl;
	}
	return 0;
}

```


---

## 作者：子谦 (赞：0)

就是把给的数作为边长拼一个正方形


# 排序！排序！排序！
------------
那我们完全可以排一个减序，if( a[i-1]<i ) 说明到这里就无法拼更大的正方形了，所以找到了最大正方形，输出就好。



```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,a[1010],flag;
int cmp(int a,int b){
	return a>b;
}
int main()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++){
			if(a[i]<i){
				flag=1;
				printf("%d\n",i-1);
				break;
			}
		}
		if(flag==0)printf("%d\n",n);   //特判它本身就是正方形的情况
		flag=0;
	}
}
```


---

