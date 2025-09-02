# Fox and Box Accumulation

## 题目描述

Fox Ciel has $ n $ boxes in her room. They have the same size and weight, but they might have different strength. The $ i $ -th box can hold at most $ x_{i} $ boxes on its top (we'll call $ x_{i} $ the strength of the box).

Since all the boxes have the same size, Ciel cannot put more than one box directly on the top of some box. For example, imagine Ciel has three boxes: the first has strength 2, the second has strength 1 and the third has strength 1. She cannot put the second and the third box simultaneously directly on the top of the first one. But she can put the second box directly on the top of the first one, and then the third box directly on the top of the second one. We will call such a construction of boxes a pile.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF388A/6d2633af40be72721ab147bac34f10adae362d79.png)Fox Ciel wants to construct piles from all the boxes. Each pile will contain some boxes from top to bottom, and there cannot be more than $ x_{i} $ boxes on the top of $ i $ -th box. What is the minimal number of piles she needs to construct?

## 说明/提示

In example 1, one optimal way is to build 2 piles: the first pile contains boxes 1 and 3 (from top to bottom), the second pile contains only box 2.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF388A/8da8ac854632528901b4b6d1d556d9ee8e51a35b.png)In example 2, we can build only 1 pile that contains boxes 1, 2, 3, 4, 5 (from top to bottom).

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF388A/c58e3e4af77310d72ce6f918487297f03a91630c.png)

## 样例 #1

### 输入

```
3
0 0 10
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
0 1 2 3 4
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
0 0 0 0
```

### 输出

```
4
```

## 样例 #4

### 输入

```
9
0 1 0 2 0 1 1 2 10
```

### 输出

```
3
```

# 题解

## 作者：Loser_King (赞：3)

这道题的数据范围很小，所以可以直接暴力+贪心。

考虑到答案只能在区间$[1,n]$之间，所以直接for循环每个盒子即可。

在此之前只需要sort，保证先把尽量大的放在堆的下面即可。

时间复杂度： $O(n^2)$

贪心依据：当不把堆中最大的数放在底部时，堆的大小就变成较小的数，对贪心不利。

代码中vis数组记录盒子有没有被用过，tal表示当前堆的高度，ans表示堆数。

$\color{blue}\texttt{Code:}$
```
#include<bits/stdc++.h>
int n,a[233],vis[233],ans;
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%d",&a[i]);
    std::sort(a,a+n);
    for(int i=0;i<n;i++)
        if(!vis[i]){
            int tal=vis[i]=1;
            for(int j=i+1;j<n;j++)
                if(!vis[j]&&tal<=a[j])vis[j]=1,tal++;
            ans++;
        }
    printf("%d",ans);
}
```
谢谢大家!

---

## 作者：Crasole (赞：0)

## 题意

一共有 $n$ 个箱子，每个箱子有一个力量值 $X_i$，代表这个在这个箱子上能放 $X_i$ 个箱子。

现在要将这些箱子堆在一起，问：最少能堆成几堆。

## 思路

先对 $X$ 数组升序排序，接着依此枚举每个箱子，用一个 $b$ 数组标记每一个数。

因为数组有序，那么假设现在的数是 $X_i$，那么现在的 $X_i$ 就是一个新的箱子堆的最顶上，然后先标记一下 $X_i$，接着从 $X_{i+1}$ 开始往后看，用一个变量 $s$ 统计这个箱子堆里的箱子数，如果箱子 $j$ 的力量值 $X_j$ 大于等于 $s$，那么这个箱子也可以放进堆里。否则，这个箱子堆里就不能放箱子了，那么答案加一。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[110],b[110];//b数组用来标记
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	int ans=0;
	for(int i=1;i<=n;i++){
		if(b[i]) continue;//如果箱子被标记了就说明这个箱子已经用了
		int s=1;b[i]=1;//标记箱子i
		for(int j=i+1;j<=n;j++)
			if(!b[j]&&s<=a[j])//看一下是否还能放箱子
				s++,b[j]=1;//标记箱子j
		ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF388A)

