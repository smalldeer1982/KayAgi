# [NEERC 2017] Designing the Toy

## 题目描述

你是这里的玩具生产大佬。最近你买了一台 3D 打印机，它给你提供了一个~~大赚一笔~~创造新玩具的机会。

你的打印机只能打印由一个个单位方块（棱长为 $1$ 的正方体）构成的几何体。因此，你不能打印出任何“光滑”的几何体（比如球体）。另外，这台打印机打印的几何体可以有完全不相连甚至浮空的部分。

建立空间直角坐标系。一个 $[x , x + 1] $ $\times $ $[y , y + 1]$ $\times $ $[z , z + 1]$ 的方块用整数三元组 $(x , y , z)$ 表示。

现在你想指定打印出的几何体在平面 $Oxy$，平面 $Oxz$ 和平面 $Oyz$ 上的投影面积。

![](https://cdn.luogu.com.cn/upload/image_hosting/udemly1h.png)

给出三个正整数 $a,b,c$，依次表示几何体在平面 $Oxy$，平面 $Oxz$ 和平面 $Oyz$ 上的投影面积。判断该集合体是否存在，若存在，找到满足条件的几何体。

## 说明/提示

时间限制：3s，内存限制：512MB。

Translated by Georiky

## 样例 #1

### 输入

```
4 3 5
```

### 输出

```
6
0 0 0
0 1 0
0 2 0
0 2 2
1 2 2
0 0 2
```

## 样例 #2

### 输入

```
100 1 1
```

### 输出

```
-1
```

# 题解

## 作者：scp020 (赞：9)

spj 提供者写的题解。

# [NEERC2017] Designing the Toy

小清新构造题，需要一点空间想象能力。

值得注意的是每个单位正方体是可以悬空的。

## 解法

题目大意是给定一个空间几何体（可以不紧挨着）的三视图中可以看到的单位正方体的数量 $a,b,c$，让你构造出这个空间几何体。

首先考虑无解情况，如果 $a,b,c$ 中最大值大于其余两个数的乘积，则无解。因为考虑有遮挡关系时我们可以尽可能多放正方体，而一个面可以看到 $a$ 个正方体（下面不妨设 $a$ 最小，$c$ 最大），另一个面可以看到 $b$ 个正方体，则最多可以放 $a \times b$ 个正方体，即一个 $1 \times a \times b$ 的空间几何体。

再考虑有解的情况。下面拿样例举例，考虑贴着 $c$ 所代表的平面放正方体。

首先要满足 $a$ 所代表的平面的要求，沿着对角线放，如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/ogo31tjp.png)

放完后我们考虑利用遮挡关系，在不影响 $a$ 的情况下放 $b$，即可以在这个对角线的左侧放 $b-a$ 个正方体，如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/tlpxppz8.png)

$a$ 和 $b$ 都已经满足了，现在考虑 $c$。在这  $b$ 个正方体围成的 $1 \times a \times b$ 的区域里放剩下的正方体，最后共放了 $c$ 个正方体，如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/m0zyfn6h.png)

