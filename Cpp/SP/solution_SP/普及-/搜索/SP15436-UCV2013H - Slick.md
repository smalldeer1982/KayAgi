# UCV2013H - Slick

## 题目描述

一片大小为 $n\times m$ 的海面发生了石油泄漏，石油表示为 $1$，海水表示为 $0$。

求石油组成的连通块总数，以及每种面积连通块的个数。

**本题多测**

## 样例 #1

### 输入

```
10 10
1 1 1 1 1 1 1 1 1 1
1 1 1 1 0 0 0 0 0 0
1 1 1 0 0 0 0 1 1 1
1 1 0 0 1 0 0 1 1 1
1 0 1 0 0 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1 1
0 0```

### 输出

```
7
1 2
2 1
6 1
10 2
20 1```

# 题解

## 作者：lzxhdxx (赞：5)

# 题解SP15436
这一题已经有两位大佬写过bfs题解了，但是讲的都不详细，蒟蒻的我写一篇我自己能看懂的题解

### 题意简述：
输入n,m，输入一副大小为n*m的图，找出这幅图内所有由1构成的连通块并记录面积，输出他们的个数，并输出每个面积所对应的连通块的数量

### 思路：
找连通块，我选的是宽搜（当然，深搜也可以），我们输入图后应该再遍历一遍图，找到1就宽搜一遍并把总数+1，把搜到的1全都标记为0避免多次宽搜，每搜到一个1就把area（面积）+1，搜完一个联通块就把ans[area]+1，最后输出总数后遍历ans，如果ans[i]!=0，那就输出i和ans[i]

# Code：
```cpp
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, m, a[300][300], ans[90010], dx[5] = { 0,-1,1,0,0 }, dy[5] = { 0,0,0,-1,1 }, cnt = 0;//dx,dy,控制四个方向

int bfs(int x, int y)
{
	int area = 1;//起始点也算面积
	queue<pair<int, int> >Q;//两个int分别存储当前x,y坐标
	Q.push(make_pair(x, y));//压入起始点
	while (!Q.empty())//队列空说明无处可搜，退出
	{
		int nowx = Q.front().first, nowy = Q.front().second;//当前点
		a[nowx][nowy] = 0;//当前点搜过，标记为0，不重复搜
		for (int i = 1; i <= 4; i++)//分别尝试4个方向
		{
			int newx = nowx + dx[i], newy = nowy + dy[i];//扩展出的新点
			if (newx >= 1 && newy >= 1 && newx <= n && newy <= m && a[newx][newy] == 1)
			{//不越界而且没有遍历过就搜一遍
				Q.push(make_pair(newx, newy));//压入新点
				a[newx][newy] = 0, area++;//新点标记为0，此联通块面积+1
			}
		}
		Q.pop();//处理完了，弹队列
	}
	return area;//联通块面积
}

int main()
{
	while (cin >> n >> m && n&& m)
	{
		memset(ans, 0, sizeof(ans));
		memset(a, 0, sizeof(a));//初始化
		cnt = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				cin >> a[i][j];//输入
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				if (a[i][j])//遍历到1就宽搜一遍当前联通块
					ans[bfs(i, j)]++, cnt++;
		cout << cnt << endl;//联通块总数
		for (int i = 1; i <= 90000; i++)//分别输出每个面积所对应的联通块个数
			if (ans[i])
				cout << i << " " << ans[i] << endl;
	}
	return 0;
}
```
感谢各位阅读！感谢管理大大审核！

拒绝代码复制，创造和谐洛谷！

---

## 作者：Lion_Li (赞：2)

#### 这个黑题是假的  ~~不过请保持住~~
类似于细胞，不过连续输入要每次都初始化一次~~不然一定会WA~~

记录大小几个可以用类似桶排的方法，定义很大的数组（62500），刷油的时候计算大小，最后数组++
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int map[251][251],m,n,ans,a,b,num[62501],k;
int dx[4]= {-1,0,1,0};
int dy[4]= {0,1,0,-1};
void bfs(int x,int y) {//其实是dfs
	for (int i=0; i<4; i++)
		if((x+dx[i]>=0)&&(x+dx[i]<m)&&(y+dy[i]>=0)&&(y+dy[i]<n)&&(map[x+dx[i]][y+dy[i]])) {
			map[x+dx[i]][y+dy[i]]=0;
			k++;
			bfs(x+dx[i],y+dy[i]);
		}
}
int main() {
	while(cin>>n>>m&&n!=0&&m!=0) {
		ans=0;
		memset(map,0,sizeof(map));//一定要加
		memset(num,0,sizeof(num));
		for(int i=0; i<m; i++)
			for(int j=0; j<n; j++) {
				cin>>map[i][j];
			}
		for(int i=0; i<m; i++)
			for(int j=0; j<n; j++)
				if(map[i][j]) {
					map[i][j]=0;
					bfs(i,j);
					ans++;
					num[k]++;//当前大小的计数器++
					k=0;
				}
		cout<<ans<<endl;
		for(int i=0;i<=62500;i++)if(num[i]!=0)cout<<i+1<<' '<<num[i]<<endl;
	}
}
```

---

## 作者：zhenglier (赞：1)

这一题是非常简单的BFS，对于每一组数据，扫描每一个点，若当前一个点没访问过且当前点有油，则对当前点跑一边BFS，记录块的大小，直接加到一个开了90000的数组中（因为就算所有点都是油，最大也只会有90000的大小）。最后直接扫一遍这个数组，把所有有值的大小输出就行了。

# 注意，每一遍处理完要初始化一遍

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans[90010];
bool v[300][300],mp[300][300];
const int dx[]={0,1,0,-1,0};
const int dy[]={0,0,1,0,-1};
int main()
{
	cin>>n>>m;
	while(n!=0||m!=0){
		memset(v,0,sizeof(v));
		memset(ans,0,sizeof(ans));
		int sum=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				scanf("%d",&mp[i][j]);
			}
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=m;++j){
				if(v[i][j])continue;
				if(!mp[i][j])continue;
				queue<pair<int,int> >q;int as=0;
				q.push(make_pair(i,j));
				v[i][j]=1;
				while(!q.empty()){
					int x=q.front().first,y=q.front().second;q.pop();as++;
					for(int i=1;i<=4;++i){
						int nx=x+dx[i],ny=y+dy[i];
						if(v[nx][ny]||nx>n||nx<1||ny>m||ny<1||!mp[nx][ny])continue;
					    v[nx][ny]=1;
						q.push(make_pair(nx,ny));
					}
				}
				ans[as]++;
				sum++;
			}
		}
		printf("%d\n",sum);
		for(int i=1;i<=n*m;++i)
		    if(ans[i])printf("%d %d\n",i,ans[i]);
		scanf("%d%d",&n,&m);
	}
}
```

