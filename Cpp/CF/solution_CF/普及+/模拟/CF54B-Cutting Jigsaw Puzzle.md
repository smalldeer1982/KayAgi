# Cutting Jigsaw Puzzle

## 题目描述

## 题目翻译
刺猬最近记得他最喜欢的童年活动之一 - 解决谜题，并以新的活力进入它。他每天都会和他的朋友一起坐在成千上万的小片中，一个接一个地寻找所需物品。

不久，刺猬想出了一个绝妙的主意：不是购买现成的拼图，而是可以将自己的大纸张带上一些图片并将其切成许多小矩形块，然后将它们混合并解决由此产生的拼图，试图拼凑图片。由此产生的任务比经典谜题更具挑战性：现在所有碎片都具有相同的矩形形状，并且可以仅依靠在碎片上绘制的图片来组装谜题。

所有拼图都是相同的尺寸 X×Y，因为图像首先通过水平切割以间距切割 X X，然后垂直切割，间距为 Y。如果我们将图片的初始大小表示为 A×B，然后 一个 A必须可被整除X和B必须可被整除Y（X和Y是整数）。

然而，并非每次切割图片都会产生很好的拼图。刺猬发现一个谜题很好，如果其中没有两个相同（比较它们时允许旋转它们，但是禁止将它们翻过来）。

你的任务是计算给定图片你可以从中制作的好谜题的数量，并找到最小尺寸的谜题。

## 样例 #1

### 输入

```
2 4
ABDC
ABDC
```

### 输出

```
3
2 1
```

## 样例 #2

### 输入

```
2 6
ABCCBA
ABCCBA
```

### 输出

```
1
2 6
```

# 题解

## 作者：Mint_Flipped (赞：2)

~~wa 无数发 原因竟然是自己编写的函数函数使用不规范~~

题目意思大致就是：判断分割后图片，经旋转后，是否重复，求出可用解的个数，以及最小解。

按题意先模拟分割，利用hash来判断是否重复。

简述下hash：h = h * base + s[ i ] [ j ] - ' a ' ,得到每个拼图的hash值，利用STLmap来记录下是否出现即可。

PS：当分割的长宽相等时，可以旋转4个方向。不等时，只能选择2个方向。

代码如下：

```c
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) (a&(-a))
#define fir(a) a->first 
#define sec(a) a->second 
const int inf=0x3f3f3f3f;
const int maxn=1e5+5;
const int mod=1e9+7;
const double eps=1e-6;
int n,m,k,t,a[maxn];
int base=131,ans,ansx,ansy;
bool flag;
unsigned long long h1,h2,h3,h4;
map <unsigned long long,bool> mp;
char s[25][25];
void check(int x,int y){
    mp.clear();
    if(x==y)
    flag=1;
    else
    flag=0;
    for(int i=1;i<=n;i+=x){
        for(int j=1;j<=m;j+=y){
    h1=0,h2=0,h3=0,h4=0;
    int l1=i,l2=i+x-1,r1=j,r2=j+y-1;
    for(int ii=l1;ii<=l2;++ii){
        for(int jj=r1;jj<=r2;++jj)
        h1=h1*base+s[ii][jj]-'a';
    }
    for(int ii=l2;ii>=l1;--ii){
        for(int jj=r2;jj>=r1;--jj)
        h2=h2*base+s[ii][jj]-'a';
    }
    if(flag){
    for(int ii=r1;ii<=r2;++ii){
        for(int jj=l2;jj>=l1;--jj)
        h3=h3*base+s[jj][ii]-'a';
    }
    for(int ii=r2;ii>=r1;--ii){
        for(int jj=l1;jj<=l2;++jj)
        h4=h4*base+s[jj][ii]-'a';
    }
    }
    if(flag){
        if(mp[h1]||mp[h2]||mp[h3]||mp[h4])
        return ;
        mp[h1]=mp[h2]=mp[h3]=mp[h4]=1;
    }
    else{
        if(mp[h1]||mp[h2])
        return ;
        mp[h1]=mp[h2]=1;
    } 
        }
    }
    ans++;
    if(ansx==0||x*y<ansx*ansy)
    ansx=x,ansy=y;
}
int main()
{
    scanf("%d%d",&n,&m);
    fo2(i,n){
        fo2(j,m)
        cin>>s[i][j];
    }
    fo2(i,n){
        fo2(j,m){
            if(n%i==0&&m%j==0)
            check(i,j);
        }
    }
    printf("%d\n%d %d\n",ans,ansx,ansy);
    return 0;
}
```


