# Chocolates

## 题目描述

You went to the store, selling $ n $ types of chocolates. There are $ a_i $ chocolates of type $ i $ in stock.

You have unlimited amount of cash (so you are not restricted by any prices) and want to buy as many chocolates as possible. However if you buy $ x_i $ chocolates of type $ i $ (clearly, $ 0 \le x_i \le a_i $ ), then for all $ 1 \le j < i $ at least one of the following must hold:

- $ x_j = 0 $ (you bought zero chocolates of type $ j $ )
- $ x_j < x_i $ (you bought less chocolates of type $ j $ than of type $ i $ )

For example, the array $ x = [0, 0, 1, 2, 10] $ satisfies the requirement above (assuming that all $ a_i \ge x_i $ ), while arrays $ x = [0, 1, 0] $ , $ x = [5, 5] $ and $ x = [3, 2] $ don't.

Calculate the maximum number of chocolates you can buy.

## 说明/提示

In the first example, it is optimal to buy: $ 0 + 0 + 1 + 3 + 6 $ chocolates.

In the second example, it is optimal to buy: $ 1 + 2 + 3 + 4 + 10 $ chocolates.

In the third example, it is optimal to buy: $ 0 + 0 + 0 + 1 $ chocolates.

## 样例 #1

### 输入

```
5
1 2 1 3 6
```

### 输出

```
10```

## 样例 #2

### 输入

```
5
3 2 5 4 10
```

### 输出

```
20```

## 样例 #3

### 输入

```
4
1 1 1 1
```

### 输出

```
1```

# 题解

## 作者：Sammy_prime (赞：4)

