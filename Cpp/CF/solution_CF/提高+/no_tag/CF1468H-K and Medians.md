# K and Medians

## 题目描述

Let's denote the median of a sequence $ s $ with odd length as the value in the middle of $ s $ if we sort $ s $ in non-decreasing order. For example, let $ s = [1, 2, 5, 7, 2, 3, 12] $ . After sorting, we get sequence $ [1, 2, 2, \underline{3}, 5, 7, 12] $ , and the median is equal to $ 3 $ .

You have a sequence of $ n $ integers $ [1, 2, \dots, n] $ and an odd integer $ k $ .

In one step, you choose any $ k $ elements from the sequence and erase all chosen elements except their median. These elements do not have to go continuously (gaps are allowed between them).

For example, if you have a sequence $ [1, 2, 3, 4, 5, 6, 7] $ (i.e. $ n=7 $ ) and $ k = 3 $ , then the following options for the first step are possible:

- choose $ [1, \underline{2}, 3] $ ; $ 2 $ is their median, so it is not erased, and the resulting sequence is $ [2, 4, 5, 6, 7] $ ;
- choose $ [2, \underline{4}, 6] $ ; $ 4 $ is their median, so it is not erased, and the resulting sequence is $ [1, 3, 4, 5, 7] $ ;
- choose $ [1, \underline{6}, 7] $ ; $ 6 $ is their median, so it is not erased, and the resulting sequence is $ [2, 3, 4, 5, 6] $ ;
- and several others.

You can do zero or more steps. Can you get a sequence $ b_1 $ , $ b_2 $ , ..., $ b_m $ after several steps?

You'll be given $ t $ test cases. Solve each test case independently.

## 说明/提示

In the first test case, you have sequence $ [1, 2, 3] $ . Since $ k = 3 $ you have only one way to choose $ k $ elements — it's to choose all elements $ [1, \underline{2}, 3] $ with median $ 2 $ . That's why after erasing all chosen elements except its median you'll get sequence $ [2] $ . In other words, there is no way to get sequence $ b = [1] $ as the result.

In the second test case, you have sequence $ [1, 2, 3, 4, 5, 6, 7] $ and one of the optimal strategies is following:

1. choose $ k = 3 $ elements $ [2, \underline{3}, 4] $ and erase them except its median; you'll get sequence $ [1, 3, 5, 6, 7] $ ;
2. choose $ 3 $ elements $ [3, \underline{5}, 6] $ and erase them except its median; you'll get desired sequence $ [1, 5, 7] $ ;

In the fourth test case, you have sequence $ [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13] $ . You can choose $ k=7 $ elements $ [2, 4, 6, \underline{7}, 8, 10, 13] $ and erase them except its median to get sequence $ b $ .

## 样例 #1

### 输入

```
4
3 3 1
1
7 3 3
1 5 7
10 5 3
4 5 6
13 7 7
1 3 5 7 9 11 12```

### 输出

```
NO
YES
NO
YES```

# 题解

## 作者：cqbztz2 (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/CF1468H)

- 一道思维题

# 思路：

每次操作可以消去 $ k-1 个数 $，所以 $ (n-m) \bmod (k-1) \ne 0 $ 的情况必然是无解的。

消去的最后一步，必然是以 $ b $ 序列中的某一元素为中位数进行的。

因此我们得到一个必要条件：存在 $ i$ ,对这个 $ b_i $ ， $ a $ 中 $ b_i $ 的两侧各有  $ k/2 $ 个不在 $ b $ 序列中的数，

但前面删除的数是任意的，所以只要满足上述条件，我们就可以在保持上述条件成立的情况下，不断减小数的个数，因此这个条件也是充分的。

# 代码：

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int t,n,k,m,b[200005];
  int main(){
      cin>>t;
      while(t--){
          cin>>n>>k>>m;
          for(int i=1;i<=m;i++){
              cin>>b[i];
          }   
          if((n-m)%(k-1)!=0){
              cout<<"NO"<<endl;
              continue;
          }
          bool flag=false;
          for(int i=1;i<=m;i++){
              if(b[i]-i>=(k-1)/2&&n-m+i-b[i]>=(k-1)/2){
                  cout<<"YES"<<endl;
                  flag=true;
                  break;
              }
          } 
          if(flag==false){
              cout<<"NO"<<endl;
          }
      }
      return 0;
  }
