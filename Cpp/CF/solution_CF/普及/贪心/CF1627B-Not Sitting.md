# Not Sitting

## 题目描述

Rahul and Tina are looking forward to starting their new year at college. As they enter their new classroom, they observe the seats of students are arranged in a $ n \times m $ grid. The seat in row $ r $ and column $ c $ is denoted by $ (r, c) $ , and the distance between two seats $ (a,b) $ and $ (c,d) $ is $ |a-c| + |b-d| $ .

As the class president, Tina has access to exactly $ k $ buckets of pink paint. The following process occurs.

- First, Tina chooses exactly $ k $ seats in the classroom to paint with pink paint. One bucket of paint can paint exactly one seat.
- After Tina has painted $ k $ seats in the previous step, Rahul chooses where he sits. He will not choose a seat that has been painted pink due to his hatred of the colour pink.
- After Rahul has chosen his seat, Tina chooses a seat for herself. She can choose any of the seats, painted or not, other than the one chosen by Rahul.

Rahul wants to choose a seat such that he sits as close to Tina as possible. However, Tina wants to sit as far away from Rahul as possible due to some complicated relationship history that we couldn't fit into the statement!

Now, Rahul wonders for $ k = 0, 1, \dots, n \cdot m - 1 $ , if Tina has $ k $ buckets of paint, how close can Rahul sit to Tina, if both Rahul and Tina are aware of each other's intentions and they both act as strategically as possible? Please help satisfy Rahul's curiosity!

## 说明/提示

One possible sequence of choices for the first testcase where Tina has $ k=3 $ buckets of paints is as follows.

Tina paints the seats at positions $ (1, 2) $ , $ (2, 2) $ , $ (3, 2) $ with pink paint. Rahul chooses the seat at $ (3, 1) $ after which Tina chooses to sit at $ (1, 3) $ .

Therefore, the distance between Tina and Rahul is $ |3-1| + |1-3| = 4 $ , and we can prove that this is indeed the minimum possible distance under the given constraints. There may be other choices of seats which lead to the same answer as well.

For $ k=0 $ in the first test case, Rahul can decide to sit at $ (2, 2) $ and Tina can decide to sit at $ (4, 3) $ so the distance between them would be $ |2 - 4| + |2 - 3| = 3 $ .

Below are pictorial representations of the $ k=3 $ and $ k=0 $ cases for the first test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627B/135a6759a6ba23b198694ead1674597ee527f081.png) A possible seating arrangement for $ k=3 $ . ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1627B/f8d6f4f57279fb43f8c4bcfe0a1490483d3f4037.png) A possible seating arrangement for $ k=0 $ .

## 样例 #1

### 输入

```
2
4 3
1 2```

### 输出

```
3 3 4 4 4 4 4 4 5 5 5 5 
1 1```

# 题解

## 作者：沉石鱼惊旋 (赞：6)

### 题目翻译

A 和 B 两个人，在 $n \times m$ 的教室找位置。A 想和 B 坐得近，B 想和 A 坐得远，由 A 先选位置，请问对于所有情况，A 与 B 之间的距离各是多少？

补充：距离的定义为：$a_{i_1,j_1}$ 与 $a_{i_2,j_2}$ 距离为 $\left|i_1-i_2\right|+\left|j_1-j_2\right|$

### 题目思路

A 会选什么位置，我们不用考虑，因为题目求所有情况，不是最优或最坏，所以只需考虑 B 坐的位置。由于想离得远，那么不管 A 坐哪，B 一定选择四个角上离得最远的位置。

根据上述分析，我们只需穷举 A 坐的位置，并且每次判断 A 的位置与四个角的距离，就可以得出所有结果。

### AC代码

```cpp
int juli(int x1,int y1,int x2,int y2)//求距离函数
{
	return abs(x1-x2)+abs(y1-y2);
}
void solve()
{
	multiset<int>s;//答案要求排序，set自动排序+去重，mutiset自动排序+不去重
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)//双重循环穷举答案
		{
			s.insert(max({juli(i,j,1,1),juli(i,j,1,m),juli(i,j,n,1),juli(i,j,n,m)}));//判断四个角的最大距离
		}
	}
	for(auto i:s)cout<<i<<" ";//输出答案
	cout<<endl;
}

```

