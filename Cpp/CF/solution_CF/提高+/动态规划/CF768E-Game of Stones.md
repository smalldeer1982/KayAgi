# Game of Stones

## 题目描述

Sam has been teaching Jon the Game of Stones to sharpen his mind and help him devise a strategy to fight the white walkers. The rules of this game are quite simple:

- The game starts with $ n $ piles of stones indexed from $ 1 $ to $ n $ . The $ i $ -th pile contains $ s_{i} $ stones.
- The players make their moves alternatively. A move is considered as removal of some number of stones from a pile. Removal of $ 0 $ stones does not count as a move.
- The player who is unable to make a move loses.

Now Jon believes that he is ready for battle, but Sam does not think so. To prove his argument, Sam suggested that they play a modified version of the game.

In this modified version, no move can be made more than once on a pile. For example, if $ 4 $ stones are removed from a pile, $ 4 $ stones cannot be removed from that pile again.

Sam sets up the game and makes the first move. Jon believes that Sam is just trying to prevent him from going to battle. Jon wants to know if he can win if both play optimally.

## 说明/提示

In the first case, Sam removes all the stones and Jon loses.

In second case, the following moves are possible by Sam: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768E/4cf426c19e824968ff19a401a7802c8ac91cbb66.png)

In each of these cases, last move can be made by Jon to win the game as follows: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF768E/dbfee646415d7f71d37ff9a2600935f88c5436ae.png)

## 样例 #1

### 输入

```
1
5
```

### 输出

```
NO```

## 样例 #2

### 输入

```
2
1
2
```

### 输出

```
YES```

# 题解

## 作者：pufanyi (赞：11)

这题的限制比较麻烦，我们考虑如何把它去掉。

假设我们有一堆$10$个石子，那么我们可以几次取完呢？最少是$1$（一次性取完），最多是$4$，即$10 = 1 + 2 + 3 + 4$。显然，用$1\sim 4$步都是可以完成的。而在没有限制情况下，可以用且仅能用$1\sim 4$步完成的石子数是$4$，所以我们认为有条件的$10$颗石子就等同于没有条件的$4$颗石子。

那如何等效过去呢？我们考虑每一步都取最少的石子，直到不能再去了。

于是就变成了一个朴素的[nim游戏](https://www.luogu.org/problemnew/show/P2197)了。

贴一发代码：

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    int n;
    scanf("%d", &n);
    int sgg = 0;
    for(int i = 1, t; i <= n; ++i)
    {
        scanf("%d", &t);
        int j = 1;
        for(j = 1; ; j++) // 把t个有限制的石子等效成j个没有限制的石子。
        {
            t -= j; // 由于1～j-1都已经用过了，那最少只能是j。
            if(t <= j) // 没办法再取了。
                break;
        }
        sgg ^= j;
    }
    puts(sgg ? "NO" : "YES");
    return 0;
}
```



---

## 作者：ωαηg (赞：5)

首先%一下楼上的同校巨佬[@pufanyi](https://www.luogu.org/space/show?uid=84088)

楼上的方法很巧妙，但在这里我将提供另一种思路，比他的略复杂一点，但是更好理解。

----

### 首先审题

题目中说“但是不能两次从同一堆石子中取出同样数量的石子”，这个“两次”并不是指连续的两次。也就是说，如果我在某一堆石子中，取了$x$颗，那么今后我就**永远**也不能在这堆石子中取$x$颗，而不仅仅是下一次对这堆石子进行操作的时候。而且，不仅仅是我不能取，**我的对手**也不能取。

举个例子，比如说我第一次在第一堆石子里面取走了三颗，那么我第二次不能再在第一堆石子里面取三颗，第三次同样不能取三颗，第四次、第五次、第六次...都是这样。而不是仅仅不能在第二次取三颗。

**把以上的话转化为人话：对于一堆石子，它每次取的数量都得不同。**

----

### 转化

我们发现每一次取的数量都得不同，那么我们完全可以按照递增的顺序来取石子。也就是说，本来是第一次取了3颗，第二次取了2颗，第三次取了1颗。我们把它变成第一次取1颗，第二次取2颗，第三次取3颗，效果等价。

那么我们的SG函数就很好设计了。

----

### 状态与转移

我们用$sg[i][j]$表示现在还剩下$i$颗石子，上一次取了$j$颗石子，此时的SG值。

再用$all\_sg[i]$表示还剩下$i$颗石子的全局SG值。

那么$sg[i][j]$的转移就是这样的，很好理解：

```cpp
for(int i=1;i<=60;i++)
      for(int j=1;j<=i;j++){
      	  for(int k=j+1;k<=i-j;k++)//暴力枚举接下来选几颗
          //因为是递增选取，所以循环从j+1开始
      	    vis1[sg[i-j][k]][1]=i,vis1[sg[i-j][k]][2]=j;
      	  for(sg[i][j]=0;vis1[sg[i][j]][1]==i && vis1[sg[i][j]][2]==j;sg[i][j]++);//求mex的基本操作（当然还有别的写法）
      }
