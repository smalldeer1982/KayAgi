# [COCI 2022/2023 #3] Estimathon

## 题目背景

Paula 和 Domagoj 正要组织一场激动人心的名为 Estimathon 的团队比赛。他们已经准备好了问题，现在为此布置房间。

## 题目描述

眨眼间，Domagoj 已经在屋里放置了 $n$ 张桌子。现在他们需要增置椅子。他们有五颜六色的椅子。一共有 $m$ 种颜色并且第 $i$ 种颜色的椅子有 $a_i$ 把。参赛每队由**四**人组成。因此对于每张桌子来说，Paula 和 Domagoj 需要增置 $4$ 把椅子。他们想把房间布置地尽可能好。为此，他们约定以下条件：
- 每张桌子的椅子颜色需要相同
- 每种颜色的椅子至少有一张桌子用到了

由于过分关心房间的完美程度，他们突然发现考核其实已然开始了。请你帮他们寻找是否有一种可能的安排方式。

## 说明/提示

**【样例解释 #2】**

我们可以有 $5$ 张分别拥有相同颜色椅子的桌子，但是我们没法使得一张桌子有第四种颜色，所以第二个条件没法满足。

**【数据范围】**

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$11$|$a_1=... =a_m=4$
|$2$|$39$|无特殊限制|

对于 $100\%$ 的数据，满足 $1\leq n,m \leq 100,1\le a_i\le 100$。

**本题满分 $50$ 分。**

## 样例 #1

### 输入

```
7 3
5 21 9```

### 输出

```
DA```

## 样例 #2

### 输入

```
5 4
8 5 10 3```

### 输出

```
NE```

## 样例 #3

### 输入

```
6 5
5 5 5 5 5```

### 输出

```
NE```

# 题解

## 作者：tangqianlang (赞：3)

题意：有 $n$ 张桌子， $m$ 种椅子，第 $i$ 种椅子有 $a_i$ 把。问有没有一种方案能满足每张桌子放 4 把相同颜色的椅子，并且每种椅子都被用过。

通过题目可以得出以下三个结论：

1. 当 $m>n$ 时，不能满足。因为每张桌子只能放一种椅子，当椅子种类比桌子多时，至少有 $m-n$ 种椅子不会被用到。

2. 当 $a_i<4$ 时，不能满足。因为第 $i$ 种椅子放不满一张桌子，所以用过每种椅子。

3. 当能摆满的桌数比 $n$ 小时，不能满足。第 $i$ 种椅子能摆满的桌数为 $\lfloor\frac{a_i}{4}\rfloor$ 。

通过以上结论可以得到代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m;
	cin>>n>>m;
	int a[m];
	for(int i=0;i<m;i++){
		cin>>a[i];
	}
	if(m>n){
		cout<<"NE";
		return 0;
	}
	int cnt=0;
	for(int i=0;i<m;i++){
		cnt+=a[i]/m;
		if(a[i]/m==0){
			cout<<"NE";
			return 0;
		}
	}
	if(cnt<n){
		cout<<"NE";
		return 0;
	}
	cout<<"DA";
	return 0;
} 
```


---

## 作者：SunSkydp (赞：3)

因为每个桌子配备的 $4$ 张椅子均为相同颜色，所以我们只要对于每一个 $a_i$ ，计数 $\lfloor\frac{a_i}{4}\rfloor$ 即可。

注意两个点：

- 当 $n < m$ 时，答案一定为 `NE`，因为 $n$ 张桌子只能用掉 $n$ 种颜色，余下 $m-n$ 种颜色，不符合题意，没判此点得分为 $39$ pts。

- 当任意 $1 \leq i \leq m$ 满足 $a_i < 4$ 时，答案一定为 `Ne`，因为这种颜色的椅子不能满足任何桌子，没判此点得分为 $11$ pts。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, x, ans, flag = true;
int main() {
	scanf("%d %d", &n, &m); 
	if(n < m) return puts("NE"), 0;
	while(m--) { 
		int x; cin >> x; 
		ans += x / 4;
		if(flag) flag = (x > 3); 
	}
	puts(ans >= n && flag ? "DA" : "NE");
	return 0;
}
```

---

