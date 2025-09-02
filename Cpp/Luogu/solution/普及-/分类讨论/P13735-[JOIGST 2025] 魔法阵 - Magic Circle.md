# [JOIGST 2025] 魔法阵 / Magic Circle

## 题目描述

比太郎所在的魔法学校即将举办运动会。运动会中有一个项目，称为“魔法阵”。

有 $N$ 个魔法阵依次排列在一个圆上，顺时针编号为 $1$ 到 $N$。每个魔法阵为红色或蓝色中的一种，使用长度为 $N$ 且仅包含小写字母 `b` 和 `r` 字符串 $S$ 表示：$S_j(1\le j\le N)$ 为 `r` 则表示魔法阵 $j$ 为红色，否则为蓝色。

比太郎可以通过如下的两种方式在魔法阵中传送：

- 选择一个相邻的魔法阵，花费 $1$ 秒传送过去。换句话说，可以在魔法阵 $j(1\le j\le N-1)$ 和 $j+1$ 间传送（两个方向均可），也可以在魔法阵 $1$ 和 $N$ 间传送（两个方向均可）；
- 选择一个与当前所在魔法阵颜色相同的魔法阵（不一定要相邻），花费 $1$ 秒传送过去。

目前他仅得知每个魔法阵的颜色，但并不知道运动会当天具体的传送计划。于是他决定考虑 $Q$ 个传送计划：在第 $i$ 个计划中，他要从魔法阵 $X_i$ 开始，花费最少的时间传送到魔法阵 $Y_i$。

请你对于每一个传送计划，求出最少需要花费的时间。

## 说明/提示

#### 【样例解释 #1】

在此样例中，魔法阵的颜色分别为红色、蓝色、红色、蓝色、蓝色。

对于第一组计划（$5\to 3$），比太郎可以使用如下传送方案：

1. 从魔法阵 $5$ 传送到相邻的魔法阵 $1$，花费 $1$ 秒；
2. 从魔法阵 $1$ 传送到颜色相同的魔法阵 $3$，花费 $1$ 秒。

最少需要花费的时间为 $2$ 秒。可以证明不可能在小于 $2$ 秒的时间内从魔法阵 $5$ 传送到魔法阵 $3$。

对于第二组计划（$4\to 5$），比太郎可以使用如下传送方案：

1. 从魔法阵 $4$ 传送到颜色相同的魔法阵 $5$，花费 $1$ 秒。

最少需要花费的时间为 $1$ 秒。

该样例满足子任务 $5,6$ 的限制。

#### 【样例解释 #2】

该样例满足子任务 $2,5,6$ 的限制。

#### 【样例解释 #3】

该样例满足子任务 $3,5,6$ 的限制。

#### 【样例解释 #4】

该样例满足子任务 $4,5,6$ 的限制。

#### 【数据范围】

- $3\le N\le 5\times 10^5$；
- $1\le Q\le 5\times 10^5$；
- $S$ 为仅包含小写字母 `b` 和 `r` 的长度为 $N$ 的字符串；
- $1\le X_i,Y_i\le N(1\le i\le Q)$；
- $X_i\ne Y_i(1\le i\le Q)$。

#### 【子任务】

1. （$6$ 分）$N=3$，$Q\le 100$；
2. （$13$ 分）$S_1$ 为 `b`，$S$ 的其他字符均为 `r`；
3. （$18$ 分）$N$ 为偶数，$S$ 奇数位置的字符为 `b`，偶数位置的字符为 `r`；
4. （$23$ 分）$N$ 为偶数，$S$ 的前 $\frac{N}{2}$ 个字符为 `b`，后 $\frac{N}{2}$ 个字符为 `r`；
5. （$21$ 分）$N,Q\le 100$；
6. （$19$ 分）无附加限制。

## 样例 #1

### 输入

```
5 2
rbrbb
5 3
4 5```

### 输出

```
2
1```

## 样例 #2

### 输入

```
4 3
brrr
2 4
1 3
3 1```

### 输出

```
1
2
2```

## 样例 #3

### 输入

```
6 3
brbrbr
1 2
2 5
2 4```

### 输出

```
1
2
1```

## 样例 #4

### 输入

```
6 5
bbbrrr
2 3
2 4
2 5
2 6
2 1```

### 输出

```
1
2
3
2
1```

