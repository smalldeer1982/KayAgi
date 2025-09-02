# Hongcow Solves A Puzzle

## 题目描述

Hongcow likes solving puzzles.

One day, Hongcow finds two identical puzzle pieces, with the instructions "make a rectangle" next to them. The pieces can be described by an $ n $ by $ m $ grid of characters, where the character 'X' denotes a part of the puzzle and '.' denotes an empty part of the grid. It is guaranteed that the puzzle pieces are one 4-connected piece. See the input format and samples for the exact details on how a jigsaw piece will be specified.

The puzzle pieces are very heavy, so Hongcow cannot rotate or flip the puzzle pieces. However, he is allowed to move them in any directions. The puzzle pieces also cannot overlap.

You are given as input the description of one of the pieces. Determine if it is possible to make a rectangle from two identical copies of the given input. The rectangle should be solid, i.e. there should be no empty holes inside it or on its border. Keep in mind that Hongcow is not allowed to flip or rotate pieces and they cannot overlap, i.e. no two 'X' from different pieces can share the same position.

## 说明/提示

For the first sample, one example of a rectangle we can form is as follows

`<br></br>111222<br></br>111222<br></br>`For the second sample, it is impossible to put two of those pieces without rotating or flipping to form a rectangle.

In the third sample, we can shift the first tile by one to the right, and then compose the following rectangle:

`<br></br>.....<br></br>..XX.<br></br>.....<br></br>.....<br></br>.....<br></br>`

## 样例 #1

### 输入

```
2 3
XXX
XXX
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2 2
.X
XX
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
5 5
.....
..X..
.....
.....
.....
```

### 输出

```
YES
```

# 题解

## 作者：Yizhixiaoyun (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF745B)

## 题目分析

不难发现，这道题实际上就是让我们找出一个包含所有 ```X``` 在内的最小矩阵，问矩阵当中是否有其他字符。

所以我们只需要扫一遍统计出所有 ```X``` 的横纵坐标最小值与最大值，求出来的横坐标最大值减最小值即为矩阵的长，纵坐标最大值减最小值即为矩阵的宽。然后扫一遍矩阵找是否存在其他字符即可。

## 贴上代码

似乎又把简单题实现麻烦了...

```cpp
#include<bits/stdc++.h>
#define ok puts("YES")
#define no puts("NO")
using namespace std;
int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-48;
		c=getchar();
	}
	return x*f;
}
const int inf=1e9;
const int maxn=502;
int n,m;
bool flag;
string s[maxn];
struct node{
	int x,y;
}fir,lst;
inline void init(){
	n=read();m=read();fir.x=inf;fir.y=inf;
	for(register int i=1;i<=n;++i){
		cin>>s[i];s[i]=" "+s[i];
		for(register int j=1;j<=m;++j){
			if(s[i][j]=='X'){
				fir.x=min(fir.x,i);fir.y=min(fir.y,j);
				lst.x=max(lst.x,i);lst.y=max(lst.y,j);
			}
		}
	}
}
int main(){
	init();
	for(register int i=fir.x;i<=lst.x;++i){
		for(register int j=fir.y;j<=lst.y;++j){
			if(s[i][j]!='X') no,exit(0);
		}
	}
	ok;
}
```

---

## 作者：_xbn (赞：3)

简单的模拟，我们一行一行搜，如果搜到一个 X 就更新这个 X 向上下左右能扩展

