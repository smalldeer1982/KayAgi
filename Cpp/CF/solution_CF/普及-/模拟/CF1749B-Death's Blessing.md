# Death's Blessing

## 题目描述

You are playing a computer game. To pass the current level, you have to kill a big horde of monsters. In this horde, there are $ n $ monsters standing in the row, numbered from $ 1 $ to $ n $ . The $ i $ -th monster has $ a_i $ health and a special "Death's Blessing" spell of strength $ b_i $ attached to it.

You are going to kill all of them one by one. It takes exactly $ h $ seconds to kill a monster with health $ h $ .

When the $ i $ -th monster dies, it casts its spell that increases the health of its neighbors by $ b_i $ (the neighbors of the $ j $ -th monster in the row are the monsters on places $ j - 1 $ and $ j + 1 $ . The first and the last monsters have only one neighbor each).

After each monster is killed, the row shrinks, so its former neighbors become adjacent to each other (so if one of them dies, the other one is affected by its spell). For example, imagine a situation with $ 4 $ monsters with health $ a = [2, 6, 7, 3] $ and spells $ b = [3, 6, 0, 5] $ . One of the ways to get rid of the monsters is shown below:

  $ 2 $  $ 6 $  $ 7 $  $ 3 $  $ \xrightarrow{6\ s} $  $ 8 $  $ 13 $  $ 3 $  $ \xrightarrow{13\ s} $  $ 8 $  $ 3 $  $ \xrightarrow{8\ s} $  $ 6 $  $ \xrightarrow{6\ s} $  $ \{\} $  $ 3 $  $ 6 $  $ 0 $  $ 5 $  $ 3 $  $ 0 $  $ 5 $  $ 3 $  $ 5 $  $ 5 $ The first row represents the health of each monster, the second one — the power of the spells.As a result, we can kill all monsters in $ 6 + 13 + 8 + 6 $ $ = $ $ 33 $ seconds. Note that it's only an example and may not be the fastest way to get rid of the monsters.

What is the minimum time required to kill all monsters in the row?

## 说明/提示

In the first test case, there is only one monster that will be killed in $ 10 $ seconds.

In the second test case, it's optimal to kill the first monster, the last monster and then the middle one. It will take $ 100 + 100 + (1 + 1 + 1) $ $ = $ $ 203 $ seconds.

In the third test case, it's optimal to kill the first monster, then the third one, then the fourth one and finally the second one. It will take $ 2 + 7 + (3 + 0) + (3 + 6 + 5) $ $ = $ $ 26 $ seconds.

## 样例 #1

### 输入

```
4
1
10
0
3
100 1 100
1 100 1
4
2 6 7 3
3 6 0 5
2
1000000000 1000000000
1000000000 1000000000```

### 输出

```
10
203
26
3000000000```

# 题解

## 作者：Yang818 (赞：4)

## 分析

读完题目首先知道 $a_i$ 是都要加进去的，所以只考虑 $b_i$。

$b_i$ 会被加到两边的元素上，但是第一个和最后一个只用加一次，又因为 $b_i$ 不会被改变，所以每个 $b_i$ 都要被加，所以最优解一定是不断地删除两边的元素，这样可以起到每个 $b_i$ 都只被加一次，最大的 $b_i$ 不用加的结果。

## 小技巧

看到删来删去首先会想到链表来存，其实不用，可以逆向思维一下，就是先把所有 $a_i$ 和 $b_i$ 都加进去，最后减去做大的  $b_i$ 即可。如果没有理解，请看公式。

$$\sum_{i=1}^n{a_i}+\sum_{i=1}^n{b_i}-\max_{i=1}^n{b_i}$$

## 代码

```cpp
#include<bits/stdc++.h>
#define F(_b,_e) for(int i=_b;i<=_e;i++)
using namespace std;

inline int read(){
	int f=1,x=0;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f*x;
}
int a,n,t;
long long sum;
int main(){
	//ios::sync_with_stdio(0);
	t=read();
	while(t--){
		n=read();
		sum=0;
		F(1,n){
			a=read();
			sum+=a;
		}
		int maxx=-1;
		F(1,n){
			a=read();
			maxx=max(maxx,a);
			sum+=a;
		}
		cout<<sum-maxx<<endl;
	}
	return 0;
}

```


---

## 作者：Strelitzia_ (赞：3)

## 题目大意

给定 $n$ 个二元组 $\{(a_i,b_i)\}$，定义删除一个二元组的代价为 $a_i$，且会让与其相邻的二元组的 $a_i$ 增加 $b_i$。求删除所有二元组的最小代价。

------------
## 思路

我们考虑整个删除过程。

注意到：所有二元组的 $a_i$ 与 $b_i$ 是一个定值，且所有二元组的 $b_i$ 最后都会被加到相邻二元组的 $a_i$ 上去（除了最后一个被删除的二元组），且对于任意的 $1\le i\le n$ 有 $b_i\ge 0$，那么我们考虑如何让 $b_i$ 产生的代价最小。

