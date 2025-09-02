# Weird Sum

## 题目描述

Egor has a table of size $ n \times m $ , with lines numbered from $ 1 $ to $ n $ and columns numbered from $ 1 $ to $ m $ . Each cell has a color that can be presented as an integer from $ 1 $ to $ 10^5 $ .

Let us denote the cell that lies in the intersection of the $ r $ -th row and the $ c $ -th column as $ (r, c) $ . We define the manhattan distance between two cells $ (r_1, c_1) $ and $ (r_2, c_2) $ as the length of a shortest path between them where each consecutive cells in the path must have a common side. The path can go through cells of any color. For example, in the table $ 3 \times 4 $ the manhattan distance between $ (1, 2) $ and $ (3, 3) $ is $ 3 $ , one of the shortest paths is the following: $ (1, 2) \to (2, 2) \to (2, 3) \to (3, 3) $ .

Egor decided to calculate the sum of manhattan distances between each pair of cells of the same color. Help him to calculate this sum.

## 说明/提示

In the first sample there are three pairs of cells of same color: in cells $ (1, 1) $ and $ (2, 3) $ , in cells $ (1, 2) $ and $ (2, 2) $ , in cells $ (1, 3) $ and $ (2, 1) $ . The manhattan distances between them are $ 3 $ , $ 1 $ and $ 3 $ , the sum is $ 7 $ .

## 样例 #1

### 输入

```
2 3
1 2 3
3 2 1```

### 输出

```
7```

## 样例 #2

### 输入

```
3 4
1 1 2 2
2 1 1 2
2 2 1 1```

### 输出

```
76```

## 样例 #3

### 输入

```
4 4
1 1 2 3
2 1 1 2
3 1 2 1
1 1 2 1```

### 输出

```
129```

# 题解

## 作者：西湖水妖 (赞：3)

### 题意简述

+ 给定一个大小为 $n\times{m}$ 的桌子，$n$ 行 $m$ 列。
+ 每个位置都有一个颜色点 $(i,j)$ 的颜色为 $c_{ij}$。
+ 你需要求出每种颜色所包含的点之间的曼哈顿距离之和。点 $(r_1,c_1),(r_2,c_2)$ 之间的曼哈顿距离是 $|r_1-r_2|+|c_1-c_2|$。
+ $1\le{n}\le{m},nm\le{10^5},1\le{c_{ij}}\le10^5$ 并且所有数据都是整数。

### 题目分析

