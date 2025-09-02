# Find Square

## 题目描述

一块矩形有n × m个白色格子，把其中的一些格子涂成黑色，形成一大块黑色的正方形格子，正方形的边长为奇数。找出这个正方形的中心点。

## 样例 #1

### 输入

```
5 6
WWBBBW
WWBBBW
WWBBBW
WWWWWW
WWWWWW
```

### 输出

```
2 4
```

## 样例 #2

### 输入

```
3 3
WWW
BWW
WWW
```

### 输出

```
2 1
```

# 题解

## 作者：hanyuchen2019 (赞：2)

## 小学生发题解 第 $12$ 弹

今天是大年三十，祝管理员大大新年快乐~

### 思路：

我们直接找出正方形的左上角和右下角，也就是**输入矩阵中第一个和最后一个出现的 `B`**，然后取这两个点 $x,y$ 坐标的平均值，就是中心点。

虽然我的思路看起来和你们的差不多，但是：

我不用数组233（边读入边处理）

## Code:

```cpp
#include<iostream>
#include<cstdio>
using namesapce std;
int main()
{
    //x1和y1是开头，x2和y2。k用来判断是不是第一个读到的B
    int n,m,x1,y1,x2,y2,k=1；
    char c;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            cin>>c；//这里不能用getchar();因为getchar()不会吃换行符
            if(c=='B')
            {
                if(k==1)
                {
                    x1=i,y1=j;
                    k=0;//不要漏了这一步！
                }
                x2=i,y2=j;
                //这里用了一种迭代的思想，如果后面还能读到，就直接覆盖
                //不能写 else x2=i,y2=j; 开头可能就是结尾（见样例2）
            }
        }
    }
    cout<<(x1+x2)/2<<" "<<(y1+y2)/2;//平均数
    cout<<endl;//AT不换行，爆零两行泪~
    return 0;
}
```

感谢观看，求点赞~

---

## 作者：yxy666 (赞：2)

题意：给我们一个 $n$ 行 $m$ 列的矩阵，由 $W$ 组成，其中有一个边长为奇数的正方形，由 $B$ 所组成。问我们这个正方形的中心坐标。

我们先看一幅图：
![](https://cdn.luogu.com.cn/upload/image_hosting/7bv7bojc.png)

很明显，这是一个边长为 $5$ 的正方形，它的中心点的横坐标就是最上面的一条边端点的横坐标和与最下面的一条边的端点的横坐标的平均值。它的中心点的纵坐标就是最左边的一条边的纵坐标和最右边的一条边的纵坐标的平均值。也就是 中心点位置为:$((6+2)/2,(3+7)/2)=(4,5)$。

那么我们在码代码实现的时候就只需要刷这个正方形的上下横坐标和左右纵坐标就好了啊。

$code$ :
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,L=1000,R,U=1000,D;
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			char ch=getchar();
			while(ch!='W'&&ch!='B')ch=getchar();//安全读入
			if(ch=='B')L=min(L,j);//刷左面的纵坐标
			if(ch=='B')U=min(U,i);//刷上面的横坐标
			if(ch=='B')R=max(R,j);//刷右边的纵坐标
			if(ch=='B')D=max(D,i);//刷下面的横坐标
		}
	}
	printf("%d %d\n",(D+U)/2,(R+L)/2);
	return 0;
}
```


---

## 作者：BINYU (赞：1)

### 题意
给定一个正方形，求它的中心点
### 思路
![](https://cdn.luogu.com.cn/upload/image_hosting/jvy9pmb4.png)

如图，黑色为B字符构成的正方形，红色是中心，可以看到，红色点的坐标是两个相对的正方形顶点的平均数（可以证明），即 $x = $ 所以，只需要记录相对的两个顶点坐标，就能求出中心点坐标$\large x = \frac{sx + ex}{2} $ , $\large y = \frac{sy + ey}{2}$
### 记录
![](https://cdn.luogu.com.cn/upload/image_hosting/e4aukdx8.png)

记录就要用到读入的一个特性，如图，用
```cpp
for(int i = 1;i <= n;i++)
	for(int j = 1;j <= m;j++)
```
循环读入顺序为从上至下，从左至右（即绿色箭头指示方向）所以第一个读入的B是左上角最后一个是右下角，记录一下，输出的时候代入上文的公式即可
### 代码
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n,m;
int sx,sy,ex,ey;//右上角，左下角坐标
char c;//由于是动态的记录，就不需要数组
int main()
{
	cin>>n>>m;
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= m;j++)
		{
			cin>>c;//数据规模小，cin也能过
			if(c == 'B')//是正方形的一部分
			{
				if(sx == 0&&sy == 0)sx = i,sy = j;//之前没有B,当前就是第一个
				ex = i,ey = j;//直接更新之前的值
			}
		}
	cout<<(sx + ex) / 2<<" "<<(sy + ey) / 2;//平均数公式
	return 0;//好习惯
}
```


