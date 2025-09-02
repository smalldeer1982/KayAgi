# [USACO17OPEN] Where's Bessie? S

## 题目描述

Farmer John 一直以精通技术而闻名，他正在测试他的新型无人机搭载的奶牛定位相机。这款相机据说可以拍摄他的田地并自动确定奶牛的位置。不幸的是，相机的算法并不擅长寻找奶牛，因此 Farmer John 需要你的帮助来开发一个更好的算法。

相机拍摄的农场俯视图由一个 $N \times N$ 的字符网格描述，每个字符在 $A \ldots Z$ 范围内，代表 26 种可能的颜色之一。Farmer John 认为，定义潜在奶牛位置（PCL）的最佳方式如下：一个 PCL 是一个矩形子网格（可能是整个图像），其边与图像的边平行，并且不包含在任何其他 PCL 中（因此 PCL 的较小子集不能也是 PCL）。此外，PCL 必须满足以下属性：仅关注矩形内的内容并忽略图像的其余部分，必须恰好存在两种颜色，其中一种颜色形成一个连续区域，另一种颜色形成两个或更多连续区域。

例如，一个矩形的内容如下：

```
AAAAA  
ABABA  
AAABB  
```

这将构成一个 PCL，因为 A 形成一个连续区域，而 B 形成多个连续区域。解释为一只颜色为 A 的奶牛带有颜色为 B 的斑点。

一个区域是“连续的”，如果可以通过向上、向下、向左或向右移动，从一个区域中的单元格反复移动到另一个区域中的单元格来遍历整个区域。

给定 Farmer John 的相机返回的图像，请计算 PCL 的数量。

## 说明/提示

在这个例子中，两个 PCL 分别是内容如下的矩形：

```
ABB  
BBB  
AAB  
ABB
```

和

```
BC  
BC  
BB  
BC  
```

## 样例 #1

### 输入

```
4
ABBC
BBBC
AABB
ABBC```

### 输出

```
2```

# 题解

## 作者：微雨燕双飞 (赞：15)

最近一直在刷老题目，很久没有发过题解了（嘻嘻，还是一如既往地菜）

