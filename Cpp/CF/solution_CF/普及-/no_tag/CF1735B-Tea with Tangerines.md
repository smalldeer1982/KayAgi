# Tea with Tangerines

## 题目描述

There are $ n $ pieces of tangerine peel, the $ i $ -th of them has size $ a_i $ . In one step it is possible to divide one piece of size $ x $ into two pieces of positive integer sizes $ y $ and $ z $ so that $ y + z = x $ .

You want that for each pair of pieces, their sizes differ strictly less than twice. In other words, there should not be two pieces of size $ x $ and $ y $ , such that $ 2x \le y $ . What is the minimum possible number of steps needed to satisfy the condition?

## 说明/提示

In the first test case, we initially have a piece of size $ 1 $ , so all final pieces must have size $ 1 $ . The total number of steps is: $ 0 + 1 + 2 + 3 + 4 = 10 $ .

In the second test case, we have just one piece, so we don't need to do anything, and the answer is $ 0 $ steps.

In the third test case, one of the possible cut options is: $ 600,\ 900,\ (600 | 700),\ (1000 | 1000),\ (1000 | 1000 | 550) $ . You can see this option in the picture below. The maximum piece has size $ 1000 $ , and it is less than $ 2 $ times bigger than the minimum piece of size $ 550 $ . $ 4 $ steps are done. We can show that it is the minimum possible number of steps.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1735B/28837ca57e9f20f873e71a5d21feab7da5248146.png)

## 样例 #1

### 输入

```
3
5
1 2 3 4 5
1
1033
5
600 900 1300 2000 2550```

### 输出

```
10
0
4```

# 题解

## 作者：minecraft_herobrine (赞：2)

题意：有 $n$ 块橘子皮，每块大小是 $a[i]$。你可以做一次操作将一块橘子皮分成任意大小的两块，整个过程橘子皮总量是不变的。问要使任意两块橘子皮 $x,y\ (x\le y)$ 都满足 $2\times x<y$ 的最小操作数。

如果找到初始状态的橘子皮中最小的那个，将其它皮都分成严格小于最小橘子皮大小的二倍一定是最优的。因为要是分割了初始最小的橘子皮必然导致额外操作。

所以对所有橘子皮排序，设 $k=2\times a[1]-1$，对每个其它橘子皮 $x$ 的操作数是 $\lceil {a[i]}/k \rceil$。统计答案即可

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+10;
int a[MAXN];
int main()
{
	int T,n,m,i,j;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(i=1;i<=n;i++) scanf("%d",&a[i]);
		sort(a+1,a+n+1);
		int res=0;
		if(a[1]==1)
		{
			for(i=2;i<=n;i++) res+=a[i]-1;
			printf("%d\n",res);
			continue;
		}
		for(i=2;i<=n;i++)
		{
			int k=a[1]*2-1;
			int t=a[i]/k+(a[i]%k!=0);
//			printf("%d ",t);
			res+=t-1;
		}
		printf("%d\n",res);
	}
	return 0;
}
```

---

## 作者：ScottSuperb (赞：2)

## 解法分析
简单贪心。为了满足分割后每块皮都小于最小块 $size$ 的两倍，我们只需将每块皮分割成若干个 $(size\times2-1)$ 即可。  
注意这样分只是为了得到答案，真正分的时候如果按这种思路分出了更小的皮，只需从任意另两块上取一部分给它即可，所以不会影响最终答案。  
在代码实现时将每块皮大小除以 $(size\times2-1)$ 的商向上取整就是应分成的块数，减去 $1$ 就是步数，而向上取整的加一与减一是可以抵消的。
## 代码
读写函数定义已省略。
```cpp
#include <bits/stdc++.h>

using namespace std;

int a[105];

int main() {
  int t = read(), n, size, ans;
  while (t--) {
    int n = read(), ans = 0;
    for (int i = 0; i < n; ++i) a[i] = read();
    sort(a, a + n);
    size = (a[0] << 1) - 1;
    for (int i = 1; i < n; ++i) ans += (a[i] - 1) / size /*+ 1 - 1*/;
    write(ans);
  }
  return 0;
}
```

---

## 作者：binaryBard (赞：1)

读题点 [这里](https://www.luogu.com.cn/problem/CF1735B)

更好的阅读体验点 [这里](https://blog.jerryz.com.cn/article/solution-CF1735B)

# 题意简述

有 $n$ 块橘子皮，每块大小是 $a_i$。你可以做一次操作将一块橘子皮分成任意大小的两块，整个过程橘子皮总量是不变的。问要使任意两块橘子皮 $x,y\ (x\le y)$ 都满足 $2x<y$ 的最小操作数。

# 思路分析

为使操作数最小，我们可以将划分橘子皮的大小定为 $minn \times 2-1$ （ $minn$ 为所有橘子皮长度的最小值）。

特别地，若当前橘子皮的长度 $a_i \bmod (minn \times 2-1)=0$,则答案需要减去 $1$。

# 代码

```C++
#include<bits/stdc++.h>
using namespace std;
#define N 105

int T,n,a[N];

int main(){
    cin>>T;
	while(T--){
		cin>>n;
		int minn=0x7fffffff,ans=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			minn=min(a[i],minn);
		}
		for(int i=1;i<=n;i++){
			ans+=a[i]/(minn*2-1);
			if(a[i]%(minn*2-1)==0) ans--;
		}
		cout<<ans<<endl;
	}
	//system("pause");
	return 0;
}
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

## 题意

有 $n$ 块橘子皮，每块大小是 $a_i$，想把它们切成若干块，使任意两块橘子皮中小的一块的 $2$ 倍大于大的一块，问最少切多少次？

