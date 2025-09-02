# Cool loves maids

## 题目背景

Cool 非常喜欢妹子，以至于 Cool 在百度上有一个非常神奇的 ID 【雾】。

## 题目描述

Cool 现在搞清楚了女生宿舍的地形。女生宿舍是由很多栋楼构成的，它们可以被抽象成 $20\times 20$ 的方格。

Cool 的妹子们所处的地方可以被表示为实数类型的坐标。当一个妹子 $(x,y)$ 在楼 $(i,j)$ 中，当且仅当 $i \le x<i+1$，$j \le y<j+1$，$i,j\in \Z$。两个妹子之间有距离，当且仅当一个妹子所在的楼的横纵坐标均小于另一个妹子所在的楼，此时她们之间的距离为她们自身坐标的曼哈顿距离。

现在 Cool 要搞一个大统计：求 $n$ 个妹子之间所有距离之和。

## 说明/提示

### 数据范围及约定

对于全部数据，保证 $1\le n\le 5\times 10^6$。

## 样例 #1

### 输入

```
6
3 5 7 11 13 17```

### 输出

```
17.52167```

# 题解

## 作者：AoPSer (赞：4)

这题刚刚看一下：不就是一道枚举吗？

后来发现：好像会超时耶

于是：加优化！

将一幢楼里的妹子看做一个集合，只要将每幢楼里的妹子横，纵坐标求和然后按要求来就行了

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,rxa,rxc,rya,ryc,rza,rzc,rp=2333333,f[45][45];
long long x,y,z,num;
double mzx,mzy,a[45][45],b[45][45],ans;
int main(){
    scanf("%d%d%d%d%d%d%d",&n,&rxa,&rxc,&rya,&ryc,&rza,&rzc);
    for(register int i=1;i<=2*n;i++)
	{
        x=(y*rxa+rxc)%rp;
        y=(z*rya+ryc)%rp;
        z=(x*rza+rzc)%rp;
        if(i%2==1)mzx=(double)(x%20)+((double)(y%10)/10.000000000)+((double)(z%10)/100.00000000);
        else
		{
            mzy=(double)(x%20)+((double)(y%10)/10.000000000)+((double)(z%10)/100.00000000);
      /*rt*/
            a[(int)mzx][(int)mzy]+=mzx;
            b[(int)mzx][(int)mzy]+=mzy;
            /*求和，也可以取平均值*/
            f[(int)mzx][(int)mzy]++;
        }
    }
    for(register int i=0;i<=20;i++)
        for(register int j=0;j<=20;j++)
            for(register int k=i+1;k<=20;k++)
                for(register int l=j+1;l<=20;l++){
                    ans+=(a[k][l]+b[k][l])*(double)f[i][j]-(a[i][j]+b[i][j])*(double)f[k][l];
                    num+=f[i][j]*f[k][l];
                }//按要求来就是了
    printf("%.5f",ans/num);
}
```

---

## 作者：Limerick (赞：2)

同样，感谢yd大神对我的指导@sgygd2004

题目居然叫cool loves maids//难道是谐音吗?妹子,maids,对于英语不好的本蒟蒻来说,也只能呵呵了

首先要自己生成数据:

初始化x=y=z=0

重复:

x=(y\*rxa+rxc)%rp;

y=(z\*rya+ryc)%rp;

z=(x\*rza+rzc)%rp;

每次得到的实数即为x%20 +y%10/10+z%10/100。rp=2333333//笑疯了

如果枚举每两个妹子之间的距离,肯定会超时,所以我们需要加优化.

不知道大家注意了没有,会有许多妹子在同一栋楼里,

所以我们只需要把妹子的坐标抽象成她所在楼的坐标即可,即将每一栋楼(i,j)加上所有属于这栋楼的妹子的坐标,这样就求出了平均值的分子:坐标总和.

另外,我们需要算出每一栋楼共有多少妹子(因为如果两个妹子所属楼在同一行或是同一列,那么他们没有距离),这样是为了求平均值的分母:总人数.

这里还需要用到一个特殊的知识:曼哈顿距离

对于这个,就不一一细讲了(因为它可以衍生出很多问题,有兴趣的话,可以自己百度一下)

你只需要知道一个公式:

在平面上，坐标（x1, y1）的i点与坐标（x2, y2）的j点的曼哈顿距离为：

d(i,j)=|X1-X2|+|Y1-Y2|.
OK,闲话少叙,我们来贴上AC代码:

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<time.h>
using namespace std;
```
/\*
P3361 cool loves maids 题解

