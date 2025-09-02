# Three Indices

## 题目描述

You are given a permutation $ p_1, p_2, \dots, p_n $ . Recall that sequence of $ n $ integers is called a permutation if it contains all integers from $ 1 $ to $ n $ exactly once.

Find three indices $ i $ , $ j $ and $ k $ such that:

- $ 1 \le i < j < k \le n $ ;
- $ p_i < p_j $ and $ p_j > p_k $ .

 Or say that there are no such indices.

## 样例 #1

### 输入

```
3
4
2 1 4 3
6
4 6 1 2 5 3
5
5 3 1 2 4```

### 输出

```
YES
2 3 4
YES
3 5 6
NO```

# 题解

## 作者：linyihdfj (赞：1)

## A.Three Indices ##
[博客食用效果更佳](https://www.cnblogs.com/linyihdfj/p/16450318.html)
### 题目描述： ###
[原题面](https://codeforces.com/problemset/problem/1380/A)
### 题目分析： ###
这题就是要让我们找到三个数，要求中间的数最大。

那么我们就考虑枚举中间的数是哪个，然后为了尽可能的使这个条件成立，我们显然就是要选择这个数左边以及右边的最小值，我们就预处理出来左边的最小值是哪个以及右边的最小值是哪个，然后每次判断一下，只要符合条件就输出。
### 代码详解: ###
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int INF = 1e8+5;
int pre[MAXN],suf[MAXN],a[MAXN];
int main(){
	int t;
	cin>>t;
	while(t--){
		bool flag = false;
		memset(pre,0,sizeof(pre));
		memset(suf,0,sizeof(suf));
		int n;
		cin>>n;
		for(int i=1;i<=n; i++){
			cin>>a[i];
		}
		int now = INF;
		pre[0] = 1;
		for(int i=1; i<=n; i++){
			pre[i] = pre[i-1];
			if(a[i] < now){
				now = a[i];
				pre[i] = i;
			}
		}
		suf[n+1] = n;
		now = INF; 
		for(int i=n; i>=1; i--){
			suf[i] = suf[i+1];
			if(a[i] < now){
				now = a[i];
				suf[i] = i;
			}
		}
		for(int i=1; i<=n; i++){
			if(a[pre[i]] < a[i] && a[suf[i]] < a[i]){
				printf("YES\n");
				printf("%d %d %d\n",pre[i],i,suf[i]);
				flag = true;
				break;
			}
		}
		if(!flag)
			printf("NO\n");
	}
	return 0;
}
```

记得多组数据每次都要清空


---

## 作者：dead_X (赞：1)

# 题意
在一个数组里找到任意三个数，使得它们下标递增且中间那个数最大。找不到输出0。
# 思路
贪心，$O(n)$。

我们先从左往右扫一遍，对于每一个数分几种情况。

1. 搜到这个数时还没有找到 $x$ ，则这个数作为 $x$ 。

2. 搜到这个数时还没有找到 $y$ ，如果这个数大于 $x$ 则这个数变成 $y$ ，不然这个数变成 $x$ 。

3. 搜到这个数时还没有找到 $y$ ，如果这个数小于 $x$ 则这个数变成 $z$ 并且输出解，不然这个数变成 $y$ 。

第一个操作没什么好说的，肯定正确。

剩下两个操作的正确性证明如下:

如果已经确认了 $x,y$ ，则只需要确认 $z$ 即可。

而如果在第 $k$ 个确定了一个 $y$ ，如果没有解当且仅当第 $k$ 到 $n$ 个数组成一个递增序列。

上面这个结论的证明:

1. 如果有一个数小于 $y$ 则 $z$ 就是那个数时就是一个合法解。

2. 在 $1.$ 的基础上如果有一个数小于前一个数，那前一个数作为新 $y$，后一个数作为 $z$ 就是一个合法解。
# 代码
```cpp
#include<bits/stdc++.h>
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
inline long long readll(){
   long long s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
using namespace std;
int a[1000003];
int main()
{
	int T=read();
	while(T--)
	{
		int n=read(),x=1,y,z=-1;
		bool f=1;
		for(int i=1; i<=n; i++) a[i]=read();
		for(int i=1; i<=n; i++)
		{
			if(f) if(a[i]>a[x]) y=i,f=0; else x=i;
			else if(a[i]<a[y]) 
			{
				z=i;
				break;
			} else y=i;
		}
		if(z==-1) puts("NO");
		else 
		{
			puts("YES");
			printf("%d %d %d\n",x,y,z);
		}
	}
	return 0;
}
```

---

## 作者：XCH_0803 (赞：0)

# 题意

给你一个 ($1\sim n$) 的排列 $p$ 让你找到三个数 ($i,j,k$) 使得 $p_i < p_j $ 且 ($p_j > p_k$) 。

# 思路

先从前往后扫一遍 ，求出哪些位置满足存在一个比它小的在它前面。这可以用树状数组统计当前 ($1\sim i$) 中出现了几个。

然后倒着再做一遍求出哪些位置存在一个比它小的在它后面。

找到一个都满足的点，然后在它前面和后面都找一个比它小的即可。

若不存在即为没有。

话不多说，上代码!

```c
#include <bits/stdc++.h>
using namespace std;
int t,n,a[1100],c[1100];
bool mark[1010],ans;
int pos;
int lowbit(int x){
	return x&(-x);
}
void add(int x){
	while(x<=n){
		c[x]++;
		x+=lowbit(x);
	}
}
int ask(int x){
	int ret=0;
	while(x){
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}
int main() {
	cin>>t;
	while(t--){
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++){
			c[i]=0;
			mark[i]=0;
		}
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			if(ask(a[i]-1)){
				mark[i]=1;
			}
			add(a[i]);
		}
		for(int i=1;i<=n;i++){
			c[i]=0;
		}
		for(int i=n;i>=1;i--){
			if(mark[i]&&ask(a[i]-1)){
				pos=i;
				ans=1;
				break;
			}
			add(a[i]);
		}
		if(ans){
			cout<<"YES"<<endl;
			for(int i=1;i<pos;i++){
				if(a[i]<a[pos]){
					cout<<i<<" ";
					break;
				}
			}
			cout<<pos<<" ";
			for(int i=pos+1;i<=n;i++){
				if(a[i]<a[pos]){
					cout<<i<<endl;
					break;
				}
			}
		} 
		else{
			cout<<"NO"<<endl;
		}
	}
	return 0;
}
```




---

## 作者：wssdl (赞：0)

# 题目大意

给你 $T$ 样例，每个样例有 $n$ 个数，让你找出 $3$ 个数的下标， $\texttt{i,j,k}$ ，保证 $1\le i<j<k\le n$，并且 $a_i<a_j$ 且 $a_j>a_k$ ，若存在解，即输出 $\texttt{YES}$ 并输出这三个下标，否则直接输出 $\texttt{NO}$ 。

# 解题思路

题目的数据范围是 $3\le n\le 1000$ 所以我们直接暴力枚举这三个下标的时间复杂度是 $O(n^3)$ ，肯定会超时，那我们想一想有没有 $O(n^2)$ 的解法，稍加思索，我们可以发现：只要枚举出中间点，并假设它为 $i$ ，再从$1\cdots i-1$ 中找出满足 $a_j<a_i$ 的那个 $j$ ，就可以了，同理，我们再从 $i+1\cdots n$ 找出那个 $k$ 即可，再用变量 $tmp1$ 与 $tmp2$ 存储 $j$ 和 $k$ 即可。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
int t;
int n;
int a[N];
int main() {
  cin >> t;
  while (t--) {  //T组样例
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    bool b = 0;
    for (int i = 2; i < n; i++) {    //枚举中间点
      int tmp1 = -1, tmp2 = -1;      //注意初始化，如果枚举结束后还为-1，说明无解
      for (int j = 1; j < i; j++) {  //枚举第一个数
        if (a[j] < a[i]) {           //找到第一个数
          tmp1 = j;
          break;
        }
      }
      for (int k = i + 1; k <= n; k++) {  //枚举第三个数
        if (a[k] < a[i]) {                //找到第三个数
          tmp2 = k;
          break;
        }
      }
      if (tmp1 != -1 && tmp2 != -1) {
        b = 1;
        cout << "YES" << endl;
        cout << tmp1 << " " << i << " " << tmp2 << endl;
        break;
      }
    }
    if (!b) {
      cout << "NO" << endl;
    }
  }
  return 0;
}
```


---

## 作者：Fan_Tuan (赞：0)

# 题意
给定一个长度为 $n$ 的序列， 寻找 $i, k, j$ 满足 $1 <= i < k < j <= n$ 且 $a_i < a_j  $ $&&$ $a_j > a_k $。
# 思路
枚举每一个$i$, 寻找第一个大于$a_i$ 的点且下标大于$i$, 用 $j$  标记为它的下标， 然后寻找第一个小于 $a_j$ 的点且下标大于 $j$， 标记它的下标为 $k$。输出答案即可。

# 代码
```c
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <queue>
#include <iostream>
using namespace std;

const int maxn = 5005;
int n, t, a[maxn];

signed main () {
    scanf("%d", &t); 
    while (t--) {
        scanf("%d", &n);
        memset (a, 0, sizeof a);
        int flag = 0;
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i++) {
            int fir = 0, sec = 0;
            for (int j = i + 1; j <= n; j++) {
                if (a[j] > a[i] && fir == 0) fir = j;
                else if (fir != 0 && sec == 0 && a[j] < a[fir]) {
                    sec = j;
                    puts ("YES");
                    printf ("%d %d %d\n", i, fir, sec);
                    flag = 1;
                    break;
                } 
            }
            if (sec != 0 && fir != 0) break;
        }
        if (flag == 0) puts ("NO");
    }
    return 0;
}
```


---

## 作者：45dino (赞：0)

一个比较好想的做法。

对于每一组数据，枚举 $i$ ，对于每一个 $i$ ，递推计算到 $k(i+1<k\le n)$ 的最大值，如果这个最大值比 $p_i$ 和 $p_k$ 大，就说明这三个数满足要求。

由于输出的是下标，所以最大值也要存下标。

喜闻乐见的代码：
```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1001],maxx[1001];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		bool out=1;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
		{
			for(int l=i-1;l<=n;l++)
				maxx[l]=0;
			maxx[i]=i;
			for(int l=i+1;l<=n;l++)
				if(a[l]>=a[maxx[l-1]])
					maxx[l]=l;
				else
				{
					maxx[l]=maxx[l-1];
					if(maxx[l]!=i)
					{
						puts("YES");
						cout<<i<<" "<<maxx[l]<<" "<<l<<endl;
						out=0;
						break;
					}
				}
			if(!out)
				break;
		}
		if(out)
			puts("NO");	
	}
	return 0;
}
```


---

