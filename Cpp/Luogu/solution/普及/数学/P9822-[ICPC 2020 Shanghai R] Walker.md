# [ICPC 2020 Shanghai R] Walker

## 题目描述

As a world-famous traveler, Prof. Pang's research interest is to travel as many places as possible in his life.

We have a segment $[0, n]$. There are two travelers on it. The first one is on position $p_1$ with velocity $v_1$ (which means s/he can walk $v_1$ unit on the segment per second). The second one is on position $p_2$ with velocity $v_2$.

From their respective beginning points, travelers can walk on the segment. They cannot walk outside the segment. Whenever they want to change their direction, they can turn around immediately.

Please help Prof. Pang to calculate the minimum  possible time by which every position of the segment is passed by at least one traveler.

## 样例 #1

### 输入

```
2
10000.0 1.0 0.001 9999.0 0.001
4306.063 4079.874 0.607 1033.423 0.847```

### 输出

```
5001000.0000000000
3827.8370013755```

# 题解

## 作者：wylnh (赞：7)

**做法**：**模拟**+**贪心**

**题意**：在一条长为 $n$ 的路上，有两人分别位于 $p_1,p_2$，速度分别为 $v_1,v_2$ ，求最少多长时间两人走完整条路，即**每个位置至少有一人经过**。

**思路**：
- 容易发现走完全程共有三种情况：
  - 一个人走完全程；
  - 两人相向而行，相遇走完全程；
  - 两人各自负责走完一边，最终相遇于中间一点。
- 对于第①种情况：
  - 选择一个人向**更近**的一端点走，然后折返走完全程：```ans=min(ans,min((n+min(n-p1,p1))/v1,(n+min(n-p2,p2))/v2))```。
- 对于第②种情况：
  - 计算每个人各自走到端点的**较大时间**：```ans=min(ans,max((n-p1)/v1,p2/v2))```。
- 对于第③种情况：
  - 两种选择，考虑**二分答案**，二分两人最终相遇的点的位置，计算所需的最短时间。
  - 此过程中，计算左边的人所走的时间：```t1=(mid+min(mid-p1,p1))/v1```，右边的人所走的时间：```t2=(n-mid+min(n-p2,p2-mid))/v2```。如果 $t1<t2$，那么说明可以向**右端**收缩，每次更新答案```ans=min(ans,max(t1,t2))```。
- 注意：
  - 题意精确到 $1\times 10^{-6}$ ，但实际应精确到 $1\times 10^{-7}$ 。~~（别问我为什么）~~
  - 若 $p_1<p_2$，则**交换** $p_1,p_2$ 与 $v_1,v_2$，使得从左到右保证**从小到大**。

**代码**：
```c
#include<bits/stdc++.h>
using namespace std;
const double eps=1e-7,INF=1e9;
int T;
double n,p1,p2,v1,v2;
int main(){
    cin>>T;
    while(T--){
    	cin>>n>>p1>>v1>>p2>>v2;
    	if(p1>p2){//交换
    		swap(p1,p2);
    		swap(v1,v2);
    	}
    	double ans=INF;
		ans=min(ans,min((n+min(n-p1,p1))/v1,(n+min(n-p2,p2))/v2));//第①种情况
		ans=min(ans,max((n-p1)/v1,p2/v2));//第②种情况
		double l=p1,r=p2;
		while(r-l>eps){
			double mid=(l+r)/2;
			double t1=(mid+min(mid-p1,p1))/v1;//左边
			double t2=(n-mid+min(n-p2,p2-mid))/v2;//右边
            ans=min(ans,max(t1,t2));//更新答案
			if(t1<t2)
				l=mid;
			else
				r=mid;
		}
		printf("%.10f\n",ans);
	}
    
    return 0;
}
```

