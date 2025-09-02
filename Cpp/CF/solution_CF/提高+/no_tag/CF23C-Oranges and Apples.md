# Oranges and Apples

## 题目描述

已知有 $2N-1$ 个箱子，每个箱子里有一些苹果和橘子。你的任务是从中选择 $N$ 个箱子使得这 $N$ 个箱子中的苹果数目不小于所有箱子里苹果总数的一半，这 $N$ 个箱子中的橘子数目也不小于所有箱子里橘子总数的一半。

## 说明/提示

$1 \leq \sum n \leq 10^5$，$0 \leq a_i,o_i \leq 10^9$。

Translated by 稀神探女

Developed by luogu_gza

## 样例 #1

### 输入

```
2
2
10 15
5 7
20 18
1
0 0
```

### 输出

```
YES
1 3
YES
1
```

# 题解

## 作者：Euler_Pursuer (赞：7)

我们可以将苹果数为关键字进行从大到小排序，得到新序列：

$$a_1,a_2,a_3,\cdots,a_{2n-1}$$

### 对于排序后的奇数项之和

显然我们有：

$$a_{2i-1}\geq a_{2i} \;\;(1\leq i< n)$$

再加上一个 $a_{2n-1}$ 得到：

$$\sum_{i\in \text{odd}} a_i > \sum_{i\in \text{even}} a_i \;\;(1\leq i\leq 2n-1)$$

所以：$2\times \text{sum}_{\text{odd}} > \text{sum}_{\text{all alpple}}$

如果排序后奇数项的橘子之和大于等于一半，那么这些箱子对应的原来的编号就是答案。

### 如果偶数项的橘子之和才大于等于一半呢？

我们不难知道：

$$\sum_{i\in \text{even}} a_i \geq \sum_{i\in \text{odd}} a_i \;\;(2\leq i\leq 2n-1)$$

再加上一个 $a_1$ 就有：

$$2a_1+2\sum_{i\in \text{even}} a_i > \text{sum}_{\text{all alpple}}$$

由于偶数项的橘子之和已经大于等于一半了，再加一个肯定更大，而对于苹果我们知道偶数项苹果之和再加上最大的那一箱的苹果也是大于一半的，那么这种情况也一定有答案，输出对应的原来的编号即可。

这里顺带也证明了一定存在解。

### 代码实现：

```cpp

#include <cstdio>
#include <algorithm>

using namespace std;

int N;
struct V
{
    int apple, orange, i;
    bool operator < (V s) const
    {
        return apple > s.apple;
    }
}a[200005];

int main()
{
    int T, tot;
    scanf("%d", &T);
    long long aleven, alodd;
    while(T--)
    {
        scanf("%d", &N);
        aleven = alodd = 0;
        tot = 2 * N - 1;
        for(register int i = 1; i <= tot; i += 1)
            scanf("%d%d", &a[i].apple, &a[i].orange), a[i].i = i;
        sort(a+1, a+tot+1);
        for(register int i = 1; i <= tot; i += 2)
            alodd = alodd + a[i].orange;
        for(register int i = 2; i <= tot; i += 2)
            aleven = aleven + a[i].orange;
        puts("YES");
        if(alodd > aleven)
            for(register int i = 1; i <= tot; i += 2)
                printf("%d ", a[i].i);
        else
        {
            printf("%d", a[1].i);
            for(register int i = 2; i <= tot; i += 2)
                printf(" %d", a[i].i);
        }
        printf("\n");
    }
    return 0;
}

```

---

## 作者：I_am_Accepted (赞：6)

线性复杂度做法。

将序列（不用排序）接成环，枚举环上每个长度为 $n$ 的区间，一定有至少一个合法。

证明：

只需要证明对于一种物品，存在至少 $n$ 个区间使得个数和至少一半，然后鸽笼原理秒了。

对于交恰为一个元素的两个区间，区间和的和 $\ge$ 总元素和，所以两者中至少有一个区间和至少一半。

将 $2n-1$ 个区间按照上述的限制连边，发现是奇环，点覆盖大小至少为 $n$，证毕。

---

## 作者：STUDENT00 (赞：4)

这题可谓是：思绪乱飞，灵光万闪，智攀高峰，方能 AC。

同时纪念一下，排序不能用 $\le or \ge$，否则会惨遭 RE！！！

------------
初看此题，$N$ 与 $2N-1$，使人联想到奇数与偶数，顺着这条思路走下去：我们先将 $Box$ 按 $a$ 从大至小排序。

