# [ABC107C] Candles

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc107/tasks/arc101_a

数直線上に $ N $ 本のろうそくが置かれています。 左から $ i $ 番目のろうそくは座標 $ x_i $ に置かれています。 ただし、$ x_1\ <\ x_2\ <\ ...\ <\ x_N $ が成り立ちます。

最初、どのろうそくにも火が付いていません。 すぬけ君は、$ N $ 本のうち $ K $ 本のろうそくに火を付けることにしました。

今、すぬけ君は座標 $ 0 $ にいます。 すぬけ君は、数直線上を左右に速度 $ 1 $ で移動することができます。 また、自分と同じ座標のろうそくに火を付けることができます。 このとき、火を付けるのに掛かる時間は無視できます。

$ K $ 本のろうそくに火を付けるのに必要な最小の時間を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ K\ \leq\ N $
- $ x_i $ は整数である。
- $ |x_i|\ \leq\ 10^8 $
- $ x_1\ <\ x_2\ <\ ...\ <\ x_N $

### Sample Explanation 1

次のように移動しながらろうそくに火を付ければよいです。 - 座標 $ 0 $ から $ -10 $ へ移動する。 - 左から $ 2 $ 番目のろうそくに火を付ける。 - 座標 $ -10 $ から $ 10 $ へ移動する。 - 左から $ 3 $ 番目のろうそくに火を付ける。 - 座標 $ 10 $ から $ 20 $ へ移動する。 - 左から $ 4 $ 番目のろうそくに火を付ける。

### Sample Explanation 3

座標 $ 0 $ にろうそくが置かれていることもあります。

## 样例 #1

### 输入

```
5 3
-30 -10 10 20 50```

### 输出

```
40```

## 样例 #2

### 输入

```
3 2
10 20 30```

### 输出

```
20```

## 样例 #3

### 输入

```
1 1
0```

### 输出

```
0```

## 样例 #4

### 输入

```
8 5
-9 -7 -4 -3 1 2 3 4```

### 输出

```
10```

# 题解

## 作者：fengenrong (赞：5)

其实这道题没有那么复杂，我们可以先用一个变量 $d$ 来表示第一个非负出现的位数。接着在进行判断，要是 $d$ 是等于 $0$ 的（就是没有找到，都是负数），我们就可以直接输出 $A_{n - k + 1}$ 的绝对值。否则我们就暴力枚举每一个点，用一个 $i$ 表示左端，$j$ 表示右端。在这里，又分为两种情况。

一：都是正数，我们可以直接让 $ans=\min(ans,A_j)$，也就是让它直接走过去。

