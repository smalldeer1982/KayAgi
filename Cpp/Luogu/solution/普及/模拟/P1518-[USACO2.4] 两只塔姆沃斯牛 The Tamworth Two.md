# [USACO2.4] 两只塔姆沃斯牛 The Tamworth Two

## 题目描述

两只牛逃跑到了森林里。Farmer John 开始用他的专家技术追捕这两头牛。你的任务是模拟他们的行为（牛和 John）。

追击在 $10 \times 10$ 的平面网格内进行。一个格子可以是：一个障碍物，两头牛（它们总在一起），或者 Farmer John。两头牛和 Farmer John 可以在同一个格子内（当他们相遇时），但是他们都不能进入有障碍的格子。

一个格子可以是：
- `.` 空地；
- `*` 障碍物；
- `C` 两头牛；
- `F` Farmer John。

这里有一个地图的例子：

```plain
*...*.....
......*...
...*...*..
..........
...*.F....
*.....*...
...*......
..C......*
...*.*....
.*.*......
```

牛在地图里以固定的方式游荡。每分钟，它们可以向前移动或是转弯。如果前方无障碍（地图边沿也是障碍），它们会按照原来的方向前进一步。否则它们会用这一分钟顺时针转 90 度。 同时，它们不会离开地图。

Farmer John 深知牛的移动方法，他也这么移动。

每次（每分钟）Farmer John 和两头牛的移动是同时的。如果他们在移动的时候穿过对方，但是没有在同一格相遇，我们不认为他们相遇了。当他们在某分钟末在某格子相遇，那么追捕结束。

读入十行表示地图。每行都只包含 10 个字符，表示的含义和上面所说的相同。保证地图中只有一个 `F` 和一个 `C`。`F` 和 `C` 一开始不会处于同一个格子中。

计算 Farmer John 需要多少分钟来抓住他的牛，假设牛和 Farmer John 一开始的行动方向都是正北（即上）。 如果 John 和牛永远不会相遇，输出 0。

## 说明/提示

翻译来自NOCOW

USACO 2.4


## 样例 #1

### 输入

```
*...*.....
......*...
...*...*..
..........
...*.F....
*.....*...
...*......
..C......*
...*.*....
.*.*......```

### 输出

```
49```

# 题解

## 作者：翼德天尊 (赞：1720)

## 老规矩，先审题！
每分钟，农夫和牛可以向前移动或是转弯。

1.如果前方无障碍（地图边沿也是障碍），它们会按照原来的方向前进一步。

2.否则它们会用这一分钟顺时针转 90 度。

终止条件：两者相遇，并且在该分钟末尾。然后计算时间。

## 分析
### 1.初始化与读入
根据题意，我们首先可以想到用一个整形变量ans储存分钟数，再用一个二维字符数组map（简称m）储存整张地图。

但是问题来了，map需要开多大呢？首先这是一个边长为10的地图，所以至少要开10* 10，但是为了更好的判断越界情况，我们可以开一个12* 12的数组，然后把边框全部变为'* '，这样相当于将边框变为了障碍物，判断更加方便。

但是我们要考虑一个问题，我们不能每次移动都遍历一遍数组，太耗时间了，所以我们可以用两个整型数组储存奶牛和农夫的信息（x,y坐标以及方向），每次移动时只需调整信息即可。既然题中说初始方向为正北，我们就可以将初始方向北设为0（初始），顺时针依次将东、南、西设为1，2，3。
```
char m[12][12];
int f[3],c[3],ans;
for (int i=0;i<=11;i++) m[i][0]='*',m[i][11]='*';
for (int i=1;i<=11;i++) m[0][i]='*',m[11][i]='*';
for (int i=1;i<=10;i++){
    for (int j=1;j<=10;j++){
    	cin>>m[i][j];
    	if (m[i][j]=='F') f[1]=i,f[2]=j;
    	if (m[i][j]=='C') c[1]=i,c[2]=j;
	}
}
```
### 2.移动与转弯
初始环节说完了，下面就迎来了我们的重头戏——移动与转弯。

这一环节其实难度不大，只需设置一个函数处理即可（不设也无所谓），遇到障碍物就拐弯，否则就根据方向移动。
```
void move(int x,int y,int mi,int h){//x,y为x,y坐标，mi为方向，h为类型：农夫为0，奶牛为1
	if (mi==0){
		if (m[x-1][y]=='*') if (h==0) f[0]=1; else c[0]=1;
		else if (h==0) f[1]--; else c[1]--;
	}else if (mi==1){
		if (m[x][y+1]=='*') if (h==0) f[0]=2; else c[0]=2;
		else if (h==0) f[2]++; else c[2]++;
	}else if (mi==2){
		if (m[x+1][y]=='*') if (h==0) f[0]=3; else c[0]=3;
		else if (h==0) f[1]++; else c[1]++;
	}else{
		if (m[x][y-1]=='*') if (h==0) f[0]=0; else c[0]=0;
		else if (h==0) f[2]--; else c[2]--;
	}
}
```
### 3.判断是否可以相遇
怎么判断呢？我们可以想到，如果两个物体先后两次从同一个方向走到同一个地点，我们就可以说它们陷入了死循环，但如何判断是否是死循环？？这是一个难倒众人的问题。

我们可以通过生成专属值的方法来判断：农夫的x坐标+他的y坐标* 10+奶牛的x坐标* 100+奶牛的y坐标* 1000+农夫的方向* 10000+奶牛的方向* 40000（农夫方向最多为4）
```
bool zt[160005];
tdz=f[1]+f[2]*10+c[1]*100+c[2]*1000+f[0]*10000+c[0]*40000;
if (zt[tdz]){
	cout<<0<<endl;
	return 0;
}
```
## 总代码如下：
```
#include<bits/stdc++.h>
using namespace std;
char m[12][12];//地图
int f[3],c[3],ans,tdz;//农夫，奶牛，秒数，专属值
bool zt[160005];//记录专属值是否出现
void move(int x,int y,int mi,int h){//移动函数
	if (mi==0){
		if (m[x-1][y]=='*') if (h==0) f[0]=1; else c[0]=1;
		else if (h==0) f[1]--; else c[1]--;
	}else if (mi==1){
		if (m[x][y+1]=='*') if (h==0) f[0]=2; else c[0]=2;
		else if (h==0) f[2]++; else c[2]++;
	}else if (mi==2){
		if (m[x+1][y]=='*') if (h==0) f[0]=3; else c[0]=3;
		else if (h==0) f[1]++; else c[1]++;
	}else{
		if (m[x][y-1]=='*') if (h==0) f[0]=0; else c[0]=0;
		else if (h==0) f[2]--; else c[2]--;
	}
}
bool pd(){ //判断循环终止条件：如果奶牛坐标与农夫坐标相等，则他们重叠，返回0，退出循环
	if (f[1]==c[1]&&f[2]==c[2]) return 0;
	else return 1;
}
int main(){
	for (int i=0;i<=11;i++) m[i][0]='*',m[i][11]='*';
	for (int i=1;i<=11;i++) m[0][i]='*',m[11][i]='*';
    for (int i=1;i<=10;i++){
    	for (int j=1;j<=10;j++){
    		cin>>m[i][j];
    		if (m[i][j]=='F') f[1]=i,f[2]=j;
    		if (m[i][j]=='C') c[1]=i,c[2]=j;
		}
	}
	while (pd()){//模拟每秒
		tdz=f[1]+f[2]*10+c[1]*100+c[2]*1000+f[0]*10000+c[0]*40000;
		if (zt[tdz]){//死循环了就输出0并结束程序
			cout<<0<<endl;
			return 0;
		}
		zt[tdz]=1;//标记
		move(f[1],f[2],f[0],0);
		move(c[1],c[2],c[0],1);//依次移动农夫和奶牛
		ans++;//记录秒数
	}
	cout<<ans<<endl;//输出
    return 0;
}
```
## 看的这么认真，不点个赞多可惜啊！


---

## 作者：早右昕 (赞：112)

### An amazing Tijie.~~其实我是来水贡献的~~


完全没有把题做得很复杂的必要，我通过以下几个方面来精简代码以及维护可读性：


- 使用```struct```维护状态，定义俩操作
- 把地图越界的地方都看作障碍
- 判无解，数据服务小可以使用```vis[i][j][k][l]```来表示（i,j),(k,l)的次数，若大于4，很明显至少有两次方向一样==>无解

代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int dx[]={-1,0,1,0};
const int dy[]={0,1,0,-1};
struct one { int x,y,face; };
char map[12][12];
int vis[11][11][11][11];
void operator++(one& a) {
    int nx=a.x+dx[a.face];
    int ny=a.y+dy[a.face];
    if(map[nx][ny]!='\*') a.x=nx,a.y=ny;
    else a.face++,a.face%=4;
}
bool operator!=(const one&a,const one&b) {
    return a.x!=b.x||a.y!=b.y;
}
int main(){
    one jhon,cow;
    fill(map[0],map[0]+12,'\*');
    fill(map[11],map[11]+12,'\*');
    for(int i=1;i<=10;i++) {
        scanf("%s\n",&map[i][1]);
        map[i][0]=map[i][11]='\*';
        for(int j=1;j<=10;j++) {
            if(map[i][j]=='C') cow=(one) {i,j,0};
            if(map[i][j]=='F') jhon=(one) {i,j,0};
        }
    }
    int ans=0;
    while(jhon!=cow) {
        if(vis[jhon.x][jhon.y][cow.x][cow.y]++==4) {
            printf("0");
            return 0;
        }
        ans++,++jhon,++cow;
    }
    printf("%d\n",ans);
    return 0;
}
```
至此，问题以完美解决。


---

## 作者：beacon_cwk (赞：90)

这题没有什么坑点，主要问题是判断他们是否能够相遇。一种做法是在移动次数达到一定值时判定为无法相遇，但还有另一种思路：给每个状态设定一个值，如果这个值之前已经出现过，说明他们陷入了循环，不能相遇。每个状态都要保存农夫和牛的x、y坐标（各10种可能）和方向（各4种可能），其中为了避免重复，可以将特征值设为

$ farmer.x+farmer.y*10+cow.x*100+cow.y*1000+farmer.facing*10000+cow.facing*40000  $

可以用bool数组来实现以O(1)的复杂度来查询该值是否已经出现。

代码：
```cpp
#include<cstdio>
bool zt[160005];//10*10*10*10*4*4=160000，开大一点以防万一
char mp[11][11];
int cx,cy,cf,fx,fy,ff,xx[4]={-1,0,1,0},yy[4]={0,1,0,-1},nt,stp;
int main()
{
    for(int i=0;i<10;i++)
    scanf("%s",mp[i]);//读入
    for(int i=0;i<10;i++)
    for(int j=0;j<10;j++)
    {
        if(mp[i][j]=='F')//遇到农夫
        fx=i,fy=j;//设定初始坐标
        if(mp[i][j]=='C')//遇到牛
        cx=i,cy=j;//设定初始坐标
    }
    while(1)
    {
        if(fx==cx&&fy==cy)//相遇了
        {
            printf("%d",stp);//输出步数
            return 0;//退出
        }
        nt=fx+fy*10+cx*100+cy*1000+ff*10000+cf*40000;//生成特征值
        if(zt[nt])//如果出现过了，则无解
        {
            printf("0");
            return 0;
        }
        zt[nt]=1;//保存特征值
        if(fx+xx[ff]<0||fx+xx[ff]>=10||fy+yy[ff]<0||fy+yy[ff]>=10||mp[fx+xx[ff]][fy+yy[ff]]=='*')//判断农夫是否还能向前走
        ff=(ff+1)%4;//如果不行，转向
        else fx=fx+xx[ff],fy=fy+yy[ff];//否则继续向前
        if(cx+xx[cf]<0||cx+xx[cf]>=10||cy+yy[cf]<0||cy+yy[cf]>=10||mp[cx+xx[cf]][cy+yy[cf]]=='*')//判断牛是否还能向前走
        cf=(cf+1)%4;//如果不行，转向
        else cx=cx+xx[cf],cy=cy+yy[cf];//否则继续向前
        stp++;//增加步数
    }
    return 0;
}