[CF1139B](https://www.luogu.com.cn/problem/CF1139B)

# 思路

可以反向贪心，在上次取的个数减一和这次可以取的最多数量之间取最小值，但是不能减负数。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n; ll a[N],minn=1<<30,tot;
int main(){
	freopen("chocolates.in","r",stdin);
	freopen("chocolates.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	    scanf("%d",&a[i]);
	for(int i=n;i>=1;i--){
		minn=min(a[i],minn-1);
		if(minn>0) tot+=minn;
	}
	printf("%lld\n",tot);
	return 0;
}
```


---

## 作者：xiaojuruo (赞：2)

## 分析
有 $n$ 个巧克力，要求巧克力购买数量从小到大，那么不妨倒推。这样，我们只需要满足当前购买巧克力的数量小于上一次购买的巧克力数量即可。
## AC 代码
一些可能难懂一点代码我都写在代码里面了，请放心食用。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000001],x,sum=0,ans=9999999999;
//ans要赋值，因为不赋值，程序会误认为我们上一次购买了0个巧克力
int main(){
	cin>>x;
	for(int i=1;i<=x;i++) cin>>a[i];
	for(int i=x;i>=1;i--){//从后面开始倒推 
		ans=min(a[i],ans-1);//判断是否小于上一个购买的巧克力
 		if(ans<=0) break; 
      //如果我买到了小于0个巧克力，那这时候我买巧克力就是不必要的了。 
		if(ans>0) sum+=ans;  
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：xht (赞：2)

题目地址：[CF1139B Chocolates](https://www.luogu.org/problemnew/show/CF1139B)

前一个必须要少于后一个，那么模拟+贪心即可

倒序模拟，每次在上次取的个数减一和这次可以取的最多数量之间取min

直到为0（注意不要减到负数）

再就是注意开long long

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 6;
int n, a[N], x = 1e9 + 1;
ll ans;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = n; i; i--) {
        x = min(a[i], x - 1);
        if (x > 0) ans += x;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：fish_shit (赞：1)

## 思路
考虑倒序遍历，这样就可以按照题意去模拟了。

为了让取到的巧克力更多，又要满足条件，可以去判断一下这次的巧克力的总个数是不是比上一轮取的个数减 $1$ 还要多。如果多了就不满足要求，只能选择上一轮取的个数减 $1$ 个；否则就可以选这次的巧克力的总个数。

注意：如果这次取的个数小于 $0$ 个，就说明不能再取了，跳出循环就可以了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[210000],cnt,pos=1e10;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=n;i>=1;i--){
		if(a[i]>pos-1){
			pos-=1;
		}	
		else{
			pos=a[i];
		}
		if(pos<0){
			break;
		}
		cnt+=pos;
	}
	cout<<cnt;
	return 0;
} 
```


---

## 作者：ink_ngm (赞：1)

分析一下题目：为了使能获得的巧克力数量尽量多，因此，我们应该尽可能的多拿多种巧克力——即**使每种巧克力之间的差尽可能维护为 $1$ 个巧克力。** 当然，如果该种巧克力后没有其他种类的巧克力，也便可以全部拿取。


那么，该怎么模拟呢？我们可以利用贪心的思路：因为题面已经保证该巧克力数量的序列为升序，因此，第 $x_{n}$ 个巧克力种类即为最多的一种巧克力。我们便可以从最后一个巧克力往前模拟：如果可以取上一个巧克力数减一的巧克力数，则可以取该种巧克力，如果反之，则在此处巧克力之前的巧克力都不能取了，便可跳出循环。


```
#include<bits/stdc++.h>
using namespace std;
inline long long read() {
    register int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') { if (ch == '-') f = -1; ch = getchar(); }
    while (ch >= '0' && ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x * f;
}
long long n,a[200005],x=1<<30;
long long ans;
int main(){
	freopen("chocolates.in","r",stdin);
    freopen("chocolates.out","w",stdout);
    n=read();
    for (register int i=1;i<=n;++i)a[i]=read();
    for (register int i=n;i;i--){
        x=min(a[i],x-1);
        if (x<=0) break;
        ans+=x;
    }
    printf ("%lld\n",ans);
    return 0;
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路

为保证购买的巧克力最多，显然购买第 $i$ 种类最多时，第 $i+1$ 种保证大于第 $i$ 种，此时我们从后往前贪，尽可能的多取。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,a[200019],maxget=0x3f3f3f3f,ans=0;

signed main() 
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for (int i=n;i>=1;i--) 
	{
		maxget=min(a[i],maxget-1);//判断当前可以取的量
		if(maxget>0) ans+=maxget;
		else break;//如果maxget等于零，此时退出循环
		//毕竟当前是零了，之后都无法取值了。
	}
	cout<<ans;
	return 0;
}

---

## 作者：fchwpo (赞：0)

考虑贪心使每一位最大，那么就是使每一位等于 $\min(a_i,a_{i+1}-1)$ ，然后直接将所有将所有大于零的部分加到一起就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
int n,ans,a[maxn]; 
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=n-1;i;i--){
		a[i]=min(a[i],a[i+1]-1);
	}
	for(int i=1;i<=n;i++) if(a[i]>=0) ans+=a[i];
	cout<<ans;
	return 0;
}

```

---

## 作者：__YancBuxIya (赞：0)

#### [题目传送门](https://www.luogu.com.cn/problem/CF1139B)

---

## 题目分析：
由题目中我们可以发现，第 $i$ 个巧克力的购买数量受到两个因素的限制：

- 第 $i$ 个巧克力本身的库存量。
- 第 $i+1$ 个巧克力购买的数量。

而第一个条件由题目中输入，故第二个条件成了我们决定所购买 $i$ 个巧克力的最多数量。

那我们可以想到，从第 $n$ 个巧克力的库存开始遍历，倒序判断购买巧克力的数量。

---
## 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	long long ans=a[n];//2*10^5 * 10^9 显然需要long long  
	int lst=a[n];//ans为答案，lst表示上一个买的数量  
	for(int i=n-1;i>=1;i--){
		if(a[i]<lst){//库存少，全部买掉  
			ans+=a[i];
			lst=a[i];
		}else{//lst少，买lst-1个 
			int ind=min(a[i],lst)-1;//此处需要-1，因为是严格小于 
			if(ind<=0) break;//已经买不了了，直接退出  
			ans+=ind; 
			lst=ind;//更新lst  
		}
	}
	printf("%lld\n",ans); 
	return 0;
} 
```
---
[AC记录](https://www.luogu.com.cn/record/129529144)

---

## 作者：2021sunzishan (赞：0)

一道及其水的题。
## 题目大意：
给定 $n$ 种巧克力，每种有 $a_i$ 个，要求买的巧克力必须呈最长上升子序列（当然，可以出现连续的 $0$ 的情况）。问最多买多少块巧克力。

## 思路：
显然，第 $n$ 种巧克力一定会选 $a_n$ 个，如有不懂请自行模拟一下样例。

那么我们只需要倒序枚举，每一次买 $\min(a_i,a_{i+1}-1)$ 就可以了。

非常好理解对不对？

如果还有不懂的，就看看代码吧！

**切勿抄袭！！！**

## 代码 ：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long//这题要开long long哦，这里偷个懒
int a[200005],n;
inline int read() {//快读
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
main() {
//	freopen("chocolate.in","r",stdin);
//	freopen("chocolate.out","w",stdout);
	n=read();
	for(int i=1; i<=n; i++)
		a[i]=read();
	int ans=a[n],l=a[n]-1;//l表示上一次的-1
	for(int i=n-1; i>=1; i--) 
		if(a[i]<=l) {//因为有0的特判，不能直接取min，但原理一样
			l=a[i]-1;
			ans+=a[i];
		} else {
			ans+=l;
			if(l)l--;//大于0的情况 
		}
	printf("%lld\n",ans);
	return 0;
}

```

完结~

---

## 作者：CRTL_xzh2009 (赞：0)

反向贪心。

鉴于难以从前往后考虑，所以采用逆推法。

先定义 $now$ 和 $ans$ 为最后一个。$ans$ 记录最终答案，$now$ 记录当前能取的最大值。

对于当前的 $a_i$，最多能买 $now-1$ 个（因为不能比后面一个大），并且在 $a_i$ 的范围内，即：`now=max(0,min(now-1,a[i]))`。

$ans$ 每次加上 $now$ 值即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100005];
signed main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	scanf("%d",&a[i]);
	int now=a[n];
	int ans=now;
	for(int i=n-1;i>=1;i--)
	{
		now=min(now-1,a[i]);
		if(now<0)
		now=0;
		ans+=now;
	}
	cout<<ans<<endl;
	return 0;
} 
```


---

## 作者：User757711 (赞：0)

# [CF1139B Chocolates](https://www.luogu.com.cn/problem/CF1139B) 题解
### 题目大意
共有 $n$ 块巧克力，要求获得的数量最多。
### 思路分析 
可以倒序模拟，在下一个和上次取得数减一之间取更小值。

注意：不开 long long 见祖宗！！！
### 最后，附上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ans;
int a[200050],x=INT_MAX;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=n;i>=1;i--) //倒序模拟
	{
		x=min(a[i],x-1); //去更小值
		if(x>0) 
		{
			ans+=x; //累加答案
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：TRZ_2007 (赞：0)

**[题解 【CF1139B Chocolates】](https://www.luogu.com.cn/problem/CF1139B)**    
# Solution  

显然，关于任意的 $x_i$，它都会比前面的所有 $x_j$ 都要大**或者**它后面的数全部都是 0，因为我们要求让 $\sum x_i$，达到最大值，故我们希望让 0 少一些，即让这个数列 $x$ 下降的慢一些，因此应该让现在的 $a_i$ 和 $x_{i + 1} - 1$ 两个数进行比较，取其中的最小值作为 $x_i$。注意 $x_i$ 根据题意大于等于 0，判断一下就解决了。  
~~最后贴一下最优解代码。~~  
~~记得开 long long。~~
# Code  
```cpp
#include <cstdio>
#include <cctype>
using namespace std;

