# [NERC 2021] Connect the Points

## 题目描述

给定平面上的三个点。你需要选择若干条与坐标轴平行的线段，使得这三个点相互连通。所选线段的总长度应尽可能短。

当两个点 $a$ 和 $b$ 之间存在一系列点 $p_0 = a, p_1, \ldots, p_k = b$，且每对相邻点 $p_i$ 和 $p_{i+1}$ 位于同一条线段上时，我们认为这两个点是**连通的**。


## 说明/提示

样例中的点和线段如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/3ln8aeda.png)

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
1 1
3 5
8 6```

### 输出

```
3
1 1 1 5
1 5 8 5
8 5 8 6```

# 题解

## 作者：fish_love_cat (赞：1)

怎么被奶龙题硬控了 1h /qd

---

按 $x$ 排序，然后让前两个点先连上，注意要先移 $x$ 再移 $y$。

第三个点直接向移 $y$ 时形成的竖线作垂就行了，分三种情况，向上延长，向下延长和不用延长。

大力写就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct cat{
    int a,b,c,d;
}ans[15];
int siz;
struct fish{
    int x,y;
}a[3];
bool cmp(fish x,fish y){
    if(x.x==y.x)return x.y<y.y;
    return x.x<y.x;
}
int main(){
    cin>>a[0].x>>a[0].y;
    cin>>a[1].x>>a[1].y;
    cin>>a[2].x>>a[2].y;
    sort(a,a+3,cmp);
    if(a[0].x!=a[1].x)
    ans[++siz]={a[0].x,a[0].y,a[1].x,a[0].y};
    if(a[0].y!=a[1].y)
    ans[++siz]={a[1].x,a[0].y,a[1].x,a[1].y};
    if(a[0].y>=a[2].y&&a[1].y<=a[2].y||a[0].y<=a[2].y&&a[1].y>=a[2].y){
        ans[++siz]={a[1].x,a[2].y,a[2].x,a[2].y};
    }else{
        int xx=siz;
        if(abs(ans[xx].a-a[2].x)+abs(ans[xx].b-a[2].y)>=
            abs(a[1].x-a[2].x)+abs(a[1].y-a[2].y)){
            if(a[1].x!=a[2].x)
            ans[++siz]={a[1].x,a[1].y,a[2].x,a[1].y};
            if(a[1].y!=a[2].y)
            ans[++siz]={a[2].x,a[1].y,a[2].x,a[2].y};
        }else{
            if(ans[xx].a!=a[2].x)
            ans[++siz]={ans[xx].a,ans[xx].b,a[2].x,ans[xx].b};
            if(ans[xx].b!=a[2].y)
            ans[++siz]={a[2].x,ans[xx].b,a[2].x,a[2].y};
        }
    }
    cout<<siz<<'\n';
    for(int i=1;i<=siz;i++)
        cout<<ans[i].a<<' '<<ans[i].b<<' '<<ans[i].c<<' '<<ans[i].d<<'\n';
    return 0;
}
```

---

## 作者：lvweisi (赞：0)

### 题目大意：
给定 $3$ 个点，用 $n$ 条线段将这 $3$ 个点连起来，且线段长度的总和要最小，输出这 $n$ 条线段。
### 思路：
因为只有 $3$ 个点，选择模拟比较方便，把这 $3$ 个点按 $x$ 的大小排序，此时会出现 $6$ 种情况，只需要根据每 $1$ 个情况分类讨论就好了。

### 代码如下：
``` cpp
#include<bits/stdc++.h>
using namespace std;
struct sbb{
	int x,y;//个人变量名命名爱好（勿喷）
}sb[10];
bool cmp(const sbb &t1,const sbb &t2){
	if(t1.x==t2.x)return t1.y<t2.y;
	return t1.x<t2.x;
}
int main(){
	for(int i=1;i<=3;i++){
		cin>>sb[i].x>>sb[i].y;
	}
	sort(sb+1,sb+1+3,cmp);
	cout<<3<<'\n';
	if(sb[1].y>sb[2].y&&sb[2].y>sb[3].y){	
		cout<<sb[1].x<<" "<<sb[1].y<<" "<<sb[2].x<<" "<<sb[1].y<<'\n';
		cout<<sb[2].x<<" "<<sb[1].y<<" "<<sb[2].x<<" "<<sb[3].y<<'\n';
		cout<<sb[2].x<<" "<<sb[3].y<<" "<<sb[3].x<<" "<<sb[3].y<<'\n';
		return 0; 
	}
	if(sb[1].y>sb[3].y&&sb[3].y>sb[2].y){
		cout<<sb[1].x<<" "<<sb[1].y<<" "<<sb[2].x<<" "<<sb[1].y<<'\n';
		cout<<sb[2].x<<" "<<sb[1].y<<" "<<sb[2].x<<" "<<sb[2].y<<'\n';
		cout<<sb[2].x<<" "<<sb[3].y<<" "<<sb[3].x<<" "<<sb[3].y<<'\n';
		return 0; 
	}
	if(sb[2].y>sb[1].y&&sb[1].y>sb[3].y){
		cout<<sb[1].x<<" "<<sb[1].y<<" "<<sb[3].x<<" "<<sb[1].y<<'\n';
		cout<<sb[2].x<<" "<<sb[1].y<<" "<<sb[2].x<<" "<<sb[2].y<<'\n';
		cout<<sb[3].x<<" "<<sb[1].y<<" "<<sb[3].x<<" "<<sb[3].y<<'\n';
		return 0; 
	}
	if(sb[2].y>sb[3].y&&sb[3].y>sb[1].y){
		cout<<sb[1].x<<" "<<sb[1].y<<" "<<sb[2].x<<" "<<sb[1].y<<'\n';
		cout<<sb[2].x<<" "<<sb[1].y<<" "<<sb[2].x<<" "<<sb[2].y<<'\n';
		cout<<sb[2].x<<" "<<sb[3].y<<" "<<sb[3].x<<" "<<sb[3].y<<'\n';
		return 0;
	}
	if(sb[3].y>sb[1].y&&sb[1].y>sb[2].y){
		cout<<sb[1].x<<" "<<sb[1].y<<" "<<sb[2].x<<" "<<sb[1].y<<'\n';
		cout<<sb[2].x<<" "<<sb[2].y<<" "<<sb[2].x<<" "<<sb[3].y<<'\n';
		cout<<sb[2].x<<" "<<sb[3].y<<" "<<sb[3].x<<" "<<sb[3].y<<'\n';
		return 0;
	}
	cout<<sb[1].x<<" "<<sb[1].y<<" "<<sb[2].x<<" "<<sb[1].y<<'\n';
	cout<<sb[2].x<<" "<<sb[1].y<<" "<<sb[2].x<<" "<<sb[3].y<<'\n';
	cout<<sb[2].x<<" "<<sb[3].y<<" "<<sb[3].x<<" "<<sb[3].y<<'\n';
	return 0;
}
```

---

