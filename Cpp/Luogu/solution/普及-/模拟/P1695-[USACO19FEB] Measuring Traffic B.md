# [USACO19FEB] Measuring Traffic B

## 题目描述

Farmer John 的农场边上的高速公路最近出现了引人注目的流量上升，或者至少 Farmer John 看起来是这样的。为了证实这件事，他打算用一组传感器测量公路上的车流量，每个传感器被用来测量一小段路面上的车流量的数值。

不幸的是，某一天经过牛棚的时候，Farmer John 被绊倒了，装有传感器的盒子掉进了一个巨大的奶缸，之后它们就不能正常工作了。比起之前可以产生一个精确的车流量读数，现在每个传感器只能输出一个可能结果的范围。例如，一个传感器可能会给出范围 $[7,13]$，表示在这段路面上的车流量不小于 $7$，并且不大于 $13$。

高速公路经过农场的这一段长 $N$ 英里，车辆仅从一个方向通过公路，从第 $1$ 英里驶向第 $N$ 英里。Farmer John 想要安装 $N$ 个传感器——每一个监测高速公路上 $1$ 英里长的路段。在其中某些路段上，有能够使得车辆进入高速公路的上匝道；在所有这样的路段上，Farmer John 会将传感器装在上匝道上，测量流入的（近似）车流量。在某些路段上有能够使得车辆离开高速公路的下匝道；在所有这样的路段上，Farmer John 会将传感器装在下匝道上。每一个路段包含至多一个匝道。如果在公路的一个路段上没有上匝道或下匝道，Farmer John就将传感器装在高速公路的主路上。

给定 Farmer John 的 $N$ 个传感器的读数，请求出在高速公路第 $1$ 英里之前和第 $N$ 英里之后车流量的最为准确的可能范围。这些范围应当与所有 $N$ 个传感器的读数相一致。 

## 说明/提示

### 样例解释 1

在这个例子中，路段 $2$ 和路段 $3$ 的读数组合在一起告诉我们通过这两个路段的车流量为范围 $[11,14]$ 之间的某个值，因为只有这个范围与两个读数 $[10,14]$ 和 $[11,15]$ 均一致。在第 $1$ 英里，恰有 $1$ 单位的车辆通过上匝道进入，所以在第 $1$ 英里之前，车流量一定在范围 $[10,13]$ 之内。在第 $4$ 英里，$2$ 单位到 $3$ 单位之间的车辆通过下匝道离开，所以这段路之后可能的车流量范围为 $[8,12]$。 

## 样例 #1

### 输入

```
4
on 1 1
none 10 14
none 11 15
off 2 3```

### 输出

```
10 13
8 12```

# 题解

## 作者：PR_CYJ (赞：5)

# [题目传送门](https://www.luogu.com.cn/problem/P1695)
# 思路
正着遍历一遍公路，维护 $minn$ 和 $maxx$ 两个变量，分别记录当前车流量可能的最小值和最大值。

对于每一英里的公路，总共有三种情况。

1. 当前是上匝道。此时就将 $minn$ 加上当前路段车流量的下限 $dw_i$，将 $maxx$ 加上当前路段车流量的上限 $uw_i$。
2. 当前是主路。此时车流量的下限就是 $\max(minn,dw_i)$，上限则是 $\min(maxx,uw_i)$。
3. 当前是下匝道。此时就将 $minn$ 减去当前路段车流量的上限，将 $maxx$ 减去当前路段车流量的下限 $dw_i$。

这样正着遍历一遍公路，就得出了第 $n$ 公里后车流量的上限和下限。

对于第 $1$ 公里前的车流量的上限和下限，我们在反着跑一遍，就可以得到答案了。但是此时三种情况的处理方式有所变化。

1. 当前是上匝道。因为我们是反着遍历的，所以可以将其看作车辆下高速。因此就将 $minn$ 更新为 $minn-uw_i$，将 $maxx$ 更新为 $maxx-dw_i$。
2. 当前是主路。此时的更新方式和正着遍历是一样，将 $minn$ 更新为 $\max(minn,dw_i)$，将 $maxx$ 更新为 $\min(maxx,uw_i)$。
3. 当前是下匝道。因为是反着遍历，所以可以将其看作车辆上高速。因此就将 $minn$ 更新为 $minn+dw_i$，将 $maxx$ 更新为 $maxx+uw_i$。