## 作者：BugGod (赞：3)

题目中给出了两个要求，我们联系起来判断即可。

首先来看第一个。这要求每一种颜色都要放满一桌，即 4 个。

再看第二个，这要求每种颜色都要放，联系第一个要求，易知一种颜色至少要有 4 把椅子，否则无法放。

并且，我们要放满 $n$ 张桌子，根据我们上面的结论，显然的，第 $i$ 种颜色可以放最多 $\lfloor \frac{a_i}{4}\rfloor$ 张桌子，那么，我们就可以统计出最多能摆出几张桌子。

这样，我们就可以分别判断。如果有颜色不足 4 把，则为 `NE`；如果放不满 $n$ 张桌子，依然是 `NE`，其余情况为 `DA`。

警钟敲烂：如果 $n<m$，显然不能做到每一种颜色都放，所以要特判！！！

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[110],cnt;
int main()
{
    cin>>n>>m;
    if(n<m){cout<<"NE";return 0;}//特判！！！
    for(int i=1;i<=m;i++)cin>>a[i];
    for(int i=1;i<=m;i++)
    {
        if(a[i]<4)//每种都要放
        {
            cout<<"NE";
            return 0;
        }
    }
    for(int i=1;i<=m;i++)cnt+=a[i]/4;//最多放几张
    if(cnt<n)cout<<"NE";
    else cout<<"DA";
    return 0;
}
```

---

## 作者：szhqwq (赞：2)

## $\tt{Solution}$

考虑进行**分类讨论**。

1. 当 $n < m$，即为桌子的数量小于椅子颜色种类数，则不能满足题目每种颜色的椅子至少都有一张桌子用到了的条件，故输出 `NE`；

2. 当 $\sum\limits_{i=1}^{n}\lfloor\frac{a_i}{4}\rfloor < n$ 时，即为对于每种椅子，能够配出 $4$ 个椅子为一组的组数之和小于桌子的数量，相当于这些椅子**放不满** $n$ 张桌子，输出 `NE`；

3. 其余情况则为满足题目条件的情况，输出 `DA`。

```cpp
#include <bits/stdc++.h>

#define re register
#define il inline

using namespace std;
const int N = 110;
int n,m;
int a[N];

il void solve() {
	scanf("%d%d",&n,&m);
	for (re int i = 1; i <= m; ++ i ) scanf("%d",&a[i]);
	int sum = 0;
	for (re int i = 1; i <= m; ++ i ) {
		if (a[i] < 4) return puts("NE"),void();
		sum += a[i] / 4;
	}
	if (n < m || n > sum) puts("NE");
	else puts("DA");
}

int main() {
	solve();
	return 0;
}
```

---

## 作者：Tjaweiof (赞：1)

# [COCI2022-2023#3] Estimathon 题解
[题目传送门](https://www.luogu.com.cn/problem/P9756)

因数据范围较小，考虑模拟。暴力枚举每一种颜色的椅子，将 $n$ 减去 $a_i\div4$。最后如果 $n\le0$ 说明能摆出 $n$ 以上数量的桌子，输出 `DA`，否则输出 `NE`。只需要加上特判即可：

+ 当任何一种颜色的椅子的数量 $\lt4$ 时，输出 `NE`；

+ 当 $n\lt m$ 时，输出 `NE`。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    if (n < m){
        cout << "NE";
        return 0;
    }
    for (int i = 1; i <= m; i++){
        cin >> a;
        if (a < 4){
            cout << "NE";
            return 0;
        }
        n -= a >> 2;
    }
    if (n <= 0){
        cout << "DA";
    } else {
        cout << "NE";
    }
    return 0;
}
```
**此代码时间复杂度 $O(m)$，空间复杂度 $O(1)$，完美过关！**

---

## 作者：2021zjhs005 (赞：1)

这道题目就是**纯熟的循环结构和分支结构**题目，只要**弄清楚题意**就能做。


题目分析
------------
题目中有两个条件，其中第二个条件明确说明了**每一种颜色的椅子都要用上！**

所以说，当 $a_i < 4$ 时，说明这种每种颜色的椅子**不可能用到，**输出 $\texttt{NE}$。

