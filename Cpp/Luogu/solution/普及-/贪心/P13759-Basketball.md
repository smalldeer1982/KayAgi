# Basketball

## 题目背景

Everyone has its own dream.

## 题目描述

有 $n$ 个人在野球场上打球，第 $i$ 个人战斗力是 $a_i$，你需要将他们分成 $m$ 组，第 $i$ 组有 $\frac{n}{m}$ 人，保证 $\frac{n}{m}$ 为奇数。

定义本组球员的不团结值为 $x_i$，表示本组所有战斗力值的中位数。

请你给出一种分组方案，使 $\sum_{i = 1}^{m} x_i$ 最小。

## 说明/提示

**『本题采用捆绑测试』**

对于 $100\%$ 的数据，$1 \le n \le 10^6$，$1 \le a_i \le 10^9$，满足 $m$ 一定是 $n$ 的因数且 $\frac{n}{m}$ 为奇数。 

| Subtask | 测试点编号 | 特殊限制 | 分值 |
| :-----------: | :----------: | :-----------: | :-----------: |
| $\text{Subtask 1}$ | $1 \sim 2$ | $n \le 10$ | $10$ |
| $\text{Subtask 2}$ | $3 \sim 5$ | 所有 $a_i$ 相等 | $15$ |
| $\text{Subtask 3}$ | $6 \sim 7$ | 对于 $2 \le i \le n$，有 $a_i = a_{i-1} + 1$ | $10$ |
| $\text{Subtask 4}$ | $8 \sim 10$ | $m=1$ | $15$ |
| $\text{Subtask 5}$ | $11 \sim 13$ | $n \le 2000$ | $15$ |
| $\text{Subtask 6}$ | $14 \sim 20$ | 无特殊限制 | $35$ |


## 样例 #1

### 输入

```
9 3
1 2 3 4 5 6 7 8 9```

### 输出

```
12```

# 题解

## 作者：Indestructible (赞：3)

## 题意

把 $n$ 个正整数 $a_1\sim a_n$ 分成 $m$ 组，使得每组中位数之和最小。

## 做法

一组中有 $\dfrac{n}{m}$ 个正整数，其中中位数是按照大小排序的第 $\dfrac{\frac{n}{m}+1}{2}$ 个。

若在 $a$ 中选择一组数使中位数最小，显然至少应选择最小的 $\dfrac{\frac{n}{m}+1}{2}$ 个。

若选择两组，在保持第一组中位数最小的情况下，第二组数的前 $\dfrac{\frac{n}{m}+1}{2}$ 个应该紧跟着第一组数。由于中位数在组内的大小排行不变，可以证明没有比这更优的方案。

若选择更多组，按照刚才的方法选择即可。

最终答案为 $\displaystyle\sum^{m}_{i=1}a_{\frac{\frac{n}{m}+1}{2}i}$。

## 代码实现

```cpp line-numbers
#include <bits/stdc++.h>
#define fr(i, x, y) for (int i = (x); i <= (y); i ++)
#define int long long
using namespace std;

const int N = 1e6 + 12;
int n, m, a[N], ans;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	fr(i, 1, n) cin >> a[i];
	sort(a + 1, a + n + 1);
	fr(i, 1, m) ans += a[i * (n / m + 1) / 2];
	cout << ans;
	return 0;
}
```

---

## 作者：cqfcbb2015 (赞：3)

# 题解：P13759 Basketball