```

而$all\_sg[i]$则是所有的$sg[i][j]$求个$mex$：
```cpp
for(int i=1;i<=60;i++){
        for(int j=1;j<=i;j++)
          vis2[sg[i][j]]=i;
        for(all_sg[i]=0;vis2[all_sg[i]]==i;all_sg[i]++);
    }
```
最后只要输出答案就可以了。

----

### 完整代码

```cpp

#include<bits/stdc++.h>
using namespace std;
inline int read(){
    int sum=0;
    char c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)){
        sum=sum*10+(c^48);
        c=getchar();
    }
    return sum;
} 
int const maxn=1e6+5;
int n,sg[65][65],all_sg[65],vis1[maxn][3],vis2[maxn];
signed main(){
    for(int i=1;i<=60;i++)
      for(int j=1;j<=i;j++){
      	  for(int k=j+1;k<=i-j;k++)
      	    vis1[sg[i-j][k]][1]=i,vis1[sg[i-j][k]][2]=j;
      	  for(sg[i][j]=0;vis1[sg[i][j]][1]==i && vis1[sg[i][j]][2]==j;sg[i][j]++);
      }
    for(int i=1;i<=60;i++){
        for(int j=1;j<=i;j++)
          vis2[sg[i][j]]=i;
        for(all_sg[i]=0;vis2[all_sg[i]]==i;all_sg[i]++);
    }
    n=read();
    int ans=0;
    for(int i=1;i<=n;i++){
        int a=read();
        ans^=all_sg[a];
    }
    if(ans) puts("NO");
    else puts("YES");
    return 0;
}
```

---

## 作者：Dancing_Wave (赞：2)

其他题解已经讲的很清楚了，实际上就是把每堆石子转化成这一堆石子最多可以取的次数，然后就可以进行普通的[nim](https://www.luogu.com.cn/problem/P2197)。

但是由于 $s_{i}$ 范围太小，这个思路的题解要么直接枚举次数，要么打表。前者在时间复杂度上是 $O(n \sqrt{\max(s_{i})})$ ，后者在空间复杂度上则是 $O(\max(s_{i}))$ 。

而题目如果将 $s_{i}$ 范围放大，这两种写法都过不了。

所以我们直接通过数学方法计算出这个次数。

每次对于一个 $s_{i}$ ，它对应的次数 $x_{i}$ 满足 $x_{i}(x_{i}+1)/2 \le s_{i}$ 且 $x_{i}$ 尽量大。

转化一下， $x_{i}$ 就等于 $x^2 + x -2s{i} = 0$ 的正根并向下取整。

解方程，得 $x = \frac{-1 \pm \sqrt{1 + 8s_{i}}}{2}$ ， $x_{i} = \lfloor \frac{-1+\sqrt{1 + 8s_{i}}}{2}\rfloor $ 。

这样就做到了时间复杂度 $O(n)$ 空间复杂度 $O(1)$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long read(){
	long long f=0,w=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')w=-1;ch=getchar();}
	while(isdigit(ch)){f=f*10+(long long)(ch-'0');ch=getchar();}
	return f*w;
}
int n,ans;
int main(){
	n=read(),ans=0;
	for(int i=1;i<=n;i++){
		int s=read();
		int x=((int)sqrt((double)(1+8*s))-1)/2;
		ans^=x;
	}
	printf("%s\n",ans?"NO":"YES");
	return 0;
}
```