```

---

## 作者：Thaumaturge (赞：59)

其实就是一道模拟题，还帮助你省去了农夫与牛相撞时的判定过程qwq

看到题后，我们的第一反应是寻找环判重叠来算次数，但这样也太麻烦了，所以考虑更简洁的直接模拟：

由于只有10x10行的地图，因此牛和农夫最多只有400种情况（每个位置有4次，4方向各一次）由乘法原理可知，无论怎么走，最多都只能出现160000种情况，实际上还要小的多（而且160000也非常小了）

那么就可以做了：
```cpp
#include <bits/stdc++.h>

using namespace std;

int a[12][12],i,j,k,cx,cy,fx,fy;//坐标，f是农夫的，c是牛的
char w;
int ff,fc;//农夫与牛的朝向,0表示向上,1表示向右,2表示向下,3表示向左
int cs;//统计行走次数，为了保险开到200000次好一些（滑稽）
int pd,ok;//为了防止重复走的东西

int main(){
	//freopen("appl.in","r",stdin);
	//freopen("appl.out","w",stdout);
	for(i=1;i<=10;i++)//记录障碍点，牛与人都不算障碍，因此只要记录它们的坐标就行了
		for(j=1;j<=10;j++)
		{
			cin>>w;
			if(w=='*') a[j][i]=-1;//横坐标对应的是列，纵坐标对应的是行
			if(w=='C') {cx=j;cy=i;}
			if(w=='F') {fx=j;fy=i;}
		}
	while((cx!=fx || cy!=fy) && cs<200000)//统计行走次数，注意判定边界
	{
		ff%=4;fc%=4;
		cs++;
		pd=0;//方便判定是否转向
		ok=0;//使得行走一次后会马上打住
		//农夫行走一次
		if(ff==0 && ok==0)
		{
			ok=1;
			if(a[fx][fy-1]!=-1 && fy>1)
			{pd=1;fy--;}
			if(pd==0)
			ff++;//转向
		}
		if(ff==1 && ok==0)
		{
			ok=1;
			if(a[fx+1][fy]!=-1 && fx<10)
			{pd=1;fx++;}
			if(pd==0)
			ff++;
		}
		if(ff==2 && ok==0)
		{
			ok=1;
			if(a[fx][fy+1]!=-1 && fy<10)
			{pd=1;fy++;}
			if(pd==0)
			ff++;
		}
		if(ff==3 && ok==0)
		{
			ok=1;
			if(a[fx-1][fy]!=-1 && fx>1)
			{pd=1;fx--;}
			if(pd==0)
			ff++;
		}
		//牛开始走
		pd=0;
		ok=0;
		if(fc==0 && ok==0)
		{
			ok=1;
			if(a[cx][cy-1]!=-1 && cy>1)
			{pd=1;cy--;}
			if(pd==0)
			fc++;
		}
		if(fc==1 && ok==0)
		{
			ok=1;
			if(a[cx+1][cy]!=-1 && cx<10)
			{pd=1;cx++;}
			if(pd==0)
			fc++;
		}
		if(fc==2 && ok==0)
		{
			ok=1;
			if(a[cx][cy+1]!=-1 && cy<10)
			{pd=1;cy++;}
			if(pd==0)
			fc++;
		}
		if(fc==3 && ok==0)
		{
			ok=1;
			if(a[cx-1][cy]!=-1 && cx>1)
			{pd=1;cx--;}
			if(pd==0)
			fc++;
		}

	}
	if(cs==200000) cout<<0;//对死循环的判定
	else cout<<cs;
	return 0;
}
```


---

## 作者：Diamiko (赞：56)

#### 题目不难，只要细心思考，有耐心地去模拟，就可以做出来

## 核心算法：模拟（？）

我看有些大佬用了搜索，其实不必

我感觉自己的思想可能是最好理解的

我们用两个$flag$记录奶牛和FJ的方向

$1$向上，$2$向右，$3$向下，$4$向左

没错，就是顺时针排列

再分别用两个变量记录当前$FJ$和奶牛的坐标

只要坐标不同（即还没有相遇），那么就一直循环，直到相遇，输出步数

在循环时进行判断，只要撞墙或者超出地图范围，就转弯

怎么转弯？

对了，让$flag$++

撞不了墙，就朝着当前的方向继续走一步

### 需要注意的一点
#### 转弯之后，是不用走下一步的，因为题目中描述转弯也消耗一分钟

具体请看代码注释

哦对了，是用$Python$实现的，但是用别的语言的各位同学也可以看下，因为语法差别对理解的阻碍并不是很大，而且最重要的是思想


```python
a=list()

#建立列表，大体上相当于某些语言的数组

for i in range(10):
	a.append(input())
	for j in range(10):
		if a[i][j]=='F':
      		  	#记录FJ的位置
			fx=i
			fy=j
		if a[i][j]=='C':
      			#记录奶牛的位置
			cx=i
			cy=j
            
#上面那段是输入，就相当于建立了一个二维数组

flagf=flagc=1

#分别是FJ和奶牛的初始方向（向上）

cnt=0

#记录步数（分钟数）

while not(cx==fx and cy==fy):
	#只要坐标不重合，就继续循环
	if flagf==1:
    
    		#向上走，就是横坐标减一
            
		if fx-1<0 or a[fx-1][fy]=='*':
        
        		#如果越界，就转向，不走
                
			flagf=2
		else:
			fx-=1
            
           		 #否则就走
                 
	elif flagf==2:
    
    			#向右走，就是纵坐标加一
                
		if fy+1>=10 or a[fx][fy+1]=='*':
			flagf=3
		else:
			fy+=1
	elif flagf==3:
    
    			#向下走，就是横坐标加一
                
		if fx+1>=10 or a[fx+1][fy]=='*':
			flagf=4
		else:
			fx+=1
	else:
    
    			#向左走，就是纵坐标减一
                
		if fy-1<0 or a[fx][fy-1]=='*':
			flagf=1
		else:
			fy-=1  
	
 	#以上是FJ的判断，下面是奶牛，同理，改变量名就行了

	if flagc==1:
		if cx-1<0 or a[cx-1][cy]=='*':
			flagc=2
		else:
			cx-=1
	elif flagc==2:
		if cy+1>=10 or a[cx][cy+1]=='*':
			flagc=3
		else:
			cy+=1
	elif flagc==3:
		if cx+1>=10 or a[cx+1][cy]=='*':
			flagc=4
		else:
			cx+=1
	else:
		if cy-1<0 or a[cx][cy-1]=='*':
			flagc=1
		else:
			cy-=1  
	cnt+=1
    
    	#步数加一
        
	if cnt>=100000:
    
    	#这是个技巧性的判断，
        #如果走了100000步还抓不到，基本无望了,
        #为了确保正确，可以提高这个数字，
        #但是由于python运行太慢，
        #就不加了，代码是可以通过的
        
		print(0)
        #输出0，到不了
		exit(0)
        #结束程序
print(cnt)
#输出步数
```
代码到这就结束了，希望大家多多支持

我感觉自己的思想是很好理解的，如果朋友们有问题还可以再询问

写题解不易，求过审

---

## 作者：Siemens_Thai (赞：37)

本蒟蒻第一篇题解，为CSP普及组小白

#### 本题解为傻子题解，逻辑非常简单，而且其内部含有骗分成分，一般人也可以懂

放代码

```cpp
#include <bits/stdc++.h> 
using namespace std ;

//基本初始：
char mp[11][11] ; //创建地图
int xa , ya , xb , yb ;	//创建变量表示农夫和牛的位置（ a 为农夫， b 为牛， x 为行， y为列）
int lxa , lya , lxb , lyb ; //创建变量表示农夫和牛移动后的位置（移动可能不成立）
int fa = 1 , fb = 1 ; //创建变量表示农夫和牛的方向（ 1 为北、 2 为东、 3 为南、 4 为西）
int ans = 0 ; //创建变量表示时间（输出结果）

//农夫移动函数：
void yda(){
	//平移区：
	if ( fa == 1 ){ //当方向为北时
		lxa = xa - 1 ; //行向上移动（减 1 ）
		lya = ya ; //列不动
	}
	if ( fa == 2 ){ //当方向为东时
		lxa = xa ; //行不动
		lya = ya + 1 ; //列向右移动（加 1 ）
	}
	if ( fa == 3 ){ //当方向为南时
		lxa = xa + 1 ; //行向下移动（加 1 ）
		lya = ya ; //列不动
	}
	if ( fa == 4 ){ //当方向为西时
		lxa = xa ; //行不动
		lya = ya - 1 ; //列向左移动（减 1 ）
	}
	//判定区：
	if ( lxa >= 1 && lya >= 1 && lya <= 10 && lxa <= 10 && mp[lxa][lya] == '.' ){ //当移动后位置在地图内且为空地
		xa = lxa ; //行位置
		ya = lya ; //列位置
	}
	else{ //不成立 
		fa++ ; //方向转变
		if ( fa > 4 ){ //当方向值大于西侧
			fa = 1 ; //变回北侧
		}
	}
}

//牛移动函数： 
void ydb(){
	//平移区
	if ( fb == 1 ){ //当方向为北时
		lxb = xb - 1 ; //行向上移动（减 1 ）
		lyb = yb ; //列不动
	}
	if ( fb == 2 ){ //当方向为东时
		lxb = xb ; //行不动
		lyb = yb + 1 ; //列向右移动（加 1 ）
	}
	if ( fb == 3 ){ //当方向为南时
		lxb = xb + 1 ; //行向下移动（加 1 ）
		lyb = yb ; //列不动
	}
	if ( fb == 4 ){ //当方向为西时
		lxb = xb ; //行不动
		lyb = yb - 1 ; //列向左移动（减 1 ）
	}
	//判定区：
	if ( lxb >= 1 && lyb >= 1 && lyb <= 10 && lxb <= 10 && mp[lxb][lyb] == '.' ){ //当移动后位置在地图内且为空地
		xb = lxb ; //行位置
		yb = lyb ; //列位置
	}
	else{ //不成立 
		fb++ ; //方向转变
		if ( fb > 4 ){ //当方向值大于西侧
			fb = 1 ; //变回北侧
		}
	}
}

