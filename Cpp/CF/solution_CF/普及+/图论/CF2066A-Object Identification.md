# Object Identification

## 题目描述

这是一道交互题。

给定一个由 $1$ 到 $n$ 的整数构成的数组 $x_1, \ldots, x_n$。评测方还拥有一个固定但隐藏的数组 $y_1, \ldots, y_n$，其元素也是 $1$ 到 $n$ 的整数。数组 $y$ 的元素对你未知。此外，已知对于所有 $i$，$x_i \neq y_i$，且所有有序对 $(x_i, y_i)$ 互不相同。

评测方秘密选择了以下两个对象之一，你需要判断具体是哪一个：

- 对象 A：一个包含 $n$ 个顶点（编号为 $1$ 到 $n$）的有向图，包含 $n$ 条形如 $x_i \to y_i$ 的边。
- 对象 B：坐标系上的 $n$ 个点，其中第 $i$ 个点的坐标为 $(x_i, y_i)$。

为了猜测评测方选择的对象，你可以进行查询。每次查询需指定两个数字 $i, j$（$1 \leq i, j \leq n, i \neq j$）。作为回应，你将得到一个数值：

- 若评测方选择对象 A，则返回顶点 $i$ 到顶点 $j$ 的最短路径长度（以边数为单位），若无路径则返回 $0$。
- 若评测方选择对象 B，则返回点 $i$ 与点 $j$ 的曼哈顿距离，即 $|x_i - x_j| + |y_i - y_j|$。

你最多可以进行 $2$ 次查询来确定评测方选择的对象。

## 说明/提示

第一个测试用例中，$x = [2,2,3]$，$y = [1,3,1]$，隐藏对象为 A。

第二个测试用例中，$x = [5,1,4,2,3]$，$y = [3,3,2,4,1]$，隐藏对象为 B。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
2
3
2 2 3

1

0

5
5 1 4 2 3

4

4```

### 输出

```
? 2 3

? 1 2

! A

? 1 5

? 5 1

! B```

# 题解

## 作者：Eason_cyx (赞：4)

牛的，这场 Div. 2D = Div. 1A，然后这题直接硬控 jiangly 50 分钟。/bx

----

首先判断这个 $x$ 是不是一个排列；如果不是，那么假设这是一张图，那么显然这个点是不可以到达任何一个点的。所以假设在 $x$ 中数 $k$ 没有出现，则我们可以询问 `! k k+1`（注意 $k=n$）。因为如果是 $n$ 个点的情况，那么这些点两两互不相同，所以距离不可能是 $0$；我们可以根据这个判断，如果是 $0$，那么就是第一种；否则是第二种。

那么如果 $x$ 是排列呢？我们可以先找到 $x_{p1}=1$ 和 $x_{p2}=n$。然后我们询问 `1 p1 p2` 和 `1 p2 p1`，得到两个结果 $\text{ans1}$ 和 $\text{ans2}$。那么对于 $n$ 个点来说，显然应当有 $\text{ans1=ans2}$，即他们如果不相等，就一定是第一种情况。如果他们相等，说明如果是图，那么图中可能有环。但是如果有环，又由于只有 $n$ 条边，所以两个答案最大为 $\dfrac{n}{2}$。但是如果是 $n$ 个点，那么一个横坐标是 $1$，另一个横坐标是 $n$，距离一定 $\ge n-1$！

那么就做完了。时间复杂度 $O(1)$。[提交记录](https://codeforces.com/contest/2067/submission/305750595)

---

## 作者：chenxi2009 (赞：3)

## 思路
题面中的一些内容提示性很强。所有的 $(x,y)$ 对互不相同，意味着如果隐藏对象是 B 则交互的回复一定不为 $0$，可以从这里入手解决部分问题。

考虑怎样交互令对象为 A 的时候回复为 $0$，不难发现当 $a$ 没有出现在 $x$ 中，则 $a$ 在 A 的图无出边，对象为 A 时任意询问 $(a,i)$ 回复均为 $0$，根据回复的是否为零可以得出答案。这种策略可以涵盖 $x$ 不为一个排列时的情况。

那么当 $x$ 为一个排列又应该如何交互？考虑 A，$x$ 为排列、对象为 A 时的图为一个内向基环树森林，两次询问的条件下很难发挥性质；手玩 $n=3$ 发现这个问题并不能仅用前三个点解决，和 $x$ 显然有关。\
开动脑筋发现令 $x_X=1,x_Y=n$，在 B 情况下 $(X,Y),(Y,X)$ 的询问答案都是一定不小于 $n-1$ 的且相等，但是在基环树森林中 $X,Y$ 即便在最极端的情况下两者之和也至多为 $n$。找出矛盾，问题解决。

时间复杂度 $O(\sum n)$。
## 代码
```cpp
#include<bits/stdc++.h> 
using namespace std;
int T,n,x[300000],knd,inp,inp2,a,b;
bool apr[300000];
inline void qry(int x,int y){printf("? %d %d\n",x,y),fflush(stdout);}
int main(){
	scanf("%d",&T);
	while(T --){
		knd = 0;
		scanf("%d",&n);
		for(int i = 1;i <= n;i ++) apr[i] = false;
		for(int i = 1;i <= n;i ++) scanf("%d",&x[i]);
		for(int i = 1;i <= n;i ++){
			if(apr[x[i]]) knd = 1;
			apr[x[i]] = true;
		}
		if(knd){//x 不是一个排列 
			for(int i = 1;i <= n;i ++) if(!apr[i]) knd = i;//任意找一个没出现过的数 
			qry(knd,1 + (knd == 1));//询问此数与任意其他数，在 A 的图中此数必然不存在到其他点的最短路
			scanf("%d",&inp);
			if(inp) printf("! B\n");
			else printf("! A\n");
		} 
		else{
			for(int i = 1;i <= n;i ++){//找到 x_i=1 和 x_i=n 的位置 
				if(x[i] == 1) a = i; 
				if(x[i] == n) b = i;
			}
			qry(a,b),scanf("%d",&inp);
			qry(b,a),scanf("%d",&inp2);
			if(inp >= n - 1 && inp == inp2) printf("! B\n");//隐藏对象是 B 当且仅当两次回复相等且不小于 n-1 
			else printf("! A\n");
		}
		fflush(stdout);
	}
	return 0; 
}

