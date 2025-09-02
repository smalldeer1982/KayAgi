# [ABC012D] バスと避けられない運命

## 题目描述

高桥君，不太喜欢公共汽车。

但是，一进入社会，就无法避免乘坐公共汽车的行为。

进入社会后，从自家到公司，必须坐公共汽车上班。高桥君还没拿到录取单，不知道要进入哪家公司，自然也就不知道公司在哪儿。高桥君经常想象乘坐巴士情况。他只想象时间最长、最坏的情况。我想把乘坐这个最坏情况的巴士的时间搬到让高桥君上班时间尽量缩短的地方。

PS：最坏的情况是指，乘坐巴士的时间合计最短，选择所乘坐的巴士时，是指在坐公共汽车的时间合计会变长的位置有公司的情况。

另外，从家中去公司时，可以选择高桥乘坐的巴士，高桥君选择乘坐巴士的时间合计最短的路径。各巴士在 $2$ 个公交车站来回行驶，去、回所需时间没有差别。随时都可以乘坐巴士，可以忽略转乘所花费的时间等。

另外，自家和公司与公共汽车站相邻，不能步行到其他巴士站，也不能通过巴士以外的方法进行移动。为高桥君找个搬家的地方，请输出搬到那里时，要坐公交车时间的最大值。

## 样例 #1

### 输入

```
3 2
1 2 10
2 3 10```

### 输出

```
10```

## 样例 #2

### 输入

```
5 5
1 2 12
2 3 14
3 4 7
4 5 9
5 1 18```

### 输出

```
26```

## 样例 #3

### 输入

```
4 6
1 2 1
2 3 1
3 4 1
4 1 1
1 3 1
4 2 1```

### 输出

```
1```

# 题解

## 作者：Ja50nY0un9_as_AgNO3 (赞：5)

发现自己咕值 229 了，就用这篇题解送自己上红吧。

题目给了我们一张无向图，让我们找一个点，使它距所有点距离的最大值最小，并输出这个最小值。

看到数据范围，$N\le300$，可以直接用 $\Theta(N^3)$ 的 Floyd 算法通过。

然后遍历 $dis$ 数组，找到每一行的最大值的最小值，最后输出。

作者惨痛的经历提醒你特别要注意 Floyd 三层循环的顺序。

接下来是代码。
```cpp
# include <iostream>
# include <cstring>
using namespace std;

int dis[301][301];

int main(){
    memset(dis, 0x3f, sizeof(dis));
    //初始化
    int n, m;
    cin >> n >> m;
    while (m--){
        int x, y, d;
        cin >> x >> y >> d;
        dis[x][y] = d, dis[y][x] = d;
    }
    for (int i = 1; i <= n; i++) dis[i][i] = 0;
    for (int k = 1; k <= n; k++)//第一层循环枚举中转点
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    int minn = 2e9;
    for (int i = 1; i <= n; i++){
        int maxn = 0;
        for (int j = 1; j <= n; j++)
            maxn = max(maxn, dis[i][j]);
        minn = min(minn, maxn);
    }
    cout << minn << endl;
    return 0;
}
```

---

## 作者：Elairin176 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc012_4)         
这题的题意比较不清晰，这里解释一下：给你一张无向图，计算出所有点到指定点最短路的最大值的最小值。        
一看到最短路和 $2\le N\le300$，我们就可以想到一个简单的最短路算法：Floyd 算法。    
Floyd 算法的实现很简单。用邻接矩阵存图，先初始化所有点权为 $\infty$，再进行计算。每一次计算的式子如下：$f_{i,j}=\min(f_{i,j},f_{i,k}+f_{k,j})$。注意 $k$ 是第一层循环内的。      
求出全源最短路后，我们就可以计算答案了。对于每个点，跑剩下的点求出最长最短路，再和答案进行比较。        
时间复杂度 $O(N^3)$，可以通过本题。   
CODE：    
```
#include <iostream>
using namespace std;
int n,m,u,v,w,f[500][500],maxx,ans=2147483647;
inline int min(int a,int b){
	return a>b?b:a;
}
inline int max(int a,int b){
	return a<b?b:a;
}
int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){//初始化为1000000
		for(int j=1;j<=n;j++){
			f[i][j]=1000000;
		}
		f[i][i]=0;
	}
	while(m--){
		scanf("%d%d%d",&u,&v,&w);
		f[u][v]=w;//两边赋值
		f[v][u]=w;
	}
	for(int k=1;k<=n;k++){//Floyd
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
			}
		}
	}
	for(int i=1;i<=n;i++){//暴力求结果
		maxx=0;
		for(int j=1;j<=n;j++){
			maxx=max(f[i][j],maxx);
		}
		ans=min(ans,maxx);
	}
	printf("%d\n",ans);
}
```


