# [AGC002C] Knot Puzzle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc002/tasks/agc002_c



# 题解

## 作者：foreverlasting (赞：4)

题面：

有$N$条绳子， 编号为$1-N$， 第$i$条的长度是$A_i$。 相邻两条绳子打了结（第$1$条不和最后一条打结）若$i$和$i+1$打了结， 我们认为这个结的编号为$i$。

每次选一段绳子， 如果这段绳子的总长度大于给定的变量$L$，我们可以在这段绳子中选一个解开。问是否有一种方案把所有绳子都解开。

贪心。

如何怎么剪总会有两段相邻的绳子剩下，如果这时可以剪，那么前面任意时刻都可以剪。所以只需找到最长的相邻绳子就好了。

code:
```
//2018.9.22 by ljz
#include<bits/stdc++.h>
using namespace std;
#define res register int
#define LL long long
#define inf 0x3f3f3f3f
#define eps 1e-15
inline int read(){
    res s=0;
    bool w=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=1;ch=getchar();}
    while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
    return w?-s:s;
}
inline void _swap(res &x,res &y){
    x^=y^=x^=y;
}
inline int _abs(const res &x){
    return x>0?x:-x;
}
inline int _max(const res &x,const res &y){
    return x>y?x:y;
}
inline int _min(const res &x,const res &y){
    return x<y?x:y;
}
const int N=1e5+10;
namespace MAIN{
    int n,l;
    int a[N];
    int tot;
    int step[N],stepx;
    inline void MAIN(){
        n=read(),l=read();
        for(res i=1;i<=n;i++)a[i]=read();
        res j=1;
        for(res i=1;i<n;i++)if(a[i]+a[i+1]>a[j]+a[j+1])j=i;
        if(a[j]+a[j+1]<l)puts("Impossible");
        else {
            puts("Possible");
            for(res i=n-1;i>j;i--)printf("%d\n",i);
            for(res i=1;i<=j;i++)printf("%d\n",i);
        }
    }
}
int main(){
    MAIN::MAIN();
    return 0;
}
```

---

## 作者：ImmortalWatcher (赞：3)

一开始最容易想到的就是将两头的长度比较一下，然后尽量使得剩下的绳子长度最大，然后贪心拆绳结。

但是有这样一个反例： $A=\{2,3,1,3\},k=5$。

正确的一种取法应该是从后往前取，但是按照上述方法会输出 $-1$。

考虑观察题目性质。

一个经典的思路，不会构造就考虑如何判定。

根据题目，可知只有最后剩下连续两段绳子，且它们长度之和 $\ge k$ 才会有解，且解非常容易构造。

这时候我们只要找到那两段绳子即可。

时间复杂度 $O(n)$。

```cpp
#include<cstdio>
using namespace std;
int n,L,a[100010];
signed main()
{
	scanf("%d%d",&n,&L);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<n;i++)
		if (a[i]+a[i+1]>=L)
		{
			puts("Possible");
			for (int j=1;j<i;j++)
				printf("%d\n",j);
			for (int j=n;j>=i+2;j--)
				printf("%d\n",j-1);
			printf("%d\n",i);
			return 0;
		}
	puts("Impossible");
	return 0;
}
```


---

## 作者：cff_0102 (赞：2)

首先，找到两段（或一段）连在一起的绳子，它们的长度加起来大于等于 $L$。