我们考虑：先找到 $b_i$ 最大的二元组，这个二元组的 $b_i$ 不能产生影响；然后我们不断从两侧删除，这样所有 $b_i$ 都只能对另一个二元组产生影响。这样做的代价是 $\displaystyle\sum_{i=1}^n(a_i+b_i)-b_{\max}$，一定是最优的。

证明一下：如果不这么选，那么必定会至少有一个 $b_i$ 被加两次，于是有 $\displaystyle\sum_{i=1}^n(a_i+b_i)-b_{\max}+b_i\ge \displaystyle\sum_{i=1}^n(a_i+b_i)-b_{\max}$，不会比原来的好。

于是我们只需要求出 $\displaystyle\sum_{i=1}^n(a_i+b_i)-b_{\max}$。就好了。代码如下：

```cpp
int t,n,ans,mx;struct E{int hth,d,l,r;}s[N];
signed main(){
	t=read();for(int nowt=1;nowt<=t;nowt++){
		n=read(),ans=0,mx=0;for(int i=1;i<=n;i++) s[i].hth=read(),ans+=s[i].hth;
		for(int i=1;i<=n;i++){
			s[i].d=read();mx=max(mx,s[i].d);ans+=s[i].d;
		}printf("%lld\n",ans-mx);
	}return Strelitzia_H;
}
```

---

## 作者：东灯 (赞：2)

首先明确一件事：$a$ 与 $b$ 无关。

我们只考虑对于每一个元素的 $b$ 尽可能对解做出的祸害最小，因为 $a$ 那些付出的代价是一定会有的。因此可以直接贪心从两边贪心的找 $b$ 最小的元素开始删，这样无论如何每个元素删除时值给左边或者右边加上自己的 $b$ 值，还能保证结果最小。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
#define MAXN 200005
int t,n,a[MAXN],b[MAXN];
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        int left=1,right=n,ans(0);
        for(register int i=1;i<=n;++i)cin>>a[i];
        for(register int i=1;i<=n;++i)cin>>b[i];
        while(left!=right){
            if(b[left]<b[right]){
                ans+=a[left];
                a[left+1]+=b[left];
                ++left;
            }else{
                ans+=a[right];
                a[right-1]+=b[right];
                --right;
            }
        }
        ans+=a[left];
        cout<<ans<<endl;
    }
}
```


---

## 作者：JOKER_chu (赞：1)

题目是啥意思是个人都看得懂吧，~~我不是人~~。

总之，题目要你求出删掉整个 a 元组的最小代价，显而易见的贪心，每删一个 $a_i$ 就要花 $a_i$ 的价格，那么相邻的两个地方也要增加 $b_i$，求删除整个 a 元组的**最小价格**。

我们从两边开始贪心，我们知道每个 $a_i$ 都要删，那么每个 $b_i$ 就也同样要删，又知道，从两边开始删除的话，每个 $b_i$ 都只会被加到一边（另一边被删了）这样最小化加起来的 $b_i$，最后，b 元组的最大值我们保留下来，不加它一定是最优的策略，也就是围绕它的两边进行删除，手推之后，画出这样的图：
![](https://cdn.luogu.com.cn/upload/image_hosting/4qluksm4.png)
可证明答案最少为 16，贪心成立。解的答案为 a 元组的全部元素之和加上 b 元组的全部元素之和减去 b 元组的最大值
## **ACcode**：
```cpp
#include <bits/stdc++.h> // chuxm CF1794B

#define int long long // 不开longlong见祖宗 

using namespace std;

int n, m, a, b, cnt, ma = INT_MIN;

signed main(){
	cin >> n; // n 组测试数据
	for(int i = 1; i <= n; i++){ 
		cin >> m; // 输入长度 
		for(int j = 1; j <= m; j++){ // a 数组处理 
			cin >> a;
			cnt += a; // 累加 a 的元素之和 
		}
		for(int j = 1; j <= m; j++){ // b 数组处理 
			cin >> b;
			ma = max(ma, b); // 取 b 数组最大值 
			cnt += b; // 累加 b 的元素之和 
		}
		cout << cnt - ma << endl; // 答案处理 （套结论）
		ma = INT_MIN; // 多组数据清空最大值 
	}
	return 0;
}

```

---

## 作者：Ultra_Cyno_0052 (赞：0)

# CF1749B Death's Blessing

题目传送门：[CF1749B Death's Blessing](https://www.luogu.com.cn/problem/CF1749B);

## 分析思路：

$a_i$ 是肯定是要算的，$b_i$ 最优的是从两边取，最终不取最大值最优，简化式子得到：
$$
\sum_{i= 1}^{n}(a_i+b_i)-b_{\max_{i =1}^{n}}
$$

## 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
long long a[MAXN], b[MAXN];
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        long long pos = 1, end = n, ans = 0;
        for (int i = 1; i < n; i++) {
            if (b[pos] < b[end]) ans += a[pos], a[pos + 1] += b[pos], pos ++;
            else ans += a[end], a[end - 1] += b[end], end --;
        }
        ans += a[pos];
        cout << ans << endl;
    }
}
```

---

## 作者：lrmlrm_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1749B)

## 题意

$\quad$ 给出 $n$ 个二元组 $\left\{a_i,b_i \right\}$。