这时便可巧妙利用 $a_i\ge a_{i+1}$，得 $a_1\ge a_2,a_3\ge a_4,\cdots,a_{2n-3}\ge a_{2n-2}$，同项相加，左式 $+a_{2n-1}$ 得：$\sum\limits_{2\nmid i}a_i\ge \sum\limits_{2\mid i}a_i$，不等式两边均 $+\sum\limits_{2\nmid i}a_i$，得：$2\sum\limits_{2\nmid i}a_i\ge \sum a_i$。

分两种情况讨论：

$1.$ $2\sum\limits_{2\nmid i}o_i\ge \sum o_i$，则 $Box_1,Box_3,Box_5\cdots Box_{2n-1}$ 为一解。

$2.$ $2\sum\limits_{2\nmid i}o_i<\sum o_i$，则 $2\sum\limits_{2\mid i}o_i>\sum o_i$。回头看 $a$，我们仍旧利用 $a_i\ge a_{i+1}$，只是这次为： $a_2\ge a_3,a_4\ge a_5,\cdots,a_{2n-2}\ge a_{2n-1}$，同项相加得：$\sum\limits_{2\mid i}a_i\ge \sum\limits_{2\nmid i}a_i-a_1$，不等式两边均 $+a_1+\sum\limits_{2\mid i}a_i$，得：$a_1+2\sum\limits_{2\mid i}a_i\ge \sum a_i$。又据 $o_1+2\sum\limits_{2\mid i}o_i\ge \sum o_i$，故 $Box_1,Box_2,Box_4\cdots Box_{2n-2}$ 为一解。

综上，对于任意情况，均有解。