首先发现颜色的范围并不是特别大，所以我们可以对每个颜色分别进行考虑。推荐先思考 [P6067[USACO05JAN]Moo Volume S](https://www.luogu.com.cn/problem/P6067) 再来通过此题，会有很大帮助。

很容易想到一种暴力的做法，枚举同种颜色的点 $i,j$，把答案增加 $\dfrac{|r_i-r_j|+|c_i-c_j|}{2}$。

接着考虑优化，我们发现对 $r,c$ 分开进行计算是不会影响结果的，所以对于每种颜色的 $r,c$ 我们都先进行从小到大排序。然后枚举 $i,j(j<i)$，把答案增加 $r_i-r_j$（$c$ 同理）。但是这样只是做了一些常数上的优化，仍然会超时。

然后，我们又发现，对于 $i$，它贡献的答案为 $r_i-r_1+r_i-r_2+\cdots+r_i-r_{i-1}=r_i(i-1)-(r_1+r_2+...+r_{i-1})$（$c$ 同理）。于是，自然而然地想到了用前缀和优化。然后就做出来了。


```cpp
array<vector<long long>, 100001> a, b; //防止爆空间，使用 vector。
//同时注意不开 long long 见祖宗。
for(int i = 1; i <= n; ++ i)
    for(int j = 1; j <= m; ++ j)
    {
        cin >> c;
        a[c].push_back(i); //这题下标建议从 0 开始，会有一些帮助。
        b[c].push_back(j);
    }
for(int i = 1; i < 100001; ++ i)
{
    sort(a[i].begin(), a[i].end());
    sort(b[i].begin(), b[i].end());
    partial_sum(a[i].begin(), a[i].end(), sum.begin()); //STL 的前缀和函数。
    for(int j = 1; j < a[i].size(); ++ j) //防止 RE，第一个点没有贡献。
    {
        ans += a[i][j] * j; //下标从 0 开始，所以不需要减 1。
        ans -= sum[j - 1];
    }
    partial_sum(b[i].begin(), b[i].end(), sum.begin());
    for(int j = 1; j < b[i].size(); ++ j)
    {
        ans += b[i][j] * j;
        ans -= sum[j - 1];
    }
}
```

---

## 作者：8atemak1r (赞：3)

## Description

给定一个 $n \times m$ 的正整数矩阵，求这个矩阵中所有相同数字的曼哈顿距离之和的和。$1 ≤ n,m,n \cdot m ≤ 10^5$。

## Solution

令序列 $x_{i,j}$、$y_{i,j}$ 分别表示编号为 $i$ 的数字第 $j$ 次出现的行数与列数，显然因为输入从上至下，行数是非单调递减的，所以同一个数字 $a$ 的行数的曼哈顿距离之和可以表示为 
$$
\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}x_{a,j}-x_{a,i}
$$
相应地，我们可以使用 `sort` 将列数序列排序为非单调递减的，所以在最终同一个数字的曼哈顿距离之和可以这样表示：
$$
\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}\left(x_{a,j}-x_{a,i}\right) + \sum_{i=1}^{n-1}\sum_{j=i+1}^{n}\left(y_{a,j}-y_{a,i}\right)
$$
所以，当序列 $x_{i,j}$、$y_{i,j}$ 均非单调递减，令 $cnt$ 表示总共出现的数字个数，最终的答案即为：
$$
ans=\sum^{cnt}_{a=1}\left[\sum_{i=1}^{n-1}\sum_{j=i+1}^{n}\left(x_{a,j}-x_{a,i}\right) + \sum_{i=1}^{n-1}\sum_{j=i+1}^{n}\left(y_{a,j}-y_{a,i}\right)\right]
$$

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
#define int long long //记得开 long long
#define maxn 100005
using namespace std;
int n, m, cnt[maxn];
int ans;
struct node {
    int x, y;
    bool operator < (const node & a) const {
        return a.y < y;
    }
};
vector<node> v[maxn];
signed main() {
    cin >> n >> m;
    for(int i = 1, a; i <= n; ++ i) {
        for(int j = 1; j <= m; ++ j) {
            cin >> a; ++ cnt[a];
            v[a].push_back((node){i, j});
        }
    }
    for(int i = 1; i < maxn; ++ i) {
        if(v[i].empty()) continue;
        for(int j = cnt[i] - 1; j >= 0; -- j) {
            ans -= (cnt[i] - j - 1) * v[i][j].x;
            ans += j * v[i][j].x;
        }
        sort(v[i].begin(), v[i].end());
        for(int j = 0; j < cnt[i]; ++ j) {
            ans += (cnt[i] - j - 1) * v[i][j].y;
            ans -= j * v[i][j].y;
        }
    }
    cout << ans;
    return 0;
}
```





---

## 作者：沉石鱼惊旋 (赞：1)

### 题目翻译

一个 $n\times m$ 的网格，每个格子里有 $1$ 个数，问对于所有相同的数，曼哈顿距离总和是多少？

曼哈顿距离：$a_{i_1,j_1}$ 与 $a_{i_2,j_2}$ 距离为 $\left|i_1-i_2\right|+\left|j_1-j_2\right|$。

### 题目思路

暴力搜一遍，肯定挂掉，$n\times m$ 有 $100000$。

所以，我们对每种数进行分类，每一类再分成 $x$ 轴的总距离求和加上 $y$ 轴的总距离求和。

这是蒟蒻我能想到的最优解了。

### 分析思路

那么总距离求和该怎么做呢，例如上文的 $x$ 轴的总距离求和。

我们考虑把它们排序，放在一根数轴上。

![](https://cdn.luogu.com.cn/upload/image_hosting/4x536hgp.png)

我们以端点为 $i_2$ 和 $i_3$ 的线段做例子：

本身长度 $2$。

往右边走，有 $i_3,i_4,i_5$，产生 $3$ 次贡献。

左边每个点都可以与上面 $3$ 个点产生连接，左边有 $2$ 个点，$i_1$ 和 $i_2$。

注意，线段的两个端点也算进去。

那么这个线段产生**左边端点个数 $\times$ 线段长度 $\times$ 右边端点个数**这么多贡献。

同理，每个线段也产生上述贡献。

### AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node
{
	int x,y;//记录x轴和y轴
};
vector<node>a[100020];//对数字分类
ll s(vector<int>a)//求和
{
	ll sum=0;
	for(int i=1;i<a.size();i++)
	{
		sum+=i*(a[i]-a[i-1])*(a.size()-i);
	}
	return sum;
}
void solve()
{
	int n,m,maxx=INT_MIN;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int z;
			cin>>z;
			node zz;
			zz.x=i;
			zz.y=j;
			a[z].push_back(zz);//插入这个点信息
			maxx=max(z,maxx);//找出最大值
		}
	}
	ll sum=0;
	for(int i=1;i<=maxx;i++)
	{
		vector<int>xx;//记录x轴
		vector<int>yy;//记录y轴
		for(auto j:a[i])//插入点的信息
		{
			xx.push_back(j.x);
			yy.push_back(j.y);
		}
        //排序
		sort(xx.begin(),xx.end());
		sort(yy.begin(),yy.end());
		ll sx=s(xx);
		ll sy=s(yy);
		sum+=sx+sy;//求和
	}
	cout<<sum<<endl;
}
int main()
{
	int t=1;
	while(t--)
	{
		solve();
	}
    return 0;
}
```