---

## 作者：ZMQ_Ink6556 (赞：2)

## 题解：CF2066A Object Identification

### 题意翻译

这是一个交互式问题。
 
给定一个由 $1$ 到 $n$ 的整数构成的数组 $x_1 , \dots , x_n$。裁判方还拥有一个固定但隐藏的由 $1$ 到 $n$ 的整数构成的数组 $y_1 , \dots , y_n$。

数组 $y$ 的元素对你是未知的。此外，已知对于所有 $i , x_i \neq y_i$，且所有 $(x_i , y_i)$ 对都是唯一的。
 
裁判方秘密选择了以下两个对象之一，你需要确定具体是哪一个：
 
- 对象 `A`：一个包含 $n$ 个顶点（编号 $1$ 到 $n$）的有向图，具有 $n$ 条形式为 $x_i \to y_i$ 的边。
- 对象 `B`：坐标系平面上的 $n$ 个点。第 $i$ 个点的坐标为 $(x_i , y_i)$。
 
为了猜测裁判方选择的对象，你可以进行查询。每次查询中，你必须指定两个数字 $i , j (1 \le i , j \le n , i \neq j)$。作为回应，你将收到一个数字：
 
如果裁判方选择的是对象 `A`，你将收到图中从顶点 $i$ 到顶点 $j$ 的最短路径长度（以边数计算），若无路径则返回 $0$。

如果裁判方选择的是对象 `B`，你将收到点 $i$ 和点 $j$ 的曼哈顿距离，即 $|x_i - x_j| + |y_i - y_j|$。
 
你最多可以进行 $2$ 次查询来确定裁判方选择的对象。

### 解题思路

非常好的交互题。

乍一看没思路的时候，不如思考一下**边界情况**。

因为所有 $(x_i , y_i)$ 对都是唯一的，所以如果评测机选择了 `B` 方案，那么绝对不会出现返回 $0$ 的情况。

此时我们可以发现，若 $x$ 数组不是一个**排列**，则 `A` 方案下有至少一个点没有出边，这个点到其他点的距离返回值则为 $0$。

所以，我们到目前唯一不能确定的情况只有 $x$ 是一个排列的情况。

我们考虑完下边界了，再考虑一下上边界。若询问 $x$ 数组中对应 $1$ 和 $n$ 的点，在 `B` 构造下一定会返回一个 $\ge n - 1$ 的数，在 `A` 构造下一定会返回一个 $\le n - 1$ 的数。

若返回值不是 $n - 1$，自然确定了是哪种构造方案。

现在只剩下了很少的情况。

`A` 构造必然使图成为这样：其中 start 和 end 为询问的两个点。

![pic](https://cdn.luogu.com.cn/upload/image_hosting/zmtlq5r8.png)

`B` 构造必然使图成为这样：其中点 $1$ 和 $n$ 的 $y$ 坐标相同。

![pic](https://cdn.luogu.com.cn/upload/image_hosting/s6c87odq.png)

若答案为 `A` 构造，则 $y$ 数组中其他元素都不可能指向 start，只有 end 位置对应的 $y$ 数组中的元素可能指向 start。所以若答案为 `A` 构造，则反向询问 `? end start` 一定返回 $0$（$y_\texttt{end} \neq \texttt{start}$） 或 $1$（$y_\texttt{end} = \texttt{start}$）。又因为数据范围 $n \ge 3$，所以若答案为 `B` 构造，返回的值一定是 $n - 1 \ge 2$。此时没有重复范围，答案自然可知。

经过大量分析，最后再梳理一下做题过程：

- 若 $x$ 不为排列：
  + 若询问 $x$ 中没有出现的任意元素和任意其他元素回答为 $0$，输出 `A`。
  + 否则输出 `B`。
- 若 $x$ 为排列：
  + 找到坐标 start 和 end，使得 $x_{\texttt{start}} = 1 , x_{\texttt{end}} = n$。
  + 询问 `? start end`
  + 若回答 $> n - 1$，输出 `B`。
  + 若回答 $< n - 1$，输出 `A`。
  + 若回答 $= n - 1$。
    * 询问 `? start end`
    * 若回答 $< n - 1$，输出 `A`。
    * 否则输出 `B`。

**注意多测！**

### 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t , n , a[200005] , b[200005] , k , k2;
bool vis[200005] , sol;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 1 ; i <= n ; i++)
		{
			vis[i] = 0;
		}
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
			vis[a[i]] = 1;
		}
		sol = 0;
		for(int i = 1 ; i <= n ; i++)
		{
			if(!vis[i])
			{
				if(i == 1)
				{
					cout << "? 1 2" << endl;
				}
				else
				{
					cout << "? " << i << " 1" << endl;
				}
				cin >> k;
				if(k == 0)
				{
					cout << "! A" << endl;
				}
				else
				{
					cout << "! B" << endl;
				}
				sol = 1;
				break;
			}
		}
		if(sol)
		{
			continue;
		}
		for(int i = 1 ; i <= n ; i++)
		{
			b[a[i]] = i;
		}
		cout << "? " << b[1] << ' ' << b[n] << endl;
		cin >> k;
		if(k > n - 1)
		{
			cout << "! B" << endl;
			continue;
		}
		if(k < n - 1)
		{
			cout << "! A" << endl;
			continue;
		}
		cout << "? " << b[n] << ' ' << b[1] << endl;
		cin >> k2;
		if(k != k2)
		{
			cout << "! A" << endl;
		}
		else
		{
			cout << "! B" << endl;
		}
	}
	return 0;
}
```

内容来源：[赛时提交](https://mirror.codeforces.com/contest/2067/submission/305696217)。

---

## 作者：Vct14 (赞：1)

若评测机选择的是对象 A，那么输入的就是有出边的点。如果某个点没有出现在输入中，那么这个点的出度就为 $0$，它到任何一个点都没有路径。

于是我们可以得到结论：如果输入不是排列，查询 $x_i$ 中没有出现的数 $k$ 和另外一个数（例如 $k+1$，但需要判断 $k=n$ 的情况）：若结果为 $0$，则为对象 A；否则为对象 B，因为若选择的是 B，那么查询结果一定不为 $0$。

---

如果输入的是一个排列，我们考虑怎样查询可以使得选择 A 或 B 结果不同。我们知道若选择 A，那么每个点都有一条出边，则查询两点之间的最短路径最大为 $n-1$。于是可以想到查询 $x_i=1$ 和 $x_j=n$，因为若选择 B，结果一定不小于 $n-1$。若结果小于 $n-1$，则为对象 A；若结果大于 $n-1$，则为对象 B。

若结果为 $n-1$，考虑如何询问一次找到答案。若选择 A，结果为 $n-1$ 当且仅当除 $n\to y_j$ 的边外图为一条链。则如果再查询一次 $x_j=n$ 和 $x_i=1$，那么若选择 A 结果一定为 $0$（$y_j\ne1$）或 $1$（$y_j=1$），若选择 B 结果一定与上一次查询一样。

总结一下输入是排列的情况。设 $x_i=1,x_j=n$。

先查询 `? i j`。

- 若结果小于 $n-1$，输出 `! A`。
- 若结果大于 $n-1$，输出 `! B`。
- 若结果等于 $n-1$，查询 `? j i`。
  - 若结果大于或等于 $n-1$（或与第一次查询结果一样），输出 `! B`。
  - 若结果为 $0$ 或 $1$，输出 `! A`。

因为 $n\ge3$ 所以这样做不会出现问题。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+2;
int x[N];
bool book[N];

int main(){
    int t;cin>>t;
    while(t--){
        memset(book,0,sizeof book);
        int n;cin>>n;
        bool isp=1;
        for(int i=1; i<=n; i++){
            cin>>x[i];
            if(book[x[i]]) isp=0;
            book[x[i]]=1;
        }
        int ans;
        if(!isp){
            int ask;
            for(int i=1; i<=n; i++){
                if(!book[i]){
                    ask=i;
                    break;
                }
            }
            cout<<"? "<<ask<<" "<<(ask==n?1:ask+1)<<"\n";
            cin>>ans;
            if(ans==0) cout<<"! A\n";
            else cout<<"! B\n";
        }
        else{
            int no1,non;
            for(int i=1; i<=n; i++){
                if(x[i]==1) no1=i;
                if(x[i]==n) non=i;
            }
            cout<<"? "<<no1<<" "<<non<<"\n";cin>>ans;
            if(ans<n-1) cout<<"! A\n";
            else if(ans>n-1) cout<<"! B\n";
            else{
            	cout<<"? "<<non<<" "<<no1<<"\n";cin>>ans;
            	if(ans>=n-1) cout<<"! B\n";
            	else cout<<"! A\n";
			}
        }
        fflush(stdout);
    }
    return 0;
}
```

