# Bouncing Boomerangs

## 题目描述

To improve the boomerang throwing skills of the animals, Zookeeper has set up an $ n \times n $ grid with some targets, where each row and each column has at most $ 2 $ targets each. The rows are numbered from $ 1 $ to $ n $ from top to bottom, and the columns are numbered from $ 1 $ to $ n $ from left to right.

 For each column, Zookeeper will throw a boomerang from the bottom of the column (below the grid) upwards. When the boomerang hits any target, it will bounce off, make a $ 90 $ degree turn to the right and fly off in a straight line in its new direction. The boomerang can hit multiple targets and does not stop until it leaves the grid.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1428D/72465dd91e513170499b588221a0f92a0b864d32.png)In the above example, $ n=6 $ and the black crosses are the targets. The boomerang in column $ 1 $ (blue arrows) bounces $ 2 $ times while the boomerang in column $ 3 $ (red arrows) bounces $ 3 $ times.

 The boomerang in column $ i $ hits exactly $ a_i $ targets before flying out of the grid. It is known that $ a_i \leq 3 $ .

However, Zookeeper has lost the original positions of the targets. Thus, he asks you to construct a valid configuration of targets that matches the number of hits for each column, or tell him that no such configuration exists. If multiple valid configurations exist, you may print any of them.

## 说明/提示

For the first test, the answer configuration is the same as in the picture from the statement.

 For the second test, the boomerang is not supposed to hit anything, so we can place $ 0 $ targets.

 For the third test, the following configuration of targets matches the number of hits, but is not allowed as row $ 3 $ has $ 4 $ targets.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1428D/e8639121efc97faecf0da2314faa18fb9ab2eb8b.png)It can be shown for this test case that no valid configuration of targets will result in the given number of target hits.

## 样例 #1

### 输入

```
6
2 0 3 0 1 1```

### 输出

```
5
2 1
2 5
3 3
3 6
5 6```

## 样例 #2

### 输入

```
1
0```

### 输出

```
0```

## 样例 #3

### 输入

```
6
3 2 2 2 1 1```

### 输出

```
-1```

# 题解

## 作者：Demoe (赞：9)

### [题目传送门](https://www.luogu.com.cn/problem/CF1428D)

## 题意

- 在 $n\times n$ 的方阵中，每一列底端都会向上进入一个球，对于每个特殊点，若球经过则球方向右转。

- 给定每一列的球经过特殊点个数，请构造方案。

## Sol

考虑到 $a_i \le 3$ 那就可发现是一道很好构造的贪心。

分四类讨论。

#### $a_i=0$

直接跳过即可。

#### $a_i=1$

新开一行即可。

#### $a_i=2$

考虑到一行最多只能有 $2$ 个特殊点，那么可发现它一定跟在一个 $a_i=1$ 的后面。

这里会出现无解情况，仅当前面不存在 $a_i=1$ 被占用。

#### $a_i=3$

再开一行即可，需要占用一个 $a_i=1/2/3$ 优先占用 $a_i=2/3$。

没了。思路清晰。简单贪心。

```cpp
// wish to get better qwq
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+5;
ll n,a[N],ans,nw;
stack<pair<ll,ll> >c1,c2,qaq,c3;
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);nw=n;
	for(ll i=1;i<=n;i++) rd(a[i]);
	for(ll i=n;i>0;i--){
		if(a[i]==0) continue;
		if(a[i]==1){
			c1.push(make_pair(nw,i));qaq.push(make_pair(nw,i));
			ans++;nw--;
		}
		if(a[i]==2){
			if(c1.empty()){
				puts("-1");return 0;
			}
			pair<ll,ll> x=c1.top();c1.pop();
			c2.push(make_pair(x.first,i));qaq.push(make_pair(x.first,i));
			ans++;
		}
		if(a[i]==3){
			if(c1.empty()&&c2.empty()&&c3.empty()){
				puts("-1");return 0;
			}
			if(!c3.empty()){
				pair<ll,ll> x=c3.top();c3.pop();
				ans+=2;
				c3.push(make_pair(nw,i));
				qaq.push(make_pair(nw,i));qaq.push(make_pair(nw,x.second));
				nw--;
				continue;
			}
			if(!c2.empty()){
				pair<ll,ll> x=c2.top();c2.pop();
				ans+=2;
				c3.push(make_pair(nw,i));
				qaq.push(make_pair(nw,i));qaq.push(make_pair(nw,x.second));
				nw--;
				continue;
			}
			pair<ll,ll> x=c1.top();c1.pop();
			ans+=2;
			c3.push(make_pair(nw,i));
			qaq.push(make_pair(nw,i));qaq.push(make_pair(nw,x.second));
			nw--;
			continue;
		}
	}
	wr(ans);puts("");
	while(!qaq.empty()){
		pair<ll,ll> x=qaq.top();qaq.pop();
		wr(x.first),putchar(' '),wr(x.second),puts("");
	}
	return 0;
}
```

---

## 作者：UncleSam_Died (赞：3)

### 解题思路
很简单的贪心。

观察发现以下性质：
- 当 $a_i=2$ 时，这一行一定只有两个目标，且第二个目标一定位于一个 $a_j=1$ 的格子内；
- 当 $a_i=3$，那么当前列右边某一列发生转向的地方，$a_j\not=0$；

那么这道题就基本已经做出来了。因为 $a_i=3$ 的格子转向格可以在任意非 $0$ 列，而 $a_i=2$ 的转向格一定在 $a_j=1$ 列，那么我们考虑优先满足 $a_i=2$ 的列的需求。显然，不管怎么填，占用的行数是固定的，那么我们考虑第 $i$ 列填在第 $i$ 行，这样可以有效避免一些重复。接下来我们填 $a_i=3$ 的格子，贪心的从左往右找到第一个可以有转向格的列，然后直接填就可以了。最后把 $a_i=1$ 的补上就结束了。