---

## 作者：Pecco (赞：2)

这题，这数据范围，怎么能不打表？

```cpp
#include <bits/stdc++.h>
using namespace std;
int block[70];
int dfs(int n)
{
    bool A[70]{};
    for (int i = 1; i <= n; ++i)
        if (!block[i])
        {
            block[i] = 1;
            A[dfs(n - i)] = 1;
            block[i] = 0;
        }
    for (int i = 0;; ++i)
        if (!A[i])
            return i;
}
int main()
{
    for (int i = 0; i <= 60; ++i)
        cout << dfs(i) << ", ";
    return 0;
}
```

如上，我们根据sg函数的定义，直接敲一个暴搜，打一个表出来，然后……然后就过了。

```cpp
#include <bits/stdc++.h>
using namespace std;
int sg[] = {0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10};
int main()
{
    int n, x, ans = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> x, ans ^= sg[x];
    cout << (ans ? "NO" : "YES");
    return 0;
}
```

其实根据这个表你是可以看出其他题解的大佬推出的结论的，sg为n的数刚好有n+1个。

---

## 作者：JerryZiruiZhang (赞：1)

* 这是一份考场上可操作性较强，并且能帮助你发现细节处问题的题解：

* 首先注意不要读错题了，如果一次取走石子的个数为 $x$ 那么**之后的每一次**都不能再取 $x$ 个石子（不要理解成只对之后的那一次有限制）

* 容易发现一堆石子的 SG 函数可以记忆化搜索得到。具体的：设 ```dfs(int rst, ll S)``` 表示剩余 rst 个石子，已经取过的数集合为 $S$ 的 SG 值，则 ```dfs(i, 0)``` 即为一堆大小为 $i$ 的石子的答案。

* 打完表之后应该手算几个位置进行验证！注意在打表中的细节！注意检查：

1. 如果求 mex 的时候从 $1$ 开始枚举 vis 数组会出错，详见代码。

```cpp
map<PIl, int> dp;
int dfs(int rst, ll S) {
	if(rst == 0) return 0;
	if(dp[mkp(rst, S)]) return dp[mkp(rst, S)];
	int vis[100] = {0};
	for(int i = 1; i <= rst; i++) {
		if((S >> (i - 1)) & 1) continue;
		int g = dfs(rst - i, S ^ (1ll << (i - 1)));
		vis[g] = true;
	}
	for(int i = 0; ; i++) { // 从 0 开始！不要从 1 开始！
		if(!vis[i]) return dp[mkp(rst, S)] = i;
	}
}
```