---

## 作者：TianTianChaoFang (赞：1)

# CF2067D - Object Identification

[我的博客](https://www.cnblogs.com/TianTianChaoFangDe/p/18732564)

## 题目大意
有一个对你公开的 $x$ 数组和一个对你隐藏的 $y$ 数组，保证没有任何两个相同的 $\{x_i, y_i\}$，并且 $x_i \neq y_i$，对于这两个数组，有以下两种可能： 
* A：一个有 $n$ 个结点的有向图，每一条边从 $x_i$ 指向 $y_i$。   
* B：一个二维坐标系中的一些点，每个点的坐标为 $(x_i, y_i)$。  

你可以对这个图进行询问：  
* 若这个图是一个有向图，则你的询问 $i, j$ 为从结点 $i$ 到结点 $j$ 的最短路径长度。  
* 若这个图是一个二维坐标系，则你的询问 $i, j$ 为从点 $(x_i, y_i)$ 到 $(x_j, y_j)$ 的曼哈顿距离 $|x_i - x_j| + |y_i - y_j|$。  

现在，你有最多 $2$ 次询问机会，来确定这个图到底是一个有向图，还是一个二维坐标系。  

## 思路
很好的一个交互题，一看题目，居然只给 $2$ 次询问？！有意思。  
要区分这两种图，我们要从二者分别的特征入手：  
* 有向图：所有的边是单向的，不可反向行走，因此两个结点正着走和反着走的距离不一定相同。  
* 二维坐标系：所有的点两两之间的曼哈顿距离是相同的，因此正着走和反着走的距离都相同，并在该题目条件下，不存在重合的两个点，因此距离一定不为 $0$。  

因此，这里有一个初步的思路，挑选两个数字，正着问一次，反着问一次，判断两次询问的距离是否相同。  
但很遗憾，就算是有向图，正着和反着的距离也有可能会相同（如下图中的 $1$ 和 $3$）。  
![有向图中两点距离相同](https://cdn.luogu.com.cn/upload/image_hosting/c5yd4mra.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
因此，若问出来距离相同，仍然无法判断为有向图还是二维坐标系。  
那么，有没有什么更特殊的点，能直接作为判断标志呢？  
有的，在有向图（不含自环）中，若一个结点的出度为 $0$，也就是这个结点没有任何的出边，那么该结点无法到达任何其他结点，即距离为 $0$！  
也就是说，如果有 $1$ 到 $n$ 中的某一个数在数组 $x$ 中一次也没有出现，那么这个结点的出度一定为 $0$，此时，只需要把它作为询问的第一个数，再任意询问另一个数，如果距离为 $0$，则是有向图，如果距离不为 $0$，则是二维坐标系。  

当然，不难发现，还有一种情况会发生，那就是 $1$ 到 $n$ 中的所有数字均在 $x$ 数组中出现，并且一定只会出现一次（如果有某个数字出现两次及以上，则一定会有一个数字不出现）。  
在这种情况中，如果是有向图，则不存在出度为 $0$ 的结点，又应该如何判断呢？  
这里我们就要用到我们 $x$ 数组的信息了，由于 $x$ 数组是已知的，再结合曼哈顿距离的定义，我们可以得出下面这个显而易见的结论：$d(i, j) \geq |x_j - x_i|$。  
因此，我们可以用这个不等式来区分有向图和二维坐标系，那选用哪两个数字来询问呢？  
这里我们选取 $1$ 和 $n$ 在 $x$ 数组中的位置 $a,b$，因为 $d(a, b) \geq n - 1$，而我们的有向图中一共有 $n$ 个结点，任意两点的距离最大值只可能达到 $n - 1$，因此如果询问 $1$ 和 $n$ 在 $x$ 数组中的位置后，如果得到的答案 $> n - 1$，则一定是二维坐标系，如果得到的答案 $< n - 1$，则一定是有向图。  

如此一番操作后，我们还剩下一次询问机会，并且如果这个时候还没有得出答案，则只剩下一种情况：$d(a, b) = n - 1$！  
再仔细观察可以发现，在有 $n$ 个结点的有向图中，每个结点的出度均为 $1$，两点最短路径长为 $n - 1$，那这时候先不管终点 $b$ 的那一条出边，此时这个图，一定是一个以 $a$ 为起点，$b$ 为终点的链！  
此时，我们仅剩一条边没有连接，也就是数字 $n$ 对应的 $b$ 结点，我们注意到题目给出的数据范围 $n \geq 3$，因此，$b$ 结点要么向其他结点连边，无法到达结点 $a$，要么向 $a$ 连边，但 $d(b, a) = 1 \neq d(a, b)$，所以一定是有向图。  
因此这时只需要再询问一次 $d(b, a)$，判断 $d(a, b)$ 是否等于 $d(b, a)$，若等于，则是二维坐标系，否则是有向图，总询问次数 $2$ 次，通过！  

## AC CODE
```cpp
const int N = 2e5 + 9;
int a[N];
int p[N];
int cnt[N];

int ask(int x, int y) {
    cout << "? " << x << ' ' << y << endl;
    int op;cin >> op;
    return op;
}

void solve()
{
    int n;cin >> n;
    for(int i = 1;i <= n;i ++)cin >> a[i];
    for(int i = 1;i <= n;i ++)cnt[i] = 0;

    for(int i = 1;i <= n;i ++)cnt[a[i]] ++, p[a[i]] = i;

    for(int i = 1;i <= n;i ++) {
        if(!cnt[i]) {
            if(ask(i, (i % n + 1)) == 0) {
                cout << "! A" << endl;
            } else {
                cout << "! B" << endl;
            }
            return;
        }
    }

    int ck = ask(p[1], p[n]);

    if(ck >= n) {
        cout << "! B" << endl;
        return;
    }

    if(ck < n - 1) {
        cout << "! A" << endl;
        return;
    }

    int dk = ask(p[n], p[1]);

    if(dk == ck) {
        cout << "! B" << endl;
    } else {
        cout << "! A" << endl;
    }
}
```

---

## 作者：_O_v_O_ (赞：1)

首先，若 $x$ 不是一个排列，那么我们就询问一个 $x$ 中没有的正整数，设它为 $k$，然后再随便选个数 $m$，询问 $\tt ?\ k\ m$，若 $ans_1=0$，那么为项目 B，否则为项目 A。因为 $x$ 中不存在这个正整数，所以这个编号的结点没有出边，也就到不了别的点。

那么 $x$ 就是一个排列了，我们设 $c_i$ 为 $i$ 在 $x$ 中的下标，我们就不妨询问 $\tt?\ c_1\ c_n$。若 $ans_1<n-1$，那么肯定为项目 B，因为 $|x_a-x_b|$ 已经达到了 $n-1$。若 $ans_1>n-1$，那么肯定为项目 A，因为若一条路径长度比 $n-1$ 大，那么肯定不是一张图的最短路。

那么 $ans_1=n-1$ 呢？只剩一次询问了。

我们注意到，若 $ans_1=n-1$，则 $c_1$ 到 $c_n$ 的最短路已经经过了 $n-1$ 条有向边，若询问 $\tt?\ c_n\ c_1$，$ans_2$ 要么为 $0$，要么为 $1$。所以我们这样就可以判定了。

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF2066A)

像这种询问次数很少的交互题，先去寻找突破点在哪里。

首先注意到 $(x_i,y_i)$ 成对不同，所以如果交互库想字母是 `B` 那么回答一定不为 $0$。

我们会发现如果有 $1$ 到 $n$ 中的数字没有出现在 $x$ 中那么就说明它在图中出度为 $0$，询问它与另一个结点，回答 $0$ 说明交互库想的是 `A`，否则是 `B`。

接下来考虑 $x$ 是排列，说明每个点的出度有且只有 $1$。考虑从字母 `B` 入手，询问的 $i$ 和 $j$ 保证 $x_i=1$ 且 $x_j=n$，或者相反，那么如果交互库想的是字母 `B`，那么回答的数肯定会大于等于 $n-1$，否则一定会小于等于 $n-1$，因为总共只有 $n$ 条边而且路径终点自己也有一条出边。于是第一次询问完之后只要回答不为 $n-1$ 就能判断交互库想的是哪个字母了。

现在考虑第二次询问，其实只要将第一次询问反过来再问一次就行了。如果交互库想的是字母 `B`，那么回答跟第一次询问一样。如果交互库想的是字母 `A`，那么由于上一次询问回答的是 $n-1$，所以反过来之后的回答只有可能是 $0$ 或 $1$，也就是这一次的路径起点的出边不指向路径终点或直接指向路径终点，可以发现由于上一次回答 $n-1$，所以前者必然无法到达路径终点，且 $3\le n$，所以 $n-1$ 不会等于 $0$ 或 $1$，于是我们就在两次询问下判断出了交互库想的字母。

# CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
int n;
int x[200010],dy[200010],v[200010];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int ans=-1;
		scanf("%d",&n);
		for(register int i=1;i<=n;i++) scanf("%d",&x[i]),v[x[i]]=1;
		int a=0,b=0;
		for(register int i=1;i<=n;i++)
			if(!v[i])
			{
				a=i;
				break;
			}
		for(register int i=1;i<=n;i++)
			if(v[i])
			{
				b=i;
				break;
			}
		if(a&&b)
		{
			int hd;
			printf("? %d %d\n",a,b),fflush(stdout);
			scanf("%d",&hd),fflush(stdout);
			printf("? %d %d\n",a,b),fflush(stdout);
			scanf("%d",&hd),fflush(stdout);
			if(!hd) ans=1;
			else ans=2;
		}
		if(ans==-1)
		{
			int hd,hd2;
			for(register int i=1;i<=n;i++) dy[x[i]]=i;
			a=dy[1],b=dy[n];
			printf("? %d %d\n",a,b),fflush(stdout);
			scanf("%d",&hd),fflush(stdout);
			if(hd<n-1) ans=1;
			if(hd>n-1) ans=2;
			printf("? %d %d\n",b,a),fflush(stdout);
			scanf("%d",&hd2),fflush(stdout);
			if(ans==-1)
			{
				if(hd==hd2) ans=2;
				else ans=1;
			}
		}
		if(ans==1) printf("! A\n"),fflush(stdout);
		else printf("! B\n"),fflush(stdout);
		for(register int i=1;i<=n;i++) v[i]=dy[i]=0;
	}
	return 0;
}
```

---

## 作者：zyb_txdy (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF2066A)

### 题意

本题多测、交互。每次询问会给定一个长度为 $n$ 的正整数序列 $x$，交互库还有一个长度为 $n$ 的正整数序列 $y$。$x$ 和 $y$ 满足

1. $\forall 1 \le i \le n$，$x_i \neq y_i$

2. 数对 $(x_i, y_i)$ 两两不同。

现在交互库有如下两个物品中的一个，这两个物品分别是：

- A：一张有向图，里面的边都是 $x_i \to y_i$。

- B：一个平面，上面有 $(x_i, y_i)$ 形式的 $n$ 个点。

现在你有两次询问机会，每次询问可以给出两个 **不相同** 的数 $i$，$j$。如果交互库有物品 A，则它会返回 $i$ 与 $j$ 之间最短路经过的边数（若无路径则返回 $0$）；否则，它会返回 $(x_i, y_i)$ 与 $(x_j, y_j)$ 之间的曼哈顿距离。请在两次询问后确定交互库拥有的物品是什么。

数据范围：$3 \le n \le 2 \times 10^5$，$1 \le x_i$，$y_i \le n$。

### 分析

下文将以“图”代替物品 A，“平面”代替物品 B。

观察我们可以通过询问得到什么信息。

首先考虑一次询问得到答案的情况。因为点对 $(x_i, y_i)$ 两两不同，故交互库只会在有图的情况下返回 $0$，这个是显然的。其次考虑询问了 $i$，$j$，那么 $(x_i, y_i)$ 和 $(x_j, y_j)$ 之间的曼哈顿距离必然是不小于 $|x_i - x_j|$ 的。那么如果返回值比 $|x_i - x_j|$ 要小，则答案也肯定是图。

接下来考虑如何通过询问确定答案。首先我们可以发现，如果第一次随便取两个数询问的话，我们能得到的信息是极其有限的，而确定 $y$ 的形态之类的更是不可能。

由于我们只有两次询问的机会，故第一次询问肯定要询问特殊值。

一个简单的想法是：设序列 $x$ 中的最小值和最大值分别为 $p$ 和 $q$，考虑询问这两个值所在的下标。通过前文的分析，若返回值大于 $q - p$，则答案必定是平面。而因为最短路径必然不可能有环，故最短路径长度必定不大于 $q - p$。因此，若返回值小于 $q - p$，答案必定为图。于是只需要考虑返回值为 $q - p$ 的情况。

设 $p$，$q$ 的下标为 $i$，$j$，则手玩一下就会发现，答案为图且「$i$ 到 $j$ 的距离」与「$j$ 到 $i$ 的距离」都为 $q - p$ 的情况是不太可能出现的。

进一步地，我们可以发现，当序列 $x$ 是 $1$ 到 $n$ 的排列时，若 $1$ 到 $n$ 的距离为 $n - 1$，则 $n$ 以外的点的出边都被限制，故 $n$ 到 $1$ 的距离必定为 $0$ 或 $1$。同时，在序列 $x$ 不是一个排列时，只需要询问一个未出现的点到任意点的距离即可获得答案。原因较为显然：当答案为图时，未出现的点到任意点的距离都为 $0$，而答案为平面时则相反。

这样我们就做出这道题了，梳理一下思路：

检查 $x$ 是否为 $1$ 到 $n$ 的排列。

- 若不是，则询问一个未出现的点到任意点的距离。若返回值为 $0$ 则答案为 A，否则为 B。

- 若是，则第一次询问值为 $1$ 的下标 $i$ 到值为 $n$ 的下标 $j$ 的距离。若返回值小于 $n - 1$，答案为 A；大于 $n - 1$，答案为 B。

  若返回值等于 $n - 1$，则询问 $j$ 到 $i$ 的距离。若返回值不为 $n - 1$，则答案为 A，否则答案为 B。

code：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
const int N = 2e5 + 5;
 
int T, n, res, buc[N], a[N], b[N];
 
void Output() {
	cout << "? 1 2" << endl;
	cin >> res;
}
 
void Solve() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	for (int i = 1; i <= n; ++i) buc[i] = 0;
	for (int i = 1; i <= n; ++i) buc[a[i]] = 1;
	for (int i = 1; i <= n; ++i) {
		if (buc[i] == 0) {
			cout << "? " << i << " ";
			if (i == 1) cout << "2" << endl;
			else cout << "1" << endl;
			cin >> res;
			if (res == 0) {
				Output(); cout << "! A" << endl;
				return ;
			} else {
				Output(); cout << "! B" << endl;
				return ;
			}
		}
	}
	int p, q;
	for (int i = 1; i <= n; ++i) {
		if (a[i] == 1) p = i;
		if (a[i] == n) q = i;
	}
	cout << "? " << p << " " << q << endl;
	cin >> res;
	if (res < n - 1) { Output(); cout << "! A" << endl; return ; }
	else if (res > n - 1) { Output(); cout << "! B" << endl; return ; }
	cout << "? " << q << " " << p << endl;
	cin >> res;
	if (res == n - 1) { cout << "! B" << endl; return ; }
	else { cout << "! A" << endl; return ; }
}
 
signed main() {
	cin >> T;
	while (T--) Solve();
	return 0;
}
```