多组数据，代码未全。请勿copy，当心踩坑！

[完整代码在这](https://codeforces.com/contest/1627/submission/142843751)

### 科普一个热知识：

可能有些同学对于 ```s.insert(max({juli(i,j,1,1),juli(i,j,1,m),juli(i,j,n,1),juli(i,j,n,m)})); ``` 这一行有疑惑，本机运行可能报错。其实这是C++20新语法，之前求多个最大值要写很多 ```max()```，现在只需 ```max({})```，在大括号里写上多个值，如这样：

求 a,b,c,d 的最大值

正常代码 ```cout<<max(max(a,b),max(c,d))<<endl;``` 要写3个 ```max()```，现在只需 ```cout<<max({a,b,c,d})<<endl;``` 即可。



---

## 作者：_QWQ__QWQ_ (赞：1)

# Not Sitting

## 题面翻译

Rahul 和 Tina 在玩一个游戏。游戏在一个 $n\times m$ 的网格图上进行，记第 $r$ 行第 $c$ 列上的格子为 $(r,c)$。定义 $(a,b)$ 与 $(c,d)$ 之间的距离为 $\left|a-c\right|+\left|b-d\right|$。

游戏开始后，Tina 会选择恰好 $k$ 个格子，并将其涂成粉红色。涂完以后，Rahul 会选择任意一个**没有被涂成粉红色的格子**并在那个格子上坐下。此后，Tina 也会选择任意一个格子（**包括被涂成粉红色和没有被涂成粉红色的格子**）并在那个格子上坐下。Rahul 希望他和 Tina 之间的距离尽可能近，而 Tina 希望她和 Rahul 之间的距离尽可能远。于是，对于所有的 $k\in[0,n\times m-1]\cap\mathbb N ^*$，Rahul 都想知道他和 Tina 之间的距离是多少。

数据范围：

- $t$ 组数据，$1\leqslant t\leqslant 5\times 10^4$。
- $2\leqslant n\times m,\sum(n\times m)\leqslant 10^5$。



## 样例 #1

### 样例输入 #1

```
2
4 3
1 2
```

### 样例输出 #1

```
3 3 4 4 4 4 4 4 5 5 5 5 
1 1
```


### 主要思路：模拟+贪心


Rahul 先选择位置，假设刚开始所有位置都未被涂色，那么 Rahul 一定会选择最靠近中间的某个位置；而 Tina 一定会选择四个墙角中离 Rahul 最远的一个位置。

对于每一个被涂色的格子，总是被涂色前 Rahul 的最佳选择，因为他们的选择都是明智的，也就是说我们可以将被涂色的格子作为 Rahul 的位置。

因为每个格子都会被涂色，所以每个格子都会作为 Rahul 的座位。

这样，问题就简化为了：求出每个位置距离四个角落的距离的最大值，然后将他们放到一个数组中，从小到大排序输出即可。


### 附源码：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int res[N];
int n, m, cnt;
int main(){
    int T;
    cin>>T;
    while(T--){
        cnt=0;//多组不清空，提交两行泪 
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){//教室是二维的，要双重循环 
                res[cnt++]=max(max(abs(1-i)+abs(1-j),abs(n-i)+abs(1-j)),max(abs(1-i)+abs(m-j),abs(n-i)+abs(m-j)));//求每个位置距离四个角落的距离的最大值
            }
        }
        sort(res,res+cnt);//排序 
        for(int i=0;i<cnt;i++){
            cout<<res[i]<<' ';//输出 
        }
        cout<<endl;//多组数据换行 
    }
    return 0;
}
```

---

## 作者：Tiantian2021 (赞：1)

### 本题思路
本题中 $R$ 要选尽可能离中间近的格子， $T$ 要选尽可能远离中间的格子。为了用贪心算法，要对”中间度“进行量化。

定义“中间度”为离“中间格”的最短距离，其中中间格的计算为：

$1)$ $n$ 奇 $m$ 奇，中间格有 $1$ 个， $(\left\lfloor\dfrac{n}{2}\right\rfloor,$ $\left\lfloor\dfrac{m}{2}\right\rfloor)$

$2)$ $n$ 奇 $m$ 偶，中间格有 $2$ 个， $(\left\lfloor\dfrac{n}{2}\right\rfloor,$ $m/2)$ 、 $(\left\lfloor\dfrac{n}{2}\right\rfloor, m/2+1)$

$3)$ $n$ 偶 $m$ 奇， 中间格有 $2$ 个，$(n/2, \left\lfloor\dfrac{m}{2}\right\rfloor)$ 、 $(n/2+1, \left\lfloor\dfrac{m}{2}\right\rfloor)$

$4)$ $n$ 偶 $m$ 偶，中间格有 $4$ 个， $(n/2, m/2)$  、   $(n/2+1, m/2)$ 、 $(n/2, m/2+1)$ 、 $(n/2+1, m/2+1)$

然后遍历地图，计算所有格子的中间度，并对中间度排序：

$dis(r, c) =$ 格子 $(r,c)$ 到所有中间格的最短距离

此时， $T$ 要涂中间度最小的 $K$ 个格子， $R$ 要占据第 $K+1$ 个格子， $T$ 必占据四个角之一，且离 $R$ 最远。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

struct T {
	int r, c, cen;
}a[100010];
int ctx[10], cty[10], ctnum;
int cal_dis(int x1, int y1, int x2, int y2) {
	return abs(x1 - x2) + abs(y1 - y2);
}

bool cmp(const T x, const T y) {
	return x.cen < y.cen;
}

signed main() {
	int t;
	cin >> t;
	
	while(t--) {
    	int n, m;
		cin >> n >> m;
         //计算中间格
		if(n % 2)
			if(m % 2) ctx[1] = (n + 1) / 2, cty[1] = (m + 1) / 2, ctnum = 1;
			else ctx[1] = ctx[2] = (n + 1) / 2, cty[1] = m / 2, cty[2] = m / 2 + 1, ctnum = 2;
		else
			if(m % 2) ctx[1] = n / 2, ctx[2] = n / 2 + 1, cty[1] = cty[2] = (m + 1) / 2, ctnum = 2;
			else {
				ctx[1] = n / 2, cty[1] = m / 2;
				ctx[2] = n / 2, cty[2] = m / 2 + 1;
				ctx[3] = n / 2 + 1, cty[3] = m / 2;
				ctx[4] = n / 2 + 1, cty[4] = m / 2 + 1;
				ctnum = 4;
			}
         //遍历地图计算中间度
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= m; j++) {
				a[(i - 1) * m + j].r = i, a[(i - 1) * m + j].c = j;
				
				int mn = 1e18;
				for(int k = 1; k <= ctnum; k++)
					mn = min(mn, cal_dis(i, j, ctx[k], cty[k]));
				a[(i - 1) * m + j].cen = mn;
			}
		sort(a + 1, a + n * m + 1, cmp);
		for(int i = 0; i < n * m; i++) { //对于所有的k: [0, n*m-1]
            T r = a[i + 1]; //R取第k+1个
			if(n * m == 2 || n * m == 3) { 	//边界处理
				int mx = 0;
				for(int j = 1; j <= n * m; j++)
					mx = max(mx, cal_dis(r.r, r.c, a[j].r, a[j].c));
				cout << mx << " ";
				continue;
			}
			//计算四个角到R的最大距离
			int mx = 0;
			for(int j = n * m - 3; j <= n * m; j++)
				mx = max(mx, cal_dis(r.r, r.c, a[j].r, a[j].c));
			cout << mx << " ";
		}
		cout << endl;
        }
        return 0;
     }
```