的距离，最后判断得到的矩形面积是否等于 X 的数量即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505;
int n,m,l,r,t,b,ans;
string str;
int main()
{

	cin>>n>>m;
	l=t=MAXN;
	r=b=-1;
	for(int i=0;i<n;i++)
	{
		cin>>str;
		for(int j=0;j<m;j++)
		{
			if(str[j]=='X')
			{
				ans++;
				l=min(l,j);
				r=max(r,j);
				t=min(t,i);
				b=max(b,i);
			}
		}
	}
	if((b-t+1)*(r-l+1)==ans)cout<<"YES";
	else cout<<"NO";
	return 0;
}
```



---

## 作者：zhouzihe (赞：0)

## 1 观察题目
观察题目，发现我们可以将最大矩形的长和宽记录下来，判断它的面积和 $X$ 字符的数量是否相等即可。我们考虑用 $a$ 记录矩形最左边的横坐标，$b$ 记录矩形最右边的横坐标，$c$ 记录矩形最上面的纵坐标，$d$ 记录矩形最下面的纵坐标。矩形的面积即为 $(b-a+1) \times (d-c+1)$。
## 2 code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[505][505],sum,a=1e9,b=-1e9,c=1e9,d=-1e9;
char ch;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ch;
			if(ch=='X'){
				f[i][j]=1;
				sum++;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(f[i][j]){
				a=min(a,j);
				b=max(b,j);
				c=min(c,i);
				d=max(d,i);
			}
		}
	}
	if((b-a+1)*(d-c+1)==sum){
		cout<<"YES";
	}
	else{
		cout<<"NO";
	}
	return 0;
}
```


---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF745B)
### **[题意解析]**
题目的意思很明确，让我们求出包含了全部的 $ X $ 字符的矩阵面积，和二维字符数组中 $ X $ 的个数，然后比较求出的值是否相等。
+ 相等输出 $\verb!YES!$ 。

+ 不相等输出 $\verb!NO!$ 。

### **[思路分析]**
一道简单的~~屑~~模拟，我们可以在读入时候统计 $  X $ 的个数，然后找到所有 $ X $ 里横坐标的最大与最小值，纵坐标里的最大与最小值，也就是找出构成矩阵的四个端点的坐标。

![矩阵长](https://cdn.luogu.com.cn/upload/image_hosting/cm0g3w07.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
 ![矩阵宽](https://cdn.luogu.com.cn/upload/image_hosting/6pqx3yg6.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

那矩阵的长就是 $ maxy-miny+1 $，宽就是 $ maxx-minx+1 $，最后就能求出矩阵面积了。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,a=2147483647,b=2147483647,c=-1,d=-1;
/*初始化*/
char s[110][110];
int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++)
    	for(int j=1; j<=m; j++)
    		cin>>s[i][j];
    for(int i=1; i<=n; i++)
    	for(int j=1; j<=m; j++){
    		if(s[i][j]=='X'){
				a=min(a,i);
				b=min(b,j);
				c=max(c,i);
				d=max(d,j);
				/*矩阵的四个端点坐标*/ 
				cnt++;
				/*X的个数*/ 
    		}
    	}
    for(int i=a; i<=c; i++)
    	for(int j=b; j<=d; j++){
    		if(s[i][j]!='X'){
    			cout<<"NO";
    			/*如果里面有.就不成立*/
    			return 0;
    		}
    	}
    if(cnt==(c-a+1)*(d-b+1))cout<<"YES";
    /*面积与个数是否相等*/ 
    return 0;
}
```

---

## 作者：lrmlrm_ (赞：0)

## 题意

给你一个 $n\times m$ 字符矩阵，问包含了所有字符 `X` 的最小矩阵是否含有其他字符？如果有，输出 `YES` ，否则输出 `NO` 。

## 思路

~~这不就是道模拟吗？~~

首先，我们需要找到所有字符 `X` 中 $x$ 坐标最小的和最大的，$y$ 坐标最小的和最大的（也就是左上角的 $x$ 坐标和 $y$ 坐标还有右下角的 $x$ 坐标和 $y$ 坐标），然后再在矩阵中去遍历寻找有没有不是 `X` 的字符即可。

但是，这种方法需要进行两次 $n\times n$ 的循环，虽然完全不会超时，但还有没有更好的想法呢？

仔细想一想就会发现，其实完全没有必要去在含有所有 `X` 的矩阵中进行遍历。我们只需要统计一下有多少个 `X` ，然后再计算一下含有所有 `X` 的矩阵的面积，如果他们两个一样，那么很明显证明这种时候含有所有 `X` 的矩阵中就没有其它的字符。否之就有两者之差个其他字符（虽然题目没让求）。

## 代码

法1（跑的较慢的）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,zsi=2147483647,zsj=2147483647,yxi=-2147483647,yxj=-2147483647;
char ch[1510][1510];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>ch[i][j];
			if(ch[i][j]=='X')zsi=min(i,zsi),zsj=min(j,zsj),yxi=max(i,yxi),yxj=max(j,yxj);
		}
//	printf("%d %d %d %d\n",zsi,zsj,yxi,yxj);
	for(int i=zsi;i<=yxi;i++)
		for(int j=zsj;j<=yxj;j++)
			if(ch[i][j]!='X'){
				printf("NO");
				return 0;
			}
	printf("YES");
	return 0;
}
```