接着，我们看到条件 $1$，它说**每一张桌子的椅子颜色必须相同**，所以我们不能三把黄色，一把红色（举个例子）。

也就是说，如果每一次读入一个数 $x$，并用变量 $ans$ 来统计**可以凑成桌子的数量**，那么每次 $ans$ 累加的就是 $\lfloor \frac{x}{4}\rfloor$。

如果分析到这里，那恭喜你：拿了 $39$ 分，因为你还有一点没有想到：

我们重新看条件二，**每一种椅子的颜色都要用到**（重点），那么如果**椅子颜色种类数量多余桌子数量**，那么**每一种颜色的椅子是不可能摆放完的**。

如：$6$ 把椅子，$5$ 张桌子，摆放 $5$ 组就能让桌子符合要求。即使每一种椅子的颜色数量大于等于 $4$，那多出来的一组是不是多余了呢？

AC 代码
------------
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,i,x,ans;
int main(){
    cin>>n>>m;//分别表示桌子数量和椅子颜色种类数量，不要搞混。
    for(i=1;i<=m;i++){
        cin>>x;
        if(x<4){
            cout<<"NE";return 0;
        }
        ans+=x/4;
    }
    if(ans>=n&&n>=m) cout<<"DA";
//能摆放这么多桌子，并且比椅子颜色种类数量多。
    else cout<<"NE";
    return 0;
}
```

---

## 作者：WsW_ (赞：1)

难度约为红到橙。

---
### 思路
首先梳理要求
* 每种颜色的椅子都必须被使用。
* 每张桌子 $4$ 把椅子。
* 每张桌子上的椅子颜色必须相同。

根据要求判断即可。

如果 $n<m$，那么肯定有某种颜色的椅子用不到，不存在满足条件的方案。  

对于每种颜色的椅子：  
* 如果 $a_i<4$，则这种颜色的椅子一定用不了，不存在满足条件的方案。
* 如果 $a_i\ge4$，则这种颜色的椅子最多可以配给 $\left\lfloor\dfrac{a_i}{4}\right\rfloor$ 张桌子。

如果 $ \sum\limits_{i=1}^m \left\lfloor\frac{a_i}{4}\right\rfloor< n$，则不存在满足条件的方案；否则存在满足条件的方案。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m;
int cnt;
int a;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	if(n<m){
		cout<<"NE";
		return 0;
	}
	for(int i=1;i<=m;i++){
		cin>>a;
		if(a<4){
			cout<<"NE";
			return 0;
		}
		cnt+=a/4;//int类型自动向下取整
	}
	if(cnt<n){
		cout<<"NE";
	}
	else cout<<"DA";
	return 0;
}
```

---

## 作者：FurippuWRY (赞：0)

思路：因为一张桌子需要 $4$ 把椅子，所以第 $i$ 种颜色的椅子一共会摆出 $\left\lfloor\dfrac{a_i}{4}\right\rfloor$ 把。但注意到：

>- 每张桌子的椅子颜色需要相同  
>- 每种颜色的椅子至少有一张桌子用到了

当 $a_i < 4$ 时，无法安排椅子，输出 `NE`。

而且根据上述两点可以推出，当 $n < m$ 时，也同样无法安排椅子，这种情况也输出 `NE`。

以及还有一点情况：放不满，这种情况下用一个变量 $ans = 0$，对于不同的 $i$，$ans\leftarrow ans + a_i$，如果加完了之后 $ans < n$，则意味着放不满，输出 `NE`。

如果上述情况都不满足，输出 `DA` 就行了。

```cpp
#include <bits/stdc++.h>

using namespace std; 

const int N = 1145141;

int n, m, a[N], ans;

int main(){
	cin >> n >> m;
	if (n < m) {
		puts("NE");
		return 0;
	}
	for (int i = 1; i <= m; ++i) {
		cin >> a[i];
		if (a[i] < 4) {
			puts("NE");
			return 0;
		}
		ans += a[i] / 4;
	}
	if (ans < n) {
		puts("NE");
		return 0;
	}
	puts("DA");
	return 0;
}
```

---

## 作者：CleverPenguin (赞：0)

