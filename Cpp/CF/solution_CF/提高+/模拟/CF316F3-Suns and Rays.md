# Suns and Rays

## 题目描述

海狸喜欢画太阳，他们准备设计一个程序来处理他的画作。给你一张海理的画，画中有2种颜色：背景色：蓝色，太阳色：黄色。

你需要计算图像中太阳的数量，并计算每一个太阳的光线数量。太阳是任意旋转的带有光线的椭圆。光线是连接太阳边界上的点与太阳外的点的线段。

图一：所有太阳都是圆的。

图二：所有的太阳都是椭圆的，而且它们的轴与坐标轴平行。

图三：所有的太阳都是可以任意旋转的椭圆。

保证以下规则：
- 两个太阳不会在一个点上
- 射线的宽度为3
- 太阳的坐标不小于40，且不大于200。
- 两条光线不会相交
- 光线的长度不小于10且不大于30

# 题解

## 作者：liumuxin (赞：0)

安利一下自己的[博客](https://wbybl.github.io/)  
其实这题的F1，F2，F3我都是一份代码过得。 
总体思路都是一样的，不受题目中椭圆、旋转的影响  
这题难点在于如何分离出太阳的光芒和主体，想了半天后在网上看到一个神奇的思路
![开始是这样的](https://cdn.luogu.com.cn/upload/image_hosting/fe4a498z.png)  
然后我们先“缩小”，就是如果一个黑色旁边有白色，就把他变成白色，当然一次只能变一层，所以我们可以先拿一个数组存下来，然后枚举一遍，再放回数组里。  
当然一遍缩点不够，我们需要进行4次缩小，然后太阳就会变成这个图中黄色的部分，当然要存在两个数组里，我只是放在一起，方便对比  
![](https://cdn.luogu.com.cn/upload/image_hosting/ix2whzga.png)  

但是这样，我们如果黄色和黑色相减，得出来的并不是分离好的光芒，而是光芒和一圈黑色，还是无法判断

所以我们要用缩小的逆操作，“展开”

在缩点后的数组中操作，如果一个点周围有黄色，就把它变成黄色，这样展开8次，就会变成左边的两张图，下面的是展开后的，上面的是原图
![](https://cdn.luogu.com.cn/upload/image_hosting/vkb6ebhi.png)

把这两张图相减，就得到了右边的图，相减的原则：只要黑色和黄色重合，就变成白色，这样在结合原图，用几次flood fill遍历一下，就可以解决这道题了


```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[2000][2000],b[2000][2000],c[2000][2000];
int n,m;
void jian(){//缩小
	memcpy(c,b,sizeof(b));
	for(int i=1;i<=n-2;i++){
		for(int j=1;j<=m-2;j++){
			if(!b[i+1][j]||!b[i][j+1]||!b[i-1][j]||!b[i][j-1])
			c[i][j]=0; 
		} 
	}
	memcpy(b,c,sizeof(b));
}
void jia(){//展开
	memcpy(c,b,sizeof(b));
	for(int i=1;i<=n-2;i++){
		for(int j=1;j<=m-2;j++){
			if(b[i+1][j]||b[i][j+1]||b[i-1][j]||b[i][j-1]){
				c[i][j]=1;
			}
		}
	}
	memcpy(b,c,sizeof(b));
}
bool vis[2000][2000];
int d[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int cnt,ans[20000];
pair<int,int> q1[6000000],q2[6000000];
int h1,t1,h2,t2;
bool count(int x,int y){//判断光芒
	h1=1;
	t1=1;
	q1[t1++]=make_pair(x,y);
	a[x][y]=0;
	int cnt=0;
	while(h1<t1){
		x=q1[h1].first;
		y=q1[h1].second;
		h1++;
		for(int i=0;i<4;i++){
			int tx=x+d[i][0],ty=y+d[i][1];
			if(tx>n||tx<0||ty>m||ty<0)continue;
			if(a[tx][ty]){
				a[tx][ty]=0;
				cnt++;
				q1[t1++]=make_pair(tx,ty);
			}
		}
	}
	if(cnt>5)return 1;
	else return 0;
}
int bfs(int x,int y){//与上面的count，下面的数太阳，上面的判断光芒
	h2=1;
	t2=1;
	q2[t2++]=make_pair(x,y);
	b[x][y]=0;
	int an=0;
	while(h2<t2){
		x=q2[h2].first;
		y=q2[h2].second;
		h2++;
		for(int i=0;i<4;i++){
			int tx=x+d[i][0],ty=y+d[i][1];
			if(a[tx][ty]){
				an+=count(tx,ty);
			}
			if(b[tx][ty]){
				b[tx][ty]=0;
				q2[t2++]=make_pair(tx,ty);
			}
		}
	} 
	return an;
}
inline int read()
{
    int x=0;
    char c=getchar();
    bool flag=0;
    while(c<'0'||c>'9')
	{
		if(c=='-')
			flag=1;
		c=getchar();
	}
    while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
    return flag?-x:x;
}
int main(){
	//freopen("1.in","r",stdin);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int C=read();
			a[i][j]=b[i][j]=C;
		}
	}
	n+=2;
	m+=2;//避免越界
	for(int i=1;i<=4;i++)jian();//缩小
//	for(int i=1;i<=n;i++){
//		for(int j=1;j<=m;j++)cout<<b[i][j];
//		cout<<endl;
//	}
	for(int i=1;i<=8;i++)jia();//展开
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(b[i][j])a[i][j]=0;//相减，得出单独的光芒
		}
	} 
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(b[i][j]){
				ans[++cnt]=bfs(i,j);//分别遍历
			}
		}
	}
	sort(ans+1,ans+cnt+1);//按要求排序输出答案
	cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++){
		cout<<ans[i]<<" ";
	} 
	cout<<endl;
	return 0;
}
```

---

