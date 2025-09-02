# [GCJ 2012 Qualification] Dancing With the Googlers

## 题目描述

你正在观看一场节目，Googler（Google 员工）们在跳舞，每位舞者会被三位评委分别打分，得到一个分数组成的三元组。每个三元组由三个 $0$ 到 $10$ 的整数分数组成。评委们的打分标准极为接近，因此如果一个三元组中有两个分数相差 $2$，就会被认为是**令人惊讶的**。不会出现分数之间相差超过 $2$ 的三元组。

例如：$(8, 8, 8)$ 和 $(7, 8, 7)$ 都不是令人惊讶的。$(6, 7, 8)$ 和 $(6, 8, 8)$ 都是令人惊讶的。$(7, 6, 9)$ 永远不会出现。

某位 Googler 的总分就是其分数组成的三元组的和。该 Googler 的最佳成绩是三元组中最大的分数。现在，给定每位 Googler 的总分，以及所有令人惊讶的三元组的数量，你需要求出最多有多少个 Googler 的最佳成绩可以达到至少 $p$ 分。

例如，假设有 $6$ 位 Googler，他们的总分分别为 $29$、$20$、$8$、$18$、$18$、$21$。你记得有 $2$ 个三元组是令人惊讶的，你想知道有多少 Googler 的最佳成绩能达到 $8$ 分或更高。

在这些总分下，且已知有两个三元组是令人惊讶的，可能的三元组如下：

```
10 9 10
6 6 8 (*)
2 3 3
6 6 6
6 6 6
6 7 8 (*)
```

带有（`*`）标记的是令人惊讶的三元组。这样，最多有 $3$ 位 Googler 至少有一项分数达到 $8$ 分。不存在比 $3$ 更大的可能，因此答案为 $3$。


## 说明/提示

**限制条件**

- $1 \leq T \leq 100$
- $0 \leq S \leq N$
- $0 \leq p \leq 10$
- $0 \leq t_i \leq 30$
- 至少有 $S$ 个 $t_i$ 满足 $2 \leq t_i \leq 28$

**测试集 1（10 分，结果可见）**

- $1 \leq N \leq 3$

**测试集 2（10 分，结果隐藏）**

- $1 \leq N \leq 100$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
4
3 1 5 15 13 11
3 0 8 23 22 21
2 1 1 8 0
6 2 8 29 20 8 18 18 21```

### 输出

```
Case #1: 3
Case #2: 2
Case #3: 1
Case #4: 3```

# 题解

## 作者：abc1234shi (赞：6)

看到题解区的题解都很复杂、绕口，于是想写一篇大家都能看懂的题解。
# 分析
贪心加数学理论。
# 思路
普通情况很好算，将三次总和直接除 $3$ 并向上取整即可，因为如果有余数的话，向上取整相当于求出最小分数加 $1$，这里不考虑令人惊讶的情况，所以最小分数加 $1$，就是最大分数。如果没有余数，向上取整会取当前整数。

接下来看令人惊讶的情况。这里加特判，如果三次总和小于 $2$ 时，最小分数会小于 $0$，不能出现分数为负数的情况，所以要加特判。同理，不能出现分数大于 $10$ 的情况，所以三次分数不会大于 $28$，也要加特判。

我们设最小分数为 $x$，因为这是令人惊讶的三元组，所以最大分数一定是 $x+2$，接下来就差中间那个数了。因为中间那个数不能大于最大分数也不能小于最小分数，所以中间数（设为 $k$）的取值范围为 $x≤k≤x+2$，所以 $k$ 可取 $x$，$x+1$，$x+2$。

那我们就来分类讨论：

- 若 $k=x$，则三数总和为 $x+x+x+2=3x+2$，这里求出最大分数 $x+2$ 可以选择将总和先加 $4$ 再除 $3$，或者将总和加 $2$ 或 $3$ 向上取整都能求出最大分数 $x+2$。

- 若 $k=x+1$，则三数总和为 $x+x+x+2+1=3x+3$，这里求出最大分数 $x+2$ 可以选择将总和先加 $3$ 再除 $3$，或者将总和加 $1$ 或 $2$ 向上取整都能求出最大分数 $x+2$。

- 若 $k=x+2$，则三数总和为 $x+x+x+2+2=3x+4$，这里求出最大分数 $x+2$ 可以选择将总和先加 $2$ 再除 $3$，或者将总和加 $1$ 向上取整都能求出最大分数 $x+2$。