这是一道较为繁琐的搜索题，难并不在搜索过程，而是在判断“两种颜色一种构成一个连通块，另一种形成两个或两个以上的连通块”和“是否被其它PCL覆盖”这两个过程（也就是模拟）。如果没有很好的处理方法，代码很容易写得十分冗长。我这份代码跑了176ms，比楼下两位的题解快一些，写法稍简洁一些，希望能给大家以帮助。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[4]={0,-1,0,1}; //两个方向数组，dfs/bfs标配
const int dy[4]={-1,0,1,0};
int n,cnt=0,sum[100],ans=0; //ans存储答案
char a[25][25]; //a数组存储矩阵
bool f[100],v[25][25]; //v数组判断是否搜过，f数组用于记录一个PCL内的某种颜色是否出现过
struct pcl
{
  int x1,y1,x2,y2;
}s[50000]; //s数组存储每个PCL的左上角及右下角的横纵坐标
void dfs(int x,int y,int n1,int n2,int m1,int m2)
{ //深搜划分连通块，注意判断越界的标准不再是整个矩阵的1和n了
  for(int i=0; i<4; i++)
  {
    int x1=x+dx[i],y1=y+dy[i];
    if(x1<n1||x1>n2||y1<m1||y1>m2||v[x1][y1]||a[x1][y1]!=a[x][y]) continue;
    v[x1][y1]=true;
    dfs(x1,y1,n1,n2,m1,m2); //递归深搜
  }
}
bool PCL(int u1,int v1,int u2,int v2) //判断当前矩阵是否是PCL
{
  int col=0; char c1,c2; //c1和c2存储矩阵中的两种不同颜色
  memset(f,0,sizeof(f));
  for(int i=u1; i<=u2; i++) //以下统计当前矩阵中的不同颜色的个数
    for(int j=v1; j<=v2; j++)
      if(!f[a[i][j]]) 
      { 
        f[a[i][j]]=true; 
        col++; 
        if(col==1) c1=a[i][j];
        if(col==2) c2=a[i][j];
      }
  if(col!=2) return false; //如果不同颜色数不为2，返回false
  memset(sum,0,sizeof(sum)); //sum数组存储每个颜色的连通块的个数
  memset(v,0,sizeof(v));
  for(int i=u1; i<=u2; i++)
    for(int j=v1; j<=v2; j++)
      if(!v[i][j]) //如果未搜索过
      {
        v[i][j]=true; //标记
        sum[a[i][j]]++; //sum数组++
        dfs(i,j,u1,u2,v1,v2); //深搜
      }
  if((sum[c1]==1&&sum[c2]>=2)||(sum[c1]>=2&&sum[c2]==1)) return true; //若满足条件2则返回true表示当前矩阵是一个PCL
    else return false;
}
bool judge(int x) //去重过程，判断第x个PCL是否被别的PCL所覆盖
{
  for(int i=1; i<=cnt; i++)
  {
    if(i!=x&&s[i].x1<=s[x].x1&&s[i].y1<=s[x].y1&&s[i].x2>=s[x].x2&&s[i].y2>=s[x].y2)
      return false;
  }
  return true;
}
int main()
{
  cin>>n;
  for(int i=1; i<=n; i++) 
    for(int j=1; j<=n; j++) cin>>a[i][j]; //读入矩阵
  for(int i=1; i<=n; i++) //四重循环暴力枚举每个矩阵的左上角和右下角坐标并做判断
    for(int j=1; j<=n; j++)
      for(int k=i; k<=n; k++)
        for(int l=j; l<=n; l++)
          if(PCL(i,j,k,l))
          { //若当前矩阵是PCL则记录下来
            cnt++;
            s[cnt].x1=i; s[cnt].y1=j; s[cnt].x2=k; s[cnt].y2=l;
          }
  for(int i=1; i<=cnt; i++) //完成去重，累计答案
    if(judge(i)) ans++;
  cout<<ans<<endl; //输出
  return 0;
}
```
希望对您有帮助！（话说做USACO月赛题的人好少）

---

## 作者：羚羊WANG (赞：3)

相信大家看到这里的时候已经熟读了题目

我们发现，题目中的重难点就是对$PCL$的理解

我们不难发现，$N \leq 20$

数据范围十分的小

所以我们可以考虑暴力

每次我们枚举的时候，可以枚举四个点，都将以这四个点构成
矩形用深搜的办法判断这一个矩形是不是$PCL$,深搜的思路十
分显然，在这里不做过多阐述

当我们求出所有的$PCL$矩形时，题目已经完成了大半

这时，如果你直接统计个数输出，你就会得到一个很~~理想~~
的成绩

所以，为了避免这种情况的发生，我们还要进行去重操作

每次把我们找到的矩形直接与所有矩形枚举判断是否覆盖即可

这样我们就得到了一个完美的答案

$PS:$大家一定能想到，还有很多方法能优化这个代码，但是我
因为懒，不想想了，希望大家不要向我学习

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[]={0,0,-1,1};
const int dy[]={-1,1,0,0};
int n,cnt,sum[100],ans;
char a[25][25];
bool f[100],v[25][25];
struct ddd{
	int x1,x2,y1,y2;
}s[50010];
void dfs(int x,int y,int n1,int n2,int m1,int m2){
	for(int i=0;i<4;i++)
		{
			int nx=x+dx[i];
			int ny=y+dy[i];
			if(nx<n1 || nx>n2 || ny<m1 || ny>m2 || v[nx][ny] || a[nx][ny]!=a[x][y]) continue;
			v[nx][ny]=true;
			dfs(nx,ny,n1,n2,m1,m2);
		}
}
bool ppcl(int u1,int v1,int u2,int v2){
	int col=0;
	char c1,c2;
	memset(f,0,sizeof(f));
	for(int i=u1;i<=u2;i++)
		for(int j=v1;j<=v2;j++)
			if(!f[a[i][j]])
				{
					f[a[i][j]]=true;
					col++;
					if(col==1)
						c1=a[i][j];
					if(col==2)
						c2=a[i][j];
				}
	if(col!=2)
		return false;
	memset(sum,0,sizeof(sum));
	memset(v,0,sizeof(v));
	for(int i=u1;i<=u2;i++)
		for(int j=v1;j<=v2;j++)
			{
				if(!v[i][j])
					{
						v[i][j]=true;
						sum[a[i][j]]++;
						dfs(i,j,u1,u2,v1,v2);
					}
			}
	if((sum[c1]==1 && sum[c2]>=2 ) || ( sum[c1]>=2 && sum[c2]==1 ))
		return true;
	return false;
}
bool ddfs(int x){
	for(int i=1; i<=cnt; i++)
		{
			if(i!=x && s[i].x1<=s[x].x1 && s[i].y1<=s[x].y1 && s[i].x2>=s[x].x2 && s[i].y2>=s[x].y2)
			    return false;
		}
	return true;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)	
		for(int j=1;j<=n;j++)
			for(int k=i;k<=n;k++)
				for(int l=j;l<=n;l++)
					if(ppcl(i,j,k,l))
						{
							cnt++;
							s[cnt].x1=i;
							s[cnt].y1=j;
							s[cnt].x2=k;
							s[cnt].y2=l;
						}
	for(int i=1;i<=cnt;i++)
		if(ddfs(i))
			ans++;
	cout<<ans;
	return 0;
}
```


