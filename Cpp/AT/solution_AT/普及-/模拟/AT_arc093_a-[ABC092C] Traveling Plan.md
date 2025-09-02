# [ABC092C] Traveling Plan

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc092/tasks/arc093_a

$ x $ 軸上に $ N $ 個の観光スポットがあり、$ 1,\ 2,\ ...,\ N $ の番号がついています。 観光スポット $ i $ は座標 $ A_i $ の点にあります。 また、$ x $ 軸上を座標 $ a $ の点から座標 $ b $ の点まで移動するには $ |a\ -\ b| $ 円かかります。

あなたは $ x $ 軸上を旅行する計画を立てました。 計画では、最初に座標 $ 0 $ の点を出発し、$ N $ 個の観光スポットを番号順に訪れ、最後に座標 $ 0 $ の点に戻ってくることになっています。

ところが、旅行の直前に急用が入り、$ N $ 個すべての観光スポットを訪れる時間的余裕がなくなってしまいました。 そこで、ある $ i $ を選び、観光スポット $ i $ を訪れるのを取りやめることにしました。 それ以外の観光スポットは予定通り番号順に訪れます。 また、最初に座標 $ 0 $ の点を出発し、最後に座標 $ 0 $ の点に戻ってくることについても、予定に変更はありません。

$ i\ =\ 1,\ 2,\ ...,\ N $ それぞれについて、観光スポット $ i $ を訪れるのを取りやめたときの、旅行中の移動にかかる金額の総和を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ -5000\ \leq\ A_i\ \leq\ 5000 $ ($ 1\ \leq\ i\ \leq\ N $)
- 入力値はすべて整数である。

### Sample Explanation 1

観光スポット $ 1,\ 2,\ 3 $ はそれぞれ座標 $ 3,\ 5,\ -1 $ の点にあります。 各 $ i $ について、観光スポット $ i $ を訪れるのを取りやめた場合の移動経路および移動にかかる金額は以下のようになります。 - $ i\ =\ 1 $ のとき、移動経路は $ 0\ \rightarrow\ 5\ \rightarrow\ -1\ \rightarrow\ 0 $ となり、移動にかかる金額は $ 5\ +\ 6\ +\ 1\ =\ 12 $ 円となります。 - $ i\ =\ 2 $ のとき、移動経路は $ 0\ \rightarrow\ 3\ \rightarrow\ -1\ \rightarrow\ 0 $ となり、移動にかかる金額は $ 3\ +\ 4\ +\ 1\ =\ 8 $ 円となります。 - $ i\ =\ 3 $ のとき、移動経路は $ 0\ \rightarrow\ 3\ \rightarrow\ 5\ \rightarrow\ 0 $ となり、移動にかかる金額は $ 3\ +\ 2\ +\ 5\ =\ 10 $ 円となります。

## 样例 #1

### 输入

```
3
3 5 -1```

### 输出

```
12
8
10```

## 样例 #2

### 输入

```
5
1 1 1 2 0```

### 输出

```
4
4
4
2
4```

## 样例 #3

### 输入

```
6
-679 -2409 -3258 3095 -3291 -4462```

### 输出

```
21630
21630
19932
8924
21630
19288```

# 题解

## 作者：TsH_GD (赞：3)

### 需会知识点


数轴上表示两点间的距离有公式为 $|A-B|$ 。

**就是两个点在数轴上对应的数的差的绝对值** 。

## 题意:

从 $0$ 出发。

~~需要去 $ N $ 个点（顺序随意）~~ 。

需要去 $ N $ 个点（**必须按顺序**）。

最后再回到 $0$ 。问假设第 $i$ 个点不用走，走过的路程分别是多少 。

## 思路

按顺序走的。

假如第 $i$ 个点不用走。

1. 减去第 $i-1$ 个点到第 $i$ 个点的距离。

2. 减去第 $i$ 个点到第 $i+1$ 个点的距离。

3. 加上第 $i-1$ 个点到第 $i+1$ 个点的距离。

### 注意！：

第 $0$ 个点和第 $n+1$ 个点全都是 $0$ 。

