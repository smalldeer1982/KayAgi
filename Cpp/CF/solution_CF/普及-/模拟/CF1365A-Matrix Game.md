# Matrix Game

## 题目描述

一个 $n$ 行 $m$ 列的网格图，有些格子上已经有 $1$，`Ashish` 和 `Vivek` 在这张网格图上做游戏，`Ashish` 先手。  

对于当前玩家，他需要在网格图上找一个位置设置为 $1$，条件是这一个位置所在的行以及列上都没有其他的 $1$，如果他不能操作了，那么他就输了。

求对于输入的网格图，谁能获胜。

## 样例 #1

### 输入

```
4
2 2
0 0
0 0
2 2
0 0
0 1
2 3
1 0 1
1 1 0
3 3
1 0 0
0 0 0
1 0 0```

### 输出

```
Vivek
Ashish
Vivek
Ashish```

# 题解

## 作者：liuyongle (赞：3)

#### 思路分析

Vivek 和 Ashish 不能在已使用的至少一个单元格的行和列中声明单元格。因此，我们需要查看最初没有使用的任何单元格的行和列的最小数量的奇偶性。

令 $a$ 为最初没有使用的任何单元格的行数，类似地为 $b$ 为最初没有使用的任何单元格的列数。每次玩家移动 $a$ 和 $b$ 都会减少 $1$，因为他们只使用行和列中的单元。

如果 $a$ 或 $b$ 之一变为 $0$，则其下一回合的玩家将输掉比赛。由于每个回合 $a$ 和 $b$ 都减少 $1$，因此 $\min(a,b)$ 首先变为 $0$。因此，如果 $\min(a,b)$ 为奇数，则 Ashish 赢得比赛，否则 Vivek 获胜。

时间复杂度为 $O(n \cdot m)$。

代码：~~还真就暴力出奇迹~~

```cpp
#include <bits/stdc++.h>
using namespace std;
 
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long

const int N = 51;

int n, m;
int a[N][N];

int32_t main()
{
	IOS;
	int t;
	cin >> t;
	while(t--)
	{
		cin >> n >> m;
		set< int > r, c;
		for(int i = 1; i <= n; i++)
		{
			for(int j = 1; j <= m; j++)
			{
				cin >> a[i][j];
				if(a[i][j] == 1)
					r.insert(i), c.insert(j);
			}
		}
		int mn = min(n — r.size(), m — c.size());
		if(mn % 2)
			cout << "Ashish" << endl;
		else
			cout << "Vivek" << endl;
	}
	return 0;
}
```

---

## 作者：ShineEternal (赞：2)

