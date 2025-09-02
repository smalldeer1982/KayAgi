# [GCJ 2010 Qualification] Theme Park

## 题目描述

过山车真有趣！似乎每个来到主题公园的人都想乘坐过山车。有些人单独前来；有些人则结伴而来，并且他们不愿意分开，必须一起上车。每个乘坐过山车的人都想再玩一次。每人每次乘坐需要支付 1 欧元；你的任务是计算今天过山车能赚多少钱。

过山车每次最多可容纳 $k$ 人。人们按组排队等候。每次上车时，按顺序让一个个小组上车，直到没有剩余小组或下一个小组无法全部上车为止；然后过山车就会出发，无论是否坐满。每次游玩结束后，所有乘客会按照原顺序重新排到队伍末尾。过山车一天会运行 $R$ 次。

例如，假设 $R=4$，$k=6$，有四个小组，人数分别为：$1$、$4$、$2$、$1$。第一次运行时，前两个小组 $[1, 4]$ 上车，还剩一个空位（$2$ 人的小组无法全部上车，$1$ 人的小组不能插队）。然后这两个小组排到队尾，队伍变为 $2$、$1$、$1$、$4$。第二次运行时，$[2, 1, 1]$ 共 $4$ 人上车。此时队伍变为 $4$、$2$、$1$、$1$。第三次运行时，$[4, 2]$ 共 $6$ 人上车。此时队伍变为 $[1, 1, 4, 2]$。最后一次运行时，$[1, 1, 4]$ 共 $6$ 人上车。最终，过山车一共赚了 $21$ 欧元。

## 说明/提示

**样例说明**

- $1 \leqslant T \leqslant 50$。
- $g_{i} \leqslant k$。

**小数据范围（10 分，测试点 1 - 可见）**

- $1 \leqslant R \leqslant 1000$。
- $1 \leqslant k \leqslant 100$。
- $1 \leqslant N \leqslant 10$。
- $1 \leqslant g_{i} \leqslant 10$。

**大数据范围（23 分，测试点 2 - 隐藏）**

- $1 \leqslant R \leqslant 10^{8}$。
- $1 \leqslant k \leqslant 10^{9}$。
- $1 \leqslant N \leqslant 1000$。
- $1 \leqslant g_{i} \leqslant 10^{7}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
4 6 4
1 4 2 1
100 10 1
1
5 5 10
2 4 2 3 4 2 1 2 1 3```

### 输出

```
Case #1: 21
Case #2: 100
Case #3: 20```

# 题解

## 作者：zhouxiaodong (赞：1)

众所周知，预处理是个好东西。大概是以下的步骤：

先初始化能搭载的游客总数和下一个需要检查的起始位置。

再模拟游乐设施的搭载过程，跳过周期，记录钱数。

最后手动模拟剩余不足的轮次。

so？你学会了吗？
``````````cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
struct node
{
	int x;
	int y;
};
int solve()
{
	int r,k,n;
	cin>>r>>k>>n;
	vector<int>a(n);
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	int cu=0;
	vector<int>rs(n,0);
	vector<int>np(n,0);
	for(int i=0;i<n;i++)
	{
		int sum=0;
		int j=i;
		int cnt=0;
		while(1)
		{
			if(sum+a[j]>k)
			{
				break;
			}
			sum+=a[j];
			cnt++;
			j=(j+1)%n;
			if(j==i)
			{
				break;
			}
		}
		rs[i]=sum;//累加上车人数
		np[i]=j;//下一个位置
	}
	unordered_map<int,node>b;//哈希表
	int ans=0;
	int ro=0;//轮数
	int cl=0;//周期
	int cs=0;//金额
	while(ro<r)
	{
		if(b.count(cu))//有周期
		{
			auto p1=b[cu];
			int p2=p1.x;
			int p3=p1.y;
			cl=ro-p3;
			cs=ans-p2;
			int re=r-ro;
			int cy=re/cl;//能跳过的完整周期
			ans+=cy*cs;
			ro+=cy*cl;//跳过周期
			while(ro<r)
			{
				ans+=rs[cu];
				cu=np[cu];
				ro++;
			}
			break;
		}
		b[cu]={ans,ro};//记录状态
		ans+=rs[cu];
		cu=np[cu];
		ro++;
	}
	return ans;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cout<<"Case #"<<i<<": "<<solve()<<"\n";
	}
	return 0;
}
``````````
时间复杂度大概是：$O(N^2 + T \times N)$，绝对通过（除非数据大大大加强）。

