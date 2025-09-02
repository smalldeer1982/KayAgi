# Psychos in a Line

## 题目描述

There are $ n $ psychos standing in a line. Each psycho is assigned a unique integer from $ 1 $ to $ n $ . At each step every psycho who has an id greater than the psycho to his right (if exists) kills his right neighbor in the line. Note that a psycho might kill and get killed at the same step.

You're given the initial arrangement of the psychos in the line. Calculate how many steps are needed to the moment of time such, that nobody kills his neighbor after that moment. Look notes to understand the statement more precise.

## 说明/提示

In the first sample line of the psychos transforms as follows: \[10 9 7 8 6 5 3 4 2 1\] $ → $ \[10 8 4\] $ → $ \[10\]. So, there are two steps.

## 样例 #1

### 输入

```
10
10 9 7 8 6 5 3 4 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
1 2 3 4 5 6
```

### 输出

```
0
```

# 题解

## 作者：xxbzzyw (赞：5)

## Solution

虽然这题被某位机房神仙丢到了单调队列的题单里，但是我是用单调栈做的（（（

最开始的想法是因为杀到最后序列是恒定的，那么能不能考虑说将局部的量通过表达式转移至整体（dp）。


首先如果某个人要一直杀人，那么显然在他右边的所有人的值就都应该比他小，于是就可以把给定的数列切成一个个单调递减的区间。

考虑如下图的情况，假设$x$段中的所有数均小于2，$y$段中的所有数均小于1。（且段内所有数均单调递增，即不会存在段内的数"内部残杀"的情况）

若$x>y$，那么显然杀$2$的会是$3$,这时一共经历了$x$轮

若$x<y$，那么当$2$被$3$杀时$2$显然还没有杀$1$，这时$3$已经杀了$y$轮，2在被杀前也杀了$y$轮，则$3$还要杀$y-x$轮才可以杀$1$。此时$3$杀了$x+(y-x)=y$轮。