一道贪心题。

我们先将箱子的力量值从小到大排序，**优先将小的放顶上**，只要还能在底下放就放，否则就到下一个堆。

为什么要从小到大往下放呢？因为越小的力量值能放的位置就越少，所以尽早放一定是最优的。相反，力量值大的选择更多。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n, ans;
int a[105];
bool vis[105]; // vis[i] = 1 表示这个箱子已经用过了
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        vis[i] = 1;
        int cnt = 1; // 当前最顶上有 1 个
        for (int j = i + 1; j <= n; j++) {
            if (!vis[j] and cnt <= a[j])  {
                vis[j] = 1;
                cnt++;
            }
        }
        ans++;
    }
    cout << ans;
    return 0;
} 


```


---

## 作者：TheSky233 (赞：0)

## Description

有 $n$ 个箱子，每个箱子上面可以放 $a_i$ 个箱子，求最少需要多少堆箱子。

$1 \le n ,a_i\le 100$。

## Solution

把箱子按 $a_i$ 排序，然后我们从 $a_i$ 最小的开始取，取完一堆后重复直到没有可以被取的即可。

具体来说：

1. 记 $p$ 为堆数，$l$ 为剩下没取的箱子，$k$ 为这一堆已取的箱子。

2. 把 $i$ 从 $1 \sim n$ 扫一遍，把 $a_i > k$ 且未被标记的 $a_i$ 标记，并 $k \gets k+1$，$l \gets l-1$。

3. 重复第二步直至 $l=0$。

### 贪心证明

逆向思维，考虑已经放好的箱子 $a_l \sim a_r$，如果此时还有 $a_k$ 可以放在 $a_l$ 前面，显然更优，于是做法得证。

## Code

```cpp
void Solve(){
	read(n);
	F(i,1,n) read(a[i]);
	sort(a+1,a+n+1);
//	for(int i=1;i<=n;i++) write(a[i],' '); ENDL;
	int used=0,lft=n,box=0;
	while(true){
		used++;
		box=-1;
		for(int i=1;i<=n;i++){
			if(a[i]>box){
				lft--;
				a[i]=-iinf;
				box++;
			}
		}
//		for(int i=1;i<=n;i++) write(a[i],' '); ENDL;
		if(lft==0) break;
	}
	write(used,'\n');
}
```

---

## 作者：Erotate (赞：0)

这题我们直接贪心，先将数组从小到大排序，使得承重能力最大的箱子在最下面。然后只需要从前向后枚举，如果当前这个箱子被用过了，那就枚举下一个，否则就枚举这个箱子下面最多放多少个箱子。

证明一下贪心的正确性：显然，如果我们不令承重能力最大的箱子在最下面，那么放在最下面的箱子能放的的箱子数量就越少，就会导致堆数变多，与题意不符。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,a[N],used[N],ans;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i){
		if(used[i]) continue;
		used[i]=1;
		ans++;
		int tmp=1;
		for(int j=i+1;j<=n;++j)
			if(!used[j] && tmp<=a[j]){
				used[j]=1;
				tmp++;
			}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：sync_with_stdio (赞：0)

学校正好讲到这题就写篇题解把，趁还没有 $O(n \log n)$ 的题解赶紧来一发O_o

## 题意

有 $n$ 个箱子， 他们上边分别能放 $a_1,a_2, \dots a_n$ 个箱子，问最少要放成几堆。

## 贪心思路

对于一堆箱子来说，从抗压能力最差的箱子开始放，能继续放这个抗压能力的箱子就继续放，否则就换抗压能力更好的箱子。

## 贪心依据

1. 对于一个抗压能力为 $Q$ 的放在这堆最底下箱子 $a$ 来说，如有另一个箱子 $b$ 的抗压能力比它强（至少为 $Q+1$）,那么 $b$ 一定能放在 $a$ 的下面（废话）。

2. 当尽可能大的数不在堆底时，那么堆的总数量会增加，平均高度减小，显然不能这么干。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[500005];    //输入数组
queue<pair<int,int> > q;           //那个队列，pair<x,y> 表示a[] 种有x个y
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    sort(a+1,a+n+1);                    //必须排序
    a[n+1]=1000000007;
    int cnt=1;
    for(int i=2;i<=n+1;i++)             //统计a[] 种所有的“x个y”，方法有很多
    {
        if(a[i]!=a[i-1])
        {
            q.push(make_pair(cnt,a[i-1]));
            cnt=1;
        }
        else
            cnt++;
    }
    int nowbox=0,tot=n;                 //nowbox:这堆箱子的总堆叠数，tot:while()的条件、表示剩余的箱子数
    int ans=0;                          //答案，一共有多少堆
    while(tot>0)
    {
        //cout<<nowbox<<endl;
        if(nowbox<=q.front().second)    //如果能放
        {
            int loss=min(q.front().first,q.front().second-nowbox+1);        //一共能放loss（这种质量能放进去的最大箱子数）
            nowbox+=loss;
            tot-=loss;
            q.front().first-=loss;
            if(q.front().first<=0)                                      //不能放了就到队尾，不干扰其他箱子的放置
                q.pop();
            else
            {
                q.push(make_pair(q.front().first,q.front().second));
                q.pop();
            }
        }
        else                                        //这堆不能再放了qwq
        {
            ans++;
            nowbox=0;
        }
    }
    cout<<ans+1;                    //最后一对没有被统计
    return 0;
}

```