//主函数： 
int main(){
	//输入区：
	for ( int i = 1 ; i <= 10 ; i++ ){ //基本二维输入行
		for ( int j = 1 ; j <= 10 ; j++ ){ //基本二维输入列
			cin >> mp[i][j] ; //输入
			if ( mp[i][j] == 'F' ){ //当输入为农夫位置时，将其存储至农夫的位置
				xa = i ; //储存行
				ya = j ; //储存列
				mp[i][j] = '.' ; //为判断方便，将其变为空地
			}
			if ( mp[i][j] == 'C' ){ //当输入为牛位置时，将其存储至牛的位置
				xb = i ; //储存行
				yb = j ; //储存列
				mp[i][j] = '.' ; //为判断方便，将其变为空地
			}
		}
	}
	//模拟区： 
	while(1){
		yda() ; //农夫移动
		ydb() ; //牛移动
		ans++ ; //时间增加
		if ( ans > 10000 ){ //此处为骗分，如果大于 10000 还是没有重合，即无法重合
			cout << 0 ; //直接输出 0
			return 0 ; //结束程序
		}
		if ( xa == xb && ya == yb ){ //如果重合（行列均相同）
			cout << ans ; //输出时间
			return 0 ; //结束程序
		}
	}
}
```


---

## 作者：Celebrate (赞：34)

这一道题我直接模拟，暴力硬搜，反正不会爆，搜索时记录一下就好了

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int dx[4]={-1,0,1,0};//上、右、下、左四个方向 
const int dy[4]={0,1,0,-1};
int cx,cy,ct;//记录奶牛 
int fx,fy,ft;//记录john 
bool f[21][21],v[21][21][4][21][21][4];//f表示地图是否能走，v表示这种情况是否有出现过 
void dfs(int k)
{
	if(cx==fx && cy==fy)//如果抓到了牛 
	{
		printf("%d\n",k);//输出 
		exit(0);
	}
	if(v[fx][fy][ft][cx][cy][ct]==false)//如果这种情况出现过 
	{
		printf("0\n");
		exit(0);
	}
	v[fx][fy][ft][cx][cy][ct]=false;//把这种情况设置为出现过 
	//找奶牛的方向 
	if(f[cx+dx[ct]][cy+dy[ct]]==false)//如果这个方向不能走 
	{
		ct++;if(ct==4) ct=0;//改变方向 
	}
	else cx=cx+dx[ct],cy=cy+dy[ct];//如果可以走就走 
	//找john的方向 
	if(f[fx+dx[ft]][fy+dy[ft]]==false) 
	{
		ft++;if(ft==4) ft=0;
	}
	else fx=fx+dx[ft],fy=fy+dy[ft];
	dfs(k+1);//往下搜索 
}
int main()
{
	int i,j;char st[21];
	memset(f,false,sizeof(f));//为了方便判断边界，一开始就当做不能走吧 
	for(i=1;i<=10;i++)
	{
		scanf("%s",st+1);//输入 
		for(j=1;j<=10;j++)
		{
			if(st[j]=='.') f[i][j]=true;//如果能走 
			if(st[j]=='F') fx=i,fy=j,f[i][j]=true;//如果是john 
			if(st[j]=='C') cx=i,cy=j,f[i][j]=true;//如果是牛 
		}
	}
	ct=ft=0;//一开始是向北 
	memset(v,true,sizeof(v));//各种情况都是可以的 
	dfs(0);//开始搜索 
	return 0;
}
```

---

## 作者：edjzy (赞：25)

我们可以开一个while循环模拟每一秒John和牛的移动找到后就输出答案  
可是如何判断约翰找不到~~妞~~牛呢？  
这时候就该 _~~骚气~~_  _**牛逼**_ 的六维数组登场啦！！！  
我们来分析一下：
如果当约翰和牛的在同一位置且同一方向重复移动时，那么他们就遇不到（可以自己想一下）  
下面上代码:  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[4]={-1,0,1,0},b[4]={0,1,0,-1},fx,fy,cx,cy,book[12][12][12][12][4][4],ans,i,j;
char s[12][12];
int main()
{
	for(int i=1;i<=10;i++)
	for(int j=1;j<=10;j++){
		cin>>s[i][j];
		if(s[i][j]=='C')cx=i,cy=j;
		if(s[i][j]=='F')fx=i,fy=j;
	}
	book[fx][fy][cx][cy][0][0]=1;
	while(1){
		if(cx==fx&&fy==cy){
			cout<<ans;
			return 0;
		}
		if(cx+a[i]>=1&&cy+b[i]>=1&&cx+a[i]<=10&&cy+b[i]<=10&&s[cx+a[i]][cy+b[i]]!='*'){//牛（约翰）还是否能往前走
			cx+=a[i];
			cy+=b[i];
		}
		else{//否则令他们转向
			if(i==3)i=0;
			else i++;
		}
		if(fx+a[j]>=1&&fy+b[j]>=1&&fx+a[j]<=10&&fy+b[j]<=10&&s[fx+a[j]][fy+b[j]]!='*'){
			fx+=a[j];fy+=b[j];
		}
		else{
			if(j==3)j=0;
			else j++;
		}
		if(book[fx][fy][cx][cy][j][i]){//第一维和第二维为约翰的坐标，三，四维为牛的坐标，5,6分别为约翰和牛的方向
			cout<<0;return 0;
		}
		book[fx][fy][cx][cy][j][i]=1;ans++;
	}
	 
}
```
 也许是 _~~最短~~_  _~~最奇葩~~_  _~~(六维数组而已)~~_  _**最渣**_ 代码

---

## 作者：AnicoderAndy (赞：18)

### 思路
#### 基本想法
一看就知道是一道模拟题，由于每次行走到的点都是确定的，我们只需要（暴力地）枚举出这次到达的点并且判断是否相遇。

#### 重点问题：如何判断是否有解

这里我想到一个十分巧(~~pian~~)妙(~~fen~~)的方法。上面的枚举次数如果超过60万那肯定就无解了，所以在上面的循环只要使i从1到600000，如果找到有解，立刻输出并终止程序。

~~*PS：60万这个数字是我随便报的，可能评测机一秒内也就只能运算70万~100万次左右吧嘤嘤嘤*~~

### 代码
```cpp
#include <iostream>
#include <string>
#include <utility>
using namespace std;

int op[4][2] = {    //四种操作，由题意，这里必须顺时针排
    {-1, 0},    //0-向上
    {0, 1},     //1-向右
    {1, 0},     //2-向下
    {0, -1}     //3-向左
};

bool no[12][12];//记录某个位置是否有障碍物(true是有障碍物)

pair<int, int> sb, cow;//sb-FarmerJohn的位置,cow-牛的位置

int dirsb = 0, dircow = 0; //二人面向的方向

int ans = 0;