# 题解

## 作者：Mindulle (赞：3)

$n$ 很大，很明显需要复杂度低的方法。而且题目有多组询问，易知此题很大可能有规律的存在，单个问题的时间复杂度需要达到 $O(1)$。

我们考虑使用分类讨论的方法解决。不妨记第 $i$ 个字符的颜色为 $c_i$。两个编号为 $x$ 和 $y$。

- 若 $c_x=c_y$，则只需要一步即可。
- 若 $c_{x-1}=c_y,c_{x+1}=c_y,c_x=c_{y+1},c_x=c_{y-1}$，易见，可以两步完成。
- 否则，我们可以转移到一个与 $x$ 同色的格子 $i$，再移动一步，移动一步到达的这个格子与 $y$ 同色，可以三步完成，容易证明这种格子 $i$ 总是存在的，否则 $i$ 就是 $y$ 或更加后面的格子。

我们可以写出如下的代码：
```cpp
s+=s[0];
···
  x--;y--;
  int dis=min(abs(x-y),n-abs(x-y));
  if(s[x]==s[y])cout<<"1\n";
  else if(s[(x-1+n)%n]==s[y]||s[(x+1)%n]==s[y]||s[(y-1+n)%n]==s[x]||s[(y+1)%n]==s[x]) cout<<"2\n";
  else cout<<"3\n";
  ···
  return 0;
}
```
交上去，发现 WA 了，因为我们没有考虑直接走的情况，这么走说不定比传送还快。
```cpp
s+=s[0];
while(q--){
  cin>>x>>y;
  x--;y--;
  int dis=min(abs(x-y),n-abs(x-y));
  if(s[x]==s[y])cout<<"1\n";
  else if(s[(x-1+n)%n]==s[y]||s[(x+1)%n]==s[y]||s[(y-1+n)%n]==s[x]||s[(y+1)%n]==s[x])cout<<min(dis,2)<<"\n";
  else cout<<min(dis,3)<<"\n";
}
```

注意输入中的 $x$ 和 $y$ 的下标和字符串的下标是不同的。

---

## 作者：zunber_small (赞：2)

其实这道题只要静下心来好好想想，其实真的不难。

题目相信大家都看了，这里就不过多赘述了。

### 思路

首先我们需要先分类讨论一下，