![](https://cdn.luogu.com.cn/upload/image_hosting/g1avbx3c.png)

接着选择这一整段绳子，它必然大于 $L$，再分别把第 $1,2,3,9,8,7,6$ 段绳子全部拆掉，就只剩 $4,5$ 这一段绳子了。

因为它的长度大于 $L$，所以也能拆开，这样所有绳子都拆开了。

如果找不到一或两段绳子长度加起来大于等于 $L$，则无解。

题目中没翻译出怎么输出的，实际上题目还要输出怎么拆分的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[114514];
int main(){
	ios::sync_with_stdio(0); 
	int n,l;cin>>n>>l;
	for(int i=1;i<=n;i++)cin>>a[i];
	int x=114514;
	for(int i=1;i<n;i++){
		if(a[i]+a[i+1]>=l){
			x=i;//记录位置 
		}
	}
	if(x==114514)cout<<"Impossible",exit(0);//找不到相邻两条长度加起来大于等于 L 的绳子（一条大于 L 则两条一定也大于 L） 
	cout<<"Possible"<<endl;//有解 
	for(int i=1;i<x;i++)cout<<i<<endl;//不是空格是换行 
	for(int i=n-1;i>x;i--)cout<<i<<endl;
	cout<<x<<endl;//最后拆这两段 
	return 0;
}
```

---

## 作者：Zskioaert1106 (赞：1)

题目传送门：[[AGC002C] Knot Puzzle](https://www.luogu.com.cn/problem/AT_agc002_c)

一道直白明显的思维构造题。其坑点在于随机发言的题目翻译以及没有写 Special Judge 的 
AtCoder。

### 题意简述

有 $N$ 根绳子首尾相接（一个链不是一个环），给你每根绳子的长度，只有长度大于等于 $L$ 的绳子才能解开上面的一个绳结。问能否把绳子全都解开，如果能请输出方案。

输入的第一行为两个整数 $N$ 和 $L$，第二行 $N$ 个整数 $a_1,a_2,\dots,a_N$ 依次表示这 $N$ 根绳子的长度。

如果不能全解开，输出一行 `Impossible`；否则先输出 `Possible`，再输出 $N-1$ 行表示依次解开第几个绳结。

### 做题过程

首先看出如果有两根绑在一起的绳子长度大于或等于 $L$，那么就可以最后解开这俩，即可以全部解开。

循环一遍，记录下有没有绳子满足这个条件以及绳结的编号。

注意 AtCoder 并没写 SPJ，所以你要按以下方法输出：

- 将最后一个满足条件的绳结编号记为 $ans$；

- 先从 $1$ 输出到 $ans-1$；

- 再从 $n$ 降序输出至 $ans+1$；

- 最后输出 $ans$。

此次仅代表我的输出方式，并不确定其它的方法**不能** AC。

### 代码编写

先读入并判断在所有的 $1 \le i < n$ 中有没有 $a_{i}+a_{i+1} \ge L$，如果没有则输出无解并结束。

否则输出有解，然后按顺序输出方案即可。

```cpp
#include<iostream>
using namespace std;
int n,l,a[100005],ans;
bool pd=1;
int main(){
	cin>>n>>l;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<n;i++){
		if(a[i]+a[i+1]>=l){
			pd=0;
			ans=i;
		}
	}
	if(pd){
		cout<<"Impossible\n";
		return 0;
	}
	cout<<"Possible\n";
	for(int i=1;i<ans;i++)cout<<i<<'\n';
	for(int i=n-1;i>=ans;i--)cout<<i<<'\n';
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/189164270)。

---

## 作者：cjZYZtcl (赞：1)

## AT1997 [AGC002C] Knot Puzzle 题解
这一题，一眼看过去，肯定是贪心。

每一次都把当前拥有 $x$ 根绳子的长绳子分成一根短绳子和一根拥有 $x-1$ 根绳子的长绳子，且使拥有 $x-1$ 根绳子的长绳子最长。

很明显，这样会使剩下能分的长度最长，如果遇到一次分不了，那么就输出 `Impossible` 并退出程序，否则输出 `Possible`，然后输出贪心过程。

然而WA了。

一看题目，发现没开 Special Judge。。。。。

好吧，看来得用别的方法。

### 正解
我们可以证明，不管怎么分，最后一步总是还剩两段绳子连在一起的情况，那么，如果连在一起的两段绳子的最长长度也不够，那么就肯定无解了，就输出 `Impossible` 并退出程序。

而如果连在一起的两段绳子的最长长度够，我们就可以找出连在一起的最长两段绳子，然后把这一段留到最后，其他段只要和这一段连在一起，就一定可以分，所以按顺序输出即可。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int a[100005];
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int n = read(), m = read(), k = 0, x;
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i < n; i++){
		if(a[i] + a[i + 1] > k){
			k = a[i] + a[i + 1];
			x = i;
		}
	}
	if(k < m) puts("Impossible");
	else{
		puts("Possible");
		for(int i = 1; i < x; i++){
			write(i);
			putchar('\n');
		}
		for(int i = n - 1; i >= x; i--){
			write(i);
			putchar('\n');
		}
	}
}
```


---

## 作者：Katz (赞：0)

首先考虑无解情况。即无法拆开所有绳结的情况。当无论怎么拆时，剩下的绳子长度小于 $L$，则无解。因为拆到最后一步只剩下两条绳子，所以我们只需要检查一遍是否所有相邻的两条绳子长度之和都是小于 $L$。

如果找出了大于 $L$ 的，即为有解。又因为找到的这两条绳子长度之和已经大于 $L$ 了，所以我们只需从小到大依次拆开这两条绳子左侧的绳结，再从大到小依次拆开这两条绳子右侧的绳结，最后再拆开链接这两条绳子的绳结。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,a[100010],pos=-1;
int main()
{
	cin>>n>>l;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<n;i++) if(a[i]+a[i+1]>=l) pos=i;
	if(pos==-1) return cout<<"Impossible"<<endl,0;//找不到相邻两条符合题意的绳子
	cout<<"Possible"<<endl;
	for(int i=1;i<pos;i++) cout<<i<<endl;//从左到右拆
	for(int i=n-1;i>pos;i--) cout<<i<<endl;//从右到左拆
	cout<<pos<<endl;
	return 0;
}
```

