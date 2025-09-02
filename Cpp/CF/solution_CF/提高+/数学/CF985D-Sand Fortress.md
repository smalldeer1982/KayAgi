# Sand Fortress

## 题目描述

You are going to the beach with the idea to build the greatest sand castle ever in your head! The beach is not as three-dimensional as you could have imagined, it can be decribed as a line of spots to pile up sand pillars. Spots are numbered $ 1 $ through infinity from left to right.

Obviously, there is not enough sand on the beach, so you brought $ n $ packs of sand with you. Let height $ h_{i} $ of the sand pillar on some spot $ i $ be the number of sand packs you spent on it. You can't split a sand pack to multiple pillars, all the sand from it should go to a single one. There is a fence of height equal to the height of pillar with $ H $ sand packs to the left of the first spot and you should prevent sand from going over it.

Finally you ended up with the following conditions to building the castle:

- $ h_{1}<=H $ : no sand from the leftmost spot should go over the fence;
- For any ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985D/77d67b6184b30d84bfc3e3e2794dc8de9b20fcf2.png) $ |h_{i}-h_{i+1}|<=1 $ : large difference in heights of two neighboring pillars can lead sand to fall down from the higher one to the lower, you really don't want this to happen;
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985D/7c65b11667de38fcb78de5945051b7b0879e1abf.png): you want to spend all the sand you brought with you.

As you have infinite spots to build, it is always possible to come up with some valid castle structure. Though you want the castle to be as compact as possible.

Your task is to calculate the minimum number of spots you can occupy so that all the aforementioned conditions hold.

## 说明/提示

Here are the heights of some valid castles:

- $ n=5,H=2,[2,2,1,0,...],[2,1,1,1,0,...],[1,0,1,2,1,0,...] $
- $ n=6,H=8,[3,2,1,0,...],[2,2,1,1,0,...],[0,1,0,1,2,1,1,0...] $ (this one has $ 5 $ spots occupied)

The first list for both cases is the optimal answer, $ 3 $ spots are occupied in them.

And here are some invalid ones:

- $ n=5,H=2,[3,2,0,...],[2,3,0,...],[1,0,2,2,...] $
- $ n=6,H=8,[2,2,2,0,...],[6,0,...],[1,4,1,0...],[2,2,1,0,...] $

## 样例 #1

### 输入

```
5 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
6 8
```

### 输出

```
3
```

# 题解

## 作者：___new2zy___ (赞：27)

## 题解 CF985D 【Sand Fortress】

题目传送门：

https://www.luogu.org/problemnew/show/CF985D

笔者语：这题是一道**二分答案**脑洞题

（请爱惜这篇题解，这是本人熬到深夜打出来的）

再次笔者真的希望能帮到大家

============================================

#### 题面翻译：

你有**n袋沙子**，你需要用沙子堆一面墙，

**沙子必须摆放在整数的位置**，而且

**最左边已经有一面高为h袋沙子的墙了，**

所以，**最左边的沙子的袋数不能大于h，**

**相邻的两个点上堆放的沙子袋数相差不能超过1**

问，怎样堆放才能**使沙子的堆数最小**。

~~（接下来自己BB）~~

看了这题感到有点蒙~~（找不着北）~~

没关系，我们接下来分析本题

============================================

#### 思路&&算法分析：

~~（我要是说显然这题是二分答案你们会打我么= =）~~

对于此题，我们要满足题目中给的3个要求如下:

1.**第一个沙堆的高度不能超过h**

2.**任意两根**沙堆的高度差不能超过1

（即**最后一个沙堆高度一定为1**）

3.沙墙的**所有沙堆消耗的沙袋总数为n**


============================================

从题目意思可以发现这里**分为3种情况**:

（h代表最左端沙堆高度，k代表每一堆沙子的高度）

	 （若K<=h）

	 1.第一种这么堆:
      K,K-1，K-2,...,2,1  
     	其中 ∑ == n;

	 (若K>h)

 	2.第二种这么堆:
      K,K+1,..,K+x-1,K+x,K+x-1,...,K,K-1,...,2,1 
    	 其中 ∑ == n;

	 3.第三种这么堆：
      K,K+1,..,K+x-1,K+x,K+x,K+x-1,..,K,K-1,..,2,1 
     	其中 ∑ == n;

这时我们不妨假设一个沙堆数k，此时我们

不难发现，堆出的沙堆高度有以下两种情况，

①从h到1的单调递减的数列（如上面的1）

显然此时总沙堆数为  k*(k+1)/2

②从h先单调递增到一个max，然后单调递减的数列
（如上面的2,3）

（插入一句话）

**请注意**:在以下②③情况中**设能堆的沙堆的最大高度 **