###   代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define Putchar(c) p3==p4 and (fwrite(Ouf,1,1<<21,stdout),p3=Ouf),*p3++=c
char Ouf[1<<21],*p3=Ouf,*p4=Ouf+(1<<21);
inline void write(int x)
{
	if(x<0) Putchar('-'),x=-x;
	if(x>=10) write(x/10),x%=10;
	Putchar(x^48);
}
int a,b,c,vis[200][200],cnt,v[200][4];
pair<int,int> p[4];
int main()
{
	cin>>p[1].first>>p[2].first>>p[3].first,p[1].second=1,p[2].second=2,p[3].second=3,sort(p+1,p+4);
	a=p[1].first,b=p[2].first,c=p[3].first;
	if(a*b<c)
	{
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=a;i++) v[++cnt][p[1].second]=i,v[cnt][p[2].second]=i,v[cnt][p[3].second]=1,vis[i][i]=1;
	for(int i=a+1;i<=b;i++) v[++cnt][p[1].second]=i,v[cnt][p[2].second]=a,v[cnt][p[3].second]=1,vis[i][a]=1;
	for(int i=1;i<=b;i++)
		for(int j=1;j<=a && cnt<c;j++) if(!vis[i][j]) v[++cnt][p[1].second]=i,v[cnt][p[2].second]=j,v[cnt][p[3].second]=1;
	write(cnt),Putchar('\n');
	for(int i=1;i<=cnt;i++,Putchar('\n')) for(int j=3;j;j--) write(v[i][j]),Putchar(' ');
	fwrite(Ouf,1,p3-Ouf,stdout),fflush(stdout);
	return 0;
}
```

---

## 作者：我怂了 (赞：3)

感谢 @scp020 同志提供的 SPJ 这哥们在我旁边花一下午手搓了两道题的 SPJ 可谓大公无私。
# 题意翻译
在空间 $xyz$ 中构造若干个棱平行于轴的单位立方体，使得它们在 $xOy$、$xOz$、$yOz$ 三个平面上的投影面积为 $a$、$b$、$c$。
# 思路
这玩意是个构造题，试图构造一些立方体，根据样例得出结论：这些立方体可以悬空搭建。

构造题思路多多，这里提供一个。
## 无解情况
### 当 $a$、$b$、$c$ 中存在两者之积小于第三者时，无解。

考虑简单证明：

此时最可能合法的情况不应有任何两个立方体在要求投影面积最大的平面上的投影重合。

原因：任何的这种情况都会在另外两个平面上的投影做出贡献，而没有对这个平面上的投影面积做出贡献。那么更会使得排出合法的情况变得不可能（因为此时要尽可能减小另两个平面上的投影面积，同时增大这个平面上的）。

此时，即使在这个平面上摆满一个矩形，也不能满足投影面积的要求，所以失败。

## 有解以后
有一个很好玩的结论：这些方块可以在一个平面内排布，使它们合法。

证明：

考虑一种相对简单的要求，使用尽可能少的方块。

这事可比直接构造好想多了。优先沿着方块少的两个平面所对的轴所成角的一条角平分线上放，然后再从角平分线上远离原点的那个端点处在这个平面内平行于第二少的那个平面所对的轴去放。

这两部分方块放完以后，便已经满足了最少的两个平面的需求。之后，在这些方块撑起来的矩形中放置方块即可满足第三个平面的需求。

然后我们发现：这题为啥是个三维的东西啊？明明二维就可以做的啊！

得出结论：出题人是个坏淫。
## 实现细节
首先，这题的实现过程中要求对三个平面的需求的投影面积大小排序，但是因为 $a$、$b$、$c$ 的大小关系不确定，所以有人（比如 @scp020 同志第一次写）就写了一百八十行，其中处理的地方重复了六次，对应三个数的六种全排列。然后嘎嘎不好调，调完嘎嘎爆炸。

这里推荐一种相对好写的方法：使用 STL pair。其中 first 存储 $a$、$b$、$c$ 的值，second 用来存储其所对应面所对的轴。$x$、$y$、$z$ 分别对应 $c$、$b$、$a$，即 $3$、$2$、$1$ 三个数，在数组中存储坐标。
## 码子自取
（IAKIOI 为写题时发疯，玄学罢了 qwq）
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,cnt;
struct nod{
	int p[4];
}v[1000001];
bool vis[101][101];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	pair<int,int> s[4];
	s[1].second=1,s[2].second=2,s[3].second=3;
	cin>>s[1].first>>s[2].first>>s[3].first;
	sort(s+1,s+4);
	int a=s[1].first,b=s[2].first,c=s[3].first;
	if(a*b<c){
		cout<<-1;
		goto IAKIOI; 
	}

	int i;
	for(i=0;i<a;i++){
		v[++cnt].p[s[1].second]=i;
		v[cnt].p[s[2].second]=i;
		vis[i][i]=true;
	} 
	for(;i<b;i++){
		v[++cnt].p[s[1].second]=i;
		v[cnt].p[s[2].second]=a-1;
		vis[a-1][i]=true;
	}
	for(int j=0;j<b&&i<c;j++){
		for(int k=0;k<a&&i<c;k++){
			if(!vis[j][k]){
				v[++cnt].p[s[1].second]=j;
				v[cnt].p[s[2].second]=k;
				i++;
			}
		}
	}
	cout<<cnt<<'\n';
	for(int i=1;i<=cnt;i++){
		cout<<v[i].p[3]<<' '<<v[i].p[2]<<' '<<v[i].p[1]<<'\n';
	}
	IAKIOI:
		return 0;
}
```
### 撒花

