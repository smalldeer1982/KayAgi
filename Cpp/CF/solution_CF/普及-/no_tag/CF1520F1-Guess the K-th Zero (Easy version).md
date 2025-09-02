# Guess the K-th Zero (Easy version)

## 题目描述

This is an interactive problem.

This is an easy version of the problem. The difference from the hard version is that in the easy version $ t=1 $ and the number of queries is limited to $ 20 $ .

Polycarp is playing a computer game. In this game, an array consisting of zeros and ones is hidden. Polycarp wins if he guesses the position of the $ k $ -th zero from the left $ t $ times.

Polycarp can make no more than $ 20 $ requests of the following type:

- ? $ l $ $ r $ — find out the sum of all elements in positions from $ l $ to $ r $ ( $ 1 \le l \le r \le n $ ) inclusive.

In this (easy version) of the problem, this paragraph doesn't really make sense since $ t=1 $ always. To make the game more interesting, each guessed zero turns into one and the game continues on the changed array. More formally, if the position of the $ k $ -th zero was $ x $ , then after Polycarp guesses this position, the $ x $ -th element of the array will be replaced from $ 0 $ to $ 1 $ . Of course, this feature affects something only for $ t>1 $ .

Help Polycarp win the game.

## 说明/提示

In the first test, the $ [1, 0, 1, 1, 0, 1] $ array is hidden. In this test $ k=2 $ .

## 样例 #1

### 输入

```
6 1
2

2

1

1

0

0```

### 输出

```
? 4 6

? 1 1

? 1 2

? 2 2

? 5 5

! 5```

# 题解

## 作者：liruixiong0101 (赞：6)

## P1 题意：
此题为**交互题**。有一个长度为 $n$，仅含 $01$ 的数组。你可以询问数组 $[l,r]$ 的区间和，你最多询问 $20$ 次。请问给你 $n,t,k$，进行 $t$ 次询问（这题很水保证 $t=1$），第 $k$ 个 $0$ 的下标是多少。

## P2 思路：
首先看到最多询问 $20$ 次，就可以感觉到需要使用二分，因为 $2^{20}\ge n$。  

---

思考一下二分查找，找什么呢？  
由于答案是从左往右的第 $k$ 个数组中 $0$ 的下标，所以可以查找从下标 $1$ 开始到下标为 $x$ 的 $0$ 的个数为 $k$，我们要找到这个**最小的** $x$。 

---

在每一次二分中询问 $1-mid$ 的和记为 $res$ 注意这里是 $1$ 的个数，$mid-res$ 才是 $0$ 的个数，可以将 $res \leftarrow mid-res$。
- 若 $res\ge k$，将答案记为 $mid$，接着让 $r\leftarrow mid-1$。
- 否则只需要让 $l\leftarrow mid+1$。

## P3 细节：
- $t$ 虽然没有用，但是一定一定要输入 $t$（我就卡在这里卡了好久）。
- 注意这是交互题，一定一定要清缓存区。

## P4 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n , t , k , ans;
int main(){
    // freopen("in.txt" , "r" , stdin);
    // freopen("out.txt" , "w" , stdout);
    ios::sync_with_stdio(0);
    cin.tie(0) , cout.tie(0);
    cin >> n >> t >> k;
    int l = 1 , r = n;
    for(int l = 1 , r = n , mid , res; l <= r;){//二分查找
        mid = (l + r) / 2;
        cout << "? 1 " << mid << endl;//询问1~mid
        cin >> res;
        res = mid - res;//算出0的个数
        if(res >= k){
            ans = mid;
            r = mid - 1;
        }
        else{
            l = mid + 1;
        }
    }
    cout << "! " << ans << endl;//输出
    return 0;
}
```

---

## 作者：qinshi0308 (赞：5)

## 思路：
这道题可以使用[二分查找](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE/10628618?fr=aladdin)来解决。

很明显，二分查找的左端点 $l=1$，右端点 $r=n$。

**注意：在本题中，输入的 $t$ 毫无用处，只要输入即可。**
### 讨论具体如何进行二分：
对于每一次二分，向 SPJ 询问 $1-mid$ 的和（不妨设这个和为 $x$），如果 $x+k\le mid$，则说明第 $k$ 个 $0$ 在 $mid$ 左边，所以将 $r$ 设为 $mid-1$；反之，如果 $x+k>mid$，则说明第 $k$ 个 $0$ 在 $mid$ 的右边，所以将 $l$ 设为 $mid+1$。

## 代码：

```cpp
# include <bits/stdc++.h>
using namespace std;
inline int work(int n,int k){//二分查找函数 
	int l=1,r=n;
	while(l<=r){
		int mid=(l+r)/2;
		cout<<"? 1 "<<mid<<endl;
		int x;
		cin>>x;
		if(x+k<=mid){
			r=mid-1; 
		}else{
			l=mid+1;
		}
	}
	return l;
}
int main(){
	int n,t,k;
	cin>>n>>t>>k;
	cout<<"! "<<work(n,k);
	return 0;
}