###  题目链接
[Not Sitting](https://www.luogu.com.cn/problem/CF1627B)

---

## 作者：Jerrlee✅ (赞：1)

## 题意
Rahul 和 Tina 在玩一个游戏。游戏在一个 $n\times m$ 的网格图上进行，记第 $r$ 行第 $c$ 列上的格子为 $(r,c)$。定义 $(a,b)$ 与 $(c,d)$ 之间的距离为 $\left|a-c\right|+\left|b-d\right|$。 游戏开始后，Tina 会选择恰好 $k$ 个格子，并将其涂成粉红色。涂完以后，Rahul 会选择任意一个**没有被涂成粉红色的格子**并在那个格子上坐下。此后，Tina 也会选择任意一个格子（**包括被涂成粉红色和没有被涂成粉红色的格子**）并在那个格子上坐下。Rahul 希望他和 Tina 之间的距离尽可能近，而 Tina 希望她和 Rahul 之间的距离尽可能远。于是，Rahul 都想知道他和 Tina 之间的距离是多少。
## 思路
Rahul 尽可能靠近 Tina，所以他一定要选最中间位置，Tina 尽可能远离 Rahul，所以她一定要选最靠边的位置，然后题目就转化为求每个位置到四个角落距离的最大值。

代码有较长的缺省源，到 CF 里看吧：<https://codeforces.com/contest/1627/submission/142861649>

---

## 作者：Daidly (赞：1)

思考一阵子，你会发现，T 坐在四角的位置是最优的，因为 T 要远离 R。

而 R 想要离 T 较近，而又是先选位置，他只能选在中间且没有红色的位置。

因为如果 R 选在两边，T 可以选在另一边，这样距离就变远了，不符合 R 的目的。

而要计算的就是当 $k\in[0,nm-1]$ 时 R 的位置到四个角距离最大的一个。

我们可以考虑给每个点赋一个值代表这个点到四个角距离最大的值，将其排序，就得到了 R 染红色的最优顺序和 T 选位置的最优顺序，而这个顺序的值就是最终的答案。

复杂度：$O(tnm\log(nm))$，CF 的官方题解里给出的是这种，可以过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
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

inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int MAXN=1e5+5;
int t,n,m,num,a[MAXN];

int main(){
	t=read();
	while(t--){
		n=read(),m=read(),num=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				a[++num]=max(i-1,n-i)+max(j-1,m-j);
			}
		}
		sort(a+1,a+num+1);
		for(int i=1;i<=num;++i){
			print(a[i]),printf(" ");
		}
		puts("");
	}
	return 0;
}
```

但是，对于这个数据范围来说，复杂度是不是有点大。

所以考虑去掉 $\log(nm)$。

发现 R 和 T 的距离是随着 $k$ 的增大而增大的，而且由于对称等原因会有一段答案是相同的。

将排序换成用桶记录，用一个桶记录距离为 $i$ 的个数，输出时连续输出桶内个数个 $i$ 即可。

而输出范围，即桶内值的大小范围也是可以确定的：

取点 $(\lfloor\frac{n}{2}\rfloor,\lfloor\frac{m}{2}\rfloor)$，它是网格的中心之一，也是 $k=0$ 时 R 的最佳选择之一，离它最远的是右下角 $(n,m)$，计算距离即为最小值 $n-\lfloor\frac{n}{2}\rfloor+m-\lfloor\frac{m}{2}\rfloor$。

最大值为 $n-1+m-1$，从左上角到右下角。

按范围输出就可以了。

复杂度：$O(tnm)$，稳过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
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

inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int MAXN=1e5+5;
int t,n,m,p[MAXN];

int main(){
	t=read();
	while(t--){
		n=read(),m=read();
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				p[max(i-1,n-i)+max(j-1,m-j)]++;
			}
		}
		for(int i=n-(n+1)/2+m-(m+1)/2;i<=n-1+m-1;++i){
			while(p[i]--)print(i),printf(" ");
			p[i]++;
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：shenbairui (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1627B)
### 题目翻译
就是 R 和 T 选座位，R 想离 T 近，T 想离 R 远，这么个意思。
### 题目分析
由于是 R 先选，所以 R 会选什么位置，我们不用考虑，所以只需考虑 T 坐的位置，不用管 R 坐哪，T 一定选择左上，左下，右上，右下这四个上离得最远的位置。

综上所述，我们只要暴力一下 R 的所有位置，就行了。

他们位置距离是用[曼哈顿距离](https://blog.csdn.net/m0_74233824/article/details/131638760?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522172005643116777224471510%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=172005643116777224471510&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_click~default-2-131638760-null-null.142^v100^pc_search_result_base1&utm_term=%E6%9B%BC%E5%93%88%E9%A1%BF%E8%B7%9D%E7%A6%BB&spm=1018.2226.3001.4187)不懂的可以看下。

这里再给大家推荐一个数据结构 [multiset](https://blog.csdn.net/qq_50285142/article/details/136097982?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522172005667616800184146003%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=172005667616800184146003&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-136097982-null-null.142^v100^pc_search_result_base1&utm_term=multiset&spm=1018.2226.3001.4187) 还不懂的可以看看，里面讲的很清楚了。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int ac(int x1,int y1,int x2,int y2){//曼哈顿距离
	return abs(x1-x2)+abs(y1-y2); 
}
int main(){
	int t;
	cin>>t;
	while(t--){
		multiset<int>s;//他和set唯一不同就是一个去重一个不去重
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				s.insert(max(max(ac(i,j,1,1)/*左上*/,ac(i,j,1,m)/*右上*/),max(ac(i,j,n,1)/*左下*/,ac(i,j,n,m)/*右下*/)));
			}
		}
		for(auto i:s)cout<<i<<" ";//遍历输出
		cout<<endl;
	}
	return 0;
}
```
下期见！拜拜！