[题目传送门](https://www.luogu.com.cn/problem/P13759)

观察到题目并没有样例解释，并且我们的第六感告诉我们这是一道结论题，于是，我们使用 `dfs` 来解释样例（请读者自行实现 `dfs` 代码）。

最终得到的解释如下：
```text
1 2 7
3 4 8
5 6 9
```

答案为 $2+4+6=12$。

前面说了，这是一道结论题。于是，我们~~手玩数据~~造几个数据，发现：设 $k = \frac{n}{m}$，然后把 $a$ 排序，答案为 $\sum_{i=1}^{m} a_{i \times \frac{k+1}{2}}$。

那么，代码如下：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[1000005],l,ans;
signed main(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a+1,a+n+1);
    int k = n / m;
    l = 0;
    for (int i = 1; i <= m; i++){
        l += (k + 1) / 2;
        ans += a[l];
    }
    cout << ans;
	return 0;
}
```
时间复杂度 $O(n \log n)$，跑得飞快。

---

## 作者：EnochLiu2012 (赞：2)

[传送器~](https://www.luogu.com.cn/problem/P13759)

**算法：贪心**

这道题其实说难不难，如果认真找规律了，基本上都能在 $15$ 分钟内做完，甚至更短。

首先，因为是求最小，所以给它**从小到大**排个序。之后，我们会发现，要让 $\sum_{i=1}^mx_i$（$x$ 表示中位数）最小，通过正确分组后，$\sum_{i=1}^mx_i$ 其实就是 $\sum_{i=1}^ma_{c\times i}$（$c$ 表示第一组中的下标）。

具体过程如下：

当 $n=15$ 时，对于序列 $\{1,3,4,6,5,7,9,12,10,15,20,19,18,17,16\}$ 且 $m=3$，将它排序并分成两组：$\{{\color{RoyalBlue}1,3,4,5,6,7,9,10,12}\},\{{\color{Red}15,16,17,18,19,20}\}$，每次从左边取 $3$ 个（对于每一组，下标要从 $1$ 取到中间），再从右边取 $2$ 个，每组为 $\{1,3,{\color{LimeGreen}4},15,16\},\{5,6,{\color{LimeGreen}7},17,18\},\{9,10,{\color{LimeGreen}12},19,20\}$，发现每一组的中位数是在左边取的最后一个数字，规律就是这么来的。

所以，代码就产生了：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int a[N],n,m,c,ans;
signed main(){
    cin>>n>>m;
    for (int i=1; i<=n; i++){
        cin>>a[i];
    }
    sort (a+1,a+1+n);
    c=n/m/2+1; //第一组中位数的下标
    for (int i=1; i<=m; i++){
        ans+=a[c*i];
    }
    cout<<ans;
    return 0;
}
```
总结：本道题就是这么轻松的搞定啦！但是我们平常做题时一定要**认真仔细**，**动脑思考**，**不要粗心大意**，这样才有效果。

---

## 作者：txy120607 (赞：1)

# 题目翻译
给定 n 个数，要求分成 m 组，每组有 $$\displaystyle\frac{n}{m}$$ 人，保证结果为奇数。需要你让每组的中位数最小并输出它们的和。

# 解题思路
观察样例，发现最优分配是分成 `1 2 9` `3 4 8` `5 6 7`三组。用我们惊人的注意力发现出每组居然是可选的前两个配最后一个。直接秒了，取前$$\displaystyle\frac{n}{m}+ 1$$ 个数和最后 $$\displaystyle\frac{n}{m}$$ 个数。

# 证明

不难看出我们使用了一个贪心，那么必须给出证明。  

首先，反证法：如果不选择前两个，而是选择第二个和第三个，那么中位数就会增大。但是由于把第二个选了，第二组的中位数还是第四个，仅仅把中位数从第二个改成了第三个。

如果选择第三个和第四个，那么调换第一组和第二组的顺序，结果不变。

如果不选择最后的数，那么必须带走小的数字陪葬，但是这会导致某一组可选的最小数字增大，进而导致中位数增大，甚至本不会被取到的大数还会作为中位数，百弊而无一利。

综上，每组应当取前$$\displaystyle\frac{n}{m}+ 1$$ 个数和最后 $$\displaystyle\frac{n}{m}$$ 个数。

# 毒瘤

但是，有个细节，样例在坑你，题目没有说数据已经排好序了。如果不排序你就可以收获打卡题 40 分的好成绩啦。~~毒瘤出题人。~~ 排个序就可以轻松取得剩下的 60 分。

吗？

十年 OI 一场空，不开 long long 见祖宗。

终于，我们战胜了毒瘤出题人，可以 AC 打卡题了。

# AC Code

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define int long long

const int N = 1e6;

int a[N];