注意，我们填的时候不需要考虑有没有填过，直接无脑填就可以了，最后再去重。

综上，本题步骤如下：
- 从左往右找到所有 $a_i=1$ 的列，并按顺序放入一个队列中；
- 从左往右枚举 $a_i=2$ 的列，并不断弹出队首直到队首列在当前列右侧，然后在队首列填入一个目标，并标记为已填；
- 清空队列，从左往右枚举所有非 $0$ 列，并放入队列中；
- 从左往右枚举 $a_i=3$ 的列，找到第一个在当前列右侧的列，然后填入两个目标；
- 枚举剩余的没有被填过的 $a_i=1$ 的列，向其中填入一个目标；
- 排序去重输出答案。

### 注意事项
- 在维护可填列的时候一定要使用队列来维护，贪心地从左往右填；
- 注意纵坐标是从上往下递增的，而不是从下往上。

### AC 代码
应该是比较短的代码了吧……
```cpp
#include<bits/stdc++.h>
#define N 100005
#define p push_back
#define C continue
#define re register
#define pii std::pair<int,int>
std::vector<pii> A;
int n,a[N],vis[N];
signed main(){scanf("%d",&n);
    for(re int i=1;i<=n;++i)
        scanf("%d",&a[i]);
    std::queue<int> q;
    for(re int i=1;i<=n;++i)
        if(a[i]==1) q.push(i);
    for(re int i=1;i<=n;++i){
        if(a[i]!=2) C;
        while(q.size()&&q.front()<i) q.pop();
        if(q.empty()){puts("-1");return 0;}
        A.p({i,i});
        A.p({i,q.front()});
        vis[q.front()]=1;q.pop();
    }while(q.size()) q.pop();
    for(re int i=1;i<=n;++i){
        if(a[i]!=0&&!vis[i]) q.push(i);
    }for(re int i=1;i<=n;++i){
        if(a[i]!=3) C;
        while(q.size()&&q.front()<=i) q.pop();
        if(q.empty()){puts("-1");return 0;}
        A.p({i,i});A.p({i,q.front()});
        A.p({q.front(),q.front()});
        vis[q.front()]=1;q.pop();
    }for(re int i=1;i<=n;++i){
        if(a[i]!=1) C;
        if(vis[i]) C;A.p({i,i});
    }std::sort(A.begin(),A.end());
    int res=std::unique(A.begin(),A.end())-A.begin();
    printf("%d\n",res);
    for(re int i=0;i<res;++i){
        printf("%d ",A[i].first);
        printf("%d\n",A[i].second);
    }
}
```


---

## 作者：AsunderSquall (赞：3)

update：远古题解一大堆格式错误，试图一个个修复。  

看到很多大佬都是从右往左扫的，我来一个从左往右扫的。  
~~可能更难想~~  
考虑到这题 $a_i \leq 3$ 那么我们可以贪心构造。

`for (int i=1;i<=n;i++)`

**1 $\mathbf{a_i=0}$**
忽略他。

**2   $\mathbf{a_i=1/2/3}$**  
那么首先这一行一定至少有一个（废话）。  
那么我们**先假设**这一行的最下面的目标，$r$为还没有出现过的值中最小的。  
有点抽象，可以举例。  
比如之前出现过 $1,1,2,3,4,2,3$（随手打的，可能并不存在），那么先把它设定为$5$。

那么肯定不会对前面产生影响。  


接着考虑他们对**后续**的影响  

- $a_i=1$  无。  
- $a_i=2$  需要这一行在后面还有目标。
- $a_i=3$  需要在这一行后面还有目标，同时这个目标所在列的下面还有一个目标。

用 ~~图~~ $\LaTeX$画图来说明

$a_i=2$ 的情况：
$$\ \times \to \to \to\times$$
$$\ \uparrow \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \downarrow$$
$$\ \uparrow \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \downarrow$$

$a_i=3$ 的情况：
$$\ \ \ \ \ \ \ \ \ \times \to \to \to \times$$
$$\ \ \ \ \ \ \ \ \ \uparrow \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \downarrow$$
$$\leftarrow \ \leftarrow \ \uparrow \ \ \leftarrow \leftarrow \leftarrow \times$$
$$\quad\quad \uparrow \quad\quad\quad\quad $$

那么我们可以在处理 $a_i=2/a_i=3$ 的时候把它加入队列或者栈什么的，等一下可以处理了再处理。注意，要加入的是处理的是哪一行。（列和行都加了也没问题的） 

为了方便表示，我们假设加入的列为 $j$，加入的行为 $h_j$。

接下来考虑每种 $a_i$ 可以处理什么。

- $a_i=1$  
可以处理 $a_j=2$ 和 $a_j=3$  。  
对于 $a_j=2$ 的情况，把最下面的目标的 $r$ 换成 $h_j$ 即可。  
对于 $a_j=3$ 的情况，除了最下面的目标外，加一个 $h_j$ 即可。  

- $a_i=2$  
可以处理 $a_j=3$ 的情况。  
对于 $a_j=2$ 的情况：  
由于第 $h_j$ 行若在 $i$ 列加入目标，则第 $i$ 列没有比 $h_j$ 更下面的目标了（不然从 $j$ 射入的飞镖会转 $3$ 次）。  
那么再考虑到 $i$ 列射入的飞镖同样要转 $2$ 遍，因此 $h_j$ 行之后还需要添加至少一个目标  
那么违反了题目**每一行或者每一列不能有超过 2 个目标**的条件。

  对于 $a_j=3$ 的情况，除了最下面的目标外，加一个 $h_j$ 即可。  

- $a_i=3$  
可以处理 $a_j=3$ 的情况。  
与 $a_i=2$ 类似，这里不再赘述。