int main()
{
    //输入
    string x[11];
    for (int i = 1; i <= 10; i++) {
        cin >> x[i];
        for (int j = 0; j < 10; j++) {
            //有障碍物
            if (x[i][j] == '*') {
                no[i][j + 1] = true;
            } else if (x[i][j] == 'F') {
                sb = make_pair(i, j + 1); //FJ的位置
            } else if (x[i][j] == 'C') {
                cow = make_pair(i, j + 1);//牛的位置
            }
        }
    }

    //棋盘四周都是障碍物
    for (int i = 0; i <= 11; i++) {
        no[0][i] = no[11][i] = true;
    }
    for (int i = 0; i <= 11; i++) {
        no[i][0] = no[i][11] = true;
    }

    for (int i = 1; i <= 600000; i++) {
        ans++;  //步数+1

        //记录新的位置
        pair<int, int> newsb, newcow;
        newsb = make_pair(sb.first + op[dirsb][0], sb.second + op[dirsb][1]);
        newcow = make_pair(cow.first + op[dircow][0], cow.second + op[dircow][1]);

        //如果有障碍物或没有
        if (no[newsb.first][newsb.second]) dirsb = (dirsb + 1) % 4;
        else sb = newsb;
        
        if (no[newcow.first][newcow.second]) dircow = (dircow + 1) % 4;
        else cow = newcow;

        //如果相遇
        if (sb == cow) {
            cout << ans << endl;
            return 0;
        }
    }
    cout << 0 << endl;
    return 0;
}
```

---

## 作者：Ricardo_Ni (赞：17)

好多人说本题一眼就是模拟题，然后我为什么一眼看是找出一个重复走过的环捏

大致思路：先找出一个路径上的环，然后枚举相遇的点和相遇时的方向，计算时间

这样其实可以过掉1000*1000的数据，我是不是有点小题大做了。。。具体解释看注释










```cpp
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
#define inf 0x3f3f3f3f
// #define maxn 
// #define int long long
using namespace std;
void write(int x){if(x<0){putchar('-');x=-x;}if(x>9) write(x/10);putchar(x%10+'0');}
int read(){int d=0,w=1;char c=getchar();for(;c<'0'||c>'9';c=getchar())if(c==
'-')w=-1;for(;c>='0'&&c<='9';c=getchar())d=(d<<1)+(d<<3)+c-48;return d*w;}
void wln(int x){write(x);putchar('\n');}
void wrs(int x){write(x);putchar(' ');}
int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}},cx,cy,mx,my,tc,tm,f[12][12][5],g[12][12][5],nowm,nowc,t,ans;
//这里d数组是方向数组，这样定义是为了+1后刚好是旋转90度
char s[12][12];
int gcd(int x,int y)
{
	return y?gcd(y,x%y):x;
}
void exgcd(int a,int b,int &x,int &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
	return;
}
signed main()
{
	// freopen("catch.in","r",stdin);
	// freopen("catch.out","w",stdout);
	for(int i=1;i<11;i++)
		gets(s[i]+1);
	for(int i=1;i<11;i++)
		s[i][0]=s[i][11]=s[0][i]=s[11][i]='*';
	for(int i=1;i<11;i++)
		for(int j=1;j<11;j++)
		{
			if(s[i][j]=='C')
			{
				cx=i;
				cy=j;
			}
			if(s[i][j]=='F')
			{
				mx=i;
				my=j;
			}
		}
	//找出F和C在哪，不解释
	nowc=0;
	nowm=0;
	f[cx][cy][0]=g[mx][my][0]=t=1;
	//初始点赋为1是因为标记为0是没有经过的点，会导致第一个点被忽略
	while(1)
	{
		int nx=cx+d[nowc][0],ny=cy+d[nowc][1];
		if(s[nx][ny]!='*')
		{
			cx=nx;
			cy=ny;
		}
		else nowc=(nowc+1)%4;
		if(!f[cx][cy][nowc]) f[cx][cy][nowc]=++t;
			else break;
	}
	//f和g数组是一个时间戳，f[i][j][k]记录最先到[i,j]这个点方向朝k的最少需要时间
	tc=t+1;
	t=1;
	while(1)
	{
		int nx=mx+d[nowm][0],ny=my+d[nowm][1];
		if(s[nx][ny]!='*')
		{
			mx=nx;
			my=ny;
		}
		else nowm=(nowm+1)%4;
		if(!g[mx][my][nowm]) g[mx][my][nowm]=++t;
			else break;
	}
	//由于mx,my,nowm是走过之后才结束的，所以环的大小就是tm-g[mx][my][nowm]，f数组同理
	tm=t+1;
	ans=inf;
	for(int i=1;i<11;i++)
		for(int j=1;j<11;j++)
			for(int k=0;k<4;k++)
				for(int l=0;l<4;l++)
					if(f[i][j][k]&&g[i][j][l])
					{
						if(f[i][j][k]<=f[cx][cy][nowc]&&g[i][j][l]<=g[mx][my][nowm])
						//当这个点既不处于f的环内又不处于g的环内，说明这个点只经过一遍，只要判断两者经过的时间是否相同
						{
							if(f[i][j][k]==g[i][j][l]) ans=min(ans,f[i][j][k]-1);
							continue;
						}
						if(f[i][j][k]<=f[cx][cy][nowc])
						//当这个点不处于f的环内单处于g的环内，判断是否多次绕环可以与f在同一时间相遇
						{
							if(f[i][j][k]>=g[i][j][l]&&(f[i][j][k]-g[i][j][l])%(tm-g[mx][my][nowm])==0) ans=min(ans,f[i][j][k]-1);
							continue;
						}
						if(g[i][j][l]<=g[mx][my][nowm])
						//与上同理
						{
							if(g[i][j][l]>=f[i][j][k]&&(g[i][j][l]-f[i][j][k])%(tc-f[cx][cy][nowc])==0) ans=min(ans,g[i][j][l]-1);
							continue;
						}
						//当这个点处于f的环内又处于g的环内时我们得到若要使两者可以相遇，那么则有 f环的大小*x+第一次f到这个点的时间=g环的大小+第一次g到这个点的时间 ，转化为一个解二元一次不定方程的问题，可以用扩展欧几里得来实现，当然首先要考虑无解与gcd的问题
						int tmx=tc-f[cx][cy][nowc],tmy=tm-g[mx][my][nowm];
						int gd=gcd(tmx,tmy),ch,x,y;
						if(g[i][j][l]>f[i][j][k])
						{
							if((g[i][j][l]-f[i][j][k])%gd!=0) continue;
							ch=(g[i][j][l]-f[i][j][k])/gd;
						}
						else
						{
							if((f[i][j][k]-g[i][j][l])%gd!=0) continue;
							ch=(f[i][j][k]-g[i][j][l])/gd;
						}
						exgcd(tmx,tmy,x,y);
						ans=min(ans,x*ch*tmx+f[i][j][k]-1);
					}
	//上述ans=min(ans,xxx-1);中的-1是因为一开始我们把初始点赋为时间1，而实际是时间0，所以需要-1
	write(ans==inf?0:ans);
	return 0;
}
```

---

## 作者：Manjusaka丶梦寒 (赞：5)

简单的模拟题，代码量不大。

他们走的路线取决于障碍物，可以把边界也看成障碍物，遇到就转，枚举次，因为100$\times$100$\times$4,只有4个可能在一个格子里面走，上下左右，按照给定的方式枚举，如果相遇就输出，没有就输出不可相遇。

(1) 边界看成障碍物，都变成 * 号就好了。

(2) 然后定义两个表示方向的数组
```cpp
int dx[5]={-1,0,1,0};
int dy[5]={0,1,0,-1};
```
分别代表上右下左(顺时针)

(3) 立两个flag：flag_F表示F现在的方向,flag_C同理。

(4) 找出F和C的初始位置。

(5) 然后开始枚举每一分钟的情况，要看清楚题目里说明了转弯需要花费时间，循环枚举。

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int dx[5]={-1,0,1,0};
int dy[5]={0,1,0,-1};
char map[22][22];
int cx,cy,fx,fy,flag_C,flag_F;
int main()
{
	flag_C=flag_F=0;
	for(int i=0;i<=11;i++)	//边界直接定义为障碍 
		map[0][i]='*',map[i][0]='*',map[11][i]='*',map[i][11]='*';
	
	for(int i=1;i<=10;i++)		//输入
		for(int j=1;j<=10;j++)
			cin>>map[i][j];
	
	for(int i=1;i<=10;i++)	//查找 F和 C的位置。 
	{
		for(int j=1;j<=10;j++)
		{
			if(map[i][j]=='C')cx=i,cy=j,map[i][j]='.';
			if(map[i][j]=='F')fx=i,fy=j,map[i][j]='.';
		}
	}
	for(int i=1;i<=400000;i++)	//循环枚举 
	{
		if(map[cx+dx[flag_C]][cy+dy[flag_C]]!='*')
			cx=cx+dx[flag_C],cy=cy+dy[flag_C];
		else flag_C++,flag_C%=4;
		
		if(map[fx+dx[flag_F]][fy+dy[flag_F]]!='*')
			fx=fx+dx[flag_F],fy=fy+dy[flag_F];
		else flag_F++,flag_F%=4;
		
		if(fx==cx&&fy==cy)
		{
			printf("%d",i);
			return 0;
		}
//		cout<<"F:"<<fx<<" "<<fy<<" and "<<"C:"<<cx<<" "<<cy<<"\n";
	}
	printf("0")
}
```

---

## 作者：能神带你飞 (赞：4)

用x1,y1，x2,y2记录人和牛的位置

到dx，dy移动

模拟即可



```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#define y1 y1z
using namespace std;
int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};//N e s w
char map[15][15];
int x1,y1,x2,y2;
int n,a,b;
int main(){
    n=10;
    a=0;b=0;
    for(int i=0;i<=n+1;i++)map[0][i]='*';
    for(int i=0;i<=n+1;i++)map[11][i]='*';
    for(int i=0;i<=n+1;i++)map[i][0]='*';
    for(int i=0;i<=n+1;i++)map[i][11]='*';    //比较愚蠢的写法，边界为障碍
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>map[i][j];
            if(map[i][j]=='F'){
                x1=i;
                y1=j;
            }
            if(map[i][j]=='C'){
                x2=i;
                y2=j;
            }
        }
    }
    int ans=0;
    while(x1!=x2||y1!=y2){
        ans++;
        if(map[x1+dx[a]][y1+dy[a]]=='*'){     //遇障碍，转向
            a=(a+1)%4;
        }else {
            x1=x1+dx[a];   //直行
            y1=y1+dy[a];
        }
        if(map[x2+dx[b]][y2+dy[b]]=='*'){    //同上
            b=(b+1)%4;
        }else {
            x2=x2+dx[b];
            y2=y2+dy[b];
        }
        if(ans>10000000){    //判定有无解，开个大大的常数，可以卡时间
            cout<<0;
            return 0;
        }
    }
    cout<<ans;
}
```

---

## 作者：「QQ红包」 (赞：4)

题解by：redbag

原题解地址：http://redbag.duapp.com/?p=1356

看楼下写得很复杂啊//ylx：其实你的更复杂

不过一堆if看起来有点233吧//ylx：你的也不一样

