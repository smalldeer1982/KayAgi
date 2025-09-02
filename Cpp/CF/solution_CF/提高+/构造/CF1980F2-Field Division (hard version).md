# Field Division (hard version)

## 题目描述

This is a hard version of the problem; it differs from the easy version only by the question. The easy version only needs you to print whether some values are non-zero or not. The hard version needs you to print the exact values.

Alice and Bob are dividing the field. The field is a rectangle of size $ n \times m $ ( $ 2 \le n, m \le 10^9 $ ); the rows are numbered from $ 1 $ to $ n $ from top to bottom, and the columns are numbered from $ 1 $ to $ m $ from left to right. The cell at the intersection of row $ r $ and column $ c $ is denoted as ( $ r, c $ ).

Bob has $ k $ ( $ 2 \le k \le 2 \cdot 10^5 $ ) fountains, all of them are located in different cells of the field. Alice is responsible for dividing the field, but she must meet several conditions:

- To divide the field, Alice will start her path in any free (without a fountain) cell on the left or top side of the field and will move, each time moving to the adjacent cell down or right. Her path will end on the right or bottom side of the field.
- Alice's path will divide the field into two parts — one part will belong to Alice (this part includes the cells of her path), the other part — to Bob.
- Alice will own the part that includes the cell ( $ n, 1 $ ).
- Bob will own the part that includes the cell ( $ 1, m $ ).

Alice wants to divide the field in such a way as to get as many cells as possible.

Bob wants to keep ownership of all the fountains, but he can give one of them to Alice. First, output the integer $ \alpha $ — the maximum possible size of Alice's plot, if Bob does not give her any fountain (i.e., all fountains will remain on Bob's plot).

Then output $ k $ non-negative integers $ a_1, a_2, \dots, a_k $ , where $ a_i $ is a value such that after Bob gives Alice the $ i $ -th fountain, the maximum size of her plot will be $ \alpha + a_i $ .

## 说明/提示

Below are the images for the second example:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1980F2/50ede57a92b2f87fd310741ab01efa95ca5a8eab.png) The indices of the fountains are labeled in green. The cells belonging to Alice are marked in blue.Note that if Bob gives Alice fountain $ 1 $ or fountain $ 3 $ , then that fountain cannot be on Alice's plot.

## 样例 #1

### 输入

```
5
2 2 3
1 1
1 2
2 2
5 5 4
1 2
2 2
3 4
4 3
2 5 9
1 2
1 5
1 1
2 2
2 4
2 5
1 4
2 3
1 3
6 4 4
6 2
1 3
1 4
1 2
3 4 5
2 1
3 2
1 4
1 3
2 4```

### 输出

```
1
1 0 1 
11
0 1 0 4 
1
0 0 1 1 0 0 0 0 0 
6
15 0 0 0 
1
2 3 0 0 0```

# 题解

## 作者：Moya_Rao (赞：1)

题解区居然只有一篇题解，太可恶了。那我还是好心造福一下各位吧。