---

## 作者：Lyccrius (赞：0)

把一根绳子拆成两段肯定不如拆掉一根绳子的一边优。

容易发现绳子的长度是随着时间单调递减的。

我们考虑这个过程，可以一直持续到拆完所有绳结，或者长度不足。

要让所有绳结都能被拆，肯定要把最可能留到最后的留到最后。

最可能留到最后的就是使得 $a_i + a_{i + 1}$ 最大的 $i$。

模拟这个过程，从两边往中间输出即可。

```cpp
#include <iostream>

const int maxN = 1e5;

int N, L;
int a[maxN + 10];
int cur;

int main() {
    std::cin >> N >> L;
    for (int i = 1; i <= N; i++) std::cin >> a[i];
    for (int i = 1; i <= N; i++) if (a[i] + a[i + 1] > a[cur] + a[cur + 1]) cur = i;
    if (a[cur] + a[cur + 1] >= L) {
        std::cout << "Possible" << '\n';
        for (int i = 1; i < cur; i++) std::cout << i << '\n';
        for (int i = N - 1; i > cur; i--) std::cout << i << '\n';
        std::cout << cur << '\n';
    } else {
        std::cout << "Impossible" << '\n';
    }
    return 0;
}
```

---

## 作者：wheneveright (赞：0)

[link](https://www.luogu.com.cn/problem/AT1997)

## 解析

考虑最后只剩下一个绳结的时候怎么样才能算是能拆掉的。

当然是这段绳子长度大于等于 $L$。

所以就找出任意一对相邻的绳子长度和大于等于 $L$， 绳结编号记为 $p$。

然后当然就是把 $1, 2, \cdots, p - 1, n - 1, n - 2, \cdots, p + 1, p$ 按顺序输出就行了。

如果找不到当然输出 $p$。

## 代码

```cpp
# include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;

int n, k, p;
int a[maxn];

int main () {
	cin >> n >> k; p = -1;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i < n; i++) if (a[i] + a[i + 1] >= k) p = i;
	if (p == -1) { puts ("Impossible"); return 0; }
	puts ("Possible");
	for (int i = 1; i < p; i++) cout << i << endl;
	for (int i = n - 1; i > p; i--) cout << i << endl;
	cout << p << endl;
	return 0;
}
```

题外话，这个代码没写 `Possible` 交到 `AGC002B` 上过了两个点。

---

## 作者：Miracle_ZX (赞：0)

### Part 0

在 CSP-J/S2 之前写写题解，保持保持状态，希望能够过审~

### Part 1

本题，我们秉着大事化小的原则，首先研究什么时候会出现 ```Impossible```。

其实，我们很容易可以知道，如果想把每一小段全部分离，最终一定会有两小段是最后分离的，倘若是最长的两小段绳结的结合体都满足不了题目中的要求，就直接输出 ```Impossible```。

那什么顺序才可以解开所有的绳结呢？

由于我们已经提前判断是否有解，说明最后一定有两段小绳是符合要求的，于是我们将这个整体看成一部分，每次分割时都要带上这两个整体，按顺序输出拆结。最终，再处理这个整体即可。

有点懵，是吗？不急，看看代码。

### Part 2

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, l, res = 0, maxn, a[10000010];
int main()
{
	cin >> n >> l; //分别代表小绳的数量和允许分拆的最短长度
	for(int i = 1; i < n; i++) cin >> a[i];
	for(int i = 1; i < n; i++)
	{
		if(a[i] + a[i + 1] > res)
		{
			res = a[i] + a[i + 1];//res 记录最长的两端绳结的结合体长度
			maxn = i;//记录这个时候的下标
		}
	}
	if(res < l) cout << "Impossible" << endl;//不能满足
	else
	{
		cout << "Possible" << endl;;
		for(int i = 1; i < maxn; i++) cout << i << endl;
		//从前往后慢慢解开
		for(int i = maxn; i <= n - 1; i++) cout << i << endl;
		//从后往前解开
		/*
			上述两种都是解开 maxn 左右的绳结，
			肯定有一段是 >= res 的，故一定符合，
			只需要将左右的绳结号输出，即可。
		*/
	}
	return 0;
}

```

### Part 3
[3.25s，O2，3.89MB](https://www.luogu.com.cn/record/58294368)

---

