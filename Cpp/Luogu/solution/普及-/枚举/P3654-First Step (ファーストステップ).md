# First Step (ファーストステップ)

## 题目背景

> **知らないことばかりなにもかもが（どうしたらいいの？）**    
**一切的一切 尽是充满了未知数（该如何是好）**   
**それでも期待で足が軽いよ（ジャンプだ！）**     
**但我仍因满怀期待而步伐轻盈（起跳吧！）**       
**温度差なんていつか消しちゃえってね**     
**冷若冰霜的态度 有朝一日将会消失得无影无踪**      
**元気だよ元気をだしていくよ**     
**拿出活力 打起精神向前迈进吧**     

 ![](https://cdn.luogu.com.cn/upload/pic/4471.png) 

我们 Aqours，要第一次举办演唱会啦！

虽然学生会长看上去不怎么支持我们的样子，可是有了理事长的支持，我们还是被允许在校内的篮球场里歌唱！

歌曲也好好地准备过了，名字叫“[最喜欢的话就没问题！ (ダイスキだったらダイジョウブ！)](https://zh.moegirl.org/%E6%9C%80%E5%96%9C%E6%AC%A2%E7%9A%84%E8%AF%9D%E5%B0%B1%E6%B2%A1%E9%97%AE%E9%A2%98)“，大家一定会喜欢的吧！

演唱会一定会顺利进行的！

希望不要发生**停电**什么的事故哦……！


## 题目描述

可是……这个篮球场，好像很久没有使用过的样子啊……

里面堆满了学校的各种杂物呢……

我们 Aqours 的成员要怎么在里面列队站下呢？


我们浦之星女子学院的篮球场是一个 $R$ 行 $C$ 列的矩阵，其中堆满了各种学校的杂物 (用 `#` 表示)，空地 (用 `.` 表示) 好像并不多的样子呢……

我们 Aqours 现在已经一共有 $K$ 个队员了，要歌唱舞蹈起来的话，我们得排成一条 $1\times K$ 的直线，一个接一个地站在篮球场的空地上呢 (横竖均可)。

我们想知道一共有多少种可行的站位方式呢。

Aqours 的真正的粉丝的你，能帮我们算算吗？


## 说明/提示

|  | $R$ | $C$ | $K$ | 备注 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
|$1\sim2$|$\leq 10$|$\leq 10$|$\leq \min(R,C)$|无|
|$3\sim4$|$\leq 100$|$\leq 100$|$\leq 1$|无|
|$5\sim6$|$\leq 100$|$\leq 100$|$\leq \min(R,C)$|没有障碍|
|$7\sim10$|$\leq 100$|$\leq 100$|$\leq \min(R,C)$|无|

对于所有数据，$1 \leq R,C \leq 100$，$1 \leq k \leq \min(R,C)$。

#### 以下是彩蛋

在 LoveLive!Sunshine!! 动画第一季第三集中，Aqours 队长高海千歌演唱“最喜欢的话就没问题！”到副歌前时，学校因为雷击停电。


## 样例 #1

### 输入

```
5 5 2
.###.
##.#.
..#..
#..#.
#.###
```

### 输出

```
8```

# 题解

## 作者：rashoumon (赞：95)

本题遍历每一个可以站人的点，然后利用dfs的思路判断每一个点向下和向右是否能满足条件；但是r=1时需要特判，因为r=1意味着向下和向右重复计算，需要除以2。
```cpp
#include <iostream>
using namespace std;
int n,m,r,ans,dx[2]={0,1},dy[2]={1,0};//位移向量，分别是朝下和朝右
char map[105][105];
void skim(int x,int y,int i,int j)//dfs
{
    if(j>r){//满足条件则ans++
        ++ans;
        return ;
    }
    if(map[x][y]!='.'||x<0||y<0||x>=n||y>=m)//处理越界和障碍
        return ;
    skim(x+dx[i],y+dy[i],i,j+1);
    return ;
}
int main()
{
    cin>>n>>m>>r;
    for(int i=0;i<n;i++)
        cin>>map[i];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(map[i][j]=='.')
                for(int k=0;k<2;k++)
                    skim(i,j,k,1);
    if(r==1)
        ans/=2;//r=1时特判
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：lin_toto (赞：81)

# 洛谷三月月赛R1·官方题解 T2


#### 本题标程请见题目页面下方的标程部分。


### 1. 解析

本题只需按照每行分别扫描所有连续的空位，判断连续的一段空位长度是否超过k，如果超过k，则在这段上一共有l-k+1种摆放方式（其中l是长度）。

然后再按照每列扫描一遍，做同样的事情。

需要注意k=1的时候，横着站竖着站一样，所以统计的结果还要除以2。


### 2. 出题事故

首先没有卡掉O(n^3)的算法。事实上这个之前本人跟出题组提过，不过并没有被重视。也是沟通上的问题。

再来k=1的情况出数据的人本身也没有考虑到特殊情况，本人在写std的时候也忘记了这一茬。结果比赛开始大约1小时才被指出，然后临时修改重测。

因为评测机实现上的一些问题，这一重测又导致了大规模的评测故障，所以本题的分数直到这篇题解发布的时候还不能完全确定。


#### 本题标程请见题目页面下方的标程部分。


---

## 作者：鸿飞 (赞：43)

**这是一道简单的暴力枚举题。**
## Part1:题目
	输入r、c和k,输入一个r*c的字符矩阵,输出其中可供k人
	排成1列站立的空地数。

------------

## Part2:思路
	从每一个点开始,横向和竖向搜索k位,如果其中没有任何
   	障碍的话就让答案加一。
    
------------

## Part3:注意事项
	当k=1时,横向和竖向是一样的,相当于计算了两次。所以
    需要特判并输出答案/2。
    
------------
## Part4:代码
```cpp
#include<iostream>
using namespace std;
char a[105][105];//地图
long long r,c,k;
long long ans=0;//输出
int main()
{
	cin >> r >> c >> k ;
	for(int i=1;i<=r;i++)
	{
		for(int j=1;j<=c;j++)
		{
			cin >> a[i][j] ;
		}
	}
	bool f=true;
	for(int i=1;i<=r;i++)//横向搜索
	{
		for(int j=1;j<=c;j++)
		{
			f=true;
			for(int s=0;s<k;s++)
			{
				if(a[i+s][j]!='.')
				{
					f=false;
					break;
				}
			}
			if(f==true)
			{
				ans++;
			}
		}
	}
	for(int i=1;i<=r;i++)//纵向搜索
	{
		for(int j=1;j<=c;j++)
		{
			f=true;
			for(int s=0;s<k;s++)
			{
				if(a[i][j+s]!='.')
				{
					f=false;
					break;
				}
			}
			if(f==true)
			{
				ans++;
			}
		}
	}
	if(k==1)//特判
	{
		cout << ans/2 ;
	}else
  	{
  		cout << ans ;
  	}
    return 0;
}

```



---

## 作者：Blue_wonders (赞：36)

## 我看这个题没人来用dfs，我来交一遍
~~(其实这个dfs只有搜索，没有回溯)~~
### 搜索，使用dfs分两个方向（附有详解）
#### 这道题有一个坑
- 这道题k=1时输出要减半（因为搜索会搜索两遍）80分WA 4,5两个点的可以注意下
#### 代码思路
- 先输入成一个二维数组（能走设成1，就不用判断边界了）
- 每一个点都dfs扫一遍（分别向下和向右找）
- 如果dfs次数等于k那么就记录+1
- 输出 
#### 代码
[AC详情](https://www.luogu.org/recordnew/show/16874801)
```cpp
#include<bits/stdc++.h>
using namespace std;
int r,c,k,ans=0,q;
int s[101][101];
void right(int i,int j,int r){//x坐标，y坐标，循环次数 
	if(r==k){//如果循环次数和k相等 
	    ans++;//答案++ 
	    return;//结束搜索 
	}
	if(s[i][j+1]==1)right(i,j+1,r+1);//如果向右是空的，那么可以循环，次数++； 
}
void under(int i,int j,int r){//与上边相同，只是改了改方向 
	if(r==k){
	    ans++;
	    return;
	}
	if(s[i+1][j]==1)under(i+1,j,r+1);
}
int main(){
	cin>>r>>c>>k;//输入 
	char a[2];
	for(int i=1;i<=r;i++){//输入(进行判断，如果是杂物就放0，可以站就是1) 
	    for(int j=1;j<=c;j++){
	        cin>>a[1];
	        if(a[1]=='#')s[i][j]=0;
	        else s[i][j]=1;
	    }
	}
	for(int i=1;i<=r;i++){ //对于每一个点都扫一遍 
	    for(int j=1;j<=c;j++){
	        if(s[i][j]==1){
	            right(i,j,1);//向右进行搜索
	            under(i,j,1);//向下进行搜索 
	        }
	    }
	}
	if(k==1)cout<<ans/2;//特判，如果是1的话，向右，向下都扫了一遍，一共是两遍，所以除以2 
	else cout<<ans;//记着加else，否则k==1时会输出两个结果 
	return 0;
} 
```
感谢大家能看我的题解！~

---

## 作者：天亮就睡觉 (赞：8)

这道题我最开始想到的是深搜求联通块，枚举每个空地作为起点，向四个方向搜索，只要长度符合并且没有越界总数加一，搜索后将这个起点置为障碍。
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

struct Coordinate{
    int row;
    int col;
};
Coordinate mov_dir[4] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
int R, C, K, cnt;
string maze[100];

void dfs(int row, int col, int dir, int len)
{
    if (row < 0 || row >= R || col < 0 || col >= C || maze[row][col] == '#') {
        return;
    }
    if (len == K) {
        cnt++;
        return;
    }
    dfs(row + mov_dir[dir].row, col + mov_dir[dir].col, dir, len + 1);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> R >> C >> K;
    for (int i = 0; i < R; i++) {
        cin >> maze[i];
    }
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (maze[i][j] == '.') {
                dfs(i, j, 0, 1);
                dfs(i, j, 1, 1);
                dfs(i, j, 2, 1);
                dfs(i, j, 3, 1);
                maze[i][j] = '#';
            }
        }
    }
    if (K == 1) {
        cnt /= 4;
    }
    cout << cnt << endl;
    return 0;
}
```


---

## 作者：十七 (赞：7)

wa了好几次就是因为没有考虑K=1 的情况  -_-//
```cpp
#include<iostream>
using namespace std;
int main() 
{
	int R,C,K,sum=0;
	char a[501][501];
	cin>>R>>C>>K;
	for(int i=0;i<R;i++)
	  for(int j=0;j<C;j++)
	     cin>>a[i][j];
	 //行查找  
	for(int i=0;i<R;i++)
	{
		for(int j=0;j<C;j++)
		{    
		   int n=0; 
			for(int k=j;k<j+K;k++)
			{
			if(a[i][k]=='.')
			n++;	
			}
			if(n==K)
			sum++;
		}
	 } 
	 //列查找 
	 for(int i=0;i<C;i++)
	{
		for(int j=0;j<R;j++)
		{    
		   int n=0; 
			for(int k=j;k<j+K;k++)
			{
			if(a[k][i]=='.')
			n++;	
			}
			if(n==K)
			sum++;
		}
	 } 
	 if(K=1)
	 sum/=2;
	 cout<<sum<<endl;
	 return 0;
}
```

---

## 作者：GoldenFishX (赞：5)

~~本蒟蒻第一次写题解，求通过。~~

我的思路与深搜有点像，几乎是纯暴力。
# 注意

### 这道题如果用4个方向写的话，那么一种站法就会算两次。
### 所以要用2个方向写，比如“下”和“右”
### 其实也可以用“上”和“左”
# 但一定不能用“上”和“下”或“左”和“右”！


-----------------------我是分割线------------------------

## 主要思路
#### 先找到一个空位，然后以空位为中心，看下“下”和“右”有没有连续k个空位，如果有，就ans++，然后就继续找空位，直到找完为止。

废话不多说，直接上代码（不懂的看注释）
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int r,c,k,i,j,i1,j1,fx[2]={0,1},fy[2]={1,0};//r行 c列 k人
	int nx,ny,ans=0; 
	char a[101][101];//场地a 
	cin>>r>>c>>k;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			cin>>a[i][j];
		}
	}
	if(k==1)//只有一个人的时候单独处理
	{
		for(i=0;i<r;i++)
		{
			for(j=0;j<c;j++)
			{
				if(a[i][j]=='.')
					ans++;
			}
		}
		cout<<ans;
		return 0;
	}
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			if(a[i][j]=='.')//如果发现一个空位，就看看旁边有没有其他空位
			{
				for(i1=0;i1<2;i1++)
				{
					nx=i+fx[i1];
					ny=j+fy[i1];
					for(j1=1;j1<k;j1++)//j1=1是因为前面已经找到了一个空位，只需要再多找k-1就好了
					{
						if(a[nx][ny]!='.')
						{
							break;
						}
						if(j1==k-1)//如果用连续k个空位，ans++
						{
							ans++;
						}
						nx=nx+fx[i1];
						ny=ny+fy[i1];
					}
				}
			}
		}
	}
	cout<<ans;
	return 0;
} 
```


---

## 作者：_Clown_ (赞：2)

~~蒟蒻又来发题解了...~~

这道题目，我们可以用暴力枚举解决。

首先，我们要枚举1*k矩阵的起点。

其次，我们需要判断两种情况：横着，竖着。

有一种特殊情况，即k=1时，横着竖着都一样，这只能算一种情况。

没看懂的不妨看看代码中的注释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int Line,Column,Should;
char Map[101][101];
int main()
{
	register int i,j,k;
	cin>>Line>>Column>>Should;//输入行、列、k
	for(i=1;i<=Line;i++)
	{
		for(j=1;j<=Column;j++)
		{
			cin>>Map[i][j];//扫描地图
		}
	}
	register int Sum=0;
	for(i=1;i<=Line;i++)//枚举起点的横坐标
	{
		for(j=1;j<=Column;j++)//枚举起点的纵坐标
		{
			bool Flag=true;//假设有解
			for(k=0;k<Should;k++)//横着看
			{
				register int Now;
				Now=i+k;
				if(Map[Now][j]=='#'||Now>Line)//如果越界或是撞墙，那么不行
				{
					Flag=false;
					break;
				}
			}
			if(Flag)
			{
				Sum++;
			}
			Flag=true;
			for(k=0;k<Should;k++)//竖着看
			{
				register int Now;
				Now=j+k;
				if(Map[i][Now]=='#'||Now>Column)//如果越界或是撞墙，那么不行
				{
					Flag=false;
					break;
				}
			}
			if(Flag&&Should!=1)//当K=1时，两种情况仅算一种
			{
				Sum++;
			}
		}
	}
	cout<<Sum<<endl;
	return 0;
}
```