---

## 作者：ncwzdlsd (赞：0)

这道题主要对字符串有两个操作：取块+旋转。

1. 取块
	
	这个比较简单，双重循环枚举 $a$ 和 $b$，如果 $a$ 或 $b$ 不能被 $N$ 或 $M$ 整除，就要`continue`。

2. 旋转
	
	可以旋转 $90$、$180$、$270$ 度，需要根据图形种类分情况讨论一下：如果是长方形，只用考虑旋转 $180$ 度的情况，因为旋转 $90$ 度或 $270$ 度不可能一样；如果是正方形，几种旋转都要考虑。
    
   简单的举例之后，我们就可以找到旋转操作的规律。
    
	旋转操作的代码如下：
    
    - $90$ 度
    ```cpp
    for (int yy=0;yy<j;yy++)
    	for (int xx=i-1;xx>=0;xx--)
			pc+=gg[x+xx][y+yy];
    ```
    - $180$ 度
    ```cpp
    for (int xx=i-1;xx>=0;xx--)
		for (int yy=j-1;yy>=0;yy--)
			pc+=gg[x+xx][y+yy];
    ```
    - $270$ 度
    ```cpp
    for (int yy=j-1;yy>=0;yy--)	
		for (int xx=0;xx<i;xx++)
			pc+=qwq[x+xx][y+yy];
    ```

小技巧：我们可以使用STL中的`set`存储字符串，便于实现去重操作以进行判断。

代码就不给了，几种操作组合一下就可以啦！

---

## 作者：youdu666 (赞：0)

## 思路：哈希

### 题意翻译：

给你一个 $n*m$ 的拼图，让你求所有块的长、宽都相等并且所有块在旋转后都不同的方案数和最优解。

### 思路简述

拿到 $n$ 和 $m$ 先处理出这两个数字的所有因数，随后用因数的组合来计算。

拿到一个左上角点的坐标和右下角点的坐标，简单地用高进制数和取模来计算任意一个方块的哈希值。当该方块为正方形时，需要计算四种方向的哈希值；若为普通长方形，则只需要计算上下翻转。计算完后扔进 STLmap 里并判断是否有重复。记得要先计算完所有方向的哈希值再扔。

### 代码