---

## 作者：ckk11288 (赞：0)

由于本题数据规模较小，可以用贪心求解。

而贪心策略的实现往往需要与排序结合，那么我们可以先将整个数组**从小到大排序**：这样可以确保策略正确（把尽量大的放在堆底）。

**贪心依据**：当最大的数不在堆底时，堆的数量会增加，而每个堆的高度则会相应减少（不符合题意）

**Code：**
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101],b[101],n,s,ans; //ans为计数器，b数组判断是否使用过
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	sort(a+1,a+1+n);//排序，默认从小到大
	for(int i=1;i<=n;i++)
	{
		if(b[i])//若已经用过
		{
			continue;//直接判断下一个
		}
		s=1;
		for(int j=i+1;j<=n;j++)
		{
			if(!b[j]&&a[j]>=s)//若可以放在当前堆上方且该箱子未使用过
			{
				s++;
				b[j]=1;//标记为已使用
			}
		}
		ans++;//计数器加一
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：York佑佑 (赞：0)

## 题意
有 $n$ 个箱子，每个箱子都有一个力量值 $a_i$，表示上面还可以放 $a_i$ 个箱子，求这些箱子最少能叠成多少堆。
## 分析
这道题很明显是贪心。并且数据范围不大，时间复杂度 $O(n^2)$ 肯定能过。

思考一下，力量值越小的箱子能放的位置就越少，力量值越大的箱子能放的位置就越多。所以力量值少的箱子要尽早放。那就可以先将数组**从小到大排序**。

接下来，我们遍历排序好的数组，优先将力量值小的箱子放在这一堆的最顶上，只要能在这一堆下放力量值更大的箱子就放，否则就放到下一个堆中。

需要考虑的还有：箱子会被重复放置。所以我们需要开另一个数组记录该箱子是否被放过。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[110],b[110],ans,cnt;
//a数组记录箱子的力量值，b数组记录箱子是否被放过 
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);//从小到大排序 
	for(int i=1;i<=n;i++)
	{
		if(b[i])	continue;//如果放过了就不能再放了 
		b[i]=1;
		int cnt=1;
		for(int j=i+1;j<=n;j++)
			if(!b[j]&&cnt<=a[j])//若该箱子未被放过且可以放在这一堆的下方 
			{
				b[j]=1;cnt++;//计数并标记为已经放过 
			}
		ans++;//有了一堆箱子,答案+1 
	}		
	cout<<ans;
	return 0;
}
```



---