### AC:
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100001],n,ans;
int main(){
  cin>>n;
  for(int i=1;i<=n;++i) cin>>a[i];
  int b=0;
  for(int i=1;i<=n+1;++i) b+=abs(a[i]-a[i-1]);
  for(int i=1;i<=n;++i){
    ans=b-abs(a[i]-a[i-1])-abs(a[i+1]-a[i])+abs(a[i+1]-a[i-1]);
    cout<<ans<<endl;
  }
  cout<<endl;
}	
```

---

## 作者：火车司机 (赞：3)

## 简要分析

题意是从 $0$ 出发**必须按顺序**走完数轴上的 $N$ 个点，最后再回到 $0$。问假设第 $i$ 个点不用走，走过的路程分别是多少

因为是按顺序走的，所以假如第 $i$ 个点不用走，我们只需要减去第 $i-1$ 个点到第 $i$ 个点的距离，以及第 $i$ 个点到第 $i+1$ 个点的距离，最后再加上第 $i-1$ 个点到第 $i+1$ 个点的距离即可

第 $0$ 个点和第 $n+1$ 个点全都是 $0$

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define N 100005
using namespace std;
int n, ans, a[N];
template <typename T>
inline void read(T &x)
{
	register T f = 0, c = getchar();
	for (; c < 48 || 57 < c; c = getchar())
		if (c == '-')
			f = 1;
	for (x = 0; 48 <= c && c <= 57; c = getchar())
		x = (x << 3) + (x << 1) + (c & 15);
	if (f)
		x = ~(--x);
}
template <typename T>
inline void print(T x)
{
	if (x < 0)
		putchar('-'), x = ~(--x);
	if (x > 9)
		print(x / 10);
	putchar(x % 10 | 48);
}
inline int A(int a)
{
	return a > 0 ? a : -a;
}
signed main()
{
	read(n);
	for (ri i = 1; i <= n; ++i)
		read(a[i]), ans += A(a[i - 1] - a[i]);
	ans += A(a[n]);
	for (ri i = 1; i <= n; ++i)
		print(ans - A(a[i - 1] - a[i]) - A(a[i] - a[i + 1]) + A(a[i - 1] - a[i + 1])), puts("");
	return 0;
}
```


---

## 作者：seac_blue (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT3978)

### 题目大意

给定数轴上的 $n$ 个点 $a_{1..n}$，需要从位置 $0$ 开始，**按顺序经过这 $n$ 个点**，最后回到位置 $0$。

给定 $n$ 组询问，第 $i$ 组询问规定不需要经过 $i$ 号点。对于每组询问，求经过的距离最小值。

### 思路

不经过 $i$ 号点，即从 $i-1$ 号点直接前往 $i+1$ 号点。则答案需要减去 $\text{Dist}(a_{i-1},a_{i})$ 和 $\text{Dist}(a_{i},a_{i+1})$，加上 $\text{Dist}(a_{i-1},a_{i+1})$ 即可。此处 $\text{Dist}(x,y)$ 指点 $x,y$ 之间的距离。

容易发现，$\text{Dist}(a_i,a_j)=|a_i-a_j|$。在代码中实现即可，需要预处理不删点时移动的距离。

### 代码

```cpp
typedef long long ll;
ll read(){/* 快读 */}

const ll MAXN = 114514;
ll n,sum;
ll a[MAXN];
ll Abs(ll x){return x>0?x:-x;}

int main(){
	n=read();
	for(ll i=1;i<=n;++i){
		a[i]=read();
		sum+=Abs(a[i]-a[i-1]);
	}
	sum+=Abs(a[n]);
	for(ll i=1;i<=n;++i){
		ll dx1=Abs(a[i-1]-a[i]);
		ll dx2=Abs(a[i+1]-a[i]);
		ll dx3=Abs(a[i+1]-a[i-1]);
		printf("%lld\n",sum-dx1-dx2+dx3);
	}
	return 0;
}
```

---

## 作者：hanzhang666 (赞：0)

# 题目分析
考虑暴力，时间复杂度 $\mathcal{O}(n^2)$，显然会超时。

考虑经过这个点和不经过这个点的所需的路程的关系，可以发现不经第 $i$ 个点的路程等于经过第 $i$ 个点的路程减去第 $i-1$ 个点与第 $i$ 个点的距离减去第 $i$ 个点与第 $i+1$ 个点的距离加上第 $i-1$ 个点与第 $i+1$ 个点的距离。证明如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/37efonxr.png?x-oss-process=image/resize,m_lfit,h_340,w_550)