```
#include<bits/stdc++.h>
#define int long long
#define mo 1145141919810111
#define base 131
//自定义模数和进制
using namespace std;
inline int read()
{
    int x=0,y=1;
    char c=getchar();
    while(c>'9'||c<'0')
    {
        if(c=='-')
            y=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x*y;
}
const int N=25;
int c[N][N];
int n,m,ansx,ansy,ans;
int gn[N],gnn,gm[N],gmn;//这两个数组用来记录因数
map<long long,bool> mp;
inline bool hsh(int xa,int ya,int xb,int yb)
{
    int ans=0,ans2=0,ans3=0,ans4=0;
    for(int i=xa;i<=xb;i++)
        for(int j=ya;j<=yb;j++)
        {
            ans=(ans*base)%mo;
            ans=(ans+c[i][j])%mo;
        }
    if(mp[ans]) return false;
    //正方向的哈希
    for(int i=xb;i>=xa;i--)
        for(int j=yb;j>=ya;j--)
        {
            ans2=(ans2*base)%mo;
            ans2=(ans2+c[i][j])%mo;
        }
    if(mp[ans2]) return false;
    //反方向，下同
    if(xb-xa!=yb-ya)//若不是正方形则不用再算了，直接退出
    {
        mp[ans]=true;
        mp[ans2]=true;
        return true;
    }

    for(int j=yb;j>=ya;j--)
        for(int i=xa;i<=xb;i++)
        {
            ans3=(ans3*base)%mo;
            ans3=(ans3+c[i][j])%mo;
        }
    if(mp[ans3]) return false;

    for(int j=ya;j<=yb;j++)
        for(int i=xb;i>=xa;i--)
        {
            ans4=(ans4*base)%mo;
            ans4=(ans4+c[i][j])%mo;
        }
    if(mp[ans4]) return false;
    mp[ans]=true;
    mp[ans2]=true;
    mp[ans3]=true;
    mp[ans4]=true;
    return true;
}
inline void chkans(int x,int y)
{//找到一组可行解
    ans++;
    if(x*y<ansx*ansy)
        ansx=x,ansy=y;
    else if((x*y==ansx*ansy)&&(x<ansx))
        ansx=x,ansy=y;
}
inline void init(void)
{//对n,m进行处理
    for(int i=1;i<=n;i++)
        if(n%i==0)
            gn[++gnn]=i;
    for(int i=1;i<=m;i++)
        if(m%i==0)
            gm[++gmn]=i;
    ansy=ansx=2e9;
}
signed main()
{
    n=read(),m=read();
    init();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            char t=getchar();
            if(t>'Z'||t<'A') t=getchar();
            c[i][j]=(t-'A'+1);
        }
    for(int i=1;i<=gnn;i++)
        for(int j=1;j<=gmn;j++)
        {
            int kx=n/gn[i],ky=m/gm[j];
            mp.clear();
            bool ok=true;
            for(int u=1;u<=n&&ok;u+=kx)
                for(int p=1;p<=m;p+=ky)
                    if(!hsh(u,p,u+kx-1,p+ky-1))
                    {
                        ok=false;
                        break;
                    }
            if(ok)
                chkans(kx,ky);
        }
    printf("%lld\n",ans);
    printf("%lld %lld\n",ansx,ansy);
}
```


---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
有一个 $n\times m$ 的字符串矩形，你可以指定一个大小 $(x,y)$，然后把矩形分割成 $\dfrac{n}{x}\times \dfrac{m}{y}$ 个小矩形（$x|n,y|m$），若所有的小矩形（**可以旋转，但不能翻转**）后均互不相同，则称这种分割是合法的.  
求合法 分割的方案总数以及子矩形最小的分割方案.  
$n,m\le20$.
## $\text{Solution}$
一道复杂度怎么做应该都太不可能 TLE 的模拟题.  
手玩出旋转对坐标的映射关系.  
分别枚举因数暴力哈希 check 即可.  
时间复杂度大概是 $O(n^3)$.
## $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
//#define double long double
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=2e5+100;
const int mod=1e9+7;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m,k;
char s[25][25];
int key=31;
struct node{
  char a[25][25];
  inline ull calc(){
    ull res(0);
    for(int i=1;i<=n;i++){
      for(int j=1;j<=m;j++) res=res*key+a[i][j]-'A'+1;
    }
    return res;
  }
}now,pre,w[6];
map<ull,int>mp;
int mn,x,y,res,num;
bool work(int a,int b,int x,int y){
  //memset(now.a,0,sizeof(a));
  num=0;
  for(int i=1;i<=max(n,m);i++){
    for(int j=1;j<=max(n,m);j++) now.a[i][j]=0;
  }
  for(int i=1;i<=x;i++){
    for(int j=1;j<=y;j++){
      //printf("  %d %d c=%c\n",a+i-1,b+j-1,s[a+i-1][b+j-1]);
      now.a[i][j]=s[a+i-1][b+j-1];
    }
  }
  /*printf("(%d %d)\n",a,b);
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++) printf("%c",now.a[i][j]?now.a[i][j]:'0');
    putchar('\n');
  }
  printf("calc=%llu\n",now.calc());*/
  if(mp[now.calc()]) return false;
  w[++num]=now;
  for(int o=1;o<=3;o++){
    memcpy(pre.a,now.a,sizeof(now.a));
    for(int i=1;i<=max(n,m);i++){
      for(int j=1;j<=max(n,m);j++) now.a[i][j]=0;
    }
    for(int i=1;i<=x;i++){
      for(int j=1;j<=y;j++){
	//printf("  (%d %d)-> (%d %d)\n",i,j,j,x-i+1);
	now.a[j][x-i+1]=pre.a[i][j];
      }
    }
    swap(x,y);    
    if(o==2||x==y){
      /*for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++) printf("%c",now.a[i][j]?now.a[i][j]:'0');
	putchar('\n');
      }
      printf("calc=%llu\n",now.calc());
      */
      if(mp[now.calc()]) return false;
      w[++num]=now;
    }
  }
  for(int i=1;i<=num;i++) mp[w[i].calc()]=1;
  return true;
}
bool check(int x,int y){
  //printf("\nx=%d y=%d\n",x,y);
  mp.clear();
  for(int i=1;i<=n;i+=x){
    for(int j=1;j<=m;j+=y){
      if(!work(i,j,x,y)) return false;
    }
  }
  return true;
}
signed main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
  #endif
  n=read();m=read();
  mn=2e9;
  for(int i=1;i<=n;i++){
    scanf(" %s",s[i]+1);
  }
  for(int i=1;i<=n;i++){
    if(n%i) continue;
    for(int j=1;j<=m;j++){
      if(m%j) continue;
      if(check(i,j)){
	++res;
	//printf("------------ok! (%d %d)\n",i,j);
	if(mn>i*j){
	  mn=i*j;x=i;y=j;
	}
      }
    }
  }
  printf("%d\n%d %d\n",res,x,y);
  return 0;
}
/*

*/