---

## 作者：Betrayer_of_love (赞：2)

题目大意：给出三视图方向上分别能看到的正方形数 $a,b,c(1\le a,b,c\le 100)$，在 $-100\le x,y,z\le 100$ 的范围内构造出满足情况的一种正方体的摆放方式。

做法很简单，首先找到 $a,b,c$ 中的最大值，如果最大值满足小于等于另两个值的乘积，则有解，否则无解；明确这一点之后，便可以将所有正方体平铺在最大值所在的平面上进行构造。

```c
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const int maxn=1e5+10;
const int inf=0x3f3f3f3f;
const double eps=1e-14;
const double pi=acos(-1.0);
#define mem(s,v) memset(s,v,sizeof(s))
#define pdd pair<double,double>
#define pii pair<int,int>
struct node{
    int num,id;
};
node a[3];
int cmp(node x,node y){
    return x.num<y.num;
}
int mp[111][111];
int main(){
    while(~scanf("%d%d%d",&a[0].num,&a[1].num,&a[2].num)){
        memset(mp,0,sizeof(mp));
        for(int i=0;i<3;++i) a[i].id=i+1;
        sort(a,a+3,cmp);
        if(a[2].num>a[0].num*a[1].num){
            puts("-1");
            continue;
        }
        int j=0;
        for(int i=0;i<a[1].num;++i){
            if(j<a[0].num){
                mp[i][j]=1;
                j++;
            }
            else{
                mp[i][j-1]=1;
            }
        }
        int t=a[2].num-a[1].num;
        for(int i=0;i<t;++i){
            int flag=1;
            for(int k=0;k<a[1].num;++k){
                for(int j=0;j<a[0].num;++j){
                    if(!mp[k][j]){
                        mp[k][j]=1;
                        flag=0;
                        break;
                    }
                }
                if(!flag) break;
            }
        }
        printf("%d\n",a[2].num);
        int x,y,z;
        if(a[2].id==1){
            z=0;
            if(a[1].id==2){
                for(int i=0;i<a[1].num;++i){
                    for(int j=0;j<a[0].num;++j){
                        if(mp[i][j]) printf("%d %d %d\n",i,j,z);
                    }
                }
            }
            else if(a[1].id==3){
                for(int i=0;i<a[1].num;++i){
                    for(int j=0;j<a[0].num;++j){
                        if(mp[i][j]) printf("%d %d %d\n",j,i,z);
                    }
                }
            }
        }
        else if(a[2].id==2){
            y=0;
            if(a[1].id==1){
                for(int i=0;i<a[1].num;++i){
                    for(int j=0;j<a[0].num;++j){
                        if(mp[i][j]) printf("%d %d %d\n",i,y,j);
                    }
                }
            }
            else if(a[1].id==3){
                for(int i=0;i<a[1].num;++i){
                    for(int j=0;j<a[0].num;++j){
                        if(mp[i][j]) printf("%d %d %d\n",j,y,i);
                    }
                }
            }
        }
        else if(a[2].id==3){
            x=0;
            if(a[1].id==2){
                for(int i=0;i<a[1].num;++i){
                    for(int j=0;j<a[0].num;++j){
                        if(mp[i][j]) printf("%d %d %d\n",x,j,i);
                    }
                }
            }
            else if(a[1].id==1){
                for(int i=0;i<a[1].num;++i){
                    for(int j=0;j<a[0].num;++j){
                        if(mp[i][j]) printf("%d %d %d\n",x,i,j);
                    }
                }
            }
        }
    }
    return 0;
}
```

### 完结撒花，谢谢！！！

---

## 作者：zhuimeng1233 (赞：1)

# **题目分析**
给你几何体三视图的面积，求一种可能的几何体形状，并且几何体可以悬空。

