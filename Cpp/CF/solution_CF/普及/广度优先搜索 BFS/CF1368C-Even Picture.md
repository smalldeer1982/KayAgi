# Even Picture

## 题目描述

### 题面描述

在网格图上给不超过 $5\times 10^5$ 的格子涂色，使得所有被涂色的格子**连通**且**与偶数个被涂色的格子相邻**，且恰好有 $n$ 个被涂色的格子的**四周的格子都被涂色**。

## 样例 #1

### 输入

```
4```

### 输出

```
12
1 0
2 0
0 1
1 1
2 1
3 1
0 2
1 2
2 2
3 2
1 3
2 3```

# 题解

## 作者：Alex_Wei (赞：13)

> [题面传送门](https://www.luogu.com.cn/problem/CF1368C)。

> 题意简述：在网格图上给不超过 $5\times 10^5$ 个格子涂色，使得所有被涂色的格子**连通**且**与偶数个被涂色的格子相邻**，且恰好有 $n$ 个被涂色的格子的**四周的格子都被涂色**。

一道有趣的构造题。

---

我们先考虑 $n=1$ 的情况。

首先应该能想到涂成一个 “十” 字，但是上下左右四个格子都只与 $1$ 个被涂色的格子相邻，不符合题意。

不过没关系，在左下角和右上角都涂上色就满足要求了。

$n=1$ 时的涂色方案（中心有点代表该方格被涂色）：

![](https://cdn.luogu.com.cn/upload/image_hosting/o37j2hkg.png)

接下来考虑 $n=2$ 的情况。

如果我们将右上角的这个方格的四周涂上色，那么其上方和右方就只与 $1$ 个被涂色的格子相邻，不符合题意。此时我们将其右上方的点涂上色即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/rmncs0kt.png)

这时候就能发现规律：考虑 $n=x$ 的情况，只需要在 $n=x-1$ 的情况下给右上角的三个格子涂色。

![](https://cdn.luogu.com.cn/upload/image_hosting/b0eitbip.png)

这样一来，不难发现我们一共需要 $3n+4$ 个点。

```cpp
int n;

int main(){
	scanf("%d",&n),printf("%d\n0 0\n",3*n+4); 
	for(int i=1;i<=n+1;i++)printf("%d %d\n%d %d\n%d %d\n",i-1,i,i,i-1,i,i);
	return 0;
}
```

---

## 作者：cupWolf (赞：3)

本蒟蒻的第一篇题解，求过。

## 成为最优构造的必要条件：
AC [CF1368C Even Picture（加强加强加强加强版）](https://www.luogu.com.cn/problem/U487982)

## 大概是最优构造：
由于楼上同样是 $n+O(\sqrt{n})$ 的大佬没有贴代码，所以比较不了。

![](https://cdn.luogu.com.cn/upload/image_hosting/v5njo17b.png)

用不同颜色将其分成了九块。

左上角/右下角块只有一个点染色，中间块除对角线外染色，其余块按三角形染色。

### 推算

设每块大小为 $s \times s$，由小学奥数可得
$$S_{总}=4s^2+2s+2$$
$$S_{冗余}=8s$$
$$S_{有效}=4s^2-6s+2$$
由于 $S_{有效} \le n$，根据求根公式，令
$$s=\left\lfloor \frac{6+\sqrt{16n+4}}{8} \right\rfloor$$
假如 $n-S_{有效}$ 的剩余部分用形如
```
##
###
 ###
  ###
   ##
```
的尾巴接在原图形上面，则有
$$k=S_{总}+3(n-S_{有效})$$
稍加计算可得
$$n+4\sqrt{n} \le k \le n+12\sqrt{n}$$
对于 $n \le 500$ 有 $k \le 748.$

![](https://cdn.luogu.com.cn/upload/image_hosting/tpo016fg.png)

### 优化

如果小尾巴改成递归构造，则上界更新为 $\min\left(x+6\sqrt{x}+43,x+12\sqrt{x}\right)$ （纯靠手动调参拟合，一点都不紧）

对于 $n \le 1000$ 有 $k \le 1192.$

![](https://cdn.luogu.com.cn/upload/image_hosting/ok5szoim.png)

### 欣赏一下构造的图形

（在代码中调用 `canvas.debug()` 即可欣赏）

$n=500, k=640$
```
n=500, k=640
                      ##
                     ####
                    ######
                   ########
                  ##########
                 ############
                ##############
               ################
              ##################
             ####################
           #######################
           # #####################
          ### ###################
         ##### #################
        ####### ###############
       ######### #############
      ########### ###########
     ############# #########
    ############### ####### ##
   ################# ##### ####
  ################### ### ######
 ##################### # ########
 #################################
  #################### # #########
   ################## ### #######
    ################ ##### #####
     ############## ####### ###
      ############ ######### # ##
       ##########  ###############
        ########    ######## # ###
         ######      ###### ### #
          ####        ####  #####
           ##          ##    ##
```

## Code:

从普通版一直改到四次加强的屎山。

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;

void small_main(){
    printf("%d\n", 3*n+4);
    printf(
    	"1 1\n"
		"1 2\n"
		"2 1\n"
		"2 2\n"
    );
    for (int i=1; i<=n; i++){
        printf(
            "%d %d\n%d %d\n%d %d\n",
            i+1, i+2,
            i+2, i+1,
            i+2, i+2
        );
    }
}

struct coord {
    int x, y;
};

const int maxdebug=80;
char buf[90][90];  // debug only

inline int __flip(bool flip, int size, int x){
	return flip ? (size+1-x) : x;
}

struct Canvas {
	int xoff, yoff;  // 每次画完之后把原点移动到特定位置，方便前后衔接
    vector<coord> ans;
    int cur_row = 1;

	void draw(int x, int y){
		ans.push_back({x+xoff, y+yoff});
	}

    void debug(){
        memset(buf, ' ', sizeof buf);
        for (int i=0; i<=maxdebug; i++){
            buf[i][maxdebug+2] = '\n';
            buf[i][maxdebug+3] = '\0';
        }
        for (coord &c: ans) {
            buf[c.x][c.y] = '#';
        }
        for (int i=0; i<=maxdebug; i++){
            cout << buf[i];
        }
    }

    void output(){
        printf("%d\n", ans.size());
        for (coord &c: ans) {
            printf("%d %d\n", c.x, c.y);
        }
    }
    
    void draw_triangle(int size, int row, int col, bool xflip, bool yflip){
    	// xflip=yflip=0时 
		// ###
    	// ## 
    	// #
    	// xflip 上下翻转，yflip 左右翻转
    	int x0 = row * size, y0 = col * size;
		for (int i=1; i<=size; i++){
			for (int j=1; i+j<=size+1; j++){
				draw(x0 + __flip(xflip, size, i),
					 y0 + __flip(yflip, size, j)); 
			}
		}
	}
	
	void draw_dhyy(int size, int row, int col){
		// 缺对角线的正方形
		//  ##
		// # #
		// ##
		int x0 = row * size, y0 = col * size;
		for (int i=1; i<=size; i++){
			for (int j=1; j<=size; j++){
				if (i != j){
					draw(x0+i, y0+j);
				}
			}
		}
	}
} canvas;



int main(){
    cin >> n;

    if (n<=30){
        small_main();
        return 0;
    }

	bool flag = false;
	// flag = not 是不是最左上角的
	// 处理衔接用

	while (n >= 7) {
		if (flag){
			n--;
		}
		int size = sqrt(16*n+4);
	    size = (size + 6) / 8;
//	    printf("size=%d\n", size);
		
		if (!flag){
	    	canvas.draw(size, size);
		}
		
		// 预留空间，1, 1 -> size, size
		if (flag){
			canvas.xoff -= size - 1;
			canvas.yoff -= size - 1;
		} else {
			flag = true;
		}	    
		
	    canvas.draw_triangle(size, 0, 1, 1, 1);
	    canvas.draw_triangle(size, 0, 2, 1, 0);
	    canvas.draw_triangle(size, 1, 0, 1, 1);
	    canvas.draw_dhyy(size, 1, 1);
	    canvas.draw_triangle(size, 1, 2, 0, 0);
	    canvas.draw_triangle(size, 2, 0, 0, 1);
	    canvas.draw_triangle(size, 2, 1, 0, 0);
	    canvas.draw(2*size+1, 2*size+1);
	    
	    n -= 4*size*size - 6*size + 2;
	    
	    // move 2*size+1, 2*size+1 -> 1, 1
	    canvas.xoff += 2*size;
		canvas.yoff += 2*size;
	}
	    
    
    for (int i=1; i<=n; i++){
    	canvas.draw(i+1, i);
    	canvas.draw(i, i+1);
    	canvas.draw(i+1, i+1);
	}
    
//    canvas.debug();
    canvas.output();

    return 0;
}

```

---

## 作者：Cure_Wing (赞：1)

[CF1368C Even Picture](https://www.luogu.com.cn/problem/CF1368C)

这个限制太宽松了，想一想如果 $k\le888$ 可以怎么做。

### 解析

![](https://cdn.luogu.com.cn/upload/image_hosting/qrfrympl.png)

首先看到 $n=4$。这种摆法观察样例就可以得出。这是接下来操作的基本图形。

扩展这种思路，每次向右下角 $45^\circ$ 平移这个基本图形，变成这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/9upmbi2g.png)

可以看到，我们的 $n$ 由 $4$ 变成了 $7$。由此类推，所有的可以表示成 $3x+4,x\in\N$ 的 $n$ 都可以通过像这样不断平移得到答案。此时可以算出 $k=\dfrac{5(n-4)}{3}+12$。

这样似乎不能表示 $n=3x+5,x\in\N$ 和 $n=3x+6,x\in\N$ 的情况，此时给出如下的解决方案。

![](https://cdn.luogu.com.cn/upload/image_hosting/id4xxh2k.png)

在右下角围出一个环，可以发现相较于上一张图多了 $2$ 个要求的点。此时得到的解决方案就是在 $n=3x+4,x\in\N$ 的基础上加一个环，可以得到 $n=3x+6,x\in\N$ 的方案。此时可以算出 $k=\dfrac{5(n-6)}{3}+22$。

同理，我们在 $n=3x+6,x\in\N$ 的基础上，在左上角也围一个相同的环，就可以得到 $n=3x+8,x\in\N$ 的方案。此时可以算出 $k=\dfrac{5(n-5)}{3}+27$。

![](https://cdn.luogu.com.cn/upload/image_hosting/uz7gv2p9.png)

此时可以发现只有 $n=1,2,3,5$ 的情况没有被考虑到，直接特判即可。方案可以自己构造或者参考代码。

时间复杂度 $O(n)$，空间复杂度 $O(1)$。可以发现当 $n\le500$ 时 $k\le852$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using std::cin;using std::cout;
int n;
signed main(){
	freopen("picture.in","r",stdin);
	freopen("picture.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n;
	if(n==1){
		cout<<"15\n";
		for(int i=1;i<=3;++i) cout<<1<<' '<<i<<'\n';
		for(int i=1;i<=3;i+=2) cout<<2<<' '<<i<<'\n';
		for(int i=1;i<=5;++i) cout<<3<<' '<<i<<'\n';
		for(int i=3;i<=5;i+=2) cout<<4<<' '<<i<<'\n';
		for(int i=3;i<=5;++i) cout<<5<<' '<<i<<'\n';
		return 0;
	}
	if(n==2){
		cout<<"20\n";
		for(int i=3;i<=4;++i) cout<<1<<' '<<i<<'\n';
		for(int i=1;i<=6;++i) cout<<2<<' '<<i<<'\n';
		for(int i=1;i<=6;++i) if(i!=2&&i!=5) cout<<3<<' '<<i<<'\n';
		for(int i=1;i<=6;i+=5) cout<<4<<' '<<i<<'\n';
		for(int i=1;i<=6;++i) cout<<5<<' '<<i<<'\n';
		return 0;
	}
	if(n==3){
		cout<<"17\n";
		for(int i=2;i<=5;++i) cout<<1<<' '<<i<<'\n';
		for(int i=2;i<=5;i+=3) cout<<2<<' '<<i<<'\n';
		for(int i=1;i<=5;++i) if(i!=4) cout<<3<<' '<<i<<'\n';
		for(int i=1;i<=5;++i) cout<<4<<' '<<i<<'\n';
		for(int i=2;i<=3;++i) cout<<5<<' '<<i<<'\n';
		return 0;
	}
	if(n==5){
		cout<<"27\n";
		for(int i=4;i<=7;++i) cout<<1<<' '<<i<<'\n';
		for(int i=4;i<=7;i+=3) cout<<2<<' '<<i<<'\n';
		for(int i=3;i<=7;++i) if(i!=6) cout<<3<<' '<<i<<'\n';
		for(int i=1;i<=7;++i) cout<<4<<' '<<i<<'\n';
		for(int i=1;i<=5;++i) if(i!=2) cout<<5<<' '<<i<<'\n';
		for(int i=1;i<=4;i+=3) cout<<6<<' '<<i<<'\n';
		for(int i=1;i<=4;++i) cout<<7<<' '<<i<<'\n';
		return 0;
	}
	int k=(n-4)/3;
	if((n-4)%3==0){
		cout<<k*5+12<<'\n';
		for(int i=2;i<=3;++i) cout<<1<<' '<<i<<'\n';
		for(int i=1;i<=4;++i) cout<<2<<' '<<i<<'\n';
		for(int i=3;i<=k+2;++i)
			for(int j=i-2;j<=i+2;++j)
				cout<<i<<' '<<j<<'\n';
		for(int i=k+1;i<=k+4;++i) cout<<k+3<<' '<<i<<'\n';
		for(int i=k+2;i<=k+3;++i) cout<<k+4<<' '<<i<<'\n';
		return 0;
	}
	if((n-4)%3==2){
		cout<<k*5+22<<'\n';
		for(int i=2;i<=3;++i) cout<<1<<' '<<i<<'\n';
		for(int i=1;i<=4;++i) cout<<2<<' '<<i<<'\n';
		for(int i=3;i<=k+2;++i)
			for(int j=i-2;j<=i+2;++j)
				cout<<i<<' '<<j<<'\n';
		for(int i=k+1;i<=k+6;++i) cout<<k+3<<' '<<i<<'\n';
		for(int i=k+2;i<=k+6;++i) if(i!=k+5) cout<<k+4<<' '<<i<<'\n';
		for(int i=k+3;i<=k+6;i+=3) cout<<k+5<<' '<<i<<'\n';
		for(int i=k+3;i<=k+6;++i) cout<<k+6<<' '<<i<<'\n';
		return 0;
	}
	cout<<k*5+27<<'\n';
	for(int i=1;i<=4;++i) cout<<1<<' '<<i<<'\n';
	for(int i=1;i<=4;i+=3) cout<<2<<' '<<i<<'\n';
	for(int i=1;i<=5;++i) if(i!=2) cout<<3<<' '<<i<<'\n';
	for(int i=1;i<=6;++i) cout<<4<<' '<<i<<'\n';
	for(int i=5;i<=k+3;++i)
		for(int j=i-2;j<=i+2;++j)
			cout<<i<<' '<<j<<'\n';
	for(int i=k+2;i<=k+7;++i) cout<<k+4<<' '<<i<<'\n';
	for(int i=k+3;i<=k+7;++i) if(i!=k+6) cout<<k+5<<' '<<i<<'\n';
	for(int i=k+4;i<=k+7;i+=3) cout<<k+6<<' '<<i<<'\n';
	for(int i=k+4;i<=k+7;++i) cout<<k+7<<' '<<i<<'\n';
	return 0;cout<<"菱川六花";
}//第一百二回 宁国府骨肉病灾祲 大观园符水驱妖孽
```

---

## 作者：OtoriEmu (赞：0)

正常的做法都是给 $3n+4$ 个点，在其他题解里面呈现得很清楚。下面给出一个点数要求更小的做法。

我们想构造一坨点使得大部分点都能造成贡献。先丢掉合法这个条件，我们可以画出类似于这样的图形（红格子表示能造成贡献，蓝格子表示不合法）：

![](https://cdn.luogu.com.cn/upload/image_hosting/v4135lqf.png)

为了使其合法，我们需要在蓝格子左右两边放上一个另一个蓝格子。也就是说像这样的图形，我们可以首尾相接拼成一个大图形，现在就只剩下最左和最右有两个蓝格子了。我们再引出一条路径就可以去掉蓝格子的贡献。

当然这个只能处理偶数，对于奇数的情况加上一个简单的小判断就好了。下面给出 $n=11$ 的构造实例。

![](https://cdn.luogu.com.cn/upload/image_hosting/92e2j8od.png)

理论上只需要 $n+O(\sqrt n)$ 个格子，但是这个常数有点大，在 $n$ 更大的时候才会体现出差距。

代码只处理了几种上面的图形（分别可以供给 $2,8,18,32$ 个红格子的四种图形），因为是暴力展开插入的比较丑所以只贴[评测链接](https://codeforces.com/problemset/submission/1368/179028794)。

---

## 作者：Error_Eric (赞：0)

### 前言

我一看这道题，$n \le 500 $ ，一开始还以为是搜索来着...

这道题目的原有题解太复杂了，跑的还不够快，不便于蒟蒻们理解，于是蒟蒻跑过来发了一篇题解。

### 正文

![https://cdn.luogu.com.cn/upload/image_hosting/hw482atp.png](https://cdn.luogu.com.cn/upload/image_hosting/hw482atp.png)

相信~~大家已经注意到了~~，在这种情况下，无论n等于几，都是符合题意的。也就是说，每一个浅色的方块周围都有两个方块，每一个深色的方块周围都有四个方块。

~~那么怎么输出呢？~~

原有题解的输出方法太复杂了。我用了新的输出方法。

我们不妨设从左往右的方向设为x轴正方向，从上往下的方向设为y轴正方向（数学老师表示很淦）那么我们可以把{(0,0),(0,1),(1,0)}分为一组,把{(1,1),(1,2),(2,1)}分为一组，{(2,2),(2,3),(3,2)}分为一组，...{(i,i),(i,i+1),(i+1,i)}分为一组。最后加上(n+1,n+1)。

伪代码如下

```
#头文件
int main(){
    输入 n;
    输出 n*3+4//自己算算。
    for(0...n){
        输出i,i,i+1,i+1,i ;
    }
    结束?
}

```

真的这么简单吗？

不好意思，真的这么简单。

$Ac\ Code:$

```cpp
#include<stdio.h>
int main(){
	int n;
	scanf("%d",&n),printf("%d\n",n*3+4);
	for(int i=0;i<=n;i++) printf("%d %d\n%d %d\n%d %d\n",i,i,i+1,i,i,i+1);
	return 0*printf("%d %d\n",n+1,n+1);
}//你可曾见过七行Ac黄题？
//不过你想压缩成两行也不是不行[doge]
```

---

## 作者：xiaolilsq (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1368C)

## 题目简述

给一个网格图黑白染色，使得**每个**黑色格子周围黑色格子数为偶数，且**恰好**有 $n$ 个黑色格子上下左右的邻居都为黑色。

## 题目分析

这类题目貌似没有一般套路，多做就熟悉了。

在草稿纸上推过几次后，发现以下几种方式都是可行的：

![](https://cdn.luogu.com.cn/upload/image_hosting/mz8ls4y3.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/qtw3f1ji.png)

当然还有其他方法，这里就不一一列举。

## 参考代码

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define ch() getchar()
#define pc(x) putchar(x)
template<typename T>inline void read(T&x){
	int f;char c;
	for(f=1,c=ch();c<'0'||c>'9';c=ch())if(c=='-')f=-f;
	for(x=0;c<='9'&&c>='0';c=ch())x=x*10+(c&15);x*=f;
}
template<typename T>inline void write(T x){
	static char q[64];int cnt=0;
	if(!x)pc('0');if(x<0)pc('-'),x=-x;
	while(x)q[cnt++]=x%10+'0',x/=10;
	while(cnt--)pc(q[cnt]);
}
void write(int a,int b){
	write(a),pc(' ');
	write(b),pc('\n');
}
int main(){
	int n;read(n);
	write(n*3+4),pc('\n');
	write(0,0),write(1,0);
	for(int i=1;i<=n;++i)
		write(i-1,i),write(i,i),write(i+1,i);
	write(n,n+1),write(n+1,n+1);
	return 0;
}
```

---