需仔细看题（见[原题解](http://redbag.duapp.com/?p=1356)的题面的红色字部分）。然后照着模拟就行了。

不难看出，两头牛其实一直在一起。

上右下左分别用1，2，3，4代替，旋转90°相当于+1，4+1就是1了，所以可以直接先取模再+1。

```cpp
/*
ID: ylx14271
PROG: ttwo
LANG: C++     
*/
#include<set>  
#include<map>  
#include<list>  
#include<queue>  
#include<stack>  
#include<string>  
#include<math.h>  
#include<time.h>  
#include<vector>  
#include<bitset>  
#include<memory>  
#include<utility>  
#include<stdio.h>  
#include<sstream>  
#include<iostream>  
#include<stdlib.h>  
#include<string.h>  
#include<algorithm> 
#define LL unsigned long long   
using namespace std;
int i,j,cx,cy,x,y;//(cy,cx)：牛的坐标
int fc,ff,t;//fc牛的方向，ff人的方向,t:时间 
char ch;
int a[15][15];//地图
int pd[11][11][11][11][5][5];//牛和人的坐标+方向
int f[5][3]=//1:上，2：右，3：下，4：左 
{{0,0,0},
{0,-1,0},
{0,0,1},
{0,1,0},
{0,0,-1}}; 
int main() 
{
    freopen("ttwo.in","r",stdin);
    freopen("ttwo.out","w",stdout);//文件
    for (i=0;i<=11;i++)
    {
        a[i][0]=-1;//地图的边赋为障碍物 
        a[0][i]=-1;//四边 
        a[11][i]=-1;
        a[i][11]=-1;
    }
    for (i=1;i<=10;i++)
    {
        for (j=1;j<=10;j++)//读入 
        {
            scanf("%c",&ch);
            switch (ch)
            {
                case '*':
                    {
                        a[i][j]=-1;//标记为障碍物 
                        break;
                    }
                case 'C':
                    {
                        cx=i;
                        cy=j;//牛的坐标 
                        break;
                    }
                case 'F':
                    {
                        x=i;
                        y=j;//坐标
                        break;
                    }
            }//就是读入而已，被我写这么长 
        }
        scanf("\n");
    } //读入完毕 
    fc=1;ff=1;//开始都是向上走 
    while (true)//模拟 
    {
        if (pd[cx][cy][x][y][fc][ff]==1)//走过了
        {//这一步走过了且在此前没有相遇,那就抓不到了 
            printf("0\n");//输出 
            return 0; 
        } 
        pd[cx][cy][x][y][fc][ff]=1;//标记 
        t++;//记录时间 
        //牛走
        if (a[cx+f[fc][1]][cy+f[fc][2]]==-1)//有障碍 
        {
            fc=fc%4+1;//顺时针旋转 
        }else
        {
            cx+=f[fc][1];
            cy+=f[fc][2];//走一步 
        } 
        //人走 
        if (a[x+f[ff][1]][y+f[ff][2]]==-1)//有障碍 
        {
            ff=ff%4+1;//顺时针旋转 
        }else
        {
            x+=f[ff][1];
            y+=f[ff][2];//走一步 
        } 
        if (cx==x&&cy==y)//相遇了
        {
            printf("%d\n",t);//输出
            return 0; 
        } 
    } 
    return 0;
}
 ```

---

## 作者：sxyzhml (赞：4)

其实是纯模拟……因为路线是固定的，并且只有10\*10的网格，所以只要一步步模拟就能AC，每个格子最多可以上下左右走一遍，如果走了第5次那么说明路线出现了重复，即F和C不可能相遇……这时候跳出循环。

```delphi

const cx:array[1..4] of longint=(-1,0,1,0);
      fx:array[1..4] of longint=(-1,0,1,0);
      fy:array[1..4] of longint=(0,1,0,-1);
      cy:array[1..4] of longint=(0,1,0,-1);//预处理旋转后的方向
var a:array[-1..11,-1..11] of  char;
    i,j,dir,dire,ni,nj,ji,jj,t:longint;
begin
fillchar(a,sizeof(a),'0');
for  i:=1  to  10  do
begin
for  j:=1   to  10  do
begin
read(a[i][j]);
if  a[i][j]='C'  then  begin  ni:=i;  nj:=j;  end;
if  a[i][j]='F'  then  begin  ji:=i;  jj:=j;  end;
end;
readln;
end;
dir:=1;
dire:=1;
t:=0;
while  t<>400 do
begin
inc(t);
if (a[ni+cx[dir]][nj+cy[dir]]<>'*')and(a[ni+cx[dir]][nj+cy[dir]]<>'0') then begin
                                                        ni:=ni+cx[dir];
                                                        nj:=nj+cy[dir];
                                                        end
                                                        else dir:=dir mod 4+1;//判断牛的下一步
if (a[ji+fx[dire]][jj+fy[dire]]<>'*')and(a[ji+fx[dire]][jj+fy[dire]]<>'0') then begin
                                                        ji:=ji+fx[dire];
                                                        jj:=jj+fy[dire];
                                                        end
                                                        else dire:=dire mod 4+1;//判断农夫的下一步
if (ni=ji)and(nj=jj) then  begin  writeln(t); exit;  end;
end;
writeln(0);
end.

```

---

## 作者：xfydemx (赞：4)

我又来水题解了...

noip2017 t2大模拟三小时打挂之后 痛定思痛 深感码力不如人 于是开始强刷模拟...于是有了这篇题解（雾）

看了一下 我跟楼下的方法接近 但是楼下那什么玩意？！ 各种谜之缩进...

好吧  我的可读性应该会好很多  我肯定我这篇可读性最高了嘿嘿

用while处理坐标变化，如果次数很大仍然没找到就肯定找不到了



        
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
char a[11][11];//多开一位，实际上相当于边界初始化为0
int m[12][12],xc,yc,xf,yf,ans;
int main(){
    for(int i=1;i<=10;i++)
    for(int j=1;j<=10;j++)
    {
       cin>>a[i][j];  //这句如果改为scanf %c 会挂 原因不明 欢迎私信告知
       if(a[i][j]=='.') m[i][j]=1;
       if(a[i][j]=='*') m[i][j]=0;
       if(a[i][j]=='C') { m[i][j]=1; yc=j; xc=i;} //标记坐标
       if(a[i][j]=='F') { m[i][j]=1; yf=j;  xf=i;}  //各种奇奇怪怪的初始化
    }   
    int pos=1,poc=1;
    for(ans=1;ans<=1009900;ans++){
        if(xc==xf&&yc==yf) break;
        if(pos==4) {
            if(m[xf][yf-1]) yf--;
            else {
            pos=1;goto cc;}
        }
        if(pos==3){
            if(m[xf+1][yf]) xf++;
            else pos=4;
        }
        if(pos==2){
            if(m[xf][yf+1]) yf++;
            else pos=3;
        }
        if(pos==1&&flag==1) flag=0;
        else if(pos==1){
              if(m[xf-1][yf]) xf--;
              else pos=2;
        } 
        cc:int x;
        if(poc==4) {
            if(m[xc][yc-1]) yc--;
            else {poc=1;continue;}
        }
        if(poc==3){
            if(m[xc+1][yc]) xc++;
            else poc=4;
        }
        if(poc==2){
            if(m[xc][yc+1]) yc++;
            else poc=3;
        }
        if(poc==1){
              if(m[xc-1][yc]) xc--;
              else poc=2;
        } 
    }
    if(ans>999999) cout<<"0";  
    else cout<<ans-1;  //从1开始的，一开始就多取了1
} 

```

---

## 作者：转身、已陌路 (赞：4)

这道题的确让人恶心  但的确是道好题

其他的不多说 按照他模拟就好

判断抓不到的时候有两种方法

（1）如果他走过一个点5次 且之前一直没有抓到牛

说明陷入死循环了 就可以跳出

（2） 定一个很大的常数 超过这个数就抓不到

代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
char a[20][20];
int  heng[5];
int  shu[5];
int main()
{
heng[0]=0;heng[1]=1;heng[2]=0;heng[3]=-1;
shu[0]=-1;shu[1]=0;shu[2]=1;shu[3]=0;
    int x1,y1;//记录农夫的位置
    int x2,y2;//记录奶牛的位置 
for (int i=0;i<=11;i++)
for (int j=0;j<=11;j++)
 a[i][j]='*';//将边界设为障碍 
    for (int i=1;i<=10;i++)
    for (int j=1;j<=10;j++)
        {cin>>a[i][j];
          if (a[i][j]=='F') {x1=i;y1=j;}
          if (a[i][j]=='C') {x2=i;y2=j;}
            }            
int x=x1,y=y1; 
int i=x2,j=y2;
int time=0;
int fx1=0,fx2=0;//刚开始都是向北走 
int sum=0;//记录农夫回到初始的次数 
//如果农夫回到初始位置达五次说明无法抓住
while (1)
{
    time++;
 // if (x1==x && y1==y&&x2==i&&y2==j) sum++;
 // if (sum==4) {cout<<0;exit(0);}
  if (a[x1+shu[fx1]][y1+heng[fx1]]!='*')
 {
   x1+=shu[fx1];
   y1+=heng[fx1];
    } 
 else fx1=(fx1+1)%4;
  if (a[x2+shu[fx2]][y2+heng[fx2]]!='*')
 {
   x2+=shu[fx2];
   y2+=heng[fx2];
    } 
 else fx2=(fx2+1)%4;
if (x1==x2&&y1==y2)
{
   cout<<time;
   exit(0);
   }
 if (time>10000000) {cout<<0;exit(0);}
    }
    return 0;
}
```

---

## 作者：judgejudge (赞：3)

# 朴素模拟
这道题毕竟是10*10，纯模拟不会有太大的问题。

但是有几点需要大家注意：

1. **奶牛的方向改变，农民的方向不一定改变，反之同理。**
1. **无论是奶牛还是农民，方向改变时，一律不前进。**
1. **若多次改变方向，并非算作同一时刻内完成的步骤，每一时刻只改变一次方向！**

代码：
```cpp
#include <iostream>
#define N 11//习惯用define
using namespace std;
typedef long long ll;
char c[N][N];
const ll m=10;//最好用const，怕一不小心手抖
ll rowc,colc,rowf,colf;//分别存奶牛的位置，农夫的位置
inline ll f(ll rmovec,ll cmovec,ll rmovef,ll cmovef,ll step){
	register int i,j;
	if(c[rowc+rmovec][colc+cmovec]=='*'||(rowc+rmovec<1||rowc+rmovec>m||colc+cmovec<1||colc+cmovec>m)){//判断是否碰到障碍物
		if(rmovec==-1&&cmovec==0)rmovec=0,cmovec=1;
		else if(rmovec==0&&cmovec==1)rmovec=1,cmovec=0;
		else if(rmovec==1&&cmovec==0)rmovec=0,cmovec=-1;
		else if(rmovec==0&&cmovec==-1)rmovec=-1,cmovec=0;
	}//改变方向：-1,0向上，0,1向右，1,0向下，0,-1向左，按顺时针方向
	else rowc+=rmovec,colc+=cmovec;//奶牛改变位置
	if(c[rowf+rmovef][colf+cmovef]=='*'||(rowf+rmovef<1||rowf+rmovef>m||colf+cmovef<1||colf+cmovef>m)){//判断是否碰到障碍物
		if(rmovef==-1&&cmovef==0)rmovef=0,cmovef=1;
		else if(rmovef==0&&cmovef==1)rmovef=1,cmovef=0;
		else if(rmovef==1&&cmovef==0)rmovef=0,cmovef=-1;
		else if(rmovef==0&&cmovef==-1)rmovef=-1,cmovef=0;
	}//改变方向：-1,0向上，0,1向右，1,0向下，0,-1向左，按顺时针方向
	else rowf+=rmovef,colf+=cmovef;//农民改变位置
	if(rowc==rowf&&colc==colf)return step;//如果重合，返回步数
	else if(step>10000)return 0;//始终巡查不到，输出0
	else f(rmovec,cmovec,rmovef,cmovef,step+1);//继续模拟
}
int main(){
	register int i,j;
	for(i=1;i<=m;i++)
	for(j=1;j<=m;j++){
	    cin>>c[i][j];
	    if(c[i][j]=='C')rowc=i,colc=j;//找奶牛初始位置
	    else if(c[i][j]=='F')rowf=i,colf=j;//找农民初始位置
	}
	cout<<f(-1,0,-1,0,1)<<endl;//递归
	return 0;
}
```


---

## 作者：珅肐 (赞：3)

提供较为简洁的代码

思路：没有什么思路，按题意模拟即可

说几个小技巧：

$1.$ 存图时将周围存一周$'*'$，就可以省去判断是否越界的麻烦。

$2.$ 方向用$dx,dy$数组存下，分别为-北-东-南-西，顺序无所谓，但是要顺时针。

分别用$d$和$cd$表示$John$和两只塔姆沃斯牛的方向标号，当前坐标加上两个数组的就是下一步的位置。

$d$每次$+1$，对$4$取模。

$3.$ 如何判断无解的情况？

显然如果出现循环，而他们还没有碰上的话，就一定无解了。

情况数最多有：$10*10*4*10*10*4=160000$种，其实非常少（只考虑位置和方向）

判断有两种，一是直接等步数超过160000的时候（实际远到不了那么多）退出，另一种是存下之前的每种情况，我用了一个六维数组存，实际上可以直接映射到一维数组，大家不要学我（捂脸），高维数组寻址非常慢。

但也不建议按第一种方法，如果数据再大一些，就会产生可见的影响。

比如可以映射为$x*16000+y*1600+f*400+cx*40+cy*4+cf$（很多种方案，$hash$也可以）


### 代码奉上：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
bool v[11][11][11][11][4][4];//标记数组
char ma[12][12];//地图map
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};//方向数组
int x,y,cx,cy,d,cd,step;//John和两只塔姆沃斯牛的坐标、方向还有步数
int main(){
    for(int i=1;i<=10;++i)scanf("%s",ma[i]+1);
    for(int i=0;i<=10;++i)ma[0][i]=ma[i][0]=ma[11][i]=ma[i][11]='*';//边界处理
    for(int i=1;i<=10;++i)
		for(int j=1;j<=10;++j)
        	if(ma[i][j]=='F')x=i,y=j;
        	else if(ma[i][j]=='C')cx=i,cy=j;//寻找John和两只塔姆沃斯牛的坐标
	while(1){
        if(x==cx && y==cy){printf("%d",step);return 0;}//John抓到了两只塔姆沃斯牛！输出并结束程序
        if(v[x][y][cx][cy][d][cd]){puts("0");return 0;}//重复，无解，输出0
        v[x][y][cx][cy][d][cd]=1;
        if(ma[x+dx[d]][y+dy[d]]=='*')d=(d+1)%4;//如果是边界/障碍就拐弯，下同
        else x=x+dx[d],y=y+dy[d];
        if(ma[cx+dx[cd]][cy+dy[cd]]=='*')cd=(cd+1)%4;
        else cx=cx+dx[cd],cy=cy+dy[cd];
        step++;//步骤++
    }
    return 0;//好习惯
}
```

---

## 作者：Victorique_De_Blois (赞：3)

### 这一道题其实就是两个队列大模拟，不要想得太复杂了！！ 

好像没有人用广搜做QWQ

两个队列，一个记录奶牛的行程，一个记录农夫的行程。

我想设置路径大家都懂，但是转弯该如何解决呢？思考这样一个问题，因为有四个方向，所以我们完全可以用1~4的编号来标记，我们按北->东->南->西->北…的链状方式来标记，那我们就可以轻松得到下一个方向：

      Next.forward = top.forward % 4 +１； 
      
再想一想，广搜的限制条件是什么呢？农夫与奶牛的行程似乎无穷无尽（想一想，为什么）。

所以我们考虑一下步长的限制：边长为１０的农场，那面积就是１００

一般广搜的层数是基于障碍的个数的，要是我们忽略的话，也就是说农场没有障碍时，那就再乘上１０００，也就是十万，再爽快点再乘个１０，此时边界就是step <= 1000000,当然农夫与奶牛的队列不能空。

接下来看具体实现。

首先，我写了一个类：

    class point 
    { 
        public: 
            int x, y;//横纵坐标 
            int forward;//朝向，标号为1~4 
            bool inside();//判断是否在边界之内 
            bool Conect();//判断是否连通，即有无障碍物 
            void Setnext();//计算下一个点的横纵坐标 
    }; 
    bool point::inside() 
    { 
        return x > 0 && x <= N && y > 0 && y <= N; 
    } 
    bool point::Conect() 
    { 
        return map[x][y] != '*'; 
    } 
    void point::Setnext() 
    { 
        x = x + dx[forward]; 
        y = y + dy[forward]; 
    } 

~~应该看得懂吧！~~

如上，一个点能否继续行走是基于他是否连通与处于边界内，换成程序语言就是

	next.inside()&&next.Conect,

如果符合，那就入队，否则就转弯。

上面已经讲过了，来看看具体的广搜代码:

    queue<point> Cow;//记录奶牛的行程 
    queue<point> John;//记录农夫John的行程
    void bfs()
        {
            while(!Cow.empty() && !John.empty() && step <= 1000000)
            {//三个边界条件 
                point Ct, jt;//取当前的队首 
                point Cnt, jnt;//目标店 
                Ct = Cow.front();//取出队首 
                jt = John.front();
                Cow.pop(); John.pop();//出队 
		
		if(Ct.x == jt.x && Ct.y == jt.y) {
			printf("%d\n", step);//两点重合就将输出答案 
			return ;//退出广搜 
		}
		
		Cnt = Ct;
		jnt = jt;
		Cnt.Setnext();//计算下一个点qwq 
		jnt.Setnext();
		
		if(Cnt.Conect() && Cnt.inside())//下一个点在边界内 
			Cow.push(Cnt);//入队 
		else {//否则改变方向 
			Ct.forward = (Ct.forward % 4) + 1;
			Cow.push(Ct);//入队 
		}
		
		if(jnt.Conect() && jnt.inside())
			John.push(jnt);
		else {
			jt.forward = (jt.forward) % 4 + 1;
			John.push(jt);
		}//好好理解
		step++;//层数加一 
	}
	printf("0");//农夫跑了1000000s追不上奶牛，输出0->qwq 
}

前面已经讲得很清楚了，完整程序就不给了。

---

## 作者：爱喝敌敌畏 (赞：3)

这道题霸王硬上弓也能对（~~数据太太太太水了~~）

只不过判重有点复杂！本蒟蒻是这么推的：

1：定一个bool数组map[i][j][q][p][f1][f2]代表在同一时间牛在（i，j）点跑f1的方向，猎人在（q，p）点跑f2的方向，若出现第二次，直接break

2.但是，我们发现，若牛和猎人在一个时间内到达了一个点五次，代表牛与猎人都陷入死循环，那么，直接break，一下子减了两个维！

输入：
```cpp
for(int  i=1;i<=n;i++)
	{
		for(int  j=1;j<=n;j++)
		{
			ss[i][j]=getchar();
			if(ss[i][j]=='F'){x1=i;y1=j;}
			else  if(ss[i][j]=='C'){x2=i;y2=j;}
		}
		getchar();
	}