题不难，但是细节极多。   
题意简述：有 $n$ 个桌子，有 $m$ 种颜色的椅子，每个桌子需要四把椅子，你需要把每个桌子都配上颜色，而每个桌子只可以有一种颜色的椅子，每种颜色都需要用上。  
先看我说的最后一句话：也就是说，每种颜色的椅子都需要四把及以上的椅子才可以，所以就有了第一种情况：
```cpp
if(a[i]<4){
	cout<<"NE";
	return 0;
}
```
其次，每个桌子只能有一种颜色，所以不能所有加起来再除以四，要一个一个算：
```cpp
sum+=a[i]/4;
```

最后最后，要记得特判：
```cpp
if(n<m){
	cout<<"NE";
	return 0;
}
```

---

## 作者：gaoleng_luogu_name (赞：0)

简单题，建议红。

要做出这一道题，只需要分析一下两个条件，找出在什么情况下不能满足条件，特判掉即可。

先来分析第一个条件。

“每张桌子的椅子颜色需要相同”。联系一下前文“对于每张桌子来说，Paula 和 Domagoj 需要增置 $4$ 把椅子”。那么告诉我们的就是：如果有一种颜色的椅子数量不足 $4$ 个，那么就无法完成条件中“颜色需要相同”。于是便可以写出这样的特判代码：
```cpp
for(int i=1;i<=m;i++) 
{
	cin>>a[i];
	if(a[i]<4)
	{
		cout<<"NE";
		return 0;
	}
}
```

再看第二个条件。

“每种颜色的椅子至少有一张桌子用到了”，就是告诉我们，椅子的颜色数量必须小于等于桌子的个数。就可以写出这样的特判：
```cpp
if(n<m)
{
    cout<<"NE";
    return 0;
}
```

剩下的求解步骤就显得十分简单了，只需计算出这些椅子最多能摆几张桌子即可，自行看代码。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
int a[105];
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++) 
	{
		cin>>a[i];
		if(a[i]<4)
		{
			cout<<"NE";
			return 0;
		}
	}
	if(n<m)
	{
		cout<<"NE";
		return 0;
	}
	int sum=0;
	for(int i=1;i<=m;i++)
	{
		sum+=a[i]/4;
	}
	if(sum>=n) cout<<"DA";
	else cout<<"NE";
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/130421675)

---

## 作者：ZYH_juruo (赞：0)