---

## 作者：rubbishZZZ (赞：0)

## CF2066A Object Identification



#### 题意：

- 给定一个整数数组 $x_1, x_2, \dots, x_n$，其中每个元素的值都在 $1$ 到 $n$ 之间。另有一个固定但隐藏的数组 $y_1, y_2, \dots, y_n$，其中每个元素的值也在 $1$ 到 $n$ 之间。已知对于所有 $i$，有 $x_i \neq y_i$，且所有的 $(x_i, y_i)$ 都是不同的。

  陪审团已经秘密地想好了一种对象，你需要确定它是哪一种：

  **对象 A**：一个有 $n$ 个顶点的有向图，顶点编号为 $1$ 到 $n$，图中有 $n$ 条边，边的形式为 $x_i \to y_i$。

  **对象 B**：平面上的 $n$ 个点，第 $i$ 个点的坐标为 $(x_i, y_i)$。

  为了猜测陪审团想到了哪种对象，你可以进行查询。在每次查询中，你需要指定两个数字 $i, j$ （$1 \leq i, j \leq n, i \neq j$）。查询的结果是一个数字：

  - 如果陪审团想的是对象 A，你会收到从顶点 $i$ 到顶点 $j$ 的最短路径长度（以边数计），如果没有路径，则返回 $0$。
  - 如果陪审团想的是对象 B，你会收到点 $i$ 和点 $j$ 之间的曼哈顿距离，计算公式为 $|x_i - x_j| + |y_i - y_j|$。

  你可以进行 $2$ 次查询，以确定陪审团想的是哪一个对象。