可以忽略不计的萌新 Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
int T,n,m;
struct Box{
	int id,apple,orange;
} boxs[N]; 
bool cmp(Box A,Box B){
	return A.apple>B.apple;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		m=(n<<1)-1;
		for(int i=1;i<=m;i++) boxs[i].id=i,scanf("%d%d",&boxs[i].apple,&boxs[i].orange);
		sort(boxs+1,boxs+m+1,cmp);
		ll sum_o=0,odd_o=0;
		for(int i=1;i<=m;i++){
			sum_o+=boxs[i].orange;
			if(i&1) odd_o+=boxs[i].orange;
		}
		puts("YES");
		if((odd_o<<1)>=sum_o){
			for(int i=1;i<=m;i+=2) printf("%d ",boxs[i].id);
		}else{
			printf("%d ",boxs[1].id);
			for(int i=2;i<=m;i+=2) printf("%d ",boxs[i].id);
		}
		putchar(10);
	}
	return 0;
}
```

---

## 作者：灵茶山艾府 (赞：3)

双倍经验：[CF798D](https://www.luogu.com.cn/problem/CF798D)

按照 $a_i$ 从小到大排序。

**结论**：如下两个方案，必定有一个是符合要求的：

- 方案一：选择装有 $a_1,a_3,a_5,\cdots,a_{2n-5},a_{2n-3},a_{2n-1}$ 苹果的 $n$ 个盒子。
- 方案二：选择装有 $a_2,a_4,a_6,\cdots,a_{2n-4},a_{2n-2},a_{2n-1}$ 苹果的 $n$ 个盒子。

**证明**：

对于方案一，除去 $a_1$ 的其余每个数，都大于等于它左边的数，所以这些苹果的个数必然大于等于没有选的苹果个数，也就是说，这些苹果的数量至少是全部苹果的一半。

对于方案二，除去 $a_{2n-1}$ 的其余每个数，都大于等于它左边的数，所以这些苹果的个数必然大于等于没有选的苹果个数，也就是说，这些苹果的数量至少是全部苹果的一半。

所以只需要证明，至少有一种方案中的橘子个数是符合要求的。

设 $s_1 = o_1 + o_3 + o_5 + \cdots + o_{2n-5} + o_{2n-3}$。

设 $s_2 = o_2 + o_4 + o_6 + \cdots + o_{2n-4} + o_{2n-2}$。

那么所有橘子的个数为 $s = s_1 + s_2 + o_{2n-1}$。

对于方案一，我们选的橘子个数为 $s_1 + o_{2n-1}$。

对于方案二，我们选的橘子个数为 $s_2 + o_{2n-1}$。

利用反证法，只要证明如下两个不等式不可能同时成立，就能证明结论。

$$
\begin{aligned}
&s_1 + o_{2n-1} < s/2\\
&s_2 + o_{2n-1} < s/2
\end{aligned}
$$

把这两个不等式相加，得

$$
s_1 + s_2 + 2\cdot o_{2n-1} < s = s_1 + s_2 + o_{2n-1}
$$

化简得

$$
o_{2n-1} < 0
$$

矛盾，所以结论成立。

```go
package main
import("bufio";."fmt";"os";"sort")

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var T, n int
	for Fscan(in, &T); T > 0; T-- {
		Fscan(in, &n)
		m := n*2 - 1
		a := make([]struct{ x, y, i int }, m)
		s := 0
		for i := range a {
			Fscan(in, &a[i].x, &a[i].y)
			s += a[i].y
			a[i].i = i + 1
		}

		sort.Slice(a, func(i, j int) bool { return a[i].x < a[j].x })
		se := 0
		for i := 0; i < m; i += 2 {
			se += a[i].y
		}

		Fprintln(out, "YES")
		if se*2 >= s { // 方案一
			for i := 0; i < m; i += 2 {
				Fprint(out, a[i].i, " ")
			}
			Fprintln(out)
		} else { // 方案二
			for i := 1; i < m; i += 2 {
				Fprint(out, a[i].i, " ")
			}
			Fprintln(out, a[m-1].i)
		}
	}
}
```

时间复杂度：$\mathcal{O}(n\log n)$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)

---

## 作者：ykzzldz (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF23C)

考虑先按照苹果个数从大到小排序，此时，可以看出当取奇数位置的苹果，大小是一定大于一半的。我们可以判断此时奇数位置的橘子数量是否大于一半，如果大于，则直接取，如果小于，那么此时偶数位置上的橘子数量就必定大于一半。那么我们只需要再取第一个，就一定可以满足要求，具体见代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int a,b,id;
}x[210000];
int n,jsq,jjsq,t,m;
bool cmp(node l,node r){
	return l.a>r.a;
}
signed main(){
	cin>>t;
	while(t--){
		jsq=0,jjsq=0;
		cin>>n;
		m=n*2-1;
		for(int i=1;i<=m;i++){
			cin>>x[i].a>>x[i].b;
			jsq+=x[i].b;
			x[i].id=i;
		}
		sort(x+1,x+1+m,cmp);
		for(int i=1;i<=m;i+=2){
			jjsq+=x[i].b;
		}
		cout<<"YES\n";
		if(jjsq*2>=jsq){
			for(int i=1;i<=m;i+=2)cout<<x[i].id<<' ';
		}
		else{
			cout<<x[1].id<<' ';
			for(int i=2;i<=m;i+=2)cout<<x[i].id<<' ';
		}
		cout<<'\n';
	}
    return 0;
}
```

---

## 作者：CheerJustice (赞：2)

### [点我传送](https://www.luogu.com.cn/problem/CF23C)

## solution

本题重点在于对方案的构造。为了方便 ，以下提到的 $ n $ 均为 $ 2n-1 $。

我们设第 $ i $ 个箱子里的苹果数为 $ a_{i} $，把箱子按照 $ a_{i} $ 升序排列。因为 $ n $ 是奇数，我们把最大的 $ a_{1} $ 先拿到一边。如此，对于苹果，我们有两种选的方案：

* 选所有下标为奇数的 $ a_{i} $。
* 选 $ a_{1} $ 与 下标为偶数的 $ a_{i} $。

不难发现，这两种方案均满足苹果大于其总数的一半，所以我们再来考虑无序的橘子。又因为如果方案一的橘子数不满足题意，则方案二必定满足，所以我们只需要比较两种方案哪一种橘子数量多就好了。

可知：本题必有一种符合条件的方案，并且不唯一。~~（想不到吧这题其实有 SPJ）~~

## code