二：有正数也有负数，我们既可以先去负数那，再回到正数；也可以先去正数在回到负数。就是：$ans=\min(ans,|A_i\times2|+ A_j,|A_i|+A_j\times2)$。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[10000005], n, d, k, ans = LLONG_MAX;//先设成一个极大值
signed main() {
    cin >> n >> k;
    for (register int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] >= 0 && (a[i - 1] < 0 || i == 1))//找第一个大于0的数
        {
            d = i;//赋值
        }
    }
    if (d == 0) {//都是负数
        cout << abs(a[n - k + 1]);//输出所需的最短时间
        return 0;
    }
    int op = 1;
    for (register int i = max(d - k - 1, op), j = i + k - 1; i <= d, j <= n; i++, j++) //i是左，j是右
    {
        if (a[i] >= 0) {//全是正数
            ans = min(ans, a[j]);//利用公式
        } else {//正数，负数都有
            ans = min(ans, min(abs(abs(a[i] * 2) + a[j]), abs(abs(a[i]) + (a[j] * 2))));//利用公式
        }
    }
    cout << abs(ans);//输出，防止是负数
    return 0;
}
```

---

## 作者：run_away (赞：1)

## 题意

在一个数轴上有 $N(1\le N\le 10^5)$ 个点，给定每个点的位置 $x_i$ (横坐标)，保证 $x_i$ 单调递增且 $|x_i|\le 10^8$ 。求从原点出发，到达不同的 $K(1\le K\le N)$ 个点所经过的最小距离。

## 分析

我们看到 $N$ 的范围正好卡掉 $O(N^2)$ ，但 $O(N)$ 可以过~~不然怎么输入~~，且点都在一条直线上，所以可以考虑直接遍历求解。

事实上，一眼就可以看出来所选的 $K$ 个点应该是连续的。所以 $x_i$ 会有三种情况：全为正，全为负或有正有负。设左边界为 $i$ ，右边界就为 $i+k-1$ (注意这个`-1`)。

1. 所有 $x_i$ 都为正数时，如图：
![图炸了](https://pic.imgdb.cn/item/65b10684871b83018aff896e.png)
可以得到此时的答案为 $x_{i+k-1}$ 。
2. 所有 $x_i$ 都为负数时，如图：
![图炸了](https://pic.imgdb.cn/item/65b1085f871b83018a080e76.png)
可以得到此时答案为 $x_i$ 。
3. 当有正有负时，如图：
![图炸了](https://pic.imgdb.cn/item/65b109b6871b83018a0e2830.png)
可得答案为 $\min(x_{i+k-1},x_i)+x_{i+k-1}-x_i$ 。

通过对以上的归纳，我们可以发现，最短的路应该是先往 $|x|$ 小的一边走，再往另一端走或继续向前。所以答案为 $ans=x_{i+k-1}-x_i+\min(x_{i+k-1},x_i)$ (因为 $i+k-1$ 一定在 $i$ 的右边或与 $i$ 重合，所以 $|x_{i+k-1}|-|x_i|$ 为正)。

最终，时间复杂度为 $O(N)$ 。

## Code

```c++
#include<bits/stdc++.h>
typedef long long ll;//可以不开long long
char buf[1<<21],*p1=buf,*p2=buf,obuf[1<<21],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
inline void write(ll x){if(x<0)putchar(45),x=-x;if(x>9)write(x/10);putchar(x%10+48);}//以上为模板
ll n,k,x[100005],ans=LONG_LONG_MAX;//注意ans的初始值为极大值
signed main(){
    n=read(),k=read();
    for(ll i=1;i<=n;++i)x[i]=read();
    for(ll i=1;i+k-1<=n;++i){
        ans=min(ans,x[i+k-1]-x[i]+min(abs(x[i]),abs(x[i+k-1])));//式子
    }
    write(ans);
    return 0;
}
```

---

## 作者：Kyl_in_2024 (赞：0)

**前言**

~~[We Love ABC！](https://www.luogu.com.cn/problem/AT_abc104_d)~~

好的进入正题。

**思路**

这题评黄不是没有原因的，数据范围非常良心，而且开关的位置单调递增。

首先可以明确一点，最终开到的开关肯定能组成一个连续区间。我是这么想的，如果最终答案不连续，那么中间不连续的开关肯定已经经过了，那么何不先把它按了然后少走几步呢？

接下来我们要做的就是枚举长度为 $k$ 的区间，复杂度 $O(n)$，然后计算答案。

一个区间有两种可能，一种走法是先走到左端点，再去右端点，或者先走到右端点，再去左端点。因为从左端点走到右端点和从右端点到左端点的代价是一样的，所以计算公式是 $ \min(\left | l \right | ,\left | r \right | ) + \left | l-r \right | $，这里，$l$ 代表左端点，$r$ 代表右端点。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int x[100008];
signed main(){
	int n,k,ans=2147483647;
	cin >> n >> k;
	for(int i=1;i<=n;i++){
		cin >> x[i];
	}
	for(int i=1;i+k-1<=n;i++){
		int l=x[i],r=x[i+k-1];
		ans=min(ans,min(abs(l),abs(r))+abs(l-r));
	}
	cout<<ans;
	return 0;
} 
```