#### 解法：

- 如果一个点没有出边，那么在图上这个点与其他点都不联通。我们只需要询问这个点以及其他某个点的值。由于 $(x_i,y_i)$ 互不相同，因此如果是 $0$ 就是 A，如果非 $0$ 就是 $B$。

  如果所有点都有出边，那么**图上**两点 $u,v$ 之间的距离和 $dis_{u,v}+dis_{v,u}\leq n$。而**平面上**我们询问 $x$ 坐标为 $1/n$ 的两点，一定距离相同且 $\geq n-1$。由此判断即可。



#### 代码：

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#include <random>
#include <cassert>
#include <numeric>
#include <cmath>
#include <bitset>
#include <ext/pb_ds/assoc_container.hpp>
#define pii pair<int, int>
#define fi first
#define se second
#define MP make_pair
#define ep emplace
#define eb emplace_back
//#define int long long
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
typedef double db;
typedef long double ldb;
typedef long long ll;
//typedef __int128 lll;
typedef unsigned long long ull;
typedef unsigned int ui;
using namespace std;
using namespace __gnu_pbds;
bool Mbe;

//char buf[1<<20],*p1,*p2;
//#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1<<20,stdin), p1 == p2) ? 0 : *p1++)
int read() {
	int s = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') f ^= (c == '-'), c = getchar();
	while (c >= '0' && c <= '9') s = s * 10 + c - '0', c = getchar();
	return f ? s : -s;
}
template<typename T>void chkmax(T&x,const T&y){if(x<y)x=y;}
template<typename T>void chkmin(T&x,const T&y){if(x>y)x=y;}
//int fplus(int x,int y){return x+y>=mod?x+y-mod:x+y;}
//void Fplus(int&x,int y){x=fplus(x,y);}
//int fminus(int x,int y){return x-y<0?x+mod-y:x-y;}
//void Fminus(int&x,int y){x=fminus(x,y);}