[更佳的阅读效果](https://vipblog.github.io/uvPUTnSVv/)。

## description：

- 给定一个 $n\times m$ 的矩阵，有一些格子是 $1$，有一些格子是 $0$。

- Ashish 和 Vivek 轮流往矩阵中放 $1$。某个格子可以放 $1$ 当且仅当这个格子所在的行和列没有 $1$。

- 最后无处放 $1$ 的玩家就输了。你需要输出赢家的姓名。

- 多组数据，数据组数不超过 $50$， $1\le n,m\le 50$。

- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution：

这道题目 $n,m$ 的范围较小，所以直接模拟即可。

由于先后顺序并没有影响，故按顺序添加就好。

在添加 $1$ 的时候记录下当前是谁走的。可以使用 ``TUrn=(TUrn+1)%2;`` 类似的标记器。


-----

update soon：

突然发现其实取出空行和空列的最小值判断奇偶性就行了。

## code：
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int a[55][55];
int x[55],y[55];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		memset(x,0,sizeof(x));
		memset(y,0,sizeof(y));
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
			{
				scanf("%d",&a[i][j]);
				if(a[i][j]==1)
				{
					x[i]=1;
					y[j]=1;
				}
			}
		}
		int TUrn=1;
		for(int i=1;i<=n;i++)
		{
			if(x[i]==0)
			{
				int flag=0;
				//x[i]=1;
				for(int j=1;j<=m;j++)
				{
					if(y[j]==0)
					{
						y[j]=1;
						flag=1;
						break;
					}
				}
				if(flag==1)
				{
					x[i]=1;
					TUrn=(TUrn+1)%2;
				}
			}
		}
		if(TUrn==1)
		{
			printf("Vivek\n");
		}
		else
		{
			printf("Ashish\n");
		}
	}
	return 0;
} 
```

---

## 作者：AzureMist (赞：1)

引用楼下的一句话：
>Vivek 和 Ashish 不能在已使用的至少一个单元格的行和列中声明单元格。因此，我们需要查看最初没有使用的任何单元格的行和列的最小数量的奇偶性。

为什么呢？因为一个 $1$ 可以影响一行和一列，所以如果在某一时刻所有的行或列都被占领了，那么下一个人肯定得输。每次把一个位置设置为 $1$ 都需要当前的行和列没有其他的 $1$，对方把所有的行或列都占领了，你不就没地方放置 $1$ 了吗？因为空的行和列的数量是一起减少的，所以最开始的时候哪个更少，游戏的结果就取决于哪个。

其实，不用 STL 容器也能做。

我们先定义两个数组 $acnt$ 和 $bcnt$，用来记录每行和每列的状态。然后再看 $acnt$ 和 $bcnt$ 里面有哪几个是 $0$，也就是这行或者这列最初没有使用任何单元格。游戏的结果就取决于最初没有使用任何单元格的行或列的奇偶性。最后不要忘了清空 $acnt$ 和 $bcnt$ 这两个数组，十年多测一场空，忘记 `memset` 见祖宗！

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int acnt[55],bcnt[55];
int min(int a,int b){
	return a<b?a:b;
}
int main()
{
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		int n,m;
		cin>>n>>m;
		for(int j=1;j<=n;j++)
		{
			for(int k=1;k<=m;k++)
			{
				char c;
				cin>>c;
				if(c=='1')
				{
					acnt[j]++;
					bcnt[k]++;//当前的行和列有1
				}
			}
		}
		int r=0,c=0;//因为char c是在循环当中定义的，所以不会撞车
		for(int j=1;j<=n;j++)
			if(acnt[j]==0)
				r++;
		for(int j=1;j<=m;j++)
			if(bcnt[j]==0)
				c++;//找符合要求的行和列
		if(min(r,c)%2==0) cout<<"Vivek"<<endl;
		else cout<<"Ashish"<<endl;
		memset(acnt,0,sizeof(acnt));
		memset(bcnt,0,sizeof(bcnt));//多测很糟糕
	}
	return 0;
} 
```

---

## 作者：_Fontainebleau_ (赞：1)

暴力出奇迹。

因为是橙题，所以蒟蒻用的是暴力模拟。

因为是模拟，所以具体解释全在代码里，~~居然排在了最优解的第二页（这已经很慢了）~~



------------
```cpp
#include<bits/stdc++.h>
#define FOR(i,j,k)  for(int i=(j);i<=(k);i++)
using namespace std;
int t;
int n,m;
int g[51][51];//网格
bool flag;
int who;
int main()
{
	scanf("%d",&t);
	while(t--)//t组数据
	{
		who=0;//who为奇数Asnish下，偶数vivek下 
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",&g[i][j]);//读入网格
		while(true)//重复直到一方下不了
		{
			who++;//更新当前下棋人
			flag=true;//默认当前选手失败，要不然TLE（https://www.luogu.com.cn/record/34359057）
			for(int i=1;i<=n;i++)//暴力枚举所有点
			{
				for(int j=1;j<=m;j++)
				{
					if(g[i][j]!=1)//当前点为0
					{
						flag=false;//有希望
						for(int x=1;x<=n;x++)//枚举竖排
							if(g[x][j]==1)//有1
							{
								flag=true;
								break;
							}
						if(flag)	continue;//不行，跳过
						for(int y=1;y<=m;y++)//枚举横排
							if(g[i][y]==1)
							{
								flag=true;
								break;
							}
						if(flag)	continue;//不行，跳过
						g[i][j]=1;//不行的都跳过了，剩下的就是可以下的
					}
					if(flag==false)	break;//已经下了就退出
				}
				if(flag==false)	break;//同上
			}
			if(flag)//如果下不了
			{
				if(who%2==1)//Ashish下不了
					printf("Vivek\n");
				else//Vivek下不了
					printf("Ashish\n");
					break;
			}	
		}
	}
	return 0;
}
```


------------

❀完结撒花❀

---

## 作者：sycqwq (赞：1)

这不就是著名的八皇后问题吗

数据范围蛮小的，直接暴力枚举

看棋盘上能摆几个最后判断奇偶性

代码：

```cpp
#include<bits/stdc++.h>
#define inf 2147283647
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n,m,h[55]={0},l[55]={0};
        cin>>n>>m;
        int a[55][55];
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                cin>>a[i][j];
                if(a[i][j]==1)//宣布占领行和列
                {
                    h[i]=1;
                    l[j]=1;
                }
            }
        int t=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                if(h[i]!=1&&l[j]!=1)//寻找还可以摆几个
                {
                    ++t;h[i]=1;l[j]=1;
                }
            }
        // cout<<t<<endl;
        if(t%2==0)//判断奇偶性
            puts("Vivek");
        else
            puts("Ashish");
    }
    return 0;
}
```

