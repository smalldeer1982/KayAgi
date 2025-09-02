# Vika and Segments

## 题目描述

Vika has an infinite sheet of squared paper. Initially all squares are white. She introduced a two-dimensional coordinate system on this sheet and drew $ n $ black horizontal and vertical segments parallel to the coordinate axes. All segments have width equal to $ 1 $ square, that means every segment occupy some set of neighbouring squares situated in one row or one column.

Your task is to calculate the number of painted cells. If a cell was painted more than once, it should be calculated exactly once.

## 说明/提示

In the first sample Vika will paint squares $ (0,1) $ , $ (1,1) $ , $ (2,1) $ , $ (1,2) $ , $ (1,3) $ , $ (1,4) $ , $ (0,3) $ and $ (2,3) $ .

## 样例 #1

### 输入

```
3
0 1 2 1
1 4 1 2
0 3 2 3
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4
-2 -1 2 -1
2 1 -2 1
-1 -2 -1 2
1 2 1 -2
```

### 输出

```
16
```

# 题解

## 作者：MarSer020 (赞：1)

题意显然，但是注意矩形的长或宽至少有一个为 $1$。

$\Large\text{Solution}$

扫描线板子，可以先写 P5490。

首先为了好画矩形，可以先将给出的线段向上向右各平移 $\frac{1}{2}$ 格，使矩形顶点在整点上。

画出样例是这样的：

![](https://pic.imgdb.cn/item/65a081cc871b83018a991fb0.jpg)

中间的线段是题目所给出的。

计算一下矩形的顶点，发现：

- 对于平行于 $\text{x}$ 轴的直线，设左端点为 $(x_1,y)$，右端点为 $(x_2,y)$，则有矩形左上角为 $(x_1,y+1)$，右下角为 $(x_2+1,y)$。
- 对于平行于 $\text{y}$ 轴的直线，设上端点为 $(x,y_1)$，下端点为 $(x,y_2)$，则有矩形左上角为 $(x,y_1+1)$，右下角为 $(x+1,y_2)$。

转换完之后扫描线即可。

$\Large\text{Code}$

```cpp
#include<bits/stdc++.h>
#define int int64_t
#define ls cur<<1
#define rs cur<<1|1
#define mid ((l+r)>>1)
using namespace std;
int n,b[2000005],cnt[4000005],t[4000005],ans;
struct node{
	int l,r,y,val;
}a[2000005];
bool cmp(node x,node y){
	return x.y<y.y;
}
void pushup(int cur,int l,int r){
	if(cnt[cur])
		t[cur]=b[r+1]-b[l];
	else
		t[cur]=t[ls]+t[rs];
}
void update(int cur,int l,int r,int x,int y,int val){
	if(x<=l&&r<=y){
		cnt[cur]+=val,pushup(cur,l,r);
		return;
	}
	if(x<=mid)
		update(ls,l,mid,x,y,val);
	if(y>mid)
		update(rs,mid+1,r,x,y,val);
	pushup(cur,l,r);
}
int32_t main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n;
	for(int i=1,xa,ya,xb,yb;i<=n;i++){
		cin>>xa>>ya>>xb>>yb;
		if(xa>xb)
			swap(xa,xb);
		if(ya<yb)
			swap(ya,yb);//注意可能第一个给出的不是左端点/上端点
		ya++,xb++,b[(i<<1)-1]=xa,b[i<<1]=xb,a[(i<<1)-1]={xa,xb,ya,1},a[i<<1]={xa,xb,yb,-1};
	}
	n<<=1,sort(a+1,a+n+1,cmp),sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)
		a[i].l=lower_bound(b+1,b+n+1,a[i].l)-b,a[i].r=lower_bound(b+1,b+n+1,a[i].r)-b;
	for(int i=1;i<=n;i++)
		update(1,1,n,a[i].l,a[i].r-1,a[i].val),ans+=t[1]*(a[i+1].y-a[i].y);
	cout<<ans;
	return 0;
}
```

---

## 作者：Your_Name (赞：0)

## 思路
发现是扫描线原题，于是考虑它与原题的区别。

首先，他只有宽为一的矩形，其次，在重建坐标系后我们发现：对于每一个矩形 $(x_1,y_1,x_2,y_2)$ 坐标变换成描述点后的坐标为 $(x_1-1,y_1,x_2,y_2-1)$，当然 $(x_1,y_1+1,x_2+1,y_2)$ 也是可以的，只是新轴位置不一样，这里以第一种举例。

结合图片可以更好理解（绿轴为新轴，黑轴为老轴，红色为矩形）。
![](https://cdn.luogu.com.cn/upload/image_hosting/doh7qt5o.png)
之后就正常扫描线就行，注意保证 $x_1 \le x_2$ 以及 $y_1 \ge y_2$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;//算面积开long long
const int N = 1e5 + 5;
struct Line{
    int l, r, y, flag;
}line[4 * N];
LL x[4 * N];
int cmp(Line a, Line b){
    return a.y < b.y;
}
struct Node{
    int l, r, tag;
    LL sum;
}t[24 * N];
void pushup(int u){
    if(t[u].tag){
        t[u].sum = x[t[u].r + 1] - x[t[u].l];//要用离散化前的长度
    }else if(t[u].l == t[u].r){
        t[u].sum = 0;
    }else{
        t[u].sum = t[u * 2].sum + t[u * 2 + 1].sum;
    }
}
void build(int u, int l, int r){
    t[u]={l,r,0,0};
    if(l == r){
        return;
    }
    int mid = l + r >> 1;
    build(u * 2, l, mid),build(u * 2 + 1, mid + 1, r);
    pushup(u);
}
void update(int u, int l, int r, int v){
    if(t[u].l == l && t[u].r ==r){
        t[u].tag += v;
        pushup(u);
        return;
    }
    int mid = t[u].l + t[u].r >> 1;
    if(r <= mid){
        update(u * 2, l, r, v);
    }else if(l >= mid + 1){
        update(u * 2 + 1, l, r, v);
    }else{
        update(u * 2, l, mid, v);
        update(u * 2 + 1, mid + 1, r, v);
    }
    pushup(u);
}//线段树板子
int main(){
    int n,x1,x2,y1,y2;
    scanf("%d",&n);
    int cnt = 0;
    for(int i = 0; i < n; i ++){
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if(x1 > x2)swap(x1, x2);
        if(y1 < y2)swap(y1, y2);//维护大小关系，好后期modify
        x1 --, y2 --;//坐标映射，上面讲了
        cnt++;
        line[cnt] = {x1, x2, y1, 1};
        x[cnt] = x1;
        cnt++;
        line[cnt] = {x1, x2, y2, -1};
        x[cnt] = x2;//存扫描线
    }
    sort(line + 1, line + cnt + 1, cmp);//从小到大
    sort(x + 1, x + cnt + 1);
    int num=unique(x + 1, x + cnt + 1) - (x + 1);//离散化
    build(1, 1, cnt - 1);
    LL sum = 0;
    for(int i = 1; i <= cnt - 1; i++){
        int l = lower_bound(x + 1, x + num + 1, line[i].l) - x;
        int r = lower_bound(x + 1, x + num + 1, line[i].r) - x - 1;//扫描线右端点记得减一
        update(1, l, r, line[i].flag);
        sum += (t[1].sum * (line[i + 1].y - line[i].y));//累计答案
    }
    printf("%lld", sum);
    return 0;
}
```
 _完结撒花_

---