signed main() {
    int n, m;
    cin >> n >> m;
    for (int& x : a) cin >> x; //刚学的高级输入方式，快去拿这个东西震惊你的朋友

    sort(a, a + n); //系统库排序，没啥可说的
    int group_size = n / m; // 组的长度
    int ans = 0; // 结果
    int l = 0, r = n - 1; // 未选的开头和结尾
    for (int i = 0; i < m; ++i) {
        l += group_size / 2; // 取到从开头到组的一半的数
        ans += a[l];
        l += 1; // 加一保证可以取到中位数
        r -= group_size / 2; // 末尾大数一起带走
    }
    cout << ans << endl;
    
    return 0;
}
```

但是，一看评测记录，400ms 你在想什么，不怕 TLE 吗？

所以，我又打了一篇最优解。

# 最优解
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace {
    constexpr static int N = 1e6;

    int a[N];

    static char ibuf[(1 << 20) + 1], * iS, * iT;
#if ONLINE_JUDGE
#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
#else
#define gh() getchar()
#endif
    static inline int read()
    {
        char ch = gh();
        int x = 0;
        bool t = 0;
        while (ch < '0' || ch>'9')   t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gh();
        return t ? -x : x;
    }
    static inline void out(long long x)
    {
        if (x < 0)putchar('-'), x = -x;
        if (x < 10)putchar(x + '0');
        else out(x / 10), putchar(x % 10 + '0');
    }
}
signed main() {
    int n, m;
    n = read();
    m = read();
    for(int i = 0; i < n; i++) a[i] = read();

    sort(a, a + n);
    int group_size = n / m;
    long long ans = 0;
    int* pl = a;
    int* pr = a + n - 1;
    for (int i = 0; i < m; ++i) {
        pl += group_size / 2;
        ans += *pl;
        pl += 1;
        pr -= group_size / 2;
    }
    out(ans);

    return 0;
}
```
细节：
- 快读起手。
- 匿名命名空间和静态成员变量以及函数可以有效优化小数据。
- 不要再用`#define int long long`了，`long long`太慢了，小心被卡常。
- 用指针替代数组取址，可以有效节约时间。
- 不要觉得 `sort` 慢，节省编程时间也加快速度，比自己打的基数排序都快。

最优解代码就别复制粘贴了吧……

---

## 作者：篮网总冠军 (赞：1)

官方题解。

很容易得出一个结论，我们可以发现，前面选的中位数大一些并不能使后面选的小一些，因为中位数与比它小的数的大小无关，但和个数有关。

先排序。

令 $k = \frac{n}{m}$。

考虑一个贪心的思路，我们对于每个选中的中位数，只需要选择 $\frac{k-1}{2}$ 个比其小的即可。

所以正解就是在前 $m \times \frac{k+1}{2}$ 个人中，每 $\frac{k+1}{2}$ 个选择其中最大的数加和。

std：


```cpp
#include <bits/stdc++.h>
using namespace std;

int a[5000005];
int main(){
	ios::sync_with_stdio(false); 
	int n,m;
	cin>>n>>m;
	int s=(n/m+1)/2;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	} 
	sort(a+1,a+1+n);
	long long ans=0;
	for(int i=1,j=s;i<=m;i++,j+=s){
		ans+=a[j];
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：CCXjxw (赞：0)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13759)
## 题目分析
希望审核大大给过。

这道题让我们把 $n$ 个数字分成 $m$ 组，使得每一组的中位数之和最小。

题目已经保证了 $\frac{n}{m}$ 为奇数，所以每一组的中位数为最中间的那个数字。下面开始分析这道题。

由于要求的跟中位数有关，所以首先要先**排序**。如果是从小到大的进行分组，那么显然不是最大值，因为越到后面中位数越大，这个时候就可以考虑用小数字带大数字，也就是这一组中前面一半全是小数字，后面一半全是大数字。用符号表示为这一组中有 $\lceil\frac{\frac{n}{m}}{2}\rceil$ 个小数字（因为中位数尽量小），$\lfloor\frac{\frac{n}{m}}{2}\rfloor$ 个大数字。这样每一个中位数的间隔就是  $\lceil\frac{\frac{n}{m}}{2}\rceil$，从第 $\lceil\frac{\frac{n}{m}}{2}\rceil$ 开始计算，总共有 $m$ 个中位数。

思路已经清晰了，只需按照思路写代码即可。（其实代码很短的）

下面是代码。
## 题目[代码](https://www.luogu.com.cn/record/231646370)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0);
#define file(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
int n,m;
int a[1000001];
int ans;
signed main(){
	speed
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=n/m/2+1,k=1;i<=n&&k<=m;i+=n/m/2+1,k++)ans+=a[i];//计算中位数
	cout<<ans;
	return 0;
}
```