---

## 作者：2021hych (赞：0)

# 简要/形式化题意
在 $n \times m$ 的全 $0$ 矩阵 $\{A_{i,j}\}$ 中，记 $d(a,b,c,d)=\left\vert a-c \right\vert + \left\vert b-d \right\vert$。甲和乙博弈。

第一轮：甲在矩阵中选取 $k$ 个点对 $(i,j)$，让 $A_{i,j}=1$。

第二轮：乙在矩阵中选取 $1$ 个点对 $(a,b)$，满足 $A_{a,b}=0$。

第三轮：甲在矩阵中选取 $1$ 个点对 $(c,d)$。

甲以 $d(a,b,c,d)$ 最大为最优，乙以 $d(a,b,c,d)$ 最小为最优。甲乙均采用最优决策。

求对于所有整数 $k$，其中 $0 \le k \le n \times m-1$，博弈的结果 $d(a,b,c,d)$ 的值。
# 题解
最后一轮的决策显然比较好讨论，因为第二轮已经确定。那么对于第三轮，为使 $d(a,b,c,d)$ 尽可能大，即 $\left\vert a-c \right\vert + \left\vert b-d \right\vert$ 尽可能大，则 $c$ 取极值（$1$ 或 $n$），$d$ 取极值（$1$ 或 $m$）。因而得到第三轮只有四种可能的最优决策：$(1,1)$，$(1,m)$，$(n,1)$，$(n,m)$，从而 $d(a,b,c,d)=\max \{a+b-2,a-1+m-b,n-a+b-1,n-a+m-b\}$。