```
**有哪些不明白的地方可以写在评论里，本人会回答。**

---

## 作者：LinkZelda (赞：2)

- **题意**：给定一个序列长度 $n$，你每次可以询问一个区间 $[l,r]$，再给定一个数 $k$，请求出第 $k$ 个 $0$ 的下标。要求询问次数 $\leq 20$。($n \leq2\times 10^5$ )

- $Solution$:

每次询问的区间和可以轻松转化为区间 $0$ 的个数。那么我们可以转化为类似静态全局第 $k$ 大整数那样的做法：对区间进行二分，先查询左区间 $0$ 的个数 $sum$，比较 $k$ 和 $sum$ 的大小：若 $k\leq sum$ 则说明第 $k$ 个 $0$ 在左区间中，否则第 $k$ 个 $0$ 必定在右区间内。递归查询即可。

询问次数为 $\mathit{O}(\log n)$。可以通过本题。

- **核心代码**：
```cpp
	int l=1,r=n,ans;
	while(l<=r)
	{
		int mid=(l+r)>>1,ret;
		cout<<"? "<<l<<' '<<mid<<endl;
		cin>>ret;
		ret=(mid-l+1)-ret;
		if(ret>=k)
			ans=mid,r=mid-1;
		else
			k-=ret,l=mid+1;
	}
	cout<<"! "<<ans<<endl;
```


---

## 作者：FuriousC (赞：1)

$upd1:$ 更改了符号错误

[题目传送门](https://www.luogu.com.cn/problem/CF1520F1)

典型的二分题。

对于当前区间 $[l,r]$ 进行询问并求得区间中 $0$ 的数量，再更新区间范围以及 $0$ 的个数即可。

时间复杂度 $O(logn)$ ，对于 $2^{20}>2 \times 10^5$ 可以通过（毕竟是简单版）。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int r,t,k,l=1;
	cin>>r>>t>>k;//t没啥用= =
	while(l<r){//二分
		int mid=(l+r)>>1;
		cout<<"? "<<l<<" "<<mid<<"\n";//询问区间
		fflush(stdout);
		int tmp;cin>>tmp;
		int num=mid-l+1;
		if(num-res>=k){
			r=mid;//更新区间
		}else{
			k-=(num-res);//减掉此区间中0的个数
			l=mid+1;//更新区间
		}
	}
	cout<<"! "<<l<<"\n";
	fflush(stdout);
	return 0;
}
```


---

## 作者：KSToki (赞：1)