法2（跑的较快的）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int sum,n,m,zsi=2147483647,zsj=2147483647,yxi=-2147483647,yxj=-2147483647;
char ch;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			cin>>ch;
			if(ch=='X')sum++,zsi=min(i,zsi),zsj=min(j,zsj),yxi=max(i,yxi),yxj=max(j,yxj);
		}
//	printf("%d %d %d %d\n",zsi,zsj,yxi,yxj);
	if(sum==(yxi-zsi+1)*(yxj-zsj+1))printf("YES");
	else printf("NO");
	return 0;
}
```

---

## 作者：PeaceSunset (赞：0)

这题是一个比较简单的**模拟**题。

#### 思路：
题目要求我们判断矩形面积是否等于 `X` 的个数。怎么样才能使矩形面积等于 `X` 的个数呢？

思考~~两年半~~就能知道，只有当矩形里面的字母都是 `X` 时，才能使两者相等。

那接下来就很简单了。我们只用把矩形的范围列出来，在判断其中是不是都是 `X`，就可以输出答案了。

列出矩形范围的方法也很简单：最大的 `X` 行数减去 最小的 `X` 行数可以得到矩形的宽。最大的 `X` 列数减去 最小的 `X` 列数可以得到矩形的长。

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,max_x,max_y,min_x=1e7,min_y=1e7;
char a[505][505];
void solve(){
	for(int i=min_y;i<=max_y;i++){
		for(int j=min_x;j<=max_x;j++){
//			cout<<a[i][j];
			if(a[i][j]!='X'){
				cout<<"NO";
				return;
			}
		}
//		cout<<endl;
	}
	cout<<"YES";
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>(a[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(a[i][j]=='X'){
				max_x=max(max_x,j);min_x=min(min_x,j);
				max_y=max(max_y,i);min_y=min(min_y,i);
			}
		}
	}
	solve();
	return 0;
} 
```


---

## 作者：A_Bit_Cold (赞：0)

简单模拟题。

读题发现，题目求包含所有 $X$ 的矩形中最小的一个，问这个矩形中是否全是 $X$。

思考，发现此矩形的左上角坐标为 $(\min(x_1,x_2,x_3,......,x_n),\min(y_1,y_2,y_3,......,y_n))$，右下角的坐标为 $(\max(x_1,x_2,x_3,......,x_n),\max(y_1,y_2,y_3,......,y_n))$，即最左上角的 $X$ 的坐标与最右下角 $X$ 的坐标，将得出矩形扫一遍即可求出结果。

---

## 作者：S__X (赞：0)

## 题意：
给你一个二维字符数组，问其中包含了全部的 `X` 字符的矩阵的面积是否与 `X` 字符的数量相等。

## 分析：
根据样例我们可以发现:

- 包含了全部的 `X` 字符的矩阵的长即为 $\max(j)-\min(j)+1$。

- 矩阵的宽即为 $\max(i)-\min(i)+1$。

因此我们只要在输入是找出 `X` 字符的横纵坐标的最大最小值就可以了。

## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans,max_x,max_y,min_x=1e9,min_y=1e9,sum;
char a;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
            cin>>a;
    		if(a=='X') {
				ans++;//统计字符个数
				max_x=max(max_x,j);//找出横纵坐标最大最小值
				min_x=min(min_x,j);
				max_y=max(max_y,i);
				min_y=min(min_y,i);
			}
		}
	}
	sum=(max_x-min_x+1)*(max_y-min_y+1);
	if(sum==ans) printf("YES");
	else printf("NO");
	return 0;
}
```

---