---

## 作者：FJ_Farmer_Johhn (赞：0)

# 题意
这道题不知道是因为翻译还是什么原因，题意给的非常的迷惑，总结一下，主要就是让求一个点，使得这个点到其他所有点的最短路的最大值最小，求出这个最大值。
# 前置知识
弗洛伊德（Floyd）算法，如果还不会就请先移步[这里](https://blog.csdn.net/jeffleo/article/details/53349825?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167109177416782429776426%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=167109177416782429776426&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-53349825-null-null.142^v68^control,201^v4^add_ask,213^v2^t3_control2&utm_term=%E5%BC%97%E6%B4%9B%E4%BC%8A%E5%BE%B7%E7%AE%97%E6%B3%95&spm=1018.2226.3001.4187)
# 解题思路
会了弗洛伊德这道题就不难了，直接跑一遍弗洛伊德求出图中任意两点的最短路，之后由于数据范围很小，就可以直接暴力枚举一下每个点作为起点的情况，先取最大值再取最小值就可以啦。
# 注意事项
别忘了弗洛伊德的中间点 $ k $ 是在最外层循环
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[1001][1001],ans=0x7fffffff;
int main()
{
	scanf("%d%d",&n,&m);
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		f[x][y]=f[y][x]=z;
	}
	for(int k=1;k<=n;k++)
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				f[i][j]=min(f[i][k]+f[k][j],f[i][j]);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		int mx=0;
		for(int j=1;j<=n;j++)
		{
			if(i==j)
				continue;
			mx=max(mx,f[i][j]);
		}
		ans=min(mx,ans);
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：AlicX (赞：0)

### 题意

这道题意十分迷惑，在此感性理解一下：有一个 $n$ 个点，$m$ 条边的图，请你找到任意一个点，使他到其他点的最大值最小，输出这个值。

## 思路
这道题题意明了之后，就是一道模板题了。首先求出每两个点之间的最短路，这里使用弗洛伊德算法求解，可以发现 $n \leq 300$，所以不会超时。然后暴力枚举每一个点，取这个点到其余点的最大值的最小值就可以了。

不会弗洛伊德的小伙伴看这里：[弗洛伊德算法](https://blog.csdn.net/jeffleo/article/details/53349825?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166917487416782428669398%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166917487416782428669398&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-53349825-null-null.142^v66^control,201^v3^control_2,213^v2^t3_control1&utm_term=%E5%BC%97%E6%B4%9B%E4%BC%8A%E5%BE%B7%E7%AE%97%E6%B3%95&spm=1018.2226.3001.4187)。


### AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=310;
int n,m;
int dis[N][N];//表示每两个点之间的最短距离 
signed main(){
	memset(dis,0x3f,sizeof dis);//因为要求最小值，所以初始化为正无穷 
	cin>>n>>m;
	while(m--){
		int u,v,w;
		cin>>u>>v>>w;
		dis[u][v]=dis[v][u]=w;//建立双向边 
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
				//枚举中转点k，更新i，j两点之间的最短路 
			}
		}
	}
	int res=1e9+7;
	for(int i=1;i<=n;i++){
		int ans=0;
		for(int j=1;j<=n;j++){
			if(i==j) continue;//重复了就跳过 
			ans=max(ans,dis[i][j]);//i点到其余点的最短路的最大值 
		}
		res=min(res,ans);//更新最小值 
	}
	cout<<res<<endl;
	return 0;//Bye~ 
}
```

---