我们需要找到一个式子，使得在三种中间数的取值中都能正确的算出 $x+2$，观察发现三个式子都可以通过将总和加 $2$ 再除 $3$ 并向上取整算出最大分数 $x+2$。所以在令人惊讶的三元组中，可以通过将总和加 $2$ 除 $3$ 并向上取整算出最大分数 $x+2$。

接下来进行判断，我们定义两个变量：一个存储答案数量；一个存储三元组满足原本最大分数不大于等于 $p$，但成为三元组后最大分数大于等于 $p$ 的三元组数量（这里不能直接将答案数组加一，因为令人惊讶的三元组数量有规定）。

那么如果原本最大分数就大于等于 $p$ 了，直接将答案变量加一。否则再判断，如果它成为令人惊讶的三元组后最大分数大于等于 $p$，就将预答案数量加一（即将存储满足原本最大分数不大于等于 $p$，但成为三元组后最大分数大于等于 $p$ 的三元组数量的变量加一）。

接下来再进行判断，如果预答案数量大于等于规定的令人惊讶的三元组数量，就将答案变量增加题目规定的令人惊讶的三元组数量。否则就将答案变量增加预答案数量。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110000];
int main(){
	int t;
	cin>>t;
	for(int rt=1;rt<=t;rt++){
		int n,s,p;
		cin>>n>>s>>p;
		int ans=0,sum=0;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			int h;
			if(a[i]==0||a[i]==1||a[i]==29||a[i]==30){
				if(ceil(1.00*a[i]/3)>=p)sum++;
			}
			else if(ceil(1.00*a[i]/3)>=p){
				sum++;
			}
			else {
				
				h=ceil((2+1.00*a[i])/3);
				if(h>=p)ans++;
			}
		}
		if(ans>=s)sum+=s;
		else sum+=ans;
		cout<<"Case #"<<rt<<": "<<sum<<endl;
	}
	return 0;
}
```

---

## 作者：DeekSeep_V3 (赞：5)

**蒟蒻水平过低，神犇大佬勿喷**
---

题意分析
---
有 $T$ 组数据，每组数据有 $n$，$s$，$p$，$n$ 代表有 $n$ 个 Googler，$s$ 代表令人惊讶的三元组数量，$p$ 代表最佳成绩，然后是 $n$ 个 $a_i$，代表分别表示每位 Googler 的总分，**注意是总分！！！** 求最佳成绩大于等于 $p$ 的 Googler 个数。

贪心证明
---
~~聪明的我手滑点到了算法标签~~!!!居然是贪心证明！！。

再分析一遍题目，可以知道只有四种情况

1. 普通情况，对于三元组 $(x,y,z)$，最极限为$(p,p-1,p-1)$。
2. 比较特殊的情况，若三元组是令人惊讶的，则最极限为 $(p,p-2,p-2)$。
3. 如果 $p$ 小于等于 $1$ 呢？？？所以，我们应该加个判断条件 ```a[j]>=2&&a[j]<=28```。
4. 最后一种情况，前三种情况全都不是，也就是说不参与计数。

具体思路见代码
---
**快乐的代码时间到了**

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,s,p;
int main(){
    cin>>T;
    for (int i=1;i<=T;i++){
        cin>>n>>s>>p;
        int a[100];
        for (int j=1;j<=n;j++) cin>>a[j];
        int ans=0; // 一定能达到 p 分的 Googler 数量
        int cnt=0; // 可能通过惊讶三元组达到 p 分的 Googler 数量
        for (int j=1;j<=n;j++){
            int maxx=(t+2)/3;
            // 如果普通情况就能达到 p 分，直接计数
            if(maxx>=p) ans++;
            // 否则检查是否可能通过惊讶三元组达到 p 分
            else if(a[j]>=2&&a[j]<=28){//只有总分在 2-28 之间才可能组成惊讶三元组
                int maxx=(t+4)/3;
                if(maxx>=p) cnt++; //可能通过惊讶达到 p 分
            }
        }
        if(cnt<s) ans+=cnt; // 如果可能惊讶的数量小于可用名额，全部使用
        else ans+=s;// 否则只能使用 s 个名额
        cout<<"Case #"<<i<<": "<<ans<<endl;
    }
    return 0;
}
```
完结撒花QWQ✿✿ヽ(°▽°)ノ✿

