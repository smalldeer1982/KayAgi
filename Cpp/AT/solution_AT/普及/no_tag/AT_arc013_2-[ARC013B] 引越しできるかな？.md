# [ARC013B] 引越しできるかな？

## 题目描述

### 题意

给出 $C$ 个长方体的长、宽、高。

求一个最小体积的纸箱可以放入每一个长方体。

# 题解

## 作者：EternalHeart1314 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/AT_arc013_2)

# 思路

把每个行李的长宽高都从小到大排个序，最后纸板箱的长宽高分别是行李的长宽高的 $\max$。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int n, a[5], mx1, mx2, mx3;

signed main() {
	cin >> n;
	while(n --) {
		cin >> a[1] >> a[2] >> a[3];
		sort(a + 1, a + 4);
		mx1 = max(mx1, a[1]),
		mx2 = max(mx2, a[2]),
		mx3 = max(mx3, a[3]);
	}
	return cout << mx1 * mx2 * mx3 << '\n', 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：YangXiaopei (赞：1)

## 题目大意：

给出 $n$ 个长方体，求一个最小的长方体盒子，可以让每个长方体单独放在盒子里。

## Solution:

简单的贪心题。

我们将长方体的长宽高排序，让大的和大的比，小的和小的比。

最后将长宽高最大的三个求出来，相乘即可。

最后提示一下：**输出时最后要加换行，不然会寄的！**

## Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x, y, z, a[5];
int main(){
	cin >> n;
	while(n--){
		for(int i = 1; i <= 3; i++){
			cin >> a[i];
		}
		sort(a + 1, a + 4);
		x = max(x, a[1]);
		y = max(y, a[2]);
		z = max(z, a[3]);
	}
	cout << x * y * z << "\n";
	return 0;
}
```

---

## 作者：WaterSky (赞：1)

# [AT_arc013_2 引越しできるかな？](https://www.luogu.com.cn/problem/solution/AT_arc013_2)

## 题目做法：
根据题目，我们得知我们只需要保证一种姿势能够放进盒子里就可以，所以我们可以保证每一个长方体都以特定的方向去放就可以了。

所以我们可以把每一个长方体的长宽高排序，再去更新答案就可以了。

题目不难，所以直接放代码。

## 代码：
```
#include <bits/stdc++.h>
using namespace std;
long long n,a[15],A,B,H;
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld%lld",&a[1],&a[2],&a[3]);
		sort(a+1,a+4);
		A=max(A,a[1]);
		B=max(B,a[2]);
		H=max(H,a[3]);
	}
	cout<<A*B*H<<endl;//注意，千万要记得输出换行（别问我为什么）。
	return 0;
}
```

---

## 作者：zhouzihang1 (赞：0)

# AT_arc013_2 [ARC013B] 引越しできるかな？ 题解

[洛谷传送门](https://www.luogu.com.cn/problem/AT_arc013_2)

[AT 传送门](https://atcoder.jp/contests/arc013/tasks/arc013_2)

[博客，更好的阅读体验](https://www.luogu.com.cn/blog/827018/atarc0132-arc013b-yin-yue-ti-xie)

## 做法

由于每个长方体可以随意放置，所以每个长方体的三个参数可以进行排序。

定义三个变量表示最终纸箱的长、宽、高，每次排序更新纸箱大小。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,l,a[10];
int main()
{
	int T;cin>>T;
	while(T--)
	{
		scanf("%d%d%d",&a[1],&a[2],&a[3]);
		sort(a+1,a+4);
		n=max(n,a[1]);
		m=max(m,a[2]);
		l=max(l,a[3]);
	}
	printf("%d\n",n*m*l);
	return 0;
}
```

---

## 作者：nkrqzjc_zzz (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_arc013_2)

------------

### 思路

题目让你求能单独放下某个长方体最小的体积，显而易见求所有长宽高中的最大值。要注意一个点，题目给的 $N$、$M$ 和 $L$ 并不是有序的，因为题目说可以调整方向，所以要排一下序。

最后，一个小贴士——**换行**！（因为此问题，我错了两次）

### 代码

具体看代码哦！

```cpp
#include<ios>//不爱万能头 
using std::max;
using std::min;
int a,b,c,d,e,f,g,h,i,j;
main(){
	scanf("%d",&d);
	while(d--){
		scanf("%d%d%d",&a,&b,&c);
		h=min(a,min(b,c));//排序 
		j=max(a,max(b,c));//排序 
		i=a+b+c-h-j;      //排序 
		e=max(e,h);//判断最大值 
		f=max(f,i);//判断最大值 
		g=max(g,j);//判断最大值 
	}
	printf("%d\n",e*f*g);
}

```