```


---

## 作者：xzy__xzy (赞：0)

模拟 

注意，比较两块拼图是否相同，允许旋转它们，但是禁止将它们翻过来

具体操作见代码

我们可以使用map来映射，这样比较的时候较简单 

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define Rep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int inf=0x3f3f3f3f;
int a,b,t,mj=inf,ansx=inf,ansy,q;
string p[405*10];
char s[23][23];
void check(int x,int y)
{
	t=0;
	for(int i=1;i<=4000;i++) p[i]="";
	int gx=a/x,gy=b/y;
	For(i,1,gx)
	{
		For(j,1,gy)
		{
			int Lx=(i-1)*x+1,Rx=i*x;
			int Ly=(j-1)*y+1,Ry=j*y;
			t++;
			For(st,Lx,Rx)
			{
				For(ed,Ly,Ry)
				{
					p[t]+=s[st][ed];
				}
			}
			t++;
			Rep(st,Rx,Lx)
			{
				Rep(ed,Ry,Ly)
				{
					p[t]+=s[st][ed];
				}
			}
			if(x==y)
			{
				t++;
				Rep(ed,Ry,Ly)
				{
					For(st,Lx,Rx)
					{
						p[t]+=s[st][ed];
					}
				}
				t++;
				For(ed,Ly,Ry)
				{
					Rep(st,Rx,Lx)
					{
						p[t]+=s[st][ed];
					}
				}
			}
		}
	}
	int f=0;
	if(x!=y)
	{
		For(i,1,t)
		{
			For(j,1,t)
			{
				if(p[i]==p[j]&&((i-1)/2)!=((j-1)/2))
				{
					f++;
					break;
				}
			}
		}
	}
	else
	{
		For(i,1,t)
		{
			For(j,1,t)
			{
				if(p[i]==p[j]&&((i-1)/4)!=((j-1)/4))
				{
					f++;
					break;
				}
			}
		}
	}
	if(!f)
	{
		q++;
		if(x*y<mj) mj=x*y,ansx=x,ansy=y;
		else if(x*y==mj)
		{
			if(x<ansx)
			{
				ansx=x,ansy=y;
			}
		}
	}
}
int main()
{
	cin>>a>>b;
	for(int i=1;i<=a;i++)
	   for(int j=1;j<=b;j++)
	      cin>>s[i][j];
	For(i,1,a)
	{
		For(j,1,b)
		{
			if(a%i==0&&b%j==0)
			{
				check(i,j);
			}
		}
	}
	if(q) cout<<q<<endl<<ansx<<" "<<ansy;
	return 0;
}
```


---