**注意 $minn$ 和 $maxx$ 在遍历过程中可能会小于 $0$，因此要取 $\max(minn,0)$ 和 $\max(maxx,0)$。**
# 代码
切勿抄袭！！！


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=110;
int n,minn,maxx=100000,op[N],dw[N],uw[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string t;
		cin>>t>>dw[i]>>uw[i];
		if (t=="on")
			op[i]=1;
		else if (t=="none")
			op[i]=2;
		else
			op[i]=3;
	}
	for(int i=n;i>=1;i--)//反着遍历高速公路，得出第一公里前车流量的上限和下限
	{
		if (op[i]==1)
		{
			minn-=uw[i];
			maxx-=dw[i];
			minn=max(minn,0);
			maxx=max(maxx,0);//注意 minn 和 maxx 可能会小于0
		}
		else if (op[i]==2)
		{
			minn=max(minn,dw[i]);
			maxx=min(maxx,uw[i]);
		}
		else
		{
			minn+=dw[i];
			maxx+=uw[i];
		}
	}
	cout<<minn<<" "<<maxx<<"\n";
	minn=0;
	maxx=100000;//注意要将变量重新设为初始值
	for(int i=1;i<=n;i++)//正着遍历高速公路，得出第 n 公里后车流量的上限和下限
	{
		if (op[i]==1)
		{
			minn+=dw[i];
			maxx+=uw[i];
		}
		else if (op[i]==2)
		{
			minn=max(minn,dw[i]);
			maxx=min(maxx,uw[i]);
		}
		else
		{
			minn-=uw[i];
			maxx-=dw[i];
			minn=max(minn,0);
			maxx=max(maxx,0);//注意 minn 和 maxx 可能会小于0
		}
	}
	cout<<minn<<" "<<maxx<<"\n";
}
```

---

## 作者：lflby (赞：2)

# 思路

对于答案我们只需要正反模拟一次即可。

我以正的来举一个例子：


```cpp
if (a[i].zr=="none") l=max(l,a[i].l),r=min(r,a[i].r);
else if (a[i].zr=="off") l-=a[i].r,r-=a[i].l;
else if (a[i].zr=="on") l+=a[i].l,r+=a[i].r;
```

其中 `a[i].zr` 表示这个传感器的状态，`a[i].l` 和 `a[i].r` 表示传感器感应到的范围。

反的和这个大同小异，把 on 和 off 的情况反过来即可。




```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
struct dian
{
	string zr;
	int l,r;
}a[105];
int main()
{
	cin>>n;
	for (int i = 1; i <= n; i++) cin>>a[i].zr>>a[i].l>>a[i].r;
	int l=-1,r=2e9;
	for (int i = n; i >= 1; i--)
	{
		if (a[i].zr=="none") l=max(l,a[i].l),r=min(r,a[i].r);
		else if (a[i].zr=="off") l+=a[i].l,r+=a[i].r;
		else l-=a[i].r,r-=a[i].l;
		l=max(l,0);r=max(r,0);
	}
	cout<<l<<" "<<r<<'\n';
	l = -1,r = 2e9;
	for (int i = 1; i <= n; i++)
	{
		if (a[i].zr=="none") l=max(l,a[i].l),r=min(r,a[i].r);
		else if (a[i].zr=="off") l-=a[i].r,r-=a[i].l;
		else l+=a[i].l,r+=a[i].r;
		l=max(l,0);r=max(r,0);
	}
	cout<<l<<" "<<r<<'\n';
	return 0;
}
```

---

## 作者：xiaozhu_zty (赞：2)

# P1695 Mesuring Traffic 题解

 简单模拟题。有点像数学集合题，建议评橙。
 
 ### 题意简述
 一条路长 $ n $ 英里，有三种路段，分别上车、下车和无操作。给出每段路的车辆数区间，求这段路之前和结束后的车辆区间。
 
 ### 分析
 对于每个路段，有三种情况。

- 上车。此时它的车流区间是前一个区间的**最大值**加上这里上车的最**小**值、前一个区间的**最小值**加上上车的**最大值**。
- 下车。此时它的车流区间是前一个区间的最大、最小值减去这里下的最大、最小值。
- 无操作。此时区间可以被前面的区间限制，最小值取两者中大的，最大值取两者中较小的。

直接按照题意模拟即可。对于开头的流量，我们反向再扫一边即可。

### 代码
```
#include <bits/stdc++.h>
using namespace std;
int n;
string opt;
int x,y;
int s1[1000],s2[1000];
int e1[1000],e2[1000];
struct cz{
    string mtd;
    int up,dn;
};
int cnt=0;
cz m[1000];
int main(){
    cin>>n;
    s2[0]=INT_MAX-1000;
    for (int i = 1;i<=n;i++){
        cin>>opt>>x>>y;
        if (opt=="off"){
            m[n-cnt]={"off",x,y};
            cnt++;
            s1[i]=max(0,s1[i-1]-y);
            s2[i]=max(0,s2[i-1]-x);
        }
        else if(opt=="none"){
            m[n-cnt]={"none",x,y};
            cnt++;
            s1[i]=max(x,s1[i-1]);
            s2[i]=min(y,s2[i-1]);
        }
        else{
            m[n-cnt]={"on",x,y};
            cnt++;
            s1[i]=s1[i-1]+x,s2[i]=s2[i-1]+y;
        }
    }
    int ans1=s1[n],ans2=s2[n];
    s1[1]=s1[n],s2[1]=s2[n];
    for (int i = 1;i<=n;i++){
        x=m[i].up,y=m[i].dn,opt=m[i].mtd;
        if (opt=="on"){
            s1[i]=max(0,s1[i-1]-y);
            s2[i]=max(0,s2[i-1]-x);
        }
        else if(opt=="none"){
            s1[i]=max(x,s1[i-1]);
            s2[i]=min(y,s2[i-1]);
        }
        else{
            s1[i]=s1[i-1]+x,s2[i]=s2[i-1]+y;
        }
    }
    cout<<s1[n]<<" "<<s2[n]<<endl;
    cout<<ans1<<" "<<ans2<<endl;
    return 0;
}

