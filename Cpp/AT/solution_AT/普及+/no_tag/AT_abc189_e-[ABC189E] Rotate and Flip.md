# [ABC189E] Rotate and Flip

## 题目描述

给出 $N$ 个点，以及每个点得坐标 $(x_i,y_i)$，给出 $M$ 次操作，操作如下：

- 第一种操作：将所有点绕原点 $(0,0)$ 顺时针旋转 $90$ 度。

- 第二种操作：将所有点绕原点 $(0,0)$ 逆时针旋转 $90$ 度。

- 第三种操作：以 $x=p$ 为对称轴，将所有的点对称过去。

- 第四种操作：以 $y=p$ 为对称轴，将所有的点对称过去。

接着给出 $Q$ 组询问，每次询问在某次操作过后某个点的坐标。

## 样例 #1

### 输入

```
1
1 2
4
1
3 3
2
4 2
5
0 1
1 1
2 1
3 1
4 1```

### 输出

```
1 2
2 -1
4 -1
1 4
1 0```

## 样例 #2

### 输入

```
2
1000000000 0
0 1000000000
4
3 -1000000000
4 -1000000000
3 1000000000
4 1000000000
2
4 1
4 2```

### 输出

```
5000000000 4000000000
4000000000 5000000000```

# 题解

## 作者：2011qiqi (赞：7)

### 题意：

在二维平面上有 $n$ 个点，给定 $m$ 个操作，有四个操作:

1. 原点顺时针旋转 90 度。
2. 原点逆时针旋转 90 度。
3. 直线 $x=p$ 的对称。
4. 直线 $y=p$ 的对称。

接着 $q$ 个询问，每个询问问一个指定的点 $B$ 在执行了 $A$ 次操作之后的坐标的值。特别的，如果询问的是第零次操作之后的位置，那么就是要求没有经过任何操作时的坐标。

---

### 思路：

可以不用矩阵(~~因为我不会~~)。

其实这题并不麻烦，耐心观察每个操作就可以发现：

操作一：$(x,~y)$ $\rightarrow$ $(y,~-x)$

操作二：$(x,~y)$ $\rightarrow$ $(-y,~x)$

操作三：$(x,~y)$ $\rightarrow$ $(2\times p~-~x,~y)$

操作四：$(x,~y)$ $\rightarrow$ $(x,~2\times p~-~y)$

可以发现对于任何几种操作相加，对于原来的横纵坐标，都能表示成：

$(cnt_x~opt_x~x,~cnt_y~opt_y~y)$ 

或 

$(cnt_y~opt_y ~y,~cnt_x~opt_x~x)$。

cnt 表示一个值，opt 表示正负号，$x/y$ 表示原来横坐标或纵坐标的值。

在具体操作时，只需要维护 $cnt_x/y$，$opt_x/y$，是否翻转横纵坐标，5 个变量即可搞定。

---

### Code(省去了缺省源)：

```c++
const int N=2e5+2;

ll x[N],y[N],opt[N],p1[N],a[N],b[N],id[N];
ll x_res[N],y_res[N];

inline bool cmp(const int &_,const int &__){
	return a[_]<a[__];
}

int main(){
	re int n=read(),i,j=1;
	for(i=1;i<=n;++i) x[i]=read(),y[i]=read();
	re int m=read();
	for(i=1;i<=m;++i){
		opt[i]=read();
		if(opt[i]>2) p1[i]=read();
	}
	re int q=read();
	for(i=1;i<=q;++i){
		a[i]=read(),b[i]=read();
		id[i]=i;
	}
	sort(id+1, id+1+q, cmp);
	re ll turn=0,x_opt=1,y_opt=1,x_cnt=0,y_cnt=0;
	for(i=1;i<=m+1;++i){
		while(a[id[j]]==i-1){
			x_res[id[j]]=x_cnt+1LL*x_opt*x[b[id[j]]];
			y_res[id[j]]=y_cnt+1LL*y_opt*y[b[id[j]]];
			if(turn) swap(x_res[id[j]], y_res[id[j]]);
			++j;
		}
		if(opt[i]==1){
			if(turn){
				y_opt=-y_opt;
				y_cnt=-y_cnt;
			}else{
				x_opt=-x_opt;
				x_cnt=-x_cnt;
			}
			turn^=1;
		}else if(opt[i]==2){
			if(turn){
				x_opt=-x_opt;
				x_cnt=-x_cnt;
			}else{
				y_opt=-y_opt;
				y_cnt=-y_cnt;
			}
			turn^=1;
		}else if(opt[i]==3){
			if(turn){
				y_cnt=2LL*p1[i]-y_cnt;
				y_opt=-y_opt;
			}else{
				x_cnt=2LL*p1[i]-x_cnt;
				x_opt=-x_opt;
			}
		}else{
			if(turn){
				x_cnt=2LL*p1[i]-x_cnt;
				x_opt=-x_opt;
			}else{
				y_cnt=2LL*p1[i]-y_cnt;
				y_opt=-y_opt;
			}
		}
	}
	for(i=1;i<=q;++i){
		print(x_res[i]);
		P;
		print(y_res[i]);
		endl;
	}
	return 0;
}
```