由特殊到一般，考虑 $k=0$ 时，这时由刚刚的结论可得对于一个确定 $(a,b)$，其博弈结果可以 $O(1)$ 确定，那么只要 $O(nm)$ 的暴力求出 $\min\limits_{1 \le a \le n,1 \le b \le m}\{\max \{a+b-2,a-1+m-b,n-a+b-1,n-a+m-b\}\}$，就得到了最优博弈结果，记这个最优决策为 $(a',b')$。

当 $k=1$ 时，第一轮为了让第二轮选不到 $(a',b')$，必然会让 $A_{a',b'}=1$，从而第二轮的最优决策博弈结果为 $\min\limits_{1 \le a \le n,1 \le b \le m,(a,b) \ne (a',b')}\{\max \{a+b-2,a-1+m-b,n-a+b-1,n-a+m-b\}\}$，可以发现其实就是次小值。

以此类推，记矩阵 $\{B_{i,j}\}$，其中 $B_{i,j}=\max \{i+j-2,i-1+m-j,n-i+j-1,n-i+m-j\}$，则最优博弈结果为 $\{B_{i,j}\}$ 中的第 $(k+1)$ 小。原问题转化为将 $\{B_{i,j}\}$ 内的数据从小到大排序输出即可，优先队列即可 $O(nm\log{nm})$ 解决，桶排序可做到 $O(nm)$。
# AC code
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10; 
int T,n,m;
int cnt;
priority_queue<int>q;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>m;
		cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) {
				int num=0;
				num=max(num,i+j-2);
				num=max(num,i-1+m-j);
				num=max(num,n-i+j-1);
				num=max(num,n-i+m-j);
				q.push(-num);
			}
		while(!q.empty()) {
			cout<<-q.top()<<" ";
			q.pop();
		}
		cout<<endl;
	}
	return 0;
}