# 题目大意
交互题。给定 $n,t,k$（由于这里是简单版，保证 $t=1$，即 $t$ 没啥用），有一个长度为 $n$ 的标号为 $1\cdots n$ 的仅含 $01$ 的数组，你每次可以询问 $l$ 到 $r$ 的和，需要得出数组中第 $k$ 个 $0$ 的下标。最多询问 $20$ 次。
# 题目分析
看这范围，很自然就能想到二分使询问次数为 $logn$，$l$ 初始为 $1$，$r$ 初始为 $n$。每次询问 $l$ 到 $mid$，计算出这个区间的 $0$ 的个数，如果多于 $k$ 个则将 $k$ 减掉个数，二分 $mid+1$ 到 $r$；否则继续二分 $l$ 到 $mid$。这其实等价于查区间第 $k$ 小，这就一定是个 $0$，~~当然有人想写线段树之类的数据结构我也没拦着~~。
# 代码
很简单的。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k,l=1,r,mid,res;
int main()
{
	cin>>r>>t>>k;
	while(l<r)
	{
		mid=(l+r)>>1;
		cout<<"? "<<l<<" "<<mid<<endl;
		fflush(stdout);
		cin>>res;
		if(mid-l+1-res>=k)
			r=mid;
		else
		{
			k-=mid-l+1-res;
			l=mid+1;
		}
	}
	cout<<"! "<<l<<endl;
	fflush(stdout);
   return 0;
}
```

---

## 作者：_zuoqingyuan (赞：0)

# 题面：
给定 $n,t,k$（由于这里是简单版，保证 $t=1$，即 $t$ 没啥用），有一个长度为 $n$ 的标号为 $1⋯n$ 的仅含 $0,1$ 的数组，你每次可以询问  $l$ 到 $r$ 的和，需要得出数组中第 $k$ 个 $0$ 的下标。最多询问 $20$ 次。

------------
# 分析：
1. “长度为 $n$ 的标号为 $1⋯n$ 的仅含 $0,1$ 的数组，你每次可以询问  $l$ 到 $r$ 的和。”——由于该序列仅含有 $0$ 和 $1$，所以，每次询问 $l$ 到 $r$ 的和，等于询问l到r这个区间内有多少个 $1$，也可以求出有多少个 $0$；

1. 基于上述，我们可以确定进本思路：枚举区间右边界 $r$，使 $1$ 到 $r$ 整个区间内有 $k$ 个零，且 $r$ 尽可能小。由于题目中要求“最多询问 $20$ 次”，因此此题与暴力算法无缘，需要换方向思考。

1. 对于要在二十次询问内在 $2\times 10^5$ 长度的串内找到一个边界，显而易见，可以用到二分算法。有了思路，就可以开始撸代码了，难度不高，代码如下：

------------
# 代码：
```
#include <iostream>
#include <cstdio>
using namespace std;
int n,k,t,l=1,r,mid,x,ans;
int main(){
    scanf("%d %d",&n,&t);
    scanf("%d",&k);
    l=1,r=n;
    while(l<=r){
        mid=(l+r)/2;//寻找中间项
        printf("? 1 %d",mid);
        scanf("%d",&x);
        if(x+k<=mid){
            ans=mid;
            r=mid-1;//在右区间寻找
        }else{
            l=mid+1;//在左区间寻找
        }
    }
    printf("! %d",ans);//得解，输出答案
    return 0;
} 
```

---

## 作者：Intermittent (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1520F1)

### 题意：
这是一道**交互题**。题面已经讲的很清楚，这里不再做解释。
### solution：
由于数据范围可以考虑使用二分。

根据题意，我们可以设左端点 $l$ 为 $1$,右端点 $r$ 为 $n+1$。

- 若 $k+x > mid$, 说明要往右找，令 $l=mid$。
- 若 $k+x \le mid$, 说明要往左找，令 $r=mid$。

最后输出 $r$ 即可。

### code:
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, t, k;

int main()
{
	cin >> n >> t >> k;
	
	int l = 0, r = n + 1; //左端点为0, 右端点为n+1
	while (l < r - 1)
	{
		int mid = (l + r) >> 1; //中间值
		int a;
		cout << "? 1 " << mid << '\n';
		cin >> a;
		if (a + k <= mid) //往左找
			r = mid; 
		else //否则往右找
			l = mid;
	}
	cout << "! " << r;
	return 0;
}
```

---

## 作者：Neilchenyinuo (赞：0)

- 这题可以用二分查找解决。

## Solution

1. 二分区间长度，所以左端点 $lt=0$，右端点 $rt=n+1$。

2. 当 $x+k>mid$ 是，说明 $mid$ 找小了，要往右找，即 $lt=mid$，反之，说明 $mid$ 找大了，需要往左找，即 $rt=mid$。

