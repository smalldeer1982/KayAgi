# Searching Rectangles

## 题目描述

给出了一个 $n \times n$ 的平面，从下到上每一行、从左到右的每一列分别标号 $1$ 到 $n$。

平面内有两个矩形，这两个矩形平行于坐标轴。

## 样例 #1

### 输入

```
5
2
1
0
1
1
1
0
1
```

### 输出

```
? 1 1 5 5
? 1 1 3 3
? 1 1 3 1
? 2 2 2 2
? 3 3 5 5
? 3 3 3 5
? 3 3 3 4
? 3 4 3 5
! 2 2 2 2 3 4 3 5
```

# 题解

## 作者：xzggzh1 (赞：1)

题意：

$n*n$ 的平面上有两个矩形,让你找出矩形的位置，每次你可以输出
 $(x_1,y_1,x_2,y_2)$ , 然后cf会返回0,1或2,表示这个坐标范围内有几个矩形。最对可以问 $200$ 次，输出这两个矩形的位置。

---

可以先二分答案出两个矩形的分界线，然后对于每一个矩形二分他的位置。

显然每个完整的二分只要log(n)次，总共的 $200$ 次绰绰有余。

代码：


```cpp
#define mid (l+r>>1)
inline void solve(int x,int y,int fx,int fy) {
	int l=x,r=fx,Ans=x;
	while(l<=r) {
		int f=out(mid,y,fx,fy);
		if(f)l=mid+1,Ans=mid; else r=mid-1;
	}
	ans[++cnt]=Ans;
	l=y,r=fy,Ans=y;
	while(l<=r) {
		int f=out(x,mid,fx,fy);
		if(f==0)r=mid-1; else l=mid+1,Ans=mid;
	}
	ans[++cnt]=Ans;
	l=x,r=fx,Ans=fx;
	while(l<=r) {
		int f=out(x,y,mid,fy);
		if(f==0)l=mid+1; else r=mid-1,Ans=mid;
	}
	ans[++cnt]=Ans;
	l=y,r=fy,Ans=fy;
	while(l<=r) {
		int f=out(x,y,fx,mid);
		if(f==0)l=mid+1; else r=mid-1,Ans=mid;
	}
	ans[++cnt]=Ans;
}
int main() {
	cin>>n;
	int l=1,r=n,flag=0;
	while(l<=r) {
		int mid=(l+r)>>1;
		int f=out(1,1,n,mid),g=out(1,mid+1,n,n);
		if(f&&g)flag=1;
		if(f==0)l=mid+1; else r=mid-1;
	}
	if(flag) {
		solve(1,1,n,l);
		solve(1,l+1,n,n);
	} else {
		l=1,r=n;
		while(l<=r) {
			int mid=(l+r)>>1;
			int f=out(1,1,mid,n);
			if(f==0)l=mid+1; else r=mid-1;
		}
		solve(1,1,l,n);
		solve(l+1,1,n,n);
	}
	printf("! ");
	for (int i=1;i<=8;i++)printf("%d ",ans[i]);
	printf("\n");
}
```

---

