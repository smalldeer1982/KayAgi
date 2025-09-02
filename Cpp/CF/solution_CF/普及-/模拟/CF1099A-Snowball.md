# Snowball

## 题目描述

Today's morning was exceptionally snowy. Meshanya decided to go outside and noticed a huge snowball rolling down the mountain! Luckily, there are two stones on that mountain.

Initially, snowball is at height $ h $ and it has weight $ w $ . Each second the following sequence of events happens: snowball's weights increases by $ i $ , where $ i $ — is the current height of snowball, then snowball hits the stone (if it's present at the current height), then snowball moves one meter down. If the snowball reaches height zero, it stops.

There are exactly two stones on the mountain. First stone has weight $ u_1 $ and is located at height $ d_1 $ , the second one — $ u_2 $ and $ d_2 $ respectively. When the snowball hits either of two stones, it loses weight equal to the weight of that stone. If after this snowball has negative weight, then its weight becomes zero, but the snowball continues moving as before.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1099A/f7b26ae9a77b6104710900b83e2e840423f8f72b.png)Find the weight of the snowball when it stops moving, that is, it reaches height 0.

## 说明/提示

In the first example, initially a snowball of weight 4 is located at a height of 3, there are two stones of weight 1, at a height of 1 and 2, respectively. The following events occur sequentially:

- The weight of the snowball increases by 3 (current height), becomes equal to 7.
- The snowball moves one meter down, the current height becomes equal to 2.
- The weight of the snowball increases by 2 (current height), becomes equal to 9.
- The snowball hits the stone, its weight decreases by 1 (the weight of the stone), becomes equal to 8.
- The snowball moves one meter down, the current height becomes equal to 1.
- The weight of the snowball increases by 1 (current height), becomes equal to 9.
- The snowball hits the stone, its weight decreases by 1 (the weight of the stone), becomes equal to 8.
- The snowball moves one meter down, the current height becomes equal to 0.

Thus, at the end the weight of the snowball is equal to 8.

## 样例 #1

### 输入

```
4 3
1 1
1 2
```

### 输出

```
8```

## 样例 #2

### 输入

```
4 3
9 2
0 1
```

### 输出

```
1```

# 题解

## 作者：封禁用户 (赞：1)

本题根据题目意思模拟就行了。
难度还可以吧……作为红题还是可以的。
```
#include<stdc++.h>
using namespace std;
int main()
{
    int a,b,c,d,e,f;
    cin>>a>>b>>c>>d>>e>>f;
    for(b;b>=1;b--)
    {
        a+=b;
        if(b==d) a-=c;
        if(b==f) a-=e;
        if(a<=0) a=0;//第一次提交我忘了判它
    }
    cout<<a<<endl;
}
```

---

## 作者：A_Cute_757 (赞：0)

Just模拟，重点不要忘了某个不符合物理学的题意...
```cpp
#include<bits/stdc++.h>
using namespace std;
int w,h;
int u1,h1,u2,h2;
int main()
{
    cin>>w>>h;
    cin>>u1>>h1>>u2>>h2;//读入数据
    for(int i=h;i>=0;i--)//从最高处开始计算
    {
        w+=i;//按照提议加上现在的高度
        if(i==h1)//现在的高度到达第一个点
        {
            w-=u1;
            if(w<=0)//之所以把判断放在这里，是因为成为负数的情况一定是在减小之后的
            {
                w=0;
            }
        }
        if(i==h2)//现在的高度到达第二个点
        {
            w-=u2;
            if(w<=0)
            {
                w=0;
            }
        }
        
    }
    cout<<w;
}
```

---

## 作者：Eason_AC (赞：0)

## Content
有一个重量为 $w$ 的雪球从高度为 $h$ 的位置开始滚落，每秒它的高度会减少 $1$，同时在高度为 $i$ 的位置它的重量会增加 $i$。在雪球滚动的路线上还有两块石头，雪球在高度为 $h_i$ 的位置碰到第 $i$ 块石头，重量会减少 $u_i$。求到达高度为 $0$ 的位置时雪球的最终重量。