---

## 作者：wangjiajian (赞：1)

### 解题思路

对于点 $(x, y)$，把每一个操作视为一个定义域和值域都为点集的函数：
 - 操作 $1$: $f_1[(x, y)] = (y, -x)$
 - 操作 $2$: $f_2[(x, y)] = (-y, x)$
 - 操作 $3$: $f_3[(x, y)] = (-x+2p, y)$
 - 操作 $4$: $f_4[(x, y)] = (x, -y+2p)$

那么操作序列就可以视作一个复合函数（如执行操作 $3$、$2$ 则可以视作 $f_2\{f_3[(x, y)]\}$），并且该线性的复合函数可以化简为一个关于 $x$ 和 $y$ 的线性表达式（如 $f_2\{f_3[(x, y)]\} = (-y, -x+2p)$ ）。

因为所有操作都是针对所有点的，因此这个关于 $x$ 和 $y$ 的同一个符合函数表达式是适用于所有点的，那么对于每一个点，求它在某一操作后的值，只需要将它的初始值 $(x, y)$ 代入当前操作后算出的表达式即可。

举例解释：

*执行操作：$3$、$2$*

每一个点 $(x, y)$ 都会变为 $(-x+2p, y)$，再变为 $(-y, -x+2p)$

### 具体做法

计算符合函数的最终表达式，需要 $5$ 个变量维护
 - $change$ 表示 $x$ 和 $y$ 是否有交换
 - $digital\_x$ 表示第一个值的系数是否为负
 - $digital\_y$ 表示第一个值的系数是否为负
 - $pls\_x$ 表示第一个值加上的常数项
 - $pls\_y$ 表示第二个值加上的常数项

遍历操作，得到当前完成操作 $i$ 的表达式，将 $A_i = i$ 的询问的点值带入表达式求解。因此，首先要根据每一个询问 $i$ 的 $A_i$ 进行排序，离线询问最后再一并输出。

### AC代码

```cpp
#include <bits/stdc++.h>
#define N (int)(2e5+2)
#define ll long long
using namespace std;

int n, m, q, x[N], y[N], opt[N], p[N];
struct question {
    int id, A, B;
} ques[N];
bool tmp, change, digital_x, digital_y;
ll pls_tmp, pls_x, pls_y, ans_x[N], ans_y[N];

inline bool cmp(question i, question j) {
    return i.A < j.A;
}

inline void work(int i) {  // 递推符合函数表达式
    if(opt[i] == 1) {
        change = !change;
        tmp = digital_x;
        digital_x = digital_y;
        digital_y = !tmp;
        pls_tmp = pls_x;
        pls_x = pls_y;
        pls_y = -pls_tmp;
    } else if(opt[i] == 2) {
        change = !change;
        tmp = digital_x;
        digital_x = !digital_y;
        digital_y = tmp;
        pls_tmp = pls_x;
        pls_x = -pls_y;
        pls_y = pls_tmp;
    } else if(opt[i] == 3) {
        digital_x = !digital_x;
        pls_x = -pls_x + (p[i]<<1);
    } else {
        digital_y = !digital_y;
        pls_y = -pls_y + (p[i]<<1);
    }
}

inline ll query_x(int i) {  // 将 x 代入表达式
    ll ret = change ? y[i]:x[i];
    ret = digital_x ? -ret:ret;
    return ret + pls_x;
}

inline ll query_y(int i) {  // 将 y 代入表达式
    ll ret = change ? x[i]:y[i];
    ret = digital_y ? -ret:ret;
    return ret + pls_y;
}

int main() {
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        scanf("%d%d", x+i, y+i);
    scanf("%d", &m);
    for(int i=1; i<=m; i++) {
        scanf("%d", opt+i);
        if(opt[i]==3 || opt[i]==4)
            scanf("%d", p+i);
    }
    scanf("%d", &q);
    for(int i=1; i<=q; i++) {
    	ques[i].id = i;
        scanf("%d%d", &ques[i].A, &ques[i].B);
    }
    sort(ques+1, ques+1+q, cmp);
    for(int i=1, j=0; i<=q; i++) {
        while(j < ques[i].A)
            work(++j);
        ans_x[ques[i].id] = query_x(ques[i].B);
        ans_y[ques[i].id] = query_y(ques[i].B);
    }
    for(int i=1; i<=q; i++)
        printf("%lld %lld\n", ans_x[i], ans_y[i]);
    return 0;
}

```