- 如果 $ S_x $ 等于 $ S_y $ ，说明是同一种魔法阵，直接花费 $ 1 $ 分钟传送就好，答案为1。
- 如果 $ x $ 和 $ y $ 之间的距离是  $ 1 $ 的话，也就是说直接就可以移动一下就可以到达，答案为 $ 1 $。
- 如果 $ S_y $ 的旁边（也就是 $ S_{y+1} $ 和 $ S_{y-1} $）和 $ S_x $ 相等，那么我们可以直接传送到 $ S_y $ 的旁边，然后再走到 $ S_y $。一共用了 $ 2 $ 分钟，答案为 $ 2 $。
- 如果 $ S_x $ 的旁边（也就是 $ S_{x+1} $ 和 $ S_{x-1} $）和 $ S_y $ 相等，那么我们可以先走到$ S_{x+1} $ 或 $ S_{x-1} $，再因为这个位置与 $ S_y $ 相等，所以我们可以直接传送。花费 $ 2 $ 分钟，答案为 $ 2 $。
- 如果 $ S_y $ 的旁边（也就是 $ S_{y+1} $ 和 $ S_{y-1} $）和 $ S_x $ 不相等，那说明 $ S_y $ 在一串与 $ S_x $ 不相同的魔法阵中间。那我们就可以先传送到这个串的旁边，然后再迈出一步进入这个串。因为这个串中的魔法阵都一样，我们就可以直接传送到 $ S_y $ 了。一共花费 $ 3 $ 分钟，答案为 $ 3 $。
![](https://i.postimg.cc/15RbZz5w/1.png)
- 如果 $ S_x $ 的旁边（也就是 $ S_{x+1} $ 和 $ S_{x-1} $）和 $ S_y $ 不相等，那说明 $ S_x $ 在一串与 $ S_y $ 不相同的魔法阵中间。那我们就可以先传送到这个串的旁边，然后再迈出一步进入这个串。因为这个串中的魔法阵都一样，我们就可以直接传送到 $ S_x $ 了。一共花费 $ 3 $ 分钟，答案为 $ 3 $。

### 代码

知道了思路，代码实现起来就很简单了。

```cpp
#include<bits/stdc++.h>
// #define int long long
using namespace std;

int n,q;//n q是输入的长度和询问次数
char a[1000000];//存储魔法阵的数组

signed main()
{   
    cin>>n>>q;//输入
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    a[n+1] = a[1];//由于魔法阵是环形的，所以我们需要让第一位和最后一位是相邻的。
    a[0] = a[n];
    for(int i=1;i<=q;i++)
    {
        int x,y;//输入
        cin>>x>>y;
        if(a[x] == a[y])//情况1
        {
            cout<<1<<endl;
        }
        else if((x == 1 && y == n) || (x == n && y == 1) || (abs(x - y) == 1))//情况2
        {
            cout<<1<<endl;
        }
        else if(a[y+1] == a[x] || a[y-1] == a[x])//情况3 
        {
            cout<<2<<endl;
        }
        else if(a[x+1] == a[y] || a[x-1] == a[y])//情况4
        {
            cout<<2<<endl;
        }
        else//由于剩余的情况都是输出3，所以我们直接输出3就行
        {
            cout<<3<<endl;
        }
    }
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/231538535)

---

## 作者：OvO_frsf (赞：2)

# P13735 [JOIGST 2025] 魔法阵 / Magic Circle 题解
## 题意简述

给出一个含有 $N$ 个点的圆，每个点为**红色**或**蓝色**，使用**相邻传送**和**同色传送**，每次传送消耗 $1$ 秒，求出从点 $x$ 至点 $y$ 的最少传送时间。

---
## 解题过程
先看数据范围，$N$ 和 $Q$ 都很大，每次回答考虑 $O(1)$ 时间复杂度的解法。

分类讨论。

1. 点 $x$ 与点 $y$ 同色，同色传送，消耗 $1$ 秒。
![](https://cdn.luogu.com.cn/upload/image_hosting/ukmjvfai.png)
2. 点 $x$ 与点 $y$ 异色，只使用相邻传送。
![](https://cdn.luogu.com.cn/upload/image_hosting/dfjqinhk.png)
3. 点 $x$ 与点 $y$ 异色，且点 $x$ 相邻有异色点，先相邻传送再同色传送，消耗 $2$ 秒。
![](https://cdn.luogu.com.cn/upload/image_hosting/dpt28g0p.png)
4. 和第 $3$ 条类似，点 $x$ 与点 $y$ 异色，且点 $y$ 相邻有异色点，先同色传送再相邻传送，消耗 $2$ 秒。
![](https://cdn.luogu.com.cn/upload/image_hosting/vml17y5x.png)
5. 点 $x$ 与点 $y$ 异色，两点都没有相邻的异色点，先同色传送到含有相邻异色点的同色点，然后相邻传送到异色点，最后同色传送到点 $y$ ，消耗 $3$ 秒。
![](https://cdn.luogu.com.cn/upload/image_hosting/sux9xryg.png)

需要注意的是，当点 $x$ 与点 $y$ 异色时，有可能出现**只使用相邻传送**的时间比**结合相邻传送和同色传送**的时间短的情况，输出时需要取最小值。
![](https://cdn.luogu.com.cn/upload/image_hosting/p6ygo71z.png)

---

## AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int n, q;
char mp[N];
int get_dis(int pos1, int pos2){	// 只使用相邻传送的时间 
	return min(abs(pos1 - pos2), n - abs(pos1 - pos2));
}
int main(){
	cin >> n >> q;
	cin >> mp + 1;
	//模拟首尾相连 
	mp[0] = mp[n];
	mp[n + 1] = mp[1];
	
	while (q--){
		int x, y, ans;
		cin >> x >> y;
		if (mp[x] == mp[y])									// 第一种情况 
			ans = 1;
		else if (mp[x - 1] != mp[x] || mp[x + 1] != mp[x])	// 第三种情况 
			ans = 2;
		else if (mp[y - 1] != mp[y] || mp[y + 1] != mp[y])	// 第四种情况 
			ans = 2;
		else												// 第五种情况 
			ans = 3;
		cout << min(ans, get_dis(x, y)) << endl;
	}
	return 0;
}
```

---

## 作者：zhouzihang3 (赞：2)

当我一眼看到这个题时，我想用最短路做，时间限制两秒，跑 $3 \times 10 ^ 5$ 次单源最短路是不够的。

:::info[TLE 代码]
```
#include<bits/stdc++.h>
using namespace std;
struct Node{
	int x,y;
};
bool operator>(const Node &a,const Node &b){
	return a.x>b.x;
}
vector<int> e[500005];
priority_queue<Node,vector<Node>,greater<Node> >q;
int dis[500005],vis[500005];
void dijkstra(int s){
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[s]=0;
	q.push({0,s});
	while(!q.empty()){
		int u=q.top().y;
		q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto it:e[u]){
			int v=it,w=1;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				q.push({dis[v],v});
			}
		}
	}
}
int n,Q,s,ed;
char c;
int b[500005],r[500005];
int cntb,cntr;
int main(){
	cin>>n>>Q;
	for(int i=0;i<n;i++){
		cin>>c;
		if(c=='b'){
			for(int j=0;j<cntb;j++){
				e[i].push_back(b[j]);
				e[b[j]].push_back(i);
			}
			b[cntb++]=i;
		}else{
			for(int j=0;j<cntr;j++){
				e[i].push_back(r[j]);
				e[r[j]].push_back(i);
			}
			r[cntr++]=i;
		}
		e[i].push_back((i+1)%n);
		e[i].push_back((i-1+n)%n);
	}
	while(Q--){
		cin>>s>>ed;
		dijkstra(s-1);
		cout<<dis[ed-1]<<'\n'; 
	}
	return 0;
}
//TLE-27pts
```
:::

再次思考，可得最大步数为 $3$，以下为推理过程：

该路径只有红蓝两种颜色，必有交界处，若起止地点颜色不同，我们可以传送至与**该点相同颜色**且**周围有不同颜色**的点，走一步到另一个颜色，再选择传送与否。

所以共有三种情况：

- $X_i$ 和 $Y_i$ 颜色相同，步数为 $1$
- $X_i$ 和 $Y_i$ 颜色不同且任意一点周围有不同颜色的点，传送后一步即达，步数为 $2$
- $X_i$ 和 $Y_i$ 不符合以上两种情况，步数为 $3$

特别需要注意一点：第二和第三种情况，若直接走比较近的话，直接走过去，如：

```
6 1
brrbrr
3 4
```

```
6 1
bbbrrr
2 5
```

**题目没有规定颜色不能都一样，所以最好特判，但我没有特判也过了，建议加强样例。**

最后代码：

```
#include<bits/stdc++.h>
using namespace std;
int n,q;
char c[500005];
int x,y;
int main(){
	cin>>n>>q;
	for(int i=0;i<n;i++){
		cin>>c[i];
	}
	while(q--){
		cin>>x>>y;
		x--,y--;
		if(c[x]==c[y]){
			cout<<1<<'\n';
			continue;
		}else if(c[(x+1)%n]==c[(x-1+n)%n]&&c[x]==c[(x-1+n)%n]&&c[(y+1)%n]==c[(y-1+n)%n]&&c[y]==c[(y-1+n)%n]){
			if((x-y+n)%n==2||(y-x+n)%n==2) cout<<2<<'\n';
			else cout<<3<<'\n';
		}else{
			if((x-y+n)%n==1||(y-x+n)%n==1) cout<<1<<'\n';
			else cout<<2<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：b9113fced86a32cad0d8 (赞：1)

~~很坑的一道题。~~

# 大体原理
对于本题，考虑分类讨论。仔细观察题目，可以把情况分为以下类别：

 - 起点和终点在同一种颜色；
 - 起点和终点在不同颜色：
   - 起点在颜色边缘，但终点不在；
   - 终点在颜色边缘，但起点不在；
   - 起点和终点都不在颜色边缘；
   - 起点和终点都在颜色边缘：
     - 起点和终点相邻；
     - 起点和终点不相邻。
   

:::info[所谓“颜色边缘”在本文中指什么？]{open}
“颜色边缘”是指某一个颜色的左侧或右侧其一是与其不同的颜色。
:::

对于每一种不同的情况，只需要判断其是否属于这种情况，并给出对应的答案即可。

|不同的情况|答案|
|:-|:-|
|起点和终点在同一种颜色|显然，只需一次传送，答案为 `1`。|
|起点在颜色边缘，但终点不在|先传送到相邻的魔法阵，来到另一个颜色，再传送到终点，答案为 `2`。|
|终点在颜色边缘，但起点不在|因为传送过程可逆，答案同样为 `2`。|
|起点和终点都不在颜色边缘|先来到边缘，再来到另一个颜色，最后来到终点，答案为 `3`。|
|起点和终点相邻|移动到相邻魔法阵，答案为 `1`。|
|起点和终点不相邻|先移动到终点旁边，再移动到终点，答案为 `2`。|

# 代码实现
只需要在代码中不断地 `if();else{}` 就行了，重点在判断这是什么情况。

因为魔法阵是一个环形，所以说 $1$ 和 $n$ 也算相邻。所以无论是边缘判断还是相邻判断都需要用到模运算。

值得注意的是，魔法阵的编号是从 $1$ 开始的，所以说在判断时下标要减一；另外，在判断编号为 $1$ 的魔法阵时，可能导致得到 $-1$，所以取模前要加上 $n$。

具体的判断方式可以看正确代码。

## 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,q;
string s;

bool check(int pos){//true=red,false=blue
	int tpos = (pos + n - 1) % n;
	if(s[tpos] == 'r') return true;
	return false;
}

int main(){
	cin>>n>>q;
	cin>>s;
	for(int i = 1;i <= q;i++){
		int a,b;
		cin>>a>>b;
		if(check(a) == check(b)){// 起点和终点在同一种颜色
			cout<<1<<"\n";
			continue;
		}
		if(abs((a + n - 1) % n - (b + n - 1) % n) == 1 || (a == 1 && b == n) || (b == 1 && a == n)){// 起点和终点相邻 
			cout<<1<<"\n";
			continue;
		}
		if(check(a) == check(a - 1) && check(a) == check(a + 1) && check(b) == check(b - 1) && check(b) == check(b + 1)){// 起点和终点都不在颜色边缘 
			cout<<3<<"\n";
			continue;
		}
		cout<<2<<"\n";// 其它情况 
	}
	return 0;
}
```

---

## 作者：szh_AK_all (赞：0)

简单分类讨论。

首先不难看出答案是不超过 $3$ 的，那可以分别对答案为 $1,2,3$ 的情况进行讨论。

- 若 $x,y$ 相邻，则答案为 $1$。

- 否则，若 $x,y$ 颜色相同，则答案为 $1$。

- 否则，若 $x$ 可以走两步到达 $y$，则答案为 $2$。

- 否则，若与 $x$ 相邻的某个点颜色与 $y$ 相同或者与 $y$ 相邻的某个点颜色与 $x$ 相同，则答案为 $2$。

- 否则，答案为 $3$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int n,q;
    cin>>n>>q;
    string s;
    cin>>s;
    s=" "+s;
    s[0]=s[n];
    while(q--)
    {
        int x,y;
        cin>>x>>y;
        if(s[x]==s[y])
            cout<<1;
        else if(x==(y%n+1)||(y==(x%n+1)))
            cout<<1;
        else if(s[x%n+1]==s[y]||s[x-1]==s[y]||s[y%n+1]==s[x]||s[y-1]==s[x])
            cout<<2;
        else if(abs(x-y)<=2||(x==1&&y>=n-1)||(x==n&&y<=2)||(x==2&&y==n)||(x==n&&y==2))
        cout<<2;
        else cout<<3;
        cout<<"\n";
    }
}
```

---

## 作者：Zjb13927701829 (赞：0)

# P13735 [Magic Circle](https://www.luogu.com.cn/problem/P13735) 题解
## 前言
**算法思路**一栏中的 $x$、$y$ 均分别指的是 $s_x$、$s_y$。
## 题目分析
给定一个**仅由** `br` 组成、长度为 $n$ 的**环形**字符串 $s$ 和 $q$ 次查询，每次查询两个位置 $x$、$y$，求从 $x$ 按照移动规则移动到 $y$ 的最小移动次数，移动规则如下：
- 选择一个相邻的字符，花费 $1$ 次移动过去。换句话说，可以在字符 $j(1\le j\le N-1)$ 和 $j+1$ 间传送（两个方向均可），**也可以在字符** $1$ **和** $N$ **间移动**（两个方向均可）；
- 选择一个与当前所在字符相同的字符（不一定要相邻），花费 $1$ 次移动过去。
## 算法思路
对于每次查询，查询的算法见下：
1. 若**位置相邻**或者 $x$、$y$ 相同：$1$ 次移动即可到达。
2. **否则**，进行层级判断（此时 $x$、$y$ 不同）：
- 检查是否存在 $x$ 的邻居与 $y$ 相同，或 $y$ 的邻居与 $x$ 相同；
- 存在就可以通过 $2$ 次移动到达；
- 否则就需要通过 $3$ 次移动到达。

## 层级判断过程
1. 需通过 $2$ 次移动到达的**过程**：
   $$x \to x\text{ 的邻居 }z \to \text{ 与 }z \text{ 相同的字符 }y$$
或者是：
   $$x \to \text{ 与 }x\text{ 相同的字符 }z \to z\text{ 的邻居 }y$$
2. 需通过 $3$ 次移动到达的**过程**：
   $$x \to \text{ 与 }x\text{ 相同的字符 }z \to z\text{ 的邻居 }w \to \text{ 与 }w\text{ 相同的字符 }y$$

说了这么多，一起来看看我的 [AC](https://www.luogu.com.cn/record/232243877) 代码吧！
## 代码实现
```cpp
//（防伪结尾）审核题解不易，管理员辛苦了！
#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int n,q;
    string s;
    cin>>n>>q>>s;
    s=" "+s;
    while(q--){
        int x,y;
        cin >>x>>y;
        if(s[x]==s[y]){ //起始相同
            cout<<"1\n";
            continue;
        }
        
        int dis=min(abs(x-y),n-abs(x-y));
        if (dis==1){ //起始相邻
            cout<<"1\n";
            continue;
        }
        
        bool fd=false; //用于层级判断的布尔值
        int xp=(x==1)?n:x-1;
        int xn=(x==n)?1:x+1;
        if(s[xp]==s[y]||s[xn]==s[y]){ //检查x的邻居是否与y相同
            fd=true;
        }
        
        int yp=(y==1)?n:y-1;
        int yn=(y==n)?1:y+1;
        if(s[yp]==s[x]||s[yn]==s[x]){ //检查y的邻居是否与x相同
            fd=true;
        }
        
        if(fd){
            cout<<"2\n";
        } 
        else{
            cout<<"3\n";
        }
    }
    
    return 0;
} //程序结束
````