```

暴力将地图用障碍围圈：
```cpp
for(int  i=1;i<=n;i++)
	{
		ss[0][i]=ss[n+1][i]=ss[i][0]=ss[i][n+1]='*';
	}
```

模拟：
```cpp
for(int  i=1;;i++)
	{
		int  tx=x1+dx[f1],ty=y1+dy[f1]；
		if(ss[ｔx][ty]=='*')
		{
			ｆ２＋＋;
			if(f1==4)f1=0；
		}
		else
		{
			x1=tx;y1=ty；
		}
		tx=x2+dx[f2],ty=y2+dy[f2];
		if(ss[tx][ty]=='*')
		{
			ｆ２＋＋；
			if(ｆ2==4)f2=0；
		}
		else
		{
			x2=tx;y2=ty；
		}
		if(x1==ｘ2  &&  y1==y2)
		{
			printf("%d\n",i)；
			return  0； 
		}
		if(map[x1][y1][ｘ2][y2]==4)break;
		else  map[x1][ｙ1][x2][y2]++;
	}
```

别复制，否则qwq

---

## 作者：happybob (赞：2)

这道题其实只是个模拟题，我的做法是用一个 `struct`记录每个位置的方向以及坐标，然后`dfs`模拟每一次，那么如何判断无法相遇？其实并不用什么六位数组或者生成值，只需要判断次数是否大于 $ 160000$，因为最多也就这么多种走法，且不会超时，只是整个代码量有点，$220$ 行……。

我前面一直是 $89$ 分，一直找不到原因，WA 了一个点，后来发现是这样的：

我的做法是农夫和牛能走就走，那这个走我用的是 `swap` 互换两个位置，但是没有考虑到如果农夫或者牛要走的位置就是牛或者农夫，导致 `swap` 后出现问题，因为题目说了是同时走，所以我后来想到了一个方法：在每次走之前不光光判断是不是障碍物，还要判断要走的位置是否是对方，就算是，走了其实也不算抓住，因为题目说某分钟后在一格才算，所以在农夫走之前，判断走的位置是否是牛，若是，先让牛走，如果不是，谁先谁后都没关系。注意，如果牛这里已经走了那么后面不要再走一次。

贴代码：

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

char ch[15][15];

struct Node
{
	int x, y;
	int fw;
	int c;
};

int cnt = 0;

Node a[15][15];

void dfs_2(int& fx, int& fy, int& cx, int& cy)
{
	if (a[cx][cy].fw == 1)
	{
		if (cx - 1 <= 0 || a[cx - 1][cy].c == 4)
		{
			a[cx][cy].fw++;
			a[cx][cy].fw--;
			a[cx][cy].fw %= 4;
			a[cx][cy].fw++;
		}
		else
		{
			swap(a[cx - 1][cy], a[cx][cy]);
			cx--;
		}
	}
	else if (a[cx][cy].fw == 2)
	{
		if (cy + 1 > 10 || a[cx][cy + 1].c == 4)
		{
			a[cx][cy].fw++;
			a[cx][cy].fw--;
			a[cx][cy].fw %= 4;
			a[cx][cy].fw++;
		}
		else
		{
			swap(a[cx][cy + 1], a[cx][cy]);
			cy++;
		}
	}
	else if (a[cx][cy].fw == 3)
	{
		if (cx + 1 > 10 || a[cx + 1][cy].c == 4)
		{
			a[cx][cy].fw++;
			a[cx][cy].fw--;
			a[cx][cy].fw %= 4;
			a[cx][cy].fw++;
		}
		else
		{
			swap(a[cx + 1][cy], a[cx][cy]);
			cx++;
		}
	}
	else if (a[cx][cy].fw == 4)
	{
		if (cy - 1 <= 0 || a[cx][cy - 1].c == 4)
		{
			a[cx][cy].fw++;
			a[cx][cy].fw--;
			a[cx][cy].fw %= 4;
			a[cx][cy].fw++;
		}
		else
		{
			swap(a[cx][cy - 1], a[cx][cy]);
			cy--;
		}
	}
}

void dfs(int fx, int fy, int cx, int cy)
{
	cnt++;
	bool flag = false;
	if (a[fx][fy].fw == 1)
	{
		if (fx - 1 <= 0 || a[fx - 1][fy].c == 4)
		{
			a[fx][fy].fw++;
			a[fx][fy].fw--;
			a[fx][fy].fw %= 4;
			a[fx][fy].fw++;
		}
		else
		{
			if (a[fx - 1][fy].fw)
			{
				dfs_2(fx, fy, cx, cy);
				flag = true;
			}
			swap(a[fx - 1][fy], a[fx][fy]);
			fx--;
		}
	}
	else if (a[fx][fy].fw == 2)
	{
		if (fy + 1 > 10 || a[fx][fy + 1].c == 4)
		{
			a[fx][fy].fw++;
			a[fx][fy].fw--;
			a[fx][fy].fw %= 4;
			a[fx][fy].fw++;
		}
		else
		{
			if (a[fx][fy + 1].fw)
			{
				dfs_2(fx, fy, cx, cy);
				flag = true;
			}
			swap(a[fx][fy + 1], a[fx][fy]);
			fy++;
		}
	}
	else if (a[fx][fy].fw == 3)
	{
		if (fx + 1 > 10 || a[fx + 1][fy].c == 4)
		{
			a[fx][fy].fw++;
			a[fx][fy].fw--;
			a[fx][fy].fw %= 4;
			a[fx][fy].fw++;
		}
		else
		{
			if (a[fx + 1][fy].fw)
			{
				dfs_2(fx, fy, cx, cy);
				flag = true;
			}
			swap(a[fx + 1][fy], a[fx][fy]);
			fx++;
		}
	}
	else if (a[fx][fy].fw == 4)
	{
		if (fy - 1 <= 0 || a[fx][fy - 1].c == 4)
		{
			a[fx][fy].fw++;
			a[fx][fy].fw--;
			a[fx][fy].fw %= 4;
			a[fx][fy].fw++;
		}
		else
		{
			if (a[fx][fy - 1].fw)
			{
				dfs_2(fx, fy, cx, cy);
				flag = true;
			}
			swap(a[fx][fy - 1], a[fx][fy]);
			fy--;
		}
	}
	if (!flag)
	{
		dfs_2(fx, fy, cx, cy);
	}
	if (cnt > 160000)
	{
		cnt = 0;
		return;
	}
	if (fx == cx && fy == cy)
	{
		return;
	}
	dfs(fx, fy, cx, cy);
}

int main()
{
	int fx, fy, cx, cy;
	fx = fy = cx = cy = 0;
	for (register int i = 1; i <= 10; i++)
	{
		for (register int j = 1; j <= 10; j++)
		{
			cin >> ch[i][j];
			a[i][j].x = i;
			a[i][j].y = j;
			if (ch[i][j] == 'C' || ch[i][j] == 'F')
			{
				a[i][j].fw = 1;
			}
			else
			{
				a[i][j].fw = 0;
			}
			if (ch[i][j] == 'C')
			{
				a[i][j].c = 1;
				cx = i;
				cy = j;
			}
			else if (ch[i][j] == 'F')
			{
				a[i][j].c = 2;
				fx = i;
				fy = j;
			}
			else if (ch[i][j] == '.') a[i][j].c = 3;
			else a[i][j].c = 4;
		}
	}
	dfs(fx, fy, cx, cy);
	cout << cnt << endl;
	return 0;
}
```