---

## 作者：rlc202204 (赞：1)

# CF1648题解

**题目传送门：[CF1648A Weird Sum](https://www.luogu.com.cn/problem/CF1648A)**

这道题要想暴力很简单，枚举每一个点对即可，不过复杂度过不去。

我用的是权值树状数组，以前碰到过类似的。

因为曼哈顿距离是 $x$ 轴和 $y$ 轴的绝对值，所以与USACO一道题很像，建议可以先做这道。

**[类似题目](https://www.luogu.com.cn/problem/P5094)**

存下每个数值的出现次数与总和，这样可以更快的算出距离。


细节见代码。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;
#define ll long long
int n, m;
ll c[100005][2] = {{0}};
ll d[100005][2] = {{0}};
struct Node{
	int x, y;
};
int lowbit(int x){
	return x & -x;
}
void modify1(int i, int x, int t){
	while(i <= 100000){
		c[i][t] += x;
		i += lowbit(i);
	}
}
ll query1(int i, int t){
	ll ans = 0;
	while(i > 0){
		ans += c[i][t];
		i -= lowbit(i);
	}
	return ans;
}
void modify2(int i, int x, int t){
	while(i <= 100000){
		d[i][t] += x;
		i += lowbit(i);
	}
}
ll query2(int i, int t){
	ll ans = 0;
	while(i > 0){
		ans += d[i][t];
		i -= lowbit(i);
	}
	return ans;
}
Node abc(int a, int b){
	Node tmp;
	tmp.x = a, tmp.y = b;
	return tmp;
}
vector<Node> v[100005];
bool f[100005] = {0};
int main(){
	scanf("%d%d", &n, &m);
	int maxn = 0, minn = 2e9;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++){
			int x;
			scanf("%d", &x);
			maxn = max(x, maxn);
			minn = min(x, minn);
		//	f[x] = true;
			v[x].push_back(abc(i, j));
		}
	ll sum = 0;
	for(int i = minn; i <= maxn; i++){
		if(v[i].size() <= 1)continue;
		ll sx = 0, sy = 0;
		int fr = 0; 
		for(int j = 0; j < v[i].size(); j++){
			Node a = v[i][j];
			int x = a.x, y = a.y;
			//比他小 
			ll cnt1x = query1(x, 1), sum1x = query2(x, 1);
			
			ll cnt1y = query1(y, 2), sum1y = query2(y, 2);
			//比他大
			ll cnt2x = fr - cnt1x, sum2x = sx - sum1x;
			
			ll cnt2y = fr - cnt1y, sum2y = sy - sum1y;
			//计算 
			sum += (x * cnt1x - sum1x + sum2x - x * cnt2x);
			
			sum += (y * cnt1y - sum1y + sum2y - y * cnt2y);
			//修改
			modify1(x, 1, 1), modify1(y, 1, 2);
			modify2(x, x, 1), modify2(y, y, 2); 
			
			sx += x, sy += y;
			fr++;
		}
		for(int j = 0; j < v[i].size(); j++){
			Node a = v[i][j];
			int x = a.x, y = a.y;
			modify1(x, -1, 1), modify1(y, -1, 2);
			modify2(x, -x, 1), modify2(y, -y, 2); 
		}
	}
	cout << sum;
	return 0;
}
```




---

## 作者：Alarm5854 (赞：1)

## 题意
给定一个矩阵的每个方格的颜色，求出每个颜色两两间的距离之和。

## 解法
对于每一个颜色，可以单独考虑，则两两间距离之和为：
$$
\sum_{i=1}^k\sum_{j=i}^k(|x_i-x_j|+|y_i-y_j|)
$$
显然，$x,y$ 可以单独考虑。那么，就是求
$$
\sum_{i=1}^k\sum_{j=i}^k|a_i-a_j|
$$
考虑这个式子中每个 $a_i$ 的贡献。$a_i$ 越大，那么起到加的贡献就越大，起到减的贡献越小。那么，可以对 $a_i$ 从小到大排序，然后求下列式子：
$$
\sum_{i=1}^ki\times a_i-(k-i+1)\times a_i
$$
这就完成了。
```cpp
#include<ctime>
#include<cctype>
#include<cstdio>
#include<vector>
#include<algorithm>
#define ll long long
using namespace std;
const int N=1e5+7;
ll read(){
	char c;
	ll x=0,f=1;
	while(!isdigit(c=getchar()))
		f-=2*(c=='-');
	while(isdigit(c)){
		x=x*10+f*(c^48);
		c=getchar();
	}
	return x;
}
int n,m,c,mx;
vector<int>a[N],b[N];
ll sum;
int main(){
	n=read();
	m=read();
	for(int i=1;i<=n;++i)
	for(int j=1;j<=m;++j){
		c=read();
		if(mx<c)
			mx=c;//求出最大的颜色编号
		a[c].push_back(i);
		b[c].push_back(j);
	}
	for(int i=1;i<=mx;++i){
		sort(a[i].begin(),a[i].end());//对x,y分别排序即可
		sort(b[i].begin(),b[i].end());
		ll cnt;
		cnt=0;
		for(auto x:a[i]){
			++cnt;
			sum+=x*cnt;
		}
		cnt=0;
		for(auto y:b[i]){
			++cnt;
			sum+=y*cnt;
		}
		reverse(a[i].begin(),a[i].end());//我这里用的是翻转
		reverse(b[i].begin(),b[i].end());
		cnt=0;
		for(auto x:a[i]){
			++cnt;
			sum-=x*cnt;
		}
		cnt=0;
		for(auto y:b[i]){
			++cnt;
			sum-=y*cnt;
		}
	}
	printf("%lld\n",sum);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

## 思路

考虑我们将行距离和列距离分开考虑，首先我们先考虑行（以行为例），将每种颜色分隔出来分别放置于若干向量中，对他们进行排序，然后使用前缀和，记录这种颜色到现在为止所有点的横坐标之和 $tot$ 与前面点的数量 $cnt$，每次看到一个点，他的贡献值为 $x\times cnt-tot$，将这个值加入 $ans$，列同理，最后输出即可。复杂度 $O(nm\log nm)$，即可通过此题。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> r[100005],c[100005];
signed main(){
	int n,m;
	cin>>n>>m;
	int ans=0,a[n+1][m+1];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
			r[a[i][j]].push_back(i);
			c[a[i][j]].push_back(j);
		}
	}
	for(int i=1;i<=100000;i++){
		sort(r[i].begin(),r[i].end());
		int tot=0,cnt=0;
		for(auto j:r[i]){
			ans+=(j*cnt-tot);
			tot+=j;
			cnt++;
		}
	}
	for(int i=1;i<=100000;i++){
		sort(c[i].begin(),c[i].end());
		int tot=0,cnt=0;
		for(auto j:c[i]){
			ans+=(j*cnt-tot);
			tot+=j;
			cnt++;
		}
	}
	cout<<ans;
}
```

---

## 作者：xinruian (赞：0)

## 

### 题意简述：

给定一个 $n \times m$ 的矩阵，每个位置都包含一个元素。求所有相同元素对的曼哈顿距离之和。

### 题目分析：

- 设该矩阵为 $a$，若 $a[i_1][j_1] = a[i_2][j_2]$，则两点之间的的曼哈顿距离为：

$$
\left|i_1 - i_2 \right| +  \left|j_1 - j_2 \right|
$$

- 显然，横纵坐标是相互独立的。使用我们可以对相同元素对的横纵坐标分别计算。
- 对于同一个元素，他们横坐标组成的数组为 $lx$，对于 $lx[i]$ 来说，他左边有 $i-1$ 个点数，他与左边所有点的横坐标距离之和为：

$$
(i-1)\cdot lx[i] - (lx[1]+lx[2]+...+lx[i-1])
$$



- 因此，我们可以对横纵坐标排序，通过维护前缀和来求解。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    map<int, vector<int>> lx, ly;
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++) {
            int c;
            cin >> c;
            lx[c].push_back(i);
            ly[c].push_back(j);
        }

    auto solve = [&](map<int, vector<int>> mp) -> long long{
        long long ans = 0;
        for (auto it: mp) {
        	auto v = it.second;
            sort(v.begin(), v.end());
            long long sum = 0, cnt = 0;
            for (int j: v) {
                ans += j * cnt - sum;
                sum += j;
                ++ cnt;
            }
        }
        return ans;
    };
	
    cout <<  solve(lx) + solve(ly) << endl;

    return 0;
}
```



