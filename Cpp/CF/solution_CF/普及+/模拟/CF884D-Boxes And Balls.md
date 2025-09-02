# Boxes And Balls

## 题目描述

Ivan has $ n $ different boxes. The first of them contains some balls of $ n $ different colors.

Ivan wants to play a strange game. He wants to distribute the balls into boxes in such a way that for every $ i $ ( $ 1<=i<=n $ ) $ i $ -th box will contain all balls with color $ i $ .

In order to do this, Ivan will make some turns. Each turn he does the following:

1. Ivan chooses any non-empty box and takes all balls from this box;
2. Then Ivan chooses any $ k $ empty boxes (the box from the first step becomes empty, and Ivan is allowed to choose it), separates the balls he took on the previous step into $ k $ non-empty groups and puts each group into one of the boxes. He should put each group into a separate box. He can choose either $ k=2 $ or $ k=3 $ .

The penalty of the turn is the number of balls Ivan takes from the box during the first step of the turn. And penalty of the game is the total penalty of turns made by Ivan until he distributes all balls to corresponding boxes.

Help Ivan to determine the minimum possible penalty of the game!

## 说明/提示

In the first example you take all the balls from the first box, choose $ k=3 $ and sort all colors to corresponding boxes. Penalty is $ 6 $ .

In the second example you make two turns:

1. Take all the balls from the first box, choose $ k=3 $ , put balls of color $ 3 $ to the third box, of color $ 4 $ — to the fourth box and the rest put back into the first box. Penalty is $ 14 $ ;
2. Take all the balls from the first box, choose $ k=2 $ , put balls of color $ 1 $ to the first box, of color $ 2 $ — to the second box. Penalty is $ 5 $ .

Total penalty is $ 19 $ .

## 样例 #1

### 输入

```
3
1 2 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
2 3 4 5
```

### 输出

```
19
```

# 题解

## 作者：Sooke (赞：11)

### 题意


你有 $n$ 个盒子和 $n$ 种颜色的球，第 $i$ 种颜色的球的数量是 $a_i$。

起初所有球都在第 $1$ 个盒子里，你希望让所有第 $i$ 种颜色的球都在第 $i$ 个盒子里。

于是你打算进行一系列操作。每次操作可以取出某个盒子中的所有球，腾空该盒子，但要扣除等于取出球数的点数，然后分成 $2$ 或 $3$ 组，将每组放到一个空盒子中。

求达到目标最少需要扣除的点数。

### 解题思路

如果把思维禁锢到分球上，固然是很难想出的。

不妨放弃分球这一目标，我们把它反过来，变成等价的目标——合并球。