```


---

## 作者：guaidaokenan (赞：1)

#### 题目大意
有 $n$ 个阶段，每种阶段有三种情况，第一种是只有上匝道，第二种只有下匝道，第三种只有主干道。

说明：上匝道是有其他地方进入高速公路的地方；下匝道是从高速公路出去的地方。

#### 主要思路
因为题目是给定了许多范围，并且最后的答案也是一个范围，所以在计算时只需要用两个变量进行记录即可。

#### 注意事项
有可能 $l\le0$ 或 $r\le0$，这时就要对这两个变量和 $0$ 取最大值。
#### 附上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{
	string s;
	int x,y;
};
node a[105];
int l=-1,r=2e9;//实时更新答案
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		cin >>a[i].s;
		scanf("%d%d",&a[i].x,&a[i].y);
	}
	for(int i=n; i>=1; i--){
		if(a[i].s=="none"){//分类处理开始范围
			l=max(l,a[i].x);
			r=min(r,a[i].y);
		}
		else if(a[i].s=="on"){
			l-=a[i].y;
			r-=a[i].x;
		}
		else{
			l+=a[i].x;
			r+=a[i].y;
		}
		l=max(l,0);
		r=max(r,0);
	}
	printf("%d %d\n",l,r);
	l=-1;
	r=2e9;//还原l和r
	for(int i=1; i<=n; i++){
		if(a[i].s=="none"){//分类处理l,r
			l=max(l,a[i].x);
			r=min(r,a[i].y);
		}
		else if(a[i].s=="on"){
			l+=a[i].x;
			r+=a[i].y;
		}
		else{
			l-=a[i].y;
			r-=a[i].x;
		}
		l=max(l,0);
		r=max(r,0);
	}
	printf("%d %d\n",l,r);
	return 0;
}
```

---

