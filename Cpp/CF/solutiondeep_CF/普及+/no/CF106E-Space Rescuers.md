# 题目信息

# Space Rescuers

## 题目描述

The Galaxy contains $ n $ planets, there are many different living creatures inhabiting each planet. And each creature can get into troubles! Space rescuers know it perfectly well and they are always ready to help anyone who really needs help. All you need to do is call for them.

Now the space rescuers plan to build the largest in the history of the Galaxy rescue station; however, the rescue station's location is yet to be determined. As some cases are real emergencies, the rescuers want to find such a point in the Galaxy from which it would be possible to get to the remotest planet in the minimum possible time. In other words, the rescuers need such point in the space that the distance between it and the planet remotest from it was minimal (if we compare this point with all other possible points in the space). Unfortunately, the rescuers can't sole this problem.

As the planets are quite remote from each other, they can be considered as points in Euclidean three-dimensional space. The distance between points $ (x_{i},y_{i},z_{i}) $ and $ (x_{j},y_{j},z_{j}) $ can be calculated by the formula ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF106E/abb554e6cf2d19bd7b5533e0d45803da81f67e64.png). The rescue station can be positioned in any point in the space. It can also coincide with some planet.

Galaxy is in danger! Save the space rescuers and find the required point for them.

## 样例 #1

### 输入

```
5
5 0 0
-5 0 0
0 3 4
4 -3 0
2 2 -2
```

### 输出

```
0.000 0.000 0.000
```

# AI分析结果

### 题目翻译
# 太空救援者

## 题目描述
银河系中有 $n$ 颗行星，每颗行星上都居住着许多不同的生物。而且每一种生物都可能陷入麻烦！太空救援者深知这一点，他们随时准备帮助任何真正需要帮助的人。你所需要做的就是向他们呼救。

现在，太空救援者计划建造银河系历史上最大的救援站；然而，救援站的位置尚未确定。由于有些情况属于真正的紧急事件，救援者们希望找到银河系中的这样一个点，从该点出发能够在尽可能短的时间内到达最远的行星。换句话说，救援者们需要在太空中找到这样一个点，使得该点与距离它最远的行星之间的距离最小（如果将这个点与太空中所有其他可能的点进行比较）。不幸的是，救援者们无法解决这个问题。

由于行星之间相距甚远，可以将它们看作欧几里得三维空间中的点。点 $(x_{i},y_{i},z_{i})$ 和点 $(x_{j},y_{j},z_{j})$ 之间的距离可以通过公式 （此处公式链接未显示，推测为两点距离公式 $\sqrt{(x_{i}-x_{j})^2+(y_{i}-y_{j})^2+(z_{i}-z_{j})^2}$）计算。救援站可以设置在太空中的任何一点，也可以与某颗行星重合。

银河系危在旦夕！拯救太空救援者，为他们找到所需的点。

## 样例 #1
### 输入
```
5
5 0 0
-5 0 0
0 3 4
4 -3 0
2 2 -2
```
### 输出
```
0.000 0.000 0.000
```

### 算法分类
数学

### 题解综合分析与结论
两题解分别采用三分法和模拟退火算法来解决问题。
 - **三分法**：利用函数的单峰性质，通过对每一维坐标进行三分查找来确定最优解。该方法逻辑清晰，理论依据充分，但需要对三分法及函数单峰性质有较深理解。
 - **模拟退火算法**：通过模拟物理退火过程，不断调整旧解以获取更优解。该方法实现相对直观，但参数设置较为关键，不同参数可能影响结果准确性和运行效率。

### 所选的题解
 - **作者：C3H5ClO (赞：2)，星级：4星**
   - **关键亮点**：通过严谨的数学推导证明函数具有单峰性，进而采用三分法求解，逻辑清晰，代码实现简洁明了。
   - **重点代码**：