---

## 作者：issue_is_fw (赞：3)

**这题真的特别考验细节和技巧，我也调试了一个小时。**

**希望我能为大家讲清楚**

PCL的要求有两个，我们逐个解决。

枚举一个$i,j$作为矩阵的左上角，枚举一个$q,w$作为矩阵的高和宽

接下来我们判断这个矩阵是否是$PCL.$

**Ⅰ**.这两种颜色一种构成一个连通块，另一种形成两个以上的连通块。

这个不难办，我们把这个矩阵的图复制到另一个临时数组b

然后对b进行染色判断即可。

**Ⅱ**.
重点是这个，$PCL$内部不能有$PCL$。

**也就是说，我们只能选最大的PCL矩阵**

这个也好办，我们把步骤Ⅰ筛选下的矩阵存入结构体数组中

然后对数组进行筛选。如果一个矩阵包含另一个矩阵，那么小矩阵就没用了，标记起来。最后答案就是没被标记的那些矩阵。

这部分的代码如下

```cpp
for(int i=1;i<=cnt;i++)
{
	if(isok[i]==0)	continue;
 //被标记的一定是小矩阵，那么小矩阵没资格去标记别人
 //因为标记自己的大矩阵会去标记掉那些别的矩阵
	for(int j=1;j<=cnt;j++)
	{
		if(i==j)	continue;
		if(s[i].l<=s[j].l&&s[i].ll>=s[j].ll&&s[i].r<=s[j].r&&s[i].rr>=s[j].rr)
				isok[j]=false;//j矩阵被包含
	}
}
```

但是具体的细节还很多，看代码吧.......

```cpp
#include <bits/stdc++.h>
using namespace std;
char a[22][22],b[22][22];
int n,m,zi[27],d[5]={0,0,1,-1},c[5]={1,-1,0,0};
bool isok[1000009];
void dfs(int x,int y,int ltop,int rtop,int ll,int rr,char s)
{
	b[x][y]='.';
	for(int i=0;i<4;i++)
	{
		int nx=x+d[i],ny=y+c[i];
		if(nx>=ltop&&nx<=ll&&ny>=rtop&&ny<=rr&&b[nx][ny]==s)
			dfs(nx,ny,ltop,rtop,ll,rr,s);
	}
}
bool init(int l,int r,int q,int w)
{
	memset(zi,0,sizeof(zi));
	int ok=0;
	for(int i=l;i<=l+q;i++)
	for(int j=r;j<=r+w;j++)
	{
		if(zi[a[i][j]-'A']==0)
			zi[a[i][j]-'A']=1,ok++;
		b[i][j]=a[i][j];
	}
	if(ok!=2)	return false;
	for(int i=l;i<=l+q;i++)
	for(int j=r;j<=r+w;j++)
	{
		if(b[i][j]=='.')	continue;
		zi[b[i][j]-'A']++;
		dfs(i,j,l,r,l+q,r+w,b[i][j]);
	}
	int y=0,o=0;
	for(int i=0;i<=26;i++)
	{
		if(zi[i]&&y==0)	y=zi[i]-1;
		else if(zi[i]&&y)	o=zi[i]-1;	
	}
	if(y==1&&o>=2)	return true;
	else if(y>=2&&o==1)	return true;
	else	return false;
}
struct p{
	int l,r,ll,rr;
}s[1000009];int cnt;
int ans=0;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)	cin>>a[i][j];
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	for(int q=0;q+i<=n;q++)//边长为q+1
	for(int w=0;w+j<=n;w++)
	{
		if(init(i,j,q,w))
			s[++cnt].l=i,s[cnt].r=j,s[cnt].ll=i+q,s[cnt].rr=j+w;
	}
	memset(isok,1,sizeof(isok));
	for(int i=1;i<=cnt;i++)
	{
		if(isok[i]==0)	continue;
		for(int j=1;j<=cnt;j++)
		{
			if(i==j)	continue;
			if(s[i].l<=s[j].l&&s[i].ll>=s[j].ll&&s[i].r<=s[j].r&&s[i].rr>=s[j].rr)
				isok[j]=false;
		}
	}
	for(int i=1;i<=cnt;i++)
	if(isok[i])		ans++;
	cout<<ans;
	return 0;
}
```