## 题目传送门
[P9756 [COCI2022-2023#3] Estimathon](https://www.luogu.com.cn/problem/P9756)

## 题目大意

给你 $n$ 个桌子，每个桌子需要 $4$ 个椅子。现在有 $m$ 种颜色的椅子，每种颜色有 $a_i$ 个椅子。在符合题目中给出的规则下，问你是否可以有一种合法的安排方式。

## 题目分析
由规则二可以得知：当颜色种类大于桌子数量时，也就是 $m>n$ 时，肯定没有合法方式。

每种颜色对答案的贡献为 $\left\lfloor\dfrac{a_i}{4}\right\rfloor$，那么我们可以将它统计起来。与 $n$ 进行比较，这题就结束了。

当然，还有一个小点。当同一颜色的桌子数小于 $4$ 时，那么它根本不合法。
## ACCODE
```cpp
#include<bits/stdc++.h>
#define maxn 105
using namespace std;
int n,m,ans;
int a[maxn];
int main()
{
	cin>>n>>m;
	if(n<m)
	{
		cout<<"NE"<<endl;
		return 0;
	}
	for(int i=1;i<=m;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++)
	{
		ans+=a[i]/4;
		if(a[i]<4)
		{
			cout<<"NE"<<endl;
			return 0;
		}
	}
	if(ans>=n) cout<<"DA"<<endl;
	else cout<<"NE"<<endl;
	return 0;
}
```

离CSP不远了，祝大家CSP J/S RP++!

完结撒花！！！


---

## 作者：hjfjwl (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9756)

### 题目大意：

有 $n$ 张桌子，$m$ 种颜色的椅子，第 $i$ 种椅子有 $a_i$ 把，要求你每张桌子都要配 $4$ 张颜色一致的椅子，并且每种颜色的椅子都要用到。

### 思路：
用一个变量 $cnt$ 来记录最多能给多少桌子配一套，$flag$ 用来标记是否每一张桌子是否都可以配一套。要注意如果 $m > n$ 的话也是不可以的。


### AC code:
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	int cnt = 0;
	bool flag = true;
	for(int i = 1;i <= m;i++)
	{
		int a;
		scanf("%d",&a);
		int t = a / 4;
		flag &= (t >= 1 ? 1 : 0),cnt+=t;
	//	cout << t<< endl;
	}
	if(flag && cnt >= n && m <= n)
	{
		puts("DA");
	}
	else
	{
		puts("NE");
	}
	return 0;
}
```

---

## 作者：zcs_ (赞：0)

本题的思路很简单，难度红就可以。

首先，如果 $a_{i}$ 直接就小于 $4$ 了，那证明这个方案根本不可行，输出"NE"即可。

还有一个特殊条件，就是桌子数量小于颜色数量了，也就是根本没法完成题目中"每种颜色的椅子至少有一张桌子用到了"的条件，输出"NE"。

否则，方案就是可行的，输出"DA"。

代码如下：

```cpp
#include <iostream>
using namespace std;
int main(){
	int n,m,a[105];
	cin>>n>>m;
	for (int i=1;i<=n;i++)cin>>a[i];
	for (int i=1;i<=n;i++){
		if (a[i]<m){
			cout<<"NE";
			return 0;
		}
	}
	if (n<m)cout<<"NE";
	cout<<"DA";
	return 0;
}

---

## 作者：JimmyDong (赞：0)

## 思路
- 对于 $n<m$，显然无法满足。
- 对于有一种颜色不足 $4$ 把椅子，无法满足。
- 对于放上能放的所有椅子且仍然放不满 $n$ 张桌子，无法满足。
- 其余情况输出 `DA`。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[105],cnt;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
		cin>>a[i];
        if(a[i]<4)
        {
            cout<<"NE";
            return 0;
        }
        cnt+=a[i]/4;
    }
    if(n<m) cout<<"NE";
    else if(cnt<n) cout<<"NE";
    else cout<<"DA";
    return 0;
}
```


---

## 作者：Neilchenyinuo (赞：0)

## 题目大意

 给定 $n$ 张桌子，$m$ 种椅子的颜色，求是否可以有一种方案满足以下要求：

1. 每张桌子的椅子颜色需要相同。

2. 每种颜色的椅子至少有一张桌子用到了。

## Solution

1. 如果说当前第 $i$ 种颜色的数量  $a_i$ 不足四个，凑不齐一桌，肯定无解。

2. 每种颜色最多使用 $\left\lfloor\dfrac{a_i}{4}\right\rfloor$ 个桌子，这时我们就可以将其累加起来，然后判断一下：

1. 如果说需要使用的桌子数量不足 $n$ 张，那么就输出 `NE`。

2. 反之，就可行，输出 `DA` 即可。

## 坑点

1. 如果你 $n<m$ 的话，肯定是无解的，因为你桌子没有颜色多肯定是放不完的，所以说也要输出 `NE`。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=105;
int n,m,a[N],sum;
int main()
{
    cin>>n>>m;
    if(n<m)
        return cout<<"NE",0;
    for(int i=1;i<=m;i++)
    {
        cin>>a[i];
        if(a[i]<4)
            return cout<<"NE",0;
        sum+=a[i]/4;
    }
    if(sum>=n)
        cout<<"DA";
    else
        cout<<"NE";
    return 0;
}
```


---

## 作者：Vct14 (赞：0)

如果桌子的数量小于椅子颜色的数量，那么一定有某种颜色的椅子不会被使用，因此没有可能的安排方式；因为每种颜色的椅子至少要有一张桌子用到了，而且每张桌子的椅子颜色需要相同，即需要 $4$ 把颜色相同的椅子，所以如果某种颜色的椅子少于 $4$ 把，也无法安排。

因为 $4$ 把颜色相同的椅子可以用来摆一张桌子，那么 $k$ 把颜色相同的椅子就可以用来摆 $\left\lfloor\dfrac{k}{4}\right\rfloor$ 张桌子。那么所有椅子一共可以摆 $s=\sum\limits_{i=1}^n\left\lfloor\dfrac{a_i}{4}\right\rfloor$ 张桌子。