题意不用多说，不懂的自己[先看题去](https://www.luogu.com.cn/problem/CF1980F2)。

首先呢，你要完成[简单版本](https://www.luogu.com.cn/problem/CF1980F1)的题目，因为我的这种做法，简单版本的思路至关重要。建议看[这篇题解](https://www.luogu.com.cn/article/57qlljuk)，讲的还算详细。~~不要问我为什么不自己写篇题解，主要太懒了~~

本题，也就是困难版本，依然需要输出一个 Bob 喷泉都不让的情况下，Alice 到底能搞到多少块土地。所以可以直接把简单版的代码粘过来，这一部分就搞定了。

接下来处理让一个喷泉的情况可就麻烦了。

首先我们可以保留简单版代码中那个求答案的，也就是有一个 `bool` 类型的 $v$ 数组用来存储 $0/1$。我们在计算答案的时候就可以跳过 $v_i = 0$ 的，省时间。

接着就是重点部分了。当前枚举到了一个拐点 $i$，我们需要查找到位于它之前的第一个拐点 $l$ 以及位于它之后的第一个拐点 $r$。怎么找？其实上暴力枚举不成问题，因为全部的时间加起来也不过 $O(k)$ 而已。

然后呢？可以发现，如果当前这个 $i$ 喷泉被移走以后，Alice 能获得的土地就会多出来一个矩阵。如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/7ers3rhx.png)

其中红色部分是其他的喷泉，标了字母的是我们当前处理的三个喷泉。橙色部分（包括 $i$ 的深橙色和其他浅橙色）都是我们多出来的那个矩阵。这个矩阵可以由 $i$ 还有 $l$ 以及 $r$ 的坐标对应算出来。具体公式会在代码中展示，不过还是建议各位自己拿草稿纸画个图推一推，挺简单的。

但是有一种情况是不可避免的，那就是我们的这个矩阵中还有别的喷泉挡着路，导致我们不能直接让这个矩阵的面积作为答案。

那该怎么办？我们敏锐地发现，其实上这就是在对一个子矩阵做最开始求不让喷泉的答案！那就轻松了，我们把简单版的代码粘过来，搞成一个函数，然后直接对这一块进行操作就好了。细节挺多，实现起来并不容易，可以多参考下我的代码。

然后就没有然后了呢。我们直接就把那个函数的结果作为这个 $i$ 的最终答案就行了，最后一把输出即可。

其他的细节还是看代码吧，多分析一下应该就能搞明白了。代码保证对的咯，不信看这个[提交记录](https://codeforces.com/contest/1980/submission/324041292)嘛。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int K = 2e5+5;
struct node{long long x,y,id;}a[K];
long long T,n,m,k,ans,res[K];bool v[K];stack<node> st;
bool cmp(node d1,node d2){return (d1.x<d2.x||(d1.x==d2.x&&d1.y<d2.y));}
long long Count_Answer(int l,int r,int sx,int sy,int ex,int ey){
    for(int i=l;i<=r;i++){
        if(a[i].x==ex&&a[i].y==sy)continue;
        if(a[i].x<sx||a[i].x>ex||a[i].y<sy||a[i].y>ey)continue;
        if(a[i].x==a[i-1].x&&i>l&&!(a[i-1].x==ex&&a[i-1].y==sy))continue;
        while(!st.empty()&&st.top().y>=a[i].y)st.pop();
        st.push(a[i]);
    }
    st.push({ex,ey+1,0});long long as=0;
    while(!st.empty()){
        node u=st.top();st.pop();
        u.x-=sx-1,u.y-=sy-1;
        if(st.empty()){as+=u.x*(u.y-1);continue;}
        node v=st.top();
        v.x-=sx-1,v.y-=sy-1;
        as+=(u.x-v.x)*(u.y-1);
    }
    return as;
}
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m>>k;
        for(int i=1;i<=k;i++){cin>>a[i].x>>a[i].y;a[i].id=i;}
        sort(a+1,a+k+1,cmp);
        for(int i=1;i<=k;i++){
            if(a[i].x==a[i-1].x){v[a[i].id]=0;continue;}
            while(!st.empty()&&st.top().y>=a[i].y){v[st.top().id]=0;st.pop();}
            st.push(a[i]);v[a[i].id]=1;
        }
        st.push({n,m+1,0});ans=0;
        while(!st.empty()){
            node u=st.top();st.pop();
            if(st.empty()){ans+=u.x*(u.y-1);continue;}
            node v=st.top();ans+=(u.x-v.x)*(u.y-1);
        }
        a[0]={0,0,0},a[k+1]={n,m+1,k+1},v[0]=1,v[k+1]=1;
        for(int i=1;i<=k;i++){
            if(!v[a[i].id]){res[a[i].id]=0;continue;}
            int l=i-1,r=i+1;
            while(l>=1&&!v[a[l].id])l--;
            while(r<=k&&!v[a[r].id])r++;
            int sx=a[l].x+1,sy=a[i].y,ex=a[i].x,ey=a[r].y-1;
            res[a[i].id]=Count_Answer(l+1,r-1,sx,sy,ex,ey);
        }
        cout<<ans<<"\n";
        for(int i=1;i<=k;i++)cout<<res[i]<<" ";cout<<"\n";
    }
    return 0;
}
```

如果本篇题解对你有帮助的话，麻烦你点一个小小的赞，真是太谢谢啦！

---

## 作者：COsm0s (赞：0)

我们先考虑不减少喷泉的情况。

一个贪心的想法就是这条分割线需要紧贴喷泉走。

![](https://cdn.luogu.com.cn/upload/image_hosting/qxkrw9u6.png)

我们看看这张样例的图示，红色的分割线紧贴着 $1,2,4$ 下来。仔细观察，我们容易得出一个结论：记每一行最右的蓝色方块为 $id_i$，则 $id$ 是一个单调不降序列。

再次观察性质，我们发现同一行里如果有多个喷泉，则分割线一定在**最左**的一个之左。

这个是好证的。如果有一个喷泉在其左边有喷泉，则如果分割线紧贴在在当前喷泉左边，则他左边的喷泉必定被蓝色方块覆盖，与题目矛盾。

为了方便，我们引入第 $k+1$ 列，并假定在 $(n,m+1)$ 有喷泉。

我们按列正序处理，则取到当前列最大的 $x_i$，面积即为 $(y_i-1)\times (x_i-pre)$，其中 $pre$ 是 $0$ 至 $i-1$ 列我们取到的 $x$。

举个例子，我们还是看上面那张图。

+ 在做第一列时，由于没有喷泉，则 $pre=0$。
+ 在做第二列时，我们取到喷泉 $2$，贡献为 $(2-1)\times 2,pre=2$。
+ 在做第三列时，我们取到喷泉 $4$，贡献为 $(3-1)\times (4-2),pre=4$。
+ 做第四列时，没有一个 $x\geq pre$，贡献为零。
+ 第五列没有喷泉。
+ 第六列（假）取到喷泉 $6$，贡献为 $(6-1)\times (5-4)$。

至此，我们解决了第一部分的问题。

我们再来看看删去一个 $i$ 会发生什么。

首先，如果 $i$ 并没有刚才第一次中产生贡献，比如刚才的喷泉 $3$，那么删去它显然没有影响。

如果它有影响，我们就模拟刚才的流程将这个点的贡献减去，然后在将其上一个有贡献的点和他下一个有贡献的点进行贡献。

需要注意的是，可能在新产生的矩形中会包含刚才没有被贡献到的喷泉。

我们还是看到上面那张图，当我们删去喷泉 $4$ 时，喷泉 $2$ 和喷泉 $6$ 新产生的矩形为以 $(3,3)$ 为左上角，$(4,5)$ 为右下角的矩形。

但是这包含了喷泉 $3$，因此我们需要将喷泉 $3$ 的贡献删去。

在一个新产生的矩形中可能会有好几个新被包含的喷泉，我们直接暴力枚举删除。由于每个喷泉只会被暴力删去一次，所以均摊是 $O(k)$ 的。

复杂度 $O(k\log k)$，瓶颈在于一开始按列的排序。


```cpp
struct node {
	int x, y, id;
	bool operator < (const node& t) const {
		return y != t.y ? y < t.y : x > t.x;
	}
} a[N];
void Solve() {
	int n, m, k;
	cin >> n >> m >> k;
	poly vis(k + 5, 0), ans(k + 5, 0);
	REP(i, 1, k) {
		cin >> a[i].x >> a[i].y;
		a[i].id = i;
	}
	sort(a + 1, a + k + 1);
	int cur = 0, pre = 0;
	REP(i, 1, k) {
		if(a[i].x <= pre) continue;
		vis[a[i].id] = true;
		cur += (a[i].x - pre) * (a[i].y - 1);
		pre = a[i].x;
	}
	cur += (n - pre) * m;
	//第一次的贡献
	a[0] = {0, 0, 0};
	a[k + 1] = {n, m + 1, 0};
	REP(i, 1, k) {
		if(!vis[a[i].id]) continue;
		int l = i - 1, r = i + 1;
		int x = a[i].x, y = a[i].y, id = a[i].id;
		while(~l && !vis[a[l].id]) l --;
		while(r <= k + 1 && !vis[a[r].id]) r ++;
		if(l < 0) l ++; if(r > k + 1) r --;
		int res = (x - a[l].x) * (a[r].y - y);//新产生的矩形面积
		int p = a[l].x;
		REP(j, i + 1, r - 1) {
			if(a[j].x > p) {
				res -= (a[j].x - p) * (a[r].y - a[j].y);
				p = a[j].x;
			}
		}//暴力枚举新被覆盖的点删除
		ans[a[i].id] = res;
	}
	cout << cur << '\n';
	REP(i, 1, k) cout << ans[i] << ' ';
	cout << '\n';
}
```

---