首先我们对橘子数列大小做出排序。

以最小的一块为标准，如果用其他方法一定会漏算。

接着用循环扫描另外 $n-1$ 块，求出每块里面有几个第一块，记得向上取整。


由于块数比切的次数多 $1$，所以每个的结果减去 $1$。

上代码！
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
double a[110];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+n+1);
		int ans=0;
		double res=a[1]*2-1;
		for(int i=2;i<=n;i++)
		{
			ans+=ceil(a[i]/res)-1;
		}
		cout<<ans<<endl;
	}
	return 0;
} 
```


---

## 作者：CR7_houyetong (赞：0)

# 题意
- 有 $n$ 片橘子皮，第 $i$ 片橘子皮的大小是 $a_i$。
- 现在可以把一片橘子皮分成任意大小的两片，显然，所有橘皮的大小之和是固定的，也就是说，不能随意丢掉橘皮~~破坏环境~~。
- 求最终不存在任何两块大小分别为 $x$ 和 $y$ 的橘子皮的关系为 $2x≤y$  的最小操作次数。
- 最后，本题有 $t$ 组独立的询问，$1≤t≤100$，$1≤n≤100$，$1≤a_1≤a_2≤\cdots≤a_n≤10^7$。

# 分析
显然这题的算法是贪心。为了使操作次数最少，我们取这些橘子皮大小的最小值 $a_1$，因为题目说了这是一个有序数列，然后要满足 $2x≤y$，所以大小最大的那片橘子皮大小不能超过 $a_1×2-1$，最后用一个累加器累加每个 $\lceil \frac{a_i}{a_1×2-1} \rceil-1$ 即可。

分析可能比较简单，如果要详细些的话建议看@[安舒阳](https://www.luogu.com.cn/blog/ASY/solution-cf1735b)的题解。

# 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t,n,i,s;
double a[1000010];
signed main(){
	cin>>t;
	while (t--){
		s=0;
		cin>>n;
		for (i=1;i<=n;i++)
		  cin>>a[i];
		for (i=1;i<=n;i++)
		  s=s+ceil(a[i]/(a[1]*2-1))-1;
		cout<<s<<endl;
	}
	return 0;
}
```

---

## 作者：alm_crax (赞：0)

## [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1735B)

## [CF原题传送门](https://codeforces.com/problemset/problem/1735/B)

## 题意
因为翻译有误，所以我重新翻译了一个：

有 $n$ 块橘子皮，第 $i$ 块大小为 $a_i$ ，一次操作可以将一块橘子皮分成任意大小的两块。在整一个操作过程中，橘子皮总大小不变。求最终不存在任何两块大小分别为 $x$ 和 $y$ 的橘子皮的关系为 $2x \leq y$ 的最小操作次数（即任意两个橘子皮关系为 $2x>y$ ）。

## 思路
简单思路：

$a_1 \cdots a_n$ 中最小的一个作为基准判断 $2x>y$ ，通过块数求操作数。

具体做法：

找一个 $a$ 中最小的数，记为 $min$ ，将 $min\times2-1$ （下面记为 $max$ ），代表最大的一块橘子皮大小的极限，将 $a_i / max$ 向上取整再 $-1$，因为求的是分出来的块数，所以 $-1$ 求操作数，最后把每一个求出来的操作数加起来，就好了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s,k;
double a[105],mn;//因为要向上取整，所以用double
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		mn=1e9;
		s=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lf",&a[i]);
			if(mn>a[i])
			{
				mn=a[i];
				k=i;
			}
		}
		mn=mn*2-1;
		for(int i=1;i<=n;i++)
		{
			if(a[i]==a[k])//优化用，可以不写
			{
				continue;
			}
			s+=ceil(a[i]/mn)-1;
		}
		printf("%d\n",s);
	}
	return 0;
}
```


---

## 作者：安舒阳 (赞：0)

本题主要思路是贪心，这里不再分析题意~~如果你像我一样一开始看翻译没看懂那么建议你去看一下样例解释~~。

直接分析。对于两个橘子皮 $x$ 和 $y$，要满足 $ 2x \lt y $，我们可以通过分割的方法使得一方的大小下降（也就是分割成两个小块）。这里并没有规定 $x$ 和 $y$ 的大小，但是显然，我们把小的那方作为 $x$ 大的那方 $y$ 是最好的，那么对于一堆数 $ a_1,a_2,\ldots,a_n $ 显而易见将最小的数也就是 $a_1$ 作为所有比较中的 $x$ 最好（题目中有说是有序数列）。

那么对于每一次比较，如果 $ 2x \ge y $，就需要考虑分割了。

对于每次分割，我们可以分割出一个严格符合要求的数，即分割为 $b=2x-1$ 和 $c=a-b$（此处 $a$ 表示原本大小，$b$ 表示第一个被分割后的数，$c$ 表示第二个被分割后的数）。那么这么一来每次就要分割 $\lfloor \frac{a_i}{2x} -1 \rfloor$ 次。

只不过需要注意当 $a_i$ 能被 $2x-1$ 整除时，会少分一次。**这是里因为我们向下取整之后算的是包含最后剩下的一段 $c$ 的段数减一，最后一段的 $c$ 是一个大于零的数，但是当能被整除时最后一段的 $c$ 刚好没有**，所以要减一。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		int data[105];
		for(int i=0;i<n;i++){
			scanf("%d",&data[i]);
		}//输入
		
		const int should=data[0]*2-1;//我们要的每段长度
		int ans=0;
		for(int i=1;i<n;i++){
			int ttmp=0;
			if(data[i]%should==0){
				ttmp=1;
			}//如果能被整除记得减一
			ans+=data[i]/should-ttmp;//+ttmp;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