## 作者：_Dynamic_Programming (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P1695)
# 思路
1. 先定义两个变量 $mi$ 和 $ma$，分别表示范围的下限和上限。
2. 将每一次读入记录下来，每次输入下限为 $x_i$，上限为 $y_i$。
3. 先反着扫一遍，算出为第 $1$ 英里之前的车流量的最准确的可能范围，对于第 $i$ 进行一下讨论：
- 如果这次是 `on` ，则表示这一英里有上匝道，要减去，因为这个范围要尽可能**大**，才能包含更多的情况，所以 $mi$ 要尽可能小，就减去 $y_i$；$ma$ 要尽可能大，就减去 $x_i$。
- 如果这次是 `off` ，则表示这一英里有下匝道，要加上，因为这个范围要尽可能**大**，才能包含更多的情况，所以 $mi$ 要尽可能小，就加上 $x_i$；$ma$ 要尽可能大，就加上 $y_i$。
- 如果这次是 `none` ，则表示这一英里既没有上匝道也没有下匝道，因为这个范围要尽可能**小**，才能满足更多的限制，所以 $mi$ 要尽可能大，$mi = \max(mi, x_i)$；$ma$ 要尽可能大，$ma = \min(mi, y_i)$。
4. 再正着扫一遍，算出为第 $N$ 英里之后的车流量的最准确的可能范围，对于第 $i$ 进行一下讨论：
- 如果这次是 `on` ，则表示这一英里有上匝道，要加上，因为这个范围要尽可能**大**，才能包含更多的情况，所以 $mi$ 要尽可能小，就加上 $x_i$；$ma$ 要尽可能大，就加上 $y_i$。
- 如果这次是 `off` ，则表示这一英里有下匝道，要减去，因为这个范围要尽可能**大**，才能包含更多的情况，所以 $mi$ 要尽可能小，就减去 $y_i$；$ma$ 要尽可能大，就减去 $x_i$。
- 如果这次是 `none` ，则表示这一英里既没有上匝道也没有下匝道，因为这个范围要尽可能**小**，才能满足更多的限制，所以 $mi$ 要尽可能大，$mi = \max(mi, x_i)$；$ma$ 要尽可能大，$ma = \min(mi, y_i)$。

还要注意，$mi$ 和 $ma$ 不能为负，所以每一次操作完后要，将 $mi$ 与 $ma$ 与 $0$ 比较，如果小于 $0$，就将其变为 $0$。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int ma, mi, n, x[105], y[105], op[105];
string s;
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> s;
		scanf("%d %d", &x[i], &y[i]);
		if(s == "on") op[i] = 1;
		if(s == "none") op[i] = 2;
		else if(s == "off") op[i] = 3;
	}
	mi = 0, ma = 1e9;
	for(int i = n; i >= 1; i--)
	{
		if(op[i] == 1) mi -= y[i], ma -= x[i];
		else if(op[i] == 2) ma = min(ma, y[i]), mi = max(mi, x[i]);
		else if(op[i] == 3) mi += x[i], ma += y[i];
		mi = max(mi, 0), ma = max(ma, 0);
	}
	cout << mi << " " << ma << endl;
	mi = 0, ma = 1e9;
	for(int i = 1; i <= n; i++)
	{
		if(op[i] == 1) mi += x[i], ma += y[i];
		else if(op[i] == 2) ma = min(ma, y[i]), mi = max(mi, x[i]);
		else if(op[i] == 3) mi -= y[i], ma -= x[i];
		mi = max(mi, 0), ma = max(ma, 0);
	}
	cout << mi << " " << ma << endl;
    return 0;
} 
```

---

## 作者：___QAQ__ (赞：0)

# 题意
有一个长为 $N$ 的路段，对每个路段进行三种描述之一：流量范围、流量增加范围、流量减少范围。求最初及最后可能的流量范围。
# 思路
分类讨论三种情况下所产生的影响，设当前范围为 $[x, y]$。

如果该路段的流量范围是 $[a, b]$，则 $[x, y]$ 变为 $[\max(a, x), \min(b, y)]$。

如果该路段的增加流量范围是 $[a, b]$，则 $[x, y]$ 变为 $[x + a, y + b]$。

如果该路段的减少流量范围是 $[a, b]$，则 $[x, y]$ 变为 $[x - b, y - a]$。

我们假定初始范围为 $[0, \infty]$，从前往后处理，即可得到最终流量范围。从后往前处理，即可得到初始流量范围，注意此时增加和相减是相反的。在处理过程中请注意越界问题。
# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e2 + 1;

int n, l, r, L[MAXN], R[MAXN];
string s[MAXN];

int main(){
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  l = 0, r = 1000;
  for(int i = 1; i <= n; i++){
    cin >> s[i] >> L[i] >> R[i];
  }
  for(int i = n; i >= 1; i--){
    if(s[i] == "off"){
      l = min(1000, l + L[i]);
      r = min(1000, r + R[i]);
    }else if(s[i] == "on"){
      l = max(0, l - R[i]);
      r = max(0, r - L[i]);
    }else{
      l = max(l, L[i]);
      r = min(r, R[i]);
    }
  }
  cout << l << ' ' << r << '\n';
  l = 0, r = 1000;
  for(int i = 1; i <= n; i++){
    if(s[i] == "on"){
      l = min(1000, l + L[i]);
      r = min(1000, r + R[i]);
    }else if(s[i] == "off"){
      l = max(0, l - R[i]);
      r = max(0, r - L[i]);
    }else{
      l = max(l, L[i]);
      r = min(r, R[i]);
    }
  }
  cout << l << ' ' << r;
  return 0;
}
```
# 复杂度
## 时间
按顺序处理路段 $O(N)$。
## 空间
记录路段信息 $O(N)$。

