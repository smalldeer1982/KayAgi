# [USACO5.3] 窗体面积Window Area

## 题目描述

你刚刚接手一项窗体界面工程。窗体界面还算简单，而且幸运的是，你不必显示实际的窗体。有 $5$ 种基本操作：
- 创建一个新窗体；
- 将窗体置顶；
- 将窗体置底；
- 删除一个窗体；
- 输出窗体可见部分的百分比（就是，不被其它窗体覆盖的部分）。

## 说明/提示

题目翻译来自 NOCOW。

USACO Training Section 5.3。

## 样例 #1

### 输入

```
w(a,10,132,20,12)
w(b,8,76,124,15)
s(a)```

### 输出

```
49.167```

# 题解

## 作者：「QQ红包」 (赞：14)

题解by：redbag

大概思路同楼下

先离散，然后再根据顺序把该减的减掉，该标记的标记，具体见代码

```cpp

/*
ID: ylx14271
PROG: window
LANG: C++
*/
#include<set>
#include<map>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath> 
#include<iostream>
#include<algorithm>
using namespace std;
char ch;
int x,y,x1,y12;
int n;//存窗户的个数/标号
struct node
{
    int x1,x2,y11,y2;
    int id,deep,flag;
} a[2500];//存每个窗户的四个边界（x1:左，x2:右，y1：下，y2:上 
map<char,int> a1;
int max1,min1;
int zx[2500],lx,ux[45000];
int zy[2500],ly,uy[45000];
int f[250][250];
void sum(int x)
{
    memset(f,0,sizeof(f));
    lx=0;ly=0;
    for (int i=1;i<=n;i++)
    {
        if (a[i].flag==0||a[i].deep<a[x].deep) continue;//压在下面的或者不存在的不要处理 
        zx[++lx]=a[i].x1;zx[++lx]=a[i].x2; 
        zy[++ly]=a[i].y11;zy[++ly]=a[i].y2;//存坐标 
    }
    sort(zx+1,zx+lx+1);//排序 
    sort(zy+1,zy+ly+1); 
    
    int t=0;
    for (int i=1;i<=lx;i++)
    {
        //cout<<zx[i]<<" ";
        if (zx[i]!=zx[i-1])
        {
            t++;
            zx[t]=zx[i];
            ux[zx[i]]=t;
        }
    } 
    lx=t;
    //离散 
    t=0;
    for (int i=1;i<=ly;i++)
    {
        //cout<<zy[i]<<" ";
        if (zy[i]!=zy[i-1])
        {
            t++;
            zy[t]=zy[i];
            uy[zy[i]]=t; 
        }
    } 
    ly=t;
    //离散 

    for (int i=ux[a[x].x1];i<=ux[a[x].x2]-1;i++)
        for (int j=uy[a[x].y11];j<=uy[a[x].y2]-1;j++)
        f[i][j]=1;//窗户部分标记 
    for (int i=1;i<=n;i++)
        if (a[i].deep>a[x].deep&&a[i].flag==1)
        {
            for (int j=ux[a[i].x1];j<=ux[a[i].x2]-1;j++)
                for (int k=uy[a[i].y11];k<=uy[a[i].y2]-1;k++)
                f[j][k]=0;
        }//有其他窗户覆盖在上面的也标记 
    double sum1=0.0;
    for (int i=1;i<lx;i++)
        for (int j=1;j<ly;j++)
        {
            sum1+=f[i][j]*(zx[i+1]-zx[i])*(zy[j+1]-zy[j]);
        }//算面积 
    double x1=100*(double)(sum1)/(double)((a[x].x2-a[x].x1)*(a[x].y2-a[x].y11));
    printf("%.3lf\n",x1);//输出 
    return;
}
int main()
{
    freopen("window.in","r",stdin);
    freopen("window.out","w",stdout);
    while (scanf("%c",&ch)!=EOF)
    {
        if (ch=='w')
        {
            scanf("(%c,%d,%d,%d,%d)",&ch,&x,&y,&x1,&y12);
            n++;//存有多少个 
            a1[ch]=n;//ch的编号存起来 
            a[n].x1=min(x,x1);a[n].x2=max(x,x1);
            a[n].y11=min(y,y12);a[n].y2=max(y,y12);
            a[n].id=ch;a[n].flag=1;
            max1++;//全部存起来 
            a[n].deep=max1;//存深度 
        } else
        if (ch=='t')//置顶 
        {
            scanf("(%c)",&ch);
            a[a1[ch]].deep=++max1;
        } else
        if (ch=='b')//置底 
        {
            scanf("(%c)",&ch);
            a[a1[ch]].deep=--min1;
        } else
        if (ch=='d')//删除 
        {
            scanf("(%c)",&ch);
            a[a1[ch]].flag=0;
        } else
        if (ch=='s')//统计 
        {
            scanf("(%c)",&ch);
            sum(a1[ch]); 
        } 
        getchar();getchar();//洛谷有行末空格 
    }
    return 0;
}
```