---

## 作者：Elysia11 (赞：0)

这是 @HerikoDeltana的 [翻译](https://www.luogu.com.cn/paste/0nukh1i8)。

这道题要求能够单独放得下每个物体最小的长方体盒子的体积。

换而言之，也就是求能够单独放得下每个物体最小的长方体盒子的长宽高。

如果直接求长宽高的最大值就会出错。

因此，我们要考虑把物体翻转。

也就是要用最大值与最大值比较，最小值与最小值比较，中间值与中间值比较。

我们可以将每组的最大值放在最后，最小值放在最前：    
```
if(x1>x2) swap(x1,x2);
if(x1>x3) swap(x1,x3);
if(x2>x3) swap(x2,x3);
```
然后再分别求出最大的长宽：
```
max1=max(max1,x1);
max2=max(max2,x2);
max3=max(max3,x3);
```
最后再将长宽高相乘：
```
cout<<max1*max2*max3<<endl;
```
代码：
```
#include<bits/stdc++.h>//万能头文件 
#define ll long long
#define INF 1e9
using namespace std;
int c;//有c件长方体物体 
int x1,x2,x3;//长方体的长宽高 
int max1,max2,max3;//最小长方形盒子的体积 
int main(){
    scanf("%d",&c);//输入件数 
    for(int i=1;i<=c;i++){
        scanf("%d%d%d",&x1,&x2,&x3);//输入长宽高 
        if(x1>x2) swap(x1,x2);
        if(x1>x3) swap(x1,x3);
        if(x2>x3) swap(x2,x3);
        //让x1为长宽高中的最小值，x3为长宽高中的的最大值 
        //因为长方体可以翻转 
        max1=max(max1,x1);
        max2=max(max2,x2);
        max3=max(max3,x3);
        //求出能够单独放得下每个物体的最小的长方体盒子的长宽高 
    }
    cout<<max1*max2*max3<<endl;//求出体积，记得回车
    return 0;//功德圆满 
}
```
第一篇题解，若有错误，请指正。

---

## 作者：IOI_AK_TLR (赞：0)

# 思路

这一题很简单，只要保证**每个**长方体都以特定的方向放就行，所以直接对于每个长方体都按长宽高排个序再更新答案就行了。


------------


# 题解

```cpp
#include <bits/stdc++.h>
using namespace std;
unsigned long long n,a[3],x=0,y=0,z=0;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	while(n--)
	{
		cin>>a[0]>>a[1]>>a[2];
		sort(a,a+3);
		x=max(x,a[0]);
		y=max(y,a[1]);
		z=max(z,a[2]);
	}
	cout<<x*y*z<<'\n';//AT的题最后一定要输出个换行！ 
	return 0;
}

```


---

## 作者：zimujum (赞：0)

这是 @HerikoDeltana  [翻译](https://www.luogu.com.cn/paste/0nukh1i8)

## 思路
我们的目的是找出最小并能装下物体的纸盒的长宽高就行，然后将物体的长宽高进行大小排序，再找出纸箱的最小的长宽高，换句话说，就是将物体依次放入纸箱，如果怎么都放不下了，就扩大纸箱直到纸箱能装下为止（详见注释）。

## 最后是 AC 代码和详细思路
```
#include <bits/stdc++.h>//美丽的万能头 
#define ll long long
#define ull unsigned long long
#define AC return 0
using namespace std;
const ll M=114514;
int n;//长方体个数 
int a[3];//要求输入的长宽高，因为想直接 sort 所以开了个数组 
int za,zb,zh;z//纸盒的长宽高 
/*
因为数据范围是 1≤C,N,M,L≤100
所以能直接用int 
*/ 
int main(){
//	freopen("eat.in","r",stdin);
//	freopen("eat.out","w",stdout);
	cin >> n;//输入长方体个数
	for(int i=1;i<=n;i++){
		cin >> a[0] >> a[1] >> a[2];//输入长宽高 
		sort(a,a+3);//因为长方体可以任意放置，所以从小到大排序 
		za=max(a[0],za);
		zb=max(a[1],zb);
		zh=max(a[2],zh);
		/*
		用max函数求出纸盒的最小长宽高
		并且能把所有长方体装下 
		*/ 
	}
	cout << za*zb*zh << endl;//最后输出纸盒的体积，记得加回车 
//	fclose(stdin);
//	fclose(stdout);
	AC;//功德圆满 



```
这是本蒟蒻第一篇题解，有错误请指正。

---