然后我们考虑到因为 $a_j=2$ 只有 $a_i=1$ 才能处理，因此当 $a_i=1$ 时优先处理 $a_j=2$ 的情况，如果没有再处理 $a_j=3$ 的情况。

最后，如果发现还有 $2/3$ 没有处理，那么输出 `-1`，否则输出答案。

**Tips**  
- 对于 $a_i=2/3$ 的情况，别忘了处理完之后还要加入队列。
- 手写 stl 的数组要开到 $2 \times n$。  
- 答案数组也要开到 $2 \times n$。  
- 行和列的下标比较奇怪，注意一下。

代码：
```cpp

#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;

 
int n,H,cnt;
int a[N];
int c[N],r[N];
int que2[N],que3[N],h[N];
int hd2=1,tl2=0,hd3=1,tl3=0;
void add(int x,int y){c[++cnt]=x;r[cnt]=y;}//加入答案
void add2(int x){que2[++tl2]=x;}//加入2队列
void add3(int x){que3[++tl3]=x;}//加入3队列
signed main()
{
	cin>>n;
	H=0;
	for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++)
	{
		if (a[i]==0) continue;
		if (a[i]==1)
		{
			//处理2的问题，如果没有则处理3，如果还没有自己再搞一行 
			if (hd2<=tl2)
			{
				int x=que2[hd2];
				add(i,h[x]);hd2++;
			}
			else if (hd3<=tl3)
			{
				H++;
				int x=que3[hd3];
				add(i,h[x]);
				add(i,H);
				hd3++;
			}
			else
			{
				H++;
				add(i,H);
			}
		}
		if (a[i]==2)
		{
			//如果有3则处理3的问题 
			//将点放入队列
			if (hd3<=tl3)
			{
				H++;
				int x=que3[hd3];
				add(i,h[x]);add(i,H);hd3++;
				add2(i);h[i]=H;
			}
			else
			{
				H++;
				add(i,H);
				add2(i);h[i]=H;
			}
		}
		if (a[i]==3)
		{
			//如果有3先处理3的问题
			//将此点放入队列 
			if (hd3<=tl3)
			{
				H++;
				int x=que3[hd3];
				add(i,h[x]);add(i,H);hd3++;
				add3(i);h[i]=H;
			}
			else
			{
				H++;
				add(i,H);
				add3(i);h[i]=H;
			}		
		}
	}
	if (hd2<=tl2 || hd3<=tl3) //如果还没有处理完2和3输出-1
	{
		cout<<-1<<endl;
		return 0;
	}
	cout<<cnt<<endl;
	for (int i=1;i<=cnt;i++) printf("%d %d\n",r[i],c[i]);
}
```

---

## 作者：jun头吉吉 (赞：3)