\*/
```cpp
int n,rxa,rxc,rya,ryc,rza,rzc,rp=2333333,i,j,k,l,f[45][45];
long long x,y,z,arr;
double xxx,yyy,a[45][45],b[45][45],ans;//注意:每个妹子的坐标是实数,所以要用double
int main(){
    cin>>n>>rxa>>rxc>>rya>>ryc>>rza>>rzc;//生成数据:读入
    for(i=1;i<=2*n;i++){
        x=(y*rxa+rxc)%rp;
        y=(z*rya+ryc)%rp;
        z=(x*rza+rzc)%rp;//你怎么讲我怎么写
        if(i%2==1){
            xxx=(double)(x%20)+(double)((double)(y%10)/10.0)+(double)((double)(z%10)/100.0);//生成的每个妹子的横坐标
        }
        else{
            yyy=(double)(x%20)+(double)((double)(y%10)/10.0)+(double)((double)(z%10)/100.0);//生成的每个妹子的纵坐标
            a[(int)xxx][(int)yyy]+=xxx;//此妹子所属楼的横坐标加上此妹子的横坐标
            b[(int)xxx][(int)yyy]+=yyy;//此妹子所属楼的纵坐标加上此妹子的纵坐标
            f[(int)xxx][(int)yyy]++;//此妹子所属楼的妹子数+1
```
/\*
另:当且仅当[x]=i, [y]=j时,妹子(x,y)属于楼(i,j) i,j均为实数

\*/
```cpp
        }
    }
    for(i=0;i<=20;i++){//枚举每栋楼
        for(j=0;j<=20;j++){
            for(k=i+1;k<=20;k++){//枚举与现在枚举到的楼不在同一行或是同一列的楼
                for(l=j+1;l<=20;l++){
                    ans+=(a[k][l]+b[k][l])*(double)f[i][j]-(a[i][j]+b[i][j])*(double)f[k][l];//分子:将两栋楼中所有妹子的坐标*其妹子总数,用曼哈顿距离一下算出所有妹子的距离
                    arr+=f[i][j]*f[k][l];//分母:两两结合,所以将两栋楼中的妹子数相乘
                }
            }
        }
    }
    printf("%.5f",ans/arr);//平均值,分子/分母
    return 0;//结束
}

```

---

## 作者：_Lemon_ (赞：1)

先说一下曼哈顿距离：其实就是把两点的横纵坐标分别相减然后加起来。

因为妹子的人数很多，暴力枚举所有肯定超时，但仔细观察可以发现整张地图只有20\*20栋宿舍。

所以不妨枚举所栋楼，肯定就不会超时了。

这时我们需要先生成数据（注意double与int类型的转换）。

然后预处理一下数据，

我们发现如果a楼里面有ra人，

b楼里面有rb人。

那么a楼里面每个人都会与b楼里面每个人配对，形成ra×rb对。

不难发现每栋楼里面的人都是一起计算的。

那么可以先把a楼里面所有人横纵都加起来，再把人数记录一下。

接下来枚举每栋楼，算出距离之和与配对数之和，

然后就可以愉快的AC了！