---

## 作者：Indestructible (赞：0)

## 题意

一个长度为 $N$ 且仅包含字符 $\texttt{b}$ 和 $\texttt{r}$ 的字符串 $S$，任意两个相邻字符或同色（即相同）字符（$S_1$ 与 $S_N$ 也算作相邻）之间的距离为 $1$。有 $Q$ 次询问，每次询问给定 $X_i,Y_i$，求 $S_{X_i}$ 与 $S_{Y_i}$ 之间的最小距离。

## 解法

对于以下的 $\pm 1$ 操作和相邻的定义，均默认特判了 $S_1$ 和 $S_N$ 之间的情况。

显然，对于任意两个满足数据范围的 $X_i,Y_i$，$S_{X_i}$ 与 $S_{Y_i}$ 之间的最小距离只可能有以下三种：

- $S_{X_i},S_{Y_i}$ 相邻或同色，距离为 $1$。
- 否则，若存在 $S_{X_i+1}$ 或 $S_{X_i-1}$ 与 $S_{Y_i}$ 同色，或者存在 $S_{Y_i+1}$ 或 $S_{Y_i-1}$ 与 $S_{X_i}$ 同色，易得距离为 $2$。（代码一般记录是否存在 $S_{i-1}$ 或 $S_{i+1}$ 与 $S_i$ 异色，即对于每个 $i$，预处理出 $S_i$ 是否存在异色节点）  
  **证明**：假设 $S_{Y_i-1},S_{X_i}$ 同色，可以从 $S_{X_i}$ 跳到 $S_{Y_i-1}$，再从 $S_{Y_i-1}$ 跳到相邻的 $S_{Y_i}$。其余三种情况同理。
