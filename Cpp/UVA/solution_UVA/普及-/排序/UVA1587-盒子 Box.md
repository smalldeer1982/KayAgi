# 盒子 Box

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=448&page=show_problem&problem=4462

[PDF](https://uva.onlinejudge.org/external/15/p1587.pdf)

# 题解

## 作者：PC_DOS (赞：10)

既然要组成立方体，那么就势必满足以下条件:

1. 至多有3种不同的长方形。

2. 能够拼在一起。

那么，我们只需要读入这六个长方形，将相同的长方形合并为一组，并判断这六个长方形能否拼在一起即可。为了处理方便，我们可以假设每个长方形的长不小于宽。

我们可以以长为第一关键字，宽为第二关键字将6个长方形降序排序，那么对于一个长方体的6个面，必然有第一个长方形和第二个相等、第三个长方形和第四个相等、第五个长方形和第六个相等。之后需要判断能否拼合，即比较不同长方形之间长与宽的关系。

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
struct Rect{ //长方形结构体
	int iLength; //长
	int iWidth; //宽
};
bool operator!=(Rect rctRect1, Rect rctRect2){ //重载不等于比较运算符(!=)
	return ((rctRect1.iLength != rctRect2.iLength) || (rctRect1.iWidth != rctRect2.iWidth));
}
bool cmp(Rect rctRect1, Rect rctRect2){ //以长为第一关键字，宽为第二关键字降序排序的比较函数
	if (rctRect1.iLength != rctRect2.iLength){
		return rctRect1.iLength > rctRect2.iLength;
	}
	else{
		return rctRect1.iWidth > rctRect2.iWidth;
	}
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	Rect arrRect[6]; //存放6个长方形的数组
	int i; //循环计数器
	while (cin >> arrRect[0].iLength >> arrRect[0].iWidth >> arrRect[1].iLength >> arrRect[1].iWidth >> arrRect[2].iLength >> arrRect[2].iWidth >> arrRect[3].iLength >> arrRect[3].iWidth >> arrRect[4].iLength >> arrRect[4].iWidth >> arrRect[5].iLength >> arrRect[5].iWidth){ //读入6个长方形
		for (i = 0; i <= 5; ++i){ //确保每个长方形的长不小于宽
			if (arrRect[i].iLength < arrRect[i].iWidth){
				swap(arrRect[i].iLength, arrRect[i].iWidth);
			}
		}
		sort(arrRect, arrRect + 6, cmp); //以长为第一关键字，宽为第二关键字将6个长方形降序排序
		if (arrRect[0] != arrRect[1] || arrRect[2] != arrRect[3] || arrRect[4] != arrRect[5]){ //对于一个长方体的6个面，必然有第一个长方形和第二个相等、第三个长方形和第四个相等、第五个长方形和第六个相等，出现不等则必定不能组成长方体
			cout << "IMPOSSIBLE\n"; //不能
			continue; //继续循环
		}
		if (arrRect[0].iLength != arrRect[2].iLength || arrRect[0].iWidth != arrRect[4].iLength || arrRect[2].iWidth != arrRect[4].iWidth) //如果发现不能拼合
			cout << "IMPOSSIBLE\n"; //不能
		else //否则
			cout << "POSSIBLE\n"; //能
	}
	return 0; //结束
}
```

---

## 作者：BobXia (赞：3)

调了很久才过，呜呜。这道题地难点在于如何对一个多维的数据，或者说结构体进行排序。在这道题中，需要给一个二维数据排序，一个数据包含长宽两个数，要先讲数据按照长的大小进行排序，然后再将具有相同的长的数据按照宽的大小进行排序，所以这就需要一些技巧。我用了一个插排，可以在 for 循环增加一个 if 来排序。

```c
#include <stdio.h>
void swap( int *a, int *b){
    if ( (*a) < (*b) ){
        int temp;
        temp = *a;
        *a = *b;
        *b = temp;
    }
}
void insert( int side[6][2], int length, int width, int len){
    int i, j;
    for( i = 0; side[i][0] && length <= side[i][0]; i++)
        if ( length == side[i][0] && width > side[i][1])
            break;
    for( j = len - 1; j >= i; j--){
        side[j + 1][0] = side[j][0];
        side[j + 1][1] = side[j][1];
    }
    side[i][0] = length;
    side[i][1] = width; 
}
int main(){
    int side[6][2];
    int i;
    while(1)
    {
        memset(side, 0, sizeof(side));
        int error = 0;
        int length, width;
        for ( i = 0; i < 6; i++)
        {
            if ( scanf("%d %d", &length, &width) == EOF )
                return 0;
            swap( &length, &width);  
            insert(side, length, width, i);
        } 
        /*首先判断是否是两两一组共三组矩形*/
        for ( i = 0; i < 6; i = i + 2){
            if ( side[i][0] != side[i + 1][0] || side[i][1] != side[i + 1][1] )
               error = 1;
        }
        if (error){
            printf("IMPOSSIBLE\n");
            continue;
        }
        /*然后取出1, 3, 5三个矩形来判断它们能否构成一个长方体的底面和侧面*/
        if ( side[0][0] == side[2][0] && side[4][0] == side[0][1] && side[2][1] == side[4][1] )
             printf ("POSSIBLE\n");
        else printf ("IMPOSSIBLE\n");
    }    
    return 0;
}
```

总体来说不太难


---

## 作者：CCF_zkskyer (赞：3)

# 这？数学？

### 1.题目

题目中的英文大可不必要看，否则你会被恶心的。

中文翻译：给定六个**矩形**的长$w$和宽$h$，让你判断能不能组成一个**长方体**（**包括正方体**）。

所以题目的输入应该就有$12$个正数（由于不知道$w_i$和$h_i$是不是整数），所以应该用$double$或者$float$类型来存。

首先我们来分析一下长（正）方体的性质，总共有$12$条棱，$6$个面，因此正好用给定的六个长方形来拼凑。

由于是长（正）方体，所以对应面的长和宽应该对应相等，这才能组成一个真正的长方体，于是我们只要判断长和宽相不相等就行了。

但是，这道题有一个坑，如图：

[![BoVfvF.png](https://s1.ax1x.com/2020/11/08/BoVfvF.png)](https://imgchr.com/i/BoVfvF)

显而易见，这两个长方形是对应面，但是左边的长是$a$，宽是$b$，而右边的则相反，因此我们发现，我们要判段两次才行。

还有，没学过队列的同学自行略过$QaQ$。

### 2.代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ri register int //宏定义。 

const int maxn=100005;

struct node
{
	double l,k;
}; //结构体来存。 

queue <node> q; //队列模拟每一个长和宽。 

double q1[15][3]; //辅助数组，q1[i][1]存长，q1[i][2]存宽。 

void yn() //判段函数。 
{
	for (ri i=1;i<=3;++i)
	{
		double a=q.front().l,b=q.front().k; //先把每次参与判断的长和宽拿出来。 
		q.pop(); //出队。 
		int now=1; //记录有几个不符合的出了队。 
		while(!q.empty())
		{
			if ((a==q.front().l && b==q.front().k) || (b==q.front().l && a==q.front().k)) 
			{
				q.pop();
				break; 
			} //如果符合，就直接出队。 
			else 
			{
				q1[now][1]=q.front().l;
				q1[now++][2]=q.front().k;
				q.pop();
			} //不符合，先用辅助数组记录，然后出队，进行下一次操作。 
		}
		for (ri j=1;j<now;++j)
		{
			q.push((node){q1[j][1],q1[j][2]}); //把不符合的再重新入队。 
		}
	}
	
	if (q.empty()) printf("POSSIBLE\n"); //如果队列是空的，就代表有三组对应面，所以可以。 
	else printf("IMPOSSIBLE\n"); //否则不可以。 
	
	return;
}

int main()
{
    int i=0; //存已知几个矩形。 
    double x,y;
    
    while(scanf("%lf%lf",&x,&y)) //只要有输入，就继续。 
    {
    	if (++i==6) //如果已经有六个了，就开始判断。 
		{
			i=0; //i归零，准备下一组。 
			yn(); //执行函数。 
			q.pop();
			q.pop();
			q.pop();
			q.pop();
			q.pop();
			q.pop(); //判断后，防止最坏情况没有一对对应面，最多出队六次。 
		} 
		else q.push((node){x,y}); //如果还没有六个面，就先将长和宽入队。 
	}
	
	return 0; //依依不舍的结束。 
}
```
### 3.结语

# UVA的第一篇题解，希望大家多多支持！！！

---

## 作者：efgh123 (赞：1)

## 构成长方体或正方体条件
![](https://cdn.luogu.com.cn/upload/image_hosting/etfaac5q.png)
### 1.有的6面中有最多3种面
#### 注意：翻过来也算一样，如图
![](https://cdn.luogu.com.cn/upload/image_hosting/dl4qj5xe.png)
### 2.12条棱4长相等，4宽相等，4高相等。
![](https://cdn.luogu.com.cn/upload/image_hosting/2titgdrg.png)
## 思路
1.输入（While无限运行）

2.判断是否有的6面中有最多3种面

3.判断是否12条棱4长相等，4宽相等，4高相等

4.输出

5.返回1

## Code（主要函数（需优化））
```cpp
struct rectangle{
	double wi,hi;
};
bool same(rectangle a,rectangle b){
	if(a.wi==b.wi&&a.hi==b.hi||a.hi==b.wi&&a.wi==b.hi){
		return 1;
	}
	return 0;
}
bool cub(rectangle a,rectangle b,rectangle c,rectangle d,rectangle e,rectangle f){
	rectangle num[6]={a,b,c,d,e,f};
	int sum=0;
	if(same(a,b))sum++;
    if(same(a,c))sum++;
    if(same(a,d))sum++;
    if(same(a,e))sum++;
    if(same(a,f))sum++;
    if(same(b,c))sum++;
    if(same(b,d))sum++;
    if(same(b,e))sum++;
    if(same(b,f))sum++;
    if(same(c,d))sum++;
    if(same(c,e))sum++;
    if(same(c,f))sum++;
    if(same(d,e))sum++;
    if(same(d,f))sum++;
    if(same(e,f))sum++;
	if(sum<3){
	return 0;
	}
	int visit[100]={-1};
	int p=0;
	int zi[100]={0};
	bool flag=1;
	for(int i=0;i<6;i++){
		if(num[i].wi==visit[0]||num[i].hi==visit[0])zi[0]++;
		if(num[i].wi==visit[1]||num[i].hi==visit[1])zi[1]++;
		if(num[i].wi==visit[2]||num[i].hi==visit[2])zi[2]++;
		if(p==0)visit[0]=num[i].wi,zi[0]++,visit[1]=num[i].hi,zi[1]++,p=2;
	    if(p==2&&num[i].wi!=visit[0]&&num[i].wi!=visit[1])visit[2]=num[i].wi,zi[2]++,p++;
	    if(p==2&&num[i].hi!=visit[0]&&num[i].hi!=visit[1])visit[2]=num[i].hi,zi[2]++,p++;
	    if(p==3&&num[i].wi!=visit[0]&&num[i].wi!=visit[2]&&num[i].wi!=visit[1]&&num[i].hi!=visit[0]&&num[i].hi!=visit[1]&&num[i].hi!=visit[2]){
			flag=0;
			break;
		}
	}
	if(zi[0]==zi[1]==zi[2]||zi[0]==zi[1]){
	return flag;
	}
	else {
	return 0;
	}
}
```


---

## 作者：Dawn_Sdy (赞：1)

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node{
    int h, w;
}a[10];
bool cmp(node x,node y){//先按照w升序排序，再按照h升序排序 
	if(x.w!=y.w)	return x.w<y.w;
	else return x.h<y.h;
}
bool ok(){//判断是否可以组成长方体 
    if(a[0].h!=a[1].h||a[0].w!=a[1].w) 
	   return false;
    if(a[2].h!=a[3].h||a[2].w!=a[3].w) 
	   return false;
    if(a[4].h!=a[5].h||a[4].w!=a[5].w) 
	   return false;
    if(a[1].h!=a[5].w)
	   return false;
    if(a[1].w!=a[2].w) 
	   return false;
    if(a[3].h!=a[4].h) 
	   return false;
    return true;
}
int main(){
    while(scanf("%d%d",&a[0].h,&a[0].w))//读入    
	    {
        if(a[0].h<a[0].w)
		   swap(a[0].h,a[0].w);//保证h<w 
        for(int i=1;i<6;i++)
			{
            scanf("%d%d",&a[i].h,&a[i].w);
            if(a[i].h<a[i].w)
			   swap(a[i].h,a[i].w);//保证h<w 
            }
        sort(a,a+6,cmp);//排序 
        if(ok()) //输出 & AC 
		   puts("POSSIBLE");
        else 
		   puts("IMPOSSIBLE");
    }
    return 0;
}
```


---

## 作者：bmzy (赞：0)

~~调了快一个小时，所以一定要发题解！~~

刚看见题目的时候，感觉就是入门难度，然后WA了两次...
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
	int w[10],h[10];
	while(cin>>w[1]>>h[1]>>w[2]>>h[2]>>w[3]>>h[3]>>w[4]>>h[4]>>w[5]>>h[5]>>w[6]>>h[6])//输入12个值
    {
        int map[10001]={0};
        for(int i=1;i<=6;i++)
        {
            map[w[i]]++;
            map[h[i]]++;
        }
        int sum=0;
        for(int i=1;i<=10000;i++)
        {
            if(map[i]!=0)
            sum++;
        }
        if(sum>3)//统计出现几个数，如果出现4个及以上就IMPOSSIBLE
        {
        //    cout<<sum<<endl;
            cout<<"IMPOSSIBLE"<<endl;
            continue;
        }
	    int ans=0;
		int a[10][3]={0};
		a[1][1]=w[1];
		a[1][2]=h[1];
		a[2][1]=w[2];
		a[2][2]=h[2];
		a[3][1]=w[3];
		a[3][2]=h[3];
		a[4][1]=w[4];
		a[4][2]=h[4];
		a[5][1]=w[5];
		a[5][2]=h[5];
		a[6][1]=w[6];
		a[6][2]=h[6];//忘记用循环了QAQ写完才发现
		for(int i=1;i<=5;i++)
		{
			for(int j=i+1;j<=6;j++)
			{

				if( a[i][1]!=0&&a[j][1]!=0&&a[i][2]!=0&&a[j][2]!=0&&(a[i][1]==a[j][1]&&a[i][2]==a[j][2]||a[i][1]==a[j][2]&&a[i][2]==a[j][1]))
                                {
                                a[i][1]=a[j][1]=a[i][2]=a[j][2]=0;
                                ans++;
                                }
			}
		}//这步像开心消消乐一样把长宽相等的消去，记得ans++完也要清零
		if(ans==3)
		cout<<"POSSIBLE"<<endl;//如果消去3次则能组成盒子，否则不能
		else
		cout<<"IMPOSSIBLE"<<endl;
    }
	return 0;
}
```
求过QAQ

---

## 作者：若_微笑 (赞：0)

```c
#include <stdio.h>
#include <stdlib.h>
int number[6][2];
int cmp(const void*a,const void*b);
void swap(int *a,int *b);
int main()
{
	while(scanf("%d %d",&number[0][0],&number[0][1])==2)
	{
		swap(&number[0][0],&number[0][1]);
		int i;
		for(i=1;i<6;i++)
		{
			scanf("%d %d",&number[i][0],&number[i][1]);
			swap(&number[i][0],&number[i][1]);
		}
		qsort(number,6,2*sizeof(int),cmp);
		if(
		  number[0][0]==number[1][0]&&number[1][0]==number[2][0]&&number[2][0]==number[3][0]
		&&number[2][1]==number[3][1]&&number[3][1]==number[4][1]&&number[4][1]==number[5][1]
		&&number[0][1]==number[1][1]&&number[1][1]==number[4][0]&&number[4][0]==number[5][0]
		)
		printf("POSSIBLE\n");
		else printf("IMPOSSIBLE\n");
	}
	return 0;
}
int cmp(const void*a,const void *b)
{
	if(*(int*)a==*(int*)b)
		return ((int*)a)[1]-((int*)b)[1];
	return *(int*)a-*(int*)b;
}
void swap(int *a,int *b)
{
	if(*a>*b)
	{
		int temp=*a;
		*a=*b;
		*b=temp;
	}
}
```

---

## 作者：Praying (赞：0)

    #include<stdio.h>
    typedef struct
     {
     int l;
     int w;
     } A;
     int main()
      {
     int m,n;
     int count=0;
     A h[6];
     while(scanf("%d%d",&m,&n)!=EOF)
     {
    int j;
     int t;
    if(m>n) t=m,m=n,n=t;
    h[0].l=m;
    h[0].w=n;
    int a,b;
     for(j=1; j<=5; j++)
     {
     scanf("%d%d",&a,&b);
      if(a>b)
      t=a,a=b,b=t;
      h[j].l=a;
      h[j].w=b;
     }
     A temp[6];
     int aa,bb;
      for(aa=1; aa<6; aa++)
      {
     for(bb=0; bb<6-aa; bb++)
     {
     if(h[bb].l>h[bb+1].l)
     temp[0]=h[bb],h[bb]=h[bb+1],h[bb+1]=temp[0];
     }
    }
     for(aa=1; aa<6; aa++)
     {
     for(bb=0; bb<6-aa; bb++)
    {
     if(h[bb].l==h[bb+1].l)
     if(h[bb].w>h[bb+1].w)
    temp[0]=h[bb],h[bb]=h[bb+1],h[bb+1]=temp[0];
   }
     
     }

         if(h[0].l==h[1].l&&h[2].l==h[3].l&&h[4].l==h[5].l)
         if(h[0].w==h[1].w&&h[2].w==h[3].w&&h[4].w==h[5].w)
         if(h[0].w==h[4].l&&h[0].l==h[2].l&&h[2].w==h[4].w) 
         printf("POSSIBLE\n");
         else printf("IMPOSSIBLE\n");
         else printf("IMPOSSIBLE\n");
         else
         printf("IMPOSSIBLE\n");
       }
    }



---