![](https://cdn.luogu.com.cn/upload/image_hosting/6fesh487.png)



发现了一定的共性，令$f[i]$表示$i$杀人的轮数，那么$i$显然可以由$i$杀到第一个$j$使得满足如上性质。

于是考虑建一个单调递减栈倒着跑，每次按单调栈的方法弹栈，每次弹出就取杀的那个人杀人的人数加一（自己还要杀他）。

That's it.

上代码
```cpp
#include <iostream>
#include <cmath>
#define maxn 100005
using namespace std;
int a[maxn],s[maxn];
inline int read(){
    int x=0,flag=1; char c=getchar();
    while(c<'0'||c>'9'){if(c=='-') flag=0;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return flag? x:-x;
}
int f[maxn];
int main(void){
	int n=read();
	int l=0; 
	int ans=0;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n;i;i--){
		int t=0;
		while(l&&a[s[l]]<a[i]){
			t++;
			f[i]=t=max(t,f[s[l]]);
			l--;
		}
		s[++l]=i;
		ans=max(ans,t);
	}
	cout<<ans;
	return 0;
}
```
upd：据某位神所言，t其实是多余的

---

## 作者：无咕_ (赞：2)

## 题解索引
1. **题目大意**
2. **Solution**
3. **AC code**
4. **类似题型**

代码类型： C++（cpp）

是否吸氧：否

不压行代码长度：20

------------

## 题目大意
题面：[<传送门>](https://www.luogu.com.cn/problem/CF319B)

题意：有 $n$ 个点，每个回合里，当 $a_i>a_{i+1}$ ，则 $a_{i+1}$ 被视为死亡。同一个回合内，某个点可能即被其他点杀死，也杀死其他点。


~~术语理解：单调栈。~~

## Solution
 
### 基础做法：单调栈

之前用过滚动数组、找单调上升子序列、模拟等等方法，发现都有很多漏洞（可能我太弱写错了）。

不过，值得注意的是，与其他题解不同，这里是 **正向存储** 。

因为是单调栈，所以前面的数全是单调的，即当新元素比栈顶大时，因前面已经是最简的了，所以表示前面已经杀完了，所以此次直接继承之前最高一次杀的结果。

最后看看是不是到自己这里又单调上升了，如果是就证明前面杀完了。

## AC code

```cpp
#include<iostream>
#include<cstdio>
#include<stack>
using namespace std;
int f[100005],ans=0,n,maxn=0,x;//分别是：杀人次数最高，答案，n，单次循环中的杀人次数最高，以及一个替死鬼（读入）
stack<int>s;//系统栈真好用
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>x;
        maxn=0;//初始化0
        while(!s.empty()&&s.top()<x){//栈非空，并且栈顶比新元素小时
            maxn=max(maxn,f[s.top()]);//首先判断这个栈顶的杀人次数（这个人杀人的次数）
            s.pop();//然后出栈
        }if(!s.empty())f[x]=maxn+1;//判空，空栈才能+1（证明前面的都杀完了，自己又开始单调上升）
        s.push(x);//入栈
        ans=max(ans,f[x]);//更新结果
    }cout<<ans<<endl;
    return 0;
}
```
AC记录[<传送门>](https://www.luogu.com.cn/record/51883349)

## 类似题型

[P5788 【模板】单调栈](https://www.luogu.com.cn/problem/P5788)



---

## 作者：ZHR100102 (赞：1)

单调栈优化 dp 好题。


# 观察

我们先观察，一个精神病人会一直杀到什么时候。显然，会杀到右边第一个比他大的精神病人那里，然后他就杀不动了。

因此我们可以从右往左考虑，算出左边的精神病人杀掉这个精神病人后左边的人的答案是什么。假设左边的人**目前已经**刀了 $x$ 个人，被杀的人**目前会**刀 $y$ 个人。如果左边杀这个人的时候这个人该杀的还没杀完，那么左边人就要接着这个人继续把该杀的杀掉，又因为它们刀人是同步进行的，所以此时左边的人目前刀掉的人数取 $\max(y,x+1)$。

于是，我们定义 $dp_i$ 表示第 $i$ 个人目前会刀几个人，然后 $O(n^2)$ 转移即可。

# 优化

但是这样显然无法通过，考虑如何优化。

因为一个人会被他左边第一个比他大的人**先**杀掉（不一定最后真的是被他杀的，如果他杀这个人之前就被杀了，那么情况还是等价的，不影响计算），所以我们从右到左维护一个单调栈，维护右边的最大值。在一个元素入栈的时候，只取弹出的元素转移即可。

时间复杂度 $O(n)$，主要还是理解**一个人先钦定被左边第一个比他大的人杀，之后再动态调整，不影响最终答案的类似反悔贪心的思想**。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[100005],dp[100005],tp=0,s[100005],ans;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=n;i>=1;i--)
    {
        int res=0;
        while(tp&&a[s[tp]]<a[i])res=max(res+1,dp[s[tp--]]);
        s[++tp]=i;
        dp[i]=res;
        ans=max(dp[i],ans);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：xing_yue (赞：1)

# Psychos in a Line题解
[题目传送门](https://www.luogu.com.cn/problem/CF319B)
## 大致题意
给定一个 $n$ 和一个长度为 $n$ 的序列 $a$。每个回合中，当
$a_i > a_{i+1}$，则 $a_{i+1}$ 被视为死亡。同一个回合内，某个点可能即被其他点杀死，也杀死其他点。求多少回合后才会没有人死亡。其中  $1 \le n \le 10^5$。

## 解题思路
**算法**：单调栈

**做法**：

首我们设立一个单调栈 $st$，其中存储没死亡的 $a$ 的值。当新元素比栈顶大时，因为前面已经最简了，即前面已经“死”完了，所以直接继承之前最高一次杀的结果。

设立一个 $f$ 存储答案，表示到 $f_{a_i}$ “死完”要多少步。每枚举出一个答案，就在前面最小的基础上 $+1$ 即可。

最终答案取 $f$ 中的 $max$ 即可。

## 代码实现
```cpp
/*CN*/
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
int n, a[N], f[N], ans;
stack<int> st;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		int maxn = 0; //勿忘初始化
		while (!st.empty() && st.top() < a[i]) { //新元素比栈顶大
			maxn = max(maxn, f[st.top()]); //求最大
			st.pop();
		}
		if (!st.empty()) { //注意判空，代表前面都“死”完了
			f[a[i]] = maxn + 1; //+1
		}
		st.push(a[i]); //为下一次操作铺垫
		ans = max(ans, f[a[i]]); // 算答案
	}
	cout << ans;
	return	 0;
}


```

---

## 作者：lyt_awa (赞：0)

## 题意
### [传送门](https://www.luogu.com.cn/problem/CF319B)
## 思路
从后往前遍历，用一个单调栈来维护一个单调递减的序列（也就是在 $i$ 之前的杀剩下来的人）。对于新的人 $a_{i}$ 在他杀掉栈顶的人时，他的回合数杀到 $sk_{top}$ 时的回合数就是目前统计的回合数 $cnt$ 与栈顶的人的回合数 $f_{sk_{top}}$ 中的较大值（说明如下）。

![](https://cdn.luogu.com.cn/upload/image_hosting/wd83qny3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

如图，若 $f_{sk_{top}}\le cnt$ 那么在 $i$ 杀到 $sk_{top}$ 前，$sk_{top}$ 已经将他前面的所有人（他能杀的）杀完了所以此时的回合数就是 $cnt$。若 $f_{sk_{top}}>cnt$ 则 $i$ 会先在 $cnt$ 回合后将 $sk_{top}$ 杀掉， 此时 $sk_{top}$ 要杀掉的人还剩下 $f_{sk_{top}}-cnt$ 个人，于是剩下的人就将被 $i$ 杀掉（因为 $a_{i} > a_{sk_{top}}$，所以 $sk_{top}$ 能杀掉的，$i$ 也能杀掉），回合数变为 $cnt+f_{sk_{top}}-cnt=f_{sk_{top}}$ 就是 $cnt$ 与 $f_{sk_{top}}$ 中的较大值。

最后 $f_{i}$ 就是最终的 $cnt$ 值。

答案就是 $ans=\max_{i\in \left [ 1,n \right ] } f_{i}$

------------
ac 代码奉上(思路看不懂的看看代码说不定就懂了)。
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <stack>
using namespace std;
const int N = 1e5 + 5;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x * f;
}

int n, a[N], f[N], ans;
int sk[N], top;

int main() {
	n = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = n; i; --i) {
		int cnt = 0;
		while (top && a[sk[top]] < a[i]) {
			++cnt;
			f[i] = cnt = max(cnt, f[sk[top]]);
			--top;
		}
		sk[++top] = i;
		ans = max(ans, cnt);
	}
	printf("%d\n", ans);
	return 0;
}
```
时间复杂度 $O(n)$。

---