```c++
#include <bits/stdc++.h>
#define ll long long;
using namespace std;
inline int in(){
	char c=getchar();int f=1;int x;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	return x*f;
}
template <typename T>
inline void in(T &x){
	char c=getchar();int f=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-')f=-1,c=getchar();
	for(x=0;c>='0'&&c<='9';c=getchar())
		x=(x<<3)+(x<<1)+(c^48);
	x*=f;
}
const int N=2*1e5+5;
struct Node{
	int app,ora,id;
}a[N];
bool cmp(Node a,Node b){
	return a.app>b.app;
}
int main(){
	for(int t=in();t;t--){
		int n=in()*2-1;ll sum1=0,sum2=0;
		for(int i=1;i<=n;i++)
			in(a[i].app),in(a[i].ora),a[i].id=i;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i+=2) 
			sum1+=1ll*a[i].ora;
		sum2=a[1].ora;
		for(int i=2;i<=n;i+=2) 
			sum2+=1ll*a[i].ora;
		printf("YES\n%d ",a[1].id);
		for(int i=sum1>sum2? 3:2;i<=n;i+=2)
			printf("%d ",a[i].id);
		puts("");
	}
	return 0;
}

```

---

## 作者：Firstly (赞：1)

## **解题思路：**

首先我们看到要求 $2N-1$ 中选择 $N$ 个，且两种水果选择在总量的一半以上，可以猜想在所有情况中，均至少有一组解，不过一个正确的结论是需要严谨的证明的。

我们可以将 $a$ 数组从小到大排序，得到有序数组 $a_1,a_2,\dots ,a_{2N-1}$。因为数组有序，所以很容易知道：
$$a_3\geq a_2,a_5\geq a_4,\dots ,a_{2N-1}\geq a_{2N-2}$$
由此可得：
$$a_1+a_3+a_5+\dots+a_{2N-1}\geq a_2+a_4+a_6+\dots+a_{2N-2}$$
同理可以得到：
$$a_2+a_4+\dots+a_{2N-2}+a_{2N-1}\geq a_1+a_3+\dots+a_{2N-3}$$
如果此时：
$$o_1+o_3+o_5+\dots+o_{2N-1}\geq \frac{1}{2}\sum_{i=1}^{2N-1}o_i$$
那么已经满足要求，即可输出所有奇数位上的元素序号。否则一定可得：
$$o_2+o_4+\dots+o_{2N-2}+o_{2N-1}>\frac{1}{2}\sum_{i=1}^{2N-1}o_i$$
即可输出所有偶数位上的元素和最后一位元素的序号。由此也可以证明本题一定有解。

## **Code：**
```cpp
#include<cstdio>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n;
struct node{
	int id,apple,orange;
	bool operator <(const node &other) const{
		return apple<other.apple;
	}
}a[N];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);puts("YES");int sumor=0;
		for(int i=1;i<2*n;i++){
			scanf("%lld%lld",&a[i].apple,&a[i].orange);
			a[i].id=i;sumor+=a[i].orange;
		}sort(a+1,a+2*n);int ans=0;
		for(int i=1;i<2*n;i+=2)ans+=a[i].orange;
		if(ans>=ceil(1.0*sumor/2)){
			for(int i=1;i<2*n;i+=2)printf("%lld ",a[i].id);
		}else{
			for(int i=2;i<2*n;i+=2)printf("%lld ",a[i].id);
			printf("%lld",a[2*n-1].id);
		}puts("");
	}return 0;
}
```


---

## 作者：FastingRabble (赞：1)

拿到问题,第一反应—— $dp,dfs?$

但是发现数据范围这是不可能对的啊！

然后，开始仔细读题，发现其中的玄妙之处

- 1. 数量 ——保证为奇数。~~（你可能还没思路）~~

- 2. 条件 —— 大于等于总数的一半！

这就很奇怪了！

我们随便选取箱子 , 必定有大于等于一般的部分！

**选取的 $VS$ 未选取的** 这样我们就可以考虑如何构造!

第一步，先以 $apple$ 排序,得到

$$
a_1\ge a_2\ge a_3 \dots \ge a_{2n-1}
$$

这时还有**奇数条件**没用！**我们会发现奇数变成了关键!**

突破口在于为平衡，分成两堆的关系一定是 $n$ 和 $n-1$ 个。

再看 $orange$,也**一定有一部分大于等于总数的一半，另一部分小于等于总数的一半**。

但不管怎么选，两堆箱子数量一定不会相等！而最大的 $a_1$ 就成了关键。

用小学知识手推一下,即可以得出结论—— $a_1$ 在哪堆，苹果数量那堆就多！

即我们可以**暂时**，不考虑 $apple$ 了！

然后问题就简单化了——只考虑**奇数堆和偶数堆**谁 $orange$ 数量多就选那堆！

______________