下面是一份丑陋的代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
long long rxa,rxc,rya,ryc,rza,rzc,rp,all;
double x[8000005],y[8000005];
long long nummap[25][25];
double pomap[25][25];
double ans; 
int main()
{
    long long xx=0,yy=0,zz=0;
    rp=2333333;
    int n,i,j;
    double xa,xb,xc;
    cin>>n;
    cin>>rxa>>rxc>>rya>>ryc>>rza>>rzc;
    for(i=1;i<=n;i++)
      {
        xx=(yy * rxa + rxc) % rp;
        yy=(zz * rya + ryc) % rp;
        zz=(xx * rza + rzc) % rp;
        xa=yy%10;
        xb=zz%10;
        x[i]=xx % 20 +xa/10+xb/100;
        xx=(yy * rxa + rxc) % rp;
        yy=(zz * rya + ryc) % rp;
        zz=(xx * rza + rzc) % rp;
        xa=yy%10;
        xb=zz%10;
        y[i]=xx % 20 +xa/10+xb/100;
    //    cout<<x[i]<<' '<<y[i]<<endl;
      }
    for(i=1;i<=n;i++)
      {
        int biu=x[i],e=y[i];
//        cout<<biu<<' '<<e<<endl;
        nummap[biu][e]++;
        pomap[biu][e]+=(x[i]+y[i]);
      }
//    for(i=1;i<=20;i++)
//      {
//        for(j=1;j<=20;j++)
 //       cout<<pomap[i][j]<<' ';
//        cout<<endl;
 //     }
    for(i=1;i<=20;i++)
      for(j=1;j<=20;j++)
         if(nummap[i][j]>0)
         {
         for(int ii=0;ii<i;ii++)
           for(int jj=0;jj<j;jj++)
           {
            if(nummap[ii][jj]>0)
            {
             ans+=(pomap[i][j]*nummap[ii][jj]-nummap[i][j]*pomap[ii][jj]);
          //   cout<<ans<<endl;
             all+=(nummap[i][j]*nummap[ii][jj]);
            }
           }
         }
   double ans1;
   ans1=ans/all;
   printf("%.5f",ans1);
}
```

---

## 作者：Frozen_Ladybug (赞：0)

刚开始看感觉就是枚举，但在本地测试数据较大的会超时。

那就加优化即可（也不需要那么麻烦的操作），剪枝，就是让之后的 $k=i+1$ 和 $l=j+1$ 就能过了。

接下来只是求所有人的坐标平均值，就是坐标总和除以总人数。

简单介绍一下曼哈顿距离（和这道题最前面的说明有关）：$d=\vert x_1-x_2 \vert + \vert y_1-y_2 \vert$。

```c
#include<bits/stdc++.h>
using namespace std;
int n,xa,xc,ya,yc,za,zc,f[45][45];
const int m=2333333;//如题的取模运算
long long x,y,z,num;
double mx,my,a[45][45],b[45][45],ans;//妹子的坐标不需要单独开数组
int main(){
    scanf("%d%d%d%d%d%d%d",&n,&xa,&xc,&ya,&yc,&za,&zc);//读入Cool的坐标
    for(int i=1;i<=2*n;i++){
        x=(y*xa+xc)%m;
        y=(z*ya+yc)%m;
        z=(x*za+zc)%m;//这个算坐标平均值的过程重复就行了,注意取模
        if(i%2==1)mx=(double)(x%20)+((double)(y%10)/10.000000000)+((double)(z%10)/100.00000000);//妹子的横坐标
        else{
            my=(double)(x%20)+((double)(y%10)/10.000000000)+((double)(z%10)/100.00000000);//妹子的纵坐标
            a[(int)mx][(int)my]+=mx;
            b[(int)mx][(int)my]+=my;//所属楼的横纵坐标加上这个妹子所在的横坐标和纵坐标
            f[(int)mx][(int)my]++;//这栋楼的妹子数量加1
        }
    }
    for(int i=0;i<=20;i++)
        for(int j=0;j<=20;j++)//直接暴力，枚举每栋楼
            for(int k=i+1;k<=20;k++)//枚举与现在枚举到的楼不在同一行且不在同一列的楼
                for(int l=j+1;l<=20;l++){//此处的优化就是从枚举过的+1再枚举新的
                    ans+=(a[k][l]+b[k][l])*(double)f[i][j]-(a[i][j]+b[i][j])*(double)f[k][l];//曼哈顿坐标算距离，需要将变量转化
                    num+=f[i][j]*f[k][l];//分母直接相乘即可
                }
    printf("%.5f",ans/num);//输出答案，就是分子除以分母
    return 0;//结束
}
```


---

