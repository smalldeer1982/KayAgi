# Rooter's Song

## 题目描述

Wherever the destination is, whoever we meet, let's render this song together.

On a Cartesian coordinate plane lies a rectangular stage of size $ w×h $ , represented by a rectangle with corners $ (0,0) $ , $ (w,0) $ , $ (w,h) $ and $ (0,h) $ . It can be seen that no collisions will happen before one enters the stage.

On the sides of the stage stand $ n $ dancers. The $ i $ -th of them falls into one of the following groups:

- Vertical: stands at $ (x_{i},0) $ , moves in positive $ y $ direction (upwards);
- Horizontal: stands at $ (0,y_{i}) $ , moves in positive $ x $ direction (rightwards).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/78a4617a270ecba0555a87f4deb825cf1f501330.png)According to choreography, the $ i $ -th dancer should stand still for the first $ t_{i} $ milliseconds, and then start moving in the specified direction at $ 1 $ unit per millisecond, until another border is reached. It is guaranteed that no two dancers have the same group, position and waiting time at the same time.

When two dancers collide (i.e. are on the same point at some time when both of them are moving), they immediately exchange their moving directions and go on.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/14a342567b0e0e96e2854bafb4e39a8b293ebae4.png)Dancers stop when a border of the stage is reached. Find out every dancer's stopping position.

## 说明/提示

The first example corresponds to the initial setup in the legend, and the tracks of dancers are marked with different colours in the following figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/d441e2a826ff927d107333215574de12d2f00a07.png)In the second example, no dancers collide.

## 样例 #1

### 输入

```
8 10 8
1 1 10
1 4 13
1 7 1
1 8 2
2 2 0
2 5 14
2 6 0
2 6 1
```

### 输出

```
4 8
10 5
8 8
10 6
10 2
1 8
7 8
10 6
```

## 样例 #2

### 输入

```
3 2 3
1 1 2
2 1 1
1 1 5
```

### 输出

```
1 3
2 1
1 3
```

# 题解

## 作者：zyctc (赞：6)

有参考上一篇题解提到的 [blog](https://www.cnblogs.com/wfj2048/p/7805678.html)，有部分引用。主要思路为模拟。

注意到两点相撞的必要条件：$p_i+t_j=p_j+t_i \Rightarrow p_i-t_i=p_j-t_j$，考虑按 $p_i-t_i$ 将点划分为组。

不同组之间的点必不可能相撞，同一组中间点的路径不会交叉，只会有交点，因为有交点就会发生碰撞并转向。

因此考虑对于每一组分别考察其路径，并计算每个点的终点。

![](https://cdn.luogu.com.cn/upload/image_hosting/tpdyi658.png)

不难发现对于同一组点，因为路径不交叉，每个点的起点和终点按照图示黑线相对顺序不变。因此对于每一组，将起点和终点按照图示黑线顺序（$y$ 第一关键字从大到小，$x$ 第二关键字从小到大）排序，再一一对应即可。

~~又丑又长的~~代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
const int maxn=2e5+5,N=1e5;
inline int read(){
    int x=0,f=1,ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
    return x*f;
}
int n,X,Y;
struct node{int x,y,id;}ans[maxn];
bool operator <(const node &a,const node &b){
    if(a.y!=b.y)return a.y>b.y;
    return a.x<b.x;
}
vector<node>d[maxn],p;
vector<int>dif;unordered_map<int,int>mp;
int main(){
    n=read();X=read();Y=read();
    for(int i=1;i<=n;i++){
        int tp=read(),p=read(),t=read();
        if(tp==1)d[p-t+N].pb((node){p,0,i});
        else d[p-t+N].pb((node){0,p,i});
        if(!mp[p-t+N]){dif.pb(p-t+N);mp[p-t+N]=1;}
    }
    for(auto k:dif){
        p.clear();
        for(auto i:d[k]){
            if(!i.y)p.pb((node){i.x,Y,0});
            else p.pb((node){X,i.y,0});
        }
        sort(d[k].begin(),d[k].end());
        sort(p.begin(),p.end());
        for(int i=0;i<d[k].size();i++)ans[d[k][i].id]=p[i];
    }
    for(int i=1;i<=n;i++)
        printf("%d %d\n",ans[i].x,ans[i].y);
    return 0;
}
```


---

## 作者：moye到碗里来 (赞：2)

颇有思维难度的一道题，做题过程中查阅了https://www.cnblogs.com/wfj2048/p/7805678.html
这位dalao的博客
发现会相撞的点一定是p-t相同的点，不论是横着的还是竖着的，然后你发现，所有点能够到达的终点是不会有除了之前的点直走能够到达的点之外的点的，因为每一次相撞，其实是交换两个点的终点。

然后你又发现，一个点只能撞到同一组p更大的点和同一组所有方向不同的点，画图就可以明白了，我就是在这里卡了很久。
然后模拟一下过程，就发现，如果同一组比它p更大的点的数目，大于等于同一组所有方向不同的点的数目，那么他的方向是不会变的，反之方向变化，而且终点是很容易可以求到的，模拟一下就很容易搞懂的，不要嫌麻烦=。=

代码如下
```
#include<bits/stdc++.h>
using namespace std;
#define N 200005
vector<pair<int,int> > vec[2][N];
pair<int,int> ans[N];
int n,w,h;
int main()
{
	scanf("%d %d %d",&n,&w,&h);
	for(int i = 1; i <= n; ++i){
		int opt,p,t;
		scanf("%d %d %d",&opt,&p,&t);
		vec[opt - 1][p - t + 100000].push_back(make_pair(p,i));
	}
	for(register int i = 1,sz1,sz2; i <= 200000; ++i){
		sort(vec[0][i].begin(),vec[0][i].end());
		sort(vec[1][i].begin(),vec[1][i].end());
		sz1 = vec[0][i].size(),sz2 = vec[1][i].size();
		for(register int j = 0; j < sz1; ++j){
			if(sz1 - j - 1 >= sz2)ans[vec[0][i][j].second] = make_pair(vec[0][i][j + sz2].first,h);
			else ans[vec[0][i][j].second] = make_pair(w,vec[1][i][sz1 - j - 1].first);
		}
		for(register int j = 0; j < sz2; ++j){
			if(sz2 - j - 1 >= sz1)ans[vec[1][i][j].second] = make_pair(w,vec[1][i][j + sz1].first);
			else ans[vec[1][i][j].second] = make_pair(vec[0][i][sz2 - j - 1].first,h); 
		}
	}
	for(int i = 1; i <= n; ++i){
		printf("%d %d\n",ans[i].first,ans[i].second);
	} 
}
```

---

