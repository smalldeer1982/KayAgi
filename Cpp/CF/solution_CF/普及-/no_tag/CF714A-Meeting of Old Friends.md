# Meeting of Old Friends

## 题目描述

今天森林里将要发生一件大事——刺猬 Filya 要去看望他的老朋友 Sonya！  
Sonya 身为一只傲娇的猫头鹰，当然要在白天睡觉。不过，她会在 $[l_1,r_1]$ 分钟内会保持清醒。作为一只美美的猫头鹰，在第 $k$ 分钟，Sonya 会补妆，这时她和 Filya 不能在一起。  
Filya 有很多工作要做，他预计在 $[l_2,r_2]$ 分钟去探望 Sonya。  
请你计算两人可以相处多长时间。

## 说明/提示

### 【样例一解释】
在第 $[9,10]$ 分钟相处。
### 【样例二解释】
在第 $[50,74]$ 分钟和第 $[76,100]$ 分钟在一起，第 $75$ 分钟时 Sonya 当然是去补妆辣！

Translated by @Ehrgeiz  @I_love_him52

## 样例 #1

### 输入

```
1 10 9 20 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 100 50 200 75
```

### 输出

```
50
```

# 题解

## 作者：0xFF (赞：3)

#### 题目大意


------------
给出两个区间 $[l1,r1]$ 和 $[l2,r2]$，同时给出一个点 $k$ 表示该点不可取。求出两段区间相交的长度。

#### 题目分析


------------
观察样例

```1 100 50 200 75```

显然，两端区间的交集的左边界是两区间左边界的较大值，右边界是两区间右边界的较小值。

故答案为 $max(l1,l2) - min(r1,r2) + 1$。

同时要注意 $k$ 的存在，如果 $k$ 在则段区间内，那么就需要将答案减一。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define int long long
using namespace std;
const int N = 10010;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