---

## 作者：_Spectator_ (赞：0)


[可能更好的食用体验](https://www.luogu.com.cn/blog/523641/CF1028A) $|$ 
[题目传送门](https://www.luogu.com.cn/problem/CF1028A) $|$ 
[我的其他题解](https://www.luogu.com.cn/blog/523641/#type=题解)

------------

这道题的思路很明显：找到黑色矩形的左上角和右下角的坐标，取它们的平均点即为中心。

```cpp
#include<bits/stdc++.h>　
using namespace std;　
int n,m,l,u,r,d;//left,up,right,down
char ch;　
int main()　
{　
    cin>>n>>m;l=u=1<<30;　
    for(int i=1;i<=n;i++)　
    	for(int j=1;j<=m;j++)　
    	{　
    		cin>>ch;　
    		if(ch=='B')　
    		{　
    			u=min(u,i),l=min(l,j);//u和l分别取最先出现B的i、j
    			d=max(d,i),r=max(r,j);//d和r分别取最后出现B的i、j
    		}　
    	}　
    cout<<(u+d)/2<<' '<<(l+r)/2;//取平均点
    return 0;　
}　
```

**[${\color{Black}\text{xt\_\_}}$](https://www.luogu.com.cn/user/523641) 温馨提示：**

${\color{White}\colorbox{#AD8800} {题解千万条，理解第一条。直接粘题解，棕名两行泪。}} $

---

## 作者：DPseud (赞：0)

思路就是找到最前面为 B 的坐标和最后面为 B 的坐标，求平均数，话不多说，直接上代码。

```cpp
#include<bits/stdc++.h>
#define M 116//定义长度为116（115（即最大长度）+1） 
using namespace std;
int main(){
    
    int n,m;
    cin>>n>>m;
    string s[M];
    char c[M][M];
    for(int i=1;i<=n;i++)
    {
    	cin>>s[i];
    	for(int j=1;j<=m;j++)c[i][j]=s[i][j-1];//将输入的字符串一维数组转为字符二维数组 
    }
    int px1=0,py1=0,px2=0,py2=0;//最前面的X坐标、Y坐标以及最后面的X坐标、Y坐标 
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
    	{
    		if(c[i][j]=='B')
    		{
    			//记录最前面的坐标 
    			px1=i;
    			py1=j;
    			goto bj;//不能用break，否则只会跳到第一层循环 
    		}
    	}
    }
    bj:
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
    	{
    		if(c[i][j]=='B')
    		{
    			//记录最后面的坐标 
    			px2=i;
    			py2=j;
    		}
    	}
    }
    //平均坐标 
    int xx=(px1+px2)/2;
    int yy=(py1+py2)/2;
    cout<<xx<<" "<<yy; 
    return 0;
}
```


---

## 作者：Amaresi (赞：0)

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main(){
	int m,n,shou=0;
	cin>>m>>n;
	char a;
	int l[2]={},r[2]={};
	//第一个B与最后一个B的坐标 
	
	for(int i=1;i<=m;i++){
		for(int ii=1;ii<=n;ii++){
			cin>>a;
		    if(a=='B'&&!shou){//取首个B的坐标 
			l[0]=i;
			l[1]=ii;
			shou++;
		    }
		    if(a=='B'){ //取最后一个B的坐标 
		    	r[0]=i;
				r[1]=ii;
			}
		}
	}

    cout<<(l[0]+r[0])/2<<" "<<(l[1]+r[1])/2;
    
return 0;
}

```




---

## 作者：兮水XiShui丶 (赞：0)

第一次写$CF$的题解呢，好激动啊$qwq$ $($虽然是个$A$题qwq

看题面，要求给定矩阵里的那一坨中找到由$B$构成的矩形的中心。   
而且数据范围不大，$n,m<=115$所以我们可以暴力枚举这个由$B$组成的矩形的起始横坐标，起始纵坐标，终点横坐标，终点纵坐标。将相应的坐标加起来再$/2$，就是答案的坐标
代码时间（原谅我写了和$cwbc$一样的代码qwq）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sx,sy,ex,ey,ansx,ansy,flag;char s[120][120];
int main()
{scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%s",s[i]+1);
    for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)
    {if(s[i][j]=='B'){sx=i;sy=j;flag=1;break;}}if(flag==1)break;}
    for(int i=sx;i<=n;i++)for(int j=sy;j<=m;j++)
    {if(s[i+1][j]!='B'&&s[i][j+1]!='B'&&s[i][j]=='B'){ex=i;ey=j;break;}}
    ansx=(sx+ex)/2;ansy=(sy+ey)/2;
    //printf("%d %d %d %d\n",sx,sy,ex,ey);
    printf("%d %d\n",ansx,ansy);
    return 0;
}
```

---