---

## 作者：Drinkwater (赞：2)

这道题不说什么，用一个6维数组来存状态去重，如果有看不懂楼下大神的方法的，看看我的程序吧，最暴力的方法，一A，好爽

/*************************************************************************

    > Author: Drinkwater-cnyali
    > Created Time: 2017/3/22 20:25:14
************************************************************************/













```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
const int maxn = 100000;
const int inf = 0x3f3f3f3f;
int n;
char s[20];
int map[20][20];
int cowx,cowy,hx,hy;
queue<int>q1,q2;
struct T
{
    int x,y,t,f;
}
int ans = 0;
int vis[15][15][5][15][15][5];
void bfs()
{
    q1.push((T){hx,hy,0,1});
    q2.push((T){cowx,cowy,0,1});
    while(!q1.empty || !q2.empty())
    {
        T ls1 = q1.front();q1.pop();
        T ls2 = q2.front();q2.pop();
        if(vis[ls1.x][ls1.y][ls1.f][ls2.x][ls2.y][ls2.f])continue;
        vis[ls1.x][ls1.y][ls1.f][ls2.x][ls2.y][ls2.f] = 1;
        if(ls1.x == ls2.x && ls1.y == ls2.y && ls1.f!=ls2.f){ans = ls1.t;return ;}
        if(ls1.f == 1)
        {
            if(map[ls1.x-1][ls1.y])q1.push((T){ls1.x,ls1.y,ls1.t+1,ls1.f%4+1});
            else q1.push((T){ls1.x-1,ls1.y,ls1.t+1,ls1.f});
        }
        if(ls1.f == 2)
        {
            if(map[ls1.x][ls1.y+1])q1.push((T){ls1.x,ls1.y,ls1.t+1,ls1.f%4+1});
            else q1.push((T){ls1.x,ls1.y+1,ls1.t+1,ls1.f});
        }
        if(ls1.f == 3)
        {
            if(map[ls1.x+1][ls1.y])q1.push((T){ls1.x,ls1.y,ls1.t+1,ls1.f%4+1});
            else q1.push((T){ls1.x+1,ls1.y,ls1.t+1,ls1.f});    
        }
        if(ls1.f == 4)
        {
            if(map[ls1.x][ls1.y-1])q1.push((T){ls1.x,ls1.y,ls1.t+1,ls1.f%4+1});
            else q1.push((T){ls1.x,ls1.y-1,ls1.t+1,ls1.f});
        }
        if(ls2.f == 1)
        {
            if(map[ls2.x-1][ls2.y])q2.push((T){ls2.x,ls2.y,ls2.t+1,ls2.f%4+1});
            else q2.push((T){ls2.x-1,ls2.y,ls2.t+1,ls2.f});
        }
        if(ls2.f == 2)
        {
            if(map[ls2.x][ls2.y+1])q2.push((T){ls2.x,ls2.y,ls2.t+1,ls2.f%4+1});
            else q2.push((T){ls2.x,ls2.y+1,ls2.t+1,ls2.f});
        }
        if(ls2.f == 3)
        {
            if(map[ls2.x+1][ls2.y])q2.push((T){ls2.x,ls2.y,ls2.t+1,ls2.f%4+1});
            else q2.push((T){ls2.x+1,ls2.y,ls2.t+1,ls2.f});    
        }
        if(ls2.f == 4)
        {
            if(map[ls2.x][ls2.y-1])q2.push((T){ls2.x,ls2.y,ls2.t+1,ls2.f%4+1});
            else q2.push((T){ls2.x,ls2.y-1,ls2.t+1,ls2.f});
        }
    }
}
int main()
{
    REP(i,1,n)
    {
        scanf("%s",s+1);
        REP(j,1,strlen(s+1))
        {
            if(s[j] == 'C')cowx = i,cowy = j;
            if(s[j] == 'F')hx = i,hy = j;
            map[i][j] == (s[j] == '*');
        }
    }
    bfs();
    return 0;
}
```

---

## 作者：1124828077ccj (赞：2)

这道题其实不难，开一个六维数组表示人的坐标，牛的坐标，人和牛的坐标，只要重复，就输出0，否则当人的坐标与牛的坐标相等时，就输出答案。

```cpp
#include<cstdio>
char s[12][12];
int x,y,X,Y,n,m,p[12][12][12][12][4][4];
int main()
{
    for (int i=0;i<10;i++)
    scanf("%s",&s[i]);
    for (int i=0;i<10;i++)
    for (int j=0;j<10;j++)
    {
        if(s[i][j]=='F'){x=i;y=j;}
        if(s[i][j]=='C'){X=i;Y=j;}
    }
    for (int i=0;;i++)
    {
        if (x==X && y==Y){printf("%d",i);return 0;}
        if (n==0 && x-1>=0 && s[x-1][y]!='*')x--;
        else if (n==1 && y+1<10 && s[x][y+1]!='*')y++;
        else if (n==2 && x+1<10 && s[x+1][y]!='*')x++;
        else if (n==3 && y-1>=0 && s[x][y-1]!='*')y--;
        else n=(n+1)%4;
        if (m==0 && X-1>=0 && s[X-1][Y]!='*')X--;
        else if (m==1 && Y+1<10 && s[X][Y+1]!='*')Y++;
        else if (m==2 && X+1<10 && s[X+1][Y]!='*')X++;
        else if (m==3 && Y-1>=0 && s[X][Y-1]!='*')Y--;
        else m=(m+1)%4;
        if (p[x][y][X][Y][n][m])break;else p[x][y][X][Y][n][m]=1;
    }
    printf("0");
    return 0;
}
```

---

## 作者：桜Sakura (赞：1)

## 我们来分析一下题意：


### 一、字符串转换数字

一大堆字符串，先变成数字。

####   · 不可以走的地方为-1

#### · 可以走的地方不为-1（奶牛是2，农民是3）




------------

### 二、预设转弯数组

接下来我们先预设一个数组来存放转弯的方向

如图

![](https://cdn.luogu.com.cn/upload/pic/35972.png )

```
int dy[4]={0,1,0,-1};
int dx[4]={-1,0,1,0};
```

在具体操作的时候，可以通过%4来实现转弯。

### 注意：行和列是反的，可以手动画图分析。




------------

### 三、防止越界

防止超出边界，我们可以加一层墙。

```
for(int i=0;i<=11;i++){
        map[0][i]=map[i][0]=map[11][i]=map[i][11]=-1;
    }
```



------------

### 四、AC代码

```cpp
//writer: Sakura
//name: 两只塔姆沃斯牛

#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int map[15][15];
char s[15][15]; 
int fx,fy,cx,cy;
int dy[4]={0,1,0,-1};
int dx[4]={-1,0,1,0};

int main(){
	for(int i=0;i<=11;i++){
        map[0][i]=map[i][0]=map[11][i]=map[i][11]=-1;
    }
	for(int i=1;i<=10;i++){
        scanf("%s",s[i]);
        for(int j=0;j<10;j++){
            if(s[i][j]=='.')map[i][j+1]=0;
            if(s[i][j]=='*')map[i][j+1]=-1;
            if(s[i][j]=='C')map[i][j+1]=2,cx=i,cy=j+1;
            if(s[i][j]=='F')map[i][j+1]=3,fx=i,fy=j+1;
        }
    }
	int t=0;
	int nowcx=cx,nowcy=cy,nowfx=fx,nowfy=fy;
	int kc=0,kf=0;
	while(t<=1000000){
		if(nowcx==nowfx && nowcy==nowfy){printf("%d\n",t);exit(0);}
		t++;
		nowcx+=dx[kc];nowcy+=dy[kc];
		if(map[nowcx][nowcy]==-1){
			nowcx-=dx[kc],nowcy-=dy[kc];
			kc+=1;
			kc%=4;
		}
		nowfx+=dx[kf];nowfy+=dy[kf];
		if(map[nowfx][nowfy]==-1){
			nowfx-=dx[kf],nowfy-=dy[kf];
			kf+=1;
			kf%=4;
		}
	}
	puts("0");
	return 0;
}
```

管理员大大给过QWQ

---

## 作者：用户已注销 (赞：1)

模拟+判重

模拟的部分太过简单，就不详细解释了，反正和一般走迷宫的套路是一样的，何况还有限制方向，所以广搜都不用写。

判重的话好像有非常多方法。。给大家介绍一下：

**方法一：最暴力的方法，六维数组**

如果当前的状态和之前某一步的状态是完全完全一样的（即人、牛坐标朝向均一致），那么再走下去肯定是死循环了，这时候弹出0。

**方法二（我的方法）：状态压缩**

方法一的进化版，因为六维数组写起来很烦，而且调用的时候非常慢（不了解数组原理的同学可以百度一下），所以这样时间会吃亏，所以可以把所有的状态压缩成一个整数。首先把1~10转换成0~9，然后把方向放在前坐标放在后，就可以发现即使浪费了一点空间，总体空间也在50万以内，而且是bool，完全存的下。

**方法三：最简单的方法，由方法二想到的**

既然上面只用了50万位的bool数组，证明最大步数一定不会超过50万，所以如果当前步数大于50万弹出0。这种方法只能说有利有弊，利在简单便捷，而且距离超时也远了去了。弊在有的无解的情况下会稍慢那么一点，不过50万+很小的常数，最慢也就几十ms。

**方法四：sxyzhml大佬的思路（从ta的题解里摘抄的，ta的题解在本页最下方，也就是第一个发表的）**

其实也是有点类似我的方法，如果一个格子被人/牛走了5次，说明肯定其中两次的方向是一样的，所以这时候弹出0。这样只需要两个二维数组（大概是这个意思吧，我不懂pas）。

自己的代码：（方法二，0msAC）

```cpp
#include<cstdio>
#include<cstring>
#define re register
using namespace std;
int con[8];//人的坐标及朝向，牛的坐标及朝向 
const int mx[4]={-1,0,1,0},my[4]={0,1,0,-1};
bool vis[500000],map[10][10]; 
int in()
{
    int ans=0;
    for(re int i=1;i<=6;i++)
        ans=ans*10+con[i];
    return ans;
```
}//压缩当前的状态
```cpp
char read()
{
    char c;
    do scanf("%c",&c); while(c!='C' and c!='F' and c!='.' and c!='*');
    return c;
}
bool can(int x,int y)//某个格子可否到达
{
    if(x<0 or y<0 or x>9 or y>9) return false;
    else return map[x][y];
} 
int main()
{
    memset(vis,false,sizeof(vis));
    memset(map,true,sizeof(map));
    for(re int i=0;i<10;i++)
        for(re int j=0;j<10;j++)
            switch(read())
            {
                case '*':
                    map[i][j]=false;
                    break;
                case 'F':
                    con[1]=0;
                    con[2]=i;
                    con[3]=j;
                    break;
                case 'C':
                    con[4]=0;
                    con[5]=i;
                    con[6]=j;
                    break;
            }
    int ans=0;
    while(con[2]!=con[5] or con[3]!=con[6])
    {
        ans++;
        //printf("step %6d:%6d\n",ans,in());
        if(vis[in()]) return !printf("0\n");//之前走过这样的情况，则死循环 
        vis[in()]=true;
        if(!can(con[2]+mx[con[1]],con[3]+my[con[1]])) con[1]=(con[1]+1)%4;//转弯
            else
            {
                con[2]+=mx[con[1]];
                con[3]+=my[con[1]];
            }
        if(!can(con[5]+mx[con[4]],con[6]+my[con[4]])) con[4]=(con[4]+1)%4;//转弯
            else
            {
                con[5]+=mx[con[4]];
                con[6]+=my[con[4]];
            }
    }
    return !printf("%d\n",ans);
}
```