---

## 作者：Brave_Cattle (赞：11)

**题解:** 这里使用了一种叫做上浮法的算法.

考虑当前要上浮的矩形在第$k$层,需要上升到第$k-1$层,那么它上面的矩形和它只有两种情况:相交或者不相交,显然不相交的情况可以不用考虑,直接将它提到第$k-1$层就可以了.

那么相交的情况怎么处理呢?我们来看一下下面这张图:
![](http://images.cnblogs.com/cnblogs_com/BCOI/1261368/o_float_method.png)



图中蓝色的是我们正在上浮的矩形$B(blue)$,红色的是在$R(red)$上面一层挡住$B$一部分面积的矩形$R$,我们可以发现,只要$R,B$有交集,那么就可以根据$R$的上下左右边将$B$分成几个矩形继续上浮(其他的情况可以自己手画一下,因为作图有点麻烦就不再举例子了).

那么根据这个原理,我们就可以将正在上升的矩形分为最多$4$部分继续上浮,这一过程可以用$dfs$来实现,具体实现看一下代码.

```
void dfs(int k, int x1, int y1, int x2, int y2){
    if(x1 == x2 || y1 == y2) return; // 判断递归的边界条件
    if(!k){ ans += (double)(x2-x1)*(y2-y1); return; }
    int a1 = a[k].x1, b1 = a[k].y1, a2 = a[k].x2, b2 = a[k].y2;
    if(a2 < x1 || a1 > x2 || b2 < y1 || b1 > y2){
        dfs(k-1, x1, y1, x2, y2); return; // 无交集直接继续下一层不需要回溯
    }
    if(a1 <= x1 && b1 <= y1 && x2 <= a2 && y2 <= b2) return; // 已经被某个矩形完全覆盖了那么就不可能被看到了,直接return
    dfs(k-1, x1, min(y2, b2), min(x2, a2), y2); // up
    dfs(k-1, min(x2, a2), max(y1, b1), x2, y2); // right
    dfs(k-1, max(x1, a1), y1, x2, max(y1, b1)); // down
    dfs(k-1, x1, y1, max(x1, a1), min(y2, b2)); // left
    //这里的四个dfs就是将正在上浮的矩形分割的过程,参数可以自己画几个栗子模拟一下
}
```

知道了如何统计矩形面积,剩下的只需要模拟一下就好了.

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100;
// N只有100是因为窗口标识符只有大小写字母和0到9

int used[300], cnt = 0;
double ans = 0, tot = 0;

struct window{
    int x1, x2, y1, y2; char c;
    window(int _x1 = 0, int _y1 = 0, int _x2 = 0, int _y2 = 0, int _c = 0){
        x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2, c = _c;
    }
    bool operator == (const window &a) const {
        return c == a.c;
    }
    bool operator < (const window &a) const {
        if(x1 != a.x1) return x1 < a.x1;
        if(y1 != a.y1) return y1 < a.y1;
        if(x2 != a.x2) return x2 < a.x2;
        return y2 < a.y2;
    }
}a[N], win[300];

void move(window x, int f){
    int pos = 0;
    for(int i = 1; i <= cnt; i++)
        if(a[i] == x){ pos = i; break; }
    if(f == 0) for(int i = pos; i >= 2; i--) swap(a[i], a[i-1]);
    else for(int i = pos; i < cnt; i++) swap(a[i], a[i+1]);
}

void delet(window x){
    int pos;
    for(int i = 1; i <= cnt; i++)
        if(a[i] == x) pos = i;
    used[x.c] = 0, win[x.c] = (window){ 0, 0, 0, 0, 0 };
    for(int i = pos+1; i <= cnt; i++) a[i-1] = a[i];
    cnt--;
}

void dfs(int k, int x1, int y1, int x2, int y2){
    if(x1 == x2 || y1 == y2) return;
    if(!k){ ans += (double)(x2-x1)*(y2-y1); return; }
    int a1 = a[k].x1, b1 = a[k].y1, a2 = a[k].x2, b2 = a[k].y2;
    if(a2 < x1 || a1 > x2 || b2 < y1 || b1 > y2){
        dfs(k-1, x1, y1, x2, y2); return;
    }
    if(a1 <= x1 && b1 <= y1 && x2 <= a2 && y2 <= b2) return;
    dfs(k-1, x1, min(y2, b2), min(x2, a2), y2); // up
    dfs(k-1, min(x2, a2), max(y1, b1), x2, y2); // right
    dfs(k-1, max(x1, a1), y1, x2, max(y1, b1)); // down
    dfs(k-1, x1, y1, max(x1, a1), min(y2, b2)); // left
}

int main(){
    char opt, id; int x1, y1, x2, y2, pos; window tmp;
    while(cin >> opt){
        if(opt == 's'){
            scanf("(%c)", &id); pos = 0;
            for(int i = 1; i <= cnt; i++)
                if(a[i] == win[id]) pos = i;
            ans = 0, tot = (double)(a[pos].x2-a[pos].x1)*(a[pos].y2-a[pos].y1);
            dfs(pos-1, a[pos].x1, a[pos].y1, a[pos].x2, a[pos].y2);
            cout << fixed << setprecision(3) << ans*100/tot << endl;
        } else {
            scanf("(%c,%d,%d,%d,%d)", &id, &x1, &y1, &x2, &y2);
            if(x1 > x2) swap(x1, x2); if(y1 > y2) swap(y1, y2);
            tmp = (window){ x1, y1, x2, y2, id };
            if(opt == 'w'){
                if(used[id]) continue;
                win[id] = a[++cnt] = tmp, move(tmp, 0);
            }
            if(opt == 't') move(tmp, 0);
            if(opt == 'b') move(tmp, 1);
            if(opt == 'd') delet(tmp);
        }
        opt = getchar();
    }
    return 0;
}
```


---

## 作者：离散小波变换° (赞：5)

如果$\LaTeX$崩了，[请在博客中查看](https://www.luogu.com.cn/blog/McHf/p2745-discrete)。

## 题目大意

要求模拟一个窗体界面。共有若干操作：

- 创建一个新窗体：$\operatorname{w}(I,x,y,X,Y)$，标识符为$I$，两个对角为$(x,y),(X,Y)$

- 将窗体置顶： $\operatorname{t}(I)$，置顶标识符为$I$的窗体。

- 将窗体置底： $\operatorname{b}(I)$，置底标识符为$I$的窗体。

- 删除一个窗体：$\operatorname{d}(I)$，删除标识符为$I$的窗体。

- 输出窗体可见部分的百分比：$\operatorname{s}(I)$。

满足$I\in\mathtt{\{'a'\cdots 'z','A'\cdots 'Z','1'\cdots'9'\}}, x,y\in[1,32767],s\text{操作不超过500次}$
## 题解

### 读入数据

对于每个操作，我们只需要读入第一个字母，再根据操作的种类确定接下来要读入什么就行了。可以手写读入，排除`(`,`)`,`\n`,`\r`这些无用的符号。

### 窗口模拟

这是一道挺好的模拟题，挺考验选手的码力的……

虽然题目并没有明确写出总操作数是多少，以及窗口的具体数量，但从标识符的可能种类可以发现窗口在同一时刻不会很多；查询操作不会很多。其他的操作越快越好。

因此我们可以用链表模拟窗口的删除、置顶、置底、创建。具体来说，我们可以直接用双向链表实现删除和创建；对于置底、置顶，先创建一个虚的最顶层窗口$head$，以及虚的最底层窗口$tail$。置顶$I$相当于删除$I$并在$head$后面插入$I$；置底相当于在$tail$前面插入$I$。

### 查询操作

很显然，我们只需要处理在$I$之上的块。考虑到$x,y\in[1,32767]$，我们先进行离散化。同时，我们计算出离散化后每个有用的点（即当前存在的所有窗口的$4$个顶点坐标），然后用差分的方法染色，最后统计有多少块被覆盖。

举个栗子：

$$\tt\begin{matrix}\backslash  & -200 & -150 & 0 & 12 & 16 & 233\cr -100 & A & A & A\cr 25 & A & AB & AB & B & B\cr 500 &  & B & B & B & B\cr 700\cr \end{matrix}$$

我们进行离散化

$$\tt\begin{matrix}\backslash  & 1 & 2 & 3 & 4 & 5 & 6\cr 1 & A & A & A\cr 2 & A & AB & AB & B & B\cr 3 &  & B & B & B & B\cr 4\cr \end{matrix}$$

然后进行差分。

$$\tt\begin{matrix}\backslash  & 1 & 2 & 3 & 4 & 5 & 6\cr 1 & +1 & 0 & 0 & -1 & 0 & 0\cr 2 & 0 & +1 & 0 & 0 & 0 & -1\cr 3 & -1 & 0 & 0 & +1 & 0 & 0\cr 3 & 0 & -1 & 0 & 0 & 0 & +1\cr \end{matrix}$$

我们将它竖着扫一遍

$$\tt\begin{matrix}\backslash  & 1 & 2 & 3 & 4 & 5 & 6\cr 1 & +1 & 0 & 0 & -1 & 0 & 0\cr 2 & +1 & +1 & 0 & -1 & 0 & -1\cr 3 & 0 & +1 & 0 & 0 & 0 & -1\cr 3 & 0 & 0 & 0 & 0 & 0 & 0\cr \end{matrix}$$

再横着扫一遍（其实先横着扫再竖着扫也一样）

$$\tt\begin{matrix}\backslash  & 1 & 2 & 3 & 4 & 5 & 6\cr 1 & 1 & 1 & 1 & 0 & 0 & 0\cr 2 & 1 & 2 & 2 & 1 & 1 & 0\cr 3 & 0 & 1 & 1 & 1 & 1 & 0\cr 3 & 0 & 0 & 0 & 0 & 0 & 0\cr \end{matrix}$$

最后，按照我们要查询的那个窗口的坐标暴力扫描里面的块。若权值不为$0$，答案减去它离散化前的面积。

时间复杂度$\mathcal O(N\times N \times M)$。其中$N$为存在的块的总个数，$M$为查询操作的总个数。因为$N\le 62,M\le 500$，可以通过本题。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;

typedef long long LL;
const int INF =2147483647;
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0')
    w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0' &  & c<='9')
    ret=ret*10+c-'0';
    return ret*w;
}  
int hsh(char ID){
    if('a'<=ID &  & ID<='z') return ID-'a'+1;
    if('A'<=ID &  & ID<='Z') return ID-'A'+1+26;
    return ID-'0'+26+26+1;
}
char readc(){
    char c; while(((c=getchar())=='('||c==')'||c==' '||c=='\n'||c=='\r') &  & c!=EOF); return c;
}
const int MAXN =26+26+10+3;
int X1[MAXN],Y1[MAXN],X2[MAXN],Y2[MAXN],rd;
int bef[MAXN],nxt[MAXN];
void dlt(int ID){
    nxt[bef[ID]]=nxt[ID],bef[nxt[ID]]=bef[ID];
}
void ist(int bf,int ID){
    bef[ID]=bf,nxt[ID]=nxt[bf],bef[nxt[bf]]=ID,nxt[bf]=ID;
}
int e=MAXN-1,tot,tp1,tp2,Q1[MAXN*2],Q2[MAXN*2];
bool use[MAXN*2][MAXN*2];
map<int,int> mmpA,mmpB;
int main(){
    bef[e]=0,nxt[0]=e;
    while((rd=readc())!=EOF){
        int ID=hsh(readc()); 
        if(rd=='w'){
            ist(0,ID),X1[ID]=qread(),Y1[ID]=qread(),
            X2[ID]=qread(),Y2[ID]=qread();
            if(X1[ID]>X2[ID]) swap(X1[ID],X2[ID]);
            if(Y1[ID]>Y2[ID]) swap(Y1[ID],Y2[ID]);
        }
        else if(rd=='d') dlt(ID);
        else if(rd=='t') dlt(ID),ist(0,ID);
        else if(rd=='b') dlt(ID),ist(bef[e],ID);
        else if(rd=='s'){
            mmpA.clear(),mmpB.clear(); tp1=tp2=0; int ans=0;
            for(int i=0;i!=ID;){
                i=nxt[i];
                Q1[++tp1]=X1[i],Q1[++tp1]=X2[i],Q2[++tp2]=Y1[i],Q2[++tp2]=Y2[i];
            }
            sort(Q1+1,Q1+1+tp1),sort(Q2+1,Q2+1+tp2);
            tp1=unique(Q1+1,Q1+1+tp1)-Q1-1,tp2=unique(Q2+1,Q2+1+tp2)-Q2-1;
            up(1,tp1,i) mmpA[Q1[i]]=i;up(1,tp2,i) mmpB[Q2[i]]=i;
            memset(use,0,sizeof(use));
            for(int i=nxt[0];i!=ID;i=nxt[i]){
                up(mmpA[X1[i]],mmpA[X2[i]]-1,a)
                up(mmpB[Y1[i]],mmpB[Y2[i]]-1,b) use[a][b]=true;
            }
            up(mmpA[X1[ID]],mmpA[X2[ID]]-1,a)
            up(mmpB[Y1[ID]],mmpB[Y2[ID]]-1,b)
            if(!use[a][b]) ans+=(Q1[a+1]-Q1[a])*(Q2[b+1]-Q2[b]);
            printf("%.3lf\n",(double)100.0*ans/((X2[ID]-X1[ID])*(Y2[ID]-Y1[ID])));
        }
    }
    return 0;
}
```

---

## 作者：Myrcella (赞：4)

不会离散化的同学看这里！！！！

这题虽然是模拟题但还是有一定技巧性的

主要需要攻克的问题有以下两个

1. 如何对优先级进行操作
2. 如何计算可见部分面积

首先第一个问题应该相对较好解决。定义一个qt qw（可以理解为队列头和队列尾）然后对应每个操作的更新就十分容易了
- w：每次创建新窗口就将qw++ 把新窗口的标识符加入vector 并把该窗口的优先级赋为qw（注意坑点！题目中说：“你不能用已经存在的标识符来创建窗体，但是你可以删除一个窗体后再用已删除窗体的标识符来创建窗体。”即新建操作的标识符有可能相同，这时得把之前的覆盖掉，也就是说在原有基础上操作，而不是直接再次新加入一个//此处表述不清看了代码就知道了）
- t: qw++ 并把该窗口的优先级赋为qw
- d：qt-- 并把该窗口的优先级赋为qt

然后就是如何求面积了 可以类比弦图用比当前矩形优先级高的矩形将当前矩形分为五个部分 然后对1 2 3 4四个部分再进行dfs

111122

440022

440022

443333

如果两个矩形只是有一部分重合，也可以如此处理，不过得运用好min max（看代码！！） 这样就会有一个部分因为不存在而不会被计算

这个做法是从一位dalao的博客里学来的[[USACO5.3]Window Area【窗体面积】](https://blog.csdn.net/zsyzClb/article/details/80580309)
讲解的挺详细的，大家可以去学习一下（他的代码总体思路也和我差不多）我觉得这个做法还是自己对着图揣摩揣摩好 我也不详细介绍了

这道题最可爱的地方在于数据范围很小。因为所有窗口的唯一标识符在'A'-'z'的范围内，即最多只可能有52个，所以写的时候可以暴力一些。代码如下（PS：因为这道题之前并没有想到dfs所以算法非常暴力和诡异 后来重新修改时懒得从头写起 于是代码非常非常的丑陋。求轻喷）
```cpp
#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

struct node{
	int x1,y1,x2,y2,p;
}a[60];//这个名字起的不好。。其实是记录每个矩形的

vector <int> win;//记录每个举行的标识符
double tot=0.0;//记录当前查询矩形的可见面积

void solve(int cur,int xx1,int yy1,int xx2,int yy2,int dep){//先看w操作中关于x1 y1 y1 y2的解释！！
	//最精髓的dfs求面积
	if (xx1==xx2||yy1==yy2) return;//矩形不存在
	bool ok=false;
	for (int i=cur;i<win.size();i++) 
		if (a[win[i]].p>dep) {//优先级更高
			int x1=a[win[i]].x1,y1=a[win[i]].y1;
			int x2=a[win[i]].x2,y2=a[win[i]].y2;
			if (x1>xx2||x2<xx1||y1>yy2||y2<yy1) continue;
			else if (x1<xx1&&y1<yy1&&x2>xx2&&y2>yy2) return;
			else {//这段很是重要！！！4个部分以及使用max min的目的 一定对着图好好理解
				ok=true;
				solve(cur+1,xx1,min(y2,yy2),min(x2,xx2),yy2,dep);
				solve(cur+1,min(xx2,x2),max(y1,yy1),xx2,yy2,dep);
				solve(cur+1,max(xx1,x1),yy1,xx2,max(y1,yy1),dep);
				solve(cur+1,xx1,yy1,max(x1,xx1),min(y2,yy2),dep);
				break;
                //找到它上面的一个就行了 不然就会出问题辣 
                //语文太差不知道怎么描述不过这个应该很好理解吧
			}
		}
	if (!ok) tot+=(double)abs((xx2-xx1)*(yy1-yy2));
    //ok=false即代表该矩形已不被覆盖，solve函数也没有再被调用了，即可更新tot值
	return;
}

int main(){
	char ope;
	int qt=0,qw=-1;
	while (scanf("%c",&ope)!=EOF){
		if (ope=='s') {
			char id;
			scanf("(%c)",&id);
			int ID=id-'A';
			tot=0;//勿忘！！！
			solve(0,a[ID].x1,a[ID].y1,a[ID].x2,a[ID].y2,a[ID].p);
			printf("%.3f\n",tot/(double)abs((a[ID].x2-a[ID].x1)*(a[ID].y1-a[ID].y2))*(double)100);
		}
		if (ope=='w') {
			char id;
			int x,y,X,Y;
			scanf("(%c,%d,%d,%d,%d)\n",&id,&x,&y,&X,&Y);
			int ID=id-'A';
			bool ok=false;
			for (int i=0;i<win.size();i++) if (win[i]==ID){
				ok=true;
				break;
			}
			a[ID].x1=min(x,X);
			a[ID].y1=min(y,Y);
			a[ID].x2=max(x,X);
			a[ID].y2=max(y,Y);
            //这里的x1 y1并非是左上角的横纵坐标 而是始终满足x1<x2 y1<y2
            //也就是说其实左上角是（x1,y2） 右下角是（x2,y1）
			qw++;
			a[ID].p=qw;
			if (!ok) win.push_back(ID);//坑点！！只有这个标识符之前没出现过时才能直接往vector里加id
		}
		if (ope=='t') {//置顶
			char id;
			scanf("(%c)",&id);
			int ID=id-'A';
			qw++;
			a[ID].p=qw;
		}
		if (ope=='b'){//置底
			char id;
			scanf("(%c)",&id);
			int ID=id-'A';
			qt--;
			a[ID].p=qt;
		}
		if (ope=='d'){
			char id;
			scanf("(%c)",&id);
			int ID=id-'A';
			for (int i=0;i<win.size();i++) {
				if (win[i]==ID) {
					win.erase(win.begin()+i);
                    //直接删除 因为solve函数中对优先级的查找也是通过win的 因此无需改动a数组
					break;
				}
			}
		}
	}
}
```

---

## 作者：_Wind_Leaves_ShaDow_ (赞：2)

发现操作数很少只有 $600$。

优先级很好做。记录一下当前优先级最大的和最小的，要改优先级直接改成新的最大最小值。删除你打一个 tag 就可以。

查询操作就是 [扫描线板子](https://www.luogu.com.cn/problem/P5490)，你把所有优先级大于要查询的矩形和当前矩形求交，然后对这些矩形求面积并。

做一次复杂度是 $O(n\log V)$，最多只有 $T$ 次操作，所以复杂度是 $O(Tn\log V)$。

因为数据范围很小就能直接过了。无脑把东西码上去，稍微考验一点码力？

```cpp
//模拟赛考的，写得有点丑
#include <bits/stdc++.h>
#define lint __int128
#define int long long
#define Il inline
#define Rg register
#define Ri Rg int
#define fi first
#define se second
#define vec vector
#define pb push_back
#define IT ::iterator
#define p_que priority_queue

using namespace std;
//typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef pair<pii,pii> ppp;
const int N=600,M=32767;
const db eps=1e-9,pi=acos(-1.0);

int Q,id=0,hl=1,hr=0;
map<char,int>mp;
struct Node{
	int xa,ya,xb,yb,h;//端点，优先级
	bool del;//删除标记
	Il int su(){return (xb-xa)*(yb-ya);}//求面积
}a[N+5];

Il bool noj(Node x,Node y){return (x.ya>y.yb||y.ya>x.yb||x.xa>y.xb||y.xa>x.xb);}//判断是否有交

Il ppp jiao(Node x,Node y){return {{max(x.xa,y.xa),max(x.ya,y.ya)},{min(x.xb,y.xb),min(x.yb,y.yb)}};}//得到交后矩形

int qn;
struct Qry{int px,pl,pr,f;Il bool operator <(const Qry &qtmp)const{return px<qtmp.px;}}qy[(N<<1)+5];

Il void ren(int &xa,int &ya,int &xb,int &yb){
	int mxx=max(xa,xb),mnx=min(xa,xb),mxy=max(ya,yb),mny=min(ya,yb);
	xa=mnx,xb=mxx,ya=mny,yb=mxy;return;
}//不知道输入的对角是什么，根据个人习惯改成左下角和右上角的点

int sg[(M<<2)+5],cv[(M<<2)+5];

Il void pup(int p,int l,int r){
	if(cv[p])sg[p]=r-l+1;
	else sg[p]=sg[p<<1]+sg[p<<1|1];
	return;
}

Il void add(int ql,int qr,int l,int r,int p,int x){
	if(ql>qr)return;
	if(ql<=l&&r<=qr){cv[p]+=x;pup(p,l,r);return;}
	int mid=(l+r)>>1;
	if(ql<=mid)add(ql,qr,l,mid,p<<1,x);
	if(qr>mid)add(ql,qr,mid+1,r,p<<1|1,x);
	pup(p,l,r);return;
}//板子

Il void solve(int ip){qn=0;
	for(Ri i=1;i<=id;i++){
        if(i==ip||a[i].del||a[ip].h<a[i].h||noj(a[ip],a[i]))continue;
		ppp tj=jiao(a[ip],a[i]);
		qy[++qn]={tj.fi.fi,tj.fi.se,tj.se.se,1};
		qy[++qn]={tj.se.fi,tj.fi.se,tj.se.se,-1};
	}
	sort(qy+1,qy+qn+1);memset(cv,0,sizeof(cv)),memset(sg,0,sizeof(sg));
	int sm=0,mj=a[ip].su();
	for(Ri i=1;i<qn;i++){
		add(qy[i].pl,qy[i].pr-1,1,M,1,qy[i].f);
		sm+=sg[1]*(qy[i+1].px-qy[i].px);
	}
	cout<<fixed<<setprecision(3)<<(db)((mj-sm)*100.0/mj)<<'\n';
	return;
}

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>Q;char op;
	while(cin>>op){
		char tc,na;
		if(op=='w'){
			int txa,tya,txb,tyb,p;
			cin>>tc>>na>>tc>>txa>>tc>>tya>>tc>>txb>>tc>>tyb>>tc;
			ren(txa,tya,txb,tyb);
			if(mp.count(na))p=mp[na];else mp[na]=p=++id;
			a[p]={txa,tya,txb,tyb,--hl,0};
		}else if(op=='t'){
			cin>>tc>>na>>tc;
			a[mp[na]].h=--hl;
		}else if(op=='b'){
			cin>>tc>>na>>tc;
			a[mp[na]].h=++hr;
		}else if(op=='d'){
			cin>>tc>>na>>tc;
			a[mp[na]].del=1;
		}else{
			cin>>tc>>na>>tc;
			solve(mp[na]);
		}
	}
	return 0; 
}
```

---

## 作者：ZHONGZIJIE0608 (赞：0)

首先，对于窗口的插入删除，为了节省复杂度，我们用双向链表维护。（单向链表不好找插入位置）

“置顶”“置底”两种操作可以通过插入删除解决。

对于“查询”操作，显然是只有顶部到当前窗口的信息是有用的。考虑在当前窗口的大小内维护被覆盖的区域面积。

这里不使用扫描线。注意到窗口数 $N$ 和查询操作数 $M$ 很小，考虑直接暴力维护。

注意到横纵坐标在 $[1,32767]$ 范围内。一个一个格子维护并不现实。考虑离散化，把格子划分在一些矩形内。

每次枚举矩形的左端点维护信息即可。

输入时要过滤掉多余的字符。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=70;
int Hash(char x){
	if(x>='A'&&x<='Z')return x-'A'+1;
	if(x>='a'&&x<='z')return (x-'a'+1)+('Z'-'A'+1);
	return (x-'0'+1)+('z'-'a'+1)+('Z'-'A'+1);
}
struct Matrix{int X1,X2,Y1,Y2,pre,nxt;}a[N];
void Delete(int x){
	a[a[x].pre].nxt=a[x].nxt;
	a[a[x].nxt].pre=a[x].pre;
}
void Insert(int pos,int x){
	a[x].pre=pos;
	a[x].nxt=a[pos].nxt;
	a[a[pos].nxt].pre=x;
	a[pos].nxt=x;
}
int bottom=N-1;
int x[N*2],cntx,y[N*2],cnty;
unordered_map<int,int>lsx,lsy;
bool vis[N*2][N*2];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	a[bottom].pre=0;a[0].nxt=bottom;
	int T;cin>>T;
	char op;
	while(cin>>op){
		char _1,_2,_3,_4,_5,_6,ID;
		if(op=='w'){
			cin>>_1>>ID;
			int id=Hash(ID);
			Insert(0,id);
			cin>>_2>>a[id].X1>>_3>>a[id].Y1>>_4>>a[id].X2>>_5>>a[id].Y2>>_6;
			if(a[id].X1>a[id].X2)swap(a[id].X1,a[id].X2);
			if(a[id].Y1>a[id].Y2)swap(a[id].Y1,a[id].Y2);
		}
		else{
			cin>>_1>>ID>>_2;int id=Hash(ID);
			if(op=='d')Delete(id);
			if(op=='b')Delete(id),Insert(a[bottom].pre,id);
			if(op=='t')Delete(id),Insert(0,id);
			if(op=='s'){
				lsx.clear();lsy.clear();cntx=cnty=0;
				memset(vis,0,sizeof vis);
				for(int i=a[0].nxt;i!=a[id].nxt;i=a[i].nxt){
					x[++cntx]=a[i].X1,x[++cntx]=a[i].X2;
					y[++cnty]=a[i].Y1,y[++cnty]=a[i].Y2;
				}
				sort(x+1,x+1+cntx);
				sort(y+1,y+1+cnty);
				cntx=unique(x+1,x+1+cntx)-x-1;
				cnty=unique(y+1,y+1+cnty)-y-1;
				for(int i=1;i<=cntx;++i)lsx[x[i]]=i;
				for(int i=1;i<=cnty;++i)lsy[y[i]]=i;
				for(int p=a[0].nxt;p!=id;p=a[p].nxt){
					for(int i=lsx[a[p].X1];i<lsx[a[p].X2]/*i 是当前块的左边界*/;++i)
					for(int j=lsy[a[p].Y1];j<lsy[a[p].Y2]/*i 是当前块的左边界*/;++j)
					vis[i][j]=1;
				}
				int ans=0;
				int p=id;
					for(int i=lsx[a[p].X1];i<lsx[a[p].X2]/*i 是当前块的左边界*/;++i)
					for(int j=lsy[a[p].Y1];j<lsy[a[p].Y2]/*i 是当前块的左边界*/;++j){
						if(!vis[i][j])ans+=(x[i+1]-x[i])*(y[j+1]-y[j]);
					}
				ans*=100;
				double S= (a[id].X2-a[id].X1)*(a[id].Y2-a[id].Y1);
				cout<<fixed<<setprecision(3)<<(ans*1.0/S)<<'\n';
			}
		}
	}
	return 0;
}
```

---