**~~小~~细节：题目要求从坐标为 $0$ 的位置出发，最终需要回到坐标为 $0$ 的位置，我们可以增加两个点，第 $0$ 个点的坐标为 $0$，第 $n+1$ 个点的坐标为 $0$。**
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int a[100005];
signed main(){
	int n=read();
	int ans=0;
	a[n+1]=0;//第n+1个点的坐标为0 
	for(int z=1;z<=n;z++) a[z]=read();
	for(int z=1;z<=n+1;z++) ans+=abs(a[z]-a[z-1]);//注意有n+2个点 
	for(int z=1;z<=n;z++){
		cout<<ans-abs(a[z]-a[z-1])-abs(a[z+1]-a[z])+abs(a[z-1]-a[z+1])<<endl;
	}
}
```


---

## 作者：wssdl (赞：0)

### 前置芝士

**绝对值** ，平面图中常用的一个用来计算距离的方法，举个例子：

```cpp
abs(a-b);
```

这就表示位置 a 到位置 b 的距离，还不懂的 [戳我](https://baike.baidu.com/item/%E7%BB%9D%E5%AF%B9%E5%80%BC) 。

### 题目思路

知道了绝对值，那这道题就很容易了，大体上可以分为三步。

第一步，求出从第一个点开始，到第二个点的距离，第二个点到第三个点的距离……第 n 个点到第一个的距离，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hgq7ajcn.png)

第二步，累加所有距离，懒得画图了。

第三步，循环除原点外其他所有点，减去这个点与其相邻点之间的距离，加上其两个相邻点之间的距离，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/y40j5it1.png)

红色表示减去的距离，蓝色表示新加的距离。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, sum;              // sum是距离总和
int a[N], s[N], ans[N];  // a表示下标，s表示距离，ans是答案
int main() {
  cin >> n;
  a[1] = 0;                           //第一个点，原点，值为0
  for (int i = 2; i <= n + 1; i++) {  //一共就有n+1个点
    cin >> a[i];
  }
  n++;
  a[n + 1] = 0;  //第n个点到原点的距离
  for (int i = 1; i <= n; i++) {
    s[i] = abs(a[i] - a[i + 1]);  //第一步
    sum += s[i];                  //第二步
  }
  for (int i = 2; i <= n + 1; i++) {  //第三步
    ans[i - 1] = sum - s[i] - s[i - 1] + abs(a[i - 1] - a[i + 1]);
  }
  for (int i = 1; i < n; i++) {  //多加了个原点
    cout << ans[i] << endl;
  }
  return 0;
}
```


~~做岛国的题多输出个换行好习惯。~~

---

## 作者：CmsMartin (赞：0)

## 题意简述

数轴上有 $N$ 个点，一开始在 $0$ 位置上，需要去 $N$ 个点（顺序从 $0$ 号点按顺序走完 $N$ 个点），最后回到 $0$ 位置。

对于 $i=1, 2, \ldots, N$ 分别输出不需要去 i 号点的最小路程。

## 思路

又是一道水题。。。

首先，我们考虑不走 $i$ 原路径会发生什么变化，

显然，会变为 $1 \to 2 \to \cdots \to i-1 \to i + 1 \to i + 2 \to \cdots \to N$

他和原本的路径的区别是：减去了 $i - 1 \to i$ 和 $i \to i + 1$ 的距离，加上了 $i - 1 \to i+1$ 的距离。

知道了这一点，那就很好做了，只需要先算出全部都走的时间，然后如上计算便可得到。

注： $i , j$ 两点的距离为 $|i - j|$ , **小心 $a_n$** 。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define I_Love_lxl_Forever cout

int N , Num[100010];
int Sum_Dist;

int main() {
    ios::sync_with_stdio(false);
    cin >> N;
    for(int i = 1; i <= N; i++) {
        cin >> Num[i];
    }
    for(int i = 1; i <= N + 1; i++) {
        Sum_Dist += abs(Num[i] - Num[i - 1]);
    }
    for(int i = 1; i <= N; i++) {
        cout << Sum_Dist - abs(Num[i] - Num[i - 1]) - abs(Num[i] - Num[i + 1]) + abs(Num[i - 1] -Num[i + 1]) <<endl;
    }
    return 0;
}
```

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT3978)

小学生又双叒叕来写题解啦！

这题的题面有误，讨论区有人提出来了，望管理员修改一下。

我就不发正确的题目描述了，自己去讨论区看看。



------------

不说闲话，我看到题目的第一反应是：直接模拟不就好了！

于是写出了如下代码：


```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define N (int)(1e5 + 5)
using namespace std;
int n, a[N]; 
int dis(int x)  //表示不用去第 x 个点的最短路程。 
{
	int ans = 0, now = 0;  //分别记录答案与当前位置。 
	for (int i = 1; i <= n+1; i++) 
	//看到 i 的范围了吗，由于第 (n+1) 个是零，我们直接遍历到那里，不就相当于回到零号点了吗？ 
	{
		if (i == x) continue;
		ans += (abs(now - a[i]));
		now = a[i];
	}
	return ans;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) printf("%d\n", dis(i));  //勿忘祖传换行。 
	return 0;
}
```


然而第一个点就爆掉了，原因是超时。

超时的原因很简单，就是这份代码的时间复杂度是 $O(n^2)$ 这么大，不爆才怪呢！

因此，我们可以**预处理**。

准确的说，由于每次计算最短路程是相关的，所以思考：能否通过整体的一次计算来得到所有答案呢？

答案是可以的。

首先算出**完整路程**，也就是没有点被省略时的路程。

然后，假设第 $i$ 个点不用去，那么只需在完整路程中减去一些东西就是结果了。

具体看这两张图。

![图一](https://cdn.luogu.com.cn/upload/image_hosting/3gsgpkuq.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如果省略第一个点，就会变成下图。

![图二](https://cdn.luogu.com.cn/upload/image_hosting/id0xsfqy.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

代码也就水到渠成了。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define N (int)(1e5 + 5)
using namespace std;
int n, a[N]; 
int dis()  //表示最短路程。 
{
	int ans = 0, now = 0;  //分别记录答案与当前位置。 
	for (int i = 1; i <= n+1; i++) 
	//看到 i 的范围了吗，由于第 (n+1) 个是零，我们直接遍历到那里，不就相当于回到零号点了吗？ 
	{
		ans += (abs(now - a[i]));
		now = a[i];
	}
	return ans;
}
int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int s = dis();
	for (int i = 1; i <= n; i++) 
	{
		//关于下面重点代码的解析，图内都标好了，对着图模拟即可。 
		int t1 = abs(a[i] - a[i-1]);
		int t2 = abs(a[i] - a[i+1]);
		int t3 = abs(a[i-1] - a[i+1]);
		printf("%d\n", s - t1 - t2 + t3);  //勿忘祖传换行。 
	}
	return 0;
}
```