---

## 作者：MithrilSword_XIV (赞：0)

## 思路

把整个图 $a_{i,j}$ 都遍历一遍。

如果 $a_{i,j}$ 是 $0$：

- 遍历 $a_{i,j}$ 所在的行，有 $1$ 就 `break`。
- 遍历 $a_{i,j}$ 所在的列，有 $1$ 就 `break`。

如果行和列都没有 $1$，就将 $a_{i,j}$ 变为 $1$。


若遍历到最后也无法将任意一个 $a_{i,j}$ 变为 $1$，那就看这是谁的回合，谁失败了，输出另一个人即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T;
bool people;//判断是谁的回合，1为Ashish的回合，0为Vivek的回合
bool b,a[55][55];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		people=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				cin>>a[i][j];
			}
		}
		while(1){//一直循环直到无法再下
			people=!people;
			b=0;
			for(int i=1;i<=n;i++){//遍历整个图
				for(int j=1;j<=m;j++){
					if(!a[i][j]){//a[i][j]是0
						b=1;
						for(int k=1;k<=n;k++){//遍历行
							if(a[k][j]){//有1就break
								b=0;
								break;
							}
						}
						for(int l=1;l<=m;l++){//遍历列
							if(a[i][l]){//有1就break
								b=0;
								break;
							}
						}
						if(!b){
							continue;
						}
						a[i][j]=1;//如果行和列都没有1，就将a[i][j]变为1
					}
					if(b){
						break;
					}
				}
				if(b){
					break;
				}
			}
			if(!b){//无法再下
				if(people){//是Ashish的回合，Ashish失败
					cout<<"Vivek"<<'\n';
				}else{//是Vivek的回合，Vivek失败
					cout<<"Ashish"<<'\n';
				}
				break;
			}
		}
	}
	return 0;
}

```

---

## 作者：Liu_Tianze (赞：0)

# P2536 CF1365A Matrix Game 题解

[**题目链接**](https://www.luogu.com.cn/problem/CF1365A)

推荐跳转至[**我的博客**](https://www.luogu.com.cn/blog/Liu-Tianze/CF1365A)进行阅读

### 题目分析

本题很明显就是一道模拟题，由于数据很小，可以很暴力的完成。

观察题目我们可以发现，每一次放置 $1$ 位置所在的行和列的 $1$ 的数量都为零。因此我们可以统计所有行及列上的 $1$ 数量。

最后统计出所有 $1$ 的数量都为零的行和列，由于两两对应，所以取两个数量中的最小值即可，这就是可以放置 $1$ 的数量。

本题中需要注意的问题有：

- 有多组数据，因此需要保证统计所使用的数组及变量均进行初始化

- 最后放置的玩家获胜

### 代码

```cpp
#include <iostream>
#include <cstring>
#define maxn 55
using namespace std;

int x[maxn],y[maxn];

int main(){
	int T;
	cin>>T;
	while(T--){
		memset(x,0,sizeof(x));
		memset(y,0,sizeof(y));
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int c;
				cin>>c;
				if(c==1) x[i]++,y[j]++;
			}
		}
		int cnt1=0,cnt2=0;
		for(int i=1;i<=n;i++){
			if(x[i]==0) cnt1++;
		}
		for(int i=1;i<=m;i++){
			if(y[i]==0) cnt2++;
		}
		int move=min(cnt1,cnt2);
		if(move%2==0) cout<<"Vivek"<<endl;
		else cout<<"Ashish"<<endl;	
	}
	return 0;
}

```


---

## 作者：njy0511_flydream (赞：0)


## [题目](https://www.luogu.com.cn/problem/CF1365A)思路：
八皇后变种 ( $n$ 车问题)

设 $a$ 和 $b$ 分别为空闲行数和空闲列数,落下一颗棋子后肯定会占一个空闲行和一个空闲列,那么 $\min(a,b)$ 为奇数时 Ashish 赢，为偶数时 Vivek 赢。

## 自造样例解释：

#### 输入：
```
1
3 4
1 0 0 0
0 0 1 0
0 0 0 0