---

## 作者：QQ9178 (赞：3)

思路：  
如果不是令人惊讶的三元组，那么三个分数应该都会接近 $\frac{n}{3}$，此时的最大值应该为 $ \lceil x \rceil $。  
如果是令人惊讶的三元组，那么三个分数的差可能更大。  
对于每个总分，算出它不是令人惊讶的三元组的最大值 $ \lceil x \rceil $，然后再判断它是否大于等于 $P$，即题面所述要求的最佳成绩，如果大于，说明它肯定不用是令人惊讶的三元组。  
那如果它小于 $P$，再计算它是令人惊讶的三元组的情况的最大值，那么如果它现在大于等于 $P$，而还有剩余的 $S$，则将 $S$ 减一，利用一次 $S$。  
这就是这道题的贪心：优先考虑那些如果不是令人惊讶的三元组无法达到 $P$ 而如果是令人惊讶的三元组可以达到 $P$ 的那些 $T_i$。  
代码：  

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n, s, p;
	    cin >> n >> s >> p;
	    int t[n];
	    for (int i = 0; i < n; ++i) cin>>t[i];
	    int cnt = 0;
	    for (int i=0;i<n;i++) {
	        int maxx = (t[i] + 2) / 3;  // 计算不是令人惊讶的三元组的最大值 
	        if (maxx >= p) cnt++;
	        else {
	            int maxn = (t[i] >= 2) ? ((t[i] + 4) / 3) : t[i];  //计算是令人惊讶的三元组的最大值，特判1 
	            if (maxn >= p && t[i] >= 2 && t[i] <= 28) 
	                if (s > 0) {//贪心考虑那些如果不是令人惊讶的三元组无法达到 P 而如果是令人惊讶的三元组可以达到 P 的那些 T[i] 
	                    s--; 
	                    cnt++;
	                } 
	        }
	    }
	    cout << "Case #" << i << ": " << cnt << endl;
    }
    return 0;
}
```

---

## 作者：Xiaoshangjie (赞：2)

### 题意
每一组数据有 $n,s,p$ 三个参数以及 $n$ 个三元组 $(a_i,b_i,c_i)$ 三数总和，若三元组中的任意两个数相差为 $2$，则是“令人惊讶的”。已知“令人惊讶的”三元组只有 $s$ 个，求每个三元组中的最大值大于等于 $p$ 的这样的三元组的个数。
### 思路
~~机智的我打开了算法标签。~~ 发现这题是贪心。

**贪心策略：**  
将每一组的总分从大到小枚举，这样只要有一个不满足条件（分低了），之后总分比其更小的就一定不满足了。

- **怎么判断是否符合条件呢？**  
对于三元组 $(x,y,z)$，若 $x+y+z=k$，则当 $3p-2\le k$ 时满足条件。  
证明：若三元组 $(x,y,z)$ 满足条件且不是“令人惊讶的”三元组，则三元组 $(x,y,z)$ 最坏的情况是 $(p,p-1,p-1)$ ，其和为 $3p-2$，只要 $k$ 大于等于 $3p-2$ 即可。
- **如果不符合条件怎么办？**  
  同上，尽量让这个三元组计入“令人惊讶的”三元组，最坏情况是 $(p,p-2,p-2)$ 即 $3p-4\le k$。
- **还不满足呢？**  
  这样的话，这个三元组永远不符合条件，从答案中剔除即可。

**特别注意：**  
若“令人惊讶的”三元组超过 $s$ 个，剩下的就要放入“永远不满足条件”一栏。（只有基于这个贪心思路才能这样）

这样的话，我们可以写出：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s,p,a[105];
int main()
{
    cin>>t;
    for(int k=1;k<=t;k++)
    {
        cin>>n>>s>>p;
        int ans=n,cnt=0;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        for(int i=n;i>=1;i--)
        {
            if(p*3-2<=a[i]) continue;
            else if(p*3-4<=a[i] && cnt<s) cnt++;
            else ans--;
        }
        cout<<"Case #"<<k<<": "<<ans<<endl;
    }
    return 0;
}
```
你发现样例的 Case#3 WA 了，为什么？