## 数据分析
 已知 $1\le a,b,c\le100$ 然而由于形状不限，那我们先假定（假设 $a<b<c$）几何体全部位于一个厚度为 $1$ 的三维空间中，那么显然最大的面的面积等于剩下两条面的面积的乘积（因为厚度为 $1$），即 $c=a\times b$，如果 $c>a\times b$，那么就算把剩下两条边填满了，也不能满足题意；同时也就意味着方块总数 $n\le 10^4$，既然知道了数据范围和大致思路，即向一个平面内填方块，那么实现起来就简单多了。

# 代码实现

用结构体存储方块的坐标（只需要两个），然后读入数据，在处理之前先比大小，然后再自定义函数中处理，这样就不需要考虑最大的面是谁了（因为如果 $a,b,c$ 中最大的值不一样的话，最大的面也不一样），只需要在输出时考虑并交换输出。

然后，在填的时候先斜着填（沿对角线），把较小的边填满，然后再把较长的边填满，如果此时还不够，那就只能向空着的地方填（一定能填得下，因为 $c\le a\times b$）。

至于判断输出时的坐标轴，首先由题给图得，若 $a$ 最大，那么 $z$ 轴为定值（为几都行，看心情）；若 $b$ 最大，那么 $y$ 轴为定值；若 $c$ 最大，那么 $x$ 轴为定值。

# **AC 代码**
```cpp
#include <bits/stdc++.h>
using namespace std;
int sl=0,d=1;
struct zft {
	int x,y;
} fk[100004];

int ffk[1001][1001];//记录填了没 

inline void dyj(int a,int b,int c) { //在这里，一定a<=b<=c
	
   if(a*b<c) {
		cout<<-1;
		return;
	}

	for(int i=1; i<=min(a,b); i++) { //以a为x轴，以b为y轴。
		if(sl<c) { //斜着填
			fk[d].x=i;
			fk[d].y=i;
			d++,sl++;
			ffk[i][i]=1;
		}
	}
	for(int i=1; i<=abs(a-b); i++) { //把a，b较小的一个填完
		if(sl>=c) break;
		fk[d].y=min(a,b)+i;
		fk[d].x=min(a,b);
		d++;
		sl++;
		ffk[min(a,b)+i][min(a,b)]=1;
	}
	for(int i=1; i<=a; i++) { //往空着的地方填
		for(int j=1; j<=b; j++) {
			if(sl>=c) break;
			if(ffk[i][j]!=1) {
				ffk[i][j]=1;
				fk[d].x=i;
				fk[d].y=j;
				d++;
				sl++;
			}
		}
	}
}
int main () {
	int a,b,c;
	cin>>a>>b>>c;
	if(a>=b) { //abc的大小应该有6种不同情况
		if(a>=c) {
			dyj(min(b,c),max(b,c),a);
			if(sl==0) return 0;//就是没有填，在自定义函数里输出过了，只是在这里退出。
			cout<<sl<<endl;
			if(c>=b)//a>c>b
				for(int i=1; i<=sl; i++)	 cout<<fk[i].x<<' '<<fk[i].y<<' '<<1<<endl;
			if(c<b)//a>b>c
				for(int i=1; i<=sl; i++)	 cout<<fk[i].y<<' '<<fk[i].x<<' '<<1<<endl;
		} 
		else { //c>a>b
			dyj(b,a,c);
			if(sl==0) return 0;
			cout<<sl<<endl;
			for(int i=1; i<=sl; i++)	 cout<<1<<' '<<fk[i].y<<' '<<fk[i].x<<endl;
		}
	} 
	else if(b>a) {
		if(b>=c) {
			dyj(min(a,c),max(a,c),b);
			if(sl==0) return 0;
			cout<<sl<<endl;
			if(a>=c)//b>a>c
				for(int i=1; i<=sl; i++)	 cout<<fk[i].y<<' '<<1<<' '<<fk[i].x<<endl;
			if(a<c)//b>c>a
				for(int i=1; i<=sl; i++)	 cout<<fk[i].x<<' '<<1<<' '<<fk[i].y<<endl;
		} else { //c>b>a 
			dyj(a,b,c);
			if(sl==0) return 0;
			cout<<sl<<endl;
			for(int i=1; i<=sl; i++)	  cout<<1<<' '<<fk[i].x<<' '<<fk[i].y<<endl;
		}
	}
	return 0;
}
```
~~第一次发现 DEV 的自动整理代码功能。~~

---