**后记**：如有错误或不足请  _dalao_  指出。（~~点个![/z](https://cdn.luogu.com.cn/upload/pic/62236.png)再走呀！~~）

---

## 作者：佬头 (赞：4)

## Description
在一条 $[0,n]$ 的线段上有两名[**旅行者**](https://www.luogu.com.cn/problem/P9822) $A,B$，$A$ 从 $p_1$ 开始以每秒 $v_1$ 单位的速度运动，$B$ 从 $p_2$ 开始以每秒 $v_2$ 单位的速度运动，并且可以随时改变运动方向。请计算出至少需要多少时间，才能使得线段上的每个位置都至少被一名旅行者经过。

## Description
不难想到有三种情况（为了方便讨论，我们设 $p_1\le p_2$）：
- $A(B)$ 独自走完全程，原因是 $B(A)$ 走得实在太慢。
- $A$ 向右走到底，$B$ 向左走到底，两人所花的时间取一个最大值。
- $A$ 走完左边的一段区间，$B$ 走完右边的一段区间（两段区间的连接点在 $[p_1,p_2]$ 内），然后对两人所花的时间取一个最大值。我们钦定这个连接点为 $P$，显然他们**各自**有**两种走法**：
	+ 先走到 $P$，再走向边界。
	+ 先走到边界，在走向 $P$。

  不难发现，$A,B$ 的走法互相之间没有影响，不一定全部都要采用同一种走法，只要各自走最优的就行。同时随着 $P$ 位置的变化，不仅花费的时间会变，他们各自采用的走法也会有所变化，那就不可以简单地将总路程除以总时间再特判一下草草了事。~~我一开始还以为直接分类讨论一下就可以了。~~ 
  
  不过可以肯定的是，随着 $P$ 的不断右移，不管 $A$ 采用什么走法，他所花的时间都是**单调递增**的（总不能我走的路程多了，花的时间反而少了吧）；$B$ 也同理。
  
  同时又想到**花费时间可能偏多的本质**是 $A,B$ 其中一人在走完自己的区间后另一人还未走完，那么这个人明显可以再多走一点。因此我们考虑**二分**出一个 $P$，使得花费时间最少，即两人恰好走完自己的区间。

最后的答案就在这三种情况里取一个最小值即可。代码时间复杂度 $\mathcal O(T\log P)~(P=10^{11})$。

不得不说这是一道很巧妙的二分题。

## Code
```cpp
#include <iostream>
using namespace std;
double n, p, v, pp, vv, ans, mid;
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
bool check(){
	double t = (min(mid - p, p) + mid) / v, tt = (min(pp - mid, n - pp) + n - mid) / vv;
	if(t < tt){
		if(tt < ans) ans = tt;
		return 1;
	}
	if(t < ans) ans = t;
	return 0;
}
int main(){
	for(int _ = read(); _ >= 1; _ --){
		scanf("%lf%lf%lf%lf%lf", &n, &p, &v, &pp, &vv);
		if(p > pp) swap(p, pp), swap(v, vv);
		ans = min((min(p, n - p) + n) / v, (min(pp, n - pp) + n) / vv); //一人走完
		ans = min(ans, max((n - p) / v, pp / vv)); //互相穿过
		double lft = p, rt = pp;
		while(rt - lft >= 0.0000001){
			mid = (lft + rt) / 2;
			if(check()) lft = mid + 0.0000001;
			else rt = mid - 0.0000001;
		}
		printf("%.6f\n", ans);
	}
	return 0;
}
```


---

## 作者：keepwatcher_kensap (赞：2)

## Part 1 题意

在一个 $[0,n]$ 的区间中为两个旅行者，两个旅行者的初始位置和移动速度分别为 $p1,v1,p2,v2$，求出两个旅行者将整个区间的每一个点都走过所需的最短时间。

## Part 2 思路

既然是要求最优情况，那就要尽量让旅行者的覆盖情况最优。我们假设两个旅行者的编号为 $x,y$，则初始状况就是：

```
0——————x———————————y————————n
```

最简单的一种想法，我们令旅行者 $x$ 走到 $n$，令旅行者 $y$ 走到 $0$，这样就可以确保整个区间都被覆盖，走法如下：

```
        --------(x)-------->
0——————x———————————y————————n
 <-------(y)-------
```

这种情况下，我们所需的时间满足：

- $time=\max(\frac{n-p1}{v1},\frac{p2}{v2})$。

其次，我们也可以让其中一个旅行者单独走完全程，即：

```
情况一：
 <---------(x1)-------------
        -------(x1)-------->
0——————x———————————y————————n
情况二：
 ------------(x2)---------->
 <-(x2)
0——————x———————————y————————n
情况三：
0——————x———————————y————————n
 <-------(y1)------
 ------------(y1)---------->
情况四：
0——————x———————————y————————n
                    -(y2)-->
 <----------(y2)------------
```

此时，我们所需要的时间就是：

- $time=\min(\frac{\min(p1,n-p1)+n}{v1},\frac{\min(p2,n-p2)+n}{v2})$。

最后一种情况，就是两个旅行者以一点 $mid$ 为中点，格子走完中点两边的路程：

```
其中一种情况：
 ----(x)--->
 <--
0———x———————mid——————y——————n
               <-----
               -----(y)---->
```

我们令 $l$ 为上图旅行者 $x$ 所需的时间，$r$ 为上图旅行者 $y$ 所需的时间，满足：

- $l=\frac{\min(p1,mid-p1)+mid}{v1}$。

- $r=\frac{\min(p2-mid,n-p2)+n-mid}{v2}$。

则此时我们所需的时间满足：

- $time=\max(l,r)$。

对于上文中的 $mid$，我们可以使用**二分**的方式进行枚举。初始的时候，我们只需区间 $[p1,p2]$ 中查找。

不难发现，如果我们在令 $time$ 尽量小，那我们就要尽量让 $l$ 和 $r$ 接近。对于每次算出来的 $l,r$，如果 $l>r$，也就是旅行者 $x$ 的用时更长，我们要让旅行者 $x$ 的用时缩短，所以把搜索的区间降到 $[left,mid]$ 中，反之则是 $[mid,right]$。这样子有助于我们将两个旅行者的用时尽可能的拉近。

温馨提示：虽然题目要求的是误差小于 $10^{-6}$，但我们在二分的时候最好精确到 $10^{-7}$ 甚至更精确，以免出现悲剧。

## Part 3 代码

```
#include <bits/stdc++.h>
using namespace std;
double n,p1,p2,v1,v2;
int main()
{
	int t;cin>>t;while (t--)
	{
		cin>>n>>p1>>v1>>p2>>v2;
		if (p1>p2) swap(p1,p2),swap(v1,v2);
		double result=1e9;
		result=min(result,min((min(p1,n-p1)+n)/v1,(min(p2,n-p2)+n)/v2));
		result=min(result,max((n-p1)/v1,p2/v2));
		double left=p1,right=p2;
		while (left+0.0000001<right)
		{
			double mid=left+(right-left)/2;
			double s1=(min(p1,mid-p1)+mid)/v1;
			double s2=(min(n-p2,p2-mid)+n-mid)/v2;
			result=min(result,max(s1,s2));
			if (s1>s2) right=mid-0.0000001;
			else left=mid+0.0000001;
		}
		printf("%.10lf\n",result);
	}
	return 0;
}
```

---

## 作者：chen_zhe (赞：1)

以下内容转载自官方题解：

大概来说，我们可以分几类来考虑这个问题：
1. 一个人把所有地方走完；
2. 两个人对穿，也就是说他们互相往另一个人的方向走，直到边界；
3. 两个人各负责自己的一边，然后在中间相遇，那么对于每个人，有两种选择，一种是先往端点走，一种是先往中间走，那么我们可以二分时间，就能够算出每个人往中间最多能走多少路，判断一下能不能把线段覆盖了就行啦！

---

## 作者：liguangjun2023 (赞：0)

#### 解题思路
共有三种情况：
1. 两个人相向而行，走到端点；
2. 一个人走完全程；
3. 每个人负责走完自己一侧，相遇在中间某一点；

对于第一种和第二种情况，相遇时间通过数学公式直接计算得到。对于第三种情况，用二分浮点算法，枚举相遇的中间点位置，按照精度控制计算结果即可。

---


```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
double n,pa,va,pb,vb; 
//二分浮点，枚举相遇的中间位置
double bsch(){
	double lef=pa,rig=pb,ans=0x3f3f3f3f;
	while(rig-lef>1e-10){
		double mid=(lef+rig)/2;
		double ta=(mid+min(mid-pa,pa))/va;
		double tb=(n-mid+min(pb-mid,n-pb))/vb;
		ans=min(ans,max(ta,tb));
		if(ta<tb)	lef=mid;
		else		rig=mid;
	}
	return ans;
}

int main(){	
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
		scanf("%lf %lf %lf %lf %lf",&n,&pa,&va,&pb,&vb);
		if(pa>pb){
			swap(pa,pb),	swap(va,vb);
		}
		double ans=0;
    //三种情况打擂台得到最小值
		ans=max((n-pa)/va,pb/vb);
		ans=min(ans,min((n+min(n-pa,pa))/va,(n+min(n-pb,pb))/vb));
		ans=min(ans,bsch());
		printf("%.10lf\n",ans);
	}
	return 0;
}
```

---

## 作者：cfkk (赞：0)

可以分成三种情况（以下令 $p_1<p_2$）：
1. $\rm A$ 或 $\rm B$ 独自走完全程，则花费的时间为

$$t=\min(\dfrac{n+\min(n-p_1,p_1)}{v_1},\dfrac{n+\min(n-p_2,p_2)}{v_2})$$
2. $\rm A$ 和 $\rm B$ 分别走到各自端点，则花费的时间为  

$$t=\max(\dfrac{n-p_1}{v_1},\dfrac{p_2}{v_2})$$
3. $\rm A$ 和 $\rm B$ 分别走到端点然后一起走到中间，则花费的时间为（设中点为 $mid$） 
$$t=\max(\dfrac{mid+\min(mid-p_1,p_1)}{v_1},\dfrac{n-mid+\min(n-p_2,p_2-mid)}{v_2})$$

第三种情况明显可以用二分寻找中点。

所以本体可以将所有情况列举一遍，然后寻找最短用时。

代码：

```cpp
signed main()
{
    int T=read();
    while(T--)
    {
        double n,p1,v1,p2,v2;
        cin>>n>>p1>>v1>>p2>>v2;
        if(p1>p2)swap(p1,p2),swap(v1,v2);
        double cnt=min((n+min(n-p1,p1))*1.0/v1,(n+min(n-p2,p2))*1.0/v2);
		cnt=min(cnt,max((n-p1)*1.0/v1,p2*1.0/v2));
		double l=p1,r=p2;
		while(r-l>=0.0000001)
        {
			double mid=(l+r)/2;
			double cnt1=(mid+min(mid-p1,p1))*1.0/v1;
			double cnt2=(n-mid+min(n-p2,p2-mid))*1.0/v2;
			if(cnt1<cnt2)l=mid,cnt=min(cnt,cnt2);
			else r=mid,cnt=min(cnt,cnt1);
		}
		printf("%.6f\n",cnt);
    }
    return 0;
}

```

---

## 作者：Hanrui1206 (赞：0)

## 题目大意：

在长度为 $n$ 的数轴上给出两个人的初始位置和速度，问使得每个位置至少被一个人走过的时间是多少

## 题目分析：

分类讨论题目，分四种情况讨论即可，设 $p1 < p2$：

1. $p1$ 走完全程
2. $p2$ 走完全程
3. $p1$ 向右走，$p2$ 向左走
4. $p1$ 向左走，$p2$ 向右走，最后共同走完 $p1 \sim p2$ 这段区间

前三种都可以推出公式快速得出，对于第四种需要二分确定答案，可以二分断点位置 $x$，这样问题就变成了：$p1$ 走完 $[0, x]$ 这段区间，$p2$ 走完 $[x, n]$ 这段区间，类比于前三种情况贪心去讨论就好了

## 特别注意：

为了避免二分被卡精度，可以计算一下时间复杂度将 `while` 改成 `for` 即可。

---

## 作者：niuzh (赞：0)

### 思路

将本题分成 $3$ 可能是最优的情况来考虑（设 $p_1\le p_2$）：

1. $a$ 或 $b$ 一个人独自走完全长。此时答案为 $\min(\frac{(\min(p_1,n-p_1)+n}{v_1},\frac{(\min(p_2,n-p_2)+n}{v_2})$。

1. $a$ 向右走到底，$b$ 向左走到底，两人时间取最大值。此时答案为 $\max(\frac{n-p_1}{v_1},\frac{p_2}{v_2})$。

1. 我们取一个点 $t$ 在 $[p_1,p_2]$ 内，让 $a$ 走完 $[0,t]$，让 $b$ 走完 $[t+1,n]$。此时再取 $a$ 所花时间的最小值与 $b$ 所花时间的最小值的最大值。确定点 $t$ 后答案为 $\max(\frac{(\min(p_1,t-p_1)+t}{v_1},\frac{(\min(p_2-t,n-p_2)+(n-t)}{v_2})$。而此时是要找确定点 $t$ 后答案的最小值，求的答案中的两个值是线性的，所以可以用二分。

最后在三个答案中取最小即可。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while (t--)
	{
		double n,p1,v1,p2,v2;
		cin>>n>>p1>>v1>>p2>>v2;
		if (p1>p2)//让p1<=p2
		{
			swap(p1,p2);
			swap(v1,v2);
		}
		double ans=min(min((min(p1,n-p1)+n)/v1,(min(p2,n-p2)+n)/v2),max((n-p1)/v1),p2/v2);//前两种答案的最小值
		double l=p1,r=p2;
		while (r-l>=0.0000001)//使用二分找点t
		{
			double mid=(l+r)/2;
			double t1=(min(mid-p1,p1)+mid)/v1,t2=(min(p2-mid,n-p2)+n-mid)/v2;//a和b分别的同时
			if (max(t1,t2)==t1)//b更慢
			{
				ans=min(ans,t1);//更新最小值
				r=mid-0.0000001;//b慢a快，向右找已平衡
			}
			else//a更慢
			{
				ans=min(ans,t2);//更新最小值
				l=mid+0.0000001;//a慢b快，向最找已平衡
			}
		}
		cout<<fixed<<setprecision(10)<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：SICKO (赞：0)

~~如果标签里没有二分的话，可能蒟蒻 Sicko 我真的会讨论完所有情况~~ 

这是个分类讨论题，首先我们按照完成人数讨论，再讨论多人时每个人各自的方向即可。

首先是单人完成，对于单人完成的情况，我们选取单人完成所需最短路径，然后除以速度算出时间即可。

对于双人完成，首先是两个人相向的情况，计算得出用时较大者即可。而剩下的情况比较复杂，因为旅行者可以同时做出不同的抉择，他们可以**先远离边界再到达边界**，也可以反过来**先到达边界再远离边界**。所以我们可以直接在一个区间二分查找一个最佳分配点，使两者最大完成时间尽可能的小。

怎么确定这个区间呢？首先这个分配点不能出现在区间的外面；其次这个分配点也不能出现在区间边界与较近的旅行者中间，这会使得旅行者被迫完成不属于自己的份额。

所以结果很明显，这个区间是两个旅行者的中间，我们只需在这个区间二分查找即可

最后附上代码

```c++
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);  // 取消同步流加快输入输出
    int t; cin>>t;  // 测试样例数量
    while(t--)
    {
        double n, p1, v1, p2, v2;
        cin>>n>>p1>>v1>>p2>>v2;
        if(p1 > p2)
        {
            swap(p1, p2); swap(v1, v2);
        }  // 确保大小顺序合理
        double res;
        // p1 走完全程
        res = (min(p1, n - p1) + n) / v1;
        // p2 走完全程
        res = min(res, (min(p2, n - p2) + n) / v2);
        // 两个人相向完成全程
        res = min(res, max(p2 / v2, (n - p1) / v1));
        // 以 mid 为分界，各自完成自己的那一份
        double lt = p1, rt = p2;
        for(int i=0; i<=100; i++)  // 利用进行一百次二分足够小来进行卡常
        {  // 二分模板
            double mid = (lt + rt) / 2.0;
            double res1 = (min(mid - p1, p1)+mid) / v1;
            double res2 = (min(n-p2, p2-mid)+n-mid) / v2;
            res = min(res, max(res1, res2));
            if (res1 < res2) lt = mid;
            else rt = mid;
        }
        cout << setiosflags(ios::fixed);
        cout << setprecision(10) << res << "\n";  // 确保精度
    }
    return 0;
}
```

---

## 作者：0x282e202e2029 (赞：0)

## 题目描述

给定 $2$ 个旅行者，分别在初始位置 $p_1$ 速度为 $v_1$，及初始位置 $p_2$ 速度为 $v_2$ 开始运动，求最少要多长时间才能走遍 $[0, n]$。

输入格式：$n \space p_1 \space v_1 \space p_2 \space v_2$（为什么没翻译出来，建议补充）。

## 思路

按照贪心思路分类讨论。易发现二者地位相同，以下讨论默认 $p_1 \le p_2$，即旅行者一初始位置坐标更小。

第 Ⅰ 类：单独一个旅行者走全程 $[0, n]$。

不难推出此类答案为 $\min(\frac{\min(p_1, n - p_1) + n}{v_1}, \frac{\min(p_2, n - p_2) + n}{v_2})$。

第 Ⅱ 类：旅行者一向右走 $[p_1, n]$，旅行者二向左走 $[0, p_2]$。

注意此时时间以用时较长为准，因此此类答案为 $\max(\frac{n - p_1}{v_1}, \frac{p_2}{v_2})$。

第 Ⅲ 类：找一个中点 $p$ 满足 $p_1 \le p \le p_2$，旅行者一走 $[0, p]$，旅行者二走 $[p, n]$。

此时旅行者一的用时为 $\frac{\min(p_1, p - p_1) + p}{v_1}$，旅行者二的用时为 $\frac{\min(p_2 - p, n - p_2) + (n - p)}{ v_2}$，即先去两端点中较近的，再走遍全程。我们运用二分的方法，在二分最优 $p$ 的时候更新答案即可。

## AC 代码

```cpp
#include <cstdio>
#include <cmath>
#include <algorithm> 
using namespace std;
const double eps = 1e-8;
int T;
double n, p1, v1, p2, v2;
double ans;
bool check(double p) {
	double t1 = (min(p1, p - p1) + p) / v1, t2 = (min(p2 - p, n - p2) + (n - p)) / v2;
    ans = min(ans, max(t1, t2)); // 更新答案 
	return t1 < t2;
}
void solve() {
    double l = p1, r = p2;
    while (r - l > eps) { // 精度二分
        double mid = (l + r) / 2;
        if (check(mid)) { // 旅行者 1 先到达会合点 
           l = mid; // 更优解在右侧 
		} else {
           r = mid; // 反之最优解在左侧
		}
    }
} // 二分，并用 check() 更新 ans 
int main() {
    scanf("%d", &T);
    while (T--) {
    	scanf("%lf%lf%lf%lf%lf", &n, &p1, &v1, &p2, &v2);
    	if (p1 > p2) {
    		swap(p1, p2), swap(v1, v2);
		} // 让 p1 ≤ p2
        ans = min((min(p1, n - p1) + n) / v1, (min(p2, n - p2) + n) / v2); // 情况 1
        ans = min(ans, max((n - p1) / v1, p2 / v2)); // 情况 2
        solve(); // 情况 3
        printf("%.10f\n", ans); // 格式输出
    }
    return 0;
}
```

---

## 作者：sfqxx1 (赞：0)

一篇 python 题解。

## 题意

有一个数轴，数轴上有两个人，位置和速度为 $v_1$，$v_2$，$p_2$，$v_2$，求出两人路程和能够覆盖数轴的最小时间。

## 思路
一共有四种情况（我们假设 $p_1$ $\le$ $p_2$）:

1. $p_1$ 与 $p_2$ 相向而行。

2. $p_1$ 走完全程。

3. $p_2$ 走完全程。

4. $p_1$ 与 $p_2$ 相背而行，最后走完 $p_1-p_2$，或者先走完 $p_1-p_2$，再走完 $p_1$ 和 $p_2$。

前三种都可以容易的推出结论，那么第四种该怎么办呢？

我们可以考虑两人在哪里相遇，即考虑是先相遇还是后相遇，相遇的点必然在 $p_1$ 和 $p_2$ 之间，在这个区间内二分求得相遇点即可。

## 代码

```

def sgn(x):#精度
    eps = 1e-10
    if abs(x) <= eps:
        return 0
    elif x < 0:
        return -1
    else:
        return 1

def slove():
        n, p1, v1, p2, v2 = map(float, input().split())
        if sgn(p1 - p2) > 0:
            p1, p2 = p2, p1
            v1, v2 = v2, v1
        ans = 1e10
        ans = min(ans, max((n - p1) / v1, p2 / v2))  
        ans = min(ans, (min(n - p1, p1) + n) / v1)  # p1 走完全程
        ans = min(ans, (min(n - p2, p2) + n) / v2)  # p2 走完全程
        l, r = p1, p2

        def check(p):
            nonlocal ans
            t1 = (min(p - p1, p1) + p) / v1
            t2 = (min(p2 - p, n - p2) + (n - p)) / v2
            ans = min(ans, max(t1, t2))
            return sgn(t1 - t2) < 0

        for _ in range(1000): 
            mid = (l + r) / 2
            if check(mid):  
                l = mid 
            else:
                r = mid
        print("%.10f" % ans)

w = int(input().strip())
for _ in range(w):
    slove()
```

---

## 作者：abc1856896 (赞：0)

# 题目大意
在一条 $[0,n]$ 的线段上有两名旅行者，第一名在位置 $p_1$ 以 $v_1$（每秒钟可以走 $v_1$ 单位的距离）的速度开始运动，第二名在位置 $p_2$ 以 $v_2$ 的速度开始运动。

从他们分别的起始点出发，旅行者可以在线段上移动，但不可以走出线段。他们可以随时改变自己的方向。

请计算至少需要多少时间，线段上的每个位置都至少被一名旅行者经过。

# 大体思路
一共有四种情况 $(p_1<p_2)$。

1.  $p_1$ 与 $p_2$ 相向而行，走到终点。
2.  $p_1$ 走完全程。
3.  $p_2$ 走完全程。
4.  $p_1$ 与 $p_2$ 相背而行，最后走完 $p_1-p_2$，或者先走完 $p_1-p_2$，再走完 $p_1$ 和 $p_2$。

~~根据小学数学我们可以得到~~

对于第 $1$ 种情况

$ans=\max((n-p_1)/v_1,p_2/v_2)$

对于第 $2$ 和第 $3$ 种情况

$ans=\min((\min(p_1,n-p_1)+n)/v1,(\min(p_2,n-p_2)+n)/v_2)$

对于第 $4$ 种情况

需要考虑两人在哪里相遇，即考虑是先相遇还是后相遇，相遇的点必然在 $p_1$ 和 $p_2$ 之间，在这个区间内二分求得相遇点即可。

# 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
const double p=1e-7;
double n,p1,v1,p2,v2,ans;//注意double 
int t;
bool check(double k){
	double t1=v1*k;//情况1 
	double t2=v2*k;//情况2
	double t3=max(t1-p1*2,(t1-p1)/2);//情况3
	double t4=max((t2-(n-p2))/2,(t2-(n-p2)*2));//情况4
	if((t4+t3)>=p2-p1) return true;
	else return false;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>p1>>v1>>p2>>v2;
		if(p1>p2) {
			swap(p1,p2);
			swap(v1,v2);
		}		
		ans=0x3f3f3f3f;//初始化 
		ans=min(ans,max((p2/v2),(n-p1)/v1));
		ans=min(ans,min((p1+n)/v1,(n-p1+n)/v1));
		ans=min(ans,min((p2+n)/v2,(n-p2+n)/v2));
		double l=max(p1/v1,(n-p2)/v2),r=ans;//左右边界 
		while(fabs(r-l)>p){//二分 
			double mid=(r+l)*1.0/2;//注意 乘以1.0！！！ 
			if(check(mid)){
				r=mid;
				ans=min(ans,mid);
			}
			else l=mid;
		}
		printf("%.8lf\n",ans);
	}
	return 0;
}
```


---