```cpp
// 计算平方
inline double sqr(double x){return x*x;}
// 计算两点距离
inline double getdis(point a,point b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y)+sqr(a.z-b.z));}
// 更新最大值
inline double chkmax(double &x,double y){if(y>x)x=y;}
// 计算当前z坐标下到最远点的距离
double fz(double x,double y,double z)
{
    double res=0; point a={x,y,z};
    for(int i=1;i<=n;i++)chkmax(res,getdis(a,p[i]));
    return res;
}
// 计算当前y坐标下的最优z坐标值对应的距离
double fy(double x,double y)
{
    double l=-M,r=M,midl,midr;
    while(r-l>eps)
    {
        midr=l+(r-l)*gold; midl=l+r-midr;
        if(fz(x,y,midl)<fz(x,y,midr))r=midr;
        else l=midl;
    }
    return fz(x,y,l);
}
// 计算当前x坐标下的最优y、z坐标值对应的距离
double fx(double x)
{
    double l=-M,r=M,midl,midr;
    while(r-l>eps)
    {
        midr=l+(r-l)*gold; midl=l+r-midr;
        if(fy(x,midl)<fy(x,midr))r=midr;
        else l=midl;
    }
    return fy(x,l);
}
```
核心实现思想：通过定义多个函数，逐步利用三分法确定每一维坐标，最终得到最优解。
 - **作者：Shunpower (赞：1)，星级：3星**
   - **关键亮点**：采用模拟退火算法，针对如何从旧解调整出优秀新解给出了明确思路，即往最远点方向拉旧解。但相比三分法，其结果受参数影响较大，稳定性稍弱。
   - **重点代码**：
```cpp
ld Rand(){
    return ((ld)rand()/RAND_MAX)*2-1;
}
// 计算两点距离
ld dis(pair<ld,ld> dx,pair<ld,ld> dy,pair<ld,ld> dz){
    return sqrt((dx.fi-dx.se)*(dx.fi-dx.se)+(dy.fi-dy.se)*(dy.fi-dy.se)+(dz.fi-dz.se)*(dz.fi-dz.se));
}
// 计算当前点到最远点的距离
ld calc(ld nx,ld ny,ld nz){
    ld maxn=0;
    fr1(i,1,n) maxn=max(maxn,dis(mp(nx,x[i]),mp(ny,y[i]),mp(nz,z[i])));
    return maxn;
}
void SA(){
    ld T=1;
    ld nowx=ansx,nowy=ansy,nowz=ansz;
    while(T>=1e-10){
        ld maxn=0;
        int idx=0;
        fr1(i,1,n){
            ld d=dis(mp(nowx,x[i]),mp(nowy,y[i]),mp(nowz,z[i]));
            if(maxn<d) maxn=d,idx=i;
        }
        ld nxtx=nowx+T*(x[idx]-nowx),nxty=nowy+T*(y[idx]-nowy),nxtz=nowz+T*(z[idx]-nowz);
        ld delta=calc(nxtx,nxty,nxtz)-calc(nowx,nowy,nowz);
        if(delta<0) nowx=nxtx,nowy=nxty,nowz=nxtz;
        else if(exp(-delta/T)>Rand()) nowx=nxtx,nowy=nxty,nowz=nxtz;
        T*=0.9992;
    }
    cout.setf(ios::fixed);
    cout<<setprecision(6)<<nowx<<" "<<nowy<<" "<<nowz<<'\n';
}
```
核心实现思想：通过模拟退火过程，不断根据当前点到最远点的距离调整点的位置，直至满足终止条件。

### 最优关键思路或技巧
利用函数的单峰性质采用三分法求解，这种方法基于严谨的数学证明，在解决此类具有单峰函数性质的问题时具有较高的准确性和稳定性。

### 可拓展之处
同类型题通常围绕在多维空间中寻找满足特定距离条件的点。类似算法套路有：当函数具有单调性或单峰性时，可考虑二分或三分查找；对于复杂空间问题，模拟退火等启发式算法也可能适用。

### 洛谷相似题目
 - [P3382 【模板】三分法](https://www.luogu.com.cn/problem/P3382)
 - [P1337 末日的传说](https://www.luogu.com.cn/problem/P1337)
 - [P2678 [NOIP2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678) 

---
处理用时：78.89秒