* 下面是 AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int SG[66] = {0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10};int main () {
	int n, sum = 0; scanf("%d", &n);
	for(int i = 1, a; i <= n; i++) scanf("%d", &a), sum ^= SG[a];
	if(sum == 0) printf("YES"); else printf("NO");
	return 0;
}
```

---

## 作者：Falashiro (赞：1)

垃圾做法喜提 luogu 时间最劣解+空间最劣解+代码长度最劣解。

考虑状压，第 $i$ 位为 $1$ 表示之前某次已经取过了 $i$ 个石子，

设 $sg_{i,j}$ 表示当前剩 $i$ 个石子，状态为 $j$ 的 $sg$ 值，

虽然一共有 $2^{60}$ 种状态，但是其中真正有效的却不多，对于某个状态，所有为 $1$ 的位的下标的和显然不能超过 $60$，否则为无效状态，

可以写一个 dfs 搜出所有有效状态，发现只有 $101983$ 种，

于是可以对于所有有效的 $sg$ 暴力求 $mex$，时间复杂度为 $O(101983\times60^2)$，即可得到所有 $sg_{i,j}$，答案即为 $sg_{a_i,0}$ 的 $xor$，

实现时可以给每个有效状态分配一个下标，用 `unordered_map` 映射回去。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
#define N 60
int read(){
	int w=0,f=1;
	char c=' ';
	while(c<'0'||c>'9')c=getchar(),f=c=='-'?-1:f;
	while(c>='0'&&c<='9')w=w*10+c-48,c=getchar();
	return w*f;
}
int n,sg[N+1][102000],sum[102000],cnt;
ull vis[102000],fl,ind[N+1],all=ULONG_LONG_MAX;
unordered_map<ull,int>mp;
bool ap[N+1];
void dfs(int now,int s){
	if(s>N)return;
	if(now==N)return vis[++cnt]=fl,sum[cnt]=s,mp[fl]=cnt,void();
	now++;
	fl&=ind[now];
	dfs(now,s);
	fl|=(1llu<<now);
	dfs(now,s+now);
}
void init(){
	for(int i=1;i<=N;i++)
		ind[i]=all^(1llu<<i);
	dfs(0,0);
	for(int i=1;i<=N;i++){
		for(int j=1;j<=cnt;j++){
			if(sum[j]+i>N)continue;
			memset(ap,0,sizeof(ap));
			for(int k=1;k<=N;k++)
				if(!(vis[j]>>k&1)&&i-k>=0)ap[sg[i-k][mp[vis[j]|1llu<<k]]]=1;
			for(int k=0;;k++)
				if(!ap[k]){
					sg[i][j]=k;
					break;
				}
		}
	}
}
signed main(){
	init();
	n=read();
	int ans=0;
	for(int i=1;i<=n;i++)
		ans^=sg[read()][1];//显然mp[0]=1
	puts(ans?"NO":"YES");
	return 0;
}
```

---

## 作者：Aigony (赞：0)

首先即使有这个奇怪的限制，每堆石子之间仍然是独立的。

我们考虑一堆有 $x$ 个石子，它最多可以不重复地取 $d$ 次。即，最大满足 $\sum\limits_{i=1}^d i \le x$ 的 $d$。  
那么这堆石子被取到不能再操作之前，只可能操作了 $1\sim d$ 次。这本质上等价于一个取法没有限制的大小为 $d$ 的石子堆。

综上，我们可以将整个问题转化为没有限制的 Nim 游戏。

```cpp
const int N=1e6+5;
int n,a[N];
int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int x=1,cnt=0;
        while(a[i]>=x) a[i]-=x,x++,cnt++;
        ans^=cnt;
    }
    if(ans) printf("NO\n");
    else printf("YES\n");
    return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 解题思路：

考虑将问题转化为一般的 $\text{NIM}$ 问题来处理。

普通的  $\text{NIM}$ 问题的 $\text{SG}$ 函数是 $\text{SG}(x)=x$。也就是每一个位置都能取到比其小的任意位置，但是本题由于有不能取相同数值的限制，不能直接进行转换。

考虑用每一个值需要取的最多的次数为考量标准，则每一次取数可以且仅可以取到比严格这个数小的任意数。

那么这个值的计算就是最小的 $\dfrac{n(n-1)}{2}>x$ 的 $n$（注意这里不能取和之前相同的，所以最后剩下来的一点点不能使得最终结果加一）。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
#define int long long
int n,a[2000005],x;
signed main(){
	scanf("%I64d",&n);
	for(int i=1;i<=n;i++){
		scanf("%I64d",&x);
		for(int j=1;j<=x;j++){
			a[i]+=j;
			if(a[i]>=x){a[i]=j-(a[i]!=x);break;}
		}
	}
	int x=0;
	for(int i=1;i<=n;i++)x^=a[i];
	if(x==0)printf("YES\n");
	else printf("NO\n");
	return 0;
}
```


---