**数据范围：$0\leqslant w,h,u_i\leqslant 100,0\leqslant h_i\leqslant h,h_1\neq h_2$。**
## Solution
数据范围这么小，为什么不直接模拟呢？从高度为 $h$ 开始，每秒增加 $h$，碰到一块石头就减少重量，但注意只能减到 $0$，不能到负数，然后再 $h\leftarrow h-1$。最后直接输出即可。
## Code
```cpp
int w, h, u[3], a[3], vis[107];

int main() {
	getint(w), getint(h);
	_for(i, 1, 2) {getint(u[i]), getint(a[i]); vis[a[i]] = u[i];}
	while(h) {
		w += h, w = max(0, w - vis[h]);
		h--;
	}
	writeint(w);
	return 0;
}
```

---

## 作者：览遍千秋 (赞：0)

本题解同步发布于[本场$\mathrm{CF}$总题解](https://www.luogu.org/blog/kaiming/CF530Div2)，欢迎来踩。

## A - Snowball

一道模拟题/数学题。

### 模拟

发现$n$的范围不大，可以直接枚举$n-1$，按照题意模拟即可。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;

int w,h; 
int a,b,c,d;
int ans;
template<typename Tp>
void read(Tp &x){
	x=0;char ch=1;int fh;
	while(ch!='-'&&(ch>'9'||ch<'0')) ch=getchar();
	if(ch=='-'){
		ch=getchar();fh=-1;
	}
	else fh=1;
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	x*=fh;
}

int main(){
	read(ans);read(h);read(a);read(b);read(c);read(d);
	for(register int i=h;i>=0;i--){
		ans+=i;
		if(i==b) ans-=a;
		if(i==d) ans-=c;
		if(ans<0) ans=0;
	}
	printf("%d\n",ans);
	return 0;
}
```

### 数学

直接输出

$$\frac{(1+n)\times n}{2}-u_1-u_2$$

但是这个的鲁棒性没有模拟好，题目并没有保证给出石头的范围一定在$[1,n]$

---

## 作者：GusyNight (赞：0)

***本题解由 缘，为何物？ 提供~~~***

**这是本蒟蒻的第11篇题解!**

**首先要弄清楚有几个量**
```cpp
int qw,wlxsq,qw1,c1,qw2,c2;
```
**然后读入(快读)**
```cpp
qw=read(),wlxsq=read();
qw1=read(),c1=read();
qw2=read(),c2=read();
```
```
接下来是最重要的模拟过程!
```
```cpp
bool flag=true;
for(int i=wlxsq;i>0;i--){
    qw+=i; 
    if(i==c1){
        qw-=qw1;
    }
    if(i==c2){
       	qw-=qw2;
    }
    if(qw<0){
       	flag=false;
    }
}
```
**解释**
```
如果i=c1那么就把质量减小，
i=c2是也是这样的道理，
但如果，qw<0了，
不可以输出负数，
这时输出"0".
```
AC code
=
```cpp
#include<bits/stdc++.h>
#define I int
#define L long long
#define C char
#define S string
#define B bool
#define Max 100000009
#define Mid 1000009
#define Sml 10009
#define Lit 109
using namespace std;
inline int read(){
    char c=getchar();
    int x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
int qw,wlxsq,qw1,c1,qw2,c2;
bool flag=true;
int main(){
    qw=read(),wlxsq=read();
    qw1=read(),c1=read();
    qw2=read(),c2=read();
    for(int i=wlxsq;i>0;i--){
        qw+=i; 
        if(i==c1){
        	qw-=qw1;
        }
        if(i==c2){
        	qw-=qw2;
        }
        if(qw<0){
        	flag=false;
        }
    }
    if(flag==true){
    	cout<<qw;
    }
    else if(flag=false){
    	puts("0");
    }
    return 0;
}
```
**看我即墨口爱，你不点个赞再走嘛？**

---

