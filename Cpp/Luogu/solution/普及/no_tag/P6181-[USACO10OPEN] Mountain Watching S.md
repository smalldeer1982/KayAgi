# [USACO10OPEN] Mountain Watching S

## 题目描述

一天，Bessie 望着远处的山脉，在思考：“哪一座山最宽呢？”

Bessie 设法测量了 $N$ 个位置的高度 $h_i$（$1 \leq N \leq 10^5$，$1 \leq h_i \leq 10^9$）。一座山被定义为一个高度先不下降，后不上升的子序列。视野边缘的山脉也只会增加或减少高度。一座山的宽度被定义为这座山包含的位置数量。

下面是一个例子：

```plain
           *******                   *
          *********                 ***
          **********               *****
          ***********           *********               *
*      *****************       ***********             *** *
**    *******************     *************   * *     *******      *
**********************************************************************
3211112333677777776543332111112344456765432111212111112343232111111211
aaaaaa                   ccccccccccccccccccccc eeeeeee    ggggggggg
  bbbbbbbbbbbbbbbbbbbbbbbbbbbb             ddddd ffffffffff  hhhhhhhhh
```

每座山都已经用字母标出来了。这里 `b` 山脉的宽度最大，为 $28$。

## 样例 #1

### 输入

```
7
3
2
3
5
4
1
6```

### 输出

```
5```

# 题解

## 作者：LeiZeProMax (赞：3)

蒟蒻的第一篇题解，如有错误请指出。

题意：给定一个序列的长度 $n$ 和序列中的数，求最长连续单峰子序列。 

我们可以定义一个 $ans$ 来代表当前最长单峰子序列的长度，因为 $n\le10^5$，所以只需要用 int 定义就可以。

求连续单峰子序列的长度也很简单，用每个数之后连续不上升序列终点减去这个数之前连续不下降序列起点再 $+1$ 即可。

注意：当连续单峰子序列的长度等于 $n$ 时，我们可以直接跳出，从而节省一定的时间。
## Code
```cpp
#include<bits/stdc++.h>
#define Max(i,j) (i>j?i:j)
using namespace std;
int i,n,ans=-12,a[100001];
int main()
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(i=1;i<=n;i++)
	{
		int x=i,y=i;
		//x为连续不下降序列起点，y为连续不上升序列终点 
		for(;a[x-1]<=a[x]&&x>1;x--);
                //求连续不下降序列起点 
		for(;a[y+1]<=a[y]&&y<n;y++);
                //求连续不上升序列终点 
		ans=Max(ans,y-x+1);
		//如果ans小于当前单峰子序列就更改答案(记得+1) 
		if(y-x+1==n)break;
		//如果连续单峰子序列长度与n相同，直接跳出 
	}
	printf("%d",ans);
	return 0;
} 
```



---

## 作者：Wy_x (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P6181)

