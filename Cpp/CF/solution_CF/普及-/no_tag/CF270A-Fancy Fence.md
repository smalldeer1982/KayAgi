# Fancy Fence

## 说明/提示

Emuskald想在他的农场周围造一圈栅栏，但是他太懒了，不想自己动手。于是，他买了一个栅栏机器人。

Emuskald想把栅栏围成正多边形。机器人每次造一个边，之后只能转动a°继续建造下一个边。

Emuskald能造出他想要的围栏吗？也就是说，有没有一种正多边形的每一个角都为a°。
第一组样例中，转动角度为30°，围不出正多边形。
第二组转动角度为60°，围出三角形。
第三组转动角度为90°，围出正方形。

感谢@PaulHunter 提供的翻译

## 样例 #1

### 输入

```
3
30
60
90
```

### 输出

```
NO
YES
YES
```

# 题解

## 作者：伟大的王夫子 (赞：4)

有关多边形内角和的问题，一般转化为外角进行讨论

因为外角和固定为$360\degree$

若内角为$a$,则外角为$180\degree - a$

只需判断$180-a$是否整除$360$即可

注意一些细节

$code$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main() {
	cin >> n;
	for (register int i = 1; i <= n; ++i) {
		double a;
		cin >> a;
		if (360.0 / (180.0 - a) == int(360 / (180 - a))) puts("YES");
		else puts("NO");
	}
}
```

---

## 作者：午尘 (赞：2)

先放代码~

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,i,j,k,x,t,a;
int main(){
	scanf("%d",&t);
	while (t--){
		scanf("%d",&a);
		if (360%(180-a)==0) cout<<"YES"<<endl;
		              else  cout<<"NO"<<endl;
	}
	return 0;
}

```


------------
然后就是证明啦（忽略了单位，都是 °）：


 内角证法：
   
   >设多边形边数为n。 
   
   >180(n-2)/n=a
   
   >180-360/n=a
   
   >360/n=180-a 


   
 ————————————————
   

 外角证法：
   
   >外角和=360
   
   >每一个外角:180-a 


外角证法更简单和巧妙些，但如果想不到内角的话也是很容易的~


------------


相关公式：

