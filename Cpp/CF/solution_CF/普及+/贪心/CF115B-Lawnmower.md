# Lawnmower

## 题目描述

你有一个完全由草和杂草组成的花园。你的花园是一个 n×m的网格。每个方格有一对坐标（r，c）表示单元格位于r行c列。每个方格可能有草或杂草。例如，一个4×5的花园可能如下（空单元格表示草）：
![](https://cdn.luogu.org/upload/vjudge_pic/CF115B/593291ddc8205e086d1d9f0caee6daf221cd4d06.png)

你有一台割草机可以割除所有的杂草。最初，你站在花园的左上角。也就是说，在方格（1,1）处。在任何时刻，你都面临着某个方向——左或右。最初，你面对右。

在一个步骤中，您可以执行以下任一操作：

1. 沿您面向的方向移动一个单元格。

- 如果你面向右：从方格（r，c ）移动到方格（r，c + 1 ） 
![](https://cdn.luogu.org/upload/vjudge_pic/CF115B/f511b6ec3d5ee7e9c4711b72b12f3f163a26b1cb.png)

- 如果你面向左：从方格（r，c ）移动到方格（r，c - 1 ） 
![](https://cdn.luogu.org/upload/vjudge_pic/CF115B/817d99d95ad6751bb75b016614c67edbc38bc05f.png)

2) 向下移动一格（即从（r，c ）移动到方格（r + 1，c ）中），并将你的方向改为相反的方向.
- 如果你面向右，你将面向左
![](https://cdn.luogu.org/upload/vjudge_pic/CF115B/eaac793c8ad146f5aa886c6e03e5682029ae2d0f.png)

- 如果你面向左，你将面对右
![](https://cdn.luogu.org/upload/vjudge_pic/CF115B/0279ba704667c612234f39ddc6d6e73ff67745d6.png)

您不得离开花园。如果你和你的割草机站在含有杂草的方格中（你的方向无关紧要），杂草就会被修剪掉。此操作不算作动作。

割除所有杂草所需的最小移动次数是多少？

------------

## 样例 #1

### 输入

```
4 5
GWGGW
GGWGG
GWGGG
WGGGG
```

### 输出

```
11
```

## 样例 #2

### 输入

```
3 3
GWW
WWW
WWG
```

### 输出

```
7
```

## 样例 #3

### 输入

```
1 1
G
```

### 输出

```
0
```

# 题解

## 作者：_xcc_ (赞：6)

~~Cf的数据果然毒瘤, 一百多个点, 卡了我一晚上...~~

写这道题的一点人生经验 :
- 细节题关键是一开始就要思路清晰, 把情况考虑全, 不能找到一个hack数据改一下, ~~改着改着代码就成屎了~~

- 实在是找不到错因就别找了, 直接重构还快得多.

这个题要注意的细节有:

- [√] 可能有空行, j最左边的草 = j最右边的草=0, 导致爆炸

- [√] 未考虑中间空多行的情况, 引用了空行(i-1 , i+1等)的草坐标(0),  导致爆炸

- [√] 最后几行都没有草, 还是跳到了最后一行,  导致爆炸

- [√] 没严格执行奇数行只能向右走, 偶数行只能向左走,  导致爆炸

......

~~打钩表示我踩过这个坑~~

**解决方法**: 记录当前人的位置, 发现草再跳, 跳的时候在算距离(曼哈顿距离), 要跳到下一行前分需不需要在上一行跳额外的步数防止逆行两种情况 

```
#include<cstdio>
#define re register
#define in inline
int n,m;
char a[151][151];
int e[151][2];
in int abs(int x)
{
    return x>0?x:-x;
}
in int dis(int x1,int y1,int x2,int y2)
{
    return abs(x1-x2)+abs(y1-y2);
}
signed main()
{
    scanf("%d%d",&n,&m);
    for(re int i=1;i<=n;++i)
    {
        scanf("%s",a[i]+1);
        for(re int j=1;j<=m;++j)
        {
            if(a[i][j]=='W'){
                if(!e[i][0]) e[i][0]=j;
                e[i][1]=j;
            }
        }
    }//e[i][0]第i行最左边草的坐标, e[i][1]最右边的草
    int ans=0,nx=1,ny=1;//nx, ny: 当前位置
    if(e[1][0]) {ans+=dis(nx,ny,1,e[1][1]);ny=e[1][1];}
    for(re int i=1;i<n;++i)
    {
        if(!e[i+1][0]) continue;
        if(i&1){
            if(e[i+1][1]>=ny){
                ans+=dis(nx,ny,i+1,e[i+1][1]);//防止下一行逆行走的额外步数
                nx=i+1,ny=e[i+1][1];
                ans+=dis(nx,ny,i+1,e[i+1][0]);
                nx=i+1,ny=e[i+1][0];
            }
            else{
                ans+=dis(nx,ny,i+1,e[i+1][0]);
                nx=i+1,ny=e[i+1][0];
            }
        }
        else{
            if(e[i+1][0]<=ny){
                ans+=dis(nx,ny,i+1,e[i+1][0]);//防止下一行逆行走的额外步数
                nx=i+1,ny=e[i+1][0];
                ans+=dis(nx,ny,i+1,e[i+1][1]);
                nx=i+1,ny=e[i+1][1];
            }
            else{
                ans+=dis(nx,ny,i+1,e[i+1][1]);
                nx=i+1,ny=e[i+1][1];
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：2simon2008 (赞：4)

## 思路

这道题思路挺简单的，其实就是模拟。对于每一行，我先把这一行的草除完（不能上去），然后考察下一行的第一个杂草，可能还要走一段路（因为下去就改变方向了），走到那个杂草上面，再下一行。

注：下一行第一个杂草指的是你下一行所走方向的第一个。e.g.第二行的第一个杂草其实是左数最后一个，右数第一个杂草。

## 优化

你可以记录每一行最左和最右的杂草，以便计算和判断。

此外，如果结尾有空行，你不用再往下走。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,l[155],r[155],k=0,nowx=1,cnt,maxn;
char ch;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++){
	  for(int j=1;j<=m;j++){
	  	ch=getchar();
		while(ch!='G'&&ch!='W')
			ch=getchar();  //读入字符
	  	if(ch=='W'){
	  		if(l[i]==0) l[i]=j;
	  		r[i]=j;
		  } //存储最左边和最右边的杂草 
	  }
	  if(r[i]) maxn=i;//更新杂草最后的一行
    }//输入并存储 
    for(int i=1;i<=maxn;i++){
    	k=1-k;//改方向 
    	if(k==1){//如果向右走 
		  if(r[i]){
		    cnt+=r[i]-nowx;//除光这一行的草 
    	    nowx=r[i];//现在位置更新 
		  }
    	  if(r[i+1]&&r[i+1]>nowx) cnt+=r[i+1]-nowx,nowx=r[i+1];
		  //因为下一行只能往左走，所以要走到下一行最右边那一个（或他的更右边） 
    	  if(i!=maxn) cnt++;
        }
        else {//如果向左走，同向右走 
          if(l[i]){
		    cnt+=nowx-l[i];//除光草 
    	    nowx=l[i];//走过去
          }
    	  if(l[i+1]&&l[i+1]<nowx) cnt+=nowx-l[i+1],nowx=l[i+1];
		  //走到下一行最左边的那一个（或更加左边） 
		  if(i!=maxn) cnt++;
        }
	}
	cout<<cnt<<endl;//输出 
	return 0;
}
```

------------
**完结撒花！**


---

## 作者：cqbztz2 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF115B)

# 思路：

本题比较水，直接贪心模拟就好了。

　题意就是从 $ (1,1) $ 出发，最少需要多少步能除完草（即 W），而每次移动的方向已经确定了，当i为奇数则第i行的方向为 $ 1→m $，否则为 $ m→1 $，每次下移必须转变到所到行的方向上。

　只需要记录一下每一行中草的位置，然后按行的方向模拟找到两边界（要么是一行草的开头位置，要么是结尾位置，具体由该行的方向确定），然后直接算曼哈顿距离，求和就解决了。
 
 # 代码：
 
 ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int n,m,a[155][155],ans,x=1,y=1;
  char s;
  int main(){
      cin>>n>>m; 
      for(int i=1;i<=n;i++){
          for(int j=1;j<=m;j++){
              cin>>s;
              if(s=='W'){
                  a[i][0]++;
                  a[i][a[i][0]]=j;
              }
          }
      }
      for(int i=1;i<=n;i++) {
          if(i&1){
              if(a[i][0]){
                  ans+=((abs(i-x)+abs(a[i][1]-y))+(abs(a[i][a[i][0]]-a[i][1])));
                  x=i;
                  y=a[i][a[i][0]];
              }
          }
          else{
              if(a[i][0]){
                  ans+=((abs(i-x)+abs(a[i][a[i][0]]-y))+(abs(a[i][a[i][0]]-a[i][1])));
                  x=i;
                  y=a[i][1];
              }
          }
      }
      cout<<ans;
      return 0;
  }
```


---

## 作者：Tony_Peter (赞：2)

这道题目就是贪心啦，很简单的，我直接放代码吧，有注解的QWQ
```cpp
#include<bits/stdc++.h>
#define go(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
const int N=152;
int n,m;
int l[N],r[N],num[N],s[N];
int f[N];
char c[N][N];
int main(){
	//freopen("Lawnmower.in","r",stdin);
	//freopen("Lawnmower.out","w",stdout);
	scanf("%d%d",&n,&m);
	go(i,1,n){
		l[i]=r[i]=1;
		getchar();
		go(j,1,m)
			c[i][j]=getchar();
	}
	int end=1;
	go(i,1,n){
		bool q=1;
		go(j,1,m)
			if(c[i][j]=='W'){
				if(q) l[i]=j,q=0;
				r[i]=j;//l,r分别记录每一行最左和最右边的杂草的位置
				end=i;//end记录有杂草的最后一行是哪一行
				num[i]++;//num记录本行杂草数量,用于特判本行是否有杂草
			}
		s[i]=r[i]-l[i];
//预处理最左和最右杂草的距离,因为后面会改变l,r的值
	}
	if(num[1]) f[1]=l[1]-1;
//注意一下这里因为起点在(1,1)所以要先走到最左边的杂草所在位置
	int x=0;//x用于记录每两行之间要移动的距离
	go(i,1,n){
		f[i]+=f[i-1]+x+s[i];//f[x]记录清除完x行杂草需要的最短时间
		if(i==end) break;//后面没有杂草了就结束
		if(i%2){//如果是奇数行就往右走
			if(num[i+1]) x=abs(r[i]-r[i+1])+1;
//注意这里要特判,如果下一行有杂草要除的话,就要移动到下一行的最右边的杂
//草,因为下一行是偶数行向左走的
			else x=1,l[i+1]=r[i];
//如果下一行没有,就直接下去,相当于忽略中间这一行,把这一行的上下两行靠
//到一起,但要注意方向
		}
		else{
			if(num[i+1]) x=abs(l[i]-l[i+1])+1;
			else x=1,r[i+1]=l[i];
		}
	}
	printf("%d\n",f[end]);
	return 0;
}

```

---

## 作者：_Lemon_ (赞：2)

我们发现,zzd 他不能后退,不能向上走。于是我们有一种解法,每次从1走到m,
或者从 m 走到1,我们发现这样是一定可行的,因为这样遍历了全地图,但不是最优的。我
们发现,在一行只有一个固定的方向。于是我们可以贪心的走。
即若方向向右,那么我们走到当前行与下一行最远(相对第一个)的一个W处。若方
向向左,那么我们走到当前行与下一行最近的一个 w 处。考虑为什么,因为在一行中,若
zzd 前后都有 W,那这一定是无解的(zzd 在一行中只能走一个方向).
在这题,贪心的策略是很容易想到的,正确性也易知。但关键点在于特殊情况的特判。
考虑那些形形色色的特殊情况:


1:连续两行空的(没有 w)


2:无需走到最后一行


3:第i行为空,第i+1行不为空



这些情况自己想一想即可,并不难。


```
#include<bits/stdc++.h>
using namespace std;
int l[505],r[504],Map[505][505],n,m;
int distance(int x,int y,int a,int b)
{
    return abs(x-y)+abs(a-b);
}
int main()
{
    char c;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int flag=1;
        for(int j=1;j<=m;j++)
        {
            cin>>c;
            if(c!='G') Map[i][j]=1;
            if (Map[i][j]) 
            {
                r[i]=j;
                if (flag) {flag=0; l[i]=j;}
            }
        }
    }
    int k=1,ans=0,X=1,Y=1;
    for (int i=1;i<=n;++i) 
    {
        if (k&&l[i]&&r[i])
        {
            ans+=distance(i,X,l[i],Y)+r[i]-l[i];
            X=i;
            Y=r[i];
        }
        else if (l[i]&&r[i])
        {
            ans+=distance(i,X,r[i],Y)+r[i]-l[i];
            X=i;
            Y=l[i];
        }
        k=!k;
    }
    cout<<ans<<endl;
}
```

---

## 作者：fls233666 (赞：1)

要求最少的步数，可以考虑**贪心**算法。

我们发现，在除掉一行的草的过程中，你是无法换方向的。由此，我们记录每一行最左边和最右边的草位置，在进入下一行之前作好调整。然后，在每一行都不多走，除完这一行调整完位置后就到下一行。这样就能保证最优解。

另外，本题实现时还有很多细节要注意。具体可以归纳为两点：

- 关于没有草的空行特判问题。
- 不用走到花园的最后一行，可以中途结束。

针对上面两点，本人构造了一个小数据，可以帮助你查错：

	7 1
    G
    G
    W
    G
    G
    W
    G

上面这组数据的答案是 $5$。~~【成功地把我 AC 前的代码卡掉了】~~

下面放出本人的 AC 代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;
int l[155],r[155];
int main(){

	int n,m,dn=1,ans=0;
	char c;
   //dn记录有草的行的最大编号
    
	scanf("%d%d",&n,&m);
	for(rgt i=1;i<=n;i++){
		for(rgt j=1;j<=m;j++){
        
			c=getchar();
			while(c!='G'&&c!='W')
				c=getchar();  //读入字符
                
			if(c=='W'){  //如果是草
				if(!l[i])  //记录最左边的草的位置
					l[i]=j;
				r[i]=j;   //更新最右边的草的位置
			}
            
		}
		if(l[i]){  //如果这行有草
			dn=i;  //更新dn
		}
	}
    
	for(rgt w=1,i=1;i<=dn;i++){
		if(i&1){  //由题可知：奇数行朝右，偶数行朝左
        //朝右
			if(r[i]){  //如果当前行不是空行，除草
				ans+=r[i]-w;
				w=r[i];
			}
            
			if(i<dn){  //如果当前行不是有草的最后一行
				if(r[i+1]&&r[i+1]>w){  //如果下一行不是空行，调整位置
					ans+=r[i+1]-w;
					w=r[i+1];
				}
                                //进入下一行
				ans++;
			}
		}else{
        //朝左，下面代码与上面类似
			if(l[i]){
				ans+=w-l[i];
				w=l[i];
			}
			if(i<dn){
				if(l[i+1]&&l[i+1]<w){
					ans+=w-l[i+1];
					w=l[i+1];
				}
				ans++;
			}
		}
	}
    
	printf("%d",ans);  //输出答案
	return 0;
}
```


---

## 作者：LKY928261 (赞：1)

## 题目分析

本人看了其他大佬们的题解，发现几乎所有人都是贪心做的。但本人则是直接求哈顿曼距离过的，根本没用到贪心，而且还避开了不少坑。

首先，根据题意，人在向下走后就不能再向上走。因此，我们可以按行来分别计算。

通过观察我们发现，在不同行的两个格点间行走的最短路长度就是曼哈顿距离，而我们要控制的，就只有同一行内的走向了。

具体如下：

- 若在只能向右走的行，则按列从小到大搜索

- 若在只能向左走的行，则按列从大到小搜索

## 参考代码

本人的代码非常精简，欢迎借(chao)鉴(xi)。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,x,y,i,j;string a;bool f;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(i=0;i<n;i++,f=!f){
		cin>>a;
		if(f)for(j=m-1;j>=0;j--){if(a[j]=='W')s+=abs(x-i)+abs(y-j),x=i,y=j;}
		else for(j=0;j<m;j++)if(a[j]=='W')s+=abs(x-i)+abs(y-j),x=i,y=j;
		//求曼哈顿距离
	}
	cout<<s<<"\n";
	//本人从不打return 0;
}
```

---

## 作者：Argon_Cube (赞：0)

- **【题目链接】**

[Link:CF115B](https://www.luogu.com.cn/problem/CF115B)

- **【解题思路】**

**1.确定贪心策略。**

既然题目标签都是贪心，那就打贪心代码。

显然最优解应该是这样：对于每一次移动，移动到下一行第一块杂草或本行最后一块杂草，看哪一个的列号离你的位置最远。

注意这里第一块杂草和最后一块杂草都是相对于本行你所面对的方向。

**2.对特殊情况的处理。**

特殊情况：空行（没有杂草的一行）。

如果空行在中间，那么可以按照平常的方式处理，但是要加一些特判。

如果空行在末尾，那么可以直接忽略，结束处理。

- **【代码】**

```cpp
#include <iostream>
#include <cmath>

using namespace std;

int main(int argc,char *argv[],char *env[])
{
	int line,row;
	cin>>line>>row;
	char garden[line][row];
	for(int i=0;i<line;i++)
		for(int j=0;j<row;j++)
			cin>>garden[i][j];
	int tlstrt,tled,linepos=0,rowpos=0,lnposcpy,cntmove=0;
	while(linepos<line)
	{
		tled=0;
		if(linepos%2==0)//找到本行最后一块杂草
		{
			for(int i=0;i<row;i++)
				if(garden[linepos][i]=='W')
					tled=i;
		}
		else
			for(int i=row-1;i>=0;i--)
				if(garden[linepos][i]=='W')
					tled=i;
		cntmove+=abs(tled-rowpos);
		lnposcpy=linepos;
		rowpos=tled;
		while(++lnposcpy<line)//找到下一非空行第一块杂草
			if(lnposcpy%2==0)
			{
				for(int i=0;i<row;i++)
					if(garden[lnposcpy][i]=='W')
					{
						tlstrt=i;
						goto cont_proc;
					}
			}
			else
				for(int i=row-1;i>=0;i--)
					if(garden[lnposcpy][i]=='W')
					{
						tlstrt=i;
						goto cont_proc;
					}
		break;
		cont_proc:
		cntmove+=lnposcpy-linepos;
		cntmove+=abs(tlstrt-rowpos);
		rowpos=tlstrt;
		linepos=lnposcpy;
	}
	tled=0;
	if(linepos%2==0)//处理最后一行的杂草
	{
		for(int i=0;i<row;i++)
			if(garden[linepos][i]=='W')
				tled=i;
	}
	else
		for(int i=row-1;i>=0;i--)
			if(garden[linepos][i]=='W')
				tled=i;
	cntmove+=abs(tled-rowpos);
	cout<<cntmove;
 	return 0;
}

```

---

## 作者：watermonster (赞：0)

有草的区间必须全部遍历。剩下的不必全部遍历，只需要走到刚好能遍历完下一行的点即可。将矩阵离散成区间，用DFS或循环实现上下遍历。
### **code:**
```cpp
#include <cstdio>
using namespace std;
#define re register
#define il inline
il void read(int &x)
{
    char ch=getchar();x=0;
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
}//快读
int n,m,left[200],right[200],ans,d;
char lawn[200][200];
il void dfs(int x,int y,int dir)
{
    if(x==d) return;//割完，结束
    ans++;//先加上下移动的时间
    if(right[x+1]==0)
        dfs(x+1,y,dir^1);//下一行没有草，直接向下
    else
    {
        if(dir==1)//当前行向右走
        {
            if(y<right[x+1]) ans+=right[x+1]-y,y=right[x+1];//从当前点向下无法遍历下一行
            ans+=y-left[x+1];//走完下一行的花费
            dfs(x+1,left[x+1],0);
        }
        else//当前行向左走
        {
            if(y>left[x+1]) ans+=y-left[x+1],y=left[x+1];//从当前点向下无法遍历下一行
            ans+=right[x+1]-y;//走完下一行的花费
            dfs(x+1,right[x+1],1);
        }
    }
}
int main()
{
    read(n),read(m);
    for(re int i=1;i<=n;++i)
    {
        for(re int j=1;j<=m;++j)
        {
            lawn[i][j]=getchar();
            if(lawn[i][j]=='W') d=i;//往下全为空地则无必要向下遍历（也是坑点）
        }
        getchar();
    }
    if(d==0){puts("0");return 0;}//全是空地
    for(re int i=1;i<=d;++i)
    {
        for(re int j=1;j<=m;++j)
            if(lawn[i][j]=='W'){left[i]=j;break;}//预处理区间左端点
        for(re int j=m;j>=1;--j)
            if(lawn[i][j]=='W'){right[i]=j;break;}//预处理区间右端点
    }
    if(right[1]>0) ans=right[1]-1,dfs(1,right[1],1);//第一行
    else dfs(1,1,1);//坑点，第一行没有草(right[1]=0)则起点必须为一
    printf("%d",ans);
    return 0;
}
```

---