$\quad$ 删除一个其中一个二元组要用 $a_i$ 秒，删除 $a_i$ 会使 $ a_{i-1}$ 和 $ a_{i+1}$ 的值加上 $b_i$，求删除所有值最少要用的时间。

## 分析及思路

$\quad$ 先来看一张图:

![](https://cdn.luogu.com.cn/upload/image_hosting/763mzoqi.png?x-oss-process=image/resize,m_lfit,h_300,w_500)

很明显发现，无论怎么删除，$a_i$都会被删掉，所以最少的时间里面肯定会有 $ \sum\limits_{i=1}^na_i$。

那么 $b_i$ 里面，又会有哪些时间要算进最短总时间中呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/ijyfeui7.png?x-oss-process=image/resize,m_lfit,h_300,w_500)

看起来是 $a_{i-1}+a_i+a_{i+1}+b_i+b_{i+1}$，但这好像并不是最大的。

那么我们换一种方式：

![](https://cdn.luogu.com.cn/upload/image_hosting/magmfzm9.png?x-oss-process=image/resize,m_lfit,h_300,w_500)

很明显，这种情况的和是 $a_{i-1}+a_i+a_{i+1}+b_{i-1}+b_i$。那么现在回归正题，要让时间最小应该怎么加呢？

~~...这很明显吧，讲什么啊~~那很明显，最小和应该就是 $ \sum\limits_{i=1}^na_i+\sum\limits_{i=1}^nb_i-b$ 数组的最大值。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,t,ans,ma;
int main(){
	scanf("%lld",&t);
	while(t--){
		ans=0,ma=-1;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a);
			ans+=a;
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&b);
			ma=max(ma,b),ans+=b;
		}
		printf("%lld\n",ans-ma);
	}
	return 0;
}
```

---

## 作者：Allanljx (赞：0)

## 思路
显然 $a_i$ 是必然要花的时间，因此仅需考虑 $b_i$。

每次删除最左边和最右边的二元组时 $b_i$ 会被累加一次，删除中间的二元组时 $b_i$ 会被累加两次，而最后一次删除时 $b_i$ 会被累加零次。因此每次删除必然删两边的元素，这样能使中间的 $b_i$ 少累加一次。为了使总和最小，最后一次删除一定会删最大的 $b_i$。所以最终的时间就是 $\sum_{i=1}^{n} a_i+\sum_{i=1}^{n} b_i-\max b_i$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m;
int a[200005];
int b[200005];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--)
	{
		int sum=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			sum+=a[i];
		}
		int maxa=0;
		for(int i=1;i<=n;i++)
		{
			cin>>b[i];
			maxa=max(maxa,b[i]);
			sum+=b[i];
		}
		cout<<sum-maxa<<endl;
	}
}
```

---

## 作者：hello_world_djh (赞：0)

更无聊的体验：[CF1749B Death's Blessing 题解](https://www.cnblogs.com/hello-world-djh/p/CF1749B.html)

~~本蒟蒻第一次发CF题解，好兴奋啊~~

题目传送门：[CF1749B Death's Blessing](https://www.luogu.com.cn/problem/CF1749B)

这个题最难处理的明显是 b 数组对邻居的影响，我们可以注意到题目中有这样一句话

> 注意，第 1 个和第 n 个不相邻

这样，我们就可以想出我们的贪心策略之一：从两边选。因为只要不从两边选，他对最终值的影响就会翻倍，从两边选的影响就是一倍。

通过说明和提示我们发现这句话：

> In the first test case, there is only one monster that will be killed in 1010 seconds.

我们就可以想到我们的贪心思路之二：每次选两边的较小者。因为我们可以发现最后一个选的不算影响，所以我们可以贪心的将最大值留到最后去选。

此题的贪心思路是固定的，但却有两种写法。有一种就是第一个写题解的大佬和我的一个同机房大佬的写法一样，我们可以从这个思路得出：最大值没有贡献，其他值一倍贡献，所以就在输入时将 a 和 b 的和统计出来，在减去最大的 b 即可。

还可以像本蒟蒻考场时这样，用双指针模拟贪心思路选数的过程，$O(n)$ 扫一遍，最终复杂度与 $O(n)$ 同阶，但空间复杂度稍差，是 $O(N)$ 的。

废话少说，上代码：
```cpp
#include <bits/stdc++.h>

template <typename T> T read() {
    T x = 0, f = 1; char ch = getchar();
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') f = ~f + 1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
    return x * f;
}

long long a[int(2e5 + 10)], b[int(2e5 + 10)];

int main() {
    int T = read<int>();
    while (T--) {
        int n = read<int>();
        for (int i = 1; i <= n; i++) a[i] = read<int>();
        for (int i = 1; i <= n; i++) b[i] = read<int>();
        int p = 1, q = n; long long ans = 0;
        for (int i = 1; i < n; i++) {
            if (b[p] < b[q]) {
                ans += a[p]; a[p + 1] += b[p]; p++;
            }
            else {
                ans += a[q]; a[q - 1] += b[q]; q--;
            }
        }
        ans += a[p]; printf("%lld\n", ans);
    } return 0;
}
```

完结撒花！！！

---