---

## 作者：rxr2018360074 (赞：0)

又是美美贪心的一天。

首先，我们先看这题的究极弱化版：如果每一队中的 $x_i$ 都是那一队的最小值，问题是不是就简单了很多。

这种情况下，我们就只需要每次取当前的最小值，然后取一大堆最大值把队伍塞满就行了。

看会这题，是不是一下就豁然开朗了？

中位数，就是排序后排在最中间的那个数，显然，对于一个长度为 $len$ 的序列的中位数来说（$len$ 为奇数），总有 $\lfloor{len\div2}\rfloor$ 个数字比它小，所以我们直接取出当前序列中前 $n\div m$ 个数，然后和之前一样取一堆大数来凑数。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000005];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1); //考虑到题目没有说明是否升序或降序，这里拍一下更保险
	int ji=n/m;
	long long sum=0;
	for(int i=1;i<=m;i++){
		sum+=a[(i-1)*(ji/2+1)+ji/2+1];
        //假如当前是第i组，单组长度为ji，那么前(i-1)组已经占用了(i-1)*(ji/2+1)个数，又因为这一组要
        //取出ji/2+1个最小数（最后一个是这组的中位数），所以中位数的下标是(i-1)*(ji/2+1)+ji/2+1
	}
	cout<<sum;
	return 0;
}
``````

---

## 作者：ICU152_lowa_IS8 (赞：0)

考虑一个显而易见的贪心。

使得所有的中位数尽量小，把当前因为过小无法成为中位数的数扔到队里，再取最小的数作为中位数，再把最大的数往里塞。

正确性十分显然，每一步都不可能有更小的中位数取法。

```
#include<bits/stdc++.h>
using namespace std;
int a[1000005];
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	} 
	sort(a+1,a+n+1);
	int t=0;
	long long ans=0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=(n/m+1)/2;j++){
		 	t++;
		}
		ans+=a[t];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xxxel (赞：0)

每组的人数为 $\frac{n}{m}$，将每个人的战力值从小到大排序后，每组的中位数为 $a _ {\lfloor \frac{n}{2m}\rfloor + 1}$。则在每组的中位数之前还有 $\lfloor \frac{n}{2m} \rfloor$ 个较小数。为了使中位数较小，就要让前 $\lfloor \frac{n}{2m} \rfloor$ 个数尽可能小，同时为了不影响后面的组，中位数后的 $\lfloor \frac{n}{2m} \rfloor$ 个数尽可能大。

例如，对于样例：  
:::align{center}
${\color{blue} 1} \quad {\color{green} 2} \quad {\color{blue} 3} \quad {\color{green} 4} \quad {\color{blue} 5} \quad {\color{green} 6} \quad {\color{red} 7} \quad {\color{red} 8} \quad {\color{red} 9}$  
第一组：$\lbrace {\color{blue} 1} \quad {\color{green} 2} \quad \lparen {\color{red} 9} \rparen \rbrace$   
第二组：$\lbrace {\color{blue} 2} \quad {\color{green} 4} \quad \lparen {\color{red} 8} \rparen \rbrace$   
第三组：$\lbrace {\color{blue} 3} \quad {\color{green} 6} \quad \lparen {\color{red} 7} \rparen \rbrace$   
答案 $\sum_{i = 1}^{m} x_i = a_2 + a_4 +a_6 = \sum_{i=1}^{m} a _ {i \times \lparen {\lfloor \frac{n}{2m}\rfloor + 1} \rparen}$
:::  
所以，这道题的答案为 $\sum_{i=1}^{m} a _ {i \times \lparen {\lfloor \frac{n}{2m}\rfloor + 1} \rparen}$。

要开 long long！

code：

```cpp
for(int i=n/m/2+1;i<=n-n/m/2*m;i+=n/m/2+1)ans+=a[i];
    cout<<ans;
```

---