**H=（k-h）/2+h**（因为这样才能保证沙堆数最少）

（下面继续正文）

但其实②情况**对于高出最左边h的高度**分为两种，

第一种是下面这样：

奇数情况：（上面的3）出现**两个并列最大值**

![](https://images2018.cnblogs.com/blog/1168200/201805/1168200-20180522121337955-1890891751.png)

这里**前半部分**有H-h+1个沙堆，**后半部分**直接等差数列求和即可：H*（H+1）

那么此时的**总沙堆数**为：(H+h) *(H-h+1)/2 + H*(H+1) /2

另一种是下面这样：

偶数情况：（上面的2）出现**单峰最大值**

![](https://images2018.cnblogs.com/blog/1168200/201805/1168200-20180522121344855-1204689348.png)

那么这里：**前半部分**H-h个沙堆，**后半部分**仍然是等差数列求和：H*（H+1）

那么此时的**总沙堆数**为(H-1+h)*(H-h)/2 + H*(H+1)/2

对于以上三种情况，只需判断是否这个k值合法即可

那么这个**答案显然是具有单调性**的（证明略）

由于考虑到要找**最少的堆**数目，我们可以使用**二分答案**，用**二分**来枚举沙堆堆数，检查这个堆数是否合法

**二分答案缩小范围的判定**：**堆k个沙堆所能堆出的沙墙使用沙袋的数目是否大于等于给出的n**，

若可行说明我们可以尝试缩小范围，得到更小堆得数目从而求得题目要的**最小值**

思路大体就是这样，~~其实不是很难~~~~（我推了一上午）~~

注意，**乘法会爆int**，笔者的代码里使用了long long

因此，我加了一个INF，如果计算出的沙堆数>=INF直接返回1（顶尖数据范围能达到那么一定是可行的）

之后就是注意等差数列求和的公式，别记错了

数学公式左边除以2可以转变为右边乘以2，实在不行就手推吧（本人也是爱莫能助啊）

接下来发代码，里面也有解释，应该会更详细一些

（本人太弱，可能讲的不是太好，dalao们不喜勿喷）

    #include<iostream>
    #include<cstdio>
    #include<cmath>
    #include<algorithm>
    using namespace std;
    typedef long long ll;
    inline ll read()
    {
        ll p=0,f=1;char c=getchar();
        while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
        return 1ll*f*p;}
    const ll inf=2000000000;
    ll n,h;
    inline bool check(ll k)
    //判断mid值是否可行,即判断所用的沙袋数最大值是否超过n
    {
        if(k<=h)
            {
                //1.如果分的堆数k<=h:直接等差数列求和
        	    if(k>=inf) return 1;
       	 	    return k*(k+1)/2>=n;
    	    }
        //以下对应k>h的情况
        ll H=(k-h)/2+h;//先求出要堆的沙堆的最大高度
        if(H>=inf)return 1;
        if((k-h)&1)//k-h为高出的高度
        //2.如果高出的高度为奇数则有两个最高点,前后两次求和
            return (H+h)*(H-h+1) + H*(H+1) >= (n<<1);
        //3.如果高出的高度为偶数则只有一个最高点,前后两次求和
        return (H-1+h)*(H-h) + H*(H+1) >= (n<<1);
    }
    int main()
    {
        n=read(),h=read();
        ll l=1,r=n,mid;
        //接下来二分答案
        while(l<=r)
            {
        	    mid=(l+r)>>1;
        	    if(check(mid))
                //二分出一个mid值进行判定
                	r=mid-1;
        	    else l=mid+1;
    	    }
        printf("%lld",r+1);
        return 0;
    }

好啦，以上就是本题的全解了，希望能帮到大家

最后推广一下我的博客：

https://www.luogu.org/blog/new2zy/

感谢阅读~~~拜拜>=<


---

## 作者：cff_0102 (赞：15)

最后的沙堆可以有两种形态：

![](https://cdn.luogu.com.cn/upload/image_hosting/cg58e5rx.png)

其中，很明显的，第一种形态比第二种在沙袋堆数相同的情况下沙袋总数更多，所以在沙袋总数相同时沙袋堆数更少。所以要尽量的选择形态 $1$。

当 $\frac{H(H+1)}{2}+2H\ge n$ 时选择形态 $1$，否则选择形态 $2$，是更优的。

- $\frac{H(H+1)}{2}\ge n$ 时，答案是最小的 $x$ 使得 $\frac{x(x+1)}{2}\ge n$，解这个方程即可。
- $\frac{H(H+1)}{2}<n$ 但 $\frac{H(H+1)}{2}+2H\ge n$ 时，选择形态 $1$，此时当 $\frac{H(H+1)}{2}+H\ge n$ 时答案是 $H+1$，当 $\frac{H(H+1)}{2}+H<n$ 时答案是 $H+2$。
- $\frac{H(H+1)}{2}+2H<n$ 时，选择形态 $2$。
   - $\frac{H(H+1)}{2}+H+(H+1)\ge n$ 时，答案是 $H+2$。
   - $\frac{H(H+1)}{2}+H+2(H+1)\ge n$ 时，答案是 $H+3$。
   - $\frac{H(H+1)}{2}+H+2(H+1)+(H+2)\ge n$ 时，答案是 $H+4$。
   - $\frac{H(H+1)}{2}+H+2(H+1)+2(H+2)\ge n$ 时，答案是 $H+5$。
   - $\frac{H(H+1)}{2}+xH+\lfloor\frac{x^2}{4}\rfloor\ge n$ 时，答案是 $H+x$。
   - 此时，答案就是最小的 $x$ 使得 $\frac{H(H+1)}{2}+xH+\lfloor\frac{x^2}{4}\rfloor\ge n$，再加上 $H$。
- 所以，当 $\frac{H(H+1)}{2}\ge n$ 时，答案是 $\frac{x(x+1)}{2}\ge n$ 的最小正整数解；否则答案就是 $\frac{H(H+1)}{2}+xH+\lfloor\frac{x^2}{4}\rfloor\ge n$ 的最小整数解加上 $H$。

接下来解这两个方程。

第一个方程：
$$\frac{x(x+1)}{2}\ge n$$
$$x^2+x\ge 2n$$
$$x^2+x-2n\ge0$$
$$x\le\frac{-1-\sqrt{8n+1}}{2}\text{或}x\ge\frac{-1+\sqrt{8n+1}}{2}$$
因为 $\frac{-1-\sqrt{8n+1}}{2}=-\frac{1+\sqrt{8n+1}}{2}$ 必然小于 $0$，且要求 $x>0$，所以 $\frac{x(x+1)}{2}\ge n$ 的最小正整数解应该是 $\lceil\frac{\sqrt{8n+1}-1}{2}\rceil$。

第二个方程：

$$\frac{H(H+1)}{2}+xH+\lfloor\frac{x^2}{4}\rfloor\ge n$$
$$\lfloor\frac{x^2}{4}\rfloor+xH+(\frac{H(H+1)}{2}-n)\ge 0$$

众所周知，对于一个整数来说，$xH+(\frac{H(H+1)}{2}-n)$ 是一个整数，且 $\lfloor\frac{x^2}{4}\rfloor$ 要么为 $\frac{x^2}{4}$，要么为 $\frac{x^2}{4}-\frac{1}{4}$。所以，对于一个整数来说，$\frac{x^2}{4}+xH+(\frac{H(H+1)}{2}-n)$ 要么等于 $\lfloor\frac{x^2}{4}\rfloor+xH+(\frac{H(H+1)}{2}-n)$，要么等于 $\lfloor\frac{x^2}{4}\rfloor+\frac14+xH+(\frac{H(H+1)}{2}-n)$。可以推出，$\frac{x^2}{4}+xH+(\frac{H(H+1)}{2}-n)$ 要么是一个整数，要么是一个整数加上 $\frac14$。解一个整数 $+\frac14\ge0$ 的方程的解，也就相当于解一个整数 $\ge-\frac14$ 的解，那么解出来的答案和这个整数 $\ge0$ 的解是完全相同的。所以，$\lfloor\frac{x^2}{4}\rfloor+xH+(\frac{H(H+1)}{2}-n)\ge 0$ 的整数解就相当于解 $\frac{x^2}{4}+xH+(\frac{H(H+1)}{2}-n)\ge0$ 的整数解。

接下来解 $\frac{x^2}{4}+xH+(\frac{H(H+1)}{2}-n)\ge0$ 这个方程。

$$\frac{x^2}{4}+xH+(\frac{H(H+1)}{2}-n)\ge 0$$
$$x^2+4Hx+(2H^2+2H-4n)\ge 0$$
$$x\le\frac{-4H-\sqrt{8H^2-8H+16n}}{2}\text{或}x\ge\frac{-4H+\sqrt{8H^2-8H+16n}}{2}$$
$$x\le-2H-\sqrt{2H^2-2H+4n}\text{或}x\ge-2H+\sqrt{2H^2-2H+4n}$$

$-2H-\sqrt{2H^2-2H+4n}$ 明显小于 $0$，所以解是最小的整数 $x$，满足 $x\ge\sqrt{2H^2-2H+4n}-2H$。

最后的答案再加上 $H$，答案就是最小的满足 $x\ge\sqrt{2H^2-2H+4n}-H$ 的 $x$。

综上所述，当 $H(H+1)\ge 2\times n$ 时，答案是 $\lceil\frac{\sqrt{8n+1}-1}{2}\rceil$；否则答案就是 $\lceil \sqrt{2H^2-2H+4n}-H\rceil$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	long double n,h;cin>>n>>h;//注意到题目数据很大，并且精度容易出问题，所以保险一点开了 long double
	long long ans;
	if(h*(h+1)>=2*n){
		ans=ceil((sqrt(8*n+1)-1)/2);//ceil 返回 double，为了避免程序出错将它复制给 ans 这个 long long 变量
	}else{
		ans=ceil(sqrt(2*h*h-2*h+4*n)-h);//见上面的分析
	}
	cout<<ans; 
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/116661024)。

---

## 作者：xcrr (赞：6)

# 不用二分，数学方法搞定
[博客qwq](https://ni-hao-114514.blog.luogu.org/#)

这道题用不上二分答案，并且需要贪心的思想。这篇题解使用贪心+数学解法，同时简单陈述二分答案的合理性。

（蒟蒻的题解，如果有疑问或者问题请指出，希望比较严谨和易懂）

看到这道题，整理一下：
+ 假设这个沙堆，从左向右高度依次是 $h_1,h_2,h_3,…,h_{x-1},h_{x}$。这里 $h_{x}=1$，其余各项之间差的绝对值不大于 $1$。
+ $h_1\le H$。
+ 各项和等于 $n$，要求 $x$ 的值尽可能小。
## 思路
+ 贪心思想，先说结论：$h_1$ 尽可能大，那么 $x$ 就尽可能小。
+ 因为各项之间差的绝对值不大于 $1$，最后一个数还要等于 $1$，所以这个数列一定有从起始高度 $h_1$ 到 $1$ 的每一个数。
+ 那么我们可以把这个数列看成这个样子：一个 $h_1$ 到 $1$ 的公差为 $1$ 的等差数列，和其他零散的数。也就是把这个等差数列先拿出来。

+ 现在考虑剩下的数都有哪些可能： 
1. 等差数列的和就是 $n$，剩下的数是空集。
2. 等差数列的和小于 $n$，剩下的数在 $[1,h_1]$ 中（因为 $h_1$ 到 $1$ 的每一个数都有了，所以直接加上这些数是符合题意的。
3. 等差数列的和小于 $n$，剩下的数比 $h_1$ 还大，它们从 $h_2$ 开始，构成了一个先递增后递减的等差数列。
+ 现在可以看出贪心结论的正确性，如果 $h_1$ 不是尽可能大的，那么如果剩下的数在 $[1,h_1]$ 中选（即可能 $2$），一定需要更多个。如果剩下的数在大于 $h_1$ 中选（即可能 $3$），相当于

![](https://cdn.luogu.com.cn/upload/image_hosting/5ys9op2i.png?x-oss-process=image/resize,m_lfit,h_340,w_450)


$2$ 图已经和前面那种情况一样了。

接下来算 $h_1$。前面的分析过后，我们直接让等差数列的和尽可能大，剩下的尽可能小。不等式：
$$
\frac{h_1(h_1+1)}{2}\leq n
$$
$$
h_1^2+h_1-2n\leq0
$$

来个图

![](https://cdn.luogu.com.cn/upload/image_hosting/ewxtrpr9.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

$$
h_{1max}=\frac{-1+\sqrt{8n+1}}{2}
$$
这样已经完成了一半。**但别忘记 $h_1$ 它还有个限制：$h_1\le H$。**

于是判断一下，如果 $h_1$ 小于等于 $H$，说明 $h_1$ 取到了最大，$n$ 要么正好不剩，要么剩下的再来一个在 $[1,h_1]$ 中的数就补上了，也就是 $n$ 减一下等差数列的和，如果剩 $0$，那么 $ans$ 就是 $h_1$（项数），如果不为 $0$，那 $ans$ 就是 $h_1+1$。

如果 $h_1$ 大于 $H$ 的情况怎么办？这就说明 $h_1$ 没取到最大，就会被 $H$ 挡住，等差数列的首项是 $H$。

显然，这种情况下，我们还要额外多放几堆，这时我们的策略显然是放上面可能性的第 $3$ 种。也就是额外放置两个等差数列。设中间最高的堆为 $h_i$，我们要让 $h_1,...,h_{i-1},h_i,h_{i+1},...,h_{2i-2}$ 形成 $h_1$ 到 $h_{i-1}$ 的上升序列，和 $h_{i}$ 到 $h_{2i-2}$ 的下降序列。如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s4kkhj8f.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

方程与上一个同理，两个等差数列的和为定值 $left=n-\frac{\left ( 1+H \right ) \times H}{2}$。
$$
\frac{\left ( h_1+h_{i-1} \right ) \left ( i-1 \right )}{2} +\frac{\left ( h_{i}+h_{2i-2} \right ) \left ( i-1 \right )}{2} \le left
$$
$$
\frac{\left ( H+h_{i-1} \right ) \left ( i-1 \right )}{2} +\frac{\left ( h_{i}+H+1\right ) \left ( i-1 \right )}{2} \le left
$$
$$
 \left ( H+h_i \right ) \left ( i-1 \right ) \le left
$$
$$
 \left ( 2H+i-1 \right ) \left ( i-1 \right ) \le left
$$

解法同上。把 $i-1$ 当成一个数化简柿子。

还有细节没完，加上这些数列，我们可能还会剩下一些数才能凑齐 $n$。 还是用 n 减一下已经算出来的和，如果剩 $0$ ，直接统计答案，否则：

剩余的大于所有已经选的最高点，我不得不多堆两个堆；

剩余的小于等于已经选的最高点，我只需多堆一个堆。


时间复杂度，显然的 $O\left ( 1 \right )$。至于为什么比一些二分跑的慢，大概是因为``sqrt``慢的原因罢。

## 参考代码
~~反正我是照着草稿纸上的柿子一点一点打的~~，建议把思路搞懂，代码就简单了。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
long long h;
ll ans;
int main()
{
	scanf("%lld%lld",&n,&h);
	ll p=(-1+sqrt(1+8*n))/2;
	if(p<=h)
	{
		if(n==p*(p+1)/2)ans=p;
		else ans=p+1;
	}
	else
	{
		n-=h*(h+1)/2;
		ll x=-h+sqrt(h*h+n);
		ans=h+2*x;
		if(n>x*x+2*h*x)
		{
			n-=x*x+2*h*x;
			if(n<=h+x)ans++;
			else ans+=2;
		}
	}
	cout<<ans;
	return 0;
}
```


这里我们浅说下**为什么二分答案的解法也正确？**
 
我们以算出来的 $h_1$ 和 $H$ 的大小关系探讨了两步，二分答案也是同样分了两步，只是和我们的求解方式不同。我们以求解 $h_1$ 的步骤举例。

看上面的上面那张图，定义域在 $x>0$ 的情况下，恰好一部分在 $x$ 轴下，一部分在 $x$ 轴上，找的是交点的值，符合二分答案的要求。

显然，两者在题目的数据范围下实际上效率相差不大（或者都能符合要求），如果出现在比赛或者测试当中，应优先写二分的方法（不易出错），数学方法用来拓宽思路较好。

---

## 作者：HC20050615 (赞：4)

看大家都用了二分，我来提供一种不用二分的思路。~~（结果还没分块跑得快）~~。

首先，由于数轴无限长所以最后一个数后一定还有 $0$，所以最后一个数一定是 $1$。

假如没有 $h$ 的限制，我们肯定尽可能的堆成等差数列，即：$x,x-1,\cdots,1$ 以及一个单独的数 $t \in[1,x] $ （也可能没有 $t$）。于是，我们有
$$
sum=\frac{x(x+1)}{2}\leq n
$$
$$
x^2+x-2n\leq0
$$
$$
x_{max}=\frac{-1+\sqrt{8n+1}}{2}
$$
~~好像根号和二分没差很远。。。~~

如果上面求出的 $x>h$，就不能直接用上面的式子了。为了让最后的答案最小，我们要尽可能的加入更大的数。乍看我们选的数最大只能到 $h$，实际上并不是这样。虽然最左端的数有限制，但我们可以让他右边的数更大，我们如下摆放：

$h,h+1,\dots,x-1,x,x-1,\dots,1$ 以及 $t_1,t2\in[1,x]$。同理，我们推一下这个式子：
$$
sum=\frac{x(x-1)}{2}+\frac{(x+h)(x-h+1)}{2}
$$
展开后得:
$$
sum=x^2-\frac{h^2-h}{2}\leq n
$$
$$
x_{max}=\lfloor\sqrt{n+\frac{h^2-h}{2}}\rfloor
$$
最后特判一下，要额外加几个 $t$ 就行了。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long h;
long long sum;
long long cnt;
int main()
{
	cin>>n>>h;
	long long x=(sqrt((long double)(8*n+1))-1)/2;
	if(x<=h)
	{
		sum=(x+1)*x/2;
		cout<<x+(sum!=n)<<endl;
	}
	else
	{
		x=sqrt(n+(h*h-h)/2);
		sum=x*x-(h*h-h)/2;
		if(n==sum)
		{
			cout<<2*x-h<<endl;
		}
		else if(n-sum<=x)
		{
			cout<<2*x-h+1<<endl;
		}
		else
		{
			cout<<2*x-h+2<<endl;
		}
	}
	return 0;
}
```


---

## 作者：尹昱钦 (赞：4)

## 解题思路
总结一下，其实只有**两种**情况：
+ $k,k-1,k-2,k-3,k-4,k-5,……,1 (k\leqslant h) +$ 一堆高度为 $[1,k]$。
+ $h,h+1,……,h+x,h+x-1,h+x-2,……,1 +$ 一堆高度为 $[1,h+x]$。

**贪心**：$k$ 和 $x$ 显然是**越大越好**。

于是我们可以**二分** $k$ 和 $x$，从而得出答案。

## 注意的细节：

等差数列求和需要 $h\times(h+1)/2$，而 $h\leqslant1e18$，直接乘会炸 long long。

所以我们可以一开始特判一下，因为 $n\leqslant1e18$，所以若 $h\geqslant1e9$，一定是第一种情况，直接二分即可。

## AC代码
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<cmath>
#include<algorithm>
using namespace std;
long long n,h; 
bool check(long long x){
	if(x*(x+1)/2>=n) return true;
	return false;
}
bool check2(long long x){
	if((h+x)*(x-h+1)/2+x*(x+1)/2>=n) return 1;
	return 0; 
}
int main(){
	cin>>n>>h;
	if(h>=2e9||(h*(h+1)/2>=n-h)){
		long long l=1,r=min((long long)2e9,h),mid=(l+r)/2;
		while(l!=r){
			if(check(mid)) r=mid;
			else l=mid+1;
			mid=(l+r)/2;
		}
		if(l*(l+1)/2<n) l++;
		cout<<l<<endl;
		return 0;
	}
	long long l=h,r=2e9,mid=(l+r)/2;
	while(l!=r){
		if(check2(mid)) r=mid;
		else l=mid+1;
		mid=(l+r)/2;
	}
	long long ans=(l-h)+l;
	if((h+l)*(l-h+1)/2+l*(l+1)/2-l<n) ans++;
	cout<<ans<<endl;
    return 0;
}
```

---

## 作者：HHYQ_07 (赞：4)

# 题解

## [题目链接](https://www.luogu.com.cn/problem/CF985D)

## 前言

因为前面已经有很多篇优秀的题解给出了详细的思路，故本篇题解不再讲述具体思路，而是给大家介绍一种新的二分方法：倍增二分。

## 倍增二分

为了避免混淆，我们称之前的二分方式为朴素二分，新的二分方式为倍增二分。

### 思想

倍增二分其实和二分没有太大关系，主要是倍增的思想。因为任何一个十进制整数都能表示为二进制的形式，换言之，通过二进制可以组成任何一个十进制整数，而二分题目特有的单调性又能保证枚举到每一个需要枚举的整数。

### 过程

枚举每一个二进制位，也就是 $2^n(n\in \mathbb N)$，满足条件的就更新答案，不满足就跳过。然而枚举的顺序一定要从大到小，因为如果此位不满足条件，即使后面的所有位都满足也不会到达这一位，这样每一步的答案都是可控制的。但是如果从小到大枚举，程序中会把满足条件的一直更新答案，也无法知道此位对答案有无影响。简洁地说，就是要满足无后效性。

### 举例

当然文字描述是十分抽象的，接下来举一个倍增二分查找例子来说明。比如说我们要找一个在 $13$ 位置的元素。我们会先跳到 $16$。比 $13$ 大，不满足条件，跳过。接下来我们会跳到 $8$，比 $13$ 小加进答案，此时答案为 $8$，接着会访问到 $4$、$2$、$1$，因为访问到 $4$、$1$ 时满足条件，所以最终会访问到目标值为：$8+4+1=13$。

### 时间复杂度

因为模拟 `check` 函数中的模拟部分是一样的，所以我们讨论在二分过程中的时间复杂度。设 $n$ 为序列长度，朴素二分是每次分一半去找符合条件的那一个，大致为 $O(\log n)$ 的时间复杂度。而倍增二分就更快一些，因为如果答案不超过 $10^9$，$2^{31}-1$ 之内就能完全覆盖答案可能的取值范围，而也仅仅只枚举了 $30$ 位，严格的时间复杂度请读者自行推理证明。

## AC code

本篇题解不展示 C++ 正确倍增二分代码，供读者自行思考。看没有 pyhton 的题解，就发一篇 python 的数学解法。

```python
import math as m
n,H=input().split(" ")
n,H=int(n),int(H)
h=int((m.sqrt(8.0*n+1)-1)/2)
if h<=H:
    if h*(h+1)==n*2:
        print(h)
    else:
        print(h+1)
    exit()
anss=m.ceil(2.0*m.sqrt(1.0*n+1.0*H*(H-1)/2.0))-H
print(int(anss))
```

---

## 作者：spdarkle (赞：3)

首先因为最后一个位置是空的，所以高度为 $0$，也即最后一堆沙袋只能有一个。

所以最终的序列必定有递减的一段。

由于相邻高度差不超过一，我们尝试着发现一些性质。

可以这么想，对于一个合法的操作序列，如果我们对 $h$ 进行自大到小的排序，我们设初始序列的首项为 $a$，则 $h_1\sim h_k(h_k=a)$ 中每个元素都至少被重复了一次。

则我们不妨将 $h_1\sim h_k$ 反过来，则 $h_k,h_{i},h_{j}…h_1,h_{x},h_y…$ 也是一个合法的序列。

也即：**一个合法序列一定可以重组为一个非严格单峰序列**。

这启发我们直接从单峰的角度考虑，不妨设首项为 $a$，峰值为 $t$。

这个合法序列可以看作 $a,a+1,a+2…t,t-1,t-2…1$ 从中插入若干个值在区间 $[1,t]$ 内的数使得序列之和是 $n$ 且序列长度最低。设这个待插入的序列的值为 $sum$。

显然这个待插入序列的长度为 $2t-a$。
其实吧，可以这样想：我们以一种贪心的形式，每次加入最大值 $t$，这是正确的。我们加入 $\left\lfloor\frac{n-sum}{t}\right\rfloor$ 个 $t$ 值，然后插入一个 $(n-sum)\bmod t$ (非零)。根据高斯公式，$sum=\frac{t(t+1)}{2}+\frac{t(t-1)}{2}-\frac{a(a-1)}{2}=t^2-\frac{a(a-1)}{2}$。

所以说，我们实际上是需要求解：

$$\min_{a\le t,a\le H}\left\lbrace\left\lceil\frac{n-t^2+\frac{a(a-1)}{2}}{t}\right\rceil+2t-a\right\rbrace$$

简单化简一下就变成了：

$$\min_{a\le t,a\le H}\left\lbrace\left\lceil\frac{n+\frac{a(a-1)}{2}}{t}\right\rceil+t-a\right\rbrace$$

对于这个式子的化简，我们进行分类讨论。

1. 当这个序列变成单减序列时候，也即 $t+t-1+t-2+…+1<n$ 的时候。

> 此时取极值显然可以得到 $t^2+t-2n=0\implies t=\frac{\sqrt{1+8n}-1}{2}$，当存在这个 $t$ 值的时候，序列长度为 $t$，当不存在这个 $t$ 值的时候，可以取其下取整结果，并多插入一个数修正即可，序列长度为 $t+1$。这显然是最短的。

2. 否则，分析这个序列，进行比较决策法。

> 对于 $a$ 与 $a+1$ 两个决策，对于下取整符号内和下取整符号外的情况，$a+1$ 会使得其下取整符号内加上 $a$，又由于 $a\le t$，所以下取整符号内的式子贡献最多为 $1$，而外面的式子贡献为 $-1$。所以与原情况相比可以得到 $a+1$ 一定不劣于 $a$。故大可以取 $a=H$ (至于为什么第一种情况要特殊列出，是因为不需要进行单增，会导致多计算)。这样的话，再次将式子写出：
>
> $$\min_{H\le t}\left\lbrace\left\lceil\frac{n+\frac{H(H-1)}{2}}{t}\right\rceil+t-H\right\rbrace=\min_{H\le t}\left\lbrace\left\lceil\frac{n+\frac{H(H-1)}{2}}{t}\right\rceil+t-H\right\rbrace$$
>
>又因为 $H$ 是常量，可以省去，实际上我们需要求解的是
>
>$$\min_{H\le t}\left\lbrace\left\lceil\frac{x+t^2}{t}\right\rceil\right\rbrace$$
>
>但事实上，我们要求其下取整的值，只需要求出它实际的最小值，其下取整的最小值自然也是其实际最小值的下取整结果。
>
>故事实上只需求：$(\frac{x}{t}+t)_{\min}$，根据均值不等式可以得到 $t=\sqrt{x}$。。而显然由于第一种情况的存在，此时 $t$ 是不会越界的。
>
>回带 $x$，最终答案计算式为：
>
>$$\left\lceil2\sqrt{n+\frac{H(H-1)}{2}}\right\rceil-H$$

参考代码

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
#define ll long long 
ll n,h,ans;
#define db double
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>h;
    ll h1=(ll)(sqrt(8.0*n+1)-1)/2;
    if(h1<=h){
        if(h1*(h1+1)==n*2)cout<<h1;
        else cout<<h1+1<<endl;
        //system("pause");
        return 0;
    }
    ll Ans=ceil((double)2.0*sqrt(1.0*n+1.0*h*(h-1)/2.0))-h;
    cout<<Ans<<endl;
    //system("pause");
    return 0;
}
```

---

## 作者：Xiao_mo (赞：3)

## [题面](https://www.luogu.com.cn/problem/CF985D)
# Step1
首先可以发现只有两种情况。
 
 1. 当 $n≤\frac{H×(H+1)}{2}$ 时，可以摆成 $[x,x-1,x-2$ …… $2,1]$ 。此时只要二分 $x$ 。
 2. 当 $n>\frac{H×(H+1)}{2}$ 时，可以摆成 $[H,H+1,H+2$ …… $H+p-1,H+p,H+p-1$ …… $2,1]$ 或者 $[H,H+1,H+2$ …… $H+p-1,H+p,H+p,H+p-1$ …… $2,1]$ 。此时二分堆数 $x$ 。
 
# Step2
考虑第一种情况。

二分 $x$ ，可以放下的沙袋个数 $ans=\frac{x×(x+1)}{2}$ 。

# Step3
考虑第二种情况。

二分 $x$ 。

先将 $x$ 加上 $(H-1)$，设 $p=\frac{x}{2}$ 。

 1. 当 $x$ 为奇数时，序列变成一个 $[1,2$ …… $p,p+1,p$ …… $2,1]$。所以此时可以放下的沙袋个数 $ans=(p+1)×(p+1)-\frac{H×(H-1)}{2}$。

 2. 当 $x$ 为偶数时，序列变成一个 $[1,2$ …… $p,p$ …… $2,1]$。所以此时可以放下的沙袋个数 $ans=(p+1)×p-\frac{H×(H-1)}{2}$。
 
观察数据范围，$n,H≤10^{18}$。

发现会爆 $long$ $long$ 。

所以我开了 $double$ 。
# End
附上代码
```
#include<bits/stdc++.h>
#define ll long long
#define rg register
using namespace std;
inline ll read() {
	register ll s=0,f=0;
	register char ch=getchar();
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return f?-s:s;
}
ll n,h;
inline bool check(ll x) {
	x+=(h-1);
	double ans=-h*(h-1)/2,p=x/2;
	ans+=p*(p+1);
	if(x&1)ans+=p+1;
	if(ans>=n)return 1;
	return 0;
}
int main() {
	n=read(),h=read();
	ll l=1,r=n,m;
	if(2*n/(h+1)<=h) {
		r=2*sqrt(n)+1;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(mid*(mid+1)/2>=n){
				m=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
	} else {
		while(l<=r) {
			ll mid=(l+r)>>1;
			if(check(mid)) {
				m=mid;
				r=mid-1;
			} else l=mid+1;
		}
	}
	printf("%lld",m);
	return 0;
}
```


---

## 作者：Halberd_Cease (赞：0)

我们首先考虑如果允许的长度为 $len$，我们最多可以摆多少个。

可以发现，要把 $len$ 吃满，摆沙包的方法一定是一个单峰的，如下图（均以 $H=3$ 为例，`o` 是放的沙包，`x` 为了补全单峰的性质添上的不存在的点）：

- 奇数（$len=5$）：

	![](https://cdn.luogu.com.cn/upload/image_hosting/lq4epv8y.png)

- 偶数（$len=4$）：

	![](https://cdn.luogu.com.cn/upload/image_hosting/cqqsrjow.png)
    
把 `o` 的数量算出来，就是当前的 $len$ 可以堆沙包的最大值。

如果沙包数量比最大值少，那就一定可以摆出来，可以感性理解：假设相比最大摆法缺失的是右边的一堆，将最高的取下，补齐右边的。

然后又因为这个最大数量单调递增，考虑二分答案，然后就做完了。

注意中间变量答案会炸 64 位整数，我选 python。

```py
def solve(len_val, h_val):
    dx = len_val + h_val - 1
    if len_val <= h_val:
        return len_val * (len_val + 1) // 2
    if dx & 1:
        return (dx // 2 + 1) * (dx // 2 + 2) // 2 + (dx // 2) * (dx // 2 + 1) // 2 - h_val * (h_val - 1) // 2
    else:
        return 2 * (dx // 2) * (dx // 2 + 1) // 2 - h_val * (h_val - 1) // 2

if __name__ == "__main__":
    nn, hh = map(int, input().split())
    n, h = nn, hh
    l, r = 1, nn
    ans = nn
    while l <= r:
        mid = (l + r) // 2
        if solve(mid, h) >= n:
            ans = mid
            r = mid - 1
        else:
            l = mid + 1
    print(ans)

```

---