这是因为 $1\le p$，那么 $3p-4$ 有可能是负数，需要和 $1$ 取 $\rm max$。 

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,s,p,a[105];
int main()
{
    cin>>t;
    for(int k=1;k<=t;k++)
    {
        cin>>n>>s>>p;
        int ans=n,cnt=0;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        for(int i=n;i>=1;i--)
        {
            if(p*3-2<=a[i]) continue;
            else if(max(p*3-4,1)<=a[i] && cnt<s) cnt++;
            else ans--;
        }
        cout<<"Case #"<<k<<": "<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：Sunrise_up (赞：2)

这题感觉没有黄。

## 思路

很明显，我们可以贪心。

我们想要一个人在总分一定的情况下，最高分数越大，最好情况下，那我们就是让这个三元组是“令人惊讶的”即可。

根据这个分析，我们可以得出让三元组是“令人惊讶的”这个条件对我们有利。然而有 $s$ 次机会可以让三元组是“令人惊讶的”。

然后呢，分类讨论：

- 若不让三元组是“令人惊讶的”的话，三元组最低要求就是 $(p-1,p-1,p)$，总和为 $3p-2$。
- 若让三元组是“令人惊讶的”的话，三元组最低要求就是 $(p-2,p-2,p)$，总和为 $3p-4$，但是这个构造的前提是 $2\le t_i\le 28$。
- 如果再不行，那就没有办法了，不管它。

## 代码

我们稍稍卡个常：

```cpp
#include<iostream>
using namespace std;
int t,te,n,s,p,x,ans;
main(){
	//ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		ans=0;
		cin>>n>>s>>p;
		while(n--){
			cin>>x;
			(p*3<=x+2?ans++:(1<x&&x<29&&s&&p*3<=x+4?ans++,s--:0));
		}
		cout<<"Case #"<<++te<<": "<<ans<<'\n';
	}
}
```

点个赞吧 qwq！

---

## 作者：llh2012 (赞：1)

## 题意
给出 Googler 的人数  $n$，令人惊讶的三元组数量 $s$，要求的最佳成绩 $p$，分别给出每位 Googler 的总分。求最多有多少个 Googler 的最佳成绩能达到 $p$。 
## 思路
看到最多，想到贪心。
#### 贪心方法：
逐个枚举，若这个 Googler 的总分能达到  $3\times p-2$，则答案加一。若这个 Googler 的总分能达到  $3\times p-4$ 且 $s>0$ ，则答案加一， $s$ 减一。
#### 贪心证明
若这个 Googler 的总分能达到  $3\times p-2$，则这个 Googler 分数最坏一定能是 $(p,p-1,p-1)$，满足最佳成绩能达到 $p$。

若这个 Googler 的总分能达到  $3\times p-4$ 且 $s>0$，则这个 Googler 分数最坏一定能是 $(p,p-2,p-2)$，满足最佳成绩能达到 $p$，是一个令人惊讶的三元组，且将任何一个总分能达到 $3\times p-4$ 的 Googler 的分数作为令人惊讶的三元组都只能增加一个最佳成绩能达到 $p$ 的 Googler。

若这个 Googler 的总分不能达到  $3\times p-4$，则无论如何这个 Googler 的最佳成绩都不能能达到 $p$。
## 代码
易错点：当 $p=1$ 时，$3\times p-1<0$，而总分不能小于 0，故需特判。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,s,p,n,a[100001];
int main(){
    cin>>t;
    for(int k=1;k<=t;k++){
        memset(a,0,sizeof(int));
        long long ans=0;
        cin>>n>>s>>p;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++){
            if(a[i]>=p+p+p-2)//若这个 Googler 的总分能达到 3*p-2 
                ans++;
            else if(a[i]>=max(p+p+p-4,1)&&s>0){//若这个 Googler 的总分能达到 3*p-4 且 s>0
                ans++;
                s--;
            }
        }
        cout<<"Case #"<<k<<": "<<ans<<endl;
    }
}
```
~~这题真是黄题吗？~~

---

## 作者：Aamumatematiikka (赞：1)

### 题意

有 $n$ 个数，每个数 $t_i$ 需要拆分成 $3$ 个数的加和形式，其中这三个数的极差不超过 $2$，问在有 $s$ 个数拆分后极差为 $2$ 的情况下，最多有多少个数拆分后最大值大于等于 $p$。

### 思路

首先，由于 $s\le n$，并且如果拆分后最大值大于等于 $p$，则如果想要调整这 $3$ 个数的大小，存在方式可以使极差为 $2$，所以我们只需要求我们拆分出来的极差为 $2$ 的组合数小于等于 $s$ 即可。

不难发现，需要使用极差为 $2$ 的次数只有两种可能：

1. $t_i=(p-2)+(p-2)+p=3p-4$
2. $t_i=(p-2)+(p-1)+p=3p-3$

当 $t_i$ 的值来到 $3p-2$ 时，可以将其拆分为 $(p-1)+(p-1)+p$，不需要消耗极差为 $2$ 的次数；当 $t_i$ 的值变为 $3p-5$ 不存在最大值大于等于 $p$ 并且极差不大于 $2$ 的拆分方式。

所以我们可以判定这两个边界，来求可以有多少的 $t_i$ 变为满足条件的组合。

还有一个小细节，样例中贴心地为我们准备了一种需要判断的情况：$p=1,t_i=0$，此时满足 $3p-3=t_i$，但是题目要求 $0\le$ 分数 $\le10$，所以不满足条件。

### 代码

```cpp
#include <iostream>
using namespace std;
typedef long long ll;
const int N=105;
int T, n, s, p, ans=0;
int main(){
	scanf("%d",&T);
	for(int q=1;q<=T;q++){
		scanf("%d%d%d",&n,&s,&p);
		ans=0;
		for(int i=1;i<=n;i++){
			int a;
			scanf("%d",&a);
			if(a<3*p-4) continue;
			if(a>=3*p-2){
				ans++;
				continue;
			}
			if(s>0&&p-2>=0) s--, ans++;
		}
		printf("Case #%d: %d\n",q,ans);
	}
	return 0;
}
```

时间复杂度为 $O(Tn)$，可以通过这道题。

---

## 作者：lmz105 (赞：0)

### 思路
如果一个舞者的最佳成绩可以达到至少 $p$ 分且该舞者得到的三元组不是令人惊讶的，那么其总分至少为 $3p-2$，如果是令人惊讶的，其总分至少也是 $3p-4$，注意分数不能为负，需要将负数变成 $0$，接着把所有的总分从大到小排序，用二分先求出总分不少于 $3p-2$ 的个数，再求出总分不少于 $3p-4$ 的个数，注意后求出的个数不能超过 $s$，两次求出的结果之和就是答案。

### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
//#define rw() ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#ifndef rw()

namespace Pv {
	template<typename T> inline void r(T &in) {
		in = 0;
		bool bo = 0;
		char ch = getchar();
		while (!isdigit(ch))
			bo ^= (ch == '-'), ch = getchar();
		while (isdigit(ch))
			in = (in << 1) + (in << 3) + (ch ^ 48), ch = getchar();
		if (bo)
			in = -in;
	}
	template<typename T> inline void w(T out) {
		static char op[25];
		int top = 0;
		if (out < 0) {
			putchar('-');
			do {
				op[++top] = -(out % 10) + 48, out /= 10;
			} while (out);
		} else {
			do {
				op[++top] = out % 10 + 48, out /= 10;
			} while (out);
		}
		while (top)
			putchar(op[top--]);
	}
	template<typename T, typename... Ts> inline void r(T &in, Ts &... ins) {
		r(in), r(ins...);
	}
	template<typename T, typename... Ts> inline void w(T out, Ts... outs) {
		w(out), w(outs...);
	}
	inline void w(const char *p) {
		while (*p) {
			putchar(*p++);
		}
	}
}
using namespace Pv;
#endif
using namespace std;
ll T, n, m, k;

int main() {
	r(T);
	for (ll t = 1; t <= T; t++) {
		r(n, m, k);
		vector<ll>v;
		while (n--) {
			ll x;
			r(x);
			v.push_back(x);
		}
		sort(v.begin(), v.end(), greater<ll>());
		ll L = 0, R = v.size() - 1, id = -1;
		while (L <= R) {
			ll mid = L + R >> 1;
			if (v[mid] >= k + max(0LL, k - 1) * 2) {
				id = mid;
				L = mid + 1;
			} else {
				R = mid - 1;
			}
		}
		L = id + 1, R = min((ll)v.size() - 1, id + m);
		while (L <= R) {
			ll mid = L + R >> 1;
			if (v[mid] >= k + max(0LL, k - 2) * 2) {
				id = mid;
				L = mid + 1;
			} else {
				R = mid - 1;
			}
		}
		w("Case #"), w(t), w(": "), w(id + 1), w("\n");
	}
	return 0;
}
```

---

## 作者：IkillDream (赞：0)

# P13312 题解

## 前言

又是在机房写题的一天，TDT 这个菜鸟还跟我说这题可以用动态规划写，反正我看他写了三个小时也没写出来，还搞的我浪费了几十分钟的时间，后来就想到了贪心。

## 思路

方法：贪心。

首先我们需要对每位舞者的总分 $t$，计算非惊讶情况下的最高分，我们可以定义一个临时变量 $a$，让 $a=\lceil \frac{t}{3}\rceil$，若 $a\ge p$ 则直接计数，若基础分不足且还有惊喜名额，计算惊喜最高分，同样用以上方法定义一个临时变量 $b$，让 $b = \lceil \frac{(t + 2)}{3} \rceil$，满足 $b \ge p$ 且 $2 \le t \le 28$ 时消耗名额计数。

## [AC](https://www.luogu.com.cn/record/225484825) 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int tt[105];
int main(){
    int t,n,s,p,ans,cas=1;
    cin>>t;
    while(t--){
        cin>>n>>s>>p;
        for(int i=0;i<n;i++) cin>>tt[i];
        ans=0;
        for(int i=0;i<n;i++){
            int t=tt[i];
            int a=(t+2)/3;
            if(a>=p) ans++;
            else if(s>0){
                int b=(t+4)/3;
                if(b>=p && t>=2 && t<=28){
                    ans++;
                    s--;
                }
            }
        }
        cout<<"Case #"<<cas++<<": "<<ans<<endl;
    }
    return 0;
}
```

## 后记

小技巧：在不知道题目考点的时候，可以点开右边的**标签**来查看算法，温馨提示：比赛时可看不了哦。

题解制作不容易如果觉得我的题解写的好的话可以点个赞吗 qwq。

题解可以抄，但是你要学会哦！

祝大家 CSP-J/S 初赛，会的都对，蒙的全对。

---

## 作者：Clouds_dream (赞：0)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13312)  
即在给定的条件下，最多有多少位 `Googler` 的最佳成绩（即三个分数中的最大值）可以达到至少 $p$ 分。每个 `Googler` 的总分由三位评委打分得到，三元组中如果有两个分数相差 2 分或以上，就是令人惊讶的。已知有 $s$ 个三元组是令人惊讶的，我们需要最大化达到 $p$ 分的 `Googler` 数量。

### 题目分析
有两种构造三元组的方式：  
1. 不是令人惊讶的三元组：三个分数彼此之间最多相差 1 分。此时，最大分数为 $\lfloor (t_i + 2)  / 3 \rfloor$。
2. 令人惊讶的三元组：存在两个分数相差至少 2 分。此时，最大分数为 $\lfloor (t_i + 4)  / 3 \rfloor$。

分类讨论：
1. 在不使用令人惊讶三元组的情况下，最大分数已经 $\ge p$，这类 `Googler` 直接计入结果，不占用 $s$ 名额。
2. 在不使用令人惊讶三元组的情况下，最大分数 $< p$，但使用令人惊讶三元组时最大分数 $\ge p$。这类 `Googler` 需要占用一个 $s$ 名额才能达到 $p$。

我们只需要统计所有类型 1 的 `Googler` 数量。然后尽可能多地使用类型 2 的 `Googler`（最多 $s$ 个），以最大化达到 $p$ 分的 `Googler` 总数。

### 代码实现

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

int T;

void f(int t){
	int n,s,p;
	cin>>n>>s>>p;
	int a[n+10];
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int cnt1=0,cnt2=0;//cnt1:非令人惊讶三元组即可满足 p, cnt2:需要令人惊讶三元组才能满足 p
	for(int i=1;i<=n;i++){
		int num=(a[i]+2)/3;//非令人惊讶情况下的最大值
		if(num>=p)cnt1++;
		else{
			if(a[i]>=2&&a[i]<=28){
				if((a[i]+4)/3>=p)cnt2++;//令人惊讶情况下的最大值
			}
		}
	}
	cout<<"Case #"<<t<<": "<<cnt1+min(cnt2,s)<<endl;
}

signed main()
{
	fst
	cin>>T;
	for(int i=1;i<=T;i++){
		f(i);
	}
	return 0;
}
```

---