const int N=200005;
int n,vis[N];

bool Med;
signed main() {
	fprintf(stderr,"%.3lfMb\n",(&Mbe-&Med)/1024./1024.);
	for(int T=read();T--;){
		n=read();
		rep(i,1,n)vis[i]=0;
		rep(i,1,n)vis[read()]=i;
		bool flag=0;
		rep(i,1,n)if(!vis[i]){
			printf("? %d %d\n",i,i%n+1),fflush(stdout);
			int x=read();
			if(x)printf("! B\n"),fflush(stdout);
			else printf("! A\n"),fflush(stdout);
			flag=1;
			break;
		}
		if(flag)continue;
		printf("? %d %d\n",vis[1],vis[n]),fflush(stdout);
		int x=read();
		printf("? %d %d\n",vis[n],vis[1]),fflush(stdout);
		int y=read();
		if(x==y&&x>=n-1)printf("! B\n"),fflush(stdout);
		else printf("! A\n"),fflush(stdout);
	}
	return 0;
}
```

---

## 作者：Engulf (赞：0)

### 题意

交互库给你长为 $n$ 的数组 $x_i$，同时它有一个隐藏的 **固定** 的长为 $n$ 的数组 $y_i$，且 $\forall i, (x_i, y_i)$ 两两不同。$1\le x_i,y_i \le n$。

交互库想了以下结构中的一种：
- 结构 A，一张有向图，由边集 $x_i \to y_i$ 构成。
- 结构 B，一个平面直角坐标系，且上面有 $n$ 个点 $(x_i, y_i)$。

可以询问 $(i, j), i \neq j$，交互库会返回：
- 若交互库想的是结构 A，返回节点 $i$ 到 $j$ 的最短路径长度（边数），若 $i$ 无法到达 $j$ 返回 $0$。
- 若交互库想的是结构 B，返回点 $(x_i, y_i)$ 和点 $(x_j, y_j)$ 的曼哈顿距离，即 $|x_i - x_j| + |y_i - y_j|$。

在 $2$ 次询问内猜出交互库想的结构。

### 分析

讨论 $x$ 的构成：
- 若 $x$ 不是排列，即 $\exist k \in [1, n], k \notin x$，说明 $k$ 的出度为 $0$。
  - 若交互库想的是结构 A，节点 $k$ 哪都去不了。
  - 所以，只需询问 $k$ 和任意一个不是 $k$ 的节点，若交互库返回了 $0$，说明是结构 A，否则是结构 B。
- 若 $x$ 是排列，即每个 $1$ 到 $n$ 的数在 $x$ 中恰好出现了一次。
  - 在平面直角坐标系上，横坐标为 $1$ 和 $n$ 的点都存在且仅有这一对，根据曼哈顿距离的表达式可知，询问 $(1, n)$，若交互库想的是结构 B，返回值一定 $\ge n - 1$。
  - 如果是结构 A，此时的图是内向基环树森林，$1$ 和 $n$ 的距离 $\le n - 1$。重叠了一个 $n - 1$。
  - 其实这个很好处理，只有在图是一条链，并且 $n$ 连回 $1$ 的时候，$\textrm{dis}(1, n)$ 取到最大值 $n - 1$。
  - 发现我们还剩一次询问的机会，不妨再询问 $(n, 1)$，如果是结构 A，返回值就会变为 $1$；如果结果和之前一样，说明是结构 B。

### 做法

由分析我们得到了做法：
- 若 $x$ 不是排列，随便找一个 $k\notin x$，询问 $(k, k+1)$（若 $k = n$，询问 $(k, 1)$）。
  - 若返回 $0$，结构 A。
  - 否则结构 B。
- 若 $x$ 是排列，找到 $x_i = 1, x_j = n$，询问 $(i, j)$ 和 $(j, i)$。
  - 返回值均 $\ge n - 1$，结构 B。
  - 否则结构 A。

---

## 作者：SICKO (赞：0)

我们正反查询一个点对，若出现了没有距离的情况，则一定是图 $A$，因为只有图 $A$ 会出现一个点无法到达另一个点的情况。 

所以我们思考，有向图什么情况下一定会出现这种情况？那就是存在一个点没有出边的情况。所以对于序列 $X = {x_1, x_2, \dots, x_n}$ 且 $x_i \in [1, n]$，如果有数 $a$ 没有出现，也就是 $a \in [1, n]$ 且 $a \notin X$，我们就查询这个 $a$ 与其他任意一个点。如果两次结果都有值，则是图 $B$，否则就是图 $A$。

如果所有数都出现了，也就是说 $X$ 是一个 $[1, n]$ 的排列，我们观察到，对于图 $A$，可能会出现环，使得我们查询到的点两两距离相同，此时如何查询呢？我们查询 $x_{a} = 1$ 与 $x_{b} = n$ 对应的点对 $(a, b)$，若两次结果和大于 $n$ 一定是 $B$，否则是 $A$。

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6+6;
const int INF = 1e18;

struct node {
    int x, id;
    bool operator < (const node &A) const {
        return x < A.x;
    }
    bool operator == (const node &A) const {
        return x == A.x;
    }
};

void solve() {
    int n; cin>>n;
    vector<node> vec(n);
    vector<int> vis(n+1);
    for(int i=0; i<n; i++) {
        int x; cin>>x;
        vec[i]= {x, i+1};
        vis[x] = 1;
    }
    int nap = 0, ort = n, res1, res2;
    for(int i=1; i<=n; i++) {
        if(!vis[i]) nap = i;
    }
    if(nap == ort) ort = 1;
    if(nap) {
        cout<<"? "<<nap<<" "<<ort<<"\n";
        cout.flush();
        cin>>res1;
        cout<<"? "<<ort<<" "<<nap<<"\n";
        cout.flush();
        cin>>res2;
        if(res1 && res2) cout<<"! B\n";
        else cout<<"! A\n";
        cout.flush();
    } else {
        sort(vec.begin(), vec.end());
        nap = vec.front().id, ort = vec.back().id;
        cout<<"? "<<nap<<" "<<ort<<"\n";
        cout.flush();
        cin>>res1;
        cout<<"? "<<ort<<" "<<nap<<"\n";
        cout.flush();
        cin>>res2;
        if(res1 + res2 > n) cout<<"! B\n";
        else cout<<"! A\n";
        cout.flush();
    }
}

signed main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1;
    cin >> T;
    for(int i=1; i<=T; i++) solve();
    return 0;
}
```