### 参考代码：
```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(2)
using namespace std;
#define int long long
struct node
{
	int x,y,id;
} a[1000050];
int sumodd;
int sumeven;
int n;
int T;
bool cmp(const node& u,const node& w)
{
	return u.x > w.x;
}

signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&n);
		sumodd=0;
		sumeven=0;
		for(register int i=1; i<=2*n-1; ++i)
		{
			a[i].x=0;
			a[i].y=0;
			a[i].id=0;
			scanf("%lld%lld",&a[i].x,&a[i].y);
			a[i].id=i;
		}
		sort(a+1,a+2*n,cmp);
		for(register int i=1; i<=2*n-1; i+=2)
		{
			sumodd+=a[i].y;
		}
		for(register int i=2; i<=2*n-1; i+=2)
		{
			sumeven+=a[i].y;
		}
		if(sumeven<sumodd)
		{
			puts("YES");
			for(register int i=1; i<=2*n-1; i+=2)
			{
				cout<<a[i].id<<' ';
			}
			cout<<endl;
		}
		else
		{
			puts("YES");
			cout<<a[1].id;
			for(register int i=2; i<=2*n-1; i+=2)
			{
				cout<<' '<<a[i].id;
			}
			cout<<endl;
		}
	}
	return 0;
}
```

**完结散花！**

---

## 作者：lilong (赞：0)

挺神奇的思维题。