# CF1428D 【Bouncing Boomerangs】
[宣传Blog](https://chen-jia-liang.gitee.io/blog/2020/10/18/%E9%A2%98%E8%A7%A3-CF1428D-%E3%80%90Bouncing-Boomerangs%E3%80%91/)
## 题意
在$n\times n$的网格上，有若干目标。从最低下扔回旋镖，碰到目标会右转。每行、每列不超过两个目标。现在已知从每一列扔出去会撞到$a_i$个障碍($a_i\le 3$)，请求出一种合法方案。

## 题解
$\color{red}\texttt{Warning:}$由于本人比较弱，算法可能会多一只`log`

首先~~通过画图~~我们发现一些奇奇怪怪的构造方法：
1. 如果$a_i=0$，那么不用管它
1. 如果$a_i=1$，那么可以新开一列，且此行还可以添，此列也还可以添
1. 如果$a_i=2$，那么可以找一个可以添的列，出现在这一列的行就不能添了
1. 如果$a_i=3$，那么可以新开一列，并找到一个可以添的行。在这两行添，出现在那行的列就不能添了。

可能说起来比较绕，解图理解一下$1,2,3$

### $a_i=1$
![](https://cdn.luogu.com.cn/upload/image_hosting/fqi3rjuj.png)

显然此时绿色的都可以放。
### $a_i=2$
![](https://cdn.luogu.com.cn/upload/image_hosting/mtk19y15.png)
此时的`x`必定放在绿色的地方。且`x`的左边都不能放。至于为什么右边的`x`上面也不能放：
![](https://cdn.luogu.com.cn/upload/image_hosting/4vejiy2x.png)

放在上面必然会出现$4$个，那时无意义的。

### $a_i=3$
![](https://cdn.luogu.com.cn/upload/image_hosting/lf2t20mg.png)

上面一行不能放是因为$2$个的限制，而下面的`x`左边不能放是因为放了会出现$4$个的情况。

## 代码
行和列一直搞不清，写得比较乱
```cpp
int n,a[100000+10];
int ans[100000+10][2];
int low=0;//最高列
set<int>can1;//还有那些行左边可以摆
set<int>can2;//还有那些列上面可以加 
int lst[100000+10];
signed main(){
	in::read(n);
	for(int i=1;i<=n;i++)
		in::read(a[i]);
	for(int i=n;i>=1;i--)
		if(a[i]==1){
			++low;
			ans[i][0]=low;
			can1.insert(low);
			lst[low]=i;
			can2.insert(i);
		}
		else if(a[i]==2){
			if(!can1.size())
				puts("-1"),exit(0);
			ans[i][0]=*can1.begin();
			can2.erase(lst[*can1.begin()]);
			can1.erase(can1.begin());
			can2.insert(i);
		} 
		else if(a[i]==3){
			if(!can2.size())
				puts("-1"),exit(0);
			low++; 
			ans[i][0]=low;
			ans[*can2.begin()][1]=low;
			can1.erase(ans[*can2.begin()][0]);
			can2.erase(can2.begin());
			can2.insert(i);
		}
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(ans[i][0])cnt++;
		if(ans[i][1])cnt++;
	}
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++){
		if(ans[i][0])printf("%d %d\n",n-ans[i][0]+1,i);
		if(ans[i][1])printf("%d %d\n",n-ans[i][1]+1,i);
	}
	out::flush();
	return 0;
}
```

---

## 作者：wizardMarshall (赞：2)

一道不错的思维题，~~不要急着看题解~~。

## 题意

从每一列下方往上扔回旋镖，回旋镖碰到特殊点会右转。给出每一列回旋镖碰到的特殊点个数，求可能的特殊点分布情况。不可能输出 `-1`。

## 思路

我们根据 $a_i$ 分类讨论。

---

$a_i=0:$

这一列为空，不用管。

---

$a_i=1:$

这一列有一个，我们可以新开一行，放一个特殊点。由于是新的行，右边也没有特殊点。

在备用点序列里存放这个特殊点的位置。

---

$a_i=2:$

根据示例图片，我们可以看到从起点一直往上走，在某一行碰到一个特殊点，右转后，在右边又碰到一个，往下。

右边这个特殊点肯定不能新开一个。如果右边某一列 $a_j=0$，则新建了特殊点之后就不是 $0$ 了。如果那一列 $a_j\ne0$，下面有特殊点，则这条路径又会碰到第三个特殊点，矛盾。

因此，第一个点可以新建，第二个点必须找一个之前已经存在的特殊点（也就是备用点序列）。

可知选择的那一列 $a_j=1$。因为一行最多有两个特殊点，否则矛盾。

在原来特殊点的那一行，当前的这一列上建一个特殊点，使得回旋镖恰好碰到两个特殊点。

之后 $j$ 这一行就不能用了，因为已经被用过，左边有了特殊点，需要从备用点序列里删掉。而这次新建的点可以加入备用点序列。

---

$a_i=3:$

同理，只不过新建的是上面两个点。右下这个特殊点可以找备用点里的任意一个（$a_j=1,2,3$ 皆可）。删掉用过的点，然后将**左上的点**放入备用点序列。

由于第二种情况只能使用 $a_j=1$，因此 $a_i=3:$ 时先贪心地看 $a_j=2,3$ 的情况有没有，没有才选 $a_j=1$。

-----

这里贴一张题目的图例，读者可以结合理解。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1428D/72465dd91e513170499b588221a0f92a0b864d32.png)

------

## Code

注意：代码中为了坐标存储便于理解，一律采用先列后行的形式。详见输出部分。


```c++

#include <bits/stdc++.h>
using namespace std;
int a[100005];
pair <int, int> ans[200005];//最终答案
pair <int, int> c1[100005];//备用点序列，存aj=1的位置
pair <int, int> c2[100005];//同理
pair <int, int> c3[100005];//...
signed main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	int top = n + 1, t1 = 0, t2 = 0, t3 = 0, ta = 0;
	for (int i = n; i >= 1; i--) {
		if (a[i] == 0)continue;//不用管
		if (a[i] == 1) {
			top--;//新开一行（从小到大开行不方便，碰到ai=3会与之前重叠，往上开就没有这个烦恼，见图例）
			ans[++ta] = {i, top};
			c1[++t1] = {i, top};//放进备用点，下同
		}else if (a[i] == 2) {
			if (t1 == 0) {//前面没有aj=1或者都被用光了
				cout << -1;
				return 0;
			}
			ans[++ta] = {i, c1[t1].second};//当前这一列，横坐标是对应右边的那个特殊点
			c2[++t2] = {i, c1[t1].second};
			t1--;//用掉一个
		}else {
			//优先选择2与3
			if (t2) {
				top--;
				ans[++ta] = {i, top};//当前这一列，新开一行
				ans[++ta] = {c2[t2].first, top};//右边那一列，行一样（这样才能使得那个点右转后到达这个点）
				t2--;
				c3[++t3] = {i, top};
				continue;
			}
			if (t3) {//同理
				top--;
				ans[++ta] = {i, top};
				ans[++ta] = {c3[t3].first, top};
				t3--;
				c3[++t3] = {i, top};
				continue;
			}
			if (t1) {
				top--;
				ans[++ta] = {i, top};
				ans[++ta] = {c1[t1].first, top};
				t1--;
				c3[++t3] = {i, top};
				continue;
			}
			cout << -1;//三种情况都没有或是都被用完
			return 0;
		}
	}
	cout << ta <<endl;
	for (int i = 1; i <= ta; i++) {
		cout << ans[i].second << " " << ans[i].first << "\n";//存的时候是先存列再存行，这里输出的时候要反一下顺序
	} 
    return 0;
}


```

---

## 作者：tommymio (赞：2)

看到 $0\leq a_i\leq 3$，$\text{sb}$ 构造题没错了。

设 $i<j$，进行分类讨论：

- $a_i=0$，不放。

- $a_i=1$，不与其他列存在关联。

- $a_i=2$，与第一个 $a_j=1$ 的列存在关联。

- $a_i=3$，与某一 $a_j=1,2,3$ 的列存在关联，其中优先选择 $a_j=2,3$ 的列，因为 $a_j=1$ 的列可能还会对 $a_i=2$ 的列产生贡献。

自己画几张图其实就知道了，然后根据这个从 $n\sim 1$ 倒序贪心就好。

```cpp
#include<cstdio>
#include<stack>
#include<functional>
#define pr std::pair<int,int>
#define mp(x,y) std::make_pair(x,y) 
std::stack<pr> s1,s2,s3,ans;
int a[100005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
int main() {
	int n=read(),cur=n;
	for(register int i=1;i<=n;++i) a[i]=read();
	for(register int i=n;i;--i) {
		if(a[i]==0) continue;
		if(a[i]==1) {ans.push(mp(cur,i)); s1.push(mp(cur,i)); --cur;}
		else if(a[i]==2) {
			if(!s1.size()) {printf("-1\n"); return 0;}
			pr x=s1.top(); s1.pop(); s2.push(mp(x.first,i)); ans.push(mp(x.first,i)); --cur;
		}
		else {
			if(!s1.size()&&!s2.size()&&!s3.size()) {printf("-1\n"); return 0;}
			if(s2.size()) {pr x=s2.top(); s2.pop(); s3.push(mp(cur,i)); ans.push(mp(cur,x.second)); ans.push(mp(cur,i));}
			else if(s3.size()) {pr x=s3.top(); s3.pop(); s3.push(mp(cur,i)); ans.push(mp(cur,x.second)); ans.push(mp(cur,i));}
			else {pr x=s1.top(); s1.pop(); s3.push(mp(cur,i)); ans.push(mp(cur,x.second)); ans.push(mp(cur,i));}
			--cur;
		}
	} 
	printf("%d\n",ans.size());
	for(;ans.size();ans.pop()) printf("%d %d\n",ans.top().first,ans.top().second);
	return 0;
}
```



---

## 作者：do_while_true (赞：1)

[$\text{更佳的阅读体验}$](https://www.cnblogs.com/do-while-true/p/13841797.html)

# $\mathcal{Translate}$

[题目链接](http://codeforces.com/problemset/problem/1428/D)

在一个 $n\times n$ 的网格图中，在下面的每一列都会射出一个飞镖，在 $n\times n$ 的网格图中会有若干个目标，如果飞镖遇到目标则顺时针旋转 $90^{\circ}$ 后继续飞行直到飞出网格图。

规定在每一行每一列最多有 $2$ 个目标，第 $i$ 行的飞镖会旋转 $a_i$ 次，现给定 $a_i$， 构造出一组合法的解（确定网格图中的目标的个数和位置）。

$n\leq 10^5,0\leq a_i\leq 3$

凉心构造题。

# $\mathcal{Solution}$

对于 $a_i=0$，忽略这个地方，不会对答案产生什么影响。

先处理 $a_i=1$ 的情况，因为 $a_i=2,3$ 会依靠另一列来进行第二、三次反弹，而 $a_i=1$ 不需要考虑，直接出去占用一行就可以。怎样占用最优？因为其它 $3$ 匹配这个 $1$ 进行三次反弹的时候需要上面多开一行，所以从下往上依次占用。

从左往右找 $a_i=2$，之后再找到右边第一个没有被前面的 $2$ 匹配的 $1$，匹配到一起，也就是利用这个 $1$ 的这一列目标进行第二次反弹。

为什么找右边第一个 $1$ ？ 因为 $2$ 需要右边的 $1$ 来反弹，贪心一下是选尽量靠左的更优，把尽量靠右让给右边的 $2$。

为什么先找 $a_i=2$？因为 $a_i=3$ 可以依靠其他的 $1,2,3$ 进行 $3$ 次反转。

最后就是 $a_i=3$ 的情况，它可以有三种方法来进行三次反弹：

1. 右边没有被其它 $2,3$ 匹配的 $1$。

2. 右边没有被其它 $3$ 匹配的 $2$。

3. 右边没有被其它 $3$ 匹配的 $3$。

因为可以从右边的 $3$ 来反弹，所以这里 $3$ 从后往前匹配找。

$a_i=2,3$ 去匹配的时候采用双指针扫，一个扫 $a_i=2,3$，一个扫哪一位可以匹配。如果没扫到就是无解。

# $\mathcal{Code}$

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
#define re register
//#define int long long
inline int Max(int x, int y) { return x > y ? x : y; }
inline int Min(int x, int y) { return x < y ? x : y; }
inline int Abs(int x) { return x < 0 ? ~x + 1 : x; }
inline int read() {
	int r = 0;
	bool w = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-') w = 1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		r = (r << 3) + (r << 1) + (ch ^ 48);
		ch = getchar();
	}
	return w ? ~r + 1 : r;
}
//#undef int
const int N = 300010;
bool f;
int n, a[N], cnt, ansx[N], ansy[N];
bool vis[N];
int row[N], rowcnt; 
signed main() {
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	//先把所有的1一行一行开 
	for(int i = 1; i <= n; ++i)
		if(a[i] == 1) ++cnt, ansx[cnt] = i, ansy[cnt] = ++rowcnt, row[i] = rowcnt;
	int pos = 1;
	//2和右边第一个1匹配 
	for(int i = 1; i <= n; ++i) {
		if(a[i] == 2) {
			pos = Max(pos, i);
			while(a[pos] != 1 && pos <= n) ++pos;
			if(pos == n + 1) {
				puts("-1");
				return 0;
			}
			++cnt;
			ansx[cnt] = i, row[i] = ansy[cnt] = row[pos];
			vis[pos] = 1;
			++pos;
		}
	}
	//3和右边三种情况匹配 
	pos = n;
	for(int i = n; i >= 1; --i) {
		if(a[i] == 3) {
			while(!((a[pos] == 1 && !vis[pos]) || a[pos] == 2 || (a[pos] == 3 && row[pos])) && pos >= i) --pos;
			if(pos == i - 1) {
				puts("-1");
				return 0;
			}
			++cnt; ansx[cnt] = i, ansy[cnt] = ++rowcnt;
			++cnt; ansx[cnt] = pos, ansy[cnt] = rowcnt;
			row[i] = rowcnt;
			--pos;
		}
	}
	//无解 
	if(cnt > n << 1 || rowcnt > n) {
		puts("-1");
		return 0;
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; ++i) printf("%d %d\n", n - ansy[i] + 1, ansx[i]);
	return 0;
}
```


---

## 作者：AlanSP (赞：1)

## [题意](https://codeforces.com/contest/1428/problem/D)

确实被这题恶心到了，导致我赛时先写的E……

我们注意到 $a_i\le3$，那么我们可以大力分类讨论。

- $a_i=0$，直接忽略就好。
- $a_i=1$，我们需要保证至少有一个目标点。
- $a_i=2$，存在 $i<j$ ,使得 $j$ 最下面的目标点和 $i$ 最下面的处于同一行。
- $a_i=3$，存在 $i<j$ ,使得 $j$ 最上面的目标点和 $i$ 最下面的处于同一行，且 $j$ 有两个目标点。

这样梳理出来，发现非常不可做，我们需要转化一下题意。

我们称 $a_i=2$ 或 $a_i=3$ 的 $<i,j>$ 二元组为一对 $<a_i,a_j>$ **匹配**。

首先可以注意到，不同行之间的顺序似乎是 “固定” 的。

$a_i=3$ 的匹配一定是处于靠上的位置，$a_i=2$ 的一定最靠下。

同时也发现，对于 $a_i$ 相同的匹配，它们行之间的顺序是任意的。

再加上每行最多两个关键点的限制，我们不难想到一行一行分开考虑。

---

**重点**：考虑一下匹配的实质：

![](https://cdn.luogu.com.cn/upload/image_hosting/7irk04y8.png)

如上图，橘色框住了 $<3,1>$ 匹配，红色框住了 $<3,2>$ 匹配，蓝色框住了 $<1,2>$ 匹配。

那么我们可以发现，任何一种匹配都可以被拆分成若干处于同一行的数对。

若是单个 $a_i=1$，则可以看成和空的数对，称这种数对为虚数对。其他的为实数对。

那么 $<2,1>$ 是一个数对，$<3,1>$ 是一个实数对和一个虚数对，$<3,2>$ 是两个实数对，$<3,3>$ 等同理。

现在我们要做的只是配好对，再按上面的顺序依次把这些数对放在各个行上面。

---

还有最后几个问题：配对的顺序以及有无解的判定。

这里我的思路和其他题解不太一样：我们可以借助栈，把所有非0的数**倒序**压栈。

这样栈顶一定是下标靠前的位置。

因为非0的数都可以相互配对 ( 除 $<1,1>$)，这样做一定是正确的。

按照上面的顺序，我们首先考虑 $a_i=3$ 的配对。

之后再把 $a_i=1$ 压栈，考虑 $<2,1>$ 的匹配。

这个地方有很多细节，具体可以看代码和注释。

无解的情况，一定是存在 $a_i=2\ $ 或 $\ a_i=3$ 没有配对，而 $a_i=1$ 可以和空配对，记得加上。

最后输出就可以了。

### **珍爱rating，远离毒瘤构造。**

---

### Code:

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
#define PII pair<int,int>
#define mp make_pair
const int N=1e5+9;
int T,stk[N],top,n;
int a[N],vis[N];
vector<PII> ans;
int main()
{
	int now=0,pre=0,cnt=0,num=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);	
	for(int i=n;i>=1;i--) if(a[i]) stk[++top]=i;//压栈一定要倒序
	for(int i=1;i<=n;i++)
		if(a[i]==3)
		{
			while(stk[top]<=i&&top) top--;//找到 j>i 的位置，注意判断非空
			if(top) 
			{
				if(a[stk[top]]==1) vis[stk[top]]=2;//vis=2表示已经匹配，但需要添加空节点
				vis[i]=true;
				ans.push_back(mp(i,stk[top])),top--,++cnt,now++;
			}
		}
	top=0;
	for(int i=n;i>=1;i--) if(a[i]==1) stk[++top]=i;
	for(int i=1;i<=n;i++)
		if(a[i]==2&&top&&!vis[i])
		{//同上
			while(top&&stk[top]<i) --top;
			while(top&&vis[stk[top]]) --top;//不能和已匹配的点匹配
			if(!top) break;//attention
			vis[stk[top]]=vis[i]=true;
			ans.push_back(mp(i,stk[top]));
			++cnt;--top;now++;
		}
	top=0;
	for(int i=1;i<=n;i++) 
		if(vis[i]!=1&&a[i]==1) ans.push_back({i,0}),++now,++num;
		else if(!vis[i]&&(a[i]==2||a[i]==3)) {puts("-1");return 0;}
	if(now>n){puts("-1");return 0;}//超过限制
	now=1;
	printf("%d\n",cnt*2+num);//num为虚数对，cnt为实数对
	for(auto i:ans)
	{
		printf("%d %d\n",now,i.first);
		if(i.second) printf("%d %d\n",now,i.second);
		now++;
	}
	return 0;
}
```



---

## 作者：gyh20 (赞：1)

构造题。

由于右边的点答案不会被左边点改变，所以我们可以强制固定右边的点。

把固定点分为两类：

$1.$ 任意固定点，当且仅当固定点的 $a_i=1$ 此时可以任意添加其他单独的固定点（上或下）。

$2.$ 限制固定点，即 $a_i=2,3$ 此时只能在上方加点，不能在下方加点。

再来对于 $a_i$ 分类讨论。

$a_i=0$，直接跳过这一行。

$a_i=1$，新建一个点，与之前的所有点坐标不同，并加入任意固定点的队列。

$a_i=2$，此时只能与之前一个任意固定点配对，在下方新建一个点，与 $i$ 坐标相同，并把 $i$ 加入限制固定点队列。

$a_i=3$，此时限制与任意都可以，但为了最优，消耗有限制的。在上方新建点，并把 $i$ 加入限制固定点队列。

关于纵坐标的处理，可以用两个指针或者最后离散化一遍。
```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int n,m,t,a[200002],b[200002],ans,pos[200002],l,r,aa[200002],bb[200002],cnt,s[200002];
queue<int>q[12];
int main(){
	n=read();l=r=100000;++l;
	for(re int i=1;i<=n;++i)s[i]=read();
	for(re int i=n;i;--i){
		if(s[i]==0)continue;
		else if(s[i]==1){
			pos[i]=++r;
			aa[++cnt]=i,bb[cnt]=r;
			q[1].push(i);
		}
		else if(s[i]==2){
			if(q[1].empty())return puts("-1"),0;
			re int xx=q[1].front();
			q[1].pop();
			pos[i]=--l;
			aa[++cnt]=xx,bb[cnt]=pos[i];
			aa[++cnt]=i,bb[cnt]=pos[i];
			q[2].push(i);
		}
		else{
			if(q[2].empty()&&q[1].empty())return puts("-1"),0;
			if(!q[2].empty()){
				re int xx=q[2].front();
				q[2].pop();
				pos[i]=++r;
				aa[++cnt]=xx,bb[cnt]=pos[i];
				aa[++cnt]=i,bb[cnt]=pos[i];
			}
			else{
				re int xx=q[1].front();
				q[1].pop();
				pos[i]=++r;
				aa[++cnt]=xx,bb[cnt]=pos[i];
				aa[++cnt]=i,bb[cnt]=pos[i];
			}
			q[2].push(i);
		}
	}
	printf("%d\n",cnt);
	for(re int i=1;i<=cnt;++i)bb[i]-=l-1,printf("%d %d\n",n-bb[i]+1,aa[i]);
}
```



---

## 作者：lfxxx (赞：0)

先不管行之间的冲突，先考虑只有列冲突的构造。

我们发现，一个 $a_i = 3$ 的位置必须与后面一个 $a_i \not = 0$ 的位置匹配，一个 $a_i = 2$ 的位置必须与后面 $a_i = 1$ 的位置匹配，于是考虑先让 $a_i = 3$ 的内部匹配，再用 $a_i = 3$ 的去匹配 $a_i = 2$ 的，最后让剩下的去与 $a_i = 1$ 的匹配。

行之间的冲突考虑假若当前让 $i,j$ 匹配，就在第 $i,j$ 行上放置障碍即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
int a[maxn],n;
deque<int> cnt[4];
set< pair<int,int> > S;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cnt[a[i]].push_back(i);
    }
    while(cnt[3].size()>=2){
        int u=cnt[3].front();
        cnt[3].pop_front();
        int v=cnt[3].front();
        cnt[3].pop_front();
        S.insert(make_pair(u,u));
        S.insert(make_pair(v,v));
        S.insert(make_pair(v,u));
        cnt[3].push_front(v);
    }
    vector<int> New;
    while(cnt[2].size()>0&&cnt[3].size()>0&&cnt[3].front()<cnt[2].back()){
        while(cnt[3].front()>cnt[2].front()) New.push_back(cnt[2].front()),cnt[2].pop_front();
        int u=cnt[3].front();
        int v=cnt[2].front();
        cnt[3].pop_front();
        cnt[2].pop_front();
        New.push_back(v);
        S.insert(make_pair(u,u));
        S.insert(make_pair(v,v));
        S.insert(make_pair(v,u));
    }
    for(int x:New) cnt[2].push_back(x);
    sort(cnt[2].begin(),cnt[2].end());
    while(cnt[2].size()>0||cnt[3].size()>0){
        int u,v;
        if(cnt[1].size()==0){
            cout<<"-1\n";
            return 0;
        }else{
            v=cnt[1].back();
            cnt[1].pop_back();
        }
        if(cnt[2].size()==0){
            u=cnt[3].back();
            cnt[3].pop_back();
        }else if(cnt[3].size()==0){
            u=cnt[2].back();
            cnt[2].pop_back();
        }else if(cnt[2].back()>cnt[3].back()){
            u=cnt[2].back();
            cnt[2].pop_back();
        }else{
            u=cnt[3].back();
            cnt[3].pop_back();
        }
        if(u>v){
            cout<<"-1\n";
            return 0;
        }else{
            if(a[u]==3){
                S.insert(make_pair(u,u));
                S.insert(make_pair(v,u));
                S.insert(make_pair(v,v));
            }else{
                S.insert(make_pair(u,u));
                S.insert(make_pair(v,u));
            }
        }
    }
    while(cnt[1].size()>0){
        int u=cnt[1].back();
        S.insert(make_pair(u,u));
        cnt[1].pop_back();
    }
    cout<<S.size()<<'\n';
    for(pair<int,int> now:S) cout<<now.second<<' '<<now.first<<'\n';
    return 0;
}
```

---

## 作者：RockyYue (赞：0)

#### 1428D

$n$ 行 $n$ 列棋盘，其中 $(i,j)$ 表示 $i$ 行 $j$ 列处。你可以选择一些点设为特殊点，每行每列不能超过 $2$ 个，棋盘上行走的规则为，给定初始点和初始方向，一直走直到遇到特殊点，此时右转并沿着这个方向继续走，直到走出棋盘也不遇到特殊点为止。

所有第 $i$ 列给定 $a_i$，表示从 $(n,i)$ 开始初始向上走，按照规则会经过几个点（$a_i\le 3$），试给出一种特殊点位置的构造或输出无解，要求 $O(n)$。

#### Sol

> 为方便叙述，下文将“特殊点”直接称作“点”。

- 分析第 $i$ 列行走路线：若 $a_i=0$，此列无点。$a_i=1$，有一个点且后面列中无同行点。$a_i=2$，至少一点且对于 $i$ 列最低点，后面列有同行点 $u$，其在列内为低点。$a_i=3$，基本同 $a_i=2$，需 $u$ 在行内为高点。
- 既然每列限制都需要后面的配合，考虑两种：倒序处理和记录前面需要处理的部分。
  - 若倒序处理，不好处理每行至多两个点的限制，故记录两个队列：`q2` 和 `q3`，表示前面列中需要需要处理的，$a_i=2$ 或 $a_i=3$ 的，低点的位置。
  - 每行至多两个点，而 $n$ 行足够每行低点互不相同了，若想不干扰前面则设为前面列的行数 $\operatorname{mex}$（此处从 $1$ 开始），后面列的点行数与其相同当且仅当来满足其需求。
- 想怎么在当前列处理前面列的需求。若 $a_i=2/3$，则后面列有与当前列低点同行的点，于是这行的低点不能作为前面列的第二个中转点（此时前面的 $a$ 为 $2$），而若这行有两个点，用高点作中转，必经过低点，还是不能处理前面的 $a=2$。
- 故当且仅当 $a_i=1$ 时能处理前面 $2$ 的需求，当前行数设为与要处理位置相等即可。
- 对于 $3$ 的需求，$a_i=1/2/3$ 均可处理，方式易。故 $a_i=1$ 时优先处理 $2$ 再处理 $3$，其他处理 $3$。
- 最终若 `q2` 或 `q3` 非空，无构造。

---

## 作者：w33z8kqrqk8zzzx33 (赞：0)

$a_i=0$ 不要考虑。

输入里有一些 $a_i=3$ 看的挺难处理。但是观察到所有 $3$ 的列可以串到一起，仅仅需要一个 $2-1$ 或者一个 $1$ 结尾，先处理完这个。

然后就只需要匹配 $a_i=2$ 和 $a_i=1$ 了，可以贪心匹配。

贪心方法是每一个 $a_i=2$ 匹配到他后面的第一个 $a_i=1$。为什么贪心正确？假设存在一个合法匹配，两个 $2-1$ 对相交了。交换一下它们对应的 $1$，后者“放松”匹配，肯定不会让匹配变得不合法。于是贪心肯定会造出来一个合法匹配。

如果还剩下 $a_i=1$，可以摆到自己的行上面。

赛时代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;

// begin fast read template by CYJian (source: https://www.luogu.com.cn/paste/i11c3ppx)

namespace io {
	const int __SIZE = (1 << 21) + 1;
	char ibuf[__SIZE], *iS, *iT, obuf[__SIZE], *oS = obuf, *oT = oS + __SIZE - 1, __c, qu[55]; int __f, qr, _eof;
	#define Gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	inline void flush () { fwrite (obuf, 1, oS - obuf, stdout), oS = obuf; }
	inline void gc (char &x) { x = Gc(); }
	inline void pc (char x) { *oS ++ = x; if (oS == oT) flush (); }
	inline void pstr (const char *s) { int __len = strlen(s); for (__f = 0; __f < __len; ++__f) pc (s[__f]); }
	inline void gstr (char *s) { for(__c = Gc(); __c < 32 || __c > 126 || __c == ' ';)  __c = Gc();
		for(; __c > 31 && __c < 127 && __c != ' '; ++s, __c = Gc()) *s = __c; *s = 0; }
	template <class I> inline bool gi (I &x) { _eof = 0;
		for (__f = 1, __c = Gc(); (__c < '0' || __c > '9') && !_eof; __c = Gc()) { if (__c == '-') __f = -1; _eof |= __c == EOF; }
		for (x = 0; __c <= '9' && __c >= '0' && !_eof; __c = Gc()) x = x * 10 + (__c & 15), _eof |= __c == EOF; x *= __f; return !_eof; }
	template <class I> inline void print (I x) { if (!x) pc ('0'); if (x < 0) pc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10; while (qr) pc (qu[qr --]); }
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
} using io::pc; using io::gc; using io::pstr; using io::gstr; using io::gi; using io::print;

// end fast read template by CYJian

#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const int MOD = 1000000007;

set<int> one, two, three;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
	rep1(i, n) {
		int v; cin >> v;
		if(v == 1) one.insert(i);
		if(v == 2) two.insert(i);
		if(v == 3) three.insert(i);
	}
	vector<pii> ans;
	int row = n;
	if(three.size()) {
		auto b = prev(three.end());
		auto twop = two.upper_bound(*b);
		if(twop == two.end() || one.upper_bound(*twop) == one.end()) {
			auto onep = one.upper_bound(*b);
			if(onep == one.end()) {
				cout << -1 << endl;
				return 0;
			} else {
				vector<int> thee(all(three));
				reverse(all(thee));
				int cur = *onep;
				for(int t:thee) {
					ans.pb({row, cur});
					ans.pb({row-1, cur});
					cur = t;
					row--;
				}
				ans.pb({row, cur});
				one.erase(onep);
				row--;
			}
		} else {
			auto onep = one.upper_bound(*twop);
			vector<int> thee(all(three));
			reverse(all(thee));
			ans.pb({row, *onep});
			int cur = *twop;
			for(int t:thee) {
				ans.pb({row, cur});
				ans.pb({row-1, cur});
				cur = t;
				row--;
			}
			ans.pb({row, cur});
			two.erase(twop);
			one.erase(onep);
			row--;
		}
		three.clear();
	}
	while(two.size()) {
		auto f = two.begin();
		if(!one.size()) {
			cout << -1 << endl;
			return 0;
		}
		auto e = one.upper_bound(*f);
		if(e == one.end() || *f > *e) {
			cout << -1 << endl;
			return 0;
		}
		ans.pb({row, *f});
		ans.pb({row, *e});
		row--;
		two.erase(f); one.erase(e);
	}
	while(one.size()) {
		auto f = one.begin();
		ans.pb({row, *f});
		one.erase(f);
		row--;
	}
	if(three.size() || two.size() || one.size()) cout << -1 << endl;
	else {
		cout << ans.size() << endl;
		for(pii a:ans) cout << a.fi << ' ' << a.se << endl;
	}
}
```

---