- 否则易得距离为 $3$。  
  **证明**：假设 $S_a,S_{X_i}$ 同色，$S_b,S_{Y_i}$ 同色且与 $S_a$ 相邻（显然一定存在），路线为 $S_{x_i}\to S_a\to S_b\to S_{Y_i}$。由于异色之间只能相邻移动，在 $S_{X_i},S_{Y_i}$ 均无相邻异色节点时，不可能在小于 $3$ 步时完成移动。

根据以上三种情况代码判断即可。

## 代码

不要忘记**特判下标**！

```cpp line-numbers
#include <bits/stdc++.h>
#define fr(i, x, y) for (int i = (x); i <= (y); i ++)
using namespace std;

const int N = 5e5 + 6;
int n, q, x, y;
string s; // 字符串 
bool f[N]; // 记录是否存在相邻异色点 

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> q >> s;
	fr(i, 0, n - 1) // 记录时注意下标 
		f[i] = (s[(i + n - 1) % n] != s[i] || s[(i + 1) % n] != s[i]);
	fr(i, 1, q){
		cin >> x >> y;
		x --, y --; // 下标范围 0 ~ n - 1 
		if (abs(y - x) == 1 || abs(y - x) == n - 1 || s[x] == s[y])
			cout << 1 << "\n"; // 相邻或同色（相邻要特判下标） 
		else if (f[x] || f[y]) cout << 2 << "\n"; // 存在相邻异色点 
		else cout << 3 << "\n"; // 均不符合 
	}
	return 0; // 好习惯让 CSP2025 RP++ 
}

```