---

## 作者：G_S_Z (赞：2)

本体的思路大致为（~~emm，别人的题解都有，就不多说了~~）放代码！


------------
```
#include<iostream>
using namespace std;
int ty[102][102],tz[102][102];
int main(){
	char a[102][102];
	int r,c,k,w[102],e=0,ans=0;
	cin>>r>>c>>k;
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			cin>>a[i][j];
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if(a[i][j]=='.'){
				ty[i][j]=1;
				for(int q=j+1;q<c;q++){
					if(a[i][q]=='.'){
						ty[i][j]++;
					}
					else{
						break;
					}
				}
			}
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if(a[i][j]=='.'){
				tz[i][j]=1;
				for(int q=i+1;q<r;q++){
					if(a[q][j]=='.'){
						tz[i][j]++;
					}
					else{
						break;
					}
				}
			}
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if(ty[i][j]>=k){
				ans++;
			}
			if(tz[i][j]>=k){
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
} 
```

------------
这个地方是个坑，别忘了k可能等于一（于是就wa了两个点qwq）
------------


```cpp
#include<iostream>
using namespace std;
int ty[102][102],tz[102][102];
int main(){
	char a[102][102];
	int r,c,k,w[102],e=0,ans=0;
	cin>>r>>c>>k;
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			cin>>a[i][j];
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if(a[i][j]=='.'){
				ty[i][j]=1;
				for(int q=j+1;q<c;q++){
					if(a[i][q]=='.'){
						ty[i][j]++;
					}
					else{
						break;
					}
				}
			}
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if(a[i][j]=='.'){
				tz[i][j]=1;
				for(int q=i+1;q<r;q++){
					if(a[q][j]=='.'){
						tz[i][j]++;
					}
					else{
						break;
					}
				}
			}
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if(ty[i][j]>=k){
				ans++;
			}
			if(tz[i][j]>=k){
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
} 
```