---

## 作者：漫雨轻飘 (赞：0)

### 哈哈第一次AC黑题（（虽然这道黑题是假的
# 难度被改回普及-了QAQ不开心
这道题就是一个简单的BFS，直接套上BFS模板，然后加上一个用来存储每个大小的油块出现的次数的数组，，最后输出，就AC了

```
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 300;
int count1 = 0;
int A[62600]; //用来记录最后每一种大小的块有多少
struct node
{
    int x, y;
} Node;
int n, m; //矩阵的大小为n*m
int matrix[300][maxn] = {0};
bool inq[maxn][maxn] = {false};
int X[4] = {0, 0, 1, -1};
int Y[4] = {1, -1, 0, 0};

bool judge(int x, int y)
{
    if (x > n || x <= 0 || y > m || y <= 0)
    {
        // printf("当前在judge函数里面，x = %d, y = %d,超过边界，返回false。\n\n", x, y);
        return false; //如果超过了边界返回false
    }
    if (inq[x][y] == true)
    {
        //printf("当前在judge函数里面，x = %d, y = %d,当前元素已经进入过队列，返回false。\n\n", x, y);
        return false; //如果当前元素是0或者当前元素已经进入过队列，返回false
    }
    if (matrix[x][y] == 0)
    {
        // printf("当前在judge函数里面，x = %d,y = %d,当前元素为0，返回false\n\n", x, y);
        return false;
    }
    else
    {
        //  printf("当前在judge函数里面，x = %d, y = %d,当前坐标的元素没有超出边界，也没有进入过队列，返回true。\n\n", x, y);
        return true;
    }
}

void BFS(int x, int y)
{
    queue<node> Q; //定义一个结构体队列，里面的x,y储存当前数字的坐标
    Node.x = x;
    Node.y = y; //当前结点的坐标是（x,y）
    Q.push(Node);
    // printf("当前在BFS函数中，现在将x = %d, y = %d 的元素压入队列中\n\n", x, y);
    //循环4次，得到4个相邻位置
    inq[x][y] = true;
    int ans = 0;
    while (!Q.empty())
    {
        node top = Q.front(); //取出队首元素，放在top中间
        ans++;                //   printf("当前队首元素出列，其元素为 x = %d,y = %d\n\n", top.x, top.y);
        Q.pop();              //队首元素出列
        for (int i = 0; i < 4; i++)
        {
            int newX = top.x + X[i];
            int newY = top.y + Y[i];
            if (judge(newX, newY))
            {
                //如果当前的元素需要访问(未进过队列)
                Node.x = newX;
                Node.y = newY;
                Q.push(Node);           //将当前元素压入队列
                inq[newX][newY] = true; //将当前元素是否已经进入队列标记为真
                                        //  cout << "当前坐标为x: " << newX << "y: " << newY << "的点被压入队列并被标记为已进入过队列" << endl
                                        //    << endl;
            }
        }
    }
    A[count1++] = ans;
}

void init()
{
    memset(inq, 0, sizeof(inq));
    memset(A, 0, sizeof(A));
    memset(matrix, 0, sizeof(matrix));
    count1 = 0;
}

int main()
{

    while (scanf("%d%d", &n, &m), (m + n))
    {
        init();
        for (int y = n; y > 0; y--)
        {
            for (int x = 1; x <= m; x++) //用两层循环记录每个元素
            {
                scanf("%d", &matrix[x][y]);
            }
        }
        int ans = 0; //存放当前的块数
        for (int y = 1; y <= n; y++)
        {
            for (int x = 1; x <= m; x++)
            {
                if (matrix[x][y] == 1 && inq[x][y] == false)
                {
                    //如果找到的这个元素为1，而且并没有入过对（并没有被标记为false）
                    ans++;
                    //  printf("发现新的块,ans+1，当前ans = %d\n\n", ans);
                    //  printf("将在下一句进入BFS函数，当前x = %d,y = %d\n\n", x, y);
                    BFS(x, y);
                }
            }
        }
        cout << ans << endl; //system("pause");
        sort(A, A + count1);
        int now = 0;
        while (now < count1)
        {
            int count2 = 1;
            while (now < count1)
            {
                if (A[now] == A[now + 1])
                {
                    count2++;
                    now++;
                }
                else
                    break;
            }
            now++;
            printf("%d %d\n", A[now - 1], count2);
        }
    }
    return 0;
}

```
我也是A过黑题的人啦（得意忘形.jpg


---