[更好的阅读体验？](https://www.luogu.com.cn/blog/73-54-16/solution-p6181)

### 题意： 

- 给定 $n$ 和 $n$ 个数，求最宽的山的宽度（其实就是最长单峰子序列，
~~但我不会~~）。


### 数据范围：
$ 1 \leq n \leq 10^5 , 1 \leq h_i \leq 10^9 $

### 做法：

- **注意：直接爆搜会超时**！！！

- 建数组 $h$ 存放山脉信息，最大值 `maxn` 存最宽山的宽度；

- 每次从 $i$ 开始搜索，定义 $l$ 和 $r$ , $l$ 记录向左搜到的位置，$r$ 记录向右搜到的位置（**注意搜到边界** $1$，$n$ **时的特判**），搜索方法题目中给出来了
 
>- 如果现在搜出的山的宽度 $>$ `maxn` 则更新 `maxn`；

>- 如果现在搜出的山的宽度 $\leq$ `maxn` 则不更新 `maxn`；

- 最后输出 `maxn`。

- 注：三目运算符`表达式1?表达式2:表达式3`，若`表达式1`值为真返回 `表达式2`，否则返回`表达式3`。

### 考虑优化：
若某次搜出的山的宽度为 $n$，那就没有继续搜索下去的必要了，`maxn=n`，以后再搜出来的山的宽度肯定 $\leq$ $n$，就不会再更新 `maxn` 的值，可以直接跳出循环。不优化最后一个点会`TLE`。

- 弱化版[P1893 山峰暸望](https://www.luogu.com.cn/problem/P1893)可以不优化。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,maxn=-1,h[100050];
//maxn存最大值，初始化最小   
int ma(int x,int y) { return x>y?x:y; }
//自己写的判断最大值的函数  
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>h[i];
    for(int i=1;i<=n;i++)
    {
        int l=i,r=i;
        //向左搜索 left，向右搜索 right 
        while(h[l-1]<=h[l]&&l-1>=1)  l--;
        while(h[r+1]<=h[r]&&r+1<=n)  r++;
        maxn=ma(r-l+1,maxn);
        //或 maxn=max(r-l+1,maxn); 
        //自己写函数只是为了加快速度  
        if(r-l+1==n) break;
        //优化： 
        //不优化会TLE 
        //若某次搜索出山的宽度为n, 
        //那这座山的宽度肯定是最大的  
		//那就没有搜下去的必要了 
        //直接跳出循环  
    }
    cout<<maxn;
    //输出最大值  
    return 0;
}
```




---

## 作者：Shadow_Lord (赞：2)

蒟蒻的第二篇题解。

题意：给出山脉上 $n$ 个位置的高度，求最宽山峰的长度。

思路：只需求出每个地点所处不上升子序列和不下降子序列的长度和的最大值即可。

重点来了：求每个地点不上升子序列的递推式：如果上一个位置高度小于等于当前位置的高度：$f[i]=f[i]+f[i-1]$。反之，即可求出每个地点不下降子序列的长度。

注意：要将 $f[i]$ 和 $g[i]$ 初值定为 $1$，$i$ 所处山峰长度应为 $f[i]+g[i]-1$。
## 代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
inline int read()//快读 
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
    return x*f;
}
const int N=1e5+5;
int n,h[N],f[N],g[N],ans;
//h数组是山峰高度，f数组是以i为结尾的不下降子序列长度，g数组是以i为结尾的不上升子序列长度，ans是山峰的宽度 
int main(){
	n=read();
	for(int i=1;i<=n;i++) h[i]=read();
	h[0]=0x3f3f3f;
	h[n+1]=-0x3f3f3f;
	//h[0]和h[n+1]改为特别大的值，方便后面计算 
	for(int i=1;i<=n;i++)f[i]=1;
	//将不下降子序列的初始长度赋值为1 
	for(int i=1;i<=n;i++) if(h[i-1]<=h[i]) f[i]+=f[i-1];
	//如果前面的山峰高度小于等于当前山峰，则长度相加 
	for(int i=1;i<=n;i++)g[i]=1;
	//将不上升子序列的初始长度赋值为1 
	for(int i=n;i>=1;i--)if(h[i+1]<=h[i])g[i]+=g[i+1],ans=max(ans,g[i]+f[i]-1);
	//如果后面的山峰高度小于等于当前山峰，高度相加
	//因为要先更新后面的山峰，所以i要从n到1倒着枚举 
	//如果ans小于不下降子序列长度和不上升子序列长度的和-1，就更新 
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Link_Cut_Y (赞：1)

感觉可以评黄。

## 简化题意

题意已经很简单了，不需要再简化了。

[点此看题](https://www.luogu.com.cn/problem/P6181)

## 题目分析

预处理以每个点为终点（起点）的最长不下降子序列（最长不上升子序列）。复杂度 $\mathrm{O(n)}$。

不妨将最长不下降子序列设为 $\mathrm{up_i}$，最长不上升子序列设为 $\mathrm{down_i}$。答案即为 $\mathrm{\max\{ up_i + down_i \} - 1}$，这里 $-1$ 是因为当前点在不下降和不上升子序列里被重复算了。这里的复杂度是 $\mathrm{O(n)}$。

## 代码示例

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#define rep(i, a, b) for (int i = (a); i <= (b); i ++ )
#define rop(i, a, b) for (int i = (a); i < (b); i ++ )
#define dep(i, a, b) for (int i = (a); i >= (b); i -- )
#define dop(i, a, b) for (int i = (a); i > (b); i ++ )

using namespace std;

const int N = 100010;
int n, h[N], up[N], down[N];
int ans = 0;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++ )
		scanf("%d", &h[i]);
	
	for (int i = 1; i <= n; i ++ )
		up[i] = h[i] >= h[i - 1] ? up[i - 1] + 1 : 1;
	for (int i = n; i >= 1; i -- )
		down[i] = h[i] >= h[i + 1] ? down[i + 1] + 1 : 1;
	for (int i = 1; i <= n; i ++ )
		ans = max(ans, up[i] + down[i] - 1);
	
	printf("%d\n", ans);
	return 0;
}
```

最后别忘了注意一下坑点：是非单调的！（~~我是不会告诉你我在这里错过的~~）

最后祝大家元宵节快乐！！

---

## 作者：a1a2a3a4a5 (赞：1)

#### [题目：](https://www.luogu.com.cn/problem/P6181)
- 题意

1. 高度先不下降，后不上升的子串是山的定义，求最宽的一座山宽度。

2. 感性理解：求一个最长的中间大两头小的子串长度。

3. 精简版：一个点的左边是不下降子串，右边是不上升子串，且两个子串的长度和最大的值。

#### 	我说：题目描述第二段写错了，应该是 ' 子串 '，而不是 ' 子序列 '。

- 思路

1. 我们很容易就可以想到 DP：原因是在上 面的 题意 $ 3 $ 精简版 可以知道：一个点左边是不下降子串，右边是不上升子串，那么宽度相当于左边的不下降子串加上右边的不上升子串的值。

2. DP 状态：这样可以想到用一个 $ up $ 数组来存左边不下降子串长度，用一个 $ down $ 数组存右边不上升子串长度。

	$ up[i] $ 表示在第 $ i $ 个点左边的不下降子串的最大长度。
    
    $ down[i] $ 表示在第 $ i $ 个点右边的不上升子串的最大长度。

3. DP 方程：再由不下降子串定义——即左边的数小于不大于右边的数，不上升子串的定义——即右边的数不大于左边的数。

	当它继续满足不下降子串定义时 $ up[i]=up[i-1]+1$。
    
    当它继续满足不上升子串定义时 $ down[i]=down[i+1]+1$。
    
    若不满足，则归一（因为只剩它一个也算上）。

- 问题

1. 枚举时，正序枚举 $ up$，逆序枚举 $ down$，这样才可以读取前一个的 DP 的值。

2. $up[1] $ 初始化为 $ 1 $，$down[n] $ 也初始化为 $ 1$，否则你只能得一半分。原因是如果开始就遇到了最好情况，那么会少算一次宽度。

- 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,da,h[110000],up[110000],down[110000];
int main()
{
		cin>>n;
		for(int i=1;i<=n;i++) cin>>h[i];
		up[1]=1,down[n]=1;
		for(int i=2;i<=n;i++) if(h[i-1]<=h[i]) up[i]=up[i-1]+1; else up[i]=1;
		for(int i=n-1;i>=1;i--) if(h[i]>=h[i+1]) down[i]=down[i+1]+1; else down[i]=1;
		for(int i=0;i<=n;i++) da=max(da,up[i]+down[i+1]);
		cout<<da;
		return 0;
}
```

---

## 作者：yydfj (赞：1)

**这是本蒟蒻第二十六次写的题解，如有错误点请好心指出！**

## 问题简述

给你一个整数 $n$ 和长度为 $n$ 的数组 $a$，在 $a$ 数组中找到一个最长连续单峰子序列，输出其长度。

## 解法综述

用 $i$ 从 $1$ 到 $n$ 遍历数组 $a$，设 $t$ 为某个连续单峰子序列的长度，$b$ 为上一个连续下降子序列末尾前一个的数，$s$ 为两个连续单峰子序列公共部分的长度。

因为单峰就是先增后减，所以当 $a_{i-1}<a_i$ 且 $b>a_{i-1}$ 的时候，说明有新的连续单峰子序列，于是更新 $t$ 为 $s+1$，否则继续计算所在序列的长度。

如果 $a_{i-1}>a_i$，说明此时序列严格下降，不存在两个连续单峰子序列有公共部分，于是更新 $b=a_{i-1}$ 和 $s=1$，否则让 $s$ 计算所在两个序列公共部分的长度。

用 $ans$ 求 $t$ 的最大值，输出 $ans$ 即可。

## 代码描述
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,a[100005],b,s,t,ans;
//t为某个连续单峰子序列的长度，b为上一个下降子序列末尾前一个的数，s为两个连续单峰子序列公共部分的长度
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i-1]<a[i]&&b>a[i-1]) t=s+1;//有新的连续单峰子序列
		else t++;//继续计算该序列的长度
		if(a[i-1]>a[i]) b=a[i-1],s=1;//此时序列严格下降
		else s++;//让s计算公共部分的长度
		ans=max(ans,t);//求t的最大值
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：huangrenheluogu (赞：0)

蒟蒻的第一篇题解，如有错误请指出。

题意：给定义行高度，求有多少个峰（最高点），然后我们就可以模拟去求。

我们仔细观察就可以发现这道题本质就是去寻找有多少个峰，我们观察题目里的示例就可以发现：

```

           *******                   *
          *********                 ***
          **********               *****
          ***********           *********               *
*      *****************       ***********             *** *
**    *******************     *************   * *     *******      *
**********************************************************************
3211112333677777776543332111112344456765432111212111112343232111111211
aaaaaa                   ccccccccccccccccccccc eeeeeee    ggggggggg
  bbbbbbbbbbbbbbbbbbbbbbbbbbbb             ddddd ffffffffff  hhhhhhhhh
  
  ```
从第 $3$ 列到第 $7$ 列（即第一个都是 $1$ 的部分）都是两座山公用的，所以我们需要处理一个重要的问题：就是在本题中的重复的山脉。

为了处理两座山，我决定用一个 `nxt` 和一个 `now`，分别表示两座山的宽度，这样当一座山真正结束的时候，我们就可以复制过去。

为了判断是上山还是下山，我们可以定义一个 `bool` 变量来标记（本题解中 `false` 表示上山，`true` 表示下山）。

接下来我们进行分类讨论：
- $a_i=a_{i+1}$

这里就说明是一个平坡，我们有两种情况，第一种是上山，则可能是在山顶的平路或者是半山腰的平路，所以代码如下：
```cpp
if(a[i]==a[i+1]){
	now++;
	if(b==true) nxt++;
}
```
- $a_i>a_{i+1}$

这里只有一种情况，下坡，但是注意处理上坡到下坡的情况，此时一个山的顶端就结束了，所以注意改变 `bool` 数组的标记，贴上代码：
```cpp
if(a[i]>a[i+1]){
	if(b==false) b=true;
	now++;
}
```
- $a_i<a_{i+1}$
这里有两种情况，一种是上坡，那没有问题，`now++` 即可。

第二种就是从下坡（即 `b` 被标记时）到上坡，所以我们可以换一种山，这里注意需要把我们的 `bool` 数组修改掉，然后我们需要进行比较，更新最大值，代码如下：
```cpp
if(a[i]<a[i+1]){
	if(b==false) now++;
	else {
		now++;
		Max=max(Max,now);
		now=1+nxt,nxt=0;
		b=false;
	}
}
```

好了，三种情况结束了，但是不要忘记可能还会被卡，因为在结束的时候我们还需要更新最大值，所以不忘忘记加上：
```cpp
Max=max(Max,now),Max=max(Max,nxt);
```
最后送给大家完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],now,nxt,Max;
bool b=false;
inline void read(int &res){
	res=0;int f=1;char ch=getchar();
	while('0'>ch||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while('0'<=ch&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^48);
		ch=getchar();
	}
	res=res*f;
}
inline void put(int x){
	if(x<0) putchar('-'),x=-x;
	if(x>=10) put(x/10);
	putchar((x%10)^48);
}
int main(){
	read(n);
	for(int i=1;i<=n;i++) read(a[i]);
	nxt=0;
	int i=1;now=0;
	while(a[i]<a[i+1]) i++,now++;
	for(;i<=n;i++){
		if(a[i]==a[i+1]){
			now++;
			if(b==true) nxt++;
		}
		if(a[i]<a[i+1]){
			if(b==false) now++;
			else {
				now++;
				Max=max(Max,now);
				now=1+nxt,nxt=0;
				b=false;
			}
		}
		if(a[i]>a[i+1]){
			if(b==false) b=true;
			now++;
		}
	}
	Max=max(Max,now),Max=max(Max,nxt);
	put(Max);
	return 0;
}
```
好了，注意加读优更快（蒟蒻只会递归的输优，大佬可以提一点建议，当然`printf`和`cout`应该也没有问题）

---

## 作者：Remake_ (赞：0)

不得不说，这道题的题目描述非常迷惑，我也是看了好长时间才看懂的，不过当你看懂之后，这道题就非常简单了，至少我觉得是个红题。

题目看懂后可以化简为这样：在给定的数列中找出一个子序列（必须是连续的）是单峰的并最大化它的长度，所谓单峰，就是在这个序列里有且仅有一个点，它的左边单调不递减，右边单调不递增。

看懂以后，我首先把他和P1091 合唱队形联系了起来，但我忘了找出来的子序列必须是连续的。

当我想到子序列必须是连续的时候，我就想到了一种递推做法，设$zheng_i$表示$i$前面（包括$i$）有多少个数在连续且不递减，设$fan_i$表示$i$后面（包括$i$）有多少个数在连续且不上升。


$zheng$的递推式：

$zheng_1=1$

$if(h_{i-1}<=h_i)\,\,\,\,\,zheng_i=zheng_{i-1}+1$

$if(h_{i-1}>h_i)\,\,\,\,\,zheng_i=1$

$fan$的递推式：

$fan_n=1$

$if(h_{i+1}<=h_i)\,\,\,\,\,fan_i=fan_{i+1}+1$

$if(h_{i+1}>h_i)\,\,\,\,\,fan_i=1$

最后再逐个比较取最大值就行了，但一定要注意得把最终答案$-1$，因为将$zheng_i$和$fan_i$相加之后$i$是被算了两次的，所以要$-1$。

ACcode:

```cpp
#include<bits/stdc++.h>
using namespace std;    
long long zheng[100005],fan[100005],n,a[100005],maxn;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
	zheng[1]=1;
	fan[n]=1;
	for(int i=2;i<=n;i++) a[i]>=a[i-1]?zheng[i]=zheng[i-1]+1:zheng[i]=1;
	for(int i=n-1;i>=1;i--) a[i]>=a[i+1]?fan[i]=fan[i+1]+1:fan[i]=1;
	for(int i=1;i<=n;i++) maxn=max(maxn,zheng[i]+fan[i]-1);
	cout<<maxn;
}
```


---

## 作者：V1mnkE (赞：0)

## 题意
在给定的数列中找出一个连续的单峰子序列，求其长度最大值。

## 思路
其实这道题看懂了之后就很简单了，我们用 $f_i$ 表示前 $i$ 个数有多少个数连续且不递减，用 $f1_i$ 表示第 $i$ 个数以及之后有多少个数连续且不上升。

可以得出如下的递推式:

- ```if( a[i]<=a[i-1] )f[i]=f[i-1]+1;else  f[i]=1;```
- ```if( a[i]>=a[i+1] )f1[i]=f1[i+1]+1;else  f1[i]=1;```

然后逐个比较 $f_i + f1_i$ 求最大值即可。

注意求出的最大值要减 $1$，因为峰顶被算了两遍。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;    
long long f[100010],f1[100010],n,a[100010],mx;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
	f[1]=1;
	f1[n]=1;
	for(int i=2;i<=n;i++) {
		if(a[i]>=a[i-1])f[i]=f[i-1]+1;
		else f[i]=1;
	}
	for(int i=n-1;i>=1;i--){
		 if(a[i]>=a[i+1])f1[i]=f1[i+1]+1;
		 else f1[i]=1;
	}
	for(int i=1;i<=n;i++) mx=max(mx,f[i]+f1[i]-1);
	cout<<mx;
}
```

---

