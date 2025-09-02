# Manhattan Wiring

## 题目描述

题目大意

n×m网格里有空格和障碍，还有两个2和两个3.要求把这两个2和两个3各用一条折线连起来，使得总长度尽量小（线必须穿过格子中心，每个单位正方形的边长为1）。

限制条件如下：障碍格里不能有线，而每个空格里最多只能有一条线。由此可知，两条折线不能相交，每条折线不能自交。

如图所示，折线总长度为18（2、2、3、3格子中各有一条长度0.5的线）。

# 题解

## 作者：TimeTraveller (赞：2)

一看路径最短，没错就是图论题，哒哒哒......  
我敲了半天感觉越敲越不对劲，复杂度和正确性越来越迷。
我此时才恍然大悟，不是图论题啊！QAQ  
~~我果然太蒟蒻了~~  
下面来讲正解吧
### 正解：DP
因为状态情况太多，保证一个最短就不能保证另一个，枚举所有情况复杂度又过不了，于是此时只能请出万能的DP。  
看了数据范围后，开始想写普通的状压，但是怎么定义状态怎么压，怎么转移又是一堆难题。最后半天反应过来，这不就是插头DP么，方格里的路径即相当于一个轮廓线啊，然后就可以定义状态了$f[i][j][k]$表示第$i$行，第$j$个，它的前面和上面的状态为$k$的时候，因为一个格子有三种情况，  
分别为：
- 没有线连接，用0表示
- 2号的线，用1表示
- 3号的线，用2表示

所以用三进制来表示吧。  
于是就定义好了，不过先看空间，时间似乎能过，但是玄学的**0M**内存限制把我吓傻了，肯定是题面有问题吧，我又没空~~其实是懒~~去看Uva的题面，所以尽量优化吧。  
我们先来看状态转移：  
- 第一种情况  
当前是障碍物，因为这一个格子肯定不能放线所以就直接继承前面的。  
转移为$f[i][j][next]=min(f[i][j][next],f[i-1][j][k])$，$next$为当前情况，$k$为上一行情况，条件应满足此格为障碍且前面和上面一格都没有线。此时应该发现$j$没有用所以就大胆删掉一维，又发现只会用到上一行所以又滚动一下，啊哈，这下空间大大缩小了。新的转移就变为为$f[now][next]=min(f[now][next],f[last][k])$了。
- 第二种情况  
当前的点为2或者3，那么就必定有线，这里又分两种情况
      - 第一种：  
      它的前面或者上面有线过来(肯定不会存在都有线过来)，那么转移就为$f[now][next]=min(f[now][next],f[last][k])$，这里要满足上面或者前面有线来的地方不超出地图范围，且不能同时存在，**这里注意细节**，$f[last][k]$为什么不加1呢，因为起点和终点的线只有0.5长，而且有且只有4条0.5的(两个起点两个终点)，所以最后答案加2就可以了。
      - 第二种：
      它的前面和上面都没有线进来，那么就只有它自己有一条线出去，要么下面，要么后面。所以转移为两种：$f[now][next+down]=min(f[now][next+down],f[last][k])$此时$i$不为最后一行。$f[now][next+right]=min(f[now][next+right],f[last][k])$此时$j$不为一行的最后一格。
- 第三种情况  
这下就没有特殊情况了，就只能分类讨论了。此时有四种大情况，每种大情况有因为起点终点是2或3的情况，所以就是8种，~~好吓人~~。但因为只是编号的不同所以可以写在一起，分别为：
      - 前面有上面没有： $f[now][next+right]=min(f[now][next+right],f[last][k]+1),f[now][next+right+down]=min(f[now][next+right+down],f[last][k]+1)$
      - 前面没有上面有：看代码吧，以此类推。
      - 前面上面都有： --------
      - 前面上面都没有：-------  
![](https://cdn.luogu.com.cn/upload/pic/15468.png)      
      
好这题就完了，~~好恶心啊~~ ，答案就在$f[now][i]$中取个最小的，开始边界就是$f[now][0]=1$ ，每次将数组赋为无限大就好啦。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#define end(a) (a==2||a==3)
//判断是否为终点或起点
using namespace std;
const int M=10,N=177148;//3^11+1
const int inf=2139062143;
int n,m,cal[M+5],now,f[2][N];
void init(){cal[0]=1;for(int i=1;i<=13;i++)cal[i]=cal[i-1]*3;}
int getpos(int a,int b){return (a/cal[b])%3;}//取三进制数a的第b位
int next(int a){return (a-(a%3))*3%cal[m+1];}//去尾左移一位
int main(){
	init();
	while(scanf("%d%d",&n,&m)==2){
		if(!n||!m) break;
		int rot=0;
		memset(f[rot],127,sizeof(f[rot]));
		f[rot][0]=0;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				scanf("%d",&now);
				
				rot^=1;//滚动数组
				memset(f[rot],127,sizeof(f[rot]));
				
				for(int k=0;k<cal[m+1];k++){
					if(f[rot^1][k]==inf) continue;//无限大无法更新后面的

					int bef=getpos(k,0),up=getpos(k,m);//bef为前面一个，up为上面一个
					int nex=next(k);

					if(!end(now)&&!bef&&!up) f[rot][nex]=min(f[rot][nex],f[rot^1][k]);//什么都不放，必须在不是终点和上方前方没有的情况下

					if(now==1)continue;//障碍不管
					
					if(end(now)){
						int type=now-1;
						if(bef==type&&!up&&j) f[rot][nex]=min(f[rot][nex],f[rot^1][k]);
						if(up==type&&!bef&&i) f[rot][nex]=min(f[rot][nex],f[rot^1][k]);
						if(!up&&!bef){
							if(i<n-1) f[rot][nex+type*3]=min(f[rot][nex+type*3],f[rot^1][k]);//在下面放一根短线
							if(j<m-1) f[rot][nex+type]=min(f[rot][nex+type],f[rot^1][k]);//在右边放一根短线
						}
						continue;
					}
					
                    if(!bef&&!up&&i<n-1&&j<m-1){
                    	f[rot][nex+8]=min(f[rot][nex+8],f[rot^1][k]+1);//在下方和右方放2线，"Γ"这个样子的+2*3^0+2*3^1
						f[rot][nex+4]=min(f[rot][nex+4],f[rot^1][k]+1);//同上方1线，3^1+3^0
					}
					
					if(!bef&&up&&i){
						//前面没有上面有就放|或L型的线
						if(i<n-1) f[rot][nex+up*3]=min(f[rot][nex+up*3],f[rot^1][k]+1);//"|"
						if(j<m-1) f[rot][nex+up]=min(f[rot][nex+up],f[rot^1][k]+1);//"L"
					}
					
					if(!up&&bef&&j){
						//前面有上面没有就放"7"或者'--'型的
						if(i<n-1) f[rot][nex+bef*3]=min(f[rot][nex+bef*3],f[rot^1][k]+1);//"--"
						if(j<m-1) f[rot][nex+bef]=min(f[rot][nex+bef],f[rot^1][k]+1);//"7"
					}
					
					if(bef==up&&bef&&i&&j){
						//前面上面都有并且这里还能放就只能放"_|"型的
						f[rot][nex]=min(f[rot][nex],f[rot^1][k]+1);
					}
				}
			}
		}
		int ans=inf;
		for(int i=0;i<cal[m+1];i++)ans=min(ans,f[rot][i]);
		if(ans>=inf) printf("0\n");//不连通
		else printf("%d\n",ans+2);//加2是因为四个半个线
	}
	return 0;
}
made by TimeTraveller 2018.3.11 21.42
```


---