---

## 作者：sycqwq (赞：2)

分析：

典型暴力题

可以枚举PCL的左上角 $x,y$ 坐标和右下角 $x,y$ 坐标。

然后判断

如果是的话记录，最后去重

判断分为 $check1$ 和 $check2$

$check1:$

判断是否有且只有两种颜色在这个区域内

直接枚举即可

$check2:$

判断是否有一种颜色只存在一个连通块，而另一种颜色存在大于等于 $2$ 个

代码：
```cpp
#include<bits/stdc++.h>
#define inf 2147283647
using namespace std;
int n;
char a[25][25];
    char q='.',p='.';
int check(int x,int y,int x1,int y1)//check1
{
     q='.',p='.';
    //  cout<<x<<' '<<y<<' '<<x1<<' '<<y1<<endl;
    for(int i=x;i<=x1;i++)//枚举这一范围
        for(int j=y;j<=y1;j++)
        {
            if(a[i][j]!=q&&a[i][j]!=p&&q!='.'&&p!='.')
            {
                // cout<<' '<<x1<<' '<<y1<<' '<<i<<' '<<j<<' '<<q<<' '<<p<<endl;
                return 0;
            }
            else
            {
                if(a[i][j]!=q&&a[i][j]!=p)
                {
                    if(q=='.')
                        q=a[i][j];
                        else
                            p=a[i][j];
                }
            }
        }
    if(q=='.'||p=='.')
        return 0; 
    return 1;
}
int tx[5]={0,0,0,1,-1},ty[5]={0,1,-1,0,0},bk[25][25];
void dfs(int x,int y,int j1,int j2,int n,int m,char t)
{
    bk[x][y]=1;
    for(int i=1;i<=4;i++)
    {
        int dx=tx[i]+x,dy=ty[i]+y;
        if(dx<j1||dx>j2||dy<n||dy>m||a[dx][dy]!=t||bk[dx][dy])//dfs要注意上下界
        {
            continue;
        }
        dfs(dx,dy,j1,j2,n,m,t);
    }
}
int check2(int x,int y,int x1,int y1)//check2
{
    int t1=0,t2=0;
    char f='1';
    for(int i=x;i<=x1;i++)//寻找每种颜色连通块个数
        for(int j=y;j<=y1;j++)
        {
            if(!bk[i][j])
            {
                if(a[i][j]==f||f=='1')
                {
                    ++t1;
                    f=a[i][j];
                }
                else
                    ++t2;
                dfs(i,j,x,x1,y,y1,a[i][j]);
            }
        }
    // cout<<t1<<' '<<t2<<endl;
    if(t1==1&&t2>=2||t2==1&&t1>=2)//是否符合要求
        return 1;
    return 0;
}
struct  node
{
    int x,y,x1,y1,c=1;
}e[100005];
int tot;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            for(int k=1;k<=n;k++)
                for(int l=1;l<=n;l++)
                {
                    if(i>k||j>l)
                        continue;
                    if(check(i,j,k,l))
                    {
                        memset(bk,0,sizeof(bk));
                        if(check2(i,j,k,l))
                        {
                            e[++tot].x=i;
                            e[tot].y=j;
                            e[tot].x1=k;
                            e[tot].y1=l;
                            // cout<<1;
                        }
                    }
                    else
                        continue;
                }
        }
        int tp=0;
    for(int i=1;i<=tot;i++)//去重
    {
        for(int j=1;j<=tot;j++)
        {
            if(i!=j)
            {
                if(e[j].x<=e[i].x&&e[j].y<=e[i].y&&e[j].x1>=e[i].x1&&e[j].y1>=e[i].y1)//包含条件
                {
                   e[i].c=0; 
                   break;
                }
            }
        }
    }
    for(int i=1;i<=tot;i++)
    {
        if(e[i].c)
        {
            // cout<<e[i].x<<' '<?<e[i].y<<' '<<e[i].x1<<' '<<e[i].y1<<endl;
            ++tp;
        }
    }

    cout<<tp;
    return 0;
}
```