```

---

## 作者：PosVII (赞：0)

**思路**

------------

我们先不管限制将 Rahul 选择的位置枚举一遍，找到此时 Tina 可以选择的最大距离。Tina 一定会贪心的将可以取得的最大距离从小到大一个个删除，就将那些距离存入优先队列模拟即可。

建议评黄/绿

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
#define max(a,b) (a>b?a:b)
template<typename G>inline void read(G&x){x=0;G f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+(ch^48),ch=getchar();x*=f;}
template<typename G>inline void write(G x){if(x<0) putchar('-'),x=-x;G y=10,len=1;while(y<=x){y*=10;++len;}while(len--){y/=10;putchar(x/y^48);x%=y;}}
const int MAXN=2e5+5;
int t,n,m;
priority_queue<int,vector<int>,greater<int> > q;
int main() {
	read(t);
	while(t--) {
		read(n),read(m);
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=m;++j) {
				q.push(max(j-1,m-j)+max(i-1,n-i));
			}
		}
		for(int i=1;i<=n;++i) {
			for(int j=1;j<=m;++j) {
				printf("%d ",q.top());
				q.pop();
			}
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：xkcdjerry (赞：0)

简单题 ~~但是由于 wtcl 导致 bfs 写错调了一个小时~~

（由于本蒟蒻记不住名字下面把男生和女生分别叫做 Bob 和 Alice）

考虑对于 Bob 和 Alice 的任意位置，Alice 如果不在一个角落一定可以通过相对 Bob 反（zhan）向（shu）移（ping）动（yi）来增加自己与 Bob 间的距离。

所以可以通过 bfs 预处理每个点到四个角中每个角的距离，取最大值即为 Alice 在 Bob 坐在此处的时候的最大可能距离（下简称 mxdis）。显然 Alice 应该优先涂掉 mxdis 最小的点。[CF 题解](http://codeforces.com/blog/entry/99067) 给出的时间复杂度是 $O(nm \log nm)$（目测是优先队列）。但是由于显然存在 $mxdis < n+m$，所以可以通过对于每个点的 mxdis 建立 $n+m$ 个桶来做到 $O(1)$ 查询与删除。

代码：

```c++
#include <cstdio>
#include <cstring>
#define N 100010
#define clear(f,n) memset(f,0,sizeof(int)*(n))
int n,m;
int f[N*2],q[N],g[4][N],vis[N];
int head,tail,t,x,y,nx,ny,pk;
void add(int x) {vis[q[head++]=x]=true; if(head==N) head=0;}
void stfw()
{
    int s[4]={0,m-1,n*m-m,n*m-1};
    clear(f,n+m);
    // 从四个角各 bfs 一次
    for(int j=0;j<4;j++)
    {
        head=tail=0;
        clear(vis,n*m); clear(g[j],n*m); add(s[j]);
        while(head!=tail)
        {
            t=q[tail++];
            x=t/m,y=t%m;
            if(tail==N) tail=0;
            int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0};
            for(int i=0;i<4;i++)
            {
                pk=(nx=x+dx[i])*m+(ny=y+dy[i]);
                if(nx>=0&&nx<n&&ny>=0&&ny<m&&!vis[pk])
                {
                    g[j][pk]=g[j][t]+1;
                    add(pk);
                }
            }
        }
    }
    //取最大值并填加到 f 中
    for(int i=0;i<n*m;i++)
    {
        t=g[0][i];
        t=g[1][i]>t?g[1][i]:t;
        t=g[2][i]>t?g[2][i]:t;
        f[g[3][i]>t?g[3][i]:t]++;
    }
}
void rtfm()
{
    scanf("%d%d",&n,&m);
    stfw();
    int p=0;
    for(int i=0;i<n*m;i++)
    {
        //取mxdis最小值让Bob坐，然后Alice涂掉
        while(!f[p]) p++;
        printf("%d ",p);
        --f[p];
    }
    putchar('\n');
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) rtfm();
}
```

时间复杂度分析：
* `bfs` 部分花费 $O(4nm)=O(nm)$ 的时间
* 输出答案时包括恰好 $nm$ 次 `f[p]--` 与至多 $n+m$ 次 `p++`，所以时间为 $O(n+m+nm)=O(nm)$

综上，程序的总复杂度为 $O(nm)$，优于 CF 官方题解的 $O(nm \log nm)$。~~顺便还不卡常到了最优解第七名~~

[AC 记录](https://www.luogu.com.cn/record/67914186)

（说句闲话，这个题第一次 AC 的时候代码长度为 1.53KB，又压了好一会才变成 1.24KB 的）

---

## 作者：Shunpower (赞：0)

## 思路

非常显然的结论：无论 Rahul 坐在哪里，Tina 为了使离他最远，都要坐在一个角落。而且这个角落一定是四个角落中距离 Rahul 最远的。

所以说我们可以考虑预处理出对于每一个位置距离最远的那一个角落，把这个最远的距离存在一个数组里面。

感性理解一下。一开始的时候，两人的距离一定会比较近（Rahul 会选择坐在中间，无论 Tina 坐在哪一个角落都会比较近）；而随着 Tina 的涂漆，中间的位置越来越少，Rahul 只能坐在更加靠近某一个角落的位置，所以两人的距离会逐渐变远。

因此，把这个距离数组从小到大排序再依次输出即可。

## 代码

```
void solve(){
	tot=0;//归零！！！
	cin>>n>>m;
	fr1(i,1,n){
		fr1(j,1,m){
			tot++;
			a[tot]=max(abs(i-1)+abs(j-1),max(abs(i-1)+abs(m-j),max(abs(n-i)+abs(j-1),abs(n-i)+abs(m-j))));//取最长距离
		}
	}
	sort(a+1,a+tot+1);//从小到大排序
	fr1(i,1,n*m){
		cout<<a[i]<<" ";//依次输出即可
	}
	pt;
}
int main(){
	cin>>T;
	while(T--){
		solve();
	}
	ET;
}
//Teens-in-Times
//HJL 2004.06.15
```

---

## 作者：ArrogHie (赞：0)

## 题解

手玩一下样例，可以发现无论 Rahul 坐在哪个格子，Tina 一定是坐在四个角落的位置之一。从这个规律可以得出，每个格子能达到与 Tina 的最近距离就是该格子到达四个角的最大距离。所以对于当前能坐的所有格子中，距离四个角的最大距离最小的格子就是 Rahul 将要选择的位置。

预处理出所有格子到达四个角的最大距离，Tina 要染色的话一定是从距离近的开始染，Rahul 一定是坐在所有能坐的格子中距离最小的。所以我们将所有格子的距离排序依次输出即可。

---

## 作者：Argon_Cube (赞：0)

* **【题目链接】**

[Link:CF1627B](https://www.luogu.com.cn/problem/CF1627B)

* **【解题思路】**

显然 Rahul 的最优方案，就是选择一个他可以坐且 Tina 离他的最大距离最小的位置。

而我们考虑 Tina 会怎么涂油漆。显然她会最先把 Rahul 的最优点涂掉，然后涂次优点，以此类推。最后 Tina 必定是坐四个角之一。

那么，我们把所有点按照一个权值 $a_{i,j}$ 排序，它的值为：当 Rahul 坐这个位置时，Tina 离他的最大距离。

* **【代码实现】**

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <array>

using namespace std;

array<pair<int,pair<int,int>>,100000> points;

int main(int argc,char *argv[],char *envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int testcnt;
	cin>>testcnt;
	while(testcnt--)
	{
		int line,row;
		cin>>line>>row;
		for(int i=0;i<line;i++)
			for(int j=0;j<row;j++)
				points[i*row+j]=make_pair(0,make_pair(i,j));
		for(int i=0;i<line*row;i++)
			points[i].first=max({points[i].second.first+points[i].second.second,(line-1-points[i].second.first)+points[i].second.second,points[i].second.first+(row-1-points[i].second.second),
						(line-1-points[i].second.first)+(row-1-points[i].second.second)});
		sort(points.begin(),points.begin()+line*row);
		for(int i=0;i<line*row;i++)
			cout<<max({points[i].second.first+points[i].second.second,(line-1-points[i].second.first)+points[i].second.second,points[i].second.first+(row-1-points[i].second.second),
						(line-1-points[i].second.first)+(row-1-points[i].second.second)})<<' ';
		cout<<'\n';
	}
 	return 0;
}


```

---