#define gc getchar
inline int read() {
	int c = gc(), t = 1, n = 0;
	while(isspace(c)) { c = gc(); }
	if(c == '-') { t = -1, c = gc(); }
	while(isdigit(c)) { n = n * 10 + c - '0', c = gc(); }
	return n * t;
}
#undef gc

const int N = 2e5 + 9;
typedef long long ll;
#define min(a,b) a > b ? b : a

ll a[N],x,sum;
int n;

int main() {
	n = read(); x = 1e10;
	for(int i = 1;i <= n;i++) a[i] = read();
	for(int i = n;i >= 1;i--) {
		x = min(a[i],x - 1);	//获得本次的xi
		sum += (x > 0) ? x : 0;	//任意的xi都大于等于0
	}
	printf("%lld\n",sum);
	return 0;
}
```

---

## 作者：CJ_LIU_XC (赞：0)

Algorithms：模拟和贪心

思路应该不难想出，每次和上次 $-1$ 即可。

这个时候再把处理过后取个 $min$。

于是就可得出：

```cpp
x = min(a[i], x - 1);
```

这个式子（$i$ 为循环变量）。

温馨提示：不开 $long$ $long $会见祖宗。

万众瞩目的AC code来了：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
int read()
{
    int ans = 0;
    char ch = getchar();
    while (!isdigit(ch) && ch != '-') ch = getchar();
    bool sign = false;
    if (ch == '-') sign = true, ch = getchar();
    while (ch >= '0' && ch <= '9') ans = ans * 10 + (ch - '0'), ch = getchar();
    return (sign == true ? -ans : ans);
}

using namespace std;

const int N = 2e5 + 6;

int n, a[N], x = 1e9 + 1;
ll ans;

int main() 
{
	n = read();
    for (int i = 1; i <= n; i++) a[i] = read();
    for (int i = n; i; i--) 
	{
        x = min(a[i], x - 1);
        if (x > 0) ans += x;
    }
    cout << ans << endl;
    return 0;
}
```


---

