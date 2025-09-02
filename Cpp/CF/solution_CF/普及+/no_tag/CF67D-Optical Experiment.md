# Optical Experiment

## 题目描述

如图所示，有 $n$ 条光线从矩形上边的 $n$ 个洞射入矩形区域后从下边的 $n$ 个洞射出。

已知从第 $i$ 个洞射入的光线编号为 $x_i$，从第 $i$ 个洞射出的光线编号为 $y_i$，要求从这 $n$ 条光线中选出最多数量的光线，使得这些光线中任意两条都会在矩形区域内相交。

## 样例 #1

### 输入

```
5
1 4 5 2 3
3 4 2 1 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
3 1 2
2 3 1
```

### 输出

```
2
```

# 题解

## 作者：liuyongle (赞：1)

#### 题意简述：

> 有 $n$ 条光线从矩形上边的 $n$ 个洞射入矩形区域后从下边的 $n$ 个洞射出。

> 已知从第 $i$ 个洞射入的光线编号为 $x_i$，从第 $i$ 个洞射出的光线编号为 $y_i$，要求从这 $n$ 条光线中选出最多数量的光线，使得这些光线中任意两条都会在矩形区域内相交。

#### 思路分析

根据题意，所选光线按照射入洞口编号经过sort排序后，其射出洞口编号必然是倒序的。因此对所有光线按射入洞口编号排序后对其射出洞口编号求最长上升（不下降）子序列（即为 LIS）即可。

#### 细节处理及注意事项

1. 最大值最好开到 `0x3f3f3f3f`，这是int类型最大值；
2. 不要类型定义 `typedef pair<int,int> pii;`，这样编译器会报错，如果一定要定义建议用 `define` 而不是 `typedef`。

代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int INF=0x3f3f3f3f,N=1e6+5;

pair<int,int> p[N];
int a[N],dp[N],n;

inline int read() { //快读，加快输入速度
    int res=0,fh=1;
    char ch=getchar();
    while((ch>'9'||ch<'0')&&ch!='-')
        ch=getchar();
    if(ch=='-')
        fh=-1,ch=getchar();
    while(ch>='0'&&ch<='9')
        res=res*10+ch-'0',ch=getchar();
    return fh*res;
}

int LIS() {
    for(int i=1;i<n;++i)
        dp[i]=INF;
    dp[0]=a[0];
    int len=1;
    for(int i=1;i<n;++i)
        if(a[i]>dp[len-1])
            dp[len++]=a[i];
        else
            dp[lower_bound(dp,dp+n,a[i])-dp]=a[i]; 
    return len;
}

int main()  {
    scanf("%d",&n);
    for(int i=0;i<n;++i)
        a[read()-1]=i;
    for(int i=0;i<n;++i)
        p[i].first=a[i];
    for(int i=0;i<n;++i)
        a[read()-1]=i;
    for(int i=0;i<n;++i)
        p[i].second=a[i];
    sort(p,p+n);
    for(int i=0;i<n;++i)
        a[i]=p[n-1-i].second;
    printf("%d\n",LIS());
    return 0;
}
```

---

## 作者：ys_kylin__ (赞：0)

## 思路
通过观察，我们发现，要使所有线互相交叉，设有 $x$ 条线是交叉的，按照其中一边升序排好序。然后，第 $1$ 条线的另一边（未排序的）必定接着最大的洞，以此类推，第 $x$ 条线接着编号最小的洞。那么也就是一边排好序后求另一边的最长上升子序列。因为洞口编号独一无二，所以也可以是最长不下降子序列。注意数据范围，$O(n^2)$ 是无法通过的，需要用 $O(n\log n)$ 来做。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {
	int x=0; bool y=false;
	char ch=getchar();
	while(ch<'0' || ch>'9') y=(ch=='-'),ch=getchar();
	while(ch>='0' && ch<='9') x=(x<<3)+(x<<1)+(ch^'0'), ch=getchar();
	return y?-x:x;
}
inline void write(int x) {
	if(x<0)putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
int n;
struct node {
	int x,y;
}jc[1000005];
int a[1000005],f[1000005];
int cmp(node x,node y) {
	return x.x>y.x;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) a[i]=read(),jc[a[i]].x=i;
	for(int i=1,x;i<=n;i++) x=read(),jc[x].y=i;
	sort(jc+1,jc+n+1,cmp);
	for(int i=1;i<=n;i++) {
		a[i]=jc[i].y;
	}//进行前期的处理
	for(int i=2;i<=n;i++) f[i]=0x3f3f3f3f;
    f[1]=a[1];
    int ans=1;
    for(int i=2;i<=n;i++){
        int j=lower_bound(f+1,f+1+ans,a[i])-f;//nlogn的最长不下降子序列
		if(j==ans+1) 
			f[++ans]=a[i];
		else f[j]=a[i];
    }
    printf("%d\n",ans);
	return 0;
}
```

---