如果 $s\geqslant n$，那么可以按要求摆放，否则无解。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,m;
    cin>>n>>m;
    int a,s=0;
    if(n<m){
    	cout<<"NE";
    	return 0;
	}
    for(int i=1; i<=m; i++){
    	cin>>a;
        if(a<4){
            cout<<"NE";
            return 0;
        }
        s+=a/4;
    }
    if(s>=n) cout<<"DA";
    else cout<<"NE";
    return 0;
}
```

因为对于 $a$ 的所有操作可以放在一起，所以不必用存储 $a$ 数组。

---

## 作者：ys_kylin__ (赞：0)

[原题](https://www.luogu.com.cn/problem/P9756)

本题非常简单，建议评红。

题目大意：给 $n$ 张桌子，$m$ 种颜色，和每种颜色的椅子数量。每桌 $4$ 人，要求每桌颜色相同，且所有颜色都要用到，所有桌子都有椅子。

然后，做以下考虑：
1. 首先，假如颜色数量大于桌子数量，必有颜色不会用到，无解。
2. 接下来，当任意颜色数量 $<4$ 时，该颜色用不了，无解。
3. 假如目前椅子组数（颜色相同的四把椅子为一组）$<n$ 时，无法放满，无解。
4. 最后，就是有解了。

然后就没了，就是这么简单。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,ans=0;//ans 记录椅子组数。
	scanf("%d%d",&n,&m);
	if(m>n) printf("NE"),exit(0);//exit直接退出。
	for(int i=1,x;i<=m;i++) {
		scanf("%d",&x);
		if(x<4) printf("NE"),exit(0);
		ans+=x/4;
	}
	if(ans<n) printf("NE"),exit(0);
	printf("DA");
	return 0;
}//十五行搞定
```

---

## 作者：麟落 (赞：0)

UPD：23/10/24 修改判断式

观察题目中的两个要求，可以推出以下条件：

- 每张桌子需要 $4$ 张椅子，且颜色需要一致
- 每种颜色都需要被用到，即至少需要 $4$ 种颜色

整理一下不难看出仅有以下可能会导致安排失败：
$$
a_i < 4 \;or\;  n < m \; or  \left( \sum_{i=1}^m \left\lfloor \frac {a_i}{4} \right\rfloor \right) < n
$$
故而整理出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[110],cnt;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=m;i++)
        cin>>a[i];
    if(n<m)
    {
        cout<<"NE";
        return 0;
    }
    for(int i=1;i<=m;i++)
    {
        if(a[i]<4)
        {
            cout<<"NE";
            return 0;
        }
        cnt+=a[i]/4;
    }
    if(cnt<n)
        cout<<"NE";
    else cout<<"DA";
    return 0;
}
```

---

## 作者：_buzhidao_ (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/P9756)  
# 题目分析
- 要求每张桌子的椅子颜色需要相同，所以每种颜色的椅子能增置 $\lfloor \frac{a_i}{4} \rfloor$ 张桌子。
- 要求每种颜色的椅子至少有一张桌子用到了，所以当 $a_i<4$，必定无法满足要求。**特别地，当 $n<m$ 时，必定无法使用所有颜色，直接输出 `NE` 即可**。

最后，只要统计**所有桌子是否都能被增置**，即，判断 $\sum \lfloor \frac{a_i}{4} \rfloor$ 是否 $\ge n$。
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,sum;
int main(){
    cin>>n>>m;
    if(n<m){//特判
        cout<<"NE";
        return 0;
    }
    for(int i=0;i<m;++i){
        cin>>a;
        if(a<=3){//ai<4
            cout<<"NE";
            return 0;
        }
        sum+=a/4;//统计
    }
    if(sum>=n) cout<<"DA";
    else cout<<"NE";
    return 0;
}
```

---

## 作者：fillemomo (赞：0)