---

## 作者：_QWQ__QWQ_ (赞：0)

## 题意：

给定 $ n\times m $ 的矩阵，求相同的数的曼哈顿距离和。

## 思路：

曼哈顿距离：$ dis_{i\to j}=|x_j - x_i| + |y_j - y_i| $ 可以发现 $ x $ 和 $ y $ 可以分开计算，我们先把多个 $ x $ 和 $ y $ 升序排列，对于第 $ i $ 个 $ x $ 或 $ y $，它需要被加 $ i-1 $ 次被减 $ n-i $ 次 故就很好写代码了。

## AC代码：
```cpp
#include<bits/stdc++.h> 
#define ll long long
using namespace std;
ll n,m,k;
vector<ll>vx[100100];
vector<ll>vy[100100];
int main(){ 
    cin>>n>>m;
    ll ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ll x; 
            cin>>x;
            vx[x].push_back(i);//把值为一样的点归为一个容器中 
            vy[x].push_back(j);        
        }
    }
    for(int i=1;i<=100001;i++){//每一类横纵坐标都升序排列 
        sort(vx[i].begin(),vx[i].end());
        sort(vy[i].begin(),vy[i].end());
    }
    for(int i=1;i<=100001;i++){
        for(int j=0;j<vx[i].size();j++){
            ans+=j*vx[i][j];//对于第j（含0）个元素他要被加j次 
            ans-=(vx[i].size()-j-1)*vx[i][j];//对于第j（含0）个元素他 要被减n-j-1次
            ans+=j*vy[i][j];
            ans-=(vy[i].size()-j-1)*vy[i][j];
        }
    }
        
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Doubeecat (赞：0)

# A. Weird Sum

> 给出两个整数 $n,m$，和一个 $n \times m$ 的矩阵。若该矩阵中两元素相同，$sum$ 就加上它们所在位置的曼哈顿距离。求 $sum$ 的值。
> 
>  $1 \leq n \le m, n \cdot m \leq 100000$ 

## 思路

首先给出曼哈顿距离的定义式：

$$
dis_{i,j} = |x_i - x_j| + |y_i - y_j|
$$

是两个绝对值的加和，而题目中所让我们求的同种颜色的两两之间曼哈顿距离，可以表示为如下式：

$$
\sum\limits_{col_{x_i,y_i} = k} \sum\limits_{col_{x_j,y_j} = k,i\not ={j}} |x_i - x_j| + |y_i - y_j| 
$$

显然，我们可以把 $x,y$ 拆开来计算，以下先考虑 $x$ 的部分如何计算，$y$ 的部分同理。

首先，我们可以把 $x_i$ 进行排序，记当前颜色有 $p$ 个点，那么 $x$ 部分的贡献可以如下表示

$$
\begin{aligned}
    &\sum\limits_{i =1}^p \sum\limits_{j = 1}^{i-1} |x_j - x_i| \\
    = &\sum\limits_{i =1}^p \sum\limits_{j = 1}^{i-1} x_i - x_j\\
    = &\sum\limits_{i =1}^p (i-1)\times x_i - \sum\limits_{j = 1}^{i-1} x_j
\end{aligned}
$$

显然，这个式子里的 $(i-1)\times x_i$ 我们可以在 $\mathcal{O}(1)$ 的时间复杂度内算出，而 $\sum\limits_{j = 1}^{i-1} x_j$ 可以在一个维护前缀和的过程中算出，时间复杂度为 $\mathcal{O}(p)$.

对每种颜色做一遍上面的计算，总时间复杂度为 $\mathcal{O}(\sum p ) = \mathcal{O}(n\times m)$，可以通过本题。$y$ 的计算同理，此处不再赘述。

## 代码

```cpp
const int N = 1e5 + 10;