---

## 作者：Day_Tao (赞：0)

考虑 $A,B$ 两种情况各自的性质：

- A：对于每种查询返回两点的最短路。会返回 $0$。

- B：对于每种查询返回两点的曼哈顿距离，由于保证所有点对不同，所以不会返回 $0$。

容易发现题目与 $x$ 数组的顺序无关，并与具体出现的数字无关，所以我们只需要考虑出现了几种数。

这就启示我们分成 $x$ 是排列和 $x$ 不是排列两种情况讨论。

- $x$ 不为排列  

  这就说明至少存在一个点不存在出边（记为 $i$），那么对于 $j\neq i$，询问 $i\ j$，如果答案为 $A$，那么得到的数字为 $0$，如果得到的数字非 $0$ 就肯定是 $B$。

- $x$ 为排列  

  注意到如果答案为 $B$，曼哈顿距离与两点的先后顺序没有关系，所以必然满足对于 $i\neq j$，询问 $i\ j$ 和 $j\ i$ 给出的值一样。

  又因为 $x$ 是个排列，所以存在一个构造，询问 $x_i$ 分别为 $1$ 和 $n$ 的两个位置，所给出的数一定 $\ge n-1$。

  我们记这两个位置为 $p_1$ 和 $p_2$，询问 $p_1\ p_2$ 和 $p_2\ p_1$，如果满足两次询问数值相等且 $\ge n-1$，最终答案就一定为 $B$。否则为 $A$。

  给出证明：如果数值不等，显然为 $A$。对于情况 $A$，一共有 $n$ 条边，如果存在一条从 $p_1$ 到 $p_2$，长度为 $n-1$ 的最短路径，那么用剩下的一条边显然无法构造出一条长为 $n-1$ 的从 $p_2$ 到 $p_1$ 的最短路径。

然后就做完了。

比较懒所以用 `set` 记录一个数是否出现，实现是 $O(n\log n)$ 的，可以做到 $O(n)$。

**code：**

```cpp
int n,a[N],x,y,p1,p2;set<int>S;
inline void qu(int x,int y){cout<<"? "<<x<<' '<<y<<endl;}
inline void an(char c){cout<<"! "<<c<<endl;}
inline void SOLVE(){
	S.clear();cin>>n;F(i,1,n)a[i]=rd(),S.insert(a[i]);
	F(i,1,n)if(S.find(i)==S.end()){
		if(i==1)qu(i,2);else qu(i,1);cin>>x;
		qu(1,n),cin>>y;if(x)an('B');else an('A');return;
	}F(i,1,n)if(a[i]==1)p1=i;else if(a[i]==n)p2=i;
	qu(p1,p2),cin>>x,qu(p2,p1),cin>>y;
	if(x==y&&x>=n-1)an('B');else an('A');
}
```

---

## 作者：2020kanade (赞：0)

前情提要：这把这题交互库锅了，打的 div2。

交互库修好之后重测了。

其中，赛时过了此题，赛后重测 FST，且下分的人，本场不计分。

我：赛时过了此题，赛后没 FST，下分。

问就是被 BC 创似了（没写出来），最后这题一个小地方调了好几遍（没看出来），+5。

回到正题。这题不难，大概 1600-1700？

注意到如果这两个数组描述的是一个二维平面上的点集，那么对于二维平面上的任意两个点，只要其中一维坐标不同，其曼哈顿距离一定是大于 $0$ 的。

