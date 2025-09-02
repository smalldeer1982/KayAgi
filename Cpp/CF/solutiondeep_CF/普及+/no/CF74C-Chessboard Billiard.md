# 题目信息

# Chessboard Billiard

## 题目描述

Let's imagine: there is a chess piece billiard ball. Its movements resemble the ones of a bishop chess piece. The only difference is that when a billiard ball hits the board's border, it can reflect from it and continue moving.

More formally, first one of four diagonal directions is chosen and the billiard ball moves in that direction. When it reaches the square located on the board's edge, the billiard ball reflects from it; it changes the direction of its movement by 90 degrees and continues moving. Specifically, having reached a corner square, the billiard ball is reflected twice and starts to move the opposite way. While it moves, the billiard ball can make an infinite number of reflections. At any square of its trajectory the billiard ball can stop and on that the move is considered completed.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF74C/2b32b43a6cf594e055f4f908960d44aaa5bece14.png)It is considered that one billiard ball $ a $ beats another billiard ball $ b $ if $ a $ can reach a point where $ b $ is located.

You are suggested to find the maximal number of billiard balls, that pairwise do not beat each other and that can be positioned on a chessboard $ n×m $ in size.

## 样例 #1

### 输入

```
3 4
```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
```

### 输出

```
3```

# AI分析结果

### 题目重写
# 棋盘台球

## 题目描述
想象一下：有一个棋子台球。它的移动方式类似于国际象棋中的象。唯一的区别是，当台球撞到棋盘边界时，它可以从边界反弹并继续移动。

更正式地说，首先从四个对角线方向中选择一个，然后台球沿该方向移动。当它到达棋盘边缘的方格时，台球会从边缘反弹；它将移动方向改变 90 度并继续移动。具体来说，当到达角落方格时，台球会反弹两次并开始向相反方向移动。在移动过程中，台球可以进行无限次反弹。在其轨迹的任何方格上，台球都可以停止，此时移动被视为完成。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF74C/2b32b43a6cf594e055f4f908960d44aaa5bece14.png)如果一个台球 $a$ 能够到达另一个台球 $b$ 所在的位置，则认为台球 $a$ 击败了台球 $b$。

请你找出在 $n×m$ 大小的棋盘上，两两互不击败且可以放置的台球的最大数量。

## 样例 #1
### 输入
```
3 4
```
### 输出
```
2```

## 样例 #2
### 输入
```
3 3
```
### 输出
```
3```

### 算法分类
数学

### 综合分析与结论
这些题解主要围绕寻找在 $n×m$ 棋盘上放置互不干扰的台球的最大数量这一问题展开，解法涵盖模拟、数学推理、并查集等多种思路。不同题解的难点在于如何高效地处理台球的反弹规律以及避免重复路径的计算。有的题解通过模拟台球运动轨迹，有的利用数学性质（如辗转相除、最小公倍数等），还有的借助并查集维护边界点关系来解决问题。

### 所选的题解
- **作者：Abeeel51 (5星)**
    - **关键亮点**：思路简洁清晰，通过观察反弹规律，类比辗转相除过程，直接得出答案公式 $ans=\gcd(n - 1,m - 1)+1$，代码实现极为简洁高效。
    - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
inline int GCD(int a,int b){return b==0?a:GCD(b,a%b);}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    printf("%d\n",GCD(n-1,m-1)+1);
    return 0;
}
```
    - **核心实现思想**：定义求最大公约数的函数 `GCD`，在 `main` 函数中读入棋盘尺寸，直接利用公式计算并输出结果。
- **作者：Air_Color5 (4星)**
    - **关键亮点**：通过观察发现只需关注棋盘一条边的颜色数量（代表不同轨迹）即可得到答案，采用模拟棋子移动轨迹的方式确定边上点的颜色，思路较直观。
    - **个人心得**：作者提到最初使用二维数组存储数据导致 TLE，后优化为用一维数组存储一行数据，认识到数据范围对数据结构选择的影响。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000006],col,ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;a[i]==0&&i<m;i++){
		col++;
		a[i]=col;
		ans++;
		int y=n-2,x=i,dy=-1,dx=1;
		if(x==m-1)dx=-1;
		x+=dx;
		while(y!=n-1||x!=i){
			if(x==m-1||x==0)dx=-dx;
			if(y==n-1||y==0){
				dy=-dy;
				if(y==n-1)a[x]=col;
			}
			int nx,ny;
			if(dx==1)nx=m-1-x;
			else nx=x;
			if(dy==1)ny=n-1-y;
			else ny=y;
			x+=dx*min(nx,ny);
			y+=dy*min(nx,ny);
		}
	}
	printf("%d",ans);
	return 0;
}
```
    - **核心实现思想**：从棋盘最后一行开始，对每个未访问的点，标记颜色并模拟其运动轨迹，通过不断更新坐标和方向，直到回到原点，过程中标记经过的最后一行的点，最后统计颜色数量即答案。
- **作者：ZLCT (4星)**
    - **关键亮点**：通过严谨的数学推理，证明多个引理，如从任意点出发都能回到自身、球一定会碰墙等，将问题转化为求左墙壁可放置球的数量，最终通过图形翻折和最小公倍数等知识得出答案公式。
    - **重点代码**：无（题解主要为数学推理过程）
    - **核心实现思想**：先证明多个引理确定问题的关键性质，通过图形翻折将反弹问题简化，利用最小公倍数计算球经过左墙壁点的数量，进而得出答案为 $\gcd(n - 1,m - 1)+1$。

### 最优关键思路或技巧
通过数学方法直接得出答案的思路最为高效，如 Abeeel51 的题解，通过观察反弹规律与辗转相除的联系，直接利用最大公约数公式求解，避免了复杂的模拟或状态维护。这种从数学性质出发寻找简洁解法的思维方式，在面对类似具有规律的几何或运动问题时非常实用。

### 可拓展之处
同类型题或类似算法套路：对于涉及物体在规则图形中运动并存在反弹等规律的问题，可以尝试寻找运动的数学规律，通过数论知识（如最大公约数、最小公倍数）简化问题。也可以考虑将图形进行变换（如翻折），转化为更易处理的形式。

### 推荐题目
- [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：考察最大公约数和最小公倍数的应用。
- [P2669 金币](https://www.luogu.com.cn/problem/P2669)：需要通过数学规律来解决问题，与本题寻找数学关系简化计算的思路类似。
- [P1463 [POI2002][HAOI2007]反素数](https://www.luogu.com.cn/problem/P1463)：运用数论知识，结合约数个数等概念求解，锻炼对数学性质的运用能力。 

---
处理用时：67.67秒