```
#### 输出：
```
Ashish
```

###### ![如图](https://cdn.luogu.com.cn/upload/image_hosting/h917df5g.png)~~（有点丑）~~

蓝色线是已被占的， Ashish 只要在两个红色 $0$ 中任选一个就赢了。
## [暴力代码](https://www.luogu.com.cn/record/87158437)：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[60][60];
int main (){
//	freopen (".in","r",stdin);
//	freopen (".out","w",stdout);
	int t;
	scanf ("%d",&t);
	while (t--){
		int n,m;
		scanf ("%d%d",&n,&m);
		for (int i=1;i<=n;++i)
			for (int j=1;j<=m;++j)
				scanf ("%d",&a[i][j]);
		int jsa=0,jsb=0;
		for (int i=1;i<=n;++i){
			int pd=0;
			for (int j=1;j<=m;++j)
				pd=pd || a[i][j];
			if (pd==0)
				jsa++;
		}
		for (int i=1;i<=m;++i){
			int pd=0;
			for (int j=1;j<=n;++j)
				pd=pd || a[j][i];
			if (pd==0)
				jsb++;
		}
		if (min(jsa,jsb)%2)
			printf ("Ashish\n");
		else
			printf ("Vivek\n");
	}
	return 0;
}
```
## ~~[博客](https://www.luogu.com.cn/blog/njy/)~~

---

## 作者：Keroshi (赞：0)

# 题目分析

题目要求无处可放的人为败者，就是求可以设置数字的个数 
不妨用两个数组记录被占用的行与列，以最后一个样例为例，
先将有数字的行和列标记被占用：
![](https://cdn.luogu.com.cn/upload/image_hosting/elakbyp4.png)    
再在没被占用过的格子里去放数字，然后不断更新，
直到格子全被占用。 由于操作是不可逆的，所以直接遍历即可。

# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=55;
//记录被占用的行和列 
int row[N],col[N];
int T,n,m;
int main(){
    scanf("%d",&T);
    while(T--){
        // 数组清空 
        memset(row,0,sizeof(row));
        memset(col,0,sizeof(col));
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                int a;
                scanf("%d",&a);
                // 记录被占用 
                if(a) {
                    row[i]=1;
                    col[j]=1;
                }
            }
        }
        int cnt=0;
        //记录操作的次数 
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                // 没被占用 
                if(!row[i]&&!col[j]){
                    cnt++;
                    // 更新数组 
                    row[i]=1;
                    col[j]=1;
                } 
            }
        }
        // 三目运算符输出
        cout << (cnt%2?"Ashish":"Vivek") << endl;
    }
    return 0;
}
```

---

## 作者：Ba_creeper (赞：0)

#### 题目分析

如果当前玩家想要在网格图上找一个位置设置为 $1$，条件式这一个位置所在的行以及列上都没有其它的 $1$。

观察到数据范围只有 $1 \leq n,m \leq 50 $，我们可以考虑直接在网格图上操作。

在读入的时候，只要读入到当前位置的数为 $1$，我们可以在网格图上将该行和该列上的所有数都标记为 $1$。

之后我们可以模拟玩家操作的过程，记录下当前回合谁在操作。每次遍历一遍网格图，如果发现网格图中有 $0$，就把这个位置变为 $1$，并且将该行和该列上的每一个数都变为 $1$。

以此不断循环，直到遍历网格图时没有 $0$，就说明一个玩家要输了，此时输出当前不是谁在操作即可。

#### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

ll n, T, m;
bool a[100][100], ok = 0;

void change(ll x, ll y){ 
    for (int i = 1; i <= n; ++i) a[i][y] = 1;
    for (int j = 1; j <= m; ++j) a[x][j] = 1;
} //将该位置的每一行和每一列都该为1

void CLEAR(){ 
    ok = 0;
    memset(a, 0, sizeof a);
} //初始化

int main()
{
    T = read();
    while (T--)
    {
        CLEAR(); //初始化
        n = read(), m = read();
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                bool x;
                cin >> x;
                if (x == 1)
                    change(i, j); //修改
            }
        }

        while (1)
        {
            bool f = 0; //为遍历表之后没有找到0而弹出做准备
            for (int i = 1; i <= n; ++i){
                for (int j = 1; j <= m; ++j){
                    if (a[i][j] == 0){
                        change(i, j);
                        if (ok == 0) ok = 1; //更换谁在操作
                        else ok = 0; //更换谁在操作
                        f = 1; //代表找到了0
                        break;
                    }
                }
                if (f == 1)
                    break;
            }
            if (f == 0){ //表里全是1，输出答案
                if (ok == 0) puts("Vivek");
                else puts("Ashish");
                break;
            }
        }
    }
    return 0;
}
```

---