之后，考虑图情况的形态：本质上是给了 $n$ 条边，那么由鸽巢原理，要么这张图是每个点有且仅有一条出边的图也就是内向基环树，要么一定有点的出度为 $0$。

对于后一种情况，我们将其作为起点，任意一个其他点作为终点，询问得到的答案在图上的话一定是 $0$（显然对应的路径是一定不存在的），否则由前面的推论，一定不是 $0$。

因此我们先当成一张图，统计每个点的出度，对于 $0$ 出度点，把它作为起点，找任意一个与它不同的点作为终点询问距离，是 $0$ 就是图，否则是二维平面点集。

如果没有零出度点，这东西是图的话一定是个内向基环树森林。注意到对于二维平面上的两个点，交换它们的顺序不会影响曼哈顿距离，而在内向基环树森林上，起点与终点交换的询问答案一致时，它们要么相互都不可达（此时都是 $0$）要么一定在同一个偶环的两端，且距离一定是环长的一半。

显然，这个距离不会超过 $\lfloor \frac{n}{2} \rfloor$，且对于 $\forall n \ge 3$，由 $n-1\gt \lfloor \frac{n}{2} \rfloor$，一定可以进行判断。

此时，我们找到标号为 $1$ 和 $n$ 对应的点的数组下标，正反询问两次，如果答案都一致且 $\gt \lfloor \frac{n}{2} \rfloor$ 那么一定是二维平面（我场上实现是判断 $\ge n-1$），否则一定是有向图。

时间复杂度可以做到线性。很简单的题，适合萌新练交互。


```cpp
//written by Amekawa_kanade
#include<bits/stdc++.h>
using namespace std;
void syncoff()//___k you sync
{
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}
const int N=5e5+11;
using ll=long long;
using i128=__int128;
using ld=long double;
const ll mod1=998244353;
const ll mod2=1e9+7;
const ll mod3=1e9+9;
int t,n,k,m,q;
int ask(int u,int v)
{
	int xx;
	cout<<"? "<<u<<' '<<v<<endl;
	cin>>xx;return xx;
}
void answer(char xx)
{
	cout<<"! "<<xx<<endl;
}
void solve1(int x,int y)
{
	//assert(x!=y);
	int d1=ask(x,y);
	if(d1==0) answer('A');
	else answer('B');
}
void solve2(int x,int y)
{
	//assert(x==1&&y==n);
	int d1=ask(x,y);
	int d2=ask(y,x);
	if((d1==0)||(d2==0)||(d1!=d2)) answer('A');
	else if((d1==d2)&&(d1>=(n-1))) answer('B');
	else answer('A');
}
void solve()
{
	cin>>n;
	vector<int> a(n+1);
	int mx=0,mi=n+1;
	for(int i=1;i<=n;++i) cin>>a[i],mx=max(mx,a[i]),mi=min(mi,a[i]);
	set<int> cnt;
	for(int i=1;i<=n;++i) cnt.insert(a[i]);
	if((cnt.size())<n)
	{
		for(int i=1;i<=n;++i) if(!cnt.contains(i))
		{
			solve1(i,(*cnt.begin()));break;
		}
	}
	else
	{
		vector<int> rnk(n+1,0);
		for(int i=1;i<=n;++i) rnk[a[i]]=i;
		solve2(rnk[1],rnk[n]);
	}
}
int main()
{
 	t=1;
    cin>>t;
    while(t--) solve();
    return 0;
}

```

---

## 作者：I_will_AKIOI (赞：0)

手玩样例，可以发现样例隐藏着一些信息。

+ 如果查询结果为 $0$，则答案为 A。

+ 如果答案为 B，那么查询 $(x,y)$ 的结果和查询 $(y,x)$ 的结果相同。

因此我们的查询要尽可能满足这两条性质，这样才能得到更多的信息。

考虑满足第一条性质。发现如果答案为 A，且若把有向图的边都视为无向边，图不连通，那么肯定有两个点不连通。发现这张图为一个基环内向森林，因此若一个点没有出边，则他不能到达其他点，而我们已知的 $x_i$ 恰好对应着出边，因此如果 $x$ 不是一个排列，那么肯定有 $1\sim n$ 中至少有一个数没有在 $x$ 中出现，找到一个没出现过的数 $x_{num}$，并且询问 $(x_1,num)$，若结果为 $0$ 则答案为 A，否则答案为 B。

然后考虑满足第二条性质，那么肯定要查询 $(x,y)$ 和 $(y,x)$。但是如果答案为 A，且图为一个环，那么可能会出现 $(x,y)$ 和 $(y,x)$ 相等的情况，怎么规避这个问题呢？发现最短路 $\le n-1$。若答案为 B，则满足 $x_i=1,x_j=n$ 的 $i,j$ 两点，这两点的曼哈顿距离 $\ge n-1$。因此找到 $i,j$，然后进行查询，这样就只剩答案为 $n-1$ 的情况了。

这时就很简单了，$i$ 到 $j$，最短路为 $n-1$，肯定是环上相邻的两点，那么 $j$ 到 $i$ 的最短路为 $1$。由于 $n\ge 3$，所以不用担心 $n-1=1$ 的情况。所以再查询一遍 $(j,i)$，如果结果和 $(i,j)$ 相同且不为 $0$，那么答案为 B，否则答案为 A。

```cpp
#include<bits/stdc++.h>
#define N 200005
#pragma GCC optimize("O3")
using namespace std;
int n,p1,p2,a[N];
bool vis[N];
int query(int x,int y)
{
	int res;
	cout<<"? "<<x<<" "<<y<<endl;
	cin>>res;
	return res;
}
void answer(char x)
{
	cout<<"! "<<x<<endl;
	return;
}
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++) vis[a[i]]=0;
	for(int i=1;i<=n;i++) cin>>a[i],vis[a[i]]=1;
	for(int i=1;i<=n;i++)
	{
		if(vis[i]) continue;
		if(!query(i,a[1])) answer('A');
		else answer('B');
		return;
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]==1) p1=i;
		if(a[i]==n) p2=i;
	}
	int res1=query(p1,p2),res2=query(p2,p1);
	if(res1>n-1) answer('B');
	else if(res1<n-1) answer('A');
	else if(res1==res2) answer('B');
	else answer('A');
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