---

## 作者：曹老师 (赞：2)

## Sol ##

[blog食用](http://www.caolaoshi.men/index.php/archives/usaco17open-wb.html)

**最最暴力的解法，~~不需要O2！！！~~**

我的思路是，枚举一个点，以该点为矩形的左上角，再枚举这个矩形的长度，这样一个矩形就能确定出来了，那么矩形确定了，我们现在就要判断这个矩形是不是$PCL$。再枚举这个矩形中的每一个点，对于每一个点做一遍$BFS$，记录下每一个联通块的颜色，以及该颜色出现的联通块的次数，然后通过上面广搜保存的，检查是否是一个$PCL$，先存起来，最后再跑一边存起来的这些点，看看他们是不是另外PCL的子矩阵，然后就能出答案了。有一个剪枝，能减很多，就是如果出现的颜色次数已经大于$3$了，就肯定不满足条件了。

~~$PS$：本来我的题解想放一个需要氧气的程序来着，优化之后就不用氧气了（逃~~

## Code ##

```
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

struct Zuobiao {
    int x , y;
    Zuobiao (int xx , int yy) {
        x = xx , y = yy;
    }
};
struct PCL {
    int x1 , y1 , x2 , y2;
};
PCL pcl[50000];
int n , map[25][25] , vis[25][25] , ans = 0 , top = 0;
int Ju[5];

void bfs(int x , int y) {
    queue<Zuobiao>q;
    vis[x][y] = 1;
    q.push(Zuobiao(x , y));
    while(!q.empty()) {
        Zuobiao u = q.front();
        q.pop();
        int xx = u.x , yy = u.y;
        if(xx-1 >= Ju[0] && !vis[xx-1][yy] && map[xx-1][yy] == map[xx][yy]) {
            vis[xx-1][yy] = 1;
            q.push(Zuobiao(xx-1 , yy));
        }
        if(xx+1 <= Ju[1] && !vis[xx+1][yy] && map[xx+1][yy] == map[xx][yy]) {
            vis[xx+1][yy] = 1;
            q.push(Zuobiao(xx+1 , yy));
        }
        if(yy-1 >= Ju[2] && !vis[xx][yy-1] && map[xx][yy-1] == map[xx][yy]) {
            vis[xx][yy-1] = 1;
            q.push(Zuobiao(xx , yy-1));
        }
        if(yy+1 <= Ju[3] && !vis[xx][yy+1] && map[xx][yy+1] == map[xx][yy]) {
            vis[xx][yy+1] = 1;
            q.push(Zuobiao(xx , yy+1));
        }
    }
}

int check(int color[]) {
    int t1 = color[1] , t2 = color[2] , t3 = color[3];
    if((t1 == t2 && t1 != t3) || (t1 == t3 && t1 != t2) || (t2 == t3 && t2 != t1))
        return 1;
    return 0;
}

int find(int sum[]) {
    int one = 0 , two = 0;
    for(int i=1; i<=26; i++)
        if(sum[i]) {
            two++;
            if(sum[i] == 1)
                one++;
        }
    if(one == 1 && two == 2)
        return 1;
    return 0;
}

int Ans(int x) {
    for(int i=1; i<=top; i++)
        if(i != x && pcl[i].x1 <= pcl[x].x1 && pcl[i].y1 <= pcl[x].y1 && pcl[i].x2 >= pcl[x].x2 && pcl[i].y2 >= pcl[x].y2)
            return 0;
    return 1;
}

int main() {
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++) {
            char c;
            cin>>c;
            map[i][j] = c - 'A' + 1;
        }
    for(int x=1; x<=n; x++)
        for(int y=1; y<=n; y++) {
            for(int len1=1; len1<=n-x+1; len1++)
                for(int len2=1; len2<=n-y+1; len2++) {
                    int cnt = 0 , sum[30];
                    Ju[0] = x , Ju[1] = x+len1-1 , Ju[2] = y , Ju[3] = y+len2-1;
                    memset(vis , 0 , sizeof(vis));
                    memset(sum , 0 , sizeof(sum));
                    for(int k=x; k<=x+len1-1; k++)
                        for(int l=y; l<=y+len2-1; l++) {
                            if(!vis[k][l]) {
                            	if(!sum[map[k][l]])
                            		cnt++;
                            	if(cnt > 3)
                            		break;
                                sum[map[k][l]]++;
                                bfs(k , l);
                            }
                        }
                    if(find(sum)) {
                        top++;
                        pcl[top].x1 = x;
                        pcl[top].y1 = y;
                        pcl[top].x2 = x + len1 - 1;
                        pcl[top].y2 = y + len2 - 1;
                    }
                }
        }
    for(int i=1; i<=top; i++)
        if(Ans(i))
            ans++;
    printf("%d",ans);
    return 0;
}
```


  [1]: https://www.luogu.org/problemnew/show/P3671

---

## 作者：xzy_caiji (赞：1)

啊~这道~~垃圾~~题竟坑了我五个小时！太可恶了！

自认为所有的坑都踩过一遍了（笑）

---
一开始：啊！好垃圾的一道题啊！

直接一波乱搞就飞了上去……可惜……题看错了……让我求的是连通块个数……不是大小……（等发现了大概`3h`左右）

又改了一下……

？咋给我`10`？（第一次都有`20`）

结果发现求连通块的`dfs`竟然被我写成了全图搜索？（`3h30min`）

改好以后……

你又给我`20`什么意思？

结果发现是`judge`函数的参数写反了……（`4h40min`）

继续改……

又是`10`……

开始看题解，但是没啥用……

根据我的经验，讨论区比题解有用。结果真找到了有用的！[link](https://www.luogu.com.cn/discuss/332593)。终于知道：原来是不能边搜边判重的，得记录下以后统一去重！！！！！

交上去，真不错，`100`！

思路全在注释里。

---
```cpp
/*
先看题，N<=20，考虑暴力。
在主程序里四重循环，每搜到一个可能的PCL都扔到一个vector里。
最后判重。
*/
#include<bits/stdc++.h>
using namespace std;
int n,ans;char a[25][25];bool vis[25][25],f[105];
struct rect{
    int x1,y1,x2,y2;
};
vector<rect>vec;
/*
关于floodfill：
可能写的有些繁琐了，请谅解。
*/
void floodfill(int x,int y,char color,int xx1,int xx2,int yy1,int yy2){
    if(x<xx1||x>xx2||y<yy1||y>yy2||vis[x][y]||a[x][y]!=color)return;
    vis[x][y]=1;
    floodfill(x-1,y,color,xx1,xx2,yy1,yy2);floodfill(x+1,y,color,xx1,xx2,yy1,yy2);floodfill(x,y-1,color,xx1,xx2,yy1,yy2);floodfill(x,y+1,color,xx1,xx2,yy1,yy2);
}
bool judge(int x){
    for(int i=0;i<vec.size();i++)if(i!=x&&vec[i].x1<=vec[x].x1&&vec[i].y1<=vec[x].y1&&vec[i].x2>=vec[x].x2&&vec[i].y2>=vec[x].y2)return 0;
    return 1;
}
/*
关于checkpcl;
忠实地按照题意模拟即可。
也写的很繁琐，请谅解。
*/
bool checkpcl(int x1,int y1,int x2,int y2){
    int cnum=0;char c1,c2;
    for(int i=x1;i<=x2;i++)
        for(int j=y1;j<=y2;j++){
            if(!f[a[i][j]]){
                cnum++;
                f[a[i][j]]=1;
                if(cnum==1)c1=a[i][j];
                if(cnum==2)c2=a[i][j];
            }
        }
    if(cnum!=2)return 0;
    int f1=0,f2=0;
    for(int i=x1;i<=x2;i++)
        for(int j=y1;j<=y2;j++){
            if(a[i][j]==c1&&!vis[i][j]){
                f1++;floodfill(i,j,c1,x1,x2,y1,y2);
            }
            if(a[i][j]==c2&&!vis[i][j]){
                f2++;floodfill(i,j,c2,x1,x2,y1,y2);
            }
        }
    if(f1==1&&f2>1||f1>1&&f2==1)return 1;
    return 0;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int k=i;k<=n;k++)
                for(int l=j;l<=n;l++){
                    if(checkpcl(i,j,k,l)){
                        vec.push_back((rect){i,j,k,l});
                    }
                    memset(f,0,sizeof(f));
                    memset(vis,0,sizeof(vis));
                }
    for(int i=0;i<vec.size();i++)if(judge(i))ans++;
    cout<<ans;
}
```

---

## 作者：KidA (赞：0)

我们先枚举所有子矩阵，验证其在不考虑重叠的情况下是否为 PCL 矩阵（dfs 求一遍联通块即可）。

然后将所有满足条件的矩阵存下来，最后朴素判断每个矩阵是否被其他矩阵包括，若没有矩阵包括它，则其对于答案的贡献为 $1$，累加所有贡献即为最终结果。

时间复杂度是 $O(n^6)$ 的。

思路很简单，讲一下坑点：

- dfs 求联通块时，注意坐标范围不是 $1 \sim n$ 而是当前子矩阵的左上角坐标 $\sim$ 右下角坐标。

- 枚举子矩阵时，左下角坐标可以等于右下角坐标，所以注意循环变量的初始值设定。

代码（略有压行）：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ft first
#define sc second
using namespace std;
int n,ans,tot,dx[]={0,0,-1,1},dy[]={-1,1,0,0};
char mp[31][31];
bool fl[31][31]; //标记联通块
pair<pair<int,int>,pair<int,int> > mat[160031]; //存放合法矩阵
void dfs(int x,int y,int n1,int n2,int m1,int m2,char c){ //dfs 求联通块
    fl[x][y]=1;
    for(int i=0;i<4;i++){
        int xx=x+dx[i],yy=y+dy[i];
        if(xx>=n1&&xx<=n2&&yy>=m1&&yy<=m2&&!fl[xx][yy]&&mp[xx][yy]==c) dfs(xx,yy,n1,n2,m1,m2,c);
    }
}
bool check(int x,int y,int xx,int yy){ //校验矩阵
    char c1=' ',c2=' '; int cnt1=0,cnt2=0; //分别表示：两种不同类型的字符、两种字符的联通块数量
    for(int i=x;i<=xx;i++){ for(int j=y;j<=yy;j++){ if(c1==' '){ c1=mp[i][j]; break; } } } //找出第一种字符
    for(int i=x;i<=xx;i++){ for(int j=y;j<=yy;j++){ if(c2==' '&&mp[i][j]!=c1){ c2=mp[i][j]; break; } } } //找出第二种字符
    for(int i=x;i<=xx;i++) for(int j=y;j<=yy;j++) if(mp[i][j]!=c1&&mp[i][j]!=c2) return 0; //若字符种类超过两种一定不合法
    memset(fl,0,sizeof(fl));
    for(int i=x;i<=xx;i++) for(int j=y;j<=yy;j++)
            if(mp[i][j]==c1&&!fl[i][j]) cnt1++,dfs(i,j,x,xx,y,yy,c1); //求第一种字符的联通块数量
    for(int i=x;i<=xx;i++) for(int j=y;j<=yy;j++)
            if(mp[i][j]==c2&&!fl[i][j]) cnt2++,dfs(i,j,x,xx,y,yy,c2); //求第二种字符的联通块数量
    if((cnt1==1&&cnt2>1)||(cnt1>1&&cnt2==1)) return 1; return 0; //若一种字符的联通块数量>1且另一种=1则合法，否则不合法
}

signed main(){
	ios::sync_with_stdio(0);
	cin>>n;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>mp[i][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
	       for(int ii=i;ii<=n;ii++) for(int jj=j;jj<=n;jj++)
	               if(check(i,j,ii,jj)) mat[++tot].ft.ft=i,mat[tot].ft.sc=j,mat[tot].sc.ft=ii,mat[tot].sc.sc=jj; //存放矩阵
	for(int i=1;i<=tot;i++){
	    bool f=1;
	    for(int j=1;j<=tot;j++) if(i!=j&&mat[i].ft.ft>=mat[j].ft.ft&&mat[i].ft.sc>=mat[j].ft.sc&&mat[i].sc.ft<=mat[j].sc.ft&&mat[i].sc.sc<=mat[j].sc.sc){ f=0; break; } //遍历矩阵判断是否覆盖
	    if(f) ans++; //累加贡献
	}
	cout<<ans;
    return 0;
}

```

---