[AC 记录](https://www.luogu.com.cn/record/232117416)。

---

## 作者：IntoTheDusk (赞：0)

::::info[题面]
有 $n$ 个点排成一个环，每个点要么是红色的，要么是蓝色的。你可以进行若干次移动，每次移动的方式有两种：

- 花费 $1$ 的代价移动到相邻的一个点。
- 花费 $1$ 的代价传送到任意一个同色的点。

你需要回答 $q$ 次询问，每次询问给出 $x,y$，求从 $x$ 到 $y$ 的最小代价。

$1 \le n \le 5 \times 10^5,1 \le q \le 5 \times 10^5,1 \le x,y \le n,x \ne y,\rm{1.0s,1024MiB}$。
::::

注意到，答案必然只能是 $1,2,3$。

- 如果 $x,y$ 相邻或者 $x,y$ 的颜色相同，我可以直接一步到位，故答案为 $1$。
- 在答案不为 $1$ 时，如果 $x,y$ 距离为 $2$ 时答案为 $2$；如果某个与 $x$ 相邻的点的颜色与 $y$ 相同，则答案为 $2$，因为我可以先移动到这个和 $y$ 颜色相同的且与 $x$ 相邻的点再一步传送到 $y$。同理，如果某个与 $y$ 相邻的点的颜色与 $x$ 相同，则答案也为 $2$。
- 如果答案不为 $1,2$，则答案为 $3$。具体做法如下：
  + 选择一个点 $z$ 满足 $z$ 的颜色与 $x$ 相同且某个与 $z$ 相邻的点的颜色与 $y$ 相同。设这个与 $z$ 相邻且颜色与 $y$ 相同的点为 $k$。
  + 从 $x$ 传送到 $z$。
  + 从 $z$ 传送到 $k$。
  + 从 $z$ 传送到 $y$。

据此直接模拟并判断即可。时间复杂度 $O\left(n+q\right)$。

在写的时候需要和两点之间的距离取最小值，防止 $n$ 很小时出错。

[评测记录](https://www.luogu.com.cn/record/231595539)

::::success[一份C++实现]
```cpp
#include <bits/stdc++.h>
#define int long long
#define INF 0x3f3f3f3f
using namespace std;
int n,m;
string s;
int dis(int l,int r){
	if(r<l) swap(l,r);
	return min(r-l,(n-r+l));
}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n>>m;
	cin>>s;s=" "+s+" ";
	s[0]=s[n];s[n+1]=s[1];
	while(m--){
		int l,r;cin>>l>>r;
		int ans=dis(l,r);
		if(s[l]==s[r]) ans=min(ans,1ll);
		else if(s[r-1]==s[l]||s[r+1]==s[l]) ans=min(ans,2ll);
		else if(s[l-1]==s[r]||s[l+1]==s[r]) ans=min(ans,2ll);
		else ans=min(ans,3ll);
		cout<<ans<<'\n';
	}
	return 0;
}
```
::::

---