---

## 作者：tZEROちゃん (赞：0)

根据小学数学，我们知道线段上两点 $A, B$ 之间的距离公式是 $|a - b|$，其中 $a, b$ 分别对应点 $A, B$ 对应的值。

我们用 $dis$ 记录所有相邻两点 $a_i, a_{i-1}$ 之间的距离之和，**注意，不要忘记 $a_n$**。

如果不需要去第 $i$ 个点，那么我们就可以减去从第 $i-1$ 个点走向 $i$ 和从第 $i+1$ 个点走向 $i$ 的距离，但是要加上从第 $i - 1$ 个点走向从第 $i + 1$ 个点的距离，即 

$$ans_i = dis - |a_{i - 1} - a_i| - |a_{i + 1} - a_i| + |a_{i + 1} - a_{i - 1}|$$

不难写出代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[114514];
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  int dis = 0;
  for (int i = 1; i <= n + 1; ++i) {
    dis += abs(a[i] - a[i - 1]);
  }
  for (int i = 1; i <= n; ++i) {
    int ans = dis - abs(a[i] - a[i - 1]) - abs(a[i + 1] - a[i]) + abs(a[i + 1] - a[i - 1]);
    cout << ans << endl;
  }
  cout << endl;
}
```
注：本代码已在 AtCoder 提交并通过，因本人 AtCoder 用户名更改，无法使用洛谷提交，这里直接给出 AtCoder 评测编号 [`#27771164`](https://atcoder.jp/contests/abc092/submissions/27771164)。

---

## 作者：orange166 (赞：0)

## AT3978 【[ARC093A] Traveling Plan】
### 题面：
数轴上有 $n$ 个点，一开始在 $0$ 位置上，需要去 $n$ 个点（顺序 **从 $0$ 至 $n$ ，不随意** ），最后回到 $0$ 位置。

对于 $i = 1 \cdots n$ ，分别输出不需要去 $i$ 号点的最小路程。  
### 思路：
因为访问点的顺序从 $0$ 至 $n$ 是固定的，所以只有一种方案。输入时计算出不去除点的总里程  $tot$ ，然后计算去除每一个点 $a_{i}$ 后的里程，为总里程减去这个点与上一个点的距离和这个点与下一个点的距离的和，加上上一个点与下一个点的距离。 即 
$$ tot - |a_{i}-a_{i-1}| - |a_{i+1}-a_{i}| + |a_{i+1}-a_{i-1}| $$  
  
点相减和单个点的值都有可能为负数。
### 代码：
```cpp
#include<cstdio>
#include<cmath>
int n,a[100100],tot;
int main(){
	scanf("%d",&n);
	for(register int i=1; i<=n; ++i)
		scanf("%d",&a[i]),tot+=abs(a[i]-a[i-1]);
	tot+=abs(a[n]); //最后一个点有可能为负数，求绝对值
	for(register int i=1; i<=n; ++i)
		printf("%d\n",tot-abs(a[i]-a[i-1])-abs(a[i+1]-a[i])+abs(a[i+1]-a[i-1])); //每一项都需要求绝对值
	return 0;
}
```
$12$ 行代码[搞定](https://www.luogu.com.cn/record/45768658)。

---

