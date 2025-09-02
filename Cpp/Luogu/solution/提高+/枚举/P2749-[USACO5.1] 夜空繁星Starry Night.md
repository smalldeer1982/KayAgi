# [USACO5.1] 夜空繁星Starry Night

## 题目背景

高高的星空，簇簇闪耀的群星形态万千。一个星座(cluster)是一群连通的星组成的非空连通星系，这里的连通是指水平，垂直或者对角相邻的两个星星。一个星座不能是另一个更大星座的一部分， 星座可以相似(similar)。如果两个星座有相同的形状，而且包括相同数目的星体，那么不管其方向性如何，就算相似。一般而言，星座可能的方向有八个，如图1所示。

![](https://cdn.luogu.com.cn/upload/pic/1970.png)


## 题目描述

夜空可以表示为一份天体图(sky map)，它是一个由字符0和1组成的二维矩阵，字符1表示所在的位置有一颗星；字符0表示该位置上是空的.给定一份天体图，用同一个小写英文标识(mark)相似的所有星座。相似的星座必须用相同的字母标识，不同的星座表示为不同的字母。标识一个星座，就是将其中各星体对应的字符1替换为相应的小写字母.


## 说明/提示

在这种情况下，天体图是一个长23宽为15的二维矩阵。请注意这幅天体图是对应（corresponds to）下面这个矩阵的图像。

Starry-2.gif 图starry-2：天体图

 ![](https://cdn.luogu.com.cn/upload/pic/1971.png) 

这是上述输入实例的一个可能的结果。请注意，该输出文件对应于下面的天空景象。


 ![](https://cdn.luogu.com.cn/upload/pic/1972.png) 

### 数据范围

0 <= 星空的长和宽 <= 100

0 <= 星座个数 <= 500

0 <= 不相似的星座个数 <= 26

1 <= 每个星座中星星个数 <= 160


## 样例 #1

### 输入

```
23
15
10001000000000010000000
01111100011111000101101
01000000010001000111111
00000000010101000101111
00000111010001000000000
00001001011111000000000
10000001000000000000000
00101000000111110010000
00001000000100010011111
00000001110101010100010
00000100110100010000000
00010001110111110000000
00100001110000000100000
00001000100001000100101
00000001110001000111000```

### 输出

```
a000a0000000000b0000000
0aaaaa000ccccc000d0dd0d
0a0000000c000c000dddddd
000000000c0b0c000d0dddd
00000eee0c000c000000000
0000e00e0ccccc000000000
b000000e000000000000000
00b0f000000ccccc00a0000
0000f000000c000c00aaaaa
0000000ddd0c0b0c0a000a0
00000b00dd0c000c0000000
000g000ddd0ccccc0000000
00g0000ddd0000000e00000
0000b000d0000f000e00e0b
0000000ddd000f000eee000```

# 题解

## 作者：「QQ红包」 (赞：11)

求联通块部分同，dfs扫

然后看是不是相似用了一种很神奇的方式：求两两之间的距离，然后加起来。

然后可以AC了

```cpp
/*
ID: ylx14271
PROG: starry 
LANG: C++     
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n,m;
int a[510][110];
char f[510][110];

int x4[510][110],y4[510][110];
double s[510];//距离和 
char c[510];
int n1,n2;

int t[510];
char ch;
double d(int x2,int y2,int x3,int y3)
{
    return sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
}
int check(int h)//求距离
{
    for (int i1=1;i1<=n2;i1++)
        for (int j1=1;j1<=n2;j1++)
        s[h]+=d(x4[n1][i1],y4[n1][i1],x4[n1][j1],y4[n1][j1]);
    for (int ii=1;ii<n1;ii++)//是否存在相同的图形
        if (fabs(s[h]-s[ii])<=0.00001) return ii;
    return 0;
}
void dfs(int x,int y)//dfs标联通块
{
    int xx,yy;
    for (int i1=-1;i1<=1;i1++)
        for (int j1=-1;j1<=1;j1++)
        {
            if (i1==0&&j1==0) continue;
            xx=x+i1;yy=y+j1;
            if (xx<=0||yy<=0||xx>n||yy>m||a[xx][yy]==0||f[xx][yy]!='0') continue;
            f[xx][yy]=ch;.//标记
            n2++;
            x4[n1][n2]=xx;//把联通块n1的所有点都存起来算距离
            y4[n1][n2]=yy;
            dfs(xx,yy);
        }
    return;
}
int main()
{
    scanf("%d%d",&m,&n);
    for (int i=1;i<=n;i++)//读入 
        for (int j=1;j<=m;j++)
        {
            ch=getchar();
            while (ch!='0'&&ch!='1') ch=getchar();
            if (ch=='0') a[i][j]=0; else a[i][j]=1;
        }
    ch='a'-1;
    memset(f,'0',sizeof(f));
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        if (f[i][j]=='0'&&a[i][j]==1) 
        {
            n2=1,n1++;
            x4[n1][n2]=i,y4[n1][n2]=j;//标记起来求距离 
            ch++;
            c[n1]=ch;
            f[i][j]=ch,dfs(i,j);
            int flag=0;
            flag=check(n1); 
            if (flag!=0)//存在相同的联通块
            {
                ch--;
                for (int i1=1;i1<=n2;i1++) f[x4[n1][i1]][y4[n1][i1]]=c[flag];//一个一个点的改标记
            } 
        }
    //for (int i=1;i<=n1;i++) printf("%.4f ",s[i]); 
    //cout<<endl;
    for (int i=1;i<=n;i++)//输出
    {
        for (int j=1;j<=m;j++) printf("%c",f[i][j]);
        printf("\n");
    }
    return 0;
}
```

---

## 作者：小菜鸟 (赞：6)

这道题的搜索部分就不说了，感觉也就普及组的搜索难度……  

还是来说说判图形全等吧！  

看到之前大佬们的用距离之和判全等的方法，感觉对我这等蒟蒻好玄QAQ  

然而判全等还有一个更好想的思路  

对于每一个图形（不考虑旋转），将其中所有点按纵坐标第一关键字、横坐标第二关键字排序后，得到了唯一的一个格点序列。  

而当两个图形全等且方向相同时，其对应点之间的横纵坐标差都是相等的。显然排过序的点一一对应，因此只要计算各对应点间横纵坐标差是否相等即可。对于旋转的情况，我们只要将其中一个图形绕$x$轴、$y$轴和对角线进行翻转，就可以得到所有的八种情况。对每种情况一一判断就行了。  

代码量略大，但基本是无脑复制，思维复杂度相比其他判重方法明显下降。同时单次判断的复杂度由$\Theta(n^2)$($n$指单个星座内的点数)下降到了$\Theta(nlogn)$（常数巨大！），还没有精度问题（我们班有人用$sqrt$爆精度了），不会撞哈希（我们班有人考试代码哈希冲突GG），真的好吃的一批ヾ(◍°∇°◍)ﾉﾞ  

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
char readchar()
{
    char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    return c;
}
struct syt//就是pair,一开始没打using namespace std,CE,于是手写（不要问我这是谁的名字）
{
    char first,second;
    syt(char aa=0,char bb=0):first(aa),second(bb) {}
    bool operator<(syt b)
    {
        if(first!=b.first)return first<b.first;
        return second<b.second;
    }
};
char skymap[105][105];
int dx[8]={-1,0,1,-1,1,-1,0,1};
int dy[8]={1,1,1,0,0,-1,-1,-1};
struct clu//结构体存星座舒服
{
    int size;//记录星星个数
    syt shape[170];//存下星座中所有星星
    void clear(){size=0;}
};
clu temp;
bool cmp(clu a,clu b)//判断两图形是否互为平移关系
{
    int s=a.size;
    int xx=a.shape[0].first-b.shape[0].first;//两图横坐标差
    int yy=a.shape[0].second-b.shape[0].second;//两图纵坐标差
    for(int i=0;i<s;++i)
    {
        if(a.shape[i].first-b.shape[i].first!=xx)return 0;//直接扫一遍
        if(a.shape[i].second-b.shape[i].second!=yy)return 0;
    }
    return 1;
}
bool operator==(clu a,clu b)//判断两图形是否全等
{
    if(a.size!=b.size)return 0;//先看是不是一样大
    bool f=0;
    int s=a.size;
    sort(a.shape,a.shape+s);//x,y //没有旋转、对称
    sort(b.shape,b.shape+s);
    f=cmp(a,b);
    if(f)return 1;
    for(int i=0;i<s;++i)b.shape[i].first=-b.shape[i].first;//-x,y //关于y轴对称
    sort(b.shape,b.shape+s);
    f=cmp(a,b);
    if(f)return 1;
    for(int i=0;i<s;++i)b.shape[i].second=-b.shape[i].second;//-x,-y //下同，直到枚举完8种情况
    sort(b.shape,b.shape+s);
    f=cmp(a,b);
    if(f)return 1;
    for(int i=0;i<s;++i)b.shape[i].first=-b.shape[i].first;//x,-y
    sort(b.shape,b.shape+s);
    f=cmp(a,b);
    if(f)return 1;
    for(int i=0;i<s;++i)swap(b.shape[i].first,b.shape[i].second);//-y,x
    sort(b.shape,b.shape+s);
    f|=cmp(a,b);
    if(f)return 1;
    for(int i=0;i<s;++i)b.shape[i].first=-b.shape[i].first;//y,x
    sort(b.shape,b.shape+s);
    f=cmp(a,b);
    if(f)return 1;
    for(int i=0;i<s;++i)b.shape[i].second=-b.shape[i].second;//y,-x
    sort(b.shape,b.shape+s);
    f=cmp(a,b);
    if(f)return 1;
    for(int i=0;i<s;++i)b.shape[i].first=-b.shape[i].first;//-y,-x
    sort(b.shape,b.shape+s);
    f=cmp(a,b);
    if(f)return 1;
    return 0;
}
bool check1(int x,int y)
{
    return x<0||x>=n||y<0||y>=m||skymap[x][y]!='1';//为第一遍搜索判断
}
bool check2(int x,int y)
{
    return x<0||x>=n||y<0||y>=m||skymap[x][y]!='2';//为第二遍搜索判断
}
void dfs1(int x,int y)
{
    skymap[x][y]='2';//染色标记已搜联通块
    temp.shape[temp.size++]=syt(x,y);//将当前点加入临时星座temp中
    for(int j=0;j<8;++j)
        {
            if(check1(x+dx[j],y+dy[j]))continue;
            dfs1(x+dx[j],y+dy[j]);
        }
}
void dfs2(int x,int y,char nm)//用于将联通块变成对应的字母
{
    skymap[x][y]=nm;
    temp.shape[temp.size++]=syt(x,y);//依然要加入temp，以便记录新的星座
    for(int j=0;j<8;++j)
        {
            if(check2(x+dx[j],y+dy[j]))continue;
            dfs2(x+dx[j],y+dy[j],nm);
        }
}
clu sim[26];//记录已经出现过的星座
char totnm='a';
int tot;
int main()
{
    scanf("%d%d",&m,&n);//注意顺序！
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            skymap[i][j]=readchar();
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
        {
            if(skymap[i][j]=='1')
            {
                temp.size=0;
                dfs1(i,j);
                bool f=0;//记录是否有重复
                for(int k=0;k<tot;++k)
                {
                    if(sim[k]==temp)//判断图形是否全等
                    {
                        temp.size=0;//重置临时星座
                        f=1;
                        dfs2(i,j,'a'+k);//染成对应的名字
                        break;
                    }
                }
                if(!f)
                {
                    temp.size=0;
                    dfs2(i,j,'a'+tot);
                    sim[tot++]=temp;//发现新的星座，则加入已知星座中
                }
            }
        }
    for(int i=0;i<n;++i)puts(skymap[i]);
}
```

~~依然感觉这题蓝得有点过分~~

---

## 作者：Limit (赞：5)

USACO的搜索，不知道为什么和二维凸包扯上关系QAQ
刚看到这道题时无从下手...貌似很难呀，~~大概翻了一下题解~~...**发现了一个玄学定理:** *每一个点和别的点的距离相加，一样的图形总是一样的*

QAQ 前方~~水题~~警告
接下来就简单了...

```pascal
const z:array[1..8,1..2]of -1..1=((1,0),(0,1),(-1,0),(0,-1),(1,1),(1,-1),(-1,1),(-1,-1));
var i,j,k:longint;
    m,n:longint;
    ans:array[0..101,0..101]of longint;
    boo:array[0..101,0..101]of boolean;
    num:array[0..501]of real;
    sum2:array[0..501]of longint;
    x,y:array[0..161]of longint;
    lastx,lasty:array[0..501]of array[0..161]of longint;
    sum,add:longint;
    ch:char;
    out:array[0..26]of char;
procedure same(p,q:longint);//第p个图形和第q个图形全等，且第q个图形在之前出现过
var i:longint;
begin
  for i:=1 to sum2[q] do 
  ans[lastx[q][i],lasty[q][i]]:=ans[lastx[p][1],lasty[p][1]];//把答案赋值成一样的
end;
procedure new(p:longint);//第p个图形在之前没有出现过
var i:longint;
begin
  inc(add);//种数++
  for i:=1 to sum2[p] do
  ans[lastx[p][i],lasty[p][i]]:=add;//把该图形赋值成这个
end;
function long(x1,y1,x2,y2:longint):real;//计算两点之间距离
begin
  exit(sqrt(sqr(x1-x2)+sqr(y1-y2)));
end;
procedure bfs(fx,fy:longint);//BFS最喜欢了，其实dfs也可以
var i,j,k,h,t:longint;
    have:boolean;
    from:longint=0;
begin
  h:=1;
  t:=1;
  x[1]:=fx;
  y[1]:=fy;
  boo[fx,fy]:=false;
  repeat
    for i:=1 to 8 do
    if boo[x[t]+z[i,1],y[t]+z[i,2]] then
    begin
      inc(h);
      x[h]:=x[t]+z[i,1];
      y[h]:=y[t]+z[i,2];
      boo[x[h],y[h]]:=false;
    end;
    inc(t);
  until t>h;
  inc(sum);
  num[sum]:=0;
  for i:=1 to h do
  for j:=1 to h do
  num[sum]:=num[sum]+long(x[i],y[i],x[j],y[j]);//计算出一个点和别的点的距离之和
  lastx[sum]:=x;//把经过的位置保留下来
  lasty[sum]:=y;
  have:=false;
  sum2[sum]:=h;
  for i:=1 to sum-1 do
  if abs(num[i]-num[sum])<0.0001 then//利用这个定理判断这两个图形全等
  begin
  same(i,sum);
  have:=true;
  from:=i;
  break;
  end;
  if not have then new(sum);//在之前没有全等的图形
end;
begin
  readln(n);
  readln(m);
  for i:=1 to m do
  begin
    for j:=1 to n do
    begin
      read(ch);
      if ch='1' then boo[i,j]:=true;
    end;
    readln;
  end;
  for i:=1 to m do
  for j:=1 to n do
  if boo[i,j] then
  bfs(i,j);
  out[0]:='0';//这样输出简单
  for i:=1 to 26 do out[i]:=chr(i+96);
  for i:=1 to m do
  begin
    for j:=1 to n do write(out[ans[i,j]]);//QAQ
    writeln;
  end;
end.
```
偶尔背一些定理对于做题还是有好处的QAQ

---

## 作者：VCVCVCFop_zz (赞：5)

这题很烦很暴力。。

大致思路就是暴力灌水搜出每张子图，并且判重。

样例很完善了，判重需要考虑旋转和对称两种情况，可以通过两个子程序解决

TIP：sizex,sizey表示子图的大小，map描述子图

旋转：

```cpp
inline node xz(node graph)
{
    node cha;
    cha.sizex=graph.sizey;
    cha.sizey=graph.sizex;
    for(int i=1;i<=cha.sizex;i++)
        for(int j=1;j<=cha.sizey;j++)
        {
            cha.map[i][j]=graph.map[j][graph.sizey-i+1];
        }
    return cha;
}
```
对称：
```cpp
inline node fz(node graph)
{
    node cha;
    cha.sizex=graph.sizex;
    cha.sizey=graph.sizey;
    for(int i=1;i<=cha.sizex;i++)
        for(int j=1;j<=cha.sizey;j++)
            cha.map[i][j]=graph.map[graph.sizex-i+1][j];
    return cha;
}
```
然后判断重复即可。
要注意，灌水的时候需要两次DFS,第一次求出左上角和右下角，第二次染色并记录子图

下面附代码：

            
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
struct node
{
    int map[101][101];
    int sizex,sizey;
}stmap;
int tmp[101][101];
int n,m,tot=0,cnt=0;
int kind[101][101];
node save[30];
int mx,my;
int num[1000];
int dx[9]={0,0,1,0,-1,1,1,-1,-1};
int dy[9]={0,1,0,-1,0,-1,1,-1,1};
int vis[101][101],st[101][101];
string s;
int x,y;
inline void dfs(int yx,int yy,int k)
{
    vis[yx][yy]=1;
    kind[yx][yy]=k;x=min(yx,x);y=min(yy,y);
    mx=max(yx,mx);my=max(yy,my);
    for(int i=1;i<=8;i++)
    {
        int tx=yx+dx[i];int ty=yy+dy[i];
        if(tx<1||tx>n||ty<1||ty>m)    continue;
        if(!vis[tx][ty]&&st[tx][ty])    dfs(tx,ty,k);
    }
}
inline void dfs1(int yx,int yy,int k)
{
    vis[yx][yy]=2;
    for(int i=1;i<=8;i++)
    {
        int tx=yx+dx[i];int ty=yy+dy[i];
        if(tx<1||tx>n||ty<1||ty>m)    continue;
        if((vis[tx][ty]==1)&&st[tx][ty])    dfs1(tx,ty,k);
    }
    stmap.map[yx-x+1][yy-y+1]=1;
}
inline void out(node graph)
{
    for(int i=1;i<=graph.sizex;i++)
    {
        for(int j=1;j<=graph.sizey;j++)
            cout<<graph.map[i][j];
        cout<<endl;
    }
    cout<<endl;
}
inline node xz(node graph)
{
    node cha;
    cha.sizex=graph.sizey;
    cha.sizey=graph.sizex;
    for(int i=1;i<=cha.sizex;i++)
        for(int j=1;j<=cha.sizey;j++)
        {
            cha.map[i][j]=graph.map[j][graph.sizey-i+1];
        }
    return cha;
}
inline node fz(node graph)
{
    node cha;
    cha.sizex=graph.sizex;
    cha.sizey=graph.sizey;
    for(int i=1;i<=cha.sizex;i++)
        for(int j=1;j<=cha.sizey;j++)
            cha.map[i][j]=graph.map[graph.sizex-i+1][j];
    return cha;
}
inline bool dif(node map1,node map2)
{
    if(map1.sizex!=map2.sizex||map1.sizey!=map2.sizey)
        return 0;
    for(int i=1;i<=map1.sizex;i++)
        for(int j=1;j<=map1.sizey;j++)
            if (map1.map[i][j]!=map2.map[i][j])    return 0;
    return 1;
}
inline bool check(node map1,node map2)
{
    node tmap=map2;
    for(int i=1;i<=4;i++)
    {
        if(dif(map1,tmap))    return 1;
        tmap=xz(tmap);
    }    
    tmap=fz(map2);
    for(int i=1;i<=4;i++)
    {
        if(dif(map1,tmap))    return 1;
        tmap=xz(tmap);
    }    
    return 0;
}
inline void solve(node stmap,int cnt)
{
    for(int i=1;i<=tot;i++)
    {
        if(check(save[i],stmap))
        {
            num[cnt]=i;
            return;
        }
    }
    tot++;
    save[tot]=stmap;
    num[cnt]=tot;
}
int main()
{
    cin>>m>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        for(int j=0;j<=m-1;j++)
            if(s[j]=='1')    st[i][j+1]=1;else st[i][j+1]=0;
    }
    for(int i=1;i<=n;i++)    for(int j=1;j<=m;j++)    vis[i][j]=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(st[i][j]&&!vis[i][j])
            {
                stmap.sizex=stmap.sizey=1;
                cnt++;
                x=i;y=j;
                mx=0;my=0;
                dfs(i,j,cnt);
                dfs1(i,j,cnt);
                stmap.sizex=mx-x+1;stmap.sizey=my-y+1;
                //for(int i=x;i<=x+stmap.sizex;i++)    for(int j=y;j<=y+stmap.sizey;j++)    stmap.map[i-x+1][j-y+1]=tmp[i][j];
                //out(stmap);
                solve(stmap,cnt);    for(int ii=1;ii<=mx;ii++)    for(int jj=1;jj<=my;jj++)    stmap.map[ii][jj]=0;
            }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
            if(st[i][j])
                printf("%c",num[kind[i][j]]+'a'-1);
                else printf("0");
        printf("\n");
    }
}
```

---

## 作者：小手冰凉 (赞：4)

题解那么少，发个一份


蒟蒻题解，可能有很多东西不需要，大犇不要太计较了


先用灌水灌出联通块，取出整个矩阵，然后用HASH判重（这步占了一半长度），如果没出现就旋转8次加入


替换时直接替换掉，不过要注意矩阵里其他连通块部分不能取出（用0占位）


    
    
    
    
    
    
    
```cpp
#include<bits/stdc++.h>
using namespace std;
bool b[105][105];
char ch[105][105];
int i,j,n,m,mx,my,sx,sy;
char x,k;
int dx[9]={0,1,1,1,-1,-1,-1,0,0};
int dy[9]={0,0,1,-1,0,1,-1,1,-1};
string hash[80005];
int kuan[80005];
char c[80005];
void get(int x,int y)//灌水连通块
{
    if(b[x][y])return;
    mx=max(x,mx);
    my=max(y,my);
    sx=min(sx,x);
    sy=min(sy,y);
    b[x][y]=true;
    for(int i=1;i<=8;i++){
        int tx=dx[i]+x;
        int ty=dy[i]+y;
        if(ch[tx][ty]=='1')get(tx,ty);
    }
    return;
}
void addto()//加入8种情况
{
    k++;
    string s;
    s.clear();
    for(int i=sx;i<=mx;i++)
        for(int j=sy;j<=my;j++)
            if(b[i][j]&&ch[i][j]=='1'||ch[i][j]=='0')s=s+ch[i][j];
            else s=s+'0';
    int z=0;
    for(int i=0;i<=s.length()-1;i++)
        z=(z*26+s[i]-'0')%80000+1;
    while(hash[z]!="!")z=z%80000+1;
    hash[z]=s;
    c[z]=k;
    kuan[z]=mx-sx;
    s.clear();
    for(int i=mx;i>=sx;i--)
        for(int j=sy;j<=my;j++)
            if(b[i][j]&&ch[i][j]=='1'||ch[i][j]=='0')s=s+ch[i][j];
            else s=s+'0';
    z=0;
    for(int i=0;i<=s.length()-1;i++)
        z=(z*26+s[i]-'0')%80000+1;
    while(hash[z]!="!")z=z%80000+1;
    hash[z]=s;
    c[z]=k;
    kuan[z]=mx-sx;
    s.clear();
    for(int i=sx;i<=mx;i++)
        for(int j=my;j>=sy;j--)
            if(b[i][j]&&ch[i][j]=='1'||ch[i][j]=='0')s=s+ch[i][j];
            else s=s+'0';
    z=0;
    for(int i=0;i<=s.length()-1;i++)
        z=(z*26+s[i]-'0')%80000+1;
    while(hash[z]!="!")z=z%80000+1;
    hash[z]=s;
    c[z]=k;
    kuan[z]=mx-sx;
    s.clear();
    for(int i=mx;i>=sx;i--)
        for(int j=my;j>=sy;j--)
            if(b[i][j]&&ch[i][j]=='1'||ch[i][j]=='0')s=s+ch[i][j];
            else s=s+'0';
    z=0;
    for(int i=0;i<=s.length()-1;i++)
        z=(z*26+s[i]-'0')%80000+1;
    while(hash[z]!="!")z=z%80000+1;
    hash[z]=s;
    c[z]=k;
    kuan[z]=mx-sx;
    s.clear();
    for(int j=sy;j<=my;j++)
        for(int i=sx;i<=mx;i++)
            if(b[i][j]&&ch[i][j]=='1'||ch[i][j]=='0')s=s+ch[i][j];
            else s=s+'0';
    z=0;
    for(int i=0;i<=s.length()-1;i++)
        z=(z*26+s[i]-'0')%80000+1;
    while(hash[z]!="!")z=z%80000+1;
    hash[z]=s;
    c[z]=k;
    kuan[z]=my-sy;
    s.clear();
    for(int j=sy;j<=my;j++)
        for(int i=mx;i>=sx;i--)
            if(b[i][j]&&ch[i][j]=='1'||ch[i][j]=='0')s=s+ch[i][j];
            else s=s+'0';
    z=0;
    for(int i=0;i<=s.length()-1;i++)
        z=(z*26+s[i]-'0')%80000+1;
    while(hash[z]!="!")z=z%80000+1;
    hash[z]=s;
    c[z]=k;
    kuan[z]=my-sy;
    s.clear();
    for(int j=my;j>=sy;j--)
        for(int i=sx;i<=mx;i++)
            if(b[i][j]&&ch[i][j]=='1'||ch[i][j]=='0')s=s+ch[i][j];
            else s=s+'0';
    z=0;
    for(int i=0;i<=s.length()-1;i++)
        z=(z*26+s[i]-'0')%80000+1;
    while(hash[z]!="!")z=z%80000+1;
    hash[z]=s;
    c[z]=k;
    kuan[z]=my-sy;
    s.clear();
    for(int j=my;j>=sy;j--)
        for(int i=mx;i>=sx;i--)
            if(b[i][j]&&ch[i][j]=='1'||ch[i][j]=='0')s=s+ch[i][j];
            else s=s+'0';
    z=0;
    for(int i=0;i<=s.length()-1;i++)
        z=(z*26+s[i]-'0')%80000+1;
    while(hash[z]!="!")z=z%80000+1;
    hash[z]=s;
    kuan[z]=my-sy;
    c[z]=k;
    return;
}
char pd()//判断是不是已出现过
{
    string s;
    s.clear();
    for(int i=sx;i<=mx;i++)
        for(int j=sy;j<=my;j++)
            if(b[i][j]&&ch[i][j]=='1'||ch[i][j]=='0')s=s+ch[i][j];
            else s=s+'0';
    int z=0;
    for(int i=0;i<=s.length()-1;i++)
        z=(z*26+s[i]-'0')%80000+1;
    while(hash[z]!="!"&&(hash[z]!=s||kuan[z]!=mx-sx))z=z%80000+1;
    if(hash[z]=="!")addto();
//    cout<<s<<' '<<c[z]<<endl;
    return c[z];
}
void change(char x)//改变矩阵
{
    for(int i=sx;i<=mx;i++)
        for(int j=sy;j<=my;j++)
            if(b[i][j]){
                ch[i][j]=x;
                b[i][j]=false;
            }
    return;
}
int main()
{
    std::ios::sync_with_stdio(false);//加快cin,cout速度
    cin>>n>>m;
    for(int i=1;i<=80004;i++)hash[i]="!";
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            cin>>ch[i][j];
    k='a'-1;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(ch[i][j]=='1'){
                mx=my=0;
                sx=sy=10000;
                get(i,j);
                x=pd();
                change(x);
            }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)
            cout<<ch[i][j];
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：Celebrate (赞：3)

这一道题可以说是城堡的升级版，还要判断是否旋转

这是唯一一个难点

暴力也可以，但是很麻烦

优化一下：

每一个点和别的点的距离相加，一样的图形总是一样的，这个我们奥数老师好像讲过

最后判断一下，注意误差，如果是在比赛里面，就最好把带根

号的单独用数组记录下来，这样才保险点

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int cnt;//星座的大小 
	int x[210],y[210];//每一个点的坐标 
	int zuji;//祖籍，记录是哪一种星座 
	double s;//记录每一个点与别的点的距离总和 
}f[510];//记录星座 
int len,now;//len表示f的长度，now表示现在星座的数量 
int n,m;
bool a[110][110];//这个点是否有天体 
int bk[110][110];//bk记录这一个点属于哪一个f集合 
inline int _(int x){return x*x;}
inline double find(int x1,int y1,int x2,int y2)//查找距离 
{
	return sqrt(double(_(x1-x2)+_(y1-y2)));
}
inline int check(int k)
{
	int i,j;f[len].s=0.0;
	for(i=1;i<=f[k].cnt;i++) for(j=1;j<=f[k].cnt;j++) f[len].s=f[len].s+find(f[len].x[i],f[len].y[i],f[len].x[j],f[len].y[j]);//查找距离 
	for(i=1;i<k;i++)
	{
		if(fabs(f[i].s-f[k].s)<=0.00001)//如果是同一星座（不是很保险） 
		{
			return f[i].zuji;//返还 
		}
	}
	return 0;//如果没有找到，说明这是一种新的星座 
}
void dfs(int x,int y)//宽搜的数组有些麻烦，就要dfs吧，时间差不多 
{
	int t=++f[len].cnt,xx,yy;
	f[len].x[t]=x;f[len].y[t]=y;
	bk[x][y]=len;
	for(int i=-1;i<=1;i++)//周围的天体 
	{
		for(int j=-1;j<=1;j++)
		{
			if(i==j && i==0) continue;//不能是自己 
			xx=x+i;yy=y+j;
			if(xx>=1 && xx<=n && yy>=1 && yy<=m)//没有差距 
			{
				if(a[xx][yy]==true)//如果有天体 
				{
					if(bk[xx][yy]==0)//如果这个天体没有记录过 
					{
						dfs(xx,yy);//往下搜索 
					}
				}
			}
		}
	}
}
int main()
{
	int i,j,t;
	scanf("%d%d",&m,&n);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=m;j++)
		{
			scanf("%1d",&t);//仅输入一个数 
			if(t==1) a[i][j]=true;
			else	 a[i][j]=false;
		}
	}
	for(i=1;i<=n;i++)//暴力搜一遍 
	{
		for(j=1;j<=m;j++)
		{
			if(a[i][j]==true && bk[i][j]==0)//如果有天体，并且没有记录过， 
			{
				len++;//长度+1 
				dfs(i,j);//以这一个点位起点搜索一下 
				t=check(len);//检查 
				if(t==0)//如果是一种新的天体 
				{
					now++;
					f[len].zuji=now;
				}
				else
				{
					f[len].zuji=t;
				}
			}
		}
	}
	for(i=1;i<=n;i++)//输出 
	{
		for(j=1;j<=m;j++)
		{
			if(a[i][j]==false) printf("0");
			else printf("%c",f[bk[i][j]].zuji+'a'-1);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：面向大海 (赞：2)

HASH判重

我的方法可能比较奇怪

注意一定要判断截出来矩形的形状和图形内部其他图形
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 110, M = 510, dx[8] = {1, 1, 1, -1, -1, -1, 0, 0},
		  dy[8] = {-1, 0, 1, -1, 0, 1, -1, 1};
const ll key[5] = {998244353, 1004535809, 1000000007, 1000000009, 123468723167};
char s[N][N], ans[M], c = 'a';
ll ht[M][8][5];
int vis[N][N], k1[M], k2[M], k3[M], k4[M], cnt, n, m;

void dfs(int x, int y)
{
	k1[cnt] = min(k1[cnt], x);
	k2[cnt] = max(k2[cnt], x);
	k3[cnt] = min(k3[cnt], y);
	k4[cnt] = max(k4[cnt], y);
	vis[x][y] = cnt;
	s[x][y] = '0';
	for (int i = 0; i < 8; ++i)
	{
		int tx = x + dx[i], ty = y + dy[i];
		if (~tx && tx < n && ~ty && ty < m && s[tx][ty] == '1') dfs(tx, ty);
	}
}

void hash1(int k)
{
	for (int i = k1[k]; i <= k2[k]; ++i)
		for (int j = k3[k]; j <= k4[k]; ++j)
			for (int p = 0; p < 5; ++p)
				ht[k][0][p] = ((ht[k][0][p] << 1) + (vis[i][j] == k)) % key[p];
}

void hash2(int k)
{
	for (int i = k2[k]; i >= k1[k]; --i)
		for (int j = k3[k]; j <= k4[k]; ++j)
			for (int p = 0; p < 5; ++p)
				ht[k][1][p] = ((ht[k][1][p] << 1) + (vis[i][j] == k)) % key[p];
}

void hash3(int k)
{
	for (int i = k1[k]; i <= k2[k]; ++i)
		for (int j = k4[k]; j >= k3[k]; --j)
			for (int p = 0; p < 5; ++p)
				ht[k][2][p] = ((ht[k][2][p] << 1) + (vis[i][j] == k)) % key[p];
}

void hash4(int k)
{
	for (int i = k2[k]; i >= k1[k]; --i)
		for (int j = k4[k]; j >= k3[k]; --j)
			for (int p = 0; p < 5; ++p)
				ht[k][3][p] = ((ht[k][3][p] << 1) + (vis[i][j] == k)) % key[p];
}

void hash5(int k)
{
	for (int j = k3[k]; j <= k4[k]; ++j)
		for (int i = k1[k]; i <= k2[k]; ++i)
			for (int p = 0; p < 5; ++p)
				ht[k][4][p] = ((ht[k][4][p] << 1) + (vis[i][j] == k)) % key[p];
}

void hash6(int k)
{
	for (int j = k3[k]; j <= k4[k]; ++j)
		for (int i = k2[k]; i >= k1[k]; --i)
			for (int p = 0; p < 5; ++p)
				ht[k][5][p] = ((ht[k][5][p] << 1) + (vis[i][j] == k)) % key[p];
}

void hash7(int k)
{
	for (int j = k4[k]; j >= k3[k]; --j)
		for (int i = k1[k]; i <= k2[k]; ++i)
			for (int p = 0; p < 5; ++p)
				ht[k][6][p] = ((ht[k][6][p] << 1) + (vis[i][j] == k)) % key[p];
}

void hash8(int k)
{
	for (int j = k4[k]; j >= k3[k]; --j)
		for (int i = k2[k]; i >= k1[k]; --i)
			for (int p = 0; p < 5; ++p)
				ht[k][7][p] = ((ht[k][7][p] << 1) + (vis[i][j] == k)) % key[p];
}

int main()
{
	scanf("%d%d", &m, &n);
	for (int i = 0; i < n; ++i) scanf("%s", s[i]);
	memset(k1, 127, sizeof k1);
	memset(k3, 127, sizeof k3);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (s[i][j] == '1') ++cnt, dfs(i, j);
	for (int i = 1; i <= cnt; ++i)
	{
		hash1(i);
		hash2(i);
		hash3(i);
		hash4(i);
		hash5(i);
		hash6(i);
		hash7(i);
		hash8(i);
	}
	for (int i = 1; i <= cnt; ++i)
		if (!ans[i])
		{
			ans[i] = c++;
			for (int j = i + 1; j <= cnt; ++j)
				if (k2[j] - k1[j] == k2[i] - k1[i]
					|| k2[j] - k1[j] == k4[i] - k3[i]
					|| k4[j] - k3[j] == k2[i] - k1[i]
					|| k4[j] - k3[j] == k4[i] - k3[i])
					for (int k = 0; k < 8; ++k)
					{
						bool flag = true;
						for (int p = 0; p < 5; ++p)
							if (ht[i][0][p] != ht[j][k][p])
							{
								flag = false;
								break;
							}
						if (flag)
						{
							ans[j] = ans[i];
							break;
						}
					}
		}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
			putchar(ans[vis[i][j]] ? ans[vis[i][j]] : '0');
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：珅肐 (赞：2)

一道稍微有难度的广搜

广搜的部分稀松平常，个人认为难点在判重
~~（不会告诉你我判重的函数写了五六个才过）~~

大体思路是：先按求联通块的方法扫一遍-->取出联通块-->判重-->赋值

有几个小技巧：比如扫联通块的时候可以把一个联通块内的点放到一个临时数组里，判重的时候就不用再求一遍联通块，赋值也好做，再就是用map判重~~（stl简直不要太好用）~~

话不多说上代码：
```cpp
#include<iostream>
#include<ctype.h>
#include<queue>
#include<map>
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
int dx[]={-1,-1,-1,0,0,1,1,1};
int dy[]={-1,0,1,-1,1,-1,0,1};
inline int read(){//快读，可快了，虽然只有两个数我还是要用
    int x=0,f=0;char ch=getchar();
    while(!isdigit(ch))f|=ch=='-',ch=getchar();
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return f?-x:x;
}
map<long double,char> ma;//判重用（逼得我开double）
int n,m,cnt;//cnt存当前联通块的点的个数
int vis[107][107];
int zx[10007],zy[10007];//判重存坐标的临时数组
char a[107][107],c='a'-1;//c存当前的字符是什么
queue<int> qx,qy;//广搜存坐标的
char check(){//判重函数
    long double ans=0.0;
    for(int i=1;i<=cnt;++i)
        for(int j=1;j<=cnt;++j)
            ans+=sqrt((zx[i]-zx[j])*(zx[i]-zx[j])+(zy[i]-zy[j])*(zy[i]-zy[j]));
	if(!ma[ans])ma[ans]=++c;
    return ma[ans];
}
inline void lfd(int sx,int sy){//没什么特点的广搜
    qx.push(sx),qy.push(sy);cnt=1;
    zx[cnt]=sx,zy[cnt]=sy;
    vis[sx][sy]=1;
    while(!qx.empty()){
        int x=qx.front(),y=qy.front();
        qx.pop(),qy.pop();
        for(int i=0;i<8;++i){//别忘了是八联通
            int xx=x+dx[i],yy=y+dy[i];
            if(xx>0 && yy>0 && xx<=n && yy<=m && !vis[xx][yy] && a[xx][yy]=='1'){
                vis[xx][yy]=1;
                qx.push(xx),qy.push(yy);
                zx[++cnt]=xx,zy[cnt]=yy;//存下当前联通块的坐标
            }
        }
    }
    char cc=check();
    for(int i=1;i<=cnt;++i)a[zx[i]][zy[i]]=cc;//赋值
}
int main(){
    m=read();n=read();
    for(int i=1;i<=n;++i)scanf("%s",a[i]+1);
    for(int i=1;i<=n;++i)for(int j=1;j<=m;++j)if(a[i][j]=='1')lfd(i,j);
    for(int i=1;i<=n;++i,puts(""))//输出（puts真好用）
        for(int j=1;j<=m;++j)
            cout<<a[i][j];
    return 0;
}

```
再说几种不可行的判重函数
```cpp
ans+=abs(zx[i]-zx[j])+abs(zy[i]-zy[j]);
```
比如求曼哈顿距离显然是不可行的，很容易找出反例
还有这个和这个

```cpp
ans+=(zx[i]-zx[j])*(zx[i]-zx[j])+(zy[i]-zy[j])*(zy[i]-zy[j]);
```
求距离平方也是不行的
```cpp
ans+=(zx[i]-zx[j])*(zx[i]-zx[j])+(zy[i]-zy[j])*(zy[i]-zy[j])+abs(zx[i]-zx[j])+abs(zy[i]-zy[j]);
```

对把它们掺起来也不行
```
ma[(long long)ans]=1;
```
就算求了距离，最后存成long long 也是不行的
等等等等..


---

## 作者：米奇奇米 (赞：1)

```cpp
#include <bits/stdc++.h>
using namespace std;
char ss[501],KD[501][501],ch,c[501];
double ans,jay[501];
int i,j,k,ii,xx1,xx2,yy1,yy2,ii1,jj1,n,m,a[501][501],now/*星座的数量*/,sum/*这个图形有几个点*/,qx[501][10001],qy[501][10001];
const int dx[8]={-1,-1,-1,0,0,1,1,1};//横的方向
const int dy[8]={-1,0,1,-1,1,-1,0,1};//纵的方向 
double dis(int x1,int x2,int y1,int y2)//计算距离的函数（距离公式） 
{
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));//计算距离的函数（距离公式）
}
void dfs(int x,int y)//横纵坐标x,y 
{
  int i,j,ii;
  for (ii=0; ii<8; ii++)
  {
    i=x+dx[ii]; 
    j=y+dy[ii];
     if (i>0 && i<=n && j>0 && j<=m && a[i][j]==1 && KD[i][j]=='0')
      {
          KD[i][j]=ch;	
          sum++;
          qx[now][sum]=i; 
          qy[now][sum]=j;
          dfs(i,j);
     }
   }		
}

int main()
{
   freopen("star.in","r",stdin);
   freopen("star.out","w",stdout);
   now=0; 
   ch='a'-1;
   scanf("%d%d",&m,&n);
   for (i=1; i<=n; i++)
   for (j=1; j<=m; j++) 
     KD[i][j]='0';
     gets(ss);	
   for (i=1; i<=n; i++)
   {
     gets(ss);
     for (j=1; j<=m; j++)
     a[i][j]=ss[j-1]-48;//转换小写字母
    }	
    for (i=1; i<=n; i++)
    for (j=1; j<=m; j++)
      if (a[i][j]==1 && KD[i][j]=='0')
      {
        sum=1;
        now++;
        ch++;
        c[now]=ch;
        qx[now][sum]=i;
        qy[now][sum]=j;
        KD[i][j]=ch;
        dfs(i,j);
        ans=0;	
        for (ii1=1; ii1<=sum; ii1++)	
        for (jj1=1; jj1<=sum; jj1++)
        {
           xx1=qx[now][ii1]; 
           yy1=qy[now][ii1];
           xx2=qx[now][jj1]; 
           yy2=qy[now][jj1]; 
           ans=ans+dis(xx1,xx2,yy1,yy2); //计算距离 
        }
        jay[now]=ans;//储存各个星座的距离，判是否相似
        for (k=1; k<now; k++)
        if (fabs(jay[k]-jay[now])<=0.0000001)	//零不能太多，不要以为零越多越准确，要不然会爆精度 
        {
            ch--;
            c[now]=c[k];
            for (ii=1; ii<=sum; ii++)
            KD[qx[now][ii]][qy[now][ii]]=c[k];
            break;
        }
     }
  for (i=1; i<=n-1; i++)
  {
    for (j=1; j<=m; j++)
    printf("%c",KD[i][j]);//输出变化后的结果 
    puts(" ");
  }
    for (j=1; j<=m; j++)
    printf("%c",KD[n][j]);//输出变化后的结果 
    return 0;
}


```

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

首先，这样定义一个点集的有向哈希：

 - 叫点集的 $x$ 最小值为 $m_x$，$y$ 最小值为 $m_y$；
 - 构造一个序列 $[x_0-m_x,y_0-m_y,x_1-m_x,y_1-m_y,\dots]$，把这个序列随便哈希。

再定义一个点集的无向哈希：

 - 算出来 8 个哈希值：
 	1. 原点集的哈希
    2. 原点集顺时针旋转 90 度的哈希
    3. 原点集顺时针旋转 180 度的哈希
    4. 原点集顺时针旋转 270 度的哈希
    5. 原点集横坐标翻过来的哈希
    6. 原点集顺时针旋转 90 度横坐标翻过来的哈希
    7. 原点集顺时针旋转 180 度横坐标翻过来的哈希
    8. 原点集顺时针旋转 270 度横坐标翻过来的哈希
  - 无向哈希等于这八个哈希里面的最小值。

现在就很轻松了，做 dfs 来统计所有连通块的格子坐标，对所有坐标点集算出来无向哈希，用无向哈希判断两个连通块是否相同。

代码：

```cpp
// writer: w33z8kqrqk8zzzx33
#include <bits/stdc++.h>
using namespace std;
 
#define iter(i, a, b) for(int i=(a); i<(b); i++)
#define rep(i, a) iter(i, 0, a)
#define rep1(i, a) iter(i, 1, (a)+1)
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define all(a) a.begin(), a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
 
using ll=long long;
using pii=pair<int, int>;
//#define int ll
const ll MOD = 1000000000039ll;

vector<pii> dt;
ll hazh() {
    ll ans = 0;
    for(pii& v:dt) {
        ans = (ans * (157 + v.fi) + 1 + v.fi) % MOD;
        ans = (ans * (163 + v.se) + 1 + v.se) % MOD;
    }
    return ans;
}
void rotate() {
    int mxy = 0;
    for(pii& v:dt) mxy = max(mxy, v.se);
    for(pii& v:dt) {
        int ps = v.se;
        v.se = v.fi;
        v.fi = mxy-ps;
    }
    sort(all(dt));
}
void flip() {
    int mxx = 0;
    for(pii& v:dt) mxx = max(mxx, v.fi);
    for(pii& v:dt) v.fi = mxx-v.fi;
    sort(all(dt));
}
ll canonise() {
    int mx = 105, my = 105;
    for(pii& v:dt) {
        mx = min(mx, v.fi);
        my = min(my, v.se);
    }
    for(pii& v:dt) {
        v.fi -= mx;
        v.se -= my;
    }
    sort(all(dt));
    ll h1 = hazh();
    rotate();
    ll h2 = hazh();
    rotate();
    ll h3 = hazh();
    rotate();
    ll h4 = hazh();
    rotate();
    flip();
    ll h5 = hazh();
    rotate();
    ll h6 = hazh();
    rotate();
    ll h7 = hazh();
    rotate();
    ll h8 = hazh();
    return min(min(min(h1, h2), min(h3, h4)), min(min(h5, h6), min(h7, h8)));
}

map<ll, char> canon;
int n, m;
char may[105][105];
int ans[105][105];
char ltkid[505];

const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

void dfs(int x, int y, int rx, int ry, int ltk) {
    may[x][y] = '0';
    ans[x][y] = ltk;
    dt.pb({rx, ry});
    rep(d, 8) {
        int nx = x+dx[d], ny = y+dy[d];
        if(0 <= nx && nx < n && 0 <= ny && ny < m && may[nx][ny] == '1')
            dfs(nx, ny, rx+dx[d], ry+dy[d], ltk);
    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> m >> n;
    rep(i, n) rep(j, m) {
        cin >> may[i][j];
        ans[i][j] = 0;
    }
    ltkid[0] = '0';
    int ltk = 1;
    char ggg = 'a';
    rep(i, n) rep(j, m) if(may[i][j] == '1') {
        dt.clear();
        dfs(i, j, 0, 0, ltk++);
        ll hz = canonise();
        if(canon.count(hz) == 0) canon[hz] = ggg++;
        ltkid[ltk-1] = canon[hz];
    }
    rep(i, n) {
        rep(j, m) cout << ltkid[ans[i][j]];
        cout << endl;
    }
}

```

---

## 作者：herofox (赞：1)

看到没题解前来贴一份

原思路来自于NOCOW某神犇

简单说一下：

这题搜索找出星星还是非常简单的，但是如何判断是否相等是一个问题，大部分人的意思是把这部分星星弄出去翻转找和之前的是否能够重合，不过我们的神犇非常厉害想到了一个简单的办法，那就是把这个星星图形里每两个点之间的距离算出来然后比较，如果相差低于0.00001就视为相同，然后轻松AC

在此膜拜NOCOW神犇huhu1711

以下是代码

[code]
/\*
ID: herofox1

LANG: C++

TASK: starry

\*/










```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#define scan(i,j) if(map[i][j]=='1')floodfill(i,j)
using namespace std;
char map[110][110], ansmap[110][110];
int w, h;
double dissum;
double all[30];
char num;
int alpha = 0;
int coor[310][2];
int EID = 0;
inline void open()
{
    freopen("starry.in", "r", stdin);
    freopen("starry.out", "w", stdout);
}
inline void close()
{
    fclose(stdin);
    fclose(stdout);
}
inline bool eq(double a, double b)
{
    double abss;
    if(a>b)
        abss=a-b;
    else
        abss=b-a;
    if(abss<=0.00001)
        return true;
    else
        return false;
}
inline void floodfill(int x, int y)
{
    map[x][y] = '0';
    coor[++EID][0] = x;
    coor[EID][1] = y;
    scan(x+1,y);
    scan(x+1,y-1);
    scan(x+1,y+1);
    scan(x,y+1);
    scan(x,y-1);
    scan(x-1,y);
    scan(x-1,y-1);
    scan(x-1,y+1);
}
inline double dis(int a, int b)
{
    return sqrt(((coor[a][0] - coor[b][0])*(coor[a][0] - coor[b][0])) + ((coor[a][1] - coor[b][1])*(coor[a][1] - coor[b][1])));
}
inline void scanff()
{
    scanf("%d%d", &w, &h);
    for(int i = 1;i <= h;++i)
        for(int j = 1;j <= w;++j)
            cin>>map[i][j];
}
inline void print()
{
    for(int i = 1;i <= h;++i)
    {
        for(int j = 1;j <= w;++j)
        {
            if(ansmap[i][j] < 'a' || ansmap[i][j] > 'z')
                cout<<"0";
            else
                cout<<ansmap[i][j];
        }
        cout<<endl;
    }
}
inline void solve()
{
    for(int i = 1;i <= h;++i)
        for(int j = 1;j <= w;++j)
            if(map[i][j] == '1')
            {
                dissum = 0;
                EID = 0;
                floodfill(i, j);
                for(int k = 1;k <= EID;k++)
                    for(int p = k + 1;p <= EID;p++)
                        dissum += dis(p, k);
                bool flag = 0;
                for(int k = 1;k <= alpha;++k)
                {
                    if(eq(dissum, all[k]))
                    {
                        num = 'a' + k - 1;
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    all[++alpha] = dissum;
                    num = alpha + 'a' - 1;
                }
                for(int k = 1;k <= EID;++k)
                    ansmap[coor[k][0]][coor[k][1]] = num;
            }
}
int main()
{
    //open();
    scanff();
    solve();
    print();
    //close();
    return 0;
}
```
[/codec]
祝大家愉快地AC


---

## 作者：Drinkwater (赞：0)

这题其实没有楼下说的那么麻烦，我们只要用距离表示一个图就好了，一个图相似当且仅当每个点与其他点的距离和相同，这样我们先DFS处理出每个图，算出距离和，然后就好了。












```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
int n,m;
char a[110][110];
int cnt,vis[110][110];
map<double,int>mp;
map<int,double>num;
double dis;
double get_dis(int x1,int y1,int x2,int y2)
{
    return sqrt((x1-x2) * (x1-x2) + (y1-y2) * (y1-y2));
}
struct T
{
    int l,r;
}q[100000];
int ff;
void dfs(int x,int y)
{
    if(vis[x][y])return ;
    if(x < 1 || x > n || y < 1 || y > m || a[x][y] != '1')return ;
    vis[x][y] = 1;
    q[++ff].l = x,q[ff].r = y;
    //cout<<x<<" "<<y<<endl;
    dfs(x-1,y);dfs(x+1,y);dfs(x,y+1);dfs(x,y-1);
    dfs(x-1,y+1);dfs(x-1,y-1);dfs(x+1,y+1);dfs(x+1,y-1);
}
void pre_hand()
{
    REP(i,1,ff)
    {
        REP(j,1,ff)
        {
            if(i == j)continue;
            dis+=get_dis(q[i].l,q[i].r,q[j].l,q[j].r);
        }
    }
}
void change(int x)
{
    REP(i,1,ff)a[q[i].l][q[i].r] = char(x + 'a'-1);
}
int pd()
{
    REP(i,1,cnt)
    {
        double ans = abs(num[i] - dis);
        if(ans <= 1e-3)return i;
    }
    num[++cnt] = dis;
    return cnt;
}
int main()
{
    m = read(),n = read();
    REP(i,1,n)
        scanf("%s",a[i]+1);
    REP(i,1,n)
    {
        REP(j,1,m)
        {
            if(a[i][j] == '1' && !vis[i][j])
            {
                memset(q,0,sizeof(q));
                dis = 0;ff = 0;
                dfs(i,j);pre_hand();
                change(pd());
            }
        }
    }
    //cout<<"!!!"<<cnt<<endl;
    //REP(i,1,cnt)cout<<num[i]<<endl;
    REP(i,1,n)
    {
        REP(j,1,m)
            cout<<a[i][j];
        cout<<endl;
    }
    return 0;
}
```

---