:::info[文件袋]
[一篇网上的哈希讲解](https://blog.csdn.net/weixin_45031801/article/details/141572449)

[又是一篇网上的哈希讲解](https://blog.csdn.net/qq_58291701/article/details/123058048)

~[听说洛谷又又又又又更行了，看看新渲染好不好用](https://www.luogu.com.cn/discuss/1115842)~

[我竟是最优解](https://www.luogu.com.cn/record/list?pid=P13389&user=&orderBy=1&status=&language=&page=1)！
:::

---

## 作者：lcfollower (赞：0)

前言
---

我们来看看这个：

![](https://cdn.luogu.com.cn/upload/image_hosting/2olcd866.png)

注意标签，是模拟和数学。

今天我一定要把标签加上一个**倍增**（而且官解也没提到）！

列文虎克
---

:::warning[$\KaTeX$ 丢失]
每人每次乘坐需要支付 1 欧元；
这句话的 $1$ 应为 $\KaTeX$。
:::

正文
---

:::info[注意]
本文的时间复杂度带一只 log，比目前唯一题解的时间复杂度高，但是稳拿[当前最优解](https://www.luogu.com.cn/record/list?pid=P13389&orderBy=1&status=&page=1)，请读者仔细阅读。

并且本文的变量名取自题目，请读者仔细甄别。

下文中如果出现 $n$ 则都为 $N$，不要搞错。

:::

废话不多说，开始。

首先我们有一个暴力，对于每一次过山车都暴力 $\mathcal O(N)$ 查找这回做过山车的人，时间复杂度为 $\mathcal O(TRN)$，期望与实际得分 $30$ 分，记录可以翻别人的，~~我没写~~。

然后我们还有目前唯一题解的找循环节的方法，也是最直接的方法。

考虑到每个节点最多出度为 $1$，不然肯定成环。所以环的长度最坏为 $\mathcal O(N)$，这也保证了目前唯一题解的正确性，时间复杂度为 $\mathcal O(TN)$。

---

现在我们思考：暴力太慢了，我们每做一次过山车要暴力，能不能优化呢？

有的，兄弟有的，我们可以**破环为链**，然后二分下标，因为**组内人数非负**，所以二分具有单调性，也保证了正确，这样时间复杂度为 $\mathcal O(R\log N)$，期望与实际得分也是 $30$ 分，具体也可以看别人记录，~~我没写~~。

然后我们思考：$R$ 太浪费时间了，有没有快速的方法？

有的，兄弟有的，我们可以倍增！

具体地，我们记 $jump_{i ,0}$ 为以组别 $i$ 为**开头**进行**一趟**过山车，能够做到 $jump_{i ,0} - 1$ 组，特别地，这里是环，所以要**破环成链**。

举个例子，比如 $g=[1,4,7,1]$，$k=10$，那么 $jump_{3,0} = 2$，因为第 $3$，$4$，$1$ 组可以一起乘坐过山车，而第 $2$ 组不行。注意我们上面要**减一**，这样我们就是直接跳到了下一个一起坐过山车的**开头**的组别。

然后我们记 $jump_{i ,j}$ 为从 $i$ 开头，一起做了 $2^j$ 趟过山车，第 $2^j + 1$ 趟过山车的起点组别下标。

:::info[注意]
不要理解错 $jump$ 的含义，这里指让我们的不良商家尽可能~~赚钱~~塞人进去，塞不下去才算一趟过山车，而不是一人一组（应该都看得懂吧）。
:::

这样我们可以对 $R$ 进行二进制拆分，然后直接跳。

比如 $R = 1101_{(2)} = 2^0 + 2^2 + 2^3$，我们设 $x = 1$（起始位置），于是跳一次是 $jump_{1 ,3}$（可以正着写，我习惯反着），第二次是 $jump_{jump_{1 ,3} ,2}$，第三次是 $jump_{jump_{jump_{1 ,3} ,2} ,0}$，过程中我们用 $x$ 记录，就可以用代码 `jump[x][i]` 来书写。

可是我们还少了什么？

没错，是我们游客被不良商家欺骗的欧元！

于是我们记 $sum_{i ,j}$ 为以 $i$ 开头，一起做了 $2^j$ 趟过山车，游客所花的~~被欺骗的~~欧元数，这样我们再记录一个变量 $ans$，每次让 $ans\gets ans + sum_{x ,i}$ 即可。

假设我们有方法知道 $\forall i \in [1 ,N]\cap \mathbb{N} ,jump_{i ,0} ,sum_{i ,0}$，怎么求解 $\forall j \in [1 ,\log_2{R}]\cap \mathbb{N} ,jump_{i ,j} ,sum_{i ,j}$ 呢？我们就可以用倍增的转移方法，即 $jump_{i ,j} = jump_{jump_{i ,j - 1} ,j - 1}$，$sum_{i ,j} = sum_{i ,j - 1} + sum_{jump_{i ,j - 1} ,j - 1}$（$1\le j\le \log_2{R}$，这里如果理解了 ST 表还是很容易理解哒，如果不能理解 $jump$ 试试回想一下它的定义。

:::info[提醒]
不要写成 $sum_{i ,j} = sum_{jump_{i ,j - 1} ,j - 1}$，这样只考虑了右半段，而我们是把区间分成左右两互不相交的段来更新。

也不要写成 $sum_{i ,j} = sum_{i ,j - 1} + sum_{sum_{i ,j - 1} ,j - 1}$（~~比如我~~），原因显然（归根究底 ST 表写惯了，没有动脑或者没有彻底理解造成的）。
:::

然后我们有什么方法求得 $jump_{i ,0}$ 和 $sum_{i ,0}$ 呢（$i$ 为正整数且 $1\le i\le N$）？我们可以使用暴力，这样时间复杂度为 $\mathcal O(N^2)$；也可以二分，时间复杂度为 $\mathcal O(N\log N)$。

但是，我们考虑到**人数非负**，那么我们的目标点也是单调递增的。于是我们使用**双指针**维护。

这里我们需要通过分析题目条件来得到更优的解法，比如如果题目满足四边形不等式我们可以想到决策点单调递增，从而优化时间复杂度。

然后就做完了，时间复杂度为 $\mathcal O(TN\log R)$，瓶颈在于更新 $jump$ 和 $sum$。

:::info[关于是否清空]
多组数据需要清空嘛？

其实不用，这里不清空也不会爆零两行泪。

因为我们 $jump$ 和 $sum$ 都是由左右两边直接用 `=` 合成，而左右两边的值都是预处理过的或者更新过的，也不会用到不必要的空间，所以其实不用清空，清空既多次一举，还会增加时间复杂度。
:::

:::info[真的就这样能 AC 了嘛]

实则不然，如果所有人一下子都能做过山车（即 $\sum\limits_{i = 1}^N g_i \le k$，指针 $r$ 可能要找好几轮，可能会 TLE（仔细观察数据范围）。

这样双指针的作用就凸显不大。所以我们特判这种情况，答案即为 $\sum\limits_{i = 1}^N g_i \times R$。

:::

那么：

:::success[恭喜你]
成功用非官解和目前唯一题解的方法 AC 这题！！！
:::

最后我想说的是，这是洛谷渲染更新后蒟蒻的第一篇题解，不喜勿喷。

::::warning[警告]

洛谷太善了，你们看看这是什么：

:::align{center}

![](https://cdn.luogu.com.cn/upload/image_hosting/3puas3ul.png)
:::

因此蒟蒻发出号召：

不要点这个按钮！它会复制我的代码！你就有可能某天早上起来发现自己名字颜色非常~~好~~难看！

::::

下面蒟蒻献上代码：

::::info[代码]

:::error[不要]
复制我的代码，我的代码不全。
:::

我可能会用高亮来区分代码块？


```cpp lines=6,7,8,14,15,16
inline void solve (){
  printf ("Case #%lld: ",++ cases);
  int ppl = 0 ,ans = 0;
  int R = read () ,k = read () ,n = read ();
  up (i ,1 ,n) ppl += (g[i] = g[i + n] = read ());
  up (i ,1 ,n << 1) pre[i] = pre[i - 1] + g[i];
  if (ppl <= k) {writeln (ppl * R) ; return ;}//特判不要忘了！
  int r = 1;
  up (l ,1 ,n) {//双指针更新 jump/sum[i][0]。
//这里不用判 r 的边界，原因可以留给读者自己思考。
    while (pre[r] - pre[l - 1] <= k) ++ r;
    jump[l][0] = (r - 1) % n + 1 ,sum[l][0] = pre[r - 1] - pre[l - 1];
  }
  up (j ,1 ,27)
    up (i ,1 ,n)
      jump[i][j] = jump[jump[i][j - 1]][j - 1] ,sum[i][j] = sum[i][j - 1] + sum[jump[i][j - 1]][j - 1];//用倍增更新 jump 和 sum。
  int x = 1;
  dn (i ,27 ,0)
    if ((R >> i) & 1) ans += sum[x][i] ,x = jump[x][i];//倍增。注意先累加后跳，原因很简单。
  writeln (ans);
}
```
::::

---

## 作者：reinforest (赞：0)

一道比较有趣的题目。

首先特判掉每次都能够坐下所有人的情况。

如果我们把这个序列卷成一个环，可以发现，每次执行完“过山车”操作后，这个环中的元素相对位置是不会变的，因此我们可以使用一个循环指针维护在这个环中队头的下标。

对于这个指针，如果现在在位置 $l$，那么它下一步所在的位置 $r$ 是确定的，如果我们对于所有的 $l$，找出对应的 $r$，然后从 $l$ 向 $r$ 连边，相当于对于每一个点，都只有一个出度，因此最后的结构一定是一个基环内向森林。

因此对于初始的 $l$，我们可以暴力找到 $r$，然后令 $l \leftarrow r$，最后一定会走到一个环中（注意这个环可能不包括起点）。可以找到这个环的长度以及环上所有点的权值和，答案就可以快速计算了。

最坏情况下时间复杂度 $\Theta(Tn^2)$，但是可以对于每一个 $l$ 通过双指针预处理出 $r$ 的方式把时间复杂度优化到线性。 

输出的时候注意冒号后面有一个空格。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
constexpr ll maxn=1e3+5;
struct node{
    ll tot,val;
}arr[maxn];
ll R,k,n,g[maxn],sum,all;
void init(){
    for(int i=0;i<maxn;i++){
        arr[i].tot=arr[i].val=0;
    }
    R=k=n=sum=all=0;
}
void solve(ll cur){
    init();
    cin>>R>>k>>n;
    for(int i=1;i<=n;i++){
        cin>>g[i];
        all+=g[i];
    }
    if(all<=k){
        //特判能够坐下所有人的情况
        cout<<"Case #"<<cur<<": "<<R*all<<"\n";
        return;
    }
    all=0;
    bool flg=false;
    for(ll l=0,r=0,i=0;i<R;l=r,i++){
        sum=0;
        while(sum+g[r%n+1]<=k){
            sum+=g[r%n+1];
            r=r%n+1;
        }
        all+=sum;
        if(!flg && arr[r].tot){
            //找到环了
            flg=true;
            ll ci=(R-arr[r].tot)/(i-arr[r].tot+1);//计算这个环经过的次数
            all+=(ci-1)*(all-arr[r].val);//增加这个环的贡献乘以次数
            //由于你已经经过了一次所以要减一
            i+=(ci-1)*(i-arr[r].tot+1);//将下标增加次数乘以环长
        }
        if(!flg){
            arr[r]={i+1,all};//标记已经经过这个点
        }
    }
    cout<<"Case #"<<cur<<": "<<all<<"\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll T;
    cin>>T;
    for(int i=1;i<=T;i++)solve(i);
    return 0;
}
```

---