```


---

## 作者：skyskyCCC (赞：2)

## 前言。
简简单单思维题，然而我卡在了第二个数据点上。
## 分析。
下面给出思路：

首先，我们发现当我们进行 $x$ 次操作后，每次删除 $k-1$ 个数，所以一共消除了 $\left(k-1\right)\times x$ 个数。如果要让两个序列 $a$ 与 $b$ 完全相同，则前提是序列中包含的个数必须相同，则意味着我们删去的数必须能被整次的次数消除，即必须满足 $\left(n-m\right)\bmod\left(k-1\right)=0$ 的情况。否则不成立。

接下来我们考虑进行这 $n-m$ 次消除操作。考虑倒推。因为要保留中位数，并且最后一次消除一定是以其中一个的某一个数为中位数，所以消除这个中位数左边的 $\frac{k-1}{2}$ 个和它右边的 $\frac{k-1}{2}$ 个，不包括该中位数。由此最后一次消除的中位数的条件显然满足以下条件：
- 首先在需要构建的答案串中出现，否则无法通过删除转换序列一致。
- 在最开始删除时，该中位数的左右两边，各有不少于 $\frac{k}{2}$ 个数**没有**被消除。

对于前面的 $x-1$ 次操作，因为只有存在刚才中位数的条件 $2$ 则一定可以找到当前的一个中位数，同理只要满足这个条件，必然存着一方式，可以构造到最后一次消除。

所以就可以进行简单的判断。

代码如下，仅供参考：
```
#include<iostream>
using namespace std;;
int t,n,k,m;
int a[200005];
int main(){
	cin>>t;
	while(t--){
		int flag=1;
		cin>>n>>k>>m;
		for(int i=1;i<=m;i++){
			cin>>a[i];
		}
		if((n-m)%(k-1)){
			cout<<"NO\n";
			continue;
		}
		//if(cheak()){
		//	cout<<"YES\n";
		//}
		//else cout<<"NO\n";
		for(int i=1;i<=m;i++){
		    if(a[i]-i>=k/2){
		    	if(n-m-(a[i]-i)>=k/2){
		    		cout<<"YES\n";
		    		flag=0;
		    	    break;
				}
	        }
	    }
	    if(flag==0) continue;
	    cout<<"NO\n";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：似嫩 (赞：2)

## 题意
给定两个序列 $a,b$ ， $b$ 是给定的**单调不减**的序列。
现在你可以若干次操作，每次操作选择序列 $a$ 的 $k$ 个整数，然后删除这 $k$ 个数里除了他们的中位数的其他 $k-1$ 个数。问你能否通过若干次操作，得到序列 $b$ 。

## 分析

因为每次操作之后，我们都会去掉 $k-1$ 个数，那么如果有解则有

$$n-m\equiv0\pmod{k-1}$$ 
其中 $n$ 是 $a$ 的长度， $m$ 是 $b$ 的长度。如果不满足，则输出 “NO”。

**现在考虑如何判断有解**

举个栗子： 第二个样例 $n=7$，$m=3$， $k=3$， $b_i={1, 5, 7}$ 。我们发现需要把 $5$ 前面的 $2, 3, 4$ ,和后面的 $6$ 给删掉。

再举个梨子： 第四个样例 $n=13$ ，$m=7$ ，$k=7$ ，$b_i={1,3,5,7,9,11,12}$ 。发现 $7$ 前面需删 $2,4,6$ 三个数，后面需删 $8,10,13$ 三个数。这两种情况都是有解的。

我们猜测，如果有一个数满足：需要删的数中，**小于它的数的个数，和大于它的数的个数均大于 $\frac{k-1}{2}$** ，那么一定有解。

下面是证明。

设 $d=\frac{k-1}{2}$ ，假设我们找到一个数 $p$ , 其中比它小的需要删除的数的个数记作 $x$ , 比它大的需要删除的数的个数记作 $y$ 。所以 $x+y=n-m\equiv0\pmod{k-1}$ 。记 $x'=x-d$ ， $y'=y-d$ ， （前后各去掉 $d$ 个数）所以有 

$$x'+y'=x+y-2d=x+y-(k-1)$$
因此
$$x'+y'\equiv0\pmod{k-1}$$
于是我们一定能找到至少一种方法把这 $x'+y'$ 个数全部删掉（最后一次，可以去序列中借一个数来当中位数）。那么只剩下 $d+1+d=k$ 个数，我们需要留下的数 $p$ 正好就是这 $k$ 个数的中位数。因为，正好有 $d$ 个数小于它,正好有 $d$ 个数大于它。最后我们把 $k-1$ 个数删去就得到了我们想要的序列。

## 总结

无解的情况只需判断是否满足 
$$n-m\equiv0\pmod{k-1}$$

否则，我们统计每个需要保留的数前后，各需要删除几个数，如果有一个数满足需要删除的数中**小于它的数的个数，和大于它的数的个数均大于 $\frac{k-1}{2}$** ，那么一定有解
```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
inline int read(){
	int x = 0, f = 1; char c = getchar();
	while (! isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while(isdigit(c)) {
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	return x * f;
}
int T, n, m, k, tot, d, sum, l, r;
int b[N];
int main(){
	T = read();
	while (T --) {
		bool f = true;
		n = read(), k =read(), m = read();
		for (int i = 1; i <= m; i ++) 
		    b[i] = read();
		if ((n - m) % (k - 1) != 0) {//无解
			printf("NO\n");
			continue;
		}
		tot = 1; d = (k - 1) / 2; sum = n;
		for (int i = 1; i <= m; i ++)
		{
			if (b[i] - i >= d && n - b[i] - m + i >= d){//判断是否有一个数满足条件
			    printf("YES\n");f = false;
				break; 
			}
		}
		if(f) printf("NO\n");//如果这个数不存在，仍无解
	}
	return 0;
}
```


---

## 作者：DaiRuiChen007 (赞：0)

# CF1468H 题解



## 思路分析

首先，一次操作会删除 $k-1$ 个数，因此如果 $(n-m)\bmod (k-1)\ne 0$，那么必然无解。

假设 $d=\dfrac{k-1}2$，那么一次操作可以看在 $\{a_i\}$ 中选定一个下标 $x$，并在 $x$ 的左边和右边各删除 $d$ 个元素。

注意到如下的观察：

> 观察：
>
> 若 $(n-m)\bmod(k-1)=0$，那么当且仅当存在一个 $i\in[1,m]$ 使得 $1\sim n$ 的待删除元素中 $<b_i$ 和 $>b_i$ 都至少有 $d$ 个时，原问题有解。
>
> 对待删除元素数量进行归纳，显然当待删除元素数量为 $0$ 时一定有解。
>
> 否则，考虑最后一次操作，保留的中位数一定是某个 $b_i$，而这就要求 $<b_i$ 和 $>b_i$ 的待删除元素都至少有 $d$ 个，如果存在这样的 $b_i$，假设操作时删除了 $a_{i_1}\sim a_{i_{k-1}}$，那么在这次操作之前，我们可以把 $a_{i_1}\sim a_{i_{k-1}} $ 全部看成需要保留的元素。
>
> 那么我们只需要删除剩下的的 $(n-m)-(k-1)$ 个元素，由于 $(n-m)\bmod (k-1)=0$，那么一定能归纳到待删除元素数量为 $0$ 的情况。
>
> 因此我们只需要证明，在保留 $a_{i_1}\sim a_{i_{k-1}}$ 之后，若 $(n-m)>(k-1)$，我们依然能够找到一个合法的操作位置来删除 $k-1$ 个元素即可。
>
> 不妨假设原本 $<b_i$ 的待删除元素有 $x$ 个，$>b_i$ 的待删除元素有 $y$ 个，而在保留 $a_{i_1}\sim a_{i_{k-1}}$ 后 $<b_i$ 的还剩 $x-d=x'$ 个，而 $>b_i$ 的还剩 $y-d=y'$ 个。
>
> 由于 $x+y=n-m,2\times d=k-1$，因此 $x+y\ge 4d$ 即 $x'+y'\ge 2d$，因此 $x'\ge d$ 和 $y'\ge d$ 中至少有一个成立，而同时成立的情况只需要继续操作 $b_i$ 即可，故我们假设 $x'> d>y'$：
> 
> 设 $d-y'=r$，则 $x'\ge d+r$，那么 $x\ge 2d+r$，那么我们在最后一次操作时选择恢复这 $x$ 个元素中的第 $d+1\sim 2d$ 个待删除元素即可，此时在这些被恢复的元素中任选一个，其左侧剩下 $d$ 个带删除元素，右侧剩下 $x'-2d+y'\ge d$ 个元素，因此我们构造出了一种方法使得在剩下的 $(n-m)-(k-1)$ 个待删除元素中也能找到一个分界点，使得其左右的待删除元素都不少于 $d$ 个，故原命题得证。

因此先判断 $(n-m)\bmod (k-1)$ 的值，然后找到一个这样的 $b_i$ 即可。

时间复杂度 $\Theta(n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
bool vis[MAXN],del[MAXN];
inline void solve() {
	int n,k,m;
	scanf("%d%d%d",&n,&k,&m);
	for(int i=1;i<=n;++i) del[i]=vis[i]=false;
	for(int i=1;i<=m;++i) {
		int x;
		scanf("%d",&x);
		vis[x]=true;
	}
	if((n-m)%(k-1)!=0) {
		puts("NO");
		return ;
	} 
	int pre=0,suf=n-m,d=(k-1)/2;
	for(int i=1;i<=n;++i) {
		if(vis[i]) {
			if(pre>=d&&suf>=d) {
				puts("YES");
				return ;
			}
		} else ++pre,--suf;
	}
	puts("NO");
}
signed main() {
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```



---