> n边形内角和=180°(n-2）
    
>n边形外角和=360°




---

## 作者：yanxingyu0910 (赞：1)

**题目链接**

[CF270A](https://www.luogu.com.cn/problem/CF270A)

**前置知识**

[① 如何证明正多边形](https://zhidao.baidu.com/question/553336820.html)

[② 外角的度数](https://baike.baidu.com/item/%E5%A4%9A%E8%BE%B9%E5%BD%A2%E7%9A%84%E5%A4%96%E8%A7%92%E5%92%8C/6636384)

**题意描述**

题解区的大佬们证明已经很详细了，

我来总结一下：

外角和恒为 $360$ （前置知识 **②** ）。

内角的度数为 $a$，外角的度数就是 $180 - a$。

那根据前置知识 **①** 显而易见只需判断 $360 \bmod \left( 180 - a \right)$ 是否为 $0$ 即可。

#### 代码

```c
#include<bits/stdc++.h>
using namespace std;
#define LL long long
int t,a,b;
inline LL read(){//快读 
    register LL x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-') f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*f;
}
signed main(){
	t=read();
	while(t--){
		a=read();
		b=360%(180-a);//依据结论模拟 
		if(b==0) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
} 
```

感谢观看~

---

## 作者：sandwave114514 (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF270A)

题目大意

机器人每次造一个边,之后只能转动 $a\degree$ 继续建造下一个边.也就是说,有没有一种正多边形的每一个角都为 $a\degree$ .如果围得出正多边形,输出"YES".否则,输出"NO".

解题思路

因为外角和固定为 $360\degree$ ,只要判断是否被 $360\degree$ 整除即可.

代码如下

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}//快读 
long long t;
double a;
int main() {
	t=read();//执行t次
	while(t--){
		cin>>a;
		if(360.0/(180.0-a)-(long long)(360/(180-a))==0)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;//完结撒花
}
```



---

## 作者：jimmyfj (赞：0)

根据多边形的外角和为 $360$ 度以及正多边形的每一个内角相等，我们只需要判断 $360$ 度是否能整除这个多边形一个内角的外角的度数就可以了。因为只有 $360$度 能整除这个多边形一个内角的外角的度数，这个多边形才会是正多边形。

参考代码 ：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int n;
int o[10005];

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
    {
        scanf("%d", &o[i]);
        if(360 % (180 - o[i]) == 0) printf("YES\n");//如果能整除, 输出YES
        else printf("NO\n");//不能输出NO
    }
    return 0;
}
```


---

## 作者：Anonymous__user (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF270A)。

**题目大意**： Emuskald 想把栅栏围成正多边形。机器人每次造一个边，之后只能转动 $a$°，继续建造下一个边。请判断有没有一种正多边形的每一个角都为 $a$°。

**思路**：我们知道正多边形的外角和是 $360$°，那么就判断输入的这个角的外角是否能被  $360$° 整除。如果能输出 YES 。不能输出 NO 。

**代码**：
```c
#include<bits/stdc++.h>
using namespace std;
long long t,n;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>n;
		if(360.000/(180-n)-360/(180-n)==0)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}

```


---

## 作者：小豆子范德萨 (赞：0)

正多边形的边数和内角和有一个大家都清楚的关系，就是
内角和=180*（n-2）。那么我们初始化边数为1，内角和为a，每次模拟加一条边，看看能否计算内角和符合上式公式。又是一道思维题，想得到就是水题，想不到就是卡题
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
//正多边形内角和=180*(n-2),刚开始 
int main()
{
    int t,a;cin>>t;
    loop:while(t--) {
    	cin>>a;
    	int tot = a;	//当前内角和
    	int n = 1;		//当前的边数 
		while(tot >= 180*(n-2)) {		//正多边形内角和多边形的关系 
			n++;
			tot += a;
			if(tot == 180*(n-2)) {
				cout<<"YES\n";
				goto loop;
			}
		}
		cout<<"NO\n";
	}
    return 0;
}
```



---

## 作者：ZolaWatle (赞：0)

### **CF270A 题解**

思路：用巧妙的数学思维打出表来做。

------------

###### 阶段一：推知360的因数

1. 原因：正n边形的中心角= $\dfrac{360}{n}$，题上说好不超int范围，所以推知360的因数，求出正多边形中心角的一切可能性。

2. 推出来的结果是（草稿纸上推的，在此不演示了）：

$$ 1,2,3,4,5,6,8,9,10,12,15,18,20,24,30,36,40,45,60,72,90,120 $$

------------

###### 阶段二：计算旋转角度的所有可能性

1. 原因：设旋转角为$ α $，中心角为$ β $；由垂径定理得，$ α = 2 \cdot \dfrac{180 - β}{2} = 180 - β$

2. 操作过程：由阶段一已推得的360的因数计算即可

3. 此过程的代码：

```cpp
#include <iostream>
#include <cstdio>
#define re register int
using namespace std;

int a[23]={0,1,2,3,4,5,6,8,9,10,12,15,18,20,24,30,36,40,45,60,72,90,120};
int res[23];

int main()
{
	for(re i=1;i<=22;i++)
	{
		res[i]=180-a[i];
		std::printf("%d,",res[i]);
	}
	return 0;
}
```

- 结果是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/yuks1769.png)

------------

###### 阶段三：打表AC

- 判断n值在所有可能中是否存在即可

- Code：

```cpp
#include <iostream>
#include <cstdio>
#define re register int
using namespace std;

int t,n;
int can[23]={0,179,178,177,176,175,174,172,171,170,168,165,162,160,156,150,144,140,135,120,108,
90,60};

int main()
{
	std::scanf("%d",&t);
	
	for(re x=1;x<=t;x++)
	{
		bool p=0;
		std::scanf("%d",&n);
		for(re i=1;i<=22;i++)
			if(n==can[i])
			{
				std::printf("YES\n");
				p=1;
				break;
			}
		if(p==0)
			std::printf("NO\n");
	}
	
	return 0;
}
```

------------

于是本题就顺利地做出来了

---

## 作者：HNYLMS_MuQiuFeng (赞：0)

这道题用外角判断就好了，我们知道，任意多边形外角和都360°，因此
我们只需要判断输入的这个角的补角（也就是外角）是否能被360°整除即可（因为要求围成的是正多边形）

因此，我们可以轻松的写出简单的代码：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n;int a;
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a;
		if(360.0/(180-a)-360/(180-a)==0)//判断（因为double型
        //不能用%）
		cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}//你看是不是很简单
	return 0;//AC啦！锵锵！
}
```
**杜绝抄袭，从我做起！！！**

---