---

## 作者：YczSS (赞：1)

分析

简单的模拟 还是KISS原则，地图的size是10 X 10，那么无论对于Farmer John抑或是Cow，每个点的状态有且仅有上，下，左，右 4 种（分别4种），也就是说，对于Framer John和Cow，每个 点最多走4次，于是在地图上Farmer John 和 Cow 最多走 10\*10\*4 = 400 次，约定 fstep 记录Farmer John 走的步数，cstep 记录 Cow 走的步数，显然不相遇的情况就是 ( fstep>400 || cstep>400 )，值得注意的是，改变方向也需要耗费 1 minutes ！ 

const dd:array[0..3,1..2] of integer=((0,-1),(1,0),(0,1),(-1,0));

 
 


```cpp
var map:array[1..10,1..10,1..10,1..10,0..3,0..3] of boolean;
    i,j,step,cx,cy,fx,fy,cd,fd:integer;
    a:array[0..11,0..11] of char;
begin
assign(input,'ttwo.in');
reset(input);
assign(output,'ttwo.out');
rewrite(output);
for i:=1 to 10 do
  begin a[0,i]:='*';a[i,0]:='*';a[11,i]:='*';a[i,11]:='*';end;
for i:=1 to 10 do
begin
  for j:=1 to 10 do
  begin
    read(a[j,i]);
    if a[j,i]='C' then begin cx:=j;cy:=i;a[i,j]:='.';end else
    if a[j,i]='F' then begin fx:=j;fy:=i;a[i,j]:='.';end;
  end;
readln;
end;
step:=0;
fd:=0;cd:=0;
repeat
map[cx,cy,fx,fy,cd,fd]:=true;
if (cx=fx) and (cy=fy) then begin writeln(step);close(output);halt;end;
if a[cx+dd[cd,1],cy+dd[cd,2]]='*' then begin cd:=(cd+1) mod 4;end
                   else begin cx:=cx+dd[cd,1];cy:=cy+dd[cd,2];end;
if a[fx+dd[fd,1],fy+dd[fd,2]]='*' then begin fd:=(fd+1) mod 4;end
                   else begin fx:=fx+dd[fd,1];fy:=fy+dd[fd,2];end;
inc(step);
until map[cx,cy,fx,fy,cd,fd]=true;
writeln(0);
close(output);
end.

```

---

## 作者：March (赞：1)

它看样子是模拟的题目,只要模拟农夫和牛的动作即可知道结果,可以用hash来判断环.

代码如下:

    
```cpp
#include<stdio.h>
#define n 10
char map[12][12];
struct dir
{
    int xadd,yadd;
}a[4];
struct node
{
    int x,y,dir;
}C,F;
void turn(struct node *T)
{
    T->dir++;
    T->dir%=4;
}
void go(struct node *T)
{
    if(map[T->x + a[T->dir].xadd][T->y + a[T->dir].yadd]!='*' && T->x + a[T->dir].xadd>=0 && T->x + a[T->dir].xadd<n && T->y + a[T->dir].yadd>=0 && T->y + a[T->dir].yadd<n){
        T->x += a[T->dir].xadd;
        T->y += a[T->dir].yadd;//move
        return;
    }
    else{
        turn(T);
        return;
    }
}
void fixdir()
{
    a[0].xadd=-1;
    a[0].yadd=0;
    a[1].xadd=0;
    a[1].yadd=1;
    a[2].xadd=1;
    a[2].yadd=0;
    a[3].xadd=0;
    a[3].yadd=-1;
}
int main()
{
    int hash[11][11][5][11][11][5]={0},ans=0,noans=0;
    int i,j;
    fixdir();
    for(i=0;i<n;i++){
        scanf("%s",&map[i]);
        j=0;
        for(j=0;j<n;j++){
            if(map[i][j]=='C'){
                C.x=i;
                C.y=j;
                C.dir=0;
                map[i][j]='.';
            }
            if(map[i][j]=='F'){
                F.x=i;
                F.y=j;
                F.dir=0;
                map[i][j]='.';
            }
        }
    }
    while(1){
        ans++;
        go(&C);
        go(&F);
        if(F.x==C.x && F.y==C.y) break;
        if(hash[C.x][C.y][C.dir][F.x][F.y][F.dir]==0){
            hash[C.x][C.y][C.dir][F.x][F.y][F.dir]=1;
        }
        else{
            printf("0");
            noans=1;
            break;
        }
    }
    if(noans==0) printf("%d",ans);
        return 0;
}
```

---

## 作者：wick (赞：1)

这一道题可以直接模拟，暴力硬搜，不会爆.
每个状态都要保存农夫和牛的x、y坐标（各10种可能）
但难在如何判输0；
直接上码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[15][15];
int i,j,sx,sy,ty,tx,dir[4][2]= {-1,0,0,1,1,0,0,-1},t,p[3],xa,ya,bm[15][15],bc[15][15];
void walk(int x,int y,int z) {//牛与人的行走//
    if(a[x+dir[p[z]][0]][y+dir[p[z]][1]]=='*') {
        p[z]=(p[z]+1)%4;
        xa=0;
        ya=0;
    } else {
        xa=dir[p[z]][0];
        ya=dir[p[z]][1];
    }
}
int main() {
    for(i=0; i<=11; i++) {//在外面画一圈“*”，防止出界；
        a[i][0]='*';
        a[0][i]='*';
        a[i][11]='*';
        a[11][i]='*';
    }
    for(i=1; i<=10; i++)for(j=1; j<=10; j++) {
            cin>>a[i][j];
            if(a[i][j]=='F') sx=i,sy=j;//记录奶牛
            if(a[i][j]=='C') tx=i,ty=j;//记录john 
        }
    while(1) {
        t++;
        walk(sx,sy,1);
        bm[sx][sy]++;
        sx+=xa;
        sy+=ya;
        walk(tx,ty,2);
        bc[tx][ty]++;
        tx+=xa;
        ty+=ya;
        if(bm[sx][sy]>10&&bc[tx][ty]>10){//经过计算，当人或牛在同一个地方过10次后，若不相遇，则定输出0！！！！
            printf("0");
            return 0;
        }
        if(sx==tx&&sy==ty) break;//相遇!
    }
    printf("%d",t);
}
```


---

## 作者：SIGSEGV (赞：1)

dalao都用模拟做，蒟蒻用的是BFS........

还加了些优化

详见代码注释：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define NDEBUG //蒟蒻调试用
int sx,sy,ex,ey,dy[] = {0,1,0,-1},dx[] = {-1,0,1,0};
//方向，对应北东南西。北相当于x坐标-1
const int N = 10;
char a[N][N];
struct Node{int sx,sy,ex,ey,sh,eh,cnt;}; 
//sx,sy,sh:FJ信息 ex,ey,eh：COW信息 cnt步数
size_t toHash(int a,int b,int c,int d,int e,int f)
{
    return a + b * 100ll + c * 10000ll + d * 1000000ll + e * 100000000ll 
            + f * 10000000000ll;//哈希值
}
struct Pos{int x,y,h;};//相当于STL的tuple，存储方位信息
set<size_t> vis;//判重
queue<Node> q;//BFS必备
Pos nwPos(int x,int y,int h) //扩展用函数
{
    int nx = x + dx[h],ny = y + dy[h];
    if (nx < 0 || ny < 0 || nx >= N || ny >= N || a[nx][ny] == '*')
        return {x,y,(h + 1) % 4};
    return {nx,ny,h}; //根据当前方向和位置获取新的方向，位置
}
int main ()
{
    for (int i = 0;i < 10;i++) scanf("%s",a[i]);
    for (int i = 0;i < 10;i++)
        for (int j = 0;j < 10;j++)
            if (a[i][j] == 'F') sx = i,sy = j;
            else if (a[i][j] == 'C') ex = i,ey = j;
            //存储FJ，cow坐标
#ifndef NDEBUG //调试代码
    cout << sx << ' ' << sy << ' ' << ex << ' ' << ey << '\n';
#endif
    q.push({sx,sy,ex,ey,0,0,0});vis.insert(toHash(sx,sy,ex,ey,0,0));//初始朝北，方位代码（偏移量dx,dy数组下标）为0
    while (!q.empty())
    {
        Node nd = q.front();q.pop();
        if (nd.sx == nd.ex && nd.sy == nd.ey) 
        {
            printf("%d",nd.cnt);
            return 0;//结束
        } 
        auto x = nwPos(nd.sx,nd.sy,nd.sh);//扩展
        auto y = nwPos(nd.ex,nd.ey,nd.eh);
        auto hashNum = toHash(x.x,x.y,y.x,y.y,x.h,y.h);
        //得到哈希值（auto是C++11新特性）
        if (vis.count(hashNum)) continue;
        vis.insert(hashNum);//判重
        q.push({x.x,x.y,y.x,y.y,x.h,y.h,nd.cnt + 1});
        //入队
    }
    printf("0"); //无法抓到牛
    return 0;
}
```

---