首先将所有元素按 $a$ 从大到小排序，考虑**交叉选**，即要么 $a_1,a_3,a_5,\cdots,a_{2n-1}$，要么 $a_1,a_2,a_4,\cdots,a_{2n-2}$。无论选哪种，$a$ **一定满足要求**（前者 $a_1>a_2,a_3>a_4,\cdots,a_{2n-3}>a_{2n-2}$，各式相加即可，后者 $a_2>a_3,a_4>a_5,\cdots,a_{2n-2}>a_{2n-1}$，同理）。那么只需要考察对应 $o$ 的情况，若一组不可以（即不到一半），那么另外一组一定可以（总和一定），所以一定有解，直接排序输出即可。


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define N 200010
#define int long long
using namespace std;
struct P{
    int a,b,id;
}c[N];
int n,s1,s2,s,ans[N];
bool cmp(P x,P y){
    return x.a>y.a;
}
void solve(){
    s=s1=s2=0;
    cin>>n;
    for(int i=1;i<=n*2-1;i++)
        cin>>c[i].a>>c[i].b,s+=c[i].b,c[i].id=i;
    sort(c+1,c+n*2-1+1,cmp);
    for(int i=1;i<=n*2-1;i+=2)
        s1+=c[i].a,s2+=c[i].b;
    cout<<"YES\n";
    if(s2>=s-s2){
        for(int i=1,j=1;i<=n*2-1;i+=2,j++)
            ans[j]=c[i].id;
    }
    else{
        ans[1]=c[1].id;
        for(int i=2,j=2;i<=n*2-1;i+=2,j++)
            ans[j]=c[i].id;
    }
    sort(ans+1,ans+n+1);
    for(int i=1;i<=n;i++)
        cout<<ans[i]<<' ';
    cout<<'\n';
}
signed main(){
    int T;
    cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：ivyjiao (赞：0)

虽然说这题正经贪心能过，但是我并没有看出来，于是，随机化，启动！

**截至发题解时没有相同做法**。

容易证明这题一定有解，这里就不说了。

每次把下标打乱一下，然后 check 这组下标是否合法即可，正确就直接输出，否则重新打乱直到找到合法解。

这题正确率的证明方法同 [P1489 猫狗大战](https://www.luogu.com.cn/problem/P1489)，~~反正正确率很高直观感受一下就行~~，大概就是一种合法的方案两个选中的下标互相交换不会影响方案的合法性，两个未选中的下标互相交换也不会影响方案的合法性，所以正确率很高。

注意开 long long！

双倍经验：[CF23C](https://www.luogu.com.cn/problem/CF23C)，[CF798D](https://www.luogu.com.cn/problem/CF798D)。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200001],b[200001],c[200001];
long long suma,sumb;
inline int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
int main(){
    srand(time(0));
    t=read();
    for(int j=1;j<=t;j++){
        suma=0;
        sumb=0;
        n=read();
        for(int i=1;i<=2*n-1;i++) a[i]=read(),b[i]=read(),c[i]=i;
        for(int i=1;i<=2*n-1;i++) suma+=a[i],sumb+=b[i];
        while(1){
            random_shuffle(c+1,c+2*n);
            long long cnt1=0,cnt2=0;
            for(int i=1;i<=n;i++) cnt1+=a[c[i]],cnt2+=b[c[i]];
            if(cnt1*2>=suma&&cnt2*2>=sumb){
                puts("YES");
                for(int i=1;i<=n;i++) printf("%d ",c[i]);
                puts("");
                break;
            }
        }
    }
}
```

~~另外，注意代码第 $21$ 行 `while(1)` 如果换成 `while((double)clock()<CLOCKS_PER_SEC*1.49/t*j)` 或  `while((double)clock()<CLOCKS_PER_SEC*1.49)` 就过不了，原因未知。~~

update on 2024-5-21：破案了，因为题目中保证了 $\sum N$，所以有可能出现一个数据点耗时很大但是总和一定不会超时，~~还是那句话，直观感受一下就行。~~

补充了一个句号。

---

## 作者：henrytb (赞：0)

将箱子按苹果数从小到大排序。

由于总共 $2N - 1$ 个箱子，我们隔一项取一个（即取第 $1, 3, 5, 7, \ldots$） 个箱子，这样恰好能取出 $N$ 个。

容易发现，这 $N$ 个箱子的苹果数是大于一半的（从后往前两项分为一组即可得知）。

然后进行调整，我们从前往后一次将两项分为一组（和上面那个括号里的分组方式不同），即 $(1, 2), (3, 4), \ldots$ 这些组。原来方案中我们每组取的都是苹果数较少的那个，某组更换了方案不会使苹果数变得不合法；那么假如某一组当前取的箱子橙子数比没取的那个橙子数少，就换成另一个。容易证明这样能使橙子数也变得合法（考虑极端情况即可）。

---

## 作者：Bulyly (赞：0)

### 题外话
整个人被恶心住了，这道题它的样例输出实际上是错误的，就这样我调了半小时，接着因为 int 又是几十分钟，再加上思考了很久 QwQ 。
### 解析
主要是贪心 $+$ 思维

我可以来看一下 给定的框的数量是 $2N-1$ 一定是比 $2N$ 的一半小的。
可以先把关键字苹果排序，分为两堆苹果堆肯定有一堆大于等于一半。接下来考虑选编号为偶数的还是奇数的苹果堆这样我们会发现只要这时编号为 $1$ 的苹果的堆一定是最大的那个堆。所以贪心地看那堆的橘子越多就选哪堆。这样橘子也会大于一半。


AC code:
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define rs register
#define N 201105
#define int long long
using namespace std;
int T,n,sum,sum1;
struct Node
{
	int a,o;
	int id;
	bool operator<(Node P) const
	{
		return a>P.a;
	}
}s[N];
signed main()
{
	scanf("%lld",&T);
	while(T--)
	{
		memset(s,0,sizeof s);
		sum=sum1=0;
		scanf("%lld",&n);
		for(rs int i=1;i<=2*n-1;i++) scanf("%lld%lld",&s[i].a,&s[i].o),s[i].id=i,sum+=s[i].o;
		sort(s+1,s+2*n);
		puts("YES");
		for(rs int i=1;i<=2*n-1;i+=2)  sum1+=s[i].o;
		sum-=sum1;
		if(sum1>sum)
		{
			for(rs int i=1;i<=2*n-1;i+=2)  printf("%lld ",s[i].id);
		}
		else
		{
			printf("%lld",s[1].id);
			for(rs int i=2;i<=2*n-1;i+=2) printf(" %lld",s[i].id);
		}
		puts("");
	}
	
	
	return 0;
} 
```
完结撒花~



---

## 作者：Mortidesperatslav (赞：0)

神仙题。记第 $i$ 个箱子为 $(a_i,b_i)$，有 $a_i$ 个苹果和 $b_i$ 个橘子。

结论：按照 $a_i$ 从大到小排序，判断除 $a_1$ 外奇数位和偶数位上哪个橘子的和多，哪个多就选哪个。

证明：注意到 $a_2 \ge a_3,a_4 \ge a_5$，以此类推。显然偶数位加上 $a_1$ 苹果数大于一半，如果橘子数大于一半肯定满足条件。

然后 $a_1 \ge a_2,a_3 \ge a_4$，以此类推，这说明奇数位加上 $a_{2n-1}$，苹果数一定也大于一半，如果橘子数大于一半肯定满足条件。

这说明一定有解。排序即可。

---