[题面](https://www.luogu.com.cn/problem/P9756)

## 思路
简单的模拟题。

1. 通过条件 $2$，我们发现如果椅子的种类数量比桌子的总数量多，则无法满足，直接输出 `NE`。

1. 通过条件 $2$，以及每个桌子都必须要 $4$ 把椅子，我们发现如果某种种类的椅子数量比 $4$ 小，则直接 `NE`。

1. 对于某种种类的椅子数量 $s$，可以凑成 $s$ 除以 $4$ 把桌子的配套，将其相加。

最后将相加的值与要配套的桌子总数比较。

~~听说 CSP 2023 -J2 考前发题解 RP++~~

## [AC](https://www.luogu.com.cn/record/130022757)代码
```cpp
#include <iostream>
using namespace std;
void RP()
{
	long long CSP_RP=0;
	while(1) CSP_RP+=1e18;
}
int n,m,a[105];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-f;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
int s;
int main()
{
	ios::sync_with_stdio(false);
	n=read();
	m=read();
	if(m>n) 
	{
		printf("NE\n");
		return 0;
	}
	for(int i=1;i<=m;i++)
	{
		a[i]=read();
		if(a[i]<4)
		{
			printf("NE\n");
			return 0;
		}
		s=s+a[i]/4;	
	}
	if(s>=n) printf("DA\n");
	else printf("NE\n");



	return 0;
}
```
# CSP 2023 -J2 RP++

---

## 作者：lichenzhen (赞：0)

## 题目大意
在放置了 $n$ 张桌子的房间里增加椅子。有 $m$ 种不同颜色的椅子，每种颜色有 $a_i$ 把。每张桌子需要 $4$ 把椅子。要求每张桌子上的椅子颜色相同，并且每种颜色的椅子至少要用在一张桌子上。求是否存在一种满足这些条件的安排方式。

## 题目解法
解法比较简单，可以很容易想出，如果 $m>n$ 无论如何都无法满足种颜色的椅子至少要用在一张桌子上。

如果 $a_i<4$，肯定也无法满足上述条件。

之后，看一下当前所有椅子是否可以摆满所有的桌子，直接循环统计一下每种颜色能够放满几个桌子。若这个数小于 $n$，则也无法满足上述条件。

排除上面的情况，那么就存在一种满足这些条件的安排方式。

### 题目解法
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110],n,m,ans;
int main(){
	cin>>n>>m;
	if(m>n) cout<<"NE\n",exit(0);
	for(int i=1;i<=m;i++) {
		cin>>a[i];
		if(a[i]<4) cout<<"NE\n",exit(0);
	}
	for(int i=1;i<=m;i++) ans+=a[i]/4;
	puts(ans>=n?"DA":"NE");
} 
```

---

## 作者：TruchyR (赞：0)

## Part 1 思路
下文如果说椅子与桌子配对，表示对应桌子的椅子满足要求。  
先考虑什么时候不可以：  
- $n<m$ 时，显然有某种颜色的椅子无法与桌子配对。  
- $a_i<4$ 时，第 $i$ 种颜色的椅子根本无法与桌子配对。  
- $\sum_{i=1}^{m} \left \lfloor \frac{a_i}{4} \right \rfloor < n$ 时，所有的椅子不足以与所有桌子配对。

剩下的情况就是可以了。
## Part 2 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a,l;
void exY(){cout<<"DA";exit(0);}
void exN(){cout<<"NE";exit(0);}
signed main(){
	cin.tie(0);cout.tie(0);
	cin>>n>>m;
	if(n<m) exN();//第一个条件判断
	for(int i=1;i<=m;i++){
		cin>>a;
		if(a<4) exN();//第二个条件判断
		l+=(a>>2);//第三个条件记录
	}
	if(l>=n) exY();//第三个条件判断
	exN();
}
```


---

## 作者：CheZiHe929 (赞：0)

# P9756 题解

### 简要思路

整理题目的信息，我们可以发现，无非就是让我们判断三个条件是否满足：

1. 每个颜色的椅子都要使用，也就是要保证每一个 $a_i$ 都 $\geq 4$；

2. 所有颜色的椅子能组成的桌子的数量要 $\geq$ 要求桌子的数量；

3. **桌子的数量要 $\geq$ 椅子的颜色数（这样才能保证每个颜色的椅子都使用**。

如果满足上述条件就输出 `DA`，否则输出 `NE`。