int n,m;
vector <int> c1[N],c2[N];

void solve() {
    for (int i = 1;i <= 100000;++i) c1[i].clear(),c2[i].clear();
    read(n,m);
    for (int i = 0;i < n;++i) {
        for (int j = 0;j < m;++j) {
            int col;read(col);
            c1[col].push_back(i);
            c2[col].push_back(j);
        }
    }
    int ans = 0;
    for (int i = 1;i <= 100000;++i) {
        if (c1[i].empty()) continue;
        sort(c1[i].begin(),c1[i].end());
        int pre = 0;
        for (int j = 0;j < c1[i].size();++j) {
            ans += j * c1[i][j] - pre;
            pre += c1[i][j];
        }
    }
    for (int i = 1;i <= 100000;++i) {
        if (c2[i].empty()) continue;
        sort(c2[i].begin(),c2[i].end());
        int pre = 0;
        for (int j = 0;j < c2[i].size();++j) {
            ans += j * c2[i][j] - pre;
            pre += c2[i][j];
        }
    }

    printf("%lld\n",ans);
}

signed main() {
    solve();
	return 0;
}
```

---

## 作者：npqenqpve (赞：0)

### 思路

首先考虑按颜色分开处理，对于同一个颜色，发现 $|x_i-x_j|+|y_i-y_j|$ 的 $x$ 部分和 $y$ 部分是相互独立的，可以分开处理，转化为如何求解一个序列中两两数字之差的绝对值之和，由于绝对值不容易直接处理，所以直接从大到小排序这个序列，差就不会产生负数，考虑到 $x_i$ 作为被减数会贡献 $n-i$ 次，并减去一个后缀和，预处理即可，将每一个颜色的答案相加就是总和。此题出题人给的是 $n\times m $ 的数据范围，所以需要动态开空间。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
vector<int>mp[100005];
vector<int>x[100005],y[100005];
int t[100005],top=0,q[100005],g[100005],f[100005];
int tot=0;
int cmp(int a,int b)
{
	return a>b;
}
signed main()
{
	int n,m;cin>>n>>m;
	for(int i=0;i<n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int k;cin>>k;
			t[++top]=k;
			q[top]=k;
		}
	}
	sort(q+1,q+top+1);
	int k=unique(q+1,q+top+1)-q-1;
	for(int i=1;i<=top;i++)
	{
		t[i]=lower_bound(q+1,q+k+1,t[i])-q;
	}
	int now=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
		{
			mp[i].push_back(t[++now]);
			tot=max(tot,t[now]);
			x[mp[i][j]].push_back(i);
			y[mp[i][j]].push_back(j);
		}
	}
	int ans=0;
	for(int i=1;i<=tot;i++)
	{
		sort(x[i].begin(),x[i].end(),cmp);
		sort(y[i].begin(),y[i].end(),cmp);
		// for(int j=0;j<x[i].size();j++)
		// {
		// 	cout<<x[i][j]<<" ";
		// }
		// puts("");
		// for(int j=0;j<y[i].size();j++)
		// {
		// 	cout<<y[i][j]<<" ";
		// }
		// puts("");
		g[0]=x[i][0],f[0]=y[i][0];
		for(int j=1;j<x[i].size();j++)
		{
			g[j]=g[j-1]+x[i][j];
		}
		for(int j=1;j<y[i].size();j++)
		{
			f[j]=f[j-1]+y[i][j];
		}
		for(int j=0;j<x[i].size();j++)
		{
			ans+=(x[i].size()-j-1)*x[i][j]-(g[x[i].size()-1]-g[j]);
		}
		for(int j=0;j<y[i].size();j++)
		{
			ans+=(y[i].size()-j-1)*y[i][j]-(f[y[i].size()-1]-f[j]);
		}
	}
	cout<<ans<<"\n";
	system("pause > null");
}//
```

---