3. 最后输出 $rt$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,k,x;
int main()
{
	cin>>n>>t>>k;
	int lt=0,rt=n+1;
	while(lt+1<rt)
	{
		int mid=(lt+rt)>>1;
		cout<<"? 1 "<<mid<<"\n";
		cin>>x;
		if(x+k<=mid)
			rt=mid; 
		else
			lt=mid;
	}
	cout<<"! "<<rt;
	return 0;
}
```
### 莫抄袭，没了 AC 记录，空悲切！

---

## 作者：BLuemoon_ (赞：0)

# [CF1520F1 题解]

## 题意

给定一个长度为 $n$ 的 $01$ 序列，你每次可以以```? l r```的形式询问 $l$ 到 $r$ 之间 $1$ 的个数，求序列中第 $k$ 个 $0$ 的位置。（当然还有一个不重要的 $t$）

## 思路

根据数据范围 $\log({2 \times 10^5}) \approx 18 \approx 20$ 想到二分。

$l$ 到 $r$ 之间 $0$ 的个数就是 $r-l+1-cnt$，其中 $cnt$ 为 $l$ 到 $r$ 之间 $1$ 的个数，即询问的答案。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,not_important,k,l,r,m,cnt; //t is not_important
int main()
{
  cin>>n>>not_important>>k;
  l=1,r=n;
  while(l<r)
  {
    m=(l+r)>>1;
    cout<<"? "<<l<<" "<<m<<endl;
    cin>>cnt;
    int tmp=m-l+1-cnt;
    if(tmp>=k)
      r=m;
    else
      k-=tmp,l=m+1;
  }
  cout<<"! "<<l<<endl;
  return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# CF1520F1 题解



## 思路分析

简单版本是非常容易解决的，直接在原序列上进行二分，每次检查 $1\sim x$ 中 $0$ 的个数是否超过 $k$ 即可，询问次数 $\log_2 n$ 次。

时间复杂度 $\Theta(\log n)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
inline int read(int l,int r) {
	cout<<"? "<<l<<" "<<r<<endl;
	int ret; cin>>ret; return ret;
}
int n,T,k;
inline bool check(int x) {
	return x-read(1,x)>=k;
}
signed main() {
	cin>>n>>T;
	while(T--) {
		cin>>k;
		int l=1,r=n,res=0;
		while(l<=r) {
			int mid=(l+r)>>1;
			if(check(mid)) res=mid,r=mid-1;
			else l=mid+1;
		}
		cout<<"! "<<res<<endl;
	}
	return 0;
}
```



---

## 作者：云浅知处 (赞：0)

## F1.Guess the K-th Zero（Easy ver.）

### Description

交互题。

给一个长为 $n$ 的 $01$ 序列 $a$，每次可以询问

$$
\sum_{i=l}^ra_i
$$

在 $20$ 次询问内确定第 $k$ 个 $0$ 的位置。保证第 $k$ 个 $0$ 存在。

$1\le n\le 2\times 10^5$。

### Solution

询问的东西本质上是 $[l,r]$ 内 $1$ 的个数，由此可以直接推出来 $[l,r]$ 内 $0$ 的个数。

考虑二分。

如果我们现在要求 $[l,r]$ 内的第 $k$ 个 $0$，那么，令 $\text{mid}=\dfrac{1}{2}(l+r)$，接着：

- 先查询一次 $[l,\text{mid}]$ 内 $0$ 的个数 $p$。
- 若 $p<k$ 则说明第 $k$ 个 $0$ 在 $[\text{mid+1},r]$ 里
- 那么就 $\texttt{k-=p}$，然后继续查询 $[\text{mid+1},r]$。
- 否则直接转到 $[l,\text{mid}]$ 里。

这样，询问次数就不会超过 $\log_2(2\times 10^5)<18$ ，足以通过本题。

```cpp
#include<cstdlib>
#include<iostream>
#include<cstring>

#define int long long

using namespace std;

int n,t,k;
int ans=0,anstmp;

signed main(void){

    cin>>n>>t;
    cin>>k;

    int l=1,r=n;
    while(l<r){
        int mid=(l+r)>>1;
        cout<<"? "<<l<<" "<<mid<<"\n";
        cin>>ans;
        int num=(mid-l+1)-ans;
        if(num>=k)r=mid;
        else if(num<k)l=mid+1,k-=num;
    }

    cout<<"! "<<l<<endl;

    return 0;
}
```

---

