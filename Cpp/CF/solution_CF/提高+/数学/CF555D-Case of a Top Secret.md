# Case of a Top Secret

## 题目描述

平面上有 $n$ 个钉子，从 $1$ 到 $n$ 编号，第 $i$ 个钉子的坐标是 $(x_i,0)$。  
把一个长度为 $L$，带重物的绳子系到第 $i$ 个钉子上，即重物所在的坐标是$(x_i,-L)$。然后将重物向右推，绳子开始逆时针旋转。

如果旋转的过程中绳子碰到其它的钉子，就会绕着那个钉子旋转。  
如果绳子碰到多个钉子，那么它会绕着离刚才的钉子的最远的那个钉子转。（参考图示）  
如果绳子的末端碰到了一个钉子，那么绳子也会绕着那个钉子、以长度为 $0$ 的在转。

每个钉子都很细，重物绕着它旋转时，不影响到绳子的长度。

经过一段时间之后，重物就会一直绕着某个钉子转。

现在有 $m$ 个查询，每个查询给出初始的绳子长度以及挂在哪个钉子下旋转，请找出重物最终会绕哪个钉子旋转。

## 说明/提示

$1\le n,m\le 2\times10^5$

$1\le a_i\le n$

$-10^9\le x_i\le 10^9$

$1\le l_i\le 10^9$ 

翻译修改自[题解](https://www.luogu.com.cn/blog/SJYAKIOI/solution-cf555d)

## 样例 #1

### 输入

```
3 2
0 3 5
2 3
1 8
```

### 输出

```
3
2
```

## 样例 #2

### 输入

```
4 4
1 5 7 15
1 4
2 15
3 16
1 28
```

### 输出

```
2
4
3
1
```

# 题解

## 作者：Luzhuoyuan (赞：1)

补充一下正确性和复杂度证明。

首先有一个简单的暴力：每次二分找到这次走到的点，不断走直到不能走为止。当然这显然是不能通过的，两个距离为 $1$ 的点和一根长为 $10^9$ 的绳子就能卡掉。考虑进行优化。

我们可以发现，从第三步开始，每步走到的点都在前两步之间（包括前两步的点）。如果跨出了两步前的点，那么在两步前就能走到这个点了（如图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/96mh5hqf.png)

因此，每次走的时候，可以计算出我们在这两个点之间走的次数，之后绳长只要对两点间距离取模就可以了。

复杂度也非常容易证明。考虑每走一步就是对绳长进行一次取模，那么绳长要么减少至少一半，要么不变（此时已经找到目标点了）。所以走的次数是 $O(\log V)$ 的（$V$ 为值域大小）。卡满的情况就是让点间距离每次缩小一半。时间复杂度为 $O(m\log V\log n)$。

注意需要特殊处理第一步走的情况。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)((x).size())
using namespace std;
const int N=2e5+5;
int n,m,a[N],d[N],id[N],x,y,z;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i],d[i]=i;
	sort(d+1,d+n+1,[](int x,int y){return a[x]<a[y];});
	for(int i=1;i<=n;i++)id[d[i]]=i;
	sort(a+1,a+n+1);
	while(m--){
		cin>>x>>y;x=id[x];z=0;
		int p=upper_bound(a+1,a+n+1,a[x]+y)-a-1;
		y-=a[p]-a[x],x=p;		
		while(1){
			if(z){
				p=upper_bound(a+1,a+n+1,a[x]+y)-a-1;
				if(p==x)break;
				z=!((y/(a[p]-a[x]))&1),y%=a[p]-a[x];
				if(!z)x=p;
			}else{
				p=lower_bound(a+1,a+n+1,a[x]-y)-a;
				if(p==x)break;
				z=(y/(a[x]-a[p]))&1,y%=a[x]-a[p];
				if(z)x=p;
			}
		}
		cout<<d[x]<<'\n';
	}
	return 0;
}
```

（逃

---

## 作者：素质玩家孙1超 (赞：0)

题目

```
平面上有n个钉子，他们从１到n编号，第i个钉子的坐标是 (xi, 0)。然后我们我们把一个长度为Ｌ，带重物的绳子系到第i个钉子上（那么重物所在的坐标是(xi, -L)）。然后用力将重物向右推，开始逆时针旋转。同时，如果旋转的过程中碰到其它的钉子，就会绕着那个钉子旋转。假设每个钉子都很细，重物绕着它旋转时，不影响到绳子的长度。


更一般的，如果绳子碰到多个钉子，那么它会绕着最远的那个钉子转。特殊的，如果绳子的末端碰到了一个钉子，那么也会绕着那个钉子以长度为０的绳子在转。

经过一段时间之后，重物就会一直绕着某个钉子转。

现在有m个查询，每个查询给出初始的绳子长度以及挂在哪个钉子下旋转，请找出重物最终会绕哪个钉子旋转
```

题意：让你模拟绳子的旋转（中途会碰到许多钉子），问最后绳子停留在哪一个钉子上

---

解法：运用模拟算法，先排序，然后二分查找下一个钉子

~~你以为这样就完了吗~~

注意事项：

+ 第一个钉子虽然往右退，但是可以转一圈回到左边（后面的也同理）

+ 如果单纯的模拟会被卡比如这个数据

```

4 4
-1000000000 0 1 1000000000
2 999999999
2 999999999
2 999999999
2 999999998

```
所以必须特判：如果以前到过这个钉子，那么必然会产生循环，这时候直接取模就好了

下面是核心代码

```cpp
int n,m,b[Maxn];
map<int,int>vis;
struct point
{
	int pos;
	int num;
	bool operator < (const point &x)const
	{
		return pos<x.pos;
	}
}a[Maxn];
inline int work(int pos,int las,bool p,int dis)//p==1时候像右,las表示剩下的长度
{
	if(vis[pos])
	{
		int p=dis-vis[pos];
		las=las%p;
		vis[pos]=dis;
	}
	vis[pos]=dis;
	if(p)
	{
		int P=upper_bound(a+1,a+1+n,(point){a[pos].pos+las,0})-a-1;
		if(P==pos)
		{
			P=lower_bound(a+1,a+1+n,(point){a[pos].pos-las,0})-a;
			if(P==pos) return pos;
			return work(P,las-(a[pos].pos-a[P].pos),1,dis+(a[pos].pos-a[P].pos));
		}
		return work(P,las-(a[P].pos-a[pos].pos),0,dis+(a[P].pos-a[pos].pos));
	}
	else 
	{
		int P=lower_bound(a+1,a+1+n,(point){a[pos].pos-las,0})-a;
		if(P==pos)
		{
			int P=upper_bound(a+1,a+1+n,(point){a[pos].pos+las,0})-a-1;
			if(P==pos) return pos;
			return work(P,las-(a[P].pos-a[pos].pos),0,dis+(a[P].pos-a[pos].pos));
		}
		return work(P,las-(a[pos].pos-a[P].pos),1,dis+(a[pos].pos-a[P].pos));
	}
}
int main()
{
	n=R();m=R();int x,y;
	for(int i=1;i<=n;i++)
	{
		a[i].pos=R();
		a[i].num=i;
	}
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++) b[a[i].num]=i;
	for(int i=1;i<=m;i++)
	{
		x=R();y=R();vis.clear();
		printf("%d\n",a[work(b[x],y,1,0)].num,0);
	}
}
```

---