signed main(){
	int l1 = read() , r1 = read() , l2 = read() , r2 = read() , k = read();
	if(l1 > r2 || r1 < l2){
		printf("0\n");
		return 0;
	}	
	int L = max(l1,l2);
	int R = min(r1,r2);
	int ans = R - L + 1;
	if(k >= L && k <= R) ans--;
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：PersistentLife (赞：2)

### 提供数据

第 $10$ 个测试点 WA 的可以测一下这个：

[输入](https://www.luogu.com.cn/paste/opjaofun) [输出](https://www.luogu.com.cn/paste/fmy76n8e)

展开源码复制即可。

### 题目分析

这题只要简单的计算即可。

就拿样例 $2$ 来说：

![示意图](https://cdn.luogu.com.cn/upload/image_hosting/1jz9ay2f.png)

我们可以发现，$\max(l_1,l_2)$ 和 $\min(r_1,r_2)$ 组成的闭区间就是他们都有空的时间段。

如果 $k$ 在这个时间段里面，那么答案就减去 $1$。

代码就很好写啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
long long l1,r1,l2,r2,k;
int main()
{
	cin>>l1>>r1>>l2>>r2>>k;
	long long l3=max(l1,l2),r3=min(r1,r2),ans=r3-l3+1;
	if(l3<=k&&k<=r3) ans--;
	cout<<ans;
	return 0;
}
```
交上去，第 $10$ 个点愉快地 WA 了……

程序输出的答案是个负数，那肯定 `long long` 存不下，要用 `unsigned long long`。

~~真是“北冥有题，其名为毒瘤，毒瘤之大，long long 存不下……”~~

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long l1,r1,l2,r2,k;
int main()
{
	cin>>l1>>r1>>l2>>r2>>k;
	unsigned long long l3=max(l1,l2),r3=min(r1,r2),ans=r3-l3+1;
	if(l3<=k&&k<=r3) ans--;
	cout<<ans;
	return 0;
}
```

然后，第 $10$ 个点又愉快地 WA 了……

如果你看到了我提供的数据，那么你肯定会发现，要特判没有重叠的情况，比如我提供的样例：

![示意图2](https://cdn.luogu.com.cn/upload/image_hosting/x2bot0ru.png)

这样输出 $0$ 即可，上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long l1,r1,l2,r2,k;
int main()
{
	cin>>l1>>r1>>l2>>r2>>k;
	if(r1<l2||l1>r2)
	{
		cout<<0;
		return 0;
	}
	unsigned long long l3=max(l1,l2),r3=min(r1,r2),ans=r3-l3+1;
	if(l3<=k&&k<=r3) ans--;
	cout<<ans;
	return 0;
}
```


---

## 作者：Chiaro (赞：2)

###### ~~水题没有题解赶快水一波~~

取左区间(l1,l2)的最大值

再取右区间(r1,r2)的最小值

相减得出可以相遇的时间区间

再判断一下化妆的时间(k)在不在这个区间段里

在 , 总时间就减一

另外 : 这个数据范围成功的引起了我的注意 , 于是我用了unsigned long long

(实际上应该不会爆longlong吧)

#### 代码如下

```cpp
#include<iostream>
#include<cstdio> 
#include<cstring>
#include<queue>
#include<map>
#define sc scanf
#define ll unsigned long long
//使用了unsigned long long
using namespace std;
ll r1,l1,r2,l2,k;
ll max(ll a,ll b){return a>b?a:b;}
ll min(ll a,ll b){return a<b?a:b;}
int main(){
	sc("%llu%llu%llu%llu%llu",&l1,&r1,&l2,&r2,&k);
    //读入
	if(l1>r2||r1<l2){cout<<0<<'\n';return 0;}
    //如果[l1,r1]与[l2,r2]这两个区间没有重合的直接输出0结束
	ll l=max(l1,l2);
	ll r=min(r1,r2);
    //取最大值与最小值
	ll ans=r-l;//相减
	++ans;
    /*
     *可以从样例中看出
     *这个区间的最左面也是要取的
     *但是相减的时候并没有算上最左面
     *所以在这里要+1
     *如果还没有明白可以参考样例
     *就是说实际相遇的时间要比相减的大一
     */
	if(k>=l&&k<=r)--ans;
    //如果在这段时间里要化妆那总时间要-1
	cout<<ans<<'\n';//输出
	return 0;
}
```

---

## 作者：hhh_778899 (赞：1)

## 题目大意

- 给出两个区间 $\lbrack \, l_1 \, , \, r_1 \, \rbrack$ 和 $\lbrack \, l_2 \, , \, r_2 \, \rbrack$ ，同时给出一个不可取的点 $k$ ，求两个区间交集的长度。

## 题目分析

计算交集长度，我们需要分两种情况讨论：

- $\lbrack \, l_1 \, , \, r_1 \, \rbrack$ 和 $\lbrack \, l_2 \, , \, r_2 \, \rbrack$ 无交集：即 $l_2 > r_1$ 或 $l_1 > r_2$ ，此时答案显然为 $0$ 。

- $\lbrack \, l_1 \, , \, r_1 \, \rbrack$ 和 $\lbrack \, l_2 \, , \, r_2 \, \rbrack$ 有交集：显然，此时交集的左边界为 $\max(l_1\,,\,l_2)$ ，右边界为 $\min(r_1\,,\,r_2)$ 。

- 故答案为：
$$ans=\min(r_1\,,\,r_2)-\max(l_1\,,\,l_2)+1$$

- 但以上还不是正确答案，因为我们没有考虑 $k$ 的存在。

- 所以如果 $k$ 在 $\max(l_1\,,\,l_2)$ 和 $\min(r_1\,,\,r_2)$ 之间，再将答案减 $1$ 即可。

## 代码
```cpp
#include <iostream>
using namespace std;

int main()
{
    long long l_1,r_1,l_2,r_2,k;//考虑到本题数据范围，只能开long long
    cin>>l_1>>r_1>>l_2>>r_2>>k;
    if(l_2>r_1||l_1>r_2)
    {
        cout<<"0";
        return 0;
    }
    long long l=max(l_1,l_2),r=min(r_1,r_2);
    if(k>=l&&k<=r)
    {
        cout<<r-l;
    }
    else
    {
        cout<<r-l+1;
    }
    return 0;
}
```


---

## 作者：CharlesZiy (赞：1)

## 写在前面

说实话，本题的难度评蓝实在偏高，评个绿题以下应该差不多。~~但谁会拒绝一道蓝题入账呢？~~

闲言少叙，我们进入主题。

## 思路

为什么说这题简单呢？因为这题不仅是思维还是代码都很简单。

先理解一下题意吧：

- 两个人要见面；
- 第一个人（就是那只猫头鹰）在第 $[l_1, r_1]$ 分钟有空，第二个人（就是那只刺猬）在第 $[l_2, r_2]$ 分钟有空；
- 那只猫头鹰要在第 $k$ 分钟去补个妆。
- 保证 $l_1 \leq r_1$，$l_2 < r_2$。（赞美良心出题人）。

可以发现，这题的题面给的很有提示性（尤其是两个时间用的还是 $l$ 和 $r$）。于是，运用小学数学知识，我们知道算一个区间 $[l, r]$ 的长度是 $l - r + 1$。万事俱备，让我们开始写代码吧。

## 实现

这里我们需要考虑一些细节：

- 如果两个人有空的时间不重合怎么办？（表现为 $l_1 > r_2$ 或者 $l_2 > r_1$）。
- 如果那只猫头鹰需要补妆，怎么办？
- 如果那只猫头鹰在会面前（会面后）才补妆，会怎么样？

对于第一个细节，直接在一开始特判输出 $0$ 即可。

对于第二个细节，将它们能相遇的时间（答案）减 $1$ 即可。

对于第三个细节，那就不用考虑补妆的事了（毕竟对于答案没影响）。

最后，看一眼数据范围：

$1 \leq l_1,  r_11, l_2, r_2 \leq 10^{18}$。

考虑到思路中并未提到要将两个正数变量相加，所以 `long long` 撑得住。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

long long l1, r1, l2, r2, k;

int main()
{
	std::ios::sync_with_stdio(false);
	
	cin >> l1 >> r1 >> l2 >> r2 >> k;
	
	if (l1 > r2 || l2 > r1)
	{
		cout << 0 << endl;
		return 0;
	}
	
	long long l, r, ans = 0;
	l = max(l1, l2);
	r = min(r1, r2);
	ans = r - l + 1;
	
	if (k >= l && k <= r) ans--;
	
	cout << ans << endl;
}
```

本题实属小清新良心练手题之典范。

---

## 作者：zoobidubi (赞：1)

这题我第一眼居然看成了线段树？？？？

好吧来说说这题的正解

首先分析一下这题时间复杂度：O（1）

没错就是O（1）

做这题有三步

1. 因为答案会超long long， 所以我们手打一个min，max函数 
 
2. 算出区间时间长度后要加一

3. 特判一下k有没有在那段时间里，如果有的话就减一

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans;
long long L1, L2, R1, R2, k;
// 一定要开longlong！
long long cmax(long long a, long long b)
//自定义函数max
{
    if (a > b) return a;
    return b;
}
long long cmin(long long a, long long b)
//自定义函数min
{
    if (a < b) return a;
    return b;
}
int main()
{
    cin >> L1 >> R1 >> L2 >> R2 >> k;
    ans =cmin(R1 , R2) - cmax(L1 , L2);//本来是左减右加一的
    //这里先不加一，如果要扣一的话就可以直接输出
    if (k >= cmax(L1, L2) && k <= cmin(R1, R2))
    //如果k在这段能要拜访的时间内
    {
        if (ans < 0) cout << 0 << endl;
        //有可能两段时间没有交集，为负数，就输出0
        else  cout << ans << endl;
        //否则直接输出
    }
    else 
    {
        if (ans < 0) cout << 0 << endl;
        //同上
        else  cout << ans+1 << endl;
        //否则输出加一的结果
    } 
return 0;
}

```


---

## 作者：DPseud (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF714A)

提供一种比较暴力但清奇的思路，比较适合脑子转不过来的人，当然此题坑点还是比较多的：

1. 要开 unsigned long long（没错，long long 都不行）。

2. 有些人容易将 $l1$、$l2$ 与 $l1$、$r1$ 混淆。

3. 要注意逻辑运算符的优先级。

4. $r1<l2$ 且 $l1>r2$ 的这种情况也是会出现的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	unsigned long long l1,r1,l2,r2,k;
	cin>>l1>>r1>>l2>>r2>>k;
	if(r1<l2||l1>r2)cout<<0;//特殊情况
	else if(l1>=l2&&r1<=r2&&k>=l1&&k<=r1)cout<<r1-l1;//包含
	else if(l1>=l2&&r1<=r2&&(k<l1||k>r1))cout<<r1-l1+1;
	else if(l1<l2&&r1<=r2&&k>=l2&&k<=r1)cout<<r1-l2;//重叠
	else if(l1<l2&&r1<=r2&&(k<l2||k>r1))cout<<r1-l2+1;
	else if(l1>=l2&&r1>r2&&k>=l1&&k<=r2)cout<<r2-l1;//也是重叠
	else if(l1>=l2&&r1>r2&&(k<l1||k>r2))cout<<r2-l1+1;
	else if(l1<l2&&r1>r2&&k>=l2&&k<=r2)cout<<r2-l2;//完全包含
	else if(l1<l2&&r1>r2&&(k<l2||k>r2))cout<<r2-l2+1;
	return 0;
}
```


---

## 作者：CH30S (赞：0)

~~最水蓝题~~。

[link](https://www.luogu.com.cn/problem/CF714A)


看起来是一道模拟，但完全不用那么麻烦。

首先观察数据范围，上限是 $10^{18}$，建议开 unsigned long long。

然后找规律，我们这里把相处时间看成一个闭区间，那么就要求出左边界和右边界。

拿样例 2 来说：

1 100 50 200 75

50

![](https://cdn.luogu.com.cn/upload/image_hosting/d08bjk08.png)

如图，可以看出 $\max(l1,l2)$ 和 $ \min(r1,r2)$ 所组成的闭区间就是相处的时间。故答案为 $\max(l1,l2)- \min(r1,r2)+1$

这里建议比较函数自己写，更快。

```c
int maxx(int a,int b){
	if(a>b) return a;
	else return b;
}

int minn(int x,int y){
	if(x<y) return x;
	else return y;
}
```


此外，如果 $k$ 在区间内，那么就需要将答案减一。


最后注意特判，要特判没有重叠的情况。

在 $r 1 < l 2$ 或 $l 1 > r 2$ 时输出 $0$ 即可。


```c
if( r 1 < l 2 || l 1 > r 2 ){
	cout<<0<<endl;
	return 0;
}
```
结束。

鸣谢@Eternal蒟蒻@Dream_weavers 

---

## 作者：_Kouki_ (赞：0)

## 题目大意： 

给您俩个区间 $ [l1,r1] $ 和 $ [l2,r2] $。   
要您求这俩个区间的**重合部分**。   
但需要除去 $ k $。   

实际难度：入门。         

## 题目思路： 

通过模拟样例可以得出 区间**重合部分为:**

- $ \min ( r1 , r2 ) - \max ( l1 , l2 ) $

特别的，如果此段时间包含 $ k $ ,需要将答案 $ -1 $ 。 

## 题目代码：    

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}
ll l1,l2,r1,r2,k,f;
int main()
{
	l1=read();
	r1=read();
	l2=read();
	r2=read();
	k=read();
	if(l1>r2||r1<l2){
		printf("0\n");
	}else{
		if(k>=max(l1,l2)&&k<=min(r1,r2)) f=-1;
		printf("%lld\n",min(r1,r2)-max(l1,l2)+1+f);
	}	
	return 0;
}
```

---

## 作者：V1mnkE (赞：0)

取左区间 $(l1,l2)$ 的最大值

再取右区间 $(r1,r2)$ 的最小值

相减得出可以相遇的时间区间

再判断一下化妆的时间 $k$ 在不在这个区间段里，如果在, 总时间就减一。

记得开 ``unsigned long long`` 。

```
#include<bits/stdc++.h>
using namespace std;
unsigned long long l1,r1,l2,r2,k;
int main()
{
	cin>>l1>>r1>>l2>>r2>>k;
	if(r1<l2 or l1>r2)
	{
		cout<<0;
		return 0;
	}
	unsigned long long l3=max(l1,l2),r3=min(r1,r2),ans=r3-l3+1;
	if(l3<=k&&k<=r3) ans--;
	cout<<ans;
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

## 思路

首先考虑没有 $k$ 这个限制的时候。

那么答案显然是两个区间的交集，即 $\max(l1,l2)$ 到 $\min(r1,r2)$ 这段范围。

如果有了 $k$，其实也很好处理：如果 $k$ 在这个区间的交集内，那么减 1 即可；否则什么都不做就好了。

最后注意一下可能两个区间没有交集，这个时候要输出 0 而不是一个奇怪的负数。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	long long l1,r1,l2,r2,k;
	cin>>l1>>r1>>l2>>r2>>k;
	long long L=max(l1,l2),R=min(r1,r2);
	if(L<=k && k<=R) cout<<R-L+1-1; // 判断 k 是否在两个区间的交集内
	else cout<<max(0ll,R-L+1); // 特判 R<L 的情况
	return 0;
}
```

---