---

## 作者：loi_hjh (赞：2)

这道题数据不大可以用n^3来枚举，这里蒟蒻介绍一下n^2的做法 

# 附上代码：

```cpp
#include<map>
#include<list>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define in inline
#define ri register int
using namespace std;
int n,m,p,q,ans;//场地大小，人数，连续有几个空位，答案 
char a[1001][1001];
int main(){
	scanf("%d%d%d",&n,&m,&p);
	for(ri i=1;i<=n;i++)
		for(ri j=1;j<=m;j++)
			cin>>a[i][j];
	for(ri i=1;i<=n;i++){//先数每一行连着的空格 
		q=0;
		for(ri j=1;j<=m;j++){
			if(a[i][j]=='.') q++;
			else{
				if(q>=p) ans+=q-p+1;//那么就有q-p+1种方案 
				q=0;
			}
		}
		if(q>=p) ans+=q-p+1;//行末再统计一次 
	}
	for(ri i=1;i<=n;i++){//再数每一列连着的空格（ctrl c+ctrl v再改一下） 
		q=0;
		for(ri j=1;j<=m;j++){
			if(a[j][i]=='.') q++;
			else{
				if(q>=p) ans+=q-p+1;//那么就有q-p+1种方案 
				q=0;
			}
		}
		if(q>=p) ans+=q-p+1;
	}
	if(p==1) ans/=2;//只有一个人的话横竖都一（shi）样（si），特判一下，居然出了两个人数是1的数据卡我20分。。。 
	printf("%d",ans);
	return ~~(0-0);
}


```

---