### 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'

int n,m;
int x;
int ans;

signed main(){
	
	std::cin>>n>>m;
	for(int i=1;i<=m;i++){
		std::cin>>x;
		if(x<4){//不满足条件一
			std::cout<<"NE\n";
			return 0;
		}
		ans+=x/4;
	}
	
	if(ans<n)std::cout<<"NE\n";//不满足条件二
    else if(n<m)std::cout<<"NE\n";//不满足条件三
	else std::cout<<"DA\n";
	return 0;
}
```

**THE END.**

**THANK YOU.**

---

## 作者：UniGravity (赞：0)

## Solution P9756 [COCI2022-2023#3] Estimathon

[传送门](https://www.luogu.com.cn/problem/P9756)   
~~蒟蒻又来水题解了~~

感觉这题应该评入门。

### 题意简述
$n$ 张桌子，有如下要求：
* 每张桌子配 $4$ 把椅子。
* $4$ 把椅子的颜色相同。
* 每种颜色的椅子至少用到 $1$ 次。

问是否有分配椅子的解。

### 思路分析
分析一下题目所说条件：
1. 当椅子的颜色数量 $m>n$ 时一定**无解**，因为此时必然有某个颜色的椅子**没有用到**。
2. 若某种椅子的数量 $a_i<4$ 时也**无解**，因为**凑不齐**一张桌子。

不难发现此时统计最多能凑齐多少张桌子，如果凑齐的桌子数量 $cnt>n$ 即为有解。

至于每一个 $a_i$，最多能凑齐 $\lfloor\frac{a_i}{4}\rfloor$ 张桌子。

### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[105];

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }
    if (m > n) {
        printf("NE");
        return 0;
    }
    
    int cnt = 0;
    
    for (int i = 1; i <= m; i++) {
        cnt += a[i] / 4;
        if (a[i] < 4) {
            printf("NE");
            return 0;
        }
    }
    if (cnt >= n) {
        printf("DA");
    } else {
        printf("NE");
    }
    return 0;
}
```

---

## 作者：ZBH_123 (赞：0)

## 思路：分情况讨论
对于本题，我们可以分出如下的情况：椅子的总数小于需要的椅子数或桌子的数量小于椅子颜色的数量，某一种颜色的椅子数量小于 $4$，以及 $m \lt n$ 的情况。对于第一种情况和第二种情况，那肯定是没有合理方案的。对于第三种情况，如果剩下的椅子能摆完剩下的桌子，那就肯定有合理的方案。

**AC code：**
```cpp
#include<iostream>
using namespace std;
int n,m,a[105],sum;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
		sum+=a[i];
	}
	if(sum<4*n||n<m){
		cout<<"NE";
		return 0;
	}
	for(int i=1;i<=m;i++){
		if(a[i]<4){
			cout<<"NE";
			return 0;
		}
	}
	if(m<n){
		for(int i=1;i<=m;i++){
			if(a[i]-4>=(n-m)*4){
				cout<<"DA";
				return 0;
			}
		}
		cout<<"NE";
		return 0;
	}
	cout<<"DA";
	return 0;
}
```

---

## 作者：Clarinet (赞：0)

建议评红。  
[博客食用观感更佳](https://www.luogu.com.cn/blog/Czel-X/ti-xie-3-post)
# 简要题意
给出 $n$ 张桌子和 $m$ 种不同颜色的椅子以及每种颜色椅子的个数，问能否同时满足一下两个条件（每张桌子放 4 把椅子）：  
- 每张桌子的椅子颜色相同
- 每种颜色的椅子都被用过

# 分析
既然每张桌子至少放 4 把椅子，那么如果有一种颜色的椅子少于 4 把那肯定就不能被用了，所以不成立。如果椅子的颜色种类大于桌子数量，那肯定也会多出椅子不被用。最后如果椅子数量凑不够，也是不成立的。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100],sum;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>a[i];
		if(a[i]<4){
			cout<<"NE";
			return 0;
		}
		sum+=a[i]/4;
	}
	if(sum<n||m>n){
		cout<<"NE";
		return 0;
	}
	cout<<"DA";
	return 0;
}
```
感谢阅读！

---