---

## 作者：Sun_pirf (赞：0)

# P1695 Mesuring Traffic 题解
模拟赛的模拟题，所以来写一发题解。
## 题意
有一条长为 $N$ 的线段，每1单位长度的段上有一定数量的车，共有三种操作（给出数量的**上下界**）：
1. 增加（on）
2. 减少（off）
3. 统计（none）

求**起始**与**终点**段的最精确汽车数量范围。
## 思路
由于是求起点与终点段的数量，所以可以分别**倒序**和**正序**计算。

我们先设 $\operatorname{maxx}$ 和 $\operatorname{minn}$ 为上下界，但是由样例解释可知：车辆的数量实际上在一次次的限制中，不断**向内缩减**，所以 $\operatorname{maxx}$ 应为极大值（0x3f3f3f3f），$\operatorname{minn}$ 应为极小值（-1），记得在每次计算前初始化一遍。

我们先来看**起点段**，即**倒序处理**。  
由于是倒序，需要**从后到前**地遍历。并且，增加与减少的操作相反。  
在增加操作中，记得判别 $\operatorname{minn}$ 一定大于等于 0。  
在统计操作时，比较当前段的上下界与 $\operatorname{maxx}$ $\operatorname{minn}$，精确范围。

**终点段**同理，仅需要注意相近的细节即可。

部分细节在代码中。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct node{//存储 
	string op;
	int low;
	int top;
}p[105];
int maxx=0x3f3f3f3f,minn=-1;
int main(){
	ios::sync_with_stdio(0);//加速 
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i].op>>p[i].low>>p[i].top;//输入 
	}
	
	//1 mile finished
	
	for(int i=n;i>=1;i--){//倒序计算 应反向 
		if(p[i].op=="on"){
			minn-=p[i].top;
			maxx-=p[i].low;
			minn=max(minn,0);//minn 大于等于0 
		}
		else if(p[i].op=="off"){//直接加 
			maxx+=p[i].top;
			minn+=p[i].low;
		}
		else{//缩范围 
			maxx=min(maxx,p[i].top);
			minn=max(minn,p[i].low);
		}
	}
	cout<<minn<<" "<<maxx<<"\n";//输出 
	
	//n miles finished
	
	maxx=0x3f3f3f3f,minn=-1;//再次初始化 
	for(int i=1;i<=n;i++){//正序计算 应正向 
		if(p[i].op=="off"){
			minn-=p[i].top;
			maxx-=p[i].low;
			minn=max(minn,0);//同上 
		}
		else if(p[i].op=="on"){
			maxx+=p[i].top;
			minn+=p[i].low;
		}
		else{
			maxx=min(maxx,p[i].top);
			minn=max(minn,p[i].low);
		}
	}
	cout<<minn<<" "<<maxx<<"\n";//输出 
	return 0;
}
```

Thanks For Watching.

---