[AC 记录](https://atcoder.jp/contests/abc107/submissions/52426744)

---

## 作者：ForgetOIDuck (赞：0)

### 思路：

首先考虑选哪些开关。

易得最后选择的开关一定是连续的，因为跳过一个开关去选后面的一个开关只会使答案更劣。

因为题目给定的 $x$ 数组是单调递增的，所以每连续 $k$ 个开关可以转换为 $x$ 上一段长度为 $K$ 的区间。

所以这题就可以 $O(N)$ 地枚举每个长度为 $K$ 的区间，并对每个区间求答案后找出最小值。

对于 $x$ 的一个区间 $[l,r]$（$l,r$ 为下标）我们有两种走法：
1. 从 $0$ 走到 $x_l$，再从 $x_l$ 走到 $x_r$，答案应该是 $|x_l| + |x_l - x_r|$；
1. 从 $0$ 走到 $x_r$，再从 $x_r$ 走到 $x_l$，答案应该是 $|x_r| + |x_l - x_r|$。

两者取最小值得 $\text{min}\{|x_l|,|x_r|\} + |x_l-x_r|$。

## AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, x[100002], ans = 1145141919;
int main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i ++ ) cin >> x[i]; 
	for (int i = 1; i + k - 1 <= n; i ++ ) ans = min(ans, abs(x[i + k - 1] - x[i]) + min(abs(x[i + k - 1]), abs(x[i])));
	cout << ans;
} 
```

---

## 作者：chl090410 (赞：0)

## The Solution to AT_arc101_a [ABC107C] Candles

### Description

[题目传送门](https://www.luogu.com.cn/problem/AT_arc101_a)

### Solution

我们设正方向要打开 $k$ 个开关（$k\le m$ 且 $k$ 可以为 $0$），则负方向要打开 $m-k$ 个开关。因为打开完先去的方向上的开关后要回到原点才能继续打开另一个方向上的开关（打开完所有开关后不需要回到原点），所以先去的方向上走的路程要乘以 $2$。

我们从小到大枚举 $k$，因为先去打开正负方向上的开关都可以，所以该方案的最短时间为两种方法中耗时短的那个，而题目要求打开门最短时间，所以最终答案为所有方案中耗时最短的方案所需的时间。

### AC code 如下：

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,a[100005],z[100005],f[100005],qz[100005],qf[100005],ans,mx=2147483644,mmx,k,kk,m;
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	cin>>a[i];
    	if(a[i]>=0){
    		z[++k]=a[i];
		}else{
			f[++kk]=-a[i];
		}
	}
	sort(z+1,z+1+k);
	sort(f+1,f+1+kk);
	if(m<=min(k,kk)){
		for(int i=0;i<=m;i++){
			mmx=min(z[i]+f[m-i]*2,z[i]*2+f[m-i]);
			mx=min(mx,mmx);
		}
	}else{
		for(int i=m-kk;i<=k;i++){
			mmx=min(z[i]+f[m-i]*2,z[i]*2+f[m-i]);
			mx=min(mx,mmx);
		}
	}
	cout<<mx;
	return 0;
}

---

## 作者：XYQ_102 (赞：0)

题目传送门：[ABC107_c & ARC101_a](https://atcoder.jp/contests/arc101/tasks/arc101_a)

题意很好理解，就是在数轴上的 $n$ 个点选出 $k$ 个，计算出最小距离即可。

至多只有 $10^5$ 的点，循环一遍也不会超时，那么就从最左边的点开始每  $k$ 个计算一次距离，求出最小的即可。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100005],ans=1e18;
int main() 
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    int l,r;
    for(int i=1;i+k-1<=n;i++)
	{
        l=i,r=i+k-1;
        ans=min(ans,a[r]-a[l]+min(abs(a[l]),abs(a[r])));
    }
    cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：RioFutaba (赞：0)

# 题意
有 $N$ 根蜡烛，第 $i$ 根的坐标为 $x_i$（输入单调递增）。当前坐标有蜡烛时，可以点燃这根蜡烛。问点燃任意 $K$ 根蜡烛最少需要移动多少次。

数据范围：$1 \le K \le N \le 10^5$，$0 \le |x_i| \le 10^8$
# 思路
观察样例：
```
N=5 K=3
-30 -10 10 20 50

```
最佳的操作应该是从 $0$ 跑到 $-10$ 处，然后再往正方向一直走，依次点燃 $-10$，$10$，$20$ 处的蜡烛。

不难想到，最佳的操作应该是点燃一个区间的蜡烛，即先跑到这个区间离自己最近的端点，再跑到另一个端点，点燃途中的所有蜡烛。

那么我们枚举每一个包含 $K$ 个蜡烛的坐标区间，然后统计最小的移动次数即可。

设左端点为 $x_i$，右端点为 $x_j$。

移动次数为：

- 跑到一个端点：$\min(|x_i|,|x_j|)$。
- 再跑到另一个端点：$x_j-x_i$。

总移动次数为 $\min(|x_i|,|x_j|)+(x_j-x_i)$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=1e5+5,INF=0x3f3f3f3f;
int n,k,x[maxn],ans=INF;//ans先赋一个极大值 
int main(){
	scanf("%d%d",&n,&k); 
	for(int i=1;i<=n;i++) scanf("%d",&x[i]);
	for(int i=1,j=k;j<=n;i++,j++) ans=min(ans,min(abs(x[i]),abs(x[j]))+(x[j]-x[i]));//每个区间扫一遍，统计答案 
	printf("%d\n",ans);//输出 
	return 0;
} 
```

---

## 作者：RioBlu (赞：0)

**分类讨论知真知**，用左端点和右端点的正负情况来分类讨论

①$left<=0,right<=0,$此时应该要走$-l$（这里和下文的$l$指左端点，$r$指右端点）单位长度

②$left<=0,right>0,$此时应该要走$min(r-2l,2r-l)$单位长度

这个就是说$Lin$，**先走到点r再走到点l的路程**还是**先走到点l再走到点r的路程**短

③$left>=0,right>=0,$此时应该要走$r$单位长度
```
#include<bits/stdc++.h>
using namespace std;
long long a,n,k[100005],ans=999999999999999;
int main()
{
	cin>>a>>n;
	for(int s=1;s<=a;s++)
	{
		cin>>k[s];
		if(s>=n)
		{
			if(k[s]<=0&&k[s-n+1]<=0)
			ans=min(ans,-k[s-n+1]);
			if(k[s]>0&&k[s-n+1]<=0)
			ans=min(ans,k[s]-k[s-n+1]*2);
			if(k[s]>=0&&k[s-n+1]>=0)
			ans=min(ans,k[s]);
		}
	}
	cout<<ans<<endl;
}
```

---