---

## 作者：Tang_poetry_syndrome (赞：0)

## [ABC189E] Rotate and Flip
### 思路
大模拟，是初二的平面直角坐标系。
经过手推可得出以下结论，此处我们定义点坐标为 $(x,y)$：  
- 当 $opt\leq2$ 时，$x,y$ 变换，随象限变换而改变 $x,y$ 的正负性。  
- 当 $opt=3$ 时，因对称轴为 $y$ 轴 $(p=0)$ 时，$x=-x$，考虑将 $y$ 轴位置转为 $p$，则得出 $y=2\times p-y$。  
- 当 $opt=4$ 时，同 $opt=3$，$x=2\times p-x$。  

考虑记录一个点在每一次操作的位置（$x,y$ 与正负号），与根据象限变换造成的 $x,y$ 转变，以此模拟即可。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,j,k) for(register int i=j;i<=k;i++)
#define g(i,j,k) for(register int i=j;i>=k;i--)
#define pb push_back 
const int N=2e5+10;
ll n,m,q,x[N],y[N],opt[N][2],p,a[N],b[N],sign[N][2],c[N][2];
bool changed_xy[N];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;
	f(i,1,n)cin>>x[i]>>y[i];
	cin>>m;
	f(i,1,m)
	{
		cin>>opt[i][0];
		if(opt[i][0]>2)cin>>opt[i][1];
	}
	sign[1][0]=sign[1][1]=1;
	f(i,1,m)
	{
		ll p=opt[i][1];
		if(opt[i][0]==1){
			c[i+1][0]=c[i][1];
		    c[i+1][1]=-c[i][0];
		    sign[i+1][0]=sign[i][1];
		    sign[i+1][1]=-sign[i][0];
		    changed_xy[i+1]=!changed_xy[i];
	    }
		else if(opt[i][0]==2){
	        c[i+1][0]=-c[i][1];
	        c[i+1][1]=c[i][0];
	        sign[i+1][0]=-sign[i][1];
	        sign[i+1][1]=sign[i][0];
	        changed_xy[i+1]=!changed_xy[i];
	    }
		else if(opt[i][0]==3){
	        c[i+1][0]=2*p-c[i][0];
	        c[i+1][1]=c[i][1];
	        sign[i+1][0]=-sign[i][0];
	        sign[i+1][1]=sign[i][1];
	        changed_xy[i+1]=changed_xy[i];
	    }
		else{
	        c[i+1][0]=c[i][0];
	        c[i+1][1]=2*p-c[i][1];
	        sign[i+1][0]=sign[i][0];
	        sign[i+1][1]=-sign[i][1];
	        changed_xy[i+1]=changed_xy[i];
	    }
	}
	cin>>q;
	f(i,1,q)
	{
		cin>>a[i]>>b[i];
		ll pos_x=x[b[i]],pos_y=y[b[i]];
		if(changed_xy[a[i]+1])swap(pos_x,pos_y);
		cout<<c[a[i]+1][0]+sign[a[i]+1][0]*pos_x<<' '<<c[a[i]+1][1]+sign[a[i]+1][1]*pos_y<<'\n';
	}
	return 0;
} 
```
[提交记录](https://atcoder.jp/contests/abc189/submissions/46653738)

---