大家应该都做过[合并果子](https://www.luogu.org/problemnew/show/P1090)这道题，其实正是本题 $k = 2$ 的情况。

可是一旦可以合并三堆球，不难想到，尽可能使用 $k = 3$ **似乎**是最优的？

其实只对了一半，如果合并三堆球，我们会少掉两堆，如果有四堆球，我们合并三堆，剩下两堆，只能使用 $k = 2$ 的合并，这样反而不优。

但正解已经水落石出了，思考一下，怎样会遇到上面的情况，导致不优呢？

没错，正是 $n$ 为偶数的时候，因为合并三堆每次少两堆，一定最后剩下两堆只能单独合并。与其这样，不如在一开始就使用合并最少的两堆，减去一堆，剩下的就可以三堆三堆的合并了。

### 代码实现

$CF$ 常识：开 $long\ long$。

```cpp
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

const int maxN = 200005;

typedef long long lol;

int n, t;
lol ans;
std::priority_queue<lol, std::vector<lol> , std::greater<lol> > q;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) { std::cin >> t; q.push(t); }
    if (n % 2 == 0) {
        lol x = q.top(); q.pop();
        lol y = q.top(); q.pop();
        q.push(x + y); ans += x + y;
    }
    while (q.size() >= 3) {
        lol x = q.top(); q.pop();
        lol y = q.top(); q.pop();
        lol z = q.top(); q.pop();
        q.push(x + y + z); ans += x + y + z;
    }
    std::cout << ans << std::endl;
    return 0;
}
```

---

## 作者：ikunTLE (赞：9)

[题目传送门](https://www.luogu.com.cn/problem/CF884D)

### 思路

这道题很像[合并果子](https://www.luogu.com.cn/problem/P1090)，不同点是这道题可以选择合并 $2$ 个数，也可以合并 $3$ 个数。没有做过合并果子的建议先去做一做。

与合并果子一样，我们可以用优先队列（`priority_queue`）将所有数存起来，将小的数放到队列的首端。可以发现，我们每一次操作尽量合并 $3$ 个数，使最终的代价最小。

然而少不了一些毒瘤数据，例如：`1 4 4 4 4 4`。若按照上文所述，第一次合并 $1,4,4$ 和 $4,4,4$，第二次合并 $9,12$，最终代价是 $42$。然而，正解是先合并 $1,4$ 和 $4,4,4$，然后合并 $4,5,12$，代价为 $38$。

我们发现，当 $n$ 为整数时，最后一次操作只能合并 $2$ 个数。也就是说，在前面的操作中，多了一次合并，使得最终代价更大。为了解决这个问题，我们可以在初始化优先队列时，可以加入一个 $0$，这样不影响合并的计算或最终代价。

**注意事项**

- 不开 `long long` 见祖宗，特别还要注意优先队列中也要开 `long long`。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
priority_queue<long long,vector<long long>,greater<long long>>pq;
long long sum;//记录最终代价
int main(){
	int n=read();
	for(int i=1;i<=n;++i)
		pq.push(read());
	if(n%2==0)
		pq.push(0);
	while(pq.size()>1){
		//每一次选3个数为最优
		long long x=pq.top();
		pq.pop();
		long long y=pq.top();
		pq.pop();
		long long z=pq.top();
		pq.pop();
		long long temp=x+y+z;
		sum+=temp;//更新代价
		pq.push(temp);
	}
	printf("%lld",sum);
	return 0;
}
```

---

## 作者：fairfriendZ (赞：5)

这道题我是打完荷马史诗后看的（因为讨论区有人说是双倍经验。

首先没思路，但仔细想想，逆向思考，其实就是哈夫曼树计算权值和。

又仔细想想，确实可以套用荷马史诗的思路，这题相较于史诗最大的区别在它只可能是二或三叉，而我们依常识可知，三叉应该尽可能得多。

但它是道绿题，所以大概率有些特殊情况。好，这下我们直接不考虑特殊情况（因为太懒了放弃推导），直接使用k叉哈夫曼。

因为不考虑它可能的二叉或三叉性，而是直接使它全部满足三叉，那么我们只需要往里面插入一些不影响权值和的 0 点，使得每一个分叉都满足三叉。这样一来，0 点只是起一个补充节点的作用。

        #include<bits/stdc++.h>
        using namespace std;
        struct ass{
            long long id,h;//h是长度 
            bool operator <(const ass &a)const{//重载运算符 
        		if(a.h!=h)return h>a.h;
        		else{
        			return id>a.id;
        		}
        	}
        };
        long long ans1;
        priority_queue<ass>q;//小根堆 
        int main(){
            long long n;
        	scanf("%lld",&n);
            for(int i=1;i<=n;i++){
                long long w;
        		scanf("%lld",&w);
                q.push((ass){i,w});//先只放，不建堆，因为重载运算符，故已排序 
            }
            int k=3;
            long long sum=0,minh=1e9;
            long long cnt=n;
            while((cnt-1)%(k-1)==1)q.push((ass){++cnt,0});//为使 k 叉树在最后只剩下1个点，补充一些无用的权值为0的点 ，（ cnt - 1 ） % ( k - 1)== 1 是为了让下一轮有三个叉可加
            while(q.size()>=k){	
        		sum=0;
        	    for(int i=1;i<=k;i++){	    
        		    	ass t=q.top();
        		    	sum+=t.h;
        		    	q.pop();
        		}ans1+=sum;
        		q.push((ass){++cnt,sum});//每次将本轮相加值放入新节点 
        	}
        	printf("%lld\n",ans1);//输出答案 
            return 0;
        }
这道题思路应该是对的，但洛谷上交不了，CF 又没找到，但能过上面有篇题解的毒瘤数据。

---

## 作者：Forever1507 (赞：4)

~~为什么这题会有蓝啊~~

典型的逆向思维题，往拆分的方向显然无果，只能浪费脑细胞，我们可以将它反过来，即给出 $n$ 个球，第 $i$ 个的权值为 $i$，每次可以合并 $2$ 个或 $3$ 个，每次合并会消耗被合并球的权值和，求最小消耗。

欸，想到这里，我寻思着这不就[合并果子](https://www.luogu.com.cn/problem/P1090)吗？只不过合并数量不同而已，显然一次合并 $3$ 个会比合并 $2$ 个优，那不就是一棵**三叉哈夫曼树**吗？用小根堆瞎搞搞不就出来了吗？

到这里已经分析差不多了，但还有最后一个问题：一定能保证每次合并 $3$ 个能刚好合并完吗？显然不是，当 $n$ 为**偶数**时，**最后一定会剩下两个**，那么反而劣，一开始就合并两个才会有最小值。

那么，整体策略就有了：若 $n$ 为偶，先取最小的两个合并并统计代价，之后只要优先队列里还有至少三个点，就将其合并并统计，最后把统计出来的总代价输出即可。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long//不开ll见祖宗！
using namespace std;
int n,a[200005];
priority_queue<int,vector<int>,greater<int> >pq; //定义小根堆
int ans;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		pq.push(a[i]);
	}
	if(n%2==0){//若是偶数先合并两个
		int cur1=pq.top();
		pq.pop();
		int cur2=pq.top();
		pq.pop();
		ans+=cur1+cur2;
		pq.push(cur1+cur2);
	}
	while(pq.size()>=3){//3个3个合并
		int cur1=pq.top();
		pq.pop();
		int cur2=pq.top();
		pq.pop();
		int cur3=pq.top();
		pq.pop();
		ans+=cur1+cur2+cur3;//统计
		pq.push(cur1+cur2+cur3);
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Stone_Xz (赞：2)

## [题目传送门](https://www.luogu.com.cn/problem/CF884D)

## 前置知识：

[哈夫曼树](https://oi-wiki.org/ds/huffman-tree/?query=%E5%93%88%E5%A4%AB%E6%9B%BC%E6%A0%91)

## 分析

首先转换一下题意，将分球转换为合并球。跟 [合并果子](https://www.luogu.com.cn/problem/P1090) 这题很相似了。可以用哈夫曼树去做。

然后我们考虑合并，是选三堆还是两堆？显然是选合并三堆更优。但是会出现问题，如果最后一次合并没有三堆可以参与，说明之前的某一次合并就多了一个数（因为这个数可以移到最后一次合并），答案会更大。出现这种情况，我们可以先合并两堆，然后再按正常的思路来搞。即加入一个为 $0$ 的点，不影响答案，但可以使第一次合并只有两个原数列的点。

分析到这里，这道题其实就是 [P2168 [NOI2015] 荷马史诗](https://www.luogu.com.cn/problem/P2168) 的 $k = 3$ 的情况了，这里直接 copy 了荷马史诗的代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, k, cnt, ans, a[200005];

struct node
{
	int tot, dep;
	bool operator < (const node &B) const
	{
		if(tot != B.tot) return tot > B.tot;
		return dep > B.dep;
	}
};
priority_queue<node> pq;

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n;
	k = 3;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		pq.push((node){a[i], 0});
	}
	if((n - 1) % (k - 1) != 0) cnt = k - 1 - ((n - 1) % (k - 1));
	for(int i = 1; i <= cnt; i++)
		pq.push((node){0, 0});
	cnt = cnt + n;
	while(cnt >= 2)
	{
		int sum, maxi;
		sum = maxi = 0;
		for(int i = 1; i <= k; i++)
		{
			sum += pq.top().tot;
			maxi = max(maxi, pq.top().dep);
			pq.pop();
		}
		pq.push((node){sum, maxi + 1});
		ans += sum;
		cnt -= k - 1;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：lcfollower (赞：2)

优先队列板子。

我们把思维不定在分球上，定在**合并**球上。

那么新的题意是：给定 $n$ 种球的数量 $a_i$，每次可以合并 $2$ 个或者 $3$ 个，然而每次合并会增加 $2$（$3$）堆球的数量之和，求最小的价值。


---


考虑每次合并三个球，设第 $i$（$1\le i\le 3$） 个球的价值为 $b_i$，合并顺序为 $k_1$，$k_2$，$k_3$：

- 两次合并，每次合并两个球，则价值为 $a_{k_1}\times 2 + a_{k_2}\times 2 + a_{k_3}$。

- 一次合并，每次合并三个球，则价值为 $a_{k_1} + a_{k_2} + a_{k_3} = a_1 + a_2 + a_3$。

这就是一个三叉哈夫曼树问题，如果是 $k$ 叉哈夫曼树，请[出门左转至《荷马史诗》](https://www.luogu.com.cn/problem/P2168)。

当然我们不难遇到毒瘤数据，当 $n$ 为偶数时，先合并最小的 $2$ 个球，然后再每次合并最小的 $3$ 个球最划算。然而除了最后一步合并最小的 $3$ 个球，最后一步合并 $2$ 个球一般就会出错。

所以我们需要在 $n$ 为偶数是往优先队列里添加一个 $0$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define up(i,x,y) for(register int i=x;i<=y;++i)

using namespace std;

inline int read(){int x=0;bool f=0;char ch=getchar();while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return (f?-x:x);}
inline void write(int x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10|48);}
inline void writeln(int x){write(x),putchar('\n');}
int n ,sum;
priority_queue <int ,vector <int> ,greater<int> > q;
signed main(){
  n = read();
  up(i,1,n){int x = read();q.push(x);}
  if(!(n & 1)) q.push(0);
  while(q.size() > 1){
    int x = q.top();
    q.pop();
    int y = q.top();
    q.pop();
    int z = q.top();
    q.pop();
    sum += x + y + z;
    q.push(x + y + z);
  } writeln(sum);
  return 0;
}
```

---

## 作者：Stars_Traveller (赞：1)

## 分析  
若按照题面的拆分去思考的话没什么想法。考虑逆向思维，将题面可以转化为把 $n$ 个球合并成一堆，每次可以合并 $2$ 堆 或 $3$ 堆，问最小花费。

这时我们可以往构造一棵二叉或三叉的哈夫曼树去想。明显构造三叉的哈夫曼树也就是每次合并三堆球，这样做每个点的深度明显会比二叉的小一点。

那做法就很明显了，我的写法是类似 [P2168 [NOI2015] 荷马史诗](https://www.luogu.com.cn/problem/P2168) 那道题的写法的，但其实可以写成像 [P1090 [NOIP2004 提高组] 合并果子 / [USACO06NOV] Fence Repair G](https://www.luogu.com.cn/problem/P1090) 那样的，只是每次合并三堆，然后特判一下 $n$ 为偶数时先单独合并两堆再每次合并三堆。

## 我的写法
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, cnt, ans, k;
struct node
{
	int id, w;
	friend bool operator <(node a,node b)
	{
		if(a.w==b.w)return a.id>b.id;
		return a.w>b.w;
	}
};
priority_queue<node> q;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n;
	k=3;
	for(int i=1;i<=n;++i)
	{
		int x;
		cin>>x;
		q.push((node){i,x});
	}
	cnt=n;
	while((cnt-1)%(k-1))
	{
		q.push((node){++cnt,0});
	}
	while(q.size()>=k)
	{
		int sum=0;
		for(int i=1;i<=k;++i)
		{
			node cur=q.top();
			q.pop();
			sum+=cur.w;
		}
		ans+=sum;
		q.push((node){++cnt,sum});
	}
	cout<<ans;
}

---

## 作者：Stars_visitor_tyw (赞：0)

## CF884D Boxes And Balls 题解
### 分析
考虑将题目转化为每次合并 $3$ 堆来思考。因为每次尽可能合并三堆比每次合并两堆要更优（构造哈夫曼树可以发现）

当然，当 $n$ 为偶数的时候需要把前两堆先合并，剩下的就可以三堆三堆合并了。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, a[200005], ans;
priority_queue<int> q;
signed main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        q.push(-a[i]);
    }
    if(!(n&1))
    {
        int x, y;
        x=q.top();
        q.pop();
        y=q.top();
        q.pop();
        ans+=-x-y;
        q.push(x+y);
    }
    while(q.size()>=3)
    {
        int x, y, z;
        x=q.top();
        q.pop();
        y=q.top();
        q.pop();
        z=q.top();
        q.pop();
        ans+=-x-y-z;
        q.push(x+y+z);
    }
    cout<<ans;
}

---

## 作者：GJX_Algorithm (赞：0)

# CF884D
## 题目描述
- 现在你有 $n$ 个颜色的盒子与球，给定每种颜色的球的数量。

- 一开始所有颜色的球都在 1 号盒子里，你想让第 $i$ 种颜色的球都在第 $i$ 个盒子里。

- 你现在可以取出某个盒子的所有球并分成 2 至 3 组放进任意盒子里，但要扣除取出球的点数。

- 问最少扣除的点数。

## 解题思路
- 先给出此题的[弱化版](https://www.luogu.com.cn/problem/P1090)和[升级版](https://www.luogu.com.cn/problem/P2168)，分别是 2 种合并与 $k$ 种合并。

- 不难想到将分球转换为合球。因为我是先做的荷马史诗（即上述升级版），所以就直接套荷马史诗的思路，直接补上不对答案做贡献的权值为 0 的点，使得其变为三叉树.

## AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int w, id;
	bool operator < (const node &b) const
	{
		if (w == b.w) return id > b.id;
		return w > b.w;
	}
};
priority_queue<node> pq;
int n, k, a[400005];
signed main ()
{
	ios::sync_with_stdio (0);
	cin.tie (0), cout.tie (0);
	cin >> n;
	k = 3;
	for (int i = 1; i <= n; i++) 
		cin >> a[i], pq.push ({a[i], i});
	while ((n - 1) % (k - 1) == 1) pq.push({0, ++n});
	int cnt = n + 1, ans = 0;
	while (pq.size () > 1)
	{
		int sum = 0;
		for (int i = 1; i <= k; i++) 
		{
			int w1 = pq.top ().w;
			pq.pop ();
			sum += w1;
		}
		pq.push({sum, cnt++});
        ans += sum;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Yizhixiaoyun (赞：0)

[博客园食用](https://www.cnblogs.com/yizhixiaoyun/p/17094020.html)

[题目传送门](https://www.luogu.com.cn/problem/CF884D)

## 题目分析

开始还真没看出来这题跟 [$\text{P1090}$ 合并果子](https://www.luogu.com.cn/problem/P1090) 的关系。

其实只要逆向思考，把拆分看成效果一样的合并就可以了。而与合并果子不同的是，在这题当中我们可以分成 $3$ 组，显然这样比分成 $2$ 组更优。

按照以下思路，不难写出以下代码（其实就是将合并果子的板子改一下）：

```cpp
while(q.size()>=3){
	int top1=q.top();q.pop();int top2=q.top();q.pop();int top3=q.top();q.pop();
	ans+=top1+top2+top3;
	q.push(top1+top2+top3);
}
```

这样我们就顺利过掉了第一个样例。

接着观察第二个样例，发现当 $n$ 为偶数时，如果 $3$ 组分下去，最后一定会剩下 $2$ 组需要单独合并。那我们不如在开始的时候就将最小的 $2$ 组进行合并，这样就解决了。

## 贴上代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define debug puts("Shiina_Mashiro_kawaii")
#define ok puts("Yes")
#define no puts("No")
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int maxn=1e5+5;
int n;
int ans;
int a[maxn];
priority_queue<int,vector<int>,greater<int> > q;
inline void init(){
	n=read();
	for(register int i=1;i<=n;++i) q.push(read());
}
signed main(){
	init();
	if(n%2==0){
		int top1=q.top();q.pop();int top2=q.top();q.pop();
		ans+=top1+top2;
		q.push(top1+top2);
	}
	while(q.size()>=3){
		int top1=q.top();q.pop();int top2=q.top();q.pop();int top3=q.top();q.pop();
		ans+=top1+top2+top3;
		q.push(top1+top2+top3);
	}
	printf("%lld",ans);
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF884D)
## 思路
这题的本意是让我们进行分球操作，但是我们完全可以把它们进行反操作，即合并球操作，这时我们就会发现这题跟[**合并果子**](https://www.luogu.com.cn/problem/P1090)差不多，只不过[**合并果子**](https://www.luogu.com.cn/problem/P1090)是[**二叉哈夫曼树**](https://oi-wiki.org/ds/huffman-tree/)，而这道题是[**三叉哈夫曼树**](https://oi-wiki.org/ds/huffman-tree/)，也就是说我们只需要每次取出来三个队顶元素就行了，这时候程序的大体框架就已经出来了。但是我们再考虑一种特殊情况：如果 $n$ 为**偶数**，这时依旧按照正常思路走的话，最后肯定会**剩下两个**，出来的并不是最优结果，所以需要特判来**优先处理**，先取出两个队顶元素，减去一堆，让 $n$ 变成奇数，才可以进行正常操作：

```cpp
if(n % 2 == 0){//若n为偶数，先合并两个
	long long x = q.top(); q.pop();
	long long y = q.top(); q.pop();
	sum += x + y;
	q.push(x + y);
}
while(q.size() > 2){
   //取最小的三个值
	long long x = q.top(); q.pop();
	long long y = q.top(); q.pop();
	long long z = q.top(); q.pop();
	sum += x + y + z;
	q.push(x + y + z);//入队，进行下一步的运算
}
```


------------

注意事项：
- 循环的条件是队列的数大于 $2$ 个，而不是非空，这样才能保证每次都有三个元素可以合并
- 小根堆和求和的变量都需要开 long long
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
priority_queue<long long, vector<long long>, greater<long long> > q;//定义小根堆
int main(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++){
		int x;
		cin >> x;
		q.push(x);//入队
	}
	long long sum = 0;//求和
	if(n % 2 == 0){//特判，当n为偶数
		long long x = q.top(); q.pop();
		long long y = q.top(); q.pop();
		sum += x + y;
		q.push(x + y);
	}
	while(q.size() >= 3){
		long long x = q.top(); q.pop();
		long long y = q.top(); q.pop();
		long long z = q.top(); q.pop();
		sum += x + y + z;
		q.push(x + y + z);
	}
	cout << sum << endl;
}
```


------------

### [已AC](https://www.luogu.com.cn/record/97467066)

---

## 作者：yuheng_wang080904 (赞：0)

## 题意

有 $n$ 个盒子和 $n$ 种颜色的球，第 $i$ 种颜色的球的数量为 $a_i$。

起初所有球都在第 1 个盒子里，你希望让所有第 $i$ 种颜色的球都在第 $i$ 个盒子里。

于是你打算进行一系列操作。每次操作可以取出某个盒子中的所有球，腾空该盒子，但要扣除等于取出球数的点数，然后分成 2 或 3 组，将每组放到一个空盒子中。

求达到目标最少需要扣除的点数。

## 思路

我们在阅读这道题时，可能会联想到合并果子，哈夫曼编码……

我们把这道题的题意进行适当的调整：有 $n$ 个数 $a_1,a_2,…,a_n$，两个或三个进行合并，代价为那些数的和，求最小代价。

这下子题意就明朗了，思路也清晰了，我们可以用一个 
```cpp
priority_queue<long long,vector<long long>,greater<long,long> >pq
```
这个小根堆来维护那些数。如果 $n$ 为奇数，那么一定是每次三个较小数合并，最终并成一个，这样一定是最优解。如果 $n$ 为偶数，那么添加 $a_{n+1}=0$，然后按照 $n$ 为奇数的方法去做，一定仍是最优解。

注意数据范围，一定要开
```cpp
long long
```
!

## 代码

接下来放上我简短的代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n,ans;
priority_queue<ll,vector<ll>,greater<ll> >pq;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
	ll a;
	cin>>a;
	pq.push(a);
    }
    if(n%2==0)pq.push(0ll);
    while(pq.size()>1){
	ll a=pq.top();
	pq.pop();
	ll b=pq.top();
	pq.pop();
	ll c=pq.top();
	pq.pop();
	pq.push(a+b+c);
	ans+=(a+b+c);
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：信息学carryHarry (赞：0)


### 题意

你有 $n$ 个盒子和 $n$ 种颜色的球，第 $i$ 种颜色的球的数量是 $a_i$。

起初所有球都在第 $1$ 个盒子里，你希望让所有第$i$种颜色的球都在第 $i$ 个盒子里。

于是你打算进行一系列操作。每次操作可以取出某个盒子中的所有球，腾空该盒子，但要扣除等于取出球数的点数，然后分成 $2$ 或 $3$ 组，将每组放到一个空盒子中。

求达到目标最少需要扣除的点数。
### 策略
一句话：转换成 $n$ 个盒子 $n$ 种颜色的球，合并到 $1$ 个盒子，每一次的点数都是两个盒子的球数之和。
### 区别：
每次可以合并 $2$ 个盒子，也可以合并 $3$ 个盒子。
### code:
```cpp
#include<bits/stdc++.h>

using namespace std;
const int N=2e5+5;
int n,a[N];
priority_queue<long long,vector<long long>,greater<long long> > pq;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		pq.push(a[i]);
	}
	long long ans=0;
	if(n%2==0)
	{
		long long x=pq.top();
		pq.pop();
		long long y=pq.top();
		pq.pop();
		pq.push(x+y);
		ans+=x+y;
	}
	while(pq.size()>=3)
	{
		long long x=pq.top();
		pq.pop();
		long long y=pq.top();
		pq.pop();
		long long z=pq.top();
		pq.pop();
		pq.push(x+y+z);
		ans+=x+y+z;
	}
	cout<<ans;
	return 0;
}

```
### [AC记录](https://www.luogu.com.cn/record/55194944)

---

## 作者：Weekoder (赞：0)

### 思路

$${\Large\boxed{\text{LiveDream}}}$$

使用逆向思维。假设一开始第 $i$ 种颜色的球都在第 $i$ 个盒子里，那么问题就转化为了每次将 $2\sim3$ 种球放入 $1$ 号盒子中（相当于合并），代价为球的数量之和。这不就是一个**合并果子**问题吗？也就是说，我们可以对 $n$ 种球构建哈夫曼树，只不过是 $2$ 或 $3$ 叉的哈夫曼树。那么答案显然为树上叶子结点的带权路径长度和。

一个结点的带权路径长度被定义为结点的权值乘以结点到根的距离。那么，在叶子结点数 $n$ 和结点权值 $a_i$ 不变的情况下，如果当前结点到根的距离越小，也就是树的深度越小，答案就越优。容易发现，在构造 $k$ 叉哈夫曼树时，$k$ 越大，树的深度越小。这给了我们一个提示：一次性合并三个点会比合并两个点更优。这对于样例一没有问题，可样例二就出了差错了。我们发现，在三个三个合并后，最后剩下的两个巨大的点需要两两合并——这样做的代价是巨大的，而且是 $n$ 是偶数导致的。因为把三个点合并，就相当于减少了两个点，而我们的目标是把点数减成 $1$，也就是合并成一堆大果子。但如果 $n$ 是偶数，最后就会减成 $0$！所以，这个时候就必须在 $n=2$ 的时候两两合并，使结点数减 $1$， $n\gets n-1$。可既然要使用代价较大的两两合并，又为什么不在一开始结点权值较小的时候合并呢？于是，答案就呼之欲出了，总结一句话就是：

当 $n$ 为偶数时，先拿出来两个权值最小的点合并，剩下的点三个三个合并，统计合并时的权值和累加即为答案。

代码：

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

int n, ans;

priority_queue<int, vector<int>, greater<int> > pq;

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
    for (int i = 1, a; i <= n; i++) {
        cin >> a;
        pq.push(a);
    }
    if (n % 2 == 0) {
        int x = pq.top(); pq.pop();
        int y = pq.top(); pq.pop();
        ans += x + y;
        pq.push(x + y);
    }
    while (pq.size() >= 3) {
        int x = pq.top(); pq.pop();
        int y = pq.top(); pq.pop();
        int z = pq.top(); pq.pop();
        ans += x + y + z;
        pq.push(x + y + z);
    }
    cout << ans;
	return 0;
}
```

